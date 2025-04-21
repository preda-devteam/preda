
// Generated from PredaScript.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "PredaScriptListener.h"


/**
 * This class provides an empty implementation of PredaScriptListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  PredaScriptBaseListener : public PredaScriptListener {
public:

  virtual void enterScripts(PredaScriptParser::ScriptsContext * /*ctx*/) override { }
  virtual void exitScripts(PredaScriptParser::ScriptsContext * /*ctx*/) override { }

  virtual void enterScript(PredaScriptParser::ScriptContext * /*ctx*/) override { }
  virtual void exitScript(PredaScriptParser::ScriptContext * /*ctx*/) override { }

  virtual void enterChainOperation(PredaScriptParser::ChainOperationContext * /*ctx*/) override { }
  virtual void exitChainOperation(PredaScriptParser::ChainOperationContext * /*ctx*/) override { }

  virtual void enterAwaitChain(PredaScriptParser::AwaitChainContext * /*ctx*/) override { }
  virtual void exitAwaitChain(PredaScriptParser::AwaitChainContext * /*ctx*/) override { }

  virtual void enterStepChain(PredaScriptParser::StepChainContext * /*ctx*/) override { }
  virtual void exitStepChain(PredaScriptParser::StepChainContext * /*ctx*/) override { }

  virtual void enterRunChain(PredaScriptParser::RunChainContext * /*ctx*/) override { }
  virtual void exitRunChain(PredaScriptParser::RunChainContext * /*ctx*/) override { }

  virtual void enterStopChain(PredaScriptParser::StopChainContext * /*ctx*/) override { }
  virtual void exitStopChain(PredaScriptParser::StopChainContext * /*ctx*/) override { }

  virtual void enterGetChainInfo(PredaScriptParser::GetChainInfoContext * /*ctx*/) override { }
  virtual void exitGetChainInfo(PredaScriptParser::GetChainInfoContext * /*ctx*/) override { }

  virtual void enterDeployContractOnChain(PredaScriptParser::DeployContractOnChainContext * /*ctx*/) override { }
  virtual void exitDeployContractOnChain(PredaScriptParser::DeployContractOnChainContext * /*ctx*/) override { }

  virtual void enterContractProperties(PredaScriptParser::ContractPropertiesContext * /*ctx*/) override { }
  virtual void exitContractProperties(PredaScriptParser::ContractPropertiesContext * /*ctx*/) override { }

  virtual void enterContractProperty(PredaScriptParser::ContractPropertyContext * /*ctx*/) override { }
  virtual void exitContractProperty(PredaScriptParser::ContractPropertyContext * /*ctx*/) override { }

  virtual void enterPredaFile(PredaScriptParser::PredaFileContext * /*ctx*/) override { }
  virtual void exitPredaFile(PredaScriptParser::PredaFileContext * /*ctx*/) override { }

  virtual void enterXtlFile(PredaScriptParser::XtlFileContext * /*ctx*/) override { }
  virtual void exitXtlFile(PredaScriptParser::XtlFileContext * /*ctx*/) override { }

  virtual void enterBatchInsertTxnOnChain(PredaScriptParser::BatchInsertTxnOnChainContext * /*ctx*/) override { }
  virtual void exitBatchInsertTxnOnChain(PredaScriptParser::BatchInsertTxnOnChainContext * /*ctx*/) override { }

  virtual void enterSetGasLimit(PredaScriptParser::SetGasLimitContext * /*ctx*/) override { }
  virtual void exitSetGasLimit(PredaScriptParser::SetGasLimitContext * /*ctx*/) override { }

  virtual void enterVariableDeclaration(PredaScriptParser::VariableDeclarationContext * /*ctx*/) override { }
  virtual void exitVariableDeclaration(PredaScriptParser::VariableDeclarationContext * /*ctx*/) override { }

  virtual void enterVariableAssign(PredaScriptParser::VariableAssignContext * /*ctx*/) override { }
  virtual void exitVariableAssign(PredaScriptParser::VariableAssignContext * /*ctx*/) override { }

  virtual void enterVarName(PredaScriptParser::VarNameContext * /*ctx*/) override { }
  virtual void exitVarName(PredaScriptParser::VarNameContext * /*ctx*/) override { }

  virtual void enterVarValue(PredaScriptParser::VarValueContext * /*ctx*/) override { }
  virtual void exitVarValue(PredaScriptParser::VarValueContext * /*ctx*/) override { }

  virtual void enterDataReadFromFile(PredaScriptParser::DataReadFromFileContext * /*ctx*/) override { }
  virtual void exitDataReadFromFile(PredaScriptParser::DataReadFromFileContext * /*ctx*/) override { }

  virtual void enterCsvfilePath(PredaScriptParser::CsvfilePathContext * /*ctx*/) override { }
  virtual void exitCsvfilePath(PredaScriptParser::CsvfilePathContext * /*ctx*/) override { }

  virtual void enterConfig(PredaScriptParser::ConfigContext * /*ctx*/) override { }
  virtual void exitConfig(PredaScriptParser::ConfigContext * /*ctx*/) override { }

  virtual void enterConfigState(PredaScriptParser::ConfigStateContext * /*ctx*/) override { }
  virtual void exitConfigState(PredaScriptParser::ConfigStateContext * /*ctx*/) override { }

  virtual void enterSetContractState(PredaScriptParser::SetContractStateContext * /*ctx*/) override { }
  virtual void exitSetContractState(PredaScriptParser::SetContractStateContext * /*ctx*/) override { }

  virtual void enterStateScope(PredaScriptParser::StateScopeContext * /*ctx*/) override { }
  virtual void exitStateScope(PredaScriptParser::StateScopeContext * /*ctx*/) override { }

  virtual void enterUpdateState(PredaScriptParser::UpdateStateContext * /*ctx*/) override { }
  virtual void exitUpdateState(PredaScriptParser::UpdateStateContext * /*ctx*/) override { }

  virtual void enterTokenState(PredaScriptParser::TokenStateContext * /*ctx*/) override { }
  virtual void exitTokenState(PredaScriptParser::TokenStateContext * /*ctx*/) override { }

  virtual void enterMintToken(PredaScriptParser::MintTokenContext * /*ctx*/) override { }
  virtual void exitMintToken(PredaScriptParser::MintTokenContext * /*ctx*/) override { }

  virtual void enterTokenSymbol(PredaScriptParser::TokenSymbolContext * /*ctx*/) override { }
  virtual void exitTokenSymbol(PredaScriptParser::TokenSymbolContext * /*ctx*/) override { }

  virtual void enterLoadState(PredaScriptParser::LoadStateContext * /*ctx*/) override { }
  virtual void exitLoadState(PredaScriptParser::LoadStateContext * /*ctx*/) override { }

  virtual void enterJsonFilePath(PredaScriptParser::JsonFilePathContext * /*ctx*/) override { }
  virtual void exitJsonFilePath(PredaScriptParser::JsonFilePathContext * /*ctx*/) override { }

  virtual void enterSaveState(PredaScriptParser::SaveStateContext * /*ctx*/) override { }
  virtual void exitSaveState(PredaScriptParser::SaveStateContext * /*ctx*/) override { }

  virtual void enterConfigAddress(PredaScriptParser::ConfigAddressContext * /*ctx*/) override { }
  virtual void exitConfigAddress(PredaScriptParser::ConfigAddressContext * /*ctx*/) override { }

  virtual void enterConfigRandomizer(PredaScriptParser::ConfigRandomizerContext * /*ctx*/) override { }
  virtual void exitConfigRandomizer(PredaScriptParser::ConfigRandomizerContext * /*ctx*/) override { }

  virtual void enterIssueTxn(PredaScriptParser::IssueTxnContext * /*ctx*/) override { }
  virtual void exitIssueTxn(PredaScriptParser::IssueTxnContext * /*ctx*/) override { }

  virtual void enterTxnReturnInfo(PredaScriptParser::TxnReturnInfoContext * /*ctx*/) override { }
  virtual void exitTxnReturnInfo(PredaScriptParser::TxnReturnInfoContext * /*ctx*/) override { }

  virtual void enterContractId(PredaScriptParser::ContractIdContext * /*ctx*/) override { }
  virtual void exitContractId(PredaScriptParser::ContractIdContext * /*ctx*/) override { }

  virtual void enterContractName(PredaScriptParser::ContractNameContext * /*ctx*/) override { }
  virtual void exitContractName(PredaScriptParser::ContractNameContext * /*ctx*/) override { }

  virtual void enterCvid(PredaScriptParser::CvidContext * /*ctx*/) override { }
  virtual void exitCvid(PredaScriptParser::CvidContext * /*ctx*/) override { }

  virtual void enterFunctionName(PredaScriptParser::FunctionNameContext * /*ctx*/) override { }
  virtual void exitFunctionName(PredaScriptParser::FunctionNameContext * /*ctx*/) override { }

  virtual void enterCount(PredaScriptParser::CountContext * /*ctx*/) override { }
  virtual void exitCount(PredaScriptParser::CountContext * /*ctx*/) override { }

  virtual void enterScope(PredaScriptParser::ScopeContext * /*ctx*/) override { }
  virtual void exitScope(PredaScriptParser::ScopeContext * /*ctx*/) override { }

  virtual void enterShardScope(PredaScriptParser::ShardScopeContext * /*ctx*/) override { }
  virtual void exitShardScope(PredaScriptParser::ShardScopeContext * /*ctx*/) override { }

  virtual void enterAddressScope(PredaScriptParser::AddressScopeContext * /*ctx*/) override { }
  virtual void exitAddressScope(PredaScriptParser::AddressScopeContext * /*ctx*/) override { }

  virtual void enterJsonParameters(PredaScriptParser::JsonParametersContext * /*ctx*/) override { }
  virtual void exitJsonParameters(PredaScriptParser::JsonParametersContext * /*ctx*/) override { }

  virtual void enterJsonParameter(PredaScriptParser::JsonParameterContext * /*ctx*/) override { }
  virtual void exitJsonParameter(PredaScriptParser::JsonParameterContext * /*ctx*/) override { }

  virtual void enterJsonKey(PredaScriptParser::JsonKeyContext * /*ctx*/) override { }
  virtual void exitJsonKey(PredaScriptParser::JsonKeyContext * /*ctx*/) override { }

  virtual void enterJsonValue(PredaScriptParser::JsonValueContext * /*ctx*/) override { }
  virtual void exitJsonValue(PredaScriptParser::JsonValueContext * /*ctx*/) override { }

  virtual void enterPrimaryValue(PredaScriptParser::PrimaryValueContext * /*ctx*/) override { }
  virtual void exitPrimaryValue(PredaScriptParser::PrimaryValueContext * /*ctx*/) override { }

  virtual void enterArrayValue(PredaScriptParser::ArrayValueContext * /*ctx*/) override { }
  virtual void exitArrayValue(PredaScriptParser::ArrayValueContext * /*ctx*/) override { }

  virtual void enterConcreteValue(PredaScriptParser::ConcreteValueContext * /*ctx*/) override { }
  virtual void exitConcreteValue(PredaScriptParser::ConcreteValueContext * /*ctx*/) override { }

  virtual void enterToBeAssignedValue(PredaScriptParser::ToBeAssignedValueContext * /*ctx*/) override { }
  virtual void exitToBeAssignedValue(PredaScriptParser::ToBeAssignedValueContext * /*ctx*/) override { }

  virtual void enterBigintRandom(PredaScriptParser::BigintRandomContext * /*ctx*/) override { }
  virtual void exitBigintRandom(PredaScriptParser::BigintRandomContext * /*ctx*/) override { }

  virtual void enterIntExpression(PredaScriptParser::IntExpressionContext * /*ctx*/) override { }
  virtual void exitIntExpression(PredaScriptParser::IntExpressionContext * /*ctx*/) override { }

  virtual void enterIntRandom(PredaScriptParser::IntRandomContext * /*ctx*/) override { }
  virtual void exitIntRandom(PredaScriptParser::IntRandomContext * /*ctx*/) override { }

  virtual void enterRandomRange(PredaScriptParser::RandomRangeContext * /*ctx*/) override { }
  virtual void exitRandomRange(PredaScriptParser::RandomRangeContext * /*ctx*/) override { }

  virtual void enterSuppliedTokens(PredaScriptParser::SuppliedTokensContext * /*ctx*/) override { }
  virtual void exitSuppliedTokens(PredaScriptParser::SuppliedTokensContext * /*ctx*/) override { }

  virtual void enterToken(PredaScriptParser::TokenContext * /*ctx*/) override { }
  virtual void exitToken(PredaScriptParser::TokenContext * /*ctx*/) override { }

  virtual void enterDebugInfo(PredaScriptParser::DebugInfoContext * /*ctx*/) override { }
  virtual void exitDebugInfo(PredaScriptParser::DebugInfoContext * /*ctx*/) override { }

  virtual void enterLogInfo(PredaScriptParser::LogInfoContext * /*ctx*/) override { }
  virtual void exitLogInfo(PredaScriptParser::LogInfoContext * /*ctx*/) override { }

  virtual void enterNormalLog(PredaScriptParser::NormalLogContext * /*ctx*/) override { }
  virtual void exitNormalLog(PredaScriptParser::NormalLogContext * /*ctx*/) override { }

  virtual void enterLogHighlight(PredaScriptParser::LogHighlightContext * /*ctx*/) override { }
  virtual void exitLogHighlight(PredaScriptParser::LogHighlightContext * /*ctx*/) override { }

  virtual void enterLogWarning(PredaScriptParser::LogWarningContext * /*ctx*/) override { }
  virtual void exitLogWarning(PredaScriptParser::LogWarningContext * /*ctx*/) override { }

  virtual void enterLogError(PredaScriptParser::LogErrorContext * /*ctx*/) override { }
  virtual void exitLogError(PredaScriptParser::LogErrorContext * /*ctx*/) override { }

  virtual void enterTimeInfo(PredaScriptParser::TimeInfoContext * /*ctx*/) override { }
  virtual void exitTimeInfo(PredaScriptParser::TimeInfoContext * /*ctx*/) override { }

  virtual void enterStopWatchRestart(PredaScriptParser::StopWatchRestartContext * /*ctx*/) override { }
  virtual void exitStopWatchRestart(PredaScriptParser::StopWatchRestartContext * /*ctx*/) override { }

  virtual void enterStopWatchReport(PredaScriptParser::StopWatchReportContext * /*ctx*/) override { }
  virtual void exitStopWatchReport(PredaScriptParser::StopWatchReportContext * /*ctx*/) override { }

  virtual void enterViz(PredaScriptParser::VizContext * /*ctx*/) override { }
  virtual void exitViz(PredaScriptParser::VizContext * /*ctx*/) override { }

  virtual void enterVizBlock(PredaScriptParser::VizBlockContext * /*ctx*/) override { }
  virtual void exitVizBlock(PredaScriptParser::VizBlockContext * /*ctx*/) override { }

  virtual void enterVizAddr(PredaScriptParser::VizAddrContext * /*ctx*/) override { }
  virtual void exitVizAddr(PredaScriptParser::VizAddrContext * /*ctx*/) override { }

  virtual void enterVizShard(PredaScriptParser::VizShardContext * /*ctx*/) override { }
  virtual void exitVizShard(PredaScriptParser::VizShardContext * /*ctx*/) override { }

  virtual void enterVizTxn(PredaScriptParser::VizTxnContext * /*ctx*/) override { }
  virtual void exitVizTxn(PredaScriptParser::VizTxnContext * /*ctx*/) override { }

  virtual void enterVizTrace(PredaScriptParser::VizTraceContext * /*ctx*/) override { }
  virtual void exitVizTrace(PredaScriptParser::VizTraceContext * /*ctx*/) override { }

  virtual void enterVizSection(PredaScriptParser::VizSectionContext * /*ctx*/) override { }
  virtual void exitVizSection(PredaScriptParser::VizSectionContext * /*ctx*/) override { }

  virtual void enterVizProfiling(PredaScriptParser::VizProfilingContext * /*ctx*/) override { }
  virtual void exitVizProfiling(PredaScriptParser::VizProfilingContext * /*ctx*/) override { }

  virtual void enterVizUintScope(PredaScriptParser::VizUintScopeContext * /*ctx*/) override { }
  virtual void exitVizUintScope(PredaScriptParser::VizUintScopeContext * /*ctx*/) override { }

  virtual void enterUintScope(PredaScriptParser::UintScopeContext * /*ctx*/) override { }
  virtual void exitUintScope(PredaScriptParser::UintScopeContext * /*ctx*/) override { }

  virtual void enterScopeTarget(PredaScriptParser::ScopeTargetContext * /*ctx*/) override { }
  virtual void exitScopeTarget(PredaScriptParser::ScopeTargetContext * /*ctx*/) override { }

  virtual void enterNumberLiteral(PredaScriptParser::NumberLiteralContext * /*ctx*/) override { }
  virtual void exitNumberLiteral(PredaScriptParser::NumberLiteralContext * /*ctx*/) override { }

  virtual void enterHexLiteral(PredaScriptParser::HexLiteralContext * /*ctx*/) override { }
  virtual void exitHexLiteral(PredaScriptParser::HexLiteralContext * /*ctx*/) override { }

  virtual void enterStringLiteral(PredaScriptParser::StringLiteralContext * /*ctx*/) override { }
  virtual void exitStringLiteral(PredaScriptParser::StringLiteralContext * /*ctx*/) override { }

  virtual void enterBoolLiteral(PredaScriptParser::BoolLiteralContext * /*ctx*/) override { }
  virtual void exitBoolLiteral(PredaScriptParser::BoolLiteralContext * /*ctx*/) override { }

  virtual void enterEd25519Address(PredaScriptParser::Ed25519AddressContext * /*ctx*/) override { }
  virtual void exitEd25519Address(PredaScriptParser::Ed25519AddressContext * /*ctx*/) override { }

  virtual void enterIdentifier(PredaScriptParser::IdentifierContext * /*ctx*/) override { }
  virtual void exitIdentifier(PredaScriptParser::IdentifierContext * /*ctx*/) override { }

  virtual void enterFileName(PredaScriptParser::FileNameContext * /*ctx*/) override { }
  virtual void exitFileName(PredaScriptParser::FileNameContext * /*ctx*/) override { }

  virtual void enterDirectivePath(PredaScriptParser::DirectivePathContext * /*ctx*/) override { }
  virtual void exitDirectivePath(PredaScriptParser::DirectivePathContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

