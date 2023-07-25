#pragma once
#include <assert.h>
#include <string>
#include <vector>
#include "../../native/abi/vm_types.h"
#include "../../native/abi/vm_interfaces.h"
#include "../../transpiler/transpiler/PredaCommon.h"
#include "../../bin/compile_env/include/runtime_interface.h"
//#include "RuntimeInterfaceImpl.h"


struct ContractFunction
{
	std::string name;
	std::string returnType;
	std::vector<std::pair<std::string, std::string>> parameters;
	std::string doxygenComment;
	uint32_t flags;
	std::string signatureHash;
};

struct ContractStruct
{
	std::string doxygenComment;
	std::string name;
	std::vector<std::pair<std::string, std::string>> members;
};

struct ContractEnum
{
	std::string doxygenComment;
	std::string name;
	std::vector<std::string> enumerators;
};

struct ContractInterface
{
	std::string name;
	std::vector<ContractFunction> functions;
};

struct ContractImplementedInterface
{
	std::string name;
	rvm::ContractModuleID interfaceDefContractModuleId;
	uint32_t interfaceDefSlot;
	std::vector<int32_t> functionIds;
};

struct ContractCompileData
{
	std::string dapp;
	std::string name;
	std::string contractDoxygenComment;
	std::string exportUniqueString;

	rvm::HashValue intermediateHash;
	rvm::ContractModuleID moduleId;

	std::vector<ContractFunction> functions;
	int32_t globalDeployFunctionIdx;
	int32_t shardScaleOutFunctionIdx;

	std::vector<ContractInterface> interfaces;
	std::vector<ContractImplementedInterface> implementedInterfaces;

	struct ScopeStateVariableMetadata
	{
		std::string signature;
		std::vector<std::string> comment;
		bool hasAsset;
		bool hasBlob;
	};

	std::vector<ScopeStateVariableMetadata> scopeStateVarMeta;

	std::vector<ContractEnum> enums;
	std::vector<ContractStruct> structs;
	std::vector<std::string> importedContracts;
};

struct ContractLinkData
{
	std::string binaryPathFileName;
	std::string srcPathFileName;
	std::string intermediatePathFileName;
};




namespace _details {
	struct ModuleIdCompare
	{
		bool operator() (const rvm::ContractModuleID& lhs, const rvm::ContractModuleID& rhs) const
		{
			return memcmp(&lhs, &rhs, sizeof(lhs)) < 0;
		}
	};


	// returns rvm::contractIdInvalid if not found
	static rvm::ContractVersionId GetOnChainContractIdFromContractFullName(const rvm::GlobalStates* pChainGlobalState, const std::string& fullName)
	{
		rvm::ConstString contractName = { fullName.c_str(), uint32_t(fullName.size()) };
		return pChainGlobalState->GetContractByName(&contractName);
	}

	static const rvm::ContractModuleID* GetOnChainContractModuleIdFromFullName(const rvm::GlobalStates* pChainGlobalState, const std::string& fullName)
	{
		rvm::ContractVersionId contractVId = GetOnChainContractIdFromContractFullName(pChainGlobalState, fullName);
		const rvm::DeployedContract *pContract = pChainGlobalState->GetContractDeployed(contractVId);
		return pContract ? &pContract->Module : nullptr;
	}

