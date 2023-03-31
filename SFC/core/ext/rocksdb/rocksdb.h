#pragma once

/**
 * @file rocksdb.h
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
/** \defgroup rocksdb rocksdb
 * @ingroup ext
 *  @{
 */
#include "../../rt/type_traits.h"
#include "../../os/multi_thread.h"
#include "../../os/file_dir.h"
#include "rocksdb_conf.h"

#include "./include/db.h"
#include "./include/slice_transform.h"
#include "./include/merge_operator.h"
#include "./include/comparator.h"
#include "./include/table.h"

namespace ext
{
/** \defgroup rocks_db rocks_db
 * @ingroup rocksdb
 *  @{
 */
typedef ::rocksdb::WriteOptions	WriteOptions;
typedef ::rocksdb::ReadOptions	ReadOptions;
typedef ::rocksdb::Iterator		Iterator;
typedef ::rocksdb::Options		Options;
typedef ::rocksdb::BlockBasedTableOptions BlockBasedTableOptions;


class SliceDyn: public ::rocksdb::Slice
{
public:
	SliceDyn(){ data_ = nullptr; }
	~SliceDyn(){ _SafeFree32AL(data_); }
	template<typename StrExp>
	SliceDyn(StrExp& se){ data_ = nullptr; *this = se; }
	template<typename StrExp>
	StrExp& operator = (StrExp& se)
	{	_SafeFree32AL(data_);
		size_ = se.GetLength();
		if((data_ = _Malloc32AL(char, size_)))
		{	se.CopyTo((LPSTR)data_);
		}else{ size_ = 0; }
		return se;
	}
};

class SliceValue: public ::rocksdb::Slice
{
protected:
	char	_embedded[8];
public:
	SliceValue():Slice(nullptr, 0){}
	SliceValue(LPCVOID p, SIZE_T sz):Slice((char*)p, sz){}

	SliceValue(int i):Slice(_embedded, sizeof(i)){ *((int*)_embedded) = i; }
	SliceValue(BYTE i):Slice(_embedded, sizeof(i)){ *((BYTE*)_embedded) = i; }
	SliceValue(WORD i):Slice(_embedded, sizeof(i)){ *((WORD*)_embedded) = i; }
	SliceValue(DWORD i):Slice(_embedded, sizeof(i)){ *((DWORD*)_embedded) = i; }
	SliceValue(ULONGLONG i):Slice(_embedded, sizeof(i)){ *((ULONGLONG*)_embedded) = i; }
	SliceValue(LONGLONG i):Slice(_embedded, sizeof(i)){ *((LONGLONG*)_embedded) = i; }
	SliceValue(float i):Slice(_embedded, sizeof(i)){ *((float*)_embedded) = i; }
	SliceValue(double i):Slice(_embedded, sizeof(i)){ *((double*)_embedded) = i; }

	SliceValue(LPSTR str):Slice(str, str?strlen(str):0){}
	SliceValue(LPCSTR str):Slice(str, str?strlen(str):0){}
	
	SliceValue(const SliceDyn& i):Slice(i){}
	SliceValue(const Slice& i):Slice(i){}

	template<typename T>
	SliceValue(const T& x)
		:Slice((LPCSTR)rt::GetDataPtr(x), rt::GetDataSize(x))
	{}

	//template<size_t LEN>
	//inline SliceValue(char str[LEN]):Slice(str, LEN-1){}
	//template<size_t LEN>
	//inline SliceValue(const char str[LEN]):Slice(str, LEN-1){}

	SIZE_T GetSize() const { return size(); }

	rt::String_Ref ToString(SIZE_T off = 0) const { ASSERT(size_>=off); return rt::String_Ref(data_ + off, size_ - off); }
	template<typename T>
	const T& To(SIZE_T off = 0) const {	ASSERT(size_ >= off + sizeof(T)); return *((T*)(data_ + off)); }
};

#define SliceValueNull		::rocksdb::Slice()
#define SliceValueSS(x)		::rocksdb::Slice(x, sizeof(x)-1)

namespace _details
{
template<typename T_KEYVAL, int METADATA_SIZE, UINT PAGING_SIZE, typename T_PAGE, typename T_VALUESIZE, class DB_CLS>
class RocksPagedBase;
} // namespace _details

class RocksCursor
{
	friend class RocksDB;
	template<typename T_KEYVAL, int METADATA_SIZE, UINT PAGING_SIZE, typename T_PAGE, typename T_VALUESIZE, class DB_CLS>
	friend class _details::RocksPagedBase;

	int					 _PagedKeySize;
	::rocksdb::Iterator* _Iter = nullptr;
public:
/**
 * @brief move constructor, enable return by RocksDB::First/Last
 * 
 * @param x 
 * @return inline 
 */
	RocksCursor() = default;
	RocksCursor(RocksCursor&& x){ _Iter = x._Iter; x._Iter = nullptr; _PagedKeySize = x._PagedKeySize; }
	~RocksCursor(){ Empty(); }
	bool				IsEmpty() const { return _Iter == nullptr; }
	void				Empty(){ _SafeDel_Untracked(_Iter); }
	void				operator = (RocksCursor&& x){ _SafeDel_Untracked(_Iter); _Iter = x._Iter; x._Iter = nullptr; }

	template<typename T>
	const T&			Key() const { return *(T*)_Iter->key().data(); }
	template<typename T>
	const T&			Value() const { return *(T*)_Iter->value().data(); }
	const SliceValue	Key() const { return (const SliceValue&)_Iter->key(); }
	const SliceValue	Value() const { return (const SliceValue&)_Iter->value(); }
	SIZE_T				KeyLength() const { return _Iter->key().size(); }
	SIZE_T				ValueLength() const { return _Iter->value().size(); }
	bool				IsValid() const { return _Iter && _Iter->Valid(); }

