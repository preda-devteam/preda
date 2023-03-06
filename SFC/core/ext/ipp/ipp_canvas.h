#pragma once
/**
 * @file ipp_canvas.h
 * @author SFC dev team
 * @brief 
 * @version 1.0
 * @date 2021-05-08
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
#include "ipp_image.h"

namespace ipp
{
/** \defgroup ipp_canvas ipp_canvas
 * @ingroup ipp
 *  @{
 */
namespace _details
{
	template<typename t_Value> struct _Value;
	template<> struct _Value<BYTE>
	{	
		static INLFUNC BYTE Bound(){ return 255; }
		static INLFUNC BYTE Saturate(int i){ return (BYTE)(i>255?255:i); }
		static INLFUNC BYTE Clamp(int i){ return (BYTE)(i>255?255:i); }
	};
	template<> struct _Value<float>
	{	
		static INLFUNC float Bound(){ return 1.0f; }
		static INLFUNC float Saturate(float i){ return (i>1.0f?1.0f:i); }
		static INLFUNC float Clamp(float i){ return i<1.0f?(i>0.0f?i:0.0f):1.0f; }
	};

	template<typename t_Value,int ChannelDst, int ChannelSrc>
	struct _Pixel
	{	static INLFUNC void Set(rt::Vec<t_Value,ChannelDst>& dst, const rt::Vec<t_Value,ChannelSrc>& src)
		{	dst = src;
		}
	};
	template<> struct _Pixel<BYTE, 4, 4>
	{	static INLFUNC void Set(rt::Vec<BYTE,4>& dst, const rt::Vec<BYTE,4>& src)
		{	
			int one_minus_dst = 255 - dst.a;
			int one_minus_src = 255 - src.a;

			dst.r = (BYTE)(255*src.r*src.a + dst.r*one_minus_src*dst.a)/(255*src.a + one_minus_src*dst.a);
			dst.g = (BYTE)(255*src.g*src.a + dst.g*one_minus_src*dst.a)/(255*src.a + one_minus_src*dst.a);
			dst.b = (BYTE)(255*src.b*src.a + dst.b*one_minus_src*dst.a)/(255*src.a + one_minus_src*dst.a);
			dst.a = (BYTE)(255 - one_minus_dst*one_minus_src/255);
		}
		static INLFUNC void Set(rt::Vec<BYTE,4>& dst, const rt::Vec<BYTE,4>& src, float additional_src_alpha)
		{	
			int src_a = (int)(src.a*additional_src_alpha + 0.5f);
			int one_minus_dst = 255 - dst.a;
			int one_minus_src = 255 - src_a;

			dst.r = (BYTE)(255*src.r*src_a + dst.r*one_minus_src*dst.a)/(255*src_a + one_minus_src*dst.a);
			dst.g = (BYTE)(255*src.g*src_a + dst.g*one_minus_src*dst.a)/(255*src_a + one_minus_src*dst.a);
			dst.b = (BYTE)(255*src.b*src_a + dst.b*one_minus_src*dst.a)/(255*src_a + one_minus_src*dst.a);
			dst.a = (BYTE)(255 - one_minus_dst*one_minus_src/255);
		}
	};
	template<> struct _Pixel<float, 4, 4>
	{	static INLFUNC void Set(rt::Vec<float,4>& dst, const rt::Vec<float,4>& src)
		{	
			float dst_a = _Value<float>::Clamp(dst.a);
			float src_a = _Value<float>::Clamp(src.a);
			float one_minus_dst = 1.0f - dst_a;
			float one_minus_src = 1.0f - src_a;

			dst.r = (src.r*src_a + dst.r*one_minus_src*dst_a)/(src_a + one_minus_src*dst_a);
			dst.g = (src.g*src_a + dst.g*one_minus_src*dst_a)/(src_a + one_minus_src*dst_a);
			dst.b = (src.b*src_a + dst.b*one_minus_src*dst_a)/(src_a + one_minus_src*dst_a);
			dst.a = (1.0f - one_minus_dst*one_minus_src);
		}
		static INLFUNC void Set(rt::Vec<float,4>& dst, const rt::Vec<float,4>& src, float additional_src_alpha)
		{	
			float dst_a = _Value<float>::Clamp(dst.a);
			float src_a = _Value<float>::Clamp(src.a*additional_src_alpha);
			float one_minus_dst = 1.0f - dst_a;
			float one_minus_src = 1.0f - src_a;

			dst.r = (src.r*src_a + dst.r*one_minus_src*dst_a)/(src_a + one_minus_src*dst_a);
			dst.g = (src.g*src_a + dst.g*one_minus_src*dst_a)/(src_a + one_minus_src*dst_a);
			dst.b = (src.b*src_a + dst.b*one_minus_src*dst_a)/(src_a + one_minus_src*dst_a);
			dst.a = (1.0f - one_minus_dst*one_minus_src);
		}
	};
	template<> struct _Pixel<BYTE, 3, 4>
	{	static INLFUNC void Set(rt::Vec<BYTE,3>& dst, const rt::Vec<BYTE,4>& src)
		{	
			int one_minus_src = 255 - src.a;

			dst.r = (BYTE)((src.r*src.a + dst.r*one_minus_src)/255);
			dst.g = (BYTE)((src.g*src.a + dst.g*one_minus_src)/255);
			dst.b = (BYTE)((src.b*src.a + dst.b*one_minus_src)/255);
		}
		static INLFUNC void Set(rt::Vec<BYTE,3>& dst, const rt::Vec<BYTE,4>& src, float additional_src_alpha)
		{	
			int src_a = (int)(additional_src_alpha*src.a + 0.5f);
			int one_minus_src = 255 - src_a;

			dst.r = (BYTE)((src.r*src_a + dst.r*one_minus_src)/255);
			dst.g = (BYTE)((src.g*src_a + dst.g*one_minus_src)/255);
			dst.b = (BYTE)((src.b*src_a + dst.b*one_minus_src)/255);
		}
	};
	template<> struct _Pixel<float, 3, 4>
	{	static INLFUNC void Set(rt::Vec<float,3>& dst, const rt::Vec<float,4>& src)
		{	
			float src_a = _Value<float>::Clamp(src.a);
			float one_minus_src = 1.0f - src_a;

			dst.r = (src.r*src_a + dst.r*one_minus_src);
			dst.g = (src.g*src_a + dst.g*one_minus_src);
			dst.b = (src.b*src_a + dst.b*one_minus_src);
		}
		static INLFUNC void Set(rt::Vec<float,3>& dst, const rt::Vec<float,4>& src, float additional_src_alpha)
		{	
			float src_a = _Value<float>::Clamp(src.a*additional_src_alpha);
			float one_minus_src = 1.0f - src_a;

			dst.r = (src.r*src_a + dst.r*one_minus_src);
			dst.g = (src.g*src_a + dst.g*one_minus_src);
			dst.b = (src.b*src_a + dst.b*one_minus_src);
		}
	};
	template<> struct _Pixel<BYTE, 4, 3>
	{	static INLFUNC void Set(rt::Vec<BYTE,4>& dst, const rt::Vec<BYTE,3>& src)
		{	
			dst.r = src.r;
			dst.g = src.g;
			dst.b = src.b;
			dst.a = 255;
		}
		static INLFUNC void Set(rt::Vec<BYTE,4>& dst, const rt::Vec<BYTE,3>& src, float additional_src_alpha)
		{	
			int src_a = (int)(_Value<float>::Clamp(additional_src_alpha)*255);
			int one_minus_dst = 255 - dst.a;
			int one_minus_src = 255 - src_a;

			dst.r = (BYTE)(255*src.r*src_a + dst.r*one_minus_src*dst.a)/(255*src_a + one_minus_src*dst.a);
			dst.g = (BYTE)(255*src.g*src_a + dst.g*one_minus_src*dst.a)/(255*src_a + one_minus_src*dst.a);
			dst.b = (BYTE)(255*src.b*src_a + dst.b*one_minus_src*dst.a)/(255*src_a + one_minus_src*dst.a);
			dst.a = (BYTE)(255 - one_minus_dst*one_minus_src/255);
		}
	};
	template<> struct _Pixel<float, 4, 3>
	{	static INLFUNC void Set(rt::Vec<float,4>& dst, const rt::Vec<float,3>& src)
		{	
			dst.r = src.r;
			dst.g = src.g;
			dst.b = src.b;
			dst.a = 1.0f;
		}
		static INLFUNC void Set(rt::Vec<float,4>& dst, const rt::Vec<float,3>& src, float additional_src_alpha)
		{	
			float dst_a = _Value<float>::Clamp(dst.a);
			float src_a = _Value<float>::Clamp(additional_src_alpha);
			float one_minus_dst = 1.0f - dst_a;
			float one_minus_src = 1.0f - src_a;

			dst.r = (src.r*src_a + dst.r*one_minus_src*dst_a)/(src_a + one_minus_src*dst_a);
			dst.g = (src.g*src_a + dst.g*one_minus_src*dst_a)/(src_a + one_minus_src*dst_a);
			dst.b = (src.b*src_a + dst.b*one_minus_src*dst_a)/(src_a + one_minus_src*dst_a);
			dst.a = (1.0f - one_minus_dst*one_minus_src);
		}
	};

