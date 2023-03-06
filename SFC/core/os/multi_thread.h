#pragma once
/**
 * @file multi_thread.h
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
#include "thread_primitive.h"
#include "kernel.h"

namespace rt
{
class Json;
};

namespace os
{
/** \defgroup multi_thread multi_thread
 * @ingroup os
 *  @{
 */

typedef DWORD	(*FUNC_THREAD_ROUTINE)(LPVOID x); ///< Multi-threading

class Thread
{
	Thread(const Thread& x);  // disable copy ctor
	LPVOID			__CB_Param;

	
	THISCALL_POLYMORPHISM_DECLARE(DWORD, 0, OnRun, LPVOID param); ///< callback by THISCALL_MFPTR
	LPVOID			__MFPTR_Obj;
	THISCALL_MFPTR	__MFPTR_Func;

	
	FUNC_THREAD_ROUTINE	__CB_Func; ///< callback by FUNC_THREAD_ROUTINE
	
public:
#if defined(PLATFORM_WIN)
	enum _tagThreadPriority
	{	PRIORITY_REALTIME = THREAD_PRIORITY_TIME_CRITICAL,
		PRIORITY_HIGH = THREAD_PRIORITY_ABOVE_NORMAL,
		PRIORITY_NORMAL = THREAD_PRIORITY_NORMAL,
		PRIORITY_LOW = THREAD_PRIORITY_BELOW_NORMAL,
		PRIORITY_IDLE = THREAD_PRIORITY_IDLE		
	};
#else
	enum _tagThreadPriority
	{	PRIORITY_REALTIME = 20,
		PRIORITY_HIGH = 5,
		PRIORITY_NORMAL = 0,
		PRIORITY_LOW = -5,
		PRIORITY_IDLE = -20		
	};
#endif
protected:

#if defined(PLATFORM_WIN)
	DWORD			_ThreadId;
#endif
	HANDLE			_hThread;
	bool			_bWantExit;
	DWORD			_ExitCode;
	DWORD			_Run();
	bool			_Create(UINT stack_size, ULONGLONG CPU_affinity);
	static void		__release_handle(HANDLE hThread);

public:
	static const int THREAD_OBJECT_DELETED_ON_RETURN = 0xfeed9038;	///< the thread route return to skip clean up

	Thread();
	~Thread();

	operator bool(){ return _hThread; }
	bool	WaitForEnding(UINT time_wait_ms = INFINITE, bool terminate_if_timeout = false);
	DWORD	GetExitCode() const { return _ExitCode; }
	bool	IsRunning() const;
	bool&	WantExit(){ return _bWantExit; }
	bool	WantExit() const { return _bWantExit; }
	void	TerminateForcely();
	void	DetachThread(){ if(_hThread){ __release_handle(_hThread); _hThread = NULL; } }
	void	SetPriority(UINT p = PRIORITY_HIGH);
#if defined(PLATFORM_WIN)
	UINT	GetId() const;
#else
    SIZE_T  GetId() const;
#endif

	bool	Create(LPVOID obj, const THISCALL_MFPTR& on_run, LPVOID param = nullptr, ULONGLONG CPU_affinity = 0xffffffffffffffffULL, UINT stack_size = 0);
	bool	Create(FUNC_THREAD_ROUTINE x, LPVOID thread_cookie = nullptr, ULONGLONG CPU_affinity = 0xffffffffffffffffULL, UINT stack_size = 0);