	void				Next(){	_Iter->Next(); if(_PagedKeySize)while(_Iter->Valid() && KeyLength() != _PagedKeySize)_Iter->Next();	}
	void				Prev(){ _Iter->Prev(); if(_PagedKeySize)while(_Iter->Valid() && KeyLength() != _PagedKeySize)_Iter->Prev(); }
	void				Next(UINT co){ while(co--)_Iter->Next(); }
	void				Prev(UINT co){ while(co--)_Iter->Prev(); }
	void				operator ++ (){ Next(); }
	void				operator -- (){ Prev(); }
	void				operator += (int step){ if(step>0){ Next(step); }else{ Prev(-step); } }
	void				operator -= (int step){ if(step>0){ Prev(step); }else{ Next(-step); } }
	void				operator ++ (int){ Next(); }
	void				operator -- (int){ Prev(); }

private:
	RocksCursor(const RocksCursor& x) = delete; // RocksCursor can only be constructed by RocksDB
	RocksCursor(::rocksdb::Iterator* it, int paged_keysize)
	{	_Iter = it;
		if(paged_keysize > 0)
		{	_PagedKeySize = paged_keysize;
			while(_Iter->Valid() && KeyLength() != _PagedKeySize)_Iter->Next();
		}
		else if(paged_keysize < 0)
		{	_PagedKeySize = -paged_keysize;
			while(_Iter->Valid() && KeyLength() != _PagedKeySize)_Iter->Prev();
		}
		else _PagedKeySize = 0;
	}
};

class RocksStorage;

class RocksDB
{
	friend class RocksStorage;
	friend class RocksDBStandalone;

public:
	class [[nodiscard]] _RocksDBIntl
	{
		friend class RocksDB;
		friend class RocksStorage;
		friend class RocksDBStandalone;
		RocksStorage*					_pStg;
		::rocksdb::ColumnFamilyHandle*	_pCF;
		_RocksDBIntl(){ rt::Zero(*this); }
		_RocksDBIntl(const _RocksDBIntl& x) = delete;
		_RocksDBIntl(_RocksDBIntl&& x){ rt::Copy(*this, x); rt::Zero(x); }
		_RocksDBIntl(RocksStorage* d, ::rocksdb::ColumnFamilyHandle* f){ _pStg=d; _pCF=f; }
	public:
		~_RocksDBIntl();
	};

protected:
	RocksStorage*					_pStg;
	::rocksdb::DB*					_pDB;
	::rocksdb::ColumnFamilyHandle*	_pCF;

public:
	static const WriteOptions*	WriteOptionsFastRisky;
	static const WriteOptions*	WriteOptionsDefault;
	static const WriteOptions*	WriteOptionsRobust;
	static const ReadOptions*	ReadOptionsDefault;

	enum DBOpenType
	{
		DBOT_SMALL_DB = 0,	///< optimized for small db
		DBOT_DEFAULT,
		DBOT_LOOKUP,		///< optimized point lookup, no range scan
	};

public:
	RocksDB(){ _pStg = nullptr; _pCF = nullptr; _pDB = nullptr; }
	~RocksDB(){ Empty(); }
	RocksDB(const RocksDB& x) = delete;
	RocksDB(RocksDB&& x){ rt::Copy(*this, x); rt::Zero(x); }
	
	void operator = (_RocksDBIntl&& x);
	RocksDB(_RocksDBIntl& x){ *this = std::move(x); }
	RocksDB(_RocksDBIntl&& x){ *this = std::move(x); }

