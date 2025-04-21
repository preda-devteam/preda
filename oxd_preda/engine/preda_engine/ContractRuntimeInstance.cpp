#include "ContractRuntimeInstance.h"
#include "ContractDatabaseEntry.h"
#include "ExecutionEngine.h"

class ContractModuleDLL : public ContractModule {
public:
	typedef void* (*FNCreateContractInstance)(prlrt::IRuntimeInterface* ____pInterface, uint64_t contractId, const uint64_t *importedContractIds, uint32_t numImportedContracts, uint64_t gas_limit);
	typedef void* (*FNDestroyContractInstance)(void* pContractInstancce);
	typedef bool(*FNMapContractContextToInstance)(void* pInstance, prlrt::ContractContextType type, const uint8_t* buffer, uint32_t bufferSize);
	typedef uint32_t(*FNTransactionCall)(void* pContractInstance, uint32_t functionId, const uint8_t* args, uint32_t args_size);
	typedef uint32_t(*FNContractCall)(void* pContractInstance, uint32_t functionId, const void** ptrs, uint32_t numPtrs);
	typedef uint32_t(*FNGetContactStateSize)(void* pContractInstance, prlrt::ContractContextType type);
	typedef uint32_t(*FNGetContractContextSerializeSize)(void* pContractInstance, prlrt::ContractContextType type);
	typedef uint32_t(*FNSerializeOutContractContext)(void* pContractInstance, prlrt::ContractContextType type, uint8_t* buffer);
	typedef uint32_t (*FNInitGasTable)(uint16_t* gas_cost_tbl, uint8_t gas_tble_size);
	typedef uint64_t(*FNGetRemainingGas)();
	typedef uint32_t (*FNSetRemainingGas)(uint64_t remainingGas);
	typedef uint32_t (*FNCommitJournaledStates)(void* pContractInstance, bool isGlobalContext);

	FNCreateContractInstance fnCreateInstance;
	FNDestroyContractInstance fnDestroyContractInstance;
	FNMapContractContextToInstance fnMapContractContextToInstance;
	FNTransactionCall fnTransactionCall;
	FNContractCall fnContractCall;
	FNGetContractContextSerializeSize fnGetContractContextSerializeSize;
	FNSerializeOutContractContext fnSerializeOutContractContext;
	FNInitGasTable fnInitGasTable;
	FNGetRemainingGas fnGetRemainingGas;
	FNSetRemainingGas fnSetRemainingGas;
	FNCommitJournaledStates fnCommitJournaledStates;

	std::unique_ptr<ContractModuleLoaded> LoadToEngine(CExecutionEngine&) override;
};
#ifndef __APPLE__
thread_local std::pmr::unsynchronized_pool_resource ContractRuntimeInstance::tl_memory_pool;
#endif

class ContractModuleDLLLoaded : public ContractModuleLoaded {
private:
	ContractModuleDLL& m_dll;
public:
	ContractModuleDLLLoaded(ContractModuleDLL& dll) : m_dll(dll) {}
	ContractRuntimeInstance* NewInstance(CExecutionEngine& engine, rvm::ContractVersionId contractId, const rvm::ContractVersionId* importedContractIds, uint32_t numImportedContracts, uint64_t gas_limit) override;
};

std::unique_ptr<ContractModuleLoaded> ContractModuleDLL::LoadToEngine(CExecutionEngine&) {
	return std::make_unique<ContractModuleDLLLoaded>(*this);
}

