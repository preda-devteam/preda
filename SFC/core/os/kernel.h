#pragma once
/**
 * @file kernel.h
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
#include "../rt/buffer_type.h"
#include "../rt/small_math.h"
#include <time.h>

#if defined(PLATFORM_WIN)
#include <intrin.h> 

#else
#include <sys/time.h>

#if defined (PLATFORM_ANDROID)
#include <asm-generic/errno.h>
#elif defined (PLATFORM_MAC) || defined (PLATFORM_IOS)
#include <mach/mach_time.h>
//#include <errno.h>
#endif

#endif

#define ASSERT_STATIC_NOT_IMPLMENTED	static_assert(0, "Not Implmentated.")

namespace os
{
/** \defgroup kernel kernel
 * @ingroup os
 *  @{
 */
#pragma pack(1)
/**
 * @brief in msec, 10^-3 
 * 
 */
struct TickCount		
{
#if defined (PLATFORM_IOS) || defined (PLATFORM_MAC)
	static struct mach_timebase_info __mach_tick_unit;
#endif
	static FORCEINL DWORD Get()
	{
#if defined(PLATFORM_WIN)
		return ::GetTickCount();
#elif defined (PLATFORM_IOS) || defined (PLATFORM_MAC)
		return (DWORD)(mach_absolute_time()*__mach_tick_unit.numer/__mach_tick_unit.denom);
#else
		timespec	ts;
		clock_gettime(CLOCK_MONOTONIC,&ts);
		return (DWORD)(ts.tv_sec*1000 + ts.tv_nsec/1000000);
#endif	
	}
	FORCEINL TickCount(DWORD x = 0){ _Tick = x; }
	FORCEINL operator DWORD () const { return _Tick; }
	FORCEINL DWORD operator = (DWORD tick){ _Tick = tick; return tick; }
	FORCEINL DWORD operator -- (){ return --_Tick;  }
	FORCEINL DWORD operator ++ (){ return ++_Tick;  }
	FORCEINL DWORD operator -- (int){ return _Tick--;  }
	FORCEINL DWORD operator ++ (int){ return _Tick++;  }
	FORCEINL void  operator -= (DWORD x){ _Tick-=x; }
	FORCEINL void  operator += (DWORD x){ _Tick+=x; }
	FORCEINL void  operator -= (int x){ _Tick-=x; }
	FORCEINL void  operator += (int x){ _Tick+=x; }
	FORCEINL void  LoadCurrentTick(){ _Tick = Get(); }
	FORCEINL int  TimeLapse(DWORD later) const // in msec
	{	if(_Tick <= later)return later - _Tick;
		else return (UINT)(0x100000000LL + later - _Tick);
	}
	FORCEINL int  TimeLapse() const { return TimeLapse(Get()); }
	FORCEINL int  TimeInterval()
	{	DWORD t = Get();
		DWORD ret = TimeLapse(t);
		_Tick = t;
		return ret;
	}
	DWORD _Tick;
};
#pragma pack()

/**
 * @brief in nanosecond 10^-9 (default), time elapsed excludes system sleep/standby/hibernation 
 * 
 */
class HighPerformanceCounter 
{
	LONGLONG		_Div;
#if defined(PLATFORM_WIN) || defined (PLATFORM_IOS) || defined (PLATFORM_MAC)
	bool			_bMul;
	LONGLONG		_Mul;
#endif
public:
	LONGLONG	Get() const
				{
				#if defined(PLATFORM_WIN)
						LONGLONG t;
						VERIFY(QueryPerformanceCounter((LARGE_INTEGER*)&t));
						return _bMul?_Mul*t:t/_Div;
				#elif defined (PLATFORM_IOS) || defined (PLATFORM_MAC)
						return _bMul?mach_absolute_time()*_Mul:mach_absolute_time()/_Div;
				#else
                
						timespec	ts;
						clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
						return (((ULONGLONG)ts.tv_sec)*1000000000LL + ts.tv_nsec)/_Div;
				#endif	
				}
	HighPerformanceCounter(){ SetOutputUnit(1); }
	LONGLONG	TimeLapse(LONGLONG later) const { return later - _Count; }
	LONGLONG	TimeLapse() const{ return TimeLapse(Get()); }
	LONGLONG	Restart(){ ULONGLONG later = Get(); later -= _Count; _Count += later; return later; }
	void		Restart(LONGLONG unix_time_msec){ _Count = Get() - unix_time_msec*1000000ULL; }
	void		LoadCurrentCount(){ _Count = Get(); }
	operator	LONGLONG () const { return _Count; }
	void		SetOutputUnit(LONGLONG u); // in nanosecond 10^-9s
	void		SetOutputMillisecond(){ SetOutputUnit(1000000LL); }
protected:
	LONGLONG	_Count;
};

} // namespace os


namespace os
{
#ifndef PLATFORM_DISABLE_LOG
enum LogPrefixItemCode
{
    _LOG_TIME = 10001, ///< in "yyyy/MM/dd hh:mm:ss", e.g. 2013/01/11 16:39:45
    _LOG_FILE, ///< e.g. Main.cpp
    _LOG_LINE, ///< e.g. 201
    _LOG_FUNC, ///< e.g. main
    _LOG_MEM, ///< in MB, e.g. 5217MB
    _LOG_CPU,
};

struct LogPrefix
{
    struct _item
    {   _item() : code(0) {}
        rt::String string;
        int code;
    };
	rt::BufferEx<_item> items;

	LogPrefix() = default;
	LogPrefix(const LogPrefix& x){ operator = (x); }
	LogPrefix& operator << (LogPrefixItemCode code);
    LogPrefix& operator << (char c);
	LogPrefix& operator << (LPCSTR s);
    const LogPrefix& operator = (const LogPrefix& x);
};

#define _LOGFORMAT (os::LogPrefix())

namespace _details
{
	void __ConsoleLogWrite(LPCSTR log, int type);

	typedef void (*FUNC_CONSOLE_LOG_WRITE)(LPCSTR log, int type, LPVOID cookie);
	typedef void (*FUNC_LOG_WRITE)(LPCSTR log, LPCSTR file, int line_num, LPCSTR func, int type, LPVOID cookie);

