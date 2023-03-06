#pragma once
/**
 * @file high_level.h
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
#include "predefines.h"
#include "../rt/string_type.h"
#include "multi_thread.h"
#include "file_dir.h"

namespace os
{
	/** \defgroup high_dir high_dir
 * @ingroup os
 *  @{
 */
/**
 * @brief singleton
 * 
 */
class Daemon	
{
#if defined(PLATFORM_WIN)
	volatile LPVOID			_hServiceHandler;
	os::Thread				_DispatchThread;
#else
#endif

protected:
	static Daemon*			_pDaemon;
	rt::String				_DaemonName;
public:
	Daemon();
	~Daemon();
	bool	InitializeDaemonController(LPCSTR name);	///< NOT thread-safe
	void	ReportDaemonStatus(DWORD state = DAEMON_PAUSED);	///< SERVICE_PAUSED
	virtual void OnDaemonControl(DWORD dwControl){};			///< dwControl = SERVICE_CONTROL_STOP/SERVICE_CONTROL_SHUTDOWN/ ...
};


template<typename t_ActualWriter>
class ParallelWriter
{
protected:
	rt::Buffer<BYTE>	_WritePool;
	double				_AvgAttenuation;

protected:
	struct _Chunk
	{	UINT	size;		
		UINT	length;		///< INFINITE indicates the chunk is not finalized
		BYTE	data[1];	///< real size set is by SetLogEntrySize
		_Chunk*	GetNext(){ return (_Chunk*)(data + size); }
	};
	static const SIZE_T _ChunkHeaderSize = sizeof(UINT)*2;
	struct _WriteBuf
	{	LPBYTE			pBuf;
		volatile int	Used;
	};
	_WriteBuf			_WriteBuffers[2];

protected:
	_WriteBuf*			_FrontBuf;
	_WriteBuf*			_BackBuf;
	UINT				_WriteDownInterval;
	UINT				_WriteBufferSize;
	os::Thread			_WriteThread;

	void _WriteDownBackBuffer()
	{	_Chunk* p = (_Chunk*)_BackBuf->pBuf;
		int used = _BackBuf->Used;
		_Chunk* pend = (_Chunk*)(_BackBuf->pBuf + rt::min<int>(used,(int)(_WriteBufferSize - _ChunkHeaderSize)));
	
		for(;p<pend;p = p->GetNext())
		{	
			if(p->size)
			{	if(p->length==INFINITE){ stat_UnfinalizedChunk++; continue; }
				if(p->length>0)
					if(!((t_ActualWriter*)this)->Write(p->data,p->length))
						stat_FileError++;
			}
			else break;
		}
		((t_ActualWriter*)this)->Flush();

		// Use Rate
		{	int fr;
			if(_BackBuf->Used >= (int)_WriteBufferSize)
			{	fr = 100;	}
			else
			{	fr = 100*(_BackBuf->Used/1024)/(_WriteBufferSize/1024);	}

			if(stat_BufferUsagePeek)
			{
				if(fr > stat_BufferUsagePeek)stat_BufferUsagePeek = fr;
				stat_BufferUsageAvg = (int)(fr + _AvgAttenuation*(stat_BufferUsageAvg - fr) + 0.5);
			}
			else
			{	stat_BufferUsagePeek = fr;
				stat_BufferUsageAvg = fr;
			}
		}

		_BackBuf->Used = 0;
		rt::Zero(_BackBuf->pBuf,_WriteBufferSize);
	}