	template<> struct _Pixel<BYTE, 3, 3>
	{	static INLFUNC void Set(rt::Vec<BYTE,3>& dst, const rt::Vec<BYTE,3>& src)
		{	
			dst.r = src.r;
			dst.g = src.g;
			dst.b = src.b;
		}
		static INLFUNC void Set(rt::Vec<BYTE,3>& dst, const rt::Vec<BYTE,3>& src, float additional_src_alpha)
		{	
			int src_a = (int)(_Value<float>::Clamp(additional_src_alpha)*255);
			int one_minus_src = 255 - src_a;

			dst.r = (BYTE)((src.r*src_a + dst.r*one_minus_src)/255);
			dst.g = (BYTE)((src.g*src_a + dst.g*one_minus_src)/255);
			dst.b = (BYTE)((src.b*src_a + dst.b*one_minus_src)/255);
		}
	};
	template<> struct _Pixel<float, 3, 3>
	{	static INLFUNC void Set(rt::Vec<float,3>& dst, const rt::Vec<float,3>& src)
		{	
			dst.r = src.r;
			dst.g = src.g;
			dst.b = src.b;
		}
		static INLFUNC void Set(rt::Vec<float,3>& dst, const rt::Vec<float,3>& src, float additional_src_alpha)
		{	
			float src_a = _Value<float>::Clamp(additional_src_alpha);
			float one_minus_src = 1.0f - src_a;

			dst.r = (src.r*src_a + dst.r*one_minus_src);
			dst.g = (src.g*src_a + dst.g*one_minus_src);
			dst.b = (src.b*src_a + dst.b*one_minus_src);
		}
	};
	template<class t_Canvas, bool tansposed>
	struct ImageAccess
	{	static INLFUNC UINT GetWidth(const t_Canvas& img){ return img.GetWidth(); }
		static INLFUNC UINT GetHeight(const t_Canvas& img){ return img.GetHeight(); }
		static INLFUNC void	SetPixel(t_Canvas& img, int x, int y, const typename t_Canvas::RGBA& c){ img._SetPixel(x,y,c); }
		static INLFUNC void	SetPixel(t_Canvas& img, int x, int y, const typename t_Canvas::RGBA& c, float a){ img._SetPixel(x,y,c,a); }
		static INLFUNC void	SetPixel(t_Canvas& img, int x, int y, const typename t_Canvas::RGB& c){ img._SetPixel(x,y,c); }
		static INLFUNC void	SetPixel(t_Canvas& img, int x, int y, const typename t_Canvas::RGB& c, float a){ img._SetPixel(x,y,c,a); }
	};
	template<class t_Canvas>
	struct ImageAccess<t_Canvas, true>
	{	static INLFUNC UINT GetHeight(const t_Canvas& img){ return img.GetWidth(); }
		static INLFUNC UINT GetWidth(const t_Canvas& img){ return img.GetHeight(); }
		static INLFUNC void	SetPixel(t_Canvas& img, int x, int y, const typename t_Canvas::RGBA& c){ img._SetPixel(y,x,c); }
		static INLFUNC void	SetPixel(t_Canvas& img, int x, int y, const typename t_Canvas::RGBA& c, float a){ img._SetPixel(y,x,c,a); }
		static INLFUNC void	SetPixel(t_Canvas& img, int x, int y, const typename t_Canvas::RGB& c){ img._SetPixel(y,x,c); }
		static INLFUNC void	SetPixel(t_Canvas& img, int x, int y, const typename t_Canvas::RGB& c, float a){ img._SetPixel(y,x,c,a); }
	};
};

