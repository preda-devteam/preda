#pragma once
#include "./antlr_generated/PredaScriptLexer.h"
#include "./antlr_generated/PredaScriptBaseListener.h"
#include "../transpiler/PredaParseTreeWalker.h"
#include "shard_data.h"
#include "simu_global.h"

#define VIZ_SECTION_BEGIN(json, tag)	{auto __section_scope = (json).ScopeAppendingElement();			\
											(json).Object( (( J(type) = tag )) );							\
											auto __section_body = (json).ScopeAppendingKey("content");	
#define VIZ_QUERY_SECTION_BEGIN(json, tag, cmd)		{auto __section_scope = (json).ScopeAppendingElement();			\
													(json).Object( (( J(type) = tag ),(J(command) = cmd)) );		\
													auto __section_body = (json).ScopeAppendingKey("content");
#define VIZ_SECTION_END					}	

namespace oxd
{

int SimulatorMain(const os::CommandLine& cmd);
class PredaScriptRunner
{
	rt::String m_currentScriptDirectoryPath;
public:
	int Run(ChainSimulator& _chsimu, const std::string& fileContent);
	rt::String_Ref GetScriptDirPath() { return m_currentScriptDirectoryPath; }
	void SetScriptDirPath(rt::String_Ref _directoryPath) { m_currentScriptDirectoryPath = _directoryPath;  }
};

class CustomErrorListener : public antlr4::BaseErrorListener {
public:
	virtual void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line, size_t charPositionInLine,
		const std::string &msg, std::exception_ptr e) override{    
		p_errors.push_back("[PRD] Line " + std::to_string(line) + ": " + msg + " at position " + std::to_string(charPositionInLine));
    }
	std::vector<std::string> p_errors;
};

class ScriptParseTreeBuilder
{
public:
	ScriptParseTreeBuilder(const std::string& input)
	: m_inputStream(input), m_lexer(&m_inputStream), m_tokens(&m_lexer), m_parser(&m_tokens){
		m_lexer.removeErrorListeners();
		m_lexer.addErrorListener(&m_errorListener);
		m_parser.removeErrorListeners();
		m_parser.addErrorListener(&m_errorListener);
	}
	antlr4::tree::ParseTree* scripts(){ 
		auto ret =  m_parser.scripts(); 
		if(m_errorListener.p_errors.size()){
			for(auto& err : m_errorListener.p_errors)
				std::cerr << err << std::endl;
			return nullptr;
		}	
		return ret;
	}
	antlr4::tree::ParseTree* toBeAssignedValue() {
		auto ret = m_parser.toBeAssignedValue();
		if (m_errorListener.p_errors.size()) {
			return nullptr;
		}
		return ret;
	}
	antlr4::tree::ParseTree* jsonParameters() {
		auto ret = m_parser.jsonParameters();
		if (m_errorListener.p_errors.size()) {
			return nullptr;
		}
		return ret;
	}
	antlr4::tree::ParseTree* issueTxn() {
		auto ret = m_parser.issueTxn();
		if (m_errorListener.p_errors.size()) {
			return nullptr;
		}
		return ret;
	}
private:
	antlr4::ANTLRInputStream m_inputStream;
	PredaScriptLexer m_lexer;
	antlr4::CommonTokenStream m_tokens;
	PredaScriptParser m_parser;
	CustomErrorListener m_errorListener;
};

class PredaScriptRealListener : public PredaScriptBaseListener, public CustomErrorListener
{
private:
	ChainSimulator 					&m_chsimu;
	os::HighPerformanceCounter		m_stopWatch;
	uint64_t						m_stopWatchPendingTxnCount;
	uint64_t						m_stopWatchExecutedTxnCount;
	mutable rt::Randomizer			m_randomizer;
	mutable os::CriticalSection		m_CS;
	std::vector<rvm::Address>		m_users;
	uint32_t 						m_currentUserId4ComposeTxn;
	uint32_t						m_currentLineNum;

