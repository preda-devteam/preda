#pragma once
#include <vector>
#include <cassert>
#include "common.h"
#include "exceptions.h"
#include "gascost.h"

//The reason why there is a wrapper around __float<bitWidth> is that
//engine and compile_env might be compiled by different compiler, thus result in different vtable layout
//We are not supposed to directly overload virtual function from runtime_interface
//Therefore, __float struct will overload functions in this wrapper struct
#define ____FLOAT_ALL_FUNCTION(_BIT_WIDTH)\
static void float_zero(PrecisionFloatInternal<_BIT_WIDTH>& _fStruct){\
	PREDA_CALL(Float_Zero_##_BIT_WIDTH, &_fStruct);\
}\
static void ToString(const PrecisionFloatInternal<_BIT_WIDTH>& _fStruct, char* buf){ \
	PREDA_CALL(ConvertToString_##_BIT_WIDTH, &_fStruct, buf); \
}\
static void ConvertFromString(PrecisionFloatInternal<_BIT_WIDTH>& _fStruct, const char* float_literal){ \
	PREDA_CALL(ConvertFromString_##_BIT_WIDTH, &_fStruct, float_literal); \
}\
static uint32_t GetConvertToStringLen(const PrecisionFloatInternal<_BIT_WIDTH>& _fStruct){ \
	return PREDA_CALL(GetConvertToStringLen_##_BIT_WIDTH, &_fStruct); \
}\
static void float_negate(const PrecisionFloatInternal<_BIT_WIDTH>& a, PrecisionFloatInternal<_BIT_WIDTH>& result){ \
	PREDA_CALL(Float_Negate_##_BIT_WIDTH, &a, &result); \
}\
static void float_add(const PrecisionFloatInternal<_BIT_WIDTH>& a, const PrecisionFloatInternal<_BIT_WIDTH>& b, PrecisionFloatInternal<_BIT_WIDTH>& result){ \
	PREDA_CALL(Float_Add_##_BIT_WIDTH, &a, &b, &result); \
}\
static void float_sub(const PrecisionFloatInternal<_BIT_WIDTH>& a, const PrecisionFloatInternal<_BIT_WIDTH>& b, PrecisionFloatInternal<_BIT_WIDTH>& result){ \
	PREDA_CALL(Float_Sub_##_BIT_WIDTH, &a, &b, &result); \
}\
static void float_mul(const PrecisionFloatInternal<_BIT_WIDTH>& a, const  PrecisionFloatInternal<_BIT_WIDTH>& b, PrecisionFloatInternal<_BIT_WIDTH>& result){ \
	PREDA_CALL(Float_Mul_##_BIT_WIDTH, &a, &b, &result); \
}\
static void float_div(const PrecisionFloatInternal<_BIT_WIDTH>& a, const  PrecisionFloatInternal<_BIT_WIDTH>& b, PrecisionFloatInternal<_BIT_WIDTH>& result){ \
	PREDA_CALL(Float_Div_##_BIT_WIDTH, &a, &b, &result); \
}\
static int float_compare(const PrecisionFloatInternal<_BIT_WIDTH>& a, const PrecisionFloatInternal<_BIT_WIDTH>& b){ \
	return 	PREDA_CALL(Float_Compare_##_BIT_WIDTH, &a, &b); \
}\
static int float_isZero(const PrecisionFloatInternal<_BIT_WIDTH>& a){ \
	return 	PREDA_CALL(Float_IsZero_##_BIT_WIDTH, &a); \
}

#define EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(oper)\
void operator oper##=(const this_type &rhs)\
{\
	*this = *this oper rhs;\
}
namespace prlrt {
struct ____floatType{
	____FLOAT_ALL_FUNCTION(256);
	____FLOAT_ALL_FUNCTION(512);
	____FLOAT_ALL_FUNCTION(1024);
};


template <uint32_t bitWidth> constexpr type_identifier_enum ____get_type_identifier_enum_of_float_type();
template <> constexpr type_identifier_enum ____get_type_identifier_enum_of_float_type<256>() { return type_identifier_enum::___float256; }
template <> constexpr type_identifier_enum ____get_type_identifier_enum_of_float_type<512>() { return type_identifier_enum::___float512; }
template <> constexpr type_identifier_enum ____get_type_identifier_enum_of_float_type<1024>() { return type_identifier_enum::___float1024; }
template<uint32_t bitWidth>
struct ____float{
    using this_type = ____float<bitWidth>;
    using is_value_type = std::true_type;
    using is_fixed_size = std::true_type;
    using internal_type = prlrt::PrecisionFloatInternal<bitWidth>;
    using fixed_size_in_bytes = std::integral_constant<serialize_size_type, serialize_size_type(sizeof(internal_type))>;
	using type_identifier_type = simple_type_type_identifier<____get_type_identifier_enum_of_float_type<bitWidth>()>;
	constexpr static uint32_t gas_coefficient = bitWidth / 256;
	static constexpr uint32_t get_type_identifier_size()
	{
		return type_identifier_type::value.length();
	}
	static constexpr const uint8_t* get_type_identifier_buffer()
	{
		return type_identifier_type::value.data;
	}
	internal_type _fStruct;
	____float(){
		____floatType::float_zero(_fStruct);
	}
	____float(const char* float_literal){
		burn_gas((uint64_t)gas_costs[PRDOP_FLOAT_ASSIGN] * gas_coefficient);
		____floatType::ConvertFromString(_fStruct, float_literal);
	}
	____float(internal_type x){
		_fStruct = x;
	}
	void operator=(const this_type &rhs)
	{
		burn_gas((uint64_t)gas_costs[PRDOP_FLOAT_ASSIGN] * gas_coefficient);
		_fStruct = rhs._fStruct;
	}
	this_type operator-() const{
		burn_gas((uint64_t)gas_costs[PRDOP_FLOAT_OP_SELF] * gas_coefficient);
		internal_type result;
		____floatType::float_negate(_fStruct, result);
		this_type out(result);
		return out;
	}
	this_type operator+(const this_type &rhs) const{
		burn_gas((uint64_t)gas_costs[PRDOP_FLOAT_OP_SIMPLE] * gas_coefficient);
		internal_type result;
		____floatType::float_add(_fStruct, rhs._fStruct, result);
		this_type out(result);
		return out;
	}
	this_type operator-(const this_type &rhs) const{
		burn_gas((uint64_t)gas_costs[PRDOP_FLOAT_OP_SIMPLE] * gas_coefficient);
		internal_type result;
		____floatType::float_sub(_fStruct, rhs._fStruct, result);
		this_type out(result);
		return out;
	}
	this_type operator*(const this_type &rhs) const{
		burn_gas((uint64_t)gas_costs[PRDOP_FLOAT_OP_COMPLEX] * gas_coefficient);
		internal_type result;
		____floatType::float_mul(_fStruct, rhs._fStruct, result);
		this_type out(result);
		return out;
	}
	bool isZero() const{
		return ____floatType::float_isZero(_fStruct);
	}
	this_type operator/(const this_type &rhs) const{
		burn_gas((uint64_t)gas_costs[PRDOP_FLOAT_OP_COMPLEX] * gas_coefficient);
		if(rhs.isZero()){
			preda_exception::throw_exception("divide by zero in " + std::string(__FUNCTION__), prlrt::ExceptionType::DividedByZero);
		}
		internal_type result;
		____floatType::float_div(_fStruct, rhs._fStruct, result);
		this_type out(result);
		return out;
	}
	__prlt_bool operator==(const this_type& rhs) const{
		burn_gas((uint64_t)gas_costs[PRDOP_FLOAT_OP_SIMPLE] * gas_coefficient);
		int result = ____floatType::float_compare(_fStruct, rhs._fStruct);
		if(result == 0){
			return __prlt_bool(true);
		}
		return __prlt_bool(false);
	}
	__prlt_bool operator!=(const this_type& rhs) const{
		burn_gas((uint64_t)gas_costs[PRDOP_FLOAT_OP_SIMPLE] * gas_coefficient);
		int result = ____floatType::float_compare(_fStruct, rhs._fStruct);
		if(result != 0){
			return __prlt_bool(true);
		}
		return __prlt_bool(false);
	}
	__prlt_bool operator>=(const this_type& rhs) const{
		burn_gas((uint64_t)gas_costs[PRDOP_FLOAT_OP_SIMPLE] * gas_coefficient);
		int result = ____floatType::float_compare(_fStruct, rhs._fStruct);
		if(result == 0 || result == 1){
			return __prlt_bool(true);
		}
		return __prlt_bool(false);
	}
	__prlt_bool operator<=(const this_type& rhs) const{
		burn_gas((uint64_t)gas_costs[PRDOP_FLOAT_OP_SIMPLE] * gas_coefficient);
		int result = ____floatType::float_compare(_fStruct, rhs._fStruct);
		if(result == 0 || result == -1){
			return __prlt_bool(true);
		}
		return __prlt_bool(false);
	}
	__prlt_bool operator<(const this_type& rhs) const{
		burn_gas((uint64_t)gas_costs[PRDOP_FLOAT_OP_SIMPLE] * gas_coefficient);
		int result = ____floatType::float_compare(_fStruct, rhs._fStruct);
		if(result == -1){
			return __prlt_bool(true);
		}
		return __prlt_bool(false);
	}
	__prlt_bool operator>(const this_type& rhs) const{
		burn_gas((uint64_t)gas_costs[PRDOP_FLOAT_OP_SIMPLE] * gas_coefficient);
		int result = ____floatType::float_compare(_fStruct, rhs._fStruct);
		if(result == 1){
			return __prlt_bool(true);
		}
		return __prlt_bool(false);
	}

	EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(+);
	EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(-);
	EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(*);
	EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT(/);
	std::string ToString() const{
		uint32_t len = ____floatType::GetConvertToStringLen(_fStruct);
		std::vector<char> buf(len + 1, '\0');
		____floatType::ToString(_fStruct, &buf[0]);
		std::string float_str(&buf[0], len);
		return float_str;
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
	bool map_from_serialized_data(const uint8_t *&buffer, serialize_size_type &bufferSize, bool bDeep)
	{
		burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_MAP_STATIC] + (uint64_t)gas_costs[PRDOP_SERIALIZE_DYNAMIC] * fixed_size_in_bytes::value);
		if (bufferSize < fixed_size_in_bytes::value)
			return false;
		_fStruct = *(internal_type*)buffer;
		buffer += fixed_size_in_bytes::value;
		bufferSize -= fixed_size_in_bytes::value;
		return true;
	}

};
}

#undef ____FLOAT_ALL_FUNCTION
#undef EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT
using __prlt_float256 = prlrt::____float<256>;
using __prlt_float512 = prlrt::____float<512>;
using __prlt_float1024 = prlrt::____float<1024>;