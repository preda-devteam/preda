#pragma once
#include "vm_address.h"


namespace rvm
{
#pragma pack(push, 1)

namespace _details
{
static const uint32_t		SCOPE_SLOT_BITS = 4u;
static const uint32_t		SCOPE_KEYTYPE_BITS = 6u;
static const uint32_t		SCOPE_TYPE_BITS = 2u;

static const uint32_t		CONTRACT_SN_BITS = 14u;
static const uint32_t		CONTRACT_SN_BITMASK = (1u<<CONTRACT_SN_BITS)-1;
static const uint32_t		CONTRACT_ENTITY_DEFINITION_BITS = 15u;
static const uint32_t		CONTRACT_ENTITY_DEFINITION_BITMASK = ((1ull<<(CONTRACT_ENTITY_DEFINITION_BITS + CONTRACT_SN_BITS)) - 1);
static const uint32_t		CONTRACT_ENTITY_TYPE_BITS = 3u;
static const uint32_t		CONTRACT_SCOPE_BITS = SCOPE_SLOT_BITS + SCOPE_KEYTYPE_BITS + SCOPE_TYPE_BITS;
static const uint32_t		CONTRACT_ENGINE_BITS = 3u;
} // namespace _details

//					[Low Bits ---------------------------------------------------------------------- High Bits]
// ContractId:		[SN:14bits][                  Reserved:15bit                 ][Engine:3bits][DAppId:32bits]
// ContractScopeId: [SN:14bits][CET:3bits][              Scope:12bits            ][Engine:3bits][DAppId:32bits]
// InterfaceId:		[SN:14bits][CET:3bits][ InterfaceSlot:8bits ][ Reserved:4bit ][Engine:3bits][DAppId:32bits]

enum class		ContractId		:uint64_t{};	
static const	ContractId		ContractIdInvalid = (ContractId)0;	// RVM_CONTRACT_ID_INVALID
enum class		ContractScopeId	:uint64_t{};
enum class		InterfaceId		:uint64_t{};	
using			InterfaceSlot	=uint8_t;	// 12bit, starts from 0
static const	InterfaceSlot	InterfaceSlotInvalid = (InterfaceSlot)0xffU;

enum class		DAppId			:uint32_t{};
static const	DAppId			DAppIdInvalid = (DAppId)0;	// RVM_DAPP_ID_INVALID

using			BuildNum		=uint16_t;		// starts from 1
static const	BuildNum		BuildNumLatest = (BuildNum)0xffff;

enum class		TokenId			:uint32_t{};
static const	TokenId			TokenIdInvalid = (TokenId)0xffffffffU;
static const	TokenId			TokenIdCoreCoin = (TokenId)1U;

enum class		NonfungibleId	:uint64_t{};
static const	NonfungibleId	NonfungibleIdZero = (NonfungibleId)0;

enum class		OpCode			:uint16_t{};	// starts from 0
static const	OpCode			OpCodeInvalid = (OpCode)0xffffU;

static const	uint32_t		GlobalShard = 0xffffU;	// shard index of the global shard

enum class ContractEntityType // Entities defined/used in a contract, like contract itself, scopes and interfaces
{
	Contract = 0,
	Scope,
	Interface,
	_Bitmask = (1u<<_details::CONTRACT_ENTITY_TYPE_BITS)-1
};

enum class ScopeType
{
	Contract = 0,			// a contract scope defined, predefined or user-defined
	ScatteredMapOnGlobal,	// a scatter map variable defined on global scope
	ScatteredMapOnShard,
	ScatteredMapOnShard_CloneScale = ScatteredMapOnShard, // a scatter map variable defined on shard scope (states are cloned to branches when scale out, default behavior)
	ScatteredMapOnShard_SplitScale,	// a scatter map variable defined on shard scope (states are split to both branch when scale out)
	_Bitmask = (1u<<_details::SCOPE_TYPE_BITS)-1
};

enum class Scope: uint16_t  // 12bits: Low [SlotIndex:4bits][ScopeKeyType:6bits][ScopeType:2bits] High
{
	Global = 0,
	Shard,
	Address,
	Customized,	// user-defined scope
	// ... more user-defined scopes
	ScatteredMapOnGlobal			= (int)ScopeType::ScatteredMapOnGlobal<<10,
	// ... more scattered maps in global scope
	ScatteredMapOnShard				= (int)ScopeType::ScatteredMapOnShard<<10,
	ScatteredMapOnShard_CloneScale	= (int)ScopeType::ScatteredMapOnShard_CloneScale<<10,
	// ... more scattered maps in shard scope that dose clone scale
	ScatteredMapOnShard_SplitScale	= (int)ScopeType::ScatteredMapOnShard_SplitScale<<10,
	// ... more scattered maps in shard scope that dose scatter scale
	Neutral = (1u<<_details::CONTRACT_SCOPE_BITS)-1,

