#pragma once
/**
 * @file string_type_ops.h
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

#include "string_type.h"


namespace rt
{
namespace _details
{
template<typename T>
String_Ref __alloca_string_ref(LPSTR p, const T& x)
{	UINT len;
	len = (UINT)x.CopyTo(p);
	return String_Ref(p, len);
}
}} // namespace rt::_details


namespace rt
{
namespace tos
{
/** \defgroup string_type_ops string_type_ops
 * @ingroup rt
 *  @{
 */
typedef ::rt::tos::S_<> Number;

struct WhiteSpace:public ::rt::tos::S_<>
{	INLFUNC WhiteSpace(int len)
	{	ASSERT(len+1 < (int)sizeof(_string));
		for(int i=0;i<len;i++)_p[i] = ' ';
		_p[len] = '\0';
		_len = len;
	}
};

struct character:public ::rt::tos::S_<>
{	INLFUNC character(char c)
	{	_p[0] = c;	_p[1] = '\0';
		_len = 1;
	}
};

struct StaticString: public ::rt::String_Ref
{	
public:
	//INLFUNC StaticString(LPCSTR x)    // don't define those, which will always be hit
	//INLFUNC StaticString(LPSTR x)
	INLFUNC StaticString(){}
	INLFUNC StaticString(const char* p, SIZE_T len): ::rt::String_Ref(p, len){}
	template<typename T>
	INLFUNC StaticString(T& x)
	{	static_assert(rt::TypeTraits<typename rt::Remove_Reference<T>::t_Result>::Typeid == _typeid_array, "StaticString accepts only C String literal");
		String_Ref::_p = (char*)x;
		String_Ref::_len = sizeof(T) - 1;
	}
	operator LPCSTR () const { return _p; }
};

struct DataAsString: public ::rt::String_Ref
{
	template<typename T>
	INLFUNC DataAsString(const T& x)
		: ::rt::String_Ref((LPCSTR)&x, (SIZE_T)(sizeof(x)))
	{}
	INLFUNC DataAsString(LPCVOID x, SIZE_T bytes)
		: ::rt::String_Ref((LPCSTR)x, bytes)
	{}
};

struct StdStringAsString: public ::rt::String_Ref
{
	template<typename std_string>
	INLFUNC StdStringAsString(const std_string& str)
		: ::rt::String_Ref(str.data(), str.size())
	{}
};

template<UINT LEN = 256>
struct StringOnStack:public ::rt::tos::S_<1,LEN>
{	typedef ::rt::tos::S_<1,LEN> _SC;
	template<class T>
    INLFUNC StringOnStack(const T& x)
	{	_SC::_len = x.CopyTo(_SC::_p);
		ASSERT(LEN>=_SC::_len);
		_SC::_p[_SC::_len] = 0;
	}
	INLFUNC operator LPCSTR() const { return _SC::_p; }
	INLFUNC StringOnStack<LEN>& operator += (const rt::String_Ref& x)
	{	ASSERT(x.GetLength() + _SC::GetLength() < LEN - 1);
		memcpy(&_SC::_p[_SC::_len], x.Begin(), x.GetLength());
		_SC::_len+=x.GetLength();
		_SC::_p[_SC::_len] = 0;
		return *this;
	}
};

template<bool upper_case = true, bool compact = false, char unit = 'B'>
struct FileSize:public ::rt::tos::S_<>
{	
	INLFUNC FileSize(ULONGLONG filesize)
	{
		int up = upper_case?0:('a' - 'A');
		rt::String_Ref sep;
		if(!compact)sep = " ";

		rt::String_Ref empty;
		if(filesize < 1024)
			SetString(empty + (UINT)(filesize) + sep + (char)(unit));
		else if(filesize < 1024*1024)
			SetString(empty + (float)(filesize/1024.f) + sep + (char)('K'+up) + (char)(unit));
		else if(filesize < 1024*1024*1024)
			SetString(empty + (float)(filesize/1024/1024.f) + sep + (char)('M'+up) + (char)(unit));
		else if(filesize < 1024LL*1024*1024*1024)
			SetString(empty + (float)(filesize/1024/1024/1024.f) + sep + (char)('G'+up) + (char)(unit));
		else if(filesize < 1024LL*1024*1024*1024*1024)
			SetString(empty + (float)(filesize/1024/1024/1024/1024.f) + sep + (char)('T'+up) + (char)(unit));
		else
			SetString(empty + (float)(filesize/1024/1024/1024/1024/1024.f) + sep + (char)('P'+up) + (char)(unit));
	}
private:
	template<class T>
	INLFUNC void SetString(const T& x)
	{	ASSERT(x.GetLength() < sizeofArray(_string)-1);
		_len = x.CopyTo(_string);
		_string[_len] = '\0';
	}
};

