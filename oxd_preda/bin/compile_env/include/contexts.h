#pragma once
#include "common.h"
#include "inttypes.h"
#include "address_blob_hash_types.h"
#include "arraytype.h"
#include "tokentype.h"
#include "gascost.h"

namespace prlrt {

	struct __prlt___block {
		__prlt_uint64 __prli_get_height() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_BLK_CTX]);
			return PREDA_CALL(Block_GetHeight, );
		}
		__prlt_uint32 __prli_get_shard_index() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_BLK_CTX]);
			return PREDA_CALL(Block_GetShardIndex, );
		}
		__prlt_uint32 __prli_get_shard_order() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_BLK_CTX]);
			return PREDA_CALL(Block_GetShardOrder, );
		}
		__prlt_uint64 __prli_get_timestamp() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_BLK_CTX]);
			return PREDA_CALL(Block_GetTimestamp, );
		}
		__prlt_uint64 __prli_get_random_number() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_BLK_CTX]);
			return PREDA_CALL(Block_GetRandomNumber, );
		}
		__prlt_address __prli_get_miner_address() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_BLK_CTX]);
			__prlt_address value;
			PREDA_CALL(Block_GetMinerAddress, (uint8_t*)&value);
			return value;
		}
	};

}

using __prlt_transaction_type__ = prlrt::transaction_type;
using __prlt_transaction_type = prlrt::enum_wrapper<prlrt::transaction_type, 4>;

namespace prlrt {

	struct __prlt___transaction {
		__prlt_transaction_type __prli_get_type() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_TXN_CTX]);
			return PREDA_CALL(Transaction_GetType, );
		}
		__prlt_address __prli_get_self_address() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_TXN_CTX]);
			__prlt_address value;
			PREDA_CALL(Transaction_GetSelfAddress, (uint8_t*)&value);
			return value;
		}
		__prlt_address __prli_get_sender() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_TXN_CTX]);
			__prlt_address value;
			PREDA_CALL(Transaction_GetSender, (uint8_t*)&value);
			return value;
		}
		__prlt_uint64 __prli_get_timestamp() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_TXN_CTX]);
			return PREDA_CALL(Transaction_GetTimeStamp, );
		}
		__prlt_array<__prlt_address> __prli_get_signers() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_TXN_CTX]);
			if (__prli_get_type() != transaction_type::__prli_normal_type && __prli_get_type() != transaction_type::__prli_system_type)
				preda_exception::throw_exception("get_signer not available", prlrt::ExceptionType::AccessUnavailableContextFunction);
			__prlt_array<__prlt_address> ret;
			uint32_t numSigner = PREDA_CALL(Transaction_GetSignerCount, );
			for (uint32_t i = 0; i < numSigner; i++) {
				__prlt_address value;
				PREDA_CALL(Transaction_GetSigner, i, (uint8_t*)&value);
				ret.__prli_push(value);
			}
			return ret;
		}
		__prlt_bool __prli_verify_signer(__prlt_uint32 signerIdx) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_TXN_CTX]);
			if (__prli_get_type() != transaction_type::__prli_normal_type)
				return false;
			if (signerIdx._v >= PREDA_CALL(Transaction_GetSignerCount, ))
				return false;
			return PREDA_CALL(Transaction_VerifySignerByIndex, signerIdx._v);
		}
		__prlt_bool __prli_verify_signer(const __prlt_address &signerAddress) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_TXN_CTX]);
			if (__prli_get_type() != transaction_type::__prli_normal_type)
				return false;
			return PREDA_CALL(Transaction_VerifySignerByAddress, (const uint8_t *)&signerAddress);
		}
		__prlt_uint32 __prli_get_originated_shard_index() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_TXN_CTX]);
			if (__prli_get_type() != transaction_type::__prli_relay_type)
				preda_exception::throw_exception("get_originated_shard_index not available", prlrt::ExceptionType::AccessUnavailableContextFunction);
			return PREDA_CALL(Transaction_GetOriginatedShardIndex, );
		}
		__prlt_uint32 __prli_get_originated_shard_order() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_TXN_CTX]);
			if (__prli_get_type() != transaction_type::__prli_relay_type)
				preda_exception::throw_exception("get_originated_shard_order not available", prlrt::ExceptionType::AccessUnavailableContextFunction);
			return PREDA_CALL(Transaction_GetOriginatedShardOrder, );
		}
		__prlt_address __prli_get_initiator_address() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_TXN_CTX]);
			if (__prli_get_type() != transaction_type::__prli_relay_type)
				preda_exception::throw_exception("get_originated_address not available", prlrt::ExceptionType::AccessUnavailableContextFunction);
			__prlt_address value;
			PREDA_CALL(Transaction_GetInitiatorAddress, (uint8_t*)&value);
			return value;
		}

		__prlt_array<__prlt_token> __prli_get_supplied_tokens() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_TXN_CTX]);
			return supplied_native_tokens;
		}

		void import_supplied_tokens() const
		{
			uint32_t count = PREDA_CALL(Transaction_GetSuppliedTokensCount, );
			for (uint32_t i = 0; i < count; i++)
			{
				__prlt_token cur_token;
				PREDA_CALL(Transaction_GetSuppliedToken, i, &cur_token.ptr->id._v, cur_token.ptr->amount._v);
				supplied_native_tokens.ptr->push(cur_token);
			}
		}

		void clear_supplied_tokens() const
		{
			supplied_native_tokens.ptr->set_length(0);
		}

		__prlt_uint64 __prli_get_remaining_gas() const
		{
			return RemainingGas;
		}

		mutable __prlt_array<__prlt_token> supplied_native_tokens;
	};

}

