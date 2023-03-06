#pragma once

#include "../../native/abi/vm_interfaces.h"
#include "../../transpiler/transpiler/PredaCommon.h"
#include "ContractData.h"


class RvmContractDelegate : public rvm::Contract
{
private:
	rt::String		m_name;
	uint32_t		m_flag;
	rvm::HashValue	m_hash;

	struct Function
	{
		rt::String name;
		rvm::OpCode opCode;
		rvm::FunctionFlag flags;
		rvm::Scope scope;
	};

	std::vector<Function> m_functions;

	rvm::OpCode m_shardScaleOutOpCode = rvm::OpCode(0);
	rvm::OpCode m_shardDeployOpCode = rvm::OpCode(0);
	rvm::OpCode m_globalDeployOpCode = rvm::OpCode(0);
	rvm::OpCode m_periodicOpCode = rvm::OpCode(0);
	rvm::OpCode m_addressPeriodicOpCode = rvm::OpCode(0);

	ContractCompileData* m_pContractCompiledData = nullptr;
	ContractDeployData* m_pDeployData = nullptr;

	struct ScopeDesc
	{
		rvm::Scope scope;
		std::underlying_type<rvm::ScopeDefinitionFlag>::type flags;
		std::string name;
		rvm::ContractScopeId originalScopeId;
	};
	std::vector<ScopeDesc> m_scopes;

public:
	RvmContractDelegate(ContractCompileData* pContractCompiledData, ContractDeployData* pDeployData);

	//virtual rvm::ConstString GetSuppliedAssets() const override;

	virtual rvm::ConstString		GetName() const override;
	virtual rvm::ContractFlag		GetFlag() const override;

	virtual const rvm::HashValue* GetIntermediateRepresentationHash() const override;

	virtual uint32_t				GetInterfaceImplemented(rvm::InterfaceId* pIID_out, uint32_t OutBufSize) const override
	{
		// TODO
		return 0;
	}
	virtual rvm::OpCode				GetInterfaceImplementedOpCode(rvm::InterfaceId i, rvm::OpCode code) const override
	{
		// TODO
		return rvm::OpCodeInvalid;
	}

	virtual uint32_t				GetScopeCount() const override
	{
		return uint32_t(m_scopes.size());
	}
	virtual rvm::Scope				GetScope(uint32_t idx) const override
	{
		return m_scopes[idx].scope;
		static const rvm::Scope builtInScopes[] = { rvm::Scope::Global, rvm::Scope::Shard, rvm::Scope::Address };
		return builtInScopes[idx];
	}
	virtual rvm::ConstString		GetScopeName(uint32_t idx) const override
	{
		return rvm::ConstString{ m_scopes[idx].name.c_str(), uint32_t(m_scopes[idx].name.size()) };
		static const char builtInScopeNames[][100] = { "global", "shard", "address" };
		return rvm::ConstString{ builtInScopeNames[idx], uint32_t(strlen(builtInScopeNames[idx])) };
	}
	virtual rvm::ScopeDefinitionFlag	GetScopeFlag(uint32_t idx) const override
	{
		return rvm::ScopeDefinitionFlag(m_scopes[idx].flags);
	}

	virtual rvm::ContractScopeId	GetScopeDefinition(uint32_t idx) const override
	{
		return m_scopes[idx].originalScopeId;
		// TODO use macro to replace -1
		return rvm::_details::CONTRACT_SET_SCOPE(m_pDeployData ? m_pDeployData->contractId : rvm::ContractId(-1), GetScope(idx));
	}
	virtual bool					GetStateSignature(rvm::Scope scope, rvm::StringStream* signature_out) const override
	{
		if (scope == rvm::Scope::Global)
			signature_out->Append(m_pContractCompiledData->globalStateVariableSignature.c_str(), uint32_t(m_pContractCompiledData->globalStateVariableSignature.length()));
		else if (scope == rvm::Scope::Shard)
			signature_out->Append(m_pContractCompiledData->perShardStateVariableSignature.c_str(), uint32_t(m_pContractCompiledData->perShardStateVariableSignature.length()));
		else if (scope == rvm::Scope::Address)
			signature_out->Append(m_pContractCompiledData->perAddressStateVariableSignature.c_str(), uint32_t(m_pContractCompiledData->perAddressStateVariableSignature.length()));
		else
			return false;

		return true;
	}

	virtual uint32_t				GetInterfaceCount() const override
	{
		// TODO:
		return 0;
	}
	virtual const rvm::Interface* GetInterface(uint32_t idx) const override
	{
		// TODO
		return nullptr;
	}
	virtual rvm::InterfaceSlot		GetInterfaceSlot(uint32_t idx) const override
	{
		return rvm::InterfaceSlot(idx);
	}

	virtual uint32_t				GetEnumCount() const override
	{
		return uint32_t(m_pContractCompiledData->enums.size());
	}
	virtual rvm::ConstString		GetEnumName(uint32_t idx) const override
	{
		if (idx >= uint32_t(m_pContractCompiledData->enums.size()))
			return rvm::ConstString{ nullptr, 0 };
		return rvm::ConstString{ m_pContractCompiledData->enums[idx].name.c_str(), uint32_t(m_pContractCompiledData->enums[idx].name.length()) };
	}
	virtual bool					GetEnumSignature(uint32_t idx, rvm::StringStream* signature_out) const override
	{
		if (idx >= uint32_t(m_pContractCompiledData->enums.size()))
			return false;

		std::string ret;
		const auto& entry = m_pContractCompiledData->enums[idx];
		uint32_t numEnumerator = uint32_t(entry.enumerators.size());
		for (uint32_t j = 0; j < numEnumerator; j++)
		{
			if (j > 0)
				ret += ',';
			ret += entry.enumerators[j];
		}
		signature_out->Append(ret.c_str(), uint32_t(ret.size()));

		return true;
	}

	virtual uint32_t				GetStructCount() const override
	{
		return uint32_t(m_pContractCompiledData->structs.size());
	}

	virtual rvm::ConstString				GetStructName(uint32_t idx) const override
	{
		if (idx >= uint32_t(m_pContractCompiledData->structs.size()))
			return rvm::ConstString{ nullptr, 0 };
		return rvm::ConstString{ m_pContractCompiledData->structs[idx].name.c_str(), uint32_t(m_pContractCompiledData->structs[idx].name.length()) };
	}

	virtual bool					GetStructSignature(uint32_t idx, rvm::StringStream* signature_out) const override
	{
		if (idx >= uint32_t(m_pContractCompiledData->structs.size()))
			return false;

		std::string ret;
		const auto& entry = m_pContractCompiledData->structs[idx];
		uint32_t numMembers = uint32_t(entry.members.size());
		ret += "struct " + std::to_string(numMembers) + " ";
		for (uint32_t j = 0; j < numMembers; j++)
		{
			ret += entry.members[j].first + " " + entry.members[j].second;
			if (j < numMembers - 1)
				ret += " ";
		}
		signature_out->Append(ret.c_str(), uint32_t(ret.size()));
		return true;
	}

	virtual uint32_t GetFunctionCount() const override;
	virtual rvm::ConstString GetFunctionName(uint32_t idx) const override;
	virtual rvm::FunctionFlag GetFunctionFlag(uint32_t idx) const override;
	virtual rvm::Scope GetFunctionScope(uint32_t idx) const override;
	virtual bool GetFunctionSignature(uint32_t idx, rvm::StringStream* signature_out) const override;
	virtual rvm::OpCode GetFunctionOpCode(uint32_t idx) const override;

	virtual void GetSystemFunctionOpCodes(rvm::SystemFunctionOpCodes* out) const override;
};
