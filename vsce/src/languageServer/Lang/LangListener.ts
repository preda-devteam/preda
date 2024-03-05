// Generated from ./src/languageServer/Preda/Preda.g4 by ANTLR 4.9.0-SNAPSHOT


import { ParseTreeListener } from "antlr4ts/tree/ParseTreeListener";

import { PredaSourceContext } from "./LangParser";
import { DirectiveContext } from "./LangParser";
import { ImportDirectiveContext } from "./LangParser";
import { AnnotationContext } from "./LangParser";
import { AnnotationItemContext } from "./LangParser";
import { DoxygenContext } from "./LangParser";
import { ContractDefinitionContext } from "./LangParser";
import { InterfaceRefContext } from "./LangParser";
import { ContractPartContext } from "./LangParser";
import { StateVariableDeclarationContext } from "./LangParser";
import { ConstVariableDeclarationContext } from "./LangParser";
import { ScopeContext } from "./LangParser";
import { StructDefinitionContext } from "./LangParser";
import { InterfaceDefinitionContext } from "./LangParser";
import { EnumDefinitionContext } from "./LangParser";
import { FunctionDefinitionContext } from "./LangParser";
import { FunctionDeclarationContext } from "./LangParser";
import { FunctionReturnTypeNameContext } from "./LangParser";
import { FunctionParameterListContext } from "./LangParser";
import { FunctionParameterContext } from "./LangParser";
import { AccessSpecifierContext } from "./LangParser";
import { VariableDeclarationContext } from "./LangParser";
import { TypeNameOrAutoContext } from "./LangParser";
import { TypeNameContext } from "./LangParser";
import { FundamentalTypeNameContext } from "./LangParser";
import { BuiltInContainerTypeNameContext } from "./LangParser";
import { MapKeyTypeNameContext } from "./LangParser";
import { MapTypeNameContext } from "./LangParser";
import { ArrayTypeNameContext } from "./LangParser";
import { UserDefinedTypeNameContext } from "./LangParser";
import { UserBlockStatementContext } from "./LangParser";
import { StatementContext } from "./LangParser";
import { ExpressionStatementContext } from "./LangParser";
import { IfStatementContext } from "./LangParser";
import { IfWithBlockContext } from "./LangParser";
import { ElseWithBlockContext } from "./LangParser";
import { ElseIfWithBlockContext } from "./LangParser";
import { WhileStatementContext } from "./LangParser";
import { RelayStatementContext } from "./LangParser";
import { RelayTypeContext } from "./LangParser";
import { RelayLambdaDefinitionContext } from "./LangParser";
import { RelayLambdaParameterContext } from "./LangParser";
import { ForStatementContext } from "./LangParser";
import { DoWhileStatementContext } from "./LangParser";
import { ContinueStatementContext } from "./LangParser";
import { BreakStatementContext } from "./LangParser";
import { ReturnStatementContext } from "./LangParser";
import { VariableDeclarationStatementContext } from "./LangParser";
import { LocalVariableDeclarationContext } from "./LangParser";
import { ExpressionContext } from "./LangParser";
import { PrimaryExpressionContext } from "./LangParser";
import { FunctionCallArgumentsContext } from "./LangParser";
import { IdentifierContext } from "./LangParser";


/**
 * This interface defines a complete listener for a parse tree produced by
 * `PredaParser`.
 */
