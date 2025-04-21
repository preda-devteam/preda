
// Generated from PredaScript.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"




class  PredaScriptParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, T__24 = 25, T__25 = 26, 
    T__26 = 27, T__27 = 28, T__28 = 29, T__29 = 30, T__30 = 31, T__31 = 32, 
    T__32 = 33, T__33 = 34, T__34 = 35, T__35 = 36, T__36 = 37, T__37 = 38, 
    T__38 = 39, T__39 = 40, T__40 = 41, T__41 = 42, T__42 = 43, T__43 = 44, 
    T__44 = 45, T__45 = 46, T__46 = 47, T__47 = 48, T__48 = 49, T__49 = 50, 
    T__50 = 51, T__51 = 52, T__52 = 53, T__53 = 54, T__54 = 55, T__55 = 56, 
    T__56 = 57, WASM = 58, NATIVE = 59, RANDOM = 60, BIGINT = 61, ALL = 62, 
    GLOBAL = 63, SHARD = 64, ADDRESS = 65, TrueKeyword = 66, FalseKeyword = 67, 
    DecimalNumber = 68, HexNumber = 69, StringLiteral = 70, Ed25519Address = 71, 
    Identifier = 72, WINPATH = 73, WIN_ABSOLUTE_PATH = 74, WIN_REALATIVE_PATH = 75, 
    UNIXPATH = 76, UNIX_ABSOLUTE_PATH = 77, UNIX_REALATIVE_PATH = 78, NotDefinedValue = 79, 
    NewLineBackSlash = 80, WS = 81, CommentSingleLine = 82, CommentMultiLine = 83
  };

  enum {
    RuleScripts = 0, RuleScript = 1, RuleChainOperation = 2, RuleAwaitChain = 3, 
    RuleStepChain = 4, RuleRunChain = 5, RuleStopChain = 6, RuleGetChainInfo = 7, 
    RuleDeployContractOnChain = 8, RuleContractProperties = 9, RuleContractProperty = 10, 
    RulePredaFile = 11, RuleXtlFile = 12, RuleBatchInsertTxnOnChain = 13, 
    RuleSetGasLimit = 14, RuleVariableDeclaration = 15, RuleVariableAssign = 16, 
    RuleVarName = 17, RuleVarValue = 18, RuleDataReadFromFile = 19, RuleCsvfilePath = 20, 
    RuleConfig = 21, RuleConfigState = 22, RuleSetContractState = 23, RuleStateScope = 24, 
    RuleUpdateState = 25, RuleTokenState = 26, RuleMintToken = 27, RuleTokenSymbol = 28, 
    RuleLoadState = 29, RuleJsonFilePath = 30, RuleSaveState = 31, RuleConfigAddress = 32, 
    RuleConfigRandomizer = 33, RuleIssueTxn = 34, RuleTxnReturnInfo = 35, 
    RuleContractId = 36, RuleContractName = 37, RuleCvid = 38, RuleFunctionName = 39, 
    RuleCount = 40, RuleScope = 41, RuleShardScope = 42, RuleAddressScope = 43, 
    RuleJsonParameters = 44, RuleJsonParameter = 45, RuleJsonKey = 46, RuleJsonValue = 47, 
    RulePrimaryValue = 48, RuleArrayValue = 49, RuleConcreteValue = 50, 
    RuleToBeAssignedValue = 51, RuleBigintRandom = 52, RuleIntExpression = 53, 
    RuleIntRandom = 54, RuleRandomRange = 55, RuleSuppliedTokens = 56, RuleToken = 57, 
    RuleDebugInfo = 58, RuleLogInfo = 59, RuleNormalLog = 60, RuleLogHighlight = 61, 
    RuleLogWarning = 62, RuleLogError = 63, RuleTimeInfo = 64, RuleStopWatchRestart = 65, 
    RuleStopWatchReport = 66, RuleViz = 67, RuleVizBlock = 68, RuleVizAddr = 69, 
    RuleVizShard = 70, RuleVizTxn = 71, RuleVizTrace = 72, RuleVizSection = 73, 
    RuleVizProfiling = 74, RuleVizUintScope = 75, RuleUintScope = 76, RuleScopeTarget = 77, 
    RuleNumberLiteral = 78, RuleHexLiteral = 79, RuleStringLiteral = 80, 
    RuleBoolLiteral = 81, RuleEd25519Address = 82, RuleIdentifier = 83, 
    RuleFileName = 84, RuleDirectivePath = 85
  };

  explicit PredaScriptParser(antlr4::TokenStream *input);

  PredaScriptParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~PredaScriptParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ScriptsContext;
  class ScriptContext;
  class ChainOperationContext;
  class AwaitChainContext;
  class StepChainContext;
  class RunChainContext;
  class StopChainContext;
  class GetChainInfoContext;
  class DeployContractOnChainContext;
  class ContractPropertiesContext;
  class ContractPropertyContext;
  class PredaFileContext;
  class XtlFileContext;
  class BatchInsertTxnOnChainContext;
  class SetGasLimitContext;
  class VariableDeclarationContext;
  class VariableAssignContext;
  class VarNameContext;
  class VarValueContext;
  class DataReadFromFileContext;
  class CsvfilePathContext;
  class ConfigContext;
  class ConfigStateContext;
  class SetContractStateContext;
  class StateScopeContext;
  class UpdateStateContext;
  class TokenStateContext;
  class MintTokenContext;
  class TokenSymbolContext;
  class LoadStateContext;
  class JsonFilePathContext;
  class SaveStateContext;
  class ConfigAddressContext;
  class ConfigRandomizerContext;
  class IssueTxnContext;
  class TxnReturnInfoContext;
  class ContractIdContext;
  class ContractNameContext;
  class CvidContext;
  class FunctionNameContext;
  class CountContext;
  class ScopeContext;
  class ShardScopeContext;
  class AddressScopeContext;
  class JsonParametersContext;
  class JsonParameterContext;
  class JsonKeyContext;
  class JsonValueContext;
  class PrimaryValueContext;
  class ArrayValueContext;
  class ConcreteValueContext;
  class ToBeAssignedValueContext;
  class BigintRandomContext;
  class IntExpressionContext;
  class IntRandomContext;
  class RandomRangeContext;
  class SuppliedTokensContext;
  class TokenContext;
  class DebugInfoContext;
  class LogInfoContext;
  class NormalLogContext;
  class LogHighlightContext;
  class LogWarningContext;
  class LogErrorContext;
  class TimeInfoContext;
  class StopWatchRestartContext;
  class StopWatchReportContext;
  class VizContext;
  class VizBlockContext;
  class VizAddrContext;
  class VizShardContext;
  class VizTxnContext;
  class VizTraceContext;
  class VizSectionContext;
  class VizProfilingContext;
  class VizUintScopeContext;
  class UintScopeContext;
  class ScopeTargetContext;
  class NumberLiteralContext;
  class HexLiteralContext;
  class StringLiteralContext;
  class BoolLiteralContext;
  class Ed25519AddressContext;
  class IdentifierContext;
  class FileNameContext;
  class DirectivePathContext; 

  class  ScriptsContext : public antlr4::ParserRuleContext {
  public:
    ScriptsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<ScriptContext *> script();
    ScriptContext* script(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ScriptsContext* scripts();

  class  ScriptContext : public antlr4::ParserRuleContext {
  public:
    ScriptContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ChainOperationContext *chainOperation();
    VariableDeclarationContext *variableDeclaration();
    ConfigContext *config();
    IssueTxnContext *issueTxn();
    DebugInfoContext *debugInfo();
    VizContext *viz();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ScriptContext* script();

  class  ChainOperationContext : public antlr4::ParserRuleContext {
  public:
    ChainOperationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AwaitChainContext *awaitChain();
    StepChainContext *stepChain();
    RunChainContext *runChain();
    StopChainContext *stopChain();
    GetChainInfoContext *getChainInfo();
    DeployContractOnChainContext *deployContractOnChain();
    BatchInsertTxnOnChainContext *batchInsertTxnOnChain();
    SetGasLimitContext *setGasLimit();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ChainOperationContext* chainOperation();

  class  AwaitChainContext : public antlr4::ParserRuleContext {
  public:
    AwaitChainContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AwaitChainContext* awaitChain();

  class  StepChainContext : public antlr4::ParserRuleContext {
  public:
    StepChainContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StepChainContext* stepChain();

  class  RunChainContext : public antlr4::ParserRuleContext {
  public:
    RunChainContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RunChainContext* runChain();

  class  StopChainContext : public antlr4::ParserRuleContext {
  public:
    StopChainContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StopChainContext* stopChain();

  class  GetChainInfoContext : public antlr4::ParserRuleContext {
  public:
    GetChainInfoContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  GetChainInfoContext* getChainInfo();

  class  DeployContractOnChainContext : public antlr4::ParserRuleContext {
  public:
    DeployContractOnChainContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ContractPropertiesContext *contractProperties();
    AddressScopeContext *addressScope();
    ShardScopeContext *shardScope();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DeployContractOnChainContext* deployContractOnChain();

  class  ContractPropertiesContext : public antlr4::ParserRuleContext {
  public:
    ContractPropertiesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ContractPropertyContext *> contractProperty();
    ContractPropertyContext* contractProperty(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ContractPropertiesContext* contractProperties();

  class  ContractPropertyContext : public antlr4::ParserRuleContext {
  public:
    ContractPropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PredaFileContext *predaFile();
    XtlFileContext *xtlFile();
    JsonParametersContext *jsonParameters();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ContractPropertyContext* contractProperty();

  class  PredaFileContext : public antlr4::ParserRuleContext {
  public:
    PredaFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    DirectivePathContext *directivePath();
    antlr4::tree::TerminalNode *NATIVE();
    antlr4::tree::TerminalNode *WASM();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PredaFileContext* predaFile();

  class  XtlFileContext : public antlr4::ParserRuleContext {
  public:
    XtlFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    DirectivePathContext *directivePath();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  XtlFileContext* xtlFile();

  class  BatchInsertTxnOnChainContext : public antlr4::ParserRuleContext {
  public:
    BatchInsertTxnOnChainContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VarNameContext *varName();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BatchInsertTxnOnChainContext* batchInsertTxnOnChain();

  class  SetGasLimitContext : public antlr4::ParserRuleContext {
  public:
    SetGasLimitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumberLiteralContext *numberLiteral();
    antlr4::tree::TerminalNode *GLOBAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SetGasLimitContext* setGasLimit();

  class  VariableDeclarationContext : public antlr4::ParserRuleContext {
  public:
    VariableDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VariableAssignContext *variableAssign();
    DataReadFromFileContext *dataReadFromFile();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VariableDeclarationContext* variableDeclaration();

  class  VariableAssignContext : public antlr4::ParserRuleContext {
  public:
    VariableAssignContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VarNameContext *varName();
    VarValueContext *varValue();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VariableAssignContext* variableAssign();

  class  VarNameContext : public antlr4::ParserRuleContext {
  public:
    VarNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VarNameContext* varName();

  class  VarValueContext : public antlr4::ParserRuleContext {
  public:
    VarValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    StringLiteralContext *stringLiteral();
    NumberLiteralContext *numberLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VarValueContext* varValue();

  class  DataReadFromFileContext : public antlr4::ParserRuleContext {
  public:
    DataReadFromFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VarNameContext *varName();
    CsvfilePathContext *csvfilePath();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DataReadFromFileContext* dataReadFromFile();

  class  CsvfilePathContext : public antlr4::ParserRuleContext {
  public:
    CsvfilePathContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FileNameContext *fileName();
    DirectivePathContext *directivePath();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CsvfilePathContext* csvfilePath();

  class  ConfigContext : public antlr4::ParserRuleContext {
  public:
    ConfigContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConfigStateContext *configState();
    ConfigAddressContext *configAddress();
    ConfigRandomizerContext *configRandomizer();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConfigContext* config();

  class  ConfigStateContext : public antlr4::ParserRuleContext {
  public:
    ConfigStateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SetContractStateContext *setContractState();
    UpdateStateContext *updateState();
    TokenStateContext *tokenState();
    LoadStateContext *loadState();
    SaveStateContext *saveState();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConfigStateContext* configState();

  class  SetContractStateContext : public antlr4::ParserRuleContext {
  public:
    SetContractStateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ContractIdContext *contractId();
    StateScopeContext *stateScope();
    JsonParametersContext *jsonParameters();
    ScopeContext *scope();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SetContractStateContext* setContractState();

  class  StateScopeContext : public antlr4::ParserRuleContext {
  public:
    StateScopeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GLOBAL();
    antlr4::tree::TerminalNode *SHARD();
    antlr4::tree::TerminalNode *ADDRESS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StateScopeContext* stateScope();

  class  UpdateStateContext : public antlr4::ParserRuleContext {
  public:
    UpdateStateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ContractIdContext *contractId();
    StateScopeContext *stateScope();
    JsonParametersContext *jsonParameters();
    ScopeContext *scope();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  UpdateStateContext* updateState();

  class  TokenStateContext : public antlr4::ParserRuleContext {
  public:
    TokenStateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MintTokenContext *mintToken();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TokenStateContext* tokenState();

  class  MintTokenContext : public antlr4::ParserRuleContext {
  public:
    MintTokenContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    TokenSymbolContext *tokenSymbol();
    ContractIdContext *contractId();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MintTokenContext* mintToken();

  class  TokenSymbolContext : public antlr4::ParserRuleContext {
  public:
    TokenSymbolContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TokenSymbolContext* tokenSymbol();

  class  LoadStateContext : public antlr4::ParserRuleContext {
  public:
    LoadStateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StateScopeContext *stateScope();
    JsonFilePathContext *jsonFilePath();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LoadStateContext* loadState();

  class  JsonFilePathContext : public antlr4::ParserRuleContext {
  public:
    JsonFilePathContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FileNameContext *fileName();
    DirectivePathContext *directivePath();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  JsonFilePathContext* jsonFilePath();

  class  SaveStateContext : public antlr4::ParserRuleContext {
  public:
    SaveStateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StateScopeContext *stateScope();
    FileNameContext *fileName();
    ContractIdContext *contractId();
    antlr4::tree::TerminalNode *ALL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SaveStateContext* saveState();

  class  ConfigAddressContext : public antlr4::ParserRuleContext {
  public:
    ConfigAddressContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumberLiteralContext *numberLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConfigAddressContext* configAddress();

  class  ConfigRandomizerContext : public antlr4::ParserRuleContext {
  public:
    ConfigRandomizerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RANDOM();
    NumberLiteralContext *numberLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConfigRandomizerContext* configRandomizer();

  class  IssueTxnContext : public antlr4::ParserRuleContext {
  public:
    IssueTxnContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ContractIdContext *contractId();
    FunctionNameContext *functionName();
    TxnReturnInfoContext *txnReturnInfo();
    CountContext *count();
    ScopeContext *scope();
    JsonParametersContext *jsonParameters();
    SuppliedTokensContext *suppliedTokens();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IssueTxnContext* issueTxn();

  class  TxnReturnInfoContext : public antlr4::ParserRuleContext {
  public:
    TxnReturnInfoContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TxnReturnInfoContext* txnReturnInfo();

  class  ContractIdContext : public antlr4::ParserRuleContext {
  public:
    ContractIdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ContractNameContext *contractName();
    CvidContext *cvid();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ContractIdContext* contractId();

  class  ContractNameContext : public antlr4::ParserRuleContext {
  public:
    PredaScriptParser::IdentifierContext *dappName = nullptr;
    ContractNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ContractNameContext* contractName();

  class  CvidContext : public antlr4::ParserRuleContext {
  public:
    CvidContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumberLiteralContext *numberLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CvidContext* cvid();

  class  FunctionNameContext : public antlr4::ParserRuleContext {
  public:
    FunctionNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionNameContext* functionName();

  class  CountContext : public antlr4::ParserRuleContext {
  public:
    CountContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumberLiteralContext *numberLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CountContext* count();

  class  ScopeContext : public antlr4::ParserRuleContext {
  public:
    ScopeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ShardScopeContext *shardScope();
    AddressScopeContext *addressScope();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ScopeContext* scope();

  class  ShardScopeContext : public antlr4::ParserRuleContext {
  public:
    ShardScopeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumberLiteralContext *numberLiteral();
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *RANDOM();
    antlr4::tree::TerminalNode *ALL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ShardScopeContext* shardScope();

  class  AddressScopeContext : public antlr4::ParserRuleContext {
  public:
    AddressScopeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumberLiteralContext *numberLiteral();
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *RANDOM();
    antlr4::tree::TerminalNode *ALL();
    Ed25519AddressContext *ed25519Address();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AddressScopeContext* addressScope();

  class  JsonParametersContext : public antlr4::ParserRuleContext {
  public:
    JsonParametersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<JsonParameterContext *> jsonParameter();
    JsonParameterContext* jsonParameter(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  JsonParametersContext* jsonParameters();

  class  JsonParameterContext : public antlr4::ParserRuleContext {
  public:
    JsonParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    JsonKeyContext *jsonKey();
    JsonValueContext *jsonValue();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  JsonParameterContext* jsonParameter();

  class  JsonKeyContext : public antlr4::ParserRuleContext {
  public:
    JsonKeyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    ConcreteValueContext *concreteValue();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  JsonKeyContext* jsonKey();

  class  JsonValueContext : public antlr4::ParserRuleContext {
  public:
    JsonValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    JsonParametersContext *jsonParameters();
    PrimaryValueContext *primaryValue();
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  JsonValueContext* jsonValue();

  class  PrimaryValueContext : public antlr4::ParserRuleContext {
  public:
    PrimaryValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ArrayValueContext *arrayValue();
    ConcreteValueContext *concreteValue();
    ToBeAssignedValueContext *toBeAssignedValue();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PrimaryValueContext* primaryValue();

  class  ArrayValueContext : public antlr4::ParserRuleContext {
  public:
    ArrayValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<JsonValueContext *> jsonValue();
    JsonValueContext* jsonValue(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ArrayValueContext* arrayValue();

  class  ConcreteValueContext : public antlr4::ParserRuleContext {
  public:
    ConcreteValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumberLiteralContext *numberLiteral();
    StringLiteralContext *stringLiteral();
    BoolLiteralContext *boolLiteral();
    HexLiteralContext *hexLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConcreteValueContext* concreteValue();

  class  ToBeAssignedValueContext : public antlr4::ParserRuleContext {
  public:
    ToBeAssignedValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AddressScopeContext *addressScope();
    BigintRandomContext *bigintRandom();
    IntExpressionContext *intExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ToBeAssignedValueContext* toBeAssignedValue();

  class  BigintRandomContext : public antlr4::ParserRuleContext {
  public:
    BigintRandomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BIGINT();
    antlr4::tree::TerminalNode *RANDOM();
    NumberLiteralContext *numberLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BigintRandomContext* bigintRandom();

  class  IntExpressionContext : public antlr4::ParserRuleContext {
  public:
    int type = -1;
    IntExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IntRandomContext *intRandom();
    NumberLiteralContext *numberLiteral();
    std::vector<IntExpressionContext *> intExpression();
    IntExpressionContext* intExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IntExpressionContext* intExpression();
  IntExpressionContext* intExpression(int precedence);
  class  IntRandomContext : public antlr4::ParserRuleContext {
  public:
    IntRandomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RANDOM();
    RandomRangeContext *randomRange();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IntRandomContext* intRandom();

  class  RandomRangeContext : public antlr4::ParserRuleContext {
  public:
    PredaScriptParser::IntExpressionContext *min = nullptr;
    PredaScriptParser::IntExpressionContext *max = nullptr;
    RandomRangeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IntExpressionContext *> intExpression();
    IntExpressionContext* intExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RandomRangeContext* randomRange();

  class  SuppliedTokensContext : public antlr4::ParserRuleContext {
  public:
    SuppliedTokensContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TokenContext *> token();
    TokenContext* token(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SuppliedTokensContext* suppliedTokens();

  class  TokenContext : public antlr4::ParserRuleContext {
  public:
    TokenContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    NumberLiteralContext *numberLiteral();
    IntExpressionContext *intExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TokenContext* token();

  class  DebugInfoContext : public antlr4::ParserRuleContext {
  public:
    DebugInfoContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LogInfoContext *logInfo();
    TimeInfoContext *timeInfo();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DebugInfoContext* debugInfo();

  class  LogInfoContext : public antlr4::ParserRuleContext {
  public:
    LogInfoContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NormalLogContext *normalLog();
    LogHighlightContext *logHighlight();
    LogWarningContext *logWarning();
    LogErrorContext *logError();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LogInfoContext* logInfo();

  class  NormalLogContext : public antlr4::ParserRuleContext {
  public:
    NormalLogContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StringLiteralContext *stringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NormalLogContext* normalLog();

  class  LogHighlightContext : public antlr4::ParserRuleContext {
  public:
    LogHighlightContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StringLiteralContext *stringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LogHighlightContext* logHighlight();

  class  LogWarningContext : public antlr4::ParserRuleContext {
  public:
    LogWarningContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StringLiteralContext *stringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LogWarningContext* logWarning();

  class  LogErrorContext : public antlr4::ParserRuleContext {
  public:
    LogErrorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StringLiteralContext *stringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LogErrorContext* logError();

  class  TimeInfoContext : public antlr4::ParserRuleContext {
  public:
    TimeInfoContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StopWatchRestartContext *stopWatchRestart();
    StopWatchReportContext *stopWatchReport();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TimeInfoContext* timeInfo();

  class  StopWatchRestartContext : public antlr4::ParserRuleContext {
  public:
    StopWatchRestartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StopWatchRestartContext* stopWatchRestart();

  class  StopWatchReportContext : public antlr4::ParserRuleContext {
  public:
    StopWatchReportContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StopWatchReportContext* stopWatchReport();

  class  VizContext : public antlr4::ParserRuleContext {
  public:
    VizContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VizBlockContext *vizBlock();
    VizAddrContext *vizAddr();
    VizShardContext *vizShard();
    VizTxnContext *vizTxn();
    VizTraceContext *vizTrace();
    VizSectionContext *vizSection();
    VizProfilingContext *vizProfiling();
    VizUintScopeContext *vizUintScope();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VizContext* viz();

  class  VizBlockContext : public antlr4::ParserRuleContext {
  public:
    VizBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ShardScopeContext *shardScope();
    NumberLiteralContext *numberLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VizBlockContext* vizBlock();

  class  VizAddrContext : public antlr4::ParserRuleContext {
  public:
    VizAddrContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AddressScopeContext *addressScope();
    ContractNameContext *contractName();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VizAddrContext* vizAddr();

  class  VizShardContext : public antlr4::ParserRuleContext {
  public:
    VizShardContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ShardScopeContext *shardScope();
    ContractNameContext *contractName();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VizShardContext* vizShard();

  class  VizTxnContext : public antlr4::ParserRuleContext {
  public:
    VizTxnContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TxnReturnInfoContext *txnReturnInfo();
    NumberLiteralContext *numberLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VizTxnContext* vizTxn();

  class  VizTraceContext : public antlr4::ParserRuleContext {
  public:
    VizTraceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TxnReturnInfoContext *txnReturnInfo();
    NumberLiteralContext *numberLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VizTraceContext* vizTrace();

  class  VizSectionContext : public antlr4::ParserRuleContext {
  public:
    VizSectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StringLiteralContext *stringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VizSectionContext* vizSection();

  class  VizProfilingContext : public antlr4::ParserRuleContext {
  public:
    VizProfilingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VizProfilingContext* vizProfiling();

  class  VizUintScopeContext : public antlr4::ParserRuleContext {
  public:
    VizUintScopeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UintScopeContext *uintScope();
    ContractNameContext *contractName();
    ScopeTargetContext *scopeTarget();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VizUintScopeContext* vizUintScope();

  class  UintScopeContext : public antlr4::ParserRuleContext {
  public:
    UintScopeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ALL();
    NumberLiteralContext *numberLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  UintScopeContext* uintScope();

  class  ScopeTargetContext : public antlr4::ParserRuleContext {
  public:
    ScopeTargetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ALL();
    NumberLiteralContext *numberLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ScopeTargetContext* scopeTarget();

  class  NumberLiteralContext : public antlr4::ParserRuleContext {
  public:
    NumberLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DecimalNumber();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NumberLiteralContext* numberLiteral();

  class  HexLiteralContext : public antlr4::ParserRuleContext {
  public:
    HexLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *HexNumber();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  HexLiteralContext* hexLiteral();

  class  StringLiteralContext : public antlr4::ParserRuleContext {
  public:
    StringLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StringLiteralContext* stringLiteral();

  class  BoolLiteralContext : public antlr4::ParserRuleContext {
  public:
    BoolLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TrueKeyword();
    antlr4::tree::TerminalNode *FalseKeyword();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BoolLiteralContext* boolLiteral();

  class  Ed25519AddressContext : public antlr4::ParserRuleContext {
  public:
    Ed25519AddressContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Ed25519Address();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Ed25519AddressContext* ed25519Address();

  class  IdentifierContext : public antlr4::ParserRuleContext {
  public:
    IdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IdentifierContext* identifier();

  class  FileNameContext : public antlr4::ParserRuleContext {
  public:
    FileNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> Identifier();
    antlr4::tree::TerminalNode* Identifier(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FileNameContext* fileName();

  class  DirectivePathContext : public antlr4::ParserRuleContext {
  public:
    DirectivePathContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WINPATH();
    antlr4::tree::TerminalNode *UNIXPATH();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DirectivePathContext* directivePath();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool intExpressionSempred(IntExpressionContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

