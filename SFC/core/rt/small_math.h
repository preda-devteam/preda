#pragma once
/**
 * @file small_math.h
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
/** \defgroup rt rt 
 * @ingroup SFC
 *  @{
 */

#include "../../core/rt/type_traits.h"
#include "../../core/rt/string_type.h"

#pragma pack(1)

///////////////////////////////////////////////////////
// Small Vector 
namespace rt
{
	/** \defgroup small_math small_math
 * @ingroup rt
 *  @{
 */
//pre-declaration

template<typename t_Val, int chan>
struct Vec
{	static const int LEN=chan;
	typedef t_Val	 VALUE;
	t_Val	_p[LEN];
	
#define DEF_VEC_FUNC \
	typedef typename rt::_details::hash_compare_fix<Vec<t_Val, LEN> > hash_compare; \
	INLFUNC Vec(const rt::String_Ref& str){ FromString(str); } \
	INLFUNC Vec(){} \
	INLFUNC Vec(signed char x){ Set((int)x); } \
	INLFUNC Vec(BYTE x){ Set((VALUE)x); } \
	INLFUNC Vec(short x){ Set((VALUE)x); } \
	INLFUNC Vec(WORD x){ Set((VALUE)x); } \
	INLFUNC Vec(int x){ Set((VALUE)x); } \
	INLFUNC Vec(UINT x){ Set((VALUE)x); } \
	INLFUNC Vec(ULONGLONG x){ Set((VALUE)x); } \
	INLFUNC Vec(LONGLONG x){ Set((VALUE)x); } \
	INLFUNC Vec(float x){ Set((VALUE)x); } \
	INLFUNC Vec(double x){ Set((VALUE)x); } \
	template<typename T> \
	INLFUNC Vec(const Vec<T,LEN>& x){ CopyFrom(x.ptr()); } \
	INLFUNC t_Val*			ptr() { return _p; } \
	INLFUNC const t_Val*	ptr() const { return _p; } \
	INLFUNC t_Val			operator [](UINT i) const { ASSERT(i<LEN); return _p[i]; } \
	INLFUNC t_Val&			operator [](UINT i){ ASSERT(i<LEN); return _p[i]; } \
	INLFUNC t_Val			operator [](int i) const { ASSERT(i<LEN); return _p[i]; } \
	INLFUNC t_Val&			operator [](int i){ ASSERT(i<LEN); return _p[i]; } \
	INLFUNC void			Set(t_Val x){ ((Vec<t_Val, LEN-1>&)(*this)).Set(x); _p[LEN-1] = x; } \
	template<typename T>	\
	INLFUNC void			CopyTo(T* x) const { ((Vec<t_Val, LEN-1>&)(*this)).CopyTo(x); x[LEN-1] = (T)_p[LEN-1]; } \
	template<typename T>	\
	INLFUNC void			CopyFrom(const T* x){ ((Vec<t_Val, LEN-1>&)(*this)).CopyFrom(x); _p[LEN-1] = (VALUE)x[LEN-1]; } \
	INLFUNC void			Random(){ ((Vec<t_Val, LEN-1>&)(*this)).Random(); _p[LEN-1] = rand()*rt::TypeTraits<t_Val>::UnitVal()/(t_Val)RAND_MAX; } \
	INLFUNC void			Clamp(t_Val min, t_Val max){ ((Vec<t_Val, LEN-1>&)(*this)).Clamp(min, max); _p[LEN-1] = rt::max(min, rt::min(max, _p[LEN-1])); } \
	template<int t_start, int t_len> \
	INLFUNC Vec<t_Val, t_len>& SubVec(){ return *((Vec<t_Val, t_len>*)&_p[t_start]); } \
	template<int t_start, int t_len> \
	INLFUNC const Vec<t_Val, t_len>& SubVec() const { return *((Vec<t_Val, t_len>*)&_p[t_start]); } \
	\
	INLFUNC typename rt::TypeTraits<t_Val>::t_Accum \
	L2NormSqr() const { return ((Vec<t_Val, LEN-1>&)(*this)).L2NormSqr() + rt::Sqr(_p[LEN-1]); } \
	INLFUNC typename rt::TypeTraits<t_Val>::t_Accum \
	L2Norm() const { return sqrt(L2NormSqr()); } \
	\
	INLFUNC typename rt::TypeTraits<t_Val>::t_Accum \
	L2NormSqr(const Vec<t_Val, LEN>& x) const { return ((const Vec<t_Val, LEN-1>&)(*this)).L2NormSqr((const Vec<t_Val, LEN-1>&)x) + rt::Sqr(_p[LEN-1] - x[LEN-1]); } \
	INLFUNC typename rt::TypeTraits<t_Val>::t_Accum \
	L2Norm(const Vec<t_Val, LEN>& x) const { return sqrt(L2NormSqr(x)); } \
	INLFUNC typename rt::TypeTraits<t_Val>::t_Accum \
	Sum() const { return ((Vec<t_Val, LEN-1>&)(*this)).Sum() + _p[LEN-1]; } \
	INLFUNC void Min(const Vec<t_Val, LEN>& x1, const Vec<t_Val, LEN>& x2){ ((Vec<t_Val, LEN-1>&)(*this)).Min((const Vec<t_Val, LEN-1>&)x1, (const Vec<t_Val, LEN-1>&)x2); _p[LEN-1] = rt::min(x1[LEN-1], x2[LEN-1]); } \
	INLFUNC void Max(const Vec<t_Val, LEN>& x1, const Vec<t_Val, LEN>& x2){ ((Vec<t_Val, LEN-1>&)(*this)).Max((const Vec<t_Val, LEN-1>&)x1, (const Vec<t_Val, LEN-1>&)x2); _p[LEN-1] = rt::max(x1[LEN-1], x2[LEN-1]); } \
	\
	INLFUNC void AvgQuad(const Vec<t_Val, LEN>& x1, const Vec<t_Val, LEN>& x2, const Vec<t_Val, LEN>& x3, const Vec<t_Val, LEN>& x4) \
	{	((Vec<t_Val, LEN-1>&)(*this)).AvgQuad((const Vec<t_Val, LEN-1>&)x1, (const Vec<t_Val, LEN-1>&)x2, (const Vec<t_Val, LEN-1>&)x3, (const Vec<t_Val, LEN-1>&)x4); \
		_p[LEN-1] = (x1[LEN-1] + x2[LEN-1] + x3[LEN-1] + x4[LEN-1])/4; \
	} \
	\
	INLFUNC typename rt::TypeTraits<t_Val>::t_Accum \
	Dot(const Vec<t_Val, LEN>& x) const { return ((const Vec<t_Val, LEN-1>&)(*this)).Dot((const Vec<t_Val, LEN-1>&)x) + _p[LEN-1]*x[LEN-1]; } \
	\
	template<typename T> \
	INLFUNC bool operator == (T x) const { return ((Vec<t_Val, LEN-1>&)(*this)) == x && rt::NumericTraits<t_Val>::IsEqual(_p[LEN-1], (t_Val)x); } \
	template<typename T> \
	INLFUNC bool operator != (T x) const { return ((Vec<t_Val, LEN-1>&)(*this)) != x || rt::NumericTraits<t_Val>::IsNotEqual(_p[LEN-1], (t_Val)x); } \
	template<typename T> \
	INLFUNC Vec<t_Val, LEN>& operator /= (T x){ ((Vec<t_Val, LEN-1>&)(*this)) /= x; _p[LEN-1]= (t_Val)(_p[LEN-1]/x); return *this; } \
	template<typename T> \
	INLFUNC Vec<t_Val, LEN>& operator *= (T x){ ((Vec<t_Val, LEN-1>&)(*this)) *= x; _p[LEN-1]= (t_Val)(_p[LEN-1]*x); return *this; } \
	template<typename T> \
	INLFUNC Vec<t_Val, LEN>& operator += (T x){ ((Vec<t_Val, LEN-1>&)(*this)) += x; _p[LEN-1]= (t_Val)(_p[LEN-1]+x); return *this; } \
	template<typename T> \
	INLFUNC Vec<t_Val, LEN>& operator -= (T x){ ((Vec<t_Val, LEN-1>&)(*this)) -= x; _p[LEN-1]= (t_Val)(_p[LEN-1]-x); return *this; } \
	template<typename T> \
	INLFUNC bool operator == (const Vec<T, LEN>& x) const { return ((Vec<t_Val, LEN-1>&)(*this)) == (const Vec<T, LEN-1>&)x && rt::NumericTraits<t_Val>::IsEqual(_p[LEN-1], (t_Val)x[LEN-1]); } \
	template<typename T> \
	INLFUNC bool operator != (const Vec<T, LEN>& x) const { return ((Vec<t_Val, LEN-1>&)(*this)) != (const Vec<T, LEN-1>&)x || rt::NumericTraits<t_Val>::IsNotEqual(_p[LEN-1], (t_Val)x[LEN-1]); } \
	template<typename T> \
	INLFUNC Vec<t_Val, LEN>& operator /= (const Vec<T, LEN>& x){ ((Vec<t_Val, LEN-1>&)(*this)) /= (const Vec<T, LEN-1>&)x; _p[LEN-1]= (t_Val)(_p[LEN-1]/x[LEN-1]); return *this; } \
	template<typename T> \
	INLFUNC Vec<t_Val, LEN>& operator *= (const Vec<T, LEN>& x){ ((Vec<t_Val, LEN-1>&)(*this)) *= (const Vec<T, LEN-1>&)x; _p[LEN-1]= (t_Val)(_p[LEN-1]*x[LEN-1]); return *this; } \
	template<typename T> \
	INLFUNC Vec<t_Val, LEN>& operator += (const Vec<T, LEN>& x){ ((Vec<t_Val, LEN-1>&)(*this)) += (const Vec<T, LEN-1>&)x; _p[LEN-1]= (t_Val)(_p[LEN-1]+x[LEN-1]); return *this; } \
	template<typename T> \
	INLFUNC Vec<t_Val, LEN>& operator -= (const Vec<T, LEN>& x){ ((Vec<t_Val, LEN-1>&)(*this)) -= (const Vec<T, LEN-1>&)x; _p[LEN-1]= (t_Val)(_p[LEN-1]-x[LEN-1]); return *this; } \
	\
	INLFUNC Vec<t_Val, LEN>& Normalize(){ *this *= rt::TypeTraits<t_Val>::UnitVal()/rt::max(rt::TypeTraits<t_Val>::Epsilon(),(t_Val)sqrt(L2NormSqr())); return *this; } \
	INLFUNC Vec<t_Val, LEN>& FromString(const rt::String_Ref& x){ int ate = x.ToNumber(_p[0]); ((Vec<t_Val, LEN-1>*)&_p[1])->FromString(x.TrimLeft(ate)); return *this; } \
	template<typename T, typename T2> \
	INLFUNC void  Interpolate(const Vec<T, LEN>& x1, const Vec<T2, LEN>& x2, float alpha) \
	{	ASSERT(alpha >=0 && alpha<=1); \
		((Vec<t_Val, LEN-1>&)(*this)).Interpolate((Vec<T, LEN-1>&)x1, (Vec<T2, LEN-1>&)x2, alpha); \
		_p[LEN-1] = (t_Val)(x1[LEN-1]*(1-alpha) + x2[LEN-1]*alpha); \
	} \
	template<typename T> \
	INLFUNC void  Interpolate(const Vec<T, LEN>& x, const Vec<T, LEN>& xx, const Vec<T, LEN>& y, const Vec<T, LEN>& yy, float alpha_x, float alpha_y) \
	{	ASSERT(alpha_x >=0 && alpha_x<=1); \
		ASSERT(alpha_y >=0 && alpha_y<=1); \
		((Vec<t_Val, LEN-1>&)(*this)).Interpolate((Vec<T, LEN-1>&)x, (Vec<T, LEN-1>&)xx, (Vec<T, LEN-1>&)y, (Vec<T, LEN-1>&)yy, alpha_x, alpha_y); \
		_p[LEN-1] = (t_Val)((x[LEN-1]*(1-alpha_x) + xx[LEN-1]*alpha_x)*(1-alpha_y) + (y[LEN-1]*(1-alpha_x) + yy[LEN-1]*alpha_x)*alpha_y); \
	} \
	
