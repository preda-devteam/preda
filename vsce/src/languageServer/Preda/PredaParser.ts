// Generated from ./src/languageServer/Preda/Preda.g4 by ANTLR 4.9.0-SNAPSHOT


import { ATN } from "antlr4ts/atn/ATN";
import { ATNDeserializer } from "antlr4ts/atn/ATNDeserializer";
import { FailedPredicateException } from "antlr4ts/FailedPredicateException";
import { NotNull } from "antlr4ts/Decorators";
import { NoViableAltException } from "antlr4ts/NoViableAltException";
import { Override } from "antlr4ts/Decorators";
import { Parser } from "antlr4ts/Parser";
import { ParserRuleContext } from "antlr4ts/ParserRuleContext";
import { ParserATNSimulator } from "antlr4ts/atn/ParserATNSimulator";
import { ParseTreeListener } from "antlr4ts/tree/ParseTreeListener";
import { ParseTreeVisitor } from "antlr4ts/tree/ParseTreeVisitor";
import { RecognitionException } from "antlr4ts/RecognitionException";
import { RuleContext } from "antlr4ts/RuleContext";
//import { RuleVersion } from "antlr4ts/RuleVersion";
import { TerminalNode } from "antlr4ts/tree/TerminalNode";
import { Token } from "antlr4ts/Token";
import { TokenStream } from "antlr4ts/TokenStream";
import { Vocabulary } from "antlr4ts/Vocabulary";
import { VocabularyImpl } from "antlr4ts/VocabularyImpl";

import * as Utils from "antlr4ts/misc/Utils";

import { PredaListener } from "./PredaListener";

export class PredaParser extends Parser {
	public static readonly T__0 = 1;
	public static readonly T__1 = 2;
	public static readonly T__2 = 3;
	public static readonly T__3 = 4;
	public static readonly T__4 = 5;
	public static readonly T__5 = 6;
	public static readonly T__6 = 7;
	public static readonly T__7 = 8;
	public static readonly T__8 = 9;
	public static readonly T__9 = 10;
	public static readonly T__10 = 11;
	public static readonly T__11 = 12;
	public static readonly T__12 = 13;
	public static readonly T__13 = 14;
	public static readonly T__14 = 15;
	public static readonly T__15 = 16;
	public static readonly T__16 = 17;
	public static readonly T__17 = 18;
	public static readonly T__18 = 19;
	public static readonly T__19 = 20;
	public static readonly T__20 = 21;
	public static readonly T__21 = 22;
	public static readonly T__22 = 23;
	public static readonly T__23 = 24;
	public static readonly T__24 = 25;
	public static readonly T__25 = 26;
	public static readonly T__26 = 27;
	public static readonly T__27 = 28;
	public static readonly T__28 = 29;
	public static readonly T__29 = 30;
	public static readonly T__30 = 31;
	public static readonly T__31 = 32;
	public static readonly T__32 = 33;
	public static readonly T__33 = 34;
	public static readonly T__34 = 35;
	public static readonly T__35 = 36;
	public static readonly T__36 = 37;
	public static readonly T__37 = 38;
	public static readonly T__38 = 39;
	public static readonly T__39 = 40;
	public static readonly T__40 = 41;
	public static readonly T__41 = 42;
	public static readonly T__42 = 43;
	public static readonly T__43 = 44;
	public static readonly T__44 = 45;
	public static readonly T__45 = 46;
	public static readonly T__46 = 47;
	public static readonly T__47 = 48;
	public static readonly T__48 = 49;
	public static readonly T__49 = 50;
	public static readonly T__50 = 51;
	public static readonly T__51 = 52;
	public static readonly T__52 = 53;
	public static readonly T__53 = 54;
	public static readonly T__54 = 55;
	public static readonly DoxygenSingle = 56;
	public static readonly DoxygenMulti = 57;
	public static readonly BreakKeyword = 58;
	public static readonly ConstantKeyword = 59;
	public static readonly ContinueKeyword = 60;
	public static readonly RelayKeyword = 61;
	public static readonly SupplyKeyword = 62;
	public static readonly IfKeyword = 63;
	public static readonly ElseKeyword = 64;
	public static readonly ShardKeyword = 65;
	public static readonly ShardsKeyword = 66;
	public static readonly GlobalKeyword = 67;
	public static readonly AddressKeyword = 68;
	public static readonly AutoKeyword = 69;
	public static readonly MinerKeyword = 70;
	public static readonly StructKeyword = 71;
	public static readonly EnumKeyword = 72;
	public static readonly ContractKeyword = 73;
	public static readonly ImportKeyword = 74;
	public static readonly FunctionKeyword = 75;
	public static readonly PublicKeyword = 76;
	public static readonly ExportKeyword = 77;
	public static readonly AsKeyword = 78;
	public static readonly UsingKeyword = 79;
	public static readonly InterfaceKeyword = 80;
	public static readonly ImplementsKeyword = 81;
	public static readonly FloatType = 82;
	public static readonly IntType = 83;
	public static readonly UintType = 84;
	public static readonly BooleanLiteral = 85;
	public static readonly DecimalFloatLiteral = 86;
	public static readonly DecimalIntegerLiteral = 87;
	public static readonly DecimalIntegerLiteralBody = 88;
	public static readonly AddressLiteral = 89;
	public static readonly HashLiteral = 90;
	public static readonly HexIntegerLiteral = 91;
	public static readonly HexIntegerLiteralBody = 92;
	public static readonly DecimalBigIntegerLiteral = 93;
	public static readonly HexBigIntegerLiteral = 94;
	public static readonly Identifier = 95;
	public static readonly StringLiteral = 96;
	public static readonly WS = 97;
	public static readonly COMMENT = 98;
	public static readonly LINE_COMMENT = 99;
	public static readonly RULE_predaSource = 0;
	public static readonly RULE_directive = 1;
	public static readonly RULE_importDirective = 2;
	public static readonly RULE_annotation = 3;
	public static readonly RULE_annotationItem = 4;
	public static readonly RULE_doxygen = 5;
	public static readonly RULE_contractDefinition = 6;
	public static readonly RULE_interfaceRef = 7;
	public static readonly RULE_contractPart = 8;
	public static readonly RULE_stateVariableDeclaration = 9;
	public static readonly RULE_constVariableDeclaration = 10;
	public static readonly RULE_scope = 11;
	public static readonly RULE_structDefinition = 12;
	public static readonly RULE_interfaceDefinition = 13;
	public static readonly RULE_enumDefinition = 14;
	public static readonly RULE_functionDefinition = 15;
	public static readonly RULE_functionDeclaration = 16;
	public static readonly RULE_functionReturnTypeName = 17;
	public static readonly RULE_functionParameterList = 18;
	public static readonly RULE_functionParameter = 19;
	public static readonly RULE_accessSpecifier = 20;
	public static readonly RULE_variableDeclaration = 21;
	public static readonly RULE_typeNameOrAuto = 22;
	public static readonly RULE_typeName = 23;
	public static readonly RULE_fundamentalTypeName = 24;
	public static readonly RULE_builtInContainerTypeName = 25;
	public static readonly RULE_mapKeyTypeName = 26;
	public static readonly RULE_mapTypeName = 27;
	public static readonly RULE_arrayTypeName = 28;
	public static readonly RULE_userDefinedTypeName = 29;
	public static readonly RULE_userBlockStatement = 30;
	public static readonly RULE_statement = 31;
	public static readonly RULE_expressionStatement = 32;
	public static readonly RULE_ifStatement = 33;
	public static readonly RULE_ifWithBlock = 34;
	public static readonly RULE_elseWithBlock = 35;
	public static readonly RULE_elseIfWithBlock = 36;
	public static readonly RULE_whileStatement = 37;
	public static readonly RULE_relayStatement = 38;
	public static readonly RULE_relayType = 39;
	public static readonly RULE_relayLambdaDefinition = 40;
	public static readonly RULE_relayLambdaParameter = 41;
	public static readonly RULE_forStatement = 42;
	public static readonly RULE_doWhileStatement = 43;
	public static readonly RULE_continueStatement = 44;
	public static readonly RULE_breakStatement = 45;
	public static readonly RULE_returnStatement = 46;
	public static readonly RULE_variableDeclarationStatement = 47;
	public static readonly RULE_localVariableDeclaration = 48;
	public static readonly RULE_expression = 49;
	public static readonly RULE_primaryExpression = 50;
	public static readonly RULE_functionCallArguments = 51;
	public static readonly RULE_identifier = 52;
	// tslint:disable:no-trailing-whitespace
	public static readonly ruleNames: string[] = [
		"predaSource", "directive", "importDirective", "annotation", "annotationItem", 
		"doxygen", "contractDefinition", "interfaceRef", "contractPart", "stateVariableDeclaration", 
		"constVariableDeclaration", "scope", "structDefinition", "interfaceDefinition", 
		"enumDefinition", "functionDefinition", "functionDeclaration", "functionReturnTypeName", 
		"functionParameterList", "functionParameter", "accessSpecifier", "variableDeclaration", 
		"typeNameOrAuto", "typeName", "fundamentalTypeName", "builtInContainerTypeName", 
		"mapKeyTypeName", "mapTypeName", "arrayTypeName", "userDefinedTypeName", 
		"userBlockStatement", "statement", "expressionStatement", "ifStatement", 
		"ifWithBlock", "elseWithBlock", "elseIfWithBlock", "whileStatement", "relayStatement", 
		"relayType", "relayLambdaDefinition", "relayLambdaParameter", "forStatement", 
		"doWhileStatement", "continueStatement", "breakStatement", "returnStatement", 
		"variableDeclarationStatement", "localVariableDeclaration", "expression", 
		"primaryExpression", "functionCallArguments", "identifier",
	];

	private static readonly _LITERAL_NAMES: Array<string | undefined> = [
		undefined, "'.'", "';'", "'['", "','", "']'", "'='", "'{'", "'}'", "'@'", 
		"'('", "')'", "'bool'", "'string'", "'blob'", "'hash'", "'bigint'", "'map'", 
		"'<'", "'>'", "'array'", "'while'", "'^'", "'for'", "'do'", "'return'", 
		"'++'", "'--'", "'+'", "'-'", "'!'", "'~'", "'*'", "'/'", "'%'", "'<<'", 
		"'<='", "'>='", "'=='", "'!='", "'&'", "'|'", "'&&'", "'||'", "'?'", "':'", 
		"'+='", "'-='", "'*='", "'/='", "'%='", "'<<='", "'>>='", "'&='", "'^='", 
		"'|='", undefined, undefined, "'break'", "'const'", "'continue'", "'relay'", 
		"'supply'", "'if'", "'else'", "'shard'", "'shards'", "'global'", "'address'", 
		"'auto'", "'miner'", "'struct'", "'enum'", "'contract'", "'import'", "'function'", 
		"'public'", "'export'", "'as'", "'using'", "'interface'", "'implements'",
	];
	private static readonly _SYMBOLIC_NAMES: Array<string | undefined> = [
		undefined, undefined, undefined, undefined, undefined, undefined, undefined, 
		undefined, undefined, undefined, undefined, undefined, undefined, undefined, 
		undefined, undefined, undefined, undefined, undefined, undefined, undefined, 
		undefined, undefined, undefined, undefined, undefined, undefined, undefined, 
		undefined, undefined, undefined, undefined, undefined, undefined, undefined, 
		undefined, undefined, undefined, undefined, undefined, undefined, undefined, 
		undefined, undefined, undefined, undefined, undefined, undefined, undefined, 
		undefined, undefined, undefined, undefined, undefined, undefined, undefined, 
		"DoxygenSingle", "DoxygenMulti", "BreakKeyword", "ConstantKeyword", "ContinueKeyword", 
		"RelayKeyword", "SupplyKeyword", "IfKeyword", "ElseKeyword", "ShardKeyword", 
		"ShardsKeyword", "GlobalKeyword", "AddressKeyword", "AutoKeyword", "MinerKeyword", 
		"StructKeyword", "EnumKeyword", "ContractKeyword", "ImportKeyword", "FunctionKeyword", 
		"PublicKeyword", "ExportKeyword", "AsKeyword", "UsingKeyword", "InterfaceKeyword", 
		"ImplementsKeyword", "FloatType", "IntType", "UintType", "BooleanLiteral", 
		"DecimalFloatLiteral", "DecimalIntegerLiteral", "DecimalIntegerLiteralBody", 
		"AddressLiteral", "HashLiteral", "HexIntegerLiteral", "HexIntegerLiteralBody", 
		"DecimalBigIntegerLiteral", "HexBigIntegerLiteral", "Identifier", "StringLiteral", 
		"WS", "COMMENT", "LINE_COMMENT",
	];
	public static readonly VOCABULARY: Vocabulary = new VocabularyImpl(PredaParser._LITERAL_NAMES, PredaParser._SYMBOLIC_NAMES, []);

	// @Override
	// @NotNull
	public get vocabulary(): Vocabulary {
		return PredaParser.VOCABULARY;
	}
	// tslint:enable:no-trailing-whitespace

	// @Override
	public get grammarFileName(): string { return "Preda.g4"; }

	// @Override
	public get ruleNames(): string[] { return PredaParser.ruleNames; }

	// @Override
	public get serializedATN(): string { return PredaParser._serializedATN; }

	protected createFailedPredicateException(predicate?: string, message?: string): FailedPredicateException {
		return new FailedPredicateException(this, predicate, message);
	}

