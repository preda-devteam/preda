#pragma once
#include <cstdint>

namespace prlrt {

	enum class ContractContextType : uint8_t {
		None = 0,
		Global = 1,
		PerShard = 2,
		PerAddress = 3,
		Num
	};

	enum class ExecutionError : uint8_t {
		NoError = 0,
		FunctionNotFound = 1,
		ArgumentDeserializationFailure = 2,
		RuntimeException = 3,
		UserDefinedError = 4,
		SerializeOutUnknownContextClass = 5,
		WASMTrapError = 6
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
	V(uint32_t, GetAddressToStringLength, )\
	V(bool, AddressToString, const void* pData, uint32_t dataLen, char* out)\
	V(void, CalculateHash, void* pHash, const uint8_t* data, uint32_t data_len)\
	V(bool, EmitRelayToAddress, const uint8_t* address, uint32_t opCode, const uint8_t* args_serialized, uint32_t args_size)\
	V(bool, EmitRelayToGlobal, uint32_t opCode, const uint8_t* args_serialized, uint32_t args_size)\
	V(bool, EmitRelayToShards, uint32_t opCode, const uint8_t* args_serialized, uint32_t args_size)\
	V(bool, HashToString, const void* pData, uint32_t dataLen, char* out) \
	V(uint32_t, CrossCall, uint64_t contractId, uint32_t opCode, const void** ptrs, uint32_t numPtrs)\
	V(uint32_t, InterfaceCall, uint64_t contractId, const char *interfaceName, uint32_t funcIdx, const void** ptrs, uint32_t numPtrs)\
	V(void, ReportOrphanToken, uint64_t id, ::prlrt::BigintPtr amount)\
	V(void, ReportReturnValue, const char* type_export_name, const uint8_t* serialized_data, uint32_t serialized_data_size)\
	V(void, DebugPrintBufferAppendSerializedData, const char* type_export_name, const uint8_t* serialized_data, uint32_t serialized_data_size)\
	V(void, DebugPrintOutputBuffer, )\
	V(void, DebugAssertionFailure, uint32_t line)\
	V(uint32_t, GetTokenIdByName, const char* name)\
\
	V(bool, IsUserAddress, const void* pAddress)\
	V(bool, IsDelegatedAddress, const void* pAddress)\
	V(bool, IsDAppAddress, const void* pAddress)\
	V(bool, IsAssetAddress, const void* pAddress)\
	V(bool, IsNameAddress, const void* pAddress)\
	V(bool, IsDomainAddress, const void* pAddress)\
\
	V(bool, BurnGasLoop, )\
	V(bool, BurnGasFunctionCall, )\
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
	V(uint64_t, Transaction_GetTimeStamp, )\
	V(void, Transaction_GetSigner, uint32_t signerIdx, uint8_t* out)\
	V(const uint32_t, Transaction_GetSingerCount, )\
	V(bool, Transaction_VerifySignerByIndex, uint32_t signerIdx)\
	V(bool, Transaction_VerifySignerByAddress, const uint8_t* pSignerAddress)\
	V(uint32_t, Transaction_GetOriginatedShardIndex, )\
	V(uint32_t, Transaction_GetOriginatedShardOrder, )\
	V(void, Transaction_GetInitiatorAddress, uint8_t* out)\
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

