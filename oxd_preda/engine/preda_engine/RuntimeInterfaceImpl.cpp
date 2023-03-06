#include<iostream>

#include "bigint.h"
#include "../../native/abi/vm_interfaces.h"
#include "../../native/types/typetraits.h"
#include "../../transpiler/transpiler/PredaCommon.h"
#include "ExecutionEngine.h"
#include "ContractDatabase.h"
#include "RuntimeInterfaceImpl.h"

namespace _details
{
	struct AddressInplaceBuffer : public rvm::DataBuffer
	{
		uint8_t* _p;
		AddressInplaceBuffer(uint8_t* p) : _p(p) {}
		virtual uint8_t* SetSize(uint32_t len) override
		{
			if (len != 36)
				return nullptr;
			return _p;
		}
		virtual const uint8_t* GetData()
		{
			return _p;
		}
		virtual uint32_t GetSize()
		{
			return 36;
		}
	};
}

CRuntimeInterface::CRuntimeInterface(CContractDatabase *pDB)
	: m_pDB(pDB)
{
}

CRuntimeInterface::~CRuntimeInterface()
{
}

prlrt::BigintPtr CRuntimeInterface::CreateBigint()
{
	prlrt::CBigInt *ptr = new prlrt::CBigInt;
	m_bigint[ptr] = std::unique_ptr<prlrt::CBigInt>(ptr);
	return ptr;
}

void CRuntimeInterface::ReleaseBigint(prlrt::BigintPtr self)
{
	m_bigint.erase(self);
}

void CRuntimeInterface::BigintAssign(prlrt::BigintPtr self, const prlrt::BigintPtr a)
{
	self->Assign(a);
}

void CRuntimeInterface::BigintAssignInt64(prlrt::BigintPtr self, int64_t a)
{
	self->AssignInt64(a);
}

void CRuntimeInterface::BigintAssignString(prlrt::BigintPtr self, const char* a, uint32_t len)
{
	self->AssignString(a, len);
}

void CRuntimeInterface::BigintAssignUint64(prlrt::BigintPtr self, uint64_t a)
{
	self->AssignUint64(a);
}

int CRuntimeInterface::BigintToInt64(prlrt::BigintPtr self, int64_t* out)
{
	return self->ToInt64(out);
}

int CRuntimeInterface::BigintToUint64(prlrt::BigintPtr self, uint64_t* out)
{
	return self->ToUint64(out);
}

void CRuntimeInterface::BigintAdd(prlrt::BigintPtr self, const prlrt::BigintPtr a, const prlrt::BigintPtr b)
{
	self->Add(a, b);
}

void CRuntimeInterface::BigintAddInplace(prlrt::BigintPtr self, const prlrt::BigintPtr a)
{
	self->AddInplace(a);
}

void CRuntimeInterface::BigintSub(prlrt::BigintPtr self, const prlrt::BigintPtr a, const prlrt::BigintPtr b)
{
	self->Sub(a, b);
}

void CRuntimeInterface::BigintSubInplace(prlrt::BigintPtr self, const prlrt::BigintPtr a)
{
	self->SubInplace(a);
}

void CRuntimeInterface::BigintMul(prlrt::BigintPtr self, const prlrt::BigintPtr a, const prlrt::BigintPtr b)
{
	self->Mul(a, b);
}

void CRuntimeInterface::BigintMul_Uint32(prlrt::BigintPtr self, const prlrt::BigintPtr a, uint32_t b)
{
	self->Mul_Uint32(a, b);
}

void CRuntimeInterface::BigintMul_Int32(prlrt::BigintPtr self, const prlrt::BigintPtr a, int b)
{
	self->Mul_Int32(a, b);
}

void CRuntimeInterface::BigintMulInplace_Int32(prlrt::BigintPtr self, int a)
{
	self->MulInplace_Int32(a);
}

void CRuntimeInterface::BigintMulInplace_Uint32(prlrt::BigintPtr self, uint32_t a)
{
	self->MulInplace_Uint32(a);
}

void CRuntimeInterface::BigintDiv_Uint32(prlrt::BigintPtr self, const prlrt::BigintPtr a, uint32_t b, uint32_t* remainder)
{
	self->Div_Uint32(a, b, remainder);
}