	DEF_VEC_FUNC;

	INLFUNC t_Val Min() const { return rt::min(_p[LEN-1], ((Vec<t_Val, LEN-1>&)(*this)).Min()); }
	INLFUNC t_Val Max() const { return rt::max(_p[LEN-1], ((Vec<t_Val, LEN-1>&)(*this)).Max()); }
};
	template< typename t_Val >
	struct Vec<t_Val, 0>
	{
		INLFUNC void Set(t_Val x){}
		template<typename T>
		INLFUNC void CopyTo(T* x) const {}
		template<typename T>
		INLFUNC void CopyFrom(const T* x){}
		INLFUNC t_Val L2NormSqr() const { return 0; }
		INLFUNC t_Val L2NormSqr(const Vec<t_Val, 0>& x) const { return 0; }
		INLFUNC t_Val Sum() const { return 0; }
		INLFUNC void  AvgQuad(const Vec<t_Val, 0>& x1, const Vec<t_Val, 0>& x2, const Vec<t_Val, 0>& x3, const Vec<t_Val, 0>& x4){}
		INLFUNC t_Val Dot(const Vec<t_Val, 0>& x) const { return 0; }
		INLFUNC void  Random(){}
		INLFUNC void Clamp(t_Val min, t_Val max){}
		INLFUNC void FromString(const rt::String_Ref& x){}
		INLFUNC void Min(const Vec<t_Val, 0>& x1, const Vec<t_Val, 0>& x2){}
		INLFUNC void Max(const Vec<t_Val, 0>& x1, const Vec<t_Val, 0>& x2){}
		template<typename T, typename T2>
		INLFUNC void  Interpolate(const Vec<T, 0>& x1, const Vec<T2, 0>& x2, float alpha){}
		template<typename T>
		INLFUNC void  Interpolate(const Vec<T, 0>& x, const Vec<T, 0>& xx, const Vec<T, 0>& y, const Vec<T, 0>& yy, float alpha_x, float alpha_y){}
	
		template<typename T> INLFUNC void operator /= (T x){}
		template<typename T> INLFUNC void operator *= (T x){}
		template<typename T> INLFUNC void operator += (T x){}
		template<typename T> INLFUNC void operator -= (T x){}
		template<typename T> INLFUNC constexpr bool operator == (T x) const { return true; }
		template<typename T> INLFUNC constexpr bool operator != (T x) const { return false; }
	};

template<typename T, int chan>
class TypeTraits<Vec<T,chan> >
{	 												
public:													
	typedef Vec<T,chan>		t_Val;
	typedef T				t_Element;
	typedef Vec<typename TypeTraits<T>::t_Signed, chan>		t_Signed;
	typedef Vec<typename TypeTraits<T>::t_Unsigned, chan>	t_Unsigned;
	static const int Typeid		= _typeid_vec;		
	static const bool IsPOD		= true;				
	static const bool IsNumeric	= true;
};

template< typename t_Val >
struct Vec<t_Val, 1>
{	static const int LEN=1;
	typedef t_Val	 VALUE;
	union
	{	struct{ t_Val _p[1];	};
		struct{ t_Val x;		};
	};
	INLFUNC operator t_Val ()const{ return x; }

	template<typename t_Val2>
	INLFUNC const Vec& operator =(const Vec<t_Val2, 1>& i){ x = (t_Val)i.x; return *this; }

	template<typename t_Val2>
	INLFUNC const Vec& operator =(const Vec<t_Val2, 2>& i){ x=(t_Val)i.GetBrightness(); return *this; }
	template<typename t_Val2>
	INLFUNC const Vec& operator =(const Vec<t_Val2, 3>& i){ x=(t_Val)i.GetBrightness(); return *this; }
	template<typename t_Val2>
	INLFUNC const Vec& operator =(const Vec<t_Val2, 4>& i){ x=(t_Val)i.GetBrightness(); return *this; }
	
	INLFUNC Vec<t_Val, 1>& v1() { return *this; }
	INLFUNC const Vec<t_Val, 1>& v1() const { return *this; }

	INLFUNC t_Val GetBrightness()const { return x; }

	DEF_VEC_FUNC;
	INLFUNC t_Val Min(){ return _p[0]; }
	INLFUNC t_Val Max(){ return _p[0]; }
};

template< typename t_Val >
struct Vec<t_Val, 2>
{	static const int LEN=2;
	typedef t_Val	 VALUE;
	union
	{	struct{ t_Val _p[2];	};
		struct{ t_Val x, y;		};
		struct{ t_Val width, height;	};
		struct{ t_Val real,imag;};	///< complex number
	};
	INLFUNC Vec(t_Val x_theta,t_Val y_phi){ x = x_theta; y = y_phi; }

	template<typename t_Val2>
	INLFUNC const Vec& operator =(const Vec<t_Val2, 2>& i){ x = (t_Val)i.x; y = (t_Val)i.y; return *this; }

	template<typename t_Val2>
	INLFUNC const Vec& operator =(const Vec<t_Val2, 1>& i){ x=y=(t_Val)i.x; return *this; }
	template<typename t_Val2>
	INLFUNC const Vec& operator =(const Vec<t_Val2, 3>& i){ *this = i.v2(); return *this; }
	template<typename t_Val2>
	INLFUNC const Vec& operator =(const Vec<t_Val2, 4>& i){ x=(t_Val)i.GetBrightness(); y=(t_Val)i.a; return *this; }

	INLFUNC Vec<t_Val, 1>& v1() { return (Vec<t_Val, 1>&)*this; }
	INLFUNC const Vec<t_Val, 1>& v1() const { return (Vec<t_Val, 1>&)*this; }
	INLFUNC Vec<t_Val, 2>& v2() { return (Vec<t_Val, 2>&)*this; }
	INLFUNC const Vec<t_Val, 2>& v2() const { return (Vec<t_Val, 2>&)*this; }
	
	INLFUNC t_Val GetBrightness()const { return (x+y)/2; }
	template<typename t_Val2>
	INLFUNC void CartesianToSpherical(const Vec<t_Val2, 3>& s) // this = <theta, phi>
	{	y = atan2(s.y, s.x);
		x = atan2(sqrt(s.x*s.x + s.y*s.y), s.z);
	}
	DEF_VEC_FUNC;
	INLFUNC t_Val Min(){ return rt::min(_p[LEN-1], ((Vec<t_Val, LEN-1>&)(*this)).Min()); }
	INLFUNC t_Val Max(){ return rt::max(_p[LEN-1], ((Vec<t_Val, LEN-1>&)(*this)).Max()); }
};


template< typename t_Val >
struct Vec<t_Val, 3>
{	static const int LEN=3;
	typedef t_Val	 VALUE;
	typedef rt::NumericTraits<t_Val>	NumericTraits_Item;
	union
	{	struct{ t_Val _p[3]; };
		struct{ t_Val x,y,z; };
		struct{ t_Val r,g,b; };	///< triple color
		struct{ t_Val h,l,s; };
	};
	INLFUNC Vec(t_Val x_r,t_Val y_g,t_Val z_b){ x = x_r; y = y_g; z = z_b; }

