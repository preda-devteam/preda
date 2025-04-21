#pragma once
#include "vm_types.h"

namespace rvm
{
struct CompiledModules;
struct BigNum;

static const uint32_t	RVM_GAS_BURNT_DEFAULT = 100;

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

struct NativeTokens
{
	virtual uint32_t			GetCount() const = 0;
	virtual ConstNativeToken	Get(uint32_t idx) const = 0;
	virtual void				Release() = 0;
};

struct Interface
{
	virtual ConstString			GetName() const = 0;
	virtual ConstString			GetFullName() const = 0;

	// Function Definitions
	virtual uint32_t			GetFunctionCount() const = 0;
	virtual ConstString			GetFunctionName(uint32_t idx) const = 0;
	virtual FunctionFlag		GetFunctionFlag(uint32_t idx) const = 0;
	virtual Scope				GetFunctionScope(uint32_t idx) const = 0;
	virtual OpCode				GetFunctionOpCode(uint32_t idx) const = 0;
	virtual bool				GetFunctionSignature(uint32_t idx, StringStream* signature_out) const = 0;
};

struct Contract: public Interface // for both PREDA contract and native contract
{
	virtual ContractFlag			GetFlag() const = 0;
	virtual const ContractModuleID* GetModuleID() const = 0;

	// Interface Implemented
	virtual uint32_t				GetInterfaceImplementedCount() const = 0;
	virtual const Interface*		GetInterfaceImplemented(uint32_t idx) const = 0;
	virtual OpCode					GetInterfaceImplementedOpCode(uint32_t idx, OpCode code) const = 0;  // convert opcode in Interface to opcode in Contract

	// Interface Definitions
	virtual uint32_t				GetInterfaceCount() const = 0;
	virtual const Interface*		GetInterface(uint32_t idx) const = 0;
	virtual InterfaceSlot			GetInterfaceSlot(uint32_t idx) const = 0;  // the contract-level id of an interface definition

	// User-defined Scope Usage/Definition (including scattered maps)
	virtual uint32_t				GetScopeCount() const = 0;
	virtual Scope					GetScope(uint32_t idx) const = 0;
	virtual ConstString				GetScopeName(uint32_t idx) const = 0;
	virtual ScopeFlag				GetScopeFlag(uint32_t idx) const = 0;

	// State Definitions (including scattered maps)
	virtual bool					GetStateSignature(Scope scope, StringStream* signature_out) const = 0;

	// Enum Definitions
	virtual uint32_t				GetEnumCount() const = 0;
	virtual ConstString				GetEnumName(uint32_t idx) const = 0;
	virtual bool					GetEnumSignature(uint32_t idx, StringStream* signature_out) const = 0;

	// Struct Definitions
	virtual uint32_t				GetStructCount() const = 0;
	virtual ConstString				GetStructName(uint32_t idx) const = 0;
	virtual bool					GetStructSignature(uint32_t idx, StringStream* signature_out) const = 0;

	// Chain Specific
	virtual void					GetSystemFunctionOpCodes(SystemFunctionOpCodes* out) const = 0;
};

struct LogMessageOutput
{
	virtual void					Log(LogMessageType type, uint32_t code, uint32_t unitIndex, uint32_t line, uint32_t lineOffset, const ConstString *message) = 0;
};

struct GlobalStates;
struct ContractRepository // expose all deployed contracts for both PREDA and bc's native built-in contracts
{
	virtual bool					StateJsonify(ContractInvokeId contract, const ConstData* contract_state, StringStream* json_out) const = 0;
	virtual bool					StateJsonParse(ContractInvokeId contract, const ConstString* json, DataBuffer* state_out, LogMessageOutput* error_out = nullptr) const = 0;

	virtual bool					ScatteredStateKeyJsonify(ContractInvokeId contract, const ConstData* key_data, StringStream* json_out) const = 0;

	virtual bool					ArgumentsJsonify(ContractInvokeId contract, OpCode opcode, const ConstData* args_serialized, StringStream* json_out) const = 0;
	virtual bool					ArgumentsJsonParse(ContractInvokeId contract, OpCode opcode, const ConstString* json, DataBuffer* args_serialized, LogMessageOutput* error_out = nullptr) const = 0;

	virtual ContractScopeId			GetScopeDefinition(ContractScopeId cid) const = 0;
	virtual const Contract*			GetContract(const ContractModuleID* module_id) const = 0; // valid build_num starts from 1, specify 0 to get the contract of latest build

