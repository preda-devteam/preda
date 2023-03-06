#pragma once
#include "shard_data.h"


namespace oxd
{

class Simulator;
class SimuShard;
class SimuGlobalShard;

class ExecuteUnit
{
	friend class Simulator;
	rvm::ExecuteUnit*	pUnits[(int)rvm::EngineId::Max];

public:
	auto*	Get(rvm::EngineId e) const { return pUnits[(int)e]; }
	void	Release(){ for(auto& p : pUnits)_SafeRelease(p); }
	ExecuteUnit(){ rt::Zero(pUnits); }
	~ExecuteUnit(){ Release(); }
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
	ExecuteUnit					_ExecUnits;
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
	bool						_IsGlobalScope() const { return (SimuShard*)_pGlobalShard == this; }
	uint64_t					_GetBlockTime() const { return _BlockTimeBase + _BlockHeight*SIMU_BLOCK_INTERVAL; }
	SimuTxn*					_CreateRelayTxn(rvm::ContractId cid, rvm::OpCode opcode, const rvm::ConstData* args_serialized, rvm::BuildNum build_num = (rvm::BuildNum)0) const;

protected:
	/////////////////////////////////////////////////////
	// From rvm::ExecutionContext::ChainState
	virtual rvm::DAppId				GetDAppByName(const rvm::ConstString* dapp_name) const override;
	virtual rvm::ContractId			GetContractByName(rvm::DAppId dapp_id, const rvm::ConstString* contract_name) const override;

	// Route to global or disable
	virtual rvm::BuildNum			GetContractEffectiveBuild(rvm::ContractId contract) const override;
	virtual const rvm::ContractDID*	GetContractDeploymentIdentifier(rvm::ContractId contract, rvm::BuildNum version) const override; // return on chain CDI of a contract of specific version
	virtual const rvm::InterfaceDID*GetInterfaceDeploymentIdentifier(rvm::InterfaceId contract) const override; // return on chain CDI of a contract of specific version

	virtual rvm::ConstAddress*		GetDAppOwner(rvm::DAppId dapp_id) const override { return nullptr; }
	virtual uint64_t				GetDAppCreationTime(rvm::DAppId dapp_id) const override { return 1660869355000ULL; }
	virtual rvm::TokenId			GetTokenBySymbol(const rvm::ConstString* token_name) const override { return rvm::TokenIdInvalid; }
	virtual	rvm::ConstString		GetTokenSymbol(rvm::TokenId id) const override { return { nullptr, 0 }; }

	virtual rvm::ConstAddress*		GetBlockCreator() const override;
	virtual uint64_t				GetBlockHeight() const override { return _BlockHeight; }
	virtual uint64_t				GetBlockTime() const override { return _GetBlockTime(); }
	virtual uint32_t				GetShardIndex() const override { return _ShardIndex; }
	virtual uint32_t				GetShardOrder() const override { return _ShardOrder; }
	virtual const rvm::HashValue*	GetBlockHash() const override { return &_BlockHash; }
	virtual rvm::ScaleOutMode		GetScalingUpMode() const override { return rvm::ScaleOutMode::None; }

public:
	// returns null if the state doesn't exist
	virtual rvm::ConstStateData		GetState(rvm::ContractScopeId cid) const override;  // will return the original state, even if modified when execution
	virtual rvm::ConstStateData		GetState(rvm::ContractScopeId cid, const rvm::ScopeKey* key) const override;  // will return the original state, even if modified when execution

protected:
	/////////////////////////////////////////////////////
	// From rvm::ExecutionContext::InvocationInfo
	virtual rvm::ScopeKey			GetScopeTarget() const override;
	virtual rvm::OpCode				GetOpCode() const override { ASSERT(_pTxn); return _pTxn->Op; }
	virtual rvm::ContractScopeId	GetContractId() const override { ASSERT(_pTxn); return _pTxn->Contract; }
	virtual rvm::BuildNum			GetBuildNum() const override { ASSERT(_pTxn); return _pTxn->BuildNum; }
	virtual uint64_t				GetTimestamp() const override { ASSERT(_pTxn); return _pTxn->Timestamp; }
	virtual rvm::InvokeContextType	GetInvokeType() const override { ASSERT(_pTxn); return _pTxn->Type; }
	// normal txn
	virtual rvm::ConstAddress*		GetSigner(uint32_t i) const override { 
		ASSERT(_pTxn && i==0); 
		return _pTxn->IsRelay()?nullptr:&_pTxn->Target;
	}
	virtual uint32_t				GetSignerCount() const override { ASSERT(_pTxn); return _pTxn->IsRelay()?0:1; }
	virtual bool					IsSignedBy(rvm::ConstAddress* addr) const override { ASSERT(_pTxn); return !_pTxn->IsRelay() && rt::IsEqual(*addr, _pTxn->Target); }
	// relay txn
	virtual uint32_t				GetOriginatedShardIndex() const override { ASSERT(_pTxn && _pTxn->IsRelay()); return _pTxn->OriginateShardIndex; }
	virtual uint32_t				GetOriginatedShardOrder() const override { ASSERT(_pTxn && _pTxn->IsRelay()); return _pTxn->OriginateShardOrder; }
	virtual uint64_t				GetOriginatedBlockHeight() const override { ASSERT(_pTxn && _pTxn->IsRelay()); return _pTxn->OriginateHeight; }
	virtual rvm::ConstAddress*		GetInitiator() const override { ASSERT(_pTxn && _pTxn->IsRelay()); return &_pTxn->Initiator; }

