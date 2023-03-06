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
//               Image Processing (ippIP)
//                    Legacy Library
//
*/

#if !defined( __IPPI_90_LEGACY_H__ )
#define __IPPI_90_LEGACY_H__

#include "ippdefs90legacy.h"
#include "ippi90legacy_redef.h"

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
LEGACY90IPPAPI( IppStatus, legacy90ippiInit, ( void ))


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
LEGACY90IPPAPI( IppStatus, legacy90ippiSetNumThreads, ( int numThr ) )

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
LEGACY90IPPAPI( IppStatus, legacy90ippiGetNumThreads, (int* pNumThr) )

/*////////////////////////////////////////////////////////////////////////////*/


/* ///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//                   Functions declarations
//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiGetLibVersion
//  Purpose:    gets the version of the library
//  Returns:    structure containing information about the current version of
//  the Intel IPP library for image processing
//  Parameters:
//
//  Notes:      there is no need to release the returned structure
*/
LEGACY90IPPAPI( const IppLibraryVersion*, legacy90ippiGetLibVersion, (void) )


/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiComplement_32s_C1IR
//
//  Purpose:    Converts negative integer number from complement to
//              direct code reserving the sign in the upper bit.
//
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         Pointer is NULL
//    ippStsStepErr            Step is less than or equal to zero
//    ippStsStrideErr          Step is less than the width of an image
//
//  Parameters:
//    pSrcDst                  Pointer to the source and destination image
//    srcdstStep               Step in bytes through the image
//    roiSize                  Size of the ROI
*/

LEGACY90IPPAPI (IppStatus, legacy90ippiComplement_32s_C1IR, ( Ipp32s* pSrcDst, int srcdstStep, IppiSize roiSize ))



/* /////////////////////////////////////////////////////////////////////////////
//                  Arithmetic Functions Operating on Complex Data
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiAddC_32fc_C1R, ippiAddC_32fc_C3R, ippiAddC_32fc_AC4R,
//              ippiSubC_32fc_C1R, ippiSubC_32fc_C3R, ippiSubC_32fc_AC4R,
//              ippiMulC_32fc_C1R, ippiMulC_32fc_C3R, ippiMulC_32fc_AC4R
//              ippiDivC_32fc_C1R, ippiDivC_32fc_C3R, ippiDivC_32fc_AC4R
//
//  Purpose:    Adds, subtracts, multiplies, or divides pixel values of an image
//              and a constant and places the results in the destination image.
//
//  Returns:
//    ippStsNoErr          OK
//    ippStsNullPtrErr     One of the pointers is NULL
//    ippStsSizeErr        The roiSize has a field with negative or zero value
//    ippStsStepErr        One of the step values is less than or equal to zero
//    ippStsDivByZeroErr   The constant is equal to zero (for division)
//
//  Parameters:
//    value                The constant value (constant vector for multi-channel images)
//    pSrc                 Pointer to the source image
//    srcStep              Step through the source image
//    pDst                 Pointer to the destination image
//    dstStep              Step through the destination image
//    roiSize              Size of the ROI
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiAddC_32fc_C1R,  (const Ipp32fc* pSrc, int srcStep, Ipp32fc value, Ipp32fc* pDst,
                                      int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddC_32fc_C3R,  (const Ipp32fc* pSrc, int srcStep, const Ipp32fc value[3],
                                      Ipp32fc* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddC_32fc_AC4R, (const Ipp32fc* pSrc, int srcStep, const Ipp32fc value[3],
                                      Ipp32fc* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiSubC_32fc_C1R,  (const Ipp32fc* pSrc, int srcStep, Ipp32fc value, Ipp32fc* pDst,
                                      int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiSubC_32fc_C3R,  (const Ipp32fc* pSrc, int srcStep, const Ipp32fc value[3],
                                      Ipp32fc* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiSubC_32fc_AC4R, (const Ipp32fc* pSrc, int srcStep, const Ipp32fc value[3],
                                      Ipp32fc* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulC_32fc_C1R,  (const Ipp32fc* pSrc, int srcStep, Ipp32fc value, Ipp32fc* pDst,
                                      int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulC_32fc_C3R,  (const Ipp32fc* pSrc, int srcStep, const Ipp32fc value[3],
                                      Ipp32fc* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulC_32fc_AC4R, (const Ipp32fc* pSrc, int srcStep, const Ipp32fc value[3],
                                      Ipp32fc* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiDivC_32fc_C1R,  (const Ipp32fc* pSrc,
                                      int srcStep, Ipp32fc value, Ipp32fc* pDst,
                                      int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiDivC_32fc_C3R,  (const Ipp32fc* pSrc,
                                      int srcStep, const Ipp32fc value[3], Ipp32fc* pDst,
                                      int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiDivC_32fc_AC4R, (const Ipp32fc* pSrc,
                                      int srcStep, const Ipp32fc value[3], Ipp32fc* pDst,
                                      int dstStep, IppiSize roiSize))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiAddC_32fc_C1IR, ippiAddC_32fc_C3IR, ippiAddC_32fc_AC4IR,
//              ippiSubC_32fc_C1IR, ippiSubC_32fc_C3IR, ippiSubC_32fc_AC4IR,
//              ippiMulC_32fc_C1IR, ippiMulC_32fc_C3IR, ippiMulC_32fc_AC4IR
//              ippiDivC_32fc_C1IR, ippiDivC_32fc_C3IR, ippiDivC_32fc_AC4IR
//
//  Purpose:    Adds, subtracts, multiplies, or divides pixel values of an image
//              and a constant and places the results in the same image.
//
//  Returns:
//    ippStsNoErr            OK
//    ippStsNullPtrErr       The pointer pSrcDst is NULL
//    ippStsSizeErr          The roiSize has a field with negative or zero value
//    ippStsStepErr          The step value is less than or equal to zero
//    ippStsDivByZeroErr     The constant is equal to zero (for division)
//
//  Parameters:
//    value                  The constant value (constant vector for multi-channel images)
//    pSrcDst                Pointer to the image
//    srcDstStep             Step through the image
//    roiSize                Size of the ROI
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiAddC_32fc_C1IR,  (Ipp32fc value, Ipp32fc* pSrcDst, int srcDstStep,
                                       IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddC_32fc_C3IR,  (const Ipp32fc value[3], Ipp32fc* pSrcDst, int srcDstStep,
                                       IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddC_32fc_AC4IR, (const Ipp32fc value[3], Ipp32fc* pSrcDst, int srcDstStep,
                                       IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiSubC_32fc_C1IR,  (Ipp32fc value, Ipp32fc* pSrcDst, int srcDstStep,
                                       IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiSubC_32fc_C3IR,  (const Ipp32fc value[3], Ipp32fc* pSrcDst, int srcDstStep,
                                       IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiSubC_32fc_AC4IR, (const Ipp32fc value[3], Ipp32fc* pSrcDst, int srcDstStep,
                                       IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulC_32fc_C1IR,  (Ipp32fc value, Ipp32fc* pSrcDst, int srcDstStep,
                                       IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulC_32fc_C3IR,  (const Ipp32fc value[3], Ipp32fc* pSrcDst, int srcDstStep,
                                       IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulC_32fc_AC4IR, (const Ipp32fc value[3], Ipp32fc* pSrcDst, int srcDstStep,
                                       IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiDivC_32fc_C1IR,  (Ipp32fc value, Ipp32fc* pSrcDst, int srcDstStep,
                                       IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiDivC_32fc_C3IR,  (const Ipp32fc value[3], Ipp32fc* pSrcDst, int srcDstStep,
                                       IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiDivC_32fc_AC4IR, (const Ipp32fc value[3], Ipp32fc* pSrcDst, int srcDstStep,
                                       IppiSize roiSize))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiAdd_32fc_C1IR, ippiAdd_32fc_C3IR, ippiAdd_32fc_AC4IR,
//              ippiSub_32fc_C1IR, ippiSub_32fc_C3IR, ippiSub_32fc_AC4IR,
//              ippiMul_32fc_C1IR, ippiMul_32fc_C3IR, ippiMul_32fc_AC4IR
//              ippiDiv_32fc_C1IR, ippiDiv_32fc_C3IR, ippiDiv_32fc_AC4IR
//
//  Purpose:    Adds, subtracts, multiplies, or divides pixel values of two
//              source images and places the results in the first source image.
//
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         One of the pointers is NULL
//    ippStsSizeErr            The roiSize has a field with negative or zero value
//    ippStsStepErr            Any of the step values is less than or equal to zero
//    ippStsDivByZero          For division only - a warning that a divisor value (pixel value
//                             of the second image) equals zero, the function execution is continued.
//                               If a dividend is equal to zero, then the result is NAN_32F;
//                               if it is greater than zero, then the result is INF_32F,
//                               if it is less than zero, then the result is INF_NEG_32F
//
//  Parameters:
//    pSrc                     Pointer to the second source image
//    srcStep                  Step through the second source image
//    pSrcDst                  Pointer to the first source/destination image
//    srcDstStep               Step through the first source/destination image
//    roiSize                  Size of the ROI
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiAdd_32fc_C1IR,  (const Ipp32fc* pSrc, int srcStep, Ipp32fc* pSrcDst,
                                      int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiAdd_32fc_C3IR,  (const Ipp32fc* pSrc, int srcStep, Ipp32fc* pSrcDst,
                                      int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiAdd_32fc_AC4IR, (const Ipp32fc* pSrc, int srcStep, Ipp32fc* pSrcDst,
                                      int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiSub_32fc_C1IR,  (const Ipp32fc* pSrc, int srcStep, Ipp32fc* pSrcDst,
                                      int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiSub_32fc_C3IR,  (const Ipp32fc* pSrc, int srcStep, Ipp32fc* pSrcDst,
                                      int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiSub_32fc_AC4IR, (const Ipp32fc* pSrc, int srcStep, Ipp32fc* pSrcDst,
                                      int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiMul_32fc_C1IR,  (const Ipp32fc* pSrc, int srcStep, Ipp32fc* pSrcDst,
                                      int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiMul_32fc_C3IR,  (const Ipp32fc* pSrc, int srcStep, Ipp32fc* pSrcDst,
                                      int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiMul_32fc_AC4IR, (const Ipp32fc* pSrc, int srcStep, Ipp32fc* pSrcDst,
                                      int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiDiv_32fc_C1IR,  (const Ipp32fc* pSrc, int srcStep, Ipp32fc* pSrcDst,
                                      int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiDiv_32fc_C3IR,  (const Ipp32fc* pSrc, int srcStep, Ipp32fc* pSrcDst,
                                      int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiDiv_32fc_AC4IR, (const Ipp32fc* pSrc, int srcStep, Ipp32fc* pSrcDst,
                                      int srcDstStep, IppiSize roiSize))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiAdd_32fc_C1R, ippiAdd_32fc_C3R, ippiAdd_32fc_AC4R,
//              ippiSub_32fc_C1R, ippiSub_32fc_C3R, ippiSub_32fc_AC4R,
//              ippiMul_32fc_C1R, ippiMul_32fc_C3R, ippiMul_32fc_AC4R
//              ippiDiv_32fc_C1R, ippiDiv_32fc_C3R, ippiDiv_32fc_AC4R
//
//  Purpose:    Adds, subtracts, multiplies, or divides pixel values of two
//              source images and places the results in the destination image.
//
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         One of the pointers is NULL
//    ippStsSizeErr            The roiSize has a field with negative or zero value
//    ippStsStepErr            Any of the step values is less than or equal to zero
//    ippStsDivByZero          For division only - a warning that a divisor value (pixel value
//                             of the second image) equals zero, the function execution is continued.
//                               If a dividend is equal to zero, then the result is NAN_32F;
//                               if it is greater than zero, then the result is INF_32F,
//                               if it is less than zero, then the result is INF_NEG_32F
//
//  Parameters:
//    pSrc1, pSrc2             Pointers to the first and second source images
//    src1Step, src2Step       Step through the first and second source images
//    pDst                     Pointer to the destination image
//    dstStep                  Step through the destination image
//    roiSize                  Size of the ROI
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiAdd_32fc_C1R,  (const Ipp32fc* pSrc1, int src1Step, const Ipp32fc* pSrc2,
                                     int src2Step, Ipp32fc* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiAdd_32fc_C3R,  (const Ipp32fc* pSrc1, int src1Step, const Ipp32fc* pSrc2,
                                     int src2Step, Ipp32fc* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiAdd_32fc_AC4R, (const Ipp32fc* pSrc1, int src1Step, const Ipp32fc* pSrc2,
                                     int src2Step, Ipp32fc* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiSub_32fc_C1R,  (const Ipp32fc* pSrc1, int src1Step, const Ipp32fc* pSrc2,
                                     int src2Step, Ipp32fc* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiSub_32fc_C3R,  (const Ipp32fc* pSrc1, int src1Step, const Ipp32fc* pSrc2,
                                     int src2Step, Ipp32fc* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiSub_32fc_AC4R, (const Ipp32fc* pSrc1, int src1Step, const Ipp32fc* pSrc2,
                                     int src2Step, Ipp32fc* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiMul_32fc_C1R,  (const Ipp32fc* pSrc1, int src1Step, const Ipp32fc* pSrc2,
                                     int src2Step, Ipp32fc* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiMul_32fc_C3R,  (const Ipp32fc* pSrc1, int src1Step, const Ipp32fc* pSrc2,
                                     int src2Step, Ipp32fc* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiMul_32fc_AC4R, (const Ipp32fc* pSrc1, int src1Step, const Ipp32fc* pSrc2,
                                     int src2Step, Ipp32fc* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiDiv_32fc_C1R,  (const Ipp32fc* pSrc1, int src1Step, const Ipp32fc* pSrc2,
                                     int src2Step, Ipp32fc* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiDiv_32fc_C3R,  (const Ipp32fc* pSrc1, int src1Step, const Ipp32fc* pSrc2,
                                     int src2Step, Ipp32fc* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiDiv_32fc_AC4R, (const Ipp32fc* pSrc1, int src1Step, const Ipp32fc* pSrc2,
                                     int src2Step, Ipp32fc* pDst, int dstStep, IppiSize roiSize))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiAdd_16sc_C1IRSfs, ippiAdd_16sc_C3IRSfs, ippiAdd_16sc_AC4IRSfs,
//              ippiSub_16sc_C1IRSfs, ippiSub_16sc_C3IRSfs, ippiSub_16sc_AC4IRSfs,
//              ippiMul_16sc_C1IRSfs, ippiMul_16sc_C3IRSfs, ippiMul_16sc_AC4IRSfs,
//              ippiDiv_16sc_C1IRSfs, ippiDiv_16sc_C3IRSfs, ippiDiv_16sc_AC4IRSfs
//
//  Purpose:    Adds, subtracts, multiplies, or divides pixel values of two
//              source images and places the results in the first source image.
//
//  Returns:
//    ippStsNoErr              OK
//    iippStsNullPtrErr        One of the pointers is NULL
//    ippStsSizeErr            The roiSize has a field with negative or zero value
//    ippStsStepErr            Any of the step values is less than or equal to zero
//    ippStsDivByZero          For division only - a warning that a divisor value (pixel value
//                             of the second image) equals zero, the function execution is continued.
//                               If a dividend is equal to zero, then the result is zero;
//                               if it is greater than zero, then the result is zero,
//                               if it is less than zero, then the result is zero
//
//  Parameters:
//    pSrc                     Pointer to the source image
//    srcStep                  Step through the source image
//    pSrcDst                  Pointer to the source and destination image
//    srcDstStep               Step through the source and destination image
//    roiSize                  Size of the ROI
//    scaleFactor              Scale factor
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiAdd_16sc_C1IRSfs,  (const Ipp16sc* pSrc, int srcStep, Ipp16sc* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiAdd_16sc_C3IRSfs,  (const Ipp16sc* pSrc, int srcStep, Ipp16sc* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiAdd_16sc_AC4IRSfs, (const Ipp16sc* pSrc, int srcStep, Ipp16sc* pSrcDst,
                                          int srcDstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiSub_16sc_C1IRSfs,  (const Ipp16sc* pSrc, int srcStep, Ipp16sc* pSrcDst,
                                          int srcDstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiSub_16sc_C3IRSfs,  (const Ipp16sc* pSrc, int srcStep, Ipp16sc* pSrcDst,
                                          int srcDstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiSub_16sc_AC4IRSfs, (const Ipp16sc* pSrc, int srcStep, Ipp16sc* pSrcDst,
                                          int srcDstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMul_16sc_C1IRSfs,  (const Ipp16sc* pSrc, int srcStep, Ipp16sc* pSrcDst,
                                          int srcDstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMul_16sc_C3IRSfs,  (const Ipp16sc* pSrc, int srcStep, Ipp16sc* pSrcDst,
                                          int srcDstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMul_16sc_AC4IRSfs, (const Ipp16sc* pSrc, int srcStep, Ipp16sc* pSrcDst,
                                          int srcDstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiDiv_16sc_C1IRSfs,  (const Ipp16sc* pSrc, int srcStep, Ipp16sc* pSrcDst,
                                          int srcDstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiDiv_16sc_C3IRSfs,  (const Ipp16sc* pSrc, int srcStep, Ipp16sc* pSrcDst,
                                          int srcDstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiDiv_16sc_AC4IRSfs, (const Ipp16sc* pSrc, int srcStep, Ipp16sc* pSrcDst,
                                          int srcDstStep, IppiSize roiSize, int scaleFactor))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiAdd_16sc_C1RSfs, ippiAdd_16sc_C3RSfs, ippiAdd_16sc_AC4RSfs,
//              ippiSub_16sc_C1RSfs, ippiSub_16sc_C3RSfs, ippiSub_16sc_AC4RSfs,
//              ippiMul_16sc_C1RSfs, ippiMul_16sc_C3RSfs, ippiMul_16sc_AC4RSfs,
//              ippiDiv_16sc_C1RSfs, ippiDiv_16sc_C3RSfs, ippiDiv_16sc_AC4RSfs
//
//  Purpose:    Adds, subtracts, multiplies, or divides pixel values of two
//              source images and places the results in the destination image.
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         One of the pointers is NULL
//    ippStsSizeErr            The roiSize has a field with negative or zero value
//    ippStsStepErr            One of the step values is less than or equal to zero
//    ippStsDivByZero          For division only - a warning that a divisor value (pixel value
//                             of the second image) equals zero, the function execution is continued.
//                               If a dividend is equal to zero, then the result is zero;
//                               if it is greater than zero, then the result is zero,
//                               if it is less than zero, then the result is zero
//  Parameters:
//    pSrc1, pSrc2             Pointers to source images
//    src1Step, src2Step       Steps through the source images
//    pDst                     Pointer to the destination image
//    dstStep                  Step through the destination image
//    roiSize                  Size of the ROI
//    scaleFactor              Scale factor
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiAdd_16sc_C1RSfs,  (const Ipp16sc* pSrc1, int src1Step, const Ipp16sc* pSrc2,
                                        int src2Step, Ipp16sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiAdd_16sc_C3RSfs,  (const Ipp16sc* pSrc1, int src1Step, const Ipp16sc* pSrc2,
                                        int src2Step, Ipp16sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiAdd_16sc_AC4RSfs, (const Ipp16sc* pSrc1, int src1Step, const Ipp16sc* pSrc2,
                                        int src2Step, Ipp16sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiSub_16sc_C1RSfs,  (const Ipp16sc* pSrc1, int src1Step, const Ipp16sc* pSrc2,
                                        int src2Step, Ipp16sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiSub_16sc_C3RSfs,  (const Ipp16sc* pSrc1, int src1Step, const Ipp16sc* pSrc2,
                                        int src2Step, Ipp16sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiSub_16sc_AC4RSfs, (const Ipp16sc* pSrc1, int src1Step, const Ipp16sc* pSrc2,
                                        int src2Step, Ipp16sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMul_16sc_C1RSfs,  (const Ipp16sc* pSrc1, int src1Step, const Ipp16sc* pSrc2,
                                        int src2Step, Ipp16sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMul_16sc_C3RSfs,  (const Ipp16sc* pSrc1, int src1Step, const Ipp16sc* pSrc2,
                                        int src2Step, Ipp16sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMul_16sc_AC4RSfs, (const Ipp16sc* pSrc1, int src1Step, const Ipp16sc* pSrc2,
                                        int src2Step, Ipp16sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiDiv_16sc_C1RSfs,  (const Ipp16sc* pSrc1, int src1Step, const Ipp16sc* pSrc2,
                                        int src2Step, Ipp16sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiDiv_16sc_C3RSfs,  (const Ipp16sc* pSrc1, int src1Step, const Ipp16sc* pSrc2,
                                        int src2Step, Ipp16sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiDiv_16sc_AC4RSfs, (const Ipp16sc* pSrc1, int src1Step, const Ipp16sc* pSrc2,
                                        int src2Step, Ipp16sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))


/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiAdd_32sc_C1IRSfs, ippiAdd_32sc_C3IRSfs, ippiAdd_32sc_AC4IRSfs,
//              ippiSub_32sc_C1IRSfs, ippiSub_32sc_C3IRSfs, ippiSub_32sc_AC4IRSfs,
//              ippiMul_32sc_C1IRSfs, ippiMul_32sc_C3IRSfs, ippiMul_32sc_AC4IRSfs,
//              ippiDiv_32sc_C1IRSfs, ippiDiv_32sc_C3IRSfs, ippiDiv_32sc_AC4IRSfs
//
//  Purpose:    Adds, subtracts, multiplies, or divides pixel values of two
//              source images and places the results in the first source image.
//
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         One of the pointers is NULL
//    ippStsSizeErr            The roiSize has a field with negative or zero value
//    ippStsStepErr            One of the step values is less than or equal to zero
//    ippStsDivByZero          For division only - a warning that a divisor value (pixel value
//                             of the second image) equals zero, the function execution is continued.
//                               If a dividend is equal to zero, then the result is zero;
//                               if it is greater than zero, then the result is IPP_MAX_32S,
//                               if it is less than zero, then the result is IPP_MIN_32S
//  Parameters:
//    pSrc                     Pointer to the second source image
//    srcStep                  Step through the second source image
//    pSrcDst                  Pointer to the first source/destination image
//    srcDstStep               Step through the first source/destination image
//    roiSize                  Size of the ROI
//    scaleFactor              Scale factor
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiAdd_32sc_C1IRSfs,  (const Ipp32sc* pSrc, int srcStep, Ipp32sc* pSrcDst,
                                          int srcDstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiAdd_32sc_C3IRSfs,  (const Ipp32sc* pSrc, int srcStep, Ipp32sc* pSrcDst,
                                          int srcDstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiAdd_32sc_AC4IRSfs, (const Ipp32sc* pSrc, int srcStep, Ipp32sc* pSrcDst,
                                          int srcDstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiSub_32sc_C1IRSfs,  (const Ipp32sc* pSrc, int srcStep, Ipp32sc* pSrcDst,
                                          int srcDstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiSub_32sc_C3IRSfs,  (const Ipp32sc* pSrc, int srcStep, Ipp32sc* pSrcDst,
                                          int srcDstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiSub_32sc_AC4IRSfs, (const Ipp32sc* pSrc, int srcStep, Ipp32sc* pSrcDst,
                                          int srcDstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMul_32sc_C1IRSfs,  (const Ipp32sc* pSrc, int srcStep, Ipp32sc* pSrcDst,
                                          int srcDstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMul_32sc_C3IRSfs,  (const Ipp32sc* pSrc, int srcStep, Ipp32sc* pSrcDst,
                                          int srcDstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMul_32sc_AC4IRSfs, (const Ipp32sc* pSrc, int srcStep, Ipp32sc* pSrcDst,
                                          int srcDstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiDiv_32sc_C1IRSfs,  (const Ipp32sc* pSrc, int srcStep, Ipp32sc* pSrcDst,
                                          int srcDstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiDiv_32sc_C3IRSfs,  (const Ipp32sc* pSrc, int srcStep, Ipp32sc* pSrcDst,
                                          int srcDstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiDiv_32sc_AC4IRSfs, (const Ipp32sc* pSrc, int srcStep, Ipp32sc* pSrcDst,
                                          int srcDstStep, IppiSize roiSize, int scaleFactor))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiAdd_32sc_C1RSfs, ippiAdd_32sc_C3RSfs, ippiAdd_32sc_AC4RSfs,
//              ippiSub_32sc_C1RSfs, ippiSub_32sc_C3RSfs, ippiSub_32sc_AC4RSfs,
//              ippiMul_32sc_C1RSfs, ippiMul_32sc_C3RSfs, ippiMul_32sc_AC4RSfs,
//              ippiDiv_32sc_C1RSfs, ippiDiv_32sc_C3RSfs, ippiDiv_32sc_AC4RSfs
//
//  Purpose:    Adds, subtracts, multiplies, or divides pixel values of two
//              source images and places the results in the destination image.
//
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         One of the pointers is NULL
//    ippStsSizeErr            The roiSize has a field with negative or zero value
//    ippStsStepErr            One of the step values is less than or equal to zero
//    ippStsDivByZero          For division only - a warning that a divisor value (pixel value
//                             of the second image) equals zero, the function execution is continued.
//                               If a dividend is equal to zero, then the result is zero;
//                               if it is greater than zero, then the result is IPP_MAX_32S,
//                               if it is less than zero, then the result is IPP_MIN_32S
//  Parameters:
//    pSrc1, pSrc2             Pointers to source images
//    src1Step, src2Step       The steps of the source images
//    pDst                     The pointer to the destination image
//    dstStep                  The step of the destination image
//    roiSize                  Size of the ROI
//    scaleFactor              Scale factor
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiAdd_32sc_C1RSfs,  (const Ipp32sc* pSrc1, int src1Step, const Ipp32sc* pSrc2,
                                         int src2Step, Ipp32sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiAdd_32sc_C3RSfs,  (const Ipp32sc* pSrc1, int src1Step, const Ipp32sc* pSrc2,
                                         int src2Step, Ipp32sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiAdd_32sc_AC4RSfs, (const Ipp32sc* pSrc1, int src1Step, const Ipp32sc* pSrc2,
                                         int src2Step, Ipp32sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiSub_32sc_C1RSfs,  (const Ipp32sc* pSrc1, int src1Step, const Ipp32sc* pSrc2,
                                         int src2Step, Ipp32sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiSub_32sc_C3RSfs,  (const Ipp32sc* pSrc1, int src1Step, const Ipp32sc* pSrc2,
                                         int src2Step, Ipp32sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiSub_32sc_AC4RSfs, (const Ipp32sc* pSrc1, int src1Step, const Ipp32sc* pSrc2,
                                         int src2Step, Ipp32sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMul_32sc_C1RSfs,  (const Ipp32sc* pSrc1, int src1Step, const Ipp32sc* pSrc2,
                                         int src2Step, Ipp32sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMul_32sc_C3RSfs,  (const Ipp32sc* pSrc1, int src1Step, const Ipp32sc* pSrc2,
                                         int src2Step, Ipp32sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMul_32sc_AC4RSfs, (const Ipp32sc* pSrc1, int src1Step, const Ipp32sc* pSrc2,
                                         int src2Step, Ipp32sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiDiv_32sc_C1RSfs,  (const Ipp32sc* pSrc1, int src1Step, const Ipp32sc* pSrc2,
                                         int src2Step, Ipp32sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiDiv_32sc_C3RSfs,  (const Ipp32sc* pSrc1, int src1Step, const Ipp32sc* pSrc2,

                                        int src2Step, Ipp32sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiDiv_32sc_AC4RSfs, (const Ipp32sc* pSrc1, int src1Step, const Ipp32sc* pSrc2,
                                        int src2Step, Ipp32sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiAddC_16sc_C1IRSfs, ippiAddC_16sc_C3IRSfs, ippiAddC_16sc_AC4IRSfs,
//              ippiSubC_16sc_C1IRSfs, ippiSubC_16sc_C3IRSfs, ippiSubC_16sc_AC4IRSfs,
//              ippiMulC_16sc_C1IRSfs, ippiMulC_16sc_C3IRSfs, ippiMulC_16sc_AC4IRSfs,
//              ippiDivC_16sc_C1IRSfs, ippiDivC_16sc_C3IRSfs, ippiDivC_16sc_AC4IRSfs
//
//  Purpose:    Adds, subtracts, multiplies, or divides pixel values of an image
//              and a constant and places the results in the same image.
//
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         The pointer is NULL
//    ippStsSizeErr            The roiSize has a field with negative or zero value
//    ippStsStepErr            The step value is less than or equal to zero
//    ippStsDivByZeroErr       The constant is equal to zero (for division)
//
//  Parameters:
//    value                  The constant value (constant vector for multi-channel images)
//    pSrcDst                Pointer to the image
//    srcDstStep             Step through the image
//    roiSize                Size of the ROI
//    scaleFactor            Scale factor
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiAddC_16sc_C1IRSfs,  (Ipp16sc value, Ipp16sc* pSrcDst, int srcDstStep,
                                           IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddC_16sc_C3IRSfs,  (const Ipp16sc value[3], Ipp16sc* pSrcDst, int srcDstStep,
                                           IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddC_16sc_AC4IRSfs, (const Ipp16sc value[3], Ipp16sc* pSrcDst, int srcDstStep,
                                           IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiSubC_16sc_C1IRSfs,  (Ipp16sc value, Ipp16sc* pSrcDst, int srcDstStep,
                                           IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiSubC_16sc_C3IRSfs,  (const Ipp16sc value[3], Ipp16sc* pSrcDst, int srcDstStep,
                                           IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiSubC_16sc_AC4IRSfs, (const Ipp16sc value[3], Ipp16sc* pSrcDst, int srcDstStep,
                                           IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulC_16sc_C1IRSfs,  (Ipp16sc value, Ipp16sc* pSrcDst, int srcDstStep,
                                           IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulC_16sc_C3IRSfs,  (const Ipp16sc value[3], Ipp16sc* pSrcDst, int srcDstStep,
                                           IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulC_16sc_AC4IRSfs, (const Ipp16sc value[3], Ipp16sc* pSrcDst, int srcDstStep,
                                           IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiDivC_16sc_C1IRSfs,  (Ipp16sc value, Ipp16sc* pSrcDst, int srcDstStep,
                                           IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiDivC_16sc_C3IRSfs,  (const Ipp16sc value[3], Ipp16sc* pSrcDst, int srcDstStep,
                                           IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiDivC_16sc_AC4IRSfs, (const Ipp16sc value[3], Ipp16sc* pSrcDst, int srcDstStep,
                                           IppiSize roiSize, int scaleFactor))

/* //////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiAddC_16sc_C1RSfs, ippiAddC_16sc_C3RSfs, ippiAddC_16sc_AC4RSfs,
//              ippiSubC_16sc_C1RSfs, ippiSubC_16sc_C3RSfs, ippiSubC_16sc_AC4RSfs,
//              ippiMulC_16sc_C1RSfs, ippiMulC_16sc_C3RSfs, ippiMulC_16sc_AC4RSfs
//              ippiDivC_16sc_C1RSfs, ippiDivC_16sc_C3RSfs, ippiDivC_16sc_AC4RSfs
//
//
//  Purpose:    Adds, subtracts, multiplies, or divides pixel values of an image
//              and a constant and places the results in the destination image.
//
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         One of the pointers is NULL
//    ippStsSizeErr            The roiSize has a field with negative or zero value
//    ippStsStepErr            One of the step values is less than or equal to zero
//    ippStsDivByZeroErr       The constant is equal to zero (for division)
//
//  Parameters:
//    value                    The constant value (constant vector for multi-channel images)
//    pSrc                     Pointer to the source image
//    srcStep                  Step through the source image
//    pDst                     Pointer to the destination image
//    dstStep                  Step through the destination image
//    roiSize                  Size of the ROI
//    scaleFactor              Scale factor
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiAddC_16sc_C1RSfs,  (const Ipp16sc* pSrc, int srcStep, Ipp16sc value, Ipp16sc* pDst,
                                          int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddC_16sc_C3RSfs,  (const Ipp16sc* pSrc, int srcStep, const Ipp16sc value[3],
                                          Ipp16sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddC_16sc_AC4RSfs, (const Ipp16sc* pSrc, int srcStep, const Ipp16sc value[3],
                                          Ipp16sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiSubC_16sc_C1RSfs,  (const Ipp16sc* pSrc, int srcStep, Ipp16sc value, Ipp16sc* pDst,
                                          int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiSubC_16sc_C3RSfs,  (const Ipp16sc* pSrc, int srcStep, const Ipp16sc value[3],
                                          Ipp16sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiSubC_16sc_AC4RSfs, (const Ipp16sc* pSrc, int srcStep, const Ipp16sc value[3],
                                          Ipp16sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulC_16sc_C1RSfs,  (const Ipp16sc* pSrc, int srcStep, Ipp16sc value, Ipp16sc* pDst,
                                          int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulC_16sc_C3RSfs,  (const Ipp16sc* pSrc, int srcStep, const Ipp16sc value[3],
                                          Ipp16sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulC_16sc_AC4RSfs, (const Ipp16sc* pSrc, int srcStep, const Ipp16sc value[3],
                                          Ipp16sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiDivC_16sc_C1RSfs,  (const Ipp16sc* pSrc,
                                          int srcStep, Ipp16sc value, Ipp16sc* pDst,
                                          int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiDivC_16sc_C3RSfs,  (const Ipp16sc* pSrc,
                                          int srcStep, const Ipp16sc value[3], Ipp16sc* pDst,
                                          int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiDivC_16sc_AC4RSfs, (const Ipp16sc* pSrc,
                                          int srcStep, const Ipp16sc value[3], Ipp16sc* pDst,
                                          int dstStep, IppiSize roiSize, int scaleFactor))


/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiAddC_32sc_C1IRSfs, ippiAddC_32sc_C3IRSfs, ippiAddC_32sc_AC4IRSfs,
//              ippiSubC_32sc_C1IRSfs, ippiSubC_32sc_C3IRSfs, ippiSubC_32sc_AC4IRSfs,
//              ippiMulC_32sc_C1IRSfs, ippiMulC_32sc_C3IRSfs, ippiMulC_32sc_AC4IRSfs,
//              ippiDivC_32sc_C1IRSfs, ippiDivC_32sc_C3IRSfs, ippiDivC_32sc_AC4IRSfs
//
//  Purpose:    Adds, subtracts, multiplies, or divides pixel values of an image
//              and a constant and places the results in the same image.
//
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         The pointer is NULL
//    ippStsSizeErr            The roiSize has a field with negative or zero value
//    ippStsStepErr            The step value is less than or equal to zero
//    ippStsDivByZeroErr       The constant is equal to zero (for division)
//
//  Parameters:
//    value                    The constant value (constant vector for multi-channel images)
//    pSrcDst                  Pointer to the image
//    srcDstStep               Step through the image
//    roiSize                  Size of the ROI
//    scaleFactor              Scale factor
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiAddC_32sc_C1IRSfs,  (Ipp32sc value, Ipp32sc* pSrcDst, int srcDstStep,
                                           IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddC_32sc_C3IRSfs,  (const Ipp32sc value[3], Ipp32sc* pSrcDst, int srcDstStep,
                                           IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddC_32sc_AC4IRSfs, (const Ipp32sc value[3], Ipp32sc* pSrcDst, int srcDstStep,
                                           IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiSubC_32sc_C1IRSfs,  (Ipp32sc value, Ipp32sc* pSrcDst, int srcDstStep,
                                           IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiSubC_32sc_C3IRSfs,  (const Ipp32sc value[3], Ipp32sc* pSrcDst, int srcDstStep,
                                           IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiSubC_32sc_AC4IRSfs, (const Ipp32sc value[3], Ipp32sc* pSrcDst, int srcDstStep,
                                           IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulC_32sc_C1IRSfs,  (Ipp32sc value, Ipp32sc* pSrcDst, int srcDstStep,
                                           IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulC_32sc_C3IRSfs,  (const Ipp32sc value[3], Ipp32sc* pSrcDst, int srcDstStep,
                                           IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulC_32sc_AC4IRSfs, (const Ipp32sc value[3], Ipp32sc* pSrcDst, int srcDstStep,
                                           IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiDivC_32sc_C1IRSfs,  (Ipp32sc value, Ipp32sc* pSrcDst, int srcDstStep,
                                           IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiDivC_32sc_C3IRSfs,  (const Ipp32sc value[3], Ipp32sc* pSrcDst, int srcDstStep,
                                           IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiDivC_32sc_AC4IRSfs, (const Ipp32sc value[3], Ipp32sc* pSrcDst, int srcDstStep,
                                           IppiSize roiSize, int scaleFactor))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiAddC_32sc_C1RSfs, ippiAddC_32sc_C3RSfs, ippiAddC_32sc_AC4RSfs,
//              ippiSubC_32sc_C1RSfs, ippiSubC_32sc_C3RSfs, ippiSubC_32sc_AC4RSfs,
//              ippiMulC_32sc_C1RSfs, ippiMulC_32sc_C3RSfs, ippiMulC_32sc_AC4RSfs,
//              ippiDivC_32sc_C1RSfs, ippiDivC_32sc_C3RSfs, ippiDivC_32sc_AC4RSfs
//
//  Purpose:    Adds, subtracts, multiplies, or divides pixel values of an image
//              and a constant and places the results in the destination image.
//
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         One of the pointers is NULL
//    ippStsSizeErr            The roiSize has a field with negative or zero value
//    ippStsStepErr            Any of the step values is less than or equal to zero
//    ippStsDivByZeroErr       The constant is equal to zero (for division)
//
//
//  Parameters:
//    value                    The constant value (constant vector for multi-channel images)
//    pSrc                     Pointer to the source image
//    srcStep                  Step through the source image
//    pDst                     Pointer to the destination image
//    dstStep                  Step through the destination image
//    roiSize                  ROI
//    scaleFactor              Scale factor
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiAddC_32sc_C1RSfs,  (const Ipp32sc* pSrc, int srcStep, Ipp32sc value, Ipp32sc* pDst,
                                          int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddC_32sc_C3RSfs,  (const Ipp32sc* pSrc, int srcStep, const Ipp32sc value[3],
                                          Ipp32sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddC_32sc_AC4RSfs, (const Ipp32sc* pSrc, int srcStep, const Ipp32sc value[3],
                                          Ipp32sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiSubC_32sc_C1RSfs,  (const Ipp32sc* pSrc, int srcStep, Ipp32sc value, Ipp32sc* pDst,
                                          int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiSubC_32sc_C3RSfs,  (const Ipp32sc* pSrc, int srcStep, const Ipp32sc value[3],
                                          Ipp32sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiSubC_32sc_AC4RSfs, (const Ipp32sc* pSrc, int srcStep, const Ipp32sc value[3],
                                          Ipp32sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulC_32sc_C1RSfs,  (const Ipp32sc* pSrc, int srcStep, Ipp32sc value, Ipp32sc* pDst,
                                          int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulC_32sc_C3RSfs,  (const Ipp32sc* pSrc, int srcStep, const Ipp32sc value[3],
                                          Ipp32sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulC_32sc_AC4RSfs, (const Ipp32sc* pSrc, int srcStep, const Ipp32sc value[3],
                                          Ipp32sc* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiDivC_32sc_C1RSfs,  (const Ipp32sc* pSrc,
                                          int srcStep, Ipp32sc value, Ipp32sc* pDst,
                                          int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiDivC_32sc_C3RSfs,  (const Ipp32sc* pSrc,
                                          int srcStep, const Ipp32sc value[3], Ipp32sc* pDst,
                                          int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiDivC_32sc_AC4RSfs, (const Ipp32sc* pSrc,
                                          int srcStep, const Ipp32sc value[3], Ipp32sc* pDst,
                                          int dstStep, IppiSize roiSize, int scaleFactor))

/* /////////////////////////////////////////////////////////////////////////////
//              Dot product of two images
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiDotProd
//  Purpose:        Computes the dot product of two images
//  Context:
//  Returns:        IppStatus
//    ippStsNoErr        OK
//    ippStsNullPtrErr   One of the pointers is NULL
//    ippStsStepErr      One of the step values is equal to zero
//  Parameters:
//    pSrc1       Pointer to the first source image.
//    src1Step    Step in bytes through the first source image
//    pSrc2       Pointer to the second source image.
//    src2Step    Step in bytes through the  source image
//    roiSize     Size of the source image ROI.
//    pDp         Pointer to the result (one-channel data) or array (multi-channel data) containing computed dot products of channel values of pixels in the source images.
//    hint        Option to select the algorithmic implementation of the function
//  Notes:
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiDotProd_8s64f_C1R,(const Ipp8s* pSrc1, int src1Step, const Ipp8s* pSrc2, int src2Step, IppiSize roiSize, Ipp64f *pDp))

LEGACY90IPPAPI(IppStatus, legacy90ippiDotProd_8s64f_C3R,(const Ipp8s* pSrc1, int src1Step, const Ipp8s* pSrc2, int src2Step, IppiSize roiSize, Ipp64f pDp[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiDotProd_8s64f_C4R,(const Ipp8s* pSrc1, int src1Step, const Ipp8s* pSrc2, int src2Step, IppiSize roiSize, Ipp64f pDp[4]))

LEGACY90IPPAPI(IppStatus, legacy90ippiDotProd_8s64f_AC4R,(const Ipp8s* pSrc1, int src1Step, const Ipp8s* pSrc2, int src2Step, IppiSize roiSize, Ipp64f pDp[3]))


/* /////////////////////////////////////////////////////////////////////////////
//              Vector Multiplication of Images in RCPack2D Format
///////////////////////////////////////////////////////////////////////////// */
/*  Name:               ippiMulPack, ippiMulPackConj
//
//  Purpose:            Multiplies pixel values of two images in RCPack2D format
//                      and store the result also in PCPack2D format
//
//  Returns:
//      ippStsNoErr       No errors
//      ippStsNullPtrErr  One of the pointers is NULL
//      ippStsStepErr     One of the step values is zero or negative
//      ippStsSizeErr     The roiSize has a field with negative or zero value
//
//  Parameters:
//      pSrc            Pointer to the source image for in-place operation
//      pSrcDst         Pointer to the source/destination image for in-place operation
//      srcStep         Step through the source image for in-place operation
//      srcDstStep      Step through the source/destination image for in-place operation
//      pSrc1           Pointer to the first source image
//      src1Step        Step through the first source image
//      pSrc2           Pointer to the second source image
//      src1Step        Step through the second source image
//      pDst            Pointer to the destination image
//      dstStep         Step through the destination image
//      roiSize         Size of the source and destination ROI
//      scaleFactor     Scale factor
//
//  Notes:              Both in-place and not-in-place operations are supported
//                      ippiMulPackConj functions are only for float data
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiMulPack_16s_C1IRSfs, (const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst, int srcDstStep,
                                        IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulPack_16s_C3IRSfs, (const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst, int srcDstStep,
                                        IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulPack_16s_C4IRSfs, (const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst, int srcDstStep,
                                        IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulPack_16s_AC4IRSfs, (const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst, int srcDstStep,
                                        IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulPack_16s_C1RSfs, (const Ipp16s* pSrc1, int src1Step, const Ipp16s* pSrc2, int src2Step,
                                        Ipp16s* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulPack_16s_C3RSfs, (const Ipp16s* pSrc1, int src1Step, const Ipp16s* pSrc2, int src2Step,
                                        Ipp16s* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulPack_16s_C4RSfs, (const Ipp16s* pSrc1, int src1Step, const Ipp16s* pSrc2, int src2Step,
                                        Ipp16s* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulPack_16s_AC4RSfs, (const Ipp16s* pSrc1, int src1Step, const Ipp16s* pSrc2, int src2Step,
                                        Ipp16s* pDst, int dstStep, IppiSize roiSize, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippiMulPack_32s_C1IRSfs, (const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst, int srcDstStep,
                                        IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulPack_32s_C3IRSfs, (const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst, int srcDstStep,
                                        IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulPack_32s_C4IRSfs, (const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst, int srcDstStep,
                                        IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulPack_32s_AC4IRSfs, (const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst, int srcDstStep,
                                        IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulPack_32s_C1RSfs, (const Ipp32s* pSrc1, int src1Step, const Ipp32s* pSrc2, int src2Step,
                                        Ipp32s* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulPack_32s_C3RSfs, (const Ipp32s* pSrc1, int src1Step, const Ipp32s* pSrc2, int src2Step,
                                        Ipp32s* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulPack_32s_C4RSfs, (const Ipp32s* pSrc1, int src1Step, const Ipp32s* pSrc2, int src2Step,
                                        Ipp32s* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiMulPack_32s_AC4RSfs, (const Ipp32s* pSrc1, int src1Step, const Ipp32s* pSrc2, int src2Step,
                                        Ipp32s* pDst, int dstStep, IppiSize roiSize, int scaleFactor))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiPackToCplxExtend
//
//  Purpose:        Converts an image in RCPack2D format to a complex data image.
//
//  Returns:
//      ippStsNoErr            No errors
//      ippStsNullPtrErr       pSrc == NULL, or pDst == NULL
//      ippStsStepErr          One of the step values is less zero or negative
//      ippStsSizeErr          The srcSize has a field with zero or negative value
//
//  Parameters:
//    pSrc        Pointer to the source image data (point to pixel (0,0))
//    srcSize     Size of the source image
//    srcStep     Step through  the source image
//    pDst        Pointer to the destination image
//    dstStep     Step through the destination image
//  Notes:
*/

