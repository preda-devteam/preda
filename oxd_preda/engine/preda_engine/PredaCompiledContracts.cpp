#include "PredaCompiledContracts.h"

PredaCompiledContracts::PredaCompiledContracts(const char *dAppName, rvm::EngineId engineId, uint32_t maxCount)
{
	m_dAppName = dAppName;
	m_engineId = engineId;
	m_contracts.reserve(maxCount);
	m_contractSourceCodes.reserve(maxCount);
	m_contractIntermediateCodes.reserve(maxCount);
	m_contractDelegates.reserve(maxCount);
}

void PredaCompiledContracts::AddContract(const ContractCompileData &entry, const char *sourceCode, const std::string &intermediateCode)
{
	ASSERT(m_contracts.capacity() > m_contracts.size());

	m_contracts.push_back(entry);
	m_contractSourceCodes.push_back(sourceCode);
	m_contractIntermediateCodes.push_back(intermediateCode);
	m_contractDelegates.emplace_back(&m_contracts.back(), nullptr);

	for (auto &imported : entry.importedContracts)
	{
		// already in the dependency list
		if (m_externalDependencies.FindString(imported.c_str()) != -1)
			continue;

		// if it's internal dependency
		bool bInternalDependency = false;
		for (auto &contract : m_contracts)
			if (contract.dapp + "." + contract.name == imported)
			{
				bInternalDependency = true;
				break;
			}
		if (!bInternalDependency)
		{
			if (m_externalDependencies.GetLength() > 0)
				m_externalDependencies += ',';
			m_externalDependencies += imported.c_str();
		}
	}
}

const char* PredaCompiledContracts::GetContractSourceCode(uint32_t contractIdx)
{
	return contractIdx >= m_contractSourceCodes.size() ? nullptr : m_contractSourceCodes[contractIdx].c_str();
}

const char* PredaCompiledContracts::GetContractIntermediateCode(uint32_t contractIdx)
{
	return contractIdx >= m_contractIntermediateCodes.size() ? nullptr : m_contractIntermediateCodes[contractIdx].c_str();
}

const ContractCompileData* PredaCompiledContracts::GetCompiledData(uint32_t contractIdx) const
{
	return contractIdx >= m_contracts.size() ? nullptr : &m_contracts[contractIdx];
}

void PredaCompiledContracts::AttachLinkData(std::vector<ContractLinkData>&& linkData)
{
	m_contractsLinkData = linkData;
}

const ContractLinkData* PredaCompiledContracts::GetLinkData(uint32_t contractIdx) const
{
	return contractIdx >= m_contractsLinkData.size() ? nullptr : &m_contractsLinkData[contractIdx];
}

// interfaces from rvm::CompiledContracts
rvm::EngineId PredaCompiledContracts::GetEngineId() const
{
	return m_engineId;
}


rvm::ConstString PredaCompiledContracts::GetDAppName() const
{
	return *(rvm::ConstString*)&m_dAppName;
}

uint32_t PredaCompiledContracts::GetCount() const
{
	return uint32_t(m_contracts.size());
}

const rvm::Contract* PredaCompiledContracts::GetContract(uint32_t idx) const
{
	if (idx >= uint32_t(m_contractDelegates.size()))
		return nullptr;

	return &m_contractDelegates[idx];
}

rvm::ConstString PredaCompiledContracts::GetExternalDependencies() const
{
	return *(rvm::ConstString*)&m_externalDependencies;
}

bool PredaCompiledContracts::IsLinked() const
{
	return m_contractsLinkData.size() == m_contracts.size();
}

void PredaCompiledContracts::Release()
{
	for (auto& itor : m_contractsLinkData)
	{
		os::File::Remove(itor.binaryPathFileName.c_str());
		os::File::Remove(itor.intermediatePathFileName.c_str());
		os::File::Remove(itor.srcPathFileName.c_str());
	}
	delete this;
}
