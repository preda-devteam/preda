#pragma once
#include "shard_data.h"
#include "../native/types/typetraits.h"
#include "core_contracts.h"

#ifndef __APPLE__
#include <memory_resource>
#endif

namespace oxd
{
class ChainSimulator;
class Simulator;
class SimuShard;
class SimuGlobalShard;

class ExecutionUnit
{
	//friend class Simulator;
	friend class ChainSimulator;
	rvm::ExecutionUnit*	pUnits[(int)rvm::EngineId::Max];

public:
	rvm::ExecutionUnit* Get(rvm::EngineId e) const { if(e >= rvm::EngineId::Max) return nullptr; return pUnits[(int)e]; }
	void	Release(){ for(auto& p : pUnits)_SafeRelease(p); }
	ExecutionUnit(){ rt::Zero(pUnits); }
	~ExecutionUnit(){ Release(); }
};

class RelayEmission
{
protected:
	rt::BufferEx<SimuTxn*>				_ToGlobal;
	rt::Buffer<rt::BufferEx<SimuTxn*>>	_ToShards;
	rt::BufferEx<SimuTxn*>				_ToNextBlock;

	ChainSimulator* _pSimulator;
	SimuShard*  _pShard;

public:
	RelayEmission(ChainSimulator* s, SimuShard* shard);
	RelayEmission(Simulator* s, SimuShard* shard);
	~RelayEmission();
	void	Collect(SimuTxn* origin, rt::BufferEx<SimuTxn*>& txns, uint64_t remained_gas);
	void	Dispatch();  // dispatch all collected and clean up
	auto&	GetDeferredTxns() const { return _ToNextBlock; }
	void	ClearDeferredTxns(){ _ToNextBlock.ShrinkSize(0); };
};

struct ShardStates
{
	SimuChainState<rvm::ContractScopeId>	_ShardStates;	// in IsGlobal(), it is global state
	SimuChainState<ShardStateKeyObj>		_ShardKeyedStates;