	void _WriteRoutine()
	{	int time_to_sleep = _WriteDownInterval;
		os::Timestamp tm;
        rt::String fn;

		int _last_claim = 0;
		os::Timestamp _last_cps;
		_last_cps.LoadCurrentTime();

		for(;;)
		{
			while(time_to_sleep > 300)
			{	os::Sleep(300);
				time_to_sleep -= 300;
				if(_WriteThread.WantExit())
					goto CLOSING_FILE;
			}

			ASSERT(time_to_sleep > 0);
			os::Sleep(time_to_sleep);

			tm.LoadCurrentTime();

			_WriteDownBackBuffer();
			rt::Swap(_BackBuf,_FrontBuf);

			{	float cps = (stat_TotalClaimed - _last_claim)*1000/(float)(_last_cps.TimeLapse(tm));
				if(stat_ClaimPerSecond<0)
					stat_ClaimPerSecond = cps;
				else stat_ClaimPerSecond = (stat_ClaimPerSecond*9 + cps)/10;

				_last_claim = stat_TotalClaimed;
				_last_cps = tm;
			}

			if(stat_ClaimFailure || stat_FinalizeFailure || stat_FileError || stat_UnfinalizedChunk)
				LogAlert();

			int time_used = (int)tm.TimeLapse();

			{	int IOUage;
				if(	time_used < (int)_WriteDownInterval )
					IOUage = 100*time_used/_WriteDownInterval;
				else
					IOUage = 100;

				if( stat_FileIOUsagePeek )
				{
					if(IOUage>stat_FileIOUsagePeek)stat_FileIOUsagePeek = IOUage;
					stat_FileIOUsageAvg = (int)(IOUage + _AvgAttenuation*(stat_FileIOUsageAvg - IOUage) + 0.5);
				}
				else
				{
					stat_FileIOUsagePeek = IOUage;
					stat_FileIOUsageAvg = IOUage;
				}
			}

			time_to_sleep = rt::min<int>(_WriteDownInterval, rt::max<int>(100, _WriteDownInterval - time_used));
		}	
CLOSING_FILE:
		_WriteDownBackBuffer();
		rt::Swap(_BackBuf,_FrontBuf);
		_WriteDownBackBuffer();
		((t_ActualWriter*)this)->Exit();
	}

public: // statistic
	int					stat_FileError;
	int					stat_UnfinalizedChunk;
	float				stat_ClaimPerSecond;
	int					stat_BufferUsageAvg;			///< percentage
	int					stat_BufferUsagePeek;			///< percentage
	int					stat_FileIOUsageAvg;			///< percentage
	int					stat_FileIOUsagePeek;			///< percentage
	volatile int		stat_TotalClaimed;
	volatile int		stat_ClaimFailure;
	volatile int		stat_FinalizeFailure;

public:
	ParallelWriter()
	{	_WriteDownInterval = 0;

		rt::Zero(_WriteBuffers,sizeof(_WriteBuffers));
		_FrontBuf = _WriteBuffers;
		_BackBuf = _FrontBuf + 1;

		stat_BufferUsagePeek = 0;
		stat_BufferUsageAvg = 0;
		stat_FileIOUsageAvg = 0;
		stat_FileIOUsagePeek = 0;

		SetWriteDownInterval(1000);
	}
	~ParallelWriter(){ Close(); }
	bool	Open(UINT buffer_size = 1024*1024)
	{	ASSERT(!_WriteThread.IsRunning());
		stat_ClaimPerSecond = -1;
		stat_BufferUsagePeek = 0;
		stat_BufferUsageAvg = 0;
		stat_FileError = 0;
		stat_UnfinalizedChunk = 0;
		stat_ClaimFailure = 0;
		stat_FinalizeFailure = 0;
		stat_FileIOUsageAvg = 0;			///< percentage
		stat_FileIOUsagePeek = 0;			///< percentage
		stat_TotalClaimed = 0;

		_WriteBufferSize = (buffer_size + 3) & 0xffffffffc;
		if(_WritePool.SetSize(2*_WriteBufferSize))
		{
			_FrontBuf->pBuf = _WritePool;
			_FrontBuf->Used = 0;
			_BackBuf->pBuf = &_WritePool[_WriteBufferSize];
			_BackBuf->Used = 0;

			struct _call
			{	static DWORD _func(LPVOID pThis)
				{	((ParallelWriter*)pThis)->_WriteRoutine();
					return 0;
				}
			};
			return _WriteThread.Create(_call::_func,this);
		}
		_WritePool.SetSize(0);
		return false;
	}
	void	Close()
	{	stat_ClaimPerSecond = -1;
		if(_WriteThread.IsRunning())
		{	_WriteThread.WantExit() = true;
			_WriteThread.WaitForEnding(1000, true);
		}
	}
	void	LogAlert()
	{	static const rt::SS precentage("% / ");
		_LOG_WARNING("ParallelFileWriter Alert"<<
						"\n - Total Claim      : "<<stat_TotalClaimed<<
						"\n - Claim Failure    : "<<stat_ClaimFailure<<
						"\n - Finalize Failure : "<<stat_FinalizeFailure<<
						"\n - Unfinalized      : "<<stat_UnfinalizedChunk<<
						"\n - File I/O Failure : "<<stat_FileError<<
						"\n - Buffer Load      : "<<stat_BufferUsageAvg<<precentage<<stat_BufferUsagePeek<<
						"%\n - File I/O Load    : "<<stat_FileIOUsageAvg<<precentage<<stat_FileIOUsagePeek<<'%'
		);
	}
	bool	IsOpen() const { return _WriteThread.IsRunning(); }
	UINT	GetWriteDownInterval() const { return _WriteDownInterval; }
	void	SetWriteDownInterval(UINT write_interval_msec)
	{	_WriteDownInterval = rt::max<UINT>(100,write_interval_msec);
		_AvgAttenuation = pow(0.64, write_interval_msec/1000.0);		///< Attenuate to 0.01 after 10 sec
		ASSERT_FLOAT(_AvgAttenuation);
	}
	UINT	GetBufferSize() const { return _WriteBufferSize; }

