#include "kernel.h"
#include "file_dir.h"
#include "multi_thread.h"

#ifdef PLATFORM_DEBUG_BUILD
#include <assert.h>
#endif

#if defined(PLATFORM_WIN)
#include <comutil.h>
#pragma comment(lib, "comsuppw.lib")
#include <Rpc.h>
#include <Psapi.h>
#pragma comment(lib,"Psapi.lib")
#include <Wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")
#include <Sddl.h>
#include <fcntl.h>
#include <Wincon.h>
#include <conio.h>
#include <io.h>
#include <iostream>
#include <ShellAPI.h>
#include <wincrypt.h>
#pragma comment(lib,"Crypt32.lib")


#elif defined(PLATFORM_IOS) || defined(PLATFORM_MAC)

#include <sys/sysctl.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <mach/mach.h>
#include <mach/processor_info.h>
#include <mach/mach_host.h>
#include <sys/mman.h>
#include <uuid/uuid.h>
#include <dlfcn.h>
#include <unistd.h>

extern int _objc_get_bundle_path(char* pOut, int OutSize);

#if defined(PLATFORM_APPLICATION)
extern UINT _objc_get_screens_dim(rt::Vec2i* p, UINT co);
#endif

#define MAP_ANONYMOUS MAP_ANON

#if defined(PLATFORM_MAC)
#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include <IOKit/ps/IOPowerSources.h>
#include <IOKit/IOKitLib.h>
#include <sys/resource.h>
#include <CoreGraphics/CGDisplayConfiguration.h>

extern UINT _objc_preference_load_string(LPCSTR key, LPSTR val_out, UINT val_size);
extern void _objc_preference_save_string(LPCSTR key, LPCSTR val);
#endif


#if defined(PLATFORM_IOS) && defined(PLATFORM_APPLICATION)
extern int _objc_get_battery_state(bool* plugged);
#endif

#elif defined(PLATFORM_ANDROID) || defined(PLATFORM_LINUX)

#ifdef PLATFORM_ANDROID
#include <sys/sysconf.h>
#include <sys/system_properties.h>

#ifdef PLATFORM_64BIT
#include <time.h>
#else
#include <time64.h>
#endif


#else
#endif

#ifdef PLATFORM_LINUX
#include <X11/Xlib.h>
#endif

#include <sys/resource.h>
#include <sys/utsname.h>
#include <sys/mman.h>
#include <asm/param.h>
#include <errno.h>
#include <unistd.h>
#include <dlfcn.h>
#include <fstream>
#include <fcntl.h>

#endif

void os::HighPerformanceCounter::SetOutputUnit(LONGLONG u)
{
#if defined(PLATFORM_WIN)
	VERIFY(QueryPerformanceFrequency((LARGE_INTEGER*)&_Mul));
	LONGLONG m = 1000000000LL/_Mul/u;
	_bMul = m>0;
	if(_bMul){ _Mul = m; }
	else{ _Div = _Mul*u/1000000000LL; }
#elif defined (PLATFORM_IOS) || defined (PLATFORM_MAC)
    struct mach_timebase_info tbi;
    mach_timebase_info(&tbi);
    LONGLONG m = tbi.numer/tbi.denom/u;
	_bMul = m>0;
	if(_bMul){ _Mul = m; }
    else{ _Div = tbi.denom*u/tbi.numer; }
#else
	_Div = u;
#endif

	_Count = Get();
}

LPCSTR os::GetBuildSpecificationString()
{
	return 
	#if		defined(PLATFORM_DEBUG_BUILD)
						"Debug"
	#elif	defined(PLATFORM_RELEASE_BUILD)
						"Release"
	#endif

	#if		defined(PLATFORM_32BIT)
						"/x86"
	#elif	defined(PLATFORM_64BIT)
						"/x64"
	#endif

	#if		defined(PLATFORM_ANDROID)
						"/Andriod"
	#elif	defined(PLATFORM_IOS)
						"/iOS"
	#elif	defined(PLATFORM_MAC)
						"/OSX"
	#elif	defined(PLATFORM_WIN)
						"/Win"
	#elif	defined(PLATFORM_LINUX)
						"/Linux"
	#else
						"/#unk"
	#endif
	;
}

/////////////////////////////////////////////////////////////////
// Platform independent implementations
bool os::GetSystemMemoryInfo(ULONGLONG* free, ULONGLONG* total)
{
	if(free)*free = 0;
	if(total)*total = 0;	
	
#if defined(PLATFORM_WIN)
	MEMORYSTATUSEX ms;
	ms.dwLength = sizeof(ms);
	if(GlobalMemoryStatusEx(&ms))
	{
		if(free)*free = ms.ullAvailPhys;
		if (total)
		{
			if (GetPhysicallyInstalledSystemMemory(total) == FALSE)
				*total = ms.ullTotalPhys;
			else
				*total *= 1024;
		}
		return true;
	}
#elif defined(PLATFORM_IOS) || defined(PLATFORM_MAC)
	mach_port_t host_port;
	mach_msg_type_number_t host_size;
	vm_size_t pagesize;

    host_port = mach_host_self();
    host_size = sizeof(vm_statistics_data_t) / sizeof(integer_t);
    host_page_size(host_port, &pagesize);        

    vm_statistics_data_t vm_stat;
    if(host_statistics(host_port, HOST_VM_INFO, (host_info_t)&vm_stat, &host_size) == KERN_SUCCESS)
	{
		if(free)*free = (vm_stat.inactive_count + vm_stat.free_count) * pagesize;
		if(total)*total = (vm_stat.inactive_count + vm_stat.free_count + vm_stat.active_count + vm_stat.wire_count) * pagesize;
		return true;
	}
#elif defined(PLATFORM_ANDROID) || defined(PLATFORM_LINUX)
	rt::String meminfo;
	if(os::File::LoadText("/proc/meminfo", meminfo))
	{
		rt::String_Ref line;
		while(meminfo.GetNextLine(line))
		{
			if(total && line.StartsWith("MemTotal:"))
			{	line.TrimLeft(9).ToNumber(*total);
				*total *= 1024;
			}
			if(free && line.StartsWith("MemAvailable:"))
			{	line.TrimLeft(13).ToNumber(*free);
				*free *= 1024;
			}
		}
	}
#else
	#error TBD
#endif
	return false;
}

bool os::GetProcessMemoryLoad(SIZE_T* vmem, SIZE_T* phy_mem)
{	// http://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process
#if defined(PLATFORM_WIN)
	PROCESS_MEMORY_COUNTERS_EX pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	if(vmem)*vmem = pmc.PrivateUsage;
	if(phy_mem)*phy_mem = pmc.WorkingSetSize;
	return true;
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_ANDROID)
	if(phy_mem)*phy_mem = 0;
	if(vmem)*vmem = 0;
	rt::String str;
	if(os::File::LoadText("/proc/self/status", str))
	{
		if(phy_mem)
		{	LPCSTR vmrss = strstr(str, "VmRSS:");
			rt::String_Ref(vmrss + 6).ToNumber(*phy_mem);
			*phy_mem *= 1024;
		}
		if(vmem)
		{	LPCSTR vm = strstr(str, "VmSize:");
			rt::String_Ref(vm + 7).ToNumber(*vmem);
			*vmem *= 1024;
		}
		return true;
	}	
	return false;
#elif defined(PLATFORM_MAC) || defined(PLATFORM_IOS)
	struct task_basic_info t_info;
	mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

	if (KERN_SUCCESS != task_info(mach_task_self(),
								  TASK_BASIC_INFO, (task_info_t)&t_info, 
								  &t_info_count))
	{
		return false;
	}

	if(phy_mem)*phy_mem = t_info.resident_size;
	if(vmem)*vmem = t_info.virtual_size;
	return true;
	
#else
	#error TBD
#endif

	return false;
}

void os::GetCPUBrand(rt::String& brand)
{
	unsigned CPUInfo[4];
	unsigned   nExIds, i = 0;
	char CPUBrandString[0x40];
	// Get the information associated with each extended ID.
	CPUID(0x80000000, CPUInfo);
	nExIds = CPUInfo[0];
	for (i = 0x80000000; i <= nExIds; ++i)
	{
		CPUID(i, CPUInfo);
		// Interpret CPU brand string
		if (i == 0x80000002)
			memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000003)
			memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000004)
			memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
	}
	//string includes manufacturer, model and clockspeed
	brand = CPUBrandString;
}

UINT os::GetNumberOfProcessors()
{
#if defined(PLATFORM_WIN)
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	return si.dwNumberOfProcessors;
#elif defined(PLATFORM_IOS) || defined(PLATFORM_MAC)
	unsigned numCPUs;
	int mib[2U] = { CTL_HW, HW_NCPU };
    size_t sizeOfNumCPUs = sizeof(numCPUs);
    int status = sysctl(mib, 2U, &numCPUs, &sizeOfNumCPUs, NULL, 0U);
    if(status)
        return 1;
	else
		return numCPUs;
#else
	return (UINT)sysconf (_SC_NPROCESSORS_ONLN);
#endif
}

UINT os::GetNumberOfPhysicalProcessors()
{
	unsigned regs[4];
	CPUID(1, regs);
	unsigned cpuFeatures = regs[3]; // EDX
	UINT num = GetNumberOfProcessors();
	if(num > 1 && ((num&1) == 0) && (cpuFeatures&(1 << 28)))  // HTT
		return num/2;
	else
		return num;
}

