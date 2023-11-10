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

void CRuntimeInterface::BigintShiftRightInplace(prlrt::BigintPtr self, int a)
{
	self->ShiftRightInplace(a);
}

void CRuntimeInterface::BigintShiftLeftInplace(prlrt::BigintPtr self, int a)
{
	self->ShiftLeftInplace(a);
}

void CRuntimeInterface::BigintNegate(prlrt::BigintPtr self, const prlrt::BigintPtr a)
{
	self->Negate(a);
}

void CRuntimeInterface::BigintNegateInplace(prlrt::BigintPtr self)
{
	self->NegateInplace();
}

bool CRuntimeInterface::BigintIsNegative(prlrt::BigintPtr self)
{
	return self->IsNegative();
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
	return ::rvm::RvmTypeJsonParse(*(::rvm::Address *)pAddress, rt::String_Ref(str));
}

bool CRuntimeInterface::InitHashFromLiteral(void *pHash, const char *str)
{
	return ::oxd::b32str::Decode(pHash, 32, str, os::Base32EncodeLength(sizeof(rvm::HashValue)));
}

void CRuntimeInterface::CalculateHash(void *pHash, const uint8_t *data, uint32_t data_len)
{
	oxd::SecuritySuite::Hash(data, data_len, pHash);
}

bool CRuntimeInterface::StringToAddress(void *pAddress, const char *data, uint32_t data_len)
{
	return ((oxd::SecureAddress*)pAddress)->FromString(rt::String_Ref(data, data_len));
}

uint32_t CRuntimeInterface::GetAddressToStringLength(const void* pAddress)
{
	return oxd::SecureAddress::String::GetStringifyLength(*(oxd::SecureAddress*)pAddress);
}

bool CRuntimeInterface::AddressToString(const void* pAddress, uint32_t dataLen, char* out)
{
	if (dataLen != sizeof(rvm::Address))
		return false;

	oxd::SecureAddress::String str(*(oxd::SecureAddress*)pAddress);
	memcpy(out, str.GetString(), str.GetLength());

	return true;
}

uint32_t CRuntimeInterface::GetHashToStringLength()
{
	return (uint32_t)os::Base32EncodeLength(RVM_HASH_SIZE);
}

bool CRuntimeInterface::HashToString(const void* pData, uint32_t dataLen, char* out)
{
	if(dataLen != sizeof(rvm::HashValue))
	{
		return false;
	}
	rt::tos::Base32CrockfordLowercaseOnStack<> str(pData, dataLen);
	memcpy(out, str.Begin(), str.GetLength());
	return true;
}

void CRuntimeInterface::PushContractStack(const rvm::ContractModuleID &moduleId, rvm::ContractVersionId cvId, uint32_t functionFlags, const rvm::ContractVersionId* importedCvId, uint32_t numImportedContracts)
{
	ContractStackEntry entry;
	entry.moduleId = moduleId;
	entry.cvId = cvId;
	entry.funtionFlags = functionFlags;
	entry.importedCvIds = importedCvId;
	entry.numImportedContracts = numImportedContracts;
	m_contractStack.push_back(entry);

	bool bIsConstCall = (functionFlags & uint32_t(transpiler::FunctionFlags::IsConst)) != 0;

	if (!bIsConstCall)
	{
		std::array<bool, uint8_t(prlrt::ContractContextType::Num)> initialFlags;
		initialFlags.fill(false);
		auto itor = m_contractStateModifiedFlags.try_emplace(cvId, initialFlags);
		transpiler::ScopeType scope = transpiler::ScopeType(functionFlags & uint32_t(transpiler::FunctionFlags::ScopeTypeMask));
		itor.first->second[uint32_t(scope)] = true;
		if (uint32_t(scope) > uint32_t(transpiler::ScopeType::Global))
			itor.first->second[uint32_t(transpiler::ScopeType::Global)] = true;
		if (uint32_t(scope) > uint32_t(transpiler::ScopeType::Shard))
			itor.first->second[uint32_t(transpiler::ScopeType::Shard)] = true;
	}
}

void CRuntimeInterface::ClearBigInt() {
	m_bigint.clear();
}

