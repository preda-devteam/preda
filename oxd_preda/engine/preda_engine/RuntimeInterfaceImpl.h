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
		PredaContractDID deployId;
		rvm::ContractId contractId;
		uint32_t funtionFlags;
	};
	std::vector<ContractStackEntry> m_contractStack;
	std::unordered_map<prlrt::CBigInt*, std::unique_ptr<prlrt::CBigInt>> m_bigint;

	std::map<PredaContractDID, std::array<bool, uint8_t(prlrt::ContractContextType::Num)>> m_contractStateModifiedFlags;
	rvm::ExecutionContext *m_pExecutionContext = nullptr;
	CExecutionEngine *m_pExecutionEngine = nullptr;
	CContractDatabase *m_pDB = nullptr;
	rvm::ChainState* m_pChainState = nullptr;
	bool m_bReportOrphanToken = true;

	uint32_t m_remainingGas = 0;

	std::string m_logOutputBuffer;
	std::stack<prlrt::ExceptionType> exec_stack;
	prlrt::ExceptionType* curr_exc = nullptr;

public:
	void PushContractStack(PredaContractDID deployId, rvm::ContractId contractId, uint32_t functionFlags);
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
	PredaContractDID GetContractStackItemDeployId(uint32_t idx)
	{
		return m_contractStack[idx].deployId;
	}
	bool* GetStateModifiedFlags(PredaContractDID deployId)
	{
		auto itor = m_contractStateModifiedFlags.find(deployId);
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

	void SetChainState(rvm::ChainState* pChainState)
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
