#pragma once
#include <cstdint>

namespace prlrt {

	enum class ContractContextType : uint8_t {
		None = 0,
		Global = 1,
		Shard = 2,
		Address = 3,
		Uint32 = 4,
		Uint64 = 5,
		Uint96 = 6,
		Uint128 = 7,
		Uint160 = 8,
		Uint256 = 9,
		Uint512 = 10,
		Num
	};

	enum class ExecutionError : uint8_t {
		NoError = 0,
		FunctionNotFound = 1,
		ArgumentDeserializationFailure = 2,
		RuntimeException = 3,
		UserDefinedError = 4,
		SerializeOutUnknownContextClass = 5,
		WASMTrapError = 6,
		ResidualNotAllowed = 7,
		DepositTokenError = 8
	};

	enum class ExceptionType : uint16_t {
		NoException = 0,
		Overflow = 1,
		Underflow = 2,
		DividedByZero = 3,
		TokenTransfer_NoTokenType = 4,
		TokenTransfer_TokenTypeMismatch = 5,
		TokenTransfer_NegativeAmount = 6,
		TokenTransfer_InsufficientCredit = 7,
		OutOfRange = 8,
		PopEmptyArray = 9,
		MapInsertFailure = 10,
		ConstMapAccessNonExistingKey = 11,
		DeserializationFailure = 12,
		InvalidMapKeyType = 13,
		EnumValueOverflow = 14,
		MemoryWriteVialation = 15,
		CrossCallFunctionNotFound = 16,
		CrossCallArgumentMismatch = 17,
		CrossCallContractNotFound = 18,
		BigIntOverFlow = 19,
		TokenDoubleSerialization = 20,
		AssertionFailure = 21,
		RelayError = 22,
		InitAddressWithInvalidLiteral = 23,
		UnknownException = 24,
		InitHashWithInvalidLiteral = 25,
		StringLengthOverflow = 26,
		AccessUnavailableContextFunction = 27,
		InvalidStringToAddressConversion = 28,
		NoAssetMintPermission = 29,
		GasUsedUp = 30,
		TokenMint_NegativeAmount = 31,
		InvalidTokenId = 32,
		DeployFailed = 33,
	};

	enum prlrt_oprations : uint8_t
	{
	// bool
	PRDOP_BOOL_ASSIGN = 0,				// =
	PRDOP_BOOL_NOT,						// !
	PRDOP_BOOL_COMP,					// == !=
	// enum
	PRDOP_ENUM_ASSIGN,					// =
	PRDOP_ENUM_COMP,					// == !=
	// int and uint
	PRDOP_INT_ASSIGN,					// =
	PRDOP_INT_OP_SELF,					// ++ -- ! -
	PRDOP_INT_OP_SIMPLE,				// + - & | ^ << >> < > == != <= >=
	PRDOP_INT_OP_COMPLEX,				// * / %
	// bigint
	PRDOP_BIGINT_ASSIGN_STATIC,			// =
	PRDOP_BIGINT_ASSIGN_DYNAMIC,		// dynamic assign coefficient
	PRDOP_BIGINT_OP_SELF,				// ++ -- ! -
	PRDOP_BIGINT_OP_SIMPLE,				// + - & | ^ << >> < > == != <= >=
	PRDOP_BIGINT_OP_COMPLEX,			// * / %
	// float
	PRDOP_FLOAT_ASSIGN,					// =
	PRDOP_FLOAT_OP_SELF,				// -
	PRDOP_FLOAT_OP_SIMPLE,				// + - << >> < > == != <= >=
	PRDOP_FLOAT_OP_COMPLEX,				// * /
	// address, blob, hash
	PRDOP_ABH_ASSIGN,					// =
	PRDOP_ABH_OP_SIMPLE,				// < > == != <= >=
	PRDOP_ABH_TYPE_TRANSFORM,					// abh to string, string to abh
	PRDOP_ADDRESS_CHECK,				// is user / delegated / dapp ...
	// string
	PRDOP_STR_ASSIGN, 					// = 
	PRDOP_STR_OP_SIMPLE,				// < > == != <= >= set, append, length
	// array
	PRDOP_ARRAY_ASSIGN,					// =
	PRDOP_ARRAY_OP_SIMPLE,				// [], length, set_length, push, pop
	// map
	PRDOP_MAP_ASSIGN,					// =
	PRDOP_MAP_OP_SIMPLE,				// length, has, erase, []
	// token
	PRDOP_TOKEN_ASSIGN,					// =
	PRDOP_TOKEN_ID,						// get_id
	PRDOP_TOKEN_AMOUNT,					// get_amount
	PRDOP_TOKEN_TRANSFER,				// transfer
	PRDOP_TOKEN_TRANSFERALL,			// transfer_all
	PRDOP_TOKEN_DEPOSIT,				// deposit
	// data serialization
	PRDOP_SERIALIZE_SIZE,				// get_serialize_size
	PRDOP_SERIALIZE_OUT_STATIC,			// serialize_out
	PRDOP_SERIALIZE_MAP_STATIC,			// map_from_serialize_data
	PRDOP_SERIALIZE_DYNAMIC,			// dynamic serialization coefficient
	// function
	PRDOP_JUMP,
	PRDOP_CROSS,
	PRDOP_RELAY,
	PRDOP_GLOBAL_RELAY,
	PRDOP_DEPLOY,
	// transaction context
	PRDOP_TXN_CTX,
	// block context
	PRDOP_BLK_CTX,
	// debug
	PRDOP_DEBUG_OP,
	// scattered types
	PRDOP_SCTP_GET_UNTOUCHED,
	PRDOP_SCTP_COMMIT,
	PRDOP_SCTMAP_ERASE,
	PRDOP_SCTARR_PUSH,
	PRDOP_SCTARR_POP,
	PRDOP_SCTARR_LEN,
	PRDOP_NUM,
	};