LEGACY90IPPAPI (IppStatus, legacy90ippiPackToCplxExtend_32s32sc_C1R, (const Ipp32s* pSrc,
        IppiSize srcSize, int srcStep,
        Ipp32sc* pDst, int dstStep ))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiCplxExtendToPack
//
//  Purpose:        Converts an image in complex data format to RCPack2D image.
//
//  Returns:
//      ippStsNoErr            No errors
//      ippStsNullPtrErr       pSrc == NULL, or pDst == NULL
//      ippStsStepErr          One of the step values is less zero or negative
//      ippStsSizeErr          The srcSize has a field with zero or negative value
//
//  Parameters:
//    pSrc        Pointer to the source image data (point to pixel (0,0))
//    srcSize     Size of the source image
//    srcStep     Step through  the source image
//    pDst        Pointer to the destination image
//    dstStep     Step through the destination image
//  Notes:
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiCplxExtendToPack_32sc32s_C1R,(const Ipp32sc* pSrc, int srcStep, IppiSize srcSize,
                                                                           Ipp32s* pDst, int dstStep ))

LEGACY90IPPAPI(IppStatus, legacy90ippiCplxExtendToPack_16sc16s_C1R,(const Ipp16sc* pSrc, int srcStep, IppiSize srcSize,
                                                                           Ipp16s* pDst, int dstStep ))


LEGACY90IPPAPI(IppStatus, legacy90ippiCplxExtendToPack_32sc32s_C3R,(const Ipp32sc* pSrc, int srcStep, IppiSize srcSize,
                                                                           Ipp32s* pDst, int dstStep ))

LEGACY90IPPAPI(IppStatus, legacy90ippiCplxExtendToPack_16sc16s_C3R,(const Ipp16sc* pSrc, int srcStep, IppiSize srcSize,
                                                                           Ipp16s* pDst, int dstStep ))


/* /////////////////////////////////////////////////////////////////////////////
//  Names:  ippiPhasePack_32f_C1R
//          ippiPhasePack_32f_C3R
//          ippiPhasePack_16s_C1RSfs
//          ippiPhasePack_16s_C3RSfs
//  Purpose:
//    Computes  the phase (in radians) of elements of an image in RCPack2D packed format.
//  Parameters:
//    pSrc         Pointer to the source complex image in Pack2D format
//    srcStep      Step through the source image
//    pDst         Pointer to the destination image
//    dstStep      Step through the destination image
//    dstRoiSize   Size of the ROI of destination image
//    scaleFactor  Scale factor (only for integer data)
//  Returns:
//    ippStsNullPtrErr    pSrc or pDst is NULL
//    ippStsSizeErr       The width or height of images is less than or equal to zero
//    ippStsStepErr       srcStep or dstStep is less than or equal to zero
//    ippStsNoErr         Otherwise
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiPhasePack_32s_C1RSfs,(const Ipp32s* pSrc, int srcStep,
                                                  Ipp32s* pDst, int dstStep,
                                           IppiSize dstRoiSize, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippiPhasePack_32s_C3RSfs,(const Ipp32s* pSrc, int srcStep,
                                                  Ipp32s* pDst, int dstStep,
                                           IppiSize dstRoiSize, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippiPhasePack_16s_C1RSfs,(const Ipp16s* pSrc, int srcStep,
                                                  Ipp16s* pDst, int dstStep,
                                           IppiSize dstRoiSize, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippiPhasePack_16s_C3RSfs,(const Ipp16s* pSrc, int srcStep,

                                                  Ipp16s* pDst, int dstStep,
                                           IppiSize dstRoiSize, int scaleFactor))


/* /////////////////////////////////////////////////////////////////////////////
//  Names:  ippiMagnitudePack_32f_C1R
//          ippiMagnitudePack_32f_C3R
//          ippiMagnitudePack_32s_C1RSfs
//          ippiMagnitudePack_32s_C3RSfs
//          ippiMagnitudePack_16s_C1RSfs
//          ippiMagnitudePack_16s_C3RSfs
//  Purpose:
//    Computes magnitude of elements of an image in RCPack2D packed format.
//  Parameters:
//    pSrc        Pointer to the source image in Pack2D format
//    srcStep     Step through the source image
//    pDst        Pointer to the destination image to store the magnitude components
//    dstStep     Step through the destination image
//    dstRoiSize  Size of the destination ROI
//    scaleFactor Scale factor (only for integer data)
//  Returns:
//    ippStsNullPtrErr    pSrc or pDst is NULL
//    ippStsSizeErr       The width or height of images is less than or equal to zero
//    ippStsStepErr       srcStep or dstStep is less than or equal to zero
//    ippStsNoErr         Otherwise
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiMagnitudePack_16s_C1RSfs,(const Ipp16s* pSrc, int srcStep,
                                                      Ipp16s* pDst, int dstStep,
                                               IppiSize dstRoiSize, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippiMagnitudePack_16s_C3RSfs,(const Ipp16s* pSrc, int srcStep,
                                                      Ipp16s* pDst, int dstStep,
                                               IppiSize dstRoiSize, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippiMagnitudePack_32s_C1RSfs,(const Ipp32s* pSrc, int srcStep,
                                                   Ipp32s* pDst, int dstStep,
                                               IppiSize dstRoiSize, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippiMagnitudePack_32s_C3RSfs,(const Ipp32s* pSrc, int srcStep,
                                                   Ipp32s* pDst, int dstStep,
                                               IppiSize dstRoiSize, int scaleFactor))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:  ippiMagnitude_32fc32f_C1R
//          ippiMagnitude_32fc32f_C3R
//          ippiMagnitude_32sc32s_C1RSfs
//          ippiMagnitude_32sc32s_C3RSfs
//          ippiMagnitude_16sc16s_C1RSfs
//          ippiMagnitude_16sc16s_C3RSfs
//          ippiMagnitude_16uc16u_C1RSfs
//          ippiMagnitude_16uc16u_C3RSfs
//  Purpose:
//    Computes magnitude of elements of a complex data image.
//  Parameters:
//    pSrc        Pointer to the source image in common complex data format
//    srcStep     Step through the source image
//    pDst        Pointer to the destination image to store magnitude components
//    dstStep     Step through the destination image
//    roiSize     Size of the ROI
//    scaleFactor Scale factor (only for integer data)
//  Returns:
//    ippStsNullPtrErr    pSrc or pDst is NULL
//    ippStsSizeErr       The width or height of images is less than or equal to zero
//    ippStsStepErr       srcStep or dstStep is less than or equal to zero
//    ippStsNoErr         Otherwise
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiMagnitude_16sc16s_C1RSfs,(const Ipp16sc* pSrc, int srcStep,
                                                      Ipp16s*  pDst, int dstStep,
                                                   IppiSize roiSize, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippiMagnitude_16sc16s_C3RSfs,(const Ipp16sc* pSrc, int srcStep,
                                                      Ipp16s* pDst,  int dstStep,
                                                   IppiSize roiSize, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippiMagnitude_32sc32s_C1RSfs,(const Ipp32sc* pSrc, int srcStep,
                                                    Ipp32s* pDst, int dstStep,
                                                   IppiSize roiSize, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippiMagnitude_32sc32s_C3RSfs,(const Ipp32sc* pSrc, int srcStep,
                                                    Ipp32s* pDst, int dstStep,
                                                   IppiSize roiSize, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippiMagnitude_16uc16u_C1RSfs,(const Ipp16uc* pSrc, int srcStep,
                                                      Ipp16u*  pDst, int dstStep,
                                                      IppiSize roiSize, int ScalFact))

LEGACY90IPPAPI(IppStatus, legacy90ippiMagnitude_16uc16u_C3RSfs,(const Ipp16uc* pSrc, int srcStep,
                                                      Ipp16u*  pDst, int dstStep,
                                                      IppiSize roiSize, int ScalFact))


/* /////////////////////////////////////////////////////////////////////////////
//  Names:   ippiPhase_32fc32f_C1R
//           ippiPhase_32fc32f_C3R
//           ippiPhase_16sc16s_C1RSfs
//           ippiPhase_16sc16s_C3RSfs
//           ippiPhase_16uc16u_C1RSfs
//           ippiPhase_16uc16u_C3RSfs
//  Purpose:
//    Computes the phase (in radians) of elements of a complex data image
//  Parameters:
//    pSrc         Pointer to the source image in common complex data format
//    srcStep      Step through the source image
//    pDst         Pointer to the destination image to store the phase components
//    dstStep      Step through the destination image
//    roiSize      Size of the ROI
//    scaleFactor  Scale factor (only for integer data)
//  Returns:
//    ippStsNullPtrErr    pSrc or pDst is NULL
//    ippStsSizeErr       The width or height of images is less than or equal to zero
//    ippStsStepErr       srcStep or dstStep is less than or equal to zero
//    ippStsNoErr         Otherwise
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiPhase_32sc32s_C1RSfs,(const Ipp32sc* pSrc, int srcStep,
                                                  Ipp32s*  pDst, int dstStep,
                                               IppiSize roiSize, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippiPhase_32sc32s_C3RSfs,(const Ipp32sc* pSrc, int srcStep,
                                                  Ipp32s* pDst,  int dstStep,
                                               IppiSize roiSize, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippiPhase_16sc16s_C1RSfs,(const Ipp16sc* pSrc, int srcStep,
                                                  Ipp16s*  pDst, int dstStep,
                                               IppiSize roiSize, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippiPhase_16sc16s_C3RSfs,(const Ipp16sc* pSrc, int srcStep,
                                                  Ipp16s* pDst,  int dstStep,
                                               IppiSize roiSize, int scaleFactor))

LEGACY90IPPAPI(IppStatus, legacy90ippiPhase_16uc16u_C1RSfs,(const Ipp16uc* pSrc, int srcStep,
                                                  Ipp16u*  pDst, int dstStep,
                                                  IppiSize roiSize, int ScalFact))

LEGACY90IPPAPI(IppStatus, legacy90ippiPhase_16uc16u_C3RSfs,(const Ipp16uc* pSrc, int srcStep,
                                                  Ipp16u*  pDst, int dstStep,
                                                  IppiSize roiSize, int ScalFact))


/* /////////////////////////////////////////////////////////////////////////////
//                  Alpha Compositing Operations
///////////////////////////////////////////////////////////////////////////// */
/*
//  Contents:
//      ippiAlphaPremul_8u_AC4R,  ippiAlphaPremul_16u_AC4R
//      ippiAlphaPremul_8u_AC4IR, ippiAlphaPremul_16u_AC4IR
//      ippiAlphaPremul_8u_AP4R,  ippiAlphaPremul_16u_AP4R
//      ippiAlphaPremul_8u_AP4IR, ippiAlphaPremul_16u_AP4IR
//   Pre-multiplies pixel values of an image by its alpha values.

//      ippiAlphaPremulC_8u_AC4R,  ippiAlphaPremulC_16u_AC4R
//      ippiAlphaPremulC_8u_AC4IR, ippiAlphaPremulC_16u_AC4IR
//      ippiAlphaPremulC_8u_AP4R,  ippiAlphaPremulC_16u_AP4R
//      ippiAlphaPremulC_8u_AP4IR, ippiAlphaPremulC_16u_AP4IR
//      ippiAlphaPremulC_8u_C4R,   ippiAlphaPremulC_16u_C4R
//      ippiAlphaPremulC_8u_C4IR,  ippiAlphaPremulC_16u_C4IR
//      ippiAlphaPremulC_8u_C3R,   ippiAlphaPremulC_16u_C3R
//      ippiAlphaPremulC_8u_C3IR,  ippiAlphaPremulC_16u_C3IR
//      ippiAlphaPremulC_8u_C1R,   ippiAlphaPremulC_16u_C1R
//      ippiAlphaPremulC_8u_C1IR,  ippiAlphaPremulC_16u_C1IR
//   Pre-multiplies pixel values of an image by constant alpha values.
//
//      ippiAlphaComp_8u_AC4R, ippiAlphaComp_16u_AC4R
//      ippiAlphaComp_8u_AC1R, ippiAlphaComp_16u_AC1R
//   Combines two images using alpha values of both images
//
//      ippiAlphaCompC_8u_AC4R, ippiAlphaCompC_16u_AC4R
//      ippiAlphaCompC_8u_AP4R, ippiAlphaCompC_16u_AP4R
//      ippiAlphaCompC_8u_C4R,  ippiAlphaCompC_16u_C4R
//      ippiAlphaCompC_8u_C3R,  ippiAlphaCompC_16u_C3R
//      ippiAlphaCompC_8u_C1R,  ippiAlphaCompC_16u_C1R
//   Combines two images using constant alpha values
//
//  Types of compositing operation (alphaType)
//      OVER   ippAlphaOver   ippAlphaOverPremul
//      IN     ippAlphaIn     ippAlphaInPremul
//      OUT    ippAlphaOut    ippAlphaOutPremul
//      ATOP   ippAlphaATop   ippAlphaATopPremul
//      XOR    ippAlphaXor    ippAlphaXorPremul
//      PLUS   ippAlphaPlus   ippAlphaPlusPremul
//
//  Type  result pixel           result pixel (Premul)    result alpha
//  OVER  aA*A+(1-aA)*aB*B         A+(1-aA)*B             aA+(1-aA)*aB
//  IN    aA*A*aB                  A*aB                   aA*aB
//  OUT   aA*A*(1-aB)              A*(1-aB)               aA*(1-aB)
//  ATOP  aA*A*aB+(1-aA)*aB*B      A*aB+(1-aA)*B          aA*aB+(1-aA)*aB
//  XOR   aA*A*(1-aB)+(1-aA)*aB*B  A*(1-aB)+(1-aA)*B      aA*(1-aB)+(1-aA)*aB
//  PLUS  aA*A+aB*B                A+B                    aA+aB
//      Here 1 corresponds significance VAL_MAX, multiplication is performed
//      with scaling
//          X * Y => (X * Y) / VAL_MAX
//      and VAL_MAX is the maximum presentable pixel value:
//          VAL_MAX == IPP_MAX_8U  for 8u
//          VAL_MAX == IPP_MAX_16U for 16u
*/


/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiAlphaComp_8u_AC4R, ippiAlphaComp_16u_AC4R
//                  ippiAlphaComp_8s_AC4R, ippiAlphaComp_16s_AC4R
//                  ippiAlphaComp_32s_AC4R,ippiAlphaComp_32u_AC4R
//                  ippiAlphaComp_8u_AP4R, ippiAlphaComp_16u_AP4R
//
//  Purpose:        Combines two 4-channel images using alpha values of both images
//
//  Parameters:
//     pSrc1        Pointer to the first source image for pixel-order data,
//                  array of pointers to separate source color planes for planar data
//     src1Step     Step through the first source image
//     pSrc2        Pointer to the second source image for pixel-order data,
//                  array of pointers to separate source color planes for planar data
//     src2Step     Step through the second source image
//     pDst         Pointer to the destination image for pixel-order data,
//                  array of pointers to separate destination color planes for planar data
//     dstStep      Step through the destination image
//     roiSize      Size of the source and destination ROI
//     alphaType    The type of composition to perform
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       pSrc1== NULL, or pSrc2== NULL, or pDst == NULL
//     ippStsSizeErr          The roiSize has a field with negative or zero value
//     ippStsAlphaTypeErr     The alphaType is incorrect
//     Note:                  Result is wrong, if Alpha < 0 for signed types
*/