bool CRuntimeInterface::EmitRelayToScope(const uint8_t* scope_key, uint32_t scope_key_size, uint32_t scope_type, uint32_t opCode, const uint8_t* args_serialized, uint32_t args_size)
{
	rvm::ConstData args;
	args.DataPtr = args_serialized;
	args.DataSize = args_size;
	// TODO: implement gas_redistribution_weight on preda code level
	rvm::Scope rvmScope = _details::PredaScopeToRvmScope(transpiler::ScopeType(scope_type));
	rvm::ScopeKey key{ scope_key, scope_key_size };
	return m_pExecutionContext->EmitRelayToScope(rvm::CONTRACT_SET_SCOPE(m_contractStack.back().cvId, rvmScope), &key, rvm::OpCode(opCode), &args, 1);
}

bool CRuntimeInterface::EmitRelayToGlobal(uint32_t opCode, const uint8_t* args_serialized, uint32_t args_size)
{
	rvm::ConstData args;
	args.DataPtr = args_serialized;
	args.DataSize = args_size;
	// TODO: implement gas_redistribution_weight on preda code level
	return m_pExecutionContext->EmitRelayToGlobal(rvm::CONTRACT_SET_SCOPE(m_contractStack.back().cvId, rvm::Scope::Global), rvm::OpCode(opCode), &args, 1);
}

bool CRuntimeInterface::EmitRelayToShards(uint32_t opCode, const uint8_t* args_serialized, uint32_t args_size)
{
	rvm::ConstData args;
	args.DataPtr = args_serialized;
	args.DataSize = args_size;
	// TODO: implement gas_redistribution_weight on preda code level
	return m_pExecutionContext->EmitBroadcastToShards(rvm::CONTRACT_SET_SCOPE(m_contractStack.back().cvId, rvm::Scope::Shard), rvm::OpCode(opCode), &args, 1);
}

uint32_t CRuntimeInterface::CrossCall(uint64_t cvId, int64_t templateContractImportSlot, uint32_t opCode, const void **ptrs, uint32_t numPtrs)
{
	static_assert(sizeof(cvId) == sizeof(rvm::ContractVersionId));

	if (templateContractImportSlot < -1 || templateContractImportSlot >= int64_t(m_contractStack.back().numImportedContracts))
		return uint32_t(prlrt::ExecutionError::RuntimeException) | (uint32_t(prlrt::ExceptionType::CrossCallContractNotFound) << 8);

	rvm::ContractVersionId templateCvId = templateContractImportSlot == -1 ? m_contractStack.back().cvId : m_contractStack.back().importedCvIds[templateContractImportSlot];

	// since the call is via arbitrary contract id, it's possible that the contract is not a copy of the base contract
	// check if their DID are the same
	if (cvId != uint64_t(templateCvId))
	{
		const rvm::DeployedContract *deployedContract = m_pChainState->GetContractDeployed(rvm::ContractVersionId(cvId));
		const rvm::DeployedContract *baseDeployedContract = m_pChainState->GetContractDeployed(templateCvId);
		if (deployedContract == nullptr || baseDeployedContract == nullptr || memcmp(&deployedContract->Module, &baseDeployedContract->Module, sizeof(rvm::ContractModuleID)) != 0)
			return uint32_t(ExecutionResult::InvalidFunctionId);
	}
	return m_pExecutionEngine->InvokeContractCall(m_pExecutionContext, rvm::ContractVersionId(cvId), opCode, ptrs, numPtrs);
}

uint32_t CRuntimeInterface::InterfaceCall(uint64_t cvId, int64_t interfaceContractImportSlot, uint32_t interfaceSlot, uint32_t funcIdx, const void** ptrs, uint32_t numPtrs)
{
	const ContractImplementedInterface* implementedInterface = GetImplementedInterfaceFromContract(cvId, interfaceContractImportSlot, interfaceSlot);
	if (implementedInterface == nullptr)
		return uint32_t(prlrt::ExecutionError::RuntimeException) | (uint32_t(prlrt::ExceptionType::CrossCallContractNotFound) << 8);

	if (funcIdx >= uint32_t(implementedInterface->functionIds.size()))
		return uint32_t(prlrt::ExecutionError::RuntimeException) | (uint32_t(prlrt::ExceptionType::CrossCallFunctionNotFound) << 8);

	uint32_t opCode = implementedInterface->functionIds[funcIdx];
	return m_pExecutionEngine->InvokeContractCall(m_pExecutionContext, rvm::ContractVersionId(cvId), opCode, ptrs, numPtrs);
}

