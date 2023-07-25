#include "Allocator.h"
#include "TemplateType.h"
#include "ConcreteType.h"

namespace transpiler {

	const std::string typeOutputPrefix = "__prlt_";
	const std::string identifierOutputPrefix = "__prli_";

	DefinedIdentifier::DefinedIdentifier(ConcreteTypePtr inType, bool inIsConst, bool inIsLValue, const std::string &inName, uint32_t inFlags)
		: qualifiedType(inType, inIsConst, inIsLValue)
	{
		inputName = inName;
		outputName = identifierOutputPrefix + inName;
		flags = inFlags;
	}

	ConcreteType::ConcreteType(TypeCategory inTypeCategory)
		: typeCategory(inTypeCategory)
	{
	}

	DefinedIdentifierPtr ConcreteType::GetMember(const std::string &memberName, bool *outIsStatic)
	{
		for (size_t i = 0; i < members.size(); i++)
			if (members[i]->inputName == memberName)
			{
				if (outIsStatic)
					*outIsStatic = vbMemberIsStatic[i];
				return members[i];
			}

		return nullptr;
	}

	DefinedIdentifierPtr ConcreteType::DefineMemberVariable(ConcreteTypePtr variableType, const std::string &variableName, uint32_t flags, bool bIsConst, bool bIsLValue, bool bIsStatic)
	{
		if (GetMember(variableName, nullptr) != nullptr)
			return nullptr;

		members.push_back(Allocator::New<DefinedIdentifier>(variableType, bIsConst, bIsLValue, variableName, flags));
		vbMemberIsStatic.push_back(bIsStatic);

		nestingPropagatableFlags |= variableType->nestingPropagatableFlags;

		return members.back();
	}

	DefinedIdentifierPtr ConcreteType::DefineMemberFunction(const std::string &name, const FunctionSignature &signature, bool bIsStatic)
	{
		bool bExistingIsStatic;
		DefinedIdentifierPtr pMember = GetMember(name, &bExistingIsStatic);

		if (pMember != nullptr)
		{
			ConcreteTypePtr functionType = pMember->qualifiedType.baseConcreteType;
			if (functionType->typeCategory != FunctionType)		// If the identifier is already defined as a variable 
				return nullptr;
			//if (bExistingIsStatic || bIsStatic)									// static member functions cannot be overloaded
			//	return nullptr;

			// If there's already a function with the same name and signature 
			for (size_t i = 0; i < functionType->vOverloadedFunctions.size(); i++)
			{
				if (signature == functionType->vOverloadedFunctions[i])
					return nullptr;
			}
		}
		else
		{
			ConcreteTypePtr functionType = Allocator::New<ConcreteType>(FunctionType);
			functionType->bIsUserDefinedStructType = false;
			functionType->inputName = "__@" + name;
			functionType->outputFullName = "__@" + name;
			functionType->exportName = "__@" + name;
			functionType->supportedOperatorMask = uint64_t(OperatorTypeBitMask::ParenthesesBit);

			members.push_back(Allocator::New<DefinedIdentifier>(functionType, false, false, name, 0));
			vbMemberIsStatic.push_back(bIsStatic);

			if (!AttachInnerConcreteType(functionType))
				return nullptr;

			pMember = members.back();
		}

		pMember->qualifiedType.baseConcreteType->vOverloadedFunctions.push_back(signature);

		if (typeCategory == InterfaceType	// function name starting with '@' or "__" are automatically generated functions like "@constructor" or "__id" and should not be included in the interface function mapping
			&& (name.size() > 0 && name[0] != '@')
			&& (name.size() < 2 || name[0] != '_' || name[1] != '_'))
		{
			vInterfaceMemberFuncIndexMapping.emplace_back(pMember, pMember->qualifiedType.baseConcreteType->vOverloadedFunctions.size() - 1);
		}

		return pMember;
	}

	DefinedIdentifierPtr ConcreteType::DefineDefaultConstructor()
	{
		return DefineMemberFunction("@constructor",	FunctionSignature(QualifiedConcreteType(shared_from_this(), false, false), std::vector<DefinedIdentifierPtr>(), 0), false);
	}

	bool ConcreteType::AttachInnerConcreteType(ConcreteTypePtr innerType)
	{
		if (innerType == nullptr || FindInnerConcreteType(innerType->inputName) != nullptr)
			return false;

		innerConcreteTypes.insert(std::make_pair(innerType->inputName, innerType));
		innerType->outerType = shared_from_this();
		if (outerType != nullptr)
		{
			innerType->exportName = exportName + "." + innerType->exportName;
			innerType->outputFullName = outputFullName + "::" + innerType->outputFullName;
		}

		return true;
	}

	bool ConcreteType::AttachInnerTemplateType(std::shared_ptr<TemplateType> innerType)
	{
		if (innerType == nullptr || FindInnerTemplateType(innerType->inputName) != nullptr)
			return false;

		innerTemplateTypes.insert(std::make_pair(innerType->inputName, innerType));
		innerType->parentType = shared_from_this();

		return true;
	}

