#pragma once

#include "antlr_generated/PredaParser.h"

#include "transpiler.h"
#include "transpiler/PredaTranspiler.h"
#include "ErrorPortal.h"

class IdentifierHub
{
	using ConcreteTypePtr = transpiler::ConcreteTypePtr;

	transpiler::PredaTranspilerContext *m_pTranspilerCtx = nullptr;
	ErrorPortal *m_pErrorPortal = nullptr;
private:
	std::map<transpiler::DefinedIdentifierPtr, std::string> constantVarMap;
public:
	void SetTranspilerContext(transpiler::PredaTranspilerContext *pCtx)
	{
		m_pTranspilerCtx = pCtx;
	}
	void SetErrorPortal(ErrorPortal *pPortal)
	{
		m_pErrorPortal = pPortal;
	}
	void AddConstMemberVar(transpiler::DefinedIdentifierPtr idPtr, std::string definition)
	{
		constantVarMap[idPtr] = definition;
	}
	bool GetConstMemberDefinition(transpiler::DefinedIdentifierPtr idPtr, std::string& definition)
	{
		auto iter = constantVarMap.find(idPtr);
		if (iter == constantVarMap.end())
		{
			definition.clear();
			return false;
		}
		definition = iter->second;
		return true;
	}
	bool FindExistingIdentifier(const std::string &typeName, ConcreteTypePtr *outType, transpiler::DefinedIdentifierPtr *outDefinedIdentifier, ConcreteTypePtr *outOuterType = nullptr);
	bool ValidateNewIdentifier(const std::string &typeName);
	bool ValidateNewIdentifier(PredaParser::IdentifierContext *ctx);
	ConcreteTypePtr GetConcreteTypeFromContextText(antlr4::ParserRuleContext *ctx);
	ConcreteTypePtr GetTypeFromBuiltInContainerTypeNameContext(PredaParser::BuiltInContainerTypeNameContext *ctx);
	ConcreteTypePtr GetTypeFromTypeNameContext(PredaParser::TypeNameContext *ctx);
};
