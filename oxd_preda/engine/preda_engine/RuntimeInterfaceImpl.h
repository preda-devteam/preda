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
#include "bigint.h"

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

	struct OrphanTokens : public rvm::NativeTokens
	{
		virtual uint32_t				GetCount() const override;
		virtual rvm::ConstNativeToken	Get(uint32_t idx) const override;
		virtual void					Release() override;

		std::vector<std::pair<uint64_t, rvm::BigNumMutable>> tokens;
	};

	std::map<uint64_t, rvm::BigNumMutable> m_orphanTokens;
	std::map<uint64_t, rvm::BigNumMutable> m_depositTokens;
	std::map<uint64_t, rvm::BigNumMutable> m_tokensSupplyChange;

	std::map<rvm::ContractVersionId, std::array<bool, uint8_t(prlrt::ContractContextType::Num)>> m_contractStateModifiedFlags;
	rvm::ExecutionContext *m_pExecutionContext = nullptr;
	CExecutionEngine *m_pExecutionEngine = nullptr;
	CContractDatabase *m_pDB = nullptr;
	rvm::ChainStates* m_pChainState = nullptr;
	bool m_bReportOrphanToken = true;

	uint64_t m_remainingGas = 0;
	constexpr static uint64_t relay_base_gas = 2000;

	std::string m_logOutputBuffer;
	std::stack<prlrt::ExceptionType> exec_stack;
	prlrt::ExceptionType* curr_exc = nullptr;

