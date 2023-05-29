#include "../rt/buffer_type.h"
#include "../rt/json.h"
#include "multi_thread.h"
#include "kernel.h"

/////////////////////////////////////////////////////////////////
// Platform independent implementations
//////////////////////////////////////////////////
// DelayedGarbageCollection
namespace os
{
namespace _details
{
	LPVOID& RRCD_Holder_GetLastEntry()
	{
		thread_local void* p = nullptr;
		return p;
	}

	struct _GarbagItem
	{	LPCVOID			pObj;
		os::DelayedGarbageCollection::LPFUNC_DELETION	pDeletionFunction;
		UINT			TimeToDead;
		void			Delete(){ pDeletionFunction((LPVOID)pObj); }
	};

	struct _GarbagBin
	{
		UINT							_Tick;
		rt::BufferEx<_GarbagItem>		_PendingGarbag;
		os::CriticalSection				_PendingGarbagCCS;
		os::Thread						_GarbagDeletionThread;
		_GarbagBin(){ _Tick = 0; }
		~_GarbagBin(){ Exit(); }
		void Exit()
		{
			if(_GarbagDeletionThread.IsRunning())
			{
				_GarbagDeletionThread.WantExit() = true;
				_GarbagDeletionThread.WaitForEnding();
			}
		}
	};
	_GarbagBin				g_GCB;
}

void DelayedGarbageCollection::Exit()
{
	_details::g_GCB.Exit();
}

DWORD DelayedGarbageCollection::_DeletionThread(LPVOID)
{
	for(;;_details::g_GCB._Tick++)
	{
		if(!os::Sleep(1000, &_details::g_GCB._GarbagDeletionThread.WantExit()))
			goto DELETION_EXITING;

		EnterCSBlock(_details::g_GCB._PendingGarbagCCS);
		UINT open = 0;
		for(UINT i=0;i<_details::g_GCB._PendingGarbag.GetSize();i++)
		{
			if(_details::g_GCB._PendingGarbag[i].TimeToDead < _details::g_GCB._Tick)
			{
				_details::g_GCB._PendingGarbag[open] = _details::g_GCB._PendingGarbag[i];
				open++;
			}
			else
			{
				_details::g_GCB._PendingGarbag[i].Delete();
			}
		}

		_details::g_GCB._PendingGarbag.ShrinkSize(open);
	}

DELETION_EXITING:
	Flush();
	return 0;
}

void DelayedGarbageCollection::Flush()
{
	EnterCSBlock(_details::g_GCB._PendingGarbagCCS);
	for(UINT i=0;i<_details::g_GCB._PendingGarbag.GetSize();i++)
		_details::g_GCB._PendingGarbag[i].Delete();

	_details::g_GCB._PendingGarbag.SetSize();
}

void DelayedGarbageCollection::DeleteObject(LPCVOID x, DWORD TTL_msec, DelayedGarbageCollection::LPFUNC_DELETION delete_func)
{
	ASSERT(delete_func);

	if(x == nullptr)return;
	if(TTL_msec == 0)
	{	delete_func((LPVOID)x);
		return;
	}

	{	EnterCSBlock(_details::g_GCB._PendingGarbagCCS);
		if(_details::g_GCB._GarbagDeletionThread.IsRunning()){}
		else
		{	_details::g_GCB._GarbagDeletionThread.Create(_DeletionThread, nullptr);
		}

#ifdef PLATFORM_DEBUG_BUILD
		// check if the object is added for collection already (delete twice)
		for(UINT i=0;i<_details::g_GCB._PendingGarbag.GetSize();i++)
			ASSERT(_details::g_GCB._PendingGarbag[i].pObj != x);
#endif

		_details::_GarbagItem& n = _details::g_GCB._PendingGarbag.push_back();
		n.pObj = x;
		n.pDeletionFunction = delete_func;
		n.TimeToDead = _details::g_GCB._Tick + (TTL_msec+999)/1000;
	}
}

#if defined(PLATFORM_DEBUG_BUILD)
namespace _details
{
thread_local std::unordered_map<const ReadWriteMutex*, bool> ReadWriteMutexLocked; // true=write, false=read
} // namespace _details

void ReadWriteMutex::__LockTrack(const ReadWriteMutex* mutex, bool write)
{
	ASSERT(_details::ReadWriteMutexLocked.find(mutex) == _details::ReadWriteMutexLocked.end());
	_details::ReadWriteMutexLocked[mutex] = write;
}

void ReadWriteMutex::__LockUntrack(const ReadWriteMutex* mutex, bool write)
{
	auto it = _details::ReadWriteMutexLocked.find(mutex);
	ASSERT(it != _details::ReadWriteMutexLocked.end());
	ASSERT(it->second == write);
	_details::ReadWriteMutexLocked.erase(it);
}

bool ReadWriteMutex::__IsReadLocked(const ReadWriteMutex* mutex)
{
	auto it = _details::ReadWriteMutexLocked.find(mutex);
	return it != _details::ReadWriteMutexLocked.end() && it->second == false;
}

bool ReadWriteMutex::__IsAnyLocked(const ReadWriteMutex* mutex)
{
	auto it = _details::ReadWriteMutexLocked.find(mutex);
	return it != _details::ReadWriteMutexLocked.end();
}
#endif

} // namespace os