	_Bitmask = Neutral,
	_SlotCount = 1<<_details::SCOPE_SLOT_BITS	// in each <ScopeKeySize, ScopeType>, 16 variables/scopes can be defined
};

enum class ScopeDefinitionFlag: uint32_t
{
	Foreign		= 1<<0, // scope definition is imported from another contract
	HasState	= 1<<1,	// state members are defined in the scope
	HasFunction	= 1<<2, // member function defined in the scope
};

enum class EngineId: uint8_t
{
	Unassigned = 0,
	Core,			// built-in
	Native,			// C++ native
	PREDA_NATIVE,	// PREDA-to-C++ with gcc native execution, support global/shard scope
	PREDA_WASM,		// PREDA-to-C++ with WASM Virtual Machine (), support global/shard scope
	SOLIDITY_EVM,	// Solidity on Ethereum Virtual Machine (EvmOne), in Global Scope only
	Max,
	_Bitmask = (1u<<_details::CONTRACT_ENGINE_BITS)-1
};

namespace _details
{
static const uint8_t	ENGINE_BITMASK = (uint8_t)EngineId::_Bitmask;
static const uint32_t	CONTRACT_ENGINE_SHIFT = CONTRACT_SN_BITS + CONTRACT_ENTITY_DEFINITION_BITS;

static const uint16_t	SCOPE_BITMASK = (uint16_t)Scope::_Bitmask;
static const uint32_t	CONTRACT_SCOPE_SHIFT = CONTRACT_SN_BITS + CONTRACT_ENTITY_TYPE_BITS;

static const uint32_t	CONTRACT_DAPP_SHIFT = 32;
static const uint64_t	CONTRACT_ID_DROP_SCOPE_BITS = ~(((uint64_t)SCOPE_BITMASK)<<CONTRACT_SCOPE_SHIFT);
static const uint64_t	CONTRACT_ID_NEUTRAL_SCOPE_BITS = (((uint64_t)Scope::Neutral)<<CONTRACT_SCOPE_SHIFT);

inline constexpr ContractScopeId	CONTRACT_SET_SCOPE(ContractId x, Scope scope){ return (ContractScopeId)(((uint64_t)x&CONTRACT_ID_DROP_SCOPE_BITS) | (((uint64_t)scope)<<CONTRACT_SCOPE_SHIFT)); }
inline constexpr ContractId			CONTRACT_UNSET_SCOPE(ContractScopeId x){ return (ContractId)((uint64_t)x&CONTRACT_ID_DROP_SCOPE_BITS); }
inline constexpr Scope				CONTRACT_SCOPE(ContractScopeId x){ return ((Scope)(((uint64_t)x>>CONTRACT_SCOPE_SHIFT) & SCOPE_BITMASK)); }
inline constexpr DAppId				CONTRACT_DAPPID(ContractScopeId x){ return ((DAppId)((uint64_t)x>>CONTRACT_DAPP_SHIFT)); }
inline constexpr DAppId				CONTRACT_DAPPID(ContractId x){ return ((DAppId)((uint64_t)x>>CONTRACT_DAPP_SHIFT)); }
inline constexpr uint32_t			CONTRACT_SERIALNUM(ContractScopeId x){ return ((uint32_t)x&CONTRACT_SN_BITMASK); }
inline constexpr uint32_t			CONTRACT_SERIALNUM(ContractId x){ return ((uint32_t)x&CONTRACT_SN_BITMASK); }
inline constexpr EngineId			CONTRACT_ENGINE(ContractScopeId x){ return ((EngineId)(((uint64_t)x>>CONTRACT_ENGINE_SHIFT)&ENGINE_BITMASK)); }
inline constexpr EngineId			CONTRACT_ENGINE(ContractId x){ return ((EngineId)(((uint64_t)x>>CONTRACT_ENGINE_SHIFT)&ENGINE_BITMASK)); }
inline constexpr ContractId			CONTRACT_ID_MAKE(uint32_t sn, DAppId dappid, EngineId engine)
									{	return	(ContractId)
												(	(sn&CONTRACT_SN_BITMASK) |
													(((uint64_t)engine)&ENGINE_BITMASK)<<CONTRACT_ENGINE_SHIFT |
													(((uint64_t)dappid)<<CONTRACT_DAPP_SHIFT)
												);
									}
inline constexpr ContractScopeId	CONTRACT_SCOPED_MAKE(uint32_t sn, Scope scope, DAppId dappid, EngineId engine)
									{	return (ContractScopeId)((uint64_t)CONTRACT_ID_MAKE(sn, dappid, engine) | ((uint64_t)scope<<CONTRACT_SCOPE_SHIFT));
									}
inline constexpr InterfaceId		INTERFACE_ID_MAKE(InterfaceSlot slot, ContractId cid)
									{	return (InterfaceId)( ((uint64_t)cid) | ((uint64_t)ContractEntityType::Interface<<CONTRACT_SN_BITS) | ((uint64_t)slot<<(CONTRACT_SN_BITS+CONTRACT_ENTITY_TYPE_BITS)) );
									}
inline constexpr ContractId			INTERFACE_CONTRACT(InterfaceId iid){ return (ContractId)( (uint64_t)iid & (~CONTRACT_ENTITY_DEFINITION_BITMASK) ); }
inline constexpr bool				SCOPE_IS_SCATTERED_MAP(Scope x)
									{	return (int)x<(int)Scope::Neutral && (int)x>=(int)Scope::ScatteredMapOnGlobal;
									}
inline constexpr bool				SCOPE_IS_ENUMERABLE(Scope x){ return (int)x & ((int)ScopeKeySize::IsEnumerable)<<4; }
inline constexpr ScopeType			SCOPE_TYPE(Scope x)
									{	if(x == Scope::Neutral)return ScopeType::Contract;
										return (ScopeType)((int)x>>8);
									}
inline constexpr bool				SCOPE_IS_CLONESCALE(Scope x){ return SCOPE_TYPE(x) == ScopeType::ScatteredMapOnShard_CloneScale; }
inline constexpr Scope				SCOPE_MAKE(ScopeType t, ScopeKeySize kst = ScopeKeySize::Default, int slot_idx = 0){ return (Scope)(((int)t<<8)|((int)kst<<4)|slot_idx); }
inline constexpr ScopeKeySize		SCOPE_KEYSIZETYPE(Scope x){ return (ScopeKeySize)(((int)x>>4) & (int)ScopeKeySize::Bitmask); }
inline constexpr int				SCOPE_KEYSIZE(Scope x) // -1: n/a, 0:varying, or the #bytes of the fixed size
									{	auto t = SCOPE_KEYSIZETYPE(x);
										if(t == ScopeKeySize::Default && !SCOPE_IS_SCATTERED_MAP(x) && (int)x<(int)Scope::Address)return -1;
										return SCOPEKEY_SIZE(t);
									}
inline constexpr bool				SCOPE_VERIFY_KEY_SIZE(Scope x, int size)
									{	int expected = SCOPE_KEYSIZE(x);
										if(expected == -1)return false;
										if(expected == 0)return size >= 0;
										return expected == size;
									}

/////////////////////////////////////////////////////////////
// NONFUNGIBLE_ID
// [SC:4b][ShardIdx:12b][NonFungibleId:48b]
// ((SC-1)*2) = bitwidth for piece_index
inline constexpr uint64_t			NONFUNGIBLE_ID_PIECEIDX_BITMASK(NonfungibleId nfid){ return (~(0xffffffffffffffffULL<<(((((uint64_t)nfid)>>60)-1)*2))); }
inline constexpr uint64_t			NONFUNGIBLE_ID_PIECE_MAXCOUNT(NonfungibleId nfid){ return (NONFUNGIBLE_ID_PIECEIDX_BITMASK(nfid)+1); }
inline constexpr uint64_t			NONFUNGIBLE_ID_PIECEIDX_BITS(uint64_t piece_count){ return (piece_count>1?(((32 - rt::LeadingZeroBits<uint64_t>(piece_count-1)) + 1)&(~1ULL)):0); }
inline constexpr uint64_t			NONFUNGIBLE_ID_PIECEIDX_SPACE(uint64_t piece_count){ return	(1ULL<<NONFUNGIBLE_ID_PIECEIDX_BITS(piece_count)); }
inline constexpr uint64_t			NONFUNGIBLE_PIECEIDX(NonfungibleId nfid){ return (NONFUNGIBLE_ID_PIECEIDX_BITMASK(nfid)&((uint64_t)nfid)); }
inline constexpr uint64_t			NONFUNGIBLE_ID_BASE(NonfungibleId nfid){ return ((~NONFUNGIBLE_ID_PIECEIDX_BITMASK(nfid))&((uint64_t)nfid)); }
inline constexpr uint64_t			NONFUNGIBLE_ID_MAKE(NonfungibleId nfid, uint64_t piece_id){ return (NONFUNGIBLE_ID_BASE(nfid) | ((piece_id)&NONFUNGIBLE_ID_PIECEIDX_BITMASK(nfid))); }

} // namespace _details

enum class CompilationFlag: uint64_t
{
	None				= 0,
	DisableDebugPrint	= 1<<0,
	DisableGlobalScope	= 1<<1,
};

struct HashValue
{	
	uint8_t		_[RVM_HASH_SIZE];
};
typedef HashValue BlobAddress;

struct DeploymentId
{	
	uint8_t		_[20];
};
struct ContractDID: public DeploymentId {}; //ContractDeploymentIdentifier
struct InterfaceDID: public DeploymentId {}; //InterfaceDeploymentIdentifier

//struct Blob
//{
//	uint8_t		Mime;
//	uint16_t	DataSizeLow;
//	uint8_t		DataSizeHigh;
//	BlobAddress	DataHash;
//};

enum class ScaleOutMode: int
{
	None			= 0,	// not scaling
	BaseBranch		= 1,	// (TXNBLK) first block of a scaled branch (base), shard_index don't change
	UpBranch		= 2,	// (TXNBLK) first block of a scaled branch (up), shard_index is shard_index + shard_count_before_scaling
	ScalingNext		= 4,	// (MSTBLK) last block before next scaling
};

struct StringStream;
struct DataBuffer;
struct ExecutionContext;

enum class DebugMessageType: uint32_t
{
	Verbose = 0,	// Gray
	Informational,	// White
	Highlight,		// Green
	Warning,		// Yellow
	Error			// Error
};

enum class NativeTypeId : uint8_t
{
	Invalid = 0,
	boolean,
	int8,
	int16,	
	int32,	
	int64,	
	uint8,	
	uint16,	
	uint32,
	uint64,
	Float256	 = 16,
	Float512,
	Float1024,
	Float2048,
	BigNum		 = 32,
	Timestamp, // 48-bit unsigned
	String,
	HashValue,
	Address,
	Coins,
	Blob,
};

enum class DeployError : uint8_t
{
	NoError							 = 0,
	ContractIdScopeBitNonWildcard	 = 1,
	ContractAlreadyExists			 = 2,
	TranspileError					 = 3,
	GccCompileBuildError			 = 6,