	template<typename T>
	auto&	Create(T routine, ULONGLONG CPU_affinity = 0xffffffffffffffffULL, UINT stack_size = 0) // Caller should ensure the lifetime of variables captured by the lambda function
			{	__MFPTR_Obj = nullptr;
				ASSERT(_hThread == NULL);
				struct _call { 
					static DWORD _func(LPVOID p)
					{   DWORD ret = rt::CallLambda<DWORD>(0, *(T*)p);
						_SafeDel_ConstPtr((T*)p);
						return ret;
					}};
				__CB_Func = _call::_func;
				__CB_Param = _New(T(routine));
				ASSERT(__CB_Param);		
				if(_Create(stack_size, CPU_affinity))return *this;
				_SafeDel_ConstPtr((T*)__CB_Param);
				return *this;
			}
	static SIZE_T GetCurrentId(){ return GetCurrentThreadId(); }
	static void SetLabel(UINT thread_label);
	static UINT GetLabel();
	template<typename T>
	static void YieldRun(T routine, ULONGLONG CPU_affinity = 0xffffffffffffffffULL, UINT stack_size = 0)
			{	auto* t = _New(Thread);
				t->Create([routine,t](){
					routine();
					__release_handle(t->_hThread);
					t->_hThread = NULL;
					_SafeDel_ConstPtr(t);
					return THREAD_OBJECT_DELETED_ON_RETURN; 
				}, CPU_affinity, stack_size);
			}

	class Fence
	{
		int				_Round;
		int				_ThreadCount;
		volatile int	_Count;
		os::Event		_Next;
	public:
		Fence(int thread_count){ _ThreadCount = thread_count; _Count = 0; _Round = 0; _Next.Reset(); }
		void Join(); // support multiple Join calls, all thread are sync-ed step by step
	};
};

template<typename FUNC>
inline uint32_t ParallelLoop(FUNC&& loop_body) // loop_body(int i) should return false to end the loop
{
	struct Loop
	{
		volatile int			LoopIndex = -1;
		rt::Buffer<os::Thread>	Threads;
		int						SubThreadCount = 0;
		volatile int			SubThreadEnded = 0;
		os::Event				AllSubThreadEnded;
		FUNC&					LoopFunction;
		static DWORD call(LPVOID x)
		{	auto* t = (Loop*)x;
			while(t->LoopFunction(os::AtomicIncrement(&t->LoopIndex)));
			os::AtomicDecrement(&t->LoopIndex);
			if(os::AtomicIncrement(&t->SubThreadEnded) == t->SubThreadCount)
				t->AllSubThreadEnded.Set();
			return 0;
		}
		Loop(FUNC&& loop_body):LoopFunction(loop_body)
		{
			Threads.SetSize(SubThreadCount = (os::GetNumberOfPhysicalProcessors()-1));
			if(SubThreadCount){	AllSubThreadEnded.Reset(); for(auto& th : Threads)th.Create(call, this); }
			while(LoopFunction(os::AtomicIncrement(&LoopIndex)));
			if(SubThreadCount)AllSubThreadEnded.WaitSignal();
		}
	};
	Loop _(loop_body);
	return _.LoopIndex;
}

/**
 * @brief Daemon/Service/Agent Control
 * 
 */
enum _tagDaemonState
{
	DAEMON_STOPPED           = 0x1,
	DAEMON_START_PENDING     = 0x2,
	DAEMON_STOP_PENDING      = 0x3,
	DAEMON_RUNNING           = 0x4,
	DAEMON_CONTINUE_PENDING  = 0x5,
	DAEMON_PAUSE_PENDING     = 0x6,
	DAEMON_PAUSED            = 0x7,

	DAEMON_CONTROL_STOP		 = 0x11,
	DAEMON_CONTROL_PAUSE	 ,
	DAEMON_CONTROL_CONTINUE	 ,
	
};


/**
 * @brief DelayedGarbageCollection 
 * 
 * singleton
 */
class DelayedGarbageCollection	
{
public:
	typedef void (*LPFUNC_DELETION)(LPVOID x);
protected:
	static DWORD _DeletionThread(LPVOID);
	static void	DeleteObject(LPCVOID x, DWORD TTL_msec, LPFUNC_DELETION delete_func);
public:
	template<typename OBJ>
	static void DeleteObj(OBJ * ptr, int TTL_msec)
	{	struct _func{ static void delete_func(LPVOID x){ _SafeDel_ConstPtr((OBJ *)x); } };
		DeleteObject(ptr,TTL_msec,_func::delete_func);
	}
	template<typename OBJ>
	static void ReleaseObj(OBJ * ptr, int TTL_msec)
	{	struct _func{ static void release_func(LPVOID x){ ((OBJ *)x)->Release(); } };
		DeleteObject(ptr,TTL_msec,_func::release_func);
	}
	template<typename OBJ>
	static void DeleteArray(OBJ * ptr, int TTL_msec)
	{	struct _func{ static void delete_func(LPVOID x){ _SafeDelArray_ConstPtr((OBJ *)x); } };
		DeleteObject(ptr,TTL_msec,_func::delete_func);
	}
	static void Delete32AL(LPVOID ptr, int TTL_msec)
	{	struct _func{ static void delete_func(LPVOID x){ _SafeFree32AL_ConstPtr(x); } };
		DeleteObject(ptr,TTL_msec,_func::delete_func);
	}
	static void Delete(LPVOID ptr, int TTL_msec, LPFUNC_DELETION dfunc )
	{	DeleteObject(ptr,TTL_msec,dfunc);
	}
	static void Exit();
	static void Flush();
};

