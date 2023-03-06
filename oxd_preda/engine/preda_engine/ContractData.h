#pragma once
#include <assert.h>
#include <string>
#include <vector>
#include "../../native/abi/vm_types.h"
#include "../../native/abi/vm_interfaces.h"
#include "../../transpiler/transpiler/PredaCommon.h"
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

	std::string perAddressStateVariableSignature;
	std::vector<std::string> perAddressStateVariableComment;
	bool perAddressStateVariableHasAsset;
	bool perAddressStateVariableHasBlob;
	std::string perShardStateVariableSignature;
	std::vector<std::string> perShardStateVariableComment;
	bool perShardStateVariableHasAsset;
	bool perShardStateVariableHasBlob;
	std::string globalStateVariableSignature;
	std::vector<std::string> globalStateVariableComment;
	bool globalStateVariableHasAsset;
	bool globalStateVariableHasBlob;

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

	static const PredaContractDID GetOnChainPredaContractDIdFromFullName(const rvm::ChainState* pChainState, const std::string& fullName, rvm::BuildNum buildNum = rvm::BuildNumLatest)
	{
		rvm::ContractId contractId = GetOnChainContractIdFromContractFullName(pChainState, fullName);
		return RvmCDIDToPredaCDID(pChainState->GetContractDeploymentIdentifier(contractId, buildNum));
	}
}