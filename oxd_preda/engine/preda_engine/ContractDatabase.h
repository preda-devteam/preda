#pragma once
#include <string>
#include <map>
#include <vector>

#include "../../../SFC/core/ext/rocksdb/rocksdb.h"
#include "../../transpiler/transpiler.h"
#include "../../native/abi/vm_interfaces.h"
#include "RuntimeInterfaceImpl.h"
#include "ContractDatabaseEntry.h"
#include "ExecutionEngine.h"
#include "ContractRuntimeInstance.h"
#include "SymbolDBForTranspiler.h"

struct PredaLogMessages;
class CContractSymbolDatabaseForTranspiler;


// std::to_underlying is only available in c++ 23, a custom version to be used here
template<class EnumRef>
constexpr std::underlying_type_t<std::remove_reference_t<EnumRef>> enum_to_underlying(EnumRef&& e)
{
	return std::underlying_type_t<std::remove_reference_t<EnumRef>>(e);
}
enum class RuntimeMode : uint32_t {
	NATIVE = 0, // native executable code
	WASM = 1,   // webassembly bytecode, JIT
	CWASM = 2,  // compiled webassembly, AOT
};

class CContractDatabase : public rvm::RvmEngine
{
	friend class CRuntimeInterface;
	os::CriticalSection m_barrier;
	std::map<rvm::ContractModuleID, ContractDatabaseEntry, _details::ModuleIdCompare> m_contracts;
	ext::RocksDBStandalone m_contractDB;
	std::string m_dbPath;
	std::string m_modulePath;
	std::string m_transpilerVersion;
	rvm::BlockchainRuntime *m_pRuntimeAPI = nullptr;

	// temporary workaround for deploy ID generation. (Now increments by 1 for each deployment, should be some hash based on source or intermediate code + deploy data (contract id, imported contract ids, etc.))
	int64_t m_nextDeployId = 1;

	wasmtime::Engine m_wasm_engine;
	std::optional<wasmtime::Module> m_wasm_main_module;
	std::map<rvm::ContractModuleID, std::unique_ptr<ContractModule>, _details::ModuleIdCompare> m_loadedContractModule;
	uint64_t m_nextLinkStageIdx = 0;

private:
	static std::string ConvertEntryToJson(const ContractDatabaseEntry *pEntry);

	bool CompileContract(const rvm::ConstString* dapp_name, CContractSymbolDatabaseForTranspiler* symbol_db, std::string& out_intermediate_code, ContractCompileData& out_compile_data, PredaLogMessages& out_log, transpiler::ITranspiler* pTranspiler);
	bool LinkContract(const std::string& source_code, const std::string& intermediate_code, ContractLinkData& out_link_data, PredaLogMessages& out_log);

	//rvm::DeployError CompileContract(const rvm::DAppName &DApp, const rvm::ContractName &name, const char *source_code, CContractSymbolDatabaseForTranspiler *symbol_db, bool transpile_only, std::string &out_intermediate_code, ContractDatabaseEntry &out_entry, rvm::StringStream *out_compile_messages);
	
	bool GetCppCompilerVersion(std::tuple<uint32_t, uint32_t, uint32_t> &outVersion);
	template<typename T>
	void mergeTwoImportList(std::vector<T>& all_import_list, std::vector<T>& incoming_import_list);

	bool _Compile(IContractFullNameToModuleIdLookupTable *lookup, const rvm::ConstString* dapp_name, uint32_t contract_count, const rvm::ConstData* deploy_data_array, rvm::CompilationFlag flag, rvm::CompiledModules** compiled_output, rvm::LogMessageOutput* log_msg_output);


public:
	const RuntimeMode m_runtime_mode;

	CContractDatabase(RuntimeMode mode);

	wasmtime::Engine& wasm_engine() {
		return m_wasm_engine;
	}

	wasmtime::Module& wasm_main_module() {
		ASSERT(m_wasm_main_module);
		return *m_wasm_main_module;
	}

