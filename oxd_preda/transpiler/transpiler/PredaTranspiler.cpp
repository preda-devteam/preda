#include <assert.h>

#include "PredaBuiltInConcreteTypes.h"
#include "PredaBuiltInTemplateTypes.h"
#include "PredaBuiltInABITypes.h"

#include "PredaTranspiler.h"

namespace transpiler{

	PredaTranspilerContext::PredaTranspilerContext()
	{
		RegisterFundementalTypes();

		// relies on int types, must be defined after them
		RegisterTokenType();

		RegisterBuiltInTemplatedContainerTypes();

		RegisterRuntimeContextTypes();
	}

	void IntArithmeticOperation(const PredaTranspilerContext::OperatorProcessor::expressionPack& exprpk, ConcreteTypePtr resultType, std::string& result)
	{
		if (resultType == exprpk.left_type)
		{
			result = exprpk.left_text + " " + exprpk.operand_str + " " + resultType->outputFullName + "(" + exprpk.right_text + ")";
		}
		else
		{
			result = resultType->outputFullName + "(" + exprpk.left_text + ") " + exprpk.operand_str + " " + exprpk.right_text;
		}
	}
	void IntArithmeticAssignmentOperation(const PredaTranspilerContext::OperatorProcessor::expressionPack& exprpk, ConcreteTypePtr resultType, std::string& result)
	{
		result = exprpk.left_text + " " + exprpk.operand_str + " " + resultType->outputFullName + "(" + exprpk.right_text + ")";
	}
	void IntBitWiseOperation(const PredaTranspilerContext::OperatorProcessor::expressionPack& exprpk, ConcreteTypePtr resultType, std::string& result)
	{
		result = exprpk.left_text + " " + exprpk.operand_str + " " + resultType->outputFullName + "(" + exprpk.right_text + ")";
	}
	void IntComparsionOperation(const PredaTranspilerContext::OperatorProcessor::expressionPack& exprpk, ConcreteTypePtr resultType, std::string& result)
	{
		if (resultType == exprpk.left_type)
		{
			result = exprpk.left_text + " " + exprpk.operand_str + " " + resultType->outputFullName + "(" + exprpk.right_text + ")";
		}
		else
		{
			result = resultType->outputFullName + "(" + exprpk.left_text + ") " + exprpk.operand_str + " " + exprpk.right_text;
		}
	}
	void UnchangingOperation(const PredaTranspilerContext::OperatorProcessor::expressionPack& exprpk, ConcreteTypePtr resultType, std::string& result)
	{
		result = exprpk.left_text + " " + exprpk.operand_str + " " + exprpk.right_text;
	}