bool os::Thread::WaitForEnding(UINT time_wait_ms, bool terminate_if_timeout)
{
	Sleep(0);
	while(time_wait_ms > (UINT)100)
	{	
		if(!IsRunning())return true;
		Sleep(100);
		if(time_wait_ms!=INFINITE)time_wait_ms -= 100;
	}

	if(terminate_if_timeout)
		TerminateForcely();

	return false;
}

os::Thread::Thread()
{
	__MFPTR_Obj = nullptr;
	__CB_Func = nullptr;
	_hThread = NULL;
	_ExitCode = INFINITE;
}

os::Thread::~Thread()
{
	ASSERT(_hThread == NULL);
}

bool os::Thread::Create(LPVOID obj, const THISCALL_MFPTR& on_run, LPVOID param, ULONGLONG cpu_aff, UINT stack_size)
{
	ASSERT(_hThread == NULL);

	__CB_Func = nullptr;
	__MFPTR_Obj = obj;
	__MFPTR_Func = on_run;
	__CB_Param = param;

	return _Create(stack_size, cpu_aff);
}

bool os::Thread::Create(FUNC_THREAD_ROUTINE x, LPVOID thread_cookie, ULONGLONG cpu_aff, UINT stack_size)
{
	ASSERT(_hThread == NULL);

	__CB_Func = x;
	__CB_Param = thread_cookie;
	__MFPTR_Obj = nullptr;
	__MFPTR_Func.Zero();

	return _Create(stack_size, cpu_aff);
}

DWORD os::Thread::_Run()
{
#if defined(PLATFORM_ANDROID)
	struct _thread_call
	{	static void thread_exit_handler(int sig)
		{ 	pthread_exit(0);
	}	};

	struct sigaction actions;
	memset(&actions, 0, sizeof(actions)); 
	sigemptyset(&actions.sa_mask);
	actions.sa_flags = 0; 
	actions.sa_handler = _thread_call::thread_exit_handler;
	sigaction(SIGUSR2,&actions,NULL);
#endif

	while(!_hThread)os::Sleep(10);
	os::Sleep(10);

	DWORD ret;
	if(__MFPTR_Obj)
	{
		ret = THISCALL_POLYMORPHISM_INVOKE(OnRun, __MFPTR_Obj, __MFPTR_Func, __CB_Param);
	}
	else
	{	
		ASSERT(__CB_Func);
		ret = __CB_Func(__CB_Param);
	}

	if(ret != (DWORD)THREAD_OBJECT_DELETED_ON_RETURN)
	{
		_ExitCode = ret;
		__release_handle(_hThread);
		_hThread = NULL;
	} // else never touch this again.

	return ret;
}