bool CRuntimeInterface::InterfaceIsImplemented(uint64_t cvId, int64_t interfaceContractImportSlot, uint32_t interfaceSlot)
{
	return GetImplementedInterfaceFromContract(cvId, interfaceContractImportSlot, interfaceSlot) != nullptr;
}

const ContractImplementedInterface* CRuntimeInterface::GetImplementedInterfaceFromContract(uint64_t cvId, int64_t interfaceContractImportSlot, uint32_t interfaceSlot)
{
	static_assert(sizeof(cvId) == sizeof(rvm::ContractVersionId));

	if (interfaceContractImportSlot < -1 || interfaceContractImportSlot >= int64_t(m_contractStack.back().numImportedContracts))
		return nullptr;

	rvm::ContractVersionId interfaceCvId = interfaceContractImportSlot == -1 ? m_contractStack.back().cvId : m_contractStack.back().importedCvIds[interfaceContractImportSlot];

	const rvm::DeployedContract* contract = m_pChainState->GetContractDeployed(rvm::ContractVersionId(cvId));
	if (contract == nullptr)
		return nullptr;
	const rvm::ContractModuleID* moduleId = &contract->Module;

	const ContractDatabaseEntry* pEntry = m_pDB->FindContractEntry(*moduleId);
	if (!pEntry)
		return nullptr;

	const rvm::DeployedContract* interfaceContract = m_pChainState->GetContractDeployed(interfaceCvId);
	if (interfaceContract == nullptr)
		return nullptr;
	const rvm::ContractModuleID* interfaceModuleId = &interfaceContract->Module;

	for (uint32_t i = 0; i < uint32_t(pEntry->compileData.implementedInterfaces.size()); i++)
	{
		const ContractImplementedInterface& implementedInterface = pEntry->compileData.implementedInterfaces[i];
		// compare slot index first because it's faster
		if (implementedInterface.interfaceDefSlot == interfaceSlot && memcmp(&implementedInterface.interfaceDefContractModuleId, interfaceModuleId, sizeof(rvm::ContractModuleID)) == 0)
			return &implementedInterface;
	}

	return nullptr;
}

