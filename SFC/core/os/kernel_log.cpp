#include "kernel.h"
#include "multi_thread.h"
#include "file_dir.h"

#if defined(PLATFORM_WIN)
#include <conio.h>
#endif

namespace os
{
namespace _details
{

#ifndef PLATFORM_DISABLE_LOG

LPCSTR _UnitTestOutputFilePrefix = nullptr;
static CriticalSection	_LogWriteCS;
static File				_LogFile;
static Timestamp		_LogTime;
static rt::String		_LogPrompt;

#endif

#if defined(PLATFORM_WIN) && !defined(PLATFORM_DISABLE_LOG)
struct _InitConsoleCodepage
{
	_InitConsoleCodepage()
	{
		auto h = ::GetConsoleWindow();
		if(h != NULL)
		{
			::SetConsoleCP(65001); // UTF-8
			::SetConsoleOutputCP(65001);
		}
	}
};
_InitConsoleCodepage __InitConsoleCodepage;

void _CreateConsole()
{
#pragma warning(disable:4311)
	static bool bInit = false;
	
	if(bInit)return;

	if(::GetConsoleWindow() == NULL)
	{
		// allocate a console for this app
		AllocConsole();
		_InitConsoleCodepage();
	}

	// set the screen buffer to be big enough to let us scroll text
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
	coninfo.dwSize.Y = 9999;
	// How many lines do you want to have in the console buffer
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);
    // redirect unbuffered STDOUT to the console
    freopen("CONOUT$", "w", stdout);
	setvbuf(stdout, NULL, _IONBF, 0);
	// redirect unbuffered STDIN to the console
    freopen("CONIN$", "r", stdin);
	setvbuf(stdin, NULL, _IONBF, 0);
	// redirect unbuffered STDERR to the console
    freopen("CONOUT$", "w", stderr);
    setvbuf(stderr, NULL, _IONBF, 0);

	// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog point to console as well
	std::ios::sync_with_stdio();

	bInit = true;
#pragma warning(default:4311)
}
#endif

} // namespace _details

void SetLogConsolePrompt(LPCSTR prompt)
{
#ifndef PLATFORM_DISABLE_LOG
	_details::_LogPrompt = rt::String_Ref(prompt).SubStr(0, 64);
#endif
}

bool SetLogFile(LPCSTR filename_in, bool append)
{
#ifndef PLATFORM_DISABLE_LOG
	rt::String filename = filename_in;

	os::Timestamp::Fields f = os::Timestamp::Get().GetLocalDateTime();

	filename.Replace("%YEAR%", rt::tos::Number(f.Year));
	filename.Replace("%MONTH%", rt::tos::Number(f.Month).RightAlign(2,'0'));
	filename.Replace("%DAY%", rt::tos::Number(f.Day).RightAlign(2,'0'));

	EnterCSBlock(_details::_LogWriteCS);
	if(_details::_LogFile.IsOpen())_details::_LogFile.Close();
	if(_details::_LogFile.Open(filename, append?os::File::Normal_Append:os::File::Normal_Write, true))
	{
		if(!append || _details::_LogFile.GetFileSize() == 0)
			if(3 != _details::_LogFile.Write("\xef\xbb\xbf", 3))
			{	_details::_LogFile.Close();
				return false;
			}

		return true;
	}
#endif

	return false;
}

rt::String_Ref GetLogFilename()
{
#ifndef PLATFORM_DISABLE_LOG
	return _details::_LogFile.GetFilename();
#else
	return nullptr;
#endif
}

void LogWriteFlush()
{
#ifndef PLATFORM_DISABLE_LOG
	if(_details::_LogFile.IsOpen())
	{
		EnterCSBlock(_details::_LogWriteCS);
		_details::_LogFile.Flush();
		_details::_LogTime.LoadCurrentTime();
	}
#endif
}

#ifndef PLATFORM_DISABLE_LOG
LogPrefix& LogPrefix::operator << (LogPrefixItemCode code)
{
	_item& it = items.push_back();
    it.code = code;
    return *this;
}

LogPrefix& LogPrefix::operator << (char c)
{
	if (items.GetSize() && !items.last().code) // if last item is a string, append the string
    {   items.last().string += c;
    }
    else
    {   _item& it = items.push_back();
		auto x = rt::String_Ref(&c, 1);
        it.string = ALLOCA_C_STRING(x);
    }
    return *this;
}

LogPrefix& LogPrefix::operator << (LPCSTR s)
{
	if (items.GetSize() && !items.last().code) // if last item is a string, append the string
    {   items.last().string += s;
    }
    else
    {   _item& it = items.push_back();
        it.string = s;
    }
    return *this;
}

const LogPrefix& LogPrefix::operator = (const LogPrefix& x)
{   items.SetSize(x.items.GetSize());
    for (int i = 0; i < (int)x.items.GetSize(); i++)
    {   
        if (x.items[i].code)
        {   items[i].code = x.items[i].code;
        }
        else
        {   items[i].string = x.items[i].string;
        }
    }
    return *this;
}
#endif // #ifndef PLATFORM_DISABLE_LOG
} // namespace os



