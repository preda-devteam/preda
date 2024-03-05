#include <iostream>
#include <sstream>
#include "../../../SFC/core/rt/json.h"
#include "../../transpiler/transpiler/PredaCommon.h"
#include "../../transpiler/transpiler.h"
#include "../../native/types/typetraits.h"
#include "../../native/abi/vm_interfaces.h"
#include "../../native/types/data_jsonifer.h"
#include "ContractDatabase.h"
#include "PredaCompiledContracts.h"
#include "ContractRuntimeInstance.h"
#include "SymbolDBForTranspiler.h"

typedef transpiler::ITranspiler* (*FNCreateTranspilerInstance)(const char *options);
FNCreateTranspilerInstance CreateTranspilerInstance = nullptr;

template <typename T>
struct AutoRelease
{
	T *m_p;
	AutoRelease(T *p)
		: m_p(p)
	{
	}

	AutoRelease()
		: m_p(nullptr)
	{
	}

	void SetPtr(T* p)
	{
		if (m_p)
			m_p->Release();
		m_p = p;
	}

	T* GetPtr()
	{
		return m_p;
	}

	~AutoRelease()
	{
		if (m_p != nullptr)
			m_p->Release();
	}
};

bool ReadEntryFromJson(const rt::JsonObject &json, ContractDatabaseEntry &outEntry)
{
	rt::String_Ref data;
	bool bExist;

	if (!json.LoadValue("module_id", data))
		return false;
	::rvm::RvmTypeJsonParse(outEntry.compileData.moduleId, data);

	outEntry.compileData.dapp = rt::String(json.GetValue("dapp", bExist));
	if (!bExist) return false;

	outEntry.compileData.name = rt::String(json.GetValue("name", bExist));
	if (!bExist) return false;

	outEntry.compileData.contractDoxygenComment = rt::String(json.GetValue("comment", bExist)).GetString();
	if (!bExist) return false;

	outEntry.compileData.exportUniqueString = rt::String(json.GetValue("export_unique_str", bExist));
	if (!bExist) return false;

	outEntry.linkData.binaryPathFileName = rt::String(json.GetValue("bin", bExist)).GetString();
	if (!bExist) return false;

	outEntry.linkData.srcPathFileName = rt::String(json.GetValue("src", bExist));
	if (!bExist) return false;

	outEntry.linkData.intermediatePathFileName = rt::String(json.GetValue("inter", bExist)).GetString();
	if (!bExist) return false;

	{
		rt::String_Ref jsonStr(json.GetValue("inter_hash", bExist));
		if (!bExist) return false;
		::rvm::RvmTypeJsonParse(outEntry.compileData.intermediateHash, jsonStr);
	}

	// state variables
	{
		data = json.GetValue("sv", bExist);
		if (!bExist) return false;
		rt::JsonArray svArray(data);
		rt::JsonObject svJson;
		outEntry.compileData.scopeStateVarMeta.resize(int(transpiler::ScopeType::Num));
		for (int i = 0; i < (int)svArray.GetSize(); i++)
		{
			svArray.GetNextObjectRaw(svJson);

			rt::String_Ref sig;
			if (!svJson.LoadValue("sig", sig))
				return false;
			outEntry.compileData.scopeStateVarMeta[i].signature = rt::String(sig).GetString();

			rt::String_Ref comment;
			if (!svJson.LoadValue("comment", comment))
				return false;
			rt::JsonArray stateVarArray(comment);
			rt::String_Ref stateVarStr;
			for (int j = 0; j < (int)stateVarArray.GetSize(); j++)
			{
				stateVarArray.GetNextObjectRaw(stateVarStr);
				outEntry.compileData.scopeStateVarMeta[i].comment.push_back(rt::String(stateVarStr).GetString());
			}

			data = svJson.GetValue("has_asset", bExist);
			if (!bExist) return false;
			data.ToNumber(outEntry.compileData.scopeStateVarMeta[i].hasAsset);

			data = svJson.GetValue("has_blob", bExist);
			if (!bExist) return false;
			data.ToNumber(outEntry.compileData.scopeStateVarMeta[i].hasBlob);
		}
	}

	{
		data = json.GetValue("imports", bExist);
		if (!bExist) return false;
		rt::JsonArray importArray(data);
		rt::JsonObject importJson;
		for (int i = 0; i < (int)importArray.GetSize(); i++)
		{
			importArray.GetNextObjectRaw(importJson);
			rt::String_Ref importData;

			outEntry.compileData.importedContracts.push_back(rt::String(importJson.GetValue("name", bExist)).GetString());
		}
	}

	{
		data = json.GetValue("enums", bExist);
		if (!bExist) return false;
		rt::JsonArray enumArray(data);
		rt::JsonObject enumJson;
		for (int i = 0; i < (int)enumArray.GetSize(); i++)
		{
			enumArray.GetNextObjectRaw(enumJson);
			rt::String_Ref enumerators;

			ContractEnum enumerate;
			enumerate.name = rt::String(enumJson.GetValue("name", bExist)).GetString();
			if (!bExist) return false;

			enumerate.doxygenComment = rt::String(enumJson.GetValue("comment", bExist)).GetString();
			if (!bExist) return false;

			enumerate.enumerators = std::vector<std::string>();
			outEntry.compileData.enums.emplace_back(enumerate);

			enumerators = enumJson.GetValue("enumerator", bExist);
			if (!bExist) return false;

			rt::JsonArray enumeratorArray(enumerators);

			rt::String_Ref strRef;
			for (int j = 0; j < (int)enumeratorArray.GetSize(); j++)
			{
				enumeratorArray.GetNextObject(strRef);
				outEntry.compileData.enums.back().enumerators.push_back(rt::String(strRef).GetString());
			}
		}
	}

	{
		data = json.GetValue("structs", bExist);
		if (!bExist) return false;
		rt::JsonArray structArray(data);
		rt::JsonObject structJson;
		for (int i = 0; i < (int)structArray.GetSize(); i++)
		{
			structArray.GetNextObjectRaw(structJson);
			rt::String_Ref variables;

			std::string structTypename = rt::String(structJson.GetValue("name", bExist)).GetString();
			if (!bExist) return false;

			std::string structDoxygenComment = rt::String(structJson.GetValue("comment", bExist)).GetString();
			if (!bExist) return false;

			outEntry.compileData.structs.emplace_back();
			outEntry.compileData.structs.back().name = structTypename;
			outEntry.compileData.structs.back().doxygenComment = structDoxygenComment;

			variables = structJson.GetValue("variable", bExist);
			if (!bExist) return false;

			rt::JsonArray memberArray(variables);
			if (memberArray.GetSize() % 2 != 0)
				return false;
			rt::String_Ref strRef;
			for (int j = 0; j < (int)memberArray.GetSize() / 2; j++)
			{
				memberArray.GetNextObject(strRef);
				std::string memberType = rt::String(strRef).GetString();
				memberArray.GetNextObject(strRef);
				std::string memberName = rt::String(strRef).GetString();
				outEntry.compileData.structs.back().members.emplace_back(memberType, memberName);
			}
		}
	}

	{
		rt::String_Ref tmp = json.GetValue("global_deploy_function", bExist);
		if (!bExist) return false;
		tmp.ToNumber(outEntry.compileData.globalDeployFunctionIdx);
	}

	{
		rt::String_Ref tmp = json.GetValue("shard_scale_out_function", bExist);
		if (!bExist) return false;
		tmp.ToNumber(outEntry.compileData.shardScaleOutFunctionIdx);
	}

	struct nested
	{
		static bool ReadFuncArrayFromJson(std::vector<ContractFunction> &out, rt::String_Ref data)
		{
			bool bExist;

			rt::JsonArray funcArray(data);
			rt::JsonObject funcJson;
			for (int i = 0; i < (int)funcArray.GetSize(); i++)
			{
				funcArray.GetNextObjectRaw(funcJson);
				rt::String_Ref funcData;

				ContractFunction func;

				func.name = rt::String(funcJson.GetValue("name", bExist)).GetString();
				if (!bExist) return false;

				funcData = funcJson.GetValue("flags", bExist);
				if (!bExist) return false;
				funcData.ToNumber(func.flags);

				func.returnType = rt::String(funcJson.GetValue("ret_type", bExist)).GetString();
				if (!bExist) return false;

				func.doxygenComment = rt::String(funcJson.GetValue("comment", bExist)).GetString();
				if (!bExist) return false;

				funcData = funcJson.GetValue("params", bExist);
				if (!bExist) return false;

				rt::JsonArray paramArray(funcData);
				if (paramArray.GetSize() % 2 != 0)
					return false;
				rt::String_Ref paramData;
				for (int j = 0; j < (int)paramArray.GetSize() / 2; j++)
				{
					paramArray.GetNextObject(paramData);
					std::string paramType = rt::String(paramData).GetString();
					paramArray.GetNextObject(paramData);
					std::string paramName = rt::String(paramData).GetString();
					func.parameters.emplace_back(paramType, paramName);
				}

				out.push_back(func);
			}

			return true;
		}
	};

	{
		data = json.GetValue("funcs", bExist);
		if (!bExist) return false;
		if (!nested::ReadFuncArrayFromJson(outEntry.compileData.functions, data))
			return false;
	}

	{
		data = json.GetValue("interfaces", bExist);
		if (!bExist) return false;
		rt::JsonArray interfaceArray(data);
		rt::JsonObject interfaceJson;
		for (int i = 0; i < (int)interfaceArray.GetSize(); i++)
		{
			interfaceArray.GetNextObjectRaw(interfaceJson);
			rt::String_Ref interfaceData;

			ContractInterface ci;

			ci.name = rt::String(interfaceJson.GetValue("name", bExist)).GetString();
			if (!bExist) return false;

			rt::String_Ref funcs = interfaceJson.GetValue("funcs", bExist);
			if (!bExist) return false;
			if (!nested::ReadFuncArrayFromJson(ci.functions, funcs))
				return false;

			outEntry.compileData.interfaces.push_back(std::move(ci));
		}
	}

	{
		data = json.GetValue("implemented_interfaces", bExist);
		if (!bExist) return false;
		rt::JsonArray interfaceArray(data);
		rt::JsonObject interfaceJson;
		for (int i = 0; i < (int)interfaceArray.GetSize(); i++)
		{
			interfaceArray.GetNextObjectRaw(interfaceJson);
			rt::String_Ref interfaceData;

			ContractImplementedInterface cii;

			cii.name = rt::String(interfaceJson.GetValue("name", bExist)).GetString();
			if (!bExist) return false;
			if (!interfaceJson.LoadValueAs("def_slot", cii.interfaceDefSlot))
				return false;
			if (!interfaceJson.LoadValue("def_module_id", data))
				return false;
			::rvm::RvmTypeJsonParse(cii.interfaceDefContractModuleId, data);

			rt::String_Ref funcs = interfaceJson.GetValue("funcs", bExist);
			if (!bExist) return false;
			rt::JsonArray funcIdxArray(funcs);
			for (int j = 0; j < (int)funcIdxArray.GetSize(); j++)
			{
				rt::String_Ref funcIdxStr;
				funcIdxArray.GetNextObject(funcIdxStr);
				int32_t idx;
				funcIdxStr.ToNumber(idx);
				cii.functionIds.push_back(idx);
			}

			outEntry.compileData.implementedInterfaces.push_back(std::move(cii));
		}
	}

	return true;
}

static wasmtime::Config GetDefaultWASMConfig() {
	wasmtime::Config cfg;
	cfg.consume_fuel(false); // TODO fuel
	cfg.wasm_bulk_memory(false);
	cfg.wasm_multi_value(false);
	cfg.wasm_reference_types(false);
	cfg.wasm_simd(false);
	cfg.wasm_threads(false);
	return cfg;
}

CContractDatabase::CContractDatabase(RuntimeMode mode):
	m_wasm_engine(GetDefaultWASMConfig()),
	m_runtime_mode(mode) {
}

#if defined(__linux__) || defined(__linux)
constexpr char EXECUTABLE_EXTENSION[] = ".so";
#elif defined(__APPLE__)
constexpr char EXECUTABLE_EXTENSION[] = ".dylib";
#elif defined(_WIN32)
constexpr char EXECUTABLE_EXTENSION[] = ".dll";
#else
#error "Unknown platform"
#endif

