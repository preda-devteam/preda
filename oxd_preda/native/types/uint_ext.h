#pragma once
#include "../abi/vm_types.h"


namespace rvm
{
#pragma pack(push, 1)

namespace _details
{

template<typename T_Low, typename T_High, typename T_Val, T_Val V_Max>
struct uint_ext
{
	static const T_Val Max = V_Max;
	T_Low		Low;
	T_High		High;

	uint_ext() = default;
	uint_ext(T_Val x){ *this = x; }
	uint_ext(const uint_ext&) = default;
	uint_ext(uint_ext&&) = default;

	operator 	T_Val() const { return Max&*(T_Val*)this; }

	T_Val		operator = (T_Val x){ ASSERT(x<=Max); rt::Copy<sizeof(uint_ext)>(this, &x); return x; }
	uint_ext&	operator = (const uint_ext& x) = default;
	void		operator += (T_Val x){ *this = *this + x; }

	void		Jsonify(rt::Json& append) const { append.Number((T_Val)*this); }
	bool		JsonParse(const rt::String_Ref& str){ T_Val l; if(str.ToNumber(l) && l<=Max){ *this = l; return true; }else return false; }
	static void	GetTypeSignature(rt::String& n){ n += rt::SS("uint") + (sizeof(uint_ext)*8); }
	TYPETRAITS_DECLARE_POD;
};

} // namespace _details

typedef _details::uint_ext<uint16_t, uint8_t, uint32_t, 0xffffffU> uint24_t;
typedef _details::uint_ext<uint32_t, uint16_t, uint64_t, 0xffffffffffffULL> uint48_t;

#pragma pack(pop)
} // namespace rvm