#if defined(PLATFORM_WIN)
//////////////////////////////////////////////////////////
// All Windows implementations
#include <windows.h>
#include <Rpc.h>
#include <iostream>
#include <io.h>
#pragma comment(lib,"Rpcrt4.lib")


namespace os
{
namespace _details
{
	void __ConsoleLogWriteDefault(LPCSTR log, int type, LPVOID)
	{	
#ifndef PLATFORM_DISABLE_LOG
		_details::_CreateConsole();

		int color[] = { 8, 8, 7, 10, 14, 12 };
		SetConsoleTextAttribute(GetStdHandle( STD_OUTPUT_HANDLE ), color[type&rt::LOGTYPE_LEVEL_MASK]);
		int len = (int)strlen(log);
		
		os::LPU16CHAR utf16;
		rt::Buffer<os::U16CHAR> temp;
		if(len < 4*1024)
			utf16 = (os::LPU16CHAR)alloca(2*len);
		else
		{
			temp.ChangeSize(len);
			utf16 = temp.Begin();
		}

		int len_utf16 = (int)os::UTF8Decode(log, len, utf16);

		char* mb;
		rt::String	temp_str;
		if(3*len_utf16 < 4*1024)
			mb = (char*)alloca(3*len_utf16 + 1);
		else
		{
			temp_str.SetLength(3*len_utf16);
			mb = temp_str;
		}

		int mb_len = WideCharToMultiByte(CP_THREAD_ACP, 0, utf16, len_utf16, mb, 3*len_utf16, NULL, NULL);
		mb[mb_len] = 0;

		thread_local bool _last_updating = false;
		static const char clear_len[] = "\r                                                                               \r";

		if(_last_updating)
			fputs(clear_len, stdout);

		if((type&rt::LOGTYPE_LEVEL_MASK) != rt::LOGTYPE_UPDATING)
		{
			if(!_details::_LogPrompt.IsEmpty())
			{	putchar('\r');
				fputs(&clear_len[sizeof(clear_len) - 3 - _details::_LogPrompt.GetLength()], stdout);
			}

			if((type&rt::LOGTYPE_IN_CONSOLE_PROMPT) == 0)
				puts(mb);

			SetConsoleTextAttribute(GetStdHandle( STD_OUTPUT_HANDLE ), color[2]);

			if(!_details::_LogPrompt.IsEmpty())
				fputs(_details::_LogPrompt, stdout);

			_last_updating = false;
		}
		else
		{
			fputs(mb, stdout);
			_last_updating = true;
			fflush(stdout);
			SetConsoleTextAttribute(GetStdHandle( STD_OUTPUT_HANDLE ), color[2]);
		}
#endif // #ifndef PLATFORM_DISABLE_LOG
	}
}

void SetLogConsoleTitle(LPCSTR title)
{
	HWND wnd = ::GetConsoleWindow();
	if(wnd)
		::SetWindowTextW(wnd, os::__UTF16(title));
}

} //  namespace os::_details

#elif defined(PLATFORM_ANDROID)
#include <android/log.h>

#ifndef PLATFORM_DISABLE_LOG
namespace os
{
namespace _details
{
	void __ConsoleLogWriteDefault(LPCSTR log, int type, LPVOID)
	{	
		ASSERT(type >=0 && (type&rt::LOGTYPE_LEVEL_MASK) <rt::LOGTYPE_MAX);
		int cat[] = { ANDROID_LOG_VERBOSE, ANDROID_LOG_DEBUG, ANDROID_LOG_INFO, ANDROID_LOG_WARN, ANDROID_LOG_ERROR };
		__android_log_write(cat[type&rt::LOGTYPE_LEVEL_MASK], "CPF", log);
	}
}} //  namespace os::_details
#endif // #ifndef PLATFORM_DISABLE_LOG

#elif defined (PLATFORM_IOS)

#ifndef PLATFORM_DISABLE_LOG
namespace os
{
namespace _details
{
	void __ConsoleLogWriteDefault(LPCSTR log, int type, LPVOID)
	{	
        static os::CriticalSection _LogCS;
        static rt::String _prev;
        
        rt::String_Ref logstr(log);
        EnterCSBlock(_LogCS);
        if(_prev == logstr)return;
        puts(log);
        _prev = logstr;
	}
}} //  namespace os::_details
#endif // #ifndef PLATFORM_DISABLE_LOG

