#pragma once
#include "inttypes.h"
#include "gascost.h"
#include <algorithm>

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

	struct __prlt_bigint {
		using this_type = __prlt_bigint;
		using is_value_type = std::true_type;
		using is_fixed_size = std::false_type;
		using fixed_size_in_bytes = std::integral_constant<serialize_size_type, 0>;		// doesn't matter
		using type_identifier_type = simple_type_type_identifier<type_identifier_enum::___bigint>;
		static constexpr uint32_t get_type_identifier_size()
		{
			return type_identifier_type::value.length();
		}

		static constexpr const uint8_t* get_type_identifier_buffer()
		{
			return type_identifier_type::value.data;
		}

		BigintPtr _v = 0;
		const uint8_t *mapped_data = nullptr;

		inline uint32_t gas_coefficient() const
		{
			return PREDA_CALL(BigintGetEmbeddedSize, _v) / 8;
		}

		inline uint32_t bigger_gas_coefficient(const this_type& rhs) const
		{
			return std::max(gas_coefficient(), rhs.gas_coefficient());
		}

		__prlt_bigint()
		{
			_v = PREDA_CALL(CreateBigint);
			PREDA_CALL(BigintAssignInt64, _v, 0);
		}
		__prlt_bigint(const char *rhs, uint32_t len)
		{
			burn_gas((uint64_t)gas_costs[PRDOP_BIGINT_ASSIGN_STATIC] + (uint64_t)gas_costs[PRDOP_BIGINT_ASSIGN_DYNAMIC] * len);
			_v = PREDA_CALL(CreateBigint);
			PREDA_CALL(BigintAssignString, _v, rhs, len);
			test_overflow();
		}
		__prlt_bigint(int64_t rhs)
		{
			_v = PREDA_CALL(CreateBigint);
			PREDA_CALL(BigintAssignInt64, _v, rhs);
		}
		__prlt_bigint(BigintPtr v, uint8_t* data): _v(v), mapped_data(data) {}
		template<typename T_OtherInternal>
		__prlt_bigint(____uint<T_OtherInternal> rhs)
		{
			burn_gas((uint64_t)gas_costs[PRDOP_BIGINT_ASSIGN_STATIC]);
			_v = PREDA_CALL(CreateBigint);
			PREDA_CALL(BigintAssignUint64, _v, rhs._v);
			//TODO: check global memory overflow
		}
		template<typename T_OtherInternal>
		__prlt_bigint(____int<T_OtherInternal> rhs)
		{
			burn_gas((uint64_t)gas_costs[PRDOP_BIGINT_ASSIGN_STATIC]);
			_v = PREDA_CALL(CreateBigint);
			PREDA_CALL(BigintAssignInt64, _v, rhs._v);
			//TODO: check global memory overflow
		}
		template<short Size>
		__prlt_bigint(const ____longint<Size>& rhs)
		{
			burn_gas((uint64_t)gas_costs[PRDOP_BIGINT_ASSIGN_STATIC] * rhs.gas_coefficient);
			_v = PREDA_CALL(CreateBigint);
			bool sign = false;
			____ulongint<Size> tmpLongInt;
			if(rhs.isNegative())
			{
				if (memcmp(rhs._fStruct._Data, ____get_min_value_of_longint<Size>()._Data, sizeof(rhs._fStruct)) == 0)
				{
					tmpLongInt._fStruct = ____get_max_value_of_longint<Size>();
					tmpLongInt++;
				}
				else
				{
					tmpLongInt = -rhs;
				}
				sign = true;
			}
			else
			{
				tmpLongInt = rhs;
			}
			constexpr uint8_t len = Size / 64;
			for(uint8_t i = 0; i < len; i++)
			{
				uint64_t cur_word = *(uint64_t*)(tmpLongInt._fStruct._Data + i * sizeof(uint64_t)/sizeof(uint8_t));
				if(cur_word > 0)
				{
					____uint<uint64_t> u64(cur_word);
					this_type tmp(u64);
					PREDA_CALL(BigintShiftLeftInplace, tmp._v, 64 * i);
					*this += tmp;
				}
			}
			if(sign)
			{
				PREDA_CALL(BigintNegateInplace, _v);
			}
		}

		template<short Size>
		__prlt_bigint(const ____ulongint<Size>& rhs)
		{
			burn_gas((uint64_t)gas_costs[PRDOP_BIGINT_ASSIGN_STATIC] * rhs.gas_coefficient);
			_v = PREDA_CALL(CreateBigint);
			constexpr uint8_t len = Size / 64;
			for(uint8_t i = 0; i < len; i++)
			{
				uint64_t cur_word = *(uint64_t*)(rhs._fStruct._Data + i * sizeof(uint64_t)/sizeof(uint8_t));
				if(cur_word > 0)
				{
					____uint<uint64_t> u64(cur_word);
					this_type tmp(u64);
					PREDA_CALL(BigintShiftLeftInplace, tmp._v, 64 * i);
					*this += tmp;
				}
			}
		}
		~__prlt_bigint()
		{
			PREDA_CALL(ReleaseBigint, _v);
		}

		__prlt_bigint(const this_type &rhs)
		{
			_v = PREDA_CALL(CreateBigint);
			PREDA_CALL(BigintAssign, _v, rhs._v);
			//TODO: check global memory overflow
		}

		bool IsNegative() const
		{
			return PREDA_CALL(BigintIsNegative, _v);
		}

		void operator=(const this_type &rhs)
		{
			burn_gas((uint64_t)gas_costs[PRDOP_BIGINT_ASSIGN_STATIC] * rhs.gas_coefficient());
			PREDA_CALL(BigintAssign, _v, rhs._v);
			//TODO: check global memory overflow
		}

		void operator++()
		{
			burn_gas((uint64_t)gas_costs[PRDOP_BIGINT_OP_SELF] * gas_coefficient());
			BigintPtr v = PREDA_CALL(CreateBigint);
			PREDA_CALL(BigintAssignInt64, v, 1);
			PREDA_CALL(BigintAddInplace, _v, v);
			test_overflow();
		}

		void operator--()
		{
			burn_gas((uint64_t)gas_costs[PRDOP_BIGINT_OP_SELF] * gas_coefficient());
			BigintPtr v = PREDA_CALL(CreateBigint);
			PREDA_CALL(BigintAssignInt64, v, 1);
			PREDA_CALL(BigintSubInplace, _v, v);
			test_overflow();
		}

		FORWARD_POST_INC_DEC_TO_PRE_INC_DEC;

		this_type operator-() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_BIGINT_OP_SELF] * gas_coefficient());
			BigintPtr v = PREDA_CALL(CreateBigint);
			PREDA_CALL(BigintNegate, v, _v);
			return this_type(v, nullptr);
		}

		this_type operator+(const this_type &rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_BIGINT_OP_SIMPLE] * bigger_gas_coefficient(rhs));
			BigintPtr v = PREDA_CALL(CreateBigint);
			PREDA_CALL(BigintAdd, v, _v, rhs._v);
			this_type ret(v, nullptr);
			ret.test_overflow();
			//TODO: check global memory overflow
			return ret;
		}
		this_type operator-(const this_type &rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_BIGINT_OP_SIMPLE] * bigger_gas_coefficient(rhs));
			BigintPtr v = PREDA_CALL(CreateBigint);
			PREDA_CALL(BigintSub, v, _v, rhs._v);
			this_type ret(v, nullptr);
			ret.test_overflow();
			//TODO: check global memory overflow
			return ret;
		}
		this_type operator*(const this_type &rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_BIGINT_OP_COMPLEX] * bigger_gas_coefficient(rhs));
			BigintPtr v = PREDA_CALL(CreateBigint);
			PREDA_CALL(BigintMul, v, _v, rhs._v);
			this_type ret(v, nullptr);
			ret.test_overflow();
			//TODO: check global memory overflow
			return ret;
		}
		this_type operator/(const this_type& rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_BIGINT_OP_COMPLEX] * bigger_gas_coefficient(rhs));
			if (0 == PREDA_CALL(BigintCompare, rhs._v, __prlt_bigint(0)._v))
			{
				preda_exception::throw_exception("divide by zero in " + std::string(__FUNCTION__), prlrt::ExceptionType::DividedByZero);
			}
			BigintPtr v = PREDA_CALL(CreateBigint);
			PREDA_CALL(BigintDiv, v, _v, rhs._v, 0);
			this_type ret(v, nullptr);
			ret.test_overflow();
			//TODO: check global memory overflow
			return ret;
		}
		this_type __prli_div_uint32(const __prlt_uint32 &rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_BIGINT_OP_COMPLEX] * gas_coefficient());
			if (rhs._v == 0)
			{
				preda_exception::throw_exception("divide by zero in " + std::string(__FUNCTION__), prlrt::ExceptionType::DividedByZero);
			}
			BigintPtr v = PREDA_CALL(CreateBigint);
			PREDA_CALL(BigintDiv_Uint32, v, _v, rhs._v, 0);
			//TODO: check global memory overflow
			return this_type(v, nullptr);
		}
		this_type operator%(const this_type& rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_BIGINT_OP_COMPLEX] * bigger_gas_coefficient(rhs));
			if (0 == PREDA_CALL(BigintCompare, rhs._v, __prlt_bigint(0)._v))
			{
				preda_exception::throw_exception("mod by zero in " + std::string(__FUNCTION__), prlrt::ExceptionType::DividedByZero);
			}
			BigintPtr v = PREDA_CALL(CreateBigint);
			PREDA_CALL(BigintMod, v, _v, rhs._v);
			this_type ret(v, nullptr);
			ret.test_overflow();
			//TODO: check global memory overflow
			return ret;
		}

		void operator+=(const this_type &rhs) const
		{
			burn_gas(((uint64_t)gas_costs[PRDOP_BIGINT_OP_SIMPLE] + (uint64_t)gas_costs[PRDOP_BIGINT_ASSIGN_STATIC]) * bigger_gas_coefficient(rhs));
			PREDA_CALL(BigintAddInplace, _v, rhs._v);
			test_overflow();
			//TODO: check global memory overflow
		}
		void operator-=(const this_type &rhs) const
		{
			burn_gas(((uint64_t)gas_costs[PRDOP_BIGINT_OP_SIMPLE] + (uint64_t)gas_costs[PRDOP_BIGINT_ASSIGN_STATIC]) * bigger_gas_coefficient(rhs));
			PREDA_CALL(BigintSubInplace, _v, rhs._v);
			test_overflow();
			//TODO: check global memory overflow
		}
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(*);
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(/ );
		EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(%);

		__prlt_bool operator ==(const this_type &rhs) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_BIGINT_OP_SIMPLE] * bigger_gas_coefficient(rhs));
			return PREDA_CALL(BigintCompare, _v, rhs._v) == 0;
		}
		__prlt_bool operator !=(const this_type &rhs) const
		{	
			burn_gas((uint64_t)gas_costs[PRDOP_BIGINT_OP_SIMPLE] * bigger_gas_coefficient(rhs));
			return PREDA_CALL(BigintCompare, _v, rhs._v) != 0;
		}
		__prlt_bool operator <(const this_type &rhs) const
		{	
			burn_gas((uint64_t)gas_costs[PRDOP_BIGINT_OP_SIMPLE] * bigger_gas_coefficient(rhs));
			return PREDA_CALL(BigintCompare, _v, rhs._v) < 0;
		}
		__prlt_bool operator >(const this_type &rhs) const
		{	
			burn_gas((uint64_t)gas_costs[PRDOP_BIGINT_OP_SIMPLE] * bigger_gas_coefficient(rhs));
			return PREDA_CALL(BigintCompare, _v, rhs._v) > 0;
		}
		__prlt_bool operator <=(const this_type &rhs) const
		{	
			burn_gas((uint64_t)gas_costs[PRDOP_BIGINT_OP_SIMPLE] * bigger_gas_coefficient(rhs));
			return PREDA_CALL(BigintCompare, _v, rhs._v) <= 0;
		}
		__prlt_bool operator >=(const this_type &rhs) const
		{	
			burn_gas((uint64_t)gas_costs[PRDOP_BIGINT_OP_SIMPLE] * bigger_gas_coefficient(rhs));
			return PREDA_CALL(BigintCompare, _v, rhs._v) >= 0;
		}

		template<typename T_OtherInternal>
		explicit operator ____uint<T_OtherInternal>() const
		{
			uint64_t v;
			int res = PREDA_CALL(BigintToUint64, _v, &v);
			if (res > 0)
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			if (res < 0)
			{
				preda_exception::throw_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			}
			if (v > uint64_t(____uint<T_OtherInternal>::max_value::value))
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			return ____uint<T_OtherInternal>(T_OtherInternal(v));
		}

		template<typename T_OtherInternal>
		explicit operator ____int<T_OtherInternal>() const
		{
			int64_t v;
			int res = PREDA_CALL(BigintToInt64, _v, &v);
			if (res > 0)
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			if (res < 0)
			{
				preda_exception::throw_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			}
			if (v > int64_t(____int<T_OtherInternal>::max_value::value))
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			if (v < int64_t(____int<T_OtherInternal>::min_value::value))
			{
				preda_exception::throw_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			}
			return ____int<T_OtherInternal>(T_OtherInternal(v));
		}
		template<short Size>
		explicit operator ____longint<Size>() const
		{
			static ____longint<Size> longintMax(____get_max_value_of_longint<Size>());
			this_type longintBNmax(longintMax);
			this_type longintBNmin = -(longintBNmax + 1);
			____longint<Size> result;
			if(*this > longintBNmax)
			{
				preda_exception::throw_exception("overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Overflow);
			}
			else if(*this < longintBNmin)
			{
				preda_exception::throw_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			}
			constexpr uint8_t len = Size / 64;
			bool sign = IsNegative();
			this_type positive_bint;
			if (sign)
			{
				PREDA_CALL(BigintNegate, positive_bint._v, _v);
			}
			else
			{
				positive_bint = *this;
			}
			for(int i = len - 1; i >= 0; i--)
			{
				this_type tmp = positive_bint;
				PREDA_CALL(BigintShiftRightInplace, tmp._v, 64 * i);
				*(uint64_t*)(result._fStruct._Data + i * sizeof(uint64_t)/sizeof(uint8_t)) =  ____uint<uint64_t>(tmp)._v;
				PREDA_CALL(BigintShiftLeftInplace, tmp._v, 64 * i);
				positive_bint -= tmp;
			}
			if(sign)
			{
				return -result;
			}
			return result;
		}
		template<short Size>
		explicit operator ____ulongint<Size>() const
		{
			//converting bigint to uint64 will throw if overflown, this won't work for underflown
			____ulongint<Size> result;
			if(IsNegative())
			{
				preda_exception::throw_exception("underflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::Underflow);
			}
			constexpr uint8_t len = Size / 64;
			for(int i = len - 1; i >= 0; i--)
			{
				this_type tmp = *this;
				PREDA_CALL(BigintShiftRightInplace, tmp._v, 64 * i);
				*(uint64_t*)(result._fStruct._Data + i * sizeof(uint64_t)/sizeof(uint8_t)) =  ____uint<uint64_t>(tmp)._v;
				PREDA_CALL(BigintShiftLeftInplace, tmp._v, 64 * i);
				*this -= tmp;
			}
			return result;
		}
		void test_overflow() const
		{
			if (!PREDA_CALL(BigintIsEmbeddable, _v))
				preda_exception::throw_exception("bigint overflow in " + std::string(__FUNCTION__), prlrt::ExceptionType::BigIntOverFlow);
		}

		serialize_size_type get_serialize_size() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_SIZE]);
			return PREDA_CALL(BigintGetEmbeddedSize, _v);
		}

		void serialize_out(uint8_t *buffer, bool for_debug) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_OUT_STATIC] + (uint64_t)gas_costs[PRDOP_SERIALIZE_DYNAMIC] * PREDA_CALL(BigintGetEmbeddedSize, _v));
			PREDA_CALL(BigintEmbed, _v, buffer);
		}

		bool map_from_serialized_data(const uint8_t *&buffer, serialize_size_type &bufferSize, bool bDeep)
		{
			uint32_t consumed = PREDA_CALL(BigintInitFromEmbedded, _v, buffer, bufferSize);
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_MAP_STATIC] + (uint64_t)gas_costs[PRDOP_SERIALIZE_DYNAMIC] * consumed);
			if (consumed == 0)
				return false;
			buffer += consumed;
			bufferSize -= consumed;
			mapped_data = buffer;
			return true;
		}
	};

}

#undef EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT
#undef FORWARD_POST_INC_DEC_TO_PRE_INC_DEC

using __prlt_bigint = prlrt::__prlt_bigint;