#pragma once
#include "shard_data.h"


namespace oxd
{

class Simulator;
class SimuShard;
class SimuGlobalShard;

class ExecutionUnit
{
	friend class Simulator;
	rvm::ExecutionUnit*	pUnits[(int)rvm::EngineId::Max];

public:
	rvm::ExecutionUnit* Get(rvm::EngineId e) const { if (e >= rvm::EngineId::Max) return nullptr; return pUnits[(int)e]; }
	void	Release(){ for(auto& p : pUnits)_SafeRelease(p); }
	ExecutionUnit(){ rt::Zero(pUnits); }
	~ExecutionUnit(){ Release(); }
};

class RelayEmission
{
protected:
	rt::BufferEx<SimuTxn*>				_ToGlobal;
	rt::Buffer<rt::BufferEx<SimuTxn*>>	_ToShards;

	Simulator*  _pSimulator;
	SimuShard*  _pShard;

public:
	RelayEmission(Simulator* s, SimuShard* shard);
	~RelayEmission();
	void	Collect(SimuTxn* origin, rt::BufferEx<SimuTxn*>& txns);
	void	Dispatch();  // dispatch all collected and clean up
};

struct ShardStates
{
	SimuChainState<rvm::ContractScopeId>	_ShardStates;	// in IsGlobal(), it is global state
	SimuChainState<ShardStateKeyObj>		_ShardKeyedStates;

