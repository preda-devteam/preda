#pragma once
/**
 * @file buffer_type.h
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
#include "../os/thread_primitive.h"
#include "string_type_ops.h"
#include <algorithm>

namespace rt
{
/** \defgroup buffer_type buffer_type
 * @ingroup rt
 *  @{
 */
namespace _details
{
	template<bool is_not_pod, typename t_Val>
	struct _xtor
	{	static void ctor(t_Val*p){ new (p) t_Val(); }
		template<typename... ARGS>
		static void ctor(t_Val*p, t_Val*end, ARGS && ... args){ for(;p<end;p++) new (p) t_Val(args...); }
		template<typename T>
		static void ctor(t_Val*p, const T& x){ new (p) t_Val(x); }
		template<typename T>
		static void ctor(t_Val*p, t_Val*end, const T*from){ for(;p<end;p++) new (p) t_Val(*from++); }
		template<typename T>
		static void copy(t_Val*p, t_Val*end, const T*from){ for(;p<end;p++,from++)*p = *from; }
		static void dtor(t_Val& x){ x.~t_Val(); }
		static void dtor(t_Val*p, t_Val*end){ for(;p<end;p++) p->~t_Val(); }
	};
		template<typename t_Val>
		struct _xtor<false, t_Val>
		{	static void ctor(t_Val*p){}
			static void ctor(t_Val*p, t_Val*end){}
			template<typename T>
			static void ctor(t_Val*p, t_Val*end, const T& x){ for(;p<end;p++)*p = (t_Val)x; }
			static void ctor(t_Val*p, t_Val*end, const t_Val*from){ memcpy(p, from, ((LPBYTE)end - (LPBYTE)p)); }
			template<typename T>
			static void ctor(t_Val*p, t_Val*end, const T*from){ for(;p<end;p++,from++)*p = (t_Val)*from; }
			static void ctor(t_Val*p, const t_Val& x){ rt::Copy(*p, x); }
			template<typename T>
			static void ctor(t_Val*p, const T& x){ *p = (t_Val)x; }
			template<typename T>
			static void copy(t_Val*p, t_Val*end, const T*from){ ctor(p, end, from); }
			static void dtor(t_Val& x){}
			static void dtor(t_Val*p, t_Val*end){}
		};
};

namespace _details
{
template<typename t_Val_, typename t_Index_ = SIZE_T>
struct BufStgRef
{
	typedef t_Val_		t_Val;
	typedef t_Index_	t_Index;
protected:
	t_Val*	_p = nullptr;
public:
	t_Val*	begin(){ return _p; }
	auto*	begin() const { return (const t_Val*)_p; }
};
template<uint32_t EmbeddableSize, typename t_Val_, typename t_Index_ = SIZE_T>
struct BufStgRefEmbeddable
{
	typedef t_Val_		t_Val;
	typedef t_Index_	t_Index;
protected:
	union {
	t_Val*	_p;
	t_Val	_e[EmbeddableSize];
	};
	t_Index	_len_reserved = EmbeddableSize;
	bool	_is_embedded() const { return _len_reserved == EmbeddableSize; }
	BufStgRefEmbeddable(){ _p = nullptr; }
	~BufStgRefEmbeddable(){}
public:
	t_Val*	begin(){ return _is_embedded()?_e:_p; }
	auto*	begin() const { return (const t_Val*)(_is_embedded()?_e:_p); }
};
template<uint32_t FixedSize, typename t_Val_, typename t_Index_ = SIZE_T>
struct BufStgRefFixed
{
	typedef t_Val_		t_Val;
	typedef t_Index_	t_Index;
	static const t_Index _len_reserved = FixedSize;
private:
	t_Val	_e[FixedSize];
public:
	t_Val*	begin(){ return _e; }
	auto*	begin() const { return (const t_Val*)_e; }
};
} // namespace _details

template<typename t_BufStgRef>
class BufferOpBase_Ref: public t_BufStgRef
{	
	typedef t_BufStgRef _SC;
public:
	typedef typename _SC::t_Val		t_Val;
	typedef typename _SC::t_Index	t_Index;
	typedef t_Val*					t_ValPtr;
	typedef const t_Val*			t_ConstValPtr;

protected:
	static const bool IsElementNotPOD = !rt::TypeTraits<t_Val>::IsPOD;
	typedef _details::_xtor<!rt::TypeTraits<t_Val>::IsPOD, t_Val> _xt;
	typedef int (* _PtFuncCompare)(const void *, const void *);
	typedef typename rt::TypeTraits<t_Index>::t_Signed	t_SignedIndex;

	t_Index			_len = 0;
	t_Val*			_ptr(){ return _SC::begin(); }
	auto*			_ptr() const { return _SC::begin(); }

public:
	auto*			Begin()const { return _ptr(); }
	auto*			Begin(){ return _ptr(); }
	auto*			End()const { return _ptr() + _len; }
	auto*			End(){ return _ptr() + _len; }
	t_Index			GetSize() const { return _len; }

	t_Val&			First(){ ASSERT(_len); return *_ptr(); }
	const t_Val&	First() const { ASSERT(_len); return *_ptr(); }
	t_Val&			Last(){ ASSERT(_len); return _ptr()[_len-1]; }
	const t_Val&	Last() const { ASSERT(_len); return _ptr()[_len-1]; }

	operator		t_ValPtr(){ return _ptr(); }
	operator		t_ConstValPtr()const { return _ptr(); }
	operator		LPVOID(){ return _ptr(); }
	operator		LPCVOID()const { return _ptr(); }

public:
	t_Val*			end(){ return End(); }///< allow for(iterator : Buffer) syntax (C++ 11)
	const t_Val*	end() const { return End(); }///< allow for(iterator : Buffer) syntax (C++ 11)
	t_Val&			first(){ ASSERT(_len); return *_ptr(); }
	const t_Val&	first()const{ ASSERT(_len); return *_ptr(); }
	t_Val&			last(){ ASSERT(_len); return _ptr()[_len-1]; }
	const t_Val&	last()const{ ASSERT(_len); return _ptr()[_len-1]; }

	bool			IsPointerAliasing(LPCVOID p) const { return (t_Val*)p >= _ptr() && (t_Val*)p < end(); }
	template<typename T>
	void			Set(const T& x){ t_Val*	end = _ptr() + _len; for(t_Val* p = _ptr(); p < end; p++)*p = x; }
	template<typename T>
	t_Val&			operator [](T i){ ASSERT(((t_Index)i)<=_len); return _ptr()[i]; }
	template<typename T>
	const t_Val&	operator [](T i) const { ASSERT(((t_Index)i)<=_len); return _ptr()[i]; }
	template<typename STG>
	void			CopyFrom(const BufferOpBase_Ref<STG>& x)
					{	ASSERT(GetSize() == x.GetSize());
						auto* p = _ptr();	auto* end = p + _len;
						auto* y = x.Begin();
						for(; p<end; p++, y++)
							*p = *y;
					}
	void			CopyFrom(const std::initializer_list<t_Val>& x)
					{	ASSERT(GetSize() == x.size());
						auto* p = _ptr();
						for(auto v : x)*p++ = v;
					}
	template<typename T>
	void			CopyFrom(const T* x)
					{	auto* p = _ptr();	auto* end = p + _len;
						for(; p<end; p++, x++)*p = *x;
					}
	template<typename T>
	void			CopyTo(T* x) const
					{	auto* p = _ptr();	auto* end = p + _len;
						for(; p<end; p++, x++)*x = *p;
					}
	void			CopyFrom(const t_Val* x){ _details::_xtor<IsElementNotPOD, t_Val>::copy(_ptr(), end(), x); }
	void			CopyTo(t_Val* x) const { _details::_xtor<IsElementNotPOD, t_Val>::copy(x, x + _len, _ptr()); }
	template<typename STG>
	bool			operator == (const BufferOpBase_Ref<STG>& x) const
					{	if(x.GetSize() != GetSize())return false;
						auto* p = _ptr();	auto* end = p + _len;
						auto* y = x._ptr();
						for(; p<end; p++, y++)
							if(*p != *y)return false;
						return true;
					}
	template<typename STG>
	bool operator !=(const BufferOpBase_Ref<STG>& x) const { return !(*this == x); }

