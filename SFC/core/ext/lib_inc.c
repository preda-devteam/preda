#pragma warning(disable: 4819)
#pragma warning(disable: 4996)
#pragma warning(disable: 4101)
#pragma warning(disable: 4244)
#pragma warning(disable: 4267)
#pragma warning(disable: 4018)
#pragma warning(disable: 4028)

#include "../os/predefines.h"
#include "ipp/ipp_config.h"
#include <math.h>

#if defined(PLATFORM_IOS) || defined(PLATFORM_ANDROID)
#define PNG_NO_MMX_CODE
#endif


#ifdef PLATFORM_INTEL_IPP_SUPPORT

/////////////////////////////////////////////////
// Platform with IPP
#ifndef PLATFORM_WIN
typedef int BOOL;
static const int TRUE = 1;
static const int FALSE = 0;
#endif

#include "ipp/inc/ipp.h"
#include "ipp/ipp_zlib/zlib_inc.c"

/////////////////////////////////////////////////
// Platform without IPP
#else
	#include <stdio.h>
	#include "zlib/zlib/zlib_inc.c"
#endif
/////////////////////////////////////////////////
#include "ipp/jpg/jpg_inc.c"
/////////////////////////////////////////////////
// Clear some garbage symbol
#undef Freq
#undef Code
#undef Dad 
#undef Len 

#include "ipp/png/png_inc.c"
#undef MASK


#undef MAX

#ifndef LOBYTE
#define LOBYTE(w)           ((BYTE)((w) & 0xff))
#endif

#ifndef HIBYTE
#define HIBYTE(w)           ((BYTE)(((w) >> 8) & 0xff))
#endif

#include "ipp/gif/gif_inc.c"
#include "7zip/inc/7zip_inc.c"

