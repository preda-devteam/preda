#pragma once
#include <cstdint>
#include <vector>
#include "transpiler/PredaCommon.h"

namespace transpiler {

	// no-longer used codes are only commented out but not removed to avoid code value ambiguity
	enum class ErrorCode : uint32_t {
		NoError = 0,
		IdentifierRedefinition = 1,
		IdentifierTwoUnderscore = 2,
		TooManyEnumerators = 3,
		ContractDoubleImport = 4,
		ContractImportFailure = 5,
		ContractAliasAlreadyUsed = 6,
		IllegalUseOfTypeAsExpression = 7,
		IllegalUseOfSystemReservedType = 8,
		TypeMismatch = 9,
		AssignConstReferenceTypeToNonConst = 10,
		AutoDeclarationWithoutInitializer = 11,
		ReturnValueFromFunctionWithoutReturnType = 12,
		ReturnWithoutValueFromFunctionWithReturnType = 13,
		BooleanExpressionExpected = 14,
		//RelayFromNoneAddressFunction = 15,
		RelayTargetAddressNotAddressType = 16,
		IdentifierNotDefined = 17,
		RelayToNoneFunction = 18,
		RelayShardsToNonShardFunction = 19,
		RelayToNoneRelayFunction = 20,
		MoveOnlyParamOfTxnFunctionOrConstructor = 21,
		ContinueOutsideLoop = 22,
		BreakOutsideLoop = 23,
		IllegalUseOfContractType = 24,
		IncorrectTxnAndRelayFuncReturnType = 25,
		FunctionRedefinition = 26,
		ExportFunctionNameConflict = 27,
		RelayFunctionCannotBeTransactionOrPublic = 28,
		EmptyStruct = 29,
		ContractNameMistach = 30,
		NoReturnFromFunctionWithReturnType = 31,
		MinedDependencyWithRelay = 32,
		NoMatchingOverloadedFunction = 33,
		ArgumentListLengthMismatch = 34,
		ConstantOutOfRange = 35,
		IdentifierScopeUnaccessible = 36,
		AccessFunctionOfHigherContextClass = 37,
		SpaceInNegativeNumberLiteral = 38,
		NoMatchingConstructor = 39,
		NotAMemberOf = 40,
		VoidOperand = 41,
		UnsupportedOperator = 42,
		AssignToNonLValue = 43,
		AssignToConst = 44,
		UnsupportedIndexType = 45,
		CallNonConstFromConstContext = 46,
		NotValidType = 47,
		ReservedFunctionMustBeShard = 48,
		ReservedFunctionMayNotBeShard = 49,
		ReservedFunctionMustBeConst = 50,
		ReservedFunctionMayNotHaveReturnValue = 51,
		ReservedFunctionMayNotHaveParameters = 52,
		ReservedFunctionHasTooHighBlockDependency = 53,
		ReservedFunctionHasTransactionDependency = 54,
		//AssetNameUnavailable = 55,
		RelayToFunctionWithConstMoveOnlyParam = 56,
		ContractNameAlreadyUsed = 57,
		ReservedFunctionCannotBePublicOrExport = 58,
		ReservedFunctionMustHaveSingleBooleanParameter = 59,
		InvalidAddressLiteral = 60,
		InvalidHashLiteral = 61,
		FunctionCallMissingArgumentList = 62,
		ContractVariableDeclarationWithoutInitializer = 63,
		IllegalReferenceToNonStaticMember = 64,
		//IssueCannotBroadcast = 65,
		//RelayCannotToMiner = 66,
		//IssueOutsideSystemFunction = 67,
		CallSystemReservedFunction = 68,
		//ReservedFunctionHasRelay = 69,
		RelayShardsToFunctionWithMoveOnlyParam = 70,
		RelayShardsOutsideGlobal = 71,
		RelayGlobalFromGlobal = 72,
		RelayGlobalToNonGlobalFunction = 73,
		RelayTargetAndFunctionScopeMismatch = 74,
		BlobInGlobalStateVariable = 75,
		InaccessibleGlobalFunctionFromNonGlobalFunction = 76,
		ReservedFunctionMustBeGlobal = 77,
		FunctionConstnessOrContextClassNotMatchInterface = 78,
		InterfaceFunctionImplementedButNotPublic = 79,
		InterfaceFunctionNotImplemented = 80,
		InvalidScope = 81,
		OnDeployCannotBeAddressFunction = 82,
		AssigningMemberVarToConstVar = 83,
		InvalidConstMemberVarType = 84,
		NonDeployableType = 85,
		MultipleConstructor = 86,
		DeployInNonGlobal = 87,
		UseCurrentContractType = 88,
		RelayNextFromShard = 89,
		MemberOnlyAccessibleViaTypeName = 90,
		ScatteredTypeDefinedInStruct = 91,
		ScatteredTypeCanOnlybeGlobalOrShard = 92,
		ScatteredTypeUsedInRelay = 93,
		ScatteredTypeNumOutOfLimit = 94,