	t_Val&			MaxValue()
					{	ASSERT(GetSize());		auto* mp = _ptr();
						for(t_Index i=1;i<GetSize();i++)if(*mp < _ptr()[i]){ mp = &_ptr()[i]; }
						return *mp;
					}
	const t_Val&	MaxValue() const { return rt::_CastToNonconst(this)->MaxValue(); }
	t_SignedIndex	Max() const
					{	if(GetSize())
						{	auto* mp = _ptr();	t_SignedIndex m = 0;
							for(t_Index i=1;i<GetSize();i++)if(*mp < _ptr()[i]){ mp = &_ptr()[i]; m = i; }
							return m;
						}else return -1;
					}
	t_Val&			MinValue()
					{	ASSERT(GetSize());		auto* mp = _ptr();
						for(t_Index i=1;i<GetSize();i++)if(_ptr()[i] < *mp){ mp = &_ptr()[i]; }
						return *mp;
					}
	const t_Val&	MinValue() const { return rt::_CastToNonconst(this)->MinValue(); }
	t_SignedIndex	Min() const
					{	if(GetSize())
						{	auto* mp = _ptr();	t_SignedIndex m = 0;
							for(t_Index i=1;i<GetSize();i++)if(_ptr()[i] < *mp){ mp = &_ptr()[i]; m = i; }
							return m;
						}else return -1;
					}
	///< binary search
	t_SignedIndex	SearchSortedItem(const t_Val& x) const { return std::find(Begin(), End(), x) - Begin(); }
	//< binary search
	t_SignedIndex	SearchLowerbound(const t_Val& x) const { return std::lower_bound(Begin(), End(), x) - Begin(); }
	void			Zero(){ static_assert(rt::TypeTraits<t_Val>::IsPOD); memset((LPVOID)_ptr(), 0, _len*sizeof(t_Val)); }
	void			Void(){ static_assert(rt::TypeTraits<t_Val>::IsPOD); memset((LPVOID)_ptr(), 0xff, _len*sizeof(t_Val)); }
	template<class TFUNC>
	void			Sort(TFUNC&& comp){ std::sort(Begin(), End(), comp); }
	void			Sort(){ std::sort(Begin(), End()); }
	void			SortDesc(){ std::sort(Begin(), End(), [](const t_Val& a, const t_Val& b){ return a > b; }); }
	void			Shuffle(DWORD seed)
					{	if(GetSize())
						{	Randomizer rng(seed);	
							for(t_Index i=0;i<GetSize()-1;i++)
								rt::Swap((*this)[i], (*this)[i+ rng%(GetSize()-i)]);
						}
					}
	t_SignedIndex	PushSorted(const t_Val& x) ///< last item will be dropped
					{	if(GetSize() == 0 || Last() < x)return -1;
						_xt::dtor(Last());
						auto* p = &Last();
						for(p--; p>=Begin(); p--)
						{	if(x < *p){ rt::Copy(p[1], *p); }
							else break;
						}
						p++;
						_xt::ctor(p, x);
						return p - Begin();
					}
	/**
	 * @brief Find Top-k Smallest value over unordered array (original values will be moved around)
	 * 
	 * https://www.geeksforgeeks.org/kth-smallestlargest-element-unsorted-array/  [ Method 4 (QuickSelect) ]
	 * @param k 
	 * @return t_Val& 
	 */
	t_Val&			FindTopKth(t_Index k)
					{	struct _Find	
						{	static t_Index partition(t_Val* arr, t_Index l, t_Index r) 
							{	rt::Swap(arr[(l + r) / 2], arr[r]);
								t_Val x(arr[r]);
								t_Index i = l;		// all elements left to i are less than or equal to x
								for(t_Index j = l; j < r; j++) 
								{ 	if(x < arr[j])continue;
									rt::Swap(arr[i], arr[j]);
									i++; 
								} 
								rt::Swap(arr[i], arr[r]);
								return i; 
							} 		
							static t_Val& kth(t_Val* arr, t_Index l, t_Index r, t_Index k)
							{	if(k > 0 && k <= r - l + 1) 
								{ 	t_Index pos = partition(arr, l, r); 
									if (pos-l == k-1) 
										return arr[pos]; 
									if (pos-l > k-1)
										return kth(arr, l, pos-1, k); 
									return kth(arr, pos+1, r, k-pos+l-1);
								} 
								ASSERT(0);	// k is more than number of elements in array 
								return arr[0];
							}
						};
						ASSERT(k>0);
						ASSERT(GetSize() >= k);
						return _Find::kth(_ptr(), 0, GetSize()-1, k);
					}
	void			RandomBits(DWORD seed = rand())
					{	static_assert(rt::TypeTraits<t_Val>::IsPOD);
						Randomizer(seed).Randomize(Begin(), GetSize()*sizeof(t_Val));
					}
	template<typename T>
	t_SignedIndex	Find(const T& v) const
					{	auto* p = _ptr();	auto* end = p + _len;
						t_SignedIndex i=0;
						for(; p<end; p++,i++)
							if(*p == v)return i;
						return -1;
					}
protected:
	template<typename T, typename visitor>
	t_Index			_ForEach(T& x, const visitor& v)
					{	t_Index i=0;
						auto* p = x._ptr();
						for(; i<x.GetSize(); i++, p++)
						{	if(!rt::_details::_CallLambda<bool, decltype(v(*p,i,x.GetSize()))>(true, v, *p, i, x.GetSize()).retval)
								return i+1;
						}
						return i;
					}
public:
	/**
	 * @brief v(obj, idx, tot)
	 * 
	 * @tparam visitor 
	 * @param v 
	 * @return SIZE_T 
	 */
	template<typename visitor>
	t_Index			ForEach(const visitor& v){ return _ForEach(*this, v); }
	/**
	 * @brief v(const obj, idx, tot)
	 * 
	 * @tparam visitor 
	 * @param v 
	 * @return SIZE_T 
	 */
	template<typename visitor>
	t_Index			ForEach(const visitor& v) const { return _ForEach(*this, v); }
};

template<typename t_Val, typename t_Index = SIZE_T>
class Buffer_Ref: public BufferOpBase_Ref<_details::BufStgRef<t_Val, t_Index>>
{
	typedef BufferOpBase_Ref<_details::BufStgRef<t_Val, t_Index>> _SC;
public:
	Buffer_Ref() = default;
	Buffer_Ref(const Buffer_Ref& x){ _SC::_p = x._p; _SC::_len = x._len; }
	Buffer_Ref(const t_Val*	p, t_Index len){ _SC::_p = (t_Val*)p; _SC::_len = len; }
	Buffer_Ref			GetSub(t_Index start, t_Index size){ ASSERT(start + size<=_SC::_len); return Buffer_Ref(_SC::_p+start, size); }
	const Buffer_Ref	GetSub(t_Index start, t_Index size) const { ASSERT(start + size<=_SC::_len); return Buffer_Ref(_SC::_p+start, size); }
};

