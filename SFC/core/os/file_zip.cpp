#include "file_zip.h"
#include "../../core/ext/botan/botan.h"
#include "../../core/ext/zlib/zlib.h"

#ifdef PLATFORM_WIN
#else
#define _7ZIP_ST
#endif

#include "../../core/ext/7zip/7zip.h"
#include <algorithm>

namespace os
{

DWORD _StreamBlockSize = 0;

void FileZip::_crc_checksum(LPCVOID pSrc, UINT SrcLen, LPDWORD crc32)
{
	sec::Hash<sec::HASH_CRC32>	crc;
	crc.Update(pSrc,SrcLen);
	crc.Finalize(crc32);
	rt::SwapByteOrder(*crc32);
}


FileZip::FileZip()
{
	_pZipFile = nullptr;
	m_CentralDirectoryStart = 0;
	m_CentralDirectoryModified = false;
	m_CompressionMode = (UINT)ZIP_STORE;

	stream_read_store.pThis = this;
	stream_write_store.pThis = this;

	stream_write_zlib.pThis = this;
	stream_read_zlib.pThis = this;

	_AddingNonZeroFileEntry = nullptr;
}

bool FileZip::Open(LPCSTR fn, LPCSTR mode, bool load_indexed)
{
	ASSERT(!IsOpen());
	return _BaseFile.Open(fn,mode) && Open(&_BaseFile,mode,load_indexed);
}

int	FileZip::FindFileRecursive(LPCSTR string, int start)
{
	int len = (int)strlen(string);
	for(int i=start; i<(int)m_FileEntries.GetSize(); i++)
	{
		FileEntry* en = (FileEntry*)m_FileEntries[i];
		if(en && en->FileNameLength>=len && memcmp(string, &en->FileName[en->FileNameLength-len],len)==0)
			return i;
	}
	return -1;
}

bool FileZip::Open(::rt::_File* pFile, LPCSTR mode, bool load_indexed)
{
	ASSERT(!IsOpen());
	ASSERT(pFile);

	m_Password.SetSize();
	_pZipFile = pFile;

	{	::rt::String_Ref	m(mode);
		m_IsReadOnly = m.FindCharacter('w')<0 && m.FindCharacter('+')<0;
	}

	if( mode[0] == 'w' && pFile->GetLength() == 0)
	{	// create new
		m_CentralDirectoryStart = 0;
		ASSERT(m_FileEntries.GetSize()==0);
		ASSERT(!m_IsReadOnly);
	}
	else
	{	// open existing
		DWORD filelen = (int)pFile->GetLength();
		if(filelen < sizeof(CentralDirectory)){ goto ERROR_OCCURED; }

		int len = (DWORD)rt::min(pFile->GetLength(), SIZE_T(0xffff + sizeof(CentralDirectory)));
		pFile->Seek(-len, rt::_File::Seek_End);

		rt::Buffer<BYTE>	cdir;
		VERIFY(cdir.SetSize(len));
		CentralDirectory*	pCD = nullptr;
		if(	pFile->Read(cdir,len) == len )
		{
			//for(UINT i=0;i<len - sizeof(CentralDirectory) + 4; i++)
			for(int i = len - sizeof(CentralDirectory) + 3;i>=0;i--)
			{
				CentralDirectory* p = (CentralDirectory*)(&cdir[i]);
				if( p->Signature == CentralDirectory::header_magic && p->m_uOffset < filelen )
				{	pCD = p;
					break;
				}
			}
		}

		if( pCD &&
			pCD->m_uThisDisk == 0 &&		// no volume support
			pCD->m_uDiskWithCD == 0 &&
			pCD->m_uDiskEntriesNo == pCD->m_uEntriesNumber &&
			(pCD->m_uSize + pCD->m_uOffset) < filelen
		){}
		else
		{ goto ERROR_OCCURED; }
		
		if(pCD->m_ZipCommentLength)
		{
			int len = rt::min(pCD->m_ZipCommentLength, (WORD)(((LPSTR)cdir.End()) - pCD->m_ZipComment));
			m_ZipComment = rt::String_Ref(pCD->m_ZipComment, len);
		}

		m_CentralDirectoryStart = pCD->m_uOffset;
		pFile->Seek(pCD->m_uOffset);
		VERIFY(_FileEntryPool.SetSize(pCD->m_uSize));
		if( pFile->Read(_FileEntryPool, pCD->m_uSize) == pCD->m_uSize )
		{
			// Load file list
			VERIFY(m_FileEntries.SetSize(pCD->m_uEntriesNumber));
			m_FileEntries.Zero();

			FileEntry* p = (FileEntry*)_FileEntryPool.Begin();
			for(UINT i=0;i<m_FileEntries.GetSize();i++)
			{
				if( p->Signature == FileEntry::header_magic &&
					((LPBYTE)p) + sizeof(FileEntry) <= _FileEntryPool.End() &&
					((LPBYTE)p) + sizeof(FileEntry) + p->FileNameLength + p->ExtraFieldLength + p->FileCommentLength - 1 <= _FileEntryPool.End()
				)
				{	m_FileEntries[i] = p;
					p = (FileEntry*)(((LPBYTE)p) + sizeof(FileEntry) + p->FileNameLength + p->ExtraFieldLength + p->FileCommentLength - 1);
				}
				else
				{	goto ERROR_OCCURED;
				}
			}

			m_ListSorted = false;
			if(load_indexed)
				ReindexAllEntries();
			
			m_CentralDirectoryModified = false;
		}
	}

	return true;

ERROR_OCCURED:
	Close();
	return false;
}

void FileZip::_FreeFileEntry(FileEntryPtr& ptr)
{
	ptr.Empty();
	FileEntry* p = ptr;
	if(p==nullptr || (p>=(LPCVOID)_FileEntryPool.Begin() && p<(LPCVOID)_FileEntryPool.End()) ){}
	else
	{
		_SafeFree32AL(ptr.p);
	}
}

void FileZip::Close()
{
	ASSERT(_AddingNonZeroFileEntry == nullptr);

	if(IsOpen())
	{
		Save();
		// flush ...
		_BaseFile.Close();
	}

	for(UINT i=0;i<m_FileEntries.GetSize();i++)
		_FreeFileEntry(m_FileEntries[i]);

	m_FileEntries.SetSize(0);
	m_ZipComment.Empty();
	m_CentralDirectoryStart = 0;

	_pZipFile = nullptr;
}


int FileZip::FindFile(const rt::String_Ref& pathname)
{
	if(!m_FileEntries.GetSize())return -1;
	
	if(m_ListSorted)
	{
		SIZE_T idx = rt::BinarySearch(m_FileEntries,m_FileEntries.GetSize(),pathname);
		if(idx < m_FileEntries.GetSize() && m_FileEntries[idx].p->Signature)
			return (int)idx;
	}
	else
	{
		for(UINT i=0;i<m_FileEntries.GetSize();i++)
			if(m_FileEntries[i] == pathname)return i;
	}

	return -1;
}

bool FileZip::AddZeroSizedEntry(const rt::String_Ref& pathname, __time64_t ftime, DWORD attrib)
{
	ASSERT(_AddingNonZeroFileEntry == nullptr);
	if(pathname.GetLength() > 0xffff)return false;
	if(m_FileEntries.GetSize() >= 0xffff)return false;
	ASSERT(!m_IsReadOnly);

	int slash_add = pathname[pathname.GetLength()-1] != '/' && 
					pathname[pathname.GetLength()-1] != '\\' &&
					attrib == FILE_ATTRIBUTE_DIRECTORY;

	UINT FileEntryLen = (UINT)(sizeof(FileEntry)-1 + pathname.GetLength() + slash_add);
	FileEntry& e = *((FileEntry*)_Malloc32AL(BYTE, FileEntryLen));
		
	e.CRC32 = 0;

	{	os::Timestamp tm(ftime);
		e.FileDate = tm.GetLocalDateTime().GetDosDate();
		e.FileTime = tm.GetLocalDateTime().GetDosTime();
	}

	e.Compression = 0;
	e.DiskNumber = 0;
	e.ExtraFieldLength = 0;
	e.FileAttributes = 0;
	e.FileAttributesOriginal = attrib;
	e.FileCommentLength = 0;
	memcpy(e.FileName,pathname.Begin(),pathname.GetLength());
	rt::String_Ref(e.FileName,pathname.GetLength()).Replace('\\','/');
	if(slash_add)e.FileName[pathname.GetLength()] = '/';
	e.FileNameLength = (WORD)pathname.GetLength() + slash_add;
	e.Flag = 0;
	e.OffsetToLocalFileHeader = 0;
	e.Signature = e.header_magic;
	e.Size = 0;
	e.SizeOriginal = 0;
	e.ZipVersion = 0x014;
	e.UnzipVersion = 0x000a;

	m_FileEntries.push_back(FileEntryPtr(&e));
	m_CentralDirectoryModified = true;
	m_ListSorted = false;

	return true;
}

void FileZip::ReindexAllEntries()
{
	if(!m_ListSorted)
	{
		std::sort(m_FileEntries.Begin(),m_FileEntries.End());
		m_ListSorted = true;
	}
}

FileZip::FileEntry* FileZip::_AddNonZeroFileEntry_Begin(const rt::String_Ref& pathname, UINT size, __time64_t ftime)
{
	ASSERT(_AddingNonZeroFileEntry == nullptr);
	if(pathname.GetLength() > 0xffff)return nullptr;
	if(m_FileEntries.GetSize() >= 0xffff)return nullptr;
	ASSERT(size); // add zero-sized file by AddDirectory and set attrib = FILE_ATTRIBUTE_ARCHIVE
	
	ASSERT(!m_IsReadOnly);

	// store
	UINT FileEntryLen = (UINT)(sizeof(FileEntry)-1 + pathname.GetLength());
	UINT offset;

	_CentralDirectoryStart_Old = m_CentralDirectoryStart;

	UINT LFlen = (UINT)(sizeof(LocalFileHeader)-1 + pathname.GetLength() + size); // + sizeof(DataDesc);
	{	
		// Looking for removed place
		for(UINT i=0;i<m_FileEntries.GetSize();i++)
			if(m_FileEntries[i].p->Signature==0 && m_FileEntries[i].p->Size >= LFlen)
			{	
				offset = m_FileEntries[i].p->OffsetToLocalFileHeader;
				m_FileEntries[i].p->Size -= LFlen;
				m_FileEntries[i].p->OffsetToLocalFileHeader += LFlen;
				_HoleFromEntry = m_FileEntries[i].p;
				_HoleTakenSize = LFlen;
				goto SAVE_ENTRY;
			}

		if(m_CentralDirectoryStart + LFlen > (UINT_MAX - sizeof(CentralDirectory) - 0xffff))return nullptr;
		offset = m_CentralDirectoryStart;
		m_CentralDirectoryStart += LFlen;
		_HoleFromEntry = nullptr;
	}

SAVE_ENTRY:

	FileEntry& e = *((FileEntry*)_Malloc32AL(BYTE, FileEntryLen));
	e.CRC32 = 0;
	e.Compression = 0;
	e.SizeOriginal = size;

	{	os::Timestamp tm(ftime);
		e.FileDate = tm.GetLocalDateTime().GetDosDate();
		e.FileTime = tm.GetLocalDateTime().GetDosTime();
	}

	e.DiskNumber = 0;
	e.ExtraFieldLength = 0;
	e.FileAttributes = 0;
	e.FileAttributesOriginal = FILE_ATTRIBUTE_ARCHIVE;
	e.FileCommentLength = 0;
	memcpy(e.FileName,pathname.Begin(),pathname.GetLength());
	rt::String_Ref(e.FileName,pathname.GetLength()).Replace('\\','/');
	e.FileNameLength = (WORD)pathname.GetLength();
	e.Flag = 0;
	e.OffsetToLocalFileHeader = offset;
	e.Signature = e.header_magic;
	e.Size = size;
	e.ZipVersion = 0x014;
	e.UnzipVersion = 0x000a;
	
	_AddingNonZeroFileEntry = &e;
	_ClaimedSize = size;
	UINT name_pos = e.OffsetToLocalFileHeader+sizeof(LocalFileHeader)-1;
	if( _pZipFile->Seek(name_pos) == name_pos &&
		_pZipFile->Write(pathname.Begin(),pathname.GetLength()) == pathname.GetLength()
	)
	{	return &e;
	}
	else
	{	_AddNonZeroFileEntry_End(false);
		return nullptr;
	}
}

bool FileZip::_AddNonZeroFileEntry_End(bool commit)
{
	ASSERT(_AddingNonZeroFileEntry);
	ASSERT(_ClaimedSize >= _AddingNonZeroFileEntry->Size);

	bool ret = true;

	if(commit)
	{
		FileEntry& e = *_AddingNonZeroFileEntry;
		LocalFileHeader LFH;
		LFH.Compression = e.Compression;
		LFH.CRC32 = e.CRC32;
		LFH.ExtraFieldLength = 0;
		LFH.FileDate = e.FileDate;
		LFH.FileNameLength = e.FileNameLength;
		LFH.FileTime = e.FileTime;
		LFH.Flag = e.Flag;
		LFH.Signature = LFH.header_magic;
		LFH.Size = e.Size;
		LFH.SizeOriginal = e.SizeOriginal;
		LFH.Version = e.UnzipVersion;

		if(	_pZipFile->Seek(_AddingNonZeroFileEntry->OffsetToLocalFileHeader) == _AddingNonZeroFileEntry->OffsetToLocalFileHeader &&
			_pZipFile->Write(&LFH,sizeof(LocalFileHeader)-1) == sizeof(LocalFileHeader)-1
		)
		{	m_FileEntries.push_back(FileEntryPtr(_AddingNonZeroFileEntry));
			m_CentralDirectoryModified = true;
			m_ListSorted = false;

			int saved = _ClaimedSize - _AddingNonZeroFileEntry->Size;
			if(saved)
			{
				if(_HoleFromEntry)
				{
					_HoleFromEntry->Size+=saved;
					_HoleFromEntry->OffsetToLocalFileHeader-=saved;
				}
				else
					m_CentralDirectoryStart -= saved;
			}

			_AddingNonZeroFileEntry = nullptr;
			return true;
		}

		ret = false;
	}

	// rollback
	_SafeFree32AL(_AddingNonZeroFileEntry);
	if(_HoleFromEntry)
	{
		_HoleFromEntry->Size+=_HoleTakenSize;
		_HoleFromEntry->OffsetToLocalFileHeader-=_HoleTakenSize;
	}
	else
		m_CentralDirectoryStart = _CentralDirectoryStart_Old;

	return ret;
}

void FileZip::compress_stream::Init(UINT base)
{
	Written = 0;
	BaseInFile = base;
	CRC = 0;
}

bool FileZip::compress_stream::Finalize(bool commit)
{
	pThis->_AddingNonZeroFileEntry->CRC32 = CRC;
	pThis->_AddingNonZeroFileEntry->Size = Written;
	return pThis->_AddNonZeroFileEntry_End(commit);
}

UINT FileZip::compress_store::Write(LPCVOID p, UINT size)
{
	if(Written + size <= pThis->_ClaimedSize)
	{
		pThis->_crc_checksum(p,size,&CRC);
		if(	pThis->_pZipFile->Seek(BaseInFile + Written) == BaseInFile + Written &&
			pThis->_pZipFile->Write(p,size) == size
		)
		{	Written += size;
			return size;
		}
	}
	return INFINITE;
}

FileZip::compress_zlib::compress_zlib()
{
	defstrm = nullptr;
}

void FileZip::compress_zlib::Clear()
{
	if(defstrm)
	{	deflateEnd(((z_stream*)defstrm));
		_SafeFree32AL(defstrm);
	}
}

bool FileZip::compress_zlib::Finalize(bool commit)
{
	if(commit)
	{
		((z_stream*)defstrm)->avail_in = 0;
		((z_stream*)defstrm)->next_in = Z_NULL;
		((z_stream*)defstrm)->avail_out = (uInt)(pThis->_StreamBuff.GetSize());
		((z_stream*)defstrm)->next_out = (Bytef*)pThis->_StreamBuff.Begin();

		for(;;)
		{	int err;
			if((err = deflate(((z_stream*)defstrm), Z_FINISH)) == Z_STREAM_END)break;
			if(err != Z_OK)
			{	compress_stream::Finalize(false);
				return false;
			}
		}

		int wsize = (int)(pThis->_StreamBuff.GetSize() - ((z_stream*)defstrm)->avail_out);

		if(wsize>0)
		{
			if(Written + wsize <= pThis->_ClaimedSize)
			{
				if(	pThis->_pZipFile->Seek(BaseInFile + Written) == BaseInFile + Written &&
					pThis->_pZipFile->Write(pThis->_StreamBuff,wsize) == wsize
				)
				{	Written += wsize;
					goto Z_FINISH_DONE;
				}
			}
			compress_stream::Finalize(false);
			return false;
		}
	}
Z_FINISH_DONE:
	return compress_stream::Finalize(commit);
}

UINT FileZip::compress_zlib::Write(LPCVOID p, UINT size)
{
	if(!Written)
	{
		Clear();
		VERIFY(pThis->_StreamBuff.SetSize(_StreamBlockSize));
		defstrm = (z_stream_ptr*)_Malloc32AL(BYTE, sizeof(z_stream));
		ASSERT(defstrm);

		((z_stream*)defstrm)->zalloc = Z_NULL;
		((z_stream*)defstrm)->zfree = Z_NULL;
		((z_stream*)defstrm)->opaque = Z_NULL;
		((z_stream*)defstrm)->avail_in = 0;
		((z_stream*)defstrm)->next_in = Z_NULL;
		((z_stream*)defstrm)->next_out = Z_NULL;
		((z_stream*)defstrm)->avail_out = 0;

		if(deflateInit2(((z_stream*)defstrm), Z_DEFAULT_COMPRESSION, Z_DEFLATED, -15, 8, Z_DEFAULT_STRATEGY)!= Z_OK)return 0;
	}

	pThis->_crc_checksum(p,size,&CRC);
	((z_stream*)defstrm)->avail_in = size;
	((z_stream*)defstrm)->next_in = (Bytef*)p;

	for(;;)
	{
		((z_stream*)defstrm)->avail_out = (uInt)(pThis->_StreamBuff.GetSize());
		((z_stream*)defstrm)->next_out = (Bytef*)pThis->_StreamBuff.Begin();

		deflate(((z_stream*)defstrm), Z_SYNC_FLUSH);

		if(((z_stream*)defstrm)->avail_in == 0 || ((z_stream*)defstrm)->avail_out == 0)
		{	
			int wsize = (int)(pThis->_StreamBuff.GetSize() - ((z_stream*)defstrm)->avail_out);

			if(Written + wsize <= pThis->_ClaimedSize)
			{
				if(	pThis->_pZipFile->Seek(BaseInFile + Written) == BaseInFile + Written &&
					pThis->_pZipFile->Write(pThis->_StreamBuff,wsize) == wsize
				)
				{	Written += wsize;
				}
			}
			else
			{	return INFINITE;	// switch to no compress !!
			}

			if(((z_stream*)defstrm)->avail_in == 0)
				return size;	// done
		}
		else return 0; // Error
	}

	ASSERT(0);
	return 0;
}


FileZip::decompress_zlib::decompress_zlib()
{
	infstrm = nullptr;
}

void FileZip::decompress_zlib::Clear()
{
	if(infstrm)
	{	inflateEnd(((z_stream*)infstrm));
		_SafeFree32AL(infstrm);
	}
}

void FileZip::decompress_zlib::Init(UINT total_out_size, UINT base, DWORD target_CRC, UINT compressed_size)
{
	decompress_stream::Init(total_out_size, base, target_CRC);
	CompressedSize = compressed_size;
	CompressedAte = 0;
}

UINT FileZip::decompress_zlib::Read(LPVOID p, UINT size)
{
	if(!CompressedAte)	// init
	{	Clear();
		VERIFY(pThis->_StreamBuff.SetSize(_StreamBlockSize));
		infstrm = (z_stream_ptr*)_Malloc32AL(BYTE, sizeof(z_stream));
		ASSERT(infstrm);
		
		((z_stream*)infstrm)->zalloc = Z_NULL;
		((z_stream*)infstrm)->zfree = Z_NULL;
		((z_stream*)infstrm)->opaque = Z_NULL;
		((z_stream*)infstrm)->avail_in = 0;
		((z_stream*)infstrm)->next_in = Z_NULL;
		((z_stream*)infstrm)->next_out = Z_NULL;
		((z_stream*)infstrm)->avail_out = 0;

		if(inflateInit2(((z_stream*)infstrm),-15) != Z_OK)return 0;
	}

	((z_stream*)infstrm)->next_out = (Bytef*)p;
	((z_stream*)infstrm)->avail_out = size;

	for(;;)
	{
		if(((z_stream*)infstrm)->avail_in == 0)
		{	// load compressed data
			if(CompressedAte >= CompressedSize)goto CHECK_CRC32;

			int load = rt::min(_StreamBlockSize,(DWORD)(CompressedSize - CompressedAte));
			((z_stream*)infstrm)->avail_in = load;

			if(	pThis->_pZipFile->Seek(BaseInFile + CompressedAte) == BaseInFile + CompressedAte &&
				pThis->_pZipFile->Read(pThis->_StreamBuff,load) == load)
			{	((z_stream*)infstrm)->next_in = (Bytef*)pThis->_StreamBuff.Begin();
			}
			else goto CHECK_CRC32;

			CompressedAte += load;
		}

		inflate(((z_stream*)infstrm), Z_SYNC_FLUSH);
		if(((z_stream*)infstrm)->avail_out == 0 || ((z_stream*)infstrm)->avail_in)
			break;
	}

CHECK_CRC32:
	UINT outed = size - ((z_stream*)infstrm)->avail_out;
	if(decompress_stream::CheckCRC(p,outed))
	{
		Outputed += outed;
		return outed;
	}
	else
		return 0;
}


FileZip::stream_writeonly* FileZip::AddFile(const rt::String_Ref& pathname, UINT size, __time64_t ftime)
{
	ASSERT(_AddingNonZeroFileEntry == nullptr);

	FileEntry* e = _AddNonZeroFileEntry_Begin(pathname,size,ftime);
	if(e)
	{
		e->Compression = m_CompressionMode;
		e->SizeOriginal = size;
		if(m_CompressionMode)
		{	
			switch(m_CompressionMode)
			{
			case 8:	// 8 - The file is Deflated (Z_DEFLATED)
				stream_write_zlib.Init(e->GetOffsetToLocalData());
				return &stream_write_zlib;
				break;
			default: ASSERT(0);
			}
		}
		else
		{	stream_write_store.Init(e->GetOffsetToLocalData());
			return &stream_write_store;
		}
	}

	return nullptr;
}


bool FileZip::AddFile(const rt::String_Ref& pathname, LPCVOID pData, UINT size, __time64_t ftime)
{
	if(size == 0)
	{
		return AddZeroSizedEntry(pathname, ftime, FILE_ATTRIBUTE_ARCHIVE);
	}

	ASSERT(_AddingNonZeroFileEntry == nullptr);
	UINT size_org = size;
	DWORD CRC32 = 0;
	_crc_checksum(pData,size,&CRC32);

	// compress
	rt::Buffer<BYTE>	compressed;
	if(m_CompressionMode)
	{	
		if(	compressed.SetSize(rt::max(1024U,(UINT)(size*1.2f))) &&
			(size = (UINT)compressed.GetSize()) &&
			rt::zlib_encode(pData,size_org,compressed,size) &&
			size < size_org
		)
		{	pData = compressed;
		}
		else
		{	size = size_org;
			compressed.SetSize();
		}
	}

	FileEntry* e = _AddNonZeroFileEntry_Begin(pathname,size,ftime);
	if(e)
	{
		UINT data_pos = e->GetOffsetToLocalData();
		if( _pZipFile->Seek(data_pos) == data_pos &&
			_pZipFile->Write(pData,size) == size
		)
		{	e->CRC32 = CRC32;
			e->SizeOriginal = size_org;
			e->Compression = (size == size_org)?0:m_CompressionMode;

			return _AddNonZeroFileEntry_End(true);
		}
		else
		{
			_AddNonZeroFileEntry_End(false);
		}
	}

	return false;
}

void FileZip::RemoveFile(UINT idx)
{
	ASSERT(!m_IsReadOnly);
	ASSERT(m_FileEntries[idx].p->Signature);
	m_FileEntries[idx].p->Signature = 0;
	m_FileEntries[idx].p->Size += (sizeof(LocalFileHeader)-1) + m_FileEntries[idx].p->FileNameLength;					
}

bool FileZip::IsFileExtractable(UINT idx) const
{
	FileEntry* e = m_FileEntries[idx].p;
	return e->Compression == 0 || e->Compression == 8;
}

bool FileZip::ExtractFile(UINT idx, LPVOID pData)
{
	FileEntry* e = m_FileEntries[idx].p;
	LocalFileHeader LFH;
	
	if(	_pZipFile->Seek(e->OffsetToLocalFileHeader) == e->OffsetToLocalFileHeader &&
		_pZipFile->Read(&LFH, offsetof(LocalFileHeader, FileName)) == offsetof(LocalFileHeader, FileName) &&
		LFH.Signature == LocalFileHeader::header_magic
	)
	{	// decompress
		DWORD begin = e->OffsetToLocalFileHeader+LFH.FileNameLength+LFH.ExtraFieldLength+sizeof(LocalFileHeader)-1;
		//DWORD end = begin + e->Size;

		if(LFH.Compression)
		{
			bool succ = false;
			LPCBYTE  p = nullptr;
			rt::Buffer<BYTE> compressed;
            
			if(	compressed.SetSize(e->Size) &&
				_pZipFile->Seek(begin) == begin &&
				_pZipFile->Read(compressed,(UINT)compressed.GetSize()) == compressed.GetSize()
			)
			{	p = compressed;
			}
			else return false; // no memory

			switch(LFH.Compression)
			{
			case 8:	// 8 - The file is Deflated (Z_DEFLATED)
				{	
					if(rt::zlib_decode(p,e->Size,pData,(UINT&)e->SizeOriginal))
						succ = true;
					break;
				}
			}

			if(!succ)return false;
		}
		else
		{	// store mode
			if(	e->Size == e->SizeOriginal &&
				_pZipFile->Seek(begin) == begin &&
				_pZipFile->Read(pData,e->Size) == e->Size
			){}
			else return false;
		}
	}

	// decrypt
	
	// CRC check
	{	DWORD sum = 0;
		_crc_checksum(pData,e->SizeOriginal,&sum);
		if(sum != e->CRC32)return false;
	}

	return true;
}

void FileZip::decompress_stream::Init(UINT total_size, UINT base, DWORD target_CRC)
{
	TotalOutput = total_size;
	Outputed = 0;
	BaseInFile = base;
	Target_CRC = target_CRC;
	CRC = 0;
}

bool FileZip::decompress_stream::CheckCRC(LPCVOID p, UINT sz)
{
	ASSERT(sz + Outputed <= TotalOutput);
	pThis->_crc_checksum(p,sz,&CRC);
	if(sz + Outputed == TotalOutput)
		return CRC == Target_CRC;

	return true;
}

FileZip::stream_readonly* FileZip::ExtractFile(UINT idx)
{
	FileEntry* e = m_FileEntries[idx].p;
	LocalFileHeader LFH;
	
	if(	_pZipFile->Seek(e->OffsetToLocalFileHeader) == e->OffsetToLocalFileHeader &&
		_pZipFile->Read(&LFH,sizeof(LocalFileHeader)-1) == sizeof(LocalFileHeader)-1 &&
		LFH.Signature == LocalFileHeader::header_magic
	)
	{	// decompress
		DWORD begin = e->OffsetToLocalFileHeader+LFH.FileNameLength+LFH.ExtraFieldLength+sizeof(LocalFileHeader)-1;
		//DWORD end = begin + e->Size;

		if(LFH.Compression)
		{
			switch(LFH.Compression)
			{
			case 8:	// 8 - The file is Deflated (Z_DEFLATED)
				{	
					stream_read_zlib.Init(e->SizeOriginal,begin,e->CRC32, e->Size);
					return &stream_read_zlib;
				}
			default: ASSERT(0);
			}
		}
		else
		{	stream_read_store.Init(e->SizeOriginal,begin,e->CRC32);
			return &stream_read_store;
		}
	}

	return nullptr;
}

UINT FileZip::decompress_store::Read(LPVOID p, UINT size)
{
	UINT read = 0;
	if( Outputed < TotalOutput &&
		pThis->_pZipFile->Seek(BaseInFile + Outputed) == BaseInFile + Outputed &&
		(read = (UINT)pThis->_pZipFile->Read(p,size))>0 &&
		CheckCRC(p,read)
	)
	{	Outputed += read;
		return read;
	}
	return 0;
}

UINT FileZip::GetFileLocalHeaderOffset(UINT idx) const
{
	return m_FileEntries[idx].p->OffsetToLocalFileHeader;
}

UINT FileZip::GetFileSize(UINT idx) const
{
	return m_FileEntries[idx].p->SizeOriginal;
}

UINT FileZip::GetLocalFileHeaderOffset(UINT idx) const
{
	return m_FileEntries[idx].p->OffsetToLocalFileHeader;
}

UINT FileZip::GetFileArchivedSize(UINT idx) const
{
	return m_FileEntries[idx].p->Size;
}

DWORD FileZip::GetFileAttribute(UINT idx) const
{
	return m_FileEntries[idx].p->FileAttributesOriginal;
}

rt::String_Ref	FileZip::GetFileName(UINT idx) const
{
	return rt::String_Ref(m_FileEntries[idx].p->FileName,m_FileEntries[idx].p->FileNameLength);
}

__time64_t FileZip::GetFileTime(UINT idx)
{
	os::Timestamp::Fields f;
	f.SetDosTime(m_FileEntries[idx].p->FileDate,m_FileEntries[idx].p->FileTime);
	return os::Timestamp(f);
}

bool FileZip::Save()
{
	if( m_CentralDirectoryModified && _pZipFile->Seek(m_CentralDirectoryStart) == m_CentralDirectoryStart )
	{
		UINT cdsize = 0;
		UINT entry_co = 0;
		for(UINT i=0; i<m_FileEntries.GetSize(); i++)
		{
			if(m_FileEntries[i].p->Signature)
			{
				entry_co++;
				cdsize += m_FileEntries[i].p->GetTotalSize();
				if(_pZipFile->Write(m_FileEntries[i].p,m_FileEntries[i].p->GetTotalSize())
							   != m_FileEntries[i].p->GetTotalSize()
				)return false;
			}
		}
		
		CentralDirectory cd;
		cd.Signature = cd.header_magic;
		cd.m_uDiskWithCD = 0;
		cd.m_uDiskEntriesNo = (WORD)entry_co;
		cd.m_uEntriesNumber = (WORD)entry_co;
		cd.m_uOffset = m_CentralDirectoryStart;
		cd.m_uSize = cdsize;
		cd.m_uThisDisk = 0;
		cd.m_ZipCommentLength = (UINT)m_ZipComment.GetLength();

		if(	_pZipFile->Write(&cd,sizeof(CentralDirectory)-1) != sizeof(CentralDirectory)-1 )return false;
		if(	m_ZipComment.GetLength() && 
			_pZipFile->Write(m_ZipComment,m_ZipComment.GetLength()) != m_ZipComment.GetLength()
		)return false;

		//ULONGLONG len = _pZipFile->Seek(0,rt::_File::Seek_Current);
		//if(!_pZipFile->SetLength(len))return false;

		m_CentralDirectoryModified = false;
		return true;
	}

	return false;
}

bool FileZip::AddEntryFrom(LPCSTR pathname_sys, LPCSTR pathname_zip)
{
	ASSERT(_AddingNonZeroFileEntry == nullptr);
	__time64_t tt;

	if(File::IsDirectory(pathname_sys))
	{
		VERIFY(os::File::GetPathTime(pathname_sys,NULL,NULL,&tt));
		return AddZeroSizedEntry(pathname_zip,tt,FILE_ATTRIBUTE_DIRECTORY);
	}

	os::File file;
	ULONGLONG fsize;
	if(!file.Open(pathname_sys))return false;
	if((fsize = file.GetLength()))	// zero sized file
	{
		if(fsize > 0xffffffff)return false;
		UINT fsz = (UINT)fsize;
		file.GetFileTime(NULL,NULL,&tt);
		return (_FileDataTemp.GetSize() > fsz || _FileDataTemp.SetSize(fsz)) &&
				file.Read(_FileDataTemp, fsz) == fsz &&
				AddFile(pathname_zip, _FileDataTemp, fsz, tt);
	}
	else
	{
		return AddZeroSizedEntry(pathname_zip,file.GetTime_LastModify(),FILE_ATTRIBUTE_ARCHIVE);
	}
}

bool FileZip::ExtractEntryTo(UINT fid, LPCSTR path_sys)
{
	ASSERT(fid < m_FileEntries.GetSize());
	if(!m_FileEntries[fid].p->Signature)return false;	// been deleted

	if(GetFileAttribute(fid)&FILE_ATTRIBUTE_DIRECTORY)
	{
		if(!File::CreateDirectories(path_sys))return false;
	}
	else
	{	UINT fsz;
		os::File file;
		if(!file.Open(path_sys, os::File::Normal_Write))return false;

		if((fsz = GetFileSize(fid)))
		{	
			if(	(_FileDataTemp.GetSize() > fsz || _FileDataTemp.SetSize(fsz)) &&
				ExtractFile(fid, _FileDataTemp) &&
				file.Write(_FileDataTemp, fsz) == fsz
			){}
			else return false;
		}

		file.Close();
	}

	/*
	FILETIME tt;
	GetFileTime(fid,&tt);
	os::File::SetPathTime(path_sys,NULL,NULL,&tt);
	*/
	return true;
}

/*
bool FileZip::AddAllEntriesFrom(LPCSTR path_sys, LPCSTR path_zip, bool include_subfolders)
{
	ASSERT(_AddingNonZeroFileEntry == nullptr);
	UINT syslen = (UINT)_tcslen(path_sys);

	w32::CFileList	list;

	if(syslen)
	{	ASSERT(path_sys[syslen-1]!='/');
		ASSERT(path_sys[syslen-1]!='\\');

		if(!(os::File::GetAttributes(path_sys)&FILE_ATTRIBUTE_DIRECTORY))return false;

	
		if(FAILED(list.ParsePathName(	rt::String_Ref(path_sys,syslen) + _T("\\*.*"),
										include_subfolders?w32::CFileList::PATHNAME_FLAG_RECURSIVE:0,
										FILE_ATTRIBUTE_OFFLINE, 0))
		)return false;
	}
	else
	{	syslen = 1;
		if(FAILED(list.ParsePathName(	_T(".\\*.*"),
										include_subfolders?w32::CFileList::PATHNAME_FLAG_RECURSIVE:0,
										FILE_ATTRIBUTE_OFFLINE, 0))
		)return false;
	}

	rt::String_Ref prefix(path_zip);
	if(prefix.GetLength())
	{
		if(prefix[prefix.GetLength()-1] == '/' || prefix[prefix.GetLength()-1] == '\\')
			prefix = prefix.TrimRight(1);
	}
	else
	{	syslen++;
	}
		
	
	for(UINT i=0;i<list.GetFileCount();i++)
	{
		LPCSTR fn = list.GetFilename(i);
		if(!AddEntryFrom(fn, prefix + (LPCSTR)ATL::CT2A(fn+syslen)))
			return false;
	}

	return true;
}
*/

bool FileZip::ExtractAllEntriesTo(LPCSTR path_zip, LPCSTR path_sys, bool include_subfolders)		// extract all files in directory path_zip in zip to path_sys
{
	UINT ziplen = path_zip?(UINT)strlen(path_zip):0;

	rt::String prefix(path_sys);
	if(	prefix.GetLength() && 
		prefix[prefix.GetLength()-1] != '/' && prefix[prefix.GetLength()-1] != '\\'
	)
	{	prefix += '\\';	}

	rt::String outname;
	if(ziplen)
	{
		ASSERT(path_zip[ziplen-1]!='/');
		ASSERT(path_zip[ziplen-1]!='\\');

		rt::String zip_prefix;
		zip_prefix = rt::String_Ref(path_zip,ziplen) + '/';
	
		for(UINT i=0;i<m_FileEntries.GetSize();i++)
		{
			FileEntry& e = *m_FileEntries[i].p;
			if(	e.Signature && 
				e.FileNameLength > zip_prefix.GetLength() && 
				memcmp(e.FileName,zip_prefix,zip_prefix.GetLength()) == 0
			)
			{
				if(!include_subfolders)
				{
					for(UINT i=(UINT)zip_prefix.GetLength();i<e.FileNameLength;i++)
						if(e.FileName[i] == '/' || e.FileName[i] == '\\')
							goto SKIP_IT;
				}
				outname = rt::String_Ref(e.FileName + zip_prefix.GetLength(), e.FileName + e.FileNameLength);
				if(!ExtractEntryTo(i, prefix + outname))
					return false;
			}
SKIP_IT:
			continue;
		}
	}
	else
	{
		for(UINT i=0;i<m_FileEntries.GetSize();i++)
		{
			FileEntry& e = *m_FileEntries[i].p;
			if(	e.Signature )
			{
				if(!include_subfolders)
				{
					for(UINT i=0;i<e.FileNameLength;i++)
						if(e.FileName[i] == '/' || e.FileName[i] == '\\')
							goto SKIP_IT2;
				}
				outname = rt::String_Ref(e.FileName,e.FileNameLength);
				if(!ExtractEntryTo(i,prefix + outname))
					return false;
			}
SKIP_IT2:
			continue;
		}
	}

	return true;
}

} // namespace os



