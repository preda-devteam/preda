#pragma once

#include "antlr_generated/PredaParser.h"

#include "transpiler.h"
#include "transpiler/PredaTranspiler.h"

class ErrorPortal {
	using ErrorCode = transpiler::ErrorCode;
	using ConcreteTypePtr = transpiler::ConcreteTypePtr;

	uint32_t m_anchorLine = 0, m_anchorPos = 0;

	struct ErrorRecord
	{
		uint32_t line;
		uint32_t pos;
		ErrorCode code;
		std::string message;

		ErrorRecord(uint32_t inLine, uint32_t inPos, ErrorCode inCode, const std::string &inMsg)
			: line(inLine), pos(inPos), code(inCode), message(inMsg)
		{

		}
	};

private:
	void AddError(uint32_t line, uint32_t pos, ErrorCode code, const std::string &msg);
	void AddError(ErrorCode code, const std::string &msg);
	std::string TypeToTypeName(ConcreteTypePtr type);

public:
	ErrorPortal() {}

	void SetAnchor(antlr4::Token *token);

	std::vector<ErrorRecord> m_errors, m_warnings;

	void AddIdentifierRedefinitionError(const std::string &identifier);
	void AddIdentifierTwoUnderscoreError();
	void AddTooManyEnumeratorsError();
	void AddContractDoubleImportError(const std::string &contractName);
	void AddContractImportFailure(const std::string &contractName);
	void AddContractAliasAlreadyUsedError(const std::string &alias, const std::string &aliasOwner);
	void AddIllegalUseOfTypeAsExpressionError();
	void AddIllegalUseOfSystemReservedTypeError(ConcreteTypePtr type);
	void AddTypeMismatchError(ConcreteTypePtr type0, ConcreteTypePtr type1);
	void AddAssignConstReferenceTypeToNonConstError(ConcreteTypePtr type);
	void AddAutoDeclarationWithoutInitializerError();
	void AddReturnValueFromFunctionWithoutReturnTypeError();
	void AddReturnWithoutValueFromFunctionWithReturnTypeError(ConcreteTypePtr expectedReturnType);
	void AddBooleanExpressionExpectedError(ConcreteTypePtr type);
	//void AddRelayFromNoneAddressFunctionError();
	void AddRelayTargetAddressNotAddressTypeError();
	void AddIdentifierNotDefinedError(const std::string &identifierName);
	void AddRelayToNoneFunctionError(const std::string &identifierName);
	void AddRelayShardsToNonShardFunctionError(const std::string &identifierName);
	void AddRelayToNoneRelayFunctionError(const std::string &identifierName);
	void AddMoveOnlyParamOfTxnFunctionOrConstructorError();
	void AddContinueOutsideLoopError();
	void AddBreakOutsideLoopError();
	void AddIllegalUseOfContractTypeError();
	void AddIncorrectTxnAndRelayFuncReturnTypeError();
	void AddFunctionRedefinitionError();
	void AddExportFunctionNameConflictError();
	void AddRelayFunctionCannotBeTransactionOrPublicError();
	void AddEmptyStructError();
	void AddContractNameMistachError(const std::string &nameInCode, const std::string &nameInParam);
	void AddNoReturnFromFunctionWithReturnTypeError();
	void AddMinedDependencyWithRelayError();
	void AddNoMatchingOverloadedFunctionError();
	void AddArgumentListLengthMismatchError(size_t numExpected, size_t numGiven);
	void AddConstantOutOfRangeError();
	void AddIdentifierScopeUnaccessibleError(const std::string &identifierName, const std::string &identifierScope, const std::string& currentScope);
	//void AddAccessFunctionOfHigherContextClassError(const std::string &identifierName);
	void AddSpaceInNegativeNumberLiteralError();
	void AddNoMatchingConstructorError(const std::string &typeName);
	void AddNotAMemberOfError(const std::string &identifierName, const std::string &typeName);
	void AddVoidOperandError(const std::string &operatorStr, const std::string &operandStr);
	void AddUnsupportedOperatorError(ConcreteTypePtr type, const std::string &operatorStr);
	void AddAssignToNonLValueError();
	void AddAssignToConstError();
	void AddUnsupportedIndexTypeError(ConcreteTypePtr hostType, ConcreteTypePtr indexType);
	void AddCallNonConstFromConstContextError(const std::string &calleeName);
	void AddNotValidTypeError(const std::string &typeName);
	void AddReservedFunctionMustBeShardError(const std::string &functionName);
	void AddReservedFunctionMayNotBeShardError(const std::string &functionName);
	void AddReservedFunctionMustBeConstError(const std::string &functionName);
	void AddReservedFunctionMayNotHaveReturnValueError(const std::string &functionName);
	void AddReservedFunctionMayNotHaveParametersError(const std::string &functionName);
	void AddReservedFunctionMustHaveSingleBooleanParameterError(const std::string &functionName);
	void AddReservedFunctionCannotBePublicOrExportError(const std::string &functionName);
	void AddReservedFunctionHasTooHighBlockDependencyError(const std::string &functionName);
	void AddReservedFunctionHasTransactionDependencyError(const std::string &functionName);
	//void AddTokenTypeUnavailableError(const std::string &tokenTypeName);
	void AddRelayToFunctionWithConstMoveOnlyParamError();
	void AddContractNameAlreadyUsedError(const std::string &contractFullName);
	void AddInvalidAddressLiteralError(const std::string &literalName);
	void AddInvalidHashLiteralError(const std::string &literalName);
	void AddFunctionCallMissingArgumentListError();
	//void AddContractVariableDeclarationWithoutInitializerError();
	void AddIllegalReferenceToNonStaticMemberError(const std::string &referenceText);
	void AddCallSystemReservedFunctionError();
	//void AddReservedFunctionHasRelayError(const std::string &functionName);
	void AddRelayShardsToFunctionWithMoveOnlyParamError();
	void AddRelayShardsOutsideGlobalError();
	void AddRelayGlobalFromGlobalError();
	void AddRelayGlobalToNonGlobalFunctionError(const std::string& identifierName);
	void AddRelayTargetAndFunctionScopeMismatchError(const std::string& targetType, const std::string& functionName, const std::string& functionScope);
	//void AddOnDeployCannotBeAddressFunctionError();
	void AddBlobInGlobalStateVariableError();
	void AddInaccessibleGlobalFunctionFromNonGlobalFunctionError(const std::string& identifierName);
	void AddReservedFunctionMustBeGlobalError(const std::string& functionName);
	void AddFunctionConstnessOrContextClassNotMatchInterfaceError(const std::string &interfaceName);
	void AddInterfaceFunctionImplementedButNotPublicError(const std::string& interfaceName);
	void AddInterfaceFunctionNotImplementedError(const std::string& interfaceName, const std::string missingFunction);
	void AddInvalidScopeError(const std::string& scopeName);
	void AssigningMemberVarToConstVarError(const std::string& identifierName);
	void AddInvalidRelayTargetTypeError(const std::string& targetType);
	void AddInvalidConstMemberVarTypeError();
	void AddNonDeployableTypeError(const std::string& expressionText);
	void AddMultipleConstructorError();
	void AddDeployInNonGlobalError();
	void AddUseCurrentContractTypeError();
	void AddRelayNextFromShardError();
	void AddMemberOnlyAccessibleViaTypeName(const std::string& identifierName, const std::string& typeName);

	void AddSyntaxError(uint32_t line, uint32_t pos, const std::string &msg);
	void AddInternalError(uint32_t line, uint32_t pos, const std::string &msg);
	void AddInternalError(const std::string &msg);
	void AddInternalError(antlr4::Token *token, const std::string &msg);

	void AddCompileWarning(uint32_t line, uint32_t pos, const std::string &msg);
};
