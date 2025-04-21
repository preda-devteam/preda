#include "../../SFC/core/ext/botan/botan.h"
#include "../../SFC/core/ext/bignum/big_num.h"
#include "simu_global.h"
#include "chain_simu.h"

#if defined(__linux__) && defined(AFFINITY_SET)
#include <pthread.h>
#include <sched.h>
#endif


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

SimuShard::SimuShard(ChainSimulator* simu, uint64_t time_base, uint32_t shard_order)
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

SimuShard::SimuShard(ChainSimulator* simu, uint64_t time_base, uint32_t shard_order, uint32_t shard_index, SimuGlobalShard* global)
	:SimuShard(simu, time_base, shard_order)
{
	_pGlobalShard = global;
	_ShardIndex = shard_index;
}

rvm::DAppId SimuShard::GetDAppByName(const rvm::ConstString* dapp_name) const
{
	return _pGlobalShard->_GetDAppByName(dapp_name);
}

rvm::ContractVersionId SimuShard::GetContractByName(const rvm::ConstString* dapp_contract_name) const
{
	return _pGlobalShard->_GetContractByName(dapp_contract_name);
}

rvm::BuildNum SimuShard::GetContractEffectiveBuild(rvm::ContractId contract) const
{
	return _pGlobalShard->GetContractEffectiveBuild(contract);
}

const rvm::DeployedContract* SimuShard::GetContractDeployed(rvm::ContractVersionId contract) const
{
	return _pGlobalShard->_GetContractDeployed(contract);
}

rvm::TokenMinterFlag SimuShard::GetTokenMinterState(rvm::TokenId tid, rvm::ContractId contract) const
{
	return _pGlobalShard->_GetTokenMinterState(tid, contract);
}

const rvm::HashValue* SimuShard::GetTxnHash(rvm::HashValue* hash_out) const
{
	return &_pTxn->Hash;
}

uint32_t SimuShard::GetMicroTxnIndex() const
{
	return 0;
}

rvm::ScopeKey SimuShard::GetScopeTarget() const
{
	rvm::Scope scope = _GetScope();
	if(scope == rvm::Scope::Global || scope == rvm::Scope::Shard)
		return { nullptr, 0 };

	return { (uint8_t*)&_pTxn->Target.u256, _pTxn->Target.target_size };
}

rvm::ConstAddress* SimuShard::GetInitiator() const 
{
	ASSERT(_pTxn);
	if(_pTxn->IsRelay())return &_pTxn->Initiator;
	if(_pTxn->Target.target_size == sizeof(rvm::Address))return &_pTxn->Target.addr;

	return nullptr;
}

rvm::ConstStateData SimuShard::GetState(rvm::ContractScopeId contract, const rvm::ScopeKey* key) const
{
	auto scope = rvm::CONTRACT_SCOPE(contract);
	auto scope_type = rvm::SCOPE_TYPE(scope);

	ASSERT(scope_type != rvm::ScopeType::Contract);
	ShardStateKey k = { contract, *key };

	const SimuState* ret = nullptr;
	if(rvm::ScopeType::ScatteredMapOnGlobal == scope_type)
		ret = _pGlobalShard->_ShardKeyedStates.Get(k);
	else if(rvm::ScopeType::ScatteredMapOnShard == scope_type)
		ret = _ShardKeyedStates.Get(k);
	else 
		ASSERT(0);

	if(ret)return { ret->Data, ret->DataSize, ret->Version };
	else return { nullptr, 0, (rvm::BuildNum)0 };
}

rvm::ConstStateData	SimuShard::GetState(rvm::ContractScopeId cid) const
{
	const SimuState* ret = nullptr;
	auto scope = rvm::CONTRACT_SCOPE(cid);

	switch(scope)
	{
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
	default:
		if(IsGlobal())goto EMPTY_STATE;
		if(_GetScope() == scope)
		{
			SimuAddressContract k{ _pTxn->Target, cid };
			ret = _AddressStates.Get(k);
		}
	}

	if(ret)
		return { ret->Data, ret->DataSize, ret->Version };

EMPTY_STATE:
	return { nullptr, 0, (rvm::BuildNum)0 };
}

uint8_t* SimuShard::AllocateStateMemory(uint32_t dataSize)
{
#ifndef __APPLE__
	auto* s = SimuState::Create(dataSize, rvm::BuildNum(0), _ShardIndex);
#else
	auto* s = SimuState::Create(dataSize, rvm::BuildNum(0));
#endif
	return s?s->Data:nullptr;
}

void SimuShard::DiscardStateMemory(uint8_t* state)
{
	reinterpret_cast<SimuState*>(state - offsetof(SimuState, Data))->Release();
}

