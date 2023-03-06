/*
// Copyright 1999-2020 Intel Corporation All Rights Reserved.
//
// The source code, information and material ("Material") contained herein is
// owned by Intel Corporation or its suppliers or licensors, and title
// to such Material remains with Intel Corporation or its suppliers or
// licensors. The Material contains proprietary information of Intel
// or its suppliers and licensors. The Material is protected by worldwide
// copyright laws and treaty provisions. No part of the Material may be used,
// copied, reproduced, modified, published, uploaded, posted, transmitted,
// distributed or disclosed in any way without Intel's prior express written
// permission. No license under any patent, copyright or other intellectual
// property rights in the Material is granted to or conferred upon you,
// either expressly, by implication, inducement, estoppel or otherwise.
// Any license under such intellectual property rights must be express and
// approved by Intel in writing.
//
// Unless otherwise agreed by Intel in writing,
// you may not remove or alter this notice or any other notice embedded in
// Materials by Intel or Intel's suppliers or licensors in any way.
//
*/

/*
//              Intel(R) Integrated Performance Primitives (Intel(R) IPP)
//              Common Types and Macro Definitions
//
//
*/


#ifndef IPPDEFS_H__
#define IPPDEFS_H__

#ifdef __cplusplus
extern "C" {
#endif


#if defined( _IPP_PARALLEL_STATIC ) || defined( _IPP_PARALLEL_DYNAMIC )
  #pragma message("Threaded versions of Intel(R) IPP libraries are deprecated and will be removed in one of the future Intel(R) IPP releases. Use the following link for details: https://software.intel.com/sites/products/ipp-deprecated-features-feedback/")
#endif

#if defined (_WIN64)
#define INTEL_PLATFORM "intel64/"
#elif defined (_WIN32)
#define INTEL_PLATFORM "ia32/"
#endif

#if !defined( IPPAPI )

  #if defined( IPP_W32DLL ) && (defined( _WIN32 ) || defined( _WIN64 ))
    #if defined( _MSC_VER ) || defined( __ICL )
      #define IPPAPI( type,name,arg ) \
                     __declspec(dllimport)   type IPP_STDCALL name arg;
    #else
      #define IPPAPI( type,name,arg )        type IPP_STDCALL name arg;
    #endif
  #else
    #define   IPPAPI( type,name,arg )        type IPP_STDCALL name arg;
  #endif

#endif

#if (defined( __ICL ) || defined( __ECL ) || defined(_MSC_VER)) && !defined( _PCS ) && !defined( _PCS_GENSTUBS )
  #if( __INTEL_COMPILER >= 1100 ) /* icl 11.0 supports additional comment */
    #if( _MSC_VER >= 1400 )
      #define IPP_DEPRECATED( comment ) __declspec( deprecated ( comment ))
    #else
      #pragma message ("your icl version supports additional comment for deprecated functions but it can't be displayed")
      #pragma message ("because internal _MSC_VER macro variable setting requires compatibility with MSVC7.1")
      #pragma message ("use -Qvc8 switch for icl command line to see these additional comments")
      #define IPP_DEPRECATED( comment ) __declspec( deprecated )
    #endif
  #elif( _MSC_FULL_VER >= 140050727 )&&( !defined( __INTEL_COMPILER )) /* VS2005 supports additional comment */
    #define IPP_DEPRECATED( comment ) __declspec( deprecated ( comment ))
  #elif( _MSC_VER <= 1200 )&&( !defined( __INTEL_COMPILER )) /* VS 6 doesn't support deprecation */
    #define IPP_DEPRECATED( comment )
  #else
    #define IPP_DEPRECATED( comment ) __declspec( deprecated )
  #endif
#elif (defined(__ICC) || defined(__ECC) || defined( __GNUC__ )) && !defined( _PCS ) && !defined( _PCS_GENSTUBS )
  #if defined( __GNUC__ )
    #if ( __GNUC__ * 100 + __GNUC_MINOR__ ) >= 405
      #define IPP_DEPRECATED( message ) __attribute__(( deprecated( message )))
    #else
      #define IPP_DEPRECATED( message ) __attribute__(( deprecated ))
    #endif
  #else
    #define IPP_DEPRECATED( comment ) __attribute__(( deprecated ))
  #endif
#else
  #define IPP_DEPRECATED( comment )
#endif

#if (defined( __ICL ) || defined( __ECL ) || defined(_MSC_VER))
  #if !defined( IPP_NO_DEFAULT_LIB )
    #if  (( defined( _IPP_PARALLEL_DYNAMIC ) && !defined( _IPP_PARALLEL_STATIC ) && !defined( _IPP_SEQUENTIAL_DYNAMIC ) && !defined( _IPP_SEQUENTIAL_STATIC )) || \
          (!defined( _IPP_PARALLEL_DYNAMIC ) &&  defined( _IPP_PARALLEL_STATIC ) && !defined( _IPP_SEQUENTIAL_DYNAMIC ) && !defined( _IPP_SEQUENTIAL_STATIC )) || \
          (!defined( _IPP_PARALLEL_DYNAMIC ) && !defined( _IPP_PARALLEL_STATIC ) &&  defined( _IPP_SEQUENTIAL_DYNAMIC ) && !defined( _IPP_SEQUENTIAL_STATIC )) || \
          (!defined( _IPP_PARALLEL_DYNAMIC ) && !defined( _IPP_PARALLEL_STATIC ) && !defined( _IPP_SEQUENTIAL_DYNAMIC ) &&  defined( _IPP_SEQUENTIAL_STATIC )))
    #elif (!defined( _IPP_PARALLEL_DYNAMIC ) && !defined( _IPP_PARALLEL_STATIC ) && !defined( _IPP_SEQUENTIAL_DYNAMIC ) && !defined( _IPP_SEQUENTIAL_STATIC ))
      #define IPP_NO_DEFAULT_LIB
    #else
      #error Illegal combination of _IPP_PARALLEL_DYNAMIC/_IPP_PARALLEL_STATIC/_IPP_SEQUENTIAL_DYNAMIC/_IPP_SEQUENTIAL_STATIC, only one definition can be defined
    #endif
  #endif
#else
  #define IPP_NO_DEFAULT_LIB
  #if (defined( _IPP_PARALLEL_DYNAMIC ) || defined( _IPP_PARALLEL_STATIC ) || defined(_IPP_SEQUENTIAL_DYNAMIC) || defined(_IPP_SEQUENTIAL_STATIC))
    #pragma message ("defines _IPP_PARALLEL_DYNAMIC/_IPP_PARALLEL_STATIC/_IPP_SEQUENTIAL_DYNAMIC/_IPP_SEQUENTIAL_STATIC do not have any effect in current configuration")
  #endif
#endif

#if !defined( IPP_NO_DEFAULT_LIB )
  #if defined( _IPP_PARALLEL_STATIC )
    #pragma comment( lib, "libiomp5md" )
  #endif
#endif

#include "ippbase.h"
#include "ipptypes.h"

#ifdef __cplusplus
}
#endif

#endif /* IPPDEFS_H__ */
