
// Generated from Preda.g4 by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"




class  PredaParser : public antlr4::Parser {
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
    T__50 = 51, T__51 = 52, T__52 = 53, T__53 = 54, T__54 = 55, DoxygenSingle = 56, 
    DoxygenMulti = 57, BreakKeyword = 58, ConstantKeyword = 59, ContinueKeyword = 60, 
    RelayKeyword = 61, SupplyKeyword = 62, IfKeyword = 63, ElseKeyword = 64, 
    ShardKeyword = 65, ShardsKeyword = 66, GlobalKeyword = 67, AddressKeyword = 68, 
    AutoKeyword = 69, MinerKeyword = 70, StructKeyword = 71, EnumKeyword = 72, 
    ContractKeyword = 73, ImportKeyword = 74, FunctionKeyword = 75, PublicKeyword = 76, 
    ExportKeyword = 77, AsKeyword = 78, UsingKeyword = 79, InterfaceKeyword = 80, 
    ImplementsKeyword = 81, FloatType = 82, IntType = 83, UintType = 84, 
    BooleanLiteral = 85, DecimalFloatLiteral = 86, DecimalIntegerLiteral = 87, 
    DecimalIntegerLiteralBody = 88, AddressLiteral = 89, HashLiteral = 90, 
    HexIntegerLiteral = 91, HexIntegerLiteralBody = 92, DecimalBigIntegerLiteral = 93, 
    HexBigIntegerLiteral = 94, Identifier = 95, StringLiteral = 96, WS = 97, 
    COMMENT = 98, LINE_COMMENT = 99
  };

  enum {
    RulePredaSource = 0, RuleDirective = 1, RuleImportDirective = 2, RuleAnnotation = 3, 
    RuleAnnotationItem = 4, RuleDoxygen = 5, RuleContractDefinition = 6, 
    RuleInterfaceRef = 7, RuleContractPart = 8, RuleStateVariableDeclaration = 9, 
    RuleConstVariableDeclaration = 10, RuleScope = 11, RuleStructDefinition = 12, 
    RuleInterfaceDefinition = 13, RuleEnumDefinition = 14, RuleFunctionDefinition = 15, 
    RuleFunctionDeclaration = 16, RuleFunctionReturnTypeName = 17, RuleFunctionParameterList = 18, 
    RuleFunctionParameter = 19, RuleAccessSpecifier = 20, RuleVariableDeclaration = 21, 
    RuleTypeNameOrAuto = 22, RuleTypeName = 23, RuleFundamentalTypeName = 24, 
    RuleBuiltInContainerTypeName = 25, RuleMapKeyTypeName = 26, RuleMapTypeName = 27, 
    RuleArrayTypeName = 28, RuleUserDefinedTypeName = 29, RuleUserBlockStatement = 30, 
    RuleStatement = 31, RuleExpressionStatement = 32, RuleIfStatement = 33, 
    RuleIfWithBlock = 34, RuleElseWithBlock = 35, RuleElseIfWithBlock = 36, 
    RuleWhileStatement = 37, RuleRelayStatement = 38, RuleRelayType = 39, 
    RuleRelayLambdaDefinition = 40, RuleRelayLambdaParameter = 41, RuleForStatement = 42, 
    RuleDoWhileStatement = 43, RuleContinueStatement = 44, RuleBreakStatement = 45, 
    RuleReturnStatement = 46, RuleVariableDeclarationStatement = 47, RuleLocalVariableDeclaration = 48, 
    RuleExpression = 49, RulePrimaryExpression = 50, RuleFunctionCallArguments = 51, 
    RuleIdentifier = 52
  };

  explicit PredaParser(antlr4::TokenStream *input);
  ~PredaParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class PredaSourceContext;
  class DirectiveContext;
  class ImportDirectiveContext;
  class AnnotationContext;
  class AnnotationItemContext;
  class DoxygenContext;
  class ContractDefinitionContext;
  class InterfaceRefContext;
  class ContractPartContext;
  class StateVariableDeclarationContext;
  class ConstVariableDeclarationContext;
  class ScopeContext;
  class StructDefinitionContext;
  class InterfaceDefinitionContext;
  class EnumDefinitionContext;
  class FunctionDefinitionContext;
  class FunctionDeclarationContext;
  class FunctionReturnTypeNameContext;
  class FunctionParameterListContext;
  class FunctionParameterContext;
  class AccessSpecifierContext;
  class VariableDeclarationContext;
  class TypeNameOrAutoContext;
  class TypeNameContext;
  class FundamentalTypeNameContext;
  class BuiltInContainerTypeNameContext;
  class MapKeyTypeNameContext;
  class MapTypeNameContext;
  class ArrayTypeNameContext;
  class UserDefinedTypeNameContext;
  class UserBlockStatementContext;
  class StatementContext;
  class ExpressionStatementContext;
  class IfStatementContext;
  class IfWithBlockContext;
  class ElseWithBlockContext;
  class ElseIfWithBlockContext;
  class WhileStatementContext;
  class RelayStatementContext;
  class RelayTypeContext;
  class RelayLambdaDefinitionContext;
  class RelayLambdaParameterContext;
  class ForStatementContext;
  class DoWhileStatementContext;
  class ContinueStatementContext;
  class BreakStatementContext;
  class ReturnStatementContext;
  class VariableDeclarationStatementContext;
  class LocalVariableDeclarationContext;
  class ExpressionContext;
  class PrimaryExpressionContext;
  class FunctionCallArgumentsContext;
  class IdentifierContext; 

  class  PredaSourceContext : public antlr4::ParserRuleContext {
  public:
    PredaSourceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ContractDefinitionContext *contractDefinition();
    antlr4::tree::TerminalNode *EOF();
    std::vector<DirectiveContext *> directive();
    DirectiveContext* directive(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PredaSourceContext* predaSource();

  class  DirectiveContext : public antlr4::ParserRuleContext {
  public:
    DirectiveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ImportDirectiveContext *importDirective();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DirectiveContext* directive();

  class  ImportDirectiveContext : public antlr4::ParserRuleContext {
  public:
    PredaParser::IdentifierContext *dAppName = nullptr;
    PredaParser::IdentifierContext *contractName = nullptr;
    PredaParser::IdentifierContext *alias = nullptr;
    ImportDirectiveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ImportKeyword();
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);
    antlr4::tree::TerminalNode *AsKeyword();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ImportDirectiveContext* importDirective();

  class  AnnotationContext : public antlr4::ParserRuleContext {
  public:
    AnnotationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AnnotationItemContext *> annotationItem();
    AnnotationItemContext* annotationItem(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AnnotationContext* annotation();

  class  AnnotationItemContext : public antlr4::ParserRuleContext {
  public:
    AnnotationItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *BooleanLiteral();
    antlr4::tree::TerminalNode *DecimalIntegerLiteral();
    antlr4::tree::TerminalNode *DecimalFloatLiteral();
    antlr4::tree::TerminalNode *HexIntegerLiteral();
    antlr4::tree::TerminalNode *StringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AnnotationItemContext* annotationItem();

  class  DoxygenContext : public antlr4::ParserRuleContext {
  public:
    DoxygenContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> DoxygenSingle();
    antlr4::tree::TerminalNode* DoxygenSingle(size_t i);
    antlr4::tree::TerminalNode *DoxygenMulti();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DoxygenContext* doxygen();

  class  ContractDefinitionContext : public antlr4::ParserRuleContext {
  public:
    ContractDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ContractKeyword();
    IdentifierContext *identifier();
    DoxygenContext *doxygen();
    AnnotationContext *annotation();
    antlr4::tree::TerminalNode *ImplementsKeyword();
    std::vector<InterfaceRefContext *> interfaceRef();
    InterfaceRefContext* interfaceRef(size_t i);
    std::vector<ContractPartContext *> contractPart();
    ContractPartContext* contractPart(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ContractDefinitionContext* contractDefinition();

  class  InterfaceRefContext : public antlr4::ParserRuleContext {
  public:
    PredaParser::IdentifierContext *contractName = nullptr;
    PredaParser::IdentifierContext *interfaceName = nullptr;
    InterfaceRefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  InterfaceRefContext* interfaceRef();

  class  ContractPartContext : public antlr4::ParserRuleContext {
  public:
    ContractPartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StateVariableDeclarationContext *stateVariableDeclaration();
    ConstVariableDeclarationContext *constVariableDeclaration();
    StructDefinitionContext *structDefinition();
    EnumDefinitionContext *enumDefinition();
    InterfaceDefinitionContext *interfaceDefinition();
    FunctionDefinitionContext *functionDefinition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ContractPartContext* contractPart();

  class  StateVariableDeclarationContext : public antlr4::ParserRuleContext {
  public:
    StateVariableDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeNameContext *typeName();
    IdentifierContext *identifier();
    DoxygenContext *doxygen();
    AnnotationContext *annotation();
    ScopeContext *scope();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StateVariableDeclarationContext* stateVariableDeclaration();

  class  ConstVariableDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ConstVariableDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ConstantKeyword();
    TypeNameContext *typeName();
    IdentifierContext *identifier();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConstVariableDeclarationContext* constVariableDeclaration();

  class  ScopeContext : public antlr4::ParserRuleContext {
  public:
    ScopeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ShardKeyword();
    antlr4::tree::TerminalNode *GlobalKeyword();
    antlr4::tree::TerminalNode *AddressKeyword();
    antlr4::tree::TerminalNode *UintType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ScopeContext* scope();

  class  StructDefinitionContext : public antlr4::ParserRuleContext {
  public:
    StructDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StructKeyword();
    IdentifierContext *identifier();
    DoxygenContext *doxygen();
    AnnotationContext *annotation();
    std::vector<VariableDeclarationContext *> variableDeclaration();
    VariableDeclarationContext* variableDeclaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StructDefinitionContext* structDefinition();

  class  InterfaceDefinitionContext : public antlr4::ParserRuleContext {
  public:
    InterfaceDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *InterfaceKeyword();
    IdentifierContext *identifier();
    std::vector<FunctionDeclarationContext *> functionDeclaration();
    FunctionDeclarationContext* functionDeclaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  InterfaceDefinitionContext* interfaceDefinition();

  class  EnumDefinitionContext : public antlr4::ParserRuleContext {
  public:
    EnumDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EnumKeyword();
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);
    DoxygenContext *doxygen();
    AnnotationContext *annotation();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  EnumDefinitionContext* enumDefinition();

  class  FunctionDefinitionContext : public antlr4::ParserRuleContext {
  public:
    FunctionDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionDeclarationContext *functionDeclaration();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionDefinitionContext* functionDefinition();

  class  FunctionDeclarationContext : public antlr4::ParserRuleContext {
  public:
    FunctionDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FunctionKeyword();
    IdentifierContext *identifier();
    FunctionParameterListContext *functionParameterList();
    DoxygenContext *doxygen();
    AnnotationContext *annotation();
    ScopeContext *scope();
    FunctionReturnTypeNameContext *functionReturnTypeName();
    std::vector<AccessSpecifierContext *> accessSpecifier();
    AccessSpecifierContext* accessSpecifier(size_t i);
    antlr4::tree::TerminalNode *ConstantKeyword();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionDeclarationContext* functionDeclaration();

  class  FunctionReturnTypeNameContext : public antlr4::ParserRuleContext {
  public:
    FunctionReturnTypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeNameContext *typeName();
    antlr4::tree::TerminalNode *ConstantKeyword();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionReturnTypeNameContext* functionReturnTypeName();

  class  FunctionParameterListContext : public antlr4::ParserRuleContext {
  public:
    FunctionParameterListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FunctionParameterContext *> functionParameter();
    FunctionParameterContext* functionParameter(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionParameterListContext* functionParameterList();

  class  FunctionParameterContext : public antlr4::ParserRuleContext {
  public:
    FunctionParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeNameContext *typeName();
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *ConstantKeyword();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionParameterContext* functionParameter();

  class  AccessSpecifierContext : public antlr4::ParserRuleContext {
  public:
    AccessSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PublicKeyword();
    antlr4::tree::TerminalNode *ExportKeyword();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AccessSpecifierContext* accessSpecifier();

  class  VariableDeclarationContext : public antlr4::ParserRuleContext {
  public:
    VariableDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeNameContext *typeName();
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VariableDeclarationContext* variableDeclaration();

  class  TypeNameOrAutoContext : public antlr4::ParserRuleContext {
  public:
    TypeNameOrAutoContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeNameContext *typeName();
    antlr4::tree::TerminalNode *AutoKeyword();
    antlr4::tree::TerminalNode *ConstantKeyword();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TypeNameOrAutoContext* typeNameOrAuto();

  class  TypeNameContext : public antlr4::ParserRuleContext {
  public:
    TypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FundamentalTypeNameContext *fundamentalTypeName();
    BuiltInContainerTypeNameContext *builtInContainerTypeName();
    UserDefinedTypeNameContext *userDefinedTypeName();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TypeNameContext* typeName();

  class  FundamentalTypeNameContext : public antlr4::ParserRuleContext {
  public:
    FundamentalTypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IntType();
    antlr4::tree::TerminalNode *UintType();
    antlr4::tree::TerminalNode *FloatType();
    antlr4::tree::TerminalNode *AddressKeyword();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FundamentalTypeNameContext* fundamentalTypeName();

  class  BuiltInContainerTypeNameContext : public antlr4::ParserRuleContext {
  public:
    BuiltInContainerTypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MapTypeNameContext *mapTypeName();
    ArrayTypeNameContext *arrayTypeName();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BuiltInContainerTypeNameContext* builtInContainerTypeName();

  class  MapKeyTypeNameContext : public antlr4::ParserRuleContext {
  public:
    MapKeyTypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IntType();
    antlr4::tree::TerminalNode *UintType();
    antlr4::tree::TerminalNode *FloatType();
    antlr4::tree::TerminalNode *AddressKeyword();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MapKeyTypeNameContext* mapKeyTypeName();

  class  MapTypeNameContext : public antlr4::ParserRuleContext {
  public:
    MapTypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MapKeyTypeNameContext *mapKeyTypeName();
    TypeNameContext *typeName();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MapTypeNameContext* mapTypeName();

  class  ArrayTypeNameContext : public antlr4::ParserRuleContext {
  public:
    ArrayTypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeNameContext *typeName();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ArrayTypeNameContext* arrayTypeName();

  class  UserDefinedTypeNameContext : public antlr4::ParserRuleContext {
  public:
    UserDefinedTypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  UserDefinedTypeNameContext* userDefinedTypeName();

  class  UserBlockStatementContext : public antlr4::ParserRuleContext {
  public:
    UserBlockStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  UserBlockStatementContext* userBlockStatement();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IfStatementContext *ifStatement();
    WhileStatementContext *whileStatement();
    ForStatementContext *forStatement();
    UserBlockStatementContext *userBlockStatement();
    DoWhileStatementContext *doWhileStatement();
    ContinueStatementContext *continueStatement();
    BreakStatementContext *breakStatement();
    ReturnStatementContext *returnStatement();
    RelayStatementContext *relayStatement();
    VariableDeclarationStatementContext *variableDeclarationStatement();
    ExpressionStatementContext *expressionStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StatementContext* statement();

  class  ExpressionStatementContext : public antlr4::ParserRuleContext {
  public:
    ExpressionStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExpressionStatementContext* expressionStatement();

  class  IfStatementContext : public antlr4::ParserRuleContext {
  public:
    IfStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IfWithBlockContext *ifWithBlock();
    std::vector<ElseIfWithBlockContext *> elseIfWithBlock();
    ElseIfWithBlockContext* elseIfWithBlock(size_t i);
    ElseWithBlockContext *elseWithBlock();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IfStatementContext* ifStatement();

  class  IfWithBlockContext : public antlr4::ParserRuleContext {
  public:
    IfWithBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IfKeyword();
    ExpressionContext *expression();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IfWithBlockContext* ifWithBlock();

  class  ElseWithBlockContext : public antlr4::ParserRuleContext {
  public:
    ElseWithBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ElseKeyword();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElseWithBlockContext* elseWithBlock();

  class  ElseIfWithBlockContext : public antlr4::ParserRuleContext {
  public:
    ElseIfWithBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ElseKeyword();
    antlr4::tree::TerminalNode *IfKeyword();
    ExpressionContext *expression();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElseIfWithBlockContext* elseIfWithBlock();

  class  WhileStatementContext : public antlr4::ParserRuleContext {
  public:
    WhileStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  WhileStatementContext* whileStatement();

  class  RelayStatementContext : public antlr4::ParserRuleContext {
  public:
    RelayStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RelayKeyword();
    RelayTypeContext *relayType();
    RelayLambdaDefinitionContext *relayLambdaDefinition();
    IdentifierContext *identifier();
    FunctionCallArgumentsContext *functionCallArguments();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RelayStatementContext* relayStatement();

  class  RelayTypeContext : public antlr4::ParserRuleContext {
  public:
    RelayTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *ShardsKeyword();
    antlr4::tree::TerminalNode *GlobalKeyword();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RelayTypeContext* relayType();

  class  RelayLambdaDefinitionContext : public antlr4::ParserRuleContext {
  public:
    RelayLambdaDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<RelayLambdaParameterContext *> relayLambdaParameter();
    RelayLambdaParameterContext* relayLambdaParameter(size_t i);
    antlr4::tree::TerminalNode *ConstantKeyword();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RelayLambdaDefinitionContext* relayLambdaDefinition();

  class  RelayLambdaParameterContext : public antlr4::ParserRuleContext {
  public:
    RelayLambdaParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeNameOrAutoContext *typeNameOrAuto();
    IdentifierContext *identifier();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RelayLambdaParameterContext* relayLambdaParameter();

  class  ForStatementContext : public antlr4::ParserRuleContext {
  public:
    PredaParser::ExpressionContext *firstExpression = nullptr;
    PredaParser::ExpressionContext *secondExpression = nullptr;
    PredaParser::ExpressionContext *thirdExpression = nullptr;
    ForStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LocalVariableDeclarationContext *localVariableDeclaration();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ForStatementContext* forStatement();

  class  DoWhileStatementContext : public antlr4::ParserRuleContext {
  public:
    DoWhileStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DoWhileStatementContext* doWhileStatement();

  class  ContinueStatementContext : public antlr4::ParserRuleContext {
  public:
    ContinueStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ContinueKeyword();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ContinueStatementContext* continueStatement();

  class  BreakStatementContext : public antlr4::ParserRuleContext {
  public:
    BreakStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BreakKeyword();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BreakStatementContext* breakStatement();

  class  ReturnStatementContext : public antlr4::ParserRuleContext {
  public:
    ReturnStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ReturnStatementContext* returnStatement();

  class  VariableDeclarationStatementContext : public antlr4::ParserRuleContext {
  public:
    VariableDeclarationStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LocalVariableDeclarationContext *localVariableDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VariableDeclarationStatementContext* variableDeclarationStatement();

  class  LocalVariableDeclarationContext : public antlr4::ParserRuleContext {
  public:
    LocalVariableDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeNameOrAutoContext *typeNameOrAuto();
    IdentifierContext *identifier();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LocalVariableDeclarationContext* localVariableDeclaration();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    int expressionType = -1;
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    PrimaryExpressionContext *primaryExpression();
    FunctionCallArgumentsContext *functionCallArguments();
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExpressionContext* expression();
  ExpressionContext* expression(int precedence);
  class  PrimaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    PrimaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BooleanLiteral();
    antlr4::tree::TerminalNode *DecimalIntegerLiteral();
    antlr4::tree::TerminalNode *DecimalFloatLiteral();
    antlr4::tree::TerminalNode *HexIntegerLiteral();
    antlr4::tree::TerminalNode *DecimalBigIntegerLiteral();
    antlr4::tree::TerminalNode *HexBigIntegerLiteral();
    antlr4::tree::TerminalNode *StringLiteral();
    antlr4::tree::TerminalNode *AddressLiteral();
    antlr4::tree::TerminalNode *HashLiteral();
    IdentifierContext *identifier();
    FundamentalTypeNameContext *fundamentalTypeName();
    BuiltInContainerTypeNameContext *builtInContainerTypeName();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PrimaryExpressionContext* primaryExpression();

  class  FunctionCallArgumentsContext : public antlr4::ParserRuleContext {
  public:
    FunctionCallArgumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionCallArgumentsContext* functionCallArguments();

  class  IdentifierContext : public antlr4::ParserRuleContext {
  public:
    IdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IdentifierContext* identifier();


  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool expressionSempred(ExpressionContext *_localctx, size_t predicateIndex);

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

