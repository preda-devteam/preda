#include <iostream>

#include "bigint.h"

#include "../../transpiler/transpiler/PredaCommon.h"
#include "ExecutionEngine.h"
#include "ContractDatabase.h"
#include "RuntimeInterfaceImpl.h"

CRuntimeInterface::CRuntimeInterface(CContractDatabase *pDB)
	: m_pDB(pDB)
{
}

prlrt::CBigInt* CRuntimeInterface::CreateBigint()
{
	return new CBigint;
}

bool CRuntimeInterface::InitAddressFromLiteral(void *pAddress, const char *str)
{
	return ::oxd::_details::_JsonParse(*(::oxd::EntityAddress *)pAddress, rt::String_Ref(str)).ret;
}

bool CRuntimeInterface::InitHashFromLiteral(void *pHash, const char *str)
{
	rt::String_Ref tmp(str, 52);
	return ::oxd::b32str::Decode(pHash, 32, tmp.Begin(), tmp.GetLength());
}

void CRuntimeInterface::CalculateHash(void *pHash, const uint8_t *data, uint32_t data_len)
{
	((oxd::HashValue*)pHash)->Hash<oxd::Hash>(data, data_len);
}

bool CRuntimeInterface::StringToAddress(void *pAddress, const char *data, uint32_t data_len)
{
	oxd::rvm::ConstString cs{ data, data_len };
	return m_pDB->m_pRuntimeAPI->SecureAddressParse(&cs, (oxd::rvm::Address*)pAddress);
}

void CRuntimeInterface::PushContractStack(oxd::RVM_CONTRACT_ID contractId, uint32_t buildNum, uint32_t functionFlags)
{
	ContractStackEntry entry;
	entry.contractId = contractId;
	entry.buildNum = buildNum;
	entry.funtionFlags = functionFlags;
	m_contractStack.push_back(entry);

	bool bIsConstCall = (functionFlags & uint32_t(transpiler::PredaFunctionFlags::IsConst)) != 0;

	if (!bIsConstCall)
	{
		auto itor = m_contractStateModifiedFlags.try_emplace(contractId, std::array<bool, uint8_t(prlrt::ContractContextType::Num)>{false, false, false, false});
		uint32_t contextClassLevel = uint32_t(functionFlags & uint32_t(transpiler::PredaFunctionFlags::ContextClassMask));
		for (uint32_t i = 0; i <= contextClassLevel; i++)
			itor.first->second[i] = true;
	}
}

bool CRuntimeInterface::EmitRelay(const uint8_t *address, uint32_t opCode, const uint8_t* args_serialized, uint32_t args_size)
{
	oxd::rvm::ConstData args;
	args.DataPtr = args_serialized;
	args.DataSize = args_size;
	return m_pExecutionContext->EmitRelayTxn(m_contractStack.back().buildNum, (oxd::rvm::ConstAddress *)address, RVM_CONTRACT_SET_SECTION(m_contractStack.back().contractId, oxd::CTRSS_ADDRESS), opCode, &args);
}

bool CRuntimeInterface::EmitRelayBroadcast(uint32_t opCode, const uint8_t* args_serialized, uint32_t args_size)
{
	oxd::rvm::ConstData args;
	args.DataPtr = args_serialized;
	args.DataSize = args_size;
	return m_pExecutionContext->BroadcastRelayTxn(m_contractStack.back().buildNum, RVM_CONTRACT_SET_SECTION(m_contractStack.back().contractId, oxd::CTRSS_SHARD), opCode, &args);
}

bool CRuntimeInterface::EmitYield(const uint8_t *address, uint32_t opCode, const uint8_t* args_serialized, uint32_t args_size)
{
	oxd::rvm::ConstData args;
	args.DataPtr = args_serialized;
	args.DataSize = args_size;
	return m_pExecutionContext->EmitYieldTxn(m_contractStack.back().buildNum, (oxd::rvm::ConstAddress *)address, RVM_CONTRACT_SET_SECTION(m_contractStack.back().contractId, oxd::CTRSS_ADDRESS), opCode, &args);
}