void SimuShard::CommitNewState(rvm::ContractInvokeId contract, const rvm::ScopeKey* key, uint8_t* state)
{
	auto scope = rvm::CONTRACT_SCOPE(contract);
	auto scope_type = rvm::SCOPE_TYPE(scope);

	ASSERT(scope_type != rvm::ScopeType::Contract);

	auto* s = (SimuState*)(state - offsetof(SimuState, Data));
	s->Version = rvm::CONTRACT_BUILD(contract);
	ShardStateKey k = { rvm::CONTRACT_UNSET_BUILD(contract), *key };

	_ShardKeyedStates.Set(k, s);
}

void SimuShard::CommitNewState(rvm::ContractInvokeId ciid, uint8_t* state)
{
	auto* s = (SimuState*)(state - offsetof(SimuState, Data));
	s->Version = rvm::CONTRACT_BUILD(ciid);

	auto csid = rvm::CONTRACT_UNSET_BUILD(ciid);
	auto scope = rvm::CONTRACT_SCOPE(ciid);
	switch (scope)
	{
	case rvm::Scope::Shard:
		ASSERT(!_IsGlobalScope());
		ASSERT(!IsGlobal());
		_ShardStates.Set(csid, s);
		break;
	case rvm::Scope::Global:
		ASSERT(_IsGlobalScope());
		ASSERT(IsGlobal());
		_ShardStates.Set(csid, s);
		break;
	default:
		{
			ASSERT(!_IsGlobalScope());
			ASSERT(_GetScope() == scope);

			SimuAddressContract k = { _pTxn->Target, csid };
			_AddressStates.Set(k, s);
		}
	}
}

rvm::ConstAddress* SimuShard::GetBlockCreator() const
{
	return &_pSimulator->GetMiner();
}

SimuTxn* SimuShard::_CreateRelayTxn(rvm::ContractInvokeId ciid, rvm::OpCode opcode, const rvm::ConstData* args_serialized, uint32_t gas_redistribution_weight) const
{
	auto scope = rvm::CONTRACT_SCOPE(ciid);
	if(rvm::CONTRACT_ENGINE(ciid) != rvm::EngineId::SOLIDITY_EVM && scope == rvm::ScopeInvalid) return nullptr;
#ifndef __APPLE__
	auto* txn = SimuTxn::CreateRelay(const_cast<std::pmr::unsynchronized_pool_resource*>(&_MemoryPool), args_serialized?(uint32_t)args_serialized->DataSize:0U, 0);
#else
	auto* txn = SimuTxn::Create(args_serialized?(uint32_t)args_serialized->DataSize:0U, 0);
#endif
	txn->Type = rvm::InvokeContextType::RelayInbound;
	txn->Contract = ciid;
	txn->Op = opcode;
	txn->Timestamp = _GetBlockTime();
	txn->Flag = TXN_RELAY;
	txn->OriginateHeight = _BlockHeight;
	ASSERT(_ShardIndex <= 65535)
	txn->OriginateShardIndex = uint16_t(_ShardIndex);
	txn->OriginateShardOrder = _ShardOrder;
	txn->Gas = 0;
	txn->GasRedistributionWeight = gas_redistribution_weight;

	ASSERT(txn->ArgsSerializedSize == args_serialized->DataSize);
	memcpy(txn->SerializedData, args_serialized->DataPtr, args_serialized->DataSize);

	sec::Hash<sec::HASH_SHA256>().Calculate(((char*)txn) + sizeof(rvm::HashValue), txn->GetSize() - sizeof(rvm::HashValue), &txn->Hash);

	return txn;
}

