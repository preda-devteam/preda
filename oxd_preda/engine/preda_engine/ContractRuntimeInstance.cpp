#include "ContractRuntimeInstance.h"
#include "ContractDatabaseEntry.h"
#include "ExecutionEngine.h"

class ContractModuleDLL : public ContractModule {
public:
	typedef void* (*FNCreateContractInstance)(prlrt::IRuntimeInterface* ____pInterface);
	typedef void* (*FNDestroyContractInstance)(void* pContractInstancce);
	typedef bool(*FNMapContractContextToInstance)(void* pInstance, prlrt::ContractContextType type, const uint8_t* buffer, uint32_t bufferSize);
	typedef uint32_t(*FNTransactionCall)(void* pContractInstance, uint32_t functionId, const uint8_t* args, uint32_t args_size);
	typedef uint32_t(*FNContractCall)(void* pContractInstance, uint32_t functionId, const void** ptrs, uint32_t numPtrs);
	typedef uint32_t(*FNGetContactStateSize)(void* pContractInstance, prlrt::ContractContextType type);
	typedef uint32_t(*FNGetContractContextSerializeSize)(void* pContractInstance, prlrt::ContractContextType type);
	typedef uint32_t(*FNSerializeOutContractContext)(void* pContractInstance, prlrt::ContractContextType type, uint8_t* buffer);

	FNCreateContractInstance fnCreateInstance;
	FNDestroyContractInstance fnDestroyContractInstance;
	FNMapContractContextToInstance fnMapContractContextToInstance;
	FNTransactionCall fnTransactionCall;
	FNContractCall fnContractCall;
	FNGetContractContextSerializeSize fnGetContractContextSerializeSize;
	FNSerializeOutContractContext fnSerializeOutContractContext;

	std::unique_ptr<ContractModuleLoaded> LoadToEngine(CExecutionEngine&) override;
};

class ContractModuleDLLLoaded : public ContractModuleLoaded {
private:
	ContractModuleDLL& m_dll;
public:
	ContractModuleDLLLoaded(ContractModuleDLL& dll) : m_dll(dll) {}
	std::unique_ptr<ContractRuntimeInstance> NewInstance(CExecutionEngine& engine) override;
};

std::unique_ptr<ContractModuleLoaded> ContractModuleDLL::LoadToEngine(CExecutionEngine&) {
	return std::make_unique<ContractModuleDLLLoaded>(*this);
}

std::unique_ptr<ContractModule> ContractModule::FromLibrary(const ContractDatabaseEntry& entry, HANDLE mod) {
	typedef void (*FNInitTables)(uint64_t curContractId, const uint64_t* importedContractIds);
	std::string exportUniqueStr = entry.compileData.exportUniqueString;
	FNInitTables InitTables = (FNInitTables)os::GetDynamicLibrarySymbol(mod, ("Contract_" + exportUniqueStr + "_InitTables").c_str());
	if (InitTables == nullptr)
		return nullptr;
	{
		const uint64_t curContractId = uint64_t(entry.deployData.contractId);
		static_assert(std::is_same_v<std::underlying_type_t<decltype(entry.deployData.contractId)>, std::remove_const_t<std::remove_reference_t<decltype(curContractId)>>>);
		const uint64_t* pImportedContractIds = entry.deployData.importedContractIds.size() > 0 ? (const uint64_t*)(&entry.deployData.importedContractIds[0]) : nullptr;
		InitTables(curContractId, pImportedContractIds);
	}

	std::unique_ptr<ContractModuleDLL> dllModule = std::make_unique<ContractModuleDLL>();

	dllModule->fnCreateInstance = (ContractModuleDLL::FNCreateContractInstance)os::GetDynamicLibrarySymbol(mod, ("Contract_" + exportUniqueStr + "_CreateInstance").c_str());
	dllModule->fnDestroyContractInstance = (ContractModuleDLL::FNDestroyContractInstance)os::GetDynamicLibrarySymbol(mod, ("Contract_" + exportUniqueStr + "_DestroyInstance").c_str());
	dllModule->fnMapContractContextToInstance = (ContractModuleDLL::FNMapContractContextToInstance)os::GetDynamicLibrarySymbol(mod, ("Contract_" + exportUniqueStr + "_MapContractContextToInstance").c_str());
	dllModule->fnTransactionCall = (ContractModuleDLL::FNTransactionCall)os::GetDynamicLibrarySymbol(mod, ("Contract_" + exportUniqueStr + "_TransactionCallEntry").c_str());
	dllModule->fnContractCall = (ContractModuleDLL::FNContractCall)os::GetDynamicLibrarySymbol(mod, ("Contract_" + exportUniqueStr + "_ContractCallEntry").c_str());
	dllModule->fnGetContractContextSerializeSize = (ContractModuleDLL::FNGetContractContextSerializeSize)os::GetDynamicLibrarySymbol(mod, ("Contract_" + exportUniqueStr + "_GetContractContextSerializeSize").c_str());
	dllModule->fnSerializeOutContractContext = (ContractModuleDLL::FNSerializeOutContractContext)os::GetDynamicLibrarySymbol(mod, ("Contract_" + exportUniqueStr + "_SerializeOutContractContext").c_str());
	if (dllModule->fnCreateInstance == nullptr
		|| dllModule->fnDestroyContractInstance == nullptr
		|| dllModule->fnMapContractContextToInstance == nullptr
		|| dllModule->fnTransactionCall == nullptr
		|| dllModule->fnContractCall == nullptr
		|| dllModule->fnGetContractContextSerializeSize == nullptr
		|| dllModule->fnSerializeOutContractContext == nullptr)
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
		delete this;
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
};


