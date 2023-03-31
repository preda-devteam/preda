#pragma once
#include "antlr_generated/PredaLexer.h"
#include "antlr_generated/PredaParser.h"
#include "antlr_generated/PredaBaseListener.h"

#include "transpiler/PredaTranspiler.h"
#include "transpiler/PredaBuiltInConcreteTypes.h"
#include "PredaParseTreeWalker.h"
#include "CodeSerializer.h"
#include "transpiler.h"
#include "ErrorPortal.h"
#include "IdentifierHub.h"
#include "FunctionCallGraph.h"
#include "ExpressionParser.h"

#include <tuple>

class PredaPreCompileListener : public PredaBaseListener {
	private:
		virtual void enterPredaSource(PredaParser::PredaSourceContext * /*ctx*/) override;
		bool ProcessImportDirective(const PredaParser::ImportDirectiveContext *ctx);
	public:
		std::string m_currentDAppName;
		std::string m_currentContractName;
		void SetContractDAppNameId(const char* dAppName){
			m_currentDAppName = dAppName;
		}

		std::vector<std::string> m_dependentContracts;
};

class PredaRealListener : public PredaBaseListener, public antlr4::BaseErrorListener {
	using ConcreteTypePtr = transpiler::ConcreteTypePtr;
public:
	PredaRealListener()
	{
		m_identifierHub.SetTranspilerContext(&m_transpilerCtx);
		m_identifierHub.SetErrorPortal(&m_errorPortal);

		m_expressionParser.SetTranspilerContext(&m_transpilerCtx);
		m_expressionParser.SetErrorPortal(&m_errorPortal);
		m_expressionParser.SetIdentifierHub(&m_identifierHub);
		m_expressionParser.SetFunctionCallGraph(&m_functionCallGraph);
	}

	transpiler::PredaTranspilerContext m_transpilerCtx;

	bool m_lastStatementInFunctionIsReturnStatement = false;

	std::vector<std::ostringstream> codeStreamStack;
	CodeSerializer codeSerializer;

	struct ForwardDeclaredContractFunction
	{
		PredaParser::FunctionDefinitionContext *ctx;
		transpiler::FunctionRef declaredFunc;
	};
	std::map<PredaParser::FunctionDefinitionContext*, size_t> m_functionDefinitionContext2ForwardDeclaredFunctions;
	std::vector<ForwardDeclaredContractFunction> m_forwardDeclaredFunctions;
	std::vector<std::pair<PredaParser::StateVariableDeclarationContext*, transpiler::DefinedIdentifier>> m_definedStateVariables;
	std::vector<std::pair<PredaParser::StructDefinitionContext*, ConcreteTypePtr>> m_definedStructs;
	std::vector<std::pair<PredaParser::EnumDefinitionContext*, ConcreteTypePtr>> m_definedEnums;
	std::vector<ConcreteTypePtr> m_definedInterfaces;

	ErrorPortal m_errorPortal;
	IdentifierHub m_identifierHub;
	FunctionCallGraph m_functionCallGraph;
	ExpressionParser m_expressionParser;

	virtual void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token * offendingSymbol, size_t line, size_t charPositionInLine,
		const std::string &msg, std::exception_ptr e) override
	{
		m_errorPortal.AddSyntaxError((uint32_t)line, (uint32_t)charPositionInLine, msg);
	}

private:
	std::vector<transpiler::FunctionRef> m_exportedFunctions;
	ForwardDeclaredContractFunction* m_curFunc; //current processing function in TraverseAllFunctions()