	struct scriptVariable{
		enum type{
			INT32,
			STRING
		} mType;
		std::vector<uint8_t> data;
	};
	std::map<std::string, scriptVariable> 				m_scriptVariables;
	std::map<std::string, std::vector<oxd::SimuTxn*>> 	m_txnRecords;
	std::map<std::string, std::vector<SimuTxn*>> 		m_batchTxns;
public:
	PredaScriptRealListener(ChainSimulator& _chsimu);
	auto 				GetLineNum() { return m_currentLineNum; }
	auto 				GetUserId(const rvm::Address& addr) { return 0; }
	auto 				GetTimeLapsed() { return m_stopWatch.TimeLapse(); }
	rvm::Address		GetUserAddr(uint32_t userId) { return (userId >= 0 && userId < m_users.size()) ? m_users[userId] : rvm::Address({0, 0});}

public:
  	virtual void enterScript(PredaScriptParser::ScriptContext * /*ctx*/) override;
  	virtual void enterAwaitChain(PredaScriptParser::AwaitChainContext * /*ctx*/) override;
  	virtual void enterStepChain(PredaScriptParser::StepChainContext * /*ctx*/) override;
  	virtual void enterRunChain(PredaScriptParser::RunChainContext * /*ctx*/) override;
  	virtual void enterStopChain(PredaScriptParser::StopChainContext * /*ctx*/) override;
  	virtual void enterGetChainInfo(PredaScriptParser::GetChainInfoContext * /*ctx*/) override;

 	virtual void enterIssueTxn(PredaScriptParser::IssueTxnContext * ctx) override;
  	virtual void enterDeployContractOnChain(PredaScriptParser::DeployContractOnChainContext * ctx) override;
  	virtual void enterBatchInsertTxnOnChain(PredaScriptParser::BatchInsertTxnOnChainContext * ctx) override;
	virtual void enterVariableAssign(PredaScriptParser::VariableAssignContext * ctx) override;
 	virtual void enterDataReadFromFile(PredaScriptParser::DataReadFromFileContext * ctx) override;

	virtual void enterSetGasLimit(PredaScriptParser::SetGasLimitContext * ctx) override;
	virtual void enterSetContractState(PredaScriptParser::SetContractStateContext * ctx) override;
	virtual void enterUpdateState(PredaScriptParser::UpdateStateContext * ctx) override;
	virtual void enterTokenState(PredaScriptParser::TokenStateContext * ctx) override;
	virtual void enterMintToken(PredaScriptParser::MintTokenContext* /*ctx*/) override;
	virtual void enterLoadState(PredaScriptParser::LoadStateContext * ctx) override;
	virtual void enterSaveState(PredaScriptParser::SaveStateContext * ctx) override;
	virtual void enterConfigAddress(PredaScriptParser::ConfigAddressContext * ctx) override;
	virtual void enterConfigRandomizer(PredaScriptParser::ConfigRandomizerContext* ctx) override;

	virtual void enterNormalLog(PredaScriptParser::NormalLogContext* ctx) override;
	virtual void enterLogHighlight(PredaScriptParser::LogHighlightContext * ctx) override;
	virtual void enterLogWarning(PredaScriptParser::LogWarningContext * ctx) override;
	virtual void enterLogError(PredaScriptParser::LogErrorContext * ctx) override;
	virtual void enterStopWatchRestart(PredaScriptParser::StopWatchRestartContext * ctx) override;
	virtual void enterStopWatchReport(PredaScriptParser::StopWatchReportContext * ctx) override;
	virtual void enterVizBlock(PredaScriptParser::VizBlockContext * ctx) override;
	virtual void enterVizAddr(PredaScriptParser::VizAddrContext * ctx) override;
	virtual void enterVizShard(PredaScriptParser::VizShardContext * ctx) override;
	virtual void enterVizTxn(PredaScriptParser::VizTxnContext * ctx) override;
	virtual void enterVizTrace(PredaScriptParser::VizTraceContext * ctx) override;
	virtual void enterVizSection(PredaScriptParser::VizSectionContext * ctx) override;
	virtual void enterVizProfiling(PredaScriptParser::VizProfilingContext * ctx) override;
	virtual void enterVizUintScope(PredaScriptParser::VizUintScopeContext * ctx) override;

private:
	uint32_t 			GetRandomUint32(){ return m_randomizer.GetNext(); }
	uint32_t 			GetRandomUint32(uint32_t min, uint32_t max) { ASSERT(min < max); return min + (GetRandomUint32() % (max - min + 1)); }
	uint64_t 			GetRandomUint64(){ return m_randomizer.GetNext() | (((uint64_t)m_randomizer.GetNext()) << 32); }
	int64_t 			GetRandomInt64(int64_t min, int64_t max) { ASSERT(min < max); return min + (GetRandomUint64() % (max - min + 1)); }
	bool				ResolveInt64Random(int64_t min, int64_t max, std::string& out) { out = std::to_string(GetRandomInt64(min, max)); return true; }
	bool				ResolveBigintRandom(uint32_t bitwidth, std::string& out);
	bool 				ResolveIntRandom(PredaScriptParser::IntRandomContext* ctx, std::string& out);
	
