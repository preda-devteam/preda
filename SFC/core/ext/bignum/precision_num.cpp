#include "precision_num.h"

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
	{	// 3:13
		typedef ttmath::Big<TTMATH_BITS(192), TTMATH_BITS(832)> Float;
		static_assert(sizeof(Float) == sizeof(PrecisionFloat<1024>), "Size of TTMath type inconsistent");
	};
	template<>
	struct TTMathType<2048>
	{	// 5:27
		typedef ttmath::Big<TTMATH_BITS(320), TTMATH_BITS(1728)> Float;
		static_assert(sizeof(Float) == sizeof(PrecisionFloat<2048>), "Size of TTMath type inconsistent");
	};
	template<>
	struct TTMathType<8192>
	{	// 9:119
		typedef ttmath::Big<TTMATH_BITS(576), TTMATH_BITS(7616)> Float;
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
PrecisionFloat<bit_width>::PrecisionFloat(ULONGLONG x)
{
	typedef typename TTMathType<bit_width>::Float Type;
	new (_Data) Type((ttmath::uint)x);
}

template<int bit_width>
PrecisionFloat<bit_width>::PrecisionFloat(LONGLONG x)
{
	typedef typename TTMathType<bit_width>::Float Type;
	new (_Data) Type((ttmath::sint)x);
}

template<int bit_width>
bool PrecisionFloat<bit_width>::Pow(ULONGLONG idx)
{
	typedef typename TTMathType<bit_width>::Float Type;
	return 0 == ((Type*)_Data)->PowUInt(ttmath::Big<TTMATH_BITS(0), TTMATH_BITS(64)>((ttmath::uint)idx));
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

//template<int bit_width>
//void PrecisionFloat<bit_width>::BN_Mul(const ext::BigNumRef& a, ext::BigNumMutable& b) const	// b = a*this
//{
//	typedef typename TTMathType<bit_width>::Float Type;
//	auto& f = *((Type*)_Data);
//
//	LONGLONG exp = f.exponent.ToInt();
//	if(exp + a.GetLength()*64 + sizeof(f.mantissa.table)*8 <= 0)
//		b.SetZero();
//
//	ASSERT((sizeof(f.mantissa.table)%sizeof(BN_BLK)) == 0);
//	::ext::_details::BN_Mul(a, BN_Ref(f.IsSign(), (BN_BLK*)f.mantissa.table, sizeof(f.mantissa.table)/sizeof(BN_BLK)), b);
//
//	b <<= (int)exp;
//}

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