	constructor(input: TokenStream) {
		super(input);
		this._interp = new ParserATNSimulator(PredaParser._ATN, this);
	}
	// @RuleVersion(0)
	public predaSource(): PredaSourceContext {
		let _localctx: PredaSourceContext = new PredaSourceContext(this._ctx, this.state);
		this.enterRule(_localctx, 0, PredaParser.RULE_predaSource);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 109;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			while (_la === PredaParser.ImportKeyword) {
				{
				{
				this.state = 106;
				this.directive();
				}
				}
				this.state = 111;
				this._errHandler.sync(this);
				_la = this._input.LA(1);
			}
			this.state = 112;
			this.contractDefinition();
			this.state = 113;
			this.match(PredaParser.EOF);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public directive(): DirectiveContext {
		let _localctx: DirectiveContext = new DirectiveContext(this._ctx, this.state);
		this.enterRule(_localctx, 2, PredaParser.RULE_directive);
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 115;
			this.importDirective();
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public importDirective(): ImportDirectiveContext {
		let _localctx: ImportDirectiveContext = new ImportDirectiveContext(this._ctx, this.state);
		this.enterRule(_localctx, 4, PredaParser.RULE_importDirective);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 117;
			this.match(PredaParser.ImportKeyword);
			this.state = 121;
			this._errHandler.sync(this);
			switch ( this.interpreter.adaptivePredict(this._input, 1, this._ctx) ) {
			case 1:
				{
				this.state = 118;
				_localctx._dAppName = this.identifier();
				this.state = 119;
				this.match(PredaParser.T__0);
				}
				break;
			}
			this.state = 123;
			_localctx._contractName = this.identifier();
			this.state = 126;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la === PredaParser.AsKeyword) {
				{
				this.state = 124;
				this.match(PredaParser.AsKeyword);
				this.state = 125;
				_localctx._alias = this.identifier();
				}
			}

			this.state = 128;
			this.match(PredaParser.T__1);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public annotation(): AnnotationContext {
		let _localctx: AnnotationContext = new AnnotationContext(this._ctx, this.state);
		this.enterRule(_localctx, 6, PredaParser.RULE_annotation);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 130;
			this.match(PredaParser.T__2);
			this.state = 132;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la === PredaParser.Identifier) {
				{
				this.state = 131;
				this.annotationItem();
				}
			}

			this.state = 138;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			while (_la === PredaParser.T__3) {
				{
				{
				this.state = 134;
				this.match(PredaParser.T__3);
				this.state = 135;
				this.annotationItem();
				}
				}
				this.state = 140;
				this._errHandler.sync(this);
				_la = this._input.LA(1);
			}
			this.state = 141;
			this.match(PredaParser.T__4);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public annotationItem(): AnnotationItemContext {
		let _localctx: AnnotationItemContext = new AnnotationItemContext(this._ctx, this.state);
		this.enterRule(_localctx, 8, PredaParser.RULE_annotationItem);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 143;
			this.identifier();
			this.state = 144;
			this.match(PredaParser.T__5);
			this.state = 145;
			_la = this._input.LA(1);
			if (!(((((_la - 85)) & ~0x1F) === 0 && ((1 << (_la - 85)) & ((1 << (PredaParser.BooleanLiteral - 85)) | (1 << (PredaParser.DecimalFloatLiteral - 85)) | (1 << (PredaParser.DecimalIntegerLiteral - 85)) | (1 << (PredaParser.HexIntegerLiteral - 85)) | (1 << (PredaParser.StringLiteral - 85)))) !== 0))) {
			this._errHandler.recoverInline(this);
			} else {
				if (this._input.LA(1) === Token.EOF) {
					this.matchedEOF = true;
				}

				this._errHandler.reportMatch(this);
				this.consume();
			}
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public doxygen(): DoxygenContext {
		let _localctx: DoxygenContext = new DoxygenContext(this._ctx, this.state);
		this.enterRule(_localctx, 10, PredaParser.RULE_doxygen);
		let _la: number;
		try {
			this.state = 153;
			this._errHandler.sync(this);
			switch (this._input.LA(1)) {
			case PredaParser.DoxygenSingle:
				this.enterOuterAlt(_localctx, 1);
				{
				this.state = 148;
				this._errHandler.sync(this);
				_la = this._input.LA(1);
				do {
					{
					{
					this.state = 147;
					this.match(PredaParser.DoxygenSingle);
					}
					}
					this.state = 150;
					this._errHandler.sync(this);
					_la = this._input.LA(1);
				} while (_la === PredaParser.DoxygenSingle);
				}
				break;
			case PredaParser.DoxygenMulti:
				this.enterOuterAlt(_localctx, 2);
				{
				this.state = 152;
				this.match(PredaParser.DoxygenMulti);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public contractDefinition(): ContractDefinitionContext {
		let _localctx: ContractDefinitionContext = new ContractDefinitionContext(this._ctx, this.state);
		this.enterRule(_localctx, 12, PredaParser.RULE_contractDefinition);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 156;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la === PredaParser.DoxygenSingle || _la === PredaParser.DoxygenMulti) {
				{
				this.state = 155;
				this.doxygen();
				}
			}

			this.state = 159;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la === PredaParser.T__2) {
				{
				this.state = 158;
				this.annotation();
				}
			}

			this.state = 161;
			this.match(PredaParser.ContractKeyword);
			this.state = 162;
			this.identifier();
			this.state = 172;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la === PredaParser.ImplementsKeyword) {
				{
				this.state = 163;
				this.match(PredaParser.ImplementsKeyword);
				this.state = 164;
				this.interfaceRef();
				this.state = 169;
				this._errHandler.sync(this);
				_la = this._input.LA(1);
				while (_la === PredaParser.T__3) {
					{
					{
					this.state = 165;
					this.match(PredaParser.T__3);
					this.state = 166;
					this.interfaceRef();
					}
					}
					this.state = 171;
					this._errHandler.sync(this);
					_la = this._input.LA(1);
				}
				}
			}

			this.state = 174;
			this.match(PredaParser.T__6);
			this.state = 178;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			while ((((_la) & ~0x1F) === 0 && ((1 << _la) & ((1 << PredaParser.T__2) | (1 << PredaParser.T__8) | (1 << PredaParser.T__11) | (1 << PredaParser.T__12) | (1 << PredaParser.T__13) | (1 << PredaParser.T__14) | (1 << PredaParser.T__15) | (1 << PredaParser.T__16) | (1 << PredaParser.T__19))) !== 0) || ((((_la - 56)) & ~0x1F) === 0 && ((1 << (_la - 56)) & ((1 << (PredaParser.DoxygenSingle - 56)) | (1 << (PredaParser.DoxygenMulti - 56)) | (1 << (PredaParser.ConstantKeyword - 56)) | (1 << (PredaParser.AddressKeyword - 56)) | (1 << (PredaParser.StructKeyword - 56)) | (1 << (PredaParser.EnumKeyword - 56)) | (1 << (PredaParser.FunctionKeyword - 56)) | (1 << (PredaParser.InterfaceKeyword - 56)) | (1 << (PredaParser.FloatType - 56)) | (1 << (PredaParser.IntType - 56)) | (1 << (PredaParser.UintType - 56)))) !== 0) || _la === PredaParser.Identifier) {
				{
				{
				this.state = 175;
				this.contractPart();
				}
				}
				this.state = 180;
				this._errHandler.sync(this);
				_la = this._input.LA(1);
			}
			this.state = 181;
			this.match(PredaParser.T__7);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public interfaceRef(): InterfaceRefContext {
		let _localctx: InterfaceRefContext = new InterfaceRefContext(this._ctx, this.state);
		this.enterRule(_localctx, 14, PredaParser.RULE_interfaceRef);
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 186;
			this._errHandler.sync(this);
			switch ( this.interpreter.adaptivePredict(this._input, 12, this._ctx) ) {
			case 1:
				{
				this.state = 183;
				_localctx._contractName = this.identifier();
				this.state = 184;
				this.match(PredaParser.T__0);
				}
				break;
			}
			this.state = 188;
			_localctx._interfaceName = this.identifier();
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public contractPart(): ContractPartContext {
		let _localctx: ContractPartContext = new ContractPartContext(this._ctx, this.state);
		this.enterRule(_localctx, 16, PredaParser.RULE_contractPart);
		try {
			this.state = 196;
			this._errHandler.sync(this);
			switch ( this.interpreter.adaptivePredict(this._input, 13, this._ctx) ) {
			case 1:
				this.enterOuterAlt(_localctx, 1);
				{
				this.state = 190;
				this.stateVariableDeclaration();
				}
				break;

			case 2:
				this.enterOuterAlt(_localctx, 2);
				{
				this.state = 191;
				this.constVariableDeclaration();
				}
				break;

			case 3:
				this.enterOuterAlt(_localctx, 3);
				{
				this.state = 192;
				this.structDefinition();
				}
				break;

			case 4:
				this.enterOuterAlt(_localctx, 4);
				{
				this.state = 193;
				this.enumDefinition();
				}
				break;

			case 5:
				this.enterOuterAlt(_localctx, 5);
				{
				this.state = 194;
				this.interfaceDefinition();
				}
				break;

			case 6:
				this.enterOuterAlt(_localctx, 6);
				{
				this.state = 195;
				this.functionDefinition();
				}
				break;
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public stateVariableDeclaration(): StateVariableDeclarationContext {
		let _localctx: StateVariableDeclarationContext = new StateVariableDeclarationContext(this._ctx, this.state);
		this.enterRule(_localctx, 18, PredaParser.RULE_stateVariableDeclaration);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 199;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la === PredaParser.DoxygenSingle || _la === PredaParser.DoxygenMulti) {
				{
				this.state = 198;
				this.doxygen();
				}
			}

			this.state = 202;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la === PredaParser.T__2) {
				{
				this.state = 201;
				this.annotation();
				}
			}

			this.state = 205;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la === PredaParser.T__8) {
				{
				this.state = 204;
				this.scope();
				}
			}

			this.state = 207;
			this.typeName();
			this.state = 208;
			this.identifier();
			this.state = 209;
			this.match(PredaParser.T__1);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public constVariableDeclaration(): ConstVariableDeclarationContext {
		let _localctx: ConstVariableDeclarationContext = new ConstVariableDeclarationContext(this._ctx, this.state);
		this.enterRule(_localctx, 20, PredaParser.RULE_constVariableDeclaration);
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 211;
			this.match(PredaParser.ConstantKeyword);
			this.state = 212;
			this.typeName();
			this.state = 213;
			this.identifier();
			this.state = 214;
			this.match(PredaParser.T__5);
			this.state = 215;
			this.expression(0);
			this.state = 216;
			this.match(PredaParser.T__1);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public scope(): ScopeContext {
		let _localctx: ScopeContext = new ScopeContext(this._ctx, this.state);
		this.enterRule(_localctx, 22, PredaParser.RULE_scope);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 218;
			this.match(PredaParser.T__8);
			this.state = 219;
			_la = this._input.LA(1);
			if (!(((((_la - 65)) & ~0x1F) === 0 && ((1 << (_la - 65)) & ((1 << (PredaParser.ShardKeyword - 65)) | (1 << (PredaParser.GlobalKeyword - 65)) | (1 << (PredaParser.AddressKeyword - 65)) | (1 << (PredaParser.UintType - 65)))) !== 0))) {
			this._errHandler.recoverInline(this);
			} else {
				if (this._input.LA(1) === Token.EOF) {
					this.matchedEOF = true;
				}

				this._errHandler.reportMatch(this);
				this.consume();
			}
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public structDefinition(): StructDefinitionContext {
		let _localctx: StructDefinitionContext = new StructDefinitionContext(this._ctx, this.state);
		this.enterRule(_localctx, 24, PredaParser.RULE_structDefinition);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 222;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la === PredaParser.DoxygenSingle || _la === PredaParser.DoxygenMulti) {
				{
				this.state = 221;
				this.doxygen();
				}
			}

			this.state = 225;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la === PredaParser.T__2) {
				{
				this.state = 224;
				this.annotation();
				}
			}

			this.state = 227;
			this.match(PredaParser.StructKeyword);
			this.state = 228;
			this.identifier();
			this.state = 229;
			this.match(PredaParser.T__6);
			this.state = 235;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			while ((((_la) & ~0x1F) === 0 && ((1 << _la) & ((1 << PredaParser.T__11) | (1 << PredaParser.T__12) | (1 << PredaParser.T__13) | (1 << PredaParser.T__14) | (1 << PredaParser.T__15) | (1 << PredaParser.T__16) | (1 << PredaParser.T__19))) !== 0) || ((((_la - 68)) & ~0x1F) === 0 && ((1 << (_la - 68)) & ((1 << (PredaParser.AddressKeyword - 68)) | (1 << (PredaParser.FloatType - 68)) | (1 << (PredaParser.IntType - 68)) | (1 << (PredaParser.UintType - 68)) | (1 << (PredaParser.Identifier - 68)))) !== 0)) {
				{
				{
				this.state = 230;
				this.variableDeclaration();
				this.state = 231;
				this.match(PredaParser.T__1);
				}
				}
				this.state = 237;
				this._errHandler.sync(this);
				_la = this._input.LA(1);
			}
			this.state = 238;
			this.match(PredaParser.T__7);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public interfaceDefinition(): InterfaceDefinitionContext {
		let _localctx: InterfaceDefinitionContext = new InterfaceDefinitionContext(this._ctx, this.state);
		this.enterRule(_localctx, 26, PredaParser.RULE_interfaceDefinition);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 240;
			this.match(PredaParser.InterfaceKeyword);
			this.state = 241;
			this.identifier();
			this.state = 242;
			this.match(PredaParser.T__6);
			this.state = 248;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			while (_la === PredaParser.T__2 || _la === PredaParser.T__8 || ((((_la - 56)) & ~0x1F) === 0 && ((1 << (_la - 56)) & ((1 << (PredaParser.DoxygenSingle - 56)) | (1 << (PredaParser.DoxygenMulti - 56)) | (1 << (PredaParser.FunctionKeyword - 56)))) !== 0)) {
				{
				{
				this.state = 243;
				this.functionDeclaration();
				this.state = 244;
				this.match(PredaParser.T__1);
				}
				}
				this.state = 250;
				this._errHandler.sync(this);
				_la = this._input.LA(1);
			}
			this.state = 251;
			this.match(PredaParser.T__7);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public enumDefinition(): EnumDefinitionContext {
		let _localctx: EnumDefinitionContext = new EnumDefinitionContext(this._ctx, this.state);
		this.enterRule(_localctx, 28, PredaParser.RULE_enumDefinition);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 254;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la === PredaParser.DoxygenSingle || _la === PredaParser.DoxygenMulti) {
				{
				this.state = 253;
				this.doxygen();
				}
			}

			this.state = 257;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la === PredaParser.T__2) {
				{
				this.state = 256;
				this.annotation();
				}
			}

			this.state = 259;
			this.match(PredaParser.EnumKeyword);
			this.state = 260;
			this.identifier();
			this.state = 261;
			this.match(PredaParser.T__6);
			this.state = 263;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la === PredaParser.Identifier) {
				{
				this.state = 262;
				this.identifier();
				}
			}

			this.state = 269;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			while (_la === PredaParser.T__3) {
				{
				{
				this.state = 265;
				this.match(PredaParser.T__3);
				this.state = 266;
				this.identifier();
				}
				}
				this.state = 271;
				this._errHandler.sync(this);
				_la = this._input.LA(1);
			}
			this.state = 272;
			this.match(PredaParser.T__7);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public functionDefinition(): FunctionDefinitionContext {
		let _localctx: FunctionDefinitionContext = new FunctionDefinitionContext(this._ctx, this.state);
		this.enterRule(_localctx, 30, PredaParser.RULE_functionDefinition);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 274;
			this.functionDeclaration();
			this.state = 275;
			this.match(PredaParser.T__6);
			this.state = 279;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			while ((((_la) & ~0x1F) === 0 && ((1 << _la) & ((1 << PredaParser.T__6) | (1 << PredaParser.T__9) | (1 << PredaParser.T__11) | (1 << PredaParser.T__12) | (1 << PredaParser.T__13) | (1 << PredaParser.T__14) | (1 << PredaParser.T__15) | (1 << PredaParser.T__16) | (1 << PredaParser.T__19) | (1 << PredaParser.T__20) | (1 << PredaParser.T__22) | (1 << PredaParser.T__23) | (1 << PredaParser.T__24) | (1 << PredaParser.T__25) | (1 << PredaParser.T__26) | (1 << PredaParser.T__27) | (1 << PredaParser.T__28) | (1 << PredaParser.T__29) | (1 << PredaParser.T__30))) !== 0) || ((((_la - 58)) & ~0x1F) === 0 && ((1 << (_la - 58)) & ((1 << (PredaParser.BreakKeyword - 58)) | (1 << (PredaParser.ConstantKeyword - 58)) | (1 << (PredaParser.ContinueKeyword - 58)) | (1 << (PredaParser.RelayKeyword - 58)) | (1 << (PredaParser.IfKeyword - 58)) | (1 << (PredaParser.AddressKeyword - 58)) | (1 << (PredaParser.AutoKeyword - 58)) | (1 << (PredaParser.FloatType - 58)) | (1 << (PredaParser.IntType - 58)) | (1 << (PredaParser.UintType - 58)) | (1 << (PredaParser.BooleanLiteral - 58)) | (1 << (PredaParser.DecimalFloatLiteral - 58)) | (1 << (PredaParser.DecimalIntegerLiteral - 58)) | (1 << (PredaParser.AddressLiteral - 58)))) !== 0) || ((((_la - 90)) & ~0x1F) === 0 && ((1 << (_la - 90)) & ((1 << (PredaParser.HashLiteral - 90)) | (1 << (PredaParser.HexIntegerLiteral - 90)) | (1 << (PredaParser.DecimalBigIntegerLiteral - 90)) | (1 << (PredaParser.HexBigIntegerLiteral - 90)) | (1 << (PredaParser.Identifier - 90)) | (1 << (PredaParser.StringLiteral - 90)))) !== 0)) {
				{
				{
				this.state = 276;
				this.statement();
				}
				}
				this.state = 281;
				this._errHandler.sync(this);
				_la = this._input.LA(1);
			}
			this.state = 282;
			this.match(PredaParser.T__7);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public functionDeclaration(): FunctionDeclarationContext {
		let _localctx: FunctionDeclarationContext = new FunctionDeclarationContext(this._ctx, this.state);
		this.enterRule(_localctx, 32, PredaParser.RULE_functionDeclaration);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 285;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la === PredaParser.DoxygenSingle || _la === PredaParser.DoxygenMulti) {
				{
				this.state = 284;
				this.doxygen();
				}
			}

			this.state = 288;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la === PredaParser.T__2) {
				{
				this.state = 287;
				this.annotation();
				}
			}

			this.state = 291;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la === PredaParser.T__8) {
				{
				this.state = 290;
				this.scope();
				}
			}

			this.state = 293;
			this.match(PredaParser.FunctionKeyword);
			this.state = 295;
			this._errHandler.sync(this);
			switch ( this.interpreter.adaptivePredict(this._input, 29, this._ctx) ) {
			case 1:
				{
				this.state = 294;
				this.functionReturnTypeName();
				}
				break;
			}
			this.state = 297;
			this.identifier();
			this.state = 298;
			this.match(PredaParser.T__9);
			this.state = 299;
			this.functionParameterList();
			this.state = 300;
			this.match(PredaParser.T__10);
			this.state = 304;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			while (_la === PredaParser.PublicKeyword || _la === PredaParser.ExportKeyword) {
				{
				{
				this.state = 301;
				this.accessSpecifier();
				}
				}
				this.state = 306;
				this._errHandler.sync(this);
				_la = this._input.LA(1);
			}
			this.state = 308;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la === PredaParser.ConstantKeyword) {
				{
				this.state = 307;
				this.match(PredaParser.ConstantKeyword);
				}
			}

			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public functionReturnTypeName(): FunctionReturnTypeNameContext {
		let _localctx: FunctionReturnTypeNameContext = new FunctionReturnTypeNameContext(this._ctx, this.state);
		this.enterRule(_localctx, 34, PredaParser.RULE_functionReturnTypeName);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 311;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la === PredaParser.ConstantKeyword) {
				{
				this.state = 310;
				this.match(PredaParser.ConstantKeyword);
				}
			}

			this.state = 313;
			this.typeName();
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public functionParameterList(): FunctionParameterListContext {
		let _localctx: FunctionParameterListContext = new FunctionParameterListContext(this._ctx, this.state);
		this.enterRule(_localctx, 36, PredaParser.RULE_functionParameterList);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 323;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if ((((_la) & ~0x1F) === 0 && ((1 << _la) & ((1 << PredaParser.T__11) | (1 << PredaParser.T__12) | (1 << PredaParser.T__13) | (1 << PredaParser.T__14) | (1 << PredaParser.T__15) | (1 << PredaParser.T__16) | (1 << PredaParser.T__19))) !== 0) || ((((_la - 59)) & ~0x1F) === 0 && ((1 << (_la - 59)) & ((1 << (PredaParser.ConstantKeyword - 59)) | (1 << (PredaParser.AddressKeyword - 59)) | (1 << (PredaParser.FloatType - 59)) | (1 << (PredaParser.IntType - 59)) | (1 << (PredaParser.UintType - 59)))) !== 0) || _la === PredaParser.Identifier) {
				{
				this.state = 315;
				this.functionParameter();
				this.state = 320;
				this._errHandler.sync(this);
				_la = this._input.LA(1);
				while (_la === PredaParser.T__3) {
					{
					{
					this.state = 316;
					this.match(PredaParser.T__3);
					this.state = 317;
					this.functionParameter();
					}
					}
					this.state = 322;
					this._errHandler.sync(this);
					_la = this._input.LA(1);
				}
				}
			}

			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public functionParameter(): FunctionParameterContext {
		let _localctx: FunctionParameterContext = new FunctionParameterContext(this._ctx, this.state);
		this.enterRule(_localctx, 38, PredaParser.RULE_functionParameter);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 326;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la === PredaParser.ConstantKeyword) {
				{
				this.state = 325;
				this.match(PredaParser.ConstantKeyword);
				}
			}

			this.state = 328;
			this.typeName();
			this.state = 329;
			this.identifier();
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public accessSpecifier(): AccessSpecifierContext {
		let _localctx: AccessSpecifierContext = new AccessSpecifierContext(this._ctx, this.state);
		this.enterRule(_localctx, 40, PredaParser.RULE_accessSpecifier);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 331;
			_la = this._input.LA(1);
			if (!(_la === PredaParser.PublicKeyword || _la === PredaParser.ExportKeyword)) {
			this._errHandler.recoverInline(this);
			} else {
				if (this._input.LA(1) === Token.EOF) {
					this.matchedEOF = true;
				}

				this._errHandler.reportMatch(this);
				this.consume();
			}
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public variableDeclaration(): VariableDeclarationContext {
		let _localctx: VariableDeclarationContext = new VariableDeclarationContext(this._ctx, this.state);
		this.enterRule(_localctx, 42, PredaParser.RULE_variableDeclaration);
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 333;
			this.typeName();
			this.state = 334;
			this.identifier();
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public typeNameOrAuto(): TypeNameOrAutoContext {
		let _localctx: TypeNameOrAutoContext = new TypeNameOrAutoContext(this._ctx, this.state);
		this.enterRule(_localctx, 44, PredaParser.RULE_typeNameOrAuto);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 337;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la === PredaParser.ConstantKeyword) {
				{
				this.state = 336;
				this.match(PredaParser.ConstantKeyword);
				}
			}

			this.state = 341;
			this._errHandler.sync(this);
			switch (this._input.LA(1)) {
			case PredaParser.T__11:
			case PredaParser.T__12:
			case PredaParser.T__13:
			case PredaParser.T__14:
			case PredaParser.T__15:
			case PredaParser.T__16:
			case PredaParser.T__19:
			case PredaParser.AddressKeyword:
			case PredaParser.FloatType:
			case PredaParser.IntType:
			case PredaParser.UintType:
			case PredaParser.Identifier:
				{
				this.state = 339;
				this.typeName();
				}
				break;
			case PredaParser.AutoKeyword:
				{
				this.state = 340;
				this.match(PredaParser.AutoKeyword);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public typeName(): TypeNameContext {
		let _localctx: TypeNameContext = new TypeNameContext(this._ctx, this.state);
		this.enterRule(_localctx, 46, PredaParser.RULE_typeName);
		try {
			this.state = 346;
			this._errHandler.sync(this);
			switch (this._input.LA(1)) {
			case PredaParser.T__11:
			case PredaParser.T__12:
			case PredaParser.T__13:
			case PredaParser.T__14:
			case PredaParser.T__15:
			case PredaParser.AddressKeyword:
			case PredaParser.FloatType:
			case PredaParser.IntType:
			case PredaParser.UintType:
				this.enterOuterAlt(_localctx, 1);
				{
				this.state = 343;
				this.fundamentalTypeName();
				}
				break;
			case PredaParser.T__16:
			case PredaParser.T__19:
				this.enterOuterAlt(_localctx, 2);
				{
				this.state = 344;
				this.builtInContainerTypeName();
				}
				break;
			case PredaParser.Identifier:
				this.enterOuterAlt(_localctx, 3);
				{
				this.state = 345;
				this.userDefinedTypeName();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public fundamentalTypeName(): FundamentalTypeNameContext {
		let _localctx: FundamentalTypeNameContext = new FundamentalTypeNameContext(this._ctx, this.state);
		this.enterRule(_localctx, 48, PredaParser.RULE_fundamentalTypeName);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 348;
			_la = this._input.LA(1);
			if (!((((_la) & ~0x1F) === 0 && ((1 << _la) & ((1 << PredaParser.T__11) | (1 << PredaParser.T__12) | (1 << PredaParser.T__13) | (1 << PredaParser.T__14) | (1 << PredaParser.T__15))) !== 0) || ((((_la - 68)) & ~0x1F) === 0 && ((1 << (_la - 68)) & ((1 << (PredaParser.AddressKeyword - 68)) | (1 << (PredaParser.FloatType - 68)) | (1 << (PredaParser.IntType - 68)) | (1 << (PredaParser.UintType - 68)))) !== 0))) {
			this._errHandler.recoverInline(this);
			} else {
				if (this._input.LA(1) === Token.EOF) {
					this.matchedEOF = true;
				}

				this._errHandler.reportMatch(this);
				this.consume();
			}
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public builtInContainerTypeName(): BuiltInContainerTypeNameContext {
		let _localctx: BuiltInContainerTypeNameContext = new BuiltInContainerTypeNameContext(this._ctx, this.state);
		this.enterRule(_localctx, 50, PredaParser.RULE_builtInContainerTypeName);
		try {
			this.state = 352;
			this._errHandler.sync(this);
			switch (this._input.LA(1)) {
			case PredaParser.T__16:
				this.enterOuterAlt(_localctx, 1);
				{
				this.state = 350;
				this.mapTypeName();
				}
				break;
			case PredaParser.T__19:
				this.enterOuterAlt(_localctx, 2);
				{
				this.state = 351;
				this.arrayTypeName();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public mapKeyTypeName(): MapKeyTypeNameContext {
		let _localctx: MapKeyTypeNameContext = new MapKeyTypeNameContext(this._ctx, this.state);
		this.enterRule(_localctx, 52, PredaParser.RULE_mapKeyTypeName);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 354;
			_la = this._input.LA(1);
			if (!((((_la) & ~0x1F) === 0 && ((1 << _la) & ((1 << PredaParser.T__11) | (1 << PredaParser.T__13) | (1 << PredaParser.T__14))) !== 0) || ((((_la - 68)) & ~0x1F) === 0 && ((1 << (_la - 68)) & ((1 << (PredaParser.AddressKeyword - 68)) | (1 << (PredaParser.FloatType - 68)) | (1 << (PredaParser.IntType - 68)) | (1 << (PredaParser.UintType - 68)))) !== 0))) {
			this._errHandler.recoverInline(this);
			} else {
				if (this._input.LA(1) === Token.EOF) {
					this.matchedEOF = true;
				}

				this._errHandler.reportMatch(this);
				this.consume();
			}
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public mapTypeName(): MapTypeNameContext {
		let _localctx: MapTypeNameContext = new MapTypeNameContext(this._ctx, this.state);
		this.enterRule(_localctx, 54, PredaParser.RULE_mapTypeName);
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 356;
			this.match(PredaParser.T__16);
			this.state = 357;
			this.match(PredaParser.T__17);
			this.state = 358;
			this.mapKeyTypeName();
			this.state = 359;
			this.match(PredaParser.T__3);
			this.state = 360;
			this.typeName();
			this.state = 361;
			this.match(PredaParser.T__18);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public arrayTypeName(): ArrayTypeNameContext {
		let _localctx: ArrayTypeNameContext = new ArrayTypeNameContext(this._ctx, this.state);
		this.enterRule(_localctx, 56, PredaParser.RULE_arrayTypeName);
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 363;
			this.match(PredaParser.T__19);
			this.state = 364;
			this.match(PredaParser.T__17);
			this.state = 365;
			this.typeName();
			this.state = 366;
			this.match(PredaParser.T__18);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public userDefinedTypeName(): UserDefinedTypeNameContext {
		let _localctx: UserDefinedTypeNameContext = new UserDefinedTypeNameContext(this._ctx, this.state);
		this.enterRule(_localctx, 58, PredaParser.RULE_userDefinedTypeName);
		try {
			let _alt: number;
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 373;
			this._errHandler.sync(this);
			_alt = this.interpreter.adaptivePredict(this._input, 40, this._ctx);
			while (_alt !== 2 && _alt !== ATN.INVALID_ALT_NUMBER) {
				if (_alt === 1) {
					{
					{
					this.state = 368;
					this.identifier();
					this.state = 369;
					this.match(PredaParser.T__0);
					}
					}
				}
				this.state = 375;
				this._errHandler.sync(this);
				_alt = this.interpreter.adaptivePredict(this._input, 40, this._ctx);
			}
			this.state = 376;
			this.identifier();
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public userBlockStatement(): UserBlockStatementContext {
		let _localctx: UserBlockStatementContext = new UserBlockStatementContext(this._ctx, this.state);
		this.enterRule(_localctx, 60, PredaParser.RULE_userBlockStatement);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 378;
			this.match(PredaParser.T__6);
			this.state = 382;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			while ((((_la) & ~0x1F) === 0 && ((1 << _la) & ((1 << PredaParser.T__6) | (1 << PredaParser.T__9) | (1 << PredaParser.T__11) | (1 << PredaParser.T__12) | (1 << PredaParser.T__13) | (1 << PredaParser.T__14) | (1 << PredaParser.T__15) | (1 << PredaParser.T__16) | (1 << PredaParser.T__19) | (1 << PredaParser.T__20) | (1 << PredaParser.T__22) | (1 << PredaParser.T__23) | (1 << PredaParser.T__24) | (1 << PredaParser.T__25) | (1 << PredaParser.T__26) | (1 << PredaParser.T__27) | (1 << PredaParser.T__28) | (1 << PredaParser.T__29) | (1 << PredaParser.T__30))) !== 0) || ((((_la - 58)) & ~0x1F) === 0 && ((1 << (_la - 58)) & ((1 << (PredaParser.BreakKeyword - 58)) | (1 << (PredaParser.ConstantKeyword - 58)) | (1 << (PredaParser.ContinueKeyword - 58)) | (1 << (PredaParser.RelayKeyword - 58)) | (1 << (PredaParser.IfKeyword - 58)) | (1 << (PredaParser.AddressKeyword - 58)) | (1 << (PredaParser.AutoKeyword - 58)) | (1 << (PredaParser.FloatType - 58)) | (1 << (PredaParser.IntType - 58)) | (1 << (PredaParser.UintType - 58)) | (1 << (PredaParser.BooleanLiteral - 58)) | (1 << (PredaParser.DecimalFloatLiteral - 58)) | (1 << (PredaParser.DecimalIntegerLiteral - 58)) | (1 << (PredaParser.AddressLiteral - 58)))) !== 0) || ((((_la - 90)) & ~0x1F) === 0 && ((1 << (_la - 90)) & ((1 << (PredaParser.HashLiteral - 90)) | (1 << (PredaParser.HexIntegerLiteral - 90)) | (1 << (PredaParser.DecimalBigIntegerLiteral - 90)) | (1 << (PredaParser.HexBigIntegerLiteral - 90)) | (1 << (PredaParser.Identifier - 90)) | (1 << (PredaParser.StringLiteral - 90)))) !== 0)) {
				{
				{
				this.state = 379;
				this.statement();
				}
				}
				this.state = 384;
				this._errHandler.sync(this);
				_la = this._input.LA(1);
			}
			this.state = 385;
			this.match(PredaParser.T__7);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public statement(): StatementContext {
		let _localctx: StatementContext = new StatementContext(this._ctx, this.state);
		this.enterRule(_localctx, 62, PredaParser.RULE_statement);
		try {
			this.state = 398;
			this._errHandler.sync(this);
			switch ( this.interpreter.adaptivePredict(this._input, 42, this._ctx) ) {
			case 1:
				this.enterOuterAlt(_localctx, 1);
				{
				this.state = 387;
				this.ifStatement();
				}
				break;

			case 2:
				this.enterOuterAlt(_localctx, 2);
				{
				this.state = 388;
				this.whileStatement();
				}
				break;

			case 3:
				this.enterOuterAlt(_localctx, 3);
				{
				this.state = 389;
				this.forStatement();
				}
				break;

			case 4:
				this.enterOuterAlt(_localctx, 4);
				{
				this.state = 390;
				this.userBlockStatement();
				}
				break;

			case 5:
				this.enterOuterAlt(_localctx, 5);
				{
				this.state = 391;
				this.doWhileStatement();
				}
				break;

			case 6:
				this.enterOuterAlt(_localctx, 6);
				{
				this.state = 392;
				this.continueStatement();
				}
				break;

			case 7:
				this.enterOuterAlt(_localctx, 7);
				{
				this.state = 393;
				this.breakStatement();
				}
				break;

			case 8:
				this.enterOuterAlt(_localctx, 8);
				{
				this.state = 394;
				this.returnStatement();
				}
				break;

			case 9:
				this.enterOuterAlt(_localctx, 9);
				{
				this.state = 395;
				this.relayStatement();
				}
				break;

			case 10:
				this.enterOuterAlt(_localctx, 10);
				{
				this.state = 396;
				this.variableDeclarationStatement();
				}
				break;

			case 11:
				this.enterOuterAlt(_localctx, 11);
				{
				this.state = 397;
				this.expressionStatement();
				}
				break;
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public expressionStatement(): ExpressionStatementContext {
		let _localctx: ExpressionStatementContext = new ExpressionStatementContext(this._ctx, this.state);
		this.enterRule(_localctx, 64, PredaParser.RULE_expressionStatement);
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 400;
			this.expression(0);
			this.state = 401;
			this.match(PredaParser.T__1);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public ifStatement(): IfStatementContext {
		let _localctx: IfStatementContext = new IfStatementContext(this._ctx, this.state);
		this.enterRule(_localctx, 66, PredaParser.RULE_ifStatement);
		let _la: number;
		try {
			let _alt: number;
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 403;
			this.ifWithBlock();
			this.state = 407;
			this._errHandler.sync(this);
			_alt = this.interpreter.adaptivePredict(this._input, 43, this._ctx);
			while (_alt !== 2 && _alt !== ATN.INVALID_ALT_NUMBER) {
				if (_alt === 1) {
					{
					{
					this.state = 404;
					this.elseIfWithBlock();
					}
					}
				}
				this.state = 409;
				this._errHandler.sync(this);
				_alt = this.interpreter.adaptivePredict(this._input, 43, this._ctx);
			}
			this.state = 411;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la === PredaParser.ElseKeyword) {
				{
				this.state = 410;
				this.elseWithBlock();
				}
			}

			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public ifWithBlock(): IfWithBlockContext {
		let _localctx: IfWithBlockContext = new IfWithBlockContext(this._ctx, this.state);
		this.enterRule(_localctx, 68, PredaParser.RULE_ifWithBlock);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 413;
			this.match(PredaParser.IfKeyword);
			this.state = 414;
			this.match(PredaParser.T__9);
			this.state = 415;
			this.expression(0);
			this.state = 416;
			this.match(PredaParser.T__10);
			this.state = 417;
			this.match(PredaParser.T__6);
			this.state = 421;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			while ((((_la) & ~0x1F) === 0 && ((1 << _la) & ((1 << PredaParser.T__6) | (1 << PredaParser.T__9) | (1 << PredaParser.T__11) | (1 << PredaParser.T__12) | (1 << PredaParser.T__13) | (1 << PredaParser.T__14) | (1 << PredaParser.T__15) | (1 << PredaParser.T__16) | (1 << PredaParser.T__19) | (1 << PredaParser.T__20) | (1 << PredaParser.T__22) | (1 << PredaParser.T__23) | (1 << PredaParser.T__24) | (1 << PredaParser.T__25) | (1 << PredaParser.T__26) | (1 << PredaParser.T__27) | (1 << PredaParser.T__28) | (1 << PredaParser.T__29) | (1 << PredaParser.T__30))) !== 0) || ((((_la - 58)) & ~0x1F) === 0 && ((1 << (_la - 58)) & ((1 << (PredaParser.BreakKeyword - 58)) | (1 << (PredaParser.ConstantKeyword - 58)) | (1 << (PredaParser.ContinueKeyword - 58)) | (1 << (PredaParser.RelayKeyword - 58)) | (1 << (PredaParser.IfKeyword - 58)) | (1 << (PredaParser.AddressKeyword - 58)) | (1 << (PredaParser.AutoKeyword - 58)) | (1 << (PredaParser.FloatType - 58)) | (1 << (PredaParser.IntType - 58)) | (1 << (PredaParser.UintType - 58)) | (1 << (PredaParser.BooleanLiteral - 58)) | (1 << (PredaParser.DecimalFloatLiteral - 58)) | (1 << (PredaParser.DecimalIntegerLiteral - 58)) | (1 << (PredaParser.AddressLiteral - 58)))) !== 0) || ((((_la - 90)) & ~0x1F) === 0 && ((1 << (_la - 90)) & ((1 << (PredaParser.HashLiteral - 90)) | (1 << (PredaParser.HexIntegerLiteral - 90)) | (1 << (PredaParser.DecimalBigIntegerLiteral - 90)) | (1 << (PredaParser.HexBigIntegerLiteral - 90)) | (1 << (PredaParser.Identifier - 90)) | (1 << (PredaParser.StringLiteral - 90)))) !== 0)) {
				{
				{
				this.state = 418;
				this.statement();
				}
				}
				this.state = 423;
				this._errHandler.sync(this);
				_la = this._input.LA(1);
			}
			this.state = 424;
			this.match(PredaParser.T__7);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public elseWithBlock(): ElseWithBlockContext {
		let _localctx: ElseWithBlockContext = new ElseWithBlockContext(this._ctx, this.state);
		this.enterRule(_localctx, 70, PredaParser.RULE_elseWithBlock);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 426;
			this.match(PredaParser.ElseKeyword);
			this.state = 427;
			this.match(PredaParser.T__6);
			this.state = 431;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			while ((((_la) & ~0x1F) === 0 && ((1 << _la) & ((1 << PredaParser.T__6) | (1 << PredaParser.T__9) | (1 << PredaParser.T__11) | (1 << PredaParser.T__12) | (1 << PredaParser.T__13) | (1 << PredaParser.T__14) | (1 << PredaParser.T__15) | (1 << PredaParser.T__16) | (1 << PredaParser.T__19) | (1 << PredaParser.T__20) | (1 << PredaParser.T__22) | (1 << PredaParser.T__23) | (1 << PredaParser.T__24) | (1 << PredaParser.T__25) | (1 << PredaParser.T__26) | (1 << PredaParser.T__27) | (1 << PredaParser.T__28) | (1 << PredaParser.T__29) | (1 << PredaParser.T__30))) !== 0) || ((((_la - 58)) & ~0x1F) === 0 && ((1 << (_la - 58)) & ((1 << (PredaParser.BreakKeyword - 58)) | (1 << (PredaParser.ConstantKeyword - 58)) | (1 << (PredaParser.ContinueKeyword - 58)) | (1 << (PredaParser.RelayKeyword - 58)) | (1 << (PredaParser.IfKeyword - 58)) | (1 << (PredaParser.AddressKeyword - 58)) | (1 << (PredaParser.AutoKeyword - 58)) | (1 << (PredaParser.FloatType - 58)) | (1 << (PredaParser.IntType - 58)) | (1 << (PredaParser.UintType - 58)) | (1 << (PredaParser.BooleanLiteral - 58)) | (1 << (PredaParser.DecimalFloatLiteral - 58)) | (1 << (PredaParser.DecimalIntegerLiteral - 58)) | (1 << (PredaParser.AddressLiteral - 58)))) !== 0) || ((((_la - 90)) & ~0x1F) === 0 && ((1 << (_la - 90)) & ((1 << (PredaParser.HashLiteral - 90)) | (1 << (PredaParser.HexIntegerLiteral - 90)) | (1 << (PredaParser.DecimalBigIntegerLiteral - 90)) | (1 << (PredaParser.HexBigIntegerLiteral - 90)) | (1 << (PredaParser.Identifier - 90)) | (1 << (PredaParser.StringLiteral - 90)))) !== 0)) {
				{
				{
				this.state = 428;
				this.statement();
				}
				}
				this.state = 433;
				this._errHandler.sync(this);
				_la = this._input.LA(1);
			}
			this.state = 434;
			this.match(PredaParser.T__7);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public elseIfWithBlock(): ElseIfWithBlockContext {
		let _localctx: ElseIfWithBlockContext = new ElseIfWithBlockContext(this._ctx, this.state);
		this.enterRule(_localctx, 72, PredaParser.RULE_elseIfWithBlock);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 436;
			this.match(PredaParser.ElseKeyword);
			this.state = 437;
			this.match(PredaParser.IfKeyword);
			this.state = 438;
			this.match(PredaParser.T__9);
			this.state = 439;
			this.expression(0);
			this.state = 440;
			this.match(PredaParser.T__10);
			this.state = 441;
			this.match(PredaParser.T__6);
			this.state = 445;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			while ((((_la) & ~0x1F) === 0 && ((1 << _la) & ((1 << PredaParser.T__6) | (1 << PredaParser.T__9) | (1 << PredaParser.T__11) | (1 << PredaParser.T__12) | (1 << PredaParser.T__13) | (1 << PredaParser.T__14) | (1 << PredaParser.T__15) | (1 << PredaParser.T__16) | (1 << PredaParser.T__19) | (1 << PredaParser.T__20) | (1 << PredaParser.T__22) | (1 << PredaParser.T__23) | (1 << PredaParser.T__24) | (1 << PredaParser.T__25) | (1 << PredaParser.T__26) | (1 << PredaParser.T__27) | (1 << PredaParser.T__28) | (1 << PredaParser.T__29) | (1 << PredaParser.T__30))) !== 0) || ((((_la - 58)) & ~0x1F) === 0 && ((1 << (_la - 58)) & ((1 << (PredaParser.BreakKeyword - 58)) | (1 << (PredaParser.ConstantKeyword - 58)) | (1 << (PredaParser.ContinueKeyword - 58)) | (1 << (PredaParser.RelayKeyword - 58)) | (1 << (PredaParser.IfKeyword - 58)) | (1 << (PredaParser.AddressKeyword - 58)) | (1 << (PredaParser.AutoKeyword - 58)) | (1 << (PredaParser.FloatType - 58)) | (1 << (PredaParser.IntType - 58)) | (1 << (PredaParser.UintType - 58)) | (1 << (PredaParser.BooleanLiteral - 58)) | (1 << (PredaParser.DecimalFloatLiteral - 58)) | (1 << (PredaParser.DecimalIntegerLiteral - 58)) | (1 << (PredaParser.AddressLiteral - 58)))) !== 0) || ((((_la - 90)) & ~0x1F) === 0 && ((1 << (_la - 90)) & ((1 << (PredaParser.HashLiteral - 90)) | (1 << (PredaParser.HexIntegerLiteral - 90)) | (1 << (PredaParser.DecimalBigIntegerLiteral - 90)) | (1 << (PredaParser.HexBigIntegerLiteral - 90)) | (1 << (PredaParser.Identifier - 90)) | (1 << (PredaParser.StringLiteral - 90)))) !== 0)) {
				{
				{
				this.state = 442;
				this.statement();
				}
				}
				this.state = 447;
				this._errHandler.sync(this);
				_la = this._input.LA(1);
			}
			this.state = 448;
			this.match(PredaParser.T__7);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public whileStatement(): WhileStatementContext {
		let _localctx: WhileStatementContext = new WhileStatementContext(this._ctx, this.state);
		this.enterRule(_localctx, 74, PredaParser.RULE_whileStatement);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 450;
			this.match(PredaParser.T__20);
			this.state = 451;
			this.match(PredaParser.T__9);
			this.state = 452;
			this.expression(0);
			this.state = 453;
			this.match(PredaParser.T__10);
			this.state = 454;
			this.match(PredaParser.T__6);
			this.state = 458;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			while ((((_la) & ~0x1F) === 0 && ((1 << _la) & ((1 << PredaParser.T__6) | (1 << PredaParser.T__9) | (1 << PredaParser.T__11) | (1 << PredaParser.T__12) | (1 << PredaParser.T__13) | (1 << PredaParser.T__14) | (1 << PredaParser.T__15) | (1 << PredaParser.T__16) | (1 << PredaParser.T__19) | (1 << PredaParser.T__20) | (1 << PredaParser.T__22) | (1 << PredaParser.T__23) | (1 << PredaParser.T__24) | (1 << PredaParser.T__25) | (1 << PredaParser.T__26) | (1 << PredaParser.T__27) | (1 << PredaParser.T__28) | (1 << PredaParser.T__29) | (1 << PredaParser.T__30))) !== 0) || ((((_la - 58)) & ~0x1F) === 0 && ((1 << (_la - 58)) & ((1 << (PredaParser.BreakKeyword - 58)) | (1 << (PredaParser.ConstantKeyword - 58)) | (1 << (PredaParser.ContinueKeyword - 58)) | (1 << (PredaParser.RelayKeyword - 58)) | (1 << (PredaParser.IfKeyword - 58)) | (1 << (PredaParser.AddressKeyword - 58)) | (1 << (PredaParser.AutoKeyword - 58)) | (1 << (PredaParser.FloatType - 58)) | (1 << (PredaParser.IntType - 58)) | (1 << (PredaParser.UintType - 58)) | (1 << (PredaParser.BooleanLiteral - 58)) | (1 << (PredaParser.DecimalFloatLiteral - 58)) | (1 << (PredaParser.DecimalIntegerLiteral - 58)) | (1 << (PredaParser.AddressLiteral - 58)))) !== 0) || ((((_la - 90)) & ~0x1F) === 0 && ((1 << (_la - 90)) & ((1 << (PredaParser.HashLiteral - 90)) | (1 << (PredaParser.HexIntegerLiteral - 90)) | (1 << (PredaParser.DecimalBigIntegerLiteral - 90)) | (1 << (PredaParser.HexBigIntegerLiteral - 90)) | (1 << (PredaParser.Identifier - 90)) | (1 << (PredaParser.StringLiteral - 90)))) !== 0)) {
				{
				{
				this.state = 455;
				this.statement();
				}
				}
				this.state = 460;
				this._errHandler.sync(this);
				_la = this._input.LA(1);
			}
			this.state = 461;
			this.match(PredaParser.T__7);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public relayStatement(): RelayStatementContext {
		let _localctx: RelayStatementContext = new RelayStatementContext(this._ctx, this.state);
		this.enterRule(_localctx, 76, PredaParser.RULE_relayStatement);
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 463;
			this.match(PredaParser.RelayKeyword);
			this.state = 464;
			this.match(PredaParser.T__8);
			this.state = 465;
			this.relayType();
			this.state = 473;
			this._errHandler.sync(this);
			switch (this._input.LA(1)) {
			case PredaParser.Identifier:
				{
				{
				this.state = 466;
				this.identifier();
				this.state = 467;
				this.match(PredaParser.T__9);
				this.state = 468;
				this.functionCallArguments();
				this.state = 469;
				this.match(PredaParser.T__10);
				this.state = 470;
				this.match(PredaParser.T__1);
				}
				}
				break;
			case PredaParser.T__9:
				{
				this.state = 472;
				this.relayLambdaDefinition();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public relayType(): RelayTypeContext {
		let _localctx: RelayTypeContext = new RelayTypeContext(this._ctx, this.state);
		this.enterRule(_localctx, 78, PredaParser.RULE_relayType);
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 478;
			this._errHandler.sync(this);
			switch (this._input.LA(1)) {
			case PredaParser.T__9:
			case PredaParser.T__11:
			case PredaParser.T__12:
			case PredaParser.T__13:
			case PredaParser.T__14:
			case PredaParser.T__15:
			case PredaParser.T__16:
			case PredaParser.T__19:
			case PredaParser.T__25:
			case PredaParser.T__26:
			case PredaParser.T__27:
			case PredaParser.T__28:
			case PredaParser.T__29:
			case PredaParser.T__30:
			case PredaParser.AddressKeyword:
			case PredaParser.FloatType:
			case PredaParser.IntType:
			case PredaParser.UintType:
			case PredaParser.BooleanLiteral:
			case PredaParser.DecimalFloatLiteral:
			case PredaParser.DecimalIntegerLiteral:
			case PredaParser.AddressLiteral:
			case PredaParser.HashLiteral:
			case PredaParser.HexIntegerLiteral:
			case PredaParser.DecimalBigIntegerLiteral:
			case PredaParser.HexBigIntegerLiteral:
			case PredaParser.Identifier:
			case PredaParser.StringLiteral:
				{
				this.state = 475;
				this.expression(0);
				}
				break;
			case PredaParser.ShardsKeyword:
				{
				this.state = 476;
				this.match(PredaParser.ShardsKeyword);
				}
				break;
			case PredaParser.GlobalKeyword:
				{
				this.state = 477;
				this.match(PredaParser.GlobalKeyword);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public relayLambdaDefinition(): RelayLambdaDefinitionContext {
		let _localctx: RelayLambdaDefinitionContext = new RelayLambdaDefinitionContext(this._ctx, this.state);
		this.enterRule(_localctx, 80, PredaParser.RULE_relayLambdaDefinition);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 480;
			this.match(PredaParser.T__9);
			this.state = 489;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if ((((_la) & ~0x1F) === 0 && ((1 << _la) & ((1 << PredaParser.T__11) | (1 << PredaParser.T__12) | (1 << PredaParser.T__13) | (1 << PredaParser.T__14) | (1 << PredaParser.T__15) | (1 << PredaParser.T__16) | (1 << PredaParser.T__19) | (1 << PredaParser.T__21))) !== 0) || ((((_la - 59)) & ~0x1F) === 0 && ((1 << (_la - 59)) & ((1 << (PredaParser.ConstantKeyword - 59)) | (1 << (PredaParser.AddressKeyword - 59)) | (1 << (PredaParser.AutoKeyword - 59)) | (1 << (PredaParser.FloatType - 59)) | (1 << (PredaParser.IntType - 59)) | (1 << (PredaParser.UintType - 59)))) !== 0) || _la === PredaParser.Identifier) {
				{
				this.state = 481;
				this.relayLambdaParameter();
				this.state = 486;
				this._errHandler.sync(this);
				_la = this._input.LA(1);
				while (_la === PredaParser.T__3) {
					{
					{
					this.state = 482;
					this.match(PredaParser.T__3);
					this.state = 483;
					this.relayLambdaParameter();
					}
					}
					this.state = 488;
					this._errHandler.sync(this);
					_la = this._input.LA(1);
				}
				}
			}

			this.state = 491;
			this.match(PredaParser.T__10);
			this.state = 493;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la === PredaParser.ConstantKeyword) {
				{
				this.state = 492;
				this.match(PredaParser.ConstantKeyword);
				}
			}

			this.state = 495;
			this.match(PredaParser.T__6);
			this.state = 499;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			while ((((_la) & ~0x1F) === 0 && ((1 << _la) & ((1 << PredaParser.T__6) | (1 << PredaParser.T__9) | (1 << PredaParser.T__11) | (1 << PredaParser.T__12) | (1 << PredaParser.T__13) | (1 << PredaParser.T__14) | (1 << PredaParser.T__15) | (1 << PredaParser.T__16) | (1 << PredaParser.T__19) | (1 << PredaParser.T__20) | (1 << PredaParser.T__22) | (1 << PredaParser.T__23) | (1 << PredaParser.T__24) | (1 << PredaParser.T__25) | (1 << PredaParser.T__26) | (1 << PredaParser.T__27) | (1 << PredaParser.T__28) | (1 << PredaParser.T__29) | (1 << PredaParser.T__30))) !== 0) || ((((_la - 58)) & ~0x1F) === 0 && ((1 << (_la - 58)) & ((1 << (PredaParser.BreakKeyword - 58)) | (1 << (PredaParser.ConstantKeyword - 58)) | (1 << (PredaParser.ContinueKeyword - 58)) | (1 << (PredaParser.RelayKeyword - 58)) | (1 << (PredaParser.IfKeyword - 58)) | (1 << (PredaParser.AddressKeyword - 58)) | (1 << (PredaParser.AutoKeyword - 58)) | (1 << (PredaParser.FloatType - 58)) | (1 << (PredaParser.IntType - 58)) | (1 << (PredaParser.UintType - 58)) | (1 << (PredaParser.BooleanLiteral - 58)) | (1 << (PredaParser.DecimalFloatLiteral - 58)) | (1 << (PredaParser.DecimalIntegerLiteral - 58)) | (1 << (PredaParser.AddressLiteral - 58)))) !== 0) || ((((_la - 90)) & ~0x1F) === 0 && ((1 << (_la - 90)) & ((1 << (PredaParser.HashLiteral - 90)) | (1 << (PredaParser.HexIntegerLiteral - 90)) | (1 << (PredaParser.DecimalBigIntegerLiteral - 90)) | (1 << (PredaParser.HexBigIntegerLiteral - 90)) | (1 << (PredaParser.Identifier - 90)) | (1 << (PredaParser.StringLiteral - 90)))) !== 0)) {
				{
				{
				this.state = 496;
				this.statement();
				}
				}
				this.state = 501;
				this._errHandler.sync(this);
				_la = this._input.LA(1);
			}
			this.state = 502;
			this.match(PredaParser.T__7);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public relayLambdaParameter(): RelayLambdaParameterContext {
		let _localctx: RelayLambdaParameterContext = new RelayLambdaParameterContext(this._ctx, this.state);
		this.enterRule(_localctx, 82, PredaParser.RULE_relayLambdaParameter);
		try {
			this.state = 511;
			this._errHandler.sync(this);
			switch (this._input.LA(1)) {
			case PredaParser.T__11:
			case PredaParser.T__12:
			case PredaParser.T__13:
			case PredaParser.T__14:
			case PredaParser.T__15:
			case PredaParser.T__16:
			case PredaParser.T__19:
			case PredaParser.ConstantKeyword:
			case PredaParser.AddressKeyword:
			case PredaParser.AutoKeyword:
			case PredaParser.FloatType:
			case PredaParser.IntType:
			case PredaParser.UintType:
			case PredaParser.Identifier:
				this.enterOuterAlt(_localctx, 1);
				{
				{
				this.state = 504;
				this.typeNameOrAuto();
				this.state = 505;
				this.identifier();
				this.state = 506;
				this.match(PredaParser.T__5);
				this.state = 507;
				this.expression(0);
				}
				}
				break;
			case PredaParser.T__21:
				this.enterOuterAlt(_localctx, 2);
				{
				{
				this.state = 509;
				this.match(PredaParser.T__21);
				this.state = 510;
				this.identifier();
				}
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public forStatement(): ForStatementContext {
		let _localctx: ForStatementContext = new ForStatementContext(this._ctx, this.state);
		this.enterRule(_localctx, 84, PredaParser.RULE_forStatement);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 513;
			this.match(PredaParser.T__22);
			this.state = 514;
			this.match(PredaParser.T__9);
			this.state = 517;
			this._errHandler.sync(this);
			switch ( this.interpreter.adaptivePredict(this._input, 56, this._ctx) ) {
			case 1:
				{
				this.state = 515;
				this.localVariableDeclaration();
				}
				break;

			case 2:
				{
				this.state = 516;
				_localctx._firstExpression = this.expression(0);
				}
				break;
			}
			this.state = 519;
			this.match(PredaParser.T__1);
			this.state = 521;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if ((((_la) & ~0x1F) === 0 && ((1 << _la) & ((1 << PredaParser.T__9) | (1 << PredaParser.T__11) | (1 << PredaParser.T__12) | (1 << PredaParser.T__13) | (1 << PredaParser.T__14) | (1 << PredaParser.T__15) | (1 << PredaParser.T__16) | (1 << PredaParser.T__19) | (1 << PredaParser.T__25) | (1 << PredaParser.T__26) | (1 << PredaParser.T__27) | (1 << PredaParser.T__28) | (1 << PredaParser.T__29) | (1 << PredaParser.T__30))) !== 0) || ((((_la - 68)) & ~0x1F) === 0 && ((1 << (_la - 68)) & ((1 << (PredaParser.AddressKeyword - 68)) | (1 << (PredaParser.FloatType - 68)) | (1 << (PredaParser.IntType - 68)) | (1 << (PredaParser.UintType - 68)) | (1 << (PredaParser.BooleanLiteral - 68)) | (1 << (PredaParser.DecimalFloatLiteral - 68)) | (1 << (PredaParser.DecimalIntegerLiteral - 68)) | (1 << (PredaParser.AddressLiteral - 68)) | (1 << (PredaParser.HashLiteral - 68)) | (1 << (PredaParser.HexIntegerLiteral - 68)) | (1 << (PredaParser.DecimalBigIntegerLiteral - 68)) | (1 << (PredaParser.HexBigIntegerLiteral - 68)) | (1 << (PredaParser.Identifier - 68)) | (1 << (PredaParser.StringLiteral - 68)))) !== 0)) {
				{
				this.state = 520;
				_localctx._secondExpression = this.expression(0);
				}
			}

			this.state = 523;
			this.match(PredaParser.T__1);
			this.state = 525;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if ((((_la) & ~0x1F) === 0 && ((1 << _la) & ((1 << PredaParser.T__9) | (1 << PredaParser.T__11) | (1 << PredaParser.T__12) | (1 << PredaParser.T__13) | (1 << PredaParser.T__14) | (1 << PredaParser.T__15) | (1 << PredaParser.T__16) | (1 << PredaParser.T__19) | (1 << PredaParser.T__25) | (1 << PredaParser.T__26) | (1 << PredaParser.T__27) | (1 << PredaParser.T__28) | (1 << PredaParser.T__29) | (1 << PredaParser.T__30))) !== 0) || ((((_la - 68)) & ~0x1F) === 0 && ((1 << (_la - 68)) & ((1 << (PredaParser.AddressKeyword - 68)) | (1 << (PredaParser.FloatType - 68)) | (1 << (PredaParser.IntType - 68)) | (1 << (PredaParser.UintType - 68)) | (1 << (PredaParser.BooleanLiteral - 68)) | (1 << (PredaParser.DecimalFloatLiteral - 68)) | (1 << (PredaParser.DecimalIntegerLiteral - 68)) | (1 << (PredaParser.AddressLiteral - 68)) | (1 << (PredaParser.HashLiteral - 68)) | (1 << (PredaParser.HexIntegerLiteral - 68)) | (1 << (PredaParser.DecimalBigIntegerLiteral - 68)) | (1 << (PredaParser.HexBigIntegerLiteral - 68)) | (1 << (PredaParser.Identifier - 68)) | (1 << (PredaParser.StringLiteral - 68)))) !== 0)) {
				{
				this.state = 524;
				_localctx._thirdExpression = this.expression(0);
				}
			}

			this.state = 527;
			this.match(PredaParser.T__10);
			this.state = 528;
			this.match(PredaParser.T__6);
			this.state = 532;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			while ((((_la) & ~0x1F) === 0 && ((1 << _la) & ((1 << PredaParser.T__6) | (1 << PredaParser.T__9) | (1 << PredaParser.T__11) | (1 << PredaParser.T__12) | (1 << PredaParser.T__13) | (1 << PredaParser.T__14) | (1 << PredaParser.T__15) | (1 << PredaParser.T__16) | (1 << PredaParser.T__19) | (1 << PredaParser.T__20) | (1 << PredaParser.T__22) | (1 << PredaParser.T__23) | (1 << PredaParser.T__24) | (1 << PredaParser.T__25) | (1 << PredaParser.T__26) | (1 << PredaParser.T__27) | (1 << PredaParser.T__28) | (1 << PredaParser.T__29) | (1 << PredaParser.T__30))) !== 0) || ((((_la - 58)) & ~0x1F) === 0 && ((1 << (_la - 58)) & ((1 << (PredaParser.BreakKeyword - 58)) | (1 << (PredaParser.ConstantKeyword - 58)) | (1 << (PredaParser.ContinueKeyword - 58)) | (1 << (PredaParser.RelayKeyword - 58)) | (1 << (PredaParser.IfKeyword - 58)) | (1 << (PredaParser.AddressKeyword - 58)) | (1 << (PredaParser.AutoKeyword - 58)) | (1 << (PredaParser.FloatType - 58)) | (1 << (PredaParser.IntType - 58)) | (1 << (PredaParser.UintType - 58)) | (1 << (PredaParser.BooleanLiteral - 58)) | (1 << (PredaParser.DecimalFloatLiteral - 58)) | (1 << (PredaParser.DecimalIntegerLiteral - 58)) | (1 << (PredaParser.AddressLiteral - 58)))) !== 0) || ((((_la - 90)) & ~0x1F) === 0 && ((1 << (_la - 90)) & ((1 << (PredaParser.HashLiteral - 90)) | (1 << (PredaParser.HexIntegerLiteral - 90)) | (1 << (PredaParser.DecimalBigIntegerLiteral - 90)) | (1 << (PredaParser.HexBigIntegerLiteral - 90)) | (1 << (PredaParser.Identifier - 90)) | (1 << (PredaParser.StringLiteral - 90)))) !== 0)) {
				{
				{
				this.state = 529;
				this.statement();
				}
				}
				this.state = 534;
				this._errHandler.sync(this);
				_la = this._input.LA(1);
			}
			this.state = 535;
			this.match(PredaParser.T__7);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public doWhileStatement(): DoWhileStatementContext {
		let _localctx: DoWhileStatementContext = new DoWhileStatementContext(this._ctx, this.state);
		this.enterRule(_localctx, 86, PredaParser.RULE_doWhileStatement);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 537;
			this.match(PredaParser.T__23);
			this.state = 538;
			this.match(PredaParser.T__6);
			this.state = 542;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			while ((((_la) & ~0x1F) === 0 && ((1 << _la) & ((1 << PredaParser.T__6) | (1 << PredaParser.T__9) | (1 << PredaParser.T__11) | (1 << PredaParser.T__12) | (1 << PredaParser.T__13) | (1 << PredaParser.T__14) | (1 << PredaParser.T__15) | (1 << PredaParser.T__16) | (1 << PredaParser.T__19) | (1 << PredaParser.T__20) | (1 << PredaParser.T__22) | (1 << PredaParser.T__23) | (1 << PredaParser.T__24) | (1 << PredaParser.T__25) | (1 << PredaParser.T__26) | (1 << PredaParser.T__27) | (1 << PredaParser.T__28) | (1 << PredaParser.T__29) | (1 << PredaParser.T__30))) !== 0) || ((((_la - 58)) & ~0x1F) === 0 && ((1 << (_la - 58)) & ((1 << (PredaParser.BreakKeyword - 58)) | (1 << (PredaParser.ConstantKeyword - 58)) | (1 << (PredaParser.ContinueKeyword - 58)) | (1 << (PredaParser.RelayKeyword - 58)) | (1 << (PredaParser.IfKeyword - 58)) | (1 << (PredaParser.AddressKeyword - 58)) | (1 << (PredaParser.AutoKeyword - 58)) | (1 << (PredaParser.FloatType - 58)) | (1 << (PredaParser.IntType - 58)) | (1 << (PredaParser.UintType - 58)) | (1 << (PredaParser.BooleanLiteral - 58)) | (1 << (PredaParser.DecimalFloatLiteral - 58)) | (1 << (PredaParser.DecimalIntegerLiteral - 58)) | (1 << (PredaParser.AddressLiteral - 58)))) !== 0) || ((((_la - 90)) & ~0x1F) === 0 && ((1 << (_la - 90)) & ((1 << (PredaParser.HashLiteral - 90)) | (1 << (PredaParser.HexIntegerLiteral - 90)) | (1 << (PredaParser.DecimalBigIntegerLiteral - 90)) | (1 << (PredaParser.HexBigIntegerLiteral - 90)) | (1 << (PredaParser.Identifier - 90)) | (1 << (PredaParser.StringLiteral - 90)))) !== 0)) {
				{
				{
				this.state = 539;
				this.statement();
				}
				}
				this.state = 544;
				this._errHandler.sync(this);
				_la = this._input.LA(1);
			}
			this.state = 545;
			this.match(PredaParser.T__7);
			this.state = 546;
			this.match(PredaParser.T__20);
			this.state = 547;
			this.match(PredaParser.T__9);
			this.state = 548;
			this.expression(0);
			this.state = 549;
			this.match(PredaParser.T__10);
			this.state = 550;
			this.match(PredaParser.T__1);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public continueStatement(): ContinueStatementContext {
		let _localctx: ContinueStatementContext = new ContinueStatementContext(this._ctx, this.state);
		this.enterRule(_localctx, 88, PredaParser.RULE_continueStatement);
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 552;
			this.match(PredaParser.ContinueKeyword);
			this.state = 553;
			this.match(PredaParser.T__1);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public breakStatement(): BreakStatementContext {
		let _localctx: BreakStatementContext = new BreakStatementContext(this._ctx, this.state);
		this.enterRule(_localctx, 90, PredaParser.RULE_breakStatement);
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 555;
			this.match(PredaParser.BreakKeyword);
			this.state = 556;
			this.match(PredaParser.T__1);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public returnStatement(): ReturnStatementContext {
		let _localctx: ReturnStatementContext = new ReturnStatementContext(this._ctx, this.state);
		this.enterRule(_localctx, 92, PredaParser.RULE_returnStatement);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 558;
			this.match(PredaParser.T__24);
			this.state = 560;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if ((((_la) & ~0x1F) === 0 && ((1 << _la) & ((1 << PredaParser.T__9) | (1 << PredaParser.T__11) | (1 << PredaParser.T__12) | (1 << PredaParser.T__13) | (1 << PredaParser.T__14) | (1 << PredaParser.T__15) | (1 << PredaParser.T__16) | (1 << PredaParser.T__19) | (1 << PredaParser.T__25) | (1 << PredaParser.T__26) | (1 << PredaParser.T__27) | (1 << PredaParser.T__28) | (1 << PredaParser.T__29) | (1 << PredaParser.T__30))) !== 0) || ((((_la - 68)) & ~0x1F) === 0 && ((1 << (_la - 68)) & ((1 << (PredaParser.AddressKeyword - 68)) | (1 << (PredaParser.FloatType - 68)) | (1 << (PredaParser.IntType - 68)) | (1 << (PredaParser.UintType - 68)) | (1 << (PredaParser.BooleanLiteral - 68)) | (1 << (PredaParser.DecimalFloatLiteral - 68)) | (1 << (PredaParser.DecimalIntegerLiteral - 68)) | (1 << (PredaParser.AddressLiteral - 68)) | (1 << (PredaParser.HashLiteral - 68)) | (1 << (PredaParser.HexIntegerLiteral - 68)) | (1 << (PredaParser.DecimalBigIntegerLiteral - 68)) | (1 << (PredaParser.HexBigIntegerLiteral - 68)) | (1 << (PredaParser.Identifier - 68)) | (1 << (PredaParser.StringLiteral - 68)))) !== 0)) {
				{
				this.state = 559;
				this.expression(0);
				}
			}

			this.state = 562;
			this.match(PredaParser.T__1);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public variableDeclarationStatement(): VariableDeclarationStatementContext {
		let _localctx: VariableDeclarationStatementContext = new VariableDeclarationStatementContext(this._ctx, this.state);
		this.enterRule(_localctx, 94, PredaParser.RULE_variableDeclarationStatement);
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 564;
			this.localVariableDeclaration();
			this.state = 565;
			this.match(PredaParser.T__1);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public localVariableDeclaration(): LocalVariableDeclarationContext {
		let _localctx: LocalVariableDeclarationContext = new LocalVariableDeclarationContext(this._ctx, this.state);
		this.enterRule(_localctx, 96, PredaParser.RULE_localVariableDeclaration);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 567;
			this.typeNameOrAuto();
			this.state = 568;
			this.identifier();
			this.state = 571;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if (_la === PredaParser.T__5) {
				{
				this.state = 569;
				this.match(PredaParser.T__5);
				this.state = 570;
				this.expression(0);
				}
			}

			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}

	public expression(): ExpressionContext;
	public expression(_p: number): ExpressionContext;
	// @RuleVersion(0)
	public expression(_p?: number): ExpressionContext {
		if (_p === undefined) {
			_p = 0;
		}

		let _parentctx: ParserRuleContext = this._ctx;
		let _parentState: number = this.state;
		let _localctx: ExpressionContext = new ExpressionContext(this._ctx, _parentState);
		let _prevctx: ExpressionContext = _localctx;
		let _startState: number = 98;
		this.enterRecursionRule(_localctx, 98, PredaParser.RULE_expression, _p);
		try {
			let _alt: number;
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 606;
			this._errHandler.sync(this);
			switch (this._input.LA(1)) {
			case PredaParser.T__9:
				{
				this.state = 574;
				this.match(PredaParser.T__9);
				this.state = 575;
				this.expression(0);
				this.state = 576;
				this.match(PredaParser.T__10);
				_localctx.expressionType =  5;
				}
				break;
			case PredaParser.T__25:
				{
				this.state = 579;
				this.match(PredaParser.T__25);
				this.state = 580;
				this.expression(37);
				_localctx.expressionType =  6;
				}
				break;
			case PredaParser.T__26:
				{
				this.state = 583;
				this.match(PredaParser.T__26);
				this.state = 584;
				this.expression(36);
				_localctx.expressionType =  7;
				}
				break;
			case PredaParser.T__27:
				{
				this.state = 587;
				this.match(PredaParser.T__27);
				this.state = 588;
				this.expression(35);
				_localctx.expressionType =  8;
				}
				break;
			case PredaParser.T__28:
				{
				this.state = 591;
				this.match(PredaParser.T__28);
				this.state = 592;
				this.expression(34);
				_localctx.expressionType =  9;
				}
				break;
			case PredaParser.T__29:
				{
				this.state = 595;
				this.match(PredaParser.T__29);
				this.state = 596;
				this.expression(33);
				_localctx.expressionType =  10;
				}
				break;
			case PredaParser.T__30:
				{
				this.state = 599;
				this.match(PredaParser.T__30);
				this.state = 600;
				this.expression(32);
				_localctx.expressionType =  11;
				}
				break;
			case PredaParser.T__11:
			case PredaParser.T__12:
			case PredaParser.T__13:
			case PredaParser.T__14:
			case PredaParser.T__15:
			case PredaParser.T__16:
			case PredaParser.T__19:
			case PredaParser.AddressKeyword:
			case PredaParser.FloatType:
			case PredaParser.IntType:
			case PredaParser.UintType:
			case PredaParser.BooleanLiteral:
			case PredaParser.DecimalFloatLiteral:
			case PredaParser.DecimalIntegerLiteral:
			case PredaParser.AddressLiteral:
			case PredaParser.HashLiteral:
			case PredaParser.HexIntegerLiteral:
			case PredaParser.DecimalBigIntegerLiteral:
			case PredaParser.HexBigIntegerLiteral:
			case PredaParser.Identifier:
			case PredaParser.StringLiteral:
				{
				this.state = 603;
				this.primaryExpression();
				_localctx.expressionType =  42;
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			this._ctx._stop = this._input.tryLT(-1);
			this.state = 786;
			this._errHandler.sync(this);
			_alt = this.interpreter.adaptivePredict(this._input, 65, this._ctx);
			while (_alt !== 2 && _alt !== ATN.INVALID_ALT_NUMBER) {
				if (_alt === 1) {
					if (this._parseListeners != null) {
						this.triggerExitRuleEvent();
					}
					_prevctx = _localctx;
					{
					this.state = 784;
					this._errHandler.sync(this);
					switch ( this.interpreter.adaptivePredict(this._input, 64, this._ctx) ) {
					case 1:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 608;
						if (!(this.precpred(this._ctx, 31))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 31)");
						}
						this.state = 609;
						this.match(PredaParser.T__31);
						this.state = 610;
						this.expression(32);
						_localctx.expressionType =  12;
						}
						break;

					case 2:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 613;
						if (!(this.precpred(this._ctx, 30))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 30)");
						}
						this.state = 614;
						this.match(PredaParser.T__32);
						this.state = 615;
						this.expression(31);
						_localctx.expressionType =  13;
						}
						break;

					case 3:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 618;
						if (!(this.precpred(this._ctx, 29))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 29)");
						}
						this.state = 619;
						this.match(PredaParser.T__33);
						this.state = 620;
						this.expression(30);
						_localctx.expressionType =  14;
						}
						break;

					case 4:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 623;
						if (!(this.precpred(this._ctx, 28))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 28)");
						}
						this.state = 624;
						this.match(PredaParser.T__27);
						this.state = 625;
						this.expression(29);
						_localctx.expressionType =  15;
						}
						break;

					case 5:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 628;
						if (!(this.precpred(this._ctx, 27))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 27)");
						}
						this.state = 629;
						this.match(PredaParser.T__28);
						this.state = 630;
						this.expression(28);
						_localctx.expressionType =  16;
						}
						break;

					case 6:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 633;
						if (!(this.precpred(this._ctx, 26))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 26)");
						}
						this.state = 634;
						this.match(PredaParser.T__34);
						this.state = 635;
						this.expression(27);
						_localctx.expressionType =  17;
						}
						break;

					case 7:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 638;
						if (!(this.precpred(this._ctx, 25))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 25)");
						}
						this.state = 639;
						this.match(PredaParser.T__18);
						this.state = 640;
						this.match(PredaParser.T__18);
						this.state = 641;
						this.expression(26);
						_localctx.expressionType =  18;
						}
						break;

					case 8:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 644;
						if (!(this.precpred(this._ctx, 24))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 24)");
						}
						this.state = 645;
						this.match(PredaParser.T__17);
						this.state = 646;
						this.expression(25);
						_localctx.expressionType =  19;
						}
						break;

					case 9:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 649;
						if (!(this.precpred(this._ctx, 23))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 23)");
						}
						this.state = 650;
						this.match(PredaParser.T__18);
						this.state = 651;
						this.expression(24);
						_localctx.expressionType =  20;
						}
						break;

					case 10:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 654;
						if (!(this.precpred(this._ctx, 22))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 22)");
						}
						this.state = 655;
						this.match(PredaParser.T__35);
						this.state = 656;
						this.expression(23);
						_localctx.expressionType =  21;
						}
						break;

					case 11:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 659;
						if (!(this.precpred(this._ctx, 21))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 21)");
						}
						this.state = 660;
						this.match(PredaParser.T__36);
						this.state = 661;
						this.expression(22);
						_localctx.expressionType =  22;
						}
						break;

					case 12:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 664;
						if (!(this.precpred(this._ctx, 20))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 20)");
						}
						this.state = 665;
						this.match(PredaParser.T__37);
						this.state = 666;
						this.expression(21);
						_localctx.expressionType =  23;
						}
						break;

					case 13:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 669;
						if (!(this.precpred(this._ctx, 19))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 19)");
						}
						this.state = 670;
						this.match(PredaParser.T__38);
						this.state = 671;
						this.expression(20);
						_localctx.expressionType =  24;
						}
						break;

					case 14:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 674;
						if (!(this.precpred(this._ctx, 18))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 18)");
						}
						this.state = 675;
						this.match(PredaParser.T__39);
						this.state = 676;
						this.expression(19);
						_localctx.expressionType =  25;
						}
						break;

					case 15:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 679;
						if (!(this.precpred(this._ctx, 17))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 17)");
						}
						this.state = 680;
						this.match(PredaParser.T__21);
						this.state = 681;
						this.expression(18);
						_localctx.expressionType =  26;
						}
						break;

					case 16:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 684;
						if (!(this.precpred(this._ctx, 16))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 16)");
						}
						this.state = 685;
						this.match(PredaParser.T__40);
						this.state = 686;
						this.expression(17);
						_localctx.expressionType =  27;
						}
						break;

					case 17:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 689;
						if (!(this.precpred(this._ctx, 15))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 15)");
						}
						this.state = 690;
						this.match(PredaParser.T__41);
						this.state = 691;
						this.expression(16);
						_localctx.expressionType =  28;
						}
						break;

					case 18:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 694;
						if (!(this.precpred(this._ctx, 14))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 14)");
						}
						this.state = 695;
						this.match(PredaParser.T__42);
						this.state = 696;
						this.expression(15);
						_localctx.expressionType =  29;
						}
						break;

					case 19:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 699;
						if (!(this.precpred(this._ctx, 13))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 13)");
						}
						this.state = 700;
						this.match(PredaParser.T__43);
						this.state = 701;
						this.expression(0);
						this.state = 702;
						this.match(PredaParser.T__44);
						this.state = 703;
						this.expression(14);
						_localctx.expressionType =  30;
						}
						break;

					case 20:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 706;
						if (!(this.precpred(this._ctx, 12))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 12)");
						}
						this.state = 707;
						this.match(PredaParser.T__5);
						this.state = 708;
						this.expression(13);
						_localctx.expressionType =  31;
						}
						break;

					case 21:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 711;
						if (!(this.precpred(this._ctx, 11))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 11)");
						}
						this.state = 712;
						this.match(PredaParser.T__45);
						this.state = 713;
						this.expression(12);
						_localctx.expressionType =  32;
						}
						break;

					case 22:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 716;
						if (!(this.precpred(this._ctx, 10))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 10)");
						}
						this.state = 717;
						this.match(PredaParser.T__46);
						this.state = 718;
						this.expression(11);
						_localctx.expressionType =  33;
						}
						break;

					case 23:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 721;
						if (!(this.precpred(this._ctx, 9))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 9)");
						}
						this.state = 722;
						this.match(PredaParser.T__47);
						this.state = 723;
						this.expression(10);
						_localctx.expressionType =  34;
						}
						break;

					case 24:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 726;
						if (!(this.precpred(this._ctx, 8))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 8)");
						}
						this.state = 727;
						this.match(PredaParser.T__48);
						this.state = 728;
						this.expression(9);
						_localctx.expressionType =  35;
						}
						break;

					case 25:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 731;
						if (!(this.precpred(this._ctx, 7))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 7)");
						}
						this.state = 732;
						this.match(PredaParser.T__49);
						this.state = 733;
						this.expression(8);
						_localctx.expressionType =  36;
						}
						break;

					case 26:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 736;
						if (!(this.precpred(this._ctx, 6))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 6)");
						}
						this.state = 737;
						this.match(PredaParser.T__50);
						this.state = 738;
						this.expression(7);
						_localctx.expressionType =  37;
						}
						break;

					case 27:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 741;
						if (!(this.precpred(this._ctx, 5))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 5)");
						}
						this.state = 742;
						this.match(PredaParser.T__51);
						this.state = 743;
						this.expression(6);
						_localctx.expressionType =  38;
						}
						break;

					case 28:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 746;
						if (!(this.precpred(this._ctx, 4))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 4)");
						}
						this.state = 747;
						this.match(PredaParser.T__52);
						this.state = 748;
						this.expression(5);
						_localctx.expressionType =  39;
						}
						break;

					case 29:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 751;
						if (!(this.precpred(this._ctx, 3))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 3)");
						}
						this.state = 752;
						this.match(PredaParser.T__53);
						this.state = 753;
						this.expression(4);
						_localctx.expressionType =  40;
						}
						break;

