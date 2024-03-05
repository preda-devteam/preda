#include "WASMRuntime.h"
#include "ExecutionEngine.h"
#include "ContractDatabase.h"

WASMRuntime::WASMRuntime(CExecutionEngine& engine,
	wasmtime::Engine& wasm_engine,
	wasmtime::Store wasm_store,
	wasmtime::Memory memory,
	wasmtime::Global stack_pointer,
	wasmtime::Global heap_base,
	wasmtime::Table indirect_function_table,
	wasmtime::TypedFunc<uint32_t, WasmPtrT> malloc,
	wasmtime::TypedFunc<WasmPtrT, std::monostate> free) :
	m_engine(engine),
	m_wasm_engine(wasm_engine),
	m_wasm_store(std::move(wasm_store)),
	m_memory(memory),
	m_stack_pointer(stack_pointer),
	m_heap_base(heap_base),
	m_indirect_function_table(indirect_function_table),
	m_malloc(malloc),
	m_free(free)
{
}

template <typename T>
inline T WasmPtrToPtr(wasmtime::Span<uint8_t> mem, WasmPtrT offset) {
	return offset == 0 ? nullptr : (T)(mem.begin() + offset);
}

inline uint32_t mem_align(uint32_t num_to_align, uint32_t align) {
	// https://stackoverflow.com/a/14878734
	uint32_t div_ceil = num_to_align / align + (num_to_align % align != 0);

	return div_ceil * align;
}

