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
	std::optional<WASMRuntime> m_wasm_rt;
	AutoReleaseExecutionIntermediateData(CExecutionEngine *p)
		: _p(p),
		m_wasm_rt(
			p->contractDatabase()->m_runtime_mode == RuntimeMode::WASM || p->contractDatabase()->m_runtime_mode == RuntimeMode::CWASM ?
			WASMRuntime::CreateRuntime(*p, p->contractDatabase()->wasm_engine(), p->contractDatabase()->wasm_main_module()) :
			std::optional<WASMRuntime>{})
	{
		_p->SetWASMRuntime(m_wasm_rt.has_value() ? &m_wasm_rt.value() : nullptr);
	}

	~AutoReleaseExecutionIntermediateData()
	{
		_p->ReleaseExecutionIntermediateData();
		_p->SetWASMRuntime(nullptr);
	}
};

CExecutionEngine::CExecutionEngine(CContractDatabase *pDB)
	: m_pDB(pDB), m_runtimeInterface(pDB), m_base_linker(
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
	m_loadedContractModule.clear();
	m_runtimeInterface.ClearStateModifiedFlags();
	m_runtimeInterface.ClearContractStack();
	m_runtimeInterface.ClearBigInt();

	m_inputStateCopies.clear();
}

ContractRuntimeInstance* CExecutionEngine::CreateContractInstance(PredaContractDID deployId, rvm::ContractId contractId)
{
	{
		auto itor = m_intermediateContractInstances.find(deployId);
		if (itor != m_intermediateContractInstances.end())
		{
			return itor->second;
		}
	}

	ContractModuleLoaded* loaded_mod = nullptr;

	{
		auto it = m_loadedContractModule.find(deployId);
		if (it != m_loadedContractModule.end())
		{
			loaded_mod = it->second.get();
		}
		else
		{
			ContractModule* mod = m_pDB->GetContractModule(deployId);
			if (mod)
			{
				loaded_mod = m_loadedContractModule.emplace(deployId, mod->LoadToEngine(*this)).first->second.get();
			}
		}
	}

	if (!loaded_mod) {
		return nullptr;
	}

	ContractRuntimeInstance* pContractInstance = loaded_mod->NewInstance(*this).release();
	if (!pContractInstance) {
		return nullptr;
	}
	pContractInstance->deployId = deployId;
	pContractInstance->contractId = contractId;
	pContractInstance->currentMappedContractContextLevel = prlrt::ContractContextType::None;

	m_intermediateContractInstances.try_emplace(deployId, pContractInstance);

	return pContractInstance;
}