uint64_t CRuntimeInterface::DeployCall(int64_t templateContractImportSlot, const void** ptrs, uint32_t numPtrs)
{
	static_assert((uint64_t)rvm::ContractVersionIdInvalid == 0, "rvm::::ContractVersionIdInvalid value changed, need to update deploy_call() in preda runtime");

	rvm::ContractVersionId stackTopCvId = m_contractStack.back().cvId;

	if (templateContractImportSlot < -1 || templateContractImportSlot >= int64_t(m_contractStack.back().numImportedContracts))
		return uint32_t(prlrt::ExecutionError::RuntimeException) | (uint32_t(prlrt::ExceptionType::CrossCallContractNotFound) << 8);

	rvm::ContractVersionId templateCvId = templateContractImportSlot == -1 ? m_contractStack.back().cvId : m_contractStack.back().importedCvIds[templateContractImportSlot];
	const rvm::DeployedContract* templateContract = m_pChainState->GetContractDeployed(templateCvId);
	if (!templateContract)
		return (uint64_t)rvm::ContractVersionIdInvalid;

	const rvm::ContractModuleID* pModuleId = &templateContract->Module;
	uint64_t dappname_i = templateContract->DAppName;
	if(templateCvId != stackTopCvId)
	{
		const rvm::DeployedContract* initiator = m_pChainState->GetContractDeployed(stackTopCvId);
		if(!initiator)
			return (uint64_t)rvm::ContractVersionIdInvalid;

		dappname_i = initiator->DAppName;
	}

	rvm::ContractVersionId newCvId = m_pExecutionContext->DeployUnnamedContract(stackTopCvId, dappname_i, templateContract);

	const ContractDatabaseEntry* pContractEntry = m_pDB->FindContractEntry(*pModuleId);
	if (!pContractEntry)
		return (uint64_t)rvm::ContractVersionIdInvalid;

	int32_t opCode = pContractEntry->compileData.globalDeployFunctionIdx;

	// deployed contract has no constructor
	static_assert(std::is_same<uint64_t, std::underlying_type_t<rvm::ContractId>>::value);
	if (opCode == -1)
		return (uint64_t)newCvId;

	if (uint32_t(opCode) >= uint32_t(pContractEntry->compileData.functions.size())
		|| (pContractEntry->compileData.functions[opCode].flags & uint32_t(transpiler::FunctionFlags::CallableFromSystem)) == 0)
		return (uint64_t)rvm::ContractVersionIdInvalid;

	// newly deployed contract should have the same stub as the template contract since it's just the imported contract ids
	PushContractStack(*pModuleId, newCvId, pContractEntry->compileData.functions[opCode].flags, (const rvm::ContractVersionId*)templateContract->Stub, templateContract->StubSize / sizeof(rvm::ContractVersionId));
	// no need to call SetExecutionContext() here, deploy call is only possible inside a transaction call, therefore execution context is already set

	// newly deployed contract should have the same stub as the template contract since it's just the imported contract ids
	ContractRuntimeInstance* pContractInstance = m_pExecutionEngine->CreateContractInstance(*pModuleId, newCvId, (const rvm::ContractVersionId*)templateContract->Stub, templateContract->StubSize / sizeof(rvm::ContractVersionId));
	if (pContractInstance == nullptr)
		return (uint64_t)rvm::ContractVersionIdInvalid;

	if (!m_pExecutionEngine->MapNeededContractContext(m_pExecutionContext, pContractInstance, pContractEntry->compileData.functions[opCode].flags))
		return (uint64_t)rvm::ContractVersionIdInvalid;

	uint32_t ret = pContractInstance->ContractCall(opCode, ptrs, numPtrs);

	PopContractStack();

	if (ExecutionResult(ret & 0xff) != ExecutionResult::NoError)
		return (uint64_t)rvm::ContractVersionIdInvalid;

	return (uint64_t)newCvId;
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
	bool res = m_pDB->VariableJsonify(m_contractStack.back().moduleId, type_export_name, serialized_data, serialized_data_size, outputStr, m_pChainState);
	assert(res);

	m_logOutputBuffer += outputStr;
}

void CRuntimeInterface::DebugPrintOutputBuffer(uint32_t line)
{
	rvm::ConstString s{ m_logOutputBuffer.c_str(), uint32_t(m_logOutputBuffer.size()) };

	m_pDB->m_pRuntimeAPI->DebugPrint(rvm::DebugMessageType::Informational, &s, m_pExecutionContext, m_pDB->GetContract(&m_contractStack.back().moduleId), line);
	m_logOutputBuffer.clear();
}

void CRuntimeInterface::DebugAssertionFailure(uint32_t line)
{
	std::string tmp = "Assertion failure on line " + std::to_string(line);
	rvm::ConstString s{ tmp.c_str(), uint32_t(tmp.size()) };
	m_pDB->m_pRuntimeAPI->DebugPrint(rvm::DebugMessageType::Warning, &s, m_pExecutionContext, m_pDB->GetContract(&m_contractStack.back().moduleId));
}

void CRuntimeInterface::DebugAssertionFailureMessage(uint32_t line, const char* message, uint32_t length)
{
	std::string tmp = "Assertion failure on line " + std::to_string(line) + ": " + std::string(message, length);
	rvm::ConstString s{ tmp.c_str(), uint32_t(tmp.size()) };
	m_pDB->m_pRuntimeAPI->DebugPrint(rvm::DebugMessageType::Warning, &s, m_pExecutionContext, m_pDB->GetContract(&m_contractStack.back().moduleId));
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
	return ((oxd::SecureAddress*)pAddress)->GetSecuritySuiteId() == oxd::SEC_SUITE_DELEGATED_DAPP;
}