std::unique_ptr<ContractRuntimeInstance> ContractModuleDLLLoaded::NewInstance(CExecutionEngine& engine)  {
	void* pInstance = m_dll.fnCreateInstance(&engine.runtimeInterface());
	if (!pInstance) {
		return nullptr;
	}
	return std::make_unique<ContractRuntimeInstanceDLL>(m_dll, pInstance);
}

struct WASMEntryPoints {
	wasmtime::Store& store;

	wasmtime::Instance wasmInstance;

	wasmtime::TypedFunc<WasmPtrT, WasmPtrT> fnCreateContract;
	wasmtime::TypedFunc<WasmPtrT, std::monostate> fnDestroyContract;
	wasmtime::TypedFunc<std::tuple<WasmPtrT, uint32_t, WasmPtrT, uint32_t>, uint32_t> fnMapContractContextToInstance;
	wasmtime::TypedFunc<std::tuple<WasmPtrT, uint32_t, WasmPtrT, uint32_t>, uint32_t> fnTransactionCall;
	wasmtime::TypedFunc<std::tuple<WasmPtrT, uint32_t, WasmPtrT, uint32_t>, uint32_t> fnContractCall;
	wasmtime::TypedFunc<std::tuple<WasmPtrT, uint32_t>, uint32_t> fnGetContractSerializeSize;
	wasmtime::TypedFunc<std::tuple<WasmPtrT, uint32_t, WasmPtrT>, uint32_t> fnSerializeOutContract;

	using FnInitTables = wasmtime::TypedFunc<std::tuple<uint64_t, WasmPtrT>, std::monostate>;
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
	std::unique_ptr<ContractRuntimeInstance> NewInstance(CExecutionEngine&) override;
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

	if (
		!fnCreateContract ||
		!fnDestroyContract ||
		!fnMapContractContextToInstance ||
		!fnTransactionCall ||
		!fnContractCall ||
		!fnGetContractSerializeSize ||
		!fnSerializeOutContract ||
		!fnInitTables)
		return nullptr;

