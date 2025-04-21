#include <iostream>
#include "EVMContractData.h"
#include "evm_abi/abi_parser.h"
#include "./evm_abi/abi_types.h"
#include "EVMExecutionEngine.h"
#include <ethash/keccak.h>

#ifdef ENABLE_EVM

namespace xtl 
{

    ContractDelegate::ContractDelegate(ContractCompileData* compile_data, ContractDeployData* deploy_data) : m_compile_data(compile_data), m_deploy_data(deploy_data)
    {
        m_name = m_compile_data->name.c_str();
		m_fullname = rt::SS("evm.") + m_compile_data->name.c_str();
        m_hash = m_compile_data->intermediateHash;
    }
    rvm::ConstString ContractDelegate::GetName() const
    {
		return rvm::ConstString{ m_name.GetString(), uint32_t(m_name.GetLength()) };
    }
	rvm::ConstString ContractDelegate::GetFullName() const
	{
		return rvm::ConstString{ m_fullname.GetString(), uint32_t(m_fullname.GetLength()) };
	}

    rvm::ContractFlag ContractDelegate::GetFlag() const
    {
        return rvm::ContractFlag();
    }

    const rvm::HashValue* ContractDelegate::GetModuleID() const
    {
		static_assert(sizeof(rvm::ContractModuleID) == sizeof(decltype(m_hash)));
		return &m_hash;
    }

	uint32_t ContractDelegate::GetInterfaceImplementedCount() const
	{
		return 0;
	}

    const rvm::Interface* ContractDelegate::GetInterfaceImplemented(uint32_t idx) const
    {
        return nullptr;
    }

    rvm::OpCode ContractDelegate::GetInterfaceImplementedOpCode(uint32_t idx, rvm::OpCode code) const
    {
        return rvm::OpCodeInvalid;
    }

    uint32_t ContractDelegate::GetScopeCount() const
    {
        return 1;
    }

    rvm::Scope ContractDelegate::GetScope(uint32_t idx) const
    {
        return rvm::Scope::ScatteredMapOnGlobal;
    }

    rvm::ScopeFlag ContractDelegate::GetScopeFlag(uint32_t idx) const
    {
        return rvm::ScopeFlag();
    }

    rvm::ConstString ContractDelegate::GetScopeName(uint32_t idx) const
    {
        static const char str[] = "global";
        rt::String_Ref tmp = str;
        return *(rvm::ConstString*)&tmp;
    }

    bool ContractDelegate::GetStateSignature(rvm::Scope scope, rvm::StringStream* signature_out) const
    {
        // TODO
        return true;
    }

    const rvm::Interface* ContractDelegate::GetInterface(uint32_t idx) const
    {
        // TODO;
        return nullptr;
    }

    rvm::InterfaceSlot ContractDelegate::GetInterfaceSlot(uint32_t idx) const
    {
        return rvm::InterfaceSlot(idx);
    }

    uint32_t ContractDelegate::GetEnumCount() const
    {
        return 0;
    }

    rvm::ConstString ContractDelegate::GetEnumName(uint32_t idx) const
    {
        return rvm::ConstString{ nullptr, 0 };
    }

    bool ContractDelegate::GetEnumSignature(uint32_t idx, rvm::StringStream* signature_out) const
    {
        return false;
    }

    uint32_t ContractDelegate::GetStructCount() const
    {
        return 0;
    }

    rvm::ConstString ContractDelegate::GetStructName(uint32_t idx) const
    {
        return rvm::ConstString{ nullptr, 0 };
    }

    bool ContractDelegate::GetStructSignature(uint32_t idx, rvm::StringStream* signature_out) const
    {
        return false;
    }

    uint32_t ContractDelegate::GetFunctionCount() const
    {
        return (uint32_t)m_compile_data->functions.size() + 1;
    }

    rvm::ConstString ContractDelegate::GetFunctionName(uint32_t idx) const
    {
        if (idx >= uint32_t(m_compile_data->functions.size()))
            return rvm::ConstString();
        return rvm::ConstString({ m_compile_data->functions[idx].name.c_str(), (uint32_t)m_compile_data->functions[idx].name.length() });
    }

    rvm::FunctionFlag ContractDelegate::GetFunctionFlag(uint32_t idx) const
    {
        return rvm::FunctionFlag();
    }

    rvm::Scope ContractDelegate::GetFunctionScope(uint32_t idx) const
    {
        return rvm::Scope::Global;
    }

    bool ContractDelegate::GetFunctionSignature(uint32_t idx, rvm::StringStream* signature_out) const
    {
		if (idx >= uint32_t(m_compile_data->functions.size()))
			return false;
		std::string tmp;
		for (std::pair<std::string, std::string> p : m_compile_data->functions[idx].parameters)
		{
			tmp += p.first + " " + p.second + " ";
		}
		if(tmp.size() > 0)
			signature_out->Append(tmp.c_str(), (uint32_t)tmp.length() - 1); //remove the last space

		return true;
    }