bool SimuShard::EmitRelayToScope(rvm::ContractInvokeId ciid, const rvm::ScopeKey* key, rvm::OpCode opcode, const rvm::ConstData* args_serialized, uint32_t gas_redistribution_weight)
{
	auto* txn = _CreateRelayTxn(ciid, opcode, args_serialized, gas_redistribution_weight);
	ASSERT(txn->Contract == ciid);
	rvm::ScopeKeySized kst = rvm::SCOPE_KEYSIZETYPE(rvm::CONTRACT_SCOPE(ciid));

	switch(kst)
	{
	case rvm::ScopeKeySized::Address:
		ASSERT(key->Size == sizeof(rvm::Address));
		txn->Target = ScopeTarget(*(rvm::Address*)key->Data);
		break;
	case rvm::ScopeKeySized::UInt32:
		ASSERT(key->Size == sizeof(uint32_t));
		txn->Target = ScopeTarget(*(uint32_t*)key->Data);
		break;
	case rvm::ScopeKeySized::UInt64:
		ASSERT(key->Size == sizeof(uint64_t));
		txn->Target = ScopeTarget(*(uint64_t*)key->Data);
		break;
	case rvm::ScopeKeySized::UInt96:
		ASSERT(key->Size == sizeof(rvm::UInt96));
		txn->Target = ScopeTarget(*(rvm::UInt96*)key->Data);
		break;
	case rvm::ScopeKeySized::UInt128:
		ASSERT(key->Size == sizeof(rvm::UInt128));
		txn->Target = ScopeTarget(*(rvm::UInt128*)key->Data);
		break;
	case rvm::ScopeKeySized::UInt160:
		ASSERT(key->Size == sizeof(rvm::UInt160));
		txn->Target = ScopeTarget(*(rvm::UInt160*)key->Data);
		break;
	case rvm::ScopeKeySized::UInt256:
		ASSERT(key->Size == sizeof(rvm::UInt256));
		txn->Target = ScopeTarget(*(rvm::UInt256*)key->Data);
		break;
	case rvm::ScopeKeySized::UInt336:
		ASSERT(key->Size == sizeof(rvm::UInt336));
		txn->Target = ScopeTarget(*(rvm::UInt336*)key->Data);
		break;
	case rvm::ScopeKeySized::UInt512:
		ASSERT(key->Size == sizeof(rvm::UInt512));
		txn->Target = ScopeTarget(*(rvm::UInt512*)key->Data);
		break;
	default:
		break;
	}
	txn->Initiator = _pTxn->IsRelay()?_pTxn->Initiator:_pTxn->Target.addr;

	_RelayEmitted.push_back(txn);
	return true;
}

bool SimuShard::EmitRelayToGlobal(rvm::ContractInvokeId cid, rvm::OpCode opcode, const rvm::ConstData* args_serialized, uint32_t gas_redistribution_weight)
{
	auto* txn = _CreateRelayTxn(cid, opcode, args_serialized, gas_redistribution_weight);

	rt::Zero(txn->Target);
	txn->Initiator = _pTxn->IsRelay()?_pTxn->Initiator:_pTxn->Target.addr;

	_RelayEmitted.push_back(txn);
	return true;
}

bool SimuShard::EmitRelayDeferred(rvm::ContractInvokeId cid, rvm::OpCode opcode, const rvm::ConstData* args_serialized, uint32_t gas_redistribution_weight)
{
	ASSERT(_pTxn->GetScope() != rvm::Scope::Shard);

	auto* txn = _CreateRelayTxn(cid, opcode, args_serialized, gas_redistribution_weight);
	txn->Flag = TXN_DEFERRED;
	txn->Target = _pTxn->Target;
	txn->Initiator = _pTxn->IsRelay()?_pTxn->Initiator:_pTxn->Target.addr;

	_RelayEmitted.push_back(txn);
	return true;
}

bool SimuShard::EmitBroadcastToShards(rvm::ContractInvokeId cid, rvm::OpCode opcode, const rvm::ConstData* args_serialized, uint32_t gas_redistribution_weight)
{
	auto* txn = _CreateRelayTxn(cid, opcode, args_serialized, gas_redistribution_weight);

	txn->Flag = (SimuTxnFlag)(txn->Flag|TXN_BROADCAST);
	rt::Zero(txn->Target);
	txn->Initiator = _pTxn->IsRelay()?_pTxn->Initiator:_pTxn->Target.addr;
	if(rvm::CONTRACT_SCOPE(_pTxn->Contract) == rvm::Scope::Global)
	{
		txn->Type = rvm::InvokeContextType::Scheduled; // Global to Shards 
	}

	_RelayEmitted.push_back(txn);
	return true;
}

rvm::ExecuteResult SimuShard::Invoke(uint32_t gas_limit, rvm::ContractInvokeId contract, rvm::OpCode opcode, const rvm::ConstData* args_serialized)
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

bool SimuShard::NativeTokensDeposit(const rvm::ConstNativeToken* tokens, uint32_t count)
{
	ASSERT(_pTxn);
	if (_pTxn->Target.target_size != sizeof(rvm::Address))
		return false;

	for (uint32_t i = 0; i < count; i++)
	{
		if (tokens[i].Amount.Sign)
			return false;
	}

	ASSERT(_pTxn->Target.target_size == sizeof(rvm::Address));

	CoreContractState<CORE_WALLET> s = _AddressStates.Get({ _pTxn->Target.addr, -CORE_WALLET });
	rvm::CoinsWalletMutable next = s.DeriveMutable();

	for (uint32_t i = 0; i < count; i++)
		next.Deposit(tokens[i]);

	CommitCoreState<CORE_WALLET>(next);

	return true;
}