void CRuntimeInterface::BigintDiv(prlrt::BigintPtr self, const prlrt::BigintPtr a, const prlrt::BigintPtr b, prlrt::BigintPtr remainder)
{
	self->Div(a, b, remainder);
}

void CRuntimeInterface::BigintMod(prlrt::BigintPtr self, const prlrt::BigintPtr a, const prlrt::BigintPtr b)
{
	self->Mod(a, b);
}

void CRuntimeInterface::BigintNegate(prlrt::BigintPtr self, const prlrt::BigintPtr a)
{
	self->Negate(a);
}

void CRuntimeInterface::BigintNegateInplace(prlrt::BigintPtr self)
{
	self->NegateInplace();
}

int CRuntimeInterface::BigintCompare(prlrt::BigintPtr self, const prlrt::BigintPtr a)
{
	return self->Compare(a);
}

uint32_t CRuntimeInterface::BigintInitFromEmbedded(prlrt::BigintPtr self, const uint8_t* in, uint32_t in_size)
{
	return self->InitFromEmbedded(in, in_size);
}

uint32_t CRuntimeInterface::BigintGetEmbeddedSize(prlrt::BigintPtr self)
{
	return self->GetEmbeddedSize();
}

void CRuntimeInterface::BigintEmbed(prlrt::BigintPtr self, uint8_t* out)
{
	return self->Embed(out);
}

bool CRuntimeInterface::BigintIsEmbeddable(prlrt::BigintPtr self)
{
	return self->IsEmbeddable();
}

uint32_t CRuntimeInterface::BigintGetStringLength(prlrt::BigintPtr self)
{
	self->GetString();
	return uint32_t(self->m_stringCache.GetLength());
}

uint32_t CRuntimeInterface::BigintToString(prlrt::BigintPtr self, char* out, uint32_t length)
{
	const char* str = self->GetString();
	uint32_t write_len = std::min((uint32_t)self->m_stringCache.GetLength(), length);
	std::memcpy(out, str, write_len);
	return write_len;
}

bool CRuntimeInterface::InitAddressFromLiteral(void *pAddress, const char *str)
{
	return ::rvm::_details::_JsonParse(*(::rvm::Address *)pAddress, rt::String_Ref(str)).ret;
}

bool CRuntimeInterface::InitHashFromLiteral(void *pHash, const char *str)
{
	rt::String_Ref tmp(str, 52);
	return ::oxd::b32str::Decode(pHash, 32, tmp.Begin(), tmp.GetLength());
}

void CRuntimeInterface::CalculateHash(void *pHash, const uint8_t *data, uint32_t data_len)
{
	oxd::SecuritySuite::Hash(data, data_len, pHash);
}

bool CRuntimeInterface::StringToAddress(void *pAddress, const char *data, uint32_t data_len)
{
	rvm::ConstString cs{ data, data_len };
	_details::AddressInplaceBuffer buf((uint8_t*)pAddress);
	if (!m_pDB->m_pRuntimeAPI->JsonParseCoreType(rvm::NativeTypeId::Address, &cs, &buf))
		return false;
	return true;
}

void CRuntimeInterface::PushContractStack(PredaContractDID deployId, rvm::ContractId contractId, uint32_t functionFlags)
{
	ContractStackEntry entry;
	entry.deployId = deployId;
	entry.contractId = contractId;
	entry.funtionFlags = functionFlags;
	m_contractStack.push_back(entry);

	bool bIsConstCall = (functionFlags & uint32_t(transpiler::PredaFunctionFlags::IsConst)) != 0;

	if (!bIsConstCall)
	{
		auto itor = m_contractStateModifiedFlags.try_emplace(deployId, std::array<bool, uint8_t(prlrt::ContractContextType::Num)>{false, false, false, false});
		uint32_t contextClassLevel = uint32_t(functionFlags & uint32_t(transpiler::PredaFunctionFlags::ContextClassMask));
		for (uint32_t i = 0; i <= contextClassLevel; i++)
			itor.first->second[i] = true;
	}
}

void CRuntimeInterface::ClearBigInt() {
	m_bigint.clear();
}

