#pragma once

#include <vector>
#include "common.h"
#include "exceptions.h"
#include "gascost.h"

#define WRAP_SIMPLE_BINARY_OPERATOR(returnType, oper, gas)\
	returnType operator oper(const this_type &rhs) const\
	{\
		burn_gas(gas);\
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
		using fixed_size_in_bytes = std::integral_constant<serialize_size_type, (serialize_size_type)(sizeof(internal_type))>;
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
		__prlt_bool() 
		{ 
			_v = false; 
		}
		__prlt_bool(bool x) { _v = x; }

		operator bool() const
		{
			return _v;
		}

		void operator=(const this_type &rhs)
		{
			burn_gas((uint64_t)gas_costs[PRDOP_BOOL_ASSIGN]);
			_v = rhs._v;
		}

		__prlt_bool operator!() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_BOOL_NOT]);
			return __prlt_bool(!_v);
		}

		// WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, &&);
		// WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, || );
		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, ==, gas_costs[PRDOP_BOOL_COMP]);
		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, !=, gas_costs[PRDOP_BOOL_COMP]);

		serialize_size_type get_serialize_size() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_SIZE]);
			return fixed_size_in_bytes::value;
		}

		void serialize_out(uint8_t *buffer, bool for_debug) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_OUT_STATIC] + (uint64_t)gas_costs[PRDOP_SERIALIZE_DYNAMIC] * fixed_size_in_bytes::value);
			(*(this_type*)buffer)._v = _v;
		}

		bool map_from_serialized_data(uint8_t *&buffer, serialize_size_type &bufferSize, bool bDeep)
		{
			if (bufferSize < fixed_size_in_bytes::value)
				return false;
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_MAP_STATIC] + (uint64_t)gas_costs[PRDOP_SERIALIZE_DYNAMIC] * fixed_size_in_bytes::value);
			_v = *(internal_type*)buffer;
			buffer += fixed_size_in_bytes::value;
			bufferSize -= fixed_size_in_bytes::value;
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
		____uint() 
		{ 
			_v = 0; 
		}
		____uint(internal_type x) { _v = x; }

		void operator=(const this_type &rhs)
		{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_ASSIGN]);
			_v = rhs._v;
		}

		void operator++()
		{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SELF]);
			if (_v == max_value::value)
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			_v++;
		}

		void operator--()
		{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SELF]);
			if (_v == min_value::value)
			{
				preda_exception::throw_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			}
			_v--;
		}

		FORWARD_POST_INC_DEC_TO_PRE_INC_DEC;

		this_type operator~() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SELF]);
			return this_type(~_v);
		}

		this_type operator+(const this_type &rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE]);
			if (max_value::value - _v < rhs._v)
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			return this_type(_v + rhs._v);
		}

		this_type operator-(const this_type &rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE]);
			if (_v < rhs._v)
			{
				preda_exception::throw_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			}
			return this_type(_v - rhs._v);
		}

		this_type operator*(const this_type &rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_COMPLEX]);
			if (_v != 0 && max_value::value / _v < rhs._v)
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			return this_type(_v * rhs._v);
		}

		this_type operator/(const this_type &rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_COMPLEX]);
			if (rhs._v == 0)
			{
				preda_exception::throw_exception("divide by zero in " + std::string(__FUNCTION__), prlrt::ExceptionType::DividedByZero);
			}
			return this_type(_v / rhs._v);
		}

		this_type operator%(const this_type &rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_COMPLEX]);
			if (rhs._v == 0)
			{
				preda_exception::throw_exception("divide by zero in " + std::string(__FUNCTION__), prlrt::ExceptionType::DividedByZero);
			}
			return this_type(_v % rhs._v);
		}

		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(+);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(-);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(*);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(/ );
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(%);

		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, ==, gas_costs[PRDOP_INT_OP_SIMPLE]);
		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, !=, gas_costs[PRDOP_INT_OP_SIMPLE]);
		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, <=, gas_costs[PRDOP_INT_OP_SIMPLE]);
		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, >=, gas_costs[PRDOP_INT_OP_SIMPLE]);
		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, <, gas_costs[PRDOP_INT_OP_SIMPLE]);
		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, >, gas_costs[PRDOP_INT_OP_SIMPLE]);

		WRAP_SIMPLE_BINARY_OPERATOR(this_type, &, gas_costs[PRDOP_INT_OP_SIMPLE]);
		WRAP_SIMPLE_BINARY_OPERATOR(this_type, ^, gas_costs[PRDOP_INT_OP_SIMPLE]);
		WRAP_SIMPLE_BINARY_OPERATOR(this_type, |, gas_costs[PRDOP_INT_OP_SIMPLE]);

		this_type operator <<(const this_type &rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE]);
			if (rhs._v >= internal_type(sizeof(internal_type) * 8))
				return this_type(internal_type(0));
			return this_type(_v << rhs._v);
		}
		this_type operator >>(const this_type& rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE]);
			if (rhs._v >= internal_type(sizeof(internal_type) * 8))
				return this_type(internal_type(0));
			return this_type(_v >> rhs._v);
		}
		template<typename T_OtherIntType>
		this_type operator<<(const T_OtherIntType& rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE]);
			int64_t bitShift;
			if(rhs.ToInt64(bitShift))
			{
				return this_type(_v << bitShift);
			}
			return this_type(internal_type(0));
		}
		template<typename T_OtherIntType>
		this_type operator>>(const T_OtherIntType& rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE]);
			int64_t bitShift;
			if(rhs.ToInt64(bitShift))
			{
				return this_type(_v >> bitShift);
			}
			return this_type(internal_type(0));
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
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
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
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			return ____int<T_OtherInternal>(T_OtherInternal(_v));
		}

		serialize_size_type get_serialize_size() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_SIZE]);
			return fixed_size_in_bytes::value;
		}

		void serialize_out(uint8_t *buffer, bool for_debug) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_OUT_STATIC] + (uint64_t)gas_costs[PRDOP_SERIALIZE_DYNAMIC] * fixed_size_in_bytes::value);
			(*(this_type*)buffer)._v = _v;
		}

		bool map_from_serialized_data(uint8_t *&buffer, serialize_size_type &bufferSize, bool bDeep)
		{
			if (bufferSize < fixed_size_in_bytes::value)
				return false;
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_MAP_STATIC] + (uint64_t)gas_costs[PRDOP_SERIALIZE_DYNAMIC] * fixed_size_in_bytes::value);
			_v = *(internal_type*)buffer;
			buffer += fixed_size_in_bytes::value;
			bufferSize -= fixed_size_in_bytes::value;
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
		____int() 
		{
			 _v = 0; 
		}
		____int(internal_type x) { _v = x; }

		void operator=(const this_type &rhs)
		{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_ASSIGN]);
			_v = rhs._v;
		}

		void operator++()
		{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SELF]);
			if (_v == max_value::value)
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			_v++;
		}

		void operator--()
		{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SELF]);
			if (_v == min_value::value)
			{
				preda_exception::throw_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			}
			_v--;
		}

		FORWARD_POST_INC_DEC_TO_PRE_INC_DEC;

		this_type operator-() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SELF]);
			if (_v == min_value::value)
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			return this_type(-_v);
		}

		this_type operator+(const this_type &rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE]);
			if ((_v > 0 && max_value::value - _v < rhs._v)
				|| (_v < 0 && min_value::value - _v > rhs._v))
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			return this_type(_v + rhs._v);
		}

		this_type operator-(const this_type &rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE]);
			if ((rhs._v > 0 && _v < min_value::value + rhs._v)
				|| (rhs._v < 0 && _v > max_value::value + rhs._v))
			{
				preda_exception::throw_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			}
			return this_type(_v - rhs._v);
		}

		this_type operator*(const this_type &rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_COMPLEX]);
			if (_v > 0)
			{
				if (rhs._v > 0)
				{
					if (max_value::value / rhs._v < _v)
					{
						preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
					}
				}
				else if (rhs._v < 0)
				{
					if (min_value::value / rhs._v < _v)
					{
						preda_exception::throw_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
					}
				}
			}
			else
			{
				if (rhs._v > 0)
				{
					if (min_value::value / rhs._v > _v)
					{
						preda_exception::throw_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
					}
				}
				else if (rhs._v < 0)
				{
					if (max_value::value / rhs._v > _v)
					{
						preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
					}
				}
			}
			return this_type(_v * rhs._v);
		}

		this_type operator/(const this_type &rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_COMPLEX]);
			if (rhs._v == 0)
			{
				preda_exception::throw_exception("divide by zero in " + std::string(__FUNCTION__), prlrt::ExceptionType::DividedByZero);
			}
			if (rhs._v == -1 && _v == min_value::value)
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			return this_type(_v / rhs._v);
		}

		this_type operator%(const this_type &rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_COMPLEX]);
			if (rhs._v == 0)
			{
				preda_exception::throw_exception("divide by zero in " + std::string(__FUNCTION__), prlrt::ExceptionType::DividedByZero);
			}
			if (rhs._v == -1 && _v == min_value::value)
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			return this_type(_v % rhs._v);
		}

		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(+);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(-);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(*);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(/ );
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(%);

		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, ==, gas_costs[PRDOP_INT_OP_SIMPLE]);
		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, !=, gas_costs[PRDOP_INT_OP_SIMPLE]);
		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, <= , gas_costs[PRDOP_INT_OP_SIMPLE]);
		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, >= , gas_costs[PRDOP_INT_OP_SIMPLE]);
		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, <, gas_costs[PRDOP_INT_OP_SIMPLE]);
		WRAP_SIMPLE_BINARY_OPERATOR(__prlt_bool, >, gas_costs[PRDOP_INT_OP_SIMPLE]);

		template<typename T_OtherInternal>
		explicit operator ____int<T_OtherInternal>() const
		{
			if (sizeof(T_OtherInternal) >= sizeof(internal_type))
				return ____int<T_OtherInternal>(T_OtherInternal(_v));
			if (_v > internal_type(____int<T_OtherInternal>::max_value::value))
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			if (_v < internal_type(____int<T_OtherInternal>::min_value::value))
			{
				preda_exception::throw_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			}
			return ____int<T_OtherInternal>(T_OtherInternal(_v));
		}

		template<typename T_OtherInternal>
		explicit operator ____uint<T_OtherInternal>() const
		{
			if (_v < 0)
				preda_exception::throw_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			if (sizeof(T_OtherInternal) >= sizeof(internal_type))
				return ____uint<T_OtherInternal>(T_OtherInternal(_v));
			if (_v > internal_type(____uint<T_OtherInternal>::max_value::value))
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			return ____uint<T_OtherInternal>(T_OtherInternal(_v));
		}

		serialize_size_type get_serialize_size() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_SIZE]);
			return fixed_size_in_bytes::value;
		}

		void serialize_out(uint8_t *buffer, bool for_debug) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_OUT_STATIC] + (uint64_t)gas_costs[PRDOP_SERIALIZE_DYNAMIC] * fixed_size_in_bytes::value);
			(*(this_type*)buffer)._v = _v;
		}

		bool map_from_serialized_data(uint8_t *&buffer, serialize_size_type &bufferSize, bool bDeep)
		{
			if (bufferSize < fixed_size_in_bytes::value)
				return false;
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_MAP_STATIC]);
			_v = *(internal_type*)buffer;
			buffer += fixed_size_in_bytes::value;
			bufferSize -= fixed_size_in_bytes::value;
			return true;
		}
	};

	#define ____LONGINT_NEGATE_FUNCTION(_SIZE)\
	static void LongInt_negate(const LongIntInternal<_SIZE>& a, LongIntInternal<_SIZE>& result){ \
		PREDA_CALL(LongInt_Negate_##_SIZE, &a, &result); \
	} \
	static bool LongInt_IsSign(const LongIntInternal<_SIZE>& a){ \
		return PREDA_CALL(LongInt_IsSign_##_SIZE, &a); \
	}
	#define ____LONGINT_ALL_FUNCTION(_SIZE, _INT_TYPE)\
	static void _INT_TYPE##_zero(LongIntInternal<_SIZE>& _fStruct){\
		PREDA_CALL(_INT_TYPE##_Zero_##_SIZE, &_fStruct);\
	}\
	static void _INT_TYPE##_ToString(const LongIntInternal<_SIZE>& _fStruct, char* buf){ \
		PREDA_CALL(_INT_TYPE##_ConvertToString_##_SIZE, &_fStruct, buf); \
	}\
    static void _INT_TYPE##_fromInt(LongIntInternal<_SIZE>& _fStruct, int64_t in){\
		PREDA_CALL(_INT_TYPE##_fromInt_##_SIZE, &_fStruct, in);\
	}\
    static void _INT_TYPE##_fromUInt(LongIntInternal<_SIZE>& _fStruct, uint64_t in){\
		PREDA_CALL(_INT_TYPE##_fromUInt_##_SIZE, &_fStruct, in);\
	}\
	static int _INT_TYPE##_toInt64(const LongIntInternal<_SIZE>& _fStruct, int64_t& result){\
		return PREDA_CALL(_INT_TYPE##_toInt64_##_SIZE, &_fStruct, &result);\
	}\
    static int _INT_TYPE##_toUInt64(const LongIntInternal<_SIZE>& _fStruct, uint64_t& result){\
		return PREDA_CALL(_INT_TYPE##_toUInt64_##_SIZE, &_fStruct, &result);\
	}\
	static void _INT_TYPE##_rightShift(LongIntInternal<_SIZE>& a, int64_t shift){\
		PREDA_CALL(_INT_TYPE##_rightShift_##_SIZE, &a, shift);\
	}\
    static void _INT_TYPE##_leftShift(LongIntInternal<_SIZE>& a, int64_t shift){\
		PREDA_CALL(_INT_TYPE##_leftShift_##_SIZE, &a, shift);\
	}\
	static uint32_t _INT_TYPE##_GetConvertToStringLen(const LongIntInternal<_SIZE>& _fStruct){ \
		return PREDA_CALL(_INT_TYPE##_GetConvertToStringLen_##_SIZE, &_fStruct); \
	}\
	static void _INT_TYPE##_ConvertFromString(LongIntInternal<_SIZE>& _fStruct, const char* longint_literal){ \
		PREDA_CALL(_INT_TYPE##_ConvertFromString_##_SIZE, &_fStruct, longint_literal); \
	}\
	static void _INT_TYPE##_ConvertFromHexString(LongIntInternal<_SIZE>& _fStruct, const char* longint_literal){ \
		PREDA_CALL(_INT_TYPE##_ConvertFromHexString_##_SIZE, &_fStruct, longint_literal); \
	}\
	static void _INT_TYPE##_add(const LongIntInternal<_SIZE>& a, const LongIntInternal<_SIZE>& b, LongIntInternal<_SIZE>& result){ \
		PREDA_CALL(_INT_TYPE##_Add_##_SIZE, &a, &b, &result); \
	}\
	static void _INT_TYPE##_sub(const LongIntInternal<_SIZE>& a, const LongIntInternal<_SIZE>& b, LongIntInternal<_SIZE>& result){ \
		PREDA_CALL(_INT_TYPE##_Sub_##_SIZE, &a, &b, &result); \
	}\
	static void _INT_TYPE##_mul(const LongIntInternal<_SIZE>& a, const  LongIntInternal<_SIZE>& b, LongIntInternal<_SIZE>& result){ \
		PREDA_CALL(_INT_TYPE##_Mul_##_SIZE, &a, &b, &result); \
	}\
	static void _INT_TYPE##_div(const LongIntInternal<_SIZE>& a, const  LongIntInternal<_SIZE>& b, LongIntInternal<_SIZE>& result){ \
		PREDA_CALL(_INT_TYPE##_Div_##_SIZE, &a, &b, &result); \
	}\
	static void _INT_TYPE##_mod(const LongIntInternal<_SIZE>& a, const  LongIntInternal<_SIZE>& b, LongIntInternal<_SIZE>& result){ \
		PREDA_CALL(_INT_TYPE##_Mod_##_SIZE, &a, &b, &result); \
	}\
	static int _INT_TYPE##_compare(const LongIntInternal<_SIZE>& a, const LongIntInternal<_SIZE>& b){ \
		return 	PREDA_CALL(_INT_TYPE##_Compare_##_SIZE, &a, &b); \
	}\
	static int _INT_TYPE##_isZero(const LongIntInternal<_SIZE>& a){ \
		return 	PREDA_CALL(_INT_TYPE##_IsZero_##_SIZE, &a); \
	}\
	static void _INT_TYPE##_SetMax(LongIntInternal<_SIZE>& a){ \
		return 	PREDA_CALL(_INT_TYPE##_SetMax_##_SIZE, &a); \
	}\
	static void _INT_TYPE##_SetMin(LongIntInternal<_SIZE>& a){ \
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

	template <uint32_t Size> constexpr type_identifier_enum ____get_type_identifier_enum_of_long_int_type();
	template <> constexpr type_identifier_enum ____get_type_identifier_enum_of_long_int_type<128>() { return type_identifier_enum::___int128; }
	template <> constexpr type_identifier_enum ____get_type_identifier_enum_of_long_int_type<256>() { return type_identifier_enum::___int256; }
	template <> constexpr type_identifier_enum ____get_type_identifier_enum_of_long_int_type<512>() { return type_identifier_enum::___int512; }
	template <uint32_t Size> constexpr type_identifier_enum ____get_type_identifier_enum_of_long_uint_type();
	template <> constexpr type_identifier_enum ____get_type_identifier_enum_of_long_uint_type<128>() { return type_identifier_enum::___uint128; }
	template <> constexpr type_identifier_enum ____get_type_identifier_enum_of_long_uint_type<256>() { return type_identifier_enum::___uint256; }
	template <> constexpr type_identifier_enum ____get_type_identifier_enum_of_long_uint_type<512>() { return type_identifier_enum::___uint512; }

	template<short Size>
	constexpr prlrt::LongIntInternal<Size> ____get_max_value_of_longint()
	{
		prlrt::LongIntInternal<Size> max;
		for(int i = 0; i < (Size / 8) - 1; i++)
		{
			max._Data[i] = 0xff;
		}
		max._Data[Size / 8 - 1] = 0x7f;
		return max;
	}
	template<short Size>
	constexpr prlrt::LongIntInternal<Size> ____get_min_value_of_longint()
	{
		prlrt::LongIntInternal<Size> min;
		min._Data[Size / 8 - 1] = 0x80;
		return min;
	}
	template<short Size>
	constexpr prlrt::LongIntInternal<Size> ____get_max_value_of_ulongint()
	{
		prlrt::LongIntInternal<Size> max;
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
		using internal_type = prlrt::LongIntInternal<Size>;
		using impl_type = ____longintType;
		using is_value_type = std::true_type;
		using is_fixed_size = std::true_type;
		using fixed_size_in_bytes = std::integral_constant<serialize_size_type, serialize_size_type(sizeof(internal_type))>;
		using type_identifier_type = simple_type_type_identifier<____get_type_identifier_enum_of_long_int_type<Size>()>;
		constexpr static internal_type max_value = ____get_max_value_of_longint<Size>();
		constexpr static internal_type min_value = ____get_min_value_of_longint<Size>();
		constexpr static short gas_coefficient = Size / 64;
		static constexpr uint32_t get_type_identifier_size()
		{
			return type_identifier_type::value.length();
		}

		static constexpr const uint8_t* get_type_identifier_buffer()
		{
			return type_identifier_type::value.data;
		}

		internal_type _fStruct;
		____longint() {}
		____longint(const char* longint_literal){
			burn_gas((uint64_t)gas_costs[PRDOP_INT_ASSIGN] * gas_coefficient);
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
			burn_gas((uint64_t)gas_costs[PRDOP_INT_ASSIGN] * gas_coefficient);
			impl_type::LongInt_fromInt(_fStruct, (int64_t)x._v);
		}
		template<typename T_OtherInternal>
		____longint(const ____uint<T_OtherInternal>& x){
			burn_gas((uint64_t)gas_costs[PRDOP_INT_ASSIGN] * gas_coefficient);
			impl_type::LongInt_fromUInt(_fStruct, (uint64_t)x._v);
		}

		template<short T_OtherSize>
		____longint(const ____longint<T_OtherSize>& x){
			burn_gas((uint64_t)gas_costs[PRDOP_INT_ASSIGN] * gas_coefficient);
			if constexpr(Size < T_OtherSize)
			{
				____longint<T_OtherSize> max;
				memcpy(max._fStruct._Data, max_value._Data, std::min(sizeof(max_value._Data), sizeof(max._fStruct._Data)));
				if(max.lt(x))
				{
					preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
				}
				____longint<T_OtherSize> min;
				memset(min._fStruct._Data, 0xff, sizeof(min._fStruct._Data));
				memcpy(min._fStruct._Data, min_value._Data, std::min(sizeof(min_value._Data), sizeof(min._fStruct._Data)));
				if(min.gt(x))
				{
					preda_exception::throw_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
				}
			}
			if(impl_type::LongInt_IsSign(x._fStruct))
			{
				memset(_fStruct._Data, 0xff, sizeof(_fStruct._Data));
			}
			memcpy(_fStruct._Data, x._fStruct._Data, std::min(sizeof(_fStruct._Data), sizeof(x._fStruct._Data)));
		}

		template<short T_OtherSize>
		____longint(const ____ulongint<T_OtherSize>& x){
			burn_gas((uint64_t)gas_costs[PRDOP_INT_ASSIGN] * gas_coefficient);
			if constexpr(Size <= T_OtherSize)
			{
				____ulongint<T_OtherSize> max;
				memcpy(max._fStruct._Data, max_value._Data, std::min(sizeof(max_value._Data), sizeof(max._fStruct._Data)));
				if(max.lt(x))
				{
					preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
				}
			}
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
			burn_gas((uint64_t)gas_costs[PRDOP_INT_ASSIGN] * gas_coefficient);
			_fStruct = rhs._fStruct;
		}
		void operator=(const internal_type &rhs)
		{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_ASSIGN] * gas_coefficient);
			_fStruct = rhs;
		}
		void operator++(){
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SELF] * gas_coefficient);
			if (isMaxValue())
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			internal_type result;
			impl_type::LongInt_add(_fStruct, this_type((int8_t)1)._fStruct, result);
			_fStruct = result;
		}
		void operator--(){
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SELF] * gas_coefficient);
			if (isMinValue())
			{
				preda_exception::throw_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			internal_type result;
			impl_type::LongInt_sub(_fStruct, this_type((int8_t)1)._fStruct, result);
			_fStruct = result;
		}
		FORWARD_POST_INC_DEC_TO_PRE_INC_DEC
		this_type operator-() const{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SELF] * gas_coefficient);
			if (isMinValue())
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			internal_type result;
			impl_type::LongInt_negate(_fStruct, result);
			return this_type(result);
		}
		this_type operator+(const this_type &rhs) const{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE] * gas_coefficient);
			internal_type tmp_sub_result_1;
			impl_type::LongInt_sub(max_value, _fStruct, tmp_sub_result_1);
			internal_type tmp_sub_result_2;
			impl_type::LongInt_sub(min_value, _fStruct, tmp_sub_result_2);
			if ((!impl_type::LongInt_IsSign(_fStruct) && this_type(tmp_sub_result_1).lt(rhs)) || (impl_type::LongInt_IsSign(_fStruct) && this_type(tmp_sub_result_2).gt(rhs)))
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			internal_type result;
			impl_type::LongInt_add(_fStruct, rhs._fStruct, result);
			return this_type(result);
		}
		this_type operator-(const this_type &rhs) const{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE] * gas_coefficient);
			internal_type tmp_add_result_1;
			impl_type::LongInt_add(min_value, rhs._fStruct, tmp_add_result_1);
			internal_type tmp_add_result_2;
			impl_type::LongInt_add(max_value, rhs._fStruct, tmp_add_result_2);
			if ((!impl_type::LongInt_IsSign(rhs._fStruct) && lt(this_type(tmp_add_result_1))) || (impl_type::LongInt_IsSign(rhs._fStruct) && gt(this_type(tmp_add_result_2))))
			{
				preda_exception::throw_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			}
			internal_type result;
			impl_type::LongInt_sub(_fStruct, rhs._fStruct, result);
			return this_type(result);
		}
		this_type operator*(const this_type &rhs) const{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_COMPLEX] * gas_coefficient);
			internal_type tmp_div_result_1;
			impl_type::LongInt_div(max_value, rhs._fStruct, tmp_div_result_1);
			internal_type tmp_div_result_2;
			impl_type::LongInt_div(min_value, rhs._fStruct, tmp_div_result_2);
			if (!impl_type::LongInt_IsSign(_fStruct))
			{
				if (!impl_type::LongInt_IsSign(rhs._fStruct))
				{
					if (this_type(tmp_div_result_1).lt(*this))
					{
						preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
					}
				}
				else if (impl_type::LongInt_IsSign(rhs._fStruct))
				{
					if (this_type(tmp_div_result_2).lt(*this))
					{
						preda_exception::throw_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
					}
				}
			}
			else
			{
				if (!impl_type::LongInt_IsSign(rhs._fStruct))
				{
					if (this_type(tmp_div_result_2).gt(*this))
					{
						preda_exception::throw_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
					}
				}
				else if (impl_type::LongInt_IsSign(rhs._fStruct))
				{
					if (this_type(tmp_div_result_1).gt(*this))
					{
						preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
					}
				}
			}
			internal_type result;
			impl_type::LongInt_mul(_fStruct, rhs._fStruct, result);
			return this_type(result);
		}

		bool isZero() const{return impl_type::LongInt_isZero(_fStruct);}
		bool isNegative() const{return impl_type::LongInt_IsSign(_fStruct);}
		bool eq(const this_type& rhs) const {return 0 == impl_type::LongInt_compare(_fStruct, rhs._fStruct);}
		bool notEq(const this_type& rhs) const {return !eq(rhs);}
		bool lt(const this_type& rhs) const {return -1 == impl_type::LongInt_compare(_fStruct, rhs._fStruct);}
		bool gt(const this_type& rhs) const {return 1 == impl_type::LongInt_compare(_fStruct, rhs._fStruct);}
		bool slt(const this_type& rhs) const {return !gt(rhs);}
		bool sgt(const this_type& rhs) const {return !lt(rhs);}
		bool isMaxValue() const {return eq(this_type(max_value));}
		bool isMinValue() const {return eq(this_type(min_value));}

		this_type operator/(const this_type &rhs) const{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_COMPLEX] * gas_coefficient);
			if (rhs.isZero())
			{
				preda_exception::throw_exception("divide by zero in " + std::string(__FUNCTION__), prlrt::ExceptionType::DividedByZero);
			}
			if (impl_type::LongInt_IsSign(rhs._fStruct) && isMinValue())
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			internal_type result;
			impl_type::LongInt_div(_fStruct, rhs._fStruct, result);
			return this_type(result);
		}
		this_type operator%(const this_type &rhs) const{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_COMPLEX] * gas_coefficient);
			if (rhs.isZero())
			{
				preda_exception::throw_exception("divide by zero in " + std::string(__FUNCTION__), prlrt::ExceptionType::DividedByZero);
			}
			if (impl_type::LongInt_IsSign(rhs._fStruct) && isMinValue())
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			internal_type result;
			impl_type::LongInt_mod(_fStruct, rhs._fStruct, result);
			return this_type(result);
		}
		__prlt_bool operator==(const this_type& rhs) const{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE] * gas_coefficient);
			return __prlt_bool(eq(rhs));
		}
		__prlt_bool operator!=(const this_type& rhs) const{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE] * gas_coefficient);
			return __prlt_bool(notEq(rhs));
		}
		__prlt_bool operator>=(const this_type& rhs) const{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE] * gas_coefficient);
			return __prlt_bool(sgt(rhs));
		}
		__prlt_bool operator<=(const this_type& rhs) const{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE] * gas_coefficient);
			return __prlt_bool(slt(rhs));
		}
		__prlt_bool operator<(const this_type& rhs) const{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE] * gas_coefficient);
			return __prlt_bool(lt(rhs));
		}
		__prlt_bool operator>(const this_type& rhs) const{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE] * gas_coefficient);
			return __prlt_bool(gt(rhs));
		}

		bool ToInt64(int64_t& result) const{return impl_type::LongInt_toInt64(_fStruct, result) <= 0;}
		bool ToUInt64(uint64_t& result) const{return impl_type::LongInt_toUInt64(_fStruct, result) <= 0;}

		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(+);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(-);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(*);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(/);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(%);

		template<typename T_OtherInternal>
		explicit operator ____int<T_OtherInternal>() { 
			int64_t result;
			if(!ToInt64(result) || result > ____int<T_OtherInternal>::max_value::value)
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			else if(result < ____int<T_OtherInternal>::min_value::value)
			{
				preda_exception::throw_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			}
			return ____int<T_OtherInternal>(T_OtherInternal(result));
		}

		template<typename T_OtherInternal>
		explicit operator ____uint<T_OtherInternal>() { 
			uint64_t result;
			if(!ToUInt64(result) || result > ____uint<T_OtherInternal>::max_value::value)
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			else if(impl_type::LongInt_IsSign(_fStruct))
			{
				preda_exception::throw_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			}
			return ____uint<T_OtherInternal>(T_OtherInternal(result));
		}

		std::string ToString() const{
			uint32_t len = impl_type::LongInt_GetConvertToStringLen(_fStruct);
			std::vector<char> buf(len + 1, '\0');
			impl_type::LongInt_ToString(_fStruct, &buf[0]);
			return std::string(&buf[0], len);
		}
		serialize_size_type get_serialize_size() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_SIZE]);
			return fixed_size_in_bytes::value;
		}
		void serialize_out(uint8_t *buffer, bool for_debug) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_OUT_STATIC] + (uint64_t)gas_costs[PRDOP_SERIALIZE_DYNAMIC] * fixed_size_in_bytes::value);
			(*(this_type*)buffer)._fStruct = _fStruct;
		}
		bool map_from_serialized_data(uint8_t *&buffer, serialize_size_type &bufferSize, bool bDeep)
		{
			if (bufferSize < fixed_size_in_bytes::value)
				return false;
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_MAP_STATIC] + (uint64_t)gas_costs[PRDOP_SERIALIZE_DYNAMIC] * fixed_size_in_bytes::value);
			_fStruct = *(internal_type*)buffer;
			buffer += fixed_size_in_bytes::value;
			bufferSize -= fixed_size_in_bytes::value;
			return true;
		}
	};

