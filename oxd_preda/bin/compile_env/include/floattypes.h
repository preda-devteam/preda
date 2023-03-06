#pragma once
#include <vector>
#include <cassert>
#include "common.h"
#include "exceptions.h"

//The reason why there is a wrapper around __float<bitWidth> is that
//engine and compile_env might be compiled by different compiler, thus result in different vtable layout
//We are not supposed to directly overload virtual function from runtime_interface
//Therefore, __float struct will overload functions in this wrapper struct
#define FLOATTEMP(_BIT_WIDTH) PrecisionFloatTemp<_BIT_WIDTH>
#define ____FLOAT_ALL_FUNCTION(_BIT_WIDTH)\
static void float_zero(FLOATTEMP(_BIT_WIDTH)& _fStruct){\
	PREDA_CALL(Float_Zero_##_BIT_WIDTH, &_fStruct);\
}\
static void ToString(const FLOATTEMP(_BIT_WIDTH)& _fStruct, char* buf){ \
	PREDA_CALL(ConvertToString_##_BIT_WIDTH, &_fStruct, buf); \
}\
static void ConvertFromString(FLOATTEMP(_BIT_WIDTH)& _fStruct, const char* float_literal){ \
	PREDA_CALL(ConvertFromString_##_BIT_WIDTH, &_fStruct, float_literal); \
}\
static uint32_t GetConvertToStringLen(const FLOATTEMP(_BIT_WIDTH)& _fStruct){ \
	return PREDA_CALL(GetConvertToStringLen_##_BIT_WIDTH, &_fStruct); \
}\
static void float_negate(const FLOATTEMP(_BIT_WIDTH)& a, FLOATTEMP(_BIT_WIDTH)& result){ \
	PREDA_CALL(Float_Negate_##_BIT_WIDTH, &a, &result); \
}\
static void float_add(const FLOATTEMP(_BIT_WIDTH)& a, const FLOATTEMP(_BIT_WIDTH)& b, FLOATTEMP(_BIT_WIDTH)& result){ \
	PREDA_CALL(Float_Add_##_BIT_WIDTH, &a, &b, &result); \
}\
static void float_sub(const FLOATTEMP(_BIT_WIDTH)& a, const FLOATTEMP(_BIT_WIDTH)& b, FLOATTEMP(_BIT_WIDTH)& result){ \
	PREDA_CALL(Float_Sub_##_BIT_WIDTH, &a, &b, &result); \
}\
static void float_mul(const FLOATTEMP(_BIT_WIDTH)& a, const  FLOATTEMP(_BIT_WIDTH)& b, FLOATTEMP(_BIT_WIDTH)& result){ \
	PREDA_CALL(Float_Mul_##_BIT_WIDTH, &a, &b, &result); \
}\
static void float_div(const FLOATTEMP(_BIT_WIDTH)& a, const  FLOATTEMP(_BIT_WIDTH)& b, FLOATTEMP(_BIT_WIDTH)& result){ \
	PREDA_CALL(Float_Div_##_BIT_WIDTH, &a, &b, &result); \
}\
static int float_compare(const FLOATTEMP(_BIT_WIDTH)& a, const FLOATTEMP(_BIT_WIDTH)& b){ \
	return 	PREDA_CALL(Float_Compare_##_BIT_WIDTH, &a, &b); \
}\
static int float_isZero(const FLOATTEMP(_BIT_WIDTH)& a){ \
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
    using internal_type = prlrt::PrecisionFloatTemp<bitWidth>;
    using fixed_size_in_bytes = std::integral_constant<serialize_size_type, serialize_size_type(sizeof(internal_type))>;
	using type_identifier_type = simple_type_type_identifier<____get_type_identifier_enum_of_float_type<bitWidth>()>;
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
		____floatType::ConvertFromString(_fStruct, float_literal);
	}
	____float(internal_type x){
		_fStruct = x;
	}
	void operator=(const this_type &rhs)
	{
		_fStruct = rhs._fStruct;
	}
	this_type operator-() const{
		internal_type result;
		____floatType::float_negate(_fStruct, result);
		this_type out(result);
		return out;
	}
	this_type operator+(const this_type &rhs) const{
		internal_type result;
		____floatType::float_add(_fStruct, rhs._fStruct, result);
		this_type out(result);
		return out;
	}
	this_type operator-(const this_type &rhs) const{
		internal_type result;
		____floatType::float_sub(_fStruct, rhs._fStruct, result);
		this_type out(result);
		return out;
	}
	this_type operator*(const this_type &rhs) const{
		internal_type result;
		____floatType::float_mul(_fStruct, rhs._fStruct, result);
		this_type out(result);
		return out;
	}
	bool isZero() const{
		return ____floatType::float_isZero(_fStruct);
	}
	this_type operator/(const this_type &rhs) const{
		if(rhs.isZero()){
			throw preda_exception("divide by zero in " + std::string(__FUNCTION__), prlrt::ExceptionType::DividedByZero);
		}
		internal_type result;
		____floatType::float_div(_fStruct, rhs._fStruct, result);
		this_type out(result);
		return out;
	}
	__prlt_bool operator==(const this_type& rhs) const{
		int result = ____floatType::float_compare(_fStruct, rhs._fStruct);
		if(result == 0){
			return __prlt_bool(true);
		}
		return __prlt_bool(false);
	}
	__prlt_bool operator!=(const this_type& rhs) const{
		int result = ____floatType::float_compare(_fStruct, rhs._fStruct);
		if(result != 0){
			return __prlt_bool(true);
		}
		return __prlt_bool(false);
	}
	__prlt_bool operator>=(const this_type& rhs) const{
		int result = ____floatType::float_compare(_fStruct, rhs._fStruct);
		if(result == 0 || result == 1){
			return __prlt_bool(true);
		}
		return __prlt_bool(false);
	}
	__prlt_bool operator<=(const this_type& rhs) const{
		int result = ____floatType::float_compare(_fStruct, rhs._fStruct);
		if(result == 0 || result == -1){
			return __prlt_bool(true);
		}
		return __prlt_bool(false);
	}
	__prlt_bool operator<(const this_type& rhs) const{
		int result = ____floatType::float_compare(_fStruct, rhs._fStruct);
		if(result == -1){
			return __prlt_bool(true);
		}
		return __prlt_bool(false);
	}
	__prlt_bool operator>(const this_type& rhs) const{
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
#undef FLOATTEMP
#undef ____FLOAT_ALL_FUNCTION
#undef EXTEND_OPERATOR_TO_COMPOUND_ASSIGNMENT
using __prlt_float256 = prlrt::____float<256>;
using __prlt_float512 = prlrt::____float<512>;
using __prlt_float1024 = prlrt::____float<1024>;