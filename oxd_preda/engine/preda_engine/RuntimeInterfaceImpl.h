#pragma once
#include <map>
#include <array>
#include <vector>
#include <optional>
#include <stack>

#include "../../native/abi/vm_interfaces.h"
#include "../../bin/compile_env/include/runtime_interface.h"
#include "../../../SFC/core/ext/bignum/ttmath/ttmath.h"
#include "../../../SFC/core/ext/bignum/precision_num.h"

#include "ContractData.h"

using float_lp = ext::_details::PrecisionFloat<256>;
using float_mp = ext::_details::PrecisionFloat<512>;
using float_hp = ext::_details::PrecisionFloat<1024>;
#define TYPEDEFINE(_SIZE, _INT_TYPE, _MATH_TYPE) \
using _INT_TYPE##_##_SIZE = ttmath::_MATH_TYPE<TTMATH_BITS(_SIZE)>;
TYPEDEFINE(128, ULongInt, UInt)
TYPEDEFINE(256, ULongInt, UInt)
TYPEDEFINE(512, ULongInt, UInt)
TYPEDEFINE(128, LongInt, Int)
TYPEDEFINE(256, LongInt, Int)
TYPEDEFINE(512, LongInt, Int)

class CExecutionEngine;
class CContractDatabase;

class CRuntimeInterface : public prlrt::IRuntimeInterface {
private:
	struct ContractStackEntry
	{
		rvm::ContractModuleID moduleId;
		rvm::ContractVersionId cvId;
		const rvm::ContractVersionId *importedCvIds;
		uint32_t numImportedContracts;
		uint32_t funtionFlags;
	};
	std::vector<ContractStackEntry> m_contractStack;
	std::unordered_map<prlrt::CBigInt*, std::unique_ptr<prlrt::CBigInt>> m_bigint;

	std::map<rvm::ContractVersionId, std::array<bool, uint8_t(prlrt::ContractContextType::Num)>> m_contractStateModifiedFlags;
	rvm::ExecutionContext *m_pExecutionContext = nullptr;
	CExecutionEngine *m_pExecutionEngine = nullptr;
	CContractDatabase *m_pDB = nullptr;
	rvm::ChainStates* m_pChainState = nullptr;
	bool m_bReportOrphanToken = true;

	uint32_t m_remainingGas = 0;

	std::string m_logOutputBuffer;
	std::stack<prlrt::ExceptionType> exec_stack;
	prlrt::ExceptionType* curr_exc = nullptr;

public:
	void PushContractStack(const rvm::ContractModuleID &moduleId, rvm::ContractVersionId cvId, uint32_t functionFlags, const rvm::ContractVersionId* importedCvId, uint32_t numImportedContracts);
	void PopContractStack()
	{
		m_contractStack.pop_back();
	}
	void PushExecStack() {
		exec_stack.push(prlrt::ExceptionType::NoException);
	}
	prlrt::ExceptionType PopExecStack() {
		prlrt::ExceptionType top = exec_stack.top();
		exec_stack.pop();
		return top;
	}
	uint32_t GetContractStackSize()
	{
		return uint32_t(m_contractStack.size());
	}
	bool* GetStateModifiedFlags(rvm::ContractVersionId cvId)
	{
		auto itor = m_contractStateModifiedFlags.find(cvId);
		if (itor == m_contractStateModifiedFlags.end())
			return nullptr;
		return &itor->second[0];
	}
	void SetExecutionEngine(CExecutionEngine *pExecutionEngine)
	{
		m_pExecutionEngine = pExecutionEngine;
	}
	void SetExecutionContext(rvm::ExecutionContext *pExecutionContext)
	{
		m_pExecutionContext = pExecutionContext;
	}
	void ClearBigInt();
	void ClearStateModifiedFlags()
	{
		m_contractStateModifiedFlags.clear();
	}
	void ClearContractStack()
	{
		m_contractStack.clear();
	}
	void TurnOhphanTokenReportOnOff(bool bOn)
	{
		m_bReportOrphanToken = bOn;
	}

	void SetGas(uint32_t totalGas)
	{
		m_remainingGas = totalGas;
	}

	void SetChainState(rvm::ChainStates* pChainState)
	{
		m_pChainState = pChainState;
	}

public:
	CRuntimeInterface(CContractDatabase *pDB);
	~CRuntimeInterface();

#define PREDA_INTERFACE_IMPL_METHOD_V(RET, FN, ...) RET FN(__VA_ARGS__) override;
	FOR_EACH_PREDA_INTERFACE_METHOD(PREDA_INTERFACE_IMPL_METHOD_V)
#undef PREDA_INTERFACE_IMPL_METHOD_V
};

STRINGIFY_ENUM_BEGIN(ExceptionType, prlrt)
	STRINGIFY_ENUM(NoException)
	STRINGIFY_ENUM(Overflow)
	STRINGIFY_ENUM(Underflow)
	STRINGIFY_ENUM(DividedByZero)
	STRINGIFY_ENUM(TokenTransfer_NoTokenType)
	STRINGIFY_ENUM(TokenTransfer_TokenTypeMismatch)
	STRINGIFY_ENUM(TokenTransfer_NegativeAmount)
	STRINGIFY_ENUM(TokenTransfer_InsufficientCredit)
	STRINGIFY_ENUM(OutOfRange)
	STRINGIFY_ENUM(PopEmptyArray)
	STRINGIFY_ENUM(MapInsertFailure)
	STRINGIFY_ENUM(ConstMapAccessNonExistingKey)
	STRINGIFY_ENUM(DeserializationFailure)
	STRINGIFY_ENUM(InvalidMapKeyType)
	STRINGIFY_ENUM(EnumValueOverflow)
	STRINGIFY_ENUM(MemoryWriteVialation)
	STRINGIFY_ENUM(CrossCallFunctionNotFound)
	STRINGIFY_ENUM(CrossCallArgumentMismatch)
	STRINGIFY_ENUM(CrossCallContractNotFound)
	STRINGIFY_ENUM(BigIntOverFlow)
	STRINGIFY_ENUM(TokenDoubleSerialization)
	STRINGIFY_ENUM(AssertionFailure)
	STRINGIFY_ENUM(RelayError)
	STRINGIFY_ENUM(InitAddressWithInvalidLiteral)
	STRINGIFY_ENUM(UnknownException)
	STRINGIFY_ENUM(InitHashWithInvalidLiteral)
	STRINGIFY_ENUM(StringLengthOverflow)
	STRINGIFY_ENUM(AccessUnavailableContextFunction)
	STRINGIFY_ENUM(InvalidStringToAddressConversion)
	STRINGIFY_ENUM(NoAssetMintPermission)
	STRINGIFY_ENUM(GasUsedUp)
	STRINGIFY_ENUM(TokenMint_NegativeAmount)
	STRINGIFY_ENUM(InvalidTokenId)
STRINGIFY_ENUM_END(ExceptionType, prlrt)
