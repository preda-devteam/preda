#pragma once
/**
 * @file string_type.h
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

#include "type_traits.h"
#include "mem_alloc.h"

#ifdef PLATFORM_LINUX
#include <cstring>
#endif

namespace rt
{
/** \defgroup string_type string_type
 * @ingroup rt
 *  @{
 */
namespace _details
{
#pragma warning(disable:4146)
/**
 * @brief code adapted based on modp_numtoa.h/.c (http://code.google.com/p/stringencoders/)
 * 
 */
struct string_ops
{	
	static void strreverse(char* begin, char* end){ char aux; while(end > begin)aux = *end, *end-- = *begin, *begin++ = aux; }
	static int	itoa(INT value, char* str)
				{	char* wstr=str;
					// Take care of sign
					unsigned int uvalue = (value < 0) ? -value : value;
					// Conversion. Number is reversed.
					do {*wstr++ = (char)(48 + (uvalue % 10));}while(uvalue /= 10);
					if (value < 0)*wstr++ = '-';
					*wstr='\0';
					// Reverse string
					strreverse(str,wstr-1);
					return (int)(wstr - str);
				}
	static int	itoa(UINT value, char* str)
				{	char* wstr=str;
					// Conversion. Number is reversed.
					do {*wstr++ = (char)(48 + (value % 10));}while (value /= 10);
					*wstr='\0';
					// Reverse string
					strreverse(str, wstr-1);
					return (int)(wstr - str);
				}
	static int	itoa(LONGLONG value, char* str)
				{	char* wstr=str;
					ULONGLONG uvalue = (LONGLONG)((value < 0) ? -value : value);
					// Conversion. Number is reversed.
					do {*wstr++ = (char)(48 + (uvalue % 10));}while(uvalue /= 10);
					if (value < 0)*wstr++ = '-';
					*wstr='\0';
					// Reverse string
					strreverse(str,wstr-1);
					return (int)(wstr - str);
				}
	static int	itoa(ULONGLONG value, char* str)
				{	char* wstr=str;
					// Conversion. Number is reversed.
					do {*wstr++ = (char)(48 + (value % 10));}while (value /= 10);
					*wstr='\0';
					// Reverse string
					strreverse(str, wstr-1);
					return (int)(wstr - str);
				}
	template<typename T>
	static int	ftoa(T value, char* str, int prec = 2)
				{	static const T pow10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
					// Hacky test for NaN
					// under -fast-math this won't work, but then you also won't have correct nan values anyways.  
					// The alternative is to link with libmath (bad) or hack IEEE double bits (bad)
					if (! (value == value)){ str[0] = 'n'; str[1] = 'a'; str[2] = 'n'; str[3] = '\0'; return 3;	}
					// if input is larger than thres_max, revert to exponential
					const T thres_max = (T)(0x7FFFFFFF);		T diff = 0;
					char* wstr = str;
					if (prec < 0){ prec = 0; }
					else if (prec > 9){ prec = 9; } /* precision of >= 10 can lead to overflow errors */
					// we'll work in positive values and deal with the negative sign issue later
					int neg = 0;
					if(value < 0){	neg = 1; value = -value; }
					int whole = (int) value;					T tmp = (value - whole) * pow10[prec];
					UINT frac = (UINT)(tmp);					diff = tmp - frac;
					if (diff > 0.5) {
						++frac;
						/* handle rollover, e.g.  case 0.99 with prec 1 is 1.0  */
						if(frac >= pow10[prec]){ frac = 0; ++whole; }
					} else if (diff == 0.5 && ((frac == 0) || (frac & 1))) {
						++frac; /* if halfway, round up if odd, OR if last digit is 0.  That last part is strange */
					}
					// for very large numbers switch back to native sprintf for exponentials. anyone want to write code to replace this? 
					// normal printf behavior is to print EVERY whole number digit which can be 100s of characters overflowing your buffers == bad
					if (value > thres_max) {
						char fmt[5] = "%.2e";
						fmt[2] = prec + '0';
						return sprintf(str, fmt, (double)(neg ? -value : value));
					}
					if(prec == 0) {
						diff = value - whole;
						if (diff > 0.5){ ++whole; } /* greater than 0.5, round up, e.g. 1.6 -> 2 */
						else if (diff == 0.5 && (whole & 1)){ ++whole; } // exactly 0.5 and ODD, then round up. 1.5 -> 2, but 2.5 -> 2 
					} else {
						int count = prec;	// now do fractional part, as an unsigned number
						do {
							--count;
							*wstr++ = (char)(48 + (frac % 10));
						} while (frac /= 10);
						while (count-- > 0) *wstr++ = '0'; // add extra 0s
						*wstr++ = '.'; // add decimal
					}
					do *wstr++ = (char)(48 + (whole % 10));		while (whole /= 10);
					if(neg){ *wstr++ = '-'; }					*wstr='\0';
					strreverse(str, wstr-1);					return (int)(wstr-str);
				}
};

template<typename T>
FORCEINL T		_pow(T x, int y){ return (T)pow((double)x,y); }
FORCEINL float	_pow(float x, int y){ return (float)pow(x,y); }

template<typename t_Left, typename t_Right>
class String_AddExpr;

template<UINT BASE, bool base_LE_10 = (BASE<=10)>
struct _to_num
{	static UINT call(int x){ return x>='0'?(x-'0'):BASE; }
};
template<UINT BASE>
struct _to_num<BASE, false>
{	static UINT call(int x)
	{	if(x<='9' && x>='0'){ return x-'0';	}
		else if(x<='A'+(BASE-10) && x>='A'){ return x-'A'+10; }
		else if(x<='a'+(BASE-10) && x>='a'){ return x-'a'+10; }
		else return BASE;
	}	
};
#pragma warning(default:4146)
} // namespace rt::_details
} // namespace rt


namespace rt
{

class CharacterSet
{
protected:
	char	_Set[127]; // model 1 to 127
public:
	void Init(LPCSTR p, LPCSTR mapped, UINT len)
	{	rt::Zero(_Set);
		for(UINT i=0;i<len;i++)
		{	ASSERT(p[i]>=1);
			_Set[p[i]-1] = mapped[i];
		}
	}
	void Init(LPCSTR p, UINT len){ Init(p,p,len); }
	CharacterSet(){ rt::Zero(_Set); }
	CharacterSet(char c){ rt::Zero(_Set); ASSERT(c>=1); _Set[c-1] = c; }
	CharacterSet(LPCSTR p){ Init(p, (UINT)strlen(p)); }
	template<typename T>
	CharacterSet(const T& s){ Init(s.Begin(), (UINT)s.GetLength()); }
	CharacterSet(LPCSTR p, LPCSTR mapped){ Init(p, mapped, (UINT)strlen(p)); }
	template<typename T>
	CharacterSet(const T& s, const T& mapped){ Init(s.Begin(), mapped.Begin(), (UINT)s.GetLength()); }
	bool Has(int c) const 
	{	if(c>=1 && c<=127)
			return _Set[c-1]; 
		else
			return false;
	}
	int Mapped(int c) const  // return 0 for out of the set
	{	if(c>=1 && _Set[c-1])
			return _Set[c-1]; 
		else
			return c;
	}
};

/**
 * @brief Escape for C/Json string
 * 
 */
struct CharacterSet_Escape: public CharacterSet	// 
{	CharacterSet_Escape():CharacterSet("\b\f\r\n\t\v\"\\","bfrntv\"\\"){}
};
/**
 * @brief Unescape for C/Json string
 * 
 */
struct CharacterSet_Unescape: public CharacterSet	
{	CharacterSet_Unescape():CharacterSet("bfrntv\"\\","\b\f\r\n\t\v\"\\"){}
};


struct CharacterSet_ControlChar: public CharacterSet
{	CharacterSet_ControlChar(LPCSTR p):CharacterSet(p)
	{	for(UINT i=1; i<' '; i++)_Set[i-1] = true;
	}
	CharacterSet_ControlChar()
	{	for(UINT i=1; i<' '; i++)_Set[i-1] = true;
	}
};

struct CharacterSet_Alphabet: public CharacterSet
{	CharacterSet_Alphabet(LPCSTR sep_additional = nullptr)
	{	for(int i='a'; i<='z'; i++)_Set[i-1] = true;
		for(int i='A'; i<='Z'; i++)_Set[i-1] = true;
		if(sep_additional)while(*sep_additional)_Set[((int)*sep_additional++)-1] = true;
	}
};

struct CharacterSet_LowerCase: public CharacterSet
{	CharacterSet_LowerCase(LPCSTR sep_additional = nullptr)
	{	for(int i='a'; i<='z'; i++)_Set[i-1] = true;
		if(sep_additional)while(*sep_additional)_Set[((int)*sep_additional++)-1] = true;
	}
};

struct CharacterSet_UpperCase: public CharacterSet
{	CharacterSet_UpperCase(LPCSTR sep_additional = nullptr)
	{	for(int i='A'; i<='Z'; i++)_Set[i-1] = true;
		if(sep_additional)while(*sep_additional)_Set[((int)*sep_additional++)-1] = true;
	}
};

	
struct CharacterSet_Digits: public CharacterSet
{	CharacterSet_Digits()
	{	for(int i='0'; i<='9'; i++)_Set[i-1] = true;
	}
};

struct CharacterSet_Number: public CharacterSet_Digits
{	CharacterSet_Number()
	{	_Set['.'-1] = true;
	}
};

struct CharacterSet_AlphabetDigits: public CharacterSet
{	CharacterSet_AlphabetDigits(LPCSTR sep_additional = nullptr)
	{	for(int i='0'; i<='9'; i++)_Set[i-1] = true;
		for(int i='a'; i<='z'; i++)_Set[i-1] = true;
		for(int i='A'; i<='Z'; i++)_Set[i-1] = true;
		if(sep_additional)while(*sep_additional)_Set[((int)*sep_additional++)-1] = true;
	}
};
/**
 * @brief C/C++ Symbol
 * 
 */
struct CharacterSet_Symbol: public CharacterSet_AlphabetDigits		
{	CharacterSet_Symbol(LPCSTR sep_additional = nullptr):CharacterSet_AlphabetDigits(sep_additional)
	{	_Set[((int)'_')-1] = true;
	}
};

struct CharacterSet_Printable: public CharacterSet_Symbol
{	CharacterSet_Printable():CharacterSet_Symbol(".{}[]|\\\"';:,<>?/-=+`~!@#$%^&*()"){}
};

namespace _details
{
	struct _StringPtrStore
	{	char*	_p;
		size_t	_len;
		bool	IsEmpty() const { return (size_t)this == 0 || _p == nullptr || _len == 0; }
		void	Empty(){ _p = nullptr; _len = 0; }
	};
	template<SIZE_T SIZE_RESERVED>
	struct _StringArrayStore
	{	char	_p[SIZE_RESERVED+1];
		size_t	_len;
		bool	IsEmpty() const { return (size_t)this == 0 || _len == 0; }
		void	Empty(){ _len = 0; }
		static const SIZE_T	_len_reserved = SIZE_RESERVED;
	};
};

class String;

template<typename t_StringStore, class t_StrRef>
class String_Base: public t_StringStore
{	typedef t_StringStore _SC;
public:
	SIZE_T		GetLength() const { return _SC::_len; }
	SIZE_T		CopyTo(char* p) const 
				{	memcpy(p,_SC::_p,GetLength()*sizeof(char));
					return GetLength(); 
				} // terminate-zero is not copied
	SIZE_T		CopyToZeroTerminated(char* p) const 
				{	memcpy(p,_SC::_p,GetLength()*sizeof(char)); 
					p[GetLength()] = '\0';
					return GetLength(); 
				} // terminate-zero is copied
	/**
 	* @brief may NOT terminated by ZERO !!
 	* 
 	* @return const char* 
 	*/
	const char*	Begin() const			{ return _SC::_p; }	
	/**
	 * @brief may NOT terminated by ZERO !!
	 * 
	 * @return char* 
	 */
	char*		Begin()					{ return _SC::_p; }	
	const char*	GetString() const		{ if(_SC::IsEmpty())return ""; ASSERT(IsZeroTerminated()); return _SC::_p; }
	const char*	End() const				{ return _SC::_p+GetLength(); }
	char&		Last()					{ ASSERT(GetLength()); return _SC::_p[GetLength()-1]; }
	const char&	Last() const			{ ASSERT(GetLength()); return _SC::_p[GetLength()-1]; }
	char&		First()					{ ASSERT(GetLength()); return _SC::_p[0]; }
	const char&	First() const			{ ASSERT(GetLength()); return _SC::_p[0]; }
	bool		IsZeroTerminated()const	{ return _SC::_p && _SC::_p[GetLength()] == 0; }
	bool		HasTrailingPathSeparator() const { return Last() == '\\' || Last() == '/'; }
	template<typename t_Str>
	void		ToString(t_Str& str){ str = *this; }
	template<typename T>
	const char&	operator [](T i) const { return _SC::_p[i]; }
	template<typename T>
	char&		operator [](T i){ return _SC::_p[i]; }