bool CRuntimeInterface::EmitYieldMiner(uint32_t opCode, const uint8_t* args_serialized, uint32_t args_size)
{
	oxd::rvm::ConstData args;
	args.DataPtr = args_serialized;
	args.DataSize = args_size;
	return m_pExecutionContext->EmitMinerYieldTxn(m_contractStack.back().buildNum, RVM_CONTRACT_SET_SECTION(m_contractStack.back().contractId, oxd::CTRSS_ADDRESS), opCode, &args);
}

uint32_t CRuntimeInterface::CrossCall(uint64_t contractId, uint32_t opCode, const void **ptrs, uint32_t numPtrs)
{
	const ContractDatabaseEntry *pEntry = m_pDB->FindContractBuild(m_contractStack.back().contractId, m_contractStack.back().buildNum);
	assert(pEntry);
	uint32_t buildNum;
	for (int i = 0; i < pEntry->deployData.importedContractIds.size(); i++)
		if (pEntry->deployData.importedContractIds[i] == contractId)
		{
			buildNum = pEntry->deployData.importedContractBuildNums[i];
			return m_pExecutionEngine->InvokeContractCall(m_pExecutionContext, oxd::RVM_CONTRACT_ID(contractId), buildNum, opCode, ptrs, numPtrs);
		}

	assert(0);
	return 0;
}

void CRuntimeInterface::ReportOrphanToken(uint32_t id, prlrt::CBigInt* amount)
{
	if (!m_bReportOrphanToken)
		return;

	uint64_t v;
	amount->ToUint64(&v);
	std::cout << "orphan token: " << id << " " << v << std::endl;
}

void CRuntimeInterface::ReportReturnValue(const char *type_export_name, const uint8_t *serialized_data, uint32_t serialized_data_size)
{
	std::cout << "return value: ";
	DebugPrintSerializedData(type_export_name, serialized_data, serialized_data_size);
	std::cout << std::endl;
}

void CRuntimeInterface::DebugPrintSerializedData(const char *type_export_name, const uint8_t *serialized_data, uint32_t serialized_data_size)
{
	if (type_export_name == nullptr || serialized_data == nullptr)
		return;

	std::string outputStr;
	bool res = m_pDB->VariableJsonify(m_contractStack.back().contractId, m_contractStack.back().buildNum, type_export_name, serialized_data, serialized_data_size, outputStr);
	assert(res);
	std::cout << outputStr;
}

void CRuntimeInterface::DebugPrintString(const char *str)
{
	std::cout << str;
}

void CRuntimeInterface::DebugAssertionFailure(uint32_t line)
{
	std::cout << "Assertion failure on line " << line << std::endl;
}

bool CRuntimeInterface::HasAssetMintPermission(uint32_t id)
{
	return m_pExecutionContext->HasAssetMintPermission(oxd::rvm::RVM_ASSET_ID(id), RVM_CONTRACT_DAPPID(m_contractStack.back().contractId));
}

bool CRuntimeInterface::IsUserAddress(const void *pAddress)
{
	return !((oxd::rvm::ConstAddress *)pAddress)->IsDelegated();
}

bool CRuntimeInterface::IsDelegatedAddress(const void *pAddress)
{
	return ((oxd::rvm::ConstAddress *)pAddress)->IsDelegated();
}

bool CRuntimeInterface::IsDAppAddress(const void *pAddress)
{
	return ((oxd::rvm::ConstAddress *)pAddress)->GetSecuritySuiteId() == oxd::SEC_SUITE_REGISTERED_DAPP;
}

bool CRuntimeInterface::IsAssetAddress(const void *pAddress)
{
	return ((oxd::rvm::ConstAddress *)pAddress)->GetSecuritySuiteId() == oxd::SEC_SUITE_REGISTERED_ASSET;
}

bool CRuntimeInterface::IsNameAddress(const void *pAddress)
{
	return ((oxd::rvm::ConstAddress *)pAddress)->GetSecuritySuiteId() == oxd::SEC_SUITE_REGISTERED_NAME;
}

bool CRuntimeInterface::IsDomainAddress(const void *pAddress)
{
	return ((oxd::rvm::ConstAddress *)pAddress)->GetSecuritySuiteId() == oxd::SEC_SUITE_REGISTERED_DOMAIN;
}

bool CRuntimeInterface::BurnGasLoop()
{
	constexpr uint32_t loopGas = 1;
	if (m_remainingGas < loopGas)
	{
		m_remainingGas = 0;
		return false;
	}

	m_remainingGas -= loopGas;
	return true;
}