		SyntaxError = 1024,
		InternalError = 0xffff,
	};

	struct IContractSymbols {
		virtual const char* GetDAppName() const = 0;
		virtual const char* GetContractName() const = 0;
		virtual const char* GetContractComment() const = 0;
		virtual const char* GetContractExportUniqueIdentifierString() const = 0;
		virtual uint32_t GetNumImportedContracts() const = 0;
		virtual const char* GetImportedContractFullName(uint32_t contractIdx) const = 0;

		// functions
		virtual uint32_t GetNumExportedFunctions() const = 0;
		virtual const char* GetExportedFunctionName(uint32_t functionIdx) const = 0;
		virtual const char* GetExportedFunctionComment(uint32_t functionIdx) const = 0;
		virtual uint32_t GetExportedFunctionFlag(uint32_t functionIdx) const = 0;
		virtual const char* GetExportedFunctionReturnType(uint32_t functionIdx) const = 0;
		virtual const char* GetExportedFunctionParameterType(uint32_t functionIdx, uint32_t paramIdx) const = 0;
		virtual const char* GetExportedFunctionParameterName(uint32_t functionIdx, uint32_t paramIdx) const = 0;
		virtual uint32_t GetExportedFunctionNumParameters(uint32_t functionIdx) const = 0;

		// reserved functions
		virtual int32_t GetGlobalDeployFunctionExportIndex() const = 0;
		virtual int32_t GetShardScaleoutFunctionExportIndex() const = 0;

		// interfaces
		virtual uint32_t GetNumExportedInterfaces() const = 0;
		virtual const char* GetExportedInterfaceName(uint32_t interfaceIdx) const = 0;
		virtual uint32_t GetNumExportedInterfaceFunctions(uint32_t interfaceIdx) const = 0;
		virtual const char* GetExportedInterfaceFunctionName(uint32_t interfaceIdx, uint32_t functionIdx) const = 0;
		virtual const char* GetExportedInterfaceFunctionComment(uint32_t interfaceIdx, uint32_t functionIdx) const = 0;
		virtual uint32_t GetExportedInterfaceFunctionFlag(uint32_t interfaceIdx, uint32_t functionIdx) const = 0;
		virtual const char* GetExportedInterfaceFunctionReturnType(uint32_t interfaceIdx, uint32_t functionIdx) const = 0;
		virtual const char* GetExportedInterfaceFunctionParameterType(uint32_t interfaceIdx, uint32_t functionIdx, uint32_t paramIdx) const = 0;
		virtual const char* GetExportedInterfaceFunctionParameterName(uint32_t interfaceIdx, uint32_t functionIdx, uint32_t paramIdx) const = 0;
		virtual uint32_t GetExportedInterfaceFunctionNumParameters(uint32_t interfaceIdx, uint32_t functionIdx) const = 0;

		// implemented interfaces
		virtual uint32_t GetNumImplementedInterfaces() const = 0;
		virtual const char* GetImplementedInterfaceName(uint32_t interfaceIdx) const = 0;
		virtual uint32_t GetNumImplementedInterfaceFunctions(uint32_t interfaceIdx) const = 0;
		virtual int32_t GetImplementedInterfaceFunctionExportIndex(uint32_t interfaceIdx, uint32_t functionIdx) const = 0;

		virtual const char* GetScopeStateVariableSignature(transpiler::ScopeType scope) const = 0;
		virtual uint32_t GetNumScopeStateVariable(transpiler::ScopeType scope) const = 0;
		virtual const char* GetScopeStateVariableComment(transpiler::ScopeType scope, uint32_t varIdx) const = 0;
		virtual bool ScopeStateVariableHasAsset(transpiler::ScopeType scope) const = 0;
		virtual bool ScopeStateVariableHasBlob(transpiler::ScopeType scope) const = 0;