std::optional<wasmtime::Linker> WASMRuntime::CreateBaseLinker(CExecutionEngine& engine) {
	wasmtime::Linker linker(engine.contractDatabase()->wasm_engine());

	linker.allow_shadowing(true);

	if (!linker.func_wrap("wasi_snapshot_preview1", "proc_exit",
		[](int32_t) -> wasmtime::Result<std::monostate, wasmtime::Trap> {
			return wasmtime::Trap("Trapped");
		})) {
		return {};
	}

	if (!linker.func_wrap("env", "predaCreateBigint",
		[&engine]() -> uint64_t {
			return (uint64_t)engine.runtimeInterface().CreateBigint();
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaReleaseBigint",
		[&engine](uint64_t bigint) -> void {
			return engine.runtimeInterface().ReleaseBigint((prlrt::BigintPtr)bigint);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintAssign",
		[&engine](uint64_t self, uint64_t a) -> void {
			return engine.runtimeInterface().BigintAssign((prlrt::BigintPtr)self, (prlrt::BigintPtr)a);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintAssignInt64",
		[&engine](uint64_t self, int64_t a) -> void {
			return engine.runtimeInterface().BigintAssignInt64((prlrt::BigintPtr)self, a);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintAssignString",
		[&engine](wasmtime::Caller caller, uint64_t self, WasmPtrT str_offset, uint32_t len) -> void {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			const char* str = WasmPtrToPtr<const char*>(mem, str_offset);
			return engine.runtimeInterface().BigintAssignString((prlrt::BigintPtr)self, str, len);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintAssignUint64",
		[&engine](uint64_t self, uint64_t a) -> void {
			return engine.runtimeInterface().BigintAssignUint64((prlrt::BigintPtr)self, a);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintToInt64",
		[&engine](wasmtime::Caller caller, uint64_t self, WasmPtrT out_offset) -> int32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().BigintToInt64((prlrt::BigintPtr)self, WasmPtrToPtr<int64_t*>(mem, out_offset));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintToUint64",
		[&engine](wasmtime::Caller caller, uint64_t self, WasmPtrT out_offset) -> int32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().BigintToUint64((prlrt::BigintPtr)self, WasmPtrToPtr<uint64_t*>(mem, out_offset));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintAdd",
		[&engine](uint64_t self, uint64_t a, uint64_t b) -> void {
			return engine.runtimeInterface().BigintAdd((prlrt::BigintPtr)self, (prlrt::BigintPtr)a, (prlrt::BigintPtr)b);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintAddInplace",
		[&engine](uint64_t self, uint64_t a) -> void {
			return engine.runtimeInterface().BigintAddInplace((prlrt::BigintPtr)self, (prlrt::BigintPtr)a);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintSub",
		[&engine](uint64_t self, uint64_t a, uint64_t b) -> void {
			return engine.runtimeInterface().BigintSub((prlrt::BigintPtr)self, (prlrt::BigintPtr)a, (prlrt::BigintPtr)b);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintSubInplace",
		[&engine](uint64_t self, uint64_t a) -> void {
			return engine.runtimeInterface().BigintSubInplace((prlrt::BigintPtr)self, (prlrt::BigintPtr)a);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintMul",
		[&engine](uint64_t self, uint64_t a, uint64_t b) -> void {
			return engine.runtimeInterface().BigintMul((prlrt::BigintPtr)self, (prlrt::BigintPtr)a, (prlrt::BigintPtr)b);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintMul_Uint32",
		[&engine](uint64_t self, uint64_t a, uint32_t b) -> void {
			return engine.runtimeInterface().BigintMul_Uint32((prlrt::BigintPtr)self, (prlrt::BigintPtr)a, b);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintMul_Int32",
		[&engine](uint64_t self, uint64_t a, int32_t b) -> void {
			return engine.runtimeInterface().BigintMul_Int32((prlrt::BigintPtr)self, (prlrt::BigintPtr)a, b);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintShiftRightInplace",
		[&engine](uint64_t self, int a) -> void {
			return engine.runtimeInterface().BigintShiftRightInplace((prlrt::BigintPtr)self, a);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintShiftLeftInplace",
		[&engine](uint64_t self, int a) -> void {
			return engine.runtimeInterface().BigintShiftLeftInplace((prlrt::BigintPtr)self, a);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintMulInplace_Int32",
		[&engine](uint64_t self, int32_t a) -> void {
			return engine.runtimeInterface().BigintMulInplace_Int32((prlrt::BigintPtr)self, a);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintMulInplace_Uint32",
		[&engine](uint64_t self, uint32_t a) -> void {
			return engine.runtimeInterface().BigintMulInplace_Uint32((prlrt::BigintPtr)self, a);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintDiv",
		[&engine](uint64_t self, uint64_t a, uint64_t b, uint64_t remainder) -> void {
			return engine.runtimeInterface().BigintDiv((prlrt::BigintPtr)self, (prlrt::BigintPtr)a, (prlrt::BigintPtr)b, (prlrt::BigintPtr)remainder);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintDiv_Uint32",
		[&engine](wasmtime::Caller caller, uint64_t self, uint64_t a, uint32_t b, WasmPtrT remainder_offset) -> void {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().BigintDiv_Uint32((prlrt::BigintPtr)self, (prlrt::BigintPtr)a, b, WasmPtrToPtr<uint32_t*>(mem, remainder_offset));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintMod",
		[&engine](uint64_t self, uint64_t a, uint64_t b) -> void {
			return engine.runtimeInterface().BigintMod((prlrt::BigintPtr)self, (prlrt::BigintPtr)a, (prlrt::BigintPtr)b);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintNegate",
		[&engine](uint64_t self, uint64_t a) -> void {
			return engine.runtimeInterface().BigintNegate((prlrt::BigintPtr)self, (prlrt::BigintPtr)a);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintNegateInplace",
		[&engine](uint64_t self) -> void {
			return engine.runtimeInterface().BigintNegateInplace((prlrt::BigintPtr)self);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintIsNegative",
		[&engine](uint64_t self) -> uint32_t {
			return engine.runtimeInterface().BigintIsNegative((prlrt::BigintPtr)self);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintCompare",
		[&engine](uint64_t self, uint64_t a) -> int32_t {
			return engine.runtimeInterface().BigintCompare((prlrt::BigintPtr)self, (prlrt::BigintPtr)a);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintInitFromEmbedded",
		[&engine](wasmtime::Caller caller, uint64_t self, WasmPtrT in_offset, uint32_t in_size) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().BigintInitFromEmbedded((prlrt::BigintPtr)self, WasmPtrToPtr<const uint8_t*>(mem, in_offset), in_size);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintGetEmbeddedSize",
		[&engine](wasmtime::Caller caller, uint64_t self) -> uint32_t {
			return engine.runtimeInterface().BigintGetEmbeddedSize((prlrt::BigintPtr)self);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintEmbed",
		[&engine](wasmtime::Caller caller, uint64_t self, WasmPtrT out_offset) -> void {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().BigintEmbed((prlrt::BigintPtr)self, WasmPtrToPtr<uint8_t*>(mem, out_offset));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintIsEmbeddable",
		[&engine](wasmtime::Caller caller, uint64_t self) -> uint32_t {
			return engine.runtimeInterface().BigintIsEmbeddable((prlrt::BigintPtr)self);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintGetStringLength",
		[&engine](wasmtime::Caller caller, uint64_t self) -> uint32_t {
			return engine.runtimeInterface().BigintGetStringLength((prlrt::BigintPtr)self);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBigintToString",
		[&engine](wasmtime::Caller caller, uint64_t self, WasmPtrT out_offset, uint32_t size) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().BigintToString((prlrt::BigintPtr)self, WasmPtrToPtr<char*>(mem, out_offset), size);
		})) {
		return {};
	}

	if (!linker.func_wrap("env", "predaInitAddressFromLiteral",
		[&engine](wasmtime::Caller caller, WasmPtrT address_offset, WasmPtrT str_offset) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().InitAddressFromLiteral(WasmPtrToPtr<void*>(mem, address_offset), WasmPtrToPtr<const char*>(mem, str_offset));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaInitHashFromLiteral",
		[&engine](wasmtime::Caller caller, WasmPtrT hash_offset, WasmPtrT str_offset) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().InitHashFromLiteral(WasmPtrToPtr<void*>(mem, hash_offset), WasmPtrToPtr<const char*>(mem, str_offset));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaStringToAddress",
		[&engine](wasmtime::Caller caller, WasmPtrT address_offset, WasmPtrT data_offset, uint32_t data_len) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().StringToAddress(WasmPtrToPtr<void*>(mem, address_offset), WasmPtrToPtr<const char*>(mem, data_offset), data_len);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaGetAddressToStringLength",
		[&engine](wasmtime::Caller caller, WasmPtrT address_offset) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().GetAddressToStringLength(WasmPtrToPtr<const void*>(mem, address_offset));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaAddressToString",
		[&engine](wasmtime::Caller caller, WasmPtrT address_offset, uint32_t data_len, WasmPtrT out_offset) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().AddressToString(WasmPtrToPtr<const void*>(mem, address_offset), data_len, WasmPtrToPtr<char*>(mem, out_offset));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaGetHashToStringLength",
		[&engine](wasmtime::Caller caller) -> uint32_t {
			return engine.runtimeInterface().GetHashToStringLength();
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaHashToString",
		[&engine](wasmtime::Caller caller, WasmPtrT data_offset, uint32_t data_len, WasmPtrT out_offset) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().HashToString(WasmPtrToPtr<const void*>(mem, data_offset), data_len, WasmPtrToPtr<char*>(mem, out_offset));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaCalculateHash",
		[&engine](wasmtime::Caller caller, WasmPtrT hash_offset, WasmPtrT data_offset, uint32_t data_len) -> void {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().CalculateHash(WasmPtrToPtr<void*>(mem, hash_offset), WasmPtrToPtr<const uint8_t*>(mem, data_offset), data_len);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaEmitRelayToScope",
		[&engine](wasmtime::Caller caller, WasmPtrT scope_key_offset, uint32_t scope_key_size, uint32_t scope_type, uint32_t op_code, WasmPtrT args_serialized_offset, uint32_t args_size) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().EmitRelayToScope(WasmPtrToPtr<const uint8_t*>(mem, scope_key_offset), scope_key_size, scope_type, op_code, WasmPtrToPtr<const uint8_t*>(mem, args_serialized_offset), args_size);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaEmitRelayToGlobal",
		[&engine](wasmtime::Caller caller, uint32_t op_code, WasmPtrT args_serialized_offset, uint32_t args_size) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().EmitRelayToGlobal(op_code, WasmPtrToPtr<const uint8_t*>(mem, args_serialized_offset), args_size);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaEmitRelayDeferred",
		[&engine](wasmtime::Caller caller, uint32_t op_code, WasmPtrT args_serialized_offset, uint32_t args_size) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().EmitRelayDeferred(op_code, WasmPtrToPtr<const uint8_t*>(mem, args_serialized_offset), args_size);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaEmitRelayToShards",
		[&engine](wasmtime::Caller caller, uint32_t op_code, WasmPtrT args_serialized_offset, uint32_t args_size) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().EmitRelayToShards(op_code, WasmPtrToPtr<const uint8_t*>(mem, args_serialized_offset), args_size);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaCrossCall",
		[&engine](wasmtime::Caller caller, uint64_t cvId, int64_t templateContractImportSlot, uint32_t opCode, WasmPtrT ptrs, uint32_t numPtrs) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().CrossCall(cvId, templateContractImportSlot, opCode,
				reinterpret_cast<const void**>(static_cast<uintptr_t>(ptrs)), numPtrs);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaInterfaceCall",
		[&engine](wasmtime::Caller caller, uint64_t contractId, int64_t interfaceContractImportSlot, uint32_t interfaceSlot, uint32_t funcIdx, WasmPtrT ptrs, uint32_t numPtrs) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().InterfaceCall(contractId,
				interfaceContractImportSlot, interfaceSlot, funcIdx,
				reinterpret_cast<const void**>(static_cast<uintptr_t>(ptrs)), numPtrs);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaContractImplementsInterface",
		[&engine](wasmtime::Caller caller, uint64_t contractId, int64_t interfaceContractImportSlot, uint32_t interfaceSlot) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().ContractImplementsInterface(contractId,
				interfaceContractImportSlot, interfaceSlot);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaContractHasTemplate",
		[&engine](wasmtime::Caller caller, uint64_t contractId, int64_t templateContractImportSlot) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().ContractHasTemplate(contractId,
				templateContractImportSlot);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaDeployCall",
		[&engine](wasmtime::Caller caller, int64_t templateContractImportSlot, WasmPtrT ptrs, uint32_t numPtrs) -> uint64_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().DeployCall(templateContractImportSlot,
				reinterpret_cast<const void**>(static_cast<uintptr_t>(ptrs)), numPtrs);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaReportOrphanToken",
		[&engine](wasmtime::Caller caller, uint64_t id, uint64_t amount) {
			engine.runtimeInterface().ReportOrphanToken(id, (prlrt::BigintPtr)(amount));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaDepositToken",
		[&engine](wasmtime::Caller caller, uint64_t id, uint64_t amount) {
			engine.runtimeInterface().DepositToken(id, (prlrt::BigintPtr)(amount));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaTokenMinted",
		[&engine](wasmtime::Caller caller, uint64_t id, uint64_t amount) {
			engine.runtimeInterface().TokenMinted(id, (prlrt::BigintPtr)(amount));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaTokenBurnt",
		[&engine](wasmtime::Caller caller, uint64_t id, uint64_t amount) {
			engine.runtimeInterface().TokenBurnt(id, (prlrt::BigintPtr)(amount));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaTokenIdToSymbolLength",
		[&engine](wasmtime::Caller caller, uint64_t id) -> uint32_t {
			return engine.runtimeInterface().TokenIdToSymbolLength(id);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaTokenSymbolToId",
		[&engine](wasmtime::Caller caller, WasmPtrT symbol_offset) -> uint64_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			const char* symbol = WasmPtrToPtr<const char*>(mem, symbol_offset);
			return engine.runtimeInterface().TokenSymbolToId(symbol);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaAllowedToMint",
		[&engine](wasmtime::Caller caller, uint64_t id) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().AllowedToMint(id);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaReportReturnValue",
		[&engine](wasmtime::Caller caller, WasmPtrT type_name_offset, WasmPtrT data_offset, uint32_t size) {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			const char* type_name = WasmPtrToPtr<const char*>(mem, type_name_offset);
			const uint8_t* data = WasmPtrToPtr<const uint8_t*>(mem, data_offset);
			engine.runtimeInterface().ReportReturnValue(type_name, data, size);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaDebugPrintBufferAppendSerializedData",
		[&engine](wasmtime::Caller caller, WasmPtrT type_name_offset, WasmPtrT data_offset, uint32_t size) {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			const char* type_name = WasmPtrToPtr<const char*>(mem, type_name_offset);
			const uint8_t* data = WasmPtrToPtr<const uint8_t*>(mem, data_offset);
			engine.runtimeInterface().DebugPrintBufferAppendSerializedData(type_name, data, size);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaDebugPrintOutputBuffer",
		[&engine](wasmtime::Caller caller, uint32_t line) {
			engine.runtimeInterface().DebugPrintOutputBuffer(line);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaDebugAssertionFailure",
		[&engine](wasmtime::Caller caller, uint32_t line) {
			engine.runtimeInterface().DebugAssertionFailure(line);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaDebugAssertionFailureMessage",
		[&engine](wasmtime::Caller caller, uint32_t line, WasmPtrT message_offset, uint32_t length) {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			const char* message = WasmPtrToPtr<const char*>(mem, message_offset);
			engine.runtimeInterface().DebugAssertionFailureMessage(line, message, length);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaIsUserAddress",
		[&engine](wasmtime::Caller caller, WasmPtrT address_offset) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().IsUserAddress(WasmPtrToPtr<const void*>(mem, address_offset));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaIsDelegatedAddress",
		[&engine](wasmtime::Caller caller, WasmPtrT address_offset) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().IsDelegatedAddress(WasmPtrToPtr<const void*>(mem, address_offset));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaIsDAppAddress",
		[&engine](wasmtime::Caller caller, WasmPtrT address_offset) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().IsDAppAddress(WasmPtrToPtr<const void*>(mem, address_offset));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaIsAssetAddress",
		[&engine](wasmtime::Caller caller, WasmPtrT address_offset) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().IsAssetAddress(WasmPtrToPtr<const void*>(mem, address_offset));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaIsNameAddress",
		[&engine](wasmtime::Caller caller, WasmPtrT address_offset) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().IsNameAddress(WasmPtrToPtr<const void*>(mem, address_offset));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaIsContractAddress",
		[&engine](wasmtime::Caller caller, WasmPtrT address_offset) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().IsContractAddress(WasmPtrToPtr<const void*>(mem, address_offset));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaIsCustomAddress",
		[&engine](wasmtime::Caller caller, WasmPtrT address_offset) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().IsCustomAddress(WasmPtrToPtr<const void*>(mem, address_offset));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaSetAsContractAddress",
		[&engine](wasmtime::Caller caller, WasmPtrT address_offset, uint64_t contract_id) -> void {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().SetAsContractAddress(WasmPtrToPtr<void*>(mem, address_offset), contract_id);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaSetAsCustomAddress",
		[&engine](wasmtime::Caller caller, WasmPtrT address_offset, WasmPtrT data_offset) -> void {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().SetAsCustomAddress(WasmPtrToPtr<void*>(mem, address_offset), WasmPtrToPtr<const uint8_t*>(mem, data_offset));
		})) {
		return {};
	}

#define _DEFINE_FLOAT_METHOD(_BIT)\
	if (!linker.func_wrap("env", "predaGetConvertToStringLen_" # _BIT,\
	[&engine](wasmtime::Caller caller, WasmPtrT pftemp_offset) -> uint32_t {\
		wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
		return engine.runtimeInterface().GetConvertToStringLen_##_BIT(WasmPtrToPtr<const ::prlrt::PrecisionFloatInternal<_BIT>*>(mem, pftemp_offset));\
	})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "predaConvertToString_" # _BIT,\
	[&engine](wasmtime::Caller caller, WasmPtrT pftemp_offset, WasmPtrT buf_offset) -> void {\
		wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
		return engine.runtimeInterface().ConvertToString_##_BIT(WasmPtrToPtr<const ::prlrt::PrecisionFloatInternal<_BIT>*>(mem, pftemp_offset), WasmPtrToPtr<char*>(mem, buf_offset));\
	})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "predaConvertFromString_" # _BIT,\
	[&engine](wasmtime::Caller caller, WasmPtrT pftemp_offset, WasmPtrT buf_offset) -> void {\
		wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
		return engine.runtimeInterface().ConvertFromString_##_BIT(WasmPtrToPtr<::prlrt::PrecisionFloatInternal<_BIT>*>(mem, pftemp_offset), WasmPtrToPtr<const char*>(mem, buf_offset));\
	})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "predaFloat_Add_" # _BIT,\
	[&engine](wasmtime::Caller caller, WasmPtrT a_offset, WasmPtrT b_offset, WasmPtrT result_offset) -> void {\
		wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
		return engine.runtimeInterface().Float_Add_##_BIT(WasmPtrToPtr<const ::prlrt::PrecisionFloatInternal<_BIT>*>(mem, a_offset), WasmPtrToPtr<const ::prlrt::PrecisionFloatInternal<_BIT>*>(mem, b_offset), WasmPtrToPtr<::prlrt::PrecisionFloatInternal<_BIT>*>(mem, result_offset));\
	})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "predaFloat_Sub_" # _BIT,\
	[&engine](wasmtime::Caller caller, WasmPtrT a_offset, WasmPtrT b_offset, WasmPtrT result_offset) -> void {\
		wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
		return engine.runtimeInterface().Float_Sub_##_BIT(WasmPtrToPtr<const ::prlrt::PrecisionFloatInternal<_BIT>*>(mem, a_offset), WasmPtrToPtr<const ::prlrt::PrecisionFloatInternal<_BIT>*>(mem, b_offset), WasmPtrToPtr<::prlrt::PrecisionFloatInternal<_BIT>*>(mem, result_offset));\
	})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "predaFloat_Mul_" # _BIT,\
	[&engine](wasmtime::Caller caller, WasmPtrT a_offset, WasmPtrT b_offset, WasmPtrT result_offset) -> void {\
		wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
		return engine.runtimeInterface().Float_Mul_##_BIT(WasmPtrToPtr<const ::prlrt::PrecisionFloatInternal<_BIT>*>(mem, a_offset), WasmPtrToPtr<const ::prlrt::PrecisionFloatInternal<_BIT>*>(mem, b_offset), WasmPtrToPtr<::prlrt::PrecisionFloatInternal<_BIT>*>(mem, result_offset));\
	})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "predaFloat_Div_" # _BIT,\
	[&engine](wasmtime::Caller caller, WasmPtrT a_offset, WasmPtrT b_offset, WasmPtrT result_offset) -> void {\
		wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
		return engine.runtimeInterface().Float_Div_##_BIT(WasmPtrToPtr<const ::prlrt::PrecisionFloatInternal<_BIT>*>(mem, a_offset), WasmPtrToPtr<const ::prlrt::PrecisionFloatInternal<_BIT>*>(mem, b_offset), WasmPtrToPtr<::prlrt::PrecisionFloatInternal<_BIT>*>(mem, result_offset));\
	})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "predaFloat_Zero_" # _BIT,\
	[&engine](wasmtime::Caller caller, WasmPtrT a_offset) -> void {\
		wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
		return engine.runtimeInterface().Float_Zero_##_BIT(WasmPtrToPtr<::prlrt::PrecisionFloatInternal<_BIT>*>(mem, a_offset));\
	})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "predaFloat_IsZero_" # _BIT,\
	[&engine](wasmtime::Caller caller, WasmPtrT a_offset) -> uint32_t {\
		wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
		return engine.runtimeInterface().Float_IsZero_##_BIT(WasmPtrToPtr<::prlrt::PrecisionFloatInternal<_BIT>*>(mem, a_offset));\
	})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "predaFloat_Negate_" # _BIT,\
	[&engine](wasmtime::Caller caller, WasmPtrT a_offset, WasmPtrT result_offset) -> void {\
		wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
		return engine.runtimeInterface().Float_Negate_##_BIT(WasmPtrToPtr<const ::prlrt::PrecisionFloatInternal<_BIT>*>(mem, a_offset), WasmPtrToPtr<::prlrt::PrecisionFloatInternal<_BIT>*>(mem, result_offset));\
	})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "predaFloat_Compare_" # _BIT,\
		[&engine](wasmtime::Caller caller, WasmPtrT a_offset, WasmPtrT b_offset) -> int32_t {\
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
			return engine.runtimeInterface().Float_Compare_##_BIT(WasmPtrToPtr<const ::prlrt::PrecisionFloatInternal<_BIT>*>(mem, a_offset), WasmPtrToPtr<const ::prlrt::PrecisionFloatInternal<_BIT>*>(mem, b_offset));\
		})) {\
		return {};\
	}\

	_DEFINE_FLOAT_METHOD(256)
	_DEFINE_FLOAT_METHOD(512)
	_DEFINE_FLOAT_METHOD(1024)
#undef _DEFINE_FLOAT_METHOD

#define _LONGINT_NEGATE_FUNC(_SIZE)\
	if (!linker.func_wrap("env", "predaLongInt_Negate_" # _SIZE,\
		[&engine](wasmtime::Caller caller, WasmPtrT a_offset, WasmPtrT b_offset) -> void {\
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
			return engine.runtimeInterface().LongInt_Negate_##_SIZE(WasmPtrToPtr<const ::prlrt::LongIntInternal<_SIZE>*>(mem, a_offset), WasmPtrToPtr<::prlrt::LongIntInternal<_SIZE>*>(mem, b_offset));\
		})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "predaLongInt_IsSign_" # _SIZE,\
	[&engine](wasmtime::Caller caller, WasmPtrT a_offset) -> uint32_t {\
		wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
		return engine.runtimeInterface().LongInt_IsSign_##_SIZE(WasmPtrToPtr<::prlrt::LongIntInternal<_SIZE>*>(mem, a_offset));\
	})) {\
		return {};\
	}\

	_LONGINT_NEGATE_FUNC(128)
	_LONGINT_NEGATE_FUNC(256)
	_LONGINT_NEGATE_FUNC(512)
#undef _LONGINT_NEGATE_FUNC

#define _LONGINTIMPLFUNC(_SIZE, _INT_TYPE) \
	if (!linker.func_wrap("env", "preda" # _INT_TYPE "_Zero_" # _SIZE,\
		[&engine](wasmtime::Caller caller, WasmPtrT a_offset) -> void {\
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
			return engine.runtimeInterface()._INT_TYPE##_Zero_##_SIZE(WasmPtrToPtr<::prlrt::LongIntInternal<_SIZE>*>(mem, a_offset));\
		})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "preda" # _INT_TYPE "_ConvertFromString_" # _SIZE,\
		[&engine](wasmtime::Caller caller, WasmPtrT a_offset, WasmPtrT longint_literal_offset) -> void {\
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
			return engine.runtimeInterface()._INT_TYPE##_ConvertFromString_##_SIZE(WasmPtrToPtr<::prlrt::LongIntInternal<_SIZE>*>(mem, a_offset), WasmPtrToPtr<const char*>(mem, longint_literal_offset));\
		})) {\
		return {};\
	}\
    if (!linker.func_wrap("env", "preda" # _INT_TYPE "_fromInt_" # _SIZE,\
		[&engine](wasmtime::Caller caller, WasmPtrT a_offset, int64_t in) -> void {\
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
			return engine.runtimeInterface()._INT_TYPE##_fromInt_##_SIZE(WasmPtrToPtr<::prlrt::LongIntInternal<_SIZE>*>(mem, a_offset), in);\
		})) {\
		return {};\
	}\
    if (!linker.func_wrap("env", "preda" # _INT_TYPE "_fromUInt_" # _SIZE,\
		[&engine](wasmtime::Caller caller, WasmPtrT a_offset, uint64_t in) -> void {\
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
			return engine.runtimeInterface()._INT_TYPE##_fromUInt_##_SIZE(WasmPtrToPtr<::prlrt::LongIntInternal<_SIZE>*>(mem, a_offset), in);\
		})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "preda" # _INT_TYPE "_toInt64_" # _SIZE,\
		[&engine](wasmtime::Caller caller, WasmPtrT a_offset, WasmPtrT result_offset) -> int {\
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
			return engine.runtimeInterface()._INT_TYPE##_toInt64_##_SIZE(WasmPtrToPtr<::prlrt::LongIntInternal<_SIZE>*>(mem, a_offset), WasmPtrToPtr<int64_t*>(mem, result_offset));\
		})) {\
		return {};\
	}\
    if (!linker.func_wrap("env", "preda" # _INT_TYPE "_toUInt64_" # _SIZE,\
		[&engine](wasmtime::Caller caller, WasmPtrT a_offset, WasmPtrT result_offset) -> int {\
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
			return engine.runtimeInterface()._INT_TYPE##_toUInt64_##_SIZE(WasmPtrToPtr<::prlrt::LongIntInternal<_SIZE>*>(mem, a_offset), WasmPtrToPtr<uint64_t*>(mem, result_offset));\
		})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "preda" # _INT_TYPE "_rightShift_" # _SIZE,\
		[&engine](wasmtime::Caller caller, WasmPtrT a_offset, int64_t shift) -> void {\
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
			return engine.runtimeInterface()._INT_TYPE##_rightShift_##_SIZE(WasmPtrToPtr<::prlrt::LongIntInternal<_SIZE>*>(mem, a_offset), shift);\
		})) {\
		return {};\
	}\
    if (!linker.func_wrap("env", "preda" # _INT_TYPE "_leftShift_" # _SIZE,\
		[&engine](wasmtime::Caller caller, WasmPtrT a_offset, int64_t shift) -> void {\
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
			return engine.runtimeInterface()._INT_TYPE##_leftShift_##_SIZE(WasmPtrToPtr<::prlrt::LongIntInternal<_SIZE>*>(mem, a_offset), shift);\
		})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "preda" # _INT_TYPE "_ConvertFromHexString_" # _SIZE,\
		[&engine](wasmtime::Caller caller, WasmPtrT a_offset, WasmPtrT longint_literal_offset) -> void {\
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
			return engine.runtimeInterface()._INT_TYPE##_ConvertFromHexString_##_SIZE(WasmPtrToPtr<::prlrt::LongIntInternal<_SIZE>*>(mem, a_offset), WasmPtrToPtr<const char*>(mem, longint_literal_offset));\
		})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "preda" # _INT_TYPE "_ConvertToString_" # _SIZE,\
		[&engine](wasmtime::Caller caller, WasmPtrT a_offset, WasmPtrT longint_literal_offset) -> void {\
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
			return engine.runtimeInterface()._INT_TYPE##_ConvertToString_##_SIZE(WasmPtrToPtr<const ::prlrt::LongIntInternal<_SIZE>*>(mem, a_offset), WasmPtrToPtr<char*>(mem, longint_literal_offset));\
		})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "preda" # _INT_TYPE "_GetConvertToStringLen_" # _SIZE,\
		[&engine](wasmtime::Caller caller, WasmPtrT a_offset) -> uint32_t {\
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
			return engine.runtimeInterface()._INT_TYPE##_GetConvertToStringLen_##_SIZE(WasmPtrToPtr<const ::prlrt::LongIntInternal<_SIZE>*>(mem, a_offset));\
		})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "preda" # _INT_TYPE "_IsZero_" # _SIZE,\
		[&engine](wasmtime::Caller caller, WasmPtrT a_offset) -> uint32_t {\
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
			return engine.runtimeInterface()._INT_TYPE##_IsZero_##_SIZE(WasmPtrToPtr<const ::prlrt::LongIntInternal<_SIZE>*>(mem, a_offset));\
		})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "preda" # _INT_TYPE "_Add_" # _SIZE,\
		[&engine](wasmtime::Caller caller, WasmPtrT a_offset, WasmPtrT b_offset, WasmPtrT result_offset) -> void {\
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
			return engine.runtimeInterface()._INT_TYPE##_Add_##_SIZE(WasmPtrToPtr<const ::prlrt::LongIntInternal<_SIZE>*>(mem, a_offset), WasmPtrToPtr<const ::prlrt::LongIntInternal<_SIZE>*>(mem, b_offset), WasmPtrToPtr<::prlrt::LongIntInternal<_SIZE>*>(mem, result_offset));\
		})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "preda" # _INT_TYPE "_Sub_" # _SIZE,\
		[&engine](wasmtime::Caller caller, WasmPtrT a_offset, WasmPtrT b_offset, WasmPtrT result_offset) -> void {\
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
			return engine.runtimeInterface()._INT_TYPE##_Sub_##_SIZE(WasmPtrToPtr<const ::prlrt::LongIntInternal<_SIZE>*>(mem, a_offset), WasmPtrToPtr<const ::prlrt::LongIntInternal<_SIZE>*>(mem, b_offset), WasmPtrToPtr<::prlrt::LongIntInternal<_SIZE>*>(mem, result_offset));\
		})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "preda" # _INT_TYPE "_Mul_" # _SIZE,\
		[&engine](wasmtime::Caller caller, WasmPtrT a_offset, WasmPtrT b_offset, WasmPtrT result_offset) -> void {\
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
			return engine.runtimeInterface()._INT_TYPE##_Mul_##_SIZE(WasmPtrToPtr<const ::prlrt::LongIntInternal<_SIZE>*>(mem, a_offset), WasmPtrToPtr<const ::prlrt::LongIntInternal<_SIZE>*>(mem, b_offset), WasmPtrToPtr<::prlrt::LongIntInternal<_SIZE>*>(mem, result_offset));\
		})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "preda" # _INT_TYPE "_Div_" # _SIZE,\
		[&engine](wasmtime::Caller caller, WasmPtrT a_offset, WasmPtrT b_offset, WasmPtrT result_offset) -> void {\
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
			return engine.runtimeInterface()._INT_TYPE##_Div_##_SIZE(WasmPtrToPtr<const ::prlrt::LongIntInternal<_SIZE>*>(mem, a_offset), WasmPtrToPtr<const ::prlrt::LongIntInternal<_SIZE>*>(mem, b_offset), WasmPtrToPtr<::prlrt::LongIntInternal<_SIZE>*>(mem, result_offset));\
		})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "preda" # _INT_TYPE "_Mod_" # _SIZE,\
		[&engine](wasmtime::Caller caller, WasmPtrT a_offset, WasmPtrT b_offset, WasmPtrT result_offset) -> void {\
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
			return engine.runtimeInterface()._INT_TYPE##_Mod_##_SIZE(WasmPtrToPtr<const ::prlrt::LongIntInternal<_SIZE>*>(mem, a_offset), WasmPtrToPtr<const ::prlrt::LongIntInternal<_SIZE>*>(mem, b_offset), WasmPtrToPtr<::prlrt::LongIntInternal<_SIZE>*>(mem, result_offset));\
		})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "preda" # _INT_TYPE "_Compare_" # _SIZE,\
		[&engine](wasmtime::Caller caller, WasmPtrT a_offset, WasmPtrT b_offset) -> int32_t {\
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
			return engine.runtimeInterface()._INT_TYPE##_Compare_##_SIZE(WasmPtrToPtr<const ::prlrt::LongIntInternal<_SIZE>*>(mem, a_offset), WasmPtrToPtr<const ::prlrt::LongIntInternal<_SIZE>*>(mem, b_offset));\
		})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "preda" # _INT_TYPE "_SetMax_" # _SIZE,\
		[&engine](wasmtime::Caller caller, WasmPtrT a_offset) -> void {\
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
			return engine.runtimeInterface()._INT_TYPE##_SetMax_##_SIZE(WasmPtrToPtr<::prlrt::LongIntInternal<_SIZE>*>(mem, a_offset));\
		})) {\
		return {};\
	}\
	if (!linker.func_wrap("env", "preda" # _INT_TYPE "_SetMin_" # _SIZE,\
		[&engine](wasmtime::Caller caller, WasmPtrT a_offset) -> void {\
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());\
			return engine.runtimeInterface()._INT_TYPE##_SetMin_##_SIZE(WasmPtrToPtr<::prlrt::LongIntInternal<_SIZE>*>(mem, a_offset));\
		})) {\
		return {};\
	}\

	_LONGINTIMPLFUNC(128, LongInt)
	_LONGINTIMPLFUNC(256, LongInt)
	_LONGINTIMPLFUNC(512, LongInt)
	_LONGINTIMPLFUNC(128, ULongInt)
	_LONGINTIMPLFUNC(256, ULongInt)
	_LONGINTIMPLFUNC(512, ULongInt)

#undef _LONGINTIMPLFUNC

	if (!linker.func_wrap("env", "predaBlock_GetHeight",
		[&engine](wasmtime::Caller caller) -> uint64_t {
			return engine.runtimeInterface().Block_GetHeight();
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBlock_GetShardIndex",
		[&engine](wasmtime::Caller caller) -> uint32_t {
			return engine.runtimeInterface().Block_GetShardIndex();
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBlock_GetShardOrder",
		[&engine](wasmtime::Caller caller) -> uint32_t {
			return engine.runtimeInterface().Block_GetShardOrder();
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBlock_GetTimestamp",
		[&engine](wasmtime::Caller caller) -> uint64_t {
			return engine.runtimeInterface().Block_GetTimestamp();
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBlock_GetRandomNumber",
		[&engine](wasmtime::Caller caller) -> uint64_t {
			return engine.runtimeInterface().Block_GetRandomNumber();
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaBlock_GetMinerAddress",
		[&engine](wasmtime::Caller caller, WasmPtrT out_offset) -> void {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().Block_GetMinerAddress(WasmPtrToPtr<uint8_t*>(mem, out_offset));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaTransaction_GetType",
		[&engine](wasmtime::Caller caller) -> uint32_t {
			return (uint32_t)engine.runtimeInterface().Transaction_GetType();
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaTransaction_GetSelfAddress",
		[&engine](wasmtime::Caller caller, WasmPtrT out_offset) -> void {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().Transaction_GetSelfAddress(WasmPtrToPtr<uint8_t*>(mem, out_offset));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaTransaction_GetSender",
		[&engine](wasmtime::Caller caller, WasmPtrT out_offset) -> void {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().Transaction_GetSender(WasmPtrToPtr<uint8_t*>(mem, out_offset));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaTransaction_GetTimeStamp",
		[&engine](wasmtime::Caller caller) -> uint64_t {
			return engine.runtimeInterface().Transaction_GetTimeStamp();
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaTransaction_GetSigner",
		[&engine](wasmtime::Caller caller, uint32_t signerIdx, WasmPtrT out_offset) -> void {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().Transaction_GetSigner(signerIdx, WasmPtrToPtr<uint8_t*>(mem, out_offset));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaTransaction_GetSignerCount",
		[&engine](wasmtime::Caller caller) -> uint32_t {
			return engine.runtimeInterface().Transaction_GetSignerCount();
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaTransaction_VerifySignerByIndex",
		[&engine](wasmtime::Caller caller, uint32_t signerIdx) -> uint32_t {
			return engine.runtimeInterface().Transaction_VerifySignerByIndex(signerIdx);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaTransaction_VerifySignerByAddress",
		[&engine](wasmtime::Caller caller, WasmPtrT pSignerAddress) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());

			return engine.runtimeInterface().Transaction_VerifySignerByAddress(WasmPtrToPtr<const uint8_t*>(mem, pSignerAddress));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaTransaction_GetOriginatedShardIndex",
		[&engine](wasmtime::Caller caller) -> uint32_t {
			return engine.runtimeInterface().Transaction_GetOriginatedShardIndex();
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaTransaction_GetOriginatedShardOrder",
		[&engine](wasmtime::Caller caller) -> uint32_t {
			return engine.runtimeInterface().Transaction_GetOriginatedShardOrder();
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaTransaction_GetInitiatorAddress",
		[&engine](wasmtime::Caller caller, WasmPtrT out_offset) -> void {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().Transaction_GetInitiatorAddress(WasmPtrToPtr<uint8_t*>(mem, out_offset));
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaTransaction_GetSuppliedTokensCount",
		[&engine](wasmtime::Caller caller) -> uint32_t {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().Transaction_GetSuppliedTokensCount();
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaTransaction_GetSuppliedToken",
		[&engine](wasmtime::Caller caller, uint32_t index, WasmPtrT id, uint64_t amount) -> void {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			return engine.runtimeInterface().Transaction_GetSuppliedToken(index, WasmPtrToPtr<uint64_t*>(mem, id), (prlrt::BigintPtr)amount);
		})) {
		return {};
	}

	if (!linker.func_wrap("env", "predaEvent_GetUserState",
		[&engine](wasmtime::Caller caller) -> uint32_t {
			return (uint32_t)engine.runtimeInterface().Event_GetUserState();
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaEvent_Push",
		[&engine](wasmtime::Caller caller, uint32_t id, WasmPtrT data_offset, uint32_t data_len) {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			const char* data = WasmPtrToPtr<const char*>(mem, data_offset);
			engine.runtimeInterface().Event_Push(id, data, data_len);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaEvent_Notify",
		[&engine](wasmtime::Caller caller, uint32_t id, WasmPtrT data_offset, uint32_t data_len) {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			const char* data = WasmPtrToPtr<const char*>(mem, data_offset);
			engine.runtimeInterface().Event_Notify(id, data, data_len);
		})) {
		return {};
	}
	if (!linker.func_wrap("env", "predaEvent_Exception",
		[&engine](wasmtime::Caller caller, WasmPtrT msg_offset, uint32_t type) {
			wasmtime::Span<uint8_t> mem = engine.wasm_runtime()->memory().data(caller.context());
			const char* msg = WasmPtrToPtr<const char*>(mem, msg_offset);
			engine.runtimeInterface().Event_Exception(msg, prlrt::ExceptionType(type));
		})) {
		return {};
	}


	return linker;
}

std::optional<wasmtime::Instance> WASMRuntime::Instantiate(wasmtime::Module& mod)
{
	std::optional<wasmtime::Linker>& maybe_linker = m_engine.base_linker();
	if (!maybe_linker) {
		return {};
	}

	wasmtime::Linker& linker = *maybe_linker;

	if (!linker.define("env", "malloc", m_malloc.func())) {
		return {};
	}
	if (!linker.define("env", "free", m_free.func())) {
		return {};
	}
	if (!linker.define("env", "__stack_pointer", m_stack_pointer)) {
		return {};
	}

	auto dylink = mod.dylinkInfo();
	if (!dylink) {
		return {};
	}

	constexpr uint32_t STACK_ALIGN = 16;

	{
		int32_t mem_base = 0;
		if (dylink->mem_size) {
			uint32_t align = std::max((uint32_t)1 << dylink->mem_align, STACK_ALIGN);

			auto result = m_malloc.call(m_wasm_store, { dylink->mem_size + align });
			if (!result) {
				return {};
			}
			mem_base = mem_align(result.ok(), align);
		}
		auto maybe_mem_base = wasmtime::Global::create(m_wasm_store, wasmtime::GlobalType(wasmtime::ValKind::I32, false), mem_base);
		if (!maybe_mem_base) {
			return {};
		}
		if (!linker.define("env", "__memory_base", maybe_mem_base.unwrap())) {
			return {};
		}
	}

	{
		int32_t table_base = 0;
		if (dylink->table_size) {
			table_base = (int32_t)m_indirect_function_table.size(m_wasm_store);
			if (!m_indirect_function_table.grow(m_wasm_store, dylink->table_size, std::optional<wasmtime::Func>())) {
				return {};
			}
		}

		auto maybe_table_base = wasmtime::Global::create(m_wasm_store, wasmtime::GlobalType(wasmtime::ValKind::I32, false), table_base);
		if (!maybe_table_base) {
			return {};
		}

		if (!linker.define("env", "__table_base", maybe_table_base.unwrap())) {
			return {};
		}
	}

	if (!linker.define("env", "memory", m_memory)) {
		return {};
	}

	if (!linker.define("env", "__indirect_function_table", m_indirect_function_table)) {
		return {};
	}

	auto maybe_instance = linker.instantiate(m_wasm_store, mod);

	if (!maybe_instance) {
		std::string msg = maybe_instance.err().message();
		std::cout << "WASM Instantiate error: " << msg << std::endl;
		return {};
	}

	return maybe_instance.ok();
}

std::optional<WASMRuntime> WASMRuntime::CreateRuntime(CExecutionEngine& engine, wasmtime::Engine& wasm_engine, wasmtime::Module& main_module)
{
	wasmtime::Store wasm_store(wasm_engine);

	std::optional<wasmtime_dylink_meminfo_t> dylink_info = main_module.dylinkInfo();

	if (!dylink_info) {
		return {};
	}

	constexpr int32_t STATIC_BASE = 1024, STACK_SIZE = 5 * 1024 * 1024;

	auto maybe_memory = wasmtime::Memory::create(wasm_store, wasmtime::MemoryType(256, 32768 /* 4gb */));
	if (!maybe_memory) {
		return {};
	}

	auto memory_base = wasmtime::Global::create(wasm_store, wasmtime::GlobalType(wasmtime::ValKind::I32, false), STATIC_BASE);
	if (!memory_base) {
		return {};
	}

	auto table_base = wasmtime::Global::create(wasm_store, wasmtime::GlobalType(wasmtime::ValKind::I32, false), 1);
	if (!table_base) {
		return {};
	}

	int32_t stack_low = mem_align(STATIC_BASE + dylink_info->mem_size, 16);
	int32_t stack_high = mem_align(stack_low + STACK_SIZE, 16);

	auto maybe_stack_pointer = wasmtime::Global::create(wasm_store, wasmtime::GlobalType(wasmtime::ValKind::I32, true), stack_high);
	if (!maybe_stack_pointer) {
		return {};
	}
	auto maybe_heap_base = wasmtime::Global::create(wasm_store, wasmtime::GlobalType(wasmtime::ValKind::I32, true), stack_high);
	if (!maybe_heap_base) {
		return {};
	}
	auto maybe_indirect_function_table = wasmtime::Table::create(wasm_store, wasmtime::TableType(wasmtime::ValKind::FuncRef, 256), std::optional<wasmtime::Func>{});
	if (!maybe_indirect_function_table) {
		return {};
	}

	wasmtime::Linker linker(wasm_engine);

	if (!linker.func_wrap("env", "emscripten_notify_memory_growth", [](uint32_t) {})) {
		return {};
	}
	if (!linker.define("env", "__stack_pointer", maybe_stack_pointer.unwrap())) {
		return {};
	}
	if (!linker.define("env", "__memory_base", memory_base.unwrap())) {
		return {};
	}
	if (!linker.define("env", "__table_base", table_base.unwrap())) {
		return {};
	}
	if (!linker.define("GOT.mem", "__heap_base", maybe_heap_base.unwrap())) {
		return {};
	}
	if (!linker.define("env", "memory", maybe_memory.unwrap())) {
		return {};
	}
	if (!linker.define("env", "__indirect_function_table", maybe_indirect_function_table.unwrap())) {
		return {};
	}

	auto maybe_main_instance = linker.instantiate(wasm_store, main_module);
	if (!maybe_main_instance) {
		return {};
	}

	auto maybe___wasm_apply_data_relocs = TypedFuncExtract<wasmtime::TypedFunc<std::tuple<>, std::monostate>>::Get(wasm_store, maybe_main_instance.unwrap(), "__wasm_apply_data_relocs");
	if (!maybe___wasm_apply_data_relocs) {
		return {};
	}
	if (!maybe___wasm_apply_data_relocs->call(wasm_store, std::tuple<>())) {
		return {};
	}

	auto maybe_malloc = TypedFuncExtract<decltype(WASMRuntime::m_malloc)>::Get(wasm_store, maybe_main_instance.unwrap(), "malloc");
	auto maybe_free = TypedFuncExtract<decltype(WASMRuntime::m_free)>::Get(wasm_store, maybe_main_instance.unwrap(), "free");
	if (!maybe_malloc || !maybe_free) {
		return {};
	}

	return WASMRuntime(
		engine,
		wasm_engine,
		std::move(wasm_store),
		maybe_memory.ok(),
		maybe_stack_pointer.ok(),
		maybe_heap_base.ok(),
		maybe_indirect_function_table.ok(),
		*maybe_malloc,
		*maybe_free);
}