void SimuShard::NativeTokensSupplyChange(const rvm::ConstNativeToken* tokens, uint32_t count)
{
	thread_local rt::String str;

	str.Empty();
	for (uint32_t i = 0; i < count; i++)
	{
		ext::BigNumRef bRef = ext::BigNumRef(tokens[i].Amount.Sign, tokens[i].Amount.Blocks, tokens[i].Amount.BlockCount);
		ext::_details::BN_ToString(bRef, str, 10);
		str += ' ';
		str += rvm::TokenIdToSymbol(tokens[i].Token);
		if (i < count - 1)
		{
			str += ',';
			str += ' ';
		}
	}
	_LOGC_VERBOSE("[PRD]: Token Supply Change: " << str);
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

	_AddressStates.Empty();
	_ShardStates.Empty();
	_ShardKeyedStates.Empty();

	for (auto b : _Chain)
		b->Release();

	_Chain.ShrinkSize(0);
}

void SimuShard::SetState(rvm::ContractScopeId csid, SimuState* s)
{
#if defined(PLATFORM_DEBUG_BUILD)
	auto scope = rvm::CONTRACT_SCOPE(csid);
	ASSERT(	(scope == rvm::Scope::Global && IsGlobal()) ||
			(scope == rvm::Scope::Shard && !IsGlobal())
	);
#endif

	_ShardStates.Set(csid, s);
}

void SimuShard::SetState(rvm::ContractScopeId csid, const rvm::Address& target, SimuState* s)
{
	ASSERT(rvm::CONTRACT_SCOPE(csid) == rvm::Scope::Address);
	ASSERT(_pSimulator->GetShardIndex(target) == _ShardIndex);

	_AddressStates.Set({ ScopeTarget(target), csid }, s);
}

void SimuShard::PushNormalTxn(SimuTxn* t)
{
	ASSERT(!t->IsRelay());

	bool first_item = _PendingTxns.Push(t);
	_pSimulator->OnTxnPushed();

	if(first_item && _pSimulator->IsShardingAsync() && !_pSimulator->IsChainPaused() && !_pSimulator->IsChainStepping())
		_GoNextBlock.Set();
}

void SimuShard::PushRelayTxn(SimuTxn** txns, uint32_t count)
{
	if(count)
	{
		ASSERT(txns[0]->IsRelay());

		bool first_item = _PendingRelayTxns.Push(txns, count);
		//_pSimulator->OnTxnPushed(count);
		_pSimulator->OnTxnPushed(count);

		if(first_item && _pSimulator->IsShardingAsync() && !_pSimulator->IsChainPaused() && !_pSimulator->IsChainStepping())
			_GoNextBlock.Set();
	}
}

RelayEmission::RelayEmission(ChainSimulator* s, SimuShard* shard)
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

void RelayEmission::Collect(SimuTxn* origin, rt::BufferEx<SimuTxn*>& txns, uint64_t remained_gas)
{
#define APPEND_TRACE(t)		_pShard->AppendToTxnTrace(origin, t)
	// calculate total gas redistribution weight
	uint32_t total_weight = 0;
	for(SimuTxn* t : txns)
	{
		switch(t->GetScope())
		{
		case rvm::Scope::Shard:
			total_weight += t->GasRedistributionWeight * (uint32_t)_ToShards.GetSize();
			break;
		default:
			total_weight += t->GasRedistributionWeight;
		}
	}
	uint64_t relay_gas_unit = remained_gas / total_weight;
	remained_gas -= relay_gas_unit * total_weight;

	for(SimuTxn* t : txns)
	{
		t->Gas += t->GasRedistributionWeight * relay_gas_unit;
		if(t->IsDeferred())
		{
			_ToNextBlock.push_back(t);
			APPEND_TRACE(t);
			continue;
		}

		ASSERT(t->IsRelay());

		switch(t->GetScope())
		{
		case rvm::Scope::Global:
			_ToGlobal.push_back(t);
			APPEND_TRACE(t);
			break;
		case rvm::Scope::Shard:
			for(uint32_t i = 1; i < _ToShards.GetSize(); i++)
			{
				SimuTxn* _clone = t->Clone();
				_ToShards[i].push_back(_clone);
				APPEND_TRACE(_clone);
			}
			_ToShards[0].push_back(t);
			APPEND_TRACE(t);
			break;
		default:
			{
				uint32_t si = _pSimulator->GetShardIndex(t->Target);
				APPEND_TRACE(t);
				if (t->OriginateShardIndex == si)
				{
					_pShard->PushIntraRelay(t);
					_pSimulator->OnTxnPushed();
					continue;
				}
				_ToShards[si].push_back(t);
			}
		}
	}

	txns.ShrinkSize(0);
#undef APPEND_TRACE
}

