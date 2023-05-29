#pragma once

/**
 * @file big_num.h
 * @author SFC dev team
 * @brief 
 * @version 1.0
 * @date 2021-04-30
 * 
 * @copyright  
 * System Foundation Classes(SFC)
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *      * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *      * Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials provided
 *        with the distribution.
 *      * Neither the name of SFC.  nor the names of its
 *        contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *  
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   
 */
 
/** \defgroup bigNum bigNum
 * @ingroup ext
 *  @{
 */
#include "../../rt/type_traits.h"
#include "../../rt/string_type.h"
#include "../../rt/buffer_type.h"


namespace ext
{
/** \defgroup bigNum bigNum
 * @ingroup ext
 *  @{
 */

class BigNumMutable;
class BigNumRough;

namespace _details
{

class NativeInt;
class NativeFloat;

//typedef uint32_t		BN_BLK;
typedef uint64_t		BN_BLK;
typedef const BN_BLK*	LPC_BN_BLK;
static const UINT		BN_BLK_SIZE = sizeof(BN_BLK);
static const UINT		BN_BLK_BITSIZE = sizeof(BN_BLK)*8;

class BN_Unsigned;
class BN_Ref;

extern bool		BN_Less(const BN_Ref& a, const BN_Ref& b); ///< a < b
extern bool		BN_Equal(const BN_Ref& a, const BN_Ref& b); ///< a == b
extern bool		BN_LessOrEqual(const BN_Ref& a, const BN_Ref& b); ///< a <= b
extern int		BN_Compare(const BN_Ref& a, const BN_Ref& b); ///< a < b: -1, a == b:0, a > b:1
extern bool		BN_IsZero(const BN_Ref& a);

extern bool		BN_AbsLess(const BN_Unsigned& a, const BN_Unsigned& b); ///< a < b
extern bool		BN_AbsEqual(const BN_Unsigned& a, const BN_Unsigned& b); ///< a == b
extern bool		BN_AbsLessOrEqual(const BN_Unsigned& a, const BN_Unsigned& b); ///< a <= b
extern int		BN_AbsCompare(const BN_Unsigned& a, const BN_Unsigned& b); ///< a < b: -1, a == b:0, a > b:1

extern void		BN_ToString(const BN_Ref& a, rt::String& out, int base);

extern void		BN_Add(const BN_Ref& a, const BN_Ref& b, ext::BigNumMutable& ret); ///< ret = a + b
extern void		BN_Sub(const BN_Ref& a, const BN_Ref& b, ext::BigNumMutable& ret); ///< ret = a - b
extern void		BN_Add(const BN_Ref& b, ext::BigNumMutable& ret); ///< ret += b
extern void		BN_Sub(const BN_Ref& b, ext::BigNumMutable& ret); ///< ret -= b
extern void		BN_AbsAdd(const BN_Unsigned& a, const BN_Unsigned& b, ext::BigNumMutable& ret); ///< ret = a + b
extern void		BN_AbsSub(const BN_Unsigned& a, const BN_Unsigned& b, ext::BigNumMutable& ret); ///< ret = a - b
extern void		BN_AbsAdd(const BN_Unsigned& b, ext::BigNumMutable& ret); ///< ret += b
extern void		BN_AbsSub(const BN_Unsigned& b, ext::BigNumMutable& ret); ///< ret -= b
extern UINT		BN_Mantissa32(const BN_Unsigned& b, int* exp);
extern auto		BN_Mantissa64(const BN_Unsigned& b, int* exp) -> ULONGLONG;

extern void		BN_Mul(const BN_Ref& a, const BN_Ref& b, ext::BigNumMutable& ret); ///< ret = a*b
extern void		BN_Mul(const BN_Ref& a, const NativeFloat& b, ext::BigNumMutable& ret); ///< ret = a*b
extern void		BN_Mul(const NativeFloat& b, ext::BigNumMutable& ret);

extern void		BN_AbsMul(const BN_Unsigned& a, UINT b, ext::BigNumMutable& ret); ///< ret = a*b
extern void		BN_AbsMul(const BN_Unsigned& a, ULONGLONG b, ext::BigNumMutable& ret); ///< ret = a*b
extern void		BN_AbsMul(UINT b, ext::BigNumMutable& ret); ///< ret *= b

/**
 * @brief ret = (a - *reminder)/b
 * 
 * if it is an early out case, quotient and remainder will both be 0.
 * @param a 
 * @param b 
 * @param reminder 
 * @param ret 
 * @return 
*/
extern bool		BN_Div(const BN_Unsigned& a, UINT b, UINT* reminder, ext::BigNumMutable& ret); ///<ret = (a - *reminder)/b
/**
 * @brief ret = (a - *reminder)/b
 * 
 * if it is an early out case, quotient and remainder will both be 0.
 * @param a 
 * @param b 
 * @param remainder 
 * @param ret 
*/
extern void     BN_Div(const BN_Ref& a, const BN_Ref& b, ext::BigNumMutable *remainder, ext::BigNumMutable& ret);

extern double	BN_2_double(const BN_Ref& x);
extern float	BN_2_float(const BN_Ref& x);
extern bool		BN_2_rough(const BN_Ref& x, BigNumRough* out); // false if range exceeds, but *out will be the saturated value

class BN_Unsigned
{
public:
	UINT		Len;
	BN_BLK*		pData;

