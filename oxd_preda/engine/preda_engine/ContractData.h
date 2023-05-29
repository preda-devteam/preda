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
	std::vector<int32_t> functionIds;
};

struct ContractCompileData
{
	std::string dapp;
	std::string name;
	std::string contractDoxygenComment;
	std::string exportUniqueString;

	rvm::HashValue intermediateHash;

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

// data only available after deploy
struct ContractDeployData
{
	rvm::ContractId contractId;
	std::vector<rvm::ContractId> importedContractIds;
};

struct ContractLinkData
{
	std::string binaryPathFileName;
	std::string srcPathFileName;
	std::string intermediatePathFileName;
};

using PredaContractDID = uint64_t;

namespace _details {
	static const PredaContractDID PredaContractDIDInvalid = (PredaContractDID)0;
	inline constexpr PredaContractDID RvmCDIDToPredaCDID(const rvm::ContractDID* rvmCDId)
	{
		return rvmCDId ? *(PredaContractDID*)rvmCDId : PredaContractDIDInvalid;
	}
	inline constexpr void PredaCDIDToRvmCDID(PredaContractDID predaCDId, rvm::ContractDID* rvmCDId)
	{
		if (rvmCDId)
		{
			rt::Zero(*rvmCDId);
			*(PredaContractDID*)rvmCDId = predaCDId;
		}
	}
	// returns rvm::contractIdInvalid if not found
	static rvm::ContractId GetOnChainContractIdFromContractFullName(const rvm::ChainState* pChainState, const std::string& fullName)
	{
		std::string::size_type dotPos = fullName.find('.');
		if (dotPos != std::string::npos)
		{
			rvm::ConstString dappName = { fullName.c_str(), uint32_t(dotPos) };
			rvm::DAppId dAppId = pChainState->GetDAppByName(&dappName);
			if (dAppId != rvm::DAppIdInvalid)
			{
				rvm::ConstString contractName = { fullName.c_str() + dotPos + 1, uint32_t(fullName.size() - dotPos - 1) };
				return pChainState->GetContractByName(dAppId, &contractName);
			}
		}

		return rvm::ContractIdInvalid;
	}

	static PredaContractDID GetOnChainPredaContractDIdFromFullName(const rvm::ChainState* pChainState, const std::string& fullName, rvm::BuildNum buildNum = rvm::BuildNumLatest)
	{
		rvm::ContractId contractId = GetOnChainContractIdFromContractFullName(pChainState, fullName);
		return RvmCDIDToPredaCDID(pChainState->GetContractDeploymentIdentifier(contractId, buildNum));
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
		case rvm::_details::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySize::UInt16, 0):
			return transpiler::ScopeType::Uint16;
		case rvm::_details::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySize::UInt32, 0):
			return transpiler::ScopeType::Uint32;
		case rvm::_details::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySize::UInt64, 0):
			return transpiler::ScopeType::Uint64;
		case rvm::_details::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySize::UInt256, 0):
			return transpiler::ScopeType::Uint256;
		case rvm::_details::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySize::UInt512, 0):
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
		case transpiler::ScopeType::Uint16:
			return rvm::Scope::UInt16;
		case transpiler::ScopeType::Uint32:
			return rvm::Scope::UInt32;
		case transpiler::ScopeType::Uint64:
			return rvm::Scope::UInt64;
		case transpiler::ScopeType::Uint256:
			return rvm::Scope::UInt256;
		case transpiler::ScopeType::Uint512:
			return rvm::Scope::UInt512;
		default:
			return rvm::Scope::Neutral;
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
		case transpiler::ScopeType::Uint16:
			return prlrt::ContractContextType::Uint16;
		case transpiler::ScopeType::Uint32:
			return prlrt::ContractContextType::Uint32;
		case transpiler::ScopeType::Uint64:
			return prlrt::ContractContextType::Uint64;
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
		case prlrt::ContractContextType::Uint16:
			return transpiler::ScopeType::Uint16;
		case prlrt::ContractContextType::Uint32:
			return transpiler::ScopeType::Uint32;
		case prlrt::ContractContextType::Uint64:
			return transpiler::ScopeType::Uint64;
		case prlrt::ContractContextType::Uint256:
			return transpiler::ScopeType::Uint256;
		case prlrt::ContractContextType::Uint512:
			return transpiler::ScopeType::Uint512;
		default:
			return transpiler::ScopeType::None;
		}
	}
}