void os::CPUID(unsigned i, unsigned regs[4])
{
#if defined(PLATFORM_WIN)
	__cpuid((int *)regs, (int)i);
#elif defined(PLATFORM_MAC)||defined(PLATFORM_LINUX)
	asm volatile
		("cpuid" : "=a" (regs[0]), "=b" (regs[1]), "=c" (regs[2]), "=d" (regs[3])
			: "a" (i), "c" (0));
	// ECX is set to zero for CPUID function 4
#else
	rt::Zero(regs);
#endif
}

void os::GetOSVersion(rt::String& name, bool rich_info)
{
#if defined(PLATFORM_WIN)
	OSVERSIONINFOW vi;
	vi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOW);
	GetVersionExW(&vi);
	if(rich_info)
	{
		name = rt::SS("win") + vi.dwMajorVersion + '.' + vi.dwMinorVersion + '.' + vi.dwBuildNumber;
#ifdef PLATFORM_64BIT
		name += rt::SS("-x64");
#else
		BOOL is64 = FALSE;
		IsWow64Process(GetCurrentProcess(), &is64);
		if(is64)
			name += rt::SS("-x64");
		else
			name += rt::SS("-x86");
#endif
	}
	else
	{	name = rt::String_Ref() + vi.dwMajorVersion + '.' + vi.dwMinorVersion;
	}
#elif defined(PLATFORM_IOS) 
	// [[NSProcessInfo processInfo] operatingSystemVersion] in iOS 8 and above.
#elif defined(PLATFORM_MAC)
	SInt32 major, minor, bugfix;
	Gestalt(gestaltSystemVersionMajor, &major);
	Gestalt(gestaltSystemVersionMinor, &minor);
	if(rich_info)
	{
		Gestalt(gestaltSystemVersionBugFix, &bugfix);
		name = rt::SS("darwin") + major + '.' + minor + '.' + bugfix;
	}
	else
	{	name = rt::String_Ref() + major + '.' + minor;
	}
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_ANDROID)
	struct utsname out;
	if(uname(&out))
	{
		name = os::GetBuildSpecificationString();
	}
	else
	{
		if(rich_info)
		{	name = rt::String_Ref(out.nodename) + " (" + out.release + ") " + out.machine;
		}
		else
		{	name = out.release;
		}
	}
#else
	#error TBD
#endif
}

int os::GetDimensionOfScreens(rt::Vec2i* pDim, UINT dim_size) // return # of screens
{
#if defined(PLATFORM_WIN)
	struct _cb_struct
	{	
		rt::Vec2i*	pDim;
		UINT		dim_size;
		UINT		count;

		static BOOL CALLBACK MonitorEnumProc(
			HMONITOR hMonitor,
			HDC      hdcMonitor,
			LPRECT   lprcMonitor,
			LPARAM   dwData
		)
		{	_cb_struct& t = *((_cb_struct*)dwData);
			if(t.count < t.dim_size)
			{
				t.pDim[t.count].width = lprcMonitor->right - lprcMonitor->left;
				t.pDim[t.count].height = lprcMonitor->bottom - lprcMonitor->top;
				t.count++;
				return true;
			}
			else return false;
		}
	};
	_cb_struct cbs;
	cbs.count = 0;
	cbs.dim_size = dim_size;
	cbs.pDim = pDim;
		
	EnumDisplayMonitors(NULL, NULL, _cb_struct::MonitorEnumProc, (LPARAM)&cbs);
	return cbs.count;
#elif defined(PLATFORM_IOS)
	ASSERT(0);
#elif defined(PLATFORM_ANDROID)
	ASSERT(0);
#elif defined(PLATFORM_MAC)
    uint32_t numDisplay;
    CGDirectDisplayID displayIDs[10];
    CGGetActiveDisplayList(10, displayIDs, &numDisplay);
    if (numDisplay > dim_size)
        numDisplay = dim_size;
    for (uint32_t i = 0; i < numDisplay; i++)
    {
        pDim[i].width = (int)CGDisplayPixelsWide(displayIDs[i]);
        pDim[i].height = (int)CGDisplayPixelsHigh(displayIDs[i]);
    }
    return (int)numDisplay;
#elif defined(PLATFORM_LINUX)
	Display* d = XOpenDisplay(NULL);
	dim_size = rt::min(XScreenCount(d), (int)dim_size);
	UINT i = 0;
	for(; i<dim_size; i++)
	{
		Screen* s = XScreenOfDisplay(d, i);
		if(s)
		{
			pDim[i].x = s->width;
			pDim[i].y = s->height;
		}
	}
	return i;
#else
	#error TBD
#endif
    return 0;
}

int os::GetLastError()
{
#if		defined(PLATFORM_WIN)
	return ::GetLastError();
#else
	return errno;
#endif
}

namespace os 
{
namespace _details 
{
#if defined(PLATFORM_ANDROID)

const char* ndk_system_property_get(const char* name)
{
    thread_local static char value[PROP_VALUE_MAX];
    if (__system_property_get(name, value))
        return value;
    else
        return nullptr;
}

#endif
}
}

void os::GetHostName(rt::String& name)
{
#if defined(PLATFORM_WIN)
	WCHAR buf[1024] = {L'\x0'};
	DWORD len = sizeofArray(buf);
	GetComputerNameW(buf, &len);
	name = __UTF8(buf);
#else

	#if defined(PLATFORM_ANDROID)
    {
        auto* v = os::_details::ndk_system_property_get("net.hostname");
        if (v)
        {
            name = v;
            return;
        }
    }
    #endif

	char buf[1024] = {'\x0'};
	gethostname(buf, sizeof(buf));
	name = buf;
#endif
}

void os::GetLogonUserName(rt::String& name)
{
#if defined(PLATFORM_WIN)
	WCHAR buf[1024] = {L'\x0'};
	DWORD len = sizeofArray(buf);
	::GetUserNameW(buf, &len);
	name = __UTF8(buf);
#else

    #if defined(PLATFORM_ANDROID)
    {
        auto* v = os::_details::ndk_system_property_get("persist.sys.device_name");
        if (v)
        {
            name = v;
            return;
        }
    }
    #endif


	name = getlogin();
	//char buf[1024] = {'\x0'};
	//getlogin_r(buf, sizeof(buf));
	//name = buf;
#endif
}

void os::SetAppTitle(LPCSTR title)
{
#if defined(PLATFORM_WIN)
	if(GetConsoleWindow())
	{	SetConsoleTitleW(os::__UTF16(title));
	}
	else
	{	ASSERT(0);
	}
#else
	ASSERT(0);
#endif
}

void os::GetExecutableFilename(rt::String& name)
{
#if defined(PLATFORM_WIN)
	WCHAR fn[MAX_PATH];
	::GetModuleFileNameW(NULL, fn, sizeofArray(fn));
	name = os::__UTF8(fn);
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_ANDROID)
	char exepath[2048];
	int len = readlink("/proc/self/exe", exepath, sizeof(exepath)-1);
	if(len > 0)name = rt::String_Ref(exepath, len);
	else name.Empty();
#elif defined(PLATFORM_MAC) || defined(PLATFORM_IOS)
	char path[1024];
	int path_len = _objc_get_bundle_path(path, 1024);
	name = rt::String_Ref(path, path_len);
#else
	ASSERT(0);
#endif
}

bool os::GetProcessorTimes(ULONGLONG* pbusy, ULONGLONG* ptotal)
{
#if defined(PLATFORM_WIN)
	FILETIME f[3];
	if(GetSystemTimes(&f[0],&f[1],&f[2]))
	{	int div = os::GetNumberOfProcessors()*10000;
		if(pbusy)*pbusy = (((ULONGLONG&)f[1]) + ((ULONGLONG&)f[2]) - (ULONGLONG&)f[0])/div;
		if(ptotal)*ptotal = (((ULONGLONG&)f[1]) + ((ULONGLONG&)f[2]))/div;
		return true;
	}
#elif defined(PLATFORM_IOS) || defined(PLATFORM_MAC)
	natural_t numCPUs = 0U;
	processor_info_array_t cpuInfo;
	mach_msg_type_number_t numCpuInfo;
	
	if(KERN_SUCCESS == host_processor_info(mach_host_self(), PROCESSOR_CPU_LOAD_INFO, &numCPUs, &cpuInfo, &numCpuInfo))
	{
		ULONGLONG inidle = 0, total = 0;
		for(unsigned i = 0U; i < numCPUs; ++i) 
		{
			total +=cpuInfo[(CPU_STATE_MAX * i) + CPU_STATE_USER] + 
					cpuInfo[(CPU_STATE_MAX * i) + CPU_STATE_SYSTEM] + 
					cpuInfo[(CPU_STATE_MAX * i) + CPU_STATE_NICE] + 
					cpuInfo[(CPU_STATE_MAX * i) + CPU_STATE_IDLE];
			inidle += cpuInfo[(CPU_STATE_MAX * i) + CPU_STATE_IDLE];
		}
		if(pbusy)*pbusy = 10*(total - inidle)/numCPUs;
		if(ptotal)*ptotal = 10*total/numCPUs;
		return true;
	}
#elif defined(PLATFORM_ANDROID) || defined(PLATFORM_LINUX)
	rt::String sss;
	if(os::File::LoadText("/proc/stat", sss))
	{
		rt::String_Ref line;
		while(sss.GetNextLine(line))
		{	
			if(line.StartsWith("cpu  "))
			{
				rt::String_Ref nums[100];
				int co = line.TrimLeft(5).Split(nums, 100, ' ');
				if(co <= 3)return false;
				ULONGLONG busy = 0;
				ULONGLONG total = 0;
				for(int i=0;i<co;i++)
				{	UINT v;
					nums[i].ToNumber(v);
					total += v;
				}
				for(int i=0;i<3;i++)
				{	UINT v;
					nums[i].ToNumber(v);
					busy += v;
				}
				busy = busy*1000/HZ;
				total = total*1000/HZ;
				int numCPUs = os::GetNumberOfProcessors();
				if(pbusy)*pbusy = busy/numCPUs;
				if(ptotal)*ptotal = total/numCPUs;
				return true;
			}
		}
	}
#else
	ASSERT_STATIC_NOT_IMPLMENTED;
#endif
	return false;
}

