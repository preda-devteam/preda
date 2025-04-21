
// Generated from Crystality.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"




class  CrystalityParser : public antlr4::Parser {
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
    T__56 = 57, T__57 = 58, T__58 = 59, T__59 = 60, T__60 = 61, T__61 = 62, 
    T__62 = 63, T__63 = 64, T__64 = 65, T__65 = 66, T__66 = 67, T__67 = 68, 
    T__68 = 69, T__69 = 70, T__70 = 71, T__71 = 72, T__72 = 73, T__73 = 74, 
    T__74 = 75, T__75 = 76, T__76 = 77, T__77 = 78, T__78 = 79, T__79 = 80, 
    T__80 = 81, T__81 = 82, T__82 = 83, T__83 = 84, T__84 = 85, T__85 = 86, 
    T__86 = 87, T__87 = 88, T__88 = 89, T__89 = 90, T__90 = 91, T__91 = 92, 
    T__92 = 93, NatSpecSingleLine = 94, NatSpecMultiLine = 95, VersionLiteral = 96, 
    BooleanLiteral = 97, DecimalNumber = 98, HexNumber = 99, Int = 100, 
    Uint = 101, Byte = 102, Fixed = 103, Ufixed = 104, NumberUnit = 105, 
    HexLiteral = 106, ReservedKeyword = 107, AnonymousKeyword = 108, BreakKeyword = 109, 
    ConstantKeyword = 110, ContinueKeyword = 111, ExternalKeyword = 112, 
    IndexedKeyword = 113, InternalKeyword = 114, PayableKeyword = 115, PrivateKeyword = 116, 
    PublicKeyword = 117, PureKeyword = 118, TypeKeyword = 119, ViewKeyword = 120, 
    RelayKeyword = 121, ConstructorKeyword = 122, OverrideKeyword = 123, 
    Identifier = 124, StringLiteral = 125, WS = 126, COMMENT = 127, LINE_COMMENT = 128
  };

  enum {
    RuleSourceUnit = 0, RulePragmaDirective = 1, RulePragmaName = 2, RulePragmaValue = 3, 
    RuleVersion = 4, RuleVersionOperator = 5, RuleVersionConstraint = 6, 
    RuleImportDeclaration = 7, RuleImportDirective = 8, RuleNatSpec = 9, 
    RuleContractDefinition = 10, RuleInheritanceSpecifier = 11, RuleContractPart = 12, 
    RuleStateVariableDeclaration = 13, RuleUsingForDeclaration = 14, RuleStructDefinition = 15, 
    RuleConstructorDefinition = 16, RuleModifierDefinition = 17, RuleModifierInvocation = 18, 
    RuleFunctionDefinition = 19, RuleFunctionDescriptor = 20, RuleReturnParameters = 21, 
    RuleModifierList = 22, RuleOverrideSpecifier = 23, RuleAccessiblity = 24, 
    RuleEventDefinition = 25, RuleEnumValue = 26, RuleEnumDefinition = 27, 
    RuleParameterList = 28, RuleParameter = 29, RuleEventParameterList = 30, 
    RuleEventParameter = 31, RuleFunctionTypeParameterList = 32, RuleFunctionTypeParameter = 33, 
    RuleVariableDeclaration = 34, RuleTypeName = 35, RuleUserDefinedTypeName = 36, 
    RuleMapping = 37, RuleFunctionTypeName = 38, RuleStorageLocation = 39, 
    RuleStateMutability = 40, RuleBlock = 41, RuleStatement = 42, RuleExpressionStatement = 43, 
    RuleIfStatement = 44, RuleIfWithBlock = 45, RuleElseWithBlock = 46, 
    RuleElseIfWithBlock = 47, RuleWhileStatement = 48, RuleForStatement = 49, 
    RuleInlineAssemblyStatement = 50, RuleDoWhileStatement = 51, RuleContinueStatement = 52, 
    RuleBreakStatement = 53, RuleReturnStatement = 54, RuleThrowStatement = 55, 
    RuleEmitStatement = 56, RuleRelayStatement = 57, RuleRelayLambdaDefinition = 58, 
    RuleRelayLambdaParameter = 59, RuleRelayScope = 60, RuleVariableDeclarationStatement = 61, 
    RuleLocalVariableDeclaration = 62, RuleVariableDeclarationList = 63, 
    RuleMoreVariableDeclaration = 64, RuleIdentifierList = 65, RuleMoreIdentifier = 66, 
    RuleElementaryTypeName = 67, RuleExpression = 68, RulePostOperator = 69, 
    RulePreOperator = 70, RuleMidOperator = 71, RulePrimaryExpression = 72, 
    RuleMatchedParentheses = 73, RuleExpressionList = 74, RuleNameValueList = 75, 
    RuleNameValue = 76, RuleFunctionCallArguments = 77, RuleFunctionCall = 78, 
    RuleAssemblyBlock = 79, RuleAssemblyItem = 80, RuleAssemblyExpression = 81, 
    RuleAssemblyCall = 82, RuleAssemblyLocalDefinition = 83, RuleAssemblyAssignment = 84, 
    RuleAssemblyIdentifierOrList = 85, RuleAssemblyIdentifierList = 86, 
    RuleAssemblyStackAssignment = 87, RuleLabelDefinition = 88, RuleAssemblySwitch = 89, 
    RuleAssemblyCase = 90, RuleAssemblyFunctionDefinition = 91, RuleAssemblyFunctionReturns = 92, 
    RuleAssemblyFor = 93, RuleAssemblyIf = 94, RuleAssemblyLiteral = 95, 
    RuleSubAssembly = 96, RuleTupleExpression = 97, RuleBracketTupleExpression = 98, 
    RuleMoreExpression = 99, RuleParanthesesTupleExpression = 100, RuleTypeNameExpression = 101, 
    RuleNumberLiteral = 102, RuleIdentifier = 103, RuleScope = 104, RuleAccessSpecifier = 105
  };

  explicit CrystalityParser(antlr4::TokenStream *input);

  CrystalityParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~CrystalityParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class SourceUnitContext;
  class PragmaDirectiveContext;
  class PragmaNameContext;
  class PragmaValueContext;
  class VersionContext;
  class VersionOperatorContext;
  class VersionConstraintContext;
  class ImportDeclarationContext;
  class ImportDirectiveContext;
  class NatSpecContext;
  class ContractDefinitionContext;
  class InheritanceSpecifierContext;
  class ContractPartContext;
  class StateVariableDeclarationContext;
  class UsingForDeclarationContext;
  class StructDefinitionContext;
  class ConstructorDefinitionContext;
  class ModifierDefinitionContext;
  class ModifierInvocationContext;
  class FunctionDefinitionContext;
  class FunctionDescriptorContext;
  class ReturnParametersContext;
  class ModifierListContext;
  class OverrideSpecifierContext;
  class AccessiblityContext;
  class EventDefinitionContext;
  class EnumValueContext;
  class EnumDefinitionContext;
  class ParameterListContext;
  class ParameterContext;
  class EventParameterListContext;
  class EventParameterContext;
  class FunctionTypeParameterListContext;
  class FunctionTypeParameterContext;
  class VariableDeclarationContext;
  class TypeNameContext;
  class UserDefinedTypeNameContext;
  class MappingContext;
  class FunctionTypeNameContext;
  class StorageLocationContext;
  class StateMutabilityContext;
  class BlockContext;
  class StatementContext;
  class ExpressionStatementContext;
  class IfStatementContext;
  class IfWithBlockContext;
  class ElseWithBlockContext;
  class ElseIfWithBlockContext;
  class WhileStatementContext;
  class ForStatementContext;
  class InlineAssemblyStatementContext;
  class DoWhileStatementContext;
  class ContinueStatementContext;
  class BreakStatementContext;
  class ReturnStatementContext;
  class ThrowStatementContext;
  class EmitStatementContext;
  class RelayStatementContext;
  class RelayLambdaDefinitionContext;
  class RelayLambdaParameterContext;
  class RelayScopeContext;
  class VariableDeclarationStatementContext;
  class LocalVariableDeclarationContext;
  class VariableDeclarationListContext;
  class MoreVariableDeclarationContext;
  class IdentifierListContext;
  class MoreIdentifierContext;
  class ElementaryTypeNameContext;
  class ExpressionContext;
  class PostOperatorContext;
  class PreOperatorContext;
  class MidOperatorContext;
  class PrimaryExpressionContext;
  class MatchedParenthesesContext;
  class ExpressionListContext;
  class NameValueListContext;
  class NameValueContext;
  class FunctionCallArgumentsContext;
  class FunctionCallContext;
  class AssemblyBlockContext;
  class AssemblyItemContext;
  class AssemblyExpressionContext;
  class AssemblyCallContext;
  class AssemblyLocalDefinitionContext;
  class AssemblyAssignmentContext;
  class AssemblyIdentifierOrListContext;
  class AssemblyIdentifierListContext;
  class AssemblyStackAssignmentContext;
  class LabelDefinitionContext;
  class AssemblySwitchContext;
  class AssemblyCaseContext;
  class AssemblyFunctionDefinitionContext;
  class AssemblyFunctionReturnsContext;
  class AssemblyForContext;
  class AssemblyIfContext;
  class AssemblyLiteralContext;
  class SubAssemblyContext;
  class TupleExpressionContext;
  class BracketTupleExpressionContext;
  class MoreExpressionContext;
  class ParanthesesTupleExpressionContext;
  class TypeNameExpressionContext;
  class NumberLiteralContext;
  class IdentifierContext;
  class ScopeContext;
  class AccessSpecifierContext; 

  class  SourceUnitContext : public antlr4::ParserRuleContext {
  public:
    SourceUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<PragmaDirectiveContext *> pragmaDirective();
    PragmaDirectiveContext* pragmaDirective(size_t i);
    std::vector<ImportDirectiveContext *> importDirective();
    ImportDirectiveContext* importDirective(size_t i);
    std::vector<ContractDefinitionContext *> contractDefinition();
    ContractDefinitionContext* contractDefinition(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SourceUnitContext* sourceUnit();

  class  PragmaDirectiveContext : public antlr4::ParserRuleContext {
  public:
    PragmaDirectiveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PragmaNameContext *pragmaName();
    PragmaValueContext *pragmaValue();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PragmaDirectiveContext* pragmaDirective();

  class  PragmaNameContext : public antlr4::ParserRuleContext {
  public:
    PragmaNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PragmaNameContext* pragmaName();

  class  PragmaValueContext : public antlr4::ParserRuleContext {
  public:
    PragmaValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VersionContext *version();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PragmaValueContext* pragmaValue();

  class  VersionContext : public antlr4::ParserRuleContext {
  public:
    VersionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<VersionConstraintContext *> versionConstraint();
    VersionConstraintContext* versionConstraint(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VersionContext* version();

  class  VersionOperatorContext : public antlr4::ParserRuleContext {
  public:
    VersionOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VersionOperatorContext* versionOperator();

  class  VersionConstraintContext : public antlr4::ParserRuleContext {
  public:
    VersionConstraintContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VersionLiteral();
    VersionOperatorContext *versionOperator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VersionConstraintContext* versionConstraint();

  class  ImportDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ImportDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ImportDeclarationContext* importDeclaration();

  class  ImportDirectiveContext : public antlr4::ParserRuleContext {
  public:
    ImportDirectiveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StringLiteral();
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);
    std::vector<ImportDeclarationContext *> importDeclaration();
    ImportDeclarationContext* importDeclaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ImportDirectiveContext* importDirective();

  class  NatSpecContext : public antlr4::ParserRuleContext {
  public:
    NatSpecContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NatSpecSingleLine();
    antlr4::tree::TerminalNode *NatSpecMultiLine();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NatSpecContext* natSpec();

  class  ContractDefinitionContext : public antlr4::ParserRuleContext {
  public:
    ContractDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    NatSpecContext *natSpec();
    std::vector<InheritanceSpecifierContext *> inheritanceSpecifier();
    InheritanceSpecifierContext* inheritanceSpecifier(size_t i);
    std::vector<ContractPartContext *> contractPart();
    ContractPartContext* contractPart(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ContractDefinitionContext* contractDefinition();

  class  InheritanceSpecifierContext : public antlr4::ParserRuleContext {
  public:
    InheritanceSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UserDefinedTypeNameContext *userDefinedTypeName();
    ExpressionListContext *expressionList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  InheritanceSpecifierContext* inheritanceSpecifier();

  class  ContractPartContext : public antlr4::ParserRuleContext {
  public:
    ContractPartContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StateVariableDeclarationContext *stateVariableDeclaration();
    UsingForDeclarationContext *usingForDeclaration();
    StructDefinitionContext *structDefinition();
    ConstructorDefinitionContext *constructorDefinition();
    ModifierDefinitionContext *modifierDefinition();
    FunctionDefinitionContext *functionDefinition();
    EventDefinitionContext *eventDefinition();
    EnumDefinitionContext *enumDefinition();

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
    ScopeContext *scope();
    std::vector<AccessSpecifierContext *> accessSpecifier();
    AccessSpecifierContext* accessSpecifier(size_t i);
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StateVariableDeclarationContext* stateVariableDeclaration();

  class  UsingForDeclarationContext : public antlr4::ParserRuleContext {
  public:
    UsingForDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    TypeNameContext *typeName();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  UsingForDeclarationContext* usingForDeclaration();

  class  StructDefinitionContext : public antlr4::ParserRuleContext {
  public:
    StructDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    std::vector<VariableDeclarationContext *> variableDeclaration();
    VariableDeclarationContext* variableDeclaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StructDefinitionContext* structDefinition();

  class  ConstructorDefinitionContext : public antlr4::ParserRuleContext {
  public:
    ConstructorDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ConstructorKeyword();
    ParameterListContext *parameterList();
    ModifierListContext *modifierList();
    BlockContext *block();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConstructorDefinitionContext* constructorDefinition();

  class  ModifierDefinitionContext : public antlr4::ParserRuleContext {
  public:
    ModifierDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    BlockContext *block();
    ParameterListContext *parameterList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ModifierDefinitionContext* modifierDefinition();

  class  ModifierInvocationContext : public antlr4::ParserRuleContext {
  public:
    ModifierInvocationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    ExpressionListContext *expressionList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ModifierInvocationContext* modifierInvocation();

  class  FunctionDefinitionContext : public antlr4::ParserRuleContext {
  public:
    FunctionDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionDescriptorContext *functionDescriptor();
    ParameterListContext *parameterList();
    ModifierListContext *modifierList();
    BlockContext *block();
    NatSpecContext *natSpec();
    ScopeContext *scope();
    ReturnParametersContext *returnParameters();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionDefinitionContext* functionDefinition();

  class  FunctionDescriptorContext : public antlr4::ParserRuleContext {
  public:
    FunctionDescriptorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    antlr4::tree::TerminalNode *ConstructorKeyword();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionDescriptorContext* functionDescriptor();

  class  ReturnParametersContext : public antlr4::ParserRuleContext {
  public:
    ReturnParametersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ParameterListContext *parameterList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ReturnParametersContext* returnParameters();

  class  ModifierListContext : public antlr4::ParserRuleContext {
  public:
    ModifierListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ModifierInvocationContext *> modifierInvocation();
    ModifierInvocationContext* modifierInvocation(size_t i);
    std::vector<StateMutabilityContext *> stateMutability();
    StateMutabilityContext* stateMutability(size_t i);
    std::vector<AccessiblityContext *> accessiblity();
    AccessiblityContext* accessiblity(size_t i);
    std::vector<OverrideSpecifierContext *> overrideSpecifier();
    OverrideSpecifierContext* overrideSpecifier(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ModifierListContext* modifierList();

  class  OverrideSpecifierContext : public antlr4::ParserRuleContext {
  public:
    OverrideSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OverrideKeyword();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  OverrideSpecifierContext* overrideSpecifier();

  class  AccessiblityContext : public antlr4::ParserRuleContext {
  public:
    AccessiblityContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ExternalKeyword();
    antlr4::tree::TerminalNode *PublicKeyword();
    antlr4::tree::TerminalNode *InternalKeyword();
    antlr4::tree::TerminalNode *PrivateKeyword();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AccessiblityContext* accessiblity();

  class  EventDefinitionContext : public antlr4::ParserRuleContext {
  public:
    EventDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    EventParameterListContext *eventParameterList();
    NatSpecContext *natSpec();
    antlr4::tree::TerminalNode *AnonymousKeyword();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  EventDefinitionContext* eventDefinition();

  class  EnumValueContext : public antlr4::ParserRuleContext {
  public:
    EnumValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  EnumValueContext* enumValue();

  class  EnumDefinitionContext : public antlr4::ParserRuleContext {
  public:
    EnumDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    std::vector<EnumValueContext *> enumValue();
    EnumValueContext* enumValue(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  EnumDefinitionContext* enumDefinition();

  class  ParameterListContext : public antlr4::ParserRuleContext {
  public:
    ParameterListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ParameterContext *> parameter();
    ParameterContext* parameter(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ParameterListContext* parameterList();

  class  ParameterContext : public antlr4::ParserRuleContext {
  public:
    ParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeNameContext *typeName();
    StorageLocationContext *storageLocation();
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ParameterContext* parameter();

  class  EventParameterListContext : public antlr4::ParserRuleContext {
  public:
    EventParameterListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<EventParameterContext *> eventParameter();
    EventParameterContext* eventParameter(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  EventParameterListContext* eventParameterList();

  class  EventParameterContext : public antlr4::ParserRuleContext {
  public:
    EventParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeNameContext *typeName();
    antlr4::tree::TerminalNode *IndexedKeyword();
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  EventParameterContext* eventParameter();

  class  FunctionTypeParameterListContext : public antlr4::ParserRuleContext {
  public:
    FunctionTypeParameterListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FunctionTypeParameterContext *> functionTypeParameter();
    FunctionTypeParameterContext* functionTypeParameter(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionTypeParameterListContext* functionTypeParameterList();

  class  FunctionTypeParameterContext : public antlr4::ParserRuleContext {
  public:
    FunctionTypeParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeNameContext *typeName();
    StorageLocationContext *storageLocation();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionTypeParameterContext* functionTypeParameter();

  class  VariableDeclarationContext : public antlr4::ParserRuleContext {
  public:
    VariableDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeNameContext *typeName();
    IdentifierContext *identifier();
    StorageLocationContext *storageLocation();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VariableDeclarationContext* variableDeclaration();

  class  TypeNameContext : public antlr4::ParserRuleContext {
  public:
    TypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ElementaryTypeNameContext *elementaryTypeName();
    UserDefinedTypeNameContext *userDefinedTypeName();
    MappingContext *mapping();
    FunctionTypeNameContext *functionTypeName();
    antlr4::tree::TerminalNode *PayableKeyword();
    TypeNameContext *typeName();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TypeNameContext* typeName();
  TypeNameContext* typeName(int precedence);
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

  class  MappingContext : public antlr4::ParserRuleContext {
  public:
    MappingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ElementaryTypeNameContext *elementaryTypeName();
    TypeNameContext *typeName();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MappingContext* mapping();

  class  FunctionTypeNameContext : public antlr4::ParserRuleContext {
  public:
    FunctionTypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FunctionTypeParameterListContext *> functionTypeParameterList();
    FunctionTypeParameterListContext* functionTypeParameterList(size_t i);
    std::vector<antlr4::tree::TerminalNode *> InternalKeyword();
    antlr4::tree::TerminalNode* InternalKeyword(size_t i);
    std::vector<antlr4::tree::TerminalNode *> ExternalKeyword();
    antlr4::tree::TerminalNode* ExternalKeyword(size_t i);
    std::vector<StateMutabilityContext *> stateMutability();
    StateMutabilityContext* stateMutability(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionTypeNameContext* functionTypeName();

  class  StorageLocationContext : public antlr4::ParserRuleContext {
  public:
    StorageLocationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StorageLocationContext* storageLocation();

  class  StateMutabilityContext : public antlr4::ParserRuleContext {
  public:
    StateMutabilityContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PureKeyword();
    antlr4::tree::TerminalNode *ConstantKeyword();
    antlr4::tree::TerminalNode *ViewKeyword();
    antlr4::tree::TerminalNode *PayableKeyword();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StateMutabilityContext* stateMutability();

  class  BlockContext : public antlr4::ParserRuleContext {
  public:
    BlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BlockContext* block();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IfStatementContext *ifStatement();
    WhileStatementContext *whileStatement();
    ForStatementContext *forStatement();
    InlineAssemblyStatementContext *inlineAssemblyStatement();
    DoWhileStatementContext *doWhileStatement();
    ContinueStatementContext *continueStatement();
    BreakStatementContext *breakStatement();
    ReturnStatementContext *returnStatement();
    ThrowStatementContext *throwStatement();
    EmitStatementContext *emitStatement();
    RelayStatementContext *relayStatement();
    VariableDeclarationStatementContext *variableDeclarationStatement();
    ExpressionStatementContext *expressionStatement();
    BlockContext *block();

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
    ExpressionContext *expression();
    BlockContext *block();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IfWithBlockContext* ifWithBlock();

  class  ElseWithBlockContext : public antlr4::ParserRuleContext {
  public:
    ElseWithBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BlockContext *block();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElseWithBlockContext* elseWithBlock();

  class  ElseIfWithBlockContext : public antlr4::ParserRuleContext {
  public:
    ElseIfWithBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    BlockContext *block();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElseIfWithBlockContext* elseIfWithBlock();

  class  WhileStatementContext : public antlr4::ParserRuleContext {
  public:
    WhileStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    StatementContext *statement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  WhileStatementContext* whileStatement();

  class  ForStatementContext : public antlr4::ParserRuleContext {
  public:
    CrystalityParser::ExpressionContext *firstExpression = nullptr;
    CrystalityParser::ExpressionContext *secondExpression = nullptr;
    CrystalityParser::ExpressionContext *thirdExpression = nullptr;
    ForStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BlockContext *block();
    LocalVariableDeclarationContext *localVariableDeclaration();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ForStatementContext* forStatement();

  class  InlineAssemblyStatementContext : public antlr4::ParserRuleContext {
  public:
    InlineAssemblyStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssemblyBlockContext *assemblyBlock();
    antlr4::tree::TerminalNode *StringLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  InlineAssemblyStatementContext* inlineAssemblyStatement();

  class  DoWhileStatementContext : public antlr4::ParserRuleContext {
  public:
    DoWhileStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementContext *statement();
    ExpressionContext *expression();

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

  class  ThrowStatementContext : public antlr4::ParserRuleContext {
  public:
    ThrowStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ThrowStatementContext* throwStatement();

  class  EmitStatementContext : public antlr4::ParserRuleContext {
  public:
    EmitStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionCallContext *functionCall();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  EmitStatementContext* emitStatement();

  class  RelayStatementContext : public antlr4::ParserRuleContext {
  public:
    RelayStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RelayKeyword();
    RelayScopeContext *relayScope();
    RelayLambdaDefinitionContext *relayLambdaDefinition();
    IdentifierContext *identifier();
    FunctionCallArgumentsContext *functionCallArguments();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RelayStatementContext* relayStatement();

  class  RelayLambdaDefinitionContext : public antlr4::ParserRuleContext {
  public:
    RelayLambdaDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BlockContext *block();
    std::vector<RelayLambdaParameterContext *> relayLambdaParameter();
    RelayLambdaParameterContext* relayLambdaParameter(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RelayLambdaDefinitionContext* relayLambdaDefinition();

  class  RelayLambdaParameterContext : public antlr4::ParserRuleContext {
  public:
    RelayLambdaParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    ExpressionContext *expression();
    TypeNameContext *typeName();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RelayLambdaParameterContext* relayLambdaParameter();

  class  RelayScopeContext : public antlr4::ParserRuleContext {
  public:
    RelayScopeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RelayScopeContext* relayScope();

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
    IdentifierListContext *identifierList();
    VariableDeclarationContext *variableDeclaration();
    VariableDeclarationListContext *variableDeclarationList();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LocalVariableDeclarationContext* localVariableDeclaration();

  class  VariableDeclarationListContext : public antlr4::ParserRuleContext {
  public:
    VariableDeclarationListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VariableDeclarationContext *variableDeclaration();
    std::vector<MoreVariableDeclarationContext *> moreVariableDeclaration();
    MoreVariableDeclarationContext* moreVariableDeclaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VariableDeclarationListContext* variableDeclarationList();

  class  MoreVariableDeclarationContext : public antlr4::ParserRuleContext {
  public:
    MoreVariableDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VariableDeclarationContext *variableDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MoreVariableDeclarationContext* moreVariableDeclaration();

  class  IdentifierListContext : public antlr4::ParserRuleContext {
  public:
    IdentifierListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MoreIdentifierContext *> moreIdentifier();
    MoreIdentifierContext* moreIdentifier(size_t i);
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IdentifierListContext* identifierList();

  class  MoreIdentifierContext : public antlr4::ParserRuleContext {
  public:
    MoreIdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MoreIdentifierContext* moreIdentifier();

  class  ElementaryTypeNameContext : public antlr4::ParserRuleContext {
  public:
    ElementaryTypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Int();
    antlr4::tree::TerminalNode *Uint();
    antlr4::tree::TerminalNode *Byte();
    antlr4::tree::TerminalNode *Fixed();
    antlr4::tree::TerminalNode *Ufixed();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElementaryTypeNameContext* elementaryTypeName();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    int expressionType = -1;
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    PreOperatorContext *preOperator();
    TypeNameContext *typeName();
    PrimaryExpressionContext *primaryExpression();
    MidOperatorContext *midOperator();
    PostOperatorContext *postOperator();
    FunctionCallArgumentsContext *functionCallArguments();
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExpressionContext* expression();
  ExpressionContext* expression(int precedence);
  class  PostOperatorContext : public antlr4::ParserRuleContext {
  public:
    PostOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PostOperatorContext* postOperator();

  class  PreOperatorContext : public antlr4::ParserRuleContext {
  public:
    PreOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PreOperatorContext* preOperator();

  class  MidOperatorContext : public antlr4::ParserRuleContext {
  public:
    MidOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MidOperatorContext* midOperator();

  class  PrimaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    PrimaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BooleanLiteral();
    NumberLiteralContext *numberLiteral();
    antlr4::tree::TerminalNode *HexLiteral();
    antlr4::tree::TerminalNode *StringLiteral();
    IdentifierContext *identifier();
    MatchedParenthesesContext *matchedParentheses();
    antlr4::tree::TerminalNode *TypeKeyword();
    TupleExpressionContext *tupleExpression();
    TypeNameExpressionContext *typeNameExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PrimaryExpressionContext* primaryExpression();

  class  MatchedParenthesesContext : public antlr4::ParserRuleContext {
  public:
    MatchedParenthesesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MatchedParenthesesContext* matchedParentheses();

  class  ExpressionListContext : public antlr4::ParserRuleContext {
  public:
    ExpressionListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExpressionListContext* expressionList();

  class  NameValueListContext : public antlr4::ParserRuleContext {
  public:
    NameValueListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<NameValueContext *> nameValue();
    NameValueContext* nameValue(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NameValueListContext* nameValueList();

  class  NameValueContext : public antlr4::ParserRuleContext {
  public:
    NameValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NameValueContext* nameValue();

  class  FunctionCallArgumentsContext : public antlr4::ParserRuleContext {
  public:
    FunctionCallArgumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NameValueListContext *nameValueList();
    ExpressionListContext *expressionList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionCallArgumentsContext* functionCallArguments();

  class  FunctionCallContext : public antlr4::ParserRuleContext {
  public:
    FunctionCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    FunctionCallArgumentsContext *functionCallArguments();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionCallContext* functionCall();

  class  AssemblyBlockContext : public antlr4::ParserRuleContext {
  public:
    AssemblyBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AssemblyItemContext *> assemblyItem();
    AssemblyItemContext* assemblyItem(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AssemblyBlockContext* assemblyBlock();

  class  AssemblyItemContext : public antlr4::ParserRuleContext {
  public:
    AssemblyItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    AssemblyBlockContext *assemblyBlock();
    AssemblyExpressionContext *assemblyExpression();
    AssemblyLocalDefinitionContext *assemblyLocalDefinition();
    AssemblyAssignmentContext *assemblyAssignment();
    AssemblyStackAssignmentContext *assemblyStackAssignment();
    LabelDefinitionContext *labelDefinition();
    AssemblySwitchContext *assemblySwitch();
    AssemblyFunctionDefinitionContext *assemblyFunctionDefinition();
    AssemblyForContext *assemblyFor();
    AssemblyIfContext *assemblyIf();
    antlr4::tree::TerminalNode *BreakKeyword();
    antlr4::tree::TerminalNode *ContinueKeyword();
    SubAssemblyContext *subAssembly();
    NumberLiteralContext *numberLiteral();
    antlr4::tree::TerminalNode *StringLiteral();
    antlr4::tree::TerminalNode *HexLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AssemblyItemContext* assemblyItem();

  class  AssemblyExpressionContext : public antlr4::ParserRuleContext {
  public:
    AssemblyExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssemblyCallContext *assemblyCall();
    AssemblyLiteralContext *assemblyLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AssemblyExpressionContext* assemblyExpression();

  class  AssemblyCallContext : public antlr4::ParserRuleContext {
  public:
    AssemblyCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    std::vector<AssemblyExpressionContext *> assemblyExpression();
    AssemblyExpressionContext* assemblyExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AssemblyCallContext* assemblyCall();

  class  AssemblyLocalDefinitionContext : public antlr4::ParserRuleContext {
  public:
    AssemblyLocalDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssemblyIdentifierOrListContext *assemblyIdentifierOrList();
    AssemblyExpressionContext *assemblyExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AssemblyLocalDefinitionContext* assemblyLocalDefinition();

  class  AssemblyAssignmentContext : public antlr4::ParserRuleContext {
  public:
    AssemblyAssignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssemblyIdentifierOrListContext *assemblyIdentifierOrList();
    AssemblyExpressionContext *assemblyExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AssemblyAssignmentContext* assemblyAssignment();

  class  AssemblyIdentifierOrListContext : public antlr4::ParserRuleContext {
  public:
    AssemblyIdentifierOrListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    AssemblyIdentifierListContext *assemblyIdentifierList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AssemblyIdentifierOrListContext* assemblyIdentifierOrList();

  class  AssemblyIdentifierListContext : public antlr4::ParserRuleContext {
  public:
    AssemblyIdentifierListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<IdentifierContext *> identifier();
    IdentifierContext* identifier(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AssemblyIdentifierListContext* assemblyIdentifierList();

  class  AssemblyStackAssignmentContext : public antlr4::ParserRuleContext {
  public:
    AssemblyStackAssignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AssemblyStackAssignmentContext* assemblyStackAssignment();

  class  LabelDefinitionContext : public antlr4::ParserRuleContext {
  public:
    LabelDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LabelDefinitionContext* labelDefinition();

  class  AssemblySwitchContext : public antlr4::ParserRuleContext {
  public:
    AssemblySwitchContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssemblyExpressionContext *assemblyExpression();
    std::vector<AssemblyCaseContext *> assemblyCase();
    AssemblyCaseContext* assemblyCase(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AssemblySwitchContext* assemblySwitch();

  class  AssemblyCaseContext : public antlr4::ParserRuleContext {
  public:
    AssemblyCaseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssemblyLiteralContext *assemblyLiteral();
    AssemblyBlockContext *assemblyBlock();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AssemblyCaseContext* assemblyCase();

  class  AssemblyFunctionDefinitionContext : public antlr4::ParserRuleContext {
  public:
    AssemblyFunctionDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    AssemblyBlockContext *assemblyBlock();
    AssemblyIdentifierListContext *assemblyIdentifierList();
    AssemblyFunctionReturnsContext *assemblyFunctionReturns();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AssemblyFunctionDefinitionContext* assemblyFunctionDefinition();

  class  AssemblyFunctionReturnsContext : public antlr4::ParserRuleContext {
  public:
    AssemblyFunctionReturnsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssemblyIdentifierListContext *assemblyIdentifierList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AssemblyFunctionReturnsContext* assemblyFunctionReturns();

  class  AssemblyForContext : public antlr4::ParserRuleContext {
  public:
    AssemblyForContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AssemblyExpressionContext *> assemblyExpression();
    AssemblyExpressionContext* assemblyExpression(size_t i);
    std::vector<AssemblyBlockContext *> assemblyBlock();
    AssemblyBlockContext* assemblyBlock(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AssemblyForContext* assemblyFor();

  class  AssemblyIfContext : public antlr4::ParserRuleContext {
  public:
    AssemblyIfContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssemblyExpressionContext *assemblyExpression();
    AssemblyBlockContext *assemblyBlock();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AssemblyIfContext* assemblyIf();

  class  AssemblyLiteralContext : public antlr4::ParserRuleContext {
  public:
    AssemblyLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *StringLiteral();
    antlr4::tree::TerminalNode *DecimalNumber();
    antlr4::tree::TerminalNode *HexNumber();
    antlr4::tree::TerminalNode *HexLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AssemblyLiteralContext* assemblyLiteral();

  class  SubAssemblyContext : public antlr4::ParserRuleContext {
  public:
    SubAssemblyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierContext *identifier();
    AssemblyBlockContext *assemblyBlock();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SubAssemblyContext* subAssembly();

  class  TupleExpressionContext : public antlr4::ParserRuleContext {
  public:
    TupleExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BracketTupleExpressionContext *bracketTupleExpression();
    ParanthesesTupleExpressionContext *paranthesesTupleExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TupleExpressionContext* tupleExpression();

  class  BracketTupleExpressionContext : public antlr4::ParserRuleContext {
  public:
    BracketTupleExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    std::vector<MoreExpressionContext *> moreExpression();
    MoreExpressionContext* moreExpression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BracketTupleExpressionContext* bracketTupleExpression();

  class  MoreExpressionContext : public antlr4::ParserRuleContext {
  public:
    MoreExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MoreExpressionContext* moreExpression();

  class  ParanthesesTupleExpressionContext : public antlr4::ParserRuleContext {
  public:
    ParanthesesTupleExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ParanthesesTupleExpressionContext* paranthesesTupleExpression();

  class  TypeNameExpressionContext : public antlr4::ParserRuleContext {
  public:
    TypeNameExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ElementaryTypeNameContext *elementaryTypeName();
    UserDefinedTypeNameContext *userDefinedTypeName();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TypeNameExpressionContext* typeNameExpression();

  class  NumberLiteralContext : public antlr4::ParserRuleContext {
  public:
    NumberLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DecimalNumber();
    antlr4::tree::TerminalNode *HexNumber();
    antlr4::tree::TerminalNode *NumberUnit();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NumberLiteralContext* numberLiteral();

  class  IdentifierContext : public antlr4::ParserRuleContext {
  public:
    IdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IdentifierContext* identifier();

  class  ScopeContext : public antlr4::ParserRuleContext {
  public:
    ScopeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Uint();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ScopeContext* scope();

  class  AccessSpecifierContext : public antlr4::ParserRuleContext {
  public:
    AccessSpecifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PublicKeyword();
    antlr4::tree::TerminalNode *InternalKeyword();
    antlr4::tree::TerminalNode *PrivateKeyword();
    antlr4::tree::TerminalNode *ConstantKeyword();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AccessSpecifierContext* accessSpecifier();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool typeNameSempred(TypeNameContext *_localctx, size_t predicateIndex);
  bool expressionSempred(ExpressionContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