	void	Revert();
	void	Commit(ShardStates& to); // this will be clear
};

class SimuShard: public rvm::ExecutionContext
			   , protected rvm::NativeTokens
			   , protected ShardStates
{
protected:
	ExecutionUnit				_ExecUnits;
	ChainSimulator*				_pSimulator = nullptr;
	SimuGlobalShard*			_pGlobalShard = nullptr;

	PendingTxns					_PendingTxns;
	PendingTxns					_PendingRelayTxns;
	PendingTxns					_IntraRelayTxns;
	uint32_t					_ConfirmedTxnCount;

	SimuChainState<SimuAddressContract>		_AddressStates; // shard scope only

	rt::BufferEx<SimuBlock*>	_Chain;
	os::Event					_GoNextBlock;
	os::Thread					_BlockCreator;
	void						_BlockCreationRoutine();
	void						_Execute(SimuTxn* t);

	ext::fast_map<SimuTxn*, rt::BufferEx<SimuTxn*>>	_TxnTrace;

protected:
	// current block being executing
	uint64_t					_BlockTimeBase;
	uint64_t					_BlockHeight;
	rvm::HashValue				_BlockHash;
	rvm::HashValue				_PrevBlockHash;
	uint32_t					_ShardIndex; // = 65535 for global shard
	uint32_t					_ShardOrder;
	rt::Randomizer				_Rand;
	uint64_t					_TotalGasBurnt;
	rt::BufferEx<ConfirmTxn>	_TxnExecuted;
	RelayEmission				_TxnEmitted;

	constexpr static uint64_t relay_base_gas = 2000;
#ifndef __APPLE__
	std::pmr::unsynchronized_pool_resource _MemoryPool;
#endif
	// current transaction being executing
	SimuTxn*					_pTxn = nullptr;
	rt::BufferEx<uint8_t>		_ReturnVal;
	rt::BufferEx<SimuTxn*>		_RelayEmitted;  // all be dispatched and cleared once txn execution is done
	bool						_IsAddressScope() const { return _pTxn&&_pTxn->GetScope() == rvm::Scope::Address; }
	rvm::Scope					_GetScope() const { if(_pTxn) return _pTxn->GetScope(); return rvm::ScopeInvalid; }
	bool						_IsGlobalScope() const { return (SimuShard*)_pGlobalShard == this; }
	uint64_t					_GetBlockTime() const { return _BlockTimeBase + _BlockHeight*SIMU_BLOCK_INTERVAL; }
	SimuTxn*					_CreateRelayTxn(rvm::ContractInvokeId ciid, rvm::OpCode opcode, const rvm::ConstData* args_serialized, uint32_t gas_redistribution_weight) const;

public:
	/////////////////////////////////////////////////////
	// From rvm::ExecutionContext::ChainState
	virtual rvm::DAppId						GetDAppByName(const rvm::ConstString* dapp_name) const override;
	virtual rvm::ContractVersionId			GetContractByName(const rvm::ConstString* dapp_contract_name) const override;
	virtual rvm::BuildNum					GetContractEffectiveBuild(rvm::ContractId contract) const override;
	virtual const rvm::DeployedContract*	GetContractDeployed(rvm::ContractVersionId) const override;
	virtual rvm::TokenMinterFlag			GetTokenMinterState(rvm::TokenId tid, rvm::ContractId contract) const override;

	virtual rvm::ConstAddress*		GetBlockCreator() const override;
	virtual uint64_t				GetBlockHeight() const override { return _BlockHeight; }
	virtual uint64_t				GetBlockTime() const override { return _GetBlockTime(); }
	virtual uint32_t				GetShardIndex() const override { return _ShardIndex; }
	virtual uint32_t				GetShardOrder() const override { return _ShardOrder; }
	virtual const rvm::HashValue*	GetPrevBlockHash() const override { return &_PrevBlockHash; }
	virtual rvm::ScaleOutMode		GetScalingUpMode() const override { return rvm::ScaleOutMode::None; }

public:
	// returns null if the state doesn't exist
	virtual rvm::ConstStateData		GetState(rvm::ContractScopeId cid) const override;  // will return the original state, even if modified when execution
	virtual rvm::ConstStateData		GetState(rvm::ContractScopeId cid, const rvm::ScopeKey* key) const override;  // will return the original state, even if modified when execution

protected:
	/////////////////////////////////////////////////////
	// From rvm::NativeTokens
	virtual uint32_t				GetCount() const override;
	virtual rvm::ConstNativeToken	Get(uint32_t idx) const override;
	virtual void					Release() override { ASSERT(0); }

	/////////////////////////////////////////////////////
	// From rvm::ExecutionContext::InvocationInfo
	virtual	const rvm::HashValue*	GetTxnHash(rvm::HashValue* hash_out = nullptr) const override; // hash_out can be nullptr is current utxn is the first one in a relay group, or in a non-grouped txn
	virtual uint32_t				GetMicroTxnIndex() const override;
	virtual rvm::ScopeKey			GetScopeTarget() const override;
	virtual rvm::OpCode				GetOpCode() const override { ASSERT(_pTxn); return _pTxn->Op; }
	virtual rvm::ContractInvokeId	GetContractId() const override { return _pTxn ? _pTxn->Contract : rvm::ContractInvokeIdInvalid; }
	virtual const rvm::NativeTokens*GetNativeTokenSupplied() const override { ASSERT(_pTxn && _pTxn->Type == rvm::InvokeContextType::Normal); return this; }
	virtual uint64_t				GetTimestamp() const override { ASSERT(_pTxn); return _pTxn->Timestamp; }
	virtual rvm::InvokeContextType	GetInvokeType() const override { return _pTxn ? _pTxn->Type : rvm::InvokeContextType::System; }
	// normal txn
	virtual rvm::ConstAddress*		GetSigner(uint32_t i) const override { return _pTxn ? (_pTxn->IsRelay()?nullptr:&_pTxn->Target.addr) : nullptr;	}
	virtual uint32_t				GetSignerCount() const override { return _pTxn ? (_pTxn->IsRelay()?0:1) : 0; }
	virtual bool					IsSignedBy(rvm::ConstAddress* addr) const override { ASSERT(_pTxn); return !_pTxn->IsRelay() && rt::IsEqual(*addr, _pTxn->Target.addr); }
	// relay txn
	virtual uint32_t				GetOriginatedShardIndex() const override { ASSERT(_pTxn && _pTxn->IsRelay()); return _pTxn->OriginateShardIndex; }
	virtual uint32_t				GetOriginatedShardOrder() const override { ASSERT(_pTxn && _pTxn->IsRelay()); return _pTxn->OriginateShardOrder; }
	virtual uint64_t				GetOriginatedBlockHeight() const override { ASSERT(_pTxn && _pTxn->IsRelay()); return _pTxn->OriginateHeight; }
	virtual rvm::ConstAddress*		GetInitiator() const override;

	/////////////////////////////////////////////////////
	// From rvm::ExecutionContext
	virtual void					Randomize(uint8_t* fill, uint32_t size) override { _Rand.Randomize(fill, size); }
	virtual uint8_t*				AllocateStateMemory(uint32_t dataSize) override;
	virtual void					DiscardStateMemory(uint8_t* state) override;		// `state` must be allocated from AllocateStateMemory
	virtual void					CommitNewState(rvm::ContractInvokeId ciid, uint8_t* state) override;  // `state` must be allocated from AllocateStateMemory
	virtual void					CommitNewState(rvm::ContractInvokeId ciid, const rvm::ScopeKey* key, uint8_t* state) override;  // `state` must be allocated from AllocateStateMemory

	template<rvm::ContractInvokeId ciid>
	void							CommitCoreState(const typename rvm::TypeTraits<typename CoreContractTypeTraits<ciid>::StateType>::Mutable& x)
									{
										typedef typename CoreContractTypeTraits<ciid>::StateType IMMUTABLE;
										auto* state = VERIFY((IMMUTABLE*)AllocateStateMemory(IMMUTABLE::GetEmbeddedSize(x)));
										state->Embed(x);
										CommitNewState(ciid, (uint8_t*)state);
									}

	virtual bool					EmitRelayToScope(rvm::ContractInvokeId cid, const rvm::ScopeKey* key, rvm::OpCode opcode, const rvm::ConstData* args_serialized, uint32_t gas_redistribution_weight) override;
	virtual bool					EmitRelayToGlobal(rvm::ContractInvokeId cid, rvm::OpCode opcode, const rvm::ConstData* args_serialized, uint32_t gas_redistribution_weight) override;
	virtual bool					EmitRelayDeferred(rvm::ContractInvokeId cid, rvm::OpCode opcode, const rvm::ConstData* args_serialized, uint32_t gas_redistribution_weight) override;
	virtual bool					EmitBroadcastToShards(rvm::ContractInvokeId cid, rvm::OpCode opcode, const rvm::ConstData* args_serialized, uint32_t gas_redistribution_weight) override;

	virtual rvm::ContractVersionId	DeployUnnamedContract(rvm::ContractVersionId deploy_initiator, uint64_t initiator_dappname, const rvm::DeployedContract* origin_deploy) override { ASSERT(0); return rvm::ContractVersionIdInvalid; } // for global shard only
	virtual rvm::ExecuteResult		Invoke(uint32_t gas_limit, rvm::ContractInvokeId contract, rvm::OpCode opcode, const rvm::ConstData* args_serialized) override; // return pointer will be invalid after next call of `Invoke` or `SetReturnValue`

	// set return value of current function being invoking
	virtual void					SetReturnValue(const rvm::ConstData* args_serialized) override;
	virtual uint8_t*				SetReturnValueClaim(uint32_t size_estimated) override { _ReturnVal.SetSize(size_estimated); return _ReturnVal.Begin(); }
	virtual void					SetReturnValueFinalize(uint32_t size_finalized) override { ASSERT(size_finalized<=_ReturnVal.GetSize()); _ReturnVal.ShrinkSize(size_finalized); }
	virtual bool					NativeTokensDeposit(const rvm::ConstNativeToken* tokens, uint32_t count) override;
	virtual void					NativeTokensSupplyChange(const rvm::ConstNativeToken* tokens, uint32_t count) override;

public:
	SimuShard(ChainSimulator* simu, uint64_t time_base, uint32_t shard_order, uint32_t shard_index, SimuGlobalShard* global); // normal shard
	SimuShard(ChainSimulator* simu, uint64_t time_base, uint32_t shard_order); // global shard
	virtual ~SimuShard(){ Term(); }

	void		Init();
	void		Term();
	bool		IsGlobal() const { return _ShardIndex == rvm::GlobalShard; }

	void		SetState(rvm::ContractScopeId cid, SimuState* s);
	void		SetState(rvm::ContractScopeId cid, const rvm::Address& target, SimuState* s);

	bool		HavePendingTxns() const { return _PendingTxns.GetSize() || _PendingRelayTxns.GetSize(); }
	void		PushNormalTxn(SimuTxn* t);
	void		PushRelayTxn(SimuTxn** relay_txns, uint32_t count);
	void		Step();  // create next block and stop
	void		LogInfo();

	bool		JsonifyAllAddressStates(rt::Json& append, const rt::BufferEx<User>& Users, rvm::ContractId cid);
	bool		JsonifyBlocks(rt::Json& append, int64_t height = -1);
	bool		JsonifyAddressState(rt::Json& append, const rvm::Address* targetAddr, uint32_t userId, rvm::ContractId cid);
	bool		JsonifyScopeState(rt::Json& append, SimuAddressContract key, bool allState);
	void		JsonifyAddressStateWithoutGrouping(rt::Json& append, rvm::ContractId cid);
	bool		JsonifyShardState(rt::Json& append, rvm::ContractId cid);
	void		JsonifyProfile(rt::Json& append) const;
	const		rt::BufferEx<SimuTxn*>	GetTxnTrace(SimuTxn* txn) const;
	void		AppendToTxnTrace(SimuTxn* origin, SimuTxn* relay);
	bool		ConfirmedTxnJsonify(const SimuTxn* txn, rt::Json& append) const;
	size_t		GetPendingTxnCount() const {return _PendingTxns.GetSize();}
	auto		GetAddressState(SimuAddressContract k) { return (const SimuState*)_AddressStates.Get(k); }
	void		PushIntraRelay(SimuTxn* t) { _IntraRelayTxns.Push(t); }
#ifndef __APPLE__
	std::pmr::unsynchronized_pool_resource* GetMemPool() { return &_MemoryPool; }
#endif
};

} // namespace oxd