					case 30:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 756;
						if (!(this.precpred(this._ctx, 2))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 2)");
						}
						this.state = 757;
						this.match(PredaParser.T__54);
						this.state = 758;
						this.expression(3);
						_localctx.expressionType =  41;
						}
						break;

					case 31:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 761;
						if (!(this.precpred(this._ctx, 43))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 43)");
						}
						this.state = 762;
						this.match(PredaParser.T__25);
						_localctx.expressionType =  0;
						}
						break;

					case 32:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 764;
						if (!(this.precpred(this._ctx, 42))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 42)");
						}
						this.state = 765;
						this.match(PredaParser.T__26);
						_localctx.expressionType =  1;
						}
						break;

					case 33:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 767;
						if (!(this.precpred(this._ctx, 41))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 41)");
						}
						this.state = 768;
						this.match(PredaParser.T__2);
						this.state = 769;
						this.expression(0);
						this.state = 770;
						this.match(PredaParser.T__4);
						_localctx.expressionType =  2;
						}
						break;

					case 34:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 773;
						if (!(this.precpred(this._ctx, 40))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 40)");
						}
						this.state = 774;
						this.match(PredaParser.T__9);
						this.state = 775;
						this.functionCallArguments();
						this.state = 776;
						this.match(PredaParser.T__10);
						_localctx.expressionType =  3;
						}
						break;

					case 35:
						{
						_localctx = new ExpressionContext(_parentctx, _parentState);
						this.pushNewRecursionContext(_localctx, _startState, PredaParser.RULE_expression);
						this.state = 779;
						if (!(this.precpred(this._ctx, 39))) {
							throw this.createFailedPredicateException("this.precpred(this._ctx, 39)");
						}
						this.state = 780;
						this.match(PredaParser.T__0);
						this.state = 781;
						this.identifier();
						_localctx.expressionType =  4;
						}
						break;
					}
					}
				}
				this.state = 788;
				this._errHandler.sync(this);
				_alt = this.interpreter.adaptivePredict(this._input, 65, this._ctx);
			}
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public primaryExpression(): PrimaryExpressionContext {
		let _localctx: PrimaryExpressionContext = new PrimaryExpressionContext(this._ctx, this.state);
		this.enterRule(_localctx, 100, PredaParser.RULE_primaryExpression);
		try {
			this.state = 801;
			this._errHandler.sync(this);
			switch (this._input.LA(1)) {
			case PredaParser.BooleanLiteral:
				this.enterOuterAlt(_localctx, 1);
				{
				this.state = 789;
				this.match(PredaParser.BooleanLiteral);
				}
				break;
			case PredaParser.DecimalIntegerLiteral:
				this.enterOuterAlt(_localctx, 2);
				{
				this.state = 790;
				this.match(PredaParser.DecimalIntegerLiteral);
				}
				break;
			case PredaParser.DecimalFloatLiteral:
				this.enterOuterAlt(_localctx, 3);
				{
				this.state = 791;
				this.match(PredaParser.DecimalFloatLiteral);
				}
				break;
			case PredaParser.HexIntegerLiteral:
				this.enterOuterAlt(_localctx, 4);
				{
				this.state = 792;
				this.match(PredaParser.HexIntegerLiteral);
				}
				break;
			case PredaParser.DecimalBigIntegerLiteral:
				this.enterOuterAlt(_localctx, 5);
				{
				this.state = 793;
				this.match(PredaParser.DecimalBigIntegerLiteral);
				}
				break;
			case PredaParser.HexBigIntegerLiteral:
				this.enterOuterAlt(_localctx, 6);
				{
				this.state = 794;
				this.match(PredaParser.HexBigIntegerLiteral);
				}
				break;
			case PredaParser.StringLiteral:
				this.enterOuterAlt(_localctx, 7);
				{
				this.state = 795;
				this.match(PredaParser.StringLiteral);
				}
				break;
			case PredaParser.AddressLiteral:
				this.enterOuterAlt(_localctx, 8);
				{
				this.state = 796;
				this.match(PredaParser.AddressLiteral);
				}
				break;
			case PredaParser.HashLiteral:
				this.enterOuterAlt(_localctx, 9);
				{
				this.state = 797;
				this.match(PredaParser.HashLiteral);
				}
				break;
			case PredaParser.Identifier:
				this.enterOuterAlt(_localctx, 10);
				{
				this.state = 798;
				this.identifier();
				}
				break;
			case PredaParser.T__11:
			case PredaParser.T__12:
			case PredaParser.T__13:
			case PredaParser.T__14:
			case PredaParser.T__15:
			case PredaParser.AddressKeyword:
			case PredaParser.FloatType:
			case PredaParser.IntType:
			case PredaParser.UintType:
				this.enterOuterAlt(_localctx, 11);
				{
				this.state = 799;
				this.fundamentalTypeName();
				}
				break;
			case PredaParser.T__16:
			case PredaParser.T__19:
				this.enterOuterAlt(_localctx, 12);
				{
				this.state = 800;
				this.builtInContainerTypeName();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public functionCallArguments(): FunctionCallArgumentsContext {
		let _localctx: FunctionCallArgumentsContext = new FunctionCallArgumentsContext(this._ctx, this.state);
		this.enterRule(_localctx, 102, PredaParser.RULE_functionCallArguments);
		let _la: number;
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 811;
			this._errHandler.sync(this);
			_la = this._input.LA(1);
			if ((((_la) & ~0x1F) === 0 && ((1 << _la) & ((1 << PredaParser.T__9) | (1 << PredaParser.T__11) | (1 << PredaParser.T__12) | (1 << PredaParser.T__13) | (1 << PredaParser.T__14) | (1 << PredaParser.T__15) | (1 << PredaParser.T__16) | (1 << PredaParser.T__19) | (1 << PredaParser.T__25) | (1 << PredaParser.T__26) | (1 << PredaParser.T__27) | (1 << PredaParser.T__28) | (1 << PredaParser.T__29) | (1 << PredaParser.T__30))) !== 0) || ((((_la - 68)) & ~0x1F) === 0 && ((1 << (_la - 68)) & ((1 << (PredaParser.AddressKeyword - 68)) | (1 << (PredaParser.FloatType - 68)) | (1 << (PredaParser.IntType - 68)) | (1 << (PredaParser.UintType - 68)) | (1 << (PredaParser.BooleanLiteral - 68)) | (1 << (PredaParser.DecimalFloatLiteral - 68)) | (1 << (PredaParser.DecimalIntegerLiteral - 68)) | (1 << (PredaParser.AddressLiteral - 68)) | (1 << (PredaParser.HashLiteral - 68)) | (1 << (PredaParser.HexIntegerLiteral - 68)) | (1 << (PredaParser.DecimalBigIntegerLiteral - 68)) | (1 << (PredaParser.HexBigIntegerLiteral - 68)) | (1 << (PredaParser.Identifier - 68)) | (1 << (PredaParser.StringLiteral - 68)))) !== 0)) {
				{
				this.state = 803;
				this.expression(0);
				this.state = 808;
				this._errHandler.sync(this);
				_la = this._input.LA(1);
				while (_la === PredaParser.T__3) {
					{
					{
					this.state = 804;
					this.match(PredaParser.T__3);
					this.state = 805;
					this.expression(0);
					}
					}
					this.state = 810;
					this._errHandler.sync(this);
					_la = this._input.LA(1);
				}
				}
			}

			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}
	// @RuleVersion(0)
	public identifier(): IdentifierContext {
		let _localctx: IdentifierContext = new IdentifierContext(this._ctx, this.state);
		this.enterRule(_localctx, 104, PredaParser.RULE_identifier);
		try {
			this.enterOuterAlt(_localctx, 1);
			{
			this.state = 813;
			this.match(PredaParser.Identifier);
			}
		}
		catch (re) {
			if (re instanceof RecognitionException) {
				_localctx.exception = re;
				this._errHandler.reportError(this, re);
				this._errHandler.recover(this, re);
			} else {
				throw re;
			}
		}
		finally {
			this.exitRule();
		}
		return _localctx;
	}

	public sempred(_localctx: RuleContext, ruleIndex: number, predIndex: number): boolean {
		switch (ruleIndex) {
		case 49:
			return this.expression_sempred(_localctx as ExpressionContext, predIndex);
		}
		return true;
	}
	private expression_sempred(_localctx: ExpressionContext, predIndex: number): boolean {
		switch (predIndex) {
		case 0:
			return this.precpred(this._ctx, 31);

		case 1:
			return this.precpred(this._ctx, 30);

		case 2:
			return this.precpred(this._ctx, 29);

		case 3:
			return this.precpred(this._ctx, 28);

		case 4:
			return this.precpred(this._ctx, 27);

		case 5:
			return this.precpred(this._ctx, 26);

		case 6:
			return this.precpred(this._ctx, 25);

		case 7:
			return this.precpred(this._ctx, 24);

		case 8:
			return this.precpred(this._ctx, 23);

		case 9:
			return this.precpred(this._ctx, 22);

		case 10:
			return this.precpred(this._ctx, 21);

		case 11:
			return this.precpred(this._ctx, 20);

		case 12:
			return this.precpred(this._ctx, 19);

		case 13:
			return this.precpred(this._ctx, 18);

		case 14:
			return this.precpred(this._ctx, 17);

		case 15:
			return this.precpred(this._ctx, 16);

		case 16:
			return this.precpred(this._ctx, 15);

		case 17:
			return this.precpred(this._ctx, 14);

		case 18:
			return this.precpred(this._ctx, 13);

		case 19:
			return this.precpred(this._ctx, 12);

		case 20:
			return this.precpred(this._ctx, 11);

		case 21:
			return this.precpred(this._ctx, 10);

		case 22:
			return this.precpred(this._ctx, 9);

		case 23:
			return this.precpred(this._ctx, 8);

		case 24:
			return this.precpred(this._ctx, 7);

		case 25:
			return this.precpred(this._ctx, 6);

		case 26:
			return this.precpred(this._ctx, 5);

		case 27:
			return this.precpred(this._ctx, 4);

		case 28:
			return this.precpred(this._ctx, 3);

		case 29:
			return this.precpred(this._ctx, 2);

		case 30:
			return this.precpred(this._ctx, 43);

		case 31:
			return this.precpred(this._ctx, 42);

		case 32:
			return this.precpred(this._ctx, 41);

		case 33:
			return this.precpred(this._ctx, 40);

		case 34:
			return this.precpred(this._ctx, 39);
		}
		return true;
	}

	private static readonly _serializedATNSegments: number = 2;
	private static readonly _serializedATNSegment0: string =
		"\x03\uC91D\uCABA\u058D\uAFBA\u4F53\u0607\uEA8B\uC241\x03e\u0332\x04\x02" +
		"\t\x02\x04\x03\t\x03\x04\x04\t\x04\x04\x05\t\x05\x04\x06\t\x06\x04\x07" +
		"\t\x07\x04\b\t\b\x04\t\t\t\x04\n\t\n\x04\v\t\v\x04\f\t\f\x04\r\t\r\x04" +
		"\x0E\t\x0E\x04\x0F\t\x0F\x04\x10\t\x10\x04\x11\t\x11\x04\x12\t\x12\x04" +
		"\x13\t\x13\x04\x14\t\x14\x04\x15\t\x15\x04\x16\t\x16\x04\x17\t\x17\x04" +
		"\x18\t\x18\x04\x19\t\x19\x04\x1A\t\x1A\x04\x1B\t\x1B\x04\x1C\t\x1C\x04" +
		"\x1D\t\x1D\x04\x1E\t\x1E\x04\x1F\t\x1F\x04 \t \x04!\t!\x04\"\t\"\x04#" +
		"\t#\x04$\t$\x04%\t%\x04&\t&\x04\'\t\'\x04(\t(\x04)\t)\x04*\t*\x04+\t+" +
		"\x04,\t,\x04-\t-\x04.\t.\x04/\t/\x040\t0\x041\t1\x042\t2\x043\t3\x044" +
		"\t4\x045\t5\x046\t6\x03\x02\x07\x02n\n\x02\f\x02\x0E\x02q\v\x02\x03\x02" +
		"\x03\x02\x03\x02\x03\x03\x03\x03\x03\x04\x03\x04\x03\x04\x03\x04\x05\x04" +
		"|\n\x04\x03\x04\x03\x04\x03\x04\x05\x04\x81\n\x04\x03\x04\x03\x04\x03" +
		"\x05\x03\x05\x05\x05\x87\n\x05\x03\x05\x03\x05\x07\x05\x8B\n\x05\f\x05" +
		"\x0E\x05\x8E\v\x05\x03\x05\x03\x05\x03\x06\x03\x06\x03\x06\x03\x06\x03" +
		"\x07\x06\x07\x97\n\x07\r\x07\x0E\x07\x98\x03\x07\x05\x07\x9C\n\x07\x03" +
		"\b\x05\b\x9F\n\b\x03\b\x05\b\xA2\n\b\x03\b\x03\b\x03\b\x03\b\x03\b\x03" +
		"\b\x07\b\xAA\n\b\f\b\x0E\b\xAD\v\b\x05\b\xAF\n\b\x03\b\x03\b\x07\b\xB3" +
		"\n\b\f\b\x0E\b\xB6\v\b\x03\b\x03\b\x03\t\x03\t\x03\t\x05\t\xBD\n\t\x03" +
		"\t\x03\t\x03\n\x03\n\x03\n\x03\n\x03\n\x03\n\x05\n\xC7\n\n\x03\v\x05\v" +
		"\xCA\n\v\x03\v\x05\v\xCD\n\v\x03\v\x05\v\xD0\n\v\x03\v\x03\v\x03\v\x03" +
		"\v\x03\f\x03\f\x03\f\x03\f\x03\f\x03\f\x03\f\x03\r\x03\r\x03\r\x03\x0E" +
		"\x05\x0E\xE1\n\x0E\x03\x0E\x05\x0E\xE4\n\x0E\x03\x0E\x03\x0E\x03\x0E\x03" +
		"\x0E\x03\x0E\x03\x0E\x07\x0E\xEC\n\x0E\f\x0E\x0E\x0E\xEF\v\x0E\x03\x0E" +
		"\x03\x0E\x03\x0F\x03\x0F\x03\x0F\x03\x0F\x03\x0F\x03\x0F\x07\x0F\xF9\n" +
		"\x0F\f\x0F\x0E\x0F\xFC\v\x0F\x03\x0F\x03\x0F\x03\x10\x05\x10\u0101\n\x10" +
		"\x03\x10\x05\x10\u0104\n\x10\x03\x10\x03\x10\x03\x10\x03\x10\x05\x10\u010A" +
		"\n\x10\x03\x10\x03\x10\x07\x10\u010E\n\x10\f\x10\x0E\x10\u0111\v\x10\x03" +
		"\x10\x03\x10\x03\x11\x03\x11\x03\x11\x07\x11\u0118\n\x11\f\x11\x0E\x11" +
		"\u011B\v\x11\x03\x11\x03\x11\x03\x12\x05\x12\u0120\n\x12\x03\x12\x05\x12" +
		"\u0123\n\x12\x03\x12\x05\x12\u0126\n\x12\x03\x12\x03\x12\x05\x12\u012A" +
		"\n\x12\x03\x12\x03\x12\x03\x12\x03\x12\x03\x12\x07\x12\u0131\n\x12\f\x12" +
		"\x0E\x12\u0134\v\x12\x03\x12\x05\x12\u0137\n\x12\x03\x13\x05\x13\u013A" +
		"\n\x13\x03\x13\x03\x13\x03\x14\x03\x14\x03\x14\x07\x14\u0141\n\x14\f\x14" +
		"\x0E\x14\u0144\v\x14\x05\x14\u0146\n\x14\x03\x15\x05\x15\u0149\n\x15\x03" +
		"\x15\x03\x15\x03\x15\x03\x16\x03\x16\x03\x17\x03\x17\x03\x17\x03\x18\x05" +
		"\x18\u0154\n\x18\x03\x18\x03\x18\x05\x18\u0158\n\x18\x03\x19\x03\x19\x03" +
		"\x19\x05\x19\u015D\n\x19\x03\x1A\x03\x1A\x03\x1B\x03\x1B\x05\x1B\u0163" +
		"\n\x1B\x03\x1C\x03\x1C\x03\x1D\x03\x1D\x03\x1D\x03\x1D\x03\x1D\x03\x1D" +
		"\x03\x1D\x03\x1E\x03\x1E\x03\x1E\x03\x1E\x03\x1E\x03\x1F\x03\x1F\x03\x1F" +
		"\x07\x1F\u0176\n\x1F\f\x1F\x0E\x1F\u0179\v\x1F\x03\x1F\x03\x1F\x03 \x03" +
		" \x07 \u017F\n \f \x0E \u0182\v \x03 \x03 \x03!\x03!\x03!\x03!\x03!\x03" +
		"!\x03!\x03!\x03!\x03!\x03!\x05!\u0191\n!\x03\"\x03\"\x03\"\x03#\x03#\x07" +
		"#\u0198\n#\f#\x0E#\u019B\v#\x03#\x05#\u019E\n#\x03$\x03$\x03$\x03$\x03" +
		"$\x03$\x07$\u01A6\n$\f$\x0E$\u01A9\v$\x03$\x03$\x03%\x03%\x03%\x07%\u01B0" +
		"\n%\f%\x0E%\u01B3\v%\x03%\x03%\x03&\x03&\x03&\x03&\x03&\x03&\x03&\x07" +
		"&\u01BE\n&\f&\x0E&\u01C1\v&\x03&\x03&\x03\'\x03\'\x03\'\x03\'\x03\'\x03" +
		"\'\x07\'\u01CB\n\'\f\'\x0E\'\u01CE\v\'\x03\'\x03\'\x03(\x03(\x03(\x03" +
		"(\x03(\x03(\x03(\x03(\x03(\x03(\x05(\u01DC\n(\x03)\x03)\x03)\x05)\u01E1" +
		"\n)\x03*\x03*\x03*\x03*\x07*\u01E7\n*\f*\x0E*\u01EA\v*\x05*\u01EC\n*\x03" +
		"*\x03*\x05*\u01F0\n*\x03*\x03*\x07*\u01F4\n*\f*\x0E*\u01F7\v*\x03*\x03" +
		"*\x03+\x03+\x03+\x03+\x03+\x03+\x03+\x05+\u0202\n+\x03,\x03,\x03,\x03" +
		",\x05,\u0208\n,\x03,\x03,\x05,\u020C\n,\x03,\x03,\x05,\u0210\n,\x03,\x03" +
		",\x03,\x07,\u0215\n,\f,\x0E,\u0218\v,\x03,\x03,\x03-\x03-\x03-\x07-\u021F" +
		"\n-\f-\x0E-\u0222\v-\x03-\x03-\x03-\x03-\x03-\x03-\x03-\x03.\x03.\x03" +
		".\x03/\x03/\x03/\x030\x030\x050\u0233\n0\x030\x030\x031\x031\x031\x03" +
		"2\x032\x032\x032\x052\u023E\n2\x033\x033\x033\x033\x033\x033\x033\x03" +
		"3\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x03" +
		"3\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x053\u0261\n" +
		"3\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x03" +
		"3\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x03" +
		"3\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x03" +
		"3\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x03" +
		"3\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x03" +
		"3\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x03" +
		"3\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x03" +
		"3\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x03" +
		"3\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x03" +
		"3\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x03" +
		"3\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x03" +
		"3\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x033\x03" +
		"3\x033\x033\x033\x033\x033\x033\x033\x033\x073\u0313\n3\f3\x0E3\u0316" +
		"\v3\x034\x034\x034\x034\x034\x034\x034\x034\x034\x034\x034\x034\x054\u0324" +
		"\n4\x035\x035\x035\x075\u0329\n5\f5\x0E5\u032C\v5\x055\u032E\n5\x036\x03" +
		"6\x036\x02\x02\x03d7\x02\x02\x04\x02\x06\x02\b\x02\n\x02\f\x02\x0E\x02" +
		"\x10\x02\x12\x02\x14\x02\x16\x02\x18\x02\x1A\x02\x1C\x02\x1E\x02 \x02" +
		"\"\x02$\x02&\x02(\x02*\x02,\x02.\x020\x022\x024\x026\x028\x02:\x02<\x02" +
		">\x02@\x02B\x02D\x02F\x02H\x02J\x02L\x02N\x02P\x02R\x02T\x02V\x02X\x02" +
		"Z\x02\\\x02^\x02`\x02b\x02d\x02f\x02h\x02j\x02\x02\x07\x05\x02WY]]bb\x05" +
		"\x02CCEFVV\x03\x02NO\x05\x02\x0E\x12FFTV\x06\x02\x0E\x0E\x10\x11FFTV\x02" +
		"\u0382\x02o\x03\x02\x02\x02\x04u\x03\x02\x02\x02\x06w\x03\x02\x02\x02" +
		"\b\x84\x03\x02\x02\x02\n\x91\x03\x02\x02\x02\f\x9B\x03\x02\x02\x02\x0E" +
		"\x9E\x03\x02\x02\x02\x10\xBC\x03\x02\x02\x02\x12\xC6\x03\x02\x02\x02\x14" +
		"\xC9\x03\x02\x02\x02\x16\xD5\x03\x02\x02\x02\x18\xDC\x03\x02\x02\x02\x1A" +
		"\xE0\x03\x02\x02\x02\x1C\xF2\x03\x02\x02\x02\x1E\u0100\x03\x02\x02\x02" +
		" \u0114\x03\x02\x02\x02\"\u011F\x03\x02\x02\x02$\u0139\x03\x02\x02\x02" +
		"&\u0145\x03\x02\x02\x02(\u0148\x03\x02\x02\x02*\u014D\x03\x02\x02\x02" +
		",\u014F\x03\x02\x02\x02.\u0153\x03\x02\x02\x020\u015C\x03\x02\x02\x02" +
		"2\u015E\x03\x02\x02\x024\u0162\x03\x02\x02\x026\u0164\x03\x02\x02\x02" +
		"8\u0166\x03\x02\x02\x02:\u016D\x03\x02\x02\x02<\u0177\x03\x02\x02\x02" +
		">\u017C\x03\x02\x02\x02@\u0190\x03\x02\x02\x02B\u0192\x03\x02\x02\x02" +
		"D\u0195\x03\x02\x02\x02F\u019F\x03\x02\x02\x02H\u01AC\x03\x02\x02\x02" +
		"J\u01B6\x03\x02\x02\x02L\u01C4\x03\x02\x02\x02N\u01D1\x03\x02\x02\x02" +
		"P\u01E0\x03\x02\x02\x02R\u01E2\x03\x02\x02\x02T\u0201\x03\x02\x02\x02" +
		"V\u0203\x03\x02\x02\x02X\u021B\x03\x02\x02\x02Z\u022A\x03\x02\x02\x02" +
		"\\\u022D\x03\x02\x02\x02^\u0230\x03\x02\x02\x02`\u0236\x03\x02\x02\x02" +
		"b\u0239\x03\x02\x02\x02d\u0260\x03\x02\x02\x02f\u0323\x03\x02\x02\x02" +
		"h\u032D\x03\x02\x02\x02j\u032F\x03\x02\x02\x02ln\x05\x04\x03\x02ml\x03" +
		"\x02\x02\x02nq\x03\x02\x02\x02om\x03\x02\x02\x02op\x03\x02\x02\x02pr\x03" +
		"\x02\x02\x02qo\x03\x02\x02\x02rs\x05\x0E\b\x02st\x07\x02\x02\x03t\x03" +
		"\x03\x02\x02\x02uv\x05\x06\x04\x02v\x05\x03\x02\x02\x02w{\x07L\x02\x02" +
		"xy\x05j6\x02yz\x07\x03\x02\x02z|\x03\x02\x02\x02{x\x03\x02\x02\x02{|\x03" +
		"\x02\x02\x02|}\x03\x02\x02\x02}\x80\x05j6\x02~\x7F\x07P\x02\x02\x7F\x81" +
		"\x05j6\x02\x80~\x03\x02\x02\x02\x80\x81\x03\x02\x02\x02\x81\x82\x03\x02" +
		"\x02\x02\x82\x83\x07\x04\x02\x02\x83\x07\x03\x02\x02\x02\x84\x86\x07\x05" +
		"\x02\x02\x85\x87\x05\n\x06\x02\x86\x85\x03\x02\x02\x02\x86\x87\x03\x02" +
		"\x02\x02\x87\x8C\x03\x02\x02\x02\x88\x89\x07\x06\x02\x02\x89\x8B\x05\n" +
		"\x06\x02\x8A\x88\x03\x02\x02\x02\x8B\x8E\x03\x02\x02\x02\x8C\x8A\x03\x02" +
		"\x02\x02\x8C\x8D\x03\x02\x02\x02\x8D\x8F\x03\x02\x02\x02\x8E\x8C\x03\x02" +
		"\x02\x02\x8F\x90\x07\x07\x02\x02\x90\t\x03\x02\x02\x02\x91\x92\x05j6\x02" +
		"\x92\x93\x07\b\x02\x02\x93\x94\t\x02\x02\x02\x94\v\x03\x02\x02\x02\x95" +
		"\x97\x07:\x02\x02\x96\x95\x03\x02\x02\x02\x97\x98\x03\x02\x02\x02\x98" +
		"\x96\x03\x02\x02\x02\x98\x99\x03\x02\x02\x02\x99\x9C\x03\x02\x02\x02\x9A" +
		"\x9C\x07;\x02\x02\x9B\x96\x03\x02\x02\x02\x9B\x9A\x03\x02\x02\x02\x9C" +
		"\r\x03\x02\x02\x02\x9D\x9F\x05\f\x07\x02\x9E\x9D\x03\x02\x02\x02\x9E\x9F" +
		"\x03\x02\x02\x02\x9F\xA1\x03\x02\x02\x02\xA0\xA2\x05\b\x05\x02\xA1\xA0" +
		"\x03\x02\x02\x02\xA1\xA2\x03\x02\x02\x02\xA2\xA3\x03\x02\x02\x02\xA3\xA4" +
		"\x07K\x02\x02\xA4\xAE\x05j6\x02\xA5\xA6\x07S\x02\x02\xA6\xAB\x05\x10\t" +
		"\x02\xA7\xA8\x07\x06\x02\x02\xA8\xAA\x05\x10\t\x02\xA9\xA7\x03\x02\x02" +
		"\x02\xAA\xAD\x03\x02\x02\x02\xAB\xA9\x03\x02\x02\x02\xAB\xAC\x03\x02\x02" +
		"\x02\xAC\xAF\x03\x02\x02\x02\xAD\xAB\x03\x02\x02\x02\xAE\xA5\x03\x02\x02" +
		"\x02\xAE\xAF\x03\x02\x02\x02\xAF\xB0\x03\x02\x02\x02\xB0\xB4\x07\t\x02" +
		"\x02\xB1\xB3\x05\x12\n\x02\xB2\xB1\x03\x02\x02\x02\xB3\xB6\x03\x02\x02" +
		"\x02\xB4\xB2\x03\x02\x02\x02\xB4\xB5\x03\x02\x02\x02\xB5\xB7\x03\x02\x02" +
		"\x02\xB6\xB4\x03\x02\x02\x02\xB7\xB8\x07\n\x02\x02\xB8\x0F\x03\x02\x02" +
		"\x02\xB9\xBA\x05j6\x02\xBA\xBB\x07\x03\x02\x02\xBB\xBD\x03\x02\x02\x02" +
		"\xBC\xB9\x03\x02\x02\x02\xBC\xBD\x03\x02\x02\x02\xBD\xBE\x03\x02\x02\x02" +
		"\xBE\xBF\x05j6\x02\xBF\x11\x03\x02\x02\x02\xC0\xC7\x05\x14\v\x02\xC1\xC7" +
		"\x05\x16\f\x02\xC2\xC7\x05\x1A\x0E\x02\xC3\xC7\x05\x1E\x10\x02\xC4\xC7" +
		"\x05\x1C\x0F\x02\xC5\xC7\x05 \x11\x02\xC6\xC0\x03\x02\x02\x02\xC6\xC1" +
		"\x03\x02\x02\x02\xC6\xC2\x03\x02\x02\x02\xC6\xC3\x03\x02\x02\x02\xC6\xC4" +
		"\x03\x02\x02\x02\xC6\xC5\x03\x02\x02\x02\xC7\x13\x03\x02\x02\x02\xC8\xCA" +
		"\x05\f\x07\x02\xC9\xC8\x03\x02\x02\x02\xC9\xCA\x03\x02\x02\x02\xCA\xCC" +
		"\x03\x02\x02\x02\xCB\xCD\x05\b\x05\x02\xCC\xCB\x03\x02\x02\x02\xCC\xCD" +
		"\x03\x02\x02\x02\xCD\xCF\x03\x02\x02\x02\xCE\xD0\x05\x18\r\x02\xCF\xCE" +
		"\x03\x02\x02\x02\xCF\xD0\x03\x02\x02\x02\xD0\xD1\x03\x02\x02\x02\xD1\xD2" +
		"\x050\x19\x02\xD2\xD3\x05j6\x02\xD3\xD4\x07\x04\x02\x02\xD4\x15\x03\x02" +
		"\x02\x02\xD5\xD6\x07=\x02\x02\xD6\xD7\x050\x19\x02\xD7\xD8\x05j6\x02\xD8" +
		"\xD9\x07\b\x02\x02\xD9\xDA\x05d3\x02\xDA\xDB\x07\x04\x02\x02\xDB\x17\x03" +
		"\x02\x02\x02\xDC\xDD\x07\v\x02\x02\xDD\xDE\t\x03\x02\x02\xDE\x19\x03\x02" +
		"\x02\x02\xDF\xE1\x05\f\x07\x02\xE0\xDF\x03\x02\x02\x02\xE0\xE1\x03\x02" +
		"\x02\x02\xE1\xE3\x03\x02\x02\x02\xE2\xE4\x05\b\x05\x02\xE3\xE2\x03\x02" +
		"\x02\x02\xE3\xE4\x03\x02\x02\x02\xE4\xE5\x03\x02\x02\x02\xE5\xE6\x07I" +
		"\x02\x02\xE6\xE7\x05j6\x02\xE7\xED\x07\t\x02\x02\xE8\xE9\x05,\x17\x02" +
		"\xE9\xEA\x07\x04\x02\x02\xEA\xEC\x03\x02\x02\x02\xEB\xE8\x03\x02\x02\x02" +
		"\xEC\xEF\x03\x02\x02\x02\xED\xEB\x03\x02\x02\x02\xED\xEE\x03\x02\x02\x02" +
		"\xEE\xF0\x03\x02\x02\x02\xEF\xED\x03\x02\x02\x02\xF0\xF1\x07\n\x02\x02" +
		"\xF1\x1B\x03\x02\x02\x02\xF2\xF3\x07R\x02\x02\xF3\xF4\x05j6\x02\xF4\xFA" +
		"\x07\t\x02\x02\xF5\xF6\x05\"\x12\x02\xF6\xF7\x07\x04\x02\x02\xF7\xF9\x03" +
		"\x02\x02\x02\xF8\xF5\x03\x02\x02\x02\xF9\xFC\x03\x02\x02\x02\xFA\xF8\x03" +
		"\x02\x02\x02\xFA\xFB\x03\x02\x02\x02\xFB\xFD\x03\x02\x02\x02\xFC\xFA\x03" +
		"\x02\x02\x02\xFD\xFE\x07\n\x02\x02\xFE\x1D\x03\x02\x02\x02\xFF\u0101\x05" +
		"\f\x07\x02\u0100\xFF\x03\x02\x02\x02\u0100\u0101\x03\x02\x02\x02\u0101" +
		"\u0103\x03\x02\x02\x02\u0102\u0104\x05\b\x05\x02\u0103\u0102\x03\x02\x02" +
		"\x02\u0103\u0104\x03\x02\x02\x02\u0104\u0105\x03\x02\x02\x02\u0105\u0106" +
		"\x07J\x02\x02\u0106\u0107\x05j6\x02\u0107\u0109\x07\t\x02\x02\u0108\u010A" +
		"\x05j6\x02\u0109\u0108\x03\x02\x02\x02\u0109\u010A\x03\x02\x02\x02\u010A" +
		"\u010F\x03\x02\x02\x02\u010B\u010C\x07\x06\x02\x02\u010C\u010E\x05j6\x02" +
		"\u010D\u010B\x03\x02\x02\x02\u010E\u0111\x03\x02\x02\x02\u010F\u010D\x03" +
		"\x02\x02\x02\u010F\u0110\x03\x02\x02\x02\u0110\u0112\x03\x02\x02\x02\u0111" +
		"\u010F\x03\x02\x02\x02\u0112\u0113\x07\n\x02\x02\u0113\x1F\x03\x02\x02" +
		"\x02\u0114\u0115\x05\"\x12\x02\u0115\u0119\x07\t\x02\x02\u0116\u0118\x05" +
		"@!\x02\u0117\u0116\x03\x02\x02\x02\u0118\u011B\x03\x02\x02\x02\u0119\u0117" +
		"\x03\x02\x02\x02\u0119\u011A\x03\x02\x02\x02\u011A\u011C\x03\x02\x02\x02" +
		"\u011B\u0119\x03\x02\x02\x02\u011C\u011D\x07\n\x02\x02\u011D!\x03\x02" +
		"\x02\x02\u011E\u0120\x05\f\x07\x02\u011F\u011E\x03\x02\x02\x02\u011F\u0120" +
		"\x03\x02\x02\x02\u0120\u0122\x03\x02\x02\x02\u0121\u0123\x05\b\x05\x02" +
		"\u0122\u0121\x03\x02\x02\x02\u0122\u0123\x03\x02\x02\x02\u0123\u0125\x03" +
		"\x02\x02\x02\u0124\u0126\x05\x18\r\x02\u0125\u0124\x03\x02\x02\x02\u0125" +
		"\u0126\x03\x02\x02\x02\u0126\u0127\x03\x02\x02\x02\u0127\u0129\x07M\x02" +
		"\x02\u0128\u012A\x05$\x13\x02\u0129\u0128\x03\x02\x02\x02\u0129\u012A" +
		"\x03\x02\x02\x02\u012A\u012B\x03\x02\x02\x02\u012B\u012C\x05j6\x02\u012C" +
		"\u012D\x07\f\x02\x02\u012D\u012E\x05&\x14\x02\u012E\u0132\x07\r\x02\x02" +
		"\u012F\u0131\x05*\x16\x02\u0130\u012F\x03\x02\x02\x02\u0131\u0134\x03" +
		"\x02\x02\x02\u0132\u0130\x03\x02\x02\x02\u0132\u0133\x03\x02\x02\x02\u0133" +
		"\u0136\x03\x02\x02\x02\u0134\u0132\x03\x02\x02\x02\u0135\u0137\x07=\x02" +
		"\x02\u0136\u0135\x03\x02\x02\x02\u0136\u0137\x03\x02\x02\x02\u0137#\x03" +
		"\x02\x02\x02\u0138\u013A\x07=\x02\x02\u0139\u0138\x03\x02\x02\x02\u0139" +
		"\u013A\x03\x02\x02\x02\u013A\u013B\x03\x02\x02\x02\u013B\u013C\x050\x19" +
		"\x02\u013C%\x03\x02\x02\x02\u013D\u0142\x05(\x15\x02\u013E\u013F\x07\x06" +
		"\x02\x02\u013F\u0141\x05(\x15\x02\u0140\u013E\x03\x02\x02\x02\u0141\u0144" +
		"\x03\x02\x02\x02\u0142\u0140\x03\x02\x02\x02\u0142\u0143\x03\x02\x02\x02" +
		"\u0143\u0146\x03\x02\x02\x02\u0144\u0142\x03\x02\x02\x02\u0145\u013D\x03" +
		"\x02\x02\x02\u0145\u0146\x03\x02\x02\x02\u0146\'\x03\x02\x02\x02\u0147" +
		"\u0149\x07=\x02\x02\u0148\u0147\x03\x02\x02\x02\u0148\u0149\x03\x02\x02" +
		"\x02\u0149\u014A\x03\x02\x02\x02\u014A\u014B\x050\x19\x02\u014B\u014C" +
		"\x05j6\x02\u014C)\x03\x02\x02\x02\u014D\u014E\t\x04\x02\x02\u014E+\x03" +
		"\x02\x02\x02\u014F\u0150\x050\x19\x02\u0150\u0151\x05j6\x02\u0151-\x03" +
		"\x02\x02\x02\u0152\u0154\x07=\x02\x02\u0153\u0152\x03\x02\x02\x02\u0153" +
		"\u0154\x03\x02\x02\x02\u0154\u0157\x03\x02\x02\x02\u0155\u0158\x050\x19" +
		"\x02\u0156\u0158\x07G\x02\x02\u0157\u0155\x03\x02\x02\x02\u0157\u0156" +
		"\x03\x02\x02\x02\u0158/\x03\x02\x02\x02\u0159\u015D\x052\x1A\x02\u015A" +
		"\u015D\x054\x1B\x02\u015B\u015D\x05<\x1F\x02\u015C\u0159\x03\x02\x02\x02" +
		"\u015C\u015A\x03\x02\x02\x02\u015C\u015B\x03\x02\x02\x02\u015D1\x03\x02" +
		"\x02\x02\u015E\u015F\t\x05\x02\x02\u015F3\x03\x02\x02\x02\u0160\u0163" +
		"\x058\x1D\x02\u0161\u0163\x05:\x1E\x02\u0162\u0160\x03\x02\x02\x02\u0162" +
		"\u0161\x03\x02\x02\x02\u01635\x03\x02\x02\x02\u0164\u0165\t\x06\x02\x02" +
		"\u01657\x03\x02\x02\x02\u0166\u0167\x07\x13\x02\x02\u0167\u0168\x07\x14" +
		"\x02\x02\u0168\u0169\x056\x1C\x02\u0169\u016A\x07\x06\x02\x02\u016A\u016B" +
		"\x050\x19\x02\u016B\u016C\x07\x15\x02\x02\u016C9\x03\x02\x02\x02\u016D" +
		"\u016E\x07\x16\x02\x02\u016E\u016F\x07\x14\x02\x02\u016F\u0170\x050\x19" +
		"\x02\u0170\u0171\x07\x15\x02\x02\u0171;\x03\x02\x02\x02\u0172\u0173\x05" +
		"j6\x02\u0173\u0174\x07\x03\x02\x02\u0174\u0176\x03\x02\x02\x02\u0175\u0172" +
		"\x03\x02\x02\x02\u0176\u0179\x03\x02\x02\x02\u0177\u0175\x03\x02\x02\x02" +
		"\u0177\u0178\x03\x02\x02\x02\u0178\u017A\x03\x02\x02\x02\u0179\u0177\x03" +
		"\x02\x02\x02\u017A\u017B\x05j6\x02\u017B=\x03\x02\x02\x02\u017C\u0180" +
		"\x07\t\x02\x02\u017D\u017F\x05@!\x02\u017E\u017D\x03\x02\x02\x02\u017F" +
		"\u0182\x03\x02\x02\x02\u0180\u017E\x03\x02\x02\x02\u0180\u0181\x03\x02" +
		"\x02\x02\u0181\u0183\x03\x02\x02\x02\u0182\u0180\x03\x02\x02\x02\u0183" +
		"\u0184\x07\n\x02\x02\u0184?\x03\x02\x02\x02\u0185\u0191\x05D#\x02\u0186" +
		"\u0191\x05L\'\x02\u0187\u0191\x05V,\x02\u0188\u0191\x05> \x02\u0189\u0191" +
		"\x05X-\x02\u018A\u0191\x05Z.\x02\u018B\u0191\x05\\/\x02\u018C\u0191\x05" +
		"^0\x02\u018D\u0191\x05N(\x02\u018E\u0191\x05`1\x02\u018F\u0191\x05B\"" +
		"\x02\u0190\u0185\x03\x02\x02\x02\u0190\u0186\x03\x02\x02\x02\u0190\u0187" +
		"\x03\x02\x02\x02\u0190\u0188\x03\x02\x02\x02\u0190\u0189\x03\x02\x02\x02" +
		"\u0190\u018A\x03\x02\x02\x02\u0190\u018B\x03\x02\x02\x02\u0190\u018C\x03" +
		"\x02\x02\x02\u0190\u018D\x03\x02\x02\x02\u0190\u018E\x03\x02\x02\x02\u0190" +
		"\u018F\x03\x02\x02\x02\u0191A\x03\x02\x02\x02\u0192\u0193\x05d3\x02\u0193" +
		"\u0194\x07\x04\x02\x02\u0194C\x03\x02\x02\x02\u0195\u0199\x05F$\x02\u0196" +
		"\u0198\x05J&\x02\u0197\u0196\x03\x02\x02\x02\u0198\u019B\x03\x02\x02\x02" +
		"\u0199\u0197\x03\x02\x02\x02\u0199\u019A\x03\x02\x02\x02\u019A\u019D\x03" +
		"\x02\x02\x02\u019B\u0199\x03\x02\x02\x02\u019C\u019E\x05H%\x02\u019D\u019C" +
		"\x03\x02\x02\x02\u019D\u019E\x03\x02\x02\x02\u019EE\x03\x02\x02\x02\u019F" +
		"\u01A0\x07A\x02\x02\u01A0\u01A1\x07\f\x02\x02\u01A1\u01A2\x05d3\x02\u01A2" +
		"\u01A3\x07\r\x02\x02\u01A3\u01A7\x07\t\x02\x02\u01A4\u01A6\x05@!\x02\u01A5" +
		"\u01A4\x03\x02\x02\x02\u01A6\u01A9\x03\x02\x02\x02\u01A7\u01A5\x03\x02" +
		"\x02\x02\u01A7\u01A8\x03\x02\x02\x02\u01A8\u01AA\x03\x02\x02\x02\u01A9" +
		"\u01A7\x03\x02\x02\x02\u01AA\u01AB\x07\n\x02\x02\u01ABG\x03\x02\x02\x02" +
		"\u01AC\u01AD\x07B\x02\x02\u01AD\u01B1\x07\t\x02\x02\u01AE\u01B0\x05@!" +
		"\x02\u01AF\u01AE\x03\x02\x02\x02\u01B0\u01B3\x03\x02\x02\x02\u01B1\u01AF" +
		"\x03\x02\x02\x02\u01B1\u01B2\x03\x02\x02\x02\u01B2\u01B4\x03\x02\x02\x02" +
		"\u01B3\u01B1\x03\x02\x02\x02\u01B4\u01B5\x07\n\x02\x02\u01B5I\x03\x02" +
		"\x02\x02\u01B6\u01B7\x07B\x02\x02\u01B7\u01B8\x07A\x02\x02\u01B8\u01B9" +
		"\x07\f\x02\x02\u01B9\u01BA\x05d3\x02\u01BA\u01BB\x07\r\x02\x02\u01BB\u01BF" +
		"\x07\t\x02\x02\u01BC\u01BE\x05@!\x02\u01BD\u01BC\x03\x02\x02\x02\u01BE" +
		"\u01C1\x03\x02\x02\x02\u01BF\u01BD\x03\x02\x02\x02\u01BF\u01C0\x03\x02" +
		"\x02\x02\u01C0\u01C2\x03\x02\x02\x02\u01C1\u01BF\x03\x02\x02\x02\u01C2" +
		"\u01C3\x07\n\x02\x02\u01C3K\x03\x02\x02\x02\u01C4\u01C5\x07\x17\x02\x02" +
		"\u01C5\u01C6\x07\f\x02\x02\u01C6\u01C7\x05d3\x02\u01C7\u01C8\x07\r\x02" +
		"\x02\u01C8\u01CC\x07\t\x02\x02\u01C9\u01CB\x05@!\x02\u01CA\u01C9\x03\x02" +
		"\x02\x02\u01CB\u01CE\x03\x02\x02\x02\u01CC\u01CA\x03\x02\x02\x02\u01CC" +
		"\u01CD\x03\x02\x02\x02\u01CD\u01CF\x03\x02\x02\x02\u01CE\u01CC\x03\x02" +
		"\x02\x02\u01CF\u01D0\x07\n\x02\x02\u01D0M\x03\x02\x02\x02\u01D1\u01D2" +
		"\x07?\x02\x02\u01D2\u01D3\x07\v\x02\x02\u01D3\u01DB\x05P)\x02\u01D4\u01D5" +
		"\x05j6\x02\u01D5\u01D6\x07\f\x02\x02\u01D6\u01D7\x05h5\x02\u01D7\u01D8" +
		"\x07\r\x02\x02\u01D8\u01D9\x07\x04\x02\x02\u01D9\u01DC\x03\x02\x02\x02" +
		"\u01DA\u01DC\x05R*\x02\u01DB\u01D4\x03\x02\x02\x02\u01DB\u01DA\x03\x02" +
		"\x02\x02\u01DCO\x03\x02\x02\x02\u01DD\u01E1\x05d3\x02\u01DE\u01E1\x07" +
		"D\x02\x02\u01DF\u01E1\x07E\x02\x02\u01E0\u01DD\x03\x02\x02\x02\u01E0\u01DE" +
		"\x03\x02\x02\x02\u01E0\u01DF\x03\x02\x02\x02\u01E1Q\x03\x02\x02\x02\u01E2" +
		"\u01EB\x07\f\x02\x02\u01E3\u01E8\x05T+\x02\u01E4\u01E5\x07\x06\x02\x02" +
		"\u01E5\u01E7\x05T+\x02\u01E6\u01E4\x03\x02\x02\x02\u01E7\u01EA\x03\x02" +
		"\x02\x02\u01E8\u01E6\x03\x02\x02\x02\u01E8\u01E9\x03\x02\x02\x02\u01E9" +
		"\u01EC\x03\x02\x02\x02\u01EA\u01E8\x03\x02\x02\x02\u01EB\u01E3\x03\x02" +
		"\x02\x02\u01EB\u01EC\x03\x02\x02\x02\u01EC\u01ED\x03\x02\x02\x02\u01ED" +
		"\u01EF\x07\r\x02\x02\u01EE\u01F0\x07=\x02\x02\u01EF\u01EE\x03\x02\x02" +
		"\x02\u01EF\u01F0\x03\x02\x02\x02\u01F0\u01F1\x03\x02\x02\x02\u01F1\u01F5" +
		"\x07\t\x02\x02\u01F2\u01F4\x05@!\x02\u01F3\u01F2\x03\x02\x02\x02\u01F4" +
		"\u01F7\x03\x02\x02\x02\u01F5\u01F3\x03\x02\x02\x02\u01F5\u01F6\x03\x02" +
		"\x02\x02\u01F6\u01F8\x03\x02\x02\x02\u01F7\u01F5\x03";
	private static readonly _serializedATNSegment1: string =
		"\x02\x02\x02\u01F8\u01F9\x07\n\x02\x02\u01F9S\x03\x02\x02\x02\u01FA\u01FB" +
		"\x05.\x18\x02\u01FB\u01FC\x05j6\x02\u01FC\u01FD\x07\b\x02\x02\u01FD\u01FE" +
		"\x05d3\x02\u01FE\u0202\x03\x02\x02\x02\u01FF\u0200\x07\x18\x02\x02\u0200" +
		"\u0202\x05j6\x02\u0201\u01FA\x03\x02\x02\x02\u0201\u01FF\x03\x02\x02\x02" +
		"\u0202U\x03\x02\x02\x02\u0203\u0204\x07\x19\x02\x02\u0204\u0207\x07\f" +
		"\x02\x02\u0205\u0208\x05b2\x02\u0206\u0208\x05d3\x02\u0207\u0205\x03\x02" +
		"\x02\x02\u0207\u0206\x03\x02\x02\x02\u0207\u0208\x03\x02\x02\x02\u0208" +
		"\u0209\x03\x02\x02\x02\u0209\u020B\x07\x04\x02\x02\u020A\u020C\x05d3\x02" +
		"\u020B\u020A\x03\x02\x02\x02\u020B\u020C\x03\x02\x02\x02\u020C\u020D\x03" +
		"\x02\x02\x02\u020D\u020F\x07\x04\x02\x02\u020E\u0210\x05d3\x02\u020F\u020E" +
		"\x03\x02\x02\x02\u020F\u0210\x03\x02\x02\x02\u0210\u0211\x03\x02\x02\x02" +
		"\u0211\u0212\x07\r\x02\x02\u0212\u0216\x07\t\x02\x02\u0213\u0215\x05@" +
		"!\x02\u0214\u0213\x03\x02\x02\x02\u0215\u0218\x03\x02\x02\x02\u0216\u0214" +
		"\x03\x02\x02\x02\u0216\u0217\x03\x02\x02\x02\u0217\u0219\x03\x02\x02\x02" +
		"\u0218\u0216\x03\x02\x02\x02\u0219\u021A\x07\n\x02\x02\u021AW\x03\x02" +
		"\x02\x02\u021B\u021C\x07\x1A\x02\x02\u021C\u0220\x07\t\x02\x02\u021D\u021F" +
		"\x05@!\x02\u021E\u021D\x03\x02\x02\x02\u021F\u0222\x03\x02\x02\x02\u0220" +
		"\u021E\x03\x02\x02\x02\u0220\u0221\x03\x02\x02\x02\u0221\u0223\x03\x02" +
		"\x02\x02\u0222\u0220\x03\x02\x02\x02\u0223\u0224\x07\n\x02\x02\u0224\u0225" +
		"\x07\x17\x02\x02\u0225\u0226\x07\f\x02\x02\u0226\u0227\x05d3\x02\u0227" +
		"\u0228\x07\r\x02\x02\u0228\u0229\x07\x04\x02\x02\u0229Y\x03\x02\x02\x02" +
		"\u022A\u022B\x07>\x02\x02\u022B\u022C\x07\x04\x02\x02\u022C[\x03\x02\x02" +
		"\x02\u022D\u022E\x07<\x02\x02\u022E\u022F\x07\x04\x02\x02\u022F]\x03\x02" +
		"\x02\x02\u0230\u0232\x07\x1B\x02\x02\u0231\u0233\x05d3\x02\u0232\u0231" +
		"\x03\x02\x02\x02\u0232\u0233\x03\x02\x02\x02\u0233\u0234\x03\x02\x02\x02" +
		"\u0234\u0235\x07\x04\x02\x02\u0235_\x03\x02\x02\x02\u0236\u0237\x05b2" +
		"\x02\u0237\u0238\x07\x04\x02\x02\u0238a\x03\x02\x02\x02\u0239\u023A\x05" +
		".\x18\x02\u023A\u023D\x05j6\x02\u023B\u023C\x07\b\x02\x02\u023C\u023E" +
		"\x05d3\x02\u023D\u023B\x03\x02\x02\x02\u023D\u023E\x03\x02\x02\x02\u023E" +
		"c\x03\x02\x02\x02\u023F\u0240\b3\x01\x02\u0240\u0241\x07\f\x02\x02\u0241" +
		"\u0242\x05d3\x02\u0242\u0243\x07\r\x02\x02\u0243\u0244\b3\x01\x02\u0244" +
		"\u0261\x03\x02\x02\x02\u0245\u0246\x07\x1C\x02\x02\u0246\u0247\x05d3\'" +
		"\u0247\u0248\b3\x01\x02\u0248\u0261\x03\x02\x02\x02\u0249\u024A\x07\x1D" +
		"\x02\x02\u024A\u024B\x05d3&\u024B\u024C\b3\x01\x02\u024C\u0261\x03\x02" +
		"\x02\x02\u024D\u024E\x07\x1E\x02\x02\u024E\u024F\x05d3%\u024F\u0250\b" +
		"3\x01\x02\u0250\u0261\x03\x02\x02\x02\u0251\u0252\x07\x1F\x02\x02\u0252" +
		"\u0253\x05d3$\u0253\u0254\b3\x01\x02\u0254\u0261\x03\x02\x02\x02\u0255" +
		"\u0256\x07 \x02\x02\u0256\u0257\x05d3#\u0257\u0258\b3\x01\x02\u0258\u0261" +
		"\x03\x02\x02\x02\u0259\u025A\x07!\x02\x02\u025A\u025B\x05d3\"\u025B\u025C" +
		"\b3\x01\x02\u025C\u0261\x03\x02\x02\x02\u025D\u025E\x05f4\x02\u025E\u025F" +
		"\b3\x01\x02\u025F\u0261\x03\x02\x02\x02\u0260\u023F\x03\x02\x02\x02\u0260" +
		"\u0245\x03\x02\x02\x02\u0260\u0249\x03\x02\x02\x02\u0260\u024D\x03\x02" +
		"\x02\x02\u0260\u0251\x03\x02\x02\x02\u0260\u0255\x03\x02\x02\x02\u0260" +
		"\u0259\x03\x02\x02\x02\u0260\u025D\x03\x02\x02\x02\u0261\u0314\x03\x02" +
		"\x02\x02\u0262\u0263\f!\x02\x02\u0263\u0264\x07\"\x02\x02\u0264\u0265" +
		"\x05d3\"\u0265\u0266\b3\x01\x02\u0266\u0313\x03\x02\x02\x02\u0267\u0268" +
		"\f \x02\x02\u0268\u0269\x07#\x02\x02\u0269\u026A\x05d3!\u026A\u026B\b" +
		"3\x01\x02\u026B\u0313\x03\x02\x02\x02\u026C\u026D\f\x1F\x02\x02\u026D" +
		"\u026E\x07$\x02\x02\u026E\u026F\x05d3 \u026F\u0270\b3\x01\x02\u0270\u0313" +
		"\x03\x02\x02\x02\u0271\u0272\f\x1E\x02\x02\u0272\u0273\x07\x1E\x02\x02" +
		"\u0273\u0274\x05d3\x1F\u0274\u0275\b3\x01\x02\u0275\u0313\x03\x02\x02" +
		"\x02\u0276\u0277\f\x1D\x02\x02\u0277\u0278\x07\x1F\x02\x02\u0278\u0279" +
		"\x05d3\x1E\u0279\u027A\b3\x01\x02\u027A\u0313\x03\x02\x02\x02\u027B\u027C" +
		"\f\x1C\x02\x02\u027C\u027D\x07%\x02\x02\u027D\u027E\x05d3\x1D\u027E\u027F" +
		"\b3\x01\x02\u027F\u0313\x03\x02\x02\x02\u0280\u0281\f\x1B\x02\x02\u0281" +
		"\u0282\x07\x15\x02\x02\u0282\u0283\x07\x15\x02\x02\u0283\u0284\x05d3\x1C" +
		"\u0284\u0285\b3\x01\x02\u0285\u0313\x03\x02\x02\x02\u0286\u0287\f\x1A" +
		"\x02\x02\u0287\u0288\x07\x14\x02\x02\u0288\u0289\x05d3\x1B\u0289\u028A" +
		"\b3\x01\x02\u028A\u0313\x03\x02\x02\x02\u028B\u028C\f\x19\x02\x02\u028C" +
		"\u028D\x07\x15\x02\x02\u028D\u028E\x05d3\x1A\u028E\u028F\b3\x01\x02\u028F" +
		"\u0313\x03\x02\x02\x02\u0290\u0291\f\x18\x02\x02\u0291\u0292\x07&\x02" +
		"\x02\u0292\u0293\x05d3\x19\u0293\u0294\b3\x01\x02\u0294\u0313\x03\x02" +
		"\x02\x02\u0295\u0296\f\x17\x02\x02\u0296\u0297\x07\'\x02\x02\u0297\u0298" +
		"\x05d3\x18\u0298\u0299\b3\x01\x02\u0299\u0313\x03\x02\x02\x02\u029A\u029B" +
		"\f\x16\x02\x02\u029B\u029C\x07(\x02\x02\u029C\u029D\x05d3\x17\u029D\u029E" +
		"\b3\x01\x02\u029E\u0313\x03\x02\x02\x02\u029F\u02A0\f\x15\x02\x02\u02A0" +
		"\u02A1\x07)\x02\x02\u02A1\u02A2\x05d3\x16\u02A2\u02A3\b3\x01\x02\u02A3" +
		"\u0313\x03\x02\x02\x02\u02A4\u02A5\f\x14\x02\x02\u02A5\u02A6\x07*\x02" +
		"\x02\u02A6\u02A7\x05d3\x15\u02A7\u02A8\b3\x01\x02\u02A8\u0313\x03\x02" +
		"\x02\x02\u02A9\u02AA\f\x13\x02\x02\u02AA\u02AB\x07\x18\x02\x02\u02AB\u02AC" +
		"\x05d3\x14\u02AC\u02AD\b3\x01\x02\u02AD\u0313\x03\x02\x02\x02\u02AE\u02AF" +
		"\f\x12\x02\x02\u02AF\u02B0\x07+\x02\x02\u02B0\u02B1\x05d3\x13\u02B1\u02B2" +
		"\b3\x01\x02\u02B2\u0313\x03\x02\x02\x02\u02B3\u02B4\f\x11\x02\x02\u02B4" +
		"\u02B5\x07,\x02\x02\u02B5\u02B6\x05d3\x12\u02B6\u02B7\b3\x01\x02\u02B7" +
		"\u0313\x03\x02\x02\x02\u02B8\u02B9\f\x10\x02\x02\u02B9\u02BA\x07-\x02" +
		"\x02\u02BA\u02BB\x05d3\x11\u02BB\u02BC\b3\x01\x02\u02BC\u0313\x03\x02" +
		"\x02\x02\u02BD\u02BE\f\x0F\x02\x02\u02BE\u02BF\x07.\x02\x02\u02BF\u02C0" +
		"\x05d3\x02\u02C0\u02C1\x07/\x02\x02\u02C1\u02C2\x05d3\x10\u02C2\u02C3" +
		"\b3\x01\x02\u02C3\u0313\x03\x02\x02\x02\u02C4\u02C5\f\x0E\x02\x02\u02C5" +
		"\u02C6\x07\b\x02\x02\u02C6\u02C7\x05d3\x0F\u02C7\u02C8\b3\x01\x02\u02C8" +
		"\u0313\x03\x02\x02\x02\u02C9\u02CA\f\r\x02\x02\u02CA\u02CB\x070\x02\x02" +
		"\u02CB\u02CC\x05d3\x0E\u02CC\u02CD\b3\x01\x02\u02CD\u0313\x03\x02\x02" +
		"\x02\u02CE\u02CF\f\f\x02\x02\u02CF\u02D0\x071\x02\x02\u02D0\u02D1\x05" +
		"d3\r\u02D1\u02D2\b3\x01\x02\u02D2\u0313\x03\x02\x02\x02\u02D3\u02D4\f" +
		"\v\x02\x02\u02D4\u02D5\x072\x02\x02\u02D5\u02D6\x05d3\f\u02D6\u02D7\b" +
		"3\x01\x02\u02D7\u0313\x03\x02\x02\x02\u02D8\u02D9\f\n\x02\x02\u02D9\u02DA" +
		"\x073\x02\x02\u02DA\u02DB\x05d3\v\u02DB\u02DC\b3\x01\x02\u02DC\u0313\x03" +
		"\x02\x02\x02\u02DD\u02DE\f\t\x02\x02\u02DE\u02DF\x074\x02\x02\u02DF\u02E0" +
		"\x05d3\n\u02E0\u02E1\b3\x01\x02\u02E1\u0313\x03\x02\x02\x02\u02E2\u02E3" +
		"\f\b\x02\x02\u02E3\u02E4\x075\x02\x02\u02E4\u02E5\x05d3\t\u02E5\u02E6" +
		"\b3\x01\x02\u02E6\u0313\x03\x02\x02\x02\u02E7\u02E8\f\x07\x02\x02\u02E8" +
		"\u02E9\x076\x02\x02\u02E9\u02EA\x05d3\b\u02EA\u02EB\b3\x01\x02\u02EB\u0313" +
		"\x03\x02\x02\x02\u02EC\u02ED\f\x06\x02\x02\u02ED\u02EE\x077\x02\x02\u02EE" +
		"\u02EF\x05d3\x07\u02EF\u02F0\b3\x01\x02\u02F0\u0313\x03\x02\x02\x02\u02F1" +
		"\u02F2\f\x05\x02\x02\u02F2\u02F3\x078\x02\x02\u02F3\u02F4\x05d3\x06\u02F4" +
		"\u02F5\b3\x01\x02\u02F5\u0313\x03\x02\x02\x02\u02F6\u02F7\f\x04\x02\x02" +
		"\u02F7\u02F8\x079\x02\x02\u02F8\u02F9\x05d3\x05\u02F9\u02FA\b3\x01\x02" +
		"\u02FA\u0313\x03\x02\x02\x02\u02FB\u02FC\f-\x02\x02\u02FC\u02FD\x07\x1C" +
		"\x02\x02\u02FD\u0313\b3\x01\x02\u02FE\u02FF\f,\x02\x02\u02FF\u0300\x07" +
		"\x1D\x02\x02\u0300\u0313\b3\x01\x02\u0301\u0302\f+\x02\x02\u0302\u0303" +
		"\x07\x05\x02\x02\u0303\u0304\x05d3\x02\u0304\u0305\x07\x07\x02\x02\u0305" +
		"\u0306\b3\x01\x02\u0306\u0313\x03\x02\x02\x02\u0307\u0308\f*\x02\x02\u0308" +
		"\u0309\x07\f\x02\x02\u0309\u030A\x05h5\x02\u030A\u030B\x07\r\x02\x02\u030B" +
		"\u030C\b3\x01\x02\u030C\u0313\x03\x02\x02\x02\u030D\u030E\f)\x02\x02\u030E" +
		"\u030F\x07\x03\x02\x02\u030F\u0310\x05j6\x02\u0310\u0311\b3\x01\x02\u0311" +
		"\u0313\x03\x02\x02\x02\u0312\u0262\x03\x02\x02\x02\u0312\u0267\x03\x02" +
		"\x02\x02\u0312\u026C\x03\x02\x02\x02\u0312\u0271\x03\x02\x02\x02\u0312" +
		"\u0276\x03\x02\x02\x02\u0312\u027B\x03\x02\x02\x02\u0312\u0280\x03\x02" +
		"\x02\x02\u0312\u0286\x03\x02\x02\x02\u0312\u028B\x03\x02\x02\x02\u0312" +
		"\u0290\x03\x02\x02\x02\u0312\u0295\x03\x02\x02\x02\u0312\u029A\x03\x02" +
		"\x02\x02\u0312\u029F\x03\x02\x02\x02\u0312\u02A4\x03\x02\x02\x02\u0312" +
		"\u02A9\x03\x02\x02\x02\u0312\u02AE\x03\x02\x02\x02\u0312\u02B3\x03\x02" +
		"\x02\x02\u0312\u02B8\x03\x02\x02\x02\u0312\u02BD\x03\x02\x02\x02\u0312" +
		"\u02C4\x03\x02\x02\x02\u0312\u02C9\x03\x02\x02\x02\u0312\u02CE\x03\x02" +
		"\x02\x02\u0312\u02D3\x03\x02\x02\x02\u0312\u02D8\x03\x02\x02\x02\u0312" +
		"\u02DD\x03\x02\x02\x02\u0312\u02E2\x03\x02\x02\x02\u0312\u02E7\x03\x02" +
		"\x02\x02\u0312\u02EC\x03\x02\x02\x02\u0312\u02F1\x03\x02\x02\x02\u0312" +
		"\u02F6\x03\x02\x02\x02\u0312\u02FB\x03\x02\x02\x02\u0312\u02FE\x03\x02" +
		"\x02\x02\u0312\u0301\x03\x02\x02\x02\u0312\u0307\x03\x02\x02\x02\u0312" +
		"\u030D\x03\x02\x02\x02\u0313\u0316\x03\x02\x02\x02\u0314\u0312\x03\x02" +
		"\x02\x02\u0314\u0315\x03\x02\x02\x02\u0315e\x03\x02\x02\x02\u0316\u0314" +
		"\x03\x02\x02\x02\u0317\u0324\x07W\x02\x02\u0318\u0324\x07Y\x02\x02\u0319" +
		"\u0324\x07X\x02\x02\u031A\u0324\x07]\x02\x02\u031B\u0324\x07_\x02\x02" +
		"\u031C\u0324\x07`\x02\x02\u031D\u0324\x07b\x02\x02\u031E\u0324\x07[\x02" +
		"\x02\u031F\u0324\x07\\\x02\x02\u0320\u0324\x05j6\x02\u0321\u0324\x052" +
		"\x1A\x02\u0322\u0324\x054\x1B\x02\u0323\u0317\x03\x02\x02\x02\u0323\u0318" +
		"\x03\x02\x02\x02\u0323\u0319\x03\x02\x02\x02\u0323\u031A\x03\x02\x02\x02" +
		"\u0323\u031B\x03\x02\x02\x02\u0323\u031C\x03\x02\x02\x02\u0323\u031D\x03" +
		"\x02\x02\x02\u0323\u031E\x03\x02\x02\x02\u0323\u031F\x03\x02\x02\x02\u0323" +
		"\u0320\x03\x02\x02\x02\u0323\u0321\x03\x02\x02\x02\u0323\u0322\x03\x02" +
		"\x02\x02\u0324g\x03\x02\x02\x02\u0325\u032A\x05d3\x02\u0326\u0327\x07" +
		"\x06\x02\x02\u0327\u0329\x05d3\x02\u0328\u0326\x03\x02\x02\x02\u0329\u032C" +
		"\x03\x02\x02\x02\u032A\u0328\x03\x02\x02\x02\u032A\u032B\x03\x02\x02\x02" +
		"\u032B\u032E\x03\x02\x02\x02\u032C\u032A\x03\x02\x02\x02\u032D\u0325\x03" +
		"\x02\x02\x02\u032D\u032E\x03\x02\x02\x02\u032Ei\x03\x02\x02\x02\u032F" +
		"\u0330\x07a\x02\x02\u0330k\x03\x02\x02\x02Go{\x80\x86\x8C\x98\x9B\x9E" +
		"\xA1\xAB\xAE\xB4\xBC\xC6\xC9\xCC\xCF\xE0\xE3\xED\xFA\u0100\u0103\u0109" +
		"\u010F\u0119\u011F\u0122\u0125\u0129\u0132\u0136\u0139\u0142\u0145\u0148" +
		"\u0153\u0157\u015C\u0162\u0177\u0180\u0190\u0199\u019D\u01A7\u01B1\u01BF" +
		"\u01CC\u01DB\u01E0\u01E8\u01EB\u01EF\u01F5\u0201\u0207\u020B\u020F\u0216" +
		"\u0220\u0232\u023D\u0260\u0312\u0314\u0323\u032A\u032D";
	public static readonly _serializedATN: string = Utils.join(
		[
			PredaParser._serializedATNSegment0,
			PredaParser._serializedATNSegment1,
		],
		"",
	);
	public static __ATN: ATN;
	public static get _ATN(): ATN {
		if (!PredaParser.__ATN) {
			PredaParser.__ATN = new ATNDeserializer().deserialize(Utils.toCharArray(PredaParser._serializedATN));
		}

		return PredaParser.__ATN;
	}

}

export class PredaSourceContext extends ParserRuleContext {
	public contractDefinition(): ContractDefinitionContext {
		return this.getRuleContext(0, ContractDefinitionContext);
	}
	public EOF(): TerminalNode { return this.getToken(PredaParser.EOF, 0); }
	public directive(): DirectiveContext[];
	public directive(i: number): DirectiveContext;
	public directive(i?: number): DirectiveContext | DirectiveContext[] {
		if (i === undefined) {
			return this.getRuleContexts(DirectiveContext);
		} else {
			return this.getRuleContext(i, DirectiveContext);
		}
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_predaSource; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterPredaSource) {
			listener.enterPredaSource(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitPredaSource) {
			listener.exitPredaSource(this);
		}
	}
}


export class DirectiveContext extends ParserRuleContext {
	public importDirective(): ImportDirectiveContext {
		return this.getRuleContext(0, ImportDirectiveContext);
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_directive; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterDirective) {
			listener.enterDirective(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitDirective) {
			listener.exitDirective(this);
		}
	}
}


export class ImportDirectiveContext extends ParserRuleContext {
	public _dAppName!: IdentifierContext;
	public _contractName!: IdentifierContext;
	public _alias!: IdentifierContext;
	public ImportKeyword(): TerminalNode { return this.getToken(PredaParser.ImportKeyword, 0); }
	public identifier(): IdentifierContext[];
	public identifier(i: number): IdentifierContext;
	public identifier(i?: number): IdentifierContext | IdentifierContext[] {
		if (i === undefined) {
			return this.getRuleContexts(IdentifierContext);
		} else {
			return this.getRuleContext(i, IdentifierContext);
		}
	}
	public AsKeyword(): TerminalNode | undefined { return this.tryGetToken(PredaParser.AsKeyword, 0); }
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_importDirective; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterImportDirective) {
			listener.enterImportDirective(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitImportDirective) {
			listener.exitImportDirective(this);
		}
	}
}


export class AnnotationContext extends ParserRuleContext {
	public annotationItem(): AnnotationItemContext[];
	public annotationItem(i: number): AnnotationItemContext;
	public annotationItem(i?: number): AnnotationItemContext | AnnotationItemContext[] {
		if (i === undefined) {
			return this.getRuleContexts(AnnotationItemContext);
		} else {
			return this.getRuleContext(i, AnnotationItemContext);
		}
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_annotation; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterAnnotation) {
			listener.enterAnnotation(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitAnnotation) {
			listener.exitAnnotation(this);
		}
	}
}


export class AnnotationItemContext extends ParserRuleContext {
	public identifier(): IdentifierContext {
		return this.getRuleContext(0, IdentifierContext);
	}
	public BooleanLiteral(): TerminalNode | undefined { return this.tryGetToken(PredaParser.BooleanLiteral, 0); }
	public DecimalIntegerLiteral(): TerminalNode | undefined { return this.tryGetToken(PredaParser.DecimalIntegerLiteral, 0); }
	public DecimalFloatLiteral(): TerminalNode | undefined { return this.tryGetToken(PredaParser.DecimalFloatLiteral, 0); }
	public HexIntegerLiteral(): TerminalNode | undefined { return this.tryGetToken(PredaParser.HexIntegerLiteral, 0); }
	public StringLiteral(): TerminalNode | undefined { return this.tryGetToken(PredaParser.StringLiteral, 0); }
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_annotationItem; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterAnnotationItem) {
			listener.enterAnnotationItem(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitAnnotationItem) {
			listener.exitAnnotationItem(this);
		}
	}
}


export class DoxygenContext extends ParserRuleContext {
	public DoxygenSingle(): TerminalNode[];
	public DoxygenSingle(i: number): TerminalNode;
	public DoxygenSingle(i?: number): TerminalNode | TerminalNode[] {
		if (i === undefined) {
			return this.getTokens(PredaParser.DoxygenSingle);
		} else {
			return this.getToken(PredaParser.DoxygenSingle, i);
		}
	}
	public DoxygenMulti(): TerminalNode | undefined { return this.tryGetToken(PredaParser.DoxygenMulti, 0); }
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_doxygen; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterDoxygen) {
			listener.enterDoxygen(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitDoxygen) {
			listener.exitDoxygen(this);
		}
	}
}