void RelayEmission::Dispatch()
{
	if(_ToGlobal.GetSize())
	{
		_pSimulator->GetGlobalShard()->PushRelayTxn(_ToGlobal, (uint32_t)_ToGlobal.GetSize());
		_ToGlobal.ShrinkSize(0);
	}

	for(uint32_t i=0; i<_ToShards.GetSize(); i++)
	{
		auto& txns = _ToShards[i];
		if(txns.GetSize())
		{
			_pSimulator->GetShard(i)->PushRelayTxn(txns, (uint32_t)txns.GetSize());
			txns.ShrinkSize(0);
		}
	}
}

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

uint32_t SimuShard::GetCount() const
{
	ASSERT(_pTxn);
	return _pTxn->HasNativeTokensSupplied()?_pTxn->GetNativeTokenSupplied().GetCount():0;
}

rvm::ConstNativeToken SimuShard::Get(uint32_t idx) const
{
	ASSERT(_pTxn);
	rvm::ConstNativeToken ret = { rvm::TokenIdInvalid, {nullptr, 0} };
	if (_pTxn->HasNativeTokensSupplied() && _pTxn->GetNativeTokenSupplied().GetCount() > idx)
	{
		const rvm::Coins& tk = _pTxn->GetNativeTokenSupplied().Get(idx);
		ret.Token = tk.GetId();
		auto& a = tk.GetAmount();
		if (a.IsPositive())
		{
			ret.Amount.BlockCount = a.GetBlockCount();
			ret.Amount.Blocks = a._Data;
			ret.Amount.Sign = a.GetSign();
		}
	}

	return ret;
}

void SimuShard::_Execute(SimuTxn* t)
{
	_pTxn = t;
	rvm::ConstData args = _pTxn->GetArguments();
	ConfirmTxn& cTxn = _TxnExecuted.push_back();
	rvm::InvokeResult& ret = cTxn.Result;
	cTxn.Txn = _pTxn;

	rvm::ExecutionUnit* pexec = nullptr;
	if(_pTxn->Type != rvm::InvokeContextType::System)
	{
		pexec = _ExecUnits.Get(_pTxn->GetEngineId());
		if(pexec)
		{
			if(_pTxn->HasNativeTokensSupplied())
			{	// withdraw native assets supply
				ASSERT(_pTxn->Type == rvm::InvokeContextType::Normal);
				auto& withdraw = _pTxn->GetNativeTokenSupplied();
				uint32_t withdraw_count = withdraw.GetCount();
				if(withdraw_count)
				{
					ASSERT(_pTxn->Target.target_size == sizeof(rvm::Address));
					CoreContractState<CORE_WALLET> s = _AddressStates.Get({ _pTxn->Target.addr, -CORE_WALLET });
					if(s.IsEmpty())
					{
						rt::Zero(ret);
						ret.Code = rvm::InvokeErrorCode::InsufficientFunds;
						goto POST_INVOKE;
					}

					rvm::CoinsWalletMutable next = s.DeriveMutable();
					for(uint32_t i=0; i<withdraw_count; i++)
					{
						if(!next.Withdraw(withdraw.Get(i)))
						{
							rt::Zero(ret);
							ret.Code = rvm::InvokeErrorCode::InsufficientFunds;
							goto POST_INVOKE;
						}
					}

					CommitCoreState<CORE_WALLET>(next);
				}
			}

			ret = pexec->Invoke(this, (uint32_t)_pTxn->Gas, _pTxn->Contract, _pTxn->Op, &args);
			if(ret.TokenResidual)
			{
				thread_local rt::String str;
				uint32_t co = ret.TokenResidual->GetCount();

				str.Empty();
				for(uint32_t i=0; i<co; i++)
				{
					const rvm::ConstNativeToken cnt = ret.TokenResidual->Get(i);
					ext::BigNumRef bRef = ext::BigNumRef(cnt.Amount.Sign, cnt.Amount.Blocks, cnt.Amount.BlockCount);
					ASSERT(!cnt.Amount.Sign);
					ext::_details::BN_ToString(bRef, str, 10);
					str += ' ';
					str += rvm::TokenIdToSymbol(cnt.Token);
					if(i<co-1)
					{
						str += ',';
						str += ' ';
					}
					ext::BigNumMutable BNTmp;
					BNTmp = bRef;
					cTxn.Residual.push_back({ cnt.Token, BNTmp });
				}

				_LOGC_VERBOSE("[PRD]: Execution Residual: "<<str);
				_SafeRelease(ret.TokenResidual);
			}
		}
		else
		{
			rt::Zero(ret);
			ret.Code = rvm::InvokeErrorCode::ExecutionEngineUnavailable;
			_LOG_WARNING("[PRD]: Engine " << rt::EnumStringify(_pTxn->GetEngineId()) << " is not available");
		}
	}	
	else
	{
		rvm::ConstData args = _pTxn->GetArguments();
		ret = _pSimulator->DeployFromStatement(args);
	}

POST_INVOKE:
	if(IsGlobal())
		_pGlobalShard->_OnGlobalTransactionExecuted(ret.Code == rvm::InvokeErrorCode::Success);

	if(ret.Code != rvm::InvokeErrorCode::Success)
	{
		if((int)ret.SubCodeLow > 0)
		{
			rvm::StringStreamImpl str;
			if(pexec)
				pexec->GetExceptionMessage(ret.SubCodeLow, &str);
			else
			{
				std::string s = std::move(std::to_string(ret.SubCodeLow));
				str.Append(s.c_str(), uint32_t(s.length()));
			}
			_LOG_WARNING("[PRD]: Engine invoke error. Error Message: " << rt::EnumStringify(ret.Code) << " (" << (rt::String_Ref)str << ")");
		}
		else
			_LOG_WARNING("[PRD]: Engine invoke error. Error Message: " << rt::EnumStringify(ret.Code));
	}

	_pTxn->Height = _BlockHeight;
	ASSERT(_ShardIndex <= 65535)
	_pTxn->ShardIndex = uint16_t(_ShardIndex);
	_pTxn->ShardOrder = _ShardOrder;

	uint64_t remainingGas = _pTxn->Gas - ret.GasBurnt;
	if(_RelayEmitted.GetSize())
		_TxnEmitted.Collect(t, _RelayEmitted, remainingGas);
	_TotalGasBurnt += _pTxn->Gas - remainingGas;

	//_LOG("Gas Burnt: " << _pTxn->Gas - remainingGas);
}

