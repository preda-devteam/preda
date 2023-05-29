#pragma once
#include "ContractData.h"
#include "../../transpiler/transpiler.h"

class CContractDatabase;
struct ContractDatabaseEntry;

class CContractSymbolDatabaseForTranspiler : public transpiler::IContractSymbolDatabase
{
	struct CContractSymbols : public transpiler::IContractSymbols
	{
		const ContractCompileData *m_pEntry;
		CContractSymbols(const ContractCompileData *pEntry)
			: m_pEntry(pEntry)
		{
		}
		virtual ~CContractSymbols() {}
		virtual const char* GetDAppName() const override
		{
			return m_pEntry->dapp.c_str();
		}
		virtual const char* GetContractName() const override
		{
			return m_pEntry->name.c_str();
		}
		virtual const char* GetContractComment() const override
		{
			return m_pEntry->contractDoxygenComment.c_str();
		}
		virtual const char* GetContractExportUniqueIdentifierString() const override
		{
			return m_pEntry->exportUniqueString.c_str();
		}

		virtual uint32_t GetNumImportedContracts() const override
		{
			return uint32_t(m_pEntry->importedContracts.size());
		}
		virtual const char* GetImportedContractFullName(uint32_t contractIdx) const override
		{
			if (contractIdx >= uint32_t(m_pEntry->importedContracts.size()))
				return nullptr;
			return m_pEntry->importedContracts[contractIdx].c_str();
		}

		// functions
		virtual uint32_t GetNumExportedFunctions() const override
		{
			return (uint32_t)m_pEntry->functions.size();
		}
		virtual const char* GetExportedFunctionName(uint32_t functionIdx) const override
		{
			if (functionIdx >= uint32_t(m_pEntry->functions.size()))
				return nullptr;
			return m_pEntry->functions[functionIdx].name.c_str();
		}
		virtual const char* GetExportedFunctionComment(uint32_t functionIdx) const override
		{
			if (functionIdx >= uint32_t(m_pEntry->functions.size()))
				return nullptr;
			return m_pEntry->functions[functionIdx].doxygenComment.c_str();

		}
		virtual uint32_t GetExportedFunctionFlag(uint32_t functionIdx) const override
		{
			if (functionIdx >= uint32_t(m_pEntry->functions.size()))
				return 0;
			return m_pEntry->functions[functionIdx].flags;
		}
		virtual const char* GetExportedFunctionReturnType(uint32_t functionIdx) const override
		{
			if (functionIdx >= uint32_t(m_pEntry->functions.size()))
				return nullptr;
			return m_pEntry->functions[functionIdx].returnType.c_str();
		}
		virtual const char* GetExportedFunctionParameterType(uint32_t functionIdx, uint32_t paramIdx) const override
		{
			if (functionIdx >= uint32_t(m_pEntry->functions.size()))
				return nullptr;
			if (paramIdx >= uint32_t(m_pEntry->functions[functionIdx].parameters.size()))
				return nullptr;
			return m_pEntry->functions[functionIdx].parameters[paramIdx].first.c_str();
		}
		virtual const char* GetExportedFunctionParameterName(uint32_t functionIdx, uint32_t paramIdx) const override
		{
			if (functionIdx >= uint32_t(m_pEntry->functions.size()))
				return nullptr;
			if (paramIdx >= uint32_t(m_pEntry->functions[functionIdx].parameters.size()))
				return nullptr;
			return m_pEntry->functions[functionIdx].parameters[paramIdx].second.c_str();
		}
		virtual uint32_t GetExportedFunctionNumParameters(uint32_t functionIdx) const override
		{
			if (functionIdx >= uint32_t(m_pEntry->functions.size()))
				return 0;
			return uint32_t(m_pEntry->functions[functionIdx].parameters.size());
		}

		virtual int32_t GetGlobalDeployFunctionExportIndex() const override
		{
			return m_pEntry->globalDeployFunctionIdx;
		}
		virtual int32_t GetShardScaleoutFunctionExportIndex() const override
		{
			return m_pEntry->shardScaleOutFunctionIdx;
		}