	static transpiler::ScopeType RvmScopeToPredaScope(rvm::Scope scope)
	{
		switch (scope)
		{
		case rvm::Scope::Global:
			return transpiler::ScopeType::Global;
		case rvm::Scope::Shard:
			return transpiler::ScopeType::Shard;
		case rvm::Scope::Address:
			return transpiler::ScopeType::Address;
		case rvm::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySize::UInt32, 0):
			return transpiler::ScopeType::Uint32;
		case rvm::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySize::UInt64, 0):
			return transpiler::ScopeType::Uint64;
		case rvm::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySize::UInt96, 0):
			return transpiler::ScopeType::Uint96;
		case rvm::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySize::UInt128, 0):
			return transpiler::ScopeType::Uint128;
		case rvm::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySize::UInt160, 0):
			return transpiler::ScopeType::Uint160;
		case rvm::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySize::UInt256, 0):
			return transpiler::ScopeType::Uint256;
		case rvm::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySize::UInt512, 0):
			return transpiler::ScopeType::Uint512;
		default:
			return transpiler::ScopeType::None;
		}
	}

	static rvm::Scope PredaScopeToRvmScope(transpiler::ScopeType scope)
	{
		switch (scope)
		{
		case transpiler::ScopeType::Global:
			return rvm::Scope::Global;
		case transpiler::ScopeType::Shard:
			return rvm::Scope::Shard;
		case transpiler::ScopeType::Address:
			return rvm::Scope::Address;
		case transpiler::ScopeType::Uint32:
			return rvm::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySize::UInt32, 0);
		case transpiler::ScopeType::Uint64:
			return rvm::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySize::UInt64, 0);
		case transpiler::ScopeType::Uint96:
			return rvm::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySize::UInt96, 0);
		case transpiler::ScopeType::Uint128:
			return rvm::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySize::UInt128, 0);
		case transpiler::ScopeType::Uint160:
			return rvm::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySize::UInt160, 0);
		case transpiler::ScopeType::Uint256:
			return rvm::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySize::UInt256, 0);
		case transpiler::ScopeType::Uint512:
			return rvm::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySize::UInt512, 0);
		default:
			return rvm::Scope::_Bitmask;
		}
	}

	static prlrt::ContractContextType PredaScopeToRuntimeContextType(transpiler::ScopeType scope)
	{
		switch (scope)
		{
		case transpiler::ScopeType::None:
			return prlrt::ContractContextType::None;
		case transpiler::ScopeType::Global:
			return prlrt::ContractContextType::Global;
		case transpiler::ScopeType::Shard:
			return prlrt::ContractContextType::Shard;
		case transpiler::ScopeType::Address:
			return prlrt::ContractContextType::Address;
		case transpiler::ScopeType::Uint32:
			return prlrt::ContractContextType::Uint32;
		case transpiler::ScopeType::Uint64:
			return prlrt::ContractContextType::Uint64;
		case transpiler::ScopeType::Uint96:
			return prlrt::ContractContextType::Uint96;
		case transpiler::ScopeType::Uint128:
			return prlrt::ContractContextType::Uint128;
		case transpiler::ScopeType::Uint160:
			return prlrt::ContractContextType::Uint160;
		case transpiler::ScopeType::Uint256:
			return prlrt::ContractContextType::Uint256;
		case transpiler::ScopeType::Uint512:
			return prlrt::ContractContextType::Uint512;
		default:
			return prlrt::ContractContextType::None;
		}
	}

	static transpiler::ScopeType RuntimeContextTypeToPredaScope(prlrt::ContractContextType scope)
	{
		switch (scope)
		{
		case prlrt::ContractContextType::None:
			return transpiler::ScopeType::None;
		case prlrt::ContractContextType::Global:
			return transpiler::ScopeType::Global;
		case prlrt::ContractContextType::Shard:
			return transpiler::ScopeType::Shard;
		case prlrt::ContractContextType::Address:
			return transpiler::ScopeType::Address;
		case prlrt::ContractContextType::Uint32:
			return transpiler::ScopeType::Uint32;
		case prlrt::ContractContextType::Uint64:
			return transpiler::ScopeType::Uint64;
		case prlrt::ContractContextType::Uint96:
			return transpiler::ScopeType::Uint96;
		case prlrt::ContractContextType::Uint128:
			return transpiler::ScopeType::Uint128;
		case prlrt::ContractContextType::Uint160:
			return transpiler::ScopeType::Uint160;
		case prlrt::ContractContextType::Uint256:
			return transpiler::ScopeType::Uint256;
		case prlrt::ContractContextType::Uint512:
			return transpiler::ScopeType::Uint512;
		default:
			return transpiler::ScopeType::None;
		}
	}
}