	UINT		GetLength() const { return Len; }
	LPC_BN_BLK	Data() const { return pData; }

	template<typename T>
	BN_Unsigned(const T& x):BN_Unsigned((BN_BLK*)x.Data(), x.GetLength()){}
	BN_Unsigned() = default;
	BN_Unsigned(BN_BLK* data, UINT len){ Len = len; pData = data; }

	bool			IsLeadingZeroTrimmed() const { return Len == 0 || pData[Len-1]; }
	BN_Unsigned		SubVal(UINT s) const { return BN_Unsigned(pData + s, Len - s); }
	BN_Unsigned		SubVal(UINT s, UINT len) const { return BN_Unsigned(pData + s, Len); }
};

class BN_Ref: public BN_Unsigned
{
public:
	bool		Sign;
	bool		GetSign() const { return Sign; }
	UINT		GetLength() const { return Len; }
	LPC_BN_BLK	Data() const { return pData; }

	BN_Ref(){ Sign = false; Len = 0; pData = nullptr; }
	BN_Ref(bool sign, const BN_BLK* data, UINT len){ Sign = sign; Len = len; pData = (BN_BLK*)data; }

	BN_Ref		Abs() const { return BN_Ref(false, pData, Len); }
	BN_Ref		Negate() const { return BN_Ref(!Sign, pData, Len); }
};


#pragma pack(push, 1)
struct BN_Dyn
{
	friend class BigNumMutable;

	rt::BufferEx<BN_BLK>	_Data;
	bool					_Sign;

	BN_Dyn(){ _Sign = false; }

	bool		GetSign() const { return _Sign; }
	void		SetSign(bool x) { _Sign = x; }

	UINT		GetLength() const { return (UINT)_Data.GetSize(); }
	void		SetLength(UINT len){ _Data.SetSize(len); }
	void		SetLengthInByte(UINT s){ SetLength((s - 1 + BN_BLK_SIZE)/BN_BLK_SIZE); }

	LPC_BN_BLK	Data() const { return _Data; }
	BN_BLK&		Last(){ return _Data[_Data.GetSize()-1]; }
	BN_BLK&		AppendLast(){ return _Data.push_back(); }
	void		ExtendLength(UINT len) { rt::Zero(_Data.push_back_n(len), sizeof(BN_BLK)*len); }

	void		FillZero(){ _Data.Zero(); }
	void		LeftShift(UINT a);
	void		RightShift(UINT a);
	void		TrimLeadingZero();
	void		SetZero(){ SetSign(false); SetLength(0); }

	operator	BN_Ref() const { return BN_Ref(_Sign, _Data.Begin(), (UINT)_Data.GetSize()); }
	BN_Unsigned	SubVal(UINT s) const { return BN_Unsigned((BN_BLK*)_Data.Begin() + s, (UINT)(_Data.GetSize() - s)); }
	BN_Unsigned	SubVal(UINT s, UINT len) const { return BN_Unsigned((BN_BLK*)_Data.Begin() + s, len); }
	BN_Ref		Abs() const { return BN_Ref(false, (BN_BLK*)_Data.Begin(), (UINT)_Data.GetSize()); }
	BN_Ref		Negate() const { return BN_Ref(!GetSign(), _Data.Begin(), (UINT)GetLength()); }
};
#pragma pack(pop)


#pragma pack(push, 1)
template<int BLK_LEN = sizeof(ULONGLONG)/sizeof(BN_BLK)>
struct BN_Fix
{
	friend class BigNumMutable;

