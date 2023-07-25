#include <iostream>
#include "EVMContractData.h"
#ifdef ENABLE_EVM

namespace preda_evm {
    void ContractCompileData::AddFunction(const ContractFunction& funcInfo)
    {
        m_functions[funcInfo.name].push_back(funcInfo);
    }

    bool ContractCompileData::ComposeInputData(const rt::JsonObject& args_json, uint64_t& value, std::string& data) const
    {
        std::map<std::string, std::pair<std::string,std::string>> inputArguments; //name => (type, value)
        uint32_t argSize = 0;
        rt::JsonKeyValuePair p;
        std::string funcName;
        while (args_json.GetNextKeyValuePair(p))
        {
            rt::String key = p.GetKey();
            rt::String val = p.GetValue();
            if (key == "SolFunctionName"){
                funcName = std::string(val.Begin(), val.GetLength());
            }
            else if(key == "value"){
                val.ToNumber<uint64_t>(value);
            }
            else{
                inputArguments[std::string(key.Begin(), key.GetLength())] = {std::string(), std::string(val.Begin(), val.GetLength())};
                argSize++;
            }
        }
        //see if "funcName" exist
        auto iter = m_functions.find(funcName);
        if(iter == m_functions.end())
        {
            return false;
        }
        bool matched = false;
        std::string funcHash;
        ContractFunction target;
        //for all overloaded "funcName"
        for(uint32_t i = 0; i < iter->second.size() && !matched; i++)
        {
            //if the parameter size does not match argument size
            if(iter->second[i].parameters.size() != argSize)
            {
                continue;
            }
            else if (iter->second[i].parameters.size() == 0 && argSize == 0) //function takes no parameter
            {
                funcHash = iter->second[i].signatureHash;
                matched = true;
                break;
            }
            //for each parameter, check if parameter name exist in the input json
            for(uint32_t j = 0; j < iter->second[i].parameters.size(); j++)
            {
                auto paramIter = inputArguments.find(iter->second[i].parameters[j].second);
                if(paramIter == inputArguments.end())
                {
                    matched = false;
                    break;
                }
                //fill in the parameter type
                paramIter->second.first = iter->second[i].parameters[j].first;
                funcHash = iter->second[i].signatureHash;
                matched = true;
                target = iter->second[i];
            }
        }
        //sort parameters in order, align with function arguments
        std::vector<std::pair<std::string, std::string>> in;
        if (matched)
        {
            data = funcHash;
            for (uint32_t i = 0; i < target.parameters.size(); i++)
            {
                in.push_back(inputArguments.find(target.parameters[i].second)->second);
            }
            EVMUtil::TypeEncoder::encodeParameters(in, data);
        }

        return matched;
    }

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
        return (uint32_t)m_compile_data->m_functions.size() + 1;
    }

    rvm::ConstString ContractDelegate::GetFunctionName(uint32_t idx) const
    {
        if (idx == 0)
        {
            static rt::String_Ref str("mint");
            return *(rvm::ConstString*)&str;
        }
        auto iter = m_compile_data->m_functions.begin();
        std::advance(iter, idx - 1); //idx 0 is reserved for mint, iterating the function map starting from idx == 1
        if(iter != m_compile_data->m_functions.end())
        {
            return rvm::ConstString({ iter->first.c_str(), (uint32_t)iter->first.length() });
        }
        return rvm::ConstString();
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
        return false;
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

    void CompiledModules::AddContract(ContractCompileData compile_data, rt::String bytecode, rt::String init_data)
    {
        m_contracts.push_back(std::move(compile_data));
        m_bytecode.push_back(std::move(bytecode));
        m_initdata.push_back(std::move(init_data));
        m_delegates.emplace_back(&m_contracts.back(), nullptr);
    }

    const rt::String_Ref CompiledModules::GetBytecode(uint32_t idx)
    {
        if (idx >= m_bytecode.size()) {
            return {};
        }
        return rt::String_Ref(m_bytecode[idx]);k
    }

    const rt::String_Ref CompiledModules::GetInitData(uint32_t idx)
    {
        if (idx >= m_bytecode.size()) {
            return {};
        }
        return rt::String_Ref(m_initdata[idx]);
    }

    void CompiledModules::AttachLinkData(std::vector<ContractLinkData> linkdata)
    {
        m_linkdata.swap(linkdata);
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
        if (idx >= m_delegates.size()) {
            return nullptr;
        }
        return &m_delegates[idx];
    }
    rvm::ConstString CompiledModules::GetExternalDependencies() const
    {
        return rvm::ConstString{ nullptr, 0 };
    }
    bool CompiledModules::IsLinked() const
    {
        return m_linkdata.size() == m_contracts.size();
    }
    void CompiledModules::Release()
    {
        delete this;
    }

}
#endif