	SystemErrorBegin				 = 128,
	TranspilerNotAvailable			 = 128,
	WriteDiskError					 = 129,
	GccLaunchError					 = 130,
	RegisterAssetError				 = 131,
};

enum class FunctionFlag : uint32_t
{
	InvokeByNormalTransaction		= (1 << 6),
	InvokeByRelayTransaction		= (1 << 7),
	InvokeBySystem					= (1 << 8),
	InvokeByForeignDApp				= (1 << 9),
	InvokeBySchedule				= (1 << 10),

	StateImmutable					= (1 << 16),
	EmitRelayInAddressScope			= (1 << 17),
	EmitRelayInShardScope			= (1 << 18),
	EmitRelayInGlobalScope			= (1 << 19),
	GlobalStateDependency			= (1 << 20),
};

enum class InvokeContextType : uint8_t
{					// TxnGenerationMode			Desc
	Normal = 0,		// TGM_USER_SIGNED				Gas will be charged, has signers available, no orig_exec_idx  (Txn issued by user)
	RelayInbound,	// TGM_RELAY					No gas payment required, has orig_exec_idx, no signers  (Txn issued by relay@ statement, cross-shard execution)
	RelayIntra,		// TGM_RELAY					No gas payment required, has orig_exec_idx, no signers, no txid  (Txn issued by relay@ statement, intra-shard execution)
	Scheduled,		// TGM_PERIODIC_SYSTEM			No gas payment required, no orig_exec_idx, no signer
					// TGM_RELAY,TGM_DEFERRED,TGM_GLOBAL_TO_SHARD  No gas payment required, has orig_exec_idx, no signer
					// TGM_PERIODIC_USER			Gas will be charged, no orig_exec_idx, no signer
	System			// n/a (deploy,scale_out)		Gas ?????
};

enum class InvokeErrorCode : uint8_t
{
	Success = 0, // Execution success, otherwise any committed states and generated relay txns will be discarded.
	Unspecified, // error coode is not specified
	InsufficientFunds, // insufficient funds for gas payment.
	InsufficientGasRequired, // Gas supplied < minimum requirement of the gas, which is determined without execution
	RunOutOfGas, // Gas runs out before execution of the the contract function is completed
	AssertionFailed, // explicit assertion defined in contract code
	ExceptionThrown, // exception trigger implicitly like divide-by-zero, thrown from underlying libraries
	ExecutionEngineUnavailable,
	ContractUnavailable,
	ContractFunctionUnavailable,
	ContractFunctionDisallowed,
	InvalidFunctionArgments,
	// Blue Screen Error
	BlueScreenErrorBegin = 200,
	InternalError = BlueScreenErrorBegin,
	OutOfMemory,
	LoadStateFailure,
	SaveStateFailure,
};

enum class ContractFlag : uint16_t  // bitwise defined
{
	HasShardScaleOut		= (1<<6),
	HasShardDeploy			= (1<<7),
	HasGlobalDeploy			= (1<<8),