	bool IsEmpty() const { return _pStg == nullptr; }
	void Empty();
	bool HasNoEntry() const;
	bool Set(const SliceValue& k, const SliceValue& val, const WriteOptions* opt = WriteOptionsDefault){ ASSERT(_pDB); return _pDB->Put(*opt, _pCF, k, val).ok(); }
	bool Merge(const SliceValue& k, const SliceValue& val, const WriteOptions* opt = WriteOptionsDefault){ ASSERT(_pDB); return _pDB->Merge(*opt, _pCF, k, val).ok(); }
	bool Get(const SliceValue& k, std::string& str, const ReadOptions* opt = ReadOptionsDefault) const { ASSERT(_pDB); return _pDB->Get(*opt, _pCF, k, &str).ok(); }
	bool Has(const SliceValue& k, const ReadOptions* opt = ReadOptionsDefault) const { thread_local std::string t; return Get(k, t, opt); }
	template<typename t_POD>
	bool Get(const SliceValue& k, t_POD* valout, const ReadOptions* opt = ReadOptionsDefault) const
	{	ASSERT_NO_FUNCTION_REENTRY;
		thread_local std::string temp;
		ASSERT(_pDB);
		if(_pDB->Get(*opt, _pCF, k, &temp).ok() && temp.length() == sizeof(t_POD))
		{	memcpy(valout, temp.data(), sizeof(t_POD));
			return true;
		}else return false;
	}
	template<typename t_NUM>
	t_NUM GetAs(const SliceValue& k, t_NUM default_val = 0, const ReadOptions* opt = ReadOptionsDefault) const
	{	ASSERT_NO_FUNCTION_REENTRY;
		thread_local std::string temp;
		ASSERT(_pDB);
		return (_pDB->Get(*opt, _pCF, k, &temp).ok() && temp.length() == sizeof(t_NUM))?
			   *((t_NUM*)temp.data()):default_val;
	}
	template<typename t_Type>
	const t_Type* Fetch(const SliceValue& k, SIZE_T* len_out = nullptr, const ReadOptions* opt = ReadOptionsDefault) const // Get a inplace referred buffer, will be invalid after next Fetch
	{	ASSERT_NO_FUNCTION_REENTRY;
		thread_local std::string temp;
		ASSERT(_pDB);
		if(_pDB->Get(*opt, _pCF, k, &temp).ok() && temp.length() >= sizeof(t_Type))
		{	if(len_out)*len_out = temp.length();
			return (t_Type*)temp.data();
		}
		else
		{	if(len_out)*len_out = 0;
			return nullptr;
		}
	}
	rt::String_Ref Fetch(const SliceValue& k, const ReadOptions* opt = ReadOptionsDefault) const
	{	ASSERT_NO_FUNCTION_REENTRY;
		thread_local std::string temp;
		ASSERT(_pDB);
		return (_pDB->Get(*opt, _pCF, k, &temp).ok())?
				rt::String_Ref(temp.data(), temp.length()):rt::String_Ref();
	}
	RocksCursor Seek(const SliceValue& begin, const ReadOptions* opt = ReadOptionsDefault) const
	{	::rocksdb::Iterator* it = rt::_CastToNonconst(_pDB)->NewIterator(*opt, _pCF);
		ASSERT(it);
		it->Seek(begin);
		return RocksCursor(it, 0);
	}
	RocksCursor First(const ReadOptions* opt = ReadOptionsDefault) const
	{	::rocksdb::Iterator* it = rt::_CastToNonconst(_pDB)->NewIterator(*opt, _pCF);
		ASSERT(it);
		it->SeekToFirst();
		return RocksCursor(it, 0);
	}
	RocksCursor Last(const ReadOptions* opt = ReadOptionsDefault) const
	{	::rocksdb::Iterator* it = rt::_CastToNonconst(_pDB)->NewIterator(*opt, _pCF);
		ASSERT(it);
		it->SeekToLast();
		return RocksCursor(it, 0);
	}
	bool Delete(const SliceValue& k, const WriteOptions* opt = WriteOptionsDefault){ ASSERT(_pDB); return _pDB->Delete(*opt, _pCF, k).ok(); }

protected:
	template<int paged_key_size, typename func_visit>
	SIZE_T _ScanBackward(const func_visit& v, const SliceValue& begin, const ReadOptions* opt = ReadOptionsDefault) const
	{	ASSERT(_pDB);
		RocksCursor it(_pDB->NewIterator(*opt, _pCF), paged_key_size);
		ASSERT(!it.IsEmpty());
		SIZE_T ret = 0;
		for(it._Iter->Seek(begin); it.IsValid(); it.Prev())
		{	ret++;
			if(!rt::_details::_CallLambda<bool, decltype(v(it))>(true, v, it).retval)
				break;
		}
		return ret;
	}
	template<int paged_key_size, typename func_visit>
	SIZE_T _ScanBackward(const func_visit& v, const ReadOptions* opt = ReadOptionsDefault) const
	{	ASSERT(_pDB);
		RocksCursor it(_pDB->NewIterator(*opt, _pCF), paged_key_size);
		ASSERT(!it.IsEmpty());
		SIZE_T ret = 0;
		for(it._Iter->SeekToLast(); it.IsValid(); it.Prev())
		{	ret++;
			if(!rt::_details::_CallLambda<bool, decltype(v(it))>(true, v, it).retval)
				break;
		}
		return ret;
	}
	template<int paged_key_size, typename func_visit>
	SIZE_T _Scan(const func_visit& v, const SliceValue& begin, const ReadOptions* opt = ReadOptionsDefault) const
	{	ASSERT(_pDB);
		RocksCursor it(_pDB->NewIterator(*opt, _pCF), paged_key_size);
		ASSERT(!it.IsEmpty());
		SIZE_T ret = 0;
		for(it._Iter->Seek(begin); it.IsValid(); it.Next())
		{	ret++;
			if(!rt::_details::_CallLambda<bool, decltype(v(it))>(true, v, it).retval)
				break;
		}
		return ret;
	}
	template<int paged_key_size, typename func_visit>
	SIZE_T _Scan(const func_visit& v, const ReadOptions* opt = ReadOptionsDefault) const
	{	ASSERT(_pDB);
		RocksCursor it(_pDB->NewIterator(*opt, _pCF), paged_key_size);
		ASSERT(!it.IsEmpty());
		SIZE_T ret = 0;
		for(it._Iter->SeekToFirst(); it.IsValid(); it.Next())
		{	ret++;
			if(!rt::_details::_CallLambda<bool, decltype(v(it))>(true, v, it).retval)
				break;
		}
		return ret;
	}

public:
	template<typename func_visit>
	SIZE_T ScanBackward(const func_visit& v, const SliceValue& begin, const ReadOptions* opt = ReadOptionsDefault) const { return _ScanBackward<0>(v, begin, opt); }
	template<typename func_visit>
	SIZE_T ScanBackward(const func_visit& v, const ReadOptions* opt = ReadOptionsDefault) const{ return _ScanBackward<0>(v, opt); }
	template<typename func_visit>
	SIZE_T Scan(const func_visit& v, const SliceValue& begin, const ReadOptions* opt = ReadOptionsDefault) const { return _Scan<0>(v, begin, opt); }
	template<typename func_visit>
	SIZE_T Scan(const func_visit& v, const ReadOptions* opt = ReadOptionsDefault) const { return _Scan<0>(v, opt); }
};

enum RocksStorageWriteRobustness
{							
	ROCKSSTG_FASTEST = 0,	
	ROCKSSTG_DEFAULT,		
	ROCKSSTG_STRONG			
};

enum RocksStorageCache
{
  ROCKSDB_NO_CACHE = 0,
  ROCKSDB_DEFAULT_CACHE,
  ROCKSDB_LARGE_CACHE
};

namespace _details
{
template<int LEN, bool is_pod>
struct _pod_equal;
template<> struct _pod_equal<1, true>{ static bool is(LPCBYTE x, LPCBYTE y){ return *x == *y; } };
template<> struct _pod_equal<2, true>{ static bool is(LPCBYTE x, LPCBYTE y){ return *(WORD*)x == *(WORD*)y; } };
template<> struct _pod_equal<3, true>{ static bool is(LPCBYTE x, LPCBYTE y){ return *(WORD*)x == *(WORD*)y && _pod_equal<1, true>::is(x+2, y+2); } };
template<> struct _pod_equal<4, true>{ static bool is(LPCBYTE x, LPCBYTE y){ return *(DWORD*)x == *(DWORD*)y; } };
template<> struct _pod_equal<5, true>{ static bool is(LPCBYTE x, LPCBYTE y){ return *(DWORD*)x == *(DWORD*)y && _pod_equal<1, true>::is(x+4, y+4); } };
template<> struct _pod_equal<6, true>{ static bool is(LPCBYTE x, LPCBYTE y){ return *(DWORD*)x == *(DWORD*)y && _pod_equal<2, true>::is(x+4, y+4); } };
template<> struct _pod_equal<7, true>{ static bool is(LPCBYTE x, LPCBYTE y){ return *(DWORD*)x == *(DWORD*)y && _pod_equal<3, true>::is(x+4, y+4); } };
template<> struct _pod_equal<8, true>{ static bool is(LPCBYTE x, LPCBYTE y){ return *(ULONGLONG*)x == *(ULONGLONG*)y; } };
template<int LEN>
struct _pod_equal<LEN, true>{ static bool is(LPCBYTE x, LPCBYTE y){ return *(ULONGLONG*)x == *(ULONGLONG*)y && _pod_equal<LEN-8, true>::is(x+8, y+8); } };

struct _compare
{	template<typename T> static auto 
	inline with(const T& x, const T& y) -> decltype(x.compare_with(y)) { return x.compare_with(y); }
	template<typename T, typename ... ARGS> static auto 
	inline with(const T& x, const T& y, ARGS&& ...args) -> decltype((x < y && x == y)*1) 
			{	if(x<y)return -1;
				if(y<x)return +1;
				return 0;
			}
	template<typename T> static auto 
	inline equal(const T& x, const T& y) -> decltype(_pod_equal<sizeof(T), rt::TypeTraits<T>::IsPOD>::is((LPCBYTE)&x, (LPCBYTE)&y)) { return _pod_equal<sizeof(T), rt::TypeTraits<T>::IsPOD>::is((LPCBYTE)&x, (LPCBYTE)&y); }
	template<typename T, typename ... ARGS> static auto 
	inline equal(const T& x, const T& y, ARGS&& ...args) -> decltype(x == y) { return x == y; }
};
} // namespace _details

class RocksDBOpenOption
{
	::rocksdb::ColumnFamilyOptions	Opt;

public:
	operator const ::rocksdb::ColumnFamilyOptions*() const { return &Opt; }
	operator ::rocksdb::ColumnFamilyOptions*(){ return &Opt; }
	operator const ::rocksdb::ColumnFamilyOptions&() const { return Opt; }
	operator ::rocksdb::ColumnFamilyOptions&(){ return Opt; }

