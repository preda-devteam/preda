#pragma once

/**
 * @file runtime_base.h
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
/** \defgroup runtime_base runtime_base
 * @ingroup rt
 *  @{
 */
#ifndef __cplusplus
#error Not compiled as C++, use .mm instead of .m on Mac/iOS
#endif

#include <limits.h>
#include <float.h>
#include <sstream>
#include <time.h>
#include <cmath>

#include "../os/predefines.h"

#if defined(PLATFORM_WIN)
#include <intrin.h>
#endif

#if defined(PLATFORM_MAC)
#include <x86intrin.h>
#endif

#if defined(PLATFORM_IOS)
#endif

#if defined(PLATFORM_LINUX)
#include <cstring>
#include <x86intrin.h>
#endif


///////////////////////////////////////////////////////
// Hash map/set
#if defined(PLATFORM_IOS) || defined(PLATFORM_ANDROID) || defined(PLATFORM_MAC) || (defined(PLATFORM_WIN) && ( _MSC_VER >= 1900 )) || defined(PLATFORM_LINUX)

#if __cplusplus == 199711L && !defined(PLATFORM_WIN)
#include <tr1/unordered_map>
#include <tr1/unordered_set>

namespace rt
{
	template<class _Key, class _Tp,
	class _HashFn = std::tr1::hash<_Key> >
	class hash_map: public std::tr1::unordered_map<_Key, _Tp, _HashFn>
    {   typedef _Key	t_Key; typedef _Tp	t_Value;
        public: hash_map(){}
    };
	template<class _Key,
	class _HashFcn  = std::tr1::hash<_Key> >
	class hash_set: public std::tr1::unordered_set<_Key, _HashFcn>
    {   typedef _Key t_Key;
        public: hash_set(){}
    };
}

#else

#include <unordered_map>
#include <unordered_set>

namespace rt
{
	template<class _Key, class _Tp,
	class _HashFn = std::hash<_Key> >
	class hash_map: public std::unordered_map<_Key, _Tp, _HashFn>
    {   typedef _Key	t_Key; typedef _Tp	t_Value;
        public: hash_map(){}
    };
	template<class _Key,
	class _HashFcn  = std::hash<_Key> >
	class hash_set: public std::unordered_set<_Key, _HashFcn>
    {   typedef _Key t_Key;
        public: hash_set(){}
    };
}

#endif

#else
#include <hash_map>
#include <hash_set>
namespace rt
{
    template<class _Kty, class _Ty,
	class _Tr = std::hash_compare<_Kty, std::less<_Kty> >,
	class _Alloc = std::allocator<std::pair<const _Kty, _Ty> > >
    class hash_map: public std::hash_map<_Kty, _Ty, _Tr, _Alloc>
    {   typedef _Kty t_Key; typedef _Ty t_Value;
        public: hash_map(){}
    };
    template<class _Kty,
	class _Tr = std::hash_compare<_Kty, std::less<_Kty> >,
	class _Alloc = std::allocator<_Kty> >
    class hash_set: public std::hash_set<_Kty, _Tr, _Alloc>
    {   typedef _Kty t_Key;
        public: hash_set(){}
    };
}
#endif

namespace rt
{
namespace _details
{
template<typename T>
struct _LOG_FULLDATA: public T{};
}

template<typename T>
INLFUNC const _details::_LOG_FULLDATA<T>& LOG_FULLDATA(const T& x){ return (const _details::_LOG_FULLDATA<T>&)x; }

enum _tagLogType
{
	LOGTYPE_VERBOSE = 0,
	LOGTYPE_UPDATING,
	LOGTYPE_INFORMATIONAL,
	LOGTYPE_HIGHLIGHT,
	LOGTYPE_WARNING,
	LOGTYPE_ERROR,
	LOGTYPE_LEVEL_MASK = 0xff,
	LOGTYPE_IN_CONSOLE = 0x100,
	LOGTYPE_IN_LOGFILE = 0x200,
	LOGTYPE_IN_CONSOLE_FORCE = 0x400,
	LOGTYPE_IN_CONSOLE_PROMPT = 0x800,
	LOGTYPE_MAX,
};
} // namespace rt

///////////////////////////////////////////////////////
namespace os
{	extern void LogWrite(LPCSTR log, LPCSTR file, int line_num, LPCSTR func, int type);
	extern void LogDisplayInConsole(bool yes);
	extern bool LogIsDisplayInConsole();
}

#ifndef PLATFORM_DISABLE_LOG
	#define __LOG_TYPE(x,type)	{	 \
									std::ostringstream _ostr;							\
									_ostr<<x;											\
									::os::LogWrite(	_ostr.rdbuf()->str().c_str(),__FILE__,__LINE__,__FUNCTION__, type); \
								}
    #define _LOGNL				{ ::os::LogWrite("",__FILE__,__LINE__,__FUNCTION__, rt::LOGTYPE_VERBOSE); }
	#define _LOGP				os::LogPrefix()
#else
	#define __LOG_TYPE(x,type)	{}
	#define _LOGNL				{}
	#define _LOGP
#endif

// Log to both console and file
#define _LOG_VERBOSE(x)				__LOG_TYPE(x, rt::LOGTYPE_IN_CONSOLE|rt::LOGTYPE_IN_LOGFILE|rt::LOGTYPE_VERBOSE)
#define _LOG_UPDATING(x)			__LOG_TYPE(x, rt::LOGTYPE_IN_CONSOLE|rt::LOGTYPE_UPDATING)
#define _LOG(x)						__LOG_TYPE(x, rt::LOGTYPE_IN_CONSOLE|rt::LOGTYPE_IN_LOGFILE|rt::LOGTYPE_INFORMATIONAL)
#define _LOG_HIGHLIGHT(x)			__LOG_TYPE(x, rt::LOGTYPE_IN_CONSOLE|rt::LOGTYPE_IN_LOGFILE|rt::LOGTYPE_HIGHLIGHT)
#define _LOG_WARNING(x)				__LOG_TYPE(x, rt::LOGTYPE_IN_CONSOLE|rt::LOGTYPE_IN_LOGFILE|rt::LOGTYPE_WARNING)
#define _LOG_ERROR(x)				__LOG_TYPE(x, rt::LOGTYPE_IN_CONSOLE|rt::LOGTYPE_IN_LOGFILE|rt::LOGTYPE_ERROR)

#define _LOG_POS					__LOG_TYPE(__FUNCTION__<<":L"<<__LINE__<<":"<<__FILE__, rt::LOGTYPE_IN_CONSOLE|rt::LOGTYPE_IN_LOGFILE|rt::LOGTYPE_VERBOSE)
#define _LOG_POS_WARNING			__LOG_TYPE(__FUNCTION__<<":L"<<__LINE__<<":"<<__FILE__, rt::LOGTYPE_IN_CONSOLE|rt::LOGTYPE_IN_LOGFILE|rt::LOGTYPE_WARNING)

// Only Log to console
#define _LOGC_VERBOSE(x)			__LOG_TYPE(x, rt::LOGTYPE_IN_CONSOLE|rt::LOGTYPE_VERBOSE)
#define _LOGC(x)					__LOG_TYPE(x, rt::LOGTYPE_IN_CONSOLE|rt::LOGTYPE_INFORMATIONAL)
#define _LOGC_PROMPT()				__LOG_TYPE("", rt::LOGTYPE_IN_CONSOLE_PROMPT|rt::LOGTYPE_INFORMATIONAL)
#define _LOGC_HIGHLIGHT(x)			__LOG_TYPE(x, rt::LOGTYPE_IN_CONSOLE|rt::LOGTYPE_HIGHLIGHT)
#define _LOGC_WARNING(x)			__LOG_TYPE(x, rt::LOGTYPE_IN_CONSOLE|rt::LOGTYPE_WARNING)
#define _LOGC_ERROR(x)				__LOG_TYPE(x, rt::LOGTYPE_IN_CONSOLE|rt::LOGTYPE_ERROR)
			
#define _LOGC_POS					__LOG_TYPE(__FUNCTION__<<":L"<<__LINE__<<":"<<__FILE__, rt::LOGTYPE_IN_CONSOLE|rt::LOGTYPE_VERBOSE)
#define _LOGC_POS_WARNING			__LOG_TYPE(__FUNCTION__<<":L"<<__LINE__<<":"<<__FILE__, rt::LOGTYPE_IN_CONSOLE|rt::LOGTYPE_WARNING)

// Only Log to file
#define _LOGF_VERBOSE(x)			__LOG_TYPE(x, rt::LOGTYPE_IN_LOGFILE|rt::LOGTYPE_VERBOSE)
#define _LOGF(x)					__LOG_TYPE(x, rt::LOGTYPE_IN_LOGFILE|rt::LOGTYPE_INFORMATIONAL)
#define _LOGF_HIGHLIGHT(x)			__LOG_TYPE(x, rt::LOGTYPE_IN_LOGFILE|rt::LOGTYPE_HIGHLIGHT)
#define _LOGF_WARNING(x)			__LOG_TYPE(x, rt::LOGTYPE_IN_LOGFILE|rt::LOGTYPE_WARNING)
#define _LOGF_ERROR(x)				__LOG_TYPE(x, rt::LOGTYPE_IN_LOGFILE|rt::LOGTYPE_ERROR)

