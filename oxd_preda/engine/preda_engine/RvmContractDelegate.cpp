#include <assert.h>
#include "RvmContractDelegate.h"
#include <sstream>
#include <array>

uint32_t PredaFunctionFlagsToRvmContractFlags(uint32_t flags)
{
	uint32_t ret = 0;

	// convert flags from preda definition to vm interface definition

	// invokability
	if (flags & uint32_t(transpiler::FunctionFlags::CallableFromTransaction))
		ret |= uint32_t(rvm::FunctionFlag::InvokeByNormalTransaction);
	if (flags & uint32_t(transpiler::FunctionFlags::CallableFromRelay))
		ret |= uint32_t(rvm::FunctionFlag::InvokeByRelayTransaction);
	if (flags & uint32_t(transpiler::FunctionFlags::CallableFromSystem))
		ret |= uint32_t(rvm::FunctionFlag::InvokeBySystem);

	// const-ness
	if (flags & uint32_t(transpiler::FunctionFlags::IsConst))
		ret |= uint32_t(rvm::FunctionFlag::StateImmutable);

	// relays
	if (flags & uint32_t(transpiler::FunctionFlags::HasRelayScopeStatement))
		ret |= uint32_t(rvm::FunctionFlag::EmitRelayInAddressScope);
	if (flags & uint32_t(transpiler::FunctionFlags::HasRelayShardsStatement))
		ret |= uint32_t(rvm::FunctionFlag::EmitRelayInShardScope);
	if (flags & uint32_t(transpiler::FunctionFlags::HasRelayGlobalStatement))
		ret |= uint32_t(rvm::FunctionFlag::EmitRelayInGlobalScope);

	if (flags & uint32_t(transpiler::FunctionFlags::GlobalStateDependency))
		ret |= uint32_t(rvm::FunctionFlag::GlobalStateDependency);

	return ret;
}

RvmContractDelegate::RvmContractDelegate(ContractCompileData* pContractCompiledData, ContractDeployData *pDeployData)
	: m_pContractCompiledData(pContractCompiledData), m_pDeployData(pDeployData)
{
	// name
	m_name = pContractCompiledData->name.c_str();

	// contract flags
	m_flag = 0;
	if (pContractCompiledData->globalDeployFunctionIdx >= 0)
	{
		m_flag |= uint32_t(rvm::ContractFlag::HasGlobalDeploy);
		m_onDeployOpCode = rvm::OpCode(pContractCompiledData->globalDeployFunctionIdx);
	}
	if (pContractCompiledData->shardScaleOutFunctionIdx >= 0)
	{
		m_flag |= uint32_t(rvm::ContractFlag::HasShardScaleOut);
		m_onScaleOutOpCode = rvm::OpCode(pContractCompiledData->shardScaleOutFunctionIdx);
	}

	// hash
	m_hash = pContractCompiledData->intermediateHash;

	// scopes
	// first check which scopes have state variables
	std::array<std::underlying_type_t<rvm::ScopeDefinitionFlag>, int(transpiler::ScopeType::Num)> scopeFlags;
	scopeFlags.fill(0);

	{
		auto NotEmptyStateSignature = [](const std::string& str)
		{
			std::istringstream t(str);
			std::string a, b;
			t >> a >> b;
			return a == "struct" && b != "0";
		};

		for (int i = 0; i < int(transpiler::ScopeType::Num); i++)
			if (NotEmptyStateSignature(pContractCompiledData->scopeStateVarMeta[i].signature))
				scopeFlags[uint32_t(transpiler::ScopeType(i))] |= uint32_t(rvm::ScopeDefinitionFlag::HasState);
	}

	// and which scopes have function
	for (size_t i = 0; i < pContractCompiledData->functions.size(); i++)
	{
		m_functions.push_back(Function());

		// function op code
		m_functions.back().opCode = rvm::OpCode(i);

		// function name
		m_functions.back().name = rt::String(pContractCompiledData->functions[i].name.c_str());

		// function flags
		m_functions.back().flags = rvm::FunctionFlag(PredaFunctionFlagsToRvmContractFlags(pContractCompiledData->functions[i].flags));
		uint32_t scopeType = pContractCompiledData->functions[i].flags & uint32_t(transpiler::FunctionFlags::ScopeTypeMask);
		rvm::Scope rvmScope = _details::PredaScopeToRvmScope(transpiler::ScopeType(scopeType));
		m_functions.back().scope = rvmScope;
		scopeFlags[scopeType] |= uint32_t(rvm::ScopeDefinitionFlag::HasFunction);
	}

	// only count scopes that have state or function, do no report the others
	static constexpr const char scopeTypeNames[int(transpiler::ScopeType::Num)][20] = { "none", "global", "shard", "address", "uint16", "uint32", "uint64", "uint256", "uint512" };
	for (int i = 0; i < int(transpiler::ScopeType::Num); i++)
		if (scopeFlags[i] != 0)
		{
			rvm::Scope rvmScope = _details::PredaScopeToRvmScope(transpiler::ScopeType(i));
			m_scopes.push_back({ rvmScope, scopeFlags[i], scopeTypeNames[i], rvm::_details::CONTRACT_SET_SCOPE(m_pDeployData ? m_pDeployData->contractId : rvm::ContractId(-1), rvmScope) });
		}
}