	template<typename t_Val2>
	INLFUNC const Vec& operator =(const Vec<t_Val2, 3>& i){ x = (t_Val)i.x; y = (t_Val)i.y; z = (t_Val)i.z; return *this; }

	template<typename t_Val2>
	INLFUNC const Vec& operator =(const Vec<t_Val2, 1>& i){ x=y=z=(t_Val)i.x; return *this; }
	template<typename t_Val2>
	INLFUNC const Vec& operator =(const Vec<t_Val2, 2>& i){ v2() = i; return *this; }
	template<typename t_Val2>
	INLFUNC const Vec& operator =(const Vec<t_Val2, 4>& i){ *this = i.v3(); return *this; }
	
	INLFUNC Vec<t_Val, 1>& v1() { return (Vec<t_Val, 1>&)*this; }
	INLFUNC const Vec<t_Val, 1>& v1() const { return (Vec<t_Val, 1>&)*this; }
	INLFUNC Vec<t_Val, 2>& v2() { return (Vec<t_Val, 2>&)*this; }
	INLFUNC const Vec<t_Val, 2>& v2() const { return (Vec<t_Val, 2>&)*this; }
	INLFUNC Vec<t_Val, 3>& v3() { return (Vec<t_Val, 3>&)*this; }
	INLFUNC const Vec<t_Val, 3>& v3() const { return (Vec<t_Val, 3>&)*this; }
	
	INLFUNC t_Val GetBrightness() const
	{	if(NumericTraits_Item::IsInteger)
		{ return (t_Val)(((int)(r+g+g+b))>>2); }
		else
		{ return (t_Val)(0.299f*r+0.587f*g+0.114f*b); }
	}
	/**
	 * @brief  a x b -> This
	 * 
	 * @tparam t_Val2 
	 * @tparam t_Val3 
	 * @param in1 
	 * @param in2 
	 * @return INLFUNC 
	 */
	template<typename t_Val2,typename t_Val3>   
	INLFUNC void CrossProduct(const Vec<t_Val2,3>& in1,const Vec<t_Val3,3>& in2)
	{
		x =  in1.y*in2.z - in1.z*in2.y;
		y = -in1.x*in2.z + in1.z*in2.x;
		z =  in1.x*in2.y - in1.y*in2.x;
	}
	/**
	 * @brief (a-org) x (b-org) -> This
	 * 
	 * @tparam t_Val2 
	 * @tparam t_Val3 
	 * @tparam t_Val4 
	 * @param a 
	 * @param b 
	 * @param c 
	 * @return INLFUNC 
	 */
	template<typename t_Val2,typename t_Val3,typename t_Val4>	
	INLFUNC void CrossProduct(const Vec<t_Val2,3>& a,const Vec<t_Val3,3>& b,const Vec<t_Val4,3>& c)
	{
		x =  (a.y-c.y)*(b.z-c.z) - (a.z-c.z)*(b.y-c.y);
		y = -(a.x-c.x)*(b.z-c.z) + (a.z-c.z)*(b.x-c.x);
		z =  (a.x-c.x)*(b.y-c.y) - (a.y-c.y)*(b.x-c.x);
	}

	/**
	 * @brief (a-org) x (b-org) -> This
	 * s = <theta, phi>
	 * @tparam t_Val2 
	 * @param s 
	 * @return INLFUNC 
	 */
	template<typename t_Val2>	
	INLFUNC void SphericalToEuclidean(const Vec<t_Val2, 2>& s) 
	{	x = sin(s.x);
		y = sin(s.y)*x;
		x = cos(s.y)*x;
		z = cos(s.x);
	}
	
	/**
	 * @brief  (a-org) x (b-org) -> This
	 * s = <theta, phi, r>
	 * @tparam t_Val2 
	 * @param s 
	 * @return INLFUNC 
	 */
	template<typename t_Val2>	//
	INLFUNC void SphericalToEuclidean(const Vec<t_Val2, 3>& s) 
	{	x = sin(s.x)*s.z;
		y = sin(s.y)*x;
		x = cos(s.y)*x;
		z = cos(s.x)*s.z;
	}
	template<typename t_Val2>
	INLFUNC void CartesianToSpherical(const Vec<t_Val2, 3>& s) // this = <theta, phi, r>
	{	z = s.x*s.x + s.y*s.y;
		y = atan2(s.y, s.x);
		x = atan2(sqrt(z), s.z);
		z = sqrt(z + s.z*s.z);
	}
	DEF_VEC_FUNC;
	INLFUNC t_Val Min(){ return rt::min(_p[LEN-1], ((Vec<t_Val, LEN-1>&)(*this)).Min()); }
	INLFUNC t_Val Max(){ return rt::max(_p[LEN-1], ((Vec<t_Val, LEN-1>&)(*this)).Max()); }
};

template< typename t_Val >
struct Vec<t_Val, 4>
{	static const int LEN=4;
	typedef t_Val	 VALUE;
	typedef rt::NumericTraits<t_Val>	NumericTraits_Item;
	union
	{	struct{ t_Val _p[4]; };
		struct{ t_Val x,y,z,w; };
		struct{ t_Val r,g,b,a; }; ///< quadruple color
	};
public:
	INLFUNC Vec(t_Val x_r,t_Val y_g,t_Val z_b,t_Val w_a){ r = x_r; g = y_g; b = z_b; a = w_a;}
	INLFUNC Vec(t_Val v,t_Val w_a){ r = v; g = v; b = v; a = w_a;}

	template<typename t_Val2>
	INLFUNC const Vec& operator =(const Vec<t_Val2, 4>& i){ x = (t_Val)i.x; y = (t_Val)i.y; z = (t_Val)i.z; w = (t_Val)i.w; return *this; }

	template<typename t_Val2>
	INLFUNC const Vec& operator =(const Vec<t_Val2, 1>& i){ x=y=z=(t_Val)i.x; return *this; }
	template<typename t_Val2>
	INLFUNC const Vec& operator =(const Vec<t_Val2, 2>& i){ x=y=z=(t_Val)i.x; a=(t_Val)i.y; return *this; }
	template<typename t_Val2>
	INLFUNC const Vec& operator =(const Vec<t_Val2, 3>& i){ v3() = i; return *this; }

	INLFUNC Vec<t_Val, 1>& v1() { return (Vec<t_Val, 1>&)*this; }
	INLFUNC const Vec<t_Val, 1>& v1() const { return (Vec<t_Val, 1>&)*this; }
	INLFUNC Vec<t_Val, 2>& v2() { return (Vec<t_Val, 2>&)*this; }
	INLFUNC const Vec<t_Val, 2>& v2() const { return (Vec<t_Val, 2>&)*this; }
	INLFUNC Vec<t_Val, 3>& v3() { return (Vec<t_Val, 3>&)*this; }
	INLFUNC const Vec<t_Val, 3>& v3() const { return (Vec<t_Val, 3>&)*this; }	
	INLFUNC Vec<t_Val, 4>& v4() { return (Vec<t_Val, 4>&)*this; }
	INLFUNC const Vec<t_Val, 4>& v4() const { return (Vec<t_Val, 4>&)*this; }
	
	INLFUNC t_Val GetBrightness() const{ return v3().GetBrightness(); }

