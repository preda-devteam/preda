#pragma once
#include "../../../SFC/core/ext/sparsehash/sparsehash.h"
#include "typetraits.h"

#pragma warning(disable: 4307) // warning C4307: '*': integral constant overflow

namespace rvm
{

namespace _details
{
static const UINT PRIME1 =  2654435761U;
static const UINT PRIME2 =  2246822519U;
static const UINT PRIME3 =  3266489917U;
static const UINT PRIME4 =   668265263U;
static const UINT PRIME5 =  0x165667b1U;
inline UINT _hash_final(UINT crc)
{	crc ^= crc >> 15;
	crc *= PRIME2;
	crc ^= crc >> 13;
	crc *= PRIME3;
	crc ^= crc >> 16;
	return crc;
}
template<typename T, typename OFF, int len = sizeof(T), bool small = !(sizeof(T)>=16), bool tiny = (sizeof(T)<=4) >
struct Hasher
{	static OFF hash(const T& key)
	{	
		const unsigned char* p = (const unsigned char*)&key;
		const unsigned char* const bEnd = p + len;
		unsigned int v1 = PRIME1;
		unsigned int v2 = v1 * PRIME2 + len;
		unsigned int v3 = v2 * PRIME3;
		unsigned int v4 = v3 * PRIME4;	
		const unsigned char* const limit = bEnd - 16;
		unsigned int crc;
		while(p<limit)
		{	v1 = _rotl(v1, 13) + (*(unsigned int*)p); p+=4;
			v2 = _rotl(v2, 11) + (*(unsigned int*)p); p+=4;
			v3 = _rotl(v3, 17) + (*(unsigned int*)p); p+=4;
			v4 = _rotl(v4, 19) + (*(unsigned int*)p); p+=4;
		} 

		p = bEnd - 16;
		v1 += _rotl(v1, 17); v2 += _rotl(v2, 19); v3 += _rotl(v3, 13); v4 += _rotl(v4, 11); 
		v1 *= PRIME1; v2 *= PRIME1; v3 *= PRIME1; v4 *= PRIME1; 
		v1 += *(unsigned int*)p; p+=4; v2 += *(unsigned int*)p; p+=4; v3 += *(unsigned int*)p; p+=4; v4 += *(unsigned int*)p;   // p+=4;
		v1 *= PRIME2; v2 *= PRIME2; v3 *= PRIME2; v4 *= PRIME2; 
		v1 += _rotl(v1, 11); v2 += _rotl(v2, 17); v3 += _rotl(v3, 19); v4 += _rotl(v4, 13); 
		v1 *= PRIME3; v2 *= PRIME3; v3 *= PRIME3; v4 *= PRIME3;

		crc = v1 + _rotl(v2, 3) + _rotl(v3, 6) + _rotl(v4, 9);
		crc ^= crc >> 11;
		crc += (PRIME4+len) * PRIME1;
		crc ^= crc >> 15;
		crc *= PRIME2;
		crc ^= crc >> 13;

		return crc;
	}
};
	template<typename T, typename OFF, int len>
	struct Hasher<T, OFF, len, true, false>
	{	static OFF hash(const T& key)
		{	const unsigned char* p = (unsigned char*)&key;
			const unsigned char* const bEnd = p + len;
			unsigned int idx = PRIME1;
			unsigned int crc = PRIME5;
			const unsigned char* const limit = bEnd - 4;
			while(p<limit)
			{	crc += ((*(unsigned int*)p) + idx++);
				crc += _rotl(crc, 17) * PRIME4;
				crc *= PRIME1;
				p+=4;
			}
			while(p<bEnd)
			{	crc += ((*p) + idx++);
				crc *= PRIME1;
				p++;
			}
			return (OFF)_hash_final(crc + len);
		}
	};
	template<typename T, typename OFF>
	struct Hasher<T, OFF, 8, true, false>
	{	static OFF hash(const T& key)
		{	const unsigned int* p = (unsigned int*)&key;
			unsigned int idx = PRIME1;
			unsigned int crc = PRIME5;
			crc += p[0] + idx++;	crc += _rotl(crc, 17) * PRIME4;		crc *= PRIME1;
			crc += p[1] + idx++;	crc += _rotl(crc, 17) * PRIME4;		crc *= PRIME1;
			return _hash_final(crc + 8);
		}
	};
	template<typename T, typename OFF, int len>
	struct Hasher<T, OFF, len, true, true>
	{	static OFF hash(const T& key)
		{	unsigned int crc = PRIME5;
			crc += (UINT)key + PRIME1;	crc += _rotl(crc, 17) * PRIME4;		crc *= PRIME1;
			return _hash_final(crc + len);
		}
	};

#pragma pack(push, 1)
template<typename KEY, typename VAL>
struct Item
{	KEY		key;
	VAL		value;
	UINT	GetSize() const { return (UINT)(rt::GetDataSize(key) + rt::GetDataSize(value)); }
	template<typename FUNC>
	void	Visit(FUNC&& v) const { return v(key, value); }
	template<typename FUNC>
	void	VisitKey(FUNC&& v) const { return v(key); }
};
template<typename KEY>
struct Item<KEY, void>
{	KEY		key;
	UINT	GetSize() const { return rt::GetDataSize(key); }
	template<typename FUNC>
	void	Visit(FUNC&& v) const { v(key); }
};
#pragma pack(pop)

template<typename KEY, typename VAL>
struct ItemOp
{	static void JsonList(const Item<KEY, VAL>* x, UINT count, rt::String& append)
	{	append += '{';
		for(UINT i=0; i<count; i++)
		{
			append += '"';	RvmTypeToString(x->key, append);				append += '"';
			append += ':';	RvmTypeJsonify(x->value, (rt::Json&)append);	append += ',';
			
			x = (const Item<KEY, VAL>*)(((LPCBYTE)x) + x->GetSize());
		}
		append.EndClosure('}');
	}
};
	template<typename KEY>
	struct ItemOp<KEY, void>
	{	static void JsonList(const Item<KEY, void>* x, UINT count, rt::String& append)
		{	append += '[';
			for(UINT i=0; i<count; i++)
			{
				RvmTypeJsonify(x[i].key, (rt::Json&)append);
				append += ',';
			}
			append.EndClosure(']');
		}
	};

template<typename KEY, typename VAL, typename OFF>
struct HashMapMutableBase;

template<typename KEY, typename VAL>
struct _HashMapSigature
{	static void Get(rt::String& n)
	{	n += rt::SS("hashmap<"); RvmTypeSignature<KEY>::Get(n); n+=','; RvmTypeSignature<VAL>::Get(n); n+='>';
	}
};
template<typename KEY>
struct _HashMapSigature<KEY, void>
{	static void Get(rt::String& n)
	{	n += rt::SS("hashset<"); RvmTypeSignature<KEY>::Get(n); n+='>';
	}
};


} // namespace _details

template<typename KEY, typename VAL = void, typename OFF = UINT, bool val_pod = rt::TypeTraits<VAL>::IsPOD>
class HashMap;

template<typename KEY, typename VAL = void, typename OFF = UINT, bool val_pod = rt::TypeTraits<VAL>::IsPOD>
class HashMapMutable;

#pragma pack(push, 1)
// POD version
template<typename KEY, typename VAL, typename OFF>
class HashMap<KEY, VAL, OFF, true>
{
	template<typename, typename, typename, bool>
	friend class HashMapMutable;
	template<typename, typename, typename>
	friend struct _details::HashMapMutableBase;

