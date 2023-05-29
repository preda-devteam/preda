#include "../rt/string_type_ops.h"
#include "kernel.h"


namespace os
{

namespace _details
{
template<typename CTX>
CTX crc_core(LPCVOID data_in, SIZE_T length, CTX crc, const CTX table[256])
{
	LPBYTE data = (LPBYTE)data_in;
	LPBYTE end = data + length;
    while(data < end)
         crc = table[(crc ^ *data++) & 0xFFU] ^ (crc >> 8);

    return crc;
} 

template<typename CTX>
struct crc_table_init
{	
	CTX table[256];
	crc_table_init(CTX polynomial)
	{	typedef typename rt::TypeTraits<CTX>::t_Signed SignedType;
		for(unsigned int i = 0; i <= 0xFF; i++)
		{
			CTX crc = i;
			for (unsigned int j = 0; j < 8; j++)
				crc = (crc >> 1) ^ (-SignedType(crc & 1) & polynomial);
			table[i] = crc;
		}
	}
};
} // namespace _details

DWORD crc32c(LPCVOID data, SIZE_T length, DWORD crc)
{
	// fomulated as in http://www.rasterbar.com/products/libtorrent/dht_sec.html
	static const _details::crc_table_init<DWORD> _(0x82F63B78U);
	return ~_details::crc_core(data, length, ~crc, _.table);
}

#define XXTEA_DELTA 0x9e3779b9
#define XXTEA_MX (((z>>5^y<<2) + (y>>3^z<<4)) ^ ((sum^y) + (key[(p&3)^e] ^ z)))
void xxtea_encode(LPCVOID key_16bytes, LPVOID data, UINT n)
{
	ASSERT(n);
	ASSERT((n&7) == 0);
	n /= 4;
	uint32_t y, z, sum;
    uint32_t p, rounds, e;

	auto* key = (const DWORD*)key_16bytes;
	auto* v = (DWORD*)data;
    rounds = 6 + 52/n;
    sum = 0;
    z = v[n-1];
    do {
		sum += XXTEA_DELTA;
		e = (sum >> 2) & 3;
		for (p=0; p<n-1; p++)
		{
			y = v[p+1]; 
			z = v[p] += XXTEA_MX;
		}
		y = v[0];
		z = v[n-1] += XXTEA_MX;
    } while (--rounds);
}

void xxtea_decode(LPCVOID key_16bytes, LPVOID cipher, UINT n)
{
 	ASSERT(n);
	ASSERT((n&7) == 0);
	n /= 4;

	uint32_t y, z, sum;
    uint32_t p, rounds, e;

	auto* key = (const DWORD*)key_16bytes;
	auto* v = (DWORD*)cipher;
	rounds = 6 + 52/n;
    sum = rounds*XXTEA_DELTA;
    y = v[0];
    do {
		e = (sum >> 2) & 3;
		for (p=n-1; p>0; p--)
		{
			z = v[p-1];
			y = v[p] -= XXTEA_MX;
		}
		z = v[n-1];
		y = v[0] -= XXTEA_MX;
		sum -= XXTEA_DELTA;
    } while (--rounds);
}
#undef XXTEA_MX
#undef XXTEA_DELTA

DWORD crc32(LPCVOID data, SIZE_T length, DWORD crc)
{
	static const _details::crc_table_init<DWORD> _(0xEDB88320U);

	rt::SwapByteOrder(crc);
	crc = ~_details::crc_core(data, length, ~crc, _.table);
	rt::SwapByteOrder(crc);
	return crc;
}

ULONGLONG crc64(LPCVOID data, SIZE_T length, ULONGLONG crc)
{
	static const _details::crc_table_init<ULONGLONG> _(0xC96C5795D7870F42ULL);
	return _details::crc_core(data, length, crc, _.table);
}

SIZE_T UTF8EncodeLength(LPCU16CHAR pIn, SIZE_T len)	// number of char
{
	SIZE_T outlen = 0;
	for(SIZE_T i=0;i<len;i++)
	{
		WORD c = (WORD&)pIn[i];
		if(c <= 0x7f)
			outlen++;
		else if(c <= 0x7ff)
			outlen+=2;
		else if(c <= 0xD7ff || c >= 0xE000)
			outlen+=3;
		else
		{	// unicode BMP
			i++;
			if(((WORD&)pIn[i] & 0xfc00) == 0xdc00)
				outlen+=4; // otherwise the previous word will be skipped
		}
	}

	return outlen;
}

SIZE_T UTF8Encode(LPCU16CHAR pIn, SIZE_T len, LPSTR pOut)
{
	LPSTR p = pOut;
	for(SIZE_T i=0;i<len;i++)
	{
		WORD c = (WORD&)pIn[i];
		if(c <= 0x7fu)
		{	*p = (char)c;
			p++;
		}
		else if(c <= 0x7ffu)	// 110xxxxx 	10xxxxxx
		{	*((WORD*)p) = 0x80c0u | ((c>>6)&0x1fu) | ((c&0x3fu)<<8);
			p+=2;
		}
		else if(c <= 0xD7ffu || c >= 0xE000) // 1110xxxx 	10xxxxxx 	10xxxxxx
		{	*((WORD*)p) = 0x80e0u | ((c>>12)&0xfu) | ((c<<2)&0x3f00u);
			p[2] = 0x80 | (c&0x3fu);
			p+=3;
		}
		else // unicode BMP W1 = 110110aa aaaaaaaa W2 = 110111 bbbb bbbbbb
		{					//   11110xxx	10xxxxxx	10xxxxxx	10xxxxxx	
							//	      0aa     aaaaaa      aabbbb      bbbbbb
			i++;
			DWORD b = (WORD&)pIn[i];	
			if((b & 0xfc00u) == 0xdc00u)
			{
				*((DWORD*)p) = 0x808080f0u | ((c>>8)&0x3u) | ((c<<6)&0x3f00u) | ((c&3u)<<20)
										   | ((b<<10)&0xf0000u) | ((b<<24)&0x3f000000u);
				p+=4;
			}
		}
	}

	return (UINT)(p - pOut);
}

SIZE_T UTF8ByteOffset(LPCSTR pIn, SIZE_T len, SIZE_T num_of_utf8_char) // counting number of utf8 chatactors
{
	SIZE_T outlen = 0;
	SIZE_T i=0;
	for(;outlen<num_of_utf8_char;outlen++)
	{
		if(i>=len)return 0;

		BYTE c = pIn[i];
		if(c <= 0x7f)
		{	i++;
		}
		else if((c&0xe0) == 0xc0)	// 110xxxxx 	10xxxxxx
		{	i+=2;
		}
		else if((c&0xf0) == 0xe0)	// 1110xxxx 	10xxxxxx 	10xxxxxx
		{	i+=3;
		}
		else if((c&0xf8) == 0xf0)	// 11110xxx		10xxxxxx	10xxxxxx	10xxxxxx
		{	i+=4;
		}
	}
	return i;
}

// UTF8 to UTF16
SIZE_T UTF8DecodeLength(LPCSTR pIn, SIZE_T len)	// number of wchar
{
	SIZE_T outlen = 0;
	for(SIZE_T i=0;i<len;)
	{
		BYTE c = pIn[i];
		if(c <= 0x7fu)
		{	i++;	outlen++;
		}
		else if((c&0xe0u) == 0xc0u)	// 110xxxxx 	10xxxxxx
		{	i+=2;	outlen++;
		}
		else if((c&0xf0u) == 0xe0u)	// 1110xxxx 	10xxxxxx 	10xxxxxx
		{	i+=3;	outlen++;
		}
		else if((c&0xfcu) == 0xf0u)	// 111100xx		10xxxxxx	10xxxxxx	10xxxxxx 
		{	i+=4;	outlen+=2;
		}
		else // (only 111100xx can be convert to unicode BMP)
			i++;
	}
	return outlen;
}

SIZE_T UTF8Decode(LPCSTR pIn, SIZE_T len, LPU16CHAR pOut)		// number of wchar
{
	LPU16CHAR p = pOut;
	for(SIZE_T i=0;i<len;)
	{
		BYTE c = pIn[i];
		if(c <= 0x7f)
		{	*p++ = c;
			i++;
		}
		else if((c&0xe0) == 0xc0)	// 110xxxxx 	10xxxxxx
		{	*p++ = ((c&0x1fu)<<6) | (pIn[i+1]&0x3fu);
			i+=2;
		}
		else if((c&0xf0) == 0xe0)	// 1110xxxx 	10xxxxxx 	10xxxxxx
		{	*p++ = ((c&0xfu)<<12) | ((pIn[i+1]&0x3fu)<<6) | (pIn[i+2]&0x3fu);
			i+=3;
		}
		else if((c&0xfcu) == 0xf0u)	// unicode BMP W1 = 110110aa aaaaaaaa W2 = 110111 bbbb bbbbbb
		{							//   11110xxx	10xxxxxx	10xxxxxx	10xxxxxx	
									//	      0aa     aaaaaa      aabbbb      bbbbbb
			WORD k = pIn[i+2];
			*p++ = 0xD800u | ((c&3u)<<8) | ((pIn[i+1]&0x3fu)<<2) | ((k>>4)&3u);
			*p++ = 0xDC00u | ((k&0xfu)<<6) | (pIn[i+3]&0x3fu);
			i+=4;
		}
		else // (only 111100xx can be convert to unicode BMP)
			i++;
	}

	return (UINT)(p - pOut);
}

SSIZE_T UTF8EncodeLengthMax(LPCVOID pIn, SIZE_T len, const rt::String_Ref& charset_name, DWORD* pCharsetIndex)
{
	ASSERT(pCharsetIndex);

	if(charset_name.StartsWith(rt::SS("iso-8859-")))
	{	UINT latin_index;
		charset_name.SubStr(9).ToNumber(latin_index);
		if(latin_index <= 10)
		{
			*pCharsetIndex = CHARSET_LATIN_BASE + latin_index;
			return len*2;
		}
		else
		{
			return -1;
		}
	}
	else if(charset_name == rt::SS("shift-jis"))
	{	*pCharsetIndex = CHARSET_SHIFT_JIS;
		return (len+1)/2*3;
	}
	else if(charset_name.StartsWith(rt::SS("gb")))
	{
		UINT gb_num;
		charset_name.SubStr(2).ToNumber(gb_num);
		switch(gb_num)
		{
		case 2312: *pCharsetIndex = CHARSET_GB_2312; break;
		case 18030:*pCharsetIndex = CHARSET_GB_18030; break;
		default: return -1;
		}
		return (len+1)/2*3; 
	}
	else if(charset_name == rt::SS("big5"))
	{	*pCharsetIndex = CHARSET_BIG5;
		return (len+1)/2*3;
	}
	else if(charset_name.StartsWith("ks") || charset_name == rt::SS("korean"))
	{
		*pCharsetIndex = CHARSET_KOREAN;
		return (len+1)/2*3;
	}
	else if(charset_name == rt::SS("utf-16"))
	{
		*pCharsetIndex = CHARSET_UTF_16;
		return (len+1)/2*3;
	}
	else if(charset_name == rt::SS("utf-8"))
	{
		*pCharsetIndex = CHARSET_UTF_8;
		return len;
	}
	else if(charset_name.StartsWith("koi8-r"))
	{
		*pCharsetIndex = CHARSET_KOI8_R;
		return len*2;
	}
	else if(charset_name.StartsWith("koi8-u"))
	{
		*pCharsetIndex = CHARSET_KOI8_U;
		return len*2;
	}
	else
	{	return -1;
	}
}

SIZE_T UTF8Encode(LPCVOID pIn, SIZE_T len, LPSTR pOut, DWORD charset_index)
{
	if(charset_index == CHARSET_UTF_8)
	{	memcpy(pOut, pIn, len);
		pOut[len] = 0;
		return len;
	}
	if(charset_index == CHARSET_UTF_16)
	{	SIZE_T outlen = UTF8Encode((LPCU16CHAR)pIn, len/2, pOut);
		pOut[outlen] = 0;
		return outlen;
	}

#ifdef PLATFORM_WIN
	LPU16CHAR buf;
	rt::Buffer<U16CHAR>	_temp;
	if(len*2 > 64*1024)
	{	// allocate on heap
		_temp.SetSize(len);
		buf = _temp;
	}
	else
	{	// allocate on stack
		buf = (LPU16CHAR)alloca(2*len);
	}
	int outlen = MultiByteToWideChar(charset_index, 0, (LPCCH)pIn, (int)len, buf, (int)len);
	return UTF8Encode(buf, outlen, pOut);
#else
	ASSERT(0);
	return 0;
#endif
}

namespace _details
{
INLFUNC bool _isb64(int c)
{
	return	(c>='a' && c<='z') ||
			(c>='A' && c<='Z') ||
			(c>='0' && c<='9') ||
			c == '+' ||
			c == '/';
}
} // namespace _details


bool Base64Encode(const rt::String_Ref&in, rt::String& out)
{
	if(!out.SetLength(Base64EncodeLength(in.GetLength())))
		return false;

	Base64Encode(out.Begin(), in.Begin(), in.GetLength());
	return true;
}

bool Base64Decode(const rt::String_Ref&in, rt::String& out)
{
	out.SetLength(Base64DecodeLength(in.Begin(), in.GetLength()));
	SIZE_T actual_len = out.GetLength();
	bool ret = Base64Decode(out.Begin(), &actual_len, in.Begin(), in.GetLength());
	out.SetLength(actual_len);
	return ret;
}

SIZE_T Base64EncodeLength(SIZE_T len)
{
	return (len+2)/3*4;
}

void Base64Encode(LPSTR pBase64Out,LPCVOID pData, SIZE_T data_len)
{
	static const char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	
	LPCBYTE p = (LPCBYTE)pData;
	for(;data_len>=3;data_len-=3,p+=3,pBase64Out+=4)
	{
		pBase64Out[0] = table[p[0]>>2];
		pBase64Out[1] = table[((p[0]&0x3)<<4)|(p[1]>>4)];
		pBase64Out[2] = table[((p[1]&0xf)<<2)|(p[2]>>6)];
		pBase64Out[3] = table[p[2]&0x3f];
	}

	if(data_len == 1)
	{
		pBase64Out[0] = table[p[0]>>2];
		pBase64Out[1] = table[((p[0]&0x3)<<4)];
		pBase64Out[2] = '=';
		pBase64Out[3] = '=';
		//pBase64Out[4] = '\0';
	}
	else if(data_len == 2)
	{
		ASSERT(data_len == 2);
		pBase64Out[0] = table[p[0]>>2];
		pBase64Out[1] = table[((p[0]&0x3)<<4)|(p[1]>>4)];
		pBase64Out[2] = table[((p[1]&0xf)<<2)];
		pBase64Out[3] = '=';
		//pBase64Out[4] = '\0';
	}
	//else
	//	pBase64Out[0] = '\0';
}

SIZE_T Base64DecodeLength(LPCSTR pBase64, SIZE_T str_len)
{
	if(str_len<=3)return 0;

	SSIZE_T fulllen = (str_len+3)/4*3;
	SSIZE_T miss = (4 - (str_len&3))&3;

	if(_details::_isb64(pBase64[str_len-2]) && _details::_isb64(pBase64[str_len-1]) && miss <= 2)
	{	
		fulllen -= miss;
	}
	else if(_details::_isb64(pBase64[str_len-2]) && !_details::_isb64(pBase64[str_len-1]))
	{
		fulllen -= (miss + 1);
	}
	else if(!_details::_isb64(pBase64[str_len-2]) && !_details::_isb64(pBase64[str_len-1]) && miss == 0)
	{
		fulllen -= 2;
	}
	else return fulllen;

	return rt::max((SSIZE_T)0, fulllen);
}

bool Base64Decode(LPVOID pDataOut, SIZE_T* pDataOutLen,LPCSTR pBase64, SIZE_T str_len)
{
	static const int rev_table[80] = // base on 2B
	{
		62,-1,-1,-1,			//'+' 2B,2C,2D,2E,
		63,						//'/' 2F
		52,53,54,55,56,57,58,59,60,61,	// '0' - '9', 30 - 39
		-1,-1,-1,-1,-1,-1,-1,	// '=', 3A, 3B, 3C, |3D|, 3E, 3F, 40
		0,1,2,3,4,5,6,7,8,9,	// 'A'-'Z', 41 - 5A
		10,11,12,13,14,15,16,17,18,19,
		20,21,22,23,24,25,		
		-1,-1,-1,-1,-1,-1,		// 5B 5C 5D 5E 5F 60
		26,27,28,29,30,31,32,33,34,35, // 'a'-'z' 61 - 7A
		36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51
	};

	LPBYTE p = (LPBYTE)pDataOut;

	int a[4];

	for(;str_len>4;str_len-=4,pBase64+=4,p+=3)
	{
		if(rt::IsInRange_CC<int>(pBase64[0],0x2b,0x7a) && (a[0]=rev_table[pBase64[0]-0x2b])>=0){}
		else break;
		if(rt::IsInRange_CC<int>(pBase64[1],0x2b,0x7a) && (a[1]=rev_table[pBase64[1]-0x2b])>=0){}
		else break;
		if(rt::IsInRange_CC<int>(pBase64[2],0x2b,0x7a) && (a[2]=rev_table[pBase64[2]-0x2b])>=0){}
		else break;
		if(rt::IsInRange_CC<int>(pBase64[3],0x2b,0x7a) && (a[3]=rev_table[pBase64[3]-0x2b])>=0){}
		else break;

		p[0] = (a[0]<<2) | (a[1]>>4);
		p[1] = ((a[1]&0xf)<<4) | (a[2]>>2);
		p[2] = ((a[2]&0x3)<<6) | a[3];
	}

	*pDataOutLen = (p - (LPBYTE)pDataOut);
	if(str_len == 0)return true;

	//int remaining = (int)rt::min(str_len, (SIZE_T)4);
	int miss = (4 - (str_len&3))&3;

	char last4char[4];
	*((DWORD*)last4char) = 0x3d3d3d3d; // all '='
	memcpy(last4char, pBase64, 4 - miss);

	if(rt::IsInRange_CC<int>(last4char[0],0x2b,0x7a) && (a[0]=rev_table[last4char[0]-0x2b])>=0){}
	else return false;
	if(rt::IsInRange_CC<int>(last4char[1],0x2b,0x7a) && (a[1]=rev_table[last4char[1]-0x2b])>=0){}
	else return false;

	if(_details::_isb64(last4char[2]) && _details::_isb64(last4char[3]))
	{
		(*pDataOutLen) += 3;

		a[2]=rev_table[last4char[2]-0x2b];
		a[3]=rev_table[last4char[3]-0x2b];

		p[0] = (a[0]<<2) | (a[1]>>4);
		p[1] = ((a[1]&0xf)<<4) | (a[2]>>2);
		p[2] = ((a[2]&0x3)<<6) | a[3];

		return str_len <= 4;
	}
	else if(_details::_isb64(last4char[2]) && !_details::_isb64(last4char[3]))
	{
		(*pDataOutLen) += 2;
		a[2]=rev_table[last4char[2]-0x2b];

		p[0] = (a[0]<<2) | (a[1]>>4);
		p[1] = ((a[1]&0xf)<<4) | (a[2]>>2);

		return str_len <= 4;
	}
	else if(!_details::_isb64(last4char[2]) && !_details::_isb64(last4char[3]))
	{
		(*pDataOutLen) += 1;
		
		p[0] = (a[0]<<2) | (a[1]>>4);

		return str_len <= 4;
	}

	return false;
}

SIZE_T Base16EncodeLength(SIZE_T len){ return len*2; }
SIZE_T Base16DecodeLength(SIZE_T len){ return len/2; }

void Base16Encode(LPSTR pBase16Out,LPCVOID pData_in, SIZE_T data_len)
{
	LPCBYTE pData = (LPCBYTE)pData_in;
	for(SIZE_T i=0;i<data_len;i++)
	{
		int c1 = pData[i]>>4;
		int c2 = pData[i]&0xf;
		pBase16Out[2*i+0] = (c1>9)?('a'+c1-10):('0'+c1);
		pBase16Out[2*i+1] = (c2>9)?('a'+c2-10):('0'+c2);
	}
}

bool Base16Decode(LPVOID pDataOut_in,SIZE_T data_len,LPCSTR pBase16, SIZE_T str_len)
{
	LPBYTE pDataOut = (LPBYTE)pDataOut_in;

	if(str_len != data_len*2)return false;
	for(SIZE_T i=0;i<data_len;i++)
	{
		int c[2] = { pBase16[2*i+0], pBase16[2*i+1] };

		for(int j=0;j<2;j++)
		{
			if(c[j]<='9')
			{	if(c[j]<'0')return false;
				c[j] -= '0';
			}
			else if(c[j]>='A' && c[j]<='F')
			{	c[j] -= 'A' - 10;
			}
			else if(c[j]>='a' && c[j]<='f')
			{	c[j] -= 'a' - 10;
			}
			else return false;
		}

		pDataOut[i] = (c[0]<<4) | c[1];
	}

	return true;
}

bool Base16Encode(const rt::String_Ref&in, rt::String& out)
{
	out.SetLength(Base16EncodeLength(in.GetLength()));
	Base16Encode(out, in.Begin(), in.GetLength());
	return true;
}

bool Base16Decode(const rt::String_Ref&in, rt::String& out)
{
	out.SetLength(Base16DecodeLength(in.GetLength()));
	return Base16Decode(out.Begin(), out.GetLength(), in.Begin(), in.GetLength());
}

namespace _details
{
	// Crockford's Base32 - http://en.wikipedia.org/wiki/Base32
	//value		encode	decode			value	encode	decode
	//0			0		0 o O			16		G		g G
	//1			1		1 i I l L		17		H		h H
	//2			2		2				18		J		j J
	//3			3		3				19		K		k K
	//4			4		4				20		M		m M
	//5			5		5				21		N		n N
	//6			6		6				22		P		p P
	//7			7		7				23		Q		q Q
	//8			8		8				24		R		r R
	//9			9		9				25		s		s S
	//10		A		a A				26		T		t T
	//11		B		b B				27		V		v V u U
	//12		C		c C				28		W		w W
	//13		D		d D				29		X		x X
	//14		E		e E				30		Y		y Y
	//15		F		f F				31		Z		z Z

