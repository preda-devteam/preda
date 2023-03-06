#include <assert.h>
#include "ContractDatabaseEntry.h"

rvm::Contract* ContractDatabaseEntry::GetDelegate()
{
	if (!contractDelegate)
		CreateDelegate();
	return contractDelegate.get();
}

void ContractDatabaseEntry::CreateDelegate()
{
	contractDelegate = std::shared_ptr<RvmContractDelegate>(new RvmContractDelegate(&compileData, &deployData));
}