namespace _details
{

template<typename t_Val, typename t_Index>
inline t_Val* BufStgReserve(t_Index& buf_resv_size, const t_Val* old, t_Index old_size, t_Index new_size, t_Index new_size_compact)
{
	ASSERT(new_size >= new_size_compact);
	ASSERT(new_size_compact > 0);
	auto* new_buf = _Malloc32AL(t_Val, new_size);
	if(new_buf == nullptr)
	{
		if(new_size == new_size_compact)return nullptr;
		new_size = new_size_compact;
		new_buf = _Malloc32AL(t_Val, new_size);
		if(new_buf == nullptr)return nullptr;
	}

	memcpy(new_buf, old, old_size*sizeof(t_Val));
	buf_resv_size = new_size;
	return new_buf;
}

template<uint32_t FixedSize, typename t_Val, typename t_Index = SIZE_T>
class BufStgFixed: public BufferOpBase_Ref<_details::BufStgRefFixed<FixedSize, t_Val, t_Index>>
{
protected:
	typedef BufferOpBase_Ref<_details::BufStgRefFixed<FixedSize, t_Val, t_Index>> _SC;
	using typename _SC::_xt;
	BufStgFixed() = default;
	~BufStgFixed(){ _xt::dtor(_SC::_ptr(), _SC::_ptr() + _SC::_len); }
	bool	_expand_entries(t_Index co = 1) // the newly added entry's ctor will not be called !!
			{	if(_SC::_len_reserved >= _SC::_len + co){ _SC::_len += co; return true; }
				return false;
			}
public:
	t_Index	reserve_size() const { return (t_Index)FixedSize; }
	void	compact_memory(){}
	bool	reserve(t_Index co){ return co<=(t_Index)FixedSize; }
	t_Val*	Detach(){ ASSERT(0); }
};

template<typename t_Val, typename t_Index = SIZE_T>
class BufStgDynamic: public Buffer_Ref<t_Val, t_Index>
{
protected:
	typedef Buffer_Ref<t_Val, t_Index> _SC;
	using typename _SC::_xt;
	BufStgDynamic() = default;
	~BufStgDynamic(){ if(_SC::_p){ _xt::dtor(_SC::_p, _SC::_p + _SC::_len); _SafeFree32AL(_SC::_p); } }
public:
	t_Index	reserve_size() const { return _SC::_len; }
	void	compact_memory(){}
	bool	reserve(t_Index co)
			{	if(co > _SC::_len)
				{	auto* new_buf = _Malloc32AL(t_Val, co);
					if(!new_buf)return false;
					memcpy(new_buf, _SC::_p, _SC::_len*sizeof(t_Val));
					rt::Swap(_SC::_p, new_buf);
					_SafeFree32AL_ConstPtr(new_buf);
				}
				return true;
			}
	t_Val*	Detach(){ auto* ret = _SC::_p; rt::Zero(*this); return ret; }
protected:
	bool	_expand_entries(t_Index co = 1) // the newly added entry's ctor will not be called !!
			{	if(co) // expand buffer
				{	if(!reserve(co + _SC::_len))return false;
					_SC::_len+=co;
				}
				return true;
			}
};

template<typename t_Val, typename t_Index = SIZE_T>
class BufStgAdjustable: public Buffer_Ref<t_Val, t_Index>
{
protected:
	typedef Buffer_Ref<t_Val, t_Index> _SC;
	using typename _SC::_xt;
	t_Index	_len_reserved = 0;
	bool	_Reallocate(t_Index new_size, t_Index new_size_compact)
			{	auto* new_buf = BufStgReserve(_len_reserved, _SC::_p, _SC::_len, new_size, new_size_compact);
				if(!new_buf)return false;
				rt::Swap(new_buf, _SC::_p);
				_SafeFree32AL_ConstPtr(new_buf);
				return true;
			}
	BufStgAdjustable() = default;
	~BufStgAdjustable(){ if(_SC::_p){ _xt::dtor(_SC::_p, _SC::_p + _SC::_len); _SafeFree32AL(_SC::_p); } }
	bool	_expand_entries(t_Index co = 1) // the newly added entry's ctor will not be called !!
			{	if(_SC::_len+co <= _len_reserved){} // expand elements only
				else // expand buffer
				{	if(!_Reallocate(rt::max(rt::max((t_Index)4, _SC::_len+co), _len_reserved*2), _SC::_len + co))
						return false;
				}
				_SC::_len+=co;
				return true;
			}
public:
	t_Index	reserve_size() const { return _len_reserved; }
	void	compact_memory()
			{	if(_SC::_len < _len_reserved)
				{	auto* pNew = _Malloc32AL(t_Val, _SC::_len);
					if(pNew)
					{	memcpy(pNew,_SC::_p,sizeof(t_Val)*_SC::_len);
						_SafeFree32AL(_SC::_p);
						_SC::_p = pNew;
						_len_reserved = _SC::_len;
					}
				}
			};
	bool	reserve(t_Index co)
			{	if(co > _len_reserved && !_Reallocate(co, co))
					return false;
				return true;
			}
	t_Val*	Detach(){ auto* ret = _SC::_p; rt::Zero(*this); return ret; }
};

template<uint32_t EmbeddableSize, typename t_Val, typename t_Index = SIZE_T>
class BufStgEmbeddable: public BufferOpBase_Ref<_details::BufStgRefEmbeddable<EmbeddableSize, t_Val, t_Index>>
{
protected:
	typedef BufferOpBase_Ref<_details::BufStgRefEmbeddable<EmbeddableSize, t_Val, t_Index>> _SC;
	using typename _SC::_xt;
	bool	_Reallocate(t_Index new_size, t_Index new_size_compact)
			{	auto* old_buf = _SC::_ptr();
				auto* new_buf = BufStgReserve(_SC::_len_reserved, old_buf, _SC::_len, new_size, new_size_compact);
				if(!new_buf)return false;
				_SC::_p = new_buf;
				if(old_buf != (t_Val*)_SC::_e)_SafeFree32AL_ConstPtr(old_buf);
				return true;
			}
	BufStgEmbeddable() = default;
	~BufStgEmbeddable(){ _xt::dtor(_SC::_ptr(), _SC::end()); if(!_SC::_is_embedded())_SafeFree32AL(_SC::_p); }
	bool	_expand_entries(t_Index co = 1) // the added entry's ctor is not called !!
			{	if(_SC::_len+co <= _SC::_len_reserved){} // expand elements only
				else // expand buffer
				{	if(!_Reallocate(rt::max(rt::max((t_Index)4, _SC::_len+co), _SC::_len_reserved*2), _SC::_len + co))
						return false;
				}
				_SC::_len+=co;
				return true;
			}
public:
	t_Index	reserve_size() const { return _SC::_len_reserved; }
	void	compact_memory()
			{	if(_SC::_len < _SC::_len_reserved && !_SC::_is_embedded())
				{	if(_SC::_len > EmbeddableSize)
					{	auto* pNew = _Malloc32AL(t_Val, _SC::_len);
						if(pNew)
						{	memcpy(pNew, _SC::_p, sizeof(t_Val)*_SC::_len);
							_SC::_len_reserved = _SC::_len;
							rt::Swap(pNew, _SC::_p);
							_SafeFree32AL(pNew);
						}
					}
					else
					{	auto* old = _SC::_p; // back to embedded
						_SC::_len_reserved = EmbeddableSize;
						memcpy(_SC::_e, old, sizeof(t_Val)*_SC::_len);
						_SafeFree32AL(old);
					}
				}
			};
	bool	reserve(t_Index co)
			{	if(co > _SC::_len_reserved && !_Reallocate(co, co))
					return false;
				return true;
			}
	t_Val*	Detach(){ ASSERT(0); }
};

} // namespace _details

