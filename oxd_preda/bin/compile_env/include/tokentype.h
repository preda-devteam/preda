#pragma once
#include "common.h"
#include "inttypes.h"
#include "biginttype.h"
#include "gascost.h"
#include "stringtype.h"

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
			disable_burn_gas();
			if (!bSerialized && amount > amount_type(0))
			{
				PREDA_CALL(ReportOrphanToken, id._v, amount._v);
			}
			enable_burn_gas();
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
			if (id._v == 0)
				return false;
			if (recipient.id._v != id._v && recipient.id._v != 0)
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

		void Deposit()
		{
			PREDA_CALL(DepositToken, id._v, amount._v);
			amount = amount_type(0);
		}

		static __prlt_string IdToSymbol(id_type id)
		{
			uint32_t len = PREDA_CALL(TokenIdToSymbolLength, id._v);
			char buf[sizeof(id) + 1];
			memcpy(buf, &id, len);
			buf[len] = 0;
			return __prlt_string(buf);
		}

		static id_type SymbolToId(const __prlt_string &symbol)
		{
			return PREDA_CALL(TokenSymbolToId, symbol.get_c_str());
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

		bool map_from_serialized_data(const uint8_t *&buffer, serialize_size_type &bufferSize, bool bDeep)
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
			burn_gas((uint64_t)gas_costs[PRDOP_TOKEN_ASSIGN]);
			ptr = rhs.ptr;
		}

		// token interface
		implementation_type::id_type __prli_get_id() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_TOKEN_ID]);
			return ptr->GetTokenId();
		}

		implementation_type::amount_type __prli_get_amount() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_TOKEN_AMOUNT]);
			return ptr->GetAmount();
		}

		__prlt_bool __prli_transfer(__prlt_token recipient, const implementation_type::amount_type &transfer_amount)
		{
			burn_gas((uint64_t)gas_costs[PRDOP_TOKEN_TRANSFER]);
			return ptr->Transfer(*recipient.ptr.get(), transfer_amount);
		}

		__prlt_bool __prli_transfer_all(__prlt_token recipient)
		{
			burn_gas((uint64_t)gas_costs[PRDOP_TOKEN_TRANSFERALL]);
			return ptr->TransferAll(*recipient.ptr.get());
		}

		void __prli_deposit() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_TOKEN_DEPOSIT]);
			return ptr->Deposit();
		}

		static __prlt_string __prli_id_to_symbol(implementation_type::id_type id)
		{
			return implementation_type::IdToSymbol(id);
		}

		static implementation_type::id_type __prli_symbol_to_id(const __prlt_string &symbol)
		{
			return implementation_type::SymbolToId(symbol);
		}

		// serialization-related interface
		serialize_size_type get_serialize_size() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_SIZE]);
			return ptr->get_serialize_size();
		}

		void serialize_out(uint8_t *buffer, bool for_debug) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_OUT_STATIC]);
			ptr->serialize_out(buffer, for_debug);
		}

		bool map_from_serialized_data(const uint8_t *&buffer, serialize_size_type &bufferSize, bool bDeep)
		{
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_MAP_STATIC]);
			return ptr->map_from_serialized_data(buffer, bufferSize, bDeep);
		}
	};

}

using __prlt_token = prlrt::__prlt_token;

namespace prlrt {
	__prlt_token mint(____token_impl::id_type id, ____token_impl::amount_type amount)
	{
		__prlt_token ret;
		if (amount.IsNegative())
		{
			return ret;
		}
		bool allowed = PREDA_CALL(AllowedToMint, id._v);
		if (allowed)
		{
			ret.ptr->id = id;
			ret.ptr->amount = amount;
			PREDA_CALL(TokenMinted, id._v, amount._v);
		}
		return ret;
	}
	bool burn(__prlt_token token)
	{
		bool allowed = PREDA_CALL(AllowedToMint, token.__prli_get_id()._v);
		if (!allowed)
			return false;

		PREDA_CALL(TokenBurnt, token.__prli_get_id()._v, token.__prli_get_amount()._v);
		token.ptr->id = 0;
		token.ptr->amount = 0;
		return true;
	}
}