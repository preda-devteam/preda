#if defined(PLATFORM_64BIT) && (defined(PLATFORM_MAC) || defined(PLATFORM_IOS))
#define _DARWIN_USE_64_BIT_INODE 1
#endif

#include "file_dir.h"
#include <sys/types.h>
#include <sys/stat.h>


#if defined(PLATFORM_WIN)
#include <io.h> 
#include <Psapi.h>
#include <sys/utime.h>
#include <tlhelp32.h>
#include <fcntl.h>

#else

#include <unistd.h>
#include <dirent.h>
#include <signal.h>
#include <sys/file.h>
namespace os
{
struct _stat:public stat{};
#if defined(PLATFORM_IOS) // ios deprecated stat64
struct _stat64:public stat{};
#else
struct _stat64:public stat64{};
#endif
}

#define _S_IFDIR S_IFDIR

//Headers for Mac/iOS
#if defined(PLATFORM_MAC) || defined(PLATFORM_IOS)
#include <sys/param.h>
#include <sys/mount.h>
#include <sys/mman.h>
#include <sys/sysctl.h>
#endif

//Headers for Andriod
#if defined(PLATFORM_ANDROID) || defined(PLATFORM_LINUX)
#include <sys/time.h>
#include <sys/statfs.h>
#include <sys/mman.h>
#include <sys/epoll.h>
#include <fcntl.h>
#endif

#if defined(PLATFORM_IOS)
int _objc_get_app_sandbox_path(char * path_out, int path_len);
#endif

#endif

const LPCSTR os::File::Normal_Read = "rb";
const LPCSTR os::File::Normal_Write = "wb+";
const LPCSTR os::File::Normal_ReadWrite = "rb+";
const LPCSTR os::File::Normal_Append = "ab+";


//////////////////////////////////////////////
// MemoryFile
os::MemoryFileRef::MemoryFileRef()
{
	_pData = nullptr;
	_CurPos = 0;
	_Len = 0;
}

void os::MemoryFileRef::SetMemoryBuffer(LPVOID pData, SIZE_T Len)
{
	_pData = (LPBYTE)pData;
	_Len = Len;
	_CurPos = 0;
}

SIZE_T os::MemoryFileRef::Write(LPCVOID pBuf, SIZE_T sz)
{
	if(sz + _CurPos <= _Len)
	{
		memcpy(&_pData[_CurPos],pBuf,sz);
		_CurPos += sz;
		return sz;
	}
	else if(_Len > _CurPos)
	{	sz = _Len - _CurPos;
		memcpy(&_pData[_CurPos], pBuf, sz);
		_CurPos = _Len;
		return sz;
	}
	else
		return 0;
}

SIZE_T os::MemoryFileRef::Seek(SSIZE_T offset, UINT where)
{
	if(where == Seek_Begin)
	{	ASSERT(offset<=(int)_Len);
		_CurPos = offset;
	}
	else if(where == Seek_Current)
	{	ASSERT(offset+(int)_CurPos>=0);
		ASSERT(offset+(int)_CurPos<=(int)_Len);
		_CurPos += offset;
	}
	else
	{	ASSERT(where == Seek_End);
		ASSERT(offset<=0);
		ASSERT(((UINT)-offset)<_Len);
		
		_CurPos = _Len + offset - 1;
	}

	return _CurPos;
}

SIZE_T os::MemoryFileRef::GetLength() const
{
	return _Len;
}


SIZE_T os::MemoryFileRef::Read(LPVOID pBuf, SIZE_T sz)
{
	if(sz + _CurPos <= _Len)
	{
		memcpy(pBuf, &_pData[_CurPos], sz);
		_CurPos += sz;
		return sz;
	}
	else if(_Len > _CurPos)
	{	
		sz = _Len - _CurPos;
		memcpy(pBuf, &_pData[_CurPos], sz);
		_CurPos = _Len;
		return sz;
	}
	else
		return 0;
}

os::MemoryFile::MemoryFile(SIZE_T Len)
{
	_CurPos = 0;
	if(Len)
	{
		_pData = _Malloc32AL(BYTE,Len);
		_Len = Len;
	}
	else
	{	
		_pData = nullptr;
		_Len = 0;
	}
}

os::MemoryFile::~MemoryFile()
{
	_SafeFree32AL(_pData);
}

void os::MemoryFile::SetBufferSize(SIZE_T Len)
{
	if(Len == _Len)return;

	_SafeFree32AL(_pData);
	_pData = _Malloc32AL(BYTE,Len);
	_CurPos = 0;
	_Len = Len;
}


//////////////////////////////////////////////
// File
bool os::File::Open(LPCSTR fn, LPCSTR mode, bool create_path)
{
	ASSERT(fn);
	ASSERT(!IsOpen());
	_bErrorFlag = false;

	if(create_path)CreateDirectories(fn);

#ifdef	PLATFORM_WIN
	_hFile = _OpenFile(fn, mode);
#else
	_hFile = fopen(fn, mode);
#endif

	if(IsOpen())
	{	
		ResolveRelativePath(fn, _Filename);
		return true;
	}
	else
	{	if(Normal_ReadWrite == mode)
		{	File	file(fn, Normal_Write, create_path);
			if(!file.IsOpen())return false;
			file.Close();

			#ifdef	PLATFORM_WIN
				_hFile = _OpenFile(fn, mode);
			#else
				_hFile = fopen(fn, mode);
			#endif
		}
		if(IsOpen())ResolveRelativePath(fn, _Filename);
		return IsOpen();
	}
}

#if defined(PLATFORM_WIN)
HANDLE os::File::_OpenFile(LPCSTR fn, LPCSTR mode)
{
	if(!mode) return INVALID_HANDLE_VALUE;
	if(_hFile != INVALID_HANDLE_VALUE) ::CloseHandle(_hFile);
	DWORD dwDesiredAccess;
	DWORD dwCreationDisposition;
	switch (*mode++) 
	{
		case 'r':	/* open for reading */
			dwDesiredAccess       = GENERIC_READ;
			dwCreationDisposition = OPEN_EXISTING;
			break;
		case 'w':	/* open for writing */
			dwDesiredAccess       = GENERIC_WRITE;
			dwCreationDisposition = CREATE_ALWAYS;
			break;
		case 'a':	/* open for appending */
			dwDesiredAccess       = FILE_APPEND_DATA;
			dwCreationDisposition = OPEN_ALWAYS;
			break;
		default:	/* illegal mode */
			return INVALID_HANDLE_VALUE;
	}

	WORD count = 3;
	while(*mode && count--)
	{
		switch (*mode++)
		{
			case 'b':
			{
				continue;
				break;
			}
			case '+':
			{
				if (dwDesiredAccess != FILE_APPEND_DATA)
				{
					dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
				}
				else
				{
					dwDesiredAccess = GENERIC_READ | FILE_APPEND_DATA;
				}
				break;
			}
			case 'x':
			{
				if(dwCreationDisposition == CREATE_ALWAYS)
				{
					dwCreationDisposition = CREATE_NEW;
				}
				else
				{
					return INVALID_HANDLE_VALUE;
				}
				break;
			}
			default:	/* illegal mode */
				return INVALID_HANDLE_VALUE;
		}
	}
	return ::CreateFileW(__UTF16(fn), dwDesiredAccess, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, dwCreationDisposition, FILE_ATTRIBUTE_NORMAL, NULL);	
}

__time64_t os::File::_WindowsTickToUnixSeconds(LPFILETIME fileTime) 
{
	LONGLONG windowsTicks = ((LONGLONG)fileTime->dwHighDateTime << 32) | fileTime->dwLowDateTime;
	return (__time64_t)(windowsTicks / WINDOWS_TICK - SEC_TO_UNIX_EPOCH);
}

bool os::File::_UnixSecondsToWindowsTick(__time64_t unixFileTime, LPFILETIME WinFileTime) 
{
	if(!WinFileTime) return false;
	LONGLONG windowsTicks = ((LONGLONG)unixFileTime + SEC_TO_UNIX_EPOCH) * WINDOWS_TICK;
	WinFileTime->dwLowDateTime = (DWORD)windowsTicks;
	WinFileTime->dwHighDateTime = windowsTicks >> 32;
	return true;
}
#endif

os::File::File()
{	
	_bErrorFlag=false;
}

os::File::File(LPCSTR fn, LPCSTR mode, bool create_path)
{
	_bErrorFlag=false; 
	Open(fn,mode,create_path);
}

os::File::~File()
{
	if(IsOpen())Close();
}

bool os::File::IsOpen() const 
{ 
#if defined(PLATFORM_WIN)
	return _hFile != INVALID_HANDLE_VALUE;
#else
	return _hFile != nullptr;
#endif
}

bool os::File::IsEOF()
{
#if defined(PLATFORM_WIN)
	ASSERT(_hFile != INVALID_HANDLE_VALUE); 
	LARGE_INTEGER pos, size;
	LARGE_INTEGER zero = { 0 };
	::SetFilePointerEx(_hFile, zero, &pos, FILE_CURRENT);
	::GetFileSizeEx(_hFile, &size);
	return (pos.QuadPart >= size.QuadPart);
#else
	ASSERT(_hFile != nullptr); 
	return feof(_hFile);
#endif
}

bool os::File::_GetFileStat(LPCSTR p, struct _stat64& st)
{
	if(p == nullptr || p[0] == '\0')return false;

	rt::Zero(st);
#ifdef	PLATFORM_WIN
	if(p[1] == ':' && p[2] == 0)
	{	char path[4] = { p[0], ':' , '\\', '\0' };
		return 0 == _wstat64(__UTF16(path), &st);
	}
	else
	{	return 0 == _wstat64(__UTF16(p), &st);
	}
#elif defined(PLATFORM_IOS)
	return 0 == stat(p, &st);
#else
	return 0 == stat64(p, &st);
#endif
}

#if !defined(PLATFORM_WIN)
bool os::File::_GetFileStat(struct _stat64& stat) const
{
#ifdef PLATFORM_IOS
		return 0 == fstat(fileno(_hFile), &stat);
#else
		return 0 == fstat64(fileno(_hFile), &stat);
#endif
}
#endif

ULONGLONG os::File::GetFileSize() const
{
#ifdef PLATFORM_WIN
	LARGE_INTEGER	i;
	::GetFileSizeEx(_hFile, &i);
	return i.QuadPart;
#else
	struct _stat64 s;
	if(_GetFileStat(s))
		return s.st_size;
	else
		return 0;
#endif
}

bool os::File::Lock(bool no_wait)
{
	ASSERT(!_FileLockedSize);
#ifdef	PLATFORM_WIN
	OVERLAPPED lap;
	rt::Zero(lap);

	ULONGLONG size = GetFileSize();
	if (::LockFileEx(_hFile, LOCKFILE_EXCLUSIVE_LOCK | (no_wait ? LOCKFILE_FAIL_IMMEDIATELY : 0)
		, 0, MAXDWORD, MAXDWORD, &lap))
	{
		_FileLockedSize = true;
		return true;
	}
	else return false;
#else
	int res = flock(GetFD(), LOCK_EX | (no_wait ? LOCK_NB : 0));
	if (res != -1)
	{
		_FileLockedSize = true;
		return true;
	}
	return false;
#endif
}

void os::File::Unlock()
{
	ASSERT(_FileLockedSize);
#ifdef	PLATFORM_WIN
	OVERLAPPED lap;
	rt::Zero(lap);
	VERIFY(::UnlockFileEx(_hFile, 0, MAXDWORD,MAXDWORD, &lap));
	_FileLockedSize = false;
#else
	VERIFY(flock(GetFD(), LOCK_UN) != -1);
	_FileLockedSize = false;
#endif
}

ULONGLONG os::File::GetFileSize(LPCSTR pathname)
{
	struct _stat64 s;
	if(_GetFileStat(pathname, s))
		return s.st_size;
	else
		return 0;
}

bool os::File::MoveFile(LPCSTR from, LPCSTR to, bool overwrite)	// will try move if fail, try copy & delete
{
	os::File::CreateDirectories(to, true);

	if(Rename(from, to))return true;
	if(IsExist(to) && !overwrite)return false;
	// Copy it
	os::File src,dst;
	rt::Buffer<BYTE>	buf;
	if(	buf.SetSize(2*1024*1024) &&
		src.Open(from) &&
		dst.Open(to, os::File::Normal_Write, true)
	)
	{	ULONGLONG fsize = src.GetLength();
		while(fsize)
		{
			uint32_t block = (uint32_t)rt::min((ULONGLONG)buf.GetSize(), fsize);
			if(	src.Read(buf, block) == block &&
				dst.Write(buf, block) == block
			)
			{	fsize -= block;
			}
			else
			{	goto ERROR_COPY;
			}
		}
	}
	else return false;

	__time64_t la, lm;
	if(src.GetFileTime(nullptr, &la, &lm))
	{
		dst.SetFileTime(la, lm);
	}

	src.Close();
	os::File::Remove(from);
	return true;

ERROR_COPY:
	if(dst.IsOpen())
	{
		dst.Close();
		os::File::Remove(to);
	}

	return false;
}