template<typename t_BufStg>
class BufferOpBase: public t_BufStg
{
	typedef t_BufStg _SC;
	typedef typename _SC::t_Val		t_Val;
	typedef typename _SC::t_Index	t_Index;
	typedef Buffer_Ref<t_Val, t_Index>	t_BufRef;
public:
	BufferOpBase() = default;
	BufferOpBase(const BufferOpBase &x){ *this = x; }
	BufferOpBase(const t_BufRef &x){ *this = x; }
	BufferOpBase(BufferOpBase &&x){ rt::Copy(*this, x); rt::Zero(x); }
	t_BufRef		GetSub(t_Index start, t_Index size){ ASSERT(start + size<=_SC::_len); return Buffer_Ref(_SC::begin()+start, size); }
	const t_BufRef	GetSub(t_Index start, t_Index size) const { ASSERT(start + size<=_SC::_len); return Buffer_Ref(_SC::begin()+start, size); }

public: // resizing
	void	ShrinkSize(t_Index new_size)	// no expand
			{	if(new_size >= _SC::_len)return;
				if(new_size<_SC::_len)
				{	auto* p = _SC::_ptr();
					_SC::_xt::dtor(p + new_size, p + _SC::_len); //call dtor for unwanted instances at back
					_SC::_len = new_size;
				}
			}
	template<typename ... ARGS>
	bool	ExpandSizeWith(t_Index new_size, ARGS... ctor_args)	// no shrink
			{	if(new_size <= _SC::_len)return true;
				if(!_SC::reserve(new_size))return false;
				_SC::_xt::ctor(_SC::_ptr() + _SC::_len, _SC::_ptr() + new_size, ctor_args...);
				_SC::_len = new_size;
				return true;
			}
	bool	ExpandSize(t_Index new_size){ return ExpandSizeWith(new_size); }
	template<typename ... ARGS>
	bool	ChangeSizeWith(SIZE_T new_size, ARGS... ctor_args) ///< Original data at front are preserved
			{	if(new_size<=_SC::_len){ ShrinkSize(new_size); return true; }
				else return ExpandSizeWith(new_size, ctor_args...);
			}
	bool	ChangeSize(t_Index new_size){ return ChangeSizeWith(new_size); } ///< Original data at front are preserved
	template<typename ... ARGS>
	bool	SetSizeWith(t_Index co, ARGS && ... ctor_args) ///< Original data at front are NOT preserved
			{	if(co<=_SC::_len)
				{	ShrinkSize(co);
					_SC::_xt::dtor(_SC::_ptr(), _SC::end());
					_SC::_xt::ctor(_SC::_ptr(), _SC::end(), ctor_args...);
					return true;
				}
				else{ ShrinkSize(0); return ExpandSizeWith(co, ctor_args...);  }
			}
	bool	SetSize(t_Index co=0){ return SetSizeWith(co); } ///< Original data at front are NOT preserved
	auto	GetSize() const { return _SC::GetSize(); } ///< make Visual Studio happy
	void	Clear(){ SetSize(0); }
	t_Val*	Detach(bool maintain_reserve_size = false)
			{	if(_SC::_len == 0)return nullptr;
				auto recv_size = _SC::reserve_size();
				auto* p = _SC::Detach(); ASSERT(p);		
				if(maintain_reserve_size)_SC::reserve(recv_size);
				return p;
			}
	auto&	operator = (const t_BufRef &x)
			{	ShrinkSize(x.GetSize());
				t_Index sz = GetSize();
				_SC::CopyFrom(x.GetSub(0, sz));
				if(sz == x.GetSize())return *this;
				VERIFY(_SC::_expand_entries(x.GetSize() - sz));
				_SC::_xt::ctor(_SC::_ptr() + sz, _SC::_ptr() + x.GetSize(), &x[sz]);
				return *this;
			}
	auto&	operator = (const BufferOpBase &x){ return *this = (const Buffer_Ref<t_Val, t_Index>&)x; }
	auto&	operator = (const std::initializer_list<t_Val>& x)
			{	VERIFY(SetSize(x.size()));
				_SC::CopyFrom(x);
				return x;
			}

public: // operations
	t_Index	Remove(const t_Val& v)
			{	t_Index open = 0;
				auto* p = _SC::_ptr();
				for(t_Index i=0; i<_SC::_len; i++)
					if(!(p[i] == v))
					{	if(i != open)
						{	_SC::_xt::dtor(p[open]);
							rt::Copy(p[open], p[i]);
						}
						open++;
					}
				t_Index ret = _SC::_len - open;
				_SC::_len = open;
				return ret;
			}
	t_Val&	push_front()
			{	VERIFY(_SC::_expand_entries());
				memmove(_SC::_ptr() + 1, _SC::_ptr(), sizeof(t_Val)*(_SC::_len-1));
				_SC::_xt::ctor(_SC::_ptr());
				return _SC::_ptr()[0];
			}
	template<typename T>
	t_Val&	push_front(const T& x)
			{	VERIFY(_SC::_expand_entries());
				memmove(_SC::_ptr()+1,_SC::_ptr(),sizeof(t_Val)*(_SC::_len-1));
				_SC::_xt::ctor(_SC::_ptr(), x);
				return *_SC::_ptr();
			}
	t_Val&	push_front(const t_Val& x){ return push_front<t_Val>(x); }
	template<typename T>
	void	push_front(const T* x, t_Index count)
			{	if(count == 0)return;
				t_Index sz = _SC::GetSize();
				VERIFY(_SC::_expand_entries(count));
				memmove(_SC::_ptr() + count, _SC::_ptr(), sizeof(t_Val)*sz);
				_SC::_xt::ctor(_SC::_ptr(), _SC::_ptr() + count, x);
			}
	template<typename T>
	void	push_front(const T& x, t_Index count)
			{	if(count == 0)return;
				SIZE_T sz = _SC::GetSize();
				VERIFY(_SC::_expand_entries(count));
				memmove(&_SC::_ptr()[count],_SC::_ptr(),sizeof(t_Val)*sz);
				_SC::_xt::ctor(_SC::_ptr(), _SC::_ptr() + count, x);
			}
	void	push_front(const t_Val& x, t_Index count){ push_front<t_Val>(x, count); }
	template<typename T>
	void	push_both(const T& x, t_Index front_count, t_Index back_count)
			{	if(front_count + back_count == 0)return;
				SIZE_T sz = _SC::GetSize();
				VERIFY(ChangeSize(sz + front_count + back_count));
				memmove(&_SC::_ptr()[front_count],_SC::_ptr(),sizeof(t_Val)*sz);
				_SC::_xt::ctor(_SC::_ptr(), _SC::_ptr() + front_count, x);
				_SC::_xt::ctor(_SC::_ptr()+sz+front_count, _SC::end(), x);
			}
	void	push_both(const t_Val& x, t_Index front_count, t_Index back_count){ push_both<t_Val>(x, front_count, back_count); }
	t_Val&	push_back()
			{	VERIFY(_SC::_expand_entries());
				t_Val& x = _SC::_ptr()[_SC::_len-1];
				_SC::_xt::ctor(&x);
				return x;
			}
	template<typename T>
	t_Val&	push_back(const T& x)
			{	VERIFY(_SC::_expand_entries());
				t_Val& ret = _SC::_ptr()[_SC::_len-1];
				_SC::_xt::ctor(&ret, x);
				return ret;
			}
	t_Val&	push_back(const t_Val& x){ return push_back<t_Val>(x); }
	template<typename ... ARGS>
	t_Val&	push_back_with(ARGS && ... ctor_args)
			{	VERIFY(_SC::_expand_entries());
				t_Val& ret = _SC::_ptr()[_SC::_len-1];
				new (&ret) t_Val(ctor_args ...);
				return ret;
			}
	template<typename T>
	void	push_back(const T* x, t_Index count)
			{	t_Index sz = _SC::GetSize();
				VERIFY(_SC::_expand_entries(count));
				_SC::_xt::ctor(_SC::_ptr()+sz, _SC::end(), x);
			}
	t_Val*	push_back_n(t_Index count)
			{	t_Index sz = _SC::GetSize();
				return ChangeSize(sz + count)?(_SC::_ptr()+sz):nullptr;
			}
	template<typename T>
	void	push_back_n(const T& x, t_Index count)
			{	t_Index sz = _SC::GetSize();
				VERIFY(_SC::_expand_entries(count));
				_SC::_xt::ctor(_SC::_ptr()+sz, _SC::end(), x);
			}
	void	push_back_n(const t_Val& x, t_Index count){ push_back_n<t_Val>(x, count); }

	/**
	 * @brief sizeof T should be multiple of size of t_Val
	 * 
	 * @tparam T 
	 * @return T& 
	 */
	template<typename T>
	T&		push_back_pod() 
			{	ASSERT(sizeof(T)%sizeof(t_Val) == 0);
				static_assert(rt::TypeTraits<T>::IsPOD && rt::TypeTraits<t_Val>::IsPOD, "push_back_pod takes only POD types");
				return *(T*)push_back_n(sizeof(T)/sizeof(t_Val));
			}
	template<typename T>
	void	push_back_pod(const T& obj){ rt::Copy(push_back_pod<T>(), obj); }
	void	pop_back()
			{	ASSERT(_SC::_len);
				_SC::_len--;
				_SC::_xt::dtor(*_SC::end());
			}
	void	pop_front()
			{	ASSERT(_SC::_len);
				_SC::_len--;
				_SC::_xt::dtor(*_SC::_ptr());
				memmove(_SC::_ptr(), _SC::_ptr()+1, sizeof(t_Val)*_SC::_len);
			}
	void	erase(t_Index index)
			{	ASSERT(index<_SC::_len);
				// call dtor for removed items
				_SC::_xt::dtor(_SC::_ptr()[index]);
				_SC::_len--;
				memmove(_SC::_ptr()+index, _SC::_ptr()+index+1, sizeof(t_Val)*(_SC::_len-index));
			}
	void	erase(t_Index index_begin, t_Index index_end) ///< [index_end] will not be erased
			{	ASSERT(index_begin<=index_end);
				ASSERT(index_end<=_SC::_len);
				_SC::_xt::dtor(_SC::_ptr()+index_begin, _SC::_ptr()+index_end);
				memmove(_SC::_ptr()+index_begin, _SC::_ptr()+index_end, sizeof(t_Val)*(_SC::_len-index_end));
				_SC::_len-=(index_end-index_begin);
			}
	void	erase(const t_Val* p)
			{	ASSERT(p < _SC::End());
				ASSERT(p >= _SC::Begin());
				erase((t_Index)(p - _SC::Begin()));
			}
	void	erase(const t_Val* begin, const t_Val* end) ///< *end will not be erased
			{	ASSERT(begin <= end);
				ASSERT(begin >= _SC::begin());
				ASSERT(end <= _SC::end());
				erase((t_Index)(begin - _SC::begin()), (t_Index)(end - _SC::end()));
			}
	t_Val&	insert(t_Index index)
			{	VERIFY(_SC::_expand_entries());
				if(index<_SC::_len-1)
					memmove(_SC::_ptr()+index+1, _SC::_ptr()+index, (_SC::_len-index-1)*sizeof(t_Val));
				auto& ret = _SC::_ptr()[index];
				_SC::_xt::ctor(&ret);
				return ret;
			}
	template<typename T>
	t_Val&	insert(t_Index index, const T& x)
			{	VERIFY(_SC::_expand_entries());
				if(index<_SC::_len-1)
					memmove(_SC::_ptr()+index+1, _SC::_ptr()+index, (_SC::_len-index-1)*sizeof(t_Val));
				auto& ret = _SC::_ptr()[index];
				_SC::_xt::ctor(&ret, x);
				return ret;
			}
	t_Val*	insert_n(t_Index index, t_Index count)
			{	if(_SC::reserve(_SC::_len + count))
				{	memmove(_SC::_ptr()+index+count, _SC::_ptr()+index, (_SC::_len-index)*sizeof(t_Val));
					_SC::_xt::ctor(_SC::_ptr()+index, _SC::_ptr()+index+count);
					_SC::_len += count;
					return _SC::_ptr()+index;
				}	
				return nullptr;
			}
	template<typename T>
	void	insert_n(t_Index index, t_Index count, const T& x)
			{	VERIFY(_SC::reserve(_SC::_len + count));
				memmove(_SC::_ptr()+index+count, _SC::_ptr()+index, (_SC::_len-index)*sizeof(t_Val));
				_SC::_xt::ctor(_SC::_ptr()+index, _SC::_ptr()+index+count, x);
				_SC::_len += count;
			}
	template<typename T>
	void	insert_n(t_Index index, t_Index count, const T* x)
			{	VERIFY(_SC::reserve(_SC::_len + count));
				memmove(_SC::_ptr()+index+count, _SC::_ptr()+index, (_SC::_len-index)*sizeof(t_Val));
				_SC::_xt::ctor(_SC::_ptr()+index, _SC::_ptr()+index+count, x);
				_SC::_len += count;
			}
public:
	template<typename T>
	SSIZE_T PushSorted(const T& x)
	{
		if(GetSize() == 0 || x<_SC::first()){ push_front(x); return 0; }
		if(_SC::reserve_size() == _SC::GetSize() && !_SC::reserve(_SC::GetSize()*2 + 1))return -1;
		_SC::_len++;
		auto* p = &_SC::Last();
		for(p--;;p--)
		{	if(x < *p){ rt::Copy(p[1], *p); }
			else break;
		}
		p++;
		_SC::_xt::ctor(p, x);
		return p - _SC::Begin();
	}
	SSIZE_T PushSortedWithMove(t_Val&& x)  // move the instance instead of copying, `x` will be an empty one
	{
		if(GetSize() == 0 || x<_SC::first())
		{	VERIFY(_SC::_expand_entries());
			_SC::_xt::ctor(_SC::_ptr());
			rt::Swap(*_SC::_ptr(), x);
			return 0;
		}
		if(_SC::reserve_size() == _SC::GetSize() && !_SC::reserve(_SC::GetSize()*2 + 1))return -1;
		_SC::_len++;
		auto* p = &_SC::Last();
		for(p--;;p--)
		{	if(x < *p){ rt::Copy(p[1], *p); }
			else break;
		}
		p++;
		_SC::_xt::ctor(p);
		rt::Swap(*p, x);
		return p - _SC::Begin();
	}
	template<typename compr_less>
	SSIZE_T PushSorted(const t_Val& x, const compr_less& compr)
	{
		if(GetSize() == 0 || compr(x, _SC::first())){ push_front(x); return 0; }
		if(_SC::reserve_size() == _SC::GetSize() && !_SC::reserve(_SC::GetSize()*2 + 1))return -1;
		_SC::_len++;
		auto* p = &_SC::Last();
		for(p--;;p--)
		{	if(compr(x, *p)){ rt::Copy(p[1], *p); }
			else break;
		}
		p++;
		_SC::_xt::ctor(p, x);
		return p - _SC::Begin();
	}
	t_Index PushUnique(const t_Val& x)
	{	auto idx = _SC::Find(x);
		if(idx>=0)return idx;
		push_back(x);
		return _SC::GetSize() - 1;
	}
};

