#pragma once
#include "../abi/vm_types.h"


namespace rvm
{

struct uint24_t
{
	static const uint32_t Max = 0xffffff;

	uint16_t	Low;
	uint8_t		High;

	operator 	uint32_t() const { return Max&*(uint32_t*)this; }
	operator 	uint32_t(){ return Max&*(uint32_t*)this; }

	uint32_t	operator = (uint32_t x){ ASSERT(x<=Max); Low = (uint16_t)x; High = *(((const uint8_t*)&x)+2); return x; }
	void		operator += (uint32_t x){ *this = *this + x; }

	TYPETRAITS_DECLARE_POD;
};

struct uint48_t
{
	static const uint64_t Max = 0xffffffffffffULL;

	uint32_t	Low;
	uint16_t	High;

	operator 	uint64_t() const { return Max&*(uint64_t*)this; }

	uint64_t	operator = (uint64_t x){ ASSERT(x<=Max); Low = (uint32_t)x; High = *(((const uint16_t*)&x)+2); return x; }
	void		operator += (uint64_t x){ *this = *this + x; }
	bool		operator < (const uint48_t& x) const { return High < x.High || (High == x.High && Low < x.Low); }
	bool		operator >= (const uint48_t& x) const { return High > x.High || (High == x.High && Low >= x.Low); }
	int			compare_with(const uint48_t& x) const 
				{	int c = (int)High - (int)x.High;
					if(c)return c;
					if(Low < x.Low)return -1;
					if(Low > x.Low)return 1;
					return 0;
				}

	TYPETRAITS_DECLARE_POD;
};

} // namespace rvm
