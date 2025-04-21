#pragma once
#define ENABLE_EVM
#ifdef ENABLE_EVM

#include <vector>
#include <map>
#ifdef _WIN32
	#pragma warning(push)
	#pragma warning(disable:4068 4819)
#endif
#include <evmc/evmc.hpp>
#ifdef _WIN32
	#pragma warning(pop)
#endif
#include "../../../native/abi/vm_types.h"
#include "../../../native/abi/vm_interfaces.h"
#include "../preda_engine/ContractData.h"
#include "../../../3rdParty/nlohmann/json.hpp"

namespace xtl {
	constexpr rvm::ContractId EVM_BASE_CID = rvm::CONTRACT_ID_MAKE(0, (rvm::DAppId)0xafffffff, rvm::EngineId::SOLIDITY_EVM);

	struct ContractVariable
	{
		std::string type;
		std::string name;
		uint16_t scope;
		uint16_t slot_id;
		uint32_t offset;
		uint32_t number_of_bytes;
		std::vector<ContractVariable> members;
	};

	struct ContractFunction
	{
		std::string name;
		std::string returnType;
		std::vector<std::pair<std::string, std::string>> parameters;				// <type, name>
		std::string signatureHash;
	};

	struct ContractEvent
	{
		std::string name;
		std::vector<std::pair<std::string, std::string>> parameters;				// <type, name>
		evmc::bytes32 signatureHash;
	};

	struct ContractCompileData
	{
		std::string dapp;
		std::string name;
		rvm::HashValue intermediateHash;
		std::vector<ContractVariable> storage_variables;							// currently stores variables of type except mapping and array
		std::vector<ContractFunction> functions;
		std::vector<ContractEvent> events;
	};

	struct ContractDeployData
	{
		rvm::ContractId contractId;
	};

	class ContractDelegate : public rvm::Contract {
	private:
		ContractCompileData* m_compile_data;
		ContractDeployData* m_deploy_data;
		rt::String m_name;
		rt::String m_fullname;
		rvm::HashValue m_hash;
	public:
		ContractDelegate(ContractCompileData* compile_data, ContractDeployData* deploy_data);
		// from rvm::Interface
		virtual rvm::ConstString				GetName() const override;
		virtual rvm::ConstString				GetFullName() const override;
		virtual uint32_t 						GetFunctionCount() const override;
		virtual rvm::ConstString 				GetFunctionName(uint32_t idx) const override;
		virtual rvm::FunctionFlag 				GetFunctionFlag(uint32_t idx) const override;
		virtual rvm::Scope 						GetFunctionScope(uint32_t idx) const override;
		virtual rvm::OpCode 					GetFunctionOpCode(uint32_t idx) const override;
		virtual bool 							GetFunctionSignature(uint32_t idx, rvm::StringStream* signature_out) const override;
		// from rvm::Contract
		virtual rvm::ContractFlag			 	GetFlag() const override;
		virtual const rvm::ContractModuleID* 	GetModuleID() const override;
		virtual uint32_t						GetInterfaceImplementedCount() const override;
		virtual const rvm::Interface*			GetInterfaceImplemented(uint32_t idx) const override;
		virtual rvm::OpCode						GetInterfaceImplementedOpCode(uint32_t idx, rvm::OpCode code) const override;  // convert opcode in Interface to opcode in Contract
		virtual uint32_t						GetInterfaceCount() const override;
		virtual const rvm::Interface* 			GetInterface(uint32_t idx) const override;
		virtual rvm::InterfaceSlot				GetInterfaceSlot(uint32_t idx) const override;
		virtual uint32_t						GetScopeCount() const override;
		virtual rvm::Scope						GetScope(uint32_t idx) const override;
		virtual rvm::ScopeFlag					GetScopeFlag(uint32_t idx) const override;
		virtual rvm::ConstString				GetScopeName(uint32_t idx) const override;
		virtual bool 							GetStateSignature(rvm::Scope scope, rvm::StringStream* signature_out) const override;
		virtual uint32_t						GetEnumCount() const override;
		virtual rvm::ConstString				GetEnumName(uint32_t idx) const override;
		virtual bool							GetEnumSignature(uint32_t idx, rvm::StringStream* signature_out) const override;
		virtual uint32_t						GetStructCount() const override;
		virtual rvm::ConstString				GetStructName(uint32_t idx) const override;
		virtual bool							GetStructSignature(uint32_t idx, rvm::StringStream* signature_out) const override;
		virtual void 							GetSystemFunctionOpCodes(rvm::SystemFunctionOpCodes* out) const override;
	};

	struct ContractDatabaseEntry
	{
		uint32_t deploy_sn;
		evmc::address address;
		ContractCompileData compileData;
		ContractDeployData deployData;

		std::shared_ptr<ContractDelegate> delegate;

		ContractDelegate* GetDelegate()
		{
			if (!delegate)
			{
				delegate = std::make_shared<ContractDelegate>(&compileData, &deployData);
			}
			return delegate.get();
		}
		int EncodeJsonFunctionArguments(std::string_view args_json, std::vector<uint8_t>& out) const;
		int DecodeEventArguments(evmc::bytes32 event_sig, evmc::bytes_view bytes, std::string& out) const;
		int ShardStateJsonify(bool b_global, const rvm::ChainStates* p_chain_state, nlohmann::json& out) const;
		int AddressStateJsonify(const rvm::Address& addr, const rvm::ChainStates* p_chain_state, nlohmann::json& out) const;
		//int Uint32StateJsonify(uint32_t scope_key, const rvm::ConstData* contract_state, nlohmann::json& out) const;
	};


	class CompiledModules : public rvm::CompiledModules {
		rt::String m_dAppName;
		std::vector<ContractCompileData> m_contracts;
		std::vector<ContractDelegate> m_delegates;
		std::vector<rt::String> m_bytecode;
		bool m_linked = false;
	public:
		CompiledModules(const char* dapp_name);
		const ContractCompileData* GetCompiledData(uint32_t contractIdx) const;
		void AddContract(ContractCompileData compile_data, rt::String bytecode);
		rt::String_Ref GetBytecode(uint32_t idx);
		void LinkContract();

		// from rvm::CompiledModules
		rvm::EngineId 			GetEngineId() const override;
		rvm::ConstString 		GetDAppName() const override;
		uint32_t 				GetCount() const override;
		const rvm::Contract* 	GetContract(uint32_t idx) const override;
		rvm::ConstString 		GetExternalDependencies() const override;
		virtual bool 			ValidateDependency(const rvm::GlobalStates* chain_state) const override {return false;}
		virtual rvm::ConstData 	GetDependencyData() const override { return rvm::ConstData(); }
		bool 					IsLinked() const override;
		void 					Release() override;
	};

namespace _details 
{
	constexpr evmc::address RVMAddressToEVMAddress(rvm::ConstAddress& addr)
	{
		evmc::address ret;
		static_assert(sizeof(addr._) >= sizeof(ret));
		for (size_t i = 0; i < sizeof(ret); i++)
		{
			ret.bytes[i] = addr._[i];
		}
		return ret;
	}

	constexpr rvm::ContractId RvmCDIDToEVMCID(const rvm::ContractModuleID* rvmCDId)
	{
		return rvmCDId ? *(rvm::ContractId*)rvmCDId : rvm::ContractIdInvalid;
	}
	constexpr void EVMCIDToRvmCDID(rvm::ContractId evmCId, rvm::ContractModuleID* rvmCDId)
	{
		if (rvmCDId)
		{
			rt::Zero(*rvmCDId);
			*(rvm::ContractId*)rvmCDId = evmCId;
		}
	}
}
}


#endif