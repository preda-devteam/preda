#include "big_num.h"
#include "../../os/kernel.h"
#include "ttmath/ttmathuint.h"


#ifdef PLATFORM_MAC
#include <immintrin.h>
#endif

namespace ext
{

ULONGLONG BigNumRough::operator = (ULONGLONG n)
{
	int a = 0;
	if(n != 0)
		a = (int)log2(n);
	if(a>MANTISSA_BITS)
	{
		Exponent = a - MANTISSA_BITS;
		Mantissa = (UINT)(n>>(a-32));
	}
	else
	{
		Exponent = 0;
		Mantissa = (UINT)n;
	}

	return n;
}

bool BigNumRough::operator < (const BigNumRough&x) const
{
	if(Exponent + MANTISSA_BITS < x.Exponent)return true;
	if(Exponent > MANTISSA_BITS + x.Exponent)return false;
	if(Exponent <= x.Exponent)
	{	return (Mantissa >> (x.Exponent - Exponent)) < x.Mantissa;
	}
	else
	{	return (Mantissa < (x.Mantissa << (Exponent - x.Exponent)));
	}
}

bool BigNumRough::operator > (const BigNumRough&x) const
{
	if(Exponent + MANTISSA_BITS < x.Exponent)return false;
	if(Exponent > MANTISSA_BITS + x.Exponent)return true;
	if(Exponent <= x.Exponent)
	{	return (Mantissa >> (x.Exponent - Exponent)) > x.Mantissa;
	}
	else
	{	return (Mantissa > (x.Mantissa << (Exponent - x.Exponent)));
	}
}

bool BigNumRough::operator <= (const BigNumRough&x) const
{
	if(Exponent <= x.Exponent)
	{	return (Mantissa >> (x.Exponent - Exponent)) <= x.Mantissa;
	}
	else
	{	return (Mantissa <= (x.Mantissa << (Exponent - x.Exponent)));
	}
}

bool BigNumRough::operator >= (const BigNumRough&x) const
{
	if(Exponent <= x.Exponent)
	{	return (Mantissa >> (x.Exponent - Exponent)) > x.Mantissa;
	}
	else
	{	return (Mantissa > (x.Mantissa << (Exponent - x.Exponent)));
	}
}

bool BigNumRough::operator == (const BigNumRough&x) const
{
	if(Exponent <= x.Exponent)
	{	return (Mantissa >> (x.Exponent - Exponent)) == x.Mantissa;
	}
	else
	{	return (Mantissa == (x.Mantissa << (Exponent - x.Exponent)));
	}
}

#define SIGNS_A_B(a,b)	((((int)a.GetSign())<<1) + (int)b.GetSign())
#define SIGNS_POS_POS	0
#define SIGNS_POS_NEG	1
#define SIGNS_NEG_POS	2
#define SIGNS_NEG_NEG	3

namespace _details
{

// no considering on sign
// assert no carry
void BN_LeftShift64(BN_Dyn& b, UINT s)
{
	if(0 == s || b.GetLength() == 0)
		return;

	ASSERT(s < 64);
	ASSERT(0 == ((~0ULL << (64 - s)) & b._Data[b.GetLength() - 1]));

	UINT i = b.GetLength() - 1;
	for(; 0 < i; i--) {
		b._Data[i] = (b._Data[i] << s) | (b._Data[i - 1] >> (64 - s));
	}
	b._Data[i] <<= s;
}

// no considering on sign
void BN_RightShift64(BN_Dyn& b, UINT s)
{
	if(0 == s || b.GetLength() == 0)
		return;

	ASSERT(s < 64);
	UINT i = 0;
	for(; i < b.GetLength() - 1; i++) {
		b._Data[i] = (b._Data[i] >> s) | (b._Data[i + 1] << (64 - s));
	}
	b._Data[i] >>= s;
}


bool BN_AbsLess(const BN_Unsigned& a, const BN_Unsigned& b) // a < b
{
	if(a.Data() == b.Data())return false;

	ASSERT(a.IsLeadingZeroTrimmed());
	ASSERT(b.IsLeadingZeroTrimmed());

	if(a.Len < b.Len)return true;
	if(a.Len == b.Len)
	{
		for(int i=a.Len - 1; i>=0; i--)
		{	
			if(a.pData[i] < b.pData[i])return true;
			if(a.pData[i] > b.pData[i])return false;
		}
	}

	return false;
}

bool BN_AbsLessOrEqual(const BN_Unsigned& a, const BN_Unsigned& b) // a < b
{
	if(a.Data() == b.Data())return true;

	ASSERT(a.IsLeadingZeroTrimmed());
	ASSERT(b.IsLeadingZeroTrimmed());

	if(a.Len < b.Len)return true;
	if(a.Len == b.Len)
	{
		for(int i=a.Len - 1; i>=0; i--)
		{	
			if(a.pData[i] < b.pData[i])return true;
			if(a.pData[i] > b.pData[i])return false;
		}

		return true;
	}

	return false;
}

bool BN_AbsEqual(const BN_Unsigned& a, const BN_Unsigned& b) // a == b
{
	if(a.Data() == b.Data())return true;

	ASSERT(a.IsLeadingZeroTrimmed());
	ASSERT(b.IsLeadingZeroTrimmed());

	if(a.Len != b.Len)return false;
	for(UINT i=0; i<a.Len; i++)
		if(a.pData[i] != b.pData[i])return false;

	return true;
}

bool BN_IsZero(const BigNumRef& a)
{
	if(a.Len == 0)return true;
	for(UINT i=0; i<a.Len; i++)
		if(a.pData[i])return false;
	return true;
}

int  BN_AbsCompare(const BN_Unsigned& a, const BN_Unsigned& b) // a < b: -1, a == b:0, a > b:1
{
	if(a.Data() == b.Data())return 0;

	ASSERT(a.IsLeadingZeroTrimmed());
	ASSERT(b.IsLeadingZeroTrimmed());

	if(a.Len > b.Len)return 1;
	if(a.Len < b.Len)return -1;

	for(int i=a.Len - 1; i>=0; i--)
	{	
		if(a.pData[i] < b.pData[i])return -1;
		if(a.pData[i] > b.pData[i])return 1;
	}

	return 0;
}

bool BN_Less(const BigNumRef& a, const BigNumRef& b) // a < b
{
	if(&a == &b)return false;

	ASSERT(a.IsLeadingZeroTrimmed());
	ASSERT(b.IsLeadingZeroTrimmed());

	switch(SIGNS_A_B(a,b))
	{
	case SIGNS_POS_POS: return BN_AbsLess(a, b);
	case SIGNS_POS_NEG: return false;
	case SIGNS_NEG_POS: return !BN_IsZero(a) || !BN_IsZero(b);
	case SIGNS_NEG_NEG: return BN_AbsLessOrEqual(b, a);
	}

	return false;
}

bool BN_Equal(const BigNumRef& a, const BigNumRef& b) // a == b
{
	if(&a == &b)return true;

	ASSERT(a.IsLeadingZeroTrimmed());
	ASSERT(b.IsLeadingZeroTrimmed());

	if(!BN_AbsEqual(a,b))return false;
	return a.GetSign() == b.GetSign() || BN_IsZero(a);
}

bool BN_LessOrEqual(const BigNumRef& a, const BigNumRef& b) // a <= b
{
	if(&a == &b)return true;

	ASSERT(a.IsLeadingZeroTrimmed());
	ASSERT(b.IsLeadingZeroTrimmed());

	switch(SIGNS_A_B(a,b))
	{
	case SIGNS_POS_POS: return BN_AbsLessOrEqual(a, b);
	case SIGNS_POS_NEG: return BN_IsZero(a) && BN_IsZero(b);
	case SIGNS_NEG_POS: return true;
	case SIGNS_NEG_NEG: return BN_AbsLess(b, a);
	}

	return false;
}

int BN_Compare(const BigNumRef& a, const BigNumRef& b) // a < b: -1, a == b:0, a > b:1
{
	if(&a == &b)return 0;

	ASSERT(a.IsLeadingZeroTrimmed());
	ASSERT(b.IsLeadingZeroTrimmed());

	if(a.GetLength() == 0 && b.GetLength() == 0)return 0;

	switch(SIGNS_A_B(a,b))
	{
	case SIGNS_POS_POS: return BN_AbsCompare(a, b);
	case SIGNS_POS_NEG: return (BN_IsZero(a) && BN_IsZero(b))?0:1;
	case SIGNS_NEG_POS: return (BN_IsZero(a) && BN_IsZero(b))?0:-1;
	case SIGNS_NEG_NEG: return BN_AbsCompare(b, a);
	}

	return 0;
}

template<bool Inplace>
bool BN_Increase(const BN_Unsigned& b, const BN_Unsigned& ret) // return carry
{
	ASSERT(b.Len == ret.Len);
	if(b.Len == 0)return true;

	UINT i=0;
	for(; i<b.Len; i++)
		if(b.pData[i] != 0xffffffffffffffffULL)
		{	ret.pData[i] = b.pData[i] + 1;
			if(!Inplace)
			{	i++;
				memcpy(ret.pData + i, b.pData + i, (b.Len - i)*BN_BLK_SIZE);
			}
			return false;
		}
		else
		{	ret.pData[i] = 0;
		}
	
	return true;
}

template<bool Inplace>
bool BN_Decrease(const BN_Unsigned& b, const BN_Unsigned& ret) // return borrow
{
	ASSERT(b.Len == ret.Len);
	if(b.Len == 0)return true;

	UINT i=0;
	for(; i<b.Len; i++)
		if(b.pData[i])
		{	ret.pData[i] = b.pData[i] - 1;
			if(!Inplace)
			{	i++;
				memcpy(ret.pData + i, b.pData + i, (b.Len - i)*BN_BLK_SIZE);
			}
			return false;
		}
		else
		{	ret.pData[i] = ~(BN_BLK)0;
		}
	
	return true;
}

void BN_Dyn::TrimLeadingZero()
{
	UINT len = (UINT)_Data.GetSize();
	while(len && _Data[len-1] == 0)
		len--;

	_Data.ShrinkSize(len);
}

void BN_Dyn::LeftShift(UINT a)
{
	if(GetLength() == 0)return;
	ASSERT(_Data.Last());

	int s = a%BN_BLK_BITSIZE;
	int Exponent = a/BN_BLK_BITSIZE;

	if(s)
	{
		_Data.push_both(0, Exponent, (_Data.Last() & (~(0ULL)<<(BN_BLK_BITSIZE - s)))?1:0);
		BN_LeftShift64(*this, s);
		TrimLeadingZero();
	}
	else
	{
		if(Exponent)
			_Data.push_front(0, Exponent);
	}
}

void BN_Dyn::RightShift(UINT a)
{
	if(GetLength() == 0)return;
	ASSERT(_Data.Last());

	int s = a%BN_BLK_BITSIZE;
	UINT Exponent = a/BN_BLK_BITSIZE;

	if(Exponent)
		_Data.erase(0, std::min(SIZE_T(Exponent), _Data.GetSize()));

	if(s)
	{
		BN_RightShift64(*this, s);
		TrimLeadingZero();
	}
}

void BN_ToString(const BigNumRef& a, rt::String& append, int base)
{
	if(base == 16)
	{
		if(a.GetLength())
		{
			UINT org_len = (UINT)append.GetLength();

			rt::tos::Base16 x(a.pData, a.Len*BN_BLK_SIZE);

			UINT co = (UINT)x.GetLength()/2;
			WORD* s = (WORD*)(x.End()-2);
			while(co && *s == 0x3030)
			{
				co--;
				s--;
			}

			WORD* p;
			if(a.GetSign())
			{
				append.SetLength(3 + co*2 + org_len);
				*(DWORD*)(append.Begin() + org_len) = 0x78302d;
				p = (WORD*)(append.Begin()+3 + org_len);
			}
			else
			{	
				append.SetLength(2 + co*2 + org_len);
				*(WORD*)(append.Begin() + org_len) = 0x7830;
				p = (WORD*)(append.Begin()+2 + org_len);
			}
		
			for(UINT i=0; i<co; i++, p++, s--)
				*p = *s;
		}
		else
		{
			append += rt::SS("0x00");
		}
	}
	else
	{	
		ASSERT(base == 10);

		if(a.GetLength())
		{
			ext::BigNumMutable w, b;
			if(a.GetSign())append += '-';

			UINT org_len = (UINT)append.GetLength();

			UINT r = 0;
			BN_Div(a, 10U, &r, w);

			append += (char)('0' + r);
			while(w.GetLength())
			{
				b.Div(w, 10U, &r);
				append += (char)('0' + r);
				rt::Swap(w, b);
			}

			append.TrimLeft(org_len).Flip();
		}
		else
		{
			append += rt::SS("0");
		}
	}
}

void BN_AbsAdd(const BN_Unsigned& a, const BN_Unsigned& b, ext::BigNumMutable& ret)
{
	if(a.Len < b.Len)
		rt::Swap(a, b);

	ret.SetLength(a.Len);

	BYTE carry = 0;
	UINT i=0;
	for(; i<b.Len; i++)
		carry = rt::AddCarry(carry, a.pData[i], b.pData[i], &ret._Data[i]);

	if(carry)
	{
		carry = BN_Increase<false>(a.SubVal(b.Len), ret.SubVal(b.Len, a.Len - b.Len));
		if(carry)ret.AppendLast() = 1;
	}
	else
	{
		memcpy(&ret._Data[b.Len], &a.pData[b.Len], (a.Len - b.Len)*BN_BLK_SIZE);
		ret.TrimLeadingZero();
	}
}

void BN_AbsAdd(const BN_Unsigned& b, ext::BigNumMutable& ret)
{
	ret.ExtendLength(b.Len);

	BN_BLK* p = ret._Data;

	BYTE carry = 0;
	UINT i=0;
	for(; i<b.Len; i++)
		carry = rt::AddCarry(carry, p[i], b.pData[i], p + i);

	if(carry)
	{
		carry = BN_Increase<true>(ret.SubVal(b.Len, ret.GetLength() - b.Len), ret.SubVal(b.Len, ret.GetLength() - b.Len));
		if(carry)ret.AppendLast() = 1;
	}

	ret.TrimLeadingZero();
}

void BN_AbsSub(const BN_Unsigned& a, const BN_Unsigned& b, ext::BigNumMutable& ret)
{
	ASSERT(BN_AbsLessOrEqual(b, a));
	ret.SetLength(a.Len);

	BN_BLK* p = ret._Data;

	BYTE borrow = 0;
	UINT i=0;
	for(; i<b.Len; i++)
		borrow = rt::SubBorrow(borrow, a.pData[i], b.pData[i], p + i);

	if(borrow)
	{
		VERIFY(0 == BN_Decrease<false>(a.SubVal(b.Len), ret.SubVal(b.Len)));
	}
	else
	{
		memcpy(&ret._Data[b.Len], &a.pData[b.Len], (a.Len - b.Len)*BN_BLK_SIZE);
	}

	ret.TrimLeadingZero();
}

void BN_AbsSub(const BN_Unsigned& b, ext::BigNumMutable& ret)
{
	if(BN_AbsLessOrEqual(b, ret))
	{
		BN_BLK* p = ret._Data;

		BYTE borrow = 0;
		UINT i=0;
		for(; i<b.Len; i++)
			borrow = rt::SubBorrow(borrow, p[i], b.pData[i], p + i);

		if(borrow)
		{
			VERIFY(0 == BN_Decrease<true>(ret.SubVal(b.Len, ret.GetLength() - b.Len), ret.SubVal(b.Len, ret.GetLength() - b.Len)));
		}
	}
	else
	{	
		ret.ExtendLength(b.Len);
		BN_BLK* p = ret._Data;

		BYTE borrow = 0;
		UINT i=0;
		for(; i<b.Len; i++)
			borrow = rt::SubBorrow(borrow, b.pData[i], p[i], p + i);

		ASSERT(borrow == 0);
	}

	ret.TrimLeadingZero();
}

void BN_Add(const BigNumRef& b, ext::BigNumMutable& ret) // ret += b
{
	switch(SIGNS_A_B(ret,b))
	{	
	case SIGNS_POS_POS:	
		BN_AbsAdd(b, ret);
		ret.SetSign(false);
		break;
	case SIGNS_POS_NEG: BN_Sub(b.Abs(), ret); break;
	case SIGNS_NEG_POS: BN_Sub(BigNumRef(true, b.pData, b.Len), ret); break;
		break;
	case SIGNS_NEG_NEG: 
		BN_AbsAdd(b, ret);
		ret.SetSign(true);
		break;
	}
}

void BN_Sub(const BigNumRef& b, ext::BigNumMutable& ret) // ret -= b
{
	switch(SIGNS_A_B(ret,b))
	{	
	case SIGNS_POS_POS:	
		{
			bool sign = BN_AbsLess(ret, b);
			BN_AbsSub(b, ret);
			ret.SetSign(sign);
		}
		break;
	case SIGNS_POS_NEG:
		BN_AbsAdd(b, ret);
		ret.SetSign(false);
		break;
	case SIGNS_NEG_POS:
		BN_AbsAdd(b, ret);
		ret.SetSign(true); break;
		break;
	case SIGNS_NEG_NEG:
		{	
			bool sign = !BN_AbsLess(ret, b);
			BN_AbsSub(b, ret);
			ret.SetSign(sign);
		}
		break;
	}
}

void BN_Add(const BigNumRef& a, const BigNumRef& b, ext::BigNumMutable& ret) // ret = a + b
{
	switch(SIGNS_A_B(a,b))
	{	
	case SIGNS_POS_POS:	
		BN_AbsAdd(a, b, ret);
		ret.SetSign(false);
		break;
	case SIGNS_POS_NEG: BN_Sub(a, b.Abs(), ret); break;
	case SIGNS_NEG_POS: BN_Sub(b, a.Abs(), ret); break;
	case SIGNS_NEG_NEG: 
		BN_AbsAdd(b, a, ret);
		ret.SetSign(true);
		break;
	}
}

void BN_Sub(const BigNumRef& a, const BigNumRef& b, ext::BigNumMutable& ret) // ret = a - b
{
	switch(SIGNS_A_B(a,b))
	{	
	case SIGNS_POS_POS:	
		if(BN_Less(a, b))
		{	ret.SetSign(true);
			BN_AbsSub(b, a, ret);
		}
		else
		{	ret.SetSign(false);
			BN_AbsSub(a, b, ret);
		}
		break;
	case SIGNS_POS_NEG:
		ret.SetSign(false);
		BN_AbsAdd(a, b, ret);
		break;
	case SIGNS_NEG_POS:
		ret.SetSign(true);
		BN_AbsAdd(a, b, ret);
		break;
	case SIGNS_NEG_NEG:	
		if(BN_AbsLess(a, b))
		{	
			ret.SetSign(false);
			BN_AbsSub(b, a, ret);
		}
		else
		{	ret.SetSign(true);
			BN_AbsSub(a, b, ret);
		}
		break;
	}
}

UINT BN_Mantissa32(const BN_Unsigned& b, int* exp)
{
	if(b.GetLength() == 0)
	{
		*exp = 0;
		return 0;
	}

	auto* p = (const UINT*)b.Data();
	int  len = (int)b.GetLength()*sizeof(BN_BLK)/sizeof(UINT);
	if(sizeof(BN_BLK) == 8 && p[len-1] == 0)len--;

	int lb = rt::LeadingZeroBits(p[len-1]);
	UINT ret = p[len-1]<<lb;
	if(len>1)ret |= p[len-2]>>(32 - lb);

	*exp = (len-1)*32 - lb;
	return ret;
}

ULONGLONG BN_Mantissa64(const BN_Unsigned& b, int* exp)
{
	if(b.GetLength() == 0)
	{
		*exp = 0;
		return 0;
	}

	auto* p = (const UINT*)b.Data();
	int   len = (int)b.GetLength()*sizeof(BN_BLK)/sizeof(UINT);
	if(sizeof(BN_BLK) == 8 && p[len-1] == 0)len--;

	int lb = rt::LeadingZeroBits(p[len-1]);
	ULONGLONG ret = ((ULONGLONG)p[len-1])<<(lb + 32);
	if(len>1)ret |= ((ULONGLONG)p[len-2])<<lb;
	if(len>2)ret |= ((ULONGLONG)p[len-3])>>(32 - lb);

	*exp = (len-2)*32 - lb;
	return ret;
}

void BN_AbsMul(const BN_Unsigned& a, UINT b_in, ext::BigNumMutable& ret)
{
	if(b_in == 0)
	{	ret.SetZero();
		return;
	}

	ret.SetLength(a.Len + 1);
	ret.FillZero();

	auto* c = (UINT*)ret._Data.Begin();
	auto* pa = (UINT*)a.pData;
	UINT a_len = a.Len*(sizeof(BN_BLK)/sizeof(UINT));

	ULONGLONG b = b_in;

	for(UINT i=0; i<a_len; i++)
	{
		auto* v = (ULONGLONG *)(c + i);
		v[1] += rt::AddCarry(0, *v, pa[i]*b, v);
	}

	ret.TrimLeadingZero();
}

void BN_AbsMul(const BN_Unsigned& a, ULONGLONG b_in, ext::BigNumMutable& ret) // ret = a*b
{
	if(b_in == 0)
	{	ret.SetZero();
		return;
	}

	if(b_in <= 0xffffffffULL)
	{	BN_AbsMul(a, (UINT)b_in, ret);
		return;
	}

	ret.SetLength(a.Len + sizeof(ULONGLONG)/sizeof(UINT));
	ret.FillZero();

	auto* c = (UINT*)ret._Data.Begin();
	auto* pa = (UINT*)a.pData;
	UINT a_len = a.Len*(sizeof(BN_BLK)/sizeof(UINT));

	ULONGLONG b1 = (UINT)b_in;
	ULONGLONG b2 = (UINT)(b_in>>32);

	for(UINT i=0; i<a_len; i++)
	{
		auto* v = (ULONGLONG *)(c + i);
		v[1] += rt::AddCarry(0, *v, pa[i]*b1, v);

		v = (ULONGLONG *)(c + i + 1);
		v[1] += rt::AddCarry(0, *v, pa[i]*b2, v);
	}

	ret.TrimLeadingZero();
}

void BN_AbsMul(UINT b_in, ext::BigNumMutable& ret)
{
	if(b_in == 0)
	{	ret.SetZero();
		return;
	}

	ret.AppendLast() = 0;
	UINT a_len = ret.GetLength()*(sizeof(BN_BLK)/sizeof(UINT));

	auto* c = (UINT*)ret._Data.Begin();

	ULONGLONG b = b_in;
	ULONGLONG carry = 0;
	for(UINT i=0; i<a_len; i++)
	{
		ULONGLONG muli;
		carry = ((ULONGLONG)rt::AddCarry(0, carry, c[i]*b, &muli))<<32;
		carry += (muli >> 32);

		c[i] = (UINT)muli;
	}

	ASSERT(carry == 0);
	ret.TrimLeadingZero();
}

void BN_Mul(const BigNumRef& a, const BigNumRef& b, ext::BigNumMutable& ret)
{
	ret.SetLength(a.Len + b.Len + 1);
	ret.FillZero();

	UINT* c = (UINT*)ret._Data.Begin();
	UINT* pa = (UINT*)a.pData;
	UINT a_len = a.Len*(sizeof(BN_BLK)/sizeof(UINT));

	UINT* pb = (UINT*)b.pData;
	UINT b_len = b.Len*(sizeof(BN_BLK)/sizeof(UINT));

	auto carries = (UINT*)_alloca(sizeof(UINT)*(b_len+a_len+2));
	rt::Zero(carries, sizeof(UINT)*(b_len+a_len+2));

	for(UINT i=0; i<a_len; i++)
	{
		ULONGLONG pa_i = pa[i];
		for(UINT j=0; j<b_len; j++)
		{
			auto* v = (ULONGLONG*)(c + i + j);
			carries[i + j + 2] += rt::AddCarry(0, *v, pa_i*pb[j], v);
		}
	}

	{	int carry = 0;
		for(UINT i=0; i<b_len+a_len+2; i++)
		{
			carry = rt::AddCarry(carry, carries[i], c[i], c + i);
		}
		ASSERT(carry == 0);
	}

	ret.SetSign(a.GetSign() != b.GetSign());
	ret.TrimLeadingZero();
}


void BN_Mul(const BigNumRef& a, const NativeFloat& b, ext::BigNumMutable& ret)
{
	if(b.Mantissa == 0 || a.GetLength()*BN_BLK_BITSIZE + b.Exponent + 32 <= 0)
	{
		ret.SetZero();
		return;
	}

	int lz = rt::LeadingZeroBits(b.Mantissa);
	if(lz >= 32)
	{
		BN_AbsMul(a, (UINT)b.Mantissa, ret);
		ret <<= b.Exponent;
	}
	else
	{
		int shift = 32 - lz;
		BN_AbsMul(a, (UINT)(b.Mantissa>>shift), ret);
		ret <<= (b.Exponent + shift);
	}
	
	ret.SetSign(a.GetSign() != b.Sign);
}

void BN_Mul(const NativeFloat& b, ext::BigNumMutable& ret)
{
	if(b.Mantissa == 0 || ret.GetLength()*BN_BLK_BITSIZE + b.Exponent + 32 <= 0)
	{
		ret.SetZero();
		return;
	}

	int lz = rt::LeadingZeroBits(b.Mantissa);
	if(lz >= 32)
	{
		BN_AbsMul((UINT)b.Mantissa, ret);
		ret <<= b.Exponent;
	}
	else
	{
		int shift = 32 - lz;
		BN_AbsMul((UINT)(b.Mantissa>>shift), ret);
		ret <<= (b.Exponent + shift);
	}
	
	ret.SetSign(ret.GetSign() != b.Sign);
}


bool BN_Div(const BN_Unsigned& a, UINT b_in, UINT* remainder, ext::BigNumMutable& ret) // ret = (a - *remainder)/b
{
	if(b_in == 0)
		return false;

	ret.SetLength(a.Len);

	auto* r = (UINT*)ret.Data();
	auto* s = (const UINT*)a.pData;

	ULONGLONG carried = 0;
	ULONGLONG b = b_in;
	for(int i=a.Len*(sizeof(BN_BLK)/sizeof(UINT))-1; i>=0; i--)
	{
		ULONGLONG v = s[i] | carried;
		r[i] = (UINT)(v/b);
		((UINT*)&carried)[1] = (UINT)(v%b);
	}

	ret.TrimLeadingZero();
	if(remainder)*remainder = ((UINT*)&carried)[1];

	return true;
}

float BN_2_float(const BigNumRef& x)
{
	if(x.GetLength() == 0)return 0;

	int exp;
	UINT m = BN_Mantissa32(x, &exp);
	ASSERT(m);

	DWORD y = (((UINT)x.GetSign())<<31) | (0x007fffff&(m>>8)) | (0x7f800000&((exp + 127 + 32 - 1) << 23));
	return (float&)y;
}

double BN_2_double(const BigNumRef& x)
{
	if(x.GetLength() == 0)return 0;
	
	int exp;
	ULONGLONG m = BN_Mantissa64(x, &exp);
	ASSERT(m);

	ULONGLONG y = (((ULONGLONG)x.GetSign())<<63) | (0xfffffffffffffULL&(m>>11)) | (0x7ff0000000000000ULL&(((ULONGLONG)(exp + 1023 + 64 - 1)) << 52));
	return (double&)y;
}

bool BN_2_rough(const BigNumRef& x, BigNumRough* out)
{
	if(x.GetSign()){ rt::Zero(*out); return false; }

	int exp;
	UINT m = BN_Mantissa32(x, &exp);

	if(exp < 0)
	{
		out->Mantissa = m >> (-exp);
		out->Exponent = 0;
	}
	else
	{
		if(exp > BigNumRough::EXPONENT_LIMIT){ rt::Void(*out); return false; }

		out->Mantissa = m;
		out->Exponent = exp;
	}

	return true;
}

namespace _details{
/*
 original code from ttmathuint.h:2306
 */
namespace ttmath{
class big_ttmath: public ::ttmath::UInt<4>{
public:
	uint64_t Div_Calculate(::ttmath::uint u2, ::ttmath::uint u1, ::ttmath::uint u0, ::ttmath::uint v1, ::ttmath::uint v0){
		::ttmath::UInt<2> u_temp;
		::ttmath::uint rp;
		bool next_test;
		
		ASSERT( v1 != 0 );
		
		u_temp.table[1] = u2;
		u_temp.table[0] = u1;
		u_temp.DivInt(v1, &rp);
		
		ASSERT( u_temp.table[1]==0 || u_temp.table[1]==1 );
		
		do
		{
			bool decrease = false;
			
			if( u_temp.table[1] == 1 )
				decrease = true;
			else
			{
				UInt<2> temp1, temp2;
				
				UInt<2>::MulTwoWords(u_temp.table[0], v0, temp1.table+1, temp1.table);
				temp2.table[1] = rp;
				temp2.table[0] = u0;
				
				if( temp1 > temp2 )
					decrease = true;
			}
			
			next_test = false;
			
			if( decrease )
			{
				u_temp.SubOne();
				rp += v1;
				
				if( rp >= v1 ) // it means that there wasn't a carry (r<b from the book)
					next_test = true;
			}
		}
		while( next_test );
		TTMATH_LOG("UInt::Div3_Calculate")
		return u_temp.table[0];
	}
};
}
/*
 Return Value:
 0: |a| > b or |a| = |b|, proceed to perform division
 1: |a| < |b|, a = 0 or b = 0, edge case, could early out
 
 */
int Div_Standard_test(const ext::BigNumMutable& a_temp, const ext::BigNumMutable& b_temp){
	if((!a_temp.IsZero() && !b_temp.IsZero()) && (a_temp.Abs() > b_temp || a_temp.Abs() == b_temp.Abs())){
		return 0;
	}
	return 1;
}

void Div_DivInt(ext::BigNumMutable& a_temp, uint64_t divisor, uint64_t& remainder){
	a_temp.TrimLeadingZero();
	ext::BigNumMutable dividend = a_temp;
	uint64_t r = 0;
	int i = a_temp.GetLength() - 1;
	for(; i >= 0; i--){
		LPC_BN_BLK current = a_temp._Data + i;
		::ttmath::UInt<2>::DivTwoWords((uint64_t)r, (uint64_t) *(dividend._Data+i), (uint64_t)divisor, (::ttmath::uint*) current , (::ttmath::uint*) &r);
	}
	remainder = r;
	return;
}

BN_BLK Div_Calculate(BN_BLK u2, BN_BLK u1, BN_BLK u0, BN_BLK v1, BN_BLK v0){
	ttmath::big_ttmath bt;
	return bt.Div_Calculate((uint64_t)u2,(uint64_t)u1,(uint64_t)u0,(uint64_t)v1,(uint64_t)v0);
}

uint32_t Div_Find_highest_bit (ext::BigNumMutable& block){
	int bitposition = 0;
	BN_BLK data = block.Last();
	while(data!=0){
		bitposition++;
		data = data >> 1;
	}
	return bitposition - 1;
}
BN_BLK Div_Normalize(ext::BigNumMutable& a, ext::BigNumMutable& b, int& bits_moved){
	uint32_t highest_bits = 0;
	highest_bits = Div_Find_highest_bit(b);
	const int block_size = 64;
	bits_moved = block_size - highest_bits - 1;
	BN_BLK u2 = a.Last();
	if(bits_moved){
		b <<= bits_moved;
		a <<= bits_moved;
		u2 >>= (highest_bits + 1);
	}
	else{
		u2 = 0;
	}
	return u2;
}

void Div_Make_new_U(ext::BigNumMutable& uu, ext::BigNumMutable& u, uint32_t j, uint32_t n, uint64_t u_max){
	if(uu.IsZero()){
		return;
	}
	uint32_t uu_len = uu.GetLength();
	if(uu_len <= n){
		uu.ExtendLength(n - uu_len + 1);
	}
	uu.FillZero();
	uint32_t i;
	for(i = 0; i < n; ++i,++j){
		*(uu._Data+i) = *(u._Data+j);
	}
	uu._Data[i] = u_max;
}

int Div_trimZeros(ext::BigNumMutable& uu){
	int i = uu.GetLength()-1;
	for(; i >= 0; i--){
		if(*(uu._Data+i) != 0){
			break;
		}
	}
	uint32_t zero_trimmed = uu.GetLength() - i - 1;
	uu.TrimLeadingZero();
	return zero_trimmed;
}

void Div_Multiply_subtract(ext::BigNumMutable& uu, ext::BigNumMutable& vv, BN_BLK& qp){
	ext::BigNumMutable vvv;
	BN_AbsMul(vv, qp, vvv);
	uint32_t trimmed_u = Div_trimZeros(uu);
	uint32_t trimmed_v = Div_trimZeros(vv);
	uu -= vvv;
	if(uu.IsNegative())
	{
		--qp;
		uu+=vvv;
	}
	uu.ExtendLength(trimmed_u);
	vv.ExtendLength(trimmed_v);
}

void Div_Copy_new_U(ext::BigNumMutable& uu, ext::BigNumMutable& u, uint32_t j, uint32_t n){
	uint32_t i = 0;
	for(;i < n;i++){
		*(u._Data + i + j) = *(uu._Data + i);
	}
	if( i+j < u.GetLength()){
		*(u._Data + i + j) = *(uu._Data + i);;
	}
}

void Div_Unnormalize(ext::BigNumMutable& Remainder, ext::BigNumMutable& a_temp, uint32_t n, int d){
	for(uint32_t i = n; i < a_temp.GetLength();i++){
		a_temp._Data[i] = 0;
	}
	a_temp.TrimLeadingZero();
	a_temp >>= d;
	Remainder = a_temp;
}
/*
 Sign Rules:
 for example: (result means 'this')
 -       20 /  3 --> result:  6   remainder:  2
 -      -20 /  3 --> result: -6   remainder: -2
 -       20 / -3 --> result: -6   remainder:  2
 -      -20 / -3 --> result:  6   remainder: -2
 */
void Div_Set_sign(const BigNumRef& a, const BigNumRef& b,ext::BigNumMutable& quotient, ext::BigNumMutable& Remainder){
	quotient.SetSign(a.GetSign() != b.GetSign());
	Remainder.SetSign(a.GetSign());
}
} //namespace _details

void BN_Div(const BigNumRef& a, const BigNumRef& b, ext::BigNumMutable *remainder, ext::BigNumMutable& quotient)	//quotient = (a/b) + remainder, a is dividend, b is divisor
{
	static_assert(sizeof(BN_BLK)==sizeof(uint64_t),"BN_Div2 only supports 64 bits blocks");

	ext::BigNumMutable tmpRemainder;
	if(!remainder)
		remainder = &tmpRemainder;

	quotient.SetZero();
	remainder->SetZero();
	BN_BLK a_value_size, u0 = 0, u1 = 0, v1 = 0, v0 = 0, u2 = 0;
	ext::BigNumMutable a_temp = 0;
	a_temp += a;
	ext::BigNumMutable b_temp = 0;
	b_temp += b;
	a_temp._Sign = false;
	b_temp._Sign = false;
	//uint32_t m = a_temp.GetLength();
	uint32_t n = b_temp.GetLength();
	uint32_t j = a_temp.GetLength() - b_temp.GetLength();
	if(_details::Div_Standard_test(a_temp, b_temp)){
		*remainder = a_temp;
		_details::Div_Set_sign(a, b, quotient, *remainder);
		quotient.TrimLeadingZero();
		return;
	}
	if(n == 1){
		uint64_t r = 0;
		_details::Div_DivInt(a_temp, (uint64_t) *(b_temp._Data), r);
		*remainder = r;
		quotient = a_temp;
		_details::Div_Set_sign(a, b, quotient, *remainder);
		quotient.TrimLeadingZero();
		return;
	}
	int d;
	a_value_size = _details::Div_Normalize(a_temp, b_temp, d);
	if(j+n == a_temp.GetLength()){
		u2 = a_value_size;
	}
	else{
		u2 = a_temp.Data()[j+n];
	}
	ext::BigNumMutable uu = a_temp;
	ext::BigNumMutable vv = b_temp;
	quotient.SetLength(j+1);
	quotient.FillZero();
	while(true){
		u1 = a_temp.Data()[j+n-1];
		u0 = a_temp.Data()[j+n-2];
		v1 = b_temp.Data()[n-1];
		v0 = b_temp.Data()[n-2];
		BN_BLK qp = _details::Div_Calculate(u2, u1, u0, v1, v0);
		_details::Div_Make_new_U(uu, a_temp, j, n , u2);
		_details::Div_Multiply_subtract(uu,vv,qp);
		_details::Div_Copy_new_U(uu, a_temp, j, n);
		*(quotient._Data+j) = qp;
		if(j--==0){
			break;
		}
		u2 = a_temp.Data()[j+n];
		
	}
	_details::Div_Unnormalize(*remainder, a_temp, n, d);
	_details::Div_Set_sign(a, b, quotient, *remainder);
	quotient.TrimLeadingZero();
	return;
}
} // namespace _details

namespace _details{
NativeFloat::NativeFloat(float x_in)
{	// https://en.wikipedia.org/wiki/Single-precision_floating-point_format
	DWORD& x = *(DWORD*)&x_in;
	Mantissa = (x&0x007fffff)|0x800000;
	Exponent = ((x&0x7f800000)>>23) - 127 - 23;
	Sign = x&0x80000000;
}

NativeFloat::NativeFloat(double x_in)
{	// https://en.wikipedia.org/wiki/Double-precision_floating-point_format
	ULONGLONG& x = *(ULONGLONG*)&x_in;

	Mantissa = (x&0xfffffffffffffULL)|0x10000000000000ULL;
	Exponent = ((x&0x7ff0000000000000ULL)>>52) - 1023 - 52;
	Sign = x&0x8000000000000000ULL;
}
};

void BigNumMutable::_FromNativeFloat(const _details::NativeFloat& x)
{
	if(x.Mantissa)
	{
		SetSign(x.Sign);

		SetLength(sizeof(ULONGLONG)/sizeof(_details::BN_BLK));
		*(ULONGLONG*)&_Data[0] = x.Mantissa;
		if(sizeof(ULONGLONG)/sizeof(_details::BN_BLK)>1 && _Data[1] == 0)
			_Data.ShrinkSize(_Data.GetSize()-1);

		*this <<= x.Exponent;
	}
	else
	{
		SetSign(false);
		SetLength(0);
	}
}

const BigNumRough& BigNumMutable::operator = (const BigNumRough& x)
{
	SetSign(false);

	if(x.Mantissa)
	{
		SetLengthInByte(x.Exponent/8 + 4 + _details::BN_BLK_SIZE);
		FillZero();

		SetLength(sizeof(ULONGLONG)/sizeof(BN_BLK));

		*(ULONGLONG*)&_Data[0] = x.Mantissa;
		if constexpr (sizeof(ULONGLONG)/sizeof(BN_BLK)>1)
			if(_Data[1] == 0)_Data.ShrinkSize(_Data.GetSize()-1);

		operator <<= (x.Exponent);
	}
	else
	{
		SetLength(0);
	}

	return x;
}

void BigNumMutable::FlipSign()
{
	SetSign(!GetSign());
}

void BigNumMutable::DivFast(const BigNumRef& a, const BigNumRef& b) // this ~= a/b
{
	int exp;
	UINT m = _details::BN_Mantissa32(b, &exp);
	ASSERT(m);

	if(exp <= 0)
	{
		Div(a, *(UINT*)b.Data());
		return;
	}

	Div(a, m);
	*this >>= exp;
}

void BigNumMutable::DivRough(const BigNumRef& a, const BigNumRef& b) // this ~= a/b
{
	int exp;
	UINT m = _details::BN_Mantissa32(b, &exp);
	ASSERT(m);

	if(exp <= 0)
	{
		Div(a, *(UINT*)b.Data());
		return;
	}

	thread_local BigNumMutable wei;
	wei.CopyLowBits(exp, b);
	if(wei.IsZero())
	{
		Div(a, m);
		*this >>= exp;
		return;
	}

	thread_local BigNumMutable up, weighted;
	up.Div(a, m);	up >>= exp;		//_LOG("y0\t="<<up);// y0	
	Div(a, m+1);	*this >>= exp;	//_LOG("y1\t="<<*this);// y1
									//_LOG("wei\t="<<wei);
	weighted.Mul(*this, wei);		//_LOG("y1*wei\t="<<weighted);// y1*wei
	SetToPowerOfTwo(exp);
	*this -= wei;
	SetSign(false);					//_LOG("1-wei\t="<<*this); // (1-wei)

	wei.Mul(*this, up);				//_LOG("y0*(1-w)="<<up_weight);// y0*(1-wei)
	Add(wei, weighted);

	*this >>= exp;
}


void BigNumMutable::CopyLowBits(UINT w, const BigNumRef& a)
{
	typedef _details::BN_BLK	BN_BLK;

	ASSERT(a.GetLength()*sizeof(BN_BLK)*8 >= w);

	UINT len = (w + sizeof(BN_BLK)*8 - 1)/(sizeof(BN_BLK)*8);
	*this = BigNumRef(false, a.Data(), len);

	UINT remain = w%(sizeof(BN_BLK)*8);
	BN_BLK mask = (~((BN_BLK)0)) >> (sizeof(BN_BLK)*8 - remain);
	_Data[len-1] &= mask;

	TrimLeadingZero();
}

bool BigNumMutable::AreLowBitsZero(uint32_t w)
{
	typedef _details::BN_BLK	BN_BLK;

	w = std::min(w, uint32_t(GetLength() * sizeof(BN_BLK) * 8));

	uint32_t len = (w + sizeof(BN_BLK) * 8 - 1) / (sizeof(BN_BLK) * 8);

	uint32_t remain = w % (sizeof(BN_BLK) * 8);
	for (uint32_t i = 0; i + 1 < len; i++)
		if (_Data[i])
			return false;
	BN_BLK mask = (~((BN_BLK)0)) >> (sizeof(BN_BLK) * 8 - remain);
	return (_Data[len - 1] & mask) == 0;
}

uint8_t BigNumMutable::GetBit(uint32_t w)
{
	typedef _details::BN_BLK	BN_BLK;

	if (w >= uint32_t(GetLength() * sizeof(BN_BLK) * 8))
		return 0;

	return (_Data[w / (sizeof(BN_BLK) * 8)] >> (w % (sizeof(BN_BLK) * 8))) & 1;
}

void BigNumMutable::SetToPowerOfTwo(UINT exp)
{
	typedef _details::BN_BLK	BN_BLK;

	UINT len = (exp + sizeof(_details::BN_BLK)*8)/(sizeof(BN_BLK)*8);
	SetLength(len);
	FillZero();
	UINT remain = (exp%(sizeof(BN_BLK)*8));

	_Data[len-1] = ((BN_BLK)1)<<remain;
}

bool BigNumMutable::FromString(const rt::String_Ref& s)
{
	struct _Hex
	{	bool error;
		int ToVal(char a)
		{
			if('0'<=a && a<='9')
			{	return a -= '0';
			}
			else if(a>='A' && a<='F')
			{	return a + 10 - 'A';
			}
			else if(a>='a' && a<='f')
			{	return a + 10 - 'a';
			}
			error = true;
			return 0;
		}
		_Hex(){ error = false; }
	};

	if(s.IsEmpty())
		return false;

	_Hex h;
	bool sign = false;
	const char *pin = s.Begin();
	if(*pin == '-')
	{	sign = true;
		pin++;
	}
	else if(*pin == '+')
		pin++;

	if(*(WORD*)pin == 0x7830 || *(WORD*)pin == 0x5830)
	{	// base16
		pin+=2;
		UINT co = (UINT)(s.End() - pin);
		UINT exp = 0;
		{	WORD* t = (WORD*)(s.End() - 2);
			UINT t_co = co/2;
			SetLengthInByte((co + 1) / 2);
			FillZero();
			while(t_co && *t == 0x3030)
			{
				co -= 2;
				t_co--;
				t--;
				exp++;
			}

			char *pout = (char *)Data() + exp;
			for(UINT i=0; i<t_co; i++, t--, pout++)
			{
				*pout = (h.ToVal(((LPCSTR)t)[0]) << 4) | 
					 (h.ToVal(((LPCSTR)t)[1]));
				if(h.error)return false;
			}
			if(co&1)
			{
				*pout = h.ToVal(((LPCSTR)t)[1]);
				if(h.error)return false;
			}

			TrimLeadingZero();
			SetSign(sign);
			return true;
		}
	}
	else
	{	// base10
		int d = s.Last() - '0';
		if(d<0 || d>9)return false;

		*this = d;
		BigNumMutable mag = 10, val;

		for(const char *pcur = s.End() - 2; pcur != pin - 1; pcur--)
		{
			if(*pcur < '0' || *pcur > '9')
				return false;
			uint32_t dig = *pcur - '0';
			if(dig)
			{
				val.Mul(mag, dig);
				*this += val;
			}
			mag *= 10;
		}

		TrimLeadingZero();
		SetSign(sign);
		return true;
	}

	return false;
}

} // namespace oxd


