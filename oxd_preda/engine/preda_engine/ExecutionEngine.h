#pragma once
#include <map>
#include "../../native/abi/vm_interfaces.h"
#include "RuntimeInterfaceImpl.h"
#include "ContractData.h"
#include "ContractRuntimeInstance.h"
#include "WASMRuntime.h"

class CContractDatabase;
class ContractRuntimeInstance;

enum class ExecutionResult : uint8_t {
	NoError									= 0,
	ContractNotFound						= 1,
	InvalidFunctionId						= 2,
	FunctionSignatureMismatch				= 3,
	ExecutionError							= 4,
	//ContractStateExceedsSizeLimit			= 5,
	//SerializeOutContractStateError		= 6,
	SystemErrorBegin						= 128,
	CannotLoadLibrary						= 128,
	CannotCreateContractInstance			= 129,
	MapContractStateError					= 130,
};

class CExecutionEngine : public rvm::ExecuteUnit {
	friend struct AutoReleaseExecutionIntermediateData;
	friend class CRuntimeInterface;
private:
	CContractDatabase *m_pDB = nullptr;
	CRuntimeInterface m_runtimeInterface;

	// Pointer to current wasm runtime on stack, holds wasmtime::Store, wasmtime::Memory and main module symbols.
	// We do not preserve a WASMRuntime in CExecutionEngine since it may leak memory for a long running program.
	// Wasmtime doesn't support exception at the moment, the vm will just abort after a c++ exception is thrown,
	// leaving memory in the linear memory leaked.
	WASMRuntime* m_wasm_runtime = nullptr;

	// The base linker to store wrapped host functions, since calling `func_wrap` costs a lot of time.
	// We are (ab)using the feature `allow_shadowing` to share linker across different WASMRuntime.
	// The wasmtime doc says it's forbidden to reuse a linker which defined store-owned items(memory, global, etc.),
	// But it doesn't check that strictly in the source code.
	std::optional<wasmtime::Linker> m_base_linker;

	std::map<PredaContractDID, std::unique_ptr<ContractModuleLoaded>> m_loadedContractModule;
	std::map<PredaContractDID, ContractRuntimeInstance*> m_intermediateContractInstances;
	std::vector<std::vector<uint8_t>> m_inputStateCopies;
	void ReleaseExecutionIntermediateData();

	uint32_t InvokeContractCall(rvm::ExecutionContext *executionContext, rvm::ContractId contractId, uint32_t opCode, const void **ptrs, uint32_t numPtrs);

	ContractRuntimeInstance *CreateContractInstance(PredaContractDID deployId, rvm::ContractId contractId);
	bool MapNeededContractContext(rvm::ExecutionContext *executionContext, ContractRuntimeInstance *pInstance, uint32_t calledFunctionFlag);

	uint32_t Invoke_Internal(rvm::ExecutionContext *executionContext, PredaContractDID deployId, rvm::OpCode opCode, const rvm::ConstData* args_serialized, uint32_t gas_limit);
public:
	CContractDatabase* contractDatabase() {
		return m_pDB;
	}
	CRuntimeInterface& runtimeInterface() {
		return m_runtimeInterface;
	}

	void SetWASMRuntime(WASMRuntime* rt) {
		m_wasm_runtime = rt;
	}

	WASMRuntime *wasm_runtime() {
		return m_wasm_runtime;
	}

	std::optional<wasmtime::Linker> &base_linker() {
		return m_base_linker;
	}

	CExecutionEngine(CContractDatabase *pDB);
	virtual ~CExecutionEngine() {}

	virtual rvm::InvokeResult Invoke(rvm::ExecutionContext *executionContext, uint32_t gas_limit, const rvm::ContractDID *contract_deployment_id, rvm::OpCode opCode, const rvm::ConstData* args_serialized) override;
	virtual rvm::InvokeResult Deploy(rvm::ExecutionContext* exec, uint32_t gas_limit, rvm::CompiledContracts* linked, rvm::ContractDID* contract_deployment_ids, rvm::InterfaceDID** interface_deployment_ids, rvm::LogMessageOutput* log_msg_output) override;

	virtual void Release() override
	{
		delete this;
	}
	virtual void GetExceptionMessage(uint16_t except, rvm::StringStream* str) const override;
};
