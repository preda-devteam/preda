#pragma once
#include "vm_types.h"

namespace rvm
{
struct CompiledContracts;

#pragma pack(push, 1)

//////////////////////////////////////////////////////////
// Interfaces maye implemented by both sides
struct StringStream
{
	virtual void				Append(const char* str, uint32_t len) = 0;
	virtual char*				AppendBegin(uint32_t over_estimated_len) = 0;  // get a buffer for filling instead of providing a filled buffer, no need to free
	virtual void				AppendEnd(uint32_t finalized_len) = 0;
	virtual ConstString			GetString() = 0;	// lifecycle ends once any subsequent call of StringStream invoked, don't keep the pointer
};

struct DataBuffer
{
	virtual uint8_t*			SetSize(uint32_t len) = 0;  // get a buffer for filling data, no need to free
	virtual const uint8_t*		GetData() = 0;
	virtual uint32_t			GetSize() = 0;
};

struct SystemFunctionOpCodes
{
	OpCode	ShardScaleOut;
	OpCode	ShardDeploy;
	OpCode	GlobalDeploy;
};

struct Interface
{
	virtual ConstString			GetName() const = 0;

	// Function Definitions
	virtual uint32_t			GetFunctionCount() const = 0;
	virtual ConstString			GetFunctionName(uint32_t idx) const = 0;
	virtual FunctionFlag		GetFunctionFlag(uint32_t idx) const = 0;
	virtual Scope				GetFunctionScope(uint32_t idx) const = 0;
	virtual bool				GetFunctionSignature(uint32_t idx, StringStream* signature_out) const = 0;
	virtual OpCode				GetFunctionOpCode(uint32_t idx) const = 0;
};

struct Contract: public Interface // for both PREDA contract and native contract
{
	virtual ContractFlag		GetFlag() const = 0;
	virtual const HashValue*	GetIntermediateRepresentationHash() const = 0;

	// Interface Implemented
	virtual uint32_t			GetInterfaceImplemented(InterfaceId* pIID_out, uint32_t OutBufSize) const = 0;
	virtual OpCode				GetInterfaceImplementedOpCode(InterfaceId i, OpCode code) const = 0;

	// Interface Definitions
	virtual uint32_t			GetInterfaceCount() const = 0;
	virtual const Interface*	GetInterface(uint32_t idx) const = 0;
	virtual InterfaceSlot		GetInterfaceSlot(uint32_t idx) const = 0;  // the contract-level id of an interface definition

	// User-defined Scope Usage/Definition (including scattered maps)
	virtual uint32_t			GetScopeCount() const = 0;
	virtual Scope				GetScope(uint32_t idx) const = 0;
	virtual ConstString			GetScopeName(uint32_t idx) const = 0;
	virtual ScopeDefinitionFlag	GetScopeFlag(uint32_t idx) const = 0;
	virtual ContractScopeId		GetScopeDefinition(uint32_t idx) const = 0; // will be another contract if GetScopeFlag()&ScopeDefinitionFlag::Foreign

	// State Definitions (including scattered maps)
	virtual bool				GetStateSignature(Scope scope, StringStream* signature_out) const = 0;

	// Enum Definitions
	virtual uint32_t			GetEnumCount() const = 0;
	virtual ConstString			GetEnumName(uint32_t idx) const = 0;
	virtual bool				GetEnumSignature(uint32_t idx, StringStream* signature_out) const = 0;

	// Struct Definitions
	virtual uint32_t			GetStructCount() const = 0;
	virtual ConstString			GetStructName(uint32_t idx) const = 0;
	virtual bool				GetStructSignature(uint32_t idx, StringStream* signature_out) const = 0;

	// Chain Specific
	virtual void				GetSystemFunctionOpCodes(SystemFunctionOpCodes* out) const = 0;
};

struct LogMessageOutput
{
	virtual void				Log(LogMessageType type, uint32_t code, uint32_t unitIndex, uint32_t line, uint32_t lineOffset, const ConstString *message) = 0;
};

struct ChainState;
struct ContractRepository // expose all deployed contracts for both PREDA and bc's native built-in contracts
{
	virtual bool				StateJsonify(BuildNum version, ContractScopeId contract, const ConstData* contract_state, StringStream* json_out, const ChainState* ps) const = 0;
	virtual bool				StateJsonParse(BuildNum version, ContractScopeId contract, const ConstString* json, DataBuffer* state_out, const ChainState* ps, LogMessageOutput* error_out = nullptr) const = 0;

	virtual bool				ArgumentsJsonify(BuildNum build_num, ContractScopeId contract, OpCode opcode, const ConstData* args_serialized, StringStream* json_out, const ChainState* ps) const = 0;
	virtual bool				ArgumentsJsonParse(BuildNum build_num, ContractScopeId contract, OpCode opcode, const ConstString* json, DataBuffer* args_serialized, const ChainState* ps, LogMessageOutput* error_out = nullptr) const = 0;

	virtual ContractScopeId		GetScopeDefinition(ContractScopeId cid) const = 0;