using __prlt_uievent_state__ = prlrt::uievent_state;
using __prlt_uievent_state = prlrt::enum_wrapper<prlrt::uievent_state, 4>;

namespace prlrt {

	struct __prlt___event {
		__prlt_uievent_state __prli_get_user_state() const
		{
			return PREDA_CALL(Event_GetUserState, );
		}
		void __prli_push(__prlt_uint32 id, __prlt_string data) const
		{
			PREDA_CALL(Event_Push, id._v, data.ptr->str.c_str(), (uint16_t)data.ptr->str.length());
		}
		void __prli_notify(__prlt_uint32 id, __prlt_string data) const
		{
			PREDA_CALL(Event_Notify, id._v, data.ptr->str.c_str(), (uint16_t)data.ptr->str.length());
		}
	};

}

namespace prlrt {

	struct __prlt___debug {

		// fallback of print() when preda is compiled with "nodebugprint" option
		void __prli_print_disabled() const
		{
		}

		void __prli_print(uint32_t line) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_DEBUG_OP]);
			PREDA_CALL(DebugPrintOutputBuffer, line);
		}

		template<typename TFirstArg, typename ...Args>
		void __prli_print(uint32_t line, const char *typeExportName, TFirstArg &&first_arg, Args &&...args) const
		{
			std::vector<uint8_t> buffer(first_arg.get_serialize_size());
			first_arg.serialize_out(&buffer[0], true);
			PREDA_CALL(DebugPrintBufferAppendSerializedData, typeExportName, &buffer[0], (uint32_t)buffer.size());
			__prli_print(line, args...);
		}

		template<typename ...Args>
		void __prli_print(uint32_t line, const char* typeExportName, bool first_arg, Args &&...args) const
		{
			uint8_t buffer = first_arg;
			PREDA_CALL(DebugPrintBufferAppendSerializedData, typeExportName, &buffer, 1);
			__prli_print(line, args...);
		}

		void __prli_assert(__prlt_bool condition, __prlt_uint32 line) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_DEBUG_OP]);
			if (!condition._v)
			{
				PREDA_CALL(DebugAssertionFailure, line._v);
				preda_exception::throw_exception("assertion failure", prlrt::ExceptionType::AssertionFailure);
			}
		}

		template<typename ...Args>
		void __prli_assert(__prlt_bool condition, uint32_t line, const char *typeExportName, bool first_arg, Args &&...args) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_DEBUG_OP]);
			if (!condition._v)
			{
				uint8_t buffer = first_arg;
				PREDA_CALL(DebugPrintBufferAppendSerializedData, typeExportName, &buffer, 1);
				__prli_assert(condition, line, args...);
			}
		}

		template<typename TFirstArg, typename ...Args>
		void __prli_assert(__prlt_bool condition, uint32_t line, const char *typeExportName, TFirstArg &&first_arg, Args &&...args) const
		{
			if (!condition._v)
			{
				std::vector<uint8_t> buffer(first_arg.get_serialize_size());
				first_arg.serialize_out(&buffer[0], true);
				PREDA_CALL(DebugPrintBufferAppendSerializedData, typeExportName, &buffer[0], (uint32_t)buffer.size());
				__prli_assert(condition, line, args...);
			}
		}
	};

}