std::unique_ptr<ContractModule> ContractModule::FromLibrary(const ContractDatabaseEntry& entry, HANDLE mod) {
	typedef void (*FNInitTables)();
	std::string exportUniqueStr = entry.compileData.exportUniqueString;
	FNInitTables InitTables = (FNInitTables)os::GetDynamicLibrarySymbol(mod, ("Contract_" + exportUniqueStr + "_InitTables").c_str());
	if (InitTables == nullptr)
		return nullptr;
	{
		InitTables();
	}

	std::unique_ptr<ContractModuleDLL> dllModule = std::make_unique<ContractModuleDLL>();

	dllModule->fnCreateInstance = (ContractModuleDLL::FNCreateContractInstance)os::GetDynamicLibrarySymbol(mod, ("Contract_" + exportUniqueStr + "_CreateInstance").c_str());
	dllModule->fnDestroyContractInstance = (ContractModuleDLL::FNDestroyContractInstance)os::GetDynamicLibrarySymbol(mod, ("Contract_" + exportUniqueStr + "_DestroyInstance").c_str());
	dllModule->fnMapContractContextToInstance = (ContractModuleDLL::FNMapContractContextToInstance)os::GetDynamicLibrarySymbol(mod, ("Contract_" + exportUniqueStr + "_MapContractContextToInstance").c_str());
	dllModule->fnTransactionCall = (ContractModuleDLL::FNTransactionCall)os::GetDynamicLibrarySymbol(mod, ("Contract_" + exportUniqueStr + "_TransactionCallEntry").c_str());
	dllModule->fnContractCall = (ContractModuleDLL::FNContractCall)os::GetDynamicLibrarySymbol(mod, ("Contract_" + exportUniqueStr + "_ContractCallEntry").c_str());
	dllModule->fnGetContractContextSerializeSize = (ContractModuleDLL::FNGetContractContextSerializeSize)os::GetDynamicLibrarySymbol(mod, ("Contract_" + exportUniqueStr + "_GetContractContextSerializeSize").c_str());
	dllModule->fnSerializeOutContractContext = (ContractModuleDLL::FNSerializeOutContractContext)os::GetDynamicLibrarySymbol(mod, ("Contract_" + exportUniqueStr + "_SerializeOutContractContext").c_str());
	dllModule->fnInitGasTable = (ContractModuleDLL::FNInitGasTable)os::GetDynamicLibrarySymbol(mod, ("Contract_" + exportUniqueStr + "_InitGasTable").c_str());
	dllModule->fnGetRemainingGas = (ContractModuleDLL::FNGetRemainingGas)os::GetDynamicLibrarySymbol(mod, ("Contract_" + exportUniqueStr + "_GetRemainingGas").c_str());
	dllModule->fnSetRemainingGas = (ContractModuleDLL::FNSetRemainingGas)os::GetDynamicLibrarySymbol(mod, ("Contract_" + exportUniqueStr + "_SetRemainingGas").c_str());
	dllModule->fnCommitJournaledStates = (ContractModuleDLL::FNCommitJournaledStates)os::GetDynamicLibrarySymbol(mod, ("Contract_" + exportUniqueStr + "_CommitJournaledStates").c_str());
	if (dllModule->fnCreateInstance == nullptr
		|| dllModule->fnDestroyContractInstance == nullptr
		|| dllModule->fnMapContractContextToInstance == nullptr
		|| dllModule->fnTransactionCall == nullptr
		|| dllModule->fnContractCall == nullptr
		|| dllModule->fnGetContractContextSerializeSize == nullptr
		|| dllModule->fnSerializeOutContractContext == nullptr
		|| dllModule->fnInitGasTable == nullptr
		|| dllModule->fnGetRemainingGas == nullptr
		|| dllModule->fnSetRemainingGas == nullptr
		|| dllModule->fnCommitJournaledStates == nullptr)
		return nullptr;
	return dllModule;
}

class ContractRuntimeInstanceDLL : public ContractRuntimeInstance {
	ContractModuleDLL& m_mod;
	void* m_instance;
public:
	ContractRuntimeInstanceDLL(ContractModuleDLL& mod, void *instance): m_mod(mod), m_instance(instance) {}

	bool DestroyContractInstance() override {
		m_mod.fnDestroyContractInstance(m_instance);
		this->~ContractRuntimeInstanceDLL();
#ifndef __APPLE__
		GetThreadLocalMemoryPool()->deallocate(this, sizeof(*this));
#endif
		return true;
	}

	bool MapContractContextToInstance(prlrt::ContractContextType type, const uint8_t* buffer, uint32_t bufferSize) override {
		return m_mod.fnMapContractContextToInstance(m_instance, type, buffer, bufferSize);
	}

