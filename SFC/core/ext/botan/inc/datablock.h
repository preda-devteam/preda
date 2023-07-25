#pragma once

/*********************************************************************
// System Foundation Classes(SFC)
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//     * Neither the name of SFC.  nor the names of its
//       contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

#include "../../../rt/string_type.h"
#include "../../../os/kernel.h"

namespace sec
{
/** \defgroup botan botan
* @ingroup ext
*  @{
*/
template<UINT _LEN>
struct dword_op
{	static void set(LPDWORD x, DWORD v){ *x = v; dword_op<_LEN-1>::set(x+1,v); }
	static void set(LPDWORD x, LPCDWORD v){ *x = *v; dword_op<_LEN-1>::set(x+1,v+1); }
	static void xor_to(LPDWORD x, LPCDWORD v){ *x ^= *v; dword_op<_LEN-1>::xor_to(x+1,v+1); }
	static int  diff_count(LPCDWORD x, LPCDWORD v){ return ((int)(*x != *v)) + dword_op<_LEN-1>::diff_count(x+1,v+1); }
	static bool equ(LPCDWORD x, DWORD v){ if(*x != v)return false; return dword_op<_LEN-1>::equ(x+1,v); }
	static bool equ(LPCDWORD x, LPCDWORD v){ if(*x != *v)return false; return dword_op<_LEN-1>::equ(x+1,v+1); }
	static bool equ_sec(LPCDWORD x, LPCDWORD v){ return 0 == diff_count(x, v); }
	static bool not_equ_sec(LPCDWORD x, LPCDWORD v){ return diff_count(x, v) > 0; }
	static bool not_equ(LPCDWORD x, LPCDWORD v){ if(*x == *v)return false; return dword_op<_LEN-1>::not_equ(x+1,v+1); }
	static int  cmp(LPCDWORD x, LPCDWORD v){ if(*x > *v)return 1; if(*x < *v)return -1; return dword_op<_LEN-1>::cmp(x+1,v+1); }
	static bool equ_constant_time(LPCDWORD x, LPCDWORD v)
				{	bool ret = true;
					for(UINT i=0;i<_LEN;i++)
						ret = ret && x[i] == v[i];
					return ret;
				}
	static bool equ_constant_time(LPCDWORD x, DWORD v)
				{	bool ret = true;
					for(UINT i=0;i<_LEN;i++)
						ret = ret && x[i] == v;
					return ret;
				}
};
	template<> struct dword_op<0>
	{	static void set(LPDWORD x, DWORD v){}
		static void set(LPDWORD x, LPCDWORD v){}
		static void xor_to(LPDWORD x, LPCDWORD v){}
		static bool equ(LPCDWORD x, DWORD v){ return true; }
		static bool equ(LPCDWORD x, LPCDWORD v){ return true; }
		static int  diff_count(LPCDWORD x, LPCDWORD v){ return 0; }
		static bool not_equ(LPCDWORD x, LPCDWORD v){ return true; }
		static int  cmp(LPCDWORD x, LPCDWORD v){ return 0; }
	};

#pragma pack(push,1)
template<UINT _LEN>
class DataBlockRef
{   
protected:
	struct byte_data
	{	BYTE Bytes[_LEN];
		byte_data(DWORD v){ dword_op<_LEN/4>::set((LPDWORD)Bytes, v); }
	};
	static LPBYTE _Zero(){ return nullptr; }
	static LPBYTE _Void(){ return (LPBYTE)-1; }
	static LPCBYTE _GetZero(){ static const byte_data x(0); return x.Bytes; }
	static LPCBYTE _GetVoid(){ static const byte_data x(0xffffffff); return x.Bytes; }
	union {
		DWORD*	DWords;
		BYTE*	Bytes;
	};
	bool	_IsSymbolicZero() const { return Bytes == _Zero(); }
	bool	_IsSymbolicVoid() const { return Bytes == _Void(); }
public:
	typedef dword_op<_LEN/4> dwop;
	static const UINT LEN = _LEN;

