#pragma once
#include <cmath>
#include "BaseTranspiler.h"
#include "PredaCommon.h"

namespace transpiler {

	enum class PredaDefinedVariableFlags : uint32_t {
		ContextClassMask				= 3,
		ContextClassNone				= 0,
		ContextClassGlobal				= 1,
		ContextClassShard				= 2,
		ContextClassAddress				= 3,
	};

	static_assert(uint32_t(PredaFunctionFlags::ContextClassMask) == uint32_t(PredaDefinedVariableFlags::ContextClassMask), "ContextClassMask in PredaFunctionFlags and PredaDefinedVariableFlags don't match.");

	// This must 100% reflect the values of $expressionType in the grammar file
	enum class PredaExpressionTypes : uint8_t {
		PostIncrement = 0,
		PostDecrement,
		Bracket,
		Parentheses,
		Dot,
		SurroundWithParentheses,
		PreIncrement,
		PreDecrement,
		UnaryPlus,
		UnaryMinus,
		LogicalNot,
		BitwiseNot,
		Multiply,
		Divide,
		Modulo,
		Add,
		Subtract,
		ShiftLeft,
		ShiftRight,
		LessThan,
		GreaterThan,
		LessThanOrEqual,
		GreaterThanOrEqual,
		Equal,
		NotEqual,
		BitwiseAnd,
		BitwiseXor,
		BitwiseOr,
		LogicalAnd,
		LogicalOr,
		TernaryConditional,
		Assignment,
		AssignmentAdd,
		AssignmentSubtract,
		AssignmentMultiply,
		AssignmentDivide,
		AssignmentModulo,
		AssignmentShiftLeft,
		AssignmentShiftRight,
		AssignmentBitwiseAnd,
		AssignmentBitwiseXor,
		AssignmentBitwiseOr,
		Primary,
		Max
	};

	enum class PredaTypeNestingPropagatableFlags : uint32_t {
		MoveOnly = 1 << 0,
		HasBlob = 1 << 1,
		HasAsset = 1 << 2,
	};

struct PredaTranspilerContext : public BaseTranspilerContext {
	PredaTranspilerContext();
	void RegisterFundementalTypes();
	void RegisterFundementalFloatTypes();
	void RegisterFundementalIntegerTypes();
	void RegisterTokenType();
	void RegisterBuiltInTemplatedContainerTypes();
	void RegisterRuntimeContextTypes();

	ConcreteTypePtr GetBuiltInIntegerType(size_t bitWidth, bool bSigned)
	{
		if((bitWidth & (bitWidth - 1)) != 0)
		{
			return nullptr;
		}
		return bSigned ? m_builtInIntType[(int)std::log2(bitWidth/8)] : m_builtInUintType[(int)std::log2(bitWidth/8)];
	}

	ConcreteTypePtr GetBuiltInFloatType(size_t floatWidth)
	{
		if(floatWidth%256 != 0 || (floatWidth & (floatWidth - 1)) != 0)
		{
			return nullptr;
		}
		return m_builtFloatType[(int)std::log2(floatWidth / 256)];
	}

	ConcreteTypePtr GetBuiltInBoolType() { return m_builtInBoolType; }
	ConcreteTypePtr GetBuiltInStringType() { return m_builtInStringType; }
	ConcreteTypePtr GetBuiltInAddressType() { return m_builtInAddressType; }
	ConcreteTypePtr GetBuiltInBlobType() { return m_builtInBlobType; }
	ConcreteTypePtr GetBuiltInHashType() { return m_builtInHashType; }
	ConcreteTypePtr GetBuiltInBigIntType() { return m_builtInBigIntType; }
	ConcreteTypePtr GetBuiltInTokenType() { return m_builtInTokenType; }
	std::shared_ptr<TemplateType> GetBuiltInArrayType() { return m_builtInArrayType; }
	std::shared_ptr<TemplateType> GetBuiltInMapType() { return m_builtInMapType; }

	// For fast indexing, we just put in plain array
	ConcreteTypePtr m_builtInUintType[7];
	ConcreteTypePtr m_builtInIntType[7];
	struct OperatorProcessor
	{	
		struct expressionPack
		{
			std::string left_text;
			std::string right_text;
			ConcreteTypePtr left_type;
			ConcreteTypePtr right_type;
			std::string operand_str;
			transpiler::OperatorTypeBitMask type;
		};
		typedef void(*processingFunc)(const expressionPack&, ConcreteTypePtr, std::string&);
		typedef std::tuple<OperatorTypeBitMask, ConcreteTypePtr, ConcreteTypePtr> operatorMapKey;
		typedef std::pair<ConcreteTypePtr, processingFunc> operationResult;
		//if operation on left subexpression and right subexpression is allowed, if allowed, what are the result expression and cast type, which is often the result type.
		//implicit conversion is performed here
		//assignment operator applies to variable assignment and declaration (int a = b and a = b)
		std::map<operatorMapKey, operationResult> m;
		bool processOperation(const expressionPack& expr, std::string& result, ConcreteTypePtr& resultType);
	};
	OperatorProcessor opProcessor;
	//Float data structure
	ConcreteTypePtr m_builtFloatType[3];

	ConcreteTypePtr m_builtInBoolType;
	ConcreteTypePtr m_builtInStringType;
	ConcreteTypePtr m_builtInAddressType;
	ConcreteTypePtr m_builtInBlobType;
	ConcreteTypePtr m_builtInHashType;
	ConcreteTypePtr m_builtInBigIntType;
	ConcreteTypePtr m_builtInTokenType;

	std::shared_ptr<TemplateType> m_builtInArrayType;
	std::shared_ptr<TemplateType> m_builtInMapType;

	ConcreteTypePtr m_builtInDebugPrintFunctionType;
	ConcreteTypePtr m_builtInDebugAssertFunctionType;
};

struct PredaTranspilerOptions {
	bool bDisableDebugPrint = false;
};

}