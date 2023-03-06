#pragma once

#include <vector>
#include <string>
#include <map>
#include <memory>

namespace transpiler {

	extern const std::string typeOutputPrefix;
	extern const std::string identifierOutputPrefix;

	// Forward declaration of ConcreteType since it's used by DefinedIdentifier
	struct ConcreteType;
	using ConcreteTypePtr = std::shared_ptr<ConcreteType>;

	struct QualifiedConcreteType
	{
		ConcreteTypePtr baseConcreteType;
		// if baseConcreteType is value type, bIsConst decides whether the value could be modified.
		// If baseConcreteType is function type, bIsConst means whether it's being called from a const context. (function types can never be modified, they don't support operator "=")
		bool bIsConst = true;
		bool bIsLValue = false;
		QualifiedConcreteType()
		{
		}
		QualifiedConcreteType(ConcreteTypePtr inBaseConcreteType, bool inIsConst, bool inIsLValue)
		{
			baseConcreteType = inBaseConcreteType;
			bIsConst = inIsConst;
			bIsLValue = inIsLValue;
		}

		bool operator == (const QualifiedConcreteType& rhs) const
		{
			return baseConcreteType == rhs.baseConcreteType && bIsConst == rhs.bIsConst && bIsLValue == rhs.bIsLValue;
		}
		bool operator != (const QualifiedConcreteType& rhs) const
		{
			return ! operator==(rhs);
		}
	};

	struct DefinedIdentifier
	{
		std::string inputName;
		std::string outputName;
		QualifiedConcreteType qualifiedType;
		uint32_t flags = 0;

		DefinedIdentifier(ConcreteTypePtr inType, bool inIsConst, bool inIsLValue, const std::string &inName, uint32_t inFlags);
	};

	using DefinedIdentifierPtr = std::shared_ptr<DefinedIdentifier>;

	struct FunctionSignature
	{
		QualifiedConcreteType returnType;
		std::vector<DefinedIdentifierPtr> parameters;
		std::string doxygenComment;
		uint32_t flags = 0;							// A list of function flags to be defined by the language itself

		FunctionSignature()
		{
		}

		FunctionSignature(const QualifiedConcreteType &inReturnType, const std::vector<DefinedIdentifierPtr> &inParameters, uint32_t inFlags)
		{
			returnType = inReturnType;
			parameters = inParameters;
			flags = inFlags;
		}

		bool operator==(const FunctionSignature &other) const
		{
			//Only compare parameter list
			if (parameters.size() != other.parameters.size())
				return false;
			for (size_t i = 0; i < parameters.size(); i++)
			{
				//only compare type, ignore the const-qualifier
				if (parameters[i]->qualifiedType.baseConcreteType != other.parameters[i]->qualifiedType.baseConcreteType)
					return false;
			}

			return true;
		}
	};

	enum class OperatorType : unsigned char {
		Scope = 0,

		PostIncrement,
		PostDecrement,
		Parentheses,
		Bracket,
		Dot,

		PreIncrement,
		PreDecrement,
		UnaryPlus,
		UnaryMinus,
		LogicalNot,
		BitwiseNot,
		New,
		Delete,

		Power,

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

		Max
	};

	enum class OperatorTypeBitMask : uint64_t {
		ScopeBit = 1ull << (unsigned char)(OperatorType::Scope),

		PostIncrementBit = 1ull << (unsigned char)(OperatorType::PostIncrement),
		PostDecrementBit = 1ull << (unsigned char)(OperatorType::PostDecrement),
		ParenthesesBit = 1ull << (unsigned char)(OperatorType::Parentheses),
		BracketBit = 1ull << (unsigned char)(OperatorType::Bracket),
		DotBit = 1ull << (unsigned char)(OperatorType::Dot),

		PreIncrementBit = 1ull << (unsigned char)(OperatorType::PreIncrement),
		PreDecrementBit = 1ull << (unsigned char)(OperatorType::PreDecrement),
		UnaryPlusBit = 1ull << (unsigned char)(OperatorType::UnaryPlus),
		UnaryMinusBit = 1ull << (unsigned char)(OperatorType::UnaryMinus),
		LogicalNotBit = 1ull << (unsigned char)(OperatorType::LogicalNot),
		BitwiseNotBit = 1ull << (unsigned char)(OperatorType::BitwiseNot),
		NewBit = 1ull << (unsigned char)(OperatorType::New),
		DeleteBit = 1ull << (unsigned char)(OperatorType::Delete),

