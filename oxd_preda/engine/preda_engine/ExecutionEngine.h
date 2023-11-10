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
	SerializeOutMultipleVersionState		= 6,
	SystemErrorBegin						= 128,
	CannotLoadLibrary						= 128,
	CannotCreateContractInstance			= 129,
	MapContractStateError					= 130,
};

class CExecutionEngine : public rvm::ExecutionUnit {
	friend struct AutoReleaseExecutionIntermediateData;
	friend class CRuntimeInterface;
private:
	CContractDatabase *m_pDB = nullptr;
	CRuntimeInterface m_runtimeInterface;

	// The wasm runtime is wrapper of wasmtime engine, holds wasmtime::Store, wasmtime::Memory and main module symbols.
	// It is created once only when the ExecutionEngine is constructed.
	// However, Wasmtime doesn't support exception at present, the vm will just abort after a c++ exception is thrown, leaving memory in the linear memory leaked.
	// We could handle this by recreate the wasmtime regularly or when encounting an exception in the future.
	std::optional<WASMRuntime> m_wasm_runtime;

	// The base linker to store wrapped host functions, since calling `func_wrap` costs a lot of time.
	// We are (ab)using the feature `allow_shadowing` to share linker across different WASMRuntime.
	// The wasmtime doc says it's forbidden to reuse a linker which defined store-owned items(memory, global, etc.),
	// But it doesn't check that strictly in the source code.
	std::optional<wasmtime::Linker> m_base_linker;

	// This data sturcture used for cross contract call, such as A call B and then B call A.
	// However, as we keep the wesmtime engine, the number of wastime::instance is limited to 10000 currently. 
	// In addition, we haven't found a way to release the wastime::instance at present, it is auto realeased as the wastime engine destroys. 
	// Thus, we keep this structure instead of clearing it every invoke to solve the limited instance issue.
	// The limited instance issue might be solved by regularlly recreating the wastime engine or enlarging the wastime::Store later on.
	std::map<rvm::ContractModuleID, std::unique_ptr<ContractModuleLoaded>, _details::ModuleIdCompare> m_loadedContractModule;

	// the intermediate instances are contracts that are already loaded on the current call chain.
	// It's not indexed by ContractInvokeId because the current relay scheme doesn't allow cross-contract
	// call to other scopes (except global /shard), therefore it's not possible for multiple custom scopes
	// of the same contract to co-exist during the execution of a call chain.
	// It's not indexed by ContractId because different versions of the same contract might co-exist along
	// the call chain. (e.g. A[v2] -> B -> A[v1]). Although in this case the call would fail if A[v1] tries
	// to map a non-empty chain state that has already been converted to A[v2] format.
	std::map<rvm::ContractVersionId, ContractRuntimeInstance*> m_intermediateContractInstances;
	std::vector<std::vector<uint8_t>> m_inputStateCopies;
	void ReleaseExecutionIntermediateData();

	uint32_t InvokeContractCall(rvm::ExecutionContext *executionContext, rvm::ContractVersionId cvId, uint32_t opCode, const void **ptrs, uint32_t numPtrs);

	ContractRuntimeInstance *CreateContractInstance(const rvm::ContractModuleID &moduleId, rvm::ContractVersionId cvId, const rvm::ContractVersionId *importedCvId, uint32_t numImportedContracts);
	bool MapNeededContractContext(rvm::ExecutionContext *executionContext, ContractRuntimeInstance *pInstance, uint32_t calledFunctionFlag);

	uint32_t Invoke_Internal(rvm::ExecutionContext *executionContext, rvm::ContractVersionId cvId, const rvm::DeployedContract *deployedContract, rvm::OpCode opCode, const rvm::ConstData* args_serialized, uint32_t gas_limit);
public:
	CContractDatabase* contractDatabase() {
		return m_pDB;
	}
	CRuntimeInterface& runtimeInterface() {
		return m_runtimeInterface;
	}

	WASMRuntime *wasm_runtime() {
		return &m_wasm_runtime.value();
	}

	std::optional<wasmtime::Linker> &base_linker() {
		return m_base_linker;
	}

	CExecutionEngine(CContractDatabase *pDB);
	virtual ~CExecutionEngine() {}

	virtual rvm::InvokeResult Invoke(rvm::ExecutionContext *executionContext, uint32_t gas_limit, rvm::ContractInvokeId contract, rvm::OpCode opCode, const rvm::ConstData* args_serialized) override;
	virtual bool DeployContracts(rvm::ExecutionContext* exec, rvm::CompiledModules* linked, const rvm::ContractVersionId* target_cvids, rvm::DataBuffer** deploy_stub, rvm::LogMessageOutput* log_msg_output) override;
	virtual rvm::InvokeResult InitializeContracts(rvm::ExecutionContext* executionContext, uint32_t gas_limit, rvm::CompiledModules* linked, const rvm::ConstData* ctor_args) override;

	virtual void Release() override
	{
		delete this;
	}
	virtual void GetExceptionMessage(uint16_t except, rvm::StringStream* str) const override;
};