export interface PredaListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by `PredaParser.predaSource`.
	 * @param ctx the parse tree
	 */
	enterPredaSource?: (ctx: PredaSourceContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.predaSource`.
	 * @param ctx the parse tree
	 */
	exitPredaSource?: (ctx: PredaSourceContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.directive`.
	 * @param ctx the parse tree
	 */
	enterDirective?: (ctx: DirectiveContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.directive`.
	 * @param ctx the parse tree
	 */
	exitDirective?: (ctx: DirectiveContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.importDirective`.
	 * @param ctx the parse tree
	 */
	enterImportDirective?: (ctx: ImportDirectiveContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.importDirective`.
	 * @param ctx the parse tree
	 */
	exitImportDirective?: (ctx: ImportDirectiveContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.annotation`.
	 * @param ctx the parse tree
	 */
	enterAnnotation?: (ctx: AnnotationContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.annotation`.
	 * @param ctx the parse tree
	 */
	exitAnnotation?: (ctx: AnnotationContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.annotationItem`.
	 * @param ctx the parse tree
	 */
	enterAnnotationItem?: (ctx: AnnotationItemContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.annotationItem`.
	 * @param ctx the parse tree
	 */
	exitAnnotationItem?: (ctx: AnnotationItemContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.doxygen`.
	 * @param ctx the parse tree
	 */
	enterDoxygen?: (ctx: DoxygenContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.doxygen`.
	 * @param ctx the parse tree
	 */
	exitDoxygen?: (ctx: DoxygenContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.contractDefinition`.
	 * @param ctx the parse tree
	 */
	enterContractDefinition?: (ctx: ContractDefinitionContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.contractDefinition`.
	 * @param ctx the parse tree
	 */
	exitContractDefinition?: (ctx: ContractDefinitionContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.interfaceRef`.
	 * @param ctx the parse tree
	 */
	enterInterfaceRef?: (ctx: InterfaceRefContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.interfaceRef`.
	 * @param ctx the parse tree
	 */
	exitInterfaceRef?: (ctx: InterfaceRefContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.contractPart`.
	 * @param ctx the parse tree
	 */
	enterContractPart?: (ctx: ContractPartContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.contractPart`.
	 * @param ctx the parse tree
	 */
	exitContractPart?: (ctx: ContractPartContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.stateVariableDeclaration`.
	 * @param ctx the parse tree
	 */
	enterStateVariableDeclaration?: (ctx: StateVariableDeclarationContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.stateVariableDeclaration`.
	 * @param ctx the parse tree
	 */
	exitStateVariableDeclaration?: (ctx: StateVariableDeclarationContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.constVariableDeclaration`.
	 * @param ctx the parse tree
	 */
	enterConstVariableDeclaration?: (ctx: ConstVariableDeclarationContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.constVariableDeclaration`.
	 * @param ctx the parse tree
	 */
	exitConstVariableDeclaration?: (ctx: ConstVariableDeclarationContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.scope`.
	 * @param ctx the parse tree
	 */
	enterScope?: (ctx: ScopeContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.scope`.
	 * @param ctx the parse tree
	 */
	exitScope?: (ctx: ScopeContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.structDefinition`.
	 * @param ctx the parse tree
	 */
	enterStructDefinition?: (ctx: StructDefinitionContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.structDefinition`.
	 * @param ctx the parse tree
	 */
	exitStructDefinition?: (ctx: StructDefinitionContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.interfaceDefinition`.
	 * @param ctx the parse tree
	 */
	enterInterfaceDefinition?: (ctx: InterfaceDefinitionContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.interfaceDefinition`.
	 * @param ctx the parse tree
	 */
	exitInterfaceDefinition?: (ctx: InterfaceDefinitionContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.enumDefinition`.
	 * @param ctx the parse tree
	 */
	enterEnumDefinition?: (ctx: EnumDefinitionContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.enumDefinition`.
	 * @param ctx the parse tree
	 */
	exitEnumDefinition?: (ctx: EnumDefinitionContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.functionDefinition`.
	 * @param ctx the parse tree
	 */
	enterFunctionDefinition?: (ctx: FunctionDefinitionContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.functionDefinition`.
	 * @param ctx the parse tree
	 */
	exitFunctionDefinition?: (ctx: FunctionDefinitionContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.functionDeclaration`.
	 * @param ctx the parse tree
	 */
	enterFunctionDeclaration?: (ctx: FunctionDeclarationContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.functionDeclaration`.
	 * @param ctx the parse tree
	 */
	exitFunctionDeclaration?: (ctx: FunctionDeclarationContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.functionReturnTypeName`.
	 * @param ctx the parse tree
	 */
	enterFunctionReturnTypeName?: (ctx: FunctionReturnTypeNameContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.functionReturnTypeName`.
	 * @param ctx the parse tree
	 */
	exitFunctionReturnTypeName?: (ctx: FunctionReturnTypeNameContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.functionParameterList`.
	 * @param ctx the parse tree
	 */
	enterFunctionParameterList?: (ctx: FunctionParameterListContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.functionParameterList`.
	 * @param ctx the parse tree
	 */
	exitFunctionParameterList?: (ctx: FunctionParameterListContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.functionParameter`.
	 * @param ctx the parse tree
	 */
	enterFunctionParameter?: (ctx: FunctionParameterContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.functionParameter`.
	 * @param ctx the parse tree
	 */
	exitFunctionParameter?: (ctx: FunctionParameterContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.accessSpecifier`.
	 * @param ctx the parse tree
	 */
	enterAccessSpecifier?: (ctx: AccessSpecifierContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.accessSpecifier`.
	 * @param ctx the parse tree
	 */
	exitAccessSpecifier?: (ctx: AccessSpecifierContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.variableDeclaration`.
	 * @param ctx the parse tree
	 */
	enterVariableDeclaration?: (ctx: VariableDeclarationContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.variableDeclaration`.
	 * @param ctx the parse tree
	 */
	exitVariableDeclaration?: (ctx: VariableDeclarationContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.typeNameOrAuto`.
	 * @param ctx the parse tree
	 */
	enterTypeNameOrAuto?: (ctx: TypeNameOrAutoContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.typeNameOrAuto`.
	 * @param ctx the parse tree
	 */
	exitTypeNameOrAuto?: (ctx: TypeNameOrAutoContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.typeName`.
	 * @param ctx the parse tree
	 */
	enterTypeName?: (ctx: TypeNameContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.typeName`.
	 * @param ctx the parse tree
	 */
	exitTypeName?: (ctx: TypeNameContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.fundamentalTypeName`.
	 * @param ctx the parse tree
	 */
	enterFundamentalTypeName?: (ctx: FundamentalTypeNameContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.fundamentalTypeName`.
	 * @param ctx the parse tree
	 */
	exitFundamentalTypeName?: (ctx: FundamentalTypeNameContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.builtInContainerTypeName`.
	 * @param ctx the parse tree
	 */
	enterBuiltInContainerTypeName?: (ctx: BuiltInContainerTypeNameContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.builtInContainerTypeName`.
	 * @param ctx the parse tree
	 */
	exitBuiltInContainerTypeName?: (ctx: BuiltInContainerTypeNameContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.mapKeyTypeName`.
	 * @param ctx the parse tree
	 */
	enterMapKeyTypeName?: (ctx: MapKeyTypeNameContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.mapKeyTypeName`.
	 * @param ctx the parse tree
	 */
	exitMapKeyTypeName?: (ctx: MapKeyTypeNameContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.mapTypeName`.
	 * @param ctx the parse tree
	 */
	enterMapTypeName?: (ctx: MapTypeNameContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.mapTypeName`.
	 * @param ctx the parse tree
	 */
	exitMapTypeName?: (ctx: MapTypeNameContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.arrayTypeName`.
	 * @param ctx the parse tree
	 */
	enterArrayTypeName?: (ctx: ArrayTypeNameContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.arrayTypeName`.
	 * @param ctx the parse tree
	 */
	exitArrayTypeName?: (ctx: ArrayTypeNameContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.userDefinedTypeName`.
	 * @param ctx the parse tree
	 */
	enterUserDefinedTypeName?: (ctx: UserDefinedTypeNameContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.userDefinedTypeName`.
	 * @param ctx the parse tree
	 */
	exitUserDefinedTypeName?: (ctx: UserDefinedTypeNameContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.userBlockStatement`.
	 * @param ctx the parse tree
	 */
	enterUserBlockStatement?: (ctx: UserBlockStatementContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.userBlockStatement`.
	 * @param ctx the parse tree
	 */
	exitUserBlockStatement?: (ctx: UserBlockStatementContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.statement`.
	 * @param ctx the parse tree
	 */
	enterStatement?: (ctx: StatementContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.statement`.
	 * @param ctx the parse tree
	 */
	exitStatement?: (ctx: StatementContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.expressionStatement`.
	 * @param ctx the parse tree
	 */
	enterExpressionStatement?: (ctx: ExpressionStatementContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.expressionStatement`.
	 * @param ctx the parse tree
	 */
	exitExpressionStatement?: (ctx: ExpressionStatementContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.ifStatement`.
	 * @param ctx the parse tree
	 */
	enterIfStatement?: (ctx: IfStatementContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.ifStatement`.
	 * @param ctx the parse tree
	 */
	exitIfStatement?: (ctx: IfStatementContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.ifWithBlock`.
	 * @param ctx the parse tree
	 */
	enterIfWithBlock?: (ctx: IfWithBlockContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.ifWithBlock`.
	 * @param ctx the parse tree
	 */
	exitIfWithBlock?: (ctx: IfWithBlockContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.elseWithBlock`.
	 * @param ctx the parse tree
	 */
	enterElseWithBlock?: (ctx: ElseWithBlockContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.elseWithBlock`.
	 * @param ctx the parse tree
	 */
	exitElseWithBlock?: (ctx: ElseWithBlockContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.elseIfWithBlock`.
	 * @param ctx the parse tree
	 */
	enterElseIfWithBlock?: (ctx: ElseIfWithBlockContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.elseIfWithBlock`.
	 * @param ctx the parse tree
	 */
	exitElseIfWithBlock?: (ctx: ElseIfWithBlockContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.whileStatement`.
	 * @param ctx the parse tree
	 */
	enterWhileStatement?: (ctx: WhileStatementContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.whileStatement`.
	 * @param ctx the parse tree
	 */
	exitWhileStatement?: (ctx: WhileStatementContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.relayStatement`.
	 * @param ctx the parse tree
	 */
	enterRelayStatement?: (ctx: RelayStatementContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.relayStatement`.
	 * @param ctx the parse tree
	 */
	exitRelayStatement?: (ctx: RelayStatementContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.relayType`.
	 * @param ctx the parse tree
	 */
	enterRelayType?: (ctx: RelayTypeContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.relayType`.
	 * @param ctx the parse tree
	 */
	exitRelayType?: (ctx: RelayTypeContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.relayLambdaDefinition`.
	 * @param ctx the parse tree
	 */
	enterRelayLambdaDefinition?: (ctx: RelayLambdaDefinitionContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.relayLambdaDefinition`.
	 * @param ctx the parse tree
	 */
	exitRelayLambdaDefinition?: (ctx: RelayLambdaDefinitionContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.relayLambdaParameter`.
	 * @param ctx the parse tree
	 */
	enterRelayLambdaParameter?: (ctx: RelayLambdaParameterContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.relayLambdaParameter`.
	 * @param ctx the parse tree
	 */
	exitRelayLambdaParameter?: (ctx: RelayLambdaParameterContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.forStatement`.
	 * @param ctx the parse tree
	 */
	enterForStatement?: (ctx: ForStatementContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.forStatement`.
	 * @param ctx the parse tree
	 */
	exitForStatement?: (ctx: ForStatementContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.doWhileStatement`.
	 * @param ctx the parse tree
	 */
	enterDoWhileStatement?: (ctx: DoWhileStatementContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.doWhileStatement`.
	 * @param ctx the parse tree
	 */
	exitDoWhileStatement?: (ctx: DoWhileStatementContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.continueStatement`.
	 * @param ctx the parse tree
	 */
	enterContinueStatement?: (ctx: ContinueStatementContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.continueStatement`.
	 * @param ctx the parse tree
	 */
	exitContinueStatement?: (ctx: ContinueStatementContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.breakStatement`.
	 * @param ctx the parse tree
	 */
	enterBreakStatement?: (ctx: BreakStatementContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.breakStatement`.
	 * @param ctx the parse tree
	 */
	exitBreakStatement?: (ctx: BreakStatementContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.returnStatement`.
	 * @param ctx the parse tree
	 */
	enterReturnStatement?: (ctx: ReturnStatementContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.returnStatement`.
	 * @param ctx the parse tree
	 */
	exitReturnStatement?: (ctx: ReturnStatementContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.variableDeclarationStatement`.
	 * @param ctx the parse tree
	 */
	enterVariableDeclarationStatement?: (ctx: VariableDeclarationStatementContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.variableDeclarationStatement`.
	 * @param ctx the parse tree
	 */
	exitVariableDeclarationStatement?: (ctx: VariableDeclarationStatementContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.localVariableDeclaration`.
	 * @param ctx the parse tree
	 */
	enterLocalVariableDeclaration?: (ctx: LocalVariableDeclarationContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.localVariableDeclaration`.
	 * @param ctx the parse tree
	 */
	exitLocalVariableDeclaration?: (ctx: LocalVariableDeclarationContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.expression`.
	 * @param ctx the parse tree
	 */
	enterExpression?: (ctx: ExpressionContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.expression`.
	 * @param ctx the parse tree
	 */
	exitExpression?: (ctx: ExpressionContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.primaryExpression`.
	 * @param ctx the parse tree
	 */
	enterPrimaryExpression?: (ctx: PrimaryExpressionContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.primaryExpression`.
	 * @param ctx the parse tree
	 */
	exitPrimaryExpression?: (ctx: PrimaryExpressionContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.functionCallArguments`.
	 * @param ctx the parse tree
	 */
	enterFunctionCallArguments?: (ctx: FunctionCallArgumentsContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.functionCallArguments`.
	 * @param ctx the parse tree
	 */
	exitFunctionCallArguments?: (ctx: FunctionCallArgumentsContext) => void;

	/**
	 * Enter a parse tree produced by `PredaParser.identifier`.
	 * @param ctx the parse tree
	 */
	enterIdentifier?: (ctx: IdentifierContext) => void;
	/**
	 * Exit a parse tree produced by `PredaParser.identifier`.
	 * @param ctx the parse tree
	 */
	exitIdentifier?: (ctx: IdentifierContext) => void;
}

