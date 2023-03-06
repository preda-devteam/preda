#pragma once
#include "../../../os/kernel.h"

#pragma warning(disable:4101)

#if defined(PLATFORM_WIN)
	#ifdef PLATFORM_64BIT
		#include "../platforms/win_x64/botan_all.h"
	#else
		#include "../platforms/win_x86/botan_all.h"
	#endif
#elif defined(PLATFORM_ANDROID)
	#if defined (__mips__)
		#include "../platforms/botan_ndk_mips.h"
	#elif defined (__arm__)
		#include "../platforms/android_arm/botan_all.h"
	#elif defined (__aarch64__)
		#include "../platforms/android_arm64/botan_all.h"
	#elif defined (__i386__)
		#include "../platforms/botan_ndk_x86.h"
	#else
		#error unknown driod platform
	#endif
#elif defined(PLATFORM_MAC)
	#ifdef PLATFORM_64BIT
		#include "../platforms/mac_x64/botan_all.h"
	#else
        #error 32-bit is not supported on MacOS
	#endif
#elif defined(PLATFORM_IOS)
    #ifdef PLATFORM_64BIT
        #include "../platforms/ios_arm64/botan_all.h"
    #else
        #error 32-bit is not supported on iOS
    #endif
#elif defined(PLATFORM_LINUX)
    #ifdef PLATFORM_64BIT
        #include "../platforms/linux_x64/botan_all.h"
    #else
        #include "../platforms/linux_x32/botan_all.h"
    #endif
#else
	#error unknown platform
#endif

#ifdef PLATFORM_ANDROID
//#define _LOG_EXPCEPTION(x)	{ do { (void)(x); } while (0) }
#define _LOG_EXPCEPTION(x) {}
#else
#define _LOG_EXPCEPTION(x)	_LOG(x)
#endif

namespace rt
{
namespace tos
{

struct StdPodVec: public Base16
{
	template<typename T>
	StdPodVec(const T& x)
		:Base16(x.data(), x.size()*sizeof(x[0]))
	{}
};

struct BigInt: public StdPodVec
{
	BigInt(const Botan::BigInt& x)
		:StdPodVec(x.get_word_vector())
	{}
};


}} // rt::tos

