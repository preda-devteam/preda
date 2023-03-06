
// Generated from Preda.g4 by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"
#include "PredaVisitor.h"


/**
 * This class provides an empty implementation of PredaVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  PredaBaseVisitor : public PredaVisitor {
public:

  virtual antlrcpp::Any visitPredaSource(PredaParser::PredaSourceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDirective(PredaParser::DirectiveContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitImportDirective(PredaParser::ImportDirectiveContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAnnotation(PredaParser::AnnotationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAnnotationItem(PredaParser::AnnotationItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDoxygen(PredaParser::DoxygenContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitContractDefinition(PredaParser::ContractDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInterfaceRef(PredaParser::InterfaceRefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitContractPart(PredaParser::ContractPartContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStateVariableDeclaration(PredaParser::StateVariableDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitScope(PredaParser::ScopeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStructDefinition(PredaParser::StructDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInterfaceDefinition(PredaParser::InterfaceDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEnumDefinition(PredaParser::EnumDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionDefinition(PredaParser::FunctionDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionDeclaration(PredaParser::FunctionDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionReturnTypeName(PredaParser::FunctionReturnTypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionParameterList(PredaParser::FunctionParameterListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionParameter(PredaParser::FunctionParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAccessSpecifier(PredaParser::AccessSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVariableDeclaration(PredaParser::VariableDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTypeNameOrAuto(PredaParser::TypeNameOrAutoContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTypeName(PredaParser::TypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFundamentalTypeName(PredaParser::FundamentalTypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBuiltInContainerTypeName(PredaParser::BuiltInContainerTypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMapKeyTypeName(PredaParser::MapKeyTypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMapTypeName(PredaParser::MapTypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitArrayTypeName(PredaParser::ArrayTypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUserDefinedTypeName(PredaParser::UserDefinedTypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUserBlockStatement(PredaParser::UserBlockStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatement(PredaParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpressionStatement(PredaParser::ExpressionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIfStatement(PredaParser::IfStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIfWithBlock(PredaParser::IfWithBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitElseWithBlock(PredaParser::ElseWithBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitElseIfWithBlock(PredaParser::ElseIfWithBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWhileStatement(PredaParser::WhileStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRelayStatement(PredaParser::RelayStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRelayType(PredaParser::RelayTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRelayLambdaDefinition(PredaParser::RelayLambdaDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRelayLambdaParameter(PredaParser::RelayLambdaParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitForStatement(PredaParser::ForStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDoWhileStatement(PredaParser::DoWhileStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitContinueStatement(PredaParser::ContinueStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBreakStatement(PredaParser::BreakStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitReturnStatement(PredaParser::ReturnStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVariableDeclarationStatement(PredaParser::VariableDeclarationStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLocalVariableDeclaration(PredaParser::LocalVariableDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpression(PredaParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrimaryExpression(PredaParser::PrimaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionCallArguments(PredaParser::FunctionCallArgumentsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIdentifier(PredaParser::IdentifierContext *ctx) override {
    return visitChildren(ctx);
  }


};