void os::GetDeviceModel(rt::String& model)
{
#if defined(PLATFORM_WIN)
    // Obtain the initial locator to Windows Management on a particular host computer.
	HRESULT ret;
	ULONG uReturn = 0;
    IWbemLocator *locator = nullptr;
    IWbemServices *services = nullptr;
	IEnumWbemClassObject* classObjectEnumerator = nullptr;
	IWbemClassObject *classObject = nullptr;
    if(	SUCCEEDED((ret = CoInitialize(NULL))) &&
		SUCCEEDED(CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID *)&locator)) &&
		SUCCEEDED(locator->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), nullptr, nullptr, 0, NULL, 0, 0, &services)) &&
		SUCCEEDED(CoSetProxyBlanket(services, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE)) &&
		SUCCEEDED(services->ExecQuery(_bstr_t(L"WQL"), _bstr_t(L"SELECT * FROM Win32_ComputerSystem"), WBEM_FLAG_FORWARD_ONLY|WBEM_FLAG_RETURN_IMMEDIATELY, nullptr, &classObjectEnumerator)) &&
		SUCCEEDED(classObjectEnumerator->Next(WBEM_INFINITE, 1, &classObject, &uReturn))
	)
	{
		auto getValue = [](IWbemClassObject *classObject, LPCWSTR property, rt::String& out){
			out.Empty();
			VARIANT propertyValue;
			if(SUCCEEDED(classObject->Get(property, 0, &propertyValue, 0, 0)))
			{	if(propertyValue.vt == VT_BSTR)
					out = os::__UTF8(propertyValue.bstrVal);
				VariantClear(&propertyValue);
			}
		};

		if(uReturn != 0)
			getValue(classObject, (LPCWSTR)L"Model", model);
	}

	if(model.IsEmpty())model = "PC-Windows";
	_SafeRelease(classObject);
	_SafeRelease(classObjectEnumerator);
	_SafeRelease(services);
	_SafeRelease(locator);
	if(ret == S_OK)CoUninitialize();  // otherwise, S_FALSE indicates the thread is already initialized COM
#elif defined(PLATFORM_MAC)
    size_t len = 0;
    sysctlbyname("hw.model", NULL, &len, NULL, 0);
    model.SetLength(len);
	sysctlbyname("hw.model", model, &len, NULL, 0);  // like Macmini8,1
#elif defined(PLATFORM_IOS)
    struct utsname systemInfo;
    uname(&systemInfo);
    model = systemInfo.machine;  // like iPhone12,3 , https://stackoverflow.com/questions/11197509/how-to-get-device-make-and-model-on-ios
#elif defined(PLATFORM_ANDROID)
	model = os::_details::ndk_system_property_get("ro.product.model");
	if(!model.IsEmpty()) return;

	FILE * f = fopen("/sys/devices/virtual/dmi/id/product_name","r");
	if(f)
	{	char buf[256];
		int len = fread(buf, 1, sizeof(buf), f);
		if(len)model = rt::SS(buf, len);
		fclose(f);
	}

	if(model.IsEmpty())model = "Android";
#elif defined(PLATFORM_LINUX)
	FILE * f = fopen("/sys/devices/virtual/dmi/id/product_name","r");
	if(f)
	{	char buf[256];
		int len = fread(buf, 1, sizeof(buf), f);
		if(len)model = rt::SS(buf, len);
		fclose(f);
	}
	if(model.IsEmpty())model = "PC-Linux";
#endif
}

UINT os::GetPowerState(bool * pHasBattery, bool* pPlugged)		// precentage of battery remaining
{
    if(pHasBattery)*pHasBattery = true;
    if(pPlugged)*pPlugged = false;
#if defined(PLATFORM_WIN)
	SYSTEM_POWER_STATUS ps;
	if(::GetSystemPowerStatus(&ps))
	{	
		if(pHasBattery)*pHasBattery = !(ps.BatteryFlag&128);
		if(pPlugged)*pPlugged = !!ps.ACLineStatus;

		if(ps.ACLineStatus == 1)return 100;
		if(ps.ACLineStatus == 0)
			return rt::min<int>(100,ps.BatteryLifePercent);
	}
	return 100;
#elif defined(PLATFORM_MAC)
	///////////////////////////////////////////////////////////////////
	// IOKit.framework is required, add it to the project
	// How? check this video: http://www.youtube.com/watch?v=La58YR9hTNY
    if(pHasBattery)
    {
        CFTypeRef blob = IOPSCopyPowerSourcesInfo();
        CFArrayRef sources = IOPSCopyPowerSourcesList(blob);
        if(CFArrayGetCount(sources))*pHasBattery = true;
        CFRelease(sources);
        CFRelease(blob);
    }

	CFTimeInterval tiv = IOPSGetTimeRemainingEstimate();
	if(tiv == kIOPSTimeRemainingUnlimited)
    {   if(pPlugged)*pPlugged = true;
        return 100;
    }
    if(tiv == kIOPSTimeRemainingUnknown)return 100;
	return rt::min(2*3600.0, tiv)*100/(2*3600);
#elif defined(PLATFORM_IOS)
    #if defined(PLATFORM_APPLICATION)
	return _objc_get_battery_state(pPlugged);
    #else
    return 10;
    #endif
#elif defined(PLATFORM_ANDROID)
	return 10; // not supported for Android
#elif defined(PLATFORM_LINUX)
	//  /sys/class/power_supply/BAT0...
	//  /proc/acpi/battery/BAT1/state
	return 10; // not supported for Android m
#else
	#error TBD
#endif
}


