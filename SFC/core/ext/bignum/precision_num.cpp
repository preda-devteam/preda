#include "precision_num.h"
#include "big_num.h"

#pragma warning(disable:4244)

#pragma pack(push, 4)
#include "./ttmath/ttmath.h"

// Add msvc.asm to the project on MSVC if linker errors
// https://stackoverflow.com/questions/33751509/external-assembly-file-in-visual-studio

namespace ext
{
namespace _details
{

template<int bit_width>
struct TTMathType;
	template<>
	struct TTMathType<256>
	{ 	// 1:3
		typedef ttmath::Big<TTMATH_BITS(64), TTMATH_BITS(192)> Float;
		static_assert(sizeof(Float) == sizeof(PrecisionFloat<256>), "Size of TTMath type inconsistent");
	};
	template<>
	struct TTMathType<512>
	{	// 1:7
		typedef ttmath::Big<TTMATH_BITS(64), TTMATH_BITS(448)> Float;
		static_assert(sizeof(Float) == sizeof(PrecisionFloat<512>), "Size of TTMath type inconsistent");
	};
	template<>
	struct TTMathType<1024>
	{	// 1:15
		typedef ttmath::Big<TTMATH_BITS(64), TTMATH_BITS(960)> Float;
		static_assert(sizeof(Float) == sizeof(PrecisionFloat<1024>), "Size of TTMath type inconsistent");
	};
	template<>
	struct TTMathType<2048>
	{	// 1:31
		typedef ttmath::Big<TTMATH_BITS(64), TTMATH_BITS(1984)> Float;
		static_assert(sizeof(Float) == sizeof(PrecisionFloat<2048>), "Size of TTMath type inconsistent");
	};
	template<>
	struct TTMathType<8192>
	{	// 1:127
		typedef ttmath::Big<TTMATH_BITS(64), TTMATH_BITS(8128)> Float;
		static_assert(sizeof(Float) == sizeof(PrecisionFloat<8192>), "Size of TTMath type inconsistent");
	};

template<int bit_width>
PrecisionFloat<bit_width>::PrecisionFloat(double x)
{
	typedef typename TTMathType<bit_width>::Float Type;
	new (_Data) Type(x);
}

template<int bit_width>
PrecisionFloat<bit_width>::PrecisionFloat(LPCSTR val_str)
{
	typedef typename TTMathType<bit_width>::Float Type;
	new (_Data) Type(val_str);
}

template<int bit_width>
PrecisionFloat<bit_width>::PrecisionFloat(ULONGLONG x, int exp)
{
	typedef typename TTMathType<bit_width>::Float Type;
	new (_Data) Type((ttmath::uint)x);
	if(exp && x)((Type*)_Data)->exponent += exp;
}

template<int bit_width>
PrecisionFloat<bit_width>::PrecisionFloat(LONGLONG x, int exp)
{
	typedef typename TTMathType<bit_width>::Float Type;
	new (_Data) Type((ttmath::sint)x);
	if(exp && x)((Type*)_Data)->exponent += exp;
}

template<int bit_width>
bool PrecisionFloat<bit_width>::Pow(ULONGLONG idx)
{
	typedef typename TTMathType<bit_width>::Float Type;
	return 0 == ((Type*)_Data)->PowUInt(ttmath::UInt<TTMATH_BITS(64)>((ttmath::uint)idx));
}

template<int bit_width>
bool PrecisionFloat<bit_width>::Pow(LONGLONG idx)
{
	typedef typename TTMathType<bit_width>::Float Type;
	return 0 == ((Type*)_Data)->PowInt(ttmath::Int<TTMATH_BITS(64)>((ttmath::sint)idx));
}

template<int bit_width>
bool PrecisionFloat<bit_width>::Pow(const PrecisionFloat& idx)
{
	typedef typename TTMathType<bit_width>::Float Type;
	return 0 == ((Type*)_Data)->PowFrac(*((Type*)idx._Data));
}

template<int bit_width>
bool PrecisionFloat<bit_width>::Log(const PrecisionFloat& f, const PrecisionFloat& base)
{
	typedef typename TTMathType<bit_width>::Float Type;
	return 0 == ((Type*)_Data)->Log(*((Type*)f._Data), *((Type*)base._Data));
}

template<int bit_width>
bool PrecisionFloat<bit_width>::Add(const PrecisionFloat& f)
{
	typedef typename TTMathType<bit_width>::Float Type;
	return 0 == ((Type*)_Data)->Add(*((Type*)f._Data));
}

template<int bit_width>
void PrecisionFloat<bit_width>::FlipSign()
{
	typedef typename TTMathType<bit_width>::Float Type;
	((Type*)_Data)->ChangeSign();
}

template<int bit_width>
bool PrecisionFloat<bit_width>::Sub(const PrecisionFloat& f)
{
	typedef typename TTMathType<bit_width>::Float Type;
	return 0 == ((Type*)_Data)->Sub(*((Type*)f._Data));
}

template<int bit_width>
bool PrecisionFloat<bit_width>::Mul(const PrecisionFloat& f)
{
	typedef typename TTMathType<bit_width>::Float Type;
	return 0 == ((Type*)_Data)->Mul(*((Type*)f._Data));
}

template<int bit_width>
bool PrecisionFloat<bit_width>::Div(const PrecisionFloat& f)
{
	typedef typename TTMathType<bit_width>::Float Type;
	return 0 == ((Type*)_Data)->Div(*((Type*)f._Data));
}

template<int bit_width>
bool PrecisionFloat<bit_width>::IsZero() const
{
	typedef typename TTMathType<bit_width>::Float Type;
	return ((Type*)_Data)->IsZero();
}

template<int bit_width>
bool PrecisionFloat<bit_width>::IsSign() const
{
	typedef typename TTMathType<bit_width>::Float Type;
	return ((Type*)_Data)->IsSign();
}

template<int bit_width>
void PrecisionFloat<bit_width>::MulPowOf2(int exp)
{
	typedef typename TTMathType<bit_width>::Float Type;
	if(!((Type*)_Data)->IsZero())
		((Type*)_Data)->exponent += exp;
}

template<int bit_width>
bool PrecisionFloat<bit_width>::MulBigNum(BigNumMutable& a, bool round_down) const
{
	BigNumMutable ret;
	if(MulBigNum(a, ret, round_down))
	{
		rt::Swap(ret, a);
		return true;
	}

	return false;
}

template<int bit_width>
bool PrecisionFloat<bit_width>::MulBigNum(const BigNumRef& a, BigNumMutable& ret, bool round_down) const
{
	typedef typename TTMathType<bit_width>::Float Type;

	Type& f = *((Type*)_Data);

	// for now we don't support exponent larger than 2^64, which is already astronomical anyway
	static_assert(sizeof(f.exponent) == 8);

	// result = a * mantissa * (2 ^ exponent)

	// first convert mantissa to big num
	static_assert(sizeof(f.mantissa) % 8 == 0);		// assuming mantissa bit-width is always multiple of 64
	constexpr uint32_t mantissa_len = sizeof(f.mantissa) / 8;
	// TTMath float representation can sometimes be suboptimal, e.g. it might store 6 not as 3 * (2 ^ 1), but rather as 384 * (2 ^ -6)
	// This would cause a * mantissa to be unnecessarily larger than needed.
	// Therefore we remove trailing zero-bits from the mantissa and add that back to the exponent.
	// We only remove multiple of 64 bits though because that's easier and a smaller chunk wouldn't make a * mantissa much larger anyway.
	uint32_t base = 0;
	for(; base < mantissa_len; base++)
	{
		uint64_t cur_word = ((uint64_t*)(&f.mantissa))[base];
		if(cur_word)break;
	}

	// now calculate a * mantissa
	BigNumRef mantissa(f.IsSign(), ((uint64_t*)(&f.mantissa)) + base, mantissa_len - base);
	ret.Mul(mantissa, a);

	// finally apply (2 ^ exponent) using shift operation
	int64_t exponent = *((int64_t*)(&f.exponent)) + base * 64;
	if (exponent >= 0)
		ret <<= exponent;
	else
	{
		bool need_round_up = ret.GetBit(-exponent - 1) == 1;	// check the highest bit to be shifted out, it decides whether the number should be rounded up
		ret >>= -exponent;
		if (need_round_up && !round_down)
		{
			if (ret.IsNegative())
				ret -= 1;
			else
				ret += 1;
		}
	}

	return true;
}

template<int bit_width>
std::string PrecisionFloat<bit_width>::ToString() const
{
	typedef typename TTMathType<bit_width>::Float Type;
	return ((Type*)_Data)->ToString();
}

template<int bit_width>
bool PrecisionFloat<bit_width>::ToNumber(SIZE_T& x_out) const
{
	typedef typename TTMathType<bit_width>::Float Type;
	
	ttmath::uint x;
	if(((Type*)_Data)->ToInt(x) == 0)
	{	x_out = x;
		return true;
	}

	return false;
}

template<int bit_width>
bool PrecisionFloat<bit_width>::ToNumber(double& x) const
{
	typedef typename TTMathType<bit_width>::Float Type;
	return ((Type*)_Data)->ToDouble(x) == 0;
}

template class PrecisionFloat<256>;
template class PrecisionFloat<512>;
template class PrecisionFloat<1024>;
template class PrecisionFloat<2048>;
template class PrecisionFloat<8192>;
}} // namespace ext::_details
#pragma pack(pop)