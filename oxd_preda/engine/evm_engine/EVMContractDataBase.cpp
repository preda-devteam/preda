#include "EVMContractDataBase.h"
#include "EVMExecutionEngine.h"
#include "../../../SFC/core/rt/json.h"
#include "../../../oxd_libsec/oxd_libsec.h"
#include "../../native/types/typetraits.h"
#include "../../transpiler/transpiler.h"
#include "../../3rdParty/nlohmann/json.hpp"
#include "./evm_abi/abi_types.h"
#include <functional>
#include <ethash/keccak.h>

#ifdef ENABLE_EVM
typedef transpiler::ICrystalityTranspiler* (*FNCreateCrystalityTranspilerInstance)(const char *options);
FNCreateCrystalityTranspilerInstance CreateCrystalityTranspilerInstance = nullptr;
namespace xtl {
	template <typename T>
	struct AutoRelease
	{
		T* m_p;
		AutoRelease(T* p)
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

		T* Release()
		{
			T* ret = m_p;
			m_p = nullptr;
			return ret;
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

	bool ReadEntryFromJson(const rt::JsonObject& json, ContractDatabaseEntry& outEntry)
	{
		bool bExist = true;
		outEntry.compileData.dapp = rt::String(json.GetValue("dapp", bExist));
		if (!bExist) return false;

		outEntry.compileData.name = rt::String(json.GetValue("name", bExist));
		if (!bExist) return false;


		if (!json.LoadValueAs("deploy_sn", outEntry.deploy_sn))
			return false;

		{
			rt::String jsonStr(json.GetValue("inter_hash", bExist));
			if (!bExist) return false;
			::rvm::RvmTypeJsonParse(outEntry.compileData.intermediateHash, jsonStr);
		}

		{
			rt::String_Ref address = json.GetValue("address", bExist);
			if (!bExist) return false;
			std::optional<evmc::address> addr = evmc::from_hex<evmc::address>(std::string_view{ address.Begin(), address.GetLength() });
			if (!addr)
				return false;
			outEntry.address = *addr;
		}

		{
			auto data = json.GetValue("id", bExist);
			if (!bExist) return false;
			data.ToNumber(*(uint64_t*)&outEntry.deployData.contractId);
		}

		// TODO fill entry fields
		return true;
	}

	rt::String ConvertEntryToJSON(const ContractDatabaseEntry& entry)
	{
		rt::Json res;
		::rvm::RvmTypeJsonify(entry.compileData.intermediateHash, res);

		rt::Json json;
		json.Object() << (
			J(dapp) = entry.compileData.dapp,
			J(name) = entry.compileData.name,
			J(deploy_sn) = (uint64_t)entry.deploy_sn,
			J(address) = evmc::hex(entry.address),
			J(id) = (uint64_t)entry.deployData.contractId,
			J(inter_hash) = res.GetInternalString().SubStr(1, res.GetLength() - 2)
			);

		return std::move(json.GetInternalString());
	}

	bool ContractDatabase::Initialize(const char* module_path, const char* db_path, rvm::BlockchainRuntime* runtime_api, rvm::ConstString* initErrorMsg)
	{
		EnterCSBlock(m_barrier);

		m_modulePath = module_path;
		if (m_modulePath[m_modulePath.size() - 1] != '\\' && m_modulePath[m_modulePath.size() - 1] != '/')
			m_modulePath += '/';

		{
	#if	defined(__linux__) || defined(__linux)
			HANDLE handle_antlr = os::LoadDynamicLibrary((m_modulePath + "libantlr4-runtime.so.4.12.0").c_str());
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

			CreateCrystalityTranspilerInstance = (FNCreateCrystalityTranspilerInstance)os::GetDynamicLibrarySymbol(handle, "CreateCrystalityTranspilerInstance");
			if (CreateCrystalityTranspilerInstance == nullptr)
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

			transpiler::ICrystalityTranspiler *pTranspiler = CreateCrystalityTranspilerInstance(nullptr);
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

			pTranspiler->Release();
		}

		m_pRuntimeAPI = runtime_api;
		
		return true;
	}

	void ContractDatabase::Release()
	{
		m_contracts.clear();
		m_contractDB.Close();
		delete this;
	}

	rvm::ConstString ContractDatabase::GetVersion() const
	{
		static const char str[] = "0.0.1";
		rt::String_Ref tmp(str);
		return *(rvm::ConstString*)&tmp;
	}

	rvm::ConstString ContractDatabase::GetName() const
	{
		static const char str[] = "PREDA EVM Host";
		rt::String_Ref tmp(str);
		return *(rvm::ConstString*)&tmp;
	}

	rvm::ConstString ContractDatabase::GetVendorInfo() const
	{
		static const char str[] = "PREDA DevTeam";
		rt::String_Ref tmp(str);
		return *(rvm::ConstString*)&tmp;
	}

	rvm::ConstString ContractDatabase::GetContractName(const rvm::ConstData* source_code)
	{
		return {};
	}

	bool ContractDatabase::Compile(const rvm::ConstString* dapp_name, uint32_t contract_count, const rvm::ConstData*deploy_data_array, rvm::CompilationFlag flag, rvm::CompiledModules** compiled_output, rvm::LogMessageOutput* log_msg_output)
	{
		EnterCSBlock(m_barrier);
		
		AutoRelease<CompiledModules> compiled_contracts(new CompiledModules(dapp_name->StrPtr));
		// 1. create transpilers
		std::vector<AutoRelease<transpiler::ICrystalityTranspiler>> transpilers(contract_count);
		{
			bool bTranspilerReady = true;
			if (CreateCrystalityTranspilerInstance == nullptr)
				bTranspilerReady = false;
			else
			{
				std::string options;
				for (uint32_t i = 0; i < contract_count; i++)
				{
					transpiler::ICrystalityTranspiler* pTranspiler = CreateCrystalityTranspilerInstance(options.c_str());
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

		// 2. transpile each contract
		bool bSuccess = true;
		for (size_t i = 0; i < contract_count; i++)
		{
			ContractCompileData compile_data;
			compile_data.dapp = std::string(dapp_name->StrPtr, dapp_name->Length);

			const rvm::ConstData& contract_data = deploy_data_array[i];
			transpiler::ICrystalityTranspiler* pCurrentTranspiler = transpilers[i].GetPtr();
			pCurrentTranspiler->BuildParseTree((const char*)contract_data.DataPtr);
			if(!pCurrentTranspiler->Transpile())
			{
				uint32_t numCompileErrors = pCurrentTranspiler->GetNumTranspileErrors();
				for (uint32_t i = 0; i < numCompileErrors; i++)
				{
					uint32_t line, pos;
					pCurrentTranspiler->GetTranspileErrorPos(i, line, pos);
					log_msg_output->Log(rvm::LogMessageType::Error, 0, i, line, pos, (rvm::ConstString*)pCurrentTranspiler->GetTranspileErrorMsg(i));
				}
				bSuccess = false;
				continue;
			}
			std::string transpiled_code(pCurrentTranspiler->GetOutput());
			for(auto i = 0; i < pCurrentTranspiler->GetNumStorageVariables(); ++i)
			{
				ContractVariable var{pCurrentTranspiler->GetStorageVariableType(i), pCurrentTranspiler->GetStorageVariableName(i), (uint16_t)rvm::ScopeInvalid, 0, 0, 0};
				std::string scope = pCurrentTranspiler->GetStorageVariableScope(i);
				if(scope == "global")
					var.scope = (uint16_t)rvm::Scope::Global;
				else if(scope == "local")
					var.scope = (uint16_t)rvm::Scope::Shard;
				else if(scope == "address")
					var.scope = (uint16_t)rvm::Scope::Address;
				else if(scope == "uint32")
					var.scope = (uint16_t)rvm::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySized::UInt32, 0);
				compile_data.storage_variables.push_back(var);
			}

			// https://docs.soliditylang.org/en/v0.8.26/using-the-compiler.html#compiler-input-and-output-json-description
			nlohmann::json solidity_standard_json;
			{
				solidity_standard_json["language"] = "Solidity";
				solidity_standard_json["sources"]["*"]["content"] = transpiled_code;
				auto& settings = solidity_standard_json["settings"];
				settings["optimizer"]["enabled"] = true;
				settings["outputSelection"]["*"]["*"] = {"evm.bytecode.object", "abi", "evm.methodIdentifiers", "storageLayout"};
			}

			std::string sol_json_str = solidity_standard_json.dump(4);

			std::string result;
			{
				std::string intermediateFilePathFileName = "sol.json";
				{
					os::File intermediateFile;
					if (!intermediateFile.Open((m_dbPath + intermediateFilePathFileName).c_str(), os::File::Normal_Write, true))
					{
						std::string errorStr = "Cannot write " + m_dbPath + intermediateFilePathFileName;
						rvm::ConstString msg{ errorStr.c_str(), uint32_t(errorStr.size()) };
						log_msg_output->Log(rvm::LogMessageType::Error, 0, 0, 0, 0, (rvm::ConstString*)&msg);
						return false;
					}
					intermediateFile.Write(sol_json_str.c_str());
					if (intermediateFile.ErrorOccured())
					{
						std::string errorStr = "Cannot write " + m_dbPath + intermediateFilePathFileName;
						rvm::ConstString msg{ errorStr.c_str(), uint32_t(errorStr.size()) };
						log_msg_output->Log(rvm::LogMessageType::Error, 0, 0, 0, 0, (rvm::ConstString*)&msg);
						return false;
					}
					intermediateFile.Close();
				}

#if	defined(__linux__) || defined(__linux) || defined(__APPLE__)
				{
#ifdef __APPLE__
					std::string cmdLine = m_modulePath + "../solc/solc-macos --standard-json \"" + m_dbPath + intermediateFilePathFileName + "\"";
#else
					std::string cmdLine = m_modulePath + "../solc/solc-static-linux --standard-json \"" + m_dbPath + intermediateFilePathFileName + "\"";
#endif
					FILE* pipe = popen(cmdLine.c_str(), "r");
					if (pipe == nullptr)
					{
						std::string errorStr = "Failed to execute " + cmdLine;
						rvm::ConstString msg{ errorStr.c_str(), uint32_t(errorStr.size()) };
						log_msg_output->Log(rvm::LogMessageType::Error, 0, 0, 0, 0, (rvm::ConstString*)&msg);
						return false;
					}
					else
					{
						char buffer[128];
						while (fgets(buffer, sizeof(buffer), pipe) != NULL)
							result += buffer;
						int res = pclose(pipe);
						if (res != 0)
						{
							rvm::ConstString msg{ result.c_str(), uint32_t(result.size()) };
							log_msg_output->Log(rvm::LogMessageType::Error, 0, 0, 0, 0, (rvm::ConstString*)&msg);
							return false;
						}
					}
				}
#elif defined(_WIN32)
				{
					os::LaunchProcess processLauncher;
					std::string cmdLine = m_modulePath + "../solc/solc-windows --standard-json \"" + m_dbPath + intermediateFilePathFileName + "\"";
					if (!processLauncher.Launch(cmdLine.c_str(), os::LaunchProcess::FLAG_SAVE_OUTPUT))
					{
						rvm::ConstString msg{ "solc launch error", uint32_t(strlen("solc launch error")) };
						log_msg_output->Log(rvm::LogMessageType::Error, 0, 0, 0, 0, (rvm::ConstString*)&msg);
						return false;
					}
					processLauncher.WaitForEnding();
					if (processLauncher.GetExitCode() != 0)
					{
						rvm::ConstString msg{ processLauncher.GetOutput(), uint32_t(processLauncher.GetOutputLen()) };
						log_msg_output->Log(rvm::LogMessageType::Error, 0, 0, 0, 0, (rvm::ConstString*)&msg);
						return false;
					}
					result = processLauncher.GetOutput();
				}
#else
				ASSERT(0);
#endif
			}

			nlohmann::json solc_output_json = nlohmann::json::parse(result);

			// https://docs.soliditylang.org/en/v0.8.17/using-the-compiler.html#output-description
			const nlohmann::json& contract_info = solc_output_json["contracts"]["*"].begin().value();
			compile_data.name = solc_output_json["contracts"]["*"].begin().key();

			const std::string& object = contract_info["evm"]["bytecode"]["object"];
			rt::String object_binary;
			if (!os::Base16Decode(object, object_binary))
				return false;
			oxd::SecuritySuite::Hash(object_binary.Begin(), (uint32_t)object_binary.GetLength(), &compile_data.intermediateHash);

			const nlohmann::json& abi_array = contract_info["abi"];
			const nlohmann::json& method_identifiers = contract_info["evm"]["methodIdentifiers"];
			// fetch abi info
			for (const auto& abi : abi_array)
			{
				if (abi["type"] != "function" && abi["type"] != "event")
					continue;

				std::function<std::string(const nlohmann::json&)> parse_components_sig;
				parse_components_sig = [&parse_components_sig](const nlohmann::json& components) -> std::string
				{
					std::string ret("(");
					for(const auto& component : components)
					{
						if(component.find("components") != component.end())
							ret += parse_components_sig(component);
						else
							ret += component["type"];
						ret += ",";
					}
					if(ret.back() == ',') 
						ret.back() = ')';
					else 
						ret += ")";
					return ret;
				};

				std::string func_name = abi["name"];
				std::string func_sig = func_name + "(";
				const nlohmann::json& params = abi["inputs"];
				std::vector<std::pair<std::string, std::string>> param_type_name_list;
				for (const auto& param : params)
				{
					std::string type_sig, type_name_list;
					if(param.find("components") != param.end())
					{
						type_sig = parse_components_sig(param["components"]);
						type_name_list = nlohmann::to_string(param["components"]);
						std::string type = param["type"];
						if(type.length() >= 2 && type.substr(type.length() - 2) == "[]")
						{
							type_sig += "[]";
							type_name_list += "[]";
						}
					}
					else
					{
						type_sig = param["type"];
						type_name_list = param["type"];
					}

					param_type_name_list.emplace_back(std::make_pair(type_name_list, param["name"]));
					func_sig += type_sig + ',';
				}
				if (func_sig.back() == ',')
					func_sig.back() = ')';
				else
					func_sig.push_back(')');
			
				if(abi["type"] == "function")
				{
					auto iter = method_identifiers.find(func_sig);
					if (iter == method_identifiers.end())
						return false;
					std::string func_hash = *iter;
					ContractFunction func;
					func.name = func_name;
					func.signatureHash = func_hash;
					func.parameters = std::move(param_type_name_list);
					compile_data.functions.push_back(func);
				}
				else if(abi["type"] == "event")
				{
					ContractEvent event;
					event.name = func_name;
					event.parameters = std::move(param_type_name_list);
					ethash_hash256 hash = ethash_keccak256((const uint8_t*)func_sig.data(), func_sig.size());
					std::copy(std::begin(hash.bytes), std::end(hash.bytes), std::begin(event.signatureHash.bytes));
					compile_data.events.push_back(event);
				}
			}
			// parse layout and offset
			const nlohmann::json& storage_layout_array = contract_info["storageLayout"]["storage"];
			const nlohmann::json& storage_layout_type_map = contract_info["storageLayout"]["types"];
			for (const auto& storage_layout : storage_layout_array)
			{
				std::string label = storage_layout["label"];
				for (auto& storage_var : compile_data.storage_variables)
				{
					if (label == storage_var.name)
					{
						storage_var.offset = storage_layout["offset"];
						storage_var.slot_id = std::stoul(std::string(storage_layout["slot"]));
						const nlohmann::json& type_info = storage_layout_type_map[storage_layout["type"]];
						storage_var.number_of_bytes = std::stoul(std::string(type_info["numberOfBytes"]));
						if (type_info.count("members"))
						{
							for (const auto& member : type_info["members"])
							{
								ContractVariable member_var;
								const nlohmann::json& type_info = storage_layout_type_map[member["type"]];
								member_var.type = type_info["label"];
								member_var.name = member["label"];
								member_var.offset = member["offset"];
								member_var.slot_id = std::stoul(std::string(member["slot"]));
								member_var.number_of_bytes = std::stoul(std::string(type_info["numberOfBytes"]));
								storage_var.members.emplace_back(std::move(member_var));
							}
						}
						break;
					}
				}
			}
			compiled_contracts.GetPtr()->AddContract(std::move(compile_data), std::move(object_binary));
		}

		if (compiled_output) {
			 *compiled_output = compiled_contracts.Release();
		}

		return true;
	}

	bool ContractDatabase::Recompile(const rvm::ConstString* dapp_name, const rvm::ConstData* dependency_data, uint32_t contract_count,  const rvm::ConstData* deploy_data_array, rvm::CompilationFlag flag, rvm::CompiledModules** compiled_output, rvm::LogMessageOutput* log_msg_output) 
	{
		return true;
	}

	bool ContractDatabase::Link(rvm::CompiledModules* compiled, rvm::LogMessageOutput* log_msg_output)
	{
		((CompiledModules*)compiled)->LinkContract();
		return true;
	}
	void ContractDatabase::CancelCurrentBuildingTask()
	{
		
	}

	rvm::ExecutionUnit* ContractDatabase::CreateExecuteUnit()
	{
		return new EVMExecutionEngine(this);
	}

	bool ContractDatabase::StateJsonify(rvm::ContractInvokeId ciid, const rvm::ConstData* contract_state, rvm::StringStream* json_out) const
	{
		rvm::ContractId cid = rvm::CONTRACT_UNSET_SCOPE_BUILD(ciid);
		auto p_engtry = FindContractEntry(cid);
		if (!p_engtry)
			return false;
			
		nlohmann::json json_states;
		json_states["Contract"] = p_engtry->compileData.name;
		json_states["CVID"] = (uint64_t)rvm::CONTRACT_UNSET_SCOPE(ciid);
		rvm::ChainStates* p_chain_state = *(rvm::ChainStates**)contract_state->DataPtr;

		nlohmann::json state_json;
		switch (rvm::CONTRACT_SCOPE(ciid))
		{
			case rvm::Scope::Global:
				p_engtry->ShardStateJsonify(true, p_chain_state, state_json);
				break;
			case rvm::Scope::Shard:
				p_engtry->ShardStateJsonify(false, p_chain_state, state_json);
				break;
			case rvm::Scope::Address:
			{
				rvm::Address* p_addr = (rvm::Address*)(contract_state->DataPtr + sizeof(rvm::ChainStates*));
				p_engtry->AddressStateJsonify(*p_addr, p_chain_state, state_json);
			}
				break;
			default:
				break;
		}

		json_states["State"] = state_json;
		std::string out = json_states.dump();
		json_out->Append(out.c_str(), out.size());

		return true;
	}

	bool ContractDatabase::StateJsonParse(rvm::ContractInvokeId contract, const rvm::ConstString* json, rvm::DataBuffer* state_out, rvm::LogMessageOutput* error_out) const
	{
		return true;
	}
	
	bool ContractDatabase::ScatteredStateKeyJsonify(rvm::ContractInvokeId contract, const rvm::ConstData* key_data, rvm::StringStream* json_out) const
	{
		return true;
	}

	bool ContractDatabase::ArgumentsJsonify(rvm::ContractInvokeId contract, rvm::OpCode opCode, const rvm::ConstData* args_serialized, rvm::StringStream* json_out) const
	{
		return true;
	}

	bool ContractDatabase::ArgumentsJsonParse(rvm::ContractInvokeId contract, rvm::OpCode opCode, const rvm::ConstString* json, rvm::DataBuffer* args_out, rvm::LogMessageOutput* error_out) const
	{
		auto entry = FindContractEntry(rvm::CONTRACT_UNSET_SCOPE_BUILD(contract));
		std::vector<uint8_t> ret;
		int ret_code = entry->EncodeJsonFunctionArguments(std::string_view(json->StrPtr, json->Length), ret);
		if (0 == ret_code)
		{
			auto pWrite = args_out->SetSize((uint32_t)ret.size());
			memcpy(pWrite, &ret[0], ret.size());
		}
		return true;
	}

	rvm::ContractScopeId ContractDatabase::GetScopeDefinition(rvm::ContractScopeId cid) const
	{
		// TODO: implement
		return cid;
	}
	
	const rvm::Contract* ContractDatabase::GetContract(const rvm::ContractModuleID* deploy_id) const
	{
		return GetContract(_details::RvmCDIDToEVMCID(deploy_id));
	}

	const rvm::Contract* ContractDatabase::GetContract(rvm::ContractId cid) const
	{
		EnterCSBlock(m_barrier);

		const ContractDatabaseEntry* pContractEntry = FindContractEntry(cid);

		if (!pContractEntry)
			return nullptr;

		return const_cast<ContractDatabaseEntry*>(pContractEntry)->GetDelegate();
	}

	uint32_t ContractDatabase::GetContractEnumSignatures(rvm::ContractVersionId contract, rvm::StringStream* signature_out) const
	{
		return 0;
	}

	bool ContractDatabase::GetContractFunctionArgumentsSignature(rvm::ContractInvokeId contract, rvm::OpCode opcode, rvm::StringStream* signature_out) const
	{
		return false;
	}

	bool ContractDatabase::GetContractStateSignature(rvm::ContractInvokeId contract, rvm::StringStream* signature_out) const
	{
		return false;
	}

	const ContractDatabaseEntry* ContractDatabase::FindContractEntry(rvm::ContractId cid) const
	{
		EnterCSBlock(m_barrier);
		
		auto itor = m_contracts.find(cid);
		if (itor == m_contracts.end())
			return nullptr;

		return &itor->second;
	}

	bool ContractDatabase::Deploy(const rvm::GlobalStates* chain_state, rvm::CompiledModules* linked, const evmc::address* deploy_address, const rvm::ContractId* cids)
	{
		EnterCSBlock(m_barrier);

		CompiledModules* pCompiledContracts = (CompiledModules*)linked;
		uint32_t contracts_count = pCompiledContracts->GetCount();
		std::vector<ContractDatabaseEntry> entries(contracts_count);

		for (uint32_t contractIdx = 0; contractIdx < contracts_count; contractIdx++)
		{
			const ContractCompileData* pCompiledData = pCompiledContracts->GetCompiledData(contractIdx);
			entries[contractIdx].compileData = *pCompiledData;
			entries[contractIdx].deployData.contractId = cids[contractIdx];
			entries[contractIdx].address = deploy_address[contractIdx];
		}

		for (uint32_t idx = 0; idx < contracts_count; idx++)
		{
			entries[idx].deploy_sn = (uint32_t)(os::AtomicIncrement(&m_nextDeployId) - 1);		// AtomicIncrement returns the incremented value, need to decrement
			rvm::ContractId cid = entries[idx].deployData.contractId;
			ASSERT(m_contracts.find(cid) == m_contracts.end());
			m_contracts.try_emplace(cid, entries[idx]);

			//rt::String json = ConvertEntryToJSON(m_contracts[cid]);
			//if (!m_contractDB.Set(cid, json.GetString()))
			//	return false;
		}
		return true;
	}

	ContractDatabase::~ContractDatabase()
	{
	}
}


#endif