export class ContractDefinitionContext extends ParserRuleContext {
	public ContractKeyword(): TerminalNode { return this.getToken(PredaParser.ContractKeyword, 0); }
	public identifier(): IdentifierContext {
		return this.getRuleContext(0, IdentifierContext);
	}
	public doxygen(): DoxygenContext | undefined {
		return this.tryGetRuleContext(0, DoxygenContext);
	}
	public annotation(): AnnotationContext | undefined {
		return this.tryGetRuleContext(0, AnnotationContext);
	}
	public ImplementsKeyword(): TerminalNode | undefined { return this.tryGetToken(PredaParser.ImplementsKeyword, 0); }
	public interfaceRef(): InterfaceRefContext[];
	public interfaceRef(i: number): InterfaceRefContext;
	public interfaceRef(i?: number): InterfaceRefContext | InterfaceRefContext[] {
		if (i === undefined) {
			return this.getRuleContexts(InterfaceRefContext);
		} else {
			return this.getRuleContext(i, InterfaceRefContext);
		}
	}
	public contractPart(): ContractPartContext[];
	public contractPart(i: number): ContractPartContext;
	public contractPart(i?: number): ContractPartContext | ContractPartContext[] {
		if (i === undefined) {
			return this.getRuleContexts(ContractPartContext);
		} else {
			return this.getRuleContext(i, ContractPartContext);
		}
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_contractDefinition; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterContractDefinition) {
			listener.enterContractDefinition(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitContractDefinition) {
			listener.exitContractDefinition(this);
		}
	}
}


