#pragma once
#include <string>
#include <iostream>
#include <wasmtime.hh> // wasmtime need string and iostream but did not include them

template <typename T>
inline std::optional<T> GetExport(wasmtime::Store::Context& ctx, wasmtime::Instance& instance, std::string_view name) {
	auto maybe = instance.get(ctx, name);
	if (!maybe || !std::holds_alternative<T>(maybe.value())) {
		return {};
	}
	return std::move(std::get<T>(maybe.value()));
}

template <typename F, typename = void>
struct TypedFuncExtract {};

template <typename Params, typename Results>
struct TypedFuncExtract<wasmtime::TypedFunc<Params, Results>> {
	static std::optional<wasmtime::TypedFunc<Params, Results>>
		Get(wasmtime::Store::Context ctx, wasmtime::Instance instance, std::string_view name) {
		auto fn = GetExport<wasmtime::Func>(ctx, instance, name);
		if (!fn) {
			return {};
		}
		auto maybe_typed_fn = fn.value().typed<Params, Results>(ctx);
		if (!maybe_typed_fn) {
			return {};
		}
		return std::move(maybe_typed_fn.unwrap());
	}
};

class CExecutionEngine;

using WasmPtrT = uint32_t; // for wasm32

class WASMRuntime {
private:
	CExecutionEngine& m_engine;
	wasmtime::Engine& m_wasm_engine;
	wasmtime::Store	 m_wasm_store;
	wasmtime::Memory m_memory;
	wasmtime::Global m_stack_pointer;
	wasmtime::Global m_heap_base;
	wasmtime::Table  m_indirect_function_table;
	wasmtime::TypedFunc<uint32_t, WasmPtrT> m_malloc;
	wasmtime::TypedFunc<WasmPtrT, std::monostate> m_free;

	WASMRuntime(CExecutionEngine& engine,
		wasmtime::Engine& wasm_engine,
		wasmtime::Store wasm_store,
		wasmtime::Memory memory,
		wasmtime::Global stack_pointer,
		wasmtime::Global heap_base,
		wasmtime::Table indirect_function_table,
		wasmtime::TypedFunc<uint32_t, WasmPtrT> malloc,
		wasmtime::TypedFunc<WasmPtrT, std::monostate> free
	);
public:
	wasmtime::Store& wasm_store() {
		return m_wasm_store;
	}

	wasmtime::Memory memory() {
		return m_memory;
	}

	wasmtime::TypedFunc<uint32_t, WasmPtrT> malloc() {
		return m_malloc;
	}

	wasmtime::TypedFunc<WasmPtrT, std::monostate> free() {
		return m_free;
	}

	std::optional<wasmtime::Instance> Instantiate(wasmtime::Module& module);

	static std::optional<wasmtime::Linker> CreateBaseLinker(CExecutionEngine& engine);

	static std::optional<WASMRuntime> CreateRuntime(CExecutionEngine& engine, wasmtime::Engine& wasm_engine, wasmtime::Module& main_module);
};