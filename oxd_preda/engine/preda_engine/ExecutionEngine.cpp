#include <cassert>
#include <tuple>
#include "../../../SFC/essentials.h"
#include "../../transpiler/transpiler/PredaCommon.h"
#include "../../native/types/type_def.h"
#include "ContractDatabase.h"
#include "ExecutionEngine.h"
#include "ContractRuntimeInstance.h"
#include "PredaCompiledContracts.h"


struct AutoReleaseExecutionIntermediateData
{
	CExecutionEngine *_p;
	AutoReleaseExecutionIntermediateData(CExecutionEngine *p)
		: _p(p)
	{}

	~AutoReleaseExecutionIntermediateData()
	{
		_p->ReleaseExecutionIntermediateData();
	}
};

CExecutionEngine::CExecutionEngine(CContractDatabase *pDB)
	: m_pDB(pDB), m_runtimeInterface(pDB), 
	m_wasm_runtime(
		pDB->m_runtime_mode == RuntimeMode::WASM || pDB->m_runtime_mode == RuntimeMode::CWASM ?
		WASMRuntime::CreateRuntime(*this, pDB->wasm_engine(), pDB->wasm_main_module()) :
		std::optional<WASMRuntime>{}
	),
	m_base_linker(
		pDB->m_runtime_mode == RuntimeMode::WASM || pDB->m_runtime_mode == RuntimeMode::CWASM ?
		WASMRuntime::CreateBaseLinker(*this) :
		std::optional<wasmtime::Linker>{}
	)
{
	m_runtimeInterface.SetExecutionEngine(this);
}

void CExecutionEngine::ReleaseExecutionIntermediateData()
{
	// do not report orphan token when destroying contract instances.
	// contract instances are serialized after execution, hence also the tokens in them.
	// The only exception is a const call. In this case serialization of the token shouldn't expected anyway.
	m_runtimeInterface.TurnOhphanTokenReportOnOff(false);
	for (auto itor : m_intermediateContractInstances)
		itor.second->DestroyContractInstance();
	m_runtimeInterface.TurnOhphanTokenReportOnOff(true);
	m_intermediateContractInstances.clear();
	m_runtimeInterface.ClearStateModifiedFlags();
	m_runtimeInterface.ClearContractStack();
	m_runtimeInterface.ClearBigInt();

	m_inputStateCopies.clear();
}

ContractRuntimeInstance* CExecutionEngine::CreateContractInstance(const rvm::ContractModuleID &moduleId, rvm::ContractVersionId cvId, const rvm::ContractVersionId *importedCvId, uint32_t numImportedContracts)
{
	{
		auto itor = m_intermediateContractInstances.find(cvId);
		if (itor != m_intermediateContractInstances.end())
		{
			return itor->second;
		}
	}

	ContractModuleLoaded* loaded_mod = nullptr;

	{
		auto it = m_loadedContractModule.find(moduleId);
		if (it != m_loadedContractModule.end())
		{
			loaded_mod = it->second.get();
		}
		else
		{
			ContractModule* mod = m_pDB->GetContractModule(moduleId);
			if (mod)
			{
				if (m_loadedContractModule.find(moduleId) == m_loadedContractModule.end())
					m_loadedContractModule.emplace(moduleId, mod->LoadToEngine(*this));
				loaded_mod = m_loadedContractModule.find(moduleId)->second.get();
			}
		}
	}

	if (!loaded_mod) {
		return nullptr;
	}

	ContractRuntimeInstance* pContractInstance = loaded_mod->NewInstance(*this, cvId, importedCvId, numImportedContracts).release();
	if (!pContractInstance) {
		return nullptr;
	}
	pContractInstance->mId = moduleId;
	pContractInstance->cvId = cvId;
	pContractInstance->currentMappedContractContextLevel = prlrt::ContractContextType::None;

	m_intermediateContractInstances.try_emplace(cvId, pContractInstance);

	return pContractInstance;
}