	extern void SetConsoleLogWriteFunction(FUNC_CONSOLE_LOG_WRITE func = nullptr, LPVOID cookie = nullptr);
	extern void SetLogWriteFunction(FUNC_LOG_WRITE func = nullptr, LPVOID cookie = nullptr);
	extern void LogWriteDefault(LPCSTR log, LPCSTR file, int line_num, LPCSTR func, int type, LPVOID);
};

extern void LogWrite(LPCSTR log, LPCSTR file, int line_num, LPCSTR func, int type);
extern void LogWriteFlush();
#endif // PLATFORM_DISABLE_LOG

namespace _details
{	extern LPCSTR	_UnitTestOutputFilePrefix;
} // namespace _details

extern void SetLogConsoleTitle(LPCSTR title);
extern bool SetLogFile(LPCSTR filename, bool append = true); // filename = nullptr to disable Log File
extern void SetLogConsolePrompt(LPCSTR prompt);
extern rt::String_Ref GetLogFilename();

#if defined(PLATFORM_IOS) || defined(PLATFORM_MAC)
} // namespace os
extern bool _objc_randomize(unsigned char* p, size_t size);
namespace os
{
INLFUNC bool Randomize(LPVOID p, UINT len){ return _objc_randomize((unsigned char*)p, len); }
#else
extern bool Randomize(LPVOID p, UINT len);
#endif

extern int  GetLastError();
extern void GetHostName(rt::String& name);
extern void GetLogonUserName(rt::String& name);
extern void GetExecutableFilename(rt::String& name);
extern void GetCPUBrand(rt::String& brand);
extern UINT GetNumberOfProcessors();
extern UINT GetNumberOfPhysicalProcessors();
extern void CPUID(unsigned i, unsigned regs[4]);
extern void GetOSVersion(rt::String& name, bool friendly_info = true);
extern int  GetDimensionOfScreens(rt::Vec2i* pDim, UINT dim_size = 1); ///< return # of screens
extern bool GetSystemMemoryInfo(ULONGLONG* free, ULONGLONG* total = nullptr);	///< in bytes
extern bool GetProcessMemoryLoad(SIZE_T* vmem, SIZE_T* phy_mem);
extern bool GetProcessorTimes(ULONGLONG* busy, ULONGLONG* total = nullptr);	///< msec, {idle, total}
extern UINT GetPowerState(bool * pHasBattery = nullptr, bool* pPlugged = nullptr);		///< precentage of battery remaining
extern void GetDeviceModel(rt::String& model);
extern bool Sleep(DWORD msec = INFINITE, const bool* interrupt_flag = nullptr); // false if sleep is interrupted 
extern void Halt();

extern LPVOID VMAlloc(SIZE_T length);
extern void	  VMFree(LPVOID ptr, SIZE_T size);
extern bool	  VMLock(LPVOID ptr, SIZE_T size);		///< ensure not page fault
extern bool	  VMUnlock(LPVOID ptr, SIZE_T size);

extern bool	  CreateGUID(BYTE id[16]);
extern HANDLE LoadDynamicLibrary(LPCSTR fn);
extern void   UnloadDynamicLibrary(HANDLE h);
extern LPVOID GetDynamicLibrarySymbol(HANDLE dll, LPCSTR fn);
extern bool	  GetDeviceUID(rt::String& uid);
extern DWORD  GetRandomSeed();

extern LPCSTR GetBuildSpecificationString();
extern void	  BruteforceExit();

#if defined(PLATFORM_WIN)

extern bool LoadRegKeyPath(HKEY root, LPCWSTR regkey, LPCWSTR value_name, LPWSTR textbuf, DWORD bufsize, bool resolve_env = false);
extern bool LoadRegKeyString(HKEY root, LPCWSTR regkey, LPCWSTR value_name, LPWSTR textbuf, DWORD bufsize);
extern INT  LoadRegKeyInt(HKEY root, LPCWSTR regkey, LPCWSTR value_name, INT default_val = 0);
extern bool SaveRegKeyString(HKEY root, LPCWSTR regkey, LPCWSTR value_name, LPCWSTR string);
extern bool SaveRegKeyInt(HKEY root, LPCWSTR regkey, LPCWSTR value_name, INT val);
extern void DeleteRegKeyValue(HKEY root, LPCWSTR regkey, LPCWSTR value_name);
extern bool CreateRegKey(HKEY root, LPCWSTR regkey);
extern void SetDataBreakPoint(LPCVOID addr, UINT slot, UINT bitwidth = 32, bool write = true, bool read = false, bool exec = false);

#endif

extern bool	OpenDefaultBrowser(LPCSTR url);
extern void SetPreferenceLocation(const rt::String_Ref& app_name);
extern INT	LoadPreference(const rt::String_Ref& keyname, INT   default_value);
extern bool	SavePreference(const rt::String_Ref& keyname, INT   value);
extern bool	LoadPreferenceString(const rt::String_Ref& keyname, rt::String& out, const rt::String_Ref& default_value = nullptr);
extern bool	SavePreferenceString(const rt::String_Ref& keyname, const rt::String_Ref& value);

extern bool EncryptData(rt::String& cipertext, const rt::String_Ref& plaintext);
extern bool DecryptData(rt::String& plaintext, const rt::String_Ref& cipertext);


enum _tagProcessPriority
{
	PROCPRIO_REALTIME = 2,
	PROCPRIO_HIGH = 1,
	PROCPRIO_NORMAL = 0,
	PROCPRIO_LOW = -1,
	PROCPRIO_IDLE = -2,
};

extern void		SetProcessPriority(int prio = PROCPRIO_HIGH);
extern int		SearchProcess(LPCSTR base_name, bool substr_match = true);	///< -1 for not found
extern int		SearchProcess(LPCSTR base_name, int* pProcessIds, UINT ProcessIdSize, bool substr_match = true);	///< 0 for not found
extern int		GetProcessId();
extern bool		TerminateProcess(int process_id);
extern void		SetAppTitle(LPCSTR title);

#pragma pack(1)
/**
 * @brief UNIX time (UTC) in millisecond, compatible to javascript's (new Date(x))
 * 
 */
struct Timestamp	
{
	struct Fields
	{
		int Year;
		int Month;
		int Day;			///< Day of Month
		int DayOfWeek;		///< Sunday is 0
		int Hour;
		int Minute;
		int Second;
		int MillSecond;

		Fields(int year, int mon, int day, int hour = 0, int min = 0, int sec = 0, int msec = 0):Year(year),Month(mon),Day(day),DayOfWeek(0),Hour(hour),Minute(min),Second(sec),MillSecond(msec){}
		Fields(){}
		explicit Fields(const rt::String_Ref& s){ FromString(s); }

		void			SetDateTime(int year, int mon, int day, int hour = 0, int min = 0, int sec = 0, int msec = 0){ Year = year; Month = mon; Day = day; DayOfWeek = 0; Hour = hour; Minute = min; Second = sec; MillSecond = msec; }
		WORD			GetDosDate()const{ return (WORD)(Day | (Month<<5) | ((Year-1980)<<9)); }
		WORD			GetDosTime()const{ return (WORD)(((Second + (MillSecond + 500)/1000)>>1) | (Minute<<5) | (Hour<<11)); }
		void			SetDosTime(WORD date, WORD timex){ SetDateTime((date>>9) + 1980, (date>>5)&0xf, date&0x1f, timex>>11, (timex>>5)&0x3f, timex&0x1f); }