	template< class StrT >
	bool		operator < (const StrT& x) const
				{	int ret = memcmp(_SC::_p,x.Begin(),min(GetLength(),x.GetLength())*sizeof(char));
					return (ret < 0) || (ret==0 && (GetLength() < x.GetLength()));
				}
	template< class StrT >
	bool		operator <= (const StrT& x) const
				{	int ret = memcmp(_SC::_p,x.Begin(),min(GetLength(),x.GetLength())*sizeof(char));
					return (ret < 0) || (ret==0 && (GetLength() <= x.GetLength()));
				}
	template< class StrT >
	bool		operator > (const StrT& x) const
				{	int ret = memcmp(_SC::_p,x.Begin(),min(GetLength(),x.GetLength())*sizeof(char));
					return (ret > 0) || (ret==0 && (GetLength() > x.GetLength()));
				}
	template< class StrT >
	bool		operator >= (const StrT& x) const
				{	int ret = memcmp(_SC::_p,x.Begin(),min(GetLength(),x.GetLength())*sizeof(char));
					return (ret > 0) || (ret==0 && (GetLength() >= x.GetLength()));
				}
	/**
	 * @brief editing distance <= 1
	 * 
	 * @tparam StrT 
	 * @param x 
	 * @return true 
	 * @return false 
	 */
	template< class StrT >
	bool		IsSimilarTo(const StrT& x) const  
				{	if(abs((SSIZE_T)_SC::_len - (SSIZE_T)x._len) > 1)return false;
					auto len_max = rt::max(_SC::_len, x._len);
					auto match_len = CommonPrefixLength(x) + CommonSuffixLength(x);
					return match_len >= len_max - 1;
				}
	/**
	 * @brief (*this) is a part of x
	 * 
	 * @tparam StrT 
	 * @param x 
	 * @return true 
	 * @return false 
	 */
	template< class StrT >
	bool		IsReferring(const StrT& x)  
				{	return Begin() >= x.Begin() && (End() <= x.End());
				}
public:
	SIZE_T		CommonPrefixLength(const t_StrRef& x) const { SIZE_T i=0; SIZE_T len = rt::min(GetLength(), x.GetLength()); for(;i<len && _SC::_p[i] == x[i];i++){}; return i; }
	SIZE_T		CommonSuffixLength(const t_StrRef& x) const { SIZE_T i=1; SIZE_T len = rt::min(GetLength(), x.GetLength()); for(;i<len && _SC::_p[_SC::_len-i] == x[x._len-i];i++){}; return i-1; }
	t_StrRef	SubStrTail(SIZE_T len) const { return len > GetLength() ? *this : t_StrRef(_SC::_p+GetLength()-len, len); }
	t_StrRef	SubStrHead(SIZE_T len) const { return t_StrRef(_SC::_p,rt::min(len,GetLength())); }
	t_StrRef	SubStr(SIZE_T start, SIZE_T len) const { return start < GetLength() ? t_StrRef(_SC::_p+start,rt::min(len,GetLength()-start)) : nullptr; }
	t_StrRef	SubStr(SIZE_T start) const { return start < GetLength() ? t_StrRef(_SC::_p+start, GetLength()-start) : nullptr; }
	bool		StartsWith(const t_StrRef& prefix) const
				{	return	(GetLength() >= prefix.GetLength()) &&
							SubStr(0,prefix.GetLength()) == prefix;
				}
	bool		EndsWith(const t_StrRef& suffix) const
				{	return	(GetLength() >= suffix.GetLength()) &&
							SubStr(GetLength() - suffix.GetLength(),suffix.GetLength()) == suffix;
				}
	SSIZE_T		FindCharacter(char ch, SIZE_T start_offset = 0) const
				{	for(;start_offset<GetLength();start_offset++)
						if(_SC::_p[start_offset] == ch)return start_offset;
					return -1;
				}
	SSIZE_T		FindCharacter(const CharacterSet& seps, SIZE_T start_offset = 0) const
				{	for(;start_offset<GetLength();start_offset++)
						if(seps.Has(_SC::_p[start_offset]))return start_offset;
					return -1;
				}
	SSIZE_T		FindCharacterExcluded(const CharacterSet& seps_exclude, SIZE_T start_offset = 0) const
				{	for(;start_offset<GetLength();start_offset++)
						if(!seps_exclude.Has(_SC::_p[start_offset]))return start_offset;
					return -1;
				}
	SSIZE_T		FindCharacterReverse(char ch, SIZE_T start_offset = 0) const
				{	SIZE_T l=GetLength(), i=l-1;
					for(;l>start_offset;l--,i--)
						if(_SC::_p[i] == ch)return i;
					return -1;
				}
	template<typename T>
	SSIZE_T		FindString(const T& x_in, SIZE_T start_offset = 0) const
				{	t_StrRef x(x_in);
					if(x.GetLength())
					{	char ch = x[0];	SSIZE_T i = start_offset;
						while((i = FindCharacter(ch,i)) >=0)
						{	if(x.GetLength() > GetLength() - i)return -1;
							if(memcmp(x.Begin(),_SC::_p + i,x.GetLength()*sizeof(char)) == 0)
								return i;
							else
								i++;
						}
						return -1;
					}
					else return -1;
				}
	template<typename T>
	SSIZE_T		FindToken(const T& x_in, const CharacterSet& sep, SIZE_T start_offset = 0) const
				{	t_StrRef x(x_in);
					for(SSIZE_T ret = -1; (ret = FindString(x, start_offset)) >= 0; start_offset = ret + 1)
						if(	(ret == 0 || sep.Has(_SC::_p[ret-1])) && (ret + x.GetLength() == GetLength() || sep.Has(_SC::_p[ret + x.GetLength()])) )
							return ret;
					return -1;
				}
	t_StrRef	MakeUpper()
				{	for(SIZE_T i=0;i<GetLength();i++)
						if(_SC::_p[i] >='a' && _SC::_p[i] <='z') _SC::_p[i] -= ('a' - 'A');
					return *this;
				}
	t_StrRef	MakeLower()
				{	for(SIZE_T i=0;i<GetLength();i++)
						if(_SC::_p[i] >='A' && _SC::_p[i] <='Z') _SC::_p[i] += ('a' - 'A');
					return *this;
				}
	int			CaseInsensitiveCompare(const t_StrRef& in) const
				{	SIZE_T len = rt::min(GetLength(), in.GetLength());
					for(UINT i=0; i<len; i++)
					{	int x = _SC::_p[i];		if(x>='A' && x<='Z')x+=('a' - 'A');
						int y = in[i];			if(y>='A' && y<='Z')y+=('a' - 'A');
						if(x<y)return -1;
						if(x>y)return 1;
					}
					if(in.GetLength() > len)return -1;
					if(GetLength() > len)return 1;
					return 0;
				}
	bool		CaseInsensitiveEqual(const t_StrRef& in) const
				{	if(GetLength() != in.GetLength())return false;
					for(UINT i=0; i<GetLength(); i++)
					{	int x = _SC::_p[i];		if(x>='A' && x<='Z')x+=('a' - 'A');
						int y = in[i];			if(y>='A' && y<='Z')y+=('a' - 'A');
						if(x != y)return false;
					}
					return true;
				}
	/**
	 * @brief replace all a with b in the current string
	 * 
	 * @param a 
	 * @param b 
	 * @return t_StrRef 
	 */
	t_StrRef	Replace(char a, char b) 
				{	for(SIZE_T i=0; i<GetLength(); ++i)
						if(_SC::_p[i] == a)_SC::_p[i] = b;
					return *this;
				}
	/**
	 * @brief replace all a with b in the current string
	 * 
	 * @param seps 
	 * @param b 
	 * @return t_StrRef 
	 */
	t_StrRef	Replace(const CharacterSet& seps, char b) 
				{	for(SIZE_T i=0; i<GetLength(); ++i)
						if(seps.Has(_SC::_p[i]))_SC::_p[i] = b;
					return *this;
				}
	bool		HasNonPrintableAscii() const
				{	for(SIZE_T i=0;i<GetLength();i++)
						if(_SC::_p[i] < ' ' || _SC::_p[i] > '~')return true;
					return false;
				}
	bool		HasOnlyNumbers() const
				{	for(SIZE_T i=0;i<GetLength();i++)
						if(_SC::_p[i] < '0' || _SC::_p[i] > '9')return false;
					return true;
				}
	bool		HasOnlyCharacters(const CharacterSet& set) const
				{	for(SIZE_T i=0;i<GetLength();i++)
						if(!set.Has(_SC::_p[i]))return false;
					return true;
				}
	/**
	 * @brief illegal character for Windows Filename
	 * 
	 * @param with 
	 */
	void		ReplaceIllegalFilenameCharacters(CHAR with = '_') 
				{	static const CharacterSet illegal(t_StrRef("\\/:*?\"><|", 9));
					for(SIZE_T i=0;i<GetLength();i++)
						if(illegal.Has(_SC::_p[i]))_SC::_p[i] = with;
				}
	/**
	 * @brief control character like '\r' '\n' '\t'
	 * 
	 * @param with 
	 */
	void		ReplaceControlCharacters(CHAR with = '_') 
				{	for(SIZE_T i=0;i<GetLength();i++)
						if((_SC::_p[i] > 0 && _SC::_p[i] < ' ') || _SC::_p[i] == '\xff')_SC::_p[i] = with;
				}
	/**
	 * @brief replace '\\' with '/'
	 * 
	 * @param with 
	 */
	void		NormalizePathSeparator(CHAR with = '_') 
				{	for(SIZE_T i=0;i<GetLength();i++)
						if(_SC::_p[i] == '\\' || _SC::_p[i] == '/')_SC::_p[i] = with;
				}
	/**
	 * @brief remove if last character is '\\' or '/'
	 * 
	 * @return t_StrRef 
	 */
	t_StrRef	TrimTrailingPathSeparator() const 
				{	if(!_SC::IsEmpty() && (Last() == '\\' || Last() == '/'))return t_StrRef(_SC::_p, GetLength()-1);
					return *this;
				}
	t_StrRef	RemoveCharacters(const rt::CharacterSet& s)
				{	SIZE_T open = 0;
					LPCSTR p = Begin();	LPCSTR end = End();
					for(;p<end;p++)
						if(!s.Has(*p))_SC::_p[open++] = *p;
					_SC::_len = open;
					return *this;
				}
	t_StrRef	Fill(CHAR c = 0){ memset(_SC::_p, c, GetLength()); return *this; }
	bool		operator == (const char* in) const { return *this == t_StrRef(in); }
	bool		operator == (const t_StrRef& in) const
				{	if(_SC::IsEmpty() && in.IsEmpty())return true;
					return GetLength() == in.GetLength() && (memcmp(_SC::_p,in.Begin(),GetLength()*sizeof(char))==0);
				}
	bool		operator != (const char* in) const { return !(*this == in); }
	bool		operator != (const t_StrRef& in) const { return !(*this == in); }
	/**
	 * @brief  replace all a with b in the current string. a and b should have the same length
	 * 
	 * @param a 
	 * @param b 
	 * @return t_StrRef 
	 */
	t_StrRef	Replace(const t_StrRef& a, const t_StrRef& b) 
				{	SIZE_T len = a.GetLength();
					ASSERT(len == b.GetLength());
					if (len == 0) return *this;
					for (SIZE_T i = 0; i < GetLength() - len; i++)
					{	SIZE_T j = 0;
						for (j = 0; j < len && _SC::_p[i + j] == a[j]; j++);
						if (j == len)
						{
							for (j = 0; j < len; j++)
							{
								_SC::_p[i + j] = b[j];
							}
							i += len - 1;
					}	}   
					return *this; 
				}
	/**
	 * @brief handles 0,1,T,F,t,f,true,false,TRUE,FALSE
	 * 
	 * @param x 
	 * @return int 
	 */
	int			ToNumber(bool& x) const 
				{	if(_SC::IsEmpty())return 0;
					if(_SC::_p[0] == '1'){ x = true; return 1; }
					if(_SC::_p[0] == '0'){ x = false; return 1; }
					if(_SC::_p[0] == 't'){ x = true; return (0x65757274 == *(DWORD*)_SC::_p)?4:1; }
					if(_SC::_p[0] == 'f'){ x = false; return (0x65736c61 == *(DWORD*)(_SC::_p+1))?5:1; }
					if(_SC::_p[0] == 'T'){ x = true; return (0x45555254 == *(DWORD*)_SC::_p)?4:1; }
					if(_SC::_p[0] == 'F'){ x = false; return (0x45534c41 == *(DWORD*)(_SC::_p+1))?5:1; }
					return 0;
				}
	template<typename T>
	int			ToNumber(T& x) const {	return ToNumber<T,10,true,'.',','>(x); }
	template<typename T, int BASE>
	int			ToNumber(T& x) const {	return ToNumber<T,BASE,true,'.',','>(x); }
	/**
	 * @brief [...][+/-/ ]12.34, return the offset where parsing stopped, return -1 if no number found
	 * 
	 * @param x 
	 * @return int 
	 */
    template<typename T, int BASE, bool ALLOW_LEADING_NON_NUMERIC, char DECIMAL_POINT, char DIGIT_GROUP_SEPARATOR, bool NO_GROUP_SEPARATOR = false>
	int			ToNumber(T& x) const  
				{	if constexpr (std::is_enum<T>::value)
					{
						auto& ix = *(typename std::underlying_type<T>::type*)&x;
						return ToNumber(ix);
					}
					else 
					{	x = (T)0;
						char *s, *d, *end = _SC::_p + GetLength();
						bool neg = false;
						if(_SC::_p == end) return -1; // string is empty

						// find the first digit
						for (d = _SC::_p; _details::_to_num<BASE>::call(*d)>=BASE && d<end; d++){};
						if (d == end) return -1; // no digit found

						// (if is float) look for possible decimal point before the first digit
						if(rt::NumericTraits<T>::IsFloat)
						{
							if ((d-_SC::_p)>=1 && *(d-1)==(char)DECIMAL_POINT) --d; // set 'd' to decimal point so that x will be 0 and fragment parse will start at this point
						}
						s = d;

						// (if is signed) look for possible signs (+/-)
						if(rt::NumericTraits<T>::IsSigned || rt::NumericTraits<T>::IsFloat)
						{
							if ((s-_SC::_p)>=1 && (*(s-1)==(char)'+' || *(s-1)==(char)'-'))
							{
								if (*(--s)==(char)'-') neg = true;
							}
						}
						else if (!rt::NumericTraits<T>::IsSigned && (s - _SC::_p) >= 1 && (*(s-1) == (char)'-')) return -1;
						// check if there is leading non-numeric
						if(!ALLOW_LEADING_NON_NUMERIC)
						{
							if (s != _SC::_p) return -1; // number doesn't start at position 0
						}

						// parse integral 'x'
						UINT val = 0;
						while(((*d==DIGIT_GROUP_SEPARATOR && !NO_GROUP_SEPARATOR) || (val = _details::_to_num<BASE>::call(*d))<BASE) && d<end)
							if(*d++!=DIGIT_GROUP_SEPARATOR || NO_GROUP_SEPARATOR)
							{	
								if((x||val) && (rt::TypeTraits<T>::MaxVal() / BASE < x))
								{
									return -1; // detect 'x' overflow
								}
								auto x_new = (T)(x*BASE + val);
								if((x || val) && x_new <= x)
								{
									if(!(neg && x_new == rt::TypeTraits<T>::MinVal())) // could be min value
									return -1;
								}
								x = x_new;
							}

						// (if is float) parse fragment
						if(rt::NumericTraits<T>::IsFloat)
						{
							if(*d == (char)DECIMAL_POINT && d<end)
							{	d++;
								double frag = 0, div = 1;
								while(((*d==DIGIT_GROUP_SEPARATOR && !NO_GROUP_SEPARATOR) || (val = _details::_to_num<BASE>::call(*d))<BASE) && d<end)
								{
									if (*d++!=DIGIT_GROUP_SEPARATOR || NO_GROUP_SEPARATOR)
									{
										div /= BASE;
										frag += div * val;
									}
								}
								x = (T)(x + frag);
							}
							// parse scientific
							if(*d == 'e' || *d == 'E')
							{	d++; int index;
								d += t_StrRef(d,End()).ToNumber(index);
								if(index)x *= _details::_pow((T)10,index);
							}
						}

						// apply sign
						if(rt::NumericTraits<T>::IsSigned || rt::NumericTraits<T>::IsFloat)
						{
						#pragma warning(disable:4146)
							if(neg)x = -x; 
						#pragma warning(default:4146)
						}
						return (int)(d - _SC::_p);
					}
				}
	template<typename T>
	T			ToNumber() const { T ret = (T)0; ToNumber<T>(ret); return ret; }
private:
	void		GetNextToken(const CharacterSet& token_charset, rt::String& token, rt::String& non_token) const { ASSERT(0); } // not supported
	void		GetNextToken(const CharacterSet& token_charset, rt::String& token) const { ASSERT(0); } // not supported
	void		GetNextLine(rt::String& x, bool skip_empty_line = true) const { ASSERT(0); } // not supported
public:
	bool		GetNextLineWithQuote(t_StrRef& x, bool skip_empty_line = true, char QUOTE = '"')
				{	int quote_co = 0;
					t_StrRef seg = x;
					if(GetNextLine(seg))
					{
						LPCSTR begin = seg.Begin();
						LPCSTR end;

						do
						{	end = seg.End();
							for(SIZE_T i=0; i<seg.GetLength(); i++)
								if(seg[i] == QUOTE)quote_co++;

							if(0 == (quote_co&1))break;
						}while(GetNextLine(seg));

						x = t_StrRef(begin, end);
						return true;
					}
					return false;
				}
	/**
	 * @brief Get the Next Line object
	 * 
	 * empty line will be skipped
	 * @param x 
	 * @param skip_empty_line 
	 * @return true 
	 * @return false 
	 */
	bool		GetNextLine(t_StrRef& x, bool skip_empty_line = true) const 
				{	LPCSTR start = _SC::_p;		const char* tail = End();
					if(x.End() >= _SC::_p && x.End() <= tail)start = (char*)x.End();
					LPCSTR end;
					if(skip_empty_line)
					{	while(start<tail && (*start==0xd || *start==0xa))start++;
						end = start+1;
					}
					else if(start<tail && (*start==0xd || *start==0xa))
					{	start++;
						if(start<tail && start[-1]==0xd && *start==0xa)start++;
						end = start;
					}
					else
					{	end = start+1;
					}
					if(start>=tail)return false;
		
					while(end<tail && *end!=0xa && *end!=0xd)end++;
					x = t_StrRef(start,end);
					return true;
				}
	bool		GetNextToken(t_StrRef& x, const CharacterSet& sep) const
				{	LPCSTR start = _SC::_p;		const char* tail = End();
					if(x.End() >= _SC::_p && x.End() <= tail)start = (char*)x.End();
					LPCSTR end;
					while(start<tail && sep.Has(*start))start++;
					if(start>=tail)return false;
					end = start+1;
					while(end<tail && !sep.Has(*end))end++;
					x = t_StrRef(start,end);
					return true;
				}
	bool		GetNextToken(const CharacterSet& token_charset, t_StrRef& token, t_StrRef& non_token) const
				{	
					LPCSTR start = _SC::_p;		LPCSTR tail = End();
					if(non_token.End() >= (LPCSTR)_SC::_p && non_token.End() <= tail){ start = non_token.End(); }
					else if(token.End() >= (LPCSTR)_SC::_p && token.End() <= tail){ start = token.End(); }
					if(start>=tail)return false;

					LPCSTR nontoken_start = start;			
					while(token_charset.Has(*nontoken_start))
					{	
						if(nontoken_start<tail){ nontoken_start++; }
						else{ token = t_StrRef(start, tail); non_token = t_StrRef(); return start < tail; }
					}
					token = t_StrRef(start, nontoken_start);

					LPCSTR nontoken_end = nontoken_start+1;
					while(!token_charset.Has(*nontoken_end))
					{	if(nontoken_end<tail){ nontoken_end++; }
						else{ non_token = t_StrRef(nontoken_start, tail); return true; }
					}
					non_token = t_StrRef(nontoken_start, nontoken_end);
					return true;
				}
	UINT		GetTokens(const CharacterSet& token_charset, t_StrRef* token, UINT token_count) const
				{	t_StrRef v;	UINT co = 0;
					while(GetNextToken(token_charset, v))
					{	token[co] = v;
						co++;
						if(co == token_count)return co;
					}
					return co;
				}
	bool		GetNextToken(const CharacterSet& token_charset, t_StrRef& token) const
				{	
					LPCSTR start = _SC::_p;
					LPCSTR tail = End();
					if(token.End() >= (LPCSTR)_SC::_p && token.End() <= tail){ start = token.End(); }
					if(start>=tail)return false;

					while(!token_charset.Has(*start))
					{	if(start<tail){	start++; }
						else return false;
					}
					LPCSTR token_end = start+1;
					while(token_charset.Has(*token_end) && token_end<tail)
						token_end++;

					token = t_StrRef(start, token_end);
					return !token.IsEmpty();
				}
	/**
	 * @brief return count of field actually parsed
	 * 
	 * @tparam merge_adjecent_sep 
	 * @tparam quote1 
	 * @tparam quote2 
	 * @tparam T 
	 * @param fields 
	 * @param fields_count 
	 * @param seps 
	 * @param def_val 
	 * @return UINT 
	 */
	template<bool merge_adjecent_sep, char quote1, char quote2, typename T>
	UINT		SplitNumbers(T* fields, UINT fields_count, const CharacterSet& seps, T def_val = 0) const 
				{	t_StrRef* seg = (t_StrRef*)_alloca(sizeof(t_StrRef)*fields_count);
					UINT co = Split<merge_adjecent_sep, quote1, quote2>(seg, fields_count, seps);
					for(UINT i=0; i<co; i++)
						if(seg[i].ToNumber(fields[i]) == 0)fields[i] = def_val;
					for(UINT i=co; i<fields_count; i++)fields[i] = def_val;
					return co;
				}
	/**
	 * @brief return count of field actually parsed
	 * 
	 * @tparam merge_adjecent_sep 
	 * @tparam quote1 
	 * @tparam quote2 
	 * @tparam T 
	 * @param fields 
	 * @param fields_count 
	 * @param seps 
	 * @return UINT 
	 */
	template<bool merge_adjecent_sep, char quote1, char quote2, typename T>
	UINT		Split(T* fields, UINT fields_count, const CharacterSet& seps)	const 
				{	if(_SC::IsEmpty())return 0;
					UINT i=0;	const char* start = _SC::_p;	const char* tail = End();
					const char* p = start;
					int quote_cur = 0;
					for(;;)
					{	
						if(p<tail)
						{
							if(quote_cur)
							{	if(quote_cur == *p && p>start && p[-1] != '\\')
								{	quote_cur = 0;
								}
								p++;
								continue;
							}
							else
							{	if(*p == quote1 || quote2 == *p)
								{	quote_cur = *p;
									p++;
									continue;
								}
								else if(!seps.Has(*p))
								{	p++;
									continue;
								}
							}
						}

						t_StrRef v(start,p);
						if(v.GetLength()>=2 && v[0] == v.Last() && (v[0] == quote1 || v[0] == quote2))
							v = v.SubStr(1,v.GetLength()-2);
						fields[i++] = v;
						if(i>=fields_count || p==tail)
						{
							for(UINT j=i+1;j<fields_count;j++)
								fields[j].Empty();
							return i;
						}
						p++;
						if(merge_adjecent_sep)
							while(seps.Has(*p) && p<tail)p++;
						start = p;
					}
				}
	/**
	 * @brief return count of field actually parsed
	 * 
	 * @tparam merge_adjecent_sep 
	 * @tparam T 
	 * @param fields 
	 * @param fields_count 
	 * @param seps 
	 * @return UINT 
	 */
	template<bool merge_adjecent_sep, typename T>
	UINT		Split(T* fields, UINT fields_count, const CharacterSet& seps)	const
				{	return Split<merge_adjecent_sep, '"', '\'', T>(fields, fields_count, seps);
				}
	/**
	 * @brief return count of field actually parsed
	 * 
	 * @tparam merge_adjecent_sep 
	 * @tparam T 
	 * @param fields 
	 * @param fields_count 
	 * @param seps 
	 * @param def_val 
	 * @return UINT 
	 */
	template<bool merge_adjecent_sep, typename T>
	UINT		SplitNumbers(T* fields, UINT fields_count, const CharacterSet& seps, T def_val = 0) const 
				{	return SplitNumbers<merge_adjecent_sep, '"', '\'', T>(fields, fields_count, seps);
				}
	/**
	 * @brief return count of field actually parsed
	 * 
	 * @tparam T 
	 * @param fields 
	 * @param fields_count 
	 * @param seps 
	 * @return UINT 
	 */
	template<typename T>
	UINT		Split(T* fields, UINT fields_count, const CharacterSet& seps)	const 
				{	return Split<false, '"', '\'', T>(fields, fields_count, seps);
				}
	/**
	 * @brief return count of field actually parsed
	 * 
	 * @tparam T 
	 * @param fields 
	 * @param fields_count 
	 * @param seps 
	 * @param def_val 
	 * @return UINT 
	 */
	template<typename T>
	UINT		SplitNumbers(T* fields, UINT fields_count, const CharacterSet& seps, T def_val = 0) const 
				{	return SplitNumbers<false, '"', '\'', T>(fields, fields_count, seps);
				}
	t_StrRef	UnescapeCharacters(char escape_sign = '\\')
				{	LPCSTR s = Begin();	LPCSTR end = End();
					LPSTR p = Begin();
					for(; s<end-1; s++)
					{	if(*s == escape_sign){ *p++ = s[1]; s++; }
						else{ *p++ = *s; }
					}
					if(*s != escape_sign)*p++ = *s;
					_SC::_len = (SIZE_T)(p-_SC::_p);
					return *this;
				}
	t_StrRef	UnescapeCharacters(const CharacterSet& unescape, char escape_sign = '\\')
				{	LPCSTR s = Begin();	LPCSTR end = End();
					LPSTR p = Begin();
					for(; s<end-1; s++)
					{	if(*s == escape_sign){ *p++ = unescape.Mapped(s[1]); s++; }
						else{ *p++ = *s; }
					}
					if(*s != escape_sign)*p++ = *s;
					_SC::_len = (SIZE_T)(p-_SC::_p);
					return *this;
				}
	t_StrRef	TrimQuotes() const
				{	if(GetLength()>1 && First() == Last() && (First() == '"' || First() == '\''))
						return t_StrRef(Begin()+1, GetLength()-2);
					return *this;
				}
	t_StrRef	TrimExtName() const
				{	SSIZE_T i = (SSIZE_T)GetLength();
					for(;i>=0;i--)
					{	if(_SC::_p[i] == (char)'.')goto FIND_EXT;
						if(_SC::_p[i] == (char)'\\' || _SC::_p[i] == (char)'/')return *this;
					}
					return *this;
				FIND_EXT:
					return SubStr(0,i);
				}
	t_StrRef	TrimTrailingIncompleteUTF8Character() const // assuming the original string is a valid UTF8 string, but just trimmed in the middle
				{	if(!_SC::IsEmpty())
					{	auto* end = End();
						for(auto* p = &Last(); p>_SC::_p; p--)
						{	int c = *(BYTE*)p;
							if((c&0x80) == 0)return t_StrRef(_SC::_p, p+1);						// 0xxxxxxx ASCII 
							if((c&0xc0) == 0x80)continue;										// 10xxxxxx UTF8 data 
							if((c&0xf0) == 0xe0 && p + 3 <= end)return t_StrRef(_SC::_p, p+3);	// 1110xxxx, with 2 byte data
							if((c&0xe0) == 0xc0 && p + 2 <= end)return t_StrRef(_SC::_p, p+2);	// 110xxxxx, with 1 byte data
							if((c&0xf8) == 0xf0 && p + 4 <= end)return t_StrRef(_SC::_p, p+4);	// 11110xxx, with 3 byte data
					}	}
					return nullptr;
				}
	t_StrRef	TrimLeadingIncompleteUTF8Character() const // assuming the original string is a valid UTF8 string, but just trimmed in the middle
				{	auto* end = End();
					auto* p = _SC::_p;
					while(p<end)
					{	int c = *(BYTE*)p;
						if((c&0x80) == 0 || (c&0xc0) != 0x80)break; // ASCII 0xxxxxxx, or UTF head (anything other than 10xxxxxx)
						p++;
					}
					return t_StrRef(p, end);
				}
	/**
	 * @brief return ".xxx"
	 * 
	 * @return t_StrRef 
	 */
	t_StrRef	GetExtName() const 
				{	SSIZE_T i=GetLength()-1;
					for(;i>=0;i--)
					{	if(_SC::_p[i] == '.')return t_StrRef(_SC::_p+i, End());
						if(_SC::_p[i] == '\\' || _SC::_p[i] == '/')return t_StrRef();
					}
					return t_StrRef();
				}
	/**
	 * @brief return "aaa.bbb"	 
	 * 
	 * @return t_StrRef 
	 */
	t_StrRef	GetFileName() const 
				{	SSIZE_T i=GetLength()-1;
					for(;i>=0;i--)
					{	if(_SC::_p[i] == '\\' || _SC::_p[i] == '/')return t_StrRef(_SC::_p+i+1,End());
					}
					return *this;
				}
	t_StrRef	GetFilePath() const
				{	SSIZE_T i=GetLength()-1;
					for(;i>=0;i--)
					{	if(_SC::_p[i] == '\\' || _SC::_p[i] == '/')return t_StrRef(Begin(), _SC::_p+i);
					}
					return ".";
				}
	/**
	 * @brief inplace precent-decoding
	 * 
	 * @return t_StrRef 
	 */
	t_StrRef	DecodedURL()	
				{	SIZE_T c = 0;
					for(SIZE_T i=0; i<GetLength(); i++)
					{	if(_SC::_p[i] != '%')
						{	_SC::_p[c++] = _SC::_p[i];
						}
						else
						{	_SC::_p[c++] =	((_SC::_p[i+1]>='A'?(_SC::_p[i+1] - 'A' + 10):(_SC::_p[i+1] - '0')) << 4 ) |
											((_SC::_p[i+2]>='A'?(_SC::_p[i+2] - 'A' + 10):(_SC::_p[i+2] - '0')) );
							i += 2;
						}
					}
					_SC::_len = c;
					return *this;
				}
	/**
	 * @brief return "aaa.bbb"
	 * 
	 * @return t_StrRef 
	 */
	t_StrRef	GetFilenameURL() const 
				{	t_StrRef fn = GetFileName();
					for(SIZE_T i=0;i<fn.GetLength();i++)
						if(fn[i] == '?' || fn[i] == '#')
							return t_StrRef(fn.Begin(), &fn[i]).GetFileName();
					return GetFileName();
				}
	void		SplitURL(t_StrRef& protocol, t_StrRef& host, t_StrRef& path) const
				{	int s = (int)FindCharacter(':');
					if(s<0)
					{	protocol.Empty(); 
						host.Empty();
						path = *this;
					}
					///< url without authority like mailto:examle@test.com
					else if(((int)GetLength()) < s+4 || _SC::_p[s+1] != '/' || _SC::_p[s+2] != '/') 
					{
						protocol = t_StrRef(_SC::_p, &_SC::_p[s]);
						host.Empty();
						path = t_StrRef(&_SC::_p[s + 1], End());
					}
					else
					{	protocol = t_StrRef(_SC::_p, &_SC::_p[s]);
						s+=3;
						int h = (int)FindCharacter('/', s);
						if(h>=s)
						{	host = t_StrRef(&_SC::_p[s], &_SC::_p[h]);
							path = t_StrRef(&_SC::_p[h], End());
						}
						else
						{	host = t_StrRef(&_SC::_p[s], End());
							path = t_StrRef("/",1);
						}
					}
				}
	void		SplitURL(t_StrRef& protocal, t_StrRef& host, t_StrRef& file_path, t_StrRef& cgi_param) const
				{	SplitURL(protocal, host, file_path);
					int off = (int)file_path.FindCharacter('?');
					if(off>=0)
					{	cgi_param = file_path.TrimLeft(off+1);
						file_path.SetLength(off);
					}
					else cgi_param.Empty();
				}
	t_StrRef	GetUrlParam(const t_StrRef& tag, const t_StrRef& def_val = nullptr) const
				{	auto off = FindCharacter('?');
					while(off<(SSIZE_T)_SC::_len-1)
					{
						off++;
						if(memcmp(&_SC::_p[off], tag.Begin(), tag.GetLength()) == 0 && _SC::_p[off + tag.GetLength()] == '=')
						{
							auto end = FindCharacter('&', off);
							return t_StrRef(&_SC::_p[off + tag.GetLength() + 1], end>0?&_SC::_p[end]:End());
						}
						else
						{	off = FindCharacter('&', off);
							if(off<0)return def_val;
						}
					}
					return def_val;
				}
	t_StrRef	ResolveRelativePath()
				{
					t_StrRef d[256];
				#ifdef PLATFORM_WIN
					UINT co = Split<true>(d, 256, "/\\");
				#else
					UINT co = Split<true>(d, 256, '/');
				#endif
					UINT open = 0;
					for(UINT q=0;q<co;q++)
					{
						//if(d[i].IsEmpty())continue;
						if(d[q].GetLength() == 1 && d[q][0] == '.')continue;
						if(d[q].GetLength() == 2 && d[q][0] == '.' && d[q][0] == '.'){ if(open)open--; continue; }
						d[open++] = d[q];
					}
					LPSTR p = _SC::_p;		UINT i = 0;
					while(p == d[i].Begin() && i<open)
					{	p += d[i].GetLength()+1;
						i++;
					}
					while(i<open)
					{	memcpy(p, d[i].Begin(), d[i].GetLength());
						p += d[i].GetLength()+1;
						if(i<open-1)p[-1] = '/';
						i++;
					}
					_SC::_len = ((SIZE_T)(p-_SC::_p)) - 1;
					return *this;
				}
	/**
	 * @brief separator will also be trimmed
	 * 
	 * @param seps 
	 * @return t_StrRef 
	 */
	t_StrRef	TrimBefore(const CharacterSet& seps) const 
				{	SIZE_T pos = 0;
					for(;pos<_SC::_len;pos++)
						if(seps.Has(_SC::_p[pos]))return t_StrRef(&_SC::_p[pos+1], End());
					return *this;
				}
	/**
	 * @brief separator will also be trimmed
	 * 
	 * @param seps 
	 * @return t_StrRef 
	 */
	t_StrRef	TrimAfter(const CharacterSet& seps) const 
				{	SIZE_T pos = 0;
					for(;pos<_SC::_len;pos++)
						if(seps.Has(_SC::_p[pos]))return t_StrRef(Begin(), &_SC::_p[pos]);
					return *this;
				}
	/**
	 * @brief separator will also be trimmed
	 * 
	 * @param seps 
	 * @return t_StrRef 
	 */
	t_StrRef	TrimBeforeReverse(const CharacterSet& seps) const 
				{	SSIZE_T pos = GetLength()-1;
					for(;pos>=0;pos--)
						if(seps.Has(_SC::_p[pos]))return t_StrRef(&_SC::_p[pos+1], End());
					return *this;
				}
	/**
	 * @brief separator will also be trimmed
	 * 
	 * @param seps 
	 * @return t_StrRef 
	 */
	t_StrRef	TrimAfterReverse(const CharacterSet& seps) const 
				{	SSIZE_T pos = GetLength()-1;
					for(;pos>=0;pos--)
						if(seps.Has(_SC::_p[pos]))return t_StrRef(Begin(), &_SC::_p[pos]);
					return *this;
				}
	/**
	 * @brief Get the Directory Name object
	 * 
	 * include the terminate '/'
	 * @return t_StrRef 
	 */
	t_StrRef	GetDirectoryName() const 
				{	
					SSIZE_T i=GetLength()-1;
					for(;i>=0;i--)
					{	if(_SC::_p[i] == '\\' || _SC::_p[i] == '/')return t_StrRef(_SC::_p,&_SC::_p[i+1]);
					}
					return t_StrRef("./",2);
				}
	t_StrRef	TrimLeft(SIZE_T length) const 
				{	if(length >= GetLength())return t_StrRef();
					return t_StrRef(_SC::_p+length, GetLength()-length);
				}
	t_StrRef	TrimRight(SIZE_T length) const
				{	if(length >= GetLength())return t_StrRef();
					return t_StrRef(_SC::_p, GetLength()-length);
				}
	t_StrRef	TrimLeftSpace() const 
				{	if(_SC::IsEmpty())return *this;
					char* p=_SC::_p, *end = _SC::_p+GetLength(); for(;p<end && *p<=0x20 && *p>=0;p++){}; return t_StrRef(p,end);
				}
	t_StrRef	TrimRightSpace() const
				{	if(_SC::IsEmpty())return *this;
					SIZE_T l = GetLength(); for(;l>1 && _SC::_p[l-1]<=0x20 && _SC::_p[l-1]>=0;l--){}; return t_StrRef(_SC::_p,l);
				}
	t_StrRef	TrimSpace() const 
				{	if(_SC::IsEmpty())return *this;
					return TrimLeftSpace().TrimRightSpace(); 
				}
	t_StrRef	RegularizeUTF8()
				{	LPSTR p = _SC::_p;
					for(SIZE_T i=0;i<GetLength();i++)
					{	int c = ((LPCBYTE)_SC::_p)[i];
						if((c&0x80) == 0){ *p++ = c; continue; }
						if((c&0xe0) == 0xc0){ *p++ = c; *p++ = 0x80 | (0x3f&_SC::_p[++i]); continue; }
						if((c&0xf0) == 0xe0){ *p++ = c; *p++ = 0x80 | (0x3f&_SC::_p[++i]); *p++ = 0x80 | (0x3f&_SC::_p[++i]); continue; }
					}
					_SC::_len = p - _SC::_p;
					return *this;
				}
	/**
	 * @brief count # of char included in the set
	 * 
	 * @param set 
	 * @return SIZE_T 
	 */
	SIZE_T		Occurrence(const rt::CharacterSet& set) const 
				{	SIZE_T c = 0;
					for(SIZE_T i=0;i<GetLength();i++)
						if(set.Has(_SC::_p[i]))c++;
					return c;
				}
	/**
	 * @brief count # of char excluded in the set
	 * 
	 * @param set 
	 * @return SIZE_T 
	 */
	SIZE_T		OccurrenceExcluded(const rt::CharacterSet& set) const
				{	SIZE_T c = 0;
					for(SIZE_T i=0;i<GetLength();i++)
						if(!set.Has(_SC::_p[i]))c++;
					return c;
				}
};
/**
 * @brief String_Ref represent a string with length, the string is not necessary zero-terminated
 * 
 */
class String_Ref: public String_Base<_details::_StringPtrStore, String_Ref> 
{	
	typedef String_Base<_details::_StringPtrStore, String_Ref> _SC;
	template<typename t_Left, typename t_Right>
	friend class _details::String_AddExpr;