	TYPETRAITS_DECLARE_NON_POD;
	RVM_IMMUTABLE_TYPE(HashMap);
	static const OFF OFF_MAX_NUM = ((1U << (8 * sizeof(OFF) - 1)) - 1);

	static_assert(rt::TypeTraits<KEY>::IsPOD, "KEY is not POD");
	static_assert(sizeof(OFF) <= 4, "type of OFF is too large");
	
	typedef _details::Item<KEY, VAL>	ITEM;

protected:
	OFF			_KeyCount;			// # of keys
	BYTE		_HashSpaceSizeOrder;	// size of hash space = 2
	BYTE		_MapData[1];			// OFF[MapSpaceSize] + <KEY,VAL>[KeyCount]

	static UINT	_FitSpaceOrderToCount(UINT count){ return rt::Log2((count + (count>>1))*2); }
	auto*		_Items(){ return (ITEM*)&_MapData[sizeof(OFF)*((size_t)1<<_HashSpaceSizeOrder)]; }
	auto*		_Items() const { return (const ITEM*)&_MapData[sizeof(OFF)*((size_t)1<<_HashSpaceSizeOrder)]; }
	const OFF*	_OffsetTable() const { return (const OFF*)_MapData; }
	UINT		_Hash(const KEY& k) const { return _details::Hasher<KEY, OFF>::hash(k)&(((size_t)1<<_HashSpaceSizeOrder)-1); }
	const VAL*	_ScanCollision(const KEY& k, const ITEM* begin, const ITEM* end) const
				{	for(; begin < end; begin++)if(begin->key == k)return (const VAL*)((&begin->key) + 1);
					return nullptr;
				}

public:
	HashMap(decltype(0) x){ ASSERT(x==0); _KeyCount = 0; }
	UINT		GetCount() const { return _KeyCount; }
	bool		IsEmpty() const { return _KeyCount == 0; }