    rvm::OpCode ContractDelegate::GetFunctionOpCode(uint32_t idx) const
    {
        if (idx > 0)
        {
            return rvm::OpCode(1);
        }
        return rvm::OpCode(0);
    }

    void ContractDelegate::GetSystemFunctionOpCodes(rvm::SystemFunctionOpCodes* out) const
    {
        out->GlobalDeploy = rvm::OpCode(0);
    }

    uint32_t ContractDelegate::GetInterfaceCount() const
    {
        return 0;
    }

    CompiledModules::CompiledModules(const char* dapp_name): m_dAppName(dapp_name)
    {
    }

    const ContractCompileData* CompiledModules::GetCompiledData(uint32_t contractIdx) const
    {
        return contractIdx >= m_contracts.size() ? nullptr : &m_contracts[contractIdx];
    }

    void CompiledModules::AddContract(ContractCompileData compile_data, rt::String bytecode)
    {
        m_contracts.push_back(std::move(compile_data));
        m_bytecode.push_back(std::move(bytecode));
		m_delegates.emplace_back(&m_contracts.back(), nullptr);
    }
    void CompiledModules::LinkContract()
	{
		m_linked = true;
	}
    rt::String_Ref CompiledModules::GetBytecode(uint32_t idx)
    {
        if (idx >= m_bytecode.size()) {
            return {};
        }
        return rt::String_Ref(m_bytecode[idx]);
    }
    rvm::EngineId CompiledModules::GetEngineId() const
    {
        return rvm::EngineId::SOLIDITY_EVM;
    }
    rvm::ConstString CompiledModules::GetDAppName() const
    {
        return *(rvm::ConstString*)&m_dAppName;
    }
    uint32_t CompiledModules::GetCount() const
    {
        return uint32_t(m_contracts.size());
    }
    const rvm::Contract* CompiledModules::GetContract(uint32_t idx) const
    {
        return idx < m_delegates.size() ? &m_delegates[idx] : nullptr;
    }
    rvm::ConstString CompiledModules::GetExternalDependencies() const
    {
        return rvm::ConstString{ nullptr, 0 };
    }
    bool CompiledModules::IsLinked() const
    {
        return m_linked;
    }
    void CompiledModules::Release()
    {
        delete this;
    }

	int ContractDatabaseEntry::EncodeJsonFunctionArguments(std::string_view args_json, std::vector<uint8_t>& out) const
	{
		nlohmann::json json = nlohmann::json::parse(args_json);
		if(json.find("__sol__function__name__") == json.end())
			return 1;
		std::string function_name = json["__sol__function__name__"];
		nlohmann::json args = json["args"];

		// find matched overloaded functions
		const ContractFunction* matched_func = nullptr;
		for(const auto& func : compileData.functions)
		{
			if(func.name != function_name || func.parameters.size() != args.size())
				continue;
			bool bFind = true;
			for(const auto& param : func.parameters)
			{
				std::string_view param_name = param.second;
				if(args.find(param_name) == args.end())
				{
					bFind = false;
					break;
				}
			}
            if (bFind) {
				matched_func = &func;
                break;
            }
		}
		if(!matched_func)
			return 2;
		
		std::vector<std::pair<std::string, std::string>> type_value_pairs;
		for(const auto& param : matched_func->parameters)
			type_value_pairs.push_back(std::make_pair(param.first, args[param.second].dump()));

        evmc::bytes ret;
		if(0 != function_arguments_abi_encode(type_value_pairs, ret))
			return 3;
			
        rt::String sig;
        os::Base16Decode(matched_func->signatureHash, sig);
        out.resize(sig.GetLength() + ret.size());

        std::copy(ret.begin(), ret.end(), std::copy(sig.Begin(), sig.Begin() + sig.GetLength(), out.begin()));

		return 0;
	}

    int ContractDatabaseEntry::DecodeEventArguments(evmc::bytes32 event_sig, evmc::bytes_view bytes, std::string& out) const
    {
		const ContractEvent* matched_event = nullptr;
		for(const auto& event : compileData.events)
		{
			if(event.signatureHash == event_sig)
				matched_event = &event;
		}
		if(!matched_event)
			return 1;
		if(0 != abi_decode(matched_event->parameters, bytes, out))
			return 2;
        return 0;
    }


