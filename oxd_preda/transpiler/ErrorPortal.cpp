#include "ErrorPortal.h"

void ErrorPortal::AddError(uint32_t line, uint32_t pos, ErrorCode code, const std::string &msg)
{
	m_errors.emplace_back(line, pos, code, msg);
}

void ErrorPortal::AddError(ErrorCode code, const std::string &msg)
{
	AddError(m_anchorLine, m_anchorPos, code, msg);
}

std::string ErrorPortal::TypeToTypeName(ConcreteTypePtr type)
{
	if (type == nullptr)
		return "void";

	// contract types have their full name stored in the exportName
	if (type->typeCategory == transpiler::ConcreteType::ContractType)
		return type->exportName;
	
	return type->inputName;
}

void ErrorPortal::ErrorPortal::SetAnchor(antlr4::Token *token)
{
	m_anchorLine = (uint32_t)token->getLine();
	m_anchorPos = (uint32_t)token->getCharPositionInLine();
}

void ErrorPortal::AddIdentifierRedefinitionError(const std::string &identifier)
{
	AddError(ErrorCode::IdentifierRedefinition, "identifier \"" + identifier + "\" already defined.");
}

void ErrorPortal::AddIdentifierTwoUnderscoreError()
{
	AddError(ErrorCode::IdentifierTwoUnderscore, "identifier that contains \"__\" are reserved for internal use.");
}

void ErrorPortal::AddTooManyEnumeratorsError()
{
	AddError(ErrorCode::TooManyEnumerators, "enum type cannot have more than 65535 enumerators.");
}

void ErrorPortal::AddContractDoubleImportError(const std::string &contractName)
{
	AddError(ErrorCode::ContractDoubleImport, "contract \"" + contractName + "\" already imported.");
}

void ErrorPortal::AddContractImportFailure(const std::string &contractName)
{
	AddError(ErrorCode::ContractImportFailure, "failed to import contract \"" + contractName + "\".");
}

void ErrorPortal::AddContractAliasAlreadyUsedError(const std::string &alias, const std::string &aliasOwner)
{
	AddError(ErrorCode::ContractAliasAlreadyUsed, "contract alias \"" + alias + "\" already used by \"" + aliasOwner + "\", please use a different alias.");
}

void ErrorPortal::AddIllegalUseOfTypeAsExpressionError()
{
	AddError(ErrorCode::IllegalUseOfTypeAsExpression, "illegal use of type as expression.");
}

void ErrorPortal::AddIllegalUseOfSystemReservedTypeError(ConcreteTypePtr type)
{
	AddError(ErrorCode::IllegalUseOfSystemReservedType, "illegal access of system-reserved type \"" + TypeToTypeName(type) + "\".");
}

void ErrorPortal::AddTypeMismatchError(ConcreteTypePtr type0, ConcreteTypePtr type1)
{
	AddError(ErrorCode::TypeMismatch, "type mismatch: \"" + TypeToTypeName(type0) + "\" and \"" + TypeToTypeName(type1) + "\".");
}

void ErrorPortal::AddAssignConstReferenceTypeToNonConstError(ConcreteTypePtr type)
{
	AddError(ErrorCode::AssignConstReferenceTypeToNonConst, "cannot assign from \"const " + TypeToTypeName(type) + "\" to \"" + TypeToTypeName(type) + "\". A const reference type cannot be assigned to non-const.");
}

void ErrorPortal::AddAutoDeclarationWithoutInitializerError()
{
	AddError(ErrorCode::AutoDeclarationWithoutInitializer, "variable declaration of type 'auto' must have an initializer.");
}

void ErrorPortal::AddReturnValueFromFunctionWithoutReturnTypeError()
{
	AddError(ErrorCode::ReturnValueFromFunctionWithoutReturnType, "returning a value from function with no return type.");
}