template<typename t_Value,int Channel>
class Canvas: public Image_Ref<t_Value, Channel>
{
	template<class t_Canvas, bool tansposed> friend struct _details::ImageAccess;

	typedef Image_Ref<t_Value, Channel> _SC;
	typedef rt::Vec<t_Value,Channel>	t_Val;
	typedef t_Value						ValueType;
	typedef t_Value*					LPValueType;
	typedef const t_Value*				LPCValueType;
	static const int chan_num = Channel;
	typedef rt::Vec<t_Value, 3>			RGB;
	typedef rt::Vec<t_Value, 4>			RGBA;

protected:
	INLFUNC bool	_IsInBound(const ::ipp::Point& p) const { return p.x>=0 && p.x<(int)_SC::Width && p.y>=0 && p.y<(int)_SC::Height; }
	INLFUNC bool	_IsInBound(int x, int y) const { return x>=0 && x<(int)_SC::Width && y>=0 && y<(int)_SC::Height; }
	INLFUNC void	_SetPixel(int x, int y, const RGBA& c){  _details::_Pixel<t_Value,Channel,4>::Set((*this)(x, y), c); }
	INLFUNC void	_SetPixel(int x, int y, const RGBA& c, float additional_src_alpha){  _details::_Pixel<t_Value,Channel,4>::Set((*this)(x, y), c, additional_src_alpha); }
	INLFUNC void	_SetPixel(int x, int y, const RGB& c){  _details::_Pixel<t_Value,Channel,3>::Set((*this)(x, y), c); }
	INLFUNC void	_SetPixel(int x, int y, const RGB& c, float additional_src_alpha){  _details::_Pixel<t_Value,Channel,3>::Set((*this)(x, y), c, additional_src_alpha); }
	
/** @name Drawing State
*/
///@{
	float	_dsPointRadius;
	float	_dsLineHalfWidth;
	float	_dsPointAreaSinglePixel;	///< used when PointSize < 1
	void	_resetDrawingState()
	{	SetPointSize(3);
		SetLineWidth(3);
	}
///@}
	/**
	 * @brief Drawing Tools
	 * 
	 * @tparam t_Transposed 
	 * @tparam t_Color 
	 * @param cnvs 
	 * @param x0 
	 * @param y0 
	 * @param x1 
	 * @param y1 
	 * @param clr 
	 */
	template<bool t_Transposed, typename t_Color>
	static void _DrawLine(Canvas& cnvs, float x0, float y0, float x1, float y1, const t_Color& clr)
	{
		typedef _details::ImageAccess<Canvas, t_Transposed>	IA;
		float dx = x1-x0;
		float dy = y1-y0;
		if(rt::abs(dx) <= rt::abs(dy))return; // zero-length
		float inc = dy/dx;
		if(dx<0)
		{	rt::Swap(x0, x1);
			rt::Swap(y0, y1);			
		}
		float dist_scale = sqrt(1 + inc*inc);
		float ext = cnvs._dsLineHalfWidth/dist_scale;
		float pad = fabs(ext*inc);
		
		int s,e;
		if(cnvs._dsLineHalfWidth>0)
		{	s = rt::max(0, (int)(x0 + pad + 1));											
			e = rt::min((int)IA::GetWidth(cnvs), (int)(x1 - 2 - pad + 0.99999f));		
		}
		else
		{	s = rt::max(0, (int)(x0 + pad));											
			e = rt::min((int)IA::GetWidth(cnvs), (int)(x1 - pad + 0.99999f));
		}
		
		if(s > (int)IA::GetWidth(cnvs) || e < 0)return;

		for(int i = s; i<=e; i++)
		{
			float c = (i-x0)*inc + y0;
			int v_s = rt::max(0, (int)(c - ext));												if(v_s> (int)IA::GetHeight(cnvs))continue;
			int v_e = rt::min((int)((int)IA::GetHeight(cnvs)-1), (int)(c + ext + 0.99999f));	if(v_e< 0)continue;
			for(int v = v_s; v <= v_e; v++)
			{
				float d = fabs(v - c)*dist_scale - cnvs._dsLineHalfWidth;

				if(d < 0){ IA::SetPixel(cnvs,i, v, clr); continue; }
				IA::SetPixel(cnvs, i, v, clr, (1.0f - d));
			}
		}
		if(cnvs._dsLineHalfWidth>0.2f)
		{	// two ends
			{	int s = rt::max(0, (int)(x0 - pad));
				int e = (int)(x0 + pad + 0.99999f);
				int v_s = rt::max(0, (int)(y0 - ext + pad*inc));
				int v_e = rt::min((int)(IA::GetHeight(cnvs)-1), (int)(y0 + ext + pad*inc + 0.99999f));
				if(e >=0 && s <= (int)IA::GetWidth(cnvs) && v_s <= (int)IA::GetHeight(cnvs) && v_e >=0)
					for(int i = s; i<e; i++)
					{
						float c = (i-x0)*inc + y0;
						for(int v = v_s; v<=v_e; v++)
						{	
							float d = fabs(v - c)*dist_scale - cnvs._dsLineHalfWidth;
							if(d > 1)continue;

							float f = x0 - (v-y0)*inc - i;
							if(f>1)continue;
							if(f>0)
							{
								if(d < 0){ IA::SetPixel(cnvs, i, v, clr, (1.0f - f)); continue; }
								IA::SetPixel(cnvs, i, v, clr, (2.0f - d - f)/2);
							}
							else
							{
								if(d < 0){ IA::SetPixel(cnvs, i, v, clr); continue; }
								IA::SetPixel(cnvs, i, v, clr, (1.0f - d));
							}
						}
					}
			}

			{	int s = rt::max(0, (int)(x1 - pad));
				int e = (int)(x1 + pad + 0.99999f);
				int v_s = rt::max(0, (int)(y1 - ext - pad*inc));
				int v_e = rt::min((int)(IA::GetHeight(cnvs)-1), (int)(y1 + ext - pad*inc + 0.99999f));
				if(e >=0 && s <= (int)IA::GetWidth(cnvs) && v_s <= (int)IA::GetHeight(cnvs) && v_e >=0)
					for(int i = s; i<=e; i++)
					{
						float c = (i-x1)*inc + y1;
						for(int v = v_s; v<=v_e; v++)
						{	
							float d = fabs(v - c)*dist_scale - cnvs._dsLineHalfWidth;
							if(d > 1)continue;

							float f = i - (x1 - (v-y1)*inc);
							if(f>1)continue;
							if(f>0)
							{
								if(d < 0){ IA::SetPixel(cnvs, i, v, clr, (1.0f - f)); continue; }
								IA::SetPixel(cnvs, i, v, clr, (2.0f - d - f)/2);
							}
							else
							{
								if(d < 0){ IA::SetPixel(cnvs, i, v, clr); continue; }
								IA::SetPixel(cnvs, i, v, clr, (1.0f - d));
							}
						}
					}
			}
		}
	}
	template<int ch, class t_Transform>
	INLFUNC void _DrawImage(t_Transform& mapper, const Image_Ref<t_Value, ch>& src)
	{	_DrawImage<ch,t_Transform>(mapper, src, ::ipp::Rect(0,0,src.GetWidth(), src.GetHeight()));
	}
	template<int ch, class t_Transform>
	INLFUNC void _DrawImage(t_Transform& mapper, const Image_Ref<t_Value, ch>& src, const ::ipp::Rect& src_roi)
	{	// dest bounding
		int x_s = _SC::GetWidth(),x_e = 0,y_s = _SC::GetHeight(),y_e = 0;
		{	rt::Vec2f p;
			mapper.Forward(rt::Vec2f((float)src_roi.x,				     (float)src_roi.y),				      p);	x_s = rt::min(x_s, (int)p.x); x_e = rt::max(x_e, (int)(p.x+0.99999f)); y_s = rt::min(y_s, (int)p.y); y_e = rt::max(y_e, (int)(p.y+0.99999f));
			mapper.Forward(rt::Vec2f((float)(src_roi.x+src_roi.width-1), (float)src_roi.y),				      p);	x_s = rt::min(x_s, (int)p.x); x_e = rt::max(x_e, (int)(p.x+0.99999f)); y_s = rt::min(y_s, (int)p.y); y_e = rt::max(y_e, (int)(p.y+0.99999f));
			mapper.Forward(rt::Vec2f((float)src_roi.x,				     (float)(src_roi.y+src_roi.height-1)),p);	x_s = rt::min(x_s, (int)p.x); x_e = rt::max(x_e, (int)(p.x+0.99999f)); y_s = rt::min(y_s, (int)p.y); y_e = rt::max(y_e, (int)(p.y+0.99999f));
			mapper.Forward(rt::Vec2f((float)(src_roi.x+src_roi.width-1), (float)(src_roi.y+src_roi.height-1)),p);	x_s = rt::min(x_s, (int)p.x); x_e = rt::max(x_e, (int)(p.x+0.99999f)); y_s = rt::min(y_s, (int)p.y); y_e = rt::max(y_e, (int)(p.y+0.99999f));
		}
		
		_DrawImage<ch, t_Transform>(mapper, ipp::Rect(x_s, y_s, x_e-x_s+1, y_e-y_s+1), src, src_roi);
	}
	template<int ch, class t_Transform>
	INLFUNC void _DrawImage(t_Transform& mapper, const ::ipp::Rect& dst_roi, const Image_Ref<t_Value, ch>& src)
	{	_DrawImage<ch,t_Transform>(mapper, dst_roi, src, ::ipp::Rect(0,0,src.GetWidth(), src.GetHeight()));
	}
	template<int ch, class t_Transform>
	INLFUNC void _DrawImage(t_Transform& mapper, const ::ipp::Rect& dst_roi, const Image_Ref<t_Value, ch>& src, const ::ipp::Rect& src_roi)
	{
		int x_s = rt::max(0, dst_roi.x);
		int y_s = rt::max(0, dst_roi.y);
		int x_e = x_s + rt::min(dst_roi.width,  (int)_SC::GetWidth() - x_s - 1);
		int y_e = y_s + rt::min(dst_roi.height, (int)_SC::GetHeight() - y_s - 1);
		if(x_s > (int)(_SC::GetWidth()-1) || x_e <= 0 || y_s > (int)(_SC::GetHeight()-1) || y_e <=0 )return;

		int srcroi_ye = src_roi.y + src_roi.height - 1;
		int srcroi_xe = src_roi.x + src_roi.width - 1;
		int srcroi_xc = (srcroi_xe + src_roi.x)/2;
		int srcroi_yc = (srcroi_ye + src_roi.y)/2;
		for(int y = y_s; y < y_e; y++)
		for(int x = x_s; x < x_e; x++)
		{	
			rt::Vec2f p;
			mapper.Backward(rt::Vec2f((float)x,(float)y), p);

			int cx = (int)p.x;
			int cy = (int)p.y;
			rt::Vec<float, ch> v1,v2;
			rt::Vec<t_Value, ch> v;

			if(cx > src_roi.x && cx < srcroi_xe && cy > src_roi.y && cy < srcroi_ye )
			{	
				v1.Interpolate(src(cx, cy),   src(cx+1, cy),   p.x - cx);
				v2.Interpolate(src(cx, cy+1), src(cx+1, cy+1), p.x - cx);

				v.Interpolate(v1, v2, p.y - cy);
				_SetPixel(x, y, v);
			}
			else if(cx >= src_roi.x && cx <= srcroi_xe && cy >= src_roi.y && cy <= srcroi_ye)
			{	
				if(cx > src_roi.x && cx < srcroi_xe)
				{	v.Interpolate(src(cx, cy),   src(cx+1, cy),   fabs(p.x - cx));
					_SetPixel(x, y, v, (cy < srcroi_yc)?(1 + p.y-src_roi.y):(1 + srcroi_ye - p.y));
				}
				else if(cy > src_roi.y && cy < srcroi_ye)
				{	v.Interpolate(src(cx, cy),   src(cx, cy+1),   fabs(p.x - cx));
					_SetPixel(x, y, v, (cx < srcroi_xc)?(1 + p.x-src_roi.x):(1 + srcroi_xe - p.x));
				}
				else 
				{
					_SetPixel(x, y, src(cx, cy),
						rt::min(
							((cy < srcroi_yc)?(1 + p.y-src_roi.y):(1 + srcroi_ye - p.y)),
							((cx < srcroi_xc)?(1 + p.x-src_roi.x):(1 + srcroi_xe - p.x))
						)
					);
				}
			}
		}
	}

public:
	INLFUNC Canvas(){ _resetDrawingState(); }
	INLFUNC Canvas(_SC& img):Image_Ref<t_Value, Channel>(img){ _resetDrawingState(); }