bool CContractDatabase::Initialize(const char* module_path, const char* db_path, rvm::BlockchainRuntime *runtime_api, rvm::ConstString *initErrorMsg)
{
	EnterCSBlock(m_barrier);

	m_modulePath = module_path;
	if (m_modulePath[m_modulePath.size() - 1] != '\\' && m_modulePath[m_modulePath.size() - 1] != '/')
		m_modulePath += '/';

	{
#if	defined(__linux__) || defined(__linux)
		HANDLE handle_antlr = os::LoadDynamicLibrary((m_modulePath + "libantlr4-runtime.so.4.9.3").c_str());
		if (handle_antlr == nullptr)
			return false;
		HANDLE handle = os::LoadDynamicLibrary((m_modulePath + "transpiler.so").c_str());
#elif defined(_WIN32)
		HANDLE handle = os::LoadDynamicLibrary((m_modulePath + "transpiler.dll").c_str());
#elif defined(__APPLE__)
		HANDLE handle = os::LoadDynamicLibrary((m_modulePath + "transpiler.dylib").c_str());
#endif
		if (handle == nullptr)
		{
			if (initErrorMsg)
			{
				constexpr static char errorMsg[] = "[PRD]: Unable to load transpiler library\n";
				static uint32_t errorMsgLen = uint32_t(strlen(errorMsg));
				initErrorMsg->StrPtr = errorMsg;
				initErrorMsg->Length = errorMsgLen;
			}
			return false;
		}

		CreateTranspilerInstance = (FNCreateTranspilerInstance)os::GetDynamicLibrarySymbol(handle, "CreateTranspilerInstance");
		if (CreateTranspilerInstance == nullptr)
		{
			if (initErrorMsg)
			{
				constexpr static char errorMsg[] = "[PRD]: Unable to load transpiler symbol\n";
				static uint32_t errorMsgLen = uint32_t(strlen(errorMsg));
				initErrorMsg->StrPtr = errorMsg;
				initErrorMsg->Length = errorMsgLen;
			}
			return false;
		}

		transpiler::ITranspiler *pTranspiler = CreateTranspilerInstance(nullptr);
		if (!pTranspiler)
		{
			if (initErrorMsg)
			{
				constexpr static char errorMsg[] = "[PRD]: Unable to create transpiler instance\n";
				static uint32_t errorMsgLen = uint32_t(strlen(errorMsg));
				initErrorMsg->StrPtr = errorMsg;
				initErrorMsg->Length = errorMsgLen;
			}
			return false;
		}
		m_transpilerVersion = pTranspiler->GetVersion();
	}

	{
		rt::String absPath;
		os::File::ResolveRelativePath(db_path, absPath);
		m_dbPath = absPath.GetString();
		if (m_dbPath[m_dbPath.size() - 1] != '\\' && m_dbPath[m_dbPath.size() - 1] != '/')
			m_dbPath += '/';
		if (!m_contractDB.Open((m_dbPath + "db/").c_str()))
		{
			if (initErrorMsg)
			{
				constexpr static char errorMsg[] = "[PRD]: Unable to open db\n";
				static uint32_t errorMsgLen = uint32_t(strlen(errorMsg));
				initErrorMsg->StrPtr = errorMsg;
				initErrorMsg->Length = errorMsgLen;
			}
			return false;
		}

		for (ext::RocksCursor itor = m_contractDB.First(); itor.IsValid(); itor.Next())
		{
			ContractDatabaseEntry entry;

			rt::JsonObject obj(itor.Value().ToString());
			if (ReadEntryFromJson(obj, entry))
			{
				m_contracts.try_emplace(entry.compileData.moduleId, entry);
				entry.CreateDelegate();
			}
		}
	}

	m_pRuntimeAPI = runtime_api;

#ifdef PLATFORM_WIN
	{
		WCHAR buffer[32767];
		GetEnvironmentVariableW(L"PATH", buffer, 32767);
		wcscat_s(buffer, os::__UTF16((";" + m_modulePath + "../mingw64/bin/").c_str()));
		SetEnvironmentVariableW(L"PATH", buffer);
	}

	if (m_runtime_mode == RuntimeMode::WASM || m_runtime_mode == RuntimeMode::CWASM) {
		WCHAR buffer[32767];
		GetEnvironmentVariableW(L"PATH", buffer, 32767);
		wcscat_s(buffer, os::__UTF16((";" + m_modulePath + "../emscripten/3.1.24/").c_str()));
		SetEnvironmentVariableW(L"PATH", buffer);
	}
	// TODO compile wasm in linux and mac
#endif

	std::tuple<uint32_t, uint32_t, uint32_t> compilerVersion;

	if (!GetCppCompilerVersion(compilerVersion))
		return false;

	if (std::get<0>(compilerVersion) < 8 || (std::get<0>(compilerVersion) == 8 && std::get<1>(compilerVersion) < 1))
	{
		if (initErrorMsg)
		{
			constexpr static char errorMsg[] = "g++ version 8.1 or above is need to compile preda contracts.";
			static uint32_t errorMsgLen = uint32_t(strlen(errorMsg));
			initErrorMsg->StrPtr = errorMsg;
			initErrorMsg->Length = errorMsgLen;
		}
		return false;
	}

	if (m_runtime_mode == RuntimeMode::WASM || m_runtime_mode == RuntimeMode::CWASM) {
		rt::String wasm_mod;
		std::string path = m_modulePath + "../compile_env/contract_wasm_main.wasm";
		if (!os::File::LoadBinary(path.c_str(), wasm_mod)) {
			return false;
		}
		auto maybe_mod = wasmtime::Module::compile(m_wasm_engine, wasmtime::Span<uint8_t>((uint8_t*)wasm_mod.Begin(), wasm_mod.GetLength()));
		if (!maybe_mod) {
			return false;
		}
		m_wasm_main_module.emplace(maybe_mod.ok());
	}

	return true;
}

bool CContractDatabase::GetCppCompilerVersion(std::tuple<uint32_t, uint32_t, uint32_t> &outVersion)
{
	std::string result;
#if	defined(__linux__) || defined(__linux) || defined(__APPLE__)
	std::string cmdLine = "g++ --version 2>&1";
	FILE *pipe = popen(cmdLine.c_str(), "r");
	if (pipe == nullptr)
		return false;
	{
		char buffer[128];
		while (fgets(buffer, sizeof(buffer), pipe) != NULL)
			result += buffer;
		int res = pclose(pipe);
		if (res != 0)
			return false;
	}

#elif defined(_WIN32)
	os::LaunchProcess processLauncher;
	std::string cmdLine = m_modulePath + "../mingw64/bin/g++ --version";
	if (!processLauncher.Launch(cmdLine.c_str(), os::LaunchProcess::FLAG_SAVE_OUTPUT))
		return false;
	processLauncher.WaitForEnding();
	if (processLauncher.GetExitCode() != 0)
		return false;
	if (processLauncher.GetOutput() == nullptr)
		return false;
	result = processLauncher.GetOutput();
#endif

#if	defined(__linux__) || defined(__linux)
	std::string::size_type version_end = result.find("\n");
#elif defined(__APPLE__)
	std::string::size_type version_end;
	//Apple clang version xx.xx.xxx (clang-xxx.xxx.xxx) OR g++ (Homebrew GCC 10.2.0_4) 10.2.0
	if(result.substr(0, 5) == "Apple" || result.substr(0, 3) == "g++")
	{
		version_end = result.find("\n");
		version_end = result.rfind(" ", version_end);
	}
	//Configured with: ...
	//Apple LLVM version 9.0.0 (clang-900.0.38)
	else if (result.substr(0, 10) == "Configured")
	{
		version_end = result.find("\n");
		if (version_end == std::string::npos)
			return false;
		version_end = result.find("\n", version_end + 1);
		if (version_end == std::string::npos)
			return false;
		  version_end = result.rfind(" ", version_end);
	}
	else
	{
		printf("Unable to obtain g++ --version\n");
	}
#elif defined(_WIN32)
	std::string::size_type version_end = result.find("\r\n");
#endif
	if (version_end == std::string::npos)
		return false;
	std::string::size_type version_begin = result.rfind(" ", version_end - 1);
	if (version_begin == std::string::npos)
		return false;
	version_begin++;

	if (version_begin >= version_end)
		return false;

	std::string versionStr = result.substr(version_begin, version_end - version_begin);

	uint32_t v0, v1, v2;
#ifdef _WIN32
	if (sscanf_s(versionStr.c_str(), "%u.%u.%u", &v0, &v1, &v2) != 3)
#else
	if (sscanf(versionStr.c_str(), "%u.%u.%u", &v0, &v1, &v2) != 3)
#endif
	{
		printf("[PRD]: Unable to parse c++ version result\n");
		return false;
	}

	outVersion = std::make_tuple(v0, v1, v2);

	return true;
}

rvm::ConstString CContractDatabase::GetVersion() const
{
	static const char str[] = "0.0.1";
	rt::String_Ref tmp(str);
	return *(rvm::ConstString*)&tmp;
}

rvm::ConstString CContractDatabase::GetName() const
{
	static const char str_native[] = "PREDA Native Build";
	static const char str_wasm[] = "PREDA WASM Build";
	static const char str_cwasm[] = "PREDA WASM Build (CWASM)";
	rt::String_Ref tmp(m_runtime_mode == RuntimeMode::NATIVE ? str_native : m_runtime_mode == RuntimeMode::WASM ? str_wasm : str_cwasm);
	return *(rvm::ConstString*)&tmp;
}

rvm::ConstString CContractDatabase::GetVendorInfo() const
{
	static const char str[] = "PREDA DevTeam";
	rt::String_Ref tmp(str);
	return *(rvm::ConstString*)&tmp;
}

void CContractDatabase::Release()
{
	m_contracts.clear();
	m_contractDB.Close();
	delete this;
}

const ContractDatabaseEntry* CContractDatabase::FindContractEntry(const rvm::ContractModuleID &moduleId) const
{
	EnterCSBlock(m_barrier);

	auto itor = m_contracts.find(moduleId);
	if (itor == m_contracts.end())
		return nullptr;

	return &itor->second;
}

const ContractDatabaseEntry* CContractDatabase::FindContractEntry(const rvm::ContractModuleID * moduleId) const
{
	if (moduleId == nullptr)
		return nullptr;

	return FindContractEntry(*moduleId);
}

static bool endsWith(std::string_view str, std::string_view suffix)
{
	return str.size() >= suffix.size() && 0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
}


ContractModule* CContractDatabase::GetContractModule(const rvm::ContractModuleID &deployId)
{
	const ContractDatabaseEntry* pContractEntry = CContractDatabase::FindContractEntry(deployId);
	if (!pContractEntry)
		return nullptr;

	EnterCSBlock(m_barrier);
	{
		auto it = m_loadedContractModule.find(deployId);
		if (it != m_loadedContractModule.end())
			return it->second.get();
	}

	std::string mod_file = m_dbPath + pContractEntry->linkData.binaryPathFileName;
	if (endsWith(mod_file, EXECUTABLE_EXTENSION))
	{
		ASSERT(m_runtime_mode == RuntimeMode::NATIVE);
		HANDLE hModule = os::LoadDynamicLibrary((m_dbPath + pContractEntry->linkData.binaryPathFileName).c_str());
		if (hModule == nullptr)
			return nullptr;
		std::unique_ptr<ContractModule> mod = ContractModule::FromLibrary(*pContractEntry, hModule);
		if (!mod)
		{
			return nullptr;
		}
		return m_loadedContractModule.try_emplace(deployId, std::move(mod)).first->second.get();
	}
	else
	{
		ASSERT(m_runtime_mode == RuntimeMode::WASM || m_runtime_mode == RuntimeMode::CWASM);

		rt::String wasm_mod;
		if (!os::File::LoadBinary(mod_file.c_str(), wasm_mod))
		{
			return nullptr;
		}
		wasmtime::Result<wasmtime::Module> maybe_mod = endsWith(mod_file, ".cwasm") ?
			wasmtime::Module::deserialize(m_wasm_engine, wasmtime::Span<uint8_t>((uint8_t*)wasm_mod.Begin(), wasm_mod.GetLength())) :
			wasmtime::Module::compile(m_wasm_engine, wasmtime::Span<uint8_t>((uint8_t*)wasm_mod.Begin(), wasm_mod.GetLength()));

		if (!maybe_mod)
		{
			return nullptr;
		}

		std::unique_ptr<ContractModule> mod = ContractModule::FromWASMModule(*pContractEntry, std::move(maybe_mod.unwrap()));
		if (!mod)
		{
			return nullptr;
		}
		return m_loadedContractModule.try_emplace(deployId, std::move(mod)).first->second.get();
	}
}

struct LogMessage
{
	rvm::ConstString		Message;
	rvm::LogMessageType		Type;
	uint32_t				Code;
	uint32_t				Line;
	uint32_t				LineOffset;
};

struct PredaLogMessages
{
	std::vector<LogMessage> m_msgs;
	std::vector<std::shared_ptr<std::string>> m_msgStrings;		// Message in m_msgs are just references, the real message strings are stored here

	void AddMessage(uint32_t line, uint32_t line_offset, uint32_t code, const char *msg)
	{
		m_msgStrings.push_back(std::make_shared<std::string>(msg));

		LogMessage logMsg;
		logMsg.Type = rvm::LogMessageType::Error;
		logMsg.Code = code;
		logMsg.Line = line;
		logMsg.LineOffset = line_offset;
		logMsg.Message.StrPtr = m_msgStrings.back()->c_str();
		logMsg.Message.Length = uint32_t(m_msgStrings.back()->size());
		m_msgs.push_back(logMsg);
	}

