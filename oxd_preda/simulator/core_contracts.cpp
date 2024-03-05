#include "core_contracts.h"
#include "simu_global.h"


namespace oxd
{

void CoreEngine::InitContractsDatabase(ContractsDatabase& x)
{
	x._ContractEngine["core"] = rvm::EngineId::Core;

#define DEF_CORE_CONTRACT(ciid, name, sn, type)							\
		x._Contracts[name] = ~ciid;										\
		x._ContractBuildNumLatest[-~ciid] = rvm::CONTRACT_BUILD(ciid);	\

ALL_CORE_CONTRACTS
#undef DEF_CORE_CONTRACT

}

bool CoreEngine::StateJsonify(rvm::ContractInvokeId contract, const rvm::ConstData* contract_state, rvm::StringStream* json_out) const
{
	thread_local rt::Json json;

#define DEF_CORE_CONTRACT(ciid, name, sn, type)							\
	case ciid: {														\
			typedef rvm::TypeTraits<type> TTS;							\
			auto& x = *(type*)contract_state->DataPtr;					\
			if(TTS::GetEmbeddedSize(x) == contract_state->DataSize) {	\
				TTS::Jsonify(x, json.Empty());							\
				auto& s = json.GetInternalString();						\
				json_out->Append(s, (uint32_t)s.GetLength());			\
				return true;											\
			}															\
		}	break;														\

	switch (contract)
	{
	ALL_CORE_CONTRACTS
	}
#undef DEF_CORE_CONTRACT

	return false;
}

bool CoreEngine::StateJsonParse(rvm::ContractInvokeId contract, const rvm::ConstString* json, rvm::DataBuffer* state_out, rvm::LogMessageOutput* error_out) const
{
#define DEF_CORE_CONTRACT(ciid, name, sn, type)					\
	case ciid: {												\
			typedef rvm::TypeTraits<type> TTS;					\
			TTS::Mutable w;										\
			if(TTS::JsonParse(w, json->Str())) {				\
				uint32_t size = TTS::GetEmbeddedSize(w);		\
				auto* p = VERIFY(state_out->SetSize(size));		\
				return TTS::Embed(p, w) == size;				\
			}													\
		}	break;												\

	switch (contract)
	{
	ALL_CORE_CONTRACTS
	}
#undef DEF_CORE_CONTRACT

	return false;
}

namespace _details
{
using namespace rvm;

struct CoreContract: public Contract
{
	ContractVersionId	CoreId;
	rt::String			FullName;

	CoreContract(const rt::String_Ref& name, ContractVersionId cvid):FullName(name), CoreId(cvid){}
	virtual ConstString				GetName() const { return { FullName.Begin() + 5, (uint32_t)FullName.GetLength() - 5 }; }
	virtual ConstString				GetFullName() const { return { FullName.Begin(), (uint32_t)FullName.GetLength() }; }

	virtual uint32_t				GetFunctionCount() const { return 0; }
	virtual ConstString				GetFunctionName(uint32_t idx) const { return { nullptr, 0 }; }
	virtual FunctionFlag			GetFunctionFlag(uint32_t idx) const { return (FunctionFlag)0; }
	virtual Scope					GetFunctionScope(uint32_t idx) const { return ScopeInvalid; }
	virtual OpCode					GetFunctionOpCode(uint32_t idx) const { return OpCodeInvalid; }
	virtual bool					GetFunctionSignature(uint32_t idx, StringStream* signature_out) const { return false; }

	virtual ContractFlag			GetFlag() const { return (ContractFlag)0; }
	virtual const ContractModuleID* GetModuleID() const { return nullptr; }
	virtual uint32_t				GetInterfaceImplementedCount() const { return 0; };
	virtual const Interface*		GetInterfaceImplemented(uint32_t idx) const { return nullptr; }
	virtual OpCode					GetInterfaceImplementedOpCode(uint32_t idx, OpCode code) const { return (OpCode)0; }
	virtual uint32_t				GetInterfaceCount() const { return 0; }
	virtual const Interface*		GetInterface(uint32_t idx) const { return nullptr; }
	virtual InterfaceSlot			GetInterfaceSlot(uint32_t idx) const { return InterfaceSlotInvalid; }
	virtual uint32_t				GetScopeCount() const { return 0; }
	virtual Scope					GetScope(uint32_t idx) const { return ScopeInvalid; }
	virtual ConstString				GetScopeName(uint32_t idx) const { return { nullptr, 0 }; }
	virtual ScopeFlag				GetScopeFlag(uint32_t idx) const { return (ScopeFlag)0; }
	virtual bool					GetStateSignature(Scope scope, StringStream* signature_out) const { return false; }
	virtual uint32_t				GetEnumCount() const { return 0; }
	virtual ConstString				GetEnumName(uint32_t idx) const { return { nullptr, 0 }; }
	virtual bool					GetEnumSignature(uint32_t idx, StringStream* signature_out) const { return false; }
	virtual uint32_t				GetStructCount() const { return 0; }
	virtual ConstString				GetStructName(uint32_t idx) const { return { nullptr, 0 }; }
	virtual bool					GetStructSignature(uint32_t idx, StringStream* signature_out) const { return false; }
	virtual void					GetSystemFunctionOpCodes(SystemFunctionOpCodes* out) const {}
};
} // namespace _details

#define DEF_CORE_CONTRACT(ciid, name, sn, type)						\
		static const _details::CoreContract	cc_##ciid(name, ~ciid);	\

ALL_CORE_CONTRACTS
#undef DEF_CORE_CONTRACT

const rvm::Contract* CoreEngine::GetContract(rvm::ContractVersionId cvid) const
{
#define DEF_CORE_CONTRACT(ciid, name, sn, type)		\
		case ~ciid: return &cc_##ciid;				\

	switch(cvid)
	{
	ALL_CORE_CONTRACTS
	}
#undef DEF_CORE_CONTRACT

	return nullptr;
}

} // namespace oxd