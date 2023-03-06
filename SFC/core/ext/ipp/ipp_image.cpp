#include "ipp_core.h"
#include "../zlib/zlib.h"

#define PNG_USE_GLOBAL_ARRAYS
#define PNG_NO_SETJMP_SUPPORTED
#include "png/png.h"
#include "png/pngstruct.h"
#include "png/pnginfo.h"
#include "jpg/cdjpeg.h"
#include "jpg/jversion.h"
#include "gif/gif_lib.h"

#ifdef PLATFORM_INTEL_IPP_WEBP_CODEC
#include "libwebp/webp_header.h"
#endif // PLATFORM_INTEL_IPP_WEBP_CODEC



#include "ipp_image.h"



namespace ipp
{
namespace ipp_cpp
{

IppStatus ippiHaarWTInv_C1R(LPCIpp8u pSrc,int srcStep,LPIpp8u pDst,int dstStep, IppiSize roi)
{
	if((!pSrc)||(!pDst))return ippStsNullPtrErr;
	if(roi.height<=0 || roi.width<=0)return ippStsSizeErr;
	if(roi.height&1 || roi.width&1)return ippStsSizeErr;

	int Offset_HL,Offset_LH,Offset_HH;
	Offset_HL = roi.width>>1;
	Offset_LH = (roi.height>>1)*dstStep;
	Offset_HH = Offset_HL+Offset_LH;

	struct _threshold8u
	{	static INLFUNC int call(int x){ return (x>=0?(x<=255?(x):255):0); }
	};

	const Ipp8u * pS;
	int DoubleStep = dstStep<<1;
	for(pS=pSrc;pS<&pSrc[Offset_LH];pDst+=DoubleStep,pS+=srcStep)
	{
		const Ipp8u * pLL=pS;
		Ipp8u *p=pDst;
		for(;pLL<&pS[Offset_HL];pLL++,p+=2)
		{
			int va,ha,aa;
			va = pLL[0]+pLL[Offset_HL] - 128;
			ha = pLL[0]+pLL[Offset_LH] - 128;
			aa = va-pLL[0]+pLL[Offset_HH] - 128 +ha;

			p[1] = _threshold8u::call((ha<<1) - aa);
			*p = _threshold8u::call(aa);
			p[srcStep] = _threshold8u::call((va<<1) - aa);
			p[srcStep+1] = _threshold8u::call(aa-((va+ha - (pLL[0]<<1))<<1));
		}
	}

	return ippStsNoErr;
}


IppStatus ippiHaarWTFwd_C1R(LPCIpp8u pSrc,int srcStep, LPIpp8u pDst,int dstStep, IppiSize roi)
{
	if((!pSrc)||(!pDst))return ippStsNullPtrErr;
	if(roi.height<=0 || roi.width<=0)return ippStsSizeErr;
	if(roi.height&1 || roi.width&1)return ippStsSizeErr;

	int Offset_HL,Offset_LH,Offset_HH;
	Offset_HL = roi.width>>1;
	Offset_LH = (roi.height>>1)*dstStep;
	Offset_HH = Offset_HL+Offset_LH;

	Ipp8u * pD;
	int DoubleStep = srcStep<<1;
	for(pD=pDst;pD<&pDst[Offset_LH];pD+=dstStep,pSrc+=DoubleStep)
	{
		Ipp8u * pLL=pD;
		const Ipp8u *p=pSrc;
		for(;pLL<&pD[Offset_HL];pLL++,p+=2)
		{
			int ha0 = ((int)p[0]+(int)p[1])>>1;
			int ha1 = (((int)p[srcStep]+(int)p[srcStep+1])>>1);
			int avg = (ha0+ha1)>>1;
			int va0 = ((int)p[0]+(int)p[srcStep])>>1;

			*pLL = avg;

			//ASSERT((va0 - avg)+128>=0);
			//ASSERT((va0 - avg)+128<=255);
			pLL[Offset_HL] = (va0 - avg)+128;

			//ASSERT((ha0 - avg)+128>=0);
			//ASSERT((ha0 - avg)+128<=255);
			pLL[Offset_LH] = (ha0 - avg)+128;

			//ASSERT(((((int)p[0] - ha0) - ((int)p[srcStep] - ha1))>>1)+128>=0);
			//ASSERT(((((int)p[0] - ha0) - ((int)p[srcStep] - ha1))>>1)+128<=255);
			pLL[Offset_HH] = ((((int)p[0] - ha0) - ((int)p[srcStep] - ha1))>>1)+128;
		}
	}

	return ippStsNoErr;
}

IppStatus ippiHaarWTInv_C1R(LPCIpp32f pSrc,int srcStep, LPIpp32f pDst,int dstStep, IppiSize roi)
{
	if((!pSrc)||(!pDst))return ippStsNullPtrErr;
	if(roi.height<=0 || roi.width<=0)return ippStsSizeErr;
	if(roi.height&1 || roi.width&1)return ippStsSizeErr;

	ASSERT((srcStep&3) == 0);
	ASSERT((dstStep&3) == 0);

	srcStep>>=2;
	dstStep>>=2;

	int Offset_HL,Offset_LH,Offset_HH;
	Offset_HL = roi.width>>1;
	Offset_LH = (roi.height>>1)*dstStep;
	Offset_HH = Offset_HL+Offset_LH;

	LPCIpp32f pS;
	int DoubleStep = dstStep<<1;
	for(pS=pSrc;pS<&pSrc[Offset_LH];pDst+=DoubleStep,pS+=srcStep)
	{
		LPCIpp32f pLL=pS;
		LPIpp32f p=pDst;
		for(;pLL<&pS[Offset_HL];pLL++,p+=2)
		{
			float va,ha,aa;
			va = pLL[0]+pLL[Offset_HL];
			ha = pLL[0]+pLL[Offset_LH];
			aa = va-pLL[0]+pLL[Offset_HH]+ha;

			p[1] = ((ha*2) - aa);
			*p = (aa);
			p[srcStep] = ((va*2) - aa);
			p[srcStep+1] = (aa-((va+ha - (pLL[0]*2))*2));
		}
	}

	return ippStsNoErr;
}


IppStatus ippiHaarWTFwd_C1R(LPCIpp32f pSrc,int srcStep, LPIpp32f pDst,int dstStep, IppiSize roi)
{
	if((!pSrc)||(!pDst))return ippStsNullPtrErr;
	if(roi.height<=0 || roi.width<=0)return ippStsSizeErr;
	if(roi.height&1 || roi.width&1)return ippStsSizeErr;

	ASSERT((srcStep&3) == 0);
	ASSERT((dstStep&3) == 0);

	srcStep>>=2;
	dstStep>>=2;

	int Offset_HL,Offset_LH,Offset_HH;
	Offset_HL = roi.width>>1;
	Offset_LH = (roi.height>>1)*dstStep;
	Offset_HH = Offset_HL+Offset_LH;

	LPIpp32f  pD;
	int DoubleStep = srcStep<<1;
	for(pD=pDst;pD<&pDst[Offset_LH];pD+=dstStep,pSrc+=DoubleStep)
	{
		LPIpp32f  pLL=pD;
		LPCIpp32f p=pSrc;
		for(;pLL<&pD[Offset_HL];pLL++,p+=2)
		{
			float ha0 = (p[0]+p[1])/2;
			float ha1 = ((p[srcStep]+p[srcStep+1])/2);
			float avg = (ha0+ha1)/2;
			float va0 = (p[0]+p[srcStep])/2;

			*pLL = avg;
			pLL[Offset_HL] = (va0 - avg);
			pLL[Offset_LH] = (ha0 - avg);
			pLL[Offset_HH] = (((p[0] - ha0) - (p[srcStep] - ha1))/2);
		}
	}

	return ippStsNoErr;
}


} // namespace ipp_cpp
} // namespace ipp