	// interfaces from rvm::LogMessages
	uint32_t GetCount()
	{
		return uint32_t(m_msgs.size());
	}
	LogMessage Get(uint32_t idx)
	{
		if (idx >= uint32_t(m_msgs.size()))
			return LogMessage();
		return m_msgs[idx];
	}
	void Release()
	{
		delete this;
	}
};

void DumpLogMessages(PredaLogMessages &logMsgs, uint32_t contractIdx, rvm::LogMessageOutput* log_msg_output)
{
	if (log_msg_output == nullptr)
		return;

	for (uint32_t msgIdx = 0; msgIdx < logMsgs.GetCount(); msgIdx++)
	{
		LogMessage msg = logMsgs.Get(msgIdx);
		log_msg_output->Log(msg.Type, msg.Code, contractIdx, msg.Line, msg.LineOffset, &msg.Message);
	}
}

rvm::ConstString CContractDatabase::GetContractName(const rvm::ConstData* source_code)
{
	if (CreateTranspilerInstance == nullptr)
		return rvm::ConstString{ nullptr, 0 };
	AutoRelease<transpiler::ITranspiler> ptr(CreateTranspilerInstance(nullptr));
	transpiler::ITranspiler* pTranspiler = ptr.GetPtr();
	std::string srcCode((char*)source_code->DataPtr, source_code->DataSize);
	if (!pTranspiler->BuildParseTree(srcCode.c_str()) || ! pTranspiler->PreCompile("dummy"))		// dapp name is irrelevant when extracting contract name
		return rvm::ConstString{ nullptr, 0 };
	std::string contractName = pTranspiler->GetContractName();
	size_t nameOffset = srcCode.find(contractName);
	if (nameOffset == std::string::npos)
		return rvm::ConstString{ nullptr, 0 };
	uint32_t nameLength = uint32_t(contractName.size());
	return rvm::ConstString { (const char*)source_code->DataPtr + nameOffset, nameLength };
}

bool CContractDatabase::_Compile(IContractFullNameToModuleIdLookupTable* lookup, const rvm::ConstString* dapp_name, uint32_t contract_count, const rvm::ConstData* deploy_data_array, rvm::CompilationFlag flag, rvm::CompiledModules** compiled_output, rvm::LogMessageOutput* log_msg_output)
{
	EnterCSBlock(m_barrier);
	m_cancel.Reset();

	std::vector<ContractCompileData> allCompileDdata;
	CContractSymbolDatabaseForTranspiler symbolDatabase(this, allCompileDdata, m_pRuntimeAPI, lookup);
	PredaCompiledContracts* compiled_contracts = new PredaCompiledContracts(dapp_name->StrPtr, m_runtime_mode == RuntimeMode::NATIVE ? rvm::EngineId::PREDA_NATIVE : rvm::EngineId::PREDA_WASM, contract_count);

	// first create the transpilers
	std::vector<AutoRelease<transpiler::ITranspiler>> transpilers(contract_count);
	{
		bool bTranspilerReady = true;
		if (CreateTranspilerInstance == nullptr)
			bTranspilerReady = false;
		else
		{
			std::string options;
			if (uint64_t(flag) & uint64_t(rvm::CompilationFlag::DisableDebugPrint))
				options += " disabledebugprint";
			for (uint32_t i = 0; i < contract_count; i++)
			{
				transpiler::ITranspiler* pTranspiler = CreateTranspilerInstance(options.c_str());
				if (pTranspiler == nullptr)
				{
					bTranspilerReady = false;
					break;
				}
				transpilers[i].SetPtr(pTranspiler);
			}
		}

		if (!bTranspilerReady)
		{
			if (log_msg_output)
			{
				rt::String_Ref msg = "Transpiler not available";
				log_msg_output->Log(rvm::LogMessageType::Error, 0, 0, 0, 0, (rvm::ConstString*)&msg);
			}
			return false;
		}
	}

	// pre-compile the contracts to extract name and dependency
	std::vector<bool> precompileSuccessful(contract_count, true);
	std::string dAppName(dapp_name->StrPtr, dapp_name->Length);
	std::vector<std::string> contractFullName(contract_count);
	std::vector<std::vector<std::string>> dependentContracts(contract_count);
	std::vector<std::vector<uint32_t>> crossDependencies(contract_count);
	std::vector<std::string> srcCode(contract_count);
	for (uint32_t contractIdx = 0; contractIdx < contract_count; contractIdx++)
		srcCode[contractIdx] = std::move(std::string((char*)deploy_data_array[contractIdx].DataPtr, deploy_data_array[contractIdx].DataSize));

	for (uint32_t contractIdx = 0; contractIdx < contract_count; contractIdx++)
	{
		PredaLogMessages logMsgs;

		transpiler::ITranspiler* pTranspiler = transpilers[contractIdx].GetPtr();

		bool bSuccess = true;
		if (!pTranspiler->BuildParseTree(srcCode[contractIdx].c_str()))
		{
			uint32_t numCompileErrors = pTranspiler->GetNumCompileErrors();
			for (uint32_t i = 0; i < numCompileErrors; i++)
			{
				uint32_t line, pos;
				pTranspiler->GetCompileErrorPos(i, line, pos);
				logMsgs.AddMessage(line, pos, uint32_t(pTranspiler->GetCompileErrorCode(i)), pTranspiler->GetCompileErrorMsg(i));
			}
			bSuccess = false;
		}

		if (bSuccess && !pTranspiler->PreCompile(dAppName.c_str()))
		{
			logMsgs.AddMessage(0, 0, 0, "Pre-compile failed. Probably a bug in code.");
			bSuccess = false;
		}

		if (bSuccess)
		{
			uint32_t numDependencies = pTranspiler->GetNumDirectDependentContracts();
			dependentContracts[contractIdx].resize(numDependencies);
			for (uint32_t idx = 0; idx < numDependencies; idx++)
				dependentContracts[contractIdx][idx] = pTranspiler->GetDirectDependentContractName(idx);

			contractFullName[contractIdx] = std::string(pTranspiler->GetDAppName()) + "." + std::string(pTranspiler->GetContractName());
		}
		else
			DumpLogMessages(logMsgs, contractIdx, log_msg_output);		// only dump log messages for those failed pre-compile, the rest will be further processed.

		precompileSuccessful[contractIdx] = bSuccess;
	}

	// find dependencies among the contracts being deployed
	// This has to be done after all contracts are pre-compiled because it relies on each contract's name
	for (uint32_t i = 0; i < contract_count; i++)
	{
		if (!precompileSuccessful[i])
			continue;
		for (uint32_t j = 0; j < uint32_t(dependentContracts[i].size()); j++)
		{
			for (uint32_t k = 0; k < contract_count; k++)
				if (dependentContracts[i][j] == contractFullName[k])
				{
					crossDependencies[i].push_back(k);
					break;
				}
		}
	}

	// go through the dependencies and find a proper compile order
	std::vector<uint32_t> compileOrder(contract_count);
	{
		std::vector<bool> added(contract_count, false);
		for (uint32_t iteration = 0; iteration < contract_count; iteration++)
		{
			int32_t nextContract = -1;
			for (uint32_t candidate = 0; candidate < contract_count; candidate++)
			{
				if (added[candidate])
					continue;
				bool valid = true;
				for (uint32_t dependencyIdx = 0; dependencyIdx < uint32_t(crossDependencies[candidate].size()); dependencyIdx++)
					if (!added[crossDependencies[candidate][dependencyIdx]])
					{
						valid = false;
						break;
					}
				if (valid)
				{
					nextContract = candidate;
					break;
				}
			}
			if (nextContract != -1)
			{
				added[nextContract] = true;
				compileOrder[iteration] = nextContract;
			}
			else
			{
				if (log_msg_output)
				{
					rt::String_Ref msg = "cyclic import dependencies found.";
					log_msg_output->Log(rvm::LogMessageType::Error, 0, 0, 0, 0, (rvm::ConstString*)&msg);
				}
				return false;
			}
		}
	}

	bool bSuccess = true;

	for (uint32_t compileIdx = 0; compileIdx < uint32_t(compileOrder.size()) && !m_cancel.IsSignaled(); compileIdx++)
	{
		uint32_t contractIdx = compileOrder[compileIdx];

		// skip those that already failed pre-compile
		if (!precompileSuccessful[contractIdx])
		{
			bSuccess = false;
			continue;
		}

		transpiler::ITranspiler* currentTranspiler = transpilers[contractIdx].GetPtr();

		PredaLogMessages logMsgs;
		std::string intermediateCode;
		ContractCompileData curContractCompiledData;
		if (CompileContract(dapp_name, &symbolDatabase, intermediateCode, curContractCompiledData, logMsgs, currentTranspiler))
		{
			// calculate intermediate hash
			oxd::SecuritySuite::Hash(intermediateCode.c_str(), (uint32_t)intermediateCode.size(), &curContractCompiledData.intermediateHash);

			// calculate module id, i.e. moduleId = Hash(intermediateHash + importedContract0.moduleId  + importedContract1.moduleId + ...)
			struct HashSrcBuffer {
				rvm::HashValue intermediateHash;
				rvm::ContractModuleID importedModuleIds[1];
			};
			std::vector<uint8_t> buffer(sizeof(curContractCompiledData.intermediateHash) + curContractCompiledData.importedContracts.size() * sizeof(curContractCompiledData.moduleId));
			HashSrcBuffer *srcBuffer = reinterpret_cast<HashSrcBuffer*>(&buffer[0]);
			srcBuffer->intermediateHash = curContractCompiledData.intermediateHash;

			// iterate through all imported contracts
			for (uint32_t importIdx = 0; uint32_t(importIdx < curContractCompiledData.importedContracts.size()); importIdx++)
			{
				const std::string& importedContractName = curContractCompiledData.importedContracts[importIdx];

				const rvm::ContractModuleID* moduleId = symbolDatabase.GetContractModuleId(importedContractName.c_str());
				if (moduleId == nullptr)
				{
					bSuccess = false;
					continue;
				}

				srcBuffer->importedModuleIds[importIdx] = *moduleId;
			}
			oxd::SecuritySuite::Hash(&buffer[0], (uint32_t)buffer.size(), &curContractCompiledData.moduleId);

			// fill the interface module ids
			for (ContractImplementedInterface& implInterface : curContractCompiledData.implementedInterfaces)
			{
				std::string::size_type lastDotPos = implInterface.name.find_last_of('.');
				if (lastDotPos == std::string::npos)
				{
					bSuccess = false;
					continue;
				}

				std::string interfaceDefContractFullName = implInterface.name.substr(0, lastDotPos);
				std::string interfaceName = implInterface.name.substr(lastDotPos + 1);
				const rvm::ContractModuleID *moduleId = nullptr;
				transpiler::IContractSymbols* symbols = nullptr;
				if (interfaceDefContractFullName == contractFullName[contractIdx])
				{
					moduleId = &curContractCompiledData.moduleId;
					symbols = currentTranspiler;
				}
				else
				{
					moduleId = symbolDatabase.GetContractModuleId(interfaceDefContractFullName.c_str());
					symbols = symbolDatabase.GetContractSymbols(interfaceDefContractFullName.c_str());
				}

				if (moduleId == nullptr || symbols == nullptr)
				{
					bSuccess = false;
					continue;
				}

				implInterface.interfaceDefContractModuleId = *moduleId;
				{
					bool bFound = false;
					for (uint32_t interfaceIdx = 0; interfaceIdx < symbols->GetNumExportedInterfaces(); interfaceIdx++)
					{
						if (interfaceName == symbols->GetExportedInterfaceName(interfaceIdx))
						{
							implInterface.interfaceDefSlot = interfaceIdx;
							bFound = true;
							break;
						}
					}
					if (!bFound)
						bSuccess = false;
				}
			}

			compiled_contracts->AddContract(curContractCompiledData, srcCode[contractIdx].c_str(), intermediateCode, contractIdx);
			allCompileDdata.push_back(curContractCompiledData);
		}
		else
			bSuccess = false;

		DumpLogMessages(logMsgs, contractIdx, log_msg_output);		// only dump log messages for those failed pre-compile, the rest will be further processed.
	}

	// generate dependency data by collecting all dependent external contracts and their module id
	if (bSuccess)
	{
		const std::map<std::string, const ContractDatabaseEntry*>& externalDependencies = symbolDatabase.GetContractEntryCache();
		if (externalDependencies.size())
		{
			std::string externalDependentContracts;
			for (const auto& itor : externalDependencies)
				externalDependentContracts += itor.first + ';';

			std::vector<uint8_t> data(uint32_t(externalDependentContracts.size() + externalDependencies.size() * sizeof(rvm::ContractModuleID)));
			memcpy(&data[0], externalDependentContracts.c_str(), externalDependentContracts.size());
			uint32_t idx = 0;
			for (const auto& itor : externalDependencies)
				((rvm::ContractModuleID*)(&data[externalDependentContracts.size()]))[idx++] = itor.second->compileData.moduleId;
			compiled_contracts->SetDependencyData(std::move(data));
		}
	}


	if (compiled_output && !m_cancel.IsSignaled())
	{
		*compiled_output = compiled_contracts;
	}
	else
	{
		compiled_contracts->Release();
		compiled_contracts = nullptr;
	}

	return m_cancel.IsSignaled() ? false : bSuccess;
}

