#pragma once
/**
 * @file rocksdb_conf.h
 * @author SFC dev team
 * @brief 
 * @version 1.0
 * @date 2021-05-08
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
/** \defgroup rocksdb rocksdb
 * @ingroup ext
 *  @{
 */
#include "../../os/platform.h"
#include <functional>

#define ROCKSDB_LITE 1
#define ROCKSDB_PORTABLE 1
#define ROCKSDB_SUPPORT_THREAD_LOCAL 1

#if defined(PLATFORM_WIN)
    #define OS_WIN 1
	#define ROCKSDB_WINDOWS_UTF8_FILENAMES 1
	#pragma comment(lib, "Shlwapi.lib")
#elif defined(PLATFORM_MAC) || defined(PLATFORM_IOS)
    #define OS_MACOSX 1
    #define ROCKSDB_PLATFORM_POSIX 1
#elif defined(PLATFORM_LINUX) || defined(PLATFORM_ANDROID)
	#define OS_LINUX 1
	#define ROCKSDB_PLATFORM_POSIX 1
#else
    #define ROCKSDB_PLATFORM_POSIX 1
#endif

#if defined(ROCKSDB_PLATFORM_POSIX)
    #define ROCKSDB_LIB_IO_POSIX 1
#endif
/** @}*/