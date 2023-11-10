#pragma once
#include "common.h"
#include "inttypes.h"
#include "biginttype.h"

namespace prlrt {

	struct ____token_impl {
		using id_type = __prlt_uint64;
		using amount_type = __prlt_bigint;
		id_type id = 0;
		amount_type amount = 0;
		mutable bool bSerialized;
		____token_impl()
			: id(0), bSerialized(false)
		{
		}

		~____token_impl()
		{
			if (!bSerialized && amount > amount_type(0))
			{
				PREDA_CALL(ReportOrphanToken, id._v, amount._v);
			}
		}

		id_type GetTokenId() const
		{
			return id;
		}

		amount_type GetAmount() const
		{
			return amount;
		}

		bool Transfer(____token_impl &recipient, const amount_type &transfer_amount)
		{
			if (id == 0)
				return false;
			if (recipient.id != id && recipient.id != 0)
				return false;
			if (transfer_amount < amount_type(0))
				return false;
			if (amount < transfer_amount)
				return false;

			//if (id == 0)
			//	preda_exception::throw_exception("trying to transfer from a token without token type", prlrt::ExceptionType::TokenTransfer_NoTokenType);
			//if (recipient.id != id && recipient.id != 0)
			//	preda_exception::throw_exception("trying to transfer to a token of different token type", prlrt::ExceptionType::TokenTransfer_TokenTypeMismatch);
			//if (transfer_amount < amount_type(0))
			//	preda_exception::throw_exception("trying to transfer a negative amount", prlrt::ExceptionType::TokenTransfer_NegativeAmount);
			//if (amount < transfer_amount)
			//	preda_exception::throw_exception("trying to transfer from a token without sufficient amount", prlrt::ExceptionType::TokenTransfer_InsufficientCredit);

			recipient.id = id;
			amount -= transfer_amount;
			recipient.amount += transfer_amount;

			return true;
		}

		bool TransferAll(____token_impl &recipient)
		{
			const amount_type &transfer_amount = GetAmount();
			return Transfer(recipient, transfer_amount);
		}

		serialize_size_type get_serialize_size() const
		{
			return id.get_serialize_size() + amount.get_serialize_size();
		}

		void serialize_out(uint8_t *buffer, bool for_debug) const
		{
			if (!for_debug && bSerialized)
				preda_exception::throw_exception("trying to serialize a token twice", prlrt::ExceptionType::TokenDoubleSerialization);

			id.serialize_out(buffer, for_debug);
			static_assert(id_type::is_fixed_size::value, "___token_impl::id_type is not fixed_size_type");
			buffer += id_type::fixed_size_in_bytes::value;
			amount.serialize_out(buffer, for_debug);

			if (!for_debug)
			{
				*const_cast<amount_type*>(&amount) = amount_type(0);
				if (!g_inRelaySerialization)
					bSerialized = true;
			}
		}

		bool map_from_serialized_data(uint8_t *&buffer, serialize_size_type &bufferSize, bool bDeep)
		{
			if (!id.map_from_serialized_data(buffer, bufferSize, bDeep))
				return false;
			if (!amount.map_from_serialized_data(buffer, bufferSize, bDeep))
				return false;
			return true;
		}
	};

	struct __prlt_token {
		using implementation_type = ____token_impl;
		using smartptr_type = std::shared_ptr<implementation_type>;
		using is_value_type = std::false_type;
		using is_fixed_size = std::false_type;
		using fixed_size_in_bytes = std::integral_constant<serialize_size_type, 0>;		// doesn't matter
		using type_identifier_type = simple_type_type_identifier<type_identifier_enum::___token>;
		static constexpr uint32_t get_type_identifier_size()
		{
			return type_identifier_type::value.length();
		}
		static constexpr const uint8_t* get_type_identifier_buffer()
		{
			return type_identifier_type::value.data;
		}

		smartptr_type ptr;
		__prlt_token()
			:ptr(new implementation_type) {}											// always new an empty vector here in constructor is a waste, but this could be improved if transpiler ignores unused variables when parsing
		__prlt_token(const smartptr_type &p)
			: ptr(p) {}
		void operator=(const smartptr_type &p)
		{
			ptr = p;
		}
		__prlt_token(const __prlt_token &rhs)
		{
			ptr = rhs.ptr;
		}
		void operator=(const __prlt_token &rhs)
		{
			ptr = rhs.ptr;
		}

		// token interface
		implementation_type::id_type __prli_get_id() const
		{
			return ptr->GetTokenId();
		}

		implementation_type::amount_type __prli_get_amount() const
		{
			return ptr->GetAmount();
		}

		__prlt_bool __prli_transfer(__prlt_token recipient, const implementation_type::amount_type &transfer_amount)
		{
			return ptr->Transfer(*recipient.ptr.get(), transfer_amount);
		}

		__prlt_bool __prli_transfer_all(__prlt_token recipient)
		{
			return ptr->TransferAll(*recipient.ptr.get());
		}

		// serialization-related interface
		serialize_size_type get_serialize_size() const
		{
			return ptr->get_serialize_size();
		}

		void serialize_out(uint8_t *buffer, bool for_debug) const
		{
			ptr->serialize_out(buffer, for_debug);
		}

		bool map_from_serialized_data(uint8_t *&buffer, serialize_size_type &bufferSize, bool bDeep)
		{
			return ptr->map_from_serialized_data(buffer, bufferSize, bDeep);
		}
	};

}

using __prlt_token = prlrt::__prlt_token;

namespace prlrt {
	__prlt_token mint(____token_impl::id_type id, ____token_impl::amount_type amount)
	{
		__prlt_token ret;
		ret.ptr->id = id;
		ret.ptr->amount = amount;
		return ret;
	}
	void burn(__prlt_token token)
	{
		token.ptr->id = 0;
		token.ptr->amount = 0;
	}
}