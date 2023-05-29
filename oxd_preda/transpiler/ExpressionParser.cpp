#include <string>

#include "ExpressionParser.h"
#include "util.h"

using ConcreteTypePtr = transpiler::ConcreteTypePtr;

void GetIntergerWidthAndSignFromLiteralSuffix(const std::string &integerLiteral, std::string &outIntegerBody, size_t &outBitWidth, bool &outIsSigned)
{
	size_t signCharPos = std::string::npos;

	signCharPos = integerLiteral.rfind('u');
	if (signCharPos != std::string::npos)
	{
		outIsSigned = false;
	}
	else
	{
		signCharPos = integerLiteral.rfind('i');
		if (signCharPos == std::string::npos)
		{
			//defaults to int32
			outBitWidth = 32;
			outIsSigned = true;
			outIntegerBody = integerLiteral;
			return;
		}
		outIsSigned = true;
	}

	if (signCharPos == integerLiteral.length() - 1)
		outBitWidth = 32;
	else
		outBitWidth = std::stoi(integerLiteral.substr(signCharPos + 1));
	outIntegerBody = integerLiteral.substr(0, signCharPos);
}

void GetFloatWidthFromLiteralSuffix(const std::string &floatLiteral, std::string &outFloatBody, size_t &outBitWidth){
	size_t bitStartPos = floatLiteral.rfind('f');
	if(bitStartPos == std::string::npos){
		outBitWidth = 256;
		outFloatBody = floatLiteral;
		return;
	}

	if(bitStartPos == floatLiteral.length() - 1){
		outBitWidth = 256;
	}
	else{
		outBitWidth = std::stoi(floatLiteral.substr(bitStartPos + 1));
	}
	outFloatBody = floatLiteral.substr(0, bitStartPos);
}
int char2int(char input)
{
	if (input >= '0' && input <= '9')
		return input - '0';
	if (input >= 'A' && input <= 'F')
		return input - 'A' + 10;
	if (input >= 'a' && input <= 'f')
		return input - 'a' + 10;
	return -1;
}

bool IsHexInRange(std::string& literalBody, size_t bitWidth, bool bIsSigned, bool literalIsNonPositive)
{
	//max of unsigned int in hex = bitwidth/4 * 'F', max of uint_128 = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
	//max of signed int in hex =  '7' + (bitwidth/4 - 1)* 'F', max of int_128 = "7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
	//min of signed int in hex = '8' + (bitwidth/4 - 1)* '0' = "80000000000000000000000000000000"
	int start_pos = 0;
	//trim leading 0
	for (; start_pos < literalBody.length(); start_pos++)
	{
		if (literalBody[start_pos] != '0')
		{
			break;
		}
	}
	literalBody = literalBody.substr(start_pos);

	size_t maxValueLen = bitWidth / 4;
	if (literalBody.length() > maxValueLen)
	{
		return false;
	}
	else if (literalBody.length() < maxValueLen)
	{
		return true;
	}
	else
	{
		if (bIsSigned && !literalIsNonPositive && char2int(literalBody[0]) > 7)
		{
			return false;
		}
		if (bIsSigned && literalIsNonPositive)
		{
			if (char2int(literalBody[0]) > 8)
			{
				return false;
			}
			else if (char2int(literalBody[0]) == 8)
			{
				for (int i = 1; i < literalBody.length(); i++)
				{
					if (char2int(literalBody[i]) > 0)
					{
						return false;
					}
				}
			}
		}
	}
	//no need to compare 'F' or 'f'
	return true;
}
bool IsLongIntegerLiteralInRange(std::string& literalBody, size_t bitWidth, bool bIsSigned)
{
	bool literalIsNonPositive = literalBody[0] == '-';
	std::string str = literalIsNonPositive ? literalBody.substr(1) : literalBody;

	if (str[0] == '0' && (str[1] == 'x' || str[0] == 'X'))
	{
		literalBody = str.substr(2);
		bool result = IsHexInRange(literalBody, bitWidth, bIsSigned, literalIsNonPositive);
		//'0x' will be prepended to literalBody to tell two formats apart
		literalBody = (literalIsNonPositive ? "-0x" : "0x") + literalBody;
		return result;
	}
	static const std::vector<std::string> unsigned_max{"340282366920938463463374607431768211455", "115792089237316195423570985008687907853269984665640564039457584007913129639935", "0", "13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084095"};
	static const std::vector<std::string> signed_max{"170141183460469231731687303715884105727", "57896044618658097711785492504343953926634992332820282019728792003956564819967", "0", "6703903964971298549787012499102923063739682910296196688861780721860882015036773488400937149083451713845015929093243025426876941405973284973216824503042047"};
	std::string maxValue = bIsSigned ? signed_max[bitWidth/128 - 1] : unsigned_max[bitWidth / 128 - 1];

	size_t maxValueLen = maxValue.length();
	if(literalIsNonPositive)
	{
		if (!bIsSigned)
		{
			return false;
		}
		maxValue[maxValue.length() - 1] = '8';
	}
	if (str.length()  > maxValueLen)
	{
		return false;
	}
	else if(str.length() < maxValueLen)
	{
		return true;
	}
	else
	{
		for (int i = 0; i < maxValueLen; i++)
		{
			if (str[i] > maxValue[i]) return false;
			if (str[i] < maxValue[i]) return true;
		}
	}
	//when literalBody = maxValue
	return true;
}
//takes std::string& instead of const std::string because leading zeros will be removed from literalBody if it is in hex
bool IsIntegerLiteralInRange(std::string &literalBody, size_t bitWidth, bool bIsSigned, uint8_t base)
{
	assert(bitWidth == 8 || bitWidth == 16 || bitWidth == 32 || bitWidth == 64 || bitWidth == 128 || bitWidth == 256 || bitWidth == 512);
	if (bitWidth > 64)
	{
		return IsLongIntegerLiteralInRange(literalBody, bitWidth, bIsSigned);
	}
	static const uint64_t  maxValues[8] = { 255, 65535, 0, 4294967295, 0, 0, 0, 18446744073709551615llu };
	uint64_t maxValue = maxValues[bitWidth / 8 - 1];
	bool literalIsNonPositive = literalBody[0] == '-';
	if (bIsSigned)
	{
		maxValue /= 2;
		if (literalIsNonPositive)
			maxValue = maxValue + 1;
	}
	else
	{
		if (literalIsNonPositive)
			maxValue = 0;
	}

	uint64_t curValue = 0;

	size_t start = 0;
	if (literalIsNonPositive)
		start++;
	if (base == 16)
		start += 2;
	for (size_t i = start; i < literalBody.size(); i++)
	{
		if (maxValue / base < curValue)
			return false;
		curValue *= base;

		uint8_t curDigit;
		if (literalBody[i] >= '0' && literalBody[i] <= '9')
			curDigit = literalBody[i] - '0';
		else if (literalBody[i] >= 'a' && literalBody[i] <= 'f')
			curDigit = literalBody[i] - 'a' + 10;
		else if (literalBody[i] >= 'A' && literalBody[i] <= 'F')
			curDigit = literalBody[i] - 'F' + 10;
		else
			return false;

		if (maxValue == 0 && (curDigit > 0 || curValue > 0))
			return false;
		if (maxValue - curDigit < curValue)
			return false;
		curValue += curDigit;
	}

	return true;
}

