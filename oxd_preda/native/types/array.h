#pragma once
#include "../../../SFC/core/ext/sparsehash/sparsehash.h"
#include "typetraits.h"

namespace rvm
{

template<typename VAL, typename OFF = UINT, bool is_pod = rt::TypeTraits<VAL>::IsPOD>
class Array;
template<typename VAL, typename OFF = UINT, bool is_pod = rt::TypeTraits<VAL>::IsPOD>
class ArrayMutable;

namespace _details
{
template<typename ARRAY, typename VAL>
class ArrayOp
{	
protected:
	auto* This() const { return (ARRAY*)this; }
	template<typename RET_MATCH, typename RET_MISMATCH>
	auto _BinarySearch(const VAL& x, RET_MATCH&& hit_func, RET_MISMATCH&& mis_func) const
	{	UINT f = 0, l = This()->GetCount() - 1;
		while(l - f > 1)
		{	UINT mid = (f + l)/2;
			auto& v = This()->Get(mid);
			if(v < x){ f = mid+1; }
			else if(x < v){ l = mid-1; }
			else return hit_func(mid); // can be any matched one
		}
		return mis_func(f, l);
	}
public:
	int Find(const VAL& x) const
	{	for(UINT i=0; i<This()->GetCount(); i++)
			if(This()->Get(i) == x)return i;
		return -1;
	}
	int FindSorted(const VAL& x) const
	{
		if(This()->GetCount() <= 16)return Find(x);
		return _BinarySearch(x, 
					[](UINT mid) -> int { return mid; },
					[&x, this](UINT f, UINT l) -> int {
						if(This()->Get(f) == x)return f;
						if(f == l || !(This()->Get(l) == x))return -1;
						return l;
				   }
			   );				
	}
	int LowerBound(const VAL& x) const // [0, GetCount()]
	{
		if(This()->GetCount() <= 16)
		{	for(int i=This()->GetCount()-1; i>=0; i--)
				if(This()->Get(i) <= x)return i+1;
			return 0;
		}
		return _BinarySearch(x, 
					[](UINT mid) -> int { return mid + 1; },
					[&x, this](UINT f, UINT l) -> int {
						if(f == l)return This()->Get(f) <= x?f+1:f;
						if(This()->Get(f) > x)return f;
						if(This()->Get(l) <= x)return l + 1;
						return l;
				   }
			   );	
	}
};
template<typename ARRAY, typename VAL, bool is_pod = rt::TypeTraits<VAL>::IsPOD>
class ArrayMutableOp;
	template<typename ARRAY, typename VAL>
	class ArrayMutableOp<ARRAY, VAL, false>: public ArrayOp<ARRAY, VAL>
	{	auto* This() const { return (ARRAY*)this; }
		auto& Get(UINT i) const { return ((ARRAY*)this)->Get(i); }
	public:
		void InsertSorted(const VAL& x){ InsertSorted(&x, RVMPTR_COPY); }
		bool InsertSortedUnique(const VAL& x){ return InsertSortedUnique(&x, RVMPTR_COPY); }
		void InsertSorted(const VAL* x, RvmTypePointerSupplyMode mode = RVMPTR_KEEP)
		{	
			if(This()->GetCount() <= 16)
			{	for(int i=This()->GetCount()-1; i>=0; i--)
				{	auto& v = Get(i);
					if(v <= *x){ This()->Insert(i + 1, x, mode); return; }
				}
				This()->Insert(0, x, mode);
				return;
			}
			ArrayOp<ARRAY, VAL>::_BinarySearch(*x, 
				[x, this, mode](UINT mid) -> void { This()->Insert(mid + 1, x, mode); },
				[x, this, mode](UINT f, UINT l) -> void {
					auto& v = Get(f);
					if(v == *x){ This()->Insert(f+1, x, mode); return; }
					if(f == l){ This()->Insert(v < *x?f+1:f, x, mode); return; }
					auto& v2 = Get(l);
					if(v2 <= *x){ This()->Insert(l+1, x, mode); return; }
					This()->Insert(l, x, mode);
				}
			);
		}
		bool InsertSortedUnique(const VAL* x, RvmTypePointerSupplyMode mode = RVMPTR_KEEP) // if false, ptr will not be taken when mode=RVMPTR_TAKE
		{	
			if(This()->GetCount() <= 16)
			{	for(int i=This()->GetCount()-1; i>=0; i--)
				{	auto& v = Get(i);
					if(v < *x){ This()->Insert(i + 1, x, mode); return true; }
					if(v == *x)return false; // duplicated
				}
				This()->Insert(0, x, mode);
				return true;
			}
			return ArrayOp<ARRAY, VAL>::_BinarySearch(*x, 
						[](UINT mid) -> bool { return false; }, // duplicated
						[x, this, mode](UINT f, UINT l) -> bool {
							auto& v = Get(f);
							if(v == *x){ return false; }
							if(f == l){ This()->Insert(v < *x?f+1:f, x, mode); return true; }
							auto& v2 = Get(l);
							if(v2 == *x)return false;
							This()->Insert(v2 < *x?l + 1:l, x, mode);
							return true;
						}
					);
		}
	};
	template<typename ARRAY, typename VAL>
	class ArrayMutableOp<ARRAY, VAL, true>: public ArrayOp<ARRAY, VAL>
	{	typedef ArrayOp<ARRAY, VAL> _SC;
		auto* This() const { return (ARRAY*)this; }
		auto& Get(UINT i) const { return ((ARRAY*)this)->Get(i); }
	public:
		void InsertSorted(const VAL& x)
		{
			if(This()->GetCount() <= 16)
			{	for(int i=This()->GetCount()-1; i>=0; i--)
				{	auto& v = Get(i);
					if(v <= x){ This()->Insert(i + 1, x); return; }
				}
				This()->Insert(0, x);
				return;
			}
			ArrayOp<ARRAY, VAL>::_BinarySearch(x, 
				[&x, this](UINT mid) -> void { This()->Insert(mid + 1, x); },
				[&x, this](UINT f, UINT l) -> void {
					auto& v = Get(f);
					if(v == x){ This()->Insert(f+1, x); return; }
					if(f == l){ This()->Insert(v < x?f+1:f, x); return; }
					auto& v2 = Get(l);
					if(v2 <= x){ This()->Insert(l+1, x); return; }
					This()->Insert(l, x);
				}
			);
		}
		bool InsertSortedUnique(const VAL& x)
		{	
			if(This()->GetCount() <= 16)
			{	for(int i=This()->GetCount()-1; i>=0; i--)
				{	auto& v = Get(i);
					if(v < x){ This()->Insert(i + 1, x); return true; }
					if(v == x)return false; // duplicated
				}
				This()->Insert(0, x);
				return true;
			}
			return ArrayOp<ARRAY, VAL>::_BinarySearch(x, 
						[](UINT mid) -> bool { return false; }, // duplicated
						[&x, this](UINT f, UINT l) -> bool {
							auto& v = Get(f);
							if(v == x){ return false; }
							if(f == l){ This()->Insert(v < x?f+1:f, x); return true; }
							auto& v2 = Get(l);
							if(v2 == x)return false;
							This()->Insert(v2 < x?l + 1:l, x);
							return true;
						}
					);
		}
	};
} // namespace _details

#pragma pack(push, 1)
template<typename VAL, typename OFF>
class Array<VAL, OFF, false>: public _details::ArrayOp<Array<VAL, OFF, false>, VAL>
{
	static_assert(sizeof(OFF) <= 4, "type of OFF is too large");
	static_assert(TypeTraits<VAL>::IsImmutable, "VAL must be immutable type");
	template<typename, typename, bool>
	friend class ArrayMutable;
	friend class _details::ArrayOp<Array, VAL>;
    enum:OFF {
        NEWBIT = 1U<<(8*sizeof(OFF)-1),
        OFFBITMASK = NEWBIT-1
    };
public:
	TYPETRAITS_DECLARE_NON_POD;
	TYPETRAITS_DECLARE_ELEMENT(VAL);
	RVM_IMMUTABLE_TYPE(Array)

protected:
	OFF				Count;			// # of keys
	OFF				ItemTotalSize;	// sizeof(<VAL>[Count])
	BYTE			Data[1];		// OFF[Count] + <VAL>[Count]

