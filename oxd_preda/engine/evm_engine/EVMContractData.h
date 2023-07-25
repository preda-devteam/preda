#pragma once
//#define ENABLE_EVM
#ifdef ENABLE_EVM

#include <vector>
#include <map>


#include "evm_abi/ABIEncode.h"
#include "../../../native/abi/vm_types.h"
#include "../../../native/abi/vm_interfaces.h"
#include "../preda_engine/ContractData.h"

namespace preda_evm {
	constexpr rvm::ContractId EVM_CID = rvm::_details::CONTRACT_ID_MAKE(0, (rvm::DAppId)0xafffffff, rvm::EngineId::SOLIDITY_EVM);

	using ContractModuleID = uint64_t;

	struct ContractCompileData
	{
		std::string dapp;
		std::string name;
		rvm::HashValue intermediateHash;
		std::map<std::string, std::vector<ContractFunction>> m_functions;
		void AddFunction(const ContractFunction& funcInfo);
		bool ComposeInputData(const rt::JsonObject& args_json, uint64_t& value, std::string& data) const;
	};

	struct ContractLinkData
	{
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

		virtual rvm::ConstString		GetName() const override;
		virtual rvm::ConstString		GetFullName() const override;
		virtual rvm::ContractFlag		GetFlag() const override;

		virtual const rvm::ContractModuleID* GetModuleID() const override;

		virtual uint32_t				GetInterfaceImplementedCount() const override;
		virtual const rvm::Interface*	GetInterfaceImplemented(uint32_t idx) const override;
		virtual rvm::OpCode				GetInterfaceImplementedOpCode(uint32_t idx, rvm::OpCode code) const override;  // convert opcode in Interface to opcode in Contract
		virtual uint32_t				GetScopeCount() const override;
		virtual rvm::Scope				GetScope(uint32_t idx) const override;
		virtual rvm::ScopeFlag		GetScopeFlag(uint32_t idx) const override;
		virtual rvm::ConstString			GetScopeName(uint32_t idx) const override;
		virtual bool 					GetStateSignature(rvm::Scope scope, rvm::StringStream* signature_out) const override;

		virtual uint32_t				GetInterfaceCount() const override;
		virtual const rvm::Interface* 			GetInterface(uint32_t idx) const override;
		virtual rvm::InterfaceSlot			GetInterfaceSlot(uint32_t idx) const override;

		virtual uint32_t				GetEnumCount() const override;
		virtual rvm::ConstString			GetEnumName(uint32_t idx) const override;
		virtual bool					GetEnumSignature(uint32_t idx, rvm::StringStream* signature_out) const override;

		virtual uint32_t				GetStructCount() const override;
		virtual rvm::ConstString			GetStructName(uint32_t idx) const override;
		virtual bool					GetStructSignature(uint32_t idx, rvm::StringStream* signature_out) const override;

		virtual uint32_t GetFunctionCount() const override;
		virtual rvm::ConstString GetFunctionName(uint32_t idx) const override;
		virtual rvm::FunctionFlag GetFunctionFlag(uint32_t idx) const override;
		virtual rvm::Scope GetFunctionScope(uint32_t idx) const override;
		virtual bool GetFunctionSignature(uint32_t idx, rvm::StringStream* signature_out) const override;
		virtual rvm::OpCode GetFunctionOpCode(uint32_t idx) const override;

		virtual void GetSystemFunctionOpCodes(rvm::SystemFunctionOpCodes* out) const override;
	};

	struct ContractDatabaseEntry
	{
		ContractModuleID deployId;
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
	};


	class CompiledModules : public rvm::CompiledModules {
		rt::String m_dAppName;
		std::vector<ContractCompileData> m_contracts;
		std::vector<ContractDelegate> m_delegates;
		std::vector<ContractLinkData> m_linkdata;
		std::vector<rt::String> m_bytecode;
		std::vector<rt::String> m_initdata;
	public:
		CompiledModules(const char* dapp_name);

		const ContractCompileData* GetCompiledData(uint32_t contractIdx) const;
		void AddContract(ContractCompileData compile_data, rt::String bytecode, rt::String init_data);
		const rt::String_Ref GetBytecode(uint32_t idx);
		const rt::String_Ref GetInitData(uint32_t idx);
		void AttachLinkData(std::vector<ContractLinkData> linkdata);
		rvm::EngineId GetEngineId() const override;
		rvm::ConstString GetDAppName() const override;
		uint32_t GetCount() const override;
		const rvm::Contract* GetContract(uint32_t idx) const override;
		rvm::ConstString GetExternalDependencies() const override;
		bool IsLinked() const override;
		void Release() override;
	};

	namespace _details {
		inline constexpr evmc::address RVMAddressToEVMAddress(rvm::ConstAddress& addr)
		{
			evmc::address ret;
			static_assert(sizeof(addr._) >= sizeof(ret));
			for (size_t i = 0; i < sizeof(ret); i++)
			{
				ret.bytes[i] = addr._[i];
			}
			return ret;
		}

		static const ContractModuleID ContractDIDInvalid = (ContractModuleID)0;
		inline constexpr ContractModuleID RvmCDIDToEVMCDID(const rvm::ContractModuleID* rvmCDId)
		{
			return rvmCDId ? *(ContractModuleID*)rvmCDId : ContractDIDInvalid;
		}
		inline constexpr void EVMCDIDToRvmCDID(ContractModuleID evmCDId, rvm::ContractModuleID* rvmCDId)
		{
			if (rvmCDId)
			{
				rt::Zero(*rvmCDId);
				*(ContractModuleID*)rvmCDId = evmCDId;
			}
		}
		// returns rvm::contractIdInvalid if not found
		static rvm::ContractId GetOnChainContractIdFromContractFullName(const rvm::ChainStates* pChainState, const std::string& fullName)
		{
			std::string::size_type dotPos = fullName.find('.');
			if (dotPos != std::string::npos)
			{
				rvm::ConstString dappName = { fullName.c_str(), uint32_t(dotPos) };
				rvm::DAppId dAppId = pChainState->GetDAppByName(&dappName);
				if (dAppId != rvm::DAppIdInvalid)
				{
					rvm::ConstString contractName = { fullName.c_str() + dotPos + 1, uint32_t(fullName.size() - dotPos - 1) };
					return pChainState->GetContractByName(dAppId, &contractName);
				}
			}

			return rvm::ContractIdInvalid;
		}

		static const ContractModuleID GetOnChainContractModuleIdFromFullName(const rvm::ChainStates* pChainState, const std::string& fullName, rvm::BuildNum buildNum = rvm::BuildNumLatest)
		{
			rvm::ContractId contractId = GetOnChainContractIdFromContractFullName(pChainState, fullName);
			return RvmCDIDToEVMCDID(pChainState->GetContractModule(contractId, buildNum));
		}
	}
}


#endif