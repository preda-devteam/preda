#pragma once
/**
 * @file snappy.h
 * @author SFC dev team
 * @brief 
 * @version 1.0
 * @date 2021-05-08
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
/** \defgroup sparsehash sparsehash
 * @ingroup ext
 *  @{
 */
#include "../../../../SFC/core/rt/string_type.h"
#include "../../../../SFC/core/rt/buffer_type.h"
#include "src/sparsehash/dense_hash_map"
#include "src/sparsehash/dense_hash_set"
#include "src/sparsehash/sparse_hash_map"
#include "src/sparsehash/sparse_hash_set"

namespace ext
{
/** \defgroup sparsehash sparsehash
 * @ingroup ext
 *  @{
 */
namespace _details
{
template<int _LEN>
struct bits_max
{	BYTE	bits[_LEN];
	bits_max(){ rt::Void(bits); bits[_LEN-1] = 0x7f; }
};
template<int _LEN>
struct bits_min
{	BYTE	bits[_LEN];
	bits_min(){ rt::Zero(bits); bits[_LEN-1] = 0x80; }
};
} // namespace _details

enum HASHKEY_CTOR_TYPE
{
	CTOR_ZERO = 0,
	CTOR_VOID = -1
};

template<typename T, bool is_pod = rt::TypeTraits<T>::IsPOD>
struct key_traits;
	template<typename T>
	struct key_traits<T, false>
	{	static const T& empty_key(){ static const T x(CTOR_ZERO); return x; }
		static const T& deleted_key(){ static const T x(CTOR_VOID); return x; }
	};
	template<typename T>
	struct key_traits<T, true>
	{	static void check_compact_pack()
		{
#if defined(PLATFORM_DEBUG_BUILD)
			_details::bits_max<sizeof(T)> x, y;
			x.bits[sizeof(x)-1] = 0xdd;
			ASSERT(!((T&)x == (T&)y));
#endif
		}
		static const T& empty_key(){ static const _details::bits_max<sizeof(T)> x; check_compact_pack(); return (const T&)x; }
		static const T& deleted_key(){ static const _details::bits_min<sizeof(T)> x; check_compact_pack(); return (const T&)x; }
	};
	template<>
	struct key_traits<rt::String_Ref>
	{	static const rt::String_Ref& empty_key(){ static const rt::String_Ref x; return x; }
		static const rt::String_Ref& deleted_key(){ static const rt::String_Ref x("\x0\x0\x0\x0", 4); return x; }
	};
	template<>
	struct key_traits<rt::String>
	{	static const rt::String& empty_key(){ return (const rt::String&)key_traits<rt::String_Ref>::empty_key(); }
		static const rt::String& deleted_key(){ return (const rt::String&)key_traits<rt::String_Ref>::deleted_key(); }
	};
	template<typename POD>
	struct key_traits<rt::PodRef<POD>, false>
	{	static const rt::PodRef<POD>& empty_key(){ static const rt::PodRef<POD> a((POD*)0); return a; }
		static const rt::PodRef<POD>& deleted_key(){ static const rt::PodRef<POD> a((POD*)-1); return a; }
	};
    
template<typename KEY, typename VALUE, typename hash_compare = SPARSEHASH_HASH<KEY>>
class fast_map: public google::dense_hash_map<KEY, VALUE, hash_compare>
{   using _SC = google::dense_hash_map<KEY, VALUE, hash_compare>;
public:
	fast_map()
    {	_SC::set_empty_key(key_traits<KEY>::empty_key());
		_SC::set_deleted_key(key_traits<KEY>::deleted_key());
	}
	fast_map(const KEY& empty_key)
	{	_SC::set_empty_key(empty_key);
		_SC::set_deleted_key(key_traits<KEY>::deleted_key());
	}
	fast_map(const KEY& empty_key, const KEY& deleted_key)
	{	_SC::set_empty_key(empty_key);
		_SC::set_deleted_key(deleted_key);
	}
	const VALUE& get(const KEY& k, const VALUE& v) const
	{	auto it = _SC::find(k);
		return it != _SC::end()?it->second:v;
	}
	VALUE& get(const KEY& k, const VALUE& default_val)
	{	auto it = _SC::find(k);
		if(it != _SC::end())return it->second;
		VALUE& ret = _SC::operator[](k);
		ret = default_val;
		return ret;
	}
	const VALUE& get(const KEY& k) const
	{	auto it = _SC::find(k);
		ASSERT(it != _SC::end());
		return it->second;
	}
	VALUE& get(const KEY& k)
	{	auto it = _SC::find(k);
		ASSERT(it != _SC::end());
		return it->second;
	}
	bool has(const KEY& k) const
	{	auto it = _SC::find(k);
		return it != _SC::end();
	}
};

template<typename KEY, typename VALUE, typename hash_compare = SPARSEHASH_HASH<KEY>>
class fast_map_aliased_key: protected fast_map<KEY, VALUE, hash_compare>
{	using _SC = fast_map<KEY, VALUE, hash_compare>;
	using key_type = typename _SC::key_type;
	using iterator = typename _SC::iterator;
	using const_iterator = typename _SC::const_iterator;
	using size_type = typename _SC::size_type;
public:

	const_iterator	begin() const { return _SC::begin(); }
	const_iterator	end() const { return _SC::end(); }
	iterator		begin(){ return _SC::begin(); }
	iterator		end(){ return _SC::end(); }

	VALUE*			get(const KEY& k) { auto it = find(k); return it == end()?nullptr:&it->second; }  // WARNING: don't modify the part mapped to key
	const VALUE*	get(const KEY& k) const { return rt::_CastToNonconst(this)->get(k); }
	bool			has(const KEY& k) const { return _SC::has(k); }
	VALUE*			take(const KEY& k){ return _SC::take(k); }

	iterator		find(const key_type& key) { return _SC::find(key); }
	const_iterator	find(const key_type& key) const { return _SC::find(key); }

	size_type		erase(const key_type& key){ return _SC::erase(key); }
	void			erase(iterator& it){ _SC::erase(it); }
	void			erase(iterator& f, iterator& l){ _SC::erase(f, l); }

	void			resize(size_type hint){ _SC::resize(hint); }
	void			rehash(size_type hint){ _SC::resize(hint); }
	size_type		size() const { return _SC::size(); }
	void			clear(){ _SC::clear(); }

	auto&			operator [](const KEY& key){ return _SC::operator [](key); }
	auto&			operator [](const KEY& key) const { return _SC::operator [](key); }
	void			set(const KEY& key, const VALUE& val){ _SC::erase(key); _SC::operator [](key) = val; }
	void			insert(const KEY& key, const VALUE& val){ ASSERT(!has(key)); _SC::operator [](key) = val; }
};

template<typename KEY, typename hash_compare = SPARSEHASH_HASH<KEY>>
class fast_set: public google::dense_hash_set<KEY, hash_compare>
{   using _SC = google::dense_hash_set<KEY, hash_compare>;
public:
	fast_set()
    {	_SC::set_empty_key(key_traits<KEY>::empty_key());
		_SC::set_deleted_key(key_traits<KEY>::deleted_key());
	}
	fast_set(const KEY& empty_key)
	{	_SC::set_empty_key(empty_key);
		_SC::set_deleted_key(key_traits<KEY>::deleted_key());
	}
	fast_set(const KEY& empty_key, const KEY& deleted_key)
	{	_SC::set_empty_key(empty_key);
		_SC::set_deleted_key(deleted_key);
	}
	bool has(const KEY&& k) const { return _SC::find(k) != _SC::end(); }
	bool has(const KEY& k) const { return _SC::find(k) != _SC::end(); }
};

template<typename KEY, typename VALUE, typename hash_compare = SPARSEHASH_HASH<KEY>>
class fast_map_ptr: public fast_map<KEY, VALUE*, hash_compare>
{   using _SC = fast_map<KEY, VALUE*, hash_compare>;
public:
    fast_map_ptr(){}
    fast_map_ptr(const KEY& empty_key):_SC(empty_key){}
	fast_map_ptr(const KEY& empty_key, const KEY& deleted_key):_SC(empty_key, deleted_key){}
	VALUE* get(const KEY& k) const
	{	auto it = _SC::find(k);
        if(it != _SC::end())return it->second;
		return nullptr;
	}
	void set(const KEY& key, VALUE* val){ _SC::operator [](key) = val; }
	void insert(const KEY& key, VALUE* val_ptr){ ASSERT(!has(key)); _SC::operator [](key) = val_ptr; }
	bool has(const KEY& k) const { return _SC::find(k) != _SC::end(); }
	VALUE* take(const KEY& k)
	{
		auto it = _SC::find(k);
		if(it == _SC::end())return nullptr;
		VALUE* ret = it->second;
		_SC::erase(it);
		return ret;
	}
	VALUE* replace(const KEY& k, VALUE* new_val)
	{
		auto it = _SC::find(k);
		if(it == _SC::end()){ set(k, new_val); return nullptr; }
		VALUE* ret = it->second;
		it->second = new_val;
		return ret;
	}
	template<typename FUNC>
	void foreach(FUNC&& v) const
	{
		for(auto it = _SC::begin(); it != _SC::end(); it++)
			v(it->first, it->second);
	}
};

template<typename KEY, typename VALUE, typename hash_compare = SPARSEHASH_HASH<KEY>>
class fast_map_ptr_aliased_key: protected fast_map_ptr<KEY, VALUE, hash_compare>
{	using _SC = fast_map_ptr<KEY, VALUE, hash_compare>;
	using key_type = typename _SC::key_type;
	using iterator = typename _SC::iterator;
	using const_iterator = typename _SC::const_iterator;
	using size_type = typename _SC::size_type;
public:

	const_iterator	begin() const { return _SC::begin(); }
	const_iterator	end() const { return _SC::end(); }
	iterator		begin(){ return _SC::begin(); }
	iterator		end(){ return _SC::end(); }

	VALUE*			get(const KEY& k){ return (VALUE*)_SC::get(k); }  // WARNING: don't modify the part mapped to key
	const VALUE*	get(const KEY& k) const { return _SC::get(k); }
	bool			has(const KEY& k) const { return _SC::has(k); }
	VALUE*			take(const KEY& k){ return _SC::take(k); }
	VALUE*			replace(const KEY& k, VALUE* new_val){ return _SC::replace(k, new_val); }
	template<typename FUNC>
	void foreach(FUNC&& v) const { _SC::foreach(v); }

	iterator		find(const key_type& key) { return _SC::find(key); }
	const_iterator	find(const key_type& key) const { return _SC::find(key); }

	size_type		erase(const key_type& key){ return _SC::erase(key); }
	void			erase(iterator& it){ _SC::erase(it); }
	void			erase(iterator& f, iterator& l){ _SC::erase(f, l); }

	void			resize(size_type hint){ _SC::resize(hint); }
	void			rehash(size_type hint){ _SC::resize(hint); }
	size_type		size() const { return _SC::size(); }
	void			clear(){ _SC::clear(); }

	void			set(const KEY& key, VALUE* val_ptr){ _SC::erase(key); _SC::operator [](key) = val_ptr; }
	void			insert(const KEY& key, VALUE* val_ptr){ ASSERT(!has(key)); _SC::operator [](key) = val_ptr; }
};

template<typename t_Tag, typename t_Count = int, typename hash_compare = SPARSEHASH_HASH<t_Tag>>
class fast_counter: public fast_map<t_Tag, t_Count, hash_compare>
{   using _SC = fast_map<t_Tag, t_Count, hash_compare>;
public:
	void Count(const t_Tag& tag, t_Count w = 1)
	{	auto it = _SC::find(tag);
        if(it == _SC::end())_SC::insert(std::pair<t_Tag, t_Count>(tag,w));
		else
		{	it->second += w;
		}
	}
	t_Count Get(const t_Tag& tag)
	{	auto it = _SC::find(tag);
		return it == _SC::end()?0:it->second;
	}
};
/** @}*/
} // ext
/** @}*/