rvm::ConstString RvmContractDelegate::GetName() const
{
	return *(rvm::ConstString*)&m_name;
}

rvm::ContractFlag RvmContractDelegate::GetFlag() const
{
	return rvm::ContractFlag(m_flag);
}

const rvm::HashValue* RvmContractDelegate::GetIntermediateRepresentationHash() const
{
	return (rvm::HashValue*)&m_hash;
}

// Function Definitions
uint32_t RvmContractDelegate::GetFunctionCount() const
{
	return uint32_t(m_functions.size());
}
rvm::ConstString RvmContractDelegate::GetFunctionName(uint32_t idx) const
{
	if (idx >= uint32_t(m_functions.size()))
	{
		rt::String_Ref tmp;
		return *(rvm::ConstString*)&tmp;
	}
	return *(rvm::ConstString*)&m_functions[idx].name;
}
rvm::FunctionFlag RvmContractDelegate::GetFunctionFlag(uint32_t idx) const
{
	if (idx >= uint32_t(m_functions.size()))
		return rvm::FunctionFlag(0);
	return m_functions[idx].flags;
}
rvm::OpCode RvmContractDelegate::GetFunctionOpCode(uint32_t idx) const
{
	if (idx >= uint32_t(m_functions.size()))
		return rvm::OpCode(0);
	return m_functions[idx].opCode;
}
rvm::Scope RvmContractDelegate::GetFunctionScope(uint32_t idx) const
{
	if (idx >= uint32_t(m_functions.size()))
		return rvm::Scope(0);
	return m_functions[idx].scope;
}
bool RvmContractDelegate::GetFunctionSignature(uint32_t idx, rvm::StringStream* signature_out) const
{
	if (idx >= uint32_t(m_functions.size()))
		return false;
	std::string tmp;
	for (std::pair<std::string, std::string> p : m_pContractCompiledData->functions[idx].parameters)
	{
		tmp += p.first + " " + p.second + " ";
	}
	if(tmp.size() > 0)
		signature_out->Append(tmp.c_str(), (uint32_t)tmp.length() - 1); //remove the last space

	return true;
}


void RvmContractDelegate::GetSystemFunctionOpCodes(rvm::SystemFunctionOpCodes* out) const
{
	constexpr rvm::OpCode invalidOpCode = rvm::OpCode(std::numeric_limits<std::underlying_type_t<rvm::OpCode>>::max());
	out->ShardScaleOut = (m_flag & uint32_t(rvm::ContractFlag::HasShardScaleOut)) != 0 ? m_onScaleOutOpCode : invalidOpCode;
	out->ShardDeploy = (m_flag & uint32_t(rvm::ContractFlag::HasShardDeploy)) != 0 ? m_shardDeployOpCode : invalidOpCode;
	out->GlobalDeploy = (m_flag & uint32_t(rvm::ContractFlag::HasGlobalDeploy)) != 0 ? m_onDeployOpCode : invalidOpCode;
}
