#pragma once

#include <vector>
#include "common.h"
#include "exceptions.h"

#define WRAP_SIMPLE_BINARY_OPERATOR(returnType, oper)\
	returnType operator oper(const this_type &rhs) const\
	{\
		return returnType(_v oper rhs._v);\
	}

#define EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(oper)\
	void operator oper##=(const this_type &rhs)\
	{\
		*this = *this oper rhs;\
	}

#define FORWARD_POST_INC_DEC_TO_PRE_INC_DEC\
	void operator++(int)\
	{\
		operator++();\
	}\
	void operator--(int)\
	{\
		operator--();\
	}

namespace prlrt {

	struct __prlt_bool {
		using this_type = __prlt_bool;
		using internal_type = bool;
		using is_value_type = std::true_type;
		using is_fixed_size = std::true_type;
		using fixed_size_in_bytes = std::integral_constant<serialize_size_type, 1>;
		using type_identifier_type = simple_type_type_identifier<type_identifier_enum::___bool>;
		static constexpr uint32_t get_type_identifier_size()
		{
			return type_identifier_type::value.length();
		}

		static constexpr const uint8_t* get_type_identifier_buffer()
		{
			return type_identifier_type::value.data;
		}

		internal_type _v;
		__prlt_bool() { _v = false; }
		__prlt_bool(bool x) { _v = x; }

		operator bool() const
		{
			return _v;
		}

		void operator=(const this_type &rhs)
		{
			_v = rhs._v;
		}