	SIZE_T _ExprFill(char* p) const	///< return number of char filled
	{	if(!IsEmpty())
		{	memcpy(p,_p,GetLength()*sizeof(char));
			return GetLength();
		}
		else return 0;
	}

public:
	typedef char t_Char;
	typedef _details::hash_compare_str<String_Ref> hash_compare;

public:
    ~String_Ref(){}
	template<typename SS, typename SR>
	String_Ref(const String_Base<SS,SR>& x){ _SC::_p = (LPSTR)x._p; _SC::_len = x._len; }
	String_Ref(){ _SC::_p = nullptr; _SC::_len = 0; }
	String_Ref(const String_Ref& x){ *this = x; }
	String_Ref(const char* x){ operator = (x); }
	String_Ref(const char* p, size_t len){ _SC::_p = (char*)p; _SC::_len = len; }
	String_Ref(const char* p, const char* end)
	{	if(end){ _p = (char*)p; ASSERT(end>=p); _SC::_len = (size_t)(end-p); }
		else{ *this = p; }
	}
	template <template<class, class, class> class std_string, class _Traits, class _Alloc>
	String_Ref(const std_string<char, _Traits, _Alloc>& str)
	{	if(str.size()){	_SC::_p = (LPSTR)str.c_str(); _SC::_len = str.size(); }
		else{ _SC::_p = nullptr; _SC::_len = 0; }
	}
	const String_Ref& operator = (const char* x)
	{	if(x)
		{	_SC::_p = (char*)x;
			_SC::_len = strlen(x);
		}
		else Empty();
		return *this;
	}
	static auto&	EmptyString(){ static const rt::String_Ref _empty; return _empty; }
	bool			SetLength(SIZE_T len){ if(len<=GetLength()){ _SC::_len = len; return true; } return false; }
public:
	String_Ref&		Replace(char a, char b){ ((_SC*)this)->Replace(a,b); return *this; }
	String_Ref&		Replace(const CharacterSet& a, char b){ ((_SC*)this)->Replace(a,b); return *this; }
	template<typename T1, typename TString>
	UINT			ReplaceTo(const T1& a, const String_Ref& b, TString& replaced) const ///< replace all a with b in the current string, low performance, return # of replacement
					{	SIZE_T a_len = rt::String_Ref(a).GetLength();
						replaced = *this;
						SIZE_T s = 0;
						UINT replaced_co = 0;
						for (;;)
						{   SSIZE_T p = replaced.FindString(a, s);
							if (p < 0) break;
							replaced = replaced.SubStrHead(p) + b + replaced.SubStr(p + a_len);
							s = p + b.GetLength();
							replaced_co++;
						}
						return replaced_co;
					}
	bool			ParseNextNumber(UINT& out)	///< parsed text will be removed
					{	SIZE_T start = 0;
						for(;start < GetLength();start++)
							if(_SC::_p[start]>=(char)'0' && _SC::_p[start]<=(char)'9')goto PARSE_UINT;
						return false;
					PARSE_UINT:
						UINT ret = 0;
						for(;start < GetLength();start++)
							if(_SC::_p[start]>=(char)'0' && _SC::_p[start]<=(char)'9')
								ret = ret*10 + (_SC::_p[start] - (char)'0');
							else break;
						_SC::_p += start; _SC::_len -= start;	out = ret;
						return true;
					}
	String_Ref		GetLengthRecalculated() const
					{	if(_p)
						{	for(SIZE_T i=0;i<GetLength();i++)
								if(_p[i] == 0)
								{	return rt::String_Ref(_p, i);
								}
						}
						return *this;
					}
	String_Ref		Flip()
					{	for(SIZE_T i=0; i<GetLength()/2; i++)
							rt::Swap(_SC::_p[i], _SC::_p[GetLength() - i - 1]);
						return *this;
					}
};
template<class t_Ostream, typename t_StringStore, class t_String_Ref>
FORCEINL t_Ostream& operator << (t_Ostream& Ostream, const String_Base<t_StringStore, t_String_Ref> & vec)
{	
	if(vec.GetLength())
	{
		if(vec.IsZeroTerminated())
		{	Ostream<<vec.Begin();	}
		else
		{	for(SIZE_T i=0;i<vec.GetLength();i++)Ostream<<vec[i];	}
	}
	return Ostream;
}

} // namespace rt