	uint32_t TransactionCall(uint32_t functionId, const uint8_t* args, uint32_t args_size) override {
		return m_mod.fnTransactionCall(m_instance, functionId, args, args_size);
	}

	uint32_t ContractCall(uint32_t functionId, const void** ptrs, uint32_t numPtrs) override {
		return m_mod.fnContractCall(m_instance, functionId, ptrs, numPtrs);
	}

	uint32_t GetContractContextSerializeSize(prlrt::ContractContextType type) override {
		return m_mod.fnGetContractContextSerializeSize(m_instance, type);
	}

	uint32_t SerializeOutContractContext(prlrt::ContractContextType type, uint8_t* buffer, uint32_t size) override {
		return m_mod.fnSerializeOutContractContext(m_instance, type, buffer);
	}

	uint32_t TransactionCallWithoutInstance(uint32_t functionId, const uint8_t* args, uint32_t args_size) override {
		return m_mod.fnTransactionCall(nullptr, functionId, args, args_size);
	}

	uint32_t InitGasTable(uint16_t* gas_cost_tbl, uint8_t gas_tbl_size) override
	{
		return m_mod.fnInitGasTable(gas_cost_tbl, gas_tbl_size);
	}

	uint64_t GetRemainingGas() override
	{
		return m_mod.fnGetRemainingGas();
	}

	uint32_t SetRemainingGas(uint64_t remainingGas) override
	{
		return m_mod.fnSetRemainingGas(remainingGas);
	}

	uint32_t CommitJournaledStates(bool isGlobalContext) override
	{
		return m_mod.fnCommitJournaledStates(m_instance, isGlobalContext);
	}
};


ContractRuntimeInstance* ContractModuleDLLLoaded::NewInstance(CExecutionEngine& engine, rvm::ContractVersionId contractId, const rvm::ContractVersionId* importedContractIds, uint32_t numImportedContracts, uint64_t gas_limit)
{
	static_assert(sizeof(uint64_t) == sizeof(rvm::ContractVersionId), "rvm::ContractVersionId is no longer a 64-bit integer, need to change contract CreateInstance() argument type");
	void* pInstance = m_dll.fnCreateInstance(&engine.runtimeInterface(), uint64_t(contractId), (const uint64_t*)importedContractIds, numImportedContracts, gas_limit);
	if (!pInstance) {
		return nullptr;
	}
#ifndef __APPLE__
	ContractRuntimeInstanceDLL *ret = (ContractRuntimeInstanceDLL*)ContractRuntimeInstance::GetThreadLocalMemoryPool()->allocate(sizeof(ContractRuntimeInstanceDLL));
	return new (ret) ContractRuntimeInstanceDLL(m_dll, pInstance);
#else 
	return new ContractRuntimeInstanceDLL(m_dll, pInstance);
#endif
}

struct WASMEntryPoints {
	wasmtime::Store& store;

	wasmtime::Instance wasmInstance;

	wasmtime::TypedFunc<std::tuple<WasmPtrT, uint64_t, WasmPtrT, uint32_t, uint64_t>, WasmPtrT> fnCreateContract;
	wasmtime::TypedFunc<WasmPtrT, std::monostate> fnDestroyContract;
	wasmtime::TypedFunc<std::tuple<WasmPtrT, uint32_t, WasmPtrT, uint32_t>, uint32_t> fnMapContractContextToInstance;
	wasmtime::TypedFunc<std::tuple<WasmPtrT, uint32_t, WasmPtrT, uint32_t>, uint32_t> fnTransactionCall;
	wasmtime::TypedFunc<std::tuple<WasmPtrT, uint32_t, WasmPtrT, uint32_t>, uint32_t> fnContractCall;
	wasmtime::TypedFunc<std::tuple<WasmPtrT, uint32_t>, uint32_t> fnGetContractSerializeSize;
	wasmtime::TypedFunc<std::tuple<WasmPtrT, uint32_t, WasmPtrT>, uint32_t> fnSerializeOutContract;
	wasmtime::TypedFunc<std::tuple<WasmPtrT, uint32_t>, uint32_t> fnInitGasTable; 
	wasmtime::TypedFunc<std::tuple<>, uint64_t> fnGetRemainingGas; 
	wasmtime::TypedFunc<std::tuple<uint64_t>, uint32_t> fnSetRemainingGas; 
	wasmtime::TypedFunc<std::tuple<WasmPtrT, uint32_t>, uint32_t> fnCommitJournaledStates; 