	INLFUNC LPSTR ClaimWriting(UINT size)
	{	ASSERT(size);
		_WriteBuf* buf = _FrontBuf;
        int chunk = os::AtomicAdd(size + _ChunkHeaderSize, &buf->Used) - (size + _ChunkHeaderSize);
		os::AtomicIncrement(&stat_TotalClaimed);
		if(chunk + (int)size + (int)_ChunkHeaderSize <= (int)_WriteBufferSize)
		{
			_Chunk* p = (_Chunk*)&buf->pBuf[chunk];
			p->size = size;
			p->length = INFINITE;
			return (LPSTR)p->data;
		}
		else
		{	// this may happen when the writer is much faster then the sync thread
			os::AtomicIncrement(&stat_ClaimFailure);
			return nullptr;
		}
	}

	INLFUNC void FinalizeWritten(LPSTR pBuf, UINT len)
	{	_Chunk* p = (_Chunk*)&pBuf[-((int)_ChunkHeaderSize)];

		if(	len <= p->size &&
			p->length == INFINITE && p->size < _WriteBufferSize)
		{	p->length = len;	}
		else 
			os::AtomicIncrement(&stat_FinalizeFailure);
			// This may happen when it takes too long time between a paired 
			// ClaimWriting/FinalizeWritten calling. e.g. longer than m_WriteDownInterval
			// other possiblity is the caller ruined the buffer (run down)  
	}
	/**
	 * @brief string expression or json definition
	 * 
	 * @tparam T 
	 * @param x 
	 * @return INLFUNC 
	 */
	template<class T>
	INLFUNC bool WriteString(const T& x)	
	{	
		UINT len = (UINT)x.GetLength();
		LPSTR p = ClaimWriting(len);
		if(p)
		{	VERIFY(len == x.CopyTo((char*)p));
			FinalizeWritten(p,len);
			return true;
		}else return false;
	}
	/**
	 * @brief string expression or json definition 
	 * 
	 * @tparam T 
	 * @param x 
	 * @return INLFUNC 
	 */
	template<class T>
	INLFUNC bool WriteLine(const T& x)	
	{
		UINT len = (UINT)x.GetLength();
		LPSTR p = ClaimWriting(len + 2);
		if(p)
		{	VERIFY(len == x.CopyTo((char*)p));
			*((WORD*)(p + len)) = 0x0a0d;	// "\r\n"
			FinalizeWritten(p,len+2);
			return true;
		}else return false;
	}
	INLFUNC bool WriteString(const rt::String_Ref& str){ ASSERT(str.GetLength()<INT_MAX); return Write(str.Begin(),(UINT)str.GetLength()); }
	INLFUNC bool Write(LPCVOID str, UINT len)
	{	
		LPSTR p = ClaimWriting(len);
		if(p)
		{	memcpy(p,str,len);
			FinalizeWritten(p,len);
			return true;
		}else return false;
	}
};

