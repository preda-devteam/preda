#include "high_level.h"

namespace os
{


os::Daemon* os::Daemon::_pDaemon = nullptr;

os::Daemon::Daemon()
{
	ASSERT(_pDaemon == nullptr);
	_pDaemon = this;
#if defined(PLATFORM_WIN)
	_hServiceHandler = NULL;
#else
#endif
}

os::Daemon::~Daemon()
{
	ASSERT(_pDaemon);
	_pDaemon = nullptr;
}

#if defined(PLATFORM_WIN)

bool os::Daemon::InitializeDaemonController(LPCSTR svc_name)
{
	ASSERT(_hServiceHandler == 0);
	_DaemonName = svc_name;
	
	struct _Func
	{	
		static VOID WINAPI OnServiceManagerControl(DWORD fdwControl)
		{
			switch(fdwControl)
			{
				case SERVICE_CONTROL_CONTINUE: _pDaemon->OnDaemonControl(DAEMON_CONTROL_CONTINUE); break;
				case SERVICE_CONTROL_PAUSE: _pDaemon->OnDaemonControl(DAEMON_CONTROL_PAUSE); break;
				case SERVICE_CONTROL_SHUTDOWN: 
				case SERVICE_CONTROL_STOP:	_pDaemon->OnDaemonControl(DAEMON_CONTROL_STOP); break;
			}
		}
		static VOID WINAPI SvcMain(DWORD dwArgc,LPSTR* lpszArgv)
		{
			_pDaemon->_hServiceHandler = ::RegisterServiceCtrlHandlerA(_pDaemon->_DaemonName,OnServiceManagerControl);
		}
		static DWORD Dispatcher(LPVOID)
		{
			SERVICE_TABLE_ENTRYA svc_tab[] = 
			{	{_pDaemon->_DaemonName,_Func::SvcMain},
				{nullptr, nullptr}
			};
			
			::StartServiceCtrlDispatcherA(svc_tab);
			return 0;
		}
	};

	// start dispatch thread
	_DispatchThread.Create(_Func::Dispatcher,0);
	Sleep(10);
	while(_hServiceHandler == NULL)
	{	
		if(_DispatchThread.WaitForEnding(200))
		{	//ASSERT(0); // StartServiceCtrlDispatcher failed
			return false;
		}
	}
	Sleep(0);

	ReportDaemonStatus(SERVICE_START_PENDING);
	return _hServiceHandler != 0;
}

void os::Daemon::ReportDaemonStatus(DWORD state)
{
	if(_hServiceHandler)
	{	
		SERVICE_STATUS SvcStatus;

		static DWORD dwCheckPoint = 1;

		SvcStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS;
		SvcStatus.dwCurrentState = state;
		SvcStatus.dwWin32ExitCode = NO_ERROR;
		SvcStatus.dwServiceSpecificExitCode = NO_ERROR;
		SvcStatus.dwWaitHint = 0;

		switch(state)
		{
		case SERVICE_START_PENDING:
		case SERVICE_CONTINUE_PENDING:
		case SERVICE_PAUSE_PENDING:
		case SERVICE_STOPPED:
			SvcStatus.dwControlsAccepted = 0;
			break;
		case SERVICE_PAUSED:
		case SERVICE_RUNNING:
			SvcStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;//|SERVICE_ACCEPT_PAUSE_CONTINUE;
			break;
		default:
			SvcStatus.dwControlsAccepted = 0;
		}

		if ( (state == SERVICE_RUNNING) || (state == SERVICE_STOPPED) )
			SvcStatus.dwCheckPoint = 0;
		else
			SvcStatus.dwCheckPoint = dwCheckPoint++;

		VERIFY(::SetServiceStatus((SERVICE_STATUS_HANDLE)_hServiceHandler,&SvcStatus));
	}
}

#endif



/////////////////////////////////////////////////
// CParallelFileWriter

ParallelFileWriter::ParallelFileWriter()
{
	_FilenameByLocalTime = false;
	_WriteDownInterval = 0;

	rt::Zero(_WriteBuffers,sizeof(_WriteBuffers));
	_FrontBuf = _WriteBuffers;
	_BackBuf = _FrontBuf + 1;

	//rt::Zero(_InMemoryCopy,sizeof(_InMemoryCopy));
	//_InMemoryCopy_FrontBuf = _InMemoryCopy;
	//_InMemoryCopy_BackBuf = _InMemoryCopy_FrontBuf + 1;

	stat_BufferUsagePeek = 0;
	stat_BufferUsageAvg = 0;
	stat_FileIOUsageAvg = 0;
	stat_FileIOUsagePeek = 0;

	SetWriteDownInterval(1000);

	_pFileWriterCB = nullptr;

	//_DesiredFileLength = 0;
	//SetTruncationBoundaryTag('\n',1);
}

ParallelFileWriter::~ParallelFileWriter()
{
	Close();
}

void ParallelFileWriter::SwitchTo(LPCSTR filename, bool no_wait)
{
	ASSERT(_File.IsOpen() && _WriteThread.IsRunning());

	EnterCSBlock(_FilenameTemplateCS);
	_FilenameTemplate = filename;
	_FilenameChanged = true;

	if(!no_wait)
	{	while(_FilenameChanged)
			os::Sleep(100);
	}
}

void ParallelFileWriter::SetWriteDownInterval(UINT sync_interval)
{
	_WriteDownInterval = rt::max<UINT>(100,sync_interval);
	_AvgAttenuation = pow(0.64, sync_interval/1000.0);		// Attenuate to 0.01 after 10 sec
	ASSERT_FLOAT(_AvgAttenuation);
}

void ParallelFileWriter::RealizeFilename(const rt::String& file_template, const os::Timestamp::Fields& f, rt::String& filename)
{
	if(file_template.FindCharacter('%')>=0)
	{
		file_template.ReplaceTo("%YEAR%", rt::tos::Number(f.Year), filename);
		filename.Replace("%MONTH%", rt::tos::Number(f.Month).RightAlign(2,'0'));
		filename.Replace("%DAY%", rt::tos::Number(f.Day).RightAlign(2,'0'));
		filename.Replace("%HOUR%", rt::tos::Number(f.Hour).RightAlign(2,'0'));
		filename.Replace("%HALFHOUR%", rt::tos::Number(f.Minute/30*30).RightAlign(2,'0'));
		filename.Replace("%QUARTER%", rt::tos::Number(f.Minute/15*15).RightAlign(2,'0'));
		filename.Replace("%MINUTE%", rt::tos::Number(f.Minute).RightAlign(2,'0'));
	}
	else
	{	filename = file_template;
	}

}

void ParallelFileWriter::_RealizeFilename(rt::String& filename)
{
	os::Timestamp::Fields f;
	if(_FilenameByLocalTime)
		os::Timestamp::Get().GetLocalDateTime(f);
	else
		os::Timestamp::Get().GetDateTime(f);

	RealizeFilename(_FilenameTemplate, f, filename);
}

bool ParallelFileWriter::Open(LPCSTR filename, bool append_existing, UINT buffer_size, bool filetime_by_localtime)
{
	EnterCSBlock(_FilenameTemplateCS);
	ASSERT(!_File.IsOpen() && !_WriteThread.IsRunning());

	_FilenameByLocalTime = filetime_by_localtime;
	_FilenameTemplate = filename;
	_FilenameChanged = false;

	stat_ClaimPerSecond = -1;
	stat_BufferUsagePeek = 0;
	stat_BufferUsageAvg = 0;
	stat_FileError = 0;
	stat_UnfinalizedChunk = 0;
	stat_ClaimFailure = 0;
	stat_FinalizeFailure = 0;
	stat_FileIOUsageAvg = 0;			// percentage
	stat_FileIOUsagePeek = 0;			// percentage
	stat_TotalClaimed = 0;

	_FileOpenFlag = append_existing?os::File::Normal_Append:os::File::Normal_Write;

	_WriteBufferSize = (buffer_size + 3) & 0xffffffffc;

	rt::String fn;
	_RealizeFilename(fn);

	if(	_File.Open(fn,_FileOpenFlag, true) &&
		_WritePool.SetSize(2*_WriteBufferSize)
	)
	{	_File.SeekToEnd();

		_FrontBuf->pBuf = _WritePool;
		_FrontBuf->Used = 0;
		_BackBuf->pBuf = &_WritePool[_WriteBufferSize];
		_BackBuf->Used = 0;

		struct _call
		{	static DWORD _func(LPVOID pThis)
			{	((ParallelFileWriter*)pThis)->_WriteRoutine();
				return 0;
			}
		};

		_WriteThread.Create(_call::_func,this);

		return true;
	}
	
	if(_File.IsOpen())
		_File.Close();

	_WritePool.SetSize(0);
	return false;
}

void ParallelFileWriter::PreClose()
{
	if(_WriteThread.IsRunning())
	{
		_WriteThread.WantExit() = true;
	}
}

void ParallelFileWriter::Close()
{
	stat_ClaimPerSecond = -1;

	if(_WriteThread.IsRunning())
	{
		_WriteThread.WantExit() = true;
		_WriteThread.WaitForEnding(1000, true);
	}
	
	if(_File.IsOpen())
		_File.Close();

	//_WritePool.SetSize(0);
}

void ParallelFileWriter::SetFileWritingCallback(FUNC_FileWriter cb, LPVOID cookie)
{
	_pFileWriterCB = cb;
	_FileWriterCookie = cookie;
}

void ParallelFileWriter::_WriteDownBackBuffer()
{
	// dump to file only
	_Chunk* p = (_Chunk*)_BackBuf->pBuf;
	int used = _BackBuf->Used;
	_Chunk* pend = (_Chunk*)(_BackBuf->pBuf + rt::min<int>(used,(int)(_WriteBufferSize - _ChunkHeaderSize)));
	
	for(;p<pend;p = p->GetNext())
	{	
		if(p->size)
		{
			if(p->length==INFINITE)
			{	stat_UnfinalizedChunk++;
				continue;
			}

			if(p->length>0)
			{	if(_pFileWriterCB)
				{	if(!_pFileWriterCB(p->data,p->length,_File,_FileWriterCookie))
					{	stat_FileError++;
					}
				}
				else
				{	if(_File.Write(p->data,p->length) != p->length)
					{	stat_FileError++;
					}
				}
			}
		}
		else break;
	}
	_File.Flush();

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

void ParallelFileWriter::LogAlert()
{
	static const rt::SS precentage("% / ");
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

void ParallelFileWriter::GetCurrentLogFilename(rt::String& filename)
{
	EnterCSBlock(_FilenameTemplateCS);
	filename = _File.GetFilename();
}

void ParallelFileWriter::_WriteRoutine()
{
	int time_to_sleep = _WriteDownInterval;
	os::Timestamp tm;
	rt::String fn;

	LONGLONG minute_last_checked = -1;

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
		LONGLONG minute = tm/(60*1000);
		
		if(_FilenameChanged || minute != minute_last_checked)
		{
			EnterCSBlock(_FilenameTemplateCS);

			_RealizeFilename(fn);
			if(_File.GetFilename() != fn)
			{	os::File	_log;
				if(_log.Open(fn,_FileOpenFlag))
				{	_log.SeekToEnd();
					rt::Swap(_log,_File);
				}
				else
				{	stat_FileError++;
				}	
			}

			_FilenameChanged = false;
			minute_last_checked = minute;
		}

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
		{
			LogAlert();
		}

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

	_File.Close();
}

} // namespace os