bool CRuntimeInterface::BurnGasFunctionCall()
{
	constexpr uint32_t functionCallGas = 1000;
	if (m_remainingGas < functionCallGas)
	{
		m_remainingGas = 0;
		return false;
	}

	m_remainingGas -= functionCallGas;
	return true;
}
std::string debugFloat(floatTemp_lp& pftemp) {
	float_lp* pfloat = (float_lp*)&pftemp;
	return pfloat->ToString();
}
std::string debugFloat(floatTemp_mp& pftemp) {
	float_mp* pfloat = (float_mp*)&pftemp;
	return pfloat->ToString();
}
std::string debugFloat(floatTemp_hp& pftemp) {
	float_hp* pfloat = (float_hp*)&pftemp;
	return pfloat->ToString();
}
void CRuntimeInterface::ConvertToString_256(const floatTemp_lp& pftemp, char* buf){
	static_assert(sizeof(pftemp) == sizeof(float_lp), "Size of Precision Float inconsistent");
	// std::cout << "Start Convert To String 256" << std::endl;
	float_lp* pfloat = (float_lp*)&pftemp;
	std::string float_literal = pfloat->ToString();
	memcpy(buf, float_literal.data(), float_literal.length());
	// std::cout << "End Convert To String 256" << std::endl;

}
void CRuntimeInterface::ConvertToString_512(const floatTemp_mp& pftemp, char* buf){
	static_assert(sizeof(pftemp) == sizeof(float_mp), "Size of Precision Float inconsistent");
	// std::cout << "Start Convert To String 512" << std::endl;
	float_mp* pfloat = (float_mp*)&pftemp;
	std::string float_literal = pfloat->ToString();
	memcpy(buf, float_literal.data(), float_literal.length());
	// std::cout << "End Convert To String 512" << std::endl;
}
void CRuntimeInterface::ConvertToString_1024(const floatTemp_hp& pftemp, char* buf){
	static_assert(sizeof(pftemp) == sizeof(float_hp), "Size of Precision Float inconsistent");
	// std::cout << "Start Convert To String 1024" << std::endl;
	float_hp* pfloat = (float_hp*)&pftemp;
	std::string float_literal = pfloat->ToString();
	memcpy(buf, float_literal.data(), float_literal.length());
	// std::cout << "End Convert To String 1024" << std::endl;

}
size_t CRuntimeInterface::GetConvertToStringLen_256(const floatTemp_lp& pftemp){
	static_assert(sizeof(pftemp) == sizeof(float_lp), "Size of Precision Float inconsistent");
	// std::cout << "String len 256" << std::endl;
	float_lp* pfloat = (float_lp*)&pftemp;
	return pfloat->ToString().length();
}
size_t CRuntimeInterface::GetConvertToStringLen_512(const floatTemp_mp& pftemp){
	static_assert(sizeof(pftemp) == sizeof(float_mp), "Size of Precision Float inconsistent");

	// std::cout << "String len 512" << std::endl;
	float_mp* pfloat = (float_mp*)&pftemp;
	return pfloat->ToString().length();
}
size_t CRuntimeInterface::GetConvertToStringLen_1024(const floatTemp_hp& pftemp){
	static_assert(sizeof(pftemp) == sizeof(float_hp), "Size of Precision Float inconsistent");
	// std::cout << "String len 1024" << std::endl;
	float_hp* pfloat = (float_hp*)&pftemp;
	return pfloat->ToString().length();
}

void CRuntimeInterface::ConvertFromString_256(floatTemp_lp &pftemp, const char* float_literal){
	static_assert(sizeof(pftemp) == sizeof(float_lp), "Size of Precision Float inconsistent");
	// std::cout << "Start of Convert from string 256" << std::endl;
	float_lp pfloat(float_literal);
	pftemp = *((floatTemp_lp*)&pfloat);
	// std::cout << "End of Convert from string 256" << std::endl;

}

void CRuntimeInterface::ConvertFromString_512(floatTemp_mp& pftemp, const char* float_literal){
	static_assert(sizeof(pftemp) == sizeof(float_mp), "Size of Precision Float inconsistent");
	// std::cout << "Start of Convert from string 512" << std::endl;
	float_mp pfloat(float_literal);
	pftemp = *((floatTemp_mp*)&pfloat);	
	// std::cout << "End of Convert from string 512" << std::endl;

}