	DEF_VEC_FUNC;
	INLFUNC t_Val Min(){ return rt::min(_p[LEN-1], ((Vec<t_Val, LEN-1>&)(*this)).Min()); }
	INLFUNC t_Val Max(){ return rt::max(_p[LEN-1], ((Vec<t_Val, LEN-1>&)(*this)).Max()); }
};

#undef DEF_VEC_FUNC


/**
 * @brief small vec expression
 * 
 * it is not implemented as template expression as string dose because
 * small vec is a POD. template expression don't produce better preformance neither
 * small memory footprint and sometime even worst when small vec is sized less than 128 bits
 */
#define DEF_VEC_OPS		DEF_VEC_OP(add,+)	\
						DEF_VEC_OP(sub,-)	\
						DEF_VEC_OP(mul,*)	\
						DEF_VEC_OP(div,/)	\

namespace _details
{
template<typename VEC, int INDX = VEC::LEN-1>
struct VecExp
{
#define DEF_VEC_OP(name,op)	static INLFUNC void name(const VEC& a, const VEC& b, VEC& c){ VecExp<VEC,INDX-1>::name(a,b,c); c[INDX] = a[INDX] op b[INDX]; }
	DEF_VEC_OPS
#undef DEF_VEC_OP
};
	template<typename VEC>
	struct VecExp<VEC,-1>
	{
#define DEF_VEC_OP(name,op)	static INLFUNC void name(const VEC& a, const VEC& b, VEC& c){}
		DEF_VEC_OPS
#undef DEF_VEC_OP
	};
} // namespace _details

#define DEF_VEC_OP(name, op)	template<typename t_Val, int chan>	\
								auto operator op (const Vec<t_Val, chan>& a, const Vec<t_Val, chan>& b){ Vec<t_Val, chan> r; _details::VecExp<Vec<t_Val, chan>>::name(a,b,r); return r; } \
								template<typename t_Val, int chan, typename T>	\
								auto operator op (const Vec<t_Val, chan>& a, T b){ Vec<t_Val, chan> r; _details::VecExp<Vec<t_Val, chan>>::name(a,b,r); return r; } \
								template<typename t_Val, int chan>	\
								auto operator op (t_Val a, const Vec<t_Val, chan>& b){ Vec<t_Val, chan> r; _details::VecExp<Vec<t_Val, chan>>::name(a,b,r); return r; }
DEF_VEC_OPS
#undef DEF_VEC_OP

#undef DEF_VEC_OPS

typedef Vec<float, 1> Vec1f;
typedef Vec<float, 2> Vec2f;
typedef Vec<float, 3> Vec3f;
typedef Vec<float, 4> Vec4f;

typedef Vec<double, 1> Vec1d;
typedef Vec<double, 2> Vec2d;
typedef Vec<double, 3> Vec3d;
typedef Vec<double, 4> Vec4d;

typedef Vec<int, 1> Vec1i;
typedef Vec<int, 2> Vec2i;
typedef Vec<int, 3> Vec3i;
typedef Vec<int, 4> Vec4i;

typedef Vec<short, 1> Vec1s;
typedef Vec<short, 2> Vec2s;
typedef Vec<short, 3> Vec3s;
typedef Vec<short, 4> Vec4s;

typedef Vec<UINT, 1> Vec1u;
typedef Vec<UINT, 2> Vec2u;
typedef Vec<UINT, 3> Vec3u;
typedef Vec<UINT, 4> Vec4u;

typedef Vec<WORD, 1> Vec1w;
typedef Vec<WORD, 2> Vec2w;
typedef Vec<WORD, 3> Vec3w;
typedef Vec<WORD, 4> Vec4w;

typedef Vec<BYTE, 1> Vec1b;
typedef Vec<BYTE, 2> Vec2b;
typedef Vec<BYTE, 3> Vec3b;
typedef Vec<BYTE, 4> Vec4b;

typedef Vec<signed char, 1> Vec1c;
typedef Vec<signed char, 2> Vec2c;
typedef Vec<signed char, 3> Vec3c;
typedef Vec<signed char, 4> Vec4c;

} // namespace rt
namespace rt
{
namespace tos
{
template<int chan = 4>
struct Vec:public ::rt::tos::S_<chan>
{	typedef ::rt::tos::S_<chan> _SC;
	template<typename t_Val, int LEN>
	Vec(const rt::Vec<t_Val, LEN>& x)
		:_SC(x)
	{}
};
} // namespace tos


#define CPF_STRING_VEC_CONNECT_OP(T) \
template<int chan> \
FORCEINL _SE<String_Ref, tos::S_<chan> >  operator + (const String_Ref& left, const Vec<T,chan>& right) \
{ return _SE<String_Ref, tos::S_<chan> > ( (left), (right) ); } \
template<int chan> \
FORCEINL _SE<tos::S_<chan>, String_Ref>  operator + (const Vec<T,chan>& left, const String_Ref& right) \
{ return _SE<tos::S_<chan>, String_Ref> ( (left), (right) ); }		\
template<typename t_Left, typename t_Right, int chan> FORCEINL		\
_SE<tos::S_<chan>, _SE<t_Left,t_Right> >							\
operator + (const Vec<T,chan>& p, const _SE<t_Left,t_Right>& x)		\
{ return _SE<tos::S_<chan>, _SE<t_Left,t_Right> >((p),x); }			\
template<typename t_Left, typename t_Right, int chan> FORCEINL		\
_SE<_SE<t_Left,t_Right> , tos::S_<chan>>										\
operator + (const _SE<t_Left,t_Right>& x, const Vec<T,chan>& p)		\
{ return _SE<_SE<t_Left,t_Right>, tos::S_<chan>>(x, (p)); }			\

CPF_STRING_VEC_CONNECT_OP(float)
CPF_STRING_VEC_CONNECT_OP(double)
CPF_STRING_VEC_CONNECT_OP(int)
CPF_STRING_VEC_CONNECT_OP(short)
CPF_STRING_VEC_CONNECT_OP(UINT)
CPF_STRING_VEC_CONNECT_OP(WORD)
CPF_STRING_VEC_CONNECT_OP(BYTE)
CPF_STRING_VEC_CONNECT_OP(signed char)

#undef CPF_STRING_VEC_CONNECT_OP

template<typename ostream, typename t_Val, int LEN>
ostream& operator << (ostream& s, const Vec<t_Val, LEN>& v)
{
	s << '(' << rt::tos::Vec<LEN>(v) << ')';
	return s;
};
} // rt


namespace rt
{

/**
 * @brief small matrix
 * 
 * @tparam t_Val 
 */
template<typename t_Val>
struct Mat4x4;
/**
 * @brief small matrix
 * 
 * @tparam t_Val 
 */
template<typename t_Val>
struct Mat3x3
{
	union{
		t_Val _p[9];
        t_Val m[3][3];
		struct {
		t_Val	m00,	m10,	m20;
		t_Val	m01,	m11,	m21;
		t_Val	m02,	m12,	m22;
 		};
	};
	INLFUNC operator t_Val*(){ return m[0]; }
	INLFUNC operator const t_Val*()const{ return m[0]; }

	INLFUNC rt::Vec<t_Val,3>& operator [](UINT i){ return *((rt::Vec<t_Val,3>*)m[i]); }
	INLFUNC const rt::Vec<t_Val,3>& operator [](UINT i)const{ return *((const rt::Vec<t_Val,3>*)m[i]); }

    INLFUNC Mat3x3() {}
	INLFUNC t_Val & operator () (int x, int y) {return m[y][x];}
	INLFUNC const t_Val & operator () (int x, int y) const { return m[y][x]; }		

	INLFUNC rt::Vec<t_Val,9>& GetVec(){ return *((rt::Vec<t_Val,9>*)&m); }
	INLFUNC const rt::Vec<t_Val,9>& GetVec()const{ return *((const rt::Vec<t_Val,9>*)&m); }

	INLFUNC void Transpose()
	{
		rt::Swap(m01,m10);
		rt::Swap(m02,m20);
		rt::Swap(m21,m12);
	}

    INLFUNC rt::Vec<t_Val,3> Product(const rt::Vec<t_Val,3> &v) const
	{
        rt::Vec<t_Val,3> res;
        res[0] = m00 * v[0] + m01 * v[1] + m02 * v[2];
        res[1] = m10 * v[0] + m11 * v[1] + m12 * v[2];
        res[2] = m20 * v[0] + m21 * v[1] + m22 * v[2];
        return res;
	}

    INLFUNC rt::Vec<t_Val,2> Product(const rt::Vec<t_Val,2> &v) const
	{
        rt::Vec<t_Val,2> res;
        res[0] = m00 * v[0] + m01 * v[1] + m02 * 1;
        res[1] = m10 * v[0] + m11 * v[1] + m12 * 1;
        return res;
	}
	
	INLFUNC void Product(const Mat3x3 &m2,const Mat3x3 &m1)
	{
		m00 = m1.m00*m2.m00 + m1.m10*m2.m01 + m1.m20*m2.m02;
		m01 = m1.m01*m2.m00 + m1.m11*m2.m01 + m1.m21*m2.m02;
		m02 = m1.m02*m2.m00 + m1.m12*m2.m01 + m1.m22*m2.m02;

		m10 = m1.m00*m2.m10 + m1.m10*m2.m11 + m1.m20*m2.m12;
		m11 = m1.m01*m2.m10 + m1.m11*m2.m11 + m1.m21*m2.m12;
		m12 = m1.m02*m2.m10 + m1.m12*m2.m11 + m1.m22*m2.m12;

		m20 = m1.m00*m2.m20 + m1.m10*m2.m21 + m1.m20*m2.m22;
		m21 = m1.m01*m2.m20 + m1.m11*m2.m21 + m1.m21*m2.m22;
		m22 = m1.m02*m2.m20 + m1.m12*m2.m21 + m1.m22*m2.m22;
	}

	INLFUNC void SetMat(const t_Val *p)
	{
		memcpy(m, p, sizeof(m));
	}
	
	//INLFUNC void Transform(Vec<t_Val,3> &out,const Vec<t_Val,3> &in) const
	//{
	//	out.x = in.x*m00+in.y*m01+in.z*m02;
	//	out.y = in.x*m10+in.y*m11+in.z*m12;
	//	out.z = in.x*m20+in.y*m21+in.z*m22;
	//}

	INLFUNC void SetIdentity()
	{
		m00 = m11 = m22 = 1.0f;
		m01 = m02 = m10 = m12 = m20 = m21 = 0.0f;
	};

	//INLFUNC void SetScale(t_Val x,t_Val y,t_Val z)
	//{
	//	m00 = x;
	//	m11 = y;
	//	m22 = z;
	//	m01 = m02 = m10 = m12 = m20 = m21 = 0.0f;	
	//};

	//template<typename T>
	//INLFUNC void SetRotate(t_Val angle,Vec3<T> axis)
	//{
	//	float s = sin(angle);
	//	float c = cos(angle);

	//	m00 = (1-c)*axis.x*axis.x + c;			m01 = (1-c)*axis.x*axis.y + s*axis.z;	m02 = (1-c)*axis.x*axis.z - s*axis.y;
	//	m10 = (1-c)*axis.x*axis.y-s*axis.z;		m11 = (1-c)*axis.y*axis.y + c;			m12 = (1-c)*axis.y*axis.z + s*axis.x;
	//	m20 = (1-c)*axis.x*axis.z + s*axis.y;	m21 = (1-c)*axis.y*axis.z - s*axis.x;	m22 = (1-c)*axis.z*axis.z + c;
	//}