namespace os
{

namespace _details
{
	int	SolveMonthLetter(int l){ return l>='a'?l-'a':l-'A'; }
	int	SolveMonth(const rt::String_Ref& seg)
	{	if(seg.GetLength() < 3)return 0;
		int sum = SolveMonthLetter(seg[0])*10000 + SolveMonthLetter(seg[1])*100 + SolveMonthLetter(seg[2]);
		switch(sum)
		{
			case ('j'-'a')*10000 + ('a'-'a')*100 + 'n'-'a': return 1;
			case ('f'-'a')*10000 + ('e'-'a')*100 + 'b'-'a': return 2;
			case ('m'-'a')*10000 + ('a'-'a')*100 + 'r'-'a': return 3;
			case ('a'-'a')*10000 + ('p'-'a')*100 + 'r'-'a': return 4;
			case ('m'-'a')*10000 + ('a'-'a')*100 + 'y'-'a': return 5;
			case ('j'-'a')*10000 + ('u'-'a')*100 + 'n'-'a': return 6;
			case ('j'-'a')*10000 + ('u'-'a')*100 + 'l'-'a': return 7;
			case ('a'-'a')*10000 + ('u'-'a')*100 + 'g'-'a': return 8;
			case ('s'-'a')*10000 + ('e'-'a')*100 + 'p'-'a': return 9;
			case ('o'-'a')*10000 + ('c'-'a')*100 + 't'-'a': return 10;
			case ('n'-'a')*10000 + ('o'-'a')*100 + 'v'-'a': return 11;
			case ('d'-'a')*10000 + ('e'-'a')*100 + 'c'-'a': return 12;
			default: return 0;
		}
	}
	bool SolveDate(const rt::String_Ref seg[3], const int num[3], int& year, int& month, int& day)
	{
		if(num[0] == 0 && (month = SolveMonth(seg[0]))>0){ year = num[2]; day = num[1]; } else // March 20,2015
		if(num[1] == 0 && (month = SolveMonth(seg[1]))>0){ year = num[2]; day = num[0]; if(year<day)rt::Swap(year,day); } else // 2015 March 10 or 10 March 2015
		if(num[2] == 0 && (month = SolveMonth(seg[2]))>0){ year = num[0]; day = num[1]; } else // 2015, 10 March
		if(num[2] == 0 || num[1] == 0 || num[0] == 0){ return false; } else
		if(num[0] > 1000){ year = num[0]; month = num[1]; day = num[2]; } else // 2015, 3, 20
		if(num[2] > 1000){ month = num[0]; day = num[1]; year = num[2]; } else
			return false;

		return month >=1 && month <=12 && day>=1 && day<=31;
	}
};

int Timestamp::Fields::FromString(const rt::String_Ref& s, bool low_bound)
{
	static const rt::CharacterSet seps(rt::SS(" -/:.+,;\t\r\nTZ"));
	static const rt::SS pm("pm");
	static const rt::SS PM("PM");

	DayOfWeek = 0;
	rt::String_Ref	f[7];
	int				fi[7];
	UINT co = s.Split<true>(f,7,seps);
	for(UINT i=0;i<co;i++)
		if(f[i].ToNumber(fi[i])==0)return -100;
	switch(co)
	{
	case 7:	// yyyy mm dd hh min sec msec
		Hour = fi[3];	Minute = fi[4];	Second = fi[5];	MillSecond = fi[6];
		if(_details::SolveDate(f, fi, Year, Month, Day))
			return 7;
	case 6:	// yyyy mm dd hh min sec
		Year = fi[0];	Month = fi[1];	Day = fi[2];
		Hour = fi[3];	Minute = fi[4];	Second = fi[5];
		MillSecond = low_bound?0:999;
		if(_details::SolveDate(f, fi, Year, Month, Day))
			return 6;
	case 5: // yyyy mm dd hh min
		Year = fi[0];	Month = fi[1];	Day = fi[2];
		Hour = fi[3];	Minute = fi[4];	
		if(low_bound){ Second = MillSecond = 0; }
		else{ Second = 59;	MillSecond = 999; }
		if(Hour<12 && (f[4].EndsWith(pm) || f[4].EndsWith(PM)))Hour += 12;
		if(_details::SolveDate(f, fi, Year, Month, Day))
			return 5;
	case 4: // hh min sec msec
		Year = 1970;	Month = 1;	Day = 1;
		Hour = fi[0];	Minute = fi[1];	Second = fi[2];	MillSecond = fi[3];
		return 4;
	case 3: // yyyy mm dd, or hh min sec
		if(s.FindCharacter(':')>0)
		{	Year = 1970;	Month = 1;	Day = 1;
			Hour = fi[0];	Minute = fi[1];	Second = fi[2];
			MillSecond = low_bound?0:999;
			return 3;
		}
		else
		{
			if(low_bound){ Hour = Minute = Second = MillSecond = 0; }
			else{ Hour = 23; Minute = 59; Second = 59;	MillSecond = 999; }
			if(_details::SolveDate(f, fi, Year, Month, Day))
				return 3;
		}
	case 2: // hh min
		Year = 1970;	Month = 1;	Day = 1;
		Hour = fi[0];	Minute = fi[1];
		if(low_bound){ Second = MillSecond = 0; }
		else{ Second = 59;	MillSecond = 999; }
		if(Hour<12 && (f[4].EndsWith(pm) || f[4].EndsWith(PM)))Hour += 12;
		return 2;
	case 1:
		{	
			switch(s.GetLength())
			{
			case 8:
				{	UINT t;
					s.ToNumber(t);
					Year = t/10000;	Month = (t%10000)/100;	Day = t%100;
					if(low_bound){ Hour = Minute = Second = MillSecond = 0; }
					else{ Hour = 23; Minute = 59; Second = 59;	MillSecond = 999; }
				}
				return 3;
			case 8 + 6:
				{	UINT t;
					s.SubStr(0, 8).ToNumber(t);
					Year = t/10000;	Month = (t%10000)/100;	Day = t%100;
					s.SubStr(8, 6).ToNumber(t);
					Hour = t/10000; Month = (t%10000)%100; Day = t%100;
					MillSecond = low_bound?0:999;
				}
				return 6;
			case 8 + 4:
				{	UINT t;
					s.SubStr(0, 8).ToNumber(t);
					Year = t/10000;	Month = (t%10000)/100;	Day = t%100;
					s.SubStr(8, 4).ToNumber(t);
					Hour = t/100; Minute = t%100;
					if(low_bound){ Second = MillSecond = 0; }
					else{ Second = 59;	MillSecond = 999; }
				}
				return 5;
			default:
				return 0;
			}
		}
	default: return 0;
	}
}

bool Timestamp::Fields::FromInternetTimeFormat(const rt::String_Ref& s)
{
	if(	s.GetLength() == 29 &&
		*((DWORD*)&s[25]) == 0x544d4720 // " GMT"
	)
	{	LPCSTR b = s._p;
		//Tue, 15 Nov 1994 12:45:26 GMT
		//0123456789012345678901234567890
		//          1         2 
		Month = ParseMonthName(&b[8]);
		Day =		(b[5]-'0')*10 + b[6] - '0';
		Year =		(b[12]-'0')*1000 + (b[13]-'0')*100 + (b[14]-'0')*10 + b[15]-'0';
	
		Hour =		(b[17]-'0')*10 + b[18] - '0';
		Minute =	(b[20]-'0')*10 + b[21] - '0';
		Second =	(b[23]-'0')*10 + b[24] - '0';
	
		MillSecond = DayOfWeek = 0;
		return true;
	}
	return false;
}

UINT Timestamp::Fields::ToInternetTimeFormat(LPSTR buf) const
{
	return (UINT)
	sprintf(buf, "%s, %02d %s %04d %02d:%02d:%02d GMT",
			GetDayOfWeekName().Begin(),		Day,		GetMonthName().Begin(),
			Year,					Hour,		Minute,
			Second);
}


bool Timestamp::GetDateTime(Fields& fields) const
{
	__time64_t t = _Timestamp/1000;
	fields.MillSecond = (int)(_Timestamp%1000);
	
	struct tm * ptm;
#if defined(PLATFORM_WIN)
	ptm = _gmtime64(&t);
#elif defined(PLATFORM_IOS) || defined(PLATFORM_MAC) || defined(PLATFORM_LINUX) || defined(PLATFORM_64BIT)
    ptm = gmtime((time_t*)&t);
#else
	ptm = gmtime64(&t);
#endif

	if(ptm)
	{
		fields.Day = ptm->tm_mday;
		fields.DayOfWeek = ptm->tm_wday;
		fields.Hour = ptm->tm_hour;
		fields.Minute = ptm->tm_min;
		fields.Month = ptm->tm_mon+1;
		fields.Second = ptm->tm_sec;
		fields.Year = ptm->tm_year+1900;
		return true;
	}
	return false;
}

bool Timestamp::GetLocalDateTime(Fields& fields) const	// Local Time
{
	__time64_t t = _Timestamp/1000;
	fields.MillSecond = (int)(_Timestamp%1000);
	
	tzset(); // update timezone info for time conversion 

	struct tm * ptm;
#if defined(PLATFORM_WIN)
	ptm = _localtime64(&t);
#elif defined(PLATFORM_IOS) || defined(PLATFORM_MAC) || defined(PLATFORM_LINUX) || defined(PLATFORM_64BIT)
    ptm = localtime((time_t*)&t);
#else
	ptm = localtime64(&t);
#endif

	if(ptm)
	{
		fields.Day = ptm->tm_mday;
		fields.DayOfWeek = ptm->tm_wday;
		fields.Hour = ptm->tm_hour;
		fields.Minute = ptm->tm_min;
		fields.Month = ptm->tm_mon+1;
		fields.Second = ptm->tm_sec;
		fields.Year = ptm->tm_year+1900;
		return true;
	}
	return false;
}

bool Timestamp::GetDateTime(Fields& f, int Timezone) const	// Local Time
{
	Timestamp t(_Timestamp + Timezone*3600000LL);
	return t.GetDateTime(f);
}

bool Timestamp::SetLocalDateTime(const Fields& f)
{
	struct tm tmstruct = { f.Second, f.Minute, f.Hour, f.Day, f.Month-1, f.Year-1900, 0, 0, -1 };
	__time64_t t;
#if defined(PLATFORM_WIN)
	t = _mktime64(&tmstruct);
#elif defined(PLATFORM_IOS) || defined(PLATFORM_MAC) || defined(PLATFORM_LINUX) || defined(PLATFORM_64BIT)
    t = mktime(&tmstruct);
#else
	t = mktime64(&tmstruct);
#endif
	if(t == -1)return false;
	_Timestamp = t*1000 + f.MillSecond;
	return true;
}

bool Timestamp::SetDateTime(const Fields& f, int Timezone)
{
	Timestamp t;
	if(t.SetDateTime(f))
	{	_Timestamp = t._Timestamp - Timezone*3600000LL;
		return true;
	}
	else return false;
}


bool Timestamp::SetDateTime(const Fields& f)
{
	struct tm tmstruct = {	f.Second, f.Minute, f.Hour, f.Day, f.Month-1, f.Year-1900, 0, 0, 0 };
	__time64_t t;
#if defined(PLATFORM_WIN)
	t = _mkgmtime64(&tmstruct);
#elif defined(PLATFORM_ANDROID) && defined(PLATFORM_32BIT)
	t = timegm64(&tmstruct);
#else
	t = timegm(&tmstruct);
#endif
	if(t == -1)return false;
	_Timestamp = t*1000 + f.MillSecond;
	return true;
}

rt::String_Ref Timestamp::GetMonthName(int month)
{	
	ASSERT(month <= 12 && month > 0);
	static const LPCSTR month_name = 
	"Jan\0Feb\0Mar\0Apr\0May\0Jun\0Jul\0Aug\0Sep\0Oct\0Nov\0Dec\0";
	return rt::String_Ref(&month_name[(month-1)*4],3);
}

int	Timestamp::ParseMonthName(LPCSTR b)
{	
	static const int month_hash[21] = { 10, 5, 9, 0, 0, 7, 0, 6, 1, 0, 0, 0, 8, 11, 0, 3, 12, 2, 4, 0, 0 };
	return month_hash[(b[0]+b[1]+b[2])%21];
}

int Timestamp::ParseWeekdayName(LPCSTR b)
{
	static const int wday_hash[15] = { 0, 0, 3, 4, 6, 5, 0, 0, 0, 0, 1, 7, 0, 2, 0 };
	return wday_hash[(b[0]+b[1]+b[2])%15];
}

LONGLONG Timestamp::ParseTimeSpan(const rt::String_Ref& x)
{	
	int offset;
	double v;
	if((offset = x.ToNumber(v))>=0)
	{
		rt::String_Ref unit = x.SubStr(offset).TrimLeftSpace();
		switch(unit[0])
		{
		case 's': case 'S':	return (LONGLONG)(v*1000.0 + 0.5);
		case 'm': case 'M':	return (LONGLONG)(v*60000.0 + 0.5);
		case 'h': case 'H':	return (LONGLONG)(v*3600000.0 + 0.5);
		case 'd': case 'D':	return (LONGLONG)(v*3600000.0*24 + 0.5);
		case 'w': case 'W':	return (LONGLONG)(v*3600000.0*24*7 + 0.5);
		default :	return (LONGLONG)(v + 0.5);	// millisecond for default
		}
	}

	return 0;
}


rt::String_Ref Timestamp::GetDayOfWeekName(int weekday)
{	
	ASSERT(weekday < 7 && weekday >= 0);
	static const LPCSTR day_name = "Sun\0Mon\0Tue\0Wed\0Thu\0Fri\0Sat\0";
	return rt::String_Ref(&day_name[weekday*4],3);
}

int Timestamp::GetMonthFromDays(int DaysSinceJan1, int year)
{
	static const BYTE month_table[365] = 
	{
		1 ,1 ,1 ,1 ,1 , 1 ,1 ,1 ,1 ,1 , 1 ,1 ,1 ,1 ,1 , 1 ,1 ,1 ,1 ,1 , 1 ,1 ,1 ,1 ,1 , 1 ,1 ,1 ,1 ,1 , 1 ,
		2 ,2 ,2 ,2 ,2 , 2 ,2 ,2 ,2 ,2 , 2 ,2 ,2 ,2 ,2 , 2 ,2 ,2 ,2 ,2 , 2 ,2 ,2 ,2 ,2 , 2 ,2 ,2 ,
		3 ,3 ,3 ,3 ,3 , 3 ,3 ,3 ,3 ,3 , 3 ,3 ,3 ,3 ,3 , 3 ,3 ,3 ,3 ,3 , 3 ,3 ,3 ,3 ,3 , 3 ,3 ,3 ,3 ,3 , 3 ,
		4 ,4 ,4 ,4 ,4 , 4 ,4 ,4 ,4 ,4 , 4 ,4 ,4 ,4 ,4 , 4 ,4 ,4 ,4 ,4 , 4 ,4 ,4 ,4 ,4 , 4 ,4 ,4 ,4 ,4 ,
		5 ,5 ,5 ,5 ,5 , 5 ,5 ,5 ,5 ,5 , 5 ,5 ,5 ,5 ,5 , 5 ,5 ,5 ,5 ,5 , 5 ,5 ,5 ,5 ,5 , 5 ,5 ,5 ,5 ,5 , 5 ,
		6 ,6 ,6 ,6 ,6 , 6 ,6 ,6 ,6 ,6 , 6 ,6 ,6 ,6 ,6 , 6 ,6 ,6 ,6 ,6 , 6 ,6 ,6 ,6 ,6 , 6 ,6 ,6 ,6 ,6 ,
		7 ,7 ,7 ,7 ,7 , 7 ,7 ,7 ,7 ,7 , 7 ,7 ,7 ,7 ,7 , 7 ,7 ,7 ,7 ,7 , 7 ,7 ,7 ,7 ,7 , 7 ,7 ,7 ,7 ,7 , 7 ,
		8 ,8 ,8 ,8 ,8 , 8 ,8 ,8 ,8 ,8 , 8 ,8 ,8 ,8 ,8 , 8 ,8 ,8 ,8 ,8 , 8 ,8 ,8 ,8 ,8 , 8 ,8 ,8 ,8 ,8 , 8 ,
		9 ,9 ,9 ,9 ,9 , 9 ,9 ,9 ,9 ,9 , 9 ,9 ,9 ,9 ,9 , 9 ,9 ,9 ,9 ,9 , 9 ,9 ,9 ,9 ,9 , 9 ,9 ,9 ,9 ,9 ,
		10,10,10,10,10, 10,10,10,10,10, 10,10,10,10,10, 10,10,10,10,10, 10,10,10,10,10, 10,10,10,10,10, 10,
		11,11,11,11,11, 11,11,11,11,11, 11,11,11,11,11, 11,11,11,11,11, 11,11,11,11,11, 11,11,11,11,11,
		12,12,12,12,12, 12,12,12,12,12, 12,12,12,12,12, 12,12,12,12,12, 12,12,12,12,12, 12,12,12,12,12, 12
	};

	if(DaysSinceJan1<= (31+28))return month_table[DaysSinceJan1];
	bool isleapyear = IsLeapYear(year);
	if(!isleapyear)
		return month_table[DaysSinceJan1];
	else
		return month_table[DaysSinceJan1-1];
}

} //  namespace os