#define _SafeDel_Delayed(x, TTL_msec)		{ if(x){ os::DelayedGarbageCollection::DeleteObj(x,TTL_msec); x=nullptr; } }
#define _SafeDelArray_Delayed(x,TTL_msec)	{ if(x){ os::DelayedGarbageCollection::DeleteArray(x,TTL_msec); x=nullptr; } }
#define _SafeFree32AL_Delayed(x,TTL_msec)	{ if(x){ os::DelayedGarbageCollection::Delete32AL(x,TTL_msec); x=nullptr; } }
#define _SafeRelease_Delayed(x, TTL_msec)	{ if(x){ os::DelayedGarbageCollection::ReleaseObj(x,TTL_msec); x=nullptr; } }


namespace _details
{
template<typename t_MTMutable>
class _TSM_Updater
{
	typedef typename std::remove_reference_t<t_MTMutable>::RRCD t_RRCD;

	t_RRCD*				_Cloned;
	t_MTMutable&		_MTM;
	bool				_UpdateBegin;
public:
	_TSM_Updater(t_MTMutable& x, bool just_try = false):_MTM(x){ _UpdateBegin = _MTM._BeginUpdate(just_try); _Cloned = nullptr; }
	~_TSM_Updater(){ if(_UpdateBegin)Commit(); }

	bool		IsUpdating() const { return _UpdateBegin; }
	bool		IsModified() const { return (bool)_Cloned; }
	const auto&	GetUnmodified() const { return _MTM._ConstObject(); }
	auto&		Get(){ ASSERT(_UpdateBegin); ReadyModify(); return _Cloned->Object; }
	
	bool		ReadyModify(bool from_empty = false){ if(!_Cloned)_Cloned = from_empty?_MTM._CreateNew():_MTM._Clone(); return (bool)_Cloned; }
	void		Revert(){ ASSERT(_UpdateBegin); _SafeDel(_Cloned); _MTM._EndUpdate(nullptr); _UpdateBegin = false; }
	void		Commit(){ ASSERT(_UpdateBegin); _MTM._EndUpdate(_Cloned); _UpdateBegin = false; }
	auto*		operator ->(){ ASSERT(_UpdateBegin); ReadyModify(); return &_Cloned->Object; }
};

extern LPVOID& RRCD_Holder_GetLastEntry();

template<typename t_MTMutable>
struct RRCD_Holder
{
	typedef typename std::remove_reference_t<t_MTMutable>::RRCD t_RRCD;
	t_RRCD* rrcd;

#if defined(PLATFORM_DEBUG_BUILD)
	LPCVOID   mtm_obj;
	RRCD_Holder(const t_MTMutable& x){ mtm_obj = &x; rrcd = nullptr; RRCD_Holder_GetLastEntry() = this; }
#else
	RRCD_Holder(){ rrcd = nullptr; RRCD_Holder_GetLastEntry() = this; }
#endif
	~RRCD_Holder(){ _SafeRelease(rrcd); }
};
} // namespace _details