	//INLFUNC void SetRotate(t_Val Theta,t_Val Phi)
	//{
	//	Mat3x3<t_Val>	m1,m2;
	//	m1.SetRotate(Theta,Vec<t_Val,3>(0,1,0));
	//	m2.SetRotate(Phi,Vec<t_Val,3>(0,0,1));

	//	Product(m1,m2);
	//}

    template<class t_Mat>
    Mat3x3(const t_Mat &m)
    {
        m00 = (t_Val)m(0, 0);
        m01 = (t_Val)m(0, 1);
        m02 = (t_Val)m(0, 2);
        m10 = (t_Val)m(1, 0);
        m11 = (t_Val)m(1, 1);
        m12 = (t_Val)m(1, 2);
        m20 = (t_Val)m(2, 0);
        m21 = (t_Val)m(2, 1);
        m22 = (t_Val)m(2, 2);
    }

	template<class t_Mat>
	INLFUNC const Mat3x3<t_Val> & operator = (const t_Mat &m)
	{
        m00 = (t_Val)m(0, 0);
        m01 = (t_Val)m(0, 1);
        m02 = (t_Val)m(0, 2);
        m10 = (t_Val)m(1, 0);
        m11 = (t_Val)m(1, 1);
        m12 = (t_Val)m(1, 2);
        m20 = (t_Val)m(2, 0);
        m21 = (t_Val)m(2, 1);
        m22 = (t_Val)m(2, 2);

		return *this;
	}

	template<class t_Mat>
	INLFUNC const Mat3x3<t_Val> & operator += (const t_Mat &m)
	{
        m00 += (t_Val)m(0, 0);
        m01 += (t_Val)m(0, 1);
        m02 += (t_Val)m(0, 2);
        m10 += (t_Val)m(1, 0);
        m11 += (t_Val)m(1, 1);
        m12 += (t_Val)m(1, 2);
        m20 += (t_Val)m(2, 0);
        m21 += (t_Val)m(2, 1);
        m22 += (t_Val)m(2, 2);

		return *this;
	}

	INLFUNC void Multiply(t_Val x)
	{
        m00 *= x; m01 *= x; m02 *= x;
        m10 *= x; m11 *= x; m12 *= x;
        m20 *= x; m21 *= x; m22 *= x;
	};


	/**
	 * @brief Add by Yanxiang, 2010,10
	 */
	INLFUNC t_Val Determinant()
	{
		t_Val ret = 0;
		ret += m00 * (m11 * m22 - m12 * m21);
		ret += -m01 * (m10 * m22 - m12 * m20);
		ret += m02 * (m10 * m21 - m11 * m20);
		return ret;
	}

	INLFUNC bool Inverse(Mat3x3<t_Val>& inverse) const	
	{	
		inverse._p[0] = _p[4]*_p[8] - _p[5]*_p[7];
		inverse._p[1] = _p[2]*_p[7] - _p[1]*_p[8];
		inverse._p[2] = _p[1]*_p[5] - _p[2]*_p[4];
		inverse._p[3] = _p[5]*_p[6] - _p[3]*_p[8];
		inverse._p[4] = _p[0]*_p[8] - _p[2]*_p[6];
		inverse._p[5] = _p[2]*_p[3] - _p[0]*_p[5];
		inverse._p[6] = _p[3]*_p[7] - _p[4]*_p[6];
		inverse._p[7] = _p[1]*_p[6] - _p[0]*_p[7];
		inverse._p[8] = _p[0]*_p[4] - _p[1]*_p[3];

		t_Val det = _p[0]*inverse._p[0] + _p[1]*inverse._p[3] +	_p[2]*inverse._p[6];

		if (det <= rt::TypeTraits<t_Val>::Epsilon() && det >= -rt::TypeTraits<t_Val>::Epsilon())
		{	rt::Zero(inverse);
			return false;
		}

		t_Val invDet = 1/det;
		inverse._p[0] *= invDet;
		inverse._p[1] *= invDet;
		inverse._p[2] *= invDet;
		inverse._p[3] *= invDet;
		inverse._p[4] *= invDet;
		inverse._p[5] *= invDet;
		inverse._p[6] *= invDet;
		inverse._p[7] *= invDet;
		inverse._p[8] *= invDet;

		return true;
	}
};

template<typename t_Val>
struct Mat4x4
{	
	union{
		t_Val m[4][4];
		struct {
		t_Val	m00,	m10,	m20,	m30;
		t_Val	m01,	m11,	m21,	m31;
		t_Val	m02,	m12,	m22,	m32;
		t_Val	m03,	m13,	m23,	m33;
		};
	};
	INLFUNC operator t_Val*(){ return m[0]; }
	INLFUNC operator const t_Val*()const{ return m[0]; }

	INLFUNC rt::Vec<t_Val,4>& operator [](UINT i){ return *((rt::Vec<t_Val,4>*)m[i]); }
	INLFUNC const rt::Vec<t_Val,4>& operator [](UINT i)const{ return *((const rt::Vec<t_Val,4>*)m[i]); }

	INLFUNC Mat4x4(){ }
	INLFUNC Mat4x4(const t_Val * p ) { SetMat(p); }
	INLFUNC t_Val & operator () (int x, int y) {return m[y][x];}
	INLFUNC const t_Val & operator () (int x, int y) const {return m[y][x]; }
	INLFUNC void Random()
	{	m00 = rand()*rt::TypeTraits<t_Val>::UnitVal()/(t_Val)RAND_MAX;
		m01 = rand()*rt::TypeTraits<t_Val>::UnitVal()/(t_Val)RAND_MAX;
		m02 = rand()*rt::TypeTraits<t_Val>::UnitVal()/(t_Val)RAND_MAX;
		m03 = rand()*rt::TypeTraits<t_Val>::UnitVal()/(t_Val)RAND_MAX;
		m10 = rand()*rt::TypeTraits<t_Val>::UnitVal()/(t_Val)RAND_MAX;
		m11 = rand()*rt::TypeTraits<t_Val>::UnitVal()/(t_Val)RAND_MAX;
		m12 = rand()*rt::TypeTraits<t_Val>::UnitVal()/(t_Val)RAND_MAX;
		m13 = rand()*rt::TypeTraits<t_Val>::UnitVal()/(t_Val)RAND_MAX;
		m20 = rand()*rt::TypeTraits<t_Val>::UnitVal()/(t_Val)RAND_MAX;
		m21 = rand()*rt::TypeTraits<t_Val>::UnitVal()/(t_Val)RAND_MAX;
		m22 = rand()*rt::TypeTraits<t_Val>::UnitVal()/(t_Val)RAND_MAX;
		m23 = rand()*rt::TypeTraits<t_Val>::UnitVal()/(t_Val)RAND_MAX;
		m30 = rand()*rt::TypeTraits<t_Val>::UnitVal()/(t_Val)RAND_MAX;
		m31 = rand()*rt::TypeTraits<t_Val>::UnitVal()/(t_Val)RAND_MAX;
		m32 = rand()*rt::TypeTraits<t_Val>::UnitVal()/(t_Val)RAND_MAX;
		m33 = rand()*rt::TypeTraits<t_Val>::UnitVal()/(t_Val)RAND_MAX;
	}

	INLFUNC rt::Vec<t_Val,16>& GetVec(){ return *((rt::Vec<t_Val,16>*)&m); }
	INLFUNC const rt::Vec<t_Val,16>& GetVec()const{ return *((const rt::Vec<t_Val,16>*)&m); }

    template<typename T>
    INLFUNC Mat4x4(const Mat3x3<T> & in)
    {
		m00 = (t_Val)in.m00;
		m01 = (t_Val)in.m01;
		m02 = (t_Val)in.m02;
				 
		m10 = (t_Val)in.m10;
		m11 = (t_Val)in.m11;
		m12 = (t_Val)in.m12;
				 
		m20 = (t_Val)in.m20;
		m21 = (t_Val)in.m21;
		m22 = (t_Val)in.m22;

        m03 = m13 = m23 = m30 = m31 = m32 = (t_Val)0.0;
        m33 = (t_Val)1.0;
    }

	template<typename T>
	INLFUNC const Mat4x4<t_Val> & operator = (const Mat3x3<T> & in)
	{
		m00 = (t_Val)in.m00;
		m01 = (t_Val)in.m01;
		m02 = (t_Val)in.m02;
				 
		m10 = (t_Val)in.m10;
		m11 = (t_Val)in.m11;
		m12 = (t_Val)in.m12;
				 
		m20 = (t_Val)in.m20;
		m21 = (t_Val)in.m21;
		m22 = (t_Val)in.m22;

        m03 = m13 = m23 = m30 = m31 = m32 = (t_Val)0.0;
        m33 = (t_Val)1.0;

		return *this;
	}

    template<class t_Mat>
    Mat4x4(const t_Mat &m)
    {
		m00 = (t_Val)m(0, 0);
		m01 = (t_Val)m(0, 1);
		m02 = (t_Val)m(0, 2);
		m03 = (t_Val)m(0, 3);
				 
		m10 = (t_Val)m(1, 0);
		m11 = (t_Val)m(1, 1);
		m12 = (t_Val)m(1, 2);
		m13 = (t_Val)m(1, 3);

		m20 = (t_Val)m(2, 0);
		m21 = (t_Val)m(2, 1);
		m22 = (t_Val)m(2, 2);
		m23 = (t_Val)m(2, 3);

		m30 = (t_Val)m(3, 0);
		m31 = (t_Val)m(3, 1);
		m32 = (t_Val)m(3, 2);
		m33 = (t_Val)m(3, 3);
    }
    