namespace ipp
{

namespace image_codec   // access to PFM
{
	bool _Write_PFM(LPCSTR fn,LPCFLOAT pData,UINT ch,UINT w,UINT h,UINT step)
	{
		ASSERT(ch==1 || ch==3);
		CHAR Header[512];
		UINT header_len = (UINT)sprintf(Header,"P%c\x0a%d %d\x0a-1.000000\x0a",(ch==1)?'f':'F',w,h);
		os::File file;
		if(file.Open(fn,os::File::Normal_Write, true))
		{
			// write header
			if(file.Write(Header,header_len) == header_len)
			{	LPCBYTE p=(LPBYTE)pData;
				p+=step*(h-1); //in reversed order, to compatible with HDRShop
				for(UINT y=0;y<h;y++,p-=step)
					file.Write(p,sizeof(float)*ch*w);

				return !file.ErrorOccured();
			}
		}
		return false;
	}
	bool _Open_PFM(LPCSTR fn,_PFM_Header* pHeader)
	{
		ASSERT(pHeader);
		char Header[1025];
		pHeader->file.Close();
		if(pHeader->file.Open(fn))
		{
			DWORD len = (DWORD)pHeader->file.Read(Header,1024);
			Header[len] = 0;
			if(len>3)
			{	Header[len-1] = 0;
				if( Header[0] == 'P' && ( Header[1] == 'F' || Header[1] == 'f' ) )		// "PF" or "Pf"
				{	pHeader->ch = (Header[1] == 'F')?3:1;
					LPSTR p = strchr(Header,0xa);
					if(p)
					{	LPSTR end;
						p++;
						end = strchr(p,0xa);
						if(end)
						{	end[0] = 0;
							if(sscanf(p,"%d %d",&pHeader->width,&pHeader->height) == 2)	// width height
							{	
								p = &end[1];
								while(*p == '#')
								{	// skip comments, compatible to IST's Data
									end = strchr(p,0xa);
									p = &end[1];
								}
								end = strchr(p,0xa);									// "-1.0000"
							
								if(end)
								{	pHeader->file.Seek(((UINT)(end-Header))+1);
									return !pHeader->file.ErrorOccured();
								}
							}
						}
					}
				}
			}
		}
		return false;
	}

