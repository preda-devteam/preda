#pragma once

#include "antlr_generated/PredaParser.h"

#include "transpiler.h"
#include "transpiler/PredaTranspiler.h"
#include "ErrorPortal.h"
#include "IdentifierHub.h"
#include "FunctionCallGraph.h"

class ExpressionParser
{
	using ConcreteTypePtr = transpiler::ConcreteTypePtr;

public:
	struct ExpressionResult
	{
		std::string text;							// text to be output to code stream
		transpiler::QualifiedConcreteType type;		// type of expression, if it's a typename expression, only type.baseConcreteType is relevant
		bool bIsTypeName = false;					// whether this expression is a type name instead of a value
	};

private:
	transpiler::PredaTranspilerContext *m_pTranspilerCtx = nullptr;
	ErrorPortal *m_pErrorPortal = nullptr;
	IdentifierHub *m_pIdentifierHub = nullptr;
	FunctionCallGraph *m_pFunctionCallGraph = nullptr;
	const transpiler::PredaTranspilerOptions* m_pOptions = nullptr;

	struct ImportedContractData {
		std::vector<ConcreteTypePtr> constructorParamList;
		uint32_t importSlotIndex;
	};

	std::map<ConcreteTypePtr, ImportedContractData> m_importedContractsData;

private:
	bool ParsePrimaryExpression(PredaParser::PrimaryExpressionContext *ctx, ExpressionResult &outResult, bool requireConst = false);
	bool ParseExpression_Internal(PredaParser::ExpressionContext *ctx, ExpressionResult &outResult, bool requireConst = false);
	bool ParseIdentifier_Internal(PredaParser::IdentifierContext *ctx, ExpressionResult &outResult, bool requireConst = false);
	bool GenerateDebugPrintArguments(const std::vector<PredaParser::ExpressionContext*>& argCtxs, std::string& outSynthesizedArgumentsString);
	bool ValidateExpressionResult(const ExpressionResult &result);

public:
	void SetTranspilerContext(transpiler::PredaTranspilerContext *pCtx)
	{
		m_pTranspilerCtx = pCtx;
	}
	void SetErrorPortal(ErrorPortal *pPortal)
	{
		m_pErrorPortal = pPortal;
	}
	void SetIdentifierHub(IdentifierHub *pHub)
	{
		m_pIdentifierHub = pHub;
	}
	void SetFunctionCallGraph(FunctionCallGraph *pGraph)
	{
		m_pFunctionCallGraph = pGraph;
	}
	void SetOptions(const transpiler::PredaTranspilerOptions* pOptions)
	{
		m_pOptions = pOptions;
	}

	bool AddImportedContract(ConcreteTypePtr contract, const std::vector<ConcreteTypePtr>& paramList, uint32_t id);

	int FindMatchingOverloadedFunction(const ConcreteTypePtr &calledFunction, PredaParser::FunctionCallArgumentsContext *ctx, std::string &outSynthesizedArgumentsString);
	bool ParseExpression(PredaParser::ExpressionContext *ctx, ExpressionResult &outResult, bool requireConst = false);
	bool ParseIdentifierAsExpression(PredaParser::IdentifierContext *ctx, ExpressionResult &outResult);
};