#include "PredaTranspiler.h"
#include "PredaBuiltInConcreteTypes.h"

namespace transpiler {

	ConcreteTypePtr BuiltInIntegerTypeFactory::CreateIntegerType(uint32_t bitWidth, bool bSigned)
	{
		ConcreteTypePtr concreteType = Allocator::New<ConcreteType>(ConcreteType::ValueType);
		concreteType->inputName = (bSigned ? "int" : "uint") + std::to_string(bitWidth);
		concreteType->outputFullName = typeOutputPrefix + concreteType->inputName;
		concreteType->exportName = concreteType->inputName;
		concreteType->supportedOperatorMask = uint64_t(OperatorTypeBitMask::AssignmentBit)
			| uint64_t(OperatorTypeBitMask::IncrementAndDecrementBits)
			| uint64_t(OperatorTypeBitMask::AddSubMulDivBits)
			| uint64_t(OperatorTypeBitMask::ModuloBit)
			| uint64_t(OperatorTypeBitMask::AssignmentModuloBit)
			| uint64_t(OperatorTypeBitMask::GenericComparisonBits);
		if (bSigned)
			concreteType->supportedOperatorMask |= uint64_t(OperatorTypeBitMask::UnaryMinusBit);
		else
			concreteType->supportedOperatorMask |= uint64_t(OperatorTypeBitMask::BitwiseBits);
		return concreteType;
	}
	ConcreteTypePtr BuiltInFloatTypeFactory::CreateFloatType(uint32_t floatWidth)
	{
		ConcreteTypePtr concreteType = Allocator::New<ConcreteType>(ConcreteType::ValueType);
		concreteType->inputName = "float" + std::to_string(floatWidth);
		concreteType->outputFullName = typeOutputPrefix + concreteType->inputName;
		concreteType->exportName = concreteType->inputName;
		concreteType->supportedOperatorMask = uint64_t(OperatorTypeBitMask::AssignmentBit)
			| uint64_t(OperatorTypeBitMask::AddSubMulDivBits)
			| uint64_t(OperatorTypeBitMask::GenericComparisonBits)
			| uint64_t(OperatorTypeBitMask::UnaryMinusBit);
		return concreteType;
	}


	/*
		BuiltInBoolType
	*/
	BuiltInBoolType::BuiltInBoolType()
		: ConcreteType(ConcreteType::ValueType)
	{
		inputName = "bool";
		outputFullName = typeOutputPrefix + inputName;
		exportName = inputName;
		supportedOperatorMask = uint64_t(OperatorTypeBitMask::AssignmentBit) | uint64_t(OperatorTypeBitMask::LogicalBits) | uint64_t(OperatorTypeBitMask::EqualityComparisonBits);
	}

	std::shared_ptr<BuiltInBoolType> BuiltInBoolType::CreateType()
	{
		return Allocator::New<BuiltInBoolType>();
	}

	/* 
		BuiltInAddressType
	*/
	BuiltInAddressType::BuiltInAddressType()
		: ConcreteType(ConcreteType::ValueType)
	{
		inputName = "address";
		outputFullName = typeOutputPrefix + inputName;
		exportName = inputName;
		supportedOperatorMask = uint64_t(OperatorTypeBitMask::AssignmentBit) | uint64_t(OperatorTypeBitMask::GenericComparisonBits) | uint64_t(OperatorTypeBitMask::DotBit);
	}

	std::shared_ptr<BuiltInAddressType> BuiltInAddressType::CreateType()
	{
		return Allocator::New<BuiltInAddressType>();
	}

	/* 
		BuiltInStringType
	*/
	BuiltInStringType::BuiltInStringType()
		: ConcreteType(ConcreteType::ReferenceType)
	{
		//TODO: add [] support for string
		inputName = "string";
		outputFullName = typeOutputPrefix + inputName;
		exportName = inputName;
		supportedOperatorMask = uint64_t(OperatorTypeBitMask::AssignmentBit) | uint64_t(OperatorTypeBitMask::GenericComparisonBits) | uint64_t(OperatorTypeBitMask::DotBit);
	}

	std::shared_ptr<BuiltInStringType> BuiltInStringType::CreateType()
	{
		return Allocator::New<BuiltInStringType>();
	}

	/*
		BuiltInBlobType
	*/
	BuiltInBlobType::BuiltInBlobType()
		: ConcreteType(ConcreteType::ValueType)
	{
		inputName = "blob";
		outputFullName = typeOutputPrefix + inputName;
		exportName = inputName;
		supportedOperatorMask = uint64_t(OperatorTypeBitMask::AssignmentBit) | uint64_t(OperatorTypeBitMask::GenericComparisonBits);
		nestingPropagatableFlags |= uint32_t(PredaTypeNestingPropagatableFlags::HasBlob);
	}

	std::shared_ptr<BuiltInBlobType> BuiltInBlobType::CreateType()
	{
		return Allocator::New<BuiltInBlobType>();
	}

	/*
		BuiltInHashType
	*/
	BuiltInHashType::BuiltInHashType()
		: ConcreteType(ConcreteType::ValueType)
	{
		//TODO: add [] support for string
		inputName = "hash";
		outputFullName = typeOutputPrefix + inputName;
		exportName = inputName;
		supportedOperatorMask = uint64_t(OperatorTypeBitMask::AssignmentBit) | uint64_t(OperatorTypeBitMask::GenericComparisonBits);
	}

	std::shared_ptr<BuiltInHashType> BuiltInHashType::CreateType()
	{
		return Allocator::New<BuiltInHashType>();
	}

	/*
		BuiltInBigIntType
	*/
	BuiltInBigIntType::BuiltInBigIntType()
		: ConcreteType(ConcreteType::ValueType)
	{
		inputName = "bigint";
		outputFullName = typeOutputPrefix + inputName;
		exportName = inputName;
		supportedOperatorMask = uint64_t(OperatorTypeBitMask::AssignmentBit)
			| uint64_t(OperatorTypeBitMask::IncrementAndDecrementBits)
			| uint64_t(OperatorTypeBitMask::AddSubMulDivBits)
			| uint64_t(OperatorTypeBitMask::ModuloBit)
			| uint64_t(OperatorTypeBitMask::AssignmentModuloBit)
			| uint64_t(OperatorTypeBitMask::GenericComparisonBits)
			| uint64_t(OperatorTypeBitMask::UnaryMinusBit)
			| uint64_t(OperatorTypeBitMask::DotBit);
	}

	std::shared_ptr<BuiltInBigIntType> BuiltInBigIntType::CreateType()
	{
		return Allocator::New<BuiltInBigIntType>();
	}
}
