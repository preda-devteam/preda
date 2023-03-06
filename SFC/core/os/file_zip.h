#pragma once
/**
 * @file file_zip.h
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
/** \defgroup os os 
 * @ingroup SFC
 *  @{
 */
#include "file_dir.h"

#ifndef PLATFORM_WIN
#define FILE_ATTRIBUTE_DIRECTORY	0x10
#define FILE_ATTRIBUTE_ARCHIVE		0x20
#endif

namespace os
{
/** \defgroup file_zip file_zip
 * @ingroup os
 *  @{
 */
/**
 * @brief Zip File
 * 
 */
class FileZip
{
	struct z_stream_ptr;
	rt::Buffer<BYTE>	_FileDataTemp;
public:
#pragma pack(push, 1)
	struct LocalFileHeader
	{
		static const int header_magic = 0x04034b50;
		enum	_tagFlag
		{	LFH_DATA_DESCRIPTOR_EXISTS = 0x0004,	///< DataDesc
		};

		DWORD	Signature;		
        WORD	Version;
		WORD	Flag;
        WORD	Compression;
        WORD	FileTime;
        WORD	FileDate;
        DWORD	CRC32;
		DWORD	Size;				///<	after compression, sizeof [file data 1]
		DWORD	SizeOriginal;
		WORD	FileNameLength;		///< sizeof(FileName)
		WORD	ExtraFieldLength;
		CHAR	FileName[1];		///<	FileNameLength
		//CHAR	ExtraField[1];		//	after FileName
	};

	struct	DataDesc
	{	DWORD	CRC32;
		DWORD	Size;				///<	after compression, sizeof [file data 1]
		DWORD	SizeOriginal;		
	};

	struct	FileEntry
	{	
		static const int header_magic = 0x02014b50;
		DWORD	Signature;				// 
		WORD	ZipVersion;				///< version made by 
		WORD	UnzipVersion;			///< version needed to extract
		WORD	Flag;
		WORD	Compression;
        WORD	FileTime;
        WORD	FileDate;
        DWORD	CRC32;
		DWORD	Size;				///<	after compression, sizeof [file data 1]
		DWORD	SizeOriginal;
		WORD	FileNameLength;		///< sizeof(FileName)
		WORD	ExtraFieldLength;
		WORD	FileCommentLength;
		WORD	DiskNumber;
		WORD	FileAttributes;
		DWORD	FileAttributesOriginal;
		DWORD	OffsetToLocalFileHeader;
        CHAR	FileName[1];
		//CHAR	ExtraField[1];
		//CHAR	FileComment[1];

		UINT	GetTotalSize() const { return sizeof(FileEntry)-1+FileNameLength+ExtraFieldLength+FileCommentLength; }
		UINT	GetOffsetToLocalData() const { return OffsetToLocalFileHeader + sizeof(LocalFileHeader)-1 + FileNameLength; }
	};

	struct	CentralDirectory
	{
		static const int header_magic = 0x06054b50;
		DWORD	Signature;
		WORD	m_uThisDisk;	
		WORD	m_uDiskWithCD;		
		WORD	m_uDiskEntriesNo;	
		WORD	m_uEntriesNumber;
		DWORD	m_uSize;			///< size of the central directory
		DWORD	m_uOffset;			///< offset of start of central directory with respect to the starting disk number
		WORD	m_ZipCommentLength;
		CHAR	m_ZipComment[1];
	};

#pragma pack(pop)

protected:
	os::File					_BaseFile;
	rt::Buffer<BYTE>			_FileEntryPool;

protected:
	rt::_File*					_pZipFile;
	rt::Buffer<CHAR>			m_Password;
	UINT						m_CompressionMode;

	bool						m_ListSorted;
	bool						m_IsReadOnly;
	rt::String					m_ZipComment;
	UINT						m_CentralDirectoryStart;
	bool						m_CentralDirectoryModified;

	struct FileEntryPtr: public rt::String_Ref
	{
		TYPETRAITS_DECLARE_POD;

