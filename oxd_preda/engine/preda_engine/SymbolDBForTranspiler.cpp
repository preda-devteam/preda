#include "ContractDatabase.h"
#include "SymbolDBForTranspiler.h"

transpiler::IContractSymbols* CContractSymbolDatabaseForTranspiler::GetContractSymbols(const char *contractFullName) const
{
	for (auto &it : m_temporaryCompileData)
	{
		if (it.dapp + "." + it.name == contractFullName)
		{
			CContractSymbols *ret = new CContractSymbols(&it);
			m_temporaryContractSymbolObjects.push_back(ret);
			return ret;
		}
	}

	const ContractDatabaseEntry* pEntry = GetContractEntryFromFullName(contractFullName);

	if (pEntry == nullptr)
		return nullptr;

	CContractSymbols *ret = new CContractSymbols(&pEntry->compileData);		// always importing from the latest version
	m_temporaryContractSymbolObjects.push_back(ret);
	return ret;
}

const ContractDatabaseEntry* CContractSymbolDatabaseForTranspiler::GetContractEntryFromFullName(const std::string& fullName) const
{
	auto itor = m_contractEntryCache.find(fullName);
	if (itor != m_contractEntryCache.end())
		return itor->second;

	const ContractDatabaseEntry* pEntry = m_pDB->FindContractEntry(_details::GetOnChainPredaContractDIdFromFullName(m_pChainState, fullName));
	m_contractEntryCache.emplace(fullName, pEntry);

	return pEntry;
}