void CRuntimeInterface::ConvertFromString_1024(floatTemp_hp& pftemp, const char* float_literal){
	static_assert(sizeof(pftemp) == sizeof(float_hp), "Size of Precision Float inconsistent");
	// std::cout << "Start of Convert from string 1024" << std::endl;
	float_hp pfloat(float_literal);
	pftemp = *((floatTemp_hp*)&pfloat);
}
void CRuntimeInterface::Float_Add_256(const floatTemp_lp& a, const floatTemp_lp& b, floatTemp_lp& result){
	static_assert(sizeof(a) == sizeof(float_lp), "Size of Precision Float inconsistent");
	static_assert(sizeof(b) == sizeof(float_lp), "Size of Precision Float inconsistent");
	// std::cout << "Start of Add 256" << std::endl;
	memcpy(result._Data, a._Data, sizeof(result._Data)/sizeof(uint8_t));
	((float_lp*)&result)->Add(*((float_lp*)&b));
}
void CRuntimeInterface::Float_Add_512(const floatTemp_mp& a, const floatTemp_mp& b, floatTemp_mp& result){
	static_assert(sizeof(a) == sizeof(float_mp), "Size of Precision Float inconsistent");
	static_assert(sizeof(b) == sizeof(float_mp), "Size of Precision Float inconsistent");
	// std::cout << "Start of Add 512" << std::endl;
	memcpy(result._Data, a._Data, sizeof(result._Data)/sizeof(uint8_t));
	((float_mp*)&result)->Add(*((float_mp*)&b));
}
void CRuntimeInterface::Float_Add_1024(const floatTemp_hp& a, const floatTemp_hp& b, floatTemp_hp& result){
	static_assert(sizeof(a) == sizeof(float_hp), "Size of Precision Float inconsistent");
	static_assert(sizeof(b) == sizeof(float_hp), "Size of Precision Float inconsistent");
	// std::cout << "Start of Add 1024" << std::endl;
	memcpy(result._Data, a._Data, sizeof(result._Data)/sizeof(uint8_t));
	((float_hp*)&result)->Add(*((float_hp*)&b));
}
void CRuntimeInterface::Float_Sub_256(const floatTemp_lp& a, const floatTemp_lp& b, floatTemp_lp& result){
	static_assert(sizeof(a) == sizeof(float_lp), "Size of Precision Float inconsistent");
	static_assert(sizeof(b) == sizeof(float_lp), "Size of Precision Float inconsistent");
	// std::cout << "Start of Sub 256" << std::endl;
	memcpy(result._Data, a._Data, sizeof(result._Data)/sizeof(uint8_t));
	((float_lp*)&result)->Sub(*((float_lp*)&b));
}
void CRuntimeInterface::Float_Sub_512(const floatTemp_mp& a, const floatTemp_mp& b, floatTemp_mp& result){
	static_assert(sizeof(a) == sizeof(float_mp), "Size of Precision Float inconsistent");
	static_assert(sizeof(b) == sizeof(float_mp), "Size of Precision Float inconsistent");
	// std::cout << "Start of Sub 512" << std::endl;
	memcpy(result._Data, a._Data, sizeof(result._Data)/sizeof(uint8_t));
	((float_mp*)&result)->Sub(*((float_mp*)&b));
}
void CRuntimeInterface::Float_Sub_1024(const floatTemp_hp& a, const floatTemp_hp& b, floatTemp_hp& result){
	static_assert(sizeof(a) == sizeof(float_hp), "Size of Precision Float inconsistent");
	static_assert(sizeof(b) == sizeof(float_hp), "Size of Precision Float inconsistent");
	// std::cout << "Start of Sub 1024" << std::endl;
	memcpy(result._Data, a._Data, sizeof(result._Data)/sizeof(uint8_t));
	((float_hp*)&result)->Sub(*((float_hp*)&b));
}
void CRuntimeInterface::Float_Mul_256(const floatTemp_lp& a, const floatTemp_lp& b, floatTemp_lp& result){
	static_assert(sizeof(a) == sizeof(float_lp), "Size of Precision Float inconsistent");
	static_assert(sizeof(b) == sizeof(float_lp), "Size of Precision Float inconsistent");
	// std::cout << "Start of Mul 256" << std::endl;
	memcpy(result._Data, a._Data, sizeof(result._Data)/sizeof(uint8_t));
	((float_lp*)&result)->Mul(*((float_lp*)&b));
}
void CRuntimeInterface::Float_Mul_512(const floatTemp_mp& a, const floatTemp_mp& b, floatTemp_mp& result){
	static_assert(sizeof(a) == sizeof(float_mp), "Size of Precision Float inconsistent");
	static_assert(sizeof(b) == sizeof(float_mp), "Size of Precision Float inconsistent");
	// std::cout << "Start of Mul 512" << std::endl;
	memcpy(result._Data, a._Data, sizeof(result._Data)/sizeof(uint8_t));
	((float_mp*)&result)->Mul(*((float_mp*)&b));
}
void CRuntimeInterface::Float_Mul_1024(const floatTemp_hp& a, const floatTemp_hp& b, floatTemp_hp& result){
	static_assert(sizeof(a) == sizeof(float_hp), "Size of Precision Float inconsistent");
	static_assert(sizeof(b) == sizeof(float_hp), "Size of Precision Float inconsistent");
	// std::cout << "Start of Mul 1024" << std::endl;
	memcpy(result._Data, a._Data, sizeof(result._Data)/sizeof(uint8_t));
	((float_hp*)&result)->Mul(*((float_hp*)&b));
}
void CRuntimeInterface::Float_Div_256(const floatTemp_lp& a, const floatTemp_lp& b, floatTemp_lp& result){
	static_assert(sizeof(a) == sizeof(float_lp), "Size of Precision Float inconsistent");
	static_assert(sizeof(b) == sizeof(float_lp), "Size of Precision Float inconsistent");
	// std::cout << "Start of Div 256" << std::endl;
	memcpy(result._Data, a._Data, sizeof(result._Data)/sizeof(uint8_t));
	((float_lp*)&result)->Div(*((float_lp*)&b));
}
void CRuntimeInterface::Float_Div_512(const floatTemp_mp& a, const floatTemp_mp& b, floatTemp_mp& result){
	static_assert(sizeof(a) == sizeof(float_mp), "Size of Precision Float inconsistent");
	static_assert(sizeof(b) == sizeof(float_mp), "Size of Precision Float inconsistent");
	// std::cout << "Start of Div 512" << std::endl;
	memcpy(result._Data, a._Data, sizeof(result._Data)/sizeof(uint8_t));
	((float_mp*)&result)->Div(*((float_mp*)&b));
}
void CRuntimeInterface::Float_Div_1024(const floatTemp_hp& a, const floatTemp_hp& b, floatTemp_hp& result){
	static_assert(sizeof(a) == sizeof(float_hp), "Size of Precision Float inconsistent");
	static_assert(sizeof(b) == sizeof(float_hp), "Size of Precision Float inconsistent");
	// std::cout << "Start of Div 1024" << std::endl;
	memcpy(result._Data, a._Data, sizeof(result._Data)/sizeof(uint8_t));
	((float_hp*)&result)->Div(*((float_hp*)&b));
}
void CRuntimeInterface::Float_Zero_256(floatTemp_lp& a){
	static_assert(sizeof(a) == sizeof(float_lp), "Size of Precision Float inconsistent");
	// std::cout << "Start of Zero 256" << std::endl;
	float_lp pfloat(0);
	a = *((floatTemp_lp*)&pfloat);
}
void CRuntimeInterface::Float_Zero_512(floatTemp_mp& a){
	static_assert(sizeof(a) == sizeof(float_mp), "Size of Precision Float inconsistent");
	// std::cout << "Start of Zero 512" << std::endl;
	float_mp pfloat(0);
	a = *((floatTemp_mp*)&pfloat);
}
void CRuntimeInterface::Float_Zero_1024(floatTemp_hp& a){
	static_assert(sizeof(a) == sizeof(float_hp), "Size of Precision Float inconsistent");
	// std::cout << "Start of Zero 1024" << std::endl;
	float_hp pfloat(0);
	a = *((floatTemp_hp*)&pfloat);
}