namespace os
{

namespace _details
{
thread_local UINT __Thread_Label = 0;
} // namespace _details


void Thread::SetLabel(UINT thread_label)
{
	_details::__Thread_Label = thread_label;
}

UINT Thread::GetLabel()
{
	return _details::__Thread_Label;
}

void Thread::Fence::Join()
{
	if(_ThreadCount <= 1)return;
	int r = _Round;
	auto ret = os::AtomicIncrement(&_Count);
	if(ret == _ThreadCount)
	{	
		_Next.Set();
		os::AtomicDecrement(&_Count);
		do{ os::Sleep(1); }while(_Count);
		_Next.Reset();
		_Round++;
	}
	else
	{
		_Next.WaitSignal();
		os::AtomicDecrement(&_Count);
		do{ os::Sleep(1); }while(r == _Round);
	}
}

} // namespace os

//////////////////////////////////////////////////////////
// All Windows implementations
#if defined(PLATFORM_WIN)

void os::Thread::__release_handle(HANDLE hThread)
{
	::CloseHandle(hThread);
}

bool os::Thread::_Create(UINT stack_size, ULONGLONG CPU_affinity)
{
	ASSERT(_hThread == NULL);
	_bWantExit = false;

	struct _call
	{	static DWORD WINAPI _func(LPVOID p)
		{	return ((Thread*)p)->_Run();
	}	};

	_hThread = ::CreateThread(NULL, stack_size, _call::_func, this, 0, &_ThreadId);
	SetThreadAffinityMask(_hThread, (DWORD_PTR&)CPU_affinity);
	return _hThread != NULL;
}

UINT os::Thread::GetId() const
{
	return _ThreadId;
}

void os::Thread::SetPriority(UINT p)
{
	SetThreadPriority(_hThread, p);
}

void os::Thread::TerminateForcely()
{
	if(_hThread)
	{
		::TerminateThread(_hThread, -1);
		__release_handle(_hThread);
		_hThread = NULL;
	}
}

bool os::Thread::IsRunning() const
{
	if(_hThread == NULL)return false;
	return ::WaitForSingleObject(_hThread, 0) == WAIT_TIMEOUT;
}


#else
//////////////////////////////////////////////////////////
// All linux/BSD implementations
#include <pthread.h>
#if defined(PLATFORM_IOS) || defined(PLATFORM_MAC)
#import <mach/thread_act.h>
#endif

bool os::Thread::IsRunning() const
{
	return _hThread != NULL;
}

bool os::Thread::_Create(UINT stack_size, ULONGLONG CPU_affinity)
{
	ASSERT(_hThread == NULL);
	_bWantExit = false;

	pthread_attr_t attr;
	pthread_attr_t* set_attr = nullptr;

    struct _call
    {    static LPVOID _func(LPVOID p)
        {    return (LPVOID)(unsigned long)((Thread*)p)->_Run();
        }    };

#if defined(PLATFORM_IOS) || defined(PLATFORM_MAC)
    if(stack_size)
    {
        pthread_attr_init(&attr);
        if(stack_size)
            pthread_attr_setstacksize(&attr, rt::max((int)PTHREAD_STACK_MIN,(int)stack_size));
        set_attr = &attr;
    }
    
    if(CPU_affinity != 0xffffffffffffffffULL)
    {
        if(pthread_create_suspended_np((pthread_t*)&_hThread, set_attr, _call::_func, this))
        {
            _hThread = NULL;
            return false;
        }
        
        mach_port_t mach_thread = pthread_mach_thread_np(*(pthread_t*)&_hThread);
        thread_affinity_policy_data_t policyData[64];
        int count = 0;
        for(UINT i=0; i<sizeof(SIZE_T)*8; i++)
            if(CPU_affinity&(1ULL<<i))
                policyData[count].affinity_tag = i;
        
        thread_policy_set(mach_thread, THREAD_AFFINITY_POLICY, (thread_policy_t)&policyData, count);
        thread_resume(mach_thread);
        return true;
    }
    
#else
	if(stack_size || CPU_affinity != 0xffffffffffffffffULL)
	{
		pthread_attr_init(&attr);
		
		if(stack_size)
			pthread_attr_setstacksize(&attr, rt::max((int)PTHREAD_STACK_MIN,(int)stack_size));
		
		if(CPU_affinity != 0xffffffffffffffffULL)
		{
			cpu_set_t cpuset;
			rt::Zero(cpuset);
			for(UINT i=0; i<sizeof(SIZE_T)*8; i++)
				if(CPU_affinity&(1ULL<<i))
					CPU_SET(i, &cpuset);
		
			#ifndef PLATFORM_ANDROID
			pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpuset);
			#endif
		}
		set_attr = &attr;
	}