bool ExpressionParser::ParseIdentifier_Internal(PredaParser::IdentifierContext *ctx, ExpressionResult &outResult, bool requireConst)
{
	std::string identifierName = ctx->getText();

	ConcreteTypePtr type;
	transpiler::DefinedIdentifierPtr pDefinedIdentifier = nullptr;
	ConcreteTypePtr outerType;

	if (!m_pIdentifierHub->FindExistingIdentifier(identifierName, &type, &pDefinedIdentifier, &outerType))
	{
		m_pErrorPortal->SetAnchor(ctx->start);
		m_pErrorPortal->AddIdentifierNotDefinedError(identifierName);
		return false;
	}

	// first check if it's a type
	if (type != nullptr)
	{
		outResult.type.baseConcreteType = type;
		outResult.text = type->outputFullName;
		outResult.bIsTypeName = true;
		return true;
	}

	// otherwise it's an identifier
	bool isConstMem = m_pIdentifierHub->GetConstMemberDefinition(pDefinedIdentifier, outResult.text); //is iddentifier is a const member var, outResult.text will be set to its definition
	//if requireConst is true, ParseIdentifier_Internal is called from defineConstVariable
	if (requireConst) {
		bool tmp;
		if (!isConstMem) //processing non-const variable in a const variable declaration
		{
			m_pErrorPortal->SetAnchor(ctx->start);
			m_pErrorPortal->AssigningMemberVarToConstVarError(identifierName);
			return false;
		}
		if (outerType == m_pTranspilerCtx->globalType && m_pTranspilerCtx->globalType->GetMember(identifierName, &tmp) != nullptr) //using global context's member in a const variable declaration
		{
			m_pErrorPortal->SetAnchor(ctx->start);
			m_pErrorPortal->AddAssignToConstError();
			return false;
		}
		outResult.type = pDefinedIdentifier->qualifiedType;
		outResult.type.bIsConst = true;
	}
	else
	{
		if (isConstMem) //searching for constant member variable in a function call
		{
			outResult.type = pDefinedIdentifier->qualifiedType;
			outResult.type.bIsConst = true;
			return true;
		}
		uint32_t curFunctionScope = m_pTranspilerCtx->functionCtx.GetFunctionSignature()->flags & uint32_t(transpiler::ScopeType::Mask);
		uint32_t identifierScope = pDefinedIdentifier->flags & uint32_t(transpiler::ScopeType::Mask);
		if (m_pTranspilerCtx->functionCtx.GetFunctionSignature())
		{
			if ((identifierScope > uint32_t(transpiler::ScopeType::Shard) && identifierScope < curFunctionScope) || identifierScope > curFunctionScope)
			{
				m_pErrorPortal->SetAnchor(ctx->start);
				m_pErrorPortal->AddIdentifierScopeUnaccessibleError(identifierName, util::ScopeTypeToString(transpiler::ScopeType(identifierScope)), util::ScopeTypeToString(transpiler::ScopeType(curFunctionScope)));
				return false;
			}
		}

		outResult.type = pDefinedIdentifier->qualifiedType;
		outResult.text = pDefinedIdentifier->outputName;
		outResult.bIsTypeName = false;

		// if we are inside a const function, all variables in the scope right outside it are limited to const access
		if (m_pTranspilerCtx->thisPtrStack.stack.size() > 0
			&& outerType == m_pTranspilerCtx->thisPtrStack.stack.back().thisType
			&& m_pTranspilerCtx->thisPtrStack.stack.back().bIsConstPtr)
			outResult.type.bIsConst = true;

		if (identifierScope == uint32_t(transpiler::ScopeType::Global))
		{
			// set global state dependency flag
			m_pTranspilerCtx->functionCtx.GetFunctionSignature()->flags |= uint32_t(transpiler::FunctionFlags::GlobalStateDependency);

			// global state variables are read-only in non-global functions
			if (curFunctionScope != uint32_t(transpiler::ScopeType::Global))
				outResult.type.bIsConst = true;
		}
	}
	return true;
}

