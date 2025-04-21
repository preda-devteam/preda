
// Generated from Crystality.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "CrystalityParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by CrystalityParser.
 */
class  CrystalityListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterSourceUnit(CrystalityParser::SourceUnitContext *ctx) = 0;
  virtual void exitSourceUnit(CrystalityParser::SourceUnitContext *ctx) = 0;

  virtual void enterPragmaDirective(CrystalityParser::PragmaDirectiveContext *ctx) = 0;
  virtual void exitPragmaDirective(CrystalityParser::PragmaDirectiveContext *ctx) = 0;

  virtual void enterPragmaName(CrystalityParser::PragmaNameContext *ctx) = 0;
  virtual void exitPragmaName(CrystalityParser::PragmaNameContext *ctx) = 0;

  virtual void enterPragmaValue(CrystalityParser::PragmaValueContext *ctx) = 0;
  virtual void exitPragmaValue(CrystalityParser::PragmaValueContext *ctx) = 0;

  virtual void enterVersion(CrystalityParser::VersionContext *ctx) = 0;
  virtual void exitVersion(CrystalityParser::VersionContext *ctx) = 0;

  virtual void enterVersionOperator(CrystalityParser::VersionOperatorContext *ctx) = 0;
  virtual void exitVersionOperator(CrystalityParser::VersionOperatorContext *ctx) = 0;

  virtual void enterVersionConstraint(CrystalityParser::VersionConstraintContext *ctx) = 0;
  virtual void exitVersionConstraint(CrystalityParser::VersionConstraintContext *ctx) = 0;

  virtual void enterImportDeclaration(CrystalityParser::ImportDeclarationContext *ctx) = 0;
  virtual void exitImportDeclaration(CrystalityParser::ImportDeclarationContext *ctx) = 0;

  virtual void enterImportDirective(CrystalityParser::ImportDirectiveContext *ctx) = 0;
  virtual void exitImportDirective(CrystalityParser::ImportDirectiveContext *ctx) = 0;

  virtual void enterNatSpec(CrystalityParser::NatSpecContext *ctx) = 0;
  virtual void exitNatSpec(CrystalityParser::NatSpecContext *ctx) = 0;

  virtual void enterContractDefinition(CrystalityParser::ContractDefinitionContext *ctx) = 0;
  virtual void exitContractDefinition(CrystalityParser::ContractDefinitionContext *ctx) = 0;

  virtual void enterInheritanceSpecifier(CrystalityParser::InheritanceSpecifierContext *ctx) = 0;
  virtual void exitInheritanceSpecifier(CrystalityParser::InheritanceSpecifierContext *ctx) = 0;

  virtual void enterContractPart(CrystalityParser::ContractPartContext *ctx) = 0;
  virtual void exitContractPart(CrystalityParser::ContractPartContext *ctx) = 0;

  virtual void enterStateVariableDeclaration(CrystalityParser::StateVariableDeclarationContext *ctx) = 0;
  virtual void exitStateVariableDeclaration(CrystalityParser::StateVariableDeclarationContext *ctx) = 0;

  virtual void enterUsingForDeclaration(CrystalityParser::UsingForDeclarationContext *ctx) = 0;
  virtual void exitUsingForDeclaration(CrystalityParser::UsingForDeclarationContext *ctx) = 0;

  virtual void enterStructDefinition(CrystalityParser::StructDefinitionContext *ctx) = 0;
  virtual void exitStructDefinition(CrystalityParser::StructDefinitionContext *ctx) = 0;

  virtual void enterConstructorDefinition(CrystalityParser::ConstructorDefinitionContext *ctx) = 0;
  virtual void exitConstructorDefinition(CrystalityParser::ConstructorDefinitionContext *ctx) = 0;

  virtual void enterModifierDefinition(CrystalityParser::ModifierDefinitionContext *ctx) = 0;
  virtual void exitModifierDefinition(CrystalityParser::ModifierDefinitionContext *ctx) = 0;

  virtual void enterModifierInvocation(CrystalityParser::ModifierInvocationContext *ctx) = 0;
  virtual void exitModifierInvocation(CrystalityParser::ModifierInvocationContext *ctx) = 0;

  virtual void enterFunctionDefinition(CrystalityParser::FunctionDefinitionContext *ctx) = 0;
  virtual void exitFunctionDefinition(CrystalityParser::FunctionDefinitionContext *ctx) = 0;

  virtual void enterFunctionDescriptor(CrystalityParser::FunctionDescriptorContext *ctx) = 0;
  virtual void exitFunctionDescriptor(CrystalityParser::FunctionDescriptorContext *ctx) = 0;

  virtual void enterReturnParameters(CrystalityParser::ReturnParametersContext *ctx) = 0;
  virtual void exitReturnParameters(CrystalityParser::ReturnParametersContext *ctx) = 0;

  virtual void enterModifierList(CrystalityParser::ModifierListContext *ctx) = 0;
  virtual void exitModifierList(CrystalityParser::ModifierListContext *ctx) = 0;

  virtual void enterOverrideSpecifier(CrystalityParser::OverrideSpecifierContext *ctx) = 0;
  virtual void exitOverrideSpecifier(CrystalityParser::OverrideSpecifierContext *ctx) = 0;

  virtual void enterAccessiblity(CrystalityParser::AccessiblityContext *ctx) = 0;
  virtual void exitAccessiblity(CrystalityParser::AccessiblityContext *ctx) = 0;

  virtual void enterEventDefinition(CrystalityParser::EventDefinitionContext *ctx) = 0;
  virtual void exitEventDefinition(CrystalityParser::EventDefinitionContext *ctx) = 0;

  virtual void enterEnumValue(CrystalityParser::EnumValueContext *ctx) = 0;
  virtual void exitEnumValue(CrystalityParser::EnumValueContext *ctx) = 0;

  virtual void enterEnumDefinition(CrystalityParser::EnumDefinitionContext *ctx) = 0;
  virtual void exitEnumDefinition(CrystalityParser::EnumDefinitionContext *ctx) = 0;

  virtual void enterParameterList(CrystalityParser::ParameterListContext *ctx) = 0;
  virtual void exitParameterList(CrystalityParser::ParameterListContext *ctx) = 0;

  virtual void enterParameter(CrystalityParser::ParameterContext *ctx) = 0;
  virtual void exitParameter(CrystalityParser::ParameterContext *ctx) = 0;

  virtual void enterEventParameterList(CrystalityParser::EventParameterListContext *ctx) = 0;
  virtual void exitEventParameterList(CrystalityParser::EventParameterListContext *ctx) = 0;

  virtual void enterEventParameter(CrystalityParser::EventParameterContext *ctx) = 0;
  virtual void exitEventParameter(CrystalityParser::EventParameterContext *ctx) = 0;

  virtual void enterFunctionTypeParameterList(CrystalityParser::FunctionTypeParameterListContext *ctx) = 0;
  virtual void exitFunctionTypeParameterList(CrystalityParser::FunctionTypeParameterListContext *ctx) = 0;

  virtual void enterFunctionTypeParameter(CrystalityParser::FunctionTypeParameterContext *ctx) = 0;
  virtual void exitFunctionTypeParameter(CrystalityParser::FunctionTypeParameterContext *ctx) = 0;

  virtual void enterVariableDeclaration(CrystalityParser::VariableDeclarationContext *ctx) = 0;
  virtual void exitVariableDeclaration(CrystalityParser::VariableDeclarationContext *ctx) = 0;

  virtual void enterTypeName(CrystalityParser::TypeNameContext *ctx) = 0;
  virtual void exitTypeName(CrystalityParser::TypeNameContext *ctx) = 0;

  virtual void enterUserDefinedTypeName(CrystalityParser::UserDefinedTypeNameContext *ctx) = 0;
  virtual void exitUserDefinedTypeName(CrystalityParser::UserDefinedTypeNameContext *ctx) = 0;

  virtual void enterMapping(CrystalityParser::MappingContext *ctx) = 0;
  virtual void exitMapping(CrystalityParser::MappingContext *ctx) = 0;

  virtual void enterFunctionTypeName(CrystalityParser::FunctionTypeNameContext *ctx) = 0;
  virtual void exitFunctionTypeName(CrystalityParser::FunctionTypeNameContext *ctx) = 0;

  virtual void enterStorageLocation(CrystalityParser::StorageLocationContext *ctx) = 0;
  virtual void exitStorageLocation(CrystalityParser::StorageLocationContext *ctx) = 0;

  virtual void enterStateMutability(CrystalityParser::StateMutabilityContext *ctx) = 0;
  virtual void exitStateMutability(CrystalityParser::StateMutabilityContext *ctx) = 0;

  virtual void enterBlock(CrystalityParser::BlockContext *ctx) = 0;
  virtual void exitBlock(CrystalityParser::BlockContext *ctx) = 0;

  virtual void enterStatement(CrystalityParser::StatementContext *ctx) = 0;
  virtual void exitStatement(CrystalityParser::StatementContext *ctx) = 0;

  virtual void enterExpressionStatement(CrystalityParser::ExpressionStatementContext *ctx) = 0;
  virtual void exitExpressionStatement(CrystalityParser::ExpressionStatementContext *ctx) = 0;

  virtual void enterIfStatement(CrystalityParser::IfStatementContext *ctx) = 0;
  virtual void exitIfStatement(CrystalityParser::IfStatementContext *ctx) = 0;

  virtual void enterIfWithBlock(CrystalityParser::IfWithBlockContext *ctx) = 0;
  virtual void exitIfWithBlock(CrystalityParser::IfWithBlockContext *ctx) = 0;

  virtual void enterElseWithBlock(CrystalityParser::ElseWithBlockContext *ctx) = 0;
  virtual void exitElseWithBlock(CrystalityParser::ElseWithBlockContext *ctx) = 0;

  virtual void enterElseIfWithBlock(CrystalityParser::ElseIfWithBlockContext *ctx) = 0;
  virtual void exitElseIfWithBlock(CrystalityParser::ElseIfWithBlockContext *ctx) = 0;

  virtual void enterWhileStatement(CrystalityParser::WhileStatementContext *ctx) = 0;
  virtual void exitWhileStatement(CrystalityParser::WhileStatementContext *ctx) = 0;

  virtual void enterForStatement(CrystalityParser::ForStatementContext *ctx) = 0;
  virtual void exitForStatement(CrystalityParser::ForStatementContext *ctx) = 0;

  virtual void enterInlineAssemblyStatement(CrystalityParser::InlineAssemblyStatementContext *ctx) = 0;
  virtual void exitInlineAssemblyStatement(CrystalityParser::InlineAssemblyStatementContext *ctx) = 0;

  virtual void enterDoWhileStatement(CrystalityParser::DoWhileStatementContext *ctx) = 0;
  virtual void exitDoWhileStatement(CrystalityParser::DoWhileStatementContext *ctx) = 0;

  virtual void enterContinueStatement(CrystalityParser::ContinueStatementContext *ctx) = 0;
  virtual void exitContinueStatement(CrystalityParser::ContinueStatementContext *ctx) = 0;

  virtual void enterBreakStatement(CrystalityParser::BreakStatementContext *ctx) = 0;
  virtual void exitBreakStatement(CrystalityParser::BreakStatementContext *ctx) = 0;

  virtual void enterReturnStatement(CrystalityParser::ReturnStatementContext *ctx) = 0;
  virtual void exitReturnStatement(CrystalityParser::ReturnStatementContext *ctx) = 0;

  virtual void enterThrowStatement(CrystalityParser::ThrowStatementContext *ctx) = 0;
  virtual void exitThrowStatement(CrystalityParser::ThrowStatementContext *ctx) = 0;

  virtual void enterEmitStatement(CrystalityParser::EmitStatementContext *ctx) = 0;
  virtual void exitEmitStatement(CrystalityParser::EmitStatementContext *ctx) = 0;

  virtual void enterRelayStatement(CrystalityParser::RelayStatementContext *ctx) = 0;
  virtual void exitRelayStatement(CrystalityParser::RelayStatementContext *ctx) = 0;

  virtual void enterRelayLambdaDefinition(CrystalityParser::RelayLambdaDefinitionContext *ctx) = 0;
  virtual void exitRelayLambdaDefinition(CrystalityParser::RelayLambdaDefinitionContext *ctx) = 0;

  virtual void enterRelayLambdaParameter(CrystalityParser::RelayLambdaParameterContext *ctx) = 0;
  virtual void exitRelayLambdaParameter(CrystalityParser::RelayLambdaParameterContext *ctx) = 0;

  virtual void enterRelayScope(CrystalityParser::RelayScopeContext *ctx) = 0;
  virtual void exitRelayScope(CrystalityParser::RelayScopeContext *ctx) = 0;

  virtual void enterVariableDeclarationStatement(CrystalityParser::VariableDeclarationStatementContext *ctx) = 0;
  virtual void exitVariableDeclarationStatement(CrystalityParser::VariableDeclarationStatementContext *ctx) = 0;

  virtual void enterLocalVariableDeclaration(CrystalityParser::LocalVariableDeclarationContext *ctx) = 0;
  virtual void exitLocalVariableDeclaration(CrystalityParser::LocalVariableDeclarationContext *ctx) = 0;

  virtual void enterVariableDeclarationList(CrystalityParser::VariableDeclarationListContext *ctx) = 0;
  virtual void exitVariableDeclarationList(CrystalityParser::VariableDeclarationListContext *ctx) = 0;

  virtual void enterMoreVariableDeclaration(CrystalityParser::MoreVariableDeclarationContext *ctx) = 0;
  virtual void exitMoreVariableDeclaration(CrystalityParser::MoreVariableDeclarationContext *ctx) = 0;

  virtual void enterIdentifierList(CrystalityParser::IdentifierListContext *ctx) = 0;
  virtual void exitIdentifierList(CrystalityParser::IdentifierListContext *ctx) = 0;

  virtual void enterMoreIdentifier(CrystalityParser::MoreIdentifierContext *ctx) = 0;
  virtual void exitMoreIdentifier(CrystalityParser::MoreIdentifierContext *ctx) = 0;

  virtual void enterElementaryTypeName(CrystalityParser::ElementaryTypeNameContext *ctx) = 0;
  virtual void exitElementaryTypeName(CrystalityParser::ElementaryTypeNameContext *ctx) = 0;

  virtual void enterExpression(CrystalityParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(CrystalityParser::ExpressionContext *ctx) = 0;

  virtual void enterPostOperator(CrystalityParser::PostOperatorContext *ctx) = 0;
  virtual void exitPostOperator(CrystalityParser::PostOperatorContext *ctx) = 0;

  virtual void enterPreOperator(CrystalityParser::PreOperatorContext *ctx) = 0;
  virtual void exitPreOperator(CrystalityParser::PreOperatorContext *ctx) = 0;

  virtual void enterMidOperator(CrystalityParser::MidOperatorContext *ctx) = 0;
  virtual void exitMidOperator(CrystalityParser::MidOperatorContext *ctx) = 0;

  virtual void enterPrimaryExpression(CrystalityParser::PrimaryExpressionContext *ctx) = 0;
  virtual void exitPrimaryExpression(CrystalityParser::PrimaryExpressionContext *ctx) = 0;

  virtual void enterMatchedParentheses(CrystalityParser::MatchedParenthesesContext *ctx) = 0;
  virtual void exitMatchedParentheses(CrystalityParser::MatchedParenthesesContext *ctx) = 0;

  virtual void enterExpressionList(CrystalityParser::ExpressionListContext *ctx) = 0;
  virtual void exitExpressionList(CrystalityParser::ExpressionListContext *ctx) = 0;

  virtual void enterNameValueList(CrystalityParser::NameValueListContext *ctx) = 0;
  virtual void exitNameValueList(CrystalityParser::NameValueListContext *ctx) = 0;

  virtual void enterNameValue(CrystalityParser::NameValueContext *ctx) = 0;
  virtual void exitNameValue(CrystalityParser::NameValueContext *ctx) = 0;

  virtual void enterFunctionCallArguments(CrystalityParser::FunctionCallArgumentsContext *ctx) = 0;
  virtual void exitFunctionCallArguments(CrystalityParser::FunctionCallArgumentsContext *ctx) = 0;

  virtual void enterFunctionCall(CrystalityParser::FunctionCallContext *ctx) = 0;
  virtual void exitFunctionCall(CrystalityParser::FunctionCallContext *ctx) = 0;

  virtual void enterAssemblyBlock(CrystalityParser::AssemblyBlockContext *ctx) = 0;
  virtual void exitAssemblyBlock(CrystalityParser::AssemblyBlockContext *ctx) = 0;

  virtual void enterAssemblyItem(CrystalityParser::AssemblyItemContext *ctx) = 0;
  virtual void exitAssemblyItem(CrystalityParser::AssemblyItemContext *ctx) = 0;

  virtual void enterAssemblyExpression(CrystalityParser::AssemblyExpressionContext *ctx) = 0;
  virtual void exitAssemblyExpression(CrystalityParser::AssemblyExpressionContext *ctx) = 0;

  virtual void enterAssemblyCall(CrystalityParser::AssemblyCallContext *ctx) = 0;
  virtual void exitAssemblyCall(CrystalityParser::AssemblyCallContext *ctx) = 0;

  virtual void enterAssemblyLocalDefinition(CrystalityParser::AssemblyLocalDefinitionContext *ctx) = 0;
  virtual void exitAssemblyLocalDefinition(CrystalityParser::AssemblyLocalDefinitionContext *ctx) = 0;

  virtual void enterAssemblyAssignment(CrystalityParser::AssemblyAssignmentContext *ctx) = 0;
  virtual void exitAssemblyAssignment(CrystalityParser::AssemblyAssignmentContext *ctx) = 0;

  virtual void enterAssemblyIdentifierOrList(CrystalityParser::AssemblyIdentifierOrListContext *ctx) = 0;
  virtual void exitAssemblyIdentifierOrList(CrystalityParser::AssemblyIdentifierOrListContext *ctx) = 0;

  virtual void enterAssemblyIdentifierList(CrystalityParser::AssemblyIdentifierListContext *ctx) = 0;
  virtual void exitAssemblyIdentifierList(CrystalityParser::AssemblyIdentifierListContext *ctx) = 0;

  virtual void enterAssemblyStackAssignment(CrystalityParser::AssemblyStackAssignmentContext *ctx) = 0;
  virtual void exitAssemblyStackAssignment(CrystalityParser::AssemblyStackAssignmentContext *ctx) = 0;

  virtual void enterLabelDefinition(CrystalityParser::LabelDefinitionContext *ctx) = 0;
  virtual void exitLabelDefinition(CrystalityParser::LabelDefinitionContext *ctx) = 0;

  virtual void enterAssemblySwitch(CrystalityParser::AssemblySwitchContext *ctx) = 0;
  virtual void exitAssemblySwitch(CrystalityParser::AssemblySwitchContext *ctx) = 0;

  virtual void enterAssemblyCase(CrystalityParser::AssemblyCaseContext *ctx) = 0;
  virtual void exitAssemblyCase(CrystalityParser::AssemblyCaseContext *ctx) = 0;

  virtual void enterAssemblyFunctionDefinition(CrystalityParser::AssemblyFunctionDefinitionContext *ctx) = 0;
  virtual void exitAssemblyFunctionDefinition(CrystalityParser::AssemblyFunctionDefinitionContext *ctx) = 0;

  virtual void enterAssemblyFunctionReturns(CrystalityParser::AssemblyFunctionReturnsContext *ctx) = 0;
  virtual void exitAssemblyFunctionReturns(CrystalityParser::AssemblyFunctionReturnsContext *ctx) = 0;

  virtual void enterAssemblyFor(CrystalityParser::AssemblyForContext *ctx) = 0;
  virtual void exitAssemblyFor(CrystalityParser::AssemblyForContext *ctx) = 0;

  virtual void enterAssemblyIf(CrystalityParser::AssemblyIfContext *ctx) = 0;
  virtual void exitAssemblyIf(CrystalityParser::AssemblyIfContext *ctx) = 0;

  virtual void enterAssemblyLiteral(CrystalityParser::AssemblyLiteralContext *ctx) = 0;
  virtual void exitAssemblyLiteral(CrystalityParser::AssemblyLiteralContext *ctx) = 0;

  virtual void enterSubAssembly(CrystalityParser::SubAssemblyContext *ctx) = 0;
  virtual void exitSubAssembly(CrystalityParser::SubAssemblyContext *ctx) = 0;

  virtual void enterTupleExpression(CrystalityParser::TupleExpressionContext *ctx) = 0;
  virtual void exitTupleExpression(CrystalityParser::TupleExpressionContext *ctx) = 0;

  virtual void enterBracketTupleExpression(CrystalityParser::BracketTupleExpressionContext *ctx) = 0;
  virtual void exitBracketTupleExpression(CrystalityParser::BracketTupleExpressionContext *ctx) = 0;

  virtual void enterMoreExpression(CrystalityParser::MoreExpressionContext *ctx) = 0;
  virtual void exitMoreExpression(CrystalityParser::MoreExpressionContext *ctx) = 0;

  virtual void enterParanthesesTupleExpression(CrystalityParser::ParanthesesTupleExpressionContext *ctx) = 0;
  virtual void exitParanthesesTupleExpression(CrystalityParser::ParanthesesTupleExpressionContext *ctx) = 0;

  virtual void enterTypeNameExpression(CrystalityParser::TypeNameExpressionContext *ctx) = 0;
  virtual void exitTypeNameExpression(CrystalityParser::TypeNameExpressionContext *ctx) = 0;

  virtual void enterNumberLiteral(CrystalityParser::NumberLiteralContext *ctx) = 0;
  virtual void exitNumberLiteral(CrystalityParser::NumberLiteralContext *ctx) = 0;

  virtual void enterIdentifier(CrystalityParser::IdentifierContext *ctx) = 0;
  virtual void exitIdentifier(CrystalityParser::IdentifierContext *ctx) = 0;

  virtual void enterScope(CrystalityParser::ScopeContext *ctx) = 0;
  virtual void exitScope(CrystalityParser::ScopeContext *ctx) = 0;

  virtual void enterAccessSpecifier(CrystalityParser::AccessSpecifierContext *ctx) = 0;
  virtual void exitAccessSpecifier(CrystalityParser::AccessSpecifierContext *ctx) = 0;


};