#if defined(PLATFORM_WIN)

void os::EnableCrashDump(LPCSTR dump_filename, bool full_memory, bool zip_after_dump)
{
	struct _call
	{
		static void _func(LPCSTR fn)
		{
			os::FileRead<BYTE>	file(fn);
			os::FileZip	zip;
			zip.SetCompressionMode();
			if(	file.GetSize() &&
				zip.Open(rt::String_Ref(fn) + ".zip", os::File::Normal_Write) &&
				zip.AddFile(fn, file, (UINT)file.GetSize()) &&
				zip.Save()
			)
			{	zip.Close();
				File::Remove(fn);
			}					
		}
	};

	if(zip_after_dump)os::_details::_SetPostCrashDumpHook(_call::_func);
	os::EnableCrashDump(dump_filename, full_memory);
}

#endif


namespace os
{


FileGzip::FileGzip()
{
	_pZipFile = nullptr;
}


bool FileGzip::Open(LPCSTR fn)
{
	_BaseFile.Close();
	return	_BaseFile.Open(fn) && Open(&_BaseFile);
}

bool FileGzip::Open(rt::_File* pFile)
{
	_pZipFile = pFile;
	SIZE_T load = rt::min((SIZE_T)sizeof(gz_header),_pZipFile->GetLength());
	gz_header	hdr;
	gz_tail		tail;

	if(	_pZipFile->Read(&hdr,load) == load &&
		hdr.magic == 0x8b1f &&
		hdr.compression == 8 &&
		_pZipFile->Seek(-((int)sizeof(gz_tail)),rt::_File::Seek_End) &&
		_pZipFile->Read(&tail,sizeof(gz_tail)) == sizeof(gz_tail)
	)
	{	LPCSTR p = (LPCSTR)&hdr;
		m_ArchiveOffset = 10;
		
		if(GZF_FEXTRA&hdr.flag)m_ArchiveOffset += hdr._extra_length;
		if(GZF_FNAME&hdr.flag)
		{
			int end = m_ArchiveOffset;
			while(end < sizeof(gz_header) && p[end])
				end++;
			if(end == sizeof(gz_header))
			{	Close();
				return false;
			}
			m_Filename = rt::String_Ref(p+m_ArchiveOffset, p+end);
			m_ArchiveOffset = end+1;
		}
		if(GZF_FCOMMENT&hdr.flag)
		{
			while(m_ArchiveOffset < sizeof(gz_header) && p[m_ArchiveOffset])
				m_ArchiveOffset++;
			if(m_ArchiveOffset == sizeof(gz_header))
			{	Close();
				return false;
			}
			m_ArchiveOffset++;
		}
		if(GZF_FHCRC&hdr.flag)
		{
			m_ArchiveOffset+=2;
		}

		m_ArchiveSize = (UINT)(_pZipFile->GetLength() - sizeof(gz_tail) - m_ArchiveOffset);
		m_OriginalSize = tail.length;

		return true;
	}

	return false;
}

void FileGzip::Close()
{
	_BaseFile.Close();
	_pZipFile = nullptr;
}

UINT FileGzip::GetFileSize() const 
{
	return m_OriginalSize;
}

rt::String_Ref	FileGzip::GetFileName() const 
{
	return m_Filename;
}

bool FileGzip::ExtractFile(LPVOID pData)	// pData pointing memory with size = GetFileSize
{
	UINT fsize = m_OriginalSize;
	rt::Buffer<BYTE>	buf;
	return	buf.SetSize(m_ArchiveSize) &&
			_pZipFile->Seek(m_ArchiveOffset) == m_ArchiveOffset &&
			_pZipFile->Read(buf,m_ArchiveSize) == m_ArchiveSize &&
			rt::zlib_decode(buf,m_ArchiveSize,pData,fsize) &&
			m_OriginalSize == fsize;
}

UINT FileGzip::GetFileArchivedSize() const
{
	return m_ArchiveSize;
}

} // namespace os