bool ExpressionParser::ParsePrimaryExpression(PredaParser::PrimaryExpressionContext *ctx, ExpressionResult &outResult, bool requireConst)
{
	if (ctx->BooleanLiteral())
	{
		outResult.type = transpiler::QualifiedConcreteType(m_pTranspilerCtx->GetBuiltInBoolType(), true, false);
		outResult.text = outResult.type.baseConcreteType->outputFullName + "(" + ctx->getText() + ")";
		outResult.bIsTypeName = false;
		return true;
	}
	else if (ctx->DecimalIntegerLiteral() || ctx->HexIntegerLiteral())
	{
		std::string literalBody;
		size_t bitWidth;
		bool bIsSigned;
		GetIntergerWidthAndSignFromLiteralSuffix(ctx->getText(), literalBody, bitWidth, bIsSigned);
		if (!IsIntegerLiteralInRange(literalBody, bitWidth, bIsSigned, ctx->DecimalIntegerLiteral() ? 10 : 16))
		{
			m_pErrorPortal->SetAnchor(ctx->start);
			m_pErrorPortal->AddConstantOutOfRangeError();
			return false;
		}
		outResult.type = transpiler::QualifiedConcreteType(m_pTranspilerCtx->GetBuiltInIntegerType(bitWidth, bIsSigned), true, false);
		if (outResult.type.baseConcreteType == nullptr)			// Theoretically this should not be hit since the grammar file is already limiting integer literal suffices to valid types
		{
			m_pErrorPortal->AddInternalError(ctx->start, "invalid integer literal \"" + ctx->getText() + "\". Probably a compiler bug.");
			return false;
		}
		if (bitWidth == 64)
		{
			if (!bIsSigned)
				literalBody += "ull";
			else
				literalBody += "ll";
		}
		outResult.text = bitWidth > 64 ? outResult.type.baseConcreteType->outputFullName + "(\"" + literalBody + "\")" : outResult.type.baseConcreteType->outputFullName + "(" + literalBody + ")";
		outResult.bIsTypeName = false;
		return true;
	}
	else if(ctx->DecimalFloatLiteral()){
		std::string floatLiteral = ctx->getText();
		std::string floatBody;
		size_t length;
		GetFloatWidthFromLiteralSuffix(floatLiteral, floatBody, length);
		outResult.type = transpiler::QualifiedConcreteType(m_pTranspilerCtx->GetBuiltInFloatType(length), true, false);
		outResult.text = outResult.type.baseConcreteType->outputFullName + "(\"" + floatBody + "\")";
		outResult.bIsTypeName = false;
		return true;
	}
	else if (ctx->DecimalBigIntegerLiteral() || ctx->HexBigIntegerLiteral())
	{
		std::string literalBody = ctx->getText();
		literalBody.erase(literalBody.end() - 2, literalBody.end());
		outResult.type = transpiler::QualifiedConcreteType(m_pTranspilerCtx->GetBuiltInBigIntType(), true, false);
		outResult.text = outResult.type.baseConcreteType->outputFullName + "(\"" + literalBody + "\", " + std::to_string(literalBody.size()) + ")";
		outResult.bIsTypeName = false;
		return true;
	}
	else if (ctx->StringLiteral())
	{
		outResult.type = transpiler::QualifiedConcreteType(m_pTranspilerCtx->GetBuiltInStringType(), false, false);
		outResult.text = outResult.type.baseConcreteType->outputFullName + "(" + ctx->getText() + ")";
		outResult.bIsTypeName = false;
		return true;
	}
	else if (ctx->AddressLiteral())
	{
		std::string literalBody = ctx->getText();
		std::string::size_type offset = literalBody.rfind(':');
		std::string encoding = literalBody.substr(offset + 1);
		if ((encoding != "ed25519" && encoding != "contract") || offset != 58)
		{
			m_pErrorPortal->SetAnchor(ctx->start);
			m_pErrorPortal->AddInvalidAddressLiteralError(literalBody);
			return false;
		}
		outResult.type = transpiler::QualifiedConcreteType(m_pTranspilerCtx->GetBuiltInAddressType(), false, false);
		outResult.text = outResult.type.baseConcreteType->outputFullName + "(\"" + ctx->getText() + "\")";
		outResult.bIsTypeName = false;
		return true;
	}
	else if (ctx->HashLiteral())
	{
		std::string literalBody = ctx->getText();
		std::string::size_type offset = literalBody.rfind(':');
		std::string encoding = literalBody.substr(offset + 1);
		if (encoding != "hash" || offset != 52)
		{
			m_pErrorPortal->SetAnchor(ctx->start);
			m_pErrorPortal->AddInvalidHashLiteralError(literalBody);
			return false;
		}
		outResult.type = transpiler::QualifiedConcreteType(m_pTranspilerCtx->GetBuiltInHashType(), false, false);
		outResult.text = outResult.type.baseConcreteType->outputFullName + "(\"" + ctx->getText() + "\")";
		outResult.bIsTypeName = false;
		return true;
	}
	else if (ctx->identifier())
	{
		return ParseIdentifier_Internal(ctx->identifier(), outResult, requireConst);
	}
	else if (ctx->fundamentalTypeName())
	{
		// look up for the built-in concrete type
		ConcreteTypePtr concreteType = m_pIdentifierHub->GetConcreteTypeFromContextText(ctx->fundamentalTypeName());
		if (concreteType == nullptr)
			return false;

		outResult.text = concreteType->outputFullName;
		outResult.type.baseConcreteType = concreteType;
		outResult.bIsTypeName = true;
		return true;
	}
	else if (ctx->builtInContainerTypeName())
	{
		// First look up for the built-in concrete type
		ConcreteTypePtr concreteType = m_pIdentifierHub->GetTypeFromBuiltInContainerTypeNameContext(ctx->builtInContainerTypeName());
		if (concreteType == nullptr)
			return false;

		outResult.text = concreteType->outputFullName;
		outResult.type.baseConcreteType = concreteType;
		outResult.bIsTypeName = true;
		return true;
	}

	assert(0);

	return false;
}

bool ExpressionParser::ValidateExpressionResult(const ExpressionResult &result)
{
	if (result.bIsTypeName)
	{
		m_pErrorPortal->AddIllegalUseOfTypeAsExpressionError();
		return false;
	}

	//if (result.type.baseConcreteType != nullptr && result.type.baseConcreteType->typeCategory == transpiler::ConcreteType::ContractType)
	//{
	//	m_pErrorPortal->AddIllegalUseOfContractTypeError();
	//	return false;
	//}

	if (result.type.baseConcreteType != nullptr && result.type.baseConcreteType->typeCategory == transpiler::ConcreteType::SystemReservedType)
	{
		m_pErrorPortal->AddIllegalUseOfSystemReservedTypeError(result.type.baseConcreteType);
		return false;
	}

	if (result.type.baseConcreteType != nullptr && result.type.baseConcreteType->typeCategory == transpiler::ConcreteType::FunctionType)
	{
		m_pErrorPortal->AddFunctionCallMissingArgumentListError();
		return false;
	}

	return true;
}

bool ExpressionParser::ParseExpression(PredaParser::ExpressionContext *ctx, ExpressionResult &outResult, bool requireConst)
{
	if (!ParseExpression_Internal(ctx, outResult, requireConst))
		return false;

	m_pErrorPortal->SetAnchor(ctx->start);
	return ValidateExpressionResult(outResult);
}

bool ExpressionParser::ParseIdentifierAsExpression(PredaParser::IdentifierContext *ctx, ExpressionResult &outResult)
{
	if (!ParseIdentifier_Internal(ctx, outResult))
		return false;

	m_pErrorPortal->SetAnchor(ctx->start);
	return ValidateExpressionResult(outResult);
}

