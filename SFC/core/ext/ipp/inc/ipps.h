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
//              Signal Processing (ippSP)
//
//
*/

#if !defined( IPPS_H__ ) || defined( _OWN_BLDPCS )
#define IPPS_H__

#ifndef IPPDEFS_H__
#include "ippdefs.h"
#endif

#include "ipps_l.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined( IPP_NO_DEFAULT_LIB )
#if defined( _IPP_SEQUENTIAL_DYNAMIC )
#pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ipps" )
#pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippcore" )
#elif defined( _IPP_SEQUENTIAL_STATIC )
#pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippsmt" )
#pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippvmmt" )
#pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippcoremt" )
#elif defined( _IPP_PARALLEL_DYNAMIC )
#pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ipps" )
#pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippcore" )
#elif defined( _IPP_PARALLEL_STATIC )
#pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippsmt" )
#pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippvmmt" )
#pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippcoremt" )
#endif
#endif

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsGetLibVersion
//  Purpose:    Get library version
//  Parameters:
//  Returns:    pointer to structure describing version of ipps library
//      typedef struct {
//         int    major;                      e.g. 1
//         int    minor;                      e.g. 2
//         int    majorBuild;                 e.g. 3
//         int    build;                      e.g. 10, always >= majorBuild
//         char  targetCpu[4];                corresponding to Intel(R) processor
//         const char* Name;                  e.g. "ippsw7"
//         const char* Version;               e.g. "v1.2 Beta"
//         const char* BuildDate;             e.g. "Jul 20 99"
//      } IppLibraryVersion;
//
//  Notes:      don't free pointer!
*/
IPPAPI(const IppLibraryVersion*, ippsGetLibVersion, (void))

/* /////////////////////////////////////////////////////////////////////////////
//                   Functions to allocate and free memory
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsMalloc
//  Purpose:    Aligned memory allocation (alignment depends on
//              CPU-architecture, 64-byte (cache line size) in most cases)
//  Parameter:
//    len       Number of elements (according to their type)
//  Returns:    Pointer to allocated memory, NULL in case of failure or len < 1
//
//  Notes:      Memory allocated by ippsMalloc must be freed by ippsFree
//              function only.
*/
IPPAPI(Ipp8u*,   ippsMalloc_8u,   (int len))
IPPAPI(Ipp16u*,  ippsMalloc_16u,  (int len))
IPPAPI(Ipp32u*,  ippsMalloc_32u,  (int len))
IPPAPI(Ipp8s*,   ippsMalloc_8s,   (int len))
IPPAPI(Ipp16s*,  ippsMalloc_16s,  (int len))
IPPAPI(Ipp32s*,  ippsMalloc_32s,  (int len))
IPPAPI(Ipp64s*,  ippsMalloc_64s,  (int len))
IPPAPI(Ipp32f*,  ippsMalloc_32f,  (int len))
IPPAPI(Ipp64f*,  ippsMalloc_64f,  (int len))
IPPAPI(Ipp8sc*,  ippsMalloc_8sc,  (int len))
IPPAPI(Ipp16sc*, ippsMalloc_16sc, (int len))
IPPAPI(Ipp32sc*, ippsMalloc_32sc, (int len))
IPPAPI(Ipp64sc*, ippsMalloc_64sc, (int len))
IPPAPI(Ipp32fc*, ippsMalloc_32fc, (int len))
IPPAPI(Ipp64fc*, ippsMalloc_64fc, (int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsFree
//  Purpose:    Free memory allocated by ippsMalloc function
//  Parameter:
//    ptr       Pointer to memory allocated by ippsMalloc function
//
//  Notes:      Use this function to free memory allocated by ippsMalloc_* only
*/
IPPAPI(void, ippsFree, (void* ptr))

/* /////////////////////////////////////////////////////////////////////////////
//                   Vector Initialization functions
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsCopy
//  Purpose:    Copy data from source to destination vector
//  Parameters:
//    pSrc        Pointer to input vector
//    pDst        Pointer to output vector
//    len         Length of vectors in elements
//  Returns:
//    ippStsNullPtrErr        One of the pointers is NULL
//    ippStsSizeErr           Vector length is less than 1
//    ippStsNoErr             Otherwise
*/
IPPAPI(IppStatus, ippsCopy_8u,   (const Ipp8u*   pSrc, Ipp8u*   pDst, int len))
IPPAPI(IppStatus, ippsCopy_16s,  (const Ipp16s*  pSrc, Ipp16s*  pDst, int len))
IPPAPI(IppStatus, ippsCopy_16sc, (const Ipp16sc* pSrc, Ipp16sc* pDst, int len))
IPPAPI(IppStatus, ippsCopy_32f,  (const Ipp32f*  pSrc, Ipp32f*  pDst, int len))
IPPAPI(IppStatus, ippsCopy_32fc, (const Ipp32fc* pSrc, Ipp32fc* pDst, int len))
IPPAPI(IppStatus, ippsCopy_64f,  (const Ipp64f*  pSrc, Ipp64f*  pDst, int len))
IPPAPI(IppStatus, ippsCopy_64fc, (const Ipp64fc* pSrc, Ipp64fc* pDst, int len))
IPPAPI(IppStatus, ippsCopy_32s,  (const Ipp32s*  pSrc, Ipp32s*  pDst, int len))
IPPAPI(IppStatus, ippsCopy_32sc, (const Ipp32sc* pSrc, Ipp32sc* pDst, int len))
IPPAPI(IppStatus, ippsCopy_64s,  (const Ipp64s*  pSrc, Ipp64s*  pDst, int len))
IPPAPI(IppStatus, ippsCopy_64sc, (const Ipp64sc* pSrc, Ipp64sc* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsCopyLE_1u
//              ippsCopyBE_1u
//  Purpose:    Copy bits data from source to destination vector
//  Parameters:
//    pSrc          Pointer to input vector
//    srcBitOffset  Bit offset in the first byte of source vector
//    pDst          Pointer to output vector
//    dstBitOffset  Bit offset in the first byte of destination vector
//    len           Vectors' length in bits
//  Return:
//    ippStsNullPtrErr        One of the pointers is NULL
//    ippStsSizeErr           Vectors' length is less than 1
//    ippStsNoErr             otherwise
*/
IPPAPI(IppStatus, ippsCopyLE_1u, (const Ipp8u* pSrc, int srcBitOffset, Ipp8u* pDst, int dstBitOffset, int len))
IPPAPI(IppStatus, ippsCopyBE_1u, (const Ipp8u* pSrc, int srcBitOffset, Ipp8u* pDst, int dstBitOffset, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsMove
//  Purpose:    ippsMove function copies "len" elements from src to dst.
//              If some regions of source and destination areas overlap,
//              ippsMove ensures that original source bytes in overlapping
//              region are copied before being overwritten.
//
//  Parameters:
//    pSrc        Pointer to input vector
//    pDst        Pointer to output vector
//    len         Vectors' length in elements
//  Return:
//    ippStsNullPtrErr        One of pointers is NULL
//    ippStsSizeErr           Vectors' length is less than 1
//    ippStsNoErr             Otherwise
*/
IPPAPI(IppStatus, ippsMove_8u,   (const Ipp8u*   pSrc, Ipp8u*   pDst, int len))
IPPAPI(IppStatus, ippsMove_16s,  (const Ipp16s*  pSrc, Ipp16s*  pDst, int len))
IPPAPI(IppStatus, ippsMove_16sc, (const Ipp16sc* pSrc, Ipp16sc* pDst, int len))
IPPAPI(IppStatus, ippsMove_32f,  (const Ipp32f*  pSrc, Ipp32f*  pDst, int len))
IPPAPI(IppStatus, ippsMove_32fc, (const Ipp32fc* pSrc, Ipp32fc* pDst, int len))
IPPAPI(IppStatus, ippsMove_64f,  (const Ipp64f*  pSrc, Ipp64f*  pDst, int len))
IPPAPI(IppStatus, ippsMove_64fc, (const Ipp64fc* pSrc, Ipp64fc* pDst, int len))
IPPAPI(IppStatus, ippsMove_32s,  (const Ipp32s*  pSrc, Ipp32s*  pDst, int len))
IPPAPI(IppStatus, ippsMove_32sc, (const Ipp32sc* pSrc, Ipp32sc* pDst, int len))
IPPAPI(IppStatus, ippsMove_64s,  (const Ipp64s*  pSrc, Ipp64s*  pDst, int len))
IPPAPI(IppStatus, ippsMove_64sc, (const Ipp64sc* pSrc, Ipp64sc* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsSet
//  Purpose:    Set elements of destination vector to defined value
//  Parameters:
//    val        Value to set for all vector's elements
//    pDst       Pointer to destination vector
//    len        Vectors' length
//  Return:
//    ippStsNullPtrErr        Pointer to vector is NULL
//    ippStsSizeErr           Vector length is less than 1
//    ippStsNoErr             Otherwise
*/
IPPAPI(IppStatus, ippsSet_8u,   (Ipp8u   val, Ipp8u*   pDst, int len))
IPPAPI(IppStatus, ippsSet_16s,  (Ipp16s  val, Ipp16s*  pDst, int len))
IPPAPI(IppStatus, ippsSet_16sc, (Ipp16sc val, Ipp16sc* pDst, int len))
IPPAPI(IppStatus, ippsSet_32s,  (Ipp32s  val, Ipp32s*  pDst, int len))
IPPAPI(IppStatus, ippsSet_32sc, (Ipp32sc val, Ipp32sc* pDst, int len))
IPPAPI(IppStatus, ippsSet_32f,  (Ipp32f  val, Ipp32f*  pDst, int len))
IPPAPI(IppStatus, ippsSet_32fc, (Ipp32fc val, Ipp32fc* pDst, int len))
IPPAPI(IppStatus, ippsSet_64s,  (Ipp64s  val, Ipp64s*  pDst, int len))
IPPAPI(IppStatus, ippsSet_64sc, (Ipp64sc val, Ipp64sc* pDst, int len))
IPPAPI(IppStatus, ippsSet_64f,  (Ipp64f  val, Ipp64f*  pDst, int len))
IPPAPI(IppStatus, ippsSet_64fc, (Ipp64fc val, Ipp64fc* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsZero
//  Purpose:    Reset all vector elements
//  Parameters:
//    pDst       Pointer to destination vector
//    len        Vector length
//  Return:
//    ippStsNullPtrErr        Pointer to vector is NULL
//    ippStsSizeErr           Vector length is less than 1
//    ippStsNoErr             Otherwise
*/
IPPAPI(IppStatus, ippsZero_8u,   (Ipp8u*   pDst, int len))
IPPAPI(IppStatus, ippsZero_16s,  (Ipp16s*  pDst, int len))
IPPAPI(IppStatus, ippsZero_16sc, (Ipp16sc* pDst, int len))
IPPAPI(IppStatus, ippsZero_32f,  (Ipp32f*  pDst, int len))
IPPAPI(IppStatus, ippsZero_32fc, (Ipp32fc* pDst, int len))
IPPAPI(IppStatus, ippsZero_64f,  (Ipp64f*  pDst, int len))
IPPAPI(IppStatus, ippsZero_64fc, (Ipp64fc* pDst, int len))
IPPAPI(IppStatus, ippsZero_32s,  (Ipp32s*  pDst, int len))
IPPAPI(IppStatus, ippsZero_32sc, (Ipp32sc* pDst, int len))
IPPAPI(IppStatus, ippsZero_64s,  (Ipp64s*  pDst, int len))
IPPAPI(IppStatus, ippsZero_64sc, (Ipp64sc* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippsTone
//  Purpose:        Generates tone with given frequency, phase and magnitude
//  Parameters:
//    pDst        - Pointer to destination vector
//    len         - Vector length
//    magn        - Magnitude of tone (maximum value attained by wave)
//    rFreq       - Frequency of tone relative to sampling frequency
//                  It must be in range [0.0, 0.5) for real, and [0.0, 1.0) for complex tone
//    pPhase      - Phase of tone relative to cosinewave. It must be in range [0.0, 2*PI)
//    hint        - Fast or accurate algorithm
//  Returns:
//    ippStsNullPtrErr   - One of pointers is NULL
//    ippStsSizeErr      - Vector length is less than 1
//    ippStsToneMagnErr  - magn value is less than or equal to zero.
//    ippStsToneFreqErr  - rFreq is less than 0 or greater than or equal to 0.5 for real tone and 1.0 for complex tone.
//    ippStsTonePhaseErr - phase is less than 0 or greater or equal 2*PI.
//    ippStsNoErr        - No error
//  Notes:
//    for real:  pDst[i] = magn * cos(IPP_2PI * rfreq * i + phase);
//    for cplx:  pDst[i].re = magn * cos(IPP_2PI * rfreq * i + phase);
//               pDst[i].im = magn * sin(IPP_2PI * rfreq * i + phase);
*/
IPPAPI(IppStatus, ippsTone_16s,  (Ipp16s*  pDst, int len, Ipp16s magn, Ipp32f rFreq, Ipp32f* pPhase, IppHintAlgorithm hint))
IPPAPI(IppStatus, ippsTone_16sc, (Ipp16sc* pDst, int len, Ipp16s magn, Ipp32f rFreq, Ipp32f* pPhase, IppHintAlgorithm hint))
IPPAPI(IppStatus, ippsTone_32f,  (Ipp32f*  pDst, int len, Ipp32f magn, Ipp32f rFreq, Ipp32f* pPhase, IppHintAlgorithm hint))
IPPAPI(IppStatus, ippsTone_32fc, (Ipp32fc* pDst, int len, Ipp32f magn, Ipp32f rFreq, Ipp32f* pPhase, IppHintAlgorithm hint))
IPPAPI(IppStatus, ippsTone_64f,  (Ipp64f*  pDst, int len, Ipp64f magn, Ipp64f rFreq, Ipp64f* pPhase, IppHintAlgorithm hint))
IPPAPI(IppStatus, ippsTone_64fc, (Ipp64fc* pDst, int len, Ipp64f magn, Ipp64f rFreq, Ipp64f* pPhase, IppHintAlgorithm hint))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippsTriangle
//  Purpose:        Generate triangle with given frequency, phase and magnitude
//  Parameters:
//    pDst        - Pointer to destination vector
//    len         - Vector length
//    magn        - Magnitude of Triangle
//    rFreq       - Frequency of Triangle relative to sampling frequency (must be in range [0.0, 0.5))
//    pPhase      - Pointer to phase of Triangle relative to acosinewave (must be in range [0.0, 2*PI))
//                  Returned value can be used to compute the next continuous data block
//    asym        - Asymmetry of Triangle (must be in range [-PI,PI))
//  Returns:
//    ippStsNullPtrErr    - Any of specified pointers is NULL
//    ippStsSizeErr       - Vector length is less than 1
//    ippStsTrnglMagnErr  - magn value is less or equal to zero
//    ippStsTrnglFreqErr  - rFreq value is out of range [0, 0.5)
//    ippStsTrnglPhaseErr - phase value is out of range [0, 2*PI)
//    ippStsTrnglAsymErr  - asym value is out of range [-PI, PI)
//    ippStsNoErr         - No error
*/
IPPAPI(IppStatus, ippsTriangle_64f,  (Ipp64f*  pDst, int len, Ipp64f magn, Ipp64f rFreq, Ipp64f asym, Ipp64f* pPhase))
IPPAPI(IppStatus, ippsTriangle_64fc, (Ipp64fc* pDst, int len, Ipp64f magn, Ipp64f rFreq, Ipp64f asym, Ipp64f* pPhase))
IPPAPI(IppStatus, ippsTriangle_32f,  (Ipp32f*  pDst, int len, Ipp32f magn, Ipp32f rFreq, Ipp32f asym, Ipp32f* pPhase))
IPPAPI(IppStatus, ippsTriangle_32fc, (Ipp32fc* pDst, int len, Ipp32f magn, Ipp32f rFreq, Ipp32f asym, Ipp32f* pPhase))
IPPAPI(IppStatus, ippsTriangle_16s,  (Ipp16s*  pDst, int len, Ipp16s magn, Ipp32f rFreq, Ipp32f asym, Ipp32f* pPhase))
IPPAPI(IppStatus, ippsTriangle_16sc, (Ipp16sc* pDst, int len, Ipp16s magn, Ipp32f rFreq, Ipp32f asym, Ipp32f* pPhase))

/* /////////////////////////////////////////////////////////////////////////
// Name:            ippsRandUniform
// Purpose:         Initialize vector with uniformly distributed values
// Parameters:
//    pDst          Pointer to vector
//    len           Vector length
//    pRandUniState Pointer to RandUniState structure
// Returns:
//    ippStsNullPtrErr       One of pointers is NULL
//    ippStsContextMatchErr  State structure has invalid content
//    ippStsNoErr            No errors
*/
IPPAPI(IppStatus, ippsRandUniform_8u,  (Ipp8u* pDst,  int len, IppsRandUniState_8u*  pRandUniState))
IPPAPI(IppStatus, ippsRandUniform_16s, (Ipp16s* pDst, int len, IppsRandUniState_16s* pRandUniState))
IPPAPI(IppStatus, ippsRandUniform_32f, (Ipp32f* pDst, int len, IppsRandUniState_32f* pRandUniState))
IPPAPI(IppStatus, ippsRandUniform_64f, (Ipp64f* pDst, int len, IppsRandUniState_64f* pRandUniState))

/* /////////////////////////////////////////////////////////////////////////
// Name:            ippsRandGauss
// Purpose:         Makes pseudo-random samples with a normal distribution
//                  and places them in the vector.
// Parameters:
//    pDst          The pointer to vector
//    len           Vector's length
//    pRandUniState A pointer to the structure containing parameters
//                  for the generator of noise
// Returns:
//    ippStsNullPtrErr       Pointer to the state structure is NULL
//    ippStsContextMatchErr  State structure has invalid content
//    ippStsSizeErr          Vector length is less than 1
//    ippStsNoErr            No errors
*/
IPPAPI(IppStatus, ippsRandGauss_8u,  (Ipp8u*  pDst, int len, IppsRandGaussState_8u*  pRandGaussState))
IPPAPI(IppStatus, ippsRandGauss_16s, (Ipp16s* pDst, int len, IppsRandGaussState_16s* pRandGaussState))
IPPAPI(IppStatus, ippsRandGauss_32f, (Ipp32f* pDst, int len, IppsRandGaussState_32f* pRandGaussState))
IPPAPI(IppStatus, ippsRandGauss_64f, (Ipp64f* pDst, int len, IppsRandGaussState_64f* pRandGaussState))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippsRandGaussGetSize
//
//  Purpose:    Calculate size of memory buffer required for RandGaussState
//              structure
//  Arguments:
//    pRandGaussStateSize      Pointer where to store computed size of
//                             memory buffer required for RandGaussState
//  Return:
//    ippStsNullPtrErr         Pointer is NULL
//    ippStsNoErr              No errors
*/
IPPAPI(IppStatus, ippsRandGaussGetSize_8u,  (int* pRandGaussStateSize))
IPPAPI(IppStatus, ippsRandGaussGetSize_16s, (int* pRandGaussStateSize))
IPPAPI(IppStatus, ippsRandGaussGetSize_32f, (int* pRandGaussStateSize))
IPPAPI(IppStatus, ippsRandGaussGetSize_64f, (int* pRandGaussStateSize))

/* //////////////////////////////////////////////////////////////////////////////////
// Name:                ippsRandGaussInit
// Purpose:             Initializes RandGaussState structure
// Parameters:
//    pRandGaussState   Pointer to RandGaussState structure
//    mean              Mean of normal distribution.
//    stdDev            Standard deviation of normal distribution.
//    seed              Initial seed value for pseudo-random number generator
// Returns:
//    ippStsNullPtrErr  Pointer to state structure is NULL
//    ippStsNoErr       No errors
//
*/
IPPAPI(IppStatus, ippsRandGaussInit_8u,  (IppsRandGaussState_8u*  pRandGaussState, Ipp8u  mean, Ipp8u  stdDev, unsigned int seed))
IPPAPI(IppStatus, ippsRandGaussInit_16s, (IppsRandGaussState_16s* pRandGaussState, Ipp16s mean, Ipp16s stdDev, unsigned int seed))
IPPAPI(IppStatus, ippsRandGaussInit_32f, (IppsRandGaussState_32f* pRandGaussState, Ipp32f mean, Ipp32f stdDev, unsigned int seed))
IPPAPI(IppStatus, ippsRandGaussInit_64f, (IppsRandGaussState_64f* pRandGaussState, Ipp64f mean, Ipp64f stdDev, unsigned int seed))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippsRandUniformGetSize
//  Purpose:    Calculates size of memory buffer required for
//              RandUniformState structure
//  Arguments:
//    pRandUniformStateSize Pointer where to store computed size of
//                          memory buffer required for RandUniformState
//  Return:
//    ippStsNullPtrErr  Pointer is NULL
//    ippStsNoErr       No errors
*/
IPPAPI(IppStatus, ippsRandUniformGetSize_8u,  (int *pRandUniformStateSize))
IPPAPI(IppStatus, ippsRandUniformGetSize_16s, (int *pRandUniformStateSize))
IPPAPI(IppStatus, ippsRandUniformGetSize_32f, (int *pRandUniformStateSize))
IPPAPI(IppStatus, ippsRandUniformGetSize_64f, (int *pRandUniformStateSize))

/* //////////////////////////////////////////////////////////////////////////////////
// Name:                ippsRandUniformInit
// Purpose:             Initializes RandUniformState structure
// Parameters:
//    pRandUniState     Pointer to RandUniformState structure
//    low               Lower bound of uniform distribution range
//    high              Upper bounds of uniform distribution range
//    seed              Initial seed value for pseudo-random number generator
// Returns:
//    ippStsNullPtrErr  Pointer is NULL
//    ippStsNoErr       No errors
//
*/
IPPAPI(IppStatus, ippsRandUniformInit_8u,  (IppsRandUniState_8u*  pRandUniState, Ipp8u  low, Ipp8u high,  unsigned int seed))
IPPAPI(IppStatus, ippsRandUniformInit_16s, (IppsRandUniState_16s* pRandUniState, Ipp16s low, Ipp16s high, unsigned int seed))
IPPAPI(IppStatus, ippsRandUniformInit_32f, (IppsRandUniState_32f* pRandUniState, Ipp32f low, Ipp32f high, unsigned int seed))
IPPAPI(IppStatus, ippsRandUniformInit_64f, (IppsRandUniState_64f* pRandUniState, Ipp64f low, Ipp64f high, unsigned int seed))

/* /////////////////////////////////////////////////////////////////////////
//  Name:               ippsVectorJaehne
//  Purpose:            Create Jaehne vector
//
//  Parameters:
//    pDst              Pointer to destination vector
//    len               Length of vector
//    magn              Magnitude of signal
//
//  Return:
//    ippStsNullPtrErr  Pointer is NULL
//    ippStsBadSizeErr  Vector length is less than 1
//    ippStsJaehneErr   Magnitude value is negative
//    ippStsNoErr       No error
//
//  Notes:              pDst[n] = magn*sin(0.5*pi*n^2/len), n=0,1,2,..len-1.
//
*/
IPPAPI(IppStatus, ippsVectorJaehne_8u,  (Ipp8u*  pDst, int len, Ipp8u  magn))
IPPAPI(IppStatus, ippsVectorJaehne_16u, (Ipp16u* pDst, int len, Ipp16u magn))
IPPAPI(IppStatus, ippsVectorJaehne_16s, (Ipp16s* pDst, int len, Ipp16s magn))
IPPAPI(IppStatus, ippsVectorJaehne_32s, (Ipp32s* pDst, int len, Ipp32s magn))
IPPAPI(IppStatus, ippsVectorJaehne_32f, (Ipp32f* pDst, int len, Ipp32f magn))
IPPAPI(IppStatus, ippsVectorJaehne_64f, (Ipp64f* pDst, int len, Ipp64f magn))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:               ippsVectorSlope
//  Purpose:            Creates ramp vector
//  Parameters:
//    pDst              A pointer to the destination vector
//    len               Vector's length
//    offset            Offset value
//    slope             Slope coefficient
//
//  Return:
//    ippStsNullPtrErr  pDst pointer is NULL
//    ippStsBadSizeErr  Vector's length is less or equal zero
//    ippStsNoErr       No error
//
//  Notes:              Dst[n] = offset + slope * n
//
*/
IPPAPI(IppStatus, ippsVectorSlope_8u,  (Ipp8u*  pDst, int len, Ipp32f offset, Ipp32f slope))
IPPAPI(IppStatus, ippsVectorSlope_16u, (Ipp16u* pDst, int len, Ipp32f offset, Ipp32f slope))
IPPAPI(IppStatus, ippsVectorSlope_16s, (Ipp16s* pDst, int len, Ipp32f offset, Ipp32f slope))
IPPAPI(IppStatus, ippsVectorSlope_32u, (Ipp32u* pDst, int len, Ipp64f offset, Ipp64f slope))
IPPAPI(IppStatus, ippsVectorSlope_32s, (Ipp32s* pDst, int len, Ipp64f offset, Ipp64f slope))
IPPAPI(IppStatus, ippsVectorSlope_32f, (Ipp32f* pDst, int len, Ipp32f offset, Ipp32f slope))
IPPAPI(IppStatus, ippsVectorSlope_64f, (Ipp64f* pDst, int len, Ipp64f offset, Ipp64f slope))

/* /////////////////////////////////////////////////////////////////////////////
//                      Vector logical functions
///////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////////
//  Names:              ippsAnd, ippsOr, ippsXor, ippsNot, ippsLShiftC, ippsRShiftC
//  Purpose:            logical operations and vector shifts
//  Parameters:
//   val                1) value to be ANDed/ORed/XORed with each element of the vector (And, Or, Xor);
//                      2) position`s number which vector elements to be SHIFTed on (ShiftC)
//   pSrc               pointer to input vector
//   pSrcDst            pointer to input/output vector
//   pSrc1              pointer to first input vector
//   pSrc2              pointer to second input vector
//   pDst               pointer to output vector
//   len                vector's length
//  Return:
//   ippStsNullPtrErr      pointer(s) to the data is NULL
//   ippStsSizeErr         vector`s length is less or equal zero
//   ippStsShiftErr        shift`s value is less zero
//   ippStsNoErr           otherwise
*/

IPPAPI(IppStatus, ippsAndC_8u_I,  (                    Ipp8u  val, Ipp8u*  pSrcDst, int len))
IPPAPI(IppStatus, ippsAndC_8u,    (const Ipp8u*  pSrc, Ipp8u  val, Ipp8u*  pDst,    int len))
IPPAPI(IppStatus, ippsAndC_16u_I, (                    Ipp16u val, Ipp16u* pSrcDst, int len))
IPPAPI(IppStatus, ippsAndC_16u,   (const Ipp16u* pSrc, Ipp16u val, Ipp16u* pDst,    int len))
IPPAPI(IppStatus, ippsAndC_32u_I, (                    Ipp32u val, Ipp32u* pSrcDst, int len))
IPPAPI(IppStatus, ippsAndC_32u,   (const Ipp32u* pSrc, Ipp32u val, Ipp32u* pDst,    int len))

IPPAPI(IppStatus, ippsAnd_8u_I,  (const Ipp8u*  pSrc,                       Ipp8u* pSrcDst,  int len))
IPPAPI(IppStatus, ippsAnd_8u,    (const Ipp8u*  pSrc1, const Ipp8u*  pSrc2, Ipp8u* pDst,     int len))
IPPAPI(IppStatus, ippsAnd_16u_I, (const Ipp16u* pSrc,                       Ipp16u* pSrcDst, int len))
IPPAPI(IppStatus, ippsAnd_16u,   (const Ipp16u* pSrc1, const Ipp16u* pSrc2, Ipp16u* pDst,    int len))
IPPAPI(IppStatus, ippsAnd_32u_I, (const Ipp32u* pSrc,                       Ipp32u* pSrcDst, int len))
IPPAPI(IppStatus, ippsAnd_32u,   (const Ipp32u* pSrc1, const Ipp32u* pSrc2, Ipp32u* pDst,    int len))

IPPAPI(IppStatus, ippsOrC_8u_I,  (                    Ipp8u val,  Ipp8u* pSrcDst,  int len))
IPPAPI(IppStatus, ippsOrC_8u,    (const Ipp8u*  pSrc, Ipp8u val,  Ipp8u* pDst,     int len))
IPPAPI(IppStatus, ippsOrC_16u_I, (                    Ipp16u val, Ipp16u* pSrcDst, int len))
IPPAPI(IppStatus, ippsOrC_16u,   (const Ipp16u* pSrc, Ipp16u val, Ipp16u* pDst,    int len))
IPPAPI(IppStatus, ippsOrC_32u_I, (                    Ipp32u val, Ipp32u* pSrcDst, int len))
IPPAPI(IppStatus, ippsOrC_32u,   (const Ipp32u* pSrc, Ipp32u val, Ipp32u* pDst,    int len))

IPPAPI(IppStatus, ippsOr_8u_I,  (const Ipp8u*  pSrc,                       Ipp8u* pSrcDst,  int len))
IPPAPI(IppStatus, ippsOr_8u,    (const Ipp8u*  pSrc1, const Ipp8u*  pSrc2, Ipp8u* pDst,     int len))
IPPAPI(IppStatus, ippsOr_16u_I, (const Ipp16u* pSrc,                       Ipp16u* pSrcDst, int len))
IPPAPI(IppStatus, ippsOr_16u,   (const Ipp16u* pSrc1, const Ipp16u* pSrc2, Ipp16u* pDst,    int len))
IPPAPI(IppStatus, ippsOr_32u_I, (const Ipp32u* pSrc,                       Ipp32u* pSrcDst, int len))
IPPAPI(IppStatus, ippsOr_32u,   (const Ipp32u* pSrc1, const Ipp32u* pSrc2, Ipp32u* pDst,    int len))

IPPAPI(IppStatus, ippsXorC_8u_I,  (                    Ipp8u val,  Ipp8u*  pSrcDst, int len))
IPPAPI(IppStatus, ippsXorC_8u,    (const Ipp8u* pSrc,  Ipp8u val,  Ipp8u*  pDst,    int len))
IPPAPI(IppStatus, ippsXorC_16u_I, (                    Ipp16u val, Ipp16u* pSrcDst, int len))
IPPAPI(IppStatus, ippsXorC_16u,   (const Ipp16u* pSrc, Ipp16u val, Ipp16u* pDst,    int len))
IPPAPI(IppStatus, ippsXorC_32u_I, (                    Ipp32u val, Ipp32u* pSrcDst, int len))
IPPAPI(IppStatus, ippsXorC_32u,   (const Ipp32u* pSrc, Ipp32u val, Ipp32u* pDst,    int len))

IPPAPI(IppStatus, ippsXor_8u_I,  (const Ipp8u*  pSrc,                       Ipp8u* pSrcDst,  int len))
IPPAPI(IppStatus, ippsXor_8u,    (const Ipp8u*  pSrc1, const Ipp8u*  pSrc2, Ipp8u* pDst,     int len))
IPPAPI(IppStatus, ippsXor_16u_I, (const Ipp16u* pSrc,                       Ipp16u* pSrcDst, int len))
IPPAPI(IppStatus, ippsXor_16u,   (const Ipp16u* pSrc1, const Ipp16u* pSrc2, Ipp16u* pDst,    int len))
IPPAPI(IppStatus, ippsXor_32u_I, (const Ipp32u* pSrc,                       Ipp32u* pSrcDst, int len))
IPPAPI(IppStatus, ippsXor_32u,   (const Ipp32u* pSrc1, const Ipp32u* pSrc2, Ipp32u* pDst,    int len))

IPPAPI(IppStatus, ippsNot_8u_I,  (                    Ipp8u*  pSrcDst, int len))
IPPAPI(IppStatus, ippsNot_8u,    (const Ipp8u*  pSrc, Ipp8u*  pDst,    int len))
IPPAPI(IppStatus, ippsNot_16u_I, (                    Ipp16u* pSrcDst, int len))
IPPAPI(IppStatus, ippsNot_16u,   (const Ipp16u* pSrc, Ipp16u* pDst,    int len))
IPPAPI(IppStatus, ippsNot_32u_I, (                    Ipp32u* pSrcDst, int len))
IPPAPI(IppStatus, ippsNot_32u,   (const Ipp32u* pSrc, Ipp32u* pDst,    int len))

IPPAPI(IppStatus, ippsLShiftC_8u_I,  (                    int val, Ipp8u*  pSrcDst, int len))
IPPAPI(IppStatus, ippsLShiftC_8u,    (const Ipp8u*  pSrc, int val, Ipp8u*  pDst,    int len))
IPPAPI(IppStatus, ippsLShiftC_16u_I, (                    int val, Ipp16u* pSrcDst, int len))
IPPAPI(IppStatus, ippsLShiftC_16u,   (const Ipp16u* pSrc, int val, Ipp16u* pDst,    int len))
IPPAPI(IppStatus, ippsLShiftC_16s_I, (                    int val, Ipp16s* pSrcDst, int len))
IPPAPI(IppStatus, ippsLShiftC_16s,   (const Ipp16s* pSrc, int val, Ipp16s* pDst,    int len))
IPPAPI(IppStatus, ippsLShiftC_32s_I, (                    int val, Ipp32s* pSrcDst, int len))
IPPAPI(IppStatus, ippsLShiftC_32s,   (const Ipp32s* pSrc, int val, Ipp32s* pDst,    int len))

IPPAPI(IppStatus, ippsRShiftC_8u_I,  (                    int val, Ipp8u*  pSrcDst, int len))
IPPAPI(IppStatus, ippsRShiftC_8u,    (const Ipp8u*  pSrc, int val, Ipp8u*  pDst,    int len))
IPPAPI(IppStatus, ippsRShiftC_16u_I, (                    int val, Ipp16u* pSrcDst, int len))
IPPAPI(IppStatus, ippsRShiftC_16u,   (const Ipp16u* pSrc, int val, Ipp16u* pDst,    int len))
IPPAPI(IppStatus, ippsRShiftC_16s_I, (                    int val, Ipp16s* pSrcDst, int len))
IPPAPI(IppStatus, ippsRShiftC_16s,   (const Ipp16s* pSrc, int val, Ipp16s* pDst,    int len))
IPPAPI(IppStatus, ippsRShiftC_32s_I, (                    int val, Ipp32s* pSrcDst, int len))
IPPAPI(IppStatus, ippsRShiftC_32s,   (const Ipp32s* pSrc, int val, Ipp32s* pDst,    int len))

/* /////////////////////////////////////////////////////////////////////////////
//                  Arithmetic functions
///////////////////////////////////////////////////////////////////////////// */

/* ////////////////////////////////////////////////////////////////////////////
//  Names:       ippsAddC
//  Purpose:    Adds constant value to each element of vector
//  Arguments:
//    pSrc                 Pointer to source vector
//    pSrcDst              Pointer to source and destination vector for in-place operation
//    pDst                 Pointer to destination vector
//    val                  Scalar value used to increment each element of source vector
//    len                  Number of elements in vector
//    scaleFactor          Scale factor
//    rndMode              Rounding mode, following values are possible:
//                         ippRndZero - floating-point values are truncated to zero
//                         ippRndNear - floating-point values are rounded to the nearest even integer
//                         when fractional part equals 0.5; otherwise they are rounded to the nearest integer
//                         ippRndFinancial - floating-point values are rounded down to the nearest
//                         integer when fractional part is less than 0.5, or rounded up to the
//                         nearest integer if the fractional part is equal or greater than 0.5
//  Return:
//    ippStsNullPtrErr     At least one of the pointers is NULL
//    ippStsSizeErr        Vectors' length is less than 1
//    ippStsNoErr          No error
//  Note:
//    AddC(X,v,Y)    :  Y[n] = X[n] + v
*/
IPPAPI(IppStatus, ippsAddC_8u_ISfs,   (                     Ipp8u   val, Ipp8u*   pSrcDst, int len,    int scaleFactor))
IPPAPI(IppStatus, ippsAddC_8u_Sfs,    (const Ipp8u*   pSrc, Ipp8u   val, Ipp8u*   pDst,    int len,    int scaleFactor))
IPPAPI(IppStatus, ippsAddC_16s_I,     (                     Ipp16s  val, Ipp16s*  pSrcDst, int len))
IPPAPI(IppStatus, ippsAddC_16s_ISfs,  (                     Ipp16s  val, Ipp16s*  pSrcDst, int len,    int scaleFactor))
IPPAPI(IppStatus, ippsAddC_16s_Sfs,   (const Ipp16s*  pSrc, Ipp16s  val, Ipp16s*  pDst,    int len,    int scaleFactor))
IPPAPI(IppStatus, ippsAddC_16sc_ISfs, (                     Ipp16sc val, Ipp16sc* pSrcDst, int len,    int scaleFactor))
IPPAPI(IppStatus, ippsAddC_16sc_Sfs,  (const Ipp16sc* pSrc, Ipp16sc val, Ipp16sc* pDst,    int len,    int scaleFactor))
IPPAPI(IppStatus, ippsAddC_16u_ISfs,  (                     Ipp16u  val, Ipp16u*  pSrcDst, int len,    int scaleFactor))
IPPAPI(IppStatus, ippsAddC_16u_Sfs,   (const Ipp16u*  pSrc, Ipp16u  val, Ipp16u*  pDst,    int len,    int scaleFactor))
IPPAPI(IppStatus, ippsAddC_32s_ISfs,  (                     Ipp32s  val, Ipp32s*  pSrcDst, int len,    int scaleFactor))
IPPAPI(IppStatus, ippsAddC_32s_Sfs,   (const Ipp32s*  pSrc, Ipp32s  val, Ipp32s*  pDst,    int len,    int scaleFactor))
IPPAPI(IppStatus, ippsAddC_32sc_ISfs, (                     Ipp32sc val, Ipp32sc* pSrcDst, int len,    int scaleFactor))
IPPAPI(IppStatus, ippsAddC_32sc_Sfs,  (const Ipp32sc* pSrc, Ipp32sc val, Ipp32sc* pDst,    int len,    int scaleFactor))
IPPAPI(IppStatus, ippsAddC_64u_Sfs,   (const Ipp64u*  pSrc, Ipp64u  val, Ipp64u*  pDst,    Ipp32u len, int scaleFactor, IppRoundMode rndMode))
IPPAPI(IppStatus, ippsAddC_64s_Sfs,   (const Ipp64s*  pSrc, Ipp64s  val, Ipp64s*  pDst,    Ipp32u len, int scaleFactor, IppRoundMode rndMode))
IPPAPI(IppStatus, ippsAddC_32f_I,     (                     Ipp32f  val, Ipp32f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsAddC_32f,       (const Ipp32f*  pSrc, Ipp32f  val, Ipp32f*  pDst,    int len))
IPPAPI(IppStatus, ippsAddC_32fc_I,    (                     Ipp32fc val, Ipp32fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsAddC_32fc,      (const Ipp32fc* pSrc, Ipp32fc val, Ipp32fc* pDst,    int len))
IPPAPI(IppStatus, ippsAddC_64f_I,     (                     Ipp64f  val, Ipp64f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsAddC_64f,       (const Ipp64f*  pSrc, Ipp64f  val, Ipp64f*  pDst,    int len))
IPPAPI(IppStatus, ippsAddC_64fc_I,    (                     Ipp64fc val, Ipp64fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsAddC_64fc,      (const Ipp64fc* pSrc, Ipp64fc val, Ipp64fc* pDst,    int len))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippsAdd
//  Purpose:    Adds elements of two vectors
//  Arguments:
//    pSrc1, pSrc2         Pointers to source vectors
//    pSrc                 Pointer to source vector for in-place operations
//    pSrcDst              Pointer to source and destination vector for in-place operation
//    pDst                 Pointer to destination vector
//    len                  Number of elements in vector
//    scaleFactor          Scale factor
//  Return:
//    ippStsNullPtrErr     At least one of the pointers is NULL
//    ippStsSizeErr        Vectors' length is less than 1
//    ippStsNoErr          No error
//  Note:
//    Add(X,Y)       :  Y[n] = Y[n] + X[n]
//    Add(X,Y,Z)     :  Z[n] = Y[n] + X[n]
*/
IPPAPI(IppStatus, ippsAdd_8u_ISfs,   (const Ipp8u*   pSrc,                        Ipp8u*   pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsAdd_8u_Sfs,    (const Ipp8u*   pSrc1, const Ipp8u*   pSrc2, Ipp8u*   pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsAdd_8u16u,     (const Ipp8u*   pSrc1, const Ipp8u*   pSrc2, Ipp16u*  pDst,    int len))
IPPAPI(IppStatus, ippsAdd_16s_I,     (const Ipp16s*  pSrc,                        Ipp16s*  pSrcDst, int len))
IPPAPI(IppStatus, ippsAdd_16s,       (const Ipp16s*  pSrc1, const Ipp16s*  pSrc2, Ipp16s*  pDst,    int len))
IPPAPI(IppStatus, ippsAdd_16s_ISfs,  (const Ipp16s*  pSrc,                        Ipp16s*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsAdd_16s_Sfs,   (const Ipp16s*  pSrc1, const Ipp16s*  pSrc2, Ipp16s*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsAdd_16s32s_I,  (const Ipp16s*  pSrc,                        Ipp32s*  pSrcDst, int len))
IPPAPI(IppStatus, ippsAdd_16s32f,    (const Ipp16s*  pSrc1, const Ipp16s*  pSrc2, Ipp32f*  pDst,    int len))
IPPAPI(IppStatus, ippsAdd_16sc_ISfs, (const Ipp16sc* pSrc,                        Ipp16sc* pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsAdd_16sc_Sfs,  (const Ipp16sc* pSrc1, const Ipp16sc* pSrc2, Ipp16sc* pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsAdd_16u_ISfs,  (const Ipp16u*  pSrc,                        Ipp16u*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsAdd_16u_Sfs,   (const Ipp16u*  pSrc1, const Ipp16u*  pSrc2, Ipp16u*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsAdd_16u,       (const Ipp16u*  pSrc1, const Ipp16u*  pSrc2, Ipp16u*  pDst,    int len))
IPPAPI(IppStatus, ippsAdd_32s_ISfs,  (const Ipp32s*  pSrc,                        Ipp32s*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsAdd_32s_Sfs,   (const Ipp32s*  pSrc1, const Ipp32s*  pSrc2, Ipp32s*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsAdd_32sc_ISfs, (const Ipp32sc* pSrc,                        Ipp32sc* pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsAdd_32sc_Sfs,  (const Ipp32sc* pSrc1, const Ipp32sc* pSrc2, Ipp32sc* pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsAdd_32u,       (const Ipp32u*  pSrc1, const Ipp32u*  pSrc2, Ipp32u*  pDst,    int len))
IPPAPI(IppStatus, ippsAdd_32u_I,     (const Ipp32u*  pSrc,                        Ipp32u*  pSrcDst, int len))
IPPAPI(IppStatus, ippsAdd_64s_Sfs,   (const Ipp64s*  pSrc1, const Ipp64s*  pSrc2, Ipp64s*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsAdd_32f_I,     (const Ipp32f*  pSrc,                        Ipp32f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsAdd_32f,       (const Ipp32f*  pSrc1, const Ipp32f*  pSrc2, Ipp32f*  pDst,    int len))
IPPAPI(IppStatus, ippsAdd_32fc_I,    (const Ipp32fc* pSrc,                        Ipp32fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsAdd_32fc,      (const Ipp32fc* pSrc1, const Ipp32fc* pSrc2, Ipp32fc* pDst,    int len))
IPPAPI(IppStatus, ippsAdd_64f_I,     (const Ipp64f*  pSrc,                        Ipp64f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsAdd_64f,       (const Ipp64f*  pSrc1, const Ipp64f*  pSrc2, Ipp64f*  pDst,    int len))
IPPAPI(IppStatus, ippsAdd_64fc_I,    (const Ipp64fc* pSrc,                        Ipp64fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsAdd_64fc,      (const Ipp64fc* pSrc1, const Ipp64fc* pSrc2, Ipp64fc* pDst,    int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsAddProductC
//  Purpose:    multiplies elements of of a vector by a constant and adds product to
//              the accumulator vector
//  Parameters:
//    pSrc                 pointer to the source vector
//    val                  constant value
//    pSrcDst              pointer to the source/destination (accumulator) vector
//    len                  length of the vectors
//  Return:
//    ippStsNullPtrErr     pointer to the vector is NULL
//    ippStsSizeErr        length of the vectors is less or equal zero
//    ippStsNoErr          otherwise
//
//  Notes:                 pSrcDst[n] = pSrcDst[n] + pSrc[n] * val, n=0,1,2,..len-1.
*/
IPPAPI(IppStatus, ippsAddProductC_32f, (const Ipp32f* pSrc, const Ipp32f val, Ipp32f* pSrcDst, int len))
IPPAPI(IppStatus, ippsAddProductC_64f, (const Ipp64f* pSrc, const Ipp64f val, Ipp64f* pSrcDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsAddProduct
//  Purpose:    multiplies elements of two source vectors and adds product to
//              the accumulator vector
//  Parameters:
//    pSrc1, pSrc2         Pointers to source vectors
//    pSrcDst              Pointer to destination accumulator vector
//    len                  Number of elements in  vectors
//    scaleFactor          scale factor value
//  Return:
//    ippStsNullPtrErr     At least one of the pointers is NULL
//    ippStsSizeErr        Vectors' length is less than 1
//    ippStsNoErr          No error
//  Notes:                 pSrcDst[n] = pSrcDst[n] + pSrc1[n] * pSrc2[n], n=0,1,2,..len-1.
*/
IPPAPI(IppStatus, ippsAddProduct_16s_Sfs,    (const Ipp16s*  pSrc1, const Ipp16s*  pSrc2, Ipp16s*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsAddProduct_16s32s_Sfs, (const Ipp16s*  pSrc1, const Ipp16s*  pSrc2, Ipp32s*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsAddProduct_32s_Sfs,    (const Ipp32s*  pSrc1, const Ipp32s*  pSrc2, Ipp32s*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsAddProduct_32f,        (const Ipp32f*  pSrc1, const Ipp32f*  pSrc2, Ipp32f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsAddProduct_32fc,       (const Ipp32fc* pSrc1, const Ipp32fc* pSrc2, Ipp32fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsAddProduct_64f,        (const Ipp64f*  pSrc1, const Ipp64f*  pSrc2, Ipp64f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsAddProduct_64fc,       (const Ipp64fc* pSrc1, const Ipp64fc* pSrc2, Ipp64fc* pSrcDst, int len))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:       ippsMulC
//  Purpose:     Multiplies each element of a vector by a constant value
//  Arguments:
//    pSrc             Pointer to source vector
//    pSrcDst          Pointer to source and destination vector for in-place operation
//    pDst             Pointer to destination vector
//    val              The scalar value used to multiply each element of source vector
//    len              Number of elements in vector
//    scaleFactor      Scale factor
//  Return:
//    ippStsNullPtrErr At least one of the pointers is NULL
//    ippStsSizeErr    Vectors' length is less than 1
//    ippStsNoErr      No error
//  Note:
//    MulC(X,v,Y)    :  Y[n] = X[n] * v
*/
IPPAPI(IppStatus, ippsMulC_8u_ISfs,     (                     Ipp8u   val, Ipp8u*   pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsMulC_8u_Sfs,      (const Ipp8u*   pSrc, Ipp8u   val, Ipp8u*   pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsMulC_16s_I,       (                     Ipp16s  val, Ipp16s*  pSrcDst, int len))
IPPAPI(IppStatus, ippsMulC_16s_ISfs,    (                     Ipp16s  val, Ipp16s*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsMulC_16s_Sfs,     (const Ipp16s*  pSrc, Ipp16s  val, Ipp16s*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsMulC_16sc_ISfs,   (                     Ipp16sc val, Ipp16sc* pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsMulC_16sc_Sfs,    (const Ipp16sc* pSrc, Ipp16sc val, Ipp16sc* pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsMulC_16u_ISfs,    (                     Ipp16u  val, Ipp16u*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsMulC_16u_Sfs,     (const Ipp16u* pSrc,  Ipp16u  val, Ipp16u*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsMulC_32s_ISfs,    (                     Ipp32s  val, Ipp32s*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsMulC_32s_Sfs,     (const Ipp32s*  pSrc, Ipp32s  val, Ipp32s*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsMulC_32sc_ISfs,   (                     Ipp32sc val, Ipp32sc* pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsMulC_32sc_Sfs,    (const Ipp32sc* pSrc, Ipp32sc val, Ipp32sc* pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsMulC_64s_ISfs,    (                     Ipp64s  val, Ipp64s*  pSrcDst, Ipp32u len, int scaleFactor))
IPPAPI(IppStatus, ippsMulC_32f_I,       (                     Ipp32f  val, Ipp32f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsMulC_32f,         (const Ipp32f*  pSrc, Ipp32f  val, Ipp32f*  pDst,    int len))
IPPAPI(IppStatus, ippsMulC_32fc_I,      (                     Ipp32fc val, Ipp32fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsMulC_32fc,        (const Ipp32fc* pSrc, Ipp32fc val, Ipp32fc* pDst,    int len))
IPPAPI(IppStatus, ippsMulC_32f16s_Sfs,  (const Ipp32f*  pSrc, Ipp32f  val, Ipp16s*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsMulC_Low_32f16s,  (const Ipp32f*  pSrc, Ipp32f  val, Ipp16s*  pDst,    int len))
IPPAPI(IppStatus, ippsMulC_64f_I,       (                     Ipp64f  val, Ipp64f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsMulC_64f,         (const Ipp64f*  pSrc, Ipp64f  val, Ipp64f*  pDst,    int len))
IPPAPI(IppStatus, ippsMulC_64fc_I,      (                     Ipp64fc val, Ipp64fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsMulC_64fc,        (const Ipp64fc* pSrc, Ipp64fc val, Ipp64fc* pDst,    int len))
IPPAPI(IppStatus, ippsMulC_64f64s_ISfs, (                     Ipp64f  val, Ipp64s*  pSrcDst, Ipp32u len, int scaleFactor))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippsMul
//  Purpose:    Multiplies elements of two vectors
//  Arguments:
//    pSrc1, pSrc2         Pointers to source vectors
//    pSrc                 Pointer to source vector for in-place operations
//    pSrcDst              Pointer to source and destination vector for in-place operation
//    pDst                 Pointer to destination vector
//    len                  Number of elements in vector
//    scaleFactor          Scale factor
//  Return:
//    ippStsNullPtrErr     At least one of the pointers is NULL
//    ippStsSizeErr        Vectors' length is less than 1
//    ippStsNoErr          No error
//  Note:
//    Mul(X,Y)       :  Y[n] = Y[n] * X[n]
//    Mul(X,Y,Z)     :  Z[n] = Y[n] * X[n]
*/
IPPAPI(IppStatus, ippsMul_8u_ISfs,   (const Ipp8u*   pSrc,                        Ipp8u*   pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsMul_8u_Sfs,    (const Ipp8u*   pSrc1, const Ipp8u*   pSrc2, Ipp8u*   pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsMul_8u16u,     (const Ipp8u*   pSrc1, const Ipp8u*   pSrc2, Ipp16u*  pDst,    int len))
IPPAPI(IppStatus, ippsMul_16s_I,     (const Ipp16s*  pSrc,                        Ipp16s*  pSrcDst, int len))
IPPAPI(IppStatus, ippsMul_16s,       (const Ipp16s*  pSrc1, const Ipp16s*  pSrc2, Ipp16s*  pDst,    int len))
IPPAPI(IppStatus, ippsMul_16s_ISfs,  (const Ipp16s*  pSrc,                        Ipp16s*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsMul_16s_Sfs,   (const Ipp16s*  pSrc1, const Ipp16s*  pSrc2, Ipp16s*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsMul_16sc_ISfs, (const Ipp16sc* pSrc,                        Ipp16sc* pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsMul_16sc_Sfs,  (const Ipp16sc* pSrc1, const Ipp16sc* pSrc2, Ipp16sc* pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsMul_16s32s_Sfs,(const Ipp16s*  pSrc1, const Ipp16s*  pSrc2, Ipp32s*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsMul_16s32f,    (const Ipp16s*  pSrc1, const Ipp16s*  pSrc2, Ipp32f*  pDst,    int len))
IPPAPI(IppStatus, ippsMul_16u_ISfs,  (const Ipp16u*  pSrc,                        Ipp16u*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsMul_16u_Sfs,   (const Ipp16u*  pSrc1, const Ipp16u* pSrc2,  Ipp16u*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsMul_16u16s_Sfs,(const Ipp16u*  pSrc1, const Ipp16s* pSrc2,  Ipp16s*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsMul_32s_ISfs,  (const Ipp32s*  pSrc,                        Ipp32s*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsMul_32s_Sfs,   (const Ipp32s*  pSrc1, const Ipp32s*  pSrc2, Ipp32s*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsMul_32sc_ISfs, (const Ipp32sc* pSrc,                        Ipp32sc* pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsMul_32sc_Sfs,  (const Ipp32sc* pSrc1, const Ipp32sc* pSrc2, Ipp32sc* pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsMul_32f_I,     (const Ipp32f*  pSrc,                        Ipp32f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsMul_32f,       (const Ipp32f*  pSrc1, const Ipp32f*  pSrc2, Ipp32f*  pDst,    int len))
IPPAPI(IppStatus, ippsMul_32fc_I,    (const Ipp32fc* pSrc,                        Ipp32fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsMul_32fc,      (const Ipp32fc* pSrc1, const Ipp32fc* pSrc2, Ipp32fc* pDst,    int len))
IPPAPI(IppStatus, ippsMul_32f32fc_I, (const Ipp32f*  pSrc,                        Ipp32fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsMul_32f32fc,   (const Ipp32f*  pSrc1, const Ipp32fc* pSrc2, Ipp32fc* pDst,    int len))
IPPAPI(IppStatus, ippsMul_64f_I,     (const Ipp64f*  pSrc,                        Ipp64f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsMul_64f,       (const Ipp64f*  pSrc1, const Ipp64f*  pSrc2, Ipp64f*  pDst,    int len))
IPPAPI(IppStatus, ippsMul_64fc_I,    (const Ipp64fc* pSrc,                        Ipp64fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsMul_64fc,      (const Ipp64fc* pSrc1, const Ipp64fc* pSrc2, Ipp64fc* pDst,    int len))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:       ippsSubC
//  Purpose:     Subtracts constant value from each element of vector
//  Arguments:
//    pSrc             Pointer to source vector
//    pSrcDst          Pointer to source and destination vector for in-place operation
//    pDst             Pointer to destination vector
//    val              Scalar value used to decrement each element of the source vector
//    len              Number of elements in vector
//    scaleFactor      Scale factor
//  Return:
//    ippStsNullPtrErr At least one of the pointers is NULL
//    ippStsSizeErr    Vectors' length is less than 1
//    ippStsNoErr      No error
//  Note:
//    SubC(X,v,Y)    :  Y[n] = X[n] - v
*/
IPPAPI(IppStatus, ippsSubC_8u_ISfs,   (                     Ipp8u   val, Ipp8u*   pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSubC_8u_Sfs,    (const Ipp8u*   pSrc, Ipp8u   val, Ipp8u*   pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSubC_16s_I,     (                     Ipp16s  val, Ipp16s*  pSrcDst, int len))
IPPAPI(IppStatus, ippsSubC_16s_ISfs,  (                     Ipp16s  val, Ipp16s*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSubC_16s_Sfs,   (const Ipp16s*  pSrc, Ipp16s  val, Ipp16s*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSubC_16sc_ISfs, (                     Ipp16sc val, Ipp16sc* pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSubC_16sc_Sfs,  (const Ipp16sc* pSrc, Ipp16sc val, Ipp16sc* pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSubC_16u_ISfs,  (                     Ipp16u  val, Ipp16u*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSubC_16u_Sfs,   (const Ipp16u* pSrc,  Ipp16u  val, Ipp16u*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSubC_32s_ISfs,  (                     Ipp32s  val, Ipp32s*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSubC_32s_Sfs,   (const Ipp32s*  pSrc, Ipp32s  val, Ipp32s*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSubC_32sc_ISfs, (                     Ipp32sc val, Ipp32sc* pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSubC_32sc_Sfs,  (const Ipp32sc* pSrc, Ipp32sc val, Ipp32sc* pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSubC_32f_I,     (                     Ipp32f  val, Ipp32f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsSubC_32f,       (const Ipp32f*  pSrc, Ipp32f  val, Ipp32f*  pDst,    int len))
IPPAPI(IppStatus, ippsSubC_32fc_I,    (                     Ipp32fc val, Ipp32fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsSubC_32fc,      (const Ipp32fc* pSrc, Ipp32fc val, Ipp32fc* pDst,    int len))
IPPAPI(IppStatus, ippsSubC_64f_I,     (                     Ipp64f  val, Ipp64f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsSubC_64f,       (const Ipp64f*  pSrc, Ipp64f  val, Ipp64f*  pDst,    int len))
IPPAPI(IppStatus, ippsSubC_64fc_I,    (                     Ipp64fc val, Ipp64fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsSubC_64fc,      (const Ipp64fc* pSrc, Ipp64fc val, Ipp64fc* pDst,    int len))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:       ippsSubCRev
//  Purpose:     Subtracts each element of vector from constant value
//  Arguments:
//    pSrc             Pointer to source vector
//    pSrcDst          Pointer to source and destination vector for in-place operation
//    pDst             Pointer to destination vector
//    val              Scalar value from which vector elements are subtracted
//    len              Number of elements in vector
//    scaleFactor      Scale factor
//  Return:
//    ippStsNullPtrErr At least one of the pointers is NULL
//    ippStsSizeErr    Vectors' length is less than 1
//    ippStsNoErr      No error
//  Note:
//    SubCRev(X,v,Y) :  Y[n] = v - X[n]
*/
IPPAPI(IppStatus, ippsSubCRev_8u_ISfs,   (                     Ipp8u   val, Ipp8u*   pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSubCRev_8u_Sfs,    (const Ipp8u*   pSrc, Ipp8u   val, Ipp8u*   pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSubCRev_16s_ISfs,  (                     Ipp16s  val, Ipp16s*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSubCRev_16s_Sfs,   (const Ipp16s*  pSrc, Ipp16s  val, Ipp16s*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSubCRev_16sc_ISfs, (                     Ipp16sc val, Ipp16sc* pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSubCRev_16sc_Sfs,  (const Ipp16sc* pSrc, Ipp16sc val, Ipp16sc* pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSubCRev_16u_ISfs,  (                     Ipp16u  val, Ipp16u*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSubCRev_16u_Sfs,   (const Ipp16u* pSrc,  Ipp16u  val, Ipp16u*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSubCRev_32s_ISfs,  (                     Ipp32s  val, Ipp32s*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSubCRev_32s_Sfs,   (const Ipp32s*  pSrc, Ipp32s  val, Ipp32s*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSubCRev_32sc_ISfs, (                     Ipp32sc val, Ipp32sc* pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSubCRev_32sc_Sfs,  (const Ipp32sc* pSrc, Ipp32sc val, Ipp32sc* pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSubCRev_32f_I,     (                     Ipp32f  val, Ipp32f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsSubCRev_32f,       (const Ipp32f*  pSrc, Ipp32f  val, Ipp32f*  pDst,    int len))
IPPAPI(IppStatus, ippsSubCRev_32fc_I,    (                     Ipp32fc val, Ipp32fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsSubCRev_32fc,      (const Ipp32fc* pSrc, Ipp32fc val, Ipp32fc* pDst,    int len))
IPPAPI(IppStatus, ippsSubCRev_64f_I,     (                     Ipp64f  val, Ipp64f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsSubCRev_64f,       (const Ipp64f*  pSrc, Ipp64f  val, Ipp64f*  pDst,    int len))
IPPAPI(IppStatus, ippsSubCRev_64fc_I,    (                     Ipp64fc val, Ipp64fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsSubCRev_64fc,      (const Ipp64fc* pSrc, Ipp64fc val, Ipp64fc* pDst,    int len))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippsSub
//  Purpose:    Subtracts elements of two vectors
//  Arguments:
//    pSrc1, pSrc2         Pointers to source vectors
//    pSrc                 Pointer to source vector for in-place operations
//    pSrcDst              Pointer to source and destination vector for in-place operation
//    pDst                 Pointer to destination vector
//    len                  Number of elements in vector
//    scaleFactor          Scale factor
//  Return:
//    ippStsNullPtrErr     At least one of the pointers is NULL
//    ippStsSizeErr        Vectors' length is less than 1
//    ippStsNoErr          No error
//  Note:
//    Sub(X,Y)       :  Y[n] = Y[n] - X[n]
//    Sub(X,Y,Z)     :  Z[n] = Y[n] - X[n]
*/
IPPAPI(IppStatus, ippsSub_8u_ISfs,   (const Ipp8u*   pSrc,                        Ipp8u*   pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSub_8u_Sfs,    (const Ipp8u*   pSrc1, const Ipp8u*   pSrc2, Ipp8u*   pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSub_16s_I,     (const Ipp16s*  pSrc,                        Ipp16s*  pSrcDst, int len))
IPPAPI(IppStatus, ippsSub_16s,       (const Ipp16s*  pSrc1, const Ipp16s*  pSrc2, Ipp16s*  pDst,    int len))
IPPAPI(IppStatus, ippsSub_16s_ISfs,  (const Ipp16s*  pSrc,                        Ipp16s*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSub_16s_Sfs,   (const Ipp16s*  pSrc1, const Ipp16s*  pSrc2, Ipp16s*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSub_16sc_ISfs, (const Ipp16sc* pSrc,                        Ipp16sc* pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSub_16sc_Sfs,  (const Ipp16sc* pSrc1, const Ipp16sc* pSrc2, Ipp16sc* pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSub_16s32f,    (const Ipp16s*  pSrc1, const Ipp16s*  pSrc2, Ipp32f*  pDst,    int len))
IPPAPI(IppStatus, ippsSub_16u_ISfs,  (const Ipp16u*  pSrc,                        Ipp16u*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSub_16u_Sfs,   (const Ipp16u*  pSrc1, const Ipp16u*  pSrc2, Ipp16u*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSub_32s_ISfs,  (const Ipp32s*  pSrc,                        Ipp32s*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSub_32s_Sfs,   (const Ipp32s*  pSrc1, const Ipp32s*  pSrc2, Ipp32s*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSub_32sc_ISfs, (const Ipp32sc* pSrc,                        Ipp32sc* pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSub_32sc_Sfs,  (const Ipp32sc* pSrc1, const Ipp32sc* pSrc2, Ipp32sc* pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSub_32f_I,     (const Ipp32f*  pSrc,                        Ipp32f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsSub_32f,       (const Ipp32f*  pSrc1, const Ipp32f*  pSrc2, Ipp32f*  pDst,    int len))
IPPAPI(IppStatus, ippsSub_32fc_I,    (const Ipp32fc* pSrc,                        Ipp32fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsSub_32fc,      (const Ipp32fc* pSrc1, const Ipp32fc* pSrc2, Ipp32fc* pDst,    int len))
IPPAPI(IppStatus, ippsSub_64f_I,     (const Ipp64f*  pSrc,                        Ipp64f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsSub_64f,       (const Ipp64f*  pSrc1, const Ipp64f*  pSrc2, Ipp64f*  pDst,    int len))
IPPAPI(IppStatus, ippsSub_64fc_I,    (const Ipp64fc* pSrc,                        Ipp64fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsSub_64fc,      (const Ipp64fc* pSrc1, const Ipp64fc* pSrc2, Ipp64fc* pDst,    int len))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDivC
//  Purpose:    Divides each element of a vector by a constant value
//  Arguments:
//    val               Scalar value used as a divisor
//    pSrc              Pointer to the source vector
//    pDst              Pointer to the destination vector
//    pSrcDst           Pointer to the source and destination vector for in-place operation
//    len               Number of elements in the vector
//    scaleFactor       Scale factor
//  Return:
//    ippStsNullPtrErr     At least one of the pointers is NULL
//    ippStsSizeErr        Vector length is less than 1
//    ippStsDivByZeroErr   Indicates an error when val is equal to 0
//    ippStsNoErr          No error
//  Note:
//    DivC(v,X,Y)  :    Y[n] = X[n] / v
//    DivC(v,X)    :    X[n] = X[n] / v
*/
IPPAPI(IppStatus, ippsDivC_8u_ISfs,  (                     Ipp8u   val, Ipp8u*   pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsDivC_8u_Sfs,   (const Ipp8u*   pSrc, Ipp8u   val, Ipp8u*   pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsDivC_16s_ISfs, (                     Ipp16s  val, Ipp16s*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsDivC_16s_Sfs,  (const Ipp16s*  pSrc, Ipp16s  val, Ipp16s*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsDivC_16sc_ISfs,(                     Ipp16sc val, Ipp16sc* pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsDivC_16sc_Sfs, (const Ipp16sc* pSrc, Ipp16sc val, Ipp16sc* pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsDivC_16u_ISfs, (                     Ipp16u  val, Ipp16u*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsDivC_16u_Sfs,  (const Ipp16u*  pSrc, Ipp16u  val, Ipp16u*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsDivC_64s_ISfs, (                     Ipp64s  val, Ipp64s*  pSrcDst, Ipp32u len, int scaleFactor))
IPPAPI(IppStatus, ippsDivC_32f_I,    (                     Ipp32f  val, Ipp32f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsDivC_32f,      (const Ipp32f*  pSrc, Ipp32f  val, Ipp32f*  pDst,    int len))
IPPAPI(IppStatus, ippsDivC_32fc_I,   (                     Ipp32fc val, Ipp32fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsDivC_32fc,     (const Ipp32fc* pSrc, Ipp32fc val, Ipp32fc* pDst,    int len))
IPPAPI(IppStatus, ippsDivC_64f_I,    (                     Ipp64f  val, Ipp64f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsDivC_64f,      (const Ipp64f*  pSrc, Ipp64f  val, Ipp64f*  pDst,    int len))
IPPAPI(IppStatus, ippsDivC_64fc_I,   (                     Ipp64fc val, Ipp64fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsDivC_64fc,     (const Ipp64fc* pSrc, Ipp64fc val, Ipp64fc* pDst,    int len))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDivCRev
//  Purpose:    Divides a constant value by each element of a vector
//  Arguments:
//    val               Constant value used as a dividend in the operation
//    pSrc              Pointer to the source vector whose elements are used as divisors
//    pDst              Pointer to the destination vector
//    pSrcDst           Pointer to the source and destination vector for in-place operation
//    len               Number of elements in the vector
//    scaleFactor       Scale factor
//  Return:
//    ippStsNullPtrErr  At least one of the pointers is NULL
//    ippStsSizeErr     Vector length is less than 1
//    ippStsDivByZero   Warning status if any element of vector is zero. IF the dividend is zero
//                      than result is NaN, if the dividend is not zero than result is Infinity
//                      with correspondent sign. Execution is not aborted.
//                      For the integer operation zero instead of NaN and the corresponding
//                      bound values instead of Infinity
//    ippStsNoErr       No error
//  Note:
//    DivCRev(v,X,Y)  :    Y[n] = v / X[n]
//    DivCRev(v,X)    :    X[n] = v / X[n]
*/
IPPAPI(IppStatus, ippsDivCRev_16u_I, (                    Ipp16u val, Ipp16u* pSrcDst, int len))
IPPAPI(IppStatus, ippsDivCRev_16u,   (const Ipp16u* pSrc, Ipp16u val, Ipp16u* pDst,    int len))
IPPAPI(IppStatus, ippsDivCRev_32f_I, (                    Ipp32f val, Ipp32f* pSrcDst, int len))
IPPAPI(IppStatus, ippsDivCRev_32f,   (const Ipp32f* pSrc, Ipp32f val, Ipp32f* pDst,    int len))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDiv
//  Purpose:    Divides the elements of two vectors
//  Arguments:
//    pSrc1             Pointer to the divisor vector.
//    pSrc2             Pointer to the dividend vector.
//    pDst              Pointer to the destination vector
//    pSrc              Pointer to the divisor vector for in-place operations
//    pSrcDst           Pointer to the source and destination vector for in-place operation
//    len               Number of elements in the vector
//    scaleFactor       Scale factor
//  Return:
//    ippStsNullPtrErr  At least one of the pointers is NULL
//    ippStsSizeErr     Vector length is less than 1
//    ippStsDivByZero   Warning status if any element of vector is zero. IF the dividend is zero
//                      than result is NaN, if the dividend is not zero than result is Infinity
//                      with correspondent sign. Execution is not aborted.
//                      For the integer operation zero instead of NaN and the corresponding
//                      bound values instead of Infinity
//    ippStsNoErr       No error
//  Note:
//    Div(X,Y)     :    Y[n] = Y[n] / X[n]
//    Div(X,Y,Z)   :    Z[n] = Y[n] / X[n]
*/
IPPAPI(IppStatus, ippsDiv_8u_ISfs,   (const Ipp8u*   pSrc,                        Ipp8u*   pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsDiv_8u_Sfs,    (const Ipp8u*   pSrc1, const Ipp8u*   pSrc2, Ipp8u*   pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsDiv_16s_ISfs,  (const Ipp16s*  pSrc,                        Ipp16s*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsDiv_16s_Sfs,   (const Ipp16s*  pSrc1, const Ipp16s*  pSrc2, Ipp16s*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsDiv_16sc_ISfs, (const Ipp16sc* pSrc,                        Ipp16sc* pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsDiv_16sc_Sfs,  (const Ipp16sc* pSrc1, const Ipp16sc* pSrc2, Ipp16sc* pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsDiv_32s_ISfs,  (const Ipp32s*  pSrc,                        Ipp32s*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsDiv_32s_Sfs,   (const Ipp32s*  pSrc1, const Ipp32s*  pSrc2, Ipp32s*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsDiv_32s16s_Sfs,(const Ipp16s*  pSrc1, const Ipp32s*  pSrc2, Ipp16s*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsDiv_16u_ISfs,  (const Ipp16u*  pSrc,                        Ipp16u*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsDiv_16u_Sfs,   (const Ipp16u*  pSrc1, const Ipp16u*  pSrc2, Ipp16u*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsDiv_32f_I,     (const Ipp32f*  pSrc,                        Ipp32f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsDiv_32f,       (const Ipp32f*  pSrc1, const Ipp32f*  pSrc2, Ipp32f*  pDst,    int len))
IPPAPI(IppStatus, ippsDiv_32fc_I,    (const Ipp32fc* pSrc,                        Ipp32fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsDiv_32fc,      (const Ipp32fc* pSrc1, const Ipp32fc* pSrc2, Ipp32fc* pDst,    int len))
IPPAPI(IppStatus, ippsDiv_64f_I,     (const Ipp64f*  pSrc,                        Ipp64f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsDiv_64f,       (const Ipp64f*  pSrc1, const Ipp64f*  pSrc2, Ipp64f*  pDst,    int len))
IPPAPI(IppStatus, ippsDiv_64fc_I,    (const Ipp64fc* pSrc,                        Ipp64fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsDiv_64fc,      (const Ipp64fc* pSrc1, const Ipp64fc* pSrc2, Ipp64fc* pDst,    int len))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDiv_Round
//  Purpose:    Divides the elements of two vectors with defined rounding
//  Arguments:
//    pSrc1        Pointer to the divisor vector.
//    pSrc2        Pointer to the dividend vector.
//    pDst         Pointer to the destination vector
//    pSrc         Pointer to the divisor vector for in-place operations
//    pSrcDst      Pointer to the source and destination vector for in-place operation
//    len          Number of elements in the vector
//    rndMode      Rounding mode, the following values are possible:
//                 ippRndZero- specifies that floating-point values are truncated toward zero,
//                 ippRndNear- specifies that floating-point values are rounded to the
//                             nearest even integer when the fractional part equals 0.5;
//                             otherwise they are rounded to the nearest integer,
//                 ippRndFinancial- specifies that floating-point values are rounded down
//                             to the nearest integer when the fractional part is less than 0.5,
//                             or rounded up to the nearest integer if the fractional part is
//                             equal or greater than 0.5.
//    scaleFactor       Scale factor
//  Return:
//    ippStsNullPtrErr  At least one of the pointers is NULL
//    ippStsSizeErr     Vector length is less than 1
//    ippStsDivByZero   Warning status if any element of vector is zero. IF the dividend is zero
//                      than result is NaN, if the dividend is not zero than result is Infinity
//                      with correspondent sign. Execution is not aborted.
//                      For the integer operation zero instead of NaN and the corresponding
//                      bound values instead of Infinity
//    ippStsNoErr       No error
//  Note:
//    Div(X,Y)     :    Y[n] = Y[n] / X[n]
//    Div(X,Y,Z)   :    Z[n] = Y[n] / X[n]
*/
IPPAPI(IppStatus, ippsDiv_Round_8u_ISfs,  (const Ipp8u*  pSrc,                       Ipp8u*  pSrcDst, int len, IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippsDiv_Round_8u_Sfs,   (const Ipp8u*  pSrc1, const Ipp8u*  pSrc2, Ipp8u*  pDst,    int len, IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippsDiv_Round_16s_ISfs, (const Ipp16s* pSrc,                       Ipp16s* pSrcDst, int len, IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippsDiv_Round_16s_Sfs,  (const Ipp16s* pSrc1, const Ipp16s* pSrc2, Ipp16s* pDst,    int len, IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippsDiv_Round_16u_ISfs, (const Ipp16u* pSrc,                       Ipp16u* pSrcDst, int len, IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippsDiv_Round_16u_Sfs,  (const Ipp16u* pSrc1, const Ipp16u* pSrc2, Ipp16u* pDst,    int len, IppRoundMode rndMode, int scaleFactor))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsAbs
//  Purpose:    compute absolute value of each element of the source vector
//  Parameters:
//   pSrcDst            pointer to the source/destination vector
//   pSrc               pointer to the source vector
//   pDst               pointer to the destination vector
//   len                length of the vector(s), number of items
//  Return:
//   ippStsNullPtrErr      pointer(s) to data vector is NULL
//   ippStsSizeErr         length of a vector is less or equal 0
//   ippStsNoErr           otherwise
*/
IPPAPI(IppStatus, ippsAbs_16s_I, (                    Ipp16s* pSrcDst, int len))
IPPAPI(IppStatus, ippsAbs_16s,   (const Ipp16s* pSrc, Ipp16s* pDst,    int len))
IPPAPI(IppStatus, ippsAbs_32s_I, (                    Ipp32s* pSrcDst, int len))
IPPAPI(IppStatus, ippsAbs_32s,   (const Ipp32s* pSrc, Ipp32s* pDst,    int len))
IPPAPI(IppStatus, ippsAbs_32f_I, (                    Ipp32f* pSrcDst, int len))
IPPAPI(IppStatus, ippsAbs_32f,   (const Ipp32f* pSrc, Ipp32f* pDst,    int len))
IPPAPI(IppStatus, ippsAbs_64f_I, (                    Ipp64f* pSrcDst, int len))
IPPAPI(IppStatus, ippsAbs_64f,   (const Ipp64f* pSrc, Ipp64f* pDst,    int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsSqr
//  Purpose:    Computes square of each element of source vector
//  Parameters:
//    pSrcDst          Pointer to the source and destination vector for in-place operations
//    pSrc             Pointer to the source vector
//    pDst             Pointer to the destination vector
//    len              Number of elements in the vector
//   scaleFactor       Scale factor
//  Return:
//    ippStsNullPtrErr     At least one of the pointers is NULL
//    ippStsSizeErr        Vectors' length is less than 1
//    ippStsNoErr          No error
*/
IPPAPI(IppStatus, ippsSqr_8u_ISfs,   (                     Ipp8u*   pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSqr_8u_Sfs,    (const Ipp8u*   pSrc, Ipp8u*   pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSqr_16s_ISfs,  (                     Ipp16s*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSqr_16s_Sfs,   (const Ipp16s*  pSrc, Ipp16s*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSqr_16sc_ISfs, (                     Ipp16sc* pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSqr_16sc_Sfs,  (const Ipp16sc* pSrc, Ipp16sc* pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSqr_16u_ISfs,  (                     Ipp16u*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSqr_16u_Sfs,   (const Ipp16u*  pSrc, Ipp16u*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSqr_32f_I,     (                     Ipp32f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsSqr_32f,       (const Ipp32f*  pSrc, Ipp32f*  pDst,    int len))
IPPAPI(IppStatus, ippsSqr_32fc_I,    (                     Ipp32fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsSqr_32fc,      (const Ipp32fc* pSrc, Ipp32fc* pDst,    int len))
IPPAPI(IppStatus, ippsSqr_64f_I,     (                     Ipp64f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsSqr_64f,       (const Ipp64f*  pSrc, Ipp64f*  pDst,    int len))
IPPAPI(IppStatus, ippsSqr_64fc_I,    (                     Ipp64fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsSqr_64fc,      (const Ipp64fc* pSrc, Ipp64fc* pDst,    int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsSqrt
//  Purpose:    compute square root value for every element of the source vector
//   pSrc                 pointer to the source vector
//   pDst                 pointer to the destination vector
//   pSrcDst              pointer to the source/destination vector
//   len                  length of the vector(s), number of items
//   scaleFactor          scale factor value
//  Return:
//   ippStsNullPtrErr        pointer to vector is NULL
//   ippStsSizeErr           length of the vector is less or equal zero
//   ippStsSqrtNegArg        negative value in real sequence
//   ippStsNoErr             otherwise
*/
IPPAPI(IppStatus, ippsSqrt_8u_ISfs,   (                     Ipp8u*   pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSqrt_8u_Sfs,    (const Ipp8u*   pSrc, Ipp8u*   pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSqrt_16s_ISfs,  (                     Ipp16s*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSqrt_16s_Sfs,   (const Ipp16s*  pSrc, Ipp16s*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSqrt_16sc_ISfs, (                     Ipp16sc* pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSqrt_16sc_Sfs,  (const Ipp16sc* pSrc, Ipp16sc* pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSqrt_16u_ISfs,  (                     Ipp16u*  pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsSqrt_16u_Sfs,   (const Ipp16u*  pSrc, Ipp16u*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSqrt_32s16s_Sfs,(const Ipp32s*  pSrc, Ipp16s*  pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsSqrt_32f_I,     (                     Ipp32f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsSqrt_32f,       (const Ipp32f*  pSrc, Ipp32f*  pDst,    int len))
IPPAPI(IppStatus, ippsSqrt_32fc_I,    (                     Ipp32fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsSqrt_32fc,      (const Ipp32fc* pSrc, Ipp32fc* pDst,    int len))
IPPAPI(IppStatus, ippsSqrt_64f_I,     (                     Ipp64f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsSqrt_64f,       (const Ipp64f*  pSrc, Ipp64f*  pDst,    int len))
IPPAPI(IppStatus, ippsSqrt_64fc_I,    (                     Ipp64fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsSqrt_64fc,      (const Ipp64fc* pSrc, Ipp64fc* pDst,    int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsCubrt
//  Purpose:    Compute cube root of every elements of the source vector
//  Parameters:
//   pSrc                 pointer to the source vector
//   pDst                 pointer to the destination vector
//   len                  length of the vector(s)
//   scaleFactor          scale factor value
//  Return:
//   ippStsNullPtrErr        pointer(s) to the data vector is NULL
//   ippStsSizeErr           length of the vector(s) is less or equal 0
//   ippStsNoErr             otherwise
*/
IPPAPI(IppStatus, ippsCubrt_32s16s_Sfs, (const Ipp32s* pSrc, Ipp16s* pDst, int Len, int scaleFactor))
IPPAPI(IppStatus, ippsCubrt_32f,        (const Ipp32f* pSrc, Ipp32f* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsExp
//  Purpose:    compute exponent value for all elements of the source vector
//  Parameters:
//   pSrcDst            pointer to the source/destination vector
//   pSrc               pointer to the source vector
//   pDst               pointer to the destination vector
//   len                length of the vector(s)
//   scaleFactor        scale factor value
//  Return:
//   ippStsNullPtrErr      pointer(s) to the data vector is NULL
//   ippStsSizeErr         length of the vector(s) is less or equal 0
//   ippStsNoErr           otherwise
*/
IPPAPI(IppStatus, ippsExp_16s_ISfs, (                    Ipp16s* pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsExp_16s_Sfs,  (const Ipp16s* pSrc, Ipp16s* pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsExp_32s_ISfs, (                    Ipp32s* pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsExp_32s_Sfs,  (const Ipp32s* pSrc, Ipp32s* pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsExp_32f_I,    (                    Ipp32f* pSrcDst, int len))
IPPAPI(IppStatus, ippsExp_32f,      (const Ipp32f* pSrc, Ipp32f* pDst,    int len))
IPPAPI(IppStatus, ippsExp_64f_I,    (                    Ipp64f* pSrcDst, int len))
IPPAPI(IppStatus, ippsExp_64f,      (const Ipp64f* pSrc, Ipp64f* pDst,    int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsLn
//  Purpose:    compute natural logarithm of every elements of the source vector
//  Parameters:
//   pSrcDst              pointer to the source/destination vector
//   pSrc                 pointer to the source vector
//   pDst                 pointer to the destination vector
//   len                  length of the vector(s)
//   ScaleFactor          scale factor value
//  Return:
//   ippStsNullPtrErr        pointer(s) to the data vector is NULL
//   ippStsSizeErr           length of the vector(s) is less or equal 0
//   ippStsLnZeroArg         zero value in the source vector
//   ippStsLnNegArg          negative value in the source vector
//   ippStsNoErr             otherwise
//  Notes:
//                Ln( x<0 ) = NaN
//                Ln( 0 ) = -Inf
*/
IPPAPI(IppStatus, ippsLn_16s_ISfs, (                    Ipp16s* pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsLn_16s_Sfs,  (const Ipp16s* pSrc, Ipp16s* pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsLn_32s_ISfs, (                    Ipp32s* pSrcDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsLn_32s_Sfs,  (const Ipp32s* pSrc, Ipp32s* pDst,    int len, int scaleFactor))
IPPAPI(IppStatus, ippsLn_32f_I,    (                    Ipp32f* pSrcDst, int len))
IPPAPI(IppStatus, ippsLn_32f,      (const Ipp32f* pSrc, Ipp32f* pDst,    int len))
IPPAPI(IppStatus, ippsLn_64f_I,    (                    Ipp64f* pSrcDst, int len))
IPPAPI(IppStatus, ippsLn_64f,      (const Ipp64f* pSrc, Ipp64f* pDst,    int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsSumLn
//  Purpose:    computes sum of natural logarithm every elements of the source vector
//  Parameters:
//   pSrc                 pointer to the source vector
//   pSum                 pointer to the result
//   len                  length of the vector
//  Return:
//   ippStsNullPtrErr     pointer(s) to the data vector is NULL
//   ippStsSizeErr        length of the vector(s) is less or equal 0
//   ippStsLnZeroArg      zero value in the source vector
//   ippStsLnNegArg       negative value in the source vector
//   ippStsNoErr          otherwise
*/


IPPAPI(IppStatus, ippsSumLn_16s32f, (const Ipp16s* pSrc, int len, Ipp32f* pSum))
IPPAPI(IppStatus, ippsSumLn_32f,    (const Ipp32f* pSrc, int len, Ipp32f* pSum))
IPPAPI(IppStatus, ippsSumLn_32f64f, (const Ipp32f* pSrc, int len, Ipp64f* pSum))
IPPAPI(IppStatus, ippsSumLn_64f,    (const Ipp64f* pSrc, int len, Ipp64f* pSum))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsArctan
//
//  Purpose: compute arctangent value for all elements of the source vector
//
//  Return:
//   stsNoErr           Ok
//   stsNullPtrErr      Some of pointers to input or output data are NULL
//   stsBadSizeErr      The length of the arrays is less or equal zero
//
//  Parameters:
//   pSrcDst            pointer to the source/destination vector
//   pSrc               pointer to the source vector
//   pDst               pointer to the destination vector
//   len                a length of the array
//
*/
IPPAPI(IppStatus, ippsArctan_32f_I, (                    Ipp32f* pSrcDst, int len))
IPPAPI(IppStatus, ippsArctan_32f,   (const Ipp32f* pSrc, Ipp32f* pDst,    int len))
IPPAPI(IppStatus, ippsArctan_64f_I, (                    Ipp64f* pSrcDst, int len))
IPPAPI(IppStatus, ippsArctan_64f,   (const Ipp64f* pSrc, Ipp64f* pDst,    int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:   ippsNormalize
//  Purpose: Normalizes elements of a real or complex vector using offset and division operations
//  Parameters:
//    pSrcDst     - Pointer to the source and destination vector for the in-place operation
//    pSrc        - Pointer to the source vector
//    pDst        - Pointer to the destination vector
//    len         - Number of elements in the vector
//    vSub        - Subtrahend value
//    vDiv        - Denominator value
//    scaleFactor - Scale factor
//  Return:
//    ippStsNoErr          No error
//    ippStsNullPtrErr     At least one of the pointers is NULL
//    ippStsSizeErr        Vector length is less than 1
//    ippStsDivByZeroErr   Indicates an error when vDivis equal to 0 or less than the
//                         minimum floating-point positive number
//  Note:
//      pDst[n] = (pSrc[n] - vSub)/vDiv
*/
IPPAPI(IppStatus, ippsNormalize_16s_ISfs, (                     Ipp16s* pSrcDst,  int len, Ipp16s  vSub, int    vDiv, int scaleFactor))
IPPAPI(IppStatus, ippsNormalize_16s_Sfs,  (const Ipp16s*  pSrc, Ipp16s* pDst,     int len, Ipp16s  vSub, int    vDiv, int scaleFactor))
IPPAPI(IppStatus, ippsNormalize_16sc_ISfs,(                     Ipp16sc* pSrcDst, int len, Ipp16sc vSub, int    vDiv, int scaleFactor))
IPPAPI(IppStatus, ippsNormalize_16sc_Sfs, (const Ipp16sc* pSrc, Ipp16sc* pDst,    int len, Ipp16sc vSub, int    vDiv, int scaleFactor))
IPPAPI(IppStatus, ippsNormalize_32f_I,    (                     Ipp32f* pSrcDst,  int len, Ipp32f  vSub, Ipp32f vDiv))
IPPAPI(IppStatus, ippsNormalize_32f,      (const Ipp32f*  pSrc, Ipp32f* pDst,     int len, Ipp32f  vSub, Ipp32f vDiv))
IPPAPI(IppStatus, ippsNormalize_32fc_I,   (                     Ipp32fc* pSrcDst, int len, Ipp32fc vSub, Ipp32f vDiv))
IPPAPI(IppStatus, ippsNormalize_32fc,     (const Ipp32fc* pSrc, Ipp32fc* pDst,    int len, Ipp32fc vSub, Ipp32f vDiv))
IPPAPI(IppStatus, ippsNormalize_64f_I,    (                     Ipp64f* pSrcDst,  int len, Ipp64f  vSub, Ipp64f vDiv))
IPPAPI(IppStatus, ippsNormalize_64f,      (const Ipp64f*  pSrc, Ipp64f* pDst,     int len, Ipp64f  vSub, Ipp64f vDiv))
IPPAPI(IppStatus, ippsNormalize_64fc_I,   (                     Ipp64fc* pSrcDst, int len, Ipp64fc vSub, Ipp64f vDiv))
IPPAPI(IppStatus, ippsNormalize_64fc,     (const Ipp64fc* pSrc, Ipp64fc* pDst,    int len, Ipp64fc vSub, Ipp64f vDiv))

/* /////////////////////////////////////////////////////////////////////////////
//                   Convert functions
///////////////////////////////////////////////////////////////////////////// */

/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippsSortAscend, ippsSortDescend
//
//  Purpose:    Execute sorting of all elemens of the vector.
//              ippsSortAscend  is sorted in increasing order.
//              ippsSortDescend is sorted in decreasing order.
//  Arguments:
//    pSrcDst              pointer to the source/destination vector
//    len                  length of the vector
//  Return:
//    ippStsNullPtrErr     pointer to the data is NULL
//    ippStsSizeErr        length of the vector is less or equal zero
//    ippStsNoErr          otherwise
*/
IPPAPI(IppStatus, ippsSortAscend_8u_I,  (Ipp8u*  pSrcDst, int len))
IPPAPI(IppStatus, ippsSortAscend_16s_I, (Ipp16s* pSrcDst, int len))
IPPAPI(IppStatus, ippsSortAscend_16u_I, (Ipp16u* pSrcDst, int len))
IPPAPI(IppStatus, ippsSortAscend_32s_I, (Ipp32s* pSrcDst, int len))
IPPAPI(IppStatus, ippsSortAscend_32f_I, (Ipp32f* pSrcDst, int len))
IPPAPI(IppStatus, ippsSortAscend_64f_I, (Ipp64f* pSrcDst, int len))

IPPAPI(IppStatus, ippsSortDescend_8u_I,  (Ipp8u*  pSrcDst, int len))
IPPAPI(IppStatus, ippsSortDescend_16s_I, (Ipp16s* pSrcDst, int len))
IPPAPI(IppStatus, ippsSortDescend_16u_I, (Ipp16u* pSrcDst, int len))
IPPAPI(IppStatus, ippsSortDescend_32s_I, (Ipp32s* pSrcDst, int len))
IPPAPI(IppStatus, ippsSortDescend_32f_I, (Ipp32f* pSrcDst, int len))
IPPAPI(IppStatus, ippsSortDescend_64f_I, (Ipp64f* pSrcDst, int len))

IPPAPI(IppStatus, ippsSortIndexAscend_8u_I,  (Ipp8u*  pSrcDst, int* pDstIdx, int len))
IPPAPI(IppStatus, ippsSortIndexAscend_16s_I, (Ipp16s* pSrcDst, int* pDstIdx, int len))
IPPAPI(IppStatus, ippsSortIndexAscend_16u_I, (Ipp16u* pSrcDst, int* pDstIdx, int len))
IPPAPI(IppStatus, ippsSortIndexAscend_32s_I, (Ipp32s* pSrcDst, int* pDstIdx, int len))
IPPAPI(IppStatus, ippsSortIndexAscend_32f_I, (Ipp32f* pSrcDst, int* pDstIdx, int len))
IPPAPI(IppStatus, ippsSortIndexAscend_64f_I, (Ipp64f* pSrcDst, int* pDstIdx, int len))

IPPAPI(IppStatus, ippsSortIndexDescend_8u_I,  (Ipp8u*  pSrcDst, int* pDstIdx, int len))
IPPAPI(IppStatus, ippsSortIndexDescend_16s_I, (Ipp16s* pSrcDst, int* pDstIdx, int len))
IPPAPI(IppStatus, ippsSortIndexDescend_16u_I, (Ipp16u* pSrcDst, int* pDstIdx, int len))
IPPAPI(IppStatus, ippsSortIndexDescend_32s_I, (Ipp32s* pSrcDst, int* pDstIdx, int len))
IPPAPI(IppStatus, ippsSortIndexDescend_32f_I, (Ipp32f* pSrcDst, int* pDstIdx, int len))
IPPAPI(IppStatus, ippsSortIndexDescend_64f_I, (Ipp64f* pSrcDst, int* pDstIdx, int len))

/* /////////////////////////////////////////////////////////////////////////////////////
//  Names:      ippsSortRadixGetBufferSize, ippsSortRadixIndexGetBufferSize
//  Purpose:     : Get the size (in bytes) of the buffer for ippsSortRadix internal calculations.
//  Arguments:
//    len           length of the vectors
//    dataType      data type of the vector.
//    pBufferSize   pointer to the calculated buffer size (in bytes).
//  Return:
//   ippStsNoErr        OK
//   ippStsNullPtrErr   pBufferSize is NULL
//   ippStsSizeErr      vector's length is not positive
//   ippStsDataTypeErr  unsupported data type
*/
IPPAPI(IppStatus, ippsSortRadixGetBufferSize,      (int    len, IppDataType dataType, int    *pBufferSize))
IPPAPI(IppStatus, ippsSortRadixIndexGetBufferSize,   (int    len, IppDataType dataType, int    *pBufferSize))

/* /////////////////////////////////////////////////////////////////////////////////////
//  Names:      ippsSortRadixAscend, ippsSortRadixDescend
//
//  Purpose:    Rearrange elements of input vector using radix sort algorithm.
//              ippsSortRadixAscend  - sorts input array in increasing order
//              ippsSortRadixDescend - sorts input array in decreasing order
//
//  Arguments:
//    pSrcDst   pointer to the source/destination vector
//    len       length of the vectors
//    pBuffer   pointer to the work buffer
//  Return:
//    ippStsNoErr       OK
//    ippStsNullPtrErr  pointer to the data or work buffer is NULL
//    ippStsSizeErr     length of the vector is less or equal zero
*/
IPPAPI(IppStatus, ippsSortRadixAscend_8u_I,  (Ipp8u  *pSrcDst, int    len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixAscend_16u_I, (Ipp16u *pSrcDst, int    len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixAscend_16s_I, (Ipp16s *pSrcDst, int    len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixAscend_32u_I, (Ipp32u *pSrcDst, int    len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixAscend_32s_I, (Ipp32s *pSrcDst, int    len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixAscend_32f_I, (Ipp32f *pSrcDst, int    len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixAscend_64u_I, (Ipp64u *pSrcDst, int    len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixAscend_64s_I, (Ipp64s *pSrcDst, int    len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixAscend_64f_I, (Ipp64f *pSrcDst, int    len, Ipp8u *pBuffer))

IPPAPI(IppStatus, ippsSortRadixDescend_8u_I,  (Ipp8u  *pSrcDst, int    len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixDescend_16u_I, (Ipp16u *pSrcDst, int    len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixDescend_16s_I, (Ipp16s *pSrcDst, int    len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixDescend_32u_I, (Ipp32u *pSrcDst, int    len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixDescend_32s_I, (Ipp32s *pSrcDst, int    len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixDescend_32f_I, (Ipp32f *pSrcDst, int    len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixDescend_64u_I, (Ipp64u *pSrcDst, int    len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixDescend_64s_I, (Ipp64s *pSrcDst, int    len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixDescend_64f_I, (Ipp64f *pSrcDst, int    len, Ipp8u *pBuffer))

/* /////////////////////////////////////////////////////////////////////////////////////
//  Names:      ippsSortRadixIndexAscend, ippsSortRadixIndexDescend
//
//  Purpose:    Indirectly sorts possibly sparse input vector, using indexes.
//              For a dense input array the following will be true:
//
//              ippsSortRadixIndexAscend  - pSrc[pDstIndx[i-1]] <= pSrc[pDstIndx[i]];
//              ippsSortRadixIndexDescend - pSrc[pDstIndx[i]] <= pSrc[pDstIndx[i-1]];
//
//  Arguments:
//    pSrc              pointer to the first element of a sparse input vector;
//    srcStrideBytes    step between two consecutive elements of input vector in bytes;
//    pDstIndx          pointer to the output indexes vector;
//    len               length of the vectors
//    pBuffer           pointer to the work buffer
//  Return:
//    ippStsNoErr       OK
//    ippStsNullPtrErr  pointers to the vectors or poiter to work buffer is NULL
//    ippStsSizeErr     length of the vector is less or equal zero
*/
IPPAPI(IppStatus, ippsSortRadixIndexAscend_8u,  (const Ipp8u*  pSrc, Ipp32s srcStrideBytes, Ipp32s *pDstIndx, int len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixIndexAscend_16s, (const Ipp16s* pSrc, Ipp32s srcStrideBytes, Ipp32s *pDstIndx, int len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixIndexAscend_16u, (const Ipp16u* pSrc, Ipp32s srcStrideBytes, Ipp32s *pDstIndx, int len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixIndexAscend_32s, (const Ipp32s* pSrc, Ipp32s srcStrideBytes, Ipp32s *pDstIndx, int len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixIndexAscend_32u, (const Ipp32u* pSrc, Ipp32s srcStrideBytes, Ipp32s *pDstIndx, int len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixIndexAscend_32f, (const Ipp32f* pSrc, Ipp32s srcStrideBytes, Ipp32s *pDstIndx, int len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixIndexAscend_64s, (const Ipp64s* pSrc, Ipp32s srcStrideBytes, Ipp32s *pDstIndx, int len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixIndexAscend_64u, (const Ipp64u* pSrc, Ipp32s srcStrideBytes, Ipp32s *pDstIndx, int len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixIndexAscend_64f, (const Ipp64f* pSrc, Ipp32s srcStrideBytes, Ipp32s *pDstIndx, int len, Ipp8u *pBuffer))

IPPAPI(IppStatus, ippsSortRadixIndexDescend_8u,  (const Ipp8u*  pSrc, Ipp32s srcStrideBytes, Ipp32s *pDstIndx, int len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixIndexDescend_16s, (const Ipp16s* pSrc, Ipp32s srcStrideBytes, Ipp32s *pDstIndx, int len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixIndexDescend_16u, (const Ipp16u* pSrc, Ipp32s srcStrideBytes, Ipp32s *pDstIndx, int len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixIndexDescend_32s, (const Ipp32s* pSrc, Ipp32s srcStrideBytes, Ipp32s *pDstIndx, int len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixIndexDescend_32u, (const Ipp32u* pSrc, Ipp32s srcStrideBytes, Ipp32s *pDstIndx, int len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixIndexDescend_32f, (const Ipp32f* pSrc, Ipp32s srcStrideBytes, Ipp32s *pDstIndx, int len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixIndexDescend_64s, (const Ipp64s* pSrc, Ipp32s srcStrideBytes, Ipp32s *pDstIndx, int len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixIndexDescend_64u, (const Ipp64u* pSrc, Ipp32s srcStrideBytes, Ipp32s *pDstIndx, int len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixIndexDescend_64f, (const Ipp64f* pSrc, Ipp32s srcStrideBytes, Ipp32s *pDstIndx, int len, Ipp8u *pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsSwapBytes
//  Purpose:    Reverses the byte order of vector
//  Parameters:
//    pSrc      Pointer to input vector
//    pSrcDst   Pointer to source and destination vector for in-place operation
//    pDst      Pointer to output vector
//    len       Vectors' length in elements
//  Return:
//    ippStsNullPtrErr        At least one pointer is NULL
//    ippStsSizeErr           Vectors' length is less than 1
//    ippStsNoErr             Otherwise
*/
IPPAPI(IppStatus, ippsSwapBytes_16u_I, (      Ipp16u* pSrcDst,            int len))
IPPAPI(IppStatus, ippsSwapBytes_16u,   (const Ipp16u* pSrc, Ipp16u* pDst, int len))
IPPAPI(IppStatus, ippsSwapBytes_24u_I, (      Ipp8u*  pSrcDst,            int len))
IPPAPI(IppStatus, ippsSwapBytes_24u,   (const Ipp8u*  pSrc, Ipp8u*  pDst, int len))
IPPAPI(IppStatus, ippsSwapBytes_32u_I, (      Ipp32u* pSrcDst,            int len))
IPPAPI(IppStatus, ippsSwapBytes_32u,   (const Ipp32u* pSrc, Ipp32u* pDst, int len))
IPPAPI(IppStatus, ippsSwapBytes_64u_I, (      Ipp64u* pSrcDst,            int len))
IPPAPI(IppStatus, ippsSwapBytes_64u,   (const Ipp64u* pSrc, Ipp64u* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsConvert
//  Purpose:    Converts vector data type
//  Parameters:
//    pSrc        Pointer to input vector
//    pDst        Pointer to output vector
//    len         Vectors' length in elements
//    rndMode     Round mode - ippRndZero, ippRndNear or ippRndFinancial
//    scaleFactor Scale factor (for some integer outputs)
//  Return:
//    ippStsNullPtrErr               One of pointers is NULL
//    ippStsSizeErr                  Vectors' length is less than 1
//    ippStsRoundModeNotSupportedErr Specified round mode is not supported
//    ippStsNoErr                    No error
//  Note:
//    all out-of-range result are saturated
*/
IPPAPI(IppStatus, ippsConvert_8s16s,      (const Ipp8s*  pSrc, Ipp16s* pDst, int len))
IPPAPI(IppStatus, ippsConvert_8s32f,      (const Ipp8s*  pSrc, Ipp32f* pDst, int len))
IPPAPI(IppStatus, ippsConvert_8u32f,      (const Ipp8u*  pSrc, Ipp32f* pDst, int len))
IPPAPI(IppStatus, ippsConvert_16s8s_Sfs,  (const Ipp16s* pSrc, Ipp8s*  pDst, Ipp32u len, IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippsConvert_16s32s,     (const Ipp16s* pSrc, Ipp32s* pDst, int len))
IPPAPI(IppStatus, ippsConvert_16s16f,     (const Ipp16s* pSrc, Ipp16f* pDst, int len, IppRoundMode rndMode))
IPPAPI(IppStatus, ippsConvert_16s32f,     (const Ipp16s* pSrc, Ipp32f* pDst, int len))
IPPAPI(IppStatus, ippsConvert_16s32f_Sfs, (const Ipp16s* pSrc, Ipp32f* pDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsConvert_16s64f_Sfs, (const Ipp16s* pSrc, Ipp64f* pDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsConvert_16u32f,     (const Ipp16u* pSrc, Ipp32f* pDst, int len))
IPPAPI(IppStatus, ippsConvert_24s32s,     (const Ipp8u*  pSrc, Ipp32s* pDst, int len))
IPPAPI(IppStatus, ippsConvert_24s32f,     (const Ipp8u*  pSrc, Ipp32f* pDst, int len))
IPPAPI(IppStatus, ippsConvert_24u32u,     (const Ipp8u*  pSrc, Ipp32u* pDst, int len))
IPPAPI(IppStatus, ippsConvert_24u32f,     (const Ipp8u*  pSrc, Ipp32f* pDst, int len))
IPPAPI(IppStatus, ippsConvert_32s16s,     (const Ipp32s* pSrc, Ipp16s* pDst, int len))
IPPAPI(IppStatus, ippsConvert_32s16s_Sfs, (const Ipp32s* pSrc, Ipp16s* pDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsConvert_32s24s_Sfs, (const Ipp32s* pSrc, Ipp8u*  pDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsConvert_32s32f,     (const Ipp32s* pSrc, Ipp32f* pDst, int len))
IPPAPI(IppStatus, ippsConvert_32s32f_Sfs, (const Ipp32s* pSrc, Ipp32f* pDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsConvert_32s64f,     (const Ipp32s* pSrc, Ipp64f* pDst, int len))
IPPAPI(IppStatus, ippsConvert_32s64f_Sfs, (const Ipp32s* pSrc, Ipp64f* pDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsConvert_32u24u_Sfs, (const Ipp32u* pSrc, Ipp8u*  pDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsConvert_64s32s_Sfs, (const Ipp64s* pSrc, Ipp32s* pDst, int len, IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippsConvert_64s64f,     (const Ipp64s* pSrc, Ipp64f* pDst, Ipp32u len))
IPPAPI(IppStatus, ippsConvert_16f16s_Sfs, (const Ipp16f* pSrc, Ipp16s* pDst, int len, IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippsConvert_16f32f,     (const Ipp16f* pSrc, Ipp32f* pDst, int len))
IPPAPI(IppStatus, ippsConvert_32f8s_Sfs,  (const Ipp32f* pSrc, Ipp8s*  pDst, int len, IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippsConvert_32f8u_Sfs,  (const Ipp32f* pSrc, Ipp8u*  pDst, int len, IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippsConvert_32f16s_Sfs, (const Ipp32f* pSrc, Ipp16s* pDst, int len, IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippsConvert_32f16u_Sfs, (const Ipp32f* pSrc, Ipp16u* pDst, int len, IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippsConvert_32f24s_Sfs, (const Ipp32f* pSrc, Ipp8u*  pDst, int len,int scaleFactor))
IPPAPI(IppStatus, ippsConvert_32f24u_Sfs, (const Ipp32f* pSrc, Ipp8u*  pDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsConvert_32f32s_Sfs, (const Ipp32f* pSrc, Ipp32s* pDst, int len, IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippsConvert_32f16f,     (const Ipp32f* pSrc, Ipp16f* pDst, int len, IppRoundMode rndMode))
IPPAPI(IppStatus, ippsConvert_32f64f,     (const Ipp32f* pSrc, Ipp64f* pDst, int len))
IPPAPI(IppStatus, ippsConvert_64f16s_Sfs, (const Ipp64f* pSrc, Ipp16s* pDst, int len, IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippsConvert_64f32s_Sfs, (const Ipp64f* pSrc, Ipp32s* pDst, int len, IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippsConvert_64f64s_Sfs, (const Ipp64f* pSrc, Ipp64s* pDst, Ipp32u len, IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippsConvert_64f32f,     (const Ipp64f* pSrc, Ipp32f* pDst, int len))
IPPAPI(IppStatus, ippsConvert_8s8u,       (const Ipp8s*  pSrc, Ipp8u*  pDst, int len))
IPPAPI(IppStatus, ippsConvert_8u8s_Sfs,   (const Ipp8u*  pSrc, Ipp8s*  pDst, int len, IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippsConvert_64f8s_Sfs,  (const Ipp64f* pSrc, Ipp8s*  pDst, int len, IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippsConvert_64f8u_Sfs,  (const Ipp64f* pSrc, Ipp8u*  pDst, int len, IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippsConvert_64f16u_Sfs, (const Ipp64f* pSrc, Ipp16u* pDst, int len, IppRoundMode rndMode, int scaleFactor))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:       ippsConj, ippsConjFlip, ippsConjCcs, ippsConjPerm, ippsConjPack
//  Purpose:     Complex conjugate input vector;
//               Ccs, Perm and Pack versions - in corresponding packed format
//  Parameters:
//    pSrc               Pointer to input complex vector
//    pDst               Pointer to output complex vector
//    len                Vectors' length in elements
//  Return:
//    ippStsNullPtrErr      One of pointers is NULL
//    ippStsSizeErr         Vectors' length is less than 1
//    ippStsNoErr           Otherwise
//  Notes:
//    ConjFlip version conjugates and stores result in reverse order
*/
IPPAPI(IppStatus, ippsConj_16sc_I,     (Ipp16sc* pSrcDst, int len))
IPPAPI(IppStatus, ippsConj_16sc,       (const Ipp16sc* pSrc, Ipp16sc* pDst, int len))
IPPAPI(IppStatus, ippsConj_32fc_I,     (Ipp32fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsConj_32fc,       (const Ipp32fc* pSrc, Ipp32fc* pDst, int len))
IPPAPI(IppStatus, ippsConj_64fc_I,     (Ipp64fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsConj_64fc,       (const Ipp64fc* pSrc, Ipp64fc* pDst, int len))
IPPAPI(IppStatus, ippsConjFlip_16sc,   (const Ipp16sc* pSrc, Ipp16sc* pDst, int len))
IPPAPI(IppStatus, ippsConjFlip_32fc,   (const Ipp32fc* pSrc, Ipp32fc* pDst, int len))
IPPAPI(IppStatus, ippsConjFlip_64fc,   (const Ipp64fc* pSrc, Ipp64fc* pDst, int len))
IPPAPI(IppStatus, ippsConjCcs_32fc_I,  (Ipp32fc* pSrcDst, int lenDst))
IPPAPI(IppStatus, ippsConjCcs_32fc,    (const Ipp32f* pSrc, Ipp32fc* pDst, int lenDst))
IPPAPI(IppStatus, ippsConjCcs_64fc_I,  (Ipp64fc* pSrcDst, int lenDst))
IPPAPI(IppStatus, ippsConjCcs_64fc,    (const Ipp64f* pSrc, Ipp64fc* pDst, int lenDst))
IPPAPI(IppStatus, ippsConjPack_32fc_I, (Ipp32fc* pSrcDst, int lenDst))
IPPAPI(IppStatus, ippsConjPack_32fc,   (const Ipp32f* pSrc, Ipp32fc* pDst, int lenDst))
IPPAPI(IppStatus, ippsConjPack_64fc_I, (Ipp64fc* pSrcDst, int lenDst))
IPPAPI(IppStatus, ippsConjPack_64fc,   (const Ipp64f* pSrc, Ipp64fc* pDst, int lenDst))
IPPAPI(IppStatus, ippsConjPerm_32fc_I, (Ipp32fc* pSrcDst, int lenDst))
IPPAPI(IppStatus, ippsConjPerm_32fc,   (const Ipp32f* pSrc, Ipp32fc* pDst, int lenDst))
IPPAPI(IppStatus, ippsConjPerm_64fc_I, (Ipp64fc* pSrcDst, int lenDst))
IPPAPI(IppStatus, ippsConjPerm_64fc,   (const Ipp64f* pSrc, Ipp64fc* pDst, int lenDst))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsMagnitude
//  Purpose:    compute magnitude of every complex element of the source
//  Parameters:
//   pSrcDst            pointer to the source/destination vector
//   pSrc               pointer to the source vector
//   pDst               pointer to the destination vector
//   len                length of the vector(s), number of items
//   scaleFactor        scale factor value
//  Return:
//   ippStsNullPtrErr      pointer(s) to data vector is NULL
//   ippStsSizeErr         length of a vector is less or equal 0
//   ippStsNoErr           otherwise
//  Notes:
//         dst = sqrt( src.re^2 + src.im^2 )
*/
IPPAPI(IppStatus, ippsMagnitude_16s_Sfs,  (const Ipp16s*  pSrcRe, const Ipp16s* pSrcIm, Ipp16s* pDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsMagnitude_16sc_Sfs, (const Ipp16sc* pSrc,                         Ipp16s* pDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsMagnitude_16s32f,   (const Ipp16s*  pSrcRe, const Ipp16s* pSrcIm, Ipp32f* pDst, int len))
IPPAPI(IppStatus, ippsMagnitude_16sc32f,  (const Ipp16sc* pSrc,                         Ipp32f* pDst, int len))
IPPAPI(IppStatus, ippsMagnitude_32sc_Sfs, (const Ipp32sc* pSrc,                         Ipp32s* pDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsMagnitude_32f,      (const Ipp32f*  pSrcRe, const Ipp32f* pSrcIm, Ipp32f* pDst, int len))
IPPAPI(IppStatus, ippsMagnitude_32fc,     (const Ipp32fc* pSrc,                         Ipp32f* pDst, int len))
IPPAPI(IppStatus, ippsMagnitude_64f,      (const Ipp64f*  pSrcRe, const Ipp64f* pSrcIm, Ipp64f* pDst, int len))
IPPAPI(IppStatus, ippsMagnitude_64fc,     (const Ipp64fc* pSrc,                         Ipp64f* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:
//    ippsPhase
//  Purpose:
//    Compute the phase (in radians) of complex vector elements.
//  Parameters:
//    pSrcRe    - an input complex vector
//    pDst      - an output vector to store the phase components;
//    len       - a length of the arrays.
//    scaleFactor   - a scale factor of output results (only for integer data)
//  Return:
//    ippStsNoErr               Ok
//    ippStsNullPtrErr          Some of pointers to input or output data are NULL
//    ippStsBadSizeErr          The length of the arrays is less or equal zero
*/
IPPAPI(IppStatus, ippsPhase_16sc_Sfs, (const Ipp16sc* pSrc, Ipp16s* pDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsPhase_16sc32f,  (const Ipp16sc* pSrc, Ipp32f* pDst, int len))
IPPAPI(IppStatus, ippsPhase_64fc,     (const Ipp64fc* pSrc, Ipp64f* pDst, int len))
IPPAPI(IppStatus, ippsPhase_32fc,     (const Ipp32fc* pSrc, Ipp32f* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:
//    ippsPhase_64f
//    ippsPhase_32f
//    ippsPhase_16s_Sfs
//    ippsPhase_16s32f
//  Purpose:
//    Compute the phase of complex data formed as two real vectors.
//  Parameters:
//    pSrcRe    - an input vector containing a real part of complex data
//    pSrcIm    - an input vector containing an imaginary part of complex data
//    pDst      - an output vector to store the phase components
//    len       - a length of the arrays.
//    scaleFactor   - a scale factor of output results (only for integer data)
//  Return:
//    ippStsNoErr               Ok
//    ippStsNullPtrErr          Some of pointers to input or output data are NULL
//    ippStsBadSizeErr          The length of the arrays is less or equal zero
*/
IPPAPI(IppStatus, ippsPhase_16s_Sfs, (const Ipp16s* pSrcRe, const Ipp16s* pSrcIm, Ipp16s* pDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsPhase_16s32f,  (const Ipp16s* pSrcRe, const Ipp16s* pSrcIm, Ipp32f* pDst, int len))
IPPAPI(IppStatus, ippsPhase_64f,     (const Ipp64f* pSrcRe, const Ipp64f* pSrcIm, Ipp64f* pDst, int len))
IPPAPI(IppStatus, ippsPhase_32f,     (const Ipp32f* pSrcRe, const Ipp32f* pSrcIm, Ipp32f* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:        ippsPowerSpectr
//  Purpose:      Compute the power spectrum of complex vector
//  Parameters:
//    pSr       - pointer to the complex input vector.
//    pSrcIm    - pointer to the image part of input vector.
//    pDst      - pointer to the result.
//    len       - vector length.
//    scaleFactor   - scale factor for rezult (only for integer data).
//  Return:
//   ippStsNullPtrErr  indicates that one or more pointers to the data is NULL.
//   ippStsSizeErr     indicates that vector length is less or equal zero.
//   ippStsNoErr       otherwise.
*/
IPPAPI(IppStatus, ippsPowerSpectr_16s_Sfs,(const Ipp16s* pSrcRe, const Ipp16s* pSrcIm, Ipp16s* pDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsPowerSpectr_16s32f, (const Ipp16s* pSrcRe, const Ipp16s* pSrcIm, Ipp32f* pDst, int len))
IPPAPI(IppStatus, ippsPowerSpectr_32f,    (const Ipp32f* pSrcRe, const Ipp32f* pSrcIm, Ipp32f* pDst, int len))
IPPAPI(IppStatus, ippsPowerSpectr_64f,    (const Ipp64f* pSrcRe, const Ipp64f* pSrcIm, Ipp64f* pDst, int len))

IPPAPI(IppStatus, ippsPowerSpectr_16sc_Sfs,(const Ipp16sc* pSrc, Ipp16s* pDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsPowerSpectr_16sc32f, (const Ipp16sc* pSrc, Ipp32f* pDst, int len))
IPPAPI(IppStatus, ippsPowerSpectr_32fc,    (const Ipp32fc* pSrc, Ipp32f* pDst, int len))
IPPAPI(IppStatus, ippsPowerSpectr_64fc,    (const Ipp64fc* pSrc, Ipp64f* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsReal
//  Purpose:    Extract real part of input complex vector
//  Parameters:
//    pSrc       Pointer to input complex vector
//    pDstRe     Pointer to output real vector
//    len        Vectors' length in elements
//  Return:
//    ippStsNullPtrErr       One of pointers is NULL
//    ippStsSizeErr          Vectors' length is less than 1
//    ippStsNoErr            Otherwise
*/
IPPAPI(IppStatus, ippsReal_64fc, (const Ipp64fc* pSrc, Ipp64f* pDstRe, int len))
IPPAPI(IppStatus, ippsReal_32fc, (const Ipp32fc* pSrc, Ipp32f* pDstRe, int len))
IPPAPI(IppStatus, ippsReal_16sc, (const Ipp16sc* pSrc, Ipp16s* pDstRe, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsImag
//  Purpose:    Extract imaginary part of input complex vector
//  Parameters:
//    pSrc       Pointer to input complex vector
//    pDstRe     Pointer to output imaginary vector
//    len        Vectors' length in elements
//  Return:
//    ippStsNullPtrErr       One of pointers is NULL
//    ippStsSizeErr          Vectors' length is less than 1
//    ippStsNoErr            Otherwise
*/
IPPAPI(IppStatus, ippsImag_64fc, (const Ipp64fc* pSrc, Ipp64f* pDstIm, int len))
IPPAPI(IppStatus, ippsImag_32fc, (const Ipp32fc* pSrc, Ipp32f* pDstIm, int len))
IPPAPI(IppStatus, ippsImag_16sc, (const Ipp16sc* pSrc, Ipp16s* pDstIm, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsRealToCplx
//  Purpose:    Compose complex vector from real and imaginary parts
//  Parameters:
//    pSrcRe     Pointer to input real vector, may be NULL
//    pSrcIm     Pointer to input imaginary vector, may be NULL
//    pDst       Pointer to output complex vector
//    len        Vectors' length in elements
//  Return:
//    ippStsNullPtrErr        Pointer to output vector is NULL, or both pointers
//                            to real and imaginary parts are NULL
//    ippStsSizeErr           Vectors' length is less than 1
//    ippStsNoErr             Otherwise
//
//  Notes:      One of two input pointers may be NULL. In this case
//              corresponding values of output complex elements are 0
*/
IPPAPI(IppStatus, ippsRealToCplx_64f, (const Ipp64f* pSrcRe, const Ipp64f* pSrcIm, Ipp64fc* pDst, int len))
IPPAPI(IppStatus, ippsRealToCplx_32f, (const Ipp32f* pSrcRe, const Ipp32f* pSrcIm, Ipp32fc* pDst, int len))
IPPAPI(IppStatus, ippsRealToCplx_16s, (const Ipp16s* pSrcRe, const Ipp16s* pSrcIm, Ipp16sc* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsCplxToReal
//  Purpose:    Extract real and imaginary parts of input complex vector
//  Parameters:
//    pSrc       Pointer to input complex vector
//    pDstRe     Pointer to output real vector
//    pDstIm     Pointer to output imaginary vector
//    len        Vectors' length in elements
//  Return:
//    ippStsNullPtrErr        One of pointers is NULL
//    ippStsSizeErr           Vectors' length is less than 1
//    ippStsNoErr             Otherwise
*/
IPPAPI(IppStatus, ippsCplxToReal_64fc, (const Ipp64fc* pSrc, Ipp64f* pDstRe, Ipp64f* pDstIm, int len))
IPPAPI(IppStatus, ippsCplxToReal_32fc, (const Ipp32fc* pSrc, Ipp32f* pDstRe, Ipp32f* pDstIm, int len))
IPPAPI(IppStatus, ippsCplxToReal_16sc, (const Ipp16sc* pSrc, Ipp16s* pDstRe, Ipp16s* pDstIm, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsThreshold
//  Purpose:    Performs threshold operation on vector's elements by limiting
//              element values by specified value.
//  Parameters:
//    level      Value used to limit each element of pSrc or pSrcDst.
//               This parameter must always be real. For complex versions,
//               it must be positive and represent magnitude
//    pSrcDst    Pointer to source and destination vector for in-place operation
//    pSrc       Pointer to input vector
//    pDst       Pointer to output vector
//    len        Number of elements in the vector
//    relOp      Values of this argument specify which relational operator
//               to use and whether level is an upper or lower bound for input.
//               relOp must have one of the following values:
//               - ippCmpLess specifies "less than" operator and level is lower bound
                 - ippCmpGreater specifies "greater than" operator and level is upper bound.
//  Return:
//    ippStsNullPtrErr          One of pointers is NULL
//    ippStsSizeErr             Vectors' length is less than 1
//    ippStsThreshNegLevelErr   Negative level value for complex operation
//    ippStsBadArgErr           relOp has invalid value
//    ippStsNoErr               No error
//  Notes:
//  real data
//    cmpLess    : pDst[n] = pSrc[n] < level ? level : pSrc[n];
//    cmpGreater : pDst[n] = pSrc[n] > level ? level : pSrc[n];
//  complex data
//    cmpLess    : pDst[n] = abs(pSrc[n]) < level ? pSrc[n]*k : pSrc[n];
//    cmpGreater : pDst[n] = abs(pSrc[n]) > level ? pSrc[n]*k : pSrc[n];
//    where k = level / abs(pSrc[n]);
*/

IPPAPI(IppStatus, ippsThreshold_16s_I,  (      Ipp16s*  pSrcDst,             int len, Ipp16s level, IppCmpOp relOp))
IPPAPI(IppStatus, ippsThreshold_16sc_I, (      Ipp16sc* pSrcDst,             int len, Ipp16s level, IppCmpOp relOp))
IPPAPI(IppStatus, ippsThreshold_32f_I,  (      Ipp32f*  pSrcDst,             int len, Ipp32f level, IppCmpOp relOp))
IPPAPI(IppStatus, ippsThreshold_32fc_I, (      Ipp32fc* pSrcDst,             int len, Ipp32f level, IppCmpOp relOp))
IPPAPI(IppStatus, ippsThreshold_64f_I,  (      Ipp64f*  pSrcDst,             int len, Ipp64f level, IppCmpOp relOp))
IPPAPI(IppStatus, ippsThreshold_64fc_I, (      Ipp64fc* pSrcDst,             int len, Ipp64f level, IppCmpOp relOp))
IPPAPI(IppStatus, ippsThreshold_16s,    (const Ipp16s*  pSrc, Ipp16s*  pDst, int len, Ipp16s level, IppCmpOp relOp))
IPPAPI(IppStatus, ippsThreshold_16sc,   (const Ipp16sc* pSrc, Ipp16sc* pDst, int len, Ipp16s level, IppCmpOp relOp))
IPPAPI(IppStatus, ippsThreshold_32f,    (const Ipp32f*  pSrc, Ipp32f*  pDst, int len, Ipp32f level, IppCmpOp relOp))
IPPAPI(IppStatus, ippsThreshold_32fc,   (const Ipp32fc* pSrc, Ipp32fc* pDst, int len, Ipp32f level, IppCmpOp relOp))
IPPAPI(IppStatus, ippsThreshold_64f,    (const Ipp64f*  pSrc, Ipp64f*  pDst, int len, Ipp64f level, IppCmpOp relOp))
IPPAPI(IppStatus, ippsThreshold_64fc,   (const Ipp64fc* pSrc, Ipp64fc* pDst, int len, Ipp64f level, IppCmpOp relOp))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsThreshold_LT, ippsThreshold_GT
//  Purpose:    Performs threshold operation on elements of vector by limiting
//              element values by specified value
//  Parameters:
//    level      Value used to limit each element of pSrc or pSrcDst.
//               This parameter must always be real. For complex versions,
//               it must be positive and represent magnitude
//    pSrcDst    Pointer to source and destination vector for in-place operation
//    pSrc       Pointer to input vector
//    pDst       Pointer to output vector
//    len        Number of elements in the vector
//  Return:
//    ippStsNullPtrErr          One of pointers is NULL
//    ippStsSizeErr             Vectors' length is less than 1
//    ippStsThreshNegLevelErr   Negative level value for complex operation
//    ippStsNoErr               No error
*/
IPPAPI(IppStatus, ippsThreshold_LT_16s_I,  (      Ipp16s*  pSrcDst,             int len, Ipp16s level))
IPPAPI(IppStatus, ippsThreshold_LT_16sc_I, (      Ipp16sc* pSrcDst,             int len, Ipp16s level))
IPPAPI(IppStatus, ippsThreshold_LT_32s_I,  (      Ipp32s*  pSrcDst,             int len, Ipp32s level))
IPPAPI(IppStatus, ippsThreshold_LT_32f_I,  (      Ipp32f*  pSrcDst,             int len, Ipp32f level))
IPPAPI(IppStatus, ippsThreshold_LT_32fc_I, (      Ipp32fc* pSrcDst,             int len, Ipp32f level))
IPPAPI(IppStatus, ippsThreshold_LT_64f_I,  (      Ipp64f*  pSrcDst,             int len, Ipp64f level))
IPPAPI(IppStatus, ippsThreshold_LT_64fc_I, (      Ipp64fc* pSrcDst,             int len, Ipp64f level))
IPPAPI(IppStatus, ippsThreshold_LT_16s,    (const Ipp16s*  pSrc, Ipp16s*  pDst, int len, Ipp16s level))
IPPAPI(IppStatus, ippsThreshold_LT_16sc,   (const Ipp16sc* pSrc, Ipp16sc* pDst, int len, Ipp16s level))
IPPAPI(IppStatus, ippsThreshold_LT_32s,    (const Ipp32s*  pSrc, Ipp32s*  pDst, int len, Ipp32s level))
IPPAPI(IppStatus, ippsThreshold_LT_32f,    (const Ipp32f*  pSrc, Ipp32f*  pDst, int len, Ipp32f level))
IPPAPI(IppStatus, ippsThreshold_LT_32fc,   (const Ipp32fc* pSrc, Ipp32fc* pDst, int len, Ipp32f level))
IPPAPI(IppStatus, ippsThreshold_LT_64f,    (const Ipp64f*  pSrc, Ipp64f*  pDst, int len, Ipp64f level))
IPPAPI(IppStatus, ippsThreshold_LT_64fc,   (const Ipp64fc* pSrc, Ipp64fc* pDst, int len, Ipp64f level))
IPPAPI(IppStatus, ippsThreshold_GT_16s_I,  (      Ipp16s*  pSrcDst,             int len, Ipp16s level))
IPPAPI(IppStatus, ippsThreshold_GT_16sc_I, (      Ipp16sc* pSrcDst,             int len, Ipp16s level))
IPPAPI(IppStatus, ippsThreshold_GT_32s_I,  (      Ipp32s*  pSrcDst,             int len, Ipp32s level))
IPPAPI(IppStatus, ippsThreshold_GT_32f_I,  (      Ipp32f*  pSrcDst,             int len, Ipp32f level))
IPPAPI(IppStatus, ippsThreshold_GT_32fc_I, (      Ipp32fc* pSrcDst,             int len, Ipp32f level))
IPPAPI(IppStatus, ippsThreshold_GT_64f_I,  (      Ipp64f*  pSrcDst,             int len, Ipp64f level))
IPPAPI(IppStatus, ippsThreshold_GT_64fc_I, (      Ipp64fc* pSrcDst,             int len, Ipp64f level))
IPPAPI(IppStatus, ippsThreshold_GT_16s,    (const Ipp16s*  pSrc, Ipp16s*  pDst, int len, Ipp16s level))
IPPAPI(IppStatus, ippsThreshold_GT_16sc,   (const Ipp16sc* pSrc, Ipp16sc* pDst, int len, Ipp16s level))
IPPAPI(IppStatus, ippsThreshold_GT_32s,    (const Ipp32s*  pSrc, Ipp32s*  pDst, int len, Ipp32s level))
IPPAPI(IppStatus, ippsThreshold_GT_32f,    (const Ipp32f*  pSrc, Ipp32f*  pDst, int len, Ipp32f level))
IPPAPI(IppStatus, ippsThreshold_GT_32fc,   (const Ipp32fc* pSrc, Ipp32fc* pDst, int len, Ipp32f level))
IPPAPI(IppStatus, ippsThreshold_GT_64f,    (const Ipp64f*  pSrc, Ipp64f*  pDst, int len, Ipp64f level))
IPPAPI(IppStatus, ippsThreshold_GT_64fc,   (const Ipp64fc* pSrc, Ipp64fc* pDst, int len, Ipp64f level))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsThreshold_LTAbs
//  Purpose:    Performs threshold operation on absolute values of elements of vector
//  Parameters:
//    level      Value used to limit each element of pSrc or pSrcDst.
//               This parameter must be positive
//    pSrcDst    Pointer to source and destination vector for in-place operation
//    pSrc       Pointer to input vector
//    pDst       Pointer to output vector
//    len        Number of elements in the vector
//  Return:
//    ippStsNullPtrErr          One of pointers is NULL
//    ippStsSizeErr             Vectors' length is less than 1
//    ippStsThreshNegLevelErr   Negative level value
//    ippStsNoErr               No error
*/
IPPAPI(IppStatus, ippsThreshold_LTAbs_16s,   (const Ipp16s* pSrc, Ipp16s *pDst, int len, Ipp16s level))
IPPAPI(IppStatus, ippsThreshold_LTAbs_32s,   (const Ipp32s* pSrc, Ipp32s *pDst, int len, Ipp32s level))
IPPAPI(IppStatus, ippsThreshold_LTAbs_32f,   (const Ipp32f* pSrc, Ipp32f *pDst, int len, Ipp32f level))
IPPAPI(IppStatus, ippsThreshold_LTAbs_64f,   (const Ipp64f* pSrc, Ipp64f *pDst, int len, Ipp64f level))
IPPAPI(IppStatus, ippsThreshold_LTAbs_16s_I, (      Ipp16s *pSrcDst,            int len, Ipp16s level))
IPPAPI(IppStatus, ippsThreshold_LTAbs_32s_I, (      Ipp32s *pSrcDst,            int len, Ipp32s level))
IPPAPI(IppStatus, ippsThreshold_LTAbs_32f_I, (      Ipp32f *pSrcDst,            int len, Ipp32f level))
IPPAPI(IppStatus, ippsThreshold_LTAbs_64f_I, (      Ipp64f *pSrcDst,            int len, Ipp64f level))
IPPAPI(IppStatus, ippsThreshold_GTAbs_16s,   (const Ipp16s* pSrc, Ipp16s *pDst, int len, Ipp16s level))
IPPAPI(IppStatus, ippsThreshold_GTAbs_32s,   (const Ipp32s* pSrc, Ipp32s *pDst, int len, Ipp32s level))
IPPAPI(IppStatus, ippsThreshold_GTAbs_32f,   (const Ipp32f* pSrc, Ipp32f *pDst, int len, Ipp32f level))
IPPAPI(IppStatus, ippsThreshold_GTAbs_64f,   (const Ipp64f* pSrc, Ipp64f *pDst, int len, Ipp64f level))
IPPAPI(IppStatus, ippsThreshold_GTAbs_16s_I, (      Ipp16s *pSrcDst,            int len, Ipp16s level))
IPPAPI(IppStatus, ippsThreshold_GTAbs_32s_I, (      Ipp32s *pSrcDst,            int len, Ipp32s level))
IPPAPI(IppStatus, ippsThreshold_GTAbs_32f_I, (      Ipp32f *pSrcDst,            int len, Ipp32f level))
IPPAPI(IppStatus, ippsThreshold_GTAbs_64f_I, (      Ipp64f *pSrcDst,            int len, Ipp64f level))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsThreshold_LTAbsVal
//  Purpose:    Performs threshold operation on absolute values of elements
//              of vector by limiting element values by specified level and
//              substituting with specified value:
//              if( ABS(x[i]) < level ) y[i] = value;
//              else y[i] = x[i];
//  Parameters:
//    level      Value used to limit each element of pSrc or pSrcDst. This argument
//               must always be positive
//    pSrcDst    Pointer to source and destination vector for in-place operation
//    pSrc       Pointer to input vector
//    pDst       Pointer to output vector
//    len        Number of elements in the vector
//    value      Value to be assigned to vector elements which are "less than"
//               by absolute value than level
//  Return:
//    ippStsNullPtrErr          One of pointers is NULL
//    ippStsSizeErr             Vectors' length is less than 1
//    ippStsThreshNegLevelErr   Negative level value
//    ippStsNoErr               No error
*/
IPPAPI(IppStatus, ippsThreshold_LTAbsVal_16s,   (const Ipp16s* pSrc, Ipp16s *pDst, int len, Ipp16s level, Ipp16s value))
IPPAPI(IppStatus, ippsThreshold_LTAbsVal_32s,   (const Ipp32s* pSrc, Ipp32s *pDst, int len, Ipp32s level, Ipp32s value))
IPPAPI(IppStatus, ippsThreshold_LTAbsVal_32f,   (const Ipp32f* pSrc, Ipp32f *pDst, int len, Ipp32f level, Ipp32f value))
IPPAPI(IppStatus, ippsThreshold_LTAbsVal_64f,   (const Ipp64f* pSrc, Ipp64f *pDst, int len, Ipp64f level, Ipp64f value))
IPPAPI(IppStatus, ippsThreshold_LTAbsVal_16s_I, (      Ipp16s *pSrcDst,            int len, Ipp16s level, Ipp16s value))
IPPAPI(IppStatus, ippsThreshold_LTAbsVal_32s_I, (      Ipp32s *pSrcDst,            int len, Ipp32s level, Ipp32s value))
IPPAPI(IppStatus, ippsThreshold_LTAbsVal_32f_I, (      Ipp32f *pSrcDst,            int len, Ipp32f level, Ipp32f value))
IPPAPI(IppStatus, ippsThreshold_LTAbsVal_64f_I, (      Ipp64f *pSrcDst,            int len, Ipp64f level, Ipp64f value))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsThreshold_LTVal, ippsThreshold_GTVal
//  Purpose:    Performs threshold operation on elements of vector by limiting
//              element values by specified level and substituting with
//              specified value
//  Parameters:
//    level      Value used to limit each element of pSrc or pSrcDst. This argument
//               must always be real. For complex versions, it must be positive and
//               represent magnitude
//    pSrcDst    Pointer to source and destination vector for in-place operation
//    pSrc       Pointer to input vector
//    pDst       Pointer to output vector
//    len        Number of elements in the vector
//    value      Value to be assigned to vector elements which are "less than" or
//               "greater than" level.
//  Return:
//    ippStsNullPtrErr          One of pointers is NULL
//    ippStsSizeErr             Vectors' length is less than 1
//    ippStsThreshNegLevelErr   Negative level value for complex operation
//    ippStsNoErr               No error
*/
IPPAPI(IppStatus, ippsThreshold_LTVal_16s_I,  (      Ipp16s*  pSrcDst,             int len, Ipp16s level, Ipp16s  value))
IPPAPI(IppStatus, ippsThreshold_LTVal_16sc_I, (      Ipp16sc* pSrcDst,             int len, Ipp16s level, Ipp16sc value))
IPPAPI(IppStatus, ippsThreshold_LTVal_32f_I,  (      Ipp32f*  pSrcDst,             int len, Ipp32f level, Ipp32f  value))
IPPAPI(IppStatus, ippsThreshold_LTVal_32fc_I, (      Ipp32fc* pSrcDst,             int len, Ipp32f level, Ipp32fc value))
IPPAPI(IppStatus, ippsThreshold_LTVal_64f_I,  (      Ipp64f*  pSrcDst,             int len, Ipp64f level, Ipp64f  value))
IPPAPI(IppStatus, ippsThreshold_LTVal_64fc_I, (      Ipp64fc* pSrcDst,             int len, Ipp64f level, Ipp64fc value))
IPPAPI(IppStatus, ippsThreshold_LTVal_16s,    (const Ipp16s*  pSrc, Ipp16s*  pDst, int len, Ipp16s level, Ipp16s  value))
IPPAPI(IppStatus, ippsThreshold_LTVal_16sc,   (const Ipp16sc* pSrc, Ipp16sc* pDst, int len, Ipp16s level, Ipp16sc value))
IPPAPI(IppStatus, ippsThreshold_LTVal_32f,    (const Ipp32f*  pSrc, Ipp32f*  pDst, int len, Ipp32f level, Ipp32f  value))
IPPAPI(IppStatus, ippsThreshold_LTVal_32fc,   (const Ipp32fc* pSrc, Ipp32fc* pDst, int len, Ipp32f level, Ipp32fc value))
IPPAPI(IppStatus, ippsThreshold_LTVal_64f,    (const Ipp64f*  pSrc, Ipp64f*  pDst, int len, Ipp64f level, Ipp64f  value))
IPPAPI(IppStatus, ippsThreshold_LTVal_64fc,   (const Ipp64fc* pSrc, Ipp64fc* pDst, int len, Ipp64f level, Ipp64fc value))
IPPAPI(IppStatus, ippsThreshold_GTVal_16s_I,  (      Ipp16s*  pSrcDst,             int len, Ipp16s level, Ipp16s  value))
IPPAPI(IppStatus, ippsThreshold_GTVal_16sc_I, (      Ipp16sc* pSrcDst,             int len, Ipp16s level, Ipp16sc value))
IPPAPI(IppStatus, ippsThreshold_GTVal_32f_I,  (      Ipp32f*  pSrcDst,             int len, Ipp32f level, Ipp32f  value))
IPPAPI(IppStatus, ippsThreshold_GTVal_32fc_I, (      Ipp32fc* pSrcDst,             int len, Ipp32f level, Ipp32fc value))
IPPAPI(IppStatus, ippsThreshold_GTVal_64f_I,  (      Ipp64f*  pSrcDst,             int len, Ipp64f level, Ipp64f  value))
IPPAPI(IppStatus, ippsThreshold_GTVal_64fc_I, (      Ipp64fc* pSrcDst,             int len, Ipp64f level, Ipp64fc value))
IPPAPI(IppStatus, ippsThreshold_GTVal_16s,    (const Ipp16s*  pSrc, Ipp16s*  pDst, int len, Ipp16s level, Ipp16s  value))
IPPAPI(IppStatus, ippsThreshold_GTVal_16sc,   (const Ipp16sc* pSrc, Ipp16sc* pDst, int len, Ipp16s level, Ipp16sc value))
IPPAPI(IppStatus, ippsThreshold_GTVal_32f,    (const Ipp32f*  pSrc, Ipp32f*  pDst, int len, Ipp32f level, Ipp32f  value))
IPPAPI(IppStatus, ippsThreshold_GTVal_32fc,   (const Ipp32fc* pSrc, Ipp32fc* pDst, int len, Ipp32f level, Ipp32fc value))
IPPAPI(IppStatus, ippsThreshold_GTVal_64f,    (const Ipp64f*  pSrc, Ipp64f*  pDst, int len, Ipp64f level, Ipp64f  value))
IPPAPI(IppStatus, ippsThreshold_GTVal_64fc,   (const Ipp64fc* pSrc, Ipp64fc* pDst, int len, Ipp64f level, Ipp64fc value))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsThreshold_LTValGTVal
//  Purpose:    Performs threshold operation on elements of vector by limiting
//              element values by specified level and substituting with
//              specified values for LT and GT cases respectively
//  Parameters:
//    levelLT    Value used to limit each element of pSrc or pSrcDst for "less than"
//    levelGT    Value used to limit each element of pSrc or pSrcDst for "greater than"
//    pSrcDst    Pointer to source and destination vector for in-place operation
//    pSrc       Pointer to input vector
//    pDst       Pointer to output vector
//    len        Number of elements in the vector
//    valueLT    Value to be assigned to vector elements which are "less than" levelLT
//    valueGT    Value to be assigned to vector elements which are "greater than" levelGT
//  Return:
//    ippStsNullPtrErr          One of pointers is NULL
//    ippStsSizeErr             Vectors' length is less than 1
//    ippStsThresholdErr        levelGT < levelLT
//    ippStsNoErr               No error
*/
IPPAPI(IppStatus, ippsThreshold_LTValGTVal_16s_I, (      Ipp16s* pSrcDst,            int len, Ipp16s levelLT, Ipp16s valueLT, Ipp16s levelGT, Ipp16s valueGT))
IPPAPI(IppStatus, ippsThreshold_LTValGTVal_16s,   (const Ipp16s* pSrc, Ipp16s* pDst, int len, Ipp16s levelLT, Ipp16s valueLT, Ipp16s levelGT, Ipp16s valueGT))
IPPAPI(IppStatus, ippsThreshold_LTValGTVal_32s_I, (      Ipp32s* pSrcDst,            int len, Ipp32s levelLT, Ipp32s valueLT, Ipp32s levelGT, Ipp32s valueGT))
IPPAPI(IppStatus, ippsThreshold_LTValGTVal_32s,   (const Ipp32s* pSrc, Ipp32s* pDst, int len, Ipp32s levelLT, Ipp32s valueLT, Ipp32s levelGT, Ipp32s valueGT))
IPPAPI(IppStatus, ippsThreshold_LTValGTVal_32f_I, (      Ipp32f* pSrcDst,            int len, Ipp32f levelLT, Ipp32f valueLT, Ipp32f levelGT, Ipp32f valueGT))
IPPAPI(IppStatus, ippsThreshold_LTValGTVal_32f,   (const Ipp32f* pSrc, Ipp32f* pDst, int len, Ipp32f levelLT, Ipp32f valueLT, Ipp32f levelGT, Ipp32f valueGT))
IPPAPI(IppStatus, ippsThreshold_LTValGTVal_64f_I, (      Ipp64f* pSrcDst,            int len, Ipp64f levelLT, Ipp64f valueLT, Ipp64f levelGT, Ipp64f valueGT))
IPPAPI(IppStatus, ippsThreshold_LTValGTVal_64f,   (const Ipp64f* pSrc, Ipp64f* pDst, int len, Ipp64f levelLT, Ipp64f valueLT, Ipp64f levelGT, Ipp64f valueGT))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsThresholdLTInv
//  Purpose:    Computes inverse of vector elements after limiting
//              their magnitudes by given lower bound
//    level      Value used to limit each element of pSrc or pSrcDst
//    pSrcDst    Pointer to source and destination vector for in-place operation
//    pSrc       Pointer to input vector
//    pDst       Pointer to output vector
//    len        Number of elements in the vector
//  Return:
//    ippStsNullPtrErr          One of pointers is NULL
//    ippStsSizeErr             Vectors' length is less than 1
//    ippStsThreshNegLevelErr   Negative level value
//    ippStsInvZero             level and source element values are zero
//    ippStsNoErr               No error
*/
IPPAPI(IppStatus, ippsThreshold_LTInv_32f_I,  (      Ipp32f*  pSrcDst,             int len, Ipp32f level))
IPPAPI(IppStatus, ippsThreshold_LTInv_32fc_I, (      Ipp32fc* pSrcDst,             int len, Ipp32f level))
IPPAPI(IppStatus, ippsThreshold_LTInv_64f_I,  (      Ipp64f*  pSrcDst,             int len, Ipp64f level))
IPPAPI(IppStatus, ippsThreshold_LTInv_64fc_I, (      Ipp64fc* pSrcDst,             int len, Ipp64f level))
IPPAPI(IppStatus, ippsThreshold_LTInv_32f,    (const Ipp32f*  pSrc, Ipp32f*  pDst, int len, Ipp32f level))
IPPAPI(IppStatus, ippsThreshold_LTInv_32fc,   (const Ipp32fc* pSrc, Ipp32fc* pDst, int len, Ipp32f level))
IPPAPI(IppStatus, ippsThreshold_LTInv_64f,    (const Ipp64f*  pSrc, Ipp64f*  pDst, int len, Ipp64f level))
IPPAPI(IppStatus, ippsThreshold_LTInv_64fc,   (const Ipp64fc* pSrc, Ipp64fc* pDst, int len, Ipp64f level))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsCartToPolar
//  Purpose:    Converts elements of complex vector to polar coordinate form
//  Parameters:
//    pSrc             Pointer to source vector
//    pSrcRe           Pointer to source vector which stores real components of
//                     Cartesian X,Y pairs
//    pSrcIm           Pointer to source vector which stores imaginary components
//                     of Cartesian X,Y pairs
//    pDstMagn         Pointer to vector which stores magnitude (radius)
//                     component of elements of vector pSrc
//    pDstPhase        Pointer to vector which stores phase (angle) component of
//                     elements of vector pSrc in radians. Phase values are in
//                     range (-Pi, Pi]
//    len              Number of elements in vector
//    magnScaleFactor  Integer scale factor for magnitude component
//    phaseScaleFactor Integer scale factor for phase component
//  Return:
//   ippStsNoErr           Indicates no error
//   ippStsNullPtrErr      At least one of specified pointers is NULL
//   ippStsSizeErr         Vectors' length is less than 1
*/
IPPAPI(IppStatus, ippsCartToPolar_32fc, (const Ipp32fc* pSrc,                        Ipp32f* pDstMagn, Ipp32f* pDstPhase, int len))
IPPAPI(IppStatus, ippsCartToPolar_64fc, (const Ipp64fc* pSrc,                        Ipp64f* pDstMagn, Ipp64f* pDstPhase, int len))
IPPAPI(IppStatus, ippsCartToPolar_32f,  (const Ipp32f* pSrcRe, const Ipp32f* pSrcIm, Ipp32f* pDstMagn, Ipp32f* pDstPhase, int len))
IPPAPI(IppStatus, ippsCartToPolar_64f,  (const Ipp64f* pSrcRe, const Ipp64f* pSrcIm, Ipp64f* pDstMagn, Ipp64f* pDstPhase, int len))

/*  Additional parameters for integer version:
//   magnScaleFactor   Scale factor for magnitude companents
//   phaseScaleFactor  Scale factor for phase companents
*/
IPPAPI(IppStatus, ippsCartToPolar_16sc_Sfs, (const Ipp16sc* pSrc, Ipp16s* pDstMagn, Ipp16s* pDstPhase, int len, int magnScaleFactor, int phaseScaleFactor))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsPolarToCart
//  Purpose:    Converts polar form magnitude/phase pairs stored
//              in input vectors to Cartesian coordinate form
//  Parameters:
//    pSrcMagn  Pointer to source vector which stores magnitude (radius)
//              components of elements in polar coordinate form
//    pSrcPhase Pointer to vector which stores phase (angle) components of
//              elements in polar coordinate form in radians
//    pDst      Pointer to  resulting vector which stores complex pairs in
//              Cartesian coordinates (X + iY)
//    pDstRe    Pointer to resulting vector which stores real components of
//              Cartesian X,Y pairs
//    pDstIm    Pointer to resulting vector which stores imaginary
//              components of Cartesian X,Y pairs
//    len       Number of elements in vectors
//  Return:
//   ippStsNoErr           Indicates no error
//   ippStsNullPtrErr      At least one of specified pointers is NULL
//   ippStsSizeErr         Vectors' length is less than 1
*/

IPPAPI(IppStatus, ippsPolarToCart_32fc, (const Ipp32f* pSrcMagn, const Ipp32f* pSrcPhase, Ipp32fc* pDst,                  int len))
IPPAPI(IppStatus, ippsPolarToCart_64fc, (const Ipp64f* pSrcMagn, const Ipp64f* pSrcPhase, Ipp64fc* pDst,                  int len))
IPPAPI(IppStatus, ippsPolarToCart_32f,  (const Ipp32f* pSrcMagn, const Ipp32f* pSrcPhase, Ipp32f* pDstRe, Ipp32f* pDstIm, int len))
IPPAPI(IppStatus, ippsPolarToCart_64f,  (const Ipp64f* pSrcMagn, const Ipp64f* pSrcPhase, Ipp64f* pDstRe, Ipp64f* pDstIm, int len))

/*  Additional parameters for integer version:
//   magnScaleFactor   Scale factor for magnitude companents
//   phaseScaleFactor  Scale factor for phase companents
*/
IPPAPI(IppStatus, ippsPolarToCart_16sc_Sfs, (const Ipp16s* pSrcMagn, const Ipp16s* pSrcPhase, Ipp16sc* pDst, int len, int magnScaleFactor, int phaseScaleFactor))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsFlip
//  Purpose:    dst[i] = src[len-i-1], i=0..len-1
//  Parameters:
//    pSrc      Pointer to input vector
//    pDst      Pointer to the output vector
//    pSrcDst   Pointer to source and destination vector for in-place operation
//    len       Vectors' length in elements
//  Return:
//    ippStsNullPtrErr        At least one pointer is NULL
//    ippStsSizeErr           Vectors' length is less than 1
//    ippStsNoErr             Otherwise
*/
IPPAPI(IppStatus, ippsFlip_8u,     (const Ipp8u*   pSrc, Ipp8u*   pDst, int len))
IPPAPI(IppStatus, ippsFlip_8u_I,   (      Ipp8u*   pSrcDst,             int len))
IPPAPI(IppStatus, ippsFlip_16u,    (const Ipp16u*  pSrc, Ipp16u*  pDst, int len))
IPPAPI(IppStatus, ippsFlip_16u_I,  (      Ipp16u*  pSrcDst,             int len))
IPPAPI(IppStatus, ippsFlip_32f,    (const Ipp32f*  pSrc, Ipp32f*  pDst, int len))
IPPAPI(IppStatus, ippsFlip_32f_I,  (      Ipp32f*  pSrcDst,             int len))
IPPAPI(IppStatus, ippsFlip_32fc,   (const Ipp32fc* pSrc, Ipp32fc* pDst, int len))
IPPAPI(IppStatus, ippsFlip_32fc_I, (      Ipp32fc* pSrcDst,             int len))
IPPAPI(IppStatus, ippsFlip_64f,    (const Ipp64f*  pSrc, Ipp64f*  pDst, int len))
IPPAPI(IppStatus, ippsFlip_64f_I,  (      Ipp64f*  pSrcDst,             int len))
IPPAPI(IppStatus, ippsFlip_64fc,   (const Ipp64fc* pSrc, Ipp64fc* pDst, int len))
IPPAPI(IppStatus, ippsFlip_64fc_I, (      Ipp64fc* pSrcDst,             int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippsFindNearestOne
//  Purpose:        Searches the table for an element closest to the reference value
//                  and returns its value and index
//  Context:
//  Returns:        IppStatus
//    ippStsNoErr        Ok
//    ippStsNullPtrErr   At least one of the specified pointers is NULL
//    ippStsSizeErr      The length of the table is less than or equal to zero
//  Parameters:
//    inpVal        reference Value
//    pOutVal       pointer to the found value
//    pOutIndx      pointer to the found index
//    pTable        table for search
//    tblLen        length of the table
//  Notes:
//                  The table should contain monotonically increasing values
*/
IPPAPI(IppStatus, ippsFindNearestOne_16u, (Ipp16u inpVal, Ipp16u* pOutVal, int* pOutIndex, const Ipp16u *pTable, int tblLen))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippsFindNearest
//  Purpose:        Searches the table for elements closest to the reference values
//                  and the their indexes
//  Context:
//  Returns:        IppStatus
//    ippStsNoErr        Ok
//    ippStsNullPtrErr   At least one of the specified pointers is NULL
//    ippStsSizeErr      The length of table or pVals is less than or equal to zero
//  Parameters:
//    pVals         pointer to the reference values vector
//    pOutVals      pointer to the vector with the found values
//    pOutIndexes   pointer to the array with indexes of the found elements
//    len           length of the input vector
//    pTable        table for search
//    tblLen        length of the table
//  Notes:
//                  The table should contain monotonically increasing values
*/
IPPAPI(IppStatus, ippsFindNearest_16u, (const Ipp16u* pVals, Ipp16u* pOutVals, int* pOutIndexes, int len, const Ipp16u *pTable, int tblLen))

/* /////////////////////////////////////////////////////////////////////////////
//                  Windowing functions
//  Note: to create the window coefficients you have to make two calls
//        Set(1,x,n) and Win(x,n)
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Names:            ippsWinBartlett
//  Parameters:
//   pSrcDst          pointer to the vector
//   len              length of the vector, window size
//  Return:
//   ippStsNullPtrErr    pointer to the vector is NULL
//   ippStsSizeErr       length of the vector is less 3
//   ippStsNoErr         otherwise
*/
IPPAPI(IppStatus, ippsWinBartlett_16s_I, (                     Ipp16s* pSrcDst,  int len))
IPPAPI(IppStatus, ippsWinBartlett_16s,   (const Ipp16s*  pSrc, Ipp16s* pDst,     int len))
IPPAPI(IppStatus, ippsWinBartlett_16sc_I,(                     Ipp16sc* pSrcDst, int len))
IPPAPI(IppStatus, ippsWinBartlett_16sc,  (const Ipp16sc* pSrc, Ipp16sc* pDst,    int len))
IPPAPI(IppStatus, ippsWinBartlett_32f_I, (                     Ipp32f* pSrcDst,  int len))
IPPAPI(IppStatus, ippsWinBartlett_32f,   (const Ipp32f*  pSrc, Ipp32f* pDst,     int len))
IPPAPI(IppStatus, ippsWinBartlett_32fc_I,(                     Ipp32fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsWinBartlett_32fc,  (const Ipp32fc* pSrc, Ipp32fc* pDst,    int len))
IPPAPI(IppStatus, ippsWinBartlett_64f_I, (                     Ipp64f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsWinBartlett_64f,   (const Ipp64f*  pSrc, Ipp64f*  pDst,    int len))
IPPAPI(IppStatus, ippsWinBartlett_64fc_I,(                     Ipp64fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsWinBartlett_64fc,  (const Ipp64fc* pSrc, Ipp64fc* pDst,    int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:            ippsWinHann
//  Parameters:
//   pSrcDst          pointer to the vector
//   len              length of the vector, window size
//  Return:
//   ippStsNullPtrErr    pointer to the vector is NULL
//   ippStsSizeErr       length of the vector is less 3
//   ippStsNoErr         otherwise
//  Functionality:    0.5*(1-cos(2*pi*n/(N-1)))
*/
IPPAPI(IppStatus, ippsWinHann_16s_I, (                     Ipp16s* pSrcDst,  int len))
IPPAPI(IppStatus, ippsWinHann_16s,   (const Ipp16s* pSrc,  Ipp16s* pDst,     int len))
IPPAPI(IppStatus, ippsWinHann_16sc_I,(                     Ipp16sc* pSrcDst, int len))
IPPAPI(IppStatus, ippsWinHann_16sc,  (const Ipp16sc* pSrc, Ipp16sc* pDst,    int len))
IPPAPI(IppStatus, ippsWinHann_32f_I, (                     Ipp32f* pSrcDst,  int len))
IPPAPI(IppStatus, ippsWinHann_32f,   (const Ipp32f* pSrc,  Ipp32f* pDst,     int len))
IPPAPI(IppStatus, ippsWinHann_32fc_I,(                     Ipp32fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsWinHann_32fc,  (const Ipp32fc* pSrc, Ipp32fc* pDst,    int len))
IPPAPI(IppStatus, ippsWinHann_64f_I, (                     Ipp64f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsWinHann_64f,   (const Ipp64f*  pSrc, Ipp64f*  pDst,    int len))
IPPAPI(IppStatus, ippsWinHann_64fc_I,(                     Ipp64fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsWinHann_64fc,  (const Ipp64fc* pSrc, Ipp64fc* pDst,    int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:            ippsWinHamming
//  Parameters:
//   pSrcDst          pointer to the vector
//   len              length of the vector, window size
//  Return:
//   ippStsNullPtrErr    pointer to the vector is NULL
//   ippStsSizeErr       length of the vector is less 3
//   ippStsNoErr         otherwise
*/
IPPAPI(IppStatus, ippsWinHamming_16s_I, (                     Ipp16s*  pSrcDst, int len))
IPPAPI(IppStatus, ippsWinHamming_16s,   (const Ipp16s* pSrc,  Ipp16s*  pDst,    int len))
IPPAPI(IppStatus, ippsWinHamming_16sc_I,(                     Ipp16sc* pSrcDst, int len))
IPPAPI(IppStatus, ippsWinHamming_16sc,  (const Ipp16sc* pSrc, Ipp16sc* pDst,    int len))
IPPAPI(IppStatus, ippsWinHamming_32f_I, (                     Ipp32f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsWinHamming_32f,   (const Ipp32f* pSrc,  Ipp32f*  pDst,    int len))
IPPAPI(IppStatus, ippsWinHamming_32fc_I,(                     Ipp32fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsWinHamming_32fc,  (const Ipp32fc* pSrc, Ipp32fc* pDst,    int len))
IPPAPI(IppStatus, ippsWinHamming_64f_I, (                     Ipp64f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsWinHamming_64f,   (const Ipp64f*  pSrc, Ipp64f*  pDst,    int len))
IPPAPI(IppStatus, ippsWinHamming_64fc_I,(                     Ipp64fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsWinHamming_64fc,  (const Ipp64fc* pSrc, Ipp64fc* pDst,    int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:            ippsWinBlackman
//  Purpose:          multiply vector by Blackman windowing function
//  Parameters:
//   pSrcDst          pointer to the vector
//   len              length of the vector, window size
//   alpha            adjustable parameter associated with the
//                    Blackman windowing equation
//   alphaQ15         scaled (scale factor 15) version of the alpha
//   scaleFactor      scale factor of the output signal
//  Return:
//   ippStsNullPtrErr    pointer to the vector is NULL
//   ippStsSizeErr       length of the vector is less 3, for Opt it's 4
//   ippStsNoErr         otherwise
//  Notes:
//     parameter alpha value
//         WinBlackmaStd   : -0.16
//         WinBlackmaOpt   : -0.5 / (1+cos(2*pi/(len-1)))
*/
IPPAPI(IppStatus, ippsWinBlackman_16s_I,  (                     Ipp16s*  pSrcDst, int len, Ipp32f alpha))
IPPAPI(IppStatus, ippsWinBlackman_16s,    (const Ipp16s*  pSrc, Ipp16s*  pDst,    int len, Ipp32f alpha))
IPPAPI(IppStatus, ippsWinBlackman_16sc_I, (                     Ipp16sc* pSrcDst, int len, Ipp32f alpha))
IPPAPI(IppStatus, ippsWinBlackman_16sc,   (const Ipp16sc* pSrc, Ipp16sc* pDst,    int len, Ipp32f alpha))
IPPAPI(IppStatus, ippsWinBlackman_32f_I,  (                     Ipp32f*  pSrcDst, int len, Ipp32f alpha))
IPPAPI(IppStatus, ippsWinBlackman_32f,    (const Ipp32f* pSrc,  Ipp32f*  pDst,    int len, Ipp32f alpha))
IPPAPI(IppStatus, ippsWinBlackman_32fc_I, (                     Ipp32fc* pSrcDst, int len, Ipp32f alpha))
IPPAPI(IppStatus, ippsWinBlackman_32fc,   (const Ipp32fc* pSrc, Ipp32fc* pDst,    int len, Ipp32f alpha))
IPPAPI(IppStatus, ippsWinBlackman_64f_I,  (                     Ipp64f*  pSrcDst, int len, Ipp64f alpha))
IPPAPI(IppStatus, ippsWinBlackman_64f,    (const Ipp64f*  pSrc, Ipp64f*  pDst,    int len, Ipp64f alpha))
IPPAPI(IppStatus, ippsWinBlackman_64fc_I, (                     Ipp64fc* pSrcDst, int len, Ipp64f alpha))
IPPAPI(IppStatus, ippsWinBlackman_64fc,   (const Ipp64fc* pSrc, Ipp64fc* pDst,    int len, Ipp64f alpha))

IPPAPI(IppStatus, ippsWinBlackmanStd_16s_I, (                     Ipp16s*  pSrcDst, int len))
IPPAPI(IppStatus, ippsWinBlackmanStd_16s,   (const Ipp16s*  pSrc, Ipp16s*  pDst,    int len))
IPPAPI(IppStatus, ippsWinBlackmanStd_16sc_I,(                     Ipp16sc* pSrcDst, int len))
IPPAPI(IppStatus, ippsWinBlackmanStd_16sc,  (const Ipp16sc* pSrc, Ipp16sc* pDst,    int len))
IPPAPI(IppStatus, ippsWinBlackmanStd_32f_I, (                     Ipp32f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsWinBlackmanStd_32f,   (const Ipp32f*  pSrc, Ipp32f*  pDst,    int len))
IPPAPI(IppStatus, ippsWinBlackmanStd_32fc_I,(                     Ipp32fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsWinBlackmanStd_32fc,  (const Ipp32fc* pSrc, Ipp32fc* pDst,    int len))
IPPAPI(IppStatus, ippsWinBlackmanStd_64f_I, (                     Ipp64f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsWinBlackmanStd_64f,   (const Ipp64f*  pSrc, Ipp64f*  pDst,    int len))
IPPAPI(IppStatus, ippsWinBlackmanStd_64fc_I,(                     Ipp64fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsWinBlackmanStd_64fc, (const Ipp64fc* pSrc,  Ipp64fc* pDst,    int len))

IPPAPI(IppStatus, ippsWinBlackmanOpt_16s_I, (                     Ipp16s*  pSrcDst, int len))
IPPAPI(IppStatus, ippsWinBlackmanOpt_16s,   (const Ipp16s*  pSrc, Ipp16s*  pDst,    int len))
IPPAPI(IppStatus, ippsWinBlackmanOpt_16sc_I,(                     Ipp16sc* pSrcDst, int len))
IPPAPI(IppStatus, ippsWinBlackmanOpt_16sc,  (const Ipp16sc* pSrc, Ipp16sc* pDst,    int len))
IPPAPI(IppStatus, ippsWinBlackmanOpt_32f_I, (                     Ipp32f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsWinBlackmanOpt_32f,   (const Ipp32f*  pSrc, Ipp32f*  pDst,    int len))
IPPAPI(IppStatus, ippsWinBlackmanOpt_32fc_I,(                     Ipp32fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsWinBlackmanOpt_32fc,  (const Ipp32fc* pSrc, Ipp32fc* pDst,    int len))
IPPAPI(IppStatus, ippsWinBlackmanOpt_64f_I, (                     Ipp64f*  pSrcDst, int len))
IPPAPI(IppStatus, ippsWinBlackmanOpt_64f,   (const Ipp64f*  pSrc, Ipp64f*  pDst,    int len))
IPPAPI(IppStatus, ippsWinBlackmanOpt_64fc_I,(                     Ipp64fc* pSrcDst, int len))
IPPAPI(IppStatus, ippsWinBlackmanOpt_64fc,  (const Ipp64fc* pSrc, Ipp64fc* pDst,    int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:            ippsWinKaiser
//  Purpose:          multiply vector by Kaiser windowing function
//  Parameters:
//   pSrcDst          pointer to the vector
//   len              length of the vector, window size
//   alpha            adjustable parameter associated with the
//                    Kaiser windowing equation
//   alphaQ15         scaled (scale factor 15) version of the alpha
//  Return:
//   ippStsNullPtrErr    pointer to the vector is NULL
//   ippStsSizeErr       length of the vector is less 1
//   ippStsHugeWinErr    window in function is huge
//   ippStsNoErr         otherwise
*/
IPPAPI(IppStatus, ippsWinKaiser_16s_I, (                     Ipp16s*  pSrcDst, int len, Ipp32f alpha))
IPPAPI(IppStatus, ippsWinKaiser_16s,   (const Ipp16s*  pSrc, Ipp16s*  pDst,    int len, Ipp32f alpha))
IPPAPI(IppStatus, ippsWinKaiser_16sc_I,(                     Ipp16sc* pSrcDst, int len, Ipp32f alpha))
IPPAPI(IppStatus, ippsWinKaiser_16sc,  (const Ipp16sc* pSrc, Ipp16sc* pDst,    int len, Ipp32f alpha))
IPPAPI(IppStatus, ippsWinKaiser_32f_I, (                     Ipp32f*  pSrcDst, int len, Ipp32f alpha))
IPPAPI(IppStatus, ippsWinKaiser_32f,   (const Ipp32f*  pSrc, Ipp32f*  pDst,    int len, Ipp32f alpha))
IPPAPI(IppStatus, ippsWinKaiser_32fc_I,(                     Ipp32fc* pSrcDst, int len, Ipp32f alpha))
IPPAPI(IppStatus, ippsWinKaiser_32fc,  (const Ipp32fc* pSrc, Ipp32fc* pDst,    int len, Ipp32f alpha))
IPPAPI(IppStatus, ippsWinKaiser_64f_I, (                     Ipp64f*  pSrcDst, int len, Ipp64f alpha))
IPPAPI(IppStatus, ippsWinKaiser_64f,   (const Ipp64f*  pSrc, Ipp64f*  pDst,    int len, Ipp64f alpha))
IPPAPI(IppStatus, ippsWinKaiser_64fc_I,(                     Ipp64fc* pSrcDst, int len, Ipp64f alpha))
IPPAPI(IppStatus, ippsWinKaiser_64fc,  (const Ipp64fc* pSrc, Ipp64fc* pDst,    int len, Ipp64f alpha))

/* /////////////////////////////////////////////////////////////////////////////
//                  Statistical functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsSum
//  Purpose:    sum all elements of the source vector
//  Parameters:
//   pSrc                pointer to the source vector
//   pSum                pointer to the result
//   len                 length of the vector
//   scaleFactor         scale factor value
//  Return:
//   ippStsNullPtrErr       pointer to the vector or result is NULL
//   ippStsSizeErr          length of the vector is less or equal 0
//   ippStsNoErr            otherwise
*/
IPPAPI(IppStatus, ippsSum_16s_Sfs,     (const Ipp16s*  pSrc, int len, Ipp16s*  pSum, int scaleFactor))
IPPAPI(IppStatus, ippsSum_16sc_Sfs,    (const Ipp16sc* pSrc, int len, Ipp16sc* pSum, int scaleFactor))
IPPAPI(IppStatus, ippsSum_16s32s_Sfs,  (const Ipp16s*  pSrc, int len, Ipp32s*  pSum, int scaleFactor))
IPPAPI(IppStatus, ippsSum_16sc32sc_Sfs,(const Ipp16sc* pSrc, int len, Ipp32sc* pSum, int scaleFactor))
IPPAPI(IppStatus, ippsSum_32s_Sfs,     (const Ipp32s*  pSrc, int len, Ipp32s*  pSum, int scaleFactor))
IPPAPI(IppStatus, ippsSum_32f,         (const Ipp32f*  pSrc, int len, Ipp32f*  pSum, IppHintAlgorithm hint))
IPPAPI(IppStatus, ippsSum_32fc,        (const Ipp32fc* pSrc, int len, Ipp32fc* pSum, IppHintAlgorithm hint))
IPPAPI(IppStatus, ippsSum_64f,         (const Ipp64f*  pSrc, int len, Ipp64f*  pSum))
IPPAPI(IppStatus, ippsSum_64fc,        (const Ipp64fc* pSrc, int len, Ipp64fc* pSum))

/* /////////////////////////////////////////////////////////////////////////////
// Names:      ippsMin, ippsMax, ippsMinMax
// Purpose:    Find minimum/maximum value among all elements of the source vector
// Parameters:
//    pSrc     - Pointer to the source vector.
//    len      - Length of the vector.
//    pMax     - Pointer to the result.
//    pMin     - Pointer to the result.
// Returns:
//    ippStsNoErr       - OK.
//    ippStsNullPtrErr  - Error when any of the specified pointers is NULL.
//    ippStsSizeErr     - Error when length of the vector is less or equal 0.
*/
IPPAPI(IppStatus, ippsMin_16s, (const Ipp16s* pSrc, int len, Ipp16s* pMin))
IPPAPI(IppStatus, ippsMin_32s, (const Ipp32s* pSrc, int len, Ipp32s* pMin))
IPPAPI(IppStatus, ippsMin_32f, (const Ipp32f* pSrc, int len, Ipp32f* pMin))
IPPAPI(IppStatus, ippsMin_64f, (const Ipp64f* pSrc, int len, Ipp64f* pMin))

IPPAPI(IppStatus, ippsMax_16s, (const Ipp16s* pSrc, int len, Ipp16s* pMax))
IPPAPI(IppStatus, ippsMax_32s, (const Ipp32s* pSrc, int len, Ipp32s* pMax))
IPPAPI(IppStatus, ippsMax_32f, (const Ipp32f* pSrc, int len, Ipp32f* pMax))
IPPAPI(IppStatus, ippsMax_64f, (const Ipp64f* pSrc, int len, Ipp64f* pMax))

IPPAPI(IppStatus, ippsMinMax_8u,  (const Ipp8u*  pSrc, int len, Ipp8u*  pMin, Ipp8u*  pMax))
IPPAPI(IppStatus, ippsMinMax_16u, (const Ipp16u* pSrc, int len, Ipp16u* pMin, Ipp16u* pMax))
IPPAPI(IppStatus, ippsMinMax_16s, (const Ipp16s* pSrc, int len, Ipp16s* pMin, Ipp16s* pMax))
IPPAPI(IppStatus, ippsMinMax_32u, (const Ipp32u* pSrc, int len, Ipp32u* pMin, Ipp32u* pMax))
IPPAPI(IppStatus, ippsMinMax_32s, (const Ipp32s* pSrc, int len, Ipp32s* pMin, Ipp32s* pMax))
IPPAPI(IppStatus, ippsMinMax_32f, (const Ipp32f* pSrc, int len, Ipp32f* pMin, Ipp32f* pMax))
IPPAPI(IppStatus, ippsMinMax_64f, (const Ipp64f* pSrc, int len, Ipp64f* pMin, Ipp64f* pMax))

/* /////////////////////////////////////////////////////////////////////////////
// Names:      ippsMinAbs, ippsMaxAbs
// Purpose:    Returns the minimum/maximum absolute value of a vector.
// Parameters:
//    pSrc     - Pointer to the source vector.
//    len      - Length of the vector.
//    pMinAbs  - Pointer to the result.
//    pMaxAbs  - Pointer to the result.
// Returns:
//    ippStsNoErr       - OK.
//    ippStsNullPtrErr  - Error when any of the specified pointers is NULL.
//    ippStsSizeErr     - Error when length of the vector is less or equal 0.
*/
IPPAPI(IppStatus, ippsMinAbs_16s, (const Ipp16s* pSrc, int len, Ipp16s* pMinAbs))
IPPAPI(IppStatus, ippsMinAbs_32s, (const Ipp32s* pSrc, int len, Ipp32s* pMinAbs))
IPPAPI(IppStatus, ippsMinAbs_32f, (const Ipp32f* pSrc, int len, Ipp32f* pMinAbs))
IPPAPI(IppStatus, ippsMinAbs_64f, (const Ipp64f* pSrc, int len, Ipp64f* pMinAbs))

IPPAPI(IppStatus, ippsMaxAbs_16s, (const Ipp16s* pSrc, int len, Ipp16s* pMaxAbs))
IPPAPI(IppStatus, ippsMaxAbs_32s, (const Ipp32s* pSrc, int len, Ipp32s* pMaxAbs))
IPPAPI(IppStatus, ippsMaxAbs_32f, (const Ipp32f* pSrc, int len, Ipp32f* pMaxAbs))
IPPAPI(IppStatus, ippsMaxAbs_64f, (const Ipp64f* pSrc, int len, Ipp64f* pMaxAbs))

/* /////////////////////////////////////////////////////////////////////////////
// Names:      ippsMinIndx, ippsMaxIndx
// Purpose:    Find element with min/max value and return the value and the index.
// Parameters:
//    pSrc     - Pointer to the input vector.
//    len      - Length of the vector.
//    pMin     - Pointer to min value found.
//    pMax     - Pointer to max value found.
//    pIndx    - Pointer to index of the first min/max value, may be NULL.
//    pMinIndx - Pointer to index of the first minimum value.
//    pMaxIndx - Pointer to index of the first maximum value.
// Returns:
//    ippStsNoErr       - OK.
//    ippStsNullPtrErr  - Error when any of the specified pointers is NULL.
//    ippStsSizeErr     - Error when length of the vector is less or equal 0.
*/
IPPAPI(IppStatus, ippsMinIndx_16s, (const Ipp16s* pSrc, int len, Ipp16s* pMin, int* pIndx))
IPPAPI(IppStatus, ippsMinIndx_32s, (const Ipp32s* pSrc, int len, Ipp32s* pMin, int* pIndx))
IPPAPI(IppStatus, ippsMinIndx_32f, (const Ipp32f* pSrc, int len, Ipp32f* pMin, int* pIndx))
IPPAPI(IppStatus, ippsMinIndx_64f, (const Ipp64f* pSrc, int len, Ipp64f* pMin, int* pIndx))

IPPAPI(IppStatus, ippsMaxIndx_16s, (const Ipp16s* pSrc, int len, Ipp16s* pMax, int* pIndx))
IPPAPI(IppStatus, ippsMaxIndx_32s, (const Ipp32s* pSrc, int len, Ipp32s* pMax, int* pIndx))
IPPAPI(IppStatus, ippsMaxIndx_32f, (const Ipp32f* pSrc, int len, Ipp32f* pMax, int* pIndx))
IPPAPI(IppStatus, ippsMaxIndx_64f, (const Ipp64f* pSrc, int len, Ipp64f* pMax, int* pIndx))

IPPAPI(IppStatus, ippsMinMaxIndx_8u,  (const Ipp8u*  pSrc, int len, Ipp8u*  pMin, int* pMinIndx, Ipp8u*  pMax, int* pMaxIndx))
IPPAPI(IppStatus, ippsMinMaxIndx_16u, (const Ipp16u* pSrc, int len, Ipp16u* pMin, int* pMinIndx, Ipp16u* pMax, int* pMaxIndx))
IPPAPI(IppStatus, ippsMinMaxIndx_16s, (const Ipp16s* pSrc, int len, Ipp16s* pMin, int* pMinIndx, Ipp16s* pMax, int* pMaxIndx))
IPPAPI(IppStatus, ippsMinMaxIndx_32u, (const Ipp32u* pSrc, int len, Ipp32u* pMin, int* pMinIndx, Ipp32u* pMax, int* pMaxIndx))
IPPAPI(IppStatus, ippsMinMaxIndx_32s, (const Ipp32s* pSrc, int len, Ipp32s* pMin, int* pMinIndx, Ipp32s* pMax, int* pMaxIndx))
IPPAPI(IppStatus, ippsMinMaxIndx_32f, (const Ipp32f* pSrc, int len, Ipp32f* pMin, int* pMinIndx, Ipp32f* pMax, int* pMaxIndx))
IPPAPI(IppStatus, ippsMinMaxIndx_64f, (const Ipp64f* pSrc, int len, Ipp64f* pMin, int* pMinIndx, Ipp64f* pMax, int* pMaxIndx))

/* /////////////////////////////////////////////////////////////////////////////
// Names:      ippsMinAbsIndx, ippsMaxAbsIndx
// Purpose:    Returns the min/max absolute value of a vector and the index of the corresponding element.
// Parameters:
//    pSrc     - Pointer to the input vector.
//    len      - Length of the vector.
//    pMinAbs  - Pointer to the min absolute value found.
//    pMaxAbs  - Pointer to the max absolute value found.
//    pMinIndx - Pointer to index of the first minimum absolute value.
//    pMaxIndx - Pointer to index of the first maximum absolute value.
// Returns:
//    ippStsNoErr       - OK.
//    ippStsNullPtrErr  - Error when any of the specified pointers is NULL.
//    ippStsSizeErr     - Error when length of the vector is less or equal 0.
*/
IPPAPI(IppStatus, ippsMinAbsIndx_16s, (const Ipp16s* pSrc, int len, Ipp16s* pMinAbs, int* pIndx))
IPPAPI(IppStatus, ippsMinAbsIndx_32s, (const Ipp32s* pSrc, int len, Ipp32s* pMinAbs, int* pIndx))
IPPAPI(IppStatus, ippsMinAbsIndx_32f, (const Ipp32f* pSrc, int len, Ipp32f* pMinAbs, int* pIndx))
IPPAPI(IppStatus, ippsMinAbsIndx_64f, (const Ipp64f* pSrc, int len, Ipp64f* pMinAbs, int* pIndx))

IPPAPI(IppStatus, ippsMaxAbsIndx_16s, (const Ipp16s* pSrc, int len, Ipp16s* pMaxAbs, int* pIndx))
IPPAPI(IppStatus, ippsMaxAbsIndx_32s, (const Ipp32s* pSrc, int len, Ipp32s* pMaxAbs, int* pIndx))
IPPAPI(IppStatus, ippsMaxAbsIndx_32f, (const Ipp32f* pSrc, int len, Ipp32f* pMaxAbs, int* pIndx))
IPPAPI(IppStatus, ippsMaxAbsIndx_64f, (const Ipp64f* pSrc, int len, Ipp64f* pMaxAbs, int* pIndx))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsMean
//  Purpose:    compute average value of all elements of the source vector
//  Parameters:
//   pSrc                pointer to the source vector
//   pMean               pointer to the result
//   len                 length of the source vector
//   scaleFactor         scale factor value
//  Return:
//   ippStsNullPtrErr       pointer(s) to the vector or the result is NULL
//   ippStsSizeErr          length of the vector is less or equal 0
//   ippStsNoErr            otherwise
*/
IPPAPI(IppStatus, ippsMean_16s_Sfs, (const Ipp16s*  pSrc, int len, Ipp16s*  pMean, int scaleFactor))
IPPAPI(IppStatus, ippsMean_16sc_Sfs,(const Ipp16sc* pSrc, int len, Ipp16sc* pMean, int scaleFactor))
IPPAPI(IppStatus, ippsMean_32s_Sfs, (const Ipp32s*  pSrc, int len, Ipp32s*  pMean, int scaleFactor))
IPPAPI(IppStatus, ippsMean_32f,     (const Ipp32f*  pSrc, int len, Ipp32f*  pMean, IppHintAlgorithm hint))
IPPAPI(IppStatus, ippsMean_32fc,    (const Ipp32fc* pSrc, int len, Ipp32fc* pMean, IppHintAlgorithm hint))
IPPAPI(IppStatus, ippsMean_64f,     (const Ipp64f*  pSrc, int len, Ipp64f*  pMean))
IPPAPI(IppStatus, ippsMean_64fc,    (const Ipp64fc* pSrc, int len, Ipp64fc* pMean))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsStdDev
//  Purpose:    compute standard deviation value of all elements of the vector
//  Parameters:
//   pSrc               pointer to the vector
//   len                length of the vector
//   pStdDev            pointer to the result
//   scaleFactor        scale factor value
//  Return:
//   ippStsNoErr           Ok
//   ippStsNullPtrErr      pointer to the vector or the result is NULL
//   ippStsSizeErr         length of the vector is less than 2
//  Functionality:
//         std = sqrt( sum( (x[n] - mean(x))^2, n=0..len-1 ) / (len-1) )
*/
IPPAPI(IppStatus, ippsStdDev_16s_Sfs,   (const Ipp16s* pSrc, int len, Ipp16s* pStdDev, int scaleFactor))
IPPAPI(IppStatus, ippsStdDev_16s32s_Sfs,(const Ipp16s* pSrc, int len, Ipp32s* pStdDev, int scaleFactor))
IPPAPI(IppStatus, ippsStdDev_32f,       (const Ipp32f* pSrc, int len, Ipp32f* pStdDev, IppHintAlgorithm hint))
IPPAPI(IppStatus, ippsStdDev_64f,       (const Ipp64f* pSrc, int len, Ipp64f* pStdDev))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsMeanStdDev
//  Purpose:    compute standard deviation value and mean value
//              of all elements of the vector
//  Parameters:
//   pSrc               pointer to the vector
//   len                length of the vector
//   pStdDev            pointer to the result
//   pMean              pointer to the result
//   scaleFactor        scale factor value
//  Return:
//   ippStsNoErr           Ok
//   ippStsNullPtrErr      pointer to the vector or the result is NULL
//   ippStsSizeErr         length of the vector is less than 2
//  Functionality:
//         std = sqrt( sum( (x[n] - mean(x))^2, n=0..len-1 ) / (len-1) )
*/
IPPAPI(IppStatus, ippsMeanStdDev_16s_Sfs,   (const Ipp16s* pSrc, int len, Ipp16s* pMean, Ipp16s* pStdDev, int scaleFactor))
IPPAPI(IppStatus, ippsMeanStdDev_16s32s_Sfs,(const Ipp16s* pSrc, int len, Ipp32s* pMean, Ipp32s* pStdDev, int scaleFactor))
IPPAPI(IppStatus, ippsMeanStdDev_32f,       (const Ipp32f* pSrc, int len, Ipp32f* pMean, Ipp32f* pStdDev, IppHintAlgorithm hint))
IPPAPI(IppStatus, ippsMeanStdDev_64f,       (const Ipp64f* pSrc, int len, Ipp64f* pMean, Ipp64f* pStdDev))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:            ippsNorm
//  Purpose:         calculate norm of vector
//     Inf   - calculate C-norm of vector:  n = MAX |src1|
//     L1    - calculate L1-norm of vector: n = SUM |src1|
//     L2    - calculate L2-norm of vector: n = SQRT(SUM |src1|^2)
//     L2Sqr - calculate L2-norm of vector: n = SUM |src1|^2
//  Parameters:
//    pSrc           source data pointer
//    len            length of vector
//    pNorm          pointer to result
//    scaleFactor    scale factor value
//  Returns:
//    ippStsNoErr       Ok
//    ippStsNullPtrErr  Some of pointers to input or output data are NULL
//    ippStsSizeErr     The length of vector is less or equal zero
//  Notes:
*/
IPPAPI(IppStatus, ippsNorm_Inf_16s32s_Sfs,  (const Ipp16s*  pSrc, int len, Ipp32s* pNorm, int scaleFactor))
IPPAPI(IppStatus, ippsNorm_Inf_16s32f,      (const Ipp16s*  pSrc, int len, Ipp32f* pNorm))
IPPAPI(IppStatus, ippsNorm_Inf_32f,         (const Ipp32f*  pSrc, int len, Ipp32f* pNorm))
IPPAPI(IppStatus, ippsNorm_Inf_32fc32f,     (const Ipp32fc* pSrc, int len, Ipp32f* pNorm))
IPPAPI(IppStatus, ippsNorm_Inf_64f,         (const Ipp64f*  pSrc, int len, Ipp64f* pNorm))
IPPAPI(IppStatus, ippsNorm_Inf_64fc64f,     (const Ipp64fc* pSrc, int len, Ipp64f* pNorm))

IPPAPI(IppStatus, ippsNorm_L1_16s32s_Sfs,   (const Ipp16s*  pSrc, int len, Ipp32s* pNorm, int scaleFactor))
IPPAPI(IppStatus, ippsNorm_L1_16s64s_Sfs,   (const Ipp16s*  pSrc, int len, Ipp64s* pNorm, int scaleFactor))
IPPAPI(IppStatus, ippsNorm_L1_16s32f,       (const Ipp16s*  pSrc, int len, Ipp32f* pNorm))
IPPAPI(IppStatus, ippsNorm_L1_32f,          (const Ipp32f*  pSrc, int len, Ipp32f* pNorm))
IPPAPI(IppStatus, ippsNorm_L1_32fc64f,      (const Ipp32fc* pSrc, int len, Ipp64f* pNorm))
IPPAPI(IppStatus, ippsNorm_L1_64f,          (const Ipp64f*  pSrc, int len, Ipp64f* pNorm))
IPPAPI(IppStatus, ippsNorm_L1_64fc64f,      (const Ipp64fc* pSrc, int len, Ipp64f* pNorm))

IPPAPI(IppStatus, ippsNorm_L2_16s32s_Sfs,   (const Ipp16s*  pSrc, int len, Ipp32s* pNorm, int scaleFactor))
IPPAPI(IppStatus, ippsNorm_L2_16s32f,       (const Ipp16s*  pSrc, int len, Ipp32f* pNorm))
IPPAPI(IppStatus, ippsNorm_L2_32f,          (const Ipp32f*  pSrc, int len, Ipp32f* pNorm))
IPPAPI(IppStatus, ippsNorm_L2_32fc64f,      (const Ipp32fc* pSrc, int len, Ipp64f* pNorm))
IPPAPI(IppStatus, ippsNorm_L2_64f,          (const Ipp64f*  pSrc, int len, Ipp64f* pNorm))
IPPAPI(IppStatus, ippsNorm_L2_64fc64f,      (const Ipp64fc* pSrc, int len, Ipp64f* pNorm))
IPPAPI(IppStatus, ippsNorm_L2Sqr_16s64s_Sfs,(const Ipp16s*  pSrc, int len, Ipp64s* pNorm, int scaleFactor))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:            ippsNormDiff
//  Purpose:         calculate norm of vectors
//     Inf   - calculate C-norm of vectors:  n = MAX |src1-src2|
//     L1    - calculate L1-norm of vectors: n = SUM |src1-src2|
//     L2    - calculate L2-norm of vectors: n = SQRT(SUM |src1-src2|^2)
//     L2Sqr - calculate L2-norm of vectors: n = SUM |src1-src2|^2
//  Parameters:
//    pSrc1, pSrc2   source data pointers
//    len            length of vector
//    pNorm          pointer to result
//    scaleFactor    scale factor value
//  Returns:
//    ippStsNoErr       Ok
//    ippStsNullPtrErr  Some of pointers to input or output data are NULL
//    ippStsSizeErr     The length of vector is less or equal zero
//  Notes:
*/
IPPAPI(IppStatus, ippsNormDiff_Inf_16s32s_Sfs,  (const Ipp16s*  pSrc1, const Ipp16s*  pSrc2, int len, Ipp32s* pNorm, int scaleFactor))
IPPAPI(IppStatus, ippsNormDiff_Inf_16s32f,      (const Ipp16s*  pSrc1, const Ipp16s*  pSrc2, int len, Ipp32f* pNorm))
IPPAPI(IppStatus, ippsNormDiff_Inf_32f,         (const Ipp32f*  pSrc1, const Ipp32f*  pSrc2, int len, Ipp32f* pNorm))
IPPAPI(IppStatus, ippsNormDiff_Inf_32fc32f,     (const Ipp32fc* pSrc1, const Ipp32fc* pSrc2, int len, Ipp32f* pNorm))
IPPAPI(IppStatus, ippsNormDiff_Inf_64f,         (const Ipp64f*  pSrc1, const Ipp64f*  pSrc2, int len, Ipp64f* pNorm))
IPPAPI(IppStatus, ippsNormDiff_Inf_64fc64f,     (const Ipp64fc* pSrc1, const Ipp64fc* pSrc2, int len, Ipp64f* pNorm))

IPPAPI(IppStatus, ippsNormDiff_L1_16s32s_Sfs,   (const Ipp16s*  pSrc1, const Ipp16s*  pSrc2, int len, Ipp32s* pNorm, int scaleFactor))
IPPAPI(IppStatus, ippsNormDiff_L1_16s64s_Sfs,   (const Ipp16s*  pSrc1, const Ipp16s*  pSrc2, int len, Ipp64s* pNorm, int scaleFactor))
IPPAPI(IppStatus, ippsNormDiff_L1_16s32f,       (const Ipp16s*  pSrc1, const Ipp16s*  pSrc2, int len, Ipp32f* pNorm))
IPPAPI(IppStatus, ippsNormDiff_L1_32f,          (const Ipp32f*  pSrc1, const Ipp32f*  pSrc2, int len, Ipp32f* pNorm))
IPPAPI(IppStatus, ippsNormDiff_L1_32fc64f,      (const Ipp32fc* pSrc1, const Ipp32fc* pSrc2, int len, Ipp64f* pNorm))
IPPAPI(IppStatus, ippsNormDiff_L1_64f,          (const Ipp64f*  pSrc1, const Ipp64f*  pSrc2, int len, Ipp64f* pNorm))
IPPAPI(IppStatus, ippsNormDiff_L1_64fc64f,      (const Ipp64fc* pSrc1, const Ipp64fc* pSrc2, int len, Ipp64f* pNorm))

IPPAPI(IppStatus, ippsNormDiff_L2_16s32s_Sfs,   (const Ipp16s*  pSrc1, const Ipp16s*  pSrc2, int len, Ipp32s* pNorm, int scaleFactor))
IPPAPI(IppStatus, ippsNormDiff_L2_16s32f,       (const Ipp16s*  pSrc1, const Ipp16s*  pSrc2, int len, Ipp32f* pNorm))
IPPAPI(IppStatus, ippsNormDiff_L2_32f,          (const Ipp32f*  pSrc1, const Ipp32f*  pSrc2, int len, Ipp32f* pNorm))
IPPAPI(IppStatus, ippsNormDiff_L2_32fc64f,      (const Ipp32fc* pSrc1, const Ipp32fc* pSrc2, int len, Ipp64f* pNorm))
IPPAPI(IppStatus, ippsNormDiff_L2_64f,          (const Ipp64f*  pSrc1, const Ipp64f*  pSrc2, int len, Ipp64f* pNorm))
IPPAPI(IppStatus, ippsNormDiff_L2_64fc64f,      (const Ipp64fc* pSrc1, const Ipp64fc* pSrc2, int len, Ipp64f* pNorm))
IPPAPI(IppStatus, ippsNormDiff_L2Sqr_16s64s_Sfs,(const Ipp16s*  pSrc1, const Ipp16s*  pSrc2, int len, Ipp64s* pNorm, int scaleFactor))

/* /////////////////////////////////////////////////////////////////////////////
//                  Dot Product Functions
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDotProd
//  Purpose:    compute Dot Product value
//  Arguments:
//     pSrc1               pointer to the source vector
//     pSrc2               pointer to the another source vector
//     len                 vector's length, number of items
//     pDp                 pointer to the result
//     scaleFactor         scale factor value
//  Return:
//     ippStsNullPtrErr       pointer(s) pSrc pDst is NULL
//     ippStsSizeErr          length of the vectors is less or equal 0
//     ippStsNoErr            otherwise
//  Notes:
//     the functions don't conjugate one of the source vectors
*/
IPPAPI(IppStatus, ippsDotProd_16s32s_Sfs,   (const Ipp16s*  pSrc1, const Ipp16s*  pSrc2, int len, Ipp32s*  pDp, int scaleFactor))
IPPAPI(IppStatus, ippsDotProd_16s64s,       (const Ipp16s*  pSrc1, const Ipp16s*  pSrc2, int len, Ipp64s*  pDp))
IPPAPI(IppStatus, ippsDotProd_16sc64sc,     (const Ipp16sc* pSrc1, const Ipp16sc* pSrc2, int len, Ipp64sc* pDp))
IPPAPI(IppStatus, ippsDotProd_16s16sc64sc,  (const Ipp16s*  pSrc1, const Ipp16sc* pSrc2, int len, Ipp64sc* pDp))
IPPAPI(IppStatus, ippsDotProd_16s32s32s_Sfs,(const Ipp16s*  pSrc1, const Ipp32s*  pSrc2, int len, Ipp32s*  pDp, int scaleFactor))
IPPAPI(IppStatus, ippsDotProd_16s32f,       (const Ipp16s*  pSrc1, const Ipp16s*  pSrc2, int len, Ipp32f*  pDp))
IPPAPI(IppStatus, ippsDotProd_32s_Sfs,      (const Ipp32s*  pSrc1, const Ipp32s*  pSrc2, int len, Ipp32s*  pDp, int scaleFactor))
IPPAPI(IppStatus, ippsDotProd_32f,          (const Ipp32f*  pSrc1, const Ipp32f*  pSrc2, int len, Ipp32f*  pDp))
IPPAPI(IppStatus, ippsDotProd_32fc,         (const Ipp32fc* pSrc1, const Ipp32fc* pSrc2, int len, Ipp32fc* pDp))
IPPAPI(IppStatus, ippsDotProd_32f32fc,      (const Ipp32f*  pSrc1, const Ipp32fc* pSrc2, int len, Ipp32fc* pDp))
IPPAPI(IppStatus, ippsDotProd_32f32fc64fc,  (const Ipp32f*  pSrc1, const Ipp32fc* pSrc2, int len, Ipp64fc* pDp))
IPPAPI(IppStatus, ippsDotProd_32f64f,       (const Ipp32f*  pSrc1, const Ipp32f*  pSrc2, int len, Ipp64f*  pDp))
IPPAPI(IppStatus, ippsDotProd_32fc64fc,     (const Ipp32fc* pSrc1, const Ipp32fc* pSrc2, int len, Ipp64fc* pDp))
IPPAPI(IppStatus, ippsDotProd_64f,          (const Ipp64f*  pSrc1, const Ipp64f*  pSrc2, int len, Ipp64f*  pDp))
IPPAPI(IppStatus, ippsDotProd_64fc,         (const Ipp64fc* pSrc1, const Ipp64fc* pSrc2, int len, Ipp64fc* pDp))
IPPAPI(IppStatus, ippsDotProd_64f64fc,      (const Ipp64f*  pSrc1, const Ipp64fc* pSrc2, int len, Ipp64fc* pDp))

/* ////////////////////////////////////////////////////////////////////////////
// Names:      ippsMinEvery, ippsMaxEvery
// Purpose:    Calculation min/max value for every element of two vectors.
// Parameters:
//    pSrc     - Pointer to the first input vector.
//    pSrcDst  - Pointer to the second input vector which stores the result.
//    pSrc1    - Pointer to the first input vector.
//    pSrc2    - Pointer to the second input vector.
//    pDst     - Pointer to the destination vector.
//    len      - Length of the vector.
// Returns:
//    ippStsNoErr       - OK.
//    ippStsNullPtrErr  - Error when any of the specified pointers is NULL.
//    ippStsSizeErr     - Error when length of the vector is less or equal 0.
*/
IPPAPI(IppStatus, ippsMinEvery_8u_I,  (const Ipp8u*  pSrc, Ipp8u*  pSrcDst, int len))
IPPAPI(IppStatus, ippsMinEvery_16u_I, (const Ipp16u* pSrc, Ipp16u* pSrcDst, int len))
IPPAPI(IppStatus, ippsMinEvery_16s_I, (const Ipp16s* pSrc, Ipp16s* pSrcDst, int len))
IPPAPI(IppStatus, ippsMinEvery_32s_I, (const Ipp32s* pSrc, Ipp32s* pSrcDst, int len))
IPPAPI(IppStatus, ippsMinEvery_32f_I, (const Ipp32f* pSrc, Ipp32f* pSrcDst, int len))
IPPAPI(IppStatus, ippsMinEvery_64f_I, (const Ipp64f* pSrc, Ipp64f* pSrcDst, Ipp32u len))

IPPAPI(IppStatus, ippsMinEvery_8u,  (const Ipp8u*  pSrc1, const Ipp8u*  pSrc2, Ipp8u*  pDst, Ipp32u len))
IPPAPI(IppStatus, ippsMinEvery_16u, (const Ipp16u* pSrc1, const Ipp16u* pSrc2, Ipp16u* pDst, Ipp32u len))
IPPAPI(IppStatus, ippsMinEvery_32f, (const Ipp32f* pSrc1, const Ipp32f* pSrc2, Ipp32f* pDst, Ipp32u len))
IPPAPI(IppStatus, ippsMinEvery_64f, (const Ipp64f* pSrc1, const Ipp64f* pSrc2, Ipp64f* pDst, Ipp32u len))

IPPAPI(IppStatus, ippsMaxEvery_8u_I,  (const Ipp8u*  pSrc, Ipp8u*  pSrcDst, int len))
IPPAPI(IppStatus, ippsMaxEvery_16u_I, (const Ipp16u* pSrc, Ipp16u* pSrcDst, int len))
IPPAPI(IppStatus, ippsMaxEvery_16s_I, (const Ipp16s* pSrc, Ipp16s* pSrcDst, int len))
IPPAPI(IppStatus, ippsMaxEvery_32s_I, (const Ipp32s* pSrc, Ipp32s* pSrcDst, int len))
IPPAPI(IppStatus, ippsMaxEvery_32f_I, (const Ipp32f* pSrc, Ipp32f* pSrcDst, int len))
IPPAPI(IppStatus, ippsMaxEvery_64f_I, (const Ipp64f* pSrc, Ipp64f* pSrcDst, Ipp32u len))

IPPAPI(IppStatus, ippsMaxEvery_8u,  (const Ipp8u*  pSrc1, const Ipp8u*  pSrc2, Ipp8u*  pDst, Ipp32u len))
IPPAPI(IppStatus, ippsMaxEvery_16u, (const Ipp16u* pSrc1, const Ipp16u* pSrc2, Ipp16u* pDst, Ipp32u len))
IPPAPI(IppStatus, ippsMaxEvery_32f, (const Ipp32f* pSrc1, const Ipp32f* pSrc2, Ipp32f* pDst, Ipp32u len))
IPPAPI(IppStatus, ippsMaxEvery_64f, (const Ipp64f* pSrc1, const Ipp64f* pSrc2, Ipp64f* pDst, Ipp32u len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:
//      ippsMaxOrder
//  Purpose:
//     Determines the maximal number of binary digits for data representation.
//  Parameters:
//    pSrc     The pointer on input signal vector.
//    pOrder   Pointer to result value.
//    len      The  length of  the input vector.
//  Return:
//    ippStsNoErr         Ok
//    ippStsNullPtrErr    Some of pointers to input or output data are NULL
//    ippStsSizeErr       The length of the arrays is less or equal zero
//    ippStsNanArg        If not a number is met in a input value
*/
IPPAPI(IppStatus, ippsMaxOrder_16s, (const Ipp16s* pSrc, int len, int* pOrder))
IPPAPI(IppStatus, ippsMaxOrder_32s, (const Ipp32s* pSrc, int len, int* pOrder))
IPPAPI(IppStatus, ippsMaxOrder_32f, (const Ipp32f* pSrc, int len, int* pOrder))
IPPAPI(IppStatus, ippsMaxOrder_64f, (const Ipp64f* pSrc, int len, int* pOrder))

/* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Name:  ippsCountInRange_32s
//  Purpose: Computes the number of vector elements falling within the specified range.
//  Return:
//     ippStsNoErr       No errors, it's OK
//     ippStsNullPtrErr  Either pSrc or pCounts equals to zero.
//     ippStsLengthErr   The vector's length is less than or equals to zero.
//  Arguments:
//     pSrc              A pointer to the source vector.
//     len               Number of the vector elements.
//     pCounts           A pointer to the output result.
//     lowerBound        The upper boundary of the range.
//     uppreBound        The lower boundary of the range.
*/
IPPAPI(IppStatus, ippsCountInRange_32s, (const Ipp32s* pSrc, int len, int* pCounts, Ipp32s lowerBound, Ipp32s upperBound))

/* ///////////////////////////////////////////////////////////////////////////
//  Name:              ippsZeroCrossing
//  Purpose:           Counts the zero-cross measure for the input signal.
//
//  Parameters:
//    pSrc             Pointer to the input signal [len].
//    len              Number of elements in the input signal.
//    pValZCR          Pointer to the result value.
//    zcType           Zero crossing measure type.
//  Return:
//    ippStsNoErr      Indicates no error.
//    ippStsNullPtrErr Indicates an error when the pSrc or pRes pointer is null.
//    ippStsRangeErr   Indicates an error when zcType is not equal to
//                     ippZCR, ippZCXor or ippZCC
*/
IPPAPI(IppStatus, ippsZeroCrossing_16s32f, (const Ipp16s* pSrc, Ipp32u len, Ipp32f* pValZCR, IppsZCType zcType))
IPPAPI(IppStatus, ippsZeroCrossing_32f,    (const Ipp32f* pSrc, Ipp32u len, Ipp32f* pValZCR, IppsZCType zcType))

/* /////////////////////////////////////////////////////////////////////////////
//                  Sampling functions
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsSampleUp
//  Purpose:    upsampling, i.e. expansion of input vector to get output vector
//              by simple adding zeroes between input elements
//  Parameters:
//   pSrc   (in)    pointer to the input vector
//   pDst   (in)    pointer to the output vector
//   srcLen (in)    length of input vector
//   pDstLen (out)  pointer to the length of output vector
//   factor (in)    the number of output elements, corresponding to one element
//                  of input vector.
//   pPhase(in-out) pointer to value, that is the position (0, ..., factor-1) of
//                  element from input vector in the group of factor elements of
//                  output vector. Out value is ready to continue upsampling with
//                  the same factor (out = in).
//
//  Return:
//   ippStsNullPtrErr        one or several pointers pSrc, pDst, pDstLen or pPhase
//                           is NULL
//   ippStsSizeErr           length of input vector is less or equal zero
//   ippStsSampleFactorErr   factor <= 0
//   ippStsSamplePhaseErr    *pPhase < 0 or *pPhase >= factor
//   ippStsNoErr             otherwise
*/
IPPAPI(IppStatus, ippsSampleUp_16s,  (const Ipp16s*  pSrc, int  srcLen, Ipp16s*  pDst, int* pDstLen, int factor, int* pPhase))
IPPAPI(IppStatus, ippsSampleUp_16sc, (const Ipp16sc* pSrc, int  srcLen, Ipp16sc* pDst, int* pDstLen, int factor, int* pPhase))
IPPAPI(IppStatus, ippsSampleUp_32f,  (const Ipp32f*  pSrc, int  srcLen, Ipp32f*  pDst, int* pDstLen, int factor, int* pPhase))
IPPAPI(IppStatus, ippsSampleUp_32fc, (const Ipp32fc* pSrc, int  srcLen, Ipp32fc* pDst, int* pDstLen, int factor, int* pPhase))
IPPAPI(IppStatus, ippsSampleUp_64f,  (const Ipp64f*  pSrc, int  srcLen, Ipp64f*  pDst, int* pDstLen, int factor, int* pPhase))
IPPAPI(IppStatus, ippsSampleUp_64fc, (const Ipp64fc* pSrc, int  srcLen, Ipp64fc* pDst, int* pDstLen, int factor, int* pPhase))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsSampleDown
//  Purpose:    subsampling, i.e. only one of "factor" elements of input vector
//              are placed to output vector
//  Parameters:
//   pSrc   (in)    pointer to the input vector
//   pDst   (in)    pointer to the output vector
//   srcLen (in)    length of input vector
//   pDstLen (out)  pointer to the length of output vector
//   factor (in)    the number of input elements, corresponding to one element
//                  of output vector.
//   pPhase(in-out) pointer to value, that is the position (0, ..., factor-1) of
//                  chosen element in the group of "factor" elements. Out value
//                  of *pPhase is ready to continue subsampling with the same
//                  factor.
//
//  Return:
//   ippStsNullPtrErr        one or several pointers pSrc, pDst, pDstLen or pPhase
//                        is NULL
//   ippStsSizeErr           length of input vector is less or equal zero
//   ippStsSampleFactorErr   factor <= 0
//   ippStsSamplePhaseErr    *pPhase < 0 or *pPhase >=factor
//   ippStsNoErr             otherwise
*/
IPPAPI(IppStatus, ippsSampleDown_16s,  (const Ipp16s*  pSrc, int  srcLen, Ipp16s*  pDst, int* pDstLen, int factor, int* pPhase))
IPPAPI(IppStatus, ippsSampleDown_16sc, (const Ipp16sc* pSrc, int  srcLen, Ipp16sc* pDst, int* pDstLen, int factor, int* pPhase))
IPPAPI(IppStatus, ippsSampleDown_32f,  (const Ipp32f*  pSrc, int  srcLen, Ipp32f*  pDst, int* pDstLen, int factor, int* pPhase))
IPPAPI(IppStatus, ippsSampleDown_32fc, (const Ipp32fc* pSrc, int  srcLen, Ipp32fc* pDst, int* pDstLen, int factor, int* pPhase))
IPPAPI(IppStatus, ippsSampleDown_64f,  (const Ipp64f*  pSrc, int  srcLen, Ipp64f*  pDst, int* pDstLen, int factor, int* pPhase))
IPPAPI(IppStatus, ippsSampleDown_64fc, (const Ipp64fc* pSrc, int  srcLen, Ipp64fc* pDst, int* pDstLen, int factor, int* pPhase))

/* /////////////////////////////////////////////////////////////////////////////
//                  Filtering
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//                AutoCorrelation Functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Names:  ippsAutoCorrNormGetBufferSize
//
//  Purpose:     : Get the size (in bytes) of the buffer for ippsAutoCorrNorm's internal calculations.
//
//  Parameters:
//     srcLen      - Source vector length.
//     dstLen      - Length of auto-correlation.
//     dataType    - Data type for auto corelation {Ipp32f|Ipp32fc|Ipp64f|Ipp64fc}.
//     algType     - Selector for the algorithm type.  Possible values are the results of
//                   composition of the IppAlgType and IppsNormOp values.
//     pBufferSize - Pointer to the calculated buffer size (in bytes).
//  Return:
//   ippStsNoErr       - OK.
//   ippStsNullPtrErr  - pBufferSize is NULL.
//   ippStsSizeErr     - Vector's length is not positive.
//   ippStsDataTypeErr - Unsupported data type.
//   ippStsAlgTypeErr  - Unsupported algorithm or normalization type.
*/
IPPAPI(IppStatus, ippsAutoCorrNormGetBufferSize, (int srcLen, int dstLen, IppDataType dataType, IppEnum algType, int* pBufferSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsAutoCorrNorm
//  Purpose:    Calculate the auto-correlation,
//              ippNormNone specifies the normal auto-correlation.
//              ippNormA specifies the biased auto-correlation
//              (the resulting values are divided by srcLen).
//              ippNormB specifies the unbiased auto-correlation
//              (the resulting values are divided by ( srcLen - n ),
//              where "n" indicates current iteration).
//  Parameters:
//     pSrc    - Pointer to the source vector.
//     srcLen  - Source vector length.
//     pDst    - Pointer to the auto-correlation result vector.
//     dstLen  - Length of auto-correlation.
//     algType - Selector for the algorithm type. Possible values are the results
//               of composition of the  IppAlgType and IppsNormOp values.
//     pBuffer - Pointer to the buffer for internal calculations.
//  Return:
//   ippStsNoErr      - OK.
//   ippStsNullPtrErr - One of the pointers is NULL.
//   ippStsSizeErr    - Vector's length is not positive.
//   ippStsAlgTypeErr - Unsupported algorithm or normalization type.
*/
IPPAPI(IppStatus, ippsAutoCorrNorm_32f, (const Ipp32f*  pSrc, int srcLen, Ipp32f*  pDst, int dstLen, IppEnum algType, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsAutoCorrNorm_64f, (const Ipp64f*  pSrc, int srcLen, Ipp64f*  pDst, int dstLen, IppEnum algType, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsAutoCorrNorm_32fc,(const Ipp32fc* pSrc, int srcLen, Ipp32fc* pDst, int dstLen, IppEnum algType, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsAutoCorrNorm_64fc,(const Ipp64fc* pSrc, int srcLen, Ipp64fc* pDst, int dstLen, IppEnum algType, Ipp8u* pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//                Cross-correlation Functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Names:  ippsCrossCorrNormGetBufferSize
//
//  Purpose:     Get the size (in bytes) of the buffer for ippsCrossCorrNorm's internal calculations.
//
//  Parameters:
//    src1Len     - Length of the first source vector.
//    src2Len     - Length of the second source vector.
//    dstLen      - Length of cross-correlation.
//    lowLag      - Cross-correlation lowest lag.
//    dataType    - Data type for correlation {Ipp32f|Ipp32fc|Ipp64f|Ipp64fc}.
//    algType     - Selector for the algorithm type. Possible values are the results of composition
//                  of the  IppAlgType and IppsNormOp values.
//    pBufferSize - Pointer to the calculated buffer size (in bytes).
//  Return:
//    ippStsNoErr       - OK.
//    ippStsNullPtrErr  - pBufferSize is NULL.
//    ippStsSizeErr     - Vector's length is not positive.
//    ippStsDataTypeErr - Unsupported data type.
//    ippStsAlgTypeErr  - Unsupported algorithm or normalization type.
*/
IPPAPI(IppStatus, ippsCrossCorrNormGetBufferSize, (int src1Len, int src2Len, int dstLen, int lowLag, IppDataType dataType, IppEnum algType, int* pBufferSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsCrossCorrNorm
//  Purpose:    Calculate the cross-correlation of two vectors.
//
//  Parameters:
//     pSrc1   - Pointer to the first source vector.
//     src1Len - Length of the first source vector.
//     pSrc2   - Pointer to the second source vector.
//     src2Len - Length of the second source vector.
//     pDst    - Pointer to the cross correlation.
//     dstLen  - Length of the cross-correlation.
//     lowLag  - Cross-correlation lowest lag.
//     algType - Selector for the algorithm type. Possible values are the results of composition
//               of the  IppAlgType and IppsNormOp values.
//     pBuffer - Pointer to the buffer for internal calculations.
//  Return:
//    ippStsNoErr      - OK.
//    ippStsNullPtrErr - One of the pointers is NULL.
//    ippStsSizeErr    - Vector's length is not positive.
//    ippStsAlgTypeErr - Unsupported algorithm or normalization type.
*/
IPPAPI(IppStatus, ippsCrossCorrNorm_32f, (const Ipp32f*  pSrc1, int src1Len, const Ipp32f*  pSrc2, int src2Len, Ipp32f*  pDst, int dstLen, int lowLag, IppEnum algType, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsCrossCorrNorm_64f, (const Ipp64f*  pSrc1, int src1Len, const Ipp64f*  pSrc2, int src2Len, Ipp64f*  pDst, int dstLen, int lowLag, IppEnum algType, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsCrossCorrNorm_32fc,(const Ipp32fc* pSrc1, int src1Len, const Ipp32fc* pSrc2, int src2Len, Ipp32fc* pDst, int dstLen, int lowLag, IppEnum algType, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsCrossCorrNorm_64fc,(const Ipp64fc* pSrc1, int src1Len, const Ipp64fc* pSrc2, int src2Len, Ipp64fc* pDst, int dstLen, int lowLag, IppEnum algType, Ipp8u* pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//                  Convolution functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Names:  ippsConvolveGetBufferSize
//
//  Purpose:     Get the size (in bytes) of the buffer for ippsConvolve's internal calculations.
//
//  Parameters:
//    src1Len     - Length of the first source vector.
//    src2Len     - Length of the second source vector.
//    dataType    - Data type for convolution {Ipp32f|Ipp64f}.
//    algType     - Selector for the algorithm type. Contains IppAlgType values.
//    pBufferSize - Pointer to the calculated buffer size (in bytes).
//  Return:
//   ippStsNoErr       - OK
//   ippStsNullPtrErr  - pBufferSize is NULL.
//   ippStsSizeErr     - Vector's length is not positive.
//   ippStsDataTypeErr - Unsupported data type.
//   ippStsAlgTypeErr - Unsupported algorithm type.
*/
IPPAPI(IppStatus, ippsConvolveGetBufferSize, (int src1Len, int src2Len, IppDataType dataType, IppEnum algType, int* pBufferSize))

/* /////////////////////////////////////////////////////////////////////////////
// Name:       ippsConvolve_32f, ippsConvolve_64f
// Purpose:    Perform a linear convolution of 1D signals.
// Parameters:
//    pSrc1   - Pointer to the first source vector.
//    src1Len - Length of the first source vector.
//    pSrc2   - Pointer to the second source vector.
//    src2Len - Length of the second source vector.
//    pDst    - Pointer to the destination vector.
//    algType - Selector for the algorithm type. Contains IppAlgType values.
//    pBuffer - Pointer to the buffer for internal calculations.
// Returns:    IppStatus
//    ippStsNoErr       - OK.
//    ippStsNullPtrErr  - One of the pointers is NULL.
//    ippStsSizeErr     - Vector's length is not positive.
//    ippStsAlgTypeErr  - Unsupported algorithm type.
//  Notes:
//          Length of the destination data vector is src1Len+src2Len-1.
//          The input signals are exchangeable because of the commutative
//          property of convolution.
//          Some other values may be returned the by FFT transform functions.
*/
IPPAPI(IppStatus, ippsConvolve_32f, (const Ipp32f* pSrc1, int src1Len, const Ipp32f* pSrc2, int src2Len, Ipp32f* pDst, IppEnum algType, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsConvolve_64f, (const Ipp64f* pSrc1, int src1Len, const Ipp64f* pSrc2, int src2Len, Ipp64f* pDst, IppEnum algType, Ipp8u* pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsConvBiased_32f
//  Purpose:    Linear Convolution of 1D signals whith a bias.
//  Parameters:
//      pSrc1               pointer to the first source vector
//      pSrc2               pointer to the second source vector
//      src1Len             length of the first source vector
//      src2Len             length of the second source vector
//      pDst                pointer to the destination vector
//      dstLen              length of the destination vector
//      bias
//  Returns:    IppStatus
//      ippStsNullPtrErr        pointer(s) to the data is NULL
//      ippStsSizeErr           length of the vectors is less or equal zero
//      ippStsNoErr             otherwise
*/
IPPAPI(IppStatus, ippsConvBiased_32f, (const Ipp32f *pSrc1, int src1Len, const Ipp32f *pSrc2, int src2Len, Ipp32f *pDst, int dstLen, int bias))

/* /////////////////////////////////////////////////////////////////////////////
//                  Filtering
///////////////////////////////////////////////////////////////////////////// */

/* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Name:  ippsSumWindow_8u32f      ippsSumWindow_16s32f
//  Purpose:
//  Return:
//    ippStsNoErr        Ok
//    ippStsNullPtrErr   one or more pointers are NULL
//    ippStsMaskSizeErr  maskSize has a field with zero, or negative value
//  Arguments:
//   pSrc        Pointer to the source vector
//   pDst        Pointer to the destination vector
//   maskSize    Size of the mask in pixels
*/
IPPAPI(IppStatus, ippsSumWindow_8u32f,  (const Ipp8u*  pSrc, Ipp32f* pDst, int len, int maskSize))
IPPAPI(IppStatus, ippsSumWindow_16s32f, (const Ipp16s* pSrc, Ipp32f* pDst, int len, int maskSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:         ippsFIRSRGetSize, ippsFIRSRInit, ippsFIRSR
//  Purpose:      Get sizes of the FIR spec structure and temporary buffer
//                initialize FIR spec structure - set taps and delay line
//                perform FIR filtering
//  Parameters:
//      pTaps       - pointer to the filter coefficients
//      tapsLen     - number of coefficients
//      tapsType    - type of coefficients (ipp32f or ipp64f)
//      pSpecSize   - pointer to the size of FIR spec
//      pBufSize    - pointer to the size of temporal buffer
//      algType     - mask for the algorithm type definition (direct, fft, auto)
//      pDlySrc     - pointer to the input  delay line values, can be NULL
//      pDlyDst     - pointer to the output delay line values, can be NULL
//      pSpec       - pointer to the constant internal structure
//      pSrc        - pointer to the source vector.
//      pDst        - pointer to the destination vector
//      numIters    - length  of the destination vector
//      pBuf        - pointer to the work buffer
//   Return:
//      status      - status value returned, its value are
//         ippStsNullPtrErr       - one of the specified pointer is NULL
//         ippStsFIRLenErr        - tapsLen <= 0
//         ippStsContextMatchErr  - wrong state identifier
//         ippStsNoErr            - OK
//         ippStsSizeErr          - numIters is not positive
//         ippStsAlgTypeErr       - unsupported algorithm type
//         ippStsMismatch         - not effective algorithm.
*/
IPPAPI(IppStatus, ippsFIRSRGetSize, (int tapsLen, IppDataType tapsType, int* pSpecSize, int* pBufSize))
IPPAPI(IppStatus, ippsFIRSRGetSize32f_32fc, (int tapsLen, int* pSpecSize, int* pBufSize))

IPPAPI(IppStatus, ippsFIRSRInit_32f, (const Ipp32f*  pTaps, int tapsLen, IppAlgType algType, IppsFIRSpec_32f*  pSpec))
IPPAPI(IppStatus, ippsFIRSRInit_64f, (const Ipp64f*  pTaps, int tapsLen, IppAlgType algType, IppsFIRSpec_64f*  pSpec))
IPPAPI(IppStatus, ippsFIRSRInit_32fc,(const Ipp32fc* pTaps, int tapsLen, IppAlgType algType, IppsFIRSpec_32fc* pSpec))
IPPAPI(IppStatus, ippsFIRSRInit_64fc,(const Ipp64fc* pTaps, int tapsLen, IppAlgType algType, IppsFIRSpec_64fc* pSpec))
IPPAPI(IppStatus, ippsFIRSRInit32f_32fc, (const Ipp32f* pTaps, int tapsLen, IppAlgType algType, IppsFIRSpec32f_32fc* pSpec))

IPPAPI(IppStatus, ippsFIRSR_16s,  (const Ipp16s*  pSrc, Ipp16s*  pDst, int numIters, IppsFIRSpec_32f*  pSpec, const Ipp16s*  pDlySrc, Ipp16s*  pDlyDst, Ipp8u * pBuf))
IPPAPI(IppStatus, ippsFIRSR_16sc, (const Ipp16sc* pSrc, Ipp16sc* pDst, int numIters, IppsFIRSpec_32fc* pSpec, const Ipp16sc* pDlySrc, Ipp16sc* pDlyDst, Ipp8u * pBuf))
IPPAPI(IppStatus, ippsFIRSR_32f,  (const Ipp32f*  pSrc, Ipp32f*  pDst, int numIters, IppsFIRSpec_32f*  pSpec, const Ipp32f*  pDlySrc, Ipp32f*  pDlyDst, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsFIRSR_64f,  (const Ipp64f*  pSrc, Ipp64f*  pDst, int numIters, IppsFIRSpec_64f*  pSpec, const Ipp64f*  pDlySrc, Ipp64f*  pDlyDst, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsFIRSR_32fc, (const Ipp32fc* pSrc, Ipp32fc* pDst, int numIters, IppsFIRSpec_32fc* pSpec, const Ipp32fc* pDlySrc, Ipp32fc* pDlyDst, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsFIRSR_64fc, (const Ipp64fc* pSrc, Ipp64fc* pDst, int numIters, IppsFIRSpec_64fc* pSpec, const Ipp64fc* pDlySrc, Ipp64fc* pDlyDst, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsFIRSR32f_32fc, (const Ipp32fc* pSrc, Ipp32fc* pDst, int numIters, IppsFIRSpec32f_32fc* pSpec, const Ipp32fc* pDlySrc, Ipp32fc* pDlyDst, Ipp8u* pBuf))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:         ippsFIRMRGetSize, ippsFIRMRInit, ippsFIRMR
//  Purpose:      Get sizes of the FIR spec structure and temporary buffer,
//                initialize FIR spec structure - set taps and delay line,
//                perform multi rate FIR filtering
//  Parameters:
//      pTaps       - pointer to the filter coefficients
//      tapsLen     - number of coefficients
//      tapsType    - type of coefficients (ipp32f, ipp32fc, ipp64f or ipp64fc)
//      pSpecSize   - pointer to the size of FIR spec
//      pBufSize    - pointer to the size of temporal buffer
//      pDlySrc     - pointer to the input  delay line values, can be NULL
//      pDlyDst     - pointer to the output delay line values, can be NULL
//      upFactor    - multi-rate up factor;
//      upPhase     - multi-rate up phase;
//      downFactor  - multi-rate down factor;
//      downPhase   - multi-rate down phase;
//      pSpec       - pointer to the constant internal structure
//      pSrc        - pointer to the source vector.
//      pDst        - pointer to the destination vector
//      numIters    - length  of the destination vector
//      pBuf        - pointer to the work buffer
//   Return:
//      status      - status value returned, its value are
//         ippStsNullPtrErr       - one of the specified pointer is NULL
//         ippStsFIRLenErr        - tapsLen <= 0
//         ippStsFIRMRFactorErr   - factor <= 0
//         ippStsFIRMRPhaseErr    - phase < 0 || factor <= phase
//         ippStsContextMatchErr  - wrong state identifier
//         ippStsNoErr            - OK
//         ippStsSizeErr          - numIters is not positive
*/
IPPAPI(IppStatus, ippsFIRMRGetSize, (int tapsLen, int upFactor, int downFactor, IppDataType tapsType, int * pSpecSize, int* pBufSize))
IPPAPI(IppStatus, ippsFIRMRGetSize32f_32fc, (int tapsLen, int upFactor, int downFactor, int * pSpecSize, int* pBufSize))

IPPAPI(IppStatus, ippsFIRMRInit_32f,  (const Ipp32f*  pTaps, int tapsLen, int upFactor, int upPhase, int downFactor, int downPhase, IppsFIRSpec_32f*  pSpec))
IPPAPI(IppStatus, ippsFIRMRInit_64f,  (const Ipp64f*  pTaps, int tapsLen, int upFactor, int upPhase, int downFactor, int downPhase, IppsFIRSpec_64f*  pSpec))
IPPAPI(IppStatus, ippsFIRMRInit_32fc, (const Ipp32fc* pTaps, int tapsLen, int upFactor, int upPhase, int downFactor, int downPhase, IppsFIRSpec_32fc* pSpec))
IPPAPI(IppStatus, ippsFIRMRInit_64fc, (const Ipp64fc* pTaps, int tapsLen, int upFactor, int upPhase, int downFactor, int downPhase, IppsFIRSpec_64fc* pSpec))
IPPAPI(IppStatus, ippsFIRMRInit32f_32fc, (const Ipp32f* pTaps, int tapsLen, int upFactor, int upPhase, int downFactor, int downPhase, IppsFIRSpec32f_32fc* pSpec))

IPPAPI(IppStatus, ippsFIRMR_16s,  (const Ipp16s*  pSrc, Ipp16s*  pDst, int numIters, IppsFIRSpec_32f*  pSpec, const Ipp16s*  pDlySrc, Ipp16s*  pDlyDst, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsFIRMR_16sc, (const Ipp16sc* pSrc, Ipp16sc* pDst, int numIters, IppsFIRSpec_32fc* pSpec, const Ipp16sc* pDlySrc, Ipp16sc* pDlyDst, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsFIRMR_32f,  (const Ipp32f*  pSrc, Ipp32f*  pDst, int numIters, IppsFIRSpec_32f*  pSpec, const Ipp32f*  pDlySrc, Ipp32f*  pDlyDst, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsFIRMR_64f,  (const Ipp64f*  pSrc, Ipp64f*  pDst, int numIters, IppsFIRSpec_64f*  pSpec, const Ipp64f*  pDlySrc, Ipp64f*  pDlyDst, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsFIRMR_32fc, (const Ipp32fc* pSrc, Ipp32fc* pDst, int numIters, IppsFIRSpec_32fc* pSpec, const Ipp32fc* pDlySrc, Ipp32fc* pDlyDst, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsFIRMR_64fc, (const Ipp64fc* pSrc, Ipp64fc* pDst, int numIters, IppsFIRSpec_64fc* pSpec, const Ipp64fc* pDlySrc, Ipp64fc* pDlyDst, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsFIRMR32f_32fc, (const Ipp32fc* pSrc, Ipp32fc* pDst, int numIters, IppsFIRSpec32f_32fc* pSpec, const Ipp32fc* pDlySrc, Ipp32fc* pDlyDst, Ipp8u* pBuf))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:         ippsFIRSparseGetStateSize,
//                ippsFIRSparseInit
//  Purpose:      ippsFIRSparseGetStateSize - calculates the size of the FIRSparse
//                                            State  structure;
//                ippsFIRSparseInit - initialize FIRSparse state - set non-zero taps,
//                their positions and delay line using external memory buffer;
//  Parameters:
//      pNZTaps     - pointer to the non-zero filter coefficients;
//      pNZTapPos   - pointer to the positions of non-zero filter coefficients;
//      nzTapsLen   - number of non-zero coefficients;
//      pDlyLine    - pointer to the delay line values, can be NULL;
//      ppState     - pointer to the FIRSparse state created or NULL;
//      order       - order of FIRSparse filter
//      pStateSize  - pointer where to store the calculated FIRSparse State
//                    structuresize (in bytes);
//   Return:
//      status      - status value returned, its value are
//         ippStsNullPtrErr       - pointer(s) to the data is NULL
//         ippStsFIRLenErr        - nzTapsLen <= 0
//         ippStsSparseErr        - non-zero tap positions are not in ascending order,
//                                  negative or repeated.
//         ippStsNoErr            - otherwise
*/
IPPAPI(IppStatus, ippsFIRSparseGetStateSize_32f, (int nzTapsLen, int order, int *pStateSize))
IPPAPI(IppStatus, ippsFIRSparseInit_32f, (IppsFIRSparseState_32f** ppState, const Ipp32f *pNZTaps, const Ipp32s* pNZTapPos, int nzTapsLen, const Ipp32f *pDlyLine, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsFIRSparseGetStateSize_32fc, (int nzTapsLen, int order, int *pStateSize))
IPPAPI(IppStatus, ippsFIRSparseInit_32fc, (IppsFIRSparseState_32fc** ppState, const Ipp32fc *pNZTaps, const Ipp32s* pNZTapPos, int nzTapsLen, const Ipp32fc *pDlyLine, Ipp8u *pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:         ippsFIRSparse
//  Purpose:       FIRSparse filter with float or complex float taps. Vector filtering
//  Parameters:
//      pSrc        - pointer to the input vector
//      pDst        - pointer to the output vector
//      len         - length data vector
//      pState      - pointer to the filter state
//  Return:
//      ippStsNullPtrErr       - pointer(s) to the data is NULL
//      ippStsSizeErr          - length of the vectors <= 0
//      ippStsNoErr            - otherwise
*/
IPPAPI(IppStatus, ippsFIRSparse_32f, (const Ipp32f* pSrc, Ipp32f* pDst, int len, IppsFIRSparseState_32f* pState))
IPPAPI(IppStatus, ippsFIRSparse_32fc, (const Ipp32fc* pSrc, Ipp32fc* pDst, int len, IppsFIRSparseState_32fc* pState))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:         ippsFIRSparseSetDlyLine_32f
//                 ippsFIRSparseGetDlyLine_32f
//  Purpose:       Get(set) delay line
//  Parameters:
//      pState      - pointer to the filter state
//      pDlyLine    - pointer to the delay line values, can be NULL;
//  Return:
//      ippStsNullPtrErr       - pointer(s) to the data is NULL
*/
IPPAPI(IppStatus, ippsFIRSparseSetDlyLine_32f, (IppsFIRSparseState_32f* pState, const Ipp32f* pDlyLine))
IPPAPI(IppStatus, ippsFIRSparseGetDlyLine_32f, (const IppsFIRSparseState_32f* pState, Ipp32f* pDlyLine))
IPPAPI(IppStatus, ippsFIRSparseSetDlyLine_32fc, (IppsFIRSparseState_32fc* pState, const Ipp32fc* pDlyLine))
IPPAPI(IppStatus, ippsFIRSparseGetDlyLine_32fc, (const IppsFIRSparseState_32fc* pState, Ipp32fc* pDlyLine))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsFIRGenGetBufferSize
//
//  Purpose:    Gets the size (in bytes) of the buffer for ippsFIRGen internal calculations.
//
//  Parameters:
//    tapsLen     - The number of taps.
//    pBufferSize - Pointer to the calculated buffer size (in bytes).
//
//  Returns:
//    ippStsNoErr      - OK.
//    ippStsNullPtrErr - Error when any of the specified pointers is NULL.
//    ippStsSizeErr    - Error when the length of coefficient's array is less than 5.
*/
IPPAPI(IppStatus, ippsFIRGenGetBufferSize, (int tapsLen, int *pBufferSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:     ippsFIRGen
//  Purpose:   This function computes the lowpass FIR filter coefficients
//              by windowing of ideal (infinite) filter coefficients segment.
//
// Parameters:
//    rFreq    - Cut off frequency (0 < rfreq < 0.5).
//    pTaps    - Pointer to the array which specifies the filter coefficients.
//    tapsLen  - The number of taps in pTaps[] array (tapsLen>=5).
//    winType  - The ippWindowType switch variable, which specifies the smoothing window type.
//    doNormal - If doNormal=0 the functions calculates non-normalized sequence of filter coefficients,
//               in other cases the sequence of coefficients will be normalized.
//    pBuffer  - Pointer to the buffer for internal calculations. The size calculates by ippsFIRGenGetBufferSize.
// Returns:
//    ippStsNoErr      - OK.
//    ippStsNullPtrErr - Error when any of the specified pointers is NULL.
//    ippStsSizeErr    - Error when the length of coefficient's array is less than 5.
//    ippStsSizeErr    - Error when the low or high frequency isn't satisfy the condition 0 < rLowFreq < 0.5.
*/
IPPAPI(IppStatus, ippsFIRGenLowpass_64f,  (Ipp64f rFreq, Ipp64f* pTaps, int tapsLen, IppWinType winType, IppBool doNormal, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFIRGenHighpass_64f, (Ipp64f rFreq, Ipp64f* pTaps, int tapsLen, IppWinType winType, IppBool doNormal, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippsFIRGenBandpass_64f, (Ipp64f rLowFreq, Ipp64f rHighFreq, Ipp64f* pTaps, int tapsLen, IppWinType winType, IppBool doNormal, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFIRGenBandstop_64f, (Ipp64f rLowFreq, Ipp64f rHighFreq, Ipp64f* pTaps, int tapsLen, IppWinType winType, IppBool doNormal, Ipp8u* pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//                  FIR LMS filters
///////////////////////////////////////////////////////////////////////////// */

/* ////////////////////////////////////////////////////////////////////////////
//  Name:         ippsFIRLMSGetStateSize, ippsFIRLMSInit
//  Purpose:      ippsFIRLMSGetStateSize - calculates the size of the FIR State
//                                                                   structure;
//                ippsFIRLMSInit - initialize FIR state - set taps and delay line
//                using external memory buffer;
//  Parameters:
//      pTaps       - pointer to the filter coefficients;
//      tapsLen     - number of coefficients;
//      dlyIndex      current index value for the delay line
//      pDlyLine    - pointer to the delay line values, can be NULL;
//      ppState     - pointer to the FIR state created or NULL;
//      pStateSize  - pointer where to store the calculated FIR State structure
//   Return:
//      status      - status value returned, its value are
//         ippStsNullPtrErr       - pointer(s) to the data is NULL
//         ippStsFIRLenErr        - tapsLen <= 0
//         ippStsNoErr            - otherwise
*/
IPPAPI(IppStatus, ippsFIRLMSGetStateSize32f_16s, (int tapsLen, int dlyIndex, int* pBufferSize))
IPPAPI(IppStatus, ippsFIRLMSGetStateSize_32f,    (int tapsLen, int dlyIndex, int* pBufferSize))

IPPAPI(IppStatus, ippsFIRLMSInit32f_16s, (IppsFIRLMSState32f_16s** ppState, const Ipp32f* pTaps, int tapsLen, const Ipp16s *pDlyLine, int dlyIndex, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFIRLMSInit_32f,    (IppsFIRLMSState_32f**    ppState, const Ipp32f* pTaps, int tapsLen, const Ipp32f *pDlyLine, int dlyIndex, Ipp8u* pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//   Names:      ippsFIRLMS
//   Purpose:    LMS filtering
//   Parameters:
//      pState    pointer to the state
//      pSrc      pointer to the source signal
//      pRef      pointer to the desired signal
//      pDst      pointer to the output signal
//      len       length of the signals
//      mu        adaptation step
//   Return:
//      ippStsNullPtrErr       pointer to the data is null
//      ippStsSizeErr          the length of signals is equal or less zero
//      ippStsContextMatchErr    wrong state identifier
//      ippStsNoErr            otherwise
*/
IPPAPI(IppStatus, ippsFIRLMS32f_16s, (const Ipp16s* pSrc, const Ipp16s* pRef, Ipp16s* pDst, int len, float mu, IppsFIRLMSState32f_16s* pState))
IPPAPI(IppStatus, ippsFIRLMS_32f,    (const Ipp32f* pSrc, const Ipp32f* pRef, Ipp32f* pDst, int len, float mu, IppsFIRLMSState_32f*    pState))

/* /////////////////////////////////////////////////////////////////////////////
//   Names:        ippsFIRLMSGetTaps
//   Purpose:      get taps values
//   Parameters:
//      pstate          pointer to the state
//      pTaps           pointer to the array to store the taps values
//   Return:
//      ippStsNullPtrErr   pointer to the data is null
//      ippStsNoErr        otherwise
*/
IPPAPI(IppStatus, ippsFIRLMSGetTaps32f_16s, (const IppsFIRLMSState32f_16s* pState, Ipp32f* pOutTaps))
IPPAPI(IppStatus, ippsFIRLMSGetTaps_32f,    (const IppsFIRLMSState_32f*    pState, Ipp32f* pOutTaps))

/* /////////////////////////////////////////////////////////////////////////////
//   Names:       ippsFIRLMSGetDlyl, ippsFIRLMSSetDlyl
//   Purpose:     set or get delay line
//   Parameters:
//      pState         pointer to the state structure
//      pDlyLine       pointer to the delay line of the single size = tapsLen
//      pDlyLineIndex  pointer to get the current delay line index
//   Return:
//      ippStsNullPtrErr       pointer to the data is null
//      ippStsContextMatchErr    wrong state identifier
//      ippStsNoErr            otherwise
*/
IPPAPI(IppStatus, ippsFIRLMSGetDlyLine32f_16s, (const IppsFIRLMSState32f_16s* pState, Ipp16s* pDlyLine, int* pDlyLineIndex))
IPPAPI(IppStatus, ippsFIRLMSGetDlyLine_32f,    (const IppsFIRLMSState_32f*    pState, Ipp32f* pDlyLine, int* pDlyLineIndex))

IPPAPI(IppStatus, ippsFIRLMSSetDlyLine32f_16s, (IppsFIRLMSState32f_16s* pState, const Ipp16s* pDlyLine, int dlyLineIndex))
IPPAPI(IppStatus, ippsFIRLMSSetDlyLine_32f,    (IppsFIRLMSState_32f*    pState, const Ipp32f* pDlyLine, int dlyLineIndex))

/* /////////////////////////////////////////////////////////////////////////////
//                     IIR filters (float and double taps versions)
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//                          Work with Delay Line
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsIIRGetDlyLine, ippsIIRSetDlyLine
//  Purpose:    set and get delay line
//  Parameters:
//      pState              - pointer to IIR filter context
//      pDelay              - pointer to delay line to be set
//  Return:
//      ippStsContextMatchErr  - wrong context identifier
//      ippStsNullPtrErr       - pointer(s) pState or pDelay is NULL
//      ippStsNoErr            - otherwise
*/
IPPAPI(IppStatus, ippsIIRGetDlyLine32f_16s,    (const IppsIIRState32f_16s*   pState, Ipp32f*  pDlyLine))
IPPAPI(IppStatus, ippsIIRGetDlyLine32fc_16sc,  (const IppsIIRState32fc_16sc* pState, Ipp32fc* pDlyLine))
IPPAPI(IppStatus, ippsIIRGetDlyLine_32f,       (const IppsIIRState_32f*      pState, Ipp32f*  pDlyLine))
IPPAPI(IppStatus, ippsIIRGetDlyLine_32fc,      (const IppsIIRState_32fc*     pState, Ipp32fc* pDlyLine))
IPPAPI(IppStatus, ippsIIRGetDlyLine64f_16s,    (const IppsIIRState64f_16s*   pState, Ipp64f*  pDlyLine))
IPPAPI(IppStatus, ippsIIRGetDlyLine64fc_16sc,  (const IppsIIRState64fc_16sc* pState, Ipp64fc* pDlyLine))
IPPAPI(IppStatus, ippsIIRGetDlyLine64f_32s,    (const IppsIIRState64f_32s*   pState, Ipp64f*  pDlyLine))
IPPAPI(IppStatus, ippsIIRGetDlyLine64fc_32sc,  (const IppsIIRState64fc_32sc* pState, Ipp64fc* pDlyLine))
IPPAPI(IppStatus, ippsIIRGetDlyLine64f_DF1_32s,(const IppsIIRState64f_32s*   pState, Ipp32s*  pDlyLine))
IPPAPI(IppStatus, ippsIIRGetDlyLine64f_32f,    (const IppsIIRState64f_32f*   pState, Ipp64f*  pDlyLine))
IPPAPI(IppStatus, ippsIIRGetDlyLine64fc_32fc,  (const IppsIIRState64fc_32fc* pState, Ipp64fc* pDlyLine))
IPPAPI(IppStatus, ippsIIRGetDlyLine_64f,       (const IppsIIRState_64f*      pState, Ipp64f*  pDlyLine))
IPPAPI(IppStatus, ippsIIRGetDlyLine_64fc,      (const IppsIIRState_64fc*     pState, Ipp64fc* pDlyLine))

IPPAPI(IppStatus, ippsIIRSetDlyLine32f_16s,    (IppsIIRState32f_16s*   pState, const Ipp32f*  pDlyLine))
IPPAPI(IppStatus, ippsIIRSetDlyLine32fc_16sc,  (IppsIIRState32fc_16sc* pState, const Ipp32fc* pDlyLine))
IPPAPI(IppStatus, ippsIIRSetDlyLine_32f,       (IppsIIRState_32f*      pState, const Ipp32f*  pDlyLine))
IPPAPI(IppStatus, ippsIIRSetDlyLine_32fc,      (IppsIIRState_32fc*     pState, const Ipp32fc* pDlyLine))
IPPAPI(IppStatus, ippsIIRSetDlyLine64f_16s,    (IppsIIRState64f_16s*   pState, const Ipp64f*  pDlyLine))
IPPAPI(IppStatus, ippsIIRSetDlyLine64fc_16sc,  (IppsIIRState64fc_16sc* pState, const Ipp64fc* pDlyLine))
IPPAPI(IppStatus, ippsIIRSetDlyLine64f_32s,    (IppsIIRState64f_32s*   pState, const Ipp64f*  pDlyLine))
IPPAPI(IppStatus, ippsIIRSetDlyLine64fc_32sc,  (IppsIIRState64fc_32sc* pState, const Ipp64fc* pDlyLine))
IPPAPI(IppStatus, ippsIIRSetDlyLine64f_DF1_32s,(IppsIIRState64f_32s*   pState, const Ipp32s*  pDlyLine))
IPPAPI(IppStatus, ippsIIRSetDlyLine64f_32f,    (IppsIIRState64f_32f*   pState, const Ipp64f*  pDlyLine))
IPPAPI(IppStatus, ippsIIRSetDlyLine64fc_32fc,  (IppsIIRState64fc_32fc* pState, const Ipp64fc* pDlyLine))
IPPAPI(IppStatus, ippsIIRSetDlyLine_64f,       (IppsIIRState_64f*      pState, const Ipp64f*  pDlyLine))
IPPAPI(IppStatus, ippsIIRSetDlyLine_64fc,      (IppsIIRState_64fc*     pState, const Ipp64fc* pDlyLine))

/* /////////////////////////////////////////////////////////////////////////////
//                  IIR Filtering
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Names:         ippsIIR
//  Purpose:       IIR filter with float or double taps. Vector filtering
//  Parameters:
//      pState              - pointer to filter context
//      pSrcDst             - pointer to input/output vector in in-place ops
//      pSrc                - pointer to input vector
//      pDst                - pointer to output vector
//      len                 - length of the vectors
//      scaleFactor         - scale factor value
//  Return:
//      ippStsContextMatchErr  - wrong context identifier
//      ippStsNullPtrErr       - pointer(s) to the data is NULL
//      ippStsSizeErr          - length of the vectors <= 0
//      ippStsNoErr            - otherwise
//
//  Note: Don't modify scaleFactor value unless context is changed
*/

IPPAPI(IppStatus, ippsIIR32f_16s_ISfs,  (                     Ipp16s*  pSrcDst, int len, IppsIIRState32f_16s*   pState, int scaleFactor))
IPPAPI(IppStatus, ippsIIR32f_16s_Sfs,   (const Ipp16s*  pSrc, Ipp16s*  pDst,    int len, IppsIIRState32f_16s*   pState, int scaleFactor))
IPPAPI(IppStatus, ippsIIR32fc_16sc_ISfs,(                     Ipp16sc* pSrcDst, int len, IppsIIRState32fc_16sc* pState, int scaleFactor))
IPPAPI(IppStatus, ippsIIR32fc_16sc_Sfs, (const Ipp16sc* pSrc, Ipp16sc* pDst,    int len, IppsIIRState32fc_16sc* pState, int scaleFactor))
IPPAPI(IppStatus, ippsIIR_32f_I,        (                     Ipp32f*  pSrcDst, int len, IppsIIRState_32f*      pState))
IPPAPI(IppStatus, ippsIIR_32f,          (const Ipp32f*  pSrc, Ipp32f*  pDst,    int len, IppsIIRState_32f*      pState))
IPPAPI(IppStatus, ippsIIR_32fc_I,       (                     Ipp32fc* pSrcDst, int len, IppsIIRState_32fc*     pState))
IPPAPI(IppStatus, ippsIIR_32fc,         (const Ipp32fc* pSrc, Ipp32fc* pDst,    int len, IppsIIRState_32fc*     pState))
IPPAPI(IppStatus, ippsIIR64f_16s_ISfs,  (                     Ipp16s*  pSrcDst, int len, IppsIIRState64f_16s*   pState, int scaleFactor))
IPPAPI(IppStatus, ippsIIR64f_16s_Sfs,   (const Ipp16s*  pSrc, Ipp16s*  pDst,    int len, IppsIIRState64f_16s*   pState, int scaleFactor))
IPPAPI(IppStatus, ippsIIR64fc_16sc_ISfs,(                     Ipp16sc* pSrcDst, int len, IppsIIRState64fc_16sc* pState, int scaleFactor))
IPPAPI(IppStatus, ippsIIR64fc_16sc_Sfs, (const Ipp16sc* pSrc, Ipp16sc* pDst,    int len, IppsIIRState64fc_16sc* pState, int scaleFactor))
IPPAPI(IppStatus, ippsIIR64f_32s_ISfs,  (                     Ipp32s*  pSrcDst, int len, IppsIIRState64f_32s*   pState, int scaleFactor))
IPPAPI(IppStatus, ippsIIR64f_32s_Sfs,   (const Ipp32s*  pSrc, Ipp32s*  pDst,    int len, IppsIIRState64f_32s*   pState, int scaleFactor))
IPPAPI(IppStatus, ippsIIR64fc_32sc_ISfs,(                     Ipp32sc* pSrcDst, int len, IppsIIRState64fc_32sc* pState, int scaleFactor))
IPPAPI(IppStatus, ippsIIR64fc_32sc_Sfs, (const Ipp32sc* pSrc, Ipp32sc* pDst,    int len, IppsIIRState64fc_32sc* pState, int scaleFactor))
IPPAPI(IppStatus, ippsIIR64f_32f_I,     (                     Ipp32f*  pSrcDst, int len, IppsIIRState64f_32f*   pState))
IPPAPI(IppStatus, ippsIIR64f_32f,       (const Ipp32f*  pSrc, Ipp32f*  pDst,    int len, IppsIIRState64f_32f*   pState))
IPPAPI(IppStatus, ippsIIR64fc_32fc_I,   (                     Ipp32fc* pSrcDst, int len, IppsIIRState64fc_32fc* pState))
IPPAPI(IppStatus, ippsIIR64fc_32fc,     (const Ipp32fc* pSrc, Ipp32fc* pDst,    int len, IppsIIRState64fc_32fc* pState))
IPPAPI(IppStatus, ippsIIR_64f_I,        (                     Ipp64f*  pSrcDst, int len, IppsIIRState_64f*      pState))
IPPAPI(IppStatus, ippsIIR_64f,          (const Ipp64f*  pSrc, Ipp64f*  pDst,    int len, IppsIIRState_64f*      pState))
IPPAPI(IppStatus, ippsIIR_64fc_I,       (                     Ipp64fc* pSrcDst, int len, IppsIIRState_64fc*     pState))
IPPAPI(IppStatus, ippsIIR_64fc,         (const Ipp64fc* pSrc, Ipp64fc* pDst,    int len, IppsIIRState_64fc*     pState))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:         ippsIIR_32f_P, ippsIIR64f_32s_P
//  Purpose:       IIR filter for multi-channel data. Vector filtering.
//  Parameters:
//      ppSrc               - pointer to array of pointers to source vectors
//      ppDst               - pointer to array of pointers to destination vectors
//      ppSrcDst            - pointer to array of source/destination vectors in in-place ops
//      len                 - length of the vectors
//      nChannels           - number of processing channels
//      ppState             - pointer to array of filter contexts
//  Return:
//      ippStsContextMatchErr  - wrong context identifier
//      ippStsNullPtrErr       - pointer(s) to the data is NULL
//      ippStsSizeErr          - length of the vectors <= 0
//      ippStsChannelErr       - number of processing channels <= 0
//      ippStsNoErr            - otherwise
//
*/
IPPAPI(IppStatus, ippsIIR_32f_IP,      (                      Ipp32f **ppSrcDst, int len, int nChannels, IppsIIRState_32f    **ppState))
IPPAPI(IppStatus, ippsIIR_32f_P,       (const Ipp32f **ppSrc, Ipp32f **ppDst,    int len, int nChannels, IppsIIRState_32f    **ppState))
IPPAPI(IppStatus, ippsIIR64f_32s_IPSfs,(                      Ipp32s **ppSrcDst, int len, int nChannels, IppsIIRState64f_32s **ppState, int *pScaleFactor))
IPPAPI(IppStatus, ippsIIR64f_32s_PSfs, (const Ipp32s **ppSrc, Ipp32s **ppDst,    int len, int nChannels, IppsIIRState64f_32s **ppState, int *pScaleFactor))

/* ////////////////////////////////////////////////////////////////////////////
//          Initialize IIR state with external memory buffer
//////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////////
//  Name:         ippsIIRGetStateSize, ippsIIRInit
//  Purpose:      ippsIIRGetStateSize - calculates the size of the IIR State structure;
//                ippsIIRInit - initialize IIR state - set taps and delay line
//                using external memory buffer;
//  Parameters:
//      pTaps       - pointer to the filter coefficients;
//      order       - order of the filter;
//      numBq       - order of the filter;
//      pDlyLine    - pointer to the delay line values, can be NULL;
//      ppState     - double pointer to the IIR state created or NULL;
//      tapsFactor  - scaleFactor for taps (integer version);
//      pBufferSize - pointer where to store the calculated IIR State structure
//                                                             size (in bytes);
//   Return:
//      status      - status value returned, its value are
//         ippStsNullPtrErr       - pointer(s) to the data is NULL
//         ippStsIIROrderErr      - order <= 0 or numBq < 1
//         ippStsNoErr            - otherwise
*/
IPPAPI(IppStatus, ippsIIRGetStateSize32f_16s,   (int order, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRGetStateSize32fc_16sc, (int order, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRGetStateSize_32f,      (int order, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRGetStateSize_32fc,     (int order, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRGetStateSize64f_16s,   (int order, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRGetStateSize64fc_16sc, (int order, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRGetStateSize64f_32s,   (int order, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRGetStateSize64fc_32sc, (int order, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRGetStateSize64f_32f,   (int order, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRGetStateSize64fc_32fc, (int order, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRGetStateSize_64f,      (int order, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRGetStateSize_64fc,     (int order, int *pBufferSize))

IPPAPI(IppStatus, ippsIIRGetStateSize32f_BiQuad_16s,    (int numBq, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRGetStateSize32fc_BiQuad_16sc,  (int numBq, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRGetStateSize_BiQuad_32f,       (int numBq, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRGetStateSize_BiQuad_DF1_32f,   (int numBq, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRGetStateSize_BiQuad_32fc,      (int numBq, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRGetStateSize64f_BiQuad_16s,    (int numBq, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRGetStateSize64fc_BiQuad_16sc,  (int numBq, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRGetStateSize64f_BiQuad_32s,    (int numBq, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRGetStateSize64f_BiQuad_DF1_32s,(int numBq, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRGetStateSize64fc_BiQuad_32sc,  (int numBq, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRGetStateSize64f_BiQuad_32f,    (int numBq, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRGetStateSize64fc_BiQuad_32fc,  (int numBq, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRGetStateSize_BiQuad_64f,       (int numBq, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRGetStateSize_BiQuad_64fc,      (int numBq, int *pBufferSize))

IPPAPI(IppStatus, ippsIIRInit32f_16s,   (IppsIIRState32f_16s**   ppState, const Ipp32f*  pTaps, int order, const Ipp32f*  pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRInit32fc_16sc, (IppsIIRState32fc_16sc** ppState, const Ipp32fc* pTaps, int order, const Ipp32fc* pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRInit_32f,      (IppsIIRState_32f**      ppState, const Ipp32f*  pTaps, int order, const Ipp32f*  pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRInit_32fc,     (IppsIIRState_32fc**     ppState, const Ipp32fc* pTaps, int order, const Ipp32fc* pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRInit64f_16s,   (IppsIIRState64f_16s**   ppState, const Ipp64f*  pTaps, int order, const Ipp64f*  pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRInit64fc_16sc, (IppsIIRState64fc_16sc** ppState, const Ipp64fc* pTaps, int order, const Ipp64fc* pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRInit64f_32s,   (IppsIIRState64f_32s**   ppState, const Ipp64f*  pTaps, int order, const Ipp64f*  pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRInit64fc_32sc, (IppsIIRState64fc_32sc** ppState, const Ipp64fc* pTaps, int order, const Ipp64fc* pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRInit64f_32f,   (IppsIIRState64f_32f**   ppState, const Ipp64f*  pTaps, int order, const Ipp64f*  pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRInit64fc_32fc, (IppsIIRState64fc_32fc** ppState, const Ipp64fc* pTaps, int order, const Ipp64fc* pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRInit_64f,      (IppsIIRState_64f**      ppState, const Ipp64f*  pTaps, int order, const Ipp64f*  pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRInit_64fc,     (IppsIIRState_64fc**     ppState, const Ipp64fc* pTaps, int order, const Ipp64fc* pDlyLine, Ipp8u* pBuf))

IPPAPI(IppStatus, ippsIIRInit32f_BiQuad_16s,    (IppsIIRState32f_16s**   ppState, const Ipp32f*  pTaps, int numBq, const Ipp32f*  pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRInit32fc_BiQuad_16sc,  (IppsIIRState32fc_16sc** ppState, const Ipp32fc* pTaps, int numBq, const Ipp32fc* pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRInit_BiQuad_32f,       (IppsIIRState_32f**      ppState, const Ipp32f*  pTaps, int numBq, const Ipp32f*  pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRInit_BiQuad_DF1_32f,   (IppsIIRState_32f**      ppState, const Ipp32f*  pTaps, int numBq, const Ipp32f*  pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRInit_BiQuad_32fc,      (IppsIIRState_32fc**     ppState, const Ipp32fc* pTaps, int numBq, const Ipp32fc* pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRInit64f_BiQuad_16s,    (IppsIIRState64f_16s**   ppState, const Ipp64f*  pTaps, int numBq, const Ipp64f*  pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRInit64fc_BiQuad_16sc,  (IppsIIRState64fc_16sc** ppState, const Ipp64fc* pTaps, int numBq, const Ipp64fc* pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRInit64f_BiQuad_32s,    (IppsIIRState64f_32s**   ppState, const Ipp64f*  pTaps, int numBq, const Ipp64f*  pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRInit64f_BiQuad_DF1_32s,(IppsIIRState64f_32s**   ppState, const Ipp64f*  pTaps, int numBq, const Ipp32s*  pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRInit64fc_BiQuad_32sc,  (IppsIIRState64fc_32sc** ppState, const Ipp64fc* pTaps, int numBq, const Ipp64fc* pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRInit64f_BiQuad_32f,    (IppsIIRState64f_32f**   ppState, const Ipp64f*  pTaps, int numBq, const Ipp64f*  pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRInit64fc_BiQuad_32fc,  (IppsIIRState64fc_32fc** ppState, const Ipp64fc* pTaps, int numBq, const Ipp64fc* pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRInit_BiQuad_64f,       (IppsIIRState_64f**      ppState, const Ipp64f*  pTaps, int numBq, const Ipp64f*  pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRInit_BiQuad_64fc,      (IppsIIRState_64fc**     ppState, const Ipp64fc* pTaps, int numBq, const Ipp64fc* pDlyLine, Ipp8u* pBuf))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:         ippsIIRSparseGetStateSize,
//                ippsIIRSparseInit
//  Purpose:      ippsIIRSparseGetStateSize - calculates the size of the
//                                            IIRSparse State structure;
//                ippsIIRSparseInit - initialize IIRSparse state - set non-zero taps,
//                their positions and delay line using external memory buffer;
//  Parameters:
//      pNZTaps     - pointer to the non-zero filter coefficients;
//      pNZTapPos   - pointer to the positions of non-zero filter coefficients;
//      nzTapsLen1,
//      nzTapsLen2  - number of non-zero coefficients according to the IIRSparseformula;
//      pDlyLine    - pointer to the delay line values, can be NULL;
//      ppState     - pointer to the IIR state created or NULL;
//      pStateSize  - pointer where to store the calculated IIR State structure
//                                                             size (in bytes);
//   Return:
//      status      - status value returned, its value are
//         ippStsNullPtrErr       - pointer(s) to the data is NULL
//         ippStsIIROrderErr      - nzTapsLen1 <= 0 or nzTapsLen2 < 0
//         ippStsSparseErr        - non-zero tap positions are not in ascending order,
//                                  negative or repeated.
//         ippStsNoErr            - otherwise
*/
IPPAPI(IppStatus, ippsIIRSparseGetStateSize_32f, (int nzTapsLen1, int nzTapsLen2, int order1, int order2, int *pStateSize))
IPPAPI(IppStatus, ippsIIRSparseInit_32f, (IppsIIRSparseState_32f** ppState, const Ipp32f* pNZTaps, const Ipp32s* pNZTapPos, int nzTapsLen1, int nzTapsLen2, const Ipp32f* pDlyLine, Ipp8u* pBuf))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:         ippsIIRSparse
//  Purpose:       IIRSparse filter with float taps. Vector filtering
//  Parameters:
//      pSrc                - pointer to input vector
//      pDst                - pointer to output vector
//      len                 - length of the vectors
//      pState              - pointer to the filter state
//  Return:
//      ippStsNullPtrErr       - pointer(s) to the data is NULL
//      ippStsSizeErr          - length of the vectors <= 0
//      ippStsNoErr            - otherwise
*/
IPPAPI(IppStatus, ippsIIRSparse_32f, (const Ipp32f* pSrc, Ipp32f* pDst, int len, IppsIIRSparseState_32f* pState))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsIIRGenLowpass_64f, ippsIIRGenHighpass_64f
//
//  Purpose:    This function computes the highpass and lowpass IIR filter coefficients
//
//  Parameters:
//    rFreq       - Cut off frequency (0 < rFreq < 0.5).
//    ripple      - Possible ripple in pass band for ippChebyshev1 type of filter.
//    order       - The order of future filter (1 <= order <= 12).
//    pTaps       - Pointer to the array which specifies the filter coefficients.
//    filterType  - Type of required filter (ippButterworth or ippChebyshev1).
//    pBuffer     - Pointer to the buffer for internal calculations. The size calculates by ippsIIRGenGetBufferSize.
//
//  Returns:
//    ippStsNoErr                - OK.
//    ippStsNullPtrErr           - Error when any of the specified pointers is NULL.
//    ippStsIIRPassbandRippleErr - Error when the ripple in passband for Chebyshev1 design is less zero, equal to zero or greater than 29.
//    ippStsFilterFrequencyErr   - Error when the cut of frequency of filter is less zero, equal to zero or greater than 0.5.
//    ippStsIIRGenOrderErr       - Error when the order of an IIR filter for design them is less than one or greater than 12.
*/
IPPAPI(IppStatus, ippsIIRGenLowpass_64f,  (Ipp64f rFreq, Ipp64f ripple, int order, Ipp64f* pTaps, IppsIIRFilterType filterType, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsIIRGenHighpass_64f, (Ipp64f rFreq, Ipp64f ripple, int order, Ipp64f* pTaps, IppsIIRFilterType filterType, Ipp8u* pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsIIRGenGetBufferSize
//
//  Purpose:    Gets the size (in bytes) of the buffer for ippsIIRGen internal calculations.
//
//  Parameters:
//    order       - The order of future filter (1 <= order <= 12).
//    pBufferSize - Pointer to the calculated buffer size (in bytes).
//
//  Returns:
//    ippStsNoErr                - OK.
//    ippStsNullPtrErr           - Error when any of the specified pointers is NULL.
//    ippStsIIRGenOrderErr       - Error when the order of an IIR filter for design them is less than one or greater than 12.
*/
IPPAPI(IppStatus, ippsIIRGenGetBufferSize, (int order, int *pBufferSize))

/* /////////////////////////////////////////////////////////////////////////////
//                  Median filter
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsFilterMedianGetBufferSize
//  Purpose:    Get sizes of working buffer for functions ipsFilterMedian
//  Parameters:
//   maskSize           median mask size (odd)
//   dataType           data type
//   pBufferSize        pointer to buffer size
//  Return:
//   ippStsNullPtrErr              pointer to pBufferSize is NULL
//   ippStsMaskSizeErr             maskSize is is less or equal zero
//   ippStsDataTypeErr             data type is incorrect or not supported.
//   ippStsNoErr                   otherwise
*/
IPPAPI(IppStatus, ippsFilterMedianGetBufferSize, (int maskSize, IppDataType dataType, int* pBufferSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsFilterMedian
//  Purpose:    filter source data by the Median Filter
//  Parameters:
//   pSrcDst            pointer to the source and destinaton vector
//   pSrc               pointer to the source vector
//   pDst               pointer to the destination vector
//   len                length of the vector(s)
//   maskSize           median mask size (odd)
//   pDlySrc            pointer to the input  delay line values (length is (maskSize-1)), can be NULL
//   pDlyDst            pointer to the output delay line values (length is (maskSize-1)), can be NULL
//   pBuffer            pointer to the work buffer
//  Return:
//   ippStsNullPtrErr              pointer(s) to the data is NULL
//   ippStsSizeErr                 length of the vector(s) is less or equal zero
//   ippStsMaskSizeErr             maskSize is is less or equal zero
//   ippStsEvenMedianMaskSize      median mask size is even warning
//   ippStsNoErr                   otherwise
//  Notes:
//   if pDlySrc is NULL for all i < 0 pSrc[i] = pSrc[0]
*/
IPPAPI(IppStatus, ippsFilterMedian_8u_I,  (                    Ipp8u*  pSrcDst, int len, int maskSize, const Ipp8u  *pDlySrc, Ipp8u  *pDlyDst, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsFilterMedian_8u,    (const Ipp8u*  pSrc, Ipp8u*  pDst,    int len, int maskSize, const Ipp8u  *pDlySrc, Ipp8u  *pDlyDst, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsFilterMedian_16s_I, (                    Ipp16s* pSrcDst, int len, int maskSize, const Ipp16s *pDlySrc, Ipp16s *pDlyDst, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsFilterMedian_16s,   (const Ipp16s* pSrc, Ipp16s* pDst,    int len, int maskSize, const Ipp16s *pDlySrc, Ipp16s *pDlyDst, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsFilterMedian_32s_I, (                    Ipp32s* pSrcDst, int len, int maskSize, const Ipp32s *pDlySrc, Ipp32s *pDlyDst, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsFilterMedian_32s,   (const Ipp32s* pSrc, Ipp32s* pDst,    int len, int maskSize, const Ipp32s *pDlySrc, Ipp32s *pDlyDst, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsFilterMedian_32f_I, (                    Ipp32f* pSrcDst, int len, int maskSize, const Ipp32f *pDlySrc, Ipp32f *pDlyDst, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsFilterMedian_32f,   (const Ipp32f* pSrc, Ipp32f* pDst,    int len, int maskSize, const Ipp32f *pDlySrc, Ipp32f *pDlyDst, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsFilterMedian_64f_I, (                    Ipp64f* pSrcDst, int len, int maskSize, const Ipp64f *pDlySrc, Ipp64f *pDlyDst, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsFilterMedian_64f,   (const Ipp64f* pSrc, Ipp64f* pDst,    int len, int maskSize, const Ipp64f *pDlySrc, Ipp64f *pDlyDst, Ipp8u *pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippsResamplePolyphase, ippsResamplePolyphaseFixed
//  Purpose:        Resample input data.
//   Arguments:
//      pSrc      The pointer to the input vector.
//      pDst      The pointer to the output vector.
//      len       The number of input vector elements to resample.
//      norm      The norming factor for output samples.
//      factor    The resampling factor.
//      pTime     The pointer to the start time of resampling (in input vector elements).
//      pOutlen   The number of calculated output vector elements
//      pSpec     The pointer to the resampling specification structure.
//   Return Value
//      ippStsNoErr        Indicates no error.
//      ippStsNullPtrErr   Indicates an error when pSpec, pSrc, pDst, pTime or pOutlen is NULL.
//      ippStsSizeErr      Indicates an error when len is less than or equal to 0.
//      ippStsBadArgErr    Indicates an error when factor is less than or equal to.
*/
IPPAPI(IppStatus, ippsResamplePolyphase_16s, (const Ipp16s *pSrc, int len, Ipp16s *pDst, Ipp64f factor, Ipp32f norm, Ipp64f *pTime, int *pOutlen, const IppsResamplingPolyphase_16s *pSpec))
IPPAPI(IppStatus, ippsResamplePolyphase_32f, (const Ipp32f *pSrc, int len, Ipp32f *pDst, Ipp64f factor, Ipp32f norm, Ipp64f *pTime, int *pOutlen, const IppsResamplingPolyphase_32f *pSpec))

IPPAPI(IppStatus, ippsResamplePolyphaseFixed_16s, (const Ipp16s *pSrc, int len, Ipp16s *pDst, Ipp32f norm, Ipp64f *pTime, int *pOutlen, const IppsResamplingPolyphaseFixed_16s *pSpec))
IPPAPI(IppStatus, ippsResamplePolyphaseFixed_32f, (const Ipp32f *pSrc, int len, Ipp32f *pDst, Ipp32f norm, Ipp64f *pTime, int *pOutlen, const IppsResamplingPolyphaseFixed_32f *pSpec))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippsResamplePolyphaseGetSize, ippsResamplePolyphaseFixedGetSize
//  Purpose:        Determines the size required for the ResamplePolyphase or ResamplePolyphaseFixed.
//   Arguments:
//      window          The size of the ideal lowpass filter window.
//      nStep           The discretization step for filter coefficients
//      inRate          The input rate for resampling with fixed factor.
//      outRate         The output rate for resampling with fixed factor.
//      len             The filter length for resampling with fixed factor.
//      pSize           Required size in bytes
//      pLen            Filter len
//      pHeight         Number of filter
//      hint            Suggests using specific code. The values for the hint argument are described in "Flag and Hint Arguments"
//
//   Return Value
//      ippStsNoErr       Indicates no error.
//      ippStsNullPtrErr  Indicates an error when pSize, pLen or pHeight are NULL.
//      ippStsSizeErr     Indicates an error when inRate, outRate or len is less than or equal to 0.
*/
IPPAPI(IppStatus, ippsResamplePolyphaseGetSize_16s, (Ipp32f window, int nStep, int* pSize, IppHintAlgorithm hint))
IPPAPI(IppStatus, ippsResamplePolyphaseGetSize_32f, (Ipp32f window, int nStep, int* pSize, IppHintAlgorithm hint))

IPPAPI(IppStatus, ippsResamplePolyphaseFixedGetSize_16s, (int inRate, int outRate, int len, int* pSize, int* pLen, int* pHeight, IppHintAlgorithm hint))
IPPAPI(IppStatus, ippsResamplePolyphaseFixedGetSize_32f, (int inRate, int outRate, int len, int* pSize, int* pLen, int* pHeight, IppHintAlgorithm hint))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippsResamplePolyphaseInit, ippsResamplePolyphaseFixedInit
//  Purpose:        Initializes ResamplePolyphase of ResamplePolyphaseFixed structures
//   Arguments:
//      window          The size of the ideal lowpass filter window.
//      nStep           The discretization step for filter coefficients
//      inRate          The input rate for resampling with fixed factor.
//      outRate         The output rate for resampling with fixed factor.
//      len             The filter length for resampling with fixed factor.
//      rollf           The roll-off frequency of the filter.
//      alpha           The parameter of the Kaiser window.
//      pSpec           The pointer to the resampling specification structure to be created.
//      hint            Suggests using specific code. The values for the hint argument are described in "Flag and Hint Arguments"
//   Return Value
//      ippStsNoErr       Indicates no error.
//      ippStsNullPtrErr  Indicates an error when pSpec is NULL.
//      ippStsSizeErr     Indicates an error when inRate, outRate or len is less than or equal to 0.
//
*/
IPPAPI(IppStatus, ippsResamplePolyphaseInit_16s, (Ipp32f window, int nStep, Ipp32f rollf, Ipp32f alpha, IppsResamplingPolyphase_16s* pSpec, IppHintAlgorithm hint))
IPPAPI(IppStatus, ippsResamplePolyphaseInit_32f, (Ipp32f window, int nStep, Ipp32f rollf, Ipp32f alpha, IppsResamplingPolyphase_32f* pSpec, IppHintAlgorithm hint))

IPPAPI(IppStatus, ippsResamplePolyphaseFixedInit_16s, (int inRate, int outRate, int len, Ipp32f rollf, Ipp32f alpha, IppsResamplingPolyphaseFixed_16s* pSpec, IppHintAlgorithm hint))
IPPAPI(IppStatus, ippsResamplePolyphaseFixedInit_32f, (int inRate, int outRate, int len, Ipp32f rollf, Ipp32f alpha, IppsResamplingPolyphaseFixed_32f* pSpec, IppHintAlgorithm hint))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippsResamplePolyphaseSetFixedFilter
//  Purpose:        Set filter coefficient
//   Arguments:
//      pSpec           The pointer to the resampling specification structure to be created.
//      pSrc            Input vector of filter coefficients [height][step]
//      step            Lenght of filter
//      height          Number of filter
//   Return Value
//      ippStsNoErr       Indicates no error.
//      ippStsNullPtrErr  Indicates an error when pSpec or pSrc are NULL.
//      ippStsSizeErr     Indicates an error when step or height is less than or equal to 0.
*/
IPPAPI(IppStatus, ippsResamplePolyphaseSetFixedFilter_16s, (const Ipp16s* pSrc, int step, int height, IppsResamplingPolyphaseFixed_16s* pSpec))
IPPAPI(IppStatus, ippsResamplePolyphaseSetFixedFilter_32f, (const Ipp32f* pSrc, int step, int height, IppsResamplingPolyphaseFixed_32f* pSpec))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippsResamplePolyphaseGetFixedFilter
//  Purpose:        Get filter coefficient
//   Arguments:
//      pSpec           The pointer to the resampling specification structure to be created.
//      pDst            Input vector of filter coefficients [height][step]
//      step            Lenght of filter
//      height          Number of filter
//   Return Value
//      ippStsNoErr       Indicates no error.
//      ippStsNullPtrErr  Indicates an error when pSpec or pSrc are NULL.
//      ippStsSizeErr     Indicates an error when step or height is less than or equal to 0.
*/
IPPAPI(IppStatus, ippsResamplePolyphaseGetFixedFilter_16s, (Ipp16s* pDst, int step, int height, const IppsResamplingPolyphaseFixed_16s* pSpec))
IPPAPI(IppStatus, ippsResamplePolyphaseGetFixedFilter_32f, (Ipp32f* pDst, int step, int height, const IppsResamplingPolyphaseFixed_32f* pSpec))

/* /////////////////////////////////////////////////////////////////////////////
//                  IIRIIR filters (analogue of FILTFILT)
///////////////////////////////////////////////////////////////////////////// */

/* ////////////////////////////////////////////////////////////////////////////
//          Initialize IIRIIR state, calculate required memory buffer size
//////////////////////////////////////////////////////////////////////////// */

/* ////////////////////////////////////////////////////////////////////////////
//  Name:         ippsIIRIIRGetStateSize,
//                ippsIIRIIRInit
//  Purpose:      ippsIIRIIRGetStateSize - calculates the size of the IIRIIR State structure;
//                ippsIIRIIRInit         - initializes IIRIIR state structure
//                and delay line using external memory buffer;
//  Parameters:
//      pTaps       - pointer to the filter coefficients;
//      order       - order of the filter;
//      pDlyLine    - pointer to the delay line, can be NULL;
//      ppState     - double pointer to the IIRIIR state;
//      tapsFactor  - scaleFactor for taps (integer version);
//      pBufferSize - pointer where to store the calculated IIRIIR
//                                 State structure size (in bytes);
//   Return:
//      status      - status value returned, its value are
//         ippStsNullPtrErr   - pointer(s) ppState or pTaps is NULL;
//                              if IIRIIRInit is called with pDlyLine==NULL then
//                              it forms delay line itself that minimizes start-up
//                              and ending transients by matching initial
//                              conditions to remove DC offset at beginning
//                              and end of input vector.
//         ippStsIIROrderErr  - order <= 0
//         ippStsDivByZeroErr - a0 == 0.0 ( pTaps[order+1] == 0.0 )
//         ippStsNoErr        - otherwise
//  Note:
//    Order of taps = b0,b1,...,bN,a0,a1,...,aN
//    N = order
//    Delay line is in the Direct Form II format
//
*/
IPPAPI(IppStatus, ippsIIRIIRGetStateSize_32f,    (int order, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRIIRGetStateSize64f_32f, (int order, int *pBufferSize))
IPPAPI(IppStatus, ippsIIRIIRGetStateSize_64f,    (int order, int *pBufferSize))

IPPAPI(IppStatus, ippsIIRIIRInit64f_32f, (IppsIIRState64f_32f** ppState, const Ipp64f* pTaps, int order, const Ipp64f* pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRIIRInit_32f,    (IppsIIRState_32f**    ppState, const Ipp32f* pTaps, int order, const Ipp32f* pDlyLine, Ipp8u* pBuf))
IPPAPI(IppStatus, ippsIIRIIRInit_64f,    (IppsIIRState_64f**    ppState, const Ipp64f* pTaps, int order, const Ipp64f* pDlyLine, Ipp8u* pBuf))

/* /////////////////////////////////////////////////////////////////////////////
//                  IIRIIR Filtering
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Names:         ippsIIRIIR
//  Purpose:       performs zero-phase digital IIR filtering by processing
//   the input vector in both the forward and reverse directions. After filtering
//   the data in the forward direction, IIRIIR runs the filtered sequence in the
//   reverse (flipped) order back through the filter. The result has the following
//   characteristics:
//       - Zero-phase distortion
//       - A filter transfer function is equal to the squared magnitude of the
//         original IIR transfer function
//       - A filter order that is double the specified IIR order
//  Parameters:
//      pState              - pointer to filter context
//      pSrcDst             - pointer to input/output vector in in-place ops
//      pSrc                - pointer to input vector
//      pDst                - pointer to output vector
//      len                 - length of the vectors
//  Return:
//      ippStsContextMatchErr  - wrong context identifier
//      ippStsNullPtrErr       - pointer(s) to the data is NULL
//      ippStsLengthErr        - length of the vectors < 3*(IIR order)
//      ippStsNoErr            - otherwise
//
*/
IPPAPI(IppStatus, ippsIIRIIR_32f_I,   (                    Ipp32f *pSrcDst, int len, IppsIIRState_32f*    pState))
IPPAPI(IppStatus, ippsIIRIIR_32f,     (const Ipp32f *pSrc, Ipp32f *pDst,    int len, IppsIIRState_32f*    pState))
IPPAPI(IppStatus, ippsIIRIIR64f_32f_I,(                    Ipp32f *pSrcDst, int len, IppsIIRState64f_32f* pState))
IPPAPI(IppStatus, ippsIIRIIR64f_32f,  (const Ipp32f *pSrc, Ipp32f *pDst,    int len, IppsIIRState64f_32f* pState))
IPPAPI(IppStatus, ippsIIRIIR_64f_I,   (                    Ipp64f *pSrcDst, int len, IppsIIRState_64f*    pState))
IPPAPI(IppStatus, ippsIIRIIR_64f,     (const Ipp64f *pSrc, Ipp64f *pDst,    int len, IppsIIRState_64f*    pState))

/* /////////////////////////////////////////////////////////////////////////////
//                  IIRIIR - Work with Delay Line
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsIIRIIRGetDlyLine, ippsIIRIIRSetDlyLine
//  Purpose:    set or get delay line
//  Parameters:
//      pState              - pointer to IIR filter context
//      pDlyLine            - pointer where from load or where to store delay line
//  Return:
//      ippStsContextMatchErr  - wrong context identifier
//      ippStsNullPtrErr       - pointer(s) pState or pDelay is NULL
//                               if IIRIIRSet is called with pDlyLine==NULL then
//                               the function forms delay line itself that minimizes
//                               start-up and ending transients by matching initial
//                               conditions to remove DC offset at beginning
//                               and end of input vector.
//      ippStsNoErr            - otherwise
*/
IPPAPI(IppStatus, ippsIIRIIRGetDlyLine64f_32f, (const IppsIIRState64f_32f *pState,       Ipp64f *pDlyLine))
IPPAPI(IppStatus, ippsIIRIIRSetDlyLine64f_32f, (      IppsIIRState64f_32f *pState, const Ipp64f *pDlyLine))
IPPAPI(IppStatus, ippsIIRIIRGetDlyLine_32f,    (const IppsIIRState_32f    *pState,       Ipp32f *pDlyLine))
IPPAPI(IppStatus, ippsIIRIIRSetDlyLine_32f,    (      IppsIIRState_32f    *pState, const Ipp32f *pDlyLine))
IPPAPI(IppStatus, ippsIIRIIRGetDlyLine_64f,    (const IppsIIRState_64f    *pState,       Ipp64f *pDlyLine))
IPPAPI(IppStatus, ippsIIRIIRSetDlyLine_64f,    (      IppsIIRState_64f    *pState, const Ipp64f *pDlyLine))

/* /////////////////////////////////////////////////////////////////////////////
//                  Linear Transform
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//                  Definitions for FFT Functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//                  FFT Get Size Functions
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsFFTGetSize_C, ippsFFTGetSize_R
//  Purpose:    Computes the size of the FFT context structure and the size
of the required work buffer (in bytes)
//  Arguments:
//     order      Base-2 logarithm of the number of samples in FFT
//     flag       Flag to choose the results normalization factors
//     hint       Option to select the algorithmic implementation of the transform
//                function
//     pSizeSpec  Pointer to the size value of FFT specification structure
//     pSizeInit  Pointer to the size value of the buffer for FFT initialization function
//     pSizeBuf   Pointer to the size value of the FFT external work buffer
//  Return:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       At least one of pointers is NULL
//     ippStsFftOrderErr      FFT order value is illegal
//     ippStsFFTFlagErr       Incorrect normalization flag value
*/
IPPAPI(IppStatus, ippsFFTGetSize_C_32f, (int order, int flag, IppHintAlgorithm hint, int* pSpecSize, int* pSpecBufferSize, int* pBufferSize))
IPPAPI(IppStatus, ippsFFTGetSize_R_32f, (int order, int flag, IppHintAlgorithm hint, int* pSpecSize, int* pSpecBufferSize, int* pBufferSize))
IPPAPI(IppStatus, ippsFFTGetSize_C_32fc,(int order, int flag, IppHintAlgorithm hint, int* pSpecSize, int* pSpecBufferSize, int* pBufferSize))
IPPAPI(IppStatus, ippsFFTGetSize_C_64f, (int order, int flag, IppHintAlgorithm hint, int* pSpecSize, int* pSpecBufferSize, int* pBufferSize))
IPPAPI(IppStatus, ippsFFTGetSize_R_64f, (int order, int flag, IppHintAlgorithm hint, int* pSpecSize, int* pSpecBufferSize, int* pBufferSize))
IPPAPI(IppStatus, ippsFFTGetSize_C_64fc,(int order, int flag, IppHintAlgorithm hint, int* pSpecSize, int* pSpecBufferSize, int* pBufferSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsFFTInit_C, ippsFFTInit_R
//  Purpose:    Initializes the FFT context structure
//  Arguments:
//     order        Base-2 logarithm of the number of samples in FFT
//     flag         Flag to choose the results normalization factors
//     hint         Option to select the algorithmic implementation of the transform
//                  function
//     ppFFTSpec    Double pointer to the FFT specification structure to be created
//     pSpec        Pointer to the FFT specification structure
//     pSpecBuffer  Pointer to the temporary work buffer
//  Return:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       At least one of pointers is NULL
//     ippStsFftOrderErr      FFT order value is illegal
//     ippStsFFTFlagErr       Incorrect normalization flag value
*/

IPPAPI(IppStatus, ippsFFTInit_C_32f, (IppsFFTSpec_C_32f**  ppFFTSpec, int order, int flag, IppHintAlgorithm hint, Ipp8u* pSpec, Ipp8u* pSpecBuffer))
IPPAPI(IppStatus, ippsFFTInit_R_32f, (IppsFFTSpec_R_32f**  ppFFTSpec, int order, int flag, IppHintAlgorithm hint, Ipp8u* pSpec, Ipp8u* pSpecBuffer))
IPPAPI(IppStatus, ippsFFTInit_C_32fc,(IppsFFTSpec_C_32fc** ppFFTSpec, int order, int flag, IppHintAlgorithm hint, Ipp8u* pSpec, Ipp8u* pSpecBuffer))
IPPAPI(IppStatus, ippsFFTInit_C_64f, (IppsFFTSpec_C_64f**  ppFFTSpec, int order, int flag, IppHintAlgorithm hint, Ipp8u* pSpec, Ipp8u* pSpecBuffer))
IPPAPI(IppStatus, ippsFFTInit_R_64f, (IppsFFTSpec_R_64f**  ppFFTSpec, int order, int flag, IppHintAlgorithm hint, Ipp8u* pSpec, Ipp8u* pSpecBuffer))
IPPAPI(IppStatus, ippsFFTInit_C_64fc,(IppsFFTSpec_C_64fc** ppFFTSpec, int order, int flag, IppHintAlgorithm hint, Ipp8u* pSpec, Ipp8u* pSpecBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//                  FFT Complex Transforms
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsFFTFwd_CToC, ippsFFTInv_CToC
//  Purpose:    Computes forward and inverse FFT of a complex signal
//  Arguments:
//     pFFTSpec     Pointer to the FFT context
//     pSrc         Pointer to the source complex signal
//     pDst         Pointer to the destination complex signal
//     pSrcRe       Pointer to the real      part of source signal
//     pSrcIm       Pointer to the imaginary part of source signal
//     pDstRe       Pointer to the real      part of destination signal
//     pDstIm       Pointer to the imaginary part of destination signal
//     pSrcDst      Pointer to the complex signal
//     pSrcDstRe    Pointer to the real      part of signal
//     pSrcDstIm    Pointer to the imaginary part of signal
//     pBuffer      Pointer to the work buffer
//     scaleFactor  Scale factor for output result
//  Return:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       At least one of pointers is NULL
//     ippStsContextMatchErr  Invalid context structure
//     ippStsMemAllocErr      Memory allocation fails
*/
IPPAPI(IppStatus, ippsFFTFwd_CToC_32fc,   (const Ipp32fc* pSrc, Ipp32fc* pDst, const IppsFFTSpec_C_32fc* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTInv_CToC_32fc,   (const Ipp32fc* pSrc, Ipp32fc* pDst, const IppsFFTSpec_C_32fc* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTFwd_CToC_64fc,   (const Ipp64fc* pSrc, Ipp64fc* pDst, const IppsFFTSpec_C_64fc* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTInv_CToC_64fc,   (const Ipp64fc* pSrc, Ipp64fc* pDst, const IppsFFTSpec_C_64fc* pFFTSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippsFFTFwd_CToC_32fc_I, (Ipp32fc* pSrcDst, const IppsFFTSpec_C_32fc* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTInv_CToC_32fc_I, (Ipp32fc* pSrcDst, const IppsFFTSpec_C_32fc* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTFwd_CToC_64fc_I, (Ipp64fc* pSrcDst, const IppsFFTSpec_C_64fc* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTInv_CToC_64fc_I, (Ipp64fc* pSrcDst, const IppsFFTSpec_C_64fc* pFFTSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippsFFTFwd_CToC_32f_I,  (Ipp32f* pSrcDstRe, Ipp32f* pSrcDstIm, const IppsFFTSpec_C_32f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTInv_CToC_32f_I,  (Ipp32f* pSrcDstRe, Ipp32f* pSrcDstIm, const IppsFFTSpec_C_32f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTFwd_CToC_64f_I,  (Ipp64f* pSrcDstRe, Ipp64f* pSrcDstIm, const IppsFFTSpec_C_64f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTInv_CToC_64f_I,  (Ipp64f* pSrcDstRe, Ipp64f* pSrcDstIm, const IppsFFTSpec_C_64f* pFFTSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippsFFTFwd_CToC_32f,    (const Ipp32f* pSrcRe, const Ipp32f* pSrcIm, Ipp32f* pDstRe, Ipp32f* pDstIm, const IppsFFTSpec_C_32f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTInv_CToC_32f,    (const Ipp32f* pSrcRe, const Ipp32f* pSrcIm, Ipp32f* pDstRe, Ipp32f* pDstIm, const IppsFFTSpec_C_32f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTFwd_CToC_64f,    (const Ipp64f* pSrcRe, const Ipp64f* pSrcIm, Ipp64f* pDstRe, Ipp64f* pDstIm, const IppsFFTSpec_C_64f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTInv_CToC_64f,    (const Ipp64f* pSrcRe, const Ipp64f* pSrcIm, Ipp64f* pDstRe, Ipp64f* pDstIm, const IppsFFTSpec_C_64f* pFFTSpec, Ipp8u* pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//                  FFT Real Packed Transforms
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsFFTFwd_RToPerm, ippsFFTFwd_RToPack, ippsFFTFwd_RToCCS
//              ippsFFTInv_PermToR, ippsFFTInv_PackToR, ippsFFTInv_CCSToR
//  Purpose:    Computes forward and inverse FFT of a real signal
//              using Perm, Pack or Ccs packed format
//  Arguments:
//     pFFTSpec       Pointer to the FFT context
//     pSrc           Pointer to the source signal
//     pDst           Pointer to thedestination signal
//     pSrcDst        Pointer to the source/destination signal (in-place)
//     pBuffer        Pointer to the work buffer
//     scaleFactor    Scale factor for output result
//  Return:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       At least one of pointers is NULL
//     ippStsContextMatchErr  Invalid context structure
//     ippStsMemAllocErr      Memory allocation fails
*/
IPPAPI(IppStatus, ippsFFTFwd_RToPerm_32f_I, (Ipp32f* pSrcDst, const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTFwd_RToPack_32f_I, (Ipp32f* pSrcDst, const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTFwd_RToCCS_32f_I,  (Ipp32f* pSrcDst, const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTInv_PermToR_32f_I, (Ipp32f* pSrcDst, const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTInv_PackToR_32f_I, (Ipp32f* pSrcDst, const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTInv_CCSToR_32f_I,  (Ipp32f* pSrcDst, const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTFwd_RToPerm_64f_I, (Ipp64f* pSrcDst, const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTFwd_RToPack_64f_I, (Ipp64f* pSrcDst, const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTFwd_RToCCS_64f_I,  (Ipp64f* pSrcDst, const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTInv_PermToR_64f_I, (Ipp64f* pSrcDst, const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTInv_PackToR_64f_I, (Ipp64f* pSrcDst, const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTInv_CCSToR_64f_I,  (Ipp64f* pSrcDst, const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippsFFTFwd_RToPerm_32f, (const Ipp32f* pSrc, Ipp32f* pDst, const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTFwd_RToPack_32f, (const Ipp32f* pSrc, Ipp32f* pDst, const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTFwd_RToCCS_32f,  (const Ipp32f* pSrc, Ipp32f* pDst, const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTInv_PermToR_32f, (const Ipp32f* pSrc, Ipp32f* pDst, const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTInv_PackToR_32f, (const Ipp32f* pSrc, Ipp32f* pDst, const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTInv_CCSToR_32f,  (const Ipp32f* pSrc, Ipp32f* pDst, const IppsFFTSpec_R_32f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTFwd_RToPerm_64f, (const Ipp64f* pSrc, Ipp64f* pDst, const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTFwd_RToPack_64f, (const Ipp64f* pSrc, Ipp64f* pDst, const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTFwd_RToCCS_64f,  (const Ipp64f* pSrc, Ipp64f* pDst, const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTInv_PermToR_64f, (const Ipp64f* pSrc, Ipp64f* pDst, const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTInv_PackToR_64f, (const Ipp64f* pSrc, Ipp64f* pDst, const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsFFTInv_CCSToR_64f,  (const Ipp64f* pSrc, Ipp64f* pDst, const IppsFFTSpec_R_64f* pFFTSpec, Ipp8u* pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//                  Definitions for DFT Functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//                  DFT Context Functions
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDFTGetSize_C, ippsDFTGetSize_R
//  Purpose:    Computes the size of the DFT context structure and the size
of the required work buffer (in bytes)
//  Arguments:
//     length     Length of the DFT transform
//     flag       Flag to choose the results normalization factors
//     hint       Option to select the algorithmic implementation of the transform
//                function
//     pSizeSpec  Pointer to the size value of DFT specification structure
//     pSizeInit  Pointer to the size value of the buffer for DFT initialization function
//     pSizeBuf   Pointer to the size value of the DFT external work buffer
//  Return:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       At least one of pointers is NULL
//     ippStsOrderErr         Invalid length value
//     ippStsFFTFlagErr       Incorrect normalization flag value
//     ippStsSizeErr          Indicates an error when length is less than or equal to 0
*/
IPPAPI(IppStatus, ippsDFTGetSize_C_32f, (int length, int flag, IppHintAlgorithm hint, int* pSizeSpec, int* pSizeInit, int* pSizeBuf))
IPPAPI(IppStatus, ippsDFTGetSize_R_32f, (int length, int flag, IppHintAlgorithm hint, int* pSizeSpec, int* pSizeInit, int* pSizeBuf))
IPPAPI(IppStatus, ippsDFTGetSize_C_32fc,(int length, int flag, IppHintAlgorithm hint, int* pSizeSpec, int* pSizeInit, int* pSizeBuf))
IPPAPI(IppStatus, ippsDFTGetSize_C_64f, (int length, int flag, IppHintAlgorithm hint, int* pSizeSpec, int* pSizeInit, int* pSizeBuf))
IPPAPI(IppStatus, ippsDFTGetSize_R_64f, (int length, int flag, IppHintAlgorithm hint, int* pSizeSpec, int* pSizeInit, int* pSizeBuf))
IPPAPI(IppStatus, ippsDFTGetSize_C_64fc,(int length, int flag, IppHintAlgorithm hint, int* pSizeSpec, int* pSizeInit, int* pSizeBuf))

/* /////////////////////////////////////////////////////////////////////////////
//                  DFT Init Functions
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDFTInit_C, ippsDFTInit_R
//  Purpose:    initialize of DFT context
//  Arguments:
//     length     Length of the DFT transform
//     flag       Flag to choose the results normalization factors
//     hint       Option to select the algorithmic implementation of the transform
//                function
//     pDFTSpec   Double pointer to the DFT context structure
//     pMemInit   Pointer to initialization buffer
//  Return:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       At least one of pointers is NULL
//     ippStsOrderErr         Invalid length value
//     ippStsFFTFlagErr       Incorrect normalization flag value
//     ippStsSizeErr          Indicates an error when length is less than or equal to 0
*/
IPPAPI(IppStatus, ippsDFTInit_C_32f, (int length, int flag, IppHintAlgorithm hint, IppsDFTSpec_C_32f*  pDFTSpec, Ipp8u* pMemInit))
IPPAPI(IppStatus, ippsDFTInit_R_32f, (int length, int flag, IppHintAlgorithm hint, IppsDFTSpec_R_32f*  pDFTSpec, Ipp8u* pMemInit))
IPPAPI(IppStatus, ippsDFTInit_C_32fc,(int length, int flag, IppHintAlgorithm hint, IppsDFTSpec_C_32fc* pDFTSpec, Ipp8u* pMemInit))
IPPAPI(IppStatus, ippsDFTInit_C_64f, (int length, int flag, IppHintAlgorithm hint, IppsDFTSpec_C_64f*  pDFTSpec, Ipp8u* pMemInit))
IPPAPI(IppStatus, ippsDFTInit_R_64f, (int length, int flag, IppHintAlgorithm hint, IppsDFTSpec_R_64f*  pDFTSpec, Ipp8u* pMemInit))
IPPAPI(IppStatus, ippsDFTInit_C_64fc,(int length, int flag, IppHintAlgorithm hint, IppsDFTSpec_C_64fc* pDFTSpec, Ipp8u* pMemInit))

/* /////////////////////////////////////////////////////////////////////////////
//                  DFT Complex Transforms
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDFTFwd_CToC, ippsDFTInv_CToC
//  Purpose:    Computes forward and inverse DFT of a complex signal
//  Arguments:
//     pDFTSpec     Pointer to the DFT context
//     pSrc         Pointer to the source complex signal
//     pDst         Pointer to the destination complex signal
//     pSrcRe       Pointer to the real      part of source signal
//     pSrcIm       Pointer to the imaginary part of source signal
//     pDstRe       Pointer to the real      part of destination signal
//     pDstIm       Pointer to the imaginary part of destination signal
//     pBuffer      Pointer to the work buffer
//     scaleFactor  Scale factor for output result
//  Return:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       At least one of pointers is NULL
//     ippStsContextMatchErr  Invalid context structure
//     ippStsMemAllocErr      Memory allocation fails
*/
IPPAPI(IppStatus, ippsDFTFwd_CToC_32fc, (const Ipp32fc* pSrc, Ipp32fc* pDst, const IppsDFTSpec_C_32fc* pDFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsDFTInv_CToC_32fc, (const Ipp32fc* pSrc, Ipp32fc* pDst, const IppsDFTSpec_C_32fc* pDFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsDFTFwd_CToC_64fc, (const Ipp64fc* pSrc, Ipp64fc* pDst, const IppsDFTSpec_C_64fc* pDFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsDFTInv_CToC_64fc, (const Ipp64fc* pSrc, Ipp64fc* pDst, const IppsDFTSpec_C_64fc* pDFTSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippsDFTFwd_CToC_32f, (const Ipp32f* pSrcRe, const Ipp32f* pSrcIm, Ipp32f* pDstRe, Ipp32f* pDstIm, const IppsDFTSpec_C_32f* pDFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsDFTInv_CToC_32f, (const Ipp32f* pSrcRe, const Ipp32f* pSrcIm, Ipp32f* pDstRe, Ipp32f* pDstIm, const IppsDFTSpec_C_32f* pDFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsDFTFwd_CToC_64f, (const Ipp64f* pSrcRe, const Ipp64f* pSrcIm, Ipp64f* pDstRe, Ipp64f* pDstIm, const IppsDFTSpec_C_64f* pDFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsDFTInv_CToC_64f, (const Ipp64f* pSrcRe, const Ipp64f* pSrcIm, Ipp64f* pDstRe, Ipp64f* pDstIm, const IppsDFTSpec_C_64f* pDFTSpec, Ipp8u* pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//                  DFT Real Packed Transforms
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDFTFwd_RToPerm, ippsDFTFwd_RToPack, ippsDFTFwd_RToCCS
//              ippsDFTInv_PermToR, ippsDFTInv_PackToR, ippsDFTInv_CCSToR
//  Purpose:    Compute forward and inverse DFT of a real signal
//              using Perm, Pack or Ccs packed format
//  Arguments:
//     pFFTSpec       Pointer to the DFT context
//     pSrc           Pointer to the source signal
//     pDst           Pointer to the destination signal
//     pSrcDst        Pointer to the source/destination signal (in-place)
//     pBuffer        Pointer to the work buffer
//     scaleFactor    Scale factor for output result
//  Return:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       At least one of pointers is NULL
//     ippStsContextMatchErr  Invalid context structure
//     ippStsMemAllocErr      Memory allocation fails
*/
IPPAPI(IppStatus, ippsDFTFwd_RToPerm_32f, (const Ipp32f* pSrc, Ipp32f* pDst, const IppsDFTSpec_R_32f* pDFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsDFTFwd_RToPack_32f, (const Ipp32f* pSrc, Ipp32f* pDst, const IppsDFTSpec_R_32f* pDFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsDFTFwd_RToCCS_32f,  (const Ipp32f* pSrc, Ipp32f* pDst, const IppsDFTSpec_R_32f* pDFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsDFTInv_PermToR_32f, (const Ipp32f* pSrc, Ipp32f* pDst, const IppsDFTSpec_R_32f* pDFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsDFTInv_PackToR_32f, (const Ipp32f* pSrc, Ipp32f* pDst, const IppsDFTSpec_R_32f* pDFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsDFTInv_CCSToR_32f,  (const Ipp32f* pSrc, Ipp32f* pDst, const IppsDFTSpec_R_32f* pDFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsDFTFwd_RToPerm_64f, (const Ipp64f* pSrc, Ipp64f* pDst, const IppsDFTSpec_R_64f* pDFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsDFTFwd_RToPack_64f, (const Ipp64f* pSrc, Ipp64f* pDst, const IppsDFTSpec_R_64f* pDFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsDFTFwd_RToCCS_64f,  (const Ipp64f* pSrc, Ipp64f* pDst, const IppsDFTSpec_R_64f* pDFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsDFTInv_PermToR_64f, (const Ipp64f* pSrc, Ipp64f* pDst, const IppsDFTSpec_R_64f* pDFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsDFTInv_PackToR_64f, (const Ipp64f* pSrc, Ipp64f* pDst, const IppsDFTSpec_R_64f* pDFTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsDFTInv_CCSToR_64f,  (const Ipp64f* pSrc, Ipp64f* pDst, const IppsDFTSpec_R_64f* pDFTSpec, Ipp8u* pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//              Vector multiplication in RCPack and in RCPerm formats
///////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////////
//  Names:              ippsMulPack, ippsMulPerm
//  Purpose:            multiply two vectors stored in RCPack and RCPerm formats
//  Parameters:
//   pSrc               pointer to input vector (in-place case)
//   pSrcDst            pointer to output vector (in-place case)
//   pSrc1              pointer to first input vector
//   pSrc2              pointer to second input vector
//   pDst               pointer to output vector
//   len                vector's length
//   scaleFactor        scale factor
//  Return:
//   ippStsNullPtrErr      pointer(s) to the data is NULL
//   ippStsSizeErr         vector`s length is less or equal zero
//   ippStsNoErr           otherwise
*/
IPPAPI(IppStatus, ippsMulPack_32f_I, (const Ipp32f* pSrc,                       Ipp32f* pSrcDst, int len))
IPPAPI(IppStatus, ippsMulPerm_32f_I, (const Ipp32f* pSrc,                       Ipp32f* pSrcDst, int len))
IPPAPI(IppStatus, ippsMulPack_32f,   (const Ipp32f* pSrc1, const Ipp32f* pSrc2, Ipp32f* pDst,    int len))
IPPAPI(IppStatus, ippsMulPerm_32f,   (const Ipp32f* pSrc1, const Ipp32f* pSrc2, Ipp32f* pDst,    int len))
IPPAPI(IppStatus, ippsMulPack_64f_I, (const Ipp64f* pSrc,                       Ipp64f* pSrcDst, int len))
IPPAPI(IppStatus, ippsMulPerm_64f_I, (const Ipp64f* pSrc,                       Ipp64f* pSrcDst, int len))
IPPAPI(IppStatus, ippsMulPack_64f,   (const Ipp64f* pSrc1, const Ipp64f* pSrc2, Ipp64f* pDst,    int len))
IPPAPI(IppStatus, ippsMulPerm_64f,   (const Ipp64f* pSrc1, const Ipp64f* pSrc2, Ipp64f* pDst,    int len))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:              ippsMulPackConj
//  Purpose:            multiply on a complex conjugate vector and store in RCPack format
//  Parameters:
//   pSrc               pointer to input vector (in-place case)
//   pSrcDst            pointer to output vector (in-place case)
//   len                vector's length
//  Return:
//   ippStsNullPtrErr      pointer(s) to the data is NULL
//   ippStsSizeErr         vector`s length is less or equal zero
//   ippStsNoErr           otherwise
*/
IPPAPI(IppStatus, ippsMulPackConj_32f_I, (const Ipp32f* pSrc, Ipp32f* pSrcDst, int len))
IPPAPI(IppStatus, ippsMulPackConj_64f_I, (const Ipp64f* pSrc, Ipp64f* pSrcDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:        ippsGoertz
//  Purpose:      compute DFT for single frequency (Goertzel algorithm)
//  Parameters:
//    freq                 single relative frequency value [0, 1.0)
//    pSrc                 pointer to the input vector
//    len                  length of the vector
//    pVal                 pointer to the DFT result value computed
//    scaleFactor          scale factor value
//  Return:
//    ippStsNullPtrErr        pointer to the data is NULL
//    ippStsSizeErr           length of the vector is less or equal zero
//    ippStsRelFreqErr        frequency value out of range
//    ippStsNoErr             otherwise
*/
IPPAPI(IppStatus, ippsGoertz_16s_Sfs, (const Ipp16s*  pSrc, int len, Ipp16sc* pVal, Ipp32f rFreq, int scaleFactor))
IPPAPI(IppStatus, ippsGoertz_16sc_Sfs,(const Ipp16sc* pSrc, int len, Ipp16sc* pVal, Ipp32f rFreq, int scaleFactor))
IPPAPI(IppStatus, ippsGoertz_32f,     (const Ipp32f*  pSrc, int len, Ipp32fc* pVal, Ipp32f rFreq))
IPPAPI(IppStatus, ippsGoertz_32fc,    (const Ipp32fc* pSrc, int len, Ipp32fc* pVal, Ipp32f rFreq))
IPPAPI(IppStatus, ippsGoertz_64f,     (const Ipp64f*  pSrc, int len, Ipp64fc* pVal, Ipp64f rFreq))
IPPAPI(IppStatus, ippsGoertz_64fc,    (const Ipp64fc* pSrc, int len, Ipp64fc* pVal, Ipp64f rFreq))

/* /////////////////////////////////////////////////////////////////////////////
//                  Definitions for DCT Functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//                  DCT Get Size Functions
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDCTFwdGetSize, ippsDCTInvGetSize
//  Purpose:    get sizes of the DCTSpec and buffers (in bytes)
//  Arguments:
//     len             - number of samples in DCT
//     hint            - code specific use hints
//     pSpecSize       - where write size of DCTSpec
//     pSpecBufferSize - where write size of buffer for DCTInit functions
//     pBufferSize     - where write size of buffer for DCT calculation
//  Return:
//     ippStsNoErr            no errors
//     ippStsNullPtrErr       pSpecSize == NULL or pSpecBufferSize == NULL or
//                            pBufferSize == NULL
//     ippStsSizeErr          bad the len value
*/
IPPAPI(IppStatus, ippsDCTFwdGetSize_32f, (int len, IppHintAlgorithm hint, int* pSpecSize, int* pSpecBufferSize, int* pBufferSize))
IPPAPI(IppStatus, ippsDCTInvGetSize_32f, (int len, IppHintAlgorithm hint, int* pSpecSize, int* pSpecBufferSize, int* pBufferSize))
IPPAPI(IppStatus, ippsDCTFwdGetSize_64f, (int len, IppHintAlgorithm hint, int* pSpecSize, int* pSpecBufferSize, int* pBufferSize))
IPPAPI(IppStatus, ippsDCTInvGetSize_64f, (int len, IppHintAlgorithm hint, int* pSpecSize, int* pSpecBufferSize, int* pBufferSize))

/* /////////////////////////////////////////////////////////////////////////////
//                  DCT Context Functions
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDCTFwdInit, ippsDCTInvInit
//  Purpose:    initialize of DCT context
//  Arguments:
//     len         - number of samples in DCT
//     hint        - code specific use hints
//     ppDCTSpec   - where write pointer to new context
//     pSpec       - pointer to area for DCTSpec
//     pSpecBuffer - pointer to work buffer
//  Return:
//     ippStsNoErr            no errors
//     ippStsNullPtrErr       ppDCTSpec == NULL or
//                            pSpec == NULL or pMemInit == NULL
//     ippStsSizeErr          bad the len value
*/
IPPAPI(IppStatus, ippsDCTFwdInit_32f, (IppsDCTFwdSpec_32f** ppDCTSpec, int len, IppHintAlgorithm hint, Ipp8u* pSpec, Ipp8u* pSpecBuffer))
IPPAPI(IppStatus, ippsDCTInvInit_32f, (IppsDCTInvSpec_32f** ppDCTSpec, int len, IppHintAlgorithm hint, Ipp8u* pSpec, Ipp8u* pSpecBuffer))
IPPAPI(IppStatus, ippsDCTFwdInit_64f, (IppsDCTFwdSpec_64f** ppDCTSpec, int len, IppHintAlgorithm hint, Ipp8u* pSpec, Ipp8u* pSpecBuffer))
IPPAPI(IppStatus, ippsDCTInvInit_64f, (IppsDCTInvSpec_64f** ppDCTSpec, int len, IppHintAlgorithm hint, Ipp8u* pSpec, Ipp8u* pSpecBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//                  DCT Transforms
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDCTFwd, ippsDCTInv
//  Purpose:    compute forward and inverse DCT of signal
//  Arguments:
//     pDCTSpec - pointer to DCT context
//     pSrc     - pointer to source signal
//     pDst     - pointer to destination signal
//     pSrcDst  - pointer to signal
//     pBuffer  - pointer to work buffer
//     scaleFactor
//              - scale factor for output result
//  Return:
//     ippStsNoErr            no errors
//     ippStsNullPtrErr       pDCTSpec == NULL or
//                            pSrc == NULL or pDst == NULL or pSrcDst == NULL
//     ippStsContextMatchErr  bad context identifier
//     ippStsMemAllocErr      memory allocation error
*/
IPPAPI(IppStatus, ippsDCTFwd_32f_I, (                    Ipp32f* pSrcDst, const IppsDCTFwdSpec_32f* pDCTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsDCTInv_32f_I, (                    Ipp32f* pSrcDst, const IppsDCTInvSpec_32f* pDCTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsDCTFwd_32f,   (const Ipp32f* pSrc, Ipp32f* pDst,    const IppsDCTFwdSpec_32f* pDCTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsDCTInv_32f,   (const Ipp32f* pSrc, Ipp32f* pDst,    const IppsDCTInvSpec_32f* pDCTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsDCTFwd_64f_I, (                    Ipp64f* pSrcDst, const IppsDCTFwdSpec_64f* pDCTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsDCTInv_64f_I, (                    Ipp64f* pSrcDst, const IppsDCTInvSpec_64f* pDCTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsDCTFwd_64f,   (const Ipp64f* pSrc, Ipp64f* pDst,    const IppsDCTFwdSpec_64f* pDCTSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsDCTInv_64f,   (const Ipp64f* pSrc, Ipp64f* pDst,    const IppsDCTInvSpec_64f* pDCTSpec, Ipp8u* pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//                  Definitions for Hilbert Functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
// Name:       ippsHilbertGetSize
// Purpose:    Get sizes (in bytes) of the IppsHilbertSpec spec structure and temporary buffer.
// Parameters:
//    length      - Number of samples in Hilbert.
//    hint        - Option to select the algorithmic implementation of the transform function (DFT).
//    pSpecSize   - Pointer to the calculated spec size (in bytes).
//    pSizeBuf    - Pointer to the calculated size of the external work buffer.
//  Returns:
//    ippStsNoErr       - OK.
//    ippStsNullPtrErr  - Error when any of the specified pointers is NULL.
//    ippStsSizeErr     - Error when length is less than 1.
*/
IPPAPI(IppStatus, ippsHilbertGetSize_32f32fc, (int length, IppHintAlgorithm hint, int *pSpecSize, int *pBufferSize))
IPPAPI(IppStatus, ippsHilbertGetSize_64f64fc, (int length, IppHintAlgorithm hint, int *pSpecSize, int *pBufferSize))

/* /////////////////////////////////////////////////////////////////////////////
// Name:       ippsHilbertInit
// Purpose:    initializes Hilbert context structure.
// Parameters:
//    length      - Number of samples in Hilbert.
//    hint        - Option to select the algorithmic implementation of the transform function (DFT).
//    pSpec       - Pointer to Hilbert context.
//    pBuffer     - Pointer to the buffer for internal calculations.
//  Returns:
//    ippStsNoErr       - OK.
//    ippStsNullPtrErr  - Error when any of the specified pointers is NULL.
//    ippStsSizeErr     - Error when length is less than 1.
*/
IPPAPI(IppStatus, ippsHilbertInit_32f32fc, (int length, IppHintAlgorithm hint, IppsHilbertSpec *pSpec, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsHilbertInit_64f64fc, (int length, IppHintAlgorithm hint, IppsHilbertSpec *pSpec, Ipp8u *pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
// Name:       ippsHilbert
// Purpose:    Computes Hilbert transform of the real signal.
// Arguments:
//    pSrc         - Pointer to source real signal
//    pDst         - Pointer to destination complex signal
//    pSpec        - Pointer to Hilbert context.
//    pBuffer      - Pointer to the buffer for internal calculations.
//    scaleFactor  - Scale factor for output signal.
// Return:
//    ippStsNoErr           - OK.
//    ippStsNullPtrErr      - Error when any of the specified pointers is NULL.
//    ippStsContextMatchErr - Error when pSpec initialized incorect.
*/
IPPAPI(IppStatus, ippsHilbert_32f32fc, (const Ipp32f *pSrc, Ipp32fc *pDst, IppsHilbertSpec *pSpec, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsHilbert_64f64fc, (const Ipp64f *pSrc, Ipp64fc *pDst, IppsHilbertSpec *pSpec, Ipp8u *pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//          Wavelet Transform Functions for Fixed Filter Banks
///////////////////////////////////////////////////////////////////////////// */
/* //////////////////////////////////////////////////////////////////////
// Name:       ippsWTHaar
// Purpose:    one level Haar Wavelet Transform
// Arguments:
//   pSrc        - source vector;
//   len         - length of source vector;
//   pDstLow     - coarse "low frequency" component destination;
//   pDstHigh    - detail "high frequency" component destination;
//   pSrcLow     - coarse "low frequency" component source;
//   pSrcHigh    - detail "high frequency" component source;
//   pDst        - destination vector;
//   scaleFactor - scale factor value
//  Return:
//   ippStsNullPtrErr    pointer(s) to the data vector is NULL
//   ippStsSizeErr       the length is less or equal zero
//   ippStsNoErr         otherwise
*/
IPPAPI(IppStatus, ippsWTHaarFwd_16s_Sfs, (const Ipp16s* pSrc, int len, Ipp16s* pDstLow, Ipp16s* pDstHigh, int scaleFactor))
IPPAPI(IppStatus, ippsWTHaarFwd_32f,     (const Ipp32f* pSrc, int len, Ipp32f* pDstLow, Ipp32f* pDstHigh))
IPPAPI(IppStatus, ippsWTHaarFwd_64f,     (const Ipp64f* pSrc, int len, Ipp64f* pDstLow, Ipp64f* pDstHigh))

IPPAPI(IppStatus, ippsWTHaarInv_16s_Sfs, (const Ipp16s* pSrcLow, const Ipp16s* pSrcHigh, Ipp16s* pDst, int len, int scaleFactor))
IPPAPI(IppStatus, ippsWTHaarInv_32f,     (const Ipp32f* pSrcLow, const Ipp32f* pSrcHigh, Ipp32f* pDst, int len))
IPPAPI(IppStatus, ippsWTHaarInv_64f,     (const Ipp64f* pSrcLow, const Ipp64f* pSrcHigh, Ipp64f* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//          Wavelet Transform Fucntions for User Filter Banks
///////////////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////////
// Name:        ippsWTFwdGetSize
//
// Purpose:      Get sizes, in bytes, of the ippsWTFwd state structure.
//
// Parameters:
//   srcType   - Data type of the source vector.
//   lenLow    - Length of lowpass filter.
//   offsLow   - Input delay of lowpass filter.
//   lenHigh   - Length of highpass filter.
//   offsHigh  - Input delay of highpass filter.
//   pStateSize- Pointer to the size of the ippsWTFwd state structure (in bytes).
//
// Returns:
//   ippStsNoErr        - Ok.
//   ippStsNullPtrErr   - Error when any of the specified pointers is NULL.
//   ippStsSizeErr      - Error when filters length is negative, or equal to zero.
//   ippStsWtOffsetErr  - Error when filter delay is less than (-1).
*/
IPPAPI(IppStatus, ippsWTFwdGetSize, (IppDataType srcType, int lenLow, int offsLow, int lenHigh, int offsHigh, int* pStateSize))

/* //////////////////////////////////////////////////////////////////////
// Name:        ippsWTFwdInit
//
// Purpose:     Initialize forward wavelet transform state structure.
//
// Parameters:
//   pState    - Pointer to allocated ippsWTFwd state structure.
//   pTapsLow  - Pointer to lowpass filter taps.
//   lenLow    - Length of lowpass filter.
//   offsLow   - Input delay of lowpass filter.
//   pTapsHigh - Pointer to highpass filter taps.
//   lenHigh   - Length of highpass filter.
//   offsHigh  - Input delay of highpass filter.
//
// Returns:
//   ippStsNoErr        - Ok.
//   ippStsNullPtrErr   - Error when any of the specified pointers is NULL.
//   ippStsSizeErr      - Error when filters length is negative, or equal to zero.
//   ippStsWtOffsetErr  - Error when filter delay is less than (-1).
*/
IPPAPI(IppStatus, ippsWTFwdInit_8u32f,  (IppsWTFwdState_8u32f*  pState, const Ipp32f* pTapsLow, int lenLow, int offsLow, const Ipp32f* pTapsHigh, int lenHigh, int offsHigh))
IPPAPI(IppStatus, ippsWTFwdInit_16s32f, (IppsWTFwdState_16s32f* pState, const Ipp32f* pTapsLow, int lenLow, int offsLow, const Ipp32f* pTapsHigh, int lenHigh, int offsHigh))
IPPAPI(IppStatus, ippsWTFwdInit_16u32f, (IppsWTFwdState_16u32f* pState, const Ipp32f* pTapsLow, int lenLow, int offsLow, const Ipp32f* pTapsHigh, int lenHigh, int offsHigh))
IPPAPI(IppStatus, ippsWTFwdInit_32f,    (IppsWTFwdState_32f*    pState, const Ipp32f* pTapsLow, int lenLow, int offsLow, const Ipp32f* pTapsHigh, int lenHigh, int offsHigh))

/* //////////////////////////////////////////////////////////////////////
// Name:        ippsWTFwdSetDlyLine_32f, ippsWTFwdSetDlyLine_8s32f,
//              ippsWTFwdSetDlyLine_8u32f, ippsWTFwdSetDlyLine_16s32f,
//              ippsWTFwdSetDlyLine_16u32f
//
// Purpose:     The function copies the pointed vectors to internal delay lines.
//
// Parameters:
//   pState   - pointer to pState structure;
//   pDlyLow  - pointer to delay line for lowpass filtering;
//   pDlyHigh - pointer to delay line for highpass filtering.
//
// Returns:
//   ippStsNoErr            - Ok;
//   ippStsNullPtrErr       - some of pointers pDlyLow
//                              or pDlyHigh vectors are NULL;
//   ippStspStateMatchErr   - mismatch pState structure.
//
// Notes: lengths of delay lines:
//          len(pDlyLow)  = lenLow  + offsLow  - 1;
//          len(pDlyHigh) = lenHigh + offsHigh - 1;
//  lenLow, offsLow, lenHigh, offsHigh - parameters
//    for ippsWTFwdInitAlloc function.
*/
IPPAPI(IppStatus, ippsWTFwdSetDlyLine_8u32f,  (IppsWTFwdState_8u32f*  pState, const Ipp32f* pDlyLow, const Ipp32f* pDlyHigh))
IPPAPI(IppStatus, ippsWTFwdSetDlyLine_16s32f, (IppsWTFwdState_16s32f* pState, const Ipp32f* pDlyLow, const Ipp32f* pDlyHigh))
IPPAPI(IppStatus, ippsWTFwdSetDlyLine_16u32f, (IppsWTFwdState_16u32f* pState, const Ipp32f* pDlyLow, const Ipp32f* pDlyHigh))
IPPAPI(IppStatus, ippsWTFwdSetDlyLine_32f,    (IppsWTFwdState_32f*    pState, const Ipp32f* pDlyLow, const Ipp32f* pDlyHigh))

/* //////////////////////////////////////////////////////////////////////
// Name:        ippsWTFwdGetDlyLine_32f, ippsWTFwdGetDlyLine_8s32f,
//              ippsWTFwdGetDlyLine_8u32f, ippsWTFwdGetDlyLine_16s32f,
//              ippsWTFwdGetDlyLine_16u32f
//
// Purpose:     The function copies data from interanl delay lines
//                to the pointed vectors.
// Parameters:
//   pState   - pointer to pState structure;
//   pDlyLow  - pointer to delay line for lowpass filtering;
//   pDlyHigh - pointer to delay line for highpass filtering.
//
// Returns:
//   ippStsNoErr            - Ok;
//   ippStsNullPtrErr       - some of pointers pDlyLow
//                              or pDlyHigh vectors are NULL;
//   ippStspStateMatchErr   - mismatch pState structure.
//
// Notes: lengths of delay lines:
//          len(pDlyLow)  = lenLow  + offsLow  - 1;
//          len(pDlyHigh) = lenHigh + offsHigh - 1;
//  lenLow, offsLow, lenHigh, offsHigh - parameters
//    for ippsWTFwdInitAlloc function.
*/
IPPAPI(IppStatus, ippsWTFwdGetDlyLine_8u32f,  (IppsWTFwdState_8u32f*  pState, Ipp32f* pDlyLow, Ipp32f* pDlyHigh))
IPPAPI(IppStatus, ippsWTFwdGetDlyLine_16s32f, (IppsWTFwdState_16s32f* pState, Ipp32f* pDlyLow, Ipp32f* pDlyHigh))
IPPAPI(IppStatus, ippsWTFwdGetDlyLine_16u32f, (IppsWTFwdState_16u32f* pState, Ipp32f* pDlyLow, Ipp32f* pDlyHigh))
IPPAPI(IppStatus, ippsWTFwdGetDlyLine_32f,    (IppsWTFwdState_32f*    pState, Ipp32f* pDlyLow, Ipp32f* pDlyHigh))

/* //////////////////////////////////////////////////////////////////////
// Name:        ippsWTFwd_32f, ippsWTFwd_16s32f, ippsWTFwd_16u32f,
//              ippsWTFwd_8s32f, ippsWTFwd_8u32f
//
// Purpose:     Forward wavelet transform.
//
// Parameters:
//   pSrc     - pointer to source block of data;
//   pDstLow  - pointer to destination block of
//                "low-frequency" component;
//   pDstHigh - pointer to destination block of
//                "high-frequency" component;
//   dstLen   - length of destination;
//   pState    - pointer to pState structure.
//
//  Returns:
//   ippStsNoErr            - Ok;
//   ippStsNullPtrErr       - some of pointers to pSrc, pDstLow
//                              or pDstHigh vectors are NULL;
//   ippStsSizeErr          - the length is less or equal zero;
//   ippStspStateMatchErr    - mismatch pState structure.
//
// Notes:      source block length must be 2 * dstLen.
*/
IPPAPI(IppStatus, ippsWTFwd_8u32f,  (const Ipp8u*  pSrc, Ipp32f* pDstLow, Ipp32f* pDstHigh, int dstLen, IppsWTFwdState_8u32f*  pState))
IPPAPI(IppStatus, ippsWTFwd_16s32f, (const Ipp16s* pSrc, Ipp32f* pDstLow, Ipp32f* pDstHigh, int dstLen, IppsWTFwdState_16s32f* pState))
IPPAPI(IppStatus, ippsWTFwd_16u32f, (const Ipp16u* pSrc, Ipp32f* pDstLow, Ipp32f* pDstHigh, int dstLen, IppsWTFwdState_16u32f* pState))
IPPAPI(IppStatus, ippsWTFwd_32f,    (const Ipp32f* pSrc, Ipp32f* pDstLow, Ipp32f* pDstHigh, int dstLen, IppsWTFwdState_32f*    pState))

/* //////////////////////////////////////////////////////////////////////
// Name:        ippsWTInvGetSize
//
// Purpose:      Get sizes, in bytes, of the ippsWTInv state structure.
//
// Parameters:
//   dstType   - Data type of the destination vector.
//   lenLow    - Length of lowpass filter.
//   offsLow   - Input delay of lowpass filter.
//   lenHigh   - Length of highpass filter.
//   offsHigh  - Input delay of highpass filter.
//   pStateSize- Pointer to the size of the ippsWTInv state structure (in bytes).
//
// Returns:
//   ippStsNoErr        - Ok.
//   ippStsNullPtrErr   - Error when any of the specified pointers is NULL.
//   ippStsSizeErr      - Error when filters length is negative, or equal to zero.
//   ippStsWtOffsetErr  - Error when filter delay is less than (-1).
*/
IPPAPI(IppStatus, ippsWTInvGetSize, (IppDataType dstType, int lenLow, int offsLow, int lenHigh, int offsHigh, int* pStateSize))

/* //////////////////////////////////////////////////////////////////////
// Name:        ippsWTInvInit
//
// Purpose:     Initialize inverse wavelet transform state structure.
//
// Parameters:
//   pState    - Pointer to allocated ippsWTInv state structure.
//   pTapsLow  - Pointer to lowpass filter taps.
//   lenLow    - Length of lowpass filter.
//   offsLow   - Input delay of lowpass filter.
//   pTapsHigh - Pointer to highpass filter taps.
//   lenHigh   - Length of highpass filter.
//   offsHigh  - Input delay of highpass filter.
//
// Returns:
//   ippStsNoErr        - Ok.
//   ippStsNullPtrErr   - Error when any of the specified pointers is NULL.
//   ippStsSizeErr      - Error when filters length is negative, or equal to zero.
//   ippStsWtOffsetErr  - Error when filter delay is less than (-1).
*/
IPPAPI(IppStatus, ippsWTInvInit_32f8u,  (IppsWTInvState_32f8u*  pState, const Ipp32f* pTapsLow, int lenLow, int offsLow, const Ipp32f* pTapsHigh, int lenHigh, int offsHigh))
IPPAPI(IppStatus, ippsWTInvInit_32f16u, (IppsWTInvState_32f16u* pState, const Ipp32f* pTapsLow, int lenLow, int offsLow, const Ipp32f* pTapsHigh, int lenHigh, int offsHigh))
IPPAPI(IppStatus, ippsWTInvInit_32f16s, (IppsWTInvState_32f16s* pState, const Ipp32f* pTapsLow, int lenLow, int offsLow, const Ipp32f* pTapsHigh, int lenHigh, int offsHigh))
IPPAPI(IppStatus, ippsWTInvInit_32f,    (IppsWTInvState_32f*    pState, const Ipp32f* pTapsLow, int lenLow, int offsLow, const Ipp32f* pTapsHigh, int lenHigh, int offsHigh))

/* //////////////////////////////////////////////////////////////////////
// Name:        ippsWTInvSetDlyLine_32f, ippsWTInvSetDlyLine_32f8s,
//              ippsWTInvSetDlyLine_32f8u, ippsWTInvSetDlyLine_32f16s,
//              ippsWTInvSetDlyLine_32f16u
//
// Purpose:     The function copies the pointed vectors to internal delay lines.
//
// Parameters:
//   pState   - pointer to pState structure;
//   pDlyLow  - pointer to delay line for lowpass filtering;
//   pDlyHigh - pointer to delay line for highpass filtering.
//
// Returns:
//   ippStsNoErr            - Ok;
//   ippStsNullPtrErr       - some of pointers pDlyLow
//                              or pDlyHigh vectors are NULL;
//   ippStspStateMatchErr   - mismatch pState structure.
//
// Notes: lengths of delay lines (as "C" expression):
//          len(pDlyLow)  = (lenLow   + offsLow  - 1) / 2;
//          len(pDlyHigh) = (lenHigh  + offsHigh - 1) / 2;
//  lenLow, offsLow, lenHigh, offsHigh - parameters
//    for ippsWTInvInitAlloc function.
*/
IPPAPI(IppStatus, ippsWTInvSetDlyLine_32f8u,  (IppsWTInvState_32f8u*  pState, const Ipp32f* pDlyLow, const Ipp32f* pDlyHigh))
IPPAPI(IppStatus, ippsWTInvSetDlyLine_32f16s, (IppsWTInvState_32f16s* pState, const Ipp32f* pDlyLow, const Ipp32f* pDlyHigh))
IPPAPI(IppStatus, ippsWTInvSetDlyLine_32f16u, (IppsWTInvState_32f16u* pState, const Ipp32f* pDlyLow, const Ipp32f* pDlyHigh))
IPPAPI(IppStatus, ippsWTInvSetDlyLine_32f,    (IppsWTInvState_32f*    pState, const Ipp32f* pDlyLow, const Ipp32f* pDlyHigh))

/* //////////////////////////////////////////////////////////////////////
// Name:        ippsWTInvGetDlyLine_32f, ippsWTInvGetDlyLine_32f8s,
//              ippsWTInvGetDlyLine_32f8u, ippsWTInvGetDlyLine_32f16s,
//              ippsWTInvGetDlyLine_32f16u
//
// Purpose:     The function copies data from interanl delay lines
//                to the pointed vectors.
// Parameters:
//   pState   - pointer to pState structure;
//   pDlyLow  - pointer to delay line for lowpass filtering;
//   pDlyHigh - pointer to delay line for highpass filtering.
//
// Returns:
//   ippStsNoErr            - Ok;
//   ippStsNullPtrErr       - some of pointers pDlyLow
//                              or pDlyHigh vectors are NULL;
//   ippStspStateMatchErr    - mismatch pState structure.
//
// Notes: lengths of delay lines (as "C" expression):
//          len(pDlyLow)  = (lenLow   + offsLow  - 1) / 2;
//          len(pDlyHigh) = (lenHigh  + offsHigh - 1) / 2;
//  lenLow, offsLow, lenHigh, offsHigh - parameters
//    for ippsWTInvInitAlloc function.
*/
IPPAPI(IppStatus, ippsWTInvGetDlyLine_32f8u,  (IppsWTInvState_32f8u*  pState, Ipp32f* pDlyLow, Ipp32f* pDlyHigh))
IPPAPI(IppStatus, ippsWTInvGetDlyLine_32f16s, (IppsWTInvState_32f16s* pState, Ipp32f* pDlyLow, Ipp32f* pDlyHigh))
IPPAPI(IppStatus, ippsWTInvGetDlyLine_32f16u, (IppsWTInvState_32f16u* pState, Ipp32f* pDlyLow, Ipp32f* pDlyHigh))
IPPAPI(IppStatus, ippsWTInvGetDlyLine_32f,    (IppsWTInvState_32f*    pState, Ipp32f* pDlyLow, Ipp32f* pDlyHigh))

/* //////////////////////////////////////////////////////////////////////
// Name:        ippsWTInv_32f, ippsWTInv_32f16s, ippsWTInv_32f16u,
//              ippsWTInv_32f8u
//
// Purpose:     Inverse wavelet transform.
//
// Parameters:
//   srcLow  - pointer to source block of "low-frequency" component;
//   srcHigh - pointer to source block of "high-frequency" component;
//   dstLen  - length of components.
//   dst     - pointer to destination block of reconstructed data;
//   pState  - pointer to pState structure;
//
//  Returns:
//   ippStsNoErr            - Ok;
//   ippStsNullPtrErr       - some of pointers to pDst pSrcLow or pSrcHigh vectors are NULL;
//   ippStsSizeErr          - the length is less or equal zero;
//   ippStspStateMatchErr   - mismatch pState structure.
//
// Notes:      destination block length must be 2 * srcLen.
*/
IPPAPI(IppStatus, ippsWTInv_32f8u,  (const Ipp32f* pSrcLow, const Ipp32f* pSrcHigh, int srcLen, Ipp8u*  pDst, IppsWTInvState_32f8u*  pState))
IPPAPI(IppStatus, ippsWTInv_32f16s, (const Ipp32f* pSrcLow, const Ipp32f* pSrcHigh, int srcLen, Ipp16s* pDst, IppsWTInvState_32f16s* pState))
IPPAPI(IppStatus, ippsWTInv_32f16u, (const Ipp32f* pSrcLow, const Ipp32f* pSrcHigh, int srcLen, Ipp16u* pDst, IppsWTInvState_32f16u* pState))
IPPAPI(IppStatus, ippsWTInv_32f,    (const Ipp32f* pSrcLow, const Ipp32f* pSrcHigh, int srcLen, Ipp32f* pDst, IppsWTInvState_32f*    pState))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsReplaceNAN
//  Purpose:    replaces the vector elements with NAN value by6 constant value
//  Parameters:
//   pSrcDst            pointer to the source/destination vector
//   len                length of the vector(s), number of items
//   value              value to be assigned to vector elements which are NAN
//  Return:
//   ippStsNullPtrErr      pointer to source/destination vector is NULL
//   ippStsSizeErr         length of a vector is less or equal 0
//   ippStsNoErr           otherwise
*/
IPPAPI(IppStatus, ippsReplaceNAN_32f_I, (Ipp32f* pSrcDst, int len, Ipp32f value))
IPPAPI(IppStatus, ippsReplaceNAN_64f_I, (Ipp64f* pSrcDst, int len, Ipp64f value))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsPatternMatch_8u16u
//  Purpose:    Compares binary patterns with array of templates 
//  Parameters:
//   pSrc        - The pointer to the  source templates.
//   srcStep     - The stride between patterns in source array.
//   srcLen      - The number of patterns in source array.
//   pPattern    - The pointer to the  array of templates.
//   patternStep - The stride between templates.
//   patternLen  - The number of elements in templates array.
//   patternSize - The size (in bytes) of pattern
//   pDst        - The pointer to result of comparing of length srcLen*patternLen*sizeof(Ipp16u).
//   bufSize     - The size of requested buffer size
//   pBuffer     - The pointer to work buffer
//   hint        - The hint of special optimization method(Memory, direct or auto).
//  Return:
//  ippStsNullPtrErr - one of the pointers is NULL
//  ippStsStepErr    - one of srcStep, patternStep is not positive
//  ippStsSizeErr    - one of srcLen, patternLen or size is not positive or size is too big
//  ippStsBadArgErr  - hint is not in list ippPatternMatchAuto/ippPatternMatchDirect/ippPatternMatchTable
*/
IPPAPI(IppStatus, ippsPatternMatchGetBufferSize, (int srcLen, int patternLen, int patternSize, IppPatternMatchMode hint, int* bufSize))
IPPAPI(IppStatus, ippsPatternMatch_8u16u, (const Ipp8u* pSrc, int srcStep, int srcLen, const Ipp8u* pPattern, int patternStep, int patternLen, int patternSize, Ipp16u* pDst, IppPatternMatchMode hint, Ipp8u* pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsTopK_32s/ippsTopK_32f
//  Purpose:    Top K elements of vector
//  Parameters:
//   pSrc        - The pointer to the  source vector.
//   srcIndex    - The start index (index of pSrc[0]).
//   srcStride   - The stride between elements in source array.
//   srcLen      - The number of elements in source array.
//   pDstValue   - The pointer to the  array of destination values.
//   pDstIndex   - The pointer to the  array of destination indexes.
//   dstLen      - The number elements in destination vector (K)
//   hint        - The hint of special optimization method.
//   pBuffer     - The pointer to work buffer
//   bufSize     - The size of requested buffer size
//  Return:
//  ippStsNullPtrErr - one of the pointers is NULL
//  ippStsStepErr    - one of srcStride, patternStep is not positive
//  ippStsSizeErr    - one of srcLen, dstLen or K is not positive or size is too big
//  ippStsBadArgErr  - hint is not element from ippsTopKMode
*/

IPPAPI(IppStatus, ippsTopKGetBufferSize, (Ipp64s srcLen, Ipp64s dstLen, IppDataType dataType, IppTopKMode hint, Ipp64s* bufSize))
IPPAPI(IppStatus, ippsTopKInit_32s, (Ipp32s* pDstValue, Ipp64s* pDstIndex, Ipp64s dstLen))
IPPAPI(IppStatus, ippsTopKInit_32f, (Ipp32f* pDstValue, Ipp64s* pDstIndex, Ipp64s dstLen))
IPPAPI(IppStatus, ippsTopK_32s, (const Ipp32s* pSrc, Ipp64s srcIndex, Ipp64s srcStride, Ipp64s srcLen, Ipp32s* pDstValue, Ipp64s* pDstIndex, Ipp64s dstLen, IppTopKMode hint, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsTopK_32f, (const Ipp32f* pSrc, Ipp64s srcIndex, Ipp64s srcStride, Ipp64s srcLen, Ipp32f* pDstValue, Ipp64s* pDstIndex, Ipp64s dstLen, IppTopKMode hint, Ipp8u* pBuffer))

#ifdef __cplusplus
}
#endif

#endif /* IPPS_H__ */