	using FnInitTables = wasmtime::TypedFunc<std::monostate, std::monostate>;
};

class ContractModuleWASM : public ContractModule {
	const ContractDatabaseEntry& m_entry;
	wasmtime::Module m_mod;
public:
	ContractModuleWASM(const ContractDatabaseEntry& entry, wasmtime::Module mod);

	std::unique_ptr<ContractModuleLoaded> LoadToEngine(CExecutionEngine&) override;
};

class ContractModuleWASMLoaded : public ContractModuleLoaded {
private:
	WASMEntryPoints m_entry_points;
public:
	ContractModuleWASMLoaded(WASMEntryPoints entry_points) : m_entry_points(std::move(entry_points)) {}
	ContractRuntimeInstance* NewInstance(CExecutionEngine&, rvm::ContractVersionId contractId, const rvm::ContractVersionId* importedContractIds, uint32_t numImportedContracts, uint64_t gas_limit) override;
};

class WASMMemory {
	bool m_freed = false;
	WasmPtrT m_ptr = 0;
	WASMRuntime& m_rt;

public:
	WASMMemory(WASMRuntime& rt, uint32_t size) : m_rt(rt) {
		auto r = rt.malloc().call(m_rt.wasm_store(), { (uint32_t)size });
		if (r) {
			m_ptr = r.unwrap();
		}
	}

	bool Valid() {
		return m_ptr != 0;
	}

	bool Resize(uint32_t size)
	{
		free();
		auto r = m_rt.malloc().call(m_rt.wasm_store(), { (uint32_t)size });
		if (r) {
			m_ptr = r.unwrap();
			return true;
		}
		return false;
	}

	WasmPtrT Ptr() {
		return m_ptr;
	}

	uint8_t* HostPtr() {
		if (!m_ptr) {
			return nullptr;
		}
		return m_rt.memory().data(m_rt.wasm_store()).data() + m_ptr;
	}

	~WASMMemory() {
		free();
	}

	bool free() {
		if (!m_freed && m_ptr) {
			auto r = m_rt.free().call(m_rt.wasm_store(), { m_ptr });
			m_freed = true;
			m_ptr = 0;
			return (bool)r;
		}
		return true;
	}

	void forget() {
		m_freed = true;
	}
};