	void PredaTranspilerContext::RegisterFundementalTypes()
	{
		RegisterFundementalIntegerTypes();
		RegisterFundementalFloatTypes();
		bool res = true;

		m_builtInBoolType = BuiltInBoolType::CreateType();
		std::vector<OperatorTypeBitMask> LogicalOp({ OperatorTypeBitMask::LogicalOrBit, OperatorTypeBitMask::LogicalAndBit });
		for (int i = 0; i < LogicalOp.size(); i++)
		{
			OperatorProcessor::operatorMapKey key = std::make_tuple(LogicalOp[i], m_builtInBoolType, m_builtInBoolType);
			opProcessor.m.emplace(key, OperatorProcessor::operationResult({ m_builtInBoolType, &UnchangingOperation }));
		}
		res = res && (globalType->AttachInnerConcreteType(m_builtInBoolType));
		res = res && (m_builtInBoolType->DefineDefaultConstructor() != nullptr);
		assert(res);

		// string type
		{
			m_builtInStringType = BuiltInStringType::CreateType();
			res = res && (globalType->AttachInnerConcreteType(m_builtInStringType));
			res = res && (m_builtInStringType->DefineDefaultConstructor() != nullptr);
			// add member functions
			{
				FunctionSignature signature;

				signature.flags = uint32_t(FunctionFlags::IsConst);
				signature.returnType = QualifiedConcreteType(GetBuiltInIntegerType(16, false), false, false);
				res = res && (m_builtInStringType->DefineMemberFunction("length", signature, false) != nullptr);

				signature.flags = 0;
				signature.returnType = QualifiedConcreteType(nullptr, true, false);
				signature.parameters.push_back(Allocator::New<DefinedIdentifier>(GetBuiltInStringType(), true, true, "value", 0));
				res = res && (m_builtInStringType->DefineMemberFunction("set", signature, false) != nullptr);

				signature.flags = 0;
				signature.returnType = QualifiedConcreteType(GetBuiltInStringType(), false, false);
				res = res && (m_builtInStringType->DefineMemberFunction("append", signature, false) != nullptr);
			}

			// Create conversion functions from all built-in integer types
			{
				FunctionSignature signature;
				signature.flags = uint32_t(FunctionFlags::IsConst);
				signature.parameters.resize(1);
				signature.returnType = QualifiedConcreteType(m_builtInStringType, false, false);

				signature.parameters[0] = (Allocator::New<DefinedIdentifier>(GetBuiltInIntegerType(8, false), true, true, "src", 0));
				res = res && (m_builtInStringType->DefineMemberFunction("@constructor", signature, false) != nullptr);
				signature.parameters[0] = (Allocator::New<DefinedIdentifier>(GetBuiltInIntegerType(16, false), true, true, "src", 0));
				res = res && (m_builtInStringType->DefineMemberFunction("@constructor", signature, false) != nullptr);
				signature.parameters[0] = (Allocator::New<DefinedIdentifier>(GetBuiltInIntegerType(32, false), true, true, "src", 0));
				res = res && (m_builtInStringType->DefineMemberFunction("@constructor", signature, false) != nullptr);
				signature.parameters[0] = (Allocator::New<DefinedIdentifier>(GetBuiltInIntegerType(64, false), true, true, "src", 0));
				res = res && (m_builtInStringType->DefineMemberFunction("@constructor", signature, false) != nullptr);
				signature.parameters[0] = (Allocator::New<DefinedIdentifier>(GetBuiltInIntegerType(128, false), true, true, "src", 0));
				res = res && (m_builtInStringType->DefineMemberFunction("@constructor", signature, false) != nullptr);
				signature.parameters[0] = (Allocator::New<DefinedIdentifier>(GetBuiltInIntegerType(256, false), true, true, "src", 0));
				res = res && (m_builtInStringType->DefineMemberFunction("@constructor", signature, false) != nullptr);
				signature.parameters[0] = (Allocator::New<DefinedIdentifier>(GetBuiltInIntegerType(512, false), true, true, "src", 0));
				res = res && (m_builtInStringType->DefineMemberFunction("@constructor", signature, false) != nullptr);

				signature.parameters[0] = (Allocator::New<DefinedIdentifier>(GetBuiltInIntegerType(8, true), true, true, "src", 0));
				res = res && (m_builtInStringType->DefineMemberFunction("@constructor", signature, false) != nullptr);
				signature.parameters[0] = (Allocator::New<DefinedIdentifier>(GetBuiltInIntegerType(16, true), true, true, "src", 0));
				res = res && (m_builtInStringType->DefineMemberFunction("@constructor", signature, false) != nullptr);
				signature.parameters[0] = (Allocator::New<DefinedIdentifier>(GetBuiltInIntegerType(32, true), true, true, "src", 0));
				res = res && (m_builtInStringType->DefineMemberFunction("@constructor", signature, false) != nullptr);
				signature.parameters[0] = (Allocator::New<DefinedIdentifier>(GetBuiltInIntegerType(64, true), true, true, "src", 0));
				res = res && (m_builtInStringType->DefineMemberFunction("@constructor", signature, false) != nullptr);
				signature.parameters[0] = (Allocator::New<DefinedIdentifier>(GetBuiltInIntegerType(128, true), true, true, "src", 0));
				res = res && (m_builtInStringType->DefineMemberFunction("@constructor", signature, false) != nullptr);
				signature.parameters[0] = (Allocator::New<DefinedIdentifier>(GetBuiltInIntegerType(256, true), true, true, "src", 0));
				res = res && (m_builtInStringType->DefineMemberFunction("@constructor", signature, false) != nullptr);
				signature.parameters[0] = (Allocator::New<DefinedIdentifier>(GetBuiltInIntegerType(512, true), true, true, "src", 0));
				res = res && (m_builtInStringType->DefineMemberFunction("@constructor", signature, false) != nullptr);

				signature.parameters[0] = (Allocator::New<DefinedIdentifier>(GetBuiltInBigIntType(), true, true, "src", 0));
				res = res && (m_builtInStringType->DefineMemberFunction("@constructor", signature, false) != nullptr);

				signature.parameters[0] = (Allocator::New<DefinedIdentifier>(GetBuiltInFloatType(256), true, true, "src", 0));
				res = res && (m_builtInStringType->DefineMemberFunction("@constructor", signature, false) != nullptr);
				signature.parameters[0] = (Allocator::New<DefinedIdentifier>(GetBuiltInFloatType(512), true, true, "src", 0));
				res = res && (m_builtInStringType->DefineMemberFunction("@constructor", signature, false) != nullptr);
				signature.parameters[0] = (Allocator::New<DefinedIdentifier>(GetBuiltInFloatType(1024), true, true, "src", 0));
				res = res && (m_builtInStringType->DefineMemberFunction("@constructor", signature, false) != nullptr);
			}
			assert(res);
		}

		// address type
		{
			m_builtInAddressType = BuiltInAddressType::CreateType();
			res = res && (globalType->AttachInnerConcreteType(m_builtInAddressType));
			res = res && (m_builtInAddressType->DefineDefaultConstructor() != nullptr);

			// Create conversion functions from string
			{
				FunctionSignature signature;
				signature.flags = uint32_t(FunctionFlags::IsConst);
				signature.parameters.resize(1);
				signature.returnType = QualifiedConcreteType(m_builtInAddressType, true, false);

				signature.parameters[0] = (Allocator::New<DefinedIdentifier>(GetBuiltInStringType(), true, true, "src", 0));
				res = res && (m_builtInAddressType->DefineMemberFunction("@constructor", signature, false) != nullptr);
			}
			// string constructor with address
			{
				FunctionSignature signature;
				signature.flags = uint32_t(FunctionFlags::IsConst);
				signature.parameters.resize(1);
				signature.returnType = QualifiedConcreteType(m_builtInStringType, false, false);

				signature.parameters[0] = (Allocator::New<DefinedIdentifier>(m_builtInAddressType, false, true, "src", 0));
				res = res && (m_builtInStringType->DefineMemberFunction("@constructor", signature, false) != nullptr);
			}
			// add member functions
			{
				FunctionSignature signature;
				signature.flags = uint32_t(FunctionFlags::IsConst);
				signature.returnType = QualifiedConcreteType(GetBuiltInBoolType(), true, false);
				bool res = true;
				res = res && (m_builtInAddressType->DefineMemberFunction("is_user", signature, false) != nullptr);
				res = res && (m_builtInAddressType->DefineMemberFunction("is_delegated", signature, false) != nullptr);
				res = res && (m_builtInAddressType->DefineMemberFunction("is_dapp", signature, false) != nullptr);
				res = res && (m_builtInAddressType->DefineMemberFunction("is_asset", signature, false) != nullptr);
				res = res && (m_builtInAddressType->DefineMemberFunction("is_name", signature, false) != nullptr);
				res = res && (m_builtInAddressType->DefineMemberFunction("is_contract", signature, false) != nullptr);
				res = res && (m_builtInAddressType->DefineMemberFunction("is_custom", signature, false) != nullptr);
				assert(res);
			}

			assert(res);
		}

		// blob type
		m_builtInBlobType = BuiltInBlobType::CreateType();
		res = res && (globalType->AttachInnerConcreteType(m_builtInBlobType));
		res = res && (m_builtInBlobType->DefineDefaultConstructor() != nullptr);
		assert(res);

		// hash type
		{
			m_builtInHashType = BuiltInHashType::CreateType();
			res = res && (globalType->AttachInnerConcreteType(m_builtInHashType));
			res = res && (m_builtInHashType->DefineDefaultConstructor() != nullptr);

			// Create conversion functions from string
			{
				FunctionSignature signature;
				signature.flags = uint32_t(FunctionFlags::IsConst);
				signature.parameters.resize(1);
				signature.returnType = QualifiedConcreteType(m_builtInHashType, true, false);

				signature.parameters[0] = (Allocator::New<DefinedIdentifier>(GetBuiltInStringType(), true, true, "src", 0));
				res = res && (m_builtInHashType->DefineMemberFunction("@constructor", signature, false) != nullptr);
			}
			{
				FunctionSignature signature;
				signature.flags = uint32_t(FunctionFlags::IsConst);
				signature.parameters.resize(1);
				signature.returnType = QualifiedConcreteType(m_builtInStringType, false, false);

				signature.parameters[0] = (Allocator::New<DefinedIdentifier>(m_builtInHashType, false, true, "src", 0));
				res = res && (m_builtInStringType->DefineMemberFunction("@constructor", signature, false) != nullptr);
			}
			// Create conversion functions to address
			{
				FunctionSignature signature;
				signature.flags = uint32_t(FunctionFlags::IsConst);
				signature.parameters.resize(1);
				signature.returnType = QualifiedConcreteType(m_builtInAddressType, true, false);

				signature.parameters[0] = (Allocator::New<DefinedIdentifier>(m_builtInHashType, true, true, "src", 0));
				res = res && (m_builtInAddressType->DefineMemberFunction("@constructor", signature, false) != nullptr);
			}
			// Create conversion functions to uint256
			{
				FunctionSignature signature;
				signature.flags = uint32_t(FunctionFlags::IsConst);
				signature.parameters.resize(1);
				signature.returnType = QualifiedConcreteType(GetBuiltInIntegerType(256, false), true, false);

				signature.parameters[0] = (Allocator::New<DefinedIdentifier>(m_builtInHashType, true, true, "src", 0));
				res = res && (GetBuiltInIntegerType(256, false)->DefineMemberFunction("@constructor", signature, false) != nullptr);
			}
			assert(res);
		}
	}