#endif

    if(0 == pthread_create((pthread_t*)&_hThread, set_attr, _call::_func, this))
        return true;

	_hThread = NULL;
	return false;
}

SIZE_T os::Thread::GetId() const
{
#if defined(PLATFORM_IOS) || defined(PLATFORM_MAC)
	return (SIZE_T)pthread_mach_thread_np(*(pthread_t*)&_hThread);
#else
	return *(SIZE_T*)&_hThread;
#endif
}

void os::Thread::SetPriority(UINT p)
{
	struct sched_param sp;
	sp.sched_priority = p;
	pthread_setschedparam(*(pthread_t*)&_hThread, SCHED_OTHER, &sp);
}

void os::Thread::TerminateForcely()
{
	if(_hThread)
	{
#if defined(PLATFORM_ANDROID)
		pthread_kill(*(pthread_t*)&_hThread, SIGUSR2);
#else
		pthread_cancel(*(pthread_t*)&_hThread);
#endif
		_hThread = NULL;
	}
}

void os::Thread::__release_handle(HANDLE hThread)
{
	pthread_detach((pthread_t&)hThread);
}

#endif

void os::ConsolePrompt::Init(CONSOLEINPUT_CALLBACK on_input, LPVOID cookie, UINT input_size_max)
{
	_InputCallback = on_input;
	_InputCallbackCookie = cookie;
	_InputBufSize = input_size_max;

	if(!IsRunning())
	{
		__fgets_called = 0;

		VERIFY(_ConsoleInputThread.Create([this](){
			_ConsoleInput();
		}));

		os::SetLogConsolePrompt("=>");	
	}
}

void os::ConsolePrompt::Term()
{
	int f = os::AtomicIncrement(&__fgets_called);
	if(_ConsoleInputThread.IsRunning())
	{
		_ConsoleInputThread.WantExit() = true;

		#if defined(PLATFORM_WIN)
		{
			INPUT_RECORD ir = { KEY_EVENT };
			KEY_EVENT_RECORD& ke = ir.Event.KeyEvent;

			ke.bKeyDown = true;
			ke.wRepeatCount = 1;
			ke.wVirtualKeyCode = VK_RETURN;
			ke.wVirtualScanCode = MapVirtualKey(VK_RETURN, MAPVK_VK_TO_VSC);
			ke.uChar.AsciiChar = VK_RETURN;
			ke.dwControlKeyState = 0;

			DWORD ret = 0;
			HANDLE hcon = CreateFile(L"CONIN$", FILE_GENERIC_WRITE, FILE_SHARE_READ || FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
			if (::WriteConsoleInput(hcon, &ir, 1, &ret) == false)
			{
				ret = GetLastError();
			}

			os::Sleep(10);
		}
		#endif	

		if(f)
			_ConsoleInputThread.TerminateForcely();
		else
			_ConsoleInputThread.WaitForEnding();
	}

	__fgets_called = 0;

	if(_CookieRelease)
		_CookieRelease(_InputCallbackCookie);
}


void os::ConsolePrompt::_ConsoleInput()
{
#if defined(PLATFORM_WIN)
	{
		HMODULE hModule = NULL;
		GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)this, &hModule);
		HMODULE hProcess = GetModuleHandle(nullptr);
		if (hModule != hProcess)
			freopen("CONIN$", "r+t", stdin);
	}