	// interfaces from RvmEngine
	virtual bool Initialize(const char* module_path, const char* db_path, rvm::BlockchainRuntime *runtime_api, rvm::ConstString *initErrorMsg) override;
	virtual void Release() override;

	virtual rvm::ConstString GetVersion() const override;
	virtual rvm::ConstString GetName() const override;
	virtual rvm::ConstString GetVendorInfo() const override;

	// Build a collection of contracts
	virtual rvm::ConstString GetContractName(const rvm::ConstData* source_code) override; // return the name of the contract without actual compilation
	virtual bool Compile(const rvm::ConstString* dapp_name, uint32_t contract_count, const rvm::ConstData* deploy_data_array, rvm::CompilationFlag flag, rvm::CompiledModules** compiled_output, rvm::LogMessageOutput* log_msg_output) override;
	virtual bool Recompile(const rvm::ConstString* dapp_name, const rvm::ConstData* dependency_data, uint32_t contract_count, const rvm::ConstData* deploy_data_array, rvm::CompilationFlag flag, rvm::CompiledModules** compiled_output, rvm::LogMessageOutput* log_msg_output) override;
	virtual bool Link(rvm::CompiledModules* compiled, rvm::LogMessageOutput* log_msg_output) override;

	void CancelCurrentBuildingTask() override;

	//virtual bool Undeploy(rvm::RVM_CONTRACT_ID contract) override;
	//virtual uint32_t GetDependingContracts(rvm::RVM_CONTRACT_ID contract, uint32_t buildNum, rvm::RVM_CONTRACT_ID *out_depending_contracts, uint32_t buffer_size) override;

	virtual rvm::ExecutionUnit* CreateExecuteUnit() override;

	// interfaces from ContractRepository
	virtual bool StateJsonify(rvm::ContractInvokeId contract, const rvm::ConstData* pState, rvm::StringStream* json_out) const override;
	virtual bool StateJsonParse(rvm::ContractInvokeId contract, const rvm::ConstString* json, rvm::DataBuffer* state_out, rvm::LogMessageOutput *log) const override;

	virtual bool ArgumentsJsonify(rvm::ContractInvokeId contract, rvm::OpCode opCode, const rvm::ConstData* args_serialized, rvm::StringStream* json_out) const override;
	virtual bool ArgumentsJsonParse(rvm::ContractInvokeId contract, rvm::OpCode opCode, const rvm::ConstString* json, rvm::DataBuffer* args_out, rvm::LogMessageOutput *log) const override;

	virtual rvm::ContractScopeId GetScopeDefinition(rvm::ContractScopeId cid) const override
	{
		// TODO: implement
		return cid;
	}


	virtual const rvm::Contract* GetContract(const rvm::ContractModuleID *module_id) const override;


	virtual uint32_t GetContractEnumSignatures(rvm::ContractVersionId contract, rvm::StringStream* signature_out = nullptr) const override;
	virtual bool GetContractFunctionArgumentsSignature(rvm::ContractInvokeId contract, rvm::OpCode opcode, rvm::StringStream* signature_out) const override;
	virtual bool GetContractStateSignature(rvm::ContractInvokeId contract, rvm::StringStream* signature_out) const override;

	const ContractDatabaseEntry* FindContractEntry(const rvm::ContractModuleID &moduleId) const;
	const ContractDatabaseEntry* FindContractEntry(const rvm::ContractModuleID *moduleId) const;
	ContractModule* GetContractModule(const rvm::ContractModuleID &deployId);
	bool Deploy(const rvm::GlobalStates* chain_state, rvm::CompiledModules* linked, rvm::DataBuffer** out_stub, rvm::LogMessageOutput* log_msg_output);

	bool VariableJsonify(rvm::ContractModuleID deployId, const char *type_string, const uint8_t *args_serialized, uint32_t args_size, std::string &outJson, const rvm::ChainStates* ps) const;

	virtual ~CContractDatabase() {}

};