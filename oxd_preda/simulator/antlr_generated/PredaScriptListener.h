
// Generated from PredaScript.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "PredaScriptParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by PredaScriptParser.
 */
class  PredaScriptListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterScripts(PredaScriptParser::ScriptsContext *ctx) = 0;
  virtual void exitScripts(PredaScriptParser::ScriptsContext *ctx) = 0;

  virtual void enterScript(PredaScriptParser::ScriptContext *ctx) = 0;
  virtual void exitScript(PredaScriptParser::ScriptContext *ctx) = 0;

  virtual void enterChainOperation(PredaScriptParser::ChainOperationContext *ctx) = 0;
  virtual void exitChainOperation(PredaScriptParser::ChainOperationContext *ctx) = 0;

  virtual void enterAwaitChain(PredaScriptParser::AwaitChainContext *ctx) = 0;
  virtual void exitAwaitChain(PredaScriptParser::AwaitChainContext *ctx) = 0;

  virtual void enterStepChain(PredaScriptParser::StepChainContext *ctx) = 0;
  virtual void exitStepChain(PredaScriptParser::StepChainContext *ctx) = 0;

  virtual void enterRunChain(PredaScriptParser::RunChainContext *ctx) = 0;
  virtual void exitRunChain(PredaScriptParser::RunChainContext *ctx) = 0;

  virtual void enterStopChain(PredaScriptParser::StopChainContext *ctx) = 0;
  virtual void exitStopChain(PredaScriptParser::StopChainContext *ctx) = 0;

  virtual void enterGetChainInfo(PredaScriptParser::GetChainInfoContext *ctx) = 0;
  virtual void exitGetChainInfo(PredaScriptParser::GetChainInfoContext *ctx) = 0;

  virtual void enterDeployContractOnChain(PredaScriptParser::DeployContractOnChainContext *ctx) = 0;
  virtual void exitDeployContractOnChain(PredaScriptParser::DeployContractOnChainContext *ctx) = 0;

  virtual void enterContractProperties(PredaScriptParser::ContractPropertiesContext *ctx) = 0;
  virtual void exitContractProperties(PredaScriptParser::ContractPropertiesContext *ctx) = 0;

  virtual void enterContractProperty(PredaScriptParser::ContractPropertyContext *ctx) = 0;
  virtual void exitContractProperty(PredaScriptParser::ContractPropertyContext *ctx) = 0;

  virtual void enterPredaFile(PredaScriptParser::PredaFileContext *ctx) = 0;
  virtual void exitPredaFile(PredaScriptParser::PredaFileContext *ctx) = 0;

  virtual void enterXtlFile(PredaScriptParser::XtlFileContext *ctx) = 0;
  virtual void exitXtlFile(PredaScriptParser::XtlFileContext *ctx) = 0;

  virtual void enterBatchInsertTxnOnChain(PredaScriptParser::BatchInsertTxnOnChainContext *ctx) = 0;
  virtual void exitBatchInsertTxnOnChain(PredaScriptParser::BatchInsertTxnOnChainContext *ctx) = 0;

  virtual void enterSetGasLimit(PredaScriptParser::SetGasLimitContext *ctx) = 0;
  virtual void exitSetGasLimit(PredaScriptParser::SetGasLimitContext *ctx) = 0;

  virtual void enterVariableDeclaration(PredaScriptParser::VariableDeclarationContext *ctx) = 0;
  virtual void exitVariableDeclaration(PredaScriptParser::VariableDeclarationContext *ctx) = 0;

  virtual void enterVariableAssign(PredaScriptParser::VariableAssignContext *ctx) = 0;
  virtual void exitVariableAssign(PredaScriptParser::VariableAssignContext *ctx) = 0;

  virtual void enterVarName(PredaScriptParser::VarNameContext *ctx) = 0;
  virtual void exitVarName(PredaScriptParser::VarNameContext *ctx) = 0;

  virtual void enterVarValue(PredaScriptParser::VarValueContext *ctx) = 0;
  virtual void exitVarValue(PredaScriptParser::VarValueContext *ctx) = 0;

  virtual void enterDataReadFromFile(PredaScriptParser::DataReadFromFileContext *ctx) = 0;
  virtual void exitDataReadFromFile(PredaScriptParser::DataReadFromFileContext *ctx) = 0;

  virtual void enterCsvfilePath(PredaScriptParser::CsvfilePathContext *ctx) = 0;
  virtual void exitCsvfilePath(PredaScriptParser::CsvfilePathContext *ctx) = 0;

  virtual void enterConfig(PredaScriptParser::ConfigContext *ctx) = 0;
  virtual void exitConfig(PredaScriptParser::ConfigContext *ctx) = 0;

  virtual void enterConfigState(PredaScriptParser::ConfigStateContext *ctx) = 0;
  virtual void exitConfigState(PredaScriptParser::ConfigStateContext *ctx) = 0;

  virtual void enterSetContractState(PredaScriptParser::SetContractStateContext *ctx) = 0;
  virtual void exitSetContractState(PredaScriptParser::SetContractStateContext *ctx) = 0;

  virtual void enterStateScope(PredaScriptParser::StateScopeContext *ctx) = 0;
  virtual void exitStateScope(PredaScriptParser::StateScopeContext *ctx) = 0;

  virtual void enterUpdateState(PredaScriptParser::UpdateStateContext *ctx) = 0;
  virtual void exitUpdateState(PredaScriptParser::UpdateStateContext *ctx) = 0;

  virtual void enterTokenState(PredaScriptParser::TokenStateContext *ctx) = 0;
  virtual void exitTokenState(PredaScriptParser::TokenStateContext *ctx) = 0;

  virtual void enterMintToken(PredaScriptParser::MintTokenContext *ctx) = 0;
  virtual void exitMintToken(PredaScriptParser::MintTokenContext *ctx) = 0;

  virtual void enterTokenSymbol(PredaScriptParser::TokenSymbolContext *ctx) = 0;
  virtual void exitTokenSymbol(PredaScriptParser::TokenSymbolContext *ctx) = 0;

  virtual void enterLoadState(PredaScriptParser::LoadStateContext *ctx) = 0;
  virtual void exitLoadState(PredaScriptParser::LoadStateContext *ctx) = 0;

  virtual void enterJsonFilePath(PredaScriptParser::JsonFilePathContext *ctx) = 0;
  virtual void exitJsonFilePath(PredaScriptParser::JsonFilePathContext *ctx) = 0;

  virtual void enterSaveState(PredaScriptParser::SaveStateContext *ctx) = 0;
  virtual void exitSaveState(PredaScriptParser::SaveStateContext *ctx) = 0;

  virtual void enterConfigAddress(PredaScriptParser::ConfigAddressContext *ctx) = 0;
  virtual void exitConfigAddress(PredaScriptParser::ConfigAddressContext *ctx) = 0;

  virtual void enterConfigRandomizer(PredaScriptParser::ConfigRandomizerContext *ctx) = 0;
  virtual void exitConfigRandomizer(PredaScriptParser::ConfigRandomizerContext *ctx) = 0;

  virtual void enterIssueTxn(PredaScriptParser::IssueTxnContext *ctx) = 0;
  virtual void exitIssueTxn(PredaScriptParser::IssueTxnContext *ctx) = 0;

  virtual void enterTxnReturnInfo(PredaScriptParser::TxnReturnInfoContext *ctx) = 0;
  virtual void exitTxnReturnInfo(PredaScriptParser::TxnReturnInfoContext *ctx) = 0;

  virtual void enterContractId(PredaScriptParser::ContractIdContext *ctx) = 0;
  virtual void exitContractId(PredaScriptParser::ContractIdContext *ctx) = 0;

  virtual void enterContractName(PredaScriptParser::ContractNameContext *ctx) = 0;
  virtual void exitContractName(PredaScriptParser::ContractNameContext *ctx) = 0;

  virtual void enterCvid(PredaScriptParser::CvidContext *ctx) = 0;
  virtual void exitCvid(PredaScriptParser::CvidContext *ctx) = 0;

  virtual void enterFunctionName(PredaScriptParser::FunctionNameContext *ctx) = 0;
  virtual void exitFunctionName(PredaScriptParser::FunctionNameContext *ctx) = 0;

  virtual void enterCount(PredaScriptParser::CountContext *ctx) = 0;
  virtual void exitCount(PredaScriptParser::CountContext *ctx) = 0;

  virtual void enterScope(PredaScriptParser::ScopeContext *ctx) = 0;
  virtual void exitScope(PredaScriptParser::ScopeContext *ctx) = 0;

  virtual void enterShardScope(PredaScriptParser::ShardScopeContext *ctx) = 0;
  virtual void exitShardScope(PredaScriptParser::ShardScopeContext *ctx) = 0;

  virtual void enterAddressScope(PredaScriptParser::AddressScopeContext *ctx) = 0;
  virtual void exitAddressScope(PredaScriptParser::AddressScopeContext *ctx) = 0;

  virtual void enterJsonParameters(PredaScriptParser::JsonParametersContext *ctx) = 0;
  virtual void exitJsonParameters(PredaScriptParser::JsonParametersContext *ctx) = 0;

  virtual void enterJsonParameter(PredaScriptParser::JsonParameterContext *ctx) = 0;
  virtual void exitJsonParameter(PredaScriptParser::JsonParameterContext *ctx) = 0;

  virtual void enterJsonKey(PredaScriptParser::JsonKeyContext *ctx) = 0;
  virtual void exitJsonKey(PredaScriptParser::JsonKeyContext *ctx) = 0;

  virtual void enterJsonValue(PredaScriptParser::JsonValueContext *ctx) = 0;
  virtual void exitJsonValue(PredaScriptParser::JsonValueContext *ctx) = 0;

  virtual void enterPrimaryValue(PredaScriptParser::PrimaryValueContext *ctx) = 0;
  virtual void exitPrimaryValue(PredaScriptParser::PrimaryValueContext *ctx) = 0;

  virtual void enterArrayValue(PredaScriptParser::ArrayValueContext *ctx) = 0;
  virtual void exitArrayValue(PredaScriptParser::ArrayValueContext *ctx) = 0;

  virtual void enterConcreteValue(PredaScriptParser::ConcreteValueContext *ctx) = 0;
  virtual void exitConcreteValue(PredaScriptParser::ConcreteValueContext *ctx) = 0;

  virtual void enterToBeAssignedValue(PredaScriptParser::ToBeAssignedValueContext *ctx) = 0;
  virtual void exitToBeAssignedValue(PredaScriptParser::ToBeAssignedValueContext *ctx) = 0;

  virtual void enterBigintRandom(PredaScriptParser::BigintRandomContext *ctx) = 0;
  virtual void exitBigintRandom(PredaScriptParser::BigintRandomContext *ctx) = 0;

  virtual void enterIntExpression(PredaScriptParser::IntExpressionContext *ctx) = 0;
  virtual void exitIntExpression(PredaScriptParser::IntExpressionContext *ctx) = 0;

  virtual void enterIntRandom(PredaScriptParser::IntRandomContext *ctx) = 0;
  virtual void exitIntRandom(PredaScriptParser::IntRandomContext *ctx) = 0;

  virtual void enterRandomRange(PredaScriptParser::RandomRangeContext *ctx) = 0;
  virtual void exitRandomRange(PredaScriptParser::RandomRangeContext *ctx) = 0;

  virtual void enterSuppliedTokens(PredaScriptParser::SuppliedTokensContext *ctx) = 0;
  virtual void exitSuppliedTokens(PredaScriptParser::SuppliedTokensContext *ctx) = 0;

  virtual void enterToken(PredaScriptParser::TokenContext *ctx) = 0;
  virtual void exitToken(PredaScriptParser::TokenContext *ctx) = 0;

  virtual void enterDebugInfo(PredaScriptParser::DebugInfoContext *ctx) = 0;
  virtual void exitDebugInfo(PredaScriptParser::DebugInfoContext *ctx) = 0;

  virtual void enterLogInfo(PredaScriptParser::LogInfoContext *ctx) = 0;
  virtual void exitLogInfo(PredaScriptParser::LogInfoContext *ctx) = 0;

  virtual void enterNormalLog(PredaScriptParser::NormalLogContext *ctx) = 0;
  virtual void exitNormalLog(PredaScriptParser::NormalLogContext *ctx) = 0;

  virtual void enterLogHighlight(PredaScriptParser::LogHighlightContext *ctx) = 0;
  virtual void exitLogHighlight(PredaScriptParser::LogHighlightContext *ctx) = 0;

  virtual void enterLogWarning(PredaScriptParser::LogWarningContext *ctx) = 0;
  virtual void exitLogWarning(PredaScriptParser::LogWarningContext *ctx) = 0;

  virtual void enterLogError(PredaScriptParser::LogErrorContext *ctx) = 0;
  virtual void exitLogError(PredaScriptParser::LogErrorContext *ctx) = 0;

  virtual void enterTimeInfo(PredaScriptParser::TimeInfoContext *ctx) = 0;
  virtual void exitTimeInfo(PredaScriptParser::TimeInfoContext *ctx) = 0;

  virtual void enterStopWatchRestart(PredaScriptParser::StopWatchRestartContext *ctx) = 0;
  virtual void exitStopWatchRestart(PredaScriptParser::StopWatchRestartContext *ctx) = 0;

  virtual void enterStopWatchReport(PredaScriptParser::StopWatchReportContext *ctx) = 0;
  virtual void exitStopWatchReport(PredaScriptParser::StopWatchReportContext *ctx) = 0;

  virtual void enterViz(PredaScriptParser::VizContext *ctx) = 0;
  virtual void exitViz(PredaScriptParser::VizContext *ctx) = 0;

  virtual void enterVizBlock(PredaScriptParser::VizBlockContext *ctx) = 0;
  virtual void exitVizBlock(PredaScriptParser::VizBlockContext *ctx) = 0;

  virtual void enterVizAddr(PredaScriptParser::VizAddrContext *ctx) = 0;
  virtual void exitVizAddr(PredaScriptParser::VizAddrContext *ctx) = 0;

  virtual void enterVizShard(PredaScriptParser::VizShardContext *ctx) = 0;
  virtual void exitVizShard(PredaScriptParser::VizShardContext *ctx) = 0;

  virtual void enterVizTxn(PredaScriptParser::VizTxnContext *ctx) = 0;
  virtual void exitVizTxn(PredaScriptParser::VizTxnContext *ctx) = 0;

  virtual void enterVizTrace(PredaScriptParser::VizTraceContext *ctx) = 0;
  virtual void exitVizTrace(PredaScriptParser::VizTraceContext *ctx) = 0;

  virtual void enterVizSection(PredaScriptParser::VizSectionContext *ctx) = 0;
  virtual void exitVizSection(PredaScriptParser::VizSectionContext *ctx) = 0;

  virtual void enterVizProfiling(PredaScriptParser::VizProfilingContext *ctx) = 0;
  virtual void exitVizProfiling(PredaScriptParser::VizProfilingContext *ctx) = 0;

  virtual void enterVizUintScope(PredaScriptParser::VizUintScopeContext *ctx) = 0;
  virtual void exitVizUintScope(PredaScriptParser::VizUintScopeContext *ctx) = 0;

  virtual void enterUintScope(PredaScriptParser::UintScopeContext *ctx) = 0;
  virtual void exitUintScope(PredaScriptParser::UintScopeContext *ctx) = 0;

  virtual void enterScopeTarget(PredaScriptParser::ScopeTargetContext *ctx) = 0;
  virtual void exitScopeTarget(PredaScriptParser::ScopeTargetContext *ctx) = 0;

  virtual void enterNumberLiteral(PredaScriptParser::NumberLiteralContext *ctx) = 0;
  virtual void exitNumberLiteral(PredaScriptParser::NumberLiteralContext *ctx) = 0;

  virtual void enterHexLiteral(PredaScriptParser::HexLiteralContext *ctx) = 0;
  virtual void exitHexLiteral(PredaScriptParser::HexLiteralContext *ctx) = 0;

  virtual void enterStringLiteral(PredaScriptParser::StringLiteralContext *ctx) = 0;
  virtual void exitStringLiteral(PredaScriptParser::StringLiteralContext *ctx) = 0;

  virtual void enterBoolLiteral(PredaScriptParser::BoolLiteralContext *ctx) = 0;
  virtual void exitBoolLiteral(PredaScriptParser::BoolLiteralContext *ctx) = 0;

  virtual void enterEd25519Address(PredaScriptParser::Ed25519AddressContext *ctx) = 0;
  virtual void exitEd25519Address(PredaScriptParser::Ed25519AddressContext *ctx) = 0;

  virtual void enterIdentifier(PredaScriptParser::IdentifierContext *ctx) = 0;
  virtual void exitIdentifier(PredaScriptParser::IdentifierContext *ctx) = 0;

  virtual void enterFileName(PredaScriptParser::FileNameContext *ctx) = 0;
  virtual void exitFileName(PredaScriptParser::FileNameContext *ctx) = 0;

  virtual void enterDirectivePath(PredaScriptParser::DirectivePathContext *ctx) = 0;
  virtual void exitDirectivePath(PredaScriptParser::DirectivePathContext *ctx) = 0;


};