	RocksDBOpenOption() = default;
	RocksDBOpenOption(const ::rocksdb::ColumnFamilyOptions& opt):Opt(opt){}
	auto	PointLookup(UINT cache_size_mb = 10) -> RocksDBOpenOption&;
	template<class KeyType>
	auto&	SetKeyOrder()
			{	struct cmp: public ::rocksdb::Comparator
				{	virtual int Compare(const ::rocksdb::Slice& a, const ::rocksdb::Slice& b) const override
					{	ASSERT(a.size()>=sizeof(KeyType));
						ASSERT(b.size()>=sizeof(KeyType));
						auto& x = *(const KeyType*)a.data();
						auto& y = *(const KeyType*)b.data();
						return _details::_compare::with(x ,y);
					}
					virtual bool Equal(const ::rocksdb::Slice& a, const ::rocksdb::Slice& b) const override 
					{	ASSERT(a.size()>=sizeof(KeyType));
						ASSERT(b.size()>=sizeof(KeyType));
						return _details::_compare::equal(*(const KeyType*)a.data(), *(const KeyType*)b.data());
					}
					rt::String _keytype_name;
					cmp(){ _keytype_name = rt::TypeNameToString<KeyType>(); }
					virtual const char* Name() const { return _keytype_name; }
					virtual void FindShortestSeparator(std::string* start, const ::rocksdb::Slice& limit) const {}
					virtual void FindShortSuccessor(std::string* key) const {}
				};
				static const cmp _cmp;
				Opt.comparator = &_cmp;
				return *this;
			}
};

class RocksStorage
{
	friend class RocksDB;
	friend class RocksDBStandalone;

public:

	// ## disableDataSync
	// If true, then the contents of manifest and data files are not synced
	// to stable storage. Their contents remain in the OS buffers till the
	// OS decides to flush them. This option is good for bulk-loading
	// of data. Once the bulk-loading is complete, please issue a
	// sync to the OS to flush all dirty buffesrs to stable storage.

	// ## use_fsync
	// If true, then every store to stable storage will issue a fsync.
	// If false, then every store to stable storage will issue a fdatasync.
	// This parameter should be set to true while storing data to
	// filesystem like ext3 that can lose files after a reboot.

	// ## allow_os_buffer
	// Hint the OS that it should not buffer disk I/O. Enabling this
	// parameter may improve performance but increases pressure on the
	// system cache.
	// The exact behavior of this parameter is platform dependent.
	//
	// On POSIX systems, after RocksDB reads data from disk it will
	// mark the pages as "unneeded". The operating system may - or may not
	// - evict these pages from memory, reducing pressure on the system
	// cache. If the disk block is requested again this can result in
	// additional disk I/O.
	//
	// On WINDOWS system, files will be opened in "unbuffered I/O" mode
	// which means that data read from the disk will not be cached or
	// bufferized. The hardware buffer of the devices may however still
	// be used. Memory mapped files are not impacted by this parameter.

protected:
	::rocksdb::ColumnFamilyOptions	_DefaultOpenOpt;
	::rocksdb::DB*					_pDB;
	rt::String						_RootDir;
	::rocksdb::Options				_Options;
	struct CFEntry
	{
		::rocksdb::ColumnFamilyHandle*	pCF;
		::rocksdb::ColumnFamilyOptions	Opt;
		int								DBRefCo;  // refer count by RocksDB instances
		CFEntry(){ pCF = nullptr; DBRefCo = 0; }
	};

	rt::hash_map<rt::String, CFEntry>	_AllDBs;
	os::CriticalSection					_AllDBsCS;

	void		_CloseColumnFamily(::rocksdb::ColumnFamilyHandle* cf);

public:
	RocksStorage();
	~RocksStorage(){ Close(); }
	bool		Open(LPCSTR db_path, RocksStorageWriteRobustness robustness = ROCKSSTG_DEFAULT, bool open_existed_only = false, UINT file_thread_co = 2, UINT logfile_num_max = 1, RocksStorageCache cache = ROCKSDB_DEFAULT_CACHE);
	bool		Open(LPCSTR db_path, const Options* opt);
	bool		IsOpen() const { return _pDB!=nullptr; }
	void		Close(bool clear_alldbs = true);
	auto		Get(const rt::String_Ref& name, bool create_auto = true) -> RocksDB::_RocksDBIntl;
	void		Drop(const rt::String_Ref& name);

	bool		Compact(os::ProgressReport* prog = nullptr); // slow deep compact by moving all data to a new storage
	uint64_t	GetDiskOccupation() const;

	/**
	 * @brief first ':' in the name will be treated as wild prefix
	 * so you can set db_name to "abc:" and all column famlity with db_name starts with "abc:" will be applied the specified options
	 * @param db_name 
	 * @param opt 
	 */
	void		SetDBOpenOption(LPCSTR db_name, const RocksDBOpenOption& opt);
	void		SetDBDefaultOpenOption(const RocksDBOpenOption& opt){ _DefaultOpenOpt = opt; }