namespace os
{

struct _7zipState
{
	CFileInStream archiveStream;
	CLookToRead lookStream;
	CSzArEx db;
	SRes res;
	ISzAlloc allocImp;
	ISzAlloc allocTempImp;
};

#define _State	(*(_7zipState*)_7zState)

File7z::File7z()
{
	static bool _first_init = true;
	if(_first_init)
	{
		static_assert(sizeof(_7zipState) == sizeof(_7zState), "size of _7zipState dosen't match");
		CrcGenerateTable();
		_first_init = false;
	}

	_IsOpen = false;
	_FolderDecodedIndex = -1;

	_State.allocImp.Alloc = SzAlloc;
	_State.allocImp.Free = SzFree;
	
	_State.allocTempImp.Alloc = SzAllocTemp;
	_State.allocTempImp.Free = SzFreeTemp;

	FileInStream_CreateVTable(&_State.archiveStream);
	LookToRead_CreateVTable(&_State.lookStream, False);
}

bool File7z::Open(LPCSTR fn)
{
	ASSERT(!_IsOpen);

	if(SZ_OK == InFile_Open(&_State.archiveStream.file, fn))
	{
		_State.lookStream.realStream = &_State.archiveStream.s;
		LookToRead_Init(&_State.lookStream);

		SzArEx_Init(&_State.db);
		if(SZ_OK == SzArEx_Open(&_State.db, &_State.lookStream.s, &_State.allocImp, &_State.allocTempImp))
		{
			_IsOpen = true;
			return true;
		}
		else
		{
			File_Close(&_State.archiveStream.file);
		}
	}

	return false;
}

void File7z::Close()
{
	SzArEx_Free(&_State.db, &_State.allocImp);
	File_Close(&_State.archiveStream.file);
	_FolderDecodedIndex = -1;
	_FolderDecoded.SetSize();
}

int	File7z::FindFile(const rt::String_Ref& pathname)	// -1 if not found, returned index will be invalidate when File List is changed													// by AddFile and RemoveFile
{
	os::__UTF16 s(pathname);
	for(UINT i=0; i<_State.db.db.NumFiles; i++)
	{
		rt::Buffer_Ref<os::U16CHAR> name = _GetFilename(i);
		if(	s.GetLength() == name.GetSize() &&
			memcmp(s.Begin(), name.Begin(), s.GetLength()*2) == 0
		)
		return i;
	}	

	return -1;
}

rt::Buffer_Ref<os::U16CHAR> File7z::_GetFilename(int idx) const
{
	ASSERT(_IsOpen);

	return	rt::Buffer_Ref<os::U16CHAR>(
				(os::LPCU16CHAR)(_State.db.FileNames.data + (_State.db.FileNameOffsets[idx] * 2)),
				_State.db.FileNameOffsets[idx + 1] - _State.db.FileNameOffsets[idx]
			);
}

int	File7z::FindFileRecursive(LPCSTR filename, int start_from_idx)			// by filename, without path
{
	os::__UTF16 s(filename);
	for(UINT i=start_from_idx; i<_State.db.db.NumFiles; i++)
	{
		rt::Buffer_Ref<os::U16CHAR> name = _GetFilename(i);
		if(	(	s.GetLength() == name.GetSize() ||
				(s.GetLength() == name.GetSize() && name[name.GetSize() - s.GetLength() - 1] == (os::U16CHAR)'/')
			)
			&& memcmp(s.Begin(), name.Begin() + name.GetSize() - s.GetLength(), s.GetLength()*2) == 0 
		)return i;
	}

	return -1;
}

SIZE_T File7z::GetFileCount() const
{
	ASSERT(_IsOpen);

	return _State.db.db.NumFiles;
}

rt::String_Ref File7z::GetFilename(UINT idx) const
{
	rt::Buffer_Ref<os::U16CHAR> b = _GetFilename(idx);
	((File7z*)this)->_utf8Name.Convert(b.Begin(), (int)b.GetSize());
	return _utf8Name;
}

DWORD File7z::GetFileAttribute(UINT idx) const
{
	ASSERT(_IsOpen);
	ASSERT(idx < GetFileCount());

	if(_State.db.db.Files[idx].AttribDefined)
		return _State.db.db.Files[idx].Attrib;
	else
		return 0;
}

bool File7z::IsDirectory(UINT idx) const
{
	ASSERT(_IsOpen);
	ASSERT(idx < (SIZE_T)GetFileCount());

	return _State.db.db.Files[idx].IsDir;
}

ULONGLONG File7z::GetFileSize(UINT idx) const
{
	ASSERT(_IsOpen);
	ASSERT(idx < GetFileCount());

	return _State.db.db.Files[idx].Size;
}

UINT File7z::GetFileArchivedSize(UINT idx) const
{
	return 0;
}

bool File7z::IsFileExtractable(UINT idx) const
{
	return !IsDirectory(idx);
}

__time64_t File7z::GetFileTime(UINT idx) const
{
	if(_State.db.db.Files[idx].MTimeDefined)
		return ((ULONGLONG&)_State.db.db.Files[idx].MTime)/10000000 - 11644473600LL;
	else
		return 0;
}

bool File7z::ExtractFile(UINT idx, LPVOID pData)	// pData pointing memory with size = GetFileSize
{
	ASSERT(_IsOpen);
	ASSERT(idx < (UINT)GetFileCount());

	UInt32 folderIndex = _State.db.FileIndexToFolderIndexMap[idx];
	CSzFolder *folder = _State.db.db.Folders + folderIndex;

    CSzFileItem *fileItem = _State.db.db.Files + idx;
    LONGLONG offset = 0;
    for(UINT i =  _State.db.FolderStartFileIndex[folderIndex]; i < idx; i++)
		offset += _State.db.db.Files[i].Size;
	LONGLONG size = _State.db.db.Files[idx].Size;

	if(size != GetFileSize(idx))return false; // file corrupted

	ULONGLONG unpackSize = offset + size;

	if(	folderIndex == _FolderDecodedIndex &&
		unpackSize <= _FolderDecoded.GetSize()
	)
	{	memcpy(pData, &_FolderDecoded[offset], size);
		return true;
	}

	UInt64 startOffset = SzArEx_GetFolderStreamPos(&_State.db, folderIndex, 0);
	
	if(offset == 0)
	{	// direct extract to pData
		Byte *outBuffer = (Byte *)pData;
		SzFolder_Decode(folder,
			 _State.db.db.PackSizes + _State.db.FolderStartPackStreamIndex[folderIndex],
			  &_State.lookStream.s, startOffset,
			  outBuffer, unpackSize, &_State.allocTempImp
		);
		if(fileItem->CrcDefined && CrcCalc(pData, size) != fileItem->Crc)return false;
	}
	else
	{	
		_FolderDecodedIndex = folderIndex;
		_FolderDecoded.SetSize(unpackSize);

		Byte *outBuffer = (Byte *)_FolderDecoded.Begin();
		SzFolder_Decode(folder,
			 _State.db.db.PackSizes + _State.db.FolderStartPackStreamIndex[folderIndex],
			  &_State.lookStream.s, startOffset,
			  outBuffer, unpackSize, &_State.allocTempImp
		);

		if(fileItem->CrcDefined && CrcCalc(&_FolderDecoded[offset], size) != fileItem->Crc)return false;
		memcpy(pData, &_FolderDecoded[offset], size);
	}

	return true;
}


} // namespace os
