#pragma once

#include <assert.h>
#include "../../native/abi/vm_interfaces.h"
#include "../../transpiler/transpiler/PredaCommon.h"
#include "ContractData.h"
#include "RvmContractDelegate.h"
#include "RvmAssetDelegate.h"

struct PredaCompiledContracts : public rvm::CompiledContracts
{
private:
	rvm::EngineId m_engineId;
	rt::String m_dAppName;
	rt::String m_externalDependencies;
	std::vector<RvmContractDelegate> m_contractDelegates;
	std::vector<ContractCompileData> m_contracts;
	std::vector<std::string> m_contractSourceCodes;
	std::vector<std::string> m_contractIntermediateCodes;
	std::vector<ContractLinkData> m_contractsLinkData;

public:
	PredaCompiledContracts(const char *dAppName, rvm::EngineId engineId, uint32_t maxCount);
	void AddContract(const ContractCompileData &entry, const char *sourceCode, const std::string &intermediateCode);
	const char* GetContractSourceCode(uint32_t contractIdx);
	const char* GetContractIntermediateCode(uint32_t contractIdx);
	const ContractCompileData* GetCompiledData(uint32_t contractIdx) const;
	void AttachLinkData(std::vector<ContractLinkData> &&linkData);		// data in linkData would be moved to PredaCompiledContracts
	const ContractLinkData* GetLinkData(uint32_t contractIdx) const;

	// interfaces from rvm::CompiledContracts
	virtual rvm::EngineId GetEngineId() const override;
	virtual rvm::ConstString GetDAppName() const override;
	virtual uint32_t GetCount() const override;
	virtual const rvm::Contract* GetContract(uint32_t idx) const override;
	virtual rvm::ConstString GetExternalDependencies() const override;
	virtual bool IsLinked() const override;
	virtual void Release() override;
};
