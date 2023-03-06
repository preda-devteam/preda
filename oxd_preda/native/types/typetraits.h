#pragma once
#include "big_num.h"
#include "string.h"
#include "blob.h"
#include "coins.h"
#include "data.h"
#include "precision_float.h"
#include "../../../oxd_libsec/oxd_libsec.h"


namespace rvm
{

namespace _details
{
template<typename T, bool pod = rt::TypeTraits<T>::IsPOD>
struct _TypeTraits;
	template<typename T>
	struct _TypeTraits<T, true>
	{	typedef T			Mutable;
		typedef T			Immutable;
		static const bool	IsMutable = false;
	};
	template<typename T>
	struct _TypeTraits<T, false>
	{	typedef typename T::MutableType		Mutable;
		typedef typename T::ImmutableType	Immutable;
		static const bool IsMutable =		rt::IsTypeSame<T, Mutable>::Result;
	};

#define _DETAILED_RVM_TYPETRAIT_NONPOD(mut, immut)		\
	template<> struct _TypeTraits<mut, false>			\
	{	typedef mut				Mutable;				\
		typedef immut			Immutable;				\
		static const bool		IsMutable = true;		\
	};													\
	template<> struct _TypeTraits<immut, false>			\
	{	typedef mut				Mutable;				\
		typedef immut			Immutable;				\
		static const bool		IsMutable = false;		\
	};													\

	_DETAILED_RVM_TYPETRAIT_NONPOD(rvm::BigNumMutable,	rvm::BigNum)
	_DETAILED_RVM_TYPETRAIT_NONPOD(rvm::DataMutable,	rvm::Data)
	_DETAILED_RVM_TYPETRAIT_NONPOD(rvm::CoinsMutable,	rvm::Coins)
	_DETAILED_RVM_TYPETRAIT_NONPOD(rvm::StringMutable,	rvm::String)
	_DETAILED_RVM_TYPETRAIT_NONPOD(rvm::BlobMutable,	rvm::Blob)
	_DETAILED_RVM_TYPETRAIT_NONPOD(rvm::NonFungibleVaultMutable,	rvm::NonFungibleVault)

#undef _DETAILED_RVM_TYPETRAIT_NONPOD

template<typename T, typename ARG,
		bool embedded_type = rt::IsTypeSame<T, typename rt::Remove_QualiferAndRef<ARG>::t_Result>::Result, 
		bool is_pod = rt::TypeTraits<T>::IsPOD
>
struct _Embed;
	template<typename T, typename ARG> struct _Embed<T, ARG, true, false>
	{	static UINT Set(LPBYTE p, const ARG& t){ UINT ret; memcpy(p, &t, ret = t.GetEmbeddedSize()); return ret; }
		static UINT GetEmbeddedSize(const ARG& t){ return t.GetEmbeddedSize(); }
		static bool IsEmbeddable(const ARG& t) { return true; }
	};
	template<typename T, typename ARG> struct _Embed<T, ARG, true, true>
	{	static UINT Set(LPBYTE p, const ARG& t){ memcpy(p, &t, sizeof(T)); return sizeof(T); }
		static UINT GetEmbeddedSize(const ARG& t){ return sizeof(T); }
		static bool IsEmbeddable(const ARG& t) { return true; }
	};
	template<typename T, typename ARG> struct _Embed<T, ARG, false, false>
	{	static UINT Set(LPBYTE p, const ARG& t){ return ((T*)p)->Embed(t); }
		static UINT GetEmbeddedSize(const ARG& t){ return T::GetEmbeddedSize(t); }
		static bool IsEmbeddable(const ARG& t){ return T::IsEmbeddable(t); }
	};
	template<typename T, typename ARG> struct _Embed<T, ARG, false, true>
	{	static UINT Set(LPBYTE p, const ARG& t){ (*(T*)p) = (T)t; return sizeof(T); }
		static UINT GetEmbeddedSize(const ARG& t){ return sizeof(T); }
		static bool IsEmbeddable(const ARG& t) { return true; }
	};
} // namespace _details

template<typename T_Mutable>
inline auto* RvmImmutableTypeCompose(const T_Mutable& m)
{	typedef typename _details::_TypeTraits<T_Mutable>::Immutable RET;
	auto* ret = (RET*)VERIFY(_Malloc8AL(BYTE, RET::GetEmbeddedSize(m)));
	ret->Embed(m);
	return ret;
}

inline rvm::String* RvmImmutableTypeCompose(const rt::String_Ref& x){ return RvmImmutableTypeCompose((const StringMutable&)x); }
inline rvm::String* RvmImmutableTypeCompose(LPCSTR x){ return RvmImmutableTypeCompose(rt::String_Ref(x)); }

template<typename T>
inline T* RvmImmutableTypeClone(const T* m)
{	if(!m)return nullptr;
	UINT size = m->GetEmbeddedSize();
	T* ret = (T*)VERIFY(_Malloc8AL(BYTE, size));
	memcpy(ret, m, size);
	return ret;
}

inline void RvmImmutableTypeDecompose(LPVOID p){ _SafeFree8AL(p); }
#define _SafeRvmImmutableTypeFree(p) {if(p){ rvm::RvmImmutableTypeDecompose(p); p = nullptr; }}

namespace _details
{

template<typename T>
inline void _JsonifyRealNum(T x, rt::String& append)
{	UINT len = (UINT)append.GetLength();
	append.SetLength(len + 20);
	append.SetLength(len + rt::_details::string_ops::ftoa(x, &append[len], 9));
	if(append.FindCharacter('e', len)<0)
	{	for(UINT i=(UINT)append.GetLength()-1; i>len; i--)
			if(append[i] != '0')
			{	if(append[i] == '.')i--;
				append.SetLength(i+1);
				break;
			}
	}
}

struct _Jsonify
{	
	template<typename T>
	_Jsonify(const T& x, rt::String& append){ x.Jsonify((rt::Json&)append); }

