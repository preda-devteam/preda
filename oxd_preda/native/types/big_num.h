#pragma once
#include "type_def.h"
#include "../../../SFC/core/ext/bignum/big_num.h"


namespace rvm
{

using BN_BLK = ext::_details::BN_BLK;

using BigNumRough = ext::BigNumRough;
using BigNumRef = ext::BigNumRef;
using BigNumMutable = ext::BigNumMutable;

#pragma pack(push, 1)
struct BigNum: public ext::BigNumImmutable<ext::_details::BN_Fix<>>
{
	RVM_IMMUTABLE_TYPE(BigNum)
	BigNum(decltype(0) x){ ASSERT(x == 0); }
	BigNum(int64_t x){ _Sign_Len = sizeof(uint64_t)/sizeof(BN_BLK); (*(uint64_t*)_Data) = abs(x); SetSign(x<0); }
	BigNum(uint64_t x){ _Sign_Len = sizeof(uint64_t)/sizeof(BN_BLK); (*(uint64_t*)_Data) = x; }
	uint32_t GetEmbeddedSize() const { ASSERT(GetLength() <= 0x7f); return sizeof(BN_BLK)*GetLength() + 1; }
	uint32_t Embed(const BigNumRef& bn)
	{
		ASSERT(bn.GetLength() <= 0x7f);
		_Sign_Len = bn.GetLength();
		SetSign(bn.GetSign());
		uint32_t ret;
		memcpy(_Data, bn.Data(), ret = sizeof(BN_BLK)*bn.GetLength());
		return ret + 1;
	}
	uint32_t		GetBlockCount() const { return BigNumImmutable<ext::_details::BN_Fix<>>::GetLength(); }
private:
	uint32_t		GetLength() const { return GetBlockCount(); }
public:
	static uint32_t	GetEmbeddedSize(const BigNumRef& bn){ ASSERT(bn.GetLength() <= 0x7f); return (uint32_t)(1 + sizeof(BN_BLK)*bn.Len); }
	static bool		IsEmbeddable(const BigNumRef& bn){ return bn.GetLength() <= 0x7f; }
	static void		GetTypeSignature(rt::String& name){ name += rt::SS("bigint"); }
	TYPETRAITS_DECLARE_NON_POD;

	static const BigNum&	Zero(){ static const BigNum _zero(0); return _zero; }
	static const uint32_t	MAX_EMBEDDED_SIZE = 0x7f*sizeof(BN_BLK) + 1;
};
#pragma pack(pop)


struct BigNumString: public rt::String
{
	BigNumString(const BigNum& x, UINT base = 10)
	{
		x.ToString(*this, base);
	}
	BigNumString(const BigNumMutable& x, UINT base = 10)
	{
		x.ToString(*this, base);
	}
	BigNumString(const BigNumRough& x, UINT base = 10)
	{
		BigNumMutable a = x;
		a.ToString(*this, base);
	}
};

typedef BigNumMutable	_BN;

} // namespace rvm