// no reserve_size O(n) memory allocation for linear push, memory compact
template<typename T>
using Buffer = BufferOpBase<_details::BufStgDynamic<T>>;

// has reserve_size O(logn) memory allocation for linear push, 2x memory amplification
template<typename T>
using BufferEx = BufferOpBase<_details::BufStgAdjustable<T>>;

// has reserve_size O(logn) memory allocation for linear push, 2x memory amplification, with small array optimization (avoids memory allocation)
template<typename T, uint32_t EmbeddableSize = 2>
using BufferEm = BufferOpBase<_details::BufStgEmbeddable<EmbeddableSize, T>>;

// fixed reserve_size, no memory allocation
template<typename T, uint32_t Size>
using BufferFx = BufferOpBase<_details::BufStgFixed<Size, T>>;

#define TYPETRAITS_BUFFER(BUFCLS)	template<typename T>							\
									class TypeTraits<BUFCLS<T>>						\
									{public:										\
										typedef BUFCLS<T> t_Val;					\
										typedef T t_Element;						\
										typedef BUFCLS<T> t_Signed;					\
										typedef BUFCLS<T> t_Unsigned;				\
										static const int Typeid = _typeid_buffer;	\
										static const bool IsPOD = false;			\
										static const bool IsNumeric = false;		\
									};
TYPETRAITS_BUFFER(Buffer)
TYPETRAITS_BUFFER(BufferEx)
#undef TYPETRAITS_BUFFER

#define TYPETRAITS_BUFFER(BUFCLS)	template<typename T, uint32_t SIZE>				\
									class TypeTraits<BUFCLS<T,SIZE>>				\
									{public:										\
										typedef BUFCLS<T,SIZE> t_Val;				\
										typedef T t_Element;						\
										typedef BUFCLS<T,SIZE> t_Signed;			\
										typedef BUFCLS<T,SIZE> t_Unsigned;			\
										static const int Typeid = _typeid_buffer;	\
										static const bool IsPOD = false;			\
										static const bool IsNumeric = false;		\
									};
TYPETRAITS_BUFFER(BufferEm)
TYPETRAITS_BUFFER(BufferFx)
#undef TYPETRAITS_BUFFER

template<class t_Ostream, typename t_Stg>
t_Ostream& operator<<(t_Ostream& Ostream, const _details::_LOG_FULLDATA<rt::BufferOpBase_Ref<t_Stg>> & vec)
{	typedef typename t_Stg::t_Val t_Ele;
	Ostream<<'{';	
	if(rt::TypeTraits<typename rt::TypeTraits<t_Ele>::t_Element>::Typeid == rt::_typeid_8s)
	{
		for(SIZE_T i=0;i<vec.GetSize();i++)
		{	if(i)
				Ostream<<','<<'"'<<vec[i]<<'"';
			else
				Ostream<<'"'<<vec[i]<<'"';
		}
	}
	else
	{
		for(SIZE_T i=0;i<vec.GetSize();i++)
		{	if(i)
				Ostream<<','<<vec[i];
			else
				Ostream<<vec[i];
		}
	}
	Ostream<<'}';
	return Ostream;
}

template<class t_Ostream, typename t_Stg>
t_Ostream& operator<<(t_Ostream& Ostream, const rt::BufferOpBase_Ref<t_Stg> & vec)
{	typedef typename t_Stg::t_Val t_Ele;
	if(rt::TypeTraits<typename rt::TypeTraits<t_Ele>::t_Element>::Typeid == rt::_typeid_8s)
	{
		if(vec.GetSize()>5)
		{	
			Ostream<<'{';
			for(SIZE_T i=0;i<3;i++)
				Ostream<<'"'<<vec[i]<<'"'<<',';
			Ostream<<" ... ,\"";
			Ostream<<vec.End()[-1]<<"\"} // size="<<vec.GetSize();
			return Ostream;
		}
	}
	else
	{
		if(vec.GetSize()>10)
		{	
			Ostream<<'{';
			for(SIZE_T i=0;i<8;i++)
				Ostream<<vec[i]<<',';
			Ostream<<" ... ,";
			Ostream<<vec.End()[-1]<<"} // size="<<vec.GetSize();
			return Ostream;
		}
	}

	return Ostream << rt::LOG_FULLDATA(vec);
}
} // namespace rt

namespace rt
{

namespace _details
{
template<bool has_trailing = true>
struct Trailing
{	template<typename X>
	static void Clear(X& x){ x._Bits[X::RT_BLOCK_COUNT - 1] &= (~(typename X::RT_BLOCK_TYPE)(0))>>(X::RT_BLOCK_SIZE - (X::BIT_SIZE%X::RT_BLOCK_SIZE)); }
};	
	template<> struct Trailing<false>
	{	template<typename X>
		static void Clear(X& x){};
	};

template<UINT bit_size, bool refer>
class BooleanArrayStg
{	template<bool> friend struct Trailing;
protected:
	static_assert(refer == false, "Fix-sized BooleanArray cannot be a Refer");
	typedef DWORD RT_BLOCK_TYPE;
	static const UINT	BIT_SIZE = bit_size;
	static const UINT	RT_BLOCK_SIZE = sizeof(RT_BLOCK_TYPE)*8;
	static const UINT	RT_BLOCK_COUNT = (BIT_SIZE + RT_BLOCK_SIZE - 1)/RT_BLOCK_SIZE;

	RT_BLOCK_TYPE			_Bits[RT_BLOCK_COUNT];
	void					_ClearTrailingBits(){ Trailing<(bit_size%RT_BLOCK_SIZE)!=0>::Clear(*this); }
};
template<>
class BooleanArrayStg<0, false>
{
protected:
	typedef DWORD RT_BLOCK_TYPE;
	static const UINT		RT_BLOCK_SIZE = sizeof(RT_BLOCK_TYPE)*8;
	UINT					BIT_SIZE;
	UINT					RT_BLOCK_COUNT;

