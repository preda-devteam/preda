#include "../../os/platform.h"
#include "rocksdb.inc"  // should come before "rocksdb.h"
#include "rocksdb.h"

namespace ext
{

const WriteOptions*	RocksDB::WriteOptionsFastRisky = nullptr;
const WriteOptions*	RocksDB::WriteOptionsDefault = nullptr;
const WriteOptions*	RocksDB::WriteOptionsRobust = nullptr;
const ReadOptions*	RocksDB::ReadOptionsDefault = nullptr;

namespace _details
{

struct __InitRocksDBOptions
{
	struct WriteOptionsMore: public rocksdb::WriteOptions
	{	WriteOptionsMore(int mode)
		{	switch(mode)
			{
			case 0: sync = false;	disableWAL = false; break;
			case 1:	sync = false;	disableWAL = true; break;
			case 2:	sync = true;	disableWAL = false; break;
			}
		}
	};

	__InitRocksDBOptions()
	{
		static const WriteOptionsMore	_WriteOptionsDefault = 0;
		static const WriteOptionsMore	_WriteOptionsFastRisky = 1;
		static const WriteOptionsMore	_WriteOptionsRobust = 2;
		
		RocksDB::WriteOptionsFastRisky = &_WriteOptionsFastRisky;
		RocksDB::WriteOptionsDefault = &_WriteOptionsDefault;
		RocksDB::WriteOptionsRobust = &_WriteOptionsRobust;

		static const ReadOptions	_ReadOptionsDefault;
		RocksDB::ReadOptionsDefault = &_ReadOptionsDefault;
	}
};

__InitRocksDBOptions	g_InitRocksDBOptions;

rt::BufferEx<BYTE>& ThreadLocalRocksPagedBaseStoreBuffer()
{
	thread_local rt::BufferEx<BYTE> _;
	return _;
}

} // namespace _details

RocksDBOpenOption& RocksDBOpenOption::PointLookup(UINT cache_size_mb)
{	
#if !defined(ROCKSDB_LITE)
	Opt.OptimizeForPointLookup(cache_size_mb);
#endif	
	return *this; 
}

RocksStorage::RocksStorage()
{
	_pDB = nullptr;
	_DefaultOpenOpt.OptimizeForSmallDb();
}

void RocksStorage::SetDBOpenOption(LPCSTR db_name, const RocksDBOpenOption& opt)
{
	EnterCSBlock(_AllDBsCS);
	auto& e = _AllDBs[db_name];
	ASSERT(e.pCF == nullptr);
	e.Opt = opt;
}

bool RocksStorage::Open(LPCSTR db_path, RocksStorageWriteRobustness robustness, bool open_existed_only, UINT file_thread_co, UINT logfile_num_max, RocksStorageCache cache)
{
	ASSERT(_pDB == nullptr);

	_Options.OptimizeForSmallDb();

	_Options.create_if_missing = !open_existed_only;
	_Options.create_missing_column_families = !open_existed_only;
	_Options.max_file_opening_threads = file_thread_co;
	_Options.keep_log_file_num = logfile_num_max;
	_Options.delete_obsolete_files_period_micros = 1ULL * 60 * 60 * 1000000;  // 1 hour

	switch(robustness)
	{
	case ROCKSSTG_FASTEST:
		//opt.disableDataSync = true;
		_Options.use_fsync = false;
		//opt.allow_os_buffer = true;
		_Options.paranoid_checks = false;
		break;
	case ROCKSSTG_DEFAULT:		
		//opt.disableDataSync = false;
		_Options.use_fsync = false;
		//opt.allow_os_buffer = true;
		break;
	case ROCKSSTG_STRONG:
		//opt.disableDataSync = false;
		_Options.use_fsync = true;
		//opt.allow_os_buffer = false;
		break;
	default:
		ASSERT(0);
		return false;
	}
  
	BlockBasedTableOptions table_options;
	switch(cache)
	{
	case ROCKSDB_NO_CACHE:
		table_options.no_block_cache = true;
		_Options.table_factory.reset(NewBlockBasedTableFactory(table_options));
		break;
	case ROCKSDB_LARGE_CACHE:
		{
			auto new_cache = ::rocksdb::NewLRUCache(1 * 1024 * 1024 * 1024LL);
			table_options.block_cache = new_cache;
			_Options.table_factory.reset(NewBlockBasedTableFactory(table_options));
		}
		break;
	default: break;
	}

	return Open(db_path, &_Options);
}

bool RocksStorage::Nuke(LPCSTR db_path)
{
	if(!os::File::IsExist(db_path))return true;

	for(UINT i=0; i<10; i++)
	{
		bool ok = ::rocksdb::DestroyDB(db_path, ::rocksdb::Options()).ok() &&
				  os::File::RemovePath(db_path);
		os::Sleep(100);
		if(ok)return true;
	}

	return false;
}

bool RocksStorage::Rename(LPCSTR db_old_path, LPCSTR db_new_path)
{
	if(!os::File::IsExist(db_old_path))
		return false;

	for(UINT i=0; i<30; i++) // retry within 3 seconds
	{
		if(os::File::Rename(db_old_path, db_new_path))
			return true;

		os::Sleep(100);
	}

	return false;
}

bool RocksStorage::Open(LPCSTR db_path, const Options* opt)
{
	LPCSTR default_cfname = "default";

	ASSERT(_pDB == nullptr);
	ASSERT(opt);

	if(opt->create_if_missing)
		os::File::CreateDirectories(db_path, false);

	std::vector<std::string>	cfs;
	if(!::rocksdb::DB::ListColumnFamilies(*opt, db_path, &cfs).ok())
	{
		if(!opt->create_if_missing)return false;
		cfs.push_back(default_cfname);
	}

	if(&_Options != opt)
		_Options = *opt;

	{
		std::vector<::rocksdb::ColumnFamilyDescriptor>	cfds;
		std::vector<::rocksdb::ColumnFamilyHandle*>	cfptrs;

		cfds.resize(cfs.size());
		cfptrs.resize(cfs.size());

		EnterCSBlock(_AllDBsCS);

		bool drop_default = cfs.size() > 1;
		if(drop_default && _AllDBs.find(default_cfname) != _AllDBs.end())
			drop_default = false;

		for(UINT i=0; i<cfs.size(); i++)
		{
			cfds[i].name = cfs[i];
			auto it = _AllDBs.find(cfs[i].c_str());
			if(it == _AllDBs.end())
			{
				rt::String_Ref name(cfs[i]);
				int pos;
				if((pos = (int)name.FindCharacter(':')) > 0)
				{
					auto wild_it = _AllDBs.find(ALLOCA_C_STRING(name.SubStr(0, pos+1)));
					if(wild_it != _AllDBs.end())
					{
						cfds[i].options = _AllDBs[cfs[i].c_str()].Opt = wild_it->second.Opt;
						continue;
					}
				}

				_AllDBs[cfs[i].c_str()].Opt = _DefaultOpenOpt;
				cfds[i].options = _DefaultOpenOpt;
			}

			cfds[i].options = _AllDBs[cfs[i].c_str()].Opt;
		}

		if(::rocksdb::DB::Open(*opt, db_path, cfds, &cfptrs, &_pDB).ok())
		{
			for(UINT i=0; i<cfs.size(); i++)
			{	
				if(drop_default && cfs[i] == default_cfname)
				{
					_pDB->DropColumnFamily(cfptrs[i]);
					_pDB->DestroyColumnFamilyHandle(cfptrs[i]);
					continue;
				}
				
				_AllDBs[cfs[i].c_str()].pCF = cfptrs[i];
			}

			if(drop_default)
				_AllDBs.erase(default_cfname);

			_RootDir = db_path;
			return true;
		}
	}

	return false;
}

RocksDB::_RocksDBIntl RocksStorage::Get(const rt::String_Ref& name, bool create_auto)
{
	if(name.Last() == ':')return RocksDB::_RocksDBIntl();
	ASSERT(IsOpen());

	EnterCSBlock(_AllDBsCS);

	LPCSTR sname = ALLOCA_C_STRING(name);
	auto it = _AllDBs.find(sname);
	if(it != _AllDBs.end())
	{
		if(it->second.pCF)
		{
			it->second.DBRefCo++;
			return RocksDB::_RocksDBIntl(this, it->second.pCF);
		}
	}

	if(create_auto)
	{
		CFEntry new_item;
		{
			auto it = _AllDBs.find(sname);
			if(it == _AllDBs.end())
			{
				rt::String_Ref ss(sname);
				int pos = (int)ss.FindCharacter(':');
				auto wild_it = _AllDBs.find(ss.SubStr(0, pos+1));
				if(wild_it != _AllDBs.end())
					new_item.Opt = wild_it->second.Opt;
				else
					new_item.Opt = _DefaultOpenOpt;
			}
			else
			{
				new_item.Opt = it->second.Opt;
			}
		}

		if(_pDB->CreateColumnFamily(new_item.Opt, sname, &new_item.pCF).ok())
		{
			new_item.DBRefCo = 1;
			_AllDBs[sname] = new_item;
			return RocksDB::_RocksDBIntl(this, new_item.pCF);
		}
	}

	return RocksDB::_RocksDBIntl();
}

void RocksStorage::Drop(const rt::String_Ref& name) // delete db
{
	if(name.Last() == ':')return;
	ASSERT(IsOpen());
	
	LPCSTR sname = ALLOCA_C_STRING(name);

	EnterCSBlock(_AllDBsCS);

	auto it = _AllDBs.find(name);
	if(it != _AllDBs.end() && it->second.pCF)
	{
		ASSERT(it->second.DBRefCo == 0); // RocksDB instance must be closed
		_pDB->DropColumnFamily(it->second.pCF);
		_pDB->DestroyColumnFamilyHandle(it->second.pCF);
		_AllDBs.erase(it);
	}
}

void RocksStorage::Close(bool clear_alldbs)
{
	if(_pDB)
	{
		{
			EnterCSBlock(_AllDBsCS);
			for(auto& it : _AllDBs)
				if(it.second.pCF)
				{
					ASSERT(it.second.DBRefCo == 0); // all RocksDB instances must be closed
					_pDB->DestroyColumnFamilyHandle(it.second.pCF);
					it.second.pCF = nullptr;
				}

			_AllDBs.clear();
		}

#if !defined(ROCKSDB_LITE)
		CancelAllBackgroundWork(_pDB, false);
#endif
		delete _pDB;  // it is allocated by rockdb library code, don't use _SafeDel here
		_pDB = nullptr;
	}
}

bool RocksStorage::Compact(os::ProgressReport* prog)
{
	ASSERT(_pDB);

	EnterCSBlock(_AllDBsCS);

	rt::String newdb_working = _RootDir + rt::SS("_compact_working_");
	rt::String newdb_finished = _RootDir + rt::SS("_compact_finished_");
	rt::String obsoleted = _RootDir + rt::SS("_compact_obsoleted_");

	{	
		if(!Nuke(newdb_working) || !Nuke(newdb_finished) || !Nuke(obsoleted))return false;

		::rocksdb::Options db_opt = _Options;
		if(prog)prog->SetProgressRange(GetDiskOccupation()/3);  // rough guess of the data amplification rate, 3x

		RocksStorage newdb;
		newdb.Open(newdb_working, &_Options);
		newdb.SetDBDefaultOpenOption(_DefaultOpenOpt);

		auto default_opt = _DefaultOpenOpt;
		rt::hash_map<rt::String, ::rocksdb::ColumnFamilyOptions> cf_opts;

		for(auto& it : _AllDBs)
		{
			ASSERT(it.second.pCF);
			ASSERT(it.second.DBRefCo == 0); // all RocksDB instances must be closed before compacting

			cf_opts[it.first] = it.second.Opt;
			newdb.SetDBOpenOption(it.first, it.second.Opt);
		
			RocksDB from = Get(it.first, false);
			RocksDB to = newdb.Get(it.first, true);

			// moving to a new database
			{
				auto it = from.First();
				while(it.IsValid())
				{
					if(!to.Set(it.Key(), it.Value()))
						goto FAILED;

					if(prog)prog->MakeProgress(it.KeyLength() + it.ValueLength());
					it++;
				}
			}
		}

		newdb.Close();

		for(int i=0;; i++)
		{
			os::Sleep(100);
			if(os::File::Rename(newdb_working, newdb_finished))break;
			if(i == 50)goto FAILED;
		}

		rt::String org = _RootDir;
		Close();

		for(int i=0;; i++)
		{
			os::Sleep(100);
			if(os::File::Rename(org, obsoleted))break;
			if(i == 50)goto FAILED;
		}

		VERIFY(os::File::Rename(newdb_finished, org));

		SetDBDefaultOpenOption(default_opt);
		for(auto it : cf_opts)
			SetDBOpenOption(it.first, it.second);

		bool ret = Open(org, &db_opt);
		if(!ret)
		{
			Nuke(org);
			VERIFY(os::File::Rename(obsoleted, org));

			SetDBDefaultOpenOption(default_opt);
			for(auto it : cf_opts)
				SetDBOpenOption(it.first, it.second);
			VERIFY(Open(org, &db_opt));
		}

		Nuke(obsoleted);
		return ret;
	}

FAILED:
	Nuke(newdb_working);
	Nuke(newdb_finished);
	Nuke(obsoleted);
	return false;
}

uint64_t RocksStorage::GetDiskOccupation() const
{
	os::FileList fl;
	uint32_t co = fl.Populate(_RootDir, nullptr, os::FileList::FLAG_RECURSIVE);

	uint64_t size = 0;
	for(uint32_t i=0; i<co; i++)
	{
		size += os::File::GetFileSize(fl.GetFullpath(i));
	}

	return size;
}

void RocksStorage::_CloseColumnFamily(::rocksdb::ColumnFamilyHandle* cf)
{
	if(cf)
	{
		EnterCSBlock(_AllDBsCS);
		for(auto& it : _AllDBs)
			if(it.second.pCF == cf)
			{
				ASSERT(it.second.DBRefCo > 0);
				it.second.DBRefCo--;
				return;
			}
	}
}

bool RocksDBStandalone::Open(LPCSTR db_path, RocksStorageWriteRobustness robustness, bool open_existed_only, UINT file_thread_co, UINT logfile_num_max)
{
	if(_Storage.Open(db_path, robustness, open_existed_only, file_thread_co, logfile_num_max))
	{
		*((RocksDB*)this) = _Storage.Get("default");
		ASSERT(_pCF);

		return true;
	}

	return false;
}

void RocksDBStandalone::Close()
{
	RocksDB::Empty();
	_Storage.Close();
}

bool RocksDB::HasNoEntry() const
{
	::rocksdb::Iterator* it = rt::_CastToNonconst(_pDB)->NewIterator(*ReadOptionsDefault, _pCF);
	bool ret = it && it->Valid();
	_SafeDel_Untracked(it); 

	return ret;
}

void RocksDB::Empty()
{
	if(_pStg)
	{	
		_pStg->_CloseColumnFamily(_pCF);

		_pDB = nullptr;
		_pCF = nullptr;
		_pStg = nullptr;
	}
}

void RocksDB::operator = (RocksDB::_RocksDBIntl&& x)
{
	_pStg = x._pStg;
	_pCF = x._pCF;
	_pDB = _pStg?_pStg->_pDB:nullptr;

	rt::Zero(x); 
}

RocksDB::_RocksDBIntl::~_RocksDBIntl()
{
	if(_pStg)
	{
		_pStg->_CloseColumnFamily(_pCF);
		rt::Zero(*this);
	}
}

} // namespace ext
