#pragma once

/**
 * @file ipp_core.h
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
/** \defgroup ipp ipp
 * @ingroup ext
 *  @{
 */
#include "../../rt/small_math.h"
#include "../../os/kernel.h"
#include "ipp_config.h"

#ifdef PLATFORM_INTEL_IPP_SUPPORT
#include "inc/ipp.h"

/**
 * @brief Helper macro 
 * 
 */
#define IPPVERIFY(x) { auto ret = (x); if(ippStsNoErr==x){}else{ _LOG_ERROR(#x " returns "<<ret); ASSERT(0); }}
#define IPPI_INTER_DEFAULT IPPI_INTER_LINEAR

namespace ipp
{
/** \defgroup ipp_core ipp_core
 * @ingroup ipp
 *  @{
 */
enum _tagAxisOrientation
{
	AxisHorizontal = ippAxsHorizontal,
	AxisVertical = ippAxsVertical,
	AxisBoth = ippAxsBoth
};
/** @}*/
} // namespace ipp

#else // PLATFORM_INTEL_IPP_SUPPORT

#include "inc/ippdefs.h"

typedef unsigned char   Ipp8u;
typedef unsigned short  Ipp16u;
typedef unsigned int    Ipp32u;

typedef signed char		Ipp8s;
typedef signed short	Ipp16s;
typedef signed int		Ipp32s;
typedef float			Ipp32f;
//typedef LONGLONG		Ipp64s;
//typedef ULONGLONG		Ipp64u;
typedef double			Ipp64f;

#endif // PLATFORM_INTEL_IPP_SUPPORT

namespace ipp
{
/** \defgroup ipp_core ipp_core
 * @ingroup ipp
 *  @{
 */
/**
 * @brief IppEnv
 * 
 */
enum _tagIppEnvOption
{
#ifdef PLATFORM_INTEL_IPP_SUPPORT
	DitherMode_None = ippDitherNone,
	DitherMode_FS = ippDitherFS,
	DitherMode_JJN = ippDitherJJN,
	DitherMode_Stucki = ippDitherStucki,
	DitherMode_Bayer = ippDitherBayer,

	BlendMethod_AlphaOver = ippAlphaOver,		///< OVER	α(A)*A+[1-α(A)]*α(B)*B 
	BlendMethod_AlphaIn   = ippAlphaIn,			///< IN	α(A)*A*α(B)
	BlendMethod_AlphaOut  = ippAlphaOut,		///< OUT	α(A)*A*[1-α(B)]
	BlendMethod_AlphaATop = ippAlphaATop,		///< ATOP	α(A)*A*α(B)+[1-α(A)]*α(B)*B 
	BlendMethod_AlphaXor  = ippAlphaXor,		///< XOR	α(A)*A*[1-α(B)]+[1-α(A)]*α(B)*B 
	BlendMethod_AlphaPlus = ippAlphaPlus,		///< PLUS	α(A)*A + α(B)*B
#endif

	RoundMode_Zero = ippRndZero,
	RoundMode_Near = ippRndNear,
	
	HintAlgorithm_Default  = ippAlgHintNone,
	HintAlgorithm_Fast  = ippAlgHintFast,
	HintAlgorithm_Accurate  = ippAlgHintAccurate,

	InterpolationMode_Nearest = IPPI_INTER_NN,
	InterpolationMode_Linear = IPPI_INTER_LINEAR,
	InterpolationMode_Cubic = IPPI_INTER_CUBIC,
	InterpolationMode_Super = IPPI_INTER_SUPER,
	InterpolationMode_SmoothEdge = IPPI_SMOOTH_EDGE,

	IppiOption_Max
};

struct IppiEnvParamItems
{
#ifdef PLATFORM_INTEL_IPP_SUPPORT
	IppiDitherType		DitherMode;
#endif

	IppRoundMode		RoundMode;
	IppHintAlgorithm	HintAlgorithm;
	IppiBorderType		BorderType;
	DWORD				InterpolationMode;
	float				FloatMin;
	float				FloatMax;
	int					ResultBitShift;  ///< return result*2^(-ResultBitShift)
	int					IntegerScaleFactor;

	int					JpegEncodeQuality;
	int					WebpEncodeQuality;
	int					GifEncodeColorCount;
};

class IppiEnvParam: public IppiEnvParamItems
{	
	friend IppiEnvParam * GetEnv();
	static const UINT EnvParamSize = sizeof(IppiEnvParamItems);

protected:
	static IppiEnvParam	g_IppEnv;
	int					m_StackPointer;

public:
	IppiEnvParam();
	void	Push();
	void	Pop();
};
inline IppiEnvParam * GetEnv(){ return &IppiEnvParam::g_IppEnv; }

/** @}*/
} // namespace ipp