#endif
 
	rt::BufferEx<CHAR> cmdbuf;

	while(!_ConsoleInputThread.WantExit())
	{
		cmdbuf.SetSize(_InputBufSize);

		os::AtomicIncrement(&__fgets_called);
		bool isFirst = true;
		while(fgets(cmdbuf.Begin() + (isFirst ? 0 : cmdbuf.GetSize() - _InputBufSize - 1), _InputBufSize + (isFirst ? 0 : 1), stdin))
		{
			isFirst = false;
			if(strlen(cmdbuf.Begin()) == cmdbuf.GetSize() - 1 && *(cmdbuf.End() - 2) != '\n')
			{
				cmdbuf.ExpandSize(cmdbuf.GetSize() + _InputBufSize);
				continue;
			}
			break;
		}
		cmdbuf.ExpandSize(cmdbuf.GetSize()*3/2 + 1);
		int f = os::AtomicDecrement(&__fgets_called);
		if(f)
		{
			cmdbuf.SetSize(0);
			os::Sleep(); // halt here, wait to be terminated
		}

		int mb_len = (int)strlen(cmdbuf.Begin());
#ifdef PLATFORM_WIN
		LPWSTR utf16 = (LPWSTR)alloca((1 + mb_len*2)*sizeof(WCHAR));
		int utf16_len = MultiByteToWideChar(CP_THREAD_ACP, 0, cmdbuf.Begin(), mb_len, utf16, 1 + mb_len*2);
		mb_len = (int)os::UTF8Encode(utf16, utf16_len, cmdbuf.Begin());
#endif
		ASSERT(mb_len < cmdbuf.GetSize()*3/2);
		cmdbuf.ChangeSize(mb_len);
		if(mb_len > 0) cmdbuf[mb_len] = 0;

		if(_InputCallback)
			_InputCallback(cmdbuf.Begin(), (UINT)cmdbuf.GetSize(), _InputCallbackCookie);

		cmdbuf.Zero();
		cmdbuf.SetSize(0);
	}
}

#if defined(PLATFORM_WIN)
////////////////////////////////////////////////////////////
// CLaunchProcess
os::LaunchProcess::LaunchProcess()
{
	_hProcess = INVALID_HANDLE_VALUE;
	hChildStdoutRdDup = INVALID_HANDLE_VALUE;
	hChildStdinRd = INVALID_HANDLE_VALUE;
	hChildStdinWrDup = INVALID_HANDLE_VALUE;
	hChildStdoutWr = INVALID_HANDLE_VALUE;

	_Callback = nullptr;

	_ExitCode = 0;
	_ExitTime = 0;
	_ExecutionTime = 0;
}

os::LaunchProcess::~LaunchProcess()
{
	IsRunning();
	_ClearAll();
}


void os::LaunchProcess::_ClearAll()
{	
	_OutputHookThread.WantExit() = true;
	_OutputHookThread.WaitForEnding();

	#define _SafeCloseHandle(x) { if((x)!=INVALID_HANDLE_VALUE){ ::CloseHandle(x); x=INVALID_HANDLE_VALUE; } }

	_SafeCloseHandle(_hProcess);

	_SafeCloseHandle(hChildStdoutRdDup);	//make hook thread exit
	_SafeCloseHandle(hChildStdinRd);
	_SafeCloseHandle(hChildStdinWrDup);
	_SafeCloseHandle(hChildStdoutWr);


	#undef _SafeCloseHandle
}


