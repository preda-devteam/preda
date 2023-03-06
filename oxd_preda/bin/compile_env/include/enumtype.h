#pragma once
#include <cstdint>

namespace prlrt {

	using enum_base_type = uint16_t;

	template<typename T_Enum, enum_base_type numEntry>
	struct enum_wrapper {
		using implementation_type = T_Enum;
		using is_value_type = std::true_type;
		using is_fixed_size = std::true_type;
		using fixed_size_in_bytes = std::integral_constant<serialize_size_type, serialize_size_type(sizeof(enum_base_type))>;
		using type_identifier_type = ____enum_type_type_identifier<enum_base_type, numEntry>;
		static constexpr uint32_t get_type_identifier_size()
		{
			return type_identifier_type::value.length();
		}

		static constexpr const uint8_t* get_type_identifier_buffer()
		{
			return type_identifier_type::value.data;
		}

		implementation_type v;

		enum_wrapper()
			: v(T_Enum(0))
		{
		}
		enum_wrapper(const T_Enum &rhs)
			: v(rhs)
		{
			if (enum_base_type(v) >= numEntry)
			{
				throw preda_exception("enum value overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::EnumValueOverflow);
			}
		}
		enum_wrapper(const enum_wrapper<T_Enum, numEntry> &rhs)
			: v(rhs.v)
		{
			if (enum_base_type(v) >= numEntry)
			{
				throw preda_exception("enum value overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::EnumValueOverflow);
			}
		}

		void operator = (const enum_wrapper<T_Enum, numEntry> &rhs)
		{
			v = rhs.v;
		}

		__prlt_bool operator == (const enum_wrapper &T)
		{
			return v == T.v;
		}
		__prlt_bool operator != (const enum_wrapper &T)
		{
			return v != T.v;
		}
		__prlt_bool operator == (const implementation_type &T)
		{
			return v == T;
		}
		__prlt_bool operator != (const implementation_type &T)
		{
			return v != T;
		}

		constexpr serialize_size_type get_serialize_size() const
		{
			return sizeof(enum_base_type);
		}

		void serialize_out(uint8_t *buffer, bool for_debug) const
		{
			*(enum_base_type*)buffer = (enum_base_type)v;
		}

		bool map_from_serialized_data(uint8_t *&buffer, serialize_size_type &bufferSize, bool bDeep)
		{
			if (bufferSize < serialize_size_type(sizeof(enum_base_type)))
				return false;
			v = (implementation_type)(*(enum_base_type*)buffer);
			if (enum_base_type(v) >= numEntry)
			{
				throw preda_exception("enum value overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::EnumValueOverflow);
			}
			buffer += serialize_size_type(sizeof(enum_base_type));
			bufferSize -= serialize_size_type(sizeof(enum_base_type));
			return true;
		}
	};

}