namespace os
{
namespace _details
{
	SIZE_T	MEMORY_PAGESIZE = 0;
} // namespace _details

LPVOID VMAlloc(SIZE_T length)
{
	length = (length+_details::MEMORY_PAGESIZE-1)/_details::MEMORY_PAGESIZE*_details::MEMORY_PAGESIZE;

#if defined(PLATFORM_WIN)
	return ::VirtualAlloc(NULL, length, MEM_COMMIT|MEM_RESERVE,PAGE_READWRITE);
#else
	return ::mmap(NULL, length, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
#endif
}

void VMFree(LPVOID ptr, SIZE_T size)
{
	size = (size+_details::MEMORY_PAGESIZE-1)/_details::MEMORY_PAGESIZE*_details::MEMORY_PAGESIZE;

#if defined(PLATFORM_WIN)
	::VirtualFree(ptr, size, MEM_RELEASE);
#else
	::munmap(ptr, size);
#endif
}

bool VMLock(LPVOID ptr, SIZE_T size)		// ensure not page fault
{
#if defined(PLATFORM_WIN)
	return ::VirtualLock(ptr, size);
#else
	return 0 == ::mlock(ptr, size);
#endif
}

bool VMUnlock(LPVOID ptr, SIZE_T size)
{
#if defined(PLATFORM_WIN)
	return ::VirtualUnlock(ptr, size);
#else
	return 0 == ::munlock(ptr, size);
#endif
}


bool CreateGUID(BYTE id[16])
{
#if defined(PLATFORM_WIN)
	RPC_STATUS ret = ::UuidCreate((UUID*)id);
	return ret == RPC_S_OK || ret == RPC_S_UUID_LOCAL_ONLY;
	
#elif defined(PLATFORM_ANDROID) || defined(PLATFORM_LINUX)
	FILE * f = fopen("/proc/sys/kernel/random/uuid","r");
	bool ret;
	if(f)
	{	ret = (16 == fread(id, 1,16, f));
		fclose(f);
		return ret;
	}
	else return false;
#else
	uuid_generate(*((uuid_t*)id));
    return true;
#endif
}

DWORD  GetRandomSeed()
{
	ULONGLONG a;
	os::GetSystemMemoryInfo(&a);
    return TickCount::Get() * (UINT)(a) * (UINT)(a>>32);
}

bool GetDeviceUID(rt::String& str)
{
#if defined(PLATFORM_WIN)
	str = "win";
	HANDLE tk;
	TOKEN_USER* tu = nullptr;
	DWORD ret_len = 0;
	LPSTR sid = nullptr;
	if(	::OpenProcessToken(::GetCurrentProcess(), TOKEN_READ, &tk) &&
		(::GetTokenInformation(tk, TokenUser, NULL, 0, &ret_len)||true) &&
		(tu = (TOKEN_USER*)_Malloc32AL(BYTE,ret_len)) &&
		::GetTokenInformation(tk, TokenUser, tu, ret_len, &ret_len) &&
		::ConvertSidToStringSidA(tu->User.Sid, &sid) &&
		sid
	)
	{	rt::String s = sid+3;
		s.Replace("-","");
		str += rt::SS() + '-' + s.TrimLeft(2);
		LocalFree(sid);
	}
	_SafeFree32AL(tu);

	WCHAR txt[1024];
	if(LoadRegKeyString(HKEY_LOCAL_MACHINE, L"HARDWARE\\DESCRIPTION\\System\\BIOS", L"BaseBoardProduct", txt, sizeofArray(txt)))
	{	str += rt::SS() + '-' + os::__UTF8(txt);
	}

	{	HKEY key = 0;
		DWORD type = REG_SZ;
		DWORD bufsize = sizeofArray(txt);
		LPCWSTR kp = L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
		if(	(	(ERROR_SUCCESS == ::RegOpenKeyExW(HKEY_LOCAL_MACHINE, kp, 0, KEY_READ|KEY_WOW64_64KEY, &key)) ||
				(ERROR_SUCCESS == ::RegOpenKeyExW(HKEY_LOCAL_MACHINE, kp, 0, KEY_READ, &key)) 
			) &&
			(ERROR_SUCCESS == ::RegQueryValueExW(key,L"ProductId", NULL, &type, (LPBYTE)txt, &bufsize))
		)
		{	str += rt::SS() + '-' + os::__UTF8(txt); 
		}
	
		if(key)::RegCloseKey(key);
	}

	DWORD vol = 0;
	if(::GetVolumeInformationA(::getenv("SystemDrive"), NULL, 0, &vol, NULL, NULL, NULL, 0))
	{	str += rt::SS() + '-' + rt::tos::Binary<>(vol);
	}

	return str.GetLength()>3;
#elif defined(PLATFORM_MAC)
	bool ret = false;
    io_registry_entry_t ioRegistryRoot = NULL;
    CFStringRef uuidCf = NULL;
	char uid_string[64];
	if( (ioRegistryRoot = IORegistryEntryFromPath(kIOMasterPortDefault, "IOService:/")) &&
		(uuidCf = (CFStringRef) IORegistryEntryCreateCFProperty(ioRegistryRoot, CFSTR(kIOPlatformUUIDKey), kCFAllocatorDefault, 0)) &&
		CFStringGetCString(uuidCf, uid_string, 64, kCFStringEncodingMacRoman) &&
		rt::String_Ref(uid_string).RemoveCharacters('-').GetLength() == 32
	)
	{	str = rt::SS("mac-") + uid_string;
		ret = true;
	}
    if(uuidCf)CFRelease(uuidCf);
	if(ioRegistryRoot)IOObjectRelease(ioRegistryRoot);
	return ret;
#elif defined(PLATFORM_IOS)
    // TBD, don't rely on adsupport.framework
#elif defined(PLATFORM_LINUX)
	rt::String board_serial, product_uuid;
	if(	os::File::LoadText("/sys/class/dmi/id/board_serial", board_serial) ||
		os::File::LoadText("/sys/class/dmi/id/product_uuid", product_uuid)
	)
	{	str = rt::SS("linux-") + board_serial + '-' + product_uuid;	
		return true;
	}
	else return false;
#elif defined(PLATFORM_ANDROID)
	//import android.provider.Settings.Secure;
	// private String android_id = Secure.getString(getContext().getContentResolver(), Secure.ANDROID_ID);
#else
#endif
	return false;
}

void BruteforceExit()
{
#if defined(PLATFORM_WIN)
	::TerminateProcess(::GetCurrentProcess(), 0);
#else
	_exit(0);
#endif

}

HANDLE LoadDynamicLibrary(LPCSTR fn)
{
#if defined(PLATFORM_WIN)
	static const rt::SS ext(".dll");
#elif defined(PLATFORM_MAC) || defined(PLATFORM_IOS)
	static const rt::SS ext(".dylib");
#else
	static const rt::SS ext(".so");
#endif

	{	rt::String_Ref fname(fn);
		if(fname.GetExtName().IsEmpty() && fname.Last() != '.')
		{
			auto fullname = fname + ext;
			fn = ALLOCA_C_STRING(fullname);
		}
	}

#if defined(PLATFORM_WIN)
	return (HANDLE)::LoadLibraryW(os::__UTF16(fn));
#else
	HANDLE handle = (HANDLE)::dlopen(fn, RTLD_LOCAL|RTLD_NOW);
	if(!handle)
	{
		char *errstr;
		errstr = dlerror();
		if (errstr != NULL)
		{
			_LOG("Dynamic linking error: " << errstr);
		}
	}
	return handle;
#endif
}

LPVOID GetDynamicLibrarySymbol(HANDLE dll, LPCSTR fn)
{
#if defined(PLATFORM_WIN)
	return ::GetProcAddress((HMODULE)dll, fn);
#else
	return ::dlsym((void*)dll, fn);
#endif
}

void UnloadDynamicLibrary(HANDLE h)
{
#if defined(PLATFORM_WIN)
	::FreeLibrary((HMODULE)h);
#else
	::dlclose((void *)h);
#endif
}

void SetProcessPriority(int prio)
{
#if defined(PLATFORM_WIN)
	switch(prio)
	{
	case PROCPRIO_REALTIME: ::SetPriorityClass(::GetCurrentProcess(), REALTIME_PRIORITY_CLASS); break;
	case PROCPRIO_HIGH: ::SetPriorityClass(::GetCurrentProcess(), HIGH_PRIORITY_CLASS); break;
	case PROCPRIO_NORMAL: ::SetPriorityClass(::GetCurrentProcess(), NORMAL_PRIORITY_CLASS); break;
	case PROCPRIO_LOW: ::SetPriorityClass(::GetCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS); break;
	case PROCPRIO_IDLE: ::SetPriorityClass(::GetCurrentProcess(), IDLE_PRIORITY_CLASS); break;
	default: ASSERT(0);
	}
#elif defined(PLATFORM_MAC) || defined(PLATFORM_LINUX) || defined(PLATFORM_IOS) || defined(PLATFORM_ANDROID)
	switch(prio)
	{
	case PROCPRIO_REALTIME: ::setpriority(PRIO_PROCESS, 0, 20); break;
	case PROCPRIO_HIGH: ::setpriority(PRIO_PROCESS, 0, 5); break;
	case PROCPRIO_NORMAL: ::setpriority(PRIO_PROCESS, 0, 0); break;
	case PROCPRIO_LOW: ::setpriority(PRIO_PROCESS, 0, -5); break;
	case PROCPRIO_IDLE: ::setpriority(PRIO_PROCESS, 0, -20); break;
	default: ASSERT(0);
	}
#else
	static_assert(0, "os::SetProcessPriority not implemented");
#endif
}


int  SearchProcess(LPCSTR base_name_in, int* pProcessIds, UINT ProcessIdSize, bool substr_match)	// 0 for not found
{
	rt::String base_name(base_name_in);
	base_name.MakeLower();
	int bufused = 0;

#if defined(PLATFORM_WIN)
	DWORD _process[10240];
	DWORD _proc_byte = 0;
	if(::EnumProcesses(_process, sizeof(_process), &_proc_byte))
	{
		for(int i=0; i<(int)(_proc_byte/sizeof(DWORD)); i++)
		{
			HANDLE h = NULL;
			WCHAR basename[1024];
			if(	(h = ::OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, false, _process[i])) &&
				::GetModuleBaseNameW(h, NULL, basename, sizeofArray(basename))
			)
			{	os::__UTF8 _str(basename);
				_str.MakeLower();

				if(	(substr_match && strstr(_str.Begin(), base_name)) ||
					_str == base_name
				)
				{	pProcessIds[bufused++] = _process[i];
					if(bufused == ProcessIdSize)break;
				}
			}

			if(h)::CloseHandle(h);
		}
	}
#elif defined(PLATFORM_MAC)
#else
#endif

	return bufused;
}

int  SearchProcess(LPCSTR base_name_in, bool substr_match)
{
	int pid = -1;
	if(SearchProcess(base_name_in, &pid, 1, substr_match))
		return pid;
	else
		return -1;
}

bool TerminateProcess(int process_id)
{
#if defined(PLATFORM_WIN)
	HANDLE proc = ::OpenProcess(PROCESS_TERMINATE, false, process_id);
	if(proc)
	{
		return ::TerminateProcess(proc, -1);
	}
	return true;
#elif defined(PLATFORM_ANDROID)
    //kill(process_id, SIGKILL);
    return true;
#else
    ASSERT(0);
	return false;
#endif
}

int  GetProcessId()
{
#if defined(PLATFORM_WIN)
	return ::GetCurrentProcessId();
#else
	return getpid();
#endif
}

} // namespace os