bool os::File::GetFileTime(__time64_t* creation,__time64_t* last_access,__time64_t* last_modify) const
{
#if defined(PLATFORM_WIN)
	FILETIME creationTime   = { 0 };
	FILETIME lastAccessTime = { 0 };
	FILETIME lastWriteTime  = { 0 };
	if (::GetFileTime(_hFile, &creationTime, &lastAccessTime, &lastWriteTime))
	{
		if(creation)*creation		= _WindowsTickToUnixSeconds(&creationTime);
		if(last_access)*last_access = _WindowsTickToUnixSeconds(&lastAccessTime);
		if(last_modify)*last_modify = _WindowsTickToUnixSeconds(&lastWriteTime);
		return true;
	}
	return false;
#else
	struct _stat64 s;
	if(_GetFileStat(s))
	{
		if(creation)*creation = s.st_ctime;
		if(last_access)*last_access = s.st_atime;
		if(last_modify)*last_modify = s.st_mtime;
		return true;
	}
	return false;
#endif
}

bool os::File::GetFileTime(LPCSTR fn, __time64_t* creation, __time64_t* last_access, __time64_t* last_modify)
{
#if defined(PLATFORM_WIN)
	WIN32_FILE_ATTRIBUTE_DATA data;
	if (!GetFileAttributesExW(__UTF16(fn), GetFileExInfoStandard, &data)) 
	{
		return false;
	}
	if(creation)*creation		= _WindowsTickToUnixSeconds(&data.ftCreationTime);
	if(last_access)*last_access = _WindowsTickToUnixSeconds(&data.ftLastAccessTime);
	if(last_modify)*last_modify = _WindowsTickToUnixSeconds(&data.ftLastWriteTime);
	return true;
#else
	struct _stat64 s;
	if(!_GetFileStat(fn, s))
	{
		return false;
	}
	if(creation)*creation = s.st_ctime;
	if(last_access)*last_access = s.st_atime;
	if(last_modify)*last_modify = s.st_mtime;
	return true;
#endif
}

bool os::File::SetFileTime(__time64_t last_access, __time64_t last_modify) const
{
#ifdef	PLATFORM_WIN
	__time64_t creation(0), access(0), modify(0);
	if((last_access == 0 || last_modify == 0) && !GetFileTime(&creation, &access, &modify))
		return false;
	
	FILETIME last_access_time = { 0 };
	FILETIME last_write_time  = { 0 };
	_UnixSecondsToWindowsTick((last_access?last_access:access), &last_access_time);
	_UnixSecondsToWindowsTick((last_modify?last_modify:modify), &last_write_time);
	return ::SetFileTime(_hFile, nullptr, &last_access_time, &last_write_time);
#else//if defined(PLATFORM_MAC) || defined(PLATFORM_IOS)
	struct _stat64 s;
	if((last_access == 0 || last_modify == 0) && !_GetFileStat(s))
		return false;
	timeval tm[2];
	tm[0].tv_sec = (time_t)(last_access?last_access:s.st_atime);
	tm[0].tv_usec = 0;
	tm[0].tv_sec = (time_t)(last_modify?last_modify:s.st_mtime);
	tm[0].tv_usec = 0;
	#if defined(PLATFORM_ANDROID)
		ASSERT(!_Filename.IsEmpty());
		return 0 == utimes(_Filename, tm);
	#else
		return 0 == futimes(fileno(_hFile), tm);
	#endif
#endif
}

bool os::File::GetPathTime(LPCSTR pathname, __time64_t* creation,__time64_t* last_access,__time64_t* last_modify)	// handles file and directory, feed nullptr if not interested
{
	struct _stat64 s;
	if(_GetFileStat(pathname, s))
	{
		if(creation)*creation = s.st_ctime;
		if(last_access)*last_access = s.st_atime;
		if(last_modify)*last_modify = s.st_mtime;
		return true;	
	}
	return false;
}

bool os::File::SetPathTime(LPCSTR pathname, __time64_t last_access, __time64_t last_modify)
{
	struct _stat64 s;
	if((last_access == 0 || last_modify == 0) && !_GetFileStat(pathname, s))
		return false;

#ifdef	PLATFORM_WIN
	__utimbuf64	 ft;
	ft.actime = last_access?last_access:s.st_atime;
	ft.modtime = last_modify?last_modify:s.st_mtime;
	return 0 == _wutime64(__UTF16(pathname), &ft);
#else
	timeval tm[2];
	tm[0].tv_sec = (time_t)(last_access?last_access:s.st_atime);
	tm[0].tv_usec = 0;
	tm[0].tv_sec = (time_t)(last_modify?last_modify:s.st_mtime);
	tm[0].tv_usec = 0;
	return 0 == utimes(pathname, tm);
#endif
}

bool os::File::IsDirectory(LPCSTR path)
{
	struct _stat64 stat;
	return _GetFileStat(path,stat) && (stat.st_mode & _S_IFDIR);
}

bool os::File::IsFile(LPCSTR path)
{
	struct _stat64 stat;
	return _GetFileStat(path,stat) && (0==(stat.st_mode & _S_IFDIR));
}

bool os::File::IsExist(LPCSTR fn)
{
	struct _stat64 stat;
	return _GetFileStat(fn,stat);
}

bool os::File::Remove(LPCSTR fn, bool secure)
{
	if(secure)
	{
		os::File file;
		if(file.Open(fn, os::File::Normal_ReadWrite))
		{
			SIZE_T len = file.GetLength();
			rt::Buffer<BYTE> a;
			a.SetSize((SIZE_T)rt::min((unsigned long long int)len, 1024ULL*64));
			a.Zero();
			file.SeekToBegin();
			for(SIZE_T off = 0; off < file.GetLength(); off += a.GetSize())
				file.Write(a, rt::min(len - off, a.GetSize()));
			file.Flush();
		}
	}

#ifdef	PLATFORM_WIN
	return 0 == _wremove(__UTF16(fn));
#else
	return 0 == remove(fn);
#endif
}

bool os::File::RemoveDirectory(LPCSTR path)
{
#ifdef	PLATFORM_WIN
	return 0 == _wrmdir(__UTF16(path));
#else
	return 0 == rmdir(path);
#endif
}

bool os::File::Rename(LPCSTR fn,LPCSTR new_fn)
{
#ifdef	PLATFORM_WIN
	return ::MoveFileW(__UTF16(fn), __UTF16(new_fn));
#else
	return 0 == rename(fn, new_fn);
#endif
}

void os::File::ResolveRelativePath(LPCSTR path, rt::String& fn_out)
{
#ifdef	PLATFORM_WIN
	os::__UTF16 in(path);
	DWORD len = rt::max<DWORD>(MAX_PATH, (DWORD)in.GetLength())*2;
	WCHAR* out = (WCHAR*)alloca(sizeof(WCHAR)*len);
	
	len = GetFullPathNameW(in, len, out, nullptr);
	if(len)
	{	fn_out = os::__UTF8(out, len);
		return;
	}
	fn_out = path;
#else
    rt::String __homed;
    if(path[0] == '~')
    {
        const char *homedir = getenv("HOME");
        if(homedir == nullptr)
        {
            fn_out = path;
            return;
        }
        
        __homed = rt::String_Ref(homedir) + (path+1);
        path = __homed;
    }
    
    if(os::File::IsExist(path))
    {
        if (path == (LPCSTR)fn_out.Begin())
        {
            rt::String temp = rt::String_Ref((LPCSTR)fn_out.Begin(), fn_out.GetLength());
            temp.SetLength(PATH_MAX);
            VERIFY(realpath(path, temp));
            path = (LPCSTR)temp.Begin();
            fn_out = temp;
        }
        else
        {
            fn_out.SetLength(PATH_MAX);
            VERIFY(realpath(path, fn_out));
        }
        fn_out.RecalculateLength();
        return;
    }
    else // realpath(3) don't works for path that not exist on the disk
    {
        rt::String_Ref input = path;
        rt::String temp;
        if(path[0] != '/')
        {   // relative path
            os::File::GetCurrentDirectory(temp);
            temp += '/';
            temp += input;
            input = temp;
            fn_out.Empty();
        }
        else
        {   rt::Swap(temp, fn_out);
        }
        
        ASSERT(input[0] == '/');
        
        rt::String_Ref seg[1024];
        UINT co = input.Split<true>(seg, sizeofArray(seg), "/\\");
        uint32_t parsed = 0;
        for(UINT i=0; i<co; i++)
        {
            if(seg[i].IsEmpty() || seg[i] == ".")continue;
            if(seg[i] == ".."){ parsed--; continue; }
            if(parsed<0)return;
            seg[parsed++] = seg[i];
        }
        
        for(UINT i=0; i<parsed; i++)
        {
            fn_out += rt::SS() + '/' + seg[i];
        }
        
        if(input.Last() == '/' || input.Last() == '\\')fn_out += '/';
        return;
    }
#endif
}

bool os::File::LoadBinary(LPCSTR fn, rt::String& out, UINT expire_sec)
{
	os::File file;
	if(	file.Open(fn) &&
		(os::Timestamp::Get()/1000 - file.GetTime_LastModify()) < expire_sec &&
		out.SetLength(file.GetLength())
	)
	{	
		return file.Read(out, out.GetLength()) == out.GetLength();
	}

	return false;
}

bool os::File::LoadText(LPCSTR fn, rt::String& out, UINT expire_sec)
{
#if defined(PLATFORM_ANDROID) || defined(PLATFORM_LINUX)
	rt::String_Ref filename(fn);
	if(filename.StartsWith("/proc/") || filename.StartsWith("/sys/"))
	{
		out.Empty();
		int fd = open(fn, O_RDONLY);
		if(fd>0)
		{			
			char data[10240];
			int r = read(fd, data, sizeof(data));
			close(fd);
			out = rt::String_Ref(data, r);
			return true;
		}
		return false;
	}
#endif
	
	os::File file;
	if(	file.Open(fn) &&
		(os::Timestamp::Get()/1000 - file.GetTime_LastModify()) < expire_sec &&
		out.SetLength(file.GetLength())
	)
	{	if(out.GetLength() < 3)
			return file.Read(out.Begin(), out.GetLength()) == out.GetLength();

		if(file.Read(out.Begin(), 3) == 3)
		{	
			if(	out[0] == '\xef' &&
				out[1] == '\xbb' &&
				out[2] == '\xbf'		// skip UTF8 signature
			)
			{	out.SetLength(out.GetLength()-3);
				return file.Read(out.Begin(), out.GetLength()) == out.GetLength();
			}
			else if(out[0] == '\xff' && out[1] == '\xfe')	// UTF16 
			{
				rt::Buffer<BYTE>	utf16;
				utf16.SetSize(out.GetLength() - 2);
				utf16[0] = out[2];
				if(file.Read(&utf16[1], utf16.GetSize()-1) == utf16.GetSize()-1)
				{
					out.SetLength(os::UTF8EncodeLength((os::LPCU16CHAR)utf16.Begin(),(int)(utf16.GetSize()/2)));
					out.SetLength(os::UTF8Encode((os::LPCU16CHAR)utf16.Begin(),(int)(utf16.GetSize()/2), out.Begin()));
					return true;
				}
			}
			else
			{	return file.Read(&out[3], out.GetLength()-3) == out.GetLength()-3;
			}
		}
	}

	return false;
}

bool os::File::SaveText(LPCSTR fn, const rt::String_Ref& in, bool add_utf8_signature, bool append)
{
	static const LPCSTR sign = "\xef\xbb\xbf";
	os::File file;
	if(append)
	{
		if(!file.Open(fn, os::File::Normal_Append, true))return false;
		if(add_utf8_signature && file.GetLength()==0 && file.Write(sign,3) != 3)return false;

		return	file.Write(in.Begin(), in.GetLength()) == in.GetLength();
	}
	else 
		return	file.Open(fn, os::File::Normal_Write, true) &&
				(!add_utf8_signature || file.Write(sign,3) == 3) &&
				file.Write(in.Begin(), in.GetLength()) == in.GetLength();
}

bool os::File::SaveBinary(LPCSTR fn, const rt::String_Ref& in)
{
	os::File file;
	return	file.Open(fn, os::File::Normal_Write, true) &&
			file.Write(in.Begin(), in.GetLength()) == in.GetLength();
}


bool os::File::CreateDirectory(LPCSTR path)
{
#if		defined(PLATFORM_WIN)
		_wmkdir(__UTF16(path));
#else
		mkdir(path,0775);
#endif
	return IsDirectory(path);
}

bool os::File::CreateDirectories(LPCSTR pathin, bool file_mode)
{
	rt::String_Ref ppp = pathin;
	if(file_mode)
		ppp = ppp.GetDirectoryName().TrimTrailingPathSeparator();
	if (ppp.IsEmpty()) return false;

	rt::String	path(ppp);
	if(CreateDirectory(path))return true;
	
	ASSERT(!path.IsEmpty());
	path.Replace('\\', '/');

	LPSTR p = path.Begin();
	LPSTR sep = p;
	LPSTR last_sep = nullptr;
	for(;;)
	{
		while(*sep && *sep!='/')sep++;
		if(!*sep)break;
		last_sep = sep;
		*sep = 0;
		if(p[0])
		{
#ifdef	PLATFORM_WIN
			_wmkdir(__UTF16(p));
#else
			mkdir(p,0775);
#endif
		}
		*sep = '/';
		sep++;
	}

	if(p[0] == 0)return true;

	if(last_sep)*last_sep = 0;
	return CreateDirectory(pathin);
}