    DataBlockRef(){ Bytes = nullptr; }
	DataBlockRef(decltype(NULL) x){ if(x==0){ Bytes = nullptr; }else if(x==-1){ Bytes = (LPBYTE)-1; }else{ ASSERT(0); } }
	DataBlockRef(const DataBlockRef& x){ Bytes = (LPBYTE)x.Bytes; }

	LPDWORD		GetDWords(){ return (LPDWORD)GetBytes(); }
	LPCDWORD	GetDWords() const { return (LPCDWORD)GetBytes(); }
	LPBYTE		GetBytes(){ ASSERT(Bytes); return Bytes; }
	LPCBYTE		GetBytes() const 
				{	if(_IsSymbolicZero())return _GetZero();
					if(_IsSymbolicVoid())return _GetVoid();
					return Bytes;
				}

	template< template<UINT l, bool s> class T >
	DataBlockRef(const T<_LEN, true>& x){ Bytes = (LPBYTE)x.Bytes; }
	template< template<UINT l, bool s> class T >
	DataBlockRef(const T<_LEN, false>& x){ Bytes = (LPBYTE)x.Bytes; }

    operator	LPCBYTE () const { return (LPCBYTE)GetBytes(); }
	operator	LPBYTE () { return (LPBYTE)GetBytes(); }
	template<typename T>
	const BYTE&	operator [](T i) const { return GetBytes()[i]; }
	template<typename T>
	BYTE&		operator [](T i){ return GetBytes()[i]; }
	UINT		GetLength() const { return _LEN; }

	template<typename T>
	const T&	Cast() const { ASSERT(sizeof(T) == _LEN); return *((const T*)GetBytes()); }

public:
	bool	operator == (const DataBlockRef<_LEN>& x) const 
			{	if(Bytes == x.Bytes)return true;
				if(x._IsSymbolicVoid() || _IsSymbolicVoid() || x._IsSymbolicZero() || _IsSymbolicZero())return false;
				return dwop::equ(GetDWords(), x.GetDWords()); 
			}
	bool	operator != (const DataBlockRef<_LEN>& x) const 
			{	if(Bytes == x.Bytes)return false;
				if(x._IsSymbolicVoid() || _IsSymbolicVoid() || x._IsSymbolicZero() || _IsSymbolicZero())return true;
				return dwop::not_equ(GetDWords(), x.GetDWords());
			}
	bool	operator < (const DataBlockRef<_LEN>& x) const	
			{	if((x._IsSymbolicVoid() && !_IsSymbolicVoid()) || (_IsSymbolicZero() && !x._IsSymbolicZero()))return true;
				if(x._IsSymbolicVoid() || _IsSymbolicVoid() || x._IsSymbolicZero() || _IsSymbolicZero())return false;
				return dwop::cmp(GetDWords(), x.GetDWords()) < 0;
			}
	bool	operator > (const DataBlockRef<_LEN>& x) const
			{	if((!x._IsSymbolicVoid() && _IsSymbolicVoid()) || (!_IsSymbolicZero() && x._IsSymbolicZero()))return true;
				if(x._IsSymbolicVoid() || _IsSymbolicVoid() || x._IsSymbolicZero() || _IsSymbolicZero())return false;
				return dwop::cmp(GetDWords(), x.GetDWords()) > 0;
			}
public:
	struct hash_compare
	{	
		enum // parameters for hash table
		{	bucket_size = 4,	// 0 < bucket_size
			min_buckets = 8		// min_buckets = 2 ^^ N, 0 < N
		};
		size_t operator()(const DataBlockRef& key) const 
		{	if(key._IsSymbolicZero())return 0;
			if(key._IsSymbolicVoid())return (size_t)-1;
			return rt::_details::_HashValueFix<_LEN>::Val(key.Bytes);
		}
		bool operator()(const DataBlockRef& _Keyval1, const DataBlockRef& _Keyval2) const { return _Keyval1 < _Keyval2;	}
		template<typename OStream>
		friend OStream& operator <<(OStream& s, const DataBlockRef& d)
		{	return s << rt::tos::Base32LowercaseOnStack<_LEN*8/5 + 4>((LPCBYTE)d, _LEN);
		}
	};
};
#pragma pack(pop)