void ErrorPortal::AddReturnWithoutValueFromFunctionWithReturnTypeError(ConcreteTypePtr expectedReturnType)
{
	AddError(ErrorCode::ReturnWithoutValueFromFunctionWithReturnType, "returning without a value from a function that expects return value of type \"" + TypeToTypeName(expectedReturnType) + "\".");
}

void ErrorPortal::AddBooleanExpressionExpectedError(ConcreteTypePtr type)
{
	AddError(ErrorCode::BooleanExpressionExpected, "boolean expression expected, \"" + TypeToTypeName(type) + "\" given.");
}

//void ErrorPortal::AddRelayFromNoneAddressFunctionError()
//{
//	AddError(ErrorCode::RelayFromNoneAddressFunction, "relay statement only allowed in per-address functions.");
//}

void ErrorPortal::AddRelayTargetAddressNotAddressTypeError()
{
	AddError(ErrorCode::RelayTargetAddressNotAddressType, "relay address must be address type.");
}

void ErrorPortal::AddIdentifierNotDefinedError(const std::string &identifierName)
{
	AddError(ErrorCode::IdentifierNotDefined, "identifier \"" + identifierName + "\" not defined.");
}

void ErrorPortal::AddRelayToNoneFunctionError(const std::string &identifierName)
{
	AddError(ErrorCode::RelayToNoneFunction, "relay to non-function \"" + identifierName + "\".");
}

void ErrorPortal::AddRelayShardsToNonShardFunctionError(const std::string &identifierName)
{
	AddError(ErrorCode::RelayShardsToNonShardFunction, "relay@shards target \"" + identifierName + "\" must be a per-shard function.");
}

void ErrorPortal::AddRelayToNoneRelayFunctionError(const std::string &identifierName)
{
	AddError(ErrorCode::RelayToNoneRelayFunction, "relay target \"" + identifierName + "\" must be a relay function.");
}

void ErrorPortal::AddMoveOnlyParamOfTxnFunctionOrConstructorError()
{
	AddError(ErrorCode::MoveOnlyParamOfTxnFunctionOrConstructor, "transaction function or contract constructor cannot have move-only type as parameter.");
}

void ErrorPortal::AddContinueOutsideLoopError()
{
	AddError(ErrorCode::ContinueOutsideLoop, "continue statement can only be used inside loops.");
}

void ErrorPortal::AddBreakOutsideLoopError()
{
	AddError(ErrorCode::BreakOutsideLoop, "break statement can only be used inside loops.");
}

void ErrorPortal::AddIllegalUseOfContractTypeError()
{
	AddError(ErrorCode::IllegalUseOfContractType, "illegal use of contract type.");
}

void ErrorPortal::AddIncorrectTxnAndRelayFuncReturnTypeError()
{
	AddError(ErrorCode::IncorrectTxnAndRelayFuncReturnType, "return type of transaction functions and relay functions must be uint16.");
}

void ErrorPortal::AddFunctionRedefinitionError()
{
	AddError(ErrorCode::FunctionRedefinition, "Function redefinition. To overload a function, use a different argument list.");
}

void ErrorPortal::AddExportFunctionNameConflictError()
{
	AddError(ErrorCode::ExportFunctionNameConflict, "cannot export multiple functions with the same name");
}

void ErrorPortal::AddRelayFunctionCannotBeTransactionOrPublicError()
{
	AddError(ErrorCode::RelayFunctionCannotBeTransactionOrPublic, "relay function cannot be defined as public or transaction.");
}

void ErrorPortal::AddEmptyStructError()
{
	AddError(ErrorCode::EmptyStruct, "empty struct type not allowed.");
}

void ErrorPortal::AddContractNameMistachError(const std::string &nameInCode, const std::string &nameInParam)
{
	AddError(ErrorCode::ContractNameMistach, "contract name in source code \"" + nameInCode + "\" differs from given name \"" + nameInParam + "\".");
}

