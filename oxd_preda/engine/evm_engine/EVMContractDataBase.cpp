#include "EVMContractDataBase.h"
#include "EVMExecutionEngine.h"
#include "../../../SFC/core/rt/json.h"
#include "../../../oxd_libsec/oxd_libsec.h"
#include "../../native/types/typetraits.h"

namespace preda_evm {
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


		if (!json.LoadValueAs("deploy_id", outEntry.deployId))
			return false;

		{
			rt::String jsonStr(json.GetValue("inter_hash", bExist));
			if (!bExist) return false;
			::rvm::_details::_JsonParse(outEntry.compileData.intermediateHash, jsonStr);
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
		rt::String res;
		::rvm::_details::_Jsonify(entry.compileData.intermediateHash, res);

		rt::Json json;
		json.Object() << (
			J(dapp) = entry.compileData.dapp,
			J(name) = entry.compileData.name,
			J(deploy_id) = (uint64_t)entry.deployId,
			J(address) = evmc::hex(entry.address),
			J(id) = (uint64_t)entry.deployData.contractId,
			J(inter_hash) = res.SubStr(1, res.GetLength() - 2)
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
					m_contracts.try_emplace(entry.deployId, std::move(entry));
				}
			}
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

	bool ContractDatabase::Compile(const rvm::ChainState* chain_state, const rvm::ConstString* dapp_name, uint32_t contract_count, const rvm::ConstData* deploy_data_array, rvm::CompilationFlag flag, rvm::CompiledContracts** compiled_output, rvm::DataBuffer* dependency, rvm::LogMessageOutput* log_msg_output)
	{
		EnterCSBlock(m_barrier);
		
		AutoRelease<CompiledContracts> compiled_contracts(new CompiledContracts(dapp_name->StrPtr));

		for (size_t i = 0; i < contract_count; i++)
		{
			ContractCompileData compile_data;
			compile_data.dapp = std::string(dapp_name->StrPtr, dapp_name->Length);
			const rvm::ConstData& contract_data = deploy_data_array[i];
			rt::String_Ref json_str((const char*)contract_data.DataPtr, contract_data.DataSize);
			rt::JsonObject compile_json(json_str);
			bool exist = true;

			rt::String_Ref entry_file = compile_json.GetValue("entryFile", exist, true);
			if (!exist)
			{
				return false;
			}
			rt::String_Ref entry_contract = compile_json.GetValue("entryContract", exist, true);
			if (!exist)
			{
				return false;
			}
			compile_data.name = std::string(entry_contract.Begin(), entry_contract.GetLength());
			rt::String_Ref sources = compile_json.GetValueRaw("sources", exist, true);
			if (!exist)
			{
				return false;
			}

			// https://docs.soliditylang.org/en/v0.8.17/using-the-compiler.html#input-description
			rt::Json sol_json;
			{
				sol_json.Object() << (
					J(language) = "Solidity",
					J(sources) = rt::_JVal(sources),
					J(settings) = (
						J(optimizer) = (J(enabled) = true),
						J(outputSelection) = (
							rt::_JTag(entry_file) = (
								rt::_JTag(entry_contract) = JA("metadata", "evm.bytecode")
								)
							)
						)
					);
			}

			std::string sol_json_str(sol_json.GetInternalString().Begin(), sol_json.GetInternalString().Begin() + sol_json.GetInternalString().GetLength());

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

			//struct SolidityInternalStr {
			//	char* str;
			//	~SolidityInternalStr() {
			//		if (str) {
			//			solidity_free(str);
			//		}
			//	}
			//	SolidityInternalStr(char* str) : str(str) {}
			//};
			//SolidityInternalStr resultRAII = solidity_compile(sol_json_str.c_str(), nullptr, nullptr);
			rt::String_Ref result_str(result.c_str());

			// https://docs.soliditylang.org/en/v0.8.17/using-the-compiler.html#output-description
			rt::JsonObject result_json = result_str;

			rt::JsonObject contracts = result_json.GetValue("contracts", exist, true);
			if (!exist) {
				return false;
			}
			rt::JsonObject contract_file = contracts.GetValue(entry_file, exist, true);
			if (!exist) {
				return false;
			}
			rt::JsonObject contract = contract_file.GetValue(entry_contract, exist, true);
			if (!exist) {
				return false;
			}
			rt::String_Ref object = contract.GetValue("evm.bytecode.object", exist, false);
			if (!exist) {
				return false;
			}
			rt::String object_binary;
			if (!os::Base16Decode(object, object_binary)) {
				return false;
			}

			rt::String calldata_binary;

			rt::String_Ref calldata = compile_json.GetValue("calldata", exist);
			if (exist)
			{
				if (!os::Base16Decode(calldata, calldata_binary))
				{
					return false;
				}
			}

			oxd::SecuritySuite::Hash(object_binary.Begin(), (uint32_t)object_binary.GetLength(), &compile_data.intermediateHash);
			compiled_contracts.GetPtr()->AddContract(std::move(compile_data), std::move(object_binary), std::move(calldata_binary));
		}

		if (compiled_output) {
			*compiled_output = compiled_contracts.Release();
		}

		return true;
	}

	bool ContractDatabase::Link(rvm::CompiledContracts* compiled, rvm::LogMessageOutput* log_msg_output)
	{
		EnterCSBlock(m_barrier);

		CompiledContracts* compiled_contracts = (CompiledContracts*)compiled;

		uint32_t count = compiled_contracts->GetCount();
		bool success = true;
		std::vector<ContractLinkData> linkdata(count);

		// link is no-op in evm

		compiled_contracts->AttachLinkData(std::move(linkdata));

		return true;
	}

