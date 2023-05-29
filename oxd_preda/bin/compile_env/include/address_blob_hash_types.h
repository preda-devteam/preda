#pragma once
#include <type_traits>
#include "common.h"
#include "inttypes.h"
#include "stringtype.h"
#include "exceptions.h"

namespace prlrt {

	template <serialize_size_type LEN, type_identifier_enum TYPE_IDENTIFIER_ENUM>
	struct fixed_size_value_type {
		using this_type = fixed_size_value_type<LEN, TYPE_IDENTIFIER_ENUM>;
		using is_value_type = std::true_type;
		using is_fixed_size = std::true_type;
		using fixed_size_in_bytes = std::integral_constant<serialize_size_type, LEN>;
		using type_identifier_type = simple_type_type_identifier<TYPE_IDENTIFIER_ENUM>;
		static constexpr uint32_t get_type_identifier_size()
		{
			return type_identifier_type::value.length();
		}

		static constexpr const uint8_t* get_type_identifier_buffer()
		{
			return type_identifier_type::value.data;
		}

		uint8_t data[LEN];

		fixed_size_value_type()
		{
			memset(data, 0, sizeof(data));
		}

		fixed_size_value_type(const this_type &rhs)
		{
			memcpy(data, rhs.data, sizeof(data));
		}

		void operator =(const this_type &rhs)
		{
			memcpy(data, rhs.data, sizeof(data));
		}

		__prlt_bool operator ==(const fixed_size_value_type<LEN, TYPE_IDENTIFIER_ENUM> &rhs) const
		{
			return memcmp(data, rhs.data, sizeof(data)) == 0;
		}

		__prlt_bool operator !=(const fixed_size_value_type<LEN, TYPE_IDENTIFIER_ENUM> &rhs) const
		{
			return memcmp(data, rhs.data, sizeof(data)) != 0;
		}

		__prlt_bool operator <(const fixed_size_value_type<LEN, TYPE_IDENTIFIER_ENUM> &rhs) const
		{
			return memcmp(data, rhs.data, sizeof(data)) < 0;
		}

		__prlt_bool operator >(const fixed_size_value_type<LEN, TYPE_IDENTIFIER_ENUM> &rhs) const
		{
			return memcmp(data, rhs.data, sizeof(data)) > 0;
		}

		__prlt_bool operator <=(const fixed_size_value_type<LEN, TYPE_IDENTIFIER_ENUM> &rhs) const
		{
			return memcmp(data, rhs.data, sizeof(data)) <= 0;
		}

		__prlt_bool operator >=(const fixed_size_value_type<LEN, TYPE_IDENTIFIER_ENUM> &rhs) const
		{
			return memcmp(data, rhs.data, sizeof(data)) >= 0;
		}

		constexpr serialize_size_type get_serialize_size() const
		{
			return sizeof(data);
		}

		void serialize_out(uint8_t *buffer, bool for_debug) const
		{
			memcpy(buffer, data, sizeof(data));
		}

		bool map_from_serialized_data(uint8_t *&buffer, serialize_size_type &bufferSize, bool bDeep)
		{
			if (bufferSize < LEN)
				return false;
			memcpy(data, buffer, sizeof(data));
			buffer += serialize_size_type(LEN);
			bufferSize -= serialize_size_type(LEN);
			return true;
		}
	};

	struct __prlt_address : public fixed_size_value_type<36, type_identifier_enum::___address>
	{
		__prlt_address() {}
		__prlt_address(const char *rhs)
		{
			if (!PREDA_CALL(InitAddressFromLiteral, this, rhs))
				throw preda_exception("init address with invalid literal", prlrt::ExceptionType::InitAddressWithInvalidLiteral);
		}
		__prlt_address(const __prlt_string &rhs)
		{
			if (!PREDA_CALL(StringToAddress, this, (const char*)rhs.ptr->str.c_str(), uint32_t(rhs.ptr->str.length())))
				throw preda_exception("invalid string to address conversion", prlrt::ExceptionType::InvalidStringToAddressConversion);
		}
		__prlt_bool __prli_is_user()
		{
			return PREDA_CALL(IsUserAddress, this);
		}
		__prlt_bool __prli_is_delegated()
		{
			return PREDA_CALL(IsDelegatedAddress, this);
		}
		__prlt_bool __prli_is_dapp()
		{
			return PREDA_CALL(IsDAppAddress, this);
		}
		__prlt_bool __prli_is_asset()
		{
			return PREDA_CALL(IsAssetAddress, this);
		}
		__prlt_bool __prli_is_name()
		{
			return PREDA_CALL(IsNameAddress, this);
		}
		__prlt_bool __prli_is_domain()
		{
			return PREDA_CALL(IsDomainAddress, this);
		}
		__prlt_bool __prli_is_contract()
		{
			return PREDA_CALL(IsContractAddress, this);
		}
		__prlt_bool __prli_is_custom()
		{
			return PREDA_CALL(IsCustomAddress, this);
		}
		explicit operator __prlt_string() const
		{
			return __prlt_string(ToString().c_str());
		}
		std::string ToString() const
		{
			uint32_t len = PREDA_CALL(GetAddressToStringLength, data);
			uint32_t dataLen = get_serialize_size();
			std::vector<char> strBuf(len, '\0');
			std::vector<uint8_t> dataBuf(dataLen);
			serialize_out(&dataBuf[0], true);
			PREDA_CALL(AddressToString, &dataBuf[0], dataLen, &strBuf[0]);
			return std::string(&strBuf[0], len);
		}
		void SetAsContract(uint64_t contract_id)
		{
			PREDA_CALL(SetAsContractAddress, &data[0], contract_id);
		}
	};

	struct  __prlt_blob : public fixed_size_value_type<36, type_identifier_enum::___blob>
	{
	};

	struct __prlt_hash : public fixed_size_value_type<32, type_identifier_enum::___hash>
	{
		__prlt_hash() {}
		__prlt_hash(const char *rhs)
		{
			if (!PREDA_CALL(InitHashFromLiteral, this, rhs))
				throw preda_exception("init hash with invalid literal", prlrt::ExceptionType::InitHashWithInvalidLiteral);
		}
		__prlt_hash(const __prlt_string &rhs)
		{
			PREDA_CALL(CalculateHash, this, (const uint8_t*)rhs.ptr->str.c_str(), uint32_t(rhs.ptr->str.length()));
		}
		explicit operator __prlt_string() const
		{
			return __prlt_string(ToString().c_str());
		}
		std::string ToString() const
		{
			uint32_t len = PREDA_CALL(GetHashToStringLength);
			uint32_t dataLen = get_serialize_size();
			std::vector<char> strBuf(len + 1, '\0');
			std::vector<uint8_t> dataBuf(dataLen);
			serialize_out(&dataBuf[0], true);
			PREDA_CALL(HashToString, &dataBuf[0], dataLen, &strBuf[0]);
			return std::string(&strBuf[0], len);
		}
		explicit operator __prlt_address()
		{
			__prlt_address result;
			PREDA_CALL(SetAsCustomAddress, result.data, data);
			return result;
		}
	};
}

using __prlt_address = prlrt::__prlt_address;
using __prlt_blob = prlrt::__prlt_blob;
using __prlt_hash = prlrt::__prlt_hash;