	DeployFinalized			= (1<<15)
};

enum class LogMessageType : uint8_t
{
	Error = 0,
	Warning,
	Information,
};

struct ConstString
{
	const char*		StrPtr;
	uint32_t		Length;
	auto Str() const { return rt::String_Ref(StrPtr, Length); }
};

struct ConstData
{
	const uint8_t*	DataPtr;
	uint32_t		DataSize;
};

struct ConstStateData
{
	const uint8_t*	DataPtr;
	uint32_t		DataSize;
	BuildNum		Version;
};

struct InvokeResult
{
	uint16_t		SubCodeLow;
	uint8_t			SubCodeHigh;
	InvokeErrorCode	Code;
	uint32_t		GasBurnt;
};

struct ExecuteResult: public InvokeResult
{
	ConstData		ReturnValue;
};

#pragma pack(pop)
} // namespace rvm

STRINGIFY_ENUM_BEGIN(EngineId, rvm)
	STRINGIFY_ENUM(Core)
	STRINGIFY_ENUM(Native)
	STRINGIFY_ENUM(PREDA_NATIVE)
	STRINGIFY_ENUM(PREDA_WASM)
	STRINGIFY_ENUM(SOLIDITY_EVM)
STRINGIFY_ENUM_END(EngineId, rvm)