void os::Halt()
{
	_LOG_WARNING("Halt ...");
	for(;;)
		os::Sleep(100);
}

bool os::EncryptData(rt::String& cipertext, const rt::String_Ref& plaintext)
{
#if defined(PLATFORM_WIN)
    if(plaintext.IsEmpty())
    {
        cipertext.Empty();
        return true;
    }
    
    DATA_BLOB	d, out;
    d.pbData = (LPBYTE)plaintext.Begin();
    d.cbData = (DWORD)plaintext.GetLength();
    
    if(CryptProtectData(&d, NULL, NULL, NULL, NULL, CRYPTPROTECT_UI_FORBIDDEN, &out) &&
       out.cbData > 0 &&
       out.pbData
       )
    {
        cipertext.SetLength(out.cbData);
        memcpy(cipertext.Begin(), out.pbData, out.cbData);
        
        rt::Zero(out.pbData, out.cbData);
        LocalFree(out.pbData);
        
        return true;
    }
#else  
    ASSERT(0);
#endif
    
    return false;
}

bool os::DecryptData(rt::String& plaintext, const rt::String_Ref& cipertext)
{
#if defined(PLATFORM_WIN)
    if(cipertext.IsEmpty())
    {
        plaintext.Empty();
        return true;
    }
    
    DATA_BLOB	d, out;
    d.pbData = (LPBYTE)cipertext.Begin();
    d.cbData = (DWORD)cipertext.GetLength();
    
    if(	CryptUnprotectData(&d, NULL, NULL, NULL, NULL, CRYPTPROTECT_UI_FORBIDDEN, &out) &&
       out.cbData > 0 &&
       out.pbData
       )
    {
        plaintext.SetLength(out.cbData);
        memcpy(plaintext.Begin(), out.pbData, out.cbData);
        
        rt::Zero(out.pbData, out.cbData);
        LocalFree(out.pbData);
        
        return true;
    }
#else
    ASSERT(0);
#endif
    
    return false;
}

#if defined(PLATFORM_WIN)
//////////////////////////////////////////////////////////
// All Windows implementations
#include <windows.h>

bool os::Sleep(DWORD msec, const bool* interrupt_flag)
{
	if(interrupt_flag)
	{
		UINT co = msec/32;

		for(UINT i=0; i<co; i++)
		{
			::Sleep(32);
			if(*interrupt_flag)return false;
		}

		if(msec%32)::Sleep(msec%32);
	}
	else
		::Sleep(msec);

	return true;
}

bool os::CreateRegKey(HKEY root, LPCWSTR regkey)
{
	HKEY r;
	bool ret = (ERROR_SUCCESS == ::RegCreateKeyW(root, regkey, &r));
	if(ret)::RegCloseKey(r);
	return ret;
}

bool os::LoadRegKeyString(HKEY root, LPCWSTR regkey, LPCWSTR value, LPWSTR textbuf, DWORD bufsize)
{
	HKEY key = NULL;
	DWORD type = REG_SZ;
	bool ret =
		(ERROR_SUCCESS == ::RegOpenKeyExW(root, regkey, 0, KEY_READ, &key)) &&
		(ERROR_SUCCESS == ::RegQueryValueExW(key, value, NULL, &type, (LPBYTE)textbuf, &bufsize));
	
	if(key)::RegCloseKey(key);
	if(!ret)
	{	textbuf[0] = 0;
	}

	return ret;
}