void ErrorPortal::AddNoReturnFromFunctionWithReturnTypeError()
{
	AddError(ErrorCode::NoReturnFromFunctionWithReturnType, "current function is expected to return a value.");
}

void ErrorPortal::AddMinedDependencyWithRelayError()
{
	AddError(ErrorCode::MinedDependencyWithRelay, "function has block dependency of 'mined' and cannot issue relay call directly or indirectly.");
}

void ErrorPortal::AddNoMatchingOverloadedFunctionError()
{
	AddError(ErrorCode::NoMatchingOverloadedFunction, "argument list does not match any of the overloaded functions.");
}

void ErrorPortal::AddArgumentListLengthMismatchError(size_t numExpected, size_t numGiven)
{
	AddError(ErrorCode::ArgumentListLengthMismatch, "function expects " + std::to_string(numExpected) + " parameter(s), " + std::to_string(numGiven) + " provided.");
}

void ErrorPortal::AddConstantOutOfRangeError()
{
	AddError(ErrorCode::ConstantOutOfRange, "constant is out of range.");
}

void ErrorPortal::AddIdentifierScopeUnaccessibleError(const std::string &identifierName, const std::string &identifierScope, const std::string& currentScope)
{
	AddError(ErrorCode::IdentifierScopeUnaccessible, "\"" + identifierName + "\" in scope \"" + identifierScope + "\" is not accessible from scope \"" + currentScope +"\".");
}

//void ErrorPortal::AddAccessFunctionOfHigherContextClassError(const std::string &identifierName)
//{
//	AddError(ErrorCode::AccessFunctionOfHigherContextClass, "function \"" + identifierName + "\" has a higher context class than the current function and is not accessible.");
//}

void ErrorPortal::AddSpaceInNegativeNumberLiteralError()
{
	AddError(ErrorCode::SpaceInNegativeNumberLiteral, "number literal should not have space between '-' and the digits.");
}

void ErrorPortal::AddNoMatchingConstructorError(const std::string &typeName)
{
	AddError(ErrorCode::NoMatchingConstructor, "no matching constructor of \"" + typeName + "\" found.");
}

void ErrorPortal::AddNotAMemberOfError(const std::string &identifierName, const std::string &typeName)
{
	AddError(ErrorCode::NotAMemberOf, "\"" + identifierName + "\" is not a member of \"" + typeName + "\".");
}

void ErrorPortal::AddVoidOperandError(const std::string &operatorStr, const std::string &operandStr)
{
	AddError(ErrorCode::VoidOperand, "operator \"" + operatorStr + "\" not expecting operand \"" + operandStr + "\" of type \"void\".");
}

void ErrorPortal::AddUnsupportedOperatorError(ConcreteTypePtr type, const std::string &operatorStr)
{
	AddError(ErrorCode::UnsupportedOperator, "type \"" + TypeToTypeName(type) + "\" does not support operator \"" + operatorStr + "\".");
}

void ErrorPortal::AddAssignToNonLValueError()
{
	AddError(ErrorCode::AssignToNonLValue, "cannot assign to a non-lvalue.");
}

void ErrorPortal::AddAssignToConstError()
{
	AddError(ErrorCode::AssignToConst, "cannot assign to a const value.");
}

void ErrorPortal::AddUnsupportedIndexTypeError(ConcreteTypePtr hostType, ConcreteTypePtr indexType)
{
	AddError(ErrorCode::UnsupportedIndexType, "type \"" + TypeToTypeName(hostType) + "\" doesn't support box operator with index type of \"" + TypeToTypeName(indexType) + "\".");
	// TODO: add supported index types in error message
}

void ErrorPortal::AddCallNonConstFromConstContextError(const std::string &calleeName)
{
	AddError(ErrorCode::CallNonConstFromConstContext, "calling non-const function \"" + calleeName + "\" from a const context.");
}

void ErrorPortal::AddNotValidTypeError(const std::string &typeName)
{
	AddError(ErrorCode::NotValidType, "\"" + typeName + "\" is not a valid type.");
}