public:
	struct ExportedFunctionMeta
	{
		std::string name;
		std::string doxygenComment;
		std::string returnType;
		std::vector<std::string> parameterType;
		std::vector<std::string> parameterName;
		uint32_t flags;
	};

	std::vector<ExportedFunctionMeta> m_exportedFunctionsMeta;

	struct ExportedInterface
	{
		std::string name;
		std::vector<ExportedFunctionMeta> functions;
	};

	std::vector<ExportedInterface> m_exportedInterface;

	struct ImplementedInterface
	{
		std::string fullName;
		std::vector<uint32_t> functionIds;
	};
	std::vector<ImplementedInterface> m_implementedInterfaces;

	std::string m_stateVariableSignature[4];
	bool m_stateVariableHasBlob[4];
	bool m_stateVariableHasAsset[4];
	std::vector<std::string> m_stateVariableDoxygenComment[4];

	struct ContractEnum
	{
		std::string doxygenComment;
		std::string name;
		std::vector<std::string> enumerators;
	};
	std::vector<ContractEnum> m_exportedEnums;

	struct ExportedStruct
	{
		std::string name;
		std::string doxygenComment;
		std::vector<std::pair<std::string, std::string>> members;
	};
	std::vector<ExportedStruct> m_exportedStructs;

	std::string m_currentDAppName;
	std::string m_currentContractName;
	std::string m_currentContractUniqueIdentifierStr;
	std::string m_currentContractNamespace;
	std::string m_currentContractOutputName;
	std::string m_currentDoxygenComment;
	std::map<std::string, std::string> m_contractAliasToFullName;
	std::map<std::string, std::string> m_contractFullNameToAlias;
	std::map<std::string, std::string> m_contractFullNameToImportName;
	std::vector<std::string> m_importedContracts;
	std::map<std::string, ConcreteTypePtr> m_importedContractsType;
	std::set<std::string> m_failedImportContracts;

	int32_t m_globalDeployFunctionExportIdx = -1;
	int32_t m_shardScaleOutFunctionExportIdx = -1;

	void SetContractDAppNameId(const char *dAppName)
	{
		m_currentDAppName = dAppName;
	}
	PredaParseTreeWalker *m_pWalker = nullptr;
	void SetWalker(PredaParseTreeWalker *pWalker)
	{
		m_pWalker = pWalker;
	}
	const transpiler::PredaTranspilerOptions* m_pOptions = nullptr;
	void SetOptions(const transpiler::PredaTranspilerOptions* pOptions)
	{
		m_pOptions = pOptions;
		m_expressionParser.SetOptions(pOptions);
	}

	transpiler::IContractSymbolDatabase *m_pContractSymbolDatabase;
	void SetContractSymbolDatabase(transpiler::IContractSymbolDatabase *pContractSymbolDatabase)
	{
		m_pContractSymbolDatabase = pContractSymbolDatabase;
	}

private:
	enum class RelayType {
		Address,
		Shards,
		Global,
	};

	struct PendingRelayLambda
	{
		PendingRelayLambda(PredaParser::RelayLambdaDefinitionContext *ctx, const std::vector<transpiler::QualifiedConcreteType> &types, RelayType type, size_t slot, ForwardDeclaredContractFunction* base)
			: pDefinitionCtx(ctx), paramTypes(types), relayType(type), exportFuncSlot(slot), baseFunc(base)
		{
		}
		PredaParser::RelayLambdaDefinitionContext *pDefinitionCtx;
		std::vector<transpiler::QualifiedConcreteType> paramTypes;
		RelayType relayType;
		size_t exportFuncSlot;
		ForwardDeclaredContractFunction* baseFunc; //function name where the relay lambda is defined
	};

	std::vector<PendingRelayLambda> m_pendingRelayLambdas;
	size_t DeclareRelayLambdaFunction(PredaParser::RelayLambdaDefinitionContext *ctx, const std::vector<transpiler::QualifiedConcreteType> &paramTypes, RelayType type, ForwardDeclaredContractFunction* base);
	void DefinePendingRelayLambdas();

private:
	transpiler::DefinedIdentifierPtr DefineFunctionLocalVariable(ConcreteTypePtr pType, PredaParser::IdentifierContext *identifierCtx, bool bIsConst, uint32_t flags);
	transpiler::DefinedIdentifierPtr DefineFunctionLocalVariable(ConcreteTypePtr pType, const std::string &identifierName, bool bIsConst, uint32_t flags);
	bool GenFunctionSignatureFromFunctionDeclareCtx(transpiler::FunctionSignature& outSig, PredaParser::FunctionDeclarationContext* declCtx);
	void ForwardDeclareFunction(PredaParser::FunctionDefinitionContext *ctx);
	void DefineStateVariable(PredaParser::StateVariableDeclarationContext *ctx);
	void DefineStruct(PredaParser::StructDefinitionContext *ctx);
	void DefineEnum(PredaParser::EnumDefinitionContext *ctx);
	void DefineInterface(PredaParser::InterfaceDefinitionContext *ctx);
	ConcreteTypePtr GetTypeFromExportedTypeName(const char *typeName);
	ConcreteTypePtr GetTypeFromExportedTypeNameStrStream(std::stringstream &inoutStream);
	void ProcessDirectives(const std::vector<PredaParser::DirectiveContext *> &vDirectiveCtx);
	void ProcessImportDirective(const PredaParser::ImportDirectiveContext *ctx);
	std::string ProcessDoxygen(PredaParser::DoxygenContext *ctx);
	ConcreteTypePtr ImportContractSymbols(transpiler::IContractSymbols *pContractSymbols, const std::string contractImportName);
	bool ImportContract(const std::string &contractFullName);
	void GenerateAuxiliaryFunctions();
	void GenerateExportFunctionMeta();
	void GenerateExportInterface();
	void VerifyImplementedInterface(const std::vector<PredaParser::InterfaceRefContext*> refs);
	bool ProcessLocalVariableDeclaration(PredaParser::LocalVariableDeclarationContext *ctx, std::string &outRes);
	bool ReservedFunctions_OnDeclare(std::string &name, transpiler::FunctionSignature &signature);
	void ReservedFunctions_PostExport(const std::string &name, const transpiler::FunctionSignature &signature, size_t exportIdx);
	void ReservedFunctions_PostFlagPropagate(const std::string &name, const transpiler::FunctionSignature &signature);
	size_t ExportFunction(transpiler::FunctionRef functionRef);
	void PropagateFunctionFlagAcrossCallingGraph();
	void TraverseAllFunctions();