	bool _Read_PFM(const _PFM_Header* pHeader,LPFLOAT pData,UINT ch,UINT step)
	{
		if( ch==pHeader->ch )
		{	LPBYTE p=&((LPBYTE)pData)[step*(pHeader->height-1)];
			for(UINT y=0;y<pHeader->height;y++,p-=step) //in reversed order, to compatible with HDRShop
			{
				rt::_CastToNonconst(&pHeader->file)->Read(p,sizeof(float)*ch*pHeader->width);
			}
			return !rt::_CastToNonconst(&pHeader->file)->ErrorOccured();
		}
		else
		{	
			if(ch==1 && pHeader->ch==3) //color->grayscale
			{	rt::Buffer<rt::Vec3f> buf;
				buf.SetSize(pHeader->width);
				LPBYTE p = (LPBYTE)pData;
				p+=step*(pHeader->height-1); //in reversed order, to compatible with HDRShop
				for(UINT y=0;y<pHeader->height;y++,p-=step)
				{
					rt::_CastToNonconst(&pHeader->file)->Read(buf,sizeof(rt::Vec3f)*pHeader->width);
					if(rt::_CastToNonconst(&pHeader->file)->ErrorOccured())return false;
					memcpy(p, buf, pHeader->width*sizeof(rt::Vec1f));
				}
				return true;
			}
			else if(ch==3 && pHeader->ch==1) //grayscale->color
			{	rt::Buffer<rt::Vec1f> buf;
				buf.SetSize(pHeader->width);
				LPBYTE p = (LPBYTE)pData;
				p+=step*(pHeader->height-1); //in reversed order, to compatible with HDRShop
				for(UINT y=0;y<pHeader->height;y++,p-=step)
				{
					rt::_CastToNonconst(&pHeader->file)->Read(buf,sizeof(rt::Vec1f)*pHeader->width);
					if(rt::_CastToNonconst(&pHeader->file)->ErrorOccured())return false;
					memcpy(p, buf, sizeof(rt::Vec3f)*pHeader->width);
				}
				return true;
			}
		
		}

		return false;
	}
} // namespace image_codec




/*
bool ImageDecoder::DecodeHeader(LPCBYTE pData, UINT DataLen, DWORD image_codec)
{
	m_DecodedImageWidth = m_DecodedImageHeight = m_DecodedImageStep = m_DecodedImageChannel = 0;
	m_ImageCodec = ImageCodec_Auto;

	if(image_codec == ImageCodec_Auto)
	{
		if(	*((DWORD*)pData) == 0xe0ffd8ff && *((DWORD*)(6 + pData)) == 0x4649464a && pData[10] == 0)
		{	image_codec = ImageCodec_JPG;
		}
		else
		if( *((ULONGLONG*)pData) == 0x0a1a0a0d474e5089	)
		{	image_codec = ImageCodec_PNG;
		}
		else return false;
	}

	m_ImageCodec = image_codec;

	if(m_ImageCodec == ImageCodec_JPG)
	{
		JPEG_CORE_PROPERTIES	m_JcProps;
		VERIFY(ijlInit(&m_JcProps) == IJL_OK);

		m_DecodedImageStep = 0;
		m_BufferUsedLen = 0;

		m_JcProps.JPGFile = nullptr;
		m_JcProps.JPGBytes = rt::_CastToNonconst(pData);
		m_JcProps.JPGSizeBytes = DataLen;
		if(ijlRead(&m_JcProps, IJL_JBUFF_READPARAMS)!=IJL_OK)
		{
			ijlFree(&m_JcProps);
			return false;
		}

		m_DecodedImageWidth = m_JcProps.JPGWidth;
		m_DecodedImageHeight = m_JcProps.JPGHeight;
		m_DecodedImageChannel = m_JcProps.JPGChannels;
		m_DecodedImageStep = m_DecodedImageWidth*m_DecodedImageChannel;
		if( m_DecodedImageStep%4 )m_DecodedImageStep = ((m_DecodedImageStep>>2)+1)<<2;

		ijlFree(&m_JcProps);
	}
	else if(m_ImageCodec == ImageCodec_PNG)
	{
		UINT datasize = DataLen;
		LPCBYTE p=&pData[8];
		for(;;)
		{	// Read png
			const _details::png_chunk* chunk = (_details::png_chunk*)p;
			UINT chunk_len = chunk->length;
			rt::SwapByteOrder(chunk_len);
			UINT total_size = chunk_len + sizeof(_details::png_chunk);
			if(total_size > datasize)return false;

			if(chunk->id == _details::png_hdrchunk)
			{
				const _details::png_header* hdr = (const _details::png_header*)(chunk->data);
				m_DecodedImageWidth = hdr->Width;
				m_DecodedImageHeight = hdr->Height;
				rt::SwapByteOrder(m_DecodedImageWidth);
				rt::SwapByteOrder(m_DecodedImageHeight);
				if(m_DecodedImageWidth == 0 || m_DecodedImageHeight == 0)return false;

				if(	hdr->ColorType == 3 && 
					(	hdr->BitDepth == 1 ||
						hdr->BitDepth == 2 ||
						hdr->BitDepth == 4 ||
						hdr->BitDepth == 8
					)
				)
				{	m_DecodedImageChannel = 3;
				}
				else
				{
					if(hdr->BitDepth != 8)return false;

					switch(hdr->ColorType)
					{
					case 0:	m_DecodedImageChannel = 1;	break;
					case 2:	m_DecodedImageChannel = 3;	break;
					case 4: m_DecodedImageChannel = 2;  break;
					case 6: m_DecodedImageChannel = 4;  break;
					default:
						return false;
					}
				}
				//w = ntohl(hdr->Width);
				//h = ntohl(hdr->Height);
				//step = w*image_size/8 + 1;	// weird padding, 1 byte, tested on 32BPP images with CgBI
				//image_size = step*h;
				//interlace = hdr->InterlaceMethod;
			}
		}
	}
	
	return true;
}
*/

_tagImageCodec ImageDecoder::DecodeFormat(LPCBYTE pData, UINT DataLen)
{
	if(DataLen < 16)return ImageCodec_Unk;

	if(	(*((WORD*)pData)) == 0xd8ff && pData[2] == 0xff)	// Exif header FF D8 FF ...
	{	return ImageCodec_JPG;
	}
	else
	if( *((ULONGLONG*)pData) == 0x0a1a0a0d474e5089	)
	{	return ImageCodec_PNG;
	}
	else
	if( pData[0] == 'P' && 
		(pData[1] == 'f' || pData[1] == 'F') && 
		pData[2] == '\x0a'
	)
	{	return ImageCodec_PFM;
	}
	else
	if(	pData[0] == 'G' && pData[1] == 'I' && pData[2] == 'F' &&
		pData[3] == '8' &&					  pData[5] == 'a'
	)
	{	return ImageCodec_GIF;
	}
#ifdef PLATFORM_INTEL_IPP_EXR_CODEC
	else
	if( *((UINT*)pData) == 0x1312f76)
	{	
		return ImageCodec_EXR;
	}
#endif
#ifdef PLATFORM_INTEL_IPP_WEBP_CODEC
	else
		if (pData[0] == 'R' && pData[1] == 'I' && pData[2] == 'F' && pData[3] == 'F' &&
			pData[8] == 'W' && pData[9] == 'E' && pData[10] == 'B' && pData[11] == 'P')
		{
			return ImageCodec_WEBP;
		}
#endif 	
	else
		return ImageCodec_Unk;
}

bool ImageDecoder::Decode(LPCVOID pDataIn, UINT DataLen, DWORD image_codec)
{
	m_BufferUsedLen = 0;
	LPCBYTE pData = (LPCBYTE)pDataIn;
	m_DecodedImageWidth = m_DecodedImageHeight = m_DecodedImageStep = m_DecodedImageChannel = 0;
	m_ImageCodec = ImageCodec_Auto;

	if(image_codec == ImageCodec_Auto)
	{
		image_codec = DecodeFormat(pData, DataLen);
		if(image_codec == ImageCodec_Unk)return false;
	}

	m_ImageCodec = image_codec;
	m_FrameCount = 0;

	if(m_ImageCodec == ImageCodec_PNG)
	{
		struct _read_function: public rt::IStream_Ref
		{	_read_function(LPCBYTE p, UINT len):rt::IStream_Ref(p, len){}
			static void _func(png_structp png, png_bytep buf, png_size_t size)
			{	png_size_t check = ((_read_function*)(png->io_ptr))->Read(buf,(UINT)size);
				if(check != size)longjmp(png->jmp_buf_local, 1);
			}
		};

		_read_function _png_io(pData, DataLen);
		png_structp png_ptr = nullptr;
		png_infop info_ptr = nullptr;
        /* initialize stuff */
		if(	(png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL)) &&
			(info_ptr = png_create_info_struct(png_ptr))
		)
		{	
			if(!setjmp(png_jmpbuf(png_ptr)))
			{
				png_set_read_fn(png_ptr, &_png_io, _read_function::_func);
				_png_io.Seek(8);

				png_set_sig_bytes(png_ptr, 8);
				png_read_info(png_ptr, info_ptr);

				//int number_of_passes = png_set_interlace_handling(png_ptr);
				png_set_expand(png_ptr);
				png_set_strip_16(png_ptr);
				png_set_packing(png_ptr);
				png_read_update_info(png_ptr, info_ptr);

				m_DecodedImageWidth = (int)info_ptr->width;
				m_DecodedImageHeight = (int)info_ptr->height;
				m_DecodedImageChannel = info_ptr->channels;
				m_DecodedImageStep = rt::max(m_DecodedImageWidth*m_DecodedImageChannel, (int)png_get_rowbytes(png_ptr,info_ptr));
				m_DecodedImageStep = (m_DecodedImageStep + 3)&0xfffffffc;
				m_FrameCount = 1;

				if(!_SetBufferSize(m_DecodedImageStep*m_DecodedImageHeight))
				{
					if(png_ptr)png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
					return false;
				}

				png_bytep* rows = (png_bytep*)alloca(sizeof(png_bytep)*m_DecodedImageHeight);
				for(int i=0;i<m_DecodedImageHeight;i++)
					rows[i] = m_TempBuffer.Begin() + i*m_DecodedImageStep;
			
				png_read_image(png_ptr, rows);
				m_BufferUsedLen = m_DecodedImageStep*m_DecodedImageHeight;
				if(png_ptr)png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
				return true;
			}
		}
		if(png_ptr)png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	}
	else if(m_ImageCodec == ImageCodec_JPG)
	{
		// Use libjpg instead
		bool ret = false;
		struct jpeg_decompress_struct cinfo;
		struct jpeg_error_mgr jerr;
		cinfo.err = jpeg_std_error(&jerr);

		jpeg_create_decompress(&cinfo);
#ifdef NEED_SIGNAL_CATCHER
  enable_signal_catcher((j_common_ptr) &cinfo);
#endif
		jpeg_mem_src(&cinfo, (LPBYTE)pDataIn, DataLen);
		if(JPEG_HEADER_OK == jpeg_read_header(&cinfo, true))
		{
			m_DecodedImageWidth = cinfo.image_width;
			m_DecodedImageHeight = cinfo.image_height;
			m_DecodedImageChannel = cinfo.num_components;

			m_DecodedImageStep = m_DecodedImageWidth*m_DecodedImageChannel;
			m_DecodedImageStep = (m_DecodedImageStep + 3)&0xfffffffc;

			if(!_SetBufferSize(m_DecodedImageHeight*m_DecodedImageStep + sizeof(LPBYTE)*m_DecodedImageHeight))
			{
				jpeg_destroy_decompress(&cinfo);
				return false;
			}

			LPBYTE* scanlines = (LPBYTE*)(m_TempBuffer.Begin() + m_DecodedImageHeight*m_DecodedImageStep);
			for(int y=0;y<m_DecodedImageHeight;y++)
				scanlines[y] = &m_TempBuffer[m_DecodedImageStep*y];

			if(jpeg_start_decompress(&cinfo))
			{	
				for(int lines=0; 
					lines<m_DecodedImageHeight; 
					lines+=jpeg_read_scanlines(&cinfo, scanlines + lines, m_DecodedImageHeight - lines)
				);
				jpeg_finish_decompress(&cinfo);
				ret = true;
			}
		}
		jpeg_destroy_decompress(&cinfo);
		return ret;
	}
#ifdef PLATFORM_INTEL_IPP_WEBP_CODEC
	else if (m_ImageCodec == ImageCodec_WEBP)
		{
		WebPBitstreamFeatures features;
		auto ret = WebPGetFeatures(pData, DataLen, &features);
		if (ret != VP8_STATUS_OK) return false;
		if (features.has_animation) return false; //do not support animation now. 
		m_DecodedImageWidth = features.width;
		m_DecodedImageHeight = features.height;
		m_DecodedImageChannel = 3 + static_cast<int>(features.has_alpha);
		//auto lossy = features.format; // 0 = undefined (/mixed), 1 = lossy, 2 = lossless  ,unused now

		m_DecodedImageStep = m_DecodedImageWidth * m_DecodedImageChannel;
		m_DecodedImageStep = (m_DecodedImageStep + 3) & 0xfffffffc;
		auto output_buffer_size = static_cast<int>(m_DecodedImageHeight * m_DecodedImageStep + sizeof(LPBYTE) * m_DecodedImageHeight);
		if (!_SetBufferSize(output_buffer_size))
		{
			return false;
		}
		m_TempBuffer.Set(0);
		uint8_t* ans = nullptr;
		if (m_DecodedImageChannel == 3)
		{
			ans = WebPDecodeRGBInto(pData, DataLen, m_TempBuffer.Begin(), output_buffer_size, m_DecodedImageStep);
		}
		else
		{
			ASSERT(m_DecodedImageChannel == 4);
			ans = WebPDecodeRGBAInto(pData, DataLen, m_TempBuffer.Begin(), output_buffer_size, m_DecodedImageStep);
		}
		if (ans == nullptr) //storage is not sufficient (or an error occurred)
		{
			return false;
		}
		m_BufferUsedLen = m_DecodedImageStep * m_DecodedImageHeight;
		return true;

		}
#endif // PLATFORM_INTEL_IPP_WEBP_CODEC