//////////////////////////////////////////////////////////////////
// A tricky thread-safe wrapper for extreme non-blocking read-only preformance while allowing multi-thread updating
// A read-only instance is obtained from ThreadSafeMutable::GetImmutable. Each call should have a cooresponded
// prerequisite THREADSAFEMUTABLE_SCOPE(x) to control the reference counting of reading instance.
// Updating is done through THREADSAFEMUTABLE_UPDATE by creating a new instance for reading access.
template<class T>
class ThreadSafeMutable
{
public:
	template<typename t_MTMutable>
	friend class _details::_TSM_Updater;
	struct RRCD // ReadRefCounted
	{
		volatile int	RefCo;
		T				Object;
		RRCD(){ RefCo = 1; }
		RRCD(const RRCD& x):Object(x.Object){ RefCo = 1; }
		void Release(){ if(os::AtomicDecrement(&RefCo)==0){ auto* t=this; _SafeDel_Delayed(t, 10); } }
	};

protected:
	typedef RRCD* LPRRCD;
	os::CriticalSection _cs_update;
	os::CriticalSection	_cs_swap;
	volatile LPRRCD		_p;
#if defined(PLATFORM_DEBUG_BUILD)
	bool				_bModifying = false;
#endif
protected:
	const T&	_ConstObject() const { static const T _t; return _p?_p->Object:_t; }
	bool		_BeginUpdate(bool just_try = false)
				{
					if(just_try){ if(!_cs_update.TryLock())return false; }
					else{ _cs_update.Lock(); }
#if defined(PLATFORM_DEBUG_BUILD)
					ASSERT(!_bModifying);
					_bModifying = true;
#endif
					return true;
				}
	void		_EndUpdate(RRCD* pNew = nullptr)/* nullptr indicates no change */
				{
					if(pNew)
					{	RRCD* pOld = _p;
						EnterCSBlock(_cs_swap);
						_p = pNew;
						_SafeRelease(pOld); 
					}
#if defined(PLATFORM_DEBUG_BUILD)
					_bModifying = false;
#endif
					_cs_update.Unlock();
				}
	RRCD*		_Clone() const { return _p?_New(RRCD(*_p)):_New(RRCD); }
	RRCD*		_CreateNew() const { return _New(RRCD); }
public:
	typedef T	t_Object;
	ThreadSafeMutable()
	{
		_p = nullptr; 
#if defined(PLATFORM_DEBUG_BUILD)
		_bModifying = false;
#endif		
	}
	~ThreadSafeMutable(){ Clear(); ASSERT(!_bModifying); }

	const T&	GetImmutable() const 
				{
					typedef _details::RRCD_Holder<ThreadSafeMutable>* LPHOLDER;
					auto& h = (LPHOLDER&)_details::RRCD_Holder_GetLastEntry();
					ASSERT(h); // add THREADSAFEMUTABLE_SCOPE(obj) before calling Get()
					ASSERT(h->mtm_obj == this);
					LPRRCD ret;
					{	EnterCSBlock(_cs_swap);
						ret = _p;
						if(!ret){ h = nullptr; return _ConstObject(); }
						os::AtomicIncrement(&ret->RefCo);
					}
					h->rrcd = ret;
					h = nullptr;
					return ret->Object;
				}

	void		Clear(){ EnterCSBlock(_cs_update); _SafeRelease(_p); }
	bool		IsEmpty() const { return _p == nullptr; }
	
	//unsafe in multi-thread
	T&			GetUnsafeMutable(){ ASSERT(_cs_update.IsLockedByCurrentThread()); ASSERT(_p); return _p->Object; }
};

#define THREADSAFEMUTABLE_LOCK(org_obj)				EnterCSBlock(*(os::CriticalSection*)&org_obj)
#define THREADSAFEMUTABLE_UPDATE(org_obj, new_obj)	os::_details::_TSM_Updater<decltype(org_obj)> new_obj(org_obj, false)
#define THREADSAFEMUTABLE_TRYUPDATE(org_obj, new_obj)	os::_details::_TSM_Updater<decltype(org_obj)> new_obj(org_obj, true)

#if defined(PLATFORM_DEBUG_BUILD)
#define THREADSAFEMUTABLE_SCOPE(obj)			os::_details::RRCD_Holder<decltype(obj)> MARCO_JOIN(_RRCD_Holder_,__COUNTER__)(obj);
#else
#define THREADSAFEMUTABLE_SCOPE(obj)			os::_details::RRCD_Holder<decltype(obj)> MARCO_JOIN(_RRCD_Holder_,__COUNTER__);
#endif