namespace rt
{
/**
 * @brief to string
 * 
 */
namespace tos
{
	template<int DIMEN = 1, int LEN = (21*DIMEN + (DIMEN-1)*2) >
	class S_:public String_Ref
	{	
		template<int _DIMEN, int _LEN> friend class S_;
		template<typename t_Left, typename t_Right> friend class String_AddExpr;
	protected:
        char _string[LEN];
		S_(){ _p = _string; _len = 0; }
		template<typename T>
		static int __toS_vec(LPSTR p, const T& x)
		{	int len = 1 + S_<DIMEN-1, LEN>::__toS_vec(p, x);
			p[len-1] = ',';
			return len + S_<1, LEN>::__toS(p+len, x[DIMEN-1]);
		}
	public:
		template<typename T>
		S_(const T& x)
		{	_len = __toS_vec(_string, x);
			_p = _string;
			ASSERT(_len < LEN);
		}
		operator LPCSTR() const { return _p; }
	};
	template<int LEN>
	class S_<1, LEN>:public String_Ref
	{	template<int _DIMEN, int _LEN> friend class S_;
		template<typename t_Left, typename t_Right>	friend class String_AddExpr;
	protected:
        char _string[LEN];
		template<typename T>
		static int __toS_vec(LPSTR p, const T& x)
		{	return S_<1, LEN>::__toS(p, x[0]);
		}
	public:
		operator LPCSTR() const { return _p; }
		String_Ref&	RightAlign(UINT w, char pad = ' ')
		{	ASSERT(w < sizeofArray(_string));
			if(w > String_Ref::GetLength())
			{	memmove(&_string[w - String_Ref::GetLength()], _string, String_Ref::GetLength());
				for(SIZE_T i=0; i<w - GetLength(); i++)_string[i] = pad;
				_len = w;
				_string[w] = 0;
			}
			return *this;
		}
		String_Ref&	LeftAlign(UINT w, char pad = ' ')
		{	ASSERT(w <= sizeofArray(_string));
			if(w > GetLength())
			{	for(SIZE_T i=GetLength(); i<w; i++)_string[i] = pad;
				_len = w;
				_string[w] = 0;
			}
			return *this;
		}
		static int __toS(LPSTR p, char x){ p[0] = x; return 1; }
		static int __toS(LPSTR p, int x){ return _details::string_ops::itoa(x,p); }///< sprintf(p,"%d",x); }
		static int __toS(LPSTR p, unsigned int x){ return _details::string_ops::itoa(x,p);; } ///< sprintf(p,"%u",x); }
		static int __toS(LPSTR p, LONGLONG x){ return _details::string_ops::itoa(x,p); } ///< sprintf(p,"%lld",x); }
		static int __toS(LPSTR p, ULONGLONG x){ return _details::string_ops::itoa(x,p); } ///< sprintf(p,"%llu",x); }
#if defined(PLATFORM_WIN) || defined(PLATFORM_MAC) || defined(PLATFORM_IOS)
		static int __toS(LPSTR p, long x){ return _details::string_ops::itoa((int)x,p); }///< sprintf(p,"%d",x); }
		static int __toS(LPSTR p, unsigned long x){ return _details::string_ops::itoa((UINT)x,p);; } ///< sprintf(p,"%u",x); }
#endif
		static int __toS(LPSTR p, LPCVOID x)
		{	p[0] = (char)'0';			p[1] = (char)'x';
#if   defined(PLATFORM_64BIT)
			return 2 + sprintf(&p[2],"%016llx",(ULONGLONG)x);
#elif defined(PLATFORM_32BIT)
			return 2 + sprintf(&p[2],"%08x",(DWORD)x);
#endif
		}
		static int __toS(LPSTR p, float x, int fractional_digits = 2){ return _details::string_ops::ftoa<float>(x, p, fractional_digits); }
		static int __toS(LPSTR p, double x, int fractional_digits = 4){ return _details::string_ops::ftoa<double>(x, p, fractional_digits); }
		static int __toS(LPSTR p, bool x)
		{	if(x){ *((DWORD*)p) = 0x65757274; return 4; }
			else{ *((DWORD*)p) = 0x736c6166; p[4] = 'e'; return 5; }
		}
		S_(const S_& x){ _p = _string; _len = x._len; memcpy(_p, x._p, _len); }
		S_(){ _p = _string; _len = 0; }
		S_(LPCVOID x){ _len = __toS(_string,x); ASSERT(_len < LEN); _string[_len] = 0; _p = _string; }
		S_(float x, int fractional_digits = 2){ _len = __toS(_string,x,fractional_digits); ASSERT(_len < LEN); _string[_len] = 0; _p = _string; }
		S_(double x, int fractional_digits = 4){ _len = __toS(_string,x,fractional_digits); ASSERT(_len < LEN); _string[_len] = 0; _p = _string; }
		template<typename T>
		S_(T x)
		{	if constexpr (std::is_enum<T>::value)
			{	// as enum
				_len = __toS(_string, *(typename std::underlying_type<T>::type*)&x);
			}
			else
			{
				_len = __toS(_string, x);
			}
			ASSERT(_len < LEN); _string[_len] = 0; _p = _string;
		}
	};

} // namespace tos



//////////////////////////////////////////
// String Expression
namespace _details
{
template<typename t_Left, typename t_Right>
class String_AddExpr
{	template<typename t_Left_, typename t_Right_>
	friend class String_AddExpr;
	char*		_pString;
	SSIZE_T		_len;

public:
	typedef char t_Char;
	t_Left		_left;
	t_Right		_right;

public:
	template<typename T1, typename T2>
	String_AddExpr(T1& l, T2& r)
		:_pString(nullptr),_len(-1),_left(l),_right(r)
	{}
	~String_AddExpr(){ _SafeFree32AL(_pString); }
	const char* Begin() const { return rt::_CastToNonconst(this)->GetSafeString(); }
	const char* GetSafeString() 
	{	if(_pString == nullptr)
		{	GetLength();
			_pString = _Malloc32AL(char,_len+1);
			ASSERT(_pString);
			VERIFY(_len == (SSIZE_T)CopyTo(_pString));
			ASSERT(rt::String_Ref(_pString, _len).GetLengthRecalculated().GetLength() == (SIZE_T)_len);
			_pString[_len] = '\0';
		}
		return _pString;
	}
	const char* Begin(){ return GetSafeString(); }
	String_Ref GetRef()
	{	if(_pString == nullptr)
		{	SIZE_T len = GetLength();
			_pString = _Malloc32AL(char,len+1);
			ASSERT(_pString);
			VERIFY(len == CopyTo(_pString));
			_pString[len] = '\0';
			return String_Ref(_pString, len);
		}
		return String_Ref(_pString);
	}
	operator const char* () const { return ((String_AddExpr*)this)->GetSafeString(); }
	operator const rt::String_Ref () const { ((String_AddExpr*)this)->GetSafeString(); return rt::String_Ref(_pString,_len); }
	SIZE_T GetLength() const
	{	if(_len < 0)((String_AddExpr*)this)->_len = _left.GetLength() + _right.GetLength();
		return _len;
	}
	SIZE_T CopyTo(char* p) const ///< terminate-zero is not copied
	{	SIZE_T len = _left.CopyTo(p);
		return len + _right.CopyTo(p+len);
	}  
	template<typename t_Str>
	void	ToString(t_Str& str) const { VERIFY(str.SetLength(GetLength())); VERIFY(str.GetLength() == CopyTo(str)); }
};
template<class t_Ostream, typename t_Left, typename t_Right>
t_Ostream& operator<<(t_Ostream& Ostream, const rt::_details::String_AddExpr<t_Left,t_Right> & str_expr)
{	return Ostream<<str_expr._left<<str_expr._right;
}

} // namespace _details

template<typename t_Left, typename t_Right>
struct _SE:public rt::_details::String_AddExpr<t_Left,t_Right>
{	template<typename T1, typename T2>
	_SE(T1& l, T2& r):rt::_details::String_AddExpr<t_Left,t_Right>(l,r){}
    //~_SE(){}  // This is an unnecessary code, And even worse, it makes release build never ends in VS2010 SP1
};

#define CPF_STRING_CONNECT_OP_(t_Left, t_Right, t_Left_in, t_Right_in)						\
FORCEINL _SE<t_Left, t_Right >  operator + (const t_Left_in left, const t_Right_in right)	\
{ return _SE<t_Left, t_Right > ( (left), (right) ); }										\

#define CPF_STRING_CONNECT_OP(t_Left, t_Right, t_Left_in, t_Right_in)						\
		CPF_STRING_CONNECT_OP_(t_Right, t_Left, t_Right_in, t_Left_in)						\
		CPF_STRING_CONNECT_OP_(t_Left, t_Right, t_Left_in, t_Right_in)						\

CPF_STRING_CONNECT_OP_(String_Ref,String_Ref,	String_Ref&, String_Ref&	)
CPF_STRING_CONNECT_OP(String_Ref, String_Ref,	String_Ref&, char*			)
CPF_STRING_CONNECT_OP(String_Ref, tos::S_<>,	String_Ref&, char			)
CPF_STRING_CONNECT_OP(String_Ref, tos::S_<>,	String_Ref&, bool			)
CPF_STRING_CONNECT_OP(String_Ref, tos::S_<>,	String_Ref&, int			)
CPF_STRING_CONNECT_OP(String_Ref, tos::S_<>,	String_Ref&, unsigned int	)
#if defined(PLATFORM_WIN) || defined(PLATFORM_MAC) || defined(PLATFORM_IOS)
CPF_STRING_CONNECT_OP(String_Ref, tos::S_<>,	String_Ref&, long			)
CPF_STRING_CONNECT_OP(String_Ref, tos::S_<>,	String_Ref&, unsigned long	)
#endif
CPF_STRING_CONNECT_OP(String_Ref, tos::S_<>,	String_Ref&, LONGLONG		)
CPF_STRING_CONNECT_OP(String_Ref, tos::S_<>,	String_Ref&, ULONGLONG		)
CPF_STRING_CONNECT_OP(String_Ref, tos::S_<>,	String_Ref&, float			)
CPF_STRING_CONNECT_OP(String_Ref, tos::S_<>,	String_Ref&, double			)



#define CPF_STRING_EXPR_CONNECT_OP(type, type_in)			\
template<typename t_Left, typename t_Right> FORCEINL		\
_SE<type, _SE<t_Left,t_Right> >								\
operator + (const type_in p, const _SE<t_Left,t_Right>& x)	\
{ return _SE<type, _SE<t_Left,t_Right> >((p),x); }			\
template<typename t_Left, typename t_Right> FORCEINL		\
_SE<_SE<t_Left,t_Right> , type>								\
operator + (const _SE<t_Left,t_Right>& x, const type_in p)	\
{ return _SE<_SE<t_Left,t_Right>, type>(x, (p)); }			\


CPF_STRING_EXPR_CONNECT_OP(String_Ref,	String_Ref&		)
CPF_STRING_EXPR_CONNECT_OP(String_Ref,	char*			)
CPF_STRING_EXPR_CONNECT_OP(tos::S_<>,	char			)
CPF_STRING_EXPR_CONNECT_OP(tos::S_<>,	int				)
CPF_STRING_EXPR_CONNECT_OP(tos::S_<>,	bool			)
CPF_STRING_EXPR_CONNECT_OP(tos::S_<>,	unsigned int	)
#if defined(PLATFORM_WIN) || defined(PLATFORM_MAC)
CPF_STRING_EXPR_CONNECT_OP(tos::S_<>,	long			)
CPF_STRING_EXPR_CONNECT_OP(tos::S_<>,	unsigned long	)
#endif
CPF_STRING_EXPR_CONNECT_OP(tos::S_<>,	LONGLONG		)
CPF_STRING_EXPR_CONNECT_OP(tos::S_<>,	ULONGLONG		)
CPF_STRING_EXPR_CONNECT_OP(tos::S_<>,	float			)
CPF_STRING_EXPR_CONNECT_OP(tos::S_<>,	double			)


template<typename t_LL, typename t_LR, typename t_RL, typename t_RR > 
_SE<_SE<t_LL,t_LR>, _SE<t_RL,t_RR> >	
FORCEINL operator + (const _SE<t_LL,t_LR>& xl, const _SE<t_RL,t_RR>& xr)					
{ return _SE<_SE<t_LL,t_LR>, _SE<t_RL,t_RR> >(xl,xr); }

template<SIZE_T LEN>
class StringFixed: public String_Base<_details::_StringArrayStore<LEN+1>, String_Ref>
{	typedef String_Base<_details::_StringArrayStore<LEN+1>, String_Ref> _SC;
public:
	StringFixed(){ _SC::_len = 0; }
	template<typename T>
	StringFixed(const T& x)
	{	if(SetLength(x.GetLength()))
			VERIFY(x.CopyTo(_SC::_p) == x.GetLength());
	}
	bool SetLength(SIZE_T sz)
	{	if(sz <= LEN){ _SC::_len = sz; _SC::_p[sz] = 0; return true; }
		else return false;
	}
	const StringFixed& operator = (const char* x){ *this = String_Ref(x); return *this; }
	const StringFixed& operator = (char* x){ *this = String_Ref(x); return *this; }
	const StringFixed& operator = (const String_Ref& x)
	{	if(!x.IsEmpty())
		{	if(SetLength(x.GetLength()))	///< handle the case of x = substring of x
				memcpy(_SC::_p,x.Begin(),_SC::GetLength());
		}else{ _SC::Empty(); }
		return *this;
	}
	template<typename T>
	const StringFixed& operator = (const T& string_expr)
	{	SIZE_T len = string_expr.GetLength();
		if(SetLength(len))
			VERIFY(len == string_expr.CopyTo(_SC::_p));
		return *this;
	}
	template<typename T>
	const T& operator += (const T& string_expr)
	{	SIZE_T len = string_expr.GetLength();
		if(len + _SC::_len < LEN)
		{	VERIFY(len == string_expr.CopyTo(_SC::_p+_SC::GetLength()));
			_SC::_p[len+_SC::GetLength()] = '\0';
			_SC::_len = len + _SC::GetLength();
		}
		return string_expr;
	}
	LPCSTR operator += (LPCSTR str){ (*this) += rt::String_Ref(str); return str; }
	void operator += (char x){ SIZE_T pos = _SC::GetLength(); if(SetLength(pos+1))_SC::_p[pos] = x; }
};

class String: public String_Ref
{
protected:
	SIZE_T	_leng_reserved;
	bool	_ChangeLength(SIZE_T new_size) ///< Orignal data at front is preserved
			{	if( new_size <= _leng_reserved){ _len = new_size; return true; }
				_leng_reserved = rt::max(rt::max((SIZE_T)16,new_size),_leng_reserved*2);
				LPBYTE pNewBuffer = _Malloc32AL(BYTE,_leng_reserved + 1);
				if(pNewBuffer){}else{ return false; }
				// copy old elements
				memcpy(pNewBuffer, _p, sizeof(char)*_len);
				_SafeFree32AL(_p);
				_p = (char*)pNewBuffer;
				_len = new_size;
				return true;
			}
public:
	String(){ _leng_reserved = 0; _p = nullptr; _len = 0; }
	String(const String& x){ _leng_reserved = 0; _p = nullptr; _len = 0; *this = (String_Ref&)x; }
	String(String&& x){ rt::Copy<sizeof(String)>(this, &x); rt::Zero(x); }
	String(const String_Ref& x){ _leng_reserved = 0; _p = nullptr; _len = 0; *this = x; }
	String(const char* x){ _leng_reserved = 0; _p = nullptr; _len = 0; operator = (x); }
	String(const char* p, SIZE_T len){ _leng_reserved = 0; _p = nullptr; _len = 0; *this = String_Ref(p,len); }
	String(const char* p, const char* end){ _leng_reserved = 0; _p = nullptr; _len = 0; *this = String_Ref(p,end); }
    String(const char c, int count){ _leng_reserved = 0; _p = nullptr; _len = 0; for (int i = 0; i < count; i++) *this += c; }
	template<typename T>
	String(const T& string_expr){ _p = nullptr; _leng_reserved = _len = 0; (*this) = string_expr; }
	~String(){ _SafeFree32AL(_p); }