SIZE_T os::File::Read(LPVOID lpBuf,SIZE_T nCount)
{
	ASSERT(IsOpen());
#if defined(PLATFORM_WIN)
	SIZE_T bytesRead = 0;
	SIZE_T remainCount = nCount;
	LPBYTE tLpBuf = (LPBYTE)lpBuf;
	while (remainCount >= MAXDWORD)
	{
		DWORD tBytesRead = 0;
		if(!::ReadFile(_hFile, tLpBuf, MAXDWORD, &tBytesRead, nullptr))
		{
			rt::_CastToNonconst(this)->_bErrorFlag = true;
			return bytesRead;
		}
		tLpBuf += tBytesRead;
		bytesRead += tBytesRead;
		if(MAXDWORD != tBytesRead)
		{
			return bytesRead;
		}
		
		remainCount -= MAXDWORD;
	}

	if(remainCount)
	{
		DWORD tBytesRead = 0;
		if(!::ReadFile(_hFile, tLpBuf, (DWORD)remainCount, &tBytesRead, nullptr))
		{
			rt::_CastToNonconst(this)->_bErrorFlag = true;
		}
		bytesRead += tBytesRead;
	}
	return bytesRead;
#else
	SIZE_T read = fread(lpBuf, 1, nCount, _hFile);
	if( read == nCount ){}
	else{ rt::_CastToNonconst(this)->_bErrorFlag = true; }
	return read;
#endif
}

SIZE_T os::File::Write(LPCVOID lpBuf,SIZE_T nCount)
{
	ASSERT(IsOpen());
#if defined(PLATFORM_WIN)
	SIZE_T bytesWritten = 0;
	SIZE_T remainCount = nCount;
	LPBYTE tLpBuf = (LPBYTE)lpBuf;
	while (remainCount >= MAXDWORD)
	{
		DWORD tBytesWritten = 0;
		if(!::WriteFile(_hFile, tLpBuf, MAXDWORD, &tBytesWritten, nullptr) || 
		   MAXDWORD != (SIZE_T)tBytesWritten)
		{
			rt::_CastToNonconst(this)->_bErrorFlag = true;
			return (bytesWritten + tBytesWritten);
		}
		tLpBuf += tBytesWritten;
		bytesWritten += tBytesWritten;
		remainCount -= MAXDWORD;
	}

	if(remainCount)
	{
		DWORD tBytesWritten = 0;
		if(!::WriteFile(_hFile, tLpBuf, (DWORD)remainCount, &tBytesWritten, nullptr) || 
		   remainCount != (SIZE_T)tBytesWritten)
		{
			rt::_CastToNonconst(this)->_bErrorFlag = true;
		}
		bytesWritten += tBytesWritten;
	}
	return bytesWritten;
#else
	SIZE_T write = fwrite(lpBuf, 1, nCount, _hFile);
	if( write == nCount ){}
	else{ rt::_CastToNonconst(this)->_bErrorFlag = true; }
	return write;
#endif
}

void os::File::Flush()
{
	ASSERT(IsOpen());
#if defined(PLATFORM_WIN)
	::FlushFileBuffers(_hFile);
#else
	fflush(_hFile);
#endif
}

void os::File::Close()
{
	if(IsOpen())
	{
		if(IsLockAcquired())Unlock();
#if defined(PLATFORM_WIN)
		::CloseHandle(_hFile);
		_hFile = INVALID_HANDLE_VALUE;
#else
		fclose(_hFile);
		_hFile = nullptr;
#endif
	}
}

SIZE_T os::File::GetLength() const
{
#ifdef PLATFORM_WIN
	LARGE_INTEGER	i;
	::GetFileSizeEx(_hFile, &i);
	return (SIZE_T)i.QuadPart;
#else
	struct _stat64 s;
	_GetFileStat(s);

	return (SIZE_T)s.st_size;
#endif
}

bool os::File::Preallocate(SIZE_T len)
{
	if(len <= GetLength())
		return Truncate(len);
	else
	{
#if defined(PLATFORM_WIN)
	ULONGLONG l = len;
	if(!::SetFilePointerEx(_hFile, (LARGE_INTEGER&)l, NULL, FILE_BEGIN) || !::SetEndOfFile(_hFile))return false;
	Seek(--l); Write('\x0');
	return true;
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_ANDROID)
	return fallocate64(GetFD(), 0, 0, len) == 0;
#else
	return Truncate(len);  // TBD, a better way?
#endif
	}
}

bool os::File::Truncate(SIZE_T len)
{
#if defined(PLATFORM_WIN)
	if(!::SetFilePointerEx(_hFile, (LARGE_INTEGER&)len, NULL, FILE_BEGIN) || !::SetEndOfFile(_hFile))return false;
	return true;
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_ANDROID)
    return ftruncate64(GetFD(), len) == 0;
#else
	return ftruncate(GetFD(), len) == 0;
#endif
}

SIZE_T os::File::GetCurrentPosition() const
{ 
	ASSERT(IsOpen());
#if defined(PLATFORM_WIN)
	LARGE_INTEGER currentPos = { 0 };
	LARGE_INTEGER zero = { 0 };
	::SetFilePointerEx(_hFile, zero, &currentPos, FILE_CURRENT);
	return currentPos.QuadPart;
#else
    return (SIZE_T)ftello(_hFile);
#endif
}

SIZE_T os::File::Seek(SSIZE_T offset, UINT nFrom)
{
	ASSERT(IsOpen());
#if defined(PLATFORM_WIN)
	LARGE_INTEGER	currentPos = { 0 };
	::SetFilePointerEx(_hFile, (LARGE_INTEGER&)offset, &currentPos, nFrom);
	return currentPos.QuadPart;
#else
    fseeko(_hFile, offset, nFrom);
    return GetCurrentPosition();
#endif
}

void os::File::SeekToBegin()
{
	ASSERT(IsOpen());
	Seek(0,(DWORD)Seek_Begin);
}

SIZE_T os::File::SeekToEnd()
{
	ASSERT(IsOpen());
	return Seek(0,(DWORD)Seek_End);
}

void os::File::GetCurrentDirectory(rt::String& out)
{
#ifdef PLATFORM_WIN
	WCHAR buf[MAX_PATH*2];
	int len = ::GetCurrentDirectoryW(sizeofArray(buf),buf);
	if(len)
	{
		int utf8_len = (int)UTF8EncodeLength(buf,len);
		out.SetLength(utf8_len);
		UTF8Encode(buf,len,out.Begin());
	}
	else
	{	out.Empty();
	}
#else
	out.SetLength(1024);
	if (getcwd(out, out.GetLength()))
		out.RecalculateLength();
	else
		out.Empty();
#endif

	if(out.IsEmpty())
		ResolveRelativePath(".", out);
}

bool os::File::SetCurrentDirectory(LPCSTR path)
{
#ifdef PLATFORM_WIN
	return ::SetCurrentDirectoryW(__UTF16(path));
#else
	return 0 == chdir(path);
#endif
}

os::CurrentDirectoryStack::~CurrentDirectoryStack()
{
	if(_DirStack.GetSize())
	{
		os::File::SetCurrentDirectory(_DirStack[0]);
		_DirStack.ShrinkSize(0);
	}
}

bool os::CurrentDirectoryStack::PushCurrentDirectory(LPCSTR dir)
{
	os::File::ResolveRelativePath("./", _DirStack.push_back());
	if(os::File::SetCurrentDirectory(dir))
		return true;

	_DirStack.pop_back();
	return false;
}

void os::CurrentDirectoryStack::Pop()
{
	ASSERT(_DirStack.GetSize());
	VERIFY(os::File::SetCurrentDirectory(_DirStack.last()));

	_DirStack.pop_back();
}

bool os::File::ProbeAvailableFilename(LPCSTR fn, rt::String& fn_out)
{
	if(IsExist(fn))
	{
		rt::String_Ref filename(fn);
		rt::String_Ref ext = filename.GetExtName();
		rt::String_Ref fnmain = filename.TrimRight(ext.GetLength());
		int idx = 1;
		do
		{	fn_out = fnmain + '_' + '(' + idx + ')' + ext;
			idx *= 2;
		}while(IsExist(fn_out));

		int open = idx/4;	// exist
		int close = idx/2;	// nonexist
		while(close - open > 1)
		{
			idx = (open + close)/2;
			fn_out = fnmain + '_' + '(' + idx + ')' + ext;
			if(IsExist(fn_out))
				open = idx;
			else
				close = idx;
		}
		fn_out = fnmain + '_' + '(' + close + ')' + ext;
		return true;
	}
	else
	{	
		fn_out = fn;
		return false;
	}
}

bool os::File::RemovePath(const rt::String_Ref& src_)
{
	rt::String src = src_.TrimTrailingPathSeparator();

	if(!os::File::IsExist(src))return true;

	if(os::File::IsDirectory(src))
	{
		os::FileList fl;
		fl.Populate(src, nullptr, os::FileList::FLAG_RECURSIVE);

		for(INT i = fl.GetCount()-1; i>=0; i--)
			if(!fl.IsDirectory(i))
				os::File::Remove(fl.GetFullpath(i));

		for(INT i = fl.GetCount()-1; i>=0; i--)
			if(fl.IsDirectory(i))
				os::File::RemoveDirectory(fl.GetFullpath(i));

		return os::File::RemoveDirectory(src);
	}
	else
	{	return os::File::Remove(src);
	}
}

bool os::File::CopyPath(const rt::String_Ref& dest_, const rt::String_Ref& src_, DWORD opt)
{
	__time64_t s_tm, d_tm;

	rt::String src = src_.TrimTrailingPathSeparator();
	if(!os::File::GetPathTime(src, nullptr, nullptr, &s_tm))
		return false;

	rt::String dst = dest_.TrimTrailingPathSeparator();

	bool skip_unmodified = !(opt&CPOPT_OVERWRITE_ALL);
	bool overwrite = opt&(CPOPT_OVERWRITE|CPOPT_MIRROR|CPOPT_OVERWRITE_ALL);
	thread_local rt::BufferEx<BYTE>	buf;

	// Copy a file
	if(os::File::IsFile(src))
	{
		ULONGLONG file_size = os::File::GetFileSize(src);
		os::File file;
		if(!file.Open(src, os::File::Normal_Read))
			return false;

		if(os::File::IsExist(dst))
		{
			if(!overwrite)return true;

			if(os::File::IsDirectory(dst))
			{
				if(!RemovePath(dst))return false;
			}
			else if(skip_unmodified)
			{
				if(file_size == os::File::GetFileSize(dst))
				{
					os::File::GetPathTime(dst, nullptr, nullptr, &d_tm);
					if(s_tm == d_tm) // file is same, skip
						return true;
				}
			}
		}

		os::File out;
		if(!out.Open(dst, os::File::Normal_Write))return false;

		// copy file
		buf.SetSize(rt::min(file_size, ULONGLONG(64ULL*1024*1024))); // ULONGLONG defined in "predefines.h"; in non-windows x64 env, "uint64_t" is "unsigned long“, not "unsigned long long"

		while(file_size)
		{
			UINT chunk = (UINT)rt::min(buf.GetSize(), file_size);

			if(file.Read(buf, chunk) != chunk || out.Write(buf, chunk) != chunk)
			{
				out.Close();
				os::File::Remove(dst);
				if((opt&0x80000000) == 0)buf.SetSize(0);
				return false;
			}

			file_size -= chunk;
		}

		file.Close();
		out.SetFileTime(s_tm, s_tm);
		if((opt&0x80000000) == 0)buf.SetSize(0);
		return true;
	}

	ASSERT_NO_FUNCTION_REENTRY;
	// copy as a directory
	auto setup_dir = [](LPCSTR dst)
	{
		if(os::File::IsExist(dst))
		{
			if(os::File::IsFile(dst))
				if(!os::File::Remove(dst))
					return false;
		}
		else
			if(!CreateDirectories(dst, false))
				return false;

		return true;
	};

	setup_dir(dst);

	rt::String dst_fn;
	os::FileList flist;
	flist.Populate(src, nullptr, os::FileList::FLAG_RECURSIVE|((opt&CPOPT_HIDDEN_FILE)?os::FileList::FLAG_SKIPHIDDEN:0));

	// create all subdirectories
	for(UINT i=0;i<flist.GetCount();i++)
	{
		if(!flist.IsDirectory(i))continue;

		dst_fn = dst + flist.GetFilename(i);
		if(!setup_dir(dst_fn))return false;

		const rt::String& src_fn = flist.GetFullpath(i);
		os::File::GetPathTime(src_fn, nullptr, nullptr, &s_tm);
		os::File::SetPathTime(dst_fn, s_tm, s_tm);
	}

	if(opt&CPOPT_MIRROR)
	{	// remove all extra files/directories in the destination
		rt::hash_set<rt::String_Ref, rt::String_Ref::hash_compare> source_set;
		for(UINT i=0;i<flist.GetCount();i++)
			source_set.insert(flist.GetFilename(i));

		os::FileList dest_fnlist;
		if(dest_fnlist.Populate(dst, nullptr, os::FileList::FLAG_RECURSIVE|((opt&CPOPT_HIDDEN_FILE)?os::FileList::FLAG_SKIPHIDDEN:0)))
		{	for(INT i=dest_fnlist.GetCount()-1;i>=0;i--)
				if(source_set.find(dest_fnlist.GetFilename(i)) == source_set.end())
				{	if(dest_fnlist.IsDirectory(i))
						os::File::RemoveDirectory(dest_fnlist.GetFullpath(i));
					else
						os::File::Remove(dest_fnlist.GetFullpath(i));
				}
		}
	}

	// copy all files
	for(UINT i=0;i<flist.GetCount();i++)
	{
		if(flist.IsDirectory(i))continue;

		const rt::String& src_fn = flist.GetFullpath(i);
		dst_fn = dst + flist.GetFilename(i);
		if(!CopyPath(dst_fn, src_fn, 0x80000000|opt))
		{
			buf.SetSize(0);
			return false;
		}
	}

	buf.SetSize(0);
	return true;
}