std::unique_ptr<ContractModuleLoaded> ContractModuleWASM::LoadToEngine(CExecutionEngine& engine) {
	WASMRuntime* rt = engine.wasm_runtime();
	if (!rt) {
		return nullptr;
	}

	wasmtime::Store::Context ctx = rt->wasm_store();

	std::optional<wasmtime::Instance> maybe_instance = rt->Instantiate(m_mod);

	if (!maybe_instance) {
		return nullptr;
	}
	wasmtime::Instance instance(*std::move(maybe_instance));

	auto maybe___wasm_apply_data_relocs = TypedFuncExtract<wasmtime::TypedFunc<std::tuple<>, std::monostate>>::Get(ctx, instance, "__wasm_apply_data_relocs");
	if (!maybe___wasm_apply_data_relocs) {
		return nullptr;
	}
	if (!maybe___wasm_apply_data_relocs->call(ctx, std::tuple<>())) {
		return {};
	}

	auto memory = rt->memory();

	const std::string& exportUniqueStr = m_entry.compileData.exportUniqueString;

	auto fnCreateContract = TypedFuncExtract<decltype(WASMEntryPoints::fnCreateContract)>::Get(ctx, instance, ("Contract_" + exportUniqueStr + "_CreateInstance"));
	auto fnDestroyContract = TypedFuncExtract<decltype(WASMEntryPoints::fnDestroyContract)>::Get(ctx, instance, ("Contract_" + exportUniqueStr + "_DestroyInstance"));
	auto fnMapContractContextToInstance = TypedFuncExtract<decltype(WASMEntryPoints::fnMapContractContextToInstance)>::Get(ctx, instance, ("Contract_" + exportUniqueStr + "_MapContractContextToInstance"));
	auto fnTransactionCall = TypedFuncExtract<decltype(WASMEntryPoints::fnTransactionCall)>::Get(ctx, instance, ("Contract_" + exportUniqueStr + "_TransactionCallEntry"));
	auto fnContractCall = TypedFuncExtract<decltype(WASMEntryPoints::fnContractCall)>::Get(ctx, instance, ("Contract_" + exportUniqueStr + "_ContractCallEntry"));
	auto fnGetContractSerializeSize = TypedFuncExtract<decltype(WASMEntryPoints::fnGetContractSerializeSize)>::Get(ctx, instance, ("Contract_" + exportUniqueStr + "_GetContractContextSerializeSize"));
	auto fnSerializeOutContract = TypedFuncExtract<decltype(WASMEntryPoints::fnSerializeOutContract)>::Get(ctx, instance, ("Contract_" + exportUniqueStr + "_SerializeOutContractContext"));

	auto fnInitTables = TypedFuncExtract<WASMEntryPoints::FnInitTables>::Get(ctx, instance, ("Contract_" + exportUniqueStr + "_InitTables"));
	auto fnInitGasTable = TypedFuncExtract<decltype(WASMEntryPoints::fnInitGasTable)>::Get(ctx, instance, ("Contract_" + exportUniqueStr + "_InitGasTable"));
	auto fnGetRemainingGas = TypedFuncExtract<decltype(WASMEntryPoints::fnGetRemainingGas)>::Get(ctx, instance, ("Contract_" + exportUniqueStr + "_GetRemainingGas"));
	auto fnSetRemainingGas = TypedFuncExtract<decltype(WASMEntryPoints::fnSetRemainingGas)>::Get(ctx, instance, ("Contract_" + exportUniqueStr + "_SetRemainingGas"));
	auto fnCommitJournaledStates = TypedFuncExtract<decltype(WASMEntryPoints::fnCommitJournaledStates)>::Get(ctx, instance, ("Contract_" + exportUniqueStr + "_CommitJournaledStates"));

	if (
		!fnCreateContract ||
		!fnDestroyContract ||
		!fnMapContractContextToInstance ||
		!fnTransactionCall ||
		!fnContractCall ||
		!fnGetContractSerializeSize ||
		!fnSerializeOutContract ||
		!fnInitTables ||
		!fnInitGasTable ||
		!fnGetRemainingGas ||
		!fnSetRemainingGas ||
		!fnCommitJournaledStates)
		return nullptr;

	{
		if (!fnInitTables->call(rt->wasm_store(), {})) {
			return nullptr;
		}
	}

	WASMEntryPoints pEntryPoints{
		rt->wasm_store(),
		instance,
		fnCreateContract.value(),
		fnDestroyContract.value(),
		fnMapContractContextToInstance.value(),
		fnTransactionCall.value(),
		fnContractCall.value(),
		fnGetContractSerializeSize.value(),
		fnSerializeOutContract.value(),
		fnInitGasTable.value(),
		fnGetRemainingGas.value(),
		fnSetRemainingGas.value(),
		fnCommitJournaledStates.value()
	};

	return std::make_unique<ContractModuleWASMLoaded>(std::move(pEntryPoints));
}

ContractModuleWASM::ContractModuleWASM(const ContractDatabaseEntry& entry, wasmtime::Module mod) : m_entry(entry), m_mod(std::move(mod)) {
}

std::unique_ptr<ContractModule> ContractModule::FromWASMModule(const ContractDatabaseEntry& entry, wasmtime::Module mod) {
	return std::make_unique<ContractModuleWASM>(entry, std::move(mod));
}