	static bool Nuke(LPCSTR db_path);
	static bool Rename(LPCSTR db_old_path, LPCSTR db_new_path);
};

class RocksDBStandalone: public RocksDB
{
	RocksStorage	_Storage;
private: 
	RocksDBStandalone(const RocksDB& x);
	void Empty();

public:
	RocksDBStandalone() = default;
	~RocksDBStandalone(){ Close(); }
	bool	Open(LPCSTR db_path, RocksStorageWriteRobustness robustness = ROCKSSTG_DEFAULT, bool open_existed_only = false, UINT file_thread_co = 2, UINT logfile_num_max = 1);
	bool	IsOpen() const { return _Storage.IsOpen(); }
	void	Close();
};

namespace _details
{
#pragma pack(push, 1)
template<int PAGE_METADATA_SIZE, typename T_VALUESIZE>
struct _ValueInStg
{	BYTE			Metadata[PAGE_METADATA_SIZE];
	T_VALUESIZE		TotalSize;
	BYTE			Data[1];
};
	template<typename T_VALUESIZE>
	struct _ValueInStg<0, T_VALUESIZE>
	{	T_VALUESIZE		TotalSize;
		BYTE			Data[1];
	};
#pragma pack(pop)

extern ::rt::BufferEx<BYTE>& ThreadLocalRocksPagedBaseStoreBuffer();

template<typename T_KEYVAL, int METADATA_SIZE = 0, UINT PAGING_SIZE = 64*1024, typename T_PAGE = WORD, typename T_VALUESIZE = UINT, class DB_CLS = RocksDB>
class RocksPagedBase: public DB_CLS
{	typedef DB_CLS _SC;
protected:
#pragma pack(push, 1)
	struct HashKeyPaged
	{	T_KEYVAL						Hash;
		rt::ByteOrderSwapped<T_PAGE>	Page;
		HashKeyPaged(const T_KEYVAL& h, T_PAGE p):Hash(h){ Page = p; }
		TYPETRAITS_DECLARE_POD;
	};
	struct ValueInStg: public _ValueInStg<METADATA_SIZE, T_VALUESIZE>
	{	typedef _ValueInStg<METADATA_SIZE, T_VALUESIZE> _SC;
		bool	IsUnpaged() const { return _SC::TotalSize<=PAGING_SIZE; }
		T_PAGE	GetPageCount() const { T_PAGE ret; ret = (T_PAGE)((_SC::TotalSize+PAGING_SIZE+1)/PAGING_SIZE); return ret; }
	};
#pragma pack(pop)
protected:
	void	_DeleteWrittenPages(const T_KEYVAL& h, T_PAGE last_page)
			{	_SC::Delete(h);
				HashKeyPaged key(h, 1);
				for(T_PAGE p = 1; p <= last_page; key.Page = ++p)
					_SC::Delete(key);
			}
public:
	static const UINT VALUE_PREFIX_SIZE = offsetof(ValueInStg, Data);
	void	DeleteAllPages(const T_KEYVAL& b)
			{	std::string data;
				auto* vis = GetPaged(b, 0, data);
				if(vis)
				{	_SC::Delete(b);
					if(vis->IsUnpaged())return;
					HashKeyPaged key(b, 1);
					T_PAGE end = vis->GetPageCount();
					for(T_PAGE p = 1; p < end; key.Page = ++p)
						_SC::Delete(key);
				}
			}
protected:
	/**
	* @brief Get the Paged object
	* first page will have FIRSTPAGE_PREFIX_SIZE bytes in `ws` before actual data
	* @param b 
	* @param page_no 
	* @param ws 
	* @return const ValueInStg* 
	*/
	auto	GetPaged(const T_KEYVAL& b, T_PAGE page_no, std::string& ws) const -> const ValueInStg* 
			{
				if(page_no == 0){ if(!_SC::Get(b, ws))return nullptr; }
				else{ if(!_SC::Get(HashKeyPaged(b, page_no), ws))return nullptr; }
				return (ValueInStg*)ws.data();
			}
	bool	GetPaged(const T_KEYVAL& b, std::string& ws, void* p_metadata) const
			{
				ws.clear();
				auto it = _SC::Seek(b);
				if(!it.IsValid())return false;
				auto& key = it.template Key<HashKeyPaged>();
				if(key.Hash != b)return false;

				auto& first_page = it.template Value<ValueInStg>();
				if(p_metadata)rt::Copy<METADATA_SIZE>(p_metadata, first_page.Metadata);

				UINT total_size = first_page.TotalSize;
				ws.append((LPSTR)first_page.Data, it.ValueLength() - VALUE_PREFIX_SIZE);
				if(first_page.IsUnpaged()){ ASSERT(ws.size() == total_size); return true; }
			
				UINT page_co = first_page.GetPageCount();
				for(UINT p=1; p<page_co; p++)
				{
					it.Next();
					if(!it.IsValid())return false;
					auto& key = it.template Key<HashKeyPaged>();
					if(key.Hash != b || key.Page != p)return false;

					auto& val = it.template Value<ValueInStg>();
					UINT data_size = (UINT)(it.ValueLength() - VALUE_PREFIX_SIZE);
					if(	(p<page_co-1 && data_size != PAGING_SIZE) ||
						(p == page_co-1 && data_size != (total_size%PAGING_SIZE))
					)return false;

					ws.append((LPSTR)val.Data, data_size);
				}
				return true;
			}

