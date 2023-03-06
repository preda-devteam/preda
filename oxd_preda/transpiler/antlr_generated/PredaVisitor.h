
// Generated from Preda.g4 by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"
#include "PredaParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by PredaParser.
 */
class  PredaVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by PredaParser.
   */
    virtual antlrcpp::Any visitPredaSource(PredaParser::PredaSourceContext *context) = 0;

    virtual antlrcpp::Any visitDirective(PredaParser::DirectiveContext *context) = 0;

    virtual antlrcpp::Any visitImportDirective(PredaParser::ImportDirectiveContext *context) = 0;

    virtual antlrcpp::Any visitAnnotation(PredaParser::AnnotationContext *context) = 0;

    virtual antlrcpp::Any visitAnnotationItem(PredaParser::AnnotationItemContext *context) = 0;

    virtual antlrcpp::Any visitDoxygen(PredaParser::DoxygenContext *context) = 0;

    virtual antlrcpp::Any visitContractDefinition(PredaParser::ContractDefinitionContext *context) = 0;

    virtual antlrcpp::Any visitInterfaceRef(PredaParser::InterfaceRefContext *context) = 0;

    virtual antlrcpp::Any visitContractPart(PredaParser::ContractPartContext *context) = 0;

    virtual antlrcpp::Any visitStateVariableDeclaration(PredaParser::StateVariableDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitScope(PredaParser::ScopeContext *context) = 0;

    virtual antlrcpp::Any visitStructDefinition(PredaParser::StructDefinitionContext *context) = 0;

    virtual antlrcpp::Any visitInterfaceDefinition(PredaParser::InterfaceDefinitionContext *context) = 0;

    virtual antlrcpp::Any visitEnumDefinition(PredaParser::EnumDefinitionContext *context) = 0;

    virtual antlrcpp::Any visitFunctionDefinition(PredaParser::FunctionDefinitionContext *context) = 0;

    virtual antlrcpp::Any visitFunctionDeclaration(PredaParser::FunctionDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitFunctionReturnTypeName(PredaParser::FunctionReturnTypeNameContext *context) = 0;

    virtual antlrcpp::Any visitFunctionParameterList(PredaParser::FunctionParameterListContext *context) = 0;

    virtual antlrcpp::Any visitFunctionParameter(PredaParser::FunctionParameterContext *context) = 0;

    virtual antlrcpp::Any visitAccessSpecifier(PredaParser::AccessSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitVariableDeclaration(PredaParser::VariableDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitTypeNameOrAuto(PredaParser::TypeNameOrAutoContext *context) = 0;

    virtual antlrcpp::Any visitTypeName(PredaParser::TypeNameContext *context) = 0;

    virtual antlrcpp::Any visitFundamentalTypeName(PredaParser::FundamentalTypeNameContext *context) = 0;

    virtual antlrcpp::Any visitBuiltInContainerTypeName(PredaParser::BuiltInContainerTypeNameContext *context) = 0;

    virtual antlrcpp::Any visitMapKeyTypeName(PredaParser::MapKeyTypeNameContext *context) = 0;

    virtual antlrcpp::Any visitMapTypeName(PredaParser::MapTypeNameContext *context) = 0;

    virtual antlrcpp::Any visitArrayTypeName(PredaParser::ArrayTypeNameContext *context) = 0;

    virtual antlrcpp::Any visitUserDefinedTypeName(PredaParser::UserDefinedTypeNameContext *context) = 0;

    virtual antlrcpp::Any visitUserBlockStatement(PredaParser::UserBlockStatementContext *context) = 0;

    virtual antlrcpp::Any visitStatement(PredaParser::StatementContext *context) = 0;

    virtual antlrcpp::Any visitExpressionStatement(PredaParser::ExpressionStatementContext *context) = 0;

    virtual antlrcpp::Any visitIfStatement(PredaParser::IfStatementContext *context) = 0;

    virtual antlrcpp::Any visitIfWithBlock(PredaParser::IfWithBlockContext *context) = 0;

    virtual antlrcpp::Any visitElseWithBlock(PredaParser::ElseWithBlockContext *context) = 0;

    virtual antlrcpp::Any visitElseIfWithBlock(PredaParser::ElseIfWithBlockContext *context) = 0;

    virtual antlrcpp::Any visitWhileStatement(PredaParser::WhileStatementContext *context) = 0;

    virtual antlrcpp::Any visitRelayStatement(PredaParser::RelayStatementContext *context) = 0;

    virtual antlrcpp::Any visitRelayType(PredaParser::RelayTypeContext *context) = 0;

    virtual antlrcpp::Any visitRelayLambdaDefinition(PredaParser::RelayLambdaDefinitionContext *context) = 0;

    virtual antlrcpp::Any visitRelayLambdaParameter(PredaParser::RelayLambdaParameterContext *context) = 0;

    virtual antlrcpp::Any visitForStatement(PredaParser::ForStatementContext *context) = 0;

    virtual antlrcpp::Any visitDoWhileStatement(PredaParser::DoWhileStatementContext *context) = 0;

    virtual antlrcpp::Any visitContinueStatement(PredaParser::ContinueStatementContext *context) = 0;

    virtual antlrcpp::Any visitBreakStatement(PredaParser::BreakStatementContext *context) = 0;

    virtual antlrcpp::Any visitReturnStatement(PredaParser::ReturnStatementContext *context) = 0;

    virtual antlrcpp::Any visitVariableDeclarationStatement(PredaParser::VariableDeclarationStatementContext *context) = 0;

    virtual antlrcpp::Any visitLocalVariableDeclaration(PredaParser::LocalVariableDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitExpression(PredaParser::ExpressionContext *context) = 0;

    virtual antlrcpp::Any visitPrimaryExpression(PredaParser::PrimaryExpressionContext *context) = 0;

    virtual antlrcpp::Any visitFunctionCallArguments(PredaParser::FunctionCallArgumentsContext *context) = 0;

    virtual antlrcpp::Any visitIdentifier(PredaParser::IdentifierContext *context) = 0;


};