#elif defined(PLATFORM_LINUX) || defined (PLATFORM_MAC)
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#ifndef PLATFORM_DISABLE_LOG
namespace os
{
namespace _details
{
	void __ConsoleLogWriteTerminal(LPCSTR mb, int type, LPVOID)
	{	
		setlocale(LC_ALL, "en_US.UTF-8");
		
		LPCSTR color[] = { "\033[0;37m", "\033[0;37m", "\033[0m", "\033[1;32m", "\033[1;33m", "\033[1;31m" };
        
		thread_local bool _last_is_updating = false;
		
		if(_last_is_updating)
			fputs("\033[2K\r", stdout);
		
		fputs(color[type&rt::LOGTYPE_LEVEL_MASK], stdout);
		if((type&rt::LOGTYPE_LEVEL_MASK) != rt::LOGTYPE_UPDATING)
		{
#ifndef PLATFORM_DISABLE_LOG
			if(!_details::_LogPrompt.IsEmpty())
                fputs("\r                                                                \r", stdout);
#endif 

			if((type&rt::LOGTYPE_IN_CONSOLE_PROMPT) == 0)
				puts(mb);
			
			fputs("\033[0m", stdout);
			
#ifndef PLATFORM_DISABLE_LOG
			if(!_details::_LogPrompt.IsEmpty())
				fputs(_details::_LogPrompt, stdout);
#endif 
				
			fflush(stdout);
			_last_is_updating = false;
		}
		else
		{	
			fputs(mb, stdout);
			_last_is_updating = true;
			fputs("\033[0m", stdout);
			fflush(stdout);
		}
	}
    
    void __ConsoleLogWriteDebugger(LPCSTR log, int type, LPVOID)
    {
        static os::CriticalSection _LogCS;
        static rt::String _prev;
        
        rt::String_Ref logstr(log);
        if(!logstr.IsEmpty() && logstr.Last() == '\r')
        {   EnterCSBlock(_LogCS);
            if(_prev == logstr)return;
            _prev = logstr;
        }
        
        puts(log);
    }
    
    void __ConsoleLogWriteDefault(LPCSTR mb, int type, LPVOID)
    {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        if(w.ws_row && w.ws_col)  // detect terminal/debugger
        {
            SetConsoleLogWriteFunction(__ConsoleLogWriteTerminal, NULL);
            __ConsoleLogWriteTerminal(mb, type, NULL);
        }
        else
        {
            SetConsoleLogWriteFunction(__ConsoleLogWriteDebugger, NULL);
            __ConsoleLogWriteDebugger(mb, type, NULL);
        }
    }
}} //  namespace os::_details
#endif // #ifndef PLATFORM_DISABLE_LOG

#else
#endif

namespace os
{

#ifndef PLATFORM_DISABLE_LOG
namespace _details
{
/////////////////////////////////////////////////////////////////
// Platform independent implementations but depend on some platform dependent functions
void LogWriteDefault(LPCSTR log, LPCSTR file, int line_num, LPCSTR func, int type, LPVOID)
{
	EnterCSBlock(_LogWriteCS);

	if(type&(rt::LOGTYPE_IN_CONSOLE|rt::LOGTYPE_IN_CONSOLE_FORCE|rt::LOGTYPE_IN_CONSOLE_PROMPT))os::_details::__ConsoleLogWrite(log, type);
	if((type&rt::LOGTYPE_IN_LOGFILE) && _LogFile.IsOpen())
	{
		_LogFile.Write(rt::String_Ref(log));
		_LogFile.Write("\n", 1);
		_LogFile.Flush();
	}
}

static FUNC_LOG_WRITE	__LogWrtieFunc = LogWriteDefault;
static LPVOID			__LogWrtieFuncCookie = nullptr;
static bool				__LogWrtieNoConsoleDisplay = false;

void SetLogWriteFunction(FUNC_LOG_WRITE func, LPVOID cookie)
{
	if(func)
	{	__LogWrtieFunc = func;
		__LogWrtieFuncCookie = cookie;
	}
	else
	{	__LogWrtieFunc = LogWriteDefault;
		__LogWrtieFuncCookie = nullptr;
	}
}

static LPVOID					__ConsoleLogWriteCookie = nullptr;
static FUNC_CONSOLE_LOG_WRITE	__ConsoleLogWriteFunc = __ConsoleLogWriteDefault;

void __ConsoleLogWrite(LPCSTR log, int type){ __ConsoleLogWriteFunc(log, type, __ConsoleLogWriteCookie); }

void SetConsoleLogWriteFunction(FUNC_CONSOLE_LOG_WRITE func, LPVOID cookie)
{
	if(func)
	{	__ConsoleLogWriteFunc = func;
		__ConsoleLogWriteCookie = cookie;
	}
	else
	{	__ConsoleLogWriteCookie = nullptr;
		__ConsoleLogWriteFunc = __ConsoleLogWriteDefault;
	}
}
} // namespace _details
#endif // #ifndef PLATFORM_DISABLE_LOG

void LogDisplayInConsole(bool yes)
{
#ifndef PLATFORM_DISABLE_LOG
	_details::__LogWrtieNoConsoleDisplay = !yes;
#endif
}

bool LogIsDisplayInConsole()
{
#ifndef PLATFORM_DISABLE_LOG
	return !_details::__LogWrtieNoConsoleDisplay;
#endif
	return false;
}

void LogWrite(LPCSTR log, LPCSTR file, int line_num, LPCSTR func, int type)
{
#ifndef PLATFORM_DISABLE_LOG
	if(_details::__LogWrtieNoConsoleDisplay)type = type&(~rt::LOGTYPE_IN_CONSOLE);
	_details::__LogWrtieFunc(log, file, line_num, func, type, _details::__LogWrtieFuncCookie);
#endif
}


} // namespace os