bool CRuntimeInterface::Float_IsZero_256(const floatTemp_lp& a){
	static_assert(sizeof(a) == sizeof(float_lp), "Size of Precision Float inconsistent");
	// std::cout << "Start of IsZero 256" << std::endl;
	float_lp* pfloat_a = (float_lp*)&a;
	double result;
	pfloat_a->ToNumber(result);
	return result == 0.0;
}
bool CRuntimeInterface::Float_IsZero_512(const floatTemp_mp& a){
	static_assert(sizeof(a) == sizeof(float_mp), "Size of Precision Float inconsistent");
	// std::cout << "Start of IsZero 512" << std::endl;
	float_mp* pfloat_a = (float_mp*)&a;
	double result;
	pfloat_a->ToNumber(result);
	return result == 0.0;
}
bool CRuntimeInterface::Float_IsZero_1024(const floatTemp_hp& a){
	static_assert(sizeof(a) == sizeof(float_hp), "Size of Precision Float inconsistent");
	// std::cout << "Start of IsZero 1024" << std::endl;
	float_hp* pfloat_a = (float_hp*)&a;
	double result;
	pfloat_a->ToNumber(result);
	return result == 0.0;
}
void CRuntimeInterface::Float_Negate_256(const floatTemp_lp& a, floatTemp_lp& result){
	static_assert(sizeof(a) == sizeof(float_lp), "Size of Precision Float inconsistent");
	// std::cout << "Start of Negate 256" << std::endl;
	memcpy(result._Data, a._Data, sizeof(result._Data)/sizeof(uint8_t));
	float_lp pfloat_b(-1);
	((float_lp*)&result)->Mul(pfloat_b);
}
void CRuntimeInterface::Float_Negate_512(const floatTemp_mp& a, floatTemp_mp& result){
	static_assert(sizeof(a) == sizeof(float_mp), "Size of Precision Float inconsistent");
	// std::cout << "Start of Negate 512" << std::endl;
	memcpy(result._Data, a._Data, sizeof(result._Data)/sizeof(uint8_t));
	float_mp pfloat_b(-1);
	((float_mp*)&result)->Mul(pfloat_b);
}
void CRuntimeInterface::Float_Negate_1024(const floatTemp_hp& a, floatTemp_hp& result){
	static_assert(sizeof(a) == sizeof(float_hp), "Size of Precision Float inconsistent");
	// std::cout << "Start of Negate 1024" << std::endl;
	memcpy(result._Data, a._Data, sizeof(result._Data)/sizeof(uint8_t));
	float_hp pfloat_b(-1);
	((float_hp*)&result)->Mul(pfloat_b);
}
int CRuntimeInterface::Float_Compare_256(const floatTemp_lp& a, const floatTemp_lp& b)
{
	static_assert(sizeof(a) == sizeof(float_lp), "Size of Precision Float inconsistent");
	// std::cout << "Start of Compare 256" << std::endl;
	float_lp pfloat_a;
	memcpy(pfloat_a._Data, a._Data, sizeof(pfloat_a._Data)/sizeof(uint8_t));
	float_lp* pfloat_b = (float_lp*)&b;
	pfloat_a.Sub(*pfloat_b);
	double result;
	pfloat_a.ToNumber(result);
	if(result < 0.0){
		return -1;
	}
	else if(result > 0.0){
		return 1;
	}
	return 0;
}
int CRuntimeInterface::Float_Compare_512(const floatTemp_mp& a, const floatTemp_mp& b)
{
	static_assert(sizeof(a) == sizeof(float_mp), "Size of Precision Float inconsistent");
	// std::cout << "Start of Negate 512" << std::endl;
	float_mp pfloat_a;
	memcpy(pfloat_a._Data, a._Data, sizeof(pfloat_a._Data)/sizeof(uint8_t));
	float_mp* pfloat_b = (float_mp*)&b;
	pfloat_a.Sub(*pfloat_b);
	double result;
	pfloat_a.ToNumber(result);
	if(result < 0.0){
		return -1;
	}
	else if(result > 0.0){
		return 1;
	}
	return 0;
}
int CRuntimeInterface::Float_Compare_1024(const floatTemp_hp& a, const floatTemp_hp& b)
{
	static_assert(sizeof(a) == sizeof(float_hp), "Size of Precision Float inconsistent");
	// std::cout << "Start of Compare 1024" << std::endl;
	float_hp pfloat_a;
	memcpy(pfloat_a._Data, a._Data, sizeof(pfloat_a._Data)/sizeof(uint8_t));
	float_hp* pfloat_b = (float_hp*)&b;
	pfloat_a.Sub(*pfloat_b);
	double result;
	pfloat_a.ToNumber(result);
	if(result < 0.0){
		return -1;
	}
	else if(result > 0.0){
		return 1;
	}
	return 0;
}

