#pragma once
#include "shard_data.h"
#include "simu_global.h"
#include "simu_script.h"

#if defined(PLATFORM_WIN)
static const constexpr char* PREDA_DATA_FOLDER = "\\AppData\\Roaming\\.preda\\";
#elif defined(PLATFORM_MAC)
static const constexpr char* PREDA_DATA_FOLDER = "/Library/Application Support/.preda/";
#elif defined(PLATFORM_LINUX)	
static const constexpr char* PREDA_DATA_FOLDER = "/.preda/";
#endif
namespace oxd
{
class PredaScriptRunner;
class PredaScriptRealListener;
class ChainSimulator: protected rvm::BlockchainRuntime
			   		, public rt::Singleton<ChainSimulator, false>
{
	friend class SimuShard;
	friend class SimuGlobalShard;
	friend class RelayEmission;
	friend class PredaScriptRealListener;
#ifndef __APPLE__
	friend struct SimuTxn;
	friend struct SimuBlock;
	friend struct SimuState;
#endif
protected:
	constexpr static uint64_t defaultBlockGasLimit = 100000000;
	struct attribute
	{
		const rvm::DAppId			DAPP_ID = (rvm::DAppId)1;
		const rt::SS				DAPP_NAME = "chsimu";
		const rvm::Address			ADDRESS{ {1,2,3,4} };
		uint32_t 					shardOrder;
		uint32_t					shardBitmask;
		bool 						isShardAsync;
		rvm::EngineId 				defaultEngineMode;
	} m_attribute;

	struct runtimeInfo
	{
		bool 						isChainStepping;
		bool						isChainPaused;
		volatile int32_t			shardsExecutedTxnCount;			// used in !isShardAsync mode
		volatile int32_t			pendingTxnCount;
		volatile int32_t			executedTxnCount;
		uint64_t					gasLimit;
		uint64_t					globalGasLimit;
	} m_runtimeInfo;

	struct vizInfo
	{
		bool 						isVizEnabled;
		rt::Json					vizJson;
		rt::String_Ref 				vizTmplFile;
		rt::String_Ref 				vizOutputFile;
		rt::BufferEx<size_t>		shardPendingTxnCount;
	} m_vizInfo;

protected:
	PredaScriptRunner*				m_pScriptRunner;
	PredaScriptRealListener*		m_pScriptListener;
	rvm::Address					m_miner;
	os::Event						m_chainIdle;

	oxd::EngineEntry				m_engines[(int)rvm::EngineId::Max];
	oxd::SimuGlobalShard*			m_pGlobalShard = nullptr;
	rt::Buffer<oxd::SimuShard*>		m_shards;

public:
	// Constructor //
	ChainSimulator():m_pScriptRunner(nullptr), m_pScriptListener(nullptr){rt::Zero(m_engines);}

	// Chain Operation Interfaces //
	bool 				Init(const os::CommandLine& cmd);
	bool				Compile(const std::vector<std::pair<rt::String, rt::String>>& prdFiles);
	bool				CompileSol(rt::String_Ref fileContent, rt::String_Ref filePath);
	void 				Deploy(SimuTxn* txn);
	bool 				SetState(rvm::ContractInvokeId ciid, SimuState* pState, uint32_t shardId = 0, const rvm::Address* target = nullptr);
	void 				IssueTxn(SimuTxn* txn);
	void 				Run(bool step = false);
	void 				Stop();
	void				Await();
	void 				Term();

	// Chain Information Interfaces //
	void 				Info();
	void 				ExportViz();
	bool 				VizBlock(uint32_t shardId, int64_t blockHeight, rt::Json& json);
	bool 				VizAddr(const std::string& contractName, const rvm::Address& userAddr, uint32_t userId, rt::Json& json);
	bool 				VizShard(const std::string& contractName, uint32_t shardId, rt::Json& json);
	bool 				VizTxn(SimuTxn* txn, rt::Json& json);
	bool 				VizTrace(SimuTxn* originTxn, rt::Json& json);
	bool 				VizProfiling(rt::Json& json);
	bool				VizUintScope(const std::string& contractName, uint32_t scopeLen, std::string scopeTarget, rt::Json& json);
	void				GetStateJson(rvm::Scope scope, rvm::ContractVersionId ciid, rt::Json& out);
	rt::Json&			GetVizJson() { return m_vizInfo.vizJson; }
	bool				EnableViz() const { return m_vizInfo.isVizEnabled; }

	// Interfaces for Composing Txn and State //
	bool				GetContractFunction(rt::String_Ref contractName, rt::String_Ref functionName, rt::String_Ref jsonParameters, ContractFunction& outCf, rvm::ContractInvokeId& outCiid);
	bool 				ResolveCiid(rt::String_Ref dappContractName, rvm::Scope scope, rvm::ContractInvokeId& out);
	int 				ComposeTxn(rvm::ContractInvokeId ciid, rvm::OpCode op, rt::String_Ref jsonParameters, rt::String_Ref tokensSuppliedStr, SimuTxn*& out);
	int 				ComposeState(rvm::ContractInvokeId ciid, rt::String_Ref jsonParameters, SimuState*& out, uint32_t shardId = rvm::GlobalShard, const rvm::ScopeKey& sk = { nullptr, 0 }, bool isSettingWholeState = true);
	void				AddSuplliedToken(rvm::ContractInvokeId cvid, rvm::TokenId tokenId);

	// GET Interfaces //
	uint32_t			GetShardOrder() const { return m_attribute.shardOrder; }
	uint32_t			GetShardCount() const { return 1 << m_attribute.shardOrder; }
	uint32_t			GetShardIndex(const rvm::Address& a) const { return rvm::ADDRESS_SHARD_DWORD(a) & m_attribute.shardBitmask; }
	uint32_t			GetShardIndex(const ScopeTarget& a) const { return rvm::SCOPEKEY_SHARD_DWORD(rvm::ScopeKey{ (uint8_t*)&a.u512, a.target_size }) & m_attribute.shardBitmask; }
	uint64_t			GetPendingTxnsCount() const { return m_runtimeInfo.pendingTxnCount; }
	uint64_t			GetExecutedTxnsCount() const { return m_runtimeInfo.executedTxnCount; }
	rt::String_Ref		GetScriptDirPath() { ASSERT(m_pScriptRunner); return m_pScriptRunner->GetScriptDirPath(); }
	uint32_t 			GetLineNum() { ASSERT(m_pScriptListener); return m_pScriptListener->GetLineNum(); }
	auto*				GetGlobalStates() const { return (const rvm::GlobalStates*)(m_pGlobalShard); }

	// SET Interfaces //
	void				SetScriptGasLimit(uint64_t gas_limit) { m_runtimeInfo.gasLimit = gas_limit; }
	void				SetScriptGlobalGasLimit(uint64_t gas_limit) { m_runtimeInfo.globalGasLimit = gas_limit; }
	void				SetScriptRunner(PredaScriptRunner* _runner) { m_pScriptRunner = _runner; }
	void				SetScriptListener(PredaScriptRealListener* _listener) { m_pScriptListener = _listener;}

protected:
	// Interfaces for SimuShard //
	auto*				GetShard(uint32_t i) { return rvm::GlobalShard == i ? m_pGlobalShard: m_shards[i]; }
	auto*				GetShard(uint32_t i) const { return rvm::GlobalShard == i ? m_pGlobalShard: m_shards[i]; }
	auto*				GetGlobalShard() { return m_pGlobalShard; }
	auto*				GetGlobalShard() const { return m_pGlobalShard; }
	uint64_t			GetScriptGasLimit() const { return m_runtimeInfo.gasLimit; }
	uint64_t			GetScriptGlobalGasLimit() const { return m_runtimeInfo.globalGasLimit; }
	rvm::RvmEngine* 	GetEngine(rvm::EngineId e) const { return m_engines[(int)e].pEngine; }
	const auto*			GetAllEngines() const { return &m_engines[0]; }
	rvm::Address&		GetMiner() { if(m_pScriptListener) m_miner =  m_pScriptListener->GetUserAddr(0); return m_miner; }

	void				OnTxnPushed(){ if(os::AtomicIncrement(&m_runtimeInfo.pendingTxnCount) < 2) m_chainIdle.Reset(); }
	void				OnTxnPushed(uint32_t count){ if(os::AtomicAdd(count, &m_runtimeInfo.pendingTxnCount) < (int)(2 + count)) m_chainIdle.Reset(); }
	void				OnTxnsConfirmed(uint32_t count){ os::AtomicAdd(-(int32_t)count, &m_runtimeInfo.pendingTxnCount); os::AtomicAdd(count, &m_runtimeInfo.executedTxnCount); }
	
	bool				IsShardingAsync() const {return m_attribute.isShardAsync; }
	bool				IsChainStepping() const {return m_runtimeInfo.isChainStepping; }
	bool				IsChainPaused() const {return m_runtimeInfo.isChainPaused; }
	void				SetChainIdle() { m_chainIdle.Set();}
	void				WaitUntilIdle() { m_chainIdle.WaitSignal(); }

	rvm::InvokeResult 	DeployFromStatement(rvm::ConstData deployArgs);
	bool				CompleteShardExecution();
	void				CreateExecuteUnit(ExecutionUnit* out) const;

private:
	// Wrapped internal functions //
	void 				_InitChain();
	bool 				_InitEngine(rvm::EngineId eng, const char* dll_name, const char* repo, const char* engine_config);
	bool 				_Deploy(ExecutionUnit& exec_units, const rt::String_Ref* fileNames, const rt::String_Ref* args, uint32_t count, rvm::InvokeResult &out);
	rvm::EngineId 		_ResolveRTEngine(rt::String in, rt::String& filename);
	bool 				_ComposeSolJson(rt::JsonObject inJson, rt::Json& out, rt::String fn);
	bool 				_ResolveOverloadedFunctions(rt::String_Ref jsonParameters, rt::BufferEx<ContractFunction>& funcs, ContractFunction& out);
	bool				_ResolveUnamedContract(rt::String_Ref contractName, rt::String_Ref functionName, rt::String& outFunctionFullName, rvm::ContractVersionId& outCvid);
	bool 				_ResolveTokensSupplied(rt::String_Ref tokensSuppliedStr, rt::BufferEx<uint8_t>& out);
	bool				_ResolveExistingState(rvm::ContractInvokeId ciid, uint32_t shardId, const rvm::ScopeKey& sk, rvm::StringStreamImpl& out);
	bool				_ComposeStateData(rvm::ContractInvokeId ciid, rt::String_Ref jsonParameters, const rt::String_Ref& existing_state, rvm::ConstData &out_buf);

protected:
	///////////////////////////////////////////////////////
	// From rvm::BlockchainRuntime
	rvm::ConstString				GetCoreDAppName() const override { return {"core", 4}; }
	rvm::ContractRepository*		GetContractRepository() override { return nullptr; }
	void							DebugPrint(rvm::DebugMessageType type, const rvm::ConstString* string, const rvm::ExecutionState* ctx_opt, const rvm::Contract* contract_opt, int32_t line) override
									{ rvm::BlockchainRuntime_DebugPrint(type, string, ctx_opt, contract_opt, line);}
	rvm::DAppId						GetDAppByName(const rvm::ConstString* dapp_name) const override { return m_pGlobalShard->_GetDAppByName(dapp_name); }
	rvm::ContractVersionId			GetContractByName(const rvm::ConstString* dapp_period_contract_name) const override { return m_pGlobalShard->_GetContractByName(dapp_period_contract_name); }
	rvm::BuildNum					GetContractEffectiveBuild(rvm::ContractId contract) const override { return m_pGlobalShard->_GetContractEffectiveBuild(contract); }
	const rvm::DeployedContract*	GetContractDeployed(rvm::ContractVersionId contract) const override { return m_pGlobalShard->_GetContractDeployed(contract); }
	rvm::TokenMinterFlag			GetTokenMinterState(rvm::TokenId tid, rvm::ContractId contract) const override { return m_pGlobalShard->_GetTokenMinterState(tid, contract); }
	///////////////////////////////////////////////////////
};

} // namespace oxd