#define ULONGINT_BITWISE_OPERATOR(oper, gas)\
this_type operator oper(const this_type &rhs) const\
{\
	burn_gas(gas);\
	this_type result;\
	for(int i = 0; i < sizeof(result._fStruct._Data)/sizeof(uint8_t); i++)\
	{\
		result._fStruct._Data[i] = _fStruct._Data[i] oper rhs._fStruct._Data[i];\
	}\
	return result;\
}

template<short Size>
	struct ____ulongint
	{
		using this_type = ____ulongint<Size>;
		using impl_type = ____longintType;
		using is_value_type = std::true_type;
		using is_fixed_size = std::true_type;
		using internal_type = prlrt::LongIntInternal<Size>;
		using fixed_size_in_bytes = std::integral_constant<serialize_size_type, serialize_size_type(sizeof(internal_type))>;
		using type_identifier_type = simple_type_type_identifier<____get_type_identifier_enum_of_long_uint_type<Size>()>;
		constexpr static internal_type max_value = ____get_max_value_of_ulongint<Size>();
		constexpr static short gas_coefficient = Size / 64;
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
			if(x._v < 0)
			{
				preda_exception::throw_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			}
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
				preda_exception::throw_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			}
			else if(Size < T_OtherSize)
			{
				____longint<T_OtherSize> max;
				memcpy(max._fStruct._Data, max_value._Data, std::min(sizeof(max_value._Data), sizeof(max._fStruct._Data)));
				if(max.lt(x))
				{
					preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
				}
			}
			memcpy(_fStruct._Data, x._fStruct._Data, std::min(sizeof(_fStruct._Data), sizeof(x._fStruct._Data)));
		}

		template<short T_OtherSize>
		____ulongint(const ____ulongint<T_OtherSize>& x){
			if constexpr(Size < T_OtherSize)
			{
				____ulongint<T_OtherSize> max;
				memcpy(max._fStruct._Data, max_value._Data, std::min(sizeof(max_value._Data), sizeof(max._fStruct._Data)));
				if(max.lt(x))
				{
					preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
				}
			}
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
			burn_gas((uint64_t)gas_costs[PRDOP_INT_ASSIGN] * gas_coefficient);
			_fStruct = rhs._fStruct;
		}
		void operator++(){
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SELF] * gas_coefficient);
			if (isMaxValue())
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			internal_type result;
			impl_type::ULongInt_add(_fStruct, this_type((int8_t)1)._fStruct, result);
			_fStruct = result;
		}
		void operator--(){
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SELF] * gas_coefficient);
			if (isZero())
			{
				preda_exception::throw_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			internal_type result;
			impl_type::ULongInt_sub(_fStruct, this_type((int8_t)1)._fStruct, result);
			_fStruct = result;
		}
		FORWARD_POST_INC_DEC_TO_PRE_INC_DEC
		this_type operator~() const{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SELF] * gas_coefficient);
			this_type result;
			for(int i = 0; i < sizeof(result._fStruct._Data) / sizeof(uint8_t); i++)
				result._fStruct._Data[i] = ~_fStruct._Data[i];
			return result;
		}
		this_type operator+(const this_type &rhs) const{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE] * gas_coefficient);
			internal_type tmp_sub_result;
			impl_type::ULongInt_sub(max_value, _fStruct, tmp_sub_result);
			if (this_type(tmp_sub_result).lt(rhs))
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			internal_type result;
			impl_type::ULongInt_add(_fStruct, rhs._fStruct, result);
			return this_type(result);
		}
		this_type operator-(const this_type &rhs) const{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE] * gas_coefficient);
			if(lt(rhs))
			{
				preda_exception::throw_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			internal_type result;
			impl_type::ULongInt_sub(_fStruct, rhs._fStruct, result);
			this_type out(result);
			return out;
		}
		this_type operator*(const this_type &rhs) const{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_COMPLEX] * gas_coefficient);
			internal_type tmp_div_result_1;
			impl_type::ULongInt_div(max_value, _fStruct, tmp_div_result_1);
			if (this_type(tmp_div_result_1).lt(rhs))
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			internal_type result;
			impl_type::ULongInt_mul(_fStruct, rhs._fStruct, result);
			this_type out(result);
			return out;
		}
		bool isZero() const{return impl_type::ULongInt_isZero(_fStruct);}
		bool eq(const this_type& rhs) const { return 0 == impl_type::ULongInt_compare(_fStruct, rhs._fStruct); }
		bool notEq(const this_type& rhs) const { return !eq(rhs); }
		bool lt(const this_type& rhs) const {return -1 == impl_type::ULongInt_compare(_fStruct, rhs._fStruct);}
		bool gt(const this_type& rhs) const {return 1 == impl_type::ULongInt_compare(_fStruct, rhs._fStruct);}
		bool slt(const this_type& rhs) const {return !gt(rhs);}
		bool sgt(const this_type& rhs) const {return !lt(rhs);}
		bool isMaxValue() const {return 0 == (impl_type::ULongInt_compare(_fStruct, this_type(max_value)._fStruct));}

		this_type operator/(const this_type &rhs) const{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_COMPLEX] * gas_coefficient);
			if(rhs.isZero()){
				preda_exception::throw_exception("divide by zero in " + std::string(__FUNCTION__), prlrt::ExceptionType::DividedByZero);
			}
			internal_type result;
			impl_type::ULongInt_div(_fStruct, rhs._fStruct, result);
			return this_type(result);
		}
		this_type operator%(const this_type &rhs) const{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_COMPLEX] * gas_coefficient);
			if(rhs.isZero()){
				preda_exception::throw_exception("divide by zero in " + std::string(__FUNCTION__), prlrt::ExceptionType::DividedByZero);
			}
			internal_type result;
			impl_type::ULongInt_mod(_fStruct, rhs._fStruct, result);
			return this_type(result);
		}
		__prlt_bool operator==(const this_type& rhs) const{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE] * gas_coefficient);
			int result = impl_type::ULongInt_compare(_fStruct, rhs._fStruct);
			return __prlt_bool(eq(rhs));
		}
		__prlt_bool operator!=(const this_type& rhs) const{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE] * gas_coefficient);
			int result = impl_type::ULongInt_compare(_fStruct, rhs._fStruct);
			return __prlt_bool(notEq(rhs));
		}
		__prlt_bool operator>=(const this_type& rhs) const{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE] * gas_coefficient);
			int result = impl_type::ULongInt_compare(_fStruct, rhs._fStruct);
			return __prlt_bool(sgt(rhs));
		}
		__prlt_bool operator<=(const this_type& rhs) const{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE] * gas_coefficient);
			int result = impl_type::ULongInt_compare(_fStruct, rhs._fStruct);
			return __prlt_bool(slt(rhs));
		}
		__prlt_bool operator<(const this_type& rhs) const{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE] * gas_coefficient);
			int result = impl_type::ULongInt_compare(_fStruct, rhs._fStruct);
			return __prlt_bool(lt(rhs));
		}
		__prlt_bool operator>(const this_type& rhs) const{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE] * gas_coefficient);
			int result = impl_type::ULongInt_compare(_fStruct, rhs._fStruct);
			return __prlt_bool(gt(rhs));
		}
		this_type operator<<(const this_type& x)
		{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE] * gas_coefficient);
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
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE] * gas_coefficient);
			int64_t bitWidth;
			if(!x.ToInt64(bitWidth) || bitWidth >= Size)
			{
				return ____ulongint();
			}
			this_type result = *this;
			impl_type::ULongInt_rightShift(result._fStruct, bitWidth);
			return result;
		}
		template<typename T_OtherIntType>
		this_type operator<<(const T_OtherIntType& x)
		{
			burn_gas((uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE] * gas_coefficient);
			int64_t bitWidth = x._v;
			if(bitWidth >= Size)
			{
				return ____ulongint();
			}
			this_type result = *this;
			impl_type::ULongInt_leftShift(result._fStruct, bitWidth);
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
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(%);
		ULONGINT_BITWISE_OPERATOR(&, (uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE] * gas_coefficient);
		ULONGINT_BITWISE_OPERATOR(^, (uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE] * gas_coefficient);
		ULONGINT_BITWISE_OPERATOR(|, (uint64_t)gas_costs[PRDOP_INT_OP_SIMPLE] * gas_coefficient);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(&);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(^);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(|);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(<<);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(>>);

		template<typename T_OtherInternal>
		explicit operator ____int<T_OtherInternal>() { 
			int64_t result;
			if(!ToInt64(result) || result > ____int<T_OtherInternal>::max_value::value)
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			return ____int<T_OtherInternal>(T_OtherInternal(result));
		}

		template<typename T_OtherInternal>
		explicit operator ____uint<T_OtherInternal>() { 
			uint64_t result;
			if(!ToUInt64(result) || result > ____uint<T_OtherInternal>::max_value::value)
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
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
		serialize_size_type get_serialize_size() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_SIZE]);
			return fixed_size_in_bytes::value;
		}
		void serialize_out(uint8_t *buffer, bool for_debug) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_OUT_STATIC] + (uint64_t)gas_costs[PRDOP_SERIALIZE_DYNAMIC] * fixed_size_in_bytes::value);
			(*(this_type*)buffer)._fStruct = _fStruct;
		}
		bool map_from_serialized_data(uint8_t *&buffer, serialize_size_type &bufferSize, bool bDeep)
		{
			if (bufferSize < fixed_size_in_bytes::value)
				return false;
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_MAP_STATIC] + (uint64_t)gas_costs[PRDOP_SERIALIZE_DYNAMIC] * fixed_size_in_bytes::value);
			_fStruct = *(internal_type*)buffer;
			buffer += fixed_size_in_bytes::value;
			bufferSize -= fixed_size_in_bytes::value;
			return true;
		}
	};
}
#undef ULONGINT_BITWISE_OPERATOR
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