public:
	// interface inherited from PredaListener
	virtual void enterVariableDeclarationStatement(PredaParser::VariableDeclarationStatementContext *ctx) override;
	virtual void enterExpressionStatement(PredaParser::ExpressionStatementContext *ctx) override;
	virtual void enterReturnStatement(PredaParser::ReturnStatementContext *ctx) override;
	virtual void enterIfWithBlock(PredaParser::IfWithBlockContext *ctx) override;
	virtual void exitIfWithBlock(PredaParser::IfWithBlockContext *ctx) override;
	virtual void enterElseWithBlock(PredaParser::ElseWithBlockContext *ctx) override;
	virtual void exitElseWithBlock(PredaParser::ElseWithBlockContext *ctx) override;
	virtual void enterElseIfWithBlock(PredaParser::ElseIfWithBlockContext *ctx) override;
	virtual void exitElseIfWithBlock(PredaParser::ElseIfWithBlockContext *ctx) override;
	virtual void enterWhileStatement(PredaParser::WhileStatementContext *ctx) override;
	virtual void exitWhileStatement(PredaParser::WhileStatementContext *ctx) override;
	virtual void enterDoWhileStatement(PredaParser::DoWhileStatementContext *ctx) override;
	virtual void exitDoWhileStatement(PredaParser::DoWhileStatementContext *ctx) override;
	virtual void enterForStatement(PredaParser::ForStatementContext *ctx) override;
	virtual void exitForStatement(PredaParser::ForStatementContext *ctx) override;
	virtual void enterUserBlockStatement(PredaParser::UserBlockStatementContext *ctx) override;
	virtual void exitUserBlockStatement(PredaParser::UserBlockStatementContext *ctx) override;
	virtual void enterRelayStatement(PredaParser::RelayStatementContext *ctx) override;
	virtual void enterContinueStatement(PredaParser::ContinueStatementContext *ctx) override;
	virtual void exitContinueStatement(PredaParser::ContinueStatementContext *ctx) override;
	virtual void enterBreakStatement(PredaParser::BreakStatementContext *ctx) override;
	virtual void exitBreakStatement(PredaParser::BreakStatementContext *ctx) override;
	virtual void enterStatement(PredaParser::StatementContext *ctx) override;
	virtual void exitStatement(PredaParser::StatementContext *ctx) override;
	virtual void enterContractDefinition(PredaParser::ContractDefinitionContext *ctx) override;
	virtual void exitContractDefinition(PredaParser::ContractDefinitionContext *ctx) override;
	virtual void enterFunctionDefinition(PredaParser::FunctionDefinitionContext *ctx) override;
	virtual void exitFunctionDefinition(PredaParser::FunctionDefinitionContext *ctx) override;
	//virtual void enterRelayLambdaStatement(PredaParser::RelayLambdaStatementContext *ctx) override;
	//virtual void exitRelayLambdaStatement(PredaParser::RelayLambdaStatementContext *ctx) override;
	virtual void enterRelayLambdaDefinition(PredaParser::RelayLambdaDefinitionContext *ctx) override;
	//virtual void exitRelayLambdaDefinition(PredaParser::RelayLambdaDefinitionContext *ctx) override;
	virtual void enterPredaSource(PredaParser::PredaSourceContext * /*ctx*/) override;
  	virtual void enterDoxygen(PredaParser::DoxygenContext * /*ctx*/) override;
};