void ErrorPortal::AddReservedFunctionMustBeShardError(const std::string &functionName)
{
	AddError(ErrorCode::ReservedFunctionMustBeShard, "reserved function " + functionName + " must have shard context class.");
}

void ErrorPortal::AddReservedFunctionMayNotBeShardError(const std::string &functionName)
{
	AddError(ErrorCode::ReservedFunctionMayNotBeShard, "reserved function " + functionName + " must have address context class.");
}

void ErrorPortal::AddReservedFunctionMustBeConstError(const std::string &functionName)
{
	AddError(ErrorCode::ReservedFunctionMustBeConst, "reserved function " + functionName + " must be const.");
}

void ErrorPortal::AddReservedFunctionMayNotHaveReturnValueError(const std::string &functionName)
{
	AddError(ErrorCode::ReservedFunctionMayNotHaveReturnValue, "reserved function " + functionName + " cannot have return value.");
}

void ErrorPortal::AddReservedFunctionMayNotHaveParametersError(const std::string &functionName)
{
	AddError(ErrorCode::ReservedFunctionMayNotHaveParameters, "reserved function " + functionName + " cannot have parameters.");
}

void ErrorPortal::AddReservedFunctionMustHaveSingleBooleanParameterError(const std::string &functionName)
{
	AddError(ErrorCode::ReservedFunctionMustHaveSingleBooleanParameter, "reserved function " + functionName + " must have a single boolean parameter.");
}

void ErrorPortal::AddReservedFunctionCannotBePublicOrExportError(const std::string &functionName)
{
	AddError(ErrorCode::ReservedFunctionCannotBePublicOrExport, "reserved function " + functionName + " cannot have parameters.");
}

void ErrorPortal::AddReservedFunctionHasTooHighBlockDependencyError(const std::string &functionName)
{
	AddError(ErrorCode::ReservedFunctionHasTooHighBlockDependency, "reserved function " + functionName + " cannot have block dependency higher than position. Check direct and indirect calls to related _block functions.");
}

void ErrorPortal::AddReservedFunctionHasTransactionDependencyError(const std::string &functionName)
{
	AddError(ErrorCode::ReservedFunctionHasTransactionDependency, "reserved function " + functionName + " cannot have transaction dependency. Check direct and indirect calls to related _transaction functions.");
}

//void ErrorPortal::AddTokenTypeUnavailableError(const std::string &tokenTypeName)
//{
//	AddError(ErrorCode::AssetNameUnavailable, "token type \"" + tokenTypeName + "\" not available for use. Try a different name.");
//}

void ErrorPortal::AddRelayToFunctionWithConstMoveOnlyParamError()
{
	AddError(ErrorCode::RelayToFunctionWithConstMoveOnlyParam, "relaying to a function with const move only parameter is not allowed. This would cause it to be lost.");
}

void ErrorPortal::AddContractNameAlreadyUsedError(const std::string &contractFullName)
{
	AddError(ErrorCode::ContractNameAlreadyUsed, "contract name \"" + contractFullName + "\" already used.");
}

void ErrorPortal::AddInvalidAddressLiteralError(const std::string &literalName)
{
	AddError(ErrorCode::InvalidAddressLiteral, "invalid address literal \"" + literalName + "\".");
}

void ErrorPortal::AddInvalidHashLiteralError(const std::string &literalName)
{
	AddError(ErrorCode::InvalidHashLiteral, "invalid hash literal \"" + literalName + "\".");
}

void ErrorPortal::AddFunctionCallMissingArgumentListError()
{
	AddError(ErrorCode::FunctionCallMissingArgumentList, "function call missing argument list.");
}

//void ErrorPortal::AddContractVariableDeclarationWithoutInitializerError()
//{
//	AddError(ErrorCode::ContractVariableDeclarationWithoutInitializer, "variable declaration of contract type must have an initializer.");
//}