bool CExecutionEngine::MapNeededContractContext(rvm::ExecutionContext *executionContext, ContractRuntimeInstance *pInstance, uint32_t calledFunctionFlag)
{
	prlrt::ContractContextType neededContextLevel = prlrt::ContractContextType::None;
	uint32_t functionScopeType = calledFunctionFlag & uint32_t(transpiler::FunctionFlags::ScopeTypeMask);
	neededContextLevel = _details::PredaScopeToRuntimeContextType(transpiler::ScopeType(functionScopeType));

	constexpr uint8_t shardLevel = uint8_t(prlrt::ContractContextType::Shard);

	// if mapping a custom scope, it should be impossible that another custom scope was already mapped
	assert(!(uint8_t(pInstance->currentMappedContractContextLevel) > shardLevel && uint8_t(neededContextLevel) > shardLevel && pInstance->currentMappedContractContextLevel != neededContextLevel));

	// everything needed already mapped
	if (pInstance->currentMappedContractContextLevel >= neededContextLevel)
		return true;

	// collect the needed contexts
	std::vector<uint8_t> neededContexts(1, uint8_t(neededContextLevel));	// first the context of the function
	// then global / shard if not already mapped
	for (uint8_t i = uint8_t(pInstance->currentMappedContractContextLevel) + 1; i < std::min(uint8_t(shardLevel + 1), uint8_t(neededContextLevel)); i++)
		neededContexts.push_back(i);

	for (int i = 0; i < (int)neededContexts.size(); i++)
	{
		const uint8_t *buffer = nullptr;
		uint32_t buffer_size = 0;
		rvm::Scope scope = _details::PredaScopeToRvmScope(_details::RuntimeContextTypeToPredaScope(prlrt::ContractContextType(neededContexts[i])));
		if (scope == rvm::Scope::_Bitmask)
			return false;

		{
			rvm::ConstStateData state = executionContext->GetState(rvm::CONTRACT_SET_SCOPE(rvm::CONTRACT_UNSET_BUILD(pInstance->cvId), scope));
			if (state.DataSize)
			{
				if (state.Version != rvm::CONTRACT_BUILD(pInstance->cvId))		// the version of the state doesn't match the contract version, TODO: upgrade state when contract state upgrading is implemented in the future
					return false;
				m_inputStateCopies.push_back(std::vector<uint8_t>());
				m_inputStateCopies.back().resize(state.DataSize);
				memcpy(&m_inputStateCopies.back()[0], state.DataPtr, state.DataSize);
				buffer = &m_inputStateCopies.back()[0];
				buffer_size = (uint32_t)state.DataSize;
			}
		}

		if (buffer == nullptr)
			continue;

		if (!pInstance->MapContractContextToInstance(prlrt::ContractContextType(neededContexts[i]), buffer, buffer_size))
		{
			return false;
		}
	}
	pInstance->currentMappedContractContextLevel = neededContextLevel;

	return true;
}

uint32_t CExecutionEngine::InvokeContractCall(rvm::ExecutionContext *executionContext, rvm::ContractVersionId cvId, uint32_t opCode, const void **ptrs, uint32_t numPtrs)
{
	const rvm::DeployedContract* deployedContract = executionContext->GetContractDeployed(cvId);
	if (deployedContract == nullptr)
		return uint32_t(prlrt::ExecutionError::RuntimeException) | (uint32_t(prlrt::ExceptionType::CrossCallContractNotFound) << 8);

	const ContractDatabaseEntry *pContractEntry = m_pDB->FindContractEntry(deployedContract->Module);;
	if (!pContractEntry
		|| opCode >= uint32_t(pContractEntry->compileData.functions.size())
		|| (pContractEntry->compileData.functions[opCode].flags & uint32_t(transpiler::FunctionFlags::CallableFromOtherContract)) == 0)
		return uint32_t(prlrt::ExecutionError::RuntimeException) | (uint32_t(prlrt::ExceptionType::CrossCallFunctionNotFound) << 8);

	m_runtimeInterface.PushContractStack(deployedContract->Module, cvId, pContractEntry->compileData.functions[opCode].flags, (const rvm::ContractVersionId*)deployedContract->Stub, deployedContract->StubSize / sizeof(rvm::ContractVersionId));
	// no need to call m_runtimeInterface.SetExecutionContext() here, contract call is only possible after a transaction call, therefore execution context is already set

	if (deployedContract->StubSize % sizeof(rvm::ContractVersionId) != 0 || deployedContract->StubSize / sizeof(rvm::ContractVersionId) != pContractEntry->compileData.importedContracts.size())
		return uint32_t(ExecutionResult::CannotCreateContractInstance);
	ContractRuntimeInstance* pContractInstance = CreateContractInstance(deployedContract->Module, cvId, (const rvm::ContractVersionId*)deployedContract->Stub, deployedContract->StubSize / sizeof(rvm::ContractVersionId));
	if (pContractInstance == nullptr)
		return uint32_t(prlrt::ExecutionError::RuntimeException) | (uint32_t(prlrt::ExceptionType::CrossCallContractNotFound) << 8);

	if (!MapNeededContractContext(executionContext, pContractInstance, pContractEntry->compileData.functions[opCode].flags))
		return uint32_t(ExecutionResult::MapContractStateError);

	uint32_t ret = pContractInstance->ContractCall(opCode, ptrs, numPtrs);

	m_runtimeInterface.PopContractStack();

	return ret;
}