	virtual const Contract*		GetContract(const ContractDID* deploy_id) const = 0; // valid build_num starts from 1, specify 0 to get the contract of latest build
	virtual const Interface*	GetInterface(const InterfaceDID* deploy_id) const = 0; // valid build_num starts from 1, specify 0 to get the contract of latest build

	virtual uint32_t			GetContractEnumSignatures(BuildNum build_num, ContractId contract, StringStream* signature_out, const ChainState* ps) const = 0;		// in format "enumtype1=enumerator11,enumerator12,...\nenumtype2=enumerator21,enumerator22,..."
	virtual bool				GetContractFunctionArgumentsSignature(BuildNum build_num, ContractScopeId contract, OpCode opcode, StringStream* signature_out, const ChainState* ps) const = 0;	// in expanded format
	virtual bool				GetContractStateSignature(BuildNum build_num, ContractScopeId contract, StringStream* signature_out, const ChainState* ps) const = 0;
};

struct AggregatedRepository: public ContractRepository	// expose all deployed contracts for both PREDA and bc's native built-in contracts
{

};

//////////////////////////////////////////////////////////
// Interfaces implemented by BC and invoked by RVM engine
struct ChainState
{
	// General state get
	virtual ConstStateData			GetState(ContractScopeId contract) const = 0; // for state in global/shard scope, or address/user-defined scope of the target ExecutionInfo::GetScopeTarget()
	virtual ConstStateData			GetState(ContractScopeId contract, const ScopeKey* key) const = 0; // for values in scattered map in global/shard scope, or address/user-defined scope of the target ExecutionInfo::GetScopeTarget()

	// DApp, Contract, Asset Registration
	virtual DAppId					GetDAppByName(const ConstString* dapp_name) const = 0; // return RVM_DAPP_ID_INVALID if not found
	virtual ConstAddress*			GetDAppOwner(DAppId dapp_id) const = 0;
	virtual uint64_t				GetDAppCreationTime(DAppId dapp_id) const = 0;

	virtual ContractId				GetContractByName(DAppId dapp_id, const ConstString* contract_name) const = 0; // return RVM_CONTRACT_ID_INVALID if not found
	virtual BuildNum				GetContractEffectiveBuild(ContractId contract) const = 0;  // return build num on chain, same contract with different scope will having same build num always, return 0 for not found
	virtual const ContractDID*		GetContractDeploymentIdentifier(ContractId contract, BuildNum version = BuildNumLatest) const = 0; // return on chain CDI of a contract of specific version
	virtual const InterfaceDID*		GetInterfaceDeploymentIdentifier(InterfaceId interf) const = 0; // return on chain CDI of a contract of specific version

	virtual TokenId					GetTokenBySymbol(const rvm::ConstString* token_name) const = 0;
	virtual	ConstString				GetTokenSymbol(TokenId id) const = 0;

	// block info
	virtual uint64_t				GetBlockTime() const = 0;
	virtual ConstAddress*			GetBlockCreator() const = 0;
	virtual ScaleOutMode			GetScalingUpMode() const = 0;
	virtual const HashValue*		GetBlockHash() const = 0;
	virtual uint32_t				GetShardIndex() const = 0;
	virtual uint32_t				GetShardOrder() const = 0;
	virtual uint64_t				GetBlockHeight() const = 0;
};

struct InvocationInfo
{
	// transaction info
	virtual ScopeKey				GetScopeTarget() const = 0;	// return nullptr if current scope is PERSHARD
	virtual OpCode					GetOpCode() const = 0;
	virtual ContractScopeId			GetContractId() const = 0;
	virtual BuildNum				GetBuildNum() const = 0;
	virtual uint64_t				GetTimestamp() const = 0;
	virtual InvokeContextType		GetInvokeType() const = 0;
	// transaction: normal txn
	virtual ConstAddress*			GetSigner(uint32_t i) const = 0;
	virtual uint32_t				GetSignerCount() const = 0;
	virtual bool					IsSignedBy(ConstAddress* addr) const = 0;
	// transaction: relay txn
	virtual uint32_t				GetOriginatedShardIndex() const = 0; // Index of the originate shard (relay transaction only)
	virtual uint32_t				GetOriginatedShardOrder() const = 0;
	virtual uint64_t				GetOriginatedBlockHeight() const = 0;
	virtual ConstAddress*			GetInitiator() const = 0;	// return nullptr if current scope is PERSHARD
};

struct ExecutionState: public ChainState
					 , public InvocationInfo
{
};

struct ExecutionContext: public ExecutionState
{
	virtual uint64_t				GetRandomNumber() = 0;

	// returns null if the state doesn't exist
	virtual uint8_t*				AllocateStateMemory(uint32_t dataSize) = 0;
	virtual void					DiscardStateMemory(uint8_t* state_memory) = 0;		// `state` must be allocated from AllocateState
	virtual void					CommitNewState(BuildNum version, ContractScopeId contract, uint8_t* state_memory) = 0;  // `state_memory` must be allocated from AllocateStateMemory, or be nullptr to empty the state
	virtual void					CommitNewState(BuildNum version, ContractScopeId contract, const ScopeKey* key, uint8_t* state_memory) = 0;