		__prlt_bool operator!() const
		{
			return __prlt_bool(!_v);
		}

		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, &&);
		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, || );
		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, == );
		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, != );

		constexpr serialize_size_type get_serialize_size() const
		{
			return sizeof(this_type);
		}

		void serialize_out(uint8_t *buffer, bool for_debug) const
		{
			*(this_type*)buffer = _v ? 1 : 0;
		}

		bool map_from_serialized_data(uint8_t *&buffer, serialize_size_type &bufferSize, bool bDeep)
		{
			if (bufferSize < serialize_size_type(sizeof(internal_type)))
				return false;
			_v = *(internal_type*)buffer;
			buffer += serialize_size_type(sizeof(internal_type));
			bufferSize -= serialize_size_type(sizeof(internal_type));
			return true;
		}
	};

	template<typename TUint>
	constexpr TUint ____get_max_value_of_uint()
	{
		TUint ret = 0;
		for (size_t i = 0; i < sizeof(TUint) * 8; i++)
			ret = (ret << 1) | 1;
		return ret;
	}

	template<typename TInt>
	constexpr TInt ____get_max_value_of_int()
	{
		TInt ret = 0;
		for (size_t i = 0; i < sizeof(TInt) * 8 - 1; i++)
			ret = ret * 2 + 1;
		return ret;
	}

	template<typename TInt>
	constexpr TInt ____get_min_value_of_int()
	{
		return -____get_max_value_of_int<TInt>() - 1;
	}

	template <typename TUint> constexpr type_identifier_enum ____get_type_identifier_enum_of_int_type();
	template <> constexpr type_identifier_enum ____get_type_identifier_enum_of_int_type<uint64_t>() { return type_identifier_enum::___uint64; }
	template <> constexpr type_identifier_enum ____get_type_identifier_enum_of_int_type<uint32_t>() { return type_identifier_enum::___uint32; }
	template <> constexpr type_identifier_enum ____get_type_identifier_enum_of_int_type<uint16_t>() { return type_identifier_enum::___uint16; }
	template <> constexpr type_identifier_enum ____get_type_identifier_enum_of_int_type<uint8_t>() { return type_identifier_enum::___uint8; }
	template <> constexpr type_identifier_enum ____get_type_identifier_enum_of_int_type<int64_t>() { return type_identifier_enum::___int64; }
	template <> constexpr type_identifier_enum ____get_type_identifier_enum_of_int_type<int32_t>() { return type_identifier_enum::___int32; }
	template <> constexpr type_identifier_enum ____get_type_identifier_enum_of_int_type<int16_t>() { return type_identifier_enum::___int16; }
	template <> constexpr type_identifier_enum ____get_type_identifier_enum_of_int_type<int8_t>() { return type_identifier_enum::___int8; }

	template<typename T_internal>
	struct ____int;
	template<short Size>
	struct ____longint;
	template<short Size>
	struct ____ulongint;
	template<typename T_internal>
	struct ____uint {
		using this_type = ____uint<T_internal>;
		using internal_type = T_internal;
		using max_value = std::integral_constant<internal_type, ____get_max_value_of_uint<internal_type>()>;
		using min_value = std::integral_constant<internal_type, 0>;
		using is_value_type = std::true_type;
		using is_fixed_size = std::true_type;
		using fixed_size_in_bytes = std::integral_constant<serialize_size_type, serialize_size_type(sizeof(internal_type))>;
		using type_identifier_type = simple_type_type_identifier<____get_type_identifier_enum_of_int_type<T_internal>()>;
		static constexpr uint32_t get_type_identifier_size()
		{
			return type_identifier_type::value.length();
		}

		static constexpr const uint8_t* get_type_identifier_buffer()
		{
			return type_identifier_type::value.data;
		}

		internal_type _v;
		____uint() { _v = 0; }
		____uint(internal_type x) { _v = x; }

		void operator=(const this_type &rhs)
		{
			_v = rhs._v;
		}

		void operator++()
		{
			if (_v == max_value::value)
			{
				throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			_v++;
		}

		void operator--()
		{
			if (_v == min_value::value)
			{
				throw preda_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			}
			_v--;
		}

		FORWARD_POST_INC_DEC_TO_PRE_INC_DEC;

		this_type operator~() const
		{
			return this_type(~_v);
		}

		this_type operator+(const this_type &rhs) const
		{
			if (max_value::value - _v < rhs._v)
			{
				throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			return this_type(_v + rhs._v);
		}

		this_type operator-(const this_type &rhs) const
		{
			if (_v < rhs._v)
			{
				throw preda_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			}
			return this_type(_v - rhs._v);
		}

		this_type operator*(const this_type &rhs) const
		{
			if (max_value::value / _v < rhs._v)
			{
				throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			return this_type(_v * rhs._v);
		}

		this_type operator/(const this_type &rhs) const
		{
			if (rhs._v == 0)
			{
				throw preda_exception("divide by zero in " + std::string(__FUNCTION__), prlrt::ExceptionType::DividedByZero);
			}
			return this_type(_v / rhs._v);
		}

		this_type operator%(const this_type &rhs) const
		{
			if (rhs._v == 0)
			{
				throw preda_exception("divide by zero in " + std::string(__FUNCTION__), prlrt::ExceptionType::DividedByZero);
			}
			return this_type(_v % rhs._v);
		}

		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(+);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(-);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(*);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(/ );
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(%);

		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, == );
		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, != );
		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, <= );
		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, >= );
		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, < );
		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, > );

		WRAP_SIMPLE_BINARY_OPERATOR(this_type, &);
		WRAP_SIMPLE_BINARY_OPERATOR(this_type, ^);
		WRAP_SIMPLE_BINARY_OPERATOR(this_type, | );

		this_type operator <<(const this_type &rhs) const
		{
			if (rhs._v >= internal_type(sizeof(internal_type) * 8))
				return this_type(internal_type(0));
			return this_type(_v << rhs._v);
		}
		this_type operator >>(const this_type& rhs) const
		{
			if (rhs._v >= internal_type(sizeof(internal_type) * 8))
				return this_type(internal_type(0));
			return this_type(_v >> rhs._v);
		}

		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(&);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(^);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(| );
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(<< );
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(>> );

		template<typename T_OtherInternal>
		explicit operator ____uint<T_OtherInternal>() const
		{
			if (sizeof(T_OtherInternal) >= sizeof(internal_type))
				return ____uint<T_OtherInternal>(T_OtherInternal(_v));
			if (_v > internal_type(____uint<T_OtherInternal>::max_value::value))
			{
				throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			return ____uint<T_OtherInternal>(T_OtherInternal(_v));
		}

		template<typename T_OtherInternal>
		explicit operator ____int<T_OtherInternal>() const
		{
			if (sizeof(T_OtherInternal) > sizeof(internal_type))
				return ____int<T_OtherInternal>(T_OtherInternal(_v));
			if (_v > internal_type(____int<T_OtherInternal>::max_value::value))
			{
				throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			return ____int<T_OtherInternal>(T_OtherInternal(_v));
		}

		constexpr serialize_size_type get_serialize_size() const
		{
			return sizeof(this_type);
		}

		void serialize_out(uint8_t *buffer, bool for_debug) const
		{
			*(this_type*)buffer = *this;
		}

		bool map_from_serialized_data(uint8_t *&buffer, serialize_size_type &bufferSize, bool bDeep)
		{
			if (bufferSize < serialize_size_type(sizeof(internal_type)))
				return false;
			_v = *(internal_type*)buffer;
			buffer += serialize_size_type(sizeof(internal_type));
			bufferSize -= serialize_size_type(sizeof(internal_type));
			return true;
		}
	};

	template<typename T_internal>
	struct ____int {
		using this_type = ____int<T_internal>;
		using internal_type = T_internal;
		using max_value = std::integral_constant<internal_type, ____get_max_value_of_int<internal_type>()>;
		using min_value = std::integral_constant<internal_type, ____get_min_value_of_int<internal_type>()>;
		using is_value_type = std::true_type;
		using is_fixed_size = std::true_type;
		using fixed_size_in_bytes = std::integral_constant<serialize_size_type, serialize_size_type(sizeof(internal_type))>;
		using type_identifier_type = simple_type_type_identifier<____get_type_identifier_enum_of_int_type<T_internal>()>;
		static constexpr uint32_t get_type_identifier_size()
		{
			return type_identifier_type::value.length();
		}

		static constexpr const uint8_t* get_type_identifier_buffer()
		{
			return type_identifier_type::value.data;
		}

		internal_type _v;
		____int() { _v = 0; }
		____int(internal_type x) { _v = x; }

		void operator=(const this_type &rhs)
		{
			_v = rhs._v;
		}

		void operator++()
		{
			if (_v == max_value::value)
			{
				throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			_v++;
		}

		void operator--()
		{
			if (_v == min_value::value)
			{
				throw preda_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			}
			_v--;
		}

		FORWARD_POST_INC_DEC_TO_PRE_INC_DEC;

		this_type operator-() const
		{
			if (_v == min_value::value)
			{
				throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			return this_type(-_v);
		}

		this_type operator+(const this_type &rhs) const
		{
			if ((_v > 0 && max_value::value - _v < rhs._v)
				|| (_v < 0 && min_value::value - _v > rhs._v))
			{
				throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			return this_type(_v + rhs._v);
		}

		this_type operator-(const this_type &rhs) const
		{
			if ((rhs._v > 0 && _v < min_value::value + rhs._v)
				|| (rhs._v < 0 && _v > max_value::value + rhs._v))
			{
				throw preda_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			}
			return this_type(_v - rhs._v);
		}

		this_type operator*(const this_type &rhs) const
		{
			if (_v > 0)
			{
				if (rhs._v > 0)
				{
					if (max_value::value / rhs._v < _v)
					{
						throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
					}
				}
				else if (rhs._v < 0)
				{
					if (min_value::value / rhs._v < _v)
					{
						throw preda_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
					}
				}
			}
			else
			{
				if (rhs._v > 0)
				{
					if (min_value::value / rhs._v > _v)
					{
						throw preda_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
					}
				}
				else if (rhs._v < 0)
				{
					if (max_value::value / rhs._v > _v)
					{
						throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
					}
				}
			}
			return this_type(_v * rhs._v);
		}

		this_type operator/(const this_type &rhs) const
		{
			if (rhs._v == 0)
			{
				throw preda_exception("divide by zero in " + std::string(__FUNCTION__), prlrt::ExceptionType::DividedByZero);
			}
			if (rhs._v == -1 && _v == min_value::value)
			{
				throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			return this_type(_v / rhs._v);
		}

		this_type operator%(const this_type &rhs) const
		{
			if (rhs._v == 0)
			{
				throw preda_exception("divide by zero in " + std::string(__FUNCTION__), prlrt::ExceptionType::DividedByZero);
			}
			if (rhs._v == -1 && _v == min_value::value)
			{
				throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			return this_type(_v % rhs._v);
		}

		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(+);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(-);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(*);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(/ );
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(%);

		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, == );
		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, != );
		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, <= );
		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, >= );
		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, < );
		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, > );

		template<typename T_OtherInternal>
		explicit operator ____int<T_OtherInternal>() const
		{
			if (sizeof(T_OtherInternal) >= sizeof(internal_type))
				return ____int<T_OtherInternal>(T_OtherInternal(_v));
			if (_v > internal_type(____int<T_OtherInternal>::max_value::value))
			{
				throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			if (_v < internal_type(____int<T_OtherInternal>::min_value::value))
			{
				throw preda_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			}
			return ____int<T_OtherInternal>(T_OtherInternal(_v));
		}

		template<typename T_OtherInternal>
		explicit operator ____uint<T_OtherInternal>() const
		{
			if (_v < 0)
				throw preda_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			if (sizeof(T_OtherInternal) >= sizeof(internal_type))
				return ____uint<T_OtherInternal>(T_OtherInternal(_v));
			if (_v > internal_type(____uint<T_OtherInternal>::max_value::value))
			{
				throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			return ____uint<T_OtherInternal>(T_OtherInternal(_v));
		}

		constexpr serialize_size_type get_serialize_size() const
		{
			return sizeof(this_type);
		}

		void serialize_out(uint8_t *buffer, bool for_debug) const
		{
			*(this_type*)buffer = *this;
		}

		bool map_from_serialized_data(uint8_t *&buffer, serialize_size_type &bufferSize, bool bDeep)
		{
			if (bufferSize < serialize_size_type(sizeof(internal_type)))
				return false;
			_v = *(internal_type*)buffer;
			buffer += serialize_size_type(sizeof(internal_type));
			bufferSize -= serialize_size_type(sizeof(internal_type));
			return true;
		}
	};

	#define LONGINTTEMP(_SIZE) LongIntTemp<_SIZE>
	#define ____LONGINT_NEGATE_FUNCTION(_SIZE)\
	static void LongInt_negate(const LONGINTTEMP(_SIZE)& a, LONGINTTEMP(_SIZE)& result){ \
		PREDA_CALL(LongInt_Negate_##_SIZE, &a, &result); \
	} \
	static bool LongInt_IsSign(const LONGINTTEMP(_SIZE)& a){ \
		return PREDA_CALL(LongInt_IsSign_##_SIZE, &a); \
	}
	#define ____LONGINT_ALL_FUNCTION(_SIZE, _INT_TYPE)\
	static void _INT_TYPE##_zero(LONGINTTEMP(_SIZE)& _fStruct){\
		PREDA_CALL(_INT_TYPE##_Zero_##_SIZE, &_fStruct);\
	}\
	static void _INT_TYPE##_ToString(const LONGINTTEMP(_SIZE)& _fStruct, char* buf){ \
		PREDA_CALL(_INT_TYPE##_ConvertToString_##_SIZE, &_fStruct, buf); \
	}\
    static void _INT_TYPE##_fromInt(LONGINTTEMP(_SIZE)& _fStruct, int64_t in){\
		PREDA_CALL(_INT_TYPE##_fromInt_##_SIZE, &_fStruct, in);\
	}\
    static void _INT_TYPE##_fromUInt(LONGINTTEMP(_SIZE)& _fStruct, uint64_t in){\
		PREDA_CALL(_INT_TYPE##_fromUInt_##_SIZE, &_fStruct, in);\
	}\
	static int _INT_TYPE##_toInt64(const LONGINTTEMP(_SIZE)& _fStruct, int64_t& result){\
		return PREDA_CALL(_INT_TYPE##_toInt64_##_SIZE, &_fStruct, &result);\
	}\
    static int _INT_TYPE##_toUInt64(const LONGINTTEMP(_SIZE)& _fStruct, uint64_t& result){\
		return PREDA_CALL(_INT_TYPE##_toUInt64_##_SIZE, &_fStruct, &result);\
	}\
	static void _INT_TYPE##_rightShift(LONGINTTEMP(_SIZE)& a, int64_t shift){\
		PREDA_CALL(_INT_TYPE##_rightShift_##_SIZE, &a, shift);\
	}\
    static void _INT_TYPE##_leftShift(LONGINTTEMP(_SIZE)& a, int64_t shift){\
		PREDA_CALL(_INT_TYPE##_leftShift_##_SIZE, &a, shift);\
	}\
	static uint32_t _INT_TYPE##_GetConvertToStringLen(const LONGINTTEMP(_SIZE)& _fStruct){ \
		return PREDA_CALL(_INT_TYPE##_GetConvertToStringLen_##_SIZE, &_fStruct); \
	}\
	static void _INT_TYPE##_ConvertFromString(LONGINTTEMP(_SIZE)& _fStruct, const char* longint_literal){ \
		PREDA_CALL(_INT_TYPE##_ConvertFromString_##_SIZE, &_fStruct, longint_literal); \
	}\
	static void _INT_TYPE##_ConvertFromHexString(LONGINTTEMP(_SIZE)& _fStruct, const char* longint_literal){ \
		PREDA_CALL(_INT_TYPE##_ConvertFromHexString_##_SIZE, &_fStruct, longint_literal); \
	}\
	static void _INT_TYPE##_add(const LONGINTTEMP(_SIZE)& a, const LONGINTTEMP(_SIZE)& b, LONGINTTEMP(_SIZE)& result){ \
		PREDA_CALL(_INT_TYPE##_Add_##_SIZE, &a, &b, &result); \
	}\
	static void _INT_TYPE##_sub(const LONGINTTEMP(_SIZE)& a, const LONGINTTEMP(_SIZE)& b, LONGINTTEMP(_SIZE)& result){ \
		PREDA_CALL(_INT_TYPE##_Sub_##_SIZE, &a, &b, &result); \
	}\
	static void _INT_TYPE##_mul(const LONGINTTEMP(_SIZE)& a, const  LONGINTTEMP(_SIZE)& b, LONGINTTEMP(_SIZE)& result){ \
		PREDA_CALL(_INT_TYPE##_Mul_##_SIZE, &a, &b, &result); \
	}\
	static void _INT_TYPE##_div(const LONGINTTEMP(_SIZE)& a, const  LONGINTTEMP(_SIZE)& b, LONGINTTEMP(_SIZE)& result){ \
		PREDA_CALL(_INT_TYPE##_Div_##_SIZE, &a, &b, &result); \
	}\
	static void _INT_TYPE##_mod(const LONGINTTEMP(_SIZE)& a, const  LONGINTTEMP(_SIZE)& b, LONGINTTEMP(_SIZE)& result){ \
		PREDA_CALL(_INT_TYPE##_Mod_##_SIZE, &a, &b, &result); \
	}\
	static int _INT_TYPE##_compare(const LONGINTTEMP(_SIZE)& a, const LONGINTTEMP(_SIZE)& b){ \
		return 	PREDA_CALL(_INT_TYPE##_Compare_##_SIZE, &a, &b); \
	}\
	static int _INT_TYPE##_isZero(const LONGINTTEMP(_SIZE)& a){ \
		return 	PREDA_CALL(_INT_TYPE##_IsZero_##_SIZE, &a); \
	}\
	static void _INT_TYPE##_SetMax(LONGINTTEMP(_SIZE)& a){ \
		return 	PREDA_CALL(_INT_TYPE##_SetMax_##_SIZE, &a); \
	}\
	static void _INT_TYPE##_SetMin(LONGINTTEMP(_SIZE)& a){ \
		return 	PREDA_CALL(_INT_TYPE##_SetMin_##_SIZE, &a); \
	}

	struct ____longintType{
		____LONGINT_ALL_FUNCTION(128, ULongInt);
		____LONGINT_ALL_FUNCTION(256, ULongInt);
		____LONGINT_ALL_FUNCTION(512, ULongInt);
		____LONGINT_ALL_FUNCTION(128, LongInt);
		____LONGINT_ALL_FUNCTION(256, LongInt);
		____LONGINT_ALL_FUNCTION(512, LongInt);
		____LONGINT_NEGATE_FUNCTION(128);
		____LONGINT_NEGATE_FUNCTION(256);
		____LONGINT_NEGATE_FUNCTION(512);
	};
	using impl_type = ____longintType;

	template <uint32_t Size> constexpr type_identifier_enum ____get_type_identifier_enum_of_long_int_type();
	template <> constexpr type_identifier_enum ____get_type_identifier_enum_of_long_int_type<128>() { return type_identifier_enum::___int128; }
	template <> constexpr type_identifier_enum ____get_type_identifier_enum_of_long_int_type<256>() { return type_identifier_enum::___int256; }
	template <> constexpr type_identifier_enum ____get_type_identifier_enum_of_long_int_type<512>() { return type_identifier_enum::___int512; }
	template <uint32_t Size> constexpr type_identifier_enum ____get_type_identifier_enum_of_long_uint_type();
	template <> constexpr type_identifier_enum ____get_type_identifier_enum_of_long_uint_type<128>() { return type_identifier_enum::___uint128; }
	template <> constexpr type_identifier_enum ____get_type_identifier_enum_of_long_uint_type<256>() { return type_identifier_enum::___uint256; }
	template <> constexpr type_identifier_enum ____get_type_identifier_enum_of_long_uint_type<512>() { return type_identifier_enum::___uint512; }

	template<short Size>
	constexpr prlrt::LongIntTemp<Size> ____get_max_value_of_longint()
	{
		prlrt::LongIntTemp<Size> max;
		for(int i = 0; i < (Size / 8) - 1; i++)
		{
			max._Data[i] = 0xff;
		}
		max._Data[Size / 8 - 1] = 0x7f;
		return max;
	}
	template<short Size>
	constexpr prlrt::LongIntTemp<Size> ____get_min_value_of_longint()
	{
		prlrt::LongIntTemp<Size> min;
		min._Data[Size / 8 - 1] = 0x80;
		return min;
	}
	template<short Size>
	constexpr prlrt::LongIntTemp<Size> ____get_max_value_of_ulongint()
	{
		prlrt::LongIntTemp<Size> max;
		for(int i = 0; i < Size / 8; i++)
		{
			max._Data[i] = 0xff;
		}
		return max;
	}

	template<short Size>
	struct ____longint
	{
		using this_type = ____longint<Size>;
		using internal_type = prlrt::LongIntTemp<Size>;
		using is_value_type = std::true_type;
		using is_fixed_size = std::true_type;
    		using fixed_size_in_bytes = std::integral_constant<serialize_size_type, serialize_size_type(sizeof(internal_type))>;
		using type_identifier_type = simple_type_type_identifier<____get_type_identifier_enum_of_long_int_type<Size>()>;
		constexpr static internal_type max_value = ____get_max_value_of_longint<Size>();
		constexpr static internal_type min_value = ____get_min_value_of_longint<Size>();
		static constexpr uint32_t get_type_identifier_size()
		{
			return type_identifier_type::value.length();
		}

		static constexpr const uint8_t* get_type_identifier_buffer()
		{
			return type_identifier_type::value.data;
		}

		internal_type _fStruct;
		____longint()
		{
			impl_type::LongInt_zero(_fStruct);
		}
		____longint(const char* longint_literal){
			int starting_pos = *longint_literal == '-' ? 1 : 0;
			if(strlen(longint_literal) >= starting_pos + 2 && longint_literal[starting_pos] == '0' && longint_literal[starting_pos + 1] == 'x')
			{
				std::string temp(longint_literal);
				temp[starting_pos + 1] = '0';
				impl_type::LongInt_ConvertFromHexString(_fStruct, temp.c_str());
			}
			else
			{
				impl_type::LongInt_ConvertFromString(_fStruct, longint_literal);
			}
		}
		template<typename T_OtherInternal>
		____longint(const ____int<T_OtherInternal>& x){
			impl_type::LongInt_fromInt(_fStruct, (int64_t)x._v);
		}
		template<typename T_OtherInternal>
		____longint(const ____uint<T_OtherInternal>& x){
			impl_type::LongInt_fromUInt(_fStruct, (uint64_t)x._v);
		}

		template<short T_OtherSize>
		____longint(const ____longint<T_OtherSize>& x){
			if constexpr(Size < T_OtherSize)
			{
				____longint<T_OtherSize> max;
				memcpy(max._fStruct._Data, max_value._Data, std::min(sizeof(max_value._Data), sizeof(max._fStruct._Data)));
				if(max < x)
				{
					throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
				}
				____longint<T_OtherSize> min;
				memcpy(min._fStruct._Data, min_value._Data, std::min(sizeof(min_value._Data), sizeof(min._fStruct._Data)));
				if(min > x)
				{
					throw preda_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
				}
			}
			impl_type::ULongInt_zero(_fStruct);
			memcpy(_fStruct._Data, x._fStruct._Data, std::min(sizeof(_fStruct._Data), sizeof(x._fStruct._Data)));
		}

		template<short T_OtherSize>
		____longint(const ____ulongint<T_OtherSize>& x){
			if constexpr(Size <= T_OtherSize)
			{
				____ulongint<T_OtherSize> max;
				memcpy(max._fStruct._Data, max_value._Data, std::min(sizeof(max_value._Data), sizeof(max._fStruct._Data)));
				if(max < x)
				{
					throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
				}
			}
			impl_type::ULongInt_zero(_fStruct);
			memcpy(_fStruct._Data, x._fStruct._Data, std::min(sizeof(_fStruct._Data), sizeof(x._fStruct._Data)));
		}

		____longint(internal_type x){
			_fStruct = x;
		}
		____longint(int8_t x){
			//depends on TTMath's implementation of TTMath::UInt<value_size>
			_fStruct._Data[0] = x;
		}
		void operator=(const this_type &rhs)
		{
			_fStruct = rhs._fStruct;
		}
		void operator=(const internal_type &LongIntTemp)
		{
			_fStruct = LongIntTemp;
		}
		void operator++(){
			if (*this == this_type(max_value))
			{
				throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			this_type tmp((int8_t)1);
			*this += tmp;
		}
		void operator--(){
			if (*this == this_type(min_value))
			{
				throw preda_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			this_type tmp((int8_t)1);
			*this -= tmp;
		}
		FORWARD_POST_INC_DEC_TO_PRE_INC_DEC
		this_type operator-() const{
			if (*this == this_type(min_value))
			{
				throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			internal_type result;
			impl_type::LongInt_negate(_fStruct, result);
			return this_type(result);
		}
		this_type operator+(const this_type &rhs) const{
			internal_type tmp_sub_result_1;
			impl_type::LongInt_sub(max_value, _fStruct, tmp_sub_result_1);
			internal_type tmp_sub_result_2;
			impl_type::LongInt_sub(min_value, _fStruct, tmp_sub_result_2);
			if ((!impl_type::LongInt_IsSign(_fStruct) && this_type(tmp_sub_result_1) < rhs) || (impl_type::LongInt_IsSign(_fStruct) && this_type(tmp_sub_result_2) > rhs))
			{
				throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			internal_type result;
			impl_type::LongInt_add(_fStruct, rhs._fStruct, result);
			return this_type(result);
		}
		this_type operator-(const this_type &rhs) const{
			internal_type tmp_add_result_1;
			impl_type::LongInt_add(min_value, rhs._fStruct, tmp_add_result_1);
			internal_type tmp_add_result_2;
			impl_type::LongInt_add(max_value, rhs._fStruct, tmp_add_result_2);
			if ((!impl_type::LongInt_IsSign(rhs._fStruct) && *this < this_type(tmp_add_result_1)) || (impl_type::LongInt_IsSign(rhs._fStruct) && *this > this_type(tmp_add_result_2)))
			{
				throw preda_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			}
			internal_type result;
			impl_type::LongInt_sub(_fStruct, rhs._fStruct, result);
			return this_type(result);
		}
		this_type operator*(const this_type &rhs) const{
			internal_type tmp_div_result_1;
			impl_type::LongInt_div(max_value, rhs._fStruct, tmp_div_result_1);
			internal_type tmp_div_result_2;
			impl_type::LongInt_div(min_value, rhs._fStruct, tmp_div_result_2);
			if (!impl_type::LongInt_IsSign(_fStruct))
			{
				if (!impl_type::LongInt_IsSign(rhs._fStruct))
				{
					if (this_type(tmp_div_result_1) < *this)
					{
						throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
					}
				}
				else if (impl_type::LongInt_IsSign(rhs._fStruct))
				{
					if (this_type(tmp_div_result_2) < *this)
					{
						throw preda_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
					}
				}
			}
			else
			{
				if (!impl_type::LongInt_IsSign(rhs._fStruct))
				{
					if (this_type(tmp_div_result_2) > *this)
					{
						throw preda_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
					}
				}
				else if (impl_type::LongInt_IsSign(rhs._fStruct))
				{
					if (this_type(tmp_div_result_1) > *this)
					{
						throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
					}
				}
			}
			internal_type result;
			impl_type::LongInt_mul(_fStruct, rhs._fStruct, result);
			return this_type(result);
		}
		bool isZero() const{
			return impl_type::LongInt_isZero(_fStruct);
		}
		this_type operator/(const this_type &rhs) const{
			if (rhs.isZero())
			{
				throw preda_exception("divide by zero in " + std::string(__FUNCTION__), prlrt::ExceptionType::DividedByZero);
			}
			if (impl_type::LongInt_IsSign(rhs._fStruct) && *this == this_type(min_value))
			{
				throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			internal_type result;
			impl_type::LongInt_div(_fStruct, rhs._fStruct, result);
			return this_type(result);
		}
		this_type operator%(const this_type &rhs) const{
			if (rhs.isZero())
			{
				throw preda_exception("divide by zero in " + std::string(__FUNCTION__), prlrt::ExceptionType::DividedByZero);
			}
			if (impl_type::LongInt_IsSign(rhs._fStruct) && *this == this_type(min_value))
			{
				throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			internal_type result;
			impl_type::LongInt_mod(_fStruct, rhs._fStruct, result);
			return this_type(result);
		}
		__prlt_bool operator==(const this_type& rhs) const{
			int result = impl_type::LongInt_compare(_fStruct, rhs._fStruct);
			if(result == 0){
				return __prlt_bool(true);
			}
			return __prlt_bool(false);
		}
		__prlt_bool operator!=(const this_type& rhs) const{
			int result = impl_type::LongInt_compare(_fStruct, rhs._fStruct);
			if(result != 0){
				return __prlt_bool(true);
			}
			return __prlt_bool(false);
		}
		__prlt_bool operator>=(const this_type& rhs) const{
			int result = impl_type::LongInt_compare(_fStruct, rhs._fStruct);
			if(result == 0 || result == 1){
				return __prlt_bool(true);
			}
			return __prlt_bool(false);
		}
		__prlt_bool operator<=(const this_type& rhs) const{
			int result = impl_type::LongInt_compare(_fStruct, rhs._fStruct);
			if(result == 0 || result == -1){
				return __prlt_bool(true);
			}
			return __prlt_bool(false);
		}
		__prlt_bool operator<(const this_type& rhs) const{
			int result = impl_type::LongInt_compare(_fStruct, rhs._fStruct);
			if(result == -1){
				return __prlt_bool(true);
			}
			return __prlt_bool(false);
		}
		__prlt_bool operator>(const this_type& rhs) const{
			int result = impl_type::LongInt_compare(_fStruct, rhs._fStruct);
			if(result == 1){
				return __prlt_bool(true);
			}
			return __prlt_bool(false);
		}
		bool ToInt64(int64_t& result) const{
			if(impl_type::LongInt_toInt64(_fStruct, result) > 0)
			{
				return false;
			}
			return true;
		}
		bool ToUInt64(uint64_t& result) const{
			if(impl_type::LongInt_toUInt64(_fStruct, result) > 0)
			{
				return false;
			}
			return true;
		}
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(+);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(-);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(*);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(/);

		template<typename T_OtherInternal>
		explicit operator ____int<T_OtherInternal>() { 
			int64_t result;
			if(!ToInt64(result) || result > ____int<T_OtherInternal>::max_value::value)
			{
				throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			else if(result < ____int<T_OtherInternal>::min_value::value)
			{
				throw preda_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			}
			return ____int<T_OtherInternal>(T_OtherInternal(result));
		}

		template<typename T_OtherInternal>
		explicit operator ____uint<T_OtherInternal>() { 
			uint64_t result;
			if(!ToUInt64(result) || result > ____uint<T_OtherInternal>::max_value::value)
			{
				throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			else if(impl_type::LongInt_IsSign(_fStruct))
			{
				throw preda_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			}
			return ____uint<T_OtherInternal>(T_OtherInternal(result));
		}

		std::string ToString() const{
			uint32_t len = impl_type::LongInt_GetConvertToStringLen(_fStruct);
			std::vector<char> buf(len + 1, '\0');
			impl_type::LongInt_ToString(_fStruct, &buf[0]);
			return std::string(&buf[0], len);
		}
		constexpr serialize_size_type get_serialize_size() const
		{
			return sizeof(this_type);
		}
		void serialize_out(uint8_t *buffer, bool for_debug) const
		{
			*(this_type*)buffer = *this;
		}
		bool map_from_serialized_data(uint8_t *&buffer, serialize_size_type &bufferSize, bool bDeep)
		{
			if (bufferSize < serialize_size_type(sizeof(internal_type)))
				return false;
			_fStruct = *(internal_type*)buffer;
			buffer += serialize_size_type(sizeof(internal_type));
			bufferSize -= serialize_size_type(sizeof(internal_type));
			return true;
		}
	};

template<short Size>
	struct ____ulongint
	{
		using this_type = ____ulongint<Size>;
		using is_value_type = std::true_type;
		using is_fixed_size = std::true_type;
		using internal_type = prlrt::LongIntTemp<Size>;
    	using fixed_size_in_bytes = std::integral_constant<serialize_size_type, serialize_size_type(sizeof(internal_type))>;
		using type_identifier_type = simple_type_type_identifier<____get_type_identifier_enum_of_long_uint_type<Size>()>;
		constexpr static internal_type max_value = ____get_max_value_of_ulongint<Size>();
		static constexpr uint32_t get_type_identifier_size()
		{
			return type_identifier_type::value.length();
		}

		static constexpr const uint8_t* get_type_identifier_buffer()
		{
			return type_identifier_type::value.data;
		}
		internal_type _fStruct;
		____ulongint()
		{
			impl_type::ULongInt_zero(_fStruct);
		}
		____ulongint(const char* longint_literal){
			if(longint_literal[0] == '0' && (longint_literal[1] == 'x' || longint_literal[0] == 'X'))
			{
				impl_type::ULongInt_ConvertFromHexString(_fStruct, longint_literal);

			}
			else
			{
				impl_type::ULongInt_ConvertFromString(_fStruct, longint_literal);
			}
		}
		template<typename T_OtherInternal>
		____ulongint(const ____int<T_OtherInternal>& x){
			impl_type::ULongInt_fromInt(_fStruct, (int64_t)x._v);
		}
		template<typename T_OtherInternal>
		____ulongint(const ____uint<T_OtherInternal>& x){
			impl_type::ULongInt_fromUInt(_fStruct, (uint64_t)x._v);
		}

		template<short T_OtherSize>
		____ulongint(const ____longint<T_OtherSize>& x){
			if(impl_type::LongInt_IsSign(x._fStruct))
			{
				throw preda_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			}
			else if(Size < T_OtherSize)
			{
				____longint<T_OtherSize> max;
				memcpy(max._fStruct._Data, max_value._Data, std::min(sizeof(max_value._Data), sizeof(max._fStruct._Data)));
				if(max < x)
				{
					throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
				}
			}
			impl_type::ULongInt_zero(_fStruct);
			memcpy(_fStruct._Data, x._fStruct._Data, std::min(sizeof(_fStruct._Data), sizeof(x._fStruct._Data)));
		}

		template<short T_OtherSize>
		____ulongint(const ____ulongint<T_OtherSize>& x){
			if constexpr(Size < T_OtherSize)
			{
				____ulongint<T_OtherSize> max;
				memcpy(max._fStruct._Data, max_value._Data, std::min(sizeof(max_value._Data), sizeof(max._fStruct._Data)));
				if(max < x)
				{
					throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
				}
			}
			impl_type::ULongInt_zero(_fStruct);
			memcpy(_fStruct._Data, x._fStruct._Data, std::min(sizeof(_fStruct._Data), sizeof(x._fStruct._Data)));
		}

		____ulongint(internal_type x){
			_fStruct = x;
		}
		____ulongint(uint8_t x){
			//depends on TTMath's implementation of TTMath::UInt<value_size>
			_fStruct._Data[0] = x;
		}
		void operator=(const this_type &rhs)
		{
			_fStruct = rhs._fStruct;
		}
		void operator++(){
			if (*this == this_type(max_value))
			{
				throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			this_type tmp((uint8_t)1);
			*this += tmp;
		}
		void operator--(){
			if (isZero())
			{
				throw preda_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			this_type tmp((uint8_t)1);
			*this -= tmp;
		}
		FORWARD_POST_INC_DEC_TO_PRE_INC_DEC
		this_type operator+(const this_type &rhs) const{
			internal_type tmp_sub_result;
			impl_type::ULongInt_sub(max_value, _fStruct, tmp_sub_result);
			if (this_type(tmp_sub_result) < rhs)
			{
				throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			internal_type result;
			impl_type::ULongInt_add(_fStruct, rhs._fStruct, result);
			return this_type(result);
		}
		this_type operator-(const this_type &rhs) const{
			if(*this < rhs)
			{
				throw preda_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			internal_type result;
			impl_type::ULongInt_sub(_fStruct, rhs._fStruct, result);
			this_type out(result);
			return out;
		}
		this_type operator*(const this_type &rhs) const{
			internal_type tmp_div_result_1;
			impl_type::ULongInt_div(max_value, _fStruct, tmp_div_result_1);
			if (this_type(tmp_div_result_1) < rhs)
			{
				throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			internal_type result;
			impl_type::ULongInt_mul(_fStruct, rhs._fStruct, result);
			this_type out(result);
			return out;
		}
		bool isZero() const{
			return impl_type::ULongInt_isZero(_fStruct);
		}
		this_type operator/(const this_type &rhs) const{
			if(rhs.isZero()){
				throw preda_exception("divide by zero in " + std::string(__FUNCTION__), prlrt::ExceptionType::DividedByZero);
			}
			internal_type result;
			impl_type::ULongInt_div(_fStruct, rhs._fStruct, result);
			return this_type(result);
		}
		this_type operator%(const this_type &rhs) const{
			if(rhs.isZero()){
				throw preda_exception("divide by zero in " + std::string(__FUNCTION__), prlrt::ExceptionType::DividedByZero);
			}
			internal_type result;
			impl_type::ULongInt_mod(_fStruct, rhs._fStruct, result);
			return this_type(result);
		}
		__prlt_bool operator==(const this_type& rhs) const{
			int result = impl_type::ULongInt_compare(_fStruct, rhs._fStruct);
			if(result == 0){
				return __prlt_bool(true);
			}
			return __prlt_bool(false);
		}
		__prlt_bool operator!=(const this_type& rhs) const{
			int result = impl_type::ULongInt_compare(_fStruct, rhs._fStruct);
			if(result != 0){
				return __prlt_bool(true);
			}
			return __prlt_bool(false);
		}
		__prlt_bool operator>=(const this_type& rhs) const{
			int result = impl_type::ULongInt_compare(_fStruct, rhs._fStruct);
			if(result == 0 || result == 1){
				return __prlt_bool(true);
			}
			return __prlt_bool(false);
		}
		__prlt_bool operator<=(const this_type& rhs) const{
			int result = impl_type::ULongInt_compare(_fStruct, rhs._fStruct);
			if(result == 0 || result == -1){
				return __prlt_bool(true);
			}
			return __prlt_bool(false);
		}
		__prlt_bool operator<(const this_type& rhs) const{
			int result = impl_type::ULongInt_compare(_fStruct, rhs._fStruct);
			if(result == -1){
				return __prlt_bool(true);
			}
			return __prlt_bool(false);
		}
		__prlt_bool operator>(const this_type& rhs) const{
			int result = impl_type::ULongInt_compare(_fStruct, rhs._fStruct);
			if(result == 1){
				return __prlt_bool(true);
			}
			return __prlt_bool(false);
		}
		this_type operator<<(const this_type& x)
		{
			int64_t bitWidth;
			if(!x.ToInt64(bitWidth) || bitWidth >= Size)
			{
				return ____ulongint();
			}
			this_type result = *this;
			impl_type::ULongInt_leftShift(result._fStruct, bitWidth);
			return result;
		}
		this_type operator>>(const this_type& x)
		{
			int64_t bitWidth;
			if(!x.ToInt64(bitWidth) || bitWidth >= Size)
			{
				return ____ulongint();
			}
			this_type result = *this;
			impl_type::ULongInt_rightShift(result._fStruct, bitWidth);
			return result;
		}
		bool ToInt64(int64_t& result) const{
			if(impl_type::ULongInt_toInt64(_fStruct, result) > 0)
			{
				return false;
			}
			return true;
		}
		bool ToUInt64(uint64_t& result) const{
			if(impl_type::ULongInt_toUInt64(_fStruct, result) > 0)
			{
				return false;
			}
			return true;
		}
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(+);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(-);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(*);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(/);

		template<typename T_OtherInternal>
		explicit operator ____int<T_OtherInternal>() { 
			int64_t result;
			if(!ToInt64(result) || result > ____int<T_OtherInternal>::max_value::value)
			{
				throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			return ____int<T_OtherInternal>(T_OtherInternal(result));
		}

		template<typename T_OtherInternal>
		explicit operator ____uint<T_OtherInternal>() { 
			uint64_t result;
			if(!ToUInt64(result) || result > ____uint<T_OtherInternal>::max_value::value)
			{
				throw preda_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			return ____uint<T_OtherInternal>(T_OtherInternal(result));
		}

		std::string ToString() const{
			uint32_t len = impl_type::ULongInt_GetConvertToStringLen(_fStruct);
			std::vector<char> buf(len + 1, '\0');
			impl_type::ULongInt_ToString(_fStruct, &buf[0]);
			std::string LongInt_str(&buf[0], len);
			return LongInt_str;
		}
		constexpr serialize_size_type get_serialize_size() const
		{
			return sizeof(this_type);
		}
		void serialize_out(uint8_t *buffer, bool for_debug) const
		{
			*(this_type*)buffer = *this;
		}
		bool map_from_serialized_data(uint8_t *&buffer, serialize_size_type &bufferSize, bool bDeep)
		{
			if (bufferSize < serialize_size_type(sizeof(internal_type)))
				return false;
			_fStruct = *(internal_type*)buffer;
			buffer += serialize_size_type(sizeof(internal_type));
			bufferSize -= serialize_size_type(sizeof(internal_type));
			return true;
		}
	};
}

#undef WRAP_SIMPLE_BINARY_OPERATOR
#undef EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT
#undef FORWARD_POST_INC_DEC_TO_PRE_INC_DEC

using __prlt_bool = prlrt::__prlt_bool;

using __prlt_uint64 = prlrt::____uint<uint64_t>;
using __prlt_uint32 = prlrt::____uint<uint32_t>;
using __prlt_uint16 = prlrt::____uint<uint16_t>;
using __prlt_uint8 = prlrt::____uint<uint8_t>;

using __prlt_int64 = prlrt::____int<int64_t>;
using __prlt_int32 = prlrt::____int<int32_t>;
using __prlt_int16 = prlrt::____int<int16_t>;
using __prlt_int8 = prlrt::____int<int8_t>;

using __prlt_uint512 = prlrt::____ulongint<512>;
using __prlt_uint256 = prlrt::____ulongint<256>;
using __prlt_uint128 = prlrt::____ulongint<128>;

using __prlt_int512 = prlrt::____longint<512>;
using __prlt_int256 = prlrt::____longint<256>;
using __prlt_int128 = prlrt::____longint<128>;