bool CRuntimeInterface::EmitRelayToAddress(const uint8_t *address, uint32_t opCode, const uint8_t* args_serialized, uint32_t args_size)
{
	rvm::ConstData args;
	args.DataPtr = args_serialized;
	args.DataSize = args_size;
	// TODO: implement gas_redistribution_weight on preda code level
	return m_pExecutionContext->EmitRelayToAddress(rvm::BuildNumLatest, (rvm::ConstAddress *)address, rvm::_details::CONTRACT_SET_SCOPE(m_contractStack.back().contractId, rvm::Scope::Address), rvm::OpCode(opCode), &args, 1);
}

bool CRuntimeInterface::EmitRelayToGlobal(uint32_t opCode, const uint8_t* args_serialized, uint32_t args_size)
{
	rvm::ConstData args;
	args.DataPtr = args_serialized;
	args.DataSize = args_size;
	// TODO: implement gas_redistribution_weight on preda code level
	return m_pExecutionContext->EmitRelayToGlobal(rvm::BuildNumLatest, rvm::_details::CONTRACT_SET_SCOPE(m_contractStack.back().contractId, rvm::Scope::Global), rvm::OpCode(opCode), &args, 1);
}

bool CRuntimeInterface::EmitRelayToShards(uint32_t opCode, const uint8_t* args_serialized, uint32_t args_size)
{
	rvm::ConstData args;
	args.DataPtr = args_serialized;
	args.DataSize = args_size;
	// TODO: implement gas_redistribution_weight on preda code level
	return m_pExecutionContext->EmitBroadcastToShards(rvm::BuildNumLatest, rvm::_details::CONTRACT_SET_SCOPE(m_contractStack.back().contractId, rvm::Scope::Shard), rvm::OpCode(opCode), &args, 1);
}

uint32_t CRuntimeInterface::CrossCall(uint64_t contractId, uint32_t opCode, const void **ptrs, uint32_t numPtrs)
{
	return m_pExecutionEngine->InvokeContractCall(m_pExecutionContext, rvm::ContractId(contractId), opCode, ptrs, numPtrs);
}

uint32_t CRuntimeInterface::InterfaceCall(uint64_t contractId, const char* interfaceName, uint32_t funcIdx, const void** ptrs, uint32_t numPtrs)
{
	PredaContractDID deployId = _details::RvmCDIDToPredaCDID(m_pChainState->GetContractDeploymentIdentifier(rvm::ContractId(contractId)));		// interface call always calls the latest build

	const ContractDatabaseEntry *pEntry = m_pDB->FindContractEntry(deployId);
	if (!pEntry)
		return uint32_t(ExecutionResult::ContractNotFound);

	for (int i = 0; i < pEntry->compileData.implementedInterfaces.size(); i++)
	{
		if (pEntry->compileData.implementedInterfaces[i].name == interfaceName)
		{
			if (funcIdx < uint32_t(pEntry->compileData.implementedInterfaces[i].functionIds.size()))
			{
				uint32_t opCode = pEntry->compileData.implementedInterfaces[i].functionIds[funcIdx];
				return m_pExecutionEngine->InvokeContractCall(m_pExecutionContext, rvm::ContractId(contractId), opCode, ptrs, numPtrs);
			}
			return uint32_t(ExecutionResult::InvalidFunctionId);
		}
	}

	return uint32_t(ExecutionResult::InvalidFunctionId);
}

void CRuntimeInterface::ReportOrphanToken(uint64_t id, prlrt::BigintPtr amount)
{
	if (!m_bReportOrphanToken)
		return;

	uint64_t v;
	amount->ToUint64(&v);
	std::cout << "orphan token: id " << id << ", amount " << v << std::endl;
}

void CRuntimeInterface::ReportReturnValue(const char *type_export_name, const uint8_t *serialized_data, uint32_t serialized_data_size)
{
	//DebugPrintBufferAppendSerializedData(type_export_name, serialized_data, serialized_data_size);
	//DebugPrintOutputBuffer();
}

void CRuntimeInterface::DebugPrintBufferAppendSerializedData(const char *type_export_name, const uint8_t *serialized_data, uint32_t serialized_data_size)
{
	if (type_export_name == nullptr || serialized_data == nullptr)
		return;

	std::string outputStr;
	bool res = m_pDB->VariableJsonify(m_contractStack.back().deployId, type_export_name, serialized_data, serialized_data_size, outputStr, m_pChainState);
	assert(res);

	m_logOutputBuffer += outputStr;
}