	/////////////////////////////////////////////////////
	// From rvm::ExecutionContext
	virtual uint64_t				GetRandomNumber() override { return _Rand.GetNext() | (((uint64_t)_Rand.GetNext())<<32U); }
	virtual uint8_t*				AllocateStateMemory(uint32_t dataSize) override;
	virtual void					DiscardStateMemory(uint8_t* state) override;		// `state` must be allocated from AllocateStateMemory
	virtual void					CommitNewState(rvm::BuildNum build_num, rvm::ContractScopeId cid, uint8_t* state) override;  // `state` must be allocated from AllocateStateMemory
	virtual void					CommitNewState(rvm::BuildNum build_num, rvm::ContractScopeId cid, const rvm::ScopeKey* key, uint8_t* state) override;  // `state` must be allocated from AllocateStateMemory

	virtual bool					EmitRelayToAddress(rvm::BuildNum build_num, rvm::ConstAddress* target, rvm::ContractScopeId cid, rvm::OpCode opcode, const rvm::ConstData* args_serialized, uint32_t gas_redistribution_weight) override;
	virtual bool					EmitRelayToGlobal(rvm::BuildNum build_num, rvm::ContractScopeId cid, rvm::OpCode opcode, const rvm::ConstData* args_serialized, uint32_t gas_redistribution_weight) override;
	virtual bool					EmitBroadcastToShards(rvm::BuildNum build_num, rvm::ContractScopeId cid, rvm::OpCode opcode, const rvm::ConstData* args_serialized, uint32_t gas_redistribution_weight) override;

	virtual rvm::ExecuteResult		Invoke(uint32_t gas_limit, rvm::BuildNum build_num, rvm::ContractScopeId contract, rvm::OpCode opcode, const rvm::ConstData* args_serialized) override; // return pointer will be invalid after next call of `Invoke` or `SetReturnValue`

	// set return value of current function being invoking
	virtual void					SetReturnValue(const rvm::ConstData* args_serialized) override;
	virtual uint8_t*				SetReturnValueClaim(uint32_t size_estimated) override { _ReturnVal.SetSize(size_estimated); return _ReturnVal.Begin(); }
	virtual void					SetReturnValueFinalize(uint32_t size_finalized) override { ASSERT(size_finalized<=_ReturnVal.GetSize()); _ReturnVal.ShrinkSize(size_finalized); }

public:
	SimuShard(Simulator* simu, uint64_t time_base, uint32_t shard_order, uint32_t shard_index, SimuGlobalShard* global); // normal shard
	SimuShard(Simulator* simu, uint64_t time_base, uint32_t shard_order); // global shard
	virtual ~SimuShard(){ Term(); }

	void	Init();
	void	Term();
	bool	IsGlobal() const { return _ShardIndex == rvm::GlobalShard; }

	void	SetState(rvm::ContractId cid, rvm::Scope scope, SimuState* s);
	void	SetState(rvm::ContractId cid, rvm::Scope scope, const rvm::Address& target, SimuState* s);

	bool	HavePendingTxns() const { return _PendingTxns.GetSize() || _PendingRelayTxns.GetSize(); }
	void	PushTxn(SimuTxn* t);
	void	PushTxn(SimuTxn** relay_txns, uint32_t count);
	void	Step();  // create next block and stop
	void	LogInfo();
#ifdef _VIZ
	bool	JsonifyAllAddressStates(rt::Json& append, const rt::BufferEx<User>& Users, rvm::ContractId cid);
	bool	JsonifyBlocks(rt::Json& append, int64_t height = -1);
	bool	JsonifyAddressState(rt::Json& append, rvm::Address& Address, const rt::BufferEx<User>& Users, rvm::ContractId cid);
	bool	JsonifyShardState(rt::Json& append, rvm::ContractId cid);
	void	JsonifyProfile(rt::Json& append) const;
	const   rt::BufferEx<SimuTxn*>	GetTxnTrace(SimuTxn* txn) const;
	void	AppendToTxnTrace(SimuTxn* origin, SimuTxn* relay);
	auto	GetConfirmTxn(const SimuTxn* txn) const -> rvm::InvokeResult*;
	size_t	GetPendingTxnCount() const {return _PendingTxns.GetSize();}
	const SimuState* GetAddressState(SimuAddressContract k) { return _AddressStates.Get(k); }
#endif
	operator const rvm::ChainState* () const { return this; }
};

} // namespace oxd
