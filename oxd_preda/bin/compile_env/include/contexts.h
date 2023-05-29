#pragma once
#include "common.h"
#include "inttypes.h"
#include "address_blob_hash_types.h"
#include "arraytype.h"

namespace prlrt {

	struct __prlt___block {
		__prlt_uint64 __prli_get_height()
		{
			return PREDA_CALL(Block_GetHeight, );
		}
		__prlt_uint32 __prli_get_shard_index()
		{
			return PREDA_CALL(Block_GetShardIndex, );
		}
		__prlt_uint32 __prli_get_shard_order()
		{
			return PREDA_CALL(Block_GetShardOrder, );
		}
		__prlt_uint64 __prli_get_timestamp()
		{
			return PREDA_CALL(Block_GetTimestamp, );
		}
		__prlt_uint64 __prli_get_random_number()
		{
			return PREDA_CALL(Block_GetRandomNumber, );
		}
		__prlt_address __prli_get_miner_address()
		{
			__prlt_address value;
			PREDA_CALL(Block_GetMinerAddress, (uint8_t*)&value);
			return value;
		}
	};

}

prlrt::__prlt___block __prli___block;


using __prlt_transaction_type__ = prlrt::transaction_type;
using __prlt_transaction_type = prlrt::enum_wrapper<prlrt::transaction_type, 4>;

namespace prlrt {

	struct __prlt___transaction {
		__prlt_transaction_type __prli_get_type()
		{
			return PREDA_CALL(Transaction_GetType, );
		}
		__prlt_address __prli_get_self_address()
		{
			__prlt_address value;
			PREDA_CALL(Transaction_GetSelfAddress, (uint8_t*)&value);
			return value;
		}
		__prlt_address __prli_get_sender()
		{
			__prlt_address value;
			PREDA_CALL(Transaction_GetSender, (uint8_t*)&value);
			return value;
		}
		__prlt_uint64 __prli_get_timestamp()
		{
			return PREDA_CALL(Transaction_GetTimeStamp, );
		}
		__prlt_array<__prlt_address> __prli_get_signers()
		{
			if (__prli_get_type() != transaction_type::__prli_normal_type)
				throw preda_exception("get_signer not available", prlrt::ExceptionType::AccessUnavailableContextFunction);
			__prlt_array<__prlt_address> ret;
			uint32_t numSigner = PREDA_CALL(Transaction_GetSingerCount, );
			for (uint32_t i = 0; i < numSigner; i++) {
				__prlt_address value;
				PREDA_CALL(Transaction_GetSigner, i, (uint8_t*)&value);
				ret.__prli_push(value);
			}
			return ret;
		}
		__prlt_bool __prli_verify_signer(__prlt_uint32 signerIdx)
		{
			if (__prli_get_type() != transaction_type::__prli_normal_type)
				return false;
			if (signerIdx._v >= PREDA_CALL(Transaction_GetSingerCount, ))
				return false;
			return PREDA_CALL(Transaction_VerifySignerByIndex, signerIdx._v);
		}
		__prlt_bool __prli_verify_signer(const __prlt_address &signerAddress)
		{
			if (__prli_get_type() != transaction_type::__prli_normal_type)
				return false;
			return PREDA_CALL(Transaction_VerifySignerByAddress, (const uint8_t *)&signerAddress);
		}
		__prlt_uint32 __prli_get_originated_shard_index()
		{
			if (__prli_get_type() != transaction_type::__prli_relay_type)
				throw preda_exception("get_originated_shard_index not available", prlrt::ExceptionType::AccessUnavailableContextFunction);
			return PREDA_CALL(Transaction_GetOriginatedShardIndex, );
		}
		__prlt_uint32 __prli_get_originated_shard_order()
		{
			if (__prli_get_type() != transaction_type::__prli_relay_type)
				throw preda_exception("get_originated_shard_order not available", prlrt::ExceptionType::AccessUnavailableContextFunction);
			return PREDA_CALL(Transaction_GetOriginatedShardOrder, );
		}
		__prlt_address __prli_get_initiator_address()
		{
			if (__prli_get_type() != transaction_type::__prli_relay_type)
				throw preda_exception("get_originated_address not available", prlrt::ExceptionType::AccessUnavailableContextFunction);
			__prlt_address value;
			PREDA_CALL(Transaction_GetInitiatorAddress, (uint8_t*)&value);
			return value;
		}
	};

}

prlrt::__prlt___transaction __prli___transaction;


using __prlt_uievent_state__ = prlrt::uievent_state;
using __prlt_uievent_state = prlrt::enum_wrapper<prlrt::uievent_state, 4>;

namespace prlrt {

	struct __prlt___event {
		__prlt_uievent_state __prli_get_user_state()
		{
			return PREDA_CALL(Event_GetUserState, );
		}
		void __prli_push(__prlt_uint32 id, __prlt_string data)
		{
			PREDA_CALL(Event_Push, id._v, data.ptr->str.c_str(), (uint16_t)data.ptr->str.length());
		}
		void __prli_notify(__prlt_uint32 id, __prlt_string data)
		{
			PREDA_CALL(Event_Notify, id._v, data.ptr->str.c_str(), (uint16_t)data.ptr->str.length());
		}
	};

}

prlrt::__prlt___event __prli___event;


namespace prlrt {

	struct __prlt___debug {

		// fallback of print() when preda is compiled with "nodebugprint" option
		void __prli_print_disabled()
		{
		}

		void __prli_print(uint32_t line)
		{
			PREDA_CALL(DebugPrintOutputBuffer, line);
		}

		template<typename TFirstArg, typename ...Args>
		void __prli_print(uint32_t line, const char *typeExportName, TFirstArg &&first_arg, Args &&...args)
		{
			std::vector<uint8_t> buffer(first_arg.get_serialize_size());
			first_arg.serialize_out(&buffer[0], true);
			PREDA_CALL(DebugPrintBufferAppendSerializedData, typeExportName, &buffer[0], (uint32_t)buffer.size());
			__prli_print(line, args...);
		}

		void __prli_assert(__prlt_bool condition, __prlt_uint32 line)
		{
			if (!condition._v)
			{
				PREDA_CALL(DebugAssertionFailure, line._v);
				throw preda_exception("assertion failure", prlrt::ExceptionType::AssertionFailure);
			}
		}

		void __prli_assert(__prlt_bool condition, __prlt_string message, __prlt_uint32 line)
		{
			if (!condition._v)
			{
				PREDA_CALL(DebugAssertionFailureMessage, line._v, message.ptr->str.c_str(), (uint32_t)message.ptr->str.length());
				throw preda_exception("assertion failure", prlrt::ExceptionType::AssertionFailure);
			}
		}

	};

}

prlrt::__prlt___debug __prli___debug;
