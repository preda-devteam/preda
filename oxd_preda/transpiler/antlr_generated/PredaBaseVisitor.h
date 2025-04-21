
// Generated from Preda.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "PredaVisitor.h"


/**
 * This class provides an empty implementation of PredaVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  PredaBaseVisitor : public PredaVisitor {
public:

  virtual std::any visitPredaSource(PredaParser::PredaSourceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDirective(PredaParser::DirectiveContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportDirective(PredaParser::ImportDirectiveContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnotation(PredaParser::AnnotationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnotationItem(PredaParser::AnnotationItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDoxygen(PredaParser::DoxygenContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContractDefinition(PredaParser::ContractDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInterfaceRef(PredaParser::InterfaceRefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContractPart(PredaParser::ContractPartContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStateVariableDeclaration(PredaParser::StateVariableDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstVariableDeclaration(PredaParser::ConstVariableDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitScope(PredaParser::ScopeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStructDefinition(PredaParser::StructDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInterfaceDefinition(PredaParser::InterfaceDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEnumDefinition(PredaParser::EnumDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionDefinition(PredaParser::FunctionDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionDeclaration(PredaParser::FunctionDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionReturnTypeName(PredaParser::FunctionReturnTypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionParameterList(PredaParser::FunctionParameterListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionParameter(PredaParser::FunctionParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAccessSpecifier(PredaParser::AccessSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableDeclaration(PredaParser::VariableDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeNameOrAuto(PredaParser::TypeNameOrAutoContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeName(PredaParser::TypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFundamentalTypeName(PredaParser::FundamentalTypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBuiltInContainerTypeName(PredaParser::BuiltInContainerTypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMapKeyTypeName(PredaParser::MapKeyTypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMapTypeName(PredaParser::MapTypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitScatteredMapTypeName(PredaParser::ScatteredMapTypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayTypeName(PredaParser::ArrayTypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitScatteredArrayTypeName(PredaParser::ScatteredArrayTypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUserDefinedTypeName(PredaParser::UserDefinedTypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUserBlockStatement(PredaParser::UserBlockStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(PredaParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionStatement(PredaParser::ExpressionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStatement(PredaParser::IfStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfWithBlock(PredaParser::IfWithBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElseWithBlock(PredaParser::ElseWithBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElseIfWithBlock(PredaParser::ElseIfWithBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhileStatement(PredaParser::WhileStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelayStatement(PredaParser::RelayStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelayType(PredaParser::RelayTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelayLambdaDefinition(PredaParser::RelayLambdaDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelayLambdaParameter(PredaParser::RelayLambdaParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForStatement(PredaParser::ForStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDoWhileStatement(PredaParser::DoWhileStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContinueStatement(PredaParser::ContinueStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBreakStatement(PredaParser::BreakStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnStatement(PredaParser::ReturnStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableDeclarationStatement(PredaParser::VariableDeclarationStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLocalVariableDeclaration(PredaParser::LocalVariableDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(PredaParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryExpression(PredaParser::PrimaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionCallArguments(PredaParser::FunctionCallArgumentsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifier(PredaParser::IdentifierContext *ctx) override {
    return visitChildren(ctx);
  }


};