		rt::String_Ref	GetMonthName() const { return Timestamp::GetMonthName(Month); }
		rt::String_Ref	GetDayOfWeekName() const { return Timestamp::GetDayOfWeekName(DayOfWeek); }

		int				FromString(const rt::String_Ref& s, bool low_bound = true); ///< >0 # of fields parsed ok, <0 error. -1: only 1 field found, others not a number in parsed fields
		bool			FromInternetTimeFormat(const rt::String_Ref& s); ///< RFC 1123 format, //Tue, 15 Nov 1994 12:45:26 GMT
		UINT			ToInternetTimeFormat(LPSTR buf) const;	///< RFC 1123 format, buf size > 30, zero-terminated , //Tue, 15 Nov 1994 12:45:26 GMT
	};

	LONGLONG	_Timestamp;

	Timestamp(){}
	explicit	Timestamp(const Fields& f, bool local = true){ local?SetLocalDateTime(f):SetDateTime(f); }
	explicit	Timestamp(LONGLONG x):_Timestamp(x){}
	operator	LONGLONG () const { return _Timestamp; }
	void		LoadCurrentTime(){ _Timestamp = Get(); }
	ULONGLONG	operator = (ULONGLONG ts){ _Timestamp = ts; return ts; }

	LONGLONG	TimeLapse() const { return TimeLapse(Get()); }
	LONGLONG	TimeLapse(LONGLONG t) const { return t - _Timestamp; }

	bool		GetDateTime(Fields& f) const;	///< GMT time
	bool		GetLocalDateTime(Fields& f) const;	///< Local Time
	bool		GetDateTime(Fields& f, int Timezone) const;	///< GMT time plus a timezone

	Fields		GetDateTime() const { Fields f; GetDateTime(f); return f; }	///< GMT time
	Fields		GetLocalDateTime() const { Fields f; GetLocalDateTime(f); return f; }	///< Local Time
	Fields		GetDateTime(int Timezone) const { Fields f; GetDateTime(f,Timezone); return f; }	///< Local Time
	
	bool		SetDateTime(const Fields& f);
	bool		SetLocalDateTime(const Fields& f);
	bool		SetDateTime(const Fields& f, int Timezone);

	bool		SetDateTime(const rt::String_Ref& f)
				{	Fields fd; 
					int r=fd.FromString(f);
					if(r>0)return SetDateTime(Fields(f));
					if(r==-1)return f.ToNumber(_Timestamp)>0;
					return false;
				}
	bool		SetDateTime(const rt::String_Ref& f, int Timezone)
				{	Fields fd;
					int r=fd.FromString(f);
					if(r>0)return SetDateTime(fd, Timezone);
					LONGLONG	t;
					if(r==-1 && f.ToNumber(t)>0)
					{	_Timestamp = t - Timezone*3600000LL;
						return true;
					}
					return false;
				}
	bool		SetLocalDateTime(const rt::String_Ref& f){ return SetLocalDateTime(Fields(f)); }

	bool		SetDateTime(int year, int mon, int day, int hour = 0, int min = 0, int sec = 0, int millsecond = 0){ return SetDateTime(Fields(year, mon, day, hour, min, sec, millsecond)); }
	bool		SetLocalDateTime(int year, int mon, int day, int hour = 0, int min = 0, int sec = 0, int millsecond = 0){ return SetLocalDateTime(Fields(year, mon, day, hour, min, sec, millsecond)); }
	void		ShiftDays(int days){ _Timestamp += days*24*3600000LL; }
	void		ShiftHours(int hours){ _Timestamp += hours*3600000LL; }
	void		ShiftWeeks(int weeks){ _Timestamp += weeks*7*24*3600000LL; }
	void		ShiftForward(const rt::String_Ref& timespan){ _Timestamp += ParseTimeSpan(timespan); }
	void		ShiftBackward(const rt::String_Ref& timespan){ _Timestamp -= ParseTimeSpan(timespan); }

	LONGLONG	Difference(const Timestamp& x) const { return _Timestamp - x._Timestamp; } ///< this - x in millsecond
	LONGLONG	DifferenceDays(const Timestamp& x) const { return (_Timestamp - x._Timestamp) / (24 * 3600000LL); } ///< this - x in days

	static int			GetMonthFromDays(int DaysSinceYear, int year);
	static bool			IsLeapYear(int year){ return (((year&0x3)==0) && (year%100)) || ((year%400)==0); }
	static LONGLONG 	DaysSince1970(int year){ year--; return 365LL * year + (year / 400) - (year/100) + (year / 4) - 719162; }
	static int			DaysSinceYear(int year,int month,int day)  ///< # of days since the begining of year
						{	static const int days[2][12] = {{ 0,31,59,90,120,151,181,212,243,273,304,334},{ 0,31,60,91,121,152,182,213,244,274,305,335}};
							return days[IsLeapYear(year)][month-1] + day - 1;
						}
	static int			GetDayOfWeek(int year,int month,int day){ return (DaysSince1970(year) + DaysSinceYear(year,month,day)-3)%7; }
	static int			GetDayOfMonthMax(int year, int month)
						{	static const int dm[] = {31,28,31, 30,31,30, 31,31,30, 31,30,31};
							ASSERT(month>=1 && month<=12);
							return dm[month-1] + (int)((month==2)&&IsLeapYear(year));
						}
	static auto			GetMonthName(int month) -> rt::String_Ref;	///< base 1
	static int			ParseMonthName(LPCSTR b);	///< base 1
	static int			ParseWeekdayName(LPCSTR b);

	static auto			GetDayOfWeekName(int day_of_week) -> rt::String_Ref; ///< base 0, Sunday is 0
	static LONGLONG		ParseTimeSpan(const rt::String_Ref& x);

	static Timestamp	Get()
						{
						#if defined(PLATFORM_WIN)
							LONGLONG ft;
							GetSystemTimeAsFileTime((FILETIME*)&ft);
							return Timestamp(ft/10000 - 11644473600000LL);
						#elif defined (PLATFORM_IOS) || defined (PLATFORM_MAC)
							struct timeval time;
							gettimeofday(&time, NULL);
							return Timestamp((time.tv_sec * 1000) + (time.tv_usec / 1000));
						#else
							timespec	ts;
							clock_gettime(CLOCK_REALTIME,&ts);
							return Timestamp(ts.tv_sec*1000 + ts.tv_nsec/1000000);
						#endif	
						}

