#pragma once

#include "BaseTranspiler.h"

namespace transpiler {

	// Built-in uint type
	struct BuiltInIntegerTypeFactory
	{
		// Unique instance of type definition
		static ConcreteTypePtr CreateIntegerType(uint32_t bitWidth, bool bSigned);
	};

	// Built-in float type
	struct BuiltInFloatTypeFactory
	{
		// Unique instance of type definition
		static ConcreteTypePtr CreateFloatType(uint32_t floatWidth);
	};


	// Built-in uint type
	struct BuiltInBoolType : public ConcreteType
	{
		BuiltInBoolType();

		// Unique instance of type definition
		static std::shared_ptr<BuiltInBoolType> CreateType();
	};

	// Built-in address type
	struct BuiltInAddressType : public ConcreteType
	{
		BuiltInAddressType();

		// Unique instance of type definition
		static std::shared_ptr<BuiltInAddressType> CreateType();
	};

	// Built-in string type
	struct BuiltInStringType : public ConcreteType
	{
		BuiltInStringType();

		// Unique instance of type definition
		static std::shared_ptr<BuiltInStringType> CreateType();
	};

	// Built-in blob type
	struct BuiltInBlobType : public ConcreteType
	{
		BuiltInBlobType();

		// Unique instance of type definition
		static std::shared_ptr<BuiltInBlobType> CreateType();
	};

	// Built-in hash type
	struct BuiltInHashType : public ConcreteType
	{
		BuiltInHashType();

		// Unique instance of type definition
		static std::shared_ptr<BuiltInHashType> CreateType();
	};
	// Built-in bigint type
	struct BuiltInBigIntType : public ConcreteType
	{
		BuiltInBigIntType();

		// Unique instance of type definition
		static std::shared_ptr<BuiltInBigIntType> CreateType();
	};
}