STRINGIFY_ENUM_BEGIN(ContractFlag, rvm)
	STRINGIFY_ENUM_BIT(HasShardScaleOut)
	STRINGIFY_ENUM_BIT(HasShardDeploy)
	STRINGIFY_ENUM_BIT(HasGlobalDeploy)
	STRINGIFY_ENUM_BIT(DeployFinalized)
STRINGIFY_ENUM_END(ContractFlag, rvm)

STRINGIFY_ENUM_BEGIN(FunctionFlag, rvm)
	STRINGIFY_ENUM_BIT(InvokeByNormalTransaction)
	STRINGIFY_ENUM_BIT(InvokeByRelayTransaction)
	STRINGIFY_ENUM_BIT(InvokeByForeignDApp)
	STRINGIFY_ENUM_BIT(InvokeBySystem)
	STRINGIFY_ENUM_BIT(InvokeBySchedule)
	STRINGIFY_ENUM_BIT(StateImmutable)
	STRINGIFY_ENUM_BIT(EmitRelayInAddressScope)
	STRINGIFY_ENUM_BIT(EmitRelayInShardScope)
	STRINGIFY_ENUM_BIT(EmitRelayInGlobalScope)
	STRINGIFY_ENUM_BIT(GlobalStateDependency)
STRINGIFY_ENUM_END(FunctionFlag, rvm)