class ContractRuntimeInstanceWASM: public ContractRuntimeInstance
{
	CExecutionEngine& m_engine;
	WASMRuntime& m_rt;
	WASMEntryPoints &m_entry_points;
	WasmPtrT m_wasm_contract = 0;
	WASMMemory m_gas_table;
	// Copy of the input states in wasm memory. Released after invocation.
	std::vector<std::shared_ptr<WASMMemory>> m_input_state_copy;

public:
	ContractRuntimeInstanceWASM(
		CExecutionEngine &engine,
		WASMRuntime& rt,
		WASMEntryPoints &entry_points,
		WasmPtrT contract);

	bool DestroyContractInstance() override;

	bool MapContractContextToInstance(prlrt::ContractContextType type, const uint8_t* buffer, uint32_t bufferSize) override ;

	uint32_t TransactionCall(uint32_t functionId, const uint8_t* args, uint32_t args_size) override;

	uint32_t ContractCall(uint32_t functionId, const void** ptrs, uint32_t numPtrs) override;

	uint32_t GetContractContextSerializeSize(prlrt::ContractContextType type) override;

	uint32_t SerializeOutContractContext(prlrt::ContractContextType type, uint8_t* buffer, uint32_t size) override;

	uint32_t TransactionCallWithoutInstance(uint32_t functionId, const uint8_t* args, uint32_t args_size) override;

	uint32_t InitGasTable(uint16_t* gas_cost_tbl, uint8_t gas_tbl_size) override;

	uint64_t GetRemainingGas() override;

	uint32_t SetRemainingGas(uint64_t remainingGas) override;

	uint32_t CommitJournaledStates(bool isGlobalContext) override;
};

ContractRuntimeInstanceWASM::ContractRuntimeInstanceWASM(
	CExecutionEngine& engine,
	WASMRuntime& rt,
	WASMEntryPoints &entry_points,
	WasmPtrT contract): m_engine(engine), m_rt(rt), m_entry_points(entry_points), m_wasm_contract(contract), m_gas_table(rt, 0)
{
}

bool ContractRuntimeInstanceWASM::DestroyContractInstance()
{
	auto r = m_entry_points.fnDestroyContract.call(m_entry_points.store.context(), { m_wasm_contract });
	this->~ContractRuntimeInstanceWASM();
#ifndef __APPLE__
	GetThreadLocalMemoryPool()->deallocate(this, sizeof(*this));
#endif
	return bool(r);
}

bool ContractRuntimeInstanceWASM::MapContractContextToInstance(prlrt::ContractContextType type, const uint8_t* buffer, uint32_t bufferSize)
{
	wasmtime::Store::Context ctx = m_entry_points.store.context();
	std::shared_ptr<WASMMemory> mem(new WASMMemory(m_rt, bufferSize));

	if (!mem->Valid()) {
		return false;
	}

	std::copy(buffer, buffer + bufferSize, mem->HostPtr());

	auto r = m_entry_points.fnMapContractContextToInstance.call(ctx, {
		m_wasm_contract, (uint32_t)type, mem->Ptr(), bufferSize
	});
	if (!r || !r.unwrap()) {
		return false;
	}

	m_input_state_copy.push_back(std::move(mem));

	return true;
}

uint32_t ContractRuntimeInstanceWASM::TransactionCall(uint32_t functionId, const uint8_t* args, uint32_t args_size)
{
	wasmtime::Store::Context ctx = m_entry_points.store.context();
	WASMMemory mem(m_rt, args_size);

	if (!mem.Valid()) {
		return (uint32_t)prlrt::ExecutionError::WASMTrapError;
	}

	std::copy(args, args + args_size, mem.HostPtr());

	m_engine.runtimeInterface().PushExecStack();
	auto r = m_entry_points.fnTransactionCall.call(ctx, {
		m_wasm_contract, (uint32_t)functionId, mem.Ptr(), args_size
	});
	prlrt::ExceptionType exc = m_engine.runtimeInterface().PopExecStack();

	if (exc != prlrt::ExceptionType::NoException) {
		return uint32_t(prlrt::ExecutionError::RuntimeException) | (uint32_t(exc) << 8);
	}
	if (!r) {
		std::string msg = r.err().message();
		return uint32_t(prlrt::ExecutionError::WASMTrapError);
	}

	return r.unwrap();
}