	static Fields		DateTime(){ return Get().GetDateTime(); }
	static Fields		LocalDateTime(){ return Get().GetLocalDateTime(); }
};
#pragma pack()
template<typename ostream>
INLFUNC ostream& operator << (ostream& s, const os::Timestamp::Fields& f)
{	s << f.Year	<<'/'<< 
		rt::tos::Number(f.Month).RightAlign(2,'0') <<'/'<<
		rt::tos::Number(f.Day).RightAlign(2,'0')<<' '<<
		rt::tos::Number(f.Hour).RightAlign(2,'0')<<':'<<
		rt::tos::Number(f.Minute).RightAlign(2,'0')<<':'<<
		rt::tos::Number(f.Second).RightAlign(2,'0')<<'.'<<
		rt::tos::Number(f.MillSecond).RightAlign(3,'0');
	return s;
};
} // namespace os

namespace rt
{
namespace tos
{
template<bool show_msec = true, bool show_date = true, char sep_date = '/', char sep_time = ':'>
struct Timestamp:public ::rt::tos::S_<1, 70>
{
	Timestamp(const os::Timestamp::Fields & x)
	{	typedef ::rt::tos::S_<1,70> _SC;
		if(show_date)
		{
			if(show_msec)
			{	_SC::_len = sprintf(_string,"%04d%c%02d%c%02d %02d%c%02d%c%02d.%03d", x.Year, sep_date, x.Month, sep_date, x.Day,x.Hour,sep_time,x.Minute,sep_time,x.Second,x.MillSecond);
			}
			else
			{	_SC::_len = sprintf(_string,"%04d%c%02d%c%02d %02d%c%02d%c%02d", x.Year, sep_date, x.Month, sep_date, x.Day,x.Hour,sep_time,x.Minute,sep_time,x.Second);
			}	
		}
		else
		{
			if(show_msec)
			{	_SC::_len = sprintf(_string,"%02d%c%02d%c%02d.%03d", x.Hour,sep_time,x.Minute,sep_time,x.Second,x.MillSecond);
			}
			else
			{	_SC::_len = sprintf(_string,"%02d%c%02d%c%02d", x.Hour,sep_time,x.Minute,sep_time,x.Second);
			}
		}
	}
	Timestamp(LONGLONG timestamp, bool local_time = true)
		:Timestamp(local_time?os::Timestamp(timestamp).GetLocalDateTime():os::Timestamp(timestamp).GetDateTime())
	{}
};

template<char sep_date = '/'>
struct TimestampDate:public ::rt::tos::S_<1, 70>
{
	TimestampDate(const os::Timestamp::Fields & x)
	{	typedef ::rt::tos::S_<1,70> _SC;
		_SC::_len = sprintf(_string,"%04d%c%02d%c%02d", x.Year, sep_date, x.Month, sep_date, x.Day);
	}
	TimestampDate(LONGLONG timestamp, bool local_time = true)
		:TimestampDate(local_time?os::Timestamp(timestamp).GetLocalDateTime():os::Timestamp(timestamp).GetDateTime())
	{}
};

}} // namespace rt::tos


namespace os
{

/**
 * @brief Console Progress Indicator 
 * 
 */
class ConsoleProgressIndicator
{
	rt::String	_Hint;
	Timestamp	_StartTime;
	Timestamp	_LastDisplay;
	ULONGLONG	_Total;
	ULONGLONG	_Prog;
	void		_Display();
public:
	ConsoleProgressIndicator(ULONGLONG total, LPCSTR hint = nullptr);
	~ConsoleProgressIndicator();
	void One(){ _Prog++; _Display(); }
	void SetProgress(ULONGLONG x){ _Prog = x; _Display(); }
};

// progress reporting for recursive tasks
class ProgressReport
{
public:
	class [[nodiscard]] Scope
	{
		friend class ProgressReport;
		ProgressReport&	Report;
		double			TotalBase;
		double			ScaleBase;
		uint64_t		RangeBase;
		Scope*			ScopeBase;
		Scope(uint64_t scope_range, ProgressReport& c);
		Scope(const Scope&x) = delete;
		Scope(Scope&&x) = delete;
	public:
		~Scope();
		operator ProgressReport&(){ return Report; }
		operator ProgressReport*(){ return &Report; }
	};

protected:
	typedef void (*FUNC_CALLBACK)(const ProgressReport& x);
	mutable bool		_Aborted;
	double				_Total;	// [0, 1]
	uint64_t			_StartTime;
	double				_Scale;
	uint64_t			_Range;
	Scope*				_pCurrentScope;

	LPCVOID				_pCallback;
	uint32_t			_CallbackInterval;
	mutable uint64_t	_LastCallBackTime;
	FUNC_CALLBACK		_CallFunc;
	void				_InvokeCallback(bool ignore_interval = false) const;

public:
	template<typename CALLBACK_FUNC>
	void SetCallback(CALLBACK_FUNC&& x, uint32_t invoke_interval_msec = 1000)
	{	struct _cb
		{	static void callback(const ProgressReport& x)
			{	
				((FUNC_CALLBACK)x._pCallback)(x);
			}
		};
		_CallFunc = _cb::callback;
		_pCallback = &x;
		_CallbackInterval = invoke_interval_msec;
		_LastCallBackTime = 0;
		_InvokeCallback(true);
	};

	void		Reset(uint64_t progress_range);
	Scope		SubScope(uint64_t scope_range){ return ProgressReport::Scope(scope_range, *this); }
	double		GetProgress() const { return _Total; } // [0, 1]
	uint32_t	GetTimeElapsed() const { return (uint32_t)(os::Timestamp::Get() - _StartTime); }
	uint32_t	GetTimeRemaining() const { return _Total>DBL_EPSILON?(uint32_t)(GetTimeElapsed()/_Total*(1.0 - _Total)):0; }
	void		Restart(){ _StartTime = os::Timestamp::Get(); }
	ProgressReport(uint32_t progress_range = 100){ Reset(progress_range); }

	// call by working function
	void		SetProgressRange(uint64_t range); // default is 100
	void		SetProgress(uint64_t progress); // in [0, scope_range]
	void		MakeProgress(uint64_t added = 1){ _Total += _Scale*added; _InvokeCallback(); }
};


/**
 * @brief Date32, representing only days  
 * 
 */
enum tagDATEFMT
{	DATEFMT_MMDDYYYY = 0x010002,
	DATEFMT_YYYYMMDD = 0x020100
};

#pragma pack(1)
struct Date32
{
	UINT	_Date; ///< year in 0xffff0000, month in 0xff00, day in 0xff

	INLFUNC Date32(){}
	INLFUNC Date32(const Date32& x){ _Date = x._Date; }
	INLFUNC Date32(int year, int mon, int day){ SetDate(year, mon, day); }

	template<typename t_Timestamp>
	INLFUNC explicit Date32(const t_Timestamp& tm){ SetDate(tm); }