void ErrorPortal::AddIllegalReferenceToNonStaticMemberError(const std::string &referenceText)
{
	AddError(ErrorCode::IllegalReferenceToNonStaticMember, "illegal reference to non-static member \"" + referenceText + "\".");
}

void ErrorPortal::AddCallSystemReservedFunctionError()
{
	AddError(ErrorCode::CallSystemReservedFunction, "cannot call system-reserved function.");
}

//void ErrorPortal::AddReservedFunctionHasRelayError(const std::string &functionName)
//{
//	AddError(ErrorCode::ReservedFunctionHasRelay, "reserved function " + functionName + " cannot issue relay call directly or indirectly, use issue instead.");
//}

void ErrorPortal::AddRelayShardsToFunctionWithMoveOnlyParamError()
{
	AddError(ErrorCode::RelayShardsToFunctionWithMoveOnlyParam, "relay@shards to a function with move only parameter is not allowed. This would cause it to be duplicated.");
}

void ErrorPortal::AddRelayShardsOutsideGlobalError()
{
	AddError(ErrorCode::RelayShardsOutsideGlobal, "relay@shards is only allowed inside a global function.");
}

void ErrorPortal::AddRelayGlobalFromGlobalError()
{
	AddError(ErrorCode::RelayGlobalFromGlobal, "relay@global is not allowed inside a global function, call that function directly instead.");
}

void ErrorPortal::AddRelayGlobalToNonGlobalFunctionError(const std::string& identifierName)
{
	AddError(ErrorCode::RelayGlobalToNonGlobalFunction, "relay@global to non-global function \"" + identifierName + "\".");
}

void ErrorPortal::AddRelayTargetAndFunctionScopeMismatchError(const std::string& targetType, const std::string& functionName, const std::string& functionScope)
{
	AddError(ErrorCode::RelayTargetAndFunctionScopeMismatch, "relay target type \"" + targetType + "\" does not match scope of function \"" + functionName + "\" (\"" + functionScope + "\").");
}

//void ErrorPortal::AddOnDeployCannotBeAddressFunctionError()
//{
//	AddError(ErrorCode::OnDeployCannotBeAddressFunction, "on_deploy() must be either a global or a per-shard function.");
//}

void ErrorPortal::AddBlobInGlobalStateVariableError()
{
	AddError(ErrorCode::BlobInGlobalStateVariable, "blob types cannot be used in global state variables.");
}

void ErrorPortal::AddInaccessibleGlobalFunctionFromNonGlobalFunctionError(const std::string& identifierName)
{
	AddError(ErrorCode::InaccessibleGlobalFunctionFromNonGlobalFunction, "global function \"" + identifierName + "\" is not const or has relay@shards, hence not accessible from non-global functions.");
}

void ErrorPortal::AddReservedFunctionMustBeGlobalError(const std::string& functionName)
{
	AddError(ErrorCode::ReservedFunctionMustBeGlobal, "reserved function " + functionName + " must have global context class.");
}

void ErrorPortal::AddFunctionConstnessOrContextClassNotMatchInterfaceError(const std::string &interfaceName)
{
	AddError(ErrorCode::FunctionConstnessOrContextClassNotMatchInterface, "function const-ness or context class not matching interface " + interfaceName + ".");
}

void ErrorPortal::AddInterfaceFunctionImplementedButNotPublicError(const std::string& interfaceName)
{
	AddError(ErrorCode::InterfaceFunctionImplementedButNotPublic, "function implementing interface (\"" + interfaceName + "\") must be made public.");
}

void ErrorPortal::AddInterfaceFunctionNotImplementedError(const std::string& interfaceName, const std::string missingFunction)
{
	AddError(ErrorCode::InterfaceFunctionNotImplemented, "interface \"" + interfaceName + "\" not implemented, missing implementation for \"" + missingFunction + "\".");
}

