#include <assert.h>

#include "PredaTranspiler.h"
#include "PredaBuiltInConcreteTypes.h"
#include "PredaBuiltInTemplateTypes.h"

namespace transpiler{

	/*
		BuiltInArrayType : Built-in array template type
	*/
	BuiltInArrayType::BuiltInArrayType(PredaTranspilerContext *inTranspilerContext)
	{
		assert(inTranspilerContext != nullptr);
		pTranspilerContext = inTranspilerContext;
		inputName = "array";				// It doesn't matter much if it matches exactly the convention in input source code, as long as the corresponding parser references the same string.
		numExpectedTemplateParams = 1;		// only one template parameter
	}

	ConcreteTypePtr BuiltInArrayType::InstantiateTemplate(const std::vector<ConcreteTypePtr> &templateParams)
	{
		assert(templateParams.size() == numExpectedTemplateParams);
		if (templateParams.size() != numExpectedTemplateParams)
			return nullptr;

		const ConcreteTypePtr &valueType = templateParams[0];
		ConcreteTypePtr pConcreteType = Allocator::New<ConcreteType>(ConcreteType::ReferenceType);
		if (pConcreteType)
		{
			pConcreteType->inputName = "array<" + valueType->inputName + ">";
			pConcreteType->outputFullName = typeOutputPrefix + "array<" + valueType->outputFullName + ">";
			pConcreteType->exportName = "array " + valueType->exportName;
			pConcreteType->supportedOperatorMask = uint64_t(OperatorTypeBitMask::AssignmentBit) | uint64_t(OperatorTypeBitMask::BracketBit) | uint64_t(OperatorTypeBitMask::DotBit);
			pConcreteType->boxBracketOperator.insert(std::make_pair(pTranspilerContext->GetBuiltInIntegerType(32, false), valueType));		// arrays support box bracket operator with uint as index type, and value type is the first template parameter type
			pConcreteType->nestingPropagatableFlags |= valueType->nestingPropagatableFlags;

			// add default constructor
			{
				bool res = pConcreteType->DefineDefaultConstructor() != nullptr;
				assert(res);
			}

			// add member function length
			{
				FunctionSignature signature;
				signature.returnType = QualifiedConcreteType(pTranspilerContext->GetBuiltInIntegerType(32, false), true, false);
				signature.flags = uint32_t(PredaFunctionFlags::IsConst);
				bool res = (pConcreteType->DefineMemberFunction("length", signature, false) != nullptr);
				assert(res);
			}

			// add member function push
			{
				FunctionSignature signature;
				signature.returnType = QualifiedConcreteType(nullptr, true, false);
				signature.parameters.push_back(Allocator::New<DefinedIdentifier>(valueType, true, true, "newElement", 0));
				signature.flags = 0;
				bool res = (pConcreteType->DefineMemberFunction("push", signature, false) != nullptr);
				assert(res);
			}

			// add member function pop
			{
				FunctionSignature signature;
				signature.returnType = QualifiedConcreteType(nullptr, true, false);
				signature.flags = 0;
				bool res = (pConcreteType->DefineMemberFunction("pop", signature, false) != nullptr);
				assert(res);
			}

			// add member function set_length
			{
				FunctionSignature signature;
				signature.returnType = QualifiedConcreteType(nullptr, true, false);
				signature.parameters.push_back(Allocator::New<DefinedIdentifier>(pTranspilerContext->GetBuiltInIntegerType(32, false), true, true, "newSize", 0));
				signature.flags = 0;
				bool res = (pConcreteType->DefineMemberFunction("set_length", signature, false) != nullptr);
				assert(res);
			}
		}

		return pConcreteType;
	}

	// Unique instance of type definition
	std::shared_ptr<BuiltInArrayType> BuiltInArrayType::CreateType(PredaTranspilerContext *inTranspilerContext)
	{
		return Allocator::New<BuiltInArrayType>(inTranspilerContext);
	}

	/*
		BuiltInMapType : Built-in map template type
	*/
	BuiltInMapType::BuiltInMapType(PredaTranspilerContext *inTranspilerContext)
	{
		assert(inTranspilerContext != nullptr);
		pTranspilerContext = inTranspilerContext;
		inputName = "map";
		numExpectedTemplateParams = 2;		// two template parameter (keyType and valueType)
	}

	ConcreteTypePtr BuiltInMapType::InstantiateTemplate(const std::vector<ConcreteTypePtr> &templateParams)
	{
		assert(templateParams.size() == numExpectedTemplateParams);
		if (templateParams.size() != numExpectedTemplateParams)
			return nullptr;

		const ConcreteTypePtr &keyType = templateParams[0];
		const ConcreteTypePtr &valueType = templateParams[1];
		ConcreteTypePtr pConcreteType = Allocator::New<ConcreteType>(ConcreteType::ReferenceType);
		if (pConcreteType)
		{
			pConcreteType->inputName = "map<" + templateParams[0]->inputName + ", " + templateParams[1]->inputName + ">";
			pConcreteType->outputFullName = typeOutputPrefix + "map<" + templateParams[0]->outputFullName + ", " + templateParams[1]->outputFullName + ">";
			pConcreteType->exportName = "map " + templateParams[0]->exportName + " " + templateParams[1]->exportName;
			pConcreteType->supportedOperatorMask = uint64_t(OperatorTypeBitMask::AssignmentBit) | uint64_t(OperatorTypeBitMask::BracketBit) | uint64_t(OperatorTypeBitMask::DotBit);
			pConcreteType->boxBracketOperator.insert(std::make_pair(templateParams[0], templateParams[1]));		// maps support box bracket operator with first template parameter as index type and second template parameter as value type
			pConcreteType->nestingPropagatableFlags |= templateParams[1]->nestingPropagatableFlags;

			// add default constructor
			{
				bool res = pConcreteType->DefineDefaultConstructor() != nullptr;
				assert(res);
			}

			// add member function has
			{
				FunctionSignature signature;
				signature.returnType = QualifiedConcreteType(pTranspilerContext->GetBuiltInBoolType(), true, false);
				signature.parameters.push_back(Allocator::New<DefinedIdentifier>(keyType, true, true, "key", 0));
				signature.flags = uint32_t(PredaFunctionFlags::IsConst);
				bool res = (pConcreteType->DefineMemberFunction("has", signature, false) != nullptr);
				assert(res);
			}
			// add member function erase
			{
				FunctionSignature signature;
				signature.returnType = QualifiedConcreteType(nullptr, true, false);
				signature.parameters.push_back(Allocator::New<DefinedIdentifier>(keyType, true, true, "key", 0));
				signature.flags = 0;
				bool res = (pConcreteType->DefineMemberFunction("erase", signature, false) != nullptr);
				assert(res);
			}
		}

		return pConcreteType;
	}

	// Unique instance of type definition
	std::shared_ptr<BuiltInMapType> BuiltInMapType::CreateType(PredaTranspilerContext *inTranspilerContext)
	{
		return Allocator::New<BuiltInMapType>(inTranspilerContext);
	}
}
