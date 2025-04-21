
// Generated from Preda.g4 by ANTLR 4.12.0

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
    virtual std::any visitPredaSource(PredaParser::PredaSourceContext *context) = 0;

    virtual std::any visitDirective(PredaParser::DirectiveContext *context) = 0;

    virtual std::any visitImportDirective(PredaParser::ImportDirectiveContext *context) = 0;

    virtual std::any visitAnnotation(PredaParser::AnnotationContext *context) = 0;

    virtual std::any visitAnnotationItem(PredaParser::AnnotationItemContext *context) = 0;

    virtual std::any visitDoxygen(PredaParser::DoxygenContext *context) = 0;

    virtual std::any visitContractDefinition(PredaParser::ContractDefinitionContext *context) = 0;

    virtual std::any visitInterfaceRef(PredaParser::InterfaceRefContext *context) = 0;

    virtual std::any visitContractPart(PredaParser::ContractPartContext *context) = 0;

    virtual std::any visitStateVariableDeclaration(PredaParser::StateVariableDeclarationContext *context) = 0;

    virtual std::any visitConstVariableDeclaration(PredaParser::ConstVariableDeclarationContext *context) = 0;

    virtual std::any visitScope(PredaParser::ScopeContext *context) = 0;

    virtual std::any visitStructDefinition(PredaParser::StructDefinitionContext *context) = 0;

    virtual std::any visitInterfaceDefinition(PredaParser::InterfaceDefinitionContext *context) = 0;

    virtual std::any visitEnumDefinition(PredaParser::EnumDefinitionContext *context) = 0;

    virtual std::any visitFunctionDefinition(PredaParser::FunctionDefinitionContext *context) = 0;

    virtual std::any visitFunctionDeclaration(PredaParser::FunctionDeclarationContext *context) = 0;

    virtual std::any visitFunctionReturnTypeName(PredaParser::FunctionReturnTypeNameContext *context) = 0;

    virtual std::any visitFunctionParameterList(PredaParser::FunctionParameterListContext *context) = 0;

    virtual std::any visitFunctionParameter(PredaParser::FunctionParameterContext *context) = 0;

    virtual std::any visitAccessSpecifier(PredaParser::AccessSpecifierContext *context) = 0;

    virtual std::any visitVariableDeclaration(PredaParser::VariableDeclarationContext *context) = 0;

    virtual std::any visitTypeNameOrAuto(PredaParser::TypeNameOrAutoContext *context) = 0;

    virtual std::any visitTypeName(PredaParser::TypeNameContext *context) = 0;

    virtual std::any visitFundamentalTypeName(PredaParser::FundamentalTypeNameContext *context) = 0;

    virtual std::any visitBuiltInContainerTypeName(PredaParser::BuiltInContainerTypeNameContext *context) = 0;

    virtual std::any visitMapKeyTypeName(PredaParser::MapKeyTypeNameContext *context) = 0;

    virtual std::any visitMapTypeName(PredaParser::MapTypeNameContext *context) = 0;

    virtual std::any visitScatteredMapTypeName(PredaParser::ScatteredMapTypeNameContext *context) = 0;

    virtual std::any visitArrayTypeName(PredaParser::ArrayTypeNameContext *context) = 0;

    virtual std::any visitScatteredArrayTypeName(PredaParser::ScatteredArrayTypeNameContext *context) = 0;

    virtual std::any visitUserDefinedTypeName(PredaParser::UserDefinedTypeNameContext *context) = 0;

    virtual std::any visitUserBlockStatement(PredaParser::UserBlockStatementContext *context) = 0;

    virtual std::any visitStatement(PredaParser::StatementContext *context) = 0;

    virtual std::any visitExpressionStatement(PredaParser::ExpressionStatementContext *context) = 0;

    virtual std::any visitIfStatement(PredaParser::IfStatementContext *context) = 0;

    virtual std::any visitIfWithBlock(PredaParser::IfWithBlockContext *context) = 0;

    virtual std::any visitElseWithBlock(PredaParser::ElseWithBlockContext *context) = 0;

    virtual std::any visitElseIfWithBlock(PredaParser::ElseIfWithBlockContext *context) = 0;

    virtual std::any visitWhileStatement(PredaParser::WhileStatementContext *context) = 0;

    virtual std::any visitRelayStatement(PredaParser::RelayStatementContext *context) = 0;

    virtual std::any visitRelayType(PredaParser::RelayTypeContext *context) = 0;

    virtual std::any visitRelayLambdaDefinition(PredaParser::RelayLambdaDefinitionContext *context) = 0;

    virtual std::any visitRelayLambdaParameter(PredaParser::RelayLambdaParameterContext *context) = 0;

    virtual std::any visitForStatement(PredaParser::ForStatementContext *context) = 0;

    virtual std::any visitDoWhileStatement(PredaParser::DoWhileStatementContext *context) = 0;

    virtual std::any visitContinueStatement(PredaParser::ContinueStatementContext *context) = 0;

    virtual std::any visitBreakStatement(PredaParser::BreakStatementContext *context) = 0;

    virtual std::any visitReturnStatement(PredaParser::ReturnStatementContext *context) = 0;

    virtual std::any visitVariableDeclarationStatement(PredaParser::VariableDeclarationStatementContext *context) = 0;

    virtual std::any visitLocalVariableDeclaration(PredaParser::LocalVariableDeclarationContext *context) = 0;

    virtual std::any visitExpression(PredaParser::ExpressionContext *context) = 0;

    virtual std::any visitPrimaryExpression(PredaParser::PrimaryExpressionContext *context) = 0;

    virtual std::any visitFunctionCallArguments(PredaParser::FunctionCallArgumentsContext *context) = 0;

    virtual std::any visitIdentifier(PredaParser::IdentifierContext *context) = 0;


};

