#include <assert.h>
#include "RvmAssetDelegate.h"

//RvmAssetDelegate::RvmAssetDelegate(ContractCompileData* pContractCompiledData)
//{
//	for (size_t i = 0; i < pContractCompiledData->issuedAssets.size(); i++)
//	{
//		m_names.emplace_back(pContractCompiledData->issuedAssets[i].name.c_str());
//		m_flags.emplace_back(pContractCompiledData->issuedAssets[i].flags);
//	}
//}
//
//uint32_t RvmAssetDelegate::GetCount()
//{
//	return uint32_t(m_names.size());
//}
//
//rvm::ConstString RvmAssetDelegate::GetSymbol(uint32_t idx)
//{
//	if (idx >= uint32_t(m_names.size()))
//	{
//		rt::String_Ref tmp;
//		return *(rvm::ConstString*)&tmp;
//	}
//	return *(rvm::ConstString*)&m_names[idx];
//}
//
//rvm::ConstString RvmAssetDelegate::GetFullName(uint32_t idx)
//{
//	rt::String_Ref tmp;
//	return *(rvm::ConstString*)&tmp;
//}
//
//rvm::AssetFlag RvmAssetDelegate::GetFlag(uint32_t idx)
//{
//	if (idx >= uint32_t(m_names.size()))
//		return rvm::AssetFlag(0);
//	return m_flags[idx];
//}