bool os::LaunchProcess::Launch(LPCSTR cmdline, DWORD flag, LPCSTR pWorkDirectory, LPCSTR pEnvVariable)
{
	VERIFY(!IsRunning());

	rt::String cmd(cmdline);
	if(cmd.IsEmpty())return false;

	_Flag = flag;
	bool hook_output = (FLAG_SAVE_OUTPUT&flag) || (FLAG_ROUTE_OUTPUT&flag) || _Callback!=NULL;

	PROCESS_INFORMATION piProcInfo;
	STARTUPINFOW siStartInfo;

	rt::Zero( &piProcInfo, sizeof(PROCESS_INFORMATION) );
	rt::Zero( &siStartInfo, sizeof(STARTUPINFO) );
	siStartInfo.cb = sizeof(STARTUPINFO);
	siStartInfo.wShowWindow = (WORD)(flag&FLAG_HIDE_WINDOW)?SW_HIDE:SW_SHOW;
	siStartInfo.dwFlags = STARTF_USESHOWWINDOW;

	if(hook_output)
	{	
		HANDLE hChildStdoutRd,hChildStdinWr;
		/////////////////////////////////////////////////////////////////////////
		// Creating a Child Process with Redirected Input and Output
		// 1. create pipes
		SECURITY_ATTRIBUTES saAttr;
		bool fSuccess; 

		// Set the bInheritHandle flag so pipe handles are inherited. 
		saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
		saAttr.bInheritHandle = true; 
		saAttr.lpSecurityDescriptor = NULL;

		// Create a pipe for the child process's STDOUT. 
		if (::CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &saAttr, 0) == 0)
			return false;

		// Create non-inheritable read handle and close the inheritable read handle. 
		fSuccess = DuplicateHandle(	GetCurrentProcess(), hChildStdoutRd,
									GetCurrentProcess(),&hChildStdoutRdDup , 0,
									false, DUPLICATE_SAME_ACCESS);
		if (!fSuccess)
			return false;

		CloseHandle(hChildStdoutRd);

		// Create a pipe for the child process's STDIN. 
		if (::CreatePipe(&hChildStdinRd, &hChildStdinWr, &saAttr, 0) == 0)
			return false;


		// Duplicate the write handle to the pipe so it is not inherited. 
		fSuccess = DuplicateHandle(	GetCurrentProcess(), hChildStdinWr, 
									GetCurrentProcess(), &hChildStdinWrDup, 0, 
									false, DUPLICATE_SAME_ACCESS); 
		if (!fSuccess)
			return false;
		CloseHandle(hChildStdinWr);

		///////////////////////////////////////////////////////
		// 2. create child process
		siStartInfo.hStdError = hChildStdoutWr;
		siStartInfo.hStdOutput = hChildStdoutWr;
		siStartInfo.hStdInput = hChildStdinRd;
		siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

		_hProcess = INVALID_HANDLE_VALUE;
		_Output.Empty();
		_OutputHookThread.Create(_OutputHookRoutine, this);
		_OutputHookThread.SetPriority(os::Thread::PRIORITY_HIGH);
	}

	rt::Buffer<WCHAR>	env;
	if(pEnvVariable)
	{
		LPCWSTR s = ::GetEnvironmentStringsW();
		UINT s_len=0;
		for(;;s_len++)
			if(s[s_len] == 0 && s[s_len+1] == 0)
				break;

		UINT a_len=0;
		for(;;a_len++)
			if(pEnvVariable[a_len] == 0 && pEnvVariable[a_len+1] == 0)
				break;

		os::__UTF16 addon(rt::String_Ref(pEnvVariable, a_len));

		env.SetSize(a_len + 1 + s_len + 1 + 1);
		env.Zero();
		memcpy(&env[0], s, sizeof(WCHAR)*s_len);
		memcpy(&env[s_len+1], addon.Begin(), sizeof(WCHAR)*a_len);
		
		pEnvVariable = (LPCSTR)env.Begin();
	}

	// Create the child process. 
	bool ret =
	CreateProcessW(	NULL, 
					os::__UTF16(cmd).Begin(),	// command line 
					NULL,				// process security attributes 
					NULL,				// primary thread security attributes 
					true,				// handles are inherited 
					pEnvVariable?CREATE_UNICODE_ENVIRONMENT:0,				// creation flags 
					(LPVOID)pEnvVariable,
					os::__UTF16(pWorkDirectory),
					&siStartInfo,		// STARTUPINFO pointer 
					&piProcInfo);		// receives PROCESS_INFORMATION 

	if(ret)
	{	
		_ExitCode = STILL_ACTIVE;
		_hProcess = piProcInfo.hProcess;
		CloseHandle( piProcInfo.hThread );
		return true;
	}
	else
	{
		_LOG_WARNING("Error launching process: "<<cmd<<" ERR: "<<GetLastError());
		_ClearAll();
		return false;
	}
}