	bool ContractDatabase::ValidateDependency(const rvm::ChainState* chain_state, rvm::CompiledContracts* compiled, const rvm::ConstData* dependency)
	{
		return true;
	}

	rvm::ExecuteUnit* ContractDatabase::CreateExecuteUnit()
	{
		return new EVMExecutionEngine(this);
	}

	bool ContractDatabase::StateJsonify(rvm::BuildNum build_num, rvm::ContractScopeId contract, const rvm::ConstData* pState, rvm::StringStream* json_out, const rvm::ChainState* ps) const
	{
		return true;
	}

	bool ContractDatabase::StateJsonParse(rvm::BuildNum build_num, rvm::ContractScopeId contract, const rvm::ConstString* json, rvm::DataBuffer* state_out, const rvm::ChainState* ps, rvm::LogMessageOutput* og) const
	{
		return true;
	}

	bool ContractDatabase::ArgumentsJsonify(rvm::BuildNum build_num, rvm::ContractScopeId contract, rvm::OpCode opCode, const rvm::ConstData* args_serialized, rvm::StringStream* json_out, const rvm::ChainState* ps) const
	{
		return true;
	}

	bool ContractDatabase::ArgumentsJsonParse(rvm::BuildNum build_num, rvm::ContractScopeId contract, rvm::OpCode opCode, const rvm::ConstString* json, rvm::DataBuffer* args_out, const rvm::ChainState* ps, rvm::LogMessageOutput* log) const
	{
		uint8_t* data = args_out->SetSize(json->Length);
		std::copy(json->StrPtr, json->StrPtr + json->Length, data);
		return true;
	}

	const rvm::Contract* ContractDatabase::GetContract(const rvm::ContractDID* deploy_id) const
	{
		return GetContract(_details::RvmCDIDToEVMCDID(deploy_id));
	}

	const rvm::Contract* ContractDatabase::GetContract(ContractDID deploy_id) const
	{
		EnterCSBlock(m_barrier);

		const ContractDatabaseEntry* pContractEntry = FindContractEntry(deploy_id);

		if (!pContractEntry)
			return nullptr;

		return const_cast<ContractDatabaseEntry*>(pContractEntry)->GetDelegate();
	}

	uint32_t ContractDatabase::GetContractEnumSignatures(rvm::BuildNum build_num, rvm::ContractId contract, rvm::StringStream* signature_out, const rvm::ChainState* ps) const
	{
		return 0;
	}

	bool ContractDatabase::GetContractFunctionArgumentsSignature(rvm::BuildNum build_num, rvm::ContractScopeId contract, rvm::OpCode opcode, rvm::StringStream* signature_out, const rvm::ChainState* ps) const
	{
		return false;
	}

	bool ContractDatabase::GetContractStateSignature(rvm::BuildNum build_num, rvm::ContractScopeId contract, rvm::StringStream* signature_out, const rvm::ChainState* ps) const
	{
		return false;
	}

	const ContractDatabaseEntry* ContractDatabase::FindContractEntry(ContractDID deployId) const
	{
		EnterCSBlock(m_barrier);

		auto itor = m_contracts.find(deployId);
		if (itor == m_contracts.end())
			return nullptr;

		return &itor->second;
	}

	bool ContractDatabase::Deploy(const rvm::ChainState* chain_state, const rvm::ContractId* contractIds, const evmc::address* addresses, rvm::CompiledContracts* linked, rvm::ContractDID* deployment_identifiers_out, rvm::InterfaceDID** interface_deployment_ids_out, rvm::LogMessageOutput* log_msg_output)
	{
		EnterCSBlock(m_barrier);

		bool bSuccess = true;

		CompiledContracts* pCompiledContracts = (CompiledContracts*)linked;

		assert(pCompiledContracts->IsLinked());

		uint32_t contracts_count = pCompiledContracts->GetCount();
		std::vector<ContractDatabaseEntry> entries(contracts_count);

		for (uint32_t contractIdx = 0; contractIdx < contracts_count; contractIdx++)
		{
			entries[contractIdx].compileData = *pCompiledContracts->GetCompiledData(contractIdx);

			rvm::ContractId contractId = contractIds[contractIdx];

			// fill contract id in deploy data
			entries[contractIdx].deployData.contractId = contractId;
			entries[contractIdx].address = addresses[contractIdx];
		}


		if (bSuccess)
		{
			for (uint32_t idx = 0; idx < contracts_count; idx++)
			{
				entries[idx].deployId = os::AtomicIncrement(&m_nextDeployId) - 1;		// AtomicIncrement returns the incremented value, need to decrement
				_details::EVMCDIDToRvmCDID(entries[idx].deployId, deployment_identifiers_out);
				ASSERT(m_contracts.find(entries[idx].deployId) == m_contracts.end());
				m_contracts.try_emplace(entries[idx].deployId, entries[idx]);

				rt::String json = ConvertEntryToJSON(m_contracts[entries[idx].deployId]);
				if (!m_contractDB.Set(entries[idx].deployId, json.GetString()))
				{
					bSuccess = false;
				}
			}
		}

		return bSuccess;
	}

	ContractDatabase::~ContractDatabase()
	{
	}
}