	void PredaTranspilerContext::RegisterTokenType()
	{
		// Register token type
		m_builtInTokenType = Allocator::New<ConcreteType>(ConcreteType::ReferenceType);
		m_builtInTokenType->inputName = "token";
		m_builtInTokenType->outputFullName = typeOutputPrefix + "token";
		m_builtInTokenType->exportName = "token";
		m_builtInTokenType->supportedOperatorMask = uint64_t(OperatorTypeBitMask::AssignmentBit) | uint64_t(OperatorTypeBitMask::DotBit);
		m_builtInTokenType->nestingPropagatableFlags |= uint32_t(PredaTypeNestingPropagatableFlags::MoveOnly);
		m_builtInTokenType->nestingPropagatableFlags |= uint32_t(PredaTypeNestingPropagatableFlags::HasAsset);

		// add default constructor
		{
			bool res = (m_builtInTokenType->DefineDefaultConstructor() != nullptr);
			assert(res);
		}

		// add member function get_id
		{
			FunctionSignature signature;
			signature.returnType = QualifiedConcreteType(GetBuiltInIntegerType(64, false), true, false);
			signature.flags = uint32_t(FunctionFlags::IsConst);
			bool res = (m_builtInTokenType->DefineMemberFunction("get_id", signature, false) != nullptr);
			assert(res);
		}
		// add member function get_amount
		{
			FunctionSignature signature;
			signature.returnType = QualifiedConcreteType(GetBuiltInBigIntType(), true, false);
			signature.flags = uint32_t(FunctionFlags::IsConst);
			bool res = (m_builtInTokenType->DefineMemberFunction("get_amount", signature, false) != nullptr);
			assert(res);
		}
		// add member function transfer
		{
			FunctionSignature signature;
			signature.returnType = QualifiedConcreteType(GetBuiltInBoolType(), true, false);
			signature.parameters.push_back(Allocator::New<DefinedIdentifier>(GetBuiltInTokenType(), false, true, "recipient", 0));
			signature.parameters.push_back(Allocator::New<DefinedIdentifier>(GetBuiltInBigIntType(), true, true, "transfer_amount", 0));
			signature.flags = 0;
			bool res = (m_builtInTokenType->DefineMemberFunction("transfer", signature, false) != nullptr);
			assert(res);
		}
		// add member function transfer_all
		{
			FunctionSignature signature;
			signature.returnType = QualifiedConcreteType(GetBuiltInBoolType(), true, false);
			signature.parameters.push_back(Allocator::New<DefinedIdentifier>(m_builtInTokenType, false, true, "recipient", 0));
			signature.flags = 0;
			bool res = (m_builtInTokenType->DefineMemberFunction("transfer_all", signature, false) != nullptr);
			assert(res);
		}
		// add member function deposit
		{
			FunctionSignature signature;
			signature.returnType = QualifiedConcreteType(nullptr, true, false);
			signature.flags = uint32_t(ScopeType::Address);
			bool res = (m_builtInTokenType->DefineMemberFunction("deposit", signature, false) != nullptr);
			assert(res);
		}
		// add static member function id_to_symbol
		{
			FunctionSignature signature;
			signature.returnType = QualifiedConcreteType(GetBuiltInStringType(), true, false);
			signature.parameters.push_back(Allocator::New<DefinedIdentifier>(GetBuiltInIntegerType(64, false), true, true, "id", 0));
			signature.flags = 0;
			bool res = (m_builtInTokenType->DefineMemberFunction("id_to_symbol", signature, true) != nullptr);
			assert(res);
		}
		// add static member function symbol_to_id
		{
			FunctionSignature signature;
			signature.returnType = QualifiedConcreteType(GetBuiltInIntegerType(64, false), true, false);
			signature.parameters.push_back(Allocator::New<DefinedIdentifier>(GetBuiltInStringType(), true, true, "symbol", 0));
			signature.flags = 0;
			bool res = (m_builtInTokenType->DefineMemberFunction("symbol_to_id", signature, true) != nullptr);
			assert(res);
		}

		bool res = (globalType->AttachInnerConcreteType(m_builtInTokenType));
		assert(res);
	}

