#pragma once
#ifdef _WIN32
	#pragma warning(push)
	#pragma warning(disable:4068 4819)
#endif
#include <evmc/evmc.hpp>
#ifdef _WIN32
	#pragma warning(pop)
#endif
#include "EVMContractData.h"

#ifdef ENABLE_EVM

#include "../../native/abi/vm_interfaces.h"
#include "../../../SFC/core/ext/rocksdb/rocksdb.h"

namespace preda_evm {
	class ContractDatabase : public rvm::RvmEngine {
		friend class CRuntimeInterface;
		os::CriticalSection m_barrier;
		ext::RocksDBStandalone m_contractDB;
		std::string m_dbPath;
		std::string m_modulePath;
		rvm::BlockchainRuntime* m_pRuntimeAPI = nullptr;

		std::map<ContractModuleID, ContractDatabaseEntry> m_contracts;

		// temporary workaround for deploy ID generation. (Now increments by 1 for each deployment, should be some hash based on source or intermediate code + deploy data (contract id, imported contract ids, etc.))
		int64_t m_nextDeployId = 1;
	public:
		// interfaces from RvmEngine
		virtual bool Initialize(const char* module_path, const char* db_path, rvm::BlockchainRuntime* runtime_api, rvm::ConstString* initErrorMsg) override;
		virtual void Release() override;

		virtual rvm::ConstString GetVersion() const override;
		virtual rvm::ConstString GetName() const override;
		virtual rvm::ConstString GetVendorInfo() const override;

		// Build a collection of contracts
		virtual bool Compile(const rvm::ChainStates* chain_state, const rvm::ConstString* dapp_name, uint32_t contract_count, const rvm::ConstData* deploy_data_array, rvm::CompilationFlag flag, rvm::CompiledModules** compiled_output, rvm::DataBuffer* dependency, rvm::LogMessageOutput* log_msg_output) override;
		virtual bool Link(rvm::CompiledModules* compiled, rvm::LogMessageOutput* log_msg_output) override;
		virtual bool ValidateDependency(const rvm::ChainStates* chain_state, rvm::CompiledModules* compiled, const rvm::ConstData* dependency) override;

		//virtual bool Undeploy(rvm::RVM_CONTRACT_ID contract) override;
		//virtual uint32_t GetDependingContracts(rvm::RVM_CONTRACT_ID contract, uint32_t buildNum, rvm::RVM_CONTRACT_ID *out_depending_contracts, uint32_t buffer_size) override;

		virtual rvm::ExecuteUnit* CreateExecuteUnit() override;

		// interfaces from ContractRepository
		virtual bool StateJsonify(rvm::BuildNum build_num, rvm::ContractScopeId contract, const rvm::ConstData* pState, rvm::StringStream* json_out, const rvm::ChainStates* ps) const override;
		virtual bool StateJsonParse(rvm::BuildNum build_num, rvm::ContractScopeId contract, const rvm::ConstString* json, rvm::DataBuffer* state_out, const rvm::ChainStates* ps, rvm::LogMessageOutput* og) const override;

		virtual bool ArgumentsJsonify(rvm::BuildNum build_num, rvm::ContractScopeId contract, rvm::OpCode opCode, const rvm::ConstData* args_serialized, rvm::StringStream* json_out, const rvm::ChainStates* ps) const override;
		virtual bool ArgumentsJsonParse(rvm::BuildNum build_num, rvm::ContractScopeId contract, rvm::OpCode opCode, const rvm::ConstString* json, rvm::DataBuffer* args_out, const rvm::ChainStates* ps, rvm::LogMessageOutput* log) const override;

		virtual rvm::ContractScopeId GetScopeDefinition(rvm::ContractScopeId cid) const override
		{
			// TODO: implement
			return cid;
		}


		virtual const rvm::Contract* GetContract(const rvm::ContractModuleID* deploy_id) const override;
		const rvm::Contract* GetContract(ContractModuleID deploy_id) const;
		virtual const rvm::Interface* GetInterface(const rvm::InterfaceModuleID* deploy_id) const override
		{
			// TODO
			return nullptr;
		}


		virtual uint32_t GetContractEnumSignatures(rvm::BuildNum build_num, rvm::ContractId contract, rvm::StringStream* signature_out, const rvm::ChainStates* ps = nullptr) const override;
		virtual bool GetContractFunctionArgumentsSignature(rvm::BuildNum build_num, rvm::ContractScopeId contract, rvm::OpCode opcode, rvm::StringStream* signature_out, const rvm::ChainStates* ps = nullptr) const override;
		virtual bool GetContractStateSignature(rvm::BuildNum build_num, rvm::ContractScopeId contract, rvm::StringStream* signature_out, const rvm::ChainStates* ps = nullptr) const override;

		const ContractDatabaseEntry* FindContractEntry(ContractModuleID deployId) const;

		bool Deploy(const rvm::ChainStates* chain_state, const rvm::ContractId* contractIds, const evmc::address* deploy_address, rvm::CompiledModules* linked, rvm::ContractModuleID* deployment_identifiers_out, rvm::InterfaceModuleID** interface_deployment_ids_out, rvm::LogMessageOutput* log_msg_output);

		virtual ~ContractDatabase();
	};
}
#endif