typedef void (*CONSOLEINPUT_CALLBACK)(LPSTR str, UINT len, LPVOID cookie);

class ConsolePrompt
{
	volatile int		__fgets_called = 0;
protected:
	os::Thread			_ConsoleInputThread;
	void				_ConsoleInput();

	CONSOLEINPUT_CALLBACK	_InputCallback = nullptr;
	LPVOID					_InputCallbackCookie = nullptr;
	UINT					_InputBufSize = 1024;

	typedef void (*_FuncRelaseCookie)(LPVOID c);
	_FuncRelaseCookie		_CookieRelease = nullptr;

public:
	void	Init(CONSOLEINPUT_CALLBACK on_input, LPVOID cookie = nullptr, UINT input_size_max = 1024);
	template<typename CB>
	void	Init(CB&& func, UINT input_size_max = 1024)
	{
		struct _on
		{	static void input(LPSTR str, UINT len, LPVOID cookie)
			{	(*(CB*)cookie)(str, len);
			}
			static void release(LPVOID cookie)
			{	_SafeDel_ConstPtr((CB*)cookie);
			}
		};
		_CookieRelease = _on::release;
		Init(&_on::input, _New(CB(func)), input_size_max);
	}
	bool	IsRunning() const { return _ConsoleInputThread.IsRunning(); }
	void	Term();
};

#if defined(PLATFORM_WIN)
class LaunchProcess
{
#if defined(PLATFORM_WIN)
	HANDLE hChildStdinRd, hChildStdinWrDup, 
		   hChildStdoutWr,hChildStdoutRdDup;

public:
	typedef void	(*FUNC_HOOKEDOUTPUT)(char* p, UINT len, LPVOID cookie);

protected:
	FUNC_HOOKEDOUTPUT	_Callback;
	LPVOID				_Callback_Cookie;
	DWORD				_Flag;
	os::Thread			_OutputHookThread;
	static DWORD		_OutputHookRoutine(LPVOID);
	void				_HookedOutput(char* p, UINT len);

protected:
	os::CriticalSection	_CCS;
	HANDLE				_hProcess;
	rt::String			_Output;
	int					_ExitCode;
	os::Timestamp		_ExecutionTime;		///< in msec
	os::Timestamp		_ExitTime;

	static void			_RemoveCarriageReturn(rt::String& output, const rt::String_Ref& add);
#endif

	void				_ClearAll();

public:
	enum
	{	FLAG_ROUTE_OUTPUT	= 0x1,
		FLAG_SAVE_OUTPUT	= 0x2,	///< retrieve by GetOutput/GetOutputLen
		FLAG_HIDE_WINDOW	= 0x4,
	};
	LaunchProcess();
	~LaunchProcess();
	void		SetOutputCallback(FUNC_HOOKEDOUTPUT func, LPVOID cookie);
	bool		Launch(LPCSTR cmdline, DWORD flag = FLAG_ROUTE_OUTPUT, LPCSTR pWorkDirectory = nullptr, LPCSTR pEnvVariableAddon = nullptr);  ///< pEnvVariableAddon is \0 seperated multiple strings (UTF8), ends with \0\0
	bool		WaitForEnding(DWORD timeout = INFINITE); ///< return false when timeout
	void		Terminate();
	bool		IsRunning();
	LPCSTR		GetOutput();
	UINT		GetOutputLen();
	void		CopyOutput(rt::String& out);
	bool		SendInput(const rt::String_Ref& str){ return str.IsEmpty()?true:SendInput(str.Begin(), (UINT)str.GetLength()); }
	bool		SendInput(LPCSTR p, UINT len);
	auto		GetExecutionTime() const { return _ExecutionTime; }	///< available after IsRunning() returns false!	
	auto		GetExitTime() const { return _ExitTime; }			///< available after IsRunning() returns false!	
	int			GetExitCode() const { return _ExitCode; }			///< available after IsRunning() returns false!
	bool		SendToStdin(LPCVOID str, UINT len);
};

#endif
/** @}*/
} // namespace os
/** @}*/