	bool				ResolveIssueTxn(PredaScriptParser::IssueTxnContext * ctx, std::vector<oxd::SimuTxn*>& out);
	bool				ResolveJsonParameters(const std::string& in, std::string& out);
	bool 				ResolveJsonParameters(PredaScriptParser::JsonParametersContext* ctx, std::string& out);
	bool				ResolveJsonParameter(PredaScriptParser::JsonParameterContext* ctx, std::string& out);
	bool				ResolveJsonValue(PredaScriptParser::JsonValueContext* ctx, std::string& out);
	bool				ResolvePrimaryValue(PredaScriptParser::PrimaryValueContext* ctx, std::string& out);
	bool				ResolveConcreteValue(PredaScriptParser::ConcreteValueContext* ctx, std::string& out);
	bool				ResolveArrayValue(PredaScriptParser::ArrayValueContext* ctx, std::string& out);
	bool				ResolveToBeAssignedValue(PredaScriptParser::ToBeAssignedValueContext* ctx, std::string& out);
	bool 				ResolveIntExpression(PredaScriptParser::IntExpressionContext* ctx, std::string& out);
	bool				ResolveSuppliedTokens(PredaScriptParser::SuppliedTokensContext* ctx, std::string& out);

	bool				ResolveIdsFromScope(PredaScriptParser::ScopeContext* ctx, std::vector<uint32_t>& out);
	bool 				ResolveShardIdFromAddressScope(PredaScriptParser::AddressScopeContext* ctx, std::vector<uint32_t>& shardIds);
	bool				ResolveShardIdFromShardScope(PredaScriptParser::ShardScopeContext* ctx, std::vector<uint32_t>& shardIds);
	bool 				ResolveShardIdFromAddressScope(PredaScriptParser::AddressScopeContext* ctx, std::vector<std::pair<uint32_t, rvm::Address*>>& out);
	bool				ResolveUserIdFromAddressScope(PredaScriptParser::AddressScopeContext* ctx, std::vector<uint32_t>& userIds);
	bool				ResolveScopeLenFromUintScope(PredaScriptParser::UintScopeContext* ctx, std::vector<uint32_t>& scopeLen);
	bool 				ResolveAddressScope(PredaScriptParser::AddressScopeContext* ctx, std::string& out);

	bool				ResolveDeployArgsData(PredaScriptParser::ContractPropertiesContext* ctx, std::vector<uint8_t>& args);
	bool				ResolveModifyState(PredaScriptParser::ContractIdContext* contractIdCtx, PredaScriptParser::ScopeContext* scopeCtx, PredaScriptParser::JsonParametersContext* jsonCtx, bool isSettingWholeState);
	bool				ResolveStateJson(rvm::Scope scope, rt::String_Ref stateJson);

	bool				CheckIfAllUsers(PredaScriptParser::JsonParametersContext* ctx);
	bool				CheckIfAllUsers(PredaScriptParser::PrimaryValueContext* ctx);
	bool				isScopeTargetCorresponded(rvm::Scope scope, PredaScriptParser::ScopeContext* tCtx);
	bool				isAddressScopeCorrect(PredaScriptParser::AddressScopeContext* ctx);
	bool				isShardScopeCorrect(PredaScriptParser::ShardScopeContext* ctx);

	int					AddNewUser(rt::String_Ref userAddr);
	void				AttachSolFunctionName(const std::string& functionName, std::string& jsonParameters);
	void				AttachSolFunctionScope(const std::string& scope, std::string& jsonParameters);
};

} // namespace oxd