	INLFUNC int		GetYear() const { return _Date>>16; }
	INLFUNC int		GetMonth() const { return (_Date>>8)&0xff; }
	INLFUNC int		GetDay() const { return _Date&0xff; }
	INLFUNC bool	IsMonthEqual(const Date32& x) const { return ((_Date^x._Date)&0xffffff00) == 0; }
 
	INLFUNC void	SetDate(int year, int mon, int day){ _Date = (year<<16) | (mon<<8) | day; }
	template<typename T>
	INLFUNC void	SetDate(const T& x){ SetDate(x.Year, x.Month, x.Day); }
	INLFUNC void	SetYear(int y){ ASSERT(y>0); _Date = (_Date&0xffff) | (y<<16); }
	INLFUNC void	SetMonth(int m){ ASSERT(m>=0&&m<=13); _Date = (_Date&0xffff00ff) | (m<<8); }
	INLFUNC void	SetDay(int d){ ASSERT(d>=0&&d<=32); _Date = (_Date&0xffffff00) | d; }
	bool			FromString(const rt::String_Ref&date_string_in , UINT format = DATEFMT_YYYYMMDD)
	{	int v[3] = { 0,0,0 };
		if(date_string_in.IsEmpty())return false;
		LPCSTR date_string = date_string_in.Begin();
		while((*date_string)>='0' && (*date_string)<='9'){ v[0] = v[0]*10 + (*date_string - '0');	date_string++; } date_string++; 
		while((*date_string)>='0' && (*date_string)<='9'){ v[1] = v[1]*10 + (*date_string - '0');	date_string++; } date_string++; 
		while((*date_string)>='0' && (*date_string)<='9'){ v[2] = v[2]*10 + (*date_string - '0');	date_string++; }
		if(v[0]&&v[1]&&v[2]){ SetDate(v[format&0xff],v[(format>>8)&0xff],v[(format>>16)&0xff]); return true; }else return false;
	}
	INLFUNC Date32&	LoadCurrentDate(bool _local = true){ auto tm = os::Timestamp::Get(); SetDate(_local?tm.GetLocalDateTime():tm.GetDateTime()); return *this; }
	INLFUNC const	Date32& operator = (const Date32& i){ _Date = i._Date; return i; }
	INLFUNC bool	operator < (const Date32& x) const { return _Date < x._Date; }
	INLFUNC bool	operator == (const Date32& x) const { return _Date == x._Date; }
	INLFUNC bool	operator != (const Date32& x) const { return _Date != x._Date; }
	INLFUNC bool	operator > (const Date32& x) const { return _Date > x._Date; }
	INLFUNC bool	operator >= (const Date32& x) const { return _Date >= x._Date; }
	INLFUNC bool	operator <= (const Date32& x) const { return _Date <= x._Date; }
	INLFUNC int		operator - (const Date32& x) const{ return (int)((os::Timestamp(os::Timestamp::Fields(GetYear(), GetMonth(), GetDay())) - os::Timestamp(os::Timestamp::Fields(x.GetYear(), x.GetMonth(), x.GetDay())))/(24LL*3600*1000)); }
	                                                                                                                                                                   
	INLFUNC Date32& operator += (int x)
	{	if(x<0)*this -= (-x);
		else for(int i = 0; i < x; i++)(*this)++;
		return *this;
	}
	INLFUNC Date32& operator -= (int x)
	{	if(x<0)*this += (-x);
		else for (int i = 0; i < x; i++)(*this)--;
		return *this;
	}
	INLFUNC Date32 NextYear() const { return Date32(GetYear()+1, 1, 1); }
	INLFUNC Date32 LastYear() const { return Date32(GetYear()-1, 1, 1); }
	INLFUNC Date32 NextDay() const
	{	Date32 ret;
		if (GetDay() != os::Timestamp::GetDayOfMonthMax(GetYear(), GetMonth())){ ret._Date = _Date+1; }
		else
		{
			ret._Date = (GetMonth() != 12) ? ((_Date & 0xffffff00) + 0x101) : ((_Date & 0xffff0000) + 0x10101);
		}
		return ret;
	}
	INLFUNC Date32 LastDay() const
	{	Date32 ret;
		if(GetDay() != 1){ ret._Date = _Date - 1;	}
		else
		{	ret._Date = (GetMonth() !=1)?(_Date&0xffffff00) - 0x100 + os::Timestamp::GetDayOfMonthMax(GetYear(), GetMonth()-1):(_Date&0xffff0000) - 0x10000 + 31 + (12<<8);	}
		return ret;
	}
	INLFUNC Date32 NextMonth() const ///< day will be 1
	{	int m = GetMonth();
		return Date32(GetYear() + m/12, 1 + m%12, 1);
	}
	INLFUNC Date32 LastMonth() const ///< day will be 1
	{	int m = GetMonth();
		return Date32(GetYear() - (13-m)/12, 1 + (10+m)%12, 1);
	}
	INLFUNC Date32& operator -- (int)
	{	if(GetDay() != 1){ _Date--;	}
		else
		{	_Date = (GetMonth() !=1)?(_Date&0xffffff00) - 0x100 + os::Timestamp::GetDayOfMonthMax(GetYear(), GetMonth()-1):(_Date&0xffff0000) - 0x10000 + 31 + (12<<8);	}
		return *this;
	}
	INLFUNC Date32& operator ++ (int)
	{
		if(GetDay() != os::Timestamp::GetDayOfMonthMax(GetYear(), GetMonth())){ _Date++; }
		else
		{
			_Date = (GetMonth() != 12) ? ((_Date & 0xffffff00) + 0x101) : ((_Date & 0xffff0000) + 0x10101);
		}
		return *this;
	}

};
#pragma pack()
} // namespace os
template<typename ostream>
ostream& operator << (ostream& s, const os::Date32& d)
{	s << d.GetYear() <<'/'<< 
		rt::tos::Number(d.GetMonth()).RightAlign(2,'0')<<'/'<<
		rt::tos::Number(d.GetDay()).RightAlign(2,'0');
	return s;
};

namespace rt
{

template <typename T, bool desc = false>
struct BigEndianNumber
{
	TYPETRAITS_DECLARE_POD;
	T		_V;
public:
	BigEndianNumber(const T& value){ Set(value); }
	void Set(const T& value)
	{
		static bool is_signed = T(-1) < 0; // rt::NumericTraits<T>::IsSigned
		T v = value;
		if(is_signed)
			v -= ((T)1) << (sizeof(T) * 8 - 1);
		if(desc)
			v ^= (T)-1;
		rt::SwitchByteOrderTo<sizeof(T)>(&v, &_V);
	}
	T Value() const
	{
		static bool is_signed = T(-1) < 0;
		T value;
		rt::SwitchByteOrderTo<sizeof(T)>(&_V, &value);
		if(desc)
			value ^= (T)-1;
		if(is_signed)
			value -= ((T)1) << (sizeof(T) * 8 - 1);
		return value;
	}
	operator T() const { return Value(); }
	void MakeMin(){ rt::Zero(_V); }
	void Maximize(){ rt::Void(_V); }
	bool IsEqual(BigEndianNumber& x) const { return rt::IsEqual(*this, x); }
};

} // namespace rt