bool CContractDatabase::Compile(const rvm::ConstString* dapp_name, uint32_t contract_count, const rvm::ConstData* deploy_data_array, rvm::CompilationFlag flag, rvm::CompiledModules** compiled_output, rvm::LogMessageOutput* log_msg_output)
{
	struct ModuleIdLookupFromChainState : public IContractFullNameToModuleIdLookupTable
	{
		const rvm::GlobalStates* m_chainState;
		ModuleIdLookupFromChainState(const rvm::GlobalStates* chainState)
			: m_chainState(chainState)
		{
		}
		virtual const rvm::ContractModuleID* GetContractModuleIdFromFullName(const std::string& fullName) override
		{
			return _details::GetOnChainContractModuleIdFromFullName(m_chainState, fullName);
		}
	};

	ModuleIdLookupFromChainState lookup(m_pRuntimeAPI);

	return _Compile(&lookup, dapp_name, contract_count, deploy_data_array, flag, compiled_output, log_msg_output);
}

bool CContractDatabase::Recompile(const rvm::ConstString* dapp_name, const rvm::ConstData* dependency_data, uint32_t contract_count, const rvm::ConstData* deploy_data_array, rvm::CompilationFlag flag, rvm::CompiledModules** compiled_output, rvm::LogMessageOutput* log_msg_output)
{
	struct ModuleIdLookupFromDependencyData : public IContractFullNameToModuleIdLookupTable
	{
		std::map<std::string, rvm::ContractModuleID> table;
		bool SetDependencyData(const rvm::ConstData* dependency_data)
		{
			if (dependency_data == nullptr || dependency_data->DataPtr == nullptr || dependency_data->DataSize == 0)
				return true;

			const rt::String_Ref depStr((char*)dependency_data->DataPtr, uint32_t(dependency_data->DataSize));
			int32_t nameLen = int32_t(depStr.FindCharacterReverse(';'));
			if (nameLen == -1)
				return true;
			uint32_t depCount = uint32_t(depStr.GetLength() - nameLen) / uint32_t(sizeof(rvm::ContractModuleID));
			std::vector<rt::String_Ref> names(depCount);
			if (rt::String_Ref(depStr.GetString(), nameLen).Split(&names[0], depCount, ';') != depCount)
				return false;

			// all imported contracts must have the same deploy id as at the time of compile
			for (uint32_t i = 0; i < depCount; i++)
				table.emplace(std::string(names[i].GetString(), names[i].GetLength()), ((const rvm::ContractModuleID*)depStr.GetString())[i]);
			return true;
		}
		virtual const rvm::ContractModuleID* GetContractModuleIdFromFullName(const std::string& fullName) override
		{
			auto itor = table.find(fullName);
			if (itor == table.end())
				return nullptr;
			return &itor->second;
		}
	};

	ModuleIdLookupFromDependencyData lookup;
	if (!lookup.SetDependencyData(dependency_data))
	{
		if (log_msg_output)
		{
			rt::String_Ref msg = "invalid dependency data format.";
			log_msg_output->Log(rvm::LogMessageType::Error, 0, 0, 0, 0, (rvm::ConstString*)&msg);
		}

		return false;
	}

	return _Compile(&lookup, dapp_name, contract_count, deploy_data_array, flag, compiled_output, log_msg_output);
}

bool CContractDatabase::CompileContract(const rvm::ConstString* dapp_name, CContractSymbolDatabaseForTranspiler *symbol_db, std::string &out_intermediate_code, ContractCompileData &out_compile_data, PredaLogMessages &out_log, transpiler::ITranspiler* pTranspiler)
{
	EnterCSBlock(m_barrier);

	std::string dAppName(dapp_name->StrPtr, dapp_name->Length);

	if(!pTranspiler->Compile(dAppName.c_str(), symbol_db))
	{
		uint32_t numCompileErrors = pTranspiler->GetNumCompileErrors();
		for (uint32_t i = 0; i < numCompileErrors; i++)
		{
			uint32_t line, pos;
			pTranspiler->GetCompileErrorPos(i, line, pos);
			out_log.AddMessage(line, pos, uint32_t(pTranspiler->GetCompileErrorCode(i)), pTranspiler->GetCompileErrorMsg(i));
		}
		return false;
	}

	out_intermediate_code = pTranspiler->GetOutput();

	{
		out_compile_data.dapp = pTranspiler->GetDAppName();
		out_compile_data.name = pTranspiler->GetContractName();
		const char* contractComment = pTranspiler->GetContractComment();
		if(contractComment){
			out_compile_data.contractDoxygenComment = contractComment;
		}
		else{
			out_compile_data.contractDoxygenComment = std::string();
		}
		out_compile_data.exportUniqueString = pTranspiler->GetContractExportUniqueIdentifierString();

		out_compile_data.scopeStateVarMeta.resize(int(transpiler::ScopeType::Num));
		for (int i = 0; i < int(transpiler::ScopeType::Num); i++)
		{
			transpiler::ScopeType scope = transpiler::ScopeType(i);
			out_compile_data.scopeStateVarMeta[i].signature = pTranspiler->GetScopeStateVariableSignature(scope);
			uint32_t NumPerAddressStateVariable = pTranspiler->GetNumScopeStateVariable(scope);
			out_compile_data.scopeStateVarMeta[i].comment = std::vector<std::string>();
			for (uint32_t j = 0; j < NumPerAddressStateVariable; j++) {
				out_compile_data.scopeStateVarMeta[i].comment.push_back(pTranspiler->GetScopeStateVariableComment(scope, j));
			}
			out_compile_data.scopeStateVarMeta[i].hasAsset = pTranspiler->ScopeStateVariableHasAsset(scope);
			out_compile_data.scopeStateVarMeta[i].hasBlob = pTranspiler->ScopeStateVariableHasBlob(scope);
		}

		for (uint32_t i = 0; i < pTranspiler->GetNumImportedContracts(); i++)
			out_compile_data.importedContracts.push_back(pTranspiler->GetImportedContractFullName(i));

		for (uint32_t i = 0; i < pTranspiler->GetNumExportedFunctions(); i++)
		{
			ContractFunction func;
			func.name = pTranspiler->GetExportedFunctionName(i);
			func.returnType = pTranspiler->GetExportedFunctionReturnType(i);
			const char* comment = pTranspiler->GetExportedFunctionComment(i);
			if(comment != nullptr){
				func.doxygenComment = comment;
			}
			else{
				func.doxygenComment = std::string();
			}
			func.flags = pTranspiler->GetExportedFunctionFlag(i);

			uint32_t numParams = pTranspiler->GetExportedFunctionNumParameters(i);
			for (uint32_t paramIdx = 0; paramIdx < numParams; paramIdx++)
			{
				func.parameters.emplace_back(pTranspiler->GetExportedFunctionParameterType(i, paramIdx), pTranspiler->GetExportedFunctionParameterName(i, paramIdx));
			}

			out_compile_data.functions.push_back(func);
		}

		for (uint32_t interfaceIdx = 0; interfaceIdx < pTranspiler->GetNumExportedInterfaces(); interfaceIdx++)
		{
			ContractInterface ci;
			ci.name = pTranspiler->GetExportedInterfaceName(interfaceIdx);
			for (uint32_t functionIdx = 0; functionIdx < pTranspiler->GetNumExportedInterfaceFunctions(interfaceIdx); functionIdx++)
			{
				ContractFunction func;
				func.name = pTranspiler->GetExportedInterfaceFunctionName(interfaceIdx, functionIdx);
				func.returnType = pTranspiler->GetExportedInterfaceFunctionReturnType(interfaceIdx, functionIdx);
				const char* comment = pTranspiler->GetExportedInterfaceFunctionComment(interfaceIdx, functionIdx);
				if (comment != nullptr) {
					func.doxygenComment = comment;
				}
				else {
					func.doxygenComment = std::string();
				}
				func.flags = pTranspiler->GetExportedInterfaceFunctionFlag(interfaceIdx, functionIdx);

				uint32_t numParams = pTranspiler->GetExportedInterfaceFunctionNumParameters(interfaceIdx, functionIdx);
				for (uint32_t paramIdx = 0; paramIdx < numParams; paramIdx++)
				{
					func.parameters.emplace_back(pTranspiler->GetExportedInterfaceFunctionParameterType(interfaceIdx, functionIdx, paramIdx), pTranspiler->GetExportedInterfaceFunctionParameterName(interfaceIdx, functionIdx, paramIdx));
				}

				ci.functions.push_back(func);
			}
			out_compile_data.interfaces.push_back(ci);
		}
		for (uint32_t interfaceIdx = 0; interfaceIdx < pTranspiler->GetNumImplementedInterfaces(); interfaceIdx++)
		{
			ContractImplementedInterface cii;
			cii.name = pTranspiler->GetImplementedInterfaceName(interfaceIdx);
			for (uint32_t funcIdx = 0; funcIdx < pTranspiler->GetNumImplementedInterfaceFunctions(interfaceIdx); funcIdx++)
				cii.functionIds.push_back(pTranspiler->GetImplementedInterfaceFunctionExportIndex(interfaceIdx, funcIdx));
			out_compile_data.implementedInterfaces.push_back(cii);
		}

		out_compile_data.globalDeployFunctionIdx = pTranspiler->GetGlobalDeployFunctionExportIndex();
		out_compile_data.shardScaleOutFunctionIdx = pTranspiler->GetShardScaleoutFunctionExportIndex();

		for (uint32_t i = 0; i < pTranspiler->GetNumEnumTypes(); i++)
		{
			ContractEnum enumerate;
			enumerate.name = pTranspiler->GetEnumTypeName(i);
			enumerate.doxygenComment = pTranspiler->GetEnumDoxygenComment(i);
			enumerate.enumerators = std::vector<std::string>();
			out_compile_data.enums.emplace_back(enumerate);
			for (uint32_t j = 0; j < pTranspiler->GetNumEnumerators(i); j++)
				out_compile_data.enums.back().enumerators.push_back(pTranspiler->GetEnumerator(i, j));
		}

		for (uint32_t i = 0; i < pTranspiler->GetNumStructTypes(); i++)
		{
			out_compile_data.structs.emplace_back();
			out_compile_data.structs.back().doxygenComment = pTranspiler->GetStructDoxygenComment(i);
			out_compile_data.structs.back().name = pTranspiler->GetStructTypeName(i);
			for (uint32_t j = 0; j < pTranspiler->GetNumStructMembers(i); j++)
				out_compile_data.structs.back().members.emplace_back(pTranspiler->GetStructMemberType(i, j), pTranspiler->GetStructMemberName(i, j));
		}
	}

	return true;
}

bool CContractDatabase::Link(rvm::CompiledModules* compiled, rvm::LogMessageOutput* log_msg_output)
{
	EnterCSBlock(m_barrier);

	bool bSuccess = true;

	PredaCompiledContracts *pCompiledContracts = (PredaCompiledContracts *)compiled;

	std::vector<ContractLinkData> linkData(pCompiledContracts->GetCount());

	for (uint32_t contractIdx = 0; contractIdx < pCompiledContracts->GetCount(); contractIdx++)
	{
		PredaLogMessages logMsgs;
		if (!LinkContract(pCompiledContracts->GetContractSourceCode(contractIdx), pCompiledContracts->GetContractIntermediateCode(contractIdx), linkData[contractIdx], logMsgs))
			bSuccess = false;

		if (log_msg_output)
		{
			for (uint32_t msgIdx = 0; msgIdx < logMsgs.GetCount(); msgIdx++)
			{
				LogMessage msg = logMsgs.Get(msgIdx);
				log_msg_output->Log(msg.Type, msg.Code, contractIdx, msg.Line, msg.LineOffset, &msg.Message);
			}
		}
	}

	if (bSuccess)
		pCompiledContracts->AttachLinkData(std::move(linkData));

	return bSuccess;
}