	void	Revert();
	void	Commit(ShardStates& to); // this will be clear
};

class SimuShard: protected rvm::ExecutionContext
			   , protected ShardStates
{
protected:
	ExecutionUnit				_ExecUnits;
	Simulator*					_pSimulator = nullptr;
	SimuGlobalShard*			_pGlobalShard = nullptr;

	PendingTxns					_PendingTxns;
	PendingTxns					_PendingRelayTxns;
	uint32_t					_ConfirmedTxnCount;

	SimuChainState<SimuAddressContract>		_AddressStates; // shard scope only

	rt::BufferEx<SimuBlock*>	_Chain;
	os::Event					_GoNextBlock;
	os::Thread					_BlockCreator;
	void						_BlockCreationRoutine();
#ifdef _VIZ
	ext::fast_map<SimuTxn*, rt::BufferEx<SimuTxn*>>	_TxnTrace;
#endif
protected:
	// current block being executing
	uint64_t					_BlockTimeBase;
	uint64_t					_BlockHeight;
	rvm::HashValue				_BlockHash;
	rvm::HashValue				_PrevBlockHash;
	uint32_t					_ShardIndex; // = -1 for global shard
	uint32_t					_ShardOrder;
	rt::Randomizer				_Rand;
	uint64_t					_TotalGasBurnt;
	rt::BufferEx<ConfirmTxn>	_TxnExecuted;
	RelayEmission				_TxnEmitted;

	// current transaction being executing
	SimuTxn*					_pTxn = nullptr;
	rt::BufferEx<uint8_t>		_ReturnVal;
	rt::BufferEx<SimuTxn*>		_RelayEmitted;  // all be dispatched and cleared once txn execution is done
	bool						_IsAddressScope() const { return _pTxn&&_pTxn->GetScope() == rvm::Scope::Address; }
	rvm::Scope					_GetScope() const { if(_pTxn) return _pTxn->GetScope(); return rvm::ScopeInvalid; }
	bool						_IsGlobalScope() const { return (SimuShard*)_pGlobalShard == this; }
	uint64_t					_GetBlockTime() const { return _BlockTimeBase + _BlockHeight*SIMU_BLOCK_INTERVAL; }
	SimuTxn*					_CreateRelayTxn(rvm::ContractInvokeId cid, rvm::OpCode opcode, const rvm::ConstData* args_serialized) const;

protected:
	/////////////////////////////////////////////////////
	// From rvm::ExecutionContext::ChainState
	virtual rvm::DAppId						GetDAppByName(const rvm::ConstString* dapp_name) const override;
	virtual rvm::ContractVersionId			GetContractByName(const rvm::ConstString* dapp_contract_name) const override;
	virtual rvm::BuildNum					GetContractEffectiveBuild(rvm::ContractId contract) const override;
	virtual const rvm::DeployedContract*	GetContractDeployed(rvm::ContractVersionId) const override;
	virtual bool							IsTokenMintAllowed(rvm::TokenId tid, rvm::ContractId contract) const override;

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
	// From rvm::ExecutionContext::InvocationInfo
	virtual	const rvm::HashValue*	GetTxnHash(rvm::HashValue* hash_out = nullptr) const override; // hash_out can be nullptr is current utxn is the first one in a relay group, or in a non-grouped txn
	virtual uint32_t				GetMicroTxnIndex() const override;
	virtual rvm::ScopeKey			GetScopeTarget() const override;
	virtual rvm::OpCode				GetOpCode() const override { ASSERT(_pTxn); return _pTxn->Op; }
	virtual rvm::ContractInvokeId	GetContractId() const override {return _pTxn ? _pTxn->Contract : rvm::ContractInvokeIdInvalid; }
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
	virtual uint64_t				GetRandomNumber() override { return _Rand.GetNext() | (((uint64_t)_Rand.GetNext())<<32U); }
	virtual uint8_t*				AllocateStateMemory(uint32_t dataSize) override;
	virtual void					DiscardStateMemory(uint8_t* state) override;		// `state` must be allocated from AllocateStateMemory
	virtual void					CommitNewState(rvm::ContractInvokeId cid, uint8_t* state) override;  // `state` must be allocated from AllocateStateMemory
	virtual void					CommitNewState(rvm::ContractInvokeId cid, const rvm::ScopeKey* key, uint8_t* state) override;  // `state` must be allocated from AllocateStateMemory

	virtual bool					EmitRelayToScope(rvm::ContractInvokeId cid, const rvm::ScopeKey* key, rvm::OpCode opcode, const rvm::ConstData* args_serialized, uint32_t gas_redistribution_weight) override;
	virtual bool					EmitRelayToGlobal(rvm::ContractInvokeId cid, rvm::OpCode opcode, const rvm::ConstData* args_serialized, uint32_t gas_redistribution_weight) override;
	virtual bool					EmitBroadcastToShards(rvm::ContractInvokeId cid, rvm::OpCode opcode, const rvm::ConstData* args_serialized, uint32_t gas_redistribution_weight) override;

	virtual rvm::ContractVersionId	DeployUnnamedContract(rvm::ContractVersionId deploy_initiator, uint64_t initiator_dappname, const rvm::DeployedContract* origin_deploy) override { ASSERT(0); return rvm::ContractVersionIdInvalid; } // for global shard only
	virtual rvm::ExecuteResult		Invoke(uint32_t gas_limit, rvm::ContractInvokeId contract, rvm::OpCode opcode, const rvm::ConstData* args_serialized) override; // return pointer will be invalid after next call of `Invoke` or `SetReturnValue`

	// set return value of current function being invoking
	virtual void					SetReturnValue(const rvm::ConstData* args_serialized) override;
	virtual uint8_t*				SetReturnValueClaim(uint32_t size_estimated) override { _ReturnVal.SetSize(size_estimated); return _ReturnVal.Begin(); }
	virtual void					SetReturnValueFinalize(uint32_t size_finalized) override { ASSERT(size_finalized<=_ReturnVal.GetSize()); _ReturnVal.ShrinkSize(size_finalized); }
	virtual bool					CoreWalletWithdraw(rvm::TokenId tid, const rvm::BigNum* amount) override { ASSERT(0); return false; }
	virtual void					CoreWalletDeposit(rvm::TokenId tid, const rvm::BigNum* amount) override { ASSERT(0); }


public:
	SimuShard(Simulator* simu, uint64_t time_base, uint32_t shard_order, uint32_t shard_index, SimuGlobalShard* global); // normal shard
	SimuShard(Simulator* simu, uint64_t time_base, uint32_t shard_order); // global shard
	virtual ~SimuShard(){ Term(); }

	void		Init();
	void		Term();
	bool		IsGlobal() const { return _ShardIndex == rvm::GlobalShard; }

	void		SetState(rvm::ContractScopeId cid, SimuState* s);
	void		SetState(rvm::ContractScopeId cid, const rvm::Address& target, SimuState* s);

	bool		HavePendingTxns() const { return _PendingTxns.GetSize() || _PendingRelayTxns.GetSize(); }
	void		PushTxn(SimuTxn* t);
	void		PushTxn(SimuTxn** relay_txns, uint32_t count);
	void		Step();  // create next block and stop
	void		LogInfo();

#ifdef _VIZ
	bool		JsonifyAllAddressStates(rt::Json& append, const rt::BufferEx<User>& Users, rvm::ContractId cid);
	bool		JsonifyBlocks(rt::Json& append, int64_t height = -1);
	bool		JsonifyAddressState(rt::Json& append, rvm::Address& Address, const rt::BufferEx<User>& Users, rvm::ContractId cid);
	bool		JsonifyShardState(rt::Json& append, rvm::ContractId cid);
	void		JsonifyProfile(rt::Json& append) const;
	const		rt::BufferEx<SimuTxn*>	GetTxnTrace(SimuTxn* txn) const;
	void		AppendToTxnTrace(SimuTxn* origin, SimuTxn* relay);
	auto		GetConfirmTxn(const SimuTxn* txn) const -> rvm::InvokeResult*;
	size_t		GetPendingTxnCount() const {return _PendingTxns.GetSize();}
	auto		GetAddressState(SimuAddressContract k) { return (const SimuState*)_AddressStates.Get(k); }
#endif
};

} // namespace oxd
