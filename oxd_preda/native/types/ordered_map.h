#pragma once
#include "map_details.h"

namespace rvm
{

///////////////////////////////////////////////////////////////////////
// Ordered Map of POD/non-POD => POD/non-POD
template<typename KEY, typename VAL, typename OFF = UINT, bool is_pod = rt::TypeTraits<KEY>::IsPOD && rt::TypeTraits<VAL>::IsPOD>
class OrderedMap;
template<typename KEY, typename VAL, typename OFF = UINT, bool is_pod = rt::TypeTraits<KEY>::IsPOD && rt::TypeTraits<VAL>::IsPOD>
class OrderedMapMutable;

#define _DETAILS_ORDEREDMAPOP_DECL_FRIEND_TYPES					\
		_DETAILS_MAPOP_DECL_FRIEND_TYPES						\
		template<typename MAP_, typename KEY_, typename VAL_>	\
		friend class _details::OrderedMapOp;					\

namespace _details
{
#pragma pack(push, 1)

struct ordered_map_prefix
{	static const rt::String_Ref& name(){ return rt::String_Ref::EmptyString(); }
};

template<typename ORDERED_MAP, typename KEY, typename VAL>
class OrderedMapOp: public _MapJsonify<ORDERED_MAP, KEY, VAL, ordered_map_prefix>
{	auto*	This() const { return (ORDERED_MAP*)this; }
public:
	template<typename RET_MATCH, typename RET_MISMATCH>
	auto	_BinarySearchKey(const KEY& x, RET_MATCH&& hit_func, RET_MISMATCH&& mis_func) const
			{	UINT f = 0, l = This()->GetCount() - 1;
				while(l - f > 1)
				{	UINT mid = (f + l)/2;
					auto& v = This()->_GetByPos(mid).key();
					if(v < x){ f = mid+1; }
					else if(x < v){ l = mid-1; }
					else return hit_func(mid); // can be any matched one
				}
				return mis_func(f, l);
			}
	int		FindKey(const KEY& x) const 
			{	if(This()->GetCount() <= 16)
				{	for(UINT i=0; i<This()->GetCount(); i++)
						if(This()->_GetByPos(i).key() == x)return i;
					return -1;
				}
				return _BinarySearchKey(x, 
							[](UINT mid) -> int { return mid; },
							[&x, this](UINT f, UINT l) -> int {
								if(This()->_GetByPos(f).key() == x)return f;
								if(f == l || !(This()->_GetByPos(l).key() == x))return -1;
								return l;
						   }
					   );	
			}
	auto&	GetByPos(UINT i) const { return This()->_GetByPos(i); }
	auto	Get(const KEY& k) const -> const VAL*
			{	int i = FindKey(k);
				if(i<0)return nullptr;
				return &This()->_GetByPos(i).val();
			}
	bool	Has(const KEY& k) const { return FindKey(k) >=0; }
	int		LowerBoundKey(const KEY& x) const // [0, GetCount()]
			{	if(This()->GetCount() <= 16)
				{	for(int i=This()->GetCount()-1; i>=0; i--)
						if(This()->_GetByPos(i).key() < x)return i+1;
					return 0;
				}
				return _BinarySearchKey(x, 
							[](UINT mid) -> int { return mid; },
							[&x, this](UINT f, UINT l) -> int {
								if(f == l)return This()->_GetByPos(f).key() < x?f+1:f;
								if(x <= This()->_GetByPos(f).key())return f;
								if(This()->_GetByPos(l).key() < x)return l + 1;
								return l;
						   }
					   );
			}
};
#pragma pack(pop)
} // namespace _details

#pragma pack(push, 1)
template<typename KEY, typename VAL, typename OFF>
class OrderedMap<KEY, VAL, OFF, true>: public _details::OrderedMapOp<OrderedMap<KEY, VAL, OFF, true>, KEY, VAL>
{
	_DETAILS_ORDEREDMAPOP_DECL_FRIEND_TYPES;
	static_assert(sizeof(OFF) <= 4, "type of OFF is too large");
	static const OFF OFF_MAX_NUM = ((1U << (8 * sizeof(OFF) - 1)) - 1);
	template<typename KEY_, typename VAL_, typename OFF_, bool is_pod>
	friend class OrderedMapMutable;
	TYPETRAITS_DECLARE_NON_POD;
	RVM_IMMUTABLE_TYPE(OrderedMap)
protected:
	typedef _details::_map_pair<true, KEY, VAL>	ITEM;
	OFF				Count;			// # of keys
	ITEM			Items[1];
	const ITEM&		_GetByPos(UINT i) const { ASSERT(i<Count); return Items[i]; }
	OFF				_ItemTotalSize() const { return Count*sizeof(ITEM); }

public:
	UINT			GetCount() const { return Count; }
	bool			IsEmpty() const { return Count == 0; }
	UINT			GetEmbeddedSize() const { return sizeof(ITEM)*Count + sizeof(Count); }