		// interfaces
		virtual uint32_t GetNumExportedInterfaces() const override
		{
			return uint32_t(m_pEntry->interfaces.size());
		}
		virtual const char* GetExportedInterfaceName(uint32_t interfaceIdx) const override
		{
			return m_pEntry->interfaces[interfaceIdx].name.c_str();
		}
		virtual uint32_t GetNumExportedInterfaceFunctions(uint32_t interfaceIdx) const override
		{
			return uint32_t(m_pEntry->interfaces[interfaceIdx].functions.size());
		}
		virtual const char* GetExportedInterfaceFunctionName(uint32_t interfaceIdx, uint32_t functionIdx) const override
		{
			return m_pEntry->interfaces[interfaceIdx].functions[functionIdx].name.c_str();
		}
		virtual const char* GetExportedInterfaceFunctionComment(uint32_t interfaceIdx, uint32_t functionIdx) const override
		{
			return m_pEntry->interfaces[interfaceIdx].functions[functionIdx].doxygenComment.c_str();
		}
		virtual uint32_t GetExportedInterfaceFunctionFlag(uint32_t interfaceIdx, uint32_t functionIdx) const override
		{
			return m_pEntry->interfaces[interfaceIdx].functions[functionIdx].flags;

		}
		virtual const char* GetExportedInterfaceFunctionReturnType(uint32_t interfaceIdx, uint32_t functionIdx) const override
		{
			return m_pEntry->interfaces[interfaceIdx].functions[functionIdx].returnType.c_str();
		}
		virtual const char* GetExportedInterfaceFunctionParameterType(uint32_t interfaceIdx, uint32_t functionIdx, uint32_t paramIdx) const override
		{
			return m_pEntry->interfaces[interfaceIdx].functions[functionIdx].parameters[paramIdx].first.c_str();
		}
		virtual const char* GetExportedInterfaceFunctionParameterName(uint32_t interfaceIdx, uint32_t functionIdx, uint32_t paramIdx) const override
		{
			return m_pEntry->interfaces[interfaceIdx].functions[functionIdx].parameters[paramIdx].second.c_str();
		}
		virtual uint32_t GetExportedInterfaceFunctionNumParameters(uint32_t interfaceIdx, uint32_t functionIdx) const override
		{
			return uint32_t(m_pEntry->interfaces[interfaceIdx].functions[functionIdx].parameters.size());
		}

		// implemented interfaces
		virtual uint32_t GetNumImplementedInterfaces() const override
		{
			return uint32_t(m_pEntry->implementedInterfaces.size());
		}
		virtual const char* GetImplementedInterfaceName(uint32_t interfaceIdx) const override
		{
			return m_pEntry->implementedInterfaces[interfaceIdx].name.c_str();
		}
		virtual uint32_t GetNumImplementedInterfaceFunctions(uint32_t interfaceIdx) const override
		{
			return uint32_t(m_pEntry->implementedInterfaces[interfaceIdx].functionIds.size());
		}
		virtual int32_t GetImplementedInterfaceFunctionExportIndex(uint32_t interfaceIdx, uint32_t functionIdx) const override
		{
			if (functionIdx >= uint32_t(m_pEntry->implementedInterfaces[interfaceIdx].functionIds.size()))
				return -1;
			return int32_t(m_pEntry->implementedInterfaces[interfaceIdx].functionIds[functionIdx]);
		}

		virtual const char* GetScopeStateVariableSignature(transpiler::ScopeType scope) const override
		{
			return m_pEntry->scopeStateVarMeta[int(scope)].signature.c_str();
		}
		virtual uint32_t GetNumScopeStateVariable(transpiler::ScopeType scope) const override
		{
			return (uint32_t)m_pEntry->scopeStateVarMeta[int(scope)].comment.size();
		}
		virtual const char* GetScopeStateVariableComment(transpiler::ScopeType scope, uint32_t varIdx) const override
		{
			return m_pEntry->scopeStateVarMeta[int(scope)].comment[varIdx].c_str();
		}
		virtual bool ScopeStateVariableHasAsset(transpiler::ScopeType scope) const override
		{
			return m_pEntry->scopeStateVarMeta[int(scope)].hasAsset;
		}
		virtual bool ScopeStateVariableHasBlob(transpiler::ScopeType scope) const override
		{
			return m_pEntry->scopeStateVarMeta[int(scope)].hasBlob;
		}

		virtual uint32_t GetNumEnumTypes() const override
		{
			return (uint32_t)m_pEntry->enums.size();
		}
		virtual const char* GetEnumTypeName(uint32_t enumTypeIdx) const override
		{
			if (enumTypeIdx >= (uint32_t)m_pEntry->enums.size())
				return nullptr;
			return m_pEntry->enums[enumTypeIdx].name.c_str();
		}
		virtual const char* GetEnumDoxygenComment(uint32_t enumTypeIdx) const override
		{
			if (enumTypeIdx >= (uint32_t)m_pEntry->enums.size())
				return nullptr;
			return m_pEntry->enums[enumTypeIdx].doxygenComment.c_str();
		}
		virtual uint32_t GetNumEnumerators(uint32_t enumTypeIdx) const override
		{
			if (enumTypeIdx >= (uint32_t)m_pEntry->enums.size())
				return 0; 
			return uint32_t(m_pEntry->enums[enumTypeIdx].enumerators.size());
		}
		virtual const char* GetEnumerator(uint32_t enumTypeIdx, uint32_t enumeratorIdx) const override
		{
			if (enumTypeIdx >= (uint32_t)m_pEntry->enums.size())
				return nullptr;
			if (enumeratorIdx >= uint32_t(m_pEntry->enums[enumTypeIdx].enumerators.size()))
				return nullptr;
			return m_pEntry->enums[enumTypeIdx].enumerators[enumeratorIdx].c_str();
		}
		virtual uint32_t GetNumStructTypes() const override
		{
			return uint32_t(m_pEntry->structs.size());
		}
		virtual const char* GetStructTypeName(uint32_t structTypeIdx) const override
		{
			if (structTypeIdx >= uint32_t(m_pEntry->structs.size()))
				return nullptr;
			return m_pEntry->structs[structTypeIdx].name.c_str();
		}
		virtual const char* GetStructDoxygenComment(uint32_t structTypeIdx) const override
		{
			if (structTypeIdx >= uint32_t(m_pEntry->structs.size()))
				return nullptr;
			return m_pEntry->structs[structTypeIdx].doxygenComment.c_str();
		}