	BYTE		_Sign_Len; ///< base 2^32
	BN_BLK		_Data[BLK_LEN]; ///< size = _Len

	bool		GetSign() const { return _Sign_Len&0x80; }
	UINT		GetLength() const { return _Sign_Len&0x7f; }
	LPC_BN_BLK	Data() const { return _Data; }

	BN_Fix(){ _Sign_Len = 0; }

	UINT		GetEmbeddedSize() const { return 1 + GetLength()*BN_BLK_SIZE; } ///< POD Size
	bool		IsNonnegative() const { return (_Sign_Len&0x80) == 0; }
	void		SetSign(bool x) { _Sign_Len = (_Sign_Len&0x7f)|(x?0x80:0); }

	operator	BN_Ref() const { return BN_Ref(GetSign(), _Data, GetLength()); }
	BN_Unsigned	SubVal(UINT s) const { return BN_Unsigned((BN_BLK*)_Data + s, GetEmbeddedSize() - s); }
	BN_Unsigned	SubVal(UINT s, UINT len) const { return BN_Unsigned((BN_BLK*)_Data + s, len); }

	BN_Ref		Abs() const { return BN_Ref(false, (BN_BLK*)_Data, GetEmbeddedSize()); }
	BN_Ref		Negate() const { return BN_Ref(!GetSign(), _Data, GetLength()); }
};
#pragma pack(pop)

} // namespace _details

/** \defgroup Typedefs_BigNum Typedefs_BigNum
 * @ingroup bigNum
 *  @{
 */
typedef _details::BN_Ref	BigNumRef;

#pragma pack(push, 1)
class BigNumRough
{
	TYPETRAITS_DECLARE_POD;

public:
	static const UINT MANTISSA_BITS = 32;
	static const UINT EXPONENT_LIMIT = sizeof(_details::BN_BLK)*8*127;

	UINT		Mantissa;
	WORD		Exponent; // base2

public:
	auto&		operator = (const BigNumRough& x){ rt::Copy(*this, x); return x; }
	ULONGLONG	operator = (ULONGLONG n);
	bool		operator < (const BigNumRough&x) const;
	bool		operator > (const BigNumRough&x) const;
	bool		operator <= (const BigNumRough&x) const;
	bool		operator >= (const BigNumRough&x) const;
	bool		operator == (const BigNumRough&x) const;

	bool		IsZero() const { return Mantissa == 0; }
	double		ToDouble() const { return pow(2.0, (double)Exponent)*Mantissa; }
	float		ToFloat() const { return pow(2.0f, (float)Exponent)*Mantissa; }
	BigNumRough	operator <<(int x) const // may overflow
				{	BigNumRough r = *this;
					if(x+Exponent<EXPONENT_LIMIT){ r.Exponent += x; }
					else { ((DWORD&)r) <<= (x+Exponent-EXPONENT_LIMIT); r.Exponent = EXPONENT_LIMIT; }
					return r;
				}
	BigNumRough	operator >>(int x) const
				{	BigNumRough r = *this;
					if(x <= Exponent){ r.Exponent -= x; }
					else{ r.Exponent=0; ((DWORD&)r)>>=x; }
					return r;
				}
	template<class t_Ostream>
	friend t_Ostream& operator<<(t_Ostream& Ostream, const BigNumRough& x){	return Ostream << x.ToDouble();	}
	static const BigNumRough& Zero(){ static const DWORD _ = 0; return (BigNumRough&)_; }
};

#pragma pack(pop)
#pragma pack(push, 1)
template<class STORE_CLS>
struct BigNumImmutable: public STORE_CLS
{
	typedef _details::BN_BLK	BN_BLK;
	
	bool		IsNegative() const { return STORE_CLS::GetSign(); }
	bool		IsNonNegative() const { return !STORE_CLS::GetSign() || STORE_CLS::GetLength() == 0; }
	bool		IsPositive() const { return !STORE_CLS::GetSign() && STORE_CLS::GetLength() > 0; }