bool CExecutionEngine::MapNeededContractContext(rvm::ExecutionContext *executionContext, ContractRuntimeInstance *pInstance, uint32_t calledFunctionFlag)
{
	prlrt::ContractContextType neededContextLevel = prlrt::ContractContextType::None;
	uint32_t functionScopeType = calledFunctionFlag & uint32_t(transpiler::FunctionFlags::ScopeTypeMask);
	neededContextLevel = _details::PredaScopeToRuntimeContextType(transpiler::ScopeType(functionScopeType));

	// everything needed already mapped
	if (pInstance->currentMappedContractContextLevel == neededContextLevel)
		return true;
	
	// if there are already some context mapped, it has to be none / global / shard, i.e. it should be impossible for it to be another custom scope
	assert(uint8_t(pInstance->currentMappedContractContextLevel) <= uint8_t(prlrt::ContractContextType::Shard));

	// collect the needed contexts
	std::vector<uint8_t> neededContexts(1, uint8_t(neededContextLevel));	// first the context of the function
	// then global / shard if not already mapped
	for (uint8_t i = uint8_t(pInstance->currentMappedContractContextLevel) + 1; i < std::min(uint8_t(uint8_t(prlrt::ContractContextType::Shard) + 1), uint8_t(neededContextLevel)); i++)
		neededContexts.push_back(i);

	for (int i = 0; i < (int)neededContexts.size(); i++)
	{
		const uint8_t *buffer = nullptr;
		uint32_t buffer_size = 0;
		rvm::Scope scope = _details::PredaScopeToRvmScope(_details::RuntimeContextTypeToPredaScope(prlrt::ContractContextType(neededContexts[i])));
		if (scope == rvm::Scope::Neutral)
			return false;

		{
			rvm::ConstStateData state = executionContext->GetState(rvm::_details::CONTRACT_SET_SCOPE(pInstance->contractId, scope));
			if (state.DataSize)
			{
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

uint32_t CExecutionEngine::InvokeContractCall(rvm::ExecutionContext *executionContext, rvm::ContractId contractId, uint32_t opCode, const void **ptrs, uint32_t numPtrs)
{
	PredaContractDID deployId = _details::RvmCDIDToPredaCDID(executionContext->GetContractDeploymentIdentifier(contractId));                // cross contract call always calls the latest build
	const ContractDatabaseEntry *pContractEntry = m_pDB->FindContractEntry(deployId);;
	if (!pContractEntry
		|| opCode >= uint32_t(pContractEntry->compileData.functions.size())
		|| (pContractEntry->compileData.functions[opCode].flags & uint32_t(transpiler::FunctionFlags::CallableFromOtherContract)) == 0)
		return uint32_t(prlrt::ExecutionError::RuntimeException) | (uint32_t(prlrt::ExceptionType::CrossCallFunctionNotFound) << 8);

	m_runtimeInterface.PushContractStack(deployId, pContractEntry->deployData.contractId, pContractEntry->compileData.functions[opCode].flags);
	// no need to call m_runtimeInterface.SetExecutionContext() here, contract call is only possible after a transaction call, therefore execution context is already set

	ContractRuntimeInstance *pContractInstance = CreateContractInstance(deployId, contractId);
	if (pContractInstance == nullptr)
		return uint32_t(prlrt::ExecutionError::RuntimeException) | (uint32_t(prlrt::ExceptionType::CrossCallContractNotFound) << 8);

	if (!MapNeededContractContext(executionContext, pContractInstance, pContractEntry->compileData.functions[opCode].flags))
		return uint32_t(ExecutionResult::MapContractStateError);

	uint32_t ret = pContractInstance->ContractCall(opCode, ptrs, numPtrs);

	m_runtimeInterface.PopContractStack();

	return ret;
}

rvm::InvokeResult CExecutionEngine::Invoke(rvm::ExecutionContext *executionContext, uint32_t gas_limit, const rvm::ContractDID *contract_deployment_id, rvm::OpCode opCode, const rvm::ConstData* args_serialized)
{
	rvm::InvokeResult ret;
	ret.SubCodeHigh = 0;
	ret.SubCodeLow = 0;

	// TODO: get gas from executionContext once it's implemented.
	m_runtimeInterface.SetGas(1000000);

	m_runtimeInterface.SetChainState(executionContext);

	rvm::_details::ExecutionStateScope::Set(executionContext);

	PredaContractDID deployId = _details::RvmCDIDToPredaCDID(contract_deployment_id);
	
	uint32_t internalRet = Invoke_Internal(executionContext, deployId, opCode, args_serialized, gas_limit);
	rvm::_details::ExecutionStateScope::Unset();

	ret.GasBurnt = 1;
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

uint32_t CExecutionEngine::Invoke_Internal(rvm::ExecutionContext *executionContext, PredaContractDID deployId, rvm::OpCode opCode, const rvm::ConstData* args_serialized, uint32_t gas_limit)
{
	AutoReleaseExecutionIntermediateData autoRelease(this);

	const ContractDatabaseEntry *pContractEntry = m_pDB->FindContractEntry(deployId);
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

	m_runtimeInterface.PushContractStack(deployId, pContractEntry->deployData.contractId, pContractEntry->compileData.functions[opCodeReal].flags);
	m_runtimeInterface.SetExecutionContext(executionContext);

	ContractRuntimeInstance *pContractInstance = CreateContractInstance(deployId, pContractEntry->deployData.contractId);
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
		thread_local std::vector<std::tuple<rvm::ContractId, rvm::Scope, uint8_t *>> pendingStates;
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

						pendingStates.emplace_back(itor.second->contractId, _details::PredaScopeToRvmScope(_details::RuntimeContextTypeToPredaScope(prlrt::ContractContextType(i))), pStateData);
					}
				}
			}
		}

		for (auto &it : pendingStates)
			executionContext->CommitNewState(rvm::BuildNumLatest, rvm::_details::CONTRACT_SET_SCOPE(std::get<0>(it), std::get<1>(it)), std::get<2>(it));
	}

	return ret;
}

rvm::InvokeResult CExecutionEngine::Deploy(rvm::ExecutionContext* exec, uint32_t gas_limit, rvm::CompiledContracts* linked, rvm::ContractDID* contract_deployment_ids, rvm::InterfaceDID** interface_deployment_ids, rvm::LogMessageOutput* log_msg_output)
{
	PredaCompiledContracts* pCompiledContracts = (PredaCompiledContracts*)linked;
	assert(pCompiledContracts->IsLinked());

	uint32_t numContracts = linked->GetCount();
	std::vector<rvm::ContractId> ids(numContracts);
	for (uint32_t i = 0; i < numContracts; i++)
	{
		const ContractCompileData* pCompiledData = pCompiledContracts->GetCompiledData(i);
		ids[i] = _details::GetOnChainContractIdFromContractFullName(exec, pCompiledData->dapp + "." + pCompiledData->name);
		if (ids[i] == rvm::ContractIdInvalid)
			return {0, 0, rvm::InvokeErrorCode::ContractUnavailable, 0};
	}

	if (!m_pDB->Deploy(exec, &ids[0], linked, contract_deployment_ids, interface_deployment_ids, log_msg_output))
		return { 0, 0, rvm::InvokeErrorCode::ContractUnavailable, 0 };

	// TODO: trigger on_deploy on all the deployed contracts

	return { 0, 0, rvm::InvokeErrorCode::Success, 0 };
}

void CExecutionEngine::GetExceptionMessage(uint16_t except, rvm::StringStream* str) const
{
	rt::EnumStringify ExceptionEnumString((prlrt::ExceptionType)except);
	str->Append(ExceptionEnumString._p, (uint32_t)ExceptionEnumString._len);
}