	template<typename OrderedMapMutable>
	static UINT		GetEmbeddedSize(const OrderedMapMutable& c){ return sizeof(ITEM)*c.GetCount() + sizeof(Count); }
	template<typename OrderedMapMutable>
	static bool		IsEmbeddable(const OrderedMapMutable& c){ return c._TotalItemSize <= OFF_MAX_NUM; }
	template<typename ArrayMutable>
	UINT			Embed(const ArrayMutable& c)
					{	Count = c.GetCount();
						for(UINT i=0; i<Count; i++)
							Items[i].Embed(c._GetByPos(i));
						return GetEmbeddedSize();
					}
};

template<typename KEY, typename VAL, typename OFF>
class OrderedMap<KEY, VAL, OFF, false>: public _details::OrderedMapOp<OrderedMap<KEY, VAL, OFF, false>, KEY, VAL>
{
	_DETAILS_ORDEREDMAPOP_DECL_FRIEND_TYPES;
	static_assert(sizeof(OFF) <= 4, "type of OFF is too large");
	static_assert(rt::TypeTraits<KEY>::IsPOD || TypeTraits<KEY>::IsImmutable, "KEY must be Immutable type");
	static_assert(rt::TypeTraits<VAL>::IsPOD || TypeTraits<VAL>::IsImmutable, "VAL must be Immutable type");
	static const OFF OFF_MAX_NUM = ((1U << (8 * sizeof(OFF) - 1)) - 1);
	template<typename KEY_, typename VAL_, typename OFF_, bool is_pod>
	friend class OrderedMapMutable;
	typedef _details::OrderedMapOp<OrderedMap<KEY, VAL, OFF, false>, KEY, VAL> _SC;
	TYPETRAITS_DECLARE_NON_POD;
	RVM_IMMUTABLE_TYPE(OrderedMap)
protected:
	typedef _details::_map_pair<true, KEY, VAL>	ITEM;
	OFF				Count;			// # of keys
	BYTE			Data[1];		// OFF[Count] + <ITEM>[Count]

	LPCBYTE			_Items() const { return &Data[sizeof(OFF)*Count]; }

