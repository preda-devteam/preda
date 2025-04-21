
// Generated from Preda.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "PredaParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by PredaParser.
 */
class  PredaListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterPredaSource(PredaParser::PredaSourceContext *ctx) = 0;
  virtual void exitPredaSource(PredaParser::PredaSourceContext *ctx) = 0;

  virtual void enterDirective(PredaParser::DirectiveContext *ctx) = 0;
  virtual void exitDirective(PredaParser::DirectiveContext *ctx) = 0;

  virtual void enterImportDirective(PredaParser::ImportDirectiveContext *ctx) = 0;
  virtual void exitImportDirective(PredaParser::ImportDirectiveContext *ctx) = 0;

  virtual void enterAnnotation(PredaParser::AnnotationContext *ctx) = 0;
  virtual void exitAnnotation(PredaParser::AnnotationContext *ctx) = 0;

  virtual void enterAnnotationItem(PredaParser::AnnotationItemContext *ctx) = 0;
  virtual void exitAnnotationItem(PredaParser::AnnotationItemContext *ctx) = 0;

  virtual void enterDoxygen(PredaParser::DoxygenContext *ctx) = 0;
  virtual void exitDoxygen(PredaParser::DoxygenContext *ctx) = 0;

  virtual void enterContractDefinition(PredaParser::ContractDefinitionContext *ctx) = 0;
  virtual void exitContractDefinition(PredaParser::ContractDefinitionContext *ctx) = 0;

  virtual void enterInterfaceRef(PredaParser::InterfaceRefContext *ctx) = 0;
  virtual void exitInterfaceRef(PredaParser::InterfaceRefContext *ctx) = 0;

  virtual void enterContractPart(PredaParser::ContractPartContext *ctx) = 0;
  virtual void exitContractPart(PredaParser::ContractPartContext *ctx) = 0;

  virtual void enterStateVariableDeclaration(PredaParser::StateVariableDeclarationContext *ctx) = 0;
  virtual void exitStateVariableDeclaration(PredaParser::StateVariableDeclarationContext *ctx) = 0;

  virtual void enterConstVariableDeclaration(PredaParser::ConstVariableDeclarationContext *ctx) = 0;
  virtual void exitConstVariableDeclaration(PredaParser::ConstVariableDeclarationContext *ctx) = 0;

  virtual void enterScope(PredaParser::ScopeContext *ctx) = 0;
  virtual void exitScope(PredaParser::ScopeContext *ctx) = 0;

  virtual void enterStructDefinition(PredaParser::StructDefinitionContext *ctx) = 0;
  virtual void exitStructDefinition(PredaParser::StructDefinitionContext *ctx) = 0;

  virtual void enterInterfaceDefinition(PredaParser::InterfaceDefinitionContext *ctx) = 0;
  virtual void exitInterfaceDefinition(PredaParser::InterfaceDefinitionContext *ctx) = 0;

  virtual void enterEnumDefinition(PredaParser::EnumDefinitionContext *ctx) = 0;
  virtual void exitEnumDefinition(PredaParser::EnumDefinitionContext *ctx) = 0;

  virtual void enterFunctionDefinition(PredaParser::FunctionDefinitionContext *ctx) = 0;
  virtual void exitFunctionDefinition(PredaParser::FunctionDefinitionContext *ctx) = 0;

  virtual void enterFunctionDeclaration(PredaParser::FunctionDeclarationContext *ctx) = 0;
  virtual void exitFunctionDeclaration(PredaParser::FunctionDeclarationContext *ctx) = 0;

  virtual void enterFunctionReturnTypeName(PredaParser::FunctionReturnTypeNameContext *ctx) = 0;
  virtual void exitFunctionReturnTypeName(PredaParser::FunctionReturnTypeNameContext *ctx) = 0;

  virtual void enterFunctionParameterList(PredaParser::FunctionParameterListContext *ctx) = 0;
  virtual void exitFunctionParameterList(PredaParser::FunctionParameterListContext *ctx) = 0;

  virtual void enterFunctionParameter(PredaParser::FunctionParameterContext *ctx) = 0;
  virtual void exitFunctionParameter(PredaParser::FunctionParameterContext *ctx) = 0;

  virtual void enterAccessSpecifier(PredaParser::AccessSpecifierContext *ctx) = 0;
  virtual void exitAccessSpecifier(PredaParser::AccessSpecifierContext *ctx) = 0;

  virtual void enterVariableDeclaration(PredaParser::VariableDeclarationContext *ctx) = 0;
  virtual void exitVariableDeclaration(PredaParser::VariableDeclarationContext *ctx) = 0;

  virtual void enterTypeNameOrAuto(PredaParser::TypeNameOrAutoContext *ctx) = 0;
  virtual void exitTypeNameOrAuto(PredaParser::TypeNameOrAutoContext *ctx) = 0;

  virtual void enterTypeName(PredaParser::TypeNameContext *ctx) = 0;
  virtual void exitTypeName(PredaParser::TypeNameContext *ctx) = 0;

  virtual void enterFundamentalTypeName(PredaParser::FundamentalTypeNameContext *ctx) = 0;
  virtual void exitFundamentalTypeName(PredaParser::FundamentalTypeNameContext *ctx) = 0;

  virtual void enterBuiltInContainerTypeName(PredaParser::BuiltInContainerTypeNameContext *ctx) = 0;
  virtual void exitBuiltInContainerTypeName(PredaParser::BuiltInContainerTypeNameContext *ctx) = 0;

  virtual void enterMapKeyTypeName(PredaParser::MapKeyTypeNameContext *ctx) = 0;
  virtual void exitMapKeyTypeName(PredaParser::MapKeyTypeNameContext *ctx) = 0;

  virtual void enterMapTypeName(PredaParser::MapTypeNameContext *ctx) = 0;
  virtual void exitMapTypeName(PredaParser::MapTypeNameContext *ctx) = 0;

  virtual void enterScatteredMapTypeName(PredaParser::ScatteredMapTypeNameContext *ctx) = 0;
  virtual void exitScatteredMapTypeName(PredaParser::ScatteredMapTypeNameContext *ctx) = 0;

  virtual void enterArrayTypeName(PredaParser::ArrayTypeNameContext *ctx) = 0;
  virtual void exitArrayTypeName(PredaParser::ArrayTypeNameContext *ctx) = 0;

  virtual void enterScatteredArrayTypeName(PredaParser::ScatteredArrayTypeNameContext *ctx) = 0;
  virtual void exitScatteredArrayTypeName(PredaParser::ScatteredArrayTypeNameContext *ctx) = 0;

  virtual void enterUserDefinedTypeName(PredaParser::UserDefinedTypeNameContext *ctx) = 0;
  virtual void exitUserDefinedTypeName(PredaParser::UserDefinedTypeNameContext *ctx) = 0;

  virtual void enterUserBlockStatement(PredaParser::UserBlockStatementContext *ctx) = 0;
  virtual void exitUserBlockStatement(PredaParser::UserBlockStatementContext *ctx) = 0;

  virtual void enterStatement(PredaParser::StatementContext *ctx) = 0;
  virtual void exitStatement(PredaParser::StatementContext *ctx) = 0;

  virtual void enterExpressionStatement(PredaParser::ExpressionStatementContext *ctx) = 0;
  virtual void exitExpressionStatement(PredaParser::ExpressionStatementContext *ctx) = 0;

  virtual void enterIfStatement(PredaParser::IfStatementContext *ctx) = 0;
  virtual void exitIfStatement(PredaParser::IfStatementContext *ctx) = 0;

  virtual void enterIfWithBlock(PredaParser::IfWithBlockContext *ctx) = 0;
  virtual void exitIfWithBlock(PredaParser::IfWithBlockContext *ctx) = 0;

  virtual void enterElseWithBlock(PredaParser::ElseWithBlockContext *ctx) = 0;
  virtual void exitElseWithBlock(PredaParser::ElseWithBlockContext *ctx) = 0;

  virtual void enterElseIfWithBlock(PredaParser::ElseIfWithBlockContext *ctx) = 0;
  virtual void exitElseIfWithBlock(PredaParser::ElseIfWithBlockContext *ctx) = 0;

  virtual void enterWhileStatement(PredaParser::WhileStatementContext *ctx) = 0;
  virtual void exitWhileStatement(PredaParser::WhileStatementContext *ctx) = 0;

  virtual void enterRelayStatement(PredaParser::RelayStatementContext *ctx) = 0;
  virtual void exitRelayStatement(PredaParser::RelayStatementContext *ctx) = 0;

  virtual void enterRelayType(PredaParser::RelayTypeContext *ctx) = 0;
  virtual void exitRelayType(PredaParser::RelayTypeContext *ctx) = 0;

  virtual void enterRelayLambdaDefinition(PredaParser::RelayLambdaDefinitionContext *ctx) = 0;
  virtual void exitRelayLambdaDefinition(PredaParser::RelayLambdaDefinitionContext *ctx) = 0;

  virtual void enterRelayLambdaParameter(PredaParser::RelayLambdaParameterContext *ctx) = 0;
  virtual void exitRelayLambdaParameter(PredaParser::RelayLambdaParameterContext *ctx) = 0;

  virtual void enterForStatement(PredaParser::ForStatementContext *ctx) = 0;
  virtual void exitForStatement(PredaParser::ForStatementContext *ctx) = 0;

  virtual void enterDoWhileStatement(PredaParser::DoWhileStatementContext *ctx) = 0;
  virtual void exitDoWhileStatement(PredaParser::DoWhileStatementContext *ctx) = 0;

  virtual void enterContinueStatement(PredaParser::ContinueStatementContext *ctx) = 0;
  virtual void exitContinueStatement(PredaParser::ContinueStatementContext *ctx) = 0;

  virtual void enterBreakStatement(PredaParser::BreakStatementContext *ctx) = 0;
  virtual void exitBreakStatement(PredaParser::BreakStatementContext *ctx) = 0;

  virtual void enterReturnStatement(PredaParser::ReturnStatementContext *ctx) = 0;
  virtual void exitReturnStatement(PredaParser::ReturnStatementContext *ctx) = 0;

  virtual void enterVariableDeclarationStatement(PredaParser::VariableDeclarationStatementContext *ctx) = 0;
  virtual void exitVariableDeclarationStatement(PredaParser::VariableDeclarationStatementContext *ctx) = 0;

  virtual void enterLocalVariableDeclaration(PredaParser::LocalVariableDeclarationContext *ctx) = 0;
  virtual void exitLocalVariableDeclaration(PredaParser::LocalVariableDeclarationContext *ctx) = 0;

  virtual void enterExpression(PredaParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(PredaParser::ExpressionContext *ctx) = 0;

  virtual void enterPrimaryExpression(PredaParser::PrimaryExpressionContext *ctx) = 0;
  virtual void exitPrimaryExpression(PredaParser::PrimaryExpressionContext *ctx) = 0;

  virtual void enterFunctionCallArguments(PredaParser::FunctionCallArgumentsContext *ctx) = 0;
  virtual void exitFunctionCallArguments(PredaParser::FunctionCallArgumentsContext *ctx) = 0;

  virtual void enterIdentifier(PredaParser::IdentifierContext *ctx) = 0;
  virtual void exitIdentifier(PredaParser::IdentifierContext *ctx) = 0;


};