	String&		  operator = (String&& x){ rt::Copy(*this, x); x._p = nullptr; x._len = x._leng_reserved = 0; return *this; }
	const String& operator = (const char* x){ *this = String_Ref(x); return *this; }
	const String& operator = (char* x){ *this = String_Ref(x); return *this; }
	const String& operator = (char x){ SetLength(1); _p[0] = x; return *this; }
	const String& operator = (const String_Ref& x)
	{	if(!x.IsEmpty())
		{	SIZE_T len = x.GetLength();
			if(len > _leng_reserved)	// handle the case of x = substring of x
			{	LPSTR p = _Malloc32AL(char, len + 1);
				memcpy(p, x.Begin(), len);
				_len = _leng_reserved = len;
				rt::Swap(p, _p);
				_SafeFree32AL(p);
			}
			else{ memmove(_p, x.Begin(), _len = len); } // handle the case of x = substring of x
			_p[_len] = 0;
		}else{ Empty(); }
		return *this;
	}
	const String& operator = (const String& x){ return *this = (const String_Ref&)x; }
	template<typename T>
	const auto& operator = (const T& string_expr)
	{	SIZE_T len = string_expr.GetLength();
		if(len == 0)return *this;
		LPSTR p = _Malloc32AL(char, len+1);	// we have to reallocate always, string_expr may refer to (*this)
		VERIFY(len == string_expr.CopyTo(p));
		_leng_reserved = _len = len;
		rt::Swap(p, _p);
		_SafeFree32AL(p);
		_p[_len] = 0;
		return *this;
	}
	template<typename T>
	const auto& operator += (const T& string_expr)
	{	SIZE_T len = string_expr.GetLength();
		if(len == 0)return *this;
		if(len + GetLength() > _leng_reserved)
		{	_leng_reserved = rt::max(_leng_reserved*2, len + GetLength());
			LPSTR p = _Malloc32AL(char, _leng_reserved + 1);
			memcpy(p, _p, GetLength());
			VERIFY(len == string_expr.CopyTo(p+GetLength()));
			rt::Swap(p, _p);
			_len = len + GetLength();
			_SafeFree32AL(p);
		}
		else if(_p)
		{	VERIFY(len == string_expr.CopyTo(_p+GetLength()));
			_len = len + GetLength();
		}
		_p[_len] = 0;
		return *this;
	}
	LPCSTR operator += (LPCSTR str){ (*this) += rt::String_Ref(str); return str; }
	LPSTR operator += (LPSTR str){ (*this) += rt::String_Ref(str); return str; }
	void operator += (char x){ SIZE_T pos = GetLength(); SetLength(pos+1); _p[pos] = x; }

public:
	bool		SetLength(SIZE_T sz)
				{	if(sz == 0)
					{	if(_p && _len){ _p[0] = 0; _len = 0; }
						return true;
					}
					if(_ChangeLength(sz)){ _p[sz] = 0; return true; }
					else return false;
				}
	LPSTR		DetachBuffer(){ LPSTR p = _p; _leng_reserved = _len = 0; _p = nullptr; return p; }
	String&		Empty(){ SetLength(0); return *this; }
	String&		SecureEmpty(){ _len = 0; rt::Zero(_p, _leng_reserved); return *this; }

private:
	bool		ParseNextNumber(UINT& out){ ASSERT(0); return false; } // ParseNextNumber cannot be used on a String
public:
	operator	LPCSTR () const { ASSERT(!_p || !_p[GetLength()]); return _p; }
	operator	LPSTR () { if(_p){ ASSERT(!_p[GetLength()]); } return _p; }
	SSIZE_T		FindString(const char* pSub, SIZE_T skip_first = 0) const // return -1 if not found
				{	return (skip_first<GetLength() && (pSub=strstr(Begin()+skip_first,pSub)))?(int)(pSub-Begin()):-1;
				}
	auto&		RemoveCharacters(const rt::CharacterSet& s){ String_Ref::RemoveCharacters(s); if(!IsEmpty())_p[_len] = 0; return *this; }
	auto&		RemoveAt(SIZE_T i){ ASSERT(i<GetLength()); _len--; memmove(_p+i, _p+i+1, _len-i);  return *this; }
	auto&		RemoveAt(SIZE_T i, SIZE_T count){ ASSERT(i<GetLength() && i+count<=GetLength()); _len-=count; memmove(_p+i, _p+i+count, _len-i); return *this; }
	auto&		RecalculateLength(){ if(_p){ _len = strlen(_p); }else{ _len = 0; } return *this; }
	auto&		Replace(char a, char b){ ((String_Base<_details::_StringPtrStore, String_Ref>*)(this))->Replace(a,b); return *this; } // replace all a with b
	auto&		Replace(char a, const String_Ref& b) // replace all a with b
				{	rt::String tmp;
					tmp.SetLength(this->GetLength() * b.GetLength());
					tmp.SetLength(0);
					for (int i=0; i<(int)this->GetLength(); i++)
					{   if (_p[i] == a) tmp += b;
						else tmp += _p[i];
					}
					rt::Swap(*this, tmp);
					return *this;
				}
	template<typename T1>
	UINT		Replace(const T1& a, const String_Ref& b) ///< replace all a with b in the current string, low performance, return # of replacement
				{	SIZE_T a_len = rt::String_Ref(a).GetLength();
					if(a_len == 0)return 0;
					rt::String tmp = *this;
					SIZE_T s = 0;
					UINT replaced = 0;
					for (;;)
					{   SSIZE_T p = tmp.FindString(a, s);
						if (p < 0) break;
						tmp = tmp.SubStrHead(p) + b + tmp.SubStr(p + a_len);
						s = p + b.GetLength();
						replaced++;
					}
					rt::Swap(*this, tmp);
					return replaced;
				}
	auto&		UnescapeCharacters(char escape_sign = '\\')
				{	if(!IsEmpty())
					{	String_Ref::UnescapeCharacters(escape_sign);
						_p[_len] = 0;
					}
					return *this;
				}
	auto&		UnescapeCharacters(const rt::String_Ref& input, char escape_sign = '\\')
				{	VERIFY(SetLength(input.GetLength()));
					LPCSTR s = input.Begin();	LPCSTR end = input.End();
					LPSTR p = Begin();
					for(; s<end-1; s++)
					{	if(*s == escape_sign){ *p++ = s[1]; s++; }
						else{ *p++ = *s; }
					}
					if(*s != escape_sign)*p++ = *s;
					_len = (size_t)(p-_p);
					_p[_len] = 0;
					return *this;
				}
	auto&		UnescapeCharacters(const rt::String_Ref& input, const CharacterSet& escape, char escape_sign = '\\')
				{	VERIFY(SetLength(input.GetLength()));
					LPCSTR s = input.Begin();	LPCSTR end = input.End();
					LPSTR p = Begin();
					for(; s<end-1; s++)
					{	if(*s == escape_sign){ *p++ = escape.Mapped(s[1]); s++; }
						else{ *p++ = *s; }
					}
					if(*s != escape_sign)*p++ = *s;
					_len = (size_t)(p-_p);
					_p[_len] = 0;
					return *this;
				}
	auto&		EscapeCharacters(const rt::String_Ref& input, const CharacterSet& characters_to_be_escaped, char escape_sign = '\\')
				{	LPCSTR s = input.Begin();
					LPCSTR end = input.End();
					SIZE_T replace_count = 0;
					for(;s<end;s++)
						if(*s == escape_sign || characters_to_be_escaped.Has(*s))replace_count++;
					if(replace_count)
					{
						VERIFY(SetLength(input.GetLength()+replace_count));
						LPSTR p = Begin();
						s = input.Begin();
						for(;s<end;s++)
						{	if(*s == escape_sign || characters_to_be_escaped.Has(*s))
							{	*p++ = escape_sign;
								*p++ = characters_to_be_escaped.Mapped(*s);
							}
							else *p++ = *s;
						}
					}
					else *this = input;
					return *this;
				}
	auto&		EscapeCharacters(const CharacterSet& characters_to_be_escaped, char escape_sign = '\\')
				{	LPCSTR s = Begin();
					LPCSTR end = End();
					SIZE_T replace_count = 0;
					for(;s<end;s++)
						if(*s == escape_sign || characters_to_be_escaped.Has(*s))replace_count++;
					if(replace_count)
					{	VERIFY(SetLength(GetLength()+replace_count));
						s = End()-1-replace_count; end = Begin()-1;
						LPSTR p = &Last();
						for(;s > end;s--)
						{	if(*s == escape_sign || characters_to_be_escaped.Has(*s))
							{	*p-- = characters_to_be_escaped.Mapped(*s);
								*p-- = escape_sign;
							}
							else *p-- = *s;
						}
						ASSERT(p == _p-1);
					}
					return *this;
				}
	/**
	 * @brief trim comment begin with "//" or "/ *"
	 * @details for whole comment line(line begin with "//"), it will be trimed totally
	 * @param code 
	 * @return auto& 
	 */
	auto&		TrimCodeComments(const rt::String_Ref& code)
				{
					if(code.IsEmpty()){	Empty(); return *this; }
					rt::String output;
					output.SetLength(code.GetLength());
					LPSTR out = output;
					LPCSTR p = code.Begin();
					LPCSTR end = code.End();
					while(p<end-1)
					{	
						if(p[0] == '"' || p[0] == '\'')	// copy 
						{	int quotation = p[0];
							*out++ = quotation;
							for(p++;p<end;p++)
							{	*out++ = *p;
								if(p[0] == quotation)
								{
									LPCSTR s = p-1;
									for(;*s == '\\';s--);
									if(((int)(s-p))&1)goto NEXT_SEGMENT;
								}
							}
							break;
						}
						if(p[0] == '/' && p[1] == '/')
						{	p+=2;
							while(p<end && (p[0]!='\r' && p[0]!='\n'))p++;
							if(out[-1] == '\r' || out[-1] == '\n')
								while(p<end && (p[0]=='\r' || p[0]=='\n'))p++;
							continue;
						}
						if(p[0] == '/' && p[1] == '*')
						{	p+=2;
							while(p<end && !(p[-1]=='*' && p[0]=='/'))p++;
							p++;
						}
						*out++ = *p;
					NEXT_SEGMENT:
						p++;
					}
					if(p<end) *out++ = *p;
					*this = rt::String_Ref(output, out);
					return *this;
				}
	auto&		Insert(SIZE_T pos, char c)
				{	SIZE_T org_len = GetLength();
					ASSERT(pos<=GetLength());
					SetLength(GetLength() + 1);
					memmove(_p + pos + 1, _p + pos, org_len - pos);
					_p[pos] = c;
					return *this;
				}
	auto&		Insert(SIZE_T pos, const rt::String_Ref& sub_str)
				{	SIZE_T org_len = GetLength();
					ASSERT(pos<=org_len);
					VERIFY(SetLength(org_len + sub_str.GetLength()));
					memmove(_p + pos + sub_str.GetLength(), _p + pos, org_len - pos);
					memcpy(_p + pos, sub_str.Begin(), sub_str.GetLength());
					return *this;
				}
	auto&		SetDefaultExtName(const rt::String_Ref& extname)
				{	if(GetExtName().IsEmpty())
					{	if(extname[0] != '.')*this += '.';
						*this += extname;
					}
					return *this;
				}
	auto&		RegularizeUTF8()
				{	String_Ref::RegularizeUTF8();
					if(_p)_p[_len] = 0;
					return *this;
				}
	auto&		DecodedURL()	// inplace precent-decoding
				{	rt::String_Ref::DecodedURL();
					if(_p)_p[_len] = 0;
					return *this;
				}
	auto&		Shorten(UINT n = 1)
				{	SetLength(rt::max<SSIZE_T>(0, ((SSIZE_T)GetLength()) - n));
					return *this;
				}
	bool		EndClosure(char closure_symb = ']') ///< false indicate the closure is empty
				{	ASSERT(!IsEmpty());
					if(Last() == ',' || Last() == '.' || Last() == ';'){ Last() = closure_symb; return true; }
					*this += closure_symb; return false;
				}
	LPSTR		Extend(SIZE_T count) // return the address of the first character being extended
				{	auto org_size = GetLength();
					SetLength(org_size + count);
					return &_p[org_size];
				}
};

#undef CPF_STRING_CONNECT_OP
#undef CPF_STRING_CONNECT_OP_
#undef CPF_STRING_EXPR_CONNECT_OP

template<> class TypeTraits<String>
{
public:	
	typedef String t_Val;
	typedef char t_Element;
	typedef String t_Signed;
	typedef String t_Unsigned;
	static const int Typeid = _typeid_string;
	static const bool IsPOD = false;
	static const bool IsNumeric = false;
};

template<> class TypeTraits<String_Ref>
{
public:	
	typedef String_Ref t_Val;
	typedef char t_Element;
	typedef String_Ref t_Signed;
	typedef String_Ref t_Unsigned;
	static const int Typeid = _typeid_string;
	static const bool IsPOD = false;
	static const bool IsNumeric = false;
};
/** @}*/
} // namespace rt

namespace std
{

template<>
struct hash<::rt::String_Ref>: public ::rt::String_Ref::hash_compare {};

template<>
struct hash<::rt::String>: public ::rt::String::hash_compare {};

} // namespace std
/** @}*/