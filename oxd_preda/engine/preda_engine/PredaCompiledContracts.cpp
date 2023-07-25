#include "PredaCompiledContracts.h"

PredaCompiledContracts::PredaCompiledContracts(const char *dAppName, rvm::EngineId engineId, uint32_t maxCount)
{
	m_dAppName = dAppName;
	m_engineId = engineId;
	m_contracts.resize(maxCount);		// m_contractDelegates keeps pointers to the contract object, therefore preallocate space here to avoid resizing
	m_contractSourceCodes.resize(maxCount);
	m_contractIntermediateCodes.resize(maxCount);
	m_contractDelegates.resize(maxCount, RvmContractDelegate(nullptr));
}

void PredaCompiledContracts::AddContract(const ContractCompileData &entry, const char *sourceCode, const std::string &intermediateCode, uint32_t slot)
{
	ASSERT(slot < m_contracts.size());

	m_contracts[slot] = entry;
	m_contractSourceCodes[slot] = sourceCode;
	m_contractIntermediateCodes[slot] = intermediateCode;
	m_contractDelegates[slot] = RvmContractDelegate(&m_contracts[slot]);		// The delegate keeps a pointer to the contract object, therefore it must persist in memory

	m_compileOrder.push_back(slot);

	for (auto &imported : entry.importedContracts)
	{
		// already in the dependency list
		if (m_externalDependencies.FindString((imported + ',').c_str()) != -1)
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
			m_externalDependencies += imported.c_str();
			m_externalDependencies += ',';
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

void PredaCompiledContracts::SetDependencyData(std::vector<uint8_t>&& data)
{
	m_dependencyData = data;
}

const std::vector<uint32_t>& PredaCompiledContracts::GetCompileOrder() const
{
	return m_compileOrder;
}


// interfaces from rvm::CompiledModules
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

rvm::ConstData PredaCompiledContracts::GetDependencyData() const
{
	return rvm::ConstData{ m_dependencyData.size() ? &m_dependencyData[0] : nullptr, uint32_t(m_dependencyData.size()) };
}

bool PredaCompiledContracts::ValidateDependency(const rvm::GlobalStates* chain_state) const
{
	if (m_dependencyData.size() == 0)
		return true;

	const rt::String_Ref depStr((char*)m_dependencyData[0], uint32_t(m_dependencyData.size()));
	int32_t nameLen = int32_t(depStr.FindCharacterReverse(';'));
	if (nameLen == -1)
		return true;
	uint32_t depCount = uint32_t(depStr.GetLength() - nameLen) / uint32_t(sizeof(rvm::ContractModuleID));
	std::vector<rt::String_Ref> names(depCount);
	if (rt::String_Ref(depStr.GetString(), nameLen).Split(&names[0], depCount, ';') != depCount)
		return false;

	// all imported contracts must have the same deploy id as at the time of compile
	for (uint32_t i = 0; i < depCount; i++)
	{
		const rvm::ContractModuleID *moduleId = _details::GetOnChainContractModuleIdFromFullName(chain_state, std::string(names[i].GetString(), names[i].GetLength()));
		if (moduleId == nullptr || memcmp(moduleId, ((const rvm::ContractModuleID*)depStr.GetString()) + i, sizeof(rvm::ContractModuleID)) != 0)
			return false;
	}
	return true;
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