	VAL*		Get(const KEY& k)
				{	if(_KeyCount == 0)return nullptr;
					auto idx = _Hash(k);
					auto* items = _Items();
					if(idx){ return (VAL*)_ScanCollision(k, items + _OffsetTable()[idx-1], items + _OffsetTable()[idx]); }
					else return (VAL*)_ScanCollision(k, items, items + _OffsetTable()[0]);
				}
	const VAL*	Get(const KEY& k) const { return rt::_CastToNonconst(this)->Get(k); }
	bool		Has(const KEY& k) const { return Get(k); }
	void		Jsonify(rt::Json& append) const { _details::ItemOp<KEY, VAL>::JsonList(_Items(), _KeyCount, append.GetInternalString()); }
	UINT		GetEmbeddedSize() const { return sizeof(_KeyCount) + (_KeyCount?(sizeof(OFF)*((size_t)1<<_HashSpaceSizeOrder) + sizeof(ITEM)*_KeyCount + sizeof(_HashSpaceSizeOrder)):0); }

	template<typename HashMapMutable>
	static UINT	GetEmbeddedSize(const HashMapMutable& c)
				{	if(!c.GetCount())return sizeof(_KeyCount);
					UINT order = _FitSpaceOrderToCount(c.GetCount());
					return sizeof(_HashSpaceSizeOrder) + sizeof(_KeyCount) + sizeof(OFF)*((size_t)1<<order) + sizeof(ITEM)*c.GetCount();
				}
	template<typename HashMapMutable>
	static bool	IsEmbeddable(const HashMapMutable& c){	return c.GetCount() <= OFF_MAX_NUM; }
	template<typename HashMapMutable>
	UINT		Embed(const HashMapMutable& c)
				{	if(!c.GetCount()){ _KeyCount = 0; return GetEmbeddedSize(); }
					_HashSpaceSizeOrder = _FitSpaceOrderToCount(c.GetCount());
					UINT space_size = 1<<_HashSpaceSizeOrder;
					_KeyCount = c.GetCount();
					thread_local rt::BufferEx<UINT> offset_slot;	// slot position of each item
					thread_local rt::BufferEx<UINT> collision;		// collision count of each slot
					offset_slot.SetSize(c.GetCount());
					collision.SetSize(space_size);
					collision.Zero();
					auto* p_offset_slot = offset_slot.Begin();
					auto* p_collision = collision.Begin();
					// collect collisions
					UINT i=0;
					c.ForEachKey([p_collision, &i, p_offset_slot, this](const KEY& k){
						p_collision[p_offset_slot[i++] = _Hash(k)]++;
					});
					ASSERT(i == _KeyCount);
					// build offset table
					auto* offset = rt::_CastToNonconst(_OffsetTable());
					rt::Zero(offset, sizeof(OFF)*collision.GetSize());
					offset[0] = collision[0];
					for(i=1; i<space_size; i++)
						offset[i] = collision[i] + offset[i-1];
					// copy items
					i=0;		ASSERT(offset[space_size - 1] == _KeyCount);
					auto* items = _Items();
					c.ForEachKey([p_collision, &i, items, offset](const KEY& it){
						UINT slot_idx = offset_slot[i++];
						rt::Copy(items[offset[slot_idx] - p_collision[slot_idx]], (const ITEM&)it);
						p_collision[slot_idx]--;
					});
					return GetEmbeddedSize();
				}
	template<typename FUNC>
	void		ForEach(FUNC&& v) const
				{	auto* items = _Items();
					for(OFF i=0; i<_KeyCount; i++)
						items[i].Visit(v);
				}
	template<typename FUNC>
	void		ForEachKey(FUNC&& v) const
				{	auto* items = _Items();
					for(OFF i=0; i<_KeyCount; i++)
						items[i].VisitKey(v);
				}	static auto& Zero(){ static const HashMap _zero(0); return _zero; }
	static void GetTypeSignature(rt::String& n){ _details::_HashMapSigature<KEY, VAL>::Get(n); }
};
#pragma pack(pop)


namespace _details
{
template<typename KEY, typename VAL, typename OFF>
struct HashMapMutableBase
{
	TYPETRAITS_DECLARE_NON_POD;
	static_assert(rt::TypeTraits<KEY>::IsPOD, "KEY is not POD");
	static_assert(sizeof(OFF) <= 4, "type of OFF is too large");
	typedef const HashMap<KEY, VAL, OFF> ImmutableMap;
	ImmutableMap*		_pBase;
	rt::BooleanArray<>	_Written;
	UINT				_BaseCount;
	HashMapMutableBase(){ _pBase = nullptr; _BaseCount = 0; }
	UINT _ItemIndex(const VAL* p) const { ASSERT(_pBase); return (UINT)(((typename ImmutableMap::ITEM*)(((LPCBYTE)p) - sizeof(KEY))) - _pBase->_Items()); }
	void _SetBase(const ImmutableMap& x)
	{	_pBase = &x; 
		_BaseCount = x.GetCount();
		_Written.SetBitSize(x.GetCount(), false);
		_Written.ResetAll();
	}
	void _SetWritten(const KEY& k)
	{	if(!_pBase)return;
		auto* item = _pBase->Get(k);
		if(item && !_Written.Set(_ItemIndex(item)))
			_BaseCount--;
	}
	template<typename FUNC>
	void _ForEach(FUNC&& v) const
	{	if(!_pBase)return;
		auto* p = _pBase->_Items();
		auto* end = p + _pBase->GetCount();
		rt::BooleanArray<>::Index b = 0; 
		for(; p<end; b++, p++)
			if(!_Written.Get(b))p->Visit(v);
	}
	template<typename FUNC>
	void _ForEachKey(FUNC&& v) const
	{	if(!_pBase)return;
		auto* p = _pBase->_Items();
		auto* end = p + _pBase->GetCount();
		rt::BooleanArray<>::Index b = 0; 
		for(; p<end; b++, p++)
			if(!_Written.Get(b))p->VisitKey(v);
	}
	auto _GetByPos(const KEY& k) const -> const VAL*
	{	if(!_pBase)return nullptr;
		auto* item = _pBase->Get(k);
		if(item && !_Written.Get(_ItemIndex(item)))
			return item;
		return nullptr;
	}
};
} // namespace _details

template<typename KEY, typename VAL, typename OFF>
class HashMapMutable<KEY, VAL, OFF, true>
					: protected ext::fast_map<KEY, VAL>
					, protected _details::HashMapMutableBase<KEY, VAL, OFF>
{   typedef _details::HashMapMutableBase<KEY, VAL, OFF> _SC;
    typedef ext::fast_map<KEY, VAL> _FM;
public:
    typedef const HashMap<KEY, VAL, OFF> ImmutableMap;
	HashMapMutable() = default;
	HashMapMutable(const ImmutableMap& x){ _SC::_SetBase(x); }
	UINT			GetCount() const { return (UINT)_FM::size() + _SC::_BaseCount; }
	bool			IsEmpty() const { return _FM::size() == 0 && _SC::_BaseCount == 0; }

	auto*			Get(const KEY& k) const
					{	auto it = _FM::find(k);
						if(it != _FM::end())return &it->second;
						return _SC::_GetByPos(k);
					}
	bool			Has(const KEY& k) const { return Get(k); }
	void			Set(const KEY& k, const VAL& x)
					{	_FM::operator [](k) = x;
                        _SC::_SetWritten(k);
					}
	void			Remove(const KEY& k)
					{	_FM::erase(k);
                        _SC::_SetWritten(k);
					}
	template<typename FUNC>
	void			ForEach(FUNC&& v) const
					{	for(auto it = _FM::begin(); it != _FM::end(); it++)
							v(it->first, it->second);
                        _SC::_ForEach(v);
					}
	template<typename FUNC>
	void			ForEachKey(FUNC&& v) const
					{	for(auto it = _FM::begin(); it != _FM::end(); it++)
							v(it->first);
                        _SC::_ForEachKey(v);
					}
};
	template<typename KEY, typename OFF>
	class HashMapMutable<KEY, void, OFF>
					: protected ext::fast_set<KEY>
					, protected _details::HashMapMutableBase<KEY, void, OFF>
    {
        typedef _details::HashMapMutableBase<KEY, void, OFF> _SC;
        typedef ext::fast_set<KEY> _FM;
	public:
		typedef const HashMap<KEY, void, OFF> ImmutableMap;
		HashMapMutable() = default;
		HashMapMutable(const ImmutableMap& x){ _SC::_SetBase(x); }
		UINT			GetCount() const { return (UINT)_FM::size() + _SC::_BaseCount; }
		bool			IsEmpty() const { return _FM::size() == 0 && _SC::_BaseCount == 0; }
		bool			Has(const KEY& k) const
						{	auto it = _FM::find(k);
							if(it != _FM::end())return true;
							return _SC::_GetByPos(k);
						}
		void			Set(const KEY& k)
						{	if(_SC::_pBase && _SC::_pBase->Has(k))return;
                            _FM::insert(k);
						}
		void			Remove(const KEY& k)
						{	_FM::erase(k);
                            _SC::_SetWritten(k);
						}
		template<typename FUNC>
		void			ForEach(FUNC&& v) const
						{	for(auto it = _FM::begin(); it != _FM::end(); it++)
								v(*it);
                            _SC::_ForEach(v);
						}
		template<typename FUNC>
		void			ForEachKey(FUNC&& v) const { ForEach(v); }
	};

#pragma pack(push, 1)
// non-POD version
template<typename KEY, typename VAL, typename T_OFF>
class HashMap<KEY, VAL, T_OFF, false>
{
	template<typename, typename, typename, bool>
	friend class HashMapMutable;
	template<typename, typename, typename>
	friend struct _details::HashMapMutableBase;