	bool	LoadAllPages(const T_KEYVAL& b, const ValueInStg* first_page, LPBYTE data_out) const
			{	
				if(first_page->IsUnpaged())
				{	memcpy(data_out, first_page->Data, first_page->TotalSize);
					return true;
				}
				else
				{	memcpy(data_out, first_page->Data, PAGING_SIZE);
					data_out += PAGING_SIZE;
				}

				UINT page_co = first_page->GetPageCount();
				auto it = _SC::Seek(HashKeyPaged(b,1));
				for(T_PAGE p=1; p<page_co; p++, it++)
				{	
					if(!it.IsValid())return false;
					auto& key = it.template Key<HashKeyPaged>();
					if(key.Hash != b || key.Page != p)return false;

					auto& val = it.Value();
					UINT data_size = (UINT)(val.size() - VALUE_PREFIX_SIZE);
					if(	(p<page_co-1 && data_size != PAGING_SIZE) ||
						(p == page_co-1 && data_size != (first_page->TotalSize%PAGING_SIZE))
					)return false;

					memcpy(data_out, val.data() + VALUE_PREFIX_SIZE, data_size);
					data_out += data_size;
				}

				return true;
			}
	/**
	 * @brief Set the Paged With Input Touched object
	 * WARNING: input data will be touch (change and revert back to original value), [data-DATA_PREFIX_SIZE] will be written
	 * @param b 
	 * @param data_with_prefixspace 
	 * @param size 
	 * @param meta 
	 * @return true 
	 * @return false 
	 */
	bool	SetPagedWithInputTouched(const T_KEYVAL& b, LPBYTE data_with_prefixspace, T_VALUESIZE size, LPCBYTE meta) 
			{
				ValueInStg touch_orig;

				auto& vis = *(ValueInStg*)(data_with_prefixspace - VALUE_PREFIX_SIZE);
				touch_orig = vis;
				rt::Copy<METADATA_SIZE>(&vis, meta);
				vis.TotalSize = size;

				bool ret = _SC::Set(b, ext::SliceValue(&vis, rt::min((T_VALUESIZE)PAGING_SIZE, size) + VALUE_PREFIX_SIZE));
				vis = touch_orig;

				if(!ret)return false;
				if(size <= PAGING_SIZE)return true;
				
				HashKeyPaged dbkey(b, 1);
				T_PAGE page = 1;
				for(UINT i = PAGING_SIZE; i<size; i += PAGING_SIZE, dbkey.Page = ++page)
				{
					UINT pagesize = rt::min(PAGING_SIZE, size - i);

					auto& vis = *(ValueInStg*)(data_with_prefixspace + i - VALUE_PREFIX_SIZE);
					touch_orig = vis;
					rt::Copy<METADATA_SIZE>(&vis, meta);
					vis.TotalSize = size;

					ret = _SC::Set(dbkey, ext::SliceValue(&vis, pagesize + VALUE_PREFIX_SIZE));
					vis = touch_orig;

					if(!ret)
					{
						_DeleteWrittenPages(b, (size + PAGING_SIZE - 1)/PAGING_SIZE);
						return false;
					}
				}

				return true;
			}
	bool	SetPaged(const T_KEYVAL& b, LPCBYTE data, T_VALUESIZE size, LPCBYTE meta)
			{
				auto& buf = ThreadLocalRocksPagedBaseStoreBuffer();

				T_VALUESIZE page_size = rt::min((T_VALUESIZE)PAGING_SIZE, size);
				buf.SetSize(page_size + VALUE_PREFIX_SIZE);

				auto& vis = *(ValueInStg*)buf.Begin();
				rt::Copy<METADATA_SIZE>(&vis, meta);
				vis.TotalSize = size;
				memcpy(vis.Data, data, page_size);

				if(!_SC::Set(b, ext::SliceValue(&vis, page_size + VALUE_PREFIX_SIZE)))
					return false;

				if(size <= PAGING_SIZE)return true;
				
				HashKeyPaged dbkey(b, 1);
				T_PAGE page = 1;
				for(UINT i = PAGING_SIZE; i<size; i += PAGING_SIZE, dbkey.Page = ++page)
				{
					page_size = rt::min(PAGING_SIZE, size - i);
					buf.SetSize(page_size + VALUE_PREFIX_SIZE);

					auto& vis = *(ValueInStg*)buf.Begin();
					rt::Copy<METADATA_SIZE>(&vis, meta);
					vis.TotalSize = size;
					memcpy(vis.Data, data + i, page_size);

					if(!_SC::Set(dbkey, ext::SliceValue(&vis, page_size + VALUE_PREFIX_SIZE)))
					{
						_DeleteWrittenPages(b, page);
						return false;
					}
				}

				return true;
			}
	bool	SetPaged(const T_KEYVAL& b, os::File& file, UINT size, LPCBYTE meta)
			{
				auto& buf = ThreadLocalRocksPagedBaseStoreBuffer();
				file.SeekToBegin();

				T_VALUESIZE page_size = rt::min((T_VALUESIZE)PAGING_SIZE, size);
				buf.SetSize(page_size + VALUE_PREFIX_SIZE);

				auto& vis = *(ValueInStg*)buf.Begin();
				rt::Copy<METADATA_SIZE>(&vis, meta);
				vis.TotalSize = size;
				if(	file.Read(vis.Data, page_size) != page_size || 
					!_SC::Set(b, ext::SliceValue(&vis, page_size + VALUE_PREFIX_SIZE))
				)return false;

				if(size <= PAGING_SIZE)return true;
				
				HashKeyPaged dbkey(b, 1);
				T_PAGE page = 1;
				for(UINT i = PAGING_SIZE; i<size; i += PAGING_SIZE, dbkey.Page = ++page)
				{
					page_size = rt::min(PAGING_SIZE, size - i);
					buf.SetSize(page_size + VALUE_PREFIX_SIZE);

					auto& vis = *(ValueInStg*)buf.Begin();
					rt::Copy<METADATA_SIZE>(&vis, meta);
					vis.TotalSize = size;

					if(	file.Read(vis.Data, page_size) != page_size ||
						!_SC::Set(dbkey, ext::SliceValue(&vis, page_size + VALUE_PREFIX_SIZE)))
					{
						_DeleteWrittenPages(b, page);
						return false;
					}
				}

				return true;
			}
public:
	bool	LoadAllPages(const T_KEYVAL& b, rt::BufferEx<BYTE>& out, std::string& workspace) const
			{
				auto* first_page = GetPaged(b, 0, workspace);
				if(!first_page|| !out.ChangeSize(first_page->TotalSize))return false;
				return LoadAllPages(b, first_page, out);
			}
	bool	LoadAllPages(const T_KEYVAL& b, rt::BufferEx<BYTE>& out) const
			{	std::string workspace;
				return LoadAllPages(b, out, workspace);
			}
	RocksCursor Seek(const SliceValue& begin, const ReadOptions* opt = RocksDB::ReadOptionsDefault) const
	{	::rocksdb::Iterator* it = rt::_CastToNonconst(_SC::_pDB)->NewIterator(*opt, _SC::_pCF);
		ASSERT(it);
		it->Seek(begin);
		return RocksCursor(it, sizeof(T_KEYVAL));
	}
	RocksCursor First(const ReadOptions* opt = RocksDB::ReadOptionsDefault) const
	{	::rocksdb::Iterator* it = rt::_CastToNonconst(_SC::_pDB)->NewIterator(*opt, _SC::_pCF);
		ASSERT(it);
		it->SeekToFirst();
		return RocksCursor(it, sizeof(T_KEYVAL));
	}
	RocksCursor Last(const ReadOptions* opt = RocksDB::ReadOptionsDefault) const
	{	::rocksdb::Iterator* it = rt::_CastToNonconst(_SC::_pDB)->NewIterator(*opt, _SC::_pCF);
		ASSERT(it);
		it->SeekToLast();
		return RocksCursor(it, -(int)sizeof(T_KEYVAL));
	}
	template<typename func_visit>
	SIZE_T ScanBackward(const func_visit& v, const SliceValue& begin, const ReadOptions* opt = RocksDB::ReadOptionsDefault) const { return _SC::_ScanBackward<-(int)sizeof(T_KEYVAL)>(v, begin, opt); }
	template<typename func_visit>
	SIZE_T ScanBackward(const func_visit& v, const ReadOptions* opt = RocksDB::ReadOptionsDefault) const{ return _SC::_ScanBackward<-(int)sizeof(T_KEYVAL)>(v, opt); }
	template<typename func_visit>
	SIZE_T Scan(const func_visit& v, const SliceValue& begin, const ReadOptions* opt = RocksDB::ReadOptionsDefault) const { return _SC::_Scan<sizeof(T_KEYVAL)>(v, begin, opt); }
	template<typename func_visit>
	SIZE_T Scan(const func_visit& v, const ReadOptions* opt = RocksDB::ReadOptionsDefault) const { return _SC::_Scan<sizeof(T_KEYVAL)>(v, opt); }
};

template<typename T_KEYVAL, typename T_METADATA, int PAGING_SIZE = 64*1024, typename T_PAGE = WORD, typename T_VALUESIZE = UINT, class DB_CLS = RocksDB>
class RocksPagedBaseT: public RocksPagedBase<T_KEYVAL, sizeof(T_METADATA), PAGING_SIZE, T_PAGE, T_VALUESIZE, DB_CLS>
{	typedef RocksPagedBase<T_KEYVAL, sizeof(T_METADATA), PAGING_SIZE, T_PAGE, T_VALUESIZE, DB_CLS> _SC;
public:
	typedef T_METADATA MetadataType;
#pragma pack(push, 1)
	struct ValueType: public T_METADATA
	{	
		T_VALUESIZE	TotalSize;
		BYTE		Data[1];
		bool		IsUnpaged() const { return TotalSize>PAGING_SIZE; }
		T_PAGE		GetPageCount() const { T_PAGE ret; ret = (T_PAGE)((TotalSize+PAGING_SIZE+1)/PAGING_SIZE); return ret; }
		UINT		GetPageSize() const {  }
	};
#pragma pack(pop)
	ValueType*	GetPaged(const T_KEYVAL& b, T_PAGE page_no, std::string& ws) const { return (ValueType*)_SC::GetPaged(b, page_no, ws); }
	bool		GetPaged(const T_KEYVAL& b, std::string& ws, T_METADATA* p_metadata = nullptr) const { return _SC::GetPaged(b, ws, p_metadata); }
	bool		LoadAllPages(const T_KEYVAL& b, const ValueType* first_page, LPVOID data_out) const { return _SC::LoadAllPages(b, (typename _SC::ValueInStg*)first_page, (LPBYTE)data_out); }
	bool		SetPagedWithInputTouched(const T_KEYVAL& b, const T_METADATA& metadata, LPVOID data_with_prefixspace_ahead, UINT size) // WARNING: input data will be touch (change and revert back to original value), [data-DATA_PREFIX_SIZE] will be written
				{	return _SC::SetPagedWithInputTouched(b, (LPBYTE)data_with_prefixspace_ahead, size, (LPCBYTE)&metadata);
				}
	bool		SetPaged(const T_KEYVAL& b, const T_METADATA& metadata, LPCVOID data, UINT size)
				{	return _SC::SetPaged(b, (LPBYTE)data, size, (LPCBYTE)&metadata);
				}
	bool		SetPaged(const T_KEYVAL& b, const T_METADATA& metadata, os::File& file, UINT size)
				{	return _SC::SetPaged(b, file, size, (LPCBYTE)&metadata);
				}
};
	template<typename T_KEYVAL, int PAGING_SIZE, typename T_PAGE, typename T_VALUESIZE, class DB_CLS>
	class RocksPagedBaseT<T_KEYVAL, void, PAGING_SIZE, T_PAGE, T_VALUESIZE, DB_CLS>: public RocksPagedBase<T_KEYVAL, 0, PAGING_SIZE, T_PAGE, T_VALUESIZE, DB_CLS>
	{	typedef RocksPagedBase<T_KEYVAL, 0, PAGING_SIZE, T_PAGE, T_VALUESIZE, DB_CLS> _SC;
	public:
		typedef void MetadataType;
#pragma pack(push, 1)
		struct ValueType
		{	
			T_VALUESIZE	TotalSize;
			BYTE		Data[1];
			bool		IsUnpaged() const { return TotalSize>PAGING_SIZE; }
			T_PAGE		GetPageCount() const { T_PAGE ret; ret = (T_PAGE)((TotalSize+PAGING_SIZE+1)/PAGING_SIZE); return ret; }
		};
#pragma pack(pop)
		ValueType*	GetPaged(const T_KEYVAL& b, T_PAGE page_no, std::string& ws) const { return (ValueType*)_SC::GetPaged(b, page_no, ws);	}
		bool		GetPaged(const T_KEYVAL& b, std::string& ws) const { return _SC::GetPaged(b, ws); }
		bool		LoadAllPages(const T_KEYVAL& b, const ValueType* first_page, LPVOID data_out) const { return _SC::LoadAllPages(b, (typename _SC::ValueInStg*)first_page, (LPBYTE)data_out); }
		bool		SetPagedWithInputTouched(const T_KEYVAL& b, LPVOID data_with_prefixspace_ahead, UINT size){ return _SC::SetPagedWithInputTouched(b, (LPBYTE)data_with_prefixspace_ahead, size, nullptr); } // WARNING: input data will be touch (change and revert back to original value), [data-DATA_PREFIX_SIZE] will be written
		bool		SetPaged(const T_KEYVAL& b, LPCVOID data, UINT size){ return _SC::SetPaged(b, (LPCBYTE)data, size, nullptr); }
		bool		SetPaged(const T_KEYVAL& b, os::File& file, UINT size){ return _SC::SetPaged(b, file, size, nullptr); }
	};
} // namespace _details

template<typename T_KEYVAL, typename T_PAGE_METADATA = void, int PAGING_SIZE = 64*1024, typename T_PAGE = WORD, typename T_VALUESIZE = UINT>
class RocksDBPaged: public _details::RocksPagedBaseT<T_KEYVAL, T_PAGE_METADATA, PAGING_SIZE, T_PAGE, T_VALUESIZE, RocksDB>
{
public:
	RocksDBPaged(){ RocksDB::Empty(); }
	RocksDBPaged(const RocksDB& x) = delete;
	RocksDBPaged(RocksDBPaged&& x){ rt::Copy(*this, x); rt::Zero(x); }
	
