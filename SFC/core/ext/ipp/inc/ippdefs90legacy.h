/* 
// Copyright 2015 Intel Corporation All Rights Reserved.
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

/* /////////////////////////////////////////////////////////////////////////////
//
//         Intel(R) Integrated Performance Primitives
//             Common Types and Macro Definitions
//
*/

#ifndef __IPPDEFS_90_LEGACY_H__
#define __IPPDEFS_90_LEGACY_H__

#include "ippbase.h"
#include "ipptypes.h"
#if !defined( __STDCALL )
#define __STDCALL IPP_STDCALL
#endif


#ifdef __cplusplus
extern "C" {
#endif


#define IPP_LEGACY_COMMENT "Function from IPP 9.0 legacy domain is used"

#if !defined( IPP_LEGACY_WRN )
  #if (defined( __ICL ) || defined( __ECL ) || defined(_MSC_VER))
    #if( __INTEL_COMPILER >= 1100 ) /* icl 11.0 supports additional comment */
      #if( _MSC_VER >= 1400 )
        #define IPP_LEGACY_WRN __declspec( deprecated ( IPP_LEGACY_COMMENT ))
      #else
        #pragma message ("your icl version supports additional comment for deprecated functions but it can't be displayed")
        #pragma message ("because internal _MSC_VER macro variable setting requires compatibility with MSVC7.1")
        #pragma message ("use -Qvc8 switch for icl command line to see these additional comments")
        #define IPP_LEGACY_WRN __declspec( IPP_LEGACY_COMMENT )
      #endif
    #elif( _MSC_FULL_VER >= 140050727 )&&( !defined( __INTEL_COMPILER )) /* VS2005 supports additional comment */
      #define IPP_LEGACY_WRN __declspec( deprecated ( IPP_LEGACY_COMMENT ))
    #elif( _MSC_VER <= 1200 )&&( !defined( __INTEL_COMPILER )) /* VS 6 doesn't support deprecation */
      #define IPP_LEGACY_WRN
    #else
      #define IPP_LEGACY_WRN __declspec( deprecated )
    #endif
  #elif (defined(__ICC) || defined(__ECC) || defined( __GNUC__ )) && !defined( _PCS ) && !defined( _PCS_GENSTUBS ) && !defined( _NO_IPP_LEGACY_WRN )
    #if defined( __GNUC__ )
      #if __GNUC__ >= 4 && __GNUC_MINOR__ >= 5
        #define IPP_LEGACY_WRN __attribute__(( deprecated( IPP_LEGACY_COMMENT )))
      #else
        #define IPP_LEGACY_WRN __attribute__(( deprecated ))
      #endif
    #else
      #define IPP_LEGACY_WRN __attribute__(( deprecated ))
    #endif
  #else
     #define IPP_LEGACY_WRN
  #endif
  #else
    #undef IPP_LEGACY_WRN
    #define IPP_LEGACY_WRN
#endif

#if !defined( LEGACY90IPPAPI )

  #if defined( IPP_W32DLL ) && (defined( _WIN32 ) || defined( _WIN64 ))
    #if defined( _MSC_VER ) || defined( __ICL )
      #define LEGACY90IPPAPI( type,name,arg ) \
                     IPP_LEGACY_WRN  __declspec(dllimport)        type __STDCALL name arg;
    #else
      #define LEGACY90IPPAPI( type,name,arg ) \
                     IPP_LEGACY_WRN type __STDCALL name arg;
    #endif
  #else
    #define   LEGACY90IPPAPI( type,name,arg ) \
                     IPP_LEGACY_WRN type __STDCALL name arg;
  #endif

#endif

/*****************************************************************************/
/*                   Below are ippCore domain specific definitions           */
/*****************************************************************************/

#if !defined( _OWN_BLDPCS )
typedef enum {
 /* Enumeration:               Processor:                                                         */
    ippCpuUnknown  = 0x00,
    ippCpuPP       = 0x01, /* Intel(R) Pentium(R) processor                                       */
    ippCpuPMX      = 0x02, /* Intel(R) Pentium(R) processor with MMX(TM) technology                        */
    ippCpuPPR      = 0x03, /* Intel(R) Pentium(R) Pro processor                                            */
    ippCpuPII      = 0x04, /* Intel(R) Pentium(R) II processor                                             */
    ippCpuPIII     = 0x05, /* Intel(R) Pentium(R) III processor and Pentium(R) III Xeon(R) processor       */
    ippCpuP4       = 0x06, /* Intel(R) Pentium(R) 4 processor and Intel(R) Xeon(R) processor               */
    ippCpuP4HT     = 0x07, /* Intel(R) Pentium(R) 4 Processor with HT Technology                           */
    ippCpuP4HT2    = 0x08, /* Intel(R) Pentium(R) 4 processor with Intel(R) Streaming SIMD Extensions 3    */
    ippCpuCentrino = 0x09, /* Intel(R) Centrino(R) mobile technology                              */
    ippCpuCoreSolo = 0x0a, /* Intel(R) Core(TM) Solo processor                                    */
    ippCpuCoreDuo  = 0x0b, /* Intel(R) Core(TM) Duo processor                                     */
    ippCpuITP      = 0x10, /* Intel(R) Itanium(R) processor                                       */
    ippCpuITP2     = 0x11, /* Intel(R) Itanium(R) 2 processor                                     */
    ippCpuEM64T    = 0x20, /* Intel(R) 64 Instruction Set Architecture (ISA)                      */
    ippCpuC2D      = 0x21, /* Intel(R) Core(TM) 2 Duo processor                                   */
    ippCpuC2Q      = 0x22, /* Intel(R) Core(TM) 2 Quad processor                                  */
    ippCpuPenryn   = 0x23, /* Intel(R) Core(TM) 2 processor with Intel(R) SSE4.1                  */
    ippCpuBonnell  = 0x24, /* Intel(R) Atom(TM) processor                                         */
    ippCpuNehalem  = 0x25, /* Intel(R) Core(TM) i7 processor                                      */
    ippCpuNext     = 0x26,
    ippCpuSSE      = 0x40, /* Processor supports Intel(R) Streaming SIMD Extensions (Intel(R) SSE) instruction set      */
    ippCpuSSE2     = 0x41, /* Processor supports Intel(R) Streaming SIMD Extensions 2 (Intel(R) SSE2) instruction set    */
    ippCpuSSE3     = 0x42, /* Processor supports Intel(R) Streaming SIMD Extensions 3 (Intel(R) SSE3) instruction set    */
    ippCpuSSSE3    = 0x43, /* Processor supports Intel(R) Supplemental Streaming SIMD Extension 3 (Intel(R) SSSE3) instruction set */
    ippCpuSSE41    = 0x44, /* Processor supports Intel(R) Streaming SIMD Extensions 4.1 (Intel(R) SSE4.1) instruction set  */
    ippCpuSSE42    = 0x45, /* Processor supports Intel(R) Streaming SIMD Extensions 4.2 (Intel(R) SSE4.2) instruction set  */
    ippCpuAVX      = 0x46, /* Processor supports Intel(R) Advanced Vector Extensions (Intel(R) AVX) instruction set     */
    ippCpuAES      = 0x47, /* Processor supports Intel(R) AES New Instructions                           */
    ippCpuSHA      = 0x48, /* Processor supports Intel(R) SHA New Instructions                           */
    ippCpuF16RND   = 0x49, /* Processor supports RDRRAND & Float16 instructions                   */
    ippCpuAVX2     = 0x4a, /* Processor supports Intel(R) Advanced Vector Extensions 2 (Intel(R) AVX2) instruction set   */
    ippCpuADCOX    = 0x4b, /* Processor supports ADCX and ADOX instructions                       */
    ippCpuX8664    = 0x60  /* Processor supports 64 bit extension                                 */
} IppCpuType;

#endif  /* _OWN_BLDPCS */

/*****************************************************************************/
/*                   Below are ippSP legacy specific definitions             */
/*****************************************************************************/
typedef struct ToneState_16s IppToneState_16s;
typedef struct TriangleState_16s IppTriangleState_16s;

typedef struct FFTSpec_C_16sc   IppsFFTSpec_C_16sc;
typedef struct FFTSpec_C_16s    IppsFFTSpec_C_16s;
typedef struct FFTSpec_R_16s    IppsFFTSpec_R_16s;
typedef struct FFTSpec_C_32sc   IppsFFTSpec_C_32sc;
typedef struct FFTSpec_C_32s    IppsFFTSpec_C_32s;
typedef struct FFTSpec_R_32s    IppsFFTSpec_R_32s;
typedef struct FFTSpec_R_16s32s IppsFFTSpec_R_16s32s;

typedef struct DFTSpec_C_16sc       IppsDFTSpec_C_16sc;
typedef struct DFTSpec_C_16s        IppsDFTSpec_C_16s;
typedef struct DFTSpec_R_16s        IppsDFTSpec_R_16s;
typedef struct DFTOutOrdSpec_C_32fc IppsDFTOutOrdSpec_C_32fc;
typedef struct DFTOutOrdSpec_C_64fc IppsDFTOutOrdSpec_C_64fc;

typedef struct DCTFwdSpec_16s IppsDCTFwdSpec_16s;
typedef struct DCTInvSpec_16s IppsDCTInvSpec_16s;

typedef struct sWTFwdState_8s32f  IppsWTFwdState_8s32f;
typedef struct sWTInvState_32f8s  IppsWTInvState_32f8s;

typedef struct IIRState32s_16s IppsIIRState32s_16s;
typedef struct IIRState32sc_16sc IppsIIRState32sc_16sc;

typedef struct FIRState_32f IppsFIRState_32f;
typedef struct FIRState_32fc IppsFIRState_32fc;
typedef struct FIRState32f_16s IppsFIRState32f_16s;
typedef struct FIRState32fc_16sc IppsFIRState32fc_16sc;
typedef struct FIRState_64f IppsFIRState_64f;
typedef struct FIRState_64fc IppsFIRState_64fc;
typedef struct FIRState64f_32f IppsFIRState64f_32f;
typedef struct FIRState64fc_32fc IppsFIRState64fc_32fc;
typedef struct FIRState64f_32s IppsFIRState64f_32s;
typedef struct FIRState64fc_32sc IppsFIRState64fc_32sc;
typedef struct FIRState64f_16s IppsFIRState64f_16s;
typedef struct FIRState64fc_16sc IppsFIRState64fc_16sc;
typedef struct FIRState32s_16s IppsFIRState32s_16s;
typedef struct FIRState32sc_16sc IppsFIRState32sc_16sc;
typedef struct FIRState_32s IppsFIRState_32s;
typedef struct FIRState_16s IppsFIRState_16s;

typedef struct FIRLMSMRState32s_16s IppsFIRLMSMRState32s_16s;
typedef struct FIRLMSMRState32sc_16sc IppsFIRLMSMRState32sc_16sc;

typedef struct HilbertSpec_32f32fc IppsHilbertSpec_32f32fc;
typedef struct HilbertSpec_16s32fc IppsHilbertSpec_16s32fc;
typedef struct HilbertSpec_16s16sc IppsHilbertSpec_16s16sc;


/*****************************************************************************/
/*                   Below are ippIP legacy specific definitions             */
/*****************************************************************************/


typedef struct FFT2DSpec_R_32s IppiFFTSpec_R_32s;

typedef struct DFT2DSpec_R_32s IppiDFTSpec_R_32s;

typedef enum
{
    ippResampleCatmullRom
} IppiResampleType;

typedef struct ResampleRowSpec_32f IppiResampleRowSpec_32f;

typedef struct MomentState64s IppiMomentState_64s;

typedef Ipp64s IppiHuMoment_64s[7];


/*****************************************************************************/
/*                   Below are ippCH legacy specific definitions             */
/*****************************************************************************/

typedef struct RegExpMultiState IppRegExpMultiState;

typedef struct {
    Ipp32u regexpDoneFlag;
    Ipp32u regexpID;
    Ipp32s numMultiFind;
    IppStatus status;
    IppRegExpFind* pFind;
} IppRegExpMultiFind;


/*****************************************************************************/
/*                   Below are ippCV legacy specific definitions             */
/*****************************************************************************/


typedef struct _IppFGHistogramModel {  /* for C3 image */
    int                valueQuant;     /* 64 */
    int                changeQuant;    /* 32 */
    int                valueUse;       /* 30 */
    int                valueAll;       /* 50 */
    int                changeUse;      /* 50 */
    int                changeAll;      /* 80 */
    Ipp32f             updBGChange;    /* 0.0046 */
    Ipp32f             updBGRef;       /* 0.0010 */
    int                numFrame;
    float              detectionRate;
    float              brightnessDistortion;
    int                shadowBG;
} IppFGHistogramModel;

typedef struct _IppFGGaussianModel {
    int                numGauss;
    Ipp32f             priorBack;
    Ipp32f             updBGProb;
    int                winSize;
    int                numFrame;
    float              detectionRate;
    float              brightnessDistortion;
    int                shadowBG;
} IppFGGaussianModel;

typedef struct _IppiSRHNSpec_PSF3x3 IppiSRHNSpec_PSF3x3;
typedef struct _IppiSRHNSpec_PSF2x2 IppiSRHNSpec_PSF2x2;


/*****************************************************************************/
/*                   Below are ippDC legacy specific definitions             */
/*****************************************************************************/

typedef struct HuffState_8u IppHuffState_8u;
typedef struct GITState_8u IppGITState_8u;
typedef enum {
    ippGITNoStrategy,
    ippGITLeftReorder,
    ippGITRightReorder,
    ippGITFixedOrder
} IppGITStrategyHint;

#ifdef __cplusplus
}
#endif

#endif /* __IPPDEFS_90_LEGACY_H__ */
