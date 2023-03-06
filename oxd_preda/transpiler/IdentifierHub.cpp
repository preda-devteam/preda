#include "PredaRealListener.h"
#include "IdentifierHub.h"

using ConcreteTypePtr = transpiler::ConcreteTypePtr;

bool FindExistingIdentifierInType(ConcreteTypePtr type, const std::string &typeName, ConcreteTypePtr *outType, transpiler::DefinedIdentifierPtr *outDefinedIdentifier, ConcreteTypePtr *outOuterType)
{
	ConcreteTypePtr resType = type->FindInnerConcreteType(typeName);

	if (resType != nullptr)
	{
		if (resType->typeCategory == transpiler::ConcreteType::AliasType)
			resType = resType->realType;
		assert(resType != nullptr && resType->typeCategory != transpiler::ConcreteType::AliasType);
	}

	if (outType)
		*outType = resType;

	transpiler::DefinedIdentifierPtr pDefinedIdentifier = type->GetMember(typeName, nullptr);
	if (outDefinedIdentifier)
		*outDefinedIdentifier = pDefinedIdentifier;

	if (resType != nullptr || pDefinedIdentifier != nullptr)
	{
		if (outOuterType != nullptr)
			*outOuterType = type;
		return true;
	}

	return false;
}

bool IdentifierHub::FindExistingIdentifier(const std::string &typeName, ConcreteTypePtr *outType, transpiler::DefinedIdentifierPtr *outDefinedIdentifier, ConcreteTypePtr *outOuterType)
{
	// first check function local scopes
	for (auto &scope : m_pTranspilerCtx->functionCtx.localScopes)
	{
		if (FindExistingIdentifierInType(scope.concreteType, typeName, outType, outDefinedIdentifier, outOuterType))
			return true;
	}

	// check this pointer scope
	if (m_pTranspilerCtx->thisPtrStack.stack.size() > 0
		&& FindExistingIdentifierInType(m_pTranspilerCtx->thisPtrStack.stack.back().thisType, typeName, outType, outDefinedIdentifier, outOuterType))
		return true;

	// check global scope
	if (FindExistingIdentifierInType(m_pTranspilerCtx->globalType, typeName, outType, outDefinedIdentifier, outOuterType))
		return true;

	return false;
}

bool IdentifierHub::ValidateNewIdentifier(const std::string &typeName)
{
	if (typeName.find("__") != std::string::npos)
	{
		m_pErrorPortal->AddIdentifierTwoUnderscoreError();
		return false;
	}

	if (FindExistingIdentifier(typeName, nullptr, nullptr))
	{
		m_pErrorPortal->AddIdentifierRedefinitionError(typeName);
		return false;
	}

	return true;
}

bool IdentifierHub::ValidateNewIdentifier(PredaParser::IdentifierContext *ctx)
{
	m_pErrorPortal->SetAnchor(ctx->start);
	return ValidateNewIdentifier(ctx->getText());
}

ConcreteTypePtr IdentifierHub::GetConcreteTypeFromContextText(antlr4::ParserRuleContext *ctx)
{
	std::string typeName = ctx->getText();
	ConcreteTypePtr ret;
	if (!FindExistingIdentifier(typeName, &ret, nullptr) || ret == nullptr)
	{
		m_pErrorPortal->SetAnchor(ctx->start);
		m_pErrorPortal->AddNotValidTypeError(typeName);
		return nullptr;
	}

	return ret;
}