	void PredaTranspilerContext::RegisterFundementalFloatTypes()
	{
		uint32_t floatBitWidths[] = { 256, 512, 1024 };
		for (size_t i = 0; i < sizeof(floatBitWidths) / sizeof(floatBitWidths[0]); i++){
			uint32_t bitWidth = floatBitWidths[i];
			m_builtFloatType[i] = BuiltInFloatTypeFactory::CreateFloatType(bitWidth);
			bool res = (m_builtFloatType[i]->DefineDefaultConstructor() != nullptr);
			res &= (globalType->AttachInnerConcreteType(m_builtFloatType[i]));
			assert(res);
		}
	}

	void PredaTranspilerContext::RegisterFundementalIntegerTypes()
	{
		uint32_t intBitWidths[] = { 8, 16, 32, 64, 128, 256, 512 };

		std::vector<ConcreteTypePtr> allIntegerTypes;

		// Create the built-in int and uint types
		for (size_t i = 0; i < sizeof(intBitWidths) / sizeof(intBitWidths[0]); i++)
		{
			int bitWidth = intBitWidths[i];
			m_builtInUintType[i] = BuiltInIntegerTypeFactory::CreateIntegerType(bitWidth, false);
			m_builtInIntType[i] = BuiltInIntegerTypeFactory::CreateIntegerType(bitWidth, true);

			allIntegerTypes.push_back(m_builtInUintType[i]);
			allIntegerTypes.push_back(m_builtInIntType[i]);
		}

		// Create built-in bigint type
		m_builtInBigIntType = BuiltInBigIntType::CreateType();
		// add member function div_uint32
		{
			FunctionSignature signature;
			signature.returnType = QualifiedConcreteType(GetBuiltInBigIntType(), false, false);
			signature.parameters.push_back(Allocator::New<DefinedIdentifier>(GetBuiltInIntegerType(32, false), true, true, "divisor", 0));
			signature.flags = uint32_t(FunctionFlags::IsConst);
			bool res = (m_builtInBigIntType->DefineMemberFunction("div_uint32", signature, false) != nullptr);
			assert(res);
		}
		allIntegerTypes.push_back(m_builtInBigIntType);

		// Create default constructor
		for (size_t i = 0; i < allIntegerTypes.size(); i++)
		{
			bool res = (allIntegerTypes[i]->DefineDefaultConstructor() != nullptr);
			assert(res);
		}

		// Create conversion functions between all built-in integer types
		FunctionSignature signature;
		signature.flags = uint32_t(FunctionFlags::IsConst);
		signature.parameters.resize(1);

		for (size_t i = 0; i < allIntegerTypes.size(); i++)
		{
			signature.parameters[0] = (Allocator::New<DefinedIdentifier>(allIntegerTypes[i], true, true, "src", 0));
			for (size_t j = 0; j < allIntegerTypes.size(); j++)
			{
				signature.returnType = QualifiedConcreteType(allIntegerTypes[j], true, false);
				bool res = (allIntegerTypes[j]->DefineMemberFunction("@constructor", signature, false) != nullptr);
				assert(res);
			}
		}

		for (size_t i = 0; i < allIntegerTypes.size(); i++)
		{
			bool res = (globalType->AttachInnerConcreteType(allIntegerTypes[i]));
			assert(res);
		}
		std::vector<OperatorTypeBitMask> ArithmeticOp({ OperatorTypeBitMask::AddBit, OperatorTypeBitMask::SubtractBit, OperatorTypeBitMask::MultiplyBit, OperatorTypeBitMask::DivideBit, OperatorTypeBitMask::ModuloBit });
		//bitwise not operation is not included because it only taks one operand
		std::vector<OperatorTypeBitMask> BitWiseOp({ OperatorTypeBitMask::ShiftLeftBit, OperatorTypeBitMask::ShiftRightBit,
			OperatorTypeBitMask::BitwiseAndBit, OperatorTypeBitMask::BitwiseXorBit, OperatorTypeBitMask::BitwiseOrBit, OperatorTypeBitMask::AssignmentBitwiseAndBit, 
			OperatorTypeBitMask::AssignmentBitwiseXorBit, OperatorTypeBitMask::AssignmentBitwiseOrBit, OperatorTypeBitMask::AssignmentShiftLeftBit, OperatorTypeBitMask::AssignmentShiftRightBit });
		std::vector<OperatorTypeBitMask> ArithmeticAssignmentOp({ OperatorTypeBitMask::AssignmentBit, OperatorTypeBitMask::AssignmentAddBit, OperatorTypeBitMask::AssignmentSubtractBit, OperatorTypeBitMask::AssignmentMultiplyBit, OperatorTypeBitMask::AssignmentDivideBit, OperatorTypeBitMask::AssignmentModuloBit });
		std::vector<OperatorTypeBitMask> ComparsionOp({ OperatorTypeBitMask::LessThanBit, OperatorTypeBitMask::GreaterThanBit, OperatorTypeBitMask::LessThanOrEqualBit, OperatorTypeBitMask::GreaterThanOrEqualBit, OperatorTypeBitMask::EqualBit, OperatorTypeBitMask::NotEqualBit });
		//allIntegerTypes: uint8, int8, uint16, int16, ....... uint512, int512, bigint (signed int -> odd, unsigned int -> even) 
		//case 1: int16 -> uint16 NO
		//case 2: int16 -> uint32 NO
		//case 3: int16 -> int32 YES
		//case 4: int16 -> bigint YES
		//case 5: uint16 -> int16 NO
		//case 6: uint16 -> int32 NO
		//case 7: uint16 -> uint32 YES
		//case 8: uint16 -> bigint YES
		for (int j = 0; j < allIntegerTypes.size(); j++)
		{
			for (int k = 0; k < allIntegerTypes.size(); k++)
			{
				if (k != allIntegerTypes.size() - 1 && j != allIntegerTypes.size() - 1 && ((j - k) % 2 != 0)) //signed int
				{
					continue;
				}
				for (int i = 0; i < ArithmeticOp.size(); i++)
				{
					OperatorProcessor::operatorMapKey key = std::make_tuple(ArithmeticOp[i], allIntegerTypes[j], allIntegerTypes[k]);
					opProcessor.m.emplace(key, OperatorProcessor::operationResult({ allIntegerTypes[std::max(j,k)], &IntArithmeticOperation }));
				}
				for (int i = 0; i < ArithmeticAssignmentOp.size(); i++)
				{
					if (j > k)
					{
						OperatorProcessor::operatorMapKey key = std::make_tuple(ArithmeticAssignmentOp[i], allIntegerTypes[j], allIntegerTypes[k]);
						opProcessor.m.emplace(key, OperatorProcessor::operationResult({ allIntegerTypes[j], &IntArithmeticAssignmentOperation }));
					}
				}
				for (int i = 0; i < BitWiseOp.size(); i++)
				{
					if (j % 2 == 0 && k <= j && k != allIntegerTypes.size() - 1 && j != allIntegerTypes.size() - 1) //opt out bigint
					{
						OperatorProcessor::operatorMapKey key = std::make_tuple(BitWiseOp[i], allIntegerTypes[j], allIntegerTypes[k]);
						opProcessor.m.emplace(key, OperatorProcessor::operationResult({ allIntegerTypes[j], &IntBitWiseOperation }));
					}
				}
				for (int i = 0; i < ComparsionOp.size(); i++)
				{
					OperatorProcessor::operatorMapKey key = std::make_tuple(ComparsionOp[i], allIntegerTypes[j], allIntegerTypes[k]);
					opProcessor.m.emplace(key, OperatorProcessor::operationResult({ allIntegerTypes[std::max(j,k)], &IntComparsionOperation }));
				}
			}
		}
		
		return;
	}