		virtual uint32_t GetNumScatteredStateVariable() const = 0;
		virtual const char* GetScatteredStateVariableTypeSignature(uint32_t scatteredStateIdx) const = 0;
		virtual const char* GetScatteredStateVariableName(uint32_t scatteredStateIdx) const = 0;
		virtual uint16_t GetScatteredStateVariableScopeKeySize(uint32_t scatteredStateIdx) const = 0;
		virtual uint8_t GetScatteredStateVariableSlotId(uint32_t scatteredStateIdx) const = 0;

		virtual uint32_t GetNumEnumTypes() const = 0;
		virtual const char* GetEnumDoxygenComment(uint32_t enumTypeIdx) const = 0;
		virtual const char* GetEnumTypeName(uint32_t enumTypeIdx) const = 0;
		virtual uint32_t GetNumEnumerators(uint32_t enumTypeIdx) const = 0;
		virtual const char* GetEnumerator(uint32_t enumTypeIdx, uint32_t enumeratorIdx) const = 0;

		virtual uint32_t GetNumStructTypes() const = 0;
		virtual const char* GetStructTypeName(uint32_t structTypeIdx) const = 0;
		virtual const char* GetStructDoxygenComment(uint32_t structTypeIdx) const = 0;
		virtual uint32_t GetNumStructMembers(uint32_t structTypeIdx) const = 0;
		virtual const char* GetStructMemberType(uint32_t structTypeIdx, uint32_t memberIdx) const = 0;
		virtual const char* GetStructMemberName(uint32_t structTypeIdx, uint32_t memberIdx) const = 0;
	};

	struct IContractSymbolDatabase {
		virtual IContractSymbols* GetContractSymbols(const char *contractFullName) const = 0;
		virtual bool ContractExists(const char *dAppName, const char *contractName) const = 0;
	};

	struct ITranspiler : public IContractSymbols{
		virtual const char* GetVersion() = 0;
		virtual void Release() = 0;
		virtual bool BuildParseTree(const char *sourceCode) = 0;
		virtual bool PreCompile(const char *dAppName) = 0;											// can only be called after BuildParseTree()
		virtual uint32_t GetNumDirectDependentContracts() const = 0;								// can only be called after PreCompile()
		virtual const char* GetDirectDependentContractName(uint32_t contractIdx) const = 0;			// can only be called after PreCompile()
		virtual bool Compile(const char *dAppName, IContractSymbolDatabase *pContractSymbolDatabase) = 0;		// can only be called after BuildParseTree()

		virtual uint32_t GetNumCompileErrors() const = 0;
		virtual const char* GetCompileErrorMsg(uint32_t errorIdx) const = 0;
		virtual void GetCompileErrorPos(uint32_t errorIdx, uint32_t &line, uint32_t &pos) const = 0;
		virtual ErrorCode GetCompileErrorCode(uint32_t errorIdx) const = 0;
		virtual uint32_t GetNumCompileWarnings() const = 0;
		virtual const char* GetCompileWarningMsg(uint32_t warningIdx) const = 0;
		virtual void GetCompileWarningPos(uint32_t warningIdx, uint32_t &line, uint32_t &pos) const = 0;

		virtual const char* GetOutput() const = 0;
	};

	struct ICrystalityTranspiler
	{
		virtual void Release() = 0;
		virtual bool BuildParseTree(const char *sourceCode) = 0;
		virtual bool Transpile() = 0;
		virtual const char* GetOutput() const = 0;

		virtual uint32_t GetNumStorageVariables() const = 0;
		virtual const char* GetStorageVariableType(uint32_t idx) const = 0;
		virtual const char* GetStorageVariableName(uint32_t idx) const = 0;
		virtual const char* GetStorageVariableScope(uint32_t idx) const = 0;

		virtual uint32_t GetNumTranspileErrors() const = 0;
		virtual const char* GetTranspileErrorMsg(uint32_t errorIdx) const = 0;
		virtual void GetTranspileErrorPos(uint32_t errorIdx, uint32_t &line, uint32_t &pos) const = 0;
	};

}