		virtual uint32_t GetNumStructMembers(uint32_t structTypeIdx) const override
		{
			if (structTypeIdx >= uint32_t(m_pEntry->structs.size()))
				return 0;
			return uint32_t(m_pEntry->structs[structTypeIdx].members.size());
		}
		virtual const char* GetStructMemberType(uint32_t structTypeIdx, uint32_t memberIdx) const override
		{
			if (structTypeIdx >= uint32_t(m_pEntry->structs.size()))
				return nullptr;
			if (memberIdx >= uint32_t(m_pEntry->structs[structTypeIdx].members.size()))
				return nullptr;
			return m_pEntry->structs[structTypeIdx].members[memberIdx].first.c_str();
		}
		virtual const char* GetStructMemberName(uint32_t structTypeIdx, uint32_t memberIdx) const override
		{
			if (structTypeIdx >= uint32_t(m_pEntry->structs.size()))
				return nullptr;
			if (memberIdx >= uint32_t(m_pEntry->structs[structTypeIdx].members.size()))
				return nullptr;
			return m_pEntry->structs[structTypeIdx].members[memberIdx].second.c_str();
		}
	};

	mutable std::vector<CContractSymbols*> m_temporaryContractSymbolObjects;

	virtual transpiler::IContractSymbols* GetContractSymbols(const char *contractFullName) const override;

	virtual bool ContractExists(const char *dAppName, const char *contractName) const override
	{
		// We don't check existing contracts on the chain. That will be check when the contract is deployed by the chain.

		//rt::String_Ref tmp(dAppName);
		//oxd::RVM_DAPP_ID dappId = m_pBcRuntime->FindDAppByName((rvm::ConstString*)&tmp);
		//if (dappId == oxd::RVM_DAPP_ID_INVALID)
		//	return false;
		//rt::String_Ref tmp1(contractName);
		//if (m_pBcRuntime->FindContractByName(dappId, rvm::ContractSection::SCOPE_ADDRESS, (rvm::ConstString*)&tmp1) == oxd::RVM_CONTRACT_ID_INVALID
		//	&& m_pBcRuntime->FindContractByName(dappId, rvm::ContractSection::SCOPE_SHARD, (rvm::ConstString*)&tmp1) == oxd::RVM_CONTRACT_ID_INVALID)
		//	return false;
		//return true;

		std::string fullname = std::string(dAppName) + "." + contractName;

		for (auto &it : m_temporaryCompileData)
		{
			if (it.dapp + "." + it.name == fullname)
				return true;
		}

		return false;
	}

	const ContractDatabaseEntry* GetContractEntryFromFullName(const std::string& fullName) const;

	CContractDatabase *m_pDB = nullptr;
	const std::vector<ContractCompileData> &m_temporaryCompileData;
	rvm::BlockchainRuntime *m_pBcRuntime;
	const rvm::ChainState* m_pChainState;

	mutable std::map<std::string, const ContractDatabaseEntry*> m_contractEntryCache;

public:
	CContractSymbolDatabaseForTranspiler(CContractDatabase *pDB, const std::vector<ContractCompileData> &temporaryCompileData, rvm::BlockchainRuntime *pNativeRuntime, const rvm::ChainState* pChainState)
		: m_pDB(pDB), m_temporaryCompileData(temporaryCompileData), m_pBcRuntime(pNativeRuntime), m_pChainState(pChainState)
	{

	}

	~CContractSymbolDatabaseForTranspiler()
	{
		for (CContractSymbols *pContractSymbol : m_temporaryContractSymbolObjects)
		{
			delete pContractSymbol;
		}
	}

	const std::map<std::string, const ContractDatabaseEntry*>& GetContractEntryCache()
	{
		return m_contractEntryCache;
	}
};