bool os::LoadRegKeyPath(HKEY root, LPCWSTR regkey, LPCWSTR value_name, LPWSTR textbuf, DWORD bufsize, bool resolve_env)
{
	if(LoadRegKeyString(root, regkey, value_name, textbuf, bufsize))
	{
		int len = (int)wcslen(textbuf);
		if(textbuf[len-1] == L'\\' || textbuf[len-1] == _T('/'))
			textbuf[len-1] = 0;

		WCHAR textenv[1024];
		LPWSTR pe, pet;
		if(	resolve_env && 
			(pe = wcschr(textbuf, L'%')) &&
			(pet = wcschr(pe+1, L'%'))
		)
		{	*pet = L'\0';
			int envlen = ::GetEnvironmentVariableW(pe+1, textenv, sizeofArray(textenv));
			memmove(pe + envlen, pet+1, (len - (pet - textbuf))*sizeof(TCHAR));
			memcpy(pe, textenv, envlen*sizeof(TCHAR));
		}

		return true;
	}

	return false;
}

INT os::LoadRegKeyInt(HKEY root, LPCWSTR regkey, LPCWSTR value, INT default_val)
{
	HKEY key = NULL;
	DWORD type = REG_DWORD;
	DWORD len = sizeof(DWORD);
	bool ret =
		(ERROR_SUCCESS == ::RegOpenKeyExW(root, regkey, 0, KEY_READ, &key)) &&
		(ERROR_SUCCESS == ::RegQueryValueExW(key, value, NULL, &type, (LPBYTE)&default_val, &len));
	
	if(key)::RegCloseKey(key);
	return default_val;
}

bool os::SaveRegKeyString(HKEY root, LPCWSTR regkey, LPCWSTR value_name, LPCWSTR string)
{
	HKEY key = NULL;
	bool ret =
		(ERROR_SUCCESS == ::RegOpenKeyExW(root, regkey, 0, KEY_WRITE, &key)) &&
		(ERROR_SUCCESS == ::RegSetValueExW(key, value_name, 0, REG_SZ, (LPCBYTE)string, sizeof(TCHAR)*(DWORD)(1+wcslen(string))));
	
	if(key)::RegCloseKey(key);
	return ret;
}

bool os::SaveRegKeyInt(HKEY root, LPCWSTR regkey, LPCWSTR value_name, INT val)
{
	HKEY key = NULL;
	bool ret =
		(ERROR_SUCCESS == ::RegOpenKeyExW(root, regkey, 0, KEY_WRITE, &key)) &&
		(ERROR_SUCCESS == ::RegSetValueExW(key, value_name, 0, REG_DWORD, (LPCBYTE)&val, 4));
	
	if(key)::RegCloseKey(key);
	return ret;
}

void os::DeleteRegKeyValue(HKEY root, LPCWSTR regkey, LPCWSTR value_name)
{
	HKEY key = NULL;
	bool ret =
		(ERROR_SUCCESS == ::RegOpenKeyExW(root, regkey, 0, KEY_WRITE, &key)) &&
		(ERROR_SUCCESS == ::RegDeleteValueW(key, value_name));
	
	if(key)::RegCloseKey(key);
}

bool os::OpenDefaultBrowser(LPCSTR url)
{
	WCHAR file[MAX_PATH+MAX_PATH];
	if(LoadRegKeyString(HKEY_CLASSES_ROOT, L"HTTP\\shell\\open\\command", NULL, file, MAX_PATH+MAX_PATH))
	{
		os::__UTF8 cmdline(file);
		rt::String	str;

		if(cmdline.FindString("%1"))
		{
			str = cmdline;
			str.Replace("%1", url);
		}
		else
		{	str = cmdline + ' ' + url;
		}

		STARTUPINFOW si;
		ZeroMemory(&si,sizeof(si));
		si.cb = sizeof(si);
		si.wShowWindow = SW_SHOW;

		PROCESS_INFORMATION pi;
		if(::CreateProcessW(NULL,os::__UTF16(str).Begin(),NULL,NULL,false,0,NULL,NULL,&si,&pi))
		{
			::CloseHandle(pi.hProcess);
			::CloseHandle(pi.hThread);
			return true;
		}
	}

	struct _open_url: public os::Thread
	{
		os::__UTF16		url;
		static DWORD _call(LPVOID p)
		{	
			::ShellExecuteW(NULL,L"open",((_open_url*)p)->url,NULL,NULL,SW_SHOW);
			_SafeDel_ConstPtr((_open_url*)p);
			return os::Thread::THREAD_OBJECT_DELETED_ON_RETURN;
		};
	};

	_open_url* p = _New(_open_url);
	p->url = url;
	p->Create([p](){
		::ShellExecuteW(NULL,L"open", p->url, NULL, NULL, SW_SHOW);
		_SafeDel_ConstPtr(p);
		return os::Thread::THREAD_OBJECT_DELETED_ON_RETURN;
	});
	return true;
}

void os::SetDataBreakPoint(LPCVOID addr, UINT slot, UINT bitwidth, bool write, bool read, bool exec)
{
#if defined(PLATFORM_DEBUG_BUILD)
	
	CONTEXT context = { 0 };
	context.ContextFlags = CONTEXT_DEBUG_REGISTERS;
	GetThreadContext(GetCurrentThread(), &context);
	
	BYTE xxyy, zw;
	switch(bitwidth)
	{
	case 8: xxyy = 0b00<<2; break;
	case 16: xxyy = 0b01<<2; break;
	case 32: xxyy = 0b11<<2; break;
	case 64: xxyy = 0b10<<2; break;
	default: ASSERT(0);
	}

	if(write && !read && !exec)
		zw = 0b01;
	else if(write && read && !exec)
		zw = 0b11;
	else if(!write && !read && exec)
		zw = 0b00;
	else ASSERT(0);

	ULONGLONG bitmask = (0b1111<<(slot*4 + 16)) | (0b11<<(slot*2));
	ULONGLONG bits = (xxyy<<(slot*4 + 16)) | (zw<<(slot*2));

	context.Dr7 = (context.Dr7&(~bitmask)) | bits;
	switch(slot)
	{
	case 0: context.Dr0 = (DWORD64)addr; break;
	case 1: context.Dr1 = (DWORD64)addr; break;
	case 2: context.Dr2 = (DWORD64)addr; break;
	case 3: context.Dr3 = (DWORD64)addr; break;
	default: ASSERT(0);
	}

	//context.Dr7 = 0b0000'1001'1001'1001'0000'0000'0011'1111;
	//                     XXYY XXYY XXYY             ZW ZWZW
	// XX = 00 : 1-bytes
	// XX = 01 : 2-bytes
	// XX = 10 : 8-bytes
	// XX = 11 : 4-bytes
	// YY = 01 : break on write
	// YY = 11 : break on write and read, excluding instruction fetch
	// YY = 10 : break on I/O write and read
	// YY = 00 : break on execute
	// Z  =  1 : global flag for corresponding DR
	// W  =  1 : local flag for corresponding DR
	context.Dr6 = 0; // clear DR6 before returning from the handler
	SetThreadContext(GetCurrentThread(), &context);
	
#endif
}

#else
//////////////////////////////////////////////////////////
// All linux/BSD implementations
#include <unistd.h>

#if defined(PLATFORM_MAC)
#include <CoreFoundation/CFBundle.h>
#include <ApplicationServices/ApplicationServices.h>

bool os::OpenDefaultBrowser(LPCSTR url_in)
{
    CFURLRef url = CFURLCreateWithBytes (
                                         NULL,                  // allocator
                                         (UInt8*)url_in,                   // URLBytes
                                         strlen(url_in),            // length
                                         kCFStringEncodingASCII,      // encoding
                                         NULL                         // baseURL
                                         );
    bool ret = LSOpenCFURLRef(url,0) == noErr;
    CFRelease(url);
    return ret;
}
#elif defined(PLATFORM_IOS)

#if defined(PLATFORM_APPLICATION)
extern void _objc_open_url(const char *urlCString, void (*completionHandler)(bool success, void* c), void* cookie);
bool os::OpenDefaultBrowser(LPCSTR url_in)
{
    struct _cb
    {   bool ret;
        os::Event _wait;
        static void on_complete(bool ret, void *c)
        {   ((_cb*)c)->ret = ret;
            ((_cb*)c)->_wait.Set();
        }
    };
    
    _cb _;
    _objc_open_url(url_in, _cb::on_complete, &_);
    _._wait.WaitSignal();
    return _.ret;
}
#endif // #if defined(PLATFORM_APPLICATION)

#else

bool os::OpenDefaultBrowser(LPCSTR url_in)
{
	return 0 == system(rt::SS("xdg-open \"") + url_in + '"');
}
#endif

bool os::Sleep(DWORD msec, const bool* interrupt_flag)
{
	if(interrupt_flag)
	{
		UINT co = msec/32;

		for(UINT i=0; i<co; i++)
		{
			::usleep(32*1000);
			if(*interrupt_flag)return false;
		}
		
		if(msec%32)::usleep((msec%32)*1000);
	}
	else
	{	
		if(msec>=1000)::sleep(msec/1000);
		if(msec%1000)::usleep((msec%1000)*1000);
	}

	return true;
}

#endif

namespace os
{  
#if defined (PLATFORM_IOS) || defined (PLATFORM_MAC)
struct mach_timebase_info TickCount::__mach_tick_unit;
#endif
} // namespace