void CRuntimeInterface::DebugPrintOutputBuffer()
{
	rvm::ConstString s{ m_logOutputBuffer.c_str(), uint32_t(m_logOutputBuffer.size()) };

	m_pDB->m_pRuntimeAPI->DebugPrint(rvm::DebugMessageType::Informational, &s, m_pExecutionContext, m_pDB->GetContract(m_contractStack.back().deployId));
	m_logOutputBuffer.clear();
}

void CRuntimeInterface::DebugAssertionFailure(uint32_t line)
{
	std::string tmp = "Assertion failure on line " + std::to_string(line);
	rvm::ConstString s{ tmp.c_str(), uint32_t(tmp.size()) };
	m_pDB->m_pRuntimeAPI->DebugPrint(rvm::DebugMessageType::Warning, &s, m_pExecutionContext, m_pDB->GetContract(m_contractStack.back().deployId));
}

uint32_t CRuntimeInterface::GetTokenIdByName(const char* name)
{
	const rvm::ConstString tokenName = { name, uint32_t(strlen(name)) };
	rvm::TokenId id = m_pExecutionContext->GetTokenBySymbol(&tokenName);

	uint32_t ret;
	static_assert(std::is_same_v<std::underlying_type_t<decltype(id)>, std::remove_const_t<std::remove_reference_t<decltype(ret)>>>);

	ret = enum_to_underlying(id);
	return ret;
}

bool CRuntimeInterface::IsUserAddress(const void *pAddress)
{
	return !((oxd::SecureAddress*)pAddress)->IsDelegated();
}

bool CRuntimeInterface::IsDelegatedAddress(const void *pAddress)
{
	return ((oxd::SecureAddress*)pAddress)->IsDelegated();
}

bool CRuntimeInterface::IsDAppAddress(const void *pAddress)
{
	return ((oxd::SecureAddress*)pAddress)->GetSecuritySuiteId() == oxd::SEC_SUITE_REGISTERED_DAPP;
}

bool CRuntimeInterface::IsAssetAddress(const void *pAddress)
{
	return ((oxd::SecureAddress*)pAddress)->GetSecuritySuiteId() == oxd::SEC_SUITE_REGISTERED_TOKEN;
}

bool CRuntimeInterface::IsNameAddress(const void *pAddress)
{
	return ((oxd::SecureAddress*)pAddress)->GetSecuritySuiteId() == oxd::SEC_SUITE_REGISTERED_NAME;
}