namespace _details
{
template<UINT _LEN, bool is_sec>
struct DataBlockStg;
	template<UINT _LEN>
	struct DataBlockStg<_LEN, false>
	{	TYPETRAITS_DECLARE_POD;
		union 
		{	DWORD	DWords[_LEN/sizeof(DWORD)];
			BYTE	Bytes[_LEN];
		};
	};
	template<UINT _LEN>
	struct DataBlockStg<_LEN, true>
	{	TYPETRAITS_DECLARE_POD;
		union 
		{	DWORD	DWords[_LEN/sizeof(DWORD)];
			BYTE	Bytes[_LEN];
		};
		~DataBlockStg(){ rt::Zero(Bytes, _LEN); }
	};
} // namespace _details

#pragma pack(push,1)
template<UINT _LEN, bool is_sec = false>
struct DataBlock: public _details::DataBlockStg<_LEN, is_sec>
{
    typedef		_details::DataBlockStg<_LEN, is_sec> _SC;
	bool		_IsSymbolicZero() const { return false; }
	bool		_IsSymbolicVoid() const { return false; }
	LPDWORD		GetDWords(){ return _SC::DWords; }
	LPCDWORD	GetDWords() const { return _SC::DWords; }
	LPBYTE		GetBytes(){ return _SC::Bytes; }
	LPCBYTE		GetBytes() const { return _SC::Bytes; }

public:
	typedef dword_op<_LEN/4> dwop;
	static const UINT LEN = _LEN;
    operator	LPCBYTE () const { return GetBytes(); }
	operator	LPBYTE () { return GetBytes(); }
    operator    DataBlock<_LEN, !is_sec>& (){ return *(DataBlock<_LEN, !is_sec>*)this; }
    operator    const DataBlock<_LEN, !is_sec>& () const { return *(DataBlock<_LEN, !is_sec>*)this; }
	template<typename T>
	const BYTE&  operator [](T i) const { return GetBytes()[i]; }
	template<typename T>
	BYTE& operator [](T i){ return GetBytes()[i]; }
	UINT		GetLength() const { return _LEN; }
	void		CopyTo(LPVOID buf) const { *((DataBlock*)buf) = *this; }
	void		SwitchByteOrder(){ rt::SwapByteOrder(*this); }
	bool		FromBase16(const rt::String_Ref& str){ return os::Base16DecodeLength(str.GetLength()) == _LEN && os::Base16Decode(GetBytes(), _LEN, str.Begin(), str.GetLength()); }
	bool		FromBase32(const rt::String_Ref& str){ return os::Base32CrockfordDecode(this, sizeof(*this), str.Begin(), str.GetLength()); }
	bool		FromBase64(const rt::String_Ref& str){ SIZE_T len; return os::Base64DecodeLength(str.Begin(), str.GetLength()) == _LEN && os::Base64Decode(GetBytes(), &len, str.Begin(), str.GetLength()) && len == _LEN; }
	bool		FromString(const rt::String_Ref& str)
				{	if(str.GetLength() == os::Base16EncodeLength(LEN) && FromBase16(str))return true;
					if(str.GetLength() == os::Base32EncodeLength(LEN) && FromBase32(str))return true;
					if(str.GetLength() == os::Base64EncodeLength(LEN) && FromBase64(str))return true;
					rt::Zero(*this); return false;
				}
	void		ToBase64(rt::String& str) const	{ str.SetLength(os::Base64EncodeLength(_LEN)); os::Base64Encode(str, GetBytes(), _LEN); }
	void		ToBase32(rt::String& str) const { str.SetLength(os::Base32EncodeLength(_LEN)); os::Base32CrockfordEncodeLowercase(str, GetBytes(), _LEN); }
	void		ToBase16(rt::String& str) const	{ str.SetLength(os::Base16EncodeLength(_LEN)); os::Base16Encode(str, GetBytes(), _LEN); }
	bool		IsZero() const { return dwop::equ(GetDWords(), (DWORD)0); }
	bool		IsVoid() const { return dwop::equ(GetDWords(), (DWORD)0xffffffff); }
	DataBlock&	Random(UINT seed){ rt::Randomizer(seed).Randomize(GetBytes(), _LEN); return *this; }