		PowerBit = 1ull << (unsigned char)(OperatorType::Power),

		MultiplyBit = 1ull << (unsigned char)(OperatorType::Multiply),
		DivideBit = 1ull << (unsigned char)(OperatorType::Divide),
		ModuloBit = 1ull << (unsigned char)(OperatorType::Modulo),

		AddBit = 1ull << (unsigned char)(OperatorType::Add),
		SubtractBit = 1ull << (unsigned char)(OperatorType::Subtract),

		ShiftLeftBit = 1ull << (unsigned char)(OperatorType::ShiftLeft),
		ShiftRightBit = 1ull << (unsigned char)(OperatorType::ShiftRight),

		LessThanBit = 1ull << (unsigned char)(OperatorType::LessThan),
		GreaterThanBit = 1ull << (unsigned char)(OperatorType::GreaterThan),
		LessThanOrEqualBit = 1ull << (unsigned char)(OperatorType::LessThanOrEqual),
		GreaterThanOrEqualBit = 1ull << (unsigned char)(OperatorType::GreaterThanOrEqual),

		EqualBit = 1ull << (unsigned char)(OperatorType::Equal),
		NotEqualBit = 1ull << (unsigned char)(OperatorType::NotEqual),

		BitwiseAndBit = 1ull << (unsigned char)(OperatorType::BitwiseAnd),

		BitwiseXorBit = 1ull << (unsigned char)(OperatorType::BitwiseXor),

		BitwiseOrBit = 1ull << (unsigned char)(OperatorType::BitwiseOr),

		LogicalAndBit = 1ull << (unsigned char)(OperatorType::LogicalAnd),

		LogicalOrBit = 1ull << (unsigned char)(OperatorType::LogicalOr),

		AssignmentBit = 1ull << (unsigned char)(OperatorType::Assignment),
		AssignmentAddBit = 1ull << (unsigned char)(OperatorType::AssignmentAdd),
		AssignmentSubtractBit = 1ull << (unsigned char)(OperatorType::AssignmentSubtract),
		AssignmentMultiplyBit = 1ull << (unsigned char)(OperatorType::AssignmentMultiply),
		AssignmentDivideBit = 1ull << (unsigned char)(OperatorType::AssignmentDivide),
		AssignmentModuloBit = 1ull << (unsigned char)(OperatorType::AssignmentModulo),
		AssignmentShiftLeftBit = 1ull << (unsigned char)(OperatorType::AssignmentShiftLeft),
		AssignmentShiftRightBit = 1ull << (unsigned char)(OperatorType::AssignmentShiftRight),
		AssignmentBitwiseAndBit = 1ull << (unsigned char)(OperatorType::AssignmentBitwiseAnd),
		AssignmentBitwiseXorBit = 1ull << (unsigned char)(OperatorType::AssignmentBitwiseXor),
		AssignmentBitwiseOrBit = 1ull << (unsigned char)(OperatorType::AssignmentBitwiseOr),

		IncrementAndDecrementBits = PostIncrementBit | PostDecrementBit | PreIncrementBit | PreDecrementBit,
		AddSubMulBits = AddBit | SubtractBit | MultiplyBit | AssignmentAddBit | AssignmentSubtractBit | AssignmentMultiplyBit,
		AddSubMulDivBits = AddSubMulBits | DivideBit | AssignmentDivideBit,
		BitwiseBits = BitwiseNotBit | BitwiseAndBit | BitwiseXorBit | BitwiseOrBit | ShiftLeftBit | ShiftRightBit | AssignmentBitwiseAndBit | AssignmentBitwiseXorBit | AssignmentBitwiseOrBit | AssignmentShiftLeftBit | AssignmentShiftRightBit,
		LogicalBits = LogicalNotBit | LogicalAndBit | LogicalOrBit,
		EqualityComparisonBits = EqualBit | NotEqualBit,
		GenericComparisonBits = EqualityComparisonBits | LessThanBit | GreaterThanBit | LessThanOrEqualBit | GreaterThanOrEqualBit,
	};