rvm::InvokeResult CExecutionEngine::Invoke(rvm::ExecutionContext *executionContext, uint32_t gas_limit, rvm::ContractInvokeId contract, rvm::OpCode opCode, const rvm::ConstData* args_serialized)
{
	rvm::InvokeResult ret;
	ret.SubCodeHigh = 0;
	ret.SubCodeLow = 0;

	// TODO: get gas from executionContext once it's implemented.
	m_runtimeInterface.SetGas(1000000);
	m_runtimeInterface.SetChainState(executionContext);

	rvm::ContractVersionId cvId = rvm::CONTRACT_UNSET_SCOPE(contract);
	const rvm::DeployedContract* deployedContract = executionContext->GetContractDeployed(cvId);
	uint32_t internalRet = Invoke_Internal(executionContext, cvId, deployedContract, opCode, args_serialized, gas_limit);

	ret.GasBurnt = rvm::RVM_GAS_BURNT_DEFAULT;
	ret.SubCodeHigh = internalRet & 0xff;
	switch (ExecutionResult(ret.SubCodeHigh))
	{
	case ExecutionResult::NoError:
		ret.Code = rvm::InvokeErrorCode::Success;
		return ret;
	case ExecutionResult::ContractNotFound:
		ret.Code = rvm::InvokeErrorCode::ContractUnavailable;
		return ret;
	case ExecutionResult::InvalidFunctionId:
		ret.Code = rvm::InvokeErrorCode::ContractFunctionDisallowed;
		return ret;
	case ExecutionResult::FunctionSignatureMismatch:
		ret.Code = rvm::InvokeErrorCode::ContractFunctionDisallowed;
		return ret;
	case ExecutionResult::ExecutionError:
	{
		switch (prlrt::ExecutionError((internalRet >> 8) & 0xff))
		{
		case prlrt::ExecutionError::NoError:
			ret.Code = rvm::InvokeErrorCode::InternalError;
			return ret;
		case prlrt::ExecutionError::FunctionNotFound:
			ret.Code = rvm::InvokeErrorCode::ContractFunctionUnavailable;
			return ret;
		case prlrt::ExecutionError::ArgumentDeserializationFailure:
			ret.Code = rvm::InvokeErrorCode::InvalidFunctionArgments;
			return ret;
		case prlrt::ExecutionError::RuntimeException:
		{
			ret.Code = rvm::InvokeErrorCode::ExceptionThrown;
			ret.SubCodeLow |= (internalRet >> 16);
			return ret;
		}
		case prlrt::ExecutionError::UserDefinedError:
			ret.Code = rvm::InvokeErrorCode::InternalError;
			return ret;
		case prlrt::ExecutionError::SerializeOutUnknownContextClass:
			ret.Code = rvm::InvokeErrorCode::InternalError;
			return ret;
		case prlrt::ExecutionError::WASMTrapError:
			ret.Code = rvm::InvokeErrorCode::InternalError;
			return ret;
		default:
			ret.Code = rvm::InvokeErrorCode::InternalError;
			return ret;
		}
	}
	//case ExecutionResult::ContractStateExceedsSizeLimit:
	//case ExecutionResult::SerializeOutContractStateError:
	//	ret.Code = rvm::InvokeErrorCode::SaveStateFailure;
	//	return ret;
	case ExecutionResult::CannotLoadLibrary:
	case ExecutionResult::CannotCreateContractInstance:
		ret.Code = rvm::InvokeErrorCode::InternalError;
		return ret;
	case ExecutionResult::MapContractStateError:
		ret.Code = rvm::InvokeErrorCode::LoadStateFailure;
		break;
	default:
		break;
	}

	return ret;
}

