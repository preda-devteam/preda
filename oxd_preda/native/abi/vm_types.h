#pragma once
#include "vm_address.h"


namespace rvm
{
#pragma pack(push, 1)

enum class		DAppId			:uint32_t{};
static const	DAppId			DAppIdInvalid	= (DAppId)0;	// RVM_DAPP_ID_INVALID
static const	DAppId			DAppIdCore		= (DAppId)1;
static const	DAppId			DAppIdMax		= (DAppId)0xfffffffu;

using			BuildNum		=uint8_t;		// starts from 1
static const	BuildNum		BuildNumInit	= (BuildNum)1u;
static const	BuildNum		BuildNumLatest	= (BuildNum)0xffu;
static const	BuildNum		BuildNumMax		= (BuildNum)0xfeu;
static const	BuildNum		BuildNumInvalid = (BuildNum)0u;

enum class		OpCode			:uint8_t{};		// starts from 0
static const	OpCode			OpCodeInvalid	= (OpCode)0xffU;

static const	uint16_t		ContractSerialNumMax = 0xfff;  // 12b
static const	uint16_t		ContractSerialNumNamedMax = 0x3ff; // 1024
static const	uint16_t		ContractSerialNumUnnamedBase = 0x400; // 1024

static const	uint32_t		DAppNameSizeMax = 8;
static const	uint32_t		DAppNameSizeMin = 4;
static const	uint32_t		DAppContractNameSizeMax = 160/8 - 2;  // max size for dapp_name.contract_name
static const	uint32_t		FunctionNameSizeMax = 32;
static const	uint32_t		ScopeNameSizeMax = 32;
static const	uint32_t		TokenNameSizeMax = 8;
static const	uint32_t		TokenNameSizeMin = 3;

enum class EngineId: uint8_t // 3b
{
	Unassigned = 0,
	Core,			// built-in
	Native,			// C++ native
	PREDA_NATIVE,	// PREDA-to-C++ with gcc native execution, support global/shard scope
	PREDA_WASM,		// PREDA-to-C++ with WASM Virtual Machine (), support global/shard scope
	SOLIDITY_EVM,	// Solidity on Ethereum Virtual Machine (EvmOne), in Global Scope only
	Max,
	Invalid = 0xfu,
	_Bitmask = 0xfu
};

enum class ScopeType : uint8_t
{
	Contract = 0,			// a contract scope defined, predefined or user-defined
	ScatteredMapOnGlobal,	// a scatter map variable defined on global scope
	ScatteredMapOnShard,
	ScatteredMapOnShard_CloneScale = ScatteredMapOnShard, // a scatter map variable defined on shard scope (states are cloned to branches when scale out, default behavior)
	ScatteredMapOnShard_SplitScale,	// a scatter map variable defined on shard scope (states are split to both branch when scale out)
	_Bitmask = 0x3u
};

namespace _details
{
static const uint32_t		SCOPE_SLOT_BITS			= 4u;
static const uint32_t		SCOPE_KEYTYPESIZE_BITS	= 6u;
static const uint32_t		SCOPE_TYPE_BITS			= 2u;
static const uint32_t		SCOPE_KTSSLT_BITS		= SCOPE_SLOT_BITS + SCOPE_KEYTYPESIZE_BITS;
static const uint32_t		SCOPE_BITS				= SCOPE_KTSSLT_BITS + SCOPE_TYPE_BITS;
}

enum class Scope: uint16_t // 12bits: Low [SlotIndex:4bits][ScopeKeySize:6bits][ScopeType:2bits] High
{	// three special scopes, which occupies slot #0,1,2 of address-typed scope in contract (ScopeType::Contract)
	Global	= 0,
	Shard	= 1,
	Address	= 2,
	ScatteredMapOnGlobal			= ((int)ScopeType::ScatteredMapOnGlobal<<_details::SCOPE_KTSSLT_BITS),
	ScatteredMapOnShard				= ((int)ScopeType::ScatteredMapOnShard<<_details::SCOPE_KTSSLT_BITS),
	ScatteredMapOnShard_CloneScale	= ((int)ScopeType::ScatteredMapOnShard_CloneScale<<_details::SCOPE_KTSSLT_BITS),
	ScatteredMapOnShard_SplitScale	= ((int)ScopeType::ScatteredMapOnShard_SplitScale<<_details::SCOPE_KTSSLT_BITS),
	_Bitmask = (1u<<_details::SCOPE_BITS)-1
};
static const Scope ScopeInvalid = (Scope)((1u<<_details::SCOPE_BITS)-1);

inline constexpr ScopeType			SCOPE_TYPE(Scope x){ return (ScopeType)(((int)x>>_details::SCOPE_KTSSLT_BITS)&(int)ScopeType::_Bitmask); }
inline constexpr uint8_t			SCOPE_SLOT(Scope x){ return (int)x>=3?(int)x&((1<<_details::SCOPE_SLOT_BITS)-1):0; }
inline constexpr ScopeKeySize		SCOPE_KEYSIZETYPE(Scope x){ return (int)x>=2?(ScopeKeySize)(((int)x>>_details::SCOPE_SLOT_BITS) & (int)ScopeKeySize::Bitmask):ScopeKeySizeInvalid; }

inline constexpr bool				SCOPE_IS_SCATTERED_MAP(Scope x){ return (int)SCOPE_TYPE(x)>=(int)ScopeType::ScatteredMapOnGlobal;	}
inline constexpr bool				SCOPE_IS_ENUMERABLE(Scope x){ return (int)SCOPE_KEYSIZETYPE(x) >= (int)ScopeKeySize::IsEnumerable; }
inline constexpr bool				SCOPE_IS_CLONESCALE(Scope x){ return SCOPE_TYPE(x) == ScopeType::ScatteredMapOnShard_CloneScale; }
inline constexpr bool				SCOPE_IS_SPLITSCALE(Scope x){ return SCOPE_TYPE(x) == ScopeType::ScatteredMapOnShard_SplitScale; }
inline constexpr Scope				SCOPE_MAKE(ScopeType t, ScopeKeySize kst, int slot_idx = 0)
									{	return ((int)t || (int)kst || slot_idx>=2)?
													(Scope)(((int)t<<_details::SCOPE_KTSSLT_BITS)|((int)kst<<_details::SCOPE_SLOT_BITS)|slot_idx)
													:ScopeInvalid;
									}
inline constexpr int				SCOPE_KEYSIZE(Scope x) // -1: n/a, or the #bytes of the fixed size
									{	if((int)x<2)return -1;
										return SCOPEKEY_SIZE(SCOPE_KEYSIZETYPE(x));
									}
inline constexpr bool				SCOPE_VERIFY_KEY_SIZE(Scope x, int size)
									{	int expected = SCOPE_KEYSIZE(x);
										if(expected == -1)return false;
										return expected == size;
									}

//					   [Low -------------------------------------------------- 64b ------------------------------------------------------------ High]
// ContractId:         [----------------- 20b ----------------][     SerialNum:12b    ][ 4b ][                      DAppId:28b                      ]
// ContractVersionId:  [   Build:8b   ][--------- 12b --------][     SerialNum:12b    ][ 4b ][                      DAppId:28b                      ]
// ContractScopeId:    [   Build:8b   ][       Scope:12b      ][     SerialNum:12b    ][ 4b ][                      DAppId:28b                      ]
// InterfaceId:        [----- 8b -----][   InterfaceSlot:12b  ][     SerialNum:12b    ][ 4b ][                      DAppId:28b                      ]
//                                                                                    EngineId

namespace _details
{
static const uint32_t		CONTRACT_BUILD_BITS		= 8u;
static const uint32_t		CONTRACT_SCOPE_BITS		= 12u;
static const uint32_t		CONTRACT_SERIALNUM_BITS	= 12u;
static const uint32_t		CONTRACT_ENGINE_BITS	= 4u;
static const uint32_t		CONTRACT_DAPP_BITS		= 28u;
} // namespace _details

enum class		ContractId			:uint64_t{}; // CID
enum class		ContractVersionId	:uint64_t{}; // CID + BuildNum
enum class		ContractScopeId		:uint64_t{}; // CID + Scope
enum class		ContractInvokeId	:uint64_t{}; // CID + Scope + BuildNum, which is ready for invocation
static const	ContractId			ContractIdInvalid = (ContractId)0;	// CID
static const	ContractVersionId	ContractVersionIdInvalid = (ContractVersionId)0;
static const	ContractScopeId		ContractScopeIdInvalid = (ContractScopeId)0;
static const	ContractInvokeId	ContractInvokeIdInvalid = (ContractInvokeId)0;

enum class		InterfaceId			:uint64_t{};	
static const	InterfaceId			InterfaceIdInvalid = (InterfaceId)0;
using			InterfaceSlot		=uint16_t;	// 12bit, starts from 0
static const	InterfaceSlot		InterfaceSlotInvalid = (InterfaceSlot)0xfffU;
static const	InterfaceSlot		InterfaceSlotMax = (InterfaceSlot)0xffeU;

namespace _details
{
static const uint32_t	SERIALNUM_BITMASK			= (1u<<CONTRACT_SERIALNUM_BITS)-1;
static const uint32_t	ENGINE_BITMASK				= (1u<<CONTRACT_ENGINE_BITS)-1;
static const uint32_t	SCOPE_BITMASK				= (1u<<SCOPE_BITS)-1;
static const uint32_t	BUILD_BITMASK				= (1u<<CONTRACT_BUILD_BITS)-1;
static const uint32_t	DAPP_BITMASK				= (1u<<CONTRACT_DAPP_BITS)-1;

static const uint32_t	CONTRACT_BUILD_BITSHIFT		= 0;
static const uint32_t	CONTRACT_SCOPE_BITSHIFT		= CONTRACT_BUILD_BITSHIFT + CONTRACT_BUILD_BITS;
static const uint32_t	CONTRACT_SERIALNUM_BITSHIFT	= CONTRACT_SCOPE_BITSHIFT + CONTRACT_SCOPE_BITS;
static const uint32_t	CONTRACT_ENGINE_BITSHIFT	= CONTRACT_SERIALNUM_BITSHIFT + CONTRACT_SERIALNUM_BITS;
static const uint32_t	CONTRACT_DAPP_BITSHIFT		= CONTRACT_ENGINE_BITSHIFT + CONTRACT_ENGINE_BITS;

static const uint64_t	CONTRACT_DROP_SCOPE_BITMASK			= ~(((uint64_t)SCOPE_BITMASK)<<CONTRACT_SCOPE_BITSHIFT);	 // reset scope
static const uint64_t	CONTRACT_DROP_BUILD_BITMASK			= ~(((uint64_t)BUILD_BITMASK)<<CONTRACT_BUILD_BITSHIFT);	 // reset build
static const uint64_t	CONTRACT_DROP_BUILD_SCOPE_BITMASK	= CONTRACT_DROP_SCOPE_BITMASK & CONTRACT_DROP_BUILD_BITMASK; // reset scope/build
}

inline constexpr ContractScopeId	CONTRACT_SET_SCOPE(ContractId x, Scope scope){ return (ContractScopeId)(((uint64_t)x&_details::CONTRACT_DROP_SCOPE_BITMASK) | (((uint64_t)scope)<<_details::CONTRACT_SCOPE_BITSHIFT)); }
inline constexpr ContractInvokeId	CONTRACT_SET_SCOPE(ContractVersionId x, Scope scope){ return (ContractInvokeId)CONTRACT_SET_SCOPE((ContractId)x, scope); }
inline constexpr ContractVersionId	CONTRACT_SET_BUILD(ContractId x, BuildNum ver){ return (ContractVersionId)(((uint64_t)x&_details::CONTRACT_DROP_BUILD_BITMASK) | (((uint64_t)ver)<<_details::CONTRACT_BUILD_BITSHIFT)); }
inline constexpr ContractInvokeId	CONTRACT_SET_BUILD(ContractScopeId x, BuildNum ver){ return (ContractInvokeId)CONTRACT_SET_BUILD((ContractId)x, ver); }
inline constexpr ContractInvokeId	CONTRACT_SET_SCOPE_BUILD(ContractId x, Scope scope, BuildNum ver)
									{	return	(ContractInvokeId)(((uint64_t)x&_details::CONTRACT_DROP_BUILD_SCOPE_BITMASK) | 
												(((uint64_t)scope)<<_details::CONTRACT_SCOPE_BITSHIFT) | 
												(((uint64_t)ver)<<_details::CONTRACT_BUILD_BITSHIFT));
									}
inline constexpr ContractVersionId	CONTRACT_UNSET_SCOPE(ContractInvokeId x){ return (ContractVersionId)((uint64_t)x&_details::CONTRACT_DROP_SCOPE_BITMASK); }
inline constexpr ContractId			CONTRACT_UNSET_SCOPE(ContractScopeId x){ return (ContractId)((uint64_t)x&_details::CONTRACT_DROP_SCOPE_BITMASK); }
inline constexpr ContractScopeId	CONTRACT_UNSET_BUILD(ContractInvokeId x){ return (ContractScopeId)((uint64_t)x&_details::CONTRACT_DROP_BUILD_BITMASK); }
inline constexpr ContractId			CONTRACT_UNSET_BUILD(ContractVersionId x){ return (ContractId)((uint64_t)x&_details::CONTRACT_DROP_BUILD_BITMASK); }
inline constexpr ContractId			CONTRACT_UNSET_SCOPE_BUILD(ContractInvokeId x){ return (ContractId)((uint64_t)x&_details::CONTRACT_DROP_BUILD_SCOPE_BITMASK); }

inline constexpr ContractId			CONTRACT_ID_MAKE(uint32_t sn, DAppId dapp, EngineId engine)
									{	return	(ContractId)
												(	(sn&_details::SERIALNUM_BITMASK)<<_details::CONTRACT_SERIALNUM_BITSHIFT |
													(((uint64_t)engine)&_details::ENGINE_BITMASK)<<_details::CONTRACT_ENGINE_BITSHIFT |
													(((uint64_t)dapp)<<_details::CONTRACT_DAPP_BITSHIFT)
												);
									}
inline constexpr ContractVersionId	CONTRACT_ID_MAKE(uint32_t sn, DAppId dapp, EngineId engine, BuildNum ver)
									{	return	(ContractVersionId)
												(	(uint64_t)CONTRACT_ID_MAKE(sn, dapp, engine) | 
													(((uint64_t)ver)<<_details::CONTRACT_BUILD_BITSHIFT)
												);
									}
inline constexpr ContractScopeId	CONTRACT_ID_MAKE(uint32_t sn, DAppId dapp, EngineId engine, Scope scope)
									{	return	(ContractScopeId)
												(	(uint64_t)CONTRACT_ID_MAKE(sn, dapp, engine) | 
													(((uint64_t)scope)<<_details::CONTRACT_SCOPE_BITSHIFT)
												);
									}
inline constexpr ContractInvokeId	CONTRACT_ID_MAKE(uint32_t sn, DAppId dapp, EngineId engine, BuildNum ver, Scope scope)
									{	return	(ContractInvokeId)
												(	(uint64_t)CONTRACT_ID_MAKE(sn, dapp, engine, ver) | 
													(((uint64_t)scope)<<_details::CONTRACT_SCOPE_BITSHIFT)
												);
									}
inline constexpr InterfaceId		INTERFACE_ID_MAKE(uint32_t sn, DAppId dapp, EngineId engine, InterfaceSlot slot)
									{	return (InterfaceId)(sn | ((uint64_t)dapp<<_details::CONTRACT_DAPP_BITSHIFT) | ((uint64_t)slot<<_details::CONTRACT_SCOPE_BITSHIFT) | ((uint64_t)engine<<_details::CONTRACT_ENGINE_BITSHIFT));
									}

template<typename T> inline constexpr bool		CONTRACT_IS_UNNAMED(T x){ return ((uint32_t)x&_details::SERIALNUM_BITMASK) >= ContractSerialNumUnnamedBase; }
template<typename T> inline constexpr Scope		CONTRACT_SCOPE(T x){ return ((Scope)(((uint64_t)x>>_details::CONTRACT_SCOPE_BITSHIFT) & _details::SCOPE_BITMASK)); }
template<typename T> inline constexpr ScopeType	CONTRACT_SCOPE_TYPE(T x){ return SCOPE_TYPE(CONTRACT_SCOPE(x)); }
template<typename T> inline constexpr auto		CONTRACT_SCOPE_BASEKEYSIZE(T x){ return (ScopeKeySize)((int)SCOPE_KEYSIZETYPE(CONTRACT_SCOPE(x))&(int)ScopeKeySize::BaseTypeBitmask); }
template<typename T> inline constexpr DAppId	CONTRACT_DAPP(T x){ return ((DAppId)((uint64_t)x>>_details::CONTRACT_DAPP_BITSHIFT)); }
template<typename T> inline constexpr uint16_t	CONTRACT_SERIALNUM(T x){ return ((uint32_t)x>>_details::CONTRACT_SERIALNUM_BITSHIFT)&_details::SERIALNUM_BITMASK; }
template<typename T> inline constexpr BuildNum	CONTRACT_BUILD(T x){ return ((BuildNum)((uint64_t)x>>_details::CONTRACT_BUILD_BITSHIFT)&_details::BUILD_BITMASK); }
template<typename T> inline constexpr EngineId	CONTRACT_ENGINE(T x){ return ((EngineId)(((uint64_t)x>>_details::CONTRACT_ENGINE_BITSHIFT)&_details::ENGINE_BITMASK)); }
template<typename T> inline constexpr bool		CONTRACT_ON_GLOBAL(T x){ return CONTRACT_SCOPE(x) == Scope::Global || SCOPE_TYPE(CONTRACT_SCOPE(x)) == ScopeType::ScatteredMapOnGlobal; }
template<typename T> inline constexpr bool		CONTRACT_ON_SHARDED_SCOPE(T x){ return (int)CONTRACT_SCOPE(x) >= (int)Scope::Address && (int)CONTRACT_SCOPE(x) < (int)Scope::ScatteredMapOnGlobal; }
template<typename T> inline constexpr bool		CONTRACT_SCOPE_IS_ENUMERABLE(T x){ return SCOPE_IS_ENUMERABLE(CONTRACT_SCOPE(x)); }

enum class			TokenId		:uint64_t{};
inline constexpr	TokenId		TokenIdMake(char x0, char x1, char x2, char x3 = 0){ return (TokenId)(x0|(x1<<8)|(x2<<16)|(x3<<24)); }
static const		TokenId		TokenIdInvalid	= (TokenId)0;
static const		TokenId		TokenIdCoreCoin = TokenIdMake('D', 'I', 'O');
static const		TokenId		TokenIdNonFungibleBit = (TokenId)0x8000'0000'0000'0000ull;
inline				TokenId		TokenIdFromSymbol(const rt::String_Ref& symbol)
								{	if(symbol.GetLength() >= TokenNameSizeMin && symbol.GetLength() <= TokenNameSizeMax)
									{	TokenId ret = TokenIdInvalid;
										symbol.CopyTo((char*)&ret);
										return ret;
									}
									else return TokenIdInvalid;
								}
inline			rt::String_Ref	TokenIdToSymbol(TokenId id){ return rt::DS(id).GetLengthRecalculated(); }

namespace _details
{
/////////////////////////////////////////////////////////////
// NONFUNGIBLE_ID
// [SC:4b][ShardIdx:12b][NonFungibleId:48b]
// ((SC-1)*2) = bitwidth for piece_index
inline constexpr uint64_t		NONFUNGIBLE_ID_PIECEIDX_BITMASK(TokenId nfid){ return (~(0xffffffffffffffffULL<<(((((uint64_t)nfid)>>60)-1)*2))); }
inline constexpr uint64_t		NONFUNGIBLE_ID_PIECE_MAXCOUNT(TokenId nfid){ return (NONFUNGIBLE_ID_PIECEIDX_BITMASK(nfid)+1); }
inline constexpr uint64_t		NONFUNGIBLE_ID_PIECEIDX_BITS(uint64_t piece_count){ return (piece_count>1?(((32 - rt::LeadingZeroBits<uint64_t>(piece_count-1)) + 1)&(~1ULL)):0); }
inline constexpr uint64_t		NONFUNGIBLE_ID_PIECEIDX_SPACE(uint64_t piece_count){ return	(1ULL<<NONFUNGIBLE_ID_PIECEIDX_BITS(piece_count)); }
inline constexpr uint64_t		NONFUNGIBLE_PIECEIDX(TokenId nfid){ return (NONFUNGIBLE_ID_PIECEIDX_BITMASK(nfid)&((uint64_t)nfid)); }
inline constexpr uint64_t		NONFUNGIBLE_ID_BASE(TokenId nfid){ return ((~NONFUNGIBLE_ID_PIECEIDX_BITMASK(nfid))&((uint64_t)nfid)); }
inline constexpr uint64_t		NONFUNGIBLE_ID_MAKE(TokenId nfid, uint64_t piece_id){ return (NONFUNGIBLE_ID_BASE(nfid) | ((piece_id)&NONFUNGIBLE_ID_PIECEIDX_BITMASK(nfid))); }
} // namespace _details

static const	uint32_t		GlobalShard = 0xffffU;	// shard index of the global shard

enum class ScopeFlag: uint32_t
{
	Foreign		= 1<<0, // scope definition is imported from another contract
	HasState	= 1<<1,	// state members are defined in the scope
	HasFunction	= 1<<2, // member function defined in the scope
};

enum class CompilationFlag: uint64_t
{
	None				= 0,
	DisableDebugPrint	= 1<<0,
	DisableGlobalScope	= 1<<1,
};

typedef uint32_t UInt32;
typedef uint64_t UInt64;
struct UInt96  { uint8_t _[96/8]; };
struct UInt128 { uint8_t _[128/8]; };
struct UInt160 { uint8_t _[160/8]; };
struct UInt256 { uint8_t _[256/8]; };
struct UInt512 { uint8_t _[512/8]; };

typedef UInt256 HashValue;
typedef HashValue BlobAddress;
typedef HashValue ContractModuleID;
static_assert(sizeof(HashValue) == RVM_HASH_SIZE);

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
	Unspecified, // error code is not specified
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
	auto Str() const { return rt::String_Ref((char*)DataPtr, DataSize); }
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

namespace rvm
{

inline ContractInvokeId		operator + (ContractScopeId csid, BuildNum b){ return CONTRACT_SET_BUILD(csid, b); }
inline ContractInvokeId		operator + (ContractVersionId cvid, Scope s){ return CONTRACT_SET_SCOPE(cvid, s); }
inline ContractVersionId	operator + (ContractId cid, BuildNum b){ return CONTRACT_SET_BUILD(cid, b); }
inline ContractScopeId		operator + (ContractId cid, Scope s){ return CONTRACT_SET_SCOPE(cid, s); }
inline ContractVersionId	operator ~ (ContractInvokeId ciid){ return CONTRACT_UNSET_SCOPE(ciid); }
inline ContractId			operator ~ (ContractScopeId csid){ return CONTRACT_UNSET_SCOPE(csid); }
inline ContractScopeId		operator - (ContractInvokeId ciid){ return CONTRACT_UNSET_BUILD(ciid); }
inline ContractId			operator - (ContractVersionId cvid){ return CONTRACT_UNSET_BUILD(cvid); }

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
	STRINGIFY_ENUM(UInt32)
	STRINGIFY_ENUM(UInt64)
	STRINGIFY_ENUM(UInt96)
	STRINGIFY_ENUM(UInt160)
	STRINGIFY_ENUM(UInt128)
	STRINGIFY_ENUM(UInt256)
	STRINGIFY_ENUM(UInt512)
	STRINGIFY_ENUM(AddressEnumerable)
	STRINGIFY_ENUM(UInt32Enumerable)
	STRINGIFY_ENUM(UInt64Enumerable)
	STRINGIFY_ENUM(UInt96Enumerable)
	STRINGIFY_ENUM(UInt128Enumerable)
	STRINGIFY_ENUM(UInt160Enumerable)
	STRINGIFY_ENUM(UInt256Enumerable)
	STRINGIFY_ENUM(UInt512Enumerable)
STRINGIFY_ENUM_END(ScopeKeySize, rvm)

STRINGIFY_ENUM_BEGIN(ScopeFlag, rvm)
	STRINGIFY_ENUM_BIT(Foreign)
	STRINGIFY_ENUM_BIT(HasState)
	STRINGIFY_ENUM_BIT(HasFunction)
STRINGIFY_ENUM_END(ScopeFlag, rvm)