	rt::BufferEx<RT_BLOCK_TYPE>_Bits;
	void					_ClearTrailingBits(){ if(RT_BLOCK_COUNT)_Bits[RT_BLOCK_COUNT - 1] &= (~(RT_BLOCK_TYPE)0)>>(RT_BLOCK_SIZE - (BIT_SIZE%RT_BLOCK_SIZE)); }
public:
	void	SetBitSize(UINT bit_size, bool keep_existing_data = true)
			{	
				BIT_SIZE = bit_size;
				RT_BLOCK_COUNT = (BIT_SIZE + RT_BLOCK_SIZE - 1)/RT_BLOCK_SIZE;
				if(keep_existing_data){ VERIFY(_Bits.ChangeSize(RT_BLOCK_COUNT)); }
				else { VERIFY(_Bits.SetSize(RT_BLOCK_COUNT)); }
				_ClearTrailingBits();
			}
};
template<>
class BooleanArrayStg<0, true>
{
protected:
	typedef DWORD RT_BLOCK_TYPE;
	static const UINT		RT_BLOCK_SIZE = sizeof(RT_BLOCK_TYPE)*8;
	UINT					BIT_SIZE;
	UINT					RT_BLOCK_COUNT;

	RT_BLOCK_TYPE*			_Bits;
	void					_ClearTrailingBits(){ if(RT_BLOCK_COUNT)_Bits[RT_BLOCK_COUNT - 1] &= (~(RT_BLOCK_TYPE)0)>>(RT_BLOCK_SIZE - (BIT_SIZE%RT_BLOCK_SIZE)); }
public:
	BooleanArrayStg(){ _Bits = nullptr; BIT_SIZE = RT_BLOCK_COUNT = 0; }
	void	Init(LPCVOID p, UINT bit_size) ///< bit_size must be multiple of 32
			{	ASSERT(bit_size%32 == 0);
				_Bits = (RT_BLOCK_TYPE*)p;
				BIT_SIZE = bit_size;
				RT_BLOCK_COUNT = (bit_size+RT_BLOCK_SIZE-1)/RT_BLOCK_SIZE;
			}
};

} // namespace _details

template<UINT bit_size = 0, bool refer = false>
class BooleanArray: public _details::BooleanArrayStg<bit_size, refer>
{
	typedef _details::BooleanArrayStg<bit_size, refer>	_SC;
    typedef typename _SC::RT_BLOCK_TYPE RT_BLOCK_TYPE;
	static const UINT RT_BLOCK_SIZE = _SC::RT_BLOCK_SIZE;
	
protected:
	static RT_BLOCK_TYPE	_BlockBitmask(UINT idx){ return ((RT_BLOCK_TYPE)1)<<(idx%RT_BLOCK_SIZE); }
public:
	class Index
	{	friend class BooleanArray;
		UINT			BlockOffset;
		RT_BLOCK_TYPE	Bitmask;
	public:
		Index(UINT idx)
		{	BlockOffset = idx/RT_BLOCK_SIZE;
			Bitmask = BooleanArray::_BlockBitmask(idx);
		}
		void operator ++(int)
		{	if(Bitmask == (1<<(RT_BLOCK_SIZE-1)))
			{	Bitmask = 1;
				BlockOffset++;
			}
			else Bitmask <<= 1;
		}
	};
	LPCVOID	GetBits() const { return _SC::_Bits; }
	bool	Get(const Index& idx) const 
			{	ASSERT(idx.BlockOffset<_SC::RT_BLOCK_COUNT);
				return _SC::_Bits[idx.BlockOffset]&idx.Bitmask; 
			}
	DWORD	Get(UINT idx, UINT bit_count) // bit_count <= 32
			{	ASSERT(idx<_SC::BIT_SIZE);
				ASSERT(bit_count <= 32);
				if(idx + bit_count > _SC::BIT_SIZE)bit_count = _SC::BIT_SIZE - idx;
				if(bit_count == 0)return 0;
				return (DWORD)(((*(ULONGLONG*)&_SC::_Bits[idx/RT_BLOCK_SIZE]) >> (idx%RT_BLOCK_SIZE)) & ((1ULL<<bit_count)-1));
			}
	bool	Set(const Index& idx, bool v = true)
			{	ASSERT(idx.BlockOffset<_SC::RT_BLOCK_COUNT);
				bool org = !!(_SC::_Bits[idx.BlockOffset]&idx.Bitmask);
				if(v)
					_SC::_Bits[idx.BlockOffset] |= idx.Bitmask;
				else
					_SC::_Bits[idx.BlockOffset] &= ~idx.Bitmask;
				return org;
			}
	void	Set(UINT idx, DWORD bits, UINT bit_count) // bit_count <= 32
			{	ASSERT(idx<_SC::BIT_SIZE);
				if(bit_count)
				{	ASSERT(idx + bit_count < _SC::BIT_SIZE);
					ASSERT(bit_count <= 32);
					ULONGLONG& ull = *(ULONGLONG*)&_SC::_Bits[idx/RT_BLOCK_SIZE];
					UINT shift = idx%RT_BLOCK_SIZE;
					ull = (ull&~(((1ULL<<bit_count)-1)<<shift)) | (((ULONGLONG)bits) << shift);
				}
			}
	bool	AtomicSet(const Index& idx) // return the bit value before atomic set
			{	ASSERT(idx.BlockOffset<_SC::RT_BLOCK_COUNT);
				return idx.Bitmask & os::AtomicOr(idx.Bitmask, (volatile UINT*)&_SC::_Bits[idx.BlockOffset]);
			}
	bool	AtomicReset(const Index& idx) // return the bit value before atomic set
			{	ASSERT(idx.BlockOffset<_SC::RT_BLOCK_COUNT);
				return idx.Bitmask & os::AtomicAnd(~idx.Bitmask, (volatile UINT*)&_SC::_Bits[idx.BlockOffset]);
			}
	void	Reset(const Index& idx){ Set(idx, false); }
	void	ResetAll(){ memset(_SC::_Bits, 0, _SC::RT_BLOCK_COUNT*sizeof(RT_BLOCK_TYPE)); }
	void	SetAll(){ memset(_SC::_Bits, 0xff, _SC::RT_BLOCK_COUNT*sizeof(RT_BLOCK_TYPE)); _SC::_ClearTrailingBits(); }
	bool	IsAllReset() const { for(UINT i=0; i<_SC::RT_BLOCK_COUNT; i++)if(_SC::_Bits[i])return false; return true; }
	UINT	PopCount() const { UINT pc = 0; for(UINT i=0; i<_SC::RT_BLOCK_COUNT; i++)pc += rt::PopCount(_SC::_Bits[i]); return pc; }
	void	operator ^= (const BooleanArray& x){ for(UINT i=0;i<_SC::RT_BLOCK_COUNT; i++)_SC::_Bits[i] ^= x._Bits[i]; }
	void	operator |= (const BooleanArray& x){ for(UINT i=0;i<_SC::RT_BLOCK_COUNT; i++)_SC::_Bits[i] |= x._Bits[i]; }
	/**
	 * @brief visit all ones
	 * 
	 * @tparam CB 
	 * @param cb 
	 * @return UINT 
	 */
	template<typename CB>
	UINT	VisitOnes(CB&& cb) const	
			{	UINT hit = 0;	UINT i=0;
				for(; i<_SC::RT_BLOCK_COUNT-1; i++)
				{	RT_BLOCK_TYPE bits = _SC::_Bits[i];
					if(bits)
					{	for(UINT b=0; b<RT_BLOCK_SIZE; b++)
						{	if(bits&(1ULL<<b))
							{	cb(i*RT_BLOCK_SIZE + b);
								hit++;
							}
						}
					}
				}
				RT_BLOCK_TYPE bits = _SC::_Bits[i];
				if(bits)
				{	for(UINT b=0; b<(bit_size%RT_BLOCK_SIZE); b++)
					{	if(bits&(1ULL<<b))
						{	cb(i*RT_BLOCK_SIZE + b);
							hit++;
						}
					}
				}
				return hit;
			}
	/**
	 * @brief visit all ones
	 * 
	 * @tparam CB 
	 * @param cb 
	 */
	template<typename CB>
	void	ForEach(CB&& cb) const	
			{	UINT i=0;
				for(; i<sizeofArray(_SC::_Bits)-1; i++)
				{	RT_BLOCK_TYPE bits = _SC::_Bits[i];
					for(UINT b=0; b<RT_BLOCK_SIZE; b++)cb(bits&(1ULL<<b));
				}
				RT_BLOCK_TYPE bits = _SC::_Bits[i];
				for(UINT b=0; b<(_SC::BIT_SIZE%RT_BLOCK_SIZE); b++)cb(bits&(1ULL<<b));
			}
	template<char one = '1', char zero = '.'>
	auto	ToString(rt::String& append) const
			{	ForEach([&append](bool v){
					append += v?one:zero;
				});
				return append;
			}
	template<char sep = ','>
	auto	ToStringWithIndex(rt::String& append) const
			{	if(VisitOnes([&append](UINT v){
					append += rt::tos::Number(v);
					append += sep;
				}))append.Shorten(1);
				return append;
			}
	BooleanArray(){}
	BooleanArray(std::initializer_list<bool> a_args)
			{	rt::Zero(_SC::_Bits);
				UINT i = 0;
				for(auto b: a_args)Set(i++, b);
			}
	void	Shift(int s){ if(s>0){LeftShift((UINT)s);}else{{RightShift((UINT)-s);}} }
	void	LeftShift(UINT s)
			{	if(s == 0)return;					if(s > bit_size){ ResetAll(); return; }
				UINT offset = s/RT_BLOCK_SIZE;			s = s%RT_BLOCK_SIZE;
				UINT i = _SC::RT_BLOCK_COUNT - 1;
				for (; 0 < i - offset; i--)
					_SC::_Bits[i] = (_SC::_Bits[i - offset] << s) | (_SC::_Bits[i - offset - 1] >> (RT_BLOCK_SIZE - s));
				_SC::_Bits[i] = _SC::_Bits[i - offset] << s;
				if(i)rt::Zero(_SC::_Bits, (i-1)*RT_BLOCK_SIZE/8);
				_SC::_ClearTrailingBits();
			}
	void	RightShift(UINT s)
			{	if(s == 0)return;					if(s > bit_size){ ResetAll(); return; }
				UINT offset = s/RT_BLOCK_SIZE;	s = s%RT_BLOCK_SIZE;
				UINT i = 0;
				for (; i + offset < _SC::RT_BLOCK_COUNT - 1; i++)
					_SC::_Bits[i] = (_SC::_Bits[i + offset] >> s) | (_SC::_Bits[i + offset + 1] << (RT_BLOCK_SIZE - s));
				_SC::_Bits[i] = _SC::_Bits[i + offset] >> s;
				if(i + 1 < _SC::RT_BLOCK_COUNT)rt::Zero(&_SC::_Bits[i+1], (_SC::RT_BLOCK_COUNT - i - 1)*RT_BLOCK_SIZE/8);
			}
};
typedef BooleanArray<0, true> BooleanArrayRef;
} // namespace rt