bool os::FilePacked_Writer::Open(LPCSTR fn) 
{
	ASSERT(!_File.IsOpen());
	DWORD hdr = _details::FilePackedMagic;
	if(	_File.Open(fn, File::Normal_Write) &&
		_File.Write(&hdr,sizeof(DWORD)) == 4
	)
	{	return true;
	}
	else
	{	Close();
		return false;
	}
}

bool os::FilePacked_Writer::Write(ULONGLONG name, LPCVOID data, UINT size)
{
	_details::FilePackedEntry e;
	e.FileName = name;
	e.Offset = (UINT)_File.GetCurrentPosition();
	e.Size = size;

	if(	_File.Write(&e,sizeof(e)) == sizeof(e) &&
		_File.Write(data,size) == size
	)
	{	return true;
	}
	else
	{	_File.Seek(e.Offset, File::Seek_Begin);
		return false;
	}
}

bool os::FilePacked_Writer::Copy(os::FilePacked_Reader& reader, ULONGLONG filename_desired, ULONGLONG filename_mask)
{
	rt::BufferEx<BYTE>	 buf;
	for(UINT i=0;i<reader.GetFileCount();i++)
	{
		ULONGLONG name = reader.GetFileName(i);
		if((name & filename_mask) == filename_desired)
		{
			if(	buf.SetSize(reader.GetFileSize(i)) &&
				reader.Read(i, buf) &&
				Write(name, buf, (UINT)buf.GetSize())
			){}
			else return false;
		}
	}

	return true;
}

bool os::FilePacked_Reader::Open(LPCSTR fn)
{
	ASSERT(!_File.IsOpen());
	DWORD hdr;
	if(	_File.Open(fn, File::Normal_Read) &&
		_File.Read(&hdr,sizeof(DWORD)) == 4 &&
		hdr == _details::FilePackedMagic
	)
	{	_details::FilePackedEntry e;
		SIZE_T offset;
		while(	(offset = _File.GetCurrentPosition()) &&
				_File.Read(&e,sizeof(e)) == sizeof(e) &&
				e.Offset == offset &&
				(offset = offset + sizeof(e) + e.Size) &&
				offset == _File.Seek(offset, File::Seek_Begin)
		)
		{	e.Offset += sizeof(e);
			_Entries.push_back(e);
		}
		return true;
	}
	
	Close();
	return false;
}

void os::FilePacked_Reader::Close()
{
	_Entries.SetSize(0);
	_File.Close(); 
}

UINT os::FilePacked_Reader::FindFirstFile(ULONGLONG name, ULONGLONG mask)	// return idx, INFINITE if not found
{
	_FileSearchName = name & mask;
	_FileSearchMask = mask;
	_FileSearchLast = -1;
	return FindNextFile();
}

UINT os::FilePacked_Reader::FindNextFile() // return idx, INFINITE if not found
{
	for(_FileSearchLast++;_FileSearchLast<(int)_Entries.GetSize();_FileSearchLast++)
		if((_Entries[_FileSearchLast].FileName & _FileSearchMask) == _FileSearchName)
			return _FileSearchLast;
	return INFINITE;
}

UINT os::FilePacked_Reader::_FindFile(ULONGLONG name)
{
	for(UINT i=0;i<(UINT)_Entries.GetSize();i++)
		if(_Entries[i].FileName == name)
			return i;
	return INFINITE;

}

UINT os::FilePacked_Reader::GetFileSize(UINT idx)
{
	return _Entries[idx].Size;
}

ULONGLONG os::FilePacked_Reader::GetFileName(UINT idx)
{
	return _Entries[idx].FileName;
}

bool os::FilePacked_Reader::Read(UINT idx, LPVOID pout)
{
	return _File.Seek(_Entries[idx].Offset, File::Seek_Begin) == _Entries[idx].Offset &&
		   _File.Read(pout, _Entries[idx].Size) == _Entries[idx].Size;
}

UINT os::FilePacked_Reader::GetFileCount() const
{
	return (UINT)_Entries.GetSize();
}

bool os::FilePacked_Reader::Load(ULONGLONG name, rt::String& out)
{
	uint32_t idx;
	return	(idx = _FindFile(name)) != INFINITE &&
			out.SetLength(GetFileSize(idx)) &&
			Read(idx, out.Begin());
}


void os::GetAppSandbox(rt::String& out_path, LPCSTR app_name)
{
#if defined(PLATFORM_WIN)
	WCHAR fn[MAX_PATH*3];
	fn[0] = 0;

	WCHAR path[MAX_PATH+1];
	if(	::GetEnvironmentVariableW(L"APPDATA", path, MAX_PATH) < 3 &&
		::GetEnvironmentVariableW(L"LOCALAPPDATA", path, MAX_PATH) < 3
	)
	{	if(	::GetEnvironmentVariableW(L"USERPROFILE", path, MAX_PATH) < 3 &&
			::GetEnvironmentVariableW(L"HOMEPATH", path + ::GetEnvironmentVariableW(L"HOMEDRIVE", path, 16) , MAX_PATH-16) < 3
		)
		{	os::File::ResolveRelativePath("./app_sandbox", out_path);
			goto APPPATH_UTF8_SET;
		}

		wcscat(path, L"\\AppData\\Roaming");
	}

	out_path = os::__UTF8(path) + '\\' + app_name;

APPPATH_UTF8_SET:
	os::File::CreateDirectories(out_path, false);
	return;	
	
#elif defined(PLATFORM_MAC) || defined(PLATFORM_LINUX)
	rt::String_Ref home(getenv("HOME"));
	out_path = home + "/Library/" + app_name;
	os::File::CreateDirectories(out_path, false);
	
#elif defined(PLATFORM_IOS)
	CHAR path[1024];
	int len = _objc_get_app_sandbox_path(path, sizeof(path)-1);
	out_path = rt::String_Ref(path, len);

#elif defined(PLATFORM_ANDROID)

	/*
	LPCSTR sdcard_roots[] = 
	{	"/mnt",
		"/storage",
		"/Removable"
	};

	rt::String		largest = ".";
	ULONGLONG		lsize = 0;
	rt::String		path;
	for(int i=0; i<sizeofArray(sdcard_roots); i++)
	{
		if(os::File::IsDirectory(sdcard_roots[i]))
		{
			os::FileList	list;
			list.Populate(sdcard_roots[i], nullptr, os::FileList::FLAG_DIRECTORYONLY);
			for(int f = 0; f<list.GetCount(); f++)
			{
				list.GetFullpath(f, path);
				ULONGLONG fs = os::GetFreeDiskSpace(path);
				if(fs > lsize)
				{	lsize = fs;
					largest = path;
				}
			}
		}
	}
	out_path = largest + '/' + app_name;
	*/
	out_path = "/storage/emulated/0/sandbox";
	os::File::CreateDirectory(out_path);
#else
	ASSERT_STATIC_NOT_IMPLMENTED;
#endif
	
}

void os::SetAppSandboxAsCurrentDirectory(LPCSTR app_name)
{
	rt::String	str;
	GetAppSandbox(str, app_name);
	os::File::SetCurrentDirectory(str);
}

ULONGLONG os::GetFreeDiskSpace(LPCSTR path_in, ULONGLONG* pTotal)
{
	rt::String path;
	os::File::ResolveRelativePath(path_in, path);
	if(!os::File::IsDirectory(path))
		path = path.GetDirectoryName();

#if		defined(PLATFORM_WIN)
		ULARGE_INTEGER sz, tot;
		if(GetDiskFreeSpaceExW(__UTF16(path), &sz, &tot, nullptr))
		{	if(pTotal)*pTotal = tot.QuadPart;
			return sz.QuadPart;
		}
#elif	defined(PLATFORM_MAC) || defined(PLATFORM_LINUX)
		struct statfs64 s;
		if(0 == statfs64(path, &s))
		{	if(pTotal)return s.f_blocks * s.f_bsize;
			return s.f_bfree * s.f_bsize;
		}
#elif	defined(PLATFORM_IOS) || defined(PLATFORM_ANDROID)
		struct statfs s;
		if(0 == statfs(path, &s))
		{	if(pTotal)*pTotal = s.f_blocks * s.f_bsize;
			return s.f_bfree * s.f_bsize;
		}
#endif
		return 0;
}

UINT os::FileList::Populate(LPCSTR directory, LPCSTR sf, DWORD flag)
{
	rt::String_Ref dir(directory);
	if(dir.IsEmpty())return 0;
	if(dir.Last() == '/' || dir.Last() == '\\')
		dir = dir.TrimRight(1);

	_Root = dir;
	_Filenames.SetSize(0);

	return _Populate(dir, sf, flag);
}

UINT os::FileList::_Populate(const rt::String_Ref& dir, LPCSTR sf, DWORD flag)
{
	rt::String		suffix_filter(sf);
	suffix_filter.MakeLower();
	rt::String_Ref	suffix[64];
	int	num_suffix = rt::String_Ref(suffix_filter).Split(suffix, 64, '|');

#ifdef PLATFORM_DEBUG_BUILD
	for(int i=0;i<num_suffix;i++)ASSERT(suffix[i].GetLength() <= 16);
#endif

	rt::BufferEx<rt::String>	Paths;
	Paths.push_back() = dir.TrimLeft(_Root.GetLength());

#if defined(PLATFORM_WIN)
	__UTF16*	suffix_w;
	suffix_w = (__UTF16*)alloca(sizeof(__UTF16)*num_suffix);
	for(int i=0;i<num_suffix;i++)
	{	new (&suffix_w[i]) __UTF16(suffix[i]);
	}

	while(Paths.GetSize())
	{
		WIN32_FIND_DATAW fd;
		HANDLE h = ::FindFirstFileW(__UTF16((LPCSTR)(_Root + Paths[0] + rt::String_Ref("\\*.*",4))), &fd);
		if(h != INVALID_HANDLE_VALUE)
		{	do
			{	// filtering
				if(	(FLAG_SKIPHIDDEN &flag) && (fd.cFileName[0] == L'.' || (fd.dwFileAttributes&FILE_ATTRIBUTE_HIDDEN))	)continue;
				if(	(fd.cFileName[0] == 0) ||
					(fd.cFileName[0] == L'.' && fd.cFileName[1] == 0) ||
					(fd.cFileName[0] == L'.' && fd.cFileName[1] == L'.' && fd.cFileName[2] == 0)
				)continue;

				__UTF8 fn_utf8(fd.cFileName);

				if((FLAG_RECURSIVE&flag) && (fd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))
				{	Paths.push_back() = Paths[0] + '/' + fn_utf8;
				}

				if((FLAG_DIRECTORYONLY&flag) && 0==(fd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))continue;
				if((FLAG_NODIRECTORY&flag) && (fd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))continue;

				if((fd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) == 0 && num_suffix)
				{
					WCHAR fn[17];
					int len_all = (int)wcslen(fd.cFileName);
					int len = rt::min(16, len_all);
					memcpy(fn, &fd.cFileName[len_all-len], sizeof(WCHAR)*(len+1));
					wcslwr(fn);
					for(int i=0; i<num_suffix; i++)
					{
						if(	len >= (int)suffix_w[i].GetLength() && 
							memcmp(suffix_w[i].Begin(), &fn[len-suffix_w[i].GetLength()], sizeof(WCHAR)*suffix_w[i].GetLength()) == 0
						)
						{	goto ExtFilterMatched;
						}
					}
					continue;
				}
			
	ExtFilterMatched:
				rt::String_Ref	fn = fn_utf8;
				_File& entry = _Filenames.push_back();
				entry.Name = Paths[0] + '/' + fn_utf8;
				entry.IsDirectory = (fd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)!=0;

				if(FLAG_ONLYFIRSTFILE&flag)break;
			}while(::FindNextFileW(h,&fd));
			::FindClose(h);
		}

		Paths.pop_front();
	}

	for(int i=0;i<num_suffix;i++)
		suffix_w[i].~__UTF16();
#else
	DIR *dp;
	struct dirent *dirp;

	while(Paths.GetSize())
	{
		if((dp = opendir(_Root + Paths[0])))
		{
			while ((dirp = readdir(dp)))
			{
				if(	(FLAG_SKIPHIDDEN&flag) && (dirp->d_name[0] == L'.'))continue;
				if(	(dirp->d_name[0] == 0) ||
					(dirp->d_name[0] == L'.' && dirp->d_name[1] == 0) ||
					(dirp->d_name[0] == L'.' && dirp->d_name[1] == L'.' && dirp->d_name[2] == 0)
				)continue;

				if((FLAG_RECURSIVE&flag) && (dirp->d_type == DT_DIR))
				{	Paths.push_back() = Paths[0] + '/' + dirp->d_name;
				}

				if(	(dirp->d_type == DT_DIR) && (FLAG_NODIRECTORY&flag))continue;
				if(	(dirp->d_type != DT_DIR) && (FLAG_DIRECTORYONLY&flag))continue;

				if(dirp->d_type != DT_DIR && num_suffix)
				{
					char fn[17];
					int  len_all = (int)strlen(dirp->d_name);
					int  len = rt::min(16, len_all);
					memcpy(fn, &dirp->d_name[len_all - len], len+1);
					rt::String_Ref(fn, len).MakeLower();
					for(int i=0; i<num_suffix; i++)
					{
						if(rt::String_Ref(fn, len).EndsWith(suffix[i]))
							goto ExtFilterMatched;
					}
					continue;
				}

ExtFilterMatched:
				_File& entry = _Filenames.push_back();
				entry.Name = Paths[0] + '/' + dirp->d_name;
				entry.IsDirectory = (dirp->d_type == DT_DIR);

				if(FLAG_ONLYFIRSTFILE&flag)break;
			}
			closedir(dp);
		}

		Paths.pop_front();
	}
#endif

	return (UINT)_Filenames.GetSize();
}