export class InterfaceRefContext extends ParserRuleContext {
	public _contractName!: IdentifierContext;
	public _interfaceName!: IdentifierContext;
	public identifier(): IdentifierContext[];
	public identifier(i: number): IdentifierContext;
	public identifier(i?: number): IdentifierContext | IdentifierContext[] {
		if (i === undefined) {
			return this.getRuleContexts(IdentifierContext);
		} else {
			return this.getRuleContext(i, IdentifierContext);
		}
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_interfaceRef; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterInterfaceRef) {
			listener.enterInterfaceRef(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitInterfaceRef) {
			listener.exitInterfaceRef(this);
		}
	}
}


export class ContractPartContext extends ParserRuleContext {
	public stateVariableDeclaration(): StateVariableDeclarationContext | undefined {
		return this.tryGetRuleContext(0, StateVariableDeclarationContext);
	}
	public constVariableDeclaration(): ConstVariableDeclarationContext | undefined {
		return this.tryGetRuleContext(0, ConstVariableDeclarationContext);
	}
	public structDefinition(): StructDefinitionContext | undefined {
		return this.tryGetRuleContext(0, StructDefinitionContext);
	}
	public enumDefinition(): EnumDefinitionContext | undefined {
		return this.tryGetRuleContext(0, EnumDefinitionContext);
	}
	public interfaceDefinition(): InterfaceDefinitionContext | undefined {
		return this.tryGetRuleContext(0, InterfaceDefinitionContext);
	}
	public functionDefinition(): FunctionDefinitionContext | undefined {
		return this.tryGetRuleContext(0, FunctionDefinitionContext);
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_contractPart; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterContractPart) {
			listener.enterContractPart(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitContractPart) {
			listener.exitContractPart(this);
		}
	}
}