bool ExpressionParser::ParseExpression_Internal(PredaParser::ExpressionContext *ctx, ExpressionResult &outResult, bool requireConst)
{
	if (transpiler::PredaExpressionTypes(ctx->expressionType) == transpiler::PredaExpressionTypes::UnaryMinus && ctx->expression(0)->primaryExpression())
	{
		if (ctx->expression(0)->primaryExpression()->DecimalIntegerLiteral() || ctx->expression(0)->primaryExpression()->HexIntegerLiteral())
		{
			if (((antlr4::tree::TerminalNode*)ctx->children[0])->getSymbol()->getStartIndex() + 1 != ctx->expression(0)->start->getStartIndex())
			{
				m_pErrorPortal->SetAnchor(ctx->expression(0)->start);
				m_pErrorPortal->AddSpaceInNegativeNumberLiteralError();
				return false;
			}

			std::string literalBody;
			size_t bitWidth;
			bool bIsSigned;
			GetIntergerWidthAndSignFromLiteralSuffix("-" + ctx->expression(0)->getText(), literalBody, bitWidth, bIsSigned);
			if (!IsIntegerLiteralInRange(literalBody, bitWidth, bIsSigned, ctx->expression(0)->primaryExpression()->DecimalIntegerLiteral() ? 10 : 16))
			{
				m_pErrorPortal->SetAnchor(ctx->start);
				m_pErrorPortal->AddConstantOutOfRangeError();
				return false;
			}
			outResult.type = transpiler::QualifiedConcreteType(m_pTranspilerCtx->GetBuiltInIntegerType(bitWidth, bIsSigned), true, false);
			if (outResult.type.baseConcreteType == nullptr)			// Theoretically this should not be hit since the grammar file is already limiting integer literal suffices to valid types
			{
				m_pErrorPortal->AddInternalError(ctx->start, "invalid integer literal \"" + ctx->getText() + "\". Probably a compiler bug.");
				return false;
			}
			if (bitWidth == 64)
			{
				if (!bIsSigned)
					literalBody += "ull";
				else
					literalBody += "ll";
			}
			outResult.text = bitWidth > 64 ? outResult.type.baseConcreteType->outputFullName + "(\"" + literalBody + "\")" : outResult.type.baseConcreteType->outputFullName + "(" + literalBody + ")";
			outResult.bIsTypeName = false;
			return true;
		}
		else if (ctx->expression(0)->primaryExpression()->DecimalBigIntegerLiteral() || ctx->expression(0)->primaryExpression()->HexBigIntegerLiteral())
		{
			if (((antlr4::tree::TerminalNode*)ctx->children[0])->getSymbol()->getStartIndex() + 1 != ctx->expression(0)->start->getStartIndex())
			{
				m_pErrorPortal->SetAnchor(ctx->expression(0)->start);
				m_pErrorPortal->AddSpaceInNegativeNumberLiteralError();
				return false;
			}

			std::string literalBody = "-" + ctx->expression(0)->getText();
			literalBody.erase(literalBody.end() - 2, literalBody.end());
			outResult.type = transpiler::QualifiedConcreteType(m_pTranspilerCtx->GetBuiltInBigIntType(), true, false);
			outResult.text = outResult.type.baseConcreteType->outputFullName + "(\"" + literalBody + "\", " + std::to_string(literalBody.size()) + ")";
			outResult.bIsTypeName = false;
			return true;
		}
	}

	outResult.type.baseConcreteType = nullptr;

	std::vector<PredaParser::ExpressionContext *> subExpressions = ctx->expression();
	std::vector<ExpressionResult> subExpRes(subExpressions.size());
	for (size_t i = 0; i < subExpressions.size(); i++)
	{
		if (!ParseExpression_Internal(ctx->expression(i), subExpRes[i], requireConst))
			return false;

		// type name expression can only be the first sub expression
		if (i > 0 && subExpRes[i].bIsTypeName)
		{
			m_pErrorPortal->SetAnchor(ctx->expression(i)->start);
			m_pErrorPortal->AddIllegalUseOfTypeAsExpressionError();
			return false;
		}
	}

	if (transpiler::PredaExpressionTypes(ctx->expressionType) == transpiler::PredaExpressionTypes::Primary)
		return ParsePrimaryExpression(ctx->primaryExpression(), outResult, requireConst);

	// First handle the case of type name expressions
	assert(subExpressions.size() > 0);
	if (subExpRes[0].bIsTypeName)
	{
		// type name expression has only 3 possibilities:
		// 1. with "()", which evaluates to the constructor
		// 2. with ".", and evaluates to a sub type
		// 3. with ".", and evaluates to a static member, currently the only possibilities are:
		//   a. an enumerator of an enumeration type
		//   b. __id() of contract type
		switch (transpiler::PredaExpressionTypes(ctx->expressionType))
		{
		case transpiler::PredaExpressionTypes::Parentheses:
		{
			transpiler::DefinedIdentifierPtr pMember = subExpRes[0].type.baseConcreteType->GetMember("@constructor", nullptr);
			if (pMember == nullptr)
			{
				m_pErrorPortal->SetAnchor(ctx->start);
				m_pErrorPortal->AddNoMatchingConstructorError(subExpressions[0]->getText());
				return false;
			}

			ConcreteTypePtr constructorType = pMember->qualifiedType.baseConcreteType;
			if (constructorType->typeCategory != transpiler::ConcreteType::FunctionType)
			{
				m_pErrorPortal->AddInternalError(ctx->start, "constructor of \"" + subExpressions[0]->getText() + "\" is not a function. Probably compiler bug.");
				return false;
			}

			std::string functionArgumentsSynthesizeResult;
			int overloadFuncIndex = FindMatchingOverloadedFunction(constructorType, ctx->functionCallArguments(), functionArgumentsSynthesizeResult);
			if (overloadFuncIndex == -1)
				return false;

			transpiler::FunctionSignature &signature = constructorType->vOverloadedFunctions[overloadFuncIndex];

			if (m_pTranspilerCtx->functionCtx.GetFunctionSignature())
			{
				uint32_t curFunctionContextClass = m_pTranspilerCtx->functionCtx.GetFunctionSignature()->flags & uint32_t(transpiler::ScopeType::Mask);
				uint32_t calleeContextClass = signature.flags & uint32_t(transpiler::ScopeType::Mask);
				if (curFunctionContextClass < calleeContextClass)
				{
					m_pErrorPortal->AddInternalError(ctx->start, "constructor of \"" + subExpressions[0]->getText() + "\" has a higher context class than the current function and is not accessible. Probably a compiler bug.");
					return false;
				}

				auto itor = m_pFunctionCallGraph->m_functionCallerSets.try_emplace(&signature).first;
				itor->second.insert(m_pTranspilerCtx->functionCtx.GetFunctionSignature());
			}

			outResult.text = subExpRes[0].text + "(" + functionArgumentsSynthesizeResult + ")";
			outResult.type = signature.returnType;

			return true;
		}
		case transpiler::PredaExpressionTypes::Dot:
		{
			std::string identifierText = ctx->identifier()->getText();

			// first check for sub types
			{
				ConcreteTypePtr type = subExpRes[0].type.baseConcreteType->FindInnerConcreteType(identifierText);
				if (type != nullptr)
				{
					outResult.bIsTypeName = true;
					outResult.text = type->outputFullName;
					outResult.type.baseConcreteType = type;
					return true;
				}
			}

			// check for static members
			{
				bool bStatic;
				transpiler::DefinedIdentifierPtr pMember = subExpRes[0].type.baseConcreteType->GetMember(identifierText, &bStatic);
				if (pMember == nullptr)
				{
					m_pErrorPortal->SetAnchor(ctx->identifier()->start);
					m_pErrorPortal->AddNotAMemberOfError(identifierText, subExpressions[0]->getText());
					return false;
				}
				if (!bStatic)
				{
					m_pErrorPortal->SetAnchor(ctx->identifier()->start);
					m_pErrorPortal->AddIllegalReferenceToNonStaticMemberError(identifierText);
					return false;
				}
				transpiler::QualifiedConcreteType memberType = pMember->qualifiedType;

				outResult.bIsTypeName = false;
				if (memberType.baseConcreteType->typeCategory == transpiler::ConcreteType::EnumType)
				{
					outResult.text = subExpRes[0].text + "(" + subExpRes[0].text + "__::" + pMember->outputName + ")";
				}
				else
				{
					outResult.text = subExpRes[0].text + "::" + pMember->outputName;
				}

				outResult.type = memberType;

				return true;
			}
		}
		default:
			m_pErrorPortal->SetAnchor(ctx->expression(0)->start);
			m_pErrorPortal->AddIllegalUseOfTypeAsExpressionError();
			return false;
		}
	}

	// Then handle normal expressions
	outResult.bIsTypeName = false;

	enum class ExpressionResultType {
		SameAsFirstOperand,
		Bool,
		Void,
		Custom
	};

	struct ExpressionDesc {
		transpiler::OperatorTypeBitMask operatorBitMask;
		std::string operatorString;
		bool modifiesFirstOperand;
		unsigned char numFixedSubexpressions;
		ExpressionResultType resultType;
	};

	static const ExpressionDesc predaExpressions[uint8_t(transpiler::PredaExpressionTypes::Max)] =
	{
		{transpiler::OperatorTypeBitMask::PostIncrementBit,			"++",	true,	1,	ExpressionResultType::Void},										//		PostIncrement = 0,
		{transpiler::OperatorTypeBitMask::PostDecrementBit,			"--",	true,	1,	ExpressionResultType::Void},										//		PostDecrement,
		{transpiler::OperatorTypeBitMask::BracketBit,				"[]",	false,	2,	ExpressionResultType::Custom},										//		Bracket,
		{transpiler::OperatorTypeBitMask::ParenthesesBit,			"()",	false,	1,	ExpressionResultType::Custom},										//		Parentheses,
		{transpiler::OperatorTypeBitMask::DotBit,					".",	false,	1,	ExpressionResultType::Custom},										//		Dot,
		{transpiler::OperatorTypeBitMask(0),						"",		false,	1,	ExpressionResultType::SameAsFirstOperand},							//		SurroundWithParentheses,
		{transpiler::OperatorTypeBitMask::PreIncrementBit,			"++",	true,	1,	ExpressionResultType::Void},										//		PreIncrement,
		{transpiler::OperatorTypeBitMask::PreDecrementBit,			"--",	true,	1,	ExpressionResultType::Void},										//		PreDecrement,
		{transpiler::OperatorTypeBitMask::UnaryPlusBit,				"+",	false,	1,	ExpressionResultType::SameAsFirstOperand},							//		UnaryPlus,
		{transpiler::OperatorTypeBitMask::UnaryMinusBit,			"-",	false,	1,	ExpressionResultType::SameAsFirstOperand},							//		UnaryMinus,
		{transpiler::OperatorTypeBitMask::LogicalNotBit,			"!",	false,	1,	ExpressionResultType::SameAsFirstOperand},							//		LogicalNot,
		{transpiler::OperatorTypeBitMask::BitwiseNotBit,			"~",	false,	1,	ExpressionResultType::SameAsFirstOperand},							//		BitwiseNot,
		{transpiler::OperatorTypeBitMask::MultiplyBit,				"*",	false,	2,	ExpressionResultType::Custom},										//		Multiply,
		{transpiler::OperatorTypeBitMask::DivideBit,				"/",	false,	2,	ExpressionResultType::Custom},										//		Divide,
		{transpiler::OperatorTypeBitMask::ModuloBit,				"%",	false,	2,	ExpressionResultType::Custom},										//		Modulo,
		{transpiler::OperatorTypeBitMask::AddBit,					"+",	false,	2,	ExpressionResultType::Custom},										//		Add,
		{transpiler::OperatorTypeBitMask::SubtractBit,				"-",	false,	2,	ExpressionResultType::Custom},										//		Subtract,
		{transpiler::OperatorTypeBitMask::ShiftLeftBit,				"<<",	false,	2,	ExpressionResultType::SameAsFirstOperand},							//		ShiftLeft,
		{transpiler::OperatorTypeBitMask::ShiftRightBit,			">>",	false,	2,	ExpressionResultType::SameAsFirstOperand},							//		ShiftRight,
		{transpiler::OperatorTypeBitMask::LessThanBit,				"<",	false,	2,	ExpressionResultType::Bool},										//		LessThan,
		{transpiler::OperatorTypeBitMask::GreaterThanBit,			">",	false,	2,	ExpressionResultType::Bool},										//		GreaterThan,
		{transpiler::OperatorTypeBitMask::LessThanOrEqualBit,		"<=",	false,	2,	ExpressionResultType::Bool},										//		LessThanOrEqual,
		{transpiler::OperatorTypeBitMask::GreaterThanOrEqualBit,	">=",	false,	2,	ExpressionResultType::Bool},										//		GreaterThanOrEqual,
		{transpiler::OperatorTypeBitMask::EqualBit,					"==",	false,	2,	ExpressionResultType::Bool},										//		Equal,
		{transpiler::OperatorTypeBitMask::NotEqualBit,				"!=",	false,	2,	ExpressionResultType::Bool},										//		NotEqual,
		{transpiler::OperatorTypeBitMask::BitwiseAndBit,			"&",	false,	2,	ExpressionResultType::SameAsFirstOperand},							//		BitwiseAnd,
		{transpiler::OperatorTypeBitMask::BitwiseXorBit,			"^",	false,	2,	ExpressionResultType::SameAsFirstOperand},							//		BitwiseXor,
		{transpiler::OperatorTypeBitMask::BitwiseOrBit,				"|",	false,	2,	ExpressionResultType::SameAsFirstOperand},							//		BitwiseOr,
		{transpiler::OperatorTypeBitMask::LogicalAndBit,			"&&",	false,	2,	ExpressionResultType::Bool},										//		LogicalAnd,
		{transpiler::OperatorTypeBitMask::LogicalOrBit,				"||",	false,	2,	ExpressionResultType::Bool},										//		LogicalOr,
		{transpiler::OperatorTypeBitMask(0),						"?:",	false,	3,	ExpressionResultType::Custom},								//		TernaryConditional,
		{transpiler::OperatorTypeBitMask::AssignmentBit,			"=",	true,	2,	ExpressionResultType::Void},										//		Assignment,
		{transpiler::OperatorTypeBitMask::AssignmentAddBit,			"+=",	true,	2,	ExpressionResultType::Void},										//		AssignmentAdd,
		{transpiler::OperatorTypeBitMask::AssignmentSubtractBit,	"-=",	true,	2,	ExpressionResultType::Void},										//		AssignmentSubtract,
		{transpiler::OperatorTypeBitMask::AssignmentMultiplyBit,	"*=",	true,	2,	ExpressionResultType::Void},										//		AssignmentMultiply,
		{transpiler::OperatorTypeBitMask::AssignmentDivideBit,		"/=",	true,	2,	ExpressionResultType::Void},										//		AssignmentDivide,
		{transpiler::OperatorTypeBitMask::AssignmentModuloBit,		"%=",	true,	2,	ExpressionResultType::Void},										//		AssignmentModulo,
		{transpiler::OperatorTypeBitMask::AssignmentShiftLeftBit,	"<<=",	true,	2,	ExpressionResultType::Void},										//		AssignmentShiftLeft,
		{transpiler::OperatorTypeBitMask::AssignmentShiftRightBit,	">>=",	true,	2,	ExpressionResultType::Void},										//		AssignmentShiftRight,
		{transpiler::OperatorTypeBitMask::AssignmentBitwiseAndBit,	"&=",	true,	2,	ExpressionResultType::Void},										//		AssignmentBitwiseAnd,
		{transpiler::OperatorTypeBitMask::AssignmentBitwiseXorBit,	"^=",	true,	2,	ExpressionResultType::Void},										//		AssignmentBitwiseXor,
		{transpiler::OperatorTypeBitMask::AssignmentBitwiseOrBit,	"|=",	true,	2,	ExpressionResultType::Void},										//		AssignmentBitwiseOr,
		{transpiler::OperatorTypeBitMask(0),						"",		false,	2,	ExpressionResultType::Custom}										//		Primary,
	};

	static_assert(sizeof(predaExpressions) / sizeof(predaExpressions[0]) == uint8_t(transpiler::PredaExpressionTypes::Max), "predaExpressions has wrong size");

	// Unified validation of expressions. And "operatorBitMask" field of 0 means that it's an invalid entry, it's in the list just to align the entries
	if (predaExpressions[ctx->expressionType].operatorBitMask != transpiler::OperatorTypeBitMask(0))
	{
		const ExpressionDesc &curExprDesc = predaExpressions[ctx->expressionType];

		// Check if any necessary operand is of type void
		for (int subExprIdx = 0; subExprIdx < curExprDesc.numFixedSubexpressions; subExprIdx++)
		{
			if (subExpRes[subExprIdx].type.baseConcreteType == nullptr)
			{
				m_pErrorPortal->SetAnchor(subExpressions[subExprIdx]->start);
				m_pErrorPortal->AddVoidOperandError(curExprDesc.operatorString, subExpressions[subExprIdx]->getText());
				return false;
			}
		}

		// Check if the operator is supported
		if ((subExpRes[0].type.baseConcreteType->supportedOperatorMask & uint64_t(curExprDesc.operatorBitMask)) == 0)
		{
			m_pErrorPortal->SetAnchor(subExpressions[0]->start);
			m_pErrorPortal->AddUnsupportedOperatorError(subExpRes[0].type.baseConcreteType, curExprDesc.operatorString);
			return false;
		}

		// Check if the operator is modifies the first operand and it is const
		if (curExprDesc.modifiesFirstOperand)
		{
			if (!subExpRes[0].type.bIsLValue)
			{
				m_pErrorPortal->SetAnchor(subExpressions[0]->start);
				m_pErrorPortal->AddAssignToNonLValueError();
				return false;
			}
			if (subExpRes[0].type.bIsConst)
			{
				m_pErrorPortal->SetAnchor(subExpressions[0]->start);
				m_pErrorPortal->AddAssignToConstError();
				return false;
			}
			if (curExprDesc.numFixedSubexpressions >= 2 && subExpRes[1].type.bIsConst && subExpRes[1].type.baseConcreteType->IsConstTransitive())
			{
				m_pErrorPortal->SetAnchor(subExpressions[0]->start);
				m_pErrorPortal->AddAssignConstReferenceTypeToNonConstError(subExpRes[0].type.baseConcreteType);
				return false;
			}
		}

		// Decide the expression result type
		switch (curExprDesc.resultType)
		{
		case ExpressionResultType::SameAsFirstOperand:
			outResult.type.baseConcreteType = subExpRes[0].type.baseConcreteType;
			break;
		case ExpressionResultType::Bool:
			outResult.type.baseConcreteType = m_pTranspilerCtx->GetBuiltInBoolType();
			break;
		case ExpressionResultType::Void:
			outResult.type.baseConcreteType = nullptr;
			break;
		case ExpressionResultType::Custom:
			break;
		}
	}

	// Most expressions generates an intermediate result and is hence non-lvalue and const.
	// The other cases will be handled individually in the switch() statement below
	outResult.type.bIsConst = true;
	outResult.type.bIsLValue = false;

	switch (transpiler::PredaExpressionTypes(ctx->expressionType))
	{
	// Unary operators that appear after the operand
	case transpiler::PredaExpressionTypes::PostIncrement:
	case transpiler::PredaExpressionTypes::PostDecrement:
		outResult.text = subExpRes[0].text + ctx->children[1]->getText();
		return true;
	// Unary operators that appear before the operand
	case transpiler::PredaExpressionTypes::PreIncrement:
	case transpiler::PredaExpressionTypes::PreDecrement:
	case transpiler::PredaExpressionTypes::UnaryPlus:
	case transpiler::PredaExpressionTypes::UnaryMinus:
	case transpiler::PredaExpressionTypes::LogicalNot:
	case transpiler::PredaExpressionTypes::BitwiseNot:
		outResult.text = ctx->children[0]->getText() + subExpRes[0].text;
		return true;
	// Binary operators
	case transpiler::PredaExpressionTypes::Multiply:
	case transpiler::PredaExpressionTypes::Divide:
	case transpiler::PredaExpressionTypes::Modulo:
	case transpiler::PredaExpressionTypes::Add:
	case transpiler::PredaExpressionTypes::Subtract:
	case transpiler::PredaExpressionTypes::BitwiseAnd:
	case transpiler::PredaExpressionTypes::BitwiseXor:
	case transpiler::PredaExpressionTypes::BitwiseOr:
	case transpiler::PredaExpressionTypes::LessThan:
	case transpiler::PredaExpressionTypes::GreaterThan:
	case transpiler::PredaExpressionTypes::LessThanOrEqual:
	case transpiler::PredaExpressionTypes::GreaterThanOrEqual:
	case transpiler::PredaExpressionTypes::Equal:
	case transpiler::PredaExpressionTypes::NotEqual:
	case transpiler::PredaExpressionTypes::LogicalAnd:
	case transpiler::PredaExpressionTypes::LogicalOr:
	case transpiler::PredaExpressionTypes::Assignment:
	case transpiler::PredaExpressionTypes::AssignmentAdd:
	case transpiler::PredaExpressionTypes::AssignmentSubtract:
	case transpiler::PredaExpressionTypes::AssignmentMultiply:
	case transpiler::PredaExpressionTypes::AssignmentDivide:
	case transpiler::PredaExpressionTypes::AssignmentModulo:
	case transpiler::PredaExpressionTypes::AssignmentBitwiseAnd:
	case transpiler::PredaExpressionTypes::AssignmentBitwiseXor:
	case transpiler::PredaExpressionTypes::AssignmentBitwiseOr:
	case transpiler::PredaExpressionTypes::ShiftLeft:
	case transpiler::PredaExpressionTypes::AssignmentShiftLeft:
	case transpiler::PredaExpressionTypes::AssignmentShiftRight:
	{
		if (subExpRes[0].type.baseConcreteType == subExpRes[1].type.baseConcreteType)
		{
			outResult.text = subExpRes[0].text + " " + ctx->children[1]->getText() + " " + subExpRes[1].text;
			if (predaExpressions[ctx->expressionType].resultType == ExpressionResultType::Custom)
			{
				outResult.type.baseConcreteType = subExpRes[0].type.baseConcreteType;
			}
		}
		else
		{
			transpiler::PredaTranspilerContext::OperatorProcessor::expressionPack exprPack({ subExpRes[0].text, subExpRes[1].text, subExpRes[0].type.baseConcreteType, subExpRes[1].type.baseConcreteType, ctx->children[1]->getText(), predaExpressions[ctx->expressionType].operatorBitMask });
			ConcreteTypePtr resultType;
			if (!m_pTranspilerCtx->opProcessor.processOperation(exprPack, outResult.text, resultType))
			{
				m_pErrorPortal->SetAnchor(subExpressions[0]->start);
				m_pErrorPortal->AddTypeMismatchError(subExpRes[0].type.baseConcreteType, subExpRes[1].type.baseConcreteType);
				return false;
			}
			if (predaExpressions[ctx->expressionType].resultType == ExpressionResultType::Custom)
			{
				outResult.type.baseConcreteType = resultType;
			}

		}
		return true;
	}
	case transpiler::PredaExpressionTypes::ShiftRight:
		// shift right has to be handled individually, for compatibility with nested template type, e.g. array<array<int32>>, the grammar for shift right is defined as '>' '>' instead of '>>'.
		// Hence we need to check that there's no extra characters between these two '>'s.
		if (((antlr4::tree::TerminalNode*)ctx->children[1])->getSymbol()->getStartIndex() + 1 != ((antlr4::tree::TerminalNode*)ctx->children[2])->getSymbol()->getStartIndex())
		{
			m_pErrorPortal->AddSyntaxError((uint32_t)((antlr4::tree::TerminalNode*)ctx->children[2])->getSymbol()->getLine(), (uint32_t)((antlr4::tree::TerminalNode*)ctx->children[2])->getSymbol()->getCharPositionInLine(), "unexpected '>'");
			return false;
		}
		if (!subExpRes[0].bIsTypeName)
		{
			transpiler::PredaTranspilerContext::OperatorProcessor::expressionPack exprPack({ subExpRes[0].text, subExpRes[1].text, subExpRes[0].type.baseConcreteType, subExpRes[1].type.baseConcreteType, " >> " , predaExpressions[ctx->expressionType].operatorBitMask});
			if (!m_pTranspilerCtx->opProcessor.processOperation(exprPack, outResult.text, outResult.type.baseConcreteType))
			{
				m_pErrorPortal->SetAnchor(subExpressions[0]->start);
				m_pErrorPortal->AddTypeMismatchError(subExpRes[0].type.baseConcreteType, subExpRes[1].type.baseConcreteType);
				return false;
			}
		}
		else
		{
			outResult.text = subExpRes[0].text + " >> " + subExpRes[1].text;
		}
		return true;

	// The special cases
	case transpiler::PredaExpressionTypes::Bracket:
	{
		auto itor = subExpRes[0].type.baseConcreteType->boxBracketOperator.find(subExpRes[1].type.baseConcreteType);
		if (itor == subExpRes[0].type.baseConcreteType->boxBracketOperator.end())
		{
			m_pErrorPortal->SetAnchor(ctx->start);
			m_pErrorPortal->AddUnsupportedIndexTypeError(subExpRes[0].type.baseConcreteType, subExpRes[1].type.baseConcreteType);
			return false;
		}
		outResult.text = subExpRes[0].text + "[" + subExpRes[1].text + "]";
		outResult.type = transpiler::QualifiedConcreteType(itor->second, subExpRes[0].type.bIsConst, true);			//if the container type is const, the member is also const-qualified.
		return true;
	}
	case transpiler::PredaExpressionTypes::Parentheses:
	{
		if (subExpRes[0].type.baseConcreteType->typeCategory != transpiler::ConcreteType::FunctionType)
		{
			m_pErrorPortal->AddInternalError(ctx->start, "calling non-function \"" + subExpRes[0].text + "\". Probably a compiler bug.");
			return false;
		}

		std::string functionArgumentsSynthesizeResult;
		int overloadFuncIndex;
		if (subExpRes[0].type.baseConcreteType == m_pTranspilerCtx->m_builtInDebugPrintFunctionType)
		{
			if (m_pOptions && m_pOptions->bDisableDebugPrint)
			{
				outResult.text = subExpRes[0].text + "_disabled()";
				outResult.type = subExpRes[0].type.baseConcreteType->vOverloadedFunctions[0].returnType;

				return true;
			}

			if (!GenerateDebugPrintArguments(ctx->functionCallArguments(), functionArgumentsSynthesizeResult))
				return false;
			overloadFuncIndex = 0;
		}
		else
		{
			overloadFuncIndex = FindMatchingOverloadedFunction(subExpRes[0].type.baseConcreteType, ctx->functionCallArguments(), functionArgumentsSynthesizeResult);
			if (overloadFuncIndex == -1)
				return false;

			if (subExpRes[0].type.baseConcreteType == m_pTranspilerCtx->m_builtInDebugAssertFunctionType)
				functionArgumentsSynthesizeResult += ", " + std::to_string((uint32_t)ctx->functionCallArguments()->start->getLine());
		}

		transpiler::FunctionSignature &signature = subExpRes[0].type.baseConcreteType->vOverloadedFunctions[overloadFuncIndex];

		if (subExpRes[0].type.bIsConst && ((signature.flags & uint32_t(transpiler::FunctionFlags::IsConst)) == 0))
		{
			m_pErrorPortal->SetAnchor(ctx->start);
			m_pErrorPortal->AddCallNonConstFromConstContextError(subExpressions[0]->getText());
			return false;
		}

		if (m_pTranspilerCtx->functionCtx.GetFunctionSignature())
		{
			uint32_t curFunctionScope = m_pTranspilerCtx->functionCtx.GetFunctionSignature()->flags & uint32_t(transpiler::ScopeType::Mask);
			uint32_t calleeScope = signature.flags & uint32_t(transpiler::ScopeType::Mask);
			if ((calleeScope > uint32_t(transpiler::ScopeType::Shard) && calleeScope < curFunctionScope) || calleeScope > curFunctionScope)
			{
				m_pErrorPortal->SetAnchor(ctx->start);
				m_pErrorPortal->AddIdentifierScopeUnaccessibleError(subExpressions[0]->getText(), util::ScopeTypeToString(transpiler::ScopeType(calleeScope)), util::ScopeTypeToString(transpiler::ScopeType(curFunctionScope)));
				return false;
			}

			// A global function is accessible from non-global functions only if it is const and doesn't have relay@shards
			if (curFunctionScope != uint32_t(transpiler::ScopeType::Global)
				&& calleeScope == uint32_t(transpiler::ScopeType::Global)
				&& (((signature.flags & uint32_t(transpiler::FunctionFlags::IsConst)) == 0) || ((signature.flags & uint32_t(transpiler::FunctionFlags::HasRelayShardsStatement)) != 0))
				)
			{
				m_pErrorPortal->SetAnchor(ctx->start);
				m_pErrorPortal->AddInaccessibleGlobalFunctionFromNonGlobalFunctionError(subExpressions[0]->getText());
				return false;
			}

			auto itor = m_pFunctionCallGraph->m_functionCallerSets.try_emplace(&signature).first;
			itor->second.insert(m_pTranspilerCtx->functionCtx.GetFunctionSignature());
		}

		outResult.text = subExpRes[0].text + "(" + functionArgumentsSynthesizeResult + ")";
		outResult.type = signature.returnType;

		// special HACK for .__self() of contract types
		if (outResult.type.baseConcreteType && outResult.type.baseConcreteType->typeCategory == transpiler::ConcreteType::ContractType)
		{
			// __self() return value const-ness is the same as the const-ness of contract function scope
			if (m_pTranspilerCtx->thisPtrStack.stack.size() == 2)
				outResult.type.bIsConst = m_pTranspilerCtx->thisPtrStack.stack[1].bIsConstPtr;
		}

		return true;
	}
	case transpiler::PredaExpressionTypes::Dot:
	{
		transpiler::DefinedIdentifierPtr pMember = subExpRes[0].type.baseConcreteType->GetMember(ctx->identifier()->getText(), nullptr);
		if (pMember == nullptr)
		{
			m_pErrorPortal->SetAnchor(ctx->identifier()->start);
			m_pErrorPortal->AddNotAMemberOfError(ctx->identifier()->getText(), subExpressions[0]->getText());
			return false;
		}

		outResult.type = pMember->qualifiedType;

		if (subExpRes[0].type.baseConcreteType->bIsUserDefinedStructType)
			outResult.text = subExpRes[0].text + "->" + pMember->outputName;			//User-defined structs are defined as ref-types and have "->" operator overloaded to access the real struct type members
		else
			outResult.text = subExpRes[0].text + "." + pMember->outputName;

		if (subExpRes[0].type.bIsConst)
			outResult.type.bIsConst = true;
		return true;
	}
	case transpiler::PredaExpressionTypes::SurroundWithParentheses:
		//if (subExpRes[0].type.baseConcreteType->typeCategory == transpiler::ConcreteType::FunctionType)
		//{
		//	m_pErrorPortal->AddInternalError(subExpressions[0]->start, "cannot surround with parentheses.");
		//	return false;
		//}
		outResult.text = "(" + subExpRes[0].text + ")";
		outResult.type = subExpRes[0].type;
		return true;
	case transpiler::PredaExpressionTypes::TernaryConditional:
		if (subExpRes[0].type.baseConcreteType != m_pTranspilerCtx->GetBuiltInBoolType())
		{
			m_pErrorPortal->SetAnchor(subExpressions[0]->start);
			m_pErrorPortal->AddBooleanExpressionExpectedError(subExpRes[0].type.baseConcreteType);
			return false;
		}
		if (subExpRes[1].type.baseConcreteType != subExpRes[2].type.baseConcreteType)
		{
			m_pErrorPortal->SetAnchor(subExpressions[1]->start);
			m_pErrorPortal->AddTypeMismatchError(subExpRes[1].type.baseConcreteType, subExpRes[2].type.baseConcreteType);
			return false;
		}
		outResult.text = subExpRes[0].text + " ? " + subExpRes[1].text + " : " + subExpRes[2].text;
		outResult.type = subExpRes[1].type;
		outResult.type.bIsConst = subExpRes[1].type.bIsConst || subExpRes[2].type.bIsConst;				// If any of the two expressions is const, the result needs to be const
		outResult.type.bIsLValue = subExpRes[1].type.bIsLValue && subExpRes[2].type.bIsLValue;			// If any of the two expressions is not lvalue, the result cannot be lvalue
		return true;

	case transpiler::PredaExpressionTypes::Primary:
		return ParsePrimaryExpression(ctx->primaryExpression(), outResult);
	default:
		assert(0);
		return false;
	}

	return false;
}