	static const int _base32_crockford_decoding['z' - '0' + 1] = 
	{
		0,1,2,3,4, 5,6,7,8,9,	/*0-9*/
		-1,-1,-1,-1,-1,-1,-1,	/*:	; <	= >	? @	*/
		10,11,12,13,14,15,16,17,/*A-H*/	
		1,						/* I = 1*/
		18,19,					/* J K */	
		1,						/*L	= 1*/
		20,21,					/*M	N */	
		0,						/*O = 0	*/
		22,						/*P	*/		
		23,24,25,26,			/*QRST */	
		27,27,					/*U V */	
		28,29,30,31,			/*WXYZ*/
		-1,-1,-1,-1,			/*[	\ ] ^*/
		-1,						/* _ */
		-1,						/* ` */	
		10,11,12,13,14,15,16,17,/*a-h*/	
		1,						/* i = 1*/
		18,19,					/* j k */	
		1,						/*l	= 1*/
		20,21,					/*m	n */	
		0,						/*o = 0	*/
		22,						/*p	*/		
		23,24,25,26,			/*qrst */	
		27,27,					/*u v */
		28,29,30,31,			/*wxyz*/
	}; 															//			1		  2			3
																//01234567890123456789012345678901
	static const char _base32_crockford_encoding_uppercase[33] = "0123456789ABCDEFGHJKMNPQRSTVWXYZ";
	static const char _base32_crockford_encoding_lowercase[33] = "0123456789abcdefghjkmnpqrstvwxyz";
																//			1		  2			3
																//01234567890123456789012345678901
	static const char _base32_extendhex_encoding_uppercase[33] = "0123456789ABCDEFGHIJKLMNOPQRSTUV";
	static const char _base32_extendhex_encoding_lowercase[33] = "0123456789abcdefghijklmnopqrstuv";