ConcreteTypePtr IdentifierHub::GetTypeFromBuiltInContainerTypeNameContext(PredaParser::BuiltInContainerTypeNameContext *ctx)
{
	if (ctx->mapTypeName())					//map
	{
		PredaParser::MapTypeNameContext *mapCtx = ctx->mapTypeName();
		std::vector<ConcreteTypePtr> templateParams;
		templateParams.push_back(GetConcreteTypeFromContextText(mapCtx->mapKeyTypeName()));	// Grab the key type
		templateParams.push_back(GetTypeFromTypeNameContext(mapCtx->typeName()));	// Grab the value type, note that this is a recursive call

		if (templateParams[0] == nullptr || templateParams[1] == nullptr)
			return nullptr;
		if (templateParams[1]->typeCategory == transpiler::ConcreteType::ContractType)
		{
			m_pErrorPortal->SetAnchor(mapCtx->typeName()->start);
			m_pErrorPortal->AddIllegalUseOfContractTypeError();
			return nullptr;
		}

		std::shared_ptr<transpiler::TemplateType> templateType = m_pTranspilerCtx->GetBuiltInMapType();										//built-in map template type
		ConcreteTypePtr instantiatedType = templateType->GetConcreteTypeFromTemplateParams(templateParams);			//instantiate the template with the given key type and value type
		if (instantiatedType == nullptr)
		{
			m_pErrorPortal->AddInternalError(mapCtx->start, "Unknown error when instantiating map with type\"" + mapCtx->mapKeyTypeName()->getText() + "\", \"" + mapCtx->typeName()->getText() + "\". Probably a compiler bug.");
			return nullptr;
		}
		return instantiatedType;
	}
	else if (ctx->arrayTypeName())			//array
	{
		std::vector<ConcreteTypePtr> templateParams(1, GetTypeFromTypeNameContext(ctx->arrayTypeName()->typeName()));	// Grab value type
		if (templateParams[0] == nullptr)
			return nullptr;
		if (templateParams[0]->typeCategory == transpiler::ConcreteType::ContractType)
		{
			m_pErrorPortal->SetAnchor(ctx->arrayTypeName()->typeName()->start);
			m_pErrorPortal->AddIllegalUseOfContractTypeError();
			return nullptr;
		}

		std::shared_ptr<transpiler::TemplateType> templateType = m_pTranspilerCtx->GetBuiltInArrayType();										//built-in array template type
		ConcreteTypePtr instantiatedType = templateType->GetConcreteTypeFromTemplateParams(templateParams);	//instantiate the template with the given value type
		if (instantiatedType == nullptr)
		{
			m_pErrorPortal->AddInternalError(ctx->arrayTypeName()->typeName()->start, "Unknown error when instantiating array with type\"" + ctx->arrayTypeName()->typeName()->getText() + "\"");
			return nullptr;
		}
		return instantiatedType;
	}
	else
	{
		assert(0);

		return nullptr;
	}
}

// Get a concrete type from a TypeNameContext
ConcreteTypePtr IdentifierHub::GetTypeFromTypeNameContext(PredaParser::TypeNameContext *ctx)
{
	if (ctx->fundamentalTypeName())				//built-in type
	{
		return GetConcreteTypeFromContextText(ctx->fundamentalTypeName());
	}
	else if (ctx->userDefinedTypeName())		//struct
	{
		std::vector<PredaParser::IdentifierContext *> identifierCtx = ctx->userDefinedTypeName()->identifier();
		ConcreteTypePtr ret = GetConcreteTypeFromContextText(identifierCtx[0]);
		if (ret == nullptr)
			return nullptr;
		std::string text = identifierCtx[0]->getText();
		for (size_t i = 1; i < identifierCtx.size(); i++)
		{
			std::string identifierText = identifierCtx[i]->getText();
			if (i > 0)
				text += ".";
			text += identifierText;

			ret = ret->FindInnerConcreteType(identifierText);
			if (ret == nullptr)
			{
				m_pErrorPortal->SetAnchor(identifierCtx[i]->start);
				m_pErrorPortal->AddNotValidTypeError(text);
				return nullptr;
			}
		}

		if (ret->typeCategory == transpiler::ConcreteType::SystemReservedType)
		{
			m_pErrorPortal->SetAnchor(identifierCtx[0]->start);
			m_pErrorPortal->AddIllegalUseOfSystemReservedTypeError(ret);
			return nullptr;
		}

		return ret;
	}
	else if (ctx->builtInContainerTypeName())
	{
		return GetTypeFromBuiltInContainerTypeNameContext(ctx->builtInContainerTypeName());
	}
	else
	{
		assert(0);
	}
	return nullptr;
}