	virtual uint32_t				GetContractEnumSignatures(ContractVersionId contract, StringStream* signature_out) const = 0;		// in format "enumtype1=enumerator11,enumerator12,...\nenumtype2=enumerator21,enumerator22,..."
	virtual bool					GetContractFunctionArgumentsSignature(ContractInvokeId contract, OpCode opcode, StringStream* signature_out) const = 0;	// in expanded format
	virtual bool					GetContractStateSignature(ContractInvokeId contract, StringStream* signature_out) const = 0;
};

//////////////////////////////////////////////////////////
// Interfaces implemented by BC and invoked by RVM engine
struct DeployedContract
{
	ContractModuleID				Module;
	uint64_t						Height;		// the block height that a contract is launched
	uint64_t						DAppName;	// DAppName in u64
	BuildNum						Version;
	uint16_t						StubSize;
	uint8_t							Stub[1];	// deployment stub, size = StubSize
};

struct GlobalStates // only available in global scope
{
	virtual DAppId					GetDAppByName(const ConstString* dapp_name) const = 0; // return RVM_DAPP_ID_INVALID if not found
	virtual ContractVersionId		GetContractByName(const ConstString* dapp_period_contract_name) const = 0; // return rvm::ContractScopeIdInvalid if not found
	virtual BuildNum				GetContractEffectiveBuild(ContractId contract) const = 0;
	virtual const DeployedContract*	GetContractDeployed(ContractVersionId contract) const = 0; // return on chain CMID of a contract of specific version
	virtual TokenMinterFlag			GetTokenMinterState(TokenId tid, ContractId contract) const = 0;
};

struct ChainStates: public GlobalStates
{
	// General state get
	virtual ConstStateData			GetState(ContractScopeId contract) const = 0; // for state in global/shard scope, or address/user-defined scope with the target available in ExecutionInfo::GetScopeTarget()
	virtual ConstStateData			GetState(ContractScopeId contract, const ScopeKey* key) const = 0; // for values in scattered map in global/shard scope, or address/user-defined scope of the target ExecutionInfo::GetScopeTarget()

	// block info
	virtual uint64_t				GetBlockTime() const = 0;
	virtual ConstAddress*			GetBlockCreator() const = 0;
	virtual ScaleOutMode			GetScalingUpMode() const = 0;
	virtual const HashValue*		GetPrevBlockHash() const = 0;
	virtual uint32_t				GetShardIndex() const = 0;
	virtual uint32_t				GetShardOrder() const = 0;
	virtual uint64_t				GetBlockHeight() const = 0;
};

struct InvocationInfo
{
	// transaction info
	virtual	const HashValue*		GetTxnHash(HashValue* hash_out = nullptr) const = 0; // hash_out can be nullptr is current utxn is the first one in a relay group, or in a non-grouped txn
	virtual uint32_t				GetMicroTxnIndex() const = 0;
	virtual ScopeKey				GetScopeTarget() const = 0;	// return nullptr if current scope is PERSHARD
	virtual OpCode					GetOpCode() const = 0;
	virtual ContractInvokeId		GetContractId() const = 0;
	virtual const NativeTokens*		GetNativeTokenSupplied() const = 0; // normal txn only (InvokeContextType::Normal)
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

struct ExecutionState: public ChainStates
					 , public InvocationInfo
{
};

struct ExecutionContext: public ExecutionState
{
	virtual void					Randomize(uint8_t* fill, uint32_t size) = 0;

	// returns null if the state doesn't exist
	virtual uint8_t*				AllocateStateMemory(uint32_t dataSize) = 0;
	virtual void					DiscardStateMemory(uint8_t* state_memory) = 0;		// `state` must be allocated from AllocateState
	virtual void					CommitNewState(ContractInvokeId contract, uint8_t* state_memory) = 0;  // `state_memory` must be allocated from AllocateStateMemory, or be nullptr to empty the state
	virtual void					CommitNewState(ContractInvokeId contract, const ScopeKey* key, uint8_t* state_memory) = 0;

	virtual bool					EmitRelayToScope(ContractInvokeId cid, const ScopeKey* scope_key, OpCode opcode, const ConstData* args_serialized, uint32_t gas_redistribution_weight) = 0;
	virtual bool					EmitRelayToGlobal(ContractInvokeId cid, OpCode opcode, const ConstData* args_serialized, uint32_t gas_redistribution_weight) = 0;
	virtual bool					EmitRelayDeferred(ContractInvokeId cid, OpCode opcode, const ConstData* args_serialized, uint32_t gas_redistribution_weight) = 0; // deferred relay to current scope, which can be global/shard/address/uds
	virtual bool					EmitBroadcastToShards(ContractInvokeId cid, OpCode opcode, const ConstData* args_serialized, uint32_t gas_redistribution_weight) = 0; // global scope to all shards

