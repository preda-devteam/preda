#pragma once
#include "../native/abi/vm_interfaces.h"
#include "simu_shard.h"


namespace oxd
{

class BuildContracts: protected rvm::LogMessageOutput
{
	friend class SimuGlobalShard;
protected:
	rvm::RvmEngine*				_pEngine = nullptr;
	rvm::EngineId				_EngineId = rvm::EngineId::Unassigned;
	rvm::DAppId					_DAppId = rvm::DAppIdInvalid;
	rt::String_Ref				_DAppName;

	rt::BufferEx<rt::String>	_Sources;
	rt::BufferEx<rt::String>	_ConstructorArgs;
	rt::BufferEx<rt::String>	_Filenames;
	rvm::CompiledModules*		_pCompiled = nullptr;
	rvm::DataBufferImpl			_CompileDependency;

	rt::BufferEx<rvm::ConstData>			_ContractDeployArgs;
	rt::BufferEx<rvm::ContractModuleID>		_ContractModuleIds;
	rt::BufferEx<rvm::DataBufferImpl>		_ContractDeployStub;

	void						_ResetContractWorkData(uint32_t size = 0);

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
	ext::fast_map<rt::String, rt::String>	_ContractToFilename;

	BuildContracts(rvm::RvmEngine* e, rvm::EngineId eid):_pEngine(e), _EngineId(eid){}
	~BuildContracts(){ Term(); }

	void		Init(const rt::String_Ref& dapp, rvm::DAppId dapp_id, rvm::EngineId eid);
	void		Term();
	uint32_t	GetSourceCount() const { return (uint32_t)_Sources.GetSize(); }

	void		AddContractCode(const rt::String_Ref& code, const rt::String_Ref& deploy_arg, const rt::String_Ref& fn = nullptr);
	bool		Compile(bool checkDeployArg = true);
	bool		Link();
	bool		VerifyDependency(const rvm::GlobalStates* global_state) const;
	bool		Deploy(rvm::ExecutionUnit* exec, rvm::ExecutionContext* exec_ctx);
	rvm::InvokeResult	InvokeConstructor(rvm::ExecutionUnit* exec, rvm::ExecutionContext* exec_ctx, uint32_t gas_limit);

	auto*		GetContractModuleIds() const { ASSERT(_Stage == STAGE_DEPLOY); return (const rvm::ContractModuleID*)_ContractModuleIds; }
	bool		IsCompiled() const { return _Stage >= STAGE_COMPILE; }
	void		GetContractsInfo(rt::Json& json) const; // _Stage >= STAGE_COMPILE
};

#pragma pack(push, 1)
struct ContractFunction
{
	rvm::ContractId	Contract;
	rvm::OpCode		Op;
	rt::String		FunctionSignature;
	ContractFunction(){ rt::Zero(*this); }
};
#pragma pack(pop)

struct ContractsDatabase
{
	struct ContractInfo
	{
		rvm::Scope				ScopeOfOpcode[256];
		rvm::DeployedContract	Deployment;
		
		void			Release(){ _SafeFree32AL_ConstPtr(this); }
		uint32_t		GetSize() const { return offsetof(ContractInfo, Deployment.Stub) + Deployment.StubSize; }
		ContractInfo*	Clone() const;
	};

	typedef ext::fast_map_ptr<rvm::ContractVersionId, ContractInfo> t_ContractInfo;
	// unnamed + named
	t_ContractInfo												_ContractInfo; // includes interfaces as well
	ext::fast_map<rvm::ContractId, rvm::BuildNum>				_ContractBuildNumLatest;
	// named only
	ext::fast_map<rt::String, rvm::ContractVersionId>			_Contracts;
	ext::fast_map<rt::String, rt::BufferEx<ContractFunction>>	_ContractFunctions;
	ext::fast_map<rt::String, rvm::EngineId>					_ContractEngine;
	uint32_t													_NextContractSN = 1;

	void	Reset(const ContractsDatabase& x);
	void	Commit(ContractsDatabase& x);
	void	Revert();
	auto	FindContractInfo(const rvm::ContractModuleID& mid) -> const ContractInfo*;
	~ContractsDatabase(){ Revert(); }
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
	rvm::DAppId							_GetDAppByName(const rvm::ConstString* dapp_name) const;
	rvm::ContractVersionId				_GetContractByName(const rvm::ConstString* dapp_contract_name) const;
	rvm::BuildNum						_GetContractEffectiveBuild(rvm::ContractId contract) const;
	const rvm::DeployedContract*		_GetContractDeployed(rvm::ContractVersionId contract) const;
	void								_FinalizeFunctionInfo(const rvm::ContractVersionId& cvid, const rt::String_Ref& func_prefix, const rvm::ContractModuleID& deploy_id, const rvm::Interface* info, const rvm::ConstData& stub);

protected:
	// From GlobalStates
	virtual rvm::ConstStateData			GetState(rvm::ContractScopeId contract) const override;
	virtual rvm::ConstStateData			GetState(rvm::ContractScopeId contract, const rvm::ScopeKey* key) const override;

	virtual rvm::DAppId					GetDAppByName(const rvm::ConstString* dapp_name) const override { return _GetDAppByName(dapp_name); }
	virtual rvm::ContractVersionId		GetContractByName(const rvm::ConstString* dapp_contract_name) const override { return _GetContractByName(dapp_contract_name); }
	virtual rvm::BuildNum				GetContractEffectiveBuild(rvm::ContractId contract) const override { return _GetContractEffectiveBuild(contract); }

	virtual const rvm::DeployedContract*GetContractDeployed(rvm::ContractVersionId contract) const override { return _GetContractDeployed(contract); };

	// From ExecutionContext
	virtual void						CommitNewState(rvm::ContractInvokeId contract, uint8_t* state_memory) override;
	virtual void						CommitNewState(rvm::ContractInvokeId contract, const rvm::ScopeKey* key, uint8_t* state_memory) override;
	virtual rvm::ContractVersionId		DeployUnnamedContract(rvm::DAppId dapp_id, rvm::EngineId engine_id, const rvm::ContractModuleID* module_id) override;

public:
	bool		IsDeploying() const { return _bDeploying; }
	void		DeployBegin();
	void		DeployEnd(bool commit);
	bool		AllocateContractIds(const BuildContracts& linked);
	bool		CommitDeployment(const BuildContracts& deployed);
	void		Term();
	auto&		GetExecuteUnits(){ return _ExecUnits; }

	SimuGlobalShard(Simulator* simu, uint64_t time_base, uint32_t shard_order);
	virtual ~SimuGlobalShard(){ Term(); }
};

} // namespace oxd