    template<class t_Mat>
	INLFUNC const Mat4x4<t_Val> & operator = (const t_Mat& m)
	{
		m00 = (t_Val)m(0, 0);
		m01 = (t_Val)m(0, 1);
		m02 = (t_Val)m(0, 2);
		m03 = (t_Val)m(0, 3);
				 
		m10 = (t_Val)m(1, 0);
		m11 = (t_Val)m(1, 1);
		m12 = (t_Val)m(1, 2);
		m13 = (t_Val)m(1, 3);

		m20 = (t_Val)m(2, 0);
		m21 = (t_Val)m(2, 1);
		m22 = (t_Val)m(2, 2);
		m23 = (t_Val)m(2, 3);

		m30 = (t_Val)m(3, 0);
		m31 = (t_Val)m(3, 1);
		m32 = (t_Val)m(3, 2);
		m33 = (t_Val)m(3, 3);

		return *this;
	}

    template<class t_Mat>
	INLFUNC const Mat4x4<t_Val> & operator += (const t_Mat& m)
	{
		m00 += (t_Val)m(0, 0);
		m01 += (t_Val)m(0, 1);
		m02 += (t_Val)m(0, 2);
		m03 += (t_Val)m(0, 3);
				 
		m10 += (t_Val)m(1, 0);
		m11 += (t_Val)m(1, 1);
		m12 += (t_Val)m(1, 2);
		m13 += (t_Val)m(1, 3);

		m20 += (t_Val)m(2, 0);
		m21 += (t_Val)m(2, 1);
		m22 += (t_Val)m(2, 2);
		m23 += (t_Val)m(2, 3);

		m30 += (t_Val)m(3, 0);
		m31 += (t_Val)m(3, 1);
		m32 += (t_Val)m(3, 2);
		m33 += (t_Val)m(3, 3);

		return *this;
	}

	// Transformation
	//
	INLFUNC void SetIdentity()
	{
		m00 = m11 = m22 = m33 = 1.0f;
		m01 = m02 = m03 = m10 = m12 = m13 = m20 = m21 = m23 = m30 = m31 = m32 = 0.0f;
	};

	INLFUNC void Zero()
	{
		memset(m, 0, sizeof(m));
	}

	//INLFUNC void Transform(const Vec<t_Val,4> &in,Vec<t_Val,4> &out) const
	//{
	//	out.x = in.x*m00+in.y*m01+in.z*m02+in.w*m03;
	//	out.y = in.x*m10+in.y*m11+in.z*m12+in.w*m13;
	//	out.z = in.x*m20+in.y*m21+in.z*m22+in.w*m23;
	//	out.w = in.x*m30+in.y*m31+in.z*m32+in.w*m33;
	//}

	//INLFUNC void Transform(const Vec<t_Val,3> &in,Vec<t_Val,3> &out) const
	//{
	//	out.x = in.x*m00+in.y*m01+in.z*m02+m03;
	//	out.y = in.x*m10+in.y*m11+in.z*m12+m13;
	//	out.z = in.x*m20+in.y*m21+in.z*m22+m23;
	//}

 //   INLFUNC void TransformHomoCoordDir(Vec<t_Val,3> &out,const Vec<t_Val,3> &in) const
 //   {
 //       Vec<t_Val,4> in4 = Vec<t_Val,4> (in.x,in.y,in.z,0.0f);
 //       Vec<t_Val,4> out4;
 //       Transform(out4,in4);
 //       out.x = out4.x/out4.w;
 //       out.y = out4.y/out4.w;
 //       out.z = out4.z/out4.w;
 //   }
 //   INLFUNC void TransformHomoCoordPos(Vec<t_Val,3> &out,const Vec<t_Val,3> &in) const
 //   {
 //       Vec<t_Val,4> in4 = Vec<t_Val,4> (in.x,in.y,in.z,1.0f);
 //       Vec<t_Val,4> out4;
 //       Transform(out4,in4);
 //       out.x = out4.x/out4.w;
 //       out.y = out4.y/out4.w;
 //       out.z = out4.z/out4.w;
 //   }
 //   INLFUNC void TransformTranspose(Vec<t_Val,3> &out,const Vec<t_Val,3> &in) const
 //   {
 //       out.x = in.x*m00+in.y*m10+in.z*m20;
 //       out.y = in.x*m01+in.y*m11+in.z*m21;
 //       out.z = in.x*m02+in.y*m12+in.z*m22;
 //   }    
	INLFUNC void SetMat(const t_Val *p)
	{
		memcpy(m, p, sizeof(m));
	}

    INLFUNC rt::Vec<t_Val,4> Product(const rt::Vec<t_Val,4> &v) const
	{
        rt::Vec<t_Val,4> res;
        res[0] = m00 * v[0] + m01 * v[1] + m02 * v[2] + m03 * v[3];
        res[1] = m10 * v[0] + m11 * v[1] + m12 * v[2] + m13 * v[3];
        res[2] = m20 * v[0] + m21 * v[1] + m22 * v[2] + m23 * v[3];
        res[3] = m30 * v[0] + m31 * v[1] + m32 * v[2] + m33 * v[3];
        return res;
	}

    INLFUNC rt::Vec<t_Val,3> Product(const rt::Vec<t_Val,3> &v) const
	{
        rt::Vec<t_Val,3> res;
        res[0] = m00 * v[0] + m01 * v[1] + m02 * v[2] + m03;
        res[1] = m10 * v[0] + m11 * v[1] + m12 * v[2] + m13;
        res[2] = m20 * v[0] + m21 * v[1] + m22 * v[2] + m23;
        return res;
	}

	INLFUNC void Product(const Mat4x4 &m2,const Mat4x4 &m1)
	{
		m00 = m1.m00*m2.m00 + m1.m10*m2.m01 + m1.m20*m2.m02 + m1.m30*m2.m03;
		m01 = m1.m01*m2.m00 + m1.m11*m2.m01 + m1.m21*m2.m02 + m1.m31*m2.m03;
		m02 = m1.m02*m2.m00 + m1.m12*m2.m01 + m1.m22*m2.m02 + m1.m32*m2.m03;
		m03 = m1.m03*m2.m00 + m1.m13*m2.m01 + m1.m23*m2.m02 + m1.m33*m2.m03;
														   
		m10 = m1.m00*m2.m10 + m1.m10*m2.m11 + m1.m20*m2.m12 + m1.m30*m2.m13;
		m11 = m1.m01*m2.m10 + m1.m11*m2.m11 + m1.m21*m2.m12 + m1.m31*m2.m13;
		m12 = m1.m02*m2.m10 + m1.m12*m2.m11 + m1.m22*m2.m12 + m1.m32*m2.m13;
		m13 = m1.m03*m2.m10 + m1.m13*m2.m11 + m1.m23*m2.m12 + m1.m33*m2.m13;
														   
		m20 = m1.m00*m2.m20 + m1.m10*m2.m21 + m1.m20*m2.m22 + m1.m30*m2.m23;
		m21 = m1.m01*m2.m20 + m1.m11*m2.m21 + m1.m21*m2.m22 + m1.m31*m2.m23;
		m22 = m1.m02*m2.m20 + m1.m12*m2.m21 + m1.m22*m2.m22 + m1.m32*m2.m23;
		m23 = m1.m03*m2.m20 + m1.m13*m2.m21 + m1.m23*m2.m22 + m1.m33*m2.m23;

		m30 = m1.m00*m2.m30 + m1.m10*m2.m31 + m1.m20*m2.m32 + m1.m30*m2.m33;
		m31 = m1.m01*m2.m30 + m1.m11*m2.m31 + m1.m21*m2.m32 + m1.m31*m2.m33;
		m32 = m1.m02*m2.m30 + m1.m12*m2.m31 + m1.m22*m2.m32 + m1.m32*m2.m33;
		m33 = m1.m03*m2.m30 + m1.m13*m2.m31 + m1.m23*m2.m32 + m1.m33*m2.m33;
	}

	INLFUNC void Transpose ()
	{
		rt::Swap(m01 ,m10);
		rt::Swap(m02 ,m20);
		rt::Swap(m03 ,m30);
		rt::Swap(m12 ,m21);
		rt::Swap(m13 ,m31);
		rt::Swap(m23 ,m32);
	}

	INLFUNC void Multiply(t_Val x)
	{
        m00 *= x; m01 *= x; m02 *= x; m03 *= x;
        m10 *= x; m11 *= x; m12 *= x; m13 *= x;
        m20 *= x; m21 *= x; m22 *= x; m23 *= x;
        m30 *= x; m31 *= x; m32 *= x; m33 *= x;
	};