#ifdef PLATFORM_WIN

UINT os::FileList::PopulateDropList(HDROP hDropInfo, LPCSTR sf, DWORD flag)
{
	_Filenames.SetSize(0);

	UINT FileCount = ::DragQueryFile(hDropInfo,0xffffffff,nullptr,0);
	if(FileCount)
	{
		rt::String		suffix_filter(sf);
		suffix_filter.MakeLower();
		rt::String_Ref	suffix[64];
		int	num_suffix = rt::String_Ref(suffix_filter).Split(suffix, 64, '|');

		__UTF16*	suffix_w;
		suffix_w = (__UTF16*)alloca(sizeof(__UTF16)*num_suffix);
		for(int i=0;i<num_suffix;i++)
		{	new (&suffix_w[i]) __UTF16(suffix[i]);
		}

#ifdef PLATFORM_DEBUG_BUILD
		for(int i=0;i<num_suffix;i++)ASSERT(suffix[i].GetLength() <= 16);
#endif

		_Filenames.SetSize(0);

		rt::BufferEx<rt::String>	Paths;
		rt::BufferEx<bool>			IsDir;

		for(UINT i=0;i<FileCount;i++)
		{
			WCHAR filename[MAX_PATH];
			UINT Len = ::DragQueryFileW(hDropInfo,i,filename,MAX_PATH);

			DWORD fa = GetFileAttributesW(filename);

			// filtering
			if(	(FLAG_SKIPHIDDEN &flag) && (filename[0] == L'.' || (fa&FILE_ATTRIBUTE_HIDDEN))	)continue;
			if(	(filename[0] == 0) ||
				(filename[0] == L'.' && filename[1] == 0) ||
				(filename[0] == L'.' && filename[1] == L'.' && filename[2] == 0)
			)continue;


			if((FLAG_RECURSIVE&flag) && (fa&FILE_ATTRIBUTE_DIRECTORY))
			{	Paths.push_back() = os::__UTF8(filename, Len);
				IsDir.push_back() = true;
				continue;
			}

			if((FLAG_DIRECTORYONLY&flag) && 0==(fa&FILE_ATTRIBUTE_DIRECTORY))continue;
			if((FLAG_NODIRECTORY&flag) && (fa&FILE_ATTRIBUTE_DIRECTORY))continue;

			if((fa&FILE_ATTRIBUTE_DIRECTORY) == 0 && num_suffix)
			{
				WCHAR fn[17];
				int len_all = Len;
				int len = rt::min(16, len_all);
				memcpy(fn, &filename[len_all-len], sizeof(WCHAR)*(len+1));
				wcslwr(fn);
				for(int i=0; i<num_suffix; i++)
				{
					if(	len >= (int)suffix_w[i].GetLength() && 
						memcmp(suffix_w[i].Begin(), &fn[len-suffix_w[i].GetLength()], sizeof(WCHAR)*suffix_w[i].GetLength()) == 0
					)
					{	goto ExtFilterMatched;
					}
				}
				continue;
			}

ExtFilterMatched:
			
			Paths.push_back() = os::__UTF8(filename, Len);
			IsDir.push_back() = !!(fa&FILE_ATTRIBUTE_DIRECTORY);
		}

		if(Paths.GetSize() == 0)return 0;

		// probing longest common prefix
		UINT c=0;
		for(;;c++)
		{
			int tc = Paths[0][c];
			if(tc == 0)goto COMMON_PREFIX_END;
			for(UINT i=1;i<FileCount;i++)
				if(Paths[i][c] != tc)
					goto COMMON_PREFIX_END;
		}

COMMON_PREFIX_END:
		_Root = Paths[0].SubStr(0, c);

		for(UINT i=0;i<Paths.GetSize();i++)
		{
			if(IsDir[i] && (flag&FLAG_RECURSIVE))
			{	_Populate(Paths[i], sf, flag);
			}
			else
			{	_File& f = _Filenames.push_back();
				f.Name = Paths[i].TrimLeft(_Root.GetLength());
				f.IsDirectory = IsDir[i];
			}
		}

		return (UINT)_Filenames.GetSize();
	}
	else
	{	_Filenames.SetSize(0);
		return 0;
	}
}

#endif


UINT os::FileList::GetCount() const
{
	return (UINT)_Filenames.GetSize();
}

void os::FileList::Sort() {
	_Filenames.Sort();
}

const rt::String& os::FileList::GetFilename(UINT idx) const
{
	return _Filenames[idx].Name;
}

//void os::FileList::GetFilenameAndExt(UINT idx,rt::String& filename, rt::String& ext) const{
//	rt::String tmp(GetFilename(idx));
//	int idx1 = tmp.FindCharacterReverse('\\');
//	int idx2 = tmp.FindCharacterReverse('/');
//	int idx = rt::max(idx1,idx2);
//	if(idx!=-1)
//		tmp = rt::String(tmp.SubStr(idx+1));
//
//	int idx_dot = tmp.FindCharacterReverse('.');
//	if(idx_dot==-1 || idx_dot==0 || idx_dot==tmp.GetLength()-1){
//		filename = tmp;
//		ext = rt::String("");
//	}else{
//		filename = tmp.SubStr(0,idx_dot);
//		ext = tmp.SubStr(idx_dot+1);
//	}
//}

void os::FileList::GetFullpath(UINT idx, rt::String& fn) const
{
	if(_Root.IsEmpty())
		fn = _Filenames[idx].Name;
	else
		fn = _Root + _Filenames[idx].Name;
}

bool os::FileList::IsDirectory(UINT idx) const
{
	return _Filenames[idx].IsDirectory;
}

void os::FileList::AddFile(const rt::String_Ref& fn, bool IsDir)
{
	_File& f = _Filenames.push_back();
	f.Name = fn;
	f.IsDirectory = IsDir;
}

////////////////////////////////
// FileReadLine
os::FileReadLine::FileReadLine()
{
	VERIFY(_buf.SetSize(FRL_BUFSIZE));
	_bufused = 0;
	_lastpos = 0;
#if defined(PLATFORM_WIN)
	_hFile = INVALID_HANDLE_VALUE;
#endif
}

void os::FileReadLine::Close()
{
#if defined(PLATFORM_WIN)
	if (_hFile != INVALID_HANDLE_VALUE)
	{
		::CloseHandle(_hFile);
		_hFile = INVALID_HANDLE_VALUE;
	}
#else
	_file.Close();
#endif
}

ULONGLONG os::FileReadLine::GetSize() const 
{
#if defined(PLATFORM_WIN)
	LARGE_INTEGER	i;
	::GetFileSizeEx(_hFile, &i);
	return i.QuadPart;
#else
	return _file.GetFileSize();
#endif
}
	