bool CContractDatabase::LinkContract(const std::string &source_code, const std::string &intermediate_code, ContractLinkData &out_link_data, PredaLogMessages &out_log)
{
	EnterCSBlock(m_barrier);

	char s[30];
#ifdef _WIN32
	sprintf_s(s, "_stage%016llx", m_nextLinkStageIdx++);
#else
	sprintf(s, "_stage%016lx", m_nextLinkStageIdx++);
#endif
	std::string contractIdString = s;

	const std::string contractIntermediateFilePathFileName = "intermediate/" + contractIdString + ".cpp";
	const std::string contractBinPathFileName = "bin/" + contractIdString + (
		m_runtime_mode == RuntimeMode::NATIVE ? EXECUTABLE_EXTENSION :
		m_runtime_mode == RuntimeMode::WASM ? ".wasm" :".cwasm");
	{
		os::File intermediateFile;
		if (!intermediateFile.Open((m_dbPath + contractIntermediateFilePathFileName).c_str(), os::File::Normal_Write, true))
		{
			out_log.AddMessage(0, 0, 0, ("Cannot write " + m_dbPath + contractIntermediateFilePathFileName).c_str());
			return false;
		}
		intermediateFile.Write(intermediate_code.c_str());
		if (intermediateFile.ErrorOccured())
		{
			out_log.AddMessage(0, 0, 0, ("Cannot write " + m_dbPath + contractIntermediateFilePathFileName).c_str());
			return false;
		}
		intermediateFile.Close();
	}

	{
		os::File templateFile;
		if (!templateFile.Open((m_dbPath + "/transpiledCode.cpp").c_str(), os::File::Normal_Write, true))
		{
			out_log.AddMessage(0, 0, 0, ("Cannot write " + m_dbPath + "/transpiledCode.cpp").c_str());
			return false;
		}
		templateFile.Write(("#include \"" + m_modulePath + "../compile_env/contract_template.h" + "\"\n").c_str());
		templateFile.Write(("#include \"" + m_dbPath + contractIntermediateFilePathFileName + "\"\n").c_str());
		if (templateFile.ErrorOccured())
		{
			out_log.AddMessage(0, 0, 0, ("Cannot write " + m_dbPath + "/transpiledCode.cpp").c_str());
			return false;
		}
		templateFile.Close();
	}

	{
		os::File::CreateDirectories((m_dbPath + contractBinPathFileName).c_str(), true);

#if	defined(__linux__) || defined(__linux) || defined(__APPLE__)
		if (m_runtime_mode == RuntimeMode::NATIVE)
		{
			std::string cmdLine = "g++ -O3 -I" + m_modulePath + "../compile_env/ -shared -fPIC -std=c++17 -o\"" + m_dbPath + contractBinPathFileName + "\" \"" + m_dbPath + "/transpiledCode.cpp\" 2>&1";
			FILE *pipe = popen(cmdLine.c_str(), "r");
			if (pipe == nullptr)
			{
				out_log.AddMessage(0, 0, 0, ("Failed to execute " + cmdLine).c_str());
				return false;
			}
			else
			{
				char buffer[128];
				std::string result;
				while (fgets(buffer, sizeof(buffer), pipe) != NULL)
					result += buffer;
				int res = pclose(pipe);
				if (res != 0)
				{
					out_log.AddMessage(0, 0, 0, result.c_str());
					return false;
				}
			}
		}
		else
		{
			std::string out_wasm = m_dbPath + "bin/" + contractIdString + ".wasm";
#if defined(__APPLE__)
			std::string cmdLine = m_modulePath + "../emscripten/3.1.24/emsdk activate 3.1.24 2>&1 && " +
				"source " + m_modulePath + "../emscripten/3.1.24/emsdk_env.sh 2>&1 && "
				"emcc -Oz --profiling-funcs --no-entry -DNDEBUG -sRELOCATABLE -sALLOW_MEMORY_GROWTH -sMALLOC=none -fPIC -fvisibility=hidden -sERROR_ON_UNDEFINED_SYMBOLS=0 -I" +
				m_modulePath + "../compile_env/ -std=c++17 -o\"" +
				out_wasm + "\" \"" + m_dbPath + "transpiledCode.cpp\" 2>&1";
#else
			std::string cmdLine = std::string("bash -c \"") +  m_modulePath + "../emscripten/3.1.24/emsdk activate 3.1.24 && " +
				"source " + m_modulePath + "../emscripten/3.1.24/emsdk_env.sh && "
				"emcc -Oz --profiling-funcs --no-entry -DNDEBUG -sRELOCATABLE -sALLOW_MEMORY_GROWTH -sMALLOC=none -fPIC -fvisibility=hidden -sERROR_ON_UNDEFINED_SYMBOLS=0 -I" +
				m_modulePath + "../compile_env/ -std=c++17 -o" +
				out_wasm + " " + m_dbPath + "/transpiledCode.cpp\" 2>&1";
#endif
			FILE *pipe = popen(cmdLine.c_str(), "r");
			if (!pipe)
			{
				out_log.AddMessage(0, 0, 0, ("Failed to execute " + cmdLine).c_str());
				return false;
			}
			else
			{
				char buffer[128];
				std::string result;
				while (fgets(buffer, sizeof(buffer), pipe) != NULL)
					result += buffer;
				int res = pclose(pipe);
				if (res != 0)
				{
					out_log.AddMessage(0, 0, 0, result.c_str());
					return false;
				}
			}
			if (m_runtime_mode == RuntimeMode::CWASM) {
				rt::String wasm_mod;
				if (!os::File::LoadBinary(out_wasm.c_str(), wasm_mod)) {
					return false;
				}
				auto maybe_mod = wasmtime::Module::compile(m_wasm_engine, wasmtime::Span<uint8_t>((uint8_t*)wasm_mod.Begin(), wasm_mod.GetLength()));
				if (!maybe_mod) {
					return false;
				}
				auto mod = maybe_mod.unwrap();
				std::optional<wasmtime_dylink_meminfo_t> dylink_info = mod.dylinkInfo();
				if (!dylink_info) {
					return false;
				}
				auto cwasm = mod.serialize();
				if (!cwasm) {
					return false;
				}
				std::vector<uint8_t> cwasm_data = cwasm.ok();
				std::string out_cwasm = m_dbPath + contractBinPathFileName;
				if (!os::File::Remove(out_wasm.c_str())) {
					return false;
				}
				if (!os::File::SaveBinary(out_cwasm.c_str(), rt::DS(cwasm_data.data(), cwasm_data.size()))) {
					return false;
				}
			}
		}

#elif defined(_WIN32)
		os::LaunchProcess processLauncher;
		std::string configFilePath = m_modulePath + "../compile_env/config.txt";
		os::File config_File;
		// in order to compile with msvc, create a config.txt file under compile_env dir and write it with the absolute path to vcvars64.bat
		// for example : C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat
		if (!config_File.Open(configFilePath.c_str()))
		{
			if (m_runtime_mode == RuntimeMode::NATIVE)
			{
				std::string cmdLine = m_modulePath + "../mingw64/bin/g++ -O3 -I" + m_modulePath + "../compile_env/ -shared -std=c++17 -o \"" + m_dbPath + contractBinPathFileName + "\" \"" + m_dbPath + "/transpiledCode.cpp\"";
				if (!processLauncher.Launch(cmdLine.c_str(), os::LaunchProcess::FLAG_SAVE_OUTPUT))
				{
					out_log.AddMessage(0, 0, 0, ("Failed to execute " + cmdLine).c_str());
					return false;
				}
				while (processLauncher.IsRunning()) 
				{
					if (m_cancel.IsSignaled()) {
						processLauncher.Terminate();
						return false;
					}
					else {
						processLauncher.WaitForEnding(100);
					}
				}
				if (processLauncher.GetExitCode() != 0)
				{
					out_log.AddMessage(0, 0, 0, processLauncher.GetOutput());
					return false;
				}
			}
			else {
				std::string out_wasm = m_dbPath + "bin/" + contractIdString + ".wasm";
				std::string cmdLine = std::string("emsdk.bat activate 3.1.24 && ") +
					"emcc -Oz --profiling-funcs --no-entry -DNDEBUG -sRELOCATABLE -sALLOW_MEMORY_GROWTH -sMALLOC=none -fPIC -fvisibility=hidden -sERROR_ON_UNDEFINED_SYMBOLS=0 -I" +
					m_modulePath + "../compile_env/ -std=c++17 -o" +
					out_wasm + " " + m_dbPath + "transpiledCode.cpp";
				if (!processLauncher.Launch(cmdLine.c_str(), os::LaunchProcess::FLAG_SAVE_OUTPUT))
				{
					out_log.AddMessage(0, 0, 0, ("Failed to execute " + cmdLine).c_str());
					return false;
				}
				while (processLauncher.IsRunning())
				{
					if (m_cancel.IsSignaled()) {
						processLauncher.Terminate();
						return false;
					}
					else {
						processLauncher.WaitForEnding(100);
					}
				}
				if (processLauncher.GetExitCode() != 0)
				{
					out_log.AddMessage(0, 0, 0, processLauncher.GetOutput());
					return false;
				}
				if (m_runtime_mode == RuntimeMode::CWASM) {
					rt::String wasm_mod;
					if (!os::File::LoadBinary(out_wasm.c_str(), wasm_mod)) {
						return false;
					}
					auto maybe_mod = wasmtime::Module::compile(m_wasm_engine, wasmtime::Span<uint8_t>((uint8_t*)wasm_mod.Begin(), wasm_mod.GetLength()));
					if (!maybe_mod) {
						return false;
					}
					auto mod = maybe_mod.unwrap();
					std::optional<wasmtime_dylink_meminfo_t> dylink_info = mod.dylinkInfo();
					if (!dylink_info) {
						return false;
					}
					auto cwasm = mod.serialize();
					if (!cwasm) {
						return false;
					}
					std::vector<uint8_t> cwasm_data = cwasm.ok();
					std::string out_cwasm = m_dbPath + contractBinPathFileName;
					if (!os::File::Remove(out_wasm.c_str())) {
						return false;
					}
					if (!os::File::SaveBinary(out_cwasm.c_str(), rt::DS(cwasm_data.data(), cwasm_data.size()))) {
						return false;
					}
				}
			}
		}
		else {
			std::string cmdLine = "cl /LDd /Zi /D \"WIN32\" /D \"_DEBUG\" /D \"TESTPREDADLL_EXPORTS\" /D \"_WINDOWS\" /D \"_USRDLL\" /D \"_WINDLL\" /D \"_UNICODE\" /D \"UNICODE\" /std:c++17 /FC /EHsc /Fo -I" + m_modulePath + "../compile_env/ " + m_dbPath + "/transpiledCode.cpp -o" + m_dbPath + contractBinPathFileName;
			SIZE_T eof = config_File.SeekToEnd();
			config_File.SeekToBegin();
			std::vector<char> buf;
			buf.resize(eof + 1);
			config_File.Read(&buf[0], eof);
			buf[eof] = '\0';
			std::string VSCommand(&buf[0], eof);
			VSCommand = VSCommand + " && " + cmdLine;
			if (!processLauncher.Launch(VSCommand.c_str(), os::LaunchProcess::FLAG_SAVE_OUTPUT))
			{
				out_log.AddMessage(0, 0, 0, ("Failed to execute " + cmdLine).c_str());
				return false;
			}
			while (processLauncher.IsRunning())
			{
				if (m_cancel.IsSignaled()) {
					processLauncher.Terminate();
					return false;
				}
				else {
					processLauncher.WaitForEnding(100);
				}
			}
			if (processLauncher.GetExitCode() != 0)
			{
				out_log.AddMessage(0, 0, 0, processLauncher.GetOutput());
				return false;
			}
		}

#endif
	}

	std::string contractSrcPathFileName = "src/" + contractIdString + ".prd";
	{
		os::File srcFile;
		if (!srcFile.Open((m_dbPath + contractSrcPathFileName).c_str(), os::File::Normal_Write, true))
		{
			out_log.AddMessage(0, 0, 0, ("Cannot write " + m_dbPath + contractSrcPathFileName).c_str());
			return false;
		}
		srcFile.Write(source_code.c_str());
		if (srcFile.ErrorOccured())
		{
			out_log.AddMessage(0, 0, 0, ("Cannot write " + m_dbPath + contractSrcPathFileName).c_str());
			return false;
		}
		srcFile.Close();
	}

	if (m_cancel.IsSignaled()) {
		return false;
	}

	{
		out_link_data.binaryPathFileName = contractBinPathFileName;
		out_link_data.srcPathFileName = contractSrcPathFileName;
		out_link_data.intermediatePathFileName = contractIntermediateFilePathFileName;
	}

	return true;
}

void CContractDatabase::CancelCurrentBuildingTask()
{
	m_cancel.Set();
}