	template<bool uppercase = true>
	struct table_extend_hex
	{
		FORCEINL static bool decode(int&b, int d)
		{	if(d>='0' && d<='9'){ b = d - '0'; return false;}
			else if(d>='a' && d<='v'){ b = d - 'a' + 10; return false; }
			else if(d>='A' && d<='V'){ b = d - 'A' + 10; return false; }
			else return true;
		}
		FORCEINL static int encode(int d){ return _base32_extendhex_encoding_uppercase[d]; }
	};
		template<> struct table_extend_hex<false>: public table_extend_hex<true>
		{	FORCEINL static int encode(int d){ return _base32_extendhex_encoding_lowercase[d]; }
		};

	template<bool uppercase = true>
	struct table_crockford
	{
		FORCEINL static bool decode(int&b, int d)
		{	
			if(d>='0' && d<='z'){ b = _base32_crockford_decoding[d - '0']; return false; }
			return true;
		}
		FORCEINL static int encode(int d){ return _base32_crockford_encoding_uppercase[d]; }
	};
		template<> struct table_crockford<false>: public table_crockford<true>
		{	FORCEINL static int encode(int d){ return _base32_crockford_encoding_lowercase[d]; }
		};

	template<typename BASE32_TABLE>
	FORCEINL void _Base32Encode(LPSTR p, LPCVOID pdata, SIZE_T data_len)
	{
		LPCBYTE d = (LPCBYTE)pdata;
		LPCBYTE e = d + data_len;
		for(;(d + 4)<e;d+=5, p+=8)
		{	
			p[0] = BASE32_TABLE::encode(d[0]>>3);
			p[1] = BASE32_TABLE::encode(((d[0]&0x7)<<2) | (d[1]>>6));
			p[2] = BASE32_TABLE::encode((d[1]>>1) & 0x1f);
			p[3] = BASE32_TABLE::encode(((d[1]&1)<<4) | (d[2]>>4));
			p[4] = BASE32_TABLE::encode(((d[2]&0xf)<<1) | (d[3]>>7));
			p[5] = BASE32_TABLE::encode((d[3]>>2) & 0x1f);
			p[6] = BASE32_TABLE::encode(((d[3]&0x3)<<3) | (d[4]>>5));
			p[7] = BASE32_TABLE::encode(d[4]&0x1f);
		}

		if(d == e)return;

		p[0] = BASE32_TABLE::encode(d[0]>>3);
		if(d+1 == e)	// nnnXX
		{	p[1] = BASE32_TABLE::encode((d[0]&0x7) << 2);
			return;
		}

		p[1] = BASE32_TABLE::encode(((d[0]&0x7)<<2) | (d[1]>>6));
		p[2] = BASE32_TABLE::encode((d[1]>>1) & 0x1f);
		if(d+2 == e)	// nXXXX
		{	p[3] = BASE32_TABLE::encode((d[1]&0x1) << 4);
			return;
		}

		p[3] = BASE32_TABLE::encode(((d[1]&1)<<4) | (d[2]>>4));
		if(d+3 == e)	// nnnnX
		{	p[4] = BASE32_TABLE::encode((d[2]&0xf) << 1);
			return;
		}

		p[4] = BASE32_TABLE::encode(((d[2]&0xf)<<1) | (d[3]>>7));
		p[5] = BASE32_TABLE::encode((d[3]>>2) & 0x1f);
		ASSERT(d+4 == e);	// nnXXX
		p[6] = BASE32_TABLE::encode((d[3]&0x3) << 3);

		return;
	}