namespace rt
{
namespace _details
{
template<class t_Storage>
class StreamT: protected t_Storage
{	typedef t_Storage _SC;
protected:
	UINT	m_Pos;
	UINT	m_Used;
public:
	StreamT(){ m_Pos = 0; m_Used = 0; }
	StreamT(LPCBYTE p, UINT len, UINT used_len):t_Storage(p,len){ m_Pos = 0; m_Used = used_len; }
	SIZE_T		GetLength() const { return m_Used; }
	LPBYTE		GetInternalBuffer(){ return (LPBYTE)_SC::_p; }
	LPCBYTE		GetInternalBuffer() const { return (LPCBYTE)_SC::_p; }
	void		Rewind(){ m_Pos = 0; }
	LONGLONG	Seek(SSIZE_T offset, int nFrom = rt::_File::Seek_Begin)
				{	SSIZE_T newp = 0;
					switch(nFrom)
					{	case rt::_File::Seek_Begin:	newp = offset; break;
						case rt::_File::Seek_Current: newp = m_Pos + offset; break;
						case rt::_File::Seek_End:		newp = m_Used + offset; break;
						default: ASSERT(0);
					}
					if(newp >=0 && newp <= (SSIZE_T)_SC::_len)m_Pos = (UINT)newp;
					return m_Pos;
				}
};

template<class t_Storage>
class OStreamT: public StreamT<t_Storage>
{	typedef StreamT<t_Storage> _SC;
public:
	OStreamT(){}
	OStreamT(LPCBYTE p, UINT len):StreamT<t_Storage>(p,len,0){}
	UINT	Write(LPCVOID pBuf, UINT co)
			{	co = rt::min((UINT)(_SC::_len - _SC::m_Pos), co);
				if(co)
				{	memcpy(_SC::_p + _SC::m_Pos,pBuf,co);
					_SC::m_Pos += co;
					if(_SC::m_Used < _SC::m_Pos)_SC::m_Used = _SC::m_Pos;
				}
				return co;
			}
};

template<class t_Storage>
class IStreamT: public StreamT<t_Storage>
{	typedef StreamT<t_Storage> _SC;
public:
	IStreamT(LPCBYTE p, UINT len):StreamT<t_Storage>(p,len,len){}
	UINT	Read(LPVOID pBuf, UINT co)
			{	ASSERT(_SC::m_Pos <= _SC::_len);
				co = rt::min(co, (UINT)(_SC::_len - _SC::m_Pos));
				memcpy(pBuf,_SC::_p + _SC::m_Pos,co);
				_SC::m_Pos += co;
				return co;
			}
};

} // namespace _details

class OStream: public _details::OStreamT<Buffer<BYTE>>
{	typedef _details::OStreamT<Buffer<BYTE>> _SC;
public:
	UINT	Write(LPCVOID pBuf, UINT co)
			{	if(ChangeSize(rt::max(_len,(SIZE_T)(m_Pos+co))))
				{	memcpy(_SC::_ptr() + m_Pos,pBuf,co);
					m_Pos += co;
					if(_SC::m_Used < _SC::m_Pos)_SC::m_Used = _SC::m_Pos;
					return co;
				}
				else return 0;
			}
	auto	Seek(SSIZE_T offset, int nFrom = rt::_File::Seek_Begin)
			{	SSIZE_T newp = 0;
				switch(nFrom)
				{	case rt::_File::Seek_Begin:	newp = offset; break;
					case rt::_File::Seek_Current: newp = m_Pos+offset; break;
					case rt::_File::Seek_End:		newp = _len + offset; break;
					default: ASSERT(0);
				}
				if(newp >=0 && ChangeSize(rt::max(_len,(SIZE_T)newp)))
					m_Pos = (UINT)newp;
				return m_Pos;
			}
	bool	SetLength(UINT sz){ m_Pos = rt::min(m_Pos,sz); m_Used = sz; return ChangeSize((UINT)sz); }
};

typedef _details::OStreamT<Buffer_Ref<BYTE> > OStream_Ref;
typedef _details::IStreamT<Buffer_Ref<BYTE> > IStream_Ref;

template<UINT LEN>
class OStreamFixed: public OStream_Ref
{
	BYTE	_Buffer[LEN];
public:
	OStreamFixed():OStream_Ref(_Buffer,LEN){}
	bool SetLength(UINT sz){ if(sz <= LEN){ m_Pos = rt::min(m_Pos,sz); m_Used = sz; return true; } return false; }
};
/**
 * @brief not thread-safe
 * 
 */
class CircularBuffer 
{
protected:
#pragma pack(1)
	struct _BlockHeader
	{	SIZE_T	Next;
		SIZE_T	PayloadSize;
		SIZE_T	PayloadLength;
	};
	struct _Block: public _BlockHeader
	{	BYTE	Payload[1];
	};
public:
	struct Block
	{	SIZE_T	Length;
		BYTE	Data[1];
	};
#pragma pack()
protected:
	LPBYTE		_Buffer;
	SIZE_T		_BufferSize;
	SIZE_T		Back;
	SIZE_T		NewBlock;
	_Block*		pLastBlock;
public:
	CircularBuffer(){ _Buffer = nullptr; SetSize(0); }
	~CircularBuffer(){ _SafeFree32AL(_Buffer); }
	void	SetSize(SIZE_T sz)
			{	_SafeFree32AL(_Buffer);
				if(sz)
				{	_Buffer = (LPBYTE)_Malloc32AL(BYTE,sz);
					_BufferSize = sz;
					ASSERT(_Buffer);
				}
				else
				{	_Buffer = nullptr;
					_BufferSize = 0;
				}
				Back = NewBlock = 0;
				pLastBlock = nullptr;
			}
	LPBYTE	Push(SIZE_T size_max)
			{	size_max = _EnlargeTo32AL(size_max);
				SIZE_T	block_size = size_max + sizeof(_BlockHeader);
				_Block*	p;
				if(	(block_size + NewBlock < _BufferSize && NewBlock >= Back) ||
					(block_size + NewBlock < Back && NewBlock < Back)
				)
				{	p = (_Block*)(_Buffer + NewBlock);
					NewBlock += block_size;
				}
				else if(NewBlock >= Back && Back > block_size)
				{	p = (_Block*)_Buffer;
					NewBlock = block_size;
				}
				else return nullptr;

				p->PayloadSize = size_max;
				p->Next = INFINITE;
				p->PayloadLength = 0;
		
				if(pLastBlock)pLastBlock->Next = ((LPBYTE)p) - _Buffer;
				pLastBlock = p;
				return p->Payload;
			}
	void	Pop()
			{
				if(Back != NewBlock)
				{
					_Block* p = (_Block*)(_Buffer + Back);
					if(p == pLastBlock)
					{	ASSERT(p->Next == INFINITE);
						pLastBlock = nullptr;
						NewBlock = Back = 0;
					}
					else
					{	ASSERT(p->Next != INFINITE);
						Back = p->Next;
					}
				}
			}
	void	SetBlockSize(LPCVOID pushed, SIZE_T finalized)	///< call after Push()
			{
				ASSERT(finalized);
				_Block* block = (_Block*)(((LPBYTE)pushed) - sizeof(_BlockHeader));
				ASSERT(block->PayloadSize >= finalized);
				block->PayloadLength = finalized;
			}
	auto	Peek() const -> const Block*
			{
				Block* p = (Back != NewBlock)?(Block*)(_Buffer + Back + sizeof(_BlockHeader) - sizeof(SIZE_T)):nullptr;
				if(p && p->Length>0)
				{	return p;
				}
				else
					return nullptr;
			}
	void	Empty(){ while(Peek())Pop(); }
};


template<typename T, UINT TOP_K=1, typename T_WEIGHT = int, bool keep_latest_value = false>
class TopWeightedValues
{
	template<typename _T, UINT _TOP_K, typename _WEIGHT, bool s> friend class TopWeightedValues;
	struct _val
	{	T			Val;
		UINT		Count;
		T_WEIGHT	Wei;
	};
public:
	static const UINT TOP_COUNT_CLAMP = rt::TypeTraits<UINT>::MaxVal()/8*7; ///< all weight will be halfed if top exceeds TOP_WEIGHT_CLAMP
	static const UINT UNMATCHED = 0;
	static const UINT MATCHED = 1;
	static const UINT MATCHED_WITH_TOP = 2;
protected:
	_val	_TopValues[TOP_K];
	int		_Match(const T& val, T_WEIGHT wei)	///< 0: not match, 1: matched and no promote, 2: matched
			{
				if(_TopValues[0].Val == val)
				{	_TopValues[0].Wei += wei;
					_TopValues[0].Count++;
					if(keep_latest_value)_TopValues[0].Val = val;
					return MATCHED_WITH_TOP;
				}
				if(_TopValues[0].Wei == 0)
				{	_TopValues[0].Wei = wei;
					_TopValues[0].Val = val;
					_TopValues[0].Count = 1;
					return MATCHED_WITH_TOP;
				}
				int ret = ((TopWeightedValues<T,TOP_K-1,T_WEIGHT>*)(void*)&_TopValues[1])->_Match(val, wei);
				if(ret == MATCHED_WITH_TOP)
				{	if(_TopValues[1].Wei > _TopValues[0].Wei)
					{	rt::Swap(_TopValues[1], _TopValues[0]);
						return MATCHED_WITH_TOP;
					}else return MATCHED;
				}
				return ret;
			}
	auto	_WeightSum() const { return _TopValues[0].Wei + ((TopWeightedValues<T,TOP_K-1,T_WEIGHT>*)&_TopValues[1])->_WeightSum(); }
public:
	TopWeightedValues(){ Reset(); }
	static	UINT GetSize(){ return TOP_K; }
	UINT	GetUniqueValueCount() const 
			{	for(UINT i=0; i<TOP_K; i++)
					if(_TopValues[i].Count == 0)return i;
				return TOP_K;
			}
	int		FindValue(const T& v) const
			{	for(UINT i=0; i<TOP_K; i++)
				{	if(_TopValues[i].Count == 0)return -1;
					if(_TopValues[i].Val == v)return i;
				}
				return -1;
			}
	void	Reset(){ rt::Zero(*this); }
	void	ClampWeight(T_WEIGHT weight_max)
			{	for(UINT i=0; i<TOP_K; i++)
				{	if(_TopValues[i].Wei > weight_max)
						_TopValues[i].Wei = weight_max;
					_TopValues[i].Count = 0;
				}
			}
	int		Sample(const T& val, T_WEIGHT wei = 1)		///< UNMATCHED / MATCHED / MATCH_WITH_TOP, 0: no match, 1: matched but not the top one no promote, 2: matched with top one
			{	int ret = _Match(val, wei);
				if(ret == MATCHED_WITH_TOP)
				{	if(	_TopValues[0].Count > TOP_COUNT_CLAMP || 
						_TopValues[0].Wei > rt::TypeTraits<T_WEIGHT>::MaxVal()/8*7
					)
					{	for(UINT i=0; i<TOP_K; i++)
						{	_TopValues[i].Count >>=1;
							_TopValues[i].Wei /= 2;
						}
					}
					return ret;
				}
				else if(ret == UNMATCHED && wei > _TopValues[TOP_K-1].Wei)
				{	UINT i=TOP_K-1;
					for(; i>0; i--)
					{	if(_TopValues[i-1].Wei < wei){ _TopValues[i] = _TopValues[i-1]; }
						else break;
					}
					_TopValues[i].Val = val;
					_TopValues[i].Wei = wei;
					_TopValues[i].Count = 1;
				}
				return ret;
			}
	UINT	GetCapacity() const { return TOP_K; }
	bool	IsEmpty() const { return GetWeight() <= 0; }
	auto	GetWeight() const { return _TopValues[0].Wei; }
	auto	GetWeight(UINT i) const { return _TopValues[i].Wei; }
	auto	GetCount() const { return _TopValues[0].Count; }
	auto	GetCount(UINT i) const { return _TopValues[i].Count; }
	auto&	operator[](UINT i) const { return Get(i); }
	auto&	Get(UINT i = 0) const { return _TopValues[i].Val; }
	auto&	operator[](UINT i) { return Get(i); }
	auto&	Get(UINT i = 0) { return _TopValues[i].Val; }
	bool	Get(UINT i, T* val, T_WEIGHT* wei, UINT* count = nullptr) const
			{	if(_TopValues[i].Wei>0)
				{	*wei = _TopValues[i].Wei;
					*val = _TopValues[i].Val;
					if(count)*count = _TopValues[i].Count;
					return true; 
				}else return false;
			}
	void	Remove(UINT i)
			{	if(((int)TOP_K) - (int)i - 1 > 0)memmove(&_TopValues[i], &_TopValues[i+1], sizeof(_val)*(TOP_K - i - 1));
				_TopValues[TOP_K-1].Wei = 0;
				_TopValues[TOP_K-1].Count = 0;
			}
	bool	IsSignificant(T_WEIGHT min_weight = 0) const { return _TopValues[0].Wei > min_weight && _TopValues[0].Wei > _WeightSum()/2; }
	UINT	GetSignificantRatio(T_WEIGHT min_weight = 0) const { return _TopValues[0].Wei > min_weight?(UINT)(_TopValues[0].Wei*100/_WeightSum()):0; }
};
	template<typename T, typename T_WEIGHT, bool s>
	class TopWeightedValues<T, 0, T_WEIGHT, s>
	{	template<typename _T, UINT _TOP_K, typename _WEIGHT, bool _s> friend class TopWeightedValues;
		protected:	int		_Match(const T& val, T_WEIGHT wei){ return 0; }
					auto	_WeightSum() const { return 0; }
	};

template<class t_Ostream, typename t_Ele, UINT TOP, typename t_Wei, bool S>
t_Ostream& operator<<(t_Ostream& Ostream, const TopWeightedValues<t_Ele, TOP, t_Wei, S> & vec)
{	Ostream<<'{';
	if(rt::TypeTraits<typename rt::TypeTraits<t_Ele>::t_Element>::Typeid == rt::_typeid_8s)
	{
		for(UINT i=0;i<vec.GetSize();i++)
		{	if(i)
				Ostream<<','<<' '<<'"'<<vec[i]<<"\"="<<vec.GetWeight(i);
			else
				Ostream<<'"'<<vec[i]<<"\"="<<vec.GetWeight(i);
		}
	}
	else
	{
		for(UINT i=0;i<vec.GetSize();i++)
		{	if(i)
				Ostream<<','<<' '<<vec[i]<<'='<<vec.GetWeight(i);
			else
				Ostream<<vec[i]<<'='<<vec.GetWeight(i);
		}
	}
	Ostream<<'}';
	return Ostream;
}
/** @}*/

} // namespace rt
/** @}*/