namespace os
{

#if		defined(PLATFORM_WIN)
rt::String		_RegAppRegKey;
#elif	defined(PLATFORM_MAC) || defined(PLATFORM_IOS)
#else
#endif

void SetPreferenceLocation(const rt::String_Ref& app_name)
{
#if		defined(PLATFORM_WIN)
	_RegAppRegKey = rt::SS("Software\\") + app_name + rt::SS("\\Preference");
	os::CreateRegKey(HKEY_CURRENT_USER, os::__UTF16(_RegAppRegKey));
#elif	defined(PLATFORM_MAC)
	return; // do nothing on Mac
#else
	ASSERT(0);
#endif
}

INT LoadPreference(const rt::String_Ref& keyname, INT   default_value)
{
#if		defined(PLATFORM_WIN)
	ASSERT(!_RegAppRegKey.IsEmpty());	// call SetPreferenceLocation first
	return LoadRegKeyInt(HKEY_CURRENT_USER, os::__UTF16(_RegAppRegKey), os::__UTF16(keyname), default_value);
#elif	defined(PLATFORM_MAC)
	char out[1024];
	rt::String_Ref ret(out, _objc_preference_load_string(ALLOCA_C_STRING(keyname), out, sizeof(out)));
	if(!ret.IsEmpty())ret.ToNumber(default_value);
	return default_value;
#else
	ASSERT(0);
	return 0;
#endif
}	 
	 
bool SavePreference(const rt::String_Ref& keyname, INT value)
{	 
#if		defined(PLATFORM_WIN)
	ASSERT(!_RegAppRegKey.IsEmpty());	// call SetPreferenceLocation first
	return SaveRegKeyInt(HKEY_CURRENT_USER, os::__UTF16(_RegAppRegKey), os::__UTF16(keyname), value);
#elif	defined(PLATFORM_MAC)
	_objc_preference_save_string(ALLOCA_C_STRING(keyname), rt::tos::Number(value).Begin());
	return true;
#else
	ASSERT(0);
	return 0;
#endif
}
	 
bool LoadPreferenceString(const rt::String_Ref& keyname, rt::String& out_val, const rt::String_Ref& default_value)
{	 
#if		defined(PLATFORM_WIN)
	ASSERT(!_RegAppRegKey.IsEmpty());	// call SetPreferenceLocation first
	WCHAR buf[1024];
	if(LoadRegKeyString(HKEY_CURRENT_USER, os::__UTF16(_RegAppRegKey), os::__UTF16(keyname), buf, sizeofArray(buf)))
	{	out_val = os::__UTF8(buf);
		return true;
	}
	out_val = default_value;
	return false;
#elif	defined(PLATFORM_MAC)
	char out[1024];
	rt::String_Ref ret(out, _objc_preference_load_string(ALLOCA_C_STRING(keyname), out, sizeof(out)));
	if(ret.IsEmpty())
    {
        out_val = default_value;
        return false;
    }
	else
	{	out_val = ret;
		return true;
	}
#else
	ASSERT(0);
	return 0;
#endif
}	 
	 
bool SavePreferenceString(const rt::String_Ref& keyname, const rt::String_Ref& value)
{
#if		defined(PLATFORM_WIN)
	ASSERT(!_RegAppRegKey.IsEmpty());	// call SetPreferenceLocation first
	return SaveRegKeyString(HKEY_CURRENT_USER, os::__UTF16(_RegAppRegKey), os::__UTF16(keyname), os::__UTF16(value));
#elif	defined(PLATFORM_MAC)
	_objc_preference_save_string(ALLOCA_C_STRING(keyname), ALLOCA_C_STRING(value));
	return true;
#else
	ASSERT(0);
	return 0;
#endif
}
} // namespace os

namespace os
{
namespace _details
{
	struct os_class_init
	{
		os_class_init()
		{
		#if defined(PLATFORM_IOS) || defined (PLATFORM_MAC)
            mach_timebase_info(&::os::TickCount::__mach_tick_unit);
            ::os::TickCount::__mach_tick_unit.denom *= 1000000;
		#endif
				
		#if defined(PLATFORM_WIN)
			SYSTEM_INFO si;
			GetSystemInfo(&si);
            ::os::_details::MEMORY_PAGESIZE = rt::max<int>(1024,si.dwPageSize);
		#else
            ::os::_details::MEMORY_PAGESIZE = rt::max<int>(1024,(int)sysconf(_SC_PAGE_SIZE));
		#endif
		}
	};
	os_class_init __init;
}} // namespace os::_details


namespace os
{

ConsoleProgressIndicator::ConsoleProgressIndicator(ULONGLONG total, LPCSTR hint)
{
	_Total = total;
	_Prog = 0;
	_LastDisplay.LoadCurrentTime();
	_StartTime.LoadCurrentTime();

	if(hint){ _Hint = hint; }
	else{ _Hint = "In Progress: "; }
}

ConsoleProgressIndicator::~ConsoleProgressIndicator()
{
	printf("%s: %llu done, %s                         \n", _Hint.GetString(), (long long unsigned int)_Total, rt::tos::TimeSpan<>(_StartTime.TimeLapse()).Begin());
}

void ConsoleProgressIndicator::_Display()
{
	if(_LastDisplay.TimeLapse() > 330)
	{
		_LastDisplay.LoadCurrentTime();
		if(_Total)
		{
			float prec = _Prog*100.0f/_Total;
			char bar[21];
			for(int i=0;i<20;i++)
			{	float t = i - prec*20;
				if(t<0)			bar[i] = '>';
				else if(t<0.5)	bar[i] = '=';
				else			bar[i] = '-';
			}
			bar[20] = 0;
			printf("%s: %llu (%0.2f%%), [%s] %s remains   \r", _Hint.GetString(), (long long unsigned int)_Prog, prec, bar, rt::tos::TimeSpan<>(_StartTime.TimeLapse()*(_Total-_Prog)/_Prog).Begin());
		}
		else
		{	
			printf("%s: %llu, %s passed   \r", _Hint.GetString(), (long long unsigned int)_Prog, rt::tos::TimeSpan<>(_StartTime.TimeLapse()).Begin());
		}
	}
}

ProgressReport::Scope::Scope(uint64_t scope_range, ProgressReport& c)
	:Report(c)
{
	TotalBase = c._Total;
	ScaleBase = c._Scale;
	RangeBase = c._Range;
	ScopeBase = c._pCurrentScope;

	c._Scale = ScaleBase*scope_range/100;
	c._Range = 100;
	c._pCurrentScope = this;
}

ProgressReport::Scope::~Scope()
{
	if(!Report._Aborted)
	{
		Report.SetProgress(Report._Range);

		Report._Total = TotalBase + Report._Scale*Report._Range;
		Report._Scale = ScaleBase;
		Report._Range = RangeBase;
	}
	
	Report._pCurrentScope = ScopeBase;
}

void ProgressReport::Reset(uint64_t progress_range)
{
	_Aborted = false;
	_Total = 0;
	_Scale = 1.0/progress_range;
	_Range = progress_range;
	_pCallback = nullptr;
	_pCurrentScope = nullptr;
	_LastCallBackTime = 0;
	Restart();
}

void ProgressReport::SetProgressRange(uint64_t range)
{
	uint64_t prog;
	if(_pCurrentScope)
	{
		prog = (uint32_t)((_Total - _pCurrentScope->TotalBase)/_Scale + 0.5);
	}
	else
	{
		prog = (uint32_t)(_Total/_Scale + 0.5);
	}

	_Scale = _Scale*_Range/range;
	_Range = range;

	SetProgress(prog);
	_InvokeCallback(true);
}

void ProgressReport::SetProgress(uint64_t progress) // in [0, progress_range]
{
	progress = rt::min(_Range, progress);

	if(_pCurrentScope)
	{
		_Total = _pCurrentScope->TotalBase + _Scale*progress;
	}
	else
	{
		_Total = progress*_Scale;
	}

	_InvokeCallback(false);
}

void ProgressReport::_InvokeCallback(bool ignore_interval) const
{
	if(_pCallback)
	{
		uint64_t t = os::Timestamp::Get();
		if(!ignore_interval && t - _LastCallBackTime < _CallbackInterval)
			return;

		ASSERT(_CallFunc);
		_CallFunc(*this);

		_LastCallBackTime = t;
	}
}

} // namespace os

#if defined(PLATFORM_WIN)
#include <Wincrypt.h>
namespace os
{
namespace _details
{	
	struct __InitCryptProv
	{	HCRYPTPROV	_hCryptProv;
		__InitCryptProv(){ ::CryptAcquireContextW(&_hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT); }
		~__InitCryptProv(){ ::CryptReleaseContext(_hCryptProv, 0); _hCryptProv = NULL; }
	};
};

bool Randomize(LPVOID p, UINT len)
{
	thread_local _details::__InitCryptProv _;
	return ::CryptGenRandom(_._hCryptProv, len, (LPBYTE)p);
}
}	// namespace sec

#elif defined(PLATFORM_LINUX) || defined(PLATFORM_ANDROID)

namespace os
{
bool Randomize(LPVOID p_in, UINT len)
{	LPBYTE p = (LPBYTE)p_in;
	int randomData = open("/dev/urandom", O_RDONLY);
	if(randomData >= 0)
	{	size_t copied = 0;
		while(copied < len)
		{
			ssize_t result = read(randomData, p + copied, len - copied);
			if(result < 0)return false;
			copied += result;
		}
		close(randomData);
		return true;
	}
	return false;
}	
} // namespace sec

#elif defined(PLATFORM_IOS) || defined(PLATFORM_MAC)
// implemented by _objc_randomize
#else
static_assert(0, "os::Randomize is not implemented");
#endif 