void SimuShard::_BlockCreationRoutine()
{
#if defined(__linux__) && defined(AFFINITY_SET)
        if(!IsGlobal())
        {
		    struct sched_param param;
            param.sched_priority = 99; // Setting priority.

    	    // set the scheduling parameters
    	    int ret = pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);
    	    if (ret != 0) {
//    	         printf("pthread_setschedparam returned %d\n", ret);
    	    }
		    cpu_set_t cpuset;
		    pthread_t thread = pthread_self();
		    int core = this->_ShardIndex;
		    CPU_ZERO(&cpuset);
		    CPU_SET(core, &cpuset);
		    pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
        }
#endif
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

		if(_BlockCreator.WantExit())
			return;

		step = _pSimulator->IsChainStepping();
		uint64_t gas_limit = IsGlobal() ? _pSimulator->GetScriptGlobalGasLimit() : _pSimulator->GetScriptGasLimit();

		// start a new block
		_TotalGasBurnt = 0;
		_PrevBlockHash = _BlockHash;
		ASSERT(_TxnExecuted.GetSize() == 0);

		// executing deferred txn from previous block
		{
			for(auto t : _TxnEmitted.GetDeferredTxns())
			{
				_Execute(t); // execute a defer txn
			}

			_TxnEmitted.ClearDeferredTxns();
		}

		// executing txns
		// relay txns first
		while (SimuTxn* t = _TotalGasBurnt < gas_limit ? _PendingRelayTxns.Pop() : nullptr)
		{
			if (!async)
			{
				// there shouldn't be txns from larger height because in sync mode all shards grow at the same time
				ASSERT(t->OriginateHeight <= _BlockHeight);
				// a relay txn shouldn't be included in blocks of the same height as its originate height, unless it's a relay from global shard
				if (t->OriginateHeight == _BlockHeight && t->OriginateShardIndex != rvm::GlobalShard)
				{
					// push the txn back to the front of the queue
					_PendingRelayTxns.Push_Front(t);
					// txns in _PendingRelayTxns are always in increasing order of OriginateHeight; and for txns of the same height, those from global shard are enqueued before the txns from other shards
					// therefore, once a txn with OriginateHeight of _BlockHeight and OriginateShardIndex of non-global is encountered, the rest of the queue should all be skipped for the current block
					break;
				}
			}
			ASSERT(_RelayEmitted.GetSize() == 0);
			_Execute(t); // execute a txn
		}

		// normal txns second
#ifdef VERIFY_SIG
		oxd::SecuritySuite ss(oxd::SEC_SUITE_ED25519);