template<bool _smart = true>
struct TimeSpan:public ::rt::tos::S_<>
{	template<typename time_type>
	INLFUNC TimeSpan(time_type msec)
	{	char* p = _string;
		if(msec < 0){ p[0]='-'; p++; msec = (time_type)(-(typename rt::TypeTraits<time_type>::t_Signed)msec); }  // just for making compiler happy 
		if(msec >= 10000)
		{	msec = (time_type)(msec/1000.0f + 0.5f);
			if(msec >= 3600*24)
			{	p+=sprintf(p,"%d",(int)(msec/(3600*24)));
				p[0]='d';	p++;
				if(_smart && (msec%(3600*24)) == 0)
				{	p[-1] = ' '; p[0] = 'd';	p[1] = 'a';	p[2] = 'y';	p+=3;
					if(msec >= 3600*48){p[0] = 's';	p++;  }
					goto END_OF_PRINT;
				}
				p[0]=':';	p++;
			}
			if(msec >= 3600)
			{	p+=sprintf(p,"%d",(int)((msec%(3600*24))/3600));
				p[0]='h';	p++;
				if(_smart && (msec%3600) == 0)
				{	if(msec < 3600*24)
					{	p[-1] = ' '; p[0] = 'h';	p[1] = 'o';	p[2] = 'u';	p[3] = 'r';	p+=4;
						if(msec >= 7200){   p[0] = 's';	p++; }
					}
					goto END_OF_PRINT;
				}
				p[0]=':';	p++;
			}
			if(msec >= 60)
			{	p+=sprintf(p,"%d",(int)((msec%(3600))/60));
				p[0]='m';	p++;
				if(_smart && (msec%60) == 0)
				{	if(msec < 3600)
					{	p[-1] = ' '; p[0] = 'm';	p[1] = 'i';	p[2] = 'n';
						p[3] = 'u';	p[4] = 't';	p[5] = 'e';	p+=6;
						if(msec >= 120){ p[0] = 's'; p++; }
					}
					goto END_OF_PRINT;
				}
				p[0]=':';	p++;
			}
			p+=sprintf(p,"%d",(int)(msec%60));
			p[0]='s';				p++;
			if(_smart && msec < 60)
			{	p[-1]=' '; p[0]='s'; p[1]='e'; p[2]='c'; p[3]='o'; p[4]='n'; p[5]='d'; p+=6;
				if(msec > 1){ p[0]='s'; p++; }
			}
		}
		else
		{	
			p[0] = ('0' + (int)(msec/1000));	p++;
			int frac = (int)(msec%1000);
			if(frac)
			{	p[0] = '.';	p++;
				p[0] = ('0' + (int)(msec%1000)/100);
				p[1] = ('0' + (int)(msec%100)/10);
				p[2] = ('0' + (int)(msec%10));
				p+=3;
			}
			if(!_smart){ p[0] = 's'; p++; }
			else
			{	p[0]=' '; p[1]='s'; p[2]='e'; p[3]='c'; p[4]='o'; p[5]='n'; p[6]='d'; p+=7;
				if(msec >= 2000){ p[0]='s'; p++; }
			}
		}
END_OF_PRINT:
		p[0] = '\0';
		_len = (int)(p-_string);
	}
};


template<int SEP = '/',bool no_year = false>
struct Date:public ::rt::tos::S_<>
{
	template<typename t_os_Date32>
	INLFUNC Date(const t_os_Date32& x)
	{	LPCSTR print_template = "%04d/%02d/%02d";
		if(!no_year)
		{
			_len = sprintf(_string,print_template, x.GetYear(), x.GetMonth(), x.GetDay());
			if(SEP != '/')
			{	_string[4] = _string[7] = SEP;
			}
		}
		if(no_year)
		{
			_len = sprintf(_string,print_template+5, x.GetMonth(), x.GetDay());
			if(SEP != '/')
			{	_string[2] = SEP;
			}
		}
	}
};