LPCSTR os::LaunchProcess::GetOutput()
{
	return _Output;
}

UINT os::LaunchProcess::GetOutputLen()
{
	return (UINT)_Output.GetLength();
}

void os::LaunchProcess::CopyOutput(rt::String& out)
{
	EnterCSBlock(_CCS);
	out = _Output;
}

bool os::LaunchProcess::WaitForEnding(DWORD timeout)
{
	os::TickCount t;
	t.LoadCurrentTick();

	::Sleep(500);

	while(IsRunning())
	{	::Sleep(500);
		if((DWORD)t.TimeLapse()>timeout)return false;
	}

	return true;
}

void os::LaunchProcess::Terminate()
{
	if(IsRunning())
	{
		::TerminateProcess(_hProcess,-1);
		os::Sleep(0);
		while(IsRunning())os::Sleep(1);
		_ClearAll();
	}
}

bool os::LaunchProcess::IsRunning()
{
	if(_hProcess!=INVALID_HANDLE_VALUE)
	{
		bool exited = false;
		VERIFY(::GetExitCodeProcess(_hProcess,(LPDWORD)&_ExitCode));
		exited = (_ExitCode!=STILL_ACTIVE);

		if(exited)
		{	
			FILETIME creat,exit,foo;
			GetProcessTimes(_hProcess,&creat,&exit,&foo,&foo);

			if(*((__int64*)&exit))
			{
				_ExecutionTime = (UINT)((((ULONGLONG&)exit) - ((ULONGLONG&)creat))/10000);
				_ExitTime = (*((__int64*)&exit))/10000LL - 11644473600000LL;
			
				_ClearAll();
				return false;
			}
		}
		return true;
	}

	return false;
}

void os::LaunchProcess::_HookedOutput(char* buffer, UINT dwRead)
{
	if(_Flag&FLAG_ROUTE_OUTPUT){ buffer[dwRead]=0; printf(buffer); }
	if(_Flag&FLAG_SAVE_OUTPUT)
	{	EnterCSBlock(_CCS);
		int i = (int)_Output.GetLength();
		_RemoveCarriageReturn(_Output, rt::String_Ref(buffer, dwRead));
	}
	if(_Callback)
	{	_Callback(buffer, dwRead, _Callback_Cookie);
	}
}