LEGACY90IPPAPI (IppStatus, legacy90ippiAlphaComp_8s_AC4R,
                   ( const Ipp8s* pSrc1, int src1Step,
                     const Ipp8s* pSrc2, int src2Step,
                     Ipp8s* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiAlphaComp_8u_AC1R, ippiAlphaComp_16u_AC1R
//                  ippiAlphaComp_8s_AC1R, ippiAlphaComp_16s_AC1R
//                  ippiAlphaComp_32s_AC1R, ippiAlphaComp_32u_AC1R
//  Purpose:        Combines two 1-channel images using alpha values of both images
//
//  Parameters:
//     pSrc1        Pointer to the first source image
//     src1Step     Step through the first source image
//     pSrc2        Pointer to the second source image
//     src2Step     Step through the second source image
//     pDst         Pointer to the destination image
//     dstStep      Step through the destination image
//     roiSize      Size of the source and destination ROI
//     alphaType    The type of composition to perform
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       pSrc1== NULL, or pSrc2== NULL, or pDst == NULL
//     ippStsSizeErr          The roiSize has a field with negative or zero value
//     ippStsAlphaTypeErr     The alphaType is incorrect
//     Note:                  Result is wrong, if Alpha < 0 for signed types
*/

LEGACY90IPPAPI (IppStatus, legacy90ippiAlphaComp_8s_AC1R,
                   ( const Ipp8s* pSrc1, int src1Step,
                     const Ipp8s* pSrc2, int src2Step,
                     Ipp8s* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiAlphaCompC_8u_C1R, ippiAlphaCompC_16u_C1R
//                  ippiAlphaCompC_8s_C1R, ippiAlphaCompC_16s_C1R
//                  ippiAlphaCompC_32s_C1R, ippiAlphaCompC_32u_C1R
//  Purpose:        Combines two 1-channel images using constant alpha values
//  Parameters:
//     pSrc1        Pointer to the first source image
//     src1Step     Step through the first source image
//     pSrc2        Pointer to the second source image
//     src2Step     Step through the second source image
//     pDst         Pointer to the destination image
//     dstStep      Step through the destination image
//     roiSize      Size of the source and destination ROI
//     alpha1       The constant alpha value for the first source image
//     alpha2       The constant alpha value for the second source image
//     alphaType    The type of composition to perform
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       pSrc1== NULL, or pSrc2== NULL, or pDst == NULL
//     ippStsSizeErr          The roiSize has a field with negative or zero value
//     ippStsAlphaTypeErr     The alphaType is incorrect
//
//  Notes:          Value becomes 0 <= alphaA <= VAL_MAX
//                                0 <= alphaB <= VAL_MAX
*/

LEGACY90IPPAPI (IppStatus, legacy90ippiAlphaCompC_8s_C1R,
                   ( const Ipp8s* pSrc1, int src1Step,
                     Ipp8s alpha1,
                     const Ipp8s* pSrc2, int src2Step,
                     Ipp8s alpha2,
                     Ipp8s* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))


/* /////////////////////////////////////////////////////////////////////////////
//                  FFT Context Functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFFTInitAlloc
//  Purpose:    Allocates and initializes the FFT context structure
//  Parameters:
//     orderX     Base-2 logarithm of the number of samples in FFT (width)
//     orderY     Base-2 logarithm of the number of samples in FFT (height)
//     flag       Flag to choose the results normalization factors
//     hint       Option to select the algorithmic implementation of the transform
//                function
//     pFFTSpec   Double pointer to the FFT context structure
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       pFFTSpec == NULL
//     ippStsFftOrderErr      FFT order value is illegal
//     ippStsFFTFlagErr       Incorrect normalization flag value
//     ippStsMemAllocErr      Memory allocation fails
*/

LEGACY90IPPAPI (IppStatus, legacy90ippiFFTInitAlloc_R_32s,
                   ( IppiFFTSpec_R_32s** pFFTSpec,
                     int orderX, int orderY, int flag, IppHintAlgorithm hint ))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFFTFree
//  Purpose:    Deallocates memory used by the FFT context structure
//  Parameters:
//     pFFTSpec  Pointer to the FFT context structure
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       pFFTSpec == NULL
//     ippStsContextMatchErr  Invalid context structure
*/

LEGACY90IPPAPI (IppStatus, legacy90ippiFFTFree_R_32s, ( IppiFFTSpec_R_32s*  pFFTSpec ))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFFTGetBufSize
//  Purpose:    Computes the size of an external FFT work buffer (in bytes)
//  Parameters:
//     pFFTSpec   Pointer to the FFT context structure
//     pSize      Pointer to the size of the external buffer
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       One of the specified pointers is NULL
//     ippStsContextMatchErr  Invalid context structure
*/

LEGACY90IPPAPI (IppStatus, legacy90ippiFFTGetBufSize_R_32s,
                   ( const IppiFFTSpec_R_32s* pFFTSpec, int* pSize ))

/* /////////////////////////////////////////////////////////////////////////////
//                  FFT Transforms
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFFTFwd, ippiFFTInv
//  Purpose:    Performs forward or inverse FFT of an image
//  Parameters:
//     pFFTSpec   Pointer to the FFT context structure
//     pSrc       Pointer to the source image
//     srcStep    Step through the source image
//     pDst       Pointer to the destination image
//     dstStep    Step through the destination image
//     pSrcDst    Pointer to the source/destination image (in-place)
//     srcDstStep Step through the source/destination image (in-place)
//     pBuffer    Pointer to the external work buffer
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       One of the specified pointers with the exception of
                              pBuffer is NULL
//     ippStsStepErr          srcStep or dstStep value is zero or negative
//     ippStsContextMatchErr  Invalid context structure
//     ippStsMemAllocErr      Memory allocation error
*/

LEGACY90IPPAPI (IppStatus, legacy90ippiFFTFwd_RToPack_8u32s_C1RSfs,
                   ( const Ipp8u *pSrc, int srcStep,
                     Ipp32s *pDst, int dstStep,
                     const IppiFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u *pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippiFFTFwd_RToPack_8u32s_C3RSfs,
                   ( const Ipp8u *pSrc, int srcStep,
                     Ipp32s *pDst, int dstStep,
                     const IppiFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u *pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippiFFTFwd_RToPack_8u32s_C4RSfs,
                   ( const Ipp8u *pSrc, int srcStep,
                     Ipp32s *pDst, int dstStep,
                     const IppiFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u *pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippiFFTFwd_RToPack_8u32s_AC4RSfs,
                   ( const Ipp8u *pSrc, int srcStep,
                     Ipp32s *pDst, int dstStep,
                     const IppiFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u *pBuffer ))

LEGACY90IPPAPI (IppStatus, legacy90ippiFFTInv_PackToR_32s8u_C1RSfs,
                   ( const Ipp32s *pSrc, int srcStep,
                     Ipp8u *pDst, int dstStep,
                     const IppiFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u *pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippiFFTInv_PackToR_32s8u_C3RSfs,
                   ( const Ipp32s *pSrc, int srcStep,
                     Ipp8u *pDst, int dstStep,
                     const IppiFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u *pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippiFFTInv_PackToR_32s8u_C4RSfs,
                   ( const Ipp32s *pSrc, int srcStep,
                     Ipp8u *pDst, int dstStep,
                     const IppiFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u *pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippiFFTInv_PackToR_32s8u_AC4RSfs,
                   ( const Ipp32s *pSrc, int srcStep,
                     Ipp8u *pDst, int dstStep,
                     const IppiFFTSpec_R_32s* pFFTSpec,
                     int scaleFactor, Ipp8u *pBuffer ))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiDFTInitAlloc
//  Purpose:      Allocates and initializes the DFT context structure
//  Parameters:
//     roiSize    Size of the ROI
//     flag       Flag to choose the results normalization factors
//     hint       Option to select the algorithmic implementation of the transform
//                function
//     pDFTSpec   Double pointer to the DFT context structure
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       pDFTSpec == NULL
//     ippStsFftOrderErr      Invalid roiSize
//     ippStsSizeErr          roiSize has a field with zero or negative value
//     ippStsFFTFlagErr       Incorrect normalization flag value
//     ippStsMemAllocErr      Memory allocation error
*/

LEGACY90IPPAPI (IppStatus, legacy90ippiDFTInitAlloc_R_32s,
                   ( IppiDFTSpec_R_32s** pDFTSpec,
                     IppiSize roiSize, int flag, IppHintAlgorithm hint ))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiDFTFree
//  Purpose:    Deallocates memory used by the DFT context structure
//  Parameters:
//     pDFTSpec       Pointer to the DFT context structure
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       pDFTSpec == NULL
//     ippStsContextMatchErr  Invalid context structure
*/

LEGACY90IPPAPI (IppStatus, legacy90ippiDFTFree_R_32s, ( IppiDFTSpec_R_32s*  pFFTSpec ))


/* /////////////////////////////////////////////////////////////////////////////
//                  DFT Buffer Size
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiDFTGetBufSize
//  Purpose:    Computes the size of the external DFT work buffer (in bytes)
//  Parameters:
//     pDFTSpec   Pointer to the DFT context structure
//     pSize      Pointer to the size of the buffer
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       One of the specified pointers is NULL
//     ippStsContextMatchErr  Invalid context structure
*/

LEGACY90IPPAPI (IppStatus, legacy90ippiDFTGetBufSize_R_32s,
                   ( const IppiDFTSpec_R_32s* pDFTSpec, int* pSize ))


/* /////////////////////////////////////////////////////////////////////////////
//                  DFT Transforms
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiDFTFwd, ippiDFTInv
//  Purpose:    Performs forward or inverse DFT of an image
//  Parameters:
//     pDFTSpec    Pointer to the DFT context structure
//     pSrc        Pointer to source image
//     srcStep     Step through the source image
//     pDst        Pointer to the destination image
//     dstStep     Step through the destination image
//     pSrcDst     Pointer to the source/destination image (in-place)
//     srcDstStep  Step through the source/destination image (in-place)
//     pBuffer     Pointer to the external work buffer
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       One of the specified pointers with the exception of
                              pBuffer is NULL
//     ippStsStepErr          srcStep or dstStep value is zero or negative
//     ippStsContextMatchErr  Invalid context structure
//     ippStsMemAllocErr      Memory allocation error
*/

LEGACY90IPPAPI (IppStatus, legacy90ippiDFTFwd_RToPack_8u32s_C1RSfs,
                   ( const Ipp8u *pSrc, int srcStep,
                     Ipp32s *pDst, int dstStep,
                     const IppiDFTSpec_R_32s* pDFTSpec,
                     int scaleFactor, Ipp8u *pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippiDFTFwd_RToPack_8u32s_C3RSfs,
                   ( const Ipp8u *pSrc, int srcStep,
                     Ipp32s *pDst, int dstStep,
                     const IppiDFTSpec_R_32s* pDFTSpec,
                     int scaleFactor, Ipp8u *pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippiDFTFwd_RToPack_8u32s_C4RSfs,
                   ( const Ipp8u *pSrc, int srcStep,
                     Ipp32s *pDst, int dstStep,
                     const IppiDFTSpec_R_32s* pDFTSpec,
                     int scaleFactor, Ipp8u *pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippiDFTFwd_RToPack_8u32s_AC4RSfs,
                   ( const Ipp8u *pSrc, int srcStep,
                     Ipp32s *pDst, int dstStep,
                     const IppiDFTSpec_R_32s* pDFTSpec,
                     int scaleFactor, Ipp8u *pBuffer ))

LEGACY90IPPAPI (IppStatus, legacy90ippiDFTInv_PackToR_32s8u_C1RSfs,
                   ( const Ipp32s *pSrc, int srcStep,
                     Ipp8u *pDst, int dstStep,
                     const IppiDFTSpec_R_32s* pDFTSpec,
                     int scaleFactor, Ipp8u *pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippiDFTInv_PackToR_32s8u_C3RSfs,
                   ( const Ipp32s *pSrc, int srcStep,
                     Ipp8u *pDst, int dstStep,
                     const IppiDFTSpec_R_32s* pDFTSpec,
                     int scaleFactor, Ipp8u *pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippiDFTInv_PackToR_32s8u_C4RSfs,
                   ( const Ipp32s *pSrc, int srcStep,
                     Ipp8u *pDst, int dstStep,
                     const IppiDFTSpec_R_32s* pDFTSpec,
                     int scaleFactor, Ipp8u *pBuffer ))
LEGACY90IPPAPI (IppStatus, legacy90ippiDFTInv_PackToR_32s8u_AC4RSfs,
                   ( const Ipp32s *pSrc, int srcStep,
                     Ipp8u *pDst, int dstStep,
                     const IppiDFTSpec_R_32s* pDFTSpec,
                     int scaleFactor, Ipp8u *pBuffer ))


/* /////////////////////////////////////////////////////////////////////////////
//                   Image resampling functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiResampleRowGetSize_32f
//
//  Purpose:    calculate the size of IppiResampleRowSpec_32f structure
//   and size of working buffer
//
//  Returns:
//    ippStsNoErr           OK
//    ippStsNullPtrErr      one of pointers is NULL
//    ippStsOutOfRangeErr   one or more SampleWidth is incorrect
//
//  Parameters:
//    srcSampleWidth        distance between neighbor pixels of a source row
//                                                         on the reference grid
//    dstSampleWidth        distance between neighbor pixels of a destination
//                                                     row on the reference grid
//    pSpecSize             pointer where to store the calculated
//                                               Spec structure size (in bytes)
//    pBufSize              pointer where to store buffer size (in bytes)
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiResampleRowGetSize_32f, (int  srcSampleWidth, int  dstSampleWidth, int *pSpecSize, int *pBufSize))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiResampleRowInit_32f
//
//  Purpose:    initialize the IppiRowSpec structure by resampling parameters
//
//  Returns:
//    ippStsNoErr           OK
//    ippStsNullPtrErr      pRowSpec is NULL pointer
//    ippStsBadArgErr       incorrect or unsupported filter type
//    ippStsOutOfRangeErr   one or more SampleWidth is incorrect
//
//  Parameters:
//    filterType            type of interpolation filter using for resampling
//    srcSampleWidth        distance between neighbor pixels of a source row
//                                                         on the reference grid
//    dstSampleWidth        distance between neighbor pixels of a destination
//                                                     row on the reference grid
//    pRowSpec              pointer where to store initialized structure
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiResampleRowInit_32f, (IppiResampleRowSpec_32f *pRowSpec, IppiResampleType filterType, int srcSampleWidth, int dstSampleWidth))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiResampleRowGetBorderWidth_32f
//
//  Purpose:    get the width of left and right borders to be applied around
//              the source buffer for ippiResampleRow (for version requiring
//              borders around source buffer)
//
//  Returns:
//    ippStsNoErr           OK
//    ippStsNullPtrErr      One of the pointers is NULL
//    ippStsBadArgErr       pointed IppiResampleRowSpec_32f is corrupted
//
//  Parameters:
//    pRowSpec              pointer to initialized IppiResampleRowSpec_32f
//    pLeftWidth            pointer where to store left border width (in pixels)
//    pRightWidth           pointer where to store right border width (in pixels)
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiResampleRowGetBorderWidth_32f, (const IppiResampleRowSpec_32f *pRowSpec, int *pLeftWidth, int *pRightWidth))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiResampleRowReplicateBorder_32f_C1R, ippiResampleRow_32f_C1
//
//  Purpose:    Resample rows with specified parameters.
//              ippiResampleRowReplicateBorder_32f_C1R function require borders
//                  around source buffer
//              ippiResampleRow_32f_C1 function replicate borders
//
//  Returns:
//    ippStsNoErr           OK
//    ippStsNullPtrErr      One of the pointers is NULL
//    ippStsBadArgErr       pointed IppiResampleRowSpec_32f is corrupted
//    ippStsOutOfRangeErr   xOriginRefGrid is out of range
//    ippStsSizeErr         sizeRefGrid is wrong
//
//  Parameters:
//    pSrc                  pointer to the source row origin
//    srcLineStep           distance in bytes between starts of consecutive lines
//                                                            in the source image
//    pDst                  pointer to the destination row origin
//    dstLineStep           distance in bytes between starts of consecutive lines
//                                                       in the destination image
//    xOriginRefGrid        X coordinate of the image origin at reference grid
//    sizeRefGrid           size of image in terms of  reference grid
//    pRowSpec              pointer to initialized IppiResampleRowSpec_32f
//    pBuffer               pointer to work buffer
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiResampleRowReplicateBorder_32f_C1R, (const Ipp32f *pSrc, int srcLineStep, Ipp32f *pDst, int dstLineStep,
            int xOriginRefGrid, IppiSize sizeRefGrid, const IppiResampleRowSpec_32f *pRowSpec, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResampleRow_32f_C1, (const Ipp32f *pSrc, int srcLineStep, Ipp32f *pDst, int dstLineStep, int xOriginRefGrid,
            IppiSize sizeRefGrid, const IppiResampleRowSpec_32f *pRowSpec, Ipp8u *pBuffer))


/* /////////////////////////////////////////////////////////////////////////////
//                   Geometric Transform functions
///////////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiRemap
//  Purpose:            Transforms the source image by remapping its pixels
//                          dst[i,j] = src[xMap[i,j], yMap[i,j]]
//  Parameters:
//    pSrc              Pointer to the source image (point to pixel (0,0)). An array
//                      of pointers to each plane of the source image for planar data
//    srcSize           Size of the source image
//    srcStep           Step through the source image
//    srcROI            Region if interest in the source image
//    pxMap             Pointer to image with x coordinates of map
//    xMapStep          The step in xMap image
//    pyMap             The pointer to image with y coordinates of map
//    yMapStep          The step in yMap image
//    pDst              Pointer to the destination image. An array of pointers
//                      to each plane of the destination image for planar data
//    dstStep           Step through the destination image
//    dstRoiSize        Size of the destination ROI
//    interpolation     The type of interpolation to perform for image resampling
//                      The following types are currently supported:
//                        IPPI_INTER_NN       Nearest neighbor interpolation
//                        IPPI_INTER_LINEAR   Linear interpolation
//                        IPPI_INTER_CUBIC    Cubic interpolation
//                        IPPI_INTER_CUBIC2P_CATMULLROM  Catmull-Rom cubic filter
//                        IPPI_INTER_LANCZOS  Interpolation by Lanczos3-windowed sinc function
//                      The special feature in addition to one of general methods:
//                        IPPI_SMOOTH_EDGE    Edges smoothing
//  Returns:
//    ippStsNoErr       OK
//    ippStsNullPtrErr  One of the pointers is NULL
//    ippStsSizeErr     srcROI or dstRoiSize has a field with zero or negative value
//    ippStsStepErr     One of the step values is zero or negative
//    ippStsInterpolateErr  interpolation has an illegal value
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiRemap_8u_P3R, (const Ipp8u* const pSrc[3], IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp32f* pxMap, int xMapStep, const Ipp32f* pyMap,
    int yMapStep, Ipp8u* const pDst[3], int dstStep, IppiSize dstROI, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRemap_8u_P4R, (const Ipp8u* const pSrc[4], IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp32f* pxMap, int xMapStep, const Ipp32f* pyMap,
    int yMapStep, Ipp8u* const pDst[4], int dstStep, IppiSize dstROI, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRemap_16u_P3R, (const Ipp16u* const pSrc[3], IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp32f* pxMap, int xMapStep, const Ipp32f* pyMap,
    int yMapStep, Ipp16u* const pDst[3], int dstStep, IppiSize dstROI, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRemap_16u_P4R, (const Ipp16u* const pSrc[4], IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp32f* pxMap, int xMapStep, const Ipp32f* pyMap,
    int yMapStep, Ipp16u* const pDst[4], int dstStep, IppiSize dstROI, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRemap_16s_P3R, (const Ipp16s* const pSrc[3], IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp32f* pxMap, int xMapStep, const Ipp32f* pyMap,
    int yMapStep, Ipp16s* const pDst[3], int dstStep, IppiSize dstROI, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRemap_16s_P4R, (const Ipp16s* const pSrc[4], IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp32f* pxMap, int xMapStep, const Ipp32f* pyMap,
    int yMapStep, Ipp16s* const pDst[4], int dstStep, IppiSize dstROI, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRemap_32f_P3R, (const Ipp32f* const pSrc[3], IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp32f* pxMap, int xMapStep, const Ipp32f* pyMap,
    int yMapStep, Ipp32f* const pDst[3], int dstStep, IppiSize dstROI, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRemap_32f_P4R, (const Ipp32f* const pSrc[4], IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp32f* pxMap, int xMapStep, const Ipp32f* pyMap,
    int yMapStep, Ipp32f* const pDst[4], int dstStep, IppiSize dstROI, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRemap_64f_P3R, (const Ipp64f* const pSrc[3], IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp64f* pxMap, int xMapStep, const Ipp64f* pyMap,
    int yMapStep, Ipp64f* const pDst[3], int dstStep, IppiSize dstROI, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRemap_64f_P4R, (const Ipp64f* const pSrc[4], IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp64f* pxMap, int xMapStep, const Ipp64f* pyMap,
    int yMapStep, Ipp64f* const pDst[4], int dstStep, IppiSize dstROI, int interpolation))


/* /////////////////////////////////////////////////////////////////////////////
//                     Resize functions
// ////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//
//  Name:               ippiResizeYUV422_8u_C2R
//  Purpose:            Resize source image by xFactor and yFactor
//  Parameters:
//    pSrc              source image data
//    srcSize           size of src
//    srcStep           step in src
//    srcROI            region of interest of src
//    pDst              resultant image data
//    dstStep           step in dst
//    dstROI            region of interest of dst
//    xFactor, yFactor  they specify fractions of resizing
//    interpolation     type of interpolation to perform for resampling the input image:
//                      IPPI_INTER_NN      nearest neighbour interpolation
//                      IPPI_INTER_LINEAR  linear interpolation
//                      IPPI_INTER_CUBIC   cubic convolution interpolation
//  Returns:
//    ippStsNoErr             no errors
//    ippStsNullPtrErr        pSrc == NULL or pDst == NULL
//    ippStsSizeErr           width or height of images is less or equal zero,
//                            width of src image is odd,
//                            width of region of interest of src is odd,
//                            xoffset of region of interest of src is odd,
//                            width of region of interest of dst is less two
//    ippStsResizeNoOperationErr one of the output image dimensions is less than 1 pixel
//    ippStsResizeFactorErr   xFactor or yFactor is less or equal zero
//    ippStsInterpolationErr  (interpolation != IPPI_INTER_NN) &&
//                            (interpolation != IPPI_INTER_LINEAR) &&
//                            (interpolation != IPPI_INTER_CUBIC)
//  Notes:
//    YUY2 pixel format (Y0U0Y1V0,Y2U1Y3V1,.. or Y0Cb0Y1Cr0,Y2Cb1Y3Cr1,..)
//    not in-place
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiResizeYUV422_8u_C2R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI,
                                            Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
                                            double xFactor, double yFactor, int interpolation))

/* /////////////////////////////////////////////////////////////////////////////
//
//  Name:               ippiResizeGetBufSize, ippiResizeGetBufSize_64f
//  Purpose:            Computes the size of an external work buffer (in bytes)
//  Parameters:
//    srcROI            region of interest of source image
//    dstROI            region of interest of destination image
//    nChannel          number of channels
//    interpolation     type of interpolation to perform for resizing the input image:
//                        IPPI_INTER_NN      Nearest Neighbor interpolation
//                        IPPI_INTER_LINEAR  Linear interpolation
//                        IPPI_INTER_CUBIC   Cubic polynomial interpolation
//                        IPPI_INTER_LANCZOS Interpolation by Lanczos3-windowed sinc function
//                        IPPI_INTER_SUPER   Super Sampling method
//                      including two-parameter cubic filters:
//                        IPPI_INTER_CUBIC2P_BSPLINE    B-spline filter (1, 0)
//                        IPPI_INTER_CUBIC2P_CATMULLROM Catmull-Rom filter (0, 1/2)
//                        IPPI_INTER_CUBIC2P_B05C03     Special filter with parameters (1/2, 3/10)
//                      including special feature for smoothing:
//                        IPPI_SMOOTH_EDGE   Edges smoothing in addition to one of general methods
//                        IPPI_SUBPIXEL_EDGE Edges handling in addition to one of general methods
//                      including special feature for antialiasing:
//                        IPPI_ANTIALIASING  Anti-aliasing method in addition to Linear/Cubic/Lanczos
//    pSize             pointer to the external buffer`s size
//  Returns:
//    ippStsNoErr             no errors
//    ippStsNullPtrErr        pSize == NULL
//    ippStsSizeErr           width or height of images is less or equal zero, or
//                            the calculated buffer size exceeds maximum 32 bit signed integer positive value
//                            (the processed image ROIs are are too large )
//    ippStsNumChannelsErr    number of channels is not 1, 3 or 4
//    ippStsInterpolationErr  interpolation has an illegal value
//    ippStsNoAntialiasing    mode does not support antialiasing
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiResizeGetBufSize, (
    IppiRect srcROI, IppiRect dstROI, int nChannel, int interpolation, int* pSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeGetBufSize_64f, (
    IppiRect srcROI, IppiRect dstROI, int nChannel, int interpolation, int* pSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiGetResizeRect
//  Purpose:            Computes coordinates of the destination rectangle
//  Parameters:
//    srcROI            region of interest of source image
//    pDstRect          pointer to resultant rectangle
//    xFactor, yFactor  they specify fractions of resizing
//    xShift, yShift    they specify shifts of resizing
//    interpolation     type of interpolation
//  Returns:
//    ippStsNoErr             no errors
//    ippStsNullPtrErr        pDstRect == NULL
//    ippStsSizeErr           width or height of srcROI is less or equal zero
//    ippStsResizeFactorErr   xFactor or yFactor is less or equal zero
//    ippStsInterpolationErr  interpolation has an illegal value
//    ippStsNoOperation       processed area is disappeared, no operation
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiGetResizeRect, (
    IppiRect srcROI, IppiRect* pDstRect,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation))

/* /////////////////////////////////////////////////////////////////////////////
//
//  Name:               ippiResizeSqrPixel
//  Purpose:            Performs RESIZE transform of the source image by xFactor and yFactor
//                            |X'|   |xFactor    0   |   |X|   |xShift|
//                            |  | = |               | * | | + |      |
//                            |Y'|   |   0    yFactor|   |Y|   |yShift|
//  Parameters:
//    pSrc              source image data
//    srcSize           size of source image
//    srcStep           step in source image
//    srcROI            region of interest of source image
//    pDst              resultant image data
//    dstStep           step in destination image
//    dstROI            region of interest of destination image
//    xFactor, yFactor  they specify fractions of resizing
//    xShift, yShift    they specify shifts of resizing
//    interpolation     type of interpolation to perform for resizing the input image:
//                        IPPI_INTER_NN      Nearest Neighbor interpolation
//                        IPPI_INTER_LINEAR  Linear interpolation
//                        IPPI_INTER_CUBIC   Cubic polynomial interpolation
//                        IPPI_INTER_LANCZOS Interpolation by Lanczos3-windowed sinc function
//                        IPPI_INTER_SUPER   Super Sampling method
//                      including two-parameter cubic filters:
//                        IPPI_INTER_CUBIC2P_BSPLINE    B-spline filter (1, 0)
//                        IPPI_INTER_CUBIC2P_CATMULLROM Catmull-Rom filter (0, 1/2)
//                        IPPI_INTER_CUBIC2P_B05C03     Special filter with parameters (1/2, 3/10)
//                      including special feature for smoothing:
//                        IPPI_SMOOTH_EDGE    Edges smoothing in addition to one of the above methods
//                        IPPI_SUBPIXEL_EDGE Edges handling in addition to one of general methods
//                      including special feature for antialiasing:
//                        IPPI_ANTIALIASING  Anti-aliasing method in addition to Linear/Cubic/Lanczos
//    pBuffer           pointer to work buffer
//  Returns:
//    ippStsNoErr             no errors
//    ippStsNullPtrErr        pSrc == NULL or pDst == NULL or pBuffer == NULL
//    ippStsSizeErr           width or height of images is less or equal zero
//    ippStsWrongIntersectROI srcROI has not intersection with the source image, no operation
//    ippStsResizeFactorErr   xFactor or yFactor is less or equal zero
//    ippStsInterpolationErr  interpolation has an illegal value
//    ippStsNoAntialiasing    mode does not support antialiasing
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_8u_C1R, (
    const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp8u* pDst, int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_8u_C3R, (
    const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp8u* pDst, int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_8u_C4R, (
    const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp8u* pDst, int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_8u_AC4R, (
    const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp8u* pDst, int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_8u_P3R, (
    const Ipp8u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp8u* const pDst[3], int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_8u_P4R, (
    const Ipp8u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp8u* const pDst[4], int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_16u_C1R, (
    const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp16u* pDst, int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_16u_C3R, (
    const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp16u* pDst, int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_16u_C4R, (
    const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp16u* pDst, int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_16u_AC4R, (
    const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp16u* pDst, int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_16u_P3R, (
    const Ipp16u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp16u* const pDst[3], int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_16u_P4R, (
    const Ipp16u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp16u* const pDst[4], int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_16s_C1R, (
    const Ipp16s* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp16s* pDst, int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_16s_C3R, (
    const Ipp16s* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp16s* pDst, int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_16s_C4R, (
    const Ipp16s* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp16s* pDst, int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_16s_AC4R, (
    const Ipp16s* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp16s* pDst, int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_16s_P3R, (
    const Ipp16s* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp16s* const pDst[3], int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_16s_P4R, (
    const Ipp16s* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp16s* const pDst[4], int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_32f_C1R, (
    const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp32f* pDst, int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_32f_C3R, (
    const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp32f* pDst, int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_32f_C4R, (
    const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp32f* pDst, int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_32f_AC4R, (
    const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp32f* pDst, int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_32f_P3R, (
    const Ipp32f* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp32f* const pDst[3], int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_32f_P4R, (
    const Ipp32f* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp32f* const pDst[4], int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_64f_C1R, (
    const Ipp64f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp64f* pDst, int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_64f_C3R, (
    const Ipp64f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp64f* pDst, int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_64f_C4R, (
    const Ipp64f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp64f* pDst, int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_64f_AC4R, (
    const Ipp64f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp64f* pDst, int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_64f_P3R, (
    const Ipp64f* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp64f* const pDst[3], int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiResizeSqrPixel_64f_P4R, (
    const Ipp64f* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp64f* const pDst[4], int dstStep, IppiRect dstROI,
    double xFactor, double yFactor, double xShift, double yShift, int interpolation, Ipp8u *pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//
//  Name:               ippiSuperSamplingGetBufSize
//  Purpose:            Computes the size of an external work buffer (in bytes)
//  Parameters:
//    srcRoiSize        region of interest of source image
//    dstRoiSize        region of interest of destination image
//    nChannel          number of channels
//    pSize             pointer to the external buffer`s size
//  Returns:
//    ippStsNoErr       no errors
//    ippStsNullPtrErr  pSize == NULL
//    ippStsSizeErr     one of the image dimensions has zero or negative value
//                      or any dimension of src less than appropriate dimension of dst
//    ippStsNumChannelsErr number of channels is not 1 or 3 or 4
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiSuperSamplingGetBufSize, (
    IppiSize srcRoiSize, IppiSize dstRoiSize, int nChannel, int *pSize))

/* /////////////////////////////////////////////////////////////////////////////
//
//  Name:               ippiSuperSampling
//  Purpose:            Performs RESIZE transform using Super Sampling method
//  Parameters:
//    pSrc              source image data
//    srcStep           step in source image
//    srcRoiSize        region of interest of source image
//    pDst              resultant image data
//    dstStep           step in destination image
//    dstRoiSize        region of interest of destination image
//    pBuffer           pointer to work buffer
//  Returns:
//    ippStsNoErr       no errors
//    ippStsNullPtrErr  pSrc == NULL or pDst == NULL or pBuffer == NULL
//    ippStsStepErr     srcStep or dstStep has a zero or negative value
//    ippStsSizeErr     one of the image dimensions has zero or negative value
//                      or any dimension of src less than appropriate dimension of dst
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiSuperSampling_8u_C1R, (
    const Ipp8u* pSrc, int srcStep, IppiSize srcRoiSize,
    Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
    Ipp8u* pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiSuperSampling_8u_C3R, (
    const Ipp8u* pSrc, int srcStep, IppiSize srcRoiSize,
    Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
    Ipp8u* pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiSuperSampling_8u_C4R, (
    const Ipp8u* pSrc, int srcStep, IppiSize srcRoiSize,
    Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
    Ipp8u* pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiSuperSampling_8u_AC4R, (
    const Ipp8u* pSrc, int srcStep, IppiSize srcRoiSize,
    Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
    Ipp8u* pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiSuperSampling_8u_P3R, (
    const Ipp8u* const pSrc[3], int srcStep, IppiSize srcRoiSize,
    Ipp8u* const pDst[3], int dstStep, IppiSize dstRoiSize,
    Ipp8u* pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiSuperSampling_8u_P4R, (
    const Ipp8u* const pSrc[4], int srcStep, IppiSize srcRoiSize,
    Ipp8u* const pDst[4], int dstStep, IppiSize dstRoiSize,
    Ipp8u* pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiSuperSampling_16u_C1R, (
    const Ipp16u* pSrc, int srcStep, IppiSize srcRoiSize,
    Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,
    Ipp8u* pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiSuperSampling_16u_C3R, (
    const Ipp16u* pSrc, int srcStep, IppiSize srcRoiSize,
    Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,
    Ipp8u* pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiSuperSampling_16u_C4R, (
    const Ipp16u* pSrc, int srcStep, IppiSize srcRoiSize,
    Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,
    Ipp8u* pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiSuperSampling_16u_AC4R, (
    const Ipp16u* pSrc, int srcStep, IppiSize srcRoiSize,
    Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,
    Ipp8u* pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiSuperSampling_16u_P3R, (
    const Ipp16u* const pSrc[3], int srcStep, IppiSize srcRoiSize,
    Ipp16u* const pDst[3], int dstStep, IppiSize dstRoiSize,
    Ipp8u* pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiSuperSampling_16u_P4R, (
    const Ipp16u* const pSrc[4], int srcStep, IppiSize srcRoiSize,
    Ipp16u* const pDst[4], int dstStep, IppiSize dstRoiSize,
    Ipp8u* pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiSuperSampling_16s_C1R, (
    const Ipp16s* pSrc, int srcStep, IppiSize srcRoiSize,
    Ipp16s* pDst, int dstStep, IppiSize dstRoiSize,
    Ipp8u* pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiSuperSampling_16s_C3R, (
    const Ipp16s* pSrc, int srcStep, IppiSize srcRoiSize,
    Ipp16s* pDst, int dstStep, IppiSize dstRoiSize,
    Ipp8u* pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiSuperSampling_16s_C4R, (
    const Ipp16s* pSrc, int srcStep, IppiSize srcRoiSize,
    Ipp16s* pDst, int dstStep, IppiSize dstRoiSize,
    Ipp8u* pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiSuperSampling_16s_AC4R, (
    const Ipp16s* pSrc, int srcStep, IppiSize srcRoiSize,
    Ipp16s* pDst, int dstStep, IppiSize dstRoiSize,
    Ipp8u* pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiSuperSampling_16s_P3R, (
    const Ipp16s* const pSrc[3], int srcStep, IppiSize srcRoiSize,
    Ipp16s* const pDst[3], int dstStep, IppiSize dstRoiSize,
    Ipp8u* pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiSuperSampling_16s_P4R, (
    const Ipp16s* const pSrc[4], int srcStep, IppiSize srcRoiSize,
    Ipp16s* const pDst[4], int dstStep, IppiSize dstRoiSize,
    Ipp8u* pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiSuperSampling_32f_C1R, (
    const Ipp32f* pSrc, int srcStep, IppiSize srcRoiSize,
    Ipp32f* pDst, int dstStep, IppiSize dstRoiSize,
    Ipp8u* pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiSuperSampling_32f_C3R, (
    const Ipp32f* pSrc, int srcStep, IppiSize srcRoiSize,
    Ipp32f* pDst, int dstStep, IppiSize dstRoiSize,
    Ipp8u* pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiSuperSampling_32f_C4R, (
    const Ipp32f* pSrc, int srcStep, IppiSize srcRoiSize,
    Ipp32f* pDst, int dstStep, IppiSize dstRoiSize,
    Ipp8u* pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiSuperSampling_32f_AC4R, (
    const Ipp32f* pSrc, int srcStep, IppiSize srcRoiSize,
    Ipp32f* pDst, int dstStep, IppiSize dstRoiSize,
    Ipp8u* pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiSuperSampling_32f_P3R, (
    const Ipp32f* const pSrc[3], int srcStep, IppiSize srcRoiSize,
    Ipp32f* const pDst[3], int dstStep, IppiSize dstRoiSize,
    Ipp8u* pBuffer))
LEGACY90IPPAPI(IppStatus, legacy90ippiSuperSampling_32f_P4R, (
    const Ipp32f* const pSrc[4], int srcStep, IppiSize srcRoiSize,
    Ipp32f* const pDst[4], int dstStep, IppiSize dstRoiSize,
    Ipp8u* pBuffer))


/* /////////////////////////////////////////////////////////////////////////////
//                     Resize functions. NV12 format
// ////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeYUV420GetBufSize
//  Purpose:            Computes the size of an external work buffer (in bytes)
//  Parameters:
//    srcRoiSize        region of interest of source image
//    dstRoiSize        region of interest of destination image
//    interpolation     type of interpolation to perform for resizing the image:
//                        IPPI_INTER_LANCZOS Interpolation by Lanczos3-windowed sinc function
//                        IPPI_INTER_SUPER   Super Sampling method
//    pSize             pointer to the external buffer`s size
//  Returns:
//    ippStsNoErr       no errors
//    ippStsNullPtrErr  pSize == NULL
//    ippStsSizeErr     width or height of srcRoiSize or dstRoiSize less than two
//                      width or height of srcRoiSize less than appropriate dimension of dstRoiSize (IPPI_INTER_SUPER)
//    ippStsInterpolationErr  interpolation has an illegal value
//    ippStsDoubleSize  width or height of srcRoiSize or dstRoiSize isn't multiple of two (indicates warning)
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiResizeYUV420GetBufSize, (
    IppiSize srcRoiSize, IppiSize dstRoiSize, int interpolation, int *pSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeYUV420_8u_P2R
//  Purpose:            Performs RESIZE transform of the NV12 image
//  Parameters:
//    pSrcY             source image Y plane
//    srcYStep          step through the source image Y plane
//    pSrcUV            source image UV plane
//    srcUVStep         step through the source image UV plane
//    srcRoiSize        size of the region of interest of source image
//    pDstY             destination image Y plane
//    dstYStep          step through the destination image Y plane
//    pDstUV            destination image UV plane
//    dstUVStep         step through the destination image UV plane
//    dstRoiSize        size of the region of interest of destination image
//    interpolation     type of interpolation to perform for resizing the image:
//                        IPPI_INTER_LANCZOS Interpolation by Lanczos3-windowed sinc function
//                        IPPI_INTER_SUPER   Super Sampling method
//    pBuffer           pointer to work buffer
//  Returns:
//    ippStsNoErr       no errors
//    ippStsNullPtrErr  one of the pointers is NULL
//    ippStsSizeErr     width or height of srcRoiSize or dstRoiSize less than two
//                      width or height of srcRoiSize less than appropriate dimension of dstRoiSize (IPPI_INTER_SUPER)
//    ippStsInterpolationErr  interpolation has an illegal value
//    ippStsDoubleSize  width or height of srcRoiSize or dstRoiSize isn't multiple of two (indicates warning)
//  Notes:
//    Source 4:2:0 two-plane image format (NV12):
//    all Y samples (pSrcY) are found first in memory as an array of
//    unsigned char with an even number of lines memory alignment,
//    followed immediately by an array (pSrcUV) of unsigned char
//    containing interleaved U and V samples
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiResizeYUV420_8u_P2R, (
    const Ipp8u* pSrcY, int srcYStep,
    const Ipp8u* pSrcUV, int srcUVStep, IppiSize srcRoiSize,
    Ipp8u* pDstY, int dstYStep,
    Ipp8u* pDstUV, int dstUVStep, IppiSize dstRoiSize,
    int interpolation, Ipp8u *pBuffer))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiWarpGetBorderSize
//  Purpose:            Computes the size of possible borders for Warp transform
//
//  Parameters:
//    pSpec             Pointer to the Spec structure for warp transform
//    borderSize        Size of necessary borders (for memory allocation)
//
//  Return Values:
//    ippStsNoErr           Indicates no error
//    ippStsNullPtrErr      Indicates an error if one of the specified pointers is NULL
//    ippStsContextMatchErr Indicates an error if pointer to an invalid pSpec structure is passed
*/
LEGACY90IPPAPI (IppStatus, legacy90ippiWarpGetBorderSize, (IppiWarpSpec* pSpec, IppiBorderSize* borderSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiWarpAffine
//  Purpose:            Performs affine transform of the source image.
//                        |X'|   |a11 a12| |X| |a13|
//                        |  | = |       |*| |+|   |
//                        |Y'|   |a21 a22| |Y| |a23|
//  Parameters:
//    pSrc              Pointer to the source image data (point to pixel (0,0))
//    srcSize           Size of the source image
//    srcStep           Step through the source image
//    srcROI            Region of interest in the source image
//    pDst              Pointer to  the destination image (point to pixel (0,0))
//    dstStep           Step through the destination image
//    dstROI            Region of interest in the destination image
//    coeffs            The affine transform matrix
//    interpolation     The type of interpolation to perform the input image:
//                        IPPI_INTER_NN       Nearest neighbor interpolation
//                        IPPI_INTER_LINEAR   Linear interpolation
//                        IPPI_INTER_CUBIC    Cubic convolution interpolation
//                        IPPI_INTER_CUBIC2P_CATMULLROM  Catmull-Rom cubic filter
//                      The special feature in addition to one of general methods:
//                        IPPI_SMOOTH_EDGE    Edges smoothing
//  Returns:
//    ippStsNoErr           OK
//    ippStsNullPtrErr      pSrc or pDst is NULL
//    ippStsSizeErr         One of the image dimensions has zero or negative value
//    ippStsInterpolateErr  interpolation has an illegal value
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffine_8u_C1R, (
    const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI,
    const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffine_8u_C3R, (
    const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI,
    const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffine_8u_C4R, (
    const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI,
    const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffine_8u_AC4R, (
    const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI,
    const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffine_8u_P3R, (
    const Ipp8u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* const pDst[3], int dstStep,
    IppiRect dstROI, const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffine_8u_P4R, (
    const Ipp8u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* const pDst[4], int dstStep, IppiRect dstROI,
    const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffine_16u_C1R, (
    const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI,
    const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffine_16u_C3R, (
    const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI,
    const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffine_16u_C4R, (
    const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI,
    const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffine_16u_AC4R, (
    const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI,
    const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffine_16u_P3R, (
    const Ipp16u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* const pDst[3], int dstStep, IppiRect dstROI,
    const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffine_16u_P4R, (
    const Ipp16u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* const pDst[4], int dstStep, IppiRect dstROI,
    const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffine_32f_C1R, (
    const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI,
    const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffine_32f_C3R, (
    const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI,
    const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffine_32f_C4R, (
    const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI,
    const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffine_32f_AC4R, (
    const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI,
    const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffine_32f_P3R, (
    const Ipp32f* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* const pDst[3], int dstStep,
    IppiRect dstROI, const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffine_32f_P4R, (
    const Ipp32f* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* const pDst[4], int dstStep,
    IppiRect dstROI, const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffine_64f_C1R, (
    const Ipp64f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp64f* pDst, int dstStep, IppiRect dstROI,
    const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffine_64f_C3R, (
    const Ipp64f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp64f* pDst, int dstStep, IppiRect dstROI,
    const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffine_64f_C4R, (
    const Ipp64f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp64f* pDst, int dstStep, IppiRect dstROI,
    const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffine_64f_AC4R, (
    const Ipp64f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp64f* pDst, int dstStep, IppiRect dstROI,
    const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffine_64f_P3R, (
    const Ipp64f* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp64f* const pDst[3], int dstStep,
    IppiRect dstROI, const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffine_64f_P4R, (
    const Ipp64f* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp64f* const pDst[4], int dstStep,
    IppiRect dstROI, const double coeffs[2][3], int interpolation))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiWarpAffineBack
//  Purpose:    Performs an inverse affine transform of an image
//                  |X'|   |a11 a12| |X| |a13|
//                  |  | = |       |*| |+|   |
//                  |Y'|   |a21 a22| |Y| |a23|
//  Context:
//  Returns:                IppStatus
//    ippStsNoErr           OK
//    ippStsNullPtrErr      pSrc or pDst is NULL
//    ippStsSizeErr         One of the image dimensions has zero or negative value
//    ippStsInterpolateErr  interpolation has an illegal value
//  Parameters:
//      pSrc        Pointer to the source image data (point to pixel (0,0))
//      srcSize     Size of the source image
//      srcStep     Step through the source image
//      srcROI      Region of interest in the source image
//      pDst        Pointer to  the destination image (point to pixel (0,0))
//      dstStep     Step through the destination image
//      dstROI      Region of interest in the destination image
//      coeffs      The affine transform matrix
//      interpolation The type of interpolation to perform for resampling
//                  the input image. Possible values:
//                  IPPI_INTER_NN       Nearest neighbor interpolation
//                  IPPI_INTER_LINEAR   Linear interpolation.
//                  IPPI_INTER_CUBIC    Cubic convolution interpolation
//  Notes:
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineBack_8u_C1R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineBack_8u_C3R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineBack_8u_AC4R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineBack_8u_P3R, (const Ipp8u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* const pDst[3], int dstStep, IppiRect dstROI, const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineBack_8u_C4R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineBack_8u_P4R, (const Ipp8u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* const pDst[4], int dstStep, IppiRect dstROI, const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineBack_32f_C1R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineBack_32f_C3R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineBack_32f_AC4R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineBack_32f_P3R, (const Ipp32f* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* const pDst[3], int dstStep, IppiRect dstROI, const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineBack_32f_C4R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineBack_32f_P4R, (const Ipp32f* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* const pDst[4], int dstStep, IppiRect dstROI, const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineBack_16u_C1R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineBack_16u_C3R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineBack_16u_AC4R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineBack_16u_P3R, (const Ipp16u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* const pDst[3], int dstStep, IppiRect dstROI, const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineBack_16u_C4R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineBack_16u_P4R, (const Ipp16u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* const pDst[4], int dstStep, IppiRect dstROI, const double coeffs[2][3], int interpolation))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiWarpAffineQuad
//  Purpose:  Performs affine transform of the given source quadrangle
//            to the specified destination quadrangle
//                  |X'|   |a11 a12| |X| |a13|
//                  |  | = |       |*| |+|   |
//                  |Y'|   |a21 a22| |Y| |a23|
//  Context:
//  Returns:                IppStatus
//    ippStsNoErr           OK
//    ippStsNullPtrErr      pSrc or pDst is NULL
//    ippStsSizeErr         One of the image dimensions has zero or negative value
//    ippStsStepErr         srcStep or dstStep has a zero or negative value
//    ippStsInterpolateErr  interpolation has an illegal value
//  Parameters:
//      pSrc        Pointer to the source image data (point to pixel (0,0))
//      srcSize     Size of the source image
//      srcStep     Step through the source image
//      srcROI      Region of interest in the source image
//      srcQuad     Given quadrangle in the source image
//      pDst        Pointer to  the destination image (point to pixel (0,0))
//      dstStep     Step through the destination image
//      dstROI      Region of interest in the destination image
//      dstQuad     Given quadrangle in the destination image
//      interpolation The type of interpolation to perform for resampling
//                  the input image. Possible values:
//                  IPPI_INTER_NN       Nearest neighbor interpolation
//                  IPPI_INTER_LINEAR   Linear interpolation
//                  IPPI_INTER_CUBIC    Cubic convolution interpolation
//                 +IPPI_SMOOTH_EDGE    Edges smoothing in addition to one of the
//                                      above methods
//  Notes: The function computes the coordinates of the 4th vertex of the quadrangle
//         that uniquely depends on the three other (specified) vertices.
//         If the computed coordinates are not equal to the ones specified in quad,
//         the function returns the warning message and continues operation with the computed values
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineQuad_8u_C1R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp8u* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineQuad_8u_C3R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp8u* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineQuad_8u_AC4R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp8u* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineQuad_8u_P3R, (const Ipp8u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp8u* const pDst[3], int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineQuad_8u_C4R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp8u* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineQuad_8u_P4R, (const Ipp8u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp8u* const pDst[4], int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineQuad_32f_C1R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp32f* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineQuad_32f_C3R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp32f* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineQuad_32f_AC4R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp32f* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineQuad_32f_P3R, (const Ipp32f* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp32f* const pDst[3], int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineQuad_32f_C4R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp32f* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineQuad_32f_P4R, (const Ipp32f* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp32f* const pDst[4], int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineQuad_16u_C1R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp16u* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineQuad_16u_C3R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp16u* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineQuad_16u_AC4R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp16u* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineQuad_16u_P3R, (const Ipp16u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp16u* const pDst[3], int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineQuad_16u_C4R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp16u* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpAffineQuad_16u_P4R, (const Ipp16u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp16u* const pDst[4], int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiRotate
//  Purpose:            Rotates an image around (0, 0) by specified angle + shifts it
//  Parameters:
//    pSrc              Pointer to the source image data (point to pixel (0,0))
//    srcSize           Size of the source image
//    srcStep           Step through the source image
//    srcROI            Region of interest in the source image
//    pDst              Pointer to  the destination image (point to pixel (0,0))
//    dstStep           Step through the destination image
//    dstROI            Region of interest in the destination image
//    angle             The angle of clockwise rotation in degrees
//    xShif, yShift     The shift along the corresponding axis
//    interpolation     The type of interpolation to perform for rotating the input image:
//                        IPPI_INTER_NN       Nearest neighbor interpolation
//                        IPPI_INTER_LINEAR   Linear interpolation
//                        IPPI_INTER_CUBIC    Cubic convolution interpolation
//                        IPPI_INTER_CUBIC2P_CATMULLROM  Catmull-Rom cubic filter
//                      The special feature in addition to one of general methods:
//                        IPPI_SMOOTH_EDGE    Edges smoothing
//  Returns:
//    ippStsNoErr       OK
//    ippStsNullPtrErr  pSrc or pDst is NULL
//    ippStsSizeErr     One of the image dimensions has zero or negative value
//    ippStsStepErr     srcStep or dstStep has a zero or negative value
//    ippStsInterpolateErr  interpolation has an illegal value
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiRotate_8u_C1R, (
    const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI,
    double angle, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotate_8u_C3R, (
    const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI,
    double angle, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotate_8u_C4R, (
    const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI,
    double angle, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotate_8u_AC4R, (
    const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI,
    double angle, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotate_8u_P3R, (
    const Ipp8u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* const pDst[3], int dstStep,
    IppiRect dstROI, double angle, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotate_8u_P4R, (
    const Ipp8u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* const pDst[4], int dstStep,
    IppiRect dstROI, double angle, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotate_16u_C1R, (
    const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI,
    double angle, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotate_16u_C3R, (
    const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI,
    double angle, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotate_16u_C4R, (
    const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI,
    double angle, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotate_16u_AC4R, (
    const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI,
    double angle, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotate_16u_P3R, (
    const Ipp16u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* const pDst[3], int dstStep,
    IppiRect dstROI, double angle, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotate_16u_P4R, (
    const Ipp16u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* const pDst[4], int dstStep,
    IppiRect dstROI, double angle, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotate_32f_C1R, (
    const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI,
    double angle, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotate_32f_C3R, (
    const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI,
    double angle, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotate_32f_C4R, (
    const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI,
    double angle, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotate_32f_AC4R, (
    const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI,
    double angle, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotate_32f_P3R, (
    const Ipp32f* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* const pDst[3], int dstStep,
    IppiRect dstROI, double angle, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotate_32f_P4R, (
    const Ipp32f* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* const pDst[4], int dstStep,
    IppiRect dstROI, double angle, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotate_64f_C1R, (
    const Ipp64f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp64f* pDst, int dstStep, IppiRect dstROI,
    double angle, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotate_64f_C3R, (
    const Ipp64f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp64f* pDst, int dstStep, IppiRect dstROI,
    double angle, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotate_64f_C4R, (
    const Ipp64f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp64f* pDst, int dstStep, IppiRect dstROI,
    double angle, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotate_64f_AC4R, (
    const Ipp64f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp64f* pDst, int dstStep, IppiRect dstROI,
    double angle, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotate_64f_P3R, (
    const Ipp64f* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp64f* const pDst[3], int dstStep,
    IppiRect dstROI, double angle, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotate_64f_P4R, (
    const Ipp64f* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp64f* const pDst[4], int dstStep,
    IppiRect dstROI, double angle, double xShift, double yShift, int interpolation))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiRotateCenter
//  Purpose:            Rotates an image about an arbitrary center
//  Parameters:
//    pSrc              Pointer to the source image data (point to pixel (0,0))
//    srcSize           Size of the source image
//    srcStep           Step through the source image
//    srcROI            Region of interest in the source image
//    pDst              Pointer to  the destination image (point to pixel (0,0))
//    dstStep           Step through the destination image
//    dstROI            Region of interest in the destination image
//    angle             The angle of clockwise rotation in degrees
//    xCenter, yCenter  Center of rotation coordinates
//    interpolation     The type of interpolation to perform for rotating the input image:
//                        IPPI_INTER_NN       Nearest neighbor interpolation
//                        IPPI_INTER_LINEAR   Linear interpolation
//                        IPPI_INTER_CUBIC    Cubic convolution interpolation
//                        IPPI_INTER_CUBIC2P_CATMULLROM  Catmull-Rom cubic filter
//                      The special feature in addition to one of general methods:
//                        IPPI_SMOOTH_EDGE    Edges smoothing
//  Returns:
//    ippStsNoErr       OK
//    ippStsNullPtrErr  pSrc or pDst is NULL
//    ippStsSizeErr     One of the image dimensions has zero or negative value
//    ippStsStepErr     srcStep or dstStep has a zero or negative value
//    ippStsInterpolateErr  interpolation has an illegal value
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiRotateCenter_8u_C1R, (
    const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI,
    double angle, double xCenter, double yCenter, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotateCenter_8u_C3R, (
    const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep,
    IppiRect dstROI, double angle, double xCenter, double yCenter, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotateCenter_8u_C4R, (
    const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI,
    double angle, double xCenter, double yCenter, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotateCenter_8u_AC4R, (
    const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI,
    double angle, double xCenter, double yCenter, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotateCenter_8u_P3R, (
    const Ipp8u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* const pDst[3], int dstStep, IppiRect dstROI,
    double angle, double xCenter, double yCenter, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotateCenter_8u_P4R, (
    const Ipp8u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* const pDst[4], int dstStep, IppiRect dstROI,
    double angle, double xCenter, double yCenter, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotateCenter_16u_C1R, (
    const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI,
    double angle, double xCenter, double yCenter, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotateCenter_16u_C3R, (
    const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep,
    IppiRect dstROI, double angle, double xCenter, double yCenter, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotateCenter_16u_C4R, (
    const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI,
    double angle, double xCenter, double yCenter, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotateCenter_16u_AC4R, (
    const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI,
    double angle, double xCenter, double yCenter, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotateCenter_16u_P3R, (
    const Ipp16u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* const pDst[3], int dstStep, IppiRect dstROI,
    double angle, double xCenter, double yCenter, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotateCenter_16u_P4R, (
    const Ipp16u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* const pDst[4], int dstStep, IppiRect dstROI,
    double angle, double xCenter, double yCenter, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotateCenter_32f_C1R, (
    const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI,
    double angle, double xCenter, double yCenter, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotateCenter_32f_C3R, (
    const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep,
    IppiRect dstROI, double angle, double xCenter, double yCenter, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotateCenter_32f_C4R, (
    const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI,
    double angle, double xCenter, double yCenter, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotateCenter_32f_AC4R, (
    const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI,
    double angle, double xCenter, double yCenter, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotateCenter_32f_P3R, (
    const Ipp32f* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* const pDst[3], int dstStep, IppiRect dstROI,
    double angle, double xCenter, double yCenter, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotateCenter_32f_P4R, (
    const Ipp32f* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* const pDst[4], int dstStep, IppiRect dstROI,
    double angle, double xCenter, double yCenter, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotateCenter_64f_C1R, (
    const Ipp64f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp64f* pDst, int dstStep, IppiRect dstROI,
    double angle, double xCenter, double yCenter, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotateCenter_64f_C3R, (
    const Ipp64f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp64f* pDst, int dstStep,
    IppiRect dstROI, double angle, double xCenter, double yCenter, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotateCenter_64f_C4R, (
    const Ipp64f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp64f* pDst, int dstStep, IppiRect dstROI,
    double angle, double xCenter, double yCenter, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotateCenter_64f_AC4R, (
    const Ipp64f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp64f* pDst, int dstStep, IppiRect dstROI,
    double angle, double xCenter, double yCenter, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotateCenter_64f_P3R, (
    const Ipp64f* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp64f* const pDst[3], int dstStep, IppiRect dstROI,
    double angle, double xCenter, double yCenter, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiRotateCenter_64f_P4R, (
    const Ipp64f* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp64f* const pDst[4], int dstStep, IppiRect dstROI,
    double angle, double xCenter, double yCenter, int interpolation))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiAddRotateShift
//  Purpose:            Calculates shifts for ippiRotate function to rotate an image
//                      around the specified center (xCenter, yCenter) with arbitrary shifts
//  Parameters:
//    xCenter, yCenter  Coordinates of the center of rotation
//    angle             The angle of clockwise rotation, degrees
//    xShift, yShift    Pointers to the shift values
//  Returns:
//    ippStsNoErr       OK
//    ippStsNullPtrErr  One of pointers to the output data is NULL
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiAddRotateShift, (
    double xCenter, double yCenter, double angle, double *xShift, double *yShift))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiGetRotateQuad
//  Purpose:            Computes the quadrangle to which the source ROI would be mapped
//  Parameters:
//    srcROI            Source image ROI
//    angle             The angle of rotation in degrees
//    xShift, yShift    The shift along the corresponding axis
//    quad              Output array with vertex coordinates of the quadrangle
//  Returns:
//    ippStsNoErr       OK
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiGetRotateQuad, (
    IppiRect srcROI, double quad[4][2], double angle, double xShift, double yShift))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiGetRotateBound
//  Purpose:            Computes the bounding rectangle for the transformed image ROI
//  Parameters:
//    srcROI            Source image ROI
//    angle             The angle of rotation in degrees
//    xShift, yShift    The shift along the corresponding axis
//    bound             Output array with vertex coordinates of the bounding rectangle
//  Returns:
//    ippStsNoErr       OK
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiGetRotateBound, (
    IppiRect srcROI, double bound[2][2], double angle, double xShift, double yShift))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiShear
//  Purpose:            Performs shear transform of the source image
//                          |X'|   |1  Shx| |X|
//                          |  | = |      |*| |
//                          |Y'|   |Shy  1| |Y|
//  Parameters:
//    pSrc              Pointer to the source image data (point to pixel (0,0))
//    srcSize           Size of the source image
//    srcStep           Step through the source image
//    srcROI            Region of interest in the source image
//    pDst              Pointer to  the destination image (point to pixel (0,0))
//    dstStep           Step through the destination image
//    dstROI            Region of interest in the destination image
//    xShear, yShear    Coefficients of the shearing transform
//    xShif, yShift     The shift along the corresponding axis
//    interpolation     The type of interpolation to perform the input image:
//                        IPPI_INTER_NN       Nearest neighbor interpolation
//                        IPPI_INTER_LINEAR   Linear interpolation
//                        IPPI_INTER_CUBIC    Cubic convolution interpolation
//                        IPPI_INTER_CUBIC2P_CATMULLROM  Catmull-Rom cubic filter
//                      The special feature in addition to one of general methods:
//                        IPPI_SMOOTH_EDGE    Edges smoothing
//  Returns:
//    ippStsNoErr        OK
//    ippStsNullPtrErr   pSrc or pDst is NULL
//    ippStsSizeErr      One of the image dimensions has zero or negative value
//    ippStsStepErr      srcStep or dstStep has a zero or negative value
//    ippStsInterpolateErr  interpolation has an illegal value
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiShear_8u_C1R, (
    const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI,
    double xShear, double yShear, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiShear_8u_C3R, (
    const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI,
    double xShear, double yShear, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiShear_8u_C4R, (
    const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI,
    double xShear, double yShear, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiShear_8u_AC4R, (
    const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI,
    double xShear, double yShear, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiShear_8u_P3R, (
    const Ipp8u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* const pDst[3], int dstStep,
    IppiRect dstROI, double xShear, double yShear, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiShear_8u_P4R, (
    const Ipp8u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* const pDst[4], int dstStep,
    IppiRect dstROI, double xShear, double yShear, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiShear_16u_C1R, (
    const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI,
    double xShear, double yShear, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiShear_16u_C3R, (
    const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI,
    double xShear, double yShear, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiShear_16u_C4R, (
    const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI,
    double xShear, double yShear, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiShear_16u_AC4R, (
    const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI,
    double xShear, double yShear, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiShear_16u_P3R, (
    const Ipp16u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* const pDst[3], int dstStep,
    IppiRect dstROI, double xShear, double yShear, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiShear_16u_P4R, (
    const Ipp16u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* const pDst[4], int dstStep,
    IppiRect dstROI, double xShear, double yShear, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiShear_32f_C1R, (
    const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI,
    double xShear, double yShear, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiShear_32f_C3R, (
    const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI,
    double xShear, double yShear, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiShear_32f_C4R, (
    const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI,
    double xShear, double yShear, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiShear_32f_AC4R, (
    const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI,
    double xShear, double yShear, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiShear_32f_P3R, (
    const Ipp32f* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* const pDst[3], int dstStep,
    IppiRect dstROI, double xShear, double yShear, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiShear_32f_P4R, (
    const Ipp32f* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* const pDst[4], int dstStep,
    IppiRect dstROI, double xShear, double yShear, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiShear_64f_C1R, (
    const Ipp64f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp64f* pDst, int dstStep, IppiRect dstROI,
    double xShear, double yShear, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiShear_64f_C3R, (
    const Ipp64f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp64f* pDst, int dstStep, IppiRect dstROI,
    double xShear, double yShear, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiShear_64f_C4R, (
    const Ipp64f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp64f* pDst, int dstStep, IppiRect dstROI,
    double xShear, double yShear, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiShear_64f_AC4R, (
    const Ipp64f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp64f* pDst, int dstStep, IppiRect dstROI,
    double xShear, double yShear, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiShear_64f_P3R, (
    const Ipp64f* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp64f* const pDst[3], int dstStep,
    IppiRect dstROI, double xShear, double yShear, double xShift, double yShift, int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiShear_64f_P4R, (
    const Ipp64f* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp64f* const pDst[4], int dstStep,
    IppiRect dstROI, double xShear, double yShear, double xShift, double yShift, int interpolation))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiGetShearQuad
//  Purpose:            Computes the quadrangle to which the source ROI would be mapped
//  Parameters:
//    srcROI            Source image ROI
//    xShear, yShear    The coefficients of the shear transform
//    xShift, yShift    The shift along the corresponding axis
//    quad              Output array with vertex coordinates of the quadrangle
//  Returns:
//    ippStsNoErr       OK
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiGetShearQuad, (
    IppiRect srcROI, double quad[4][2], double xShear, double yShear, double xShift, double yShift))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiGetShearBound
//  Purpose:            Computes the bounding rectangle for the transformed image ROI
//  Parameters:
//    srcROI            Source image ROI
//    xShear, yShear    The coefficients of the shear transform
//    xShift, yShift    The shift along the corresponding axis
//    bound             Output array with vertex coordinates of the bounding rectangle
//  Returns:
//    ippStsNoErr       OK
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiGetShearBound, (
    IppiRect srcROI, double bound[2][2], double xShear, double yShear, double xShift, double yShift))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiWarpPerspective
//  Purpose:   Performs perspective warping of an image
//                     a11*j + a12*i + a13
//                 x = -------------------
//                     a31*j + a32*i + a33
//
//                     a21*j + a22*i + a23
//                 y = -------------------
//                     a31*j + a32*i + a33
//  Context:
//  Returns:        IppStatus
//    ippStsNoErr           OK
//    ippStsNullPtrErr      pSrc or pDst is NULL
//    ippStsSizeErr         One of the image dimensions has zero or negative value
//    ippStsStepErr         srcStep or dstStep has a zero or negative value
//    ippStsInterpolateErr  interpolation has an illegal value
//  Parameters:
//      pSrc        Pointer to the source image data (point to pixel (0,0))
//      srcSize     Size of the source image
//      srcStep     Step through the source image
//      srcROI      Region of interest in the source image
//      pDst        Pointer to  the destination image (point to pixel (0,0))
//      dstStep     Step through the destination image
//      dstROI      Region of interest in the destination image
//      coeffs      The perspective transform matrix
//      interpolation  The type of interpolation to perform for resampling
//                  the input image. Possible values:
//                  IPPI_INTER_NN       Nearest neighbor interpolation
//                  IPPI_INTER_LINEAR   Linear interpolation
//                  IPPI_INTER_CUBIC    Cubic convolution interpolation
//                  IPPI_SMOOTH_EDGE    Edges smoothing in addition to one of the
//                                      above methods
//  Notes:
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspective_8u_C1R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspective_8u_C3R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspective_8u_AC4R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspective_8u_P3R, (const Ipp8u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* const pDst[3], int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspective_8u_C4R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspective_8u_P4R, (const Ipp8u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* const pDst[4], int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspective_32f_C1R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspective_32f_C3R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspective_32f_AC4R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspective_32f_P3R, (const Ipp32f* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* const pDst[3], int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspective_32f_C4R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspective_32f_P4R, (const Ipp32f* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* const pDst[4], int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspective_16u_C1R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspective_16u_C3R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspective_16u_AC4R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspective_16u_P3R, (const Ipp16u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* const pDst[3], int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspective_16u_C4R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspective_16u_P4R, (const Ipp16u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* const pDst[4], int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiWarpPerspectiveBack
//  Purpose:   Performs an inverse perspective warping of an image
//                     a11*j + a12*i + a13
//                 x = -------------------
//                     a31*j + a32*i + a33
//
//                     a21*j + a22*i + a23
//                 y = -------------------
//                     a31*j + a32*i + a33
//  Context:
//  Returns:        IppStatus
//    ippStsNoErr           OK
//    ippStsNullPtrErr      pSrc or pDst is NULL
//    ippStsSizeErr         One of the image dimensions has zero or negative value
//    ippStsStepErr         srcStep or dstStep has a zero or negative value
//    ippStsInterpolateErr  interpolation has an illegal value
//  Parameters:
//      pSrc        Pointer to the source image data (point to pixel (0,0))
//      srcSize     Size of the source image
//      srcStep     Step through the source image
//      srcROI      Region of interest in the source image
//      pDst        Pointer to  the destination image (point to pixel (0,0))
//      dstStep     Step through the destination image
//      dstROI      Region of interest in the destination image
//      coeffs      The perspective transform matrix
//      interpolation  The type of interpolation to perform for resampling
//                  the input image. Possible values:
//                  IPPI_INTER_NN       Nearest neighbor interpolation
//                  IPPI_INTER_LINEAR   Linear interpolation
//                  IPPI_INTER_CUBIC    Cubic convolution interpolation
//  Notes:
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveBack_8u_C1R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveBack_8u_C3R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveBack_8u_AC4R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveBack_8u_P3R, (const Ipp8u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* const pDst[3], int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveBack_8u_C4R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveBack_8u_P4R, (const Ipp8u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* const pDst[4], int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveBack_32f_C1R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveBack_32f_C3R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveBack_32f_AC4R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveBack_32f_P3R, (const Ipp32f* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* const pDst[3], int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveBack_32f_C4R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveBack_32f_P4R, (const Ipp32f* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* const pDst[4], int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveBack_16u_C1R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveBack_16u_C3R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveBack_16u_AC4R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveBack_16u_P3R, (const Ipp16u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* const pDst[3], int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveBack_16u_C4R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveBack_16u_P4R, (const Ipp16u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* const pDst[4], int dstStep, IppiRect dstROI, const double coeffs[3][3], int interpolation))

/* ///////////////////////////////////////////////////////////////////////////////
//  Name:           ippiWarpPerspectiveQuad
//  Purpose:  Performs perspective warping of an arbitrary quadrangle in the source
//            image to the quadrangle in the destination image
//                     a11*j + a12*i + a13
//                 x = -------------------
//                     a31*j + a32*i + a33
//
//                     a21*j + a22*i + a23
//                 y = -------------------
//                     a31*j + a32*i + a33
//  Context:
//    ippStsNoErr           OK
//    ippStsNullPtrErr      pSrc or pDst is NULL
//    ippStsSizeErr         One of the image dimensions has zero or negative value
//    ippStsStepErr         srcStep or dstStep has a zero or negative value
//    ippStsInterpolateErr  interpolation has an illegal value
//  Parameters:
//      pSrc        Pointer to the source image data (point to the pixel (0,0))
//      srcSize     Size of the source image
//      srcStep     Step through the source image
//      srcROI      Region of interest in the source image
//      srcQuad     Vertex coordinates of a given quadrangle in the source image
//      pDst        Pointer to  the destination image (point to the pixel (0,0))
//      dstStep     Step through the destination image
//      dstROI      Region of interest in the destination image
//      dstQuad     Vertex coordinates of the given quadrangle in the destination image
//      interpolation  The type of interpolation to perform for resampling
//                  the input image. Possible values:
//                  IPPI_INTER_NN       Nearest neighbor interpolation
//                  IPPI_INTER_LINEAR   Linear interpolation
//                  IPPI_INTER_CUBIC    Cubic convolution interpolation
//  Notes:
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveQuad_8u_C1R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp8u* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveQuad_8u_C3R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp8u* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveQuad_8u_AC4R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp8u* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveQuad_8u_P3R, (const Ipp8u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp8u* const pDst[3], int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveQuad_8u_C4R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp8u* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveQuad_8u_P4R, (const Ipp8u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp8u* const pDst[4], int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveQuad_32f_C1R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp32f* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveQuad_32f_C3R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp32f* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveQuad_32f_AC4R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp32f* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveQuad_32f_P3R, (const Ipp32f* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp32f* const pDst[3], int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveQuad_32f_C4R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp32f* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveQuad_32f_P4R, (const Ipp32f* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp32f* const pDst[4], int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveQuad_16u_C1R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp16u* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveQuad_16u_C3R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp16u* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveQuad_16u_AC4R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp16u* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveQuad_16u_P3R, (const Ipp16u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp16u* const pDst[3], int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveQuad_16u_C4R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp16u* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpPerspectiveQuad_16u_P4R, (const Ipp16u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp16u* const pDst[4], int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiWarpBilinear
//  Purpose:  Performs bilinear warping of an image
//                  |X|   |a11|      |a12 a13| |J|   |a14|
//                  | | = |   |*JI + |       |*| | + |   |
//                  |Y|   |a21|      |a22 a23| |I|   |a24|
//  Context:
//    ippStsNoErr           OK
//    ippStsNullPtrErr      pSrc or pDst is NULL
//    ippStsSizeErr         One of the image dimensions has zero or negative value
//    ippStsStepErr         srcStep or dstStep has a zero or negative value
//    ippStsInterpolateErr  interpolation has an illegal value
//  Parameters:
//      pSrc        Pointer to the source image data (point to pixel (0,0))
//      srcSize     Size of the source image
//      srcStep     Step through the source image
//      srcROI      Region of interest in the source image
//      pDst        Pointer to  the destination image (point to pixel (0,0))
//      dstStep     Step through the destination image
//      dstROI      Region of interest in the destination image
//      coeffs      The bilinear transform matrix
//      interpolation  The type of interpolation to perform for resampling
//                  the input image. Possible values:
//                  IPPI_INTER_NN       Nearest neighbor interpolation
//                  IPPI_INTER_LINEAR   Linear interpolation
//                  IPPI_INTER_CUBIC    Cubic convolution interpolation
//                  IPPI_SMOOTH_EDGE    Edges smoothing in addition to one of the
//                                      above methods
//  Notes:
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinear_8u_AC4R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinear_8u_P3R, (const Ipp8u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* const pDst[3], int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinear_8u_P4R, (const Ipp8u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* const pDst[4], int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinear_32f_AC4R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinear_32f_P3R, (const Ipp32f* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* const pDst[3], int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinear_32f_P4R, (const Ipp32f* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* const pDst[4], int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinear_16u_AC4R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinear_16u_P3R, (const Ipp16u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* const pDst[3], int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinear_16u_P4R, (const Ipp16u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* const pDst[4], int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiWarpBilinearBack
//  Purpose:  Performs an inverse bilinear warping of an image
//                  |X|   |a11|      |a12 a13| |J|   |a14|
//                  | | = |   |*JI + |       |*| | + |   |
//                  |Y|   |a21|      |a22 a23| |I|   |a24|
//  Context:
//    ippStsNoErr           OK
//    ippStsNullPtrErr      pSrc or pDst is NULL
//    ippStsSizeErr         One of the image dimensions has zero or negative value
//    ippStsStepErr         srcStep or dstStep has a zero or negative value
//    ippStsInterpolateErr  interpolation has an illegal value
//  Parameters:
//      pSrc        Pointer to the source image data (point to pixel (0,0))
//      srcSize     Size of the source image
//      srcStep     Step through the source image
//      srcROI      Region of interest in the source image
//      pDst        Pointer to  the destination image (point to pixel (0,0))
//      dstStep     Step through the destination image
//      dstROI      Region of interest in the destination image
//      coeffs      The bilinear transform matrix
//      interpolation  The type of interpolation to perform for resampling
//                     the input image. Possible values:
//                  IPPI_INTER_NN       Nearest neighbor interpolation
//                  IPPI_INTER_LINEAR   Linear interpolation
//                  IPPI_INTER_CUBIC    Cubic convolution interpolation
//  Notes:
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinearBack_8u_AC4R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinearBack_8u_P3R, (const Ipp8u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* const pDst[3], int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinearBack_8u_P4R, (const Ipp8u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* const pDst[4], int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinearBack_32f_AC4R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinearBack_32f_P3R, (const Ipp32f* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* const pDst[3], int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinearBack_32f_P4R, (const Ipp32f* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* const pDst[4], int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinearBack_16u_AC4R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinearBack_16u_P3R, (const Ipp16u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* const pDst[3], int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinearBack_16u_P4R, (const Ipp16u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* const pDst[4], int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiWarpBilinearQuad
//  Purpose:  Performs bilinear warping of an arbitrary quadrangle in the source
//            image to the quadrangle in the destination image
//                  |X|   |a11|      |a12 a13| |J|   |a14|
//                  | | = |   |*JI + |       |*| | + |   |
//                  |Y|   |a21|      |a22 a23| |I|   |a24|
//  Context:
//    ippStsNoErr           OK
//    ippStsNullPtrErr      pSrc or pDst is NULL
//    ippStsSizeErr         One of the image dimensions has zero or negative value
//    ippStsStepErr         srcStep or dstStep has a zero or negative value
//    ippStsInterpolateErr  interpolation has an illegal value
//  Parameters:
//      pSrc        Pointer to the source image data (point to pixel (0,0))
//      srcSize     Size of the source image
//      srcStep     Step through the source image
//      srcROI      Region of interest in the source image
//      srcQuad     A given quadrangle in the source image
//      pDst        Pointer to  the destination image (point to pixel (0,0))
//      dstStep     Step through the destination image
//      dstROI      Region of interest in the destination image
//      dstQuad     A given quadrangle in the destination image
//      interpolation  The type of interpolation to perform for resampling
//                  the input image. Possible values:
//                  IPPI_INTER_NN       Nearest neighbor interpolation
//                  IPPI_INTER_LINEAR   Linear interpolation
//                  IPPI_INTER_CUBIC    Cubic convolution interpolation
//                  IPPI_SMOOTH_EDGE    Edges smoothing in addition to one of the
//                                      above methods
//  Notes:
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinearQuad_8u_AC4R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp8u* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinearQuad_8u_P3R, (const Ipp8u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp8u* const pDst[3], int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinearQuad_8u_P4R, (const Ipp8u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp8u* const pDst[4], int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinearQuad_32f_AC4R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp32f* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinearQuad_32f_P3R, (const Ipp32f* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp32f* const pDst[3], int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinearQuad_32f_P4R, (const Ipp32f* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp32f* const pDst[4], int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinearQuad_16u_AC4R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp16u* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinearQuad_16u_P3R, (const Ipp16u* const pSrc[3], IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp16u* const pDst[3], int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))
LEGACY90IPPAPI(IppStatus, legacy90ippiWarpBilinearQuad_16u_P4R, (const Ipp16u* const pSrc[4], IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp16u* const pDst[4], int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation))



/* /////////////////////////////////////////////////////////////////////////////
//                   Statistic functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiMomentInitAlloc()
//
//  Purpose:   Allocates memory and initializes MomentState structure
//
//  Returns:
//    ippStsMemAllocErr Memory allocation failure
//    ippStsNoErr       No errors
//
//  Parameters:
//    hint     Option to specify the computation algorithm
//    pState   Pointer to the MomentState structure
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiMomentInitAlloc_64s, (IppiMomentState_64s** pState, IppHintAlgorithm hint))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiMomentFree()
//
//  Purpose:   Deallocates the MomentState structure
//
//  Returns:
//    ippStsNullPtrErr       pState==NULL
//    ippStsContextMatchErr  pState->idCtx != idCtxMoment
//    ippStsNoErr            No errors
//
//  Parameters:
//    pState   Pointer to the MomentState structure
//
*/
LEGACY90IPPAPI (IppStatus, legacy90ippiMomentFree_64s, (IppiMomentState_64s* pState))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiMomentGetStateSize_64s
//             ippiMomentGetStateSize_64f
//
//  Purpose:   Computes the size of the external buffer for the state
//             structure ippiMomentsState_64s in bytes
//
//  Returns:
//    ippStsNoErr         OK
//    ippStsNullPtrErr    pSize==NULL
//  Parameters:
//    hint                Option to specify the computation algorithm
//    pSize               Pointer to the value of the buffer size
//                        of the structure ippiMomentState_64s.
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiMomentGetStateSize_64s, (IppHintAlgorithm hint, int * pSize))


/* ////////////////////////////////////////////////////////////////////////////////////
//  Name:           ippiMomentInit64s
//                  ippiMomentInit64f
//
//  Purpose:        Initializes ippiMomentState_64s structure (without memory allocation)
//
//  Returns:
//    ippStsNoErr   No errors
//
//  Parameters:
//    pState        Pointer to the MomentState structure
//    hint          Option to specify the computation algorithm
*/
LEGACY90IPPAPI (IppStatus, legacy90ippiMomentInit_64s, (IppiMomentState_64s* pState, IppHintAlgorithm hint))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiMoments
//
//  Purpose:   Computes statistical moments of an image
//
//  Returns:
//    ippStsContextMatchErr   pState->idCtx != idCtxMoment
//    ippStsNullPtrErr        (pSrc == NULL) or (pState == NULL)
//    ippStsStepErr           pSrcStep <0
//    ippStsSizeErr           (roiSize.width  <1) or (roiSize.height <1)
//    ippStsNoErr             No errors
//
//  Parameters:
//    pSrc     Pointer to the source image
//    srcStep  Step in bytes through the source image
//    roiSize  Size of the source ROI
//    pState   Pointer to the MomentState structure
//
//  Notes:
//    These functions compute moments of order 0 to 3 only
//
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiMoments64s_8u_C1R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, IppiMomentState_64s* pCtx))
LEGACY90IPPAPI(IppStatus, legacy90ippiMoments64s_8u_C3R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, IppiMomentState_64s* pCtx))
LEGACY90IPPAPI(IppStatus, legacy90ippiMoments64s_8u_AC4R,(const Ipp8u* pSrc, int srcStep, IppiSize roiSize, IppiMomentState_64s* pCtx))

LEGACY90IPPAPI(IppStatus, legacy90ippiMoments64s_16u_C1R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, IppiMomentState_64s* pCtx))
LEGACY90IPPAPI(IppStatus, legacy90ippiMoments64s_16u_C3R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, IppiMomentState_64s* pCtx))
LEGACY90IPPAPI(IppStatus, legacy90ippiMoments64s_16u_AC4R,(const Ipp16u* pSrc, int srcStep, IppiSize roiSize, IppiMomentState_64s* pCtx))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiGetSpatialMoment()
//             ippiGetCentralMoment()
//
//  Purpose:   Retrieves the value of the image spatial/central moment.
//
//  Returns:
//    ippStsNullPtrErr      (pState == NULL) or (pValue == NULL)
//    ippStsContextMatchErr pState->idCtx != idCtxMoment
//    ippStsSizeErr         (mOrd+nOrd) >3 or
//                          (nChannel<0) or (nChannel>=pState->nChannelInUse)
//    ippStsNoErr           No errors
//
//  Parameters:
//    pState      Pointer to the MomentState structure
//    mOrd        m- Order (X direction)
//    nOrd        n- Order (Y direction)
//    nChannel    Channel number
//    roiOffset   Offset of the ROI origin (ippiGetSpatialMoment ONLY!)
//    pValue      Pointer to the retrieved moment value
//    scaleFactor Factor to scale the moment value (for integer data)
//
//  NOTE:
//    ippiGetSpatialMoment uses Absolute Coordinates (left-top image has 0,0).
//
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiGetSpatialMoment_64s,(const IppiMomentState_64s* pState,
                                       int mOrd, int nOrd, int nChannel,
                                       IppiPoint roiOffset, Ipp64s* pValue, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiGetCentralMoment_64s,(const IppiMomentState_64s* pState,
                                       int mOrd, int nOrd, int nChannel,
                                       Ipp64s* pValue, int scaleFactor))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiGetNormalizedSpatialMoment()
//             ippiGetNormalizedCentralMoment()
//
//  Purpose:   Retrieves the normalized value of the image spatial/central moment.
//
//  Returns:
//    ippStsNullPtrErr      (pState == NULL) or (pValue == NULL)
//    ippStsContextMatchErr pState->idCtx != idCtxMoment
//    ippStsSizeErr         (mOrd+nOrd) >3 or
//                          (nChannel<0) or (nChannel>=pState->nChannelInUse)
//    ippStsMoment00ZeroErr mm[0][0] < IPP_EPS52
//    ippStsNoErr           No errors
//
//  Parameters:
//    pState      Pointer to the MomentState structure
//    mOrd        m- Order (X direction)
//    nOrd        n- Order (Y direction)
//    nChannel    Channel number
//    roiOffset   Offset of the ROI origin (ippiGetSpatialMoment ONLY!)
//    pValue      Pointer to the normalized moment value
//    scaleFactor Factor to scale the moment value (for integer data)
//
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiGetNormalizedSpatialMoment_64s,(const IppiMomentState_64s* pState,
                                   int mOrd, int nOrd, int nChannel,
                                   IppiPoint roiOffset, Ipp64s* pValue, int scaleFactor))
LEGACY90IPPAPI(IppStatus, legacy90ippiGetNormalizedCentralMoment_64s,(const IppiMomentState_64s* pState,
                                   int mOrd, int nOrd, int nChannel,
                                   Ipp64s* pValue, int scaleFactor))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiGetHuMoments()
//
//  Purpose:   Retrieves image Hu moment invariants.
//
//  Returns:
//    ippStsNullPtrErr      (pState == NULL) or (pHu == NULL)
//    ippStsContextMatchErr pState->idCtx != idCtxMoment
//    ippStsSizeErr         (nChannel<0) or (nChannel>=pState->nChannelInUse)
//    ippStsMoment00ZeroErr mm[0][0] < IPP_EPS52
//    ippStsNoErr           No errors
//
//  Parameters:
//    pState      Pointer to the MomentState structure
//    nChannel    Channel number
//    pHm         Pointer to the array of the Hu moment invariants
//    scaleFactor Factor to scale the moment value (for integer data)
//
//  Notes:
//    We consider Hu moments up to the 7-th order only
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiGetHuMoments_64s,(const IppiMomentState_64s* pState,
                                   int nChannel, IppiHuMoment_64s pHm, int scaleFactor))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiNorm_Inf
//  Purpose:        computes the C-norm of pixel values of the image: n = MAX |src1|
//  Context:
//  Returns:        IppStatus
//    ippStsNoErr        OK
//    ippStsNullPtrErr   One of the pointers is NULL
//    ippStsSizeErr      roiSize has a field with zero or negative value
//  Parameters:
//    pSrc        Pointer to the source image.
//    srcStep     Step through the source image
//    roiSize     Size of the source ROI.
//    pValue      Pointer to the computed norm (one-channel data)
//    value       Array of the computed norms for each channel (multi-channel data)
//  Notes:
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiNorm_Inf_8u_AC4R, (const Ipp8u* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNorm_Inf_16s_AC4R, (const Ipp16s* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNorm_Inf_16u_AC4R, (const Ipp16u* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNorm_Inf_32s_C1R, (const Ipp32s* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f* value))

LEGACY90IPPAPI(IppStatus, legacy90ippiNorm_Inf_32f_AC4R, (const Ipp32f* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f value[3]))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiNorm_L1
//  Purpose:        computes the L1-norm of pixel values of the image: n = SUM |src1|
//  Context:
//  Returns:        IppStatus
//    ippStsNoErr        OK
//    ippStsNullPtrErr   One of the pointers is NULL
//    ippStsSizeErr      roiSize has a field with zero or negative value
//  Parameters:
//    pSrc        Pointer to the source image.
//    srcStep     Step through the source image
//    roiSize     Size of the source ROI.
//    pValue      Pointer to the computed norm (one-channel data)
//    value       Array of the computed norms for each channel (multi-channel data)
//    hint        Option to specify the computation algorithm
//  Notes:
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiNorm_L1_8u_AC4R, (const Ipp8u* pSrc, int srcStep,
                                       IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNorm_L1_16s_AC4R, (const Ipp16s* pSrc, int srcStep,
                                       IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNorm_L1_16u_AC4R, (const Ipp16u* pSrc, int srcStep,
                                       IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNorm_L1_32f_AC4R, (const Ipp32f* pSrc, int srcStep,
                                       IppiSize roiSize, Ipp64f value[3], IppHintAlgorithm hint))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiNorm_L2
//  Purpose:        computes the L2-norm of pixel values of the image: n = SQRT(SUM |src1|^2)
//  Context:
//  Returns:        IppStatus
//    ippStsNoErr        OK
//    ippStsNullPtrErr   One of the pointers is NULL
//    ippStsSizeErr      roiSize has a field with zero or negative value
//  Parameters:
//    pSrc        Pointer to the source image.
//    srcStep     Step through the source image
//    roiSize     Size of the source ROI.
//    pValue      Pointer to the computed norm (one-channel data)
//    value       Array of the computed norms for each channel (multi-channel data)
//    hint        Option to specify the computation algorithm
//  Notes:
//    simple mul is better than table for P6 family
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiNorm_L2_8u_AC4R, (const Ipp8u* pSrc, int srcStep,
                                       IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNorm_L2_16s_AC4R, (const Ipp16s* pSrc, int srcStep,
                                       IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNorm_L2_16u_AC4R, (const Ipp16u* pSrc, int srcStep,
                                       IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNorm_L2_32f_AC4R, (const Ipp32f* pSrc, int srcStep,
                                       IppiSize roiSize, Ipp64f value[3], IppHintAlgorithm hint))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiNormDiff_Inf
//  Purpose:        computes the C-norm of pixel values of two images: n = MAX |src1 - src2|
//  Context:
//  Returns:        IppStatus
//    ippStsNoErr         OK
//    ippStsNullPtrErr    One of the pointers is NULL
//    ippStsSizeErr       roiSize has a field with zero or negative value
//  Parameters:
//    pSrc1, pSrc2        Pointers to the source images.
//    src1Step, src2Step  Steps in bytes through the source images
//    roiSize             Size of the source ROI.
//    pValue              Pointer to the computed norm (one-channel data)
//    value               Array of the computed norms for each channel (multi-channel data)
//  Notes:
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiNormDiff_Inf_8u_AC4R, (const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNormDiff_Inf_16s_AC4R, (const Ipp16s* pSrc1, int src1Step,
                                        const Ipp16s* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNormDiff_Inf_16u_AC4R, (const Ipp16u* pSrc1, int src1Step,
                                        const Ipp16u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNormDiff_Inf_32f_AC4R, (const Ipp32f* pSrc1, int src1Step,
                                        const Ipp32f* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiNormDiff_L1
//  Purpose:        computes the L1-norm of pixel values of two images: n = SUM |src1 - src2|
//  Context:
//  Returns:        IppStatus
//    ippStsNoErr         OK
//    ippStsNullPtrErr    One of the pointers is NULL
//    ippStsSizeErr       roiSize has a field with zero or negative value
//  Parameters:
//    pSrc1, pSrc2        Pointers to the source images.
//    src1Step, src2Step  Steps in bytes through the source images
//    roiSize             Size of the source ROI.
//    pValue              Pointer to the computed norm (one-channel data)
//    value               Array of the computed norms for each channel (multi-channel data)
//    hint                Option to specify the computation algorithm
//  Notes:
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiNormDiff_L1_8u_AC4R, (const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNormDiff_L1_16s_AC4R, (const Ipp16s* pSrc1, int src1Step,
                                        const Ipp16s* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNormDiff_L1_16u_AC4R, (const Ipp16u* pSrc1, int src1Step,
                                        const Ipp16u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNormDiff_L1_32f_AC4R, (const Ipp32f* pSrc1, int src1Step,
                                        const Ipp32f* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3], IppHintAlgorithm hint))


/* /////////////////////////////////////////////////////////////////////////////////
//  Name:           ippiNormDiff_L2
//  Purpose:        computes the L2-norm of pixel values of two images:
//                    n = SQRT(SUM |src1 - src2|^2)
//  Context:
//  Returns:        IppStatus
//    ippStsNoErr         OK
//    ippStsNullPtrErr    One of the pointers is NULL
//    ippStsSizeErr       roiSize has a field with zero or negative value
//  Parameters:
//    pSrc1, pSrc2        Pointers to the source images.
//    src1Step, src2Step  Steps in bytes through the source images
//    roiSize             Size of the source ROI.
//    pValue              Pointer to the computed norm (one-channel data)
//    value               Array of the computed norms for each channel (multi-channel data)
//    hint                Option to specify the computation algorithm
//  Notes:
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiNormDiff_L2_8u_AC4R, (const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNormDiff_L2_16s_AC4R, (const Ipp16s* pSrc1, int src1Step,
                                        const Ipp16s* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNormDiff_L2_16u_AC4R, (const Ipp16u* pSrc1, int src1Step,
                                        const Ipp16u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNormDiff_L2_32f_AC4R, (const Ipp32f* pSrc1, int src1Step,
                                        const Ipp32f* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3], IppHintAlgorithm hint))


/* //////////////////////////////////////////////////////////////////////////////////////////
//  Name:           ippiNormRel_Inf
//  Purpose:        computes the relative error for the C-norm of pixel values of two images:
//                      n = MAX |src1 - src2| / MAX |src2|
//  Context:
//  Returns:        IppStatus
//    ippStsNoErr         OK
//    ippStsNullPtrErr    One of the pointers is NULL
//    ippStsSizeErr       roiSize has a field with zero or negative value
//    ippStsDivByZero     MAX |src2| == 0
//  Parameters:
//    pSrc1, pSrc2        Pointers to the source images.
//    src1Step, src2Step  Steps in bytes through the source images
//    roiSize             Size of the source ROI.
//    pValue              Pointer to the computed norm (one-channel data)
//    value               Array of the computed norms for each channel (multi-channel data)
//  Notes:
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiNormRel_Inf_8u_AC4R, (const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNormRel_Inf_16s_AC4R, (const Ipp16s* pSrc1, int src1Step,
                                        const Ipp16s* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNormRel_Inf_16u_AC4R, (const Ipp16u* pSrc1, int src1Step,
                                        const Ipp16u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNormRel_Inf_32f_AC4R, (const Ipp32f* pSrc1, int src1Step,
                                        const Ipp32f* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))


/* /////////////////////////////////////////////////////////////////////////////////////////
//  Name:           ippiNormRel_L1
//  Purpose:        computes the relative error for the 1-norm of pixel values of two images:
//                      n = SUM |src1 - src2| / SUM |src2|
//  Context:
//  Returns:        IppStatus
//    ippStsNoErr         OK
//    ippStsNullPtrErr    One of the pointers is NULL
//    ippStsSizeErr       roiSize has a field with zero or negative value
//    ippStsDivByZero     SUM |src2| == 0
//  Parameters:
//    pSrc1, pSrc2        Pointers to the source images.
//    src1Step, src2Step  Steps in bytes through the source images
//    roiSize             Size of the source ROI.
//    pValue              Pointer to the computed norm (one-channel data)
//    value               Array of the computed norms for each channel (multi-channel data)
//    hint                Option to specify the computation algorithm
//  Notes:
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiNormRel_L1_8u_AC4R, (const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNormRel_L1_16s_AC4R, (const Ipp16s* pSrc1, int src1Step,
                                        const Ipp16s* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNormRel_L1_16u_AC4R, (const Ipp16u* pSrc1, int src1Step,
                                        const Ipp16u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNormRel_L1_32f_AC4R, (const Ipp32f* pSrc1, int src1Step,
                                        const Ipp32f* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3], IppHintAlgorithm hint))


/* //////////////////////////////////////////////////////////////////////////////////////////
//  Name:           ippiNormRel_L2
//  Purpose:        computes the relative error for the L2-norm of pixel values of two images:
//                      n = SQRT(SUM |src1 - src2|^2 / SUM |src2|^2)
//  Context:
//  Returns:        IppStatus
//    ippStsNoErr         OK
//    ippStsNullPtrErr    One of the pointers is NULL
//    ippStsSizeErr       roiSize has a field with zero or negative value
//    ippStsDivByZero     SUM |src2|^2 == 0
//  Parameters:
//    pSrc1, pSrc2        Pointers to the source images.
//    src1Step, src2Step  Steps in bytes through the source images
//    roiSize             Size of the source ROI.
//    pValue              Pointer to the computed norm (one-channel data)
//    value               Array of the computed norms for each channel (multi-channel data)
//    hint                Option to specify the computation algorithm
//  Notes:
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiNormRel_L2_8u_AC4R, (const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNormRel_L2_16s_AC4R, (const Ipp16s* pSrc1, int src1Step,
                                        const Ipp16s* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNormRel_L2_16u_AC4R, (const Ipp16u* pSrc1, int src1Step,
                                        const Ipp16u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiNormRel_L2_32f_AC4R, (const Ipp32f* pSrc1, int src1Step,
                                        const Ipp32f* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3], IppHintAlgorithm hint))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiSum
//  Purpose:        computes the sum of image pixel values
//  Context:
//  Returns:        IppStatus
//    ippStsNoErr        OK
//    ippStsNullPtrErr   One of the pointers is NULL
//    ippStsSizeErr      roiSize has a field with zero or negative value
//  Parameters:
//    pSrc        Pointer to the source image.
//    srcStep     Step in bytes through the source image
//    roiSize     Size of the source image ROI.
//    pSum        Pointer to the result (one-channel data)
//    sum         Array containing the results (multi-channel data)
//    hint        Option to select the algorithmic implementation of the function
//  Notes:
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiSum_8u_AC4R, (const Ipp8u* pSrc, int srcStep,
                                    IppiSize roiSize, Ipp64f sum[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiSum_16s_AC4R, (const Ipp16s* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f sum[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiSum_16u_AC4R, (const Ipp16u* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f sum[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiSum_32f_AC4R, (const Ipp32f* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f sum[3], IppHintAlgorithm hint))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiMean
//  Purpose:        computes the mean of image pixel values
//  Context:
//  Returns:        IppStatus
//    ippStsNoErr        OK
//    ippStsNullPtrErr   One of the pointers is NULL
//    ippStsSizeErr      roiSize has a field with zero or negative value.
//  Parameters:
//    pSrc        Pointer to the source image.
//    srcStep     Step in bytes through the source image
//    roiSize     Size of the source ROI.
//    pMean       Pointer to the result (one-channel data)
//    mean        Array containing the results (multi-channel data)
//    hint        Option to select the algorithmic implementation of the function
//  Notes:
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiMean_8u_AC4R, (const Ipp8u* pSrc, int srcStep,
                                    IppiSize roiSize, Ipp64f mean[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiMean_16s_AC4R, (const Ipp16s* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f mean[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiMean_16u_AC4R, (const Ipp16u* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f mean[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiMean_32f_AC4R, (const Ipp32f* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f mean[3], IppHintAlgorithm hint))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiHistogramRange
//  Purpose:        computes the intensity histogram of an image
//  Context:
//  Returns:        IppStatus
//    ippStsNoErr           OK
//    ippStsNullPtrErr      One of the pointers is NULL
//    ippStsSizeErr         roiSize has a field with zero or negative value
//    ippStsMemAllocErr     There is not enough memory for the inner histogram
//    ippStsHistoNofLevelsErr  Number of levels is less than 2
//  Parameters:
//    pSrc        Pointer to the source image.
//    srcStep     Step in bytes through the source image
//    roiSize     Size of the source ROI.
//    pHist       Pointer to the computed histogram.
//    pLevels     Pointer to the array of level values.
//    nLevels     Number of levels
//  Notes:
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramRange_8u_C1R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist, const Ipp32s* pLevels, int nLevels))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramRange_8u_C3R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramRange_8u_AC4R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramRange_8u_C4R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist[4],  const Ipp32s* pLevels[4], int nLevels[4]))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramRange_16s_C1R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist, const Ipp32s* pLevels, int nLevels))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramRange_16s_C3R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist[3],const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramRange_16s_AC4R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist[3],const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramRange_16s_C4R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist[4],const Ipp32s* pLevels[4], int nLevels[4]))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramRange_16u_C1R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist, const Ipp32s* pLevels, int nLevels))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramRange_16u_C3R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist[3],const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramRange_16u_AC4R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist[3],const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramRange_16u_C4R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist[4],const Ipp32s* pLevels[4], int nLevels[4]))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramRange_32f_C1R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist, const Ipp32f* pLevels, int nLevels))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramRange_32f_C3R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist[3],  const Ipp32f* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramRange_32f_AC4R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist[3], const Ipp32f* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramRange_32f_C4R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist[4],  const Ipp32f* pLevels[4], int nLevels[4]))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiHistogramEven
//  Purpose:        Computes the intensity histogram of an image
//                  using equal bins - even histogram
//  Context:
//  Returns:        IppStatus
//    ippStsNoErr        OK
//    ippStsNullPtrErr   One of the pointers is NULL
//    ippStsSizeErr      roiSize has a field with zero or negative value
//    ippStsMemAllocErr  There is not enough memory for the inner histogram
//    ippStsHistoNofLevelsErr Number of levels is less 2
//  Parameters:
//    pSrc        Pointer to the source image.
//    srcStep     Step in bytes through the source image
//    roiSize     Size of the source ROI.
//    pHist       Pointer to the computed histogram.
//    pLevels     Pointer to the array of level values.
//    nLevels     Number of levels
//    lowerLevel  Lower level boundary
//    upperLevel  Upper level boundary
//  Notes:
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramEven_8u_C1R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist, Ipp32s* pLevels, int nLevels, Ipp32s lowerLevel, Ipp32s upperLevel))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramEven_8u_C3R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist[3], Ipp32s* pLevels[3], int nLevels[3], Ipp32s lowerLevel[3], Ipp32s upperLevel[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramEven_8u_AC4R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist[3], Ipp32s* pLevels[3], int nLevels[3], Ipp32s lowerLevel[3], Ipp32s upperLevel[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramEven_8u_C4R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist[4], Ipp32s* pLevels[4], int nLevels[4], Ipp32s lowerLevel[4], Ipp32s upperLevel[4]))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramEven_16s_C1R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist, Ipp32s* pLevels, int nLevels, Ipp32s lowerLevel, Ipp32s upperLevel))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramEven_16s_C3R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist[3], Ipp32s* pLevels[3], int nLevels[3], Ipp32s lowerLevel[3], Ipp32s upperLevel[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramEven_16s_AC4R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist[3], Ipp32s* pLevels[3], int nLevels[3], Ipp32s lowerLevel[3], Ipp32s upperLevel[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramEven_16s_C4R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist[4], Ipp32s* pLevels[4], int nLevels[4], Ipp32s lowerLevel[4], Ipp32s upperLevel[4]))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramEven_16u_C1R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist, Ipp32s* pLevels, int nLevels, Ipp32s lowerLevel, Ipp32s upperLevel))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramEven_16u_C3R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist[3], Ipp32s* pLevels[3], int nLevels[3], Ipp32s lowerLevel[3], Ipp32s upperLevel[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramEven_16u_AC4R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist[3], Ipp32s* pLevels[3], int nLevels[3], Ipp32s lowerLevel[3], Ipp32s upperLevel[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiHistogramEven_16u_C4R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp32s* pHist[4], Ipp32s* pLevels[4], int nLevels[4], Ipp32s lowerLevel[4], Ipp32s upperLevel[4]))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiLUT_Linear, ippiLUT_Cubic
//  Purpose:        Performs intensity transformation of an image
//                  using lookup table (LUT) without interpolation or
//                  using lookup table (LUT) with linear interpolation or
//                  using lookup table (LUT) with cubic interpolation
//  Parameters:
//    pSrc          pointer to the source image
//    srcStep       step in bytes through the source image
//    pDst          pointer to the destination image
//    dstStep       step in bytes through the destination image
//    pSrcDst       pointer to the destination image (inplace case)
//    srcDstStep    step in bytes through the destination image (inplace case)
//    roiSize       size of the source and destination ROI
//    pValues       pointer to the array of intensity values
//    pLevels       pointer to the array of level values
//    nLevels       number of levels
//  Returns:
//    ippStsNoErr           no errors
//    ippStsNullPtrErr      one of the pointers is NULL
//    ippStsSizeErr         roiSize has a field with zero or negative value
//    ippStsMemAllocErr     there is not enough memory for the inner histogram
//    ippStsLUTNofLevelsErr number of levels is less 2
//  Notes:
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_8u_C1R,(const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp32s* pValues, const Ipp32s* pLevels, int nLevels))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_8u_C3R,(const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp32s* pValues[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_8u_C4R,(const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp32s* pValues[4], const Ipp32s* pLevels[4], int nLevels[4]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_8u_AC4R,(const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp32s* pValues[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_8u_C1IR,(Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32s* pValues, const Ipp32s* pLevels, int nLevels))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_8u_C3IR,(Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32s* pValues[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_8u_C4IR,(Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32s* pValues[4], const Ipp32s* pLevels[4], int nLevels[4]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_8u_AC4IR,(Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32s* pValues[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_16s_C1R,(const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, const Ipp32s* pValues, const Ipp32s* pLevels, int nLevels))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_16s_C3R,(const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, const Ipp32s* pValues[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_16s_C4R,(const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, const Ipp32s* pValues[4], const Ipp32s* pLevels[4], int nLevels[4]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_16s_AC4R,(const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, const Ipp32s* pValues[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_16s_C1IR,(Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32s* pValues, const Ipp32s* pLevels, int nLevels))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_16s_C3IR,(Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32s* pValues[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_16s_C4IR,(Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32s* pValues[4], const Ipp32s* pLevels[4], int nLevels[4]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_16s_AC4IR,(Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32s* pValues[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_16u_C1R,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, const Ipp32s* pValues, const Ipp32s* pLevels, int nLevels))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_16u_C3R,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, const Ipp32s* pValues[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_16u_C4R,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, const Ipp32s* pValues[4], const Ipp32s* pLevels[4], int nLevels[4]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_16u_AC4R,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, const Ipp32s* pValues[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_16u_C1IR,(Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32s* pValues, const Ipp32s* pLevels, int nLevels))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_16u_C3IR,(Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32s* pValues[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_16u_C4IR,(Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32s* pValues[4], const Ipp32s* pLevels[4], int nLevels[4]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_16u_AC4IR,(Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32s* pValues[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_32f_C1R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, const Ipp32f* pValues, const Ipp32f* pLevels, int nLevels))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_32f_C3R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, const Ipp32f* pValues[3], const Ipp32f* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_32f_C4R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, const Ipp32f* pValues[4], const Ipp32f* pLevels[4], int nLevels[4]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_32f_AC4R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, const Ipp32f* pValues[3], const Ipp32f* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_32f_C1IR,(Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32f* pValues, const Ipp32f* pLevels, int nLevels))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_32f_C3IR,(Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32f* pValues[3], const Ipp32f* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_32f_C4IR,(Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32f* pValues[4], const Ipp32f* pLevels[4], int nLevels[4]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Linear_32f_AC4IR,(Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32f* pValues[3], const Ipp32f* pLevels[3], int nLevels[3]))

LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_8u_C1R,(const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp32s* pValues, const Ipp32s* pLevels, int nLevels))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_8u_C3R,(const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp32s* pValues[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_8u_C4R,(const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp32s* pValues[4], const Ipp32s* pLevels[4], int nLevels[4]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_8u_AC4R,(const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp32s* pValues[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_8u_C1IR,(Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32s* pValues, const Ipp32s* pLevels, int nLevels))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_8u_C3IR,(Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32s* pValues[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_8u_C4IR,(Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32s* pValues[4], const Ipp32s* pLevels[4], int nLevels[4]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_8u_AC4IR,(Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32s* pValues[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_16s_C1R,(const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, const Ipp32s* pValues, const Ipp32s* pLevels, int nLevels))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_16s_C3R,(const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, const Ipp32s* pValues[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_16s_C4R,(const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, const Ipp32s* pValues[4], const Ipp32s* pLevels[4], int nLevels[4]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_16s_AC4R,(const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, const Ipp32s* pValues[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_16s_C1IR,(Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32s* pValues, const Ipp32s* pLevels, int nLevels))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_16s_C3IR,(Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32s* pValues[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_16s_C4IR,(Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32s* pValues[4], const Ipp32s* pLevels[4], int nLevels[4]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_16s_AC4IR,(Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32s* pValues[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_16u_C1R,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, const Ipp32s* pValues, const Ipp32s* pLevels, int nLevels))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_16u_C3R,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, const Ipp32s* pValues[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_16u_C4R,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, const Ipp32s* pValues[4], const Ipp32s* pLevels[4], int nLevels[4]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_16u_AC4R,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, const Ipp32s* pValues[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_16u_C1IR,(Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32s* pValues, const Ipp32s* pLevels, int nLevels))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_16u_C3IR,(Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32s* pValues[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_16u_C4IR,(Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32s* pValues[4], const Ipp32s* pLevels[4], int nLevels[4]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_16u_AC4IR,(Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32s* pValues[3], const Ipp32s* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_32f_C1R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, const Ipp32f* pValues, const Ipp32f* pLevels, int nLevels))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_32f_C3R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, const Ipp32f* pValues[3], const Ipp32f* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_32f_C4R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, const Ipp32f* pValues[4], const Ipp32f* pLevels[4], int nLevels[4]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_32f_AC4R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, const Ipp32f* pValues[3], const Ipp32f* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_32f_C1IR,(Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32f* pValues, const Ipp32f* pLevels, int nLevels))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_32f_C3IR,(Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32f* pValues[3], const Ipp32f* pLevels[3], int nLevels[3]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_32f_C4IR,(Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32f* pValues[4], const Ipp32f* pLevels[4], int nLevels[4]))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUT_Cubic_32f_AC4IR,(Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize, const Ipp32f* pValues[3], const Ipp32f* pLevels[3], int nLevels[3]))


/* ////////////////////////////////////////////////////////////////////////////
//  Names:       ippiLUTPalette
//  Purpose:     intensity transformation of image using the palette lookup table pTable
//  Parameters:
//    pSrc       pointer to the source image
//    srcStep    line offset in input data in bytes
//    alphaValue constant alpha channel
//    pDst       pointer to the destination image
//    dstStep    line offset in output data in bytes
//    roiSize    size of source ROI in pixels
//    pTable     pointer to palette table of size 2^nBitSize or
//               array of pointers to each channel
//    nBitSize   number of valid bits in the source image
//               (range [1,8] for 8u source images and range [1,16] for 16u source images)
//  Returns:
//    ippStsNoErr         no errors
//    ippStsNullPtrErr    pSrc == NULL or pDst == NULL or pTable == NULL
//    ippStsSizeErr       width or height of ROI is less or equal zero
//    ippStsOutOfRangeErr nBitSize is out of range
//  Notes:
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiLUTPalette_8u_C3A0C4R, (const Ipp8u* pSrc, int srcStep, int alphaValue, Ipp8u* pDst, int dstStep,
       IppiSize roiSize, const Ipp8u* const pTable[3], int nBitSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUTPalette_16u_C3A0C4R, (const Ipp16u* pSrc, int srcStep, int alphaValue, Ipp16u* pDst, int dstStep,
       IppiSize roiSize, const Ipp16u* const pTable[3], int nBitSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUTPaletteSwap_8u_C3A0C4R, (const Ipp8u* pSrc, int srcStep, int alphaValue, Ipp8u* pDst, int dstStep,
       IppiSize roiSize, const Ipp8u* const pTable[3], int nBitSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiLUTPaletteSwap_16u_C3A0C4R, (const Ipp16u* pSrc, int srcStep, int alphaValue, Ipp16u* pDst, int dstStep,
       IppiSize roiSize, const Ipp16u* const pTable[3], int nBitSize))


/* ///////////////////////////////////////////////////////////////////////////
//             Non-linear Filters
/////////////////////////////////////////////////////////////////////////// */

/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiFilterMedianHoriz_8u_C1R
//              ippiFilterMedianHoriz_8u_C3R
//              ippiFilterMedianHoriz_8u_AC4R
//              ippiFilterMedianHoriz_16s_C1R
//              ippiFilterMedianHoriz_16s_C3R
//              ippiFilterMedianHoriz_16s_AC4R
//              ippiFilterMedianHoriz_8u_C4R
//              ippiFilterMedianHoriz_16s_C4R
//              ippiFilterMedianHoriz_16u_C1R
//              ippiFilterMedianHoriz_16u_C3R
//              ippiFilterMedianHoriz_16u_AC4R
//              ippiFilterMedianHoriz_16u_C4R

//  Purpose:  Performs horizontal median filtering
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  pSrc or pDst is NULL
//   ippStsSizeErr     dstRoiSize has a field with zero or negative value
//   ippStsStepErr     srcStep or dstStep has zero or negative value
//   ippStsMaskSizeErr Illegal value of mask
//
//  Parameters:
//   pSrc        Pointer to the source image
//   srcStep     Step through the source image
//   pDst        Pointer to the destination image
//   dstStep     Step through the destination image
//   dstRoiSize  Size of the destination ROI
//   mask        Type of the filter mask
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedianHoriz_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedianHoriz_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedianHoriz_8u_AC4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedianHoriz_16s_C1R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedianHoriz_16s_C3R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedianHoriz_16s_AC4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedianHoriz_8u_C4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedianHoriz_16s_C4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedianHoriz_16u_C1R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedianHoriz_16u_C3R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedianHoriz_16u_AC4R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedianHoriz_16u_C4R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiFilterMedianVert_8u_C1R
//              ippiFilterMedianVert_8u_C3R
//              ippiFilterMedianVert_8u_AC4R
//              ippiFilterMedianVert_16s_C1R
//              ippiFilterMedianVert_16s_C3R
//              ippiFilterMedianVert_16s_AC4R
//              ippiFilterMedianVert_8u_C4R
//              ippiFilterMedianVert_16s_C4R
//              ippiFilterMedianVert_16u_C1R
//              ippiFilterMedianVert_16u_C3R
//              ippiFilterMedianVert_16u_AC4R
//              ippiFilterMedianVert_16u_C4R
//  Purpose: Performs vertical median filtering
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  pSrc or pDst is NULL
//   ippStsSizeErr     dstRoiSize has a field with zero or negative value
//   ippStsStepErr     srcStep or dstStep has zero or negative value
//   ippStsMaskSizeErr Illegal value of mask
//
//  Parameters:
//   pSrc        Pointer to the source image
//   srcStep     Step through the source image
//   pDst        Pointer to the destination image
//   dstStep     Step through the destination image
//   dstRoiSize  Size of the destination ROI
//   mask        Type of the filter mask
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedianVert_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedianVert_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedianVert_8u_AC4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedianVert_16s_C1R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedianVert_16s_C3R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedianVert_16s_AC4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedianVert_8u_C4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedianVert_16s_C4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedianVert_16u_C1R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedianVert_16u_C3R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedianVert_16u_AC4R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedianVert_16u_C4R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))


/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiFilterMedian_8u_C1R
//              ippiFilterMedian_8u_C3R
//              ippiFilterMedian_8u_AC4R
//              ippiFilterMedian_16s_C1R
//              ippiFilterMedian_16s_C3R
//              ippiFilterMedian_16s_AC4R
//              ippiFilterMedian_8u_C4R
//              ippiFilterMedian_16s_C4R
//              ippiFilterMedian_16u_C1R
//              ippiFilterMedian_16u_C3R
//              ippiFilterMedian_16u_AC4R
//              ippiFilterMedian_16u_C4R
//              ippiFilterMedian_32f_C1R
//              ippiFilterMedian_32f_C3R
//              ippiFilterMedian_32f_C4R
//              ippiFilterMedian_64f_C1R

//  Purpose:  Filters an image using a box median filter
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  pSrc or pDst is NULL
//   ippStsSizeErr     dstRoiSize has a field with zero or negative value
//   ippStsStepErr     srcStep or dstStep has zero or negative value
//   ippStsMaskSizeErr maskSize has a field with zero, negative, or even value
//   ippStsAnchorErr   anchor is outside the mask
//
//  Parameters:
//   pSrc        Pointer to the source image
//   srcStep     Step through the source image
//   pDst        Pointer to the destination image
//   dstStep     Step through the destination image
//   dstRoiSize  Size of the destination ROI
//   maskSize    Size of the mask in pixels
//   anchor      Anchor cell specifying the mask alignment with respect to
//               the position of input pixel
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedian_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedian_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedian_8u_AC4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedian_16s_C1R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedian_16s_C3R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedian_16s_AC4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedian_8u_C4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedian_16s_C4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedian_16u_C1R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedian_16u_C3R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedian_16u_AC4R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedian_16u_C4R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMedian_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))


/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiFilterMax_8u_C1R
//              ippiFilterMax_8u_C3R
//              ippiFilterMax_8u_AC4R
//              ippiFilterMax_8u_C4R
//              ippiFilterMax_16s_C1R
//              ippiFilterMax_16s_C3R
//              ippiFilterMax_16s_AC4R
//              ippiFilterMax_16s_C4R
//              ippiFilterMax_16u_C1R
//              ippiFilterMax_16u_C3R
//              ippiFilterMax_16u_AC4R
//              ippiFilterMax_16u_C4R
//              ippiFilterMax_32f_C1R
//              ippiFilterMax_32f_C3R
//              ippiFilterMax_32f_AC4R
//              ippiFilterMax_32f_C4R
//  Purpose:  Applies the "max" filter to an image
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  pSrc or pDst is NULL
//   ippStsSizeErr     dstRoiSize has a field with zero or negative value
//   ippStsStepErr     srcStep or dstStep has zero or negative value
//   ippStsMaskSizeErr maskSize has a field with zero, or negative value
//   ippStsAnchorErr   anchor is outside the mask
//
//  Parameters:
//   pSrc        Pointer to the source image
//   srcStep     Step through the source image
//   pDst        Pointer to the destination image
//   dstStep     Step through the destination image
//   pSrcDst     Pointer to the source/destination image (in-place flavors)
//   srcDstStep  Step through the source/destination image (in-place flavors)
//   dstRoiSize  Size of the destination ROI
//   roiSize     Size of the source/destination ROI (in-place flavors)
//   maskSize    Size of the mask in pixels
//   anchor      Anchor cell specifying the mask alignment with respect to
//               the position of input pixel
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMax_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMax_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMax_8u_AC4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMax_8u_C4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))

LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMax_16s_C1R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMax_16s_C3R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMax_16s_AC4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMax_16s_C4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))

LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMax_16u_C1R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMax_16u_C3R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMax_16u_AC4R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMax_16u_C4R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))

LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMax_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMax_32f_C3R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMax_32f_AC4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMax_32f_C4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiFilterMin_8u_C1R
//              ippiFilterMin_8u_C3R
//              ippiFilterMin_8u_AC4R
//              ippiFilterMin_8u_C4R
//              ippiFilterMin_16s_C1R
//              ippiFilterMin_16s_C3R
//              ippiFilterMin_16s_AC4R
//              ippiFilterMin_16s_C4R
//              ippiFilterMin_16u_C1R
//              ippiFilterMin_16u_C3R
//              ippiFilterMin_16u_AC4R
//              ippiFilterMin_16u_C4R
//              ippiFilterMin_32f_C1R
//              ippiFilterMin_32f_C3R
//              ippiFilterMin_32f_AC4R
//              ippiFilterMin_32f_C4R
//  Purpose:  Applies the "min" filter to an image
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  pSrc or pDst is NULL
//   ippStsSizeErr     dstRoiSize has a field with zero or negative value
//   ippStsStepErr     srcStep or dstStep has zero or negative value
//   ippStsMaskSizeErr maskSize has a field with zero, or negative value
//   ippStsAnchorErr   anchor is outside the mask
//
//  Parameters:
//   pSrc        Pointer to the source image
//   srcStep     Step through the source image
//   pDst        Pointer to the destination image
//   dstStep     Step through the destination image
//   dstRoiSize  Size of the destination ROI
//   maskSize    Size of the mask in pixels
//   anchor      Anchor cell specifying the mask alignment with respect to
//               the position of input pixel
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMin_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMin_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMin_8u_AC4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMin_8u_C4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))

LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMin_16s_C1R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMin_16s_C3R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMin_16s_AC4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMin_16s_C4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))

LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMin_16u_C1R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMin_16u_C3R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMin_16u_AC4R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMin_16u_C4R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))

LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMin_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMin_32f_C3R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMin_32f_AC4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterMin_32f_C4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor))


/* ///////////////////////////////////////////////////////////////////////////
// Name:   ippiFilterBox_8u_<desc>R,  ippiFilterBox_8u_<desc>IR
//         ippiFilterBox_16u_<desc>R, ippiFilterBox_16u_<desc>IR
//         ippiFilterBox_16s_<desc>R, ippiFilterBox_16s_<desc>IR
//         ippiFilterBox_32f_<desc>R, ippiFilterBox_32f_<desc>IR
//           <desc>  C1|C3|C4|AC4   (descriptor)
// Purpose:             Blurs an image using a simple box filter
// Parameters:
//   pSrc               pointer to the source image
//   srcStep            step in the source image
//   pDst               pointer to the destination image
//   dstStep            step in the destination image
//   pSrcDst            pointer to the source/destination image (in-place flavors)
//   srcDstStep         step in the source/destination image (in-place flavors)
//   dstRoiSize         size of the destination ROI
//   roiSize            size of the source/destination ROI (in-place flavors)
//   maskSize           size of the mask in pixels
//   anchor             the [x,y] coordinates of the anchor cell in the kernel
// Returns:
//   ippStsNoErr        No errors
//   ippStsNullPtrErr   pSrc == NULL or pDst == NULL or pSrcDst == NULL
//   ippStsStepErr      one of the step values is zero or negative
//   ippStsSizeErr      dstRoiSize or roiSize has a field with zero or negative value
//   ippStsMaskSizeErr  maskSize has a field with zero or negative value
//   ippStsAnchorErr    anchor is outside the mask
//   ippStsMemAllocErr  memory allocation error
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_8u_C1R, (const Ipp8u* pSrc,int srcStep,
       Ipp8u* pDst, int dstStep,IppiSize dstRoiSize, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_8u_C3R, (const Ipp8u* pSrc,int srcStep,
       Ipp8u* pDst, int dstStep,IppiSize dstRoiSize, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_8u_C4R, (const Ipp8u* pSrc,int srcStep,
       Ipp8u* pDst, int dstStep,IppiSize dstRoiSize, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_8u_AC4R, (const Ipp8u* pSrc,int srcStep,
       Ipp8u* pDst, int dstStep,IppiSize dstRoiSize, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_16u_C1R, (const Ipp16u* pSrc,int srcStep,
       Ipp16u* pDst, int dstStep,IppiSize dstRoiSize,IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_16u_C3R, (const Ipp16u* pSrc,int srcStep,
       Ipp16u* pDst, int dstStep,IppiSize dstRoiSize, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_16u_C4R, (const Ipp16u* pSrc,int srcStep,
       Ipp16u* pDst, int dstStep,IppiSize dstRoiSize, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_16u_AC4R, (const Ipp16u* pSrc,int srcStep,
       Ipp16u* pDst, int dstStep,IppiSize dstRoiSize,IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_16s_C1R, (const Ipp16s* pSrc,int srcStep,
       Ipp16s* pDst, int dstStep,IppiSize dstRoiSize,IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_16s_C3R, (const Ipp16s* pSrc,int srcStep,
       Ipp16s* pDst, int dstStep,IppiSize dstRoiSize, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_16s_C4R, (const Ipp16s* pSrc,int srcStep,
       Ipp16s* pDst, int dstStep,IppiSize dstRoiSize, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_16s_AC4R, (const Ipp16s* pSrc,int srcStep,
       Ipp16s* pDst, int dstStep,IppiSize dstRoiSize,IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_32f_C1R, (const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep,IppiSize dstRoiSize, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_32f_C3R, (const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep,IppiSize dstRoiSize, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_32f_C4R, (const Ipp32f* pSrc,int srcStep,
       Ipp32f* pDst, int dstStep,IppiSize dstRoiSize, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_32f_AC4R, (const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep,IppiSize dstRoiSize, IppiSize maskSize, IppiPoint anchor))

LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_8u_C1IR, (Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_8u_C3IR, (Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_8u_C4IR, (Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize,IppiSize maskSize,IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_8u_AC4IR, (Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_16u_C1IR, (Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_16u_C3IR, (Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_16u_C4IR, (Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize,IppiSize maskSize,IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_16u_AC4IR, (Ipp16u* pSrc, int srcDstStep,
       IppiSize roiSize, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_16s_C1IR, (Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_16s_C3IR, (Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_16s_C4IR, (Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize,IppiSize maskSize,IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_16s_AC4IR, (Ipp16s* pSrc, int srcDstStep,
       IppiSize roiSize, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_32f_C1IR, (Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_32f_C3IR, (Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_32f_C4IR, (Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize,IppiSize maskSize,IppiPoint anchor))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBox_32f_AC4IR, (Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize, IppiSize maskSize, IppiPoint anchor))


/* ///////////////////////////////////////////////////////////////////////////
//             Filters with Fixed Kernel
/////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiFilterPrewittHoriz_8u_C1R
//              ippiFilterPrewittHoriz_8u_C3R
//              ippiFilterPrewittHoriz_8u_AC4R
//              ippiFilterPrewittHoriz_8u_C4R
//              ippiFilterPrewittHoriz_16s_C1R
//              ippiFilterPrewittHoriz_16s_C3R
//              ippiFilterPrewittHoriz_16s_AC4R
//              ippiFilterPrewittHoriz_16s_C4R
//              ippiFilterPrewittHoriz_32f_C1R
//              ippiFilterPrewittHoriz_32f_C3R
//              ippiFilterPrewittHoriz_32f_AC4R
//              ippiFilterPrewittHoriz_32f_C4R
//              ippiFilterPrewittVert_8u_C1R
//              ippiFilterPrewittVert_8u_C3R
//              ippiFilterPrewittVert_8u_AC4R
//              ippiFilterPrewittVert_8u_C4R
//              ippiFilterPrewittVert_16s_C1R
//              ippiFilterPrewittVert_16s_C3R
//              ippiFilterPrewittVert_16s_AC4R
//              ippiFilterPrewittVert_16s_C4R
//              ippiFilterPrewittVert_32f_C1R
//              ippiFilterPrewittVert_32f_C3R
//              ippiFilterPrewittVert_32f_AC4R
//              ippiFilterPrewittVert_32f_C4R
//              ippiFilterSobelHoriz_8u_C1R
//              ippiFilterSobelHoriz_8u_C3R
//              ippiFilterSobelHoriz_8u_AC4R
//              ippiFilterSobelHoriz_8u_C4R
//              ippiFilterSobelHoriz_16s_C1R
//              ippiFilterSobelHoriz_16s_C3R
//              ippiFilterSobelHoriz_16s_AC4R
//              ippiFilterSobelHoriz_16s_C4R
//              ippiFilterSobelHoriz_32f_C1R
//              ippiFilterSobelHoriz_32f_C3R
//              ippiFilterSobelHoriz_32f_AC4R
//              ippiFilterSobelHoriz_32f_C4R
//              ippiFilterSobelVert_8u_C1R
//              ippiFilterSobelVert_8u_C3R
//              ippiFilterSobelVert_8u_AC4R
//              ippiFilterSobelVert_8u_C4R
//              ippiFilterSobelVert_16s_C1R
//              ippiFilterSobelVert_16s_C3R
//              ippiFilterSobelVert_16s_AC4R
//              ippiFilterSobelVert_16s_C4R
//              ippiFilterSobelVert_32f_C1R
//              ippiFilterSobelVert_32f_C3R
//              ippiFilterSobelVert_32f_AC4R
//              ippiFilterSobelVert_32f_C4R
//              ippiFilterRobertsDown_8u_C1R
//              ippiFilterRobertsDown_8u_C3R
//              ippiFilterRobertsDown_8u_AC4R
//              ippiFilterRobertsDown_16s_C1R
//              ippiFilterRobertsDown_16s_C3R
//              ippiFilterRobertsDown_16s_AC4R
//              ippiFilterRobertsDown_32f_C1R
//              ippiFilterRobertsDown_32f_C3R
//              ippiFilterRobertsDown_32f_AC4R
//              ippiFilterRobertsUp_8u_C1R
//              ippiFilterRobertsUp_8u_C3R
//              ippiFilterRobertsUp_8u_AC4R
//              ippiFilterRobertsUp_16s_C1R
//              ippiFilterRobertsUp_16s_C3R
//              ippiFilterRobertsUp_16s_AC4R
//              ippiFilterRobertsUp_32f_C1R
//              ippiFilterRobertsUp_32f_C3R
//              ippiFilterRobertsUp_32f_AC4R
//              ippiFilterSharpen_8u_C1R
//              ippiFilterSharpen_8u_C3R
//              ippiFilterSharpen_8u_AC4R
//              ippiFilterSharpen_8u_C4R
//              ippiFilterSharpen_16s_C1R
//              ippiFilterSharpen_16s_C3R
//              ippiFilterSharpen_16s_AC4R
//              ippiFilterSharpen_16s_C4R
//              ippiFilterSharpen_32f_C1R
//              ippiFilterSharpen_32f_C3R
//              ippiFilterSharpen_32f_AC4R
//              ippiFilterSharpen_32f_C4R
//              ippiFilterScharrVert_8u16s_C1R
//              ippiFilterScharrVert_8s16s_C1R
//              ippiFilterScharrVert_32f_C1R
//              ippiFilterScharrHoriz_8u16s_C1R
//              ippiFilterScharrHoriz_8s16s_C1R
//              ippiFilterScharrHoriz_32f_C1R
//
//  Purpose:  Perform linear filtering of an image using one of
//            predefined convolution kernels (3x3):
//
//                                1  1  1
//              PrewittHoriz      0  0  0
//                               -1 -1 -1
//
//
//                               -1  0  1
//              PrewittVert      -1  0  1
//                               -1  0  1
//
//
//                                1  2  1
//              SobelHoriz        0  0  0
//                               -1 -2 -1
//
//
//                               -1  0  1
//              SobelVert        -2  0  2
//                               -1  0  1
//
//
//                                0  0  0
//              RobetsDown        0  1  0
//                                0  0 -1
//
//
//                                0  0  0
//              RobertsUp         0  1  0
//                               -1  0  0
//
//
//                               -1 -1  1
//              Sharpen          -1 16  1  X  1/8
//                               -1 -1  1
//
//
//                                3  0  -3
//              ScharrVert       10  0 -10
//                                3  0  -3
//
//
//                                3  10  3
//              ScharrHoriz       0   0  0
//                               -3 -10 -3
//
//
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  pSrc or pDst is NULL
//   ippStsSizeErr     roiSize has a field with zero or negative value
//   ippStsStepErr     srcStep or dstStep has zero or negative value
//
//  Parameters:
//   pSrc       Pointer to the source image
//   srcStep    Step through the source image
//   pDst       Pointer to the destination image
//   dstStep    Step through the destination image
//   roiSize    size of the ROI
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterPrewittVert_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterPrewittVert_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterPrewittVert_8u_AC4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterPrewittVert_8u_C4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterPrewittVert_16s_C1R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterPrewittVert_16s_C3R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterPrewittVert_16s_AC4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterPrewittVert_16s_C4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterPrewittVert_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterPrewittVert_32f_C3R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterPrewittVert_32f_AC4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterPrewittVert_32f_C4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterPrewittHoriz_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterPrewittHoriz_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterPrewittHoriz_8u_AC4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterPrewittHoriz_8u_C4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterPrewittHoriz_16s_C1R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterPrewittHoriz_16s_C3R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterPrewittHoriz_16s_AC4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterPrewittHoriz_16s_C4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterPrewittHoriz_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterPrewittHoriz_32f_C3R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterPrewittHoriz_32f_AC4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterPrewittHoriz_32f_C4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelVert_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelVert_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelVert_8u_AC4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelVert_8u_C4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelVert_16s_C1R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelVert_16s_C3R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelVert_16s_AC4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelVert_16s_C4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelVert_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelVert_32f_C3R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelVert_32f_AC4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelVert_32f_C4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelHoriz_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelHoriz_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelHoriz_8u_AC4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelHoriz_8u_C4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelHoriz_16s_C1R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelHoriz_16s_C3R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelHoriz_16s_AC4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelHoriz_16s_C4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelHoriz_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelHoriz_32f_C3R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelHoriz_32f_AC4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelHoriz_32f_C4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterRobertsUp_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterRobertsUp_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterRobertsUp_8u_AC4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterRobertsUp_16s_C1R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterRobertsUp_16s_C3R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterRobertsUp_16s_AC4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterRobertsUp_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterRobertsUp_32f_C3R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterRobertsUp_32f_AC4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterRobertsDown_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterRobertsDown_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterRobertsDown_8u_AC4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterRobertsDown_16s_C1R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterRobertsDown_16s_C3R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterRobertsDown_16s_AC4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterRobertsDown_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterRobertsDown_32f_C3R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterRobertsDown_32f_AC4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSharpen_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSharpen_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSharpen_8u_AC4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSharpen_8u_C4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSharpen_16s_C1R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSharpen_16s_C3R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSharpen_16s_AC4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSharpen_16s_C4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSharpen_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSharpen_32f_C3R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSharpen_32f_AC4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSharpen_32f_C4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterScharrVert_8u16s_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize ))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterScharrHoriz_8u16s_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize ))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterScharrVert_8s16s_C1R,(const Ipp8s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize ))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterScharrHoriz_8s16s_C1R,(const Ipp8s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize ))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterScharrVert_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize ))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterScharrHoriz_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize ))


/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiFilterLaplace_8u_C1R
//              ippiFilterLaplace_8u_C3R
//              ippiFilterLaplace_8u_AC4R
//              ippiFilterLaplace_8u_C4R
//              ippiFilterLaplace_16s_C1R
//              ippiFilterLaplace_16s_C3R
//              ippiFilterLaplace_16s_AC4R
//              ippiFilterLaplace_16s_C4R
//              ippiFilterLaplace_32f_C1R
//              ippiFilterLaplace_32f_C3R
//              ippiFilterLaplace_32f_AC4R
//              ippiFilterLaplace_32f_C4R
//              ippiFilterGauss_8u_C1R
//              ippiFilterGauss_8u_C3R
//              ippiFilterGauss_8u_AC4R
//              ippiFilterGauss_8u_C4R
//              ippiFilterGauss_16s_C1R
//              ippiFilterGauss_16s_C3R
//              ippiFilterGauss_16s_AC4R
//              ippiFilterGauss_16s_C4R
//              ippiFilterGauss_16u_C1R
//              ippiFilterGauss_16u_C3R
//              ippiFilterGauss_16u_AC4R
//              ippiFilterGauss_16u_C4R
//              ippiFilterGauss_32f_C1R
//              ippiFilterGauss_32f_C3R
//              ippiFilterGauss_32f_AC4R
//              ippiFilterGauss_32f_C4R
//              ippiFilterLowpass_8u_C1R
//              ippiFilterLowpass_8u_C3R
//              ippiFilterLowpass_8u_AC4R
//              ippiFilterLowpass_16s_C1R
//              ippiFilterLowpass_16s_C3R
//              ippiFilterLowpass_16s_AC4R
//              ippiFilterLowpass_16u_C1R
//              ippiFilterLowpass_16u_C3R
//              ippiFilterLowpass_16u_AC4R
//              ippiFilterLowpass_32f_C1R
//              ippiFilterLowpass_32f_C3R
//              ippiFilterLowpass_32f_AC4R
//              ippiFilterHipass_8u_C1R
//              ippiFilterHipass_8u_C3R
//              ippiFilterHipass_8u_AC4R
//              ippiFilterHipass_8u_C4R
//              ippiFilterHipass_16s_C1R
//              ippiFilterHipass_16s_C3R
//              ippiFilterHipass_16s_AC4R
//              ippiFilterHipass_16s_C4R
//              ippiFilterHipass_32f_C1R
//              ippiFilterHipass_32f_C3R
//              ippiFilterHipass_32f_AC4R
//              ippiFilterHipass_32f_C4R
//              ippiFilterSobelVert_8u16s_C1R
//              ippiFilterSobelVert_8s16s_C1R
//              ippiFilterSobelVertMask_32f_C1R
//              ippiFilterSobelHoriz_8u16s_C1R
//              ippiFilterSobelHoriz_8s16s_C1R
//              ippiFilterSobelHorizMask_32f_C1R
//              ippiFilterSobelVertSecond_8u16s_C1R
//              ippiFilterSobelVertSecond_8s16s_C1R
//              ippiFilterSobelVertSecond_32f_C1R
//              ippiFilterSobelHorizSecond_8u16s_C1R
//              ippiFilterSobelHorizSecond_8s16s_C1R
//              ippiFilterSobelHorizSecond_32f_C1R
//              ippiFilterSobelCross_8u16s_C1R
//              ippiFilterSobelCross_8s16s_C1R
//              ippiFilterSobelCross_32f_C1R
//
//  Purpose:   Perform linear filtering of an image using one of
//             predefined convolution kernels (3x3 or 5x5):
//
//                               -1 -1  1
//              Laplace (3x3)    -1  8  1
//                               -1 -1  1
//
//
//                                1  2  1
//              Gauss (3x3)       2  4  2  X  1/16
//                                1  2  1
//
//
//                                1  1  1
//              Lowpass (3x3)     1  1  1  X  1/9
//                                1  1  1
//
//
//                               -1 -1 -1
//              Hipass (3x3 )    -1  8 -1
//                               -1 -1 -1
//
//
//                               -1  0  1
//              SobelVert (3x3)  -2  0  2
//                               -1  0  1
//
//
//                                1  2  1
//              SobelHoriz (3x3)  0  0  0
//                               -1 -2 -1
//
//
//                                       1 -2  1
//              SobelVertSecond (3x3)    2 -4  2
//                                       1 -2  1
//
//
//                                       1  2  1
//              SobelHorizSecond (3x3)  -2 -4 -2
//                                       1  2  1
//
//
//                               -1  0  1
//              SobelCross (3x3)  0  0  0
//                                1  0 -1
//
//
//                               -1 -3 -4 -3 -1
//                               -3  0  6  0 -3
//              Laplace (5x5)    -4  6 20  6 -4
//                               -3  0  6  0 -3
//                               -1 -3 -4 -3 -1
//
//                                2   7  12   7   2
//                                7  31  52  31   7
//              Gauss (5x5)      12  52 127  52  12  X  1/571
//                                7  31  52  31   7
//                                2   7  12   7   2
//
//                                1 1 1 1 1
//                                1 1 1 1 1
//              Lowpass (5x5)     1 1 1 1 1  X  1/25
//                                1 1 1 1 1
//                                1 1 1 1 1
//

//                               -1 -1 -1 -1 -1
//                               -1 -1 -1 -1 -1
//              Hipass (5x5)     -1 -1 24 -1 -1
//                               -1 -1 -1 -1 -1
//                               -1 -1 -1 -1 -1
//
//                               -1  -2   0   2   1
//                               -4  -8   0   8   4
//              SobelVert (5x5)  -6 -12   0  12   6
//                               -4  -8   0   8   4
//                               -1  -2   0   2   1
//
//                                1   4   6   4   1
//                                2   8  12   8   2
//              SobelHoriz (5x5)  0   0   0   0   0
//                               -2  -8 -12  -8  -4
//                               -1  -4  -6  -4  -1
//
//                                       1   0  -2   0   1
//                                       4   0  -8   0   4
//              SobelVertSecond (5x5)    6   0 -12   0   6
//                                       4   0  -8   0   4
//                                       1   0  -2   0   1
//
//                                       1   4   6   4   1
//                                       0   0   0   0   0
//              SobelVertHoriz (5x5)    -2  -8 -12  -8  -2
//                                       0   0   0   0   0
//                                       1   4   6   4   1
//
//                               -1  -2   0   2   1
//                               -2  -4   0   4   2
//              SobelCross (5x5)  0   0   0   0   0
//                                2   4   0  -4  -2
//                                1   2   0  -2  -1
//
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  pSrc or pDst is NULL
//   ippStsSizeErr     roiSize has a field with zero or negative value
//   ippStsStepErr     srcStep or dstStep has zero or negative value
//   ippStsMaskSizeErr Illegal mask value
//
//  Parameters:
//   pSrc       Pointer to the source image
//   srcStep    Step through the source image
//   pDst       Pointer to the destination image
//   dstStep    Step through the destination image
//   roiSize    size of the ROI
//   mask       Filter mask
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLaplace_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLaplace_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLaplace_8u_AC4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLaplace_8u_C4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLaplace_16s_C1R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLaplace_16s_C3R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLaplace_16s_AC4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLaplace_16s_C4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLaplace_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLaplace_32f_C3R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLaplace_32f_AC4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLaplace_32f_C4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterGauss_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterGauss_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterGauss_8u_AC4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterGauss_8u_C4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterGauss_16s_C1R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterGauss_16s_C3R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterGauss_16s_AC4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterGauss_16s_C4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterGauss_16u_C1R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterGauss_16u_C3R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterGauss_16u_AC4R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterGauss_16u_C4R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterGauss_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterGauss_32f_C3R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterGauss_32f_AC4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterGauss_32f_C4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterHipass_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterHipass_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterHipass_8u_AC4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterHipass_8u_C4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterHipass_16s_C1R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterHipass_16s_C3R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterHipass_16s_AC4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterHipass_16s_C4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterHipass_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterHipass_32f_C3R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterHipass_32f_AC4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterHipass_32f_C4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLowpass_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLowpass_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLowpass_8u_AC4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLowpass_16s_C1R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLowpass_16s_C3R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLowpass_16s_AC4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLowpass_16u_C1R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLowpass_16u_C3R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLowpass_16u_AC4R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLowpass_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLowpass_32f_C3R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLowpass_32f_AC4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLaplace_8u16s_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask ))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterLaplace_8s16s_C1R,(const Ipp8s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask ))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelVert_8u16s_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask ))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelHoriz_8u16s_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask ))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelVertSecond_8u16s_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask ))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelHorizSecond_8u16s_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask ))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelCross_8u16s_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask ))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelVert_8s16s_C1R,(const Ipp8s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask ))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelHoriz_8s16s_C1R,(const Ipp8s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask ))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelVertSecond_8s16s_C1R,(const Ipp8s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask ))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelHorizSecond_8s16s_C1R,(const Ipp8s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask ))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelCross_8s16s_C1R,(const Ipp8s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask ))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelVertMask_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask ))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelHorizMask_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask ))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelVertSecond_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask ))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelHorizSecond_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask ))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelCross_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiFilterSobelVertGetBufferSize_8u16s_C1R
//                      ippiFilterSobelHorizGetBufferSize_8u16s_C1R
//                      ippiFilterSobelVertGetBufferSize_32f_C1R
//                      ippiFilterSobelHorizGetBufferSize_32f_C1R
//
//  Purpose:            Computes the size of the external buffer for horizontal
//                      or vertical Sobel filter with border
//
//  Parameters:
//   roiSize            Size of destination ROI in pixels.
//   mask               Predefined mask of IppiMaskSize type. Possible values are ippMask3x3 or ippMask5x5.
//   pBufferSize        Pointer to the size (in bytes) of the external work buffer.
//
//  Return Values:
//   ippStsNoErr        Indicates no error.
//   ippStsNullPtrErr   Indicates an error when pBufferSize is NULL.
//   ippStsSizeErr      Indicates an error when roiSize is negative, or equal to zero.
//   ippStsMaskSizeErr  Indicates an error condition if mask has a wrong value
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelVertGetBufferSize_8u16s_C1R,(IppiSize roiSize, IppiMaskSize mask, int* pBufferSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelHorizGetBufferSize_8u16s_C1R,(IppiSize roiSize, IppiMaskSize mask, int* pBufferSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelVertGetBufferSize_32f_C1R,(IppiSize roiSize, IppiMaskSize mask, int* pBufferSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterSobelHorizGetBufferSize_32f_C1R,(IppiSize roiSize, IppiMaskSize mask, int* pBufferSize))


/* ///////////////////////////////////////////////////////////////////////////
//             General Linear Filters
/////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////////
//   Names:     ippiFilter_8u_C1R
//              ippiFilter_8u_C3R
//              ippiFilter_8u_C4R
//              ippiFilter_8u_AC4R
//              ippiFilter_16s_C1R    ippiFilter_16u_C1R
//              ippiFilter_16s_C3R    ippiFilter_16u_C3R
//              ippiFilter_16s_C4R    ippiFilter_16u_C4R
//              ippiFilter_16s_AC4R   ippiFilter_16u_AC4R
//
//  Purpose:    Filters an image using a general integer rectangular kernel
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  One of the pointers is NULL
//   ippStsSizeErr     dstRoiSize or kernelSize has a field with zero or negative value
//   ippStsDivisorErr  divisor value is zero, function execution is interrupted
//
//  Parameters:
//      pSrc        Pointer to the source buffer
//      srcStep     Step in bytes through the source image buffer
//      pDst        Pointer to the destination buffer
//      dstStep     Step in bytes through the destination image buffer
//      dstRoiSize  Size of the source and destination ROI in pixels
//      pKernel     Pointer to the kernel values ( 32s kernel )
//      kernelSize  Size of the rectangular kernel in pixels.
//      anchor      Anchor cell specifying the rectangular kernel alignment
//                  with respect to the position of the input pixel
//      divisor     The integer value by which the computed result is divided.
*/

LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_8u_C1R, ( const Ipp8u* pSrc, int srcStep,
        Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        IppiSize kernelSize, IppiPoint anchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_8u_C3R, ( const Ipp8u* pSrc, int srcStep,
        Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        IppiSize kernelSize, IppiPoint anchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_8u_C4R, ( const Ipp8u* pSrc, int srcStep,
        Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        IppiSize kernelSize, IppiPoint anchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_8u_AC4R, ( const Ipp8u* pSrc, int srcStep,
        Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        IppiSize kernelSize, IppiPoint anchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_16s_C1R, ( const Ipp16s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        IppiSize kernelSize, IppiPoint anchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_16s_C3R, ( const Ipp16s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        IppiSize kernelSize, IppiPoint anchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_16s_C4R, ( const Ipp16s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        IppiSize kernelSize, IppiPoint anchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_16s_AC4R, ( const Ipp16s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        IppiSize kernelSize, IppiPoint anchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_16u_C1R, ( const Ipp16u* pSrc, int srcStep,
        Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        IppiSize kernelSize, IppiPoint anchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_16u_C3R, ( const Ipp16u* pSrc, int srcStep,
        Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        IppiSize kernelSize, IppiPoint anchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_16u_C4R, ( const Ipp16u* pSrc, int srcStep,
        Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        IppiSize kernelSize, IppiPoint anchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_16u_AC4R, ( const Ipp16u* pSrc, int srcStep,
        Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        IppiSize kernelSize, IppiPoint anchor, int divisor ))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiFilter32f_8u_C1R
//              ippiFilter32f_8u_C3R
//              ippiFilter32f_8u_C4R
//              ippiFilter32f_8u_AC4R
//              ippiFilter32f_16s_C1R    ippiFilter32f_16u_C1R
//              ippiFilter32f_16s_C3R    ippiFilter32f_16u_C3R
//              ippiFilter32f_16s_C4R    ippiFilter32f_16u_C4R
//              ippiFilter32f_16s_AC4R   ippiFilter32f_16u_AC4R
//              ippiFilter32f_8u16s_C1R
//              ippiFilter32f_8u16s_C3R
//              ippiFilter32f_8u16s_C4R
//              ippiFilter32f_8s16s_C1R
//              ippiFilter32f_8s16s_C3R
//              ippiFilter32f_8s16s_C4R
//              ippiFilter32f_8s_C1R
//              ippiFilter32f_8s_C3R
//              ippiFilter32f_8s_C4R
//              ippiFilter32f_32s_C1R
//              ippiFilter32f_32s_C3R
//              ippiFilter32f_32s_C4R
//              ippiFilter_32f_C1R
//              ippiFilter_32f_C3R
//              ippiFilter_32f_C4R
//              ippiFilter_32f_AC4R
//  Purpose:    Filters an image that consists of integer data with use of
//              the rectangular kernel of floating-point values.
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  One of the pointers is NULL
//   ippStsSizeErr     dstRoiSize or kernelSize has a field with zero or negative value
//
//  Parameters:
//      pSrc            Pointer to the source buffer
//      srcStep         Step in bytes through the source image buffer
//      pDst            Pointer to the destination buffer
//      dstStep         Step in bytes through the destination image buffer
//      dstRoiSize      Size of the source and destination ROI in pixels
//      pKernel         Pointer to the kernel values ( 32f kernel )
//      kernelSize      Size of the rectangular kernel in pixels.
//      anchor          Anchor cell specifying the rectangular kernel alignment
//                      with respect to the position of the input pixel
*/
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter32f_8u_C1R, ( const Ipp8u* pSrc, int srcStep,
        Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter32f_8u_C3R, ( const Ipp8u* pSrc, int srcStep,
        Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter32f_8u_C4R, ( const Ipp8u* pSrc, int srcStep,
        Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter32f_8u_AC4R, ( const Ipp8u* pSrc, int srcStep,
        Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter32f_16s_C1R, ( const Ipp16s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter32f_16s_C3R, ( const Ipp16s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter32f_16s_C4R, ( const Ipp16s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter32f_16s_AC4R, ( const Ipp16s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter32f_16u_C1R, ( const Ipp16u* pSrc, int srcStep,
        Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter32f_16u_C3R, ( const Ipp16u* pSrc, int srcStep,
        Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter32f_16u_C4R, ( const Ipp16u* pSrc, int srcStep,
        Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter32f_16u_AC4R, ( const Ipp16u* pSrc, int srcStep,
        Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_32f_C1R, ( const Ipp32f* pSrc, int srcStep,
        Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_32f_C3R, ( const Ipp32f* pSrc, int srcStep,
        Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_32f_C4R, ( const Ipp32f* pSrc, int srcStep,
        Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_32f_AC4R, ( const Ipp32f* pSrc, int srcStep,
        Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter32f_8u16s_C1R, ( const Ipp8u* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter32f_8u16s_C3R, ( const Ipp8u* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter32f_8u16s_C4R, ( const Ipp8u* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter32f_8s16s_C1R, ( const Ipp8s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter32f_8s16s_C3R, ( const Ipp8s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter32f_8s16s_C4R, ( const Ipp8s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter32f_8s_C1R, ( const Ipp8s* pSrc, int srcStep,
        Ipp8s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter32f_8s_C3R, ( const Ipp8s* pSrc, int srcStep,
        Ipp8s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter32f_8s_C4R, ( const Ipp8s* pSrc, int srcStep,
        Ipp8s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter32f_32s_C1R, ( const Ipp32s* pSrc, int srcStep,
        Ipp32s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter32f_32s_C3R, ( const Ipp32s* pSrc, int srcStep,
        Ipp32s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter32f_32s_C4R, ( const Ipp32s* pSrc, int srcStep,
        Ipp32s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor ))

/* ////////////////////////////////////////////////////////////////////////////
//                Separable Filters
//////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////////
//   Names:     ippiFilterColumn_8u_C1R
//              ippiFilterColumn_8u_C3R
//              ippiFilterColumn_8u_C4R
//              ippiFilterColumn_8u_AC4R
//              ippiFilterColumn_16s_C1R    ippiFilterColumn_16u_C1R
//              ippiFilterColumn_16s_C3R    ippiFilterColumn_16u_C3R
//              ippiFilterColumn_16s_C4R    ippiFilterColumn_16u_C4R
//              ippiFilterColumn_16s_AC4R   ippiFilterColumn_16u_AC4R
//
//  Purpose:    Filters an image using a spatial 32s kernel consisting of a
//              single column
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  One of the pointers is NULL
//   ippStsSizeErr     dstRoiSize has a field with zero or negative value, or
//                     kernelSize value is zero or negative
//   ippStsDivisorErr  divisor value is zero, function execution is interrupted
//
//  Parameters:
//      pSrc        Pointer to the source buffer
//      srcStep     Step in bytes through the source image buffer
//      pDst        Pointer to the destination buffer
//      dstStep     Step in bytes through the destination image buffer
//      dstRoiSize  Size of the source and destination ROI in pixels
//      pKernel     Pointer to the column kernel values ( 32s kernel )
//      kernelSize  Size of the column kernel in pixels.
//      yAnchor     Anchor cell specifying the kernel vertical alignment with
//                  respect to the position of the input pixel
//      divisor     The integer value by which the computed result is divided.
*/
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn_8u_C1R, ( const Ipp8u* pSrc,
        int srcStep, Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32s* pKernel, int kernelSize, int yAnchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn_8u_C3R, ( const Ipp8u* pSrc,
        int srcStep, Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32s* pKernel, int kernelSize, int yAnchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn_8u_C4R, ( const Ipp8u* pSrc,
        int srcStep, Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32s* pKernel, int kernelSize, int yAnchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn_8u_AC4R, ( const Ipp8u* pSrc,
        int srcStep, Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32s* pKernel, int kernelSize, int yAnchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn_16s_C1R, ( const Ipp16s* pSrc,
        int srcStep, Ipp16s* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32s* pKernel, int kernelSize, int yAnchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn_16s_C3R, ( const Ipp16s* pSrc,
        int srcStep, Ipp16s* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32s* pKernel, int kernelSize, int yAnchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn_16s_C4R, ( const Ipp16s* pSrc,
        int srcStep, Ipp16s* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32s* pKernel, int kernelSize, int yAnchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn_16s_AC4R, ( const Ipp16s* pSrc,
        int srcStep, Ipp16s* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32s* pKernel, int kernelSize, int yAnchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn_16u_C1R, ( const Ipp16u* pSrc,
        int srcStep, Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32s* pKernel, int kernelSize, int yAnchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn_16u_C3R, ( const Ipp16u* pSrc,
        int srcStep, Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32s* pKernel, int kernelSize, int yAnchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn_16u_C4R, ( const Ipp16u* pSrc,
        int srcStep, Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32s* pKernel, int kernelSize, int yAnchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn_16u_AC4R, ( const Ipp16u* pSrc,
        int srcStep, Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32s* pKernel, int kernelSize, int yAnchor, int divisor ))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiFilterColumn32f_8u_C1R
//              ippiFilterColumn32f_8u_C3R
//              ippiFilterColumn32f_8u_C4R
//              ippiFilterColumn32f_8u_AC4R
//              ippiFilterColumn32f_16s_C1R    ippiFilterColumn32f_16u_C1R
//              ippiFilterColumn32f_16s_C3R    ippiFilterColumn32f_16u_C3R
//              ippiFilterColumn32f_16s_C4R    ippiFilterColumn32f_16u_C4R
//              ippiFilterColumn32f_16s_AC4R   ippiFilterColumn32f_16u_AC4R
//              ippiFilterColumn_32f_C1R
//              ippiFilterColumn_32f_C3R
//              ippiFilterColumn_32f_C4R
//              ippiFilterColumn_32f_AC4R
//              ippiFilterColumn_64f_C1R
//
//  Purpose:    Filters an image using a spatial 32f kernel consisting of a
//              single column
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  Some of pointers to pSrc, pDst or pKernel are NULL
//   ippStsSizeErr     dstRoiSize has a field with zero or negative value, or
//                     kernelSize value is zero or negative
//
//  Parameters:
//      pSrc        Pointer to the source buffer
//      srcStep     Step in bytes through the source image buffer
//      pDst        Pointer to the destination buffer
//      dstStep     Step in bytes through the destination image buffer
//      dstRoiSize  Size of the source and destination ROI in pixels
//      pKernel     Pointer to the column kernel values ( 32f kernel )
//      kernelSize  Size of the column kernel in pixels.
//      yAnchor     Anchor cell specifying the kernel vertical alignment with
//                  respect to the position of the input pixel
*/
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn32f_8u_C1R, ( const Ipp8u* pSrc,
        int srcStep, Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32f* pKernel, int kernelSize, int yAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn32f_8u_C3R, ( const Ipp8u* pSrc,
        int srcStep, Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32f* pKernel, int kernelSize, int yAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn32f_8u_C4R, ( const Ipp8u* pSrc,
        int srcStep, Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32f* pKernel, int kernelSize, int yAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn32f_8u_AC4R, ( const Ipp8u* pSrc,
        int srcStep, Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32f* pKernel, int kernelSize, int yAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn32f_16s_C1R, ( const Ipp16s* pSrc,
        int srcStep, Ipp16s* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32f* pKernel, int kernelSize, int yAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn32f_16s_C3R, ( const Ipp16s* pSrc,
        int srcStep, Ipp16s* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32f* pKernel, int kernelSize, int yAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn32f_16s_C4R, ( const Ipp16s* pSrc,
        int srcStep, Ipp16s* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32f* pKernel, int kernelSize, int yAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn32f_16s_AC4R, ( const Ipp16s* pSrc,
        int srcStep, Ipp16s* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32f* pKernel, int kernelSize, int yAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn32f_16u_C1R, ( const Ipp16u* pSrc,
        int srcStep, Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32f* pKernel, int kernelSize, int yAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn32f_16u_C3R, ( const Ipp16u* pSrc,
        int srcStep, Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32f* pKernel, int kernelSize, int yAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn32f_16u_C4R, ( const Ipp16u* pSrc,
        int srcStep, Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32f* pKernel, int kernelSize, int yAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn32f_16u_AC4R, ( const Ipp16u* pSrc,
        int srcStep, Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32f* pKernel, int kernelSize, int yAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn_32f_C1R, ( const Ipp32f* pSrc,
        int srcStep, Ipp32f* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32f* pKernel, int kernelSize, int yAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn_32f_C3R, ( const Ipp32f* pSrc,
        int srcStep, Ipp32f* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32f* pKernel, int kernelSize, int yAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn_32f_C4R, ( const Ipp32f* pSrc,
        int srcStep, Ipp32f* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32f* pKernel, int kernelSize, int yAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterColumn_32f_AC4R, ( const Ipp32f* pSrc,
        int srcStep, Ipp32f* pDst, int dstStep, IppiSize dstRoiSize,
        const Ipp32f* pKernel, int kernelSize, int yAnchor ))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiFilterRow_8u_C1R
//              ippiFilterRow_8u_C3R
//              ippiFilterRow_8u_C4R
//              ippiFilterRow_8u_AC4R
//              ippiFilterRow_16s_C1R    ippiFilterRow_16u_C1R
//              ippiFilterRow_16s_C3R    ippiFilterRow_16u_C3R
//              ippiFilterRow_16s_C4R    ippiFilterRow_16u_C4R
//              ippiFilterRow_16s_AC4R   ippiFilterRow_16u_AC4R
//
//  Purpose:   Filters an image using a spatial 32s kernel consisting of a
//             single row
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  One of the pointers is NULL
//   ippStsSizeErr     dstRoiSize has a field with zero or negative value, or
//                     kernelSize value is zero or negative
//   ippStsDivisorErr  divisor value is zero, function execution is interrupted
//
//  Parameters:
//      pSrc        Pointer to the source buffer
//      srcStep     Step in bytes through the source image buffer
//      pDst        Pointer to the destination buffer
//      dstStep     Step in bytes through the destination image buffer
//      dstRoiSize  Size of the source and destination ROI in pixels
//      pKernel     Pointer to the row kernel values ( 32s kernel )
//      kernelSize  Size of the row kernel in pixels.
//      xAnchor     Anchor cell specifying the kernel horizontal alignment with
//                  respect to the position of the input pixel.
//      divisor     The integer value by which the computed result is divided.
*/
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow_8u_C1R, ( const Ipp8u* pSrc, int srcStep,
        Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        int kernelSize, int xAnchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow_8u_C3R, ( const Ipp8u* pSrc, int srcStep,
        Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        int kernelSize, int xAnchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow_8u_C4R, ( const Ipp8u* pSrc, int srcStep,
        Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        int kernelSize, int xAnchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow_8u_AC4R, ( const Ipp8u* pSrc, int srcStep,
        Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        int kernelSize, int xAnchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow_16s_C1R, ( const Ipp16s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        int kernelSize, int xAnchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow_16s_C3R, ( const Ipp16s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        int kernelSize, int xAnchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow_16s_C4R, ( const Ipp16s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        int kernelSize, int xAnchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow_16s_AC4R, ( const Ipp16s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        int kernelSize, int xAnchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow_16u_C1R, ( const Ipp16u* pSrc, int srcStep,
        Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        int kernelSize, int xAnchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow_16u_C3R, ( const Ipp16u* pSrc, int srcStep,
        Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        int kernelSize, int xAnchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow_16u_C4R, ( const Ipp16u* pSrc, int srcStep,
        Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        int kernelSize, int xAnchor, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow_16u_AC4R, ( const Ipp16u* pSrc, int srcStep,
        Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        int kernelSize, int xAnchor, int divisor ))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiFilterRow32f_8u_C1R
//              ippiFilterRow32f_8u_C3R
//              ippiFilterRow32f_8u_C4R
//              ippiFilterRow32f_8u_AC4R
//              ippiFilterRow32f_16s_C1R    ippiFilterRow32f_16u_C1R
//              ippiFilterRow32f_16s_C3R    ippiFilterRow32f_16u_C3R
//              ippiFilterRow32f_16s_C4R    ippiFilterRow32f_16u_C4R
//              ippiFilterRow32f_16s_AC4R   ippiFilterRow32f_16u_AC4R
//              ippiFilterRow_32f_C1R
//              ippiFilterRow_32f_C3R
//              ippiFilterRow_32f_C4R
//              ippiFilterRow_32f_AC4R
//              ippiFilterRow_64f_C1R
//
//  Purpose:   Filters an image using a spatial 32f kernel consisting of a
//             single row
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  One of the pointers is NULL
//   ippStsSizeErr     dstRoiSize has a field with zero or negative value, or
//                     kernelSize value is zero or negative
//   ippStsStepErr     srcStep is less than required (roiWidth+kernelWidth-1)*sizeof(<flavor>)*nChannels, or
//                     dstStep is less than dstWidth*sizeof(<flavor>)*nChannels
//
//  Parameters:
//      pSrc        Pointer to the source buffer;
//      srcStep     Step in bytes through the source image buffer;
//      pDst        Pointer to the destination buffer;
//      dstStep     Step in bytes through the destination image buffer;
//      dstRoiSize  Size of the source and destination ROI in pixels;
//      pKernel     Pointer to the row kernel values ( 32f kernel );
//      kernelSize  Size of the row kernel in pixels;
//      xAnchor     Anchor cell specifying the kernel horizontal alignment with
//                  respect to the position of the input pixel.
*/
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow32f_8u_C1R, ( const Ipp8u* pSrc, int srcStep,
        Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        int kernelSize, int xAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow32f_8u_C3R, ( const Ipp8u* pSrc, int srcStep,
        Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        int kernelSize, int xAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow32f_8u_C4R, ( const Ipp8u* pSrc, int srcStep,
        Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        int kernelSize, int xAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow32f_8u_AC4R, ( const Ipp8u* pSrc, int srcStep,
        Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        int kernelSize, int xAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow32f_16s_C1R, ( const Ipp16s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        int kernelSize, int xAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow32f_16s_C3R, ( const Ipp16s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        int kernelSize, int xAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow32f_16s_C4R, ( const Ipp16s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        int kernelSize, int xAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow32f_16s_AC4R, ( const Ipp16s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        int kernelSize, int xAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow32f_16u_C1R, ( const Ipp16u* pSrc, int srcStep,
        Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        int kernelSize, int xAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow32f_16u_C3R, ( const Ipp16u* pSrc, int srcStep,
        Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        int kernelSize, int xAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow32f_16u_C4R, ( const Ipp16u* pSrc, int srcStep,
        Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        int kernelSize, int xAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow32f_16u_AC4R, ( const Ipp16u* pSrc, int srcStep,
        Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        int kernelSize, int xAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow_32f_C1R, ( const Ipp32f* pSrc, int srcStep,
        Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        int kernelSize, int xAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow_32f_C3R, ( const Ipp32f* pSrc, int srcStep,
        Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        int kernelSize, int xAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow_32f_C4R, ( const Ipp32f* pSrc, int srcStep,
        Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        int kernelSize, int xAnchor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRow_32f_AC4R, ( const Ipp32f* pSrc, int srcStep,
        Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        int kernelSize, int xAnchor ))


/* ////////////////////////////////////////////////////////////////////////////
//   Names:     ippiConvFull_32f_C1R
//              ippiConvFull_32f_C3R
//              ippiConvFull_32f_AC4R
//              ippiConvFull_16s_C1R
//              ippiConvFull_16s_C3R
//              ippiConvFull_16s_AC4R
//              ippiConvFull_8u_C1R
//              ippiConvFull_8u_C3R
//              ippiConvFull_8u_AC4R
//
//  Purpose: Performs full 2-D convolution of matrices (images). If IppiSize's
//           of matrices are Wa*Ha and Wb*Hb correspondingly, then the
//           IppiSize of the resulting matrix (image) will be
//              (Wa+Wb-1)*(Ha+Hb-1).
//           For big data size, the function uses 2D FFT algorithm.
//
//  Returns:
//      ippStsNoErr       OK;
//      ippStsNullPtrErr  One of the pointers pSrc1, pSrc2, pDst is NULL;
//      ippStsSizeErr     src1Size, src2Size has at least one field with
//                                                zero or negative value;
//      ippStsStepErr     One of the step values is zero or negative;
///     ippStsDivisorErr  divisor value is zero, function execution is interrupted;
//      ippStsMemAllocErr Memory allocation error.
//
//  Parameters:
//      pSrc1       Pointer to the source buffer 1;
//      src1Step    Step in bytes through the source image buffer 1;
//      src1Size    Size of the source buffer 1 in pixels;
//      pSrc2       Pointer to the source buffer 2;
//      src2Step    Step in bytes through the source image buffer 2;
//      Src2Size    Size of the source buffer 2 in pixels;
//      pDst        Pointer to the destination buffer;
//      dstStep     Step in bytes through the destination image buffer;
//      divisor     The integer value by which the computed result is divided
//                  (in case of 8u or 16s data).
*/

LEGACY90IPPAPI( IppStatus, legacy90ippiConvFull_32f_C1R,( const Ipp32f* pSrc1, int src1Step,
        IppiSize src1Size, const Ipp32f* pSrc2, int src2Step, IppiSize src2Size,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiConvFull_32f_C3R,( const Ipp32f* pSrc1, int src1Step,
        IppiSize src1Size, const Ipp32f* pSrc2, int src2Step, IppiSize src2Size,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiConvFull_32f_AC4R,( const Ipp32f* pSrc1, int src1Step,
        IppiSize src1Size, const Ipp32f* pSrc2, int src2Step, IppiSize src2Size,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiConvFull_16s_C1R,( const Ipp16s* pSrc1, int src1Step,
        IppiSize src1Size, const Ipp16s* pSrc2, int src2Step, IppiSize src2Size,
        Ipp16s* pDst, int dstStep, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiConvFull_16s_C3R,( const Ipp16s* pSrc1, int src1Step,
        IppiSize src1Size, const Ipp16s* pSrc2, int src2Step, IppiSize src2Size,
        Ipp16s* pDst, int dstStep, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiConvFull_16s_AC4R,( const Ipp16s* pSrc1, int src1Step,
        IppiSize src1Size, const Ipp16s* pSrc2, int src2Step, IppiSize src2Size,
        Ipp16s* pDst, int dstStep, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiConvFull_8u_C1R,( const Ipp8u* pSrc1, int src1Step,
        IppiSize src1Size, const Ipp8u* pSrc2, int src2Step, IppiSize src2Size,
        Ipp8u* pDst, int dstStep, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiConvFull_8u_C3R,( const Ipp8u* pSrc1, int src1Step,
        IppiSize src1Size, const Ipp8u* pSrc2, int src2Step, IppiSize src2Size,
        Ipp8u* pDst, int dstStep, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiConvFull_8u_AC4R,( const Ipp8u* pSrc1, int src1Step,
        IppiSize src1Size, const Ipp8u* pSrc2, int src2Step, IppiSize src2Size,
        Ipp8u* pDst, int dstStep, int divisor ))



/* ////////////////////////////////////////////////////////////////////////////
//   Names:     ippiConvValid_32f_C1R
//              ippiConvValid_32f_C3R
//              ippiConvValid_32f_AC4R
//              ippiConvValid_16s_C1R
//              ippiConvValid_16s_C3R
//              ippiConvValid_16s_AC4R
//              ippiConvValid_8u_C1R
//              ippiConvValid_8u_C3R
//              ippiConvValid_8u_AC4R
//
//  Purpose: Performs the VALID 2-D convolution of matrices (images).
//           If IppiSize's of matrices (images) are Wa*Ha and Wb*Hb
//           correspondingly, then the IppiSize of the resulting matrix
//           (image) will be (|Wa-Wb|+1)*(|Ha-Hb|+1).
//           For big data size, the function uses 2D FFT algorithm.
//
//  Returns:
//      ippStsNoErr       OK;
//      ippStsNullPtrErr  One of the pointers pSrc1, pSrc2, pDst is NULL;
//      ippStsSizeErr     src1Size, src2Size has at least one field with
//                                                zero or negative value;
//      ippStsStepErr     One of the step values is zero or negative;
///     ippStsDivisorErr  divisor value is zero, function execution is interrupted;
//      ippStsMemAllocErr Memory allocation error.
//
//  Parameters:
//      pSrc1       Pointer to the source buffer 1;
//      src1Step    Step in bytes through the source image buffer 1;
//      src1Size    Size of the source buffer 1 in pixels;
//      pSrc2       Pointer to the source buffer 2;
//      src2Step    Step in bytes through the source image buffer 2;
//      src2Size    Size of the source buffer 2 in pixels;
//      pDst        Pointer to the destination buffer;
//      dstStep     Step in bytes through the destination image buffer;
//      divisor     The integer value by which the computed result is divided
//                  (in case of 8u or 16s data).
*/

LEGACY90IPPAPI( IppStatus, legacy90ippiConvValid_32f_C1R,( const Ipp32f* pSrc1, int src1Step,
        IppiSize src1Size, const Ipp32f* pSrc2, int src2Step, IppiSize src2Size,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiConvValid_32f_C3R,( const Ipp32f* pSrc1, int src1Step,
        IppiSize src1Size, const Ipp32f* pSrc2, int src2Step, IppiSize src2Size,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiConvValid_32f_AC4R,( const Ipp32f* pSrc1, int src1Step,
        IppiSize src1Size, const Ipp32f* pSrc2, int src2Step, IppiSize src2Size,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiConvValid_16s_C1R,( const Ipp16s* pSrc1, int src1Step,
        IppiSize src1Size, const Ipp16s* pSrc2, int src2Step, IppiSize src2Size,
        Ipp16s* pDst, int dstStep, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiConvValid_16s_C3R,( const Ipp16s* pSrc1, int src1Step,
        IppiSize src1Size, const Ipp16s* pSrc2, int src2Step, IppiSize src2Size,
        Ipp16s* pDst, int dstStep, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiConvValid_16s_AC4R,( const Ipp16s* pSrc1, int src1Step,
        IppiSize src1Size, const Ipp16s* pSrc2, int src2Step, IppiSize src2Size,
        Ipp16s* pDst, int dstStep, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiConvValid_8u_C1R,( const Ipp8u* pSrc1, int src1Step,
        IppiSize src1Size, const Ipp8u* pSrc2, int src2Step, IppiSize src2Size,
        Ipp8u* pDst, int dstStep, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiConvValid_8u_C3R,( const Ipp8u* pSrc1, int src1Step,
        IppiSize src1Size, const Ipp8u* pSrc2, int src2Step, IppiSize src2Size,
        Ipp8u* pDst, int dstStep, int divisor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiConvValid_8u_AC4R,( const Ipp8u* pSrc1, int src1Step,
        IppiSize src1Size, const Ipp8u* pSrc2, int src2Step, IppiSize src2Size,
        Ipp8u* pDst, int dstStep, int divisor ))



/*///////////////////////////////////////////////////////////////////////////////////////
//  Names:
//      ippiCrossCorrFull_Norm_32f_C1R,         ippiCrossCorrSame_Norm_32f_C1R,
//      ippiCrossCorrFull_Norm_32f_C3R,         ippiCrossCorrSame_Norm_32f_C3R,
//      ippiCrossCorrFull_Norm_32f_C4R,         ippiCrossCorrSame_Norm_32f_C4R,
//      ippiCrossCorrFull_Norm_32f_AC4R,        ippiCrossCorrSame_Norm_32f_AC4R,
//      ippiCrossCorrFull_Norm_8u_C1RSfs,       ippiCrossCorrSame_Norm_8u_C1RSfs,
//      ippiCrossCorrFull_Norm_8u_C3RSfs,       ippiCrossCorrSame_Norm_8u_C3RSfs,
//      ippiCrossCorrFull_Norm_8u_C4RSfs,       ippiCrossCorrSame_Norm_8u_C4RSfs,
//      ippiCrossCorrFull_Norm_8u_AC4RSfs,      ippiCrossCorrSame_Norm_8u_AC4RSfs,
//      ippiCrossCorrFull_Norm_8u32f_C1R,       ippiCrossCorrSame_Norm_8u32f_C1R,
//      ippiCrossCorrFull_Norm_8u32f_C3R,       ippiCrossCorrSame_Norm_8u32f_C3R,
//      ippiCrossCorrFull_Norm_8u32f_C4R,       ippiCrossCorrSame_Norm_8u32f_C4R,
//      ippiCrossCorrFull_Norm_8u32f_AC4R,      ippiCrossCorrSame_Norm_8u32f_AC4R,
//      ippiCrossCorrFull_Norm_8s32f_C1R,       ippiCrossCorrSame_Norm_8s32f_C1R,
//      ippiCrossCorrFull_Norm_8s32f_C3R,       ippiCrossCorrSame_Norm_8s32f_C3R,
//      ippiCrossCorrFull_Norm_8s32f_C4R,       ippiCrossCorrSame_Norm_8s32f_C4R,
//      ippiCrossCorrFull_Norm_8s32f_AC4R,      ippiCrossCorrSame_Norm_8s32f_AC4R,
//      ippiCrossCorrFull_Norm_16u32f_C1R,      ippiCrossCorrSame_Norm_16u32f_C1R,
//      ippiCrossCorrFull_Norm_16u32f_C3R,      ippiCrossCorrSame_Norm_16u32f_C3R,
//      ippiCrossCorrFull_Norm_16u32f_C4R,      ippiCrossCorrSame_Norm_16u32f_C4R,
//      ippiCrossCorrFull_Norm_16u32f_AC4R,     ippiCrossCorrSame_Norm_16u32f_AC4R,
//
//      ippiCrossCorrValid_Norm_32f_C1R,
//      ippiCrossCorrValid_Norm_32f_C3R,
//      ippiCrossCorrValid_Norm_32f_C4R,
//      ippiCrossCorrValid_Norm_32f_AC4R,
//      ippiCrossCorrValid_Norm_8u_C1RSfs,
//      ippiCrossCorrValid_Norm_8u_C3RSfs,
//      ippiCrossCorrValid_Norm_8u_C4RSfs,
//      ippiCrossCorrValid_Norm_8u_AC4RSfs,
//      ippiCrossCorrValid_Norm_8u32f_C1R,
//      ippiCrossCorrValid_Norm_8u32f_C3R,
//      ippiCrossCorrValid_Norm_8u32f_C4R,
//      ippiCrossCorrValid_Norm_8u32f_AC4R.
//      ippiCrossCorrValid_Norm_8s32f_C1R,
//      ippiCrossCorrValid_Norm_8s32f_C3R,
//      ippiCrossCorrValid_Norm_8s32f_C4R,
//      ippiCrossCorrValid_Norm_8s32f_AC4R.
//
//  Purpose: Computes normalized cross-correlation between
//           an image and a template (another image).
//           The cross-correlation values are the image similarity measures: the
//           higher cross-correlation at a particular pixel, the more
//           similarity between the template and the image in the neighborhood
//           of the pixel. If IppiSize's of image and template are Wa * Ha and
//           Wb * Hb correspondingly, then the IppiSize of the resulting
//           matrix with normalized cross-correlation coefficients will be
//           a) in case of 'Full' suffix:
//              ( Wa + Wb - 1 )*( Ha + Hb - 1 ).
//           b) in case of 'Same' suffix:
//              ( Wa )*( Ha ).
//           c) in case of 'Valid' suffix:
//              ( Wa - Wb + 1 )*( Ha - Hb + 1 ).
//  Notice:
//           suffix 'R' (ROI) means only scanline alignment (srcStep), in
//           'Same' and 'Full' cases no any requirements for data outside
//           the ROI - it's assumed that template and source images are zero padded.
//
//  Parameters:
//      pSrc        Pointer to the source image ROI;
//      srcStep     Step in bytes through the source image buffer;
//      srcRoiSize  Size of the source ROI in pixels;
//      pTpl        Pointer to the template ( feature ) image ROI;
//      tplStep     Step in bytes through the template image buffer;
//      tplRoiSize  Size of the template ROI in pixels;
//      pDst        Pointer to the destination buffer;
//      dstStep     Step in bytes through the destination image buffer;
//      scaleFactor Scale factor value ( integer output data ).
//
//  Returns:
//   ippStsNoErr        OK
//   ippStsNullPtrErr   One of the pointers to pSrc, pDst or pTpl is NULL;
//   ippStsSizeErr      srcRoiSize or tplRoiSize has a field with zero or
//                      negative value,
//                      or srcRoiSize has a field with value smaller than value
//                      of the corresponding field of tplRoiSize;
//   ippStsStepErr      One of the step values is less than or equal to zero;
//   ippStsMemAllocErr  Memory allocation for internal buffers fails.
*/

LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_Norm_32f_C1R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_Norm_32f_C3R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_Norm_32f_AC4R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_Norm_8u32f_C1R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_Norm_8u32f_C3R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_Norm_8u32f_AC4R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_Norm_8u_C1RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_Norm_8u_C3RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_Norm_8u_AC4RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_Norm_16u32f_C1R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_Norm_16u32f_C3R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_Norm_16u32f_AC4R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_Norm_16u32f_C4R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_Norm_32f_C4R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_Norm_8u32f_C4R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_Norm_8s32f_C1R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_Norm_8s32f_C3R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_Norm_8s32f_C4R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_Norm_8s32f_AC4R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_Norm_8u_C4RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))

LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_Norm_32f_C1R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_Norm_32f_C3R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_Norm_32f_AC4R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_Norm_8u32f_C1R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_Norm_8u32f_C3R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_Norm_8u32f_AC4R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_Norm_8u_C1RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_Norm_8u_C3RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_Norm_8u_AC4RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_Norm_32f_C4R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_Norm_8u32f_C4R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_Norm_8s32f_C1R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_Norm_8s32f_C3R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_Norm_8s32f_C4R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_Norm_8s32f_AC4R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_Norm_8u_C4RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_Norm_16u32f_C1R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_Norm_16u32f_C3R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_Norm_16u32f_AC4R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_Norm_16u32f_C4R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))

LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_Norm_32f_C1R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_Norm_32f_C3R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_Norm_32f_AC4R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_Norm_8u32f_C1R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_Norm_8u32f_C3R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_Norm_8u32f_AC4R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_Norm_8u_C1RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_Norm_8u_C3RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_Norm_8u_AC4RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_Norm_32f_C4R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_Norm_8u32f_C4R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_Norm_8s32f_C1R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_Norm_8s32f_C3R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_Norm_8s32f_C4R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_Norm_8s32f_AC4R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_Norm_8u_C4RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_Norm_16u32f_C1R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_Norm_16u32f_C3R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_Norm_16u32f_AC4R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_Norm_16u32f_C4R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))

/* /////////////////////////////////////////////////////////////////////////////////
//  Names:
//      ippiCrossCorrFull_NormLevel_32f_C1R,    ippiCrossCorrSame_NormLevel_32f_C1R,
//      ippiCrossCorrFull_NormLevel_32f_C3R,    ippiCrossCorrSame_NormLevel_32f_C3R,
//      ippiCrossCorrFull_NormLevel_32f_C4R,    ippiCrossCorrSame_NormLevel_32f_C4R,
//      ippiCrossCorrFull_NormLevel_32f_AC4R,   ippiCrossCorrSame_NormLevel_32f_AC4R,
//      ippiCrossCorrFull_NormLevel_8u_C1RSfs,  ippiCrossCorrSame_NormLevel_8u_C1RSfs,
//      ippiCrossCorrFull_NormLevel_8u_C3RSfs,  ippiCrossCorrSame_NormLevel_8u_C3RSfs,
//      ippiCrossCorrFull_NormLevel_8u_C4RSfs,  ippiCrossCorrSame_NormLevel_8u_C4RSfs,
//      ippiCrossCorrFull_NormLevel_8u_AC4RSfs, ippiCrossCorrSame_NormLevel_8u_AC4RSfs,
//      ippiCrossCorrFull_NormLevel_8u32f_C1R,  ippiCrossCorrSame_NormLevel_8u32f_C1R,
//      ippiCrossCorrFull_NormLevel_8u32f_C3R,  ippiCrossCorrSame_NormLevel_8u32f_C3R,
//      ippiCrossCorrFull_NormLevel_8u32f_C4R,  ippiCrossCorrSame_NormLevel_8u32f_C4R,
//      ippiCrossCorrFull_NormLevel_8u32f_AC4R, ippiCrossCorrSame_NormLevel_8u32f_AC4R,
//      ippiCrossCorrFull_NormLevel_8s32f_C1R,  ippiCrossCorrSame_NormLevel_8s32f_C1R,
//      ippiCrossCorrFull_NormLevel_8s32f_C3R,  ippiCrossCorrSame_NormLevel_8s32f_C3R,
//      ippiCrossCorrFull_NormLevel_8s32f_C4R,  ippiCrossCorrSame_NormLevel_8s32f_C4R,
//      ippiCrossCorrFull_NormLevel_8s32f_AC4R, ippiCrossCorrSame_NormLevel_8s32f_AC4R,
//      ippiCrossCorrFull_NormLevel_16u32f_C1R, ippiCrossCorrSame_NormLevel_16u32f_C1R,
//      ippiCrossCorrFull_NormLevel_16u32f_C3R, ippiCrossCorrSame_NormLevel_16u32f_C3R,
//      ippiCrossCorrFull_NormLevel_16u32f_C4R, ippiCrossCorrSame_NormLevel_16u32f_C4R,
//      ippiCrossCorrFull_NormLevel_16u32f_AC4R,ippiCrossCorrSame_NormLevel_16u32f_AC4R,
//
//      ippiCrossCorrValid_NormLevel_32f_C1R,
//      ippiCrossCorrValid_NormLevel_32f_C3R,
//      ippiCrossCorrValid_NormLevel_32f_C4R,
//      ippiCrossCorrValid_NormLevel_32f_AC4R,
//      ippiCrossCorrValid_NormLevel_8u_C1RSfs,
//      ippiCrossCorrValid_NormLevel_8u_C3RSfs,
//      ippiCrossCorrValid_NormLevel_8u_C4RSfs,
//      ippiCrossCorrValid_NormLevel_8u_AC4RSfs,
//      ippiCrossCorrValid_NormLevel_8u32f_C1R,
//      ippiCrossCorrValid_NormLevel_8u32f_C3R,
//      ippiCrossCorrValid_NormLevel_8u32f_C4R,
//      ippiCrossCorrValid_NormLevel_8u32f_AC4R,
//      ippiCrossCorrValid_NormLevel_8s32f_C1R,
//      ippiCrossCorrValid_NormLevel_8s32f_C3R,
//      ippiCrossCorrValid_NormLevel_8s32f_C4R,
//      ippiCrossCorrValid_NormLevel_8s32f_AC4R.
//      ippiCrossCorrValid_NormLevel_16u32f_C1R,
//      ippiCrossCorrValid_NormLevel_16u32f_C3R,
//      ippiCrossCorrValid_NormLevel_16u32f_C4R,
//      ippiCrossCorrValid_NormLevel_16u32f_AC4R.
//
//  Purpose: Computes normalized correlation coefficient between an image
//           and a template.
//           ippiCrossCorr_NormLevel() function allows you to compute the
//           cross-correlation of an image and a template (another image).
//           The cross-correlation values are image similarity measures: the
//           higher cross-correlation at a particular pixel, the more
//           similarity between the template and the image in the neighborhood
//           of the pixel. If IppiSize's of image and template are Wa * Ha and
//           Wb * Hb correspondingly, then the IppiSize of the resulting
//           matrix with normalized cross-correlation coefficients will be
//           a) in case of 'Full' suffix:
//              ( Wa + Wb - 1 )*( Ha + Hb - 1 ).
//           b) in case of 'Same' suffix:
//              ( Wa )*( Ha ).
//           c) in case of 'Valid' suffix:
//              ( Wa - Wb + 1 )*( Ha - Hb + 1 ).
//  Notice:
//           suffix 'R' (ROI) means only scanline alignment (srcStep), in
//           'Same' and 'Full' cases no any requirements for data outstand
//           the ROI - it's assumes that template and src are zero padded.
//           The difference from ippiCrossCorr_Norm() functions is the using
//           of Zero Mean image and Template to avoid brightness impact.
//           (Before the calculation of the cross-correlation coefficients,
//           the mean of the image in the region under the feature is subtracted
//           from every image pixel; the same for the template.)
//
//  Parameters:
//      pSrc        Pointer to the source image ROI;
//      srcStep     Step in bytes through the source image buffer;
//      srcRoiSize  Size of the source ROI in pixels;
//      pTpl        Pointer to the template ( feature ) image ROI;
//      tplStep     Step in bytes through the template image buffer;
//      tplRoiSize  Size of the template ROI in pixels;
//      pDst        Pointer to the destination buffer;
//      dstStep     Step in bytes through the destination image buffer;
//      scaleFactor Scale factor value ( integer output data ).
//
//  Returns:
//   ippStsNoErr        OK
//   ippStsNullPtrErr   One of the pointers to pSrc, pDst or pTpl is NULL;
//   ippStsSizeErr      srcRoiSize or tplRoiSize has a field with zero or
//                      negative value,
//                      or srcRoiSize has a field with value smaller than value
//                      of the corresponding field of tplRoiSize;
//   ippStsStepErr      One of the step values is less than or equal to zero;
//   ippStsMemAllocErr  Memory allocation for internal buffers fails.
*/

LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_NormLevel_32f_C1R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_NormLevel_32f_C3R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_NormLevel_32f_C4R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_NormLevel_32f_AC4R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_NormLevel_8u32f_C1R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_NormLevel_8u32f_C3R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_NormLevel_8u32f_C4R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_NormLevel_8u32f_AC4R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_NormLevel_8s32f_C1R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_NormLevel_8s32f_C3R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_NormLevel_8s32f_C4R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_NormLevel_8s32f_AC4R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_NormLevel_8u_C1RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_NormLevel_8u_C3RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_NormLevel_8u_C4RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_NormLevel_8u_AC4RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_NormLevel_16u32f_C1R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_NormLevel_16u32f_C3R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_NormLevel_16u32f_AC4R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_NormLevel_16u32f_C4R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))

LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_NormLevel_32f_C1R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_NormLevel_32f_C3R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_NormLevel_32f_C4R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_NormLevel_32f_AC4R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_NormLevel_8u32f_C1R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_NormLevel_8u32f_C3R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_NormLevel_8u32f_C4R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_NormLevel_8u32f_AC4R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_NormLevel_8s32f_C1R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_NormLevel_8s32f_C3R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_NormLevel_8s32f_C4R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_NormLevel_8s32f_AC4R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_NormLevel_8u_C1RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_NormLevel_8u_C3RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_NormLevel_8u_C4RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_NormLevel_8u_AC4RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_NormLevel_16u32f_C1R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_NormLevel_16u32f_C3R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_NormLevel_16u32f_AC4R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_NormLevel_16u32f_C4R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))

LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_NormLevel_32f_C1R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_NormLevel_32f_C3R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_NormLevel_32f_C4R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_NormLevel_32f_AC4R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_NormLevel_8u32f_C1R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_NormLevel_8u32f_C3R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_NormLevel_8u32f_C4R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_NormLevel_8u32f_AC4R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_NormLevel_8s32f_C1R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_NormLevel_8s32f_C3R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_NormLevel_8s32f_C4R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_NormLevel_8s32f_AC4R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_NormLevel_8u_C1RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_NormLevel_8u_C3RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_NormLevel_8u_C4RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_NormLevel_8u_AC4RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_NormLevel_16u32f_C1R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_NormLevel_16u32f_C3R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_NormLevel_16u32f_AC4R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrSame_NormLevel_16u32f_C4R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_NormLevel_64f_C1R, ( const Ipp64f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp64f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp64f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrFull_NormLevel_64f_C1R, ( const Ipp64f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp64f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp64f* pDst, int dstStep ))



/* //////////////////////////////////////////////////////////////////////////////////
//  Names:
//      ippiSqrDistanceFull_Norm_32f_C1R,    ippiSqrDistanceSame_Norm_32f_C1R,
//      ippiSqrDistanceFull_Norm_32f_C3R,    ippiSqrDistanceSame_Norm_32f_C3R,
//      ippiSqrDistanceFull_Norm_32f_C4R,    ippiSqrDistanceSame_Norm_32f_C4R,
//      ippiSqrDistanceFull_Norm_32f_AC4R,   ippiSqrDistanceSame_Norm_32f_AC4R,
//      ippiSqrDistanceFull_Norm_8u_C1RSfs,  ippiSqrDistanceSame_Norm_8u_C1RSfs,
//      ippiSqrDistanceFull_Norm_8u_C3RSfs,  ippiSqrDistanceSame_Norm_8u_C3RSfs,
//      ippiSqrDistanceFull_Norm_8u_C4RSfs,  ippiSqrDistanceSame_Norm_8u_C4RSfs,
//      ippiSqrDistanceFull_Norm_8u_AC4RSfs, ippiSqrDistanceSame_Norm_8u_AC4RSfs,
//      ippiSqrDistanceFull_Norm_8u32f_C1R,  ippiSqrDistanceSame_Norm_8u32f_C1R,
//      ippiSqrDistanceFull_Norm_8u32f_C3R,  ippiSqrDistanceSame_Norm_8u32f_C3R,
//      ippiSqrDistanceFull_Norm_8u32f_C4R,  ippiSqrDistanceSame_Norm_8u32f_C4R,
//      ippiSqrDistanceFull_Norm_8u32f_AC4R, ippiSqrDistanceSame_Norm_8u32f_AC4R,
//      ippiSqrDistanceFull_Norm_8s32f_C1R,  ippiSqrDistanceSame_Norm_8s32f_C1R,
//      ippiSqrDistanceFull_Norm_8s32f_C3R,  ippiSqrDistanceSame_Norm_8s32f_C3R,
//      ippiSqrDistanceFull_Norm_8s32f_C4R,  ippiSqrDistanceSame_Norm_8s32f_C4R,
//      ippiSqrDistanceFull_Norm_8s32f_AC4R, ippiSqrDistanceSame_Norm_8s32f_AC4R,
//      ippiSqrDistanceFull_Norm_16u32f_C1R, ippiSqrDistanceSame_Norm_16u32f_C1R,
//      ippiSqrDistanceFull_Norm_16u32f_C3R, ippiSqrDistanceSame_Norm_16u32f_C3R,
//      ippiSqrDistanceFull_Norm_16u32f_C4R, ippiSqrDistanceSame_Norm_16u32f_C4R,
//      ippiSqrDistanceFull_Norm_16u32f_AC4R,ippiSqrDistanceSame_Norm_16u32f_AC4R,
//
//      ippiSqrDistanceValid_Norm_32f_C1R,
//      ippiSqrDistanceValid_Norm_32f_C3R,
//      ippiSqrDistanceValid_Norm_32f_C4R,
//      ippiSqrDistanceValid_Norm_32f_AC4R,
//      ippiSqrDistanceValid_Norm_8u_C1RSfs,
//      ippiSqrDistanceValid_Norm_8u_C3RSfs,
//      ippiSqrDistanceValid_Norm_8u_C4RSfs,
//      ippiSqrDistanceValid_Norm_8u_AC4RSfs,
//      ippiSqrDistanceValid_Norm_8u32f_C1R,
//      ippiSqrDistanceValid_Norm_8u32f_C3R,
//      ippiSqrDistanceValid_Norm_8u32f_C4R,
//      ippiSqrDistanceValid_Norm_8u32f_AC4R.
//      ippiSqrDistanceValid_Norm_16u32f_C1R,
//      ippiSqrDistanceValid_Norm_16u32f_C3R,
//      ippiSqrDistanceValid_Norm_16u32f_C4R,
//      ippiSqrDistanceValid_Norm_16u32f_AC4R.
//      ippiSqrDistanceValid_Norm_8s32f_C1R,
//      ippiSqrDistanceValid_Norm_8s32f_C3R,
//      ippiSqrDistanceValid_Norm_8s32f_C4R,
//      ippiSqrDistanceValid_Norm_8s32f_AC4R.
//
//  Purpose: Computes normalized Euclidean distance, or Sum of Squared
//           Distance (SSD) of an image and a template (another image).
//               The SSD values are image similarity measures: the smaller
//           value of SSD at a particular pixel, the more similarity between
//           the template and the image in the neighborhood of the pixel.
//               If IppiSize's of image and template are Wa * Ha and
//           Wb * Hb correspondingly, then the IppiSize of the resulting
//           matrix with normalized SSD coefficients will be
//           a) in case of 'Full' suffix:
//              ( Wa + Wb - 1 )*( Ha + Hb - 1 ).
//           b) in case of 'Same' suffix:
//              ( Wa )*( Ha ).
//           c) in case of 'Valid' suffix:
//              ( Wa - Wb + 1 )*( Ha - Hb + 1 ).
//  Notice:
//           suffix 'R' (ROI) means only scanline alignment (srcStep), in
//           'Same' and 'Full' cases no any requirements for data outstand
//           the ROI - it's assumed that template and source images are zero padded.
//
//  Parameters:
//      pSrc        Pointer to the source image ROI;
//      srcStep     Step in bytes through the source image buffer;
//      srcRoiSize  Size of the source ROI in pixels;
//      pTpl        Pointer to the template ( feature ) image ROI;
//      tplStep     Step in bytes through the template image buffer;
//      tplRoiSize  Size of the template ROI in pixels;
//      pDst        Pointer to the destination buffer;
//      dstStep     Step in bytes through the destination image buffer;
//      scaleFactor Scale factor value ( integer output data ).
//
//  Returns:
//   ippStsNoErr        OK
//   ippStsNullPtrErr   One of the pointers to pSrc, pDst or pTpl is NULL;
//   ippStsSizeErr      srcRoiSize or tplRoiSize has a field with zero or
//                      negative value,
//                      or srcRoiSize has a field with value smaller than value
//                      of the corresponding field of tplRoiSize;
//   ippStsStepErr      One of the step values is less than or equal to zero;
//   ippStsMemAllocErr  Memory allocation for internal buffers fails.
*/

LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceFull_Norm_32f_C1R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceFull_Norm_32f_C3R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceFull_Norm_32f_AC4R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceFull_Norm_8u32f_C1R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceFull_Norm_8u32f_C3R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceFull_Norm_8u32f_AC4R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceFull_Norm_8u_C1RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceFull_Norm_8u_C3RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceFull_Norm_8u_AC4RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))

LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceValid_Norm_32f_C1R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceValid_Norm_32f_C3R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceValid_Norm_32f_AC4R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceValid_Norm_8u32f_C1R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceValid_Norm_8u32f_C3R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceValid_Norm_8u32f_AC4R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceValid_Norm_8u_C1RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceValid_Norm_8u_C3RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceValid_Norm_8u_AC4RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))

LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceSame_Norm_32f_C1R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceSame_Norm_32f_C3R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceSame_Norm_32f_AC4R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceSame_Norm_8u32f_C1R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceSame_Norm_8u32f_C3R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceSame_Norm_8u32f_AC4R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceSame_Norm_8u_C1RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceSame_Norm_8u_C3RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceSame_Norm_8u_AC4RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))

LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceFull_Norm_32f_C4R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceFull_Norm_8u32f_C4R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceFull_Norm_8s32f_C1R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceFull_Norm_8s32f_C3R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceFull_Norm_8s32f_C4R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceFull_Norm_8s32f_AC4R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceFull_Norm_8u_C4RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceFull_Norm_16u32f_C1R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceFull_Norm_16u32f_C3R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceFull_Norm_16u32f_AC4R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceFull_Norm_16u32f_C4R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))

LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceValid_Norm_32f_C4R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceValid_Norm_8u32f_C4R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceValid_Norm_8s32f_C1R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceValid_Norm_8s32f_C3R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceValid_Norm_8s32f_C4R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceValid_Norm_8s32f_AC4R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceValid_Norm_8u_C4RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceValid_Norm_16u32f_C1R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceValid_Norm_16u32f_C3R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceValid_Norm_16u32f_AC4R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceValid_Norm_16u32f_C4R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))

LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceSame_Norm_32f_C4R, ( const Ipp32f* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceSame_Norm_8u32f_C4R, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceSame_Norm_8s32f_C1R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceSame_Norm_8s32f_C3R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceSame_Norm_8s32f_C4R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceSame_Norm_8s32f_AC4R, ( const Ipp8s* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceSame_Norm_8u_C4RSfs, ( const Ipp8u* pSrc, int srcStep,
        IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
        Ipp8u* pDst, int dstStep, int scaleFactor ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceSame_Norm_16u32f_C1R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceSame_Norm_16u32f_C3R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceSame_Norm_16u32f_AC4R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiSqrDistanceSame_Norm_16u32f_C4R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
/*
///////////////////////   Version without normalization ///////////////////////
//
//  Names:
//      ippiCrossCorrValid_32f_C1R
//      ippiCrossCorrValid_8u32f_C1R
//      ippiCrossCorrValid_8s32f_C1R
//      ippiCrossCorrValid_16u32f_C1R
//
//  Arguments:
//      pSrc        - pointer to the source image ROI;
//      srcStep     - step in bytes through the source image buffer;
//      srcRoiSize  - size of the source ROI in pixels;
//      pTpl        - pointer to the template ( feature ) image ROI;
//      tplStep     - step in bytes through the template image buffer;
//      tplRoiSize  - size of the template ROI in pixels;
//      pDst        - pointer to the destination buffer;
//      dstStep     - step in bytes through the destination image buffer;
//
//  Return:
//   ippStsNoErr        - Ok
//   ippStsNullPtrErr   - at least one of the pointers to pSrc, pDst or pTpl is NULL;
//   ippStsSizeErr      - at least one of the sizes of srcRoiSize or tplRoiSize is less or equal zero,
//                        or at least one of the sizes of srcRoiSize is smaller than the corresponding
//                        size of the tplRoiSize;
//   ippStsStepErr      - at least one of the srcStep, tplStep or dstStep is less or equal zero;
//   ippStsMemAllocErr  - an error occurs during allocation memory for internal buffers.
//
//  Purpose: ippiCrossCorr() function allows you to compute the
//           cross-correlation of an image and a template (another image).
//           The cross-correlation values are image similarity measures: the
//           higher cross-correlation at a particular pixel, the more
//           similarity between the template and the image in the neighborhood
//           of the pixel.
//
//           If IppiSize's of image and template are Wa * Ha and
//           Wb * Hb correspondingly, then the IppiSize of the resulting
//           matrice with coefficients will be
//
//                      ( Wa - Wb + 1 )*( Ha - Hb + 1 )
//
//           ('Valid' case in MatLab notation)
//  Notice:
//           suffix 'R' (ROI) means only scanline alingment (srcStep), in
//           'Same' and 'Full' cases no any requirements for data outstand
//           the ROI - it's assumes that template and src are zero padded.
*/
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_32f_C1R, ( const Ipp32f* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_8u32f_C1R, ( const Ipp8u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_8s32f_C1R, ( const Ipp8s* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp8s* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
LEGACY90IPPAPI( IppStatus, legacy90ippiCrossCorrValid_16u32f_C1R, ( const Ipp16u* pSrc,
        int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep,
        IppiSize tplRoiSize, Ipp32f* pDst, int dstStep ))
/* /////////////////////////////////////////////////////////////////////////////
//                   Threshold operations
///////////////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////////////////////
//  Name:  ippiAddRandUniform_Direct_8u_C1IR,  ippiAddRandUniform_Direct_8u_C3IR,
//         ippiAddRandUniform_Direct_8u_C4IR,  ippiAddRandUniform_Direct_8u_AC4IR,
//         ippiAddRandUniform_Direct_16s_C1IR, ippiAddRandUniform_Direct_16s_C3IR,
//         ippiAddRandUniform_Direct_16s_C4IR, ippiAddRandUniform_Direct_16s_AC4IR,
//         ippiAddRandUniform_Direct_32f_C1IR, ippiAddRandUniform_Direct_32f_C3IR,
//         ippiAddRandUniform_Direct_32f_C4IR, ippiAddRandUniform_Direct_32f_AC4IR
//         ippiAddRandUniform_Direct_16u_C1IR, ippiAddRandUniform_Direct_16u_C3IR,
//         ippiAddRandUniform_Direct_16u_C4IR, ippiAddRandUniform_Direct_16u_AC4IR,
//
//  Purpose:    Generates pseudo-random samples with uniform distribution and adds them
//              to an image.
//
//  Returns:
//    ippStsNoErr          OK
//    ippStsNullPtrErr     One of the pointers is NULL
//    ippStsSizeErr        roiSize has a field with zero or negative value
//    ippStsStepErr        The step in image is less than or equal to zero
//
//  Parameters:
//    pSrcDst              Pointer to the image
//    srcDstStep           Step in bytes through the image
//    roiSize              ROI size
//    low                  The lower bounds of the uniform distributions range
//    high                 The upper bounds of the uniform distributions range
//    pSeed                Pointer to the seed value for the pseudo-random number
//                          generator
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandUniform_Direct_8u_C1IR,   (Ipp8u* pSrcDst, int srcDstStep,
                                                        IppiSize roiSize, Ipp8u low, Ipp8u high,
                                                        unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandUniform_Direct_8u_C3IR,   (Ipp8u* pSrcDst, int srcDstStep,
                                                        IppiSize roiSize, Ipp8u low, Ipp8u high,
                                                        unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandUniform_Direct_8u_C4IR,   (Ipp8u* pSrcDst, int srcDstStep,
                                                        IppiSize roiSize, Ipp8u low, Ipp8u high,
                                                        unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandUniform_Direct_8u_AC4IR,  (Ipp8u* pSrcDst, int srcDstStep,
                                                        IppiSize roiSize, Ipp8u low, Ipp8u high,
                                                        unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandUniform_Direct_16s_C1IR,  (Ipp16s* pSrcDst, int srcDstStep,
                                                        IppiSize roiSize, Ipp16s low, Ipp16s high,
                                                        unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandUniform_Direct_16s_C3IR,  (Ipp16s* pSrcDst, int srcDstStep,
                                                        IppiSize roiSize, Ipp16s low, Ipp16s high,
                                                        unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandUniform_Direct_16s_C4IR,  (Ipp16s* pSrcDst, int srcDstStep,
                                                        IppiSize roiSize, Ipp16s low, Ipp16s high,
                                                        unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandUniform_Direct_16s_AC4IR, (Ipp16s* pSrcDst, int srcDstStep,
                                                        IppiSize roiSize, Ipp16s low, Ipp16s high,
                                                        unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandUniform_Direct_32f_C1IR,  (Ipp32f* pSrcDst, int srcDstStep,
                                                        IppiSize roiSize, Ipp32f low, Ipp32f high,
                                                        unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandUniform_Direct_32f_C3IR,  (Ipp32f* pSrcDst, int srcDstStep,
                                                        IppiSize roiSize, Ipp32f low, Ipp32f high,
                                                        unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandUniform_Direct_32f_C4IR,  (Ipp32f* pSrcDst, int srcDstStep,
                                                        IppiSize roiSize, Ipp32f low, Ipp32f high,
                                                        unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandUniform_Direct_32f_AC4IR, (Ipp32f* pSrcDst, int srcDstStep,
                                                        IppiSize roiSize, Ipp32f low, Ipp32f high,
                                                        unsigned int* pSeed))

LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandUniform_Direct_16u_C1IR, (Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize,
                                                           Ipp16u low, Ipp16u high, unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandUniform_Direct_16u_C3IR, (Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize,
                                                           Ipp16u low, Ipp16u high, unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandUniform_Direct_16u_C4IR, (Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize,
                                                           Ipp16u low, Ipp16u high, unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandUniform_Direct_16u_AC4IR,(Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize,
                                                           Ipp16u low, Ipp16u high, unsigned int* pSeed))

/* ////////////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiAddRandGauss_Direct_8u_C1IR,  ippiAddRandGauss_Direct_8u_C3IR,
//              ippiAddRandGauss_Direct_8u_C4IR,  ippiAddRandGauss_Direct_8u_AC4IR
//              ippiAddRandGauss_Direct_16s_C1IR, ippiAddRandGauss_Direct_16s_C3IR,
//              ippiAddRandGauss_Direct_16s_C4IR, ippiAddRandGauss_Direct_16s_AC4IR,
//              ippiAddRandGauss_Direct_32f_C1IR, ippiAddRandGauss_Direct_32f_C3IR,
//              ippiAddRandGauss_Direct_32f_C4IR, ippiAddRandGauss_Direct_32f_AC4IR
//              ippiAddRandGauss_Direct_16u_C1IR, ippiAddRandGauss_Direct_16u_C3IR,
//              ippiAddRandGauss_Direct_16u_C4IR, ippiAddRandGauss_Direct_16u_AC4IR,
//
//  Purpose:    Generates pseudo-random samples with normal distribution and adds them
//              to an image.
//
//  Returns:
//    ippStsNoErr           OK
//    ippStsNullPtrErr      One of the pointers is NULL
//    ippStsSizeErr         roiSize has a field with zero or negative value
//    ippStsStepErr         The step value is less than or equal to zero
//
//  Parameters:
//    pSrcDst               Pointer to the image
//    srcDstStep            Step in bytes through the image
//    roiSize               ROI size
//    mean                  The mean of the normal distribution
//    stdev                 The standard deviation of the normal distribution
//    pSeed                 Pointer to the seed value for the pseudo-random number
//                             generator
*/


LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandGauss_Direct_8u_C1IR,   (Ipp8u* pSrcDst, int srcDstStep,
                                                      IppiSize roiSize, Ipp8u mean, Ipp8u stdev,
                                                      unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandGauss_Direct_8u_C3IR,   (Ipp8u* pSrcDst, int srcDstStep,
                                                      IppiSize roiSize, Ipp8u mean, Ipp8u stdev,
                                                      unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandGauss_Direct_8u_C4IR,   (Ipp8u* pSrcDst, int srcDstStep,
                                                      IppiSize roiSize, Ipp8u mean, Ipp8u stdev,
                                                      unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandGauss_Direct_8u_AC4IR,  (Ipp8u* pSrcDst, int srcDstStep,
                                                      IppiSize roiSize, Ipp8u mean, Ipp8u stdev,
                                                      unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandGauss_Direct_16s_C1IR,  (Ipp16s* pSrcDst, int srcDstStep,
                                                      IppiSize roiSize, Ipp16s mean, Ipp16s stdev,
                                                      unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandGauss_Direct_16s_C3IR,  (Ipp16s* pSrcDst, int srcDstStep,
                                                      IppiSize roiSize, Ipp16s mean, Ipp16s stdev,
                                                      unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandGauss_Direct_16s_C4IR,  (Ipp16s* pSrcDst, int srcDstStep,
                                                      IppiSize roiSize, Ipp16s mean, Ipp16s stdev,
                                                      unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandGauss_Direct_16s_AC4IR, (Ipp16s* pSrcDst, int srcDstStep,
                                                      IppiSize roiSize, Ipp16s mean, Ipp16s stdev,
                                                      unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandGauss_Direct_32f_C1IR,  (Ipp32f* pSrcDst, int srcDstStep,
                                                      IppiSize roiSize, Ipp32f mean, Ipp32f stdev,
                                                      unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandGauss_Direct_32f_C3IR,  (Ipp32f* pSrcDst, int srcDstStep,
                                                      IppiSize roiSize, Ipp32f mean, Ipp32f stdev,
                                                      unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandGauss_Direct_32f_C4IR,  (Ipp32f* pSrcDst, int srcDstStep,
                                                      IppiSize roiSize, Ipp32f mean, Ipp32f stdev,
                                                      unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandGauss_Direct_32f_AC4IR, (Ipp32f* pSrcDst, int srcDstStep,
                                                      IppiSize roiSize, Ipp32f mean, Ipp32f stdev,
                                                      unsigned int* pSeed))

LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandGauss_Direct_16u_C1IR, (Ipp16u* pSrcDst,int srcDstStep,IppiSize roiSize,
                                                     Ipp16u mean, Ipp16u stdev, unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandGauss_Direct_16u_C3IR, (Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize,
                                                      Ipp16u mean, Ipp16u stdev, unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandGauss_Direct_16u_C4IR, (Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize,
                                                      Ipp16u mean, Ipp16u stdev, unsigned int* pSeed))
LEGACY90IPPAPI(IppStatus, legacy90ippiAddRandGauss_Direct_16u_AC4IR,(Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize,
                                                      Ipp16u mean, Ipp16u stdev, unsigned int* pSeed))

/* ////////////////////////////////////////////////////////////////////////////////////
//  Name:               ippiImageJaehne
//  Purpose:            Creates Jaenne's test image
//  Returns:
//    ippStsNoErr       No error
//    ippStsNullPtrErr  pDst pointer is NULL
//    ippStsSizeErr     roiSize has a field with zero or negative value, or
//                      srcDstStep has a zero or negative value
//  Parameters:
//    pDst              Pointer to the destination buffer
//    DstStep           Step in bytes through the destination buffer
//    roiSize           Size of the destination image ROI in pixels
//  Notes:
//                      Dst(x,y,) = A*Sin(0.5*IPP_PI* (x2^2 + y2^2) / roiSize.height),
//                      x variables from 0 to roi.width-1,
//                      y variables from 0 to roi.height-1,
//                      x2 = (x-roi.width+1)/2.0 ,   y2 = (y-roi.height+1)/2.0 .
//                      A is the constant value depends on the image type being created.
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiImageJaehne_8s_C1R, (Ipp8s* pDst, int DstStep, IppiSize roiSize))

LEGACY90IPPAPI(IppStatus, legacy90ippiImageJaehne_8s_C3R, (Ipp8s* pDst, int DstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiImageJaehne_32s_C1R, (Ipp32s* pDst, int DstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiImageJaehne_32s_C3R, (Ipp32s* pDst, int DstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiImageJaehne_8s_C4R,  (Ipp8s* pDst,  int DstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiImageJaehne_32s_C4R, (Ipp32s* pDst, int DstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiImageJaehne_8s_AC4R, (Ipp8s* pDst,  int DstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiImageJaehne_32s_AC4R,(Ipp32s* pDst, int DstStep, IppiSize roiSize))


/* /////////////////////////////////////////////////////////////////////////
//  Name:               ippiImageRamp
//  Purpose:            Creates an ippi test image with an intensity ramp
//  Returns:
//    ippStsNoErr       No error
//    ippStsNullPtrErr  pDst pointer is NULL
//    ippStsSizeErr     roiSize has a field with zero or negative value, or
//                      srcDstStep has a zero or negative value
//  Parameters:
//    pDst              Pointer to the destination buffer
//    DstStep           Step in bytes through the destination buffer
//    roiSize           Size of the destination image ROI in pixels
//    offset            Offset value
//    slope             Slope coefficient
//    axis              Specifies the direction of the image intensity ramp,
//                      possible values:
//                        ippAxsHorizontal   in X-direction,
//                        ippAxsVertical     in Y-direction,
//                        ippAxsBoth         in both X and Y-directions.
//  Notes:              Dst(x,y) = offset + slope * x   (if ramp for X-direction)
//                      Dst(x,y) = offset + slope * y   (if ramp for Y-direction)
//                      Dst(x,y) = offset + slope * x*y (if ramp for X,Y-direction)
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiImageRamp_8s_C1R, (Ipp8s* pDst, int DstStep, IppiSize roiSize, float offset, float slope, IppiAxis axis))
LEGACY90IPPAPI(IppStatus, legacy90ippiImageRamp_8s_C3R, (Ipp8s* pDst, int DstStep, IppiSize roiSize, float offset, float slope, IppiAxis axis))
LEGACY90IPPAPI(IppStatus, legacy90ippiImageRamp_32s_C1R, (Ipp32s* pDst, int DstStep, IppiSize roiSize, float offset, float slope, IppiAxis axis))
LEGACY90IPPAPI(IppStatus, legacy90ippiImageRamp_32s_C3R, (Ipp32s* pDst, int DstStep, IppiSize roiSize, float offset, float slope, IppiAxis axis))
LEGACY90IPPAPI(IppStatus, legacy90ippiImageRamp_8s_C4R, (Ipp8s* pDst, int DstStep, IppiSize roiSize, float offset, float slope, IppiAxis axis))
LEGACY90IPPAPI(IppStatus, legacy90ippiImageRamp_32s_C4R,(Ipp32s* pDst, int DstStep, IppiSize roiSize, float offset, float slope, IppiAxis axis))
LEGACY90IPPAPI(IppStatus, legacy90ippiImageRamp_8s_AC4R, (Ipp8s* pDst, int DstStep, IppiSize roiSize, float offset, float slope, IppiAxis axis))
LEGACY90IPPAPI(IppStatus, legacy90ippiImageRamp_32s_AC4R,(Ipp32s* pDst, int DstStep, IppiSize roiSize, float offset, float slope, IppiAxis axis))


/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiConvert_1u8u_C1R
//
//  Purpose:    Converts a bitonal image to an 8u grayscale image
//
//  Returns:
//    ippStsNullPtrErr   One of the pointers is NULL
//    ippStsSizeErr      roiSize has a field with zero or negative value,
//                       or srcBitOffset is less than zero
//    ippStsStepErr      srcStep or dstStep has a negative or zero value
//    ippStsNoErr        OK
//
//  Parameters:
//    pSrc               Pointer  to the source image
//    srcStep            Step through the source image
//    srcBitOffset       Offset in the first byte of the source image row
//    pDst               Pointer to the  destination image
//    dstStep            Step through the destination image
//    roiSize            Size of the ROI
*/
LEGACY90IPPAPI ( IppStatus, legacy90ippiConvert_1u8u_C1R,( const Ipp8u* pSrc, int srcStep, int srcBitOffset, Ipp8u* pDst, int dstStep, IppiSize roiSize ))


/* /////////////////////////////////////////////////////////////////////////////
//  Names:            ippiPolarToCart
//
//  Purpose:     Converts an image in the polar coordinate form to Cartesian
//               coordinate form
//  Parameters:
//   pSrcMagn            Pointer to the source image plane containing magnitudes
//   pSrcPhase           Pointer to the source image plane containing phase values
//   srcStep             Step through the source image
//   pDst                Pointer to the destination image
//   dstStep             Step through the destination image
//   roiSize             Size of the ROI
//  Return:
//   ippStsNullPtrErr    One of the pointers is NULL
//   ippStsSizeErr       height or width of the image is less than 1
//   ippStsStepErr,      if srcStep <= 0 or
//                          dstStep <= 0
//   ippStsNoErr         No errors
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiPolarToCart_32f32fc_P2C1R,( const Ipp32f *pSrcMagn, const Ipp32f *pSrcPhase,
                                                 int srcStep, Ipp32fc *pDst, int dstStep, IppiSize roiSize ))

LEGACY90IPPAPI(IppStatus, legacy90ippiPolarToCart_32sc_C1R,(const Ipp32s* pSrcMagn, const Ipp32s* pSrcPhase, int srcStep,
                                             int PhaseFixedPoint, IppiSize roiSize, Ipp32sc *pDst , int dstStep))

LEGACY90IPPAPI(IppStatus, legacy90ippiPolarToCart_16sc_C1R,(const Ipp16s* pSrcMagn, const Ipp16s* pSrcPhase, int srcStep,
                                             int PhaseFixedPoint, IppiSize roiSize, Ipp16sc *pDst , int dstStep))

LEGACY90IPPAPI(IppStatus, legacy90ippiPolarToCart_32sc_C3R,(const Ipp32s* pSrcMagn, const Ipp32s* pSrcPhase, int srcStep,
                                             int PhaseFixedPoint, IppiSize roiSize, Ipp32sc *pDst , int dstStep))

LEGACY90IPPAPI(IppStatus, legacy90ippiPolarToCart_16sc_C3R,(const Ipp16s* pSrcMagn, const Ipp16s* pSrcPhase, int srcStep,
                                             int PhaseFixedPoint, IppiSize roiSize, Ipp16sc *pDst , int dstStep))


/* /////////////////////////////////////////////////////////////////////////////////////////////////
//                      Logical Operations and Shift Functions
///////////////////////////////////////////////////////////////////////////////////////////////// */
/*
//  Names:          ippiAnd, ippiAndC, ippiOr, ippiOrC, ippiXor, ippiXorC, ippiNot,
//  Purpose:        Performs corresponding bitwise logical operation between pixels of two image
//                  (AndC/OrC/XorC  - between pixel of the source image and a constant)
//
//  Names:          ippiLShiftC, ippiRShiftC
//  Purpose:        Shifts bits in each pixel value to the left and right
//  Parameters:
//   value         1) The constant value to be ANDed/ORed/XORed with each pixel of the source,
//                     constant vector for multi-channel images;
//                 2) The number of bits to shift, constant vector for multi-channel images.
//   pSrc          Pointer to the source image
//   srcStep       Step through the source image
//   pSrcDst       Pointer to the source/destination image (in-place flavors)
//   srcDstStep    Step through the source/destination image (in-place flavors)
//   pSrc1         Pointer to first source image
//   src1Step      Step through first source image
//   pSrc2         Pointer to second source image
//   src2Step      Step through second source image
//   pDst          Pointer to the destination image
//   dstStep       Step in destination image
//   roiSize       Size of the ROI
//
//  Returns:
//   ippStsNullPtrErr   One of the pointers is NULL
//   ippStsStepErr      One of the step values is less than or equal to zero
//   ippStsSizeErr      roiSize has a field with zero or negative value
//   ippStsShiftErr     Shift's value is less than zero
//   ippStsNoErr        No errors
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiRShiftC_8s_C1R, (const Ipp8s* pSrc, int srcStep, Ipp32u value, Ipp8s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiRShiftC_8s_C3R, (const Ipp8s* pSrc, int srcStep, const Ipp32u value[3], Ipp8s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiRShiftC_8s_C4R, (const Ipp8s* pSrc, int srcStep, const Ipp32u value[4], Ipp8s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiRShiftC_8s_AC4R, (const Ipp8s* pSrc, int srcStep, const Ipp32u value[3], Ipp8s* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiRShiftC_8s_C1IR, (Ipp32u value, Ipp8s* pSrcDst, int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiRShiftC_8s_C3IR, (const Ipp32u value[3], Ipp8s* pSrcDst, int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiRShiftC_8s_C4IR, (const Ipp32u value[4], Ipp8s* pSrcDst, int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI(IppStatus, legacy90ippiRShiftC_8s_AC4IR, (const Ipp32u value[3], Ipp8s* pSrcDst, int srcDstStep, IppiSize roiSize))


/* /////////////////////////////////////////////////////////////////////////////////////////////////
//                 Morphological Operations
///////////////////////////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiErode3x3_8u_C1R()    ippiDilate3x3_8u_C1R()
//             ippiErode3x3_8u_C3R()    ippiDilate3x3_8u_C3R()
//             ippiErode3x3_8u_AC4R()   ippiDilate3x3_8u_AC4R()
//             ippiErode3x3_8u_C4R()    ippiDilate3x3_8u_C4R()
//
//             ippiErode3x3_32f_C1R()   ippiDilate3x3_32f_C1R()
//             ippiErode3x3_32f_C3R()   ippiDilate3x3_32f_C3R()
//             ippiErode3x3_32f_AC4R()  ippiDilate3x3_32f_AC4R()
//             ippiErode3x3_32f_C4R()   ippiDilate3x3_32f_C4R()
//
//  Purpose:   Performs not in-place erosion/dilation using a 3x3 mask
//
//  Returns:
//    ippStsNullPtrErr   pSrc == NULL or pDst == NULL
//    ippStsStepErr      srcStep <= 0 or dstStep <= 0
//    ippStsSizeErr      roiSize has a field with zero or negative value
//    ippStsStrideErr    (2+roiSize.width)*nChannels*sizeof(item) > srcStep or
//                       (2+roiSize.width)*nChannels*sizeof(item) > dstStep
//    ippStsNoErr        No errors
//
//  Parameters:
//    pSrc          Pointer to the source image ROI
//    srcStep       Step (bytes) through the source image
//    pDst          Pointer to the destination image ROI
//    dstStep       Step (bytes) through the destination image
//    roiSize       Size of the ROI
*/
LEGACY90IPPAPI (IppStatus, legacy90ippiErode3x3_8u_C1R,   (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode3x3_8u_C3R,   (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode3x3_8u_AC4R,  (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode3x3_8u_C4R,   (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize))

LEGACY90IPPAPI (IppStatus, legacy90ippiDilate3x3_8u_C1R,  (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate3x3_8u_C3R,  (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate3x3_8u_AC4R, (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate3x3_8u_C4R,  (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize))

LEGACY90IPPAPI (IppStatus, legacy90ippiErode3x3_32f_C1R,  (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode3x3_32f_C3R,  (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode3x3_32f_AC4R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode3x3_32f_C4R,  (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize))

LEGACY90IPPAPI (IppStatus, legacy90ippiDilate3x3_32f_C1R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate3x3_32f_C3R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate3x3_32f_AC4R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate3x3_32f_C4R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize))


LEGACY90IPPAPI (IppStatus, legacy90ippiErode3x3_16u_C1R,  (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode3x3_16u_C3R,  (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode3x3_16u_C4R,  (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode3x3_16u_AC4R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize))

LEGACY90IPPAPI (IppStatus, legacy90ippiDilate3x3_16u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate3x3_16u_C3R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate3x3_16u_AC4R,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate3x3_16u_C4R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiErode3x3_8u_C1IR()    ippiDilate3x3_8u_C1IR()
//             ippiErode3x3_8u_C3IR()    ippiDilate3x3_8u_C3IR()
//             ippiErode3x3_8u_AC4IR()   ippiDilate3x3_8u_AC4IR()
//             ippiErode3x3_8u_C4IR()    ippiDilate3x3_8u_C4IR()
//
//             ippiErode3x3_32f_C1IR()   ippiDilate3x3_32f_C1IR()
//             ippiErode3x3_32f_C3IR()   ippiDilate3x3_32f_C3IR()
//             ippiErode3x3_32f_AC4IR()  ippiDilate3x3_32f_AC4IR()
//             ippiErode3x3_32f_C4IR()   ippiDilate3x3_32f_C4IR()
//
//  Purpose:   Performs in-place erosion/dilation using a 3x3 mask
//
//  Returns:
//    ippStsNullPtrErr    pSrcDst == NULL
//    ippStsStepErr       srcDstStep <= 0
//    ippStsSizeErr       roiSize.width  <1 or
//                        roiSize.height <1
//    ippStsStrideErr     (2+roiSize.width)*nChannels*sizeof(item) > srcDstStep
//    ippStsMemAllocErr   Memory allocation fails
//    ippStsNoErr         No errors
//
//  Parameters:
//    pSrcDst     Pointer to the source/destination image IROI
//    srcDstStep  Step (bytes) through the source/destination image
//    roiSize     Size of the ROI
*/
LEGACY90IPPAPI (IppStatus, legacy90ippiErode3x3_8u_C1IR,   (Ipp8u*  pSrcDst, int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode3x3_8u_C3IR,   (Ipp8u*  pSrcDst, int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode3x3_8u_AC4IR,  (Ipp8u*  pSrcDst, int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode3x3_8u_C4IR,   (Ipp8u*  pSrcDst, int srcDstStep, IppiSize roiSize))

LEGACY90IPPAPI (IppStatus, legacy90ippiDilate3x3_8u_C1IR,  (Ipp8u*  pSrcDst, int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate3x3_8u_C3IR,  (Ipp8u*  pSrcDst, int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate3x3_8u_AC4IR, (Ipp8u*  pSrcDst, int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate3x3_8u_C4IR,  (Ipp8u*  pSrcDst, int srcDstStep, IppiSize roiSize))

LEGACY90IPPAPI (IppStatus, legacy90ippiErode3x3_32f_C1IR,  (Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode3x3_32f_C3IR,  (Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode3x3_32f_AC4IR, (Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode3x3_32f_C4IR,  (Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))

LEGACY90IPPAPI (IppStatus, legacy90ippiDilate3x3_32f_C1IR, (Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate3x3_32f_C3IR, (Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate3x3_32f_AC4IR,(Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate3x3_32f_C4IR, (Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))


LEGACY90IPPAPI (IppStatus, legacy90ippiErode3x3_16u_C1IR,  (Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode3x3_16u_C3IR,  (Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode3x3_16u_C4IR,  (Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode3x3_16u_AC4IR, (Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))

LEGACY90IPPAPI (IppStatus, legacy90ippiDilate3x3_16u_C1IR, (Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate3x3_16u_C3IR, (Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate3x3_16u_C4IR, (Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate3x3_16u_AC4IR,(Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiErode_8u_C1R()   ippiDilate_8u_C1R()
//             ippiErode_8u_C3R()   ippiDilate_8u_C3R()
//             ippiErode_8u_C4R()   ippiDilate_8u_C4R()
//             ippiErode_8u_AC4R()  ippiDilate_8u_AC4R()
//
//             ippiErode_32f_C1R()  ippiDilate_32f_C1R()
//             ippiErode_32f_C3R()  ippiDilate_32f_C3R()
//             ippiErode_32f_C4R()  ippiDilate_32f_C4R()
//             ippiErode_32f_AC4R() ippiDilate_32f_AC4R()
//
//  Purpose:   Performs not in-place erosion/dilation using an arbitrary mask
//
//  Returns:
//    ippStsNullPtrErr,   if pSrc == NULL or
//                           pDst == NULL or
//                           pMask== NULL
//    ippStsStepErr,      if srcStep <= 0 or
//                           dstStep <= 0
//    ippStsSizeErr,      if dstRoiSize.width  <1 or
//                           dstRoiSize.height <1
//    ippStsSizeErr,      if maskSize.width  <1 or
//                           maskSize.height <1
//    ippStsAnchorErr,    if (0>anchor.x)||(anchor.x>=maskSize.width) or
//                           (0>anchor.y)||(anchor.y>=maskSize.height)
//    ippStsStrideErr,    if (maskSize.width-1+dstRoiSize.width)*nChannels*sizeof(item)) > srcStep or
//                           (maskSize.width-1+dstRoiSize.width)*nChannels*sizeof(item)) > dstStep
//    ippStsMemAllocErr,  if can not allocate memory
//    ippStsZeroMaskValuesErr, if all values of the mask are zero
//    ippStsNoErr,        if no errors
//
//  Parameters:
//    pSrc          pointer to the source image ROI
//    srcStep       source image scan-line size (bytes)
//    pDst          pointer to the target image ROI
//    dstStep       target image scan-line size (bytes)
//    dstRoiSize    size of ROI
//    pMask         pointer to the mask
//    maskSize      size of mask
//    anchor        position of the anchor
*/
LEGACY90IPPAPI (IppStatus, legacy90ippiErode_8u_C1R,   (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
                             const Ipp8u* pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode_8u_C3R,   (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
                             const Ipp8u* pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode_8u_C4R,   (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
                             const Ipp8u* pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode_8u_AC4R,  (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
                             const Ipp8u* pMask, IppiSize maskSize, IppiPoint anchor))

LEGACY90IPPAPI (IppStatus, legacy90ippiDilate_8u_C1R,  (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
                             const Ipp8u* pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate_8u_C3R,  (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
                             const Ipp8u* pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate_8u_C4R,  (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
                             const Ipp8u* pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate_8u_AC4R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
                             const Ipp8u* pMask, IppiSize maskSize, IppiPoint anchor))

LEGACY90IPPAPI (IppStatus, legacy90ippiErode_32f_C1R,  (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize dstRoiSize,
                             const Ipp8u*  pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode_32f_C3R,  (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize dstRoiSize,
                             const Ipp8u*  pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode_32f_C4R,  (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize dstRoiSize,
                             const Ipp8u*  pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode_32f_AC4R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize dstRoiSize,
                             const Ipp8u*  pMask, IppiSize maskSize, IppiPoint anchor))

LEGACY90IPPAPI (IppStatus, legacy90ippiDilate_32f_C1R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize dstRoiSize,
                             const Ipp8u*  pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate_32f_C3R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize dstRoiSize,
                             const Ipp8u*  pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate_32f_C4R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize dstRoiSize,
                             const Ipp8u*  pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate_32f_AC4R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize dstRoiSize,
                             const Ipp8u*  pMask, IppiSize maskSize, IppiPoint anchor))


LEGACY90IPPAPI (IppStatus, legacy90ippiErode_16u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,
                                       const Ipp8u*  pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode_16u_C3R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,
                                       const Ipp8u*  pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode_16u_C4R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,
                                       const Ipp8u*  pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode_16u_AC4R,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,
                                       const Ipp8u*  pMask, IppiSize maskSize, IppiPoint anchor))

LEGACY90IPPAPI (IppStatus, legacy90ippiDilate_16u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,
                                        const Ipp8u*  pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate_16u_C3R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,
                                        const Ipp8u*  pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate_16u_C4R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,
                                        const Ipp8u*  pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate_16u_AC4R,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,
                                        const Ipp8u*  pMask, IppiSize maskSize, IppiPoint anchor))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiErode_8u_C1IR()   ippiDilate_8u_C1IR()
//             ippiErode_8u_C3IR()   ippiDilate_8u_C3IR()
//             ippiErode_8u_AC4IR()  ippiDilate_8u_AC4IR()
//
//             ippiErode_32f_C1IR()  ippiDilate_32f_C1IR()
//             ippiErode_32f_C3IR()  ippiDilate_32f_C3IR()
//             ippiErode_32f_AC4IR() ippiDilate_32f_AC4IR()
//
//  Purpose:   Performs in-place erosion/dilation using an arbitrary mask
//
//  Returns:
//    ippStsNullPtrErr,   if pSrcDst == NULL or
//                           pMask== NULL
//    ippStsStepErr,      if srcDstStep <= 0
//    ippStsSizeErr,      if dstRoiSize.width  <1 or
//                           dstRoiSize.height <1
//    ippStsSizeErr,      if maskSize.width  <1 or
//                           maskSize.height <1
//    ippStsAnchorErr,    if (0>anchor.x)||(anchor.x>=maskSize.width) or
//                           (0>anchor.y)||(anchor.y>=maskSize.height)
//    ippStsStrideErr,    if (maskSize.width-1+dstRoiSize.width)*nChannels*sizeof(item)) > srcDstStep
//    ippStsMemAllocErr,  if can not allocate memory
//    ippStsZeroMaskValuesErr, if all values of the mask are zero
//    ippStsNoErr,        if no errors
//
//  Parameters:
//    pSrcDst       pointer to the source image ROI
//    srcDstStep    source image scan-line size (bytes)
//    dstRoiSize    size of ROI
//    pMask         pointer to the mask
//    maskSize      size of mask
//    anchor        position of the anchor
*/
LEGACY90IPPAPI (IppStatus, legacy90ippiErode_8u_C1IR,   (Ipp8u* pSrcDst, int srcDstStep, IppiSize dstRoiSize,
                              const Ipp8u* pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode_8u_C3IR,   (Ipp8u* pSrcDst, int srcDstStep, IppiSize dstRoiSize,
                              const Ipp8u* pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode_8u_AC4IR,  (Ipp8u* pSrcDst, int srcDstStep, IppiSize dstRoiSize,
                              const Ipp8u* pMask, IppiSize maskSize, IppiPoint anchor))

LEGACY90IPPAPI (IppStatus, legacy90ippiDilate_8u_C1IR,  (Ipp8u* pSrcDst, int srcDstStep, IppiSize dstRoiSize,
                              const Ipp8u* pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate_8u_C3IR,  (Ipp8u* pSrcDst, int srcDstStep, IppiSize dstRoiSize,
                              const Ipp8u* pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate_8u_AC4IR, (Ipp8u* pSrcDst, int srcDstStep, IppiSize dstRoiSize,
                              const Ipp8u* pMask, IppiSize maskSize, IppiPoint anchor))

LEGACY90IPPAPI (IppStatus, legacy90ippiErode_32f_C1IR,  (Ipp32f* pSrcDst, int srcDstStep, IppiSize dstRoiSize,
                              const Ipp8u*  pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode_32f_C3IR,  (Ipp32f* pSrcDst, int srcDstStep, IppiSize dstRoiSize,
                              const Ipp8u*  pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode_32f_AC4IR, (Ipp32f* pSrcDst, int srcDstStep, IppiSize dstRoiSize,
                              const Ipp8u*  pMask, IppiSize maskSize, IppiPoint anchor))

LEGACY90IPPAPI (IppStatus, legacy90ippiDilate_32f_C1IR, (Ipp32f* pSrcDst, int srcDstStep, IppiSize dstRoiSize,
                              const Ipp8u*  pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate_32f_C3IR, (Ipp32f* pSrcDst, int srcDstStep, IppiSize dstRoiSize,
                              const Ipp8u*  pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate_32f_AC4IR,(Ipp32f* pSrcDst, int srcDstStep, IppiSize dstRoiSize,
                              const Ipp8u*  pMask, IppiSize maskSize, IppiPoint anchor))

LEGACY90IPPAPI (IppStatus, legacy90ippiErode_16u_C1IR, (Ipp16u* pSrcDst, int srcDstStep, IppiSize dstRoiSize,
                                   const Ipp8u* pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode_16u_C3IR, (Ipp16u* pSrcDst, int srcDstStep, IppiSize dstRoiSize,
                                   const Ipp8u* pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiErode_16u_AC4IR,(Ipp16u* pSrcDst, int srcDstStep, IppiSize dstRoiSize,
                                   const Ipp8u* pMask, IppiSize maskSize, IppiPoint anchor))

LEGACY90IPPAPI (IppStatus, legacy90ippiDilate_16u_C1IR, (Ipp16u* pSrcDst, int srcDstStep, IppiSize dstRoiSize,
                                    const Ipp8u* pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate_16u_C3IR, (Ipp16u* pSrcDst, int srcDstStep, IppiSize dstRoiSize,
                                    const Ipp8u* pMask, IppiSize maskSize, IppiPoint anchor))
LEGACY90IPPAPI (IppStatus, legacy90ippiDilate_16u_AC4IR,(Ipp16u* pSrcDst, int srcDstStep, IppiSize dstRoiSize,
                                    const Ipp8u* pMask, IppiSize maskSize, IppiPoint anchor))


/* /////////////////////////////////////////////////////////////////////////////
//                     Bilateral filter function
// /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFilterBilateralGetBufSize_8u_C1R
//  Purpose:    to define buffer size for bilateral filter
//  Parameters:
//    filter        type of bilateral filter
//    maxDstRoiSize maximum roi size of destination image what will be applied
//                  for processing
//    maxKernelSize maximum size of kernel what will be applied for processing
//    pBufferSize   pointer to buffer size
//  Return:
//    ippStsNoErr               OK
//    ippStsNullPtrErr          pointer to buffer size is NULL
//    ippStsSizeErr             size of maxDstRoiSize is less or equal 0
//    ippStsMaskSizeErr         size of maxKernelSize is less or equal 0
//    ippStsNotSupportedModeErr bilateral filter type is not supported
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBilateralGetBufSize_8u_C1R,
       ( IppiFilterBilateralType filter, IppiSize maxDstRoiSize,
       IppiSize maxKernelSize, int *pBufferSize ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFilterBilateralInit_8u_C1R
//  Purpose:    initialization of Spec for bilateral filter
//  Parameters:
//    filter            type of bilateral filter
//    valSquareSigma    square of Sigma for factor function for pixel value
//    posSquareSigma    square of Sigma for factor function for pixel position
//    stepInKernel      processing step in kernel
//    pSpec             pointer to Spec
//  Return:
//    ippStsNoErr               OK
//    ippStsNullPtrErr          pointer to Spec is NULL
//    ippStsMaskSizeErr         size of maxKernelSize is less or equal 0
//    ippStsBadArgErr           valSquareSigma, posSquareSigma or stepInKernel
//                              is less or equal 0
//    ippStsNotSupportedModeErr bilateral filter type is not supported
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBilateralInit_8u_C1R,( IppiFilterBilateralType filter,
       IppiSize maxKernelSize, Ipp32f valSquareSigma, Ipp32f posSquareSigma,
       int stepInKernel, IppiFilterBilateralSpec *pSpec ))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFilterBilateral_8u_C1R
//  Purpose:    bilateral filter
//  Parameters:
//    pSrc         Pointer to the source image
//    srcStep      Step through the source image
//    pDst         Pointer to the destination image
//    dstStep      Step through the destination image
//    dstRoiSize   Size of the destination ROI
//    kernelSize   Size of the filter kernel
//    pSpec        Pointer to filter spec
//  Return:
//    ippStsNoErr           OK
//    ippStsNullPtrErr      pointer to Src, Dst or Specc is NULL
//    ippStsSizeErr         size of dstRoiSize is less or equal 0
//    ippStsMaskSizeErr     size of kernelSize is less or equal 0
//    ippStsStepErr         step of src or dst is less or equal 0
//    ippStsContextMatchErr filter Spec is not match
*/
LEGACY90IPPAPI(IppStatus, legacy90ippiFilterBilateral_8u_C1R,( const Ipp8u *pSrc, int srcStep,
       Ipp8u *pDst, int dstStep, IppiSize dstRoiSize, IppiSize kernelSize,
       IppiFilterBilateralSpec *pSpec))


/* ///////////////////////////////////////////////////////////////////////////
//             General Linear Filters with rounding
// ////////////////////////////////////////////////////////////////////////////
//   Names:     ippiFilterRoundGetBufSize16s_8u_C1R
//              ippiFilterRoundGetBufSize16s_8u_C3R
//              ippiFilterRoundGetBufSize16s_8u_C4R
//              ippiFilterRoundGetBufSize16s_8u_AC4R
//              ippiFilterRoundGetBufSize32s_16u_C1R
//              ippiFilterRoundGetBufSize32s_16u_C3R
//              ippiFilterRoundGetBufSize32s_16u_C4R
//              ippiFilterRoundGetBufSize32s_16u_AC4R
//              ippiFilterRoundGetBufSize32s_16s_C1R
//              ippiFilterRoundGetBufSize32s_16s_C3R
//              ippiFilterRoundGetBufSize32s_16s_C4R
//              ippiFilterRoundGetBufSize32s_16s_AC4R
//              ippiFilterRoundGetBufSize32f_8u_C3R
//              ippiFilterRoundGetBufSize32f_8u_C3R
//              ippiFilterRoundGetBufSize32f_8u_C4R
//              ippiFilterRoundGetBufSize32f_8u_AC4R
//              ippiFilterRoundGetBufSize32f_16u_C1R
//              ippiFilterRoundGetBufSize32f_16u_C3R
//              ippiFilterRoundGetBufSize32f_16u_C4R
//              ippiFilterRoundGetBufSize32f_16u_AC4R
//              ippiFilterRoundGetBufSize32f_16s_C1R
//              ippiFilterRoundGetBufSize32f_16s_C3R
//              ippiFilterRoundGetBufSize32f_16s_C4R
//              ippiFilterRoundGetBufSize32f_16s_AC4R

//  Purpose:    Filters an image using a general integer rectangular kernel
//              with rounding(ippRndZero, ippRndNear, ippRndFinancial)
//  Purpose:    Get size of temporal buffer
//      kernelSize      Size of the rectangular kernel in pixels.
//      roiWidth        Width of ROI
//      pSize           Pointer to the size of work buffer
//  Returns:
//   ippStsNoErr        Ok
//   ippStsNullPtrErr   pSize is NULL
//   ippStsSizeErr      Some size of kernelSize or roiWidth less or equal zero
//  Remark:             Function may return zero size of buffer.
*/
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRoundGetBufSize16s_8u_C1R, (IppiSize  kernelSize, int roiWidth, int* pSize))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRoundGetBufSize16s_8u_C3R, (IppiSize  kernelSize, int roiWidth, int* pSize))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRoundGetBufSize16s_8u_C4R, (IppiSize  kernelSize, int roiWidth, int* pSize))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRoundGetBufSize16s_8u_AC4R,(IppiSize  kernelSize, int roiWidth, int* pSize))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRoundGetBufSize32s_16u_C1R, (IppiSize  kernelSize, int roiWidth, int* pSize))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRoundGetBufSize32s_16u_C3R, (IppiSize  kernelSize, int roiWidth, int* pSize))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRoundGetBufSize32s_16u_C4R, (IppiSize  kernelSize, int roiWidth, int* pSize))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRoundGetBufSize32s_16u_AC4R,(IppiSize  kernelSize, int roiWidth, int* pSize))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRoundGetBufSize32s_16s_C1R, (IppiSize  kernelSize, int roiWidth, int* pSize))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRoundGetBufSize32s_16s_C3R, (IppiSize  kernelSize, int roiWidth, int* pSize))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRoundGetBufSize32s_16s_C4R, (IppiSize  kernelSize, int roiWidth, int* pSize))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRoundGetBufSize32s_16s_AC4R,(IppiSize  kernelSize, int roiWidth, int* pSize))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRoundGetBufSize32f_8u_C1R, (IppiSize  kernelSize, int roiWidth, int* pSize))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRoundGetBufSize32f_8u_C3R, (IppiSize  kernelSize, int roiWidth, int* pSize))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRoundGetBufSize32f_8u_C4R, (IppiSize  kernelSize, int roiWidth, int* pSize))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRoundGetBufSize32f_8u_AC4R,(IppiSize  kernelSize, int roiWidth, int* pSize))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRoundGetBufSize32f_16u_C1R, (IppiSize  kernelSize, int roiWidth, int* pSize))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRoundGetBufSize32f_16u_C3R, (IppiSize  kernelSize, int roiWidth, int* pSize))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRoundGetBufSize32f_16u_C4R, (IppiSize  kernelSize, int roiWidth, int* pSize))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRoundGetBufSize32f_16u_AC4R,(IppiSize  kernelSize, int roiWidth, int* pSize))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRoundGetBufSize32f_16s_C1R, (IppiSize  kernelSize, int roiWidth, int* pSize))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRoundGetBufSize32f_16s_C3R, (IppiSize  kernelSize, int roiWidth, int* pSize))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRoundGetBufSize32f_16s_C4R, (IppiSize  kernelSize, int roiWidth, int* pSize))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilterRoundGetBufSize32f_16s_AC4R,(IppiSize  kernelSize, int roiWidth, int* pSize))
/*
//
//  Purpose:    Filters an image using a general integer rectangular kernel
//   Names:     ippiFilter_Round16s_8u_C1R
//              ippiFilter_Round16s_8u_C3R
//              ippiFilter_Round16s_8u_C4R
//              ippiFilter_Round16s_8u_AC4R
//              ippiFilter_Round32s_16u_C1R
//              ippiFilter_Round32s_16u_C3R
//              ippiFilter_Round32s_16u_C4R
//              ippiFilter_Round32s_16u_AC4R
//              ippiFilter_Round32s_16s_C1R
//              ippiFilter_Round32s_16s_C3R
//              ippiFilter_Round32s_16s_C4R
//              ippiFilter_Round32s_16s_AC4R
//  Purpose:    Filters an image using a general integer rectangular kernel
//              with rounding(ippRndZero, ippRndNear, ippRndFinancial)
//  Parameters:
//      pSrc           Pointer to the source buffer
//      srcStep        Step in bytes through the source image buffer
//      pDst           Pointer to the destination buffer
//      dstStep        Step in bytes through the destination image buffer
//      dstRoiSize     Size of the source and destination ROI in pixels
//      pKernel        Pointer to the kernel values ( 16s(32s) kernel )
//      kernelSize     Size of the rectangular kernel in pixels.
//      anchor         Anchor cell specifying the rectangular kernel alignment
//                     with respect to the position of the input pixel
//      divisor        The integer value by which the computed result is divided.
//      roundMode      Rounding mode (ippRndZero, ippRndNear or ippRndFinancial)
//      pBuffer        Pointer to the temporary data

//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  Some of pointers to pSrc, pDst or pKernel are NULL or
//                     pBuffer is null but GetBufSize returned non zero size
//   ippStsSizeErr     dstRoiSize or kernelSize has a field with zero or negative value
//   ippStsDivisorErr  divisor value is zero, function execution is interrupted
//   ippStsStepErr      srcStep is less than (roiWidth + kernelWidth - 1) * sizeof(Ipp64f) or
//                      dstStep is less than  roiWidth * sizeof(*pSrc)
//   ippStsRoundModeNotSupportedErr Unsupported round mode
*/
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_Round16s_8u_C1R, ( const Ipp8u* pSrc, int srcStep,
        Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp16s* pKernel,
        IppiSize kernelSize, IppiPoint anchor, int divisor, IppRoundMode roundMode, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_Round16s_8u_C3R, ( const Ipp8u* pSrc, int srcStep,
        Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp16s* pKernel,
        IppiSize kernelSize, IppiPoint anchor, int divisor, IppRoundMode roundMode, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_Round16s_8u_C4R, ( const Ipp8u* pSrc, int srcStep,
        Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp16s* pKernel,
        IppiSize kernelSize, IppiPoint anchor, int divisor, IppRoundMode roundMode, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_Round16s_8u_AC4R, ( const Ipp8u* pSrc, int srcStep,
        Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp16s* pKernel,
        IppiSize kernelSize, IppiPoint anchor, int divisor, IppRoundMode roundMode, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_Round32s_16u_C1R, ( const Ipp16u* pSrc, int srcStep,
        Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        IppiSize kernelSize, IppiPoint anchor, int divisor, IppRoundMode roundMode, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_Round32s_16u_C3R, ( const Ipp16u* pSrc, int srcStep,
        Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        IppiSize kernelSize, IppiPoint anchor, int divisor, IppRoundMode roundMode, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_Round32s_16u_C4R, ( const Ipp16u* pSrc, int srcStep,
        Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        IppiSize kernelSize, IppiPoint anchor, int divisor, IppRoundMode roundMode, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_Round32s_16u_AC4R, ( const Ipp16u* pSrc, int srcStep,
        Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        IppiSize kernelSize, IppiPoint anchor, int divisor, IppRoundMode roundMode, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_Round32s_16s_C1R, ( const Ipp16s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        IppiSize kernelSize, IppiPoint anchor, int divisor, IppRoundMode roundMode, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_Round32s_16s_C3R, ( const Ipp16s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        IppiSize kernelSize, IppiPoint anchor, int divisor, IppRoundMode roundMode, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_Round32s_16s_C4R, ( const Ipp16s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        IppiSize kernelSize, IppiPoint anchor, int divisor, IppRoundMode roundMode, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_Round32s_16s_AC4R, ( const Ipp16s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32s* pKernel,
        IppiSize kernelSize, IppiPoint anchor, int divisor, IppRoundMode roundMode, Ipp8u* pBuffer ))
/*
//
//  Purpose:    Filters an image using a general integer rectangular kernel
//   Names:     ippiFilter_Round32f_8u_C1R
//              ippiFilter_Round32f_8u_C3R
//              ippiFilter_Round32f_8u_C4R
//              ippiFilter_Round32f_8u_AC4R
//              ippiFilter_Round32f_16u_C1R
//              ippiFilter_Round32f_16u_C3R
//              ippiFilter_Round32f_16u_C4R
//              ippiFilter_Round32f_16u_AC4R
//              ippiFilter_Round32f_16s_C1R
//              ippiFilter_Round32f_16s_C3R
//              ippiFilter_Round32f_16s_C4R
//              ippiFilter_Round32f_16s_AC4R
//  Purpose:    Filters an image using a general integer rectangular kernel
//              with rounding(ippRndZero, ippRndNear, ippRndFinancial)
//  Parameters:
//      pSrc           Pointer to the source buffer
//      srcStep        Step in bytes through the source image buffer
//      pDst           Pointer to the destination buffer
//      dstStep        Step in bytes through the destination image buffer
//      dstRoiSize     Size of the source and destination ROI in pixels
//      pKernel        Pointer to the kernel values ( 32f kernel )
//      kernelSize     Size of the rectangular kernel in pixels.
//      anchor         Anchor cell specifying the rectangular kernel alignment
//                     with respect to the position of the input pixel
//      roundMode      Rounding mode (ippRndZero, ippRndNear or ippRndFinancial)
//      pBuffer        Pointer to the temporary data

//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  Some of pointers to pSrc, pDst or pKernel are NULL or
//                     pBuffer is null but GetBufSize returned non zero size
//   ippStsSizeErr     dstRoiSize or kernelSize has a field with zero or negative value
//   ippStsStepErr      srcStep is less than (roiWidth + kernelWidth - 1) * sizeof(Ipp64f) or
//                      dstStep is less than  roiWidth * sizeof(*pSrc)
//   ippStsRoundModeNotSupportedErr Unsupported round mode
*/
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_Round32f_8u_C1R, ( const Ipp8u* pSrc, int srcStep,
        Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor, IppRoundMode roundMode, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_Round32f_8u_C3R, ( const Ipp8u* pSrc, int srcStep,
        Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor, IppRoundMode roundMode, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_Round32f_8u_C4R, ( const Ipp8u* pSrc, int srcStep,
        Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor, IppRoundMode roundMode, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_Round32f_8u_AC4R, ( const Ipp8u* pSrc, int srcStep,
        Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor, IppRoundMode roundMode, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_Round32f_16u_C1R, ( const Ipp16u* pSrc, int srcStep,
        Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor,  IppRoundMode roundMode, Ipp8u* pBuffer))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_Round32f_16u_C3R, ( const Ipp16u* pSrc, int srcStep,
        Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor,  IppRoundMode roundMode, Ipp8u* pBuffer))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_Round32f_16u_C4R, ( const Ipp16u* pSrc, int srcStep,
        Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor,  IppRoundMode roundMode, Ipp8u* pBuffer))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_Round32f_16u_AC4R, ( const Ipp16u* pSrc, int srcStep,
        Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor,  IppRoundMode roundMode, Ipp8u* pBuffer))

LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_Round32f_16s_C1R, ( const Ipp16s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor, IppRoundMode roundMode, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_Round32f_16s_C3R, ( const Ipp16s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor, IppRoundMode roundMode, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_Round32f_16s_C4R, ( const Ipp16s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor, IppRoundMode roundMode, Ipp8u* pBuffer ))
LEGACY90IPPAPI( IppStatus, legacy90ippiFilter_Round32f_16s_AC4R, ( const Ipp16s* pSrc, int srcStep,
        Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* pKernel,
        IppiSize kernelSize, IppiPoint anchor, IppRoundMode roundMode, Ipp8u* pBuffer ))


/*
//  Purpose:    Evaluates per-pixel SSIM equation on filtered images.
//              Intended to be uses as part of a wSSIM evaluation pipeline according to the following reference:
//              Z. Wang, A. C. Bovik, H. R. Sheikh and E. P. Simoncelli, "Image quality assessment: From error
//              visibility to structural similarity," IEEE TIP, vol. 13, no. 4, pp. 600-612, Apr. 2004.
//              Link: h__p://www.ece.uwaterloo.ca/~z70wang/publications/ssim.html
//
//    pDst[i] = (2*F(I1)[i]*F(I2)[i]+C1)/(F(I1)[i]^2+F(I2)[i]^2+C1)*
//              *(2*F(I1*I2)-2*F(I1)[i]*F(I2)[i]+C2)/(F(I1^2)+F(I1^2)-F(I1)[i]^2-F(I2)[i]^2+C2)
//
//  Parameters:
//    pSrc1                    Filtered first source image F(I1)
//    src1Step                 Step through the first source image
//    pSrc2                    Filtered second source image F(I2)
//    src2Step                 Step through the second source image
//    pSrc3                    Filtered squared first source image F(I1^2)
//    src3Step                 Step through the squared first source image
//    pSrc4                    Filtered squared second source image F(I2^2)
//    src4Step                 Step through the squared second source image
//    pSrc5                    Filtered product of the first and second source images F(I1*I2)
//    src5Step                 Step through the product of the first and second source images
//    pDst                     Pointer to the unweighted per-pixel SSIM indexes array
//    dstStep                  Step through the unweighted per-pixel SSIM indexes array
//    roiSize                  Size of the ROI
//    C1                       First predefined algorithm constant
//    C2                       Second predefined algorithm constant
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         One of the pointers is NULL
//    ippStsSizeErr            roiSize has a field with zero or negative value
//    ippStsStepErr            At least one step value is less than or equal to zero
//    ippStsBadArgErr          Incorrect hint value
*/

LEGACY90IPPAPI( IppStatus, legacy90ippiSSIM_32f_C1R,( const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2, int src2Step,
       const Ipp32f* pSrc3, int src3Step, const Ipp32f* pSrc4, int src4Step, const Ipp32f* pSrc5, int src5Step,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, Ipp32f C1, Ipp32f C2, IppHintAlgorithm hint))


/*****************************************************************************************************
//  Name:       ippiLBPImage...
//  Purpose:    Calculates the LBP of the image.
//  Parameters:
//    pSrc        Pointer to the source image ROI.
//    srcStep     Distance in bytes between starting points of consecutive lines in the source image.
//    pDst        Pointer to the destination image ROI.
//    dstStep     Distance in bytes between starting points of consecutive lines in the destination image.
//    dstRoiSize  Size of the destination ROI in pixels.
//    maskSize    Size of the mask in pixels. borderType Type of border.
//                Possible values are:
//                     ippBorderRepl Border is replicated from the edge pixels.
//                     ippBorderInMem Border is obtained from the source image pixels in memory.
//                     Mixed borders are also supported.
//                     They can be obtained by the bitwise operation OR between ippBorderRepl and ippBorderInMemTop, ippBorderInMemBottom, ippBorderInMemLeft, ippBorderInMemRight.
//    borderValue Constant value to assign to pixels of the constant border. This parameter is applicable only to the ippBorderConst border type.
//  Returns:
//    ippStsNoErr      Indicates no error.
//    ippStsNullPtrErr Indicates an error when one of the specified pointers is NULL.
//    ippStsSizeErr    Indicates an error if dstRoiSize has a field with zero or negative value.
//    ippStsBadArgErr  Indicates an error when border has an illegal value.
*/

LEGACY90IPPAPI(IppStatus, legacy90ippiLBPImage3x3_8u_C1R,   (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,IppiBorderType border,const Ipp8u* borderValue))
LEGACY90IPPAPI(IppStatus, legacy90ippiLBPImage5x5_8u_C1R,   (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,IppiBorderType border,const Ipp8u* borderValue))
LEGACY90IPPAPI(IppStatus, legacy90ippiLBPImage5x5_8u16u_C1R,(const Ipp8u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,IppiBorderType borderType,const Ipp8u* borderValue))
LEGACY90IPPAPI(IppStatus, legacy90ippiLBPImage3x3_32f8u_C1R,(const Ipp32f* pSrc, int srcStep,Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,IppiBorderType borderType,const Ipp32f* borderValue))
LEGACY90IPPAPI(IppStatus, legacy90ippiLBPImage5x5_32f8u_C1R,(const Ipp32f* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,IppiBorderType borderType,const Ipp32f* borderValue))
LEGACY90IPPAPI(IppStatus, legacy90ippiLBPImage5x5_32f16u_C1R,(const Ipp32f* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,IppiBorderType borderType,const Ipp32f* borderValue))


#ifdef __cplusplus
}
#endif

#endif /* __IPPI_90_LEGACY_H__ */
