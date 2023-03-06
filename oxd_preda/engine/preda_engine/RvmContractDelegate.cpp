#include <assert.h>
#include "RvmContractDelegate.h"
#include <sstream>

uint32_t PredaFunctionFlagsToRvmContractFlags(uint32_t flags)
{
	uint32_t ret = 0;

	// convert flags from preda definition to vm interface definition

	// block dependency are no longer used, TODO: remove corresponding PREDA flags as well
	//if (flags & uint32_t(transpiler::PredaFunctionFlags::BlockDependencyEntropy))
	//	ret |= uint32_t(rvm::FunctionFlag::BlockDependencySecureEntropy);
	//else if (flags & uint32_t(transpiler::PredaFunctionFlags::BlockDependencyPayload))
	//	ret |= uint32_t(rvm::FunctionFlag::BlockDependencyBlock);
	//else if (flags & uint32_t(transpiler::PredaFunctionFlags::BlockDependencyPosition))
	//	ret |= uint32_t(rvm::FunctionFlag::BlockDependencyPosition);
	//else
	//	ret |= uint32_t(rvm::FunctionFlag::BlockDependencyNone);

	// invokability
	if (flags & uint32_t(transpiler::PredaFunctionFlags::CallableFromTransaction))
		ret |= uint32_t(rvm::FunctionFlag::InvokeByNormalTransaction);
	if (flags & uint32_t(transpiler::PredaFunctionFlags::CallableFromRelay))
		ret |= uint32_t(rvm::FunctionFlag::InvokeByRelayTransaction);
	if (flags & uint32_t(transpiler::PredaFunctionFlags::CallableFromSystem))
		ret |= uint32_t(rvm::FunctionFlag::InvokeBySystem);

	// transaction dependency not longer used, TODO: remove corresponding PREDA flags as well
	//if (flags & uint32_t(transpiler::PredaFunctionFlags::TransactionDependency))
	//	ret |= uint32_t(rvm::FunctionFlag::TransactionDependency);

	// const-ness
	if (flags & uint32_t(transpiler::PredaFunctionFlags::IsConst))
		ret |= uint32_t(rvm::FunctionFlag::StateImmutable);

	// relays
	if (flags & uint32_t(transpiler::PredaFunctionFlags::HasRelayAddressStatement))
		ret |= uint32_t(rvm::FunctionFlag::EmitRelayInAddressScope);
	if (flags & uint32_t(transpiler::PredaFunctionFlags::HasRelayShardsStatement))
		ret |= uint32_t(rvm::FunctionFlag::EmitRelayInShardScope);
	if (flags & uint32_t(transpiler::PredaFunctionFlags::HasRelayGlobalStatement))
		ret |= uint32_t(rvm::FunctionFlag::EmitRelayInGlobalScope);

	if (flags & uint32_t(transpiler::PredaFunctionFlags::GlobalStateDependency))
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
		m_globalDeployOpCode = rvm::OpCode(pContractCompiledData->globalDeployFunctionIdx);
	}
	if (pContractCompiledData->shardScaleOutFunctionIdx >= 0)
	{
		m_flag |= uint32_t(rvm::ContractFlag::HasShardScaleOut);
		m_shardScaleOutOpCode = rvm::OpCode(pContractCompiledData->shardScaleOutFunctionIdx);
	}

	// scopes
	m_scopes.resize(3);
	m_scopes[0] = { rvm::Scope::Global, 0, "global", rvm::_details::CONTRACT_SET_SCOPE(m_pDeployData ? m_pDeployData->contractId : rvm::ContractId(-1), rvm::Scope::Global) };
	m_scopes[1] = { rvm::Scope::Shard, 0, "shard", rvm::_details::CONTRACT_SET_SCOPE(m_pDeployData ? m_pDeployData->contractId : rvm::ContractId(-1), rvm::Scope::Shard) };
	m_scopes[2] = { rvm::Scope::Address, 0, "address", rvm::_details::CONTRACT_SET_SCOPE(m_pDeployData ? m_pDeployData->contractId : rvm::ContractId(-1), rvm::Scope::Address) };

	{
		auto NotEmptyStateSignature = [](const std::string& str)
		{
			std::istringstream t(str);
			std::string a, b;
			t >> a >> b;
			return a == "struct" && b != "0";
		};

		if (NotEmptyStateSignature(pContractCompiledData->globalStateVariableSignature))
			m_scopes[uint32_t(rvm::Scope::Global)].flags |= uint32_t(rvm::ScopeDefinitionFlag::HasState);
		if (NotEmptyStateSignature(pContractCompiledData->perShardStateVariableSignature))
			m_scopes[uint32_t(rvm::Scope::Shard)].flags |= uint32_t(rvm::ScopeDefinitionFlag::HasState);
		if (NotEmptyStateSignature(pContractCompiledData->perAddressStateVariableSignature))
			m_scopes[uint32_t(rvm::Scope::Address)].flags |= uint32_t(rvm::ScopeDefinitionFlag::HasState);
	}

	// hash
	m_hash = pContractCompiledData->intermediateHash;

	for (size_t i = 0; i < pContractCompiledData->functions.size(); i++)
	{
		m_functions.push_back(Function());

		// function op code
		m_functions.back().opCode = rvm::OpCode(i);

		// function name
		m_functions.back().name = rt::String(pContractCompiledData->functions[i].name.c_str());

		// function flags
		m_functions.back().flags = rvm::FunctionFlag(PredaFunctionFlagsToRvmContractFlags(pContractCompiledData->functions[i].flags));
		uint32_t sectionMask = pContractCompiledData->functions[i].flags & uint32_t(transpiler::PredaFunctionFlags::ContextClassMask);
		if (sectionMask == uint32_t(transpiler::PredaFunctionFlags::ContextClassGlobal))
		{
			m_functions.back().scope = rvm::Scope::Global;
			m_scopes[uint32_t(rvm::Scope::Global)].flags |= uint32_t(rvm::ScopeDefinitionFlag::HasFunction);
		}
		else if (sectionMask == uint32_t(transpiler::PredaFunctionFlags::ContextClassShard))
		{
			m_functions.back().scope = rvm::Scope::Shard;
			m_scopes[uint32_t(rvm::Scope::Shard)].flags |= uint32_t(rvm::ScopeDefinitionFlag::HasFunction);
		}
		else if (sectionMask == uint32_t(transpiler::PredaFunctionFlags::ContextClassAddress))
		{
			m_functions.back().scope = rvm::Scope::Address;
			m_scopes[uint32_t(rvm::Scope::Address)].flags |= uint32_t(rvm::ScopeDefinitionFlag::HasFunction);
		}
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
	// TODO: implement
	return false;
}


void RvmContractDelegate::GetSystemFunctionOpCodes(rvm::SystemFunctionOpCodes* out) const
{
	constexpr rvm::OpCode invalidOpCode = rvm::OpCode(std::numeric_limits<std::underlying_type_t<rvm::OpCode>>::max());
	out->ShardScaleOut = (m_flag & uint32_t(rvm::ContractFlag::HasShardScaleOut)) != 0 ? m_shardScaleOutOpCode : invalidOpCode;
	out->ShardDeploy = (m_flag & uint32_t(rvm::ContractFlag::HasShardDeploy)) != 0 ? m_shardDeployOpCode : invalidOpCode;
	out->GlobalDeploy = (m_flag & uint32_t(rvm::ContractFlag::HasGlobalDeploy)) != 0 ? m_globalDeployOpCode : invalidOpCode;
}