#endif
		while (SimuTxn* t = _TotalGasBurnt < gas_limit ? _PendingTxns.Pop() : nullptr)
		{
			ASSERT(_RelayEmitted.GetSize() == 0);
#ifdef VERIFY_SIG
			if(rvm::Scope::Address == t->GetScope() && !ss.VerifySignature( &(t->pk[0]), &(t->sig[0]), &t->SerializedData, t->ArgsSerializedSize)) {
				std::cout << "verify failed" << std::endl;
			}
#endif
			_Execute(t); // execute a txn
		}

		// intra-relays last
		while (SimuTxn* t = _IntraRelayTxns.Pop())
			_Execute(t);

		// finalize a block
		auto* block = SimuBlock::Create((uint32_t)_TxnExecuted.GetSize());
		block->Height = _BlockHeight;
		block->PrevBlock = _PrevBlockHash;
		block->Timestamp = _GetBlockTime();
		block->Miner = _pSimulator->GetMiner();
		block->ShardId = _ShardIndex;
		block->TxnCount = (uint32_t)_TxnExecuted.GetSize();
		_TxnExecuted.CopyTo(block->Txns);
		*(uint64_t*)&_BlockHash = os::crc64(block, offsetof(SimuBlock, Txns));
		block->TotalGas = _TotalGasBurnt;
		_Chain.push_back(block);

		// dispatch relay
		_TxnEmitted.Dispatch();
		_pSimulator->OnTxnPushed(uint32_t(_TxnEmitted.GetDeferredTxns().GetSize()));		// otherwise _PendingTxnCount would be incorrect and chain step might step due if there are no other txns pending

		// clean up
		_ConfirmedTxnCount += (uint32_t)_TxnExecuted.GetSize();
		if(_TxnExecuted.GetSize())
		{
			_pSimulator->OnTxnsConfirmed((uint32_t)_TxnExecuted.GetSize());
			_TxnExecuted.ShrinkSize(0);
		}
		_ReturnVal.ShrinkSize(0);
		_BlockHeight++;

		//_BlockCreator.WantExit() = _pSimulator->GetTerminationSignal();

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
					if(_pSimulator->GetPendingTxnsCount() && !step && !_pSimulator->IsChainPaused())
						_pGlobalShard->Step();
					else
						_pSimulator->SetChainIdle();
				}
			}
			else{
				if(_pSimulator->GetPendingTxnsCount() && !step && !_pSimulator->IsChainPaused())
					_pGlobalShard->Step();
				else
					_pSimulator->SetChainIdle();
			}
		}
	}
}

void SimuShard::LogInfo()
{
	rt::tos::Number gi(_ShardIndex);
	if(IsGlobal())(rt::String_Ref&)gi = "g";

	_LOG(	"[PRD]: " <<
			"Shd#"<<gi<<":\t"<<
			"h:"<<_BlockHeight<<" "
			"txn:"<<_PendingTxns.GetSize()<<'/'<<_PendingRelayTxns.GetSize()<<'/'<<_ConfirmedTxnCount<<" "
			"addr:"<<_AddressStates.GetSize()
	);
}