    //void   Xor(const DataBlock& x){ dwop::xor_to(DWords, x.GetDWords()); }
    //template<bool sb> void   Xor(const DataBlock<_LEN, sb>& x){ dwop::xor_to(DWords, x.GetDWords()); }
    
	void		From(const DataBlock& x){	dwop::set(GetDWords(), x.GetDWords()); }
	int			Compare(const DataBlock& x) const { return dwop::cmp(GetDWords(), x.GetDWords()); }
    void		operator ^= (const DataBlock& x){ dwop::xor_to(GetDWords(), x.GetDWords()); }
	bool		operator < (const DataBlock& x) const	{ return dwop::cmp(GetDWords(), x.GetDWords()) < 0; }
	bool		operator <= (const DataBlock& x) const { return dwop::cmp(GetDWords(), x.GetDWords()) <= 0; }
	bool		operator > (const DataBlock& x) const { return dwop::cmp(GetDWords(), x.GetDWords()) > 0; }
	bool		operator >= (const DataBlock& x) const { return dwop::cmp(GetDWords(), x.GetDWords()) >= 0; }
	// equ_sec and not_equ_sec are time-consistent comparing to defense against timing attack
	bool		operator == (const DataBlock& x) const { return is_sec?dwop::equ_sec(GetDWords(), x.GetDWords()):dwop::equ(GetDWords(), x.GetDWords()); }
	bool		operator != (const DataBlock& x) const { return is_sec?dwop::not_equ_sec(GetDWords(), x.GetDWords()):dwop::not_equ(GetDWords(), x.GetDWords()); }

	auto&		Zero(){ dwop::set(GetDWords(), (DWORD)0); return *this; }
	auto&		Void(){ dwop::set(GetDWords(), (DWORD)0xffffffff); return *this; }

public:
	struct hash_compare
	{	
		enum // parameters for hash table
		{	bucket_size = 4,	// 0 < bucket_size
			min_buckets = 8		// min_buckets = 2 ^^ N, 0 < N
		};
		size_t operator()(const DataBlock& key) const { return rt::_details::_HashValueFix<_LEN>::Val(key.Bytes); }
		bool operator()(const DataBlock& _Keyval1, const DataBlock& _Keyval2) const	{ return _Keyval1 < _Keyval2; }
	};
	rt::String_Ref ToString() const { return rt::String_Ref((LPCSTR)GetBytes(),_LEN); }

public:
	template<bool sb>
	const DataBlock<_LEN, sb>& operator = (const DataBlock<_LEN, sb>& x){ From(x); return x; }

	typedef DataBlockRef<_LEN> RefType;
	RefType Ref(){ return RefType(*this); }
	const RefType Ref() const { return RefType(*this); }

	template<typename OStream>
	friend OStream& operator <<(OStream& s, const DataBlock& d)
	{ return s << rt::tos::Base64OnStack<_LEN*8/5 + 4>((LPCBYTE)d, _LEN); }
};
#pragma pack(pop)
/** @}*/
} // namespace sec

namespace std
{
template<UINT LEN, bool is_sec>
struct hash<::sec::DataBlock<LEN, is_sec>>: public ::sec::DataBlock<LEN, is_sec>::hash_compare {};

template<UINT LEN>
struct hash<::sec::DataBlockRef<LEN>>: public ::sec::DataBlockRef<LEN>::hash_compare {};
} // namespace std