uint32_t ContractRuntimeInstanceWASM::ContractCall(uint32_t functionId, const void** ptrs, uint32_t numPtrs)
{
	m_engine.runtimeInterface().PushExecStack();
	auto r = m_entry_points.fnContractCall.call(m_entry_points.store, {
		m_wasm_contract, (uint32_t)functionId, static_cast<WasmPtrT>(reinterpret_cast<uintptr_t>(ptrs)), numPtrs
	});
	prlrt::ExceptionType exc = m_engine.runtimeInterface().PopExecStack();
	if (exc != prlrt::ExceptionType::NoException) {
		return uint32_t(prlrt::ExecutionError::RuntimeException) | (uint32_t(exc) << 8);
	}
	if (!r) {
		std::string msg = r.err().message();
		return uint32_t(prlrt::ExecutionError::WASMTrapError);
	}

	return r.unwrap();
}

uint32_t ContractRuntimeInstanceWASM::GetContractContextSerializeSize(prlrt::ContractContextType type)
{
	m_engine.runtimeInterface().PushExecStack();
	auto r = m_entry_points.fnGetContractSerializeSize.call(m_entry_points.store.context(), { m_wasm_contract, (uint32_t)type });
	prlrt::ExceptionType exc = m_engine.runtimeInterface().PopExecStack();
	if (exc != prlrt::ExceptionType::NoException || !r) {
		return 0;
	}
	return r.unwrap();
}

uint32_t ContractRuntimeInstanceWASM::SerializeOutContractContext(prlrt::ContractContextType type, uint8_t* buffer, uint32_t size)
{
	wasmtime::Store::Context ctx = m_entry_points.store.context();
	WASMMemory mem(m_rt, size);

	if (!mem.Valid()) {
		return (uint32_t)prlrt::ExecutionError::WASMTrapError;
	}

	m_engine.runtimeInterface().PushExecStack();
	auto r = m_entry_points.fnSerializeOutContract.call(ctx, { m_wasm_contract, (uint32_t)type, mem.Ptr() });
	prlrt::ExceptionType exc = m_engine.runtimeInterface().PopExecStack();

	if (exc != prlrt::ExceptionType::NoException) {
		return uint32_t(prlrt::ExecutionError::RuntimeException) | (uint32_t(exc) << 8);
	}
	if (!r) {
		std::string msg = r.err().message();
		return uint32_t(prlrt::ExecutionError::WASMTrapError);
	}

	std::copy(mem.HostPtr(), mem.HostPtr() + size, buffer);

	return r.unwrap();
}

uint32_t ContractRuntimeInstanceWASM::TransactionCallWithoutInstance(uint32_t functionId, const uint8_t* args, uint32_t args_size)
{
	wasmtime::Store::Context ctx = m_entry_points.store.context();
	WASMMemory mem(m_rt, args_size);

	if (!mem.Valid()) {
		return (uint32_t)prlrt::ExecutionError::WASMTrapError;
	}

	std::copy(args, args + args_size, mem.HostPtr());

	m_engine.runtimeInterface().PushExecStack();
	auto r = m_entry_points.fnTransactionCall.call(ctx, {
		0, (uint32_t)functionId, mem.Ptr(), args_size
		});
	prlrt::ExceptionType exc = m_engine.runtimeInterface().PopExecStack();

	if (exc != prlrt::ExceptionType::NoException) {
		return uint32_t(prlrt::ExecutionError::RuntimeException) | (uint32_t(exc) << 8);
	}
	if (!r) {
		std::string msg = r.err().message();
		return uint32_t(prlrt::ExecutionError::WASMTrapError);
	}

	return r.unwrap();
}

template <typename T>
inline T WasmPtrToPtr(wasmtime::Span<uint8_t> mem, WasmPtrT offset) {
	return offset == 0 ? nullptr : (T)(mem.begin() + offset);
}