#define _LOGF_POS					__LOG_TYPE(__FUNCTION__<<":L"<<__LINE__<<":"<<__FILE__, rt::LOGTYPE_IN_LOGFILE|rt::LOGTYPE_VERBOSE)
#define _LOGF_POS_WARNING			__LOG_TYPE(__FUNCTION__<<":L"<<__LINE__<<":"<<__FILE__, rt::LOGTYPE_IN_LOGFILE|rt::LOGTYPE_WARNING)

#define _LOGVAL(x)					#x " = " << (x)


/**
 * @brief  Debugging and error handling
 * 
 */
#ifndef ASSERT
	#ifdef PLATFORM_DEBUG_BUILD
		#if defined(PLATFORM_WIN)
			#define ASSERT(x) if(!(x)){ _LOG_ERROR("ASSERTION FAILED: " #x); _LOG_POS; _ASSERT(x); }
		#elif defined(PLATFORM_ANDROID)
			#define ASSERT(x) if(!(x)){ _LOG_ERROR("ASSERTION FAILED: " #x); _LOG_POS; }
		#else
			#include <assert.h>
			#define ASSERT(x) assert(x);
		#endif
	#else
		#define ASSERT(x) {}
	#endif
#endif

#ifndef ASSERT_AND_LOG
	#ifdef PLATFORM_DEBUG_BUILD
		#if defined(PLATFORM_WIN)
			#define ASSERT_AND_LOG(x,expect) {\
					auto __tmp = (x); \
					auto __tmp_expect = (expect); \
					if(__tmp!=__tmp_expect){ \
						_LOG_ERROR("ASSERTION FAILED: " #x " == " #expect); \
						_LOG_POS; \
						_ASSERT(__tmp==__tmp_expect); \
					} else { \
						_LOG(#x " == " #expect); \
					} \
			}
		#elif defined(PLATFORM_ANDROID)
			#define ASSERT_AND_LOG(x,expect) {\
					auto __tmp = (x); \
					auto __tmp_expect = (expect); \
					if(__tmp!=__tmp_expect){ \
						_LOG_ERROR("ASSERTION FAILED: " #x " == " #expect); \
						_LOG_POS; \
					} else { \
						_LOG(#x " == " #expect); \
					} \
			}
		#else
			#include <assert.h>
			#define ASSERT_AND_LOG(x,expect) {\
					assert(x==expect);\
					_LOG(#x " == " #expect);\
			}		
		#endif
	#else
		#define ASSERT_AND_LOG(x,expect) {}
	#endif
#endif // !ASSERT_AND_LOG


#ifdef VERIFY
#undef VERIFY
#endif

#define VERIFY(x)	rt::_details::_VERIFY_RET(x, #x, __FUNCTION__ , __LINE__ , __FILE__)

#define ASSERTH(re) ASSERT(SUCCEEDED(re))
#define VERIFYH(re) VERIFY(SUCCEEDED(re))

#define STATIC_ASSERT(x)	static_assert(x, #x " failed");

namespace rt
{
namespace _details
{

template<typename RET>
INLFUNC RET& _VERIFY_RET(RET&& exp, LPCSTR exp_str, LPCSTR func, int line, LPCSTR file)
{
#ifdef PLATFORM_DEBUG_BUILD
	if(!exp)
	{
		_LOG_WARNING("ASSERTION FAILED: "<<exp_str<<" in "<<func<<", file "<<file<<", line "<<line);
		ASSERT(0);
	}
#endif
	return exp;
}

} // namespace _details
} // namespace rt

/**
 * @brief Runtime diagnosis
 * 
 */
#if defined(PLATFORM_DEBUG_BUILD) && defined(PLATFORM_WIN)
	#define _CheckHeap	ASSERT(_CrtCheckMemory())
#else
	#define _CheckHeap	{}
#endif

#ifdef PLATFORM_DEBUG_BUILD
	#define ASSERT_FLOAT(x)	{ ASSERT(rt::IsNumberOk(x)); }
	#define VERIFY_FLOAT(x)	ASSERT_FLOAT(x)
#else
	#define ASSERT_FLOAT(x)	while(0)
	#define VERIFY_FLOAT(x)	while(x){ break; }
#endif
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
// Some constant 
namespace rt
{
 
struct _DummyType;

template<typename T>
constexpr auto Sqr(T x){ return x*x; }

template<typename T>
constexpr T max(const T& x, const T& y)
{
#pragma warning(disable:4018)
	return (x<y? y:x);
#pragma warning(default:4018)
}
    
template<typename T>
constexpr T min(const T& x, const T& y)
{
#pragma warning(disable:4018)
	return (x>y? y:x);
#pragma warning(default:4018)
}
	
template<typename T>
constexpr T abs(const T& x)
{
#pragma warning(disable:4018)
	return (x>=0? x:-x);
#pragma warning(default:4018)
}

template<typename T, typename T_R>
constexpr bool IsInRange_OO(T var,T_R min_v,T_R max_v)
{
	return (var > min_v) && (var < max_v);
}

template<typename T, typename T_R>
constexpr bool IsInRange_CC(T var,T_R min_v,T_R max_v)
{
	return (var >= min_v) && (var <= max_v);
}

template<typename T, typename T_R>
constexpr bool IsInRange_CO(T var,T_R min_v,T_R max_v)
{
	return (var >= min_v) && (var < max_v);
}

template<typename T, typename T_R>
constexpr bool IsInRange_OC(T var,T_R min_v,T_R max_v)
{
	return (var > min_v) && (var <= max_v);
}

#if defined(PLATFORM_WIN)
inline bool IsNumberOk(float val){ return ::rt::IsInRange_CC(_fpclass(val),_FPCLASS_NN,_FPCLASS_PN); }
inline bool IsNumberOk(double val){ return ::rt::IsInRange_CC(_fpclass(val),_FPCLASS_NN,_FPCLASS_PN); }
#elif defined(PLATFORM_ANDROID)
inline bool IsNumberOk(float val){ return isnormal(val); }
inline bool IsNumberOk(double val){ return isnormal(val); }
#else
inline bool IsNumberOk(float val){ int c = std::fpclassify(val); return c!=FP_INFINITE && c!=FP_NAN; }
inline bool IsNumberOk(double val){ int c = std::fpclassify(val); return c!=FP_INFINITE && c!=FP_NAN; }
#endif

inline bool IsPositiveInfinity		(float val){ return ((DWORD&)val)==0x7f800000; }
inline bool IsNegativeInfinity		(float val){ return ((DWORD&)val)==0xff800000; }
inline bool IsNotANumber			(float val){ return ((DWORD&)val)==0x7fffffff; }
inline bool IsPositiveInfinity		(double val){ return ((ULONGLONG&)val)==0x7ff0000000000000; }
inline bool IsNegativeInfinity		(double val){ return ((ULONGLONG&)val)==0xfff0000000000000; }
inline bool IsNotANumber			(double val){ return ((ULONGLONG&)val)==0x7fffffffffffffff; }
inline void MakePositiveInfinity	(float& val){ ((DWORD&)val)=0x7f800000; }
inline void MakeNegativeInfinity	(float& val){ ((DWORD&)val)=0xff800000; }
inline void MakeNotANumber			(float& val){ ((DWORD&)val)=0x7fffffff; }
inline void MakePositiveInfinity	(double& val){ ((ULONGLONG&)val)=0x7ff0000000000000; }
inline void MakeNegativeInfinity	(double& val){ ((ULONGLONG&)val)=0xfff0000000000000; }
inline void MakeNotANumber			(double& val){ ((ULONGLONG&)val)=0x7fffffffffffffff; }

// PopCount
namespace _details
{
const ULONGLONG m1  = 0x5555555555555555ULL; ///< binary: 0101...
const ULONGLONG m2  = 0x3333333333333333ULL; ///< binary: 00110011..
const ULONGLONG m4  = 0x0f0f0f0f0f0f0f0fULL; ///< binary:  4 zeros,  4 ones ...
};

constexpr int PopCount(ULONGLONG x) {
    x -= (x >> 1) & _details::m1;             ///< put count of each 2 bits into those 2 bits
    x = (x & _details::m2) + ((x >> 2) & _details::m2); ///< put count of each 4 bits into those 4 bits 
    x = (x + (x >> 4)) & _details::m4;        ///< put count of each 8 bits into those 8 bits 
    x += x >>  8;  ///< put count of each 16 bits into their lowest 8 bits
    x += x >> 16;  ///< put count of each 32 bits into their lowest 8 bits
    x += x >> 32;  ///< put count of each 64 bits into their lowest 8 bits
    return x & 0x7f;
}



// xxHash
namespace _details
{
	static const UINT PRIME1 =  2654435761U;
	static const UINT PRIME2 =  2246822519U;
	static const UINT PRIME3 =  3266489917U;
	static const UINT PRIME4 =   668265263U;
	static const UINT PRIME5 =  0x165667b1U;

	/**
	 * @brief This version is for very small inputs (< 16  bytes)
	 * 
	 * @param key 
	 * @param len 
	 * @param seed 
	 * @return INLFUNC 
	 */
	INLFUNC unsigned int xxHash_small(const void* key, int len, unsigned int seed)
	{	const unsigned char* p = (unsigned char*)key;
		const unsigned char* const bEnd = p + len;
		unsigned int idx = seed + PRIME1;
		unsigned int crc = PRIME5;
		const unsigned char* const limit = bEnd - 4;
		while (p<limit)
		{	crc += ((*(unsigned int*)p) + idx++);
			crc += _rotl(crc, 17) * PRIME4;
			crc *= PRIME1;
			p+=4;
		}
		while (p<bEnd)
		{	crc += ((*p) + idx++);
			crc *= PRIME1;
			p++;
		}
		crc += len;
		crc ^= crc >> 15;
		crc *= PRIME2;
		crc ^= crc >> 13;
		crc *= PRIME3;
		crc ^= crc >> 16;
		return crc;
	}
}

INLFUNC UINT xxHash(const void* input, int len, unsigned int seed = 0)
{	// Special case, for small inputs
	if (len < 16) return _details::xxHash_small(input, len, seed);
	const unsigned char* p = (const unsigned char*)input;
	const unsigned char* const bEnd = p + len;
	unsigned int v1 = seed + _details::PRIME1;
	unsigned int v2 = v1 * _details::PRIME2 + len;
	unsigned int v3 = v2 * _details::PRIME3;
	unsigned int v4 = v3 * _details::PRIME4;	
	const unsigned char* const limit = bEnd - 16;
	unsigned int crc;
	while (p<limit)
	{	v1 = _rotl(v1, 13) + (*(unsigned int*)p); p+=4;
		v2 = _rotl(v2, 11) + (*(unsigned int*)p); p+=4;
		v3 = _rotl(v3, 17) + (*(unsigned int*)p); p+=4;
		v4 = _rotl(v4, 19) + (*(unsigned int*)p); p+=4;
	} 

	p = bEnd - 16;
	v1 += _rotl(v1, 17); v2 += _rotl(v2, 19); v3 += _rotl(v3, 13); v4 += _rotl(v4, 11); 
	v1 *= _details::PRIME1; v2 *= _details::PRIME1; v3 *= _details::PRIME1; v4 *= _details::PRIME1; 
	v1 += *(unsigned int*)p; p+=4; v2 += *(unsigned int*)p; p+=4; v3 += *(unsigned int*)p; p+=4; v4 += *(unsigned int*)p;   // p+=4;
	v1 *= _details::PRIME2; v2 *= _details::PRIME2; v3 *= _details::PRIME2; v4 *= _details::PRIME2; 
	v1 += _rotl(v1, 11); v2 += _rotl(v2, 17); v3 += _rotl(v3, 19); v4 += _rotl(v4, 13); 
	v1 *= _details::PRIME3; v2 *= _details::PRIME3; v3 *= _details::PRIME3; v4 *= _details::PRIME3;

	crc = v1 + _rotl(v2, 3) + _rotl(v3, 6) + _rotl(v4, 9);
	crc ^= crc >> 11;
	crc += (_details::PRIME4+len) * _details::PRIME1;
	crc ^= crc >> 15;
	crc *= _details::PRIME2;
	crc ^= crc >> 13;

	return crc;
}

INLFUNC UINT xxHashStrong(const void* input, int len, unsigned int seed = 0)
{	// Special case, for small inputs
	if (len < 16) return _details::xxHash_small(input, len, seed);
	const unsigned char* p = (const unsigned char*)input;
	const unsigned char* const bEnd = p + len;
	unsigned int v1 = seed + _details::PRIME1;
	unsigned int v2 = v1 * _details::PRIME2 + len;
	unsigned int v3 = v2 * _details::PRIME3;
	unsigned int v4 = v3 * _details::PRIME4;	
	const unsigned char* const limit = bEnd - 16;
	unsigned int crc;

	while (p<limit)
	{
		v1 += _rotl(v1, 13); v1 *= _details::PRIME1; v1 += (*(unsigned int*)p); p+=4;
		v2 += _rotl(v2, 11); v2 *= _details::PRIME1; v2 += (*(unsigned int*)p); p+=4;
		v3 += _rotl(v3, 17); v3 *= _details::PRIME1; v3 += (*(unsigned int*)p); p+=4;
		v4 += _rotl(v4, 19); v4 *= _details::PRIME1; v4 += (*(unsigned int*)p); p+=4;
	} 

	p = bEnd - 16;
	v1 += _rotl(v1, 17); v2 += _rotl(v2, 19); v3 += _rotl(v3, 13); v4 += _rotl(v4, 11); 
	v1 *= _details::PRIME1; v2 *= _details::PRIME1; v3 *= _details::PRIME1; v4 *= _details::PRIME1; 
	v1 += *(unsigned int*)p; p+=4; v2 += *(unsigned int*)p; p+=4; v3 += *(unsigned int*)p; p+=4; v4 += *(unsigned int*)p;   // p+=4;
	v1 *= _details::PRIME2; v2 *= _details::PRIME2; v3 *= _details::PRIME2; v4 *= _details::PRIME2; 
	v1 += _rotl(v1, 11); v2 += _rotl(v2, 17); v3 += _rotl(v3, 19); v4 += _rotl(v4, 13); 
	v1 *= _details::PRIME3; v2 *= _details::PRIME3; v3 *= _details::PRIME3; v4 *= _details::PRIME3;

	crc = v1 + _rotl(v2, 3) + _rotl(v3, 6) + _rotl(v4, 9);
	crc ^= crc >> 11;
	crc += (_details::PRIME4+len) * _details::PRIME1;
	crc ^= crc >> 15;
	crc *= _details::PRIME2;
	crc ^= crc >> 13;
	return crc;
}


struct _File
{
	static const int Seek_Begin		= 0;
	static const int Seek_Current	= 1;
	static const int Seek_End		= 2;

	virtual SIZE_T		Read(LPVOID lpBuf,SIZE_T nCount) = 0;
	virtual SIZE_T		Write(LPCVOID lpBuf,SIZE_T nCount) = 0;
	virtual SIZE_T		Seek(SSIZE_T offset,UINT nFrom = Seek_Begin) = 0; ///< return ULLONG_MAX for failure.
	virtual SIZE_T		GetLength() const = 0;
};

namespace _details
{

template<int size, SIZE_T set, bool size_exceeded = (size > 32)> struct _PodFill
{	static INLFUNC void Fill(LPBYTE obj) noexcept 
	{	SIZE_T* p = (SIZE_T*)obj;
		for(SIZE_T i=sizeof(SIZE_T);i<=size;i+=sizeof(SIZE_T), p++)*p = set;
		_PodFill<size%sizeof(SIZE_T), set>::Fill(obj + (size - size%sizeof(SIZE_T)));
}	};
	template<int size, SIZE_T set> struct _PodFill<size, set, false>
	{	static INLFUNC void Fill(LPBYTE p) noexcept 
		{	*(SIZE_T*)p = set;
			_PodFill<size-sizeof(SIZE_T), set, false>::Fill(p+sizeof(SIZE_T));
	}	};
	template<SIZE_T set> struct _PodFill<0, set, false>{ static INLFUNC void Fill(LPBYTE p) noexcept {}};
	template<SIZE_T set> struct _PodFill<1, set, false>{ static INLFUNC void Fill(LPBYTE p) noexcept { *p = (BYTE)set; }};
	template<SIZE_T set> struct _PodFill<2, set, false>{ static INLFUNC void Fill(LPBYTE p) noexcept { *(WORD*)p = (WORD)set; }};
	template<SIZE_T set> struct _PodFill<3, set, false>{ static INLFUNC void Fill(LPBYTE p) noexcept { *(WORD*)p = (WORD)set; p[2] = (BYTE)set; }};
#if defined(PLATFORM_64BIT)
	template<SIZE_T set> struct _PodFill<4, set, false>{ static INLFUNC void Fill(LPBYTE p) noexcept { *(DWORD*)p = (DWORD)set; }};
	template<SIZE_T set> struct _PodFill<5, set, false>{ static INLFUNC void Fill(LPBYTE p) noexcept { *(DWORD*)p = (DWORD)set; _PodFill<1, set>::Fill(p+4); }};
	template<SIZE_T set> struct _PodFill<6, set, false>{ static INLFUNC void Fill(LPBYTE p) noexcept { *(DWORD*)p = (DWORD)set; _PodFill<2, set>::Fill(p+4); }};
	template<SIZE_T set> struct _PodFill<7, set, false>{ static INLFUNC void Fill(LPBYTE p) noexcept { *(DWORD*)p = (DWORD)set; _PodFill<3, set>::Fill(p+4); }};
#endif

} // namespace _details

template<typename T> INLFUNC void Zero(T& obj) noexcept { _details::_PodFill<sizeof(T), 0>::Fill((LPBYTE)&obj); } // treat any type as POD
template<typename T> INLFUNC void Void(T& obj) noexcept { _details::_PodFill<sizeof(T), (SIZE_T)-1>::Fill((LPBYTE)&obj); } // treat any type as POD
template<UINT LEN> INLFUNC void Zero(LPVOID obj) noexcept { _details::_PodFill<LEN, 0>::Fill((LPBYTE)obj); }
template<UINT LEN> INLFUNC void Void(LPVOID obj) noexcept { _details::_PodFill<LEN, (SIZE_T)-1>::Fill((LPBYTE)obj); }

INLFUNC void Zero(LPVOID obj, SIZE_T size)
{	SIZE_T* p = (SIZE_T*)obj;
	for(;size>=sizeof(SIZE_T);size-=sizeof(SIZE_T), p++)*p = 0;
	switch(size)
	{	case 0: return;
		case 1: _details::_PodFill<1, 0>::Fill((LPBYTE)p); return;
		case 2: _details::_PodFill<2, 0>::Fill((LPBYTE)p); return;
		case 3: _details::_PodFill<3, 0>::Fill((LPBYTE)p); return;
#if defined(PLATFORM_64BIT)
		case 4: _details::_PodFill<4, 0>::Fill((LPBYTE)p); return;
		case 5: _details::_PodFill<5, 0>::Fill((LPBYTE)p); return;
		case 6: _details::_PodFill<6, 0>::Fill((LPBYTE)p); return;
		case 7: _details::_PodFill<7, 0>::Fill((LPBYTE)p); return;
#endif
		default: ASSERT(0); return;
	}
}

INLFUNC void Void(LPVOID obj, SIZE_T size)
{	SIZE_T* p = (SIZE_T*)obj;
	for(;size>=sizeof(SIZE_T);size-=sizeof(SIZE_T), p++)*p = (SIZE_T)-1;
	switch(size)
	{	case 0: return;
		case 1: _details::_PodFill<1, (SIZE_T)-1>::Fill((LPBYTE)p); return;
		case 2: _details::_PodFill<2, (SIZE_T)-1>::Fill((LPBYTE)p); return;
		case 3: _details::_PodFill<3, (SIZE_T)-1>::Fill((LPBYTE)p); return;
#if defined(PLATFORM_64BIT)
		case 4: _details::_PodFill<4, (SIZE_T)-1>::Fill((LPBYTE)p); return;
		case 5: _details::_PodFill<5, (SIZE_T)-1>::Fill((LPBYTE)p); return;
		case 6: _details::_PodFill<6, (SIZE_T)-1>::Fill((LPBYTE)p); return;
		case 7: _details::_PodFill<7, (SIZE_T)-1>::Fill((LPBYTE)p); return;
#endif
		default: ASSERT(0); return;
	}
}

namespace _details
{
template<int size, bool size_exceeded = (size > 32)> struct _PodCopy
{	static INLFUNC void Fill(LPBYTE p_in, LPCBYTE s_in) noexcept
	{	SIZE_T* p = (SIZE_T*)p_in;
		SIZE_T* s = (SIZE_T*)s_in;
		for(SIZE_T i=sizeof(SIZE_T);i<=size;i+=sizeof(SIZE_T), p++, s++)*p = *s;
		_PodCopy<size%sizeof(SIZE_T)>::Fill(p_in + (size - size%sizeof(SIZE_T)), s_in + (size - size%sizeof(SIZE_T)));
}	};
	template<int size> struct _PodCopy<size, false>
	{	static INLFUNC void Fill(LPBYTE p, LPCBYTE s) noexcept
		{	*(SIZE_T*)p = *(SIZE_T*)s;
			_PodCopy<size-sizeof(SIZE_T)>::Fill(p+sizeof(SIZE_T), s+sizeof(SIZE_T));
	}	};
	template<> struct _PodCopy<0>{ static INLFUNC void Fill(LPBYTE p, LPCBYTE s) noexcept {}};
	template<> struct _PodCopy<1>{ static INLFUNC void Fill(LPBYTE p, LPCBYTE s) noexcept { *p = *s; }};
	template<> struct _PodCopy<2>{ static INLFUNC void Fill(LPBYTE p, LPCBYTE s) noexcept { *(WORD*)p = *(WORD*)s; }};
	template<> struct _PodCopy<3>{ static INLFUNC void Fill(LPBYTE p, LPCBYTE s) noexcept { *(WORD*)p = *(WORD*)s; p[2] = s[2]; }};
#if defined(PLATFORM_64BIT)
	template<> struct _PodCopy<4>{ static INLFUNC void Fill(LPBYTE p, LPCBYTE s) noexcept { *(DWORD*)p = *(DWORD*)s; }};
	template<> struct _PodCopy<5>{ static INLFUNC void Fill(LPBYTE p, LPCBYTE s) noexcept { *(DWORD*)p = *(DWORD*)s; _PodCopy<1>::Fill(p+4, s+4); }};
	template<> struct _PodCopy<6>{ static INLFUNC void Fill(LPBYTE p, LPCBYTE s) noexcept { *(DWORD*)p = *(DWORD*)s; _PodCopy<2>::Fill(p+4, s+4); }};
	template<> struct _PodCopy<7>{ static INLFUNC void Fill(LPBYTE p, LPCBYTE s) noexcept { *(DWORD*)p = *(DWORD*)s; _PodCopy<3>::Fill(p+4, s+4); }};
#endif

template<int size, bool size_exceeded = (size > 32)> struct _PodEqual
{	static INLFUNC bool IsEqual(LPCBYTE p_in, LPCBYTE s_in) noexcept
	{	SIZE_T* p = (SIZE_T*)p_in;
		SIZE_T* s = (SIZE_T*)s_in;
		for(SIZE_T i=sizeof(SIZE_T);i<=size;i+=sizeof(SIZE_T), p++, s++)if(*p != *s)return false;
		return _PodEqual<size%sizeof(SIZE_T)>::IsEqual(p_in + (size - size%sizeof(SIZE_T)), s_in + (size - size%sizeof(SIZE_T)));
}	};
	template<int size> struct _PodEqual<size, false>
	{	static INLFUNC bool IsEqual(LPCBYTE p, LPCBYTE s) noexcept
		{	return	*(SIZE_T*)p == *(SIZE_T*)s &&
					_PodEqual<size-sizeof(SIZE_T)>::IsEqual(p+sizeof(SIZE_T), s+sizeof(SIZE_T));
	}	};
	template<> struct _PodEqual<0, false>{ static INLFUNC bool IsEqual(LPCBYTE p, LPCBYTE s) noexcept { return true; }};
	template<> struct _PodEqual<1, false>{ static INLFUNC bool IsEqual(LPCBYTE p, LPCBYTE s) noexcept { return *p == *s; }};
	template<> struct _PodEqual<2, false>{ static INLFUNC bool IsEqual(LPCBYTE p, LPCBYTE s) noexcept { return *(WORD*)p == *(WORD*)s; }};
	template<> struct _PodEqual<3, false>{ static INLFUNC bool IsEqual(LPCBYTE p, LPCBYTE s) noexcept { return *(WORD*)p == *(WORD*)s && p[2] == s[2]; }};
#if defined(PLATFORM_64BIT)
	template<> struct _PodEqual<4, false>{ static INLFUNC bool IsEqual(LPCBYTE p, LPCBYTE s) noexcept { return *(DWORD*)p == *(DWORD*)s; }};
	template<> struct _PodEqual<5, false>{ static INLFUNC bool IsEqual(LPCBYTE p, LPCBYTE s) noexcept { return *(DWORD*)p == *(DWORD*)s && _PodEqual<1>::IsEqual(p+4, s+4); }};
	template<> struct _PodEqual<6, false>{ static INLFUNC bool IsEqual(LPCBYTE p, LPCBYTE s) noexcept { return *(DWORD*)p == *(DWORD*)s && _PodEqual<2>::IsEqual(p+4, s+4); }};
	template<> struct _PodEqual<7, false>{ static INLFUNC bool IsEqual(LPCBYTE p, LPCBYTE s) noexcept { return *(DWORD*)p == *(DWORD*)s && _PodEqual<3>::IsEqual(p+4, s+4); }};
#endif

} // namespace _details

template<UINT LEN>
INLFUNC void Copy(LPVOID obj, LPCVOID from) noexcept { _details::_PodCopy<LEN>::Fill((LPBYTE)obj, (LPCBYTE)from); }
template<typename T1, typename T2>
INLFUNC void Copy(T1& obj, const T2& from) noexcept { Copy<sizeof(T1)>((LPBYTE)&obj, (LPCBYTE)&from); static_assert(sizeof(T1) == sizeof(T2), "rt::Copy sizes of operands mismatch"); } // treat any type as POD

template<UINT LEN>
INLFUNC bool IsEqual(LPCVOID obj, LPCVOID from) noexcept { return _details::_PodEqual<LEN>::IsEqual((LPCBYTE)obj, (LPCBYTE)from); }
template<typename T1, typename T2>
INLFUNC bool IsEqual(const T1& obj, const T2& from) noexcept { return IsEqual<sizeof(T1)>((LPCBYTE)&obj, (LPCBYTE)&from); static_assert(sizeof(T1) == sizeof(T2), "rt::IsEqual sizes of operands mismatch"); } // treat any type as POD


namespace _details
{
	// FNV Hash function (http://isthe.com/chongo/tech/comp/fnv/)
#if defined(PLATFORM_64BIT)
	static const SIZE_T	_HashInit = 14695981039346656037ULL;
	INLFUNC SIZE_T		_HashKernel(SIZE_T new_data, SIZE_T prev_val){ return 1099511628211ULL * (prev_val ^ new_data); }
#else
	static const SIZE_T	_HashInit = 2166136261U;
	INLFUNC SIZE_T		_HashKernel(SIZE_T new_data, SIZE_T prev_val){ return 16777619U * (prev_val ^ new_data); }
#endif

	template<int Size=0> struct _HashValueFix
	{	static INLFUNC SIZE_T Val(LPCBYTE p, SIZE_T prev_val = _HashInit)
		{	return _HashValueFix<Size-sizeof(SIZE_T)>::Val(p+sizeof(SIZE_T), _HashKernel(*(SIZE_T*)p, prev_val));
	}	};
		template<> struct _HashValueFix<0>{	static INLFUNC SIZE_T Val(LPCBYTE p, SIZE_T prev_val = _HashInit){ return prev_val; }};
		template<> struct _HashValueFix<1>{	static INLFUNC SIZE_T Val(LPCBYTE p, SIZE_T prev_val = _HashInit){ return _HashKernel((SIZE_T)*p, prev_val); }};
		template<> struct _HashValueFix<2>{	static INLFUNC SIZE_T Val(LPCBYTE p, SIZE_T prev_val = _HashInit){ return _HashKernel((SIZE_T)*(WORD*)p, prev_val); }};
		template<> struct _HashValueFix<3>{	static INLFUNC SIZE_T Val(LPCBYTE p, SIZE_T prev_val = _HashInit){ return _HashKernel((0xffffffU&(SIZE_T)*(DWORD*)p), prev_val); }};
#if defined(PLATFORM_64BIT)
		template<> struct _HashValueFix<4>{	static INLFUNC SIZE_T Val(LPCBYTE p, SIZE_T prev_val = _HashInit){ return _HashKernel((SIZE_T)*(DWORD*)p, prev_val); }};
		template<> struct _HashValueFix<5>{	static INLFUNC SIZE_T Val(LPCBYTE p, SIZE_T prev_val = _HashInit){ return _HashKernel(0xffffffffffULL&(SIZE_T)*(ULONGLONG*)p, prev_val); }};
		template<> struct _HashValueFix<6>{	static INLFUNC SIZE_T Val(LPCBYTE p, SIZE_T prev_val = _HashInit){ return _HashKernel(0xffffffffffffULL&(SIZE_T)*(ULONGLONG*)p, prev_val); }};
		template<> struct _HashValueFix<7>{	static INLFUNC SIZE_T Val(LPCBYTE p, SIZE_T prev_val = _HashInit){ return _HashKernel(0xffffffffffffffULL&(SIZE_T)*(ULONGLONG*)p, prev_val); }};
	// x64
	INLFUNC SIZE_T _HashValue(LPCVOID p_in, SIZE_T size, SIZE_T val = _HashInit)
	{	const SIZE_T* p = (const SIZE_T*)p_in;
		for(; size >= sizeof(SIZE_T); size -=sizeof(SIZE_T), p++)
			val = _HashKernel(*p, val);
		switch(size)
		{	case 0: return _HashValueFix<0>::Val((LPCBYTE)p, val);
			case 1: return _HashValueFix<1>::Val((LPCBYTE)p, val);
			case 2: return _HashValueFix<2>::Val((LPCBYTE)p, val);
			case 3: return _HashValueFix<3>::Val((LPCBYTE)p, val);
			case 4: return _HashValueFix<4>::Val((LPCBYTE)p, val);
			case 5: return _HashValueFix<5>::Val((LPCBYTE)p, val);
			case 6: return _HashValueFix<6>::Val((LPCBYTE)p, val);
			case 7: return _HashValueFix<7>::Val((LPCBYTE)p, val);
			default: ASSERT(0); return val;
		}
	}
#else
	// x86
	INLFUNC SIZE_T _HashValue(LPCVOID p_in, SIZE_T size, SIZE_T val = _HashInit)
	{	const SIZE_T* p = (const SIZE_T*)p_in;
		for(; size >= sizeof(SIZE_T); size -=sizeof(SIZE_T), p++)
			val = _HashKernel(*p, val);
		switch(size)
		{	case 0: return _HashValueFix<0>::Val((LPCBYTE)p, val);
			case 1: return _HashValueFix<1>::Val((LPCBYTE)p, val);
			case 2: return _HashValueFix<2>::Val((LPCBYTE)p, val);
			case 3: return _HashValueFix<3>::Val((LPCBYTE)p, val);
			default: ASSERT(0); return val;
		}
	}
#endif
	template<typename T>
	INLFUNC SIZE_T _HashValuePod(const T& obj, SIZE_T val = _HashInit)
	{	return _HashValueFix<sizeof(T)>::Val((LPCBYTE)&obj, val);
	}
	/**
	 * @brief traits class for hash containers
	 * 
	 * @tparam T 
	 */
	template<typename T>
	struct hash_compare_str
	{	
		enum ///< parameters for hash table
		{	bucket_size = 4,	///< 0 < bucket_size
			min_buckets = 8		///< min_buckets = 2 ^^ N, 0 < N
		};
		INLFUNC size_t operator()(const T& key) const
		{	return _HashValue(key.Begin(),(key.End() - key.Begin())*sizeof(*key.Begin()));	
        }
		INLFUNC bool operator()(const T& _Keyval1, const T& _Keyval2) const
		{	return _Keyval1 < _Keyval2;		}
	};
	//template<typename T, int t_Block = sizeof(T)%4>
	template<typename T, int t_Block = 1>
	struct hash_compare_fix;
	template<typename T> struct hash_compare_fix<T, 1>
	{	
		enum ///< parameters for hash table
		{	bucket_size = 4,	///< 0 < bucket_size
			min_buckets = 8		///< min_buckets = 2 ^^ N, 0 < N
		};
		INLFUNC size_t operator()(const T& key) const
		{	return _HashValueFix<sizeof(T)>::Val((LPCBYTE)&key);}
		INLFUNC bool operator()(const T& _Keyval1, const T& _Keyval2) const
		{	return memcmp(&_Keyval1, &_Keyval2, sizeof(T)) < 0;	}
	};
} // namespace _details

} // namespace rt

///////////////////////////////////////////////////////
// Safe delete Objects
#define _SafeRelease(x)				{ if(x){x->Release(); x=nullptr;} }
#define _SafeRelease_ConstPtr(x)	{ auto* ___p___=(x); if(___p___)rt::_CastToNonconst(___p___)->Release(); }

#if defined(PLATFORM_MAC) || defined(PLATFORM_IOS)
#define _SafeCFRelease(x)	{ if(x){::CFRelease(x); x=nullptr;} }
#endif
///////////////////////////////////////////////////////

namespace rt
{

//INLFUNC void Randomize( DWORD seed = time(NULL) ){ srand(seed); }
/**
 * @brief Misc inline templates
 * 
 * @tparam T 
 * @param within 
 * @return FORCEINL 
 */
template<typename T>
INLFUNC T MaxPower2Within(T within)
{
	if(within)
	{
		UINT ret=1;
		while(within!=1)
		{
			ret<<=1;
			within>>=1;
		}

		return ret;
	}
	else
		return 0;
}

template<typename T>
inline T* _CastToNonconst(const T * p){ return (T*)((size_t)p); }

template<typename T>
inline T& _CastToNonconst(const T& x){ return *(T*)&x; }

template<typename T>
inline const T* _CastToConst(T * p){ return p; }

template<typename T>
inline const T& _CastToConst(T& x){ return x; }

template<typename T>
INLFUNC T* _RelocatePointer(LPCVOID new_base, LPCVOID old_base, T* old_p)
{
	ASSERT(new_base);
	if(new_base == nullptr || old_p == nullptr)return nullptr;
	return (T*)(((LPBYTE)old_p) + ((LPCBYTE)new_base - (LPCBYTE)old_base));
}

} // namespace rt




namespace rt
{
namespace _details
{	
	/**
	 * @brief switch little-endian/big-endian values, inplace
	 * 
	 * @tparam sz 
	 * @param p 
	 * @return FORCEINL 
	 */
	template<int sz>
	INLFUNC void _SwapByteOrder(LPBYTE p)
	{	BYTE t = p[0];
		p[0] = p[sz-1];
		p[sz-1] = t;
		_SwapByteOrder<sz-2>(p+1);
	}
	template<>
	INLFUNC void _SwapByteOrder<1>(LPBYTE p){}
	template<>
	INLFUNC void _SwapByteOrder<0>(LPBYTE p){}
} // namespace _details
} // namespace rt

namespace rt
{
	template<typename T>
	INLFUNC void SwapByteOrder(T& x)
	{	_details::_SwapByteOrder<sizeof(T)>((LPBYTE)&x);
	}
	template<typename T>
	INLFUNC T SwapByteOrder(const T& x)
	{	T out = x;
		_details::_SwapByteOrder<sizeof(T)>((LPBYTE)&out);
		return out;
	}
}

namespace rt
{
namespace _details
{	
	template<int sz>
	INLFUNC void _SwitchByteOrderTo(LPCBYTE f, LPBYTE t)
	{	*t = *f;
 		_SwitchByteOrderTo<sz-1>(f-1, t+1);
	}
	template<>
	INLFUNC void _SwitchByteOrderTo<0>(LPCBYTE f, LPBYTE t){}

	template<size_t sz, int block = sz>=8?8:(sz>=4?4:(sz>=2?2:1)), bool is_small = (sz<=128) >
	struct _CopyByteTo;
		template<size_t sz> struct _CopyByteTo<sz,8,true>
		{	static INLFUNC void Copy(LPCBYTE f, LPBYTE t)
			{	*((ULONGLONG*)t) = *((ULONGLONG*)f);
				_CopyByteTo<sz-8>::Copy(f+8, t+8);
		}	};
		template<size_t sz> struct _CopyByteTo<sz,4,true>
		{	static INLFUNC void Copy(LPCBYTE f, LPBYTE t)
			{	*((DWORD*)t) = *((DWORD*)f);
				_CopyByteTo<sz-4>::Copy(f+4, t+4);
		}	};
		template<size_t sz> struct _CopyByteTo<sz,2,true>
		{	static INLFUNC void Copy(LPCBYTE f, LPBYTE t)
			{	*((WORD*)t) = *((WORD*)f);
				_CopyByteTo<sz-2>::Copy(f+2, t+2);
		}	};
		template<> struct _CopyByteTo<1,1,true>
		{	static INLFUNC void Copy(LPCBYTE f, LPBYTE t)
			{	*((BYTE*)t) = *((BYTE*)f);
		}	};
		template<> struct _CopyByteTo<0, 1,true>
		{	static INLFUNC void Copy(LPCBYTE f, LPBYTE t){}
		};
		template<size_t sz, int block> struct _CopyByteTo<sz, block, false>
		{	static INLFUNC void Copy(LPCBYTE f, LPBYTE t){ memcpy(t, f, sz); }
		};
} // namespace _details
} // namespace rt

namespace rt
{
	template<typename T>
	INLFUNC void SwitchByteOrderTo(const T& from, T& to)
	{	_details::_SwitchByteOrderTo<sizeof(T)>(((LPCBYTE)&from) + sizeof(T) - 1, (LPBYTE)&to);
	}
	template<int SIZE>
	INLFUNC void SwitchByteOrderTo(LPCVOID from, LPVOID to)
	{	_details::_SwitchByteOrderTo<SIZE>(((LPCBYTE)from) + SIZE - 1, (LPBYTE)to);
	}
	template<typename T>
	INLFUNC void CopyByteTo(const T& from, T& to)
	{	_details::_CopyByteTo<sizeof(T)>::Copy((LPCBYTE)&from, (LPBYTE)&to);
	}
	template<int SIZE>
	INLFUNC void CopyByteTo(LPCVOID from, LPVOID to)
	{	_details::_CopyByteTo<SIZE>::Copy((LPCBYTE)from, (LPBYTE)to);
	}
	template<typename T>
	INLFUNC void CopyBits(T& x, T val, T mask)
	{
		ASSERT((val & (~mask)) == 0);
		x = (x&(~mask)) | val;
	}
} // namespace rt


namespace rt
{
INLFUNC WORD		BitSmudgeRight(WORD x) // (minimum power of 2 >= x) - 1
					{	UINT r = x | (x>>1);
						r |= r >> 2;	r |= r >> 4;	r |= r >> 8;
						return (WORD)r;
					}
INLFUNC UINT		BitSmudgeRight(UINT x) // (minimum power of 2 >= x) - 1
					{	UINT r = x | (x>>1);
						r |= r >> 2;	r |= r >> 4;	r |= r >> 8;	r |= r >> 16;
						return r;
					}
INLFUNC ULONGLONG	BitSmudgeRight(ULONGLONG x) // (minimum power of 2 >= x) - 1
					{	ULONGLONG r = x | (x>>1);
						r |= r >> 2;	r |= r >> 4;	r |= r >> 8;	r |= r >> 16;	r |= r >> 32;
						return (WORD)r;
					}
}


namespace rt
{
	namespace _details
	{
		/**
		 * @brief Optimized Object Swap
		 * 
		 * Optimized Object Swap, UNSAFE if the object has self or member pointed pointers
		 * 
		 * No additional temporary object, no ctor/dtor called
		 * @tparam Len 
		 * @param obj_a 
		 * @param obj_b 
		 * @return FORCEINL 
		 */
		template<UINT Len>
		INLFUNC void _Exchange_32AL(LPDWORD obj_a,LPDWORD obj_b) noexcept
		{
			DWORD t = *obj_a;
			*obj_a = *obj_b;
			*obj_b = t;

			rt::_details::_Exchange_32AL<Len-1>(obj_a+1,obj_b+1);
		}
		template<>
		INLFUNC void _Exchange_32AL<0>(LPDWORD,LPDWORD) noexcept {} // dummy
	} // namespace _details
} // namespace rt

namespace rt
{
#pragma warning(disable: 4307) ///< warning C4307: '*' : integral constant overflow
template<typename T>
INLFUNC void Swap(T& a, T& b) noexcept
{	
	rt::_details::_Exchange_32AL<sizeof(T)/4> ((LPDWORD)&a, (LPDWORD)&b);
	if( (sizeof(T)&0x1) == 0x1 )
	{	DWORD t;
		t = ((LPBYTE)&a)[sizeof(T)-1];
		((LPBYTE)&a)[sizeof(T)-1] = ((LPBYTE)&b)[sizeof(T)-1];
		((LPBYTE)&b)[sizeof(T)-1] = (BYTE)t;
	}
	if( (sizeof(T)&0x2) == 0x2 )
	{	DWORD t;
		t = ((LPWORD)&a)[sizeof(T)/2-1];
		((LPWORD)&a)[sizeof(T)/2-1] = ((LPWORD)&b)[sizeof(T)/2-1];
		((LPWORD)&b)[sizeof(T)/2-1] = (WORD)t;
	}
}
#pragma warning(default: 4307) ///< warning C4307: '*' : integral constant overflow

} // namespace rt


///////////////////////////////////////////////////////
// Advanced Bits Operations
namespace rt
{
namespace _details
{	
	template<typename T, int bitw = sizeof(T)*8>
	struct AdvBitOps;
		template<typename T> struct AdvBitOps<T, 16>
		{
#if defined(PLATFORM_WIN)
			static UINT LeadingZeroBits(T x){ ULONG index; return _BitScanReverse(&index, (DWORD)x) ? 16U - 1U - (UINT)index : 16U; }
			static UINT TrailingZeroBits(T x) { ULONG index; return _BitScanForward(&index, (DWORD)x) ? (UINT)index : 16U; }
			static UINT NonzeroBits(T x) { return (UINT)__popcnt16((WORD)x); }
			static T	ByteOrderSwap(T x) { return (T)_byteswap_ushort((WORD)x); }
#else
			static UINT LeadingZeroBits(T x) { if (0 == x)return 16; return (UINT)__builtin_clz((DWORD)x) - 16; }
			static UINT TrailingZeroBits(T x) { if (0 == x)return 16; return (UINT)__builtin_ctz((DWORD)x); }
			static UINT NonzeroBits(T x) { return (UINT)__builtin_popcount((DWORD)x); }
			static T	ByteOrderSwap(T x) { return (T)__builtin_bswap16((WORD)x); }
#endif
		};
		template<typename T> struct AdvBitOps<T, 32>
		{
#if defined(PLATFORM_WIN)
			static UINT LeadingZeroBits(T x) { ULONG index; return _BitScanReverse(&index, (DWORD)x) ? 32U - 1U - (UINT)index : 32U; }
			static UINT TrailingZeroBits(T x) { ULONG index; return _BitScanForward(&index, (DWORD)x) ? (UINT)index : 32U; }
			static UINT NonzeroBits(T x) { return (UINT)__popcnt((DWORD)x); }
			static T	ByteOrderSwap(T x) { return _byteswap_ulong((DWORD)x); }
            static BYTE AddCarry(BYTE carry, T a, T b, T* c){ return _addcarry_u32(carry, (UINT)a, (UINT)b, (UINT*)c); }
            static BYTE SubBorrow(BYTE carry, T a, T b, T* c) { return _subborrow_u32(carry, (UINT)a, (UINT)b, (UINT*)c); }
#else
			static UINT LeadingZeroBits(T x) { if(0 == x)return 32; return (UINT)__builtin_clz((DWORD)x); }
			static UINT TrailingZeroBits(T x) { if(0 == x)return 32; return (UINT)__builtin_ctz((DWORD)x); }
			static UINT NonzeroBits(T x) { return (UINT)__builtin_popcount((DWORD)x); }
			static T	ByteOrderSwap(T x) { return __builtin_bswap32((DWORD)x); }
#if defined(PLATFORM_LINUX)
            static BYTE AddCarry(BYTE carry, T a, T b, T* c){ return _addcarry_u32(carry, (UINT)a, (UINT)b, (UINT*)c); }
            static BYTE SubBorrow(BYTE carry, T a, T b, T* c) { return _subborrow_u32(carry, (UINT)a, (UINT)b, (UINT*)c); }
#else
            static BYTE AddCarry(BYTE carry, T a, T b, T* c){ UINT carry_out; *(UINT*)c = __builtin_addc((UINT)a, (UINT)b, carry, &carry_out); return (BYTE)carry_out; }
			static BYTE SubBorrow(BYTE carry, T a, T b, T* c){ UINT carry_out; *(UINT*)c = __builtin_subc((UINT)a, (UINT)b, carry, &carry_out); return (BYTE)carry_out; }
#endif
#endif
        };
		template<typename T> struct AdvBitOps<T, 64>
		{
#if defined(PLATFORM_WIN)
	#if defined(PLATFORM_64BIT)
			static UINT LeadingZeroBits(T x) { ULONG index; return _BitScanReverse64(&index, (ULONGLONG)x) ? 64U - 1U - (UINT)index : 64U; }
			static UINT TrailingZeroBits(T x) { ULONG index; return _BitScanForward64(&index, (ULONGLONG)x) ? (UINT)index : 64U; }
			static UINT NonzeroBits(T x) { return (UINT)__popcnt64((ULONGLONG)x); }
			static T	ByteOrderSwap(T x) { return (T)_byteswap_uint64((ULONGLONG)x); }
            static BYTE AddCarry(BYTE carry, T a, T b, T* c){ return _addcarry_u64(carry, (ULONGLONG)a, (ULONGLONG)b, (ULONGLONG*)c); }
            static BYTE SubBorrow(BYTE carry, T a, T b, T* c) { return _subborrow_u64(carry, (ULONGLONG)a, (ULONGLONG)b, (ULONGLONG*)c); }
	#endif
#else
			static UINT LeadingZeroBits(T x) { if(0 == x)return 64; return (UINT)__builtin_clzll((ULONGLONG)x); }
			static UINT TrailingZeroBits(T x) { if(0 == x)return 64; return (UINT)__builtin_ctzll((ULONGLONG)x); }
			static UINT NonzeroBits(T x) { return (UINT)__builtin_popcountll((ULONGLONG)x); }
			static T	ByteOrderSwap(T x) { return (T)__builtin_bswap64((ULONGLONG)x); }
#if defined(PLATFORM_LINUX)
            static BYTE AddCarry(BYTE carry, T a, T b, T* c){ return _addcarry_u64(carry, (ULONGLONG)a, (ULONGLONG)b, (unsigned long long*)c); }
            static BYTE SubBorrow(BYTE carry, T a, T b, T* c) { return _subborrow_u64(carry, (ULONGLONG)a, (ULONGLONG)b, (unsigned long long*)c); }
#else
            static BYTE AddCarry(BYTE carry, T a, T b, T* c){ ULONGLONG carry_out; *(ULONGLONG*)c = __builtin_addcll((ULONGLONG)a, (ULONGLONG)b, carry, (unsigned long long*)&carry_out); return (BYTE)carry_out; }
            static BYTE SubBorrow(BYTE carry, T a, T b, T* c){ ULONGLONG carry_out; *(ULONGLONG*)c = __builtin_subcll((ULONGLONG)a, (ULONGLONG)b, carry, (unsigned long long*)&carry_out); return (BYTE)carry_out; }
#endif			
#endif
		};
} // namespace _details
	
template<typename T> UINT LeadingZeroBits(T x) { return _details::AdvBitOps<T>::LeadingZeroBits(x); }
template<typename T> UINT TrailingZeroBits(T x) { return _details::AdvBitOps<T>::TrailingZeroBits(x); }
template<typename T> UINT NonzeroBits(T x) { return _details::AdvBitOps<T>::NonzeroBits(x); }
template<typename T> T	  ByteOrderSwap(T x) { return _details::AdvBitOps<T>::ByteOrderSwap(x); }
template<typename T> UINT Log2(T x){ return sizeof(T)*8 - 1 - LeadingZeroBits(x); }
template<typename T> BYTE SubBorrow(BYTE b_in, T a, T b, T* out){ return _details::AdvBitOps<T>::SubBorrow(b_in, a, b, out); }
template<typename T> BYTE AddCarry(BYTE b_in, T a, T b, T* out){ return _details::AdvBitOps<T>::AddCarry(b_in, a, b, out); }
}


namespace rt
{
/** \defgroup runtime_base runtime_base
 * @ingroup rt
 *  @{
 */
template<typename T> class TypeTraits;
template<typename T1, typename T2> struct IsTypeSame;

template<typename T_NUM>
bool CyclicLessThanOrEqual(T_NUM a, T_NUM b)
{
	static_assert(rt::TypeTraits<T_NUM>::IsNumeric, "T_NUM must be native numeric type");
	static_assert(rt::IsTypeSame<typename rt::TypeTraits<T_NUM>::t_Unsigned, T_NUM>::Result, "T_NUM must be unsigned type");
	static const T_NUM sign_bit = ((T_NUM)1)<<(sizeof(T_NUM)*8-1);

	if((a^b) > sign_bit)
	{	// warpped
		if(a < b)return b - a < sign_bit;
		else if(b < a)return a - b > sign_bit;
		else return true;
	}
	else
	{	return a<=b;
	}
}

template<typename T_NUM>
bool CyclicLessThan(T_NUM a, T_NUM b)
{
	static_assert(rt::TypeTraits<T_NUM>::IsNumeric, "T_NUM must be native numeric type");
	static_assert(rt::IsTypeSame<typename rt::TypeTraits<T_NUM>::t_Unsigned, T_NUM>::Result, "T_NUM must be unsigned type");
	static const T_NUM sign_bit = ((T_NUM)1)<<(sizeof(T_NUM)*8-1);

	if((a^b) > sign_bit)
	{	// warpped
		if(a < b)return b - a < sign_bit;
		else if(b < a)return a - b > sign_bit;
		else return true;
	}
	else
	{	return a<b;
	}
}

namespace _details
{
/**
 * @brief first item equal to or greater than that of a specified key
 * 
 * T should have operator [], and the element should have operator <  
 * @tparam T 
 * @tparam t_Val 
 * @tparam t_GetKey 
 * @param arr 
 * @param len 
 * @param key 
 * @return INLFUNC 
 */
template<class T, typename t_Val, class t_GetKey>	
INLFUNC SIZE_T _LowerBound(const T& arr, SIZE_T len, const t_Val &key)	
{
	if(len == 0 || !(t_GetKey::Key(arr[0]) < key))return 0;
	if( !(t_GetKey::Key(arr[len - 1]) < key) ){}
	else{ return len; }

	SIZE_T ret = len - 1;
	SIZE_T L = 0;
	while ( L + 1 < ret )
	{	SIZE_T mid = (L + ret) >> 1;
		if ( t_GetKey::Key(arr[mid]) < key )
			L = mid;
		else
			ret = mid;					
	}
	return ret;
}
/**
 * @brief first item equal to key, or length of arr
 * 
 * @tparam T 
 * @tparam t_Val 
 * @tparam t_GetKey 
 * @param arr 
 * @param len 
 * @param key 
 * @return INLFUNC 
 */
template<class T, typename t_Val, class t_GetKey>
INLFUNC SIZE_T _BinarySearch(const T& arr, SIZE_T len, const t_Val &key)	
{
	SIZE_T r = _LowerBound<T,t_Val,t_GetKey>(arr,len,key);
	if(r<len && key < t_GetKey::Key(arr[r]))return len;
	return r;
}

struct _TrivialGetKey
{	template<typename T> static INLFUNC T& Key(T& x){ return x; }
};

} // namespace _details

/**
 * @brief first item equal to or greater than that of a specified key
 * 
 *  T should have operator [], and the element should have operator <
 * @tparam t_GetKey 
 * @tparam T 
 * @tparam t_Val 
 * @param arr 
 * @param len 
 * @param key 
 * @return INLFUNC 
 */
template<class t_GetKey, class T, typename t_Val>	// T should have operator [], and the element should have operator <
INLFUNC SIZE_T LowerBound(const T& arr, SIZE_T len, const t_Val &key)	// first item equal to or greater than that of a specified key
{	return _details::_LowerBound<T,t_Val,t_GetKey>(arr,len,key);
}

/**
 * @brief first item equal to key, or length of arr
 * 
 * @tparam t_GetKey 
 * @tparam T 
 * @tparam t_Val 
 * @param arr 
 * @param len 
 * @param key 
 * @return INLFUNC 
 */
template<class t_GetKey, class T, typename t_Val> // T should have operator [], and the element should have operator <
INLFUNC SIZE_T BinarySearch(const T& arr, SIZE_T len, const t_Val &key)	// first item equal to key, or length of arr
{	return _details::_BinarySearch<T,t_Val,t_GetKey>(arr,len,key);
}

/**
 * @brief first item equal to or greater than that of a specified key
 * 
 * T should have operator [], and the element should have operator <
 * @tparam T 
 * @tparam t_Val 
 * @param arr 
 * @param len 
 * @param key 
 * @return FORCEINL 
 */
template<class T, typename t_Val>	
INLFUNC SIZE_T LowerBound(const T& arr, SIZE_T len, const t_Val &key)	// first item equal to or greater than that of a specified key
{	return _details::_LowerBound<T,t_Val,_details::_TrivialGetKey>(arr,len,key);
}

/**
 * @brief first item equal to key, or length of arr
 * 
 * @tparam T 
 * @tparam t_Val 
 * @param arr 
 * @param len 
 * @param key 
 * @return FORCEINL 
 */
template<class T, typename t_Val>
INLFUNC SIZE_T BinarySearch(const T& arr, SIZE_T len, const t_Val &key)	// first item equal to key, or length of arr
{	return _details::_BinarySearch<T,t_Val,_details::_TrivialGetKey>(arr,len,key);
}

template<class T>
class ObjRef
{	
protected:
	T*	_p;
public:
	typedef T	t_Obj;
	INLFUNC ObjRef(T*x):_p(x){}
	INLFUNC ObjRef(){ Empty(); }
	INLFUNC T* operator ->(){ return _p; }
	INLFUNC const T* operator ->() const { return _p; }
	INLFUNC operator T& () { return *_p; }
	INLFUNC operator const T& () const { return *_p; }
	INLFUNC operator T* () { return _p; }
	INLFUNC operator const T* () const { return _p; }

	INLFUNC T* operator = (T*x){ _p = x; return x; }

	INLFUNC bool	IsEmpty() const { return _p == nullptr; }  
	INLFUNC void	Empty(){ _p=nullptr; }
	INLFUNC void	SafeDel(){ _SafeDel(_p); }
	INLFUNC void	SafeRelease(){ _SafeRelease(_p); }
};

template<typename T, bool has_default_obj = true>
class Singleton;
	template<typename T>
	class Singleton<T, true>
	{   typedef T* LPT;
		static LPT& _Ptr(){ static T* ptr = nullptr; return ptr; }
		static T&   _Def(){ static T ret; return ret; }
	public:
		static T&   Get(){ T* p = _Ptr(); return p?*p:_Def(); }
		static bool HasInstance(){ return _Ptr(); }
	protected:
		Singleton(){ ASSERT(_Ptr() == nullptr); _Ptr() = static_cast<T*>(this); }
		~Singleton(){ ASSERT(_Ptr()); _Ptr() = nullptr; }
	};
	template<typename T>
	class Singleton<T, false>
	{   typedef T* LPT;
		static LPT& _Ptr(){ static T* ptr = nullptr; return ptr; }
	public:
		static T&   Get(){ T* p = _Ptr(); ASSERT(p); return *p; }
		static bool HasInstance(){ return _Ptr(); }
	protected:
		Singleton(){ ASSERT(_Ptr() == nullptr); _Ptr() = static_cast<T*>(this); }
		~Singleton(){ ASSERT(_Ptr()); _Ptr() = nullptr; }
	};

struct FrequencyDivision
{
	UINT	_TickDiv;
	UINT	_Interval;
	UINT	_TriggerEdge;
public:
	FrequencyDivision(UINT intv, UINT edge = 0){ SetInterval(intv, edge); Reset(); }
	void Reset(){ _TickDiv = 0; }
	void SetInterval(UINT intv, UINT edge = 0){ ASSERT(intv > edge); _Interval = intv; _TriggerEdge = edge; }
	bool Hit(UINT tick)
	{	UINT td = tick/_Interval;
		if(td >= _TickDiv && (tick%_Interval)>=_TriggerEdge){ _TickDiv = td+1; return true; }
		if(td + 1 < _TickDiv)_TickDiv = td;
		return false;
	}
	bool operator ()(UINT tick){ return Hit(tick); }
};

template<typename T>
class ObjectPlaceHolder
{
	BYTE	_Place[sizeof(T)];
	bool	_bInit;
	void	_Copy(const ObjectPlaceHolder<T>& x){ if(x._bInit){ new (_Place) T(x); _bInit = true; }else{ _bInit = false; } }

public:
	ObjectPlaceHolder(){ _bInit = false; }
	ObjectPlaceHolder(const T& x){ new (_Place) T(x); _bInit = true; }
	ObjectPlaceHolder(const ObjectPlaceHolder<T>& x){ _Copy(x); }

	const T& operator = (const T& x){ Term(); new (_Place) T(x); _bInit = true; return x; }
	const ObjectPlaceHolder<T>& operator = (const ObjectPlaceHolder<T>& x){ Term(); _Copy(x); return x; }

	~ObjectPlaceHolder(){ Term(); }
	void Term(){ if(_bInit){ _bInit = false; ((T*)_Place)->~T(); } }

	ObjectPlaceHolder<T>&	Init(){ ASSERT(!_bInit); new (_Place) T; _bInit = true; return *this; }
	ObjectPlaceHolder<T>&	Reinit(){ Term(); new (_Place) T; _bInit = true; return *this; }

	ObjectPlaceHolder<T>&	Init(const ObjectPlaceHolder<T>& x){ ASSERT(!_bInit); _Copy(x); return *this; }
	ObjectPlaceHolder<T>&	Reinit(const ObjectPlaceHolder<T>& x){ Term(); _Copy(x); return *this; }

	template<typename... Params>
	ObjectPlaceHolder<T>&	Init(Params&&... args){ ASSERT(!_bInit); new (_Place) T(std::forward<Params>(args)...); _bInit = true; return *this; }
	template<typename... Params>
	ObjectPlaceHolder<T>&	Reinit(Params&&... args){ Term(); return Init(args...); }

	// for virtual classes
	template<typename DERIVED, typename... Params>
	ObjectPlaceHolder<T>&	InitByDerived(Params&&... args){ ASSERT(!_bInit); ASSERT(sizeof(T) == sizeof(DERIVED)); new (_Place) DERIVED(std::forward<Params>(args)...); _bInit = true; return *this; }
	template<typename DERIVED, typename... Params>
	ObjectPlaceHolder<T>&	ReinitByDerived(Params&&... args){ Term(); return InitByDerived<DERIVED>(args...); }

	T&						Object(){ return *(T*)_Place; }
	const T&				Object() const { return *(const T*)_Place; }
	bool					IsInitialized() const { return _bInit; }

	operator T&				(){ ASSERT(_bInit); return *(T*)_Place; }
	operator const T&		() const { ASSERT(_bInit); return *(const T*)_Place; }
	operator T*				(){ ASSERT(_bInit); return (T*)_Place; }
	operator const T*		() const { ASSERT(_bInit); return (const T*)_Place; }

	T* operator ->			(){ ASSERT(_bInit); return (T*)_Place; }
	const T* operator ->	() const { ASSERT(_bInit); return (const T*)_Place; }
};



/**
 * @brief simple pseudo-random number generator invented by George Marsaglia. It's a non-crypto PRNG.
 * 
 * http://en.wikipedia.org/wiki/Random_number_generation
 */
class Randomizer
{
	UINT m_z, m_w;
public:
	INLFUNC Randomizer(UINT seed = 17)
	{	if(seed==0 || seed==0x464fffff || (seed*seed)==0x9068ffff)seed+=0x52897528;
		m_w = seed;
		m_z = seed*seed;
	}
	INLFUNC UINT GetNext()
	{	m_z = 36969 * (m_z & 65535) + (m_z >> 16);
		m_w = 18000 * (m_w & 65535) + (m_w >> 16);
		return (m_z << 16) + m_w;
	}
	template<typename T>
	INLFUNC auto& Randomize(T& pod){ return Randomize(&pod, sizeof(T)); }
	INLFUNC auto& Randomize(LPVOID p_in, SIZE_T sz)
	{	UINT* p = (UINT*)p_in;
		for(UINT i=0;i<sz/sizeof(UINT);i++)
			p[i] = GetNext();
		if(sz&3)
		{	BYTE num[4];
			*((UINT*)num) = GetNext();
			LPBYTE t = ((LPBYTE)p_in) + (sz&(~3));
			LPBYTE tend = ((LPBYTE)p_in) + sz;
			for(SIZE_T i=0;t<tend;t++, i++)
				*t = num[i];
		}
		return *this;
	}
	INLFUNC operator UINT(){ return GetNext(); }
};

// ASSERT_NO_FUNCTION_REENTRY
// declare recursive invocation of a function is not allowed
// parallel invocation from different thread is *NOT* recursive, which is allowed
namespace _details
{
struct ReentryCheck
{	bool& _Entered;
	ReentryCheck(bool& c):_Entered(c){ ASSERT(!_Entered); _Entered = true; } // ASSERT_NO_FUNCTION_REENTRY voliated
	~ReentryCheck(){ _Entered = false; }
};
} // namespace _details

#if defined(PLATFORM_DEBUG_BUILD)
#define ASSERT_NO_FUNCTION_REENTRY	thread_local bool ___RT_REENTRY_FLAG = false; rt::_details::ReentryCheck ___RT_REENTRY_FLAG_CHECK(___RT_REENTRY_FLAG); // no reentry in the same thread
#else
#define ASSERT_NO_FUNCTION_REENTRY	{}
#endif

/** @}*/
} // namespace rt
////////////////////////////////////////////////////////////////////////////


/** @}*/
/** @}*/