	bool		operator < (const BigNumRef& x) const { return _details::BN_Less(*this, x); }
	bool		operator > (const BigNumRef& x) const { return _details::BN_Less(x, *this); }
	bool		operator <= (const BigNumRef& x) const { return _details::BN_LessOrEqual(*this, x); }
	bool		operator >= (const BigNumRef& x) const { return _details::BN_LessOrEqual(x, *this); }
	bool		operator == (const BigNumRef& x) const { return _details::BN_Equal(*this, x); }
	bool		operator != (const BigNumRef& x) const { return !_details::BN_Equal(*this, x); }
	bool		operator > (ULONGLONG x) const { return !IsNegative() && (STORE_CLS::GetLength()>1 || (STORE_CLS::GetLength()==1 && STORE_CLS::Data()[0] >x)); }

	template<class t_Ostream>
	friend t_Ostream& operator<<(t_Ostream& Ostream, const BigNumImmutable& x)
				{	rt::String out;
					x.ToString(out, 10);
					return Ostream << out;
				}

	auto		Abs() const 
				{	BigNumImmutable<_details::BN_Ref> x;
					x.Len = STORE_CLS::GetLength();	x.pData = (BN_BLK *)STORE_CLS::Data();
					return x;
				}
	auto		Negate() const 
				{	BigNumImmutable<_details::BN_Ref> x;
					x.Len = STORE_CLS::GetLength();	x.pData = (BN_BLK *)STORE_CLS::Data();	x.Sign = !STORE_CLS::GetSign();
					return x;
				}

	template<typename T>
	bool		To(T* x) const
				{	if(sizeof(T) < sizeof(BN_BLK)*STORE_CLS::GetLength())return false;
					*x = 0;
					memcpy(x, STORE_CLS::Data(), sizeof(BN_BLK)*STORE_CLS::GetLength());
					return true;
				}
	bool		To(double* x) const { *x = BN_2_double(*this); return true; }
	bool		To(float* x) const { *x = BN_2_float(*this); return true; }
	bool		To(BigNumRough* x) const { BN_2_rough(*this, x); return true; }

	double		ToDouble() const { return BN_2_double(*this); }
	float		ToFloat() const { return BN_2_float(*this); }
	BigNumRough	ToRough() const { BigNumRough ret; BN_2_rough(*this, &ret); return ret; }
	/** @brief to string only append
	 */
	rt::String& ToString(rt::String& out, int base = 10) const { BN_ToString(*this, out, base); return out; }
	bool		IsZero() const { return BN_IsZero(*this); }
};
#pragma pack(pop)

namespace _details
{
class NativeInt: public BigNumImmutable<BN_Fix<>> ///< All native integers
{
public:
	NativeInt(unsigned int   x){ *this = x; }
	NativeInt(         int   x){ *this = x; }
	NativeInt(unsigned short x){ *this = x; }
	NativeInt(         short x){ *this = x; }
	NativeInt(LONGLONG       x){ *this = x; }
	NativeInt(ULONGLONG      x){ *this = x; }

	unsigned int	operator = (unsigned int   x){ if(x){ _Sign_Len = 1; _Data[0] = x; }else{ _Sign_Len = 0; } return x; }
	unsigned short	operator = (unsigned short x){ if(x){ _Sign_Len = 1; _Data[0] = x; }else{ _Sign_Len = 0; } return x; }
	int				operator = (int			x){ if(x){ if(x>=0){ _Sign_Len = 1; _Data[0] = x; }else{ _Sign_Len = 0x81; _Data[0] = -x; } }else{ _Sign_Len = 0; } return x; }
	short			operator = (short		x){ if(x){ if(x>=0){ _Sign_Len = 1; _Data[0] = x; }else{ _Sign_Len = 0x81; _Data[0] = -x; } }else{ _Sign_Len = 0; } return x; }