	void operator = (RocksDB::_RocksDBIntl&& x){ RocksDB::operator = (std::move(x)); }
	RocksDBPaged(RocksDB::_RocksDBIntl& x){ *this = std::move(x); }
	RocksDBPaged(RocksDB::_RocksDBIntl&& x){ *this = std::move(x); }
};

template<typename T_KEYVAL, typename T_PAGE_METADATA = void, int PAGING_SIZE = 64*1024, typename T_PAGE = WORD, typename T_VALUESIZE = UINT>
using RocksDBStandalonePaged = _details::RocksPagedBaseT<T_KEYVAL, T_PAGE_METADATA, PAGING_SIZE, T_PAGE, T_VALUESIZE, RocksDBStandalone>;

template<char separator = ':'>
class SeparatorPrefixTransform : public ::rocksdb::SliceTransform 
{
public:
	explicit SeparatorPrefixTransform() = default;
    virtual const char* Name() const override { return "SeparatorPrefixTransform"; }
	virtual ::rocksdb::Slice Transform(const ::rocksdb::Slice& src) const override
	{	const char* p = src.data();
		const char* sep = strchr(p, separator);
		if(sep)
		{	return ::rocksdb::Slice(src.data(), (int)(sep - p));
		}else return src;
	}
	virtual bool InDomain(const ::rocksdb::Slice& src) const override {	return true; }
	virtual bool InRange(const ::rocksdb::Slice& dst) const override { return dst[dst.size()-1] == ':' || strchr(dst.data(), ':') == nullptr; }
	virtual bool SameResultWhenAppended(const ::rocksdb::Slice& prefix) const override { return strchr(prefix.data(), ':') != nullptr; }
};

#define ALLOCA_DBKEY(varname, ...)	auto	varname##_strexp = __VA_ARGS__;	\
									char*	varname##_buf = (char*)alloca(varname##_strexp.GetLength());	\
									UINT	varname##_strlen = (UINT)varname##_strexp.CopyTo(varname##_buf); \
									SliceValue varname(varname##_buf, varname##_strlen); \


template<typename T>
inline void NegateFirstBit(T& out)
{
	if(rt::NumericTraits<T>::IsSigned)
	{
		LPBYTE p = (LPBYTE)&out;
		if((p[0] & 0x80) == 0x80)
		{
			p[0] = p[0] & 0x7f;
		}
		else p[0] = p[0] | 0x80;
	}
}
template<typename T>
inline  T ToSwappedByteOrder(const T& x)
{
	T out = x;
	rt::SwapByteOrder(out);
	NegateFirstBit<T>(out);
	return out;
}
template<typename T>
inline  T ToNormalByteOrder(const T& x)
{
	T out = x;
	NegateFirstBit<T>(out);
	rt::SwapByteOrder(out);
	return out;
}

template<bool Reverse, typename... Values> struct ToRightByteOrder;
template<bool Reverse> struct ToRightByteOrder<Reverse> {};

template<bool Reverse, typename Head, typename... Tail>
struct ToRightByteOrder<Reverse, Head, Tail...>
	: public ToRightByteOrder<Reverse, Tail...>
{
	Head m_head;

	typedef ToRightByteOrder<Reverse, Tail...> inherited;
	ToRightByteOrder() {}
	ToRightByteOrder(const Head& value, Tail... vtail) :inherited(vtail...)
	{
		m_head = ToSwappedByteOrder<Head>(value);
		if(Reverse) m_head = ~m_head;
	}
	Head getHead() const
	{
		if(!Reverse)
			return(ToNormalByteOrder<Head>(m_head));
		else
			return(~ToNormalByteOrder<Head>(m_head));
	}
	void setHead(Head& value)
	{
		m_head = ToSwappedByteOrder<Head>(value);
		if(Reverse) m_head = ~m_head;
	}
};

template <int N, typename ... __args_type>
struct RightByteOrder_element;

template <int N, bool Reverse>
struct RightByteOrder_element<N, ToRightByteOrder<Reverse>>
{
	static_assert(0 > N, "Index outside of tuple!");
};

template <int N, bool Reverse, typename Head, typename ... Tail>
struct RightByteOrder_element<N, ToRightByteOrder<Reverse, Head, Tail ...>>
	: public RightByteOrder_element<N - 1, ToRightByteOrder<Reverse, Tail ...>> {};

template <bool Reverse, typename Head, typename ... Tail>
struct RightByteOrder_element<0, ToRightByteOrder<Reverse, Head, Tail ...>>
{
	using value_type = Head;
	using class_type = ToRightByteOrder<Reverse, Head, Tail ...>;
};

template <int N, bool Reverse, typename ... Values>
inline auto getRightByteOrderElement(ToRightByteOrder<Reverse, Values ...>& tu)
{
	using __class_type = typename RightByteOrder_element<N, ToRightByteOrder<Reverse, Values ...>>::class_type;
	return ((__class_type&)tu).getHead();
}
template <int N, bool Reverse, typename Head, typename ... Tail>
inline auto setRightByteOrderElement(Head value, ToRightByteOrder<Reverse, Head, Tail ...>& tu)
{
	using __class_type = typename RightByteOrder_element<N, ToRightByteOrder<Reverse, Head, Tail ...>>::class_type;
	((__class_type&)tu).setHead(value);
}
/** @}*/
} // namespace ext
/** @}*/