	INLFUNC void DrawPixel(const ::ipp::Point& p, const RGBA& c){ if(_IsInBound(p))_SetPixel(p.x, p.y, c); }
	INLFUNC void DrawPixel(int x, int y, const RGBA& c){ if(_IsInBound(x,y))_SetPixel(x, y, c); }
	INLFUNC void DrawPixel(const ::ipp::Point& p, const RGB& c){ if(_IsInBound(p))_SetPixel(p.x, p.y, c); }
	INLFUNC void DrawPixel(int x, int y, const RGB& c){ if(_IsInBound(x,y))_SetPixel(x, y, c); }

	INLFUNC void Clear(const t_Val& c){ _SC::Set(c); }


/** @name Drawing State
*/
///@{
	INLFUNC void  SetPointSize(float sz){ _dsPointRadius = sz/2.0f - 0.5f; _dsPointAreaSinglePixel = 3.1415926f/4.0f*sz*sz; }
	INLFUNC float GetPointSize(float sz) const { return _dsPointRadius*2.0f + 0.5f; }
	INLFUNC void  SetLineWidth(float sz){ _dsLineHalfWidth = sz/2.0f - 0.5f; }
	INLFUNC float GetLineWidth(float sz) const { return _dsLineHalfWidth*2.0f + 0.5f; }
///@}
/** @name Drawing Tools
*/
///@{
	template<int ch>
	void DrawPoint(float cx, float cy, const rt::Vec<t_Value, ch>& c)
	{
		if(_dsPointRadius>0)
		{	int x_s = rt::max(0, (int)(cx - _dsPointRadius));								if(x_s > (int)_SC::Width)return;
			int x_e = rt::min((int)(_SC::Width-1), (int)(cx + _dsPointRadius + 0.99999f));	if(x_e < 0)return;
			int y_s = rt::max(0, (int)(cy - _dsPointRadius));								if(y_s > (int)_SC::Height)return;
			int y_e = rt::min((int)(_SC::Height-1), (int)(cy + _dsPointRadius + 0.99999f));	if(y_e < 0)return;

			for(int y = y_s; y <= y_e; y++)
			for(int x = x_s; x <= x_e; x++)
			{
				float d = sqrt(rt::Sqr(x - cx) + rt::Sqr(y - cy)) - _dsPointRadius;
				if(d < 0){ _SetPixel(x, y, c); continue; }
				if(d > 1){ continue; }
				
				_SetPixel(x, y, c, (1.0f - d));
			}
		}
		else
		{	_SetPixel((int)(cx+0.5f), (int)(cy+0.5f), c, _dsPointAreaSinglePixel);
		}
	}
	template<int ch> 
	INLFUNC void DrawPoint(const rt::Vec2f& p, const rt::Vec<t_Value, ch>& c){ DrawPoint<ch>(p.x, p.y, c); }