	struct CBigInt;

	enum class transaction_type : uint16_t {
		__prli_normal_type = 0,
		__prli_relay_type,
		__prli_system_type,
		__prli_scheduled_type,
	};

	enum class uievent_state : uint16_t {
		__prli_deactivated = 0,
		__prli_activated,
		__prli_locked,
		__prli_unlocked
	};

#pragma pack(push, 1)
	template<int bitWidth>
	struct PrecisionFloatInternal {
		static const bool __IsPOD = true;
		uint8_t _Data[bitWidth / 8 + 4];
		PrecisionFloatInternal<bitWidth>() {
			memset(_Data, 0, bitWidth / 8 + 4);
		}
	};

	template<int Size>
	struct LongIntInternal{
		static const bool __IsPOD = true;
		uint8_t _Data[Size/8];
		constexpr LongIntInternal<Size>() : _Data()
		{
			for (int i = 0; i < Size / 8; i++)
			{
				_Data[i] = 0;
			}
		}
	};
#pragma pack(pop)

#define FOR_EACH_PREDA_FLOAT_METHOD(V, _BIT)\
	V(uint32_t, GetConvertToStringLen_##_BIT, const ::prlrt::PrecisionFloatInternal<_BIT>* pftemp)\
	V(void, ConvertToString_##_BIT, const ::prlrt::PrecisionFloatInternal<_BIT>* pftemp, char* buf)\
	V(void, ConvertFromString_##_BIT, ::prlrt::PrecisionFloatInternal<_BIT>* pftemp, const char* float_literal)\
	V(void, Float_Add_##_BIT, const ::prlrt::PrecisionFloatInternal<_BIT>* a, const ::prlrt::PrecisionFloatInternal<_BIT>* b, ::prlrt::PrecisionFloatInternal<_BIT>* result)\
	V(void, Float_Sub_##_BIT, const ::prlrt::PrecisionFloatInternal<_BIT>* a, const ::prlrt::PrecisionFloatInternal<_BIT>* b, ::prlrt::PrecisionFloatInternal<_BIT>* result)\
	V(void, Float_Mul_##_BIT, const ::prlrt::PrecisionFloatInternal<_BIT>* a, const ::prlrt::PrecisionFloatInternal<_BIT>* b, ::prlrt::PrecisionFloatInternal<_BIT>* result)\
	V(void, Float_Div_##_BIT, const ::prlrt::PrecisionFloatInternal<_BIT>* a, const ::prlrt::PrecisionFloatInternal<_BIT>* b, ::prlrt::PrecisionFloatInternal<_BIT>* result)\
	V(void, Float_Zero_##_BIT, ::prlrt::PrecisionFloatInternal<_BIT>* a)\
	V(bool, Float_IsZero_##_BIT, const ::prlrt::PrecisionFloatInternal<_BIT>* a)\
	V(void, Float_Negate_##_BIT, const ::prlrt::PrecisionFloatInternal<_BIT>* a, ::prlrt::PrecisionFloatInternal<_BIT>* result)\
	V(int, Float_Compare_##_BIT, const ::prlrt::PrecisionFloatInternal<_BIT>* a, const ::prlrt::PrecisionFloatInternal<_BIT>* b)\

#define FOR_EACH_LONGINT_METHOD(V, _SIZE, _INT_TYPE) \
	V(void, _INT_TYPE##_Zero_##_SIZE, ::prlrt::LongIntInternal<_SIZE>* a)\
	V(void, _INT_TYPE##_ConvertFromString_##_SIZE, ::prlrt::LongIntInternal<_SIZE>* a, const char* longint_literal)\
	V(void, _INT_TYPE##_fromInt_##_SIZE, ::prlrt::LongIntInternal<_SIZE>* a, int64_t in)\
	V(void, _INT_TYPE##_fromUInt_##_SIZE, ::prlrt::LongIntInternal<_SIZE>* a, uint64_t in)\
	V(int, _INT_TYPE##_toInt64_##_SIZE, const ::prlrt::LongIntInternal<_SIZE>* a, int64_t* result)\
	V(int, _INT_TYPE##_toUInt64_##_SIZE, const ::prlrt::LongIntInternal<_SIZE>* a, uint64_t* result)\
	V(void, _INT_TYPE##_rightShift_##_SIZE, ::prlrt::LongIntInternal<_SIZE>* a, int64_t shift)\
	V(void, _INT_TYPE##_leftShift_##_SIZE, ::prlrt::LongIntInternal<_SIZE>* a, int64_t shift)\
	V(void, _INT_TYPE##_ConvertFromHexString_##_SIZE, ::prlrt::LongIntInternal<_SIZE>* a, const char* longint_literal)\
	V(void, _INT_TYPE##_ConvertToString_##_SIZE, const ::prlrt::LongIntInternal<_SIZE>* a, char* buf)\
	V(uint32_t, _INT_TYPE##_GetConvertToStringLen_##_SIZE, const ::prlrt::LongIntInternal<_SIZE>* a)\
	V(bool, _INT_TYPE##_IsZero_##_SIZE, const ::prlrt::LongIntInternal<_SIZE>* a)\
	V(void, _INT_TYPE##_Add_##_SIZE, const ::prlrt::LongIntInternal<_SIZE>* a, const ::prlrt::LongIntInternal<_SIZE>* b, ::prlrt::LongIntInternal<_SIZE>* result)\
	V(void, _INT_TYPE##_Sub_##_SIZE, const ::prlrt::LongIntInternal<_SIZE>* a, const ::prlrt::LongIntInternal<_SIZE>* b, ::prlrt::LongIntInternal<_SIZE>* result)\
	V(void, _INT_TYPE##_Mul_##_SIZE, const ::prlrt::LongIntInternal<_SIZE>* a, const ::prlrt::LongIntInternal<_SIZE>* b, ::prlrt::LongIntInternal<_SIZE>* result)\
	V(void, _INT_TYPE##_Div_##_SIZE, const ::prlrt::LongIntInternal<_SIZE>* a, const ::prlrt::LongIntInternal<_SIZE>* b, ::prlrt::LongIntInternal<_SIZE>* result)\
	V(void, _INT_TYPE##_Mod_##_SIZE, const ::prlrt::LongIntInternal<_SIZE>* a, const ::prlrt::LongIntInternal<_SIZE>* b, ::prlrt::LongIntInternal<_SIZE>* result)\
	V(int, _INT_TYPE##_Compare_##_SIZE, const ::prlrt::LongIntInternal<_SIZE>* a, const ::prlrt::LongIntInternal<_SIZE>* b)\
	V(void, _INT_TYPE##_SetMax_##_SIZE, ::prlrt::LongIntInternal<_SIZE>* a)\
	V(void, _INT_TYPE##_SetMin_##_SIZE, ::prlrt::LongIntInternal<_SIZE>* a)\

#define FOR_EACH_LONGINT_NEGATE_METHOD(V, _SIZE) \
	V(void, LongInt_Negate_##_SIZE, const ::prlrt::LongIntInternal<_SIZE>* a, ::prlrt::LongIntInternal<_SIZE>* result)\
	V(bool, LongInt_IsSign_##_SIZE, const ::prlrt::LongIntInternal<_SIZE>* a)\

#define FOR_EACH_PREDA_INTERFACE_METHOD(V) \
	/* Bigint start */ \
	V(::prlrt::BigintPtr, CreateBigint, )\
	V(void, ReleaseBigint, ::prlrt::BigintPtr self)\
	/* assign */\
	V(void, BigintAssign, ::prlrt::BigintPtr self, const ::prlrt::BigintPtr a)\
	V(void, BigintAssignInt64, ::prlrt::BigintPtr self, int64_t a)\
	V(void, BigintAssignString, ::prlrt::BigintPtr self, const char* a, uint32_t len)\
	V(void, BigintAssignUint64, ::prlrt::BigintPtr self, uint64_t a)\
\
	/*  conversion */\
	/*  1: overflow */\
	/*  0: success */\
	/* -1: underflow */\
	V(int, BigintToInt64, ::prlrt::BigintPtr self, int64_t* out)\
	V(int, BigintToUint64, ::prlrt::BigintPtr self, uint64_t* out)\
\
	/*  operators */\
	V(void, BigintAdd, ::prlrt::BigintPtr self, const ::prlrt::BigintPtr a, const ::prlrt::BigintPtr b)\
	V(void, BigintAddInplace, ::prlrt::BigintPtr self, const ::prlrt::BigintPtr a)\
	V(void, BigintSub, ::prlrt::BigintPtr self, const ::prlrt::BigintPtr a, const ::prlrt::BigintPtr b)\
	V(void, BigintSubInplace, ::prlrt::BigintPtr self, const ::prlrt::BigintPtr a)\
	V(void, BigintMul, ::prlrt::BigintPtr self, const ::prlrt::BigintPtr a, const ::prlrt::BigintPtr b)\
	V(void, BigintMul_Uint32, ::prlrt::BigintPtr self, const ::prlrt::BigintPtr a, uint32_t b)\
	V(void, BigintMul_Int32, ::prlrt::BigintPtr self, const ::prlrt::BigintPtr a, int b)\
	V(void, BigintShiftRightInplace, ::prlrt::BigintPtr self, int a)\
	V(void, BigintShiftLeftInplace, ::prlrt::BigintPtr self, int a)\
	V(void, BigintMulInplace_Int32, ::prlrt::BigintPtr self, int a)\
	V(void, BigintMulInplace_Uint32, ::prlrt::BigintPtr self, uint32_t a)\
	V(void, BigintDiv_Uint32, ::prlrt::BigintPtr self, const ::prlrt::BigintPtr a, uint32_t b, uint32_t* remainder = nullptr)\
	V(void, BigintDiv, ::prlrt::BigintPtr self, const ::prlrt::BigintPtr a, const ::prlrt::BigintPtr b, ::prlrt::BigintPtr remainder = 0)\
	V(void, BigintMod, ::prlrt::BigintPtr self, const ::prlrt::BigintPtr a, const ::prlrt::BigintPtr b)\
	V(void, BigintNegate, ::prlrt::BigintPtr self, const ::prlrt::BigintPtr a)\
	V(void, BigintNegateInplace, ::prlrt::BigintPtr self)\
	V(bool, BigintIsNegative, ::prlrt::BigintPtr self)\
\
	/*  compare */\
	V(int, BigintCompare, ::prlrt::BigintPtr self, const ::prlrt::BigintPtr a)\
\
	/*  serialization */\
	V(uint32_t, BigintInitFromEmbedded, ::prlrt::BigintPtr self, const uint8_t* in, uint32_t in_size)\
	V(uint32_t, BigintGetEmbeddedSize, ::prlrt::BigintPtr self)\
	V(void, BigintEmbed, ::prlrt::BigintPtr self, uint8_t* out)\
	V(bool, BigintIsEmbeddable, ::prlrt::BigintPtr self)\
	V(uint32_t, BigintGetStringLength, ::prlrt::BigintPtr self)\
	V(uint32_t, BigintToString, ::prlrt::BigintPtr self, char* out, uint32_t size)\
	/*  Bigint end */\
\
	V(bool, InitAddressFromLiteral, void* pAddress, const char* str)\
	V(bool, InitHashFromLiteral, void* pHash, const char* str)\
	V(bool, StringToAddress, void* pAddress, const char* data, uint32_t data_len)\
	V(uint32_t, GetHashToStringLength, )\
	V(uint32_t, GetAddressToStringLength, const void* pAddress)\
	V(bool, AddressToString, const void* pData, uint32_t dataLen, char* out)\
	V(void, CalculateHash, void* pHash, const uint8_t* data, uint32_t data_len)\
	V(bool, EmitRelayToScope, const uint8_t* scope_key, uint32_t scope_key_size, uint32_t scope_type, uint32_t opCode, const uint8_t* args_serialized, uint32_t args_size)\
	V(bool, EmitRelayToGlobal, uint32_t opCode, const uint8_t* args_serialized, uint32_t args_size)\
	V(bool, EmitRelayToShards, uint32_t opCode, const uint8_t* args_serialized, uint32_t args_size)\
	V(bool, EmitRelayDeferred, uint32_t opCode, const uint8_t* args_serialized, uint32_t args_size)\
	V(bool, HashToString, const void* pData, uint32_t dataLen, char* out) \
	V(uint32_t, CrossCall, uint64_t cvId, int64_t templateContractImportSlot, uint32_t opCode, const void** ptrs, uint32_t numPtrs)\
	V(uint32_t, InterfaceCall, uint64_t cvId, int64_t interfaceContractImportSlot, uint32_t slotIdx, uint32_t funcIdx, const void** ptrs, uint32_t numPtrs)\
	V(bool, ContractImplementsInterface, uint64_t cvId, int64_t interfaceContractImportSlot, uint32_t slotIdx)\
	V(bool, ContractHasTemplate, uint64_t cvId, int64_t templateContractImportSlot)\
	V(uint64_t, DeployCall, int64_t templateContractImportSlot, const void** ptrs, uint32_t numPtrs)\
	V(void, ReportOrphanToken, uint64_t id, ::prlrt::BigintPtr amount)\
	V(void, DepositToken, uint64_t id, ::prlrt::BigintPtr amount)\
	V(void, TokenMinted, uint64_t id, ::prlrt::BigintPtr amount)\
	V(void, TokenBurnt, uint64_t id, ::prlrt::BigintPtr amount)\
	V(uint32_t, TokenIdToSymbolLength, uint64_t id)\
	V(uint64_t, TokenSymbolToId, const char *symbol)\
	V(bool, AllowedToMint, uint64_t id)\
	V(void, ReportReturnValue, const char* type_export_name, const uint8_t* serialized_data, uint32_t serialized_data_size)\
	V(void, DebugPrintBufferAppendSerializedData, const char* type_export_name, const uint8_t* serialized_data, uint32_t serialized_data_size)\
	V(void, DebugPrintOutputBuffer, uint32_t line)\
	V(void, DebugAssertionFailure, uint32_t line)\
	V(void, DebugAssertionFailureMessage, uint32_t line, const char* message, uint32_t length)\
\
	V(bool, IsUserAddress, const void* pAddress)\
	V(bool, IsDelegatedAddress, const void* pAddress)\
	V(bool, IsDAppAddress, const void* pAddress)\
	V(bool, IsAssetAddress, const void* pAddress)\
	V(bool, IsNameAddress, const void* pAddress)\
	V(bool, IsContractAddress, const void* pAddress)\
	V(bool, IsCustomAddress, const void* pAddress)\
	V(void, SetAsContractAddress, void* pAddress, uint64_t contract_id)\
	V(void, SetAsCustomAddress, void* pAddress, const uint8_t* data)\
\
	V(bool, GetState, uint64_t cvid, uint8_t scope_id, uint8_t slot_id, const uint8_t* key_data, uint32_t key_data_size, const uint8_t*& value_data, uint32_t& value_data_size)\
	V(void, SetState, uint64_t cvid, uint8_t scope_id, uint8_t slot_id, const uint8_t* key_data, uint32_t key_data_size, const uint8_t* value_data, uint32_t value_data_size)\
	V(uint32_t, GetStateSize, uint64_t cvid, uint8_t scope_id, uint8_t slot_id, const uint8_t* key_data, uint32_t key_data_size)\
	V(bool, GetStateData, uint64_t cvid, uint8_t scope_id, uint8_t slot_id, const uint8_t* key_data, uint32_t key_data_size, uint8_t* value_data)\
\
	FOR_EACH_PREDA_FLOAT_METHOD(V, 256)\
	FOR_EACH_PREDA_FLOAT_METHOD(V, 512)\
	FOR_EACH_PREDA_FLOAT_METHOD(V, 1024)\
\
	FOR_EACH_LONGINT_METHOD(V, 128, ULongInt)\
	FOR_EACH_LONGINT_METHOD(V, 256, ULongInt)\
	FOR_EACH_LONGINT_METHOD(V, 512, ULongInt)\
	FOR_EACH_LONGINT_METHOD(V, 128, LongInt)\
	FOR_EACH_LONGINT_METHOD(V, 256, LongInt)\
	FOR_EACH_LONGINT_METHOD(V, 512, LongInt)\
	FOR_EACH_LONGINT_NEGATE_METHOD(V, 128)\
	FOR_EACH_LONGINT_NEGATE_METHOD(V, 256)\
	FOR_EACH_LONGINT_NEGATE_METHOD(V, 512)\
	/*  block context */\
	V(uint64_t, Block_GetHeight, )\
	V(uint32_t, Block_GetShardIndex, )\
	V(uint32_t, Block_GetShardOrder, )\
	V(uint64_t, Block_GetTimestamp, )\
	V(uint64_t, Block_GetRandomNumber, )\
	V(void, Block_GetMinerAddress, uint8_t* out)\
\
	/*  transaction context */\
	V(::prlrt::transaction_type, Transaction_GetType, )\
	V(void, Transaction_GetSelfAddress, uint8_t* out)\
	V(void, Transaction_GetSender, uint8_t* out)\
	V(uint64_t, Transaction_GetTimeStamp, )\
	V(void, Transaction_GetSigner, uint32_t signerIdx, uint8_t* out)\
	V(const uint32_t, Transaction_GetSignerCount, )\
	V(bool, Transaction_VerifySignerByIndex, uint32_t signerIdx)\
	V(bool, Transaction_VerifySignerByAddress, const uint8_t* pSignerAddress)\
	V(uint32_t, Transaction_GetOriginatedShardIndex, )\
	V(uint32_t, Transaction_GetOriginatedShardOrder, )\
	V(void, Transaction_GetInitiatorAddress, uint8_t* out)\
	V(uint32_t, Transaction_GetSuppliedTokensCount, )\
	V(void, Transaction_GetSuppliedToken, uint32_t index, uint64_t *id, ::prlrt::BigintPtr self)\
\
	/*  event context */\
	V(::prlrt::uievent_state, Event_GetUserState)\
	V(void, Event_Push, uint32_t id, const char* pData, uint32_t dataLen)\
	V(void, Event_Notify, uint32_t id, const char* pData, uint32_t dataLen)\
	V(void, Event_Exception, const char *msg, ::prlrt::ExceptionType exc_type)

#if defined(__wasm32__)
#define PREDA_INTERFACE_METHOD_V(RET, FN, ...) RET preda##FN(__VA_ARGS__);
struct IRuntimeInterface {};
using BigintPtr = uint64_t;
extern "C" {
	FOR_EACH_PREDA_INTERFACE_METHOD(PREDA_INTERFACE_METHOD_V)
}
#undef PREDA_INTERFACE_METHOD_V
#else
#define PREDA_INTERFACE_METHOD_V(RET, FN, ...) virtual RET FN(__VA_ARGS__) = 0;
using BigintPtr = prlrt::CBigInt*;
struct IRuntimeInterface {
	FOR_EACH_PREDA_INTERFACE_METHOD(PREDA_INTERFACE_METHOD_V)
};
#undef PREDA_INTERFACE_METHOD_V
#endif
}