	_Jsonify(const HashValue& x, rt::String& append){
		append += '"';
		rt::String tmp;
		tmp.SetLength(os::Base32EncodeLength(RVM_HASH_SIZE));
		os::Base32CrockfordEncodeLowercase(tmp, &x, sizeof(x));
		append += tmp + '"';
	}
	_Jsonify(ULONGLONG x, rt::String& append){ append += rt::tos::Number(x); }
	_Jsonify(LONGLONG x, rt::String& append){ append += rt::tos::Number(x); }
	_Jsonify(UINT x, rt::String& append){ append += rt::tos::Number(x); }
	_Jsonify(int x, rt::String& append){ append += rt::tos::Number(x); }
	_Jsonify(short x, rt::String& append){ append += rt::tos::Number(x); }
	_Jsonify(signed char x, rt::String& append){ append += rt::tos::Number((int)x); }
	_Jsonify(BYTE x, rt::String& append){ append += rt::tos::Number(x); }
	_Jsonify(WORD x, rt::String& append){ append += rt::tos::Number(x); }
	_Jsonify(bool x, rt::String& append){ append += x?"true":"false"; }
	_Jsonify(float x, rt::String& append){ _JsonifyRealNum(x, append); }
	_Jsonify(double x, rt::String& append){ _JsonifyRealNum(x, append); }
	_Jsonify(const BigNumRough& x, rt::String& append):_Jsonify(x.ToDouble(), append){ }
	_Jsonify(const uint48_t& x, rt::String& append){ append += rt::tos::Number((ULONGLONG)x); }
	_Jsonify(const Address& x, rt::String& append){
		char addr_buf[rvm::_details::ADDRESS_BASE32_LEN];
		append += '"';
		rvm::_details::ADDRESS_TO_STRING(x, addr_buf);
		append += rt::String(addr_buf, rvm::_details::ADDRESS_BASE32_LEN);
		append += rt::SS(":") + oxd::SecuritySuite::IdToString(x._SSID);
		append += '"'; }
	_Jsonify(TokenId x, rt::String& append){ append += rt::tos::Number((UINT)x); }
	_Jsonify(const NonFungibleToken& x, rt::String& append){ append += rt::tos::Number((ULONGLONG)x.GetId()); }
};

struct _JsonDictKey
{
	template<typename T>
	_JsonDictKey(const T& x, rt::String& append){ x.Jsonify((rt::Json&)append); }