#ifndef PLATFORM_DISABLE_LOG
class ParallelLog
{
protected:
	struct LogE
	{	int  type;
		int  line;
		int  log_len;  ///< include terminate-zero
		int  filename_len;
		int  funcname_len;
		char text[1];
	};
	struct LogWriter
	{	void Flush(){};
		void Exit(){};
		bool Write(LPCVOID p, UINT size)
		{	const LogE& e = *((LogE*)p);
			os::_details::LogWriteDefault(e.text, &e.text[e.log_len], e.line, &e.text[e.log_len + e.filename_len], e.type, nullptr);
			return true;
		}
	};

	ParallelWriter<LogWriter>	_PW;

public:
	/**
	 * @brief When defining an instance of a class, the log will be recorded by ParalleLog by default
	 * @param writedown_interval Interval of writting down to file (at least 100)
	 * @param buffer_size 
	*/
	ParallelLog(UINT writedown_interval = 500, UINT buffer_size = 1024*1024)
	{	VERIFY(_PW.Open(buffer_size)); _PW.SetWriteDownInterval(writedown_interval);
		struct _call
		{	static void _log(LPCSTR log, LPCSTR file, int line_num, LPCSTR func, int type, LPVOID cookie)
			{	((ParallelLog*)cookie)->Write(log, file, line_num, func, type);
			}
		};
		os::_details::SetLogWriteFunction(_call::_log, this);
	}
	~ParallelLog(){ _PW.Close(); os::_details::SetLogWriteFunction(); }
	INLFUNC void Write(LPCSTR log, LPCSTR file, int line_num, LPCSTR func, int type)
	{	ASSERT(log && file && func);
		int log_len = (int)strlen(log)+1;
		int filename_len = (int)strlen(file)+1;
		int funcname_len = (int)strlen(func)+1;
		int tot_len = 5*sizeof(int) + log_len + filename_len + funcname_len;
		LogE* e = (LogE*)_PW.ClaimWriting(tot_len);
		if(e)
		{	e->filename_len = filename_len;
			e->funcname_len = funcname_len;
			e->line = line_num;
			e->log_len = log_len;
			e->type = type;
			memcpy(e->text, log, log_len);
			memcpy(e->text + log_len, file, filename_len);
			memcpy(e->text + log_len + filename_len, func, funcname_len);
		}
		_PW.FinalizeWritten((LPSTR)e, tot_len);
	}
};
#endif

class ParallelFileWriter
{
protected:
	rt::Buffer<BYTE>	_WritePool;
	os::File			_File;
	double				_AvgAttenuation;

public:
	typedef bool (*FUNC_FileWriter)(LPCVOID data, UINT len, os::File& file, LPVOID cookie);
	
protected:
	FUNC_FileWriter		_pFileWriterCB;
	LPVOID				_FileWriterCookie;
	bool				_FilenameByLocalTime;

	LPCSTR				_FileOpenFlag;
	rt::String			_FilenameTemplate;
	bool				_FilenameChanged;
	os::CriticalSection	_FilenameTemplateCS;

protected:
	struct _Chunk
	{	UINT	size;		
		UINT	length;		///< INFINITE indicates the chunk is not finalized
		BYTE	data[1];	///< real size set is by SetLogEntrySize
		_Chunk*	GetNext(){ return (_Chunk*)(data + size); }
	};
	static const SIZE_T _ChunkHeaderSize = sizeof(UINT)*2;
	struct _WriteBuf
	{	LPBYTE			pBuf;
		volatile int	Used;
	};
	_WriteBuf			_WriteBuffers[2];

protected:
	_WriteBuf*			_FrontBuf;
	_WriteBuf*			_BackBuf;
	UINT				_WriteDownInterval;
	UINT				_WriteBufferSize;
	os::Thread			_WriteThread;