bool os::FileReadLine::Open(LPCSTR fn)
{
	_filename = fn;

	_bufused = 0;
	_lastpos = 0;
#if defined(PLATFORM_WIN)
	if(_hFile != INVALID_HANDLE_VALUE)::CloseHandle(_hFile);
	_hFile = ::CreateFileW(__UTF16(fn), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if(_hFile == INVALID_HANDLE_VALUE)return false;
#else
	_file.Close();
	if(!_file.Open(fn))return false;
#endif

	return true;
}

bool os::FileReadLine::ReadBlock(LPCVOID& p, UINT size)
{
	if(p < _buf.Begin() || p >= _buf.End())	
	{	
#if defined(PLATFORM_WIN)
		LARGE_INTEGER	i;
		i.QuadPart = 0;
		if(::SetFilePointerEx(_hFile, i, NULL, FILE_BEGIN))
			::ReadFile(_hFile, _buf, FRL_BUFSIZE, (LPDWORD)&_bufused,NULL);
#else
		VERIFY(0 == _file.Seek(0));
		_bufused = (UINT)_file.Read(_buf, FRL_BUFSIZE);
#endif
		if(_bufused < size)return false;
		_lastpos = 0;

		p = _buf.Begin();
		return true;
	}
	else
	{	
		if(p > _buf.Begin() + _bufused - size*2)
		{
			int removed = (int)((char*)p - _buf.Begin()) + size;
			memmove(_buf.Begin(), (char*)p + size, _bufused - removed);
			p = _buf.Begin();
			_bufused -= removed;
			_lastpos += removed;
#if defined(PLATFORM_WIN)
			DWORD read = 0;
			::ReadFile(_hFile, _buf.Begin() + _bufused, FRL_BUFSIZE - _bufused, &read, NULL);
			_bufused += read;
#else
			_bufused += _file.Read(_buf.Begin() + _bufused, FRL_BUFSIZE - _bufused);
#endif
			return _bufused >= size;
		}
	}

	if(p <= _buf.Begin() + _bufused - size)
	{
		p = (char*)p + size;
		return true;
	}
	
	return false;
}


bool os::FileReadLine::GetNextLineWithQuote(rt::String_Ref& line, char quote)
{
	if(line.Begin() < _buf.Begin() || line.Begin() >= _buf.End())	
	{	
#if defined(PLATFORM_WIN)
		LARGE_INTEGER	i;
		i.QuadPart = 0;
		if(::SetFilePointerEx(_hFile, i, NULL, FILE_BEGIN))
			::ReadFile(_hFile, _buf, FRL_BUFSIZE, (LPDWORD)&_bufused,NULL);
#else
		VERIFY(0 == _file.Seek(0));
		_bufused = (UINT)_file.Read(_buf, FRL_BUFSIZE);
#endif
		if(_bufused == 0)return false;
		_lastpos = 0;
		// skip UFT8 sign
		if(_buf[0] == '\xEF' && _buf[1] == '\xBB' && _buf[2] == '\xBF')
		{
			if(quote)
				return rt::String_Ref(_buf+3, _bufused-3).GetNextLineWithQuote(line, true, quote);
			else
				return rt::String_Ref(_buf+3, _bufused-3).GetNextLine(line);

			return true;
		}
	}
	else
	{	
		if(line.Begin() > _buf.Begin() + FRL_BUFSIZE/2)
		{	
			int removed = (int)(line.Begin() - _buf.Begin());
			memmove(_buf.Begin(), line.Begin(), _buf.Begin() + _bufused - line.Begin());
			line._p = _buf.Begin();
			_bufused -= removed;
			_lastpos += removed;
#if defined(PLATFORM_WIN)
			DWORD read = 0;
			::ReadFile(_hFile, _buf.Begin() + _bufused, FRL_BUFSIZE - _bufused, &read, NULL);
			_bufused += read;
#else
			_bufused += _file.Read(_buf.Begin() + _bufused, FRL_BUFSIZE - _bufused);
#endif
		}
	}

	if(quote)
		return rt::String_Ref(_buf, _bufused).GetNextLineWithQuote(line, true, quote);
	else
		return rt::String_Ref(_buf, _bufused).GetNextLine(line);
}

os::FileWrite::FileWrite()
{
	VERIFY(_WriteBuf.reserve(FRL_BUFSIZE));

#if defined(PLATFORM_WIN)
	_hFile = INVALID_HANDLE_VALUE;
	rt::Zero(_Overlapped);
#else
#endif
}

bool os::FileWrite::IsOpen() const
{
#if defined(PLATFORM_WIN)
	return _hFile != INVALID_HANDLE_VALUE;
#else
	return _File.IsOpen();
#endif
}

bool os::FileWrite::Open(LPCSTR fn, DWORD flag, UINT header_size)
{
	Close();
	
#if !defined(PLATFORM_WIN)
	if(flag&FW_ASYNC)
	{
		flag &= ~FW_ASYNC;
		_LOGC_WARNING("os::FileWrite don't support asynchronous I/O, fallback to blocking I/O.")
	}
#endif		

	_bWritePending = false;
	if(flag&FW_ASYNC)
	{
		ASSERT(_WriteBuf.Begin());
		_WriteBuf_Back.reserve(FRL_BUFSIZE);
	}
	else
	{
		_WriteBuf_Back.SetSize(0);
		ASSERT(_WriteBuf_Back.Begin() == nullptr);
	}

	if(flag&FW_UTF8SIGN)
	{	_HeaderSize = 3U;
		ASSERT(0 == header_size);
	}
	else _HeaderSize = header_size;

	os::File::CreateDirectories(fn);

#if defined(PLATFORM_WIN)
	_hFile = ::CreateFileW(__UTF16(fn), GENERIC_WRITE, FILE_SHARE_READ, NULL, (flag&FW_TRUNCATE)?CREATE_ALWAYS:OPEN_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN|((flag&FW_ASYNC)?FILE_FLAG_OVERLAPPED:0), NULL);
	if(_hFile != INVALID_HANDLE_VALUE)
	{
		if(_IsAsyncMode())
			VERIFY(_Overlapped.hEvent = ::CreateEvent(NULL, true, false, NULL));

		ULONGLONG zero = 0;
		LARGE_INTEGER pos;
		::SetFilePointerEx(_hFile, (LARGE_INTEGER&)zero, &pos, FILE_END);
		if(_HeaderSize > pos.QuadPart)
		{
			zero = _HeaderSize;
			::SetFilePointerEx(_hFile, (LARGE_INTEGER&)zero, &pos, FILE_BEGIN);
			ASSERT(pos.QuadPart == _HeaderSize);
			if(flag&FW_UTF8SIGN)WriteHeader("\xef\xbb\xbf", 3);
		}

		_Overlapped.Pointer = (PVOID&)pos;
		return true;
	}
#else
	if(_File.Open(fn, (flag&FW_TRUNCATE)?os::File::Normal_Write:os::File::Normal_Append))
	{
		ASSERT(!_IsAsyncMode());
		
		size_t pos = _File.SeekToEnd();
		if(_HeaderSize > pos)
		{
			_File.Truncate(_HeaderSize);
			_File.SeekToBegin();
			if(flag&FW_UTF8SIGN)WriteHeader("\xef\xbb\xbf", 3);
			_File.SeekToEnd();
		}
		
		return true;
	}
#endif

	Close();
	return false;
}

bool os::FileWrite::_FileWriteBuf()
{
	ASSERT(IsOpen());
#if defined(PLATFORM_WIN)
	if(_IsAsyncMode())
	{
		_FileWriteSync();
		ASSERT(_WriteBuf_Back.GetSize() == 0);
		if(!::WriteFile(_hFile, _WriteBuf.Begin(), (UINT)_WriteBuf.GetSize(), NULL, &_Overlapped) && ::GetLastError() == ERROR_IO_PENDING)
		{
			((SIZE_T&)_Overlapped.Pointer) += _WriteBuf.GetSize();
			rt::Swap(_WriteBuf_Back, _WriteBuf);
			_bWritePending = true;
			return true;
		}
	}
	else
	{	ASSERT(!_bWritePending);
		DWORD w;
		if(::WriteFile(_hFile, _WriteBuf.Begin(), (UINT)_WriteBuf.GetSize(), &w, NULL))
		{
			_WriteBuf.ChangeSize(0);
			return true;
		}
		return false;
	}
#else
	ASSERT(!_IsAsyncMode());
	if(write(_File.GetFD(), _WriteBuf.Begin(), (UINT)_WriteBuf.GetSize()) >= 0)
	{
		_WriteBuf.ChangeSize(0);
		return true;
	}
#endif

	return false;
}

void os::FileWrite::_FileWriteSync()
{
	ASSERT(IsOpen());
	if(!_bWritePending)return;

#if defined(PLATFORM_WIN)
	VERIFY(WAIT_OBJECT_0 == ::WaitForSingleObject(_Overlapped.hEvent, INFINITE));
	_WriteBuf_Back.ChangeSize(0);
	::ResetEvent(_Overlapped.hEvent);
#else
	ASSERT(0);
#endif

	_bWritePending = false;
}

void os::FileWrite::Close()
{
	if(!IsOpen())return;
	Flush();

#if defined(PLATFORM_WIN)
	if(_hFile != INVALID_HANDLE_VALUE)
	{	
		::CloseHandle(_hFile);
		_hFile = INVALID_HANDLE_VALUE;
	}
	if(_Overlapped.hEvent)
	{	
		_bWritePending = false;
		::CloseHandle(_Overlapped.hEvent);
		_Overlapped.hEvent = NULL;
	}
#else
	_File.Close();
#endif
}

bool os::FileWrite::Flush()
{
	if(!_FileWriteBuf())return false;
	_FileWriteSync();

#if defined(PLATFORM_WIN)
	::FlushFileBuffers(_hFile);
#else
	_File.Flush();
#endif

	return true;
}

bool os::FileWrite::WriteHeader(LPCVOID p, UINT size)
{
	ASSERT(_HeaderSize == size);
#if defined(PLATFORM_WIN)
	if(_IsAsyncMode())
	{
		_FileWriteSync();
		OVERLAPPED op = _Overlapped;
		op.Pointer = 0;
		if(!::WriteFile(_hFile, p,  size, NULL, &op) && ::GetLastError() == ERROR_IO_PENDING)
		{
			_bWritePending = true;
			_FileWriteSync();
			return true;
		}
		
		return false;
	}
	else
	{
		DWORD w;
		LARGE_INTEGER zero;
		zero.QuadPart = 0;
		return	::SetFilePointerEx(_hFile, zero, NULL, FILE_BEGIN) &&
				::WriteFile(_hFile, p,  size, &w, NULL) &&
				::SetFilePointerEx(_hFile, zero, NULL, FILE_END);
	}
#else
	ASSERT(!_IsAsyncMode());
	_File.SeekToBegin();
	bool ret = write(_File.GetFD(), p,  size) == size;
	_File.SeekToEnd();
	return ret;
#endif
}


////////////////////////////////
// Cmdline parser
namespace os
{
	namespace _details
	{
		os::CommandLine* __FirstParsedCommandLine = nullptr;
	}
}

os::CommandLine::~CommandLine()
{
	if(_details::__FirstParsedCommandLine == this)
		_details::__FirstParsedCommandLine = nullptr;
}

void os::CommandLine::SetOptionInitial(LPCSTR opt_init)
{
	_OptionInitial.Init(opt_init, (UINT)strlen(opt_init));
}

#if defined(PLATFORM_WIN)

void os::CommandLine::Parse(int argc, WCHAR* argv[])	// for _tmain
{
	if(!_details::__FirstParsedCommandLine)
		_details::__FirstParsedCommandLine = this;

	LPSTR * s = (LPSTR *)alloca(sizeof(LPCSTR)*argc);
	__UTF8* p = (__UTF8*)alloca(sizeof(__UTF8)*argc);
	for(int i=0; i<argc; i++)
	{
		new (&p[i]) __UTF8(argv[i]);
		s[i] = p[i]._utf8.Begin();
	}

	Parse(argc, s);

	for(int i=0; i<argc; i++)
	{
		p[i].~__UTF8();
	}
}

void os::CommandLine::Parse(LPCWSTR pCmdLine)		// for _twmain
{
	Parse(__UTF8(pCmdLine));
}

#endif // defined(PLATFORM_WIN) && defined(UNICODE)

void os::CommandLine::Parse(int argc, char* argv[])	// for _tmain
{
	Empty();

	if(!_details::__FirstParsedCommandLine)
		_details::__FirstParsedCommandLine = this;

	_Parse(argc, argv);

	for(int i=1;i<argc;i++)
	{	
		_CommandLine += rt::String_Ref(argv[i]);
		if(i+1 < argc)_CommandLine += ' ';
	}
}

void os::CommandLine::_Parse(int argc, char* argv[])	// for _tmain
{
	ASSERT(argc>=0);
		
	for(int i=1;i<argc;i++)
	{	
		if(_OptionInitial.Has(argv[i][0]))
		{	// is option
			_opt& opt = _Options.push_back();
			LPCSTR optstr = argv[i] + 1;
			if(optstr[-1] == optstr[0])
				optstr++; // linux style cmdline option --xxxx

			rt::String_Ref seg(optstr); // = rt::String_Ref(optstr).TrimSpace();

			rt::String_Ref f[2];
			UINT co = seg.Split(f,2,":=");
			opt.Name = f[0];
			if(co>1)
			{
				if(f[1][0] == '"')
					opt.Value = rt::String_Ref(f[1].Begin() + 1, seg.End());
				else			
					opt.Value = rt::String_Ref(f[1].Begin(), seg.End()).RemoveCharacters('"').TrimSpace();
			}
		}
		else
		{	// is text
			_Arguments.push_back() = argv[i];
		}
	}
}

void os::CommandLine::ParseURI(const rt::String_Ref& path, const rt::String_Ref& query)
{
	Empty();

	_CommandLine = path;
	if(!query.IsEmpty())
	{	_CommandLine += '?';
		_CommandLine += query;
	}

	_ParseCompleteLine();
}

void os::CommandLine::Empty()
{
	_Arguments.SetSize();
	_Options.SetSize();
	_CommandLine.Empty();
}

void os::CommandLine::_ParseCompleteLine()
{
	rt::String	cmdline(_CommandLine);
	if(cmdline.IsEmpty())return;

	LPSTR pCmd = cmdline.Begin();

	rt::BufferEx<LPSTR>	argv;
	argv.push_back((LPSTR)nullptr);

	bool is_in_quotation = false;
	bool not_start = true;
	while(*pCmd)
	{	
		switch(*pCmd)
		{
		case ' ':
			if(!is_in_quotation){ *pCmd = 0; not_start = true; }
			break;
		case '\"':
			if(is_in_quotation)
			{
				*pCmd = 0;
				is_in_quotation = false;
			}
			else
			{
				is_in_quotation = true;
			}
			break;
		default:
			if(!not_start){}
			else{ argv.push_back(pCmd); not_start = false; }
		}

		pCmd++;
	}

	_Parse((int)argv.GetSize(),argv);
}

void os::CommandLine::Parse(LPCSTR pCmdLine)
{	
	Empty();
	_CommandLine = rt::String_Ref(pCmdLine).TrimSpace();
	_ParseCompleteLine();
}

void os::CommandLine::SubstituteOptions(rt::String& string, const rt::String_Ref& prefix, const rt::String_Ref& suffix) const
{
	rt::String tag;
	for(UINT i=0;i<_Options.GetSize();i++)
	{	
		tag = prefix + _Options[i].Name + suffix;
		string.Replace(tag, _Options[i].Value);
	}	
}

const os::CommandLine& os::CommandLine::Get()
{
	static const os::CommandLine _;
	return _details::__FirstParsedCommandLine?*_details::__FirstParsedCommandLine:_;
}

os::CommandLine& os::CommandLine::GetMutable()
{
	ASSERT(_details::__FirstParsedCommandLine);
	return *_details::__FirstParsedCommandLine;
}

bool os::CommandLine::HasOption(const rt::String_Ref& option_name) const
{
	rt::String_Ref opts[16];
	UINT opt_co = option_name.Split(opts, sizeofArray(opts), "|,;/");

	for(UINT i=0;i<_Options.GetSize();i++)
	{	
		for(UINT j=0; j<opt_co; j++)
			if(opts[j] == _Options[i].Name)
				return true;
	}
	return false;
}

void os::CommandLine::RemoveOption(const rt::String_Ref& option_name)
{
	for(UINT i=0;i<_Options.GetSize();i++)
	{	
		if(option_name == _Options[i].Name)
			_Options.erase(i);
	}
}

void os::CommandLine::AppendText(const rt::String_Ref& arg)
{
	_Arguments.push_back() = arg;
}

rt::String_Ref os::CommandLine::GetSeparatorIgnoredOption(const rt::String_Ref& option_name) const
{
	rt::String_Ref opts[16];
	UINT opt_co = option_name.Split(opts, sizeofArray(opts), "|,;/");

	for(UINT i=0; i<opt_co; i++)
	{
		auto s = rt::SS("/") + opts[i] + ':';
		auto* str = ALLOCA_C_STRING(s);

		auto pos = _CommandLine.FindString(str);
		if(pos >= 0)
			return _CommandLine.SubStr(pos + 2 + opts[i].GetLength());
	}
	
	return nullptr;
}

LPCSTR os::CommandLine::SearchOptionEx(const rt::String_Ref& option_substring) const
{	
	for(UINT i=0;i<_Options.GetSize();i++)
	{	
		if(_Options[i].Name == option_substring)
		{
			return _Options[i].Value;
		}
	}
	return nullptr;
}

rt::String_Ref os::CommandLine::GetOption(const rt::String_Ref& option_name, const rt::String_Ref& def_val) const
{
	rt::String_Ref opts[16];
	UINT opt_co = option_name.Split(opts, sizeofArray(opts), "|,;/");

	for(UINT i=0;i<_Options.GetSize();i++)
	{	
		for(UINT j=0; j<opt_co; j++)
			if(_Options[i].Name == opts[j])
			{
				if(_Options[i].Value.IsEmpty())return def_val;
				return _Options[i].Value;
			}
	}
	return def_val;
}

void os::CommandLine::SecureClear()
{
	for(UINT i=0; i<_Arguments.GetSize(); i++)
		_Arguments[i].SecureEmpty();
	_Arguments.SetSize();

	for(UINT i=0; i<_Options.GetSize(); i++)
	{	_Options[i].Value.SecureEmpty();
		_Options[i].Name.SecureEmpty();
	}
	_Options.SetSize();
}

void os::CommandLine::LoadEnvironmentVariablesAsOptions()
{
#if defined(PLATFORM_WIN)
	LPWCH pCH = GetEnvironmentStringsW();
	while(*pCH)
	{
		int size = (int)wcslen(pCH);
		os::__UTF8 utf8(pCH, size);
		rt::String_Ref f[2];
		if(utf8.Split(f,2,'=') == 1)
		{	SetOptionDefault(f[0], nullptr);
		}
		else
		{	SetOptionDefault(f[0], rt::String_Ref(f[1].Begin(), utf8.End()));
		}
		pCH += size+1;
	}
#elif defined(PLATFORM_MAC) || defined(PLATFORM_IOS)
	_LOG_WARNING("LoadEnvironmentVariablesAsOptions on Mac/iOS is not implemented");
#else
	for(int i=0; environ[i]; i++)
	{	
		rt::String_Ref variable(environ[i]);
		rt::String_Ref f[2];
		if(variable.Split(f,2,'=') == 1)
		{	SetOptionDefault(f[0], nullptr);
		}
		else
		{	SetOptionDefault(f[0], rt::String_Ref(f[1].Begin(), variable.End()));
		}
	}
#endif
}


void os::CommandLine::SetOptionDefault(const rt::String_Ref& opt_name, const rt::String_Ref& value)
{
	if(!HasOption(opt_name))
	{	
		_opt& opt = _Options.push_back();
		opt.Name = opt_name;
		opt.Value = value;
	}
}

void os::CommandLine::SetOption(const rt::String_Ref& opt_name, const rt::String_Ref& value)
{
	for(UINT i=0;i<_Options.GetSize();i++)
	{	
		if(_Options[i].Name == opt_name)
		{	_Options[i].Value = value;
			return;
		}
	}
	
	_opt& n = _Options.push_back();
	n.Name = opt_name;
	n.Value = value;
}

bool os::Process::WaitForEnding(DWORD timeout) // return false when timeout
{
	os::TickCount	t;
	t.LoadCurrentTick();

	while(IsRunning())
	{	os::Sleep(500);
		if(	timeout != INFINITE &&
			(DWORD)t.TimeLapse()>timeout
		)return false;
	}

	return true;
}

os::Process::Process()
{
	_ExecutionTime = 0;
#if defined(PLATFORM_WIN)
	_hProcess = INVALID_HANDLE_VALUE;
#else
#endif
}

bool os::Process::Launch(LPCSTR cmdline, LPCSTR pWorkDirectory, LPVOID pEnvVariable)
{
	VERIFY(!IsRunning());
	if(rt::String_Ref(cmdline).IsEmpty())return false;

#if defined(PLATFORM_WIN)
	PROCESS_INFORMATION piProcInfo;
	STARTUPINFOW siStartInfo;

	rt::Zero( &piProcInfo, sizeof(PROCESS_INFORMATION) );
	rt::Zero( &siStartInfo, sizeof(STARTUPINFO) );
	siStartInfo.cb = sizeof(STARTUPINFO);
	siStartInfo.dwFlags = 0;

	_ExitCode = STILL_ACTIVE;
	// Create the child process. 
	bool ret;
	ret = CreateProcessW(	NULL, 
							(LPWSTR)(LPCWSTR)__UTF16(cmdline),	// command line 
							NULL,				// process security attributes 
							NULL,				// primary thread security attributes 
							true,				// handles are inherited 
							0,					// creation flags 
							pEnvVariable,
							__UTF16(pWorkDirectory),	
							&siStartInfo,		// STARTUPINFO pointer 
							&piProcInfo);		// receives PROCESS_INFORMATION 

	if(ret)
	{	::SetPriorityClass(GetCurrentProcess(),ABOVE_NORMAL_PRIORITY_CLASS);

		_hProcess = piProcInfo.hProcess;
		CloseHandle( piProcInfo.hThread );
		return true;
	}
#else
#endif

	return false;
}

void os::Process::Terminate()
{
	if(IsRunning())
	{
#if defined(PLATFORM_WIN)
		::TerminateProcess(_hProcess,-1);
#else
#endif
		IsRunning();
	}
}

bool os::Process::IsRunning()
{
#if defined(PLATFORM_WIN)
	if(_hProcess!=INVALID_HANDLE_VALUE)
	{
		bool exited = false;
		VERIFY(::GetExitCodeProcess(_hProcess,(LPDWORD)&_ExitCode));
		exited = (_ExitCode!=STILL_ACTIVE);

		if(exited)
		{	
			FILETIME creat,exit,foo;
			GetProcessTimes(_hProcess,&creat,&exit,&foo,&foo);
			_ExitTime = (*((__time64_t*)&exit))/10000LL - 11644473600000LL;
			_ExecutionTime = (UINT)((((ULONGLONG&)exit) - ((ULONGLONG&)creat))/10000);

			return false;
		}
		return true;
	}
#else
#endif
	return false;
}

// FolderChangingMonitor
#if defined(PLATFORM_WIN)

bool os::FolderChangingMonitor::IsStarted()
{
	return _WorkingThread != NULL;
}

os::FolderChangingMonitor::FolderChangingMonitor()
{	
	_WaitingHandle = INVALID_HANDLE_VALUE; 
	_WorkingThread = NULL;
	_CoalescingInterval = 0;
}

DWORD WINAPI os::FolderChangingMonitor::_WorkingThreadFunc(LPVOID p)
{	
	ASSERT(p);
	FolderChangingMonitor* This  = ((FolderChangingMonitor*)p);
	for(;;)
	{	DWORD ret;
		ret = WaitForSingleObject(This->_WaitingHandle,INFINITE);
		VERIFY(FindNextChangeNotification(This->_WaitingHandle));
		if(ret == WAIT_OBJECT_0)
		{
			if(This->_CoalescingInterval)
			{	os::TickCount tick;
				tick.LoadCurrentTick();
				while(tick.TimeLapse() <= This->_CoalescingInterval)
				{
					ret = WaitForSingleObject(This->_WaitingHandle,rt::min(200, This->_CoalescingInterval));
					if(ret == WAIT_OBJECT_0)
					{	VERIFY(FindNextChangeNotification(This->_WaitingHandle));
					}
					else break;
				}
			}
			This->OnFolderChanged();
		}
	}
}

bool os::FolderChangingMonitor::Create(LPCSTR Folder,bool IncludeSubTree, DWORD filter)
{
	ASSERT(_WaitingHandle == INVALID_HANDLE_VALUE);

	_WaitingHandle = FindFirstChangeNotificationW(__UTF16(Folder),IncludeSubTree,filter);
	if(_WaitingHandle != INVALID_HANDLE_VALUE)
	{
		_WorkingThread = ::CreateThread(NULL,0,_WorkingThreadFunc,this,0,NULL);
		::SetThreadPriority(_WorkingThread,THREAD_PRIORITY_ABOVE_NORMAL);
		ASSERT( _WorkingThread );
		return true;
	}
	return false;
}

void os::FolderChangingMonitor::Destroy()
{
	if( _WorkingThread )
	{	::TerminateThread(_WorkingThread,0);
		_WorkingThread = NULL;
	}
	if( _WaitingHandle != INVALID_HANDLE_VALUE )
	{	FindCloseChangeNotification(_WaitingHandle);
		_WaitingHandle = INVALID_HANDLE_VALUE;
	}
}

#else
#endif


#if defined(PLATFORM_WIN)

os::FileMapping::FileMapping()
{
	_hFile = INVALID_HANDLE_VALUE;
	_hFileMapping = NULL;
	_Ptr = nullptr;
	_Size = 0;
}

bool os::FileMapping::Open(LPCSTR filename, SIZE_T length, bool readonly, bool create_new)
{
	ASSERT(_hFile == INVALID_HANDLE_VALUE);
	ASSERT(_Ptr == nullptr);

	_Readonly = readonly;

	DWORD fprot;
	DWORD vfacc;
	if(readonly)
	{
		_hFile = ::CreateFileW(__UTF16(filename), GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
		fprot = PAGE_READONLY;
		vfacc = FILE_MAP_READ;
	}
	else
	{
		os::File::CreateDirectories(filename, true);
		if(create_new)os::File::Remove(filename);
		_hFile = ::CreateFileW(__UTF16(filename), GENERIC_WRITE|GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL);
		fprot = PAGE_READWRITE;
		vfacc = FILE_MAP_WRITE|FILE_MAP_READ;
	}

	if(INVALID_HANDLE_VALUE == _hFile)return false;

	LARGE_INTEGER sz;
	VERIFY(::GetFileSizeEx(_hFile, &sz));
	if(length == 0)
	{	length = (SIZE_T)(sz.QuadPart);
		if(length != sz.QuadPart)return false;
	}
	if(length == 0)return false;

	{	DWORD w = 0;
		if(!readonly && sz.QuadPart == 0)::WriteFile(_hFile, &w, 1, &w, NULL);	// avoid zero-sized file if write-able
	}

	DWORD highSize = 0;
	#if defined(PLATFORM_64BIT)
	highSize = (DWORD)(length>>32);
	#endif

	if(	(_hFileMapping = ::CreateFileMappingW(_hFile, NULL, fprot, highSize, (DWORD)length, NULL)) &&
		(_Ptr = ::MapViewOfFile(_hFileMapping, vfacc, 0, 0, length))
	)
	{	_Size = length;
		_Filename = filename;
		return true;
	}
	else
	{	Close();
		return false;
	}
}

void os::FileMapping::Close(bool also_delete_file)
{
	_Size = 0;
	if(_Ptr){ ::UnmapViewOfFile(_Ptr); _Ptr = nullptr; }
	if(_hFileMapping){ ::CloseHandle(_hFileMapping); _hFileMapping = NULL; }
	if(_hFile != INVALID_HANDLE_VALUE)
	{	
		::CloseHandle(_hFile);
		_hFile = INVALID_HANDLE_VALUE; 
	}
	if(also_delete_file && !_Filename.IsEmpty())os::File::Remove(_Filename);
	_Filename.Empty();
}

const rt::String& os::FileMapping::GetFilename() const
{
	return _Filename;
}

#else

os::FileMapping::FileMapping()
{
	_Ptr = nullptr;
	_Size = 0;
}


bool os::FileMapping::Open(LPCSTR filename, SIZE_T length, bool readonly, bool create_new)
{
	ASSERT(!_File.IsOpen());
	_Readonly = readonly;

	int prot;
	if(readonly)
	{
		if(!_File.Open(filename, File::Normal_Read))return false;
		prot = PROT_READ;
	}
	else
	{	if(!_File.Open(filename, File::Normal_ReadWrite))return false;
		prot = PROT_READ|PROT_WRITE;
	}

	SIZE_T fsz = _File.GetLength();
	if(length > fsz)
	{
		if(readonly || !create_new)return false;
		
		_File.SeekToEnd();
		
		rt::Buffer<BYTE>	block;
		VERIFY(block.SetSize(64*1024));
		block.Zero();
		for(SIZE_T i=fsz; i<length; i += block.GetSize())
		{
			UINT ws = (UINT)rt::min(block.GetSize(), length - i);
			_File.Write(block, ws);
		}
		fsz = _File.GetLength();
		if(length > fsz)return false;
	}
	length = fsz;

	if((_Ptr = mmap(NULL, length, prot, MAP_SHARED, _File.GetFD(), 0)))
	{	_Size = length;
		return true;
	}
	else
	{	Close();
		return false;
	}
}

void os::FileMapping::Close(bool also_delete_file)
{
	if(_Ptr){ ::munmap(_Ptr, _Size); _Ptr = nullptr; };
	_File.Close();
	_Size = 0;
	if(also_delete_file)os::File::Remove(_File.GetFilename().Begin());
}

const rt::String& os::FileMapping::GetFilename() const
{
	return _File.GetFilename();
}

#endif

#if defined(PLATFORM_WIN)
void os::Process::Populate(rt::Buffer<Info>& list_out)
{
	DWORD ids[2048];
	DWORD count;

	if(::EnumProcesses(ids, sizeof(ids), &count))
	{
		count /= sizeof(DWORD);

		list_out.SetSize(count);

		for(UINT i=0;i<count;i++)
		{
			list_out[i].PID = ids[i];
			list_out[i].StartTime = 0;

			HANDLE hp = ::OpenProcess(PROCESS_QUERY_INFORMATION, false, ids[i]);
			if(hp==NULL)hp = ::OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, false, ids[i]);
			if(hp)
			{
				FILETIME start_time, foo;
				::GetProcessTimes(hp, &start_time, &foo, &foo, &foo);
				list_out[i].StartTime = (*((__time64_t*)&start_time))/10000LL - 11644473600000LL;

				WCHAR base_name[MAX_PATH];
				DWORD len = MAX_PATH;
#ifdef PLATFORM_MAX_COMPATIBILITY
				if(::GetProcessImageFileNameW(hp, base_name, len))
#else
				if(::QueryFullProcessImageNameW(hp, 0, base_name, &len))
#endif
					list_out[i].Name = os::__UTF8(base_name);
			}
		}
	}
}

UINT os::Process::CurrentId()
{
	return ::GetCurrentProcessId();
}

UINT os::Process::CurrentParentId()
{
	UINT pid = CurrentId();
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32W procentry;
	procentry.dwSize = sizeof(PROCESSENTRY32);
	bool bContinue = Process32FirstW(hSnapShot, &procentry);
    while( bContinue )
    {
	   if(pid == procentry.th32ProcessID)
	   {
		   ::CloseHandle(hSnapShot);
		   return procentry.th32ParentProcessID;
	   }

       procentry.dwSize = sizeof(PROCESSENTRY32) ;
       bContinue = Process32NextW(hSnapShot, &procentry);
    }//while ends

	::CloseHandle(hSnapShot);
	return 0;
}

bool os::Process::IsRunning(UINT pid)
{
	DWORD ids[2048];
	DWORD count;

	if(::EnumProcesses(ids, sizeof(ids), &count))
	{
		for(UINT i=0; i<count; i++)
			if(pid == ids[i])return true;
	}

	return false;
}


bool os::Process::Search(Info& list_out, const rt::String_Ref& process_substr)
{
	DWORD ids[2048];
	DWORD count;
	INT self = os::GetProcessId();

	os::__UTF16 pn(process_substr);

	if(::EnumProcesses(ids, sizeof(ids), &count))
	{
		count /= sizeof(DWORD);

		for(UINT i=0;i<count;i++)
		{
			if(self == ids[i])continue;

			HANDLE hp = ::OpenProcess(PROCESS_QUERY_INFORMATION, false, ids[i]);
			if(hp==NULL)hp = ::OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, false, ids[i]);
			if(hp)
			{
				WCHAR base_name[MAX_PATH];
				DWORD len = MAX_PATH;
#ifdef PLATFORM_MAX_COMPATIBILITY
				if(::GetProcessImageFileNameW(hp, base_name, len)
#else
				if(::QueryFullProcessImageNameW(hp, 0, base_name, &len)
#endif
					&& wcsstr(base_name, pn)
				)
				{	list_out.Name = os::__UTF8(base_name);
					FILETIME start_time, foo;
					::GetProcessTimes(hp, &start_time, &foo, &foo, &foo);
					list_out.StartTime = (*((__time64_t*)&start_time))/10000LL - 11644473600000LL;

					list_out.PID = ids[i];
					return true;
				}
			}
		}
	}

	return false;
}

void os::Process::Terminate(UINT pid)
{
	HANDLE h = ::OpenProcess(PROCESS_TERMINATE, false, pid);
	if(h != INVALID_HANDLE_VALUE)
	{
		::TerminateProcess(h, -1);
		::CloseHandle(h);
	}	
}


#elif defined(PLATFORM_IOS) || defined(PLATFORM_MAC)
void os::Process::Populate(rt::Buffer<Info>& list_out)
{
    int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0};
    size_t miblen = 4;
	UINT self = os::GetProcessId();
    
    size_t size = 0;
    int st = sysctl(mib, (u_int)miblen, NULL, &size, NULL, 0);
    
    if(st==0)
    {
        rt::Buffer<BYTE> buf;
        VERIFY(buf.SetSize((size_t)(size*1.25f)));
        
        struct kinfo_proc * process = (struct kinfo_proc *)buf.Begin();
        
        st = sysctl(mib, (u_int)miblen, process, &size, NULL, 0);
        
        UINT co = (UINT)(size/sizeof(kinfo_proc));
        list_out.SetSize(co);
        for(UINT i=0;i<co;i++)
        {
            if(self == process[i].kp_proc.p_pid)continue;

            list_out[i].Name = process[i].kp_proc.p_comm;
            list_out[i].StartTime._Timestamp =
                ((LONGLONG)process[i].kp_proc.p_un.__p_starttime.tv_sec)*1000LL +
                process[i].kp_proc.p_un.__p_starttime.tv_sec/1000;
            list_out[i].PID = (UINT)process[i].kp_proc.p_pid;
        }
    }
    else
        list_out.ShrinkSize(0);
}

