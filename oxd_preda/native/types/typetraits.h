#pragma once
#include "../../../oxd_libsec/oxd_libsec.h"
#include "../abi/vm_types.h"
#include "big_num.h"
#include "string.h"
#include "blob.h"
#include "coins.h"
#include "data.h"
#include "precision_float.h"


namespace rvm
{
namespace _details
{
template<typename T>
inline void _StringifyRealNum(T x, rt::String& append)
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
} // namespace _details

template<typename T>
inline const T& RvmTypeZero(){ return (T&)oxd::SecDataBlock<512/8>::ZeroValue(); }

template<typename T, bool pod = rt::TypeTraits<T>::IsPOD, 
					 bool numeric_pod = std::is_enum<T>::value || rt::NumericTraits<T>::IsBuiltInNumeric
>
struct TypeTraits
{	// all rvm compound types, containers, native contracts and transaction argument pack
	typedef typename T::MutableType		Mutable;
	typedef typename T::ImmutableType	Immutable;
	static const bool		IsMutable = std::is_same<T, Mutable>::value;
	static const bool		IsImmutable = std::is_same<T, Immutable>::value;
	static void				Jsonify(const Immutable& x, rt::Json& json){ x.Jsonify(json); }
	static bool				JsonParse(Mutable& x, const rt::String_Ref& str){ return !str.IsEmpty() && x.JsonParse(str); }
};
	template<> struct TypeTraits<void>
	{
		typedef void		Mutable;
		typedef void		Immutable;
		static const bool	IsMutable = true;
		static const bool	IsImmutable = true;
	};
	template<typename T>
	struct TypeTraits<T, true, true> // all built-in numeric types
	{	typedef T			Mutable;
		typedef T			Immutable;
		static const bool	IsMutable = true;
		static const bool	IsImmutable = true;
		static void			ToString(T x, rt::String& append)
							{	if constexpr (rt::NumericTraits<T>::IsFloat)
									_details::_StringifyRealNum(x, append);
								else
									append += rt::tos::Number(x);
							}
		static void			Jsonify(T x, rt::Json& json){ ToString(x, json.GetInternalString()); }
		static bool			JsonParse(T& x, const rt::String_Ref& str){ return !str.IsEmpty() && str.ToNumber(x) == str.GetLength(); }
	};

	template<typename T>
	struct TypeTraits<T, true, false>
	{	typedef T			Mutable;
		typedef T			Immutable;
		static const bool	IsMutable = true;
		static const bool	IsImmutable = true;
		static void			ToString(const T& x, rt::String& append)
							{	if constexpr (sizeof(T) <= sizeof(uint64_t))
								{	os::Base16Encode(append.Extend(os::Base16EncodeLength(sizeof(T))), &x, sizeof(x));
								}
								else
								{	if constexpr (sizeof(T) == sizeof(rvm::Address))
										((oxd::SecureAddress&)x).ToString(append);
									else 
										os::Base32CrockfordEncodeLowercase(append.Extend(os::Base32EncodeLength(sizeof(T))), &x, sizeof(x));
								}
							}
		static void			Jsonify(const T& x, rt::Json& json)
							{	auto& append = json.GetInternalString();
								append += '"';		ToString(x, append);		append += '"';
							}
		static bool			JsonParse(T& x, const rt::String_Ref& str_in)
							{	auto str = str_in.TrimQuotes();
								if constexpr (sizeof(T) <= sizeof(uint64_t))
								{	uint64_t v;
									if(str.ToNumber(v) != str.GetLength())return false;
									x = v;
									return x == v;
								}
								else if constexpr (sizeof(T) == sizeof(::rvm::Address))
									return ((oxd::SecureAddress&)x).FromString(str);
								else if constexpr ((sizeof(T)%4) == 0)
								{
									return ((sec::DataBlock<sizeof(T)>&)x).FromString(str);
								}
								else
								{	if(os::Base32DecodeLength(str.GetLength()) != sizeof(T))return false;
									return os::Base32CrockfordDecode(&x, sizeof(T), str.Begin(), str.GetLength());
								}
							}
	};


#define RVM_TYPETRAITS_DEF_KEYABLE(immut, mut)																			\
	namespace rvm {																										\
	template<> struct TypeTraits<mut>																					\
	{	typedef mut				Mutable;																				\
		typedef immut			Immutable;																				\
		static const bool		IsMutable = true;																		\
		static const bool		IsImmutable = false;																	\
		static bool				JsonParse(mut& x, const rt::String_Ref& str){ return x.JsonParse(str); }				\
	};																													\
	template<> struct TypeTraits<immut>																					\
	{	typedef mut				Mutable;																				\
		typedef immut			Immutable;																				\
		static const bool		IsMutable = false;																		\
		static const bool		IsImmutable = true;																		\
		static void				Jsonify(const immut& x, rt::Json& json){ x.Jsonify(json); }								\
		static void				ToString(const immut& x, rt::String& append){ x.ToString(append); }						\
		static bool				JsonParse(mut& x, const rt::String_Ref& str){ return x.JsonParse(str); }				\
	};																													\
	}																													\

#define RVM_TYPETRAITS_DEF_STRUCT(T)																					\
		namespace rvm {																									\
		template<> struct TypeTraits<T, true, false>																	\
		{	typedef T				Mutable;																			\
			typedef T				Immutable;																			\
			static const bool		IsMutable = true;																	\
			static const bool		IsImmutable = true;																	\
			static void				Jsonify(const T& x, rt::Json& json){ return x.Jsonify(json); }						\
			static bool				JsonParse(T& x, const rt::String_Ref& str){ return x.JsonParse(str); }				\
		};																												\
		}																												\

#define RVM_TYPETRAITS_DEF_INTERNAL_POD(T)																				\
		namespace rvm {																									\
		template<> struct TypeTraits<T, true, false>																	\
		{	typedef T				Mutable;																			\
			typedef T				Immutable;																			\
			static const bool		IsMutable = true;																	\
			static const bool		IsImmutable = true;																	\
			static void				Jsonify(const T& x, rt::Json& json){ ASSERT(0); }									\
			static bool				JsonParse(T& x, const rt::String_Ref& str){ return false; }							\
		};																												\
		}																												\

#define RVM_TYPETRAITS_GENERIC_DEF(template_arg, immut, mut)															\
	namespace rvm {																										\
	template<template_arg> struct TypeTraits<mut, false, false>															\
	{	typedef mut					Mutable;																			\
		typedef immut				Immutable;																			\
		static const bool			IsMutable = std::is_same<mut, Mutable>::value;										\
		static const bool			IsImmutable = std::is_same<mut, Immutable>::value;									\
		static bool					JsonParse(Mutable& x, const rt::String_Ref& str){ return x.JsonParse(str); }		\
	};																													\
	template<template_arg> struct TypeTraits<immut, false, false>														\
	{	typedef mut					Mutable;																			\
		typedef immut				Immutable;																			\
		static const bool			IsMutable = std::is_same<immut, Mutable>::value;									\
		static const bool			IsImmutable = std::is_same<immut, Immutable>::value;								\
		static void					Jsonify(const Immutable& x, rt::Json& json){ return x.Jsonify(json); }				\
		static bool					JsonParse(Mutable& x, const rt::String_Ref& str){ return x.JsonParse(str); }		\
	};																													\
	}																													\

#define RVM_TYPETRAITS_DEF(immut, mut)	RVM_TYPETRAITS_GENERIC_DEF(MARCO_CONCAT(), immut, mut)

} // namespace rvm