export class StateVariableDeclarationContext extends ParserRuleContext {
	public typeName(): TypeNameContext {
		return this.getRuleContext(0, TypeNameContext);
	}
	public identifier(): IdentifierContext {
		return this.getRuleContext(0, IdentifierContext);
	}
	public doxygen(): DoxygenContext | undefined {
		return this.tryGetRuleContext(0, DoxygenContext);
	}
	public annotation(): AnnotationContext | undefined {
		return this.tryGetRuleContext(0, AnnotationContext);
	}
	public scope(): ScopeContext | undefined {
		return this.tryGetRuleContext(0, ScopeContext);
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_stateVariableDeclaration; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterStateVariableDeclaration) {
			listener.enterStateVariableDeclaration(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitStateVariableDeclaration) {
			listener.exitStateVariableDeclaration(this);
		}
	}
}


export class ConstVariableDeclarationContext extends ParserRuleContext {
	public ConstantKeyword(): TerminalNode { return this.getToken(PredaParser.ConstantKeyword, 0); }
	public typeName(): TypeNameContext {
		return this.getRuleContext(0, TypeNameContext);
	}
	public identifier(): IdentifierContext {
		return this.getRuleContext(0, IdentifierContext);
	}
	public expression(): ExpressionContext {
		return this.getRuleContext(0, ExpressionContext);
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_constVariableDeclaration; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterConstVariableDeclaration) {
			listener.enterConstVariableDeclaration(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitConstVariableDeclaration) {
			listener.exitConstVariableDeclaration(this);
		}
	}
}


