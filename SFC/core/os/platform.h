#pragma once

/**
 * @file platform.h
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
/** \defgroup platform platform
 * @ingroup os
 *  @{
 */
#if defined(PLATFORM_RECOGNIZED)
	#error CFP platform header conflict
#endif

///////////////////////////////////////////////
// Platfrom detection
//	PLATFORM_WIN
//	PLATFORM_IOS
//	PLATFORM_MAC
//	PLATFORM_ANDROID

#if		defined(__ANDROID__)
		#define PLATFORM_ANDROID
		#define PLATFORM_RECOGNIZED
#elif	defined(__APPLE__)
		#include "TargetConditionals.h"
		#if TARGET_OS_IPHONE
		    #define PLATFORM_IOS
		#elif TARGET_IPHONE_SIMULATOR
			#define PLATFORM_IOS
		#else
		    #define PLATFORM_MAC
		#endif
		#define PLATFORM_RECOGNIZED
#elif	defined(_WIN32)
		#define PLATFORM_WIN
		#define PLATFORM_RECOGNIZED
	#if _MSC_VER >= 1900  ///< Visual Studio 2015
	#endif
#elif	defined(__linux__) || defined(__linux)
		#define PLATFORM_LINUX
		#define PLATFORM_RECOGNIZED
#else
		#error Unrecognized Platform
#endif


/**
 * @brief  define this macro project-wisely to prevent using 
 *  of some APIs that are not widely supported
 *  #define PLATFORM_MAX_COMPATIBILITY
 */
#if		defined(PLATFORM_WIN) || defined(PLATFORM_MAC) || defined(PLATFORM_LINUX)

#ifndef	PLATFORM_DISABLE_INTEL_IPP
		#define PLATFORM_INTEL_IPP_SUPPORT
#endif

		#define PLATFORM_OPENGL_SUPPORT

#if defined(PLATFORM_WIN) || defined(PLATFORM_MAC) || defined(PLATFORM_LINUX)
		#define PLATFORM_INTEL_MKL_SUPPORT
#endif

#elif	defined(PLATFORM_IOS) || defined(PLATFORM_ANDROID)
		#define PLATFORM_OPENGL_ES_SUPPORT
#endif

#if	(defined(PLATFORM_WIN) && defined(_WIN64)) || defined(__LP64__)
	#define PLATFORM_64BIT
#else
	#define PLATFORM_32BIT
#endif

#if	defined(PLATFORM_WIN) || defined(PLATFORM_MAC) || defined(PLATFORM_IOS)

#if defined(_DEBUG) || defined(DEBUG)
	#define PLATFORM_DEBUG_BUILD
#else
	#define PLATFORM_RELEASE_BUILD
#endif

#elif defined(PLATFORM_LINUX) || defined(PLATFORM_ANDROID)

#if defined(NDEBUG)
	#define PLATFORM_RELEASE_BUILD
#else
	#define PLATFORM_DEBUG_BUILD
#endif

#endif
/** @}*/
/** @}*/