void ErrorPortal::AddInvalidScopeError(const std::string& scopeName)
{
	AddError(ErrorCode::InvalidScope, "invalid scope name \"" + scopeName + "\".");
}

void ErrorPortal::AssigningMemberVarToConstVarError(const std::string& identifierName)
{
	AddError(ErrorCode::AssigningMemberVarToConstVar, "variable \"" + identifierName + "\" cannot be assigned to const member variable");
}

void ErrorPortal::AddInvalidRelayTargetTypeError(const std::string& targetType)
{
	AddError(ErrorCode::InvalidScope, "invalid relay target type \"" + targetType + "\".");
}

void ErrorPortal::AddInvalidConstMemberVarTypeError()
{
	AddError(ErrorCode::InvalidConstMemberVarType, "Invalid constant member variable type. Only string, enum, and value types are supported.");
}

void ErrorPortal::AddNonDeployableTypeError(const std::string& expressionText)
{
	AddError(ErrorCode::NonDeployableType, "\"" + expressionText + "\" is not a deployable type.");
}

void ErrorPortal::AddMultipleConstructorError()
{
	AddError(ErrorCode::MultipleConstructor, "More than one constructor defined.");
}

void ErrorPortal::AddDeployInNonGlobalError()
{
	AddError(ErrorCode::DeployInNonGlobal, "deploy expression can only be used in non-const global functions.");
}

void ErrorPortal::AddUseCurrentContractTypeError()
{
	AddError(ErrorCode::UseCurrentContractType, "using current contract type is not supported.");
}

void ErrorPortal::AddRelayNextFromShardError()
{
	AddError(ErrorCode::RelayNextFromShard, "relay@next is not allowed inside a shard function.");
}

void ErrorPortal::AddMemberOnlyAccessibleViaTypeName(const std::string& identifierName, const std::string& typeName)
{
	AddError(ErrorCode::MemberOnlyAccessibleViaTypeName, "\"" + identifierName + "\" cannot be accessed via an instance, use \"" + typeName + "." + identifierName + "\" instead.");
}


void ErrorPortal::AddSyntaxError(uint32_t line, uint32_t pos, const std::string &msg)
{
	m_errors.emplace_back(line, pos, ErrorCode::SyntaxError, "syntax error: " + msg);
}
void ErrorPortal::AddInternalError(uint32_t line, uint32_t pos, const std::string &msg)
{
	m_errors.emplace_back(line, pos, ErrorCode::InternalError, msg);
}
void ErrorPortal::AddInternalError(const std::string &msg)
{
	m_errors.emplace_back(m_anchorLine, m_anchorPos, ErrorCode::InternalError, msg);
}
void ErrorPortal::AddInternalError(antlr4::Token *token, const std::string &msg)
{
	AddInternalError((uint32_t)token->getLine(), (uint32_t)token->getCharPositionInLine(), msg);
}
void ErrorPortal::AddCompileWarning(uint32_t line, uint32_t pos, const std::string &msg)
{
	m_warnings.emplace_back(line, pos, ErrorCode::InternalError, msg);
}

void ErrorPortal::AddScatteredMapDefinedinStructError()
{
	AddError(ErrorCode::ScatteredTypeDefinedInStruct, "scattered types are not allowed to be defined in struct");
}

void ErrorPortal::AddScatteredTypesScopeError()
{
	AddError(ErrorCode::ScatteredTypeCanOnlybeGlobalOrShard, "scattered types must be in global or shard scope.");
}

void ErrorPortal::AddScatteredTypesAsRelayParamsError()
{
	AddError(ErrorCode::ScatteredTypeUsedInRelay, "scattered types cannot be used in relay parameters.");
}

void ErrorPortal::AddExceedScatteredTypesNumberLimitError()
{
	AddError(ErrorCode::ScatteredTypeNumOutOfLimit, "scattered types with the same key size can be defined 16 times at most. (\"scattered_array<*>\" and \"scattered_map<uint32,*>\" are calculated together)");
}