	template<typename BASE32_TABLE>
	FORCEINL bool _Base32Decode(LPVOID pDataOut, SIZE_T data_len, LPCSTR pBase32, SIZE_T str_len)
	{
		if(os::Base32DecodeLength(str_len) != data_len)return false;

		LPBYTE p = (LPBYTE)pDataOut;
		LPCSTR d = pBase32;
		LPCSTR e = d + str_len;
		for(;(d + 8)<=e; p+=5)
		{
			int b[8];
			if(BASE32_TABLE::decode(b[0], *d++))return false;
			if(BASE32_TABLE::decode(b[1], *d++))return false;
			if(BASE32_TABLE::decode(b[2], *d++))return false;
			if(BASE32_TABLE::decode(b[3], *d++))return false;
			if(BASE32_TABLE::decode(b[4], *d++))return false;
			if(BASE32_TABLE::decode(b[5], *d++))return false;
			if(BASE32_TABLE::decode(b[6], *d++))return false;
			if(BASE32_TABLE::decode(b[7], *d++))return false;

			p[0] = (b[0]<<3) | (b[1]>>2);
			p[1] = (b[1]<<6) | (b[2]<<1) | (b[3]>>4);
			p[2] = (b[3]<<4) | (b[4]>>1);
			p[3] = (b[4]<<7) | (b[5]<<2) | (b[6]>>3);
			p[4] = (b[6]<<5) | b[7];
		}

		if(d == e)return true;

		int t;
		int b[7];
		if(BASE32_TABLE::decode(b[0], *d++))return false;

		if(d+1 == e)
		{		
			if(BASE32_TABLE::decode(t, *d) || (t = t >> 2) > 7)return false;
			p[0] = (b[0]<<3) | t;
			return true;
		}
	
		if(BASE32_TABLE::decode(b[1], *d++))return false;
		p[0] = (b[0]<<3) | (b[1]>>2);
		if(BASE32_TABLE::decode(b[2], *d++))return false;

		if(d+1 == e)
		{	
			if(BASE32_TABLE::decode(t, *d) || (t = t >> 4) > 1)return false;
			p[1] = (b[1]<<6) | (b[2]<<1) | t;
			return true;
		}
	
		if(BASE32_TABLE::decode(b[3], *d++))return false;
		p[1] = (b[1]<<6) | (b[2]<<1) | (b[3]>>4);

		if(d+1 == e)
		{	
			if(BASE32_TABLE::decode(t, *d) || (t = t >> 1) > 16)return false;
			p[2] = (b[3]<<4) | t;
			return true;
		}

		if(BASE32_TABLE::decode(b[4], *d++))return false;
		p[2] = (b[3]<<4) | (b[4]>>1);
		if(BASE32_TABLE::decode(b[5], *d++))return false;

		if(d+1 == e)
		{	
			if(BASE32_TABLE::decode(t, *d) || (t = t >> 3) > 4)return false;
			p[3] = (b[4]<<7) | (b[5]<<2) | t;
			return true;
		}

		return false;
	}
} // namespace _details

SIZE_T Base32DecodeLength(SIZE_T len)
{						    // 0, 1, 2, 3, 4, 5, 6, 7
	static const int tl[] = {  0,-1, 1,-1, 2, 3,-1, 4 } ;
	int tail_len = tl[len&0x7];
	if(tail_len >=0)
		return len/8*5 + tail_len;
	else
		return 0;
}

SIZE_T Base32EncodeLength(SIZE_T len)
{
	return (len*8+4)/5;// + 1;
}

bool Base32CrockfordDecode(LPVOID pDataOut, SIZE_T data_len, LPCSTR pBase32, SIZE_T str_len)
{
	return _details::_Base32Decode<_details::table_crockford<>>(pDataOut, data_len, pBase32, str_len);
}

void Base32CrockfordEncode(LPSTR pBase32Out, LPCVOID pData, SIZE_T data_len)
{
	_details::_Base32Encode<_details::table_crockford<true>>(pBase32Out, pData, data_len);
}

void Base32CrockfordEncodeLowercase(LPSTR pBase32Out,LPCVOID pData, SIZE_T data_len)
{
	_details::_Base32Encode<_details::table_crockford<false>>(pBase32Out, pData, data_len);
}

bool Base32Decode(LPVOID pDataOut,SIZE_T data_len,LPCSTR pBase32, SIZE_T str_len)
{
	return _details::_Base32Decode<_details::table_extend_hex<>>(pDataOut, data_len, pBase32, str_len);
}

void Base32Encode(LPSTR pBase32Out,LPCVOID pData, SIZE_T data_len)
{
	_details::_Base32Encode<_details::table_extend_hex<true>>(pBase32Out, pData, data_len);
}

void Base32EncodeLowercase(LPSTR pBase32Out,LPCVOID pData, SIZE_T data_len)
{
	_details::_Base32Encode<_details::table_extend_hex<false>>(pBase32Out, pData, data_len);
}

void UrlEncode(const rt::String_Ref& url, rt::String& encoded_url)
{
	encoded_url.SetLength(url.GetLength()*3);
	encoded_url.SetLength(UrlEncode((LPCSTR)url.Begin(), (UINT)url.GetLength(), (LPSTR)encoded_url.Begin()));
}

UINT UrlEncode(LPCSTR url, UINT url_len, LPSTR encoded_url)
{
	UINT out_len = 0;
	for(UINT i=0;i<url_len;i++)
	{
		if(	(url[i]>='a' && url[i]<='z') ||
			(url[i]>='A' && url[i]<='Z') ||
			(url[i]>='0' && url[i]<='9') ||
			url[i] == '-' ||
			url[i] == '_' ||
			url[i] == '.' ||
			url[i] == '~'
		)
		{	encoded_url[out_len++] = url[i];
		}
		else
		{	encoded_url[out_len++] = '%';

			rt::tos::Binary<> code(&url[i], 1);

			encoded_url[out_len++] = code[0];
			encoded_url[out_len++] = code[1];
		}
	}

	return out_len;
}

UINT UrlDecode(LPCSTR encoded_url, UINT encoded_url_len, LPSTR url)  // return encoded length
{
	UINT out_len = 0;
	for(UINT i=0;i<encoded_url_len;i++)
	{
		if(encoded_url[i] == '%')
		{
			int c1 = encoded_url[i+1];
			int c2 = encoded_url[i+2];

			if(c1>='0' && c1<='9')
				c1 -= '0';
			else if(c1>='A' && c1<='F')
				c1 -= c1-'A' + 10;
			else if(c1>='a' && c1<='f')
				c1 -= c1-'a' + 10;
			else break;

			if(c2>='0' && c2<='9')
				c2 -= '0';
			else if(c2>='A' && c2<='F')
				c2 = c2-'A' + 10;
			else if(c2>='a' && c2<='f')
				c2 = c2-'a' + 10;
			else break;

			url[out_len++] = (c1<<4) | c2;
			i+=2;
		}
		else
		{	url[out_len++] = encoded_url[i];
		}
	}

	return out_len;
}

void UrlDecode(const rt::String_Ref& encoded_url, rt::String& url)
{
	url.SetLength(encoded_url.GetLength());
	url.SetLength(UrlDecode(encoded_url.Begin(), (UINT)encoded_url.GetLength(), url.Begin()));
}

} // namespace os