STRINGIFY_ENUM_BEGIN(InvokeErrorCode, rvm)
	STRINGIFY_ENUM(Success)
	STRINGIFY_ENUM(Unspecified)
	STRINGIFY_ENUM(InsufficientFunds)
	STRINGIFY_ENUM(InsufficientGasRequired)
	STRINGIFY_ENUM(RunOutOfGas)
	STRINGIFY_ENUM(AssertionFailed)
	STRINGIFY_ENUM(ExceptionThrown)
	STRINGIFY_ENUM(ExecutionEngineUnavailable)
	STRINGIFY_ENUM(ContractUnavailable)
	STRINGIFY_ENUM(ContractFunctionUnavailable)
	STRINGIFY_ENUM(ContractFunctionDisallowed)
	STRINGIFY_ENUM(InvalidFunctionArgments)
	STRINGIFY_ENUM(InternalError)
	STRINGIFY_ENUM(OutOfMemory)
	STRINGIFY_ENUM(LoadStateFailure)
	STRINGIFY_ENUM(SaveStateFailure)
STRINGIFY_ENUM_END(InvokeErrorCode, rvm)

STRINGIFY_ENUM_BEGIN(CompilationFlag, rvm)
	STRINGIFY_ENUM_BIT(DisableDebugPrint)
	STRINGIFY_ENUM_BIT(DisableGlobalScope)
STRINGIFY_ENUM_END(CompilationFlag, rvm)

STRINGIFY_ENUM_BEGIN(InvokeContextType, rvm)
	STRINGIFY_ENUM(Normal)
	STRINGIFY_ENUM(RelayInbound)
	STRINGIFY_ENUM(RelayIntra)
	STRINGIFY_ENUM(Scheduled)
	STRINGIFY_ENUM(System)
STRINGIFY_ENUM_END(InvokeContextType, rvm)

STRINGIFY_ENUM_BEGIN(ScopeType, rvm)
	STRINGIFY_ENUM(Contract)
	STRINGIFY_ENUM(ScatteredMapOnGlobal)
	STRINGIFY_ENUM(ScatteredMapOnShard)
	STRINGIFY_ENUM(ScatteredMapOnShard_SplitScale)
STRINGIFY_ENUM_END(ScopeType, rvm)

STRINGIFY_ENUM_BEGIN(ScopeKeySize, rvm)
	STRINGIFY_ENUM(Address)
	STRINGIFY_ENUM(UInt16)
	STRINGIFY_ENUM(UInt32)
	STRINGIFY_ENUM(UInt64)
	STRINGIFY_ENUM(UInt160)
	STRINGIFY_ENUM(UInt256)
	STRINGIFY_ENUM(UInt512)
	STRINGIFY_ENUM(VaryingSize)
	STRINGIFY_ENUM(AddressEnumerable)
	STRINGIFY_ENUM(UInt16Enumerable)
	STRINGIFY_ENUM(UInt32Enumerable)
	STRINGIFY_ENUM(UInt64Enumerable)
	STRINGIFY_ENUM(UInt160Enumerable)
	STRINGIFY_ENUM(UInt256Enumerable)
	STRINGIFY_ENUM(UInt512Enumerable)
STRINGIFY_ENUM_END(ScopeKeySize, rvm)

STRINGIFY_ENUM_BEGIN(ScopeDefinitionFlag, rvm)
	STRINGIFY_ENUM_BIT(Foreign)
	STRINGIFY_ENUM_BIT(HasState)
	STRINGIFY_ENUM_BIT(HasFunction)
STRINGIFY_ENUM_END(ScopeDefinitionFlag, rvm)