uint64_t CRuntimeInterface::Block_GetHeight()
{
	return m_pExecutionContext->GetBlockHeight();
}

uint32_t CRuntimeInterface::Block_GetShardIndex()
{
	return m_pExecutionContext->GetShardIndex();
}

uint32_t CRuntimeInterface::Block_GetShardOrder()
{
	return m_pExecutionContext->GetShardOrder();
}

uint32_t CRuntimeInterface::Block_GetParentShardIndex()
{
	return m_pExecutionContext->GetParentShardIndex();
}

uint32_t CRuntimeInterface::Block_GetParentShardOrder()
{
	return m_pExecutionContext->GetParentShardOrder();
}

const uint8_t* CRuntimeInterface::Block_GetParentBlockHash()
{
	return (const uint8_t*)m_pExecutionContext->GetParentBlockHash();
}

uint64_t CRuntimeInterface::Block_GetTimestamp()
{
	return m_pExecutionContext->GetBlockTime();
}

uint64_t CRuntimeInterface::Block_GetRandomNumber()
{
	return m_pExecutionContext->GetRandomNumber();
}

uint64_t CRuntimeInterface::Block_GetSecureRandomNumber()
{
	return m_pExecutionContext->GetSecureRandomNumber();
}

const uint8_t* CRuntimeInterface::Block_GetMinerAddress()
{
	return (const uint8_t*)m_pExecutionContext->GetMinerAddress();
}