	ConcreteTypePtr ConcreteType::FindInnerConcreteType(const std::string &typeName)
	{
		auto itor = innerConcreteTypes.find(typeName);
		if (itor != innerConcreteTypes.end())
			return itor->second;

		return nullptr;
	}

	// Return a built-in template type based on the enum
	std::shared_ptr<TemplateType> ConcreteType::FindInnerTemplateType(const std::string &typeName)
	{
		auto itor = innerTemplateTypes.find(typeName);
		if (itor != innerTemplateTypes.end())
			return itor->second;

		return nullptr;
	}

	ConcreteTypePtr ConcreteType::CreateInnerUnnamedScopeType(const std::string &customLabel)
	{
		ConcreteTypePtr ret;

		ret = Allocator::New<ConcreteType>(UnnamedScopeType);
		ret->bIsUserDefinedStructType = false;
		ret->inputName = "__scope" + std::to_string(numUnnamedScopes) + "@" + customLabel;
		ret->outputFullName = ret->inputName;
		ret->exportName = ret->inputName;
		ret->supportedOperatorMask = 0;

		if (!AttachInnerConcreteType(ret))
			return nullptr;

		numUnnamedScopes++;

		return ret;
	}

	ConcreteTypePtr ConcreteType::CreateInnerContractType(const std::string &typeName, const std::string &contractfullName)
	{
		ConcreteTypePtr contractType = Allocator::New<ConcreteType>(ContractType);
		contractType->bIsUserDefinedStructType = false;
		contractType->inputName = typeName;
		contractType->outputFullName = typeOutputPrefix + typeName;
		contractType->exportName = contractfullName;
		contractType->supportedOperatorMask = uint64_t(OperatorTypeBitMask::AssignmentBit) | uint64_t(OperatorTypeBitMask::DotBit);

		if (!AttachInnerConcreteType(contractType))
			return nullptr;

		return contractType;
	}

	ConcreteTypePtr ConcreteType::CreateInnerUserDefinedStructType(const std::string &typeName)
	{
		ConcreteTypePtr structType = Allocator::New<ConcreteType>(ReferenceType);
		structType->bIsUserDefinedStructType = true;
		structType->inputName = typeName;
		structType->outputFullName = typeOutputPrefix + typeName;			// User-defined struct names are kept the same in the output
		structType->exportName = typeName;
		structType->supportedOperatorMask = uint64_t(OperatorTypeBitMask::DotBit) | uint64_t(OperatorTypeBitMask::AssignmentBit);

		if (!AttachInnerConcreteType(structType))
			return nullptr;

		return structType;
	}

	ConcreteTypePtr ConcreteType::CreateInnerEnumType(const std::string &typeName)
	{
		ConcreteTypePtr enumType = Allocator::New<ConcreteType>(EnumType);
		enumType->bIsUserDefinedStructType = false;
		enumType->inputName = typeName;
		enumType->outputFullName = typeOutputPrefix + typeName;			// User-defined enum names are kept the same in the output
		enumType->exportName = typeName;
		enumType->supportedOperatorMask = uint64_t(OperatorTypeBitMask::AssignmentBit) | uint64_t(OperatorTypeBitMask::EqualityComparisonBits);

		if (!AttachInnerConcreteType(enumType))
			return nullptr;

		return enumType;
	}

	ConcreteTypePtr ConcreteType::CreateInnerAliasType(const std::string &typeName, ConcreteTypePtr realType)
	{
		if (realType == nullptr)
			return nullptr;

		ConcreteTypePtr aliasType = Allocator::New<ConcreteType>(AliasType);
		aliasType->bIsUserDefinedStructType = false;
		aliasType->inputName = typeName;
		aliasType->outputFullName = typeOutputPrefix + typeName;
		aliasType->exportName = typeName;
		aliasType->supportedOperatorMask = 0;
		aliasType->realType = realType->typeCategory == AliasType ? realType->realType : realType;

		if (!AttachInnerConcreteType(aliasType))
			return nullptr;

		return aliasType;
	}

	ConcreteTypePtr ConcreteType::CreateInnerInterfaceType(const std::string& typeName)
	{
		ConcreteTypePtr interfaceType = Allocator::New<ConcreteType>(InterfaceType);
		interfaceType->bIsUserDefinedStructType = false;
		interfaceType->inputName = typeName;
		interfaceType->outputFullName = typeOutputPrefix + typeName;
		interfaceType->exportName = typeName;
		interfaceType->supportedOperatorMask = uint64_t(OperatorTypeBitMask::AssignmentBit) | uint64_t(OperatorTypeBitMask::DotBit);

		if (!AttachInnerConcreteType(interfaceType))
			return nullptr;

		return interfaceType;
	}
}
