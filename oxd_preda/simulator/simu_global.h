#pragma once
#include "../native/abi/vm_interfaces.h"
#include "simu_shard.h"


namespace oxd
{

class BuildContracts: protected rvm::LogMessageOutput
{
protected:
	rvm::RvmEngine*				_pEngine = nullptr;
	rvm::EngineId				_EngineId = rvm::EngineId::Unassigned;
	rvm::DAppId					_DAppId = rvm::DAppIdInvalid;
	rt::String_Ref				_DAppName;

	rt::Buffer<rt::String_Ref>	_Sources;
	rt::Buffer<rt::String_Ref>	_Filenames;
	rvm::CompiledContracts*		_pCompiled = nullptr;
	DataBuffer					_CompileDependency;

	rt::BufferEx<rvm::ContractDID>		_ContractDeploymentIds;
	rt::BufferEx<rvm::InterfaceDID*>	_InterfaceDeploymentIds;
	ext::fast_map<rt::String, rt::String> _ContractToFN;
protected:
	enum Stage
	{
		STAGE_SOURCE,
		STAGE_COMPILE,
		STAGE_LINK,
		STAGE_DEPLOY
	};
	Stage						_Stage = STAGE_SOURCE;

	//////////////////////////////////////////////////////
	// From rvm::LogMessageOutput
	virtual void				Log(rvm::LogMessageType type, uint32_t code, uint32_t unitIndex, uint32_t line, uint32_t lineOffset, const rvm::ConstString *message) override;

public:
	BuildContracts(rvm::RvmEngine* e, rvm::EngineId eid):_pEngine(e), _EngineId(eid){}
	~BuildContracts(){ Term(); }

	void		Init(const rt::String_Ref& dapp, rvm::DAppId dapp_id, rvm::EngineId eid);
	void		Term();
	uint32_t	GetSourceCount() const { return (uint32_t)_Sources.GetSize(); }
	operator	const rvm::CompiledContracts* () const { return VERIFY(_pCompiled); }

	void		AddSource(const rt::String_Ref& code, const rt::String_Ref& fn = nullptr);
	bool		Compile(const rvm::ChainState* global_state);
	bool		Link();
	bool		VerifyDependency(const rvm::ChainState* global_state) const;
	bool		Deploy(rvm::ExecuteUnit* exec, rvm::ExecutionContext* exec_ctx, uint32_t gas_limit);

	auto*		GetContractDeploymentIds() const { ASSERT(_Stage == STAGE_DEPLOY); return (const rvm::ContractDID*)_ContractDeploymentIds; }
	auto		GetInterfaceDeploymentIds() const { ASSERT(_Stage == STAGE_DEPLOY); return (const rvm::InterfaceDID* const*)_InterfaceDeploymentIds.Begin(); }

	bool		IsCompiled() const { return _Stage >= STAGE_COMPILE; }
	void		GetContractsInfo(rt::Json& json, const rvm::ChainState* global_state) const; // _Stage >= STAGE_COMPILE
};

#pragma pack(push, 1)
struct ContractVersionedId
{
	TYPETRAITS_DECLARE_POD;
	union {
	rvm::ContractId		Contract;
	rvm::InterfaceId	Interface;
	};
	rvm::BuildNum		Version;

	ContractVersionedId(){}
	ContractVersionedId(rvm::ContractId cid, rvm::BuildNum v){ Contract = cid; Version = v; }
	ContractVersionedId(rvm::InterfaceId ifid, rvm::BuildNum v){ Interface = ifid; Version = v; }
	bool operator == (const ContractVersionedId& x) const { return rt::IsEqual(*this, x); }
};

struct ContractFunction
{
	rvm::ContractId	Contract;
	rvm::OpCode		Op;
	ContractFunction(){ rt::Zero(*this); }
};
#pragma pack(pop)

struct ContractsDatabase
{
#pragma pack(push, 1)
	struct ContractInfo
	{
		rvm::BuildNum		Version;
		rvm::DeploymentId	DeploymentId;
		rvm::Scope			ScopeOfOpcode[256];
		ContractInfo(){ Version = (rvm::BuildNum)0; }
	};
#pragma pack(pop)