	_JsonDictKey(const HashValue& x, rt::String& append) {
		append += '"';
		rt::String tmp;
		tmp.SetLength(os::Base32EncodeLength(RVM_HASH_SIZE));
		os::Base32CrockfordEncodeLowercase(tmp, &x, sizeof(x));
		append += tmp + '"';
	}
	_JsonDictKey(ULONGLONG x, rt::String& append){ append += '"'; append += rt::tos::Number(x) + '"'; }
	_JsonDictKey(LONGLONG x, rt::String& append){ append += '"'; append += rt::tos::Number(x) + '"'; }
	_JsonDictKey(UINT x, rt::String& append){ append += '"'; append += rt::tos::Number(x) + '"'; }
	_JsonDictKey(int x, rt::String& append){ append += '"'; append += rt::tos::Number(x) + '"'; }
	_JsonDictKey(BYTE x, rt::String& append){ append += '"'; append += rt::tos::Number(x) + '"'; }
	_JsonDictKey(WORD x, rt::String& append){ append += '"'; append += rt::tos::Number(x) + '"'; }
	_JsonDictKey(bool x, rt::String& append){ append += '"'; append += x?"true\"":"false\""; }
	_JsonDictKey(double x, rt::String& append)
			{	append += '"';
				UINT len = (UINT)append.GetLength();
				append.SetLength(len + 20);
				append.SetLength(len + rt::_details::string_ops::ftoa(x, &append[len], 9));
				if(append.FindCharacter('e', len)<0)
				{	for(UINT i=(UINT)append.GetLength()-1; i>len; i--)
						if(append[i] != '0')
						{	if(append[i] == '.')i--;
							append.SetLength(i+1);
							break;
						}
				}
				append += '"';
			}
	_JsonDictKey(const BigNumRough& x, rt::String& append):_JsonDictKey(x.ToDouble(), append){ }
	_JsonDictKey(const uint48_t& x, rt::String& append){ append += '"'; append += rt::tos::Number((ULONGLONG)x) + '"'; }
	//_JsonDictKey(const EntityAddress& x, rt::String& append){ append += '"'; x.ToString(append); append += '"'; }
	_JsonDictKey(TokenId x, rt::String& append){ append += '"'; append += rt::tos::Number((UINT)x) + '"'; }
};

struct _JsonParse
{
	bool ret;
	operator bool() const { return ret; }

	template<typename T>
	_JsonParse(T& x, const rt::String_Ref& str){ ret = x.JsonParse(str.TrimQuotes()); }