namespace ipp
{
/** \defgroup ipp_core ipp_core
 * @ingroup ipp
 *  @{
 */
struct Size:public IppiSize
{
	Size(){}
	Size(const IppiSize&x){ width=x.width; height=x.height;  }
	Size(int w,int h){ width = w; height = h; }
	Size(int s){ width = s; height = s; }
	Size	AddBorder(int border_x,int border_y) const { return Size(width+border_x*2,height+border_y*2); }
	Size	AddBorder(int border) const {	return AddBorder(border,border); }
	Size	ScaleTo(int min_sz) const	///< making the short dimension to min_sz
			{	if(width > height)return Size((int)(width*min_sz/height + 0.5f), min_sz);
				else{ return Size(min_sz, (int)(height*min_sz/width + 0.5f)); }
			}
	Size	ScaleTo(int max_width, int max_height) const	///< making both w <= max_width and h <= max_height
			{	int neww = width*max_height/height;
				if(neww <= max_width){ return Size(neww, max_height); }
				else{ return Size(max_width, height*max_width/width); }
			}
	bool	operator == (const Size& x) const	{ return width == x.width && height == x.height; }
	int		Area() const { return width*height; }
	int		GetShortDimen() const { return rt::min(width, height); }
};

struct Point:public IppiPoint
{
	Point(){}
	Point(int ix,int iy){ x = ix; y = iy; }
	bool	operator == (const Point& q) const { return x == q.x && y == q.y; }
	Point	Translate(int dx, int dy) const { return Point(x+dx, y+dy); }
	Point	Translate(const rt::Vec2i& m) const { return Point(x+m.x, y+m.y); }
};

struct Rect:public IppiRect
{
	Rect(){}
	Rect(int ix,int iy,int w,int h){ x = ix; y = iy; width = w; height = h; }
	Rect(const Point& pt,int w,int h){ x = pt.x; y = pt.y; width = w; height = h; }
	Rect(const Point& pt1,const Point& pt2)
	{	if(pt1.x < pt2.x){ x=pt1.x; width=pt2.x-pt1.x; }
		else{ x=pt2.x; width=pt1.x-pt2.x; }
		if(pt1.y < pt2.y){ y=pt1.y; height=pt2.y-pt1.y; }
		else{ y=pt2.y; height=pt1.y-pt2.y; }
	}
	int				Area() const { return width*height; }
	Point&			Position(){ return *((Point*)this); }
	const Point&	Position() const { return *((Point*)this); }
	bool			IsHit(const Point& p) const { return p.x>=x && p.x<=x+width && p.y>=y && p.y<=y+height; }
	void			BoundingBoxOf(const Rect& rect1, const Rect& rect2)
					{	int xx = rt::min(rect1.x, rect2.x);	int yy = rt::min(rect1.y, rect2.y);
						width = rt::max(rect1.x+rect1.width, rect2.x+rect2.width) - xx;
						height = rt::max(rect1.y+rect1.height, rect2.y+rect2.height) - yy;
						x = xx;
						y = yy;
					}
};

/**
 * @brief Type definitions
 * 
 */
#define IPP_TYPE_EXT(x) typedef x * LP##x; typedef const x * LPC##x;
	IPP_TYPE_EXT(Ipp8u);
	IPP_TYPE_EXT(Ipp8s);
	IPP_TYPE_EXT(Ipp16u);
	IPP_TYPE_EXT(Ipp16s);
	IPP_TYPE_EXT(Ipp32u);
	IPP_TYPE_EXT(Ipp32s);
	IPP_TYPE_EXT(Ipp32f);
	IPP_TYPE_EXT(Ipp64s);
	IPP_TYPE_EXT(Ipp64f);
#undef IPP_TYPE_EXT

inline ULONGLONG crc64(LPCVOID stream, SIZE_T n, ULONGLONG crc_init = 0){ return os::crc64(stream, n, crc_init); }

#ifndef PLATFORM_INTEL_IPP_SUPPORT
inline DWORD crc32c(LPCVOID data, SIZE_T length, DWORD crc_init = 0){ return os::crc32c(data, length, crc_init); }
#else
inline DWORD crc32c(LPCVOID data, SIZE_T length, DWORD crc_init = 0)
{	crc_init = ~crc_init;
	IPPCALL(ippsCRC32C_8u)((const Ipp8u*)data, (UINT)length, (Ipp32u*)&crc_init);
	return ~crc_init;
}
#endif

#ifndef PLATFORM_INTEL_IPP_SUPPORT
inline DWORD crc32(LPCVOID data, SIZE_T length, DWORD crc_init = 0){ return os::crc32(data, length, crc_init); }
#else
inline DWORD crc32(LPCVOID data, SIZE_T length, DWORD crc_init = 0)
{	IPPCALL(ippsSwapBytes_32u_I)((Ipp32u*)&crc_init, 1);
	IPPCALL(ippsCRC32_8u)((const Ipp8u*)data, (UINT)length, (Ipp32u*)&crc_init);
	IPPCALL(ippsSwapBytes_32u_I)((Ipp32u*)&crc_init, 1);
	return crc_init;
}
#endif

/** @}*/
} // namespace ipp
/** @}*/