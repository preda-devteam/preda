
// Generated from Preda.g4 by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"
#include "PredaListener.h"


/**
 * This class provides an empty implementation of PredaListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  PredaBaseListener : public PredaListener {
public:

  virtual void enterPredaSource(PredaParser::PredaSourceContext * /*ctx*/) override { }
  virtual void exitPredaSource(PredaParser::PredaSourceContext * /*ctx*/) override { }

  virtual void enterDirective(PredaParser::DirectiveContext * /*ctx*/) override { }
  virtual void exitDirective(PredaParser::DirectiveContext * /*ctx*/) override { }

  virtual void enterImportDirective(PredaParser::ImportDirectiveContext * /*ctx*/) override { }
  virtual void exitImportDirective(PredaParser::ImportDirectiveContext * /*ctx*/) override { }

  virtual void enterAnnotation(PredaParser::AnnotationContext * /*ctx*/) override { }
  virtual void exitAnnotation(PredaParser::AnnotationContext * /*ctx*/) override { }

  virtual void enterAnnotationItem(PredaParser::AnnotationItemContext * /*ctx*/) override { }
  virtual void exitAnnotationItem(PredaParser::AnnotationItemContext * /*ctx*/) override { }

  virtual void enterDoxygen(PredaParser::DoxygenContext * /*ctx*/) override { }
  virtual void exitDoxygen(PredaParser::DoxygenContext * /*ctx*/) override { }

  virtual void enterContractDefinition(PredaParser::ContractDefinitionContext * /*ctx*/) override { }
  virtual void exitContractDefinition(PredaParser::ContractDefinitionContext * /*ctx*/) override { }

  virtual void enterInterfaceRef(PredaParser::InterfaceRefContext * /*ctx*/) override { }
  virtual void exitInterfaceRef(PredaParser::InterfaceRefContext * /*ctx*/) override { }

  virtual void enterContractPart(PredaParser::ContractPartContext * /*ctx*/) override { }
  virtual void exitContractPart(PredaParser::ContractPartContext * /*ctx*/) override { }

  virtual void enterStateVariableDeclaration(PredaParser::StateVariableDeclarationContext * /*ctx*/) override { }
  virtual void exitStateVariableDeclaration(PredaParser::StateVariableDeclarationContext * /*ctx*/) override { }

  virtual void enterConstVariableDeclaration(PredaParser::ConstVariableDeclarationContext * /*ctx*/) override { }
  virtual void exitConstVariableDeclaration(PredaParser::ConstVariableDeclarationContext * /*ctx*/) override { }

  virtual void enterScope(PredaParser::ScopeContext * /*ctx*/) override { }
  virtual void exitScope(PredaParser::ScopeContext * /*ctx*/) override { }

  virtual void enterStructDefinition(PredaParser::StructDefinitionContext * /*ctx*/) override { }
  virtual void exitStructDefinition(PredaParser::StructDefinitionContext * /*ctx*/) override { }

  virtual void enterInterfaceDefinition(PredaParser::InterfaceDefinitionContext * /*ctx*/) override { }
  virtual void exitInterfaceDefinition(PredaParser::InterfaceDefinitionContext * /*ctx*/) override { }

  virtual void enterEnumDefinition(PredaParser::EnumDefinitionContext * /*ctx*/) override { }
  virtual void exitEnumDefinition(PredaParser::EnumDefinitionContext * /*ctx*/) override { }

  virtual void enterFunctionDefinition(PredaParser::FunctionDefinitionContext * /*ctx*/) override { }
  virtual void exitFunctionDefinition(PredaParser::FunctionDefinitionContext * /*ctx*/) override { }

  virtual void enterFunctionDeclaration(PredaParser::FunctionDeclarationContext * /*ctx*/) override { }
  virtual void exitFunctionDeclaration(PredaParser::FunctionDeclarationContext * /*ctx*/) override { }

  virtual void enterFunctionReturnTypeName(PredaParser::FunctionReturnTypeNameContext * /*ctx*/) override { }
  virtual void exitFunctionReturnTypeName(PredaParser::FunctionReturnTypeNameContext * /*ctx*/) override { }

  virtual void enterFunctionParameterList(PredaParser::FunctionParameterListContext * /*ctx*/) override { }
  virtual void exitFunctionParameterList(PredaParser::FunctionParameterListContext * /*ctx*/) override { }

  virtual void enterFunctionParameter(PredaParser::FunctionParameterContext * /*ctx*/) override { }
  virtual void exitFunctionParameter(PredaParser::FunctionParameterContext * /*ctx*/) override { }

  virtual void enterAccessSpecifier(PredaParser::AccessSpecifierContext * /*ctx*/) override { }
  virtual void exitAccessSpecifier(PredaParser::AccessSpecifierContext * /*ctx*/) override { }

  virtual void enterVariableDeclaration(PredaParser::VariableDeclarationContext * /*ctx*/) override { }
  virtual void exitVariableDeclaration(PredaParser::VariableDeclarationContext * /*ctx*/) override { }

  virtual void enterTypeNameOrAuto(PredaParser::TypeNameOrAutoContext * /*ctx*/) override { }
  virtual void exitTypeNameOrAuto(PredaParser::TypeNameOrAutoContext * /*ctx*/) override { }

  virtual void enterTypeName(PredaParser::TypeNameContext * /*ctx*/) override { }
  virtual void exitTypeName(PredaParser::TypeNameContext * /*ctx*/) override { }

  virtual void enterFundamentalTypeName(PredaParser::FundamentalTypeNameContext * /*ctx*/) override { }
  virtual void exitFundamentalTypeName(PredaParser::FundamentalTypeNameContext * /*ctx*/) override { }

  virtual void enterBuiltInContainerTypeName(PredaParser::BuiltInContainerTypeNameContext * /*ctx*/) override { }
  virtual void exitBuiltInContainerTypeName(PredaParser::BuiltInContainerTypeNameContext * /*ctx*/) override { }

  virtual void enterMapKeyTypeName(PredaParser::MapKeyTypeNameContext * /*ctx*/) override { }
  virtual void exitMapKeyTypeName(PredaParser::MapKeyTypeNameContext * /*ctx*/) override { }

  virtual void enterMapTypeName(PredaParser::MapTypeNameContext * /*ctx*/) override { }
  virtual void exitMapTypeName(PredaParser::MapTypeNameContext * /*ctx*/) override { }

  virtual void enterArrayTypeName(PredaParser::ArrayTypeNameContext * /*ctx*/) override { }
  virtual void exitArrayTypeName(PredaParser::ArrayTypeNameContext * /*ctx*/) override { }

  virtual void enterUserDefinedTypeName(PredaParser::UserDefinedTypeNameContext * /*ctx*/) override { }
  virtual void exitUserDefinedTypeName(PredaParser::UserDefinedTypeNameContext * /*ctx*/) override { }

  virtual void enterUserBlockStatement(PredaParser::UserBlockStatementContext * /*ctx*/) override { }
  virtual void exitUserBlockStatement(PredaParser::UserBlockStatementContext * /*ctx*/) override { }

  virtual void enterStatement(PredaParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(PredaParser::StatementContext * /*ctx*/) override { }

  virtual void enterExpressionStatement(PredaParser::ExpressionStatementContext * /*ctx*/) override { }
  virtual void exitExpressionStatement(PredaParser::ExpressionStatementContext * /*ctx*/) override { }

  virtual void enterIfStatement(PredaParser::IfStatementContext * /*ctx*/) override { }
  virtual void exitIfStatement(PredaParser::IfStatementContext * /*ctx*/) override { }

  virtual void enterIfWithBlock(PredaParser::IfWithBlockContext * /*ctx*/) override { }
  virtual void exitIfWithBlock(PredaParser::IfWithBlockContext * /*ctx*/) override { }

  virtual void enterElseWithBlock(PredaParser::ElseWithBlockContext * /*ctx*/) override { }
  virtual void exitElseWithBlock(PredaParser::ElseWithBlockContext * /*ctx*/) override { }

  virtual void enterElseIfWithBlock(PredaParser::ElseIfWithBlockContext * /*ctx*/) override { }
  virtual void exitElseIfWithBlock(PredaParser::ElseIfWithBlockContext * /*ctx*/) override { }

  virtual void enterWhileStatement(PredaParser::WhileStatementContext * /*ctx*/) override { }
  virtual void exitWhileStatement(PredaParser::WhileStatementContext * /*ctx*/) override { }

  virtual void enterRelayStatement(PredaParser::RelayStatementContext * /*ctx*/) override { }
  virtual void exitRelayStatement(PredaParser::RelayStatementContext * /*ctx*/) override { }

  virtual void enterRelayType(PredaParser::RelayTypeContext * /*ctx*/) override { }
  virtual void exitRelayType(PredaParser::RelayTypeContext * /*ctx*/) override { }

  virtual void enterRelayLambdaDefinition(PredaParser::RelayLambdaDefinitionContext * /*ctx*/) override { }
  virtual void exitRelayLambdaDefinition(PredaParser::RelayLambdaDefinitionContext * /*ctx*/) override { }

  virtual void enterRelayLambdaParameter(PredaParser::RelayLambdaParameterContext * /*ctx*/) override { }
  virtual void exitRelayLambdaParameter(PredaParser::RelayLambdaParameterContext * /*ctx*/) override { }

  virtual void enterForStatement(PredaParser::ForStatementContext * /*ctx*/) override { }
  virtual void exitForStatement(PredaParser::ForStatementContext * /*ctx*/) override { }

  virtual void enterDoWhileStatement(PredaParser::DoWhileStatementContext * /*ctx*/) override { }
  virtual void exitDoWhileStatement(PredaParser::DoWhileStatementContext * /*ctx*/) override { }

  virtual void enterContinueStatement(PredaParser::ContinueStatementContext * /*ctx*/) override { }
  virtual void exitContinueStatement(PredaParser::ContinueStatementContext * /*ctx*/) override { }

  virtual void enterBreakStatement(PredaParser::BreakStatementContext * /*ctx*/) override { }
  virtual void exitBreakStatement(PredaParser::BreakStatementContext * /*ctx*/) override { }

  virtual void enterReturnStatement(PredaParser::ReturnStatementContext * /*ctx*/) override { }
  virtual void exitReturnStatement(PredaParser::ReturnStatementContext * /*ctx*/) override { }

  virtual void enterVariableDeclarationStatement(PredaParser::VariableDeclarationStatementContext * /*ctx*/) override { }
  virtual void exitVariableDeclarationStatement(PredaParser::VariableDeclarationStatementContext * /*ctx*/) override { }

  virtual void enterLocalVariableDeclaration(PredaParser::LocalVariableDeclarationContext * /*ctx*/) override { }
  virtual void exitLocalVariableDeclaration(PredaParser::LocalVariableDeclarationContext * /*ctx*/) override { }

  virtual void enterExpression(PredaParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(PredaParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterPrimaryExpression(PredaParser::PrimaryExpressionContext * /*ctx*/) override { }
  virtual void exitPrimaryExpression(PredaParser::PrimaryExpressionContext * /*ctx*/) override { }

  virtual void enterFunctionCallArguments(PredaParser::FunctionCallArgumentsContext * /*ctx*/) override { }
  virtual void exitFunctionCallArguments(PredaParser::FunctionCallArgumentsContext * /*ctx*/) override { }

  virtual void enterIdentifier(PredaParser::IdentifierContext * /*ctx*/) override { }
  virtual void exitIdentifier(PredaParser::IdentifierContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

