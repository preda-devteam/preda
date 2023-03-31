#pragma once
#include "typetraits.h"

namespace rvm
{

namespace _details
{
#pragma pack(push, 1)

struct om_pair_void_value
{	void	val() const {}
};

template<bool immutable, typename KEY, typename VAL, bool is_pod_key = rt::TypeTraits<KEY>::IsPOD, bool is_pod_val = rt::TypeTraits<VAL>::IsPOD>
struct _map_pair;
	template<bool immutable, typename KEY, typename VAL>
	struct _map_pair<immutable, KEY, VAL, true, true>
	{	KEY		_key;
		VAL		_value;
		auto&	key() const { return _key; }
		auto&	val() const { return _value; }
		_map_pair() = default;
		template<typename T>
		_map_pair(T& x){ Embed(x); }
		void Set(const KEY* k, RvmTypePointerSupplyMode key_mode, const VAL* v, RvmTypePointerSupplyMode val_mode){ _key = *k; _value = *v; }
		void Set(const _map_pair& x, RvmTypePointerSupplyMode mode){ _key = x.key(); _value = x.val(); }
		void SetValue(const VAL* v, RvmTypePointerSupplyMode val_mode){ _value = *v; }
		UINT GetEmbeddedSize() const { return sizeof(KEY) + sizeof(VAL); }
		template<typename ITEM>
		UINT Embed(const ITEM& x){ _key = x.key(); _value = x.val(); return GetEmbeddedSize(); }
	};
		template<bool immutable, typename KEY>
		struct _map_pair<immutable, KEY, void, true, true>: public om_pair_void_value
		{	KEY		_key;
			auto&	key() const { return _key; }
			_map_pair() = default;
			template<typename T>
			_map_pair(T& x){ _key = x.key(); }
			void Set(const KEY* k, RvmTypePointerSupplyMode key_mode, const void* v, RvmTypePointerSupplyMode val_mode){ _key = *k; }
			void Set(const _map_pair& x, RvmTypePointerSupplyMode mode){ _key = x.key(); }
			void SetValue(const void* v, RvmTypePointerSupplyMode val_mode){}
			UINT GetEmbeddedSize() const { return sizeof(KEY); }
			template<typename ITEM>
			UINT	Embed(const ITEM& x){ rt::Copy(_key, x.key()); return sizeof(KEY); }
		};
	template<typename KEY, typename VAL>
	struct _map_pair<true, KEY, VAL, false, true>
	{	BYTE	_data[1]; // <key> + <val>
		auto&	key() const { return *(KEY*)_data; }
		auto&	val() const { return *(VAL*)(_data + key().GetEmbeddedSize()); }
		UINT	GetEmbeddedSize() const { return key().GetEmbeddedSize() + sizeof(VAL); }
		template<typename ITEM>
		UINT	Embed(const ITEM& x)
				{	UINT s = rt::_CastToNonconst(key()).Embed(x.key());
					rt::Copy(*(VAL*)(_data + s), x.val());
					return s + sizeof(VAL);
				}
	};
		template<typename KEY>
		struct _map_pair<true, KEY, void, false, true>: public om_pair_void_value
		{	BYTE	_data[1]; // <key> + <val>
			auto&	key() const { return *(KEY*)_data; }
			UINT	GetEmbeddedSize() const { return key().GetEmbeddedSize(); }
			template<typename ITEM>
			UINT	Embed(const ITEM& x){ return rt::_CastToNonconst(key()).Embed(x.key());	}
		};
	template<typename KEY, typename VAL>
	struct _map_pair<true, KEY, VAL, true, false>
	{	KEY		_key;
		BYTE	_data[1]; // <key> + <val>
		auto&	key() const { return _key; }
		auto&	val() const { return *(VAL*)_data; }
		UINT	GetEmbeddedSize() const { return sizeof(KEY) + val().GetEmbeddedSize(); }
		template<typename ITEM>
		UINT	Embed(const ITEM& x)
				{	rt::Copy(_key, x.key());
					return rt::_CastToNonconst(val()).Embed(x.val()) + sizeof(KEY);
				}
	};
	template<typename KEY, typename VAL>
	struct _map_pair<true, KEY, VAL, false, false>
	{	BYTE	_data[1]; // <key> + <val>
		auto&	key() const { return *(KEY*)_data; }
		auto&	val() const { return *(VAL*)(_data + key().GetEmbeddedSize()); }
		UINT	GetEmbeddedSize() const 
				{	UINT key_size = key().GetEmbeddedSize();
					return key_size + ((VAL*)(_data + key_size))->GetEmbeddedSize();
				}
		template<typename ITEM>
		UINT	Embed(const ITEM& x)
				{	UINT s = rt::_CastToNonconst(key()).Embed(x.key());
					return s + ((VAL*)(_data + s))->Embed(x.val());
				}
	};
	template<typename KEY, typename VAL>
	struct _map_pair<false, KEY, VAL, false, true>
	{	_details::rvmtype_ptr<KEY>	_key;
		VAL		_value;
		auto&	key() const { return VERIFY(_key.v); }
		auto&	val() const { return _value; }
		_map_pair() = default;
		template<typename T>
		_map_pair(T& x):_key(&x.key(), RVMPTR_KEEP){ _value = x.val(); }
		void Set(const KEY* k, RvmTypePointerSupplyMode key_mode, const VAL* v, RvmTypePointerSupplyMode val_mode){ _key.Set(k, key_mode); _value = *v; }
		void Set(const _map_pair& x, RvmTypePointerSupplyMode mode){ _key.Set(&x.key(), mode); _value = x.val(); ASSERT(mode != RVMPTR_TAKE); }
		void SetValue(const VAL* v, RvmTypePointerSupplyMode val_mode){ _value = *v; }
		UINT GetEmbeddedSize() const { return _key.GetValueSize() + sizeof(VAL); }
	};
		template<typename KEY>
		struct _map_pair<false, KEY, void, false, true>: public om_pair_void_value
		{	_details::rvmtype_ptr<KEY>	_key;
			auto&	key() const { return *(VERIFY(_key.v)); }
			_map_pair() = default;
			template<typename T>
			_map_pair(T& x):_key(&x.key(), RVMPTR_KEEP){}
			void Set(const KEY* k, RvmTypePointerSupplyMode key_mode, const void* v, RvmTypePointerSupplyMode val_mode){ _key.Set(k, key_mode); }
			void Set(const _map_pair& x, RvmTypePointerSupplyMode mode){ _key.Set(&x.key(), mode); ASSERT(mode != RVMPTR_TAKE); }
			void SetValue(const void* v, RvmTypePointerSupplyMode val_mode){}
			UINT GetEmbeddedSize() const { return _key.GetValueSize(); }
		};
	template<typename KEY, typename VAL>
	struct _map_pair<false, KEY, VAL, true, false>
	{	KEY		_key;
		_details::rvmtype_ptr<VAL>	_value;
		auto&	key() const { return _key; }
		auto&	val() const { return _value.SafeGet(); }
		_map_pair() = default;
		template<typename T>
		_map_pair(T& x):_value(&x.val(), RVMPTR_KEEP){ _key = x.key(); }
		void Set(const KEY* k, RvmTypePointerSupplyMode key_mode, const VAL* v, RvmTypePointerSupplyMode val_mode){ _key = *k; _value.Set(v, val_mode); }
		void Set(const _map_pair& x, RvmTypePointerSupplyMode mode){ _value.Set(&x.val(), mode); _key = x.key(); ASSERT(mode != RVMPTR_TAKE); }
		void SetValue(const VAL* v, RvmTypePointerSupplyMode val_mode){ _value.Set(v, val_mode); }
		UINT GetEmbeddedSize() const { return _value.GetValueSize() + sizeof(KEY); }
	};
	template<typename KEY, typename VAL>
	struct _map_pair<false, KEY, VAL, false, false>
	{	_details::rvmtype_ptr<KEY>	_key;
		_details::rvmtype_ptr<VAL>	_value;
		auto&	key() const { return *(VERIFY(_key.v)); }
		auto&	val() const { return _value.SafeGet(); }
		_map_pair() = default;
		template<typename T>
		_map_pair(T& x):_key(&x.key(), RVMPTR_KEEP), _value(&x.val(), RVMPTR_KEEP){}
		void Set(const KEY* k, RvmTypePointerSupplyMode key_mode, const VAL* v, RvmTypePointerSupplyMode val_mode){ _key.Set(k, key_mode); _value.Set(v, val_mode); }
		void Set(const _map_pair& x, RvmTypePointerSupplyMode mode){ _key.Set(&x.key(), mode); _value.Set(&x.val(), mode); ASSERT(mode != RVMPTR_TAKE); }
		void SetValue(const VAL* v, RvmTypePointerSupplyMode val_mode){ _value.Set(v, val_mode); }
		UINT GetEmbeddedSize() const { return _key.GetValueSize() + _value.GetValueSize(); }
	};

template<typename KEY, typename VAL>
using _mutable_pair = _map_pair<false, KEY, VAL>;

template<typename KEY, typename VAL>
struct _map_pair_ref
{
	const KEY&	_key;
	const VAL&	_val;
	auto&	key() const { return _key; }
	auto&	val() const { return _val; }
	template<typename T>
	_map_pair_ref(T& x):_key(x.key()), _val(x.val()){}
	UINT GetEmbeddedSize() const { return _details::_EmbedSize(_key) + _details::_EmbedSize(_val); }
};
	template<typename KEY>
	struct _map_pair_ref<KEY, void>: public _details::om_pair_void_value
	{
		const KEY&	_key;
		auto&	key() const { return _key; }
		template<typename T>
		_map_pair_ref(T& x):_key(x.key()){}
		UINT GetEmbeddedSize() const { return _details::_EmbedSize(_key); }
	};

template<typename MAP, typename KEY, typename VAL, typename name_prefix>
class _MapJsonify
{	auto*	This() const { return (MAP*)this; }
public:
	void	Jsonify(rt::Json& append) const
			{	auto& s = append.GetInternalString();
				s += '{';
				for(UINT i=0; i<This()->GetCount(); i++)
				{	auto& item = This()->_GetByPos(i);
					_details::_JsonDictKey(item.key(), s);
					s += ':';
					_details::_Jsonify(item.val(), s);
					s += ',';
				}
				s.EndClosure('}');
			}
	static void	GetTypeSignature(rt::String& n){ n += name_prefix::name() + rt::SS("map<"); _details::_TypeSignature<KEY>::Get(n); n += ','; _details::_TypeSignature<VAL>::Get(n); n += '>'; }
};
	template<typename MAP, typename KEY, typename name_prefix>
	class _MapJsonify<MAP, KEY, void, name_prefix>
	{	auto*	This() const { return (MAP*)this; }
	public:
		void	Jsonify(rt::Json& append) const
				{	auto& s = append.GetInternalString();
					s += '[';
					for(UINT i=0; i<This()->GetCount(); i++)
					{	_details::_Jsonify(This()->_GetByPos(i).key(), s);
						s += ',';
					}
					s.EndClosure(']');
				}
		static void	GetTypeSignature(rt::String& n){ n += name_prefix::name() + rt::SS("set<"); _details::_TypeSignature<KEY>::Get(n); n += '>'; }
	};

#pragma pack(pop)
} // namespace _details

namespace _details
{
template<typename KEY, typename KEY_MUTABLE, typename OMM>
inline bool _MapMutableRemove(OMM* t, const KEY_MUTABLE& key)
{	UINT immutable_size = KEY::GetEmbeddedSize(key);
	if(immutable_size <= 1024)
	{	auto* imm = (KEY*)_alloca(immutable_size);
		imm->Embed(key);
		return t->_Remove(*imm);
	}
	else
	{	auto* imm = RvmImmutableTypeCompose(key);
		bool ret = t->_Remove(*imm);
		RvmImmutableTypeDecompose(imm);
		return ret;
	}
}

template<typename MAP, typename KEY, typename VAL, bool is_pod_key = rt::TypeTraits<KEY>::IsPOD, bool is_pod_val = rt::TypeTraits<VAL>::IsPOD>
struct _MapMutableOp;
	template<typename MAP, typename KEY, typename VAL>
	struct _MapMutableOp<MAP, KEY, VAL, true, true>
	{	bool Set(const KEY& k, const VAL& v){ return ((MAP*)this)->_Set(&k, RVMPTR_COPY, &v, RVMPTR_COPY); }
		void Set(const _mutable_pair<KEY, VAL>* keys_sorted, UINT count, RvmTypePointerSupplyMode mode = RVMPTR_COPY){ ((MAP*)this)->_Set(keys_sorted, count, mode); }
		bool Append(const KEY& k, const VAL& v){ return ((MAP*)this)->_Append(&k, RVMPTR_COPY, &v, RVMPTR_COPY); }
		bool Remove(const KEY& k){ return ((MAP*)this)->_Remove(k); }
	};
	template<typename MAP, typename KEY, typename VAL>
	struct _MapMutableOp<MAP, KEY, VAL, false, true>
	{	typedef typename _details::_TypeTraits<KEY>::Mutable KEY_MUTABLE;
		bool Set(const KEY_MUTABLE& k, const VAL& v){ return ((MAP*)this)->_Set(RvmImmutableTypeCompose(k), RVMPTR_TAKE, &v, RVMPTR_COPY); }
		bool Append(const KEY_MUTABLE& k, const VAL& v){ return ((MAP*)this)->_Append(RvmImmutableTypeCompose(k), RVMPTR_TAKE, &v, RVMPTR_COPY); }
		bool Set(const KEY* k, RvmTypePointerSupplyMode kmode, const VAL& v){ return ((MAP*)this)->_Set(k, kmode, &v, RVMPTR_COPY); }
		void Set(const _mutable_pair<KEY, VAL>* keys_sorted, UINT count, RvmTypePointerSupplyMode mode = RVMPTR_COPY){ ((MAP*)this)->_Set(keys_sorted, count, mode); }
		bool Append(const KEY* k, RvmTypePointerSupplyMode kmode, const VAL& v){ return ((MAP*)this)->_Append(k, kmode, &v, RVMPTR_COPY); }
		bool Remove(const KEY_MUTABLE& k){ return _MapMutableRemove<KEY, KEY_MUTABLE>((MAP*)this, k); }
		bool Set(const KEY& k, const VAL& v){ return ((MAP*)this)->_Set(&k, RVMPTR_COPY, &v, RVMPTR_COPY); }
		bool Append(const KEY& k, const VAL& v){ return ((MAP*)this)->_Append(&k, RVMPTR_COPY, &v, RVMPTR_COPY); }
		bool Remove(const KEY& k){ return ((MAP*)this)->_Remove(k); }
	};
	template<typename MAP, typename KEY, typename VAL>
	struct _MapMutableOp<MAP, KEY, VAL, true, false>
	{	typedef typename _details::_TypeTraits<VAL>::Mutable VAL_MUTABLE;
		bool Set(const KEY& k, const VAL_MUTABLE& v){ return ((MAP*)this)->_Set(&k, RVMPTR_COPY, RvmImmutableTypeCompose(v), RVMPTR_TAKE); }
		void Set(const _mutable_pair<KEY, VAL>* keys_sorted, UINT count, RvmTypePointerSupplyMode mode = RVMPTR_COPY){ ((MAP*)this)->_Set(keys_sorted, count, mode); }
		bool Append(const KEY& k, const VAL_MUTABLE& v){ return ((MAP*)this)->_Append(&k, RVMPTR_COPY, RvmImmutableTypeCompose(v), RVMPTR_TAKE); }
		bool Set(const KEY& k, const VAL* v, RvmTypePointerSupplyMode vmode){ return ((MAP*)this)->_Set(&k, RVMPTR_COPY, v, vmode); }
		bool Append(const KEY& k, const VAL* v, RvmTypePointerSupplyMode vmode){ return ((MAP*)this)->_Append(&k, RVMPTR_COPY, v, vmode); }
		bool Set(const KEY& k, const VAL& v){ return ((MAP*)this)->_Set(&k, RVMPTR_COPY, &v, RVMPTR_COPY); }
		bool Append(const KEY& k, const VAL& v){ return ((MAP*)this)->_Append(&k, RVMPTR_COPY, &v, RVMPTR_COPY); }
		bool Remove(const KEY& k){ return ((MAP*)this)->_Remove(k); }
	};
	template<typename MAP, typename KEY, typename VAL>
	struct _MapMutableOp<MAP, KEY, VAL, false, false>
	{	typedef typename _details::_TypeTraits<KEY>::Mutable KEY_MUTABLE;
		typedef typename _details::_TypeTraits<VAL>::Mutable VAL_MUTABLE;
		bool Set(const KEY_MUTABLE& k, const VAL_MUTABLE& v){ return ((MAP*)this)->_Set(RvmImmutableTypeCompose(k), RVMPTR_TAKE, RvmImmutableTypeCompose(v), RVMPTR_TAKE); }
		void Set(const _mutable_pair<KEY, VAL>* keys_sorted, UINT count, RvmTypePointerSupplyMode mode = RVMPTR_COPY){ ((MAP*)this)->_Set(keys_sorted, count, mode); }
		bool Append(const KEY_MUTABLE& k, const VAL_MUTABLE& v){ return ((MAP*)this)->_Append(RvmImmutableTypeCompose(k), RVMPTR_TAKE, RvmImmutableTypeCompose(v), RVMPTR_TAKE); }
		bool Set(const KEY* k, RvmTypePointerSupplyMode kmode, const VAL* v, RvmTypePointerSupplyMode vmode){ return ((MAP*)this)->_Set(k, kmode, v, vmode); }
		bool Append(const KEY* k, RvmTypePointerSupplyMode kmode, const VAL* v, RvmTypePointerSupplyMode vmode){ return ((MAP*)this)->_Append(k, kmode, v, vmode); }
		bool Remove(const KEY_MUTABLE& k){ return _MapMutableRemove<KEY, KEY_MUTABLE>((MAP*)this, k); }
		bool Set(const KEY& k, const VAL& v){ return ((MAP*)this)->_Set(&k, RVMPTR_COPY, &v, RVMPTR_COPY); }
		bool Append(const KEY& k, const VAL& v){ return ((MAP*)this)->_Append(&k, RVMPTR_COPY, &v, RVMPTR_COPY); }
		bool Remove(const KEY& k){ return ((MAP*)this)->_Remove(k); }
	};
	template<typename MAP, typename KEY>
	struct _MapMutableOp<MAP, KEY, void, true, true>
	{	bool Insert(const KEY& k){ return ((MAP*)this)->_Set(&k, RVMPTR_COPY, nullptr, RVMPTR_KEEP); }
		bool Insert(const KEY* k, RvmTypePointerSupplyMode kmode){ return ((MAP*)this)->_Set(k, kmode, nullptr, RVMPTR_KEEP); }
		void Insert(const _mutable_pair<KEY, void>* keys_sorted, UINT count, RvmTypePointerSupplyMode mode = RVMPTR_COPY){ ((MAP*)this)->_Set(keys_sorted, count, mode); }
		void Insert(const KEY* keys_sorted, UINT count, RvmTypePointerSupplyMode mode = RVMPTR_COPY){ Insert((_mutable_pair<KEY, void>*)keys_sorted, count, mode); }
		bool Append(const KEY& k){ return ((MAP*)this)->_Append(&k, RVMPTR_COPY, nullptr, RVMPTR_KEEP); }
		bool Remove(const KEY& k){ return ((MAP*)this)->_Remove(k); }
	};
	template<typename MAP, typename KEY>
	struct _MapMutableOp<MAP, KEY, void, false, true>
	{	typedef typename _details::_TypeTraits<KEY>::Mutable KEY_MUTABLE;
		bool Insert(const KEY_MUTABLE& k){ return ((MAP*)this)->_Set(RvmImmutableTypeCompose(k), RVMPTR_TAKE, nullptr, RVMPTR_KEEP); }
		bool Append(const KEY_MUTABLE& k){ return ((MAP*)this)->_Append(RvmImmutableTypeCompose(k), RVMPTR_TAKE, nullptr, RVMPTR_KEEP); }
		bool Insert(const KEY* k, RvmTypePointerSupplyMode kmode){ return ((MAP*)this)->_Set(k, kmode, nullptr, RVMPTR_KEEP); }
		void Insert(const _mutable_pair<KEY, void>* keys_sorted, UINT count, RvmTypePointerSupplyMode mode = RVMPTR_COPY){ ((MAP*)this)->_Set(keys_sorted, count, mode); }
		bool Remove(const KEY_MUTABLE& k){ return _MapMutableRemove<KEY, KEY_MUTABLE>((MAP*)this, k); }
		bool Insert(const KEY& k){ return ((MAP*)this)->_Set(&k, RVMPTR_COPY, nullptr, RVMPTR_KEEP); }
		bool Append(const KEY& k){ return ((MAP*)this)->_Append(&k, RVMPTR_COPY, nullptr, RVMPTR_KEEP); }
		bool Remove(const KEY& k){ return ((MAP*)this)->_Remove(k); }
	};
} // namespace _details

} // namespace rvm

#define _DETAILS_MAPOP_DECL_FRIEND_TYPES													\
	template<typename MAP_, typename KEY_, typename VAL_, bool is_pod_key, bool is_val_key>	\
	friend struct _details::_MapMutableOp;													\
	template<typename MAP_, typename KEY_, typename VAL_, typename prefix>					\
	friend class _details::_MapJsonify;														\