template<SIZE_T LEN = 65, bool uppercase = true>
struct HexNum:public ::rt::tos::S_<1,LEN>
{
	template<typename T>
	INLFUNC HexNum(const T& x){ new (this) HexNum(&x, sizeof(x)); }
	INLFUNC HexNum(LPCVOID pbyte, int len)
	{	
		const char char_base = uppercase?'A':'a';
		typedef ::rt::tos::S_<1,LEN> _SC;
		ASSERT(len < (int)sizeofArray( _SC::_string)/2);
		LPSTR p =  _SC::_string;
		int i=0;
		for(;i<len-1 && ((LPCBYTE)pbyte)[len - i - 1] == 0; i++);
		for(;i<len;i++,p+=2)
		{
			BYTE v = ((LPCBYTE)pbyte)[len - i - 1];
			p[0] = (v>=0xa0?char_base+((v-0xa0)>>4):'0'+(v>>4));
			v = v&0xf;
			p[1] = (v>=0xa?char_base+(v-0xa):'0'+v);
		}
		*p = 0;
		 _SC::_len = (p-_SC::_string);
		 _SC::_p[ _SC::_len] = 0;
	}
};

template<SIZE_T LEN = 65, bool uppercase = true>
struct Binary:public ::rt::tos::S_<1,LEN>
{
	template<typename T>
	INLFUNC Binary(const T& x){ new (this) Binary(&x, sizeof(x)); }
	INLFUNC Binary(LPCVOID pbyte, int len)
	{	
		const char char_base = uppercase?'A':'a';
		typedef ::rt::tos::S_<1,LEN> _SC;
		ASSERT(len < (int)sizeofArray( _SC::_string)/2);
		LPSTR p =  _SC::_string;
		for(int i=0;i<len;i++,p+=2)
		{
			BYTE v = ((LPCBYTE)pbyte)[i];
			p[0] = (v>=0xa0?char_base+((v-0xa0)>>4):'0'+(v>>4));
			v = v&0xf;
			p[1] = (v>=0xa?char_base+(v-0xa):'0'+v);
		}
		 _SC::_len = len*2;
		 _SC::_p[ _SC::_len] = 0;
	}
};

template<SIZE_T LEN = 65>
struct BinaryCString:public ::rt::tos::S_<1,LEN>
{
	INLFUNC BinaryCString(const rt::String_Ref& d){ new (this) BinaryCString(d.Begin(), (UINT)d.GetLength()); }
	INLFUNC BinaryCString(LPCVOID pbyte, int len)
	{	
		typedef ::rt::tos::S_<1,LEN> _SC;
		ASSERT(len < (int)sizeofArray( _SC::_string)/2);
		LPSTR p =  _SC::_string;
		for(int i=0;i<len;i++,p+=4)
		{
			p[0] = '\\';
			p[1] = 'x';
			BYTE v = ((LPCBYTE)pbyte)[i];
			p[2] = (v>=0xa0?'a'+((v-0xa0)>>4):'0'+(v>>4));
			v = v&0xf;
			p[3] = (v>=0xa?'a'+(v-0xa):'0'+v);
		}
		 _SC::_len = len*4;
		 _SC::_p[ _SC::_len] = 0;
	}
};

struct GUID:public ::rt::tos::S_<>
{
	INLFUNC GUID(const ::GUID& guid)
	{
		if((&guid) != nullptr)
        {	LPCSTR print_template = "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x";
			_len = sprintf(_string,print_template, guid.Data1,guid.Data2,guid.Data3,
							 guid.Data4[0],guid.Data4[1],guid.Data4[2],guid.Data4[3],
							 guid.Data4[4],guid.Data4[5],guid.Data4[6],guid.Data4[7]);
		}
		else
		{	memcpy(_string,"NULL",5);
			_len = 4;
		}
	}
};

} // tos

typedef tos::StaticString SS;
typedef tos::DataAsString DS;
typedef tos::StdStringAsString	StdStr;

// typename to string
namespace _details
{

template<typename __TNAS_T>
struct __TNAS
{	static LPCSTR __TNAS_END()
	{
#if defined(PLATFORM_WIN)
		return __FUNCTION__; 
#else
		return __PRETTY_FUNCTION__;
#endif
	}
};

} // namespace _details