DWORD os::LaunchProcess::_OutputHookRoutine(LPVOID p)
{
	LaunchProcess* pThis = (LaunchProcess*)p;

	while (pThis->_hProcess == INVALID_HANDLE_VALUE && !pThis->_OutputHookThread.WantExit())
		Sleep(100);

	char buffer[1024];

	DWORD dwRead,exitcode;
	exitcode = pThis->_ExitCode;
	while(exitcode==STILL_ACTIVE)
	{	
		if(PeekNamedPipe(pThis->hChildStdoutRdDup,NULL,0,NULL,&dwRead,0))
		{	if( dwRead )
			{	if( ReadFile( pThis->hChildStdoutRdDup, buffer, rt::min((DWORD)sizeof(buffer)-1,dwRead), &dwRead, NULL) && dwRead )
				{	pThis->_HookedOutput(buffer,dwRead);
					continue;
				}
			}
		}

		Sleep(100);
		if (pThis->hChildStdoutRdDup == INVALID_HANDLE_VALUE)
			return 0;
		if (pThis->_hProcess != INVALID_HANDLE_VALUE)
			GetExitCodeProcess(pThis->_hProcess, &exitcode);
		else
			return 0;
	} 

	// check for words before death of the process
	do
	{	dwRead = 0;
		if(PeekNamedPipe(pThis->hChildStdoutRdDup,NULL,0,NULL,&dwRead,0))
		{	if( dwRead )
			{	if( ReadFile( pThis->hChildStdoutRdDup, buffer, rt::min((DWORD)sizeof(buffer)-1,dwRead), &dwRead, NULL) && dwRead )
					pThis->_HookedOutput(buffer,dwRead);
			}
		}
	}while(dwRead);

	pThis->_ExitCode = exitcode;
	return 0;
}

bool os::LaunchProcess::SendToStdin(LPCVOID str, UINT len)
{
	DWORD wlen = 0;
	return WriteFile(hChildStdinWrDup, str, len, &wlen, NULL) && wlen == len;
}

void os::LaunchProcess::_RemoveCarriageReturn(rt::String& output, const rt::String_Ref& add)
{
	if(add.IsEmpty())return;

	LPCSTR p = add.Begin();
	LPCSTR end = add.End();
	LPCSTR last_linend = nullptr;
	LPCSTR last_copied = p;

	if(!output.IsEmpty() && output.Last() == '\r')
	{
		if(*p == '\n')
		{	p++;
			output += '\n';
			last_copied = last_linend = p;
		}
		else
		{	int i = (int)output.FindCharacterReverse('\n');
			if(i<0){ output.Empty(); }
			else{ output.SetLength(i+1); }
			last_linend = p;
		}
	}
	else
	{	LPCSTR s = p;
		while(*s != '\r' && *s != '\n' && s < end)s++;
		if(*s == '\r')
		{
			if(s+1 < end)
			{	
				if(s[1] == '\n')
				{	last_linend = s+2;
				}
				else
				{	int i = (int)output.FindCharacterReverse('\n');
					if(i<0){ output.Empty(); }
					else{ output.SetLength(i + 1); }
					p = last_copied = last_linend = s + 1;
				}
			}
			else
			{	output += rt::String_Ref(p,s+1);
				return;
			}	
		}
		else if(s == end)
		{
			output += add;
			return;
		}
		else
		{	ASSERT(*s == '\n');
			last_linend = p = s+1;
		}
	}

	for(;p < end;p++)
	{

		if(*p == '\n'){ last_linend = p+1; }
		else if(*p == '\r')
		{
			if(p+1<end)
			{
				if(p[1] == '\n')
				{	last_linend = p + 2;
					p++;
				}
				else
				{	ASSERT(last_linend >= last_copied);
					if(last_linend != last_copied)
					{	output += rt::String_Ref(last_copied,last_linend); 
					}
					last_copied = last_linend = p + 1;
				}
			}
			else
			{
				output += rt::String_Ref(last_copied, p+1);
				return;
			}
		}
	}

	if(last_copied < end)
		output += rt::String_Ref(last_copied, end);
}


void os::LaunchProcess::SetOutputCallback(FUNC_HOOKEDOUTPUT func, LPVOID cookie)
{
	_Callback = func;
	_Callback_Cookie = cookie;
}

bool os::LaunchProcess::SendInput(LPCSTR p, UINT len)
{
	if(hChildStdinWrDup)
	{	DWORD w;
		return WriteFile(hChildStdinWrDup, p, len, &w, NULL) && w == len;
	}
	return false;
}

#endif // #if defined(PLATFORM_WIN)