	ext::fast_map_ptr<ContractVersionedId, ContractInfo, rt::_details::hash_compare_fix<ContractVersionedId>>	_ContractInfo; // includes interfaces as well
	ext::fast_map<rt::String, rvm::ContractId>			_Contracts;
	ext::fast_map<rvm::ContractId, rvm::BuildNum>		_ContractBuildNumLatest;
	ext::fast_map<rt::String, ContractFunction>			_ContractFunctions;
	uint32_t											_NextContractSN = 1;

	void	Reset(const ContractsDatabase& x);
	void	Commit(ContractsDatabase& x);
	void	Revert();
};

class SimuGlobalShard: public SimuShard
					 , protected ContractsDatabase
{	// SimuGlobalShard is single-threaded when writing
	// SimuGlobalShard is being read when there is no writing thread
	friend class SimuShard;
	friend class Simulator;

protected:
	bool								_bDeploying;
	ContractsDatabase					_DeployingDatabase;
	ShardStates							_DeployingStates;

protected:
	rvm::BuildNum						_GetContractEffectiveBuild(rvm::ContractId contract) const;
	const rvm::ContractDID*				_GetContractDeploymentIdentifier(rvm::ContractId cid, rvm::BuildNum version = rvm::BuildNumLatest) const;
	const rvm::InterfaceDID*			_GetInterfaceDeploymentIdentifier(rvm::InterfaceId ifid, rvm::BuildNum version = rvm::BuildNumLatest) const;
	rvm::ContractId						_GetContractByName(rvm::DAppId dapp_id, const rvm::ConstString* contract_name) const;
	void								_FinalizeFunctionInfo(const ContractVersionedId& cvid, const rt::String_Ref& func_prefix, const rvm::DeploymentId& deploy_id, const rvm::Interface* info);

protected:
	// From ChainState
	virtual rvm::ConstStateData			GetState(rvm::ContractScopeId contract) const override;
	virtual rvm::ConstStateData			GetState(rvm::ContractScopeId contract, const rvm::ScopeKey* key) const override;

	virtual rvm::BuildNum				GetContractEffectiveBuild(rvm::ContractId contract) const override { return _GetContractEffectiveBuild(contract); }
	virtual const rvm::ContractDID*		GetContractDeploymentIdentifier(rvm::ContractId contract, rvm::BuildNum version) const override { return _GetContractDeploymentIdentifier(contract, version); }
	virtual const rvm::InterfaceDID*	GetInterfaceDeploymentIdentifier(rvm::InterfaceId contract) const override { return _GetInterfaceDeploymentIdentifier(contract); }

	// From ExecutionContext
	virtual void						CommitNewState(rvm::BuildNum version, rvm::ContractScopeId contract, uint8_t* state_memory) override;
	virtual void						CommitNewState(rvm::BuildNum version, rvm::ContractScopeId contract, const rvm::ScopeKey* key, uint8_t* state_memory) override;

public:
	void		DeployBegin(SimuTxn* txn);
	void		DeployEnd(bool commit);
	bool		AllocateContractIds(const rvm::CompiledContracts* linked);
	bool		FinalizeDeployment(	const rvm::CompiledContracts* deployed, 
									const rvm::ContractDID* contract_deployment_ids,
									const rvm::InterfaceDID* const* interface_deployment_ids
				);
	void		Term();
	auto&		GetExecuteUnits(){ return _ExecUnits; }

	SimuGlobalShard(Simulator* simu, uint64_t time_base, uint32_t shard_order);
	virtual ~SimuGlobalShard(){ Term(); }
};

} // namespace oxd