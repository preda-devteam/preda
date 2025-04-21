#pragma once
#include "../native/abi/vm_interfaces.h"
#include "../native/types/array.h"
#include "../native/types/ordered_map.h"
#include "../native/types/coins.h"
#include "../native/types/wallet.h"
#include "shard_data.h"


namespace oxd
{
struct ContractsDatabase;

template<rvm::ContractInvokeId cid>
struct CoreContractTypeTraits;

#define ALL_CORE_CONTRACTS																																											\
			DEF_CORE_CONTRACT(CORE_WALLET,			 "core.wallet",				((((uint32_t)rvm::Scope::Address)<<10) + 1),	rvm::CoinsWallet)													\
			DEF_CORE_CONTRACT(CORE_TOKEN_SUPPLIERS,	 "core.token_suppliers",	((((uint32_t)rvm::Scope::Global)<<10) +  1),	MARCO_CONCAT(rvm::OrderedMap<rvm::UInt128, rvm::TokenMinterFlag>))	\
			DEF_CORE_CONTRACT(CORE_CONTRACT_DEFAULT, "core.token_default",		((((uint32_t)rvm::Scope::Global)<<10) +  2),	MARCO_CONCAT(rvm::OrderedMap<rvm::ContractId, rvm::TokenId>))		\

// define all core contract ids
#define DEF_CORE_CONTRACT(ciid, name, sn, type)																										\
		static constexpr auto ciid = rvm::CONTRACT_ID_MAKE(sn, rvm::DAppIdCore, rvm::EngineId::Core) + rvm::BuildNumInit + (rvm::Scope(sn>>10));	\
		template<> struct CoreContractTypeTraits<ciid> {																							\
			typedef type StateType;																													\
		};

ALL_CORE_CONTRACTS
#undef DEF_CORE_CONTRACT

template<rvm::ContractInvokeId ciid>
class CoreContractState: public ConstState<typename CoreContractTypeTraits<ciid>::StateType>
{	typedef ConstState<typename CoreContractTypeTraits<ciid>::StateType> _SC;
public:
	CoreContractState(const rvm::ConstStateData& data):_SC(data){}
	CoreContractState(const SimuState* s):_SC(s){}
};

class CoreEngine: public rt::Singleton<CoreEngine>
				, public rvm::RvmEngine
{
	// ContractRepository
	virtual bool					StateJsonify(rvm::ContractInvokeId contract, const rvm::ConstData* contract_state, rvm::StringStream* json_out) const;
	virtual bool					StateJsonParse(rvm::ContractInvokeId contract, const rvm::ConstString* json, rvm::DataBuffer* state_out, rvm::LogMessageOutput* error_out = nullptr) const;
	virtual bool 					ScatteredStateKeyJsonify(rvm::ContractInvokeId contract, const rvm::ConstData* key_data, rvm::StringStream* json_out) const { return false; };

	virtual bool					ArgumentsJsonify(rvm::ContractInvokeId contract, rvm::OpCode opcode, const rvm::ConstData* args_serialized, rvm::StringStream* json_out) const { return false; }
	virtual bool					ArgumentsJsonParse(rvm::ContractInvokeId contract, rvm::OpCode opcode, const rvm::ConstString* json, rvm::DataBuffer* args_serialized, rvm::LogMessageOutput* error_out = nullptr) const { return false; }
	virtual rvm::ContractScopeId	GetScopeDefinition(rvm::ContractScopeId cid) const { return rvm::ContractScopeIdInvalid; }
	virtual const rvm::Contract*	GetContract(const rvm::ContractModuleID* module_id) const { return nullptr; }
	virtual uint32_t				GetContractEnumSignatures(rvm::ContractVersionId contract, rvm::StringStream* signature_out) const { return 0; }
	virtual bool					GetContractFunctionArgumentsSignature(rvm::ContractInvokeId contract, rvm::OpCode opcode, rvm::StringStream* signature_out) const { return false; }
	virtual bool					GetContractStateSignature(rvm::ContractInvokeId contract, rvm::StringStream* signature_out) const { return false; }

	// RvmEngine
	virtual bool					Initialize(const char* module_path, const char* db_path, rvm::BlockchainRuntime* runtime_api, rvm::ConstString *initErrorMsg = nullptr){ return true; };
	virtual void					Release(){} // it is a singleton

	virtual rvm::ConstString		GetVersion() const { return { "v0.1", 4 }; }
	virtual rvm::ConstString		GetName() const { return { "core", 4 }; }
	virtual rvm::ConstString		GetVendorInfo() const { return { "Chain-Simulator/PREDA Dev Team", 30 }; }

	virtual rvm::ConstString		GetContractName(const rvm::ConstData* source_code){ return { nullptr, 0 }; }
	virtual bool					Compile(const rvm::ConstString*	dapp_name,
											uint32_t				contract_count, 
											const rvm::ConstData*	deploy_data_array,	// size = contract_count
											rvm::CompilationFlag	flag,
											rvm::CompiledModules**	compiled_output,
											rvm::LogMessageOutput*	log_msg_output
									){ return false; }
	virtual bool					Recompile(	const rvm::ConstString*	dapp_name,
												const rvm::ConstData*	dependency_data,
												uint32_t				contract_count, 
												const rvm::ConstData*	deploy_data_array,	// size = contract_count
												rvm::CompilationFlag	flag,
												rvm::CompiledModules**	compiled_output,
												rvm::LogMessageOutput*	log_msg_output
									){ return false; }
	virtual bool					Link(rvm::CompiledModules* compiled, rvm::LogMessageOutput* log_msg_output){ return false; }
	virtual void					CancelCurrentBuildingTask(){}
	virtual rvm::ExecutionUnit*		CreateExecuteUnit(){ return nullptr; }

public:
	const rvm::Contract*			GetContract(rvm::ContractVersionId cvid) const;
	static void						InitContractsDatabase(ContractsDatabase& x);
};

// Gas calculation
enum GasCoefficients
{
	GAS_PERBYTE_OF_ARGUMENT		= 1,
	GAS_PERBYTE_OF_STATE		= 8,
	GAS_PERBYTE_OF_SOURCECODE	= GAS_PERBYTE_OF_STATE*16,	// for contract compiling
	GAS_PERBYTE_OF_BLOB			= 2,
	GAS_PERBYTE_OF_BLOB_NEGEXP	= 6,