namespace rt
{
TYPETRAITS_DEFINE(os::Date32,void,true,false)
TYPETRAITS_DEFINE(os::TickCount,void,true,false)
TYPETRAITS_DEFINE(os::Timestamp,void,true,false)
}

namespace os
{

extern DWORD		crc32c(LPCVOID data, SIZE_T length, DWORD crc_init = 0);
extern DWORD		crc32(LPCVOID data, SIZE_T length, DWORD crc_init = 0);
extern ULONGLONG	crc64(LPCVOID stream, SIZE_T n, ULONGLONG crc_init = 0);

// https://en.wikipedia.org/wiki/XXTEA
extern void			xxtea_encode(LPCVOID key_16bytes, LPVOID data, UINT length);  // inplace encode, data length should be multiple of 8bytes
extern void			xxtea_decode(LPCVOID key_16bytes, LPVOID cipher, UINT length);  // inplace decode, cipher length should be multiple of 8bytes

#if defined(PLATFORM_WIN)
#else
typedef char16_t        WCHAR;
#endif
    
typedef WCHAR           U16CHAR;
typedef const WCHAR*	LPCU16CHAR;
typedef WCHAR*          LPU16CHAR;

/**
 * @brief UTF16 to UTF8 
 * 
 * return number of char
 * @param pIn 
 * @param len 
 * @return SIZE_T 
 */
extern SIZE_T	UTF8EncodeLength(LPCU16CHAR pIn, SIZE_T len);			
/**
 * @brief UTF16 to UTF8  
 * 
 * return number of char
 * @param pIn 
 * @param len 
 * @param pOut 
 * @return SIZE_T 
 */
extern SIZE_T	UTF8Encode(LPCU16CHAR pIn, SIZE_T len, LPSTR pOut);		
/**
 * @brief UTF8 to UTF16
 * 
 * return number of wchar
 * @param pIn 
 * @param len 
 * @return SIZE_T 
 */
extern SIZE_T	UTF8DecodeLength(LPCSTR pIn, SIZE_T len);				
/**
 * @brief UTF8 to UTF16
 * 
 * return number of wchar
 * @param pIn 
 * @param len 
 * @param pOut 
 * @return SIZE_T 
 */
extern SIZE_T	UTF8Decode(LPCSTR pIn, SIZE_T len, LPU16CHAR pOut);	
/**
 * @brief UTF8 to UTF16
 * 
 * counting number of utf8 chatactors
 * @param pIn 
 * @param len 
 * @param num_of_utf8_char 
 * @return SIZE_T 
 */
extern SIZE_T	UTF8ByteOffset(LPCSTR pIn, SIZE_T len, SIZE_T num_of_utf8_char); 

// Charset to UTF8
// charset_name follows http standard: http://www.iana.org/assignments/character-sets/character-sets.xhtml
// the Preferred MIME name, or the name

//**** charset index is platform dependent  ****//
#ifdef PLATFORM_WIN
	static const DWORD CHARSET_LATIN_BASE	= 28591;
	static const DWORD CHARSET_SHIFT_JIS	= 932;
	static const DWORD CHARSET_GB_2312		= 936;
	static const DWORD CHARSET_GB_18030		= 54936;
	static const DWORD CHARSET_BIG5			= 950;
	static const DWORD CHARSET_KOREAN		= 1361;
	static const DWORD CHARSET_UTF_16		= 1200;
	static const DWORD CHARSET_UTF_8		= 65001;
	static const DWORD CHARSET_KOI8_U		= 21866;
	static const DWORD CHARSET_KOI8_R		= 20866;
#else
	static const DWORD CHARSET_LATIN_BASE	= 0;
	static const DWORD CHARSET_SHIFT_JIS	= 0;
	static const DWORD CHARSET_GB_2312		= 0;
	static const DWORD CHARSET_GB_18030		= 0;
	static const DWORD CHARSET_BIG5			= 0;
	static const DWORD CHARSET_KOREAN		= 0;
	static const DWORD CHARSET_UTF_16		= 0;
	static const DWORD CHARSET_UTF_8		= 0;
	static const DWORD CHARSET_KOI8_U		= 0;
	static const DWORD CHARSET_KOI8_R		= 0;
#endif

/**
 * @brief return max possible number of char, -1 for unknown charset, len is in byte, *pCharsetIndex is platform dependent
 * 
 * @param pIn 
 * @param size_in_byte 
 * @param charset_name 
 * @param pCharsetIndex_out 
 * @return SSIZE_T 
 */
extern SSIZE_T		UTF8EncodeLengthMax(LPCVOID pIn, SIZE_T size_in_byte, const rt::String_Ref& charset_name, DWORD* pCharsetIndex_out);	
/**
 * @brief return actual number of char encoded
 * 
 * @param pIn 
 * @param len 
 * @param pOut 
 * @param charset_index 
 * @return SIZE_T 
 */
extern SIZE_T		UTF8Encode(LPCVOID pIn, SIZE_T len, LPSTR pOut, DWORD charset_index);					


struct __UTF16
{	rt::BufferEx<U16CHAR>	_utf16;
	INLFUNC __UTF16(){}
	INLFUNC __UTF16(LPCU16CHAR x){ *this = x; }
	INLFUNC __UTF16(const rt::String_Ref& x){ *this = x; }
	INLFUNC rt::String_Ref operator = (const rt::String_Ref& x)
	{	if(!x.IsEmpty())
		{	int len = (int)x.GetLength();
			int utf16_len = (int)os::UTF8DecodeLength(x.Begin(),len);
			VERIFY(_utf16.SetSize(utf16_len + 1));
			_utf16[utf16_len] = 0;
			os::UTF8Decode(x.Begin(), len, _utf16);
		}
		return x;
	}
	INLFUNC	 LPCU16CHAR operator = (LPCU16CHAR x)
	{	if(x)
		{	SIZE_T len = 0;
			while(x[len])len++;
			_utf16.SetSize(len+1);
			memcpy(_utf16, x, sizeof(U16CHAR)*(len+1));
		}else _utf16.SetSize(0);
        return x;
	}
	INLFUNC	 bool		IsEmpty() const { return _utf16.GetSize()<=1 || _utf16[0] == 0; }
	INLFUNC  operator	LPCU16CHAR() const { return (LPCU16CHAR)_utf16.Begin(); }
	INLFUNC  LPU16CHAR	Begin(){ return _utf16.Begin(); }
	INLFUNC  SIZE_T		GetLength() const { return _utf16.GetSize()?_utf16.GetSize()-1:0; }
	INLFUNC	 bool		SetLength(SIZE_T len){ if(_utf16.SetSize(len+1)){ _utf16[len] = 0; return true;} else return false; }
	INLFUNC static int	GetNextU16CHAR(LPCSTR& p)
	{	UINT c = *p;
		if(c <= 0x7f){ p++;	}
		else if((c&0xf0) == 0xe0)	// 1110xxxx 	10xxxxxx 	10xxxxxx
		{	c = ((c&0xf)<<12) | ((p[1]&0x3f)<<6) | (p[2]&0x3f);		p+=3;	}
		else if((c&0xe0) == 0xc0)	// 110xxxxx 	10xxxxxx
		{	c = ((c&0x1f)<<6) | (p[1]&0x3f);	p+=2;	}
		else{ c = '?'; p+=4; }
		return c;
	}
	INLFUNC U16CHAR		operator [](SIZE_T i) const { return _utf16[i]; }
	INLFUNC U16CHAR&	operator [](SIZE_T i){ return _utf16[i]; }
private:
	__UTF16(const __UTF16&x){};
};
template<UINT bufsize>
struct __UTF16_S
{	U16CHAR	_utf16[bufsize+1];
	UINT	_utf16_len;
	INLFUNC __UTF16_S(){}
	INLFUNC __UTF16_S(LPCU16CHAR x){ *this = x; }
	INLFUNC __UTF16_S(const rt::String_Ref& x){ *this = x; }
	INLFUNC rt::String_Ref operator = (const rt::String_Ref& x)
	{	if(!x.IsEmpty())
		{	int len = (int)x.GetLength();
			int utf16_len = (int)os::UTF8DecodeLength(x.Begin(),len);
			if(utf16_len<=bufsize)
			{
				_utf16_len = utf16_len;
				os::UTF8Decode(x.Begin(), len, _utf16);
			}
			else _utf16_len = utf16_len;
			_utf16[utf16_len] = 0;
		}
		return x;
	}
	INLFUNC	 bool		IsEmpty() const { return _utf16.GetSize()<=1 || _utf16[0] == 0; }
	INLFUNC  operator	LPCU16CHAR() const { return (LPCU16CHAR)_utf16; }
	INLFUNC  LPU16CHAR	Begin(){ return _utf16; }
	INLFUNC  SIZE_T		GetLength() const { return _utf16_len; }
	INLFUNC U16CHAR		operator [](SIZE_T i) const { ASSERT(i<=_utf16_len); return _utf16[i]; }
	INLFUNC U16CHAR&	operator [](SIZE_T i){ ASSERT(i<=_utf16_len); return _utf16[i]; }
private:
	__UTF16_S(const __UTF16_S&x){};
};
struct __UTF8: public rt::String_Ref
{
	rt::BufferEx<CHAR>	_utf8;
	__UTF8() = default;
    __UTF8(LPCU16CHAR x, int maxlen = INT_MAX){ Convert(x, maxlen); }
	void Convert(LPCU16CHAR x, int maxlen = INT_MAX)
	{	if(x)
		{	int len = 0;
			while(len < maxlen && x[len])len++;
			int utf8_len = (int)os::UTF8EncodeLength(x,len);
			VERIFY(_utf8.SetSize(utf8_len + 1));
			_utf8[utf8_len] = 0;
			os::UTF8Encode(x, len, _utf8);
		}
		if(_utf8.GetSize())
		{	_p = (LPSTR)SafeString();
			_len = _utf8.GetSize() - 1;
		}
		else Empty();
	}
	operator LPCSTR(){ return (LPCSTR)_utf8.Begin(); }
	LPCSTR	 SafeString() const { return _utf8.Begin()?_utf8.Begin():""; }
private:
	__UTF8(const __UTF8&){ ASSERT(0); }
};
template<UINT bufsize>
struct __UTF8_S: public rt::String_Ref
{
	CHAR _utf8[bufsize+1];
	__UTF8_S(){ _utf8[0] = 0; }
	__UTF8_S(LPCU16CHAR x, int maxlen = INT_MAX){ Convert(x, maxlen); }
	void Convert(LPCU16CHAR x, int maxlen = INT_MAX)
	{	if(x)
		{	int len = 0;
			while(len < maxlen && x[len])len++;
			int utf8_len = (int)os::UTF8EncodeLength(x,len);
			ASSERT(utf8_len<=bufsize);
			if(utf8_len<=bufsize)
			{
				_len = utf8_len;
				_utf8[utf8_len] = 0;
				os::UTF8Encode(x, len, _utf8);
			}
			else _len = 0;
		}
		_p = (LPSTR)SafeString();
	}
	operator LPCSTR(){ return _utf8; }
	LPCSTR	 SafeString() const { return _utf8; }
private:
	__UTF8_S(const __UTF8_S&){ ASSERT(0); }
};


inline constexpr SIZE_T	Base64EncodeLength(SIZE_T len){ return (len+2)/3*4; }
extern SIZE_T	Base64DecodeLength(LPCSTR pBase64, SIZE_T len);
extern void		Base64Encode(LPSTR pBase64Out,LPCVOID pData, SIZE_T data_len); ///< assuming the data is well formated
extern bool		Base64Decode(LPVOID pDataOut,SIZE_T* pDataOutLen,LPCSTR pBase64, SIZE_T str_len); ///< false if partial data decoded due to illegal data (*pDataOutLen) might be smaller than Base64DecodeLength returned

extern bool		Base64Encode(const rt::String_Ref&in, rt::String& out);
extern bool		Base64Decode(const rt::String_Ref&in, rt::String& out);

inline constexpr SIZE_T	Base16EncodeLength(SIZE_T len){ return len*2; }
inline constexpr SIZE_T	Base16DecodeLength(SIZE_T len){ return len/2; }
extern void		Base16Encode(LPSTR pBase16Out,LPCVOID pData, SIZE_T data_len);
extern bool		Base16Decode(LPVOID pDataOut,SIZE_T data_len,LPCSTR pBase16, SIZE_T str_len);

extern bool		Base16Encode(const rt::String_Ref&in, rt::String& out);
extern bool		Base16Decode(const rt::String_Ref&in, rt::String& out);

extern UINT		UrlEncode(LPCSTR url, UINT url_len, LPSTR encoded_url);  ///< return encoded length
extern void		UrlEncode(const rt::String_Ref& url, rt::String& encoded_url);

extern UINT		UrlDecode(LPCSTR encoded_url, UINT encoded_url_len, LPSTR url);  ///< return encoded length
extern void		UrlDecode(const rt::String_Ref& encoded_url, rt::String& url);

// Base32 Encoding
inline constexpr SIZE_T	Base32EncodeLength(SIZE_T len){ return (len*8+4)/5; }
extern SIZE_T	Base32DecodeLength(SIZE_T len);
// Base32 Extended HEX (0-9A-V)
extern bool		Base32Decode(LPVOID pDataOut,SIZE_T data_len,LPCSTR pBase32, SIZE_T str_len);  ///< for both upper/lowercase
extern void		Base32Encode(LPSTR pBase32Out,LPCVOID pData, SIZE_T data_len);
extern void		Base32EncodeLowercase(LPSTR pBase32Out,LPCVOID pData, SIZE_T data_len);
// Base32 Modified Crockford (also avoids s and z, which confuse with 2 and 5)
extern bool		Base32CrockfordDecode(LPVOID pDataOut, SIZE_T data_len, LPCSTR pBase32, SIZE_T str_len);  ///< for both upper/lowercase
extern void		Base32CrockfordEncode(LPSTR pBase32Out,LPCVOID pData, SIZE_T data_len);
extern void		Base32CrockfordEncodeLowercase(LPSTR pBase32Out,LPCVOID pData, SIZE_T data_len);
/** @}*/
} // namespace os


