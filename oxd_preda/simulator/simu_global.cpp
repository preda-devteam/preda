#include "simu_global.h"
#include "simulator.h"
#include "../native/types/data_jsonifer.h"


namespace oxd
{

void ContractsDatabase::Reset(const ContractsDatabase& x)
{
	_NextContractSN = x._NextContractSN;
	ASSERT(_ContractInfo.size() == 0);
}

const ContractsDatabase::ContractInfo* ContractsDatabase::FindContractInfo(const rvm::ContractModuleID& mid)
{
	for(auto& it : _ContractInfo)
	{
		if(rt::IsEqual(it.second->Deployment.Module, mid))
			return it.second;
	}

	return nullptr;
}

void ContractsDatabase::Commit(ContractsDatabase& x)
{
	for(auto& it : _ContractInfo)
		x._ContractInfo[it.first] = it.second;
	for(auto& it : _Contracts)
		x._Contracts[it.first] = it.second;
	for(auto& it : _ContractBuildNumLatest)
		x._ContractBuildNumLatest[it.first] = it.second;
	for(auto& it : _ContractFunctions)
		x._ContractFunctions[it.first] = it.second;
	for(auto& it : _ContractEngine)
		x._ContractEngine[it.first] = it.second;

	x._NextContractSN = _NextContractSN;

	_ContractInfo.clear();
	Revert();
}

void ContractsDatabase::Revert()
{
	for(auto& p : _ContractInfo)
		p.second->Release();
	_ContractInfo.clear();

	_Contracts.clear();
	_ContractBuildNumLatest.clear();
	_ContractFunctions.clear();
	_ContractEngine.clear();

	_NextContractSN = 0;
}

SimuGlobalShard::SimuGlobalShard(Simulator* simu, uint64_t time_base, uint32_t shard_order)
	:SimuShard(simu, time_base, shard_order)
{
	_pGlobalShard = this;
	_bDeploying = false;
}

rvm::BuildNum SimuGlobalShard::_GetContractEffectiveBuild(rvm::ContractId contract) const
{
	if(_bDeploying)
	{	
		auto v = _DeployingDatabase._ContractBuildNumLatest.get(contract, 0);
		if(v)return v;
	}

	return _ContractBuildNumLatest.get(contract, 0);
}

const rvm::DeployedContract* SimuGlobalShard::_GetContractDeployed(rvm::ContractVersionId contract) const
{
	if(_bDeploying)
	{
		auto it = _DeployingDatabase._ContractInfo.find(contract);
		if(it != _DeployingDatabase._ContractInfo.end())
			return &it->second->Deployment;
	}

	auto it = _ContractInfo.find(contract);
	if(it != _ContractInfo.end())
		return &it->second->Deployment;
	else
		return nullptr;
}

void SimuGlobalShard::DeployBegin()
{
	ASSERT(!_bDeploying);

	_bDeploying = true;
	_DeployingDatabase.Reset(*this);
}

void SimuGlobalShard::DeployEnd(bool commit)
{
	ASSERT(_bDeploying);

	if(commit)
	{
		_DeployingDatabase.Commit(*this);
		_DeployingStates.Commit(*this);
	}
	else
	{
		_DeployingDatabase.Revert();
		_DeployingStates.Revert();
	}

	_bDeploying = false;
}

void SimuGlobalShard::_OnGlobalTransactionExecuted(bool succeess)
{
	if(_bDeploying)
		DeployEnd(succeess);
}

ContractsDatabase::ContractInfo* ContractsDatabase::ContractInfo::Clone() const
{
	uint32_t len =  GetSize();
	auto* ret = (ContractInfo*)_Malloc32AL(BYTE, len);
	memcpy(ret, this, len);

	return ret;
}

rvm::ContractVersionId SimuGlobalShard::DeployUnnamedContract(rvm::ContractVersionId deploy_initiator, uint64_t initiator_dappname, const rvm::DeployedContract* origin_deploy)
{
	ASSERT(origin_deploy);
	ASSERT(_pTxn);
	if(!_bDeploying)
	{	// DeployBegin, unnamed deployment can be invoked more than once in a single transaction execution
		_bDeploying = true;
		_DeployingDatabase.Reset(*this);
	}

	auto* info = _DeployingDatabase.FindContractInfo(origin_deploy->Module);
	if(!info)info = FindContractInfo(origin_deploy->Module);
	if(info)
	{
		rvm::ContractVersionId cid = rvm::CONTRACT_ID_MAKE(
											_DeployingDatabase._NextContractSN++, 
											rvm::CONTRACT_DAPP(deploy_initiator),
											rvm::CONTRACT_ENGINE(deploy_initiator),
											BUILD_NUM_INIT
		);

		auto& new_info = _DeployingDatabase._ContractInfo[cid];
		new_info = info->Clone();
		new_info->Deployment.Version = BUILD_NUM_INIT;
		new_info->Deployment.Height = _BlockHeight;

		_DeployingDatabase._ContractBuildNumLatest[rvm::CONTRACT_UNSET_BUILD(cid)] = rvm::CONTRACT_BUILD(cid);

		return cid;
	}
	else
		return rvm::ContractVersionIdInvalid;
}

rvm::ConstStateData SimuGlobalShard::GetState(rvm::ContractScopeId contract) const
{
	SimuState* r = nullptr;

	if(_bDeploying && _DeployingStates._ShardStates.Get(contract, &r))
		goto FOUND;

	r = _ShardStates.Get(contract);

FOUND:
	if(r)return { r->Data, r->DataSize, r->Version };
	else return { nullptr, 0, 0 };
}

rvm::ConstStateData SimuGlobalShard::GetState(rvm::ContractScopeId contract, const rvm::ScopeKey* key) const
{
	ShardStateKey k = { contract, *key };
	SimuState* r = nullptr;

	if(_bDeploying && _DeployingStates._ShardKeyedStates.Get(k, &r))
		goto FOUND;

	r = _ShardKeyedStates.Get(k);

FOUND:
	if(r)return { r->Data, r->DataSize, r->Version };
	else return { nullptr, 0, 0 };
}

void SimuGlobalShard::CommitNewState(rvm::ContractInvokeId ciid, uint8_t* state)
{
	if(_bDeploying)
	{
		if(state)
		{
			auto* s = (SimuState*)(state - offsetof(SimuState, Data));
			s->Version = rvm::CONTRACT_BUILD(ciid);

			_DeployingStates._ShardStates.Set(rvm::CONTRACT_UNSET_BUILD(ciid), s);
		}
		else
		{
			_DeployingStates._ShardStates.Set(rvm::CONTRACT_UNSET_BUILD(ciid), nullptr, true);
		}
	}
	else
		SimuShard::CommitNewState(ciid, state);
}

void SimuGlobalShard::CommitNewState(rvm::ContractInvokeId contract, const rvm::ScopeKey* key, uint8_t* state)
{
	if(_bDeploying)
	{
		auto csid = rvm::CONTRACT_UNSET_BUILD(contract);
		ShardStateKey k = { csid, *key };

		if(state)
		{
			auto* s = (SimuState*)(state - offsetof(SimuState, Data));
			s->Version = rvm::CONTRACT_BUILD(contract);

			_DeployingStates._ShardKeyedStates.Set(k, s);
		}
		else
		{
			_DeployingStates._ShardKeyedStates.Set(k, nullptr, true);
		}
	}
	else
		SimuShard::CommitNewState(contract, key, state);
}

bool SimuGlobalShard::AllocateContractIds(const BuildContracts& built)
{
	ASSERT(_bDeploying);
	auto* linked = built._pCompiled;

	rvm::EngineId e = linked->GetEngineId();
	uint32_t count = (uint32_t)linked->GetCount();
	for(uint32_t i=0; i<count; i++)
	{
		auto* c = linked->GetContract(i);
		rt::String full_name = _pSimulator->DAPP_NAME + '.' + c->GetName().Str();
		
		rvm::ContractVersionId cvid = _Contracts.get(full_name, rvm::ContractVersionIdInvalid);
		if(cvid == rvm::ContractVersionIdInvalid)
		{
			rvm::ContractId cid = rvm::CONTRACT_ID_MAKE(_DeployingDatabase._NextContractSN++, _pSimulator->DAPP_ID, e);
			cvid = rvm::CONTRACT_SET_BUILD(cid, BUILD_NUM_INIT);
			
			_DeployingDatabase._Contracts[full_name] = cvid;
			_DeployingDatabase._ContractBuildNumLatest[cid] = BUILD_NUM_INIT;
			_DeployingDatabase._ContractEngine[full_name] = e;
			_Contracts[full_name] = cvid;
		}
		else
		{
			if(_DeployingDatabase._ContractEngine[full_name] != e && _ContractEngine[full_name] != e)
			{
				_LOG("[PRD] Contract " << full_name << " already deployed with another engine")
				return false;
			}

			rvm::ContractId cid = rvm::CONTRACT_UNSET_BUILD(cvid);
			rvm::BuildNum ver = _ContractBuildNumLatest.get(cid) + 1;
			_DeployingDatabase._ContractBuildNumLatest[cid] = ver;
			_DeployingDatabase._Contracts[full_name] = rvm::CONTRACT_SET_BUILD(cid, ver);
		}
	}

	return true;
}

rvm::DAppId	SimuGlobalShard::_GetDAppByName(const rvm::ConstString* dapp_name) const
{
	if(dapp_name->Str() == Simulator::Get().DAPP_NAME)
		return Simulator::Get().DAPP_ID;

	return rvm::DAppIdInvalid;
}

void SimuGlobalShard::_FinalizeFunctionInfo(const rvm::ContractVersionId& cvid, const rt::String_Ref& func_prefix, const rvm::ContractModuleID& deploy_id, const rvm::Interface* c, const rvm::ConstData& stub)
{
	ContractInfo*& info = _DeployingDatabase._ContractInfo[cvid];
	uint32_t info_len = stub.DataSize + offsetof(ContractsDatabase::ContractInfo, Deployment.Stub);
	info = (ContractsDatabase::ContractInfo*)_Malloc32AL(BYTE, info_len);

	info->Deployment.Version = rvm::CONTRACT_BUILD(cvid);
	info->Deployment.Module = deploy_id;
	info->Deployment.StubSize = stub.DataSize;
	if (stub.DataSize > 0)
		memcpy(info->Deployment.Stub, stub.DataPtr, stub.DataSize);

	for(int i=0; i<256; i++)
		info->ScopeOfOpcode[i] = rvm::ScopeInvalid;

	UINT func_co = c->GetFunctionCount();
	rt::String funcname;
	for(UINT i=0; i<func_co; i++)
	{
		auto opcode = c->GetFunctionOpCode(i);
		info->ScopeOfOpcode[(int)opcode] = c->GetFunctionScope(i);
		funcname = func_prefix + '.' + c->GetFunctionName(i).Str();
		auto& fi = _DeployingDatabase._ContractFunctions[funcname].push_back();
		fi.Contract = rvm::CONTRACT_UNSET_BUILD(cvid);
		fi.Op = opcode;
		rvm::StringStreamImpl ss(fi.FunctionSignature);
		c->GetFunctionSignature(i, &ss);
	}
}

bool SimuGlobalShard::CommitDeployment(const BuildContracts& built)
{
	ASSERT(_bDeploying);
	auto* deployed = built._pCompiled;
	ASSERT(deployed);

	rt::String if_prefix;
	uint32_t count = deployed->GetCount();
	for(uint32_t i=0; i<count; i++)
	{
		auto* c = deployed->GetContract(i);
		auto name = c->GetName();
		rt::String full_name = _pSimulator->DAPP_NAME + '.' + name.Str();
		rvm::ConstString s = { full_name.Begin(), (uint32_t)full_name.GetLength() };
		rvm::ContractVersionId cvid = _GetContractByName(&s);
		ASSERT(cvid != rvm::ContractVersionIdInvalid);

		_FinalizeFunctionInfo(cvid, full_name, *c->GetModuleID(), c, built._ContractDeployStub[i].GetRvmConstData());
	}

	return true;
}

rvm::ContractVersionId SimuGlobalShard::_GetContractByName(const rvm::ConstString* dapp_contract_name) const
{
	rvm::ContractVersionId r = rvm::ContractVersionIdInvalid;
	if(_bDeploying)
		r = _DeployingDatabase._Contracts.get(dapp_contract_name->Str(), rvm::ContractVersionIdInvalid);

	if(r == rvm::ContractVersionIdInvalid)
		r = _Contracts.get(dapp_contract_name->Str(), rvm::ContractVersionIdInvalid);

	return r;
}

void SimuGlobalShard::Term()
{
	ASSERT(!_bDeploying);

	ContractsDatabase::Revert();
	_DeployingDatabase.Revert();
	_DeployingStates.Revert();

	SimuShard::Term();
}

void BuildContracts::Init(const rt::String_Ref& dapp, rvm::DAppId dapp_id, rvm::EngineId eid)
{
	_DAppId = dapp_id;
	_EngineId = eid;
	_Stage = STAGE_SOURCE;
	_DAppName = dapp;
	_CompileDependency.Empty();
	_Sources.ShrinkSize(0);
	_ConstructorArgs.ShrinkSize(0);
	_Filenames.ShrinkSize(0);

	_ContractModuleIds.ShrinkSize(0);
	_ResetContractWorkData();
	_ContractToFilename.clear();
}

void BuildContracts::Term()
{
	_pEngine = nullptr;
	_EngineId = rvm::EngineId::Unassigned;
	_DAppId = rvm::DAppIdInvalid;
	_Sources.ShrinkSize(0);
	_Filenames.ShrinkSize(0);

	_SafeRelease(_pCompiled);
	_CompileDependency.Empty();
	_ContractModuleIds.ShrinkSize(0);
	_ResetContractWorkData();
}

void BuildContracts::AddContractCode(const rt::String_Ref& code, const rt::String_Ref& deploy_arg, const rt::String_Ref& fn)
{
	ASSERT(_Stage == STAGE_SOURCE);

	rvm::ConstData data = { (uint8_t*)code.Begin(), (uint32_t)code.GetLength() };
	rt::String_Ref contract_name = _pEngine->GetContractName(&data).Str();

	_Sources.push_back(code);
	_Filenames.push_back(fn);
	_ConstructorArgs.push_back(deploy_arg);

	if(!contract_name.IsEmpty())
	{
		_LOG("Source code for contract `"<<contract_name<<"` is loaded from "<<fn);
	}
	else
	{
		_LOG("Cannot extract contract name from source code file "<<fn);
	}
}

void BuildContracts::Log(rvm::LogMessageType type, uint32_t code, uint32_t unitIndex, uint32_t line, uint32_t lineOffset, const rvm::ConstString *message)
{
	auto log_type = rt::LOGTYPE_INFORMATIONAL;
	LPCSTR type_str = "";
	switch(type)
	{
	case rvm::LogMessageType::Error:		type_str = "error";		log_type = rt::LOGTYPE_ERROR;	break;
	case rvm::LogMessageType::Warning:		type_str = "warning";	log_type = rt::LOGTYPE_WARNING;	break;
	case rvm::LogMessageType::Information:	type_str = "info";		break;
	default: ASSERT(0);
	}

	rt::String_Ref msg = "<no message>";
	if(message)msg = rt::String_Ref(message->StrPtr, message->Length);

	const char* label[] = { nullptr, "compile", "link", "deploy", nullptr };

	rt::String_Ref fn = _Filenames[unitIndex];
	if(fn.IsEmpty())
	{
		auto str = rt::SS("build_unit#") + unitIndex + '[' + rt::EnumStringify(_EngineId) + ']';
		fn = ALLOCA_C_STRING(str);
	}

	__LOG_TYPE(	fn<<'('<<line<<':'<<lineOffset<<"): "<<
				label[_Stage]<<' '<<type_str<<" #"<<code<<rt::SS(": ")<<
				msg,
				rt::LOGTYPE_IN_CONSOLE|rt::LOGTYPE_IN_LOGFILE|log_type
	);
}

bool BuildContracts::Compile(bool checkDeployArg)
{
	uint32_t count = (uint32_t)_Sources.GetSize();
	if(!count)return false;

	if(!_pEngine)
	{
		_LOG_WARNING("Engine "<<rt::EnumStringify(_EngineId)<<" is not available");
		return false;
	}

	ASSERT(_Stage == STAGE_SOURCE);
	ASSERT(_pCompiled == nullptr);

	auto* codes = (rvm::ConstData*)_alloca(sizeof(rvm::ConstData) * count);

	for(uint32_t i = 0; i < count; i++)
		codes[i] = { (uint8_t*)_Sources[i].Begin(), (uint32_t)_Sources[i].GetLength() };

	_Stage = STAGE_COMPILE;
	_LOG("Compiling " << count << " contract(s), target=" << rt::EnumStringify(_EngineId));

	rvm::CompilationFlag cflag = rvm::CompilationFlag::None;
	if(os::CommandLine::Get().HasOption("perftest"))
		cflag |= rvm::CompilationFlag::DisableDebugPrint;

	rvm::ConstString dapp = { _DAppName.Begin(), (uint32_t)_DAppName.GetLength() };
	if(_pEngine->Compile(&dapp, count, codes, cflag, &_pCompiled, this) && _pCompiled && _pCompiled->GetCount() == count)
	{
		_ResetContractWorkData(count);
		rt::String filename, sig;

		for(uint32_t i = 0; i < count; i++)
		{
			auto* contract = _pCompiled->GetContract(i);
			ASSERT(contract);

			if(_EngineId == rvm::EngineId::SOLIDITY_EVM)
			{
				rt::JsonObject sol_json(_Sources[0]);
				_ContractToFilename[sol_json.GetValue("entryContract")] = filename = sol_json.GetValue("entryFile");
			}
			else
			{
				rvm::ConstString contractCS = contract->GetName();
				_ContractToFilename[contractCS.Str()] = filename = _Filenames[i].GetFileName();
			}

			auto deploy_arg = _ConstructorArgs[i];
			rvm::SystemFunctionOpCodes opcodes;
			contract->GetSystemFunctionOpCodes(&opcodes);

			if (opcodes.GlobalDeploy == rvm::OpCodeInvalid)
			{
				if (!deploy_arg.IsEmpty())
				{
					_LOG_WARNING("[PRD]: Contract deploy arguments for `" << filename << "` is not expected");
					goto COMPILE_FAILED;
				}
			}
			else if(checkDeployArg)
			{
				uint32_t func_co = contract->GetFunctionCount();
				for(uint32_t f=0; f<func_co; f++)
					if(opcodes.GlobalDeploy == contract->GetFunctionOpCode(f))
					{
						rvm::StringStreamImpl sig_ss(sig);

						if(contract->GetFunctionSignature(f, &sig_ss))
						{
							rvm::RvmDataJsonParser arg_parse(sig, nullptr);
							std::vector<uint8_t> data;
							if (deploy_arg.IsEmpty())			// when deploy_arg is not given, regarding it as an empty json
								deploy_arg = "{}";
							if(rvm::FunctionArgumentUtil::JsonParseArguments(sig.GetString(), nullptr, deploy_arg, data))
							{
								auto* d =  _Malloc8AL(uint8_t, data.size());
								memcpy(d, data.data(), data.size());

								_ContractDeployArgs[i] = { d, (uint32_t)data.size() };
								goto GO_NEXT_SOURCE;
							}
							else
							{
								_LOG_WARNING("[PRD]: Failed to parse Json of contract deploy arguments for `"<<filename<<'`');
								goto COMPILE_FAILED;
							}
						}
					}

				_LOG_WARNING("[PRD]: Signature of contract deployment function in `"<<filename<<"` is not found");
				goto COMPILE_FAILED;
			}

GO_NEXT_SOURCE:
			continue;
		}

		_Stage = STAGE_COMPILE;
		return true;
	}
	
COMPILE_FAILED:
	_LOG_WARNING("[PRD]: Compile failed");
	_SafeRelease(_pCompiled);

	_Stage = STAGE_SOURCE;
	return false;
}

bool BuildContracts::Link()
{
	uint32_t count = (uint32_t)_Sources.GetSize();
	if(!count)return false;

	ASSERT(_Stage == STAGE_COMPILE);
	ASSERT(_pCompiled);
	ASSERT(!_pCompiled->IsLinked());

	_Stage = STAGE_LINK;
	_LOG("[PRD]: Linking " << count << " contract(s), target=" << rt::EnumStringify(_EngineId));

	ASSERT(_pEngine);
	if(_pEngine->Link(_pCompiled, this))
		return true;

	_LOG_WARNING("[PRD]: Link failed");

	_Stage = STAGE_COMPILE;
	return false;
}

bool BuildContracts::VerifyDependency(const rvm::GlobalStates* global_state) const
{
	uint32_t count = (uint32_t)_Sources.GetSize();
	if(!count)return true;

	ASSERT(_Stage >= STAGE_COMPILE);
	ASSERT(_pCompiled);

	ASSERT(_pEngine);

	auto dep_data = _CompileDependency.GetRvmConstData();
	return _pCompiled->ValidateDependency(global_state);
}

void BuildContracts::_ResetContractWorkData(uint32_t size)
{
	for(auto& p : _ContractDeployArgs)
		_SafeFree8AL_ConstPtr(p.DataPtr);

	_ContractDeployArgs.ChangeSize(size);
	_ContractDeployArgs.Zero();

	_ContractDeployStub.ChangeSize(size);
	for(auto& s : _ContractDeployStub)
		s.Empty();
}

bool BuildContracts::Deploy(rvm::ExecutionUnit* exec, rvm::ExecutionContext* exec_ctx)
{
	uint32_t count = (uint32_t)_Sources.GetSize();
	if(!count)return false;

	ASSERT(_Stage == STAGE_LINK);
	ASSERT(_pCompiled);
	ASSERT(_pCompiled->IsLinked());
	ASSERT(count == _pCompiled->GetCount());

	_ContractModuleIds.SetSize(count);
	_ContractDeployStub.SetSize(count);

	_Stage = STAGE_DEPLOY;
	
	rvm::DataBuffer** deploy_stub = (rvm::DataBuffer**)alloca(sizeof(rvm::DataBuffer*)*count);
	for(uint32_t i=0; i<count; i++)
		deploy_stub[i] = &_ContractDeployStub[i];

	if(exec->DeployContracts(exec_ctx, _pCompiled, nullptr, deploy_stub, this))
		return true;

	_ContractModuleIds.ShrinkSize(0);
	_Stage = STAGE_LINK;
	return false;
}

rvm::InvokeResult BuildContracts::InvokeConstructor(rvm::ExecutionUnit* exec, rvm::ExecutionContext* exec_ctx, uint32_t gas_limit)
{
	ASSERT(_Stage == STAGE_DEPLOY);
	return exec->InitializeContracts(exec_ctx, gas_limit, _pCompiled, _ContractDeployArgs);
}

void BuildContracts::GetContractsInfo(rt::Json& json) const
{
	rvm::CompiledModules_Jsonify(json, _pCompiled);
}

} // namespace oxd