	virtual bool					EmitRelayToAddress(BuildNum version, ConstAddress* target, ContractScopeId cid, OpCode opcode, const ConstData* args_serialized, uint32_t gas_redistribution_weight) = 0;
	virtual bool					EmitRelayToGlobal(BuildNum version, ContractScopeId cid, OpCode opcode, const ConstData* args_serialized, uint32_t gas_redistribution_weight) = 0;
	virtual bool					EmitBroadcastToShards(BuildNum version, ContractScopeId cid, OpCode opcode, const ConstData* args_serialized, uint32_t gas_redistribution_weight) = 0; // global scope to all shards

	// invoke a contract function (may cross-engine)
	virtual ExecuteResult			Invoke(uint32_t gas_limit, BuildNum version, ContractScopeId contract, OpCode opcode, const ConstData* args_serialized) = 0; // return pointer will be invalid after next call of `Invoke` or `SetReturnValue`						

	// set return value of current function being invoking
	virtual void					SetReturnValue(const ConstData* args_serialized) = 0;
	virtual uint8_t*				SetReturnValueClaim(uint32_t size_estimated) = 0;
	virtual void					SetReturnValueFinalize(uint32_t size_finalized) = 0;
};

struct BlockchainRuntime
{
	// Types and Contracts of Native DApp (Core)
	virtual int32_t					JsonifyCoreType(NativeTypeId tid, const ConstData* serialized, StringStream* json_out) const = 0; // -1 for error, or #bytes eta
	virtual bool					JsonParseCoreType(NativeTypeId tid, const ConstString* json, DataBuffer* serialized_out) const = 0;

	virtual ConstString				GetCoreDAppName() const = 0;
	virtual AggregatedRepository*	GetContractRepository() = 0;  // no need to release

	virtual void					DebugPrint(DebugMessageType type, const ConstString* string, const ExecutionState* ctx_opt = nullptr, const Contract* contract_opt = nullptr) = 0;
};


//////////////////////////////////////////////////////////
// Interfaces implemented by RVM engine and invoked by BC
struct CompiledContracts
{
	virtual EngineId				GetEngineId() const = 0;
	virtual ConstString				GetDAppName() const = 0;
	virtual uint32_t				GetCount() const = 0;
	virtual const Contract*			GetContract(uint32_t idx) const = 0;  // may return nullptr if `idx` contract is failed in compilation
	virtual ConstString				GetExternalDependencies() const = 0;   // list of contract names, "dapp_name.contract_name,dapp.contract..."
	virtual bool					IsLinked() const = 0;
	virtual void					Release() = 0;
};

struct ExecuteUnit		// multi-instances are allowed, and may run in different threads
{
	virtual InvokeResult			Invoke(ExecutionContext* exec, uint32_t gas_limit, BuildNum version, ContractScopeId contract, OpCode opcode, const ConstData* args_serialized) = 0;
	// Deploy the contracts into repository and ready for execution and cross-contract reference
	virtual InvokeResult			Deploy(	ExecutionContext* exec, uint32_t gas_limit, 
											CompiledContracts* linked, 
											rvm::ContractDID* contract_deployment_ids,		// CDID[contracts_count]
											rvm::InterfaceDID** interface_deployment_ids,	// IDID[contracts_count][#_of_interface_in_each_contract]
											LogMessageOutput* log_msg_output
									) = 0;
	virtual void					Release() = 0;
};

struct RvmEngine: public ContractRepository // singleton
{
	virtual bool			Initialize(const char* module_path, const char* db_path, BlockchainRuntime* runtime_api, rvm::ConstString *initErrorMsg = nullptr) = 0;
	virtual void			Release() = 0;

	virtual ConstString		GetVersion() const = 0;
	virtual ConstString		GetName() const = 0;
	virtual ConstString		GetVendorInfo() const = 0;

	// Build a collection of contracts
	// Compile source to intermediate representation (PREDA: source code to C++)
	virtual bool			Compile(	const ChainState* chain_state,
										const ConstString* dapp_name,
										uint32_t contract_count, 
										const ConstData* deploy_data_array,	// size = contract_count
										CompilationFlag flag,
										CompiledContracts** compiled_output,
										DataBuffer* dependency,  // call SetSize(0) if no dependency data
										LogMessageOutput* log_msg_output
							) = 0;
	// Build intermediate representation to platform specific runtime (PREDA: C++ to dll/so, involving extern gcc compiler) 
	virtual bool			Link(		CompiledContracts* compiled,
										LogMessageOutput* log_msg_output
							) = 0;
	// Verify a previously compiled contract is compatible with current chain state
	virtual bool			ValidateDependency(const ChainState* chain_state, CompiledContracts* compiled, const ConstData* dependency) = 0;

	virtual ExecuteUnit*	CreateExecuteUnit() = 0;
};

typedef rvm::RvmEngine* (*GetEngineFunctionType)(const char* config);
inline const char* GetEngineFunctionName(){ return "CreateEngine"; }

#pragma pack(pop)
} // namespace rvm