	GAS_PERSECOND_OF_BUILD		= 100,

	GAS_STATE_WRITE_MULTIPLIER	= 32,
	GAS_STATE_WRITE_BN			= 10*GAS_STATE_WRITE_MULTIPLIER,
	GAS_STATE_WRITE_COIN		= 12*GAS_STATE_WRITE_MULTIPLIER,

	GAS_PERENTRY_OF_ID			= 32,
	GAS_PERENTRY_OF_DELEGATION	= 64,
	GAS_PERENTRY_OF_CONTRACT	= 1024,

	GAS_NATIVE_OP				= 1,
	GAS_BN_ASSIGN_FROM_ROUGH	= 1,
	GAS_BN_MULTIPLY				= 16,
	GAS_BN_COMPARE_BN			= 4,
	GAS_BN_ADD_BN				= 8,
	GAS_HASHSET_LOOKUP			= 2,
	GAS_HASHSET_MODIFY			= GAS_HASHSET_LOOKUP*32,
	GAS_ORDERED_LOOKUP			= 2,
	GAS_ORDERED_MODIFY			= GAS_ORDERED_LOOKUP*32,
	GAS_POINT_LOOKUP			= 1,
	GAS_POINT_MODIFY			= GAS_POINT_LOOKUP*32,
	GAS_SCATTERED_LOOKUP		= 1,
	GAS_SCATTERED_MODIFY		= GAS_SCATTERED_LOOKUP*2,

	GAS_RELAY_EMIT				= 64,
	GAS_GLOBAL_MULTIPLIER		= 16,

	GAS_FEE_COMPUTE				= GAS_BN_MULTIPLY + GAS_BN_ASSIGN_FROM_ROUGH + GAS_BN_COMPARE_BN + GAS_BN_ADD_BN,
	GAS_RVM_COMPILE				= 1024,
};

inline constexpr uint32_t SIZE_OF_DEPLOY_CONFIGING = 45;	// size of struct DeployConfig define in core contracts
inline constexpr uint32_t SIZE_OF_SCHEDULEDDEPLOYMENT = 17;	// size of struct ScheduledDeployment define in core contracts
} // namespace oxd