	TYPETRAITS_DECLARE_NON_POD;
	RVM_IMMUTABLE_TYPE(HashMap);
	static const T_OFF OFF_MAX_NUM = ((1U << (8 * sizeof(T_OFF) - 1)) - 1);
	static_assert(TypeTraits<VAL>::IsImmutable, "VAL must be Immutable type");
	static_assert(rt::TypeTraits<KEY>::IsPOD, "KEY is not POD");
	static_assert(sizeof(T_OFF) <= 4, "type of OFF is too large");
	
	typedef _details::Item<KEY, VAL>	ITEM;
	typedef T_OFF	OFF;

	struct Entry
	{	OFF			Offset;
		BYTE		Collision;	// # of Collisions
	};

protected:
	OFF				KeyCount;			// # of keys
	OFF				TotalItemSize;		// sizeof(<KEY,VAL>[KeyCount])
	BYTE			HashSpaceSizeOrder;	// size of hash space = 2
	BYTE			MapData[1];			// <OFF,BYTE>[MapSpaceSize] + <KEY,VAL>[KeyCount]

	static UINT		_FitSpaceOrderToCount(UINT count){ return rt::Log2((count + (count>>1))*2); }
	auto*			_Item(OFF offset){ return (ITEM*)&MapData[sizeof(Entry)*((size_t)1<<HashSpaceSizeOrder) + offset]; }
	auto*			_Item(OFF offset) const { return rt::_CastToNonconst(this)->_Item(offset); }
	static auto*	_ItemNext(const ITEM* p){ return (const ITEM*)(((LPCBYTE)p) + p->GetSize()); }
	const Entry&	_GetMap(UINT h) const { return *(((const Entry*)MapData) + h); }
	UINT			_Hash(const KEY& k) const { return _details::Hasher<KEY, OFF>::hash(k)&(((size_t)1<<HashSpaceSizeOrder)-1); }
	const VAL*		_ScanCollision(const KEY& k, const ITEM* begin, UINT count) const
					{	for(UINT i=0; i < count; i++, begin = _ItemNext(begin))
							if(begin->key == k)return (const VAL*)((&begin->key) + 1);
						return nullptr;
					}
public:
	HashMap(decltype(0) x){ ASSERT(x==0); KeyCount = 0; }
	UINT			GetCount() const { return KeyCount; }
	bool			IsEmpty() const { return KeyCount == 0; }
	VAL*			Get(const KEY& k)
					{	if(KeyCount == 0)return nullptr;
						auto& e = _GetMap(_Hash(k));
						return (VAL*)_ScanCollision(k, _Item(e.Offset), e.Collision);
					}
	const VAL*		Get(const KEY& k) const { return rt::_CastToNonconst(this)->Get(k); }
	bool			Has(const KEY& k) const { return Get(k); }
	void			Jsonify(rt::Json& append) const { _details::ItemOp<KEY, VAL>::JsonList(_Item(0), KeyCount, append.GetInternalString()); }
	UINT			GetEmbeddedSize() const { return sizeof(KeyCount) + (KeyCount?(sizeof(Entry)*((size_t)1<<HashSpaceSizeOrder) + TotalItemSize + sizeof(TotalItemSize) + sizeof(HashSpaceSizeOrder)):0); }