	const OFF*		_OffsetTable() const { return (const OFF*)Data; }
	const ITEM&		_GetByPos(UINT i) const 
					{	ASSERT(i<Count);
						if(i>0){ auto off = _OffsetTable()[i-1]; return *(ITEM*)&_Items()[off]; }
						return *(ITEM*)_Items();
					}
	OFF				_ItemTotalSize() const { return Count?_OffsetTable()[Count-1]:0; }

public:
	UINT			GetCount() const { return Count; }
	const VAL*		Get(const KEY& k) const
					{	if(((LPCBYTE)&k) >= _Items() && ((LPCBYTE)&k) < _Items() + _ItemTotalSize())
							return &((ITEM&)k).val();
						int i = _SC::FindKey(k);
						if(i<0)return nullptr;
						return &_GetByPos(i).val();
					}
	bool			IsEmpty() const { return Count == 0; }
	UINT			GetEmbeddedSize() const { return sizeof(OFF)*(1 + Count) + _ItemTotalSize(); }
	template<typename OrderedMapMutable>
	static UINT		GetEmbeddedSize(const OrderedMapMutable& c){ return sizeof(OFF)*(1 + c.GetCount()) + c._ItemTotalSize(); }
	template<typename OrderedMapMutable>
	static bool		IsEmbeddable(const OrderedMapMutable& c) { return c._TotalItemSize <= OFF_MAX_NUM; }
	template<typename ArrayMutable>
	UINT			Embed(const ArrayMutable& c)
					{	Count = c.GetCount();
						OFF ItemTotalSize = 0;
						auto* table = rt::_CastToNonconst(_OffsetTable());
						auto* items = rt::_CastToNonconst(_Items());
						for(UINT i=0; i<Count; i++)
						{	ItemTotalSize += (OFF)((ITEM*)&items[ItemTotalSize])->Embed(c._GetByPos(i));
							table[i] = ItemTotalSize;
						}
						ASSERT(ItemTotalSize == c._ItemTotalSize());
						return GetEmbeddedSize();
					}
};
#pragma pack(pop)

template<typename KEY, typename VAL, typename OFF, bool is_pod>
class OrderedMapMutable: public _details::OrderedMapOp<OrderedMapMutable<KEY, VAL, OFF, is_pod>, KEY, VAL>
					   , public _details::_MapMutableOp<OrderedMapMutable<KEY, VAL, OFF, is_pod>, KEY, VAL>
{
	static_assert(rt::TypeTraits<KEY>::IsPOD || TypeTraits<KEY>::IsImmutable, "KEY should be Immutable type");
	static_assert(rt::TypeTraits<VAL>::IsPOD || TypeTraits<VAL>::IsImmutable, "VAL should be Immutable type");
	_DETAILS_ORDEREDMAPOP_DECL_FRIEND_TYPES;
	template<typename KEY_, typename VAL_, typename OFF_, bool is_pod_>
	friend class OrderedMap;
	template<typename KEY_, typename KEY_MUTABLE, typename OMM>
	friend bool _details::_MapMutableRemove(OMM* t, const KEY_MUTABLE& key);

	TYPETRAITS_DECLARE_NON_POD;
	typedef _details::OrderedMapOp<OrderedMapMutable<KEY, VAL, OFF, is_pod>, KEY, VAL> _SC;
protected:
	typedef const OrderedMap<KEY, VAL, OFF, is_pod> ImmutableMap;
	typedef _details::_map_pair<false, KEY, VAL>	ITEM;
	const ImmutableMap*	_pBase;
	UINT				_BaseCount;
	UINT				_TotalItemSize;
	rt::BufferEx<ITEM>	_NewItems;

	void			_Unbase(){ _pBase = nullptr; _BaseCount = 0; }
	void			_ImportBase(UINT append_count = 0)
					{	if(_BaseCount)
						{	UINT total_size = _BaseCount + (UINT)_NewItems.GetSize();
							_NewItems.ChangeSize(total_size + append_count);
							memmove(&_NewItems[_BaseCount], &_NewItems[0], sizeof(ITEM)*(total_size - _BaseCount));
							for(UINT i=0; i<_BaseCount; i++)
								new (&_NewItems[i]) ITEM(_pBase->_GetByPos(i));
							_Unbase();
						}
					}
	auto			_GetByPos(UINT i) const 
					{	if(i>=_BaseCount)return _details::_map_pair_ref<KEY, VAL>(_NewItems[i-_BaseCount]);
						return _details::_map_pair_ref<KEY, VAL>(_pBase->_GetByPos(i));
					}
	UINT			_ItemTotalSize() const { return _TotalItemSize; }
	bool			_Set(const KEY* k, RvmTypePointerSupplyMode key_mode, const VAL* v, RvmTypePointerSupplyMode val_mode) // return if key is new
					{	int i = _SC::LowerBoundKey(*k);
						if(i == GetCount())
						{	// new 
							auto& item = _NewItems.push_back();
							item.Set(k, key_mode, v, val_mode);
							_TotalItemSize += item.GetEmbeddedSize();
							return true;
						}
						else
						{	if(i < (int)_BaseCount)_ImportBase();
							auto& item = _NewItems[i - _BaseCount];
							if(item.key() == *k)
							{	
								_TotalItemSize -= item.GetEmbeddedSize();
								item.SetValue(v, val_mode);
								_TotalItemSize += item.GetEmbeddedSize();
								return false;
							}
							else
							{	auto& item = _NewItems.insert(i);
								item.Set(k, key_mode, v, val_mode);
								_TotalItemSize += item.GetEmbeddedSize();
								return true;
							}
						}
					}
	void			_Set(const ITEM* keys_sorted, UINT count, RvmTypePointerSupplyMode mode)
					{	if(count == 0)return;
						int i = _SC::LowerBoundKey(keys_sorted[0].key());
						if(i == GetCount())
						{	// new 
							auto* items = _NewItems.push_back_n(count);
							for(UINT i=0; i<count; i++)
							{	items[i].Set(keys_sorted[i], mode);
								_TotalItemSize += items[i].GetEmbeddedSize();
							}
						}
						else
						{	UINT org_total = GetCount();
							if(i<(int)_BaseCount)_ImportBase(count);
							else _NewItems.ChangeSize(_NewItems.GetSize() + count);
							
							int innew  = 0;
							int merge = GetCount() - (org_total - i);
							memmove(&_NewItems[merge], &_NewItems[i], (org_total - i)*sizeof(ITEM));
							for(;;i++)
							{
								if(innew >= (int)count)
								{	
									UINT rest_len = (UINT)(_NewItems.GetSize() - merge);
									memmove(&_NewItems[i], &_NewItems[merge], rest_len*sizeof(ITEM));
									i += rest_len - 1;
									goto MERGE_END;
								}
								if(merge >= _NewItems.GetSize())break;
								if(_NewItems[merge].key() < keys_sorted[innew].key())
								{
									rt::Copy(_NewItems[i], _NewItems[merge]);
									merge++;
								}
								else if(keys_sorted[innew].key() < _NewItems[merge].key())
								{
									if(!is_pod)rt::Zero(_NewItems[i]);
									_NewItems[i].Set(keys_sorted[innew], mode);
									_TotalItemSize += _NewItems[i].GetEmbeddedSize();
									innew++;
								}
								else
								{	
									_TotalItemSize -= _NewItems[merge].GetEmbeddedSize();
									if(!is_pod)_NewItems[merge].~ITEM();
									merge++;

									if(!is_pod)rt::Zero(_NewItems[i]);
									_NewItems[i].Set(keys_sorted[innew], mode);
									_TotalItemSize += _NewItems[i].GetEmbeddedSize();
									innew++;
								}
							}
							// append all the rest
							for(;innew < (int)count; innew++, i++)
							{
								rt::Zero(_NewItems[i]);
								_NewItems[i].Set(keys_sorted[innew], mode);
							}

						MERGE_END:
							((rt::BufferEx<rt::_details::Zeros<sizeof(ITEM)>>&)_NewItems).ShrinkSize(i - _BaseCount + 1); // hack: skip dtor
						}
					}
	bool			_Append(const KEY* k, RvmTypePointerSupplyMode key_mode, const VAL* v, RvmTypePointerSupplyMode val_mode)
					{	if(GetCount() && *k <= _GetByPos(GetCount()-1).key())return false;
						auto& n = _NewItems.push_back();
						n.Set(k, key_mode, v, val_mode);
						_TotalItemSize += n.GetEmbeddedSize();
						return true;
					}
	bool			_Remove(const KEY& k)
					{	int i = _SC::FindKey(k);
						if(i<0)return false;
						if(i < (int)_BaseCount)_ImportBase();
						_TotalItemSize -= _NewItems[i - _BaseCount].GetEmbeddedSize();
						_NewItems.erase(i);
						return true;
					}
public:
	OrderedMapMutable(){ _Unbase(); _TotalItemSize = 0; }
	OrderedMapMutable(const OrderedMap<KEY, VAL, OFF, is_pod>& x){ Assign(x); }
	void			Assign(const OrderedMap<KEY, VAL, OFF, is_pod>& x){ _pBase = &x; _BaseCount = _pBase->GetCount(); _TotalItemSize = _pBase->_ItemTotalSize(); _NewItems.ChangeSize(0); }
	bool			IsEmpty() const { return _BaseCount == 0 && _NewItems.GetSize() == 0; }
	void			Empty(){ _Unbase(); _NewItems.ShrinkSize(0); }
	UINT			GetCount() const { return (UINT)_NewItems.GetSize() + _BaseCount; }
	bool			Has(const KEY& k) const { return _SC::FindKey(k) >= 0; }

#if defined(PLATFORM_DEBUG_BUILD)
	bool			VerifyTotalItemSize() const
					{	ULONGLONG item_size = 0;
						for(UINT i=0; i<GetCount(); i++)
							item_size += _GetByPos(i).GetEmbeddedSize();
						return item_size == _TotalItemSize;
					}
#endif
};

template<typename KEY, typename OFF = UINT>
using OrderedSet = OrderedMap<KEY,void,OFF>;

template<typename KEY, typename OFF = UINT>
using OrderedSetMutable = OrderedMapMutable<KEY,void,OFF>;

#undef _DETAILS_ORDEREDMAPOP_DECL_FRIEND_TYPES
} // namespace rvm

RVM_TYPETRAITS_GENERIC_DEF(
	MARCO_CONCAT(typename KEY, typename VAL, typename OFF, bool is_pod),
	MARCO_CONCAT(OrderedMap<KEY,VAL,OFF,is_pod>),
	MARCO_CONCAT(OrderedMapMutable<KEY,VAL,OFF,is_pod>)
)