uint32_t CExecutionEngine::Invoke_Internal(rvm::ExecutionContext *executionContext, rvm::ContractVersionId cvId, const rvm::DeployedContract *deployedContract, rvm::OpCode opCode, const rvm::ConstData* args_serialized, uint32_t gas_limit)
{
	AutoReleaseExecutionIntermediateData autoRelease(this);

	if (deployedContract == nullptr)
		return uint32_t(ExecutionResult::ContractNotFound);

	const ContractDatabaseEntry *pContractEntry = m_pDB->FindContractEntry(deployedContract->Module);
	if (!pContractEntry)
		return uint32_t(ExecutionResult::ContractNotFound);

	auto opCodeReal = enum_to_underlying(opCode);
	if (opCodeReal >= uint32_t(pContractEntry->compileData.functions.size()))
		return uint32_t(ExecutionResult::InvalidFunctionId);
	{
		rvm::InvokeContextType txnType = executionContext->GetInvokeType();
		if ((txnType == rvm::InvokeContextType::Normal && (pContractEntry->compileData.functions[opCodeReal].flags & uint32_t(transpiler::FunctionFlags::CallableFromTransaction)) == 0)
			|| ((txnType == rvm::InvokeContextType::RelayInbound || txnType == rvm::InvokeContextType::RelayIntra) && (pContractEntry->compileData.functions[opCodeReal].flags & uint32_t(transpiler::FunctionFlags::CallableFromRelay)) == 0)
			|| (txnType == rvm::InvokeContextType::System && (pContractEntry->compileData.functions[opCodeReal].flags & uint32_t(transpiler::FunctionFlags::CallableFromSystem)) == 0))
			return uint32_t(ExecutionResult::FunctionSignatureMismatch);
	}

	m_runtimeInterface.PushContractStack(deployedContract->Module, cvId, pContractEntry->compileData.functions[opCodeReal].flags, (const rvm::ContractVersionId*)deployedContract->Stub, deployedContract->StubSize / sizeof(rvm::ContractVersionId));
	m_runtimeInterface.SetExecutionContext(executionContext);

	if (deployedContract->StubSize % sizeof(rvm::ContractVersionId) != 0 || deployedContract->StubSize / sizeof(rvm::ContractVersionId) != pContractEntry->compileData.importedContracts.size())
		return uint32_t(ExecutionResult::CannotCreateContractInstance);
	ContractRuntimeInstance *pContractInstance = CreateContractInstance(deployedContract->Module, cvId, (const rvm::ContractVersionId *)deployedContract->Stub, deployedContract->StubSize / sizeof(rvm::ContractVersionId));
	if (pContractInstance == nullptr)
		return uint32_t(ExecutionResult::CannotCreateContractInstance);

	if (!MapNeededContractContext(executionContext, pContractInstance, pContractEntry->compileData.functions[opCodeReal].flags))
		return uint32_t(ExecutionResult::MapContractStateError);

	bool bGlobalContext;
	{
		uint32_t functionContextClass = pContractEntry->compileData.functions[opCodeReal].flags & uint32_t(transpiler::FunctionFlags::ScopeTypeMask);
		bGlobalContext = functionContextClass == uint32_t(transpiler::ScopeType::Global);
	}

	// TODO: pass gas_limit into contract
	uint32_t ret = pContractInstance->TransactionCall(opCodeReal, args_serialized->DataPtr, args_serialized->DataSize);

	m_runtimeInterface.PopContractStack();

	assert(m_runtimeInterface.GetContractStackSize() == 0);

	if ((ret & 0xff) != uint8_t(prlrt::ExecutionError::NoError))
		ret = (ret << 8) | uint32_t(ExecutionResult::ExecutionError);
	else
		ret = (ret << 8) | uint32_t(ExecutionResult::NoError);

	if ((ret & 0xff) == uint32_t(ExecutionResult::NoError))
	{
		// first check if multiple states will different versions of a contract is to be committed.
		// This could happen is some cases, e.g.A[v2] --calls--> B --calls--> A[v1] and A didn't have an existing state.
		std::map<rvm::ContractId, rvm::BuildNum> modifiedContractVersions;
		for (auto itor : m_intermediateContractInstances)
		{
			rvm::ContractVersionId cvId = itor.first;
			rvm::ContractId cId = rvm::CONTRACT_UNSET_BUILD(cvId);
			rvm::BuildNum version = rvm::CONTRACT_BUILD(cvId);
			auto itor2 = modifiedContractVersions.find(cId);
			if (itor2 == modifiedContractVersions.end())
				modifiedContractVersions.emplace(cId, version);
			else
			{
				if (itor2->second != version)
					return uint32_t(ExecutionResult::SerializeOutMultipleVersionState);
			}
		}

		thread_local std::vector<std::tuple<rvm::ContractVersionId, rvm::Scope, uint8_t *>> pendingStates;
		pendingStates.clear();
		for (auto itor : m_intermediateContractInstances)
		{
			bool *pModifiedFlags = m_runtimeInterface.GetStateModifiedFlags(itor.first);
			if (pModifiedFlags)
			{
				for (uint8_t i = 0; i < uint8_t(prlrt::ContractContextType::Num); i++)
				{
					// global state is read-only in non-global scope, therefore no need to commit it
					if (i == uint8_t(prlrt::ContractContextType::Global) && !bGlobalContext)
						continue;

					if (pModifiedFlags[i])
					{
						uint32_t csSize = itor.second->GetContractContextSerializeSize(prlrt::ContractContextType(i));
						if (csSize == 0)
							continue;

						uint8_t *pStateData = executionContext->AllocateStateMemory(csSize);
						uint32_t serializeRes = itor.second->SerializeOutContractContext(prlrt::ContractContextType(i), pStateData, csSize);
						if ((serializeRes & 0xff) != uint8_t(prlrt::ExecutionError::NoError))
						{
							for (auto &it : pendingStates)
								executionContext->DiscardStateMemory(std::get<2>(it));

							return (serializeRes << 8) | uint32_t(ExecutionResult::ExecutionError);
						}

						pendingStates.emplace_back(itor.second->cvId, _details::PredaScopeToRvmScope(_details::RuntimeContextTypeToPredaScope(prlrt::ContractContextType(i))), pStateData);
					}
				}
			}
		}

		for (auto &it : pendingStates)
			executionContext->CommitNewState(rvm::CONTRACT_SET_SCOPE(std::get<0>(it), std::get<1>(it)), std::get<2>(it));
	}

	return ret;
}