	void PredaTranspilerContext::RegisterBuiltInTemplatedContainerTypes()
	{
		bool res = true;
		// Register built-in template types
		m_builtInArrayType = BuiltInArrayType::CreateType(this, "array");
		res = res && (globalType->AttachInnerTemplateType(m_builtInArrayType));
		m_builtInMapType = BuiltInMapType::CreateType(this, "map");
		res = res && (globalType->AttachInnerTemplateType(m_builtInMapType));
		m_builtInScatteredMapType = BuiltInMapType::CreateType(this, "scattered_map");
		res = res && (globalType->AttachInnerTemplateType(m_builtInScatteredMapType));
		m_builtInScatteredArrayType = BuiltInArrayType::CreateType(this, "scattered_array");
		res = res && (globalType->AttachInnerTemplateType(m_builtInScatteredArrayType));
		assert(res);
	}

	void PredaTranspilerContext::RegisterRuntimeContextTypes()
	{
		bool res = true;
		ConcreteTypePtr blockStructType = BuiltInBlockStructType::CreateType(this);
		res = res && (globalType->AttachInnerConcreteType(blockStructType));
		res = res && (globalType->DefineMemberVariable(blockStructType, "__block", 0, true, false, true));

		ConcreteTypePtr transactionStructType = BuiltInTransactionStructType::CreateType(this);
		res = res && (globalType->AttachInnerConcreteType(transactionStructType));
		res = res && (globalType->DefineMemberVariable(transactionStructType, "__transaction", 0, true, false, true));

		ConcreteTypePtr eventStructType = BuiltInEventStructType::CreateType(this);
		res = res && (globalType->AttachInnerConcreteType(eventStructType));
		res = res && (globalType->DefineMemberVariable(eventStructType, "__event", 0, true, false, true));

		ConcreteTypePtr debugStructType = BuiltInDebugStructType::CreateType(this);
		res = res && (globalType->AttachInnerConcreteType(debugStructType));
		res = res && (globalType->DefineMemberVariable(debugStructType, "__debug", 0, true, false, true));

		assert(res);

		{
			DefinedIdentifierPtr pFunc = debugStructType->GetMember("print", nullptr);
			assert(pFunc != nullptr);
			m_builtInDebugPrintFunctionType = pFunc->qualifiedType.baseConcreteType;
		}
		{
			DefinedIdentifierPtr pFunc = debugStructType->GetMember("assert", nullptr);
			assert(pFunc != nullptr);
			m_builtInDebugAssertFunctionType = pFunc->qualifiedType.baseConcreteType;
		}
	}

	bool PredaTranspilerContext::OperatorProcessor::processOperation(const expressionPack& expr, std::string& result, ConcreteTypePtr& resultType)
	{
		ConcreteTypePtr left_type = expr.left_type;
		ConcreteTypePtr right_type = expr.right_type;
		operatorMapKey k = std::make_tuple(expr.type, left_type, right_type);
		auto iter = m.find(k);
		if (iter == m.end())
		{
			return false;
		}
		(*iter->second.second)(expr, iter->second.first, result);
		resultType = iter->second.first;
		return true;
	}
}
