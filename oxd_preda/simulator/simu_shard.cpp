#include "simu_global.h"
#include "simulator.h"


namespace oxd
{

void ShardStates::Revert()
{
	_ShardStates.Empty();
	_ShardKeyedStates.Empty();
}

void ShardStates::Commit(ShardStates& to)
{
	_ShardStates.Commit(to._ShardStates);
	_ShardKeyedStates.Commit(to._ShardKeyedStates);
}

SimuShard::SimuShard(Simulator* simu, uint64_t time_base, uint32_t shard_order)
	:_TxnEmitted(simu, this)
{
	_pSimulator = simu;
	_pGlobalShard = nullptr;

	_BlockTimeBase = time_base;
	_ShardIndex = rvm::GlobalShard;
	_ShardOrder = shard_order;
	_GoNextBlock.Reset();
	rt::Zero(_PrevBlockHash);
}

SimuShard::SimuShard(Simulator* simu, uint64_t time_base, uint32_t shard_order, uint32_t shard_index, SimuGlobalShard* global)
	:SimuShard(simu, time_base, shard_order)
{
	_pGlobalShard = global;
	_ShardIndex = shard_index;
}

rvm::ScopeKey SimuShard::GetScopeTarget() const
{
	rvm::Scope scope = _GetScope();
	if (scope == rvm::Scope::Global || scope == rvm::Scope::Shard)
		return { nullptr, 0 };

	return { (uint8_t*)&_pTxn->Target, _pTxn->Target.target_size };
}

rvm::ConstStateData SimuShard::GetState(rvm::ContractScopeId contract, const rvm::ScopeKey* key) const
{
	auto scope = rvm::_details::CONTRACT_SCOPE(contract);
	auto scope_type = rvm::_details::SCOPE_TYPE(scope);

	ASSERT(scope_type != rvm::ScopeType::Contract);

	ShardStateKey k = { contract, *key };
	const SimuState* ret = _ShardKeyedStates.Get(k);
	if(ret)return { ret->Data, ret->DataSize, ret->Version };
	else return { nullptr, 0, (rvm::BuildNum)0 };
}

rvm::ConstStateData	SimuShard::GetState(rvm::ContractScopeId cid) const
{
	const SimuState* ret = nullptr;
	auto scope = rvm::_details::CONTRACT_SCOPE(cid);

	switch(scope)
	{
	case rvm::Scope::Address:
	case rvm::Scope::UInt16:
	case rvm::Scope::UInt32:
	case rvm::Scope::UInt64:
	case rvm::Scope::UInt256:
	case rvm::Scope::UInt512:
		if(IsGlobal())goto EMPTY_STATE;
		if(_GetScope() == scope)
		{
			SimuAddressContract k{ _pTxn->Target, cid };
			ret = _AddressStates.Get(k);
		}
		break;
	case rvm::Scope::Shard:
		{
			if(IsGlobal())goto EMPTY_STATE;
			ret = _ShardStates.Get(cid);
		}
		break;
	case rvm::Scope::Global:
		{
			ret = IsGlobal()?_ShardStates.Get(cid):
							 _pGlobalShard->_ShardStates.Get(cid);
		}
		break;
	default: ASSERT(0);
		break;
	}

	if(ret)
		return { ret->Data, ret->DataSize, ret->Version };

EMPTY_STATE:
	return { nullptr, 0, (rvm::BuildNum)0 };
}

uint8_t* SimuShard::AllocateStateMemory(uint32_t dataSize)
{
	auto* s = SimuState::Create(dataSize);
	return s?s->Data:nullptr;
}

void SimuShard::DiscardStateMemory(uint8_t* state)
{
	_SafeFree8AL_ConstPtr(state - offsetof(SimuState, Data));
}

void SimuShard::CommitNewState(rvm::BuildNum build_num, rvm::ContractScopeId contract, const rvm::ScopeKey* key, uint8_t* state)
{
	auto scope = rvm::_details::CONTRACT_SCOPE(contract);
	auto scope_type = rvm::_details::SCOPE_TYPE(scope);

	ASSERT(scope_type != rvm::ScopeType::Contract);

	auto* s = (SimuState*)(state - offsetof(SimuState, Data));
	s->Version = build_num;
	ShardStateKey k = { contract, *key };

	_ShardKeyedStates.Set(k, s);
}

void SimuShard::CommitNewState(rvm::BuildNum build_num, rvm::ContractScopeId cid, uint8_t* state)
{
	auto* s = (SimuState*)(state - offsetof(SimuState, Data));
	s->Version = build_num;

	auto scope = rvm::_details::CONTRACT_SCOPE(cid);
	switch (scope)
	{
	case rvm::Scope::Address:
	case rvm::Scope::UInt16:
	case rvm::Scope::UInt32:
	case rvm::Scope::UInt64:
	case rvm::Scope::UInt256:
	case rvm::Scope::UInt512:
		{
			ASSERT(!_IsGlobalScope());
			ASSERT(_GetScope() == scope);

			SimuAddressContract k = { _pTxn->Target, cid };
			_AddressStates.Set(k, s);
		}
		break;
	case rvm::Scope::Shard:
		ASSERT(!_IsGlobalScope());
		ASSERT(!IsGlobal());
		_ShardStates.Set(cid, s);
		break;
	case rvm::Scope::Global:
		ASSERT(_IsGlobalScope());
		ASSERT(IsGlobal());
		_ShardStates.Set(cid, s);
		break;
	default:
		ASSERT(0);
	}
}

rvm::ConstAddress* SimuShard::GetBlockCreator() const
{
	return &_pSimulator->GetMiner();
}

SimuTxn* SimuShard::_CreateRelayTxn(rvm::ContractId cid, rvm::OpCode opcode, const rvm::ConstData* args_serialized, rvm::BuildNum build_num) const
{
	auto scope = _pSimulator->PrepareTxn(cid, opcode, build_num);
	if(scope == rvm::Scope::Neutral)return nullptr;

	auto* txn = SimuTxn::Create(args_serialized?(uint32_t)args_serialized->DataSize:0U);
	txn->Type = rvm::InvokeContextType::RelayInbound;
	txn->Contract = rvm::_details::CONTRACT_SET_SCOPE(cid, scope);
	txn->Op = opcode;
	txn->BuildNum = build_num;
	txn->Timestamp = _GetBlockTime();
	txn->Flag = TXN_RELAY;
	txn->OriginateHeight = _BlockHeight;
	txn->OriginateShardIndex = _ShardIndex;
	txn->OriginateShardOrder = _ShardOrder;

	ASSERT(txn->ArgsSerializedSize == args_serialized->DataSize);
	memcpy(txn->ArgsSerializedData, args_serialized->DataPtr, args_serialized->DataSize);

	return txn;
}

bool SimuShard::EmitRelayToScope(rvm::BuildNum build_num, const uint8_t* scope_key, uint32_t scope_key_size, rvm::ContractScopeId cid, rvm::OpCode opcode, const rvm::ConstData* args_serialized, uint32_t gas_redistribution_weight)
{
	auto* txn = _CreateRelayTxn(rvm::_details::CONTRACT_UNSET_SCOPE(cid), opcode, args_serialized, build_num);
	ASSERT(txn->Contract == cid);
	rvm::Scope scope = rvm::_details::CONTRACT_SCOPE(cid);
	switch (scope)
	{
	case rvm::Scope::Address:
		ASSERT(scope_key_size == sizeof(rvm::ConstAddress));
		txn->Target = ScopeTarget(*(rvm::ConstAddress *)scope_key);
		break;
	case rvm::Scope::UInt16:
		ASSERT(scope_key_size == sizeof(uint16_t));
		txn->Target = ScopeTarget(*(uint16_t*)scope_key);
		break;
	case rvm::Scope::UInt32:
		ASSERT(scope_key_size == sizeof(uint32_t));
		txn->Target = ScopeTarget(*(uint32_t*)scope_key);
		break;
	case rvm::Scope::UInt64:
		ASSERT(scope_key_size == sizeof(uint64_t));
		txn->Target = ScopeTarget(*(uint64_t*)scope_key);
		break;
	case rvm::Scope::UInt256:
		ASSERT(scope_key_size == 32);
		txn->Target = ScopeTarget(*(std::array<uint8_t, 32>*)scope_key);
		break;
	case rvm::Scope::UInt512:
		ASSERT(scope_key_size == 64);
		txn->Target = ScopeTarget(*(std::array<uint8_t, 64>*)scope_key);
		break;
	default:
		break;
	}
	txn->Initiator = _pTxn->IsRelay()?_pTxn->Initiator:_pTxn->Target.addr;

	_RelayEmitted.push_back(txn);
	return true;
}

bool SimuShard::EmitRelayToGlobal(rvm::BuildNum build_num, rvm::ContractScopeId cid, rvm::OpCode opcode, const rvm::ConstData* args_serialized, uint32_t gas_redistribution_weight)
{
	auto* txn = _CreateRelayTxn(rvm::_details::CONTRACT_UNSET_SCOPE(cid), opcode, args_serialized, build_num);

	rt::Zero(txn->Target);
	txn->Initiator = _pTxn->IsRelay()?_pTxn->Initiator:_pTxn->Target.addr;

	_RelayEmitted.push_back(txn);
	return true;
}

bool SimuShard::EmitBroadcastToShards(rvm::BuildNum build_num, rvm::ContractScopeId cid, rvm::OpCode opcode, const rvm::ConstData* args_serialized, uint32_t gas_redistribution_weight)
{
	auto* txn = _CreateRelayTxn(rvm::_details::CONTRACT_UNSET_SCOPE(cid), opcode, args_serialized, build_num);

	txn->Flag = (SimuTxnFlag)(txn->Flag|TXN_BROADCAST);
	rt::Zero(txn->Target);
	txn->Initiator = _pTxn->IsRelay()?_pTxn->Initiator:_pTxn->Target.addr;
	if(rvm::_details::CONTRACT_SCOPE(_pTxn->Contract) == rvm::Scope::Global)
	{
		txn->Type = rvm::InvokeContextType::Scheduled; // Global to Shards 
	}

	_RelayEmitted.push_back(txn);
	return true;
}

rvm::ContractId SimuShard::GetContractByName(rvm::DAppId dapp_id, const rvm::ConstString* contract_name) const
{
	return _pGlobalShard->_GetContractByName(dapp_id, contract_name);
}

rvm::DAppId	SimuShard::GetDAppByName(const rvm::ConstString* dapp_name) const
{
	return _pSimulator->DAPP_ID;
}

rvm::BuildNum SimuShard::GetContractEffectiveBuild(rvm::ContractId contract) const
{
	return _pGlobalShard->_GetContractEffectiveBuild(contract);
}

const rvm::ContractDID* SimuShard::GetContractDeploymentIdentifier(rvm::ContractId contract, rvm::BuildNum version) const
{
	return _pGlobalShard->_GetContractDeploymentIdentifier(contract, version);
}

const rvm::InterfaceDID* SimuShard::GetInterfaceDeploymentIdentifier(rvm::InterfaceId contract) const
{
	return _pGlobalShard->_GetInterfaceDeploymentIdentifier(contract);
}

rvm::ExecuteResult SimuShard::Invoke(uint32_t gas_limit, rvm::BuildNum build_num, rvm::ContractScopeId contract, rvm::OpCode opcode, const rvm::ConstData* args_serialized)
{
	rvm::ExecuteResult ret;
	rt::Zero(ret);
	ret.Code = rvm::InvokeErrorCode::ContractUnavailable;

	return ret;
}

void SimuShard::SetReturnValue(const rvm::ConstData* args_serialized)
{
	auto* d = SetReturnValueClaim((uint32_t)args_serialized->DataSize);
	ASSERT(d);

	memcpy(d, args_serialized->DataPtr, (uint32_t)args_serialized->DataSize);
	SetReturnValueFinalize((uint32_t)args_serialized->DataSize);
}

void SimuShard::Init()
{
	rt::Zero(_BlockHash);
	rt::Zero(_PrevBlockHash);
	_BlockTimeBase = os::Timestamp::Get();
	_BlockHeight = 0;
	_ConfirmedTxnCount = 0;

	_pSimulator->CreateExecuteUnit(&_ExecUnits);

	_GoNextBlock.Reset();
	_BlockCreator.Create([this](){ _BlockCreationRoutine(); });
}

void SimuShard::Term()
{
	if(_BlockCreator.IsRunning())
	{
		_BlockCreator.WantExit() = true;
		_GoNextBlock.Set();
		_BlockCreator.WaitForEnding();
	}

	for(auto b : _Chain)
		b->Release();

	_Chain.ShrinkSize(0);
}

void SimuShard::SetState(rvm::ContractId cid, rvm::Scope scope, SimuState* s)
{
	ASSERT(	(scope == rvm::Scope::Global && IsGlobal()) ||
			(scope == rvm::Scope::Shard && !IsGlobal())
	);

	_ShardStates.Set(rvm::_details::CONTRACT_SET_SCOPE(cid, scope), s);
}

void SimuShard::SetState(rvm::ContractId cid, rvm::Scope scope, const rvm::Address& target, SimuState* s)
{
	ASSERT(scope == rvm::Scope::Address);
	ASSERT(_pSimulator->GetShardIndex(target) == _ShardIndex);

	_AddressStates.Set({ ScopeTarget(target), rvm::_details::CONTRACT_SET_SCOPE(cid, scope) }, s);
}

void SimuShard::PushTxn(SimuTxn* t)
{
	bool first_item = (t->IsRelay()?_PendingRelayTxns:_PendingTxns).Push(t);
	_pSimulator->OnTxnPushed();

	if(first_item && _pSimulator->IsShardingAsync() && !_pSimulator->IsChainPaused() && !_pSimulator->IsChainStepping())
		_GoNextBlock.Set();
}

void SimuShard::PushTxn(SimuTxn** txns, uint32_t count)
{
	if(count)
	{
		ASSERT(txns[0]->IsRelay());

		bool first_item = _PendingTxns.Push(txns, count);
		_pSimulator->OnTxnPushed(count);

		if(first_item && _pSimulator->IsShardingAsync() && !_pSimulator->IsChainPaused() && !_pSimulator->IsChainStepping())
			_GoNextBlock.Set();
	}
}

RelayEmission::RelayEmission(Simulator* s, SimuShard* shard)
	:_pSimulator(s),_pShard(shard)
{
	_ToShards.SetSize(s->GetShardCount());
}

RelayEmission::~RelayEmission()
{
	auto rel = [](rt::BufferEx<SimuTxn*>& txns)
	{
		for(auto t : txns)t->Release();
		txns.SetSize(0);
	};

	rel(_ToGlobal);
	for(auto& s : _ToShards)rel(s);

	_ToShards.SetSize(0);
}

void RelayEmission::Collect(SimuTxn* origin, rt::BufferEx<SimuTxn*>& txns)
{
	for(SimuTxn* t : txns)
	{
		ASSERT(t->IsRelay());

		switch(t->GetScope())
		{
		case rvm::Scope::Global:
			_ToGlobal.push_back(t);
#ifdef _VIZ
			_pShard->AppendToTxnTrace(origin, t);
#endif
			break;
		case rvm::Scope::Shard:
			for (uint32_t i = 1; i < _ToShards.GetSize(); i++)
			{
				SimuTxn* _clone = t->Clone();
				_ToShards[i].push_back(_clone);
#ifdef _VIZ
				_pShard->AppendToTxnTrace(origin, _clone);
#endif
			}
			_ToShards[0].push_back(t);
#ifdef _VIZ
			_pShard->AppendToTxnTrace(origin, t);
#endif
			break;
		case rvm::Scope::Address:
			{
				uint32_t si = _pSimulator->GetShardIndex(t->Target.addr);
				_ToShards[si].push_back(t);
#ifdef _VIZ
				_pShard->AppendToTxnTrace(origin, t);
#endif
			}
			break;
		case rvm::Scope::UInt16:
		case rvm::Scope::UInt32:
		case rvm::Scope::UInt64:
		case rvm::Scope::UInt256:
		case rvm::Scope::UInt512:
		{
			uint32_t si = _pSimulator->GetShardIndex(t->Target);
			_ToShards[si].push_back(t);
#ifdef _VIZ
			_pShard->AppendToTxnTrace(origin, t);
#endif
		}
		break;

		default:
			ASSERT(0);
		}
	}

	txns.ShrinkSize(0);
}

void RelayEmission::Dispatch()
{
	if(_ToGlobal.GetSize())
	{
		_pSimulator->GetGlobalShard()->PushTxn(_ToGlobal, (uint32_t)_ToGlobal.GetSize());
		_ToGlobal.ShrinkSize(0);
	}

	for(uint32_t i=0; i<_ToShards.GetSize(); i++)
	{
		auto& txns = _ToShards[i];
		if(txns.GetSize())
		{
			_pSimulator->GetShard(i)->PushTxn(txns, (uint32_t)txns.GetSize());
			txns.ShrinkSize(0);
		}
	}
}
#ifdef _VIZ

void SimuShard::AppendToTxnTrace(SimuTxn* origin, SimuTxn* relay)
{
	rt::BufferEx<SimuTxn*> tmp;
	if(_TxnTrace.has(origin))
		tmp = _TxnTrace.get(origin);

	tmp.push_back(relay);
	_TxnTrace[origin] = tmp;
}

const rt::BufferEx<SimuTxn*> SimuShard::GetTxnTrace(SimuTxn* txn) const
{
	if(_TxnTrace.has(txn))
		return _TxnTrace.get(txn);
	else
		return rt::BufferEx<SimuTxn*>();
}
#endif

void SimuShard::_BlockCreationRoutine()
{
	while(!_BlockCreator.WantExit())
	{
		bool step = _pSimulator->IsChainStepping();
		bool async = _pSimulator->IsShardingAsync() && !IsGlobal();

		if(	!async || step || _pSimulator->IsChainPaused() ||
			(_PendingRelayTxns.IsEmpty() && _PendingTxns.IsEmpty())
		)
		{	_GoNextBlock.WaitSignal();
			_GoNextBlock.Reset();
		}

		if(_BlockCreator.WantExit())return;

		step = _pSimulator->IsChainStepping();
		uint64_t gas_limit  =_pSimulator->GetScriptGasLimit();

		// start a new block
		_TotalGasBurnt = 0;
		_PrevBlockHash = _BlockHash;
		ASSERT(_TxnExecuted.GetSize() == 0);

		// collecting txns
		while(_TotalGasBurnt < gas_limit)
		{
			auto* t = _PendingRelayTxns.Pop(); // confirm relay first
			if(t == nullptr)t = _PendingTxns.Pop();
			if(t == nullptr)break; // mempool empty

			ASSERT(_RelayEmitted.GetSize() == 0);

			// execute a txn
			_pTxn = t;
			rvm::ConstData args = { _pTxn->ArgsSerializedData, _pTxn->ArgsSerializedSize };

			rvm::InvokeResult ret;
			auto* pexec = _ExecUnits.Get(_pTxn->GetEngineId());
			if(pexec)
			{
				const rvm::ContractDID* contract_deployment_id = GetContractDeploymentIdentifier(rvm::_details::CONTRACT_UNSET_SCOPE(_pTxn->Contract), _pTxn->BuildNum);
				ret = pexec->Invoke(this, 0xffffffffU, contract_deployment_id, _pTxn->Op, &args);
				if((int)ret.Code > 0)
				{
					if ((int)ret.SubCodeLow > 0) {
						rt::String tmp("");
						StreamByString str(tmp);
						pexec->GetExceptionMessage(ret.SubCodeLow, &str);
						_LOG_WARNING("[PRD]: Engine invoke error. Error Message: " << rt::EnumStringify(ret.Code) << " (" << str.GetString().Str() << ")");
					}
					else
						_LOG_WARNING("[PRD]: Engine invoke error. Error Message: " << rt::EnumStringify(ret.Code));
				}
			}
			else
			{
				rt::Zero(ret);
				ret.Code = rvm::InvokeErrorCode::ExecutionEngineUnavailable;
				_LOG_WARNING("[PRD]: Engine "<<rt::EnumStringify(_pTxn->GetEngineId())<<" is not available");
			}

			_TxnExecuted.push_back({ _pTxn, ret.GasBurnt, ret });
			_TotalGasBurnt += ret.GasBurnt;

			_pTxn->Height = _BlockHeight;
			_pTxn->ShardIndex = _ShardIndex;
			_pTxn->ShardOrder = _ShardOrder;

			if(_RelayEmitted.GetSize())
				_TxnEmitted.Collect(t, _RelayEmitted);
		}

		// finalize a block
		auto* block = SimuBlock::Create((uint32_t)_TxnExecuted.GetSize());
		block->Height = _BlockHeight;
		block->PrevBlock = _PrevBlockHash;
		block->Timestamp = _GetBlockTime();
		block->Miner = _pSimulator->GetMiner();
		block->TxnCount = (uint32_t)_TxnExecuted.GetSize();
		_TxnExecuted.CopyTo(block->Txns);
		*(uint64_t*)&_BlockHash = os::crc64(block, offsetof(SimuBlock, Txns));
		block->TotalGas = _TotalGasBurnt;
		_Chain.push_back(block);

		//_LOG_HIGHLIGHT("[PRD]: Block#"<<ShardIndexString(_ShardIndex)<<"-h"<<_BlockHeight<<": txn:"<<block->TxnCount<<" emit:"<<_RelayEmitted.GetSize());

		// dispatch relay
		_TxnEmitted.Dispatch();

		// clean up
		_ConfirmedTxnCount += (uint32_t)_TxnExecuted.GetSize();
		if(_TxnExecuted.GetSize())
		{
			_pSimulator->OnTxnsConfirmed((uint32_t)_TxnExecuted.GetSize());
			_TxnExecuted.ShrinkSize(0);
		}
		_ReturnVal.ShrinkSize(0);
		_BlockHeight++;

		// continue to next block
		if(IsGlobal())
		{	// trigger all shards
			ASSERT(!async);
			for(uint32_t i=0; i<_pSimulator->GetShardCount(); i++)
				_pSimulator->GetShard(i)->Step();
		}
		else
		{
			if(!async)
			{
				bool trigger_global = _pSimulator->CompleteShardExecution();
				if(trigger_global)
				{
					if(_pSimulator->GetPendingTxnCount() && !step && !_pSimulator->IsChainPaused())
						_pGlobalShard->Step();
				}
			}
			else{
				if (_pSimulator->GetPendingTxnCount() && !step && !_pSimulator->IsChainPaused())
					_pGlobalShard->Step();
			}
		}
	}
}

void SimuShard::LogInfo()
{
	rt::tos::Number gi(_ShardIndex);
	if(IsGlobal())(rt::String_Ref&)gi = "g";

	_LOG(	"Shd#"<<gi<<":\t"<<
			"h:"<<_BlockHeight<<" "
			"txn:"<<_PendingTxns.GetSize()<<'/'<<_PendingRelayTxns.GetSize()<<'/'<<_ConfirmedTxnCount<<" "
			"addr:"<<_AddressStates.GetSize()
	);
}

void SimuShard::Step()
{
	_GoNextBlock.Set();
}
#ifdef _VIZ
bool SimuShard::JsonifyBlocks(rt::Json& append, int64_t height)
{
	if(!_Chain.GetSize() || height >= (int)_Chain.GetSize())
	{
		_LOG("[PRD] Line " << _pSimulator->GetLineNum() << ": block index is out of range")
		return false;
	}
	uint64_t starting_idx = height < 0 ? 0 : height;
	uint64_t ending_idx = height < 0 ? _Chain.GetSize() : height + 1;
	rt::String shard_index = IsGlobal()? "#g" : rt::String("#") + GetShardIndex();
	for(;starting_idx < ending_idx; starting_idx++)
	{
		auto s1 = append.ScopeAppendingElement();
		SimuBlock* blk = _Chain[starting_idx];
		rt::String prev_blk_hash;
		prev_blk_hash.SetLength(os::Base32EncodeLength(RVM_HASH_SIZE));
		os::Base32CrockfordEncodeLowercase(prev_blk_hash.Begin(), &blk->PrevBlock, RVM_HASH_SIZE);
		char miner_buf[rvm::_details::ADDRESS_BASE32_LEN];
		rvm::_details::ADDRESS_TO_STRING(blk->Miner, miner_buf);
		append.Object((
			(J(Height) = blk->Height),
			(J(PrevBlock) = prev_blk_hash),
			(J(ShardIndex) = shard_index),
			(J(Timestamp) = blk->Timestamp),
			(J(Miner) = rt::String(miner_buf, rvm::_details::ADDRESS_BASE32_LEN) + rt::SS(":") + oxd::SecuritySuite::IdToString(blk->Miner._SSID)),
			(J(TxnCount) = blk->TxnCount)
		));
		if(blk->TxnCount > 0)
		{
			auto s2 = append.ScopeAppendingKey("ConfirmTxn");
			append.Array();
			for(uint32_t i = 0; i < blk->TxnCount; i++)
			{
				auto& txn = _Chain[starting_idx]->Txns[i];
				txn.Jsonify(_pSimulator->GetEngine(txn.Txn->GetEngineId()), *_pGlobalShard, append);
			}
		}
	}

	return true;
}

bool SimuShard::JsonifyAllAddressStates(rt::Json& append, const rt::BufferEx<User>& Users, rvm::ContractId cid)
{
	if(!_AddressStates.GetSize())
	{
		return false;
	}
	_AddressStates.AllAddressStateJsonify(_pSimulator->GetAllEngines(), append, Users, cid, GetShardIndex(), _pGlobalShard);
	return true;
}

bool SimuShard::JsonifyAddressState(rt::Json& append, rvm::Address& Address, const rt::BufferEx<User>& Users, rvm::ContractId cid)
{
	if(!_AddressStates.GetSize())
	{
		return false;
	}
	_AddressStates.AddressStateJsonify(_pSimulator->GetAllEngines(), Address, append, Users, cid, GetShardIndex(), _pGlobalShard);
	return true;
}

bool SimuShard::JsonifyShardState(rt::Json& append, rvm::ContractId cid)
{
	return _ShardStates.ShardStateJsonify(_pSimulator->GetAllEngines(), append, cid, GetShardIndex(), _pGlobalShard);
}

rvm::InvokeResult*	SimuShard::GetConfirmTxn(const SimuTxn* txn) const
{
	uint64_t height = txn->Height;
	if(height < _Chain.GetSize())
	{
		SimuBlock* blk = _Chain[height];
		for (uint32_t i = 0; i < blk->TxnCount; i++)
		{
			if(blk->Txns[i].Txn == txn)
			{
				return &blk->Txns[i].Result;
			}
		}
	}
	return nullptr;
}

void SimuShard::JsonifyProfile(rt::Json& append) const
{
	rt::String sh = IsGlobal() ? "#g" : rt::String("#") + GetShardIndex();
	append.Object((J(ShardIndex) = sh,
		J(BlockHeight) = GetBlockHeight()));
}
#endif
} // namespace oxd