ContractRuntimeInstance* ContractModuleWASMLoaded::NewInstance(CExecutionEngine& engine, rvm::ContractVersionId contractId, const rvm::ContractVersionId *importedContractIds, uint32_t numImportedContracts, uint64_t gas_limit)
{
	WASMRuntime *rt = engine.wasm_runtime();
	if (!rt) {
		return nullptr;
	}

	static_assert(sizeof(uint64_t) == sizeof(rvm::ContractVersionId), "rvm::ContractVersionId is no longer a 64-bit integer, need to change contract CreateInstance() argument type");

	WasmPtrT importedContractIds_offset = 0;
	if (numImportedContracts > 0) {
		WASMMemory mem(*rt, uint32_t(sizeof(importedContractIds[0]) * numImportedContracts));
		std::copy(importedContractIds, importedContractIds + numImportedContracts, (rvm::ContractVersionId*)mem.HostPtr());
		importedContractIds_offset = mem.Ptr();
		mem.forget();
	}

	auto maybe_contractInstance = m_entry_points.fnCreateContract.call(m_entry_points.store, { 0, uint64_t(contractId), importedContractIds_offset, numImportedContracts, gas_limit });
	if (!maybe_contractInstance) {
		std::string msg = maybe_contractInstance.err().message();
		return nullptr;
	}
	WasmPtrT contractInstance = maybe_contractInstance.unwrap();
	if (!contractInstance) {
		return nullptr;
	}
#ifndef __APPLE__
	ContractRuntimeInstanceWASM* ret = (ContractRuntimeInstanceWASM*)ContractRuntimeInstance::GetThreadLocalMemoryPool()->allocate(sizeof(ContractRuntimeInstanceWASM));
	return new (ret) ContractRuntimeInstanceWASM(engine, *rt, m_entry_points, contractInstance);
#else
	return new ContractRuntimeInstanceWASM(engine, *rt, m_entry_points, contractInstance);
#endif
}

uint32_t ContractRuntimeInstanceWASM::InitGasTable(uint16_t* gas_cost_tbl, uint8_t gas_tbl_size) 
{
	wasmtime::Store::Context ctx = m_entry_points.store.context();
	std::vector<uint8_t> data(gas_tbl_size * 2);
	std::copy((uint8_t*)gas_cost_tbl, (uint8_t*)gas_cost_tbl + gas_tbl_size * 2, data.begin());
	m_gas_table.Resize(data.size());

	if (!m_gas_table.Valid()) {
		return (uint32_t)prlrt::ExecutionError::WASMTrapError;
	}
	std::copy(data.begin(), data.end(), m_gas_table.HostPtr());

	auto r = m_entry_points.fnInitGasTable.call(ctx, { m_gas_table.Ptr(), gas_tbl_size});
	if (!r) {
		std::string msg = r.err().message();
		return uint32_t(prlrt::ExecutionError::WASMTrapError);
	}
	return r.unwrap();
}

uint64_t ContractRuntimeInstanceWASM::GetRemainingGas()
{
	auto r = m_entry_points.fnGetRemainingGas.call(m_entry_points.store.context(), {});
	if(!r) return 0;
	return r.unwrap();
}

uint32_t ContractRuntimeInstanceWASM::SetRemainingGas(uint64_t remainingGas)
{
	auto r = m_entry_points.fnSetRemainingGas.call(m_entry_points.store.context(), {remainingGas});
	if (!r) {
		std::string msg = r.err().message();
		return uint32_t(prlrt::ExecutionError::WASMTrapError);
	}
	return r.unwrap();
}

uint32_t ContractRuntimeInstanceWASM::CommitJournaledStates(bool isGlobalContext) 
{
	m_engine.runtimeInterface().PushExecStack();
	auto r = m_entry_points.fnCommitJournaledStates.call(m_entry_points.store.context(), {m_wasm_contract, isGlobalContext});
	prlrt::ExceptionType exc = m_engine.runtimeInterface().PopExecStack();

	if (exc != prlrt::ExceptionType::NoException) {
		return uint32_t(prlrt::ExecutionError::RuntimeException) | (uint32_t(exc) << 8);
	}
	if(!r) return 0;
	return r.unwrap();	
}