template<typename T>
INLFUNC rt::String_Ref TypeNameToString()
{
	LPCSTR raw_name = _details::__TNAS<T>::__TNAS_END();
	raw_name = strstr(raw_name, "rt::_details::__TNAS<");			ASSERT(raw_name);
	raw_name += 21;
	LPCSTR end = strstr(raw_name, ">::__TNAS_END");					ASSERT(end);
	if(rt::String_Ref(raw_name, end) == rt::SS("__TNAS_T"))
	{	raw_name = strstr(end, "__TNAS_T = ");						ASSERT(raw_name);
		raw_name += 11;
		end = strchr(raw_name,';');
	}
	if(memcmp(raw_name, "struct ", 7) == 0){ raw_name += 7; }
	else if(memcmp(raw_name, "class ", 6) == 0){ raw_name += 6; }
	else if(memcmp(raw_name, "enum ", 5) == 0){ raw_name += 5; }
	rt::String_Ref ret(raw_name, end);
	// check if nested type defined within function scope, and fullback to clang's behavior 
	return ret.Occurrence("()") >= 2?ret.TrimBeforeReverse("):"):ret;
}

namespace _details
{
template<typename T>
LPSTR __alloca_string(LPSTR p, const T& x)
{	p[x.CopyTo(p)] = 0;
	return p;
}
} // namespace rt::_details
} // namespace rt

#define __SS(...)						(rt::SS(#__VA_ARGS__))
#define ALLOCA_STRING_BUFFER(size)		(rt::String_Ref((LPSTR)alloca(size), size))
#define ALLOCA_STRING_REF(x)			(rt::_details::__alloca_string_ref((LPSTR)alloca((x).GetLength()), (x)))	///< x should be a varible, instead of a expression. use auto x = ..... if it need to be an expression
#define ALLOCA_C_STRING(x)				(rt::_details::__alloca_string((LPSTR)alloca((x).GetLength() + 1), (x)))	///< x should be a varible, instead of a expression. use auto x = ..... if it need to be an expression


//////////////////////////////////////////////////////
// Stringify Enum
namespace rt
{
namespace _details
{
template<typename T>
struct _EnumStringify;
template<typename T_Enum>
struct _EnumString
{	
	static LPCSTR	ToString(T_Enum x)
					{	LPCSTR ret = nullptr;
						_EnumStringify<T_Enum>::_Iterate(
							[&ret, x](T_Enum e, const rt::String_Ref& name){
								if(x == e){ ret = name.Begin(); return false; }
								return true;
							}
						);
						return ret;
					}
	static T_Enum	FromString(const rt::String_Ref& name, T_Enum default_val = (T_Enum)-1)
					{	
						_EnumStringify<T_Enum>::_Iterate(
							[&default_val, &name](T_Enum e, const rt::String_Ref& e_name){
								if(name == e_name){ default_val = e; return false; }
								return true;
							}
						);
						return default_val;
					}
};
} // namespace _details

#define STRINGIFY_ENUM_BEGIN_(type)				namespace rt {								\
												namespace _details {						\
												template<>									\
												struct _EnumStringify<type>					\
												{	typedef ::type TYPE;					\
													template<typename T_FUNC>				\
													static bool _Iterate(T_FUNC&& c){		
#define STRINGIFY_ENUM_BEGIN(type, ns)			namespace rt {								\
												namespace _details {						\
												using namespace ns;							\
												template<>									\
												struct _EnumStringify<type>					\
												{	typedef ::ns::type TYPE;				\
													template<typename T_FUNC>				\
													static bool _Iterate(T_FUNC&& c){		\
														using namespace ::ns;
#define STRINGIFY_ENUM(enum_val)						if(!c(TYPE::enum_val, rt::SS(#enum_val), (TYPE)0xffffffffU))return true;
#define STRINGIFY_ENUM_BIT(enum_val)					if(!c(TYPE::enum_val, rt::SS(#enum_val), TYPE::enum_val))return true;
#define STRINGIFY_ENUM_BITS(enum_val, enum_mask)		if(!c(TYPE::enum_val, rt::SS(#enum_val), TYPE::enum_mask))return true;
#define STRINGIFY_ENUM_END(type, ns)					return false;												\
													}																\
												};}}																\
												namespace ns {														\
												template<class t_Ostream>											\
												INLFUNC t_Ostream& operator<<(t_Ostream& Ostream, type x)			\
												{	Ostream<<::rt::EnumStringify(x);								\
													return Ostream;													\
												}	STRINGIFY_ENUM_OPS(type)										\
												}
#define STRINGIFY_ENUM_END_(type)						return false;												\
													}																\
												};}}																\
												template<class t_Ostream>											\
												INLFUNC t_Ostream& operator<<(t_Ostream& Ostream, type x)			\
												{	Ostream<<::rt::EnumStringify(x);								\
													return Ostream;													\
												}	STRINGIFY_ENUM_OPS(type)