	/**
	 * @brief algorithm from http://www.geometrictools.com//LibFoundation/Mathematics/Wm4Matrix4.inl
	 * 
	 * @param kInv 
	 * @return INLFUNC 
	 */
	INLFUNC void Inverse(Mat4x4<t_Val>& kInv) const
	{
		t_Val fA0 = m00*m11 - m01*m10;
		t_Val fA1 = m00*m12 - m02*m10;
		t_Val fA2 = m00*m13 - m03*m10;
		t_Val fA3 = m01*m12 - m02*m11;
		t_Val fA4 = m01*m13 - m03*m11;
		t_Val fA5 = m02*m13 - m03*m12;
		t_Val fB0 = m20*m31 - m21*m30;
		t_Val fB1 = m20*m32 - m22*m30;
		t_Val fB2 = m20*m33 - m23*m30;
		t_Val fB3 = m21*m32 - m22*m31;
		t_Val fB4 = m21*m33 - m23*m31;
		t_Val fB5 = m22*m33 - m23*m32;

		t_Val fDet = fA0*fB5-fA1*fB4+fA2*fB3+fA3*fB2-fA4*fB1+fA5*fB0;
		if(fDet <= rt::TypeTraits<t_Val>::Epsilon() && fDet >= -rt::TypeTraits<t_Val>::Epsilon())
		{	kInv.Zero();
			return;
		}

		kInv.m00 =	+ m11*fB5 - m12*fB4 + m13*fB3;
		kInv.m10 =	- m10*fB5 + m12*fB2 - m13*fB1;
		kInv.m20 =	+ m10*fB4 - m11*fB2 + m13*fB0;
		kInv.m30 =	- m10*fB3 + m11*fB1 - m12*fB0;
		kInv.m01 =	- m01*fB5 + m02*fB4 - m03*fB3;
		kInv.m11 =	+ m00*fB5 - m02*fB2 + m03*fB1;
		kInv.m21 =	- m00*fB4 + m01*fB2 - m03*fB0;
		kInv.m31 =	+ m00*fB3 - m01*fB1 + m02*fB0;
		kInv.m02 =	+ m31*fA5 - m32*fA4 + m33*fA3;
		kInv.m12 =	- m30*fA5 + m32*fA2 - m33*fA1;
		kInv.m22 =	+ m30*fA4 - m31*fA2 + m33*fA0;
		kInv.m32 =	- m30*fA3 + m31*fA1 - m32*fA0;
		kInv.m03 =	- m21*fA5 + m22*fA4 - m23*fA3;
		kInv.m13 =	+ m20*fA5 - m22*fA2 + m23*fA1;
		kInv.m23 =	- m20*fA4 + m21*fA2 - m23*fA0;
		kInv.m33 =	+ m20*fA3 - m21*fA1 + m22*fA0;

		t_Val fInvDet = ((t_Val)1.0)/fDet;
		kInv.m00 *= fInvDet;
		kInv.m01 *= fInvDet;
		kInv.m02 *= fInvDet;
		kInv.m03 *= fInvDet;
		kInv.m10 *= fInvDet;
		kInv.m11 *= fInvDet;
		kInv.m12 *= fInvDet;
		kInv.m13 *= fInvDet;
		kInv.m20 *= fInvDet;
		kInv.m21 *= fInvDet;
		kInv.m22 *= fInvDet;
		kInv.m23 *= fInvDet;
		kInv.m30 *= fInvDet;
		kInv.m31 *= fInvDet;
		kInv.m32 *= fInvDet;
		kInv.m33 *= fInvDet;
	};


	//INLFUNC void SetRotation(t_Val Theta,t_Val Phi)
	//{
	//	float sp = sin(Phi);
	//	float cp = cos(Phi);
	//	float st = sin(Theta);
	//	float ct = cos(Theta);

	//	float sp2 = sp*sp;
	//	float cp2 = 1-sp2;

	//	m00 = ct;
	//	m01 = sp;

	//	m00 = cp*ct;
	//	m01 = sp*(ct+sp2+(1-ct)*cp2-ct*sp2);
	//	m02 = -cp*st;

	//	m10 = -ct*sp;
	//	m11 = cp*(ct+sp2+(1-ct)*cp2-ct*sp2);
	//	m12 = sp*st;

	//	m20 = sp2*st+cp2*(sp-ct*sp+st);
	//	m21 = sp2*cp*(1-ct);
	//	m22 = ct;

	//	m03 = m13 = m23 = m30 = m31 = m32 = 0;
	//	m33 = 1;
	//}

	//INLFUNC void SetRotate(t_Val Theta,t_Val Phi)
	//{
	//	Mat3x3<t_Val>	m1,m2,q;
	//	m1.SetRotate(Theta,Vec<t_Val,3>(0,1,0));

	//	m2.SetRotate(Phi,Vec<t_Val,3>(0,0,1));

	//	q.Product(m1,m2);

	//	m00 = q.m00;
	//	m01 = q.m01;
	//	m02 = q.m02;
	//			
	//	m10 = q.m10;
	//	m11 = q.m11;
	//	m12 = q.m12;
	//			
	//	m20 = q.m20;
	//	m21 = q.m21;
	//	m22 = q.m22;

	//	m03 = m13 = m23 = m30 = m31 = m32 = 0;
	//	m33 = 1;
	//}

	//INLFUNC void SetColumnVec3(int i,const Vec<t_Val,3> &v)
	//{
	//	ASSERT(i>=0&&i<4);
	//	m[i][0] = v[0];
	//	m[i][1] = v[1];
	//	m[i][2] = v[2];
	//}
	//INLFUNC void SetRowVec3(int i,const Vec<t_Val,3> &v) const
	//{
	//	ASSERT(i>=0&&i<4);
	//	m[0][i] = v[0];
	//	m[1][i] = v[1];
	//	m[2][i] = v[2];
	//}

 //   INLFUNC Vec<t_Val,3> GetColumnVec3(int i) const
 //   {
 //       ASSERT(i>=0&&i<4);
 //       return Vec<t_Val,3>(m[i][0],m[i][1],m[i][2]);
 //   }
 //   INLFUNC Vec<t_Val,3> GetRowVec3(int i) const
 //   {
 //       ASSERT(i>=0&&i<4);
 //       return Vec<t_Val,3> (m[0][i],m[1][i],m[2][i]);
 //   }
 //   INLFUNC Vec<t_Val,4> GetColumn(int i) const
 //   {
 //       ASSERT(i>=0&&i<4);
 //       return Vec<t_Val,4>(m[i][0],m[i][1],m[i][2],m[i][3]);
 //   }
 //   INLFUNC Vec<t_Val,4> GetRow(int i) const
 //   {
 //       ASSERT(i>=0&&i<4);
 //       return Vec<t_Val,4>(m[0][i],m[1][i],m[2][i],m[3][i]);
 //   }
};

typedef Mat3x3<float> Mat3x3f;
typedef Mat4x4<float> Mat4x4f;
typedef Mat3x3<double> Mat3x3d;
typedef Mat4x4<double> Mat4x4d;

template<class t_Ostream, typename t_Ele>
t_Ostream& operator<<(t_Ostream& Ostream, const Mat3x3<t_Ele> & vec)
{	Ostream<<*((rt::Vec<t_Ele,3>*)&vec.m00)<<'\n'
		   <<*((rt::Vec<t_Ele,3>*)&vec.m01)<<'\n'
		   <<*((rt::Vec<t_Ele,3>*)&vec.m02);
	return Ostream;
}
template<class t_Ostream, typename t_Ele>
t_Ostream& operator<<(t_Ostream& Ostream, const Mat4x4<t_Ele> & vec)
{	Ostream<<*((rt::Vec<t_Ele,3>*)&vec.m00)<<'\n'
		   <<*((rt::Vec<t_Ele,3>*)&vec.m01)<<'\n'
		   <<*((rt::Vec<t_Ele,3>*)&vec.m02)<<'\n'
		   <<*((rt::Vec<t_Ele,3>*)&vec.m03);
	return Ostream;
}
} // namespace rt

//////////////////////////////////////////////////////////
// Quaternion
namespace rt
{

template <typename t_Val, typename t_Comp = double>
class Quaternion : public rt::Vec<t_Val, 4>
{
	typedef rt::Vec<t_Val, 4> SC;
public:
    template <typename T>
    INLFUNC void Multiply(const rt::Quaternion<T>& q)
    {
        t_Comp w0, x0, y0, z0;
        w0 = (t_Comp)(SC::w * q.w - (SC::x * q.x + SC::y * q.y + SC::z * q.z));
        x0 = (t_Comp)(SC::w * q.x +  q.w * SC::x + SC::y * q.z - SC::z * q.y);
        y0 = (t_Comp)(SC::w * q.y -  q.z * SC::x + SC::y * q.w + SC::z * q.x); 
        z0 = (t_Comp)(SC::w * q.z +  q.y * SC::x - SC::y * q.x + SC::z * q.w);

        SC::w = (t_Val)w0;
        SC::x = (t_Val)x0;
        SC::y = (t_Val)y0;
        SC::z = (t_Val)z0;
    }

