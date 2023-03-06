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
//        Intel(R) Integrated Performance Primitives
//               Signal Processing (ippSP)
//                    Legacy Library
//
*/

#if !defined( __IPPS_90_LEGACY_H__ )
#define __IPPS_90_LEGACY_H__

#include "ippdefs90legacy.h"
#include "ipps90legacy_redef.h"

#ifdef __cplusplus
extern "C" {
#endif


/*//////////////////////////////////////////////////////////////////////////////
//  Core functionality for legacy libraries
//////////////////////////////////////////////////////////////////////////////*/

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippInit
//  Purpose:    Automatic switching to best for current cpu library code using.
//  Returns:
//   ippStsNoErr
//
//  Parameter:  nothing
//
//  Notes:      At the moment of this function execution no any other IPP function
//              has to be working
*/
LEGACY90IPPAPI( IppStatus, legacy90ippsInit, ( void ))


/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippSetNumThreads
//
//  Purpose:
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNoOperation        For static library internal threading is not supported
//    ippStsSizeErr            Desired number of threads less or equal zero
//
//  Arguments:
//    numThr                   Desired number of threads
*/
LEGACY90IPPAPI( IppStatus, legacy90ippsSetNumThreads, ( int numThr ) )

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippGetNumThreads
//
//  Purpose:
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         Pointer to numThr is Null
//    ippStsNoOperation        For static library internal threading is not supported
//                             and return value is always == 1
//
//  Arguments:
//    pNumThr                  Pointer to memory location where to store current numThr
*/
LEGACY90IPPAPI( IppStatus, legacy90ippsGetNumThreads, (int* pNumThr) )

/*////////////////////////////////////////////////////////////////////////////*/


/* ///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//                   Functions declarations
//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsGetLibVersion
//  Purpose:    get the library version
//  Parameters:
//  Returns:    pointer to structure describing version of the ipps library
//
//  Notes:      don't free the pointer
*/
LEGACY90IPPAPI( const IppLibraryVersion*, legacy90ippsGetLibVersion, (void) )


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsPackBits_32u8u
//  Purpose:    Packing of bit's data from source to destination vector
//  Parameters:
//    pSrcBit       pointer to the input vector with data bits
//    pSrcBits      pointer to the input vector that specifies number of data bits
//    srcLen        length of the pSrcBit and pSrcBits vectors, number of items
//    pDst          pointer to the output vector
//    dstBitOffset  offset in the first byte of the destination vector
//    pDstLenBit    pointer to the length of the output vector, number of bits
//  Return:
//    ippStsNullPtrErr        pointer(s) to the data is NULL
//    ippStsSizeErr           length of the vectors is less or equal zero
//    ippStsSizeErr           dstBitOffset is less zero
//
//    ippStsOverlongString    Warning: pSrcBits[i] < 0, or pSrcBits[i] > 32.
//
//    ippStsNoErr             otherwise
*/

LEGACY90IPPAPI( IppStatus, legacy90ippsPackBits_32u8u,( const Ipp32u* pSrcBit,
                                        const int*    pSrcBits,
                                              int     srcLen,
                                              Ipp8u*  pDst,
                                              int     dstBitOffset,
                                              int*    pDstLenBit ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsCopy_1u
//              ippsCopyLE_1u
//              ippsCopyBE_1u
//  Purpose:    copy bit's data from source to destination vector
//  Parameters:
//    pSrc          pointer to the input vector
//    srcBitOffset  offset in the first byte of the source vector
//    pDst          pointer to the output vector
//    dstBitOffset  offset in the first byte of the destination vector
//    len           length of the vectors, number of bits
//  Return:
//    ippStsNullPtrErr        pointer(s) to the data is NULL
//    ippStsSizeErr           length of the vectors is less or equal zero
//    ippStsNoErr             otherwise
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsCopy_1u,
      ( const Ipp8u* pSrc, int srcBitOffset, Ipp8u* pDst, int dstBitOffset, int len ))


/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippsRandUniform_Direct_16s, ippsRandUniform_Direct_32f, ippsRandUniform_Direct_64f
//
//  Purpose:    Makes pseudo-random samples with a uniform distribution and places them in
//              the vector.
//
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         The pointer to vector is NULL
//    ippStsBadSizeErr         The length of the vector is less or equal zero
//
//  Arguments:
//    low                      The lower bounds of the uniform distributions range.
//    high                     The upper bounds of the uniform distributions range.
//    pSeed                    The pointer to the seed value used by the pseudo-random number
//                             generation algorithm.
//    pSrcDst                  The pointer to vector
//    len                      Vector's length
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsRandUniform_Direct_16s, (Ipp16s* pDst, int len, Ipp16s low, Ipp16s high,
                                               unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippsRandUniform_Direct_32f, (Ipp32f* pDst, int len, Ipp32f low, Ipp32f high,
                                               unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippsRandUniform_Direct_64f, (Ipp64f* pDst, int len, Ipp64f low, Ipp64f high,
                                               unsigned int* pSeed))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippsRandGauss_Direct_16s, ippsRandGauss_Direct_32f, ippsRandGauss_Direct_64f
//
//  Purpose:    Makes pseudo-random samples with a Normal distribution distribution and places
//              them in the vector.
//
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         The pointer to vector is NULL
//    ippStsBadSizeErr         The length of the vector is less or equal zero
//
//  Arguments:
//    mean                     The mean of the Normal distribution.
//    stdev                    The standard deviation of the Normal distribution.
//    pSeed                    The pointer to the seed value used by the pseudo-random number
//                             generation algorithm.
//    pSrcDst                  The pointer to vector
//    len                      Vector's length
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsRandGauss_Direct_16s, (Ipp16s* pDst, int len, Ipp16s mean, Ipp16s stdev,
                                            unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippsRandGauss_Direct_32f, (Ipp32f* pDst, int len, Ipp32f mean, Ipp32f stdev,
                                            unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippsRandGauss_Direct_64f, (Ipp64f* pDst, int len, Ipp64f mean, Ipp64f stdev,
                                            unsigned int* pSeed))


/* /////////////////////////////////////////////////////////////////////////
//  Name:               ippsVectorJaehne
//  Purpose:            creates Jaehne vector
//
//  Parameters:
//    pDst              the pointer to the destination vector
//    len               length of the vector
//    magn              magnitude of the signal
//
//  Return:
//    ippStsNoErr       indicates no error
//    ippStsNullPtrErr  indicates an error when the pDst pointer is NULL
//    ippStsBadSizeErr  indicates an error when len is less or equal zero
//    ippStsJaehneErr   indicates an error when magnitude value is negative
//
//  Notes:              pDst[n] = magn*sin(0.5*pi*n^2/len), n=0,1,2,..len-1.
//
*/
LEGACY90IPPAPI (IppStatus, legacy90ippsVectorJaehne_8s,  (Ipp8s*  pDst, int len, Ipp8s magn))
LEGACY90IPPAPI (IppStatus, legacy90ippsVectorJaehne_32u, (Ipp32u* pDst, int len, Ipp32u magn))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippsTone_Direct
//  Purpose:        generates a tone
//  Context:
//  Returns:        IppStatus
//    ippStsNoErr        Ok
//    ippStsNullPtrErr   Some of pointers to input or output data are NULL
//    ippStsSizeErr      The length of vector is less or equal zero
//    ippStsToneMagnErr  The magn value is less than or equal to zero
//    ippStsToneFreqErr  The rFreq value is less than 0 or greater than or equal to 0.5
//                       for real tone and 1.0 for complex tone
//    ippStsTonePhaseErr The phase value is less 0 or greater or equal 2*PI
//  Parameters:
//    magn            Magnitude of the tone; that is, the maximum value
//                    attained by the wave
//    rFreq           Frequency of the tone relative to the sampling
//                    frequency. It must be in range [0.0, 0.5) for real, and
//                    [0.0, 1.0) for complex tone
//    pPhase          Phase of the tone relative to a cosinewave. It must
//                    be in range [0.0, 2*PI).
//    pDst            Pointer to the destination vector.
//    len             Length of the vector
//    hint            Suggests using specific code
//  Notes:
//    for real:  pDst[i] = magn * cos(IPP_2PI * rfreq * i + phase);
//    for cplx:  pDst[i].re = magn * cos(IPP_2PI * rfreq * i + phase);
//               pDst[i].im = magn * sin(IPP_2PI * rfreq * i + phase);
*/


LEGACY90IPPAPI(IppStatus, legacy90ippsTone_Direct_32f, (Ipp32f* pDst, int len, float magn,
                                float rFreq, float* pPhase, IppHintAlgorithm hint))
LEGACY90IPPAPI(IppStatus, legacy90ippsTone_Direct_32fc, (Ipp32fc* pDst, int len, float magn,
                                float rFreq, float* pPhase, IppHintAlgorithm hint))
LEGACY90IPPAPI(IppStatus, legacy90ippsTone_Direct_64f, (Ipp64f* pDst, int len, double magn,
                               double rFreq, double* pPhase, IppHintAlgorithm hint))
LEGACY90IPPAPI(IppStatus, legacy90ippsTone_Direct_64fc, (Ipp64fc* pDst, int len, double magn,
                               double rFreq, double* pPhase, IppHintAlgorithm hint))
LEGACY90IPPAPI(IppStatus, legacy90ippsTone_Direct_16s, (Ipp16s* pDst, int len, Ipp16s magn,
                                float rFreq, float* pPhase, IppHintAlgorithm hint))
LEGACY90IPPAPI(IppStatus, legacy90ippsTone_Direct_16sc, (Ipp16sc* pDst, int len, Ipp16s magn,
                                float rFreq, float* pPhase, IppHintAlgorithm hint))

/*
//  Name:                ippsToneInitAllocQ15_16s
//  Purpose:             Allocates memory for the structure IppToneState_16s,
//                       initializes it with a set of cosinwave parameters (magnitude,
//                       frequency, phase).
//  Context:
//  Returns:             IppStatus
//    ippStsNoErr        Ok
//    ippStsNullPtrErr   Double pointer to pToneState is NULL
//    ippStsToneMagnErr  The magn value is less than or equal to zero
//    ippStsToneFreqErr  The freqQ15 value is less than 0 or greater than 16383
//    ippStsTonePhaseErr The phaseQ15 value is less than 0 or greater than 205886
//  Parameters:
//    **pToneState       Double pointer to the structure IppToneState_16s.
//    magn               Magnitude of the tone; that is, the maximum value
//                       attained by the wave.
//    rFreqQ15           Frequency of the tone relative to the sampling
//                       frequency. It must be between 0 and 16383
//    phaseQ15           Phase of the tone relative to a cosinewave. It must
//                       be between 0 and 205886.
//  Notes:
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsToneInitAllocQ15_16s, (IppToneState_16s** pToneState,
                                             Ipp16s magn, Ipp16s rFreqQ15, Ipp32s phaseQ15))

/*
//  Name:                ippsToneFree_16s
//  Purpose:             Frees memory, which was allocated
//                       for the structure IppToneState_16s.
//  Context:
//  Returns:             IppStatus
//    ippStsNoErr        Ok
//    ippStsNullPtrErr   Pointer to pToneState is NULL
//  Parameters:
//    *pToneState        Pointer to the structure IppToneState_16s.
//  Notes:
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsToneFree, (IppToneState_16s* pToneState))

/*
//  Name:                ippsToneGetStateSizeQ15_16s
//  Purpose:             Computes the size, in bytes, of the structure IppToneState_16s
//  Context:
//  Returns:             IppStatus
//    ippStsNoErr        Ok
//    ippStsNullPtrErr   Pointer to pToneState size is NULL
//  Parameters:
//    *pToneStateSize    Pointer to the computed value of the size
//                       of the structure IppToneState_16s.
//  Notes:
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsToneGetStateSizeQ15_16s, (int* pToneStateSize))

/*
//  Name:                ippsToneInitQ15_16s
//  Purpose:             initializes the structure IppToneState_16s with
//                       given set of cosinewave parameters (magnitude,
//                       frequency, phase)
//  Context:
//  Returns:             IppStatus
//    ippStsNoErr        Ok
//    ippStsNullPtrErr   Pointer to pToneState is NULL
//    ippStsToneMagnErr  The magn value is less than or equal to zero
//    ippStsToneFreqErr  The rFreqQ15 value is less than 0 or greater 16383
//    ippStsTonePhaseErr The phaseQ15 value is less than 0 or greater 205886
//  Parameters:
//    *pToneState        Pointer to the structure IppToneState_16s.
//    magn               Magnitude of the tone; that is, the maximum value
//                       attained by the wave.
//    rFreqQ15           Frequency of the tone relative to the sampling
//                       frequency. It must be between 0 and 16383
//    phaseQ15           Phase of the tone relative to a cosinewave. It must
//                       be between 0 and 205886.
//  Notes:
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsToneInitQ15_16s, (IppToneState_16s* pToneState, Ipp16s magn,
                                        Ipp16s rFreqQ15, Ipp32s phaseQ15))

/*
//  Name:                ippsToneQ15_16s
//  Purpose:             generates a tone
//  Context:
//  Returns:             IppStatus
//    ippStsNoErr        Ok
//    ippStsNullPtrErr   One of the specified pointers is NULL
//    ippStsSizeErr      len is less than or equal to 0
//  Parameters:
//    pDst               Pointer to the destination vector.
//    len                Length of the vector
//    *pToneState        Pointer to the structure IppToneState_16s.
//  Notes:
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsToneQ15_16s, (Ipp16s* pDst, int len, IppToneState_16s* pToneState))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippsTriangle_Direct
//  Purpose:        generates a Triangle
//  Context:
//  Returns:        IppStatus
//    ippStsNoErr        Ok
//    ippStsNullPtrErr   Some of pointers to input or output data are NULL
//    ippStsSizeErr       The length of vector is less or equal zero
//    ippStsTrnglMagnErr  The magn value is less or equal to zero
//    ippStsTrnglFreqErr  The rfreq value is less 0 or greater or equal 0.5
//    ippStsTrnglPhaseErr The phase value is less 0 or greater or equal 2*PI
//    ippStsTrnglAsymErr  The asym value is less -PI or greater or equal PI
//  Parameters:
//    magn            Magnitude of the Triangle; that is, the maximum value
//                    attained by the wave
//    rFreq           Frequency of the Triangle relative to the sampling
//                    frequency. It must be in range [0.0, 0.5)
//    pPhase          POinter to the phase of the Triangle relative to acosinewave. It must
//                    be in range [0.0, 2*PI)
//    asym            Asymmetry of a triangle. It must be in range [-PI,PI).
//    pDst            Pointer to destination vector.
//    len             Length of the vector
*/


LEGACY90IPPAPI(IppStatus, legacy90ippsTriangle_Direct_64f, (Ipp64f* pDst, int len, double magn,
                                double rFreq, double asym, double* pPhase))
LEGACY90IPPAPI(IppStatus, legacy90ippsTriangle_Direct_64fc, (Ipp64fc* pDst, int len, double magn,
                                double rFreq, double asym, double* pPhase))
LEGACY90IPPAPI(IppStatus, legacy90ippsTriangle_Direct_32f, (Ipp32f* pDst, int len, float magn,
                                float rFreq, float asym, float* pPhase))
LEGACY90IPPAPI(IppStatus, legacy90ippsTriangle_Direct_32fc, (Ipp32fc* pDst, int len, float magn,
                                float rFreq, float asym, float* pPhase))
LEGACY90IPPAPI(IppStatus, legacy90ippsTriangle_Direct_16s, (Ipp16s* pDst, int len, Ipp16s magn,
                                float rFreq, float asym, float* pPhase))
LEGACY90IPPAPI(IppStatus, legacy90ippsTriangle_Direct_16sc, (Ipp16sc* pDst, int len, Ipp16s magn,
                                float rFreq, float asym, float* pPhase))

/*
//  Name:                ippsTriangleInitAllocQ15_16s
//  Purpose:             Allocates memory for the structure IppTriangleState_16s,
//                       initializes it with a set of wave parameters (magnitude,
//                       frequency, phase, asymmetry).
//  Context:
//  Returns:             IppStatus
//    ippStsNoErr        Ok
//    ippStsNullPtrErr   Double pointer to pTriangleState is NULL
//    ippStsTriangleMagnErr  The magn value is less than or equal to zero
//    ippStsTriangleFreqErr  The freqQ15 value is less than 0 or greater than 16383
//    ippStsTriangleAsymErr  The phaseQ15 value is less than 0 or greater than 205886
//    ippStsTrianglePhaseErr The asymQ15 value is less than -102943 or greater than 102943
//  Parameters:
//    **pTriangleState   Double pointer to the structure IppTriangleState_16s.
//    magn               Magnitude of the Triangle; that is, the maximum value
//                       attained by the wave.
//    rFreqQ15           Frequency of the Triangle relative to the sampling
//                       frequency. It must be between 0 and 16383
//    phaseQ15           Phase of the Triangle relative to a wave. It must
//                       be between 0 and 205886.
//    asymQ15            Asymmetry of the Triangle relative to a wave. It must
//                       be between -102943 and 102943.
//  Notes:
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsTriangleInitAllocQ15_16s, (IppTriangleState_16s** pTriangleState,
                         Ipp16s magn, Ipp16s rFreqQ15, Ipp32s phaseQ15, Ipp32s asymQ15))



/*
//  Name:                ippsTriangleFree_16s
//  Purpose:             Frees memory, which was allocated
//                       for the structure IppTriangleState_16s.
//  Context:
//  Returns:             IppStatus
//    ippStsNoErr        Ok
//    ippStsNullPtrErr   Pointer to pTriangleState is NULL
//  Parameters:
//    *pTriangleState    Pointer to the structure IppTriangleState_16s.
//  Notes:
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsTriangleFree, (IppTriangleState_16s* pTriangleState))



/*
//  Name:                ippsTriangleGetStateSizeQ15_16s
//  Purpose:             Computes the size, in bytes, of the structure IppTriangleState_16s
//  Context:
//  Returns:             IppStatus
//    ippStsNoErr        Ok
//    ippStsNullPtrErr   Pointer to pTriangleState size is NULL
//  Parameters:
//    *pTriangleStateSize Pointer to the computed value of the size
//                        of the structure IppTriangleState_16s.
//  Notes:
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsTriangleGetStateSizeQ15_16s, (int* pTriangleStateSize))

/*
//  Name:                ippsTriangleInitQ15_16s
//  Purpose:             Initializes the structure IppTriangleState_16s
//                       with a given set of cosinewave parameters (magnitude,
//                       frequency, phase)
//  Context:
//  Returns:               IppStatus
//    ippStsNoErr          Ok
//    ippStsNullPtrErr     The pointer to pTriangleState is NULL
//    ippStsTrngleMagnErr  The magn value is less than or equal to zero
//    ippStsTrngleFreqErr  The freqQ15 value is less than 0 or greater than 16383
//    ippStsTrnglePhaseErr The phaseQ15 value is less than 0 or greater than 205886
//    ippStsTrngleAsymErr  The asymQ15 value is less than -102943 or greater than 102943
//  Parameters:
//    *pTriangleState    Pointer to the structure IppTriangleState_16s.
//    magn               Magnitude of the Triangle; that is, the maximum value
//                       attained by the wave.
//    rFreqQ15           Frequency of the Triangle relative to the sampling
//                       frequency. It must be between 0 and 16383
//    phaseQ15           Phase of the Triangle relative to a wave. It must
//                       be between 0 and 205886.
//    asymQ15            Asymmetry of the Triangle relative to a wave. It must
//                       be between -102943 and 102943.

//  Notes:
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsTriangleInitQ15_16s, (IppTriangleState_16s* pTriangleState,
                  Ipp16s magn, Ipp16s rFreqQ15, Ipp32s phaseQ15, Ipp32s asymQ15))


/*
//  Name:                ippsTriangleQ15_16s
//  Purpose:             generates a Triangle
//  Context:
//  Returns:             IppStatus
//    ippStsNoErr        Ok
//  Parameters:
//    pDst               The pointer to destination vector.
//    len                The length of vector
//    *pTriangleState    Pointer to the structure IppTriangleState_16s.
//  Notes:
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsTriangleQ15_16s, (Ipp16s* pDst, int len, IppTriangleState_16s* pTriangleState))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippsToneQ15_Direct_16s
//  Purpose:        generates a tone
//  Context:
//  Returns:             IppStatus
//    ippStsNoErr        Ok
//    ippStsNullPtrErr   The pointer to the destination vector is NULL
//    ippStsSizeErr      The length of the vector is less than or equal to zero
//    ippStsToneMagnErr  The magn value is less than or equal to zero
//    ippStsToneFreqErr  The rFreqQ15 value is less than 0 or greater than 16383
//    ippStsTonePhaseErr The phaseQ15 value is less than 0 or greater than 205886

//  Parameters:
//    pDst          Pointer to the destination vector.
//    len           Length of the vector
//    magn          Magnitude of the tone; that is, the maximum value
//                  attained by the wave.It must be between 0 and 32767
//    rFreqQ15      Frequency of the tone relative to the sampling
//                  frequency. It must be between 0 and 16383
//    phaseQ15      Phase of the tone relative to a cosinewave. It must
//                  be between 0 and 205886.
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsToneQ15_Direct_16s, (Ipp16s* pDst, int len,
                                          Ipp16s magn, Ipp16s rFreqQ15, Ipp32s phaseQ15))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippsTriangleQ15_Direct_16s
//  Purpose:        generates a Triangle
//  Context:
//  Returns:                 IppStatus
//    ippStsNoErr            Ok
//    ippStsNullPtrErr       The pointer to the destination vector is NULL
//    ippStsSizeErr          The length of the vector is less than or equal to zero
//    ippStsTriangleMagnErr  The magn value is less than or equal to zero
//    ippStsTriangleFreqErr  The rFfreqQ15 value is less than 0 or greater than 16383
//    ippStsTriangleAsymErr  The asymQ15 value is less than 0 or greater than 205886
//    ippStsTrianglePhaseErr The phaseQ15 value is less than -102943 or greater than 102943
//  Parameters:
//    pDst          Pointer to the destination vector.
//    len           Length of the vector
//    mag           Magnitude of the Triangle; that is, the maximum value
//                  attained by the wave. It must be between 0 and 32767.
//    rFreqQ15      Frequency of the Triangle relative to the sampling
//                  frequency. It must be between 0 and 16383
//    phaseQ15      The phase of the Triangle relative to a wave. It must
//                  be between 0 and 205886.
//    asymQ15       The asymmetry of the Triangle relative to a wave. It must
//                  be between -102943 and 102943.
//  Notes:
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsTriangleQ15_Direct_16s, ( Ipp16s* pDst, int len,
                                                Ipp16s magn, Ipp16s rFreqQ15,
                                                Ipp32s phaseQ15, Ipp32s asymQ15))



/* /////////////////////////////////////////////////////////////////////////
//  Name:               ippsVectorRamp_8u,  ippsVectorRamp_8s,
//                      ippsVectorRamp_16u, ippsVectorRamp_16s,
//                      ippsVectorRamp_32u, ippsVectorRamp_32s,
//                      ippsVectorRamp_32f, ippsVectorRamp_64f
//  Purpose:            Creates ramp vector
//
//  Parameters:
//    pDst              A pointer to the destination vector
//    len               Vector's length
//    offset            Offset value
//    slope             Slope coefficient
//
//  Return:
//    ippStsNoErr       No error
//    ippStsNullPtrErr  pDst pointer is NULL
//    ippStsBadSizeErr  Vector's length is less or equal zero
//    ippStsNoErr       No error
//
//  Notes:              Dst[n] = offset + slope * n
//
*/
LEGACY90IPPAPI (IppStatus, legacy90ippsVectorRamp_8u,  (Ipp8u*  pDst, int len, float offset, float slope))
LEGACY90IPPAPI (IppStatus, legacy90ippsVectorRamp_8s,  (Ipp8s*  pDst, int len, float offset, float slope))
LEGACY90IPPAPI (IppStatus, legacy90ippsVectorRamp_16u, (Ipp16u* pDst, int len, float offset, float slope))
LEGACY90IPPAPI (IppStatus, legacy90ippsVectorRamp_16s, (Ipp16s* pDst, int len, float offset, float slope))
LEGACY90IPPAPI (IppStatus, legacy90ippsVectorRamp_32u, (Ipp32u* pDst, int len, float offset, float slope))
LEGACY90IPPAPI (IppStatus, legacy90ippsVectorRamp_32s, (Ipp32s* pDst, int len, float offset, float slope))
LEGACY90IPPAPI (IppStatus, legacy90ippsVectorRamp_32f, (Ipp32f* pDst, int len, float offset, float slope))
LEGACY90IPPAPI (IppStatus, legacy90ippsVectorRamp_64f, (Ipp64f* pDst, int len, float offset, float slope))



/* /////////////////////////////////////////////////////////////////////////////
//  Names:       ippsConj, ippsConjFlip
//  Purpose:     complex conjugate data vector
//  Parameters:
//    pSrc               pointer to the input vector
//    pDst               pointer to the output vector
//    len                length of the vectors
//  Return:
//    ippStsNullPtrErr      pointer(s) to the data is NULL
//    ippStsSizeErr         length of the vectors is less or equal zero
//    ippStsNoErr           otherwise
//  Notes:
//    the ConjFlip version conjugates and stores result in reverse order
*/

LEGACY90IPPAPI ( IppStatus, legacy90ippsConjCcs_16sc_I,
                    ( Ipp16sc* pSrcDst, int lenDst ))
LEGACY90IPPAPI ( IppStatus, legacy90ippsConjCcs_16sc,
                    ( const Ipp16s* pSrc, Ipp16sc* pDst, int lenDst ))
LEGACY90IPPAPI ( IppStatus, legacy90ippsConjPack_16sc_I,
                    ( Ipp16sc* pSrcDst, int lenDst ))
LEGACY90IPPAPI ( IppStatus, legacy90ippsConjPack_16sc,
                    ( const Ipp16s* pSrc, Ipp16sc* pDst, int lenDst ))
LEGACY90IPPAPI ( IppStatus, legacy90ippsConjPerm_16sc_I,
                    ( Ipp16sc* pSrcDst, int lenDst ))
LEGACY90IPPAPI ( IppStatus, legacy90ippsConjPerm_16sc,
                    ( const Ipp16s* pSrc, Ipp16sc* pDst, int lenDst ))


/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsPolarToCart
//
//  Purpose:    Convert polar coordinate to cartesian. Output data are formed as
//              a complex vector.
//
//  Parameters:
//   pDstMagn      an input vector containing the magnitude components
//   pDstPhase     an input vector containing the phase components(in radians)
//   pDst          an output complex vector to store the cartesian coordinates
//   len           a length of the arrays
//  Return:
//   ippStsNoErr           Ok
//   ippStsNullPtrErr      Some of pointers to input or output data are NULL
//   ippStsSizeErr         The length of the arrays is less or equal zero
//
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsPolarToCart_32sc,(const Ipp32s* pSrcMagn,
                  const Ipp32s* pSrcPhase, int phaseFixedPoint, Ipp32sc* pDst, int len))

LEGACY90IPPAPI(IppStatus, legacy90ippsPolarToCart_16sc,(const Ipp16s* pSrcMagn,
                  const Ipp16s* pSrcPhase, int phaseFixedPoint, Ipp16sc* pDst, int len))


/* /////////////////////////////////////////////////////////////////////////////
//                          Companding functions
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsALawToLin
//  Purpose:    convert from A-Law to linear PCM value
//  Parameters:
//    pSrc        pointer to the input vector containing A-Law values
//    pDst        pointer to the output vector for store linear PCM values
//    len         length of the vectors, number of items
//  Return:
//    ippStsNullPtrErr        pointer(s) to the data is NULL
//    ippStsSizeErr           length of the vectors is less or equal zero
//    ippStsNoErr             otherwise
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsALawToLin_8u32f, (const Ipp8u* pSrc, Ipp32f* pDst, int len))
LEGACY90IPPAPI(IppStatus, legacy90ippsALawToLin_8u16s, (const Ipp8u* pSrc, Ipp16s* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsMuLawToLin
//  Purpose:    convert from Mu-Law to linear PCM value
//  Parameters:
//    pSrc        pointer to the input vector containing Mu-Law values
//    pDst        pointer to the output vector for store linear PCM values
//    len         length of the vectors, number of items
//  Return:
//    ippStsNullPtrErr        pointer(s) to the data is NULL
//    ippStsSizeErr           length of the vectors is less or equal zero
//    ippStsNoErr             otherwise
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsMuLawToLin_8u32f, (const Ipp8u* pSrc, Ipp32f* pDst, int len))
LEGACY90IPPAPI(IppStatus, legacy90ippsMuLawToLin_8u16s, (const Ipp8u* pSrc, Ipp16s* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsLinToALaw
//  Purpose:    convert from linear PCM to A-Law value
//  Parameters:
//    pSrc        pointer to the input vector containing linear PCM values
//    pDst        pointer to the output vector for store A-Law values
//    len         length of the vectors, number of items
//  Return:
//    ippStsNullPtrErr        pointer(s) to the data is NULL
//    ippStsSizeErr           length of the vectors is less or equal zero
//    ippStsNoErr             otherwise
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsLinToALaw_32f8u, (const Ipp32f* pSrc, Ipp8u* pDst, int len))
LEGACY90IPPAPI(IppStatus, legacy90ippsLinToALaw_16s8u, (const Ipp16s* pSrc, Ipp8u* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsMuLawToLin
//  Purpose:    convert from linear PCM to Mu-Law value
//  Parameters:
//    pSrc        pointer to the input vector containing linear PCM values
//    pDst        pointer to the output vector for store Mu-Law values
//    len         length of the vectors, number of items
//  Return:
//    ippStsNullPtrErr        pointer(s) to the data is NULL
//    ippStsSizeErr           length of the vectors is less or equal zero
//    ippStsNoErr             otherwise
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsLinToMuLaw_32f8u, (const Ipp32f* pSrc, Ipp8u* pDst, int len))
LEGACY90IPPAPI(IppStatus, legacy90ippsLinToMuLaw_16s8u, (const Ipp16s* pSrc, Ipp8u* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsALawToMuLaw, ippsMuLawToALaw
//  Purpose:    convert from A-Law to Mu-Law and vice-versa
//  Parameters:
//    pSrc        pointer to the input vector containing A-Law or Mu-Law values
//    pDst        pointer to the output vector for store Mu-Law or A-Law values
//    len         length of the vectors, number of items
//  Return:
//    ippStsNullPtrErr        pointer(s) to the data is NULL
//    ippStsSizeErr           length of the vectors is less or equal zero
//    ippStsNoErr             otherwise
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsALawToMuLaw_8u,  (const Ipp8u* pSrc, Ipp8u* pDst, int len))
LEGACY90IPPAPI(IppStatus, legacy90ippsMuLawToALaw_8u,   (const Ipp8u* pSrc, Ipp8u* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:
//    ippsPreemphasize_32f
//  Purpose:
//    Compute the preemphasizes a single precision real signal.
//  Parameters:
//    pSrcDst  pointer to the vector for in-place operation.
//    len      length of  the input vector.
//    val      The multiplier to be used in the preemphasis difference equation
//             y(n) = x(n) - a * x(n-1)  where y  is the preemphasized  output
//             and x is the input. Usually a value  of 0.95  is  used for speech
//             audio  signals.
//  Return:
//    ippStsNoErr         Ok
//    ippStsNullPtrErr    Some of pointers to input or output data are NULL
//    ippStsSizeErr       The length of the arrays is less or equal zero
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsPreemphasize_32f,(Ipp32f* pSrcDst, int len, Ipp32f val))
LEGACY90IPPAPI(IppStatus, legacy90ippsPreemphasize_16s,(Ipp16s* pSrcDst, int len, Ipp32f val))


/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippsUpdateLinear_16s32s_I
//  Purpose:    Calc Update Linear value
//  Return:
//   IPP_NO_ERR                 Ok
//   IPP_NULL_PTR_ERR           Pointer to pSrc or pointer to pSrcDst is NULL
//   IPP_BADSIZE_ERR            The length of the array is less or equal zero
//  Parameters:
//   pSrc           pointer to vector
//   len            a length of the array
//   pSrcDst        pointer to input and output
//   srcShiftRight  shiftright of src (0<=srcShiftRight<=15)
//   alpha          weight
//   hint           code specific use hints
//
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsUpdateLinear_16s32s_I,(const Ipp16s* pSrc,int len,
       Ipp32s* pSrcDst, int srcShiftRight,Ipp16s alpha, IppHintAlgorithm hint))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippsUpdatePower_16s32s_I
//  Purpose:    Calc Update Power value
//  Return:
//   IPP_NO_ERR                 Ok
//   IPP_NULL_PTR_ERR           Pointer to pSrc or pointer to pSrcDst is NULL
//   IPP_BADSIZE_ERR            The length of the array is less or equal zero
//  Parameters:
//   pSrc           pointer to vector
//   len            a length of the array
//   pSrcDst        pointer to input and output
//   srcShiftRight  shiftright of src (0<=srcShiftRight<=31)
//   alpha          weight
//   hint           code specific use hints
//
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsUpdatePower_16s32s_I,(const Ipp16s* pSrc,int len,
       Ipp32s* pSrcDst, int srcShiftRight,Ipp16s alpha, IppHintAlgorithm hint))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsJoinScaled_32f16s_D2L
//              ippsJoinScaled_32f24s_D2L
//
//  Purpose:    Join of vectors.
//  Parameters:
//      pSrc        pointer to pointers to the input vectors
//      pDst        pointer to the output vector
//      nChannels   number of channels
//      chanlen     length of the channel
//  Return:
//      ippStsNullPtrErr        pointer(s) to the data is NULL
//      ippStsSizeErr           nChannels or chanlen are less or equal zero
//      ippStsNoErr             otherwise
//
//      Note: Default region of the src data is [-1.0,1.0].
*/

LEGACY90IPPAPI( IppStatus, legacy90ippsJoinScaled_32f16s_D2L,
        ( const Ipp32f** pSrc, int nChannels, int chanLen, Ipp16s* pDst ) )
LEGACY90IPPAPI( IppStatus, legacy90ippsJoinScaled_32f24s_D2L,
        ( const Ipp32f** pSrc, int nChannels, int chanLen, Ipp8u* pDst ) )

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsSplitScaled_16s32f_D2L
//              ippsSplitScaled_24s32f_D2L
//
//  Purpose:    Split of vector.
//  Parameters:
//      pSrc        pointer to the input vector
//      pDst        pointer to pointers to the output vectors
//      nChannels   number of channels
//      chanlen     length of the channel
//  Return:
//      ippStsNullPtrErr        pointer(s) to the data is NULL
//      ippStsSizeErr           nChannels or chanlen are less or equal zero
//      ippStsNoErr             otherwise
//
//      Note: Region of the dst data is [-1.0,1.0].
*/

LEGACY90IPPAPI( IppStatus, legacy90ippsSplitScaled_16s32f_D2L,
        ( const Ipp16s* pSrc, Ipp32f** pDst, int nChannels, int chanLen ) )
LEGACY90IPPAPI( IppStatus, legacy90ippsSplitScaled_24s32f_D2L,
        ( const Ipp8u* pSrc, Ipp32f** pDst, int nChannels, int chanLen ) )

/* /////////////////////////////////////////////////////////////////////////////
//                  Arithmetic functions
///////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////////
//  Names:       ippsAdd, ippsSub, ippsMul
//
//  Purpose:    add, subtract and multiply operations upon every element of
//              the source vector
//  Arguments:
//    pSrc                 pointer to the source vector
//    pSrcDst              pointer to the source/destination vector
//    pSrc1                pointer to the first source vector
//    pSrc2                pointer to the second source vector
//    pDst                 pointer to the destination vector
//    len                  length of the vectors
//    scaleFactor          scale factor value
//  Return:
//    ippStsNullPtrErr     pointer(s) to the data is NULL
//    ippStsSizeErr        length of the vectors is less or equal zero
//    ippStsNoErr          otherwise
//  Note:
//    AddC(X,v,Y)    :  Y[n] = X[n] + v
//    MulC(X,v,Y)    :  Y[n] = X[n] * v
//    SubC(X,v,Y)    :  Y[n] = X[n] - v
//    SubCRev(X,v,Y) :  Y[n] = v - X[n]
//    Sub(X,Y)       :  Y[n] = Y[n] - X[n]
//    Sub(X,Y,Z)     :  Z[n] = Y[n] - X[n]
*/


LEGACY90IPPAPI(IppStatus, legacy90ippsMul_32s32sc_ISfs, (const Ipp32s* pSrc, Ipp32sc* pSrcDst,
       int len, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippsMul_32s32sc_Sfs,  (const Ipp32s* pSrc1, const Ipp32sc* pSrc2,
       Ipp32sc* pDst, int len, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippsMul_Low_32s_Sfs, ( const Ipp32s* pSrc1, const Ipp32s* pSrc2,
       Ipp32s* pDst, int len, int scaleFactor))


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
LEGACY90IPPAPI(IppStatus, legacy90ippsSqrt_64s_ISfs,(Ipp64s* pSrcDst,int len,int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippsSqrt_64s_Sfs,(const Ipp64s* pSrc,Ipp64s* pDst,int len,
                                   int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippsSqrt_64s16s_Sfs,(const Ipp64s* pSrc,Ipp16s* pDst,
       int len, int scaleFactor))



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
LEGACY90IPPAPI(IppStatus, legacy90ippsMagSquared_32sc32s_Sfs, (const Ipp32sc* pSrc, Ipp32s* pDst, int len, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippsMagSquared_32fc64f, (const Ipp32fc* pSrc, Ipp64f* pDst, int len))


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
LEGACY90IPPAPI(IppStatus, legacy90ippsExp_64s_ISfs,(Ipp64s* pSrcDst, int len, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippsExp_64s_Sfs,(const Ipp64s* pSrc, Ipp64s* pDst, int len,
   int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippsExp_32f64f,(const Ipp32f* pSrc, Ipp64f* pDst, int len))


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

LEGACY90IPPAPI(IppStatus, legacy90ippsLn_64f32f,(const Ipp64f* pSrc, Ipp32f* pDst, int len))

LEGACY90IPPAPI(IppStatus, legacy90ippsLn_32s16s_Sfs, ( const Ipp32s* pSrc, Ipp16s* pDst, int Len, int scaleFactor))


/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ipps10Log10_32s_ISfs
//              ipps10Log10_32s_Sfs
//
//  Purpose:    compute decimal logarithm multiplied by 10 of every elements
//              of the source vector (for integer only).
//
//  Parameters:
//   pSrcDst              pointer to the source/destination vector
//   pSrc                 pointer to the source vector
//   pDst                 pointer to the destination vector
//   len                  length of the vector(s)
//   ScaleFactor          scale factor value
//  Return:
//   ippStsNullPtrErr     pointer(s) to the data vector is NULL
//   ippStsSizeErr        length of the vector(s) is less or equal 0
//   ippStsLnZeroArg      zero value in the source vector
//   ippStsLnNegArg       negative value in the source vector
//   ippStsNoErr          otherwise
//
*/
LEGACY90IPPAPI(IppStatus, legacy90ipps10Log10_32s_ISfs,( Ipp32s* pSrcDst, int len, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ipps10Log10_32s_Sfs, ( const Ipp32s* pSrc, Ipp32s* pDst, int len, int scaleFactor))


/* /////////////////////////////////////////////////////////////////////////////
//  Names:
//    ippsPhase_32sc_Sfs
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
LEGACY90IPPAPI(IppStatus, legacy90ippsPhase_32sc_Sfs,(const Ipp32sc* pSrc, Ipp32s* pDst, int len,
                                                                int scaleFactor))

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

LEGACY90IPPAPI(IppStatus, legacy90ippsDotProd_16s_Sfs, (const Ipp16s* pSrc1,
       const Ipp16s* pSrc2, int len, Ipp16s* pDp, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippsDotProd_16sc_Sfs,(const Ipp16sc* pSrc1,
       const Ipp16sc* pSrc2, int len, Ipp16sc* pDp, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippsDotProd_16s16sc_Sfs, (const Ipp16s* pSrc1,
       const Ipp16sc* pSrc2, int len, Ipp16sc* pDp, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippsDotProd_16sc32fc, (const Ipp16sc* pSrc1,
       const Ipp16sc* pSrc2, int len, Ipp32fc* pDp))
LEGACY90IPPAPI(IppStatus, legacy90ippsDotProd_16s16sc32fc,(const Ipp16s*  pSrc1,
       const Ipp16sc* pSrc2, int len, Ipp32fc* pDp))

LEGACY90IPPAPI ( IppStatus, legacy90ippsDotProd_16sc32sc_Sfs,
        ( const Ipp16sc* pSrc1, const Ipp16sc* pSrc2,
          int len, Ipp32sc* pDp, int scaleFactor ))
LEGACY90IPPAPI ( IppStatus, legacy90ippsDotProd_16s16sc32sc_Sfs,
        ( const Ipp16s* pSrc1, const Ipp16sc* pSrc2,
          int len, Ipp32sc* pDp, int scaleFactor ))

LEGACY90IPPAPI ( IppStatus, legacy90ippsDotProd_32sc_Sfs,
        ( const Ipp32sc* pSrc1, const Ipp32sc* pSrc2,
          int len, Ipp32sc* pDp, int scaleFactor ))
LEGACY90IPPAPI ( IppStatus, legacy90ippsDotProd_32s32sc_Sfs,
        ( const Ipp32s* pSrc1, const Ipp32sc* pSrc2,
          int len, Ipp32sc* pDp, int scaleFactor ))



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
//     ippStsNullPtrErr       One of the specified pointers is NULL
//     ippStsFftOrderErr      FFT order value is illegal
//     ippStsFFTFlagErr       Incorrect normalization flag value
*/

LEGACY90IPPAPI (IppStatus, legacy90ippsFFTGetSize_C_16sc,
                   ( int order, int flag, IppHintAlgorithm hint,
                     int* pSpecSize, int* pSpecBufferSize, int* pBufferSize ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTGetSize_C_16s,
                   ( int order, int flag, IppHintAlgorithm hint,
                     int* pSpecSize, int* pSpecBufferSize, int* pBufferSize ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTGetSize_R_16s,
                   ( int order, int flag, IppHintAlgorithm hint,
                     int* pSpecSize, int* pSpecBufferSize, int* pBufferSize ))

LEGACY90IPPAPI (IppStatus, legacy90ippsFFTGetSize_C_32sc,
                   ( int order, int flag, IppHintAlgorithm hint,
                     int* pSpecSize, int* pSpecBufferSize, int* pBufferSize ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTGetSize_C_32s,
                   ( int order, int flag, IppHintAlgorithm hint,
                     int* pSpecSize, int* pSpecBufferSize, int* pBufferSize ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTGetSize_R_32s,
                   ( int order, int flag, IppHintAlgorithm hint,
                     int* pSpecSize, int* pSpecBufferSize, int* pBufferSize ))

LEGACY90IPPAPI (IppStatus, legacy90ippsFFTGetSize_R_16s32s,
                   ( int order, int flag, IppHintAlgorithm hint,
                     int* pSpecSize, int* pSpecBufferSize, int* pBufferSize ))

/* /////////////////////////////////////////////////////////////////////////////
//                  FFT Context Functions
///////////////////////////////////////////////////////////////////////////// */
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
//     ippStsNullPtrErr       One of the specified pointers is NULL
//     ippStsFftOrderErr      FFT order value is illegal
//     ippStsFFTFlagErr       Incorrect normalization flag value
*/

LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInit_C_16sc,
                   ( IppsFFTSpec_C_16sc** ppFFTSpec,
                     int order, int flag, IppHintAlgorithm hint,
                     Ipp8u* pSpec, Ipp8u* pSpecBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInit_C_16s,
                   ( IppsFFTSpec_C_16s** ppFFTSpec,
                     int order, int flag, IppHintAlgorithm hint,
                     Ipp8u* pSpec, Ipp8u* pSpecBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInit_R_16s,
                   ( IppsFFTSpec_R_16s** ppFFTSpec,
                     int order, int flag, IppHintAlgorithm hint,
                     Ipp8u* pSpec, Ipp8u* pSpecBuffer ))

LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInit_C_32sc,
                   ( IppsFFTSpec_C_32sc** ppFFTSpec,
                     int order, int flag, IppHintAlgorithm hint,
                     Ipp8u* pSpec, Ipp8u* pSpecBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInit_C_32s,
                   ( IppsFFTSpec_C_32s** ppFFTSpec,
                     int order, int flag, IppHintAlgorithm hint,
                     Ipp8u* pSpec, Ipp8u* pSpecBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInit_R_32s,
                   ( IppsFFTSpec_R_32s** ppFFTSpec,
                     int order, int flag, IppHintAlgorithm hint,
                     Ipp8u* pSpec, Ipp8u* pSpecBuffer ))

LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInit_R_16s32s,
                   ( IppsFFTSpec_R_16s32s** ppFFTSpec,
                     int order, int flag, IppHintAlgorithm hint,
                     Ipp8u* pSpec, Ipp8u* pSpecBuffer ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsFFTInitAlloc_C, ippsFFTInitAlloc_R
//  Purpose:    Allocates and initializes the FFT specification structure
//  Arguments:
//     order       Base-2 logarithm of the number of samples in FFT
//     flag        Flag to choose the results normalization factors
//     hint        Option to select the algorithmic implementation of the transform
//                 function
//     ppFFTSpec   Double pointer to the FFT context structure
//  Return:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       ppFFTSpec == NULL
//     ippStsFftOrderErr      FFT order value is illegal
//     ippStsFFTFlagErr       Incorrect normalization flag value
//     ippStsMemAllocErr      Memory allocation fails
*/

LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInitAlloc_C_16sc,
                   ( IppsFFTSpec_C_16sc** ppFFTSpec,
                     int order, int flag, IppHintAlgorithm hint ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInitAlloc_C_16s,
                   ( IppsFFTSpec_C_16s** ppFFTSpec,
                     int order, int flag, IppHintAlgorithm hint ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInitAlloc_R_16s,
                   ( IppsFFTSpec_R_16s** ppFFTSpec,
                     int order, int flag, IppHintAlgorithm hint ))

LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInitAlloc_C_32sc,
                   ( IppsFFTSpec_C_32sc** ppFFTSpec,
                     int order, int flag, IppHintAlgorithm hint ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInitAlloc_C_32s,
                   ( IppsFFTSpec_C_32s** ppFFTSpec,
                     int order, int flag, IppHintAlgorithm hint ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInitAlloc_R_32s,
                   ( IppsFFTSpec_R_32s** ppFFTSpec,
                     int order, int flag, IppHintAlgorithm hint ))

LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInitAlloc_R_16s32s,
                   ( IppsFFTSpec_R_16s32s** ppFFTSpec,
                     int order, int flag, IppHintAlgorithm hint ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsFFTFree_C, ippsFFTFree_R
//  Purpose:    Closes the DFT specification structure
//  Arguments:
//     pFFTSpec  Pointer to the FFT context structure
//  Return:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       pFFTSpec == NULL
//     ippStsContextMatchErr  Invalid context structure
*/

LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFree_C_16sc,   ( IppsFFTSpec_C_16sc* pFFTSpec ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFree_C_16s,    ( IppsFFTSpec_C_16s*  pFFTSpec ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFree_R_16s,    ( IppsFFTSpec_R_16s*  pFFTSpec ))

LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFree_C_32sc,   ( IppsFFTSpec_C_32sc* pFFTSpec ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFree_C_32s,    ( IppsFFTSpec_C_32s*  pFFTSpec ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFree_R_32s,    ( IppsFFTSpec_R_32s*  pFFTSpec ))

LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFree_R_16s32s, ( IppsFFTSpec_R_16s32s* pFFTSpec ))

/* /////////////////////////////////////////////////////////////////////////////
//                  FFT Buffer Size
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsFFTGetBufSize_C, ippsFFTGetBufSize_R
//  Purpose:    Computes the size of the FFT work buffer (in bytes)
//  Arguments:
//     pFFTSpec      Pointer to the FFT context structure
//     pBufferSize   Pointer to the size of the external buffer
//  Return:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       One of the specified pointers is NULL
//     ippStsContextMatchErr  Invalid context structure
*/

LEGACY90IPPAPI (IppStatus, legacy90ippsFFTGetBufSize_C_16sc,
                   ( const IppsFFTSpec_C_16sc* pFFTSpec, int* pBufferSize ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTGetBufSize_C_16s,
                   ( const IppsFFTSpec_C_16s*  pFFTSpec, int* pBufferSize ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTGetBufSize_R_16s,
                   ( const IppsFFTSpec_R_16s*  pFFTSpec, int* pBufferSize ))

LEGACY90IPPAPI (IppStatus, legacy90ippsFFTGetBufSize_C_32sc,
                   ( const IppsFFTSpec_C_32sc* pFFTSpec, int* pBufferSize ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTGetBufSize_C_32s,
                   ( const IppsFFTSpec_C_32s*  pFFTSpec, int* pBufferSize ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTGetBufSize_R_32s,
                   ( const IppsFFTSpec_R_32s*  pFFTSpec, int* pBufferSize ))

LEGACY90IPPAPI (IppStatus, legacy90ippsFFTGetBufSize_R_16s32s,
                   ( const IppsFFTSpec_R_16s32s* pFFTSpec, int* pBufferSize ))

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
//     ippStsNullPtrErr       One of the specified pointers with the exception of
                              pBuffer is NULL
//     ippStsContextMatchErr  Invalid context structure
//     ippStsMemAllocErr      Memory allocation fails
*/

LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFwd_CToC_16sc_Sfs,
                   ( const Ipp16sc* pSrc, Ipp16sc* pDst,
                     const IppsFFTSpec_C_16sc* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInv_CToC_16sc_Sfs,
                   ( const Ipp16sc* pSrc, Ipp16sc* pDst,
                     const IppsFFTSpec_C_16sc* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFwd_CToC_16s_Sfs,
                   ( const Ipp16s* pSrcRe, const Ipp16s* pSrcIm,
                     Ipp16s* pDstRe, Ipp16s* pDstIm,
                     const IppsFFTSpec_C_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInv_CToC_16s_Sfs,
                   ( const Ipp16s* pSrcRe, const Ipp16s* pSrcIm,
                     Ipp16s* pDstRe, Ipp16s* pDstIm,
                     const IppsFFTSpec_C_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))

LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFwd_CToC_16sc_ISfs,
                   ( Ipp16sc* pSrcDst,
                     const IppsFFTSpec_C_16sc* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInv_CToC_16sc_ISfs,
                   ( Ipp16sc* pSrcDst,
                     const IppsFFTSpec_C_16sc* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFwd_CToC_16s_ISfs,
                   ( Ipp16s* pSrcDstRe, Ipp16s* pSrcDstIm,
                     const IppsFFTSpec_C_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInv_CToC_16s_ISfs,
                   ( Ipp16s* pSrcDstRe, Ipp16s* pSrcDstIm,
                     const IppsFFTSpec_C_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))

LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFwd_CToC_32sc_Sfs,
                   ( const Ipp32sc* pSrc, Ipp32sc* pDst,
                     const IppsFFTSpec_C_32sc* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInv_CToC_32sc_Sfs,
                   ( const Ipp32sc* pSrc, Ipp32sc* pDst,
                     const IppsFFTSpec_C_32sc* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFwd_CToC_32s_Sfs,
                   ( const Ipp32s* pSrcRe, const Ipp32s* pSrcIm,
                     Ipp32s* pDstRe, Ipp32s* pDstIm,
                     const IppsFFTSpec_C_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInv_CToC_32s_Sfs,
                   ( const Ipp32s* pSrcRe, const Ipp32s* pSrcIm,
                     Ipp32s* pDstRe, Ipp32s* pDstIm,
                     const IppsFFTSpec_C_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))

LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFwd_CToC_32sc_ISfs,
                   ( Ipp32sc* pSrcDst,
                     const IppsFFTSpec_C_32sc* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInv_CToC_32sc_ISfs,
                   ( Ipp32sc* pSrcDst,
                     const IppsFFTSpec_C_32sc* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFwd_CToC_32s_ISfs,
                   ( Ipp32s* pSrcDstRe, Ipp32s* pSrcDstIm,
                     const IppsFFTSpec_C_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInv_CToC_32s_ISfs,
                   ( Ipp32s* pSrcDstRe, Ipp32s* pSrcDstIm,
                     const IppsFFTSpec_C_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))

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
//     ippStsNullPtrErr       One of the specified pointers with the exception of
                              pBuffer is NULL
//     ippStsContextMatchErr  Invalid context structure
//     ippStsMemAllocErr      Memory allocation fails
*/

LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFwd_RToPerm_16s_Sfs,
                   ( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFwd_RToPack_16s_Sfs,
                   ( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFwd_RToCCS_16s_Sfs,
                   ( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInv_PermToR_16s_Sfs,
                   ( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInv_PackToR_16s_Sfs,
                   ( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInv_CCSToR_16s_Sfs,
                   ( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))

LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFwd_RToPerm_16s_ISfs,
                   ( Ipp16s* pSrcDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFwd_RToPack_16s_ISfs,
                   ( Ipp16s* pSrcDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFwd_RToCCS_16s_ISfs,
                   ( Ipp16s* pSrcDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInv_PermToR_16s_ISfs,
                   ( Ipp16s* pSrcDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInv_PackToR_16s_ISfs,
                   ( Ipp16s* pSrcDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInv_CCSToR_16s_ISfs,
                   ( Ipp16s* pSrcDst,
                     const IppsFFTSpec_R_16s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))

LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFwd_RToPerm_32s_Sfs,
                   ( const Ipp32s* pSrc, Ipp32s* pDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFwd_RToPack_32s_Sfs,
                   ( const Ipp32s* pSrc, Ipp32s* pDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFwd_RToCCS_32s_Sfs,
                   ( const Ipp32s* pSrc, Ipp32s* pDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInv_PermToR_32s_Sfs,
                   ( const Ipp32s* pSrc, Ipp32s* pDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInv_PackToR_32s_Sfs,
                   ( const Ipp32s* pSrc, Ipp32s* pDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInv_CCSToR_32s_Sfs,
                   ( const Ipp32s* pSrc, Ipp32s* pDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))

LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFwd_RToPerm_32s_ISfs,
                   ( Ipp32s* pSrcDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFwd_RToPack_32s_ISfs,
                   ( Ipp32s* pSrcDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFwd_RToCCS_32s_ISfs,
                   ( Ipp32s* pSrcDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInv_PermToR_32s_ISfs,
                   ( Ipp32s* pSrcDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInv_PackToR_32s_ISfs,
                   ( Ipp32s* pSrcDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInv_CCSToR_32s_ISfs,
                   ( Ipp32s* pSrcDst,
                     const IppsFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))

LEGACY90IPPAPI (IppStatus, legacy90ippsFFTFwd_RToCCS_16s32s_Sfs,
                   ( const Ipp16s* pSrc, Ipp32s* pDst,
                     const IppsFFTSpec_R_16s32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsFFTInv_CCSToR_32s16s_Sfs,
                   ( const Ipp32s* pSrc, Ipp16s* pDst,
                     const IppsFFTSpec_R_16s32s* pFFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))



/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDFTInitAlloc_C, ippsDFTInitAlloc_R
//  Purpose:    Allocates and initializes the DFT specification structure
//  Arguments:
//     length     Length of the DFT transform
//     flag       Flag to choose the results normalization factors
//     hint       Option to select the algorithmic implementation of the transform
//                function
//     pDFTSpec   Double pointer to the DFT context structure
//  Return:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       pDFTSpec == NULL
//     ippStsFftOrderErr      FFT order value is illegal
//     ippStsFFTFlagErr       Incorrect normalization flag value
//     ippStsMemAllocErr      Memory allocation fails
*/

LEGACY90IPPAPI (IppStatus, legacy90ippsDFTInitAlloc_C_16sc,
                   ( IppsDFTSpec_C_16sc** pDFTSpec,
                     int length, int flag, IppHintAlgorithm hint ))
LEGACY90IPPAPI (IppStatus, legacy90ippsDFTInitAlloc_C_16s,
                   ( IppsDFTSpec_C_16s** pDFTSpec,
                     int length, int flag, IppHintAlgorithm hint ))
LEGACY90IPPAPI (IppStatus, legacy90ippsDFTInitAlloc_R_16s,
                   ( IppsDFTSpec_R_16s** pDFTSpec,
                     int length, int flag, IppHintAlgorithm hint ))

LEGACY90IPPAPI (IppStatus, legacy90ippsDFTOutOrdInitAlloc_C_32fc,
                   ( IppsDFTOutOrdSpec_C_32fc** pDFTSpec,
                     int length, int flag, IppHintAlgorithm hint ))

LEGACY90IPPAPI (IppStatus, legacy90ippsDFTOutOrdInitAlloc_C_64fc,
                   ( IppsDFTOutOrdSpec_C_64fc** pDFTSpec,
                     int length, int flag, IppHintAlgorithm hint ))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDFTFree_C, ippsDFTFree_R
//  Purpose:    Closes the DFT specification structure
//  Arguments:
//     pDFTSpec  Pointer to the DFT context structure
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       pDFTSpec == NULL
//     ippStsContextMatchErr  Invalid context structure
*/

LEGACY90IPPAPI (IppStatus, legacy90ippsDFTFree_C_16sc, ( IppsDFTSpec_C_16sc* pDFTSpec ))
LEGACY90IPPAPI (IppStatus, legacy90ippsDFTFree_C_16s,  ( IppsDFTSpec_C_16s*  pDFTSpec ))
LEGACY90IPPAPI (IppStatus, legacy90ippsDFTFree_R_16s,  ( IppsDFTSpec_R_16s*  pDFTSpec ))

LEGACY90IPPAPI (IppStatus, legacy90ippsDFTOutOrdFree_C_32fc, ( IppsDFTOutOrdSpec_C_32fc* pDFTSpec ))
LEGACY90IPPAPI (IppStatus, legacy90ippsDFTOutOrdFree_C_64fc, ( IppsDFTOutOrdSpec_C_64fc* pDFTSpec ))


/* /////////////////////////////////////////////////////////////////////////////
//                  DFT Buffer Size
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDFTGetBufSize_C, ippsDFTGetBufSize_R
//  Purpose:    Computes the size of the DFT work buffer (in bytes)
//  Arguments:
//     pFFTSpec      Pointer to the DFT context structure
//     pBufferSize   Pointer to the size of the external buffer
//  Return:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       One of the specified pointers is NULL
//     ippStsContextMatchErr  Invalid context structure
*/

LEGACY90IPPAPI (IppStatus, legacy90ippsDFTGetBufSize_C_16sc,
                   ( const IppsDFTSpec_C_16sc* pDFTSpec, int* pSize ))
LEGACY90IPPAPI (IppStatus, legacy90ippsDFTGetBufSize_C_16s,
                   ( const IppsDFTSpec_C_16s*  pDFTSpec, int* pSize ))
LEGACY90IPPAPI (IppStatus, legacy90ippsDFTGetBufSize_R_16s,
                   ( const IppsDFTSpec_R_16s*  pDFTSpec, int* pSize ))

LEGACY90IPPAPI (IppStatus, legacy90ippsDFTOutOrdGetBufSize_C_32fc,
                   ( const IppsDFTOutOrdSpec_C_32fc* pDFTSpec, int* size ))

LEGACY90IPPAPI (IppStatus, legacy90ippsDFTOutOrdGetBufSize_C_64fc,
                   ( const IppsDFTOutOrdSpec_C_64fc* pDFTSpec, int* size ))


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
//     ippStsNullPtrErr       One of the specified pointers with the exception of
                              pBuffer is NULL
//     ippStsContextMatchErr  Invalid context structure
//     ippStsMemAllocErr      Memory allocation fails
*/

LEGACY90IPPAPI (IppStatus, legacy90ippsDFTFwd_CToC_16sc_Sfs,
                   ( const Ipp16sc* pSrc, Ipp16sc* pDst,
                     const IppsDFTSpec_C_16sc* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsDFTInv_CToC_16sc_Sfs,
                   ( const Ipp16sc* pSrc, Ipp16sc* pDst,
                     const IppsDFTSpec_C_16sc* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsDFTFwd_CToC_16s_Sfs,
                   ( const Ipp16s* pSrcRe, const Ipp16s* pSrcIm,
                     Ipp16s* pDstRe, Ipp16s* pDstIm,
                     const IppsDFTSpec_C_16s* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsDFTInv_CToC_16s_Sfs,
                   ( const Ipp16s* pSrcRe, const Ipp16s* pSrcIm,
                     Ipp16s* pDstRe, Ipp16s* pDstIm,
                     const IppsDFTSpec_C_16s* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))

LEGACY90IPPAPI (IppStatus, legacy90ippsDFTOutOrdFwd_CToC_32fc,
                   ( const Ipp32fc* pSrc, Ipp32fc* pDst,
                     const IppsDFTOutOrdSpec_C_32fc* pDFTSpec, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsDFTOutOrdInv_CToC_32fc,
                   ( const Ipp32fc* pSrc, Ipp32fc* pDst,
                     const IppsDFTOutOrdSpec_C_32fc* pDFTSpec, Ipp8u* pBuffer ))

LEGACY90IPPAPI (IppStatus, legacy90ippsDFTOutOrdFwd_CToC_64fc,
                   ( const Ipp64fc* pSrc, Ipp64fc* pDst,
                     const IppsDFTOutOrdSpec_C_64fc* pDFTSpec, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsDFTOutOrdInv_CToC_64fc,
                   ( const Ipp64fc* pSrc, Ipp64fc* pDst,
                     const IppsDFTOutOrdSpec_C_64fc* pDFTSpec, Ipp8u* pBuffer ))


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
//     ippStsNullPtrErr       One of the specified pointers with the exception of
                              pBuffer is NULL
//     ippStsContextMatchErr  Invalid context structure
//     ippStsMemAllocErr      Memory allocation fails
*/

LEGACY90IPPAPI (IppStatus, legacy90ippsDFTFwd_RToPerm_16s_Sfs,
                   ( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsDFTSpec_R_16s* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsDFTFwd_RToPack_16s_Sfs,
                   ( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsDFTSpec_R_16s* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsDFTFwd_RToCCS_16s_Sfs,
                   ( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsDFTSpec_R_16s* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsDFTInv_PermToR_16s_Sfs,
                   ( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsDFTSpec_R_16s* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsDFTInv_PackToR_16s_Sfs,
                   ( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsDFTSpec_R_16s* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsDFTInv_CCSToR_16s_Sfs,
                   ( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsDFTSpec_R_16s* pDFTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))

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
//   length             vector's length
//   scaleFactor        scale factor
//  Return:
//   ippStsNullPtrErr      pointer(s) to the data is NULL
//   ippStsSizeErr         vector`s length is less or equal zero
//   ippStsNoErr           otherwise
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsMulPack_16s_ISfs, (const Ipp16s* pSrc, Ipp16s* pSrcDst, int length, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippsMulPerm_16s_ISfs, (const Ipp16s* pSrc, Ipp16s* pSrcDst, int length, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippsMulPack_16s_Sfs, (const Ipp16s* pSrc1, const Ipp16s* pSrc2, Ipp16s* pDst, int length, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippsMulPerm_16s_Sfs, (const Ipp16s* pSrc1, const Ipp16s* pSrc2, Ipp16s* pDst, int length, int scaleFactor))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:        ippsGoertzTwo
//  Purpose:      compute DFT for dual frequency (Goertzel algorithm)
//  Parameters:
//    freq                 pointer to two relative frequency values [0, 1.0)
//    pSrc                 pointer to the input vector
//    len                  length of the vector
//    pVal                 pointer to the DFT result value computed
//    scaleFactor          scale factor value
//  Return:
//    ippStsNullPtrErr        pointer to the data is NULL
//    ippStsSizeErr           length of the vector is less or equal zero
//    ippStsRelFreqErr        frequency values out of range
//    ippStsNoErr             otherwise
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsGoertzTwo_32fc, (const Ipp32fc* pSrc, int len,
       Ipp32fc val[2], const Ipp32f rFreq[2] ))
LEGACY90IPPAPI(IppStatus, legacy90ippsGoertzTwo_64fc, (const Ipp64fc* pSrc, int len,
       Ipp64fc val[2], const Ipp64f rFreq[2] ))
LEGACY90IPPAPI(IppStatus, legacy90ippsGoertzTwo_16sc_Sfs, (const Ipp16sc* pSrc, int len,
       Ipp16sc val[2], const Ipp32f rFreq[2], int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippsGoertzTwo_32f, (const Ipp32f* pSrc, int len,
       Ipp32fc val[2], const Ipp32f rFreq[2] ))
LEGACY90IPPAPI(IppStatus, legacy90ippsGoertzTwo_64f, (const Ipp64f* pSrc, int len,
       Ipp64fc val[2], const Ipp64f rFreq[2] ))



/* /////////////////////////////////////////////////////////////////////////////
//  Names:        ippsGoertzQ15
//  Purpose:      compute DFT for single frequency (Goertzel algorithm)
//  Parameters:
//    rFreqQ15             single relative frequency value [0, 32767]
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

LEGACY90IPPAPI(IppStatus, legacy90ippsGoertzQ15_16sc_Sfs,
                  ( const Ipp16sc* pSrc, int len, Ipp16sc* pVal,
                    Ipp16s rFreqQ15, int scaleFactor ))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:        ippsGoertzTwoQ15
//  Purpose:      compute DFT for dual frequency (Goertzel algorithm)
//  Parameters:
//    rFreqQ15             pointer to two relative frequency values [0, 32767]
//    pSrc                 pointer to the input vector
//    len                  length of the vector
//    pVal                 pointer to the DFT result value computed
//    scaleFactor          scale factor value
//  Return:
//    ippStsNullPtrErr        pointer to the data is NULL
//    ippStsSizeErr           length of the vector is less or equal zero
//    ippStsRelFreqErr        frequency values out of range
//    ippStsNoErr             otherwise
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsGoertzTwoQ15_16sc_Sfs,
                  ( const Ipp16sc* pSrc, int len, Ipp16sc pVal[2],
                    const Ipp16s rFreqQ15[2], int scaleFactor ))



/* /////////////////////////////////////////////////////////////////////////////
//                  DCT Get Size Functions
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDCTFwdGetSize, ippsDCTInvGetSize
//  Purpose:    get sizes of the DCTSpec and buffers (on bytes)
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

LEGACY90IPPAPI (IppStatus, legacy90ippsDCTFwdGetSize_16s,
                   ( int len, IppHintAlgorithm hint,
                     int* pSpecSize, int* pSpecBufferSize, int* pBufferSize ))
LEGACY90IPPAPI (IppStatus, legacy90ippsDCTInvGetSize_16s,
                   ( int len, IppHintAlgorithm hint,
                     int* pSpecSize, int* pSpecBufferSize, int* pBufferSize ))

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

LEGACY90IPPAPI (IppStatus, legacy90ippsDCTFwdInit_16s,
                   ( IppsDCTFwdSpec_16s** ppDCTSpec,
                     int len, IppHintAlgorithm hint,
                     Ipp8u* pSpec, Ipp8u* pSpecBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsDCTInvInit_16s,
                   ( IppsDCTInvSpec_16s** ppDCTSpec,
                     int len, IppHintAlgorithm hint,
                     Ipp8u* pSpec, Ipp8u* pSpecBuffer ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDCTFwdInitAlloc, ippsDCTInvInitAlloc
//  Purpose:    create and initialize of DCT context
//  Arguments:
//     len       - number of samples in DCT
//     hint      - code specific use hints
//     ppDCTSpec - where write pointer to new context
//  Return:
//     ippStsNoErr            no errors
//     ippStsNullPtrErr       ppDCTSpec == NULL
//     ippStsSizeErr          bad the len value
//     ippStsMemAllocErr      memory allocation error
*/

LEGACY90IPPAPI (IppStatus, legacy90ippsDCTFwdInitAlloc_16s,
                   ( IppsDCTFwdSpec_16s** ppDCTSpec,
                     int len, IppHintAlgorithm hint ))
LEGACY90IPPAPI (IppStatus, legacy90ippsDCTInvInitAlloc_16s,
                   ( IppsDCTInvSpec_16s** ppDCTSpec,
                     int len, IppHintAlgorithm hint ))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDCTFwdFree, ippsDCTInvFree
//  Purpose:    delete DCT context
//  Arguments:
//     pDCTSpec - pointer to DCT context to be deleted
//  Return:
//     ippStsNoErr            no errors
//     ippStsNullPtrErr       pDCTSpec == NULL
//     ippStsContextMatchErr  bad context identifier
*/

LEGACY90IPPAPI (IppStatus, legacy90ippsDCTFwdFree_16s, ( IppsDCTFwdSpec_16s*  pDCTSpec ))
LEGACY90IPPAPI (IppStatus, legacy90ippsDCTInvFree_16s, ( IppsDCTInvSpec_16s*  pDCTSpec ))


/* /////////////////////////////////////////////////////////////////////////////
//                  DCT Buffer Size
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDCTFwdGetBufSize, ippsDCTInvGetBufSize
//  Purpose:    get size of the DCT work buffer (on bytes)
//  Arguments:
//     pDCTSpec    - pointer to the DCT structure
//     pBufferSize - pointer to the DCT work buffer size value
//  Return:
//     ippStsNoErr            no errors
//     ippStsNullPtrErr       pDCTSpec == NULL or pSize == NULL
//     ippStsContextMatchErr  bad context identifier
*/

LEGACY90IPPAPI (IppStatus, legacy90ippsDCTFwdGetBufSize_16s,
                   ( const IppsDCTFwdSpec_16s* pDCTSpec, int* pBufferSize ))
LEGACY90IPPAPI (IppStatus, legacy90ippsDCTInvGetBufSize_16s,
                   ( const IppsDCTInvSpec_16s* pDCTSpec, int* pBufferSize ))


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

LEGACY90IPPAPI (IppStatus, legacy90ippsDCTFwd_16s_Sfs,
                   ( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsDCTFwdSpec_16s* pDCTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsDCTInv_16s_Sfs,
                   ( const Ipp16s* pSrc, Ipp16s* pDst,
                     const IppsDCTInvSpec_16s* pDCTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))

LEGACY90IPPAPI (IppStatus, legacy90ippsDCTFwd_16s_ISfs,
                   ( Ipp16s* pSrcDst,
                     const IppsDCTFwdSpec_16s* pDCTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippsDCTInv_16s_ISfs,
                   ( Ipp16s* pSrcDst,
                     const IppsDCTInvSpec_16s* pDCTSpec,
                     int scaleFactor, Ipp8u* pBuffer ))


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

LEGACY90IPPAPI (IppStatus, legacy90ippsWTHaarFwd_8s,
                   ( const Ipp8s* pSrc, int len,
                        Ipp8s* pDstLow, Ipp8s* pDstHigh ))
LEGACY90IPPAPI (IppStatus, legacy90ippsWTHaarFwd_16s,
                   ( const Ipp16s* pSrc, int len,
                        Ipp16s* pDstLow, Ipp16s* pDstHigh ))
LEGACY90IPPAPI (IppStatus, legacy90ippsWTHaarFwd_32s,
                   ( const Ipp32s* pSrc, int len,
                        Ipp32s* pDstLow, Ipp32s* pDstHigh ))
LEGACY90IPPAPI (IppStatus, legacy90ippsWTHaarFwd_64s,
                   ( const Ipp64s* pSrc, int len,
                        Ipp64s* pDstLow, Ipp64s* pDstHigh ))

LEGACY90IPPAPI (IppStatus, legacy90ippsWTHaarFwd_8s_Sfs,
                   ( const Ipp8s* pSrc, int len,
                        Ipp8s* pDstLow, Ipp8s* pDstHigh, int scaleFactor))
LEGACY90IPPAPI (IppStatus, legacy90ippsWTHaarFwd_32s_Sfs,
                   ( const Ipp32s* pSrc, int len,
                        Ipp32s* pDstLow, Ipp32s* pDstHigh, int scaleFactor ))
LEGACY90IPPAPI (IppStatus, legacy90ippsWTHaarFwd_64s_Sfs,
                   ( const Ipp64s* pSrc, int len,
                        Ipp64s* pDstLow, Ipp64s* pDstHigh, int scaleFactor ))

LEGACY90IPPAPI (IppStatus, legacy90ippsWTHaarInv_8s,
                   ( const Ipp8s* pSrcLow, const Ipp8s* pSrcHigh,
                                Ipp8s* pDst, int len ))
LEGACY90IPPAPI (IppStatus, legacy90ippsWTHaarInv_16s,
                   ( const Ipp16s* pSrcLow, const Ipp16s* pSrcHigh,
                                Ipp16s* pDst, int len ))
LEGACY90IPPAPI (IppStatus, legacy90ippsWTHaarInv_32s,
                   ( const Ipp32s* pSrcLow, const Ipp32s* pSrcHigh,
                                Ipp32s* pDst, int len ))
LEGACY90IPPAPI (IppStatus, legacy90ippsWTHaarInv_64s,
                   ( const Ipp64s* pSrcLow, const Ipp64s* pSrcHigh,
                                Ipp64s* pDst, int len ))

LEGACY90IPPAPI (IppStatus, legacy90ippsWTHaarInv_8s_Sfs,
                   ( const Ipp8s* pSrcLow, const Ipp8s* pSrcHigh,
                                Ipp8s* pDst, int len, int scaleFactor ))
LEGACY90IPPAPI (IppStatus, legacy90ippsWTHaarInv_32s_Sfs,
                   ( const Ipp32s* pSrcLow, const Ipp32s* pSrcHigh,
                                Ipp32s* pDst, int len, int scaleFactor ))
LEGACY90IPPAPI (IppStatus, legacy90ippsWTHaarInv_64s_Sfs,
                   ( const Ipp64s* pSrcLow, const Ipp64s* pSrcHigh,
                              Ipp64s* pDst, int len, int scaleFactor ))


/* /////////////////////////////////////////////////////////////////////////////
//          Wavelet Transform Fucntions for User Filter Banks
///////////////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////////
// Name:        ippsWTFwdInitAlloc_32f, ippsWTFwdInitAlloc_8s32f,
//              ippsWTFwdInitAlloc_8u32f, ippsWTFwdInitAlloc_16s32f,
//              ippsWTFwdInitAlloc_16u32f
//
// Purpose:     Allocate and initialize
//                forward wavelet transform pState structure.
// Parameters:
//   pState    - pointer to pointer to allocated and initialized
//                pState structure.
//   pTapsLow  - pointer to lowpass filter taps;
//   lenLow    - length of lowpass filter;
//   offsLow   - input delay of lowpass filter;
//   pTapsHigh - pointer to highpass filter taps;
//   lenHigh   - length of highpass filter;
//   offsHigh  - input delay of highpass filter;
//
// Returns:
//   ippStsNoErr        - Ok;
//   ippStsNullPtrErr   - pointer to filter taps are NULL
//                          or pointer to pState structure is NULL;
//   ippStsSizeErr      - filter length is less or equal zero;
//   ippStsWtOffsetErr  - filter delay is less than (-1).
//
// Notes:   filter input delay minimum value is (-1) that corresponds to
//            downsampling phase equal 1 (first sample excluded,
//            second included and so on);
*/
LEGACY90IPPAPI (IppStatus, legacy90ippsWTFwdInitAlloc_8s32f, (IppsWTFwdState_8s32f** pState,
        const Ipp32f* pTapsLow,  int lenLow,  int offsLow,
        const Ipp32f* pTapsHigh, int lenHigh, int offsHigh))


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

LEGACY90IPPAPI (IppStatus, legacy90ippsWTFwdSetDlyLine_8s32f, (IppsWTFwdState_8s32f* pState,
        const Ipp32f* pDlyLow, const Ipp32f* pDlyHigh))


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
LEGACY90IPPAPI (IppStatus, legacy90ippsWTFwdGetDlyLine_8s32f, (IppsWTFwdState_8s32f* pState,
        Ipp32f* pDlyLow, Ipp32f* pDlyHigh))


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
LEGACY90IPPAPI (IppStatus, legacy90ippsWTFwd_8s32f, (const Ipp8s* pSrc,
        Ipp32f* pDstLow, Ipp32f* pDstHigh, int dstLen,
        IppsWTFwdState_8s32f* pState))


/* //////////////////////////////////////////////////////////////////////
// Name:        ippsWTFwdFree_32f, ippsWTFwdFree_8s32f, ippsWTFwdFree_8u32f,
//              ippsWTFwdFree_16s32f, ippsWTFwdFree_16u32f
//
// Purpose:     Free and Deallocate forward wavelet transofrm pState structure.
//
// Parameters:
//   IppsWTFwdState_32f *pState - pointer to pState structure.
//
//  Returns:
//   ippStsNoErr            - Ok;
//   ippStsNullPtrErr       - Pointer to pState structure is NULL;
//   ippStspStateMatchErr   - Mismatch pState structure.
//
// Notes:      if pointer to pState is NULL, ippStsNoErr will be returned.
*/
LEGACY90IPPAPI (IppStatus, legacy90ippsWTFwdFree_8s32f, (IppsWTFwdState_8s32f* pState))


/* //////////////////////////////////////////////////////////////////////
// Name:        ippsWTInvInitAlloc_32f,   ippsWTInvInitAlloc_32f8s,
//              ippsWTInvInitAlloc_32f8u, ippsWTInvInitAlloc_32f16s,
//              ippsWTInvInitAlloc_32f16u
//
// Purpose:     Allocate and initialize
//                inverse wavelet transform pState structure.
// Parameters:
//   pState    - pointer to pointer to allocated and initialized
//                pState structure.
//   pTapsLow  - pointer to lowpass filter taps;
//   lenLow    - length of lowpass filter;
//   offsLow   - input delay of lowpass filter;
//   pTapsHigh - pointer to highpass filter taps;
//   lenHigh   - length of highpass filter;
//   offsHigh  - input delay of highpass filter;
//
// Returns:
//   ippStsNoErr        - Ok;
//   ippStsNullPtrErr   - pointer to filter taps are NULL
//                          or pointer to pState structure is NULL;
//   ippStsSizeErr      - filter length is less or equal zero;
//   ippStsWtOffsetErr  - filter delay is less than (-1).
//
// Notes:       filter output delay minimum value is 0 that corresponds to
//             upsampling phase equal 0 (first sample included,
//                                          second sample is zero and so on);
//              pointer to returned error status may be NULL if no error
//             diagnostic required.
*/
LEGACY90IPPAPI (IppStatus, legacy90ippsWTInvInitAlloc_32f8s, (IppsWTInvState_32f8s** pState,
        const Ipp32f* pTapsLow,  int lenLow,  int offsLow,
        const Ipp32f* pTapsHigh, int lenHigh, int offsHigh))


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
LEGACY90IPPAPI (IppStatus, legacy90ippsWTInvSetDlyLine_32f8s, (IppsWTInvState_32f8s* pState,
        const Ipp32f* pDlyLow, const Ipp32f* pDlyHigh))


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
LEGACY90IPPAPI (IppStatus, legacy90ippsWTInvGetDlyLine_32f8s, (IppsWTInvState_32f8s* pState,
        Ipp32f* pDlyLow, Ipp32f* pDlyHigh))


/* //////////////////////////////////////////////////////////////////////
// Name:        ippsWTInv_32f, ippsWTInv_32f16s, ippsWTInv_32f16u,
//              ippsWTInv_32f8s, ippsWTInv_32f8u
//
// Purpose:     Inverse wavelet transform.
//
// Parameters:
//   srcLow  - pointer to source block of
//               "low-frequency" component;
//   srcHigh - pointer to source block of
//               "high-frequency" component;
//   dstLen  - length of components.
//   dst     - pointer to destination block of
//               reconstructed data;
//   pState  - pointer to pState structure;
//
//  Returns:
//   ippStsNoErr            - Ok;
//   ippStsNullPtrErr       - some of pointers to pDst pSrcLow
//                              or pSrcHigh vectors are NULL;
//   ippStsSizeErr          - the length is less or equal zero;
//   ippStspStateMatchErr    - mismatch pState structure.
//
// Notes:      destination block length must be 2 * srcLen.
*/

LEGACY90IPPAPI (IppStatus, legacy90ippsWTInv_32f8s, (
        const Ipp32f* pSrcLow, const Ipp32f* pSrcHigh, int srcLen, Ipp8s* pDst,
        IppsWTInvState_32f8s* pState))

/* //////////////////////////////////////////////////////////////////////
// Name:        ippsWTInvFree_32f, ippsWTInvFree_32f8s, ippsWTInvFree_32f8u,
//              ippsWTInvFree_32f16s, ippsWTInvFree_32f16u
//
// Purpose:     Free and Deallocate inverse wavelet transofrm pState structure.
//
// Parameters:
//   IppsWTInvState_32f *pState - pointer to pState structure.
//
//  Returns:
//   ippStsNoErr            - Ok;
//   ippStsNullPtrErr       - Pointer to pState structure is NULL;
//   ippStspStateMatchErr   - Mismatch pState structure.
//
// Notes:      if pointer to pState is NULL, ippStsNoErr will be returned.
*/
LEGACY90IPPAPI (IppStatus, legacy90ippsWTInvFree_32f8s, (IppsWTInvState_32f8s* pState))



/* /////////////////////////////////////////////////////////////////////////////
//                  Filtering
///////////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////////
//                  Convolution functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsConv
//  Purpose:    Linear Convolution of 1D signals
//  Parameters:
//      pSrc1                pointer to the first source vector
//      pSrc2                pointer to the second source vector
//      lenSrc1              length of the first source vector
//      lenSrc2              length of the second source vector
//      pDst                 pointer to the destination vector
//  Returns:    IppStatus
//      ippStsNullPtrErr        pointer(s) to the data is NULL
//      ippStsSizeErr           length of the vectors is less or equal zero
//      ippStsMemAllocErr       no memory for internal buffers
//      ippStsNoErr             otherwise
//  Notes:
//          Length of the destination data vector is lenSrc1+lenSrc2-1.
//          The input signal are exchangeable because of
//          commutative convolution property.
//          Some other values may be returned by FFT transform functions
*/

LEGACY90IPPAPI( IppStatus, legacy90ippsConv_32f, ( const Ipp32f* pSrc1, int lenSrc1, const Ipp32f* pSrc2, int lenSrc2, Ipp32f* pDst))
LEGACY90IPPAPI( IppStatus, legacy90ippsConv_64f, ( const Ipp64f* pSrc1, int lenSrc1, const Ipp64f* pSrc2, int lenSrc2, Ipp64f* pDst))
LEGACY90IPPAPI( IppStatus, legacy90ippsConv_16s_Sfs, ( const Ipp16s* pSrc1, int lenSrc1, const Ipp16s* pSrc2, int lenSrc2, Ipp16s* pDst, int scaleFactor))


/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsConvCyclic
//  Purpose:    Cyclic Convolution of 1D signals of fixed size
//  Parameters: the pointers to data of fixed size
//  Returns:    IppStatus
//                ippStsNoErr    parameters are not checked
//  Notes:
//          The length of the convolution is given in the function name.
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsConvCyclic8x8_32f,( const Ipp32f* x,
       const Ipp32f* h, Ipp32f* y ))
LEGACY90IPPAPI(IppStatus, legacy90ippsConvCyclic8x8_16s_Sfs,( const Ipp16s* x,
       const Ipp16s* h, Ipp16s* y, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsConvCyclic4x4_32f32fc,( const Ipp32f* x,
       const Ipp32fc* h, Ipp32fc* y ))



/* /////////////////////////////////////////////////////////////////////////////
//                     IIR filters (integer taps version)
///////////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////////
//  Initialize context
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Names:         ippsIIRInitAlloc, ippsIIRInitAlloc_BiQuad, ippsIIRFree
//  Purpose:       create and initialize IIR context for AR filter
//  Parameters:
//      ppState     - double pointer to filter context
//      pState      - pointer to filter context
//      pTaps       - pointer to filter coefficients
//      order       - arbitrary filter order
//      tapsFactor  - scale factor for Ipp32s context taps
//      numBq       - number of biquads in BQ filter
//      pDelay      - pointer to delay line, may be NULL
//  Return:
//      ippStsNoErr        - Ok
//      ippStsMemAllocErr  - memory allocate error
//      ippStsNullPtrErr   - pointer(s) to ppState, pState or pTaps is NULL
//      ippStsIIROrderErr  - filter order < 0 or numBq <= 0
//      ippStsDivByZeroErr - A(0) or A(n,0) or B(n,0) is zero
//
//  the Ipp32s taps from the source Ipp32f taps and taps factor
//  may be prepared by this way, for example
//
//   ippsAbs_64f( taps, tmp, 6 );
//   ippsMax_64f( tmp, 6, &tmax );
//
//   tapsfactor = 0;
//   if( tmax > IPP_MAX_32S )
//      while( (tmax/=2) > IPP_MAX_32S ) ++tapsfactor;
//   else
//      while( (tmax*=2) < IPP_MAX_32S ) --tapsfactor;
//
//   if( tapsfactor > 0 )
//      ippsDivC_64f_I( (float)(1<<(++tapsfactor)), taps, 6 );
//   else if( tapsfactor < 0 )
//      ippsMulC_64f_I( (float)(1<<(-(tapsfactor))), taps, 6 );
//
//   ippsConvert_64f32s_Sfs ( taps, taps32s, 6, ippRndNear, 0 );
//
//  Order of coefficients is:
//     B(0),B(1),...,B(order),A(0),A(1),...,A(order)
//  A(0) != 0
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsIIRInitAlloc32s_16s, (IppsIIRState32s_16s** ppState,
       const Ipp32s* pTaps, int order, int tapsFactor, const Ipp32s* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsIIRInitAlloc32s_16s32f, (IppsIIRState32s_16s** ppState,
       const Ipp32f* pTaps, int order, const Ipp32s* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsIIRInitAlloc32sc_16sc, (IppsIIRState32sc_16sc** ppState,
       const Ipp32sc* pTaps, int order, int tapsFactor, const Ipp32sc* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsIIRInitAlloc32sc_16sc32fc, (IppsIIRState32sc_16sc** ppState,
       const Ipp32fc* pTaps, int order, const Ipp32sc* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsIIRInitAlloc32s_BiQuad_16s, (IppsIIRState32s_16s** ppState,
       const Ipp32s* pTaps, int numBq, int tapsFactor, const Ipp32s* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsIIRInitAlloc32s_BiQuad_16s32f, (IppsIIRState32s_16s** ppState,
       const Ipp32f* pTaps, int numBq, const Ipp32s* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsIIRInitAlloc32sc_BiQuad_16sc, (IppsIIRState32sc_16sc** ppState,
       const Ipp32sc* pTaps, int numBq, int tapsFactor, const Ipp32sc* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsIIRInitAlloc32sc_BiQuad_16sc32fc, (IppsIIRState32sc_16sc** ppState,
       const Ipp32fc* pTaps, int numBq, const Ipp32sc* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsIIRFree32s_16s, (IppsIIRState32s_16s* pState))
LEGACY90IPPAPI(IppStatus, legacy90ippsIIRFree32sc_16sc, (IppsIIRState32sc_16sc* pState))


/* /////////////////////////////////////////////////////////////////////////////
//  Work with Delay Line
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsIIRGetDlyLine, ippsIIRSetDlyLine
//  Purpose:    set and get delay line
//  Parameters:
//      pState              - pointer to IIR filter context
//      pDelay              - pointer to delay line to be set
//  Return:
//      ippStsContextMatchErr  - wrong context identifier
//      ippStsNullPtrErr       - pointer(s) to the data is NULL
//      ippStsNoErr            - otherwise
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsIIRGetDlyLine32s_16s, (const IppsIIRState32s_16s* pState, Ipp32s* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsIIRSetDlyLine32s_16s, (IppsIIRState32s_16s* pState, const Ipp32s* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsIIRGetDlyLine32sc_16sc, (const IppsIIRState32sc_16sc* pState, Ipp32sc* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsIIRSetDlyLine32sc_16sc, (IppsIIRState32sc_16sc* pState, const Ipp32sc* pDlyLine))

/* /////////////////////////////////////////////////////////////////////////////
//  Filtering
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Names:         ippsIIROne
//  Purpose:       IIR filter. One sample operation
//  Parameters:
//      pState              - pointer to the filter context
//      src                 - the input sample
//      pDstVal             - pointer to the output sample
//      scaleFactor         - scale factor value
//  Return:
//      ippStsContextMatchErr  - wrong context
//      ippStsNullPtrErr       - pointer(s) to pState or pDstVal is NULL
//      ippStsNoErr            - otherwise
//
//  Note: Don't modify scaleFactor value unless context is changed
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsIIROne32s_16s_Sfs, (Ipp16s src, Ipp16s* pDstVal, IppsIIRState32s_16s* pState, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippsIIROne32sc_16sc_Sfs, (Ipp16sc src, Ipp16sc* pDstVal, IppsIIRState32sc_16sc* pState, int scaleFactor))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:        ippsIIR
//  Purpose:      IIR filter. Vector filtering
//  Parameters:
//      pState              - pointer to the filter context
//      pSrc                - pointer to input data
//      pSrcDst             - pointer to input/ouput data
//      pDst                - pointer to output data
//      len                 - length of the vectors
//      scaleFactor         - scale factor value
//  Return:
//      ippStsContextMatchErr  - wrong context
//      ippStsNullPtrErr       - pointer(s) pState or pSrc or pDst is NULL
//      ippStsSizeErr          - length of the vectors <= 0
//      ippStsNoErr            - otherwise
//
//  Note: Don't modify scaleFactor value unless context is changed
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsIIR32s_16s_Sfs, (const Ipp16s* pSrc, Ipp16s* pDst, int len,
       IppsIIRState32s_16s* pState, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippsIIR32sc_16sc_Sfs, (const Ipp16sc* pSrc, Ipp16sc* pDst, int len,
       IppsIIRState32sc_16sc* pState, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippsIIR32s_16s_ISfs, (Ipp16s* pSrcDst, int len, IppsIIRState32s_16s* pState,
       int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippsIIR32sc_16sc_ISfs, (Ipp16sc* pSrcDst, int len, IppsIIRState32sc_16sc* pState,
       int scaleFactor))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:  ippsIIR_Direct_16s, ippsIIR_Direct_16s_I,
//          ippsIIROne_Direct_16s, ippsIIROne_Direct_16s_I,
//          ippsIIR_BiQuadDirect_16s, ippsIIR_BiQuadDirect_16s_I,
//          ippsIIROne_BiQuadDirect_16s, ippsIIROne_BiQuadDirect_16s_I.
//  Purpose: IIR filter with 16s taps. One sample (with suffix One), or vector
//           operation, direct (without State structure) form. Suffix "BiQuad"
//           means numBq-section filter, else the arbitrary coefficients IIR
//           filter.
//  Parameters:
//      pSrc        - pointer to the input array.
//      src         - input sample in 'One' case.
//      pDst        - pointer to the output array.
//      pDstVal     - pointer to the output sample in 'One' case.
//      pSrcDst     - pointer to the input and output array for the in-place
//                                                                   operation.
//      pSrcDstVal  - pointer to the input and output sample for in-place
//                                                     operation in 'One' case.
//      pTaps       - pointer to filter coefficients
//      order       - arbitrary filter order
//      numBq       - number biquads of BQ filter
//      pDlyLine    - pointer to delay line data
//  Return: IppStatus
//      ippStsNullPtrErr    - pointer(s) to the data is NULL
//      ippStsIIROrderErr   - filter order < 0
//      ippStsScaleRangeErr - if A(0) < 0, see "Note..."
//      ippStsMemAllocErr   - memory allocation error
//      ippStsSizeErr       - length of the vectors <= 0
//      ippStsNoErr         - otherwise
//
//  Order of the coefficients in the input taps buffer for the arbitrary
//                                                                      filter:
//     B(0),B(1),B(2)..,B(order);
//     A(0),A(1),A(2)..,A(order);
//     . . .
//  Note:
//      A(0) >= 0, and means the scale factor (not divisor !) for all the
//                                                                  other taps.
//  Order of the coefficients in the input taps buffer for BiQuad-section
//                                                                      filter:
//     B(0,0),B(0,1),B(0,2),A(0,0),A(0,1),A(0,2);
//     B(1,0),B(1,1),B(1,2),A(1,0),A(1,1),A(1,2);
//     ........
//  Note:
//      A(0,0) >= 0, A(1,0) >= 0..., and means the scale factor (not divisor !)
//      for all the other taps of each section.
*/

LEGACY90IPPAPI( IppStatus, legacy90ippsIIR_Direct_16s,( const Ipp16s* pSrc, Ipp16s* pDst,
                 int len, const Ipp16s* pTaps, int order, Ipp32s* pDlyLine ))
LEGACY90IPPAPI( IppStatus, legacy90ippsIIR_Direct_16s_I,( Ipp16s* pSrcDst, int len,
                          const Ipp16s* pTaps, int order, Ipp32s* pDlyLine ))
LEGACY90IPPAPI( IppStatus, legacy90ippsIIROne_Direct_16s,( Ipp16s src, Ipp16s* pDstVal,
                          const Ipp16s* pTaps, int order, Ipp32s* pDlyLine ))
LEGACY90IPPAPI( IppStatus, legacy90ippsIIROne_Direct_16s_I,( Ipp16s* pSrcDst,
                          const Ipp16s* pTaps, int order, Ipp32s* pDlyLine ))

LEGACY90IPPAPI( IppStatus, legacy90ippsIIR_BiQuadDirect_16s,( const Ipp16s* pSrc, Ipp16s* pDst,
             int len, const Ipp16s* pTaps, int numBq, Ipp32s* pDlyLine ))
LEGACY90IPPAPI( IppStatus, legacy90ippsIIR_BiQuadDirect_16s_I,( Ipp16s* pSrcDst, int len,
                     const Ipp16s * pTaps, int numBq, Ipp32s* pDlyLine ))
LEGACY90IPPAPI( IppStatus, legacy90ippsIIROne_BiQuadDirect_16s,( Ipp16s src, Ipp16s* pDstVal,
                      const Ipp16s* pTaps, int numBq, Ipp32s* pDlyLine ))
LEGACY90IPPAPI( IppStatus, legacy90ippsIIROne_BiQuadDirect_16s_I,( Ipp16s* pSrcDstVal,
                      const Ipp16s* pTaps, int numBq, Ipp32s* pDlyLine ))



/* ////////////////////////////////////////////////////////////////////////////
//          Initialize IIR state with external memory buffer
//////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////////
//  Name:         ippsIIRGetStateSize, ippsIIRGetStateSize_BiQuad,
//                ippsIIRGetStateSize_BiQuad_DF1_32f,
//                ippsIIRInit, ippsIIRInit_BiQuad,
//                ippsIIRInit_BiQuad_DF1_32f
//
//  Purpose:      ippsIIRGetStateSize - calculates the size of the IIR State
//                                                                   structure;
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

/* ******************************** 32s_16s ******************************** */
LEGACY90IPPAPI( IppStatus, legacy90ippsIIRGetStateSize32s_16s,( int order, int *pBufferSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsIIRGetStateSize32sc_16sc,( int order,
                                                            int *pBufferSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsIIRGetStateSize32s_BiQuad_16s,( int numBq,
                                                            int *pBufferSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsIIRGetStateSize32sc_BiQuad_16sc,( int numBq,
                                                            int *pBufferSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsIIRInit32s_16s,( IppsIIRState32s_16s** ppState,
                                const Ipp32s* pTaps, int order, int tapsFactor,
                                         const Ipp32s* pDlyLine, Ipp8u* pBuf ))
LEGACY90IPPAPI( IppStatus, legacy90ippsIIRInit32sc_16sc,( IppsIIRState32sc_16sc** ppState,
                               const Ipp32sc* pTaps, int order, int tapsFactor,
                                        const Ipp32sc* pDlyLine, Ipp8u* pBuf ))
LEGACY90IPPAPI( IppStatus, legacy90ippsIIRInit32s_BiQuad_16s,( IppsIIRState32s_16s** ppState,
                                const Ipp32s* pTaps, int numBq, int tapsFactor,
                                         const Ipp32s* pDlyLine, Ipp8u* pBuf ))
LEGACY90IPPAPI( IppStatus, legacy90ippsIIRInit32sc_BiQuad_16sc,(
                   IppsIIRState32sc_16sc** ppState, const Ipp32sc* pTaps,
             int numBq, int tapsFactor, const Ipp32sc* pDlyLine, Ipp8u* pBuf ))

/* ****************************** 32s_16s32f ******************************* */
LEGACY90IPPAPI( IppStatus, legacy90ippsIIRGetStateSize32s_16s32f,( int order,
                                                            int *pBufferSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsIIRGetStateSize32sc_16sc32fc,( int order,
                                                            int *pBufferSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsIIRGetStateSize32s_BiQuad_16s32f,( int numBq,
                                                            int *pBufferSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsIIRGetStateSize32sc_BiQuad_16sc32fc,( int numBq,
                                                            int *pBufferSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsIIRInit32s_16s32f,( IppsIIRState32s_16s** ppState,
         const Ipp32f* pTaps, int order, const Ipp32s* pDlyLine, Ipp8u* pBuf ))
LEGACY90IPPAPI( IppStatus, legacy90ippsIIRInit32sc_16sc32fc,( IppsIIRState32sc_16sc** ppState,
                                               const Ipp32fc* pTaps, int order,
                                        const Ipp32sc* pDlyLine, Ipp8u* pBuf ))
LEGACY90IPPAPI( IppStatus, legacy90ippsIIRInit32s_BiQuad_16s32f,( IppsIIRState32s_16s** ppState,
                                                const Ipp32f* pTaps, int numBq,
                                         const Ipp32s* pDlyLine, Ipp8u* pBuf ))
LEGACY90IPPAPI( IppStatus, legacy90ippsIIRInit32sc_BiQuad_16sc32fc,(
                          IppsIIRState32sc_16sc** ppState, const Ipp32fc* pTaps,
                             int numBq, const Ipp32sc* pDlyLine, Ipp8u* pBuf ))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:              ippsIIRSetTaps
//  Purpose:            set new IIR taps values to state
//  Parameters:
//      pTaps       -   pointer to new IIR taps
//      pState      -   pointer to the IIR filter state
//      tapsFactor  -   scaleFactor for taps (integer version only)
//  Return:
//      ippStsContextMatchErr  -   wrong state identifier
//      ippStsNullPtrErr       -   pointer(s) to the data is NULL
//      ippStsNoErr            -   otherwise
*/
LEGACY90IPPAPI( IppStatus, legacy90ippsIIRSetTaps32s_16s,( const Ipp32s *pTaps,
                                 IppsIIRState32s_16s* pState, int tapsFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippsIIRSetTaps32sc_16sc,( const Ipp32sc *pTaps,
                               IppsIIRState32sc_16sc* pState, int tapsFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippsIIRSetTaps32s_16s32f,( const Ipp32f *pTaps,
                                                 IppsIIRState32s_16s* pState ))
LEGACY90IPPAPI( IppStatus, legacy90ippsIIRSetTaps32sc_16sc32fc,( const Ipp32fc *pTaps,
                                               IppsIIRState32sc_16sc* pState ))


/* /////////////////////////////////////////////////////////////////////////////
//                     FIR filters (float and double taps versions)
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Initialize FIR state
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:         ippsFIRInitAlloc, ippsFIRMRInitAlloc, ippsFIRFree
//  Purpose:      create and initialize FIR state - set taps and delay line
//                and close it
//  Parameters:
//      pTaps       - pointer to the filter coefficients
//      tapsLen     - number of coefficients
//      pDlyLine    - pointer to the delay line values, can be NULL
//      state       - pointer to the FIR state created or NULL;
//   Return:
//      status      - status value returned, its value are
//         ippStsMemAllocErr      - memory allocation error
//         ippStsNullPtrErr       - pointer(s) to the data is NULL
//         ippStsFIRLenErr        - tapsLen <= 0
//         ippStsFIRMRFactorErr   - factor <= 0
//         ippStsFIRMRPhaseErr    - phase < 0 || factor <= phase
//         ippStsContextMatchErr  - wrong state identifier
//         ippStsNoErr            - otherwise
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRInitAlloc_32f, (IppsFIRState_32f** pState,
        const Ipp32f* pTaps, int tapsLen, const Ipp32f* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMRInitAlloc_32f, (IppsFIRState_32f** pState,
        const Ipp32f* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp32f* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRInitAlloc_32fc, (IppsFIRState_32fc** pState,
        const Ipp32fc* pTaps, int tapsLen, const Ipp32fc* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMRInitAlloc_32fc, (IppsFIRState_32fc** pState,
        const Ipp32fc* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp32fc* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRInitAlloc32f_16s, (IppsFIRState32f_16s** pState,
        const Ipp32f* pTaps, int tapsLen, const Ipp16s* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMRInitAlloc32f_16s, (IppsFIRState32f_16s** pState,
        const Ipp32f* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp16s* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRInitAlloc32fc_16sc, (IppsFIRState32fc_16sc** pState,
        const Ipp32fc* pTaps, int tapsLen, const Ipp16sc* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMRInitAlloc32fc_16sc, (IppsFIRState32fc_16sc** pState,
        const Ipp32fc* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp16sc* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRInitAlloc_64f, (IppsFIRState_64f** pState,
        const Ipp64f* pTaps, int tapsLen, const Ipp64f* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMRInitAlloc_64f, (IppsFIRState_64f** pState,
        const Ipp64f* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp64f* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRInitAlloc_64fc, (IppsFIRState_64fc** pState,
        const Ipp64fc* pTaps, int tapsLen, const Ipp64fc* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMRInitAlloc_64fc, (IppsFIRState_64fc** pState,
        const Ipp64fc* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp64fc* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRInitAlloc64f_32f, (IppsFIRState64f_32f** pState,
        const Ipp64f* pTaps, int tapsLen, const Ipp32f* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMRInitAlloc64f_32f, (IppsFIRState64f_32f** pState,
        const Ipp64f* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp32f* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRInitAlloc64fc_32fc, (IppsFIRState64fc_32fc** pState,
        const Ipp64fc* pTaps, int tapsLen, const Ipp32fc* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMRInitAlloc64fc_32fc, (IppsFIRState64fc_32fc** pState,
        const Ipp64fc* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp32fc* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRInitAlloc64f_32s, (IppsFIRState64f_32s** pState,
        const Ipp64f* pTaps, int tapsLen, const Ipp32s* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMRInitAlloc64f_32s, (IppsFIRState64f_32s** pState,
        const Ipp64f* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp32s* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRInitAlloc64fc_32sc, (IppsFIRState64fc_32sc** pState,
        const Ipp64fc* pTaps, int tapsLen, const Ipp32sc* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMRInitAlloc64fc_32sc, (IppsFIRState64fc_32sc** pState,
        const Ipp64fc* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp32sc* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRInitAlloc64f_16s, (IppsFIRState64f_16s** pState,
        const Ipp64f* pTaps, int tapsLen, const Ipp16s* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMRInitAlloc64f_16s, (IppsFIRState64f_16s** pState,
        const Ipp64f* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp16s* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRInitAlloc64fc_16sc, (IppsFIRState64fc_16sc** pState,
        const Ipp64fc* pTaps, int tapsLen, const Ipp16sc* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMRInitAlloc64fc_16sc, (IppsFIRState64fc_16sc** pState,
        const Ipp64fc* pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp16sc* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRFree_32f, (IppsFIRState_32f* pState))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRFree_32fc, (IppsFIRState_32fc* pState))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRFree32f_16s, (IppsFIRState32f_16s* pState))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRFree32fc_16sc, (IppsFIRState32fc_16sc* pState))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRFree_64f, (IppsFIRState_64f* pState))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRFree_64fc, (IppsFIRState_64fc* pState))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRFree64f_32f, (IppsFIRState64f_32f* pState))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRFree64fc_32fc, (IppsFIRState64fc_32fc* pState))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRFree64f_32s, (IppsFIRState64f_32s* pState))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRFree64fc_32sc, (IppsFIRState64fc_32sc* pState))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRFree64f_16s, (IppsFIRState64f_16s* pState))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRFree64fc_16sc, (IppsFIRState64fc_16sc* pState))

/* ////////////////////////////////////////////////////////////////////////////
//          Initialize FIR state with external memory buffer
//////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////////
//  Name:         ippsFIRGetStateSize, ippsFIRMRGetStateSize,
//                ippsFIRInit, ippsFIRMRInit
//  Purpose:      ippsFIRGetStateSize - calculates the size of the FIR State
//                                                                   structure;
//                ippsFIRInit - initialize FIR state - set taps and delay line
//                using external memory buffer;
//  Parameters:
//      pTaps       - pointer to the filter coefficients;
//      tapsLen     - number of coefficients;
//      pDlyLine    - pointer to the delay line values, can be NULL;
//      ppState     - pointer to the FIR state created or NULL;
//      upFactor    - multi-rate up factor;
//      upPhase     - multi-rate up phase;
//      downFactor  - multi-rate down factor;
//      downPhase   - multi-rate down phase;
//      pStateSize  - pointer where to store the calculated FIR State structure
//                                                             size (in bytes);
//   Return:
//      status      - status value returned, its value are
//         ippStsNullPtrErr       - pointer(s) to the data is NULL
//         ippStsFIRLenErr        - tapsLen <= 0
//         ippStsFIRMRFactorErr   - factor <= 0
//         ippStsFIRMRPhaseErr    - phase < 0 || factor <= phase
//         ippStsNoErr            - otherwise
*/

/* ******************************** 32s_16s ******************************** */
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRGetStateSize32s_16s,( int tapsLen, int* pStateSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRInit32s_16s,( IppsFIRState32s_16s** ppState,
      const Ipp32s *pTaps, int tapsLen, int tapsFactor, const Ipp16s *pDlyLine,
                                                             Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRGetStateSize32s_16s,( int tapsLen, int upFactor,
                                            int downFactor, int *pStateSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRInit32s_16s,( IppsFIRState32s_16s** ppState,
   const Ipp32s *pTaps, int tapsLen, int tapsFactor, int upFactor, int upPhase,
         int downFactor, int downPhase, const Ipp16s *pDlyLine, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRInit32sc_16sc,( IppsFIRState32sc_16sc** ppState,
                             const Ipp32sc *pTaps, int tapsLen, int tapsFactor,
                                       const Ipp16sc *pDlyLine, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRGetStateSize32sc_16sc,( int tapsLen, int upFactor,
                                            int downFactor, int* pStateSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRInit32sc_16sc,( IppsFIRState32sc_16sc** ppState,
  const Ipp32sc *pTaps, int tapsLen, int tapsFactor, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp16sc *pDlyLine, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRGetStateSize32sc_16sc32fc,( int tapsLen,
                                                            int *pStateSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRGetStateSize32sc_16sc,( int tapsLen,
                                                            int *pStateSize ))
/* ****************************** 32s_16s32f ******************************* */
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRGetStateSize32s_16s32f,( int tapsLen,
                                                            int* pStateSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRInit32s_16s32f,( IppsFIRState32s_16s** ppState,
      const Ipp32f *pTaps, int tapsLen, const Ipp16s *pDlyLine, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRGetStateSize32s_16s32f,( int tapsLen, int upFactor,
                                            int downFactor, int *pStateSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRInit32s_16s32f,( IppsFIRState32s_16s** ppState,
                   const Ipp32f *pTaps, int tapsLen, int upFactor, int upPhase,
         int downFactor, int downPhase, const Ipp16s *pDlyLine, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRInit32sc_16sc32fc,( IppsFIRState32sc_16sc** ppState,
    const Ipp32fc *pTaps, int tapsLen, const Ipp16sc *pDlyLine, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRGetStateSize32sc_16sc32fc,( int tapsLen,
                              int upFactor, int downFactor, int *pStateSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRInit32sc_16sc32fc,( IppsFIRState32sc_16sc** ppState,
                  const Ipp32fc *pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp16sc *pDlyLine, Ipp8u* pBuffer ))
/* ********************************** 32f ********************************** */
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRInit_32f,( IppsFIRState_32f** ppState,
   const Ipp32f *pTaps, int tapsLen, const Ipp32f *pDlyLine, Ipp8u *pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRInit_32fc,( IppsFIRState_32fc** ppState,
 const Ipp32fc *pTaps, int tapsLen, const Ipp32fc *pDlyLine, Ipp8u *pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRGetStateSize_32f,( int tapsLen, int *pBufferSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRGetStateSize_32fc,( int tapsLen, int *pBufferSize ))
/* ******************************** 32f_16s ******************************** */
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRGetStateSize32f_16s,( int tapsLen,
                                                           int* pBufferSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRInit32f_16s,( IppsFIRState32f_16s** ppState,
   const Ipp32f *pTaps, int tapsLen, const Ipp16s *pDlyLine, Ipp8u* pBuffer ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetStateSize32fc_16sc, ( int tapsLen,
                                                           int *pBufferSize ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRInit32fc_16sc, (IppsFIRState32fc_16sc** ppState,
 const Ipp32fc *pTaps, int tapsLen, const Ipp16sc *pDlyLine, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRGetStateSize32f_16s,( int tapsLen, int upFactor,
                                           int downFactor, int* pBufferSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRInit32f_16s,( IppsFIRState32f_16s** ppState,
                   const Ipp32f* pTaps, int tapsLen, int upFactor, int upPhase,
      int downFactor, int downPhase, const Ipp16s* pDlyLine, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRGetStateSize32fc_16sc,( int tapsLen, int upFactor,
                                           int downFactor, int* pBufferSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRInit32fc_16sc,( IppsFIRState32fc_16sc** ppState,
                  const Ipp32fc *pTaps, int tapsLen, int upFactor, int upPhase,
     int downFactor, int downPhase, const Ipp16sc *pDlyLine, Ipp8u* pBuffer ))
/* ********************************** 64f ********************************** */
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRInit_64f,( IppsFIRState_64f** ppState,
   const Ipp64f *pTaps, int tapsLen, const Ipp64f *pDlyLine, Ipp8u *pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRInit_64fc,( IppsFIRState_64fc** ppState,
 const Ipp64fc *pTaps, int tapsLen, const Ipp64fc *pDlyLine, Ipp8u *pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRGetStateSize_64f,( int tapsLen, int *pBufferSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRGetStateSize_64fc,( int tapsLen, int *pBufferSize ))
/* ******************************** 64f_16s ******************************** */
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRGetStateSize64f_16s,( int tapsLen,
                                                           int* pBufferSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRInit64f_16s,( IppsFIRState64f_16s** ppState,
   const Ipp64f *pTaps, int tapsLen, const Ipp16s *pDlyLine, Ipp8u* pBuffer ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetStateSize64fc_16sc, ( int tapsLen,
                                                           int *pBufferSize ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRInit64fc_16sc, (IppsFIRState64fc_16sc** ppState,
 const Ipp64fc *pTaps, int tapsLen, const Ipp16sc *pDlyLine, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRGetStateSize64f_16s,( int tapsLen, int upFactor,
                                           int downFactor, int* pBufferSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRInit64f_16s,( IppsFIRState64f_16s** ppState,
                   const Ipp64f* pTaps, int tapsLen, int upFactor, int upPhase,
      int downFactor, int downPhase, const Ipp16s* pDlyLine, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRGetStateSize64fc_16sc,( int tapsLen, int upFactor,
                                           int downFactor, int* pBufferSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRInit64fc_16sc,( IppsFIRState64fc_16sc** ppState,
                  const Ipp64fc *pTaps, int tapsLen, int upFactor, int upPhase,
     int downFactor, int downPhase, const Ipp16sc *pDlyLine, Ipp8u* pBuffer ))
/* ******************************** 64f_32s ******************************** */
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRGetStateSize64f_32s,( int tapsLen,
                                                           int* pBufferSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRInit64f_32s,( IppsFIRState64f_32s** ppState,
   const Ipp64f *pTaps, int tapsLen, const Ipp32s *pDlyLine, Ipp8u* pBuffer ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetStateSize64fc_32sc, ( int tapsLen,
                                                           int *pBufferSize ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRInit64fc_32sc, (IppsFIRState64fc_32sc** ppState,
 const Ipp64fc *pTaps, int tapsLen, const Ipp32sc *pDlyLine, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRGetStateSize64f_32s,( int tapsLen, int upFactor,
                                           int downFactor, int* pBufferSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRInit64f_32s,( IppsFIRState64f_32s** ppState,
                   const Ipp64f* pTaps, int tapsLen, int upFactor, int upPhase,
      int downFactor, int downPhase, const Ipp32s* pDlyLine, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRGetStateSize64fc_32sc,( int tapsLen, int upFactor,
                                           int downFactor, int* pBufferSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRInit64fc_32sc,( IppsFIRState64fc_32sc** ppState,
                  const Ipp64fc *pTaps, int tapsLen, int upFactor, int upPhase,
     int downFactor, int downPhase, const Ipp32sc *pDlyLine, Ipp8u* pBuffer ))
/* ******************************** 64f_32f ******************************** */
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRGetStateSize64f_32f,( int tapsLen,
                                                           int* pBufferSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRInit64f_32f,( IppsFIRState64f_32f** ppState,
   const Ipp64f *pTaps, int tapsLen, const Ipp32f *pDlyLine, Ipp8u* pBuffer ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetStateSize64fc_32fc, ( int tapsLen,
                                                           int *pBufferSize ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRInit64fc_32fc, (IppsFIRState64fc_32fc** ppState,
 const Ipp64fc *pTaps, int tapsLen, const Ipp32fc *pDlyLine, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRGetStateSize64f_32f,( int tapsLen, int upFactor,
                                           int downFactor, int* pBufferSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRInit64f_32f,( IppsFIRState64f_32f** ppState,
                   const Ipp64f* pTaps, int tapsLen, int upFactor, int upPhase,
      int downFactor, int downPhase, const Ipp32f* pDlyLine, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRGetStateSize64fc_32fc,( int tapsLen, int upFactor,
                                           int downFactor, int* pBufferSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRInit64fc_32fc,( IppsFIRState64fc_32fc** ppState,
                  const Ipp64fc *pTaps, int tapsLen, int upFactor, int upPhase,
     int downFactor, int downPhase, const Ipp32fc *pDlyLine, Ipp8u* pBuffer ))


/* /////////////////////////////////////////////////////////////////////////////
//  Names:              ippsFIRGetTaps
//  Purpose:            get FIR taps value from state
//  Parameters:
//      pTaps       -   pointer to buffer to get FIR taps
//      pState      -   pointer to the FIR filter state
//  Return:
//      ippStsContextMatchErr  -   wrong state identifier
//      ippStsNullPtrErr       -   pointer(s) to the data is NULL
//      ippStsNoErr            -   otherwise
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetTaps_32f, (const IppsFIRState_32f* pState, Ipp32f* pTaps))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetTaps_32fc, (const IppsFIRState_32fc* pState, Ipp32fc* pTaps))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetTaps32f_16s, (const IppsFIRState32f_16s* pState, Ipp32f* pTaps))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetTaps32fc_16sc, (const IppsFIRState32fc_16sc* pState, Ipp32fc* pTaps))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetTaps_64f, (const IppsFIRState_64f* pState, Ipp64f* pTaps))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetTaps_64fc, (const IppsFIRState_64fc* pState, Ipp64fc* pTaps))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetTaps64f_32f, (const IppsFIRState64f_32f* pState, Ipp64f* pTaps))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetTaps64fc_32fc, (const IppsFIRState64fc_32fc* pState, Ipp64fc* pTaps))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetTaps64f_32s, (const IppsFIRState64f_32s* pState, Ipp64f* pTaps))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetTaps64fc_32sc, (const IppsFIRState64fc_32sc* pState, Ipp64fc* pTaps))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetTaps64f_16s, (const IppsFIRState64f_16s* pState, Ipp64f* pTaps))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetTaps64fc_16sc, (const IppsFIRState64fc_16sc* pState, Ipp64fc* pTaps))


/* /////////////////////////////////////////////////////////////////////////////
//  Names:              ippsFIRGSetTaps
//  Purpose:            set FIR taps value to state
//  Parameters:
//      pTaps       -   pointer to buffer to set FIR taps
//      pState      -   pointer to the FIR filter state
//  Return:
//      ippStsContextMatchErr  -   wrong state identifier
//      ippStsNullPtrErr       -   pointer(s) to the data is NULL
//      ippStsNoErr            -   otherwise
*/

LEGACY90IPPAPI( IppStatus, legacy90ippsFIRSetTaps_32f,( const Ipp32f *pTaps,
                                                    IppsFIRState_32f* pState ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRSetTaps_32fc,( const Ipp32fc *pTaps,
                                                   IppsFIRState_32fc* pState ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRSetTaps32f_16s,( const Ipp32f *pTaps,
                                                 IppsFIRState32f_16s* pState ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRSetTaps32fc_16sc,( const Ipp32fc *pTaps,
                                               IppsFIRState32fc_16sc* pState ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRSetTaps32s_16s,( const Ipp32s *pTaps,
                                 IppsFIRState32s_16s* pState, int tapsFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRSetTaps32sc_16sc,( const Ipp32sc *pTaps,
                               IppsFIRState32sc_16sc* pState, int tapsFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRSetTaps32s_16s32f,( const Ipp32f *pTaps,
                                                 IppsFIRState32s_16s* pState ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRSetTaps32sc_16sc32fc,( const Ipp32fc *pTaps,
                                               IppsFIRState32sc_16sc* pState ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRSetTaps_64f,( const Ipp64f *pTaps,
                                                    IppsFIRState_64f* pState ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRSetTaps_64fc,( const Ipp64fc *pTaps,
                                                   IppsFIRState_64fc* pState ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRSetTaps64f_32f,( const Ipp64f *pTaps,
                                                 IppsFIRState64f_32f* pState ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRSetTaps64fc_32fc,( const Ipp64fc *pTaps,
                                               IppsFIRState64fc_32fc* pState ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRSetTaps64f_32s,( const Ipp64f *pTaps,
                                                 IppsFIRState64f_32s* pState ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRSetTaps64fc_32sc,( const Ipp64fc *pTaps,
                                               IppsFIRState64fc_32sc* pState ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRSetTaps64f_16s,( const Ipp64f *pTaps,
                                                 IppsFIRState64f_16s* pState ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRSetTaps64fc_16sc,( const Ipp64fc *pTaps,
                                               IppsFIRState64fc_16sc* pState ))



/* /////////////////////////////////////////////////////////////////////////////
//  Work with Delay Line
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Names:           ippsFIRGetDlyLine, ippsFIRSetDlyLine
//  Purpose:         set and get delay line
//  Parameters:
//      pDlyLine            - pointer to delay line
//      pState              - pointer to the filter state
//  Return:
//      ippStsContextMatchErr  - wrong state identifier
//      ippStsNullPtrErr       - pointer(s) to the data is NULL
//      ippStsNoErr            - otherwise
//  Note: pDlyLine may be NULL
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetDlyLine_32f, (const IppsFIRState_32f* pState, Ipp32f* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRSetDlyLine_32f, (IppsFIRState_32f* pState, const Ipp32f* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetDlyLine_32fc, (const IppsFIRState_32fc* pState, Ipp32fc* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRSetDlyLine_32fc, (IppsFIRState_32fc* pState, const Ipp32fc* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetDlyLine32f_16s, (const IppsFIRState32f_16s* pState, Ipp16s* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRSetDlyLine32f_16s, (IppsFIRState32f_16s* pState, const Ipp16s* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetDlyLine32fc_16sc, (const IppsFIRState32fc_16sc* pState, Ipp16sc* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRSetDlyLine32fc_16sc, (IppsFIRState32fc_16sc* pState, const Ipp16sc* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetDlyLine_64f, (const IppsFIRState_64f* pState, Ipp64f* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRSetDlyLine_64f, (IppsFIRState_64f* pState, const Ipp64f* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetDlyLine_64fc, (const IppsFIRState_64fc* pState, Ipp64fc* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRSetDlyLine_64fc, (IppsFIRState_64fc* pState, const Ipp64fc* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetDlyLine64f_32f, (const IppsFIRState64f_32f* pState, Ipp32f* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRSetDlyLine64f_32f, (IppsFIRState64f_32f* pState, const Ipp32f* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetDlyLine64fc_32fc, (const IppsFIRState64fc_32fc* pState, Ipp32fc* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRSetDlyLine64fc_32fc, (IppsFIRState64fc_32fc* pState, const Ipp32fc* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetDlyLine64f_32s, (const IppsFIRState64f_32s* pState, Ipp32s* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRSetDlyLine64f_32s, (IppsFIRState64f_32s* pState, const Ipp32s* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetDlyLine64fc_32sc, (const IppsFIRState64fc_32sc* pState, Ipp32sc* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRSetDlyLine64fc_32sc, (IppsFIRState64fc_32sc* pState, const Ipp32sc* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetDlyLine64f_16s, (const IppsFIRState64f_16s* pState, Ipp16s* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRSetDlyLine64f_16s, (IppsFIRState64f_16s* pState, const Ipp16s* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetDlyLine64fc_16sc, (const IppsFIRState64fc_16sc* pState, Ipp16sc* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRSetDlyLine64fc_16sc, (IppsFIRState64fc_16sc* pState, const Ipp16sc* pDlyLine))

/* /////////////////////////////////////////////////////////////////////////////
//  Filtering
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Names:         ippsFIROne
//  Purpose:       FIR filter. One point filtering
//  Parameters:
//      src            - input sample
//      pDstVal        - output sample
//      pState         - pointer to the filter state
//      scaleFactor    - scale factor value
//  Return:
//      ippStsContextMatchErr  - wrong state identifier
//      ippStsNullPtrErr       - pointer(s) to the data is NULL
//      ippStsNoErr            - otherwise
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne_32f, (Ipp32f src, Ipp32f* pDstVal, IppsFIRState_32f* pState))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne_32fc, (Ipp32fc src, Ipp32fc* pDstVal, IppsFIRState_32fc* pState))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne32f_16s_Sfs, (Ipp16s src, Ipp16s* pDstVal,
        IppsFIRState32f_16s* pState, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne32fc_16sc_Sfs, (Ipp16sc src, Ipp16sc* pDstVal,
        IppsFIRState32fc_16sc* pState,  int scaleFactor ))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne_64f, (Ipp64f src, Ipp64f* pDstVal, IppsFIRState_64f* pState))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne_64fc, (Ipp64fc src, Ipp64fc* pDstVal, IppsFIRState_64fc* pState))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne64f_32f, (Ipp32f src, Ipp32f* pDstVal, IppsFIRState64f_32f* pState))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne64fc_32fc, (Ipp32fc src, Ipp32fc* pDstVal, IppsFIRState64fc_32fc* pState))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne64f_32s_Sfs, (Ipp32s src, Ipp32s* pDstVal,
        IppsFIRState64f_32s* pState, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne64fc_32sc_Sfs, (Ipp32sc src, Ipp32sc* pDstVal,
        IppsFIRState64fc_32sc* pState,  int scaleFactor ))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne64f_16s_Sfs, (Ipp16s src, Ipp16s* pDstVal,
        IppsFIRState64f_16s* pState,  int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne64fc_16sc_Sfs, (Ipp16sc src, Ipp16sc* pDstVal,
         IppsFIRState64fc_16sc* pState, int scaleFactor ))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:         ippsFIR
//  Purpose:       FIR filter. Vector filtering
//  Parameters:
//      pSrcDst     - pointer to the input/output vector in in-place operation
//      pSrc        - pointer to the input vector
//      pDst        - pointer to the output vector
//      numIters    - number iterations (for single-rate equal length data vector)
//      pState      - pointer to the filter state
//      scaleFactor - scale factor value
//  Return:
//      ippStsContextMatchErr  - wrong state identifier
//      ippStsNullPtrErr       - pointer(s) to the data is NULL
//      ippStsSizeErr          - numIters is less or equal zero
//      ippStsNoErr            - otherwise
//  Note: for Multi-Rate filtering
//          length pSrc = numIters*downFactor
//          length pDst = numIters*upFactor
//          for inplace functions max this values
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR_32f, (const Ipp32f* pSrc, Ipp32f* pDst, int numIters,
        IppsFIRState_32f* pState))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR_32fc, (const Ipp32fc* pSrc, Ipp32fc* pDst, int numIters,
        IppsFIRState_32fc* pState))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR32f_16s_Sfs, (const Ipp16s* pSrc, Ipp16s* pDst, int numIters,
        IppsFIRState32f_16s* pState, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR32fc_16sc_Sfs, (const Ipp16sc* pSrc, Ipp16sc* pDst, int numIters,
        IppsFIRState32fc_16sc* pState, int scaleFactor ))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR_32f_I, (Ipp32f* pSrcDst, int numIters,
        IppsFIRState_32f* pState))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR_32fc_I, (Ipp32fc* pSrcDst, int numIters,
        IppsFIRState_32fc* pState))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR32f_16s_ISfs, (Ipp16s* pSrcDst, int numIters,
        IppsFIRState32f_16s* pState, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR32fc_16sc_ISfs, (Ipp16sc* pSrcDst, int numIters,
        IppsFIRState32fc_16sc* pState, int scaleFactor ))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR_64f, (const Ipp64f* pSrc, Ipp64f* pDst, int numIters,
        IppsFIRState_64f* pState))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR_64fc, (const Ipp64fc* pSrc, Ipp64fc* pDst, int numIters,
        IppsFIRState_64fc* pState))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR_64f_I, (Ipp64f* pSrcDst, int numIters,
        IppsFIRState_64f* pState))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR_64fc_I, (Ipp64fc* pSrcDst, int numIters,
        IppsFIRState_64fc* pState))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR64f_32f, (const Ipp32f* pSrc, Ipp32f* pDst, int numIters,
        IppsFIRState64f_32f* pState))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR64fc_32fc, (const Ipp32fc* pSrc, Ipp32fc* pDst, int numIters,
        IppsFIRState64fc_32fc* pState))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR64f_32f_I, (Ipp32f* pSrcDst, int numIters,
        IppsFIRState64f_32f* pState))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR64fc_32fc_I, (Ipp32fc* pSrcDst, int numIters,
        IppsFIRState64fc_32fc* pState))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR64f_32s_Sfs, (const Ipp32s* pSrc, Ipp32s* pDst, int numIters,
        IppsFIRState64f_32s* pState, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR64fc_32sc_Sfs, (const Ipp32sc* pSrc, Ipp32sc* pDst, int numIters,
        IppsFIRState64fc_32sc* pState, int scaleFactor ))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR64f_32s_ISfs, (Ipp32s* pSrcDst, int numIters,
        IppsFIRState64f_32s* pState,  int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR64fc_32sc_ISfs, (Ipp32sc* pSrcDst, int numIters,
        IppsFIRState64fc_32sc* pState,  int scaleFactor ))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR64f_16s_Sfs, (const Ipp16s* pSrc, Ipp16s* pDst, int numIters,
        IppsFIRState64f_16s* pState,  int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR64fc_16sc_Sfs, (const Ipp16sc* pSrc, Ipp16sc* pDst, int numIters,
        IppsFIRState64fc_16sc* pState, int scaleFactor ))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR64f_16s_ISfs, (Ipp16s* pSrcDst, int numIters,
        IppsFIRState64f_16s* pState, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR64fc_16sc_ISfs, (Ipp16sc* pSrcDst, int numIters,
        IppsFIRState64fc_16sc* pState, int scaleFactor ))

/* /////////////////////////////////////////////////////////////////////////////
//                     FIR filters (integer taps version)
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Initialize State
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Names:       ippsFIRInitAlloc, ippsFIRMRInitAlloc, ippsFIRFree
//  Purpose:     create and initialize FIR state, set taps and delay line
//  Parameters:
//      pTaps          - pointer to the filter coefficients
//      tapsLen        - number of coefficients
//      tapsFactor     - scale factor of Ipp32s taps
//      pDlyLine       - pointer delay line, may be NULL
//      state          - pointer to the state created or NULL
//  Return:
//      status         - status returned, its values are
//          ippStsMemAllocErr  - memory allocation error
//          ippStsNullPtrErr   - pointer(s) to the data is NULL
//          ippStsFIRLenErr    - tapsLen <= 0
//          ippStsFIRMRFactorErr   - factor <= 0
//          ippStsFIRMRPhaseErr    - phase < 0 || factor <= phase
//          ippStsNoErr        - otherwise
//  Notes:   pTaps and tapsFactor for Ipp32s calculate as follows
//
//          Ipp64f mpy = 1.0;
//          Ipp32f pFTaps[tapsLen];     // true values of the coefficients
//          Ipp32s pTaps[tapsLen];      // values to be pass to integer FIR
//
//          ... calculate coefficients, filling pFTaps ...
//
//          max = MAX(abs(pFTaps[i]));   for i = 0..tapsLen-1
//
//          tapsFactor = 0;
//          if (max > IPP_MAX_32S) {
//              while (max > IPP_MAX_32S) {
//                  tapsFactor++;
//                  max *= 0.5;
//                  mpy *= 0.5;
//              }
//          } else {
//              while (max < IPP_MAX_32S && tapsFactor > -17) {
//                  tapsFactor--;
//                  max += max;
//                  mpy += mpy;
//              }
//              tapsFactor++;
//              mpy *= 0.5;
//          }
//
//          for (i = 0; i < tapsLen; i++)
//              if (pFTaps[i] < 0)
//                  pSTaps[i] = (Ipp32s)(mpy*pFTaps[i]-0.5);
//              else
//                  pSTaps[i] = (Ipp32s)(mpy*pFTaps[i]+0.5);
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRInitAlloc32s_16s, (IppsFIRState32s_16s** pState,
        const Ipp32s *pTaps, int tapsLen, int tapsFactor, const Ipp16s *pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMRInitAlloc32s_16s, (IppsFIRState32s_16s** pState,
        const Ipp32s *pTaps, int tapsLen, int tapsFactor, int upFactor,
        int upPhase, int downFactor, int downPhase, const Ipp16s *pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRInitAlloc32s_16s32f, (IppsFIRState32s_16s** pState,
        const Ipp32f *pTaps, int tapsLen, const Ipp16s *pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMRInitAlloc32s_16s32f, (IppsFIRState32s_16s **pState,
        const Ipp32f *pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp16s *pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRInitAlloc32sc_16sc, (IppsFIRState32sc_16sc** pState,
        const Ipp32sc *pTaps, int tapsLen, int tapsFactor, const Ipp16sc *pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMRInitAlloc32sc_16sc, (IppsFIRState32sc_16sc** pState,
        const Ipp32sc *pTaps, int tapsLen, int tapsFactor, int upFactor,
        int upPhase, int downFactor, int downPhase, const Ipp16sc *pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRInitAlloc32sc_16sc32fc, (IppsFIRState32sc_16sc** pState,
        const Ipp32fc *pTaps, int tapsLen, const Ipp16sc *pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMRInitAlloc32sc_16sc32fc, (IppsFIRState32sc_16sc** pState,
        const Ipp32fc *pTaps, int tapsLen, int upFactor, int upPhase,
        int downFactor, int downPhase, const Ipp16sc *pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRFree32s_16s, (IppsFIRState32s_16s *pState))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRFree32sc_16sc, (IppsFIRState32sc_16sc *pState))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:              ippsFIRGetTaps
//  Purpose:            get FIR taps value from state
//  Parameters:
//      pTaps       -   pointer to buffer to get FIR taps
//      pState      -   pointer to the FIR filter state
//  Return:
//      ippStsContextMatchErr  -   wrong state identifier
//      ippStsNullPtrErr       -   pointer(s) to the data is NULL
//      ippStsNoErr            -   otherwise
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetTaps32s_16s, (const IppsFIRState32s_16s* pState,
        Ipp32s* pTaps, int* tapsFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetTaps32sc_16sc, (const IppsFIRState32sc_16sc* pState,
        Ipp32sc* pTaps, int* tapsFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetTaps32s_16s32f, (const IppsFIRState32s_16s* pState,
        Ipp32f* pTaps))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetTaps32sc_16sc32fc, (const IppsFIRState32sc_16sc* pState,
        Ipp32fc* pTaps))


/* /////////////////////////////////////////////////////////////////////////////
//  Work with Delay Line
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Names:             ippsFIRGetDlyLine, ippsFIRSetDlyLine
//  Purpose:           set and get delay line
//  Parameters:
//      pDlyLine       - pointer to the delay line
//      pState         - pointer to the FIR filter state
//  Return:
//      ippStsContextMatchErr  -   wrong state identifier
//      ippStsNullPtrErr       -   pointer(s) to the data is NULL
//      ippStsNoErr            -   otherwise
//  Note: pDlyLine may be NULL
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetDlyLine32s_16s, (const IppsFIRState32s_16s* pState,
        Ipp16s* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRSetDlyLine32s_16s, (IppsFIRState32s_16s* pState,
        const Ipp16s* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRGetDlyLine32sc_16sc, (const IppsFIRState32sc_16sc* pState,
        Ipp16sc* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRSetDlyLine32sc_16sc, (IppsFIRState32sc_16sc* pState,
        const Ipp16sc* pDlyLine))

/* /////////////////////////////////////////////////////////////////////////////
//  Filtering
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Names:            ippsFIROne, ippsFIROne
//  Purpose:          FIR filter with integer taps. One sample filtering
//  Parameters:
//      src            - input sample
//      pDstVal        - pointer to the output sample
//      pState         - pointer to the FIR filter state
//      scaleFactor    - scale factor value
//  Return:
//      ippStsContextMatchErr  - wrong state identifier
//      ippStsNullPtrErr       - pointer(s) to the data is NULL
//      ippStsNoErr            - otherwise
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne32s_16s_Sfs, (Ipp16s src, Ipp16s *pDstVal,
        IppsFIRState32s_16s *pState, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne32sc_16sc_Sfs, (Ipp16sc src, Ipp16sc *pDstVal,
        IppsFIRState32sc_16sc *pState, int scaleFactor ))


/* /////////////////////////////////////////////////////////////////////////////
//  Names:        ippsFIR
//  Purpose:      FIR filter with integer taps. Vector filtering
//  Parameters:
//      pSrc          - pointer to the input vector
//      pDst          - pointer to the output vector
//      pSrcDst       - pointer to input/output vector in in-place operation
//      numIters      - number iterations (for single-rate equal length data vector)
//      pState        - pointer to the filter state
//      scaleFactor   - scale factor value
//  Return:
//      ippStsContextMatchErr  - wrong State identifier
//      ippStsNullPtrErr       - pointer(s) to the data is NULL
//      ippStsSizeErr          - numIters <= 0
//      ippStsNoErr            - otherwise
//  Note: for Multi-Rate filtering
//          length pSrc = numIters*downFactor
//          length pDst = numIters*upFactor
//          for inplace functions max this values
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR32s_16s_Sfs, (const Ipp16s *pSrc, Ipp16s *pDst,
        int numIters, IppsFIRState32s_16s *pState, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR32sc_16sc_Sfs, (const Ipp16sc *pSrc, Ipp16sc *pDst,
        int numIters, IppsFIRState32sc_16sc *pState, int scaleFactor ))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR32s_16s_ISfs, (Ipp16s *pSrcDst, int numIters,
        IppsFIRState32s_16s *pState, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR32sc_16sc_ISfs, (Ipp16sc *pSrcDst, int numIters,
        IppsFIRState32sc_16sc *pState, int scaleFactor ))

LEGACY90IPPAPI( IppStatus, legacy90ippsFIRInitAlloc_32s,( IppsFIRState_32s** pState,
                   const Ipp32s *pTaps, int tapsLen, const Ipp32s *pDlyLine ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRGetStateSize_32s,( int tapsLen, int* pBufferSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRInit_32s,( IppsFIRState_32s** pState,
      const Ipp32s *pTaps, int tapsLen, const Ipp32s *pDlyLine, Ipp8u* pBuf ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRSetTaps_32s,( const Ipp32s *pTaps,
                                                   IppsFIRState_32s* pState ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRGetTaps_32s,( const IppsFIRState_32s* pState,
                                                              Ipp32s* pTaps ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIROne_32s_Sfs,( Ipp32s src, Ipp32s *pDstVal,
                                  IppsFIRState_32s *pState, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIR_32s_Sfs,( const Ipp32s *pSrc, Ipp32s *pDst,
                    int numIters, IppsFIRState_32s *pState, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIR_32s_ISfs,( Ipp32s *pSrcDst, int numIters,
                                  IppsFIRState_32s *pState, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRFree_32s,( IppsFIRState_32s *pState ))

LEGACY90IPPAPI( IppStatus, legacy90ippsFIRGetStateSize_16s,( int tapsLen, int* pStateSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRGetStateSize_16s,( int tapsLen, int upFactor,
                                            int downFactor, int *pStateSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRInit_16s,( IppsFIRState_16s** ppState,
      const Ipp16s *pTaps, int tapsLen, int tapsFactor, const Ipp16s *pDlyLine,
                                                            Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRInit_16s,( IppsFIRState_16s** ppState,
   const Ipp16s *pTaps, int tapsLen, int tapsFactor, int upFactor, int upPhase,
         int downFactor, int downPhase, const Ipp16s *pDlyLine, Ipp8u* pBuffer ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRInitAlloc_16s, (IppsFIRState_16s** pState,
        const Ipp16s *pTaps, int tapsLen, int tapsFactor, const Ipp16s *pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMRInitAlloc_16s, (IppsFIRState_16s** pState,
        const Ipp16s *pTaps, int tapsLen, int tapsFactor, int upFactor,
        int upPhase, int downFactor, int downPhase, const Ipp16s *pDlyLine))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRSetTaps_16s,( const Ipp16s *pTaps,
                                 IppsFIRState_16s* pState, int tapsFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRGetTaps_16s,( const IppsFIRState_16s* pState,
                                              Ipp16s* pTaps, int* tapsFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRSetDlyLine_16s,( IppsFIRState_16s *pState,
                                                      const Ipp16s *pDlyLine ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRGetDlyLine_16s,(
                         const IppsFIRState_16s *pState, Ipp16s *pDlyLine ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIROne_16s_Sfs,( Ipp16s src, Ipp16s *pDstVal,
                               IppsFIRState_16s *pState,  int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR_16s_Sfs, (const Ipp16s *pSrc, Ipp16s *pDst,
        int numIters, IppsFIRState_16s *pState, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIR_16s_ISfs,( Ipp16s *pSrcDst, int numIters,
                                IppsFIRState_16s *pState, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRFree_16s, (IppsFIRState_16s *pState))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:        ippsFIRStream
//  Purpose:      FIR stream filter with integer taps. Vector filtering
//                It does not have delay line.
//  Parameters:
//      pSrc          - pointer to the input vector
//      pDst          - pointer to the output vector
//      numIters      - number iterations (for single-rate equal length data vector)
//      pState        - pointer to the filter state
//      scaleFactor   - scale factor value
//  Return:
//      ippStsContextMatchErr  - wrong State identifier
//      ippStsNullPtrErr       - pointer(s) to the data is NULL
//      ippStsSizeErr          - numIters <= 0
//      ippStsNoErr            - otherwise
//  Note: for Multi-Rate filtering
//          length pSrc = numIters*downFactor
//          length pDst = numIters*upFactor
//          for inplace functions max this values
*/

LEGACY90IPPAPI( IppStatus, legacy90ippsFIRStreamGetStateSize_16s,( int tapsLen, int* pStateSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRStreamGetStateSize_16s,( int tapsLen, int upFactor,
                                            int downFactor, int *pStateSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRStreamInit_16s,( IppsFIRState_16s** pState,
      const Ipp16s *pTaps, int tapsLen, int tapsFactor,  IppRoundMode rndMode, Ipp8u* pBuf ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRStreamInit_16s,( IppsFIRState_16s** ppState,
   const Ipp16s *pTaps, int tapsLen, int tapsFactor, int upFactor, int upPhase,
         int downFactor, int downPhase, IppRoundMode rndMode, Ipp8u* pBuffer ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRStreamInitAlloc_16s, (IppsFIRState_16s** pState,
        const Ipp16s *pTaps, int tapsLen, int tapsFactor, IppRoundMode rndMode))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMRStreamInitAlloc_16s, (IppsFIRState_16s** pState,
        const Ipp16s *pTaps, int tapsLen, int tapsFactor, int upFactor,
        int upPhase, int downFactor, int downPhase, IppRoundMode rndMode))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:        ippsFIRStream
//  Purpose:      FIR stream filter with float taps. Vector filtering
//                It does not have delay line.
//  Parameters:
//      pSrc          - pointer to the input vector
//      pDst          - pointer to the output vector
//      numIters      - number iterations (for single-rate equal length data vector)
//      pState        - pointer to the filter state
//      scaleFactor   - scale factor value//  Return:
//      ippStsContextMatchErr  - wrong State identifier
//      ippStsNullPtrErr       - pointer(s) to the data is NULL
//      ippStsSizeErr          - numIters <= 0
//      ippStsNoErr            - otherwise
//  Note: for Multi-Rate filtering
//          length pSrc = numIters*downFactor
//          length pDst = numIters*upFactor
//          for inplace functions max this values
*/
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRStreamGetStateSize_32f,( int tapsLen, int *pBufferSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRStreamGetStateSize_32f,( int tapsLen, int upFactor,
                                             int downFactor, int *pBufferSize ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRStreamInit_32f,( IppsFIRState_32f** pState,
    const Ipp32f *pTaps, int tapsLen, Ipp8u *pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRStreamInit_32f,( IppsFIRState_32f** pState,
    const Ipp32f *pTaps, int tapsLen, int upFactor, int upPhase,
                  int downFactor, int downPhase, Ipp8u *pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRStreamInitAlloc_32f,( IppsFIRState_32f** pState,
                    const Ipp32f *pTaps, int tapsLen ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRMRStreamInitAlloc_32f,( IppsFIRState_32f** pState,
                   const Ipp32f* pTaps, int tapsLen, int upFactor, int upPhase,
                       int downFactor, int downPhase ))

/* /////////////////////////////////////////////////////////////////////////////
//                  FIR LMS filters
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//   Names:     ippsFIRLMSOne_Direct
//   Purpose:   direct form of a FIR LMS filter. One point operation.
//   Parameters:
//      src          source signal sample
//      refval       desired signal sample
//      pTapsInv     FIR taps coefficient values to be fitted
//      tapsLen      number of the taps
//      pDlyLine     pointer to the delay line values
//      pDlyIndex    pointer to the current index of delay line
//      mu           adaptation step
//      muQ15        adaptation step, integer version
//                   muQ15 = (int)(mu * (1<<15) + 0.5f)
//      pDstVal      where write output sample to
//   Return:
//      ippStsNullPtrErr  pointer the the data is null
//      ippStsSizeErr     the taps length is equal or less zero
//      ippStsNoErr       otherwise
//   Note: adaptation error value has been deleted from the parameter
//         list because it can be computed as (refval - dst).
//         taps array is inverted, delay line is of double size = tapsLen * 2
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRLMSOne_Direct_32f,( Ipp32f src, Ipp32f refval,
       Ipp32f* pDstVal, Ipp32f* pTapsInv, int tapsLen, float mu, Ipp32f* pDlyLine,
       int* pDlyIndex ))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRLMSOne_Direct32f_16s,( Ipp16s src, Ipp16s refval,
       Ipp16s* pDstVal, Ipp32f* pTapsInv, int tapsLen, float mu, Ipp16s* pDlyLine,
       int* pDlyIndex ))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRLMSOne_DirectQ15_16s,( Ipp16s src, Ipp16s refval,
       Ipp16s* pDstVal, Ipp32s* pTapsInv, int tapsLen, int muQ15, Ipp16s* pDlyLine,
       int* pDlyIndex ))



/* /////////////////////////////////////////////////////////////////////////////
//                  FIR LMS MR filters
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//   Names:      ippsFIRLMSMROne, ippsFIRLMSMROneVal
//   Purpose:    LMS MR filtering with context use
//   Parameters:
//      val       the source signal last value to update delay line
//      pDstVal   pointer to the output signal value
//      pState    pointer to the state
//   Return:
//      ippStsNullPtrErr        pointer to the data is null
//      ippStsContextMatchErr   wrong state identifier
//      ippStsNoErr             otherwise
*/
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMROne32s_16s,( Ipp32s* pDstVal,
                                            IppsFIRLMSMRState32s_16s* pState ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMROneVal32s_16s,( Ipp16s val, Ipp32s* pDstVal,
                                            IppsFIRLMSMRState32s_16s* pState ))

LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMROne32sc_16sc,( Ipp32sc* pDstVal,
                                            IppsFIRLMSMRState32sc_16sc* pState ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMROneVal32sc_16sc,( Ipp16sc val, Ipp32sc* pDstVal,
                                            IppsFIRLMSMRState32sc_16sc* pState ))

/* /////////////////////////////////////////////////////////////////////////////
//   Names:       ippsFIRLMSMRInitAlloc, ippsFIRLMSMRFree
//   Purpose:     LMS MR initialization functions
//   Parameters:
//      pState        address of pointer to the state returned
//      pTaps         pointer to the taps values. May be null
//      tapsLen       number of the taps
//      pDlyLine      pointer to the delay line. May be null
//      dlyLineIndex  current index value for the delay line
//      dlyStep       sample down factor
//      updateDly     update delay in samples
//      mu            adaptation step
//   Return:
//      ippStsNullPtrErr       pointer is null
//      ippStsContextMatchErr  wrong state identifier
//      ippStsNoErr            otherwise
*/

LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMRInitAlloc32s_16s,( IppsFIRLMSMRState32s_16s** pState,
   const Ipp32s* pTaps, int tapsLen, const Ipp16s* pDlyLine, int dlyLineIndex,
   int dlyStep, int updateDly, int mu ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMRFree32s_16s,( IppsFIRLMSMRState32s_16s* pState ))

LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMRInitAlloc32sc_16sc,( IppsFIRLMSMRState32sc_16sc** pState,
   const Ipp32sc* pTaps, int tapsLen, const Ipp16sc* pDlyLine, int dlyLineIndex,
   int dlyStep, int updateDly, int mu ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMRFree32sc_16sc,( IppsFIRLMSMRState32sc_16sc* pState ))

/* /////////////////////////////////////////////////////////////////////////////
//   Names:        ippsFIRLMSMRGetTaps, ippsFIRLMSMRSetTaps,
//                 ippsFIRLMSMRGetTapsPointer
//   Purpose:      get & set taps values
//   Parameters:
//      pState     pointer to the state
//      pOutTaps   pointer to the array to store the taps values
//      pInTaps    pointer to the taps values. May be null
//      pTaps      pointer to the state taps values. For direct access
//   Return:
//      ippStsNullPtrErr       pointer to the data is null
//      ippStsContextMatchErr  wrong state identifier
//      ippStsNoErr            otherwise
*/

LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMRSetTaps32s_16s,( IppsFIRLMSMRState32s_16s* pState,
                                        const Ipp32s* pInTaps ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMRGetTaps32s_16s,( IppsFIRLMSMRState32s_16s* pState,
                                           Ipp32s* pOutTaps ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMRGetTapsPointer32s_16s,( IppsFIRLMSMRState32s_16s* pState,
                                           Ipp32s** pTaps ))

LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMRSetTaps32sc_16sc,( IppsFIRLMSMRState32sc_16sc* pState,
                                        const Ipp32sc* pInTaps ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMRGetTaps32sc_16sc,( IppsFIRLMSMRState32sc_16sc* pState,
                                           Ipp32sc* pOutTaps ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMRGetTapsPointer32sc_16sc,(
                        IppsFIRLMSMRState32sc_16sc* pState, Ipp32sc** pTaps ))

/* /////////////////////////////////////////////////////////////////////////////
//   Names:       ippsFIRLMSMRGetDlyLine, ippsFIRLMSMRSetDlyLine,
//                ippsFIRLMSMRGetDlyVal
//   Purpose:     set or get delay line, or get one delay line value from
//                specified position
//   Parameters:
//      pState          pointer to the state structure
//      pInDlyLine      pointer to the delay line of the (see state definition)
//                          size = tapsLen * dlyStep + updateDly (may be null)
//      pOutDlyLine     pointer to the delay line of the (see state definition)
//                      size = tapsLen * dlyStep + updateDly
//      pOutDlyLineIndex  pointer to get the current delay line index
//      dlyLineIndex    current index value for the delay line
//      index           to get one value posted into delay line "index" iterations ago
//   Return:
//      ippStsNullPtrErr       pointer to the data is null
//      ippStsContextMatchErr  wrong state identifier
//      ippStsNoErr            otherwise
*/

LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMRSetDlyLine32s_16s,( IppsFIRLMSMRState32s_16s* pState,
                                        const Ipp16s* pInDlyLine, int dlyLineIndex ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMRGetDlyLine32s_16s,( IppsFIRLMSMRState32s_16s* pState,
                                        Ipp16s* pOutDlyLine, int* pOutDlyIndex ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMRGetDlyVal32s_16s,( IppsFIRLMSMRState32s_16s* pState,
                                        Ipp16s* pOutVal, int index ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMRSetDlyLine32sc_16sc,( IppsFIRLMSMRState32sc_16sc* pState,
                                        const Ipp16sc* pInDlyLine, int dlyLineIndex ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMRGetDlyLine32sc_16sc,( IppsFIRLMSMRState32sc_16sc* pState,
                                        Ipp16sc* pOutDlyLine, int* pOutDlyLineIndex ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMRGetDlyVal32sc_16sc,( IppsFIRLMSMRState32sc_16sc* pState,
                                        Ipp16sc* pOutVal, int index ))

/* /////////////////////////////////////////////////////////////////////////////
//   Names:       ippsFIRLMSMRPutVal
//   Purpose:     put one value to the delay line
//   Parameters:
//      val       the source signal last value to update delay line
//      pState    pointer to the state structure
//   Return:
//      ippStsNullPtrErr       pointer to the data is null
//      ippStsContextMatchErr  wrong state identifier
//      ippStsNoErr            otherwise
*/

LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMRPutVal32s_16s,( Ipp16s val,
                                            IppsFIRLMSMRState32s_16s* pState ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMRPutVal32sc_16sc,( Ipp16sc val,
                                            IppsFIRLMSMRState32sc_16sc* pState ))

/* /////////////////////////////////////////////////////////////////////////////
//   Names:       ippsFIRLMSMRSetMu
//   Purpose:     set new adaptation step
//   Parameters:
//      pState    pointer to the state structure
//      mu        new adaptation step
//   Return:
//      ippStsNullPtrErr       pointer to the data is null
//      ippStsContextMatchErr  wrong state identifier
//      ippStsNoErr            otherwise
*/

LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMRSetMu32s_16s,( IppsFIRLMSMRState32s_16s* pState,
                                           const int mu ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMRSetMu32sc_16sc,( IppsFIRLMSMRState32sc_16sc* pState,
                                           const int mu ))

/* /////////////////////////////////////////////////////////////////////////////
//   Names:       ippsFIRLMSMRUpdateTaps
//   Purpose:     recalculation of taps using Least Mean Square alg
//   Parameters:
//      ErrVal    difference between output and reference signal
//      pState    pointer to the state structure
//   Return:
//      ippStsNullPtrErr       pointer to the data is null
//      ippStsContextMatchErr  wrong state identifier
//      ippStsNoErr            otherwise
*/

LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMRUpdateTaps32s_16s,( Ipp32s ErrVal,
                                            IppsFIRLMSMRState32s_16s* pState ))
LEGACY90IPPAPI( IppStatus, legacy90ippsFIRLMSMRUpdateTaps32sc_16sc,( Ipp32sc ErrVal,
                                            IppsFIRLMSMRState32sc_16sc* pState ))




/* /////////////////////////////////////////////////////////////////////////////
//                     FIR filters (direct version)
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//   Names:      ippsFIROne_Direct
//   Purpose:    Directly filters a single sample through a FIR filter.
//   Parameters:
//      src            input sample
//      pDstVal        pointer to the output sample
//      pSrcDstVal     pointer to the input and output sample for in-place operation.
//      pTaps          pointer to the array containing the taps values,
//                       the number of elements in the array is tapsLen
//      tapsLen        number of elements in the array containing the taps values.
//      tapsFactor     scale factor for the taps of Ipp32s data type
//                               (for integer versions only).
//      pDlyLine       pointer to the array containing the delay line values,
//                        the number of elements in the array is 2*tapsLen
//      pDlyLineIndex  pointer to the current delay line index
//      scaleFactor    integer scaling factor value
//   Return:
//      ippStsNullPtrErr       pointer(s) to data arrays is(are) NULL
//      ippStsFIRLenErr        tapsLen is less than or equal to 0
//      ippStsNoErr            otherwise
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne_Direct_32f, (Ipp32f src, Ipp32f* pDstVal, const Ipp32f* pTaps, int tapsLen,
        Ipp32f* pDlyLine, int* pDlyLineIndex))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne_Direct_32fc, (Ipp32fc src, Ipp32fc* pDstVal, const Ipp32fc* pTaps, int tapsLen,
        Ipp32fc* pDlyLine, int* pDlyLineIndex))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne_Direct_32f_I, (Ipp32f* pSrcDstVal, const Ipp32f* pTaps, int tapsLen,
        Ipp32f* pDlyLine, int* pDlyLineIndex))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne_Direct_32fc_I, (Ipp32fc* pSrcDstVal, const Ipp32fc* pTaps, int tapsLen,
        Ipp32fc* pDlyLine, int* pDlyLineIndex))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne32f_Direct_16s_Sfs, (Ipp16s src, Ipp16s* pDstVal, const Ipp32f* pTaps, int tapsLen,
        Ipp16s* pDlyLine, int* pDlyLineIndex, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne32fc_Direct_16sc_Sfs, (Ipp16sc src, Ipp16sc* pDstVal, const Ipp32fc* pTaps, int tapsLen,
        Ipp16sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne32f_Direct_16s_ISfs, (Ipp16s* pSrcDstVal, const Ipp32f* pTaps, int tapsLen,
        Ipp16s* pDlyLine, int* pDlyLineIndex, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne32fc_Direct_16sc_ISfs, (Ipp16sc* pSrcDstVal, const Ipp32fc* pTaps, int tapsLen,
        Ipp16sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne_Direct_64f, (Ipp64f src, Ipp64f* pDstVal, const Ipp64f* pTaps, int tapsLen,
        Ipp64f* pDlyLine, int* pDlyLineIndex))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne_Direct_64fc, (Ipp64fc src, Ipp64fc* pDstVal, const Ipp64fc* pTaps, int tapsLen,
        Ipp64fc* pDlyLine, int* pDlyLineIndex))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne_Direct_64f_I, (Ipp64f* pSrcDstVal, const Ipp64f* pTaps, int tapsLen,
        Ipp64f* pDlyLine, int* pDlyLineIndex))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne_Direct_64fc_I, (Ipp64fc* pSrcDstVal, const Ipp64fc* pTaps, int tapsLen,
        Ipp64fc* pDlyLine, int* pDlyLineIndex))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne64f_Direct_32f, (Ipp32f src, Ipp32f* pDstVal, const Ipp64f* pTaps, int tapsLen,
        Ipp32f* pDlyLine, int* pDlyLineIndex))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne64fc_Direct_32fc, (Ipp32fc src, Ipp32fc* pDstVal, const Ipp64fc* pTaps, int tapsLen,
        Ipp32fc* pDlyLine, int* pDlyLineIndex))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne64f_Direct_32f_I, (Ipp32f* pSrcDstVal, const Ipp64f* pTaps, int tapsLen,
        Ipp32f* pDlyLine, int* pDlyLineIndex))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne64fc_Direct_32fc_I, (Ipp32fc* pSrcDstVal, const Ipp64fc* pTaps, int tapsLen,
        Ipp32fc* pDlyLine, int* pDlyLineIndex))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne64f_Direct_32s_Sfs, (Ipp32s src, Ipp32s* pDstVal, const Ipp64f* pTaps, int tapsLen,
        Ipp32s* pDlyLine, int* pDlyLineIndex, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne64fc_Direct_32sc_Sfs, (Ipp32sc src, Ipp32sc* pDstVal, const Ipp64fc* pTaps, int tapsLen,
        Ipp32sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne64f_Direct_32s_ISfs, (Ipp32s* pSrcDstVal, const Ipp64f* pTaps, int tapsLen,
        Ipp32s* pDlyLine, int* pDlyLineIndex, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne64fc_Direct_32sc_ISfs, (Ipp32sc* pSrcDstVal, const Ipp64fc* pTaps, int tapsLen,
        Ipp32sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne64f_Direct_16s_Sfs, (Ipp16s src, Ipp16s* pDstVal, const Ipp64f* pTaps, int tapsLen,
        Ipp16s* pDlyLine, int* pDlyLineIndex, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne64fc_Direct_16sc_Sfs, (Ipp16sc src, Ipp16sc* pDstVal, const Ipp64fc* pTaps, int tapsLen,
        Ipp16sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne64f_Direct_16s_ISfs, (Ipp16s* pSrcDstVal, const Ipp64f* pTaps, int tapsLen,
        Ipp16s* pDlyLine, int* pDlyLineIndex, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne64fc_Direct_16sc_ISfs, (Ipp16sc* pSrcDstVal, const Ipp64fc* pTaps, int tapsLen,
        Ipp16sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne32s_Direct_16s_Sfs, (Ipp16s src, Ipp16s* pDstVal,
        const Ipp32s* pTaps, int tapsLen, int tapsFactor,
        Ipp16s* pDlyLine, int* pDlyLineIndex, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne32sc_Direct_16sc_Sfs, (Ipp16sc src, Ipp16sc* pDstVal,
        const Ipp32sc* pTaps, int tapsLen, int tapsFactor,
        Ipp16sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne32s_Direct_16s_ISfs, (Ipp16s* pSrcDstVal,
        const Ipp32s* pTaps, int tapsLen, int tapsFactor,
        Ipp16s* pDlyLine, int* pDlyLineIndex, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIROne32sc_Direct_16sc_ISfs, (Ipp16sc* pSrcDstVal,
        const Ipp32sc* pTaps, int tapsLen, int tapsFactor,
        Ipp16sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ))

/* ///////////////////////////////////////////////////////////////////////////////////////////
//   Names:      ippsFIR_Direct
//   Purpose:    Directly filters a block of samples through a single-rate FIR filter.
//   Parameters:
//      pSrc           pointer to the input array
//      pDst           pointer to the output array
//      pSrcDst        pointer to the input and output array for in-place operation.
//      numIters       number of samples in the input array
//      pTaps          pointer to the array containing the taps values,
//                       the number of elements in the array is tapsLen
//      tapsLen        number of elements in the array containing the taps values.
//      tapsFactor     scale factor for the taps of Ipp32s data type
//                               (for integer versions only).
//      pDlyLine       pointer to the array containing the delay line values,
//                        the number of elements in the array is 2*tapsLen
//      pDlyLineIndex  pointer to the current delay line index
//      scaleFactor    integer scaling factor value
//   Return:
//      ippStsNullPtrErr       pointer(s) to data arrays is(are) NULL
//      ippStsFIRLenErr        tapsLen is less than or equal to 0
//      ippStsSizeErr          numIters is less than or equal to 0
//      ippStsNoErr            otherwise
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR_Direct_32f, (const Ipp32f* pSrc, Ipp32f* pDst, int numIters, const Ipp32f* pTaps, int tapsLen,
        Ipp32f* pDlyLine, int* pDlyLineIndex))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR_Direct_32fc, (const Ipp32fc* pSrc, Ipp32fc* pDst, int numIters, const Ipp32fc* pTaps, int tapsLen,
        Ipp32fc* pDlyLine, int* pDlyLineIndex))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR_Direct_32f_I, (Ipp32f* pSrcDst, int numIters, const Ipp32f* pTaps, int tapsLen,
        Ipp32f* pDlyLine, int* pDlyLineIndex))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR_Direct_32fc_I, (Ipp32fc* pSrcDst, int numIters, const Ipp32fc* pTaps, int tapsLen,
        Ipp32fc* pDlyLine, int* pDlyLineIndex))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR32f_Direct_16s_Sfs, (const Ipp16s* pSrc, Ipp16s* pDst, int numIters, const Ipp32f* pTaps, int tapsLen,
        Ipp16s* pDlyLine, int* pDlyLineIndex, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR32fc_Direct_16sc_Sfs, (const Ipp16sc* pSrc, Ipp16sc* pDst, int numIters, const Ipp32fc* pTaps, int tapsLen,
        Ipp16sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR32f_Direct_16s_ISfs, (Ipp16s* pSrcDst, int numIters, const Ipp32f* pTaps, int tapsLen,
        Ipp16s* pDlyLine, int* pDlyLineIndex, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR32fc_Direct_16sc_ISfs, (Ipp16sc* pSrcDst, int numIters, const Ipp32fc* pTaps, int tapsLen,
        Ipp16sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR_Direct_64f, (const Ipp64f* pSrc, Ipp64f* pDst, int numIters, const Ipp64f* pTaps, int tapsLen,
        Ipp64f* pDlyLine, int* pDlyLineIndex))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR_Direct_64fc, (const Ipp64fc* pSrc, Ipp64fc* pDst, int numIters, const Ipp64fc* pTaps, int tapsLen,
        Ipp64fc* pDlyLine, int* pDlyLineIndex))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR_Direct_64f_I, (Ipp64f* pSrcDst, int numIters, const Ipp64f* pTaps, int tapsLen,
        Ipp64f* pDlyLine, int* pDlyLineIndex))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR_Direct_64fc_I, (Ipp64fc* pSrcDst, int numIters, const Ipp64fc* pTaps, int tapsLen,
        Ipp64fc* pDlyLine, int* pDlyLineIndex))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR64f_Direct_32f, (const Ipp32f* pSrc, Ipp32f* pDst, int numIters, const Ipp64f* pTaps, int tapsLen,
        Ipp32f* pDlyLine, int* pDlyLineIndex))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR64fc_Direct_32fc, (const Ipp32fc* pSrc, Ipp32fc* pDst, int numIters, const Ipp64fc* pTaps, int tapsLen,
        Ipp32fc* pDlyLine, int* pDlyLineIndex))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR64f_Direct_32f_I, (Ipp32f* pSrcDst, int numIters, const Ipp64f* pTaps, int tapsLen,
        Ipp32f* pDlyLine, int* pDlyLineIndex))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR64fc_Direct_32fc_I, (Ipp32fc* pSrcDst, int numIters, const Ipp64fc* pTaps, int tapsLen,
        Ipp32fc* pDlyLine, int* pDlyLineIndex))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR64f_Direct_32s_Sfs, (const Ipp32s* pSrc, Ipp32s* pDst, int numIters, const Ipp64f* pTaps, int tapsLen,
        Ipp32s* pDlyLine, int* pDlyLineIndex, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR64fc_Direct_32sc_Sfs, (const Ipp32sc* pSrc, Ipp32sc* pDst, int numIters, const Ipp64fc* pTaps, int tapsLen,
        Ipp32sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR64f_Direct_32s_ISfs, (Ipp32s* pSrcDst, int numIters, const Ipp64f* pTaps, int tapsLen,
        Ipp32s* pDlyLine, int* pDlyLineIndex, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR64fc_Direct_32sc_ISfs, (Ipp32sc* pSrcDst, int numIters, const Ipp64fc* pTaps, int tapsLen,
        Ipp32sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR64f_Direct_16s_Sfs, (const Ipp16s* pSrc, Ipp16s* pDst, int numIters, const Ipp64f* pTaps, int tapsLen,
        Ipp16s* pDlyLine, int* pDlyLineIndex, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR64fc_Direct_16sc_Sfs, (const Ipp16sc* pSrc, Ipp16sc* pDst, int numIters, const Ipp64fc* pTaps, int tapsLen,
        Ipp16sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR64f_Direct_16s_ISfs, (Ipp16s* pSrcDst, int numIters, const Ipp64f* pTaps, int tapsLen,
        Ipp16s* pDlyLine, int* pDlyLineIndex, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR64fc_Direct_16sc_ISfs, (Ipp16sc* pSrcDst, int numIters, const Ipp64fc* pTaps, int tapsLen,
        Ipp16sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR32s_Direct_16s_Sfs, (const Ipp16s* pSrc, Ipp16s* pDst, int numIters,
        const Ipp32s* pTaps, int tapsLen, int tapsFactor,
        Ipp16s* pDlyLine, int* pDlyLineIndex, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR32sc_Direct_16sc_Sfs, (const Ipp16sc* pSrc, Ipp16sc* pDst, int numIters,
        const Ipp32sc* pTaps, int tapsLen, int tapsFactor,
        Ipp16sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIR32s_Direct_16s_ISfs, (Ipp16s* pSrcDst, int numIters,
        const Ipp32s* pTaps, int tapsLen, int tapsFactor,
        Ipp16s* pDlyLine, int* pDlyLineIndex, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIR32sc_Direct_16sc_ISfs, (Ipp16sc* pSrcDst, int numIters,
        const Ipp32sc* pTaps, int tapsLen, int tapsFactor,
        Ipp16sc* pDlyLine, int* pDlyLineIndex, int scaleFactor ))

/* ///////////////////////////////////////////////////////////////////////////////////////////
//   Names:      ippsFIRMR_Direct
//   Purpose:    Directly filters a block of samples through a multi-rate FIR filter.
//   Parameters:
//      pSrc           pointer to the input array
//      pDst           pointer to the output array
//      pSrcDst        pointer to the input and output array for in-place operation.
//      numIters       number of iterations in the input array
//      pTaps          pointer to the array containing the taps values,
//                       the number of elements in the array is tapsLen
//      tapsLen        number of elements in the array containing the taps values.
//      tapsFactor     scale factor for the taps of Ipp32s data type
//                               (for integer versions only).
//      pDlyLine       pointer to the array containing the delay line values
//      upFactor       up-sampling factor
//      downFactor     down-sampling factor
//      upPhase        up-sampling phase
//      downPhase      down-sampling phase
//      scaleFactor    integer scaling factor value
//   Return:
//      ippStsNullPtrErr       pointer(s) to data arrays is(are) NULL
//      ippStsFIRLenErr        tapsLen is less than or equal to 0
//      ippStsSizeErr          numIters is less than or equal to 0
//      ippStsFIRMRFactorErr   upFactor (downFactor) is less than or equal to 0
//      ippStsFIRMRPhaseErr    upPhase (downPhase) is negative,
//                                       or less than or equal to upFactor (downFactor).
//      ippStsNoErr            otherwise
*/


LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR_Direct_32f, (const Ipp32f* pSrc, Ipp32f* pDst, int numIters,
        const Ipp32f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp32f* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR_Direct_32fc, (const Ipp32fc* pSrc, Ipp32fc* pDst, int numIters,
        const Ipp32fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp32fc* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR_Direct_32f_I, (Ipp32f* pSrcDst, int numIters,
        const Ipp32f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp32f* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR_Direct_32fc_I, (Ipp32fc* pSrcDst, int numIters,
        const Ipp32fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp32fc* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR32f_Direct_16s_Sfs, (const Ipp16s* pSrc, Ipp16s* pDst, int numIters,
        const Ipp32f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp16s* pDlyLine, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR32fc_Direct_16sc_Sfs, (const Ipp16sc* pSrc, Ipp16sc* pDst, int numIters,
        const Ipp32fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp16sc* pDlyLine, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR32f_Direct_16s_ISfs, (Ipp16s* pSrcDst, int numIters,
        const Ipp32f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp16s* pDlyLine, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR32fc_Direct_16sc_ISfs, (Ipp16sc* pSrcDst, int numIters,
        const Ipp32fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp16sc* pDlyLine, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR_Direct_64f, (const Ipp64f* pSrc, Ipp64f* pDst, int numIters,
        const Ipp64f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp64f* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR_Direct_64fc, (const Ipp64fc* pSrc, Ipp64fc* pDst, int numIters,
        const Ipp64fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp64fc* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR_Direct_64f_I, (Ipp64f* pSrcDst, int numIters,
        const Ipp64f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp64f* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR_Direct_64fc_I, (Ipp64fc* pSrcDst, int numIters,
        const Ipp64fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp64fc* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR64f_Direct_32f, (const Ipp32f* pSrc, Ipp32f* pDst, int numIters,
        const Ipp64f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp32f* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR64fc_Direct_32fc, (const Ipp32fc* pSrc, Ipp32fc* pDst, int numIters,
        const Ipp64fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp32fc* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR64f_Direct_32f_I, (Ipp32f* pSrcDst, int numIters,
        const Ipp64f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp32f* pDlyLine))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR64fc_Direct_32fc_I, (Ipp32fc* pSrcDst, int numIters,
        const Ipp64fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp32fc* pDlyLine))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR64f_Direct_32s_Sfs, (const Ipp32s* pSrc, Ipp32s* pDst, int numIters,
        const Ipp64f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp32s* pDlyLine, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR64fc_Direct_32sc_Sfs, (const Ipp32sc* pSrc, Ipp32sc* pDst, int numIters,
        const Ipp64fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp32sc* pDlyLine, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR64f_Direct_32s_ISfs, (Ipp32s* pSrcDst, int numIters,
        const Ipp64f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp32s* pDlyLine, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR64fc_Direct_32sc_ISfs, (Ipp32sc* pSrcDst, int numIters,
        const Ipp64fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp32sc* pDlyLine, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR64f_Direct_16s_Sfs, (const Ipp16s* pSrc, Ipp16s* pDst, int numIters,
        const Ipp64f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp16s* pDlyLine, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR64fc_Direct_16sc_Sfs, (const Ipp16sc* pSrc, Ipp16sc* pDst, int numIters,
        const Ipp64fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp16sc* pDlyLine, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR64f_Direct_16s_ISfs, (Ipp16s* pSrcDst, int numIters,
        const Ipp64f* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp16s* pDlyLine, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR64fc_Direct_16sc_ISfs, (Ipp16sc* pSrcDst, int numIters,
        const Ipp64fc* pTaps, int tapsLen, int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp16sc* pDlyLine, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR32s_Direct_16s_Sfs, (const Ipp16s* pSrc, Ipp16s* pDst, int numIters,
        const Ipp32s* pTaps, int tapsLen, int tapsFactor,
        int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp16s* pDlyLine, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR32sc_Direct_16sc_Sfs, (const Ipp16sc* pSrc, Ipp16sc* pDst, int numIters,
        const Ipp32sc* pTaps, int tapsLen, int tapsFactor,
        int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp16sc* pDlyLine, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR32s_Direct_16s_ISfs, (Ipp16s* pSrcDst, int numIters,
        const Ipp32s* pTaps, int tapsLen, int tapsFactor,
        int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp16s* pDlyLine, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippsFIRMR32sc_Direct_16sc_ISfs, (Ipp16sc* pSrcDst, int numIters,
        const Ipp32sc* pTaps, int tapsLen, int tapsFactor,
        int upFactor,int upPhase, int downFactor, int downPhase,
        Ipp16sc* pDlyLine, int scaleFactor))


/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippsFIR_Direct_16s_Sfs,
//              ippsFIR_Direct_16s_ISfs,
//              ippsFIROne_Direct_16s_Sfs,
//              ippsFIROne_Direct_16s_ISfs.
//  Purpose:    Directly filters a block of samples (or one sample in 'One'
//              case) through a single-rate FIR filter with fixed point taps
//              ( Q15 ).
//   Parameters:
//      pSrc            pointer to the input array.
//      src             input sample in 'One' case.
//      pDst            pointer to the output array.
//      pDstVal         pointer to the output sample in 'One' case.
//      pSrcDst         pointer to the input and output array for in-place
//                      operation.
//      pSrcDstVal      pointer to the input and output sample for in-place
//                      operation in 'One' case.
//      numIters        number of samples in the input array.
//      pTapsQ15        pointer to the array containing the taps values,
//                      the number of elements in the array is tapsLen.
//      tapsLen         number of elements in the array containing the taps
//                      values.
//      pDlyLine        pointer to the array containing the delay line values,
//                      the number of elements in the array is 2 * tapsLen.
//      pDlyLineIndex   pointer to the current delay line index.
//      scaleFactor     integer scaling factor value.
//   Return:
//      ippStsNullPtrErr       pointer(s) to data arrays is(are) NULL.
//      ippStsFIRLenErr        tapsLen is less than or equal to 0.
//      ippStsSizeErr          sampLen is less than or equal to 0.
//      ippStsDlyLineIndexErr  current delay line index is greater or equal
//                             tapsLen, or less than 0.
//      ippStsNoErr            otherwise.
*/

LEGACY90IPPAPI( IppStatus, legacy90ippsFIR_Direct_16s_Sfs,( const Ipp16s* pSrc, Ipp16s* pDst,
          int numIters, const Ipp16s* pTapsQ15, int tapsLen, Ipp16s* pDlyLine,
                                      int* pDlyLineIndex, int scaleFactor ))

LEGACY90IPPAPI( IppStatus, legacy90ippsFIR_Direct_16s_ISfs,( Ipp16s* pSrcDst, int numIters,
                       const Ipp16s* pTapsQ15, int tapsLen, Ipp16s* pDlyLine,
                                      int* pDlyLineIndex, int scaleFactor ))

LEGACY90IPPAPI( IppStatus, legacy90ippsFIROne_Direct_16s_Sfs,( Ipp16s src, Ipp16s* pDstVal,
                       const Ipp16s* pTapsQ15, int tapsLen, Ipp16s* pDlyLine,
                                      int* pDlyLineIndex, int scaleFactor ))

LEGACY90IPPAPI( IppStatus, legacy90ippsFIROne_Direct_16s_ISfs,( Ipp16s* pSrcDstVal,
                      const Ipp16s* pTapsQ15, int tapsLen, Ipp16s * pDlyLine,
                                      int* pDlyLineIndex, int scaleFactor ))



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

LEGACY90IPPAPI(IppStatus, legacy90ippsWinBlackmanQ15_16s_ISfs, (Ipp16s* pSrcDst, int len,
                                             int alphaQ15, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippsWinBlackmanQ15_16s_I, (Ipp16s* pSrcDst, int len, int alphaQ15))
LEGACY90IPPAPI(IppStatus, legacy90ippsWinBlackmanQ15_16sc_I, (Ipp16sc* pSrcDst, int len, int alphaQ15))

LEGACY90IPPAPI(IppStatus, legacy90ippsWinBlackmanQ15_16s, (const Ipp16s* pSrc, Ipp16s* pDst, int len, int alphaQ15))
LEGACY90IPPAPI(IppStatus, legacy90ippsWinBlackmanQ15_16sc, (const Ipp16sc* pSrc, Ipp16sc* pDst, int len, int alphaQ15))


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

LEGACY90IPPAPI(IppStatus, legacy90ippsWinKaiserQ15_16s, (const Ipp16s* pSrc, Ipp16s* pDst, int len, int alphaQ15))
LEGACY90IPPAPI(IppStatus, legacy90ippsWinKaiserQ15_16s_I,(Ipp16s* pSrcDst, int len, int alphaQ15))
LEGACY90IPPAPI(IppStatus, legacy90ippsWinKaiserQ15_16sc,(const Ipp16sc* pSrc, Ipp16sc* pDst, int len, int alphaQ15))
LEGACY90IPPAPI(IppStatus, legacy90ippsWinKaiserQ15_16sc_I,(Ipp16sc* pSrcDst, int len, int alphaQ15))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsCrossCorr_32f,  ippsCrossCorr_64f,
//              ippsCrossCorr_32fc, ippsCrossCorr_64fc
//
//  Purpose:    Calculate the cross-correlation of two vectors.
//
//  Arguments:
//     pSrc1   - pointer to the vector_1 source
//     src1Len - vector_1 source length
//     pSrc2   - pointer to the vector_2 source
//     src2Len - vector_2 source length
//     pDst    - pointer to the cross correlation
//     dstLen  - length of cross-correlation
//     lowLag  - cross-correlation lowest lag
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  either pSrc1 or(and) pSrc2 are NULL
//   ippStsSizeErr     vector's length is not positive
//
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsCrossCorr_32f, (const Ipp32f* pSrc1, int src1Len, const Ipp32f* pSrc2, int src2Len, Ipp32f* pDst,  int dstLen, int lowLag))
LEGACY90IPPAPI(IppStatus, legacy90ippsCrossCorr_64f, (const Ipp64f* pSrc1, int src1Len, const Ipp64f* pSrc2, int src2Len, Ipp64f* pDst,  int dstLen, int lowLag))
LEGACY90IPPAPI(IppStatus, legacy90ippsCrossCorr_32fc,(const Ipp32fc* pSrc1, int src1Len, const Ipp32fc* pSrc2, int src2Len, Ipp32fc* pDst,  int dstLen, int lowLag))
LEGACY90IPPAPI(IppStatus, legacy90ippsCrossCorr_64fc,(const Ipp64fc* pSrc1, int src1Len, const Ipp64fc* pSrc2, int src2Len, Ipp64fc* pDst,  int dstLen, int lowLag))



/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsCrossCorr_16s_Sfs
//              ippsCrossCorr_16s64s
//
//  Purpose:    Calculate Cross Correlation and Scale Result (with saturate)
//
//  Arguments:
//     pSrc1   - pointer to the vector_1 source
//     src1Len - vector_1 source length
//     pSrc2   - pointer to the vector_2 source
//     src2Len - vector_2 source length
//     pDst    - pointer to the cross correlation
//     dstLen  - length of cross-correlation
//     lowLag  - cross-correlation lowest lag
//     scaleFactor - scale factor value
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  either pSrc1 or(and) pSrc2 are NULL
//   ippStsSizeErr     vector's length is not positive
//
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsCrossCorr_16s_Sfs, (const Ipp16s* pSrc1, int src1Len, const Ipp16s* pSrc2, int src2Len,
                                                   Ipp16s* pDst, int dstLen, int lowLag, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippsCrossCorr_16s64s, (const Ipp16s* pSrc1, int src1Len, const Ipp16s* pSrc2, int src2Len,
                                                                    Ipp64s* pDst, int dstLen, int lowLag))
/* /////////////////////////////////////////////////////////////////////////////
//                AutoCorrelation Functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Names:  ippsAutoCorr_32f,  ippsAutoCorr_NormA_32f,  ippsAutoCorr_NormB_32f,
//          ippsAutoCorr_64f,  ippsAutoCorr_NormA_64f,  ippsAutoCorr_NormB_64f,
//          ippsAutoCorr_32fc, ippsAutoCorr_NormA_32fc, ippsAutoCorr_NormB_32fc,
//          ippsAutoCorr_64fc, ippsAutoCorr_NormA_64fc, ippsAutoCorr_NormB_64fc,
//
//  Purpose:    Calculate the autocorrelation,
//              without suffix NormX specifies that the normal autocorrelation to be
//              computed;
//              suffix NormA specifies that the biased autocorrelation to be
//              computed (the resulting values are to be divided on srcLen);
//              suffix NormB specifies that the unbiased autocorrelation to be
//              computed (the resulting values are to be divided on ( srcLen - n ),
//              where "n" means current iteration).
//
//  Arguments:
//     pSrc   - pointer to the source vector
//     srcLen - source vector length
//     pDst   - pointer to the auto-correlation result vector
//     dstLen - length of auto-correlation
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  either pSrc or(and) pDst are NULL
//   ippStsSizeErr     vector's length is not positive
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsAutoCorr_32f, ( const Ipp32f* pSrc, int srcLen, Ipp32f* pDst, int dstLen ))
LEGACY90IPPAPI(IppStatus, legacy90ippsAutoCorr_NormA_32f, ( const Ipp32f* pSrc, int srcLen, Ipp32f* pDst, int dstLen ))
LEGACY90IPPAPI(IppStatus, legacy90ippsAutoCorr_NormB_32f, ( const Ipp32f* pSrc, int srcLen, Ipp32f* pDst, int dstLen ))
LEGACY90IPPAPI(IppStatus, legacy90ippsAutoCorr_64f, ( const Ipp64f* pSrc, int srcLen, Ipp64f* pDst, int dstLen ))
LEGACY90IPPAPI(IppStatus, legacy90ippsAutoCorr_NormA_64f, ( const Ipp64f* pSrc, int srcLen, Ipp64f* pDst, int dstLen ))
LEGACY90IPPAPI(IppStatus, legacy90ippsAutoCorr_NormB_64f, ( const Ipp64f* pSrc, int srcLen, Ipp64f* pDst, int dstLen ))
LEGACY90IPPAPI(IppStatus, legacy90ippsAutoCorr_32fc,( const Ipp32fc* pSrc, int srcLen, Ipp32fc* pDst, int dstLen ))
LEGACY90IPPAPI(IppStatus, legacy90ippsAutoCorr_NormA_32fc,( const Ipp32fc* pSrc, int srcLen, Ipp32fc* pDst, int dstLen ))
LEGACY90IPPAPI(IppStatus, legacy90ippsAutoCorr_NormB_32fc,( const Ipp32fc* pSrc, int srcLen, Ipp32fc* pDst, int dstLen ))
LEGACY90IPPAPI(IppStatus, legacy90ippsAutoCorr_64fc,( const Ipp64fc* pSrc, int srcLen, Ipp64fc* pDst, int dstLen ))
LEGACY90IPPAPI(IppStatus, legacy90ippsAutoCorr_NormA_64fc,( const Ipp64fc* pSrc, int srcLen, Ipp64fc* pDst, int dstLen ))
LEGACY90IPPAPI(IppStatus, legacy90ippsAutoCorr_NormB_64fc,( const Ipp64fc* pSrc, int srcLen, Ipp64fc* pDst, int dstLen ))



/* /////////////////////////////////////////////////////////////////////////////
//  Names:  ippsAutoCorr_16s_Sfs,
//          ippsAutoCorr_NormA_16s_Sfs,
//          ippsAutoCorr_NormB_16s_Sfs
//
//  Purpose:    Calculate the autocorrelation,
//              without suffix NormX specifies that the normal autocorrelation to be
//              computed;
//              suffix NormA specifies that the biased autocorrelation to be
//              computed (the resulting values are to be divided on srcLen);
//              suffix NormB specifies that the unbiased autocorrelation to be
//              computed (the resulting values are to be divided on ( srcLen - n ),
//              where n means current iteration).
//
//  Arguments:
//     pSrc   - pointer to the source vector
//     srcLen - source vector length
//     pDst   - pointer to the auto-correlation result vector
//     dstLen - length of auto-correlation
//     scaleFactor - scale factor value
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  either pSrc or(and) pDst are NULL
//   ippStsSizeErr     vector's length is not positive
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsAutoCorr_16s_Sfs,( const Ipp16s* pSrc, int srcLen, Ipp16s* pDst, int dstLen, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsAutoCorr_NormA_16s_Sfs,( const Ipp16s* pSrc, int srcLen, Ipp16s* pDst, int dstLen, int scaleFactor ))
LEGACY90IPPAPI(IppStatus, legacy90ippsAutoCorr_NormB_16s_Sfs,( const Ipp16s* pSrc, int srcLen, Ipp16s* pDst, int dstLen, int scaleFactor ))



/* ///////////////////////////////////////////////////////////////////////////
//  Names:      ippsGetVarPointDV_16sc
//  Purpose:    Fills the array VariantPoint with information about 8
//              (if State = 32,64) or 4 (if State = 16) closest to the
//              refPoint complex points (stores the indexes in the
//              offset table and errors between refPoint and the
//              current point)
//  Return:
//  ippStsNoErr         Ok
//  ippStsNullPtrErr    Any of the specified pointers is NULL
//  Parameters:
//  pSrc            pointer to the reference point in format 9:7
//  pDst            pointer to the closest to the reference point left
//                  and bottom comlexpoint in format 9:7
//  pVariantPoint   pointer to the array where the information is stored
//  pLabel          pointer to the labels table
//  state           number of states of the convolution coder
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsGetVarPointDV_16sc,(const Ipp16sc *pSrc,Ipp16sc *pDst,
       Ipp16sc *pVariantPoint,const Ipp8u *pLabel,int state))


/* ///////////////////////////////////////////////////////////////////////////
//  Names:      ippsCalcStatesDV_16sc
//  Purpose:    Computes possible states of the Viterbi decoder
//  Return:
//  ippStsNoErr         OK
//  ippStsNullPtrErr    Any of the specified pointers is NULL
//  Parameters:
//  pPathError          pointer to the table of path error metrics
//  pNextState          pointer to the next state table
//  pBranchError        pointer to the branch error table
//  pCurrentSubsetPoint pointer to the current 4D subset
//  pPathTable          pointer to the Viterbi path table
//  state               number of states of the convolution coder
//  presentIndex        start index in Viterbi Path table
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsCalcStatesDV_16sc,(const Ipp16u *pathError,
       const Ipp8u *pNextState, Ipp16u *pBranchError,
       const Ipp16s *pCurrentSubsetPoint, Ipp16s *pPathTable,
       int state,int presentIndex))

/* ///////////////////////////////////////////////////////////////////////////
//  Names:      ippsBuildSymblTableDV4D_16s
//  Purpose:    Fills the array with an information of possible 4D symbols
//  Return:
//  ippStsNoErr         OK
//  ippStsNullPtrErr    Any of the specified pointers is NULL
//  Parameters:
//  pVariantPoint       pointer to the array of possible 2D symbols
//  pCurrentSubsetPoint pointer to the current array of 4D symbols
//  state               number of states of the convolution coder
//  bitInversion        bit Inversion
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsBuildSymblTableDV4D_16sc,(const Ipp16sc *pVariantPoint,
       Ipp16sc *pCurrentSubsetPoint,int state,int bitInversion ))

/* ///////////////////////////////////////////////////////////////////////////
//  Names:      ippsUpdatePathMetricsDV_16u
//  Purpose:    Searches for the minimum path metric and updates states of the decoder
//  Return:
//  ippStsNoErr         OK
//  ippStsNullPtrErr    Any of the specified pointers is NULL
//  Parameters:
//  pBranchError        pointer to the branch error table
//  pMinPathError       pointer to the current minimum path error metric
//  pMinSost            pointer to the state with minimum path metric
//  pPathError          pointer to table of path error metrics
//  state               number of states of the convolution coder
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsUpdatePathMetricsDV_16u,(Ipp16u *pBranchError,
       Ipp16u *pMinPathError,Ipp8u *pMinSost,Ipp16u *pPathError,int state))



/* /////////////////////////////////////////////////////////////////////////////
//                  Hilbert Context Functions
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsHilbertInitAlloc_32f32fc, ippsHilbertFree_32f32fc,
//              ippsHilbertInitAlloc_16s32fc, ippsHilbertFree_16s32fc,
//              ippsHilbertInitAlloc_16s16sc, ippsHilbertFree_16s16sc
//  Purpose:    create, initialize and delete Hilbert context
//  Arguments:
//     pSpec    - where write pointer to new context
//     length   - number of samples in Hilbert
//     hint     - code specific use hints (DFT)
//  Return:
//     ippStsNoErr            no errors
//     ippStsNullPtrErr       pSpec == NULL
//     ippStsSizeErr          bad the length value
//     ippStsContextMatchErr  bad context identifier
//     ippStsMemAllocErr      memory allocation error
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsHilbertInitAlloc_16s32fc, (IppsHilbertSpec_16s32fc **pSpec,
                                                 int length, IppHintAlgorithm hint))
LEGACY90IPPAPI(IppStatus, legacy90ippsHilbertInitAlloc_16s16sc, (IppsHilbertSpec_16s16sc **pSpec,
                                                 int length, IppHintAlgorithm hint))
LEGACY90IPPAPI(IppStatus, legacy90ippsHilbertFree_16s32fc, (IppsHilbertSpec_16s32fc *pSpec))
LEGACY90IPPAPI(IppStatus, legacy90ippsHilbertFree_16s16sc, (IppsHilbertSpec_16s16sc *pSpec))


/* /////////////////////////////////////////////////////////////////////////////
//                  Hilbert Transform Functions
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsHilbert_32f32fc,
//              ippsHilbert_16s32fc,
//              ippsHilbert_16s16sc_Sfs
//  Purpose:    compute Hilbert transform of the real signal
//  Arguments:
//     pSrc     - pointer to source real signal
//     pDst     - pointer to destination complex signal
//     pSpec    - pointer to Hilbert context
//     scaleFactor - scale factor for output signal
//  Return:
//     ippStsNoErr            no errors
//     ippStsNullPtrErr       pointer(s) to the data is NULL
//     ippStsContextMatchErr  bad context identifier
//     ippStsMemAllocErr      memory allocation error
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsHilbert_16s32fc, (const Ipp16s *pSrc, Ipp32fc *pDst,
                                        IppsHilbertSpec_16s32fc *pSpec))
LEGACY90IPPAPI(IppStatus, legacy90ippsHilbert_16s16sc_Sfs, (const Ipp16s *pSrc, Ipp16sc *pDst,
                                        IppsHilbertSpec_16s16sc *pSpec, int scaleFactor))


/*
//  Purpose:            Creates ramp vector
//
//  Parameters:
//    pDst              A pointer to the destination vector
//    len               Vector's length
//    offset            Offset value
//    slope             Slope coefficient
//
//  Return:
//    ippStsNoErr       No error
//    ippStsNullPtrErr  pDst pointer is NULL
//    ippStsBadSizeErr  Vector's length is less or equal zero
//    ippStsNoErr       No error
//
//  Notes:              Dst[n] = offset + slope * n
//
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsVectorSlope_8s, ( Ipp8s*  pDst, int len, Ipp32f offset, Ipp32f slope ))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:      ippsDemodulateFM_CToR_16s
//  Purpose:    FM demodulate
//  Return:
//   IPP_NO_ERR                 Ok
//   IPP_NULL_PTR_ERR           Some of pointers are NULL
//   IPP_BADSIZE_ERR            The length of the array is less or equal zero
//  Parameters:
//   pSrcRe     pointer to input vector of Real data
//   pSrcIm     pointer to input vector of Image data
//   pDst       pointer to output vector
//   len        a length of the array
//   pDlyPoint  pointer to earlier data
*/
LEGACY90IPPAPI(IppStatus, legacy90ippsDemodulateFM_CToR_16s,( const Ipp16s* pSrcRe,
       const Ipp16s *pSrcIm, Ipp16s *pDst, int len, Ipp16sc *pDlyPoint ))



/* ///////////////////////////////////////////////////////////////////////////
//  Name:    ippsCauchy_32f_I, ippsCauchyD_32f_I, ippsCauchyDD2_32f_I
//
//  Purpose: Compute Cauchy robust error function or its 1st, 2nd derivatives
//
//  Return:
//    ippStsNoErr         Ok
//    ippStsNullPtrErr    Some of the pointers are NULL's
//    ippStsSizeErr       Length is negative
//    ippStsOutOfRangeErr C is negative
//
//  Arguments:
//    pSrcDst          The input/output array of function arguments/values.
//    pD2F             The array of values of the 2nd derivative.
//    len              Length of srcdst and d2fval
//    C                Cauchy function parameter
*/

LEGACY90IPPAPI(IppStatus, legacy90ippsCauchy_32f_I, (Ipp32f* pSrcDst, int len, Ipp32f C))
LEGACY90IPPAPI(IppStatus, legacy90ippsCauchyD_32f_I, (Ipp32f* pSrcDst, int len, Ipp32f C))
LEGACY90IPPAPI(IppStatus, legacy90ippsCauchyDD2_32f_I, (Ipp32f* pSrcDst, Ipp32f* pD2F, int len, Ipp32f C))



#if defined (_IPP_STDCALL_CDECL)
  #undef  _IPP_STDCALL_CDECL
  #define __stdcall __cdecl
#endif


#ifdef __cplusplus
}
#endif

#endif /* __IPPS_90_LEGACY_H__ */