	LPBYTE			_Items(){ return &Data[sizeof(OFF)*Count]; }
	LPCBYTE			_Items() const { return &Data[sizeof(OFF)*Count]; }
	const OFF*		_OffsetTable() const { return (const OFF*)Data; }
	VAL*			_GetByPos(UINT i) const { ASSERT(i<Count); auto off = _OffsetTable()[i]; return off!=OFFBITMASK?(VAL*)&_Items()[off]:nullptr; }

public:
	Array(decltype(0) x){ ASSERT(x==0); Count = 0; }
	UINT			GetCount() const { return Count; }
	bool			IsEmpty() const { return Count == 0; }

	const VAL&		operator [](UINT i) const { return Get(i); }
	const VAL&		Get(UINT i) const { auto* ret = _GetByPos(i); return ret?*ret:VAL::Zero(); }
	void			Jsonify(rt::Json& append) const 
					{	auto& str = append.GetInternalString();
						str += '[';
						LPCBYTE p = _Items();
						auto* offsets = _OffsetTable();
						for(UINT i=0; i<Count; i++)
						{	if(i)str += ',';
							auto off = offsets[i];
							if(off != OFFBITMASK)
								RvmTypeJsonify(*(const VAL*)(p + off), (rt::Json&)str);
							else
								str += rt::SS("null");
						}
						str += ']';
					}
	UINT			GetEmbeddedSize() const { return sizeof(Count) + (Count?sizeof(ItemTotalSize) + ItemTotalSize + Count*sizeof(OFF):0); }