	ULONGLONG		operator = (ULONGLONG	   x)
					{	if(x)
						{	_Sign_Len = sizeof(ULONGLONG)/sizeof(BN_BLK);
							*(ULONGLONG*)&_Data[0] = x;
							if(sizeof(ULONGLONG)/sizeof(BN_BLK)>1 && _Data[1] == 0)
								_Sign_Len--;
						}
						else{ _Sign_Len = 0; }
						return x; 
					}
	LONGLONG		operator = (LONGLONG    x)
					{	if(x == 0){ _Sign_Len = 0; return x; }
						if(x>0)
						{	_Sign_Len = sizeof(ULONGLONG)/sizeof(BN_BLK);
							*(ULONGLONG*)&_Data[0] = x;
						}
						else
						{	_Sign_Len = 0x80 | (sizeof(ULONGLONG)/sizeof(BN_BLK));
							*(ULONGLONG*)&_Data[0] = -x; 
						}
						if(sizeof(ULONGLONG)/sizeof(BN_BLK)>1 && _Data[1] == 0)
							_Sign_Len--;
						return x;
					}
};

class NativeFloat
{
public:
	bool		Sign;
	ULONGLONG	Mantissa;
	int			Exponent; ///< base2, can be negative

	NativeFloat(float x);
	NativeFloat(double x);
};
} // namespace _details


class BigNumMutable: public BigNumImmutable<_details::BN_Dyn>
{
	typedef BigNumImmutable<_details::BN_Dyn> _SC;
	void _FromNativeFloat(const _details::NativeFloat& x);
public:
	static const int MANTISSA_SIZE_MIN = 8;

public:
	template<class S>
	auto&			operator = (const BigNumImmutable<S>& x)
					{	SetSign(x.GetSign());
						SetLength(x.GetLength());
						memcpy(_Data, x.Data(), x.GetLength()*_details::BN_BLK_SIZE);
						return x;
					}

	auto& operator = (const BigNumMutable& x) { return operator = <_details::BN_Dyn>(x); }
	BigNumMutable(){}
	template<class S>
	BigNumMutable(const BigNumImmutable<S>& x){ *this = x; }
	BigNumMutable(const BigNumMutable& x){ *this = x; }
	BigNumMutable(BigNumMutable&& x) { rt::Copy(*this, x); rt::Zero(x); }
	BigNumMutable(unsigned int x){ *this = x; }
	BigNumMutable(int x){ *this = x; }
	BigNumMutable(unsigned short x){ *this = x; }
	BigNumMutable(short x){ *this = x; }
	BigNumMutable(LONGLONG x){ *this = x; }
	BigNumMutable(ULONGLONG x){ *this = x; }
	BigNumMutable(float x){ *this = x; }
	BigNumMutable(double x){ *this = x; }
	BigNumMutable(const rt::String_Ref& s){ *this = s; }
	BigNumMutable(const BigNumRough& x) { *this = x; }

protected:					
	void 			_FromNativeInt(const _details::NativeInt& x){ *this = x; }
			
public:		
	auto&			operator = (const BigNumRef& x)
					{	SetSign(x.GetSign());
						SetLength(x.GetLength());
						memcpy(_Data, x.Data(), x.GetLength()*_details::BN_BLK_SIZE);
						return x;
					}
	auto&			operator = (const _details::BN_Unsigned& x)
					{	SetLength(x.GetLength());
						memcpy(_Data, x.Data(), x.GetLength()*_details::BN_BLK_SIZE);
						return x;
					}
	unsigned int 	operator = (unsigned int x){ _FromNativeInt(x); return x; }
	int 		 	operator = (int x){ _FromNativeInt(x); return x; }
	unsigned short 	operator = (unsigned short x){ _FromNativeInt(x); return x; }
	short 			operator = (short x){ _FromNativeInt(x); return x; }
	int64_t 		operator = (int64_t x){ _FromNativeInt(x); return x; }
	uint64_t 		operator = (uint64_t x){ _FromNativeInt(x); return x; }
	float 			operator = (float x){ _FromNativeFloat(x); return x; }
	double 			operator = (double x){ _FromNativeFloat(x); return x; }

	const rt::String_Ref & operator = (const rt::String_Ref &x){ FromString(x); return  x; }
	const BigNumRough&     operator = (const BigNumRough& x);

	bool FromString(const rt::String_Ref& s);
	void FlipSign();