void SimuShard::Step()
{
	_GoNextBlock.Set();
}
bool SimuShard::JsonifyBlocks(rt::Json& append, int64_t height)
{
	if(!_Chain.GetSize() || height >= (int)_Chain.GetSize())
	{
		_LOG("[PRD] Line " << _pSimulator->GetLineNum() << ": Block index is out of range")
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
		append.Object((
			(J(Height) = blk->Height),
			(J(PrevBlock) = prev_blk_hash),
			(J(ShardIndex) = shard_index),
			(J(Timestamp) = blk->Timestamp),
			(J(Miner) = oxd::SecureAddress::String(blk->Miner)),
			(J(TxnCount) = blk->TxnCount)
		));
		if(blk->TxnCount > 0)
		{
			auto s2 = append.ScopeAppendingKey("ConfirmTxn");
			append.Array();
			for(uint32_t i = 0; i < blk->TxnCount; i++)
			{
				auto& txn = _Chain[starting_idx]->Txns[i];
				txn.Jsonify(_pSimulator->GetEngine(txn.Txn->GetEngineId()), append);
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
	for(uint32_t id = 0; id < Users.GetSize(); ++id)
		_AddressStates.AddressStateJsonify(_pSimulator->GetAllEngines(), append, id, cid, GetShardIndex(), &Users[id].Addr);
	return true;
}

bool SimuShard::JsonifyAddressState(rt::Json& append, const rvm::Address* targetAddr, uint32_t userId, rvm::ContractId cid)
{
	if(rvm::CONTRACT_ENGINE(cid) == rvm::EngineId::SOLIDITY_EVM)
	{
		rvm::ContractInvokeId ciid = rvm::CONTRACT_SET_SCOPE_BUILD(cid, rvm::Scope::Address, rvm::BuildNumInit);
		rvm::StringStreamImpl str_impl;
		std::vector<uint8_t> data(sizeof(rvm::ChainStates*) + sizeof(rvm::Address));
		auto chain_state_addr = dynamic_cast<rvm::ChainStates*>(this);
		std::memcpy(data.data(), &chain_state_addr, sizeof(rvm::ChainStates*));
		std::memcpy(data.data() + sizeof(rvm::ChainStates*), targetAddr, sizeof(rvm::Address));
		rvm::ConstData const_data{data.data(), sizeof(rvm::Address)};
		if (!_pSimulator->GetAllEngines()[(uint8_t)rvm::EngineId::SOLIDITY_EVM].pEngine->StateJsonify(ciid, &const_data, &str_impl))
			return false;
		nlohmann::json json;
		rt::tos::Base32CrockfordLowercaseOnStack<> addrStr(targetAddr, sizeof(rvm::ConstAddress));
		json["Address"] = std::string(addrStr.Begin());
		json["AddressIndex"] = userId;
		json["ShardIndex"] = _ShardIndex;
		json["States"].push_back(nlohmann::json::parse(str_impl.GetString().StrPtr));
		nlohmann::json json_out = nlohmann::json::parse(append.GetInternalString().GetString());
		json_out.push_back(json);
		append.GetInternalString() = rt::String(json_out.dump().c_str());
	}
	else
	{
		if(!_AddressStates.GetSize())
			return false;
		_AddressStates.AddressStateJsonify(_pSimulator->GetAllEngines(), append, userId, cid, GetShardIndex(), targetAddr);
	}
	return true;
}

void SimuShard::JsonifyAddressStateWithoutGrouping(rt::Json& append, rvm::ContractId cid)
{
	_AddressStates.ContractStateJsonify(_pSimulator->GetAllEngines(), append, cid);
}

bool SimuShard::JsonifyShardState(rt::Json& append, rvm::ContractId cid)
{
	if(!_ShardStates.ShardStateJsonify(_pSimulator->GetAllEngines(), append, cid, GetShardIndex()))
		return false;
	if(!_ShardKeyedStates.ScatteredMapJsonify(_pSimulator->GetAllEngines(), append.GetInternalString(), GetShardIndex()))
		return false;
	if(rvm::CONTRACT_ENGINE(cid) == rvm::EngineId::SOLIDITY_EVM)
	{
		rvm::ContractInvokeId ciid = rvm::CONTRACT_SET_SCOPE_BUILD(cid, IsGlobal() ? rvm::Scope::Global : rvm::Scope::Shard, rvm::BuildNumInit);
		rvm::StringStreamImpl str_impl;
		std::vector<uint8_t> data(sizeof(rvm::ChainStates*));
		auto chain_state_addr = dynamic_cast<rvm::ChainStates*>(this);
		std::memcpy(data.data(), &chain_state_addr, sizeof(rvm::ChainStates*));
		rvm::ConstData const_data{data.data(), 0};
		if (!_pSimulator->GetAllEngines()[(uint8_t)rvm::EngineId::SOLIDITY_EVM].pEngine->StateJsonify(ciid, &const_data, &str_impl))
			return false;
		nlohmann::json json = nlohmann::json::parse(append.GetInternalString().GetString());
		json.back()["States"].push_back(nlohmann::json::parse(str_impl.GetString().StrPtr));
		append.GetInternalString() = rt::String(json.dump().c_str());
	}
	return true;
}

bool SimuShard::ConfirmedTxnJsonify(const SimuTxn* txn, rt::Json& append) const
{
	uint64_t height = txn->Height;
	if(height < _Chain.GetSize())
	{
		SimuBlock* blk = _Chain[height];
		for(uint32_t i = 0; i < blk->TxnCount; i++)
		{
			if(blk->Txns[i].Txn == txn)
			{
				blk->Txns[i].Jsonify(_pSimulator->GetEngine(blk->Txns[i].Txn->GetEngineId()), append);
				return true;
			}
		}
	}
	return false;
}
bool SimuShard::JsonifyScopeState(rt::Json& append, SimuAddressContract key, bool allState)
{
	return _AddressStates.ScopeStateJsonify(_pSimulator->GetAllEngines(), append, key, _ShardIndex, allState);
}

void SimuShard::JsonifyProfile(rt::Json& append) const
{
	rt::String sh = IsGlobal() ? "#g" : rt::String("#") + GetShardIndex();
	append.Object((J(ShardIndex) = sh,
		J(BlockHeight) = GetBlockHeight()));
}
} // namespace oxd
