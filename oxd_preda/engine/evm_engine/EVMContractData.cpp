#include "EVMContractData.h"

namespace preda_evm {
    ContractDelegate::ContractDelegate(ContractCompileData* compile_data, ContractDeployData* deploy_data): m_compile_data(compile_data), m_deploy_data(deploy_data)
    {
        m_name = m_compile_data->name.c_str();
        m_hash = m_compile_data->intermediateHash;
    }
    rvm::ConstString ContractDelegate::GetName() const
    {
        return *(rvm::ConstString*)&m_name;
    }

    rvm::ContractFlag ContractDelegate::GetFlag() const
    {
        return rvm::ContractFlag();
    }

    const rvm::HashValue* ContractDelegate::GetIntermediateRepresentationHash() const
    {
        return &m_hash;
    }

    uint32_t ContractDelegate::GetInterfaceImplemented(rvm::InterfaceId* pIID_out, uint32_t OutBufSize) const
    {
        return 0;
    }

    rvm::OpCode ContractDelegate::GetInterfaceImplementedOpCode(rvm::InterfaceId i, rvm::OpCode code) const
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

    rvm::ScopeDefinitionFlag ContractDelegate::GetScopeFlag(uint32_t idx) const
    {
        return rvm::ScopeDefinitionFlag();
    }

    rvm::ConstString ContractDelegate::GetScopeName(uint32_t idx) const
    {
        static const char str[] = "global";
        rt::String_Ref tmp = str;
        return *(rvm::ConstString*)&tmp;
    }

    rvm::ContractScopeId ContractDelegate::GetScopeDefinition(uint32_t idx) const
    {
        return rvm::_details::CONTRACT_SET_SCOPE(m_deploy_data ? m_deploy_data->contractId : rvm::ContractId(-1), GetScope(idx));
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
        return 2; // only 2 functions: call, mint
    }

    rvm::ConstString ContractDelegate::GetFunctionName(uint32_t idx) const
    {
        if (idx < 2) {
            static const char* str[] = { "call", "mint" };
            rt::String_Ref tmp = str[idx];
            return *(rvm::ConstString*)&tmp;
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
        return rvm::OpCode(idx);
    }

    void ContractDelegate::GetSystemFunctionOpCodes(rvm::SystemFunctionOpCodes* out) const
    {
    }

    uint32_t ContractDelegate::GetInterfaceCount() const
    {
        return 0;
    }

    CompiledContracts::CompiledContracts(const char* dapp_name): m_dAppName(dapp_name)
    {
    }

    const ContractCompileData* CompiledContracts::GetCompiledData(uint32_t contractIdx) const
    {
        return contractIdx >= m_contracts.size() ? nullptr : &m_contracts[contractIdx];
    }

    void CompiledContracts::AddContract(ContractCompileData compile_data, rt::String bytecode, rt::String init_data)
    {
        m_contracts.push_back(std::move(compile_data));
        m_bytecode.push_back(std::move(bytecode));
        m_initdata.push_back(std::move(init_data));
        m_delegates.emplace_back(&m_contracts.back(), nullptr);
    }

    const rt::String_Ref CompiledContracts::GetBytecode(uint32_t idx)
    {
        if (idx >= m_bytecode.size()) {
            return {};
        }
        return rt::String_Ref(m_bytecode[idx]);
    }

    const rt::String_Ref CompiledContracts::GetInitData(uint32_t idx)
    {
        if (idx >= m_bytecode.size()) {
            return {};
        }
        return rt::String_Ref(m_initdata[idx]);
    }

    void CompiledContracts::AttachLinkData(std::vector<ContractLinkData> linkdata)
    {
        m_linkdata.swap(linkdata);
    }

    rvm::EngineId CompiledContracts::GetEngineId() const
    {
        return rvm::EngineId::SOLIDITY_EVM;
    }
    rvm::ConstString CompiledContracts::GetDAppName() const
    {
        return *(rvm::ConstString*)&m_dAppName;
    }
    uint32_t CompiledContracts::GetCount() const
    {
        return uint32_t(m_contracts.size());
    }
    const rvm::Contract* CompiledContracts::GetContract(uint32_t idx) const
    {
        if (idx >= m_delegates.size()) {
            return nullptr;
        }
        return &m_delegates[idx];
    }
    rvm::ConstString CompiledContracts::GetExternalDependencies() const
    {
        return rvm::ConstString{ nullptr, 0 };
    }
    bool CompiledContracts::IsLinked() const
    {
        return m_linkdata.size() == m_contracts.size();
    }
    void CompiledContracts::Release()
    {
        delete this;
    }

}