bool CContractDatabase::Deploy(const rvm::GlobalStates* chain_state, rvm::CompiledModules* linked, const rvm::ContractVersionId* target_cvids, rvm::DataBuffer** out_stub, rvm::LogMessageOutput* log_msg_output)
{
	// generating stub requires chain_state
	if (out_stub && !chain_state)
		return false;

	PredaCompiledContracts* pCompiledContracts = (PredaCompiledContracts*)linked;
	assert(pCompiledContracts->IsLinked());

	uint32_t numContracts = linked->GetCount();
	std::vector<rvm::ContractVersionId> contractIds(numContracts);
	for (uint32_t i = 0; i < numContracts; i++)
	{
		if (target_cvids)
		{
			contractIds[i] = target_cvids[i];
		}
		else if (chain_state)
		{
			const ContractCompileData* pCompiledData = pCompiledContracts->GetCompiledData(i);
			contractIds[i] = _details::GetOnChainContractIdFromContractFullName(chain_state, pCompiledData->dapp + "." + pCompiledData->name);
			if (contractIds[i] == rvm::ContractVersionIdInvalid)
				return false;
		}
	}

	EnterCSBlock(m_barrier);

	bool bSuccess = true;

	uint32_t contracts_count = pCompiledContracts->GetCount();
	std::vector<ContractDatabaseEntry> entries(contracts_count);

	for (uint32_t contractIdx = 0; contractIdx < contracts_count; contractIdx++)
		entries[contractIdx].compileData = *pCompiledContracts->GetCompiledData(contractIdx);

	for (uint32_t contractIdx = 0; contractIdx < contracts_count; contractIdx++)
	{
		// it could happen that the module id is already used, in which case there's no need to rename the files
		if (m_contracts.find(entries[contractIdx].compileData.moduleId) == m_contracts.end())
		{
			rvm::ContractVersionId contractId = contractIds[contractIdx];

			// move corresponding files from linked stage to final location
			std::vector<char> s(entries[contractIdx].compileData.name.size() + 100);
#ifdef _WIN32
			sprintf_s(&s[0], s.size(), "%lld_%016llx_%s", m_nextDeployId + contractIdx, uint64_t(contractId), entries[contractIdx].compileData.name.c_str());
#else
			sprintf(&s[0], "%lu_%016lx_%s", uint64_t(contractId), m_nextDeployId + contractIdx, entries[contractIdx].compileData.name.c_str());
#endif
			std::string contractIdString = &s[0];
			entries[contractIdx].linkData.intermediatePathFileName = "intermediate/" + contractIdString + ".cpp";
			entries[contractIdx].linkData.binaryPathFileName = "bin/" + contractIdString + (
				m_runtime_mode == RuntimeMode::NATIVE ? EXECUTABLE_EXTENSION :
				m_runtime_mode == RuntimeMode::WASM ? ".wasm" : ".cwasm");
			entries[contractIdx].linkData.srcPathFileName = "src/" + contractIdString + ".prd";
			if (!os::File::Rename((m_dbPath + pCompiledContracts->GetLinkData(contractIdx)->intermediatePathFileName).c_str(), (m_dbPath + entries[contractIdx].linkData.intermediatePathFileName).c_str())
				|| !os::File::Rename((m_dbPath + pCompiledContracts->GetLinkData(contractIdx)->binaryPathFileName).c_str(), (m_dbPath + entries[contractIdx].linkData.binaryPathFileName).c_str())
				|| !os::File::Rename((m_dbPath + pCompiledContracts->GetLinkData(contractIdx)->srcPathFileName).c_str(), (m_dbPath + entries[contractIdx].linkData.srcPathFileName).c_str()))
			{
				if (log_msg_output)
				{
					std::string tmp = "contract " + entries[contractIdx].compileData.name + " deploy to disk failed";
					rt::String_Ref tmp1(tmp.c_str());
					log_msg_output->Log(rvm::LogMessageType::Error, 0, contractIdx, 0, 0, (rvm::ConstString*)&tmp1);
				}
				bSuccess = false;
				continue;
			}
		}

		if(os::File::IsExist((m_modulePath + "../compile_env/config.txt").c_str())){
			os::File src,dst;
			rt::Buffer<BYTE>	buf;
			if(	buf.SetSize(2*1024*1024) &&
				src.Open((m_dbPath + entries[contractIdx].linkData.intermediatePathFileName).c_str()) &&
				dst.Open((m_dbPath + pCompiledContracts->GetLinkData(contractIdx)->intermediatePathFileName).c_str(), os::File::Normal_Write, true)
			)
			{	ULONGLONG fsize = src.GetLength();
				while(fsize)
				{
					int block = (int)rt::min((ULONGLONG)buf.GetSize(), fsize);
					if(	src.Read(buf, block) == block &&
						dst.Write(buf, block) == block
					)
					{	fsize -= block;
					}
					else
					{
						if(dst.IsOpen())
						{
							dst.Close();
							os::File::Remove((m_dbPath + pCompiledContracts->GetLinkData(contractIdx)->intermediatePathFileName).c_str());
							break;
						}
					}
				}
			}
		}

		if (out_stub)
		{
			std::vector<rvm::ContractVersionId> importedContractIds(entries[contractIdx].compileData.importedContracts.size());
			for (uint32_t importedContractIdx = 0; importedContractIdx < entries[contractIdx].compileData.importedContracts.size(); importedContractIdx++)
			{
				const std::string& importedContractName = entries[contractIdx].compileData.importedContracts[importedContractIdx];

				rvm::ContractVersionId importedContractId = rvm::ContractVersionIdInvalid;

				// first look in the contracts that are being deployed
				for (uint32_t i = 0; i < contracts_count; i++)
				{
					if (entries[i].compileData.dapp + "." + entries[i].compileData.name == importedContractName)
					{
						importedContractId = contractIds[i];
						break;
					}
				}

				// then look in the chain state
				if (importedContractId == rvm::ContractVersionIdInvalid && chain_state)
					importedContractId = _details::GetOnChainContractIdFromContractFullName(chain_state, importedContractName);

				if (importedContractId == rvm::ContractVersionIdInvalid)
				{
					if (log_msg_output)
					{
						std::string tmp = "imported contract " + importedContractName + " not found";
						rt::String_Ref tmp1(tmp.c_str());
						log_msg_output->Log(rvm::LogMessageType::Error, 0, contractIdx, 0, 0, (rvm::ConstString*)&tmp1);
					}
					bSuccess = false;
					continue;
				}

				importedContractIds[importedContractIdx] = importedContractId;
			}

			if (bSuccess && importedContractIds.size())
			{
				uint8_t* buffer = out_stub[contractIdx]->SetSize(uint32_t(importedContractIds.size() * sizeof(importedContractIds[0])));
				memcpy(buffer, &importedContractIds[0], out_stub[contractIdx]->GetSize());
			}
		}
	}

	if (bSuccess)
	{
		for (uint32_t idx = 0; idx < contracts_count; idx++)
		{
			const rvm::ContractModuleID& moduleId = entries[idx].compileData.moduleId;

			// it's possible that there's already this module id in DB
			auto itor = m_contracts.find(moduleId);
			if (itor == m_contracts.end())
			{
				m_contracts.try_emplace(moduleId, entries[idx]);
				std::string json = ConvertEntryToJson(&entries[idx]);
				m_contractDB.Set(moduleId, json.c_str());
			}
		}
	}

	return bSuccess;
}

template<typename T>
void CContractDatabase::mergeTwoImportList(std::vector<T>& all_import_list, std::vector<T>& incoming_import_list)
{
	//1. current iterator points to all_import_list's beginning element
	//2. for every element in the incoming_import_list, if an element exists in the all_import_list, we do not insert the element but we move the current iterator to that position
	//3. if an element does not exist in the all_import_list, we insert it at the current position and current position++;
	//4. if all_import_list is empty, we assign incoming_import_list to all_import_list
	//5. import_list include the target contract id
	if(all_import_list.empty()){
		all_import_list = incoming_import_list;
		return;
	}
	typename std::vector<T>::iterator current = all_import_list.begin();
  	for(int i = 0; i < incoming_import_list.size(); i++)
	{
		typename std::vector<T>::iterator last = std::find(all_import_list.begin(), all_import_list.end(), incoming_import_list[i]);
    	if (last == all_import_list.end())
		{
      		last = current;
      		current = all_import_list.insert(last, incoming_import_list[i]);
    	}
    	else
		{
      		current = last;
    	}
		current++;
	}
}

std::string CContractDatabase::ConvertEntryToJson(const ContractDatabaseEntry *pEntry)
{
	std::string json;
	json = "\t{\n";
	{
		rt::Json res;
		::rvm::RvmTypeJsonify(pEntry->compileData.moduleId, res);
		json += "\t\"module_id\": " + std::string(res.GetInternalString()) + ",\n";
	}
	json += "\t\"dapp\": \"" + pEntry->compileData.dapp + "\",\n";
	json += "\t\"name\": \"" + pEntry->compileData.name + "\",\n";
	json += "\t\"comment\": \"" + pEntry->compileData.contractDoxygenComment + "\",\n";

	json += "\t\"export_unique_str\": \"" + pEntry->compileData.exportUniqueString + "\",\n";
	json += "\t\"bin\": \"" + pEntry->linkData.binaryPathFileName + "\",\n";
	json += "\t\"src\": \"" + pEntry->linkData.srcPathFileName + "\",\n";
	json += "\t\"inter\": \"" + pEntry->linkData.intermediatePathFileName + "\",\n";
	{
		rt::Json res;
		::rvm::RvmTypeJsonify(pEntry->compileData.intermediateHash, res);
		json += "\t\"inter_hash\": " + std::string(res.GetInternalString()) + ",\n";
	}

	// state vars
	json += "\t\"sv\": [\n";
	for (int i = 0; i < int(transpiler::ScopeType::Num); i++)
	{
		json += "\t\t{\n";
		json += "\t\t\t\"sig\": \"" + pEntry->compileData.scopeStateVarMeta[i].signature + "\",\n";
		json += "\t\t\t\"comment\": [\n";
		for (int j = 0; j < pEntry->compileData.scopeStateVarMeta[i].comment.size(); j++) {
			if (j > 0)
				json += ", ";
			json += "\"" + pEntry->compileData.scopeStateVarMeta[i].comment[j] + "\"";
		}
		json += "\n\t\t\t],\n";
		json += "\t\t\t\"has_asset\": \"" + std::string(pEntry->compileData.scopeStateVarMeta[i].hasAsset ? "true" : "false") + "\",\n";
		json += "\t\t\t\"has_blob\": \"" + std::string(pEntry->compileData.scopeStateVarMeta[i].hasBlob ? "true" : "false") + "\"\n";
		json += "\t\t}" + std::string(i < int(transpiler::ScopeType::Num) - 1 ? ",":"") + "\n";
	}
	json += "\t],\n";

	json += "\t\"imports\": [\n";
	for (size_t i = 0; i < pEntry->compileData.importedContracts.size(); i++)
	{
		json += "\t\t{\n";
		json += "\t\t\t\"name\": \"" + pEntry->compileData.importedContracts[i] + "\"\n";
		json += i < pEntry->compileData.importedContracts.size() - 1 ? "\t\t},\n" : "\t\t}\n";
	}
	json += "\t],\n";

	json += "\t\"enums\": [\n";
	for (size_t i = 0; i < pEntry->compileData.enums.size(); i++)
	{
		json += "\t\t{\n";
		json += "\t\t\t\"comment\": \"" + pEntry->compileData.enums[i].doxygenComment + "\",\n";
		json += "\t\t\t\"name\": \"" + pEntry->compileData.enums[i].name + "\",\n";
		json += "\t\t\t\"enumerator\": [";
		for (size_t j = 0; j < pEntry->compileData.enums[i].enumerators.size(); j++)
		{
			if (j > 0)
				json += ", ";
			json += "\"" + pEntry->compileData.enums[i].enumerators[j] + "\"";

		}
		json += (i < pEntry->compileData.enums.size() - 1) ? "]\n\t},\n" : "]\n\t}\n";

	}
	json += "\t],\n";
	json += "\t\"structs\": [\n";
	for (size_t i = 0; i < pEntry->compileData.structs.size(); i++)
	{
		json += "\t\t{\n";
		json += "\t\t\t\"comment\": \"" + pEntry->compileData.structs[i].doxygenComment  + "\",\n";
		json += "\t\t\t\"name\": \"" + pEntry->compileData.structs[i].name + "\",\n";
		json += "\t\t\t\"variable\": [";
		for (size_t j = 0; j < pEntry->compileData.structs[i].members.size(); j++)
		{
			if (j > 0)
				json += ", ";
			json += "\"" + pEntry->compileData.structs[i].members[j].first + "\"";
			json += ", \"" + pEntry->compileData.structs[i].members[j].second + "\"";

		}
		json += (i < pEntry->compileData.structs.size() - 1) ? "]\n\t},\n" : "]\n\t}\n";
	}
	json+= "\t],\n";

	json += "\t\"global_deploy_function\": \"" + std::to_string(pEntry->compileData.globalDeployFunctionIdx) + "\",\n";
	json += "\t\"shard_scale_out_function\": \"" + std::to_string(pEntry->compileData.shardScaleOutFunctionIdx) + "\",\n";

	struct __detail
	{
		static void JsonifyFunction(std::string &json, const ContractFunction& func, const std::string &indent)
		{
			json += indent + "{\n";
			json += indent + "\t\"name\": \"" + func.name + "\",\n";
			json += indent + "\t\"comment\": \"" + func.doxygenComment + "\",\n";

			json += indent + "\t\"flags\": " + std::to_string(func.flags) + ",\n";
			json += indent + "\t\"ret_type\": \"" + func.returnType + "\",\n";
			json += indent + "\t\"params\": [";
			for (size_t j = 0; j < func.parameters.size(); j++)
			{
				json += "\"" + func.parameters[j].first + "\", ";
				json += "\"" + func.parameters[j].second + "\"";
				if (j < func.parameters.size() - 1)
					json += ", ";
			}
			json += "]\n";
			json += indent + "}";
		}
	};

	//functions
	json += "\t\"funcs\": [\n";
	for (size_t i = 0; i < pEntry->compileData.functions.size(); i++)
	{
		__detail::JsonifyFunction(json, pEntry->compileData.functions[i], "\t\t");
		json += i < pEntry->compileData.functions.size() - 1 ? ",\n" : "\n";
	}
	json += "\t],\n";

	//interfaces
	json += "\t\"interfaces\": [\n";
	for (size_t i = 0; i < pEntry->compileData.interfaces.size(); i++)
	{
		json += "\t\t{";
		json += "\t\t\t\"name\": \"" + pEntry->compileData.interfaces[i].name + "\",\n";
		json += "\t\t\t\"funcs\": [\n";
		for (size_t j = 0; j < pEntry->compileData.interfaces[i].functions.size(); j++)
		{
			__detail::JsonifyFunction(json, pEntry->compileData.interfaces[i].functions[j], "\t\t\t\t");
			json += j < pEntry->compileData.interfaces[i].functions.size() - 1 ? ",\n" : "\n";
		}
		json += "\t\t\t]\n";
		json += "\t\t}";
		json += i < pEntry->compileData.interfaces.size() - 1 ? ",\n" : "\n";
	}
	json += "\t],\n";

	//implemented interfaces
	json += "\t\"implemented_interfaces\": [\n";
	for (size_t i = 0; i < pEntry->compileData.implementedInterfaces.size(); i++)
	{
		json += "\t\t{";
		json += "\t\t\t\"name\": \"" + pEntry->compileData.implementedInterfaces[i].name + "\",\n";
		{
			rt::Json res;
			::rvm::RvmTypeJsonify(pEntry->compileData.implementedInterfaces[i].interfaceDefContractModuleId, res);
			json += "\t\t\t\"def_module_id\": " + std::string(res.GetInternalString()) + ",\n";
		}
		json += "\t\t\t\"def_slot\": \"" + std::to_string(pEntry->compileData.implementedInterfaces[i].interfaceDefSlot) + "\",\n";
		json += "\t\t\t\"funcs\": [";
		for (size_t j = 0; j < pEntry->compileData.implementedInterfaces[i].functionIds.size(); j++)
		{
			if (j > 0)
				json += ",";
			json += std::to_string(pEntry->compileData.implementedInterfaces[i].functionIds[j]);
		}
		json += "]\n";
		json += "\t\t}";
		json += i < pEntry->compileData.implementedInterfaces.size() - 1 ? ",\n" : "\n";
	}
	json += "\t]\n";


	// closing bracket
	json += "}\n";

	return json;
}

