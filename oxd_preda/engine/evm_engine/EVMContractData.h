#pragma once

#include <vector>
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


namespace preda_evm {
	constexpr rvm::ContractId EVM_CID = rvm::_details::CONTRACT_ID_MAKE(0, (rvm::DAppId)0xafffffff, rvm::EngineId::SOLIDITY_EVM);

	using ContractDID = uint64_t;

	struct ContractCompileData
	{
		std::string dapp;
		std::string name;
		rvm::HashValue intermediateHash;
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
		rt::String		m_name;
		rvm::HashValue  m_hash;
	public:
		ContractDelegate(ContractCompileData* compile_data, ContractDeployData* deploy_data);

		virtual rvm::ConstString		GetName() const override;
		virtual rvm::ContractFlag		GetFlag() const override;

		virtual const rvm::HashValue* GetIntermediateRepresentationHash() const override;

		virtual uint32_t				GetInterfaceImplemented(rvm::InterfaceId* pIID_out, uint32_t OutBufSize) const override;
		virtual rvm::OpCode				GetInterfaceImplementedOpCode(rvm::InterfaceId i, rvm::OpCode code) const override;
		virtual uint32_t				GetScopeCount() const override;
		virtual rvm::Scope				GetScope(uint32_t idx) const override;
		virtual rvm::ScopeDefinitionFlag		GetScopeFlag(uint32_t idx) const override;
		virtual rvm::ConstString			GetScopeName(uint32_t idx) const override;
		virtual rvm::ContractScopeId			GetScopeDefinition(uint32_t idx) const override;
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
		ContractDID deployId;
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


	class CompiledContracts : public rvm::CompiledContracts {
		rt::String m_dAppName;
		std::vector<ContractCompileData> m_contracts;
		std::vector<ContractDelegate> m_delegates;
		std::vector<ContractLinkData> m_linkdata;
		std::vector<rt::String> m_bytecode;
		std::vector<rt::String> m_initdata;
	public:
		CompiledContracts(const char* dapp_name);

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

		static const ContractDID ContractDIDInvalid = (ContractDID)0;
		inline constexpr ContractDID RvmCDIDToEVMCDID(const rvm::ContractDID* rvmCDId)
		{
			return rvmCDId ? *(ContractDID*)rvmCDId : ContractDIDInvalid;
		}
		inline constexpr void EVMCDIDToRvmCDID(ContractDID evmCDId, rvm::ContractDID* rvmCDId)
		{
			if (rvmCDId)
			{
				rt::Zero(*rvmCDId);
				*(ContractDID*)rvmCDId = evmCDId;
			}
		}
		// returns rvm::contractIdInvalid if not found
		static rvm::ContractId GetOnChainContractIdFromContractFullName(const rvm::ChainState* pChainState, const std::string& fullName)
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

		static const ContractDID GetOnChainPredaContractDIdFromFullName(const rvm::ChainState* pChainState, const std::string& fullName, rvm::BuildNum buildNum = rvm::BuildNumLatest)
		{
			rvm::ContractId contractId = GetOnChainContractIdFromContractFullName(pChainState, fullName);
			return RvmCDIDToEVMCDID(pChainState->GetContractDeploymentIdentifier(contractId, buildNum));
		}
	}
}