bool CRuntimeInterface::IsAssetAddress(const void *pAddress)
{
	return ((oxd::SecureAddress*)pAddress)->GetSecuritySuiteId() == oxd::SEC_SUITE_DELEGATED_TOKEN;
}

bool CRuntimeInterface::IsNameAddress(const void *pAddress)
{
	return ((oxd::SecureAddress*)pAddress)->GetSecuritySuiteId() == oxd::SEC_SUITE_DELEGATED_NAME;
}

bool CRuntimeInterface::IsContractAddress(const void* pAddress)
{
	return ((oxd::SecureAddress*)pAddress)->GetSecuritySuiteId() == oxd::SEC_SUITE_CONTRACT;
}

bool CRuntimeInterface::IsCustomAddress(const void* pAddress)
{
	return ((oxd::SecureAddress*)pAddress)->GetSecuritySuiteId() == oxd::SEC_SUITE_DELEGATED_HASH;
}

void CRuntimeInterface::SetAsCustomAddress(void* pAddress, const uint8_t* data)
{
	((oxd::SecureAddress*)pAddress)->SetDelegatedAsHash(data);
}

void CRuntimeInterface::SetAsContractAddress(void* pAddress, uint64_t contract_id)
{
	((oxd::SecureAddress*)pAddress)->SetAsContract(contract_id);
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
void CRuntimeInterface::ConvertToString_##_SIZE(const ::prlrt::PrecisionFloatInternal<_SIZE>* pftemp, char* buf){\
	static_assert(sizeof(std::remove_pointer_t<decltype(pftemp)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	_FLOAT_TYPE* pfloat = (_FLOAT_TYPE*)pftemp;\
	std::string float_literal = pfloat->ToString();\
	memcpy(buf, float_literal.data(), float_literal.length());\
}\
uint32_t CRuntimeInterface::GetConvertToStringLen_##_SIZE(const ::prlrt::PrecisionFloatInternal<_SIZE>* pftemp){\
	static_assert(sizeof(std::remove_pointer_t<decltype(pftemp)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	_FLOAT_TYPE* pfloat = (_FLOAT_TYPE*)pftemp;\
	return (uint32_t)pfloat->ToString().length();\
}\
void CRuntimeInterface::ConvertFromString_##_SIZE(::prlrt::PrecisionFloatInternal<_SIZE>* pftemp, const char* float_literal){\
	static_assert(sizeof(std::remove_pointer_t<decltype(pftemp)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	_FLOAT_TYPE pfloat(float_literal);\
	*pftemp = *((::prlrt::PrecisionFloatInternal<_SIZE>*)&pfloat);\
}\
void CRuntimeInterface::Float_Add_##_SIZE(const ::prlrt::PrecisionFloatInternal<_SIZE>* a, const ::prlrt::PrecisionFloatInternal<_SIZE>* b, ::prlrt::PrecisionFloatInternal<_SIZE>* result){\
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	static_assert(sizeof(std::remove_pointer_t<decltype(b)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	memcpy(result->_Data, a->_Data, sizeof(result->_Data)/sizeof(uint8_t));\
	((_FLOAT_TYPE*)result)->Add(*((_FLOAT_TYPE*)b));\
}\
void CRuntimeInterface::Float_Sub_##_SIZE(const ::prlrt::PrecisionFloatInternal<_SIZE>* a, const ::prlrt::PrecisionFloatInternal<_SIZE>* b, ::prlrt::PrecisionFloatInternal<_SIZE>* result){\
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	static_assert(sizeof(std::remove_pointer_t<decltype(b)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	memcpy(result->_Data, a->_Data, sizeof(result->_Data)/sizeof(uint8_t));\
	((_FLOAT_TYPE*)result)->Sub(*((_FLOAT_TYPE*)b));\
}\
void CRuntimeInterface::Float_Mul_##_SIZE(const ::prlrt::PrecisionFloatInternal<_SIZE>* a, const ::prlrt::PrecisionFloatInternal<_SIZE>* b, ::prlrt::PrecisionFloatInternal<_SIZE>* result){\
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	static_assert(sizeof(std::remove_pointer_t<decltype(b)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	memcpy(result->_Data, a->_Data, sizeof(result->_Data)/sizeof(uint8_t));\
	((_FLOAT_TYPE*)result)->Mul(*((_FLOAT_TYPE*)b));\
}\
void CRuntimeInterface::Float_Div_##_SIZE(const ::prlrt::PrecisionFloatInternal<_SIZE>* a, const ::prlrt::PrecisionFloatInternal<_SIZE>* b, ::prlrt::PrecisionFloatInternal<_SIZE>* result){\
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	static_assert(sizeof(std::remove_pointer_t<decltype(b)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	memcpy(result->_Data, a->_Data, sizeof(result->_Data)/sizeof(uint8_t));\
	((_FLOAT_TYPE*)result)->Div(*((_FLOAT_TYPE*)b));\
}\
void CRuntimeInterface::Float_Zero_##_SIZE(::prlrt::PrecisionFloatInternal<_SIZE>* a){\
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	_FLOAT_TYPE pfloat(0);\
	*a = *((::prlrt::PrecisionFloatInternal<_SIZE>*)&pfloat);\
}\
bool CRuntimeInterface::Float_IsZero_##_SIZE(const ::prlrt::PrecisionFloatInternal<_SIZE>* a){\
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	_FLOAT_TYPE* pfloat_a = (_FLOAT_TYPE*)a;\
	double result;\
	pfloat_a->ToNumber(result);\
	return result == 0.0;\
}\
void CRuntimeInterface::Float_Negate_##_SIZE(const ::prlrt::PrecisionFloatInternal<_SIZE>* a, ::prlrt::PrecisionFloatInternal<_SIZE>* result)\
{\
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_FLOAT_TYPE), "Size of Precision Float inconsistent");\
	memcpy(result->_Data, a->_Data, sizeof(result->_Data)/sizeof(uint8_t));\
	_FLOAT_TYPE pfloat_b(-1);\
	((_FLOAT_TYPE*)result)->Mul(pfloat_b);\
}\
int CRuntimeInterface::Float_Compare_##_SIZE(const ::prlrt::PrecisionFloatInternal<_SIZE>* a, const ::prlrt::PrecisionFloatInternal<_SIZE>* b)\
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
void CRuntimeInterface::LongInt_Negate_##_SIZE(const ::prlrt::LongIntInternal<_SIZE>* a, ::prlrt::LongIntInternal<_SIZE>* result){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(LongInt_##_SIZE), "Size of DataType inconsistent"); \
	memcpy(result->_Data, a->_Data, sizeof(result->_Data)/sizeof(uint8_t)); \
	((LongInt_##_SIZE*)result)->ChangeSign(); } \
bool CRuntimeInterface::LongInt_IsSign_##_SIZE(const ::prlrt::LongIntInternal<_SIZE>* a){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(LongInt_##_SIZE), "Size of DataType inconsistent"); \
	return ((LongInt_##_SIZE*)a)->IsSign(); }
#define LONGINTIMPLFUNC(_SIZE, _INT_TYPE) \
void CRuntimeInterface::_INT_TYPE##_Zero_##_SIZE(::prlrt::LongIntInternal<_SIZE>* a){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(LongInt_##_SIZE), "Size of DataType inconsistent"); \
	_INT_TYPE##_##_SIZE b(0); \
	*a = *((::prlrt::LongIntInternal<_SIZE>*)&b); } \
void CRuntimeInterface::_INT_TYPE##_fromInt_##_SIZE(::prlrt::LongIntInternal<_SIZE>* a, int64_t in){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(LongInt_##_SIZE), "Size of DataType inconsistent"); \
	((_INT_TYPE##_##_SIZE*)a)->FromInt((ttmath::sint)in); } \
void CRuntimeInterface::_INT_TYPE##_fromUInt_##_SIZE(::prlrt::LongIntInternal<_SIZE>* a, uint64_t in){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(LongInt_##_SIZE), "Size of DataType inconsistent"); \
	((_INT_TYPE##_##_SIZE*)a)->FromInt((ttmath::uint)in); } \
int CRuntimeInterface::_INT_TYPE##_toInt64_##_SIZE(const ::prlrt::LongIntInternal<_SIZE>* a, int64_t* result){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(LongInt_##_SIZE), "Size of DataType inconsistent"); \
	return ((_INT_TYPE##_##_SIZE*)a)->ToInt(*(ttmath::sint*)result); } \
int CRuntimeInterface::_INT_TYPE##_toUInt64_##_SIZE(const ::prlrt::LongIntInternal<_SIZE>* a, uint64_t* result){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(LongInt_##_SIZE), "Size of DataType inconsistent"); \
	return ((_INT_TYPE##_##_SIZE*)a)->ToUInt(*(ttmath::uint*)result); } \
void CRuntimeInterface::_INT_TYPE##_rightShift_##_SIZE(::prlrt::LongIntInternal<_SIZE>* a, int64_t shift){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(LongInt_##_SIZE), "Size of DataType inconsistent"); \
	*((_INT_TYPE##_##_SIZE*)a) >>= shift; } \
void CRuntimeInterface::_INT_TYPE##_leftShift_##_SIZE(::prlrt::LongIntInternal<_SIZE>* a, int64_t shift){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(LongInt_##_SIZE), "Size of DataType inconsistent"); \
	*((_INT_TYPE##_##_SIZE*)a) <<= shift; } \
void CRuntimeInterface::_INT_TYPE##_ConvertFromString_##_SIZE(::prlrt::LongIntInternal<_SIZE>* a, const char* longint_literal){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(LongInt_##_SIZE), "Size of DataType inconsistent"); \
	_INT_TYPE##_##_SIZE b(longint_literal); \
	*a = *((::prlrt::LongIntInternal<_SIZE>*)&b); } \
void CRuntimeInterface::_INT_TYPE##_ConvertFromHexString_##_SIZE(::prlrt::LongIntInternal<_SIZE>* a, const char* longint_literal){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	_INT_TYPE##_##_SIZE b; \
	b.FromString(longint_literal, 16); \
	*a = *((::prlrt::LongIntInternal<_SIZE>*)&b); } \
void CRuntimeInterface::_INT_TYPE##_ConvertToString_##_SIZE(const ::prlrt::LongIntInternal<_SIZE>* a, char* buf){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	std::string result; \
	((_INT_TYPE##_##_SIZE*)a)->ToString(result); \
	memcpy(buf, result.data(), result.length()); } \
uint32_t CRuntimeInterface::_INT_TYPE##_GetConvertToStringLen_##_SIZE(const ::prlrt::LongIntInternal<_SIZE>* a){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	return uint32_t(((_INT_TYPE##_##_SIZE*)a)->ToString().length()); } \
bool CRuntimeInterface::_INT_TYPE##_IsZero_##_SIZE(const ::prlrt::LongIntInternal<_SIZE>* a) { \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	return ((_INT_TYPE##_##_SIZE*)a)->IsZero(); } \
void CRuntimeInterface::_INT_TYPE##_Add_##_SIZE(const ::prlrt::LongIntInternal<_SIZE>* a, const ::prlrt::LongIntInternal<_SIZE>* b, ::prlrt::LongIntInternal<_SIZE>* result){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	static_assert(sizeof(std::remove_pointer_t<decltype(b)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	memcpy(result->_Data, a->_Data, sizeof(result->_Data)/sizeof(uint8_t)); \
	((_INT_TYPE##_##_SIZE*)result)->Add(*((_INT_TYPE##_##_SIZE*)b)); } \
void CRuntimeInterface::_INT_TYPE##_Sub_##_SIZE(const ::prlrt::LongIntInternal<_SIZE>* a, const ::prlrt::LongIntInternal<_SIZE>* b, ::prlrt::LongIntInternal<_SIZE>* result){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	static_assert(sizeof(std::remove_pointer_t<decltype(b)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	memcpy(result->_Data, a->_Data, sizeof(result->_Data)/sizeof(uint8_t)); \
	((_INT_TYPE##_##_SIZE*)result)->Sub(*((_INT_TYPE##_##_SIZE*)b)); } \
void CRuntimeInterface::_INT_TYPE##_Mul_##_SIZE(const ::prlrt::LongIntInternal<_SIZE>* a, const ::prlrt::LongIntInternal<_SIZE>* b, ::prlrt::LongIntInternal<_SIZE>* result){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	static_assert(sizeof(std::remove_pointer_t<decltype(b)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	memcpy(result->_Data, a->_Data, sizeof(result->_Data)/sizeof(uint8_t)); \
	((_INT_TYPE##_##_SIZE*)result)->Mul(*((_INT_TYPE##_##_SIZE*)b)); } \
void CRuntimeInterface::_INT_TYPE##_Div_##_SIZE(const ::prlrt::LongIntInternal<_SIZE>* a, const ::prlrt::LongIntInternal<_SIZE>* b, ::prlrt::LongIntInternal<_SIZE>* result){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	static_assert(sizeof(std::remove_pointer_t<decltype(b)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	memcpy(result->_Data, a->_Data, sizeof(result->_Data)/sizeof(uint8_t)); \
	((_INT_TYPE##_##_SIZE*)result)->Div(*((_INT_TYPE##_##_SIZE*)b)); } \
void CRuntimeInterface::_INT_TYPE##_Mod_##_SIZE(const ::prlrt::LongIntInternal<_SIZE>* a, const ::prlrt::LongIntInternal<_SIZE>* b, ::prlrt::LongIntInternal<_SIZE>* result){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	static_assert(sizeof(std::remove_pointer_t<decltype(b)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	_INT_TYPE##_##_SIZE remainder = (*(_INT_TYPE##_##_SIZE*)a) % (*((_INT_TYPE##_##_SIZE*)b)); \
	memcpy(result->_Data, &remainder, sizeof(result->_Data)/sizeof(uint8_t)); } \
int CRuntimeInterface::_INT_TYPE##_Compare_##_SIZE(const ::prlrt::LongIntInternal<_SIZE>* a, const ::prlrt::LongIntInternal<_SIZE>* b){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	static_assert(sizeof(std::remove_pointer_t<decltype(b)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	_INT_TYPE##_##_SIZE* a_math = (_INT_TYPE##_##_SIZE*)a; \
	_INT_TYPE##_##_SIZE* b_math = (_INT_TYPE##_##_SIZE*)b; \
	if(*a_math > *b_math) return 1; \
	else if(*a_math < *b_math) return -1; \
	return 0;} \
void CRuntimeInterface::_INT_TYPE##_SetMax_##_SIZE(::prlrt::LongIntInternal<_SIZE>* a){ \
	static_assert(sizeof(std::remove_pointer_t<decltype(a)>) == sizeof(_INT_TYPE##_##_SIZE), "Size of DataType inconsistent"); \
	((_INT_TYPE##_##_SIZE*)a)->SetMax(); } \
void CRuntimeInterface::_INT_TYPE##_SetMin_##_SIZE(::prlrt::LongIntInternal<_SIZE>* a){ \
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
	if (rvm::CONTRACT_SCOPE(m_pExecutionContext->GetContractId()) == rvm::Scope::Address)
		*(rvm::Address*)out = *(rvm::Address*)m_pExecutionContext->GetScopeTarget().Data;

}

void CRuntimeInterface::Transaction_GetSender(uint8_t* out)
{
	// only if scope is address
	if (m_contractStack.size() > 1)
		((oxd::SecureAddress*)out)->SetAsContract(uint64_t(m_contractStack[m_contractStack.size() - 2].cvId));
	else
	{
		rvm::ConstAddress* initiator = m_pExecutionContext->GetInitiator();
		if (initiator != nullptr)
		{
			*(rvm::Address*)out = *initiator;
		}
		else
			((oxd::SecureAddress*)out)->Zero();
	}
}

uint64_t CRuntimeInterface::Transaction_GetTimeStamp()
{
	return m_pExecutionContext->GetTimestamp();
}

void CRuntimeInterface::Transaction_GetSigner(uint32_t signerIdx, uint8_t* out)
{
	rvm::ConstAddress* signer = m_pExecutionContext->GetSigner(signerIdx);
	if (signer)
		*(rvm::Address*)out = *signer;
	else
		((oxd::SecureAddress*)out)->Zero();
}

const uint32_t CRuntimeInterface::Transaction_GetSignerCount()
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