	auto&			GetItemByReference(OFF refer) const { return *(const _details::Item<KEY, VAL>*)(((LPCBYTE)this) + refer); }
	OFF				GetReferenceByKey(const KEY& k) const // 0 for not found
					{	auto* v = Get(k);
						if(v)return GetReferenceByValue(*v);
						return 0;
					}
	OFF				GetReferenceByValue(const VAL& v) const // v should be obtained from Get() or ForEach([]())
					{	return (OFF)((LPCBYTE)&v - sizeof(KEY) - (LPCBYTE)this);
					}
	
	template<typename FUNC>
	void			ForEach(FUNC&& v) const
					{	const auto* item = _Item(0);
						for(UINT i=0; i<KeyCount; i++, item = _ItemNext(item))
							item->Visit(v);
					}
	template<typename FUNC>
	void			ForEachKey(FUNC&& v) const
					{	const auto* item = _Item(0);
						for(UINT i=0; i<KeyCount; i++, item = _ItemNext(item))
							item->VisitKey(v);
					}
	template<typename HashMapMutable>
	static UINT		GetEmbeddedSize(const HashMapMutable& c)
					{	if(!c.GetCount())return sizeof(KeyCount);
						UINT order = _FitSpaceOrderToCount(c.GetCount());
						return sizeof(HashSpaceSizeOrder) + sizeof(KeyCount) + sizeof(TotalItemSize) + sizeof(Entry)*((size_t)1<<order) + c._TotalItemSize;
					}
	template<typename HashMapMutable>
	static bool		IsEmbeddable(const HashMapMutable& c) { return c._TotalItemSize <= OFF_MAX_NUM; }
	template<typename HashMapMutable>
	UINT			Embed(const HashMapMutable& c)
					{	if(!c.GetCount()){ KeyCount = 0; return GetEmbeddedSize(); }
						HashSpaceSizeOrder = _FitSpaceOrderToCount(c.GetCount());
						TotalItemSize = c._TotalItemSize;
						UINT space_size = 1<<HashSpaceSizeOrder;
						KeyCount = c.GetCount();
						thread_local rt::BufferEx<UINT> offset_slot;	// slot position of each item
						thread_local rt::BufferEx<UINT> collision;		// collision count of each slot
						offset_slot.SetSize(c.GetCount());
						collision.SetSize(space_size);
						collision.Zero();
						auto* p_offset_slot = offset_slot.Begin();
						auto* p_collision = collision.Begin();
						// collect collisions
						UINT i=0;
						c.ForEach([p_collision, &i, p_offset_slot, this](const KEY& k, const VAL& v){
							p_collision[p_offset_slot[i++] = _Hash(k)] += sizeof(k) + v.GetEmbeddedSize();
						});
						ASSERT(i == KeyCount);
						// build offset table
						auto* offset = (Entry*)MapData;
						rt::Zero(offset, sizeof(Entry)*collision.GetSize());
						offset[0].Offset = 0;
						for(i=1; i<space_size; i++)
							offset[i].Offset = collision[i-1] + offset[i-1].Offset;
						// copy items
						i=0;
						auto* item_buf = (LPBYTE)_Item(0);
						c.ForEach([p_collision, &i, item_buf, offset](const KEY& k, const VAL& v){
							UINT slot_idx = offset_slot[i++];
							UINT size = sizeof(k) + v.GetEmbeddedSize();
							p_collision[slot_idx]-=size;
							offset[slot_idx].Collision++;
							// copy item
							LPBYTE p = &item_buf[offset[slot_idx].Offset + p_collision[slot_idx]];
							rt::Copy<sizeof(KEY)>(p, &k);
							memcpy(p + sizeof(KEY), &v, v.GetEmbeddedSize());
						});
						return GetEmbeddedSize();
					}
	static auto&	ZeroValue(){ static const HashMap _zero(0); return _zero; }
	static void		GetTypeSignature(rt::String& n){ n += rt::SS("hashmap<"); RvmTypeSignature<KEY>::Get(n); n+=','; RvmTypeSignature<VAL>::Get(n); n+='>'; }
};
#pragma pack(pop)

template<typename KEY, typename VAL, typename OFF>
class HashMapMutable<KEY, VAL, OFF, false>
					: protected ext::fast_map<KEY, _details::rvmtype_ptr<VAL>>
{   typedef ext::fast_map<KEY, _details::rvmtype_ptr<VAL>> _SC;
	TYPETRAITS_DECLARE_NON_POD;
	static_assert(TypeTraits<VAL>::IsImmutable, "VAL should be Immutable type");
	static_assert(rt::TypeTraits<KEY>::IsPOD, "KEY is not POD");
	static_assert(sizeof(OFF) <= 4, "type of OFF is too large");
	typedef const HashMap<KEY, VAL, OFF> ImmutableMap;
	typedef _details::rvmtype_ptr<VAL>	rvmtype_ptr;
	const ImmutableMap*	_pBase;
	rt::BooleanArray<>	_Written;
	rt::BufferEx<OFF>	_HashEntryItemIndex;
	UINT				_BaseCount;
	UINT				_TotalItemSize;

	const VAL* _BaseGet(const KEY& k) const
	{	if(!_pBase)return nullptr;
		OFF hash = _pBase->_Hash(k);
		auto& e = _pBase->_GetMap(hash);
		if(!e.Collision)return nullptr;
		const auto* p = _pBase->_Item(e.Offset);
		for(UINT i=0; i < e.Collision; i++, p = ImmutableMap::_ItemNext(p))
			if(p->key == k)
			{	if(!_Written.Get(_HashEntryItemIndex[hash] + i))
					return &p->value;
				break;
			}
		return nullptr;
	}
	UINT _SetWritten(const KEY& k) // size of the item written
	{	if(!_pBase)return 0;
		OFF hash = _pBase->_Hash(k);
		auto& e = _pBase->_GetMap(hash);
		if(!e.Collision)return 0;
		const auto* p = _pBase->_Item(e.Offset);
		for(UINT i=0; i < e.Collision; i++, p = ImmutableMap::_ItemNext(p))
			if(p->key == k)
			{	if(!_Written.Set(_HashEntryItemIndex[hash] + i))
				{	_BaseCount--;
					return p->GetSize();
				}
				break;
			}
		return 0;
	}
public:
	HashMapMutable() { _pBase = nullptr; _BaseCount = 0; _TotalItemSize = 0;}
	HashMapMutable(const ImmutableMap& x)
				{	if(x.GetCount() == 0){ _pBase = nullptr; _BaseCount = 0; return; }
					_pBase = &x; 
					_BaseCount = x.GetCount();
					_Written.SetBitSize(x.GetCount(), false);
					_Written.ResetAll();
					_TotalItemSize = x.TotalItemSize;
					// build ItemIndex table
					UINT hashspace_size = 1<<x.HashSpaceSizeOrder;
					_HashEntryItemIndex.SetSize(hashspace_size);
					auto* entries = &x._GetMap(0);
					_HashEntryItemIndex[0] = 0;
					for(UINT i=1; i<hashspace_size; i++)
						_HashEntryItemIndex[i] = _HashEntryItemIndex[i-1] + entries[i-1].Collision;
				}
	UINT		GetCount() const { return (UINT)_SC::size() + _BaseCount; }
	bool		IsEmpty() const { return _SC::size() == 0 && _BaseCount == 0; }
	const VAL*	Get(const KEY& k) const
				{	auto it = _SC::find(k);
					if(it != _SC::end())return it->second;
					return _BaseGet(k);
				}
	bool		Has(const KEY& k) const { return Get(k); }
	void		Set(const KEY& k, const VAL& x){ Set(k, (VAL*)&x, RVMPTR_COPY); }
	void		Set(const KEY& k, VAL* x, RvmTypePointerSupplyMode mode = RVMPTR_KEEP)
				{	_TotalItemSize += x->GetEmbeddedSize() + sizeof(k);
					rvmtype_ptr* val;
					auto it = _SC::find(k);
					if(it != _SC::end())
					{	_TotalItemSize -= it->second->GetEmbeddedSize() + sizeof(k);
						val = &(it->second);
					}
					else
					{	_TotalItemSize -= _SetWritten(k);
						val = &_SC::operator [](k);
					}
					val->Set(x, mode);
				}
	void		Remove(const KEY& k)
				{	auto it = _SC::find(k);
					if(it != _SC::end())
					{	_TotalItemSize -= it->second->GetEmbeddedSize() + sizeof(k);
                        _SC::erase(it);
					}
					else
						_TotalItemSize -= _SetWritten(k);
				}
	bool		ModifyKey(const KEY& k, const KEY& new_k)
				{	if(k == new_k)return true;
					auto it = _SC::find(k);
					if(it != _SC::end())
					{	auto* p = it->second.v;
						auto owned = it->second.owned;
						it->second.Detach();
                        _SC::erase(it);
						Remove(new_k);
						auto& v = _SC::operator [](new_k);
						v.v = p; v.owned = owned;
						return true;
					}
					auto* p = _BaseGet(k);
					if(p)
					{
						Remove(new_k);
						auto& v = _SC::operator [](new_k);
						v.v = (VAL*)p; v.owned = false;
						_SetWritten(k);
						return true;
					}
					return false;
				}
	template<typename FUNC>
	void		ForEach(FUNC&& v) const
				{	for(auto it = _SC::begin(); it != _SC::end(); it++)
						v(it->first, *it->second);
					if(_pBase)
					{	const typename ImmutableMap::ITEM* p = _pBase->_Item(0);
						auto* end = (const typename ImmutableMap::ITEM*)(((LPCBYTE)p) + _pBase->TotalItemSize);
						rt::BooleanArray<>::Index b = 0; 
						for(; p<end; b++, p = ImmutableMap::_ItemNext(p))
							if(!_Written.Get(b))p->Visit(v);
					}
				}
	template<typename FUNC>
	void		ForEachKey(FUNC&& v) const
				{	for(auto it = _SC::begin(); it != _SC::end(); it++)
						v(it->first);
					if(_pBase)
					{	const typename ImmutableMap::ITEM* p = _pBase->_Item(0);
						auto* end = (const typename ImmutableMap::ITEM*)(((LPCBYTE)p) + _pBase->TotalItemSize);
						rt::BooleanArray<>::Index b = 0; 
						for(; p<end; b++, p = ImmutableMap::_ItemNext(p))
							if(!_Written.Get(b))p->VisitKey(v);
					}
				}
};

template<typename KEY, typename OFF = UINT>
using HashSet = HashMap<KEY,void,OFF>;

template<typename KEY, typename OFF = UINT>
using HashSetMutable = HashMapMutable<KEY,void,OFF>;

} // namespace rvm

RVM_TYPETRAITS_GENERIC_DEF(
	MARCO_CONCAT(typename KEY, typename VAL, typename OFF, bool is_pod),
	MARCO_CONCAT(HashMap<KEY,VAL,OFF,is_pod>),
	MARCO_CONCAT(HashMapMutable<KEY,VAL,OFF,is_pod>)
)