	// Deploy an unnamed contract
	virtual ContractVersionId		DeployUnnamedContract(rvm::ContractVersionId deploy_initiator, uint64_t initiator_dappname, const rvm::DeployedContract* origin_deploy) = 0; // for global scope only

	// invoke a contract function (may cross-engine)
	virtual ExecuteResult			Invoke(uint32_t gas_limit, ContractInvokeId contract, OpCode opcode, const ConstData* args_serialized) = 0; // return pointer will be invalid after next call of `Invoke` or `SetReturnValue`						

	// set return value of current function being invoking
	virtual void					SetReturnValue(const ConstData* args_serialized) = 0;
	virtual uint8_t*				SetReturnValueClaim(uint32_t size_estimated) = 0;
	virtual void					SetReturnValueFinalize(uint32_t size_finalized) = 0;

	// native contracts
	virtual bool					NativeTokensDeposit(const ConstNativeToken* tokens, uint32_t count) = 0;
	virtual void					NativeTokensSupplyChange(const ConstNativeToken* tokens, uint32_t count) = 0;
};

struct BlockchainRuntime: public GlobalStates
{
	virtual ConstString				GetCoreDAppName() const = 0;
	virtual ContractRepository*		GetContractRepository() = 0;  // no need to release

	virtual void					DebugPrint(DebugMessageType type, const ConstString* string, const ExecutionState* ctx_opt = nullptr, const Contract* contract_opt = nullptr, int32_t line = -1) = 0;
};

//////////////////////////////////////////////////////////
// Interfaces implemented by RVM engine and invoked by BC
struct CompiledModules
{
	virtual EngineId				GetEngineId() const = 0;
	virtual ConstString				GetDAppName() const = 0;
	virtual uint32_t				GetCount() const = 0;
	virtual const Contract*			GetContract(uint32_t idx) const = 0;  // may return nullptr if `idx` contract is failed in compilation
	virtual ConstString				GetExternalDependencies() const = 0;   // list of contract names, "dapp_name.contract_name,dapp.contract..."
	virtual bool					ValidateDependency(const GlobalStates* chain_state) const = 0; // validate in case the chainstate for deployment is not the same when it is compiled
	virtual ConstData				GetDependencyData() const = 0;
	virtual bool					IsLinked() const = 0;
	virtual void					Release() = 0;
};

struct ExecutionUnit		// multi-instances are allowed, and may run in different threads
{
	virtual InvokeResult			Invoke(ExecutionContext* exec, uint32_t gas_limit, ContractInvokeId contract, OpCode opcode, const ConstData* args_serialized) = 0;
	virtual bool					DeployContracts(	ExecutionContext*			exec,
														CompiledModules*			linked, 
														const ContractVersionId*	target_cvids,
														DataBuffer**				deploy_stub,   // DataBuffer*[deploy_count]
														LogMessageOutput*			log_msg_output
									) = 0;
	virtual InvokeResult			InitializeContracts(ExecutionContext* exec, uint32_t gas_limit, CompiledModules* linked, const ConstData* ctor_args) = 0;
	virtual void					Release() = 0;
	virtual void					GetExceptionMessage(uint16_t except, StringStream* str) const = 0;
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
	virtual ConstString		GetContractName(const ConstData* source_code) = 0; // return the name of the contract without actual compilation
	virtual bool			Compile(	const ConstString*	dapp_name,
										uint32_t			contract_count, 
										const ConstData*	deploy_data_array,	// size = contract_count
										CompilationFlag		flag,
										CompiledModules**	compiled_output,
										LogMessageOutput*	log_msg_output
							) = 0;
	virtual bool			Recompile(	const ConstString*	dapp_name,
										const ConstData*	dependency_data,
										uint32_t			contract_count, 
										const ConstData*	deploy_data_array,	// size = contract_count
										CompilationFlag		flag,
										CompiledModules**	compiled_output,
										LogMessageOutput*	log_msg_output
							) = 0;
	// Build intermediate representation to platform specific runtime (PREDA: C++ to dll/so, involving extern gcc compiler) 
	virtual bool			Link(		CompiledModules*	compiled,
										LogMessageOutput*	log_msg_output
							) = 0;
	// Deploy the contracts into repository and ready for execution and cross-contract reference
	virtual void			CancelCurrentBuildingTask() = 0;  // abort in-progress Compile or Link task, async call

	virtual ExecutionUnit*	CreateExecuteUnit() = 0;
};

typedef rvm::RvmEngine* (*GetEngineFunctionType)(const char* config);
inline const char* GetEngineFunctionName(){ return "CreateEngine"; }

#pragma pack(pop)
} // namespace rvm
