#pragma once

#include "ContractData.h"
#include "RvmContractDelegate.h"

struct ContractDatabaseEntry
{
	ContractCompileData compileData;
	ContractLinkData linkData;
	
	std::shared_ptr<RvmContractDelegate> contractDelegate;

	rvm::Contract* GetDelegate();
	void CreateDelegate();
};