	else if(m_ImageCodec == ImageCodec_GIF || m_ImageCodec == ImageCodec_GIF_ANI)
	{
		struct data
		{	LPCVOID pDataIn;
			UINT	DataLen;
			UINT	Pos;
			static int read(GifFileType * g, GifByteType * out, int s)
			{	
				auto& d = *(data*)g->UserData;
				s = rt::min((UINT)s, d.DataLen - d.Pos);
				
				memcpy(out, ((LPCBYTE)d.pDataIn) + d.Pos, s);
				d.Pos += s;
				return s;
			}
		};
		data d;
		d.DataLen = DataLen;
		d.pDataIn = pDataIn;
		d.Pos = 0;
		
		GifFileType* gif = DGifOpen(&d, data::read, NULL);
		if(gif && DGifSlurp(gif) == GIF_OK && gif->ImageCount > 0 && gif->SWidth > 0 && gif->SHeight > 0)
		{
			m_DecodedImageWidth = gif->SWidth;
			m_DecodedImageHeight = gif->SHeight;
			m_DecodedImageChannel = 3;

			m_FrameCount = gif->ImageCount;
			if(m_ImageCodec != ImageCodec_GIF_ANI)
				m_FrameCount = 1;

			m_DecodedImageStep = m_DecodedImageWidth*m_DecodedImageChannel;
			m_DecodedImageStep = (m_DecodedImageStep + 3)&0xfffffffc;

			if(!_SetBufferSize(m_DecodedImageStep * m_DecodedImageHeight * m_FrameCount))
			{
				DGifCloseFile(gif, NULL);
				return false;
			}

			for(int f=0; f<m_FrameCount; f++)
			{
				auto& img = gif->SavedImages[f];
				ColorMapObject* cmo = gif->SColorMap?gif->SColorMap:img.ImageDesc.ColorMap;

				if(	img.ImageDesc.Top < 0 || img.ImageDesc.Left < 0 || 
					img.ImageDesc.Left + img.ImageDesc.Width > m_DecodedImageWidth ||
					img.ImageDesc.Top + img.ImageDesc.Height > m_DecodedImageHeight ||
					cmo == nullptr ||
					img.RasterBits == nullptr
				)
				{	goto GIF_DECODE_FAILED;
				}

				LPBYTE data = m_TempBuffer.Begin() + m_DecodedImageStep * m_DecodedImageHeight * f;
				if(img.ImageDesc.Width < m_DecodedImageWidth || img.ImageDesc.Height < m_DecodedImageHeight)
				{	
					if(f == 0)
					{	// init first frame
						rt::Zero(data, m_DecodedImageStep * m_DecodedImageHeight);
					}
					else
					{	// copy from preivous frame
						memcpy(data, data - m_DecodedImageStep * m_DecodedImageHeight, m_DecodedImageStep * m_DecodedImageHeight);
					}
				}

				data += m_DecodedImageStep * img.ImageDesc.Top + img.ImageDesc.Left * 3;

				LPCBYTE raster = img.RasterBits;
                GifColorType* colormap = cmo->Colors;
				int color_count = cmo->ColorCount;

				for(int y = 0; y < img.ImageDesc.Height; y++)
				{
					LPBYTE scanline = data + y*m_DecodedImageStep;
					for(int x = 0; x < img.ImageDesc.Width; x++, raster++, scanline+=3)
					{
						if(*raster<color_count)
						{	
							auto& c = colormap[*raster];
							scanline[0] = c.Red;	scanline[1] = c.Green;		scanline[2] = c.Blue;
						}
						else
						{	scanline[0] = 0;		scanline[1] = 0;			scanline[2] = 0;
						}
					}
				}
			}

			return true;
		}
		
		else
		{	
GIF_DECODE_FAILED:
			if(gif)DGifCloseFile(gif, NULL);
			return false;
		}
	}