export class ScopeContext extends ParserRuleContext {
	public ShardKeyword(): TerminalNode | undefined { return this.tryGetToken(PredaParser.ShardKeyword, 0); }
	public GlobalKeyword(): TerminalNode | undefined { return this.tryGetToken(PredaParser.GlobalKeyword, 0); }
	public AddressKeyword(): TerminalNode | undefined { return this.tryGetToken(PredaParser.AddressKeyword, 0); }
	public UintType(): TerminalNode | undefined { return this.tryGetToken(PredaParser.UintType, 0); }
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_scope; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterScope) {
			listener.enterScope(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitScope) {
			listener.exitScope(this);
		}
	}
}


export class StructDefinitionContext extends ParserRuleContext {
	public StructKeyword(): TerminalNode { return this.getToken(PredaParser.StructKeyword, 0); }
	public identifier(): IdentifierContext {
		return this.getRuleContext(0, IdentifierContext);
	}
	public doxygen(): DoxygenContext | undefined {
		return this.tryGetRuleContext(0, DoxygenContext);
	}
	public annotation(): AnnotationContext | undefined {
		return this.tryGetRuleContext(0, AnnotationContext);
	}
	public variableDeclaration(): VariableDeclarationContext[];
	public variableDeclaration(i: number): VariableDeclarationContext;
	public variableDeclaration(i?: number): VariableDeclarationContext | VariableDeclarationContext[] {
		if (i === undefined) {
			return this.getRuleContexts(VariableDeclarationContext);
		} else {
			return this.getRuleContext(i, VariableDeclarationContext);
		}
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_structDefinition; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterStructDefinition) {
			listener.enterStructDefinition(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitStructDefinition) {
			listener.exitStructDefinition(this);
		}
	}
}


export class InterfaceDefinitionContext extends ParserRuleContext {
	public InterfaceKeyword(): TerminalNode { return this.getToken(PredaParser.InterfaceKeyword, 0); }
	public identifier(): IdentifierContext {
		return this.getRuleContext(0, IdentifierContext);
	}
	public functionDeclaration(): FunctionDeclarationContext[];
	public functionDeclaration(i: number): FunctionDeclarationContext;
	public functionDeclaration(i?: number): FunctionDeclarationContext | FunctionDeclarationContext[] {
		if (i === undefined) {
			return this.getRuleContexts(FunctionDeclarationContext);
		} else {
			return this.getRuleContext(i, FunctionDeclarationContext);
		}
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_interfaceDefinition; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterInterfaceDefinition) {
			listener.enterInterfaceDefinition(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitInterfaceDefinition) {
			listener.exitInterfaceDefinition(this);
		}
	}
}


export class EnumDefinitionContext extends ParserRuleContext {
	public EnumKeyword(): TerminalNode { return this.getToken(PredaParser.EnumKeyword, 0); }
	public identifier(): IdentifierContext[];
	public identifier(i: number): IdentifierContext;
	public identifier(i?: number): IdentifierContext | IdentifierContext[] {
		if (i === undefined) {
			return this.getRuleContexts(IdentifierContext);
		} else {
			return this.getRuleContext(i, IdentifierContext);
		}
	}
	public doxygen(): DoxygenContext | undefined {
		return this.tryGetRuleContext(0, DoxygenContext);
	}
	public annotation(): AnnotationContext | undefined {
		return this.tryGetRuleContext(0, AnnotationContext);
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_enumDefinition; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterEnumDefinition) {
			listener.enterEnumDefinition(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitEnumDefinition) {
			listener.exitEnumDefinition(this);
		}
	}
}


export class FunctionDefinitionContext extends ParserRuleContext {
	public functionDeclaration(): FunctionDeclarationContext {
		return this.getRuleContext(0, FunctionDeclarationContext);
	}
	public statement(): StatementContext[];
	public statement(i: number): StatementContext;
	public statement(i?: number): StatementContext | StatementContext[] {
		if (i === undefined) {
			return this.getRuleContexts(StatementContext);
		} else {
			return this.getRuleContext(i, StatementContext);
		}
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_functionDefinition; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterFunctionDefinition) {
			listener.enterFunctionDefinition(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitFunctionDefinition) {
			listener.exitFunctionDefinition(this);
		}
	}
}


export class FunctionDeclarationContext extends ParserRuleContext {
	public FunctionKeyword(): TerminalNode { return this.getToken(PredaParser.FunctionKeyword, 0); }
	public identifier(): IdentifierContext {
		return this.getRuleContext(0, IdentifierContext);
	}
	public functionParameterList(): FunctionParameterListContext {
		return this.getRuleContext(0, FunctionParameterListContext);
	}
	public doxygen(): DoxygenContext | undefined {
		return this.tryGetRuleContext(0, DoxygenContext);
	}
	public annotation(): AnnotationContext | undefined {
		return this.tryGetRuleContext(0, AnnotationContext);
	}
	public scope(): ScopeContext | undefined {
		return this.tryGetRuleContext(0, ScopeContext);
	}
	public functionReturnTypeName(): FunctionReturnTypeNameContext | undefined {
		return this.tryGetRuleContext(0, FunctionReturnTypeNameContext);
	}
	public accessSpecifier(): AccessSpecifierContext[];
	public accessSpecifier(i: number): AccessSpecifierContext;
	public accessSpecifier(i?: number): AccessSpecifierContext | AccessSpecifierContext[] {
		if (i === undefined) {
			return this.getRuleContexts(AccessSpecifierContext);
		} else {
			return this.getRuleContext(i, AccessSpecifierContext);
		}
	}
	public ConstantKeyword(): TerminalNode | undefined { return this.tryGetToken(PredaParser.ConstantKeyword, 0); }
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_functionDeclaration; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterFunctionDeclaration) {
			listener.enterFunctionDeclaration(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitFunctionDeclaration) {
			listener.exitFunctionDeclaration(this);
		}
	}
}