namespace rt
{
namespace tos
{
/** \defgroup kernel kernel
 * @ingroup os
 *  @{
 */
template<UINT LEN = 256>
struct Base64OnStack: public ::rt::tos::S_<1, LEN>
{	typedef ::rt::tos::S_<1, LEN> _SC;
	Base64OnStack(LPCVOID pData, SIZE_T len)
	{	int slen = (int)os::Base64EncodeLength((UINT)len);
		ASSERT(slen < LEN);
		os::Base64Encode(_SC::_p, pData,(UINT)len);
		_SC::_p[slen] = 0;
		_SC::_len = slen;
	}
	template<typename T>
	Base64OnStack(const T& x)
	{	new (this) Base64OnStack(&x, sizeof(x));
	}
};

template<UINT LEN = 256>
struct Base32OnStack: public ::rt::tos::S_<1, LEN>
{	typedef ::rt::tos::S_<1, LEN> _SC;
	Base32OnStack(LPCVOID pData, SIZE_T len)
	{	int slen = (int)os::Base32EncodeLength((UINT)len);
		ASSERT(slen < LEN);
		os::Base32Encode(_SC::_p, pData,(UINT)len);
		_SC::_p[slen] = 0;
		_SC::_len = slen;
	}
	template<typename T>
	Base32OnStack(const T& x)
	{	new (this) Base32OnStack(&x, sizeof(x));
	}
};

template<UINT LEN = 256>
struct Base32LowercaseOnStack: public ::rt::tos::S_<1, LEN>
{	typedef ::rt::tos::S_<1, LEN> _SC;
	Base32LowercaseOnStack(LPCVOID pData, SIZE_T len)
	{	int slen = (int)os::Base32EncodeLength((UINT)len);
		ASSERT(slen < LEN);
		os::Base32EncodeLowercase(_SC::_p, pData,(UINT)len);
		_SC::_p[slen] = 0;
		_SC::_len = slen;
	}
	template<typename T>
	Base32LowercaseOnStack(const T& x)
	{	new (this) Base32LowercaseOnStack(&x, sizeof(x));
	}
};

template<UINT LEN = 256>
struct Base32CrockfordOnStack: public ::rt::tos::S_<1, LEN>
{	typedef ::rt::tos::S_<1, LEN> _SC;
	Base32CrockfordOnStack(LPCVOID pData, SIZE_T len)
	{	int slen = (int)os::Base32EncodeLength((UINT)len);
		ASSERT(slen < LEN);
		os::Base32CrockfordEncode(_SC::_p, pData,(UINT)len);
		_SC::_p[slen] = 0;
		_SC::_len = slen;
	}
	template<typename T>
	Base32CrockfordOnStack(const T& x)
	{	new (this) Base32CrockfordOnStack(&x, sizeof(x));
	}
};

template<UINT LEN = 256>
struct Base32CrockfordLowercaseOnStack: public ::rt::tos::S_<1, LEN>
{	typedef ::rt::tos::S_<1, LEN> _SC;
	Base32CrockfordLowercaseOnStack(LPCVOID pData, SIZE_T len)
	{	int slen = (int)os::Base32EncodeLength((UINT)len);
		ASSERT(slen < (int)LEN);
		os::Base32CrockfordEncodeLowercase(_SC::_p, pData,(UINT)len);
		_SC::_p[slen] = 0;
		_SC::_len = slen;
	}
	template<typename T>
	Base32CrockfordLowercaseOnStack(const T& x)
	{	new (this) Base32CrockfordLowercaseOnStack(&x, sizeof(x));
	}
};

template<UINT LEN = 256>
struct Base16OnStack: public ::rt::tos::S_<1, LEN>
{	typedef ::rt::tos::S_<1, LEN> _SC;
	Base16OnStack(LPCVOID pData, SIZE_T len)
	{	UINT slen = (UINT)os::Base16EncodeLength((UINT)len);
		ASSERT(slen < LEN);
		os::Base16Encode(_SC::_p, pData,(UINT)len);
		_SC::_p[slen] = 0;
		_SC::_len = slen;
	}
	template<typename T>
	Base16OnStack(const T& x):Base16OnStack(&x, sizeof(x)){}
};

struct Base64: public String
{	
	Base64(const rt::String_Ref& data):Base64(data.Begin(), data.GetLength()){}
	Base64(LPCVOID pData, SIZE_T len)
	{	SetLength(os::Base64EncodeLength((UINT)len));
		os::Base64Encode(Begin(), pData,(UINT)len);
	}
	template<typename T>
	Base64(const T& x)
	{	new (this) Base64(&x, sizeof(x));
	}
};

struct Base32: public String
{	Base32(LPCVOID pData, SIZE_T len)
	{	if(SetLength(os::Base32EncodeLength((UINT)len)))
			os::Base32Encode(Begin(), pData,(UINT)len);
	}
	template<typename T>
	Base32(const T& x)
	{	new (this) Base32(&x, sizeof(x));
	}
};

struct Base16: public String
{	Base16(LPCVOID pData, SIZE_T len)
	{	if(SetLength(os::Base16EncodeLength((UINT)len)))
			os::Base16Encode(Begin(), pData,(UINT)len);
	}
	template<typename T>
	Base16(const T& x)
	{	new (this) Base16(&x, sizeof(x));
	}
};

/** @}*/
} // tos

} // rt

/** @}*/