	template<int ch>
	INLFUNC void DrawLine(float x0, float y0, float x1, float y1, const rt::Vec<t_Value, ch>& c)
	{	float dx = x1-x0;
		float dy = y1-y0;
		if(rt::abs(dx) > rt::abs(dy))	// scan along x
		{	_DrawLine<false, rt::Vec<t_Value, ch> >(*this, x0, y0, x1, y1, c);
		}
		else
		{	_DrawLine<true, rt::Vec<t_Value, ch> >(*this, y0, x0, y1, x1, c);
		}
	}
	template<int ch>
	INLFUNC void DrawLine(const rt::Vec2f& p0, const rt::Vec2f& p1, const rt::Vec<t_Value, ch>& c){ DrawLine<ch>(p0.x, p0.y, p1.x, p1.y, c); }
	template<int ch>
	INLFUNC void DrawLines(const rt::Vec2f* p, int count, const rt::Vec<t_Value, ch>& c)
	{	for(int i=0;i<count-1;i++)
			DrawLine<ch>(p[i], p[i+1], c); 
	}
	template<int ch>
	INLFUNC void DrawLineLoop(const rt::Vec2f* p, int count, const rt::Vec<t_Value, ch>& c)
	{	DrawLines<ch>(p,count,c);
		DrawLine<ch>(p[0], p[count-1], c);
	}

