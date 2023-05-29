#include "simu_global.h"
#include "simulator.h"


namespace oxd
{

void ContractsDatabase::Reset(const ContractsDatabase& x)
{
	_NextContractSN = x._NextContractSN;
}

void ContractsDatabase::Commit(ContractsDatabase& x)
{
	for(auto& it : _Contracts)x._Contracts[it.first] = it.second;
	for(auto& it : _ContractBuildNumLatest)x._ContractBuildNumLatest[it.first] = it.second;
	for(auto& it : _ContractFunctions)x._ContractFunctions[it.first] = it.second;
	for(auto& it : _ContractInfo)_SafeDel_ConstPtr(x._ContractInfo.replace(it.first, it.second));

	x._NextContractSN = _NextContractSN;

	_ContractInfo.clear();
	Revert();
}

void ContractsDatabase::Revert()
{
	_Contracts.clear();
	_ContractBuildNumLatest.clear();
	_ContractFunctions.clear();

	for(auto& it : _ContractInfo)
		_SafeDel_ConstPtr(it.second);
	_ContractInfo.clear();

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

const rvm::ContractDID*	SimuGlobalShard::_GetContractDeploymentIdentifier(rvm::ContractId contract, rvm::BuildNum version) const
{
	if(version == rvm::BuildNumLatest)
		version = _GetContractEffectiveBuild(contract);

	if(version)
	{
		ContractVersionedId k = { contract, version };

		if(_bDeploying)
		{
			auto* it = _DeployingDatabase._ContractInfo.get(k);
			if(it)return  (const rvm::ContractDID*)&it->DeploymentId;
		}

		auto* it = _ContractInfo.get(k);
		if(it)return (const rvm::ContractDID*)&it->DeploymentId;
	}

	return nullptr;
}

const rvm::InterfaceDID* SimuGlobalShard::_GetInterfaceDeploymentIdentifier(rvm::InterfaceId ifid, rvm::BuildNum version) const
{
	if(version == rvm::BuildNumLatest)
		version = _GetContractEffectiveBuild(rvm::_details::INTERFACE_CONTRACT(ifid));

	if(version)
	{
		ContractVersionedId k = { ifid, version };

		if(_bDeploying)
		{
			auto* it = _DeployingDatabase._ContractInfo.get(k);
			if(it)return  (const rvm::InterfaceDID*)&it->DeploymentId;
		}

		auto* it = _ContractInfo.get(k);
		if(it)return (const rvm::InterfaceDID*)&it->DeploymentId;
	}

	return nullptr;
}

void SimuGlobalShard::DeployBegin(SimuTxn* txn)
{
	ASSERT(!_bDeploying);

	_bDeploying = true;
	_DeployingDatabase.Reset(*this);

	_pTxn = txn;
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
	_pTxn = nullptr;
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

void SimuGlobalShard::CommitNewState(rvm::BuildNum version, rvm::ContractScopeId contract, uint8_t* state)
{
	if(_bDeploying)
	{
		if(state)
		{
			auto* s = (SimuState*)(state - offsetof(SimuState, Data));
			s->Version = version;

			_DeployingStates._ShardStates.Set(contract, s);
		}
		else
		{
			_DeployingStates._ShardStates.Set(contract, nullptr, true);
		}
	}
	else
		SimuShard::CommitNewState(version, contract, state);
}

void SimuGlobalShard::CommitNewState(rvm::BuildNum version, rvm::ContractScopeId contract, const rvm::ScopeKey* key, uint8_t* state)
{
	if(_bDeploying)
	{
		ShardStateKey k = { contract, *key };

		if(state)
		{
			auto* s = (SimuState*)(state - offsetof(SimuState, Data));
			s->Version = version;

			_DeployingStates._ShardKeyedStates.Set(k, s);
		}
		else
		{
			_DeployingStates._ShardKeyedStates.Set(k, nullptr, true);
		}
	}
	else
		SimuShard::CommitNewState(version, contract, key, state);
}

bool SimuGlobalShard::AllocateContractIds(const rvm::CompiledContracts* linked)
{
	ASSERT(_bDeploying);

	rvm::EngineId e = linked->GetEngineId();
	uint32_t count = (uint32_t)linked->GetCount();
	for(uint32_t i=0; i<count; i++)
	{
		auto* c = linked->GetContract(i);
		auto name = c->GetName();
		
		rvm::ContractId cid = _Contracts.get(name.Str(), (rvm::ContractId)0);
		if(cid == (rvm::ContractId)0)
		{
			cid = rvm::_details::CONTRACT_ID_MAKE(_DeployingDatabase._NextContractSN++, _pSimulator->DAPP_ID, e);
			_DeployingDatabase._Contracts[name.Str()] = cid;
			_DeployingDatabase._ContractBuildNumLatest[cid] = BUILD_NUM_INIT;
			_DeployingDatabase._ContractEngine[name.Str()] = e;
			_Contracts[name.Str()] = cid;
		}
		else
		{
			if (_DeployingDatabase._ContractEngine[name.Str()] != e)
			{
				_LOG("[PRD] Contract " << name.Str() << " already deployed with another engine")
				return false;
			}
			_DeployingDatabase._ContractBuildNumLatest[cid] = _ContractBuildNumLatest.get(cid) + 1;
		}
	}

	return true;
}

void SimuGlobalShard::_FinalizeFunctionInfo(const ContractVersionedId& cvid, const rt::String_Ref& func_prefix, const rvm::DeploymentId& deploy_id, const rvm::Interface* c)
{
	auto* info = _New(ContractInfo);

	info->Version = cvid.Version;
	info->DeploymentId = deploy_id;

	for(int i=0; i<256; i++)
		info->ScopeOfOpcode[i] = rvm::Scope::Neutral;

	UINT func_co = c->GetFunctionCount();
	rt::String funcname;
	for(UINT i=0; i<func_co; i++)
	{
		auto opcode = c->GetFunctionOpCode(i);
		info->ScopeOfOpcode[(int)opcode] = c->GetFunctionScope(i);
		funcname = func_prefix + '.' + c->GetFunctionName(i).Str();
		auto& fi = _DeployingDatabase._ContractFunctions[funcname].push_back();
		fi.Contract = cvid.Contract;
		fi.Op = opcode;
		StreamByString ss(fi.FunctionSignature);
		c->GetFunctionSignature(i, &ss);
	}

	_SafeDel_ConstPtr(_DeployingDatabase._ContractInfo.replace(cvid, info));
}


bool SimuGlobalShard::FinalizeDeployment(	const rvm::CompiledContracts* deployed, 
											const rvm::ContractDID* contract_deployment_ids,  // CDID[linked->GetCount()]
											const rvm::InterfaceDID* const * interface_deployment_ids // IDID[linked->GetCount()][#_of_interface_in_each_contract]
										)
{
	ASSERT(_bDeploying);

	rt::String if_prefix;
	uint32_t count = deployed->GetCount();
	for(uint32_t i=0; i<count; i++)
	{
		auto* c = deployed->GetContract(i);
		auto name = c->GetName();

		rvm::ContractId cid = _GetContractByName(_pSimulator->DAPP_ID, &name);
		ASSERT(cid != (rvm::ContractId)0);

		auto version = _GetContractEffectiveBuild(cid);
		ContractVersionedId cvid = { cid, version };

		_FinalizeFunctionInfo(cvid, name.Str(), contract_deployment_ids[i], c);

		const rvm::InterfaceDID* if_dids = interface_deployment_ids[i];
		uint32_t if_count = c->GetInterfaceCount();
		for(uint32_t q=0; q<if_count; q++)
		{
			auto* if_info = c->GetInterface(q);
			cvid.Interface = rvm::_details::INTERFACE_ID_MAKE(c->GetInterfaceSlot(q), cid);

			if_prefix = name.Str() + rt::SS("::") + if_info->GetName().Str();
			_FinalizeFunctionInfo(cvid, if_prefix, if_dids[q], if_info);
		}
	}

	return true;
}

rvm::ContractId	SimuGlobalShard::_GetContractByName(rvm::DAppId dapp_id, const rvm::ConstString* contract_name) const
{
	ASSERT(_pSimulator->DAPP_ID == dapp_id);

	if(_bDeploying)
	{
		auto r = _DeployingDatabase._Contracts.get(contract_name->Str(), (rvm::ContractId)0);
		if(r != (rvm::ContractId)0)
			return r;
	}

	return _Contracts.get(contract_name->Str(), (rvm::ContractId)0);
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
	_ContractDeploymentIds.ShrinkSize(0);
	_InterfaceDeploymentIds.ShrinkSize(0);
}

void BuildContracts::AddSource(const rt::String_Ref& code, const rt::String_Ref& fn)
{
	ASSERT(_Stage == STAGE_SOURCE);

	_Sources.push_back(code);
	_Filenames.push_back(fn);
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

bool BuildContracts::Compile(const rvm::ChainState* global_state)
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

	for (UINT i = 0; i < count; i++)
		codes[i] = { (uint8_t*)_Sources[i].Begin(), (uint32_t)_Sources[i].GetLength() };

	_Stage = STAGE_COMPILE;
	_LOG("Compiling " << count << " contract(s), target=" << rt::EnumStringify(_EngineId));

	rvm::CompilationFlag cflag = rvm::CompilationFlag::None;
	if(os::CommandLine::Get().HasOption("perftest"))
		cflag |= rvm::CompilationFlag::DisableDebugPrint;

	rvm::ConstString dapp = { _DAppName.Begin(), (uint32_t)_DAppName.GetLength() };
	if (_pEngine->Compile(global_state, &dapp, count, codes, cflag, &_pCompiled, &_CompileDependency, this) && _pCompiled && _pCompiled->GetCount() == count)
	{
		for (uint32_t i = 0; i < count; i++)
		{
			if (_EngineId == rvm::EngineId::SOLIDITY_EVM)
			{
				rt::JsonObject sol_json(_Sources[0]);
				_ContractToFN[sol_json.GetValue("entryContract")] = sol_json.GetValue("entryFile");
			}
			else
			{
				rvm::ConstString contractCS = _pCompiled->GetContract(i)->GetName();
				rt::String tmp = _Filenames[i];
				int64_t slashPos = rt::max(tmp.FindCharacterReverse('\\'), tmp.FindCharacterReverse('/'));
				if (slashPos >= 0)
				{
					tmp = tmp.SubStr(slashPos + 1);
				}
				_ContractToFN[contractCS.Str()] = tmp;
			}
		}
		return true;
	}
	
	_LOG_WARNING("[PRD]: Compile failed");
	_SafeRelease(_pCompiled);

	_Stage = STAGE_SOURCE;
	_Sources.ShrinkSize(0);
	_Filenames.ShrinkSize(0);
	_CompileDependency.Empty();
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
	_LOG("Linking " << count << " contract(s), target=" << rt::EnumStringify(_EngineId));

	ASSERT(_pEngine);
	if(_pEngine->Link(_pCompiled, this))
		return true;

	_LOG_WARNING("[PRD]: Link failed");

	_Stage = STAGE_COMPILE;
	return false;
}

bool BuildContracts::VerifyDependency(const rvm::ChainState* global_state) const
{
	uint32_t count = (uint32_t)_Sources.GetSize();
	if(!count)return true;

	ASSERT(_Stage >= STAGE_COMPILE);
	ASSERT(_pCompiled);

	ASSERT(_pEngine);

	auto dep_data = _CompileDependency.GetRvmConstData();
	return _pEngine->ValidateDependency(global_state, _pCompiled, &dep_data);
}

bool BuildContracts::Deploy(rvm::ExecuteUnit* exec, rvm::ExecutionContext* exec_ctx, uint32_t gas_limit)
{
	uint32_t count = (uint32_t)_Sources.GetSize();
	if(!count)return false;

	ASSERT(_Stage == STAGE_LINK);
	ASSERT(_pCompiled);
	ASSERT(_pCompiled->IsLinked());
	ASSERT(count == _pCompiled->GetCount());

	_ContractDeploymentIds.SetSize(count);
	_InterfaceDeploymentIds.SetSize(count);
	_InterfaceDeploymentIds.Zero();

	for(uint32_t i=0; i<count; i++)
	{
		auto* c = _pCompiled->GetContract(i);
		uint32_t if_count = c->GetInterfaceCount();
		if(if_count)
			_InterfaceDeploymentIds[i] = _Malloc8AL(rvm::InterfaceDID, if_count);
	}

	_Stage = STAGE_DEPLOY;

	if(exec->Deploy(exec_ctx, gas_limit, _pCompiled, _ContractDeploymentIds, _InterfaceDeploymentIds, this).Code == rvm::InvokeErrorCode::Success)
		return true;

	_ContractDeploymentIds.ShrinkSize(0);
	_InterfaceDeploymentIds.ShrinkSize(0);
	_Stage = STAGE_LINK;
	return false;
}

void getVarNameType(const rt::String_Ref* varArr, uint32_t& idx, rt::String& varName, rt::String& varType, uint32_t size)
{
	rt::String_Ref curType = varArr[idx++];
	if (curType == "array" && idx + 2 <= size)
	{
		varType = "array (" + varArr[idx++] + ")";
		varName = varArr[idx++];
	}
	else if (curType == "map" && idx + 3 <= size)
	{
		varType = "map (" + varArr[idx++] + " : ";
		varType += varArr[idx++] + ")";
		varName = varArr[idx++];
	}
	else
	{
		varType = curType;
		varName = varArr[idx++];
	}
}

void ConvertSigToJson(rt::Json& json, const rt::String& name, const rt::String& sig, bool structSig)
{
	//stateSig example
	//struct 6 address controller uint32 current_case array chsimu.Ballot.Proposal proposals chsimu.Ballot.BallotResult last_result map int32 chsimu.Ballot.BallotResult test uint32 shardGatherRatio
	//sturct [number of var] [var #0's member data type] (inner data type if array or map) [var #0's member identifier] [var #1's member data type] [var #1's member identifier] 
	rt::String_Ref var[1024];
	uint32_t co = sig.Split<true>(var, sizeofArray(var), " ");
	if (co < 2)return;
	int32_t numMember = var[1].ToNumber<int32_t>();
	for (uint32_t i = 2; i < co; )
	{
		if (structSig)
		{
			auto s = json.ScopeAppendingElement();
			json.Object(J(name)=name);
			auto ss = json.ScopeAppendingKey("layout");
			json.Array();
			for (int32_t j = 0; j < numMember; j++)
			{
				rt::String varName, varType;
				getVarNameType(var, i, varName, varType, co);
				auto sss = json.ScopeAppendingElement();
				json.Object((J(identifier) = varName, J(dataType) = varType));
			}
		}
		else
		{
			for (int32_t j = 0; j < numMember; j++)
			{
				rt::String varName, varType;
				getVarNameType(var, i, varName, varType, co);
				auto sss = json.ScopeAppendingElement();
				json.Object((J(name) = varName, J(scope) = name, J(dataType) = varType));
			}
		}
	}
}

void BuildContracts::GetContractsInfo(rt::Json& json, const rvm::ChainState* global_state) const
{
	ASSERT(_Stage >= STAGE_COMPILE);
	ASSERT(_pCompiled);
	ASSERT(global_state);
	uint32_t count = _pCompiled->GetCount();
	for(uint32_t i=0; i<count; i++)
	{
		auto contract_scope = json.ScopeAppendingElement();
		auto* contract = _pCompiled->GetContract(i);
		auto name = contract->GetName();
		auto flag = contract->GetFlag();
		rt::String fn = _ContractToFN.get(name.Str());
		json.Object((
			J(contract) = name.Str(),
			J(source) = fn,
			J(engine) = rt::EnumStringify(_EngineId),
			J(hash) = rt::tos::Base32CrockfordLowercaseOnStack<>(*contract->GetIntermediateRepresentationHash()),
			J(finalized) = (bool)(flag&rvm::ContractFlag::DeployFinalized)
		));

		{	// interface implemented
			auto scpdef_scope = json.ScopeAppendingKey("implments");
			json.Array();

			rvm::InterfaceId ifid[256];
			uint32_t if_count = contract->GetInterfaceImplemented(ifid, sizeofArray(ifid));
			for(uint32_t i=0; i<if_count; i++)
			{
				auto* if_did = global_state->GetInterfaceDeploymentIdentifier(ifid[i]);
				const rvm::Interface* ifc;
				if(if_did && (ifc = _pEngine->GetInterface(if_did)))
				{
					json.AppendElement(ifc->GetName().Str());
				}
				else
				{	
					json.AppendElement(rt::SS("(IID:0x") + rt::tos::HexNum(ifid[i]) + ')');
				}
			}
		}

		ext::fast_map<uint32_t, rt::String> scope_names(0x80000001, 0x80000002);		
		bool has_scattered_maps = false;
		uint32_t scope_count = contract->GetScopeCount();
		{
			auto stateVar_scope = json.ScopeAppendingKey("stateVariables");
			json.Array();
			for (uint32_t s = 0; s < scope_count; s++)
			{
				auto scope = contract->GetScope(s);
				rt::String tmp;
				StreamByString stateSig(tmp);
				contract->GetStateSignature(scope, (rvm::StringStream*)&stateSig);
				rt::String scopeName = contract->GetScopeName(s).Str();
				ConvertSigToJson(json, scopeName, tmp, false);
			}
		}

		{	// scope definitions
			auto scpdef_scope = json.ScopeAppendingKey("scopes");
			json.Object();

			// involved scopes
			uint32_t scope_count = contract->GetScopeCount();
			for(uint32_t s=0; s<scope_count; s++)
			{
				auto scope = contract->GetScope(s);
				if(rvm::_details::SCOPE_TYPE(scope) == rvm::ScopeType::Contract)
				{
					auto scope_name = contract->GetScopeName(s);
					scope_names[(uint32_t)scope] = scope_name.Str();

					auto flag = contract->GetScopeFlag(s);
					if(scope <= rvm::Scope::Address && flag == (rvm::ScopeDefinitionFlag)0)
						continue;

					json.AppendKey(scope_name.Str(), rt::EnumStringify(flag));
				}
				else has_scattered_maps = true;
			}
		}

		{	// scattered maps
			auto scpdef_scope = json.ScopeAppendingKey("scatteredMaps");
			json.Object();
			if(has_scattered_maps)
			{
				uint32_t scope_count = contract->GetScopeCount();
				for(uint32_t s=0; s<scope_count; s++)
				{
					auto scope = contract->GetScope(s);
					if(rvm::_details::SCOPE_TYPE(scope) > rvm::ScopeType::Contract)
					{
						rt::String_Ref prefix = 
							(rvm::_details::SCOPE_TYPE(scope) > rvm::ScopeType::ScatteredMapOnGlobal)?"Shard":"Global";

						auto scope_name = contract->GetScopeName(s);
						json.AppendKey(scope_name.Str(), prefix + rt::SS("Map:") + rt::EnumStringify(rvm::_details::SCOPE_KEYSIZETYPE(scope)));
					}
				}
			}
		}

		{
			auto struct_scope = json.ScopeAppendingKey("structs");
			json.Array();
			uint32_t struct_count = contract->GetStructCount();
			for (uint32_t i = 0; i < struct_count; i++)
			{
				rt::String tmp;
				StreamByString structSig(tmp);
				contract->GetStructSignature(i, (rvm::StringStream*)&structSig);
				rvm::ConstString str = contract->GetStructName(i);
				rt::String structName(str.Str());
				ConvertSigToJson(json, structName, tmp, true);
			}
		}

		{	// enum
			auto enum_scope = json.ScopeAppendingKey("enumerables");
			json.Array();
			uint32_t enum_count = contract->GetEnumCount();
			for (uint32_t i = 0; i < enum_count; i++)
			{
				auto s = json.ScopeAppendingElement();
				json.Object((J(name) = contract->GetEnumName(i).Str()));
				auto enum_scope = json.ScopeAppendingKey("value");
				rt::String tmp;
				StreamByString structSig(tmp);
				contract->GetEnumSignature(i, (rvm::StringStream*)&structSig);
				rt::String_Ref enumator[1024];
				uint32_t co = tmp.Split<true>(enumator, sizeofArray(enumator), ",");
				json.Array();
				for (uint32_t i = 0; i < co; i++)
				{
					json.AppendElement(enumator[i]);
				}
			}
		}

		auto json_if = [&scope_names](const rvm::Interface* ifc, rt::Json& json){
			uint32_t func_count = ifc->GetFunctionCount();
			json.Array();
			for(uint32_t i=0; i<func_count; i++)
			{
				auto arr_scope = json.ScopeAppendingElement();
				auto scope = ifc->GetFunctionScope(i);
				auto op = ifc->GetFunctionOpCode(i);
				auto flag = ifc->GetFunctionFlag(i);
				json.Object(((J(name) = ifc->GetFunctionName(i).Str()), (J(flag) = rt::EnumStringify(flag)), (J(scope) = scope_names[(uint32_t)scope]), (J(opcode) = (int)op)));
			}
		};

		{	// interfaces
			auto if_scope = json.ScopeAppendingKey("interfaces");
			json.Object();
			uint32_t if_count = contract->GetInterfaceCount();
			for(uint32_t i=0; i<if_count; i++)
			{
				auto* ifc = contract->GetInterface(i);
				auto func_scope = json.ScopeAppendingKey(ifc->GetName().Str());
				json.Object((
					J(Slot) = (int)contract->GetInterfaceSlot(i)
				));
				json_if(ifc, json);
			}
		}

		{	// functions
			auto if_scope = json.ScopeAppendingKey("functions");
			json_if(contract, json);
		}
	}
}

}