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

	virtual std::unique_ptr<ContractRuntimeInstance> NewInstance(CExecutionEngine&, rvm::ContractVersionId cvId, const rvm::ContractVersionId* importedContractIds, uint32_t numImportedContracts) = 0;
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
	rvm::ContractModuleID mId;
	
	// here uses ContractVersionId + ContractContextType instead of ContractInvokeId because
	// currentMappedContractContextLevel might be changed during a call chain. e.g.
	// 1. A.f() calls B.g() (shard)
	// 2. B.g() returns
	// 3. A.f() then calls B.h() (custom scope, e.g. address)
	// In this case, at step 3, the instance of B created at step will be reused. (and has to,
	// be reused, otherwise any shard state changed by B.g() is not reflected.) It's mapped level
	// will then be changed from shard to address
	rvm::ContractVersionId cvId;
	prlrt::ContractContextType currentMappedContractContextLevel;

	virtual ~ContractRuntimeInstance() = default;

	virtual bool DestroyContractInstance() = 0;

	virtual bool MapContractContextToInstance(prlrt::ContractContextType type, const uint8_t* buffer, uint32_t bufferSize) = 0;

	virtual uint32_t TransactionCall(uint32_t functionId, const uint8_t* args, uint32_t args_size) = 0;

	virtual uint32_t ContractCall(uint32_t functionId, const void** ptrs, uint32_t numPtrs) = 0;

	virtual uint32_t GetContractContextSerializeSize(prlrt::ContractContextType type) = 0;

	virtual uint32_t SerializeOutContractContext(prlrt::ContractContextType type, uint8_t* buffer, uint32_t size) = 0;
};