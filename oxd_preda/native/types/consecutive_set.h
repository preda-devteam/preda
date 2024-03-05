#pragma once
#include "ordered_map.h"


namespace rvm
{

///////////////////////////////////////////////////////////////////////
// Ordered Map of POD/non-POD => POD/non-POD
template<typename T, typename T_COUNT>
class ConsecutiveSet;
template<typename T, typename T_COUNT>
class ConsecutiveSetMutable;

namespace _details
{
#pragma pack(push, 1)

template<typename T, typename T_COUNT>
struct ConsecutiveRange
{
	T			Val;
	T_COUNT		Count;
	T			begin() const { return Val; }
	T			end() const { return Val + Count; }
	bool		has(const ConsecutiveRange& x) const { return x.begin() >= begin() && x.end() <= end(); }
	bool		has(T x) const { return begin() <= x && x < end(); }
};

template<typename SET, typename T, typename T_COUNT>
class ConsecutiveRangedSetOp
{	typedef _details::ConsecutiveRange<T, T_COUNT> T_RANGE;
	auto&	_get() const { return *(SET*)this; }
	template<typename TT>
	bool	_has(const TT& x) const
			{	
				for(UINT i = 0; i < _get()._Count(); i++)
				{
					if(_get().Ranged[i].has(x))return true;
				}
				return false;
			}
public:
	void	Jsonify(rt::Json& append) const
			{
				auto& str = append.GetInternalString();
				str += '[';
				for(UINT i = 0; i < _get()._Count(); i++)
				{	
					ASSERT(_get().Ranged[i].Count);
					if(_get().Ranged[i].Count == 1)
					{
						str += rt::tos::Number(_get().Ranged[i].Val) + ',';
					}
					else {
						str += '[' + rt::tos::Number(_get().Ranged[i].Val) + ',' + rt::tos::Number(_get().Ranged[i].Count) + "],";
					}
				}
				str.EndClosure(']');
			}
	void	RangeJsonify(rt::Json& append) const
			{
				auto& str = append.GetInternalString();
				str += '[';
				for(UINT i = 0; i < _get()._Count();)
				{
					T base = _get().Flatten[i];
					UINT range_count = 1;
					UINT j = i + 1;
					for(; j < _get()._Count(); j++)
					{
						if(base + j - i == _get().Flatten[j])
						{
							range_count++;
						}
						else 
						{
							break;
						}
					}
					str += '[' + rt::tos::Number(base) + ',' + rt::tos::Number(range_count) + "],";
					i = j;
				}
				str.EndClosure(']');
			}
	LONGLONG	AssertValid() const	// return total count
			{	if(_get()._Count() == 0)return 0;
				LONGLONG ret = (LONGLONG)_get().Ranged[0].Count;
				for(UINT i=1; i<_get()._Count(); i++)
				{	
					ASSERT(_get().Ranged[i].begin() > _get().Ranged[i-1].end());
					ret += _get().Ranged[i].Count;
				}
				return ret;
			}
	bool	Has(T x) const { return _has(x); }
	bool	Has(const T_RANGE& x) const { return _has(x); }
};

#pragma pack(pop)
} // namespace _details


#pragma pack(push, 1)
template<typename T, typename T_COUNT> // memory layout compatible with OrderedSet<T, UINT> 
class ConsecutiveSet: protected _details::ConsecutiveRangedSetOp<ConsecutiveSet<T, T_COUNT>, T, T_COUNT>
{
	static_assert(rt::TypeTraits<T>::IsPOD, "T must be POD type");
	template<typename, typename>
	friend class ConsecutiveSetMutable;
	template<typename, typename, typename>
	friend class _details::ConsecutiveRangedSetOp;
	typedef _details::ConsecutiveRange<T, T_COUNT> T_RANGE;
	typedef _details::ConsecutiveRangedSetOp<ConsecutiveSet<T, T_COUNT>, T, T_COUNT> _SC;
	TYPETRAITS_DECLARE_NON_POD;
    RVM_IMMUTABLE_TYPE(ConsecutiveSet);

protected:
	UINT	Type_Count;
	union
	{
		T		Flatten[1];
		T_RANGE	Ranged[1];
	};
	UINT	_Count() const { return Type_Count&0x7fffffffU; }
public:
	typedef T_RANGE Range;
	auto&	_OrderSet() const { return *((const OrderedSet<T, UINT>*)this); }
	bool	IsRanged() const { return Type_Count&0x80000000U; }
	UINT	GetEmbeddedSize() const { return sizeof(UINT) + _Count()*(IsRanged()?sizeof(T_RANGE):sizeof(T)); }
	bool	Has(T x){ return IsRanged()?_SC::Has(x):_OrderSet().Has(x); }
	bool	Has(const T_RANGE& x)
			{	if(IsRanged())return _SC::Has(x);
				int pos = _OrderSet().FindKey(x.Val);
				if(pos<0)return false;
				if(pos + x.Count > _Count())return false;
				for(UINT i=1; i<x.Count; i++)
					if(Flatten[pos + i] != x.Val + i)return false;
				return true;
			}
	UINT	Embed(const ConsecutiveSetMutable<T, T_COUNT>& d)
			{	if(d.bPreferRangedEmbedding)
				{	Type_Count = (UINT)(d.Ranged.GetSize() | 0x80000000U);
					memcpy(Ranged, d.Ranged, sizeof(T_RANGE)*d.Ranged.GetSize());
					return UINT(sizeof(UINT) + sizeof(T_RANGE)*d.Ranged.GetSize());
				}
				else
				{	
					Type_Count = (UINT)d.TotalCount;
					UINT pos = 0;
					for(auto& r : d.Ranged)
					{	Flatten[pos++] = r.Val;
						for(UINT i=1; i<r.Count; i++)
							Flatten[pos++] = r.Val + i;
					}
					ASSERT(pos == d.TotalCount);
					return sizeof(UINT) + sizeof(T)*pos;
				}
			}
	UINT 	Embed(const ConsecutiveSet<T, T_COUNT>& d)
			{
				Type_Count = d.Type_Count;
				if(d.IsRanged())
				{	
					memcpy(Ranged, d.Ranged, sizeof(T_RANGE)*d._Count());
					return UINT(sizeof(T_RANGE)*d._Count());
				}
				else
				{	
					memcpy(Flatten, d.Flatten, sizeof(T)*d._Count());
					return UINT(sizeof(T)*d._Count());
				}
			}
	template<typename FUNC>
	void	Iterate(FUNC&& it) const
			{	
				if(IsRanged())
				{	for(UINT i=0; i<_Count(); i++)
						if(!rt::CallLambda(true, it, Ranged[i]))return;
				}
				else
				{	for(UINT i=0; i<_Count(); i++)
						if(!rt::CallLambda(true, it, Range{Flatten[i], 1}))return;
				}
			}
	void	Jsonify(rt::Json& append, bool bForcedRanged = false) const 
	{ 
		if(bForcedRanged && !IsRanged())
		{
			_SC::RangeJsonify(append);
		}
		else if(IsRanged())
		{
			_SC::Jsonify(append);
		}
		else{ 
			_OrderSet().Jsonify(append);
		}
	}
	static UINT		GetEmbeddedSize(const ConsecutiveSetMutable<T, T_COUNT>& d)
					{	return (UINT)(offsetof(ConsecutiveSet, Flatten) + (d.bPreferRangedEmbedding?
							sizeof(T_RANGE)*d.Ranged.GetSize():sizeof(T)*d.TotalCount
						));
					}
	static bool		IsEmbeddable(const ConsecutiveSetMutable<T, T_COUNT>& d)
	{
		return (d.bPreferRangedEmbedding && d.Ranged.GetSize() < 0x80000000U) || 
		   (!d.bPreferRangedEmbedding && d.TotalCount < 0x80000000U);
	}
	static auto&	Zero(){ static const UINT _zero(0); return (const ConsecutiveSet&)_zero; }
	static void		GetTypeSignature(rt::String& n){ n += rt::SS("consecutive_set<"); RvmTypeSignature<T>::Get(n); n += ','; RvmTypeSignature<T_COUNT>::Get(n); n += '>'; }
};
#pragma pack(pop)


template<typename T, typename T_COUNT>
class ConsecutiveSetMutable: protected _details::ConsecutiveRangedSetOp<ConsecutiveSetMutable<T, T_COUNT>, T, T_COUNT>
{
	TYPETRAITS_UNITTEST_OPEN_ACCESS;
	static_assert(rt::TypeTraits<T>::IsPOD, "T should be POD type");
	template<typename, typename> // memory layout compatible with OrderedSet<T, UINT> 
	friend class ConsecutiveSet;
	template<typename, typename, typename>
	friend class _details::ConsecutiveRangedSetOp;
	typedef  _details::ConsecutiveRangedSetOp<ConsecutiveSetMutable<T, T_COUNT>, T, T_COUNT> _SC;
	TYPETRAITS_DECLARE_NON_POD;

protected:
	typedef _details::ConsecutiveRange<T, T_COUNT> T_RANGE;
	bool					bPreferRangedEmbedding;
	LONGLONG				TotalCount;
	rt::BufferEx<T_RANGE>	Ranged;
	SIZE_T	_Count() const { return Ranged.GetSize(); }
	void	_AdjustTotalCount(int i)
			{	TotalCount += i;
				LONGLONG flatten_size = TotalCount*sizeof(T);
				LONGLONG ranged_size = Ranged.GetSize()*sizeof(T_RANGE);
				bPreferRangedEmbedding = ranged_size <= flatten_size;
				// _LOG("Total count: " << TotalCount);
				// for(auto range : Ranged) {
				// _LOG("begin: " << range.begin() << ", count: " << range.Count);
				// }
				ASSERT(TotalCount == _SC::AssertValid());
			}
	bool	search_insert_pos(const T& val, int lower, int upper, int& mid)
			{
				mid = (upper - lower + 1)/2 + lower;
				if(Ranged[mid].has(val)) {
					return true;
				}
				if(upper > lower + 1) {
					if(Ranged[mid].begin() < val) {
						return search_insert_pos(val, mid, upper, mid);
					}
					else {
						return search_insert_pos(val, lower, mid, mid);
					}
				}
				mid = val < Ranged[upper].begin()? lower : upper;
				if(mid == Ranged.GetSize() - 1 && val > Ranged[mid].end()){
					mid = (int)Ranged.GetSize();
					return true;
				}
				return false;
			}
	void	printBuffer()
			{
				rt::String str;
				str += '[';
				for(UINT i = 0; i < Ranged.GetSize(); i++)
				{	
					ASSERT(Ranged[i].Count);
					if(Ranged[i].Count == 1)
					{
						str += rt::tos::Number(Ranged[i].Val) + ',';
					}
					else {
						str += '[' + rt::tos::Number(Ranged[i].Val) + ',' + rt::tos::Number(Ranged[i].Count) + "],";
					}
				}
				str.EndClosure(']');
				_LOG(str);
			}
public:
	bool	IsEmpty() const { return Ranged.GetSize() == 0; }
	void	Empty(){ Ranged.ShrinkSize(0); TotalCount = 0; bPreferRangedEmbedding = false; }
	void	Insert(const T_RANGE& x)
			{
				int size = (int)Ranged.GetSize();
				if(size == 0){
					Ranged.push_front(x);
					_AdjustTotalCount((int)x.Count);
					return;
				}
				int head_insert_pos = 0;
				bool head_found = search_insert_pos(x.begin(), 0, size - 1, head_insert_pos);
				head_insert_pos = !head_found && head_insert_pos < Ranged.GetSize() - 1 && (Ranged[head_insert_pos].end() < x.begin()) ? head_insert_pos + 1 : head_insert_pos;
				int tail_insert_pos = 0;
				bool tail_found = search_insert_pos(x.end(), 0, size - 1, tail_insert_pos);
				tail_insert_pos = !tail_found && tail_insert_pos < head_insert_pos && (Ranged[tail_insert_pos].end() < x.begin()) && (Ranged[head_insert_pos].begin() > x.end())? head_insert_pos : tail_insert_pos;
				if(tail_insert_pos == Ranged.GetSize() && head_insert_pos != Ranged.GetSize()){
					tail_insert_pos = (int)Ranged.GetSize() - 1;
				}
				if((tail_insert_pos == Ranged.GetSize() && head_insert_pos == Ranged.GetSize()) || (head_insert_pos == tail_insert_pos && !Ranged[head_insert_pos].has(x.begin()) && !Ranged[head_insert_pos].has(x.end()) && !x.has(Ranged[head_insert_pos].begin()) && !x.has(Ranged[head_insert_pos].end()))){
					Ranged.insert(head_insert_pos, x);
					_AdjustTotalCount((int)x.Count);
					return;
				}
				int overlapped_count = 0;
				for(int i = head_insert_pos; i <= tail_insert_pos; i++){
					overlapped_count += (int)Ranged[i].Count;
				}
				T_RANGE tmp({Ranged[tail_insert_pos].Val, Ranged[tail_insert_pos].Count});
				Ranged[head_insert_pos].Val = rt::min(Ranged[head_insert_pos].Val , x.Val);
				Ranged[head_insert_pos].Count = rt::max(tmp.end(), x.end()) - Ranged[head_insert_pos].Val;
				Ranged.erase(head_insert_pos + 1, tail_insert_pos + 1);
				_AdjustTotalCount((int)Ranged[head_insert_pos].Count - overlapped_count);
				return;
			}
	void	Insert(T x){ Insert(T_RANGE{ x, 1 }); }
	bool	Remove(const T_RANGE& x)
			{	
				for(UINT i=0; i<Ranged.GetSize(); i++)
				{	
					auto& r = Ranged[i];
					if(r.end() < x.begin())continue;
					if(r.end() < x.end() || x.begin() < r.begin() || x.end() < r.begin())return false;
					if(r.begin() == x.begin() && r.Count == x.Count){ 
						Ranged.erase(i);
						_AdjustTotalCount(-int(x.Count));
						return true;
					}
					if(r.begin() == x.begin()){ r = { x.end(), r.Count - x.Count }; _AdjustTotalCount(-int(x.Count)); return true; }
					if(r.end() == x.end()){ r.Count -= x.Count; _AdjustTotalCount(-int(x.Count)); return true; }
					T_RANGE temp({ x.end(), (T_COUNT)(Ranged[i].end() - x.end()) });
					Ranged.insert(i + 1, temp);
					Ranged[i].Count = x.begin() - Ranged[i].begin();
					_AdjustTotalCount(-int(x.Count));
					return true;
				}
				return false;
			}
	bool	Remove(T x){ return Remove({ x, 1 }); }
	void	Assign(const ConsecutiveSet<T, T_COUNT>& x)
			{	Empty();
				if(x.IsRanged())
				{	
					for(UINT i=0; i<x._Count(); i++)
					{	
						Insert(x.Ranged[i]);
					}
				}
				else
				{
					for(UINT i=0; i<x._Count(); i++)
					{	
						Insert({ x.Flatten[i], 1 });
					}
				}
			}
	bool	JsonParse(const rt::String_Ref& str)
			{	
				Empty();
				rt::JsonArray arr(str);
				rt::String_Ref val;
				while(arr.GetNextObjectRaw(val))
				{
					if(val.IsEmpty())return false;

					auto& r = Ranged.push_back();
					if(val[0] == '[')
					{	
						bPreferRangedEmbedding = true;
						rt::String range[2];
						char* p = val.Begin() + 1;
						while(*p != ',') {
							if(*p == ']') {
								return false;
							}
							range[0] += *p;
							p++;
						}
						if(*p == ',') {
							p++;
						}
						else {
							return false;
						}
						while(*p != ']') {
							range[1] += *p;
							p++;
						}
						if(range[0].ToNumber(r.Val) < 0 || range[1].ToNumber(r.Count) < 0)return false;
						if(r.Count == 0)
						{	Ranged.ShrinkSize(Ranged.GetSize() - 1);
							continue;
						}
					}
					else
					{
						if(val.ToNumber(r.Val) < 0)return false;
						r.Count = 1;
					}
					TotalCount += r.Count;
					if(Ranged.GetSize()>1)
					{
						auto& prev = Ranged[Ranged.GetSize()-2];
						if(prev.begin() > r.begin())return false;
						if(prev.end() >= r.begin())
						{
							prev.Count = rt::max(prev.end(), r.end()) - prev.begin();
							Ranged.ShrinkSize(Ranged.GetSize()-1);
						}
					}
				}

				return true;
			}
	void	Jsonify(rt::Json& append) const {
			auto& str = append.GetInternalString();
			str += '[';
			for(UINT i = 0; i < Ranged.GetSize(); i++)
			{
				str += '[' + rt::tos::Number(Ranged[i].Val) + ',' + rt::tos::Number(Ranged[i].Count) + "],";
			}
			str.EndClosure(']');
	}

};

} // namespace rvm

RVM_TYPETRAITS_GENERIC_DEF(
	MARCO_CONCAT(typename T, typename T_COUNT),
	MARCO_CONCAT(ConsecutiveSet<T, T_COUNT>), 
	MARCO_CONCAT(ConsecutiveSetMutable<T, T_COUNT>)
)