	int ContractDatabaseEntry::ShardStateJsonify(bool b_global, const rvm::ChainStates* p_chain_state, nlohmann::json& out) const
	{
		rvm::ContractScopeId csid = rvm::CONTRACT_SET_SCOPE(deployData.contractId, b_global ? xtl::CrystalityHost::GlobalStorageScope : xtl::CrystalityHost::ShardStorageScope);
		uint16_t scope = (uint16_t)(b_global ? rvm::Scope::Global : rvm::Scope::Shard);
		for(const auto& storage_var : compileData.storage_variables)
		{
			if(storage_var.scope == scope)
			{
				evmc::bytes bytes_data(storage_var.number_of_bytes, 0);
				uint32_t number_of_bytes = storage_var.number_of_bytes;
				if(storage_var.offset)
				{
					evmc::bytes32 storage_key(storage_var.slot_id);
					rvm::ScopeKey skey{ storage_key.bytes, sizeof(evmc::bytes32) };
					rvm::ConstStateData state_data = p_chain_state->GetState(csid, &skey);
					if(state_data.DataSize)
						std::memcpy(bytes_data.data(), state_data.DataPtr + storage_var.offset, number_of_bytes);
				}
				else 
				{
					uint16_t slot_id = storage_var.slot_id;
					while(number_of_bytes)
					{
						evmc::bytes32 storage_key(slot_id++);
						rvm::ScopeKey skey{ storage_key.bytes, sizeof(evmc::bytes32) };
						rvm::ConstStateData state_data = p_chain_state->GetState(csid, &skey);
						if(number_of_bytes >= 32)
						{
							if(state_data.DataSize)
								std::memcpy(bytes_data.data() + storage_var.number_of_bytes - number_of_bytes, state_data.DataPtr, sizeof(evmc::bytes32));
							number_of_bytes -= sizeof(evmc::bytes32);
						}
						else
						{
							if(state_data.DataSize)
								std::memcpy(bytes_data.data() + storage_var.number_of_bytes - number_of_bytes, state_data.DataPtr, number_of_bytes);
							number_of_bytes = 0;
						}
					}
				}
				if(storage_var.members.empty())
				{
					xtl::TypeParser type_parser(storage_var.type);
					out[storage_var.name] = (type_parser.type == xtl::Type::Undefined || type_parser.is_dynamic_array) ? "" : xtl::create_type(storage_var.type, bytes_data)->GetDecodedDataString();
				}
				else
				{
					for(const auto& member : storage_var.members)
					{
						xtl::TypeParser type_parser(member.type);
						evmc::bytes_view bv(bytes_data.data() + member.slot_id * sizeof(evmc::bytes32), member.number_of_bytes);
                        if (type_parser.type == xtl::Type::String || type_parser.type == xtl::Type::Bytes)
                        {
                            evmc::bytes str_bytes(2 * sizeof(evmc::bytes32), 0);
                            evmc::bytes32 str_len((uint32_t)bv[31]);
                            std::memcpy(str_bytes.data(), str_len.bytes, sizeof(evmc::bytes32));
                            std::memcpy(str_bytes.data() + sizeof(evmc::bytes32), bv.data(), (uint32_t)bv[31]);
                            out[storage_var.name][member.name] = xtl::create_type(member.type, str_bytes)->GetDecodedDataString();
                        }
                        else
                        {
						    out[storage_var.name][member.name] = (type_parser.type == xtl::Type::Undefined || type_parser.is_dynamic_array) ? "" : xtl::create_type(member.type, bv)->GetDecodedDataString();
                        }
					}
				}
			}
		}
        return 0;
    }

    int ContractDatabaseEntry::AddressStateJsonify(const rvm::Address& addr, const rvm::ChainStates* p_chain_state, nlohmann::json& out) const
    {
		rvm::ContractScopeId csid = rvm::CONTRACT_SET_SCOPE(deployData.contractId, xtl::CrystalityHost::ShardStorageScope);
		for(const auto& storage_var : compileData.storage_variables)
		{
			if(storage_var.scope == (uint16_t)rvm::Scope::Address)
			{
				uint32_t number_of_bytes = storage_var.number_of_bytes;
				uint16_t slot_id = storage_var.slot_id;
				evmc::bytes bytes_key;
				bytes_key.resize(sizeof(evmc::bytes32) * 2, 0);
				std::memcpy(bytes_key.data() + sizeof(evmc::bytes32) - sizeof(evmc::address), &addr, sizeof(evmc::address));
				evmc::bytes32 slot_key(storage_var.slot_id);
				std::memcpy(bytes_key.data() + sizeof(evmc::bytes32), slot_key.bytes, sizeof(evmc::bytes32));

				ethash_hash256 hash = ethash_keccak256(bytes_key.data(), bytes_key.size());
				rvm::ScopeKey skey{ hash.bytes, sizeof(ethash_hash256) };
				rvm::ConstStateData state_data = p_chain_state->GetState(csid, &skey);
				evmc::bytes bytes_data(storage_var.number_of_bytes, 0);
                if(state_data.DataSize)
				    std::memcpy(bytes_data.data(), state_data.DataPtr, number_of_bytes);

				xtl::TypeParser type_parser(storage_var.type);
				out[storage_var.name] = (type_parser.type == xtl::Type::Undefined || type_parser.is_dynamic_array) ? "" : xtl::create_type(storage_var.type, bytes_data)->GetDecodedDataString();
			}
		}
        return 0;
    }
}
#endif