const rvm::Contract* CContractDatabase::GetContract(const rvm::ContractModuleID *module_id) const
{
	EnterCSBlock(m_barrier);

	const ContractDatabaseEntry* pContractEntry = CContractDatabase::FindContractEntry(*module_id);

	if (!pContractEntry)
		return nullptr;

	return const_cast<ContractDatabaseEntry*>(pContractEntry)->GetDelegate();
}

rvm::ExecutionUnit* CContractDatabase::CreateExecuteUnit()
{
	return new CExecutionEngine(this);
}

class CSymbolDatabaseForJsonifier : public rvm::ISymbolDatabaseForJsonifier {
private:
	static std::vector<ContractEnum> s_builtInEnums;
	const CContractDatabase* m_pDB = nullptr;
	const rvm::GlobalStates* m_pChainGlobalState = nullptr;

	std::map<std::string, const ContractDatabaseEntry*> m_contractEntryCache;

	const ContractDatabaseEntry* GetContractEntryFromFullName(const std::string &fullName)
	{
		auto itor = m_contractEntryCache.find(fullName);
		if (itor != m_contractEntryCache.end())
			return itor->second;

		const rvm::ContractModuleID* moduleId = _details::GetOnChainContractModuleIdFromFullName(m_pChainGlobalState, fullName);
		if (moduleId == nullptr)
			return nullptr;
		const ContractDatabaseEntry* pEntry = m_pDB->FindContractEntry(*moduleId);
		m_contractEntryCache.emplace(fullName, pEntry);

		return pEntry;
	}
public:
	CSymbolDatabaseForJsonifier(const CContractDatabase* pDB, const rvm::GlobalStates* pChainGlobalState)
		: m_pDB(pDB)
		, m_pChainGlobalState(pChainGlobalState)
	{
	}

	virtual bool GetEnumValueFromString(const std::string &enumTypeName, const std::string &enumIdentifier, uint16_t &outValue) override
	{
		const std::vector<ContractEnum> *pEnums = nullptr;
		size_t scopePos = enumTypeName.rfind(".");
		std::string nonScopedType;
		if (scopePos == std::string::npos)
		{
			pEnums = &s_builtInEnums;
			nonScopedType = enumTypeName;
		}
		else
		{
			std::string contractFullName = enumTypeName.substr(0, scopePos);
			const ContractDatabaseEntry *pEntry = GetContractEntryFromFullName(contractFullName);
			if (pEntry == nullptr)
				return false;
			pEnums = &pEntry->compileData.enums;
			nonScopedType = enumTypeName.substr(scopePos + 1);
		}

		for (auto &itor : *pEnums)
		{
			if (itor.name == nonScopedType)
			{
				for (size_t i = 0; i < itor.enumerators.size(); i++)
					if (itor.enumerators[i] == enumIdentifier)
					{
						outValue = uint16_t(i);
						return true;
					}

				return false;
			}
		}

		return false;
	}
	virtual const char* GetEnumStringFromValue(const std::string &enumTypeName, uint16_t value) override
	{
		const std::vector<ContractEnum> *pEnums = nullptr;
		size_t scopePos = enumTypeName.rfind(".");
		std::string nonScopedType;
		if (scopePos == std::string::npos)
		{
			pEnums = &s_builtInEnums;
			nonScopedType = enumTypeName;
		}
		else
		{
			std::string contractFullName = enumTypeName.substr(0, scopePos);
			const ContractDatabaseEntry *pEntry = GetContractEntryFromFullName(contractFullName);
			if (pEntry == nullptr)
				return nullptr;
			pEnums = &pEntry->compileData.enums;
			nonScopedType = enumTypeName.substr(scopePos + 1);
		}

		for (auto &itor : *pEnums)
		{
			if (itor.name == nonScopedType)
			{
				if (value < itor.enumerators.size())
					return itor.enumerators[value].c_str();

				return nullptr;
			}
		}

		return nullptr;
	}
	bool ExpandUserDefinedTypes(const std::string &inType, std::string &outType)
	{
		size_t firstScopePos = inType.find_first_of('.');
		if (firstScopePos == std::string::npos)
		{
			for (auto &itor : s_builtInEnums)
			{
				if (itor.name == inType)
				{
					outType = "enum " + inType;
					return true;
				}
			}

			outType = inType;
			return true;
		}
		
		size_t secondScopePos = inType.find_first_of('.', firstScopePos + 1);
		// type is contract
		if (secondScopePos == std::string::npos)
		{
			const ContractDatabaseEntry* pEntry = GetContractEntryFromFullName(inType);
			if (pEntry == nullptr)
				return false;

			outType = "contract";
			return true;
		}

		// type is whatever type defined in a contract
		std::string nonScopedType = inType.substr(secondScopePos + 1);

		std::string contractFullName = inType.substr(0, secondScopePos);
		const ContractDatabaseEntry* pEntry = GetContractEntryFromFullName(contractFullName);
		if (pEntry == nullptr)
			return false;

		for (auto &itor : pEntry->compileData.enums)
		{
			if (itor.name == nonScopedType)
			{
				outType = "enum " + inType;
				return true;
			}
		}

		for (auto &itor : pEntry->compileData.structs)
		{
			if (itor.name == nonScopedType)
			{
				outType = "struct " + std::to_string(itor.members.size());
				for (size_t i = 0; i < itor.members.size(); i++)
				{
					std::string expandedMemberType;
					if (!ExpandUserDefinedTypesInTypeString(itor.members[i].first, expandedMemberType))
						return false;
					outType += " " + expandedMemberType + " " + itor.members[i].second;
				}
				return true;
			}
		}

		for (auto& itor : pEntry->compileData.interfaces)
		{
			if (itor.name == nonScopedType)
			{
				outType = "interface";
				return true;
			}
		}

		return false;
	}
	bool ExpandUserDefinedTypesInTypeString(const std::string &inTypeStr, std::string &outTypeStr)
	{
		std::stringstream inTypeStrStream(inTypeStr);
		outTypeStr = "";
		std::string curType;
		while (inTypeStrStream >> curType)
		{
			std::string expandedType;
			if (!ExpandUserDefinedTypes(curType, expandedType))
				return false;
			if (outTypeStr.length() != 0)
				outTypeStr += " ";
			outTypeStr += expandedType;
		}

		return true;
	}
};

std::vector<ContractEnum> CSymbolDatabaseForJsonifier::s_builtInEnums = {
		{
			ContractEnum{
				std::string(),
				"transaction_type",
				{
					"normal_type",
					"relay_type",
					"system_type",
					"issue_type"
				}
			}
		},
		{
			ContractEnum{
				std::string(),
				"uievent_state",
				{
					"deactivated",
					"activated",
					"locked",
					"unlocked"
				}
			}
		}
};

bool CContractDatabase::StateJsonify(rvm::ContractInvokeId contract, const rvm::ConstData* pState, rvm::StringStream* json_out) const
{
	EnterCSBlock(m_barrier);

	const rvm::DeployedContract *deployedContract = m_pRuntimeAPI->GetContractDeployed(rvm::CONTRACT_UNSET_SCOPE(contract));
	if (!deployedContract)
		return false;
	const ContractDatabaseEntry *pContractEntry = FindContractEntry(deployedContract->Module);
	if (pContractEntry == nullptr)
		return false;
	const std::string *pSig = nullptr;
	rvm::Scope scope = rvm::CONTRACT_SCOPE(contract);
	transpiler::ScopeType predaScope = _details::RvmScopeToPredaScope(scope);
	if (predaScope == transpiler::ScopeType::None)
		return false;

	pSig = &pContractEntry->compileData.scopeStateVarMeta[int(predaScope)].signature;

	CSymbolDatabaseForJsonifier symbolDb(this, m_pRuntimeAPI);
	std::string expandedSig;
	if (!symbolDb.ExpandUserDefinedTypesInTypeString(*pSig, expandedSig))
		return false;
	rvm::RvmDataJsonifier jsonifier(expandedSig.c_str(), &symbolDb);
	std::string jsonStr;
	if (jsonifier.Jsonify(jsonStr, pState->DataPtr, (uint32_t)pState->DataSize, true) != int32_t(pState->DataSize))
		return false;

	json_out->Append(jsonStr.c_str(), uint32_t(jsonStr.length()));
	return true;
}