	{
		WasmPtrT importedContractIds_offset = 0;
		if (m_entry.deployData.importedContractIds.size() > 0) {
			auto& ids = m_entry.deployData.importedContractIds;
			WASMMemory mem(*rt, uint32_t(sizeof(ids[0]) * ids.size()));
			std::copy(ids.begin(), ids.end(), (rvm::ContractId*)mem.HostPtr());
			importedContractIds_offset = mem.Ptr();
			mem.forget();
		}
		if (!fnInitTables->call(rt->wasm_store(), { (uint64_t)m_entry.deployData.contractId, importedContractIds_offset })) {
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


};

ContractRuntimeInstanceWASM::ContractRuntimeInstanceWASM(
	CExecutionEngine& engine,
	WASMRuntime& rt,
	WASMEntryPoints &entry_points,
	WasmPtrT contract): m_engine(engine), m_rt(rt), m_entry_points(entry_points), m_wasm_contract(contract)
{
}

bool ContractRuntimeInstanceWASM::DestroyContractInstance()
{
	auto r = m_entry_points.fnDestroyContract.call(m_entry_points.store.context(), { m_wasm_contract });
	delete this;
	return bool(r);
}

bool ContractRuntimeInstanceWASM::MapContractContextToInstance(prlrt::ContractContextType type, const uint8_t* buffer, uint32_t bufferSize)
{
	wasmtime::Store::Context ctx = m_entry_points.store.context();
	WASMMemory mem(m_rt, bufferSize);

	if (!mem.Valid()) {
		return false;
	}

	std::copy(buffer, buffer + bufferSize, mem.HostPtr());

	auto r = m_entry_points.fnMapContractContextToInstance.call(ctx, {
		m_wasm_contract, (uint32_t)type, mem.Ptr(), bufferSize
	});
	if (!r || !r.unwrap()) {
		return false;
	}

	mem.forget();

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

	if (!r) {
		std::string msg = r.err().message();
		return uint32_t(prlrt::ExecutionError::RuntimeException) | (uint32_t(prlrt::ExecutionError::WASMTrapError) << 8);
	}
	if (exc != prlrt::ExceptionType::NoException) {
		return uint32_t(prlrt::ExecutionError::RuntimeException) | (uint32_t(exc) << 8);
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
	if (!r) {
		std::string msg = r.err().message();
		return uint32_t(prlrt::ExecutionError::RuntimeException) | (uint32_t(prlrt::ExecutionError::WASMTrapError) << 8);
	}
	if (exc != prlrt::ExceptionType::NoException) {
		return uint32_t(prlrt::ExecutionError::RuntimeException) | (uint32_t(exc) << 8);
	}

	return r.unwrap();
}

uint32_t ContractRuntimeInstanceWASM::GetContractContextSerializeSize(prlrt::ContractContextType type)
{
	auto r = m_entry_points.fnGetContractSerializeSize.call(m_entry_points.store.context(), { m_wasm_contract, (uint32_t)type });
	if (!r) {
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

	if (!r) {
		std::string msg = r.err().message();
		return uint32_t(prlrt::ExecutionError::RuntimeException) | (uint32_t(prlrt::ExecutionError::WASMTrapError) << 8);
	}
	if (exc != prlrt::ExceptionType::NoException) {
		return uint32_t(prlrt::ExecutionError::RuntimeException) | (uint32_t(exc) << 8);
	}

	std::copy(mem.HostPtr(), mem.HostPtr() + size, buffer);

	return r.unwrap();
}

template <typename T>
inline T WasmPtrToPtr(wasmtime::Span<uint8_t> mem, WasmPtrT offset) {
	return offset == 0 ? nullptr : (T)(mem.begin() + offset);
}

std::unique_ptr<ContractRuntimeInstance> ContractModuleWASMLoaded::NewInstance(CExecutionEngine& engine)
{
	WASMRuntime *rt = engine.wasm_runtime();
	if (!rt) {
		return nullptr;
	}

	auto maybe_contractInstance = m_entry_points.fnCreateContract.call(m_entry_points.store, { 0 });
	if (!maybe_contractInstance) {
		std::string msg = maybe_contractInstance.err().message();
		return nullptr;
	}
	WasmPtrT contractInstance = maybe_contractInstance.unwrap();
	if (!contractInstance) {
		return nullptr;
	}

	return std::make_unique<ContractRuntimeInstanceWASM>(engine, *rt, m_entry_points, contractInstance);
}