	template<int ch> 
	INLFUNC void DrawRect(const rt::Vec2f& p0, const rt::Vec2f& p1, const rt::Vec<t_Value, ch>& c)
	{	
		_DrawLine<false, rt::Vec<t_Value, ch> >(*this, p0.x, p0.y, p1.x, p0.y, c);
		_DrawLine<false, rt::Vec<t_Value, ch> >(*this, p0.x, p1.y, p1.x, p1.y, c);
		_DrawLine<true, rt::Vec<t_Value, ch> >(*this, p0.y, p0.x, p1.y, p0.x, c);
		_DrawLine<true, rt::Vec<t_Value, ch> >(*this, p0.y, p1.x, p1.y, p1.x, c);
	}
	template<int ch> 
	INLFUNC void DrawRect(const ::ipp::Rect& rc, const rt::Vec<t_Value, ch>& c)
	{	DrawRect(rt::Vec2f((float)rc.x, (float)rc.y), rt::Vec2f((float)(rc.x+rc.width-1), (float)(rc.y+rc.height-1)), c);
	}

	template<int ch>
	INLFUNC void DrawImage(int to_x, int to_y, const Image_Ref<t_Value, ch>& img, const ::ipp::Rect& roi)
	{	int x_s = rt::max(0, to_x + roi.x);											if(x_s > (int)_SC::Width)return;
		int x_e = rt::min((int)(_SC::Width-1), to_x + roi.x + (int)roi.width - 1);	if(x_e < 0)return;
		int y_s = rt::max(0, to_y + roi.y);											if(y_s > (int)_SC::Height)return;
		int y_e = rt::min((int)(_SC::Height-1),to_y + roi.y + (int)roi.height- 1);	if(y_e < 0)return;

		for(int y=y_s; y<=y_e; y++)
		for(int x=x_s; x<=x_e; x++)
		{	_SetPixel(x,y, img(x - to_x, y - to_y));
		}
	}
	template<int ch>
	INLFUNC void DrawImage(int to_x, int to_y, const Image_Ref<t_Value, ch>& img)
	{	DrawImage(to_x, to_y, img, ipp::Rect(0,0,img.GetWidth(), img.GetHeight()));
	}
	