	template<typename ArrayMutable>
	static UINT		GetEmbeddedSize(const ArrayMutable& c){	return sizeof(Count) + (c.GetCount()?sizeof(ItemTotalSize) + c._TotalItemSize + c.GetCount()*sizeof(OFF):0); }
	template<typename ArrayMutable>
	static bool		IsEmbeddable(const ArrayMutable& c) { return c._TotalItemSize < OFFBITMASK; }
	template<typename ArrayMutable>
	UINT			Embed(const ArrayMutable& c)
					{	Count = c.GetCount();
						ASSERT(c.VerifyTotalItemSize());
						if(Count)
						{	ItemTotalSize = c._TotalItemSize;
							auto* offsets = rt::_CastToNonconst(_OffsetTable());
							LPBYTE items = _Items();
							OFF off = 0;
							c.ForEach([&offsets, &off, items](const VAL* x){
								if(x)
								{	UINT size = x->GetEmbeddedSize();
									*offsets = off;
									memcpy(items + off, x, size);
									off += size;
								}
								else *offsets = OFFBITMASK;
								offsets++;
							});
						}
						return GetEmbeddedSize();
					}
	static auto&	Zero(){ static const Array _zero(0); return _zero; }
	static void		GetTypeSignature(rt::String& n){ n += rt::SS("array<"); RvmTypeSignature<VAL>::Get(n); n += '>'; }
};
#pragma pack(pop)

template<typename VAL, typename OFF>
class ArrayMutable<VAL, OFF, false>: public _details::ArrayMutableOp<ArrayMutable<VAL, OFF, false>, VAL>
{
	TYPETRAITS_DECLARE_NON_POD;
	static_assert(sizeof(OFF) <= 4, "type of OFF is too large");
	static_assert(TypeTraits<VAL>::IsImmutable, "VAL should be Immutable type");
	template<typename, typename, bool>
	friend class Array;
	friend class _details::ArrayOp<ArrayMutable, VAL>;
	friend class _details::ArrayMutableOp<ArrayMutable, VAL>;
    enum:OFF {
        NEWBIT = 1U<<(8*sizeof(OFF)-1),
        OFFBITMASK = NEWBIT-1
    };
	const Array<VAL, OFF, false>*				_pBase;
	UINT										_BaseCount;
	bool										_BaseImported;  // in _NewItems
	rt::BufferEx<_details::rvmtype_ptr<VAL>>	_NewItems;
	OFF											_TotalItemSize;
	const VAL&		_Refer(OFF x) const { ASSERT(x!=OFFBITMASK); return *(VAL*)((x&NEWBIT)?&_NewItems[x&OFFBITMASK]:(_pBase->_Items() + x)); }
	UINT			_GetItemSize(UINT i) const
					{	if(_BaseImported)return _NewItems[i].GetValueSize();
						if(i>=_BaseCount)return _NewItems[i-_BaseCount].GetValueSize();
						return _pBase->Get(i).GetEmbeddedSize();
					}
	void			_Import(UINT size)
					{	ASSERT(!_BaseImported);
						ASSERT(size <= _BaseCount);
						_NewItems.ChangeSize(_NewItems.GetSize() + size);
						memmove(&_NewItems[size], &_NewItems[0], _NewItems.GetSize() - size);
						for(UINT i=0; i<size; i++)
							_NewItems[i].Set(_pBase->_GetByPos(i), RVMPTR_KEEP);
						_BaseImported = true;
					}
public:
	ArrayMutable(){ _pBase = nullptr; _BaseImported = true; _BaseCount = 0; _TotalItemSize = 0; }
	ArrayMutable(const Array<VAL, OFF, false>& x){ _pBase = &x; _BaseCount = _pBase->GetCount(); _BaseImported = false; _TotalItemSize = _pBase->ItemTotalSize; }
	bool			IsEmpty() const { return _BaseCount == 0 && _NewItems.GetSize() == 0; }
	void			Empty(){ _pBase = nullptr; _BaseImported = true; _BaseCount = 0; _TotalItemSize = 0; _NewItems.ShrinkSize(0); }
	UINT			GetCount() const { return _BaseImported?(UINT)_NewItems.GetSize():(UINT)_NewItems.GetSize() + _BaseCount; }
	void			SetCount(UINT size)
					{	if(size > GetCount())
						{	_NewItems.ChangeSize(_NewItems.GetSize() + size - GetCount());
						}
						else // shrink
						{	for(UINT i=size; i<GetCount(); i++)
								_TotalItemSize -= _GetItemSize(i);
							if(_BaseImported)
								_NewItems.ShrinkSize(size);
							else
							{	if(size >= _BaseCount)
									_NewItems.ChangeSize(size - _BaseCount);
								else
									_Import(size);
							}
						}
					}
	const VAL&		Get(UINT i) const
					{	if(i>=_BaseCount)return _NewItems[i-_BaseCount].SafeGet();
						ASSERT(_pBase);
						return _pBase->Get(i);
					}
	VAL&			Get(UINT i)
					{	if(i>=_BaseCount)return _NewItems[i-_BaseCount].Get();
						if(!_BaseImported)_Import(_BaseCount);
						return _NewItems[i].Get();
					}
	void			Set(UINT i, const VAL& x){ Set(i, &x, RVMPTR_COPY); }
	void			Set(UINT i, const VAL* x, RvmTypePointerSupplyMode mode = RVMPTR_KEEP)
					{	ASSERT(i<GetCount());
						_TotalItemSize -= _GetItemSize(i);
						_TotalItemSize += x->GetEmbeddedSize();
						if(i>=_BaseCount)
						{	if(_BaseImported)_NewItems[i].Set(x, mode);
							else _NewItems[i - _BaseCount].Set(x, mode);
							return;
						}
						if(!_BaseImported)_Import(_BaseCount);
						_NewItems[i].Set(x, mode);
					}
	void			Unset(UINT i) // set [i] to null
					{	ASSERT(i<GetCount());
						_TotalItemSize -= _GetItemSize(i);
						if(i>=_BaseCount)
						{	if(_BaseImported)_NewItems[i].Release();
							else _NewItems[i - _BaseCount].Release();
							return;
						}
						if(!_BaseImported)_Import(_BaseCount);
						_NewItems[i].Release();
					}
	OFF				Append(const VAL& x){ return Append(&x, RVMPTR_COPY); }
	OFF				Append(const VAL* x, RvmTypePointerSupplyMode mode = RVMPTR_KEEP)
					{	_NewItems.push_back().Set(x, mode);
						_TotalItemSize += x->GetEmbeddedSize();
						return GetCount() - 1;
					}
	void			Insert(UINT i, const VAL& x){ Insert(i, &x, RVMPTR_COPY); }
	void			Insert(UINT i, const VAL* x, RvmTypePointerSupplyMode mode = RVMPTR_KEEP)
					{	if(i>=_BaseCount){ _NewItems.insert(i - _BaseCount).Set(x, mode); }
						else
						{	_Import(_BaseCount);
							_NewItems.insert(i).Set(x, mode);
						}
						_TotalItemSize += x->GetEmbeddedSize();
					}
	void			Remove(UINT i)
					{	ASSERT(i<GetCount());
						_TotalItemSize -= _GetItemSize(i);
						if(_BaseImported)
							_NewItems.erase(i);
						else
						{	if(i>=_BaseCount)
								_NewItems.erase(i - _BaseCount);
							else
							{	_Import(_BaseCount);
								_NewItems.erase(i);
							}
						}
					}
	void			Remove(const UINT* poss, UINT pos_count)
					{	for(UINT i=0; i<pos_count; i++)
						{	UINT pos = poss[i];
							_TotalItemSize -= _GetItemSize(pos);
							ASSERT(pos < GetCount());
							if(_BaseImported)
								_NewItems[pos].MarkAsDeleted();
							else
							{	if(i >= _BaseCount)
									_NewItems[pos - _BaseCount].MarkAsDeleted();
								else
								{	_Import(_BaseCount);
									_NewItems[pos].MarkAsDeleted();
								}
							}
						}
						UINT open = 0;  // earse ones marked as deleted
						for(UINT i=0; i<_NewItems.GetSize(); i++)
						{	if(_NewItems[i].IsMarkedAsDeleted())
								continue;
							if(i != open)rt::Copy(_NewItems[open], _NewItems[i]);
							open++;
						}
						typedef rt::_details::Zeros<sizeof(_NewItems[0])> EP;
						((rt::BufferEx<EP>&)_NewItems).ShrinkSize(open); // avoid calling dtor on moved items
					}
	template<typename FUNC>
	void			ForEach(FUNC&& v) const
					{	if(_BaseImported){ for(auto& ptr : _NewItems)v(ptr.v); }
						else
						{
							for(UINT i=0; i<_BaseCount; i++)
							{	auto off = _pBase->_OffsetTable()[i];
								v(off!=OFFBITMASK?(const VAL*)&_pBase->_Items()[off]:nullptr);
							}
							for(auto& ptr : _NewItems)
								v(ptr.v);
						}
					}
	bool			JsonParse(const rt::String_Ref& str_in)
					{	Empty();
						rt::String_Ref str = str_in.TrimSpace();
						if(str[0] != '[' || str.Last() != ']')return false;
						typedef typename TypeTraits<VAL>::Mutable val_mutable;
						rt::String_Ref item;
						rt::JsonArray json = str;
						val_mutable m;
						while(json.GetNextObjectRaw(item))
						{	if(!RvmTypeJsonParse(m, item)){ Empty(); return false; }
							Append(RvmImmutableTypeCompose(m), RVMPTR_TAKE);
						}
						return true;
					}
#if defined(PLATFORM_DEBUG_BUILD)
	bool			VerifyTotalItemSize() const
					{	ULONGLONG item_size = 0;
						for(UINT i=0; i<GetCount(); i++)
							item_size += _GetItemSize(i);
						return item_size == _TotalItemSize;
					}
#endif
};

#pragma pack(push, 1)
template<typename VAL, typename OFF>
class Array<VAL, OFF, true>: public _details::ArrayOp<Array<VAL, OFF, true>, VAL>
{
	static_assert(sizeof(OFF) <= 4, "type of OFF is too large");
	template<typename, typename, bool>
	friend class ArrayMutable;
	friend class _details::ArrayOp<Array, VAL>;
	TYPETRAITS_DECLARE_NON_POD;
	TYPETRAITS_DECLARE_ELEMENT(VAL);
	static const OFF OFF_MAX_NUM = ((1U << (8 * sizeof(OFF) - 1)) - 1);

protected:
	OFF				Count;			// # of keys
	VAL				Data[1];		// OFF[Count] + <VAL>[Count]
	VAL*			_GetByPos(UINT i) const { return &Data[i]; }

public:
	Array(decltype(0) x){ ASSERT(x==0); Count = 0; }
	UINT			GetCount() const { return Count; }
	bool			IsEmpty() const { return Count == 0; }

