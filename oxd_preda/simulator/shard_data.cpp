#pragma warning(push)
#pragma warning(disable:4244)
#include "../../SFC/core/ext/bignum/ttmath/ttmath.h"
#pragma warning(pop)
#include "shard_data.h"
#include "simu_global.h"
#include "chain_simu.h"
#include "core_contracts.h"


namespace oxd
{
ShardStateKeyObj::ShardStateKeyObj(const ShardStateKeyObj& x)
{
	Contract = x.Contract;
	Key.Size = x.Key.Size;
	if(Key.Size)
	{
		Key.Data = _Malloc8AL(uint8_t, Key.Size);
		memcpy((void*)Key.Data, x.Key.Data, Key.Size);
	}
	else
		Key.Data = nullptr;
}

const ShardStateKeyObj& ShardStateKeyObj::operator = (const ShardStateKeyObj& x)
{
	_SafeFree8AL_ConstPtr(Key.Data);

	Contract = x.Contract;
	Key.Size = x.Key.Size;
	if(Key.Size)
	{
		Key.Data = _Malloc8AL(uint8_t, Key.Size);
		memcpy((void*)Key.Data, x.Key.Data, Key.Size);
	}
	else
		Key.Data = nullptr;

	return x;
}

bool ShardStateKeyObj::operator == (const ShardStateKeyObj& x) const
{
	return Contract == x.Contract && Key.Size == x.Key.Size && memcmp(Key.Data, x.Key.Data, Key.Size) == 0;
}

ShardStateKeyObj::ShardStateKeyObj(ShardStateKeyObj&& x)
{
	rt::Copy(*this, x);
	rt::Zero(x);
}

ShardStateKeyObj::~ShardStateKeyObj()
{
	_SafeFree8AL_ConstPtr(Key.Data);
	rt::Zero(*this);
}

PendingTxns::~PendingTxns()
{
	std::lock_guard<std::mutex> lock(_Mutex);
	for (SimuTxn *txn : _Queue)
		txn->Release();
}

bool PendingTxns::Push(SimuTxn* tx)
{
	std::lock_guard<std::mutex> lock(_Mutex);
	bool ret = (_Queue.size() == 0);
	_Queue.push_back(tx);

	return ret;
}


bool PendingTxns::Push(SimuTxn** txns, uint32_t count)
{
	ASSERT(count);

	std::lock_guard<std::mutex> lock(_Mutex);

	bool ret = (_Queue.size() == 0);
	for (uint32_t i=0; i<count; i++, txns++)
	{
		ASSERT((*txns)->IsRelay());
		_Queue.push_back(*txns);
	}

	return ret;
}

bool PendingTxns::Push_Front(SimuTxn* tx)
{
	std::lock_guard<std::mutex> lock(_Mutex);
	bool ret = (_Queue.size() == 0);
	_Queue.push_front(tx);

	return ret;
}

SimuTxn* PendingTxns::Pop()
{
	std::lock_guard<std::mutex> lock(_Mutex);

	if (_Queue.empty())
		return nullptr;

	SimuTxn* txn = _Queue.front();
	_Queue.pop_front();
	return txn;
}

void SimuTxn::Jsonify(rvm::RvmEngine* engine, rt::Json& append) const
{
	append.Object();
	append.AppendKeyWithString("InvokeContextType", rt::EnumStringify(Type));
	rvm::Scope scope = GetScope();
	if(scope != rvm::Scope::Global && scope != rvm::Scope::Shard)
	{
		static const rt::SS szTarget("Target");
		rvm::ScopeKeySized kst = rvm::SCOPE_KEYSIZETYPE(scope);
		switch (kst)
		{
		case rvm::ScopeKeySized::Address:
			append.AppendKeyWithString(szTarget, oxd::SecureAddress::String(Target.addr));
			if(TargetIndex >= 0)
				append.AppendKeyWithString("AddressIndex", rt::SS() + ('@') + TargetIndex);
			break;
		case rvm::ScopeKeySized::UInt32:
			append.AppendKeyWithString(szTarget, rt::tos::Number(Target.u32) + "u32");
			break;
		case rvm::ScopeKeySized::UInt64:
			append.AppendKeyWithString(szTarget, rt::tos::Number(Target.u64) + "u64");
			break;
		case rvm::ScopeKeySized::UInt96:
			append.AppendKeyWithString(szTarget, (*(ttmath::UInt<96 / 32>*) & Target.u96).ToString() + "u96");
			break;
		case rvm::ScopeKeySized::UInt128:
			append.AppendKeyWithString(szTarget, (*(ttmath::UInt<128 / 32>*) & Target.u256).ToString() + "u128");
			break;
		case rvm::ScopeKeySized::UInt160:
			append.AppendKeyWithString(szTarget, (*(ttmath::UInt<160 / 32>*) & Target.u256).ToString() + "u160");
			break;
		case rvm::ScopeKeySized::UInt256:
			append.AppendKeyWithString(szTarget, (*(ttmath::UInt<256 / 32>*) & Target.u256).ToString() + "u256");
			break;
		case rvm::ScopeKeySized::UInt512:
			append.AppendKeyWithString(szTarget, (*(ttmath::UInt<512 / 32>*) & Target.u512).ToString() + "u512");
			break;
		default:
			ASSERT(0);
			break;
		}
	}

	if(IsRelay())
	{
		append << ((
			J(Initiator) = oxd::SecureAddress::String(Initiator),
			J(OriginateHeight) = OriginateHeight
		));

		if(OriginateShardIndex == rvm::GlobalShard)
		{
			append << ((J(OriginateShardIndex) = "g"));
		}
		else{
			append << ((J(OriginateShardIndex) = OriginateShardIndex));
		}
		append << ((J(OriginateShardOrder) = OriginateShardOrder));
	}

	if(Type == rvm::InvokeContextType::System)
	{
		append << ((
			J(BuildNum) = 0,
			J(Timestamp) = Timestamp,
			J(Contract) = "chain.deploy",
			J(Function) = "deploy"
			));
	}
	else
	{
		const rvm::Contract* contract = RvmDeployedContract(engine, rvm::CONTRACT_UNSET_SCOPE(Contract));
		if(!contract)
		{
			append.Empty();
			return;
		}
		append << ((
			J(BuildNum) = rvm::CONTRACT_BUILD(Contract),
			J(Timestamp) = Timestamp,
			J(Contract) = contract->GetName().Str(),
			J(Function) = contract->GetFunctionName((uint32_t)Op).Str()
			));
	}

	if (HasNativeTokensSupplied())
	{
		auto& coinsArr = GetNativeTokenSupplied();
		auto walletBody = append.ScopeAppendingKey("TokenSupply");
		append.Array();
		for (uint32_t i = 0; i < coinsArr.GetCount(); i++)
		{
			auto s = append.ScopeAppendingElement();
			coinsArr[i].Jsonify(append);
		}
	}
	
	if(Type != rvm::InvokeContextType::System && ArgsSerializedSize > 0)
	{
		rvm::StringStreamImpl str_out(append.GetInternalString());
		auto s2 = append.ScopeAppendingKey("Arguments");
		rvm::ConstData data({ SerializedData + TokensSerializedSize, ArgsSerializedSize });
		engine->ArgumentsJsonify(Contract, Op, &data, &str_out);
	}
	append << ((J(Height) = Height));

	if(ShardIndex == rvm::GlobalShard)
	{
		append << ((J(ShardIndex) = "g"));
	}
	else{
		append << ((J(ShardIndex) = ShardIndex));
	}
	append << ((J(ShardOrder) = ShardOrder));
}

SimuTxn* SimuTxn::Create(uint32_t args_size, uint32_t assets_size)
{
	uint32_t size = args_size + assets_size + offsetof(SimuTxn, SerializedData);
	auto* ret = (SimuTxn*)_Malloc8AL(uint8_t, size);
	rt::Zero(ret, size);
	ret->ArgsSerializedSize = args_size;
	ret->TokensSerializedSize = assets_size;
	ret->Gas = DefaultGas;

	return ret;
}

#ifndef __APPLE__
void SimuTxn::ReleaseRelay(std::pmr::unsynchronized_pool_resource* mem_pool)
{
	mem_pool->deallocate(this, GetSize());
}

SimuTxn* SimuTxn::CreateRelay(std::pmr::unsynchronized_pool_resource* mem_pool, uint32_t args_size, uint32_t assets_size)
{
	uint32_t size = args_size + assets_size + offsetof(SimuTxn, SerializedData);
	auto* ret = (SimuTxn*)mem_pool->allocate(size);
	rt::Zero(ret, size);
	ret->ArgsSerializedSize = args_size;
	ret->TokensSerializedSize = assets_size;
	ret->Gas = DefaultGas;

	return ret;
}
#endif

SimuTxn* SimuTxn::Clone() const
{
	uint64_t s = GetSize();
	SimuTxn* t = nullptr;
#ifndef __APPLE__
	if (IsRelay())
		t = (SimuTxn*)ChainSimulator::Get().GetShard(OriginateShardIndex)->GetMemPool()->allocate(s);
	else
#endif
		t = (SimuTxn*)_Malloc8AL(uint64_t, s);
	memcpy(t, this, s);

	return t;
}

void SimuBlock::Release()
{
	for(uint32_t i=0; i<TxnCount; i++){
#ifndef __APPLE__
		if(Txns[i].Txn->IsRelay())
			Txns[i].Txn->ReleaseRelay(ChainSimulator::Get().GetShard(Txns[i].Txn->OriginateShardIndex)->GetMemPool());
		else
#endif
			Txns[i].Txn->Release();
	}

	_SafeFree8AL_ConstPtr(this);
}

SimuBlock* SimuBlock::Create(uint32_t txn_count)
{
	uint32_t sz = offsetof(SimuBlock, Txns) + sizeof(ConfirmTxn)*txn_count;
	auto* ret = (SimuBlock*)_Malloc8AL(uint8_t, sz);

	rt::Zero(ret, sz);
	return ret;
}

#ifndef __APPLE__
SimuState* SimuState::Create(uint32_t size, rvm::BuildNum version, uint32_t shard_id, const void* data)
{
	auto* s = (SimuState*)ChainSimulator::Get().GetShard(shard_id)->GetMemPool()->allocate(size + offsetof(SimuState, Data));
	s->ShardId = shard_id;
	s->Version = version;
	s->DataSize = size;

	if(data)memcpy(s->Data, data, size);
	return s;
}
#else
SimuState* SimuState::Create(uint32_t size, rvm::BuildNum version, const void* data)
{
	auto* s = (SimuState*)_Malloc8AL(uint8_t, size + offsetof(SimuState, Data));
	s->Version = version;
	s->DataSize = size;

	if(data)memcpy(s->Data, data, size);
	return s;
}
#endif

void SimuState::Release() 
{ 
#ifndef __APPLE__
	ChainSimulator::Get().GetShard(ShardId)->GetMemPool()->deallocate(this, DataSize + offsetof(SimuState, Data));
#else
	_SafeFree8AL_ConstPtr(this);
#endif
}

bool RvmStateJsonify(rvm::ContractRepository* engine, rvm::ContractInvokeId ciid, const rvm::ConstData* contract_state, rvm::StringStream* json_out)
{
	if(contract_state == nullptr || contract_state->DataSize == 0)
	{
		json_out->Append("{}", 2);
		return true;
	}

	return engine->StateJsonify(ciid, contract_state, json_out);
}

const rvm::Contract* RvmDeployedContract(rvm::RvmEngine* engine, rvm::ContractVersionId cvid)
{
	if(rvm::CONTRACT_ENGINE(cvid) == rvm::EngineId::Core)
	{
		return CoreEngine::Get().GetContract(cvid);
	}
	else
	{
		auto* cdid = ChainSimulator::Get().GetGlobalStates()->GetContractDeployed(cvid);
		if(cdid)return engine->GetContract(&cdid->Module);
	}

	return nullptr;
}

} // namespace oxd