	/**
	 * @brief The matrix m is assumed to be already normalized.
	 * 
	 * @tparam t_Mat 
	 * @param m 
	 * @return INLFUNC 
	 */
    template <class t_Mat>
    INLFUNC void ImportRotationMatrix(const t_Mat &m)
    {
        rt::Mat3x3<t_Comp> mat(m);

#ifdef PLATFORM_DEBUG_BUILD
        rt::Vec<t_Comp,3> v;
        t_Comp L;
        
        v.x = mat(0, 0); v.y = mat(0, 1); v.z = mat(0, 2);
        L = (t_Comp)v.L2NormSqr();
        ASSERT( (t_Val)fabs( L - 1.0 ) < rt::TypeTraits<t_Val>::Epsilon() );

        v.x = mat(1, 0); v.y = mat(1, 1); v.z = mat(1, 2);
        L = (t_Comp)sqrt(v.L2NormSqr());
        ASSERT( (t_Val)fabs( L - 1.0 ) < rt::TypeTraits<t_Val>::Epsilon() );

        v.x = mat(2, 0); v.y = mat(2, 1); v.z = mat(2, 2);
        L = (t_Comp)sqrt(v.L2NormSqr());
        ASSERT( (t_Val)fabs( L - 1.0 ) < rt::TypeTraits<t_Val>::Epsilon() );
#endif

        // Calculation
		t_Comp s;
		t_Comp tr = mat(0, 0) + mat(1, 1) + mat(2, 2);

		// check the diagonal
        if ( tr > rt::TypeTraits<t_Comp>::Epsilon() )
		{
			s = (t_Comp)sqrt(tr + 1);
			SC::w = (t_Val)(0.5 * s);
			s = (t_Comp)(0.5 / s);
			SC::x = (t_Val)((mat(2, 1) - mat(1, 2)) * s);
			SC::y = (t_Val)((mat(0, 2) - mat(2, 0)) * s);
			SC::z = (t_Val)((mat(1, 0) - mat(0, 1)) * s);
		}
		else
		{
			if ( mat(1, 1) - mat(0, 0) > rt::TypeTraits<t_Comp>::Epsilon() &&
                 mat(1, 1) - mat(2, 2) > -rt::TypeTraits<t_Comp>::Epsilon() )
			{
				s = (t_Comp)sqrt((mat(1, 1) - (mat(2, 2) + mat(0, 0))) + 1);

				SC::y = (t_Val)(0.5 * s);
				if ( fabs(s) > rt::TypeTraits<t_Comp>::Epsilon() )
				{
					s = (t_Comp)(0.5 / s);
				}

				SC::w = (t_Val)((mat(0, 2) - mat(2, 0)) * s);
				SC::z = (t_Val)((mat(1, 2) + mat(2, 1)) * s);
				SC::x = (t_Val)((mat(1, 0) + mat(0, 1)) * s);
			}
			else
			{
				if ( (	mat(0, 0) - mat(1, 1) > -rt::TypeTraits<t_Val>::Epsilon() &&
						mat(2, 2) - mat(0, 0) > rt::TypeTraits<t_Val>::Epsilon()
					  ) ||
					  mat(2, 2) - mat(1, 1) > rt::TypeTraits<t_Val>::Epsilon()
				)
				{
					s = (t_Comp)sqrt((mat(2, 2) - (mat(0, 0) + mat(1, 1))) + 1);

					SC::z = (t_Val)(0.5 * s);

					if ( fabs(s) > rt::TypeTraits<t_Comp>::Epsilon() )
					{
						s = (t_Comp)(0.5 / s);
					}

					SC::w = (t_Val)((mat(1, 0) - mat(0, 1)) * s);
					SC::x = (t_Val)((mat(2, 0) + mat(0, 2)) * s);
					SC::y = (t_Val)((mat(2, 1) + mat(1, 2)) * s);
				}
				else
				{
					s = (t_Comp)sqrt((mat(0, 0) - (mat(1, 1) + mat(2, 2))) + 1);

					SC::x = (t_Val)(0.5 * s);

					if ( fabs(s) > rt::TypeTraits<t_Comp>::Epsilon() )
					{
						s = (t_Comp)(0.5 / s);
					}

					SC::w = (t_Val)((mat(2, 1) - mat(1, 2)) * s);
					SC::y = (t_Val)((mat(0, 1) + mat(1, 0)) * s);
					SC::z = (t_Val)((mat(0, 2) + mat(2, 0)) * s);
				}
			}
        }

        SC::Normalize();
    }
	/**
	 * @brief seperate scaling and import the normalized rotation matrix
	 * 
	 * @tparam t_Mat 
	 * @param m 
	 * @param scale 
	 * @return INLFUNC 
	 */
    template <class t_Mat>
    INLFUNC void ImportRotationMatrix(const t_Mat &m, rt::Vec<t_Val,3> &scale) 
    {
        rt::Mat3x3<t_Comp> mat(m);

        // Normalization
        rt::Vec<t_Comp,3> v;
        t_Comp L;
        
        v.x = mat(0, 0); v.y = mat(0, 1); v.z = mat(0, 2);
        L = (t_Comp)sqrt(v.L2NormSqr());
        if ( L > rt::TypeTraits<t_Comp>::Epsilon() )
            scale.x = (t_Val)L;
        else
            scale.x = (t_Val)1.0;
        v.Normalize();
        mat(0, 0) = (t_Comp)v.x; mat(0, 1) = v.y; mat(0, 2) = v.z;

        v.x = mat(1, 0); v.y = mat(1, 1); v.z = mat(1, 2);
        L = (t_Comp)sqrt(v.L2NormSqr());
        if ( L > rt::TypeTraits<t_Comp>::Epsilon() )
            scale.y = (t_Val)L;
        else
            scale.y = (t_Val)1.0;
        v.Normalize();
        mat(1, 0) = v.x; mat(1, 1) = v.y; mat(1, 2) = v.z;

        v.x = mat(2, 0); v.y = mat(2, 1); v.z = mat(2, 2);
        L = (t_Comp)sqrt(v.L2NormSqr());
        if ( L > rt::TypeTraits<t_Comp>::Epsilon() )
            scale.z = (t_Val)L;
        else
            scale.z = (t_Val)1.0;
        v.Normalize();
        mat(2, 0) = v.x; mat(2, 1) = v.y; mat(2, 2) = v.z;

        ImportRotationMatrix(mat);
    }

    template <class t_Mat>
    INLFUNC void ExportRotationMatrix(t_Mat& mat) const
    {
		t_Comp x2 = (SC::x + SC::x);
		t_Comp y2 = (SC::y + SC::y);
        t_Comp z2 = (SC::z + SC::z);

        t_Comp xx2 = SC::x * x2, xy2 = SC::x * y2, xz2 = SC::x * z2;
        t_Comp yy2 = SC::y * y2, yz2 = SC::y * z2, zz2 = SC::z * z2;
        t_Comp wx2 = SC::w * x2, wy2 = SC::w * y2, wz2 = SC::w * z2;

        mat(0, 0) = (t_Val)(1 - yy2 - zz2);
        mat(1, 0) = (t_Val)(xy2 + wz2);
        mat(2, 0) = (t_Val)(xz2 - wy2);
        mat(0, 1) = (t_Val)(xy2 - wz2);
        mat(1, 1) = (t_Val)(1 - xx2 - zz2); 
        mat(2, 1) = (t_Val)(yz2 + wx2);
        mat(0, 2) = (t_Val)(xz2 + wy2);
        mat(1, 2) = (t_Val)(yz2 - wx2);
        mat(2, 2) = (t_Val)(1 - xx2 - yy2);
    }

    template <class t_Mat>
    INLFUNC void ExportRotationMatrix(t_Mat& mat, const rt::Vec<t_Val,3> &scale) const
    {
		t_Comp x2 = (SC::x + SC::x);
		t_Comp y2 = (SC::y + SC::y);
        t_Comp z2 = (SC::z + SC::z);

        t_Comp xx2 = SC::x * x2, xy2 = SC::x * y2, xz2 = SC::x * z2;
        t_Comp yy2 = SC::y * y2, yz2 = SC::y * z2, zz2 = SC::z * z2;
        t_Comp wx2 = SC::w * x2, wy2 = SC::w * y2, wz2 = SC::w * z2;

        mat(0, 0) = (t_Val)(1 - yy2 - zz2) * scale.x;
        mat(1, 0) = (t_Val)(xy2 + wz2) * scale.y;
        mat(2, 0) = (t_Val)(xz2 - wy2) * scale.z;
        mat(0, 1) = (t_Val)(xy2 - wz2) * scale.x;
        mat(1, 1) = (t_Val)(1 - xx2 - zz2) * scale.y; 
        mat(2, 1) = (t_Val)(yz2 + wx2) * scale.z;
        mat(0, 2) = (t_Val)(xz2 + wy2) * scale.x;
        mat(1, 2) = (t_Val)(yz2 - wx2) * scale.y;
        mat(2, 2) = (t_Val)(1 - xx2 - yy2) * scale.z;
    }

	INLFUNC void Interpolate(const Quaternion<t_Val> &lhs, const Quaternion<t_Val> &rhs, const t_Val &t)
	{
        Quaternion<t_Val> aa, bb;

        t_Comp c = lhs.Dot(rhs);
        if ( c > -rt::TypeTraits<t_Comp>::Epsilon() )
        {
		    aa = lhs;
		    bb = rhs;
	    }
        else
        {
		    aa = lhs;
		    bb = rhs;
            bb *= (t_Val)(-1.0);
		    c = -c;
	    }

	    t_Val theta = (t_Val)acos( c );
	    t_Val sinom = (t_Val)sin( theta );

	    if( sinom>rt::TypeTraits<t_Val>::Epsilon() )
        {
            aa *= (t_Val)sin((t_Comp)(1-t)*theta);
            bb *= (t_Val)((t_Comp)sin(t*theta));
	        *this = aa;
            *this += bb;
            *this /= sinom;
			SC::Normalize();
	    }
        else
        {
            aa *= (t_Val)((t_Comp)1.0 - t);
            bb *= (t_Val)t;
            *this = aa;
            *this += bb;
			SC::Normalize();
        }
	}

    INLFUNC void				SetIdentity(){ SC::w = (t_Val)1.0; SC::x = SC::y = SC::z = (t_Val)0.0; }
    INLFUNC const t_Val&		Quat_Scal() const { return SC::w; }
    INLFUNC t_Val&				Quat_Scal(){ return SC::w; }
    INLFUNC const Vec<t_Val,3>&	Quat_Vec() const { return SC::v3(); }
    INLFUNC Vec<t_Val,3>&		Quat_Vec(){ return SC::v3(); }
};

typedef Quaternion<float> Quaternionf;
typedef Quaternion<double> Quaterniond;
/** @}*/
} // namespace rt

#pragma pack()
/** @}*/