	VAL&			Get(UINT i){ ASSERT(i<Count); return Data[i]; }
	const VAL&		operator [](UINT i) const { return Get(i); }
	const VAL&		Get(UINT i) const { return rt::_CastToNonconst(this)->Get(i); }
	UINT			GetEmbeddedSize() const { return sizeof(Count) + sizeof(VAL)*Count; }

	template<typename ArrayMutable>
	static UINT		GetEmbeddedSize(const ArrayMutable& c){	return sizeof(Count) + c.GetCount()*sizeof(VAL); }
	template<typename ArrayMutable>
	static bool		IsEmbeddable(const ArrayMutable& c){ return c.GetCount() <= OFF_MAX_NUM; }
	template<typename ArrayMutable>
	UINT			Embed(const ArrayMutable& c)
					{	Count = c.GetCount();
						if(c._BaseCount)
						{	memcpy(Data, c._pBase->Data, c._BaseCount*sizeof(VAL));
							memcpy(Data + c._BaseCount, c._NewItems, c._NewItems.GetSize()*sizeof(VAL));
						}
						else
							memcpy(Data, c._NewItems, Count*sizeof(VAL));
						return GetEmbeddedSize();
					}
	void			Jsonify(rt::Json& append) const 
					{	auto& str = append.GetInternalString();
						str += '[';
						for(UINT i=0; i<Count; i++)
						{	if(i)str += ',';
							RvmTypeJsonify(Data[i], (rt::Json&)str);
						}
						str += ']';
					}
	static auto&	Zero(){ static const Array _zero(0); return _zero; }
	static void		GetTypeSignature(rt::String& n){ n += rt::SS("array<"); RvmTypeSignature<VAL>::Get(n); n += '>'; }
};
#pragma pack(pop)

template<typename VAL, typename OFF>
class ArrayMutable<VAL, OFF, true>: public _details::ArrayMutableOp<ArrayMutable<VAL, OFF, true>, VAL>
{
	TYPETRAITS_DECLARE_NON_POD;
	static_assert(sizeof(OFF) <= 4, "type of OFF is too large");
	template<typename, typename, bool>
	friend class Array;
	friend class _details::ArrayOp<ArrayMutable, VAL>;
	friend class _details::ArrayMutableOp<ArrayMutable, VAL>;
	const Array<VAL, OFF, true>*	_pBase;
	UINT							_BaseCount;
	rt::BufferEx<VAL>				_NewItems;
	void							_Unbase(){ _pBase = nullptr; _BaseCount = 0; }
public:
	ArrayMutable(){ _Unbase(); }
	ArrayMutable(const Array<VAL, OFF, true>& x){ _pBase = &x; _BaseCount = _pBase->GetCount(); }
	bool			IsEmpty() const { return _BaseCount == 0 && _NewItems.GetSize() == 0; }
	void			Empty(){ _Unbase(); _NewItems.ShrinkSize(0); }
	UINT			GetCount() const { return (UINT)_NewItems.GetSize() + _BaseCount; }
	void			SetCount(UINT size)
					{	if(size > GetCount())
						{	UINT ext = size - GetCount();
							_NewItems.push_back_n(VAL(0), ext);
						}
						else // shrink
						{	if(!_pBase)
								_NewItems.SetSize(size);
							else
							{	if(size >= _BaseCount)
									_NewItems.SetSize(size - _BaseCount);
								else
								{	_NewItems.SetSize(size);
									memcpy(_NewItems.Begin(), _pBase->Data, size*sizeof(VAL));
									_Unbase();
								}
							}
						}
					}
	const VAL&		Get(UINT i) const
					{	if(i<_BaseCount)
							return _pBase->Get(i);
						else
							return _NewItems[i - _BaseCount];
					}
	VAL&			Set(UINT i)
					{	if(i<_BaseCount)
						{
							UINT new_count = (UINT)_NewItems.GetSize();
							VERIFY(_NewItems.ChangeSize(new_count + _BaseCount));
							memmove(&_NewItems[_BaseCount], &_NewItems[0], new_count*sizeof(VAL));
							memcpy(&_NewItems[0], _pBase->Data, _BaseCount*sizeof(VAL));
							_Unbase();
						}
						return rt::_CastToNonconst(Get(i));
					}
	void			Set(UINT i, const VAL& x){ Set(i) = x; }
	void			Unset(UINT i){ Set(i, VAL(0)); }
	OFF				Append(const VAL& x)
					{	_NewItems.push_back(x);
						return GetCount() - 1;
					}
	void			Insert(UINT i, const VAL& x)
					{	ASSERT(i<=GetCount());
						if(i>=_BaseCount)
							_NewItems.insert(i - _BaseCount, x);
						else
						{	// include base and insert
							UINT new_count = (UINT)_NewItems.GetSize();
							VERIFY(_NewItems.ChangeSize(new_count + _BaseCount + 1));
							memmove(&_NewItems[_BaseCount+1], &_NewItems[0], new_count*sizeof(VAL));
							memcpy(&_NewItems[0], _pBase->Data, i*sizeof(VAL));
							_NewItems[i] = x;
							memcpy(&_NewItems[i+1], &_pBase->Data[i], (_BaseCount-i)*sizeof(VAL));
							_Unbase();
						}
					}
	void			Remove(UINT i)
					{	ASSERT(i<GetCount());
						if(i>=_BaseCount)
							_NewItems.erase(i - _BaseCount);
						else
						{	// include base and remove
							UINT new_count = _NewItems.GetSize();
							VERIFY(_NewItems.ChangeSize(new_count + _BaseCount - 1));
							memmove(&_NewItems[_BaseCount-1], &_NewItems[0], new_count*sizeof(VAL));
							memcpy(&_NewItems[0], _pBase->Data, i*sizeof(VAL));
							memcpy(&_NewItems[i], &_pBase->Data[i+1], (_BaseCount-i-1)*sizeof(VAL));
							_Unbase();
						}
					}
	void			Remove(const UINT* poss, UINT pos_count, const VAL& deleted_marker) // deleted_marker should be a value never used as element in the array
					{	for(UINT i=0; i<pos_count; i++)
						{	UINT pos = poss[i];
							ASSERT(pos < GetCount());
							if(i >= _BaseCount)
								_NewItems[pos - _BaseCount] = deleted_marker;
							else
							{	
								UINT new_count = (UINT)_NewItems.GetSize();
								VERIFY(_NewItems.ChangeSize(new_count + _BaseCount - 1));
								memmove(&_NewItems[_BaseCount], &_NewItems[0], new_count*sizeof(VAL));
								memcpy(&_NewItems[0], _pBase->Data, _BaseCount*sizeof(VAL));
								_Unbase();
								_NewItems[pos] = deleted_marker;
							}
						}
						UINT open = 0;  // drop ones marked as deleted
						for(UINT i=0; i<_NewItems.GetSize(); i++)
						{	if(_NewItems[i] == deleted_marker)
								continue;
							if(i != open)rt::Copy(_NewItems[open], _NewItems[i]);
							open++;
						}
						_NewItems.ShrinkSize(open); // avoid calling dtor on moved items
					}
	bool			JsonParse(const rt::String_Ref& str_in)
					{	Empty();
						rt::String_Ref str = str_in.TrimSpace();
						if(str[0] != '[' || str.Last() != ']')return false;
						typedef typename TypeTraits<VAL>::Mutable val_mutable;
						rt::String_Ref item;
						rt::JsonArray json = str;
						val_mutable m;
						while(json.GetNextObjectRaw(item))
						{	if(!RvmTypeJsonParse(m, item)){ Empty(); return false; }
							VAL x;
							_details::_Embed<VAL, val_mutable>::Set((LPBYTE)&x, m);
							Append(x);
						}
						return true;
					}
};

} // namespace rvm

RVM_TYPETRAITS_GENERIC_DEF(
	MARCO_CONCAT(typename VAL, typename OFF, bool is_pod),
	MARCO_CONCAT(Array<VAL,OFF,is_pod>), 
	MARCO_CONCAT(ArrayMutable<VAL,OFF,is_pod>)
)