bool os::Process::IsRunning(UINT pid)
{
    int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0};
    size_t miblen = 4;
	UINT self = os::GetProcessId();
    
    size_t size;
    int st = sysctl(mib, (u_int)miblen, NULL, &size, NULL, 0);
    if(st==0)
    {
        rt::Buffer<BYTE> buf;
        VERIFY(buf.SetSize((size_t)(size*1.25f)));
        
        struct kinfo_proc * process = (struct kinfo_proc *)buf.Begin();
        
        st = sysctl(mib, (u_int)miblen, process, &size, NULL, 0);
        
        UINT co = (UINT)(size/sizeof(kinfo_proc));
        for(UINT i=0;i<co;i++)
            if(process[i].kp_proc.p_pid == pid)return true;
    }
    
	return false;
}

bool os::Process::Search(Info& list_out, const rt::String_Ref& process_substr)
{
	rt::String pn = process_substr;

    int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0};
    size_t miblen = 4;
    
    size_t size;
    int st = sysctl(mib, (u_int)miblen, NULL, &size, NULL, 0);
    
    if(st==0)
    {
        rt::Buffer<BYTE> buf;
        VERIFY(buf.SetSize((size_t)(size*1.25f)));
        
        struct kinfo_proc * process = (struct kinfo_proc *)buf.Begin();
        
        st = sysctl(mib, (u_int)miblen, process, &size, NULL, 0);
        
        UINT co = (UINT)(size/sizeof(kinfo_proc));
        for(UINT i=0;i<co;i++)
        {
            if(strstr(process[i].kp_proc.p_comm, pn))
            {
                list_out.Name = process[i].kp_proc.p_comm;
                list_out.StartTime._Timestamp =
                    ((LONGLONG)process[i].kp_proc.p_un.__p_starttime.tv_sec)*1000LL +
                    process[i].kp_proc.p_un.__p_starttime.tv_sec/1000;
                list_out.PID = (UINT)process[i].kp_proc.p_pid;
                return true;
            }
        }
    }
	return false;
}