#define STRINGIFY_ENUM_END2(type, ns1, ns2)				return false;												\
													}																\
												};}}																\
												namespace ns1 { namespace ns2 {										\
												template<class t_Ostream>											\
												INLFUNC t_Ostream& operator<<(t_Ostream& Ostream, type x)			\
												{	Ostream<<::rt::EnumStringify(x);								\
													return Ostream;													\
												}	STRINGIFY_ENUM_OPS(type)										\
												}}
#define STRINGIFY_ENUM_OPS(type)				INLFUNC type operator | (type a, type b){ return (type)((uint64_t)a|(uint64_t)b); }	\
												INLFUNC type operator & (type a, type b){ return (type)((uint64_t)a&(uint64_t)b); } \
												INLFUNC type operator ^ (type a, type b){ return (type)((uint64_t)a^(uint64_t)b); } \
												INLFUNC type operator |= (type& a, type b){ return a = (type)((uint64_t)a|(uint64_t)b); } \
												INLFUNC type operator &= (type& a, type b){ return a = (type)((uint64_t)a&(uint64_t)b); } \
												INLFUNC type operator ^= (type& a, type b){ return a = (type)((uint64_t)a^(uint64_t)b); } \
												INLFUNC type operator ~ (type b){ return (type)(~((uint64_t)b)); } \

class EnumStringify: public rt::String_Ref
{	char _Str[320];
	template<typename T> void _append(const T& x)
	{	UINT sz = (UINT)x.GetLength();	if(_len + sz >= sizeof(_Str))return;
		x.CopyTo(_p + _len);			_len += sz;		_Str[_len] = 0;
	}
	void _append(char x){ if(_len + 1 >= sizeof(_Str))return; _p[_len++] = x; _p[_len] = 0; }
public:
	template<typename T_Enum>
	INLFUNC EnumStringify(T_Enum x)
	{	static_assert(sizeof(T_Enum)<=sizeof(UINT), "Enum cannot fit in a DWORD");
		_p = _Str; _len = 0;
		::rt::_details::_EnumStringify<T_Enum>::_Iterate(
			[&x, this](T_Enum e, const rt::String_Ref& name, T_Enum mask){
				if((((UINT)x)&((UINT)mask)) == (UINT)e)
				{	if(!IsEmpty())_append('|');
					_append(name);
					x = (T_Enum) (((UINT)x)&(~(UINT)mask));
					if((UINT)x == 0)return false;
				}
				return true;
			}
		);
		if((UINT)x != 0)
		{	if(!IsEmpty())_append('|');
			_append(rt::tos::Number((int)x));
		}
	}
};

template<typename T_Enum>
INLFUNC bool	EnumParse(const rt::String_Ref& name, T_Enum& value_out)
				{	rt::String_Ref tags[sizeof(T_Enum)*8];
					UINT co = name.Split(tags, sizeofArray(tags), "|,+;");
					value_out = (T_Enum)0;
					for(UINT i=0; i<co; i++)
					{	auto tag = tags[i].TrimSpace();
						if(tag.IsEmpty())continue;
						if((tag[0] >= '0' && tag[0] <= '9') || (tag[0] == '-' && tag[1] >= '0' && tag[1] <= '9'))
						{	UINT x;
							tag.ToNumber(x);
							value_out = (T_Enum)((UINT)value_out | (UINT)x);
						}
						else
						{	if(!::rt::_details::_EnumStringify<T_Enum>::_Iterate(
									[&value_out, &tag](T_Enum e, const rt::String_Ref& e_name, T_Enum mask){
										if(tag == e_name)
										{	value_out = (T_Enum)((UINT)value_out | (UINT)e);
											return false;
										}
										return true;
									}
								)
							)return false;
					}	}
					return true;
				}
			/** @}*/
} // namespace rt
/** @}*/