bool CRuntimeInterface::IsDomainAddress(const void *pAddress)
{
	return ((oxd::SecureAddress*)pAddress)->GetSecuritySuiteId() == oxd::SEC_SUITE_REGISTERED_DOMAIN;
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

#define PREDA_FLOAT_METHOD_IMPL(_FLOAT_TYPE, _SIZE)\
void CRuntimeInterface::ConvertToString_##_SIZE(const ::prlrt::PrecisionFloatTemp<_SIZE>* pftemp, char* buf){\
	static_assert(sizeof(std::remove_pointer_t<decltype(pftemp)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	_FLOAT_TYPE* pfloat = (_FLOAT_TYPE*)pftemp;\
	std::string float_literal = pfloat->ToString();\
	memcpy(buf, float_literal.data(), float_literal.length());\
}\
uint32_t CRuntimeInterface::GetConvertToStringLen_##_SIZE(const ::prlrt::PrecisionFloatTemp<_SIZE>* pftemp){\
	static_assert(sizeof(std::remove_pointer_t<decltype(pftemp)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	_FLOAT_TYPE* pfloat = (_FLOAT_TYPE*)pftemp;\
	return (uint32_t)pfloat->ToString().length();\
}\
void CRuntimeInterface::ConvertFromString_##_SIZE(::prlrt::PrecisionFloatTemp<_SIZE>* pftemp, const char* float_literal){\
	static_assert(sizeof(std::remove_pointer_t<decltype(pftemp)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	_FLOAT_TYPE pfloat(float_literal);\
	*pftemp = *((::prlrt::PrecisionFloatTemp<_SIZE>*)&pfloat);\
}\
void CRuntimeInterface::Float_Add_##_SIZE(const ::prlrt::PrecisionFloatTemp<_SIZE>* a, const ::prlrt::PrecisionFloatTemp<_SIZE>* b, ::prlrt::PrecisionFloatTemp<_SIZE>* result){\
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	static_assert(sizeof(std::remove_pointer_t<decltype(b)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	memcpy(result->_Data, a->_Data, sizeof(result->_Data)/sizeof(uint8_t));\
	((_FLOAT_TYPE*)result)->Add(*((_FLOAT_TYPE*)b));\
}\
void CRuntimeInterface::Float_Sub_##_SIZE(const ::prlrt::PrecisionFloatTemp<_SIZE>* a, const ::prlrt::PrecisionFloatTemp<_SIZE>* b, ::prlrt::PrecisionFloatTemp<_SIZE>* result){\
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	static_assert(sizeof(std::remove_pointer_t<decltype(b)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	memcpy(result->_Data, a->_Data, sizeof(result->_Data)/sizeof(uint8_t));\
	((_FLOAT_TYPE*)result)->Sub(*((_FLOAT_TYPE*)b));\
}\
void CRuntimeInterface::Float_Mul_##_SIZE(const ::prlrt::PrecisionFloatTemp<_SIZE>* a, const ::prlrt::PrecisionFloatTemp<_SIZE>* b, ::prlrt::PrecisionFloatTemp<_SIZE>* result){\
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	static_assert(sizeof(std::remove_pointer_t<decltype(b)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	memcpy(result->_Data, a->_Data, sizeof(result->_Data)/sizeof(uint8_t));\
	((_FLOAT_TYPE*)result)->Mul(*((_FLOAT_TYPE*)b));\
}\
void CRuntimeInterface::Float_Div_##_SIZE(const ::prlrt::PrecisionFloatTemp<_SIZE>* a, const ::prlrt::PrecisionFloatTemp<_SIZE>* b, ::prlrt::PrecisionFloatTemp<_SIZE>* result){\
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	static_assert(sizeof(std::remove_pointer_t<decltype(b)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	memcpy(result->_Data, a->_Data, sizeof(result->_Data)/sizeof(uint8_t));\
	((_FLOAT_TYPE*)result)->Div(*((_FLOAT_TYPE*)b));\
}\
void CRuntimeInterface::Float_Zero_##_SIZE(::prlrt::PrecisionFloatTemp<_SIZE>* a){\
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	_FLOAT_TYPE pfloat(0);\
	*a = *((::prlrt::PrecisionFloatTemp<_SIZE>*)&pfloat);\
}\
bool CRuntimeInterface::Float_IsZero_##_SIZE(const ::prlrt::PrecisionFloatTemp<_SIZE>* a){\
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	_FLOAT_TYPE* pfloat_a = (_FLOAT_TYPE*)a;\
	double result;\
	pfloat_a->ToNumber(result);\
	return result == 0.0;\
}\
void CRuntimeInterface::Float_Negate_##_SIZE(const ::prlrt::PrecisionFloatTemp<_SIZE>* a, ::prlrt::PrecisionFloatTemp<_SIZE>* result)\
{\
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	memcpy(result->_Data, a->_Data, sizeof(result->_Data)/sizeof(uint8_t));\
	_FLOAT_TYPE pfloat_b(-1);\
	((_FLOAT_TYPE*)result)->Mul(pfloat_b);\
}\
int CRuntimeInterface::Float_Compare_##_SIZE(const ::prlrt::PrecisionFloatTemp<_SIZE>* a, const ::prlrt::PrecisionFloatTemp<_SIZE>* b)\
{\
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	_FLOAT_TYPE pfloat_a;\
	memcpy(pfloat_a._Data, a->_Data, sizeof(pfloat_a._Data)/sizeof(uint8_t));\
	_FLOAT_TYPE* pfloat_b = (_FLOAT_TYPE*)b;\
	pfloat_a.Sub(*pfloat_b);\
	double result;\
	pfloat_a.ToNumber(result);\
	if(result < 0.0){\
		return -1;\
	}\
	else if(result > 0.0){\
		return 1;\
	}\
	return 0;\
}\

PREDA_FLOAT_METHOD_IMPL(float_lp, 256)
PREDA_FLOAT_METHOD_IMPL(float_mp, 512)
PREDA_FLOAT_METHOD_IMPL(float_hp, 1024)


#define LONGINT_NEGATE_FUNC(_SIZE) \
void CRuntimeInterface::LongInt_Negate_##_SIZE(const ::prlrt::LongIntTemp<_SIZE>* a, ::prlrt::LongIntTemp<_SIZE>* result){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(LongInt_##_SIZE), "Size of DataType inconsistent"); \
	memcpy(result->_Data, a->_Data, sizeof(result->_Data)/sizeof(uint8_t)); \
	((LongInt_##_SIZE*)result)->ChangeSign(); } \
bool CRuntimeInterface::LongInt_IsSign_##_SIZE(const ::prlrt::LongIntTemp<_SIZE>* a){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(LongInt_##_SIZE), "Size of DataType inconsistent"); \
	return ((LongInt_##_SIZE*)a)->IsSign(); }
#define LONGINTIMPLFUNC(_SIZE, _INT_TYPE) \
void CRuntimeInterface::_INT_TYPE##_Zero_##_SIZE(::prlrt::LongIntTemp<_SIZE>* a){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(LongInt_##_SIZE), "Size of DataType inconsistent"); \
	_INT_TYPE##_##_SIZE b(0); \
	*a = *((::prlrt::LongIntTemp<_SIZE>*)&b); } \
void CRuntimeInterface::_INT_TYPE##_fromInt_##_SIZE(::prlrt::LongIntTemp<_SIZE>* a, int64_t in){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(LongInt_##_SIZE), "Size of DataType inconsistent"); \
	((_INT_TYPE##_##_SIZE*)a)->FromInt((ttmath::sint)in); } \
void CRuntimeInterface::_INT_TYPE##_fromUInt_##_SIZE(::prlrt::LongIntTemp<_SIZE>* a, uint64_t in){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(LongInt_##_SIZE), "Size of DataType inconsistent"); \
	((_INT_TYPE##_##_SIZE*)a)->FromInt((ttmath::uint)in); } \
int CRuntimeInterface::_INT_TYPE##_toInt64_##_SIZE(const ::prlrt::LongIntTemp<_SIZE>* a, int64_t* result){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(LongInt_##_SIZE), "Size of DataType inconsistent"); \
	return ((_INT_TYPE##_##_SIZE*)a)->ToInt(*(ttmath::sint*)result); } \
int CRuntimeInterface::_INT_TYPE##_toUInt64_##_SIZE(const ::prlrt::LongIntTemp<_SIZE>* a, uint64_t* result){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(LongInt_##_SIZE), "Size of DataType inconsistent"); \
	return ((_INT_TYPE##_##_SIZE*)a)->ToUInt(*(ttmath::uint*)result); } \
void CRuntimeInterface::_INT_TYPE##_rightShift_##_SIZE(::prlrt::LongIntTemp<_SIZE>* a, int64_t shift){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(LongInt_##_SIZE), "Size of DataType inconsistent"); \
	*((_INT_TYPE##_##_SIZE*)a) >>= shift; } \
void CRuntimeInterface::_INT_TYPE##_leftShift_##_SIZE(::prlrt::LongIntTemp<_SIZE>* a, int64_t shift){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(LongInt_##_SIZE), "Size of DataType inconsistent"); \
	*((_INT_TYPE##_##_SIZE*)a) <<= shift; } \
void CRuntimeInterface::_INT_TYPE##_ConvertFromString_##_SIZE(::prlrt::LongIntTemp<_SIZE>* a, const char* longint_literal){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(LongInt_##_SIZE), "Size of DataType inconsistent"); \
	_INT_TYPE##_##_SIZE b(longint_literal); \
	*a = *((::prlrt::LongIntTemp<_SIZE>*)&b); } \
void CRuntimeInterface::_INT_TYPE##_ConvertFromHexString_##_SIZE(::prlrt::LongIntTemp<_SIZE>* a, const char* longint_literal){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	_INT_TYPE##_##_SIZE b; \
	b.FromString(longint_literal, 16); \
	*a = *((::prlrt::LongIntTemp<_SIZE>*)&b); } \
void CRuntimeInterface::_INT_TYPE##_ConvertToString_##_SIZE(const ::prlrt::LongIntTemp<_SIZE>* a, char* buf){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	std::string result; \
	((_INT_TYPE##_##_SIZE*)a)->ToString(result); \
	memcpy(buf, result.data(), result.length()); } \
uint32_t CRuntimeInterface::_INT_TYPE##_GetConvertToStringLen_##_SIZE(const ::prlrt::LongIntTemp<_SIZE>* a){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	return uint32_t(((_INT_TYPE##_##_SIZE*)a)->ToString().length()); } \
bool CRuntimeInterface::_INT_TYPE##_IsZero_##_SIZE(const ::prlrt::LongIntTemp<_SIZE>* a) { \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	return ((_INT_TYPE##_##_SIZE*)a)->IsZero(); } \
void CRuntimeInterface::_INT_TYPE##_Add_##_SIZE(const ::prlrt::LongIntTemp<_SIZE>* a, const ::prlrt::LongIntTemp<_SIZE>* b, ::prlrt::LongIntTemp<_SIZE>* result){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	static_assert(sizeof(std::remove_pointer_t<decltype(b)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	memcpy(result->_Data, a->_Data, sizeof(result->_Data)/sizeof(uint8_t)); \
	((_INT_TYPE##_##_SIZE*)result)->Add(*((_INT_TYPE##_##_SIZE*)b)); } \
void CRuntimeInterface::_INT_TYPE##_Sub_##_SIZE(const ::prlrt::LongIntTemp<_SIZE>* a, const ::prlrt::LongIntTemp<_SIZE>* b, ::prlrt::LongIntTemp<_SIZE>* result){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	static_assert(sizeof(std::remove_pointer_t<decltype(b)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	memcpy(result->_Data, a->_Data, sizeof(result->_Data)/sizeof(uint8_t)); \
	((_INT_TYPE##_##_SIZE*)result)->Sub(*((_INT_TYPE##_##_SIZE*)b)); } \
void CRuntimeInterface::_INT_TYPE##_Mul_##_SIZE(const ::prlrt::LongIntTemp<_SIZE>* a, const ::prlrt::LongIntTemp<_SIZE>* b, ::prlrt::LongIntTemp<_SIZE>* result){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	static_assert(sizeof(std::remove_pointer_t<decltype(b)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	memcpy(result->_Data, a->_Data, sizeof(result->_Data)/sizeof(uint8_t)); \
	((_INT_TYPE##_##_SIZE*)result)->Mul(*((_INT_TYPE##_##_SIZE*)b)); } \
void CRuntimeInterface::_INT_TYPE##_Div_##_SIZE(const ::prlrt::LongIntTemp<_SIZE>* a, const ::prlrt::LongIntTemp<_SIZE>* b, ::prlrt::LongIntTemp<_SIZE>* result){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	static_assert(sizeof(std::remove_pointer_t<decltype(b)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	memcpy(result->_Data, a->_Data, sizeof(result->_Data)/sizeof(uint8_t)); \
	((_INT_TYPE##_##_SIZE*)result)->Div(*((_INT_TYPE##_##_SIZE*)b)); } \
void CRuntimeInterface::_INT_TYPE##_Mod_##_SIZE(const ::prlrt::LongIntTemp<_SIZE>* a, const ::prlrt::LongIntTemp<_SIZE>* b, ::prlrt::LongIntTemp<_SIZE>* result){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	static_assert(sizeof(std::remove_pointer_t<decltype(b)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	_INT_TYPE##_##_SIZE remainder = (*(_INT_TYPE##_##_SIZE*)a) % (*((_INT_TYPE##_##_SIZE*)b)); \
	memcpy(result->_Data, &remainder, sizeof(result->_Data)/sizeof(uint8_t)); } \
int CRuntimeInterface::_INT_TYPE##_Compare_##_SIZE(const ::prlrt::LongIntTemp<_SIZE>* a, const ::prlrt::LongIntTemp<_SIZE>* b){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	static_assert(sizeof(std::remove_pointer_t<decltype(b)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	_INT_TYPE##_##_SIZE* a_math = (_INT_TYPE##_##_SIZE*)a; \
	_INT_TYPE##_##_SIZE* b_math = (_INT_TYPE##_##_SIZE*)b; \
	if(*a_math > *b_math) return 1; \
	else if(*a_math < *b_math) return -1; \
	return 0;} \
void CRuntimeInterface::_INT_TYPE##_SetMax_##_SIZE(::prlrt::LongIntTemp<_SIZE>* a){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	((_INT_TYPE##_##_SIZE*)a)->SetMax(); } \
void CRuntimeInterface::_INT_TYPE##_SetMin_##_SIZE(::prlrt::LongIntTemp<_SIZE>* a){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	((_INT_TYPE##_##_SIZE*)a)->SetMin(); }
#pragma warning(push)
#pragma warning(disable:4244)
LONGINT_NEGATE_FUNC(128)
LONGINT_NEGATE_FUNC(256)
LONGINT_NEGATE_FUNC(512)
LONGINTIMPLFUNC(128, LongInt)
LONGINTIMPLFUNC(256, LongInt)
LONGINTIMPLFUNC(512, LongInt)
LONGINTIMPLFUNC(128, ULongInt)
LONGINTIMPLFUNC(256, ULongInt)
LONGINTIMPLFUNC(512, ULongInt)
#pragma warning(pop)
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

uint64_t CRuntimeInterface::Block_GetTimestamp()
{
	return m_pExecutionContext->GetBlockTime();
}

uint64_t CRuntimeInterface::Block_GetRandomNumber()
{
	return m_pExecutionContext->GetRandomNumber();
}

void CRuntimeInterface::Block_GetMinerAddress(uint8_t* out)
{
	*(rvm::Address*)out = *m_pExecutionContext->GetBlockCreator();
}

prlrt::transaction_type CRuntimeInterface::Transaction_GetType()
{
	switch (m_pExecutionContext->GetInvokeType())
	{
	case rvm::InvokeContextType::RelayIntra:
	case rvm::InvokeContextType::RelayInbound:
		return prlrt::transaction_type::__prli_relay_type;
	case rvm::InvokeContextType::System:
		return prlrt::transaction_type::__prli_system_type;
	case rvm::InvokeContextType::Scheduled:
		return prlrt::transaction_type::__prli_scheduled_type;
	case rvm::InvokeContextType::Normal:
	default:
		return prlrt::transaction_type::__prli_normal_type;
	}
}

void CRuntimeInterface::Transaction_GetSelfAddress(uint8_t* out)
{
	// only if scope is address
	if (rvm::_details::CONTRACT_SCOPE(m_pExecutionContext->GetContractId()) == rvm::Scope::Address)
		*(rvm::Address*)out = *(rvm::Address*)m_pExecutionContext->GetScopeTarget().Data;

}

uint64_t CRuntimeInterface::Transaction_GetTimeStamp()
{
	return m_pExecutionContext->GetTimestamp();
}

void CRuntimeInterface::Transaction_GetSigner(uint32_t signerIdx, uint8_t* out)
{
	*(rvm::Address*)out = *m_pExecutionContext->GetSigner(signerIdx);
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
	return m_pExecutionContext->IsSignedBy((rvm::ConstAddress*)pSignerAddress);
}

uint32_t CRuntimeInterface::Transaction_GetOriginatedShardIndex()
{
	return m_pExecutionContext->GetOriginatedShardIndex();
}

uint32_t CRuntimeInterface::Transaction_GetOriginatedShardOrder()
{
	return m_pExecutionContext->GetOriginatedShardOrder();
}

void CRuntimeInterface::Transaction_GetInitiatorAddress(uint8_t* out)
{
	*(rvm::Address*)out = *m_pExecutionContext->GetInitiator();
}

void CRuntimeInterface::Event_Push(uint32_t, const char*, uint32_t)
{
}

prlrt::uievent_state CRuntimeInterface::Event_GetUserState()
{
	return prlrt::uievent_state::__prli_activated;
}

void CRuntimeInterface::Event_Notify(uint32_t, const char*, uint32_t)
{
}

void CRuntimeInterface::Event_Exception(const char* msg, prlrt::ExceptionType exc_type)
{
	// this method in only called in wasm mode
	// since in wasm, cpp exception is not supported
	// `curr_exc` is set to a stack value before calling any method inside vm
	ASSERT(!exec_stack.empty());
	exec_stack.top() = exc_type;
}
