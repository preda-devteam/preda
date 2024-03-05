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
			memset(data, 0, fixed_size_in_bytes::value);
		}

		fixed_size_value_type(const this_type &rhs)
		{
			burn_gas((uint64_t)gas_costs[PRDOP_ABH_ASSIGN]);
			memcpy(data, rhs.data, fixed_size_in_bytes::value);
		}

		void operator =(const this_type &rhs)
		{
			burn_gas((uint64_t)gas_costs[PRDOP_ABH_ASSIGN]);
			memcpy(data, rhs.data, fixed_size_in_bytes::value);
		}

		__prlt_bool operator ==(const fixed_size_value_type<LEN, TYPE_IDENTIFIER_ENUM> &rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_ABH_OP_SIMPLE]);
			return memcmp(data, rhs.data, fixed_size_in_bytes::value) == 0;
		}

		__prlt_bool operator !=(const fixed_size_value_type<LEN, TYPE_IDENTIFIER_ENUM> &rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_ABH_OP_SIMPLE]);
			return memcmp(data, rhs.data, fixed_size_in_bytes::value) != 0;
		}

		__prlt_bool operator <(const fixed_size_value_type<LEN, TYPE_IDENTIFIER_ENUM> &rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_ABH_OP_SIMPLE]);
			return memcmp(data, rhs.data, fixed_size_in_bytes::value) < 0;
		}

		__prlt_bool operator >(const fixed_size_value_type<LEN, TYPE_IDENTIFIER_ENUM> &rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_ABH_OP_SIMPLE]);
			return memcmp(data, rhs.data, fixed_size_in_bytes::value) > 0;
		}

		__prlt_bool operator <=(const fixed_size_value_type<LEN, TYPE_IDENTIFIER_ENUM> &rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_ABH_OP_SIMPLE]);
			return memcmp(data, rhs.data, fixed_size_in_bytes::value) <= 0;
		}

		__prlt_bool operator >=(const fixed_size_value_type<LEN, TYPE_IDENTIFIER_ENUM> &rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_ABH_OP_SIMPLE]);
			return memcmp(data, rhs.data, fixed_size_in_bytes::value) >= 0;
		}

		serialize_size_type get_serialize_size() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_SIZE]);
			return fixed_size_in_bytes::value;
		}

		void serialize_out(uint8_t *buffer, bool for_debug) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_OUT_STATIC] + (uint64_t)gas_costs[PRDOP_SERIALIZE_DYNAMIC] * fixed_size_in_bytes::value);
			memcpy(buffer, data, fixed_size_in_bytes::value);
		}

		bool map_from_serialized_data(uint8_t *&buffer, serialize_size_type &bufferSize, bool bDeep)
		{
			if (bufferSize < LEN)
				return false;
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_MAP_STATIC] + (uint64_t)gas_costs[PRDOP_SERIALIZE_DYNAMIC] * fixed_size_in_bytes::value);
			memcpy(data, buffer, fixed_size_in_bytes::value);
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
			burn_gas((uint64_t)gas_costs[PRDOP_ABH_TYPE_TRANSFORM]);
			if (!PREDA_CALL(InitAddressFromLiteral, this, rhs))
				preda_exception::throw_exception("init address with invalid literal", prlrt::ExceptionType::InitAddressWithInvalidLiteral);
		}
		__prlt_address(const __prlt_string &rhs)
		{
			burn_gas((uint64_t)gas_costs[PRDOP_ABH_TYPE_TRANSFORM]);
			if (!PREDA_CALL(StringToAddress, this, (const char*)rhs.ptr->str.c_str(), uint32_t(rhs.ptr->str.length())))
				preda_exception::throw_exception("invalid string to address conversion", prlrt::ExceptionType::InvalidStringToAddressConversion);
		}
		__prlt_bool __prli_is_user()
		{
			burn_gas((uint64_t)gas_costs[PRDOP_ADDRESS_CHECK]);
			return PREDA_CALL(IsUserAddress, this);
		}
		__prlt_bool __prli_is_delegated()
		{
			burn_gas((uint64_t)gas_costs[PRDOP_ADDRESS_CHECK]);
			return PREDA_CALL(IsDelegatedAddress, this);
		}
		__prlt_bool __prli_is_dapp()
		{
			burn_gas((uint64_t)gas_costs[PRDOP_ADDRESS_CHECK]);
			return PREDA_CALL(IsDAppAddress, this);
		}
		__prlt_bool __prli_is_asset()
		{
			burn_gas((uint64_t)gas_costs[PRDOP_ADDRESS_CHECK]);
			return PREDA_CALL(IsAssetAddress, this);
		}
		__prlt_bool __prli_is_name()
		{
			burn_gas((uint64_t)gas_costs[PRDOP_ADDRESS_CHECK]);
			return PREDA_CALL(IsNameAddress, this);
		}
		__prlt_bool __prli_is_contract()
		{
			burn_gas((uint64_t)gas_costs[PRDOP_ADDRESS_CHECK]);
			return PREDA_CALL(IsContractAddress, this);
		}
		__prlt_bool __prli_is_custom()
		{
			burn_gas((uint64_t)gas_costs[PRDOP_ADDRESS_CHECK]);
			return PREDA_CALL(IsCustomAddress, this);
		}
		explicit operator __prlt_string() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_ABH_TYPE_TRANSFORM]);
			return __prlt_string(ToString().c_str());
		}
		std::string ToString() const
		{
			uint32_t len = PREDA_CALL(GetAddressToStringLength, data);
			uint32_t dataLen = fixed_size_in_bytes::value;
			burn_gas((uint64_t)gas_costs[PRDOP_ABH_TYPE_TRANSFORM]);
			std::vector<char> strBuf(len, '\0');
			std::vector<uint8_t> dataBuf(dataLen);
			memcpy(&dataBuf[0], data, fixed_size_in_bytes::value);
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
			burn_gas((uint64_t)gas_costs[PRDOP_ABH_TYPE_TRANSFORM]);
			if (!PREDA_CALL(InitHashFromLiteral, this, rhs))
				preda_exception::throw_exception("init hash with invalid literal", prlrt::ExceptionType::InitHashWithInvalidLiteral);
		}
		__prlt_hash(const __prlt_string &rhs)
		{
			burn_gas((uint64_t)gas_costs[PRDOP_ABH_TYPE_TRANSFORM]);
			PREDA_CALL(CalculateHash, this, (const uint8_t*)rhs.ptr->str.c_str(), uint32_t(rhs.ptr->str.length()));
		}
		explicit operator __prlt_string() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_ABH_TYPE_TRANSFORM]);
			return __prlt_string(ToString().c_str());
		}
		explicit operator __prlt_uint256() const
		{
			__prlt_uint256 ret;
			memcpy(ret._fStruct._Data, data, fixed_size_in_bytes::value);
			return ret;
		}
		std::string ToString() const
		{
			uint32_t len = PREDA_CALL(GetHashToStringLength);
			uint32_t dataLen = fixed_size_in_bytes::value;
			burn_gas((uint64_t)gas_costs[PRDOP_ABH_TYPE_TRANSFORM]);
			std::vector<char> strBuf(len + 1, '\0');
			std::vector<uint8_t> dataBuf(dataLen);
			memcpy(&dataBuf[0], data, fixed_size_in_bytes::value);
			PREDA_CALL(HashToString, &dataBuf[0], dataLen, &strBuf[0]);
			return std::string(&strBuf[0], len);
		}
		explicit operator __prlt_address()
		{
			burn_gas((uint64_t)gas_costs[PRDOP_ABH_TYPE_TRANSFORM]);
			__prlt_address result;
			PREDA_CALL(SetAsCustomAddress, result.data, data);
			return result;
		}
	};
}

using __prlt_address = prlrt::__prlt_address;
using __prlt_blob = prlrt::__prlt_blob;
using __prlt_hash = prlrt::__prlt_hash;