	static_assert((unsigned char)(OperatorType::Max) <= sizeof(OperatorTypeBitMask) * 8, "Number of operators more than bit mask size");

	struct TemplateType;

	// A concrete type, could be:
	//   built-in type
	//   user-defined struct
	//   user-defined enum
	//   instantiated template type
	//   function
	//   contract
	//   placeholder for unnamed scopes
	struct ConcreteType : public std::enable_shared_from_this<ConcreteType>
	{
		enum TypeCategory {
			ValueType,
			ReferenceType,
			EnumType,
			FunctionType,
			InterfaceType,
			ContractType,
			SystemReservedType,
			UnnamedScopeType,
			AliasType,
		};

		std::string inputName;																				// the name of this type to match the input source code, e.g. "string", "MyStruct", "array<map<uint, MyStruct>>"
		std::string outputFullName;																			// the output name of this type to the target language, e.g. "___string", "MyStruct", "___vector<___map<uint, MyStruct>>"
		std::string exportName;																				// the export name of this type to identify the type. This should be the same as inputName, except for templated types and user-defined types

		TypeCategory typeCategory;
		bool bIsUserDefinedStructType = false;
		std::map<ConcreteTypePtr, ConcreteTypePtr> boxBracketOperator;			// mapping from box bracket operator index type to value type, e.g. vector<string>[uint] = string; or, map<string, uint>[string] = uint;

		std::vector<DefinedIdentifierPtr> members;
		std::vector<bool> vbMemberIsStatic;
		std::vector<FunctionSignature> vOverloadedFunctions;												// the list of functions overloaded under the name of this variable
		std::vector<std::pair<DefinedIdentifierPtr, size_t>> vInterfaceMemberFuncIndexMapping;				// for interface types, this maps the function index to the corresponding member and overload index
		ConcreteTypePtr outerType;																			// outer type
		std::map<std::string, ConcreteTypePtr> innerConcreteTypes;											// inner concrete types defined under this type
		std::map<std::string, std::shared_ptr<TemplateType>> innerTemplateTypes;							// inner template types defined under this type
		ConcreteTypePtr realType;																			// For alias types, this is the real type behind it
		uint32_t numUnnamedScopes = 0;																		// number of unnamed scopes under this type
		uint64_t supportedOperatorMask = 0ll;																// bitmask for common operators. TODO: extend to support operator overloading based on the operand type
		uint32_t nestingPropagatableFlags = 0;																// flags that should propagate to nesting types e.g. int32 -> array<int32> -> map<address, array<int32>>
		std::string doxygenComment;						//doxygen tag and comments.
		ConcreteType(TypeCategory inTypeCategory);

		DefinedIdentifierPtr GetMember(const std::string &memberName, bool *outIsStatic);
		DefinedIdentifierPtr DefineMemberVariable(ConcreteTypePtr variableType, const std::string &variableName, uint32_t flags, bool bIsConst, bool bIsLValue, bool bIsStatic);
		DefinedIdentifierPtr DefineMemberFunction(const std::string &name, const FunctionSignature &signature, bool bIsStatic);
		DefinedIdentifierPtr DefineDefaultConstructor();

		bool AttachInnerConcreteType(ConcreteTypePtr innerType);
		bool AttachInnerTemplateType(std::shared_ptr<TemplateType> innerType);
		ConcreteTypePtr FindInnerConcreteType(const std::string &typeName);
		std::shared_ptr<TemplateType> FindInnerTemplateType(const std::string &typeName);

		ConcreteTypePtr CreateInnerUnnamedScopeType(const std::string &customLabel);
		ConcreteTypePtr CreateInnerContractType(const std::string &typeName, const std::string &contractfullName);
		ConcreteTypePtr CreateInnerUserDefinedStructType(const std::string &typeName);
		ConcreteTypePtr CreateInnerEnumType(const std::string &typeName);
		ConcreteTypePtr CreateInnerAliasType(const std::string &typeName, ConcreteTypePtr realType);
		ConcreteTypePtr CreateInnerInterfaceType(const std::string& typeName);

		bool IsConstTransitive()
		{
			return typeCategory == ReferenceType || typeCategory == ContractType;
		}
	};

}