prlrt::transaction_type CRuntimeInterface::Transaction_GetType()
{
	switch (m_pExecutionContext->GetTransactionType())
	{
	case oxd::rvm::InvokeContextType::Normal:
		return prlrt::transaction_type::__prli_normal_type;
	case oxd::rvm::InvokeContextType::RelayIntra:
	case oxd::rvm::InvokeContextType::RelayInbound:
		return prlrt::transaction_type::__prli_relay_type;
	case oxd::rvm::InvokeContextType::System:
		return prlrt::transaction_type::__prli_system_type;
	case oxd::rvm::InvokeContextType::Yield:
	default:
		return prlrt::transaction_type::__prli_issue_type;
	}
}

const uint8_t* CRuntimeInterface::Transaction_GetSelfAddress()
{
	return (const uint8_t*)m_pExecutionContext->GetSelfAddress();
}

uint64_t CRuntimeInterface::Transaction_GetTimeStamp()
{
	return m_pExecutionContext->GetTimestamp();
}

const uint8_t* CRuntimeInterface::Transaction_GetSigner(uint32_t signerIdx)
{
	return (const uint8_t*)m_pExecutionContext->GetSigner(signerIdx);
}

const uint32_t CRuntimeInterface::Transaction_GetSingerCount()
{
	return m_pExecutionContext->GetSignerCount();
}

bool CRuntimeInterface::Transaction_VerifySignerByIndex(uint32_t signerIdx)
{
	return m_pExecutionContext->IsSignedBy(m_pExecutionContext->GetSigner(signerIdx));
}

bool CRuntimeInterface::Transaction_VerifySignerByAddress(const uint8_t* pSignerAddress)
{
	return m_pExecutionContext->IsSignedBy((oxd::rvm::ConstAddress*)pSignerAddress);
}

uint32_t CRuntimeInterface::Transaction_GetOriginatedShardIndex()
{
	return m_pExecutionContext->GetOriginatedShardIndex();
}

uint32_t CRuntimeInterface::Transaction_GetOriginatedShardOrder()
{
	return m_pExecutionContext->GetOriginatedShardOrder();
}

const uint8_t* CRuntimeInterface::Transaction_GetOriginatedAddress()
{
	return (const uint8_t*)m_pExecutionContext->GetOriginatedAddress();
}