private:
	const ContractImplementedInterface* GetImplementedInterfaceFromContract(uint64_t cvId, int64_t interfaceContractImportSlot, uint32_t interfaceSlot);
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
	rvm::ContractVersionId GetContractTopCvid()
	{
		return m_contractStack.back().cvId;
	}
	bool* GetStateModifiedFlags(rvm::ContractVersionId cvId)
	{
		auto itor = m_contractStateModifiedFlags.find(cvId);
		if (itor == m_contractStateModifiedFlags.end())
			return nullptr;
		return &itor->second[0];
	}
	const std::map<uint64_t, rvm::BigNumMutable>& GetDepositTokens()
	{
		return m_depositTokens;
	}
	const std::map<uint64_t, rvm::BigNumMutable>& GetTokensSupplyChange()
	{
		return m_tokensSupplyChange;
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
	void ClearOrphanTokens()
	{
		m_orphanTokens.clear();
	}
	rvm::NativeTokens* GetOrphanTokens();		// caller should release the returned value
	void ClearDepositTokens()
	{
		m_depositTokens.clear();
	}
	void ClearTokensSupplyChange()
	{
		m_tokensSupplyChange.clear();
	}
	void TurnOhphanTokenReportOnOff(bool bOn)
	{
		m_bReportOrphanToken = bOn;
	}

	void SetGas(uint32_t totalGas)
	{
		m_remainingGas = totalGas;
	}

	uint64_t GetRemainingGas()
	{
		return m_remainingGas;
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
	STRINGIFY_ENUM(DeployFailed)
STRINGIFY_ENUM_END(ExceptionType, prlrt)

namespace prlrt
{

constexpr uint16_t undefined = 0;

using GasCostTable = std::array<uint16_t, PRDOP_NUM>;

inline GasCostTable gasCostTbl = []() constexpr noexcept {
	GasCostTable table{};

	for(auto& t : table)
		t = undefined;
	
	/* bool
	operation						gas
	=								1
	!								2
	== != 							3
	*/
	table[PRDOP_BOOL_ASSIGN] = 1;
	table[PRDOP_BOOL_NOT] = 2;
	table[PRDOP_BOOL_COMP] = 3;

	/* enum
	operation						gas
	=								1
	== != 							3
	*/
	table[PRDOP_ENUM_ASSIGN] = 1;
	table[PRDOP_ENUM_COMP] = 3;

	/* int
	operation						gas (*[size / 64])
	=								1
	++ — ~ - 						2
	+ - == != <= >= < > 			3
	* / %							5
	+= -= 							4
	*= /= %=						6
	*/

	/* uint
	operation							gas (*[size / 64])
	=									1
	++ — ~  							2
	+ - == != <= >= < > & ^ | << >>		3
	* / %								5
	+= -= &= |= ^= <<= >>=				4
	*= /= %=							6
	*/
	table[PRDOP_INT_ASSIGN] = 1;
	table[PRDOP_INT_OP_SELF] = 2;
	table[PRDOP_INT_OP_SIMPLE] = 3;
	table[PRDOP_INT_OP_COMPLEX] = 5;

	/* float 
	operation						gas (*[size / 256])
	=								4
	-								12
	+ - == != >= < = < >			20
	* / 							28
	+= -=							24
	*= /=							32
	*/
	table[PRDOP_FLOAT_ASSIGN] = 4;
	table[PRDOP_FLOAT_OP_SELF] = 12;
	table[PRDOP_FLOAT_OP_SIMPLE] = 20;
	table[PRDOP_FLOAT_OP_COMPLEX] = 28;

	/* bigint
	operation						gas (*[size / 64])
	=								2
	++ — -							4
	+ - == != < > <= >=				6
	* / %							10
	+= -= 							8
	*= /= %= 						12
	*/
	table[PRDOP_BIGINT_ASSIGN_STATIC] = 2;
	table[PRDOP_BIGINT_ASSIGN_DYNAMIC] = 1;
	table[PRDOP_BIGINT_OP_SELF] = 4;
	table[PRDOP_BIGINT_OP_SIMPLE] = 6;
	table[PRDOP_BIGINT_OP_COMPLEX] = 10;

	/* address blob hash
	operation						gas
	=								4
	== != < > <= >= 				12
	*/
	table[PRDOP_ABH_ASSIGN] = 4;
	table[PRDOP_ABH_OP_SIMPLE] = 12;

	/* address
	operation						gas
	is_user							12
	is_delegated					12					
	is_dapp							12
	is_asset						12
	is_name							12
	is_contract						12
	is_custom						12
	string to address				12
	to_string						12
	*/
	table[PRDOP_ADDRESS_CHECK] = 12;

	/* hash
	operation						gas
	string to hash					12
	to_string						12
	*/
	table[PRDOP_ABH_TYPE_TRANSFORM] = 12;

	/* string
	operation						gas
	=								2
	== != < > <= >=					3
	set								3 + new size - old size
	append							3 + size
	length							3
	*/
	table[PRDOP_STR_ASSIGN] = 2;
	table[PRDOP_STR_OP_SIMPLE] = 3;

	/* array
	operation						gas
	=								2
	[]								3
	length							3
	set length						3 + new size - old size
	push							3 + elem_size
	pop								3
	*/
	table[PRDOP_ARRAY_ASSIGN] = 2;
	table[PRDOP_ARRAY_OP_SIMPLE] = 3;

	/* map
	operation						gas
	=								2
	length							3
	has								3
	erase							3
	[]								3 
	*/
	table[PRDOP_MAP_ASSIGN] = 2;
	table[PRDOP_MAP_OP_SIMPLE] = 3;

	/* token
	operation						gas
	=								2
	get_id							3
	get_amount						5
	transfer						5
	transferAll						8
	*/
	table[PRDOP_TOKEN_ASSIGN] = 2;
	table[PRDOP_TOKEN_ID] = 3;
	table[PRDOP_TOKEN_AMOUNT] = 3;
	table[PRDOP_TOKEN_TRANSFER] = 5;
	table[PRDOP_TOKEN_TRANSFERALL] = 8;
	table[PRDOP_TOKEN_DEPOSIT] = 5;

	/* data serialization
	operation						gas
	get_serialize_size				2
	serialize_out					3 + [serialize_size / 8]
	map_from_serialiezed_data		5 + [serialize_size / 8]
	*/
	table[PRDOP_SERIALIZE_SIZE] = 2;
	table[PRDOP_SERIALIZE_OUT_STATIC] = 3;
	table[PRDOP_SERIALIZE_MAP_STATIC] = 5;
	table[PRDOP_SERIALIZE_DYNAMIC] = 1;

	/* function call and loop
	operation						gas
	for, while loop					8
	normal function call			8
	cross function call				200
	intrinsic						500
	relay function call				1000
	*/
	table[PRDOP_JUMP] = 8;
	table[PRDOP_CROSS] = 200;
	table[PRDOP_RELAY] = 8000;
	table[PRDOP_GLOBAL_RELAY] = 50000;
	table[PRDOP_DEPLOY] = 30000;

	// get transaction context
	table[PRDOP_TXN_CTX] = 3;

	// get block context
	table[PRDOP_BLK_CTX] = 3;

	// debug 
	table[PRDOP_DEBUG_OP] = 3;

	return table;
}();

}