UINT os::Process::CurrentId()
{
	return getpid();
}

UINT os::Process::CurrentParentId()
{
	return getppid();
}

void os::Process::Terminate(UINT pid)
{
	kill(pid, 0);
}

#else
void os::Process::Populate(rt::Buffer<Info>& list_out)
{
	DIR* d = opendir("/proc");
	struct dirent * de;
	
	rt::BufferEx<int>	pids;
	
	while((de = readdir(d)) != 0){
		if(isdigit(de->d_name[0])){
			int pid = atoi(de->d_name);
			pids.push_back(pid);
		}
	}
	
	closedir(d);
	
	rt::String str;
	os::File::LoadText("/proc/uptime", str);
	
	float uptime;
	
	rt::String_Ref col[22];
	str.Split(col, 2, ' ');
	col[0].ToNumber(uptime);
	LONGLONG base = os::Timestamp::Get() - (LONGLONG)(uptime*1000 + 0.5f);
	
	int un = (int)sysconf(_SC_CLK_TCK);
	
	char path[100];
	list_out.SetSize(pids.GetSize());
	for(UINT i=0; i<pids.GetSize(); i++)
	{
		list_out[i].PID = pids[i];
		
		sprintf(path, "/proc/%d/cmdline", pids[i]);
		os::File::LoadText(path, list_out[i].Name);
		
		sprintf(path, "/proc/%d/stat", pids[i]);
		if(os::File::LoadText(path, str) && 22 == str.Split(col, 22, ' '))
		{	int starttime;
			col[21].ToNumber(starttime);
			starttime = starttime*1000/un;
			list_out[i].StartTime = base + starttime;
		}
		else list_out[i].StartTime = 0;
	}
}

bool os::Process::IsRunning(UINT pid_in)
{
	DIR* d = opendir("/proc");
	struct dirent * de;
	
	while((de = readdir(d)) != 0){
		if(isdigit(de->d_name[0])){
			uint32_t pid = atoi(de->d_name);
			if(pid == pid_in)
			{
				closedir(d);
				return true;
			}
		}
	}
	
	closedir(d);
	return false;
}

UINT os::Process::CurrentId()
{
	return getpid();
}

UINT os::Process::CurrentParentId()
{
	return getppid();
}

void os::Process::Terminate(UINT pid)
{
	kill(pid, 0);
}

#endif


#if defined(PLATFORM_WIN)

#pragma warning(disable: 4091) // warning C4091: 'typedef ': ignored on left of '' when no variable is declared (\windows kits\8.1\include\um\dbghelp.h(1544))
#include <DbgHelp.h>
#pragma comment(lib,"Dbghelp.lib")

namespace os
{
namespace _details
{
	static rt::String g_DumpFilename;
	static DWORD g_DumpFlag = 0;
	static FUNC_PostCrashDump g_PostCrashDump = nullptr;
	bool _WriteCrashDump(LPCSTR fn, PEXCEPTION_POINTERS ExceptionInfo, DWORD dump_flag)
	{
		HANDLE hFile;
		hFile = ::CreateFileW(__UTF16(fn),FILE_ALL_ACCESS,FILE_SHARE_DELETE|FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_ALWAYS,0,NULL);
		if(hFile != INVALID_HANDLE_VALUE)
		{
			bool ret;
			if(ExceptionInfo)
			{
				MINIDUMP_EXCEPTION_INFORMATION ei;
				ei.ThreadId = ::GetCurrentThreadId();
				ei.ExceptionPointers = ExceptionInfo;
				ei.ClientPointers = true;

				ret = MiniDumpWriteDump(::GetCurrentProcess(),::GetCurrentProcessId(),
										hFile,	(MINIDUMP_TYPE)(dump_flag),
										&ei,	NULL,	NULL);
			}
			else
			{
				ret = MiniDumpWriteDump(::GetCurrentProcess(),::GetCurrentProcessId(),
										hFile,	(MINIDUMP_TYPE)(dump_flag),
										NULL,	NULL,	NULL);
			}

			::CloseHandle(hFile);

			if(g_PostCrashDump)g_PostCrashDump(fn);

			return ret;
		}
		return false;
	}
	void _SetPostCrashDumpHook(_details::FUNC_PostCrashDump hook)
	{
		g_PostCrashDump = hook;
	}
}}

void os::EnableCrashDump(LPCSTR dump_filename, bool full_memory)
{
	if(dump_filename)
	{	os::_details::g_DumpFilename = rt::String_Ref(dump_filename) + '_' + rt::tos::Timestamp<true,true,'-','-'>(os::Timestamp::Get()) + ".dmp";
	}
	else
	{	os::_details::g_DumpFilename.Empty();
	}

	struct _expception_handler
	{	static LONG WINAPI handler(struct _EXCEPTION_POINTERS *ExceptionInfo)
		{	
			static bool bInHandler = false;

			if(!bInHandler)
			{	
				bInHandler = true;

				if(!os::_details::g_DumpFilename.IsEmpty())
				{
					_LOG("JP: I'm dead >_<, Start memory dump ...");
					os::_details::_WriteCrashDump(os::_details::g_DumpFilename, ExceptionInfo, os::_details::g_DumpFlag);
				}
				else
				{
					_LOG("JP: Process ID("<<os::GetProcessId()<<") is dead");
				}
			}
			return EXCEPTION_EXECUTE_HANDLER;
		}
	};

	os::_details::g_DumpFlag = MiniDumpNormal|MiniDumpWithHandleData|MiniDumpWithProcessThreadData;
	if(full_memory)os::_details::g_DumpFlag |= MiniDumpWithDataSegs|MiniDumpWithFullMemory;

	SetUnhandledExceptionFilter(_expception_handler::handler);
}
#endif //#if defined(PLATFORM_WIN)