		FileEntry*	p;
		FileEntryPtr(){}
		FileEntryPtr(FileEntry* x):rt::String_Ref(x->FileName,x->FileNameLength){ p = x; }
		operator FileEntry*() { return p; }
	};
	rt::BufferEx<FileEntryPtr>	m_FileEntries;
	void						_FreeFileEntry(FileEntryPtr& p);

private:
	FileEntry*					_AddingNonZeroFileEntry;
	FileEntry*					_HoleFromEntry;
	UINT						_HoleTakenSize;
	UINT						_CentralDirectoryStart_Old;
	UINT						_ClaimedSize;
	FileEntry*					_AddNonZeroFileEntry_Begin(const rt::String_Ref& pathname, UINT size, __time64_t ftime);
	/**
	 * @brief Following member MUST be updated before call _AddNonZeroFileEntry_End(true);
	 * 
	 * e.CRC32 = 0;
	 * 
	 * e.Compression = 0;
	 * 
	 * e.Size and e.SizeOriginal can be only updated to that smaller than claimed in _AddNonZeroFileEntry_Begin call
	 * @param commit 
	 * @return true 
	 * @return false 
	 */
	bool						_AddNonZeroFileEntry_End(bool commit);
	void						_crc_checksum(LPCVOID pSrc, UINT SrcLen, LPDWORD crc32);
public:
	//struct plugin
	//{	virtual bool Process(LPCVOID pSrc, UINT SrcLen, LPVOID pDst, UINT& DstLen) = 0;	};

	struct stream_readonly
	{	virtual UINT Read(LPVOID p, UINT size) = 0; ///< return number of byte read 
	};
	struct stream_writeonly
	{	virtual UINT Write(LPCVOID p, UINT size) = 0; ///< return number of byte written (INFINITE for compression failure, call for AddFile again in store mode  
		virtual bool Finalize(bool commit) = 0; ///< call to stop writing 
	};

protected:
	rt::Buffer<BYTE>	_StreamBuff;

	struct decompress_stream:public stream_readonly
	{
		FileZip* pThis;
		UINT	TotalOutput;
		UINT	Outputed;
		UINT	BaseInFile;
		DWORD	CRC;
		DWORD	Target_CRC;
		void	Init(UINT total_out_size, UINT base, DWORD target_CRC);
	protected:
		bool	CheckCRC(LPCVOID p, UINT sz);
	};
	struct decompress_store:public decompress_stream
	{	virtual UINT Read(LPVOID p, UINT size);
	};
	decompress_store	stream_read_store;
	struct decompress_zlib:public decompress_stream
	{	
		z_stream_ptr*	infstrm;
		UINT		_AlignOffset;
		UINT		CompressedSize;
		UINT		CompressedAte;