export class FunctionReturnTypeNameContext extends ParserRuleContext {
	public typeName(): TypeNameContext {
		return this.getRuleContext(0, TypeNameContext);
	}
	public ConstantKeyword(): TerminalNode | undefined { return this.tryGetToken(PredaParser.ConstantKeyword, 0); }
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_functionReturnTypeName; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterFunctionReturnTypeName) {
			listener.enterFunctionReturnTypeName(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitFunctionReturnTypeName) {
			listener.exitFunctionReturnTypeName(this);
		}
	}
}


export class FunctionParameterListContext extends ParserRuleContext {
	public functionParameter(): FunctionParameterContext[];
	public functionParameter(i: number): FunctionParameterContext;
	public functionParameter(i?: number): FunctionParameterContext | FunctionParameterContext[] {
		if (i === undefined) {
			return this.getRuleContexts(FunctionParameterContext);
		} else {
			return this.getRuleContext(i, FunctionParameterContext);
		}
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_functionParameterList; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterFunctionParameterList) {
			listener.enterFunctionParameterList(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitFunctionParameterList) {
			listener.exitFunctionParameterList(this);
		}
	}
}


export class FunctionParameterContext extends ParserRuleContext {
	public typeName(): TypeNameContext {
		return this.getRuleContext(0, TypeNameContext);
	}
	public identifier(): IdentifierContext {
		return this.getRuleContext(0, IdentifierContext);
	}
	public ConstantKeyword(): TerminalNode | undefined { return this.tryGetToken(PredaParser.ConstantKeyword, 0); }
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_functionParameter; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterFunctionParameter) {
			listener.enterFunctionParameter(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitFunctionParameter) {
			listener.exitFunctionParameter(this);
		}
	}
}


export class AccessSpecifierContext extends ParserRuleContext {
	public PublicKeyword(): TerminalNode | undefined { return this.tryGetToken(PredaParser.PublicKeyword, 0); }
	public ExportKeyword(): TerminalNode | undefined { return this.tryGetToken(PredaParser.ExportKeyword, 0); }
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_accessSpecifier; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterAccessSpecifier) {
			listener.enterAccessSpecifier(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitAccessSpecifier) {
			listener.exitAccessSpecifier(this);
		}
	}
}


export class VariableDeclarationContext extends ParserRuleContext {
	public typeName(): TypeNameContext {
		return this.getRuleContext(0, TypeNameContext);
	}
	public identifier(): IdentifierContext {
		return this.getRuleContext(0, IdentifierContext);
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_variableDeclaration; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterVariableDeclaration) {
			listener.enterVariableDeclaration(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitVariableDeclaration) {
			listener.exitVariableDeclaration(this);
		}
	}
}


export class TypeNameOrAutoContext extends ParserRuleContext {
	public typeName(): TypeNameContext | undefined {
		return this.tryGetRuleContext(0, TypeNameContext);
	}
	public AutoKeyword(): TerminalNode | undefined { return this.tryGetToken(PredaParser.AutoKeyword, 0); }
	public ConstantKeyword(): TerminalNode | undefined { return this.tryGetToken(PredaParser.ConstantKeyword, 0); }
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_typeNameOrAuto; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterTypeNameOrAuto) {
			listener.enterTypeNameOrAuto(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitTypeNameOrAuto) {
			listener.exitTypeNameOrAuto(this);
		}
	}
}


export class TypeNameContext extends ParserRuleContext {
	public fundamentalTypeName(): FundamentalTypeNameContext | undefined {
		return this.tryGetRuleContext(0, FundamentalTypeNameContext);
	}
	public builtInContainerTypeName(): BuiltInContainerTypeNameContext | undefined {
		return this.tryGetRuleContext(0, BuiltInContainerTypeNameContext);
	}
	public userDefinedTypeName(): UserDefinedTypeNameContext | undefined {
		return this.tryGetRuleContext(0, UserDefinedTypeNameContext);
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_typeName; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterTypeName) {
			listener.enterTypeName(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitTypeName) {
			listener.exitTypeName(this);
		}
	}
}


export class FundamentalTypeNameContext extends ParserRuleContext {
	public IntType(): TerminalNode | undefined { return this.tryGetToken(PredaParser.IntType, 0); }
	public UintType(): TerminalNode | undefined { return this.tryGetToken(PredaParser.UintType, 0); }
	public FloatType(): TerminalNode | undefined { return this.tryGetToken(PredaParser.FloatType, 0); }
	public AddressKeyword(): TerminalNode | undefined { return this.tryGetToken(PredaParser.AddressKeyword, 0); }
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_fundamentalTypeName; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterFundamentalTypeName) {
			listener.enterFundamentalTypeName(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitFundamentalTypeName) {
			listener.exitFundamentalTypeName(this);
		}
	}
}


export class BuiltInContainerTypeNameContext extends ParserRuleContext {
	public mapTypeName(): MapTypeNameContext | undefined {
		return this.tryGetRuleContext(0, MapTypeNameContext);
	}
	public arrayTypeName(): ArrayTypeNameContext | undefined {
		return this.tryGetRuleContext(0, ArrayTypeNameContext);
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_builtInContainerTypeName; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterBuiltInContainerTypeName) {
			listener.enterBuiltInContainerTypeName(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitBuiltInContainerTypeName) {
			listener.exitBuiltInContainerTypeName(this);
		}
	}
}


export class MapKeyTypeNameContext extends ParserRuleContext {
	public IntType(): TerminalNode | undefined { return this.tryGetToken(PredaParser.IntType, 0); }
	public UintType(): TerminalNode | undefined { return this.tryGetToken(PredaParser.UintType, 0); }
	public FloatType(): TerminalNode | undefined { return this.tryGetToken(PredaParser.FloatType, 0); }
	public AddressKeyword(): TerminalNode | undefined { return this.tryGetToken(PredaParser.AddressKeyword, 0); }
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_mapKeyTypeName; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterMapKeyTypeName) {
			listener.enterMapKeyTypeName(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitMapKeyTypeName) {
			listener.exitMapKeyTypeName(this);
		}
	}
}


export class MapTypeNameContext extends ParserRuleContext {
	public mapKeyTypeName(): MapKeyTypeNameContext {
		return this.getRuleContext(0, MapKeyTypeNameContext);
	}
	public typeName(): TypeNameContext {
		return this.getRuleContext(0, TypeNameContext);
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_mapTypeName; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterMapTypeName) {
			listener.enterMapTypeName(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitMapTypeName) {
			listener.exitMapTypeName(this);
		}
	}
}


export class ArrayTypeNameContext extends ParserRuleContext {
	public typeName(): TypeNameContext {
		return this.getRuleContext(0, TypeNameContext);
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_arrayTypeName; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterArrayTypeName) {
			listener.enterArrayTypeName(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitArrayTypeName) {
			listener.exitArrayTypeName(this);
		}
	}
}


export class UserDefinedTypeNameContext extends ParserRuleContext {
	public identifier(): IdentifierContext[];
	public identifier(i: number): IdentifierContext;
	public identifier(i?: number): IdentifierContext | IdentifierContext[] {
		if (i === undefined) {
			return this.getRuleContexts(IdentifierContext);
		} else {
			return this.getRuleContext(i, IdentifierContext);
		}
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_userDefinedTypeName; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterUserDefinedTypeName) {
			listener.enterUserDefinedTypeName(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitUserDefinedTypeName) {
			listener.exitUserDefinedTypeName(this);
		}
	}
}


export class UserBlockStatementContext extends ParserRuleContext {
	public statement(): StatementContext[];
	public statement(i: number): StatementContext;
	public statement(i?: number): StatementContext | StatementContext[] {
		if (i === undefined) {
			return this.getRuleContexts(StatementContext);
		} else {
			return this.getRuleContext(i, StatementContext);
		}
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_userBlockStatement; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterUserBlockStatement) {
			listener.enterUserBlockStatement(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitUserBlockStatement) {
			listener.exitUserBlockStatement(this);
		}
	}
}


export class StatementContext extends ParserRuleContext {
	public ifStatement(): IfStatementContext | undefined {
		return this.tryGetRuleContext(0, IfStatementContext);
	}
	public whileStatement(): WhileStatementContext | undefined {
		return this.tryGetRuleContext(0, WhileStatementContext);
	}
	public forStatement(): ForStatementContext | undefined {
		return this.tryGetRuleContext(0, ForStatementContext);
	}
	public userBlockStatement(): UserBlockStatementContext | undefined {
		return this.tryGetRuleContext(0, UserBlockStatementContext);
	}
	public doWhileStatement(): DoWhileStatementContext | undefined {
		return this.tryGetRuleContext(0, DoWhileStatementContext);
	}
	public continueStatement(): ContinueStatementContext | undefined {
		return this.tryGetRuleContext(0, ContinueStatementContext);
	}
	public breakStatement(): BreakStatementContext | undefined {
		return this.tryGetRuleContext(0, BreakStatementContext);
	}
	public returnStatement(): ReturnStatementContext | undefined {
		return this.tryGetRuleContext(0, ReturnStatementContext);
	}
	public relayStatement(): RelayStatementContext | undefined {
		return this.tryGetRuleContext(0, RelayStatementContext);
	}
	public variableDeclarationStatement(): VariableDeclarationStatementContext | undefined {
		return this.tryGetRuleContext(0, VariableDeclarationStatementContext);
	}
	public expressionStatement(): ExpressionStatementContext | undefined {
		return this.tryGetRuleContext(0, ExpressionStatementContext);
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_statement; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterStatement) {
			listener.enterStatement(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitStatement) {
			listener.exitStatement(this);
		}
	}
}


export class ExpressionStatementContext extends ParserRuleContext {
	public expression(): ExpressionContext {
		return this.getRuleContext(0, ExpressionContext);
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_expressionStatement; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterExpressionStatement) {
			listener.enterExpressionStatement(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitExpressionStatement) {
			listener.exitExpressionStatement(this);
		}
	}
}


export class IfStatementContext extends ParserRuleContext {
	public ifWithBlock(): IfWithBlockContext {
		return this.getRuleContext(0, IfWithBlockContext);
	}
	public elseIfWithBlock(): ElseIfWithBlockContext[];
	public elseIfWithBlock(i: number): ElseIfWithBlockContext;
	public elseIfWithBlock(i?: number): ElseIfWithBlockContext | ElseIfWithBlockContext[] {
		if (i === undefined) {
			return this.getRuleContexts(ElseIfWithBlockContext);
		} else {
			return this.getRuleContext(i, ElseIfWithBlockContext);
		}
	}
	public elseWithBlock(): ElseWithBlockContext | undefined {
		return this.tryGetRuleContext(0, ElseWithBlockContext);
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_ifStatement; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterIfStatement) {
			listener.enterIfStatement(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitIfStatement) {
			listener.exitIfStatement(this);
		}
	}
}


export class IfWithBlockContext extends ParserRuleContext {
	public IfKeyword(): TerminalNode { return this.getToken(PredaParser.IfKeyword, 0); }
	public expression(): ExpressionContext {
		return this.getRuleContext(0, ExpressionContext);
	}
	public statement(): StatementContext[];
	public statement(i: number): StatementContext;
	public statement(i?: number): StatementContext | StatementContext[] {
		if (i === undefined) {
			return this.getRuleContexts(StatementContext);
		} else {
			return this.getRuleContext(i, StatementContext);
		}
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_ifWithBlock; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterIfWithBlock) {
			listener.enterIfWithBlock(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitIfWithBlock) {
			listener.exitIfWithBlock(this);
		}
	}
}


export class ElseWithBlockContext extends ParserRuleContext {
	public ElseKeyword(): TerminalNode { return this.getToken(PredaParser.ElseKeyword, 0); }
	public statement(): StatementContext[];
	public statement(i: number): StatementContext;
	public statement(i?: number): StatementContext | StatementContext[] {
		if (i === undefined) {
			return this.getRuleContexts(StatementContext);
		} else {
			return this.getRuleContext(i, StatementContext);
		}
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_elseWithBlock; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterElseWithBlock) {
			listener.enterElseWithBlock(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitElseWithBlock) {
			listener.exitElseWithBlock(this);
		}
	}
}


export class ElseIfWithBlockContext extends ParserRuleContext {
	public ElseKeyword(): TerminalNode { return this.getToken(PredaParser.ElseKeyword, 0); }
	public IfKeyword(): TerminalNode { return this.getToken(PredaParser.IfKeyword, 0); }
	public expression(): ExpressionContext {
		return this.getRuleContext(0, ExpressionContext);
	}
	public statement(): StatementContext[];
	public statement(i: number): StatementContext;
	public statement(i?: number): StatementContext | StatementContext[] {
		if (i === undefined) {
			return this.getRuleContexts(StatementContext);
		} else {
			return this.getRuleContext(i, StatementContext);
		}
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_elseIfWithBlock; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterElseIfWithBlock) {
			listener.enterElseIfWithBlock(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitElseIfWithBlock) {
			listener.exitElseIfWithBlock(this);
		}
	}
}


export class WhileStatementContext extends ParserRuleContext {
	public expression(): ExpressionContext {
		return this.getRuleContext(0, ExpressionContext);
	}
	public statement(): StatementContext[];
	public statement(i: number): StatementContext;
	public statement(i?: number): StatementContext | StatementContext[] {
		if (i === undefined) {
			return this.getRuleContexts(StatementContext);
		} else {
			return this.getRuleContext(i, StatementContext);
		}
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_whileStatement; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterWhileStatement) {
			listener.enterWhileStatement(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitWhileStatement) {
			listener.exitWhileStatement(this);
		}
	}
}


export class RelayStatementContext extends ParserRuleContext {
	public RelayKeyword(): TerminalNode { return this.getToken(PredaParser.RelayKeyword, 0); }
	public relayType(): RelayTypeContext {
		return this.getRuleContext(0, RelayTypeContext);
	}
	public relayLambdaDefinition(): RelayLambdaDefinitionContext | undefined {
		return this.tryGetRuleContext(0, RelayLambdaDefinitionContext);
	}
	public identifier(): IdentifierContext | undefined {
		return this.tryGetRuleContext(0, IdentifierContext);
	}
	public functionCallArguments(): FunctionCallArgumentsContext | undefined {
		return this.tryGetRuleContext(0, FunctionCallArgumentsContext);
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_relayStatement; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterRelayStatement) {
			listener.enterRelayStatement(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitRelayStatement) {
			listener.exitRelayStatement(this);
		}
	}
}


export class RelayTypeContext extends ParserRuleContext {
	public expression(): ExpressionContext | undefined {
		return this.tryGetRuleContext(0, ExpressionContext);
	}
	public ShardsKeyword(): TerminalNode | undefined { return this.tryGetToken(PredaParser.ShardsKeyword, 0); }
	public GlobalKeyword(): TerminalNode | undefined { return this.tryGetToken(PredaParser.GlobalKeyword, 0); }
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_relayType; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterRelayType) {
			listener.enterRelayType(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitRelayType) {
			listener.exitRelayType(this);
		}
	}
}


export class RelayLambdaDefinitionContext extends ParserRuleContext {
	public relayLambdaParameter(): RelayLambdaParameterContext[];
	public relayLambdaParameter(i: number): RelayLambdaParameterContext;
	public relayLambdaParameter(i?: number): RelayLambdaParameterContext | RelayLambdaParameterContext[] {
		if (i === undefined) {
			return this.getRuleContexts(RelayLambdaParameterContext);
		} else {
			return this.getRuleContext(i, RelayLambdaParameterContext);
		}
	}
	public ConstantKeyword(): TerminalNode | undefined { return this.tryGetToken(PredaParser.ConstantKeyword, 0); }
	public statement(): StatementContext[];
	public statement(i: number): StatementContext;
	public statement(i?: number): StatementContext | StatementContext[] {
		if (i === undefined) {
			return this.getRuleContexts(StatementContext);
		} else {
			return this.getRuleContext(i, StatementContext);
		}
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_relayLambdaDefinition; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterRelayLambdaDefinition) {
			listener.enterRelayLambdaDefinition(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitRelayLambdaDefinition) {
			listener.exitRelayLambdaDefinition(this);
		}
	}
}


export class RelayLambdaParameterContext extends ParserRuleContext {
	public typeNameOrAuto(): TypeNameOrAutoContext | undefined {
		return this.tryGetRuleContext(0, TypeNameOrAutoContext);
	}
	public identifier(): IdentifierContext | undefined {
		return this.tryGetRuleContext(0, IdentifierContext);
	}
	public expression(): ExpressionContext | undefined {
		return this.tryGetRuleContext(0, ExpressionContext);
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_relayLambdaParameter; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterRelayLambdaParameter) {
			listener.enterRelayLambdaParameter(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitRelayLambdaParameter) {
			listener.exitRelayLambdaParameter(this);
		}
	}
}


export class ForStatementContext extends ParserRuleContext {
	public _firstExpression!: ExpressionContext;
	public _secondExpression!: ExpressionContext;
	public _thirdExpression!: ExpressionContext;
	public localVariableDeclaration(): LocalVariableDeclarationContext | undefined {
		return this.tryGetRuleContext(0, LocalVariableDeclarationContext);
	}
	public statement(): StatementContext[];
	public statement(i: number): StatementContext;
	public statement(i?: number): StatementContext | StatementContext[] {
		if (i === undefined) {
			return this.getRuleContexts(StatementContext);
		} else {
			return this.getRuleContext(i, StatementContext);
		}
	}
	public expression(): ExpressionContext[];
	public expression(i: number): ExpressionContext;
	public expression(i?: number): ExpressionContext | ExpressionContext[] {
		if (i === undefined) {
			return this.getRuleContexts(ExpressionContext);
		} else {
			return this.getRuleContext(i, ExpressionContext);
		}
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_forStatement; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterForStatement) {
			listener.enterForStatement(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitForStatement) {
			listener.exitForStatement(this);
		}
	}
}


export class DoWhileStatementContext extends ParserRuleContext {
	public expression(): ExpressionContext {
		return this.getRuleContext(0, ExpressionContext);
	}
	public statement(): StatementContext[];
	public statement(i: number): StatementContext;
	public statement(i?: number): StatementContext | StatementContext[] {
		if (i === undefined) {
			return this.getRuleContexts(StatementContext);
		} else {
			return this.getRuleContext(i, StatementContext);
		}
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_doWhileStatement; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterDoWhileStatement) {
			listener.enterDoWhileStatement(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitDoWhileStatement) {
			listener.exitDoWhileStatement(this);
		}
	}
}


export class ContinueStatementContext extends ParserRuleContext {
	public ContinueKeyword(): TerminalNode { return this.getToken(PredaParser.ContinueKeyword, 0); }
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_continueStatement; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterContinueStatement) {
			listener.enterContinueStatement(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitContinueStatement) {
			listener.exitContinueStatement(this);
		}
	}
}


export class BreakStatementContext extends ParserRuleContext {
	public BreakKeyword(): TerminalNode { return this.getToken(PredaParser.BreakKeyword, 0); }
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_breakStatement; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterBreakStatement) {
			listener.enterBreakStatement(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitBreakStatement) {
			listener.exitBreakStatement(this);
		}
	}
}


export class ReturnStatementContext extends ParserRuleContext {
	public expression(): ExpressionContext | undefined {
		return this.tryGetRuleContext(0, ExpressionContext);
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_returnStatement; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterReturnStatement) {
			listener.enterReturnStatement(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitReturnStatement) {
			listener.exitReturnStatement(this);
		}
	}
}


export class VariableDeclarationStatementContext extends ParserRuleContext {
	public localVariableDeclaration(): LocalVariableDeclarationContext {
		return this.getRuleContext(0, LocalVariableDeclarationContext);
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_variableDeclarationStatement; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterVariableDeclarationStatement) {
			listener.enterVariableDeclarationStatement(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitVariableDeclarationStatement) {
			listener.exitVariableDeclarationStatement(this);
		}
	}
}


export class LocalVariableDeclarationContext extends ParserRuleContext {
	public typeNameOrAuto(): TypeNameOrAutoContext {
		return this.getRuleContext(0, TypeNameOrAutoContext);
	}
	public identifier(): IdentifierContext {
		return this.getRuleContext(0, IdentifierContext);
	}
	public expression(): ExpressionContext | undefined {
		return this.tryGetRuleContext(0, ExpressionContext);
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_localVariableDeclaration; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterLocalVariableDeclaration) {
			listener.enterLocalVariableDeclaration(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitLocalVariableDeclaration) {
			listener.exitLocalVariableDeclaration(this);
		}
	}
}


export class ExpressionContext extends ParserRuleContext {
	public expressionType: any = -1;
	public expression(): ExpressionContext[];
	public expression(i: number): ExpressionContext;
	public expression(i?: number): ExpressionContext | ExpressionContext[] {
		if (i === undefined) {
			return this.getRuleContexts(ExpressionContext);
		} else {
			return this.getRuleContext(i, ExpressionContext);
		}
	}
	public functionCallArguments(): FunctionCallArgumentsContext | undefined {
		return this.tryGetRuleContext(0, FunctionCallArgumentsContext);
	}
	public identifier(): IdentifierContext | undefined {
		return this.tryGetRuleContext(0, IdentifierContext);
	}
	public primaryExpression(): PrimaryExpressionContext | undefined {
		return this.tryGetRuleContext(0, PrimaryExpressionContext);
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_expression; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterExpression) {
			listener.enterExpression(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitExpression) {
			listener.exitExpression(this);
		}
	}
}


export class PrimaryExpressionContext extends ParserRuleContext {
	public BooleanLiteral(): TerminalNode | undefined { return this.tryGetToken(PredaParser.BooleanLiteral, 0); }
	public DecimalIntegerLiteral(): TerminalNode | undefined { return this.tryGetToken(PredaParser.DecimalIntegerLiteral, 0); }
	public DecimalFloatLiteral(): TerminalNode | undefined { return this.tryGetToken(PredaParser.DecimalFloatLiteral, 0); }
	public HexIntegerLiteral(): TerminalNode | undefined { return this.tryGetToken(PredaParser.HexIntegerLiteral, 0); }
	public DecimalBigIntegerLiteral(): TerminalNode | undefined { return this.tryGetToken(PredaParser.DecimalBigIntegerLiteral, 0); }
	public HexBigIntegerLiteral(): TerminalNode | undefined { return this.tryGetToken(PredaParser.HexBigIntegerLiteral, 0); }
	public StringLiteral(): TerminalNode | undefined { return this.tryGetToken(PredaParser.StringLiteral, 0); }
	public AddressLiteral(): TerminalNode | undefined { return this.tryGetToken(PredaParser.AddressLiteral, 0); }
	public HashLiteral(): TerminalNode | undefined { return this.tryGetToken(PredaParser.HashLiteral, 0); }
	public identifier(): IdentifierContext | undefined {
		return this.tryGetRuleContext(0, IdentifierContext);
	}
	public fundamentalTypeName(): FundamentalTypeNameContext | undefined {
		return this.tryGetRuleContext(0, FundamentalTypeNameContext);
	}
	public builtInContainerTypeName(): BuiltInContainerTypeNameContext | undefined {
		return this.tryGetRuleContext(0, BuiltInContainerTypeNameContext);
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_primaryExpression; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterPrimaryExpression) {
			listener.enterPrimaryExpression(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitPrimaryExpression) {
			listener.exitPrimaryExpression(this);
		}
	}
}


export class FunctionCallArgumentsContext extends ParserRuleContext {
	public expression(): ExpressionContext[];
	public expression(i: number): ExpressionContext;
	public expression(i?: number): ExpressionContext | ExpressionContext[] {
		if (i === undefined) {
			return this.getRuleContexts(ExpressionContext);
		} else {
			return this.getRuleContext(i, ExpressionContext);
		}
	}
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_functionCallArguments; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterFunctionCallArguments) {
			listener.enterFunctionCallArguments(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitFunctionCallArguments) {
			listener.exitFunctionCallArguments(this);
		}
	}
}


export class IdentifierContext extends ParserRuleContext {
	public Identifier(): TerminalNode { return this.getToken(PredaParser.Identifier, 0); }
	constructor(parent: ParserRuleContext | undefined, invokingState: number) {
		super(parent, invokingState);
	}
	// @Override
	public get ruleIndex(): number { return PredaParser.RULE_identifier; }
	// @Override
	public enterRule(listener: PredaListener): void {
		if (listener.enterIdentifier) {
			listener.enterIdentifier(this);
		}
	}
	// @Override
	public exitRule(listener: PredaListener): void {
		if (listener.exitIdentifier) {
			listener.exitIdentifier(this);
		}
	}
}