	_JsonParse(bool& x, const rt::String_Ref& str){ ret = !str.IsEmpty() && str.ToNumber(x) == str.GetLength(); }
	_JsonParse(uint8_t& x, const rt::String_Ref& str){ ret = !str.IsEmpty() && str.ToNumber<uint8_t,10,false,0,0>(x) == str.GetLength(); }
	_JsonParse(uint16_t& x, const rt::String_Ref& str){ ret = !str.IsEmpty() && str.ToNumber<uint16_t,10,false,0,0>(x) == str.GetLength(); }
	_JsonParse(uint32_t& x, const rt::String_Ref& str){ ret = !str.IsEmpty() && str.ToNumber<uint32_t,10,false,0,0>(x) == str.GetLength(); }
	_JsonParse(uint64_t& x, const rt::String_Ref& str){ ret = !str.IsEmpty() && str.ToNumber<uint64_t,10,false,0,0>(x) == str.GetLength(); }
	_JsonParse(int8_t& x, const rt::String_Ref& str){ ret = !str.IsEmpty() && str.ToNumber<int8_t,10,false,0,0>(x) == str.GetLength(); }
	_JsonParse(int16_t& x, const rt::String_Ref& str){ ret = !str.IsEmpty() && str.ToNumber<int16_t,10,false,0,0>(x) == str.GetLength(); }
	_JsonParse(int32_t& x, const rt::String_Ref& str){ ret = !str.IsEmpty() && str.ToNumber<int32_t,10,false,0,0>(x) == str.GetLength(); }
	_JsonParse(int64_t& x, const rt::String_Ref& str){ ret = !str.IsEmpty() && str.ToNumber<int64_t,10,false,0,0>(x) == str.GetLength(); }
	_JsonParse(uint48_t& x, const rt::String_Ref& str){ ULONGLONG l; if((ret = str.ToNumber(l) && l<=uint48_t::Max))x = l; }
	_JsonParse(BigNumMutable& x, const rt::String_Ref& str){ ret = !str.IsEmpty() && x.FromString(str.TrimQuotes()); }
	_JsonParse(Address& x, const rt::String_Ref& str){ ret = ((oxd::SecureAddress&)x).FromString(str.TrimQuotes()); }
	_JsonParse(HashValue& x, const rt::String_Ref& str){ ret = ((sec::DataBlock<RVM_HASH_SIZE>&)x).FromString(str.TrimQuotes()); }
	_JsonParse(rt::String& x, const rt::String_Ref& str){ ret = true; x = str.TrimQuotes(); }
	_JsonParse(DataMutable& x, const rt::String_Ref& str){ ret = x.JsonParse(str); }
	_JsonParse(BlobMutable& x, const rt::String_Ref& str){ ret = x.FromString(str.TrimQuotes()); }
	_JsonParse(TokenId& x, const rt::String_Ref& str){ ret = str.ToNumber((UINT&)x) > 0;; }
	template<typename T>
	_JsonParse(rt::BufferEx<T>& x, const rt::String_Ref& str)
	{	ret = false;
		if(str.IsEmpty() || str.First() != '[' || str.Last() != ']')return;
		x.ShrinkSize(0);
		rt::JsonArray a(str);
		rt::String_Ref item;
		while(a.GetNextObject(item))
			if(!_JsonParse(x.push_back(), item)){ x.ShrinkSize(0); return; }
		ret = true;
	}
	//_JsonParse(rvm::NonFungibleVaultMutable& x, const rt::String_Ref& str) { ret = x.JsonParse(str.TrimQuotes());}
};

template<typename T, bool is_pod = rt::TypeTraits<T>::IsPOD>
struct _TypeSignature
{
	static void Get(rt::String& n){ T::GetTypeSignature(n); }
};
#define TYPESIG_POD(type, name)	template<> struct _TypeSignature<type, rt::TypeTraits<type>::IsPOD>{ static void Get(rt::String& n){ n += rt::SS(#name); } };
TYPESIG_POD(bool,					bool)
TYPESIG_POD(uint8_t,				uint8)
TYPESIG_POD(uint16_t,				uint16)
TYPESIG_POD(uint32_t,				uint32)
TYPESIG_POD(uint64_t,				uint64)
TYPESIG_POD(int8_t,					int8)
TYPESIG_POD(int16_t,				int16)
TYPESIG_POD(int32_t,				int32)
TYPESIG_POD(int64_t,				int64)
TYPESIG_POD(rvm::HashValue,			hash)
TYPESIG_POD(Address,				address)
TYPESIG_POD(rvm::uint48_t,			uint48)
TYPESIG_POD(rvm::uint24_t,			uint24)
TYPESIG_POD(rvm::TokenId,			token_id)
TYPESIG_POD(rvm::NonFungibleToken,	nft_id)
#undef TYPESIG_POD

template<typename T>
inline auto* CloneContractState(const T& x)
{
	UINT size = x.GetEmbeddedSize();
	auto* ret = (T*)_Malloc32AL(BYTE, size);
	memcpy(ret, &x, size);
	return ret;
}

template<typename T>
inline void SafeFreeContractState(T& p){ _SafeFree32AL(p); }
} // namespace _details

enum RvmTypePointerSupplyMode
{
	RVMPTR_COPY = 0,	// just copy the value and leave the pointer alone
	RVMPTR_KEEP,		// keep the original pointer in internal representation, but don't release when no longer needed
	RVMPTR_TAKE,		// take the original pointer in internal representation, and will release internally
};

namespace _details
{
template<typename VAL>
struct rvmtype_ptr
{	VAL*	v;
	bool	owned;
	operator VAL*(){ return v; }
	operator const VAL*() const { return v; }
	VAL* operator ->(){ return v; }
	const VAL* operator ->() const { return v; }
	rvmtype_ptr(){ v = nullptr; owned = false; }
	rvmtype_ptr(const VAL* x, RvmTypePointerSupplyMode mode)
			{	switch(mode)
				{	case RVMPTR_COPY:
					{	UINT size = x->GetEmbeddedSize();
						v = (VAL*)_Malloc8AL(BYTE, size);
						memcpy(v, &x, size);
						owned = true; 
					} break;
					case RVMPTR_KEEP: v = (VAL*)x; owned = false; break;
					case RVMPTR_TAKE: v = (VAL*)x; owned = true; break;
					default: ASSERT(0);
				}
			}
	~rvmtype_ptr(){ Release(); }
	void	Detach(){ v = nullptr; owned = false; }
	void	Release(){ if(owned){ _SafeRvmImmutableTypeFree(v); } v = nullptr; }
	void	Replace(const VAL& x)
			{	UINT size = x.GetEmbeddedSize();
				if(v && owned && v->GetEmbeddedSize() >= size)
					memcpy(v, &x, size);
				else
				{	Release();
					owned = true;
					v = (VAL*)_Malloc8AL(BYTE, size);
					memcpy(v, &x, size);
				}
			}
	void	Set(const VAL* x, RvmTypePointerSupplyMode mode)
			{	switch(mode)
				{	case RVMPTR_COPY: Replace(*x); break;
					case RVMPTR_KEEP: Release(); v = (VAL*)x; owned = false; break;
					case RVMPTR_TAKE: Release(); v = (VAL*)x; owned = true; break;
					default: ASSERT(0);
				}
			}
	UINT	GetValueSize() const { return v?v->GetEmbeddedSize():0; }
	auto&	SafeGet() const { return v?*v:VAL::Zero(); }
	auto&	Get(){ ASSERT(v); return *v; }
	void	MarkAsDeleted(){ if(owned){ RvmTypeDecompose(v); } v = (VAL*)-1; owned = false; }
	bool	IsMarkedAsDeleted() const { return v == (VAL*)-1; }
};

template<typename T, bool is_pod = rt::TypeTraits<T>::IsPOD, bool is_mutable = _TypeTraits<T>::IsMutable>
struct __EmbedSizeGet;
	template<typename T, bool is_mutable>
	struct __EmbedSizeGet<T, true, is_mutable>{ static UINT Get(const T& x){ return sizeof(T); } };
	template<typename T>
	struct __EmbedSizeGet<T, false, false>{ static UINT Get(const T& x){ return x.GetEmbeddedSize(); } };
	template<typename T>
	struct __EmbedSizeGet<T, false, true>
	{	static UINT Get(const T& x)
		{	typedef typename _TypeTraits<T>::Immutable IMMUTABLE;
			return IMMUTABLE::GetEmbeddedSize(x);
		}
	};

template<typename T>
inline UINT _EmbedSize(const T& x){ return __EmbedSizeGet<T>::Get(x); }

template<typename T>
inline UINT _EmbedSize(const rvmtype_ptr<T>& x){ return x.GetValueSize(); }

} // namespace _details

} // namespace rvm