	return false;
}

_tagImageCodec ImageEncoder::CodecFromExtName(const rt::String_Ref& filename)
{
	rt::String	str = filename.GetExtName().TrimLeft(1);
	if(str.IsEmpty())
	{	if(filename[0] == '.')
			str = filename.TrimLeft(1);
		else
			str = filename;
	}
	
	str.MakeLower();
	if(str == "jpg" || str == "jpeg" || str == "jfif")
		return ImageCodec_JPG;
	else if(str == "png")
		return ImageCodec_PNG;
	else if(str == "pfm")
		return ImageCodec_PFM;
#ifdef PLATFORM_INTEL_IPP_EXR_CODEC
	else if(str == "exr")
		return ImageCodec_EXR_PIZ;
#endif
	else if(str == "gif")
		return ImageCodec_GIF;
#ifdef PLATFORM_INTEL_IPP_WEBP_CODEC
	else if (str == "webp")
		return ImageCodec_WEBP;
#endif 	
	else 
		return ImageCodec_Unk;

}

bool ImageEncoder::Encode(LPCBYTE pData,int Channel,int Width,int Height,int Step, DWORD codec)
{
	m_BufferUsedLen = 0;
	ASSERT(Channel>=0 && Channel<=4);
	if(Width == 0 || Height == 0)return false;

	if(codec == ImageCodec_PNG)
	{
		if(!_SetBufferSize(Channel*Width*Height + 1024))
			return false;

		struct _write_function: public rt::OStream_Ref
		{	_write_function(LPCBYTE p, UINT len):rt::OStream_Ref(p, len){}
			static void _func(png_structp png, png_bytep buf, png_size_t size)
			{	png_size_t check = ((_write_function*)(png->io_ptr))->Write(buf,(UINT)size);
				if(check != size)longjmp(png->jmp_buf_local, 1);
			}
		};

		_write_function _png_io(m_TempBuffer, (UINT)m_TempBuffer.GetSize());
		png_structp png_ptr = nullptr;
		png_infop info_ptr = nullptr;
        /* initialize stuff */
		if(	(png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL)) &&
			(info_ptr = png_create_info_struct(png_ptr))
		)
		{	
			if(!setjmp(png_jmpbuf(png_ptr)))
			{
				int color_type[] = {0, 4, 2, 6};
				png_set_write_fn(png_ptr, &_png_io, _write_function::_func,NULL);
				png_set_IHDR(png_ptr, info_ptr, Width, Height, 8, color_type[Channel-1], 
							 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

				png_write_info(png_ptr, info_ptr);

				png_bytep* rows = (png_bytep*)alloca(sizeof(png_bytep)*Height);
				for(int i=0;i<Height;i++)
					rows[i] = (png_bytep)(pData + i*Step);

				png_write_image(png_ptr, rows);
				png_write_end(png_ptr, NULL);
				if(png_ptr)png_destroy_write_struct(&png_ptr, &info_ptr);
				m_BufferUsedLen = (int)_png_io.GetLength();
				return true;
			}
			if(png_ptr)png_destroy_write_struct(&png_ptr, &info_ptr);
		}
	}
	else if(codec == ImageCodec_JPG)
	{
		// Use libjpg instead
		if(Channel != 1 && Channel != 3)return false; // consider libjpeg-turbo to support RGBA

		bool ret = false;

		struct jpeg_compress_struct cinfo;
		struct jpeg_error_mgr jerr;
		
		cinfo.err = jpeg_std_error(&jerr);
		jpeg_create_compress(&cinfo);
#ifdef NEED_SIGNAL_CATCHER
		enable_signal_catcher((j_common_ptr) &cinfo);
#endif
		cinfo.image_width = Width;
		cinfo.image_height = Height;
		cinfo.input_components = Channel;
		cinfo.in_color_space = Channel==1?JCS_GRAYSCALE:JCS_RGB;

		jpeg_set_defaults(&cinfo);
		cinfo.dct_method = JDCT_ISLOW;
		jpeg_set_quality(&cinfo, m_Quality, false);

		if(!_SetBufferSize(Channel*Width*Height + 1024))
			return false;

		LPBYTE buf = m_TempBuffer.Begin();
		m_BufferUsedLen = (int)m_TempBuffer.GetSize();
		jpeg_mem_dest(&cinfo, &buf, (unsigned long*)&m_BufferUsedLen);

		jpeg_start_compress(&cinfo, true);
		LPCBYTE src = pData;
		for(int lines = 0;
			lines < Height;
			src += Step
		)
		{	int written = jpeg_write_scanlines(&cinfo, (JSAMPARRAY)&src, 1);
			if(!written)
			{	jpeg_destroy_compress(&cinfo);
				return false;
			}
			lines++;
		}

		jpeg_finish_compress(&cinfo);
		jpeg_destroy_compress(&cinfo);

		return true;
	}
#ifdef PLATFORM_INTEL_IPP_WEBP_CODEC
	else if (codec == ImageCodec_WEBP)
	{
		if (Channel != 3 && Channel != 4) return false; // only support RGB &&RGBA
		LPBYTE outPut = nullptr;
		if (Channel == 3)
		{
			m_BufferUsedLen = (int)WebPEncodeRGB(pData, Width, Height, Step, (float)m_Quality, &outPut);
		}
		else
		{
			ASSERT(Channel == 4);
			m_BufferUsedLen = (int)WebPEncodeRGBA(pData, Width, Height, Step, (float)m_Quality, &outPut);
		}
		VERIFY(m_TempBuffer.SetSize(m_BufferUsedLen));
		m_TempBuffer.CopyFrom(outPut);
		WebPFree(outPut);
		return m_BufferUsedLen; //compress failed if zero-sized
	}
	else if (codec == ImageCodec_WEBP_LOSSLESS)
	{
		if (Channel != 3 && Channel != 4) return false; // only support RGB &&RGBA
		LPBYTE outPut = nullptr;
		if (Channel == 3)
		{
			m_BufferUsedLen = (int)WebPEncodeLosslessRGB(pData, Width, Height, Step, &outPut);
		}
		else
		{
			ASSERT(Channel == 4);
			m_BufferUsedLen = (int)WebPEncodeLosslessRGBA(pData, Width, Height, Step, &outPut);
		}
		VERIFY(m_TempBuffer.SetSize(m_BufferUsedLen));
		m_TempBuffer.CopyFrom(outPut);
		WebPFree(outPut);
		return m_BufferUsedLen; //compress failed if zero-sized
	}
#endif // PLATFORM_INTEL_IPP_WEBP_CODEC	
	else if(codec == ImageCodec_GIF)
	{
		int colormap_size = GetEnv()->GifEncodeColorCount;
		ColorMapObject *colormap;
		colormap = GifMakeMapObject(colormap_size, NULL);

		if(!colormap)return false;

		rt::Buffer<BYTE> bufs;
		LPBYTE out, r, g, b;

		switch(Channel)
		{
		case 1:
			if(!bufs.SetSize(Width*Height*2))return false;

			out = bufs.Begin();
			r = out + Width*Height;
			g = r;
			b = r;

			for(int y=0; y<Height; y++)
			{
				LPCBYTE scanline = pData + y*Step;
				memcpy(r + y*Width, scanline, Width);
			}
			b = g = r;
			break;
		case 3:
			if(!bufs.SetSize(Width*Height*4))return false;

			out = bufs.Begin();
			r = out + Width*Height;
			g = r + Width*Height;
			b = g + Width*Height;

			for(int y=0; y<Height; y++)
			{
				LPCBYTE scanline = pData + y*Step;
				int offset = y*Width;
				for(int x=0; x<Width; x++)
				{
					r[x + offset] = scanline[x*3];
					g[x + offset] = scanline[x*3+1];
					b[x + offset] = scanline[x*3+2];
				}
			}
			break;
		case 4:
			if(!bufs.SetSize(Width*Height*4))return false;

			out = bufs.Begin();
			r = out + Width*Height;
			g = r + Width*Height;
			b = g + Width*Height;

			for(int y=0; y<Height; y++)
			{
				LPCBYTE scanline = pData + y*Step;
				int offset = y*Width;
				for(int x=0; x<Width; x++)
				{
					g[x + offset] = scanline[x*4+1];
					r[x + offset] = scanline[x*4];
					b[x + offset] = scanline[x*4+2];
				}
			}
			break;
		default: return false;
		}

		if(GifQuantizeBuffer(Width, Height, &colormap_size, r, g, b,  out, colormap->Colors) == GIF_ERROR)
			return false;

		if(!_SetBufferSize(Width*Height + colormap_size*3 + 1024))return false;

		struct data
		{	LPCVOID pDataOut;
			UINT	DataLen;
			int&	Used;

			data(int &usedlen):Used(usedlen){}
			static int write(GifFileType * g, const GifByteType * in, int s)
			{	
				auto& d = *(data*)g->UserData;
				s = rt::min((UINT)s, d.DataLen - d.Used);
				
				memcpy(((LPBYTE)d.pDataOut) + d.Used, in, s);
				d.Used += s;
				return s;
			}
		};
		data d(m_BufferUsedLen);
		d.pDataOut = m_TempBuffer.Begin();
		d.DataLen = (UINT)m_TempBuffer.GetSize();

		GifFileType* gif = EGifOpen(&d, data::write, NULL);
		if(	gif &&
			EGifPutScreenDesc(gif, Width, Height, colormap_size, 0, colormap) == GIF_OK &&
			EGifPutImageDesc(gif, 0, 0, Width, Height, 0, NULL) == GIF_OK
		)
		{
			LPCBYTE ptr = out;
			for(int i = 0; i < Height; i++)
			{
				if(EGifPutLine(gif, (GifPixelType*)ptr, Width) == GIF_ERROR)
					goto GIF_ENCODE_FAILED;

				ptr += Width;
			}

			if(EGifCloseFile(gif, NULL) == GIF_OK)
				return true;
		}

GIF_ENCODE_FAILED:
		if(gif)EGifCloseFile(gif, NULL);
	}

	return false;
}

} // namespace ipp

#ifdef PLATFORM_INTEL_IPP_EXR_CODEC
#include "openexr/OpenEXR_inc.cpp"
#endif 