		decompress_zlib();
		~decompress_zlib(){ Clear(); }
		void	Init(UINT total_out_size, UINT base, DWORD target_CRC, UINT compressed_size);
		void	Clear();
		virtual UINT Read(LPVOID p, UINT size);
	private: void	Init(UINT total_out_size, UINT base, DWORD target_CRC);
	};
	decompress_zlib		stream_read_zlib;
	struct compress_stream:public stream_writeonly
	{	FileZip*	pThis;
		UINT		Written;
		UINT		BaseInFile;
		DWORD		CRC;
		void		Init(UINT base);
	protected:
		virtual		bool Finalize(bool commit);
	};
	struct compress_store:public compress_stream
	{	virtual		UINT Write(LPCVOID p, UINT size);
	};
	compress_store	stream_write_store;
	struct compress_zlib:public compress_stream
	{	
		z_stream_ptr*	defstrm;
		void			Clear();
		virtual			bool Finalize(bool commit);
		virtual			UINT Write(LPCVOID p, UINT size);
		compress_zlib();
		~compress_zlib(){ Clear(); }
	};
	compress_zlib	stream_write_zlib;

public:
	enum _tagCompressionMode
	{	ZIP_STORE = 0,
		ZIP_DEFLATED = 8
	};
	void	SetCompressionMode(UINT mode = ZIP_DEFLATED){ m_CompressionMode = mode; }

public:
	FileZip();
	~FileZip(){ Close(); }
/** @name Basic Operation
*/
///@{
	bool	IsOpen() const { return _pZipFile!=nullptr; }
	bool	Open(LPCSTR fn, LPCSTR openflag = File::Normal_Read, bool load_indexed = true);
	bool	Open(rt::_File* pFile, LPCSTR mode, bool load_indexed = true);
	void	Close();	///< save and close
	bool	Save();		///< just save, no squeeze
	bool	Squeeze();	///< squeeze space after some deletion
	File*	GetBaseFile(){ return _BaseFile.IsOpen()?&_BaseFile:nullptr; }
///@}
/** @name FindFile
*/
///@{
	int		FindFile(const rt::String_Ref& pathname);	///< -1 if not found, returned index will be invalidate when File List is changed
														///< by AddFile and RemoveFile
	int		FindFile(LPCSTR pathname){ return FindFile(rt::String_Ref(pathname)); }
	int		FindFileRecursive(LPCSTR filename, int start_from_idx = 0);			///< by filename, without path
///@}
/** @name AddZeroSizedEntry
*/
///@{
	bool	AddZeroSizedEntry(const rt::String_Ref& pathname, __time64_t ftime, DWORD attrib = FILE_ATTRIBUTE_DIRECTORY); ///< add a zero-sized file by attrib = FILE_ATTRIBUTE_ARCHIVE
	bool	AddZeroSizedEntry(LPCSTR pathname, __time64_t ftime, DWORD attrib = FILE_ATTRIBUTE_DIRECTORY){ return AddZeroSizedEntry(rt::String_Ref(pathname),ftime, attrib); }
	bool	AddZeroSizedEntry(const rt::String_Ref& pathname, DWORD attrib = FILE_ATTRIBUTE_DIRECTORY){ return AddZeroSizedEntry(rt::String_Ref(pathname), os::Timestamp::Get(), attrib); }
	bool	AddZeroSizedEntry(LPCSTR pathname, DWORD attrib = FILE_ATTRIBUTE_DIRECTORY){ return AddZeroSizedEntry(rt::String_Ref(pathname), attrib); }
///@}
/** @name AddFile
*/
///@{
	stream_writeonly* AddFile(const rt::String_Ref& pathname, UINT size, __time64_t ftime);
	stream_writeonly* AddFile(const rt::String_Ref& pathname, UINT size){ return AddFile(rt::String_Ref(pathname),size, os::Timestamp::Get()); }
	stream_writeonly* AddFile(LPCSTR pathname, UINT size, __time64_t ftime){ return AddFile(rt::String_Ref(pathname),size,ftime); }
	stream_writeonly* AddFile(LPCSTR pathname, UINT size){ return AddFile(rt::String_Ref(pathname),size); }

	bool	AddFile(const rt::String_Ref& pathname, LPCVOID pData, UINT size, __time64_t ftime);
	bool	AddFile(const rt::String_Ref& pathname, LPCVOID pData, UINT size){ return AddFile(rt::String_Ref(pathname), pData, size, os::Timestamp::Get()); }
	bool	AddFile(LPCSTR pathname, LPCVOID pData, UINT size, __time64_t ftime){ return AddFile(rt::String_Ref(pathname),pData,size,ftime); }
	bool	AddFile(LPCSTR pathname, LPCVOID pData, UINT size){ return AddFile(rt::String_Ref(pathname),pData,size); }
///@}	
	bool				ExtractFile(UINT idx, LPVOID pData);	///< pData pointing memory with size = GetFileSize
	stream_readonly*	ExtractFile(UINT idx);			///< returned object will be unavailable after next ExtractFile call
	DWORD				GetFileAttribute(UINT idx) const;
	UINT				GetFileSize(UINT idx) const;
	UINT				GetLocalFileHeaderOffset(UINT idx) const;
	UINT				GetFileArchivedSize(UINT idx) const;
	UINT				GetFileLocalHeaderOffset(UINT idx) const;
	bool				IsFileExtractable(UINT idx) const;
	__time64_t			GetFileTime(UINT idx);
	rt::String_Ref		GetFileName(UINT idx) const;
	void				RemoveFile(UINT idx);	///< will not invalidate index returned by FindFile, NOT tested yet
	UINT				GetEntryCount() const { return (UINT)m_FileEntries.GetSize(); }
	 
	
/** @name Entries
 * handle both files, zero-sized files and directories
*/ 
///@{
	void	ReindexAllEntries();	///< call after adding something
	bool	AddEntryFrom(LPCSTR pathname_sys, LPCSTR pathname_zip);
	bool	ExtractEntryTo(UINT idx, LPCSTR to_pathname_sys);
	bool	AddAllEntriesFrom(LPCSTR path_sys, LPCSTR path_zip, bool include_subfolders);			///< add all files in path_sys, to directory path_zip in zip
	bool	ExtractAllEntriesTo(LPCSTR path_zip, LPCSTR path_sys, bool include_subfolders);		///< extract all files in directory path_zip in zip to path_sys

