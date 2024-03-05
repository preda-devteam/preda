#pragma once
#include "shard_data.h"
#include "simu_global.h"


namespace oxd
{

class Simulator;
class SimuShard;
class DataBuffer;

extern int SimulatorMain(const os::CommandLine& cmd);

struct InvokeIdentifier
{
	rt::String_Ref	DApp;
	rt::String_Ref	Contract;
	rt::String_Ref	Scope;

	rvm::ContractInvokeId	CIID;
};

class Simulator: protected rvm::BlockchainRuntime
			   , public rt::Singleton<Simulator, false>
{
	friend class InputParametrized;
	friend class SimuGlobalShard;

public:
	const rvm::DAppId		DAPP_ID = ( rvm::DAppId)1;
	const rt::SS			DAPP_NAME = "chsimu";
	const rvm::Address		ADDRESS{ {1,2,3,4} };

protected:

	EngineEntry				_Engines[(int)rvm::EngineId::Max];
	bool					_InitEngine(rvm::EngineId eng, const char* dll_name, const char* repo, const char* engine_config = nullptr);

protected:
	ext::fast_map<rt::String_Ref, rt::BufferEx<SimuTxn*>> _TxnPool;
	mutable os::CriticalSection	_CS;

protected:
	SimuGlobalShard*			_pGlobalShard = nullptr;
	rt::Buffer<SimuShard*>		_Shards;
	rt::BufferEx<size_t>		_ShardPendingTxn;

	volatile int32_t			_iShardsExecuted;	// used in !_bShardAsync mode
	uint32_t					_ShardOrder;
	uint32_t					_ShardBitmask;
	bool						_bChainStepping;
	bool						_bShardAsync;		// monoxide
	bool						_bChainPaused;
	volatile int32_t			_PendingTxnCount;
	volatile int32_t			_ExecutedTxnCount;
	os::Event					_ChainIdle;

	bool						_ParseInvokeIdentifier(const rt::String_Ref& x, int line_num, InvokeIdentifier& out) const;
	void						_InitChain(UINT shard_count);
	static rt::String_Ref		_LookupFunctionName(const rvm::Contract* contract, rvm::OpCode op);

protected:
	///////////////////////////////////////////////////////
	// From rvm::BlockchainRuntime
	rvm::ConstString			GetCoreDAppName() const override { return {"core", 4}; }
	rvm::ContractRepository*	GetContractRepository() override { return nullptr; }
	void						DebugPrint(rvm::DebugMessageType type, const rvm::ConstString* string, const rvm::ExecutionState* ctx_opt, const rvm::Contract* contract_opt, int32_t line) override;
	rvm::DAppId					GetDAppByName(const rvm::ConstString* dapp_name) const override { return _pGlobalShard->_GetDAppByName(dapp_name); }
	rvm::ContractVersionId		GetContractByName(const rvm::ConstString* dapp_period_contract_name) const override { return _pGlobalShard->_GetContractByName(dapp_period_contract_name); }
	rvm::BuildNum				GetContractEffectiveBuild(rvm::ContractId contract) const override { return _pGlobalShard->_GetContractEffectiveBuild(contract); }
	const rvm::DeployedContract*GetContractDeployed(rvm::ContractVersionId contract) const override { return _pGlobalShard->_GetContractDeployed(contract); }
	rvm::TokenMinterFlag		GetTokenMinterState(rvm::TokenId tid, rvm::ContractId contract) const override { return _pGlobalShard->_GetTokenMinterState(tid, contract); }

protected:
	// Scripting
	struct CmdParse
	{
		rt::String_Ref		L1;
		rt::String_Ref		L2;
		rt::String_Ref		Args;
		int					Repeat;
		rt::String_Ref		Identifier;
		bool				Identifier_isArray;
		CmdParse(const rt::String_Ref& cmd, uint32_t LineNum);
	};
	struct TargetParse
	{
		rt::String_Ref		Target;
		rt::String_Ref		ArgsJson;

		TargetParse(const rt::String_Ref& arg_part, rvm::Scope scope, uint32_t LineNum);
		TargetParse() {};
		bool				IsError() const { return ArgsJson.IsEmpty(); }
	};
	std::map<rt::String, rt::BufferEx<SimuTxn*>>	_batchImportTxns;
	//Addresses of new users who are not generated from allocate.address, and their index in _Users
	std::map<rt::String, uint32_t> _NewUserIndex;
	rt::BufferEx<User>				_Users;
	uint32_t						_UserIndexRandMax;
	rt::String						_ScriptPath;
	bool							_ScriptAborted;
	InputParametrized::Symbols		_ScriptEnv;
	mutable rt::Randomizer			_ScriptRand;
	uint64_t						_ScriptGasLimit;
	uint64_t						_ScriptGlobalGasLimit;
	os::HighPerformanceCounter		_ScriptStopWatch;
	uint64_t						_ScriptStopWatchPendingTxnCount = 0;
	uint64_t						_ScriptStopWatchExecutedTxnCount = 0;
	rt::Json						_ScriptVizJson;
	uint32_t						_ScriptVizSectionNum;
	bool							_ScriptVizEnabled;
	bool							_VizToConsole;
	rt::String						_DefaultRTMode;
	bool							_CompileOnly;
	ext::AsyncDataQueueInfinite<std::pair<rt::String, SimuTxn*>, false, 64, true> _IdTxnQueue;
	os::CriticalSection				_RandScriptCS;

	bool							_ExecAllocate(const CmdParse& cmd);
	bool							_ExecState(const CmdParse& cmd);
	bool							_ExecChain(const CmdParse& cmd);
	bool							_ExecLog(const CmdParse& cmd);
	bool							_ExecIssueTxn(const CmdParse& cmd);
	bool							_ExecGenerateBatchTxn(const CmdParse& cmd);
	bool							_ExecVisualize(const CmdParse& cmd, const rt::String_Ref& cmd_in);
	bool							_ExecBlocksLog(const CmdParse& cmd, rt::Json& json);
	bool							_ExecAddrStateLog(const CmdParse& cmd, rt::Json& json);
	bool							_ExecShardStateLog(const CmdParse& cmd, rt::Json& json);
	bool 							_ExecTxnLog(const CmdParse& cmd, rt::Json& json);
	bool							_ExecTraceLog(const CmdParse& cmd, rt::Json& json);
	void							_ExecProfileLog(rt::Json& json);
	bool							_ExecKeyedScopeLog(const CmdParse& cmd, rt::Json& json);
	bool							_ExecAllKeyedScopeLog(const CmdParse& cmd, rt::Json& json);
	bool							_GetContractFunction(const CmdParse& cmd, ContractFunction& fi) const;
	bool							_ProcessTargetRequest(rt::String& out, uint32_t LineNum, bool shardReq);
	bool							_ProcessIdentifierRequest(const CmdParse& cmd, rt::String& id_name, int& index, bool isTrace);
	void							_ConvertQueueToTxnPool();
	bool							_ConfirmedTxnJsonify(const SimuTxn* txn, rt::Json& append) const;
	bool							_ModifyState(rvm::ContractInvokeId ciid, InputParametrized& input, const rt::String_Ref& in_state, bool replace, SimuShard* s = nullptr, const rvm::ScopeKey& sk = { nullptr, 0 });
	bool							_ComposeSolJson(rt::JsonObject inJson, rt::Json& out, rt::String fn);
	void							_RunDeployAsTxn(const CmdParse& cmd);
	bool							_Step();

	rvm::EngineId						_ResolveRTEngine(rt::String in, rt::String& filename);
	bool							_ParseSolidityFunc(const rt::String& functionName, rt::String& argument);

private:
	//Add new users to Users and _NewUserIndex, and return addr's index in _Users
	uint32_t						_AddNewUser(rt::String_Ref addrStr, rvm::Address& addr);
	bool							_BatchInsertTxn(const rt::String_Ref& csvData);
	SimuTxn*						_ComposeTxnFromStr(const CmdParse& cmd, rvm::ContractInvokeId& cvid, ContractFunction& fi, TargetParse& target, InputParametrized& input);
	int32_t							_GetIndexFromAddrStr(const rt::String& target);
	bool							_SetGasLimit(const rt::String_Ref& args, uint64_t& gaslimit);
	bool							_ResolveUnnameContract(const rt::String_Ref unnameContract, rt::String_Ref contractFunc, rt::String& contractName, rvm::ContractVersionId& cvid) const;
	bool							_ReadStateFromFile(const rt::String_Ref& filename, const rt::String_Ref* TargetSeg);
	void							_SaveStateToFile(const rt::String_Ref& filename, const rt::String& scope, rvm::ContractVersionId cvid);
	bool							_GenerateSetStateCmd(const rt::String_Ref& line, const rt::String_Ref& scope, const rt::String_Ref& target_contract);


public:
	Simulator();
	~Simulator(){ Term(); }

	rvm::Scope		PrepareTxn(rvm::ContractId cid, rvm::OpCode opcode, rvm::BuildNum& buildnum_inout) const;
	uint32_t		GetShardIndex(const rvm::Address& a) const { return rvm::ADDRESS_SHARD_DWORD(a)&_ShardBitmask; }
	uint32_t		GetShardIndex(const ScopeTarget& a) const { return rvm::SCOPEKEY_SHARD_DWORD(rvm::ScopeKey{ (uint8_t*)&a.u512, a.target_size }) &_ShardBitmask; }
	uint32_t		GetShardCount() const { return 1<<_ShardOrder; }
	auto*			GetShard(uint32_t i){ return _Shards[i]; }
	auto*			GetShard(uint32_t i) const { return _Shards[i]; }
	auto*			GetGlobalShard(){ return _pGlobalShard; }
	auto*			GetGlobalShard() const { return _pGlobalShard; }
	const auto&		GetUsers() const { return _Users; }

	bool			Init(const os::CommandLine& cmd);
	void			Term();

	void			CreateExecuteUnit(ExecutionUnit* out) const;
	auto&			GetMiner() const { return _Users[0].Addr; }
	bool			CompleteShardExecution();
	bool			IsShardingAsync() const { return _bShardAsync; }
	bool			IsChainStepping() const { return _bChainStepping; }
	bool			IsChainPaused() const { return _bChainPaused; }

	uint32_t		GetScriptRandom32() const { EnterCSBlock(_RandScriptCS); return _ScriptRand.GetNext(); }
	uint64_t		GetScriptRandom64() const { EnterCSBlock(_RandScriptCS); return _ScriptRand.GetNext() | (((uint64_t)_ScriptRand.GetNext())<<32); }
	uint64_t		GetScriptGasLimit() const { return _ScriptGasLimit; }
	uint64_t		GetScriptGlobalGasLimit() const { return _ScriptGlobalGasLimit; }
	auto&			GetScriptEnvSymbols() const { return _ScriptEnv; }
	auto&			GetScriptAddress(uint32_t i) const { return _Users[i]; }
	auto&			GetScriptRandomAddress() const { return _Users[GetScriptRandomAddressIndex()].Addr; }
	uint32_t		GetScriptRandomAddressIndex() const;
	uint32_t		GetScriptAddressCount() const { return (uint32_t)_Users.GetSize(); }

	bool			ExecuteCommand(const rt::String_Ref& cmd);
	void			Run(rt::Buffer<rt::String_Ref>& input_files);
	bool			Deploy(ExecutionUnit& exec_units, const rt::String_Ref* filenames, const rt::String_Ref* ctor_args, uint32_t count, bool within_script, rvm::InvokeResult &ctor_invoke_result);
	bool			Compile(rvm::EngineId e, rt::Buffer<rt::String>& sources, rt::Buffer<rt::String_Ref>& code_fns);

	void			OnTxnPushed(){ if(os::AtomicIncrement(&_PendingTxnCount) < 2)_ChainIdle.Reset(); }
	void			OnTxnPushed(uint32_t co){ if(os::AtomicAdd(co, &_PendingTxnCount) < (int)(2 + co))_ChainIdle.Reset(); }
	void			OnTxnsConfirmed(uint32_t co)
					{
						os::AtomicAdd(-(int32_t)co, &_PendingTxnCount); //ChainIdle will be set when all shards finish block creation and pendingTxnCount reaches zero
						os::AtomicAdd(co, &_ExecutedTxnCount);
					}
	uint32_t		GetPendingTxnCount() const { return _PendingTxnCount; }
	void			WaitUntilIdle();
	bool			ExportVizHtml(const rt::String_Ref& assets, const rt::String_Ref& output) const;
	rvm::RvmEngine* GetEngine(rvm::EngineId e) const { return _Engines[(int)e].pEngine;	}
	const auto*		GetAllEngines() const { return &_Engines[0]; }
	auto*			GetGlobalStates() const { return (const rvm::GlobalStates*)(_pGlobalShard); }

	uint32_t		GetLineNum() const { return LineNum; }
	auto			DeployFromStatement(const rt::String_Ref& deployStatement) -> rvm::InvokeResult;
	void			SetChainIdle() { _ChainIdle.Set();}
	bool			IsVizToConsole() const { return _VizToConsole; }
public:
	JsonLogError	JsonLog;
	uint32_t		LineNum;
};

} // namespace oxd