int ExpressionParser::FindMatchingOverloadedFunction(const ConcreteTypePtr &calledFunction, PredaParser::FunctionCallArgumentsContext *ctx, std::string &outSynthesizedArgumentsString)
{
	std::vector<PredaParser::ExpressionContext *> argCtxs = ctx->expression();
	std::vector<ExpressionResult> args(argCtxs.size());

	outSynthesizedArgumentsString = "";
	for (size_t i = 0; i < argCtxs.size(); i++)
	{
		if (!ParseExpression(argCtxs[i], args[i]))
			return -1;

		if (i > 0)
			outSynthesizedArgumentsString += ", ";
		outSynthesizedArgumentsString += args[i].text;
	}

	assert(calledFunction->vOverloadedFunctions.size() > 0);

	bool bFunctionIsOverloaded = (calledFunction->vOverloadedFunctions.size() > 1);

	for (size_t i = 0; i < calledFunction->vOverloadedFunctions.size(); i++)
	{
		const transpiler::FunctionSignature& functionSignature = calledFunction->vOverloadedFunctions[i];
		if (functionSignature.parameters.size() != argCtxs.size())
		{
			// When there's no function overload, we provide a detailed error, otherwise skip to the next overloaded version
			if (!bFunctionIsOverloaded)
			{
				m_pErrorPortal->SetAnchor(ctx->start);
				m_pErrorPortal->AddArgumentListLengthMismatchError(functionSignature.parameters.size(), argCtxs.size());
				return -1;
			}
			else
				continue;
		}

		bool parameterListMatch = true;

		for (size_t j = 0; j < argCtxs.size(); j++)
		{
			if (args[j].type.baseConcreteType != functionSignature.parameters[j]->qualifiedType.baseConcreteType)
			{
				if (!bFunctionIsOverloaded)
				{
					m_pErrorPortal->SetAnchor(argCtxs[j]->start);
					m_pErrorPortal->AddTypeMismatchError(functionSignature.parameters[j]->qualifiedType.baseConcreteType, args[j].type.baseConcreteType);
					return -1;
				}
				else
				{
					parameterListMatch = false;
					break;
				}
			}

			if (args[j].type.bIsConst && !functionSignature.parameters[j]->qualifiedType.bIsConst && args[j].type.baseConcreteType->IsConstTransitive())
			{
				if (!bFunctionIsOverloaded)
				{
					m_pErrorPortal->SetAnchor(argCtxs[j]->start);
					m_pErrorPortal->AddAssignConstReferenceTypeToNonConstError(args[j].type.baseConcreteType);
					return -1;
				}
				else
				{
					parameterListMatch = false;
					break;
				}
			}
		}

		if (parameterListMatch)
		{
			if ((functionSignature.flags & uint32_t(transpiler::FunctionFlags::CallableFromSystem)) != 0)
			{
				m_pErrorPortal->SetAnchor(ctx->start);
				m_pErrorPortal->AddCallSystemReservedFunctionError();
				return -1;
			}
			return int(i);
		}
	}

	m_pErrorPortal->SetAnchor(ctx->start);
	m_pErrorPortal->AddNoMatchingOverloadedFunctionError();
	return -1;
}

bool ExpressionParser::GenerateDebugPrintArguments(PredaParser::FunctionCallArgumentsContext *ctx, std::string &outSynthesizedArgumentsString)
{
	std::vector<PredaParser::ExpressionContext *> argCtxs = ctx->expression();

	outSynthesizedArgumentsString = std::to_string((uint32_t)ctx->start->getLine()) + ", ";
	bool bFirstArg = true;
	for (size_t i = 0; i < argCtxs.size(); i++)
	{
		ExpressionResult arg;
		if (!ParseExpression(argCtxs[i], arg))
			return false;

		// skip arguments that are of void type
		if (arg.type.baseConcreteType == nullptr)
			continue;

		if (!bFirstArg)
			outSynthesizedArgumentsString += ", ";
		else
			bFirstArg = false;
		outSynthesizedArgumentsString += "\"" + arg.type.baseConcreteType->exportName + "\", " + arg.text;
	}

	return true;
}
