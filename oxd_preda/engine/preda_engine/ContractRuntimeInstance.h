#pragma once

#include <string>
#include <iostream>
#include <wasmtime.hh> // wasmtime need string and iostream but did not include them

#include "ContractData.h"
#include "../../native/abi/vm_types.h"
#include "../../bin/compile_env/include/runtime_interface.h"

class ContractRuntimeInstance;
class CExecutionEngine;
class CContractDatabase;
struct ContractDatabaseEntry;

class ContractModuleLoaded {
public:
	virtual ~ContractModuleLoaded() = default;

	virtual std::unique_ptr<ContractRuntimeInstance> NewInstance(CExecutionEngine&) = 0;
};

class ContractModule {
public:
	virtual ~ContractModule() = default;
	virtual std::unique_ptr<ContractModuleLoaded> LoadToEngine(CExecutionEngine&) = 0;

	static std::unique_ptr<ContractModule> FromLibrary(const ContractDatabaseEntry&, HANDLE mod);
	static std::unique_ptr<ContractModule> FromWASMModule(const ContractDatabaseEntry&, wasmtime::Module mod);
};

class ContractRuntimeInstance {
public:
	PredaContractDID deployId;
	rvm::ContractId contractId;
	prlrt::ContractContextType currentMappedContractContextLevel;

	virtual ~ContractRuntimeInstance() = default;

	virtual bool DestroyContractInstance() = 0;

	virtual bool MapContractContextToInstance(prlrt::ContractContextType type, const uint8_t* buffer, uint32_t bufferSize) = 0;

	virtual uint32_t TransactionCall(uint32_t functionId, const uint8_t* args, uint32_t args_size) = 0;

	virtual uint32_t ContractCall(uint32_t functionId, const void** ptrs, uint32_t numPtrs) = 0;

	virtual uint32_t GetContractContextSerializeSize(prlrt::ContractContextType type) = 0;

	virtual uint32_t SerializeOutContractContext(prlrt::ContractContextType type, uint8_t* buffer, uint32_t size) = 0;
};