	__time64_t	GetZipFileTime() const { ASSERT(_BaseFile.IsOpen()); return _BaseFile.GetTime_LastModify(); }
///@}	
};


#if defined(PLATFORM_WIN)
extern void EnableCrashDump(LPCSTR dump_filename, bool full_memory, bool zip_after_dump);
#endif

/**
 * @brief assumeing gzip with single file
 * 
 */
class FileGzip	
{
protected:
	os::File		_BaseFile;
	rt::_File*		_pZipFile;
	enum
	{	GZF_FTEXT	=	0x01,
		GZF_FHCRC	=	0x02,
		GZF_FEXTRA	=	0x04,
		GZF_FNAME	=	0x08,
		GZF_FCOMMENT=	0x10,
	};

#pragma pack(push, 1)
	struct gz_header
	{
		WORD	magic;				///< 0x8b1f
		BYTE	compression;		///< 0x8
		BYTE	flag;
		DWORD	mtime;
		BYTE	extra_flag;
		BYTE	platform;

		WORD	_extra_length;
		BYTE	_extra_data[500];
	};
	struct gz_tail
	{	DWORD	crc32;
		UINT	length;
	};
#pragma pack(pop)

	rt::String	m_Filename;
	UINT		m_ArchiveOffset;
	UINT		m_ArchiveSize;
	UINT		m_OriginalSize;


public:
	FileGzip();
	bool			IsOpen() const { return _pZipFile!=nullptr; }
	bool			Open(LPCSTR fn);
	bool			Open(rt::_File* pFile);
	void			Close();
	UINT			GetFileSize() const;
	rt::String_Ref	GetFileName() const;
	bool			ExtractFile(LPVOID pData);	///< pData pointing memory with size = GetFileSize
	UINT			GetFileArchivedSize() const;
};

class File7z
{
	rt::Buffer_Ref<os::U16CHAR>	_GetFilename(int idx) const;

#if defined(PLATFORM_WIN)
	#ifdef PLATFORM_64BIT
        BYTE				_7zState[16632];
	#else
        BYTE				_7zState[16528];
	#endif
#elif defined(PLATFORM_MAC) || defined(PLATFORM_IOS)
	#ifdef PLATFORM_64BIT
        BYTE				_7zState[16632];
	#else
        BYTE				_7zState[16528];
	#endif
#else
    #ifdef PLATFORM_64BIT
        BYTE				_7zState[16632];
    #else
        BYTE				_7zState[16528];
    #endif
#endif

	bool				_IsOpen;
	os::__UTF8			_utf8Name;

	rt::Buffer<BYTE>	_FolderDecoded;
	int					_FolderDecodedIndex;

public:
	File7z();
	~File7z(){ Close(); }
	void	Close();
	bool	Open(LPCSTR fn);

	int		FindFile(const rt::String_Ref& pathname);	///< -1 if not found, returned index will be invalidate when File List is changed													// by AddFile and RemoveFile
	int		FindFile(LPCSTR pathname){ return FindFile(rt::String_Ref(pathname)); }
	int		FindFileRecursive(LPCSTR filename, int start_from_idx = 0);			///< by filename, without path

	SIZE_T			GetFileCount() const;
	rt::String_Ref	GetFilename(UINT idx) const;
	bool			IsDirectory(UINT idx) const;
	DWORD			GetFileAttribute(UINT idx) const;
	ULONGLONG		GetFileSize(UINT idx) const;
	UINT			GetFileArchivedSize(UINT idx) const;
	bool			IsFileExtractable(UINT idx) const;
	__time64_t		GetFileTime(UINT idx) const;

	bool			ExtractFile(UINT idx, LPVOID pData);	///< pData pointing memory with size = GetFileSize

};
/** @}*/

} // namespace os
/** @}*/