bool CExecutionEngine::DeployContracts(rvm::ExecutionContext* exec, rvm::CompiledModules* linked, const rvm::ContractVersionId* target_cvids, rvm::DataBuffer** deploy_stub, rvm::LogMessageOutput* log_msg_output)
{
	return m_pDB->Deploy(exec, linked, target_cvids, deploy_stub, log_msg_output);
}

rvm::InvokeResult CExecutionEngine::InitializeContracts(rvm::ExecutionContext* executionContext, uint32_t gas_limit, rvm::CompiledModules* linked, const rvm::ConstData* ctor_args)
{
	//if(gas_limit < rvm::RVM_GAS_BURNT_DEFAULT)return { 0, 0, rvm::InvokeErrorCode::InsufficientGas, 0 };

	PredaCompiledContracts* pCompiledContracts = (PredaCompiledContracts*)linked;
	assert(pCompiledContracts->IsLinked());

	uint32_t numContracts = linked->GetCount();
	std::vector<rvm::ContractVersionId> ids(numContracts);
	for (uint32_t i = 0; i < numContracts; i++)
	{
		const ContractCompileData* pCompiledData = pCompiledContracts->GetCompiledData(i);
		ids[i] = _details::GetOnChainContractIdFromContractFullName(executionContext, pCompiledData->dapp + "." + pCompiledData->name);
		if (ids[i] == rvm::ContractVersionIdInvalid)
			return {0, 0, rvm::InvokeErrorCode::ContractUnavailable, 0};
	}

	const std::vector<uint32_t>& compileOrder = pCompiledContracts->GetCompileOrder();
	for (uint32_t i = 0; i < uint32_t(compileOrder.size()); i++)
	{
		uint32_t slot = compileOrder[i];
		rvm::SystemFunctionOpCodes opCodes;
		linked->GetContract(slot)->GetSystemFunctionOpCodes(&opCodes);
		if (opCodes.GlobalDeploy != rvm::OpCodeInvalid)
		{
			// TODO: design a mechanism to distribute gas among multiple contracts
			rvm::InvokeResult result = Invoke(executionContext, gas_limit, rvm::CONTRACT_SET_SCOPE(ids[slot], rvm::Scope::Global), opCodes.GlobalDeploy, &ctor_args[slot]);
			if (result.Code != rvm::InvokeErrorCode::Success)
				return result;
		}
	}

	//return { 0, 0, rvm::InvokeErrorCode::Success, rvm::RVM_GAS_BURNT_DEFAULT };
	return { 0, 0, rvm::InvokeErrorCode::Success, 0 };
}

void CExecutionEngine::GetExceptionMessage(uint16_t except, rvm::StringStream* str) const
{
	rt::EnumStringify ExceptionEnumString((prlrt::ExceptionType)except);
	str->Append(ExceptionEnumString._p, (uint32_t)ExceptionEnumString._len);
}