bool CContractDatabase::StateJsonParse(rvm::ContractInvokeId contract, const rvm::ConstString* json, rvm::DataBuffer* state_out, rvm::LogMessageOutput *log) const
{
	EnterCSBlock(m_barrier);

	const rvm::DeployedContract* deployedContract = m_pRuntimeAPI->GetContractDeployed(rvm::CONTRACT_UNSET_SCOPE(contract));
	if (!deployedContract)
		return false;
	const ContractDatabaseEntry* pContractEntry = FindContractEntry(deployedContract->Module);
	if (pContractEntry == nullptr)
	{
		if (log)
		{
			rt::String_Ref msg = "invalid contract id.";
			log->Log(rvm::LogMessageType::Error, uint32_t(rvm::JsonParseErrorCode::InvalidContractId), 0, 0, 0, (rvm::ConstString*)&msg);
		}
		return false;
	}
	const std::string *pSig = nullptr;
	rvm::Scope scope = rvm::CONTRACT_SCOPE(contract);
	transpiler::ScopeType predaScope = _details::RvmScopeToPredaScope(scope);
	if (predaScope == transpiler::ScopeType::None)
	{
		if (log)
		{
			rt::String_Ref msg = "invalid scope.";
			log->Log(rvm::LogMessageType::Error, uint32_t(rvm::JsonParseErrorCode::InvalidContractId), 0, 0, 0, (rvm::ConstString*)&msg);
		}
		return false;
	}

	pSig = &pContractEntry->compileData.scopeStateVarMeta[int(predaScope)].signature;

	std::vector<uint8_t> ret;

	CSymbolDatabaseForJsonifier symbolDb(this, m_pRuntimeAPI);
	std::string expandedSig;
	if (!symbolDb.ExpandUserDefinedTypesInTypeString(*pSig, expandedSig))
	{
		if (log)
		{
			rt::String_Ref msg = "Internal error. Cannot expand data type.";
			log->Log(rvm::LogMessageType::Error, uint32_t(rvm::JsonParseErrorCode::ExpandDataTypeError), 0, 0, 0, (rvm::ConstString*)&msg);
		}
		return false;
	}

	rvm::RvmDataJsonParser dejsonifier(expandedSig.c_str(), &symbolDb);
	if (!dejsonifier.JsonParse(*(rt::String_Ref*)json, ret))
	{
		if (log)
		{
			rt::String_Ref msg = dejsonifier.GetErrorMsg().c_str();
			log->Log(rvm::LogMessageType::Error, uint32_t(dejsonifier.GetErrorCode()), 0, 0, uint32_t(dejsonifier.GetErrorPos() - ((rt::String_Ref*)json)->Begin()), (rvm::ConstString*)&msg);
		}
		return false;
	}

	uint8_t *pWrite = state_out->SetSize(uint32_t(ret.size()));
	if (ret.size() > 0)
		memcpy(pWrite, &ret[0], ret.size());

	return true;
}

bool CContractDatabase::ArgumentsJsonify(rvm::ContractInvokeId contract, rvm::OpCode opCode, const rvm::ConstData* args_serialized, rvm::StringStream* json_out) const
{
	EnterCSBlock(m_barrier);

	const rvm::DeployedContract* deployedContract = m_pRuntimeAPI->GetContractDeployed(rvm::CONTRACT_UNSET_SCOPE(contract));
	if (!deployedContract)
		return false;
	const ContractDatabaseEntry* pContractEntry = FindContractEntry(deployedContract->Module);
	if (pContractEntry == nullptr)
		return false;

	if (enum_to_underlying(opCode) >= uint32_t(pContractEntry->compileData.functions.size()))
		return false;

	const ContractFunction &func = pContractEntry->compileData.functions[enum_to_underlying(opCode)];

	std::string jsonStr;
	jsonStr = "{";
	CSymbolDatabaseForJsonifier symbolDb(this, m_pRuntimeAPI);
	const uint8_t *args_ptr = args_serialized->DataPtr;
	uint32_t args_size = (uint32_t)args_serialized->DataSize;

	for (int i = 0; i < (int)func.parameters.size(); i++)
	{
		std::string paramType;
		if (!symbolDb.ExpandUserDefinedTypesInTypeString(func.parameters[i].first, paramType))
			return false;
		const char *pTypeString = paramType.c_str();
		// skip the const modifier
		if (paramType.length() >= 2 && paramType[0] == 'c' && paramType[1] == ' ')
			pTypeString += 2;

		rvm::RvmDataJsonifier jsonifier(pTypeString, &symbolDb);
		std::string paramJson;
		int32_t numConsumedBytes = jsonifier.Jsonify(paramJson, args_ptr, args_size, true);
		if (numConsumedBytes == -1)
			return false;

		args_ptr += numConsumedBytes;
		args_size -= numConsumedBytes;

		if (i > 0)
			jsonStr += ", ";
		jsonStr += "\"" + func.parameters[i].second + "\": ";
		jsonStr += paramJson;
	}
	jsonStr += "}";

	if (args_size != 0)
		return false;

	json_out->Append(jsonStr.c_str(), uint32_t(jsonStr.length()));
	return true;
}

bool CContractDatabase::VariableJsonify(rvm::ContractModuleID deployId, const char *type_string, const uint8_t *args_serialized, uint32_t args_size, std::string &outJson, const rvm::ChainStates* ps) const
{
	EnterCSBlock(m_barrier);

	const ContractDatabaseEntry *pContractEntry = FindContractEntry(deployId);
	if (pContractEntry == nullptr)
		return false;

	CSymbolDatabaseForJsonifier symbolDb(this, ps);

	std::string varType;
	if (!symbolDb.ExpandUserDefinedTypesInTypeString(type_string, varType))
		return false;
	const char *pTypeString = varType.c_str();

	// skip the const modifier
	if (varType.length() >= 2 && varType[0] == 'c' && varType[1] == ' ')
		pTypeString += 2;

	bool needQuotation = true;
	std::istringstream iss(pTypeString);
	std::string first_type;
	if ((iss >> first_type) && first_type == "string")
		needQuotation = false;

	rvm::RvmDataJsonifier jsonifier(pTypeString, &symbolDb);
	if (jsonifier.Jsonify(outJson, args_serialized, args_size, needQuotation) != int32_t(args_size))
		return false;

	return true;
}

bool CContractDatabase::ArgumentsJsonParse(rvm::ContractInvokeId contract, rvm::OpCode opCode, const rvm::ConstString* json, rvm::DataBuffer* args_out, rvm::LogMessageOutput *log) const
{
	EnterCSBlock(m_barrier);

	const rvm::DeployedContract* deployedContract = m_pRuntimeAPI->GetContractDeployed(rvm::CONTRACT_UNSET_SCOPE(contract));
	if (!deployedContract)
		return false;
	const ContractDatabaseEntry* pContractEntry = FindContractEntry(deployedContract->Module);
	if (pContractEntry == nullptr)
		return false;

	if (enum_to_underlying(opCode) >= uint32_t(pContractEntry->compileData.functions.size()))
	{
		if (log)
		{
			rt::String_Ref msg = "invalid contract id.";
			log->Log(rvm::LogMessageType::Error, uint32_t(rvm::JsonParseErrorCode::InvalidContractId), 0, 0, 0, (rvm::ConstString*)&msg);
		}

		return false;
	}

	const ContractFunction &func = pContractEntry->compileData.functions[enum_to_underlying(opCode)];

	if (rt::JsonKeyValuePair::GetValueType(*(rt::String_Ref *)json) != rt::JSON_OBJECT)
	{
		if (log)
		{
			rt::String_Ref msg = "Data type mismatch. Expecting object.";
			log->Log(rvm::LogMessageType::Error, uint32_t(rvm::JsonParseErrorCode::JsonDataTypeMismatch), 0, 0, 0, (rvm::ConstString*)&msg);
		}
		return false;
	}
	rt::JsonObject jsonObj(json->StrPtr, (uint32_t)json->Length);

	std::vector<uint8_t> ret;

	CSymbolDatabaseForJsonifier symbolDb(this, m_pRuntimeAPI);
	for (int i = 0; i < (int)func.parameters.size(); i++)
	{
		rt::String_Ref data;
		bool bExist;

		data = jsonObj.GetValue(func.parameters[i].second.c_str(), bExist);
		if (!bExist)
		{
			if (log)
			{
				std::string tmp = "Object missing expected member \"" + func.parameters[i].second + "\".";
				rt::String_Ref msg = tmp.c_str();
				log->Log(rvm::LogMessageType::Error, uint32_t(rvm::JsonParseErrorCode::JsonObjectMemberMissing), 0, 0, 0, (rvm::ConstString*)&msg);
			}
			return false;
		}

		std::string paramType;
		if (!symbolDb.ExpandUserDefinedTypesInTypeString(func.parameters[i].first, paramType))
		{
			if (log)
			{
				rt::String_Ref msg = "Internal error. Type stream has invalid format.";
				log->Log(rvm::LogMessageType::Error, uint32_t(rvm::JsonParseErrorCode::TypeStreamFormatError), 0, 0, 0, (rvm::ConstString*)&msg);
			}
			return false;
		}

		const char *pTypeString = paramType.c_str();
		// skip the const modifier
		if (paramType.length() >= 2 && paramType[0] == 'c' && paramType[1] == ' ')
			pTypeString += 2;

		std::vector<uint8_t> buffer;
		rvm::RvmDataJsonParser dejsonifier(pTypeString, &symbolDb);
		if (!dejsonifier.JsonParse(data, buffer))
		{
			if (log)
			{
				rt::String_Ref msg = dejsonifier.GetErrorMsg().c_str();
				log->Log(rvm::LogMessageType::Error, uint32_t(dejsonifier.GetErrorCode()), 0, 0, uint32_t(dejsonifier.GetErrorPos() - ((rt::String_Ref*)json)->Begin()), (rvm::ConstString*)&msg);
			}
			return false;
		}

		ret.insert(ret.end(), buffer.begin(), buffer.end());
	}

	uint8_t *pWrite = args_out->SetSize(uint32_t(ret.size()));
	if (ret.size() > 0)
		memcpy(pWrite, &ret[0], ret.size());

	return true;
}

bool CContractDatabase::GetContractFunctionArgumentsSignature(rvm::ContractInvokeId contract, rvm::OpCode opcode, rvm::StringStream* signature_out) const
{
	EnterCSBlock(m_barrier);

	const rvm::DeployedContract* deployedContract = m_pRuntimeAPI->GetContractDeployed(rvm::CONTRACT_UNSET_SCOPE(contract));
	if (!deployedContract)
		return false;
	const ContractDatabaseEntry* pContractEntry = FindContractEntry(deployedContract->Module);
	if (pContractEntry == nullptr)
		return false;

	if (enum_to_underlying(opcode) >= uint32_t(pContractEntry->compileData.functions.size()))
		return false;

	const ContractFunction &func = pContractEntry->compileData.functions[enum_to_underlying(opcode)];

	std::string ret;

	CSymbolDatabaseForJsonifier symbolDb(this, m_pRuntimeAPI);
	for (int i = 0; i < (int)func.parameters.size(); i++)
	{
		std::string paramType;
		if (!symbolDb.ExpandUserDefinedTypesInTypeString(func.parameters[i].first, paramType))
			return false;

		const char *pTypeString = paramType.c_str();
		// skip the const modifier
		if (paramType.length() >= 2 && paramType[0] == 'c' && paramType[1] == ' ')
			pTypeString += 2;

		if (i > 0)
			ret += std::string(" ");
		ret += std::string(pTypeString) + " " + func.parameters[i].second;
	}

	signature_out->Append(ret.c_str(), uint32_t(ret.size()));

	return true;
}

bool CContractDatabase::GetContractStateSignature(rvm::ContractInvokeId contract, rvm::StringStream* signature_out) const
{
	EnterCSBlock(m_barrier);

	const rvm::DeployedContract* deployedContract = m_pRuntimeAPI->GetContractDeployed(rvm::CONTRACT_UNSET_SCOPE(contract));
	if (!deployedContract)
		return false;
	const ContractDatabaseEntry* pContractEntry = FindContractEntry(deployedContract->Module);
	if (pContractEntry == nullptr)
		return false;
	const std::string *pSig = nullptr;
	rvm::Scope scope = rvm::CONTRACT_SCOPE(contract);
	transpiler::ScopeType predaScope = _details::RvmScopeToPredaScope(scope);
	if (predaScope == transpiler::ScopeType::None)
		return false;

	pSig = &pContractEntry->compileData.scopeStateVarMeta[int(predaScope)].signature;

	CSymbolDatabaseForJsonifier symbolDb(this, m_pRuntimeAPI);
	std::string expandedSig;
	if (!symbolDb.ExpandUserDefinedTypesInTypeString(*pSig, expandedSig))
		return false;

	signature_out->Append(expandedSig.c_str(), uint32_t(expandedSig.size()));

	return true;
}

uint32_t CContractDatabase::GetContractEnumSignatures(rvm::ContractVersionId contract, rvm::StringStream* signature_out) const
{
	EnterCSBlock(m_barrier);

	const rvm::DeployedContract* deployedContract = m_pRuntimeAPI->GetContractDeployed(contract);
	if (!deployedContract)
		return false;
	const ContractDatabaseEntry* pContractEntry = FindContractEntry(deployedContract->Module);
	if (pContractEntry == nullptr)
		return 0;

	uint32_t numEnum = uint32_t(pContractEntry->compileData.enums.size());

	std::string ret;

	for (uint32_t i = 0; i < numEnum; i++)
	{
		const auto &entry = pContractEntry->compileData.enums[i];
		ret += entry.name + '=';
		uint32_t numEnumerator = uint32_t(entry.enumerators.size());
		for (uint32_t j = 0; j < numEnumerator; j++)
		{
			if (j > 0)
				ret += ',';
			ret += entry.enumerators[j];
		}
		ret += '\n';
	}


	signature_out->Append(ret.c_str(), uint32_t(ret.size()));

	return numEnum;
}
