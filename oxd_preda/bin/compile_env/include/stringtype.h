#pragma once
#include "common.h"
#include "inttypes.h"
#include "floattypes.h"
#include <string>

namespace prlrt {

	struct string_impl {
		using length_type = uint16_t;
		std::string str;
		static_assert(sizeof(length_type) == 2, "string length type changed! This could cause incompatibility with existing data");

		void test_length_overflow()
		{
			if (length_type(str.length()) != str.length())
				throw preda_exception("string length overflow " + std::string(__FUNCTION__), prlrt::ExceptionType::StringLengthOverflow);
		}

		string_impl()
		{
		}

		string_impl(const char *p)
			: str(p)
		{
			test_length_overflow();
		}

		template<typename T>
		void convert_from_uint(const ____uint<T> &rhs)
		{
			// TODO: implement our own version to avoid std dependency.
			str = std::to_string(rhs._v);
		}

		template<typename T>
		void convert_from_int(const ____int<T> &rhs)
		{
			// TODO: implement our own version to avoid std dependency.
			str = std::to_string(rhs._v);
		}
		template<short Size>
		void convert_from_ulongint(const ____ulongint<Size> &rhs)
		{
			str = rhs.ToString();
		}
		template<short Size>
		void convert_from_longint(const ____longint<Size> &rhs)
		{
			str = rhs.ToString();
		}

		void convert_from_bigint(const __prlt_bigint &rhs)
		{
			uint32_t l = PREDA_CALL(BigintGetStringLength, rhs._v);
			str.resize(l);
			PREDA_CALL(BigintToString, rhs._v, str.data(), l);
		}
		template<unsigned int bitWidth>
		void convert_from_float(const ____float<bitWidth> &rhs)
		{
			str = rhs.ToString();
		}
		bool operator ==(const string_impl &rhs) const
		{
			return str == rhs.str;
		}

		bool operator !=(const string_impl &rhs) const
		{
			return str != rhs.str;
		}

		bool operator <(const string_impl &rhs) const
		{
			return str <= rhs.str;
		}

		bool operator >(const string_impl &rhs) const
		{
			return str >= rhs.str;
		}

		bool operator <=(const string_impl &rhs) const
		{
			return str <= rhs.str;
		}

		bool operator >=(const string_impl &rhs) const
		{
			return str >= rhs.str;
		}

		void set(const string_impl &rhs)
		{
			str = rhs.str;
			test_length_overflow();
		}

		void append(const string_impl &rhs)
		{
			str += rhs.str;
			test_length_overflow();
		}

		serialize_size_type get_serialize_size() const
		{
			return serialize_size_type(sizeof(length_type)) + serialize_size_type(length());
		}

		length_type length() const
		{
			return length_type(str.length());
		}

		void serialize_out(uint8_t *buffer, bool for_debug) const
		{
			*(length_type *)buffer = length_type(length());
			buffer += sizeof(length_type);
			if (length() > 0)
				memcpy(buffer, str.c_str(), length());
		}

		bool map_from_serialized_data(uint8_t *&buffer, serialize_size_type &bufferSize, bool bDeep)
		{
			if (bufferSize < serialize_size_type(sizeof(length_type)))
				return false;
			length_type len = *(length_type *)buffer;
			buffer += sizeof(len);
			bufferSize -= serialize_size_type(sizeof(len));

			if (len > 0)
			{
				if (bufferSize < serialize_size_type(len))
					return false;
				str.resize(len);
				memcpy(&str[0], buffer, len);
				buffer += len;
				bufferSize -= serialize_size_type(len);
			}

			return true;
		}
	};

	struct __prlt_string {
		using implementation_type = string_impl;
		using smartptr_type = std::shared_ptr<implementation_type>;
		using is_value_type = std::false_type;
		using is_fixed_size = std::false_type;
		using fixed_size_in_bytes = std::integral_constant<serialize_size_type, 0>;		// doesn't matter
		using type_identifier_type = simple_type_type_identifier<type_identifier_enum::___string>;
		static constexpr uint32_t get_type_identifier_size()
		{
			return type_identifier_type::value.length();
		}
		static constexpr const uint8_t* get_type_identifier_buffer()
		{
			return type_identifier_type::value.data;
		}

		smartptr_type ptr;
		__prlt_string()
			:ptr(new implementation_type) {}											// always new an empty vector here in constructor is a waste, but this could be improved if transpiler ignores unused variables when parsing
		__prlt_string(const smartptr_type &p)
			: ptr(p) {}
		void operator=(const smartptr_type &p)
		{
			ptr = p;
		}
		__prlt_string(const __prlt_string &rhs)
		{
			ptr = rhs.ptr;
		}
		template<typename T>
		__prlt_string(const ____uint<T> &rhs)
			: ptr(new implementation_type)
		{
			ptr->convert_from_uint(rhs);
		}
		template<typename T>
		__prlt_string(const ____int<T> &rhs)
			: ptr(new implementation_type)
		{
			ptr->convert_from_int(rhs);
		}

		template<short Size>
		__prlt_string(const ____ulongint<Size> &rhs)
			: ptr(new implementation_type)
		{
			ptr->convert_from_ulongint(rhs);
		}
		template<short Size>
		__prlt_string(const ____longint<Size> &rhs)
			: ptr(new implementation_type)
		{
			ptr->convert_from_longint(rhs);
		}

		__prlt_string(const __prlt_bigint &rhs)
			: ptr(new implementation_type)
		{
			ptr->convert_from_bigint(rhs);
		}
		template<unsigned int bitWidth>
		__prlt_string(const ____float<bitWidth> &rhs)
			: ptr(new implementation_type)
		{
			ptr->convert_from_float(rhs);
		}
		void operator=(const __prlt_string &rhs)
		{
			ptr = rhs.ptr;
		}
		explicit __prlt_string(const char *p)
			: ptr(new implementation_type(p)) {}

		// string interface
		__prlt_bool operator ==(const __prlt_string &rhs) const
		{
			return ptr->operator ==(*rhs.ptr.get());
		}

		__prlt_bool operator !=(const __prlt_string &rhs) const
		{
			return ptr->operator !=(*rhs.ptr.get());
		}

		__prlt_bool operator <(const __prlt_string &rhs) const
		{
			return ptr->operator <(*rhs.ptr.get());
		}

		__prlt_bool operator >(const __prlt_string &rhs) const
		{
			return ptr->operator >(*rhs.ptr.get());
		}

		__prlt_bool operator <=(const __prlt_string &rhs) const
		{
			return ptr->operator <=(*rhs.ptr.get());
		}

		__prlt_bool operator >=(const __prlt_string &rhs) const
		{
			return ptr->operator >=(*rhs.ptr.get());
		}

		void __prli_set(const __prlt_string &rhs)
		{
			ptr->set(*rhs.ptr.get());
		}

		void __prli_append(const __prlt_string &rhs)
		{
			ptr->append(*rhs.ptr.get());
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

using __prlt_string = prlrt::__prlt_string;