	void				_WriteDownBackBuffer();
	void				_WriteRoutine();
	void				_RealizeFilename(rt::String& filename);

public: // statistic
	int					stat_FileError;
	int					stat_UnfinalizedChunk;
	float				stat_ClaimPerSecond;
	int					stat_BufferUsageAvg;			///< percentage
	int					stat_BufferUsagePeek;			///< percentage
	int					stat_FileIOUsageAvg;			///< percentage
	int					stat_FileIOUsagePeek;			///< percentage
	volatile int		stat_TotalClaimed;
	volatile int		stat_ClaimFailure;
	volatile int		stat_FinalizeFailure;

public:
	ParallelFileWriter();
	~ParallelFileWriter();
	static void RealizeFilename(const rt::String& file_template, const os::Timestamp::Fields& time_f, rt::String& filename);
	void	SetFileWritingCallback(FUNC_FileWriter cb, LPVOID cookie);
	bool	Open(LPCSTR filename, bool append_existing = true, UINT buffer_size = 1024*1024, bool filetime_by_localtime = false);  ///< filename may contain macros as %YEAR% %MONTH% %DAY% %HOUR% %MINUTE% %HALFHOUR% %QUARTER%
	void	Close();
	void	PreClose(); ///< call if you want ParallelFileWriter to close but will do something else before hanging on Close() or dtor
	void	LogAlert(); ///< Log ParallelFileWriter Alert to view failure rate.
	bool	IsOpen() const { return _File.IsOpen(); }
	void	SwitchTo(LPCSTR filename, bool no_wait);
	UINT	GetWriteDownInterval() const { return _WriteDownInterval; }
	/**
	 * @brief Set interval of writting down to file 
	 * @param write_interval_msec max(100,write_interval_msec)
	*/
	void	SetWriteDownInterval(UINT write_interval_msec);
	UINT	GetBufferSize() const { return _WriteBufferSize; }
	void	GetCurrentLogFilename(rt::String& filename);
	const rt::String& GetLogFilename() const { return _FilenameTemplate; }
	INLFUNC LPSTR ClaimWriting(UINT size)
	{	ASSERT(size);
		_WriteBuf* buf = _FrontBuf;
        int chunk = os::AtomicAdd(size + _ChunkHeaderSize, &buf->Used) - (size + _ChunkHeaderSize);
		os::AtomicIncrement(&stat_TotalClaimed);
		if(chunk + (int)size + _ChunkHeaderSize <= (int)_WriteBufferSize)
		{
			_Chunk* p = (_Chunk*)&buf->pBuf[chunk];
			p->size = size;
			p->length = INFINITE;
			return (LPSTR)p->data;
		}
		else
		{	// this may happen when the writer is much faster then the sync thread
			os::AtomicIncrement(&stat_ClaimFailure);
			return nullptr;
		}
	}

	INLFUNC void FinalizeWritten(LPSTR pBuf, UINT len)
	{	_Chunk* p = (_Chunk*)&pBuf[-((int)_ChunkHeaderSize)];

		if(	len <= p->size &&
			p->length == INFINITE && p->size < _WriteBufferSize)
		{	p->length = len;	}
		else 
			os::AtomicIncrement(&stat_FinalizeFailure);
			// This may happen when it takes too long time between a paired 
			// ClaimWriting/FinalizeWritten calling. e.g. longer than m_WriteDownInterval
			// other possiblity is the caller ruined the buffer (run down)  
	}
	/**
	 * @brief string expression or json definition 
	 * 
	 * @tparam T 
	 * @param x 
	 * @return INLFUNC 
	 */
	template<class T>
	INLFUNC bool WriteString(const T& x)	
	{	
		UINT len = (UINT)x.GetLength();
		LPSTR p = ClaimWriting(len);
		if(p)
		{	VERIFY(len == x.CopyTo((char*)p));
			FinalizeWritten(p,len);
			return true;
		}else return false;
	}
	/**
	 * @brief string expression or json definition
	 * 
	 * @tparam T 
	 * @param x 
	 * @return INLFUNC 
	 */
	template<class T>
	INLFUNC bool WriteLine(const T& x)
	{
		UINT len = (UINT)x.GetLength();
		LPSTR p = ClaimWriting(len + 2);
		if(p)
		{	VERIFY(len == x.CopyTo((char*)p));
			*((WORD*)(p + len)) = 0x0a0d;	// "\r\n"
			FinalizeWritten(p,len+2);
			return true;
		}else return false;
	}
	INLFUNC bool WriteString(const rt::String_Ref& str){ ASSERT(str.GetLength()<INT_MAX); return Write(str.Begin(),(UINT)str.GetLength()); }
	INLFUNC bool Write(LPCVOID str, UINT len)
	{	
		LPSTR p = ClaimWriting(len);
		if(p)
		{	memcpy(p,str,len);
			FinalizeWritten(p,len);
			return true;
		}else return false;
	}
};
/** @}*/
} // namespace os
/** @}*/