	template<int ch>
	INLFUNC void DrawImage(float to_x, float to_y, const Image_Ref<t_Value, ch>& img, const ::ipp::Rect& roi)
	{	struct _trans
		{	float dx,dy;
			INLFUNC void Backward(const rt::Vec2f& f, rt::Vec2f& t){ t.x = f.x - dx; t.y = f.y - dy; }
			INLFUNC void Forward(const rt::Vec2f& f, rt::Vec2f& t){ t.x = f.x + dx; t.y = f.y + dy; }
		};
		_trans t = { to_x, to_y };
		_DrawImage(t, img, roi);
	}
	template<int ch>
	INLFUNC void DrawImage(float to_x, float to_y, const Image_Ref<t_Value, ch>& img)
	{	DrawImage(to_x, to_y, img, ipp::Rect(0,0,img.GetWidth(), img.GetHeight()));
	};

	template<int ch>
	INLFUNC bool DrawImage(const rt::Mat3x3f& transform, const Image_Ref<t_Value, ch>& img, const ::ipp::Rect& roi) // transform is treated as forward transform
	{	struct _trans
		{	const rt::Mat3x3f& trans;
			rt::Mat3x3f inv;
			bool inv_ok;
			_trans(const rt::Mat3x3f& t):trans(t){ inv_ok = t.Inverse(inv); }
			INLFUNC void Backward(const rt::Vec2f& f, rt::Vec2f& t)
			{	t.x = inv.m00*f.x + inv.m01*f.y + inv.m02;
				t.y = inv.m10*f.x + inv.m11*f.y + inv.m12;
			}
			INLFUNC void Forward(const rt::Vec2f& f, rt::Vec2f& t)
			{	t.x = trans.m00*f.x + trans.m01*f.y + trans.m02;
				t.y = trans.m10*f.x + trans.m11*f.y + trans.m12;
			}
		};
		_trans t(transform);
		if(!t.inv_ok)return false;
		_DrawImage(t, img, roi);
		return true;
	}
	template<int ch>
	INLFUNC bool DrawImage(const rt::Mat3x3f& transform, const Image_Ref<t_Value, ch>& img) // transform is treated as forward transform
	{	return DrawImage(transform, img, ipp::Rect(0,0,img.GetWidth(), img.GetHeight()));
	};
///@}
};


typedef Canvas<float,1>	Canvas_1c32f;
typedef Canvas<float,3>	Canvas_3c32f;
typedef Canvas<float,4>	Canvas_4c32f;
						
typedef Canvas<BYTE,1>	Canvas_1c8u;
typedef Canvas<BYTE,3>	Canvas_3c8u;
typedef Canvas<BYTE,4>	Canvas_4c8u;
/** @}*/

} // namespace ipp
/** @}*/
