
// Generated from Preda.g4 by ANTLR 4.12.0

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
    T__50 = 51, T__51 = 52, T__52 = 53, T__53 = 54, T__54 = 55, T__55 = 56, 
    T__56 = 57, DoxygenSingle = 58, DoxygenMulti = 59, BreakKeyword = 60, 
    ConstantKeyword = 61, ContinueKeyword = 62, RelayKeyword = 63, SupplyKeyword = 64, 
    IfKeyword = 65, ElseKeyword = 66, ShardKeyword = 67, ShardsKeyword = 68, 
    GlobalKeyword = 69, AddressKeyword = 70, AutoKeyword = 71, MinerKeyword = 72, 
    StructKeyword = 73, EnumKeyword = 74, ContractKeyword = 75, ImportKeyword = 76, 
    FunctionKeyword = 77, PublicKeyword = 78, ExportKeyword = 79, AsKeyword = 80, 
    UsingKeyword = 81, InterfaceKeyword = 82, ImplementsKeyword = 83, DeployKeyword = 84, 
    ConstructorKeyword = 85, NextKeyword = 86, FloatType = 87, IntType = 88, 
    UintType = 89, BooleanLiteral = 90, DecimalFloatLiteral = 91, DecimalIntegerLiteral = 92, 
    DecimalIntegerLiteralBody = 93, AddressLiteral = 94, HashLiteral = 95, 
    HexIntegerLiteral = 96, HexIntegerLiteralBody = 97, DecimalBigIntegerLiteral = 98, 
    HexBigIntegerLiteral = 99, Identifier = 100, StringLiteral = 101, WS = 102, 
    COMMENT = 103, LINE_COMMENT = 104
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
    RuleScatteredMapTypeName = 28, RuleArrayTypeName = 29, RuleScatteredArrayTypeName = 30, 
    RuleUserDefinedTypeName = 31, RuleUserBlockStatement = 32, RuleStatement = 33, 
    RuleExpressionStatement = 34, RuleIfStatement = 35, RuleIfWithBlock = 36, 
    RuleElseWithBlock = 37, RuleElseIfWithBlock = 38, RuleWhileStatement = 39, 
    RuleRelayStatement = 40, RuleRelayType = 41, RuleRelayLambdaDefinition = 42, 
    RuleRelayLambdaParameter = 43, RuleForStatement = 44, RuleDoWhileStatement = 45, 
    RuleContinueStatement = 46, RuleBreakStatement = 47, RuleReturnStatement = 48, 
    RuleVariableDeclarationStatement = 49, RuleLocalVariableDeclaration = 50, 
    RuleExpression = 51, RulePrimaryExpression = 52, RuleFunctionCallArguments = 53, 
    RuleIdentifier = 54
  };

  explicit PredaParser(antlr4::TokenStream *input);

  PredaParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~PredaParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


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
  class ScatteredMapTypeNameContext;
  class ArrayTypeNameContext;
  class ScatteredArrayTypeNameContext;
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PredaSourceContext* predaSource();

  class  DirectiveContext : public antlr4::ParserRuleContext {
  public:
    DirectiveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ImportDirectiveContext *importDirective();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FundamentalTypeNameContext* fundamentalTypeName();

  class  BuiltInContainerTypeNameContext : public antlr4::ParserRuleContext {
  public:
    BuiltInContainerTypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MapTypeNameContext *mapTypeName();
    ArrayTypeNameContext *arrayTypeName();
    ScatteredMapTypeNameContext *scatteredMapTypeName();
    ScatteredArrayTypeNameContext *scatteredArrayTypeName();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BuiltInContainerTypeNameContext* builtInContainerTypeName();

  class  MapKeyTypeNameContext : public antlr4::ParserRuleContext {
  public:
    MapKeyTypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IntType();
    antlr4::tree::TerminalNode *UintType();
    antlr4::tree::TerminalNode *AddressKeyword();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MapTypeNameContext* mapTypeName();

  class  ScatteredMapTypeNameContext : public antlr4::ParserRuleContext {
  public:
    ScatteredMapTypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MapKeyTypeNameContext *mapKeyTypeName();
    TypeNameContext *typeName();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ScatteredMapTypeNameContext* scatteredMapTypeName();

  class  ArrayTypeNameContext : public antlr4::ParserRuleContext {
  public:
    ArrayTypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeNameContext *typeName();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrayTypeNameContext* arrayTypeName();

  class  ScatteredArrayTypeNameContext : public antlr4::ParserRuleContext {
  public:
    ScatteredArrayTypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeNameContext *typeName();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ScatteredArrayTypeNameContext* scatteredArrayTypeName();

  class  UserDefinedTypeNameContext : public antlr4::ParserRuleContext {
  public:
    UserDefinedTypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  ExpressionStatementContext : public antlr4::ParserRuleContext {
  public:
    ExpressionStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RelayStatementContext* relayStatement();

  class  RelayTypeContext : public antlr4::ParserRuleContext {
  public:
    RelayTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *ShardsKeyword();
    antlr4::tree::TerminalNode *GlobalKeyword();
    antlr4::tree::TerminalNode *NextKeyword();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DoWhileStatementContext* doWhileStatement();

  class  ContinueStatementContext : public antlr4::ParserRuleContext {
  public:
    ContinueStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ContinueKeyword();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ContinueStatementContext* continueStatement();

  class  BreakStatementContext : public antlr4::ParserRuleContext {
  public:
    BreakStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BreakKeyword();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BreakStatementContext* breakStatement();

  class  ReturnStatementContext : public antlr4::ParserRuleContext {
  public:
    ReturnStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ReturnStatementContext* returnStatement();

  class  VariableDeclarationStatementContext : public antlr4::ParserRuleContext {
  public:
    VariableDeclarationStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LocalVariableDeclarationContext *localVariableDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LocalVariableDeclarationContext* localVariableDeclaration();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    int expressionType = -1;
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *DeployKeyword();
    FunctionCallArgumentsContext *functionCallArguments();
    PrimaryExpressionContext *primaryExpression();
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
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

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionCallArgumentsContext* functionCallArguments();

  class  IdentifierContext : public antlr4::ParserRuleContext {
  public:
    IdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentifierContext* identifier();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool expressionSempred(ExpressionContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