RVM_TYPETRAITS_DEF_STRUCT(Blob)
RVM_TYPETRAITS_DEF(Data, DataMutable)
RVM_TYPETRAITS_DEF(Coins, CoinsMutable)
RVM_TYPETRAITS_DEF_KEYABLE(BigNum, BigNumMutable)
RVM_TYPETRAITS_DEF_KEYABLE(String, StringMutable)

namespace rvm
{
template<typename T>
inline void RvmTypeJsonify(const T& x, rt::Json& json){ TypeTraits<T>::Jsonify(x, json); }

template<typename T>
inline void RvmTypeToString(const T& x, rt::String& append){ TypeTraits<T>::ToString(x, append); }

template<typename T>
inline bool RvmTypeJsonParse(T& x, const rt::String_Ref& str){ return TypeTraits<T>::JsonParse(x, str); }

template<typename T, bool is_pod = rt::TypeTraits<T>::IsPOD>
struct RvmTypeSignature
{
	static void Get(rt::String& n){ T::GetTypeSignature(n); }
};
#define TYPESIG_POD(type, name)	template<> struct RvmTypeSignature<type, rt::TypeTraits<type>::IsPOD>{ static void Get(rt::String& n){ n += rt::SS(#name); } };
TYPESIG_POD(bool,				bool)
TYPESIG_POD(uint8_t,			uint8)
TYPESIG_POD(uint16_t,			uint16)
TYPESIG_POD(uint32_t,			uint32)
TYPESIG_POD(uint64_t,			uint64)
TYPESIG_POD(int8_t,				int8)
TYPESIG_POD(int16_t,			int16)
TYPESIG_POD(int32_t,			int32)
TYPESIG_POD(int64_t,			int64)
TYPESIG_POD(UInt96,				uint96)
TYPESIG_POD(UInt128,			uint128)
TYPESIG_POD(UInt160,			uint160)
TYPESIG_POD(UInt512,			uint512)
TYPESIG_POD(HashValue,			hash)
TYPESIG_POD(Address,			address)
TYPESIG_POD(uint48_t,			uint48)
TYPESIG_POD(uint24_t,			uint24)
TYPESIG_POD(TokenId,			token_id)
#undef TYPESIG_POD

template<typename T_Mutable>
inline auto* RvmImmutableTypeCompose(const T_Mutable& m)
{	typedef typename TypeTraits<T_Mutable>::Immutable RET;
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
#define _SafeFreeRvmImmutableType(p) {if(p){ ::rvm::RvmImmutableTypeDecompose(p); p = nullptr; }}

namespace _details
{

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
	void	Release(){ if(owned){ _SafeFreeRvmImmutableType(v); } v = nullptr; }
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

template<typename T, bool is_pod = rt::TypeTraits<T>::IsPOD, bool is_immutable = TypeTraits<T>::IsImmutable>
struct __EmbedSizeGet;
	template<typename T, bool is_immutable>
	struct __EmbedSizeGet<T, true, is_immutable>{ static UINT Get(const T& x){ return sizeof(T); } };
	template<typename T>
	struct __EmbedSizeGet<T, false, true>{ static UINT Get(const T& x){ return x.GetEmbeddedSize(); } };
	template<typename T>
	struct __EmbedSizeGet<T, false, false>
	{	static UINT Get(const T& x)
		{	typedef typename TypeTraits<T>::Immutable IMMUTABLE;
			return IMMUTABLE::GetEmbeddedSize(x);
		}
	};

template<typename T>
inline UINT _EmbedSize(const T& x){ return __EmbedSizeGet<T>::Get(x); }

template<typename T>
inline UINT _EmbedSize(const rvmtype_ptr<T>& x){ return x.GetValueSize(); }

} // namespace _details
} // namespace rvm