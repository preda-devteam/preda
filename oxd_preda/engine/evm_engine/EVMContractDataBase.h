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

namespace xtl {
	class ContractDatabase : public rvm::RvmEngine {
		friend class CRuntimeInterface;
		os::CriticalSection m_barrier;
		ext::RocksDBStandalone m_contractDB;
		std::string m_dbPath;
		std::string m_modulePath;
		rvm::BlockchainRuntime* m_pRuntimeAPI = nullptr;

		std::map<rvm::ContractId, ContractDatabaseEntry> m_contracts;

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
		virtual rvm::ConstString GetContractName(const rvm::ConstData* source_code) override;
		virtual bool			 Compile(	const rvm::ConstString*	dapp_name,
											uint32_t				contract_count, 
											const rvm::ConstData*	deploy_data_array,
											rvm::CompilationFlag	flag,
											rvm::CompiledModules**	compiled_output,
											rvm::LogMessageOutput*	log_msg_output
								 ) override;
		virtual bool			 Recompile(	const rvm::ConstString*	dapp_name,
											const rvm::ConstData*	dependency_data,
											uint32_t				contract_count, 
											const rvm::ConstData*	deploy_data_array,
											rvm::CompilationFlag	flag,
											rvm::CompiledModules**	compiled_output,
											rvm::LogMessageOutput*	log_msg_output
								 ) override;
		virtual bool			 Link(		rvm::CompiledModules*	compiled,
											rvm::LogMessageOutput*	log_msg_output
								 ) override;
		virtual void			 CancelCurrentBuildingTask() override;

		virtual rvm::ExecutionUnit* CreateExecuteUnit() override;

		// interfaces from ContractRepository
		virtual bool StateJsonify(rvm::ContractInvokeId contract, const rvm::ConstData* contract_state, rvm::StringStream* json_out) const override;
		virtual bool StateJsonParse(rvm::ContractInvokeId contract, const rvm::ConstString* json, rvm::DataBuffer* state_out, rvm::LogMessageOutput* error_out) const override;

		virtual bool ScatteredStateKeyJsonify(rvm::ContractInvokeId contract, const rvm::ConstData* key_data, rvm::StringStream* json_out) const override;

		virtual bool ArgumentsJsonify(rvm::ContractInvokeId contract, rvm::OpCode opCode, const rvm::ConstData* args_serialized, rvm::StringStream* json_out) const override;
		virtual bool ArgumentsJsonParse(rvm::ContractInvokeId contract, rvm::OpCode opCode, const rvm::ConstString* json, rvm::DataBuffer* args_out, rvm::LogMessageOutput* error_out) const override;

		virtual rvm::ContractScopeId GetScopeDefinition(rvm::ContractScopeId cid) const override;
		virtual const rvm::Contract* GetContract(const rvm::ContractModuleID* deploy_id) const override;
		virtual uint32_t GetContractEnumSignatures(rvm::ContractVersionId contract, rvm::StringStream* signature_out) const override;
		virtual bool GetContractFunctionArgumentsSignature(rvm::ContractInvokeId contract, rvm::OpCode opcode, rvm::StringStream* signature_out) const override;
		virtual bool GetContractStateSignature(rvm::ContractInvokeId contract, rvm::StringStream* signature_out) const override;

		const rvm::Contract* GetContract(rvm::ContractId cid) const;
		const ContractDatabaseEntry* FindContractEntry(rvm::ContractId deployId) const;

		bool Deploy(const rvm::GlobalStates* chain_state, rvm::CompiledModules* linked, const evmc::address* deploy_address, const rvm::ContractId* cids);
		virtual ~ContractDatabase();
	};
}
#endif