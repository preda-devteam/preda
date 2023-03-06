#pragma once

#include "ContractData.h"
#include "RvmContractDelegate.h"

struct ContractDatabaseEntry
{
	ContractCompileData compileData;
	ContractLinkData linkData;
	ContractDeployData deployData;
	
	PredaContractDID deployIdentifier;

	std::shared_ptr<RvmContractDelegate> contractDelegate;

	rvm::Contract* GetDelegate();
	void CreateDelegate();
};