	void Add(const BigNumRef& a, const BigNumRef& b){ _details::BN_Add(a, b, *this); } ///< this = a + b
	void Sub(const BigNumRef& a, const BigNumRef& b){ _details::BN_Sub(a, b, *this); } ///< this = a - b
	void Add(const BigNumRef& a, const _details::NativeInt& b){ Add(a, (const BigNumImmutable<_details::BN_Fix<>>&)b); } ///< this = a + b
	void Sub(const BigNumRef& a, const _details::NativeInt& b){ Sub(a, (const BigNumImmutable<_details::BN_Fix<>>&)b); } ///< this = a - b
	/** @brief result cannot be any of the parameter */
	void Mul(const BigNumRef& a, const BigNumRef& b){ _details::BN_Mul(a, b, *this); } 
	void Mul(const BigNumRef& a, int b){ _details::BN_AbsMul(a, (UINT)abs(b), *this); SetSign(a.GetSign() != (b<0)); }
	void Mul(const BigNumRef& a, UINT b){ _details::BN_AbsMul(a, b, *this); SetSign(a.GetSign()); }
	void Mul(const BigNumRef& a, LONGLONG b){ _details::BN_AbsMul(a, (ULONGLONG)abs(b), *this); SetSign(a.GetSign() != (b<0)); }
	void Mul(const BigNumRef& a, ULONGLONG b){ _details::BN_AbsMul(a, b, *this); SetSign(a.GetSign()); }
	void Mul(const BigNumRef& a, float b){ _details::BN_Mul(a, _details::NativeFloat(b), *this); }
	void Mul(const BigNumRef& a, double b){ _details::BN_Mul(a, _details::NativeFloat(b), *this); }
	void Div(const BigNumRef& a, UINT b, UINT* reminder = nullptr){ _details::BN_Div(a, b, reminder, *this); }
	void Div(const BigNumRef& a, const BigNumRef& b, BigNumMutable* reminder = nullptr){ _details::BN_Div(a, b, reminder, *this); }

	void DivFast(const BigNumRef& a, const BigNumRef& b); ///< this ~= a/b (9 digits precision)
	void DivRough(const BigNumRef& a, const BigNumRef& b); ///< this ~= a/b (19 digits precision)

	void operator <<= (int shift){ shift>0?LeftShift(shift):RightShift(-shift); }
	void operator >>= (int shift){ shift>0?RightShift(shift):LeftShift(-shift); }

	void operator += (const BigNumRef& b){ BN_Add(b, *this); }
	void operator -= (const BigNumRef& b){ BN_Sub(b, *this); }
	void operator += (unsigned int x){ BN_Add(_details::NativeInt(x), *this); }
	void operator += (int x){BN_Add(_details::NativeInt(x), *this); }
	void operator += (unsigned short x){ BN_Add(_details::NativeInt(x), *this); }
	void operator += (short x){ BN_Add(_details::NativeInt(x), *this); }
	void operator += (LONGLONG x){ BN_Add(_details::NativeInt(x), *this); }
	void operator += (ULONGLONG x){ BN_Add(_details::NativeInt(x), *this); }
	void operator -= (unsigned int x){ BN_Sub(_details::NativeInt(x), *this); }
	void operator -= (int x){ BN_Sub(_details::NativeInt(x), *this); }
	void operator -= (unsigned short x){ BN_Sub(_details::NativeInt(x), *this); }
	void operator -= (short x){ BN_Sub(_details::NativeInt(x), *this); }
	void operator -= (LONGLONG x){ BN_Sub(_details::NativeInt(x), *this); }
	void operator -= (ULONGLONG x){ BN_Sub(_details::NativeInt(x), *this); }

	void operator *= (UINT b){ BN_AbsMul(b, *this); }
	void operator *= (int b){ BN_AbsMul(abs(b), *this); SetSign(GetSign() != (b<0)); }
	void operator *= (float b){ BN_Mul(_details::NativeFloat(b), *this); }
	void operator *= (double b){ BN_Mul(_details::NativeFloat(b), *this); }
	void operator /= (const BigNumRef& b) {
		BigNumMutable result;
		_details::BN_Div(*this, b, nullptr, result);
		*this = result;
	}

	void CopyLowBits(UINT w, const BigNumRef& a);
	void SetToPowerOfTwo(UINT exp);
};

typedef BigNumMutable	_BN;
/** @}*/
/** @}*/
} // namespace oxd
/** @}*/