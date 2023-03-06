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
//              Image Processing
//
//
*/


#if !defined( IPPI_H__ ) || defined( _OWN_BLDPCS )
#define IPPI_H__

#ifndef IPPDEFS_H__
  #include "ippdefs.h"
#endif

#include "ippi_l.h"

#if (defined( IPP_ENABLED_THREADING_LAYER ) || defined( IPP_ENABLED_THREADING_LAYER_REDEFINITIONS ))
    #include "ippi_tl.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if !defined( IPP_NO_DEFAULT_LIB )
  #if defined( _IPP_SEQUENTIAL_DYNAMIC )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippi" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippcore" )
  #elif defined( _IPP_SEQUENTIAL_STATIC )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippimt" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippsmt" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippvmmt" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippcoremt" )
  #elif defined( _IPP_PARALLEL_DYNAMIC )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippi" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippcore" )
  #elif defined( _IPP_PARALLEL_STATIC )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippimt" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippsmt" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippvmmt" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippcoremt" )
  #endif
#endif



/* /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//                   Functions declarations
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiGetLibVersion
//  Purpose:    gets the version of the library
//  Returns:    structure containing information about the current version of
//  the Intel(R) IPP library for image processing
//  Parameters:
//
//  Notes:      there is no need to release the returned structure
*/
IPPAPI( const IppLibraryVersion*, ippiGetLibVersion, (void) )


/* /////////////////////////////////////////////////////////////////////////////
//                   Memory Allocation Functions
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiMalloc
//  Purpose:    allocates memory with 32-byte aligned pointer for ippIP images,
//              every line of the image is aligned due to the padding characterized
//              by pStepBytes
//  Parameter:
//    widthPixels   width of image in pixels
//    heightPixels  height of image in pixels
//    pStepBytes    pointer to the image step, it is an output parameter
//                  calculated by the function
//
//  Returns:    pointer to the allocated memory or NULL if out of memory or wrong parameters
//  Notes:      free the allocated memory using the function ippiFree only
*/

IPPAPI( Ipp8u*,   ippiMalloc_8u_C1,    ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp16u*,  ippiMalloc_16u_C1,   ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp16s*,  ippiMalloc_16s_C1,   ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp32s*,  ippiMalloc_32s_C1,   ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp32f*,  ippiMalloc_32f_C1,   ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp32sc*, ippiMalloc_32sc_C1,  ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp32fc*, ippiMalloc_32fc_C1,  ( int widthPixels, int heightPixels, int* pStepBytes ) )

IPPAPI( Ipp8u*,   ippiMalloc_8u_C2,    ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp16u*,  ippiMalloc_16u_C2,   ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp16s*,  ippiMalloc_16s_C2,   ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp32s*,  ippiMalloc_32s_C2,   ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp32f*,  ippiMalloc_32f_C2,   ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp32sc*, ippiMalloc_32sc_C2,  ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp32fc*, ippiMalloc_32fc_C2,  ( int widthPixels, int heightPixels, int* pStepBytes ) )

IPPAPI( Ipp8u*,   ippiMalloc_8u_C3,    ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp16u*,  ippiMalloc_16u_C3,   ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp16s*,  ippiMalloc_16s_C3,   ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp32s*,  ippiMalloc_32s_C3,   ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp32f*,  ippiMalloc_32f_C3,   ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp32sc*, ippiMalloc_32sc_C3,  ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp32fc*, ippiMalloc_32fc_C3,  ( int widthPixels, int heightPixels, int* pStepBytes ) )

IPPAPI( Ipp8u*,   ippiMalloc_8u_C4,    ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp16u*,  ippiMalloc_16u_C4,   ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp16s*,  ippiMalloc_16s_C4,   ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp32s*,  ippiMalloc_32s_C4,   ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp32f*,  ippiMalloc_32f_C4,   ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp32sc*, ippiMalloc_32sc_C4,  ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp32fc*, ippiMalloc_32fc_C4,  ( int widthPixels, int heightPixels, int* pStepBytes ) )

IPPAPI( Ipp8u*,   ippiMalloc_8u_AC4,   ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp16u*,  ippiMalloc_16u_AC4,  ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp16s*,  ippiMalloc_16s_AC4,  ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp32s*,  ippiMalloc_32s_AC4,  ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp32f*,  ippiMalloc_32f_AC4,  ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp32sc*, ippiMalloc_32sc_AC4, ( int widthPixels, int heightPixels, int* pStepBytes ) )
IPPAPI( Ipp32fc*, ippiMalloc_32fc_AC4, ( int widthPixels, int heightPixels, int* pStepBytes ) )


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFree
//  Purpose:    frees memory allocated by the ippiMalloc functions
//  Parameter:
//    ptr       pointer to the memory allocated by the ippiMalloc functions
//
//  Notes:      use this function to free memory allocated by ippiMalloc
*/
IPPAPI( void, ippiFree, (void* ptr) )


/* ///////////////////////////////////////////////////////////////////////////////////////
//                  Arithmetic Functions
///////////////////////////////////////////////////////////////////////////// */
/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:  ippiAdd_8u_C1RSfs,  ippiAdd_8u_C3RSfs,  ippiAdd_8u_C4RSfs,  ippiAdd_8u_AC4RSfs,
//         ippiAdd_16s_C1RSfs, ippiAdd_16s_C3RSfs, ippiAdd_16s_C4RSfs, ippiAdd_16s_AC4RSfs,
//         ippiAdd_16u_C1RSfs, ippiAdd_16u_C3RSfs, ippiAdd_16u_C4RSfs, ippiAdd_16u_AC4RSfs,
//         ippiSub_8u_C1RSfs,  ippiSub_8u_C3RSfs,  ippiSub_8u_C4RSfs,  ippiSub_8u_AC4RSfs,
//         ippiSub_16s_C1RSfs, ippiSub_16s_C3RSfs, ippiSub_16s_C4RSfs, ippiSub_16s_AC4RSfs,
//         ippiSub_16u_C1RSfs, ippiSub_16u_C3RSfs, ippiSub_16u_C4RSfs, ippiSub_16u_AC4RSfs,
//         ippiMul_8u_C1RSfs,  ippiMul_8u_C3RSfs,  ippiMul_8u_C4RSfs,  ippiMul_8u_AC4RSfs,
//         ippiMul_16s_C1RSfs, ippiMul_16s_C3RSfs, ippiMul_16s_C4RSfs, ippiMul_16s_AC4RSfs
//         ippiMul_16u_C1RSfs, ippiMul_16u_C3RSfs, ippiMul_16u_C4RSfs, ippiMul_16u_AC4RSfs
//
//  Purpose:    Adds, subtracts, or multiplies pixel values of two
//              source images and places the scaled result in the destination image.
//
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         One of the pointers is NULL
//    ippStsSizeErr            Width or height of images is less than or equal to zero
//
//  Parameters:
//    pSrc1, pSrc2             Pointers to the source images
//    src1Step, src2Step       Steps through the source images
//    pDst                     Pointer to the destination image
//    dstStep                  Step through the destination image
//    roiSize                  Size of the ROI
//    scaleFactor              Scale factor
*/

IPPAPI(IppStatus, ippiAdd_8u_C1RSfs,   (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2,
                                        int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiAdd_8u_C3RSfs,   (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2,
                                        int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiAdd_8u_C4RSfs,   (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2,
                                        int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiAdd_8u_AC4RSfs,  (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2,
                                        int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16s_C1RSfs,  (const Ipp16s* pSrc1, int src1Step, const Ipp16s* pSrc2,
                                        int src2Step, Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16s_C3RSfs,  (const Ipp16s* pSrc1, int src1Step, const Ipp16s* pSrc2,
                                        int src2Step, Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16s_C4RSfs,  (const Ipp16s* pSrc1, int src1Step, const Ipp16s* pSrc2,
                                        int src2Step, Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16s_AC4RSfs, (const Ipp16s* pSrc1, int src1Step, const Ipp16s* pSrc2,
                                        int src2Step, Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16u_C1RSfs,  (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2,
                                        int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16u_C3RSfs,  (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2,
                                        int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16u_C4RSfs,  (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2,
                                        int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16u_AC4RSfs, (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2,
                                        int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiSub_8u_C1RSfs,   (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2,
                                        int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiSub_8u_C3RSfs,   (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2,
                                        int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiSub_8u_C4RSfs,   (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2,
                                        int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiSub_8u_AC4RSfs,  (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2,
                                        int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiSub_16s_C1RSfs,  (const Ipp16s* pSrc1, int src1Step, const Ipp16s* pSrc2,
                                        int src2Step, Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiSub_16s_C3RSfs,  (const Ipp16s* pSrc1, int src1Step, const Ipp16s* pSrc2,
                                        int src2Step, Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiSub_16s_C4RSfs,  (const Ipp16s* pSrc1, int src1Step, const Ipp16s* pSrc2,
                                        int src2Step, Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiSub_16s_AC4RSfs, (const Ipp16s* pSrc1, int src1Step, const Ipp16s* pSrc2,
                                        int src2Step, Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiSub_16u_C1RSfs,  (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2,
                                        int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiSub_16u_C3RSfs,  (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2,
                                        int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiSub_16u_C4RSfs,  (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2,
                                        int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiSub_16u_AC4RSfs, (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2,
                                        int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiMul_8u_C1RSfs,   (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2,
                                        int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiMul_8u_C3RSfs,   (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2,
                                        int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiMul_8u_C4RSfs,   (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2,
                                        int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiMul_8u_AC4RSfs,  (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2,
                                        int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiMul_16s_C1RSfs,  (const Ipp16s* pSrc1, int src1Step, const Ipp16s* pSrc2,
                                        int src2Step, Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiMul_16s_C3RSfs,  (const Ipp16s* pSrc1, int src1Step, const Ipp16s* pSrc2,
                                        int src2Step, Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiMul_16s_C4RSfs,  (const Ipp16s* pSrc1, int src1Step, const Ipp16s* pSrc2,
                                        int src2Step, Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiMul_16s_AC4RSfs, (const Ipp16s* pSrc1, int src1Step, const Ipp16s* pSrc2,
                                        int src2Step, Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiMul_16u_C1RSfs,  (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2,
                                        int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiMul_16u_C3RSfs,  (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2,
                                        int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiMul_16u_C4RSfs,  (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2,
                                        int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))
IPPAPI(IppStatus, ippiMul_16u_AC4RSfs, (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2,
                                        int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize,
                                        int scaleFactor))

/* //////////////////////////////////////////////////////////////////////////////////////////////
//  Name: ippiAddC_8u_C1IRSfs,  ippiAddC_8u_C3IRSfs,  ippiAddC_8u_C4IRSfs,   ippiAddC_8u_AC4IRSfs,
//        ippiAddC_16s_C1IRSfs, ippiAddC_16s_C3IRSfs, ippiAddC_16s_C4IRSfs,  ippiAddC_16s_AC4IRSfs,
//        ippiAddC_16u_C1IRSfs, ippiAddC_16u_C3IRSfs, ippiAddC_16u_C4IRSfs,  ippiAddC_16u_AC4IRSfs,
//        ippiSubC_8u_C1IRSfs,  ippiSubC_8u_C3IRSfs,  ippiSubC_8u_C4IRSfs,   ippiSubC_8u_AC4IRSfs,
//        ippiSubC_16s_C1IRSfs, ippiSubC_16s_C3IRSfs, ippiSubC_16s_C4IRSfs,  ippiSubC_16s_AC4IRSfs,
//        ippiSubC_16u_C1IRSfs, ippiSubC_16u_C3IRSfs, ippiSubC_16u_C4IRSfs,  ippiSubC_16u_AC4IRSfs,
//        ippiMulC_8u_C1IRSfs,  ippiMulC_8u_C3IRSfs,  ippiMulC_8u_C4IRSfs,   ippiMulC_8u_AC4IRSfs,
//        ippiMulC_16s_C1IRSfs, ippiMulC_16s_C3IRSfs, ippiMulC_16s_C4IRSfs,  ippiMulC_16s_AC4IRSfs
//        ippiMulC_16u_C1IRSfs, ippiMulC_16u_C3IRSfs, ippiMulC_16u_C4IRSfs,  ippiMulC_16u_AC4IRSfs
//
//  Purpose:    Adds, subtracts, or multiplies pixel values of an image and a constant
//              and places the scaled results in the same image.
//
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         Pointer is NULL
//    ippStsSizeErr            Width or height of an image is less than or equal to zero
//
//  Parameters:
//    value                    Constant value (constant vector for multi-channel images)
//    pSrcDst                  Pointer to the image
//    srcDstStep               Step through the image
//    roiSize                  Size of the ROI
//    scaleFactor              Scale factor
*/

IPPAPI(IppStatus, ippiAddC_8u_C1IRSfs,   (Ipp8u value, Ipp8u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_8u_C3IRSfs,   (const Ipp8u value[3], Ipp8u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_8u_C4IRSfs,   (const Ipp8u value[4], Ipp8u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_8u_AC4IRSfs,  (const Ipp8u value[3], Ipp8u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16s_C1IRSfs,  (Ipp16s value, Ipp16s* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16s_C3IRSfs,  (const Ipp16s value[3], Ipp16s* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16s_C4IRSfs,  (const Ipp16s value[4], Ipp16s* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16s_AC4IRSfs, (const Ipp16s value[3], Ipp16s* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16u_C1IRSfs,  (Ipp16u value, Ipp16u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16u_C3IRSfs,  (const Ipp16u value[3], Ipp16u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16u_C4IRSfs,  (const Ipp16u value[4], Ipp16u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16u_AC4IRSfs, (const Ipp16u value[3], Ipp16u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_8u_C1IRSfs,   (Ipp8u value, Ipp8u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_8u_C3IRSfs,   (const Ipp8u value[3], Ipp8u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_8u_C4IRSfs,   (const Ipp8u value[4], Ipp8u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_8u_AC4IRSfs,  (const Ipp8u value[3], Ipp8u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16s_C1IRSfs,  (Ipp16s value, Ipp16s* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16s_C3IRSfs,  (const Ipp16s value[3], Ipp16s* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16s_C4IRSfs,  (const Ipp16s value[4], Ipp16s* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16s_AC4IRSfs, (const Ipp16s value[3], Ipp16s* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16u_C1IRSfs,  (Ipp16u value, Ipp16u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16u_C3IRSfs,  (const Ipp16u value[3], Ipp16u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16u_C4IRSfs,  (const Ipp16u value[4], Ipp16u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16u_AC4IRSfs, (const Ipp16u value[3], Ipp16u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_8u_C1IRSfs,   (Ipp8u value, Ipp8u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_8u_C3IRSfs,   (const Ipp8u value[3], Ipp8u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_8u_C4IRSfs,   (const Ipp8u value[4], Ipp8u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_8u_AC4IRSfs,  (const Ipp8u value[3], Ipp8u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16s_C1IRSfs,  (Ipp16s value, Ipp16s* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16s_C3IRSfs,  (const Ipp16s value[3], Ipp16s* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16s_C4IRSfs,  (const Ipp16s value[4], Ipp16s* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16s_AC4IRSfs, (const Ipp16s value[3], Ipp16s* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16u_C1IRSfs,  (Ipp16u value, Ipp16u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16u_C3IRSfs,  (const Ipp16u value[3], Ipp16u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16u_C4IRSfs,  (const Ipp16u value[4], Ipp16u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16u_AC4IRSfs, (const Ipp16u value[3], Ipp16u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int scaleFactor))

/* /////////////////////////////////////////////////////////////////////////////////////////////
//  Name: ippiAddC_8u_C1RSfs,  ippiAddC_8u_C3RSfs,  ippiAddC_8u_C4RSfs   ippiAddC_8u_AC4RSfs,
//        ippiAddC_16s_C1RSfs, ippiAddC_16s_C3RSfs, ippiAddC_16s_C4RSfs, ippiAddC_16s_AC4RSfs,
//        ippiAddC_16u_C1RSfs, ippiAddC_16u_C3RSfs, ippiAddC_16u_C4RSfs, ippiAddC_16u_AC4RSfs,
//        ippiSubC_8u_C1RSfs,  ippiSubC_8u_C3RSfs,  ippiSubC_8u_C4RSfs,  ippiSubC_8u_AC4RSfs,
//        ippiSubC_16s_C1RSfs, ippiSubC_16s_C3RSfs, ippiSubC_16s_C4RSfs, ippiSubC_16s_AC4RSfs,
//        ippiSubC_16u_C1RSfs, ippiSubC_16u_C3RSfs, ippiSubC_16u_C4RSfs, ippiSubC_16u_AC4RSfs,
//        ippiMulC_8u_C1RSfs,  ippiMulC_8u_C3RSfs,  ippiMulC_8u_C4RSfs,  ippiMulC_8u_AC4RSfs,
//        ippiMulC_16s_C1RSfs, ippiMulC_16s_C3RSfs, ippiMulC_16s_C4RSfs, ippiMulC_16s_AC4RSfs
//        ippiMulC_16u_C1RSfs, ippiMulC_16u_C3RSfs, ippiMulC_16u_C4RSfs, ippiMulC_16u_AC4RSfs
//
//  Purpose:    Adds, subtracts, or multiplies pixel values of a source image
//              and a constant, and places the scaled results in the destination image.
//
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         One of the pointers is NULL
//    ippStsSizeErr            Width or height of images is less than or equal to zero
//
//  Parameters:
//    value                    Constant value (constant vector for multi-channel images)
//    pSrc                     Pointer to the source image
//    srcStep                  Step through the source image
//    pDst                     Pointer to the destination image
//    dstStep                  Step through the destination image
//    roiSize                  Size of the ROI
//    scaleFactor              Scale factor
*/

IPPAPI(IppStatus, ippiAddC_8u_C1RSfs,   (const Ipp8u* pSrc, int srcStep, Ipp8u value, Ipp8u* pDst,
                                         int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_8u_C3RSfs,   (const Ipp8u* pSrc, int srcStep, const Ipp8u value[3],
                                         Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiAddC_8u_C4RSfs,   (const Ipp8u* pSrc, int srcStep, const Ipp8u value[4],
                                         Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiAddC_8u_AC4RSfs,  (const Ipp8u* pSrc, int srcStep, const Ipp8u value[3],
                                         Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16s_C1RSfs,  (const Ipp16s* pSrc, int srcStep, Ipp16s value, Ipp16s* pDst,
                                         int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16s_C3RSfs,  (const Ipp16s* pSrc, int srcStep, const Ipp16s value[3],
                                         Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16s_C4RSfs,  (const Ipp16s* pSrc, int srcStep, const Ipp16s value[4],
                                         Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16s_AC4RSfs, (const Ipp16s* pSrc, int srcStep, const Ipp16s value[3],
                                         Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16u_C1RSfs,  (const Ipp16u* pSrc, int srcStep, Ipp16u value, Ipp16u* pDst,
                                         int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16u_C3RSfs,  (const Ipp16u* pSrc, int srcStep, const Ipp16u value[3],
                                         Ipp16u* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16u_C4RSfs,  (const Ipp16u* pSrc, int srcStep, const Ipp16u value[4],
                                         Ipp16u* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16u_AC4RSfs, (const Ipp16u* pSrc, int srcStep, const Ipp16u value[3],
                                         Ipp16u* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiSubC_8u_C1RSfs,   (const Ipp8u* pSrc, int srcStep, Ipp8u value, Ipp8u* pDst,
                                         int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_8u_C3RSfs,   (const Ipp8u* pSrc, int srcStep ,const Ipp8u value[3],
                                         Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiSubC_8u_C4RSfs,   (const Ipp8u* pSrc, int srcStep, const Ipp8u value[4],
                                         Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiSubC_8u_AC4RSfs,  (const Ipp8u* pSrc, int srcStep, const Ipp8u value[3],
                                         Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16s_C1RSfs,  (const Ipp16s* pSrc, int srcStep, Ipp16s value, Ipp16s* pDst,
                                         int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16s_C3RSfs,  (const Ipp16s* pSrc, int srcStep, const Ipp16s value[3],
                                         Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16s_C4RSfs,  (const Ipp16s* pSrc, int srcStep, const Ipp16s value[4],
                                         Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16s_AC4RSfs, (const Ipp16s* pSrc, int srcStep, const Ipp16s value[3],
                                         Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16u_C1RSfs,  (const Ipp16u* pSrc, int srcStep, Ipp16u value, Ipp16u* pDst,
                                         int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16u_C3RSfs,  (const Ipp16u* pSrc, int srcStep, const Ipp16u value[3],
                                         Ipp16u* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16u_C4RSfs,  (const Ipp16u* pSrc, int srcStep, const Ipp16u value[4],
                                         Ipp16u* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16u_AC4RSfs, (const Ipp16u* pSrc, int srcStep, const Ipp16u value[3],
                                         Ipp16u* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiMulC_8u_C1RSfs,   (const Ipp8u* pSrc, int srcStep, Ipp8u value, Ipp8u* pDst,
                                         int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_8u_C3RSfs,   (const Ipp8u* pSrc, int srcStep, const Ipp8u value[3],
                                         Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiMulC_8u_C4RSfs,   (const Ipp8u* pSrc, int srcStep, const Ipp8u value[4],
                                         Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiMulC_8u_AC4RSfs,  (const Ipp8u* pSrc, int srcStep, const Ipp8u value[3],
                                         Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16s_C1RSfs,  (const Ipp16s* pSrc, int srcStep, Ipp16s value, Ipp16s* pDst,
                                         int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16s_C3RSfs,  (const Ipp16s* pSrc, int srcStep, const Ipp16s value[3],
                                         Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16s_C4RSfs,  (const Ipp16s* pSrc, int srcStep, const Ipp16s value[4],
                                         Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16s_AC4RSfs, (const Ipp16s* pSrc, int srcStep, const Ipp16s value[3],
                                         Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16u_C1RSfs,  (const Ipp16u* pSrc, int srcStep, Ipp16u value, Ipp16u* pDst,
                                         int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16u_C3RSfs,  (const Ipp16u* pSrc, int srcStep, const Ipp16u value[3],
                                         Ipp16u* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16u_C4RSfs,  (const Ipp16u* pSrc, int srcStep, const Ipp16u value[4],
                                         Ipp16u* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16u_AC4RSfs, (const Ipp16u* pSrc, int srcStep, const Ipp16u value[3],
                                         Ipp16u* pDst, int dstStep, IppiSize roiSize,
                                         int scaleFactor))

/* ////////////////////////////////////////////////////////////////////////////////////////////
//  Name: ippiAdd_8u_C1IRSfs,  ippiAdd_8u_C3IRSfs,  ippiAdd_8u_C4IRSfs,  ippiAdd_8u_AC4IRSfs,
//        ippiAdd_16s_C1IRSfs, ippiAdd_16s_C3IRSfs, ippiAdd_16s_C4IRSfs, ippiAdd_16s_AC4IRSfs,
//        ippiAdd_16u_C1IRSfs, ippiAdd_16u_C3IRSfs, ippiAdd_16u_C4IRSfs, ippiAdd_16u_AC4IRSfs,
//        ippiSub_8u_C1IRSfs,  ippiSub_8u_C3IRSfs,  ippiSub_8u_C4IRSfs,  ippiSub_8u_AC4IRSfs,
//        ippiSub_16s_C1IRSfs, ippiSub_16s_C3IRSfs, ippiSub_16s_C4IRSfs  ippiSub_16s_AC4IRSfs,
//        ippiSub_16u_C1IRSfs, ippiSub_16u_C3IRSfs, ippiSub_16u_C4IRSfs  ippiSub_16u_AC4IRSfs,
//        ippiMul_8u_C1IRSfs,  ippiMul_8u_C3IRSfs,  ippiMul_8u_C4IRSfs,  ippiMul_8u_AC4IRSfs,
//        ippiMul_16s_C1IRSfs, ippiMul_16s_C3IRSfs, ippiMul_16s_C4IRSfs, ippiMul_16s_AC4IRSfs
//        ippiMul_16u_C1IRSfs, ippiMul_16u_C3IRSfs, ippiMul_16u_C4IRSfs, ippiMul_16u_AC4IRSfs
//
//  Purpose:    Adds, subtracts, or multiplies pixel values of two source images
//              and places the scaled results in the first source image.
//
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         One of the pointers is NULL
//    ippStsSizeErr            Width or height of images is less than or equal to zero
//
//  Parameters:
//    pSrc                     Pointer to the second source image
//    srcStep                  Step through the second source image
//    pSrcDst                  Pointer to the first source/destination image
//    srcDstStep               Step through the first source/destination image
//    roiSize                  Size of the ROI
//    scaleFactor              Scale factor
*/

IPPAPI(IppStatus, ippiAdd_8u_C1IRSfs,   (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))

IPPAPI(IppStatus, ippiAdd_8u_C3IRSfs,   (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_8u_C4IRSfs,   (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_8u_AC4IRSfs,  (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16s_C1IRSfs,  (const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16s_C3IRSfs,  (const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16s_C4IRSfs,  (const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16s_AC4IRSfs, (const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16u_C1IRSfs,  (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16u_C3IRSfs,  (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16u_C4IRSfs,  (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16u_AC4IRSfs, (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_8u_C1IRSfs,   (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_8u_C3IRSfs,   (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_8u_C4IRSfs,   (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_8u_AC4IRSfs,  (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_16s_C1IRSfs,  (const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_16s_C3IRSfs,  (const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_16s_C4IRSfs,  (const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_16s_AC4IRSfs, (const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_16u_C1IRSfs,  (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_16u_C3IRSfs,  (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_16u_C4IRSfs,  (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_16u_AC4IRSfs, (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_8u_C1IRSfs,   (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_8u_C3IRSfs,   (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_8u_C4IRSfs,   (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_8u_AC4IRSfs,  (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_16s_C1IRSfs,  (const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_16s_C3IRSfs,  (const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_16s_C4IRSfs,  (const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_16s_AC4IRSfs, (const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_16u_C1IRSfs,  (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_16u_C3IRSfs,  (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_16u_C4IRSfs,  (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_16u_AC4IRSfs, (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))

/* /////////////////////////////////////////////////////////////////////////////////
//  Name: ippiAddC_32f_C1R, ippiAddC_32f_C3R, ippiAddC_32f_C4R,  ippiAddC_32f_AC4R,
//        ippiSubC_32f_C1R, ippiSubC_32f_C3R, ippiSubC_32f_C4R,  ippiSubC_32f_AC4R,
//        ippiMulC_32f_C1R, ippiMulC_32f_C3R, ippiMulC_32f_C4R,  ippiMulC_32f_AC4R
//
//  Purpose:    Adds, subtracts, or multiplies pixel values of a source image
//              and a constant, and places the results in a destination image.
//
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         One of the pointers is NULL
//    ippStsSizeErr            Width or height of images is less than or equal to zero
//
//  Parameters:
//    value                    The constant value for the specified operation
//    pSrc                     Pointer to the source image
//    srcStep                  Step through the source image
//    pDst                     Pointer to the destination image
//    dstStep                  Step through the destination image
//    roiSize                  Size of the ROI
*/

IPPAPI(IppStatus, ippiAddC_32f_C1R,  (const Ipp32f* pSrc, int srcStep, Ipp32f value, Ipp32f* pDst,
                                      int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAddC_32f_C3R,  (const Ipp32f* pSrc, int srcStep, const Ipp32f value[3],
                                      Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAddC_32f_C4R,  (const Ipp32f* pSrc, int srcStep, const Ipp32f value[4],
                                      Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAddC_32f_AC4R, (const Ipp32f* pSrc, int srcStep, const Ipp32f value[3],
                                      Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiSubC_32f_C1R,  (const Ipp32f* pSrc, int srcStep, Ipp32f value, Ipp32f* pDst,
                                      int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiSubC_32f_C3R,  (const Ipp32f* pSrc, int srcStep, const Ipp32f value[3],
                                      Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiSubC_32f_C4R,  (const Ipp32f* pSrc, int srcStep, const Ipp32f value[4],
                                      Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiSubC_32f_AC4R, (const Ipp32f* pSrc, int srcStep, const Ipp32f value[3],
                                      Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulC_32f_C1R,  (const Ipp32f* pSrc, int srcStep, Ipp32f value, Ipp32f* pDst,
                                      int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulC_32f_C3R,  (const Ipp32f* pSrc, int srcStep, const Ipp32f value[3],
                                      Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulC_32f_C4R,  (const Ipp32f* pSrc, int srcStep, const Ipp32f value[4],
                                      Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulC_32f_AC4R, (const Ipp32f* pSrc, int srcStep, const Ipp32f value[3],
                                      Ipp32f* pDst, int dstStep, IppiSize roiSize))

/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name: ippiAddC_32f_C1IR, ippiAddC_32f_C3IR, ippiAddC_32f_C4IR, ippiAddC_32f_AC4IR,
//        ippiSubC_32f_C1IR, ippiSubC_32f_C3IR, ippiSubC_32f_C4IR, ippiSubC_32f_AC4IR,
//        ippiMulC_32f_C1IR, ippiMulC_32f_C3IR, ippiMulC_32f_C4IR, ippiMulC_32f_AC4IR
//
//  Purpose:    Adds, subtracts, or multiplies pixel values of an image
//              and a constant, and places the results in the same image.
//
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         Pointer is NULL
//    ippStsSizeErr            Width or height of an image is less than or equal to zero
//
//  Parameters:
//    value                    The constant value for the specified operation
//    pSrcDst                  Pointer to the image
//    srcDstStep               Step through the image
//    roiSize                  Size of the ROI
*/

IPPAPI(IppStatus, ippiAddC_32f_C1IR,  (Ipp32f value, Ipp32f* pSrcDst, int srcDstStep,
                                       IppiSize roiSize))
IPPAPI(IppStatus, ippiAddC_32f_C3IR,  (const Ipp32f value[3], Ipp32f* pSrcDst, int srcDstStep,
                                       IppiSize roiSize))
IPPAPI(IppStatus, ippiAddC_32f_C4IR,  (const Ipp32f value[4], Ipp32f* pSrcDst, int srcDstStep,
                                       IppiSize roiSize))
IPPAPI(IppStatus, ippiAddC_32f_AC4IR, (const Ipp32f value[3], Ipp32f* pSrcDst, int srcDstStep,
                                       IppiSize roiSize))
IPPAPI(IppStatus, ippiSubC_32f_C1IR,  (Ipp32f value, Ipp32f* pSrcDst, int srcDstStep,
                                       IppiSize roiSize))
IPPAPI(IppStatus, ippiSubC_32f_C3IR,  (const Ipp32f value[3], Ipp32f* pSrcDst, int srcDstStep,
                                       IppiSize roiSize))
IPPAPI(IppStatus, ippiSubC_32f_C4IR,  (const Ipp32f value[4], Ipp32f* pSrcDst, int srcDstStep,
                                       IppiSize roiSize))
IPPAPI(IppStatus, ippiSubC_32f_AC4IR, (const Ipp32f value[3], Ipp32f* pSrcDst, int srcDstStep,
                                       IppiSize roiSize))
IPPAPI(IppStatus, ippiMulC_32f_C1IR,  (Ipp32f value, Ipp32f* pSrcDst, int srcDstStep,
                                       IppiSize roiSize))
IPPAPI(IppStatus, ippiMulC_32f_C3IR,  (const Ipp32f value[3], Ipp32f* pSrcDst, int srcDstStep,
                                       IppiSize roiSize))
IPPAPI(IppStatus, ippiMulC_32f_C4IR,  (const Ipp32f value[4], Ipp32f* pSrcDst, int srcDstStep,
                                       IppiSize roiSize))
IPPAPI(IppStatus, ippiMulC_32f_AC4IR, (const Ipp32f value[3], Ipp32f* pSrcDst, int srcDstStep,
                                       IppiSize roiSize))

/* ////////////////////////////////////////////////////////////////////////////////////
//  Name: ippiAdd_32f_C1IR, ippiAdd_32f_C3IR, ippiAdd_32f_C4IR, ippiAdd_32f_AC4IR,
//        ippiSub_32f_C1IR, ippiSub_32f_C3IR, ippiSub_32f_C4IR, ippiSub_32f_AC4IR,
//        ippiMul_32f_C1IR, ippiMul_32f_C3IR, ippiMul_32f_C4IR, ippiMul_32f_AC4IR
//
//  Purpose:    Adds, subtracts, or multiplies pixel values of two source images
//              and places the results in the first image.
//
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         One of the pointers is NULL
//    ippStsSizeErr            Width or height of images is less than or equal to zero
//
//  Parameters:
//    pSrc                     Pointer to the second source image
//    srcStep                  Step through the second source image
//    pSrcDst                  Pointer to the  first source/destination image
//    srcDstStep               Step through the first source/destination image
//    roiSize                  Size of the ROI
*/

IPPAPI(IppStatus, ippiAdd_32f_C1IR,  (const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst,
                                      int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAdd_32f_C3IR,  (const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst,
                                      int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAdd_32f_C4IR,  (const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst,
                                      int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAdd_32f_AC4IR, (const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst,
                                      int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiSub_32f_C1IR,  (const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst,
                                      int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiSub_32f_C3IR,  (const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst,
                                      int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiSub_32f_C4IR,  (const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst,
                                      int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiSub_32f_AC4IR, (const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst,
                                      int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMul_32f_C1IR,  (const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst,
                                      int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMul_32f_C3IR,  (const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst,
                                      int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMul_32f_C4IR,  (const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst,
                                      int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMul_32f_AC4IR, (const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst,
                                      int srcDstStep, IppiSize roiSize))

/* ////////////////////////////////////////////////////////////////////////////
//  Name: ippiAdd_32f_C1R, ippiAdd_32f_C3R, ippiAdd_32f_C4R, ippiAdd_32f_AC4R,
//        ippiSub_32f_C1R, ippiSub_32f_C3R, ippiSub_32f_C4R, ippiSub_32f_AC4R,
//        ippiMul_32f_C1R, ippiMul_32f_C3R, ippiMul_32f_C4R, ippiMul_32f_AC4R
//
//  Purpose:    Adds, subtracts, or multiplies pixel values of two
//              source images and places the results in a destination image.
//
//  Returns:
//    ippStsNoErr            OK
//    ippStsNullPtrErr       One of the pointers is NULL
//    ippStsSizeErr          Width or height of images is less than or equal to zero
//
//  Parameters:
//    pSrc1, pSrc2           Pointers to the source images
//    src1Step, src2Step     Steps through the source images
//    pDst                   Pointer to the destination image
//    dstStep                Step through the destination image

//    roiSize                Size of the ROI
*/

IPPAPI(IppStatus, ippiAdd_32f_C1R,  (const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2,
                                     int src2Step, Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAdd_32f_C3R,  (const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2,
                                     int src2Step, Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAdd_32f_C4R,  (const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2,
                                     int src2Step, Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAdd_32f_AC4R, (const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2,
                                     int src2Step, Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiSub_32f_C1R,  (const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2,
                                     int src2Step, Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiSub_32f_C3R,  (const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2,
                                     int src2Step, Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiSub_32f_C4R,  (const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2,
                                     int src2Step, Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiSub_32f_AC4R, (const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2,
                                     int src2Step, Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMul_32f_C1R,  (const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2,
                                     int src2Step, Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMul_32f_C3R,  (const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2,
                                     int src2Step, Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMul_32f_C4R,  (const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2,
                                     int src2Step, Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMul_32f_AC4R, (const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2,
                                     int src2Step, Ipp32f* pDst, int dstStep, IppiSize roiSize))

/* //////////////////////////////////////////////////////////////////////////////
//  Name:       ippiDiv_32f_C1R, ippiDiv_32f_C3R ippiDiv_32f_C4R ippiDiv_32f_AC4R
//
//  Purpose:    Divides pixel values of an image by pixel values of another image
//              and places the results in a destination image.
//
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         One of the pointers is NULL
//    ippStsSizeErr            roiSize has a field with zero or negative value
//    ippStsStepErr            At least one step value is less than or equal to zero
//    ippStsDivByZero          A warning that a divisor value is zero, the function
//                             execution is continued.
//                             If a dividend is equal to zero, then the result is NAN_32F;
//                             if it is greater than zero, then the result is INF_32F,
//                             if it is less than zero, then the result is INF_NEG_32F
//
//  Parameters:
//    pSrc1                    Pointer to the divisor source image
//    src1Step                 Step through the divisor source image
//    pSrc2                    Pointer to the dividend source image
//    src2Step                 Step through the dividend source image
//    pDst                     Pointer to the destination image
//    dstStep                  Step through the destination image
//    roiSize                  Size of the ROI
*/

IPPAPI(IppStatus, ippiDiv_32f_C1R,    (const Ipp32f* pSrc1, int src1Step,
                                       const Ipp32f* pSrc2, int src2Step,
                                             Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiDiv_32f_C3R,    (const Ipp32f* pSrc1, int src1Step,
                                       const Ipp32f* pSrc2, int src2Step,
                                             Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiDiv_32f_C4R,    (const Ipp32f* pSrc1, int src1Step,
                                       const Ipp32f* pSrc2, int src2Step,
                                             Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiDiv_32f_AC4R,    (const Ipp32f* pSrc1, int src1Step,
                                        const Ipp32f* pSrc2, int src2Step,
                                             Ipp32f* pDst, int dstStep, IppiSize roiSize))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiDiv_16s_C1RSfs, ippiDiv_8u_C1RSfs, ippiDiv_16u_C1RSfs,
//              ippiDiv_16s_C3RSfs, ippiDiv_8u_C3RSfs, ippiDiv_16u_C3RSfs,
//              ippiDiv_16s_C4RSfs, ippiDiv_8u_C4RSfs, ippiDiv_16u_C4RSfs,
//              ippiDiv_16s_AC4RSfs,ippiDiv_8u_AC4RSfs,ippiDiv_16u_AC4RSfs
//
//  Purpose:    Divides pixel values of an image by pixel values of
//              another image and places the scaled results in a destination
//              image.
//
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         One of the pointers is NULL
//    ippStsSizeErr            roiSize has a field with zero or negative value
//    ippStsStepErr            At least one step value is less than or equal to zero
//    ippStsDivByZero          A warning that a divisor value is zero, the function
//                             execution is continued.
//                    If a dividend is equal to zero, then the result is zero;
//                    if it is greater than zero, then the result is IPP_MAX_16S, or IPP_MAX_8U, or IPP_MAX_16U
//                    if it is less than zero (for 16s), then the result is IPP_MIN_16S
//
//  Parameters:
//    pSrc1                    Pointer to the divisor source image
//    src1Step                 Step through the divisor source image
//    pSrc2                    Pointer to the dividend source image
//    src2Step                 Step through the dividend source image
//    pDst                     Pointer to the destination image
//    dstStep                  Step through the destination image
//    roiSize                  Size of the ROI
//    scaleFactor              Scale factor
*/

IPPAPI(IppStatus, ippiDiv_16s_C1RSfs, (const Ipp16s* pSrc1, int src1Step,
                                       const Ipp16s* pSrc2, int src2Step,
                                             Ipp16s* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_16s_C3RSfs, (const Ipp16s* pSrc1, int src1Step,
                                       const Ipp16s* pSrc2, int src2Step,
                                             Ipp16s* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_16s_C4RSfs, (const Ipp16s* pSrc1, int src1Step,
                                       const Ipp16s* pSrc2, int src2Step,
                                       Ipp16s* pDst, int dstStep, IppiSize roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_16s_AC4RSfs, (const Ipp16s* pSrc1, int src1Step,
                                       const Ipp16s* pSrc2, int src2Step,
                                       Ipp16s* pDst, int dstStep, IppiSize roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_8u_C1RSfs,  (const Ipp8u* pSrc1, int src1Step,
                                       const Ipp8u* pSrc2, int src2Step,
                                             Ipp8u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_8u_C3RSfs,  (const Ipp8u* pSrc1, int src1Step,
                                       const Ipp8u* pSrc2, int src2Step,
                                             Ipp8u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_8u_C4RSfs, (const Ipp8u* pSrc1, int src1Step,
                                       const Ipp8u* pSrc2, int src2Step,
                                       Ipp8u* pDst, int dstStep, IppiSize roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_8u_AC4RSfs, (const Ipp8u* pSrc1, int src1Step,
                                       const Ipp8u* pSrc2, int src2Step,
                                       Ipp8u* pDst, int dstStep, IppiSize roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_16u_C1RSfs, (const Ipp16u* pSrc1, int src1Step,
                                       const Ipp16u* pSrc2, int src2Step,
                                             Ipp16u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_16u_C3RSfs, (const Ipp16u* pSrc1, int src1Step,
                                       const Ipp16u* pSrc2, int src2Step,
                                             Ipp16u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_16u_C4RSfs, (const Ipp16u* pSrc1, int src1Step,
                                       const Ipp16u* pSrc2, int src2Step,
                                       Ipp16u* pDst, int dstStep, IppiSize roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_16u_AC4RSfs, (const Ipp16u* pSrc1, int src1Step,
                                       const Ipp16u* pSrc2, int src2Step,
                                       Ipp16u* pDst, int dstStep, IppiSize roiSize, int ScaleFactor))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiDivC_32f_C1R, ippiDivC_32f_C3R
//              ippiDivC_32f_C4R, ippiDivC_32f_AC4R
//
//  Purpose:    Divides pixel values of a source image by a constant
//              and places the results in a destination image.
//
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         One of the pointers is NULL
//    ippStsSizeErr            roiSize has a field with zero or negative value
//    ippStsStepErr            step value is less than or equal to zero
//    ippStsDivByZeroErr       The constant is equal to zero
//
//  Parameters:
//    value                    The constant divisor
//    pSrc                     Pointer to the source image
//    pDst                     Pointer to the destination image
//    roiSize                  Size of the ROI
*/

IPPAPI(IppStatus, ippiDivC_32f_C1R,    (const Ipp32f* pSrc, int srcStep, Ipp32f value,
                                        Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiDivC_32f_C3R,    (const Ipp32f* pSrc, int srcStep, const Ipp32f value[3],
                                        Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiDivC_32f_C4R, (const Ipp32f* pSrc, int srcStep, const Ipp32f val[4],
                                     Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiDivC_32f_AC4R,(const Ipp32f* pSrc, int srcStep, const Ipp32f val[3],
                                     Ipp32f* pDst, int dstStep, IppiSize roiSize))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiDivC_16s_C1RSfs, ippiDivC_8u_C1RSfs, ippiDivC_16u_C1RSfs,
//              ippiDivC_16s_C3RSfs, ippiDivC_8u_C3RSfs, ippiDivC_16u_C3RSfs,
//              ippiDivC_16s_C4RSfs, ippiDivC_8u_C4RSfs, ippiDivC_16u_C4RSfs,
//              ippiDivC_16s_AC4RSfs,ippiDivC_8u_AC4RSfs,ippiDivC_16u_AC4RSfs
//
//  Purpose:    Divides pixel values of a source image by a constant
//              and places the scaled results in a destination image.
//
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         One of the pointers is NULL
//    ippStsSizeErr            roiSize has a field with zero or negative value
//    ippStsStepErr            Step value is less than or equal to zero
//    ippStsDivByZeroErr       The constant is equal to zero
//
//  Parameters:
//    value                    Constant divisor
//    pSrc                     Pointer to the source image
//    pDst                     Pointer to the destination image
//    roiSize                  Size of the ROI
//    scaleFactor              Scale factor
*/

IPPAPI(IppStatus, ippiDivC_16s_C1RSfs, (const Ipp16s* pSrc, int srcStep, Ipp16s value,
                                        Ipp16s* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_16s_C3RSfs, (const Ipp16s* pSrc, int srcStep, const Ipp16s value[3],
                                        Ipp16s* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_16s_C4RSfs,  (const Ipp16s* pSrc, int srcStep, const Ipp16s value[4],
                                        Ipp16s* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_16s_AC4RSfs,  (const Ipp16s* pSrc, int srcStep, const Ipp16s value[3],
                                        Ipp16s* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_8u_C1RSfs,  (const Ipp8u* pSrc, int srcStep, Ipp8u value,
                                        Ipp8u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_8u_C3RSfs,  (const Ipp8u* pSrc, int srcStep, const Ipp8u value[3],
                                        Ipp8u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_8u_C4RSfs,  (const Ipp8u* pSrc, int srcStep, const Ipp8u value[4],
                                        Ipp8u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_8u_AC4RSfs,  (const Ipp8u* pSrc, int srcStep, const Ipp8u value[3],
                                        Ipp8u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_16u_C1RSfs, (const Ipp16u* pSrc, int srcStep, Ipp16u value,
                                        Ipp16u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_16u_C3RSfs, (const Ipp16u* pSrc, int srcStep, const Ipp16u value[3],
                                        Ipp16u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_16u_C4RSfs,  (const Ipp16u* pSrc, int srcStep, const Ipp16u value[4],
                                        Ipp16u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_16u_AC4RSfs,  (const Ipp16u* pSrc, int srcStep, const Ipp16u value[3],
                                        Ipp16u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiDiv_32f_C1IR, ippiDiv_32f_C3IR ippiDiv_32f_C4IR ippiDiv_32f_AC4IR
//
//  Purpose:    Divides pixel values of an image by pixel values of
//              another image and places the results in the dividend source
//              image.
//
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         One of the pointers is NULL
//    ippStsSizeErr            roiSize has a field with zero or negative value
//    ippStsStepErr            At least one step value is less than or equal to zero
//    ippStsDivByZero          A warning that a divisor value is zero, the function
//                             execution is continued.
//                             If a dividend is equal to zero, then the result is NAN_32F;
//                             if it is greater than zero, then the result is INF_32F,
//                             if it is less than zero, then the result is INF_NEG_32F
//
//  Parameters:
//    pSrc                     Pointer to the divisor source image
//    srcStep                  Step through the divisor source image
//    pSrcDst                  Pointer to the dividend source/destination image
//    srcDstStep               Step through the dividend source/destination image
//    roiSize                  Size of the ROI
*/

IPPAPI(IppStatus, ippiDiv_32f_C1IR,    (const Ipp32f* pSrc, int srcStep,
                                              Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiDiv_32f_C3IR,    (const Ipp32f* pSrc, int srcStep,
                                              Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiDiv_32f_C4IR,    (const Ipp32f* pSrc, int srcStep,
                                              Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiDiv_32f_AC4IR,    (const Ipp32f* pSrc, int srcStep,
                                              Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiDiv_16s_C1IRSfs, ippiDiv_8u_C1IRSfs, ippiDiv_16u_C1IRSfs,
//              ippiDiv_16s_C3IRSfs, ippiDiv_8u_C3IRSfs, ippiDiv_16u_C3IRSfs,
//              ippiDiv_16s_C4IRSfs, ippiDiv_8u_C4IRSfs, ippiDiv_16u_C4IRSfs,
//              ippiDiv_16s_AC4IRSfs,ippiDiv_8u_AC4IRSfs,ippiDiv_16u_AC4IRSfs
//
//  Purpose:    Divides pixel values of an image by pixel values of
//              another image and places the scaled results in the dividend
//              source image.
//
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         One of the pointers is NULL
//    ippStsSizeErr            roiSize has a field with zero or negative value
//    ippStsStepErr            At least one step value is less than or equal to zero
//    ippStsDivByZero          A warning that a divisor value is zero, the function
//                             execution is continued.
//                    If a dividend is equal to zero, then the result is zero;
//                    if it is greater than zero, then the result is IPP_MAX_16S, or IPP_MAX_8U, or IPP_MAX_16U
//                    if it is less than zero (for 16s), then the result is IPP_MIN_16S
//
//  Parameters:
//    pSrc                     Pointer to the divisor source image
//    srcStep                  Step through the divisor source image
//    pSrcDst                  Pointer to the dividend source/destination image
//    srcDstStep               Step through the dividend source/destination image
//    roiSize                  Size of the ROI
//    scaleFactor              Scale factor
*/

IPPAPI(IppStatus, ippiDiv_16s_C1IRSfs, (const Ipp16s* pSrc, int srcStep,
                                              Ipp16s* pSrcDst, int srcDstStep,
                                              IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_16s_C3IRSfs, (const Ipp16s* pSrc, int srcStep,
                                              Ipp16s* pSrcDst, int srcDstStep,
                                              IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_16s_C4IRSfs, (const Ipp16s* pSrc, int srcStep,
                                              Ipp16s* pSrcDst, int srcDstStep,
                                              IppiSize roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_16s_AC4IRSfs, (const Ipp16s* pSrc, int srcStep,
                                              Ipp16s* pSrcDst, int srcDstStep,
                                              IppiSize roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_8u_C1IRSfs,  (const Ipp8u* pSrc, int srcStep,
                                              Ipp8u* pSrcDst, int srcDstStep,
                                              IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_8u_C3IRSfs,  (const Ipp8u* pSrc, int srcStep,
                                              Ipp8u* pSrcDst, int srcDstStep,
                                              IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_8u_C4IRSfs, (const Ipp8u* pSrc, int srcStep,
                                             Ipp8u* pSrcDst, int srcDstStep,
                                             IppiSize roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_8u_AC4IRSfs, (const Ipp8u* pSrc, int srcStep,
                                             Ipp8u* pSrcDst, int srcDstStep,
                                             IppiSize roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_16u_C1IRSfs, (const Ipp16u* pSrc, int srcStep,
                                              Ipp16u* pSrcDst, int srcDstStep,
                                              IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_16u_C3IRSfs, (const Ipp16u* pSrc, int srcStep,
                                              Ipp16u* pSrcDst, int srcDstStep,
                                              IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_16u_C4IRSfs, (const Ipp16u* pSrc, int srcStep,
                                              Ipp16u* pSrcDst, int srcDstStep,
                                              IppiSize roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_16u_AC4IRSfs, (const Ipp16u* pSrc, int srcStep,
                                              Ipp16u* pSrcDst, int srcDstStep,
                                              IppiSize roiSize, int ScaleFactor))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiDivC_32f_C1IR, ippiDivC_32f_C3IR,
//              ippiDivC_32f_C4IR, ippiDivC_32f_AC4IR
//
//  Purpose:    Divides pixel values of a source image by a constant
//              and places the results in the same image.
//
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         The pointer is NULL
//    ippStsSizeErr            The roiSize has a field with zero or negative value
//    ippStsStepErr            The step value is less than or equal to zero
//    ippStsDivByZeroErr       The constant is equal to zero
//
//  Parameters:
//    value                    The constant divisor
//    pSrcDst                  Pointer to the source/destination image
//    srcDstStep               Step through the source/destination image
//    roiSize                  Size of the ROI
*/

IPPAPI(IppStatus, ippiDivC_32f_C1IR,    (Ipp32f value, Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiDivC_32f_C3IR,    (const Ipp32f value[3], Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiDivC_32f_C4IR, (const Ipp32f val[4], Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiDivC_32f_AC4IR, (const Ipp32f val[3], Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiDivC_16s_C1IRSfs, ippiDivC_8u_C1IRSfs, ippiDivC_16u_C1IRSfs,
//              ippiDivC_16s_C3IRSfs, ippiDivC_8u_C3IRSfs, ippiDivC_16u_C3IRSfs,
//              ippiDivC_16s_C4IRSfs, ippiDivC_8u_C4IRSfs, ippiDivC_16u_C4IRSfs,
//              ippiDivC_16s_AC4IRSfs,ippiDivC_8u_AC4IRSfs,ippiDivC_16u_AC4IRSfs
//
//  Purpose:    Divides pixel values of a source image by a constant
//              and places the scaled results in the same image.
//
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         The pointer is NULL
//    ippStsSizeErr            The roiSize has a field with zero or negative value
//    ippStsStepErr            The step value is less than or equal to zero
//    ippStsDivByZeroErr       The constant is equal to zero
//
//  Parameters:
//    value                    The constant divisor
//    pSrcDst                  Pointer to the source/destination image
//    srcDstStep               Step through the source/destination image
//    roiSize                  Size of the ROI
//    scaleFactor              Scale factor
*/

IPPAPI(IppStatus, ippiDivC_16s_C1IRSfs, (Ipp16s value, Ipp16s* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_16s_C3IRSfs, (const Ipp16s value[3], Ipp16s* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_16s_C4IRSfs, (const Ipp16s val[4], Ipp16s* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDivC_16s_AC4IRSfs, (const Ipp16s val[3], Ipp16s* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDivC_8u_C1IRSfs,  (Ipp8u value, Ipp8u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_8u_C3IRSfs,  (const Ipp8u value[3], Ipp8u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_8u_C4IRSfs, (const Ipp8u val[4], Ipp8u* pSrcDst,
                                        int srcDstStep, IppiSize roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDivC_8u_AC4IRSfs, (const Ipp8u val[3], Ipp8u* pSrcDst,
                                        int srcDstStep, IppiSize roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDivC_16u_C1IRSfs, (Ipp16u value, Ipp16u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_16u_C3IRSfs, (const Ipp16u value[3], Ipp16u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_16u_C4IRSfs, (const Ipp16u val[4], Ipp16u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDivC_16u_AC4IRSfs, (const Ipp16u val[3], Ipp16u* pSrcDst,
                                         int srcDstStep, IppiSize roiSize, int ScaleFactor))


/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiAbs_16s_C1R
//              ippiAbs_16s_C3R
//              ippiAbs_16s_C4R
//              ippiAbs_16s_AC4R
//              ippiAbs_32f_C1R
//              ippiAbs_32f_C3R
//              ippiAbs_32f_C4R
//              ippiAbs_32f_AC4R
//
//              ippiAbs_16s_C1IR
//              ippiAbs_16s_C3IR
//              ippiAbs_16s_C4IR
//              ippiAbs_16s_AC4IR
//              ippiAbs_32f_C1IR
//              ippiAbs_32f_C3IR
//              ippiAbs_32f_C4IR
//              ippiAbs_32f_AC4IR
//
//  Purpose:    computes absolute value of each pixel of a source image and
//              places results in the destination image;
//              for in-place flavors - in the same source image
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  One of the pointers is NULL
//   ippStsSizeErr     The roiSize has a field with negative or zero value
//
//  Parameters:
//   pSrc       pointer to the source image
//   srcStep    step through the source image
//   pDst       pointer to the destination image
//   dstStep    step through the destination image
//   pSrcDst    pointer to the source/destination image (for in-place function)
//   srcDstStep step through the source/destination image (for in-place function)
//   roiSize    size of the ROI
*/
IPPAPI(IppStatus,ippiAbs_16s_C1R,(const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
       IppiSize roiSize))
IPPAPI(IppStatus,ippiAbs_16s_C3R,(const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
       IppiSize roiSize))
IPPAPI(IppStatus,ippiAbs_16s_AC4R,(const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
       IppiSize roiSize))
IPPAPI(IppStatus,ippiAbs_32f_C1R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
       IppiSize roiSize))
IPPAPI(IppStatus,ippiAbs_32f_C3R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
       IppiSize roiSize))
IPPAPI(IppStatus,ippiAbs_32f_AC4R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
       IppiSize roiSize))
IPPAPI(IppStatus,ippiAbs_16s_C1IR,(Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiAbs_16s_C3IR,(Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiAbs_16s_AC4IR,(Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiAbs_32f_C1IR,(Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiAbs_32f_C3IR,(Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiAbs_32f_AC4IR,(Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiAbs_16s_C4R,(const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
       IppiSize roiSize))
IPPAPI(IppStatus,ippiAbs_32f_C4R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
       IppiSize roiSize))
IPPAPI(IppStatus,ippiAbs_16s_C4IR,(Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiAbs_32f_C4IR,(Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))


/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiSqr_8u_C1RSfs
//              ippiSqr_8u_C3RSfs
//              ippiSqr_8u_AC4RSfs
//              ippiSqr_8u_C4RSfs
//              ippiSqr_16u_C1RSfs
//              ippiSqr_16u_C3RSfs
//              ippiSqr_16u_AC4RSfs
//              ippiSqr_16u_C4RSfs
//              ippiSqr_16s_C1RSfs
//              ippiSqr_16s_C3RSfs
//              ippiSqr_16s_AC4RSfs
//              ippiSqr_16s_C4RSfs
//              ippiSqr_32f_C1R
//              ippiSqr_32f_C3R
//              ippiSqr_32f_AC4R
//              ippiSqr_32f_C4R
//
//              ippiSqr_8u_C1IRSfs
//              ippiSqr_8u_C3IRSfs
//              ippiSqr_8u_AC4IRSfs
//              ippiSqr_8u_C4IRSfs
//              ippiSqr_16u_C1IRSfs
//              ippiSqr_16u_C3IRSfs
//              ippiSqr_16u_AC4IRSfs
//              ippiSqr_16u_C4IRSfs
//              ippiSqr_16s_C1IRSfs
//              ippiSqr_16s_C3IRSfs
//              ippiSqr_16s_AC4IRSfs
//              ippiSqr_16s_C4IRSfs
//              ippiSqr_32f_C1IR
//              ippiSqr_32f_C3IR
//              ippiSqr_32f_AC4IR
//              ippiSqr_32f_C4IR
//
//  Purpose:    squares pixel values of an image and
//              places results in the destination image;
//              for in-place flavors - in  the same image
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  One of the pointers is NULL
//   ippStsSizeErr     The roiSize has a field with negative or zero value
//
//  Parameters:
//   pSrc       pointer to the source image
//   srcStep    step through the source image
//   pDst       pointer to the destination image
//   dstStep    step through the destination image
//   pSrcDst    pointer to the source/destination image (for in-place function)
//   srcDstStep step through the source/destination image (for in-place function)
//   roiSize    size of the ROI
//   scaleFactor scale factor
*/

IPPAPI(IppStatus,ippiSqr_8u_C1RSfs,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqr_8u_C3RSfs,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqr_8u_AC4RSfs,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqr_8u_C4RSfs,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqr_16u_C1RSfs,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqr_16u_C3RSfs,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqr_16u_AC4RSfs,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqr_16u_C4RSfs,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqr_16s_C1RSfs,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqr_16s_C3RSfs,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqr_16s_AC4RSfs,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqr_16s_C4RSfs,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqr_32f_C1R, (const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiSqr_32f_C3R, (const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiSqr_32f_AC4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiSqr_32f_C4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiSqr_8u_C1IRSfs, (Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqr_8u_C3IRSfs, (Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqr_8u_AC4IRSfs,(Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqr_8u_C4IRSfs,(Ipp8u* pSrcDst, int srcDstStep,

       IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqr_16u_C1IRSfs, (Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqr_16u_C3IRSfs, (Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqr_16u_AC4IRSfs,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqr_16u_C4IRSfs,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqr_16s_C1IRSfs, (Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqr_16s_C3IRSfs, (Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqr_16s_AC4IRSfs,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqr_16s_C4IRSfs,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqr_32f_C1IR, (Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize))
IPPAPI(IppStatus,ippiSqr_32f_C3IR, (Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize))
IPPAPI(IppStatus,ippiSqr_32f_AC4IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize))
IPPAPI(IppStatus,ippiSqr_32f_C4IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize))


/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiSqrt_8u_C1RSfs
//              ippiSqrt_8u_C3RSfs
//              ippiSqrt_8u_AC4RSfs
//              ippiSqrt_16u_C1RSfs
//              ippiSqrt_16u_C3RSfs
//              ippiSqrt_16u_AC4RSfs
//              ippiSqrt_16s_C1RSfs
//              ippiSqrt_16s_C3RSfs
//              ippiSqrt_16s_AC4RSfs
//              ippiSqrt_32f_C1R
//              ippiSqrt_32f_C3R
//              ippiSqrt_32f_AC4R
//
//              ippiSqrt_8u_C1IRSfs
//              ippiSqrt_8u_C3IRSfs
//              ippiSqrt_8u_AC4IRSfs
//              ippiSqrt_16u_C1IRSfs
//              ippiSqrt_16u_C3IRSfs
//              ippiSqrt_16u_AC4IRSfs
//              ippiSqrt_16s_C1IRSfs
//              ippiSqrt_16s_C3IRSfs
//              ippiSqrt_16s_AC4IRSfs
//              ippiSqrt_32f_C1IR
//              ippiSqrt_32f_C3IR
//              ippiSqrt_32f_AC4IR
//              ippiSqrt_32f_C4IR
//  Purpose:    computes square roots of pixel values of a source image and
//              places results in the destination image;
//              for in-place flavors - in the same image
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  One of pointers is NULL
//   ippStsSizeErr     The roiSize has a field with negative or zero value
//   ippStsSqrtNegArg  Source image pixel has a negative value
//
//  Parameters:
//   pSrc       pointer to the source image
//   srcStep    step through the source image
//   pDst       pointer to the destination image
//   dstStep    step through the destination image
//   pSrcDst    pointer to the source/destination image (for in-place function)
//   srcDstStep step through the source/destination image (for in-place function)
//   roiSize    size of the ROI
//   scaleFactor scale factor
*/
IPPAPI(IppStatus,ippiSqrt_8u_C1RSfs,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqrt_8u_C3RSfs,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqrt_8u_AC4RSfs,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqrt_16u_C1RSfs,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqrt_16u_C3RSfs,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqrt_16u_AC4RSfs,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqrt_16s_C1RSfs,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqrt_16s_C3RSfs,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqrt_16s_AC4RSfs,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqrt_32f_C1R, (const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiSqrt_32f_C3R, (const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiSqrt_32f_AC4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiSqrt_8u_C1IRSfs, (Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqrt_8u_C3IRSfs, (Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqrt_8u_AC4IRSfs,(Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqrt_16u_C1IRSfs, (Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqrt_16u_C3IRSfs, (Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqrt_16u_AC4IRSfs,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqrt_16s_C1IRSfs, (Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqrt_16s_C3IRSfs, (Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqrt_16s_AC4IRSfs,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus,ippiSqrt_32f_C1IR, (Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize))
IPPAPI(IppStatus,ippiSqrt_32f_C3IR, (Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize))
IPPAPI(IppStatus,ippiSqrt_32f_AC4IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize))

IPPAPI(IppStatus,ippiSqrt_32f_C4IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize))



/* /////////////////////////////////////////////////////////////////////////////
//  Names:
//  ippiLn_32f_C1IR   ippiLn_16s_C1IRSfs  ippiLn_8u_C1IRSfs ippiLn_16u_C1IRSfs
//  ippiLn_32f_C3IR   ippiLn_16s_C3IRSfs  ippiLn_8u_C3IRSfs ippiLn_16u_C3IRSfs
//  ippiLn_32f_C1R    ippiLn_16s_C1RSfs   ippiLn_8u_C1RSfs  ippiLn_16u_C1RSfs
//  ippiLn_32f_C3R    ippiLn_16s_C3RSfs   ippiLn_8u_C3RSfs  ippiLn_16u_C3RSfs
//  Purpose:
//     computes the natural logarithm of each pixel values of a source image
//     and places the results in the destination image;
//     for in-place flavors - in the same image
//  Parameters:
//    pSrc         Pointer to the source image.
//    pDst         Pointer to the destination image.
//    pSrcDst      Pointer to the source/destination image for in-place functions.
//    srcStep      Step through the source image.
//    dstStep      Step through the destination image.
//    srcDstStep   Step through the source/destination image for in-place functions.
//    roiSize      Size of the ROI.
//    scaleFactor  Scale factor for integer data.
//  Returns:
//    ippStsNullPtrErr    One of the pointers is NULL
//    ippStsSizeErr       The roiSize has a field with negative or zero value
//    ippStsStepErr       One of the step values is less than or equal to zero
//    ippStsLnZeroArg     The source pixel has a zero value
//    ippStsLnNegArg      The source pixel has a negative value
//    ippStsNoErr         otherwise
*/

IPPAPI(IppStatus, ippiLn_32f_C1IR,(Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLn_32f_C3IR,(Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLn_32f_C1R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst,
                                                       int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLn_32f_C3R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst,
                                                       int dstStep, IppiSize roiSize))

IPPAPI(IppStatus, ippiLn_16s_C1IRSfs,(Ipp16s* pSrcDst, int srcDstStep,
                                    IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiLn_16s_C3IRSfs,(Ipp16s* pSrcDst, int srcDstStep,
                                    IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiLn_16s_C1RSfs, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst,

                                     int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiLn_16s_C3RSfs, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst,
                                     int dstStep, IppiSize roiSize, int scaleFactor))

IPPAPI(IppStatus,ippiLn_16u_C1RSfs,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst,
                                        int dstStep, IppiSize roiSize, int ScalFact))
IPPAPI(IppStatus,ippiLn_16u_C3RSfs,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst,
                                        int dstStep, IppiSize roiSize, int ScalFact))


IPPAPI(IppStatus, ippiLn_8u_C1IRSfs,(Ipp8u* pSrcDst, int srcDstStep,
                                    IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiLn_8u_C3IRSfs,(Ipp8u* pSrcDst, int srcDstStep,
                                    IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiLn_8u_C1RSfs, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst,
                                     int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiLn_8u_C3RSfs, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst,
                                     int dstStep, IppiSize roiSize, int scaleFactor))

IPPAPI(IppStatus,ippiLn_16u_C1IRSfs,(Ipp16u* pSrcDst, int srcDstStep,
                                        IppiSize roiSize, int ScalFact))
IPPAPI(IppStatus,ippiLn_16u_C3IRSfs,(Ipp16u* pSrcDst, int srcDstStep,
                                        IppiSize roiSize, int ScalFact))


/* /////////////////////////////////////////////////////////////////////////////
//  Names:
//  ippiExp_32f_C1IR   ippiExp_16s_C1IRSfs  ippiExp_8u_C1IRSfs ippiExp_16u_C1IRSfs
//  ippiExp_32f_C3IR   ippiExp_16s_C3IRSfs  ippiExp_8u_C3IRSfs ippiExp_16u_C3IRSfs
//  ippiExp_32f_C1R    ippiExp_16s_C1RSfs   ippiExp_8u_C1RSfs  ippiExp_16u_C1RSfs
//  ippiExp_32f_C3R    ippiExp_16s_C3RSfs   ippiExp_8u_C3RSfs  ippiExp_16u_C3RSfs
//  Purpose:
//     computes the exponential of pixel values in a source image
//  Parameters:
//    pSrc         Pointer to the source image.
//    pDst         Pointer to the destination image.
//    pSrcDst      Pointer to the source/destination image for in-place functions.
//    srcStep      Step through the source image.
//    dstStep      Step through the in destination image.
//    srcDstStep   Step through the source/destination image for in-place functions.
//    roiSize      Size of the ROI.
//    scaleFactor  Scale factor for integer data.

//  Returns:
//    ippStsNullPtrErr    One of the pointers is NULL
//    ippStsSizeErr       The roiSize has a field with negative or zero value
//    ippStsStepErr       One of the step values is less than or equal to zero
//    ippStsNoErr         otherwise
*/


IPPAPI(IppStatus, ippiExp_32f_C1IR,(Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiExp_32f_C3IR,(Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiExp_32f_C1R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst,
                                                       int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiExp_32f_C3R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst,
                                                       int dstStep, IppiSize roiSize))

IPPAPI(IppStatus, ippiExp_16s_C1IRSfs,(Ipp16s* pSrcDst, int srcDstStep,
                                    IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiExp_16s_C3IRSfs,(Ipp16s* pSrcDst, int srcDstStep,
                                    IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiExp_16s_C1RSfs, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst,
                                     int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiExp_16s_C3RSfs, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst,
                                     int dstStep, IppiSize roiSize, int scaleFactor))

IPPAPI(IppStatus,ippiExp_16u_C1IRSfs,(Ipp16u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int sFact))
IPPAPI(IppStatus,ippiExp_16u_C3IRSfs,(Ipp16u* pSrcDst, int srcDstStep,
                                          IppiSize roiSize, int sFact))


IPPAPI(IppStatus, ippiExp_8u_C1IRSfs,(Ipp8u* pSrcDst, int srcDstStep,
                                    IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiExp_8u_C3IRSfs,(Ipp8u* pSrcDst, int srcDstStep,
                                    IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiExp_8u_C1RSfs, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst,
                                     int dstStep, IppiSize roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiExp_8u_C3RSfs, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst,
                                     int dstStep, IppiSize roiSize, int scaleFactor))

IPPAPI(IppStatus,ippiExp_16u_C1RSfs,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst,
                                          int dstStep, IppiSize roiSize, int sFact))
IPPAPI(IppStatus,ippiExp_16u_C3RSfs,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst,
                                          int dstStep, IppiSize roiSize, int sFact))

/* /////////////////////////////////////////////////////////////////////////////////////////////////
//                      Multiplication with Scaling
///////////////////////////////////////////////////////////////////////////////////////////////// */
/*
//  Names:              ippiMulScale, ippiMulCScale
//
//  Purpose:            Multiplies pixel values of two images (MulScale),
//                      or pixel values of an image by a constant (MulScaleC) and scales the products
//
//  Parameters:
//   value              The constant value (constant vector for multi-channel images)
//   pSrc               Pointer to the source image
//   srcStep            Step through the source image
//   pSrcDst            Pointer to the source/destination image (in-place operations)
//   srcDstStep         Step through the source/destination image (in-place operations)
//   pSrc1              Pointer to the first source image
//   src1Step           Step through the first source image
//   pSrc2              Pointer to the second source image
//   src2Step           Step through the second source image
//   pDst               Pointer to the destination image
//   dstStep            Step through the destination image
//   roiSize            Size of the image ROI
//
//  Returns:
//   ippStsNullPtrErr   One of the pointers is NULL
//   ippStsStepErr      One of the step values is less than or equal to zero
//   ippStsSizeErr      The roiSize has a field with negative or zero value
//   ippStsNoErr        otherwise
*/

IPPAPI(IppStatus, ippiMulScale_8u_C1R, (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulScale_8u_C3R, (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulScale_8u_C4R, (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulScale_8u_AC4R, (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulScale_8u_C1IR, (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulScale_8u_C3IR, (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulScale_8u_C4IR, (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulScale_8u_AC4IR, (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulCScale_8u_C1R, (const Ipp8u* pSrc, int srcStep, Ipp8u value, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulCScale_8u_C3R, (const Ipp8u* pSrc, int srcStep, const Ipp8u value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulCScale_8u_C4R, (const Ipp8u* pSrc, int srcStep, const Ipp8u value[4], Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulCScale_8u_AC4R, (const Ipp8u* pSrc, int srcStep, const Ipp8u value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulCScale_8u_C1IR, (Ipp8u value, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulCScale_8u_C3IR, (const Ipp8u value[3], Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulCScale_8u_C4IR, (const Ipp8u value[4], Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulCScale_8u_AC4IR, (const Ipp8u value[3], Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))

IPPAPI(IppStatus, ippiMulScale_16u_C1R, (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulScale_16u_C3R, (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulScale_16u_C4R, (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulScale_16u_AC4R, (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulScale_16u_C1IR, (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulScale_16u_C3IR, (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulScale_16u_C4IR, (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulScale_16u_AC4IR, (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulCScale_16u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp16u value, Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulCScale_16u_C3R, (const Ipp16u* pSrc, int srcStep, const Ipp16u value[3], Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulCScale_16u_C4R, (const Ipp16u* pSrc, int srcStep, const Ipp16u value[4], Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulCScale_16u_AC4R, (const Ipp16u* pSrc, int srcStep, const Ipp16u value[3], Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulCScale_16u_C1IR, (Ipp16u value, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulCScale_16u_C3IR, (const Ipp16u value[3], Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulCScale_16u_C4IR, (const Ipp16u value[4], Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulCScale_16u_AC4IR, (const Ipp16u value[3], Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))

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
IPPAPI(IppStatus, ippiDotProd_8u64f_C1R,(const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, IppiSize roiSize, Ipp64f *pDp))
IPPAPI(IppStatus, ippiDotProd_16u64f_C1R,(const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, IppiSize roiSize, Ipp64f *pDp))
IPPAPI(IppStatus, ippiDotProd_16s64f_C1R,(const Ipp16s* pSrc1, int src1Step, const Ipp16s* pSrc2, int src2Step, IppiSize roiSize, Ipp64f *pDp))
IPPAPI(IppStatus, ippiDotProd_32u64f_C1R,(const Ipp32u* pSrc1, int src1Step, const Ipp32u* pSrc2, int src2Step, IppiSize roiSize, Ipp64f *pDp))
IPPAPI(IppStatus, ippiDotProd_32s64f_C1R,(const Ipp32s* pSrc1, int src1Step, const Ipp32s* pSrc2, int src2Step, IppiSize roiSize, Ipp64f *pDp))
IPPAPI(IppStatus, ippiDotProd_32f64f_C1R,(const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2, int src2Step, IppiSize roiSize, Ipp64f *pDp, IppHintAlgorithm hint))

IPPAPI(IppStatus, ippiDotProd_8u64f_C3R,(const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, IppiSize roiSize, Ipp64f pDp[3]))
IPPAPI(IppStatus, ippiDotProd_16u64f_C3R,(const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, IppiSize roiSize, Ipp64f pDp[3]))
IPPAPI(IppStatus, ippiDotProd_16s64f_C3R,(const Ipp16s* pSrc1, int src1Step, const Ipp16s* pSrc2, int src2Step, IppiSize roiSize, Ipp64f pDp[3]))
IPPAPI(IppStatus, ippiDotProd_32u64f_C3R,(const Ipp32u* pSrc1, int src1Step, const Ipp32u* pSrc2, int src2Step, IppiSize roiSize, Ipp64f pDp[3]))
IPPAPI(IppStatus, ippiDotProd_32s64f_C3R,(const Ipp32s* pSrc1, int src1Step, const Ipp32s* pSrc2, int src2Step, IppiSize roiSize, Ipp64f pDp[3]))
IPPAPI(IppStatus, ippiDotProd_32f64f_C3R,(const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2, int src2Step, IppiSize roiSize, Ipp64f pDp[3], IppHintAlgorithm hint))

IPPAPI(IppStatus, ippiDotProd_8u64f_C4R,(const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, IppiSize roiSize, Ipp64f pDp[4]))
IPPAPI(IppStatus, ippiDotProd_16u64f_C4R,(const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, IppiSize roiSize, Ipp64f pDp[4]))
IPPAPI(IppStatus, ippiDotProd_16s64f_C4R,(const Ipp16s* pSrc1, int src1Step, const Ipp16s* pSrc2, int src2Step, IppiSize roiSize, Ipp64f pDp[4]))
IPPAPI(IppStatus, ippiDotProd_32u64f_C4R,(const Ipp32u* pSrc1, int src1Step, const Ipp32u* pSrc2, int src2Step, IppiSize roiSize, Ipp64f pDp[4]))
IPPAPI(IppStatus, ippiDotProd_32s64f_C4R,(const Ipp32s* pSrc1, int src1Step, const Ipp32s* pSrc2, int src2Step, IppiSize roiSize, Ipp64f pDp[4]))
IPPAPI(IppStatus, ippiDotProd_32f64f_C4R,(const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2, int src2Step, IppiSize roiSize, Ipp64f pDp[4], IppHintAlgorithm hint))

IPPAPI(IppStatus, ippiDotProd_8u64f_AC4R,(const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, IppiSize roiSize, Ipp64f pDp[3]))
IPPAPI(IppStatus, ippiDotProd_16u64f_AC4R,(const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, IppiSize roiSize, Ipp64f pDp[3]))
IPPAPI(IppStatus, ippiDotProd_16s64f_AC4R,(const Ipp16s* pSrc1, int src1Step, const Ipp16s* pSrc2, int src2Step, IppiSize roiSize, Ipp64f pDp[3]))
IPPAPI(IppStatus, ippiDotProd_32u64f_AC4R,(const Ipp32u* pSrc1, int src1Step, const Ipp32u* pSrc2, int src2Step, IppiSize roiSize, Ipp64f pDp[3]))
IPPAPI(IppStatus, ippiDotProd_32s64f_AC4R,(const Ipp32s* pSrc1, int src1Step, const Ipp32s* pSrc2, int src2Step, IppiSize roiSize, Ipp64f pDp[3]))
IPPAPI(IppStatus, ippiDotProd_32f64f_AC4R,(const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2, int src2Step, IppiSize roiSize, Ipp64f pDp[3], IppHintAlgorithm hint))

/* /////////////////////////////////////////////////////////////////////////////
//              Dot product of taps vector and columns,
//                  which are placed in stripe of rows
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiDotProdCol_32f_L2
//              ippiDotProdCol_64f_L2
//
//  Purpose:    Calculates the dot product of taps vector and columns,
//      which are placed in stripe of rows; useful for external vertical
//      filtering pipeline implementation.
//
//  Parameters:
//    ppSrcRow              pointer to set of rows
//    pTaps                 pointer to taps vector
//    tapsLen               taps length and (equal to number of rows)
//    pDst                  pointer where to store the result row
//    width                 width of source and destination rows
//
//  Returns:
//    ippStsNoErr           OK
//    ippStsNullPtrErr      one of the pointers is NULL
//    ippStsSizeErr         width is less than or equal to zero
*/
IPPAPI(IppStatus, ippiDotProdCol_32f_L2, (const Ipp32f *const ppSrcRow[], const Ipp32f *pTaps, int tapsLen, Ipp32f *pDst, int width))
IPPAPI(IppStatus, ippiDotProdCol_64f_L2, (const Ipp64f *const ppSrcRow[], const Ipp64f *pTaps, int tapsLen, Ipp64f *pDst, int width))



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
IPPAPI(IppStatus, ippiMulPack_32f_C1IR, (const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulPack_32f_C3IR, (const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulPack_32f_C4IR, (const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulPack_32f_AC4IR, (const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))

IPPAPI(IppStatus, ippiMulPack_32f_C1R, (const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2, int src2Step, Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulPack_32f_C3R, (const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2, int src2Step, Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulPack_32f_C4R, (const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2, int src2Step, Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulPack_32f_AC4R,(const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2, int src2Step, Ipp32f* pDst, int dstStep, IppiSize roiSize))

IPPAPI(IppStatus, ippiMulPackConj_32f_C1IR, (const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulPackConj_32f_C3IR, (const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulPackConj_32f_C4IR, (const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulPackConj_32f_AC4IR,(const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize))

IPPAPI(IppStatus, ippiMulPackConj_32f_C1R, (const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2, int src2Step, Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulPackConj_32f_C3R, (const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2, int src2Step, Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulPackConj_32f_C4R, (const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2, int src2Step, Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMulPackConj_32f_AC4R,(const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2, int src2Step, Ipp32f* pDst, int dstStep, IppiSize roiSize))



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
IPPAPI (IppStatus, ippiPackToCplxExtend_32f32fc_C1R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, Ipp32fc* pDst, int dstStep ))



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
IPPAPI(IppStatus,ippiCplxExtendToPack_32fc32f_C1R,(const Ipp32fc* pSrc, int srcStep, IppiSize srcSize, Ipp32f* pDst, int dstStep ))
IPPAPI(IppStatus,ippiCplxExtendToPack_32fc32f_C3R,(const Ipp32fc* pSrc, int srcStep, IppiSize srcSize, Ipp32f* pDst, int dstStep ))



/* /////////////////////////////////////////////////////////////////////////////
// Names:         ippiPhasePack
// Purpose:       Computes the phase (in radians) of elements of an image in RCPack2D packed format.
// Parameters:
//    pSrc        - Pointer to the source image.
//    srcStep     - Distances, in bytes, between the starting points of consecutive lines in the source images.
//    pDst        - Pointer to the destination image.
//    dstStep     - Distance, in bytes, between the starting points of consecutive lines in the destination image.
//    dstRoiSize  - Size, in pixels, of the destination ROI.
//    pBuffer     - Pointer to the buffer for internal calculations. Size of the buffer is calculated by ippiPhasePackGetBufferSize_32f.
//    scaleFactor - Scale factor (only for integer data).
// Returns:
//    ippStsNoErr      - OK.
//    ippStsNullPtrErr - Error when any of the specified pointers is NULL.
//    ippStsSizeErr    - Error when dstRoiSize has a field with value less than 1.
//    ippStsStepErr    - Error when srcStep or dstStep has a zero or negative value.
*/
IPPAPI(IppStatus, ippiPhasePack_32f_C1R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippiPhasePack_32f_C3R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, Ipp8u *pBuffer))


/* /////////////////////////////////////////////////////////////////////////////
// Names:         ippiPhasePackGetBufferSize_32f
// Purpose:       Gets the size (in bytes) of the buffer for ippiPhasePack internal calculations.
// Parameters:
//    numChannels - Number of image channels. Possible values are 1 and 3.
//    dstRoiSize  - Size, in pixels, of the destination ROI.
//    pSize       - Pointer to the calculated buffer size (in bytes).
// Return:
//    ippStsNoErr          - OK.
//    ippStsNullPtrErr     - Error when pSize pointer is NULL.
//    ippStsSizeErr        - Error when dstRoiSize has a field with value less than 1.
//    ippStsNumChannelsErr - Error when the numChannels value differs from 1 or 3.
*/
IPPAPI(IppStatus, ippiPhasePackGetBufferSize_32f, (int numChannels, IppiSize dstRoiSize, int *pSize))



/* /////////////////////////////////////////////////////////////////////////////
// Names:         ippiMagnitudePack
// Purpose:       Computes magnitude of elements of an image in RCPack2D packed format.
// Parameters:
//    pSrc        - Pointer to the source image.
//    srcStep     - Distances, in bytes, between the starting points of consecutive lines in the source images.
//    pDst        - Pointer to the destination image.
//    dstStep     - Distance, in bytes, between the starting points of consecutive lines in the destination image.
//    dstRoiSize  - Size, in pixels, of the destination ROI.
//    pBuffer     - Pointer to the buffer for internal calculations. Size of the buffer is calculated by ippiMagnitudePackGetBufferSize_32f.
//    scaleFactor - Scale factor (only for integer data).
// Returns:
//    ippStsNoErr      - OK.
//    ippStsNullPtrErr - Error when any of the specified pointers is NULL.
//    ippStsSizeErr    - Error when dstRoiSize has a field with value less than 1.
//    ippStsStepErr    - Error when srcStep or dstStep has a zero or negative value.
*/
IPPAPI(IppStatus, ippiMagnitudePack_32f_C1R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippiMagnitudePack_32f_C3R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, Ipp8u *pBuffer))


/* /////////////////////////////////////////////////////////////////////////////
// Names:         ippiMagnitudePackGetBufferSize_32f
// Purpose:       Gets the size (in bytes) of the buffer for ippiMagnitudePack internal calculations.
// Parameters:
//    numChannels - Number of image channels. Possible values are 1 and 3.
//    dstRoiSize  - Size, in pixels, of the destination ROI.
//    pSize       - Pointer to the calculated buffer size (in bytes).
// Return:
//    ippStsNoErr          - OK.
//    ippStsNullPtrErr     - Error when pSize pointer is NULL.
//    ippStsSizeErr        - Error when dstRoiSize has a field with value less than 1.
//    ippStsNumChannelsErr - Error when the numChannels value differs from 1 or 3.
*/
IPPAPI(IppStatus, ippiMagnitudePackGetBufferSize_32f, (int numChannels, IppiSize dstRoiSize, int *pSize))



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
IPPAPI(IppStatus, ippiMagnitude_32fc32f_C1R,(const Ipp32fc* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiMagnitude_32fc32f_C3R,(const Ipp32fc* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize))


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
IPPAPI(IppStatus, ippiPhase_32fc32f_C1R,(const Ipp32fc* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiPhase_32fc32f_C3R,(const Ipp32fc* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize))


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
//  Name:           ippiAlphaPremul_8u_AC4R,  ippiAlphaPremul_16u_AC4R
//                  ippiAlphaPremul_8u_AC4IR, ippiAlphaPremul_16u_AC4IR
//                  ippiAlphaPremul_8u_AP4R,  ippiAlphaPremul_16u_AP4R
//                  ippiAlphaPremul_8u_AP4IR, ippiAlphaPremul_16u_AP4IR
//
//  Purpose:        Pre-multiplies pixel values of an image by its alpha values
//                  for 4-channel images
//               For channels 1-3
//                      dst_pixel = (src_pixel * src_alpha) / VAL_MAX
//               For alpha-channel (channel 4)
//                      dst_alpha = src_alpha
//  Parameters:
//     pSrc         Pointer to the source image for pixel-order data,
//                  array of pointers to separate source color planes for planar data
//     srcStep      Step through the source image
//     pDst         Pointer to the destination image for pixel-order data,
//                  array of pointers to separate destination color planes for planar data
//     dstStep      Step through the destination image
//     pSrcDst      Pointer to the source/destination image, or array of pointers
//                  to separate source/destination color planes for in-place functions
//     srcDstStep   Step through the source/destination image for in-place functions
//     roiSize      Size of the source and destination ROI
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       pSrc == NULL, or pDst == NULL, or pSrcDst == NULL
//     ippStsSizeErr          The roiSize has a field with negative or zero value
*/

IPPAPI (IppStatus, ippiAlphaPremul_8u_AC4R,
                   ( const Ipp8u* pSrc, int srcStep,
                     Ipp8u* pDst, int dstStep,
                     IppiSize roiSize ))
IPPAPI (IppStatus, ippiAlphaPremul_16u_AC4R,
                   ( const Ipp16u* pSrc, int srcStep,
                     Ipp16u* pDst, int dstStep,
                     IppiSize roiSize ))

IPPAPI (IppStatus, ippiAlphaPremul_8u_AC4IR,
                   ( Ipp8u* pSrcDst, int srcDstStep,
                     IppiSize roiSize ))
IPPAPI (IppStatus, ippiAlphaPremul_16u_AC4IR,
                   ( Ipp16u* pSrcDst, int srcDstStep,
                     IppiSize roiSize ))


IPPAPI (IppStatus, ippiAlphaPremul_8u_AP4R,
                   ( const Ipp8u* const pSrc[4], int srcStep,
                     Ipp8u* const pDst[4], int dstStep,
                     IppiSize roiSize ))
IPPAPI (IppStatus, ippiAlphaPremul_16u_AP4R,
                   ( const Ipp16u* const pSrc[4], int srcStep,
                     Ipp16u* const pDst[4], int dstStep,
                     IppiSize roiSize ))

IPPAPI (IppStatus, ippiAlphaPremul_8u_AP4IR,
                   ( Ipp8u* const pSrcDst[4], int srcDstStep,
                     IppiSize roiSize ))
IPPAPI (IppStatus, ippiAlphaPremul_16u_AP4IR,
                   ( Ipp16u* const pSrcDst[4], int srcDstStep,
                     IppiSize roiSize ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiAlphaPremulC_8u_AC4R,  ippiAlphaPremulC_16u_AC4R
//                  ippiAlphaPremulC_8u_AC4IR, ippiAlphaPremulC_16u_ACI4R
//                  ippiAlphaPremulC_8u_AP4R,  ippiAlphaPremulC_16u_AP4R
//                  ippiAlphaPremulC_8u_AP4IR, ippiAlphaPremulC_16u_API4R
//
//  Purpose:        Pre-multiplies pixel values of an image by constant alpha values
//                  for 4-channel images
//               For channels 1-3
//                      dst_pixel = (src_pixel * const_alpha) / VAL_MAX
//               For alpha-channel (channel 4)
//                      dst_alpha = const_alpha
//  Parameters:
//     pSrc         Pointer to the source image for pixel-order data,
//                  array of pointers to separate source color planes for planar data
//     srcStep      Step through the source image
//     pDst         Pointer to the destination image for pixel-order data,
//                  array of pointers to separate destination color planes for planar data
//     dstStep      Step through the destination image
//     pSrcDst      Pointer to the source/destination image, or array of pointers
//                  to separate source/destination color planes for in-place functions
//     srcDstStep   Step through the source/destination image for in-place functions
//     alpha        The constant alpha value
//     roiSize      Size of the source and destination ROI
//  Returns:
//     ippStsNoErr            no errors
//     ippStsNullPtrErr       pSrc == NULL, or pDst == NULL, or pSrcDst == NULL
//     ippStsSizeErr          The roiSize has a field with negative or zero value
//
//  Notes:          Value becomes 0 <= alpha <= VAL_MAX
*/

IPPAPI (IppStatus, ippiAlphaPremulC_8u_AC4R,
                   ( const Ipp8u* pSrc, int srcStep,
                     Ipp8u alpha,
                     Ipp8u* pDst, int dstStep,
                     IppiSize roiSize ))
IPPAPI (IppStatus, ippiAlphaPremulC_16u_AC4R,
                   ( const Ipp16u* pSrc, int srcStep,
                     Ipp16u alpha,
                     Ipp16u* pDst, int dstStep,
                     IppiSize roiSize ))

IPPAPI (IppStatus, ippiAlphaPremulC_8u_AC4IR,
                   ( Ipp8u alpha,

                     Ipp8u* pSrcDst, int srcDstStep,
                     IppiSize roiSize ))
IPPAPI (IppStatus, ippiAlphaPremulC_16u_AC4IR,
                   ( Ipp16u alpha,
                     Ipp16u* pSrcDst, int srcDstStep,
                     IppiSize roiSize ))

IPPAPI (IppStatus, ippiAlphaPremulC_8u_AP4R,
                   ( const Ipp8u* const pSrc[4], int srcStep,
                     Ipp8u alpha,
                     Ipp8u* const pDst[4], int dstStep,
                     IppiSize roiSize ))
IPPAPI (IppStatus, ippiAlphaPremulC_16u_AP4R,
                   ( const Ipp16u* const pSrc[4], int srcStep,
                     Ipp16u alpha,
                     Ipp16u* const pDst[4], int dstStep,
                     IppiSize roiSize ))

IPPAPI (IppStatus, ippiAlphaPremulC_8u_AP4IR,
                   ( Ipp8u alpha,
                     Ipp8u* const pSrcDst[4], int srcDstStep,
                     IppiSize roiSize ))
IPPAPI (IppStatus, ippiAlphaPremulC_16u_AP4IR,
                   ( Ipp16u alpha,
                     Ipp16u* const pSrcDst[4], int srcDstStep,
                     IppiSize roiSize ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiAlphaPremulC_8u_C4R,  ippiAlphaPremulC_16u_C4R
//                  ippiAlphaPremulC_8u_C4IR, ippiAlphaPremulC_16u_C4IR
//
//  Purpose:        Pre-multiplies pixel values of an image by constant alpha values
//                  for 4-channel images:
//                      dst_pixel = (src_pixel * const_alpha) / VAL_MAX
//  Parameters:
//     pSrc         Pointer to the source image
//     srcStep      Step through the source image
//     pDst         Pointer to the destination image
//     dstStep      Step through the destination image
//     pSrcDst      Pointer to the source/destination image for in-place functions
//     srcDstStep   Step through the source/destination image for in-place functions
//     alpha        The constant alpha value
//     roiSize      Size of the source and destination ROI
//  Returns:
//     ippStsNoErr            no errors
//     ippStsNullPtrErr       pSrc == NULL, or pDst == NULL, or pSrcDst == NULL
//     ippStsSizeErr          The roiSize has a field with negative or zero value
//
//  Notes:          Value becomes 0 <= alpha <= VAL_MAX
*/

IPPAPI (IppStatus, ippiAlphaPremulC_8u_C4R,
                   ( const Ipp8u* pSrc, int srcStep,
                     Ipp8u alpha,
                     Ipp8u* pDst, int dstStep,
                     IppiSize roiSize ))
IPPAPI (IppStatus, ippiAlphaPremulC_16u_C4R,
                   ( const Ipp16u* pSrc, int srcStep,
                     Ipp16u alpha,
                     Ipp16u* pDst, int dstStep,
                     IppiSize roiSize ))

IPPAPI (IppStatus, ippiAlphaPremulC_8u_C4IR,
                   ( Ipp8u alpha,
                     Ipp8u* pSrcDst, int srcDstStep,
                     IppiSize roiSize ))
IPPAPI (IppStatus, ippiAlphaPremulC_16u_C4IR,
                   ( Ipp16u alpha,
                     Ipp16u* pSrcDst, int srcDstStep,
                     IppiSize roiSize ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiAlphaPremulC_8u_C3R,  ippiAlphaPremulC_16u_C3R
//                  ippiAlphaPremulC_8u_C3IR, ippiAlphaPremulC_16u_C3IR
//  Purpose:        Pre-multiplies pixel values of an image by constant alpha values
//                  for 3-channel images:
//                      dst_pixel = (src_pixel * const_alpha) / VAL_MAX
//  Parameters:
//     pSrc         Pointer to the source image
//     srcStep      Step through the source image
//     pDst         Pointer to the destination image
//     dstStep      Step through the destination image
//     pSrcDst      Pointer to the source/destination image for in-place functions
//     srcDstStep   Step through the source/destination image for in-place functions
//     alpha        The constant alpha value
//     roiSize      Size of the source and destination ROI
//  Returns:
//     ippStsNoErr            no errors
//     ippStsNullPtrErr       pSrc == NULL, or pDst == NULL, or pSrcDst == NULL
//     ippStsSizeErr          The roiSize has a field with negative or zero value
//
//  Notes:          Value becomes 0 <= alpha <= VAL_MAX
*/

IPPAPI (IppStatus, ippiAlphaPremulC_8u_C3R,
                   ( const Ipp8u* pSrc, int srcStep,
                     Ipp8u alpha,
                     Ipp8u* pDst, int dstStep,
                     IppiSize roiSize ))
IPPAPI (IppStatus, ippiAlphaPremulC_16u_C3R,
                   ( const Ipp16u* pSrc, int srcStep,
                     Ipp16u alpha,
                     Ipp16u* pDst, int dstStep,
                     IppiSize roiSize ))

IPPAPI (IppStatus, ippiAlphaPremulC_8u_C3IR,
                   ( Ipp8u alpha,
                     Ipp8u* pSrcDst, int srcDstStep,
                     IppiSize roiSize ))
IPPAPI (IppStatus, ippiAlphaPremulC_16u_C3IR,
                   ( Ipp16u alpha,
                     Ipp16u* pSrcDst, int srcDstStep,
                     IppiSize roiSize ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiAlphaPremulC_8u_C1R,  ippiAlphaPremulC_16u_C1R
//                  ippiAlphaPremulC_8u_C1IR, ippiAlphaPremulC_16u_C1IR
//  Purpose:        Pre-multiplies pixel values of an image by constant alpha values
//                  for 1-channel images:
//                      dst_pixel = (src_pixel * const_alpha) / VAL_MAX
//  Parameters:
//     pSrc         Pointer to the source image
//     srcStep      Step through the source image
//     pDst         Pointer to the destination image
//     dstStep      Step through the destination image
//     pSrcDst      Pointer to the source/destination image for in-place functions
//     srcDstStep   Step through the source/destination image for in-place functions
//     alpha        The constant alpha value
//     roiSize      Size of the source and destination ROI
//  Returns:
//     ippStsNoErr            no errors
//     ippStsNullPtrErr       pSrc == NULL, or pDst == NULL, or pSrcDst == NULL
//     ippStsSizeErr          The roiSize has a field with negative or zero value
//
//  Notes:          Value becomes 0 <= alpha <= VAL_MAX
*/


IPPAPI (IppStatus, ippiAlphaPremulC_8u_C1R,
                   ( const Ipp8u* pSrc, int srcStep,
                     Ipp8u alpha,
                     Ipp8u* pDst, int dstStep,
                     IppiSize roiSize ))
IPPAPI (IppStatus, ippiAlphaPremulC_16u_C1R,
                   ( const Ipp16u* pSrc, int srcStep,
                     Ipp16u alpha,
                     Ipp16u* pDst, int dstStep,
                     IppiSize roiSize ))

IPPAPI (IppStatus, ippiAlphaPremulC_8u_C1IR,
                   ( Ipp8u alpha,
                     Ipp8u* pSrcDst, int srcDstStep,
                     IppiSize roiSize ))
IPPAPI (IppStatus, ippiAlphaPremulC_16u_C1IR,
                   ( Ipp16u alpha,
                     Ipp16u* pSrcDst, int srcDstStep,
                     IppiSize roiSize ))

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

IPPAPI (IppStatus, ippiAlphaComp_8u_AC4R,
                   ( const Ipp8u* pSrc1, int src1Step,

                     const Ipp8u* pSrc2, int src2Step,
                     Ipp8u* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))
IPPAPI (IppStatus, ippiAlphaComp_16u_AC4R,
                   ( const Ipp16u* pSrc1, int src1Step,
                     const Ipp16u* pSrc2, int src2Step,
                     Ipp16u* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))


IPPAPI (IppStatus, ippiAlphaComp_16s_AC4R,
                   ( const Ipp16s* pSrc1, int src1Step,
                     const Ipp16s* pSrc2, int src2Step,
                     Ipp16s* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

IPPAPI (IppStatus, ippiAlphaComp_32s_AC4R,
                   ( const Ipp32s* pSrc1, int src1Step,
                     const Ipp32s* pSrc2, int src2Step,
                     Ipp32s* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

IPPAPI (IppStatus, ippiAlphaComp_32u_AC4R,
                   ( const Ipp32u* pSrc1, int src1Step,
                     const Ipp32u* pSrc2, int src2Step,
                     Ipp32u* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

IPPAPI (IppStatus, ippiAlphaComp_32f_AC4R,
                   ( const Ipp32f* pSrc1, int src1Step,
                     const Ipp32f* pSrc2, int src2Step,
                     Ipp32f* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

IPPAPI (IppStatus, ippiAlphaComp_8u_AP4R,
                   ( const Ipp8u* const pSrc1[4], int src1Step,
                     const Ipp8u* const pSrc2[4], int src2Step,
                     Ipp8u* const pDst[4], int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

IPPAPI (IppStatus, ippiAlphaComp_16u_AP4R,
                   ( const Ipp16u* const pSrc1[4], int src1Step,
                     const Ipp16u* const pSrc2[4], int src2Step,
                     Ipp16u* const pDst[4], int dstStep,
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

IPPAPI (IppStatus, ippiAlphaComp_8u_AC1R,
                   ( const Ipp8u* pSrc1, int src1Step,
                     const Ipp8u* pSrc2, int src2Step,
                     Ipp8u* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))
IPPAPI (IppStatus, ippiAlphaComp_16u_AC1R,
                   ( const Ipp16u* pSrc1, int src1Step,
                     const Ipp16u* pSrc2, int src2Step,
                     Ipp16u* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

IPPAPI (IppStatus, ippiAlphaComp_16s_AC1R,
                   ( const Ipp16s* pSrc1, int src1Step,
                     const Ipp16s* pSrc2, int src2Step,
                     Ipp16s* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

IPPAPI (IppStatus, ippiAlphaComp_32s_AC1R,
                   ( const Ipp32s* pSrc1, int src1Step,
                     const Ipp32s* pSrc2, int src2Step,
                     Ipp32s* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

IPPAPI (IppStatus, ippiAlphaComp_32u_AC1R,
                   ( const Ipp32u* pSrc1, int src1Step,
                     const Ipp32u* pSrc2, int src2Step,
                     Ipp32u* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

IPPAPI (IppStatus, ippiAlphaComp_32f_AC1R,
                   ( const Ipp32f* pSrc1, int src1Step,
                     const Ipp32f* pSrc2, int src2Step,
                     Ipp32f* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))
/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiAlphaCompC_8u_AC4R, ippiAlphaCompC_16u_AC4R
//                  ippiAlphaCompC_8u_AP4R, ippiAlphaCompC_16u_AP4R
//
//  Purpose:        Combines two 4-channel images using constant alpha values
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
//     alpha1       The constant alpha value for the first source image
//     alpha2       The constant alpha value for the second source image
//     alphaType    The type of composition to perform
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       pSrc1== NULL, or pSrc2== NULL, or pDst == NULL
//     ippStsSizeErr          The roiSize has a field with negative or zero value
//     ippStsAlphaTypeErr     The alphaType is incorrect
//
//  Notes:          Alpha-channel values (channel 4) remain without modifications
//                  Value becomes 0 <= alphaA <= VAL_MAX
//                                0 <= alphaB <= VAL_MAX
*/

IPPAPI (IppStatus, ippiAlphaCompC_8u_AC4R,
                   ( const Ipp8u* pSrc1, int src1Step,
                     Ipp8u alpha1,
                     const Ipp8u* pSrc2, int src2Step,
                     Ipp8u alpha2,
                     Ipp8u* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))
IPPAPI (IppStatus, ippiAlphaCompC_16u_AC4R,
                   ( const Ipp16u* pSrc1, int src1Step,
                     Ipp16u alpha1,
                     const Ipp16u* pSrc2, int src2Step,
                     Ipp16u alpha2,
                     Ipp16u* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

IPPAPI (IppStatus, ippiAlphaCompC_8u_AP4R,
                   ( const Ipp8u* const pSrc1[4], int src1Step,
                     Ipp8u alpha1,
                     const Ipp8u* const pSrc2[4], int src2Step,
                     Ipp8u alpha2,
                     Ipp8u* const pDst[4], int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))
IPPAPI (IppStatus, ippiAlphaCompC_16u_AP4R,
                   ( const Ipp16u* const pSrc1[4], int src1Step,
                     Ipp16u alpha1,
                     const Ipp16u* const pSrc2[4], int src2Step,
                     Ipp16u alpha2,
                     Ipp16u* const pDst[4], int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiAlphaCompC_8u_C4R, ippiAlphaCompC_16u_C4R
//
//  Purpose:        Combines two 4-channel images using constant alpha values
//
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

IPPAPI (IppStatus, ippiAlphaCompC_8u_C4R,
                   ( const Ipp8u* pSrc1, int src1Step,
                     Ipp8u alpha1,
                     const Ipp8u* pSrc2, int src2Step,

                     Ipp8u alpha2,
                     Ipp8u* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))
IPPAPI (IppStatus, ippiAlphaCompC_16u_C4R,
                   ( const Ipp16u* pSrc1, int src1Step,
                     Ipp16u alpha1,
                     const Ipp16u* pSrc2, int src2Step,
                     Ipp16u alpha2,
                     Ipp16u* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiAlphaCompC_8u_C3R, ippiAlphaCompC_16u_C3R
//  Purpose:        Combines two 3-channel images using constant alpha values
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

IPPAPI (IppStatus, ippiAlphaCompC_8u_C3R,
                   ( const Ipp8u* pSrc1, int src1Step,
                     Ipp8u alpha1,
                     const Ipp8u* pSrc2, int src2Step,
                     Ipp8u alpha2,
                     Ipp8u* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))
IPPAPI (IppStatus, ippiAlphaCompC_16u_C3R,
                   ( const Ipp16u* pSrc1, int src1Step,
                     Ipp16u alpha1,
                     const Ipp16u* pSrc2, int src2Step,
                     Ipp16u alpha2,
                     Ipp16u* pDst, int dstStep,
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

IPPAPI (IppStatus, ippiAlphaCompC_8u_C1R,
                   ( const Ipp8u* pSrc1, int src1Step,
                     Ipp8u alpha1,
                     const Ipp8u* pSrc2, int src2Step,
                     Ipp8u alpha2,
                     Ipp8u* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))
IPPAPI (IppStatus, ippiAlphaCompC_16u_C1R,
                   ( const Ipp16u* pSrc1, int src1Step,
                     Ipp16u alpha1,
                     const Ipp16u* pSrc2, int src2Step,
                     Ipp16u alpha2,
                     Ipp16u* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

IPPAPI (IppStatus, ippiAlphaCompC_16s_C1R,
                   ( const Ipp16s* pSrc1, int src1Step,
                     Ipp16s alpha1,
                     const Ipp16s* pSrc2, int src2Step,
                     Ipp16s alpha2,
                     Ipp16s* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))


IPPAPI (IppStatus, ippiAlphaCompC_32s_C1R,
                   ( const Ipp32s* pSrc1, int src1Step,
                     Ipp32s alpha1,
                     const Ipp32s* pSrc2, int src2Step,
                     Ipp32s alpha2,
                     Ipp32s* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

IPPAPI (IppStatus, ippiAlphaCompC_32u_C1R,
                   ( const Ipp32u* pSrc1, int src1Step,
                     Ipp32u alpha1,
                     const Ipp32u* pSrc2, int src2Step,
                     Ipp32u alpha2,
                     Ipp32u* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

IPPAPI (IppStatus, ippiAlphaCompC_32f_C1R,
                   ( const Ipp32f* pSrc1, int src1Step,
                     Ipp32f alpha1,
                     const Ipp32f* pSrc2, int src2Step,
                     Ipp32f alpha2,
                     Ipp32f* pDst, int dstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiAlphaComp_8u_AC4IR, ippiAlphaComp_16u_AC4IR
//                  ippiAlphaComp_8s_AC4IR, ippiAlphaComp_16s_AC4IR
//                  ippiAlphaComp_32s_AC4IR,ippiAlphaComp_32u_AC4IR
//                  ippiAlphaComp_8u_AP4IR, ippiAlphaComp_16u_AP4IR
//
//  Purpose:        Combines two 4-channel images using alpha values of both images
//
//  Parameters:
//     pSrc         Pointer to the source image for pixel-order data,
//                  array of pointers to separate source color planes for planar data
//     srcStep      Step through the source image
//     pSrcDst      Pointer to the source/destination image for pixel-order data,
//                  array of pointers to separate source/destination color planes for planar data
//     srcDstStep   Step through the source/destination image
//     roiSize      Size of the source and destination ROI
//     alphaType    The type of composition to perform
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       pSrc == NULL, or pSrcDst == NULL
//     ippStsSizeErr          The roiSize has a field with negative or zero value
//     ippStsAlphaTypeErr     The alphaType is incorrect
//     Note:                  Result is wrong, if Alpha < 0 for signed types
*/

IPPAPI (IppStatus, ippiAlphaComp_8u_AC4IR,
                   ( const Ipp8u* pSrc, int srcStep,
                     Ipp8u* pSrcDst, int srcDstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

IPPAPI (IppStatus, ippiAlphaComp_16u_AC4IR,
                   ( const Ipp16u* pSrc, int srcStep,
                     Ipp16u* pSrcDst, int srcDstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

IPPAPI (IppStatus, ippiAlphaComp_16s_AC4IR,
                   ( const Ipp16s* pSrc, int srcStep,
                     Ipp16s* pSrcDst, int srcDstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

IPPAPI (IppStatus, ippiAlphaComp_32s_AC4IR,
                   ( const Ipp32s* pSrc, int srcStep,
                     Ipp32s* pSrcDst, int srcDstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

IPPAPI (IppStatus, ippiAlphaComp_32u_AC4IR,
                   ( const Ipp32u* pSrc, int srcStep,
                     Ipp32u* pSrcDst, int srcDstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

IPPAPI (IppStatus, ippiAlphaComp_32f_AC4IR,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pSrcDst, int srcDstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

IPPAPI (IppStatus, ippiAlphaComp_8u_AP4IR,
                   ( const Ipp8u* const pSrc[4], int srcStep,
                     Ipp8u* const pSrcDst[4], int srcDstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

IPPAPI (IppStatus, ippiAlphaComp_16u_AP4IR,
                   ( const Ipp16u* const pSrc[4], int srcStep,
                     Ipp16u* const pSrcDst[4], int srcDstStep,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiAlphaCompC_8u_AC4IR, ippiAlphaCompC_16u_AC4IR
//                  ippiAlphaCompC_8u_AP4IR, ippiAlphaCompC_16u_AP4IR
//
//  Purpose:        Combines two 4-channel images using constant alpha values
//
//  Parameters:
//     pSrc         Pointer to the source image for pixel-order data,
//                  array of pointers to separate source color planes for planar data
//     srcStep      Step through the source image
//     pSrcDst      Pointer to the source/destination image for pixel-order data,
//                  array of pointers to separate source/destination color planes for planar data
//     srcDstStep   Step through the source/destination image
//     roiSize      Size of the source and destination ROI
//     alpha1       The constant alpha value for the source image
//     alpha2       The constant alpha value for the source/destination image
//     alphaType    The type of composition to perform
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       pSrc == NULL, or pSrcDst == NULL
//     ippStsSizeErr          The roiSize has a field with negative or zero value
//     ippStsAlphaTypeErr     The alphaType is incorrect
//
//  Notes:          Alpha-channel values (channel 4) remain without modifications
//                  Value becomes 0 <= alphaA <= VAL_MAX
//                                0 <= alphaB <= VAL_MAX
*/

IPPAPI (IppStatus, ippiAlphaCompC_8u_AC4IR,
                   ( const Ipp8u* pSrc, int srcStep,
                     Ipp8u alpha1,
                     Ipp8u* pSrcDst, int srcDstStep,
                     Ipp8u alpha2,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))
IPPAPI (IppStatus, ippiAlphaCompC_16u_AC4IR,
                   ( const Ipp16u* pSrc, int srcStep,
                     Ipp16u alpha1,
                     Ipp16u* pSrcDst, int srcDstStep,
                     Ipp16u alpha2,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

IPPAPI (IppStatus, ippiAlphaCompC_8u_AP4IR,
                   ( const Ipp8u* const pSrc[4], int srcStep,
                     Ipp8u alpha1,
                     Ipp8u* const pSrcDst[4], int srcDstStep,
                     Ipp8u alpha2,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))
IPPAPI (IppStatus, ippiAlphaCompC_16u_AP4IR,
                   ( const Ipp16u* const pSrc[4], int srcStep,
                     Ipp16u alpha1,
                     Ipp16u* const pSrcDst[4], int srcDstStep,
                     Ipp16u alpha2,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiAlphaCompC_8u_C4IR, ippiAlphaCompC_16u_C4IR
//
//  Purpose:        Combines two 4-channel images using constant alpha values
//
//  Parameters:
//     pSrc         Pointer to the source image
//     srcStep      Step through the source image
//     pSrcDst      Pointer to the source/destination image
//     srcDstStep   Step through the source/destination image
//     roiSize      Size of the source and destination ROI
//     alpha1       The constant alpha value for the source image
//     alpha2       The constant alpha value for the source/destination image
//     alphaType    The type of composition to perform
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       pSrc == NULL, or pSrcDst == NULL
//     ippStsSizeErr          The roiSize has a field with negative or zero value
//     ippStsAlphaTypeErr     The alphaType is incorrect
//
//  Notes:          Value becomes 0 <= alphaA <= VAL_MAX
//                                0 <= alphaB <= VAL_MAX
*/

IPPAPI (IppStatus, ippiAlphaCompC_8u_C4IR,
                   ( const Ipp8u* pSrc, int srcStep,
                     Ipp8u alpha1,
                     Ipp8u* pSrcDst, int srcDstStep,
                     Ipp8u alpha2,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))
IPPAPI (IppStatus, ippiAlphaCompC_16u_C4IR,
                   ( const Ipp16u* pSrc, int srcStep,
                     Ipp16u alpha1,
                     Ipp16u* pSrcDst, int srcDstStep,
                     Ipp16u alpha2,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiAlphaCompC_8u_C3IR, ippiAlphaCompC_16u_C3IR
//  Purpose:        Combines two 3-channel images using constant alpha values
//  Parameters:
//     pSrc         Pointer to the source image
//     srcStep      Step through the source image
//     pSrcDst      Pointer to the source/destination image
//     srcDstStep   Step through the source/destination image
//     roiSize      Size of the source and destination ROI
//     alpha1       The constant alpha value for the source image
//     alpha2       The constant alpha value for the source/destination image
//     alphaType    The type of composition to perform
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       pSrc == NULL, or pSrcDst == NULL
//     ippStsSizeErr          The roiSize has a field with negative or zero value
//     ippStsAlphaTypeErr     The alphaType is incorrect
//
//  Notes:          Value becomes 0 <= alphaA <= VAL_MAX
//                                0 <= alphaB <= VAL_MAX
*/

IPPAPI (IppStatus, ippiAlphaCompC_8u_C3IR,
                   ( const Ipp8u* pSrc, int srcStep,
                     Ipp8u alpha1,
                     Ipp8u* pSrcDst, int srcDstStep,
                     Ipp8u alpha2,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))
IPPAPI (IppStatus, ippiAlphaCompC_16u_C3IR,
                   ( const Ipp16u* pSrc, int srcStep,
                     Ipp16u alpha1,
                     Ipp16u* pSrcDst, int srcDstStep,
                     Ipp16u alpha2,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiAlphaCompC_8u_C1IR, ippiAlphaCompC_16u_C1IR
//                  ippiAlphaCompC_8s_C1IR, ippiAlphaCompC_16s_C1IR
//                  ippiAlphaCompC_32s_C1IR, ippiAlphaCompC_32u_C1IR
//  Purpose:        Combines two 1-channel images using constant alpha values
//  Parameters:
//     pSrc         Pointer to the source image
//     srcStep      Step through the source image
//     pSrcDst      Pointer to the source/destination image
//     srcDstStep   Step through the source/destination image
//     roiSize      Size of the source and destination ROI
//     alpha1       The constant alpha value for the source image
//     alpha2       The constant alpha value for the source/destination image
//     alphaType    The type of composition to perform
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       pSrc == NULL, or pSrcDst == NULL
//     ippStsSizeErr          The roiSize has a field with negative or zero value
//     ippStsAlphaTypeErr     The alphaType is incorrect
//
//  Notes:          Value becomes 0 <= alphaA <= VAL_MAX
//                                0 <= alphaB <= VAL_MAX
*/

IPPAPI (IppStatus, ippiAlphaCompC_8u_C1IR,
                   ( const Ipp8u* pSrc, int srcStep,
                     Ipp8u alpha1,
                     Ipp8u* pSrcDst, int srcDstStep,
                     Ipp8u alpha2,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))
IPPAPI (IppStatus, ippiAlphaCompC_16u_C1IR,
                   ( const Ipp16u* pSrc, int srcStep,
                     Ipp16u alpha1,
                     Ipp16u* pSrcDst, int srcDstStep,
                     Ipp16u alpha2,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

IPPAPI (IppStatus, ippiAlphaCompC_16s_C1IR,
                   ( const Ipp16s* pSrc, int srcStep,
                     Ipp16s alpha1,
                     Ipp16s* pSrcDst, int srcDstStep,
                     Ipp16s alpha2,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))


IPPAPI (IppStatus, ippiAlphaCompC_32s_C1IR,
                   ( const Ipp32s* pSrc, int srcStep,
                     Ipp32s alpha1,
                     Ipp32s* pSrcDst, int srcDstStep,
                     Ipp32s alpha2,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

IPPAPI (IppStatus, ippiAlphaCompC_32u_C1IR,
                   ( const Ipp32u* pSrc, int srcStep,
                     Ipp32u alpha1,
                     Ipp32u* pSrcDst, int srcDstStep,
                     Ipp32u alpha2,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))

IPPAPI (IppStatus, ippiAlphaCompC_32f_C1IR,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f alpha1,
                     Ipp32f* pSrcDst, int srcDstStep,
                     Ipp32f alpha2,
                     IppiSize roiSize,
                     IppiAlphaType alphaType ))


/* /////////////////////////////////////////////////////////////////////////////
//                  Linear Transform Operations
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//                  Definitions for FFT Functions
///////////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////////
//                  FFT Context Functions
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFFTInit
//  Purpose:    Initializes the FFT context structure
//  Arguments:
//     orderX     Base-2 logarithm of the number of samples in FFT (width)
//     orderY     Base-2 logarithm of the number of samples in FFT (height)
//     flag       Flag to choose the results normalization factors
//     hint       Option to select the algorithmic implementation of the transform
//                function
//     pFFTSpec   Pointer to the FFT context structure
//     pMemInit   Pointer to the temporary work buffer
//  Return:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       One of the specified pointers is NULL
//     ippStsFftOrderErr      FFT order value is illegal
//     ippStsFFTFlagErr       Incorrect normalization flag value
*/

IPPAPI (IppStatus, ippiFFTInit_C_32fc,
                   ( int orderX, int orderY, int flag, IppHintAlgorithm hint,
                     IppiFFTSpec_C_32fc* pFFTSpec, Ipp8u* pMemInit ))
IPPAPI (IppStatus, ippiFFTInit_R_32f,
                   ( int orderX, int orderY, int flag, IppHintAlgorithm hint,
                     IppiFFTSpec_R_32f* pFFTSpec, Ipp8u* pMemInit ))


/* /////////////////////////////////////////////////////////////////////////////
//                  FFT Size
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFFTGetSize
//  Purpose:    Computes the size of the FFT context structure and the size
                of the required work buffer (in bytes)
//  Arguments:
//     orderX     Base-2 logarithm of the number of samples in FFT (width)
//     orderY     Base-2 logarithm of the number of samples in FFT (height)
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

IPPAPI (IppStatus, ippiFFTGetSize_C_32fc,
                   ( int orderX, int orderY, int flag, IppHintAlgorithm hint,
                     int* pSizeSpec, int* pSizeInit, int* pSizeBuf ))
IPPAPI (IppStatus, ippiFFTGetSize_R_32f,
                   ( int orderX, int orderY, int flag, IppHintAlgorithm hint,
                     int* pSizeSpec, int* pSizeInit, int* pSizeBuf ))

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

IPPAPI (IppStatus, ippiFFTFwd_CToC_32fc_C1R,
                   ( const Ipp32fc* pSrc, int srcStep,
                     Ipp32fc* pDst, int dstStep,
                     const IppiFFTSpec_C_32fc* pFFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiFFTInv_CToC_32fc_C1R,
                   ( const Ipp32fc* pSrc, int srcStep,
                     Ipp32fc* pDst, int dstStep,
                     const IppiFFTSpec_C_32fc* pFFTSpec,
                     Ipp8u* pBuffer ))

IPPAPI (IppStatus, ippiFFTFwd_RToPack_32f_C1R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep,
                     const IppiFFTSpec_R_32f* pFFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiFFTFwd_RToPack_32f_C3R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep,
                     const IppiFFTSpec_R_32f* pFFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiFFTFwd_RToPack_32f_C4R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep,
                     const IppiFFTSpec_R_32f* pFFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiFFTFwd_RToPack_32f_AC4R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep,
                     const IppiFFTSpec_R_32f* pFFTSpec,
                     Ipp8u* pBuffer ))

IPPAPI (IppStatus, ippiFFTInv_PackToR_32f_C1R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep,
                     const IppiFFTSpec_R_32f* pFFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiFFTInv_PackToR_32f_C3R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep,
                     const IppiFFTSpec_R_32f* pFFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiFFTInv_PackToR_32f_C4R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep,
                     const IppiFFTSpec_R_32f* pFFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiFFTInv_PackToR_32f_AC4R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep,
                     const IppiFFTSpec_R_32f* pFFTSpec,
                     Ipp8u* pBuffer ))

IPPAPI (IppStatus, ippiFFTFwd_CToC_32fc_C1IR,
                   ( Ipp32fc* pSrcDst, int srcDstStep,
                     const IppiFFTSpec_C_32fc* pFFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiFFTInv_CToC_32fc_C1IR,
                   ( Ipp32fc* pSrcDst, int srcDstStep,
                     const IppiFFTSpec_C_32fc* pFFTSpec,
                     Ipp8u* pBuffer ))

IPPAPI (IppStatus, ippiFFTFwd_RToPack_32f_C1IR,
                   ( Ipp32f* pSrcDst, int srcDstStep,
                     const IppiFFTSpec_R_32f* pFFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiFFTFwd_RToPack_32f_C3IR,
                   ( Ipp32f* pSrcDst, int srcDstStep,
                     const IppiFFTSpec_R_32f* pFFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiFFTFwd_RToPack_32f_C4IR,
                   ( Ipp32f* pSrcDst, int srcDstStep,
                     const IppiFFTSpec_R_32f* pFFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiFFTFwd_RToPack_32f_AC4IR,
                   ( Ipp32f* pSrcDst, int srcDstStep,
                     const IppiFFTSpec_R_32f* pFFTSpec,
                     Ipp8u* pBuffer ))

IPPAPI (IppStatus, ippiFFTInv_PackToR_32f_C1IR,
                   ( Ipp32f* pSrcDst, int srcDstStep,
                     const IppiFFTSpec_R_32f* pFFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiFFTInv_PackToR_32f_C3IR,
                   ( Ipp32f* pSrcDst, int srcDstStep,
                     const IppiFFTSpec_R_32f* pFFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiFFTInv_PackToR_32f_C4IR,
                   ( Ipp32f* pSrcDst, int srcDstStep,
                     const IppiFFTSpec_R_32f* pFFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiFFTInv_PackToR_32f_AC4IR,
                   ( Ipp32f* pSrcDst, int srcDstStep,
                     const IppiFFTSpec_R_32f* pFFTSpec,
                     Ipp8u* pBuffer ))

/* /////////////////////////////////////////////////////////////////////////////
//                  Definitions for DFT Functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//                  DFT Context Functions
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:         ippiDFTInit
//  Purpose:      Initializes the DFT context structure
//  Parameters:
//     roiSize    Size of the ROI
//     flag       Flag to choose the results normalization factors
//     hint       Option to select the algorithmic implementation of the transform
//                function
//     pDFTSpec   Double pointer to the DFT context structure
//     pMemInit   Pointer to initialization buffer
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       One of the specified pointers is NULL
//     ippStsFftOrderErr      Invalid roiSize
//     ippStsSizeErr          roiSize has a field with zero or negative value
//     ippStsFFTFlagErr       Incorrect normalization flag value
*/

IPPAPI (IppStatus, ippiDFTInit_C_32fc,
                   ( IppiSize roiSize, int flag, IppHintAlgorithm hint,
                   IppiDFTSpec_C_32fc* pDFTSpec, Ipp8u* pMemInit ))
IPPAPI (IppStatus, ippiDFTInit_R_32f,
                   ( IppiSize roiSize, int flag, IppHintAlgorithm hint,
                   IppiDFTSpec_R_32f* pDFTSpec, Ipp8u* pMemInit ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiDFTGetSize
//  Purpose:    Computes the size of the DFT context structure and the size
                of the required work buffer (in bytes)
//  Parameters:
//     roiSize    Size of the ROI
//     flag       Flag to choose the results normalization factors
//     hint       Option to select the algorithmic implementation of the transform
//                function
//     pSizeSpec  Pointer to the size value of DFT specification structure
//     pSizeInit  Pointer to the size value of the buffer for DFT initialization function
//     pSizeBuf   Pointer to the size value of the DFT external work buffer
//  Return:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       One of the specified pointers is NULL
//     ippStsFftOrderErr      Invalid roiSize
//     ippStsSizeErr          roiSize has a field with zero or negative value
//     ippStsFFTFlagErr       Incorrect normalization flag value
*/

IPPAPI (IppStatus, ippiDFTGetSize_C_32fc,
                   ( IppiSize roiSize, int flag, IppHintAlgorithm hint,
                   int* pSizeSpec, int* pSizeInit, int* pSizeBuf ))
IPPAPI (IppStatus, ippiDFTGetSize_R_32f,
                   ( IppiSize roiSize, int flag, IppHintAlgorithm hint,
                   int* pSizeSpec, int* pSizeInit, int* pSizeBuf ))


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

IPPAPI (IppStatus, ippiDFTFwd_CToC_32fc_C1R,
                   ( const Ipp32fc* pSrc, int srcStep,
                     Ipp32fc* pDst, int dstStep,
                     const IppiDFTSpec_C_32fc* pDFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiDFTInv_CToC_32fc_C1R,
                   ( const Ipp32fc* pSrc, int srcStep,
                     Ipp32fc* pDst, int dstStep,
                     const IppiDFTSpec_C_32fc* pDFTSpec,
                     Ipp8u* pBuffer ))

IPPAPI (IppStatus, ippiDFTFwd_RToPack_32f_C1R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep,
                     const IppiDFTSpec_R_32f* pDFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiDFTFwd_RToPack_32f_C3R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep,
                     const IppiDFTSpec_R_32f* pDFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiDFTFwd_RToPack_32f_C4R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep,
                     const IppiDFTSpec_R_32f* pDFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiDFTFwd_RToPack_32f_AC4R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep,
                     const IppiDFTSpec_R_32f* pDFTSpec,
                     Ipp8u* pBuffer ))

IPPAPI (IppStatus, ippiDFTInv_PackToR_32f_C1R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep,
                     const IppiDFTSpec_R_32f* pDFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiDFTInv_PackToR_32f_C3R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep,
                     const IppiDFTSpec_R_32f* pDFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiDFTInv_PackToR_32f_C4R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep,
                     const IppiDFTSpec_R_32f* pDFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiDFTInv_PackToR_32f_AC4R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep,
                     const IppiDFTSpec_R_32f* pDFTSpec,
                     Ipp8u* pBuffer ))

IPPAPI (IppStatus, ippiDFTFwd_CToC_32fc_C1IR,
                   ( Ipp32fc* pSrcDst, int srcDstStep,
                     const IppiDFTSpec_C_32fc* pDFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiDFTInv_CToC_32fc_C1IR,
                   ( Ipp32fc* pSrcDst, int srcDstStep,
                     const IppiDFTSpec_C_32fc* pDFTSpec,
                     Ipp8u* pBuffer ))

IPPAPI (IppStatus, ippiDFTFwd_RToPack_32f_C1IR,
                   ( Ipp32f* pSrcDst, int srcDstStep,
                     const IppiDFTSpec_R_32f* pDFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiDFTFwd_RToPack_32f_C3IR,
                   ( Ipp32f* pSrcDst, int srcDstStep,
                     const IppiDFTSpec_R_32f* pDFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiDFTFwd_RToPack_32f_C4IR,
                   ( Ipp32f* pSrcDst, int srcDstStep,
                     const IppiDFTSpec_R_32f* pDFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiDFTFwd_RToPack_32f_AC4IR,
                   ( Ipp32f* pSrcDst, int srcDstStep,
                     const IppiDFTSpec_R_32f* pDFTSpec,
                     Ipp8u* pBuffer ))

IPPAPI (IppStatus, ippiDFTInv_PackToR_32f_C1IR,
                   ( Ipp32f* pSrcDst, int srcDstStep,
                     const IppiDFTSpec_R_32f* pDFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiDFTInv_PackToR_32f_C3IR,
                   ( Ipp32f* pSrcDst, int srcDstStep,
                     const IppiDFTSpec_R_32f* pDFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiDFTInv_PackToR_32f_C4IR,
                   ( Ipp32f* pSrcDst, int srcDstStep,
                     const IppiDFTSpec_R_32f* pDFTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiDFTInv_PackToR_32f_AC4IR,
                   ( Ipp32f* pSrcDst, int srcDstStep,
                     const IppiDFTSpec_R_32f* pDFTSpec,
                     Ipp8u* pBuffer ))

/* /////////////////////////////////////////////////////////////////////////////
//                  Definitions for DCT Functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//                  DCT Context Functions
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiDCTFwdInit, ippiDCTInvInit
//  Purpose:    Initializes the forward/inverse DCT context structure
//  Parameters:
//     pDCTSpec   Pointer to the DCT context structure
//     roiSize    Size of the ROI
//     pMemInit   Pointer to the temporary work buffer
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       pDCTSpec == NULL
//     ippStsSizeErr          roiSize has a field with zero or negative value
*/

IPPAPI (IppStatus, ippiDCTFwdInit_32f,
                   ( IppiDCTFwdSpec_32f* pDCTSpec,
                   IppiSize roiSize, Ipp8u* pMemInit ))
IPPAPI (IppStatus, ippiDCTInvInit_32f,
                   ( IppiDCTInvSpec_32f* pDCTSpec,
                   IppiSize roiSize, Ipp8u* pMemInit ))

/* /////////////////////////////////////////////////////////////////////////////
//                  DCT Buffer Size
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiDCTFwdGetSize, ippiDCTInvGetSize
//  Purpose:    Computes the size of the forward/inverse DCT context structure and the size
//              of the required work buffer (in bytes)
//  Parameters:
//     roiSize    Size of the ROI
//     pSizeSpec  Pointer to the size value of DCT context structure
//     pSizeInit  Pointer to the size value of the buffer for DCT initialization function
//     pSizeBuf   Pointer to the size value of the DCT external work buffer
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       One of the specified pointers is NULL
//     ippStsSizeErr          roiSize has a field with zero or negative value
*/

IPPAPI (IppStatus, ippiDCTFwdGetSize_32f,
                   ( IppiSize roiSize,
                   int* pSizeSpec, int* pSizeInit, int* pSizeBuf ))
IPPAPI (IppStatus, ippiDCTInvGetSize_32f,
                   ( IppiSize roiSize,
                   int* pSizeSpec, int* pSizeInit, int* pSizeBuf ))

/* /////////////////////////////////////////////////////////////////////////////
//                  DCT Transforms
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiDCTFwd, ippiDCTInv
//  Purpose:    Performs forward or inverse DCT of an image
//  Parameters:
//     pDCTSpec   Pointer to the DCT context structure
//     pSrc       Pointer to the source image
//     srcStep    Step through the source image
//     pDst       Pointer to the destination image
//     dstStep    Step through the destination image
//     pBuffer    Pointer to the work buffer
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       One of the specified pointers with the exception of
                              pBuffer is NULL
//     ippStsStepErr          srcStep or dstStep value is zero or negative
//     ippStsContextMatchErr  Invalid context structure
//     ippStsMemAllocErr      Memory allocation error
*/

IPPAPI (IppStatus, ippiDCTFwd_32f_C1R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep,
                     const IppiDCTFwdSpec_32f* pDCTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiDCTFwd_32f_C3R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep,
                     const IppiDCTFwdSpec_32f* pDCTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiDCTFwd_32f_C4R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep,
                     const IppiDCTFwdSpec_32f* pDCTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiDCTFwd_32f_AC4R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep,
                     const IppiDCTFwdSpec_32f* pDCTSpec,
                     Ipp8u* pBuffer ))

IPPAPI (IppStatus, ippiDCTInv_32f_C1R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep,
                     const IppiDCTInvSpec_32f* pDCTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiDCTInv_32f_C3R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep,
                     const IppiDCTInvSpec_32f* pDCTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiDCTInv_32f_C4R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep,
                     const IppiDCTInvSpec_32f* pDCTSpec,
                     Ipp8u* pBuffer ))
IPPAPI (IppStatus, ippiDCTInv_32f_AC4R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep,
                     const IppiDCTInvSpec_32f* pDCTSpec,
                     Ipp8u* pBuffer ))

/* /////////////////////////////////////////////////////////////////////////////
//                  8x8 DCT Transforms
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiDCT8x8Fwd_16s_C1, ippiDCT8x8Fwd_16s_C1I
//             ippiDCT8x8Inv_16s_C1, ippiDCT8x8Inv_16s_C1I
//             ippiDCT8x8Fwd_16s_C1R
//             ippiDCT8x8Inv_16s_C1R
//  Purpose:   Performs forward or inverse DCT in the 8x8 buffer for 16s data
//
//  Parameters:
//     pSrc       Pointer to the source buffer
//     pDst       Pointer to the destination buffer
//     pSrcDst    Pointer to the source and destination buffer (in-place operations)
//     srcStep    Step through the source image (operations with ROI)
//     dstStep    Step through the destination image (operations with ROI)
//  Returns:
//     ippStsNoErr         No errors
//     ippStsNullPtrErr    One of the specified pointers is NULL
//     ippStsStepErr       srcStep or dstStep value is zero or negative
//  Notes:
//     Source data for inverse DCT functions must be the result of the forward DCT
//     of data from the range [-256,255]
*/

IPPAPI (IppStatus, ippiDCT8x8Fwd_16s_C1,  ( const Ipp16s* pSrc, Ipp16s* pDst ))
IPPAPI (IppStatus, ippiDCT8x8Inv_16s_C1,  ( const Ipp16s* pSrc, Ipp16s* pDst ))

IPPAPI (IppStatus, ippiDCT8x8Fwd_16s_C1I, ( Ipp16s* pSrcDst ))
IPPAPI (IppStatus, ippiDCT8x8Inv_16s_C1I, ( Ipp16s* pSrcDst ))

IPPAPI (IppStatus, ippiDCT8x8Fwd_16s_C1R,
                           ( const Ipp16s* pSrc, int srcStep, Ipp16s* pDst ))
IPPAPI (IppStatus, ippiDCT8x8Inv_16s_C1R,
                           ( const Ipp16s* pSrc, Ipp16s* pDst, int dstStep ))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiDCT8x8Inv_2x2_16s_C1, ippiDCT8x8Inv_2x2_16s_C1I
//             ippiDCT8x8Inv_4x4_16s_C1, ippiDCT8x8Inv_4x4_16s_C1I
//  Purpose:   Performs inverse DCT of nonzero elements in the top left quadrant
//             of size 2x2 or 4x4 in the 8x8 buffer
//  Parameters:
//     pSrc       Pointer to the source buffer
//     pDst       Pointer to the destination buffer
//     pSrcDst    Pointer to the source/destination buffer (in-place operations)
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       One of the specified pointers is NULL
//  Notes:
//     Source data for these functions must be the result of the forward DCT
//     of data from the range [-256,255]
*/

IPPAPI (IppStatus, ippiDCT8x8Inv_2x2_16s_C1,  ( const Ipp16s* pSrc, Ipp16s* pDst ))
IPPAPI (IppStatus, ippiDCT8x8Inv_4x4_16s_C1,  ( const Ipp16s* pSrc, Ipp16s* pDst ))

IPPAPI (IppStatus, ippiDCT8x8Inv_2x2_16s_C1I, ( Ipp16s* pSrcDst ))
IPPAPI (IppStatus, ippiDCT8x8Inv_4x4_16s_C1I, ( Ipp16s* pSrcDst ))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiDCT8x8To2x2Inv_16s_C1, ippiDCT8x8To2x2Inv_16s_C1I
//             ippiDCT8x8To4x4Inv_16s_C1, ippiDCT8x8To4x4Inv_16s_C1I
//  Purpose:   Inverse Discrete Cosine Transform 8x8 for 16s data and
//             downsampling of the result from 8x8 to 2x2 or 4x4 by averaging
//  Arguments:
//     pSrc       Pointer to the source buffer
//     pDst       Pointer to the destination buffer
//     pSrcDst    Pointer to the source/destination buffer (in-place operations)
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       One of the specified pointers is NULL
//  Notes:
//     Source data for these functions must be the result of the forward DCT
//     of data from the range [-256,255]
*/

IPPAPI (IppStatus, ippiDCT8x8To2x2Inv_16s_C1,  ( const Ipp16s* pSrc, Ipp16s* pDst ))
IPPAPI (IppStatus, ippiDCT8x8To4x4Inv_16s_C1,  ( const Ipp16s* pSrc, Ipp16s* pDst ))

IPPAPI (IppStatus, ippiDCT8x8To2x2Inv_16s_C1I, ( Ipp16s* pSrcDst ))
IPPAPI (IppStatus, ippiDCT8x8To4x4Inv_16s_C1I, ( Ipp16s* pSrcDst ))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiDCT8x8Inv_A10_16s_C1, ippiDCT8x8Inv_A10_16s_C1I
//  Purpose:   Performs inverse DCT in the 8x8 buffer for 10 bits 16s data
//
//  Parameters:
//     pSrc       Pointer to the source buffer
//     pDst       Pointer to the destination buffer
//  Returns:
//     ippStsNoErr         No errors
//     ippStsNullPtrErr    One of the specified pointers is NULL
//  Notes:
//     Source data for these functions must be the result of the forward DCT
//     of data from the range [-512,511]
*/

IPPAPI (IppStatus, ippiDCT8x8Inv_A10_16s_C1,  ( const Ipp16s* pSrc, Ipp16s* pDst ))
IPPAPI (IppStatus, ippiDCT8x8Inv_A10_16s_C1I, ( Ipp16s* pSrcDst ))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiDCT8x8Fwd_8u16s_C1R
//             ippiDCT8x8Inv_16s8u_C1R
//  Purpose:   Performs forward and inverse DCT in 8x8 buffer
//             for 16s data with conversion from/to 8u
//  Parameters:
//     pSrc      Pointer to the source buffer
//     pDst      Pointer to the destination buffer
//     srcStep   Step through the source image
//     dstStep   Step through the destination image
//  Returns:
//     ippStsNoErr        No errors
//     ippStsNullPtrErr   One of the specified pointers is NULL
//     ippStsStepErr      srcStep or dstStep value is zero or negative
*/

IPPAPI (IppStatus, ippiDCT8x8Fwd_8u16s_C1R,
                   ( const Ipp8u* pSrc, int srcStep, Ipp16s* pDst ))

IPPAPI (IppStatus, ippiDCT8x8Inv_16s8u_C1R,
                   ( const Ipp16s* pSrc, Ipp8u* pDst, int dstStep ))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiDCT8x8FwdLS_8u16s_C1R
//  Purpose:   Performs forward DCT in 8x8 buffer for 16s data
//             with conversion from 8u and level shift
//  Parameters:
//     pSrc      Pointer to start of source buffer
//     pDst      Pointer to start of destination buffer
//     srcStep   Step the source buffer
//     addVal    Constant value adding before DCT (level shift)
//  Returns:
//     ippStsNoErr         No errors
//     ippStsNullPtrErr    One of the specified pointers is NULL
//     ippStsStepErr       srcStep value is zero or negative
*/

IPPAPI (IppStatus, ippiDCT8x8FwdLS_8u16s_C1R,
                   ( const Ipp8u* pSrc, int srcStep, Ipp16s* pDst,
                     Ipp16s addVal ))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiDCT8x8InvLSClip_16s8u_C1R
//  Purpose:   Performs inverse DCT in 8x8 buffer for 16s data
//             with level shift, clipping and conversion to 8u
//  Parameters:
//     pSrc      Pointer to the source buffer
//     pDst      Pointer to the destination buffer
//     dstStep   Step through the destination image
//     addVal    Constant value adding after DCT (level shift)
//     clipDown  Constant value for clipping (MIN)
//     clipUp    Constant value for clipping (MAX)
//  Returns:
//     ippStsNoErr           No errors
//     ippStsNullPtrErr      One of the pointers is NULL
//     ippStsStepErr         dstStep value is zero or negative
*/

IPPAPI (IppStatus, ippiDCT8x8InvLSClip_16s8u_C1R,
                   ( const Ipp16s* pSrc, Ipp8u* pDst, int dstStep,
                     Ipp16s addVal, Ipp8u clipDown, Ipp8u clipUp ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiDCT8x8Fwd_32f_C1, ippiDCT8x8Fwd_32f_C1I
//             ippiDCT8x8Inv_32f_C1, ippiDCT8x8Inv_32f_C1I
//  Purpose:   Performs forward or inverse DCT in the 8x8 buffer for 32f data
//
//  Parameters:
//     pSrc       Pointer to the source buffer
//     pDst       Pointer to the destination buffer
//     pSrcDst    Pointer to the source and destination buffer (in-place operations)
//  Returns:
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       One of the specified pointers is NULL
*/

IPPAPI (IppStatus, ippiDCT8x8Fwd_32f_C1,  ( const Ipp32f* pSrc, Ipp32f* pDst ))
IPPAPI (IppStatus, ippiDCT8x8Inv_32f_C1,  ( const Ipp32f* pSrc, Ipp32f* pDst ))

IPPAPI (IppStatus, ippiDCT8x8Fwd_32f_C1I, ( Ipp32f* pSrcDst ))
IPPAPI (IppStatus, ippiDCT8x8Inv_32f_C1I, ( Ipp32f* pSrcDst ))




/* /////////////////////////////////////////////////////////////////////////////
//          Wavelet Transform Functions for User Filter Banks
///////////////////////////////////////////////////////////////////////////// */

/* //////////////////////////////////////////////////////////////////////
// Name:        ippiWTFwdGetSize_32f
//
// Purpose:     Get sizes, in bytes, of the ippiWTFwd spec structure and the work buffer.
//
// Parameters:
//    numChannels - Number of image channels. Possible values are 1 and 3.
//    lenLow      - Length of the lowpass filter.
//    anchorLow   - Anchor position of the lowpass filter.
//    lenHigh     - Length of the highpass filter.
//    anchorHigh  - Anchor position of the highpass filter.
//    pSpecSize   - Pointer to the size of the ippiWTFwd spec structure (in bytes).
//    pBufSize    - Pointer to the size of the work buffer (in bytes).
//
// Returns:
//    ippStsNoErr           - Ok.
//    ippStsNullPtrErr      - Error when any of the specified pointers is NULL.
//    ippStsNumChannelsErr  - Error when the numChannels value differs from 1 or 3.
//    ippStsSizeErr         - Error when lenLow or lenHigh is less than 2.
//    ippStsAnchorErr       - Error when anchorLow or anchorHigh is less than zero.
*/
IPPAPI (IppStatus, ippiWTFwdGetSize_32f, ( int numChannels, int lenLow, int anchorLow, int lenHigh, int anchorHigh, int* pSpecSize, int* pBufSize ))

/* //////////////////////////////////////////////////////////////////////
// Name:       ippiWTFwdInit_
//
// Purpose:    Initialize forward wavelet transform spec structure.
//
// Parameters:
//   pSpec        - Pointer to pointer to allocated ippiWTFwd spec structure.
//   pTapsLow     - Pointer to lowpass filter taps.
//   lenLow       - Length of lowpass filter.
//   anchorLow    - Anchor position of lowpass filter.
//   pTapsHigh    - Pointer to highpass filter taps.
//   lenHigh      - Length of highpass filter.
//   anchorHigh   - Anchor position of highpass filter.
//
// Returns:
//    ippStsNoErr           - Ok.
//    ippStsNullPtrErr      - Error when any of the specified pointers is NULL.
//    ippStsNumChannelsErr  - Error when the numChannels value differs from 1 or 3.
//    ippStsSizeErr         - Error when lenLow or lenHigh is less than 2.
//    ippStsAnchorErr       - Error when anchorLow or anchorHigh is less than zero.
*/
IPPAPI (IppStatus, ippiWTFwdInit_32f_C1R, (IppiWTFwdSpec_32f_C1R* pSpec, const Ipp32f* pTapsLow, int lenLow, int anchorLow, const Ipp32f* pTapsHigh, int lenHigh, int anchorHigh))
IPPAPI (IppStatus, ippiWTFwdInit_32f_C3R, (IppiWTFwdSpec_32f_C3R* pSpec, const Ipp32f* pTapsLow, int lenLow, int anchorLow, const Ipp32f* pTapsHigh, int lenHigh, int anchorHigh))



/* //////////////////////////////////////////////////////////////////////
// Name:        ippiWTFwd_32f_C1R
//              ippiWTFwd_32f_C3R
//
// Purpose:     Performs wavelet decomposition of an image.
//
// Parameters:
//   pSrc         Pointer to source image ROI;
//   srcStep      Step in bytes through the source image;
//   pApproxDst   Pointer to destination "approximation" image ROI;
//   approxStep   Step in bytes through the destination approximation image;
//   pDetailXDst  Pointer to the destination "horizontal details" image ROI;
//   detailXStep  Step in bytes through the destination horizontal detail image;
//   pDetailYDst  Pointer to the destination "vertical details" image ROI;
//   detailYStep  Step in bytes through the destination "vertical details" image;
//   pDetailXYDst Pointer to the destination "diagonal details" image ROI;
//   detailXYStep Step in bytes through the destination "diagonal details" image;
//   dstRoiSize   ROI size for all destination images.
//   pSpec        Pointer to the context structure.
//
// Returns:
//   ippStsNoErr            OK;
//   ippStsNullPtrErr       One of pointers is NULL;
//   ippStsSizeErr          dstRoiSize has a field with zero or negative value;
//   ippStsContextMatchErr  Invalid context structure.
//
// Notes:
//   No any fixed borders extension (wrap, symm.) will be applied!
//   Source image must have valid and accessible border data outside of ROI.
//
//   Only the same ROI sizes for destination images are supported.
//
//   Source ROI size should be calculated by the following rule:
//          srcRoiSize.width  = 2 * dstRoiSize.width;
//          srcRoiSize.height = 2 * dstRoiSize.height.
//
//   Conventional tokens for destination images have next meaning:
//    "Approximation"     - image obtained by vertical
//                              and horizontal lowpass filtering.
//    "Horizontal detail" - image obtained by vertical highpass
//                              and horizontal lowpass filtering.
//    "Vertical detail"   - image obtained by vertical lowpass
//                              and horizontal highpass filtering.
//    "Diagonal detail"   - image obtained by vertical
//                              and horizontal highpass filtering.
//   These tokens are used only for identification convenience.
//
//
*/
IPPAPI (IppStatus, ippiWTFwd_32f_C1R, (const Ipp32f* pSrc,  int srcStep, Ipp32f* pApproxDst,   int approxStep,
        Ipp32f* pDetailXDst,  int detailXStep, Ipp32f* pDetailYDst,  int detailYStep, Ipp32f* pDetailXYDst, int detailXYStep,
        IppiSize dstRoiSize, const IppiWTFwdSpec_32f_C1R* pSpec, Ipp8u* pBuffer))

IPPAPI (IppStatus, ippiWTFwd_32f_C3R, (const Ipp32f* pSrc,  int srcStep, Ipp32f* pApproxDst,   int approxStep,
        Ipp32f* pDetailXDst,  int detailXStep, Ipp32f* pDetailYDst,  int detailYStep, Ipp32f* pDetailXYDst, int detailXYStep,
        IppiSize dstRoiSize, const IppiWTFwdSpec_32f_C3R* pSpec, Ipp8u* pBuffer))


/* //////////////////////////////////////////////////////////////////////
// Name:        ippiWTInvGetSize_32f
//
// Purpose:     Get sizes, in bytes, of the WTInv spec structure and the work buffer.
//
// Parameters:
//    numChannels - Number of image channels. Possible values are 1 and 3.
//    lenLow      - Length of the lowpass filter.
//    anchorLow   - Anchor position of the lowpass filter.
//    lenHigh     - Length of the highpass filter.
//    anchorHigh  - Anchor position of the highpass filter.
//    pSpecSize   - Pointer to the size of the ippiWTInv spec structure (in bytes).
//    pBufSize    - Pointer to the size of the work buffer (in bytes).
//
// Returns:
//    ippStsNoErr           - Ok.
//    ippStsNullPtrErr      - Error when any of the specified pointers is NULL.
//    ippStsNumChannelsErr  - Error when the numChannels value differs from 1 or 3.
//    ippStsSizeErr         - Error when lenLow or lenHigh is less than 2.
//    ippStsAnchorErr       - Error when anchorLow or anchorHigh is less than zero.
*/
IPPAPI (IppStatus, ippiWTInvGetSize_32f, ( int numChannels, int lenLow, int anchorLow, int lenHigh, int anchorHigh, int* pSpecSize, int* pBufSize ))


/* //////////////////////////////////////////////////////////////////////
// Name:       ippiWTInvInit_
//
// Purpose:    Initialize inverse wavelet transform spec structure.
//
// Parameters:
//   pSpec        - Pointer to pointer to allocated ippiWTInv spec structure.
//   pTapsLow     - Pointer to lowpass filter taps.
//   lenLow       - Length of lowpass filter.
//   anchorLow    - Anchor position of lowpass filter.
//   pTapsHigh    - Pointer to highpass filter taps.
//   lenHigh      - Length of highpass filter.
//   anchorHigh   - Anchor position of highpass filter.
//
// Returns:
//    ippStsNoErr           - Ok.
//    ippStsNullPtrErr      - Error when any of the specified pointers is NULL.
//    ippStsNumChannelsErr  - Error when the numChannels value differs from 1 or 3.
//    ippStsSizeErr         - Error when lenLow or lenHigh is less than 2.
//    ippStsAnchorErr       - Error when anchorLow or anchorHigh is less than zero.
*/
IPPAPI (IppStatus, ippiWTInvInit_32f_C1R, (IppiWTInvSpec_32f_C1R* pSpec, const Ipp32f* pTapsLow, int lenLow, int anchorLow, const Ipp32f* pTapsHigh, int lenHigh, int anchorHigh))
IPPAPI (IppStatus, ippiWTInvInit_32f_C3R, (IppiWTInvSpec_32f_C3R* pSpec, const Ipp32f* pTapsLow, int lenLow, int anchorLow, const Ipp32f* pTapsHigh, int lenHigh, int anchorHigh))




/* //////////////////////////////////////////////////////////////////////
// Name:        ippiWTInv_32f_C1R
//              ippiWTInv_32f_C3R
//
// Purpose:     Performs wavelet reconstruction of an image.
//
// Parameters:
//   pApproxSrc    Pointer to the source "approximation" image ROI;
//   approxStep    Step in bytes through the source approximation image;
//   pDetailXSrc   Pointer to the source "horizontal details" image ROI;
//   detailXStep   Step in bytes through the source horizontal detail image;
//   pDetailYSrc   Pointer to the source "vertical details" image ROI;
//   detailYStep   Step in bytes through the source "vertical details" image;
//   pDetailXYSrc  Pointer to the source "diagonal details" image ROI;
//   detailXYStep  Step in bytes through the source "diagonal details" image;
//   srcRoiSize    ROI size for all source images.
//   pDst          Pointer to the destination image ROI;
//   dstStep       Step in bytes through the destination image;
//   pSpec         Pointer to the context structure;
//   pBuffer       Pointer to the allocated buffer for intermediate operations.
//
// Returns:
//   ippStsNoErr            OK;
//   ippStsNullPtrErr       One of the pointers is NULL;
//   ippStsSizeErr          srcRoiSize has a field with zero or negative value;
//   ippStsContextMatchErr  Invalid context structure.
//
// Notes:
//   No any fixed borders extension (wrap, symm.) will be applied! Source
//    images must have valid and accessible border data outside of ROI.
//
//   Only the same ROI size for source images supported. Destination ROI size
//     should be calculated by next rule:
//          dstRoiSize.width  = 2 * srcRoiSize.width;
//          dstRoiSize.height = 2 * srcRoiSize.height.
//
//
//   Monikers for the source images are in accordance with decomposition destination.
//
//
*/
IPPAPI (IppStatus, ippiWTInv_32f_C1R, ( const Ipp32f* pApproxSrc,   int approxStep, const Ipp32f* pDetailXSrc,  int detailXStep,
        const Ipp32f* pDetailYSrc,  int detailYStep, const Ipp32f* pDetailXYSrc, int detailXYStep,
        IppiSize srcRoiSize, Ipp32f* pDst,  int dstStep, const IppiWTInvSpec_32f_C1R* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWTInv_32f_C3R, (const Ipp32f* pApproxSrc,   int approxStep, const Ipp32f* pDetailXSrc,  int detailXStep,
        const Ipp32f* pDetailYSrc,  int detailYStep, const Ipp32f* pDetailXYSrc, int detailXYStep,
        IppiSize srcRoiSize, Ipp32f* pDst,  int dstStep, const IppiWTInvSpec_32f_C3R* pSpec, Ipp8u* pBuffer))




/* /////////////////////////////////////////////////////////////////////////////
//                   Image resampling functions
///////////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiDecimateFilterRow_8u_C1R,
//                      ippiDecimateFilterColumn_8u_C1R
//  Purpose:            Decimate the image with specified filters
//                      in horizontal or vertical directions
//  Parameters:
//    pSrc              source image data
//    srcStep           step in source image
//    srcRoiSize        region of interest of source image
//    pDst              resultant image data
//    dstStep           step in destination image
//    fraction          they specify fractions of decimating
//  Returns:
//    ippStsNoErr       no errors
//    ippStsNullPtrErr  one of the pointers is NULL
//    ippStsStepErr     one of the step values is zero or negative
//    ippStsSizeErr     srcRoiSize has a field with negative or zero value
//    ippStsDecimateFractionErr (fraction != ippPolyphase_1_2) &&
//                              (fraction != ippPolyphase_3_5) &&
//                              (fraction != ippPolyphase_2_3) &&
//                              (fraction != ippPolyphase_7_10) &&
//                              (fraction != ippPolyphase_3_4)
*/

IPPAPI(IppStatus, ippiDecimateFilterRow_8u_C1R, (
    const Ipp8u* pSrc, int srcStep, IppiSize srcRoiSize,
    Ipp8u* pDst, int dstStep, IppiFraction fraction))
IPPAPI(IppStatus, ippiDecimateFilterColumn_8u_C1R, (
    const Ipp8u* pSrc, int srcStep, IppiSize srcRoiSize,
    Ipp8u* pDst, int dstStep, IppiFraction fraction))


/* /////////////////////////////////////////////////////////////////////////////
//                   Geometric Transform functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//
//  Name:        ippiMirror
//
//  Purpose:     Mirrors an image about a horizontal
//               or vertical axis, or both
//
//  Context:
//
//  Returns:     IppStatus
//    ippStsNoErr         No errors
//    ippStsNullPtrErr    pSrc == NULL, or pDst == NULL
//    ippStsSizeErr,      roiSize has a field with zero or negative value
//    ippStsMirrorFlipErr (flip != ippAxsHorizontal) &&
//                        (flip != ippAxsVertical) &&
//                        (flip != ippAxsBoth)
//
//  Parameters:
//    pSrc       Pointer to the source image
//    srcStep    Step through the source image
//    pDst       Pointer to the destination image
//    dstStep    Step through the destination image
//    pSrcDst    Pointer to the source/destination image (in-place flavors)
//    srcDstStep Step through the source/destination image (in-place flavors)
//    roiSize    Size of the ROI
//    flip       Specifies the axis to mirror the image about:
//                 ippAxsHorizontal     horizontal axis,
//                 ippAxsVertical       vertical axis,
//                 ippAxsBoth           both horizontal and vertical axes
//
//  Notes:
//
*/

IPPAPI(IppStatus, ippiMirror_8u_C1R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
                                      IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_8u_C3R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
                                      IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_8u_AC4R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
                                       IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_8u_C4R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
                                                       IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_8u_C1IR, (Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_8u_C3IR, (Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_8u_AC4IR, (Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_8u_C4IR, (Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize, IppiAxis flip))

IPPAPI(IppStatus, ippiMirror_16u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
                                       IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_16u_C3R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
                                       IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_16u_AC4R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
                                        IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_16u_C4R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
                                                        IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_16u_C1IR, (Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_16u_C3IR, (Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_16u_AC4IR, (Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize, IppiAxis flip))
IPPAPI (IppStatus, ippiMirror_16u_C4IR, (Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize, IppiAxis flip))

IPPAPI(IppStatus, ippiMirror_32s_C1R, (const Ipp32s* pSrc, int srcStep, Ipp32s* pDst, int dstStep,
                                       IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_32s_C3R, (const Ipp32s* pSrc, int srcStep, Ipp32s* pDst, int dstStep,
                                       IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_32s_AC4R, (const Ipp32s* pSrc, int srcStep, Ipp32s* pDst, int dstStep,
                                        IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_32s_C4R, (const Ipp32s* pSrc, int srcStep, Ipp32s* pDst, int dstStep,
                                                        IppiSize roiSize, IppiAxis flip ) )

IPPAPI(IppStatus, ippiMirror_32s_C1IR, (Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_32s_C3IR, (Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_32s_AC4IR, (Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_32s_C4IR, (Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize, IppiAxis flip))

IPPAPI(IppStatus, ippiMirror_16s_C1R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
                                       IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_16s_C3R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
                                       IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_16s_AC4R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
                                        IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_16s_C4R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
                                                        IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_16s_C1IR, (Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_16s_C3IR, (Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_16s_AC4IR, (Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize, IppiAxis flip))
IPPAPI (IppStatus, ippiMirror_16s_C4IR, (Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize, IppiAxis flip))

IPPAPI(IppStatus, ippiMirror_32f_C1R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
                                       IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_32f_C3R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
                                       IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_32f_AC4R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
                                        IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_32f_C4R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
                                                        IppiSize roiSize, IppiAxis flip ) )
IPPAPI(IppStatus, ippiMirror_32f_C1IR, (Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_32f_C3IR, (Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_32f_AC4IR, (Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize, IppiAxis flip))
IPPAPI(IppStatus, ippiMirror_32f_C4IR, (Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize, IppiAxis flip))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiRemap
//  Purpose:            Transforms the source image by remapping its pixels
//                          dst[i,j] = src[yMap[i,j], xMap[i,j]]
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

IPPAPI(IppStatus, ippiRemap_8u_C1R, (const Ipp8u* pSrc, IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp32f* pxMap, int xMapStep,
    const Ipp32f* pyMap, int yMapStep, Ipp8u* pDst, int dstStep,
    IppiSize dstRoiSize, int interpolation))
IPPAPI(IppStatus, ippiRemap_8u_C3R, (const Ipp8u* pSrc, IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp32f* pxMap, int xMapStep,
    const Ipp32f* pyMap, int yMapStep, Ipp8u* pDst, int dstStep,
    IppiSize dstRoiSize, int interpolation))
IPPAPI(IppStatus, ippiRemap_8u_C4R, (const Ipp8u* pSrc, IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp32f* pxMap, int xMapStep,
    const Ipp32f* pyMap, int yMapStep, Ipp8u* pDst, int dstStep,
    IppiSize dstRoiSize, int interpolation))
IPPAPI(IppStatus, ippiRemap_8u_AC4R, (const Ipp8u* pSrc, IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp32f* pxMap, int xMapStep,
    const Ipp32f* pyMap, int yMapStep, Ipp8u* pDst, int dstStep,
    IppiSize dstRoiSize, int interpolation))
IPPAPI(IppStatus, ippiRemap_16u_C1R, (const Ipp16u* pSrc, IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp32f* pxMap, int xMapStep,
    const Ipp32f* pyMap, int yMapStep, Ipp16u* pDst, int dstStep,
    IppiSize dstRoiSize, int interpolation))
IPPAPI(IppStatus, ippiRemap_16u_C3R, (const Ipp16u* pSrc, IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp32f* pxMap, int xMapStep,
    const Ipp32f* pyMap, int yMapStep, Ipp16u* pDst, int dstStep,
    IppiSize dstRoiSize, int interpolation))
IPPAPI(IppStatus, ippiRemap_16u_C4R, (const Ipp16u* pSrc, IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp32f* pxMap, int xMapStep,
    const Ipp32f* pyMap, int yMapStep, Ipp16u* pDst, int dstStep,
    IppiSize dstRoiSize, int interpolation))
IPPAPI(IppStatus, ippiRemap_16u_AC4R, (const Ipp16u* pSrc, IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp32f* pxMap, int xMapStep,
    const Ipp32f* pyMap, int yMapStep, Ipp16u* pDst, int dstStep,
    IppiSize dstRoiSize, int interpolation))
IPPAPI(IppStatus, ippiRemap_16s_C1R, (const Ipp16s* pSrc, IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp32f* pxMap, int xMapStep,
    const Ipp32f* pyMap, int yMapStep, Ipp16s* pDst, int dstStep,
    IppiSize dstRoiSize, int interpolation))
IPPAPI(IppStatus, ippiRemap_16s_C3R, (const Ipp16s* pSrc, IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp32f* pxMap, int xMapStep,
    const Ipp32f* pyMap, int yMapStep, Ipp16s* pDst, int dstStep,
    IppiSize dstRoiSize, int interpolation))
IPPAPI(IppStatus, ippiRemap_16s_C4R, (const Ipp16s* pSrc, IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp32f* pxMap, int xMapStep,
    const Ipp32f* pyMap, int yMapStep, Ipp16s* pDst, int dstStep,
    IppiSize dstRoiSize, int interpolation))
IPPAPI(IppStatus, ippiRemap_16s_AC4R, (const Ipp16s* pSrc, IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp32f* pxMap, int xMapStep,
    const Ipp32f* pyMap, int yMapStep, Ipp16s* pDst, int dstStep,
    IppiSize dstRoiSize, int interpolation))
IPPAPI(IppStatus, ippiRemap_32f_C1R, (const Ipp32f* pSrc, IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp32f* pxMap, int xMapStep,
    const Ipp32f* pyMap, int yMapStep, Ipp32f* pDst, int dstStep,
    IppiSize dstRoiSize, int interpolation))
IPPAPI(IppStatus, ippiRemap_32f_C3R, (const Ipp32f* pSrc, IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp32f* pxMap, int xMapStep,
    const Ipp32f* pyMap, int yMapStep, Ipp32f* pDst, int dstStep,
    IppiSize dstRoiSize, int interpolation))
IPPAPI(IppStatus, ippiRemap_32f_C4R, (const Ipp32f* pSrc, IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp32f* pxMap, int xMapStep,
    const Ipp32f* pyMap, int yMapStep, Ipp32f* pDst, int dstStep,
    IppiSize dstRoiSize, int interpolation))
IPPAPI(IppStatus, ippiRemap_32f_AC4R, (const Ipp32f* pSrc, IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp32f* pxMap, int xMapStep,
    const Ipp32f* pyMap, int yMapStep, Ipp32f* pDst, int dstStep,
    IppiSize dstRoiSize, int interpolation))
IPPAPI(IppStatus, ippiRemap_64f_C1R, (const Ipp64f* pSrc, IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp64f* pxMap, int xMapStep,
    const Ipp64f* pyMap, int yMapStep, Ipp64f* pDst, int dstStep,
    IppiSize dstRoiSize, int interpolation))
IPPAPI(IppStatus, ippiRemap_64f_C3R, (const Ipp64f* pSrc, IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp64f* pxMap, int xMapStep,
    const Ipp64f* pyMap, int yMapStep, Ipp64f* pDst, int dstStep,
    IppiSize dstRoiSize, int interpolation))
IPPAPI(IppStatus, ippiRemap_64f_C4R, (const Ipp64f* pSrc, IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp64f* pxMap, int xMapStep,
    const Ipp64f* pyMap, int yMapStep, Ipp64f* pDst, int dstStep,
    IppiSize dstRoiSize, int interpolation))
IPPAPI(IppStatus, ippiRemap_64f_AC4R, (const Ipp64f* pSrc, IppiSize srcSize,
    int srcStep, IppiRect srcROI, const Ipp64f* pxMap, int xMapStep,
    const Ipp64f* pyMap, int yMapStep, Ipp64f* pDst, int dstStep,
    IppiSize dstRoiSize, int interpolation))


/* /////////////////////////////////////////////////////////////////////////////
//                     Resize functions
// ////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiResizeSetMode
//  Purpose:    Set roundMode (Fast or Accurate) for Resize functions
//
//  Parameters:
//    hint        ippAlgHintFast, ippAlgHintAccurate: fast or accurate rounding.
//                ippAlgHintFast (default mode) means that performance takes precedence over accuracy and some output
//                pixels can differ on +-1 from exact result
//                ippAlgHintAccurate means that all output pixels are exact and accuracy takes precedence over performance
//    pSpec       Pointer to the initialized ResizeSpec

//  Returns:
//    ippStsNoErr                    no errors
//    ippStsNullPtrErr               one of the pointers is NULL
//    ippStsAccurateModeNotSupported the accurate mode not supported for some data types. The result of rounding can be inexact.
*/

IPPAPI( IppStatus, ippiResizeSetMode, (IppHintAlgorithm hint, IppiResizeSpec* pSpec))

/* /////////////////////////////////////////////////////////////////////////////
//
//  Name:               ippiResizeFilterGetSize_8u_C1R
//  Purpose:            Computes pState size for resize filter (in bytes)
//  Parameters:
//    srcRoiSize        region of interest of source image
//    dstRoiSize        region of interest of destination image
//    filter            type of resize filter
//    pSize             pointer to State size
//  Returns:
//    ippStsNoErr       no errors
//    ippStsSizeErr     width or height of images is less or equal to zero
//    ippStsNotSupportedModeErr filter type is not supported
//    ippStsNullPtrErr  pointer to buffer size is NULL
*/

IPPAPI(IppStatus, ippiResizeFilterGetSize_8u_C1R, (
    IppiSize srcRoiSize, IppiSize dstRoiSize, IppiResizeFilterType filter, Ipp32u *pSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeFilterInit_8u_C1R
//  Purpose:            Initialization of State for resize filter
//  Parameters:
//    pState            pointer to State
//    srcRoiSize        region of interest of source image
//    dstRoiSize        region of interest of destination image
//    filter            type of resize filter
//  Returns:
//    ippStsNoErr       no errors
//    ippStsNullPtrErr  pointer to Spec is NULL
//    ippStsSizeErr     width or height of images is less or equal to zero
//    ippStsNotSupportedModeErr filter type is not supported
*/

IPPAPI(IppStatus, ippiResizeFilterInit_8u_C1R, (
    IppiResizeFilterState *pState, IppiSize srcRoiSize, IppiSize dstRoiSize, IppiResizeFilterType filter))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeFilter_8u_C1R
//  Purpose:            Performs RESIZE transform using generic filter
//  Parameters:
//    pSrc              source image data
//    srcStep           step in source image
//    srcRoiSize        region of interest of source image
//    pDst              resultant image data
//    dstStep           step in destination image
//    dstRoiSize        region of interest of destination image
//    pState            pointer to filter state
//  Return:
//    ippStsNoErr       no errors
//    ippStsNullPtrErr  pSrc == NULL or pDst == NULL or pState == NULL
//    ippStsStepErr     srcStep or dstStep is less than or equal to zero
//    ippStsSizeErr     width or height of images is less or equal to zero
//    ippStsContextMatchErr invalid context structure
*/

IPPAPI(IppStatus, ippiResizeFilter_8u_C1R, (
    const Ipp8u *pSrc, int srcStep, IppiSize srcRoiSize,
    Ipp8u *pDst, int dstStep, IppiSize dstRoiSize, IppiResizeFilterState *pState))


/* /////////////////////////////////////////////////////////////////////////////
//                     Resize functions. YUY2 pixel format
// ////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeYCbCr422GetBufSize
//  Purpose:            Computes the size of an external work buffer (in bytes)
//  Parameters:
//    srcROI            region of interest of source image
//    dstRoiSize        region of interest of destination image
//    interpolation     type of interpolation to perform for resizing the input image:
//                        IPPI_INTER_NN      Nearest Neighbor interpolation
//                        IPPI_INTER_LINEAR  Linear interpolation
//                        IPPI_INTER_CUBIC   Cubic interpolation
//                        IPPI_INTER_CUBIC2P_CATMULLROM Catmull-Rom cubic filter
//                        IPPI_INTER_LANCZOS Lanczos3 filter
//    pSize             pointer to the external buffer`s size
//  Returns:
//    ippStsNoErr       no errors
//    ippStsNullPtrErr  pSize == NULL
//    ippStsSizeErr     width of src or dst image is less than two, or
//                      height of src or dst image is less than one
//    ippStsDoubleSize  width of src or dst image doesn't multiple of two (indicates warning)
//    ippStsInterpolationErr  interpolation has an illegal value
*/

IPPAPI(IppStatus, ippiResizeYCbCr422GetBufSize, (
    IppiRect srcROI, IppiSize dstRoiSize, int interpolation, int *pSize))

/*
//  Name:               ippiResizeYCbCr422_8u_C2R
//  Purpose:            Performs RESIZE transform for image with YCbCr422 pixel format
//  Parameters:
//    pSrc              source image data
//    srcSize           size of source image
//    srcStep           step in source image
//    srcROI            region of interest of source image
//    pDst              resultant image data
//    dstStep           step in destination image
//    dstRoiSize        region of interest of destination image
//    interpolation     type of interpolation to perform for resizing the input image:
//                        IPPI_INTER_NN      Nearest Neighbor interpolation
//                        IPPI_INTER_LINEAR  Linear interpolation
//                        IPPI_INTER_CUBIC   Cubic interpolation
//                        IPPI_INTER_CUBIC2P_CATMULLROM Catmull-Rom cubic filter
//                        IPPI_INTER_LANCZOS Lanczos3 filter
//    pBuffer           pointer to work buffer
//  Returns:
//    ippStsNoErr       no errors
//    ippStsNullPtrErr  pSrc == NULL or pDst == NULL or pBuffer == NULL
//    ippStsSizeErr     width of src or dst image is less than two, or
//                      height of src or dst image is less than one
//    ippStsDoubleSize  width of src or dst image doesn't multiple of two (indicates warning)
//    ippStsWrongIntersectROI srcROI has not intersection with the source image, no operation
//    ippStsInterpolationErr  interpolation has an illegal value
//  Note:
//    YUY2 pixel format (Y0U0Y1V0,Y2U1Y3V1,.. or Y0Cb0Y1Cr0,Y2Cb1Y3Cr1,..)
*/

IPPAPI(IppStatus, ippiResizeYCbCr422_8u_C2R, (
    const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI,
    Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
    int interpolation, Ipp8u *pBuffer))


/* /////////////////////////////////////////////////////////////////////////////
//                     Affine Transform functions
// ////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiGetAffineBound
//  Purpose:            Computes the bounding rectangle of the transformed image ROI
//  Parameters:
//    srcROI            Source image ROI
//    coeffs            The affine transform matrix
//                        |X'|   |a11 a12| |X| |a13|
//                        |  | = |       |*| |+|   |
//                        |Y'|   |a21 a22| |Y| |a23|
//    bound             Resultant bounding rectangle
//  Returns:
//    ippStsNoErr       OK
*/

IPPAPI(IppStatus, ippiGetAffineBound, (
    IppiRect srcROI, double bound[2][2], const double coeffs[2][3]))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiGetAffineQuad
//  Purpose:            Computes coordinates of the quadrangle to which a source ROI is mapped
//  Parameters:
//    srcROI            Source image ROI
//    coeffs            The affine transform matrix
//                        |X'|   |a11 a12| |X| |a13|
//                        |  | = |       |*| |+|   |
//                        |Y'|   |a21 a22| |Y| |a23|
//    quad              Resultant quadrangle
//  Returns:
//    ippStsNoErr       OK
*/

IPPAPI(IppStatus, ippiGetAffineQuad, (
    IppiRect srcROI, double quad[4][2], const double coeffs[2][3]))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiGetAffineTransform
//  Purpose:            Computes coefficients to transform a source ROI to a given quadrangle
//  Parameters:
//      srcROI          Source image ROI.
//      coeffs          The resultant affine transform matrix
//                        |X'|   |a11 a12| |X| |a13|
//                        |  | = |       |*| |+|   |
//                        |Y'|   |a21 a22| |Y| |a23|
//      quad            Vertex coordinates of the quadrangle
//  Returns:
//    ippStsNoErr       OK
//  Notes: The function computes the coordinates of the 4th vertex of the quadrangle
//         that uniquely depends on the three other (specified) vertices.
//         If the computed coordinates are not equal to the ones specified in quad,
//         the function returns the warning message and continues operation with the computed values
*/

IPPAPI(IppStatus, ippiGetAffineTransform, (
    IppiRect srcROI, const double quad[4][2], double coeffs[2][3]))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiGetAffineSrcRoi
//  Purpose:            Computes the ROI of input image for affine transform
//
//  Parameters:
//    srcSize           Size of the input image (in pixels)
//    coeffs            The affine transform coefficients
//    direction         Transformation direction. Possible values are:
//                          ippWarpForward  - Forward transformation.
//                          ippWarpBackward - Backward transformation.
//    dstRoiOffset      Offset of the destination image ROI
//    dstRoiSize        Size of the ROI of destination image
//    srcROI            Pointer to the computed region of interest in the source image
//
//  Return Values:
//    ippStsNoErr               Indicates no error
//    ippStsNullPtrErr          Indicates an error if one of the specified pointers is NULL
//    ippStsSizeErr             Indicates an error in the following cases:
//                               -  if width or height of the source image is negative or equal to 0
//                               -  if width or height of the destination ROI is negative or equal to 0
//    ippStsOutOfRangeErr           Indicates an error if the destination image offset has negative values
//    ippStsWarpDirectionErr    Indicates an error when the direction value is illegal.
//    ippStsCoeffErr            Indicates an error condition, if affine transformation is singular.
//    ippStsWrongIntersectQuad  Indicates a warning that no operation is performed, if the transformed
//                              source image has no intersection with the destination ROI.
*/
IPPAPI(IppStatus, ippiGetAffineSrcRoi, (IppiSize srcSize, const double coeffs[2][3], IppiWarpDirection direction, IppiPoint dstRoiOffset, IppiSize dstRoiSize, IppiRect *srcRoi))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiGetRotateShift
//  Purpose:            Calculates shifts for ippiGetRotateTransform function to rotate an image
//                      around the specified center (xCenter, yCenter)
//  Parameters:
//    xCenter, yCenter  Coordinates of the center of rotation
//    angle             The angle of clockwise rotation, degrees
//    xShift, yShift    Pointers to the shift values
//  Returns:
//    ippStsNoErr       OK
//    ippStsNullPtrErr  One of the pointers to the output data is NULL
*/
IPPAPI(IppStatus, ippiGetRotateShift, (
    double xCenter, double yCenter, double angle, double *xShift, double *yShift))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:                  ippiGetRotateTransform
//  Purpose:               Computes the affine coefficients for the transform that
//                         rotates an image around (0, 0) by specified angle + shifts it
//                         | cos(angle)  sin(angle)  xShift|
//                         |                               |
//                         |-sin(angle)  cos(angle)  yShift|
//  Parameters:
//    srcROI               Source image ROI
//    angle                The angle of rotation in degrees
//    xShift, yShift       The shift along the corresponding axis
//    coeffs               Output array with the affine transform coefficients
//  Returns:
//    ippStsNoErr          OK
//    ippStsOutOfRangeErr  Indicates an error if the angle is NaN or Infinity
*/

IPPAPI(IppStatus, ippiGetRotateTransform, (
    double angle, double xShift, double yShift, double coeffs[2][3]))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiGetPerspectiveBound
//  Purpose:  Computes the bounding rectangle for the transformed image ROI
//  Context:
//  Returns:        IppStatus.
//    ippStsNoErr   OK
//  Parameters:
//      srcROI  Source image ROI.
//      coeffs  The perspective transform matrix
//                     a11*j + a12*i + a13
//                 x = -------------------
//                     a31*j + a32*i + a33
//
//                     a21*j + a22*i + a23
//                 y = -------------------
//                     a31*j + a32*i + a33
//      bound   Output array with vertex coordinates of the bounding rectangle
//  Notes:
*/

IPPAPI(IppStatus, ippiGetPerspectiveBound, (IppiRect srcROI, double bound[2][2], const double coeffs[3][3]))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiGetPerspectiveQuad
//  Purpose:    Computes the quadrangle to which the source ROI would be mapped
//  Context:
//  Returns:        IppStatus
//    ippStsNoErr   OK
//  Parameters:
//      srcROI    Source image ROI
//      coeffs    The perspective transform matrix
//                     a11*j + a12*i + a13
//                 x = -------------------
//                     a31*j + a32*i + a33
//
//                     a21*j + a22*i + a23
//                 y = -------------------
//                     a31*j + a32*i + a33
//      quadr     Output array with vertex coordinates of the quadrangle
//  Notes:
*/

IPPAPI(IppStatus, ippiGetPerspectiveQuad, (IppiRect srcROI, double quad[4][2], const double coeffs[3][3]))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiGetPerspectiveTransform
//  Purpose:  Computes perspective transform matrix to transform the source ROI
//            to the given quadrangle
//  Context:
//  Returns:        IppStatus.
//    ippStsNoErr   OK
//  Parameters:
//      srcROI   Source image ROI.
//      coeffs   The resultant perspective transform matrix
//                     a11*j + a12*i + a13
//                 x = -------------------
//                     a31*j + a32*i + a33
//
//                     a21*j + a22*i + a23
//                 y = -------------------
//                     a31*j + a32*i + a33
//      quad     Vertex coordinates of the quadrangle
//  Notes:
*/

IPPAPI(IppStatus, ippiGetPerspectiveTransform, (IppiRect srcROI, const double quad[4][2], double coeffs[3][3]))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiGetBilinearBound
//  Purpose:  Computes the bounding rectangle for the transformed image ROI
//  Context:
//  Returns:        IppStatus.
//    ippStsNoErr   OK
//  Parameters:
//      srcROI  Source image ROI.
//      coeffs  The bilinear transform matrix
//                  |X|   |a11|      |a12 a13| |J|   |a14|
//                  | | = |   |*JI + |       |*| | + |   |
//                  |Y|   |a21|      |a22 a23| |I|   |a24|
//      bound   Output array with vertex coordinates of the bounding rectangle
//  Notes:
*/

IPPAPI(IppStatus, ippiGetBilinearBound, (IppiRect srcROI, double bound[2][2], const double coeffs[2][4]))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiGetBilinearQuad
//  Purpose:   Computes the quadrangle to which the source ROI would be mapped
//  Context:
//  Returns:        IppStatus.
//    ippStsNoErr   OK
//  Parameters:
//      srcROI   Source image ROI.
//      coeffs   The bilinear transform matrix
//                  |X|   |a11|      |a12 a13| |J|   |a14|
//                  | | = |   |*JI + |       |*| | + |   |
//                  |Y|   |a21|      |a22 a23| |I|   |a24|
//      quadr    Output array with vertex coordinates of the quadrangle
//  Notes:
*/

IPPAPI(IppStatus, ippiGetBilinearQuad, (IppiRect srcROI, double quad[4][2], const double coeffs[2][4]))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiGetBilinearTransform
//  Purpose:  Computes bilinear transform matrix to transform the source ROI
//            to the given quadrangle
//  Context:
//  Returns:        IppStatus.
//    ippStsNoErr        OK
//  Parameters:
//      srcROI         Source image ROI.
//      coeffs      The resultant bilinear transform matrix
//                  |X|   |a11|      |a12 a13| |J|   |a14|
//                  | | = |   |*JI + |       |*| | + |   |
//                  |Y|   |a21|      |a22 a23| |I|   |a24|
//      quad        Vertex coordinates of the quadrangle
//  Notes:
*/

IPPAPI(IppStatus, ippiGetBilinearTransform, (IppiRect srcROI,const double quad[4][2], double coeffs[2][4]))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiWarpBilinearGetBufferSize
//  Purpose:            Computes the size of external buffer for Bilinear transform
//
//  Context:
//    ippStsNoErr             Indicates no error
//    ippStsNullPtrErr        Indicates an error condition, if one of the specified pointers is NULL
//    ippStsSizeErr           Indicates an error condition, if one of the image dimensions has zero or negative value
//    ippStsWarpDirectionErr  Indicates an error when the direction value is illegal.
//    ippStsCoeffErr          Indicates an error condition, if the bilinear transformation is singular.
//    ippStsInterpolationErr  Indicates an error condition, the interpolation has an illegal value
//    ippStsWrongIntersectROI Indicates a warning that no operation is performed,
//                            if the ROI has no intersection with the source or destination ROI. No operation.
//    ippStsWrongIntersectQuad  Indicates a warning that no operation is performed, if the transformed
//                              source image has no intersection with the destination image.
//
//  Parameters:
//    srcSize           Size of the source image
//    srcROI            Region of interest in the source image
//    dstROI            Region of interest in the destination image
//    coeffs            The bilinear transform matrix
//    direction         Transformation direction. Possible values are:
//                          ippWarpForward  - Forward transformation.
//                          ippWarpBackward - Backward transformation.
//    coeffs            The bilinear transform matrix
//    interpolation     The type of interpolation to perform for resampling
//                      the input image. Possible values:
//                          IPPI_INTER_NN       Nearest neighbor interpolation
//                          IPPI_INTER_LINEAR   Linear interpolation
//                          IPPI_INTER_CUBIC    Cubic convolution interpolation
//                          IPPI_SMOOTH_EDGE    Edges smoothing in addition to one of the
//                                              above methods
//    pBufSize          Pointer to the size (in bytes) of the external buffer
*/
IPPAPI(IppStatus, ippiWarpBilinearGetBufferSize, (IppiSize srcSize, IppiRect srcROI, IppiRect dstROI, IppiWarpDirection direction,
                                                  const double coeffs[2][4], int interpolation, int* pBufSize))

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
//      pBuffer     Pointer to the external work buffer
//  Notes:
*/

IPPAPI(IppStatus, ippiWarpBilinear_8u_C1R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWarpBilinear_8u_C3R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWarpBilinear_8u_C4R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWarpBilinear_32f_C1R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWarpBilinear_32f_C3R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWarpBilinear_32f_C4R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWarpBilinear_16u_C1R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWarpBilinear_16u_C3R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWarpBilinear_16u_C4R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation, Ipp8u* pBuffer))

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
//      pBuffer     Pointer to the external work buffer
//  Notes:
*/

IPPAPI(IppStatus, ippiWarpBilinearBack_8u_C1R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWarpBilinearBack_8u_C3R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWarpBilinearBack_8u_C4R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp8u* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWarpBilinearBack_32f_C1R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWarpBilinearBack_32f_C3R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWarpBilinearBack_32f_C4R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp32f* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWarpBilinearBack_16u_C1R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWarpBilinearBack_16u_C3R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWarpBilinearBack_16u_C4R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, Ipp16u* pDst, int dstStep, IppiRect dstROI, const double coeffs[2][4], int interpolation, Ipp8u* pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiWarpBilinearQuadGetBufferSize
//  Purpose:    Computes the size of external buffer for Bilinear warping of
//              an arbitrary quadrangle in the source image to the quadrangle
//              in the destination image
//
//  Context:
//    ippStsNoErr             Indicates no error
//    ippStsNullPtrErr        Indicates an error condition, if pBufSize is NULL
//    ippStsSizeErr           Indicates an error condition in the following cases:
//                              if one of images ROI x,y has negative value
//                              if one of images ROI dimension has zero or negative value
//    ippStsQuadErr           Indicates an error if either of the given quadrangles is nonconvex
//                            or degenerates into triangle, line, or point.
//    ippStsInterpolateErr    Indicates an error condition, the interpolation has an illegal value.
//
//  Parameters:
//    srcSize     Size of the source image
//    srcROI      Region of interest in the source image
//    srcQuad     A given quadrangle in the source image
//    dstROI      Region of interest in the destination image
//    dstQuad     A given quadrangle in the destination image
//    pBufSize    Pointer to the size (in bytes) of the external buffer
*/

IPPAPI(IppStatus, ippiWarpBilinearQuadGetBufferSize, (IppiSize srcSize, IppiRect srcROI, const double srcQuad[4][2],
                                                      IppiRect dstROI, const double dstQuad[4][2], int interpolation, int* pBufSize))

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
//      pBuffer     Pointer to the external work buffer
//  Notes:
*/

IPPAPI(IppStatus, ippiWarpBilinearQuad_8u_C1R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp8u* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWarpBilinearQuad_8u_C3R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp8u* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWarpBilinearQuad_8u_C4R, (const Ipp8u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp8u* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWarpBilinearQuad_32f_C1R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp32f* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWarpBilinearQuad_32f_C3R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp32f* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWarpBilinearQuad_32f_C4R, (const Ipp32f* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp32f* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWarpBilinearQuad_16u_C1R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp16u* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWarpBilinearQuad_16u_C3R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp16u* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWarpBilinearQuad_16u_C4R, (const Ipp16u* pSrc, IppiSize srcSize, int srcStep, IppiRect srcROI, const double srcQuad[4][2], Ipp16u* pDst, int dstStep, IppiRect dstROI, const double dstQuad[4][2], int interpolation, Ipp8u* pBuffer))


/* /////////////////////////////////////////////////////////////////////////////
//                     Warp Transform functions
// ////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiWarpGetBufferSize
//  Purpose:            Computes the size of external buffer for Warp transform
//
//  Parameters:
//    pSpec             Pointer to the Spec structure for warp transform
//    dstRoiSize        Size of the output image (in pixels)
//    numChannels       Number of channels, possible values are 1 or 3 or 4
//    pBufSize          Pointer to the size (in bytes) of the external buffer
//
//  Return Values:
//    ippStsNoErr           Indicates no error
//    ippStsNullPtrErr      Indicates an error if one of the specified pointers is NULL
//    ippStsNoOperation     Indicates a warning if width or height of output image is zero
//    ippStsContextMatchErr Indicates an error if pointer to an invalid pSpec structure is passed
//    ippStsNumChannelsErr  Indicates an error if numChannels has illegal value
//    ippStsSizeErr         Indicates an error condition in the following cases:
//                          - if width or height of the source image is negative,
//                          - if the calculated buffer size exceeds maximum 32 bit signed integer
//                            positive value (the processed image ROIs are too large ).
//    ippStsSizeWrn         Indicates a warning if the destination image size is more than
//                          the destination image origin size
*/
IPPAPI (IppStatus, ippiWarpGetBufferSize, (const IppiWarpSpec* pSpec, IppiSize dstRoiSize, int* pBufSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiWarpQuadGetSize
//  Purpose:            Computes the size of Spec structure and temporal buffer
//                      for warping of an arbitrary quadrangle in the source
//                      image to the quadrangle in the destination image
//
//  Parameters:
//    srcSize           Size of the input image (in pixels)
//    dstQuad           Given quadrangle in the source image
//    dstSize           Size of the output image (in pixels)
//    dstQuad           Given quadrangle in the destination image
//    transform         Warp transform type. Supported values: ippWarpAffine, and ippWarpPerspective.
//    dataType          Data type of the source and destination images. Possible values
//                      are ipp8u, ipp16u, ipp16s, ipp32f and ipp64f.
//    interpolation     Interpolation method. Supported values: ippNearest, ippLinear and ippCubic.
//    border            Type of the border
//    pSpecSize         Pointer to the size (in bytes) of the Spec structure
//    pInitBufSize      Pointer to the size (in bytes) of the temporal buffer
//
//  Return Values:
//    ippStsNoErr                Indicates no error
//    ippStsNullPtrErr           Indicates an error if one of the specified pointers is NULL
//    ippStsSizeErr              Indicates an error in the following cases:
//                               -  if width or height of the source or destination image is negative,
//                                  or equal to zero
//                               -  if one of the calculated sizes exceeds maximum 32 bit signed integer
//                                  positive value (the size of the one of the processed images is too large).
//    ippStsDataTypeErr          Indicates an error when dataType has an illegal value.
//    ippStsInterpolationErr     Indicates an error if interpolation has an illegal value
//    ippStsNotSupportedModeErr  Indicates an error if the requested mode is not supported.
//    ippStsBorderErr            Indicates an error if border type has an illegal value
//    ippStsQuadErr              Indicates an error if either of the given quadrangles is nonconvex
//                               or degenerates into triangle, line, or point
//    ippStsWarpTransformTypeErr Indicates an error when the transform value is illegal.
//    ippStsWrongIntersectQuad   Indicates a warning that no operation is performed in the following cases:
//                               -  if the transformed source image has no intersection with the destination image.
//                               -  if either of the source quadrangle or destination quadrangle has no intersection
//                                   with the source or destination image correspondingly
//
*/
IPPAPI (IppStatus, ippiWarpQuadGetSize, (IppiSize srcSize, const double srcQuad[4][2], IppiSize dstSize, const double dstQuad[4][2],
                                         IppiWarpTransformType transform, IppDataType dataType, IppiInterpolationType interpolation,
                                         IppiBorderType borderType, int* pSpecSize, int* pInitBufSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiWarpQuadNearestInit
//                      ippiWarpQuadLinearInit
//                      ippiWarpQuadCubicInit
//
//  Purpose:            Initializes the Spec structure for warping of
//                      an arbitrary quadrangle in the source image to the quadrangle
//                      in the destination image
//
//  Parameters:
//    srcSize           Size of the input image (in pixels)
//    srcQuad           Given quadrangle in the source image
//    dstSize           Size of the output image (in pixels)
//    dstQuad           Given quadrangle in the destination image
//    transform         Warp transform type. Supported values: ippWarpAffine, and ippWarpPerspective.
//    dataType          Data type of the source and destination images. Possible values
//                      are ipp8u, ipp16u, ipp16s, ipp32f and ipp64f.
//    numChannels       Number of channels, possible values are 1 or 3 or 4
//    valueB            The first parameter (B) for specifying Cubic filters
//    valueC            The second parameter (C) for specifying Cubic filters
//    border            Type of the border
//    borderValue       Pointer to the constant value(s) if border type equals ippBorderConstant
//    smoothEdge        The smooth edge flag. Supported values:
//                          0 - transform without edge smoothing
//                          1 - transform with edge smoothing
//    pSpec             Pointer to the Spec structure for resize filter
//    pInitBuf          Pointer to the temporal buffer for several initialization cases
//
//  Return Values:
//    ippStsNoErr               Indicates no error
//    ippStsNullPtrErr          Indicates an error if one of the specified pointers is NULL
//    ippStsSizeErr             Indicates an error if width or height of the source or destination
//                              image is negative, or equal to zero
//    ippStsDataTypeErr         Indicates an error when dataType has an illegal value.
//    ippStsWarpTransformErr    Indicates an error when the transform value is illegal.
//    ippStsNumChannelsErr      Indicates an error if numChannels has illegal value
//    ippStsBorderErr           Indicates an error if border type has an illegal value
//    ippStsQuadErr             Indicates an error if either of the given quadrangles is nonconvex
//                               or degenerates into triangle, line, or point
//    ippStsWrongIntersectQuad  Indicates a warning that no operation is performed, if the transformed
//                              source image has no intersection with the destination image.
//    ippStsNotSupportedModeErr Indicates an error if the requested mode is not supported.
//
//  Notes/References:
//    1. The equation shows the family of cubic filters:
//           ((12-9B-6C)*|x|^3 + (-18+12B+6C)*|x|^2                  + (6-2B)  ) / 6   for |x| < 1
//    K(x) = ((   -B-6C)*|x|^3 + (    6B+30C)*|x|^2 + (-12B-48C)*|x| + (8B+24C); / 6   for 1 <= |x| < 2
//           0   elsewhere
//    Some values of (B,C) correspond to known cubic splines: Catmull-Rom (B=0,C=0.5), B-Spline (B=1,C=0) and other.
//      Mitchell, Don P.; Netravali, Arun N. (Aug. 1988). "Reconstruction filters in computer graphics"
//      http://www.mentallandscape.com/Papers_siggraph88.pdf
//
//    2. Supported border types are ippBorderTransp and ippBorderInMem
*/
IPPAPI (IppStatus, ippiWarpQuadNearestInit,
        (IppiSize srcSize, const double srcQuad[4][2], IppiSize dstSize,
         const double dstQuad[4][2], IppiWarpTransformType transform,IppDataType dataType, int numChannels,
         IppiBorderType borderType, const Ipp64f *pBorderValue, int smoothEdge, IppiWarpSpec* pSpec))

IPPAPI (IppStatus, ippiWarpQuadLinearInit,
        (IppiSize srcSize, const double srcQuad[4][2], IppiSize dstSize,
         const double dstQuad[4][2], IppiWarpTransformType transform, IppDataType dataType, int numChannels,
         IppiBorderType borderType, const Ipp64f *pBorderValue, int smoothEdge, IppiWarpSpec* pSpec))

IPPAPI (IppStatus, ippiWarpQuadCubicInit,
        (IppiSize srcSize, const double srcQuad[4][2], IppiSize dstSize,
         const double dstQuad[4][2], IppiWarpTransformType transform, IppDataType dataType, int numChannels,
         Ipp64f valueB, Ipp64f valueC, IppiBorderType borderType, const Ipp64f *pBorderValue, int smoothEdge,
         IppiWarpSpec* pSpec, Ipp8u* pInitBuf))

/* /////////////////////////////////////////////////////////////////////////////
//                     Warp Affine Transform functions
// ////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiWarpAffineGetSize
//  Purpose:            Computes the size of Spec structure and temporal buffer for Affine transform
//
//  Parameters:
//    srcSize           Size of the input image (in pixels)
//    dstSize           Size of the output image (in pixels)
//    dataType          Data type of the source and destination images. Possible values
//                      are ipp8u, ipp16u, ipp16s, ipp32f and ipp64f.
//    coeffs            The affine transform coefficients
//    interpolation     Interpolation method. Supported values: ippNearest, ippLinear and ippCubic.
//    direction         Transformation direction. Possible values are:
//                          ippWarpForward  - Forward transformation.
//                          ippWarpBackward - Backward transformation.
//    border            Type of the border
//    pSpecSize         Pointer to the size (in bytes) of the Spec structure
//    pInitBufSize      Pointer to the size (in bytes) of the temporal buffer
//
//  Return Values:
//    ippStsNoErr               Indicates no error
//    ippStsNullPtrErr          Indicates an error if one of the specified pointers is NULL
//    ippStsNoOperation         Indicates a warning if width or height of any image is zero
//    ippStsSizeErr             Indicates an error if width or height of the source
//                              or destination image is negative,
//    ippStsDataTypeErr         Indicates an error when dataType has an illegal value.
//    ippStsWarpDirectionErr    Indicates an error when the direction value is illegal.
//    ippStsInterpolationErr    Indicates an error if interpolation has an illegal value
//    ippStsNotSupportedModeErr Indicates an error if the requested mode is not supported.
//    ippStsCoeffErr            Indicates an error condition, if affine transformation is singular.
//    ippStsBorderErr           Indicates an error if border type has an illegal value
//    ippStsExceededSizeErr     Indicates an error in the following cases:
//                              -  if one of the calculated sizes exceeds maximum of 32 bit signed integer
//                                 type positive value (the size of the one of the processed images is too large)
//                              -  if one of width or height of the destination image or the source image
//                                 exceeds 33554431 (0x1FFFFFF)
//
*/
IPPAPI (IppStatus, ippiWarpAffineGetSize, (IppiSize srcSize, IppiSize dstSize, IppDataType dataType, const double coeffs[2][3],
                                           IppiInterpolationType interpolation, IppiWarpDirection direction,
                                           IppiBorderType borderType, int* pSpecSize, int* pInitBufSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiWarpAffineNearestInit
//                      ippiWarpAffineLinearInit
//                      ippiWarpAffineCubicInit
//
//  Purpose:            Initializes the Spec structure for the Warp affine transform
//                      by different interpolation methods
//
//  Parameters:
//    srcSize           Size of the input image (in pixels)
//    dstSize           Size of the output image (in pixels)
//    dataType          Data type of the source and destination images. Possible values are:
//                      ipp8u, ipp16u, ipp16s, ipp32f, ipp64f.
//    coeffs            The affine transform coefficients
//    direction         Transformation direction. Possible values are:
//                          ippWarpForward  - Forward transformation.
//                          ippWarpBackward - Backward transformation.
//    numChannels       Number of channels, possible values are 1 or 3 or 4
//    valueB            The first parameter (B) for specifying Cubic filters
//    valueC            The second parameter (C) for specifying Cubic filters
//    border            Type of the border
//    borderValue       Pointer to the constant value(s) if border type equals ippBorderConstant
//    smoothEdge        The smooth edge flag. Supported values:
//                          0 - transform without edge smoothing
//                          1 - transform with edge smoothing
//    pSpec             Pointer to the Spec structure for resize filter
//    pInitBuf          Pointer to the temporal buffer for several initialization cases
//
//  Return Values:
//    ippStsNoErr               Indicates no error
//    ippStsNullPtrErr          Indicates an error if one of the specified pointers is NULL
//    ippStsNoOperation         Indicates a warning if width or height of any image is zero
//    ippStsSizeErr             Indicates an error if width or height of the source or destination
//                              image is negative
//    ippStsDataTypeErr         Indicates an error when dataType has an illegal value.
//    ippStsWarpDirectionErr    Indicates an error when the direction value is illegal.
//    ippStsCoeffErr            Indicates an error condition, if the affine transformation is singular.
//    ippStsNumChannelsErr      Indicates an error if numChannels has illegal value
//    ippStsBorderErr           Indicates an error if border type has an illegal value
//    ippStsWrongIntersectQuad  Indicates a warning that no operation is performed, if the transformed
//                              source image has no intersection with the destination image.
//    ippStsNotSupportedModeErr Indicates an error if the requested mode is not supported.
//    ippStsExceededSizeErr     Indicates an error if one of width or height of the destination
//                              image or the source image exceeds 33554431 (0x1FFFFFF)
//
//  Notes/References:
//    1. The equation shows the family of cubic filters:
//           ((12-9B-6C)*|x|^3 + (-18+12B+6C)*|x|^2                  + (6-2B)  ) / 6   for |x| < 1
//    K(x) = ((   -B-6C)*|x|^3 + (    6B+30C)*|x|^2 + (-12B-48C)*|x| + (8B+24C); / 6   for 1 <= |x| < 2
//           0   elsewhere
//    Some values of (B,C) correspond to known cubic splines: Catmull-Rom (B=0,C=0.5), B-Spline (B=1,C=0) and other.
//      Mitchell, Don P.; Netravali, Arun N. (Aug. 1988). "Reconstruction filters in computer graphics"
//      http://www.mentallandscape.com/Papers_siggraph88.pdf
//
//    2. Supported border types are ippBorderRepl, ippBorderConst, ippBorderTransp and ippBorderInMem
*/
IPPAPI (IppStatus, ippiWarpAffineNearestInit, (IppiSize srcSize, IppiSize dstSize, IppDataType dataType, const double coeffs[2][3],
                                               IppiWarpDirection direction, int numChannels, IppiBorderType borderType,
                                               const Ipp64f *pBorderValue, int smoothEdge, IppiWarpSpec* pSpec))
IPPAPI (IppStatus, ippiWarpAffineLinearInit, (IppiSize srcSize, IppiSize dstSize, IppDataType dataType, const double coeffs[2][3],
                                               IppiWarpDirection direction, int numChannels, IppiBorderType borderType,
                                               const Ipp64f *pBorderValue, int smoothEdge, IppiWarpSpec* pSpec))
IPPAPI (IppStatus, ippiWarpAffineCubicInit, (IppiSize srcSize, IppiSize dstSize, IppDataType dataType, const double coeffs[2][3],
                                             IppiWarpDirection direction, int numChannels, Ipp64f valueB, Ipp64f valueC,
                                             IppiBorderType borderType, const Ipp64f *pBorderValue, int smoothEdge, IppiWarpSpec* pSpec,
                                             Ipp8u* pInitBuf))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiWarpAffineNearest
//                      ippiWarpAffineLinear
//                      ippiWarpAffineCubic
//
//  Purpose:            Performs affine transform of an image with using different interpolation methods
//
//  Parameters:
//    pSrc              Pointer to the source image
//    srcStep           Distance (in bytes) between of consecutive lines in the source image
//    pDst              Pointer to the destination image
//    dstStep           Distance (in bytes) between of consecutive lines in the destination image
//    dstRoiOffset      Offset of tiled image respectively destination image origin
//    dstRoiSize        Size of the destination image (in pixels)
//    border            Type of the border
//    borderValue       Pointer to the constant value(s) if border type equals ippBorderConstant
//    pSpec             Pointer to the Spec structure for resize filter
//    pBuffer           Pointer to the work buffer
//
//  Return Values:
//    ippStsNoErr               Indicates no error
//    ippStsNullPtrErr          Indicates an error if one of the specified pointers is NULL
//    ippStsNoOperation         Indicates a warning if width or height of output image is zero
//    ippStsBorderErr           Indicates an error if border type has an illegal value
//    ippStsContextMatchErr     Indicates an error if pointer to an invalid pSpec structure is passed
//    ippStsNotSupportedModeErr Indicates an error if requested mode is currently not supported
//    ippStsSizeErr             Indicates an error if width or height of the destination image
//                              is negative
//    ippStsStepErr             Indicates an error if the step value is not data type multiple
//    ippStsOutOfRangeErr       Indicates an error if the destination image offset point is outside the
//                              destination image origin
//    ippStsSizeWrn             Indicates a warning if the destination image size is more than
//                              the destination image origin size
//    ippStsWrongIntersectQuad  Indicates a warning that no operation is performed if the destination
//                              ROI has no intersection with the transformed source image origin.
//
//  Notes:
//    1. Supported border types are ippBorderRepl, ippBorderConst, ippBorderTransp and ippBorderRepl
*/
IPPAPI (IppStatus, ippiWarpAffineNearest_8u_C1R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_8u_C3R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_8u_C4R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_16u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
                                                   IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_16u_C3R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
                                                   IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_16u_C4R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
                                                   IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_16s_C1R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
                                                   IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_16s_C3R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
                                                   IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_16s_C4R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
                                                   IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_32f_C1R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
                                                   IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_32f_C3R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
                                                   IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_32f_C4R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
                                                   IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_64f_C1R, (const Ipp64f* pSrc, int srcStep, Ipp64f* pDst, int dstStep,
                                                   IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_64f_C3R, (const Ipp64f* pSrc, int srcStep, Ipp64f* pDst, int dstStep,
                                                   IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_64f_C4R, (const Ipp64f* pSrc, int srcStep, Ipp64f* pDst, int dstStep,
                                                   IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))

IPPAPI (IppStatus, ippiWarpAffineLinear_8u_C1R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_8u_C3R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_8u_C4R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_16u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_16u_C3R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_16u_C4R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_16s_C1R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_16s_C3R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_16s_C4R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_32f_C1R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_32f_C3R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_32f_C4R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_64f_C1R, (const Ipp64f* pSrc, int srcStep, Ipp64f* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_64f_C3R, (const Ipp64f* pSrc, int srcStep, Ipp64f* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_64f_C4R, (const Ipp64f* pSrc, int srcStep, Ipp64f* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))

IPPAPI (IppStatus, ippiWarpAffineCubic_8u_C1R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
                                                IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_8u_C3R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
                                                IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_8u_C4R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
                                                IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_16u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_16u_C3R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_16u_C4R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_16s_C1R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_16s_C3R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_16s_C4R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_32f_C1R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_32f_C3R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_32f_C4R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_64f_C1R, (const Ipp64f* pSrc, int srcStep, Ipp64f* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_64f_C3R, (const Ipp64f* pSrc, int srcStep, Ipp64f* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_64f_C4R, (const Ipp64f* pSrc, int srcStep, Ipp64f* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//                     Warp Perspective Transform functions
// ////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiWarpGetRectInfinite
//  Purpose:            Returns the constant value ippRectInfinite
//
//                      ippRectInfinite = {IPP_MIN_32S/2, IPP_MIN_32S/2,
//                                         IPP_MAX_32S,   IPP_MAX_32S};
//
//  Return Values:
//    ippRectInfinite constant value of IppiRect type
//
*/
IPPAPI(IppiRect, ippiWarpGetRectInfinite, (void))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiWarpPerspectiveGetSize
//  Purpose:            Computes the size of Spec structure and temporal buffer
//                      for Perspective transform
//
//  Parameters:
//    srcSize           Size of the input image (in pixels)
//    srcRoi            Region of interest in the source image
//    dstSize           Size of the output image (in pixels)
//    dataType          Data type of the source and destination images. Possible values
//                      are ipp8u, ipp16u, ipp16s, ipp32f and ipp64f.
//    coeffs            The perspective transform coefficients
//    interpolation     Interpolation method. Supported values: ippNearest, ippLinear and ippCubic.
//    direction         Transformation direction. Possible values are:
//                          ippWarpForward  - Forward transformation.
//                          ippWarpBackward - Backward transformation.
//    border            Type of the border
//    pSpecSize         Pointer to the size (in bytes) of the Spec structure
//    pInitBufSize      Pointer to the size (in bytes) of the temporal buffer
//
//  Return Values:
//    ippStsNoErr               Indicates no error
//    ippStsNullPtrErr          Indicates an error if one of the specified pointers is NULL
//    ippStsNoOperation         Indicates a warning if width or height of any image is zero
//    ippStsSizeErr             Indicates an error in the following cases:
//                              -  if width or height of the source or destination image is negative,
//                              -  if one of the calculated sizes exceeds maximum 32 bit signed integer
//                                 positive value (the size of the one of the processed images is too large).
//    ippStsDataTypeErr         Indicates an error when dataType has an illegal value.
//    ippStsWarpDirectionErr    Indicates an error when the direction value is illegal.
//    ippStsInterpolationErr    Indicates an error if interpolation has an illegal value
//    ippStsNotSupportedModeErr Indicates an error if the requested mode is not supported.
//    ippStsCoeffErr            Indicates an error condition, if perspective transformation is singular.
//    ippStsBorderErr           Indicates an error if border type has an illegal value
//
*/
IPPAPI (IppStatus, ippiWarpPerspectiveGetSize, (IppiSize srcSize, IppiRect srcRoi, IppiSize dstSize, IppDataType dataType,
                                                const double coeffs[3][3], IppiInterpolationType interpolation,
                                                IppiWarpDirection direction, IppiBorderType borderType, int* pSpecSize,
                                                int* pInitBufSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiWarpPerspectiveNearestInit
//                      ippiWarpPerspectiveLinearInit
//                      ippiWarpPerspectiveCubicInit
//
//  Purpose:            Initializes the Spec structure for the Warp perspective transform
//                      by different interpolation methods
//
//  Parameters:
//    srcSize           Size of the input image (in pixels)
//    srcRoi            Region of interest in the source image
//    dstSize           Size of the output image (in pixels)
//    dataType          Data type of the source and destination images. Possible values are:
//                      ipp8u, ipp16u, ipp16s, ipp32f, ipp64f.
//    coeffs            The perspective transform coefficients
//    direction         Transformation direction. Possible values are:
//                          ippWarpForward  - Forward transformation.
//                          ippWarpBackward - Backward transformation.
//    numChannels       Number of channels, possible values are 1 or 3 or 4
//    valueB            The first parameter (B) for specifying Cubic filters
//    valueC            The second parameter (C) for specifying Cubic filters
//    border            Type of the border
//    borderValue       Pointer to the constant value(s) if border type equals ippBorderConstant
//    smoothEdge        The smooth edge flag. Supported values:
//                          0 - transform without edge smoothing
//                          1 - transform with edge smoothing
//    pSpec             Pointer to the Spec structure for resize filter
//    pInitBuf          Pointer to the temporal buffer for several initialization cases
//
//  Return Values:
//    ippStsNoErr               Indicates no error
//    ippStsNullPtrErr          Indicates an error if one of the specified pointers is NULL
//    ippStsNoOperation         Indicates a warning if width or height of any image is zero
//    ippStsSizeErr             Indicates an error if width or height of the source or destination
//                              image is negative
//    ippStsDataTypeErr         Indicates an error when dataType has an illegal value.
//    ippStsWarpDirectionErr    Indicates an error when the direction value is illegal.
//    ippStsCoeffErr            Indicates an error condition, if the perspective transformation is singular.
//    ippStsNumChannelsErr      Indicates an error if numChannels has illegal value
//    ippStsBorderErr           Indicates an error if border type has an illegal value
//    ippStsWrongIntersectQuad  Indicates a warning that no operation is performed, if the transformed
//                              source image has no intersection with the destination image.
//    ippStsNotSupportedModeErr Indicates an error if the requested mode is not supported.
//
//  Notes/References:
//    1. The equation shows the family of cubic filters:
//           ((12-9B-6C)*|x|^3 + (-18+12B+6C)*|x|^2                  + (6-2B)  ) / 6   for |x| < 1
//    K(x) = ((   -B-6C)*|x|^3 + (    6B+30C)*|x|^2 + (-12B-48C)*|x| + (8B+24C); / 6   for 1 <= |x| < 2
//           0   elsewhere
//    Some values of (B,C) correspond to known cubic splines: Catmull-Rom (B=0,C=0.5), B-Spline (B=1,C=0) and other.
//      Mitchell, Don P.; Netravali, Arun N. (Aug. 1988). "Reconstruction filters in computer graphics"
//      http://www.mentallandscape.com/Papers_siggraph88.pdf
//
//    2. Supported border types are ippBorderRepl, ippBorderConst, ippBorderTransp and ippBorderRepl
*/
IPPAPI (IppStatus, ippiWarpPerspectiveNearestInit, (IppiSize srcSize, IppiRect srcRoi, IppiSize dstSize, IppDataType dataType,
                                                    const double coeffs[3][3], IppiWarpDirection direction, int numChannels,
                                                    IppiBorderType borderType, const Ipp64f *pBorderValue, int smoothEdge, IppiWarpSpec* pSpec))
IPPAPI (IppStatus, ippiWarpPerspectiveLinearInit, (IppiSize srcSize, IppiRect srcRoi, IppiSize dstSize, IppDataType dataType,
                                                   const double coeffs[3][3], IppiWarpDirection direction, int numChannels,
                                                   IppiBorderType borderType, const Ipp64f *pBorderValue, int smoothEdge, IppiWarpSpec* pSpec))
IPPAPI (IppStatus, ippiWarpPerspectiveCubicInit, (IppiSize srcSize, IppiRect srcRoi, IppiSize dstSize, IppDataType dataType, const double coeffs[3][3],
                                                  IppiWarpDirection direction, int numChannels, Ipp64f valueB, Ipp64f valueC,
                                                  IppiBorderType borderType, const Ipp64f *pBorderValue, int smoothEdge, IppiWarpSpec* pSpec,
                                                  Ipp8u* pInitBuf))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiWarpPerspectiveNearest
//                      ippiWarpPerspectiveLinear
//                      ippiWarpPerspectiveCubic
//
//  Purpose:            Performs perspective transform of an image with using
//                      different interpolation methods
//
//  Parameters:
//    pSrc              Pointer to the source image
//    srcStep           Distance (in bytes) between of consecutive lines in the source image
//    pDst              Pointer to the destination image
//    dstStep           Distance (in bytes) between of consecutive lines in the destination image
//    dstRoiOffset      Offset of tiled image respectively destination image origin
//    dstRoiSize        Size of the destination image (in pixels)
//    border            Type of the border
//    borderValue       Pointer to the constant value(s) if border type equals ippBorderConstant
//    pSpec             Pointer to the Spec structure for resize filter
//    pBuffer           Pointer to the work buffer
//
//  Return Values:
//    ippStsNoErr               Indicates no error
//    ippStsNullPtrErr          Indicates an error if one of the specified pointers is NULL
//    ippStsNoOperation         Indicates a warning if width or height of output image is zero
//    ippStsBorderErr           Indicates an error if border type has an illegal value
//    ippStsContextMatchErr     Indicates an error if pointer to an invalid pSpec structure is passed
//    ippStsNotSupportedModeErr Indicates an error if requested mode is currently not supported
//    ippStsSizeErr             Indicates an error if width or height of the destination image
//                              is negative
//    ippStsStepErr             Indicates an error if the step value is not data type multiple
//    ippStsOutOfRangeErr       Indicates an error if the destination image offset point is outside the
//                              destination image origin
//    ippStsSizeWrn             Indicates a warning if the destination image size is more than
//                              the destination image origin size
//    ippStsWrongIntersectQuad  Indicates a warning that no operation is performed if the destination
//                              ROI has no intersection with the transformed source image origin.
//
//  Notes:
//    1. Supported border types are ippBorderRepl, ippBorderConst, ippBorderTransp and ippBorderRepl
*/
IPPAPI (IppStatus, ippiWarpPerspectiveNearest_8u_C1R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveNearest_8u_C3R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveNearest_8u_C4R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveNearest_16u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
                                                   IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveNearest_16u_C3R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
                                                   IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveNearest_16u_C4R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
                                                   IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveNearest_16s_C1R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
                                                   IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveNearest_16s_C3R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
                                                   IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveNearest_16s_C4R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
                                                   IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveNearest_32f_C1R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
                                                   IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveNearest_32f_C3R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
                                                   IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveNearest_32f_C4R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
                                                   IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))

IPPAPI (IppStatus, ippiWarpPerspectiveLinear_8u_C1R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveLinear_8u_C3R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveLinear_8u_C4R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveLinear_16u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveLinear_16u_C3R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveLinear_16u_C4R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveLinear_16s_C1R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveLinear_16s_C3R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveLinear_16s_C4R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveLinear_32f_C1R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveLinear_32f_C3R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveLinear_32f_C4R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
                                                  IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))

IPPAPI (IppStatus, ippiWarpPerspectiveCubic_8u_C1R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
                                                IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveCubic_8u_C3R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
                                                IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveCubic_8u_C4R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
                                                IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveCubic_16u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveCubic_16u_C3R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveCubic_16u_C4R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveCubic_16s_C1R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveCubic_16s_C3R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveCubic_16s_C4R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveCubic_32f_C1R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveCubic_32f_C3R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpPerspectiveCubic_32f_C4R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
                                                 IppiPoint dstRoiOffset, IppiSize dstRoiSize, const IppiWarpSpec* pSpec,
                                                 Ipp8u* pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//                   Statistic functions
///////////////////////////////////////////////////////////////////////////// */

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
IPPAPI(IppStatus,  ippiMomentGetStateSize_64f, (IppHintAlgorithm hint, int * pSize))


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
IPPAPI (IppStatus, ippiMomentInit_64f, (IppiMomentState_64f* pState, IppHintAlgorithm hint))


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
IPPAPI(IppStatus,ippiMoments64f_8u_C1R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, IppiMomentState_64f* pCtx))
IPPAPI(IppStatus,ippiMoments64f_8u_C3R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, IppiMomentState_64f* pCtx))
IPPAPI(IppStatus,ippiMoments64f_8u_AC4R,(const Ipp8u* pSrc, int srcStep, IppiSize roiSize, IppiMomentState_64f* pCtx))

IPPAPI(IppStatus,ippiMoments64f_32f_C1R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, IppiMomentState_64f* pCtx))
IPPAPI(IppStatus,ippiMoments64f_32f_C3R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, IppiMomentState_64f* pCtx))
IPPAPI(IppStatus,ippiMoments64f_32f_AC4R,(const Ipp32f* pSrc, int srcStep, IppiSize roiSize, IppiMomentState_64f* pCtx))

IPPAPI(IppStatus,ippiMoments64f_16u_C1R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, IppiMomentState_64f* pCtx))
IPPAPI(IppStatus,ippiMoments64f_16u_C3R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, IppiMomentState_64f* pCtx))
IPPAPI(IppStatus,ippiMoments64f_16u_AC4R,(const Ipp16u* pSrc, int srcStep, IppiSize roiSize, IppiMomentState_64f* pCtx))


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
IPPAPI(IppStatus,ippiGetSpatialMoment_64f,(const IppiMomentState_64f* pState,
                                       int mOrd, int nOrd, int nChannel,
                                       IppiPoint roiOffset, Ipp64f* pValue))
IPPAPI(IppStatus,ippiGetCentralMoment_64f,(const IppiMomentState_64f* pState,
                                       int mOrd, int nOrd, int nChannel,
                                       Ipp64f* pValue))

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
IPPAPI(IppStatus,ippiGetNormalizedSpatialMoment_64f,(const IppiMomentState_64f* pState,
                                   int mOrd, int nOrd, int nChannel,
                                   IppiPoint roiOffset, Ipp64f* pValue))
IPPAPI(IppStatus,ippiGetNormalizedCentralMoment_64f,(const IppiMomentState_64f* pState,
                                   int mOrd, int nOrd, int nChannel,
                                   Ipp64f* pValue))


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
IPPAPI(IppStatus,ippiGetHuMoments_64f,(const IppiMomentState_64f* pState,
                                   int nChannel, IppiHuMoment_64f pHm))


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

IPPAPI(IppStatus, ippiNorm_Inf_8u_C1R, (const Ipp8u* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNorm_Inf_8u_C3R, (const Ipp8u* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNorm_Inf_8u_C4R, (const Ipp8u* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNorm_Inf_16s_C1R, (const Ipp16s* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNorm_Inf_16s_C3R, (const Ipp16s* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNorm_Inf_16s_C4R, (const Ipp16s* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNorm_Inf_16u_C1R, (const Ipp16u* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNorm_Inf_16u_C3R, (const Ipp16u* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNorm_Inf_16u_C4R, (const Ipp16u* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNorm_Inf_32f_C1R, (const Ipp32f* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNorm_Inf_32f_C3R, (const Ipp32f* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNorm_Inf_32f_C4R, (const Ipp32f* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f value[4]))

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

IPPAPI(IppStatus, ippiNorm_L1_8u_C1R, (const Ipp8u* pSrc, int srcStep,
                                      IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNorm_L1_8u_C3R, (const Ipp8u* pSrc, int srcStep,
                                      IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNorm_L1_8u_C4R, (const Ipp8u* pSrc, int srcStep,
                                       IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNorm_L1_16s_C1R, (const Ipp16s* pSrc, int srcStep,
                                      IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNorm_L1_16s_C3R, (const Ipp16s* pSrc, int srcStep,
                                      IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNorm_L1_16s_C4R, (const Ipp16s* pSrc, int srcStep,
                                       IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNorm_L1_16u_C1R, (const Ipp16u* pSrc, int srcStep,
                                      IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNorm_L1_16u_C3R, (const Ipp16u* pSrc, int srcStep,
                                      IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNorm_L1_16u_C4R, (const Ipp16u* pSrc, int srcStep,
                                       IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNorm_L1_32f_C1R, (const Ipp32f* pSrc, int srcStep,
                                      IppiSize roiSize, Ipp64f* pValue, IppHintAlgorithm hint))

IPPAPI(IppStatus, ippiNorm_L1_32f_C3R, (const Ipp32f* pSrc, int srcStep,
                                      IppiSize roiSize, Ipp64f value[3], IppHintAlgorithm hint))

IPPAPI(IppStatus, ippiNorm_L1_32f_C4R, (const Ipp32f* pSrc, int srcStep,
                                       IppiSize roiSize, Ipp64f value[4], IppHintAlgorithm hint))

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

IPPAPI(IppStatus, ippiNorm_L2_8u_C1R, (const Ipp8u* pSrc, int srcStep,
                                      IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNorm_L2_8u_C3R, (const Ipp8u* pSrc, int srcStep,
                                      IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNorm_L2_8u_C4R, (const Ipp8u* pSrc, int srcStep,
                                       IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNorm_L2_16s_C1R, (const Ipp16s* pSrc, int srcStep,
                                      IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNorm_L2_16s_C3R, (const Ipp16s* pSrc, int srcStep,
                                      IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNorm_L2_16s_C4R, (const Ipp16s* pSrc, int srcStep,
                                       IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNorm_L2_16u_C1R, (const Ipp16u* pSrc, int srcStep,
                                      IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNorm_L2_16u_C3R, (const Ipp16u* pSrc, int srcStep,
                                      IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNorm_L2_16u_C4R, (const Ipp16u* pSrc, int srcStep,
                                       IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNorm_L2_32f_C1R, (const Ipp32f* pSrc, int srcStep,
                                      IppiSize roiSize, Ipp64f* pValue, IppHintAlgorithm hint))

IPPAPI(IppStatus, ippiNorm_L2_32f_C3R, (const Ipp32f* pSrc, int srcStep,
                                      IppiSize roiSize, Ipp64f value[3], IppHintAlgorithm hint))

IPPAPI(IppStatus, ippiNorm_L2_32f_C4R, (const Ipp32f* pSrc, int srcStep,
                                       IppiSize roiSize, Ipp64f value[4], IppHintAlgorithm hint))

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

IPPAPI(IppStatus, ippiNormDiff_Inf_8u_C1R, (const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNormDiff_Inf_8u_C3R, (const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNormDiff_Inf_8u_C4R, (const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNormDiff_Inf_16s_C1R, (const Ipp16s* pSrc1, int src1Step,
                                        const Ipp16s* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNormDiff_Inf_16s_C3R, (const Ipp16s* pSrc1, int src1Step,
                                        const Ipp16s* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNormDiff_Inf_16s_C4R, (const Ipp16s* pSrc1, int src1Step,
                                        const Ipp16s* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNormDiff_Inf_16u_C1R, (const Ipp16u* pSrc1, int src1Step,
                                        const Ipp16u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNormDiff_Inf_16u_C3R, (const Ipp16u* pSrc1, int src1Step,
                                        const Ipp16u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNormDiff_Inf_16u_C4R, (const Ipp16u* pSrc1, int src1Step,
                                        const Ipp16u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNormDiff_Inf_32f_C1R, (const Ipp32f* pSrc1, int src1Step,
                                        const Ipp32f* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNormDiff_Inf_32f_C3R, (const Ipp32f* pSrc1, int src1Step,
                                        const Ipp32f* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNormDiff_Inf_32f_C4R, (const Ipp32f* pSrc1, int src1Step,
                                        const Ipp32f* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[4]))

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

IPPAPI(IppStatus, ippiNormDiff_L1_8u_C1R, (const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNormDiff_L1_8u_C3R, (const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNormDiff_L1_8u_C4R, (const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNormDiff_L1_16s_C1R, (const Ipp16s* pSrc1, int src1Step,
                                        const Ipp16s* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNormDiff_L1_16s_C3R, (const Ipp16s* pSrc1, int src1Step,
                                        const Ipp16s* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNormDiff_L1_16s_C4R, (const Ipp16s* pSrc1, int src1Step,
                                        const Ipp16s* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNormDiff_L1_16u_C1R, (const Ipp16u* pSrc1, int src1Step,
                                        const Ipp16u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNormDiff_L1_16u_C3R, (const Ipp16u* pSrc1, int src1Step,
                                        const Ipp16u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNormDiff_L1_16u_C4R, (const Ipp16u* pSrc1, int src1Step,
                                        const Ipp16u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNormDiff_L1_32f_C1R, (const Ipp32f* pSrc1, int src1Step,
                                        const Ipp32f* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f* pValue, IppHintAlgorithm hint))

IPPAPI(IppStatus, ippiNormDiff_L1_32f_C3R, (const Ipp32f* pSrc1, int src1Step,
                                        const Ipp32f* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3], IppHintAlgorithm hint))

IPPAPI(IppStatus, ippiNormDiff_L1_32f_C4R, (const Ipp32f* pSrc1, int src1Step,
                                        const Ipp32f* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[4], IppHintAlgorithm hint))

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

IPPAPI(IppStatus, ippiNormDiff_L2_8u_C1R, (const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNormDiff_L2_8u_C3R, (const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNormDiff_L2_8u_C4R, (const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNormDiff_L2_16s_C1R, (const Ipp16s* pSrc1, int src1Step,
                                        const Ipp16s* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNormDiff_L2_16s_C3R, (const Ipp16s* pSrc1, int src1Step,
                                        const Ipp16s* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNormDiff_L2_16s_C4R, (const Ipp16s* pSrc1, int src1Step,
                                        const Ipp16s* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNormDiff_L2_16u_C1R, (const Ipp16u* pSrc1, int src1Step,
                                        const Ipp16u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNormDiff_L2_16u_C3R, (const Ipp16u* pSrc1, int src1Step,
                                        const Ipp16u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNormDiff_L2_16u_C4R, (const Ipp16u* pSrc1, int src1Step,
                                        const Ipp16u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNormDiff_L2_32f_C1R, (const Ipp32f* pSrc1, int src1Step,
                                        const Ipp32f* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f* pValue, IppHintAlgorithm hint))

IPPAPI(IppStatus, ippiNormDiff_L2_32f_C3R, (const Ipp32f* pSrc1, int src1Step,
                                        const Ipp32f* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3], IppHintAlgorithm hint))

IPPAPI(IppStatus, ippiNormDiff_L2_32f_C4R, (const Ipp32f* pSrc1, int src1Step,
                                        const Ipp32f* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[4], IppHintAlgorithm hint))

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

IPPAPI(IppStatus, ippiNormRel_Inf_8u_C1R, (const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNormRel_Inf_8u_C3R, (const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNormRel_Inf_8u_C4R, (const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNormRel_Inf_16s_C1R, (const Ipp16s* pSrc1, int src1Step,
                                        const Ipp16s* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNormRel_Inf_16s_C3R, (const Ipp16s* pSrc1, int src1Step,
                                        const Ipp16s* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNormRel_Inf_16s_C4R, (const Ipp16s* pSrc1, int src1Step,
                                        const Ipp16s* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNormRel_Inf_16u_C1R, (const Ipp16u* pSrc1, int src1Step,
                                        const Ipp16u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNormRel_Inf_16u_C3R, (const Ipp16u* pSrc1, int src1Step,
                                        const Ipp16u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNormRel_Inf_16u_C4R, (const Ipp16u* pSrc1, int src1Step,
                                        const Ipp16u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNormRel_Inf_32f_C1R, (const Ipp32f* pSrc1, int src1Step,
                                        const Ipp32f* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNormRel_Inf_32f_C3R, (const Ipp32f* pSrc1, int src1Step,
                                        const Ipp32f* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNormRel_Inf_32f_C4R, (const Ipp32f* pSrc1, int src1Step,
                                        const Ipp32f* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[4]))

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

IPPAPI(IppStatus, ippiNormRel_L1_8u_C1R, (const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNormRel_L1_8u_C3R, (const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNormRel_L1_8u_C4R, (const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNormRel_L1_16s_C1R, (const Ipp16s* pSrc1, int src1Step,
                                        const Ipp16s* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNormRel_L1_16s_C3R, (const Ipp16s* pSrc1, int src1Step,
                                        const Ipp16s* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNormRel_L1_16s_C4R, (const Ipp16s* pSrc1, int src1Step,
                                        const Ipp16s* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNormRel_L1_16u_C1R, (const Ipp16u* pSrc1, int src1Step,
                                        const Ipp16u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNormRel_L1_16u_C3R, (const Ipp16u* pSrc1, int src1Step,
                                        const Ipp16u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNormRel_L1_16u_C4R, (const Ipp16u* pSrc1, int src1Step,
                                        const Ipp16u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNormRel_L1_32f_C1R, (const Ipp32f* pSrc1, int src1Step,
                                        const Ipp32f* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f* pValue, IppHintAlgorithm hint))

IPPAPI(IppStatus, ippiNormRel_L1_32f_C3R, (const Ipp32f* pSrc1, int src1Step,
                                        const Ipp32f* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3], IppHintAlgorithm hint))

IPPAPI(IppStatus, ippiNormRel_L1_32f_C4R, (const Ipp32f* pSrc1, int src1Step,
                                        const Ipp32f* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[4], IppHintAlgorithm hint))

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

IPPAPI(IppStatus, ippiNormRel_L2_8u_C1R, (const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNormRel_L2_8u_C3R, (const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNormRel_L2_8u_C4R, (const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNormRel_L2_16s_C1R, (const Ipp16s* pSrc1, int src1Step,
                                        const Ipp16s* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNormRel_L2_16s_C3R, (const Ipp16s* pSrc1, int src1Step,
                                        const Ipp16s* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNormRel_L2_16s_C4R, (const Ipp16s* pSrc1, int src1Step,
                                        const Ipp16s* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNormRel_L2_16u_C1R, (const Ipp16u* pSrc1, int src1Step,
                                        const Ipp16u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f* pValue))

IPPAPI(IppStatus, ippiNormRel_L2_16u_C3R, (const Ipp16u* pSrc1, int src1Step,
                                        const Ipp16u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3]))

IPPAPI(IppStatus, ippiNormRel_L2_16u_C4R, (const Ipp16u* pSrc1, int src1Step,
                                        const Ipp16u* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[4]))

IPPAPI(IppStatus, ippiNormRel_L2_32f_C1R, (const Ipp32f* pSrc1, int src1Step,
                                        const Ipp32f* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f* pValue, IppHintAlgorithm hint))

IPPAPI(IppStatus, ippiNormRel_L2_32f_C3R, (const Ipp32f* pSrc1, int src1Step,
                                        const Ipp32f* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[3], IppHintAlgorithm hint))

IPPAPI(IppStatus, ippiNormRel_L2_32f_C4R, (const Ipp32f* pSrc1, int src1Step,
                                        const Ipp32f* pSrc2, int src2Step,
                                        IppiSize roiSize, Ipp64f value[4], IppHintAlgorithm hint))


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

IPPAPI(IppStatus, ippiSum_8u_C1R, (const Ipp8u* pSrc, int srcStep,
                                   IppiSize roiSize, Ipp64f* pSum))

IPPAPI(IppStatus, ippiSum_8u_C3R, (const Ipp8u* pSrc, int srcStep,
                                   IppiSize roiSize, Ipp64f sum[3]))

IPPAPI(IppStatus, ippiSum_8u_C4R, (const Ipp8u* pSrc, int srcStep,
                                    IppiSize roiSize, Ipp64f sum[4]))

IPPAPI(IppStatus, ippiSum_16s_C1R, (const Ipp16s* pSrc, int srcStep,
                                    IppiSize roiSize, Ipp64f* pSum))

IPPAPI(IppStatus, ippiSum_16s_C3R, (const Ipp16s* pSrc, int srcStep,
                                    IppiSize roiSize, Ipp64f sum[3]))

IPPAPI(IppStatus, ippiSum_16s_C4R, (const Ipp16s* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f sum[4]))

IPPAPI(IppStatus, ippiSum_16u_C1R, (const Ipp16u* pSrc, int srcStep,
                                    IppiSize roiSize, Ipp64f* pSum))

IPPAPI(IppStatus, ippiSum_16u_C3R, (const Ipp16u* pSrc, int srcStep,
                                    IppiSize roiSize, Ipp64f sum[3]))

IPPAPI(IppStatus, ippiSum_16u_C4R, (const Ipp16u* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f sum[4]))

IPPAPI(IppStatus, ippiSum_32f_C1R, (const Ipp32f* pSrc, int srcStep,
                                    IppiSize roiSize, Ipp64f* pSum, IppHintAlgorithm hint))

IPPAPI(IppStatus, ippiSum_32f_C3R, (const Ipp32f* pSrc, int srcStep,
                                    IppiSize roiSize, Ipp64f sum[3], IppHintAlgorithm hint))

IPPAPI(IppStatus, ippiSum_32f_C4R, (const Ipp32f* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f sum[4], IppHintAlgorithm hint))

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

IPPAPI(IppStatus, ippiMean_8u_C1R, (const Ipp8u* pSrc, int srcStep,
                                   IppiSize roiSize, Ipp64f* pMean))

IPPAPI(IppStatus, ippiMean_8u_C3R, (const Ipp8u* pSrc, int srcStep,
                                   IppiSize roiSize, Ipp64f mean[3]))

IPPAPI(IppStatus, ippiMean_8u_C4R, (const Ipp8u* pSrc, int srcStep,
                                    IppiSize roiSize, Ipp64f mean[4]))

IPPAPI(IppStatus, ippiMean_16s_C1R, (const Ipp16s* pSrc, int srcStep,
                                    IppiSize roiSize, Ipp64f* pMean))

IPPAPI(IppStatus, ippiMean_16s_C3R, (const Ipp16s* pSrc, int srcStep,
                                    IppiSize roiSize, Ipp64f mean[3]))

IPPAPI(IppStatus, ippiMean_16s_C4R, (const Ipp16s* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f mean[4]))

IPPAPI(IppStatus, ippiMean_16u_C1R, (const Ipp16u* pSrc, int srcStep,
                                    IppiSize roiSize, Ipp64f* pMean))

IPPAPI(IppStatus, ippiMean_16u_C3R, (const Ipp16u* pSrc, int srcStep,
                                    IppiSize roiSize, Ipp64f mean[3]))

IPPAPI(IppStatus, ippiMean_16u_C4R, (const Ipp16u* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f mean[4]))

IPPAPI(IppStatus, ippiMean_32f_C1R, (const Ipp32f* pSrc, int srcStep,
                                    IppiSize roiSize, Ipp64f* pMean, IppHintAlgorithm hint))

IPPAPI(IppStatus, ippiMean_32f_C3R, (const Ipp32f* pSrc, int srcStep,
                                    IppiSize roiSize, Ipp64f mean[3], IppHintAlgorithm hint))

IPPAPI(IppStatus, ippiMean_32f_C4R, (const Ipp32f* pSrc, int srcStep,
                                     IppiSize roiSize, Ipp64f mean[4], IppHintAlgorithm hint))


/* /////////////////////////////////////////////////////////////////////////////
//  Names:   ippiQualityIndex
//
//  Purpose: ippiQualityIndex() function calculates the Universal Image Quality
//           Index. Instead of traditional error summation methods, the
//           proposed index is designed by modeling any image distortion as a
//           combination of three factors: loss of correlation, luminance
//           distortion, and contrast distortion. The dynamic range of the index
//           is [-1.0, 1.0].
//
//  Parameters:
//    pSrc1          - Pointer to the first source image ROI.
//    src1Step       - Distance, in bytes, between the starting points of consecutive lines in the first source image.
//    pSrc2          - Pointer to the second source image ROI.
//    src2Step       - Distance, in bytes, between the starting points of consecutive lines in the second source image.
//    roiSize        - Size, in pixels, of the 1st and 2nd source images.
//    pQualityIndex  - Pointer where to store the calculated Universal Image Quality Index.
//    pBuffer        - Pointer to the buffer for internal calculations. Size of the buffer is calculated by ippiQualityIndexGetBufferSize.
//
//  Returns:
//    ippStsNoErr       - OK.
//    ippStsNullPtrErr  - Error when any of the specified pointers is NULL.
//    ippStsSizeErr     - Error when the roiSize has a zero or negative value.
//    ippStsStepErr     - Error when the src1Step or src2Step is less than or equal to zero.
*/
IPPAPI( IppStatus, ippiQualityIndex_8u32f_C1R, (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, IppiSize roiSize, Ipp32f pQualityIndex[1], Ipp8u *pBuffer))
IPPAPI( IppStatus, ippiQualityIndex_8u32f_C3R, (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, IppiSize roiSize, Ipp32f pQualityIndex[3], Ipp8u *pBuffer))
IPPAPI( IppStatus, ippiQualityIndex_8u32f_AC4R,(const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, IppiSize roiSize, Ipp32f pQualityIndex[3], Ipp8u *pBuffer))

IPPAPI( IppStatus, ippiQualityIndex_16u32f_C1R, (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, IppiSize roiSize, Ipp32f pQualityIndex[1], Ipp8u *pBuffer))
IPPAPI( IppStatus, ippiQualityIndex_16u32f_C3R, (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, IppiSize roiSize, Ipp32f pQualityIndex[3], Ipp8u *pBuffer))
IPPAPI( IppStatus, ippiQualityIndex_16u32f_AC4R,(const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, IppiSize roiSize, Ipp32f pQualityIndex[3], Ipp8u *pBuffer))

IPPAPI( IppStatus, ippiQualityIndex_32f_C1R, (const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2, int src2Step, IppiSize roiSize, Ipp32f pQualityIndex[1], Ipp8u *pBuffer))
IPPAPI( IppStatus, ippiQualityIndex_32f_C3R, (const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2, int src2Step, IppiSize roiSize, Ipp32f pQualityIndex[3], Ipp8u *pBuffer))
IPPAPI( IppStatus, ippiQualityIndex_32f_AC4R,(const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2, int src2Step, IppiSize roiSize, Ipp32f pQualityIndex[3], Ipp8u *pBuffer))


/* /////////////////////////////////////////////////////////////////////////////
//  Names:     ippiQualityIndexGetBufferSize
//  Purpose:   Get the size (in bytes) of the buffer for ippiQualityIndex.
//  Parameters:
//    srcType     - Intel(R) IPP data type name of the source images. Possible values are ipp8u, ipp16u or ipp32f.
//    ippChan     - Intel(R) IPP channels name of of the source images. Possible values are ippC1, ippC3 or ippAC4.
//    roiSize     - Size, in pixels, of the source images.
//    pBufferSize - Pointer to the calculated buffer size (in bytes).
//  Return:
//    ippStsNoErr       - OK.
//    ippStsNullPtrErr  - Error when any of the specified pointers is NULL.
//    ippStsSizeErr     - Error when the roiSize has a zero or negative value.
//    ippStsDataTypeErr - Error when the srcType has an illegal value.
//    ippStsChannelErr  - Error when the ippChan has an illegal value.
*/
IPPAPI( IppStatus, ippiQualityIndexGetBufferSize,(IppDataType srcType, IppChannels ippChan, IppiSize roiSize, int *pBufferSize))



/* /////////////////////////////////////////////////////////////////////////////
//  Names:     ippiHistogramGetBufferSize
//  Purpose:   Get the sizes (in bytes) of the spec and the buffer for ippiHistogram_.
//  Parameters:
//    dataType    - Data type for source image. Possible values are ipp8u, ipp16u, ipp16s or ipp32f.
//    roiSize     - Size, in pixels, of the source image.
//    nLevels     - Number of levels values, separate for each channel.
//    numChannels - Number of image channels. Possible values are 1, 3, or 4.
//    uniform     - Type of levels distribution: 0 - with random step, 1 - with uniform step.
//    pSpecSize   - Pointer to the calculated spec size (in bytes).
//    pBufferSize - Pointer to the calculated buffer size (in bytes).
//  Return:
//    ippStsNoErr             - OK.
//    ippStsNullPtrErr        - Error when any of the specified pointers is NULL.
//    ippStsSizeErr           - Error when the roiSize has a zero or negative value.
//    ippStsHistoNofLevelsErr - Error when the number of levels is less than 2.
//    ippStsNumChannelsErr    - Error when the numChannels value differs from 1, 3, or 4.
//    ippStsDataTypeErr       - Error when the dataType value differs from the ipp8u, ipp16u, ipp16s or ipp32f.
*/
IPPAPI(IppStatus, ippiHistogramGetBufferSize, (IppDataType dataType, IppiSize roiSize, const int nLevels[], int numChannels, int uniform, int* pSpecSize, int* pBufferSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:     ippiHistogramInit, ippiHistogramUniformInit
//  Purpose:   Initializes the Spec for ippiHistogram.
//  Parameters:
//    dataType    - Data type for source image. Possible values are ipp8u, ipp16u, ipp16s or ipp32f.
//    pLevels     - Pointer to the array of level values. In case of multi-channel data, pLevels is an array of pointers to the level values array for each channel.
//    lowerLevel  - The lower levels for uniform histogram, separate for each channel.
//    upperLevel  - The upper levels for uniform histogram, separate for each channel.
//    nLevels     - Number of levels values, separate for each channel.
//    numChannels - Number of image channels. Possible values are 1, 3, or 4.
//    pSpec       - Pointer to the spec object.
//  Return:
//    ippStsNoErr             - OK.
//    ippStsNullPtrErr        - Error when any of the specified pointers is NULL.
//    ippStsNumChannelsErr    - Error when the numChannels value differs from 1, 3, or 4.
//    ippStsHistoNofLevelsErr - Error when the number of levels is less than 2.
//    ippStsRangeErr          - Error when consecutive pLevels values don't satisfy the condition: pLevel[i] < pLevel[i+1].
//    ippStsDataTypeErr       - Error when the dataType value differs from the ipp8u, ipp16u, ipp16s or ipp32f.
//    ippStsSizeWrn           - Warning ( in case of uniform histogram of integer data type) when rated level step is less than 1.
*/
IPPAPI(IppStatus, ippiHistogramInit, (IppDataType dataType, const Ipp32f *pLevels[], int nLevels[], int numChannels, IppiHistogramSpec* pSpec))
IPPAPI(IppStatus, ippiHistogramUniformInit, (IppDataType dataType, Ipp32f lowerLevel[], Ipp32f upperLevel[], int nLevels[], int numChannels, IppiHistogramSpec* pSpec))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiHistogramGetLevels
//  Purpose:   Returns levels arrays stored in the pSpec object.
//  Parameters:
//    pSpec       - Pointer to the spec object.
//    pLevels     - Pointer to the array of level values. In case of multi-channel data, pLevels is an array of pointers to the level values array for each channel.
//  Return:
//    ippStsNoErr             - OK.
//    ippStsNullPtrErr        - Error when any of the specified pointers is NULL.
//    ippStsBadArgErr         - Error when pSpec object doesn`t initialized.
*/
IPPAPI(IppStatus, ippiHistogramGetLevels, (const IppiHistogramSpec* pSpec, Ipp32f *pLevels[]))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:         ippiHistogram
//  Purpose:      Computes the intensity histogram of an image.
//  Parameters:
//    pSrc        - Pointer to the source image ROI.
//    srcStep     - Distance, in bytes, between the starting points of consecutive lines in the source image.
//    roiSize     - Size, in pixels, of the source image.
//    pHist       - Pointer to the computed histogram. In case of multi-channel data, pHist is an array of pointers to the histogram for each channel.
//    pSpec       - Pointer to the spec.
//    pBuffer     - Pointer to the buffer for internal calculations.
//  Returns:
//    ippStsNoErr             - OK.
//    ippStsNullPtrErr        - Error when any of the specified pointers is NULL.
//    ippStsSizeErr           - Error when the roiSize has a zero or negative value.
//    ippStsStepErr           - Error when the srcStep is less than roiSize.width*sizeof(*pSrc)*nChannels.
//    ippStsBadArgErr         - Error when pSpec object doesn`t initialized.
*/
IPPAPI(IppStatus, ippiHistogram_8u_C1R , (const Ipp8u*  pSrc, int srcStep, IppiSize roiSize, Ipp32u* pHist   , const IppiHistogramSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiHistogram_8u_C3R , (const Ipp8u*  pSrc, int srcStep, IppiSize roiSize, Ipp32u* pHist[3], const IppiHistogramSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiHistogram_8u_C4R , (const Ipp8u*  pSrc, int srcStep, IppiSize roiSize, Ipp32u* pHist[4], const IppiHistogramSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiHistogram_16s_C1R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp32u* pHist   , const IppiHistogramSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiHistogram_16s_C3R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp32u* pHist[3], const IppiHistogramSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiHistogram_16s_C4R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp32u* pHist[4], const IppiHistogramSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiHistogram_16u_C1R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp32u* pHist   , const IppiHistogramSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiHistogram_16u_C3R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp32u* pHist[3], const IppiHistogramSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiHistogram_16u_C4R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp32u* pHist[4], const IppiHistogramSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiHistogram_32f_C1R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32u* pHist   , const IppiHistogramSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiHistogram_32f_C3R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32u* pHist[3], const IppiHistogramSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiHistogram_32f_C4R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32u* pHist[4], const IppiHistogramSpec* pSpec, Ipp8u* pBuffer))


/* /////////////////////////////////////////////////////////////////////////////
// Name:          ippiLUT
// Purpose:       Performs intensity transformation of an image
//                using lookup table (LUT) without interpolation or
//                using lookup table (LUT) with linear interpolation or
//                using lookup table (LUT) with cubic interpolation
//  Parameters:
//    pSrc        - Pointer to the source image.
//    srcStep     - Distances, in bytes, between the starting points of consecutive lines in the source images.
//    pDst        - Pointer to the destination image.
//    dstStep     - Distance, in bytes, between the starting points of consecutive lines in the destination image.
//    pSrcDst     - Pointer to the source/destination image (inplace case).
//    srcDstStep  - Distance, in bytes, between the starting points of consecutive lines in the source/destination image (inplace case).
//    roiSize     - Size, in pixels, of the ROI.
//    pSpec       - Pointer to the LUT spec structure.
//  Returns:
//    ippStsNoErr      - OK.
//    ippStsNullPtrErr - Error when any of the specified pointers is NULL.
//    ippStsSizeErr    - Error when roiSize has a field with value less than 1.
//    ippStsStepErr    - Error when srcStep, dstStep  or srcDstStep has a zero or negative value.
//    ippStsBadArgErr  - Error when pSpec initialized incorect.
*/
IPPAPI(IppStatus, ippiLUT_8u_C1R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_8u_C3R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_8u_C4R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_8u_AC4R,(const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))

IPPAPI(IppStatus, ippiLUT_8u_C1IR ,(Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_8u_C3IR ,(Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_8u_C4IR ,(Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_8u_AC4IR,(Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))

IPPAPI(IppStatus, ippiLUT_16u_C1R ,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_16u_C3R ,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_16u_C4R ,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_16u_AC4R,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))

IPPAPI(IppStatus, ippiLUT_16u_C1IR ,(Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_16u_C3IR ,(Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_16u_C4IR ,(Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_16u_AC4IR,(Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))

IPPAPI(IppStatus, ippiLUT_16s_C1R ,(const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_16s_C3R ,(const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_16s_C4R ,(const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_16s_AC4R,(const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))

IPPAPI(IppStatus, ippiLUT_16s_C1IR ,(Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_16s_C3IR ,(Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_16s_C4IR ,(Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_16s_AC4IR,(Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))

IPPAPI(IppStatus, ippiLUT_32f_C1R ,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_32f_C3R ,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_32f_C4R ,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_32f_AC4R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))

IPPAPI(IppStatus, ippiLUT_32f_C1IR ,(Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_32f_C3IR ,(Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_32f_C4IR ,(Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_32f_AC4IR,(Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize, IppiLUT_Spec* pSpec))


/* /////////////////////////////////////////////////////////////////////////////
// Name:          ippiLUT_GetSize
// Purpose:       Gets the size (in bytes) of the spec buffer for ippiLUT.
//  Parameters:
//    interp         - Interpolation type (ippCubic or ippLinear or ippNearest).
//    dataType       - Intel(R) IPP data type name of the images. Possible values are ipp8u, ipp16u, ipp16s or ipp32f.
//    numChannels    - Intel(R) IPP channels name of of the images. Possible values are ippC1, ippC3, ippC4 or ippAC4.
//    roiSize        - Size, in pixels, of the destination ROI.
//    nLevels        - Number of levels, separate for each channel.
//    pSpecSize      - Pointer to the calculated spec size (in bytes).
//  Returns:
//    ippStsNoErr            - OK.
//    ippStsNullPtrErr       - Error when any of the specified pointers is NULL.
//    ippStsSizeErr          - Error when roiSize has a field with value less than 1.
//    ippStsDataTypeErr      - Error when the srcType has an illegal value.
//    ippStsChannelErr       - Error when the ippChan has an illegal value.
//    ippStsInterpolationErr - Error when the interpolationType has an illegal value.
*/
IPPAPI(IppStatus, ippiLUT_GetSize, (IppiInterpolationType interp, IppDataType dataType, IppChannels ippChan, IppiSize roiSize, const int nLevels[], int* pSpecSize))

/* /////////////////////////////////////////////////////////////////////////////
// Name:          ippiLUT_Init
// Purpose:       Initializes the spec for ippiLUT.
//  Parameters:
//    interp         - Interpolation type (ippCubic or ippLinear or ippNearest).
//    numChannels    - Intel(R) IPP channels name of of the images. Possible values are ippC1, ippC3, ippC4 or ippAC4.
//    roiSize        - Size, in pixels, of the destination ROI.
//    pValues        - Ppointer to the array of intensity values, separate for each channel.
//    pLevels        - Pointer to the array of level values, separate for each channel.
//    nLevels        - Number of levels, separate for each channel.
//    pSpec          - Pointer to the LUT spec structure.
//  Returns:
//    ippStsNoErr            - OK.
//    ippStsNullPtrErr       - Error when any of the specified pointers is NULL.
//    ippStsSizeErr          - Error when roiSize has a field with value less than 1.
//    ippStsChannelErr       - Error when the ippChan has an illegal value.
//    ippStsLUTNofLevelsErr  - Error when the number of levels is less 2.
//    ippStsInterpolationErr - Error when the interpolationType has an illegal value.
*/
IPPAPI(IppStatus, ippiLUT_Init_8u,  (IppiInterpolationType interp, IppChannels ippChan, IppiSize roiSize, const Ipp32s* pValues[], const Ipp32s* pLevels[], int nLevels[], IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_Init_16u, (IppiInterpolationType interp, IppChannels ippChan, IppiSize roiSize, const Ipp32s* pValues[], const Ipp32s* pLevels[], int nLevels[], IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_Init_16s, (IppiInterpolationType interp, IppChannels ippChan, IppiSize roiSize, const Ipp32s* pValues[], const Ipp32s* pLevels[], int nLevels[], IppiLUT_Spec* pSpec))
IPPAPI(IppStatus, ippiLUT_Init_32f, (IppiInterpolationType interp, IppChannels ippChan, IppiSize roiSize, const Ipp32f* pValues[], const Ipp32f* pLevels[], int nLevels[], IppiLUT_Spec* pSpec))



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
IPPAPI(IppStatus, ippiLUTPalette_16u32u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp32u* pDst, int dstStep,
       IppiSize roiSize, const Ipp32u* pTable, int nBitSize))
IPPAPI(IppStatus, ippiLUTPalette_16u24u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
       IppiSize roiSize, const Ipp8u* pTable, int nBitSize))
IPPAPI(IppStatus, ippiLUTPalette_16u8u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
       IppiSize roiSize, const Ipp8u* pTable, int nBitSize))
IPPAPI(IppStatus, ippiLUTPalette_8u32u_C1R, (const Ipp8u* pSrc, int srcStep, Ipp32u* pDst, int dstStep,
       IppiSize roiSize, const Ipp32u* pTable, int nBitSize))
IPPAPI(IppStatus, ippiLUTPalette_8u24u_C1R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
       IppiSize roiSize, const Ipp8u* pTable, int nBitSize))
IPPAPI(IppStatus, ippiLUTPalette_8u_C1R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
       IppiSize roiSize, const Ipp8u* pTable, int nBitSize))
IPPAPI(IppStatus, ippiLUTPalette_16u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
       IppiSize roiSize, const Ipp16u* pTable, int nBitSize))
IPPAPI(IppStatus, ippiLUTPalette_8u_C3R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
       IppiSize roiSize, const Ipp8u* const pTable[3], int nBitSize))
IPPAPI(IppStatus, ippiLUTPalette_16u_C3R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
       IppiSize roiSize, const Ipp16u* const pTable[3], int nBitSize))
IPPAPI(IppStatus, ippiLUTPalette_8u_C4R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
       IppiSize roiSize, const Ipp8u* const pTable[4], int nBitSize))
IPPAPI(IppStatus, ippiLUTPalette_16u_C4R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
       IppiSize roiSize, const Ipp16u* const pTable[4], int nBitSize))
IPPAPI(IppStatus, ippiLUTPalette_8u_AC4R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
       IppiSize roiSize, const Ipp8u* const pTable[3], int nBitSize))
IPPAPI(IppStatus, ippiLUTPalette_16u_AC4R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
       IppiSize roiSize, const Ipp16u* const pTable[3], int nBitSize))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:                ippiCountInRange
//
//  Purpose:  Computes the number of pixels with intensity values within the given range
//
//  Returns:             IppStatus
//      ippStsNoErr       No errors
//      ippStsNullPtrErr  pSrc == NULL
//      ippStsStepErr     srcStep is less than or equal to zero
//      ippStsSizeErr     roiSize has a field with zero or negative value
//      ippStsRangeErr    lowerBound is greater than upperBound
//
//  Parameters:
//      pSrc             Pointer to the source buffer
//      roiSize          Size of the source ROI
//      srcStep          Step through the source image buffer
//      counts           Number of pixels within the given intensity range
//      lowerBound       Lower limit of the range
//      upperBound       Upper limit of the range
*/

IPPAPI(IppStatus, ippiCountInRange_8u_C1R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize,
                                            int* counts, Ipp8u lowerBound, Ipp8u upperBound))
IPPAPI(IppStatus, ippiCountInRange_8u_C3R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize,
                                            int counts[3], Ipp8u lowerBound[3], Ipp8u upperBound[3]))
IPPAPI(IppStatus, ippiCountInRange_8u_AC4R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize,
                                            int counts[3], Ipp8u lowerBound[3], Ipp8u upperBound[3]))
IPPAPI(IppStatus, ippiCountInRange_32f_C1R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize,
                                            int* counts, Ipp32f lowerBound, Ipp32f upperBound))
IPPAPI(IppStatus, ippiCountInRange_32f_C3R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize,
                                            int counts[3], Ipp32f lowerBound[3], Ipp32f upperBound[3]))
IPPAPI(IppStatus, ippiCountInRange_32f_AC4R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize,
                                            int counts[3], Ipp32f lowerBound[3], Ipp32f upperBound[3]))


/* ///////////////////////////////////////////////////////////////////////////
//             Non-linear Filters
/////////////////////////////////////////////////////////////////////////// */



/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiFilterMedianGetBufferSize_32f

//  Purpose:  Get size of internal buffer for median filter
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  bufferSize is NULL
//   ippStsSizeErr     dstRoiSize has a field with zero or negative value
//   ippStsMaskSizeErr maskSize has a field with zero, negative, or even value
//   ippStsNumChannelsErr number of channels is not 3 or 4
//  Parameters:
//   dstRoiSize   Size of the destination ROI
//   maskSize     Size of the mask in pixels
//   nChannels     Number of channels
//   bufferSize  reference to size buffer
*/
IPPAPI(IppStatus,ippiFilterMedianGetBufferSize_32f,( IppiSize dstRoiSize,
       IppiSize maskSize, Ipp32u nChannels, Ipp32u* bufferSize))
IPPAPI(IppStatus,ippiFilterMedianGetBufferSize_64f,( IppiSize dstRoiSize,
       IppiSize maskSize, Ipp32u nChannels, Ipp32u* bufferSize))
/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiFilterMedian_32f_C3R
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

IPPAPI(IppStatus,ippiFilterMedian_32f_C3R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor, Ipp8u* pBuffer))
IPPAPI(IppStatus,ippiFilterMedian_32f_C4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor, Ipp8u* pBuffer))
IPPAPI(IppStatus,ippiFilterMedian_64f_C1R,(const Ipp64f* pSrc, int srcStep,
       Ipp64f* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
       IppiPoint anchor, Ipp8u* pBuffer))
/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiFilterMedianCross_8u_C1R
//              ippiFilterMedianCross_8u_C3R
//              ippiFilterMedianCross_8u_AC4R
//              ippiFilterMedianCross_16s_C1R
//              ippiFilterMedianCross_16s_C3R
//              ippiFilterMedianCross_16s_AC4R
//              ippiFilterMedianCross_16u_C1R
//              ippiFilterMedianCross_16u_C3R
//              ippiFilterMedianCross_16u_AC4R
//  Purpose:  Filters an image using a cross median filter
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
IPPAPI(IppStatus,ippiFilterMedianCross_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
IPPAPI(IppStatus,ippiFilterMedianCross_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
IPPAPI(IppStatus,ippiFilterMedianCross_8u_AC4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
IPPAPI(IppStatus,ippiFilterMedianCross_16s_C1R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
IPPAPI(IppStatus,ippiFilterMedianCross_16s_C3R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
IPPAPI(IppStatus,ippiFilterMedianCross_16s_AC4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
IPPAPI(IppStatus,ippiFilterMedianCross_16u_C1R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
IPPAPI(IppStatus,ippiFilterMedianCross_16u_C3R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
IPPAPI(IppStatus,ippiFilterMedianCross_16u_AC4R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiFilterMedianColor_8u_C3R
//              ippiFilterMedianColor_8u_AC4R
//              ippiFilterMedianColor_16s_C3R
//              ippiFilterMedianColor_16s_AC4R
//              ippiFilterMedianColor_32f_C3R
//              ippiFilterMedianColor_32f_AC4R
//  Purpose:  Filters an image using a box color median filter
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
IPPAPI(IppStatus,ippiFilterMedianColor_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
IPPAPI(IppStatus,ippiFilterMedianColor_8u_AC4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
IPPAPI(IppStatus,ippiFilterMedianColor_16s_C3R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
IPPAPI(IppStatus,ippiFilterMedianColor_16s_AC4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
IPPAPI(IppStatus,ippiFilterMedianColor_32f_C3R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))
IPPAPI(IppStatus,ippiFilterMedianColor_32f_AC4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiFilterMedianWeightedCenter3x3_8u_C1R

//  Purpose:  Filter an image using a median filter with kernel size 3x3 and
//            enlarged weight of central pixel
//  Returns:
//   ippStsNoErr            OK
//   ippStsNullPtrErr       pSrc or pDst is NULL
//   ippStsSizeErr          dstRoiSize has a field with zero or negative value
//   ippStsStepErr          srcStep or dstStep has zero or negative value
//   ippStsWeightErr        weight of central Pixel has zero or negative value
//   ippStsEvenMedianWeight weight of central Pixel has even value
//
//  Parameters:
//   pSrc        Pointer to the source image
//   srcStep     Step through the source image
//   pDst        Pointer to the destination image
//   dstStep     Step through the destination image
//   dstRoiSize  Size of the destination ROI
//   weight      Weight of central pixel
*/
IPPAPI(IppStatus,ippiFilterMedianWeightedCenter3x3_8u_C1R,(const Ipp8u* pSrc,
       int srcStep, Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, int weight))



/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiFilterMedianBorderGetBufferSize
//
//  Purpose:            Computes the size of the external buffer for median filter with border
//
//  Parameters:
//   roiSize            Size of destination ROI in pixels.
//   maskSize           Size of filter mask.
//   dataType           Data type of the source an desination images.
//   numChannels        Number of channels in the images. Possible values are 1, 3 or 4.
//   pBufferSize        Pointer to the size (in bytes) of the external work buffer.
//
//  Return Values:
//   ippStsNoErr        Indicates no error.
//   ippStsNullPtrErr   Indicates an error when pBufferSize is NULL.
//   ippStsSizeErr      Indicates an error when roiSize has a field with negative or zero value.
//   ippStsMaskSizeErr  Indicates an error when maskSize has a field with negative, zero or even value.
//   ippStsDataTypeErr  Indicates an error when dataType has an illegal value.
//   ippStsNumChannelsErr Indicates an error when numChannels has an illegal value.
*/
IPPAPI(IppStatus, ippiFilterMedianBorderGetBufferSize,(IppiSize dstRoiSize, IppiSize maskSize,
    IppDataType dataType, int numChannels, int* pBufferSize))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiFilterMedianBorder_8u_C1R
//                      ippiFilterMedianBorder_16s_C1R
//                      ippiFilterMedianBorder_16u_C1R
//                      ippiFilterMedianBorder_32f_C1R
//  Purpose:            Perform median filtering of an image with border
//
//  Parameters:
//   pSrc               Pointer to the source image ROI.
//   srcStep            Distance in bytes between starting points of consecutive lines in the sorce image.
//   pDst               Pointer to the destination image ROI.
//   dstStep            Distance in bytes between starting points of consecutive lines in the destination image.
//   dstRoiSize         Size of destination ROI in pixels.
//   maskSize           Size of filter mask.
//   borderType         Type of border.
//   borderValue        Constant value to assign to pixels of the constant border. This parameter is applicable
//                      only to the ippBorderConst border type.
//   pBorderValue       Pointer to constant value to assign to pixels of the constant border. This parameter is applicable
//                      only to the ippBorderConst border type.
//   pBuffer            Pointer to the work buffer.
//
//  Return Values:
//   ippStsNoErr        Indicates no error.
//   ippStsNullPtrErr   Indicates an error when pSrc, pDst or pBufferSize is NULL.
//   ippStsSizeErr      Indicates an error when roiSize has a field with negative or zero value.
//   ippStsMaskSizeErr  Indicates an error when maskSize has a field with negative, zero or even value.
//   ippStsNotEvenStepErr Indicated an error when one of the step values is not divisible by 4
//                      for floating-point images, or by 2 for short-integer images.
//   ippStsBorderErr    Indicates an error when borderType has illegal value.
*/

IPPAPI(IppStatus, ippiFilterMedianBorder_8u_C1R, (const Ipp8u* pSrc, int srcStep,
    Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, Ipp8u borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMedianBorder_16s_C1R, (const Ipp16s* pSrc, int srcStep,
    Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, Ipp16s borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMedianBorder_16u_C1R, (const Ipp16u* pSrc, int srcStep,
    Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, Ipp16u borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMedianBorder_32f_C1R, (const Ipp32f* pSrc, int srcStep,
    Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, Ipp32f borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterMedianBorder_8u_C3R, (const Ipp8u* pSrc, int srcStep,
    Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp8u pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMedianBorder_16s_C3R, (const Ipp16s* pSrc, int srcStep,
    Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp16s pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMedianBorder_16u_C3R, (const Ipp16u* pSrc, int srcStep,
    Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp16u pBorderValue[3], Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterMedianBorder_8u_AC4R, (const Ipp8u* pSrc, int srcStep,
    Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp8u pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMedianBorder_16s_AC4R, (const Ipp16s* pSrc, int srcStep,
    Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp16s pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMedianBorder_16u_AC4R, (const Ipp16u* pSrc, int srcStep,
    Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp16u pBorderValue[3], Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterMedianBorder_8u_C4R, (const Ipp8u* pSrc, int srcStep,
    Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp8u pBorderValue[4], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMedianBorder_16s_C4R, (const Ipp16s* pSrc, int srcStep,
    Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp16s pBorderValue[4], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMedianBorder_16u_C4R, (const Ipp16u* pSrc, int srcStep,
    Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp16u pBorderValue[4], Ipp8u* pBuffer))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiFilterMaxBorderGetBufferSize
//                      ippiFilterMinBorderGetBufferSize
//
//  Purpose:            Computes the size of the external buffer for median filter with border
//
//  Parameters:
//   roiSize            Size of destination ROI in pixels.
//   maskSize           Size of mask.
//   dataType           data type of source and destination images.
//   numChannels        Number of channels in the images. Possible values is 1.
//   pBufferSize        Pointer to the size (in bytes) of the external work buffer.
//
//  Return Values:
//   ippStsNoErr        Indicates no error.
//   ippStsNullPtrErr   Indicates an error when pBufferSize is NULL.
//   ippStsSizeErr      Indicates an error when roiSize is negative, or equal to zero.
//   ippStsMaskSizeErr  Indicates an error when maskSize is negative, or equal to zero.
//   ippStsDataTypeErr  Indicates an error when dataType has an illegal value.
//   ippStsNumChannelsErr Indicates an error when numChannels has an illegal value.
*/
IPPAPI(IppStatus, ippiFilterMaxBorderGetBufferSize,(IppiSize dstRoiSize, IppiSize maskSize,
    IppDataType dataType, int numChannels, int* pBufferSize))
IPPAPI(IppStatus, ippiFilterMinBorderGetBufferSize,(IppiSize dstRoiSize, IppiSize maskSize,
    IppDataType dataType, int numChannels, int* pBufferSize))


/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiFilterMaxBorder_8u_C1R
//              ippiFilterMaxBorder_8u_C3R
//              ippiFilterMaxBorder_8u_AC4R
//              ippiFilterMaxBorder_8u_C4R
//              ippiFilterMaxBorder_16s_C1R
//              ippiFilterMaxBorder_16s_C3R
//              ippiFilterMaxBorder_16s_AC4R
//              ippiFilterMaxBorder_16s_C4R
//              ippiFilterMaxBorder_16u_C1R
//              ippiFilterMaxBorder_16u_C3R
//              ippiFilterMaxBorder_16u_AC4R
//              ippiFilterMaxBorder_16u_C4R
//              ippiFilterMaxBorder_32f_C1R
//              ippiFilterMaxBorder_32f_C3R
//              ippiFilterMaxBorder_32f_AC4R
//              ippiFilterMaxBorder_32f_C4R
//              ippiFilterMinBorder_8u_C1R
//              ippiFilterMinBorder_8u_C3R
//              ippiFilterMinBorder_8u_AC4R
//              ippiFilterMinBorder_8u_C4R
//              ippiFilterMinBorder_16s_C1R
//              ippiFilterMinBorder_16s_C3R
//              ippiFilterMinBorder_16s_AC4R
//              ippiFilterMinBorder_16s_C4R
//              ippiFilterMinBorder_16u_C1R
//              ippiFilterMinBorder_16u_C3R
//              ippiFilterMinBorder_16u_AC4R
//              ippiFilterMinBorder_16u_C4R
//              ippiFilterMinBorder_32f_C1R
//              ippiFilterMinBorder_32f_C3R
//              ippiFilterMinBorder_32f_AC4R
//              ippiFilterMinBorder_32f_C4R
//
// Purpose:    Max and Min Filter with Border
// Parameters:
//   pSrc               Pointer to the source image ROI.
//   srcStep            Distance in bytes between starting points of consecutive lines in the sorce image.
//   pDst               Pointer to the destination image ROI.
//   dstStep            Distance in bytes between starting points of consecutive lines in the destination image.
//   dstRoiSize         Size of destination ROI in pixels.
//   maskSize           Size of mask.
//   borderType         Type of border.
//   borderValue        Constant value to assign to pixels of the constant border. This parameter is applicable
//                      only to the ippBorderConst border type.
//   pBorderValue       Pointer to constant value to assign to pixels of the constant border. This parameter is applicable
//                      only to the ippBorderConst border type.
//   pBuffer            Pointer to the work buffer.
//
//  Return Values:
//   ippStsNoErr        Indicates no error.
//   ippStsNullPtrErr   Indicates an error when pBuffer is NULL while it must be no NULL.
//   ippStsSizeErr      Indicates an error when roiSize is negative, or equal to zero.
//   ippStsStepErr      Indicates an error when srcStep or dstStep is negative, or equal to zero.
//   ippStsBorderErr    Indicates an error when borderType has illegal value.
*/
IPPAPI(IppStatus, ippiFilterMaxBorder_8u_C1R, (const Ipp8u* pSrc, int srcStep,
    Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, Ipp8u borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMaxBorder_8u_C3R, (const Ipp8u* pSrc, int srcStep,
    Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp8u pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMaxBorder_8u_AC4R, (const Ipp8u* pSrc, int srcStep,
    Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp8u pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMaxBorder_8u_C4R, (const Ipp8u* pSrc, int srcStep,
    Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp8u pBorderValue[4], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMaxBorder_16s_C1R, (const Ipp16s* pSrc, int srcStep,
    Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, Ipp16s borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMaxBorder_16s_C3R, (const Ipp16s* pSrc, int srcStep,
    Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp16s pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMaxBorder_16s_AC4R, (const Ipp16s* pSrc, int srcStep,
    Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp16s pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMaxBorder_16s_C4R, (const Ipp16s* pSrc, int srcStep,
    Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp16s pBorderValue[4], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMaxBorder_16u_C1R, (const Ipp16u* pSrc, int srcStep,
    Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, Ipp16u borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMaxBorder_16u_C3R, (const Ipp16u* pSrc, int srcStep,
    Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp16u pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMaxBorder_16u_AC4R, (const Ipp16u* pSrc, int srcStep,
    Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp16u pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMaxBorder_16u_C4R, (const Ipp16u* pSrc, int srcStep,
    Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp16u pBorderValue[4], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMaxBorder_32f_C1R, (const Ipp32f* pSrc, int srcStep,
    Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, Ipp32f borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMaxBorder_32f_C3R, (const Ipp32f* pSrc, int srcStep,
    Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp32f pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMaxBorder_32f_AC4R, (const Ipp32f* pSrc, int srcStep,
    Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp32f pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMaxBorder_32f_C4R, (const Ipp32f* pSrc, int srcStep,
    Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp32f pBorderValue[4], Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterMinBorder_8u_C1R, (const Ipp8u* pSrc, int srcStep,
    Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, Ipp8u borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMinBorder_8u_C3R, (const Ipp8u* pSrc, int srcStep,
    Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp8u pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMinBorder_8u_AC4R, (const Ipp8u* pSrc, int srcStep,
    Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp8u pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMinBorder_8u_C4R, (const Ipp8u* pSrc, int srcStep,
    Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp8u pBorderValue[4], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMinBorder_16s_C1R, (const Ipp16s* pSrc, int srcStep,
    Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, Ipp16s borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMinBorder_16s_C3R, (const Ipp16s* pSrc, int srcStep,
    Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp16s pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMinBorder_16s_AC4R, (const Ipp16s* pSrc, int srcStep,
    Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp16s pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMinBorder_16s_C4R, (const Ipp16s* pSrc, int srcStep,
    Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp16s pBorderValue[4], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMinBorder_16u_C1R, (const Ipp16u* pSrc, int srcStep,
    Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, Ipp16u borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMinBorder_16u_C3R, (const Ipp16u* pSrc, int srcStep,
    Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp16u pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMinBorder_16u_AC4R, (const Ipp16u* pSrc, int srcStep,
    Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp16u pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMinBorder_16u_C4R, (const Ipp16u* pSrc, int srcStep,
    Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp16u pBorderValue[4], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMinBorder_32f_C1R, (const Ipp32f* pSrc, int srcStep,
    Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, Ipp32f borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMinBorder_32f_C3R, (const Ipp32f* pSrc, int srcStep,
    Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp32f pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMinBorder_32f_AC4R, (const Ipp32f* pSrc, int srcStep,
    Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp32f pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterMinBorder_32f_C4R, (const Ipp32f* pSrc, int srcStep,
    Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
    IppiBorderType borderType, const Ipp32f pBorderValue[4], Ipp8u* pBuffer))

/* ///////////////////////////////////////////////////////////////////////////
//             Linear Filters
/////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiFilterBoxBorderGetBufferSize
//  Purpose:            Computes the size of external buffer for FilterBoxBorder
//
//  Parameters:
//    roiSize      Maximum size of the destination image ROI.
//    maskSize     Size of the mask in pixels.
//    dataType     Data type of the image. Possible values are ipp8u, ipp16u, ipp16s, or ipp32f.
//    numChannels  Number of channels in the image. Possible values are 1, 3, or 4.
//    pBufferSize  Pointer to the size of the external work buffer.
//
//  Return Values:
//    ippStsNoErr Indicates no error.
//    ippStsSizeErr Indicates an error when roiSize is negative, or equal to zero.
//    ippStsMaskSizeErr Indicates an error when mask has an illegal value.
//    ippStsDataTypeErr Indicates an error when dataType has an illegal value.
//    ippStsNumChannelsError Indicates an error when numChannels has an illegal value.
*/
IPPAPI (IppStatus, ippiFilterBoxBorderGetBufferSize,(IppiSize roiSize, IppiSize maskSize, IppDataType dataType, int numChannels, int* pBufferSize))

/* ///////////////////////////////////////////////////////////////////////////
//  Name: ippiFilterBoxBorder_32f_<desc>R / ippiFilterBoxBorder_16u_<desc>R / ippiFilterBoxBorder_8u_<desc>R / ippiFilterBoxBorder_16s_<desc>R
//               <desc>  C1|C3|C4|AC4   (descriptor)
// Purpose:             Blurs an image using a simple box filter
// Parameters:
//   pSrc           Pointer to the source image.
//   srcStep        Distance in bytes between starting points of consecutive lines in the source image.
//   pDst           Pointer to the destination image.
//   dstStep        Distance in bytes between starting points of consecutive lines in the destination image.
//   dstRoiSize     Size of the destination ROI in pixels.
//   maskSize       Size of the mask in pixels.
//   border         Type of border. Possible values are:
//                     ippBorderConst Values of all border pixels are set to constant.
//                     ippBorderRepl Border is replicated from the edge pixels.
//                     ippBorderInMem Border is obtained from the source image pixels in memory.
//                     Mixed borders are also supported. They can be obtained by the bitwise operation OR between ippBorderRepl and ippBorderInMemTop, ippBorderInMemBottom, ippBorderInMemLeft, ippBorderInMemRight.
//   borderValue    Constant value to assign to pixels of the constant border. This parameter is applicable only to the ippBorderConst border type.
//   pBuffer        Pointer to the work buffer.
// Returns:
//   ippStsNoErr       Indicates no error.
//   ippStsNullPtrErr  Indicates an error when pSrc or pDst is NULL.
//   ippStsSizeErr     Indicates an error if roiSize has a field with zero or negative value.
//   ippStsMaskSizeErr Indicates an error if mask has an illegal value.
//   ippStsBorderErr   Indicates an error when border has an illegal value.
*/

IPPAPI(IppStatus, ippiFilterBoxBorder_32f_C1R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,IppiSize roiSize,
    IppiSize maskSize, IppiBorderType border,const Ipp32f* borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterBoxBorder_32f_C3R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize,
    IppiSize maskSize, IppiBorderType border,const Ipp32f borderValue[3],Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterBoxBorder_32f_C4R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize,
    IppiSize maskSize, IppiBorderType border,const Ipp32f borderValue[4],Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterBoxBorder_32f_AC4R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize,
    IppiSize maskSize, IppiBorderType border,const Ipp32f borderValue[4],Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterBoxBorder_16u_C1R,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,IppiSize roiSize,
    IppiSize maskSize, IppiBorderType border,const Ipp16u* borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterBoxBorder_16u_C3R,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize,
    IppiSize maskSize, IppiBorderType border,const Ipp16u borderValue[3],Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterBoxBorder_16u_C4R,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize,
    IppiSize maskSize, IppiBorderType border,const Ipp16u borderValue[3],Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterBoxBorder_16u_AC4R,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize,
    IppiSize maskSize, IppiBorderType border,const Ipp16u borderValue[3],Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterBoxBorder_16s_C1R,(const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,IppiSize roiSize,
    IppiSize maskSize, IppiBorderType border,const Ipp16s* borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterBoxBorder_16s_C3R,(const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize,
    IppiSize maskSize, IppiBorderType border,const Ipp16s borderValue[3],Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterBoxBorder_16s_C4R,(const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize,
    IppiSize maskSize, IppiBorderType border,const Ipp16s borderValue[3],Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterBoxBorder_16s_AC4R,(const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize,
    IppiSize maskSize, IppiBorderType border,const Ipp16s borderValue[3],Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterBoxBorder_8u_C1R,(const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,IppiSize roiSize,
    IppiSize maskSize, IppiBorderType border,const Ipp8u* borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterBoxBorder_8u_C3R,(const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize,
    IppiSize maskSize, IppiBorderType border,const Ipp8u borderValue[3],Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterBoxBorder_8u_C4R,(const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize,
    IppiSize maskSize, IppiBorderType border,const Ipp8u borderValue[4],Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterBoxBorder_8u_AC4R,(const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize,
    IppiSize maskSize, IppiBorderType border,const Ipp8u borderValue[4],Ipp8u* pBuffer))

/* ///////////////////////////////////////////////////////////////////////////
// Name:   ippiFilterBox_64f_C1R
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


IPPAPI(IppStatus, ippiFilterBox_64f_C1R, (const Ipp64f* pSrc, int srcStep,
       Ipp64f* pDst, int dstStep,IppiSize dstRoiSize, IppiSize maskSize, IppiPoint anchor))

/* ///////////////////////////////////////////////////////////////////////////
// Name:   ippiSumWindo_8u32s_<desc>R
//         ippiSumWindow_16u32f_<desc>R
//         ippiSumWindow_16s32f_<desc>R
//         ippiSumWindow_32f_<desc>R
//           <desc>  C1|C3|C4   (descriptor)
// Purpose:             Sums pixel values in the row or column mask applied to the image
// Parameters:
//   pSrc               pointer to the source image
//   srcStep            step in the source image
//   pDst               pointer to the destination image
//   dstStep            step in the destination image
//   roiSize            size of the destination ROI
//   maskSize           size of the horizontal or vertical mask in pixels
//   border             Type of border. Possible values are:
//                         ippBorderConst Values of all border pixels are set to constant.
//                         ippBorderRepl Border is replicated from the edge pixels.
//                         ippBorderInMem Border is obtained from the source image pixels in memory.
//                         Mixed borders are also supported. They can be obtained by the bitwise operation
//                         OR between ippBorderRepl and ippBorderInMemTop, ippBorderInMemBottom, ippBorderInMemLeft, ippBorderInMemRight.
//   borderValue        Constant value to assign to pixels of the constant border. This parameter is applicable only to the ippBorderConst border type.
//   pBuffer            Pointer to the work buffer.
// Returns:
//   ippStsNoErr       Indicates no error.
//   ippStsNullPtrErr  Indicates an error when pSrc or pDst is NULL.
//   ippStsSizeErr     Indicates an error if roiSize has a field with zero or negative value.
//   ippStsMaskSizeErr Indicates an error if mask has an illegal value.
//   ippStsBorderErr   Indicates an error when border has an illegal value.
*/

IPPAPI(IppStatus, ippiSumWindowGetBufferSize, (IppiSize roiSize, IppiSize maskSize, IppDataType dataType, int numChannels, int* pBufferSize))

IPPAPI(IppStatus, ippiSumWindow_8u32s_C1R, (const Ipp8u* pSrc, int srcStep,
    Ipp32s* pDst, int dstStep, IppiSize roiSize, IppiSize maskSize, IppiBorderType BorderType, const Ipp8u* borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiSumWindow_8u32s_C3R, (const Ipp8u* pSrc, int srcStep,
    Ipp32s* pDst, int dstStep, IppiSize roiSize, IppiSize maskSize, IppiBorderType BorderType, const Ipp8u* borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiSumWindow_8u32s_C4R, (const Ipp8u* pSrc, int srcStep,
    Ipp32s* pDst, int dstStep, IppiSize roiSize, IppiSize maskSize, IppiBorderType BorderType, const Ipp8u* borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiSumWindow_8u32s_AC4R, (const Ipp8u* pSrc, int srcStep,
    Ipp32s* pDst, int dstStep, IppiSize roiSize, IppiSize maskSize, IppiBorderType BorderType, const Ipp8u* borderValue, Ipp8u* pBuffer))


IPPAPI(IppStatus, ippiSumWindow_16s32f_C1R, (const Ipp16s* pSrc, int srcStep,
    Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiSize maskSize, IppiBorderType BorderType, const Ipp16s* borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiSumWindow_16s32f_C3R, (const Ipp16s* pSrc, int srcStep,
    Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiSize maskSize, IppiBorderType BorderType, const Ipp16s* borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiSumWindow_16s32f_C4R, (const Ipp16s* pSrc, int srcStep,
    Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiSize maskSize, IppiBorderType BorderType, const Ipp16s* borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiSumWindow_16s32f_AC4R, (const Ipp16s* pSrc, int srcStep,
    Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiSize maskSize, IppiBorderType BorderType, const Ipp16s* borderValue, Ipp8u* pBuffer))


IPPAPI(IppStatus, ippiSumWindow_16u32f_C1R, (const Ipp16u* pSrc, int srcStep,
    Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiSize maskSize, IppiBorderType BorderType, const Ipp16u* borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiSumWindow_16u32f_C3R, (const Ipp16u* pSrc, int srcStep,
    Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiSize maskSize, IppiBorderType BorderType, const Ipp16u* borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiSumWindow_16u32f_C4R, (const Ipp16u* pSrc, int srcStep,
    Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiSize maskSize, IppiBorderType BorderType, const Ipp16u* borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiSumWindow_16u32f_AC4R, (const Ipp16u* pSrc, int srcStep,
    Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiSize maskSize, IppiBorderType BorderType, const Ipp16u* borderValue, Ipp8u* pBuffer))


IPPAPI(IppStatus, ippiSumWindow_32f_C1R, (const Ipp32f* pSrc, int srcStep,
    Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiSize maskSize, IppiBorderType BorderType, const Ipp32f* borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiSumWindow_32f_C3R, (const Ipp32f* pSrc, int srcStep,
    Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiSize maskSize, IppiBorderType BorderType, const Ipp32f* borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiSumWindow_32f_C4R, (const Ipp32f* pSrc, int srcStep,
    Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiSize maskSize, IppiBorderType BorderType, const Ipp32f* borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiSumWindow_32f_AC4R, (const Ipp32f* pSrc, int srcStep,
    Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiSize maskSize, IppiBorderType BorderType, const Ipp32f* borderValue, Ipp8u* pBuffer))

/* ///////////////////////////////////////////////////////////////////////////
// Name:   ippiSumWindowRow_8u32f_<desc>R,  ippiSumWindowColumn_8u32f_<desc>R
//         ippiSumWindowRow_16u32f_<desc>R, ippiSumWindowColumn_16u32f_<desc>R
//         ippiSumWindowRow_16s32f_<desc>R, ippiSumWindowColumn_16s32f_<desc>R
//           <desc>  C1|C3|C4   (descriptor)
// Purpose:             Sums pixel values in the row or column mask applied to the image
// Parameters:
//   pSrc               pointer to the source image
//   srcStep            step in the source image
//   pDst               pointer to the destination image
//   dstStep            step in the destination image
//   dstRoiSize         size of the destination ROI
//   maskSize           size of the horizontal or vertical mask in pixels
//   anchor             the anchor cell
// Returns:
//   ippStsNoErr        No errors
//   ippStsNullPtrErr   pSrc == NULL or pDst == NULL or pSrcDst == NULL
//   ippStsSizeErr      dstRoiSize has a field with zero or negative value
//   ippStsMaskSizeErr  maskSize is zero or negative value
//   ippStsAnchorErr    anchor is outside the mask
//   ippStsMemAllocErr  memory allocation error (ippiSumWindowColumn only)
*/

IPPAPI(IppStatus,ippiSumWindowRow_8u32f_C1R, (const Ipp8u* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, int maskSize, int anchor))
IPPAPI(IppStatus,ippiSumWindowRow_8u32f_C3R, (const Ipp8u* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, int maskSize, int anchor))
IPPAPI(IppStatus,ippiSumWindowRow_8u32f_C4R, (const Ipp8u* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, int maskSize, int anchor))
IPPAPI(IppStatus,ippiSumWindowRow_16u32f_C1R, (const Ipp16u* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, int maskSize, int anchor))
IPPAPI(IppStatus,ippiSumWindowRow_16u32f_C3R, (const Ipp16u* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, int maskSize, int anchor))
IPPAPI(IppStatus,ippiSumWindowRow_16u32f_C4R, (const Ipp16u* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, int maskSize, int anchor))
IPPAPI(IppStatus,ippiSumWindowRow_16s32f_C1R, (const Ipp16s* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, int maskSize, int anchor))
IPPAPI(IppStatus,ippiSumWindowRow_16s32f_C3R, (const Ipp16s* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, int maskSize, int anchor))
IPPAPI(IppStatus,ippiSumWindowRow_16s32f_C4R, (const Ipp16s* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, int maskSize, int anchor))

IPPAPI(IppStatus,ippiSumWindowColumn_8u32f_C1R, (const Ipp8u* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, int maskSize, int anchor))
IPPAPI(IppStatus,ippiSumWindowColumn_8u32f_C3R, (const Ipp8u* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, int maskSize, int anchor))
IPPAPI(IppStatus,ippiSumWindowColumn_8u32f_C4R, (const Ipp8u* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, int maskSize, int anchor))
IPPAPI(IppStatus,ippiSumWindowColumn_16u32f_C1R, (const Ipp16u* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, int maskSize, int anchor))
IPPAPI(IppStatus,ippiSumWindowColumn_16u32f_C3R, (const Ipp16u* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, int maskSize, int anchor))
IPPAPI(IppStatus,ippiSumWindowColumn_16u32f_C4R, (const Ipp16u* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, int maskSize, int anchor))
IPPAPI(IppStatus,ippiSumWindowColumn_16s32f_C1R, (const Ipp16s* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, int maskSize, int anchor))
IPPAPI(IppStatus,ippiSumWindowColumn_16s32f_C3R, (const Ipp16s* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, int maskSize, int anchor))
IPPAPI(IppStatus,ippiSumWindowColumn_16s32f_C4R, (const Ipp16s* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, int maskSize, int anchor))


/* ///////////////////////////////////////////////////////////////////////////
//             Filters with Fixed Kernel
/////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////////
//              Kernels:
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
//                               -1 -1 -1
//              Sharpen          -1 16 -1  X  1/8
//                               -1 -1 -1
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
//                               -1 -1 -1
//              Laplace (3x3)    -1  8 -1
//                               -1 -1 -1
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
//                               -2  -8 -12  -8  -2
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
//              SobelHorizSecond (5x5)  -2  -8 -12  -8  -2
//                                       0   0   0   0   0
//                                       1   4   6   4   1
//
//                               -1  -2   0   2   1
//                               -2  -4   0   4   2
//              SobelCross (5x5)  0   0   0   0   0
//                                2   4   0  -4  -2
//                                1   2   0  -2  -1
//
*/

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiFilterSobelHorizBorderGetBufferSize
//                      ippiFilterSobelVertBorderGetBufferSize
//                      ippiFilterScharrHorizMaskBorderGetBufferSize
//                      ippiFilterScharrVertMaskBorderGetBufferSize
//                      ippiFilterPrewittHorizBorderGetBufferSize
//                      ippiFilterPrewittVertBorderGetBufferSize
//                      ippiFilterRobertsDownBorderGetBufferSize
//                      ippiFilterRobertsUpBorderGetBufferSize
//                      ippiFilterSobelHorizSecondBorderGetBufferSize
//                      ippiFilterSobelVertSecondBorderGetBufferSize
//                      ippiFilterSobelNegVertBorderGetBufferSize
//
//  Purpose:            Computes the size of the external buffer for fixed filter with border
//
//  Parameters:
//   roiSize            Size of destination ROI in pixels.
//   mask               Predefined mask of IppiMaskSize type.
//   srcDataType        Data type of the source image.
//   dstDataType        Data type of the destination image.
//   numChannels        Number of channels in the images.
//   pBufferSize        Pointer to the size (in bytes) of the external work buffer.
//
//  Return Values:
//   ippStsNoErr        Indicates no error.
//   ippStsNullPtrErr   Indicates an error when pBufferSize is NULL.
//   ippStsSizeErr      Indicates an error when roiSize is negative, or equal to zero.
//   ippStsMaskSizeErr  Indicates an error condition if mask has a wrong value.
//   ippStsDataTypeErr  Indicates an error when srcDataType or dstDataType has an illegal value.
//   ippStsNumChannelsErr Indicates an error when numChannels has an illegal value.
*/
IPPAPI(IppStatus, ippiFilterSobelHorizBorderGetBufferSize,(IppiSize dstRoiSize, IppiMaskSize mask,
    IppDataType srcDataType, IppDataType dstDataType, int numChannels, int* pBufferSize))
IPPAPI(IppStatus, ippiFilterSobelVertBorderGetBufferSize,(IppiSize dstRoiSize, IppiMaskSize mask,
    IppDataType srcDataType, IppDataType dstDataType, int numChannels, int* pBufferSize))
IPPAPI(IppStatus,  ippiFilterScharrHorizMaskBorderGetBufferSize,(IppiSize dstRoiSize, IppiMaskSize mask,
    IppDataType srcDataType, IppDataType dstDataType, int numChannels, int* pBufferSize))
IPPAPI(IppStatus,  ippiFilterScharrVertMaskBorderGetBufferSize,(IppiSize dstRoiSize, IppiMaskSize mask,
    IppDataType srcDataType, IppDataType dstDataType, int numChannels, int* pBufferSize))
IPPAPI(IppStatus,  ippiFilterPrewittHorizBorderGetBufferSize,(IppiSize dstRoiSize, IppiMaskSize mask,
    IppDataType srcDataType, IppDataType dstDataType, int numChannels, int* pBufferSize))
IPPAPI(IppStatus,  ippiFilterPrewittVertBorderGetBufferSize,(IppiSize dstRoiSize, IppiMaskSize mask,
    IppDataType srcDataType, IppDataType dstDataType, int numChannels, int* pBufferSize))
IPPAPI(IppStatus,  ippiFilterRobertsDownBorderGetBufferSize,(IppiSize dstRoiSize, IppiMaskSize mask,
    IppDataType srcDataType, IppDataType dstDataType, int numChannels, int* pBufferSize))
IPPAPI(IppStatus,  ippiFilterRobertsUpBorderGetBufferSize,(IppiSize dstRoiSize, IppiMaskSize mask,
    IppDataType srcDataType, IppDataType dstDataType, int numChannels, int* pBufferSize))
IPPAPI(IppStatus, ippiFilterSobelHorizSecondBorderGetBufferSize,(IppiSize dstRoiSize, IppiMaskSize mask,
    IppDataType srcDataType, IppDataType dstDataType, int numChannels, int* pBufferSize))
IPPAPI(IppStatus, ippiFilterSobelVertSecondBorderGetBufferSize,(IppiSize dstRoiSize, IppiMaskSize mask,
    IppDataType srcDataType, IppDataType dstDataType, int numChannels, int* pBufferSize))
IPPAPI(IppStatus, ippiFilterSobelNegVertBorderGetBufferSize,(IppiSize dstRoiSize, IppiMaskSize mask,
    IppDataType srcDataType, IppDataType dstDataType, int numChannels, int* pBufferSize))
IPPAPI(IppStatus, ippiFilterLaplaceBorderGetBufferSize,(IppiSize dstRoiSize, IppiMaskSize mask,
    IppDataType srcDataType, IppDataType dstDataType, int numChannels, int* pBufferSize))
IPPAPI(IppStatus, ippiFilterHipassBorderGetBufferSize,(IppiSize dstRoiSize, IppiMaskSize mask,
    IppDataType srcDataType, IppDataType dstDataType, int numChannels, int* pBufferSize))
IPPAPI(IppStatus, ippiFilterSharpenBorderGetBufferSize,(IppiSize dstRoiSize, IppiMaskSize mask,
    IppDataType srcDataType, IppDataType dstDataType, int numChannels, int* pBufferSize))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiFilterSobelVertBorder_8u16s_C1R
//                      ippiFilterSobelHorizBorder_8u16s_C1R
//                      ippiFilterScharrVertMaskBorder_8u16s_C1R
//                      ippiFilterScharrHorizMaskBorder_8u16s_C1R
//                      ippiFilterPrewittVertBorder_8u16s_C1R
//                      ippiFilterPrewittHorizBorder_8u16s_C1R
//                      ippiFilterRobertsDownBorder_8u16s_C1R
//                      ippiFilterRobertsUpBorder_8u16s_C1R
//                      ippiFilterSobelVertSecondBorder_8u16s_C1R
//                      ippiFilterSobelHorizSecondBorder_8u16s_C1R
//                      ippiFilterSobelNegVertBorder_8u16s_C1R
//                      ippiFilterSobelVertBorder_16s_C1R
//                      ippiFilterSobelHorizBorder_16s_C1R
//                      ippiFilterScharrVertMaskBorder_16s_C1R
//                      ippiFilterScharrHorizMaskBorder_16s_C1R
//                      ippiFilterPrewittVertBorder_16s_C1R
//                      ippiFilterPrewittHorizBorder_16s_C1R
//                      ippiFilterRobertsDownBorder_16s_C1R
//                      ippiFilterRobertsUpBorder_16s_C1R
//                      ippiFilterSobelVertBorder_32f_C1R
//                      ippiFilterSobelHorizBorder_32f_C1R
//                      ippiFilterScharrVertMaskBorder_32f_C1R
//                      ippiFilterScharrHorizMaskBorder_32f_C1R
//                      ippiFilterPrewittVertBorder_32f_C1R
//                      ippiFilterPrewittHorizBorder_32f_C1R
//                      ippiFilterRobertsDownBorder_32f_C1R
//                      ippiFilterRobertsUpBorder_32f_C1R
//                      ippiFilterSobelVertSecondBorder_32f_C1R
//                      ippiFilterSobelHorizSecondBorder_32f_C1R
//                      ippiFilterSobelNegVertBorder_32f_C1R
//                      ippiFilterLaplaceBorder_8u_C1R
//                      ippiFilterLaplaceBorder_8u_C3R
//                      ippiFilterLaplaceBorder_8u_C4R
//                      ippiFilterLaplaceBorder_8u_AC4R
//                      ippiFilterLaplaceBorder_16s_C1R
//                      ippiFilterLaplaceBorder_16s_C3R
//                      ippiFilterLaplaceBorder_16s_C4R
//                      ippiFilterLaplaceBorder_16s_AC4R
//                      ippiFilterLaplaceBorder_32f_C1R
//                      ippiFilterLaplaceBorder_32f_C3R
//                      ippiFilterLaplaceBorder_32f_C4R
//                      ippiFilterLaplaceBorder_32f_AC4R
//                      ippiFilterHipassBorder_8u_C1R
//                      ippiFilterHipassBorder_8u_C3R
//                      ippiFilterHipassBorder_8u_C4R
//                      ippiFilterHipassBorder_8u_AC4R
//                      ippiFilterHipassBorder_16s_C1R
//                      ippiFilterHipassBorder_16s_C3R
//                      ippiFilterHipassBorder_16s_C4R
//                      ippiFilterHipassBorder_16s_AC4R
//                      ippiFilterHipassBorder_32f_C1R
//                      ippiFilterHipassBorder_32f_C3R
//                      ippiFilterHipassBorder_32f_C4R
//                      ippiFilterHipassBorder_32f_AC4R
//                      ippiFilterSharpenBorder_8u_C1R
//                      ippiFilterSharpenBorder_8u_C3R
//                      ippiFilterSharpenBorder_8u_C4R
//                      ippiFilterSharpenBorder_8u_AC4R
//                      ippiFilterSharpenBorder_16s_C1R
//                      ippiFilterSharpenBorder_16s_C3R
//                      ippiFilterSharpenBorder_16s_C4R
//                      ippiFilterSharpenBorder_16s_AC4R
//                      ippiFilterSharpenBorder_32f_C1R
//                      ippiFilterSharpenBorder_32f_C3R
//                      ippiFilterSharpenBorder_32f_C4R
//                      ippiFilterSharpenBorder_32f_AC4R

//
//  Purpose:            Perform linear filtering of an image using one of
//                      predefined convolution kernels.
//
//  Parameters:
//   pSrc               Pointer to the source image ROI.
//   srcStep            Distance in bytes between starting points of consecutive lines in the sorce image.
//   pDst               Pointer to the destination image ROI.
//   dstStep            Distance in bytes between starting points of consecutive lines in the destination image.
//   dstRoiSize         Size of destination ROI in pixels.
//   mask               Predefined mask of IppiMaskSize type.
//   borderType         Type of border.
//   borderValue        Constant value to assign to pixels of the constant border. This parameter is applicable
//                      only to the ippBorderConst border type.
//   pBorderValue       The pointer to constant values to assign to pixels of the constant border. This parameter is applicable
//                      only to the ippBorderConst border type.
//   pBuffer            Pointer to the work buffer.
//
//  Return Values:
//   ippStsNoErr        Indicates no error.
//   ippStsNullPtrErr   Indicates an error when pBufferSize is NULL.
//   ippStsSizeErr      Indicates an error when roiSize is negative, or equal to zero.
//   ippStsNotEvenStepErr Indicated an error when one of the step values is not divisible by 4
//                      for floating-point images, or by 2 for short-integer images.
//   ippStsBorderErr    Indicates an error when borderType has illegal value.
*/
IPPAPI(IppStatus, ippiFilterSobelVertBorder_8u16s_C1R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp8u borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSobelHorizBorder_8u16s_C1R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp8u borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterScharrVertMaskBorder_8u16s_C1R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp8u borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterScharrHorizMaskBorder_8u16s_C1R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp8u borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterPrewittVertBorder_8u16s_C1R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp8u borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterPrewittHorizBorder_8u16s_C1R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp8u borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterRobertsDownBorder_8u16s_C1R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp8u borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterRobertsUpBorder_8u16s_C1R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp8u borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSobelVertSecondBorder_8u16s_C1R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp8u borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSobelHorizSecondBorder_8u16s_C1R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp8u borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSobelNegVertBorder_8u16s_C1R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp8u borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterSobelVertBorder_32f_C1R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp32f borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSobelHorizBorder_32f_C1R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp32f borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterScharrVertMaskBorder_32f_C1R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp32f borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterScharrHorizMaskBorder_32f_C1R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp32f borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterPrewittVertBorder_32f_C1R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp32f borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterPrewittHorizBorder_32f_C1R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp32f borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterRobertsDownBorder_32f_C1R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp32f borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterRobertsUpBorder_32f_C1R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp32f borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSobelVertSecondBorder_32f_C1R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp32f borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSobelHorizSecondBorder_32f_C1R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp32f borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSobelNegVertBorder_32f_C1R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp32f borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterSobelVertBorder_16s_C1R, (const Ipp16s* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp16s borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSobelHorizBorder_16s_C1R, (const Ipp16s* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp16s borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterScharrVertMaskBorder_16s_C1R, (const Ipp16s* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp16s borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterScharrHorizMaskBorder_16s_C1R, (const Ipp16s* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp16s borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterPrewittVertBorder_16s_C1R, (const Ipp16s* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp16s borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterPrewittHorizBorder_16s_C1R, (const Ipp16s* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp16s borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterRobertsDownBorder_16s_C1R, (const Ipp16s* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp16s borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterRobertsUpBorder_16s_C1R, (const Ipp16s* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp16s borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterLaplaceBorder_8u_C1R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp8u borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterLaplaceBorder_8u_C3R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp8u pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterLaplaceBorder_8u_AC4R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp8u pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterLaplaceBorder_8u_C4R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp8u pBorderValue[4], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterLaplaceBorder_16s_C1R, (const Ipp16s* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp16s borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterLaplaceBorder_16s_C3R, (const Ipp16s* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp16s pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterLaplaceBorder_16s_AC4R, (const Ipp16s* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp16s pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterLaplaceBorder_16s_C4R, (const Ipp16s* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp16s pBorderValue[4], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterLaplaceBorder_32f_C1R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp32f borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterLaplaceBorder_32f_C3R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp32f pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterLaplaceBorder_32f_AC4R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp32f pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterLaplaceBorder_32f_C4R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp32f pBorderValue[4], Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterHipassBorder_8u_C1R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp8u borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterHipassBorder_8u_C3R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp8u pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterHipassBorder_8u_AC4R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp8u pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterHipassBorder_8u_C4R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp8u pBorderValue[4], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterHipassBorder_16s_C1R, (const Ipp16s* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp16s borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterHipassBorder_16s_C3R, (const Ipp16s* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp16s pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterHipassBorder_16s_AC4R, (const Ipp16s* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp16s pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterHipassBorder_16s_C4R, (const Ipp16s* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp16s pBorderValue[4], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterHipassBorder_32f_C1R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp32f borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterHipassBorder_32f_C3R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp32f pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterHipassBorder_32f_AC4R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp32f pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterHipassBorder_32f_C4R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp32f pBorderValue[4], Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterSharpenBorder_8u_C1R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp8u borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSharpenBorder_8u_C3R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp8u pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSharpenBorder_8u_AC4R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp8u pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSharpenBorder_8u_C4R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp8u pBorderValue[4], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSharpenBorder_16s_C1R, (const Ipp16s* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp16s borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSharpenBorder_16s_C3R, (const Ipp16s* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp16s pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSharpenBorder_16s_AC4R, (const Ipp16s* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp16s pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSharpenBorder_16s_C4R, (const Ipp16s* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp16s pBorderValue[4], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSharpenBorder_32f_C1R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp32f borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSharpenBorder_32f_C3R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp32f pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSharpenBorder_32f_AC4R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp32f pBorderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSharpenBorder_32f_C4R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, const Ipp32f pBorderValue[4], Ipp8u* pBuffer))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiFilterSobelGetBufferSize
//
//  Purpose:            Computes the size of the external buffer for sobel operator
//
//  Parameters:
//   roiSize            Size of destination ROI in pixels.
//   mask               Predefined mask of IppiMaskSize type.
//   normTypre          Normalization mode if IppNormTYpe type.
//   srcDataType        Data type of the source image.
//   dstDataType        Data type of the destination image.
//   numChannels        Number of channels in the images. Possible values is 1.
//   pBufferSize        Pointer to the size (in bytes) of the external work buffer.
//
//  Return Values:
//   ippStsNoErr        Indicates no error.
//   ippStsNullPtrErr   Indicates an error when pBufferSize is NULL.
//   ippStsSizeErr      Indicates an error when roiSize is negative, or equal to zero.
//   ippStsMaskSizeErr  Indicates an error condition if mask has a wrong value.
//   ippStsBadArgErr    Indicates an error condition if normType has an illegal value.
//   ippStsDataTypeErr  Indicates an error when srcDataType or dstDataType has an illegal value.
//   ippStsNumChannelsErr Indicates an error when numChannels has an illegal value.
*/
IPPAPI(IppStatus, ippiFilterSobelGetBufferSize,(IppiSize dstRoiSize, IppiMaskSize mask, IppNormType normType,
    IppDataType srcDataType, IppDataType dstDataType, int numChannels, int* pBufferSize))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiFilterSobel_8u16s_C1R
//                      ippiFilterSobel_16s32f_C1R
//                      ippiFilterSobel_16u32f_C1R
//                      ippiFilterSobel_32f_C1R
//
//  Purpose:            Perform Sobel operation of an image using pair of
//                      predefined convolution kernels.
//
//  Parameters:
//   pSrc               Pointer to the source image ROI.
//   srcStep            Distance in bytes between starting points of consecutive lines in the sorce image.
//   pDst               Pointer to the destination image ROI.
//   dstStep            Distance in bytes between starting points of consecutive lines in the destination image.
//   dstRoiSize         Size of destination ROI in pixels.
//   mask               Predefined mask of IppiMaskSize type.
//   normType           Normalization mode of IppNoremType type
//   borderType         Type of border.
//   borderValue        Constant value to assign to pixels of the constant border. This parameter is applicable
//                      only to the ippBorderConst border type.
//   pBuffer            Pointer to the work buffer.
//
//  Return Values:
//   ippStsNoErr        Indicates no error.
//   ippStsNullPtrErr   Indicates an error condition if pSrc, pDst or pBufferSize is NULL.
//   ippStsSizeErr      Indicates an error condition if dstRoiSize has a fild with zero or negative value.
//   ippStsMaskSizeErr  Indicates an error condition if mask has an illegal value.
//   ippStsBadArgErr    Indicates an error condition if normType has an illegal value.
//   ippStsNotEvenStepErr Indicated an error when one of the step values is not divisible by 4
//                      for floating-point images, or by 2 for short-integer images.
//   ippStsBorderErr    Indicates an error when borderType has illegal value.
*/
IPPAPI(IppStatus, ippiFilterSobel_8u16s_C1R, (const Ipp8u* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
    IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType, IppiBorderType borderType,
    Ipp8u borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSobel_16s32f_C1R, (const Ipp16s* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
    IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType, IppiBorderType borderType,
    Ipp16s borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSobel_16u32f_C1R, (const Ipp16u* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
    IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType, IppiBorderType borderType,
    Ipp16u borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSobel_32f_C1R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
    IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType, IppiBorderType borderType,
    Ipp32f borderValue, Ipp8u* pBuffer))






/* /////////////////////////////////////////////////////////////////////////////
//                  Wiener Filters
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Names:
//      ippiFilterWienerGetBufferSize,
//  Purpose: Computes the size of the external buffer for Wiener filter
//
//      ippiFilterWiener_8u_C1R,  ippiFilterWiener_16s_C1R,
//      ippiFilterWiener_8u_C3R,  ippiFilterWiener_16s_C3R,
//      ippiFilterWiener_8u_C4R,  ippiFilterWiener_16s_C4R,
//      ippiFilterWiener_8u_AC4R, ippiFilterWiener_16s_AC4R,
//      ippiFilterWiener_32f_C1R,
//      ippiFilterWiener_32f_C3R,
//      ippiFilterWiener_32f_C4R,
//      ippiFilterWiener_32f_AC4R.
//
//  Purpose: Performs two-dimensional adaptive noise-removal
//           filtering of an image using Wiener filter.
//
//  Parameters:
//      pSrc        Pointer to the source image ROI;
//      srcStep     Step in bytes through the source image buffer;
//      pDst        Pointer to the destination image ROI;
//      dstStep     Step in bytes through the destination image buffer;
//      dstRoiSize  Size of the destination ROI in pixels;
//      maskSize    Size of the rectangular local pixel neighborhood (mask);
//      anchor      Anchor cell specifying the mask alignment
//                           with respect to the position of the input pixel;
//      noise       Noise level value or array of the noise level values for
//                                                       multi-channel image;
//      pBuffer     Pointer to the external work buffer;
//      pBufferSize Pointer to the computed value of the external buffer size;
//      channels    Number of channels in the image ( 1, 3, or 4 ).
//
//  Returns:
//   ippStsNoErr           OK
//   ippStsNumChannelsErr  channels is not 1, 3, or 4
//   ippStsNullPtrErr      One of the pointers is NULL;
//   ippStsSizeErr         dstRoiSize has a field with zero or negative value
//   ippStsMaskSizeErr     maskSize has a field with zero or negative value
//   ippStsNoiseRangeErr   One of the noise values is less than 0
//                                                         or greater than 1.0;
*/

IPPAPI( IppStatus, ippiFilterWienerGetBufferSize,( IppiSize dstRoiSize,
                          IppiSize maskSize, int channels, int* pBufferSize ))
IPPAPI( IppStatus, ippiFilterWiener_8u_C1R,( const Ipp8u* pSrc, int srcStep,
              Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
                           IppiPoint anchor, Ipp32f noise[1], Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiFilterWiener_8u_C3R,( const Ipp8u* pSrc, int srcStep,
              Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
                           IppiPoint anchor, Ipp32f noise[3], Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiFilterWiener_8u_AC4R,( const Ipp8u* pSrc, int srcStep,
              Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
                           IppiPoint anchor, Ipp32f noise[3], Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiFilterWiener_8u_C4R,( const Ipp8u* pSrc, int srcStep,
              Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
                           IppiPoint anchor, Ipp32f noise[4], Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiFilterWiener_16s_C1R,( const Ipp16s* pSrc, int srcStep,
             Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
                           IppiPoint anchor, Ipp32f noise[1], Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiFilterWiener_16s_C3R,( const Ipp16s* pSrc, int srcStep,
             Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
                           IppiPoint anchor, Ipp32f noise[3], Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiFilterWiener_16s_AC4R,( const Ipp16s* pSrc, int srcStep,
             Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
                           IppiPoint anchor, Ipp32f noise[3], Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiFilterWiener_16s_C4R,( const Ipp16s* pSrc, int srcStep,
             Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
                           IppiPoint anchor, Ipp32f noise[4], Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiFilterWiener_32f_C1R,( const Ipp32f* pSrc, int srcStep,
             Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
                           IppiPoint anchor, Ipp32f noise[1], Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiFilterWiener_32f_C3R,( const Ipp32f* pSrc, int srcStep,
             Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
                           IppiPoint anchor, Ipp32f noise[3], Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiFilterWiener_32f_AC4R,( const Ipp32f* pSrc, int srcStep,
             Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
                           IppiPoint anchor, Ipp32f noise[3], Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiFilterWiener_32f_C4R,( const Ipp32f* pSrc, int srcStep,
             Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
                           IppiPoint anchor, Ipp32f noise[4], Ipp8u* pBuffer ))


/* /////////////////////////////////////////////////////////////////////////////
//  Names:  ippiConvGetBufferSize
//
//  Purpose:     Get the size (in bytes) of the buffer for ippiConv internal calculations.
//
//  Parameters:
//    src1Size    - Size, in pixels, of the first source image.
//    src2Size    - Size, in pixels, of the second source image.
//    dataType    - Data type for convolution. Possible values are ipp32f, ipp16s, or ipp8u.
//    numChannels - Number of image channels. Possible values are 1, 3, or 4.
//    algType     - Bit-field mask for the algorithm type definition.
//                  Possible values are the results of composition of the IppAlgType and IppiROIShape values.
//                  Example: (ippiROIFull|ippAlgFFT) - full-shaped convolution will be calculated using 2D FFT.
//    pBufferSize - Pointer to the calculated buffer size (in bytes).
//
//  Return:
//   ippStsNoErr          - OK.
//   ippStsSizeErr        - Error when the src1Size or src2Size is negative, or equal to zero.
//   ippStsNumChannelsErr - Error when the numChannels value differs from 1, 3, or 4.
//   ippStsDataTypeErr    - Error when the dataType value differs from the ipp32f, ipp16s, or ipp8u.
//   ippStsAlgTypeErr     - Error when :
//                            The result of the bitwise AND operation between algType and ippAlgMask differs from the ippAlgAuto, ippAlgDirect, or ippAlgFFT values.
//                            The result of the bitwise AND operation between algType and ippiROIMask differs from the ippiROIFull or ippiROIValid values.
//   ippStsNullPtrErr     - Error when the pBufferSize is NULL.
*/
IPPAPI( IppStatus, ippiConvGetBufferSize, ( IppiSize src1Size, IppiSize src2Size, IppDataType dataType, int numChannels,  IppEnum algType, int* pBufferSize ))

/* ////////////////////////////////////////////////////////////////////////////
//   Names: ippiConv_32f_C1R, ippiConv_32f_C3R, ippiConv_32f_C4R
//          ippiConv_16s_C1R, ippiConv_16s_C3R, ippiConv_16s_C4R
//          ippiConv_8u_C1R,  ippiConv_8u_C3R,  ippiConv_8u_C4R
//  Purpose: Performs full or valid 2-D convolution of two images.
//           The result image size depends on operation shape selected in algType mask as follows:
//             (Wa+Wb-1)*(Ha+Hb-1) for ippiROIFull mask
//             (Wa-Wb+1)*(Ha-Hb+1) for ippiROIValid mask,
//           where Wa*Ha and Wb*Hb are the sizes of the image and template, respectively.
//          If the IppAlgMask value in algType is equal to ippAlgAuto, the optimal algorithm is selected
//          automatically. For big data size, the function uses 2D FFT algorithm.
//  Parameters:
//    pSrc1, pSrc2       - Pointers to the source images ROI.
//    src1Step, src2Step - Distances, in bytes, between the starting points of consecutive lines in the source images.
//    src1Size, src2Size - Size, in pixels, of the source images.
//    pDst               - Pointer to the destination image ROI.
//    dstStep            - Distance, in bytes, between the starting points of consecutive lines in the destination image.
//    divisor            - The integer value by which the computed result is divided (for operations on integer data only).
//    algType            - Bit-field mask for the algorithm type definition. Possible values are the results of composition of the IppAlgType and IppiROIShape values.
//                          Usage example: algType=(ippiROIFull|ippAlgFFT); - full-shaped convolution will be calculated using 2D FFT.
//    pBuffer            - Pointer to the buffer for internal calculations.
//  Returns:
//    ippStsNoErr      - OK.
//    ippStsNullPtrErr - Error when any of the specified pointers is NULL.
//    ippStsStepErr    - Error when src1Step, src2Step, or dstStep has a zero or negative value.
//    ippStsSizeErr    - Error when src1Size or src2Size has a zero or negative value.
//    ippStsDivisorErr - Error when divisor has the zero value.
//    ippStsAlgTypeErr - Error when :
//                         The result of the bitwise AND operation between algType and ippAlgMask differs from the ippAlgAuto, ippAlgDirect, or ippAlgFFT values.
//                         The result of the bitwise AND operation between algType and ippiROIMask differs from the ippiROIFull or ippiROIValid values.
*/
IPPAPI( IppStatus, ippiConv_32f_C1R, ( const Ipp32f* pSrc1, int src1Step, IppiSize src1Size, const Ipp32f* pSrc2, int src2Step, IppiSize src2Size,
         Ipp32f* pDst, int dstStep, IppEnum algType, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiConv_32f_C3R, ( const Ipp32f* pSrc1, int src1Step, IppiSize src1Size, const Ipp32f* pSrc2, int src2Step, IppiSize src2Size,
         Ipp32f* pDst, int dstStep, IppEnum algType, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiConv_32f_C4R, ( const Ipp32f* pSrc1, int src1Step, IppiSize src1Size, const Ipp32f* pSrc2, int src2Step, IppiSize src2Size,
         Ipp32f* pDst, int dstStep, IppEnum algType, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiConv_16s_C1R, ( const Ipp16s* pSrc1, int src1Step, IppiSize src1Size, const Ipp16s* pSrc2, int src2Step, IppiSize src2Size,
         Ipp16s* pDst, int dstStep,  int divisor, IppEnum algType, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiConv_16s_C3R, ( const Ipp16s* pSrc1, int src1Step, IppiSize src1Size, const Ipp16s* pSrc2, int src2Step, IppiSize src2Size,
         Ipp16s* pDst, int dstStep, int divisor, IppEnum algType, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiConv_16s_C4R, ( const Ipp16s* pSrc1, int src1Step, IppiSize src1Size, const Ipp16s* pSrc2, int src2Step, IppiSize src2Size,
         Ipp16s* pDst, int dstStep, int divisor, IppEnum algType, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiConv_8u_C1R, ( const Ipp8u* pSrc1, int src1Step, IppiSize src1Size, const Ipp8u* pSrc2, int src2Step, IppiSize src2Size,
         Ipp8u* pDst, int dstStep, int divisor, IppEnum algType, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiConv_8u_C3R, ( const Ipp8u* pSrc1, int src1Step, IppiSize src1Size, const Ipp8u* pSrc2, int src2Step, IppiSize src2Size,
         Ipp8u* pDst, int dstStep, int divisor, IppEnum algType, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiConv_8u_C4R, ( const Ipp8u* pSrc1, int src1Step, IppiSize src1Size, const Ipp8u* pSrc2, int src2Step, IppiSize src2Size,
         Ipp8u* pDst, int dstStep, int divisor, IppEnum algType, Ipp8u* pBuffer ))



/* //////////////////////////////////////////////////////////////////////////////////////
//                   Image Proximity Measures
////////////////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Names:  ippiCrossCorrNormGetBufferSize
//
//  Purpose:     Computes the size (in bytes) of the work buffer for the ippiCrossCorrNorm functions.
//
//  Parameters:
//    srcRoiSize  - Size of the source ROI in pixels.
//    tplRoiSize  - Size of the template ROI in pixels.
//    algType     - Bit-field mask for the algorithm type definition. Possible values are the results of composition of the IppAlgType, IppiROIShape, and IppiNormOp values.
//                  Usage example: algType=(ippiROIFull|ippAlgFFT|ippiNorm); - full-shaped cross-correlation will be calculated
//                      using 2D FFT and normalization applied to result image.
//    pBufferSize - Pointer to the size of the work buffer (in bytes).
//  Return:
//    ippStsNoErr       - OK.
//    ippStsSizeErr     - Error when:
//                            srcRoiSize or tplRoiSize is negative, or equal to zero.
//                            The value of srcRoiSize is less than the corresponding value of the tplRoiSize.
//    ippStsAlgTypeErr  - Error when :
//                            The result of the bitwise AND operation between the algType and ippAlgMask differs from the ippAlgAuto, ippAlgDirect, or ippAlgFFT values.
//                            The result of the bitwise AND operation between the algType and ippiROIMask differs from the ippiROIFull, ippiROISame, or ippiROIValid values.
//                            The result of the bitwise AND operation between the algType and ippiNormMask differs from the ippiNormNone, ippiNorm, or ippiNormCoefficient values.
//    ippStsNullPtrErr  - Error when the pBufferSize is NULL.
*/
IPPAPI( IppStatus, ippiCrossCorrNormGetBufferSize, ( IppiSize srcRoiSize, IppiSize tplRoiSize, IppEnum algType, int* pBufferSize ))


/* ////////////////////////////////////////////////////////////////////////////
//  Names: ippiCrossCorrNorm_32f_C1R
//         ippiCrossCorrNorm_16u32f_C1R
//         ippiCrossCorrNorm_8u32f_C1R
//         ippiCrossCorrNorm_8u_C1RSfs
//  Purpose: Computes normalized cross-correlation between an image and a template.
//           The result image size depends on operation shape selected in algType mask as follows :
//             (Wa+Wb-1)*(Ha+Hb-1) for ippiROIFull mask,
//             (Wa)*(Ha)           for ippiROISame mask,
//             (Wa-Wb+1)*(Ha-Hb+1) for ippiROIValid mask,
//           where Wa*Ha and Wb*Hb are the sizes of the image and template correspondingly.
//           Support of normalization operations (set in the algType mask) is set by selecting the following masks:
//             ippiNormNone   - the cross-correlation without normalization.
//             ippiNorm - the normalized cross-correlation.
//             ippiNormCoefficient  - the normalized correlation coefficients.
//           If the IppAlgMask value in algType is equal to ippAlgAuto, the optimal algorithm is selected automatically.
//           For big data size, the function uses 2D FFT algorithm.
//  Parameters:
//    pSrc        - Pointer to the source image ROI.
//    srcStep     - Distance, in bytes, between the starting points of consecutive lines in the source image.
//    srcRoiSize  - Size of the source ROI in pixels.
//    pTpl        - Pointer to the template image.
//    tplStep     - Distance, in bytes, between the starting points of consecutive lines in the template image.
//    tplRoiSize  - Size of the template ROI in pixels.
//    pDst        - Pointer to the destination image ROI.
//    dstStep     - Distance, in bytes, between the starting points of consecutive lines in the destination image.
//    scaleFactor - Scale factor.
//    algType     - Bit-field mask for the algorithm type definition. Possible values are the results of composition of the IppAlgType, IppiROIShape, and IppiNormOp values.
//                  Usage example: algType=(ippiROIFull|ippAlgFFT|ippiNormNone); - full-shaped cross-correlation will be calculated using 2D FFT without result normalization.
//    pBuffer     - Pointer to the work buffer.
//  Returns:
//    ippStsNoErr      OK.
//    ippStsNullPtrErr Error when any of the specified pointers is NULL.
//    ippStsStepErr    Error when the value of srcStep, tplStep, or dstStep is negative, or equal to zero.
//    ippStsSizeErr    Error when :
//                         srcRoiSize or tplRoiSize is negative, or equal to zero.
//                         The value of srcRoiSize is less than the corresponding value of tplRoiSize.
//    ippStsAlgTypeErr Error when :
//                         The result of the bitwise AND operation between the algType and ippAlgMask differs from the ippAlgAuto, ippAlgDirect, or ippAlgFFT values.
//                         The result of the bitwise AND operation between the algType and ippiROIMask differs from the ippiROIFull, ippiROISame, or ippiROIValid values.
//                         The result of the bitwise AND operation between the algType and ippiNormMask differs from the ippiNormNone, ippiNorm, or ippiNormCoefficient values.
*/
IPPAPI( IppStatus, ippiCrossCorrNorm_32f_C1R, ( const Ipp32f* pSrc, int srcStep, IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
      Ipp32f* pDst, int dstStep, IppEnum algType, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiCrossCorrNorm_16u32f_C1R, ( const Ipp16u* pSrc, int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep, IppiSize tplRoiSize,
      Ipp32f* pDst, int dstStep, IppEnum algType, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiCrossCorrNorm_8u32f_C1R, ( const Ipp8u* pSrc, int srcStep, IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
      Ipp32f* pDst, int dstStep, IppEnum algType, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiCrossCorrNorm_8u_C1RSfs, ( const Ipp8u* pSrc, int srcStep, IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
      Ipp8u* pDst, int dstStep, int scaleFactor, IppEnum algType, Ipp8u* pBuffer ))

/* /////////////////////////////////////////////////////////////////////////////
//  Names:  ippiSqrDistanceNormGetBufferSize
//
//  Purpose:     Computes the size of the work buffer for the ippiSqrDistanceNorm functions.
//
//  Parameters:
//    srcRoiSize  - Size of the source ROI, in pixels.
//    tplRoiSize  - Size of the template ROI, in pixels.
//    algType     - Bit-field mask for the algorithm type definition. Possible values are the results of composition of the IppAlgType, IppiROIShape, and IppiNormOp values.
//                  Usage example: algType=(ippiROIFull|ippAlgFFT|ippiNorm); - result image will be calculated for full-shaped ROI
//                  using 2D FFT and normalization applied.
//    pBufferSize - Pointer where to store the calculated buffer size (in bytes)
//  Return:
//    ippStsNoErr      - Ok.
//    ippStsSizeErr    - Error when :
//                           srcRoiSize or tplRoiSize is negative, or equal to zero.
//                           The value of srcRoiSize is less than the corresponding value of tplRoiSize.
//    ippStsAlgTypeErr - Error when :
//                           The result of the bitwise AND operation between the algType and ippAlgMask differs from the ippAlgAuto, ippAlgDirect, or ippAlgFFT values.
//                           The result of the bitwise AND operation between the algType and ippiROIMask differs from the ippiROIFull, ippiROISame, or ippiROIValid values.
//                           The result of the bitwise AND operation between the algType and ippiNormMask differs from the ippiNormNone or ippiNorm values.
//    ippStsNullPtrErr - Error when the pBufferSize is NULL.
*/
IPPAPI( IppStatus, ippiSqrDistanceNormGetBufferSize, ( IppiSize srcRoiSize, IppiSize tplRoiSize, IppEnum algType, int* pBufferSize ))

/* ////////////////////////////////////////////////////////////////////////////
//  Names: ippiSqrDistanceNorm_32f_C1R
//         ippiSqrDistanceNorm_16u32f_C1R
//         ippiSqrDistanceNorm_8u32f_C1R
//         ippiSqrDistanceNorm_8u_C1RSfs
//  Purpose: Computes Euclidean distance between an image and a template.
//           The result image size depends on operation shape selected in algType mask as follows :
//             (Wa+Wb-1)*(Ha+Hb-1) for ippiROIFull mask,
//             (Wa)*(Ha)           for ippiROISame mask,
//             (Wa-Wb+1)*(Ha-Hb+1) for ippiROIValid mask,
//           where Wa*Ha and Wb*Hb are the sizes of the image and template , respectively.
//           Support of normalization operations (set the algType mask) :
//             ippiNormNone   - the squared Euclidean distances.
//             ippiNorm - the normalized squared Euclidean distances.
//           If the IppAlgMask value in algType is equal to ippAlgAuto, the optimal algorithm is selected
//           automatically. For big data size, the function uses 2D FFT algorithm.
//  Parameters:
//    pSrc        - Pointer to the source image ROI.
//    srcStep     - Distance, in bytes, between the starting points of consecutive lines in the source image.
//    srcRoiSize  - Size of the source ROI, in pixels.
//    pTpl        - Pointer to the template image.
//    tplStep     - Distance, in bytes, between the starting points of consecutive lines in the template image.
//    tplRoiSize  - Size of the template ROI, in pixels.
//    pDst        - Pointer to the destination image ROI.
//    dstStep     - Distance, in bytes, between the starting points of consecutive lines in the destination image.
//    scaleFactor - Scale factor.
//    algType     - Bit-field mask for the algorithm type definition. Possible values are the results of composition of the IppAlgType, IppiROIShape, and IppiNormOp values.
//                  Usage example: algType=(ippiROIFull|ippiNormNone|ippAlgFFT); - result will be calculated for full-shaped ROI using 2D FFT without normalization.
//    pBuffer     - Pointer to the buffer for internal calculation.
//  Returns:
//    ippStsNoErr      OK.
//    ippStsNullPtrErr Error when any of the specified pointers is NULL.
//    ippStsStepErr    Error when the value of srcStep, tplStep, or dstStep is negative, or equal to zero.
//    ippStsSizeErr    Error when :
//                         srcRoiSize or tplRoiSize is negative, or equal to zero.
//                         The value of srcRoiSize is less than the corresponding value of the tplRoiSize.
//    ippStsAlgTypeErr Error when :
//                         The result of the bitwise AND operation between the algType and ippAlgMask differs from the ippAlgAuto, ippAlgDirect, or ippAlgFFT values.
//                         The result of the bitwise AND operation between the algType and ippiROIMask differs from the ippiROIFull, ippiROISame, or ippiROIValid values.
//                         The result of the bitwise AND operation between the algType and ippiNormMask differs from the ippiNormNone or ippiNorm values.
*/
IPPAPI( IppStatus, ippiSqrDistanceNorm_32f_C1R, ( const Ipp32f* pSrc, int srcStep, IppiSize srcRoiSize, const Ipp32f* pTpl, int tplStep, IppiSize tplRoiSize,
         Ipp32f* pDst, int dstStep, IppEnum algType, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiSqrDistanceNorm_16u32f_C1R, ( const Ipp16u* pSrc, int srcStep, IppiSize srcRoiSize, const Ipp16u* pTpl, int tplStep, IppiSize tplRoiSize,
         Ipp32f* pDst, int dstStep, IppEnum algType, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiSqrDistanceNorm_8u32f_C1R, ( const Ipp8u* pSrc, int srcStep, IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
         Ipp32f* pDst, int dstStep, IppEnum algType, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiSqrDistanceNorm_8u_C1RSfs, ( const Ipp8u* pSrc, int srcStep, IppiSize srcRoiSize, const Ipp8u* pTpl, int tplStep, IppiSize tplRoiSize,
         Ipp8u* pDst, int dstStep, int scaleFactor, IppEnum algType, Ipp8u* pBuffer ))


/* /////////////////////////////////////////////////////////////////////////////
//                   Threshold operations
///////////////////////////////////////////////////////////////////////////// */

/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiThreshold_8u_C1R
//              ippiThreshold_8u_C3R
//              ippiThreshold_8u_AC4R
//              ippiThreshold_16s_C1R
//              ippiThreshold_16s_C3R
//              ippiThreshold_16s_AC4R
//              ippiThreshold_32f_C1R
//              ippiThreshold_32f_C3R
//              ippiThreshold_32f_AC4R
//              ippiThreshold_8u_C1IR
//              ippiThreshold_8u_C3IR
//              ippiThreshold_8u_AC4IR
//              ippiThreshold_16s_C1IR
//              ippiThreshold_16s_C3IR
//              ippiThreshold_16s_AC4IR
//              ippiThreshold_32f_C1IR
//              ippiThreshold_32f_C3IR
//              ippiThreshold_32f_AC4IR
//              ippiThreshold_16u_C1R
//              ippiThreshold_16u_C3R
//              ippiThreshold_16u_AC4R
//              ippiThreshold_16u_C1IR
//              ippiThreshold_16u_C3IR
//              ippiThreshold_16u_AC4IR
//
//  Purpose:    Performs thresholding of an image using the specified level

//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  One of the pointers is NULL
//   ippStsSizeErr     roiSize has a field with zero or negative value
//   ippStsStepErr     One of the step values is zero or negative
//
//  Parameters:
//   pSrc       Pointer to the source image
//   srcStep    Step through the source image
//   pDst       Pointer to the destination image
//   dstStep    Step through the destination image
//   pSrcDst    Pointer to the source/destination image (in-place flavors)
//   srcDstStep Step through the source/destination image (in-place flavors)
//   roiSize    Size of the ROI
//   threshold  Threshold level value (array of values for multi-channel data)
//   ippCmpOp   Comparison mode, possible values:
//                ippCmpLess     - less than,
//                ippCmpGreater  - greater than
*/
IPPAPI(IppStatus,ippiThreshold_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, Ipp8u threshold,
       IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_16s_C1R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, Ipp16s threshold,
       IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, Ipp32f threshold,
       IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp8u threshold[3],
       IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_16s_C3R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, const Ipp16s threshold[3],
       IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_32f_C3R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, const Ipp32f threshold[3],
       IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_8u_AC4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp8u threshold[3],
       IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_16s_AC4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, const Ipp16s threshold[3],
       IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_32f_AC4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, const Ipp32f threshold[3],
       IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_8u_C1IR,(Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp8u threshold, IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_16s_C1IR,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp16s threshold, IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_32f_C1IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp32f threshold, IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_8u_C3IR,(Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp8u threshold[3], IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_16s_C3IR,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16s threshold[3], IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_32f_C3IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp32f threshold[3], IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_8u_AC4IR,(Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp8u threshold[3], IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_16s_AC4IR,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16s threshold[3], IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_32f_AC4IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp32f threshold[3], IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_16u_C1R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, Ipp16u threshold,
       IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_16u_C3R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, const Ipp16u threshold[3],
       IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_16u_AC4R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, const Ipp16u threshold[3],
       IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_16u_C1IR,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp16u threshold, IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_16u_C3IR,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16u threshold[3], IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_16u_AC4IR,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16u threshold[3], IppCmpOp ippCmpOp))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiThreshold_GT_8u_C1R
//              ippiThreshold_GT_8u_C3R
//              ippiThreshold_GT_8u_AC4R
//              ippiThreshold_GT_16s_C1R
//              ippiThreshold_GT_16s_C3R
//              ippiThreshold_GT_16s_AC4R
//              ippiThreshold_GT_32f_C1R
//              ippiThreshold_GT_32f_C3R
//              ippiThreshold_GT_32f_AC4R
//              ippiThreshold_GT_8u_C1IR
//              ippiThreshold_GT_8u_C3IR
//              ippiThreshold_GT_8u_AC4IR
//              ippiThreshold_GT_16s_C1IR
//              ippiThreshold_GT_16s_C3IR
//              ippiThreshold_GT_16s_AC4IR
//              ippiThreshold_GT_32f_C1IR
//              ippiThreshold_GT_32f_C3IR
//              ippiThreshold_GT_32f_AC4IR
//              ippiThreshold_GT_16u_C1R
//              ippiThreshold_GT_16u_C3R
//              ippiThreshold_GT_16u_AC4R
//              ippiThreshold_GT_16u_C1IR
//              ippiThreshold_GT_16u_C3IR
//              ippiThreshold_GT_16u_AC4IR
//
//  Purpose:   Performs threshold operation using the comparison "greater than"
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  One of the pointers is NULL
//   ippStsSizeErr     roiSize has a field with zero or negative value
//   ippStsStepErr     One of the step values is zero or negative
//
//  Parameters:
//   pSrc       Pointer to the source image
//   srcStep    Step through the source image
//   pDst       Pointer to the destination image
//   dstStep    Step through the destination image
//   pSrcDst    Pointer to the source/destination image (in-place flavors)
//   srcDstStep Step through the source/destination image (in-place flavors)
//   roiSize    Size of the ROI
//   threshold  Threshold level value (array of values for multi-channel data)
*/
IPPAPI(IppStatus,ippiThreshold_GT_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, Ipp8u threshold))
IPPAPI(IppStatus,ippiThreshold_GT_16s_C1R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, Ipp16s threshold))
IPPAPI(IppStatus,ippiThreshold_GT_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, Ipp32f threshold))
IPPAPI(IppStatus,ippiThreshold_GT_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp8u threshold[3]))
IPPAPI(IppStatus,ippiThreshold_GT_16s_C3R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, const Ipp16s threshold[3]))
IPPAPI(IppStatus,ippiThreshold_GT_32f_C3R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, const Ipp32f threshold[3]))
IPPAPI(IppStatus,ippiThreshold_GT_8u_AC4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp8u threshold[3]))
IPPAPI(IppStatus,ippiThreshold_GT_16s_AC4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, const Ipp16s threshold[3]))
IPPAPI(IppStatus,ippiThreshold_GT_32f_AC4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, const Ipp32f threshold[3]))
IPPAPI(IppStatus,ippiThreshold_GT_8u_C1IR,(Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp8u threshold))
IPPAPI(IppStatus,ippiThreshold_GT_16s_C1IR,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp16s threshold))
IPPAPI(IppStatus,ippiThreshold_GT_32f_C1IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp32f threshold))
IPPAPI(IppStatus,ippiThreshold_GT_8u_C3IR,(Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp8u threshold[3]))
IPPAPI(IppStatus,ippiThreshold_GT_16s_C3IR,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16s threshold[3]))
IPPAPI(IppStatus,ippiThreshold_GT_32f_C3IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp32f threshold[3]))
IPPAPI(IppStatus,ippiThreshold_GT_8u_AC4IR,(Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp8u threshold[3]))
IPPAPI(IppStatus,ippiThreshold_GT_16s_AC4IR,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16s threshold[3]))
IPPAPI(IppStatus,ippiThreshold_GT_32f_AC4IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp32f threshold[3]))
IPPAPI(IppStatus,ippiThreshold_GT_16u_C1R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, Ipp16u threshold))
IPPAPI(IppStatus,ippiThreshold_GT_16u_C3R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, const Ipp16u threshold[3]))
IPPAPI(IppStatus,ippiThreshold_GT_16u_AC4R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, const Ipp16u threshold[3]))
IPPAPI(IppStatus,ippiThreshold_GT_16u_C1IR,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp16u threshold))
IPPAPI(IppStatus,ippiThreshold_GT_16u_C3IR,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16u threshold[3]))
IPPAPI(IppStatus,ippiThreshold_GT_16u_AC4IR,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16u threshold[3]))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiThreshold_LT_8u_C1R
//              ippiThreshold_LT_8u_C3R
//              ippiThreshold_LT_8u_AC4R
//              ippiThreshold_LT_16s_C1R
//              ippiThreshold_LT_16s_C3R
//              ippiThreshold_LT_16s_AC4R
//              ippiThreshold_LT_32f_C1R
//              ippiThreshold_LT_32f_C3R
//              ippiThreshold_LT_32f_AC4R
//              ippiThreshold_LT_8u_C1IR
//              ippiThreshold_LT_8u_C3IR
//              ippiThreshold_LT_8u_AC4IR
//              ippiThreshold_LT_16s_C1IR
//              ippiThreshold_LT_16s_C3IR
//              ippiThreshold_LT_16s_AC4IR
//              ippiThreshold_LT_32f_C1IR
//              ippiThreshold_LT_32f_C3IR
//              ippiThreshold_LT_32f_AC4IR
//              ippiThreshold_LT_16u_C1R
//              ippiThreshold_LT_16u_C3R
//              ippiThreshold_LT_16u_AC4R
//              ippiThreshold_LT_16u_C1IR
//              ippiThreshold_LT_16u_C3IR
//              ippiThreshold_LT_16u_AC4IR
//
//  Purpose:  Performs threshold operation using the comparison "less than"
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  One of the pointers is NULL
//   ippStsSizeErr     roiSize has a field with zero or negative value
//   ippStsStepErr     One of the step values is zero or negative
//
//  Parameters:
//   pSrc       Pointer to the source image
//   srcStep    Step through the source image
//   pDst       Pointer to the destination image
//   dstStep    Step through the destination image
//   pSrcDst    Pointer to the source/destination image (in-place flavors)
//   srcDstStep Step through the source/destination image (in-place flavors)
//   roiSize    Size of the ROI
//   threshold  Threshold level value (array of values for multi-channel data)
//   ippCmpOp   Comparison mode, possible values:
//                ippCmpLess     - less than
//                ippCmpGreater  - greater than
*/
IPPAPI(IppStatus,ippiThreshold_LT_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, Ipp8u threshold))
IPPAPI(IppStatus,ippiThreshold_LT_16s_C1R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, Ipp16s threshold))
IPPAPI(IppStatus,ippiThreshold_LT_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, Ipp32f threshold))
IPPAPI(IppStatus,ippiThreshold_LT_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp8u threshold[3]))
IPPAPI(IppStatus,ippiThreshold_LT_16s_C3R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, const Ipp16s threshold[3]))
IPPAPI(IppStatus,ippiThreshold_LT_32f_C3R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, const Ipp32f threshold[3]))
IPPAPI(IppStatus,ippiThreshold_LT_8u_AC4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp8u threshold[3]))
IPPAPI(IppStatus,ippiThreshold_LT_16s_AC4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, const Ipp16s threshold[3]))
IPPAPI(IppStatus,ippiThreshold_LT_32f_AC4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, const Ipp32f threshold[3]))
IPPAPI(IppStatus,ippiThreshold_LT_8u_C1IR,(Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp8u threshold))
IPPAPI(IppStatus,ippiThreshold_LT_16s_C1IR,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp16s threshold))
IPPAPI(IppStatus,ippiThreshold_LT_32f_C1IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp32f threshold))
IPPAPI(IppStatus,ippiThreshold_LT_8u_C3IR,(Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp8u threshold[3]))
IPPAPI(IppStatus,ippiThreshold_LT_16s_C3IR,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16s threshold[3]))
IPPAPI(IppStatus,ippiThreshold_LT_32f_C3IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp32f threshold[3]))
IPPAPI(IppStatus,ippiThreshold_LT_8u_AC4IR,(Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp8u threshold[3]))
IPPAPI(IppStatus,ippiThreshold_LT_16s_AC4IR,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16s threshold[3]))
IPPAPI(IppStatus,ippiThreshold_LT_32f_AC4IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp32f threshold[3]))
IPPAPI(IppStatus,ippiThreshold_LT_16u_C1R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, Ipp16u threshold))
IPPAPI(IppStatus,ippiThreshold_LT_16u_C3R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, const Ipp16u threshold[3]))
IPPAPI(IppStatus,ippiThreshold_LT_16u_AC4R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, const Ipp16u threshold[3]))
IPPAPI(IppStatus,ippiThreshold_LT_16u_C1IR,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp16u threshold))
IPPAPI(IppStatus,ippiThreshold_LT_16u_C3IR,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16u threshold[3]))
IPPAPI(IppStatus,ippiThreshold_LT_16u_AC4IR,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16u threshold[3]))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiThreshold_Val_8u_C1R
//              ippiThreshold_Val_8u_C3R
//              ippiThreshold_Val_8u_AC4R
//              ippiThreshold_Val_16s_C1R
//              ippiThreshold_Val_16s_C3R
//              ippiThreshold_Val_16s_AC4R
//              ippiThreshold_Val_32f_C1R
//              ippiThreshold_Val_32f_C3R
//              ippiThreshold_Val_32f_AC4R
//              ippiThreshold_Val_8u_C1IR
//              ippiThreshold_Val_8u_C3IR
//              ippiThreshold_Val_8u_AC4IR
//              ippiThreshold_Val_16s_C1IR
//              ippiThreshold_Val_16s_C3IR
//              ippiThreshold_Val_16s_AC4IR
//              ippiThreshold_Val_32f_C1IR
//              ippiThreshold_Val_32f_C3IR
//              ippiThreshold_Val_32f_AC4IR
//              ippiThreshold_Val_16u_C1R
//              ippiThreshold_Val_16u_C3R
//              ippiThreshold_Val_16u_AC4R
//              ippiThreshold_Val_16u_C1IR
//              ippiThreshold_Val_16u_C3IR
//              ippiThreshold_Val_16u_AC4IR
//
//  Purpose:  Performs thresholding of pixel values: pixels that satisfy
//            the compare conditions are set to a specified value
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  One of the pointers is NULL
//   ippStsSizeErr     roiSize has a field with zero or negative value
//   ippStsStepErr     One of the step values is zero or negative
//
//  Parameters:
//   pSrc       Pointer to the source image
//   srcStep    Step through the source image
//   pDst       Pointer to the destination image
//   dstStep    Step through the destination image
//   pSrcDst    Pointer to the source/destination image (in-place flavors)
//   srcDstStep Step through the source/destination image (in-place flavors)
//   roiSize    Size of the ROI
//   threshold  Threshold level value (array of values for multi-channel data)
//   value      The output value (array or values for multi-channel data)
//   ippCmpOp      comparison mode, ippCmpLess or ippCmpGreater
*/
IPPAPI(IppStatus,ippiThreshold_Val_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, Ipp8u threshold,
       Ipp8u value, IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_Val_16s_C1R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, Ipp16s threshold,
       Ipp16s value, IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_Val_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, Ipp32f threshold,
       Ipp32f value, IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_Val_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp8u threshold[3],
       const Ipp8u value[3], IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_Val_16s_C3R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, const Ipp16s threshold[3],
       const Ipp16s value[3], IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_Val_32f_C3R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, const Ipp32f threshold[3],
       const Ipp32f value[3], IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_Val_8u_AC4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp8u threshold[3],
       const Ipp8u value[3], IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_Val_16s_AC4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, const Ipp16s threshold[3],
       const Ipp16s value[3], IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_Val_32f_AC4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, const Ipp32f threshold[3],
       const Ipp32f value[3], IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_Val_8u_C1IR,(Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp8u threshold, Ipp8u value, IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_Val_16s_C1IR,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp16s threshold, Ipp16s value, IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_Val_32f_C1IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp32f threshold, Ipp32f value, IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_Val_8u_C3IR,(Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp8u threshold[3], const Ipp8u value[3],
       IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_Val_16s_C3IR,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16s threshold[3], const Ipp16s value[3],
       IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_Val_32f_C3IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp32f threshold[3], const Ipp32f value[3],
       IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_Val_8u_AC4IR,(Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp8u threshold[3], const Ipp8u value[3],
       IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_Val_16s_AC4IR,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16s threshold[3], const Ipp16s value[3],
       IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_Val_32f_AC4IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp32f threshold[3], const Ipp32f value[3],
       IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_Val_16u_C1R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, Ipp16u threshold,
       Ipp16u value, IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_Val_16u_C3R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, const Ipp16u threshold[3],
       const Ipp16u value[3], IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_Val_16u_AC4R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, const Ipp16u threshold[3],
       const Ipp16u value[3], IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_Val_16u_C1IR,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp16u threshold, Ipp16u value, IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_Val_16u_C3IR,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16u threshold[3], const Ipp16u value[3],
       IppCmpOp ippCmpOp))
IPPAPI(IppStatus,ippiThreshold_Val_16u_AC4IR,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16u threshold[3], const Ipp16u value[3],
       IppCmpOp ippCmpOp))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiThreshold_GTVal_8u_C1R
//              ippiThreshold_GTVal_8u_C3R
//              ippiThreshold_GTVal_8u_AC4R
//              ippiThreshold_GTVal_16s_C1R
//              ippiThreshold_GTVal_16s_C3R
//              ippiThreshold_GTVal_16s_AC4R
//              ippiThreshold_GTVal_32f_C1R
//              ippiThreshold_GTVal_32f_C3R
//              ippiThreshold_GTVal_32f_AC4R
//              ippiThreshold_GTVal_8u_C1IR
//              ippiThreshold_GTVal_8u_C3IR
//              ippiThreshold_GTVal_8u_AC4IR
//              ippiThreshold_GTVal_16s_C1IR
//              ippiThreshold_GTVal_16s_C3IR
//              ippiThreshold_GTVal_16s_AC4IR
//              ippiThreshold_GTVal_32f_C1IR
//              ippiThreshold_GTVal_32f_C3IR
//              ippiThreshold_GTVal_32f_AC4IR
//              ippiThreshold_GTVal_8u_C4R
//              ippiThreshold_GTVal_16s_C4R
//              ippiThreshold_GTVal_32f_C4R
//              ippiThreshold_GTVal_8u_C4IR
//              ippiThreshold_GTVal_16s_C4IR
//              ippiThreshold_GTVal_32f_C4IR
//              ippiThreshold_GTVal_16u_C1R
//              ippiThreshold_GTVal_16u_C3R
//              ippiThreshold_GTVal_16u_AC4R
//              ippiThreshold_GTVal_16u_C1IR
//              ippiThreshold_GTVal_16u_C3IR
//              ippiThreshold_GTVal_16u_AC4IR
//              ippiThreshold_GTVal_16u_C4R
//              ippiThreshold_GTVal_16u_C4IR
//
//  Purpose:  Performs thresholding of pixel values: pixels that are
//            greater than threshold, are set to a specified value
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  One of the pointers is NULL
//   ippStsSizeErr     roiSize has a field with zero or negative value
//   ippStsStepErr     One of the step values is zero or negative
//
//  Parameters:
//   pSrc       Pointer to the source image
//   srcStep    Step through the source image
//   pDst       Pointer to the destination image
//   dstStep    Step through the destination image
//   pSrcDst    Pointer to the source/destination image (in-place flavors)
//   srcDstStep Step through the source/destination image (in-place flavors)
//   roiSize    Size of the ROI
//   threshold  Threshold level value (array of values for multi-channel data)
//   value      The output value (array or values for multi-channel data)
*/
IPPAPI(IppStatus,ippiThreshold_GTVal_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, Ipp8u threshold,
       Ipp8u value))
IPPAPI(IppStatus,ippiThreshold_GTVal_16s_C1R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, Ipp16s threshold,
       Ipp16s value))
IPPAPI(IppStatus,ippiThreshold_GTVal_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, Ipp32f threshold,
       Ipp32f value))
IPPAPI(IppStatus,ippiThreshold_GTVal_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp8u threshold[3],
       const Ipp8u value[3]))
IPPAPI(IppStatus,ippiThreshold_GTVal_16s_C3R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, const Ipp16s threshold[3],
       const Ipp16s value[3]))
IPPAPI(IppStatus,ippiThreshold_GTVal_32f_C3R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, const Ipp32f threshold[3],
       const Ipp32f value[3]))
IPPAPI(IppStatus,ippiThreshold_GTVal_8u_AC4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp8u threshold[3],
       const Ipp8u value[3]))
IPPAPI(IppStatus,ippiThreshold_GTVal_16s_AC4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, const Ipp16s threshold[3],
       const Ipp16s value[3]))
IPPAPI(IppStatus,ippiThreshold_GTVal_32f_AC4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, const Ipp32f threshold[3],
       const Ipp32f value[3]))
IPPAPI(IppStatus,ippiThreshold_GTVal_8u_C1IR,(Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp8u threshold, Ipp8u value))
IPPAPI(IppStatus,ippiThreshold_GTVal_16s_C1IR,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp16s threshold, Ipp16s value))
IPPAPI(IppStatus,ippiThreshold_GTVal_32f_C1IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp32f threshold, Ipp32f value))
IPPAPI(IppStatus,ippiThreshold_GTVal_8u_C3IR,(Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp8u threshold[3], const Ipp8u value[3]))
IPPAPI(IppStatus,ippiThreshold_GTVal_16s_C3IR,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16s threshold[3], const Ipp16s value[3]))
IPPAPI(IppStatus,ippiThreshold_GTVal_32f_C3IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp32f threshold[3], const Ipp32f value[3]))
IPPAPI(IppStatus,ippiThreshold_GTVal_8u_AC4IR,(Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp8u threshold[3], const Ipp8u value[3]))
IPPAPI(IppStatus,ippiThreshold_GTVal_16s_AC4IR,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16s threshold[3], const Ipp16s value[3]))
IPPAPI(IppStatus,ippiThreshold_GTVal_32f_AC4IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp32f threshold[3], const Ipp32f value[3]))
IPPAPI(IppStatus,ippiThreshold_GTVal_8u_C4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp8u threshold[4],
       const Ipp8u value[4]))
IPPAPI(IppStatus,ippiThreshold_GTVal_16s_C4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, const Ipp16s threshold[4],
       const Ipp16s value[4]))
IPPAPI(IppStatus,ippiThreshold_GTVal_32f_C4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, const Ipp32f threshold[4],
       const Ipp32f value[4]))
IPPAPI(IppStatus,ippiThreshold_GTVal_8u_C4IR,(Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp8u threshold[4], const Ipp8u value[4]))
IPPAPI(IppStatus,ippiThreshold_GTVal_16s_C4IR,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16s threshold[4], const Ipp16s value[4]))
IPPAPI(IppStatus,ippiThreshold_GTVal_32f_C4IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp32f threshold[4], const Ipp32f value[4]))
IPPAPI(IppStatus,ippiThreshold_GTVal_16u_C1R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, Ipp16u threshold,
       Ipp16u value))
IPPAPI(IppStatus,ippiThreshold_GTVal_16u_C3R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, const Ipp16u threshold[3],
       const Ipp16u value[3]))
IPPAPI(IppStatus,ippiThreshold_GTVal_16u_AC4R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, const Ipp16u threshold[3],
       const Ipp16u value[3]))
IPPAPI(IppStatus,ippiThreshold_GTVal_16u_C1IR,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp16u threshold, Ipp16u value))
IPPAPI(IppStatus,ippiThreshold_GTVal_16u_C3IR,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16u threshold[3], const Ipp16u value[3]))
IPPAPI(IppStatus,ippiThreshold_GTVal_16u_AC4IR,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16u threshold[3], const Ipp16u value[3]))
IPPAPI(IppStatus,ippiThreshold_GTVal_16u_C4R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, const Ipp16u threshold[4],
       const Ipp16u value[4]))
IPPAPI(IppStatus,ippiThreshold_GTVal_16u_C4IR,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16u threshold[4], const Ipp16u value[4]))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiThreshold_LTVal_8u_C1R
//              ippiThreshold_LTVal_8u_C3R
//              ippiThreshold_LTVal_8u_AC4R
//              ippiThreshold_LTVal_16s_C1R
//              ippiThreshold_LTVal_16s_C3R
//              ippiThreshold_LTVal_16s_AC4R
//              ippiThreshold_LTVal_32f_C1R
//              ippiThreshold_LTVal_32f_C3R
//              ippiThreshold_LTVal_32f_AC4R
//              ippiThreshold_LTVal_8u_C1IR
//              ippiThreshold_LTVal_8u_C3IR
//              ippiThreshold_LTVal_8u_AC4IR
//              ippiThreshold_LTVal_16s_C1IR
//              ippiThreshold_LTVal_16s_C3IR
//              ippiThreshold_LTVal_16s_AC4IR
//              ippiThreshold_LTVal_32f_C1IR
//              ippiThreshold_LTVal_32f_C3IR
//              ippiThreshold_LTVal_32f_AC4IR
//              ippiThreshold_LTVal_8u_C4R
//              ippiThreshold_LTVal_16s_C4R
//              ippiThreshold_LTVal_32f_C4R
//              ippiThreshold_LTVal_8u_C4IR
//              ippiThreshold_LTVal_16s_C4IR
//              ippiThreshold_LTVal_32f_C4IR
//              ippiThreshold_LTVal_16u_C1R
//              ippiThreshold_LTVal_16u_C3R
//              ippiThreshold_LTVal_16u_AC4R
//              ippiThreshold_LTVal_16u_C1IR
//              ippiThreshold_LTVal_16u_C3IR
//              ippiThreshold_LTVal_16u_AC4IR
//              ippiThreshold_LTVal_16u_C4R
//              ippiThreshold_LTVal_16u_C4IR
//
//  Purpose:  Performs thresholding of pixel values: pixels that are
//            less than threshold, are set to a specified value
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  One of the pointers is NULL
//   ippStsSizeErr     roiSize has a field with zero or negative value
//   ippStsStepErr     One of the step values is zero or negative
//
//  Parameters:
//   pSrc       Pointer to the source image
//   srcStep    Step through the source image
//   pDst       Pointer to the destination image
//   dstStep    Step through the destination image
//   pSrcDst    Pointer to the source/destination image (in-place flavors)
//   srcDstStep Step through the source/destination image (in-place flavors)
//   roiSize    Size of the ROI
//   threshold  Threshold level value (array of values for multi-channel data)
//   value      The output value (array or values for multi-channel data)
*/
IPPAPI(IppStatus,ippiThreshold_LTVal_8u_C1R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, Ipp8u threshold,
       Ipp8u value))
IPPAPI(IppStatus,ippiThreshold_LTVal_16s_C1R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, Ipp16s threshold,
       Ipp16s value))
IPPAPI(IppStatus,ippiThreshold_LTVal_32f_C1R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, Ipp32f threshold,
       Ipp32f value))
IPPAPI(IppStatus,ippiThreshold_LTVal_8u_C3R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp8u threshold[3],
       const Ipp8u value[3]))
IPPAPI(IppStatus,ippiThreshold_LTVal_16s_C3R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, const Ipp16s threshold[3],
       const Ipp16s value[3]))
IPPAPI(IppStatus,ippiThreshold_LTVal_32f_C3R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, const Ipp32f threshold[3],
       const Ipp32f value[3]))
IPPAPI(IppStatus,ippiThreshold_LTVal_8u_AC4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp8u threshold[3],
       const Ipp8u value[3]))
IPPAPI(IppStatus,ippiThreshold_LTVal_16s_AC4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, const Ipp16s threshold[3],
       const Ipp16s value[3]))
IPPAPI(IppStatus,ippiThreshold_LTVal_32f_AC4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, const Ipp32f threshold[3],
       const Ipp32f value[3]))
IPPAPI(IppStatus,ippiThreshold_LTVal_8u_C1IR,(Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp8u threshold, Ipp8u value))
IPPAPI(IppStatus,ippiThreshold_LTVal_16s_C1IR,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp16s threshold, Ipp16s value))
IPPAPI(IppStatus,ippiThreshold_LTVal_32f_C1IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp32f threshold, Ipp32f value))
IPPAPI(IppStatus,ippiThreshold_LTVal_8u_C3IR,(Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp8u threshold[3], const Ipp8u value[3]))
IPPAPI(IppStatus,ippiThreshold_LTVal_16s_C3IR,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16s threshold[3], const Ipp16s value[3]))
IPPAPI(IppStatus,ippiThreshold_LTVal_32f_C3IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp32f threshold[3], const Ipp32f value[3]))
IPPAPI(IppStatus,ippiThreshold_LTVal_8u_AC4IR,(Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp8u threshold[3], const Ipp8u value[3]))
IPPAPI(IppStatus,ippiThreshold_LTVal_16s_AC4IR,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16s threshold[3], const Ipp16s value[3]))
IPPAPI(IppStatus,ippiThreshold_LTVal_32f_AC4IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp32f threshold[3], const Ipp32f value[3]))
IPPAPI(IppStatus,ippiThreshold_LTVal_8u_C4R,(const Ipp8u* pSrc, int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp8u threshold[4],
       const Ipp8u value[4]))
IPPAPI(IppStatus,ippiThreshold_LTVal_16s_C4R,(const Ipp16s* pSrc, int srcStep,
       Ipp16s* pDst, int dstStep, IppiSize roiSize, const Ipp16s threshold[4],
       const Ipp16s value[4]))
IPPAPI(IppStatus,ippiThreshold_LTVal_32f_C4R,(const Ipp32f* pSrc, int srcStep,
       Ipp32f* pDst, int dstStep, IppiSize roiSize, const Ipp32f threshold[4],
       const Ipp32f value[4]))
IPPAPI(IppStatus,ippiThreshold_LTVal_8u_C4IR,(Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp8u threshold[4], const Ipp8u value[4]))
IPPAPI(IppStatus,ippiThreshold_LTVal_16s_C4IR,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16s threshold[4], const Ipp16s value[4]))
IPPAPI(IppStatus,ippiThreshold_LTVal_32f_C4IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp32f threshold[4], const Ipp32f value[4]))
IPPAPI(IppStatus,ippiThreshold_LTVal_16u_C1R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, Ipp16u threshold,
       Ipp16u value))
IPPAPI(IppStatus,ippiThreshold_LTVal_16u_C3R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, const Ipp16u threshold[3],
       const Ipp16u value[3]))
IPPAPI(IppStatus,ippiThreshold_LTVal_16u_AC4R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, const Ipp16u threshold[3],
       const Ipp16u value[3]))
IPPAPI(IppStatus,ippiThreshold_LTVal_16u_C1IR,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp16u threshold, Ipp16u value))
IPPAPI(IppStatus,ippiThreshold_LTVal_16u_C3IR,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16u threshold[3], const Ipp16u value[3]))
IPPAPI(IppStatus,ippiThreshold_LTVal_16u_AC4IR,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16u threshold[3], const Ipp16u value[3]))
IPPAPI(IppStatus,ippiThreshold_LTVal_16u_C4R,(const Ipp16u* pSrc, int srcStep,
       Ipp16u* pDst, int dstStep, IppiSize roiSize, const Ipp16u threshold[4],
       const Ipp16u value[4]))
IPPAPI(IppStatus,ippiThreshold_LTVal_16u_C4IR,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16u threshold[4], const Ipp16u value[4]))

/* ////////////////////////////////////////////////////////////////////////////
//  Names:      ippiThreshold_LTValGTVal_8u_C1R
//              ippiThreshold_LTValGTVal_8u_C3R
//              ippiThreshold_LTValGTVal_8u_AC4R
//              ippiThreshold_LTValGTVal_16s_C1R
//              ippiThreshold_LTValGTVal_16s_C3R
//              ippiThreshold_LTValGTVal_16s_AC4R
//              ippiThreshold_LTValGTVal_32f_C1R
//              ippiThreshold_LTValGTVal_32f_C3R
//              ippiThreshold_LTValGTVal_32f_AC4R
//              ippiThreshold_LTValGTVal_16u_C1R
//              ippiThreshold_LTValGTVal_16u_C3R
//              ippiThreshold_LTValGTVal_16u_AC4R
//
//  Purpose:    Performs double thresholding of pixel values
//  Returns:
//   ippStsNoErr        OK
//   ippStsNullPtrErr   One of the pointers is NULL
//   ippStsSizeErr      roiSize has a field with zero or negative value
//   ippStsThresholdErr thresholdLT > thresholdGT
//   ippStsStepErr      One of the step values is zero or negative
//
//  Parameters:
///  Parameters:
//   pSrc        Pointer to the source image
//   srcStep     Step through the source image
//   pDst        Pointer to the destination image
//   dstStep     Step through the destination image
//   pSrcDst     Pointer to the source/destination image (in-place flavors)
//   srcDstStep  Step through the source/destination image (in-place flavors)
//   roiSize     Size of the ROI
//   thresholdLT Lower threshold value (array of values for multi-channel data)
//   valueLT     Lower output value (array or values for multi-channel data)
//   thresholdGT Upper threshold value (array of values for multi-channel data)
//   valueGT     Upper output value (array or values for multi-channel data)
*/
IPPAPI(IppStatus,ippiThreshold_LTValGTVal_8u_C1R,(const Ipp8u* pSrc,int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, Ipp8u thresholdLT,
       Ipp8u valueLT, Ipp8u thresholdGT, Ipp8u valueGT))
IPPAPI(IppStatus,ippiThreshold_LTValGTVal_16s_C1R,(const Ipp16s* pSrc,
       int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize,
       Ipp16s thresholdLT, Ipp16s valueLT, Ipp16s thresholdGT,
       Ipp16s valueGT))
IPPAPI(IppStatus,ippiThreshold_LTValGTVal_32f_C1R,(const Ipp32f* pSrc,
       int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize,
       Ipp32f thresholdLT, Ipp32f valueLT, Ipp32f thresholdGT,
       Ipp32f valueGT))
IPPAPI(IppStatus,ippiThreshold_LTValGTVal_8u_C3R,(const Ipp8u* pSrc,int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp8u thresholdLT[3],
       const Ipp8u valueLT[3], const Ipp8u thresholdGT[3],
       const Ipp8u valueGT[3]))
IPPAPI(IppStatus,ippiThreshold_LTValGTVal_16s_C3R,(const Ipp16s* pSrc,
       int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize,
       const Ipp16s thresholdLT[3], const Ipp16s valueLT[3],
       const Ipp16s thresholdGT[3], const Ipp16s valueGT[3]))
IPPAPI(IppStatus,ippiThreshold_LTValGTVal_32f_C3R,(const Ipp32f* pSrc,
       int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize,
       const Ipp32f thresholdLT[3], const Ipp32f valueLT[3],
       const Ipp32f thresholdGT[3], const Ipp32f valueGT[3]))
IPPAPI(IppStatus,ippiThreshold_LTValGTVal_8u_AC4R,(const Ipp8u* pSrc,int srcStep,
       Ipp8u* pDst, int dstStep, IppiSize roiSize, const Ipp8u thresholdLT[3],
       const Ipp8u valueLT[3], const Ipp8u thresholdGT[3],
       const Ipp8u valueGT[3]))
IPPAPI(IppStatus,ippiThreshold_LTValGTVal_16s_AC4R,(const Ipp16s* pSrc,
       int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize,
       const Ipp16s thresholdLT[3], const Ipp16s valueLT[3],
       const Ipp16s thresholdGT[3], const Ipp16s valueGT[3]))
IPPAPI(IppStatus,ippiThreshold_LTValGTVal_32f_AC4R,(const Ipp32f* pSrc,
       int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize,
       const Ipp32f thresholdLT[3], const Ipp32f valueLT[3],
       const Ipp32f thresholdGT[3], const Ipp32f valueGT[3]))
IPPAPI(IppStatus,ippiThreshold_LTValGTVal_8u_C1IR,(Ipp8u* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp8u thresholdLT, Ipp8u valueLT, Ipp8u thresholdGT,
       Ipp8u valueGT))
IPPAPI(IppStatus,ippiThreshold_LTValGTVal_16s_C1IR,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp16s thresholdLT, Ipp16s valueLT, Ipp16s thresholdGT,
       Ipp16s valueGT))
IPPAPI(IppStatus,ippiThreshold_LTValGTVal_32f_C1IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp32f thresholdLT, Ipp32f valueLT, Ipp32f thresholdGT,
       Ipp32f valueGT))
IPPAPI(IppStatus,ippiThreshold_LTValGTVal_8u_C3IR,(Ipp8u* pSrcDst,int srcDstStep,
       IppiSize roiSize, const Ipp8u thresholdLT[3], const Ipp8u valueLT[3],
       const Ipp8u thresholdGT[3], const Ipp8u valueGT[3]))
IPPAPI(IppStatus,ippiThreshold_LTValGTVal_16s_C3IR,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16s thresholdLT[3], const Ipp16s valueLT[3],
       const Ipp16s thresholdGT[3], const Ipp16s valueGT[3]))
IPPAPI(IppStatus,ippiThreshold_LTValGTVal_32f_C3IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize,  const Ipp32f thresholdLT[3], const Ipp32f valueLT[3],
       const Ipp32f thresholdGT[3], const Ipp32f valueGT[3]))
IPPAPI(IppStatus,ippiThreshold_LTValGTVal_8u_AC4IR,(Ipp8u* pSrcDst,int srcDstStep,
       IppiSize roiSize, const Ipp8u thresholdLT[3], const Ipp8u valueLT[3],
       const Ipp8u thresholdGT[3], const Ipp8u valueGT[3]))
IPPAPI(IppStatus,ippiThreshold_LTValGTVal_16s_AC4IR,(Ipp16s* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16s thresholdLT[3], const Ipp16s valueLT[3],
       const Ipp16s thresholdGT[3], const Ipp16s valueGT[3]))
IPPAPI(IppStatus,ippiThreshold_LTValGTVal_32f_AC4IR,(Ipp32f* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp32f thresholdLT[3], const Ipp32f valueLT[3],
       const Ipp32f thresholdGT[3], const Ipp32f valueGT[3]))

IPPAPI(IppStatus,ippiThreshold_LTValGTVal_16u_C1R,(const Ipp16u* pSrc,
       int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize,
       Ipp16u thresholdLT, Ipp16u valueLT, Ipp16u thresholdGT,
       Ipp16u valueGT))
IPPAPI(IppStatus,ippiThreshold_LTValGTVal_16u_C3R,(const Ipp16u* pSrc,
       int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize,
       const Ipp16u thresholdLT[3], const Ipp16u valueLT[3],
       const Ipp16u thresholdGT[3], const Ipp16u valueGT[3]))
IPPAPI(IppStatus,ippiThreshold_LTValGTVal_16u_AC4R,(const Ipp16u* pSrc,
       int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize,
       const Ipp16u thresholdLT[3], const Ipp16u valueLT[3],
       const Ipp16u thresholdGT[3], const Ipp16u valueGT[3]))
IPPAPI(IppStatus,ippiThreshold_LTValGTVal_16u_C1IR,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, Ipp16u thresholdLT, Ipp16u valueLT, Ipp16u thresholdGT,
       Ipp16u valueGT))
IPPAPI(IppStatus,ippiThreshold_LTValGTVal_16u_C3IR,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16u thresholdLT[3], const Ipp16u valueLT[3],
       const Ipp16u thresholdGT[3], const Ipp16u valueGT[3]))
IPPAPI(IppStatus,ippiThreshold_LTValGTVal_16u_AC4IR,(Ipp16u* pSrcDst, int srcDstStep,
       IppiSize roiSize, const Ipp16u thresholdLT[3], const Ipp16u valueLT[3],
       const Ipp16u thresholdGT[3], const Ipp16u valueGT[3]))

/*F/////////////////////////////////////////////////////////////////////////////////
//  Name: ippiComputeThreshold_Otsu_8u_C1R
//
//  Purpose: Calculate Otsu theshold value of images
//    Return:
//      ippStsNoErr              Ok
//      ippStsNullPtrErr         One of pointers is NULL
//      ippStsSizeErr            The width or height of images is less or equal zero
//      ippStsStepErr            The steps in images is less ROI
//    Parameters:
//      pSrc                     Pointer to image
//      srcStep                  Image step
//      roiSize                  Size of image ROI
//      pThreshold               Returned Otsu theshold value
//
//F*/

IPPAPI (IppStatus, ippiComputeThreshold_Otsu_8u_C1R, (const Ipp8u* pSrc, int srcStep,
        IppiSize roiSize, Ipp8u* pThreshold))

/* /////////////////////////////////////////////////////////////////////////////
//                     Adaptive threshold functions
// /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiThresholdAdaptiveBoxGetBufferSize
//              ippiThresholdAdaptiveGaussGetBufferSize
//  Purpose:    to define spec and buffer sizes for adaptive threshold
//  Parameters:
//   roiSize       Size of the destination ROI in pixels.
//   maskSize      Size of kernel for calculation of threshold level.
//                 Width and height of maskSize must be equal and odd.
//   dataType      Data type of the source and destination images. Possible value is ipp8u.
//   numChannels   Number of channels in the images. Possible value is 1.
//   pSpecSize     Pointer to the computed value of the spec size.
//   pBufferSize   Pointer to the computed value of the external buffer size.
//  Return:
//    ippStsNoErr               OK
//    ippStsNullPtrErr          any pointer is NULL
//    ippStsSizeErr             size of dstRoiSize is less or equal 0
//    ippStsMaskSizeErr         fields of maskSize are not equak or ones are less or equal 0
//    ippStsDataTypeErr         Indicates an error when dataType has an illegal value.
//    ippStsNumChannelsErr      Indicates an error when numChannels has an illegal value.
*/
IPPAPI(IppStatus,ippiThresholdAdaptiveBoxGetBufferSize,
       (IppiSize roiSize, IppiSize maskSize, IppDataType dataType, int numChannels, int *pBufferSize))
IPPAPI(IppStatus,ippiThresholdAdaptiveGaussGetBufferSize,
       (IppiSize roiSize, IppiSize maskSize, IppDataType dataType, int numChannels, int *pSpecSize, int *pBufferSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFilterThresholdGaussAdaptiveInit
//  Purpose:    initialization of Spec for adaptive threshold
//  Parameters:
//   roiSize       Size of the destination ROI in pixels.
//   maskSize      Size of kernel for calculation of threshold level.
//                 Width and height of maskSize must be equal and odd.
//   dataType      Data type of the source and destination images. Possible value is ipp8u.
//   numChannels   Number of channels in the images. Possible value is 1.
//   sigma         value of sigma for calculation of threshold level for Gauss-method,
//                 if sigma value is less or equal zero than sigma is set automatically
//                 in compliance with kernel size, in this cases
//                 sigma = 0.3*(maskSize.width-1)*0.5-1)+0.8;
//   pSpec         pointer to Spec
//  Return:
//    ippStsNoErr               OK
//    ippStsNullPtrErr          pointer to Spec is NULL
//    ippStsSizeErr             size of dstRoiSize is less or equal 0
//    ippStsMaskSizeErr         size of kernel for calculation of threshold level.
//                              Width and height of maskSize must be equal and odd.
//    ippStsDataTypeErr         Indicates an error when dataType has an illegal value.
//    ippStsNumChannelsErr      Indicates an error when numChannels has an illegal value.
*/
IPPAPI(IppStatus,ippiThresholdAdaptiveGaussInit,
       (IppiSize roiSize, IppiSize maskSize, IppDataType dataType, int numChannels,
       Ipp32f sigma, IppiThresholdAdaptiveSpec *pSpec))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiThresholdAdaptiveBox_8u_C1R
//              ippiThresholdAdaptiveThreshold_8u_C1R
//  Purpose:    to executes adaptive threshold operation
//  Parameters:
//   pSrc          Pointer to the source image ROI.
//   srcStep       Distance in bytes between starts of consecutive lines in the source image.
//   pDst          Pointer to the destination image ROI.
//   dstStep       Distance in bytes between starts of consecutive lines in the destination image.
//   dstRoiSize    Size of the destination ROI in pixels.
//   maskSize      Size of kernel for calculation of threshold level.
//                 Width and height of maskSize must be equal and odd.
//   delta         value for calculation of threshold (subtrahend).
//   valGT         output pixel if source pixel is great then threshold.
//   valLE         output pixel if source pixel is less or equal threshold.
/    borderType    Type of border.
//   borderValue   Constant value to assign to pixels of the constant border. This parameter is applicable
//                 only to the ippBorderConst border type.
//   pSpecSize     Pointer to the computed value of the spec size.
//   pBufferSize   Pointer to the computed value of the external buffer size.
//  Return:
//    ippStsNoErr           OK
//    ippStsNullPtrErr      any pointer is NULL
//    ippStsSizeErr         size of dstRoiSize is less or equal 0
//    ippStsMaskSizeErr     one of the fields of maskSize has a negative or zero value or
//                          if the fields of maskSize are not equal
//    ippStsContextMatchErr spec is not match
//    ippStsBorderErr       Indicates an error when borderType has illegal value.
//
//     Output pixels are calculated such:
//     pDst(x,y) = valGT if (pSrc(x,y) > T(x,y))
//     and
//     pDst(x,y) = valLE if (pSrc(x,y) <= T(x,y))

//     For ippiThresholdAdaptiveBox_8u_C1R:
//     T(x,y) is a mean of the kernelSize.width*kernelSize.height neighborhood of (x,y)-pixel
//     minus delta.
//
//     For ippiThresholdAdaptiveGauss_8u_C1R:
//     T(x,y) is a weighted sum (cross-correlation with a Gaussian window) of
//     the kernelSize.width*kernelSize.height neighborhood of (x,y)-pixel minus delta.
//     Coefficients of Gaussian window is separable.
//     Coefficients for row of separable Gaussian window:
//     Gi = A * exp(-(i-(kernelSize.width-1)/2)^2/(0.5 * sigma^2),
//     A is scale factor for
//     SUM(Gi) = 1 (i = 0,...,maskSize.width-1).
*/
IPPAPI(IppStatus,ippiThresholdAdaptiveBox_8u_C1R,
       (const Ipp8u *pSrc, int srcStep, Ipp8u *pDst, int dstStep, IppiSize roiSize, IppiSize maskSize,
       Ipp32f delta, Ipp8u valGT, Ipp8u valLE, IppiBorderType borderType, Ipp8u borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus,ippiThresholdAdaptiveGauss_8u_C1R,
       (const Ipp8u *pSrc, int srcStep, Ipp8u *pDst, int dstStep, IppiSize roiSize, Ipp32f delta,
       Ipp8u valGT, Ipp8u valLE, IppiBorderType borderType, Ipp8u borderValue,
       IppiThresholdAdaptiveSpec *pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus,ippiThresholdAdaptiveBox_8u_C1IR,
       (Ipp8u *pSrcDst, int srcDstStep, IppiSize roiSize, IppiSize maskSize,
       Ipp32f delta, Ipp8u valGT, Ipp8u valLE, IppiBorderType borderType, Ipp8u borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus,ippiThresholdAdaptiveGauss_8u_C1IR,
       (Ipp8u *pSrcDst, int srcDstStep, IppiSize roiSize, Ipp32f delta,
       Ipp8u valGT, Ipp8u valLE, IppiBorderType borderType, Ipp8u borderValue,
       IppiThresholdAdaptiveSpec *pSpec, Ipp8u* pBuffer))



/* /////////////////////////////////////////////////////////////////////////////
//                   Convert and Initialization functions
///////////////////////////////////////////////////////////////////////////// */
/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiCopyManaged
//
//  Purpose:  copy pixel values from the source image to the destination  image
//
//
//  Returns:
//    ippStsNullPtrErr  One of the pointers is NULL
//    ippStsSizeErr     roiSize has a field with zero or negative value
//    ippStsNoErr       OK
//
//  Parameters:
//    pSrc              Pointer  to the source image buffer
//    srcStep           Step in bytes through the source image buffer
//    pDst              Pointer to the  destination image buffer
//    dstStep           Step in bytes through the destination image buffer
//    roiSize           Size of the ROI
//    flags             The logic sum of tags sets type of copying.
//                      (IPP_TEMPORAL_COPY,IPP_NONTEMPORAL_STORE etc.)
*/

IPPAPI( IppStatus, ippiCopyManaged_8u_C1R,
                   ( const Ipp8u* pSrc, int srcStep,
                           Ipp8u* pDst, int dstStep,
                      IppiSize roiSize, int flags ))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiCopy
//
//  Purpose:  copy pixel values from the source image to the destination  image
//
//
//  Returns:
//    ippStsNullPtrErr  One of the pointers is NULL
//    ippStsSizeErr     roiSize has a field with zero or negative value
//    ippStsNoErr       OK
//
//  Parameters:
//    pSrc              Pointer  to the source image buffer
//    srcStep           Step in bytes through the source image buffer
//    pDst              Pointer to the  destination image buffer
//    dstStep           Step in bytes through the destination image buffer
//    roiSize           Size of the ROI
//    pMask             Pointer to the mask image buffer
//    maskStep          Step in bytes through the mask image buffer
*/

IPPAPI( IppStatus, ippiCopy_8u_C3C1R,
                   ( const Ipp8u* pSrc, int srcStep,
                     Ipp8u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_8u_C1C3R,
                   ( const Ipp8u* pSrc, int srcStep,
                     Ipp8u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_8u_C4C1R,
                   ( const Ipp8u* pSrc, int srcStep,
                     Ipp8u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_8u_C1C4R,
                   ( const Ipp8u* pSrc, int srcStep,
                     Ipp8u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_8u_C3CR,
                   ( const Ipp8u* pSrc, int srcStep,
                     Ipp8u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_8u_C4CR,
                   ( const Ipp8u* pSrc, int srcStep,
                     Ipp8u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_8u_AC4C3R,
                   ( const Ipp8u* pSrc, int srcStep,
                     Ipp8u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_8u_C3AC4R,
                   ( const Ipp8u* pSrc, int srcStep,
                     Ipp8u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_8u_C1R,
                    ( const Ipp8u* pSrc, int srcStep,
                      Ipp8u* pDst, int dstStep,IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_8u_C3R,
                    ( const Ipp8u* pSrc, int srcStep,
                      Ipp8u* pDst, int dstStep,IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_8u_C4R,
                    ( const Ipp8u* pSrc, int srcStep,
                      Ipp8u* pDst, int dstStep,IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_8u_AC4R,
                    ( const Ipp8u* pSrc, int srcStep,
                      Ipp8u* pDst, int dstStep,IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_8u_C1MR,
                    ( const Ipp8u* pSrc, int srcStep,
                      Ipp8u* pDst, int dstStep,IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiCopy_8u_C3MR,
                    ( const Ipp8u* pSrc, int srcStep,
                      Ipp8u* pDst, int dstStep,IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiCopy_8u_C4MR,
                    ( const Ipp8u* pSrc, int srcStep,
                      Ipp8u* pDst, int dstStep,IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiCopy_8u_AC4MR,
                    ( const Ipp8u* pSrc, int srcStep,
                      Ipp8u* pDst, int dstStep,IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI( IppStatus, ippiCopy_16s_C3C1R,
                   ( const Ipp16s* pSrc, int srcStep,
                     Ipp16s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_16s_C1C3R,
                   ( const Ipp16s* pSrc, int srcStep,
                     Ipp16s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_16s_C4C1R,
                   ( const Ipp16s* pSrc, int srcStep,
                     Ipp16s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_16s_C1C4R,
                   ( const Ipp16s* pSrc, int srcStep,
                     Ipp16s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_16s_C3CR,
                   ( const Ipp16s* pSrc, int srcStep,
                     Ipp16s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_16s_C4CR,
                   ( const Ipp16s* pSrc, int srcStep,
                     Ipp16s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_16s_AC4C3R,
                   ( const Ipp16s* pSrc, int srcStep,
                     Ipp16s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_16s_C3AC4R,
                   ( const Ipp16s* pSrc, int srcStep,
                     Ipp16s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_16s_C1R,
                    ( const Ipp16s* pSrc, int srcStep,
                      Ipp16s* pDst, int dstStep,IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_16s_C3R,
                    ( const Ipp16s* pSrc, int srcStep,
                      Ipp16s* pDst, int dstStep,IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_16s_C4R,
                    ( const Ipp16s* pSrc, int srcStep,
                      Ipp16s* pDst, int dstStep,IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_16s_AC4R,
                    ( const Ipp16s* pSrc, int srcStep,
                      Ipp16s* pDst, int dstStep,IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_16s_C1MR,
                    ( const Ipp16s* pSrc, int srcStep,
                      Ipp16s* pDst, int dstStep,IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiCopy_16s_C3MR,
                    ( const Ipp16s* pSrc, int srcStep,
                      Ipp16s* pDst, int dstStep,IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiCopy_16s_C4MR,
                    ( const Ipp16s* pSrc, int srcStep,
                      Ipp16s* pDst, int dstStep,IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiCopy_16s_AC4MR,
                    ( const Ipp16s* pSrc, int srcStep,
                      Ipp16s* pDst, int dstStep,IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI( IppStatus, ippiCopy_32f_C3C1R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_32f_C1C3R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_32f_C4C1R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_32f_C1C4R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_32f_C3CR,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_32f_C4CR,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_32f_AC4C3R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_32f_C3AC4R,
                   ( const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_32f_C1R,
                    ( const Ipp32f* pSrc, int srcStep,
                      Ipp32f* pDst, int dstStep,IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_32f_C3R,
                    ( const Ipp32f* pSrc, int srcStep,
                      Ipp32f* pDst, int dstStep,IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_32f_C4R,
                    ( const Ipp32f* pSrc, int srcStep,
                      Ipp32f* pDst, int dstStep,IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_32f_AC4R,
                    ( const Ipp32f* pSrc, int srcStep,
                      Ipp32f* pDst, int dstStep,IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_32f_C1MR,
                    ( const Ipp32f* pSrc, int srcStep,
                      Ipp32f* pDst, int dstStep,IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiCopy_32f_C3MR,
                    ( const Ipp32f* pSrc, int srcStep,
                      Ipp32f* pDst, int dstStep,IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiCopy_32f_C4MR,
                    ( const Ipp32f* pSrc, int srcStep,
                      Ipp32f* pDst, int dstStep,IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiCopy_32f_AC4MR,
                    ( const Ipp32f* pSrc, int srcStep,
                      Ipp32f* pDst, int dstStep,IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiCopy_8u_C3P3R, ( const Ipp8u* pSrc, int srcStep,
                    Ipp8u* const pDst[3], int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_8u_P3C3R, (const  Ipp8u* const pSrc[3],
                            int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_8u_C4P4R, ( const Ipp8u* pSrc, int srcStep,
                    Ipp8u* const pDst[4], int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_8u_P4C4R, (const  Ipp8u* const pSrc[4],
                            int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_16s_C3P3R, ( const Ipp16s* pSrc, int srcStep,
                    Ipp16s* const pDst[3], int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_16s_P3C3R, (const  Ipp16s* const pSrc[3],
                            int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_16s_C4P4R, ( const Ipp16s* pSrc, int srcStep,
                    Ipp16s* const pDst[4], int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_16s_P4C4R, (const  Ipp16s* const pSrc[4],
                            int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_32f_C3P3R, ( const Ipp32f* pSrc, int srcStep,
                    Ipp32f* const pDst[3], int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_32f_P3C3R, (const  Ipp32f* const pSrc[3],
                            int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_32f_C4P4R, ( const Ipp32f* pSrc, int srcStep,
                    Ipp32f* const pDst[4], int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_32f_P4C4R, (const  Ipp32f* const pSrc[4],
                            int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_32s_C3C1R,
                   ( const Ipp32s* pSrc, int srcStep,
                     Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_32s_C1C3R,
                   ( const Ipp32s* pSrc, int srcStep,
                     Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_32s_C4C1R,
                   ( const Ipp32s* pSrc, int srcStep,
                     Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_32s_C1C4R,
                   ( const Ipp32s* pSrc, int srcStep,
                     Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_32s_C3CR,
                   ( const Ipp32s* pSrc, int srcStep,
                     Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_32s_C4CR,
                   ( const Ipp32s* pSrc, int srcStep,
                     Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_32s_AC4C3R,
                   ( const Ipp32s* pSrc, int srcStep,
                     Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_32s_C3AC4R,
                   ( const Ipp32s* pSrc, int srcStep,
                     Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_32s_C1R,
                    ( const Ipp32s* pSrc, int srcStep,
                      Ipp32s* pDst, int dstStep,IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_32s_C3R,
                    ( const Ipp32s* pSrc, int srcStep,
                      Ipp32s* pDst, int dstStep,IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_32s_C4R,
                    ( const Ipp32s* pSrc, int srcStep,
                      Ipp32s* pDst, int dstStep,IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_32s_AC4R,
                    ( const Ipp32s* pSrc, int srcStep,
                      Ipp32s* pDst, int dstStep,IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_32s_C1MR,
                    ( const Ipp32s* pSrc, int srcStep,
                      Ipp32s* pDst, int dstStep,IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiCopy_32s_C3MR,
                    ( const Ipp32s* pSrc, int srcStep,
                      Ipp32s* pDst, int dstStep,IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiCopy_32s_C4MR,
                    ( const Ipp32s* pSrc, int srcStep,
                      Ipp32s* pDst, int dstStep,IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiCopy_32s_AC4MR,
                    ( const Ipp32s* pSrc, int srcStep,
                      Ipp32s* pDst, int dstStep,IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiCopy_32s_C3P3R, ( const Ipp32s* pSrc, int srcStep,
                    Ipp32s* const pDst[3], int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_32s_P3C3R, (const  Ipp32s* const pSrc[3],
                            int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_32s_C4P4R, ( const Ipp32s* pSrc, int srcStep,
                    Ipp32s* const pDst[4], int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_32s_P4C4R, (const  Ipp32s* const pSrc[4],
                            int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize ))

IPPAPI( IppStatus, ippiCopy_16u_C3C1R,
                   ( const Ipp16u* pSrc, int srcStep,
                     Ipp16u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_16u_C1C3R,
                   ( const Ipp16u* pSrc, int srcStep,
                     Ipp16u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_16u_C4C1R,
                   ( const Ipp16u* pSrc, int srcStep,
                     Ipp16u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_16u_C1C4R,
                   ( const Ipp16u* pSrc, int srcStep,
                     Ipp16u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_16u_C3CR,
                   ( const Ipp16u* pSrc, int srcStep,
                     Ipp16u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_16u_C4CR,
                   ( const Ipp16u* pSrc, int srcStep,
                     Ipp16u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_16u_AC4C3R,
                   ( const Ipp16u* pSrc, int srcStep,
                     Ipp16u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI( IppStatus, ippiCopy_16u_C3AC4R,
                   ( const Ipp16u* pSrc, int srcStep,
                     Ipp16u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_16u_C1R,
                    ( const Ipp16u* pSrc, int srcStep,
                      Ipp16u* pDst, int dstStep,IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_16u_C3R,
                    ( const Ipp16u* pSrc, int srcStep,
                      Ipp16u* pDst, int dstStep,IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_16u_C4R,
                    ( const Ipp16u* pSrc, int srcStep,
                      Ipp16u* pDst, int dstStep,IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_16u_AC4R,
                    ( const Ipp16u* pSrc, int srcStep,
                      Ipp16u* pDst, int dstStep,IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_16u_C1MR,
                    ( const Ipp16u* pSrc, int srcStep,
                      Ipp16u* pDst, int dstStep,IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiCopy_16u_C3MR,
                    ( const Ipp16u* pSrc, int srcStep,
                      Ipp16u* pDst, int dstStep,IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiCopy_16u_C4MR,
                    ( const Ipp16u* pSrc, int srcStep,
                      Ipp16u* pDst, int dstStep,IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiCopy_16u_AC4MR,
                    ( const Ipp16u* pSrc, int srcStep,
                      Ipp16u* pDst, int dstStep,IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))

IPPAPI ( IppStatus, ippiCopy_16u_C3P3R, ( const Ipp16u* pSrc, int srcStep,
                    Ipp16u* const pDst[3], int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_16u_P3C3R, (const  Ipp16u* const pSrc[3],
                            int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_16u_C4P4R, ( const Ipp16u* pSrc, int srcStep,
                    Ipp16u* const pDst[4], int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiCopy_16u_P4C4R, (const  Ipp16u* const pSrc[4],
                            int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize ))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiCopyReplicateBorder
//
//  Purpose:   Copies pixel values between two buffers and adds
//             the replicated border pixels.
//
//  Returns:
//    ippStsNullPtrErr    One of the pointers is NULL
//    ippStsSizeErr       1). srcRoiSize or dstRoiSize has a field with negative or zero value
//                        2). topBorderHeight or leftBorderWidth is less than zero
//                        3). dstRoiSize.width < srcRoiSize.width + leftBorderWidth
//                        4). dstRoiSize.height < srcRoiSize.height + topBorderHeight
//    ippStsStepErr       srcStep or dstStep is less than or equal to zero
//    ippStsNoErr         OK
//
//  Parameters:
//    pSrc                Pointer  to the source image buffer
//    srcStep             Step in bytes through the source image
//    pDst                Pointer to the  destination image buffer
//    dstStep             Step in bytes through the destination image
//    scrRoiSize          Size of the source ROI in pixels
//    dstRoiSize          Size of the destination ROI in pixels
//    topBorderHeight     Height of the top border in pixels
//    leftBorderWidth     Width of the left border in pixels
*/

IPPAPI(IppStatus, ippiCopyReplicateBorder_8u_C1R, (const Ipp8u* pSrc, int srcStep, IppiSize srcRoiSize, Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, int topBorderHeight, int leftBorderWidth))
IPPAPI (IppStatus, ippiCopyReplicateBorder_8u_C3R,
            ( const Ipp8u* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp8u* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI (IppStatus, ippiCopyReplicateBorder_8u_AC4R,
            ( const Ipp8u* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp8u* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI (IppStatus, ippiCopyReplicateBorder_8u_C4R,
            ( const Ipp8u* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp8u* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI(IppStatus, ippiCopyReplicateBorder_16s_C1R, (const Ipp16s* pSrc, int srcStep, IppiSize srcRoiSize, Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, int topBorderHeight, int leftBorderWidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_16s_C3R, (const Ipp16s* pSrc, int srcStep, IppiSize srcRoiSize, Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, int topBorderHeight, int leftBorderWidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_16s_AC4R, (const Ipp16s* pSrc, int srcStep, IppiSize srcRoiSize, Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, int topBorderHeight, int leftBorderWidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_16s_C4R, (const Ipp16s* pSrc, int srcStep, IppiSize srcRoiSize, Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, int topBorderHeight, int leftBorderWidth))
IPPAPI (IppStatus, ippiCopyReplicateBorder_32s_C1R,
            ( const Ipp32s* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp32s* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI (IppStatus, ippiCopyReplicateBorder_32s_C3R,
            ( const Ipp32s* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp32s* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI (IppStatus, ippiCopyReplicateBorder_32s_AC4R,
            ( const Ipp32s* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp32s* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI (IppStatus, ippiCopyReplicateBorder_32s_C4R,
            ( const Ipp32s* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp32s* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )

IPPAPI ( IppStatus, ippiCopyReplicateBorder_8u_C1IR,
                    ( const Ipp8u* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )
IPPAPI ( IppStatus, ippiCopyReplicateBorder_8u_C3IR,
                    ( const Ipp8u* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )
IPPAPI ( IppStatus, ippiCopyReplicateBorder_8u_AC4IR,
                    ( const Ipp8u* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )
IPPAPI ( IppStatus, ippiCopyReplicateBorder_8u_C4IR,
                    ( const Ipp8u* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )

IPPAPI ( IppStatus, ippiCopyReplicateBorder_16s_C1IR,
                    ( const Ipp16s* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )
IPPAPI ( IppStatus, ippiCopyReplicateBorder_16s_C3IR,
                    ( const Ipp16s* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )
IPPAPI ( IppStatus, ippiCopyReplicateBorder_16s_AC4IR,
                    ( const Ipp16s* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )
IPPAPI ( IppStatus, ippiCopyReplicateBorder_16s_C4IR,
                    ( const Ipp16s* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )

IPPAPI ( IppStatus, ippiCopyReplicateBorder_32s_C1IR,
                    ( const Ipp32s* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )
IPPAPI ( IppStatus, ippiCopyReplicateBorder_32s_C3IR,
                    ( const Ipp32s* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )
IPPAPI ( IppStatus, ippiCopyReplicateBorder_32s_AC4IR,
                    ( const Ipp32s* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )
IPPAPI ( IppStatus, ippiCopyReplicateBorder_32s_C4IR,
                    ( const Ipp32s* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )

IPPAPI ( IppStatus, ippiCopyReplicateBorder_16u_C1IR,
                    ( const Ipp16u* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )
IPPAPI ( IppStatus, ippiCopyReplicateBorder_16u_C3IR,
                    ( const Ipp16u* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )
IPPAPI ( IppStatus, ippiCopyReplicateBorder_16u_AC4IR,
                    ( const Ipp16u* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )
IPPAPI ( IppStatus, ippiCopyReplicateBorder_16u_C4IR,
                    ( const Ipp16u* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )

IPPAPI (IppStatus, ippiCopyReplicateBorder_16u_C1R,
            ( const Ipp16u* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp16u* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI (IppStatus, ippiCopyReplicateBorder_16u_C3R,
            ( const Ipp16u* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp16u* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI (IppStatus, ippiCopyReplicateBorder_16u_AC4R,
            ( const Ipp16u* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp16u* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI (IppStatus, ippiCopyReplicateBorder_16u_C4R,
            ( const Ipp16u* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp16u* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )

IPPAPI (IppStatus, ippiCopyReplicateBorder_32f_C1R,
            ( const Ipp32f* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp32f* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI (IppStatus, ippiCopyReplicateBorder_32f_C3R,
            ( const Ipp32f* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp32f* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI (IppStatus, ippiCopyReplicateBorder_32f_AC4R,
            ( const Ipp32f* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp32f* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI (IppStatus, ippiCopyReplicateBorder_32f_C4R,
            ( const Ipp32f* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp32f* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )

IPPAPI(IppStatus, ippiCopyReplicateBorder_32f_C1IR, (const Ipp32f* pSrc, int srcDstStep, IppiSize srcRoiSize, IppiSize dstRoiSize, int topBorderHeight, int leftborderwidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_32f_C3IR, (const Ipp32f* pSrc, int srcDstStep, IppiSize srcRoiSize, IppiSize dstRoiSize, int topBorderHeight, int leftborderwidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_32f_AC4IR, (const Ipp32f* pSrc, int srcDstStep, IppiSize srcRoiSize, IppiSize dstRoiSize, int topBorderHeight, int leftborderwidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_32f_C4IR, (const Ipp32f* pSrc, int srcDstStep, IppiSize srcRoiSize, IppiSize dstRoiSize, int topBorderHeight, int leftborderwidth))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiCopyConstBorder
//
//  Purpose:    Copies pixel values between two buffers and adds
//              the border pixels with constant value.
//
//  Returns:
//    ippStsNullPtrErr   One of the pointers is NULL
//    ippStsSizeErr      1). srcRoiSize or dstRoiSize has a field with negative or zero value
//                       2). topBorderHeight or leftBorderWidth is less than zero
//                       3). dstRoiSize.width < srcRoiSize.width + leftBorderWidth
//                       4). dstRoiSize.height < srcRoiSize.height + topBorderHeight
//    ippStsStepErr      srcStep or dstStep is less than or equal to zero
//    ippStsNoErr        OK
//
//  Parameters:
//    pSrc               Pointer  to the source image buffer
//    srcStep            Step in bytes through the source image
//    pDst               Pointer to the  destination image buffer
//    dstStep            Step in bytes through the destination image
//    srcRoiSize         Size of the source ROI in pixels
//    dstRoiSize         Size of the destination ROI in pixels
//    topBorderHeight    Height of the top border in pixels
//    leftBorderWidth    Width of the left border in pixels
//    value              Constant value to assign to the border pixels
*/

IPPAPI (IppStatus, ippiCopyConstBorder_8u_C1R,
            ( const Ipp8u* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp8u* pDst,  int dstStep, IppiSize dstRoiSize,
                            int topBorderHeight, int leftBorderWidth,
                            Ipp8u value ) )
IPPAPI (IppStatus, ippiCopyConstBorder_8u_C3R,
            ( const Ipp8u* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp8u* pDst,  int dstStep, IppiSize dstRoiSize,
                            int topBorderHeight, int leftBorderWidth,
                            const Ipp8u value[3] ) )
IPPAPI (IppStatus, ippiCopyConstBorder_8u_AC4R,
            ( const Ipp8u* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp8u* pDst,  int dstStep, IppiSize dstRoiSize,
                            int topBorderHeight, int leftBorderWidth,
                            const Ipp8u value[3] ) )
IPPAPI (IppStatus, ippiCopyConstBorder_8u_C4R,
            ( const Ipp8u* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp8u* pDst,  int dstStep, IppiSize dstRoiSize,
                            int topBorderHeight, int leftBorderWidth,
                            const Ipp8u value[4] ) )
IPPAPI (IppStatus, ippiCopyConstBorder_16s_C1R,
            ( const Ipp16s* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp16s* pDst,  int dstStep, IppiSize dstRoiSize,
                            int topBorderHeight, int leftBorderWidth,
                            Ipp16s value ) )
IPPAPI (IppStatus, ippiCopyConstBorder_16s_C3R,
            ( const Ipp16s* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp16s* pDst,  int dstStep, IppiSize dstRoiSize,
                            int topBorderHeight, int leftBorderWidth,
                            const Ipp16s value[3] ) )
IPPAPI (IppStatus, ippiCopyConstBorder_16s_AC4R,
            ( const Ipp16s* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp16s* pDst,  int dstStep, IppiSize dstRoiSize,
                            int topBorderHeight, int leftBorderWidth,
                            const Ipp16s value[3] ) )
IPPAPI (IppStatus, ippiCopyConstBorder_16s_C4R,
            ( const Ipp16s* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp16s* pDst,  int dstStep, IppiSize dstRoiSize,
                            int topBorderHeight, int leftBorderWidth,
                            const Ipp16s value[4] ) )
IPPAPI (IppStatus, ippiCopyConstBorder_32s_C1R,
            ( const Ipp32s* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp32s* pDst,  int dstStep, IppiSize dstRoiSize,
                            int topBorderHeight, int leftBorderWidth,
                            Ipp32s value ) )
IPPAPI (IppStatus, ippiCopyConstBorder_32s_C3R,
            ( const Ipp32s* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp32s* pDst,  int dstStep, IppiSize dstRoiSize,
                            int topBorderHeight, int leftBorderWidth,
                            const Ipp32s value[3] ) )
IPPAPI (IppStatus, ippiCopyConstBorder_32s_AC4R,
            ( const Ipp32s* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp32s* pDst,  int dstStep, IppiSize dstRoiSize,
                            int topBorderHeight, int leftBorderWidth,
                            const Ipp32s value[3] ) )
IPPAPI (IppStatus, ippiCopyConstBorder_32s_C4R,
            ( const Ipp32s* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp32s* pDst,  int dstStep, IppiSize dstRoiSize,
                            int topBorderHeight, int leftBorderWidth,
                            const Ipp32s value[4] ) )

IPPAPI (IppStatus, ippiCopyConstBorder_16u_C1R,
            ( const Ipp16u* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp16u* pDst,  int dstStep, IppiSize dstRoiSize,
                            int topBorderHeight, int leftBorderWidth,
                            Ipp16u value ) )
IPPAPI (IppStatus, ippiCopyConstBorder_16u_C3R,
            ( const Ipp16u* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp16u* pDst,  int dstStep, IppiSize dstRoiSize,
                            int topBorderHeight, int leftBorderWidth,
                            const Ipp16u value[3] ) )
IPPAPI (IppStatus, ippiCopyConstBorder_16u_AC4R,
            ( const Ipp16u* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp16u* pDst,  int dstStep, IppiSize dstRoiSize,
                            int topBorderHeight, int leftBorderWidth,
                            const Ipp16u value[3] ) )
IPPAPI (IppStatus, ippiCopyConstBorder_16u_C4R,
            ( const Ipp16u* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp16u* pDst,  int dstStep, IppiSize dstRoiSize,
                            int topBorderHeight, int leftBorderWidth,
                            const Ipp16u value[4] ) )

IPPAPI (IppStatus, ippiCopyConstBorder_32f_C1R,
            ( const Ipp32f* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp32f* pDst,  int dstStep, IppiSize dstRoiSize,
                            int topBorderHeight, int leftBorderWidth,
                            Ipp32f value ) )
IPPAPI (IppStatus, ippiCopyConstBorder_32f_C3R,
            ( const Ipp32f* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp32f* pDst,  int dstStep, IppiSize dstRoiSize,
                            int topBorderHeight, int leftBorderWidth,
                            const Ipp32f value[3] ) )
IPPAPI (IppStatus, ippiCopyConstBorder_32f_AC4R,
            ( const Ipp32f* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp32f* pDst,  int dstStep, IppiSize dstRoiSize,
                            int topBorderHeight, int leftBorderWidth,
                            const Ipp32f value[3] ) )
IPPAPI (IppStatus, ippiCopyConstBorder_32f_C4R,
            ( const Ipp32f* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp32f* pDst,  int dstStep, IppiSize dstRoiSize,
                            int topBorderHeight, int leftBorderWidth,
                            const Ipp32f value[4] ) )

IPPAPI (IppStatus, ippiCopyConstBorder_8u_C1IR,
            (Ipp8u* pSrcDst, int srcDstStep, IppiSize srcRoiSize,
             IppiSize dstRoiSize, int topBorderHeight, int
             leftborderwidth, const Ipp8u value))
IPPAPI (IppStatus, ippiCopyConstBorder_8u_C3IR,
            (Ipp8u* pSrcDst, int srcDstStep, IppiSize srcRoiSize,
             IppiSize dstRoiSize, int topBorderHeight, int
             leftborderwidth, const Ipp8u value[3]))
IPPAPI (IppStatus, ippiCopyConstBorder_8u_AC4IR,
            (Ipp8u* pSrcDst, int srcDstStep, IppiSize srcRoiSize,
             IppiSize dstRoiSize, int topBorderHeight, int
             leftborderwidth, const Ipp8u value[3]))
IPPAPI (IppStatus, ippiCopyConstBorder_8u_C4IR,
            (Ipp8u* pSrcDst, int srcDstStep, IppiSize srcRoiSize,
             IppiSize dstRoiSize, int topBorderHeight, int
             leftborderwidth, const Ipp8u value[4]))

IPPAPI (IppStatus, ippiCopyConstBorder_16u_C1IR,
            (Ipp16u* pSrcDst, int srcDstStep, IppiSize srcRoiSize,
             IppiSize dstRoiSize, int topBorderHeight, int
             leftborderwidth, const Ipp16u value))
IPPAPI (IppStatus, ippiCopyConstBorder_16u_C3IR,
            (Ipp16u* pSrcDst, int srcDstStep, IppiSize srcRoiSize,
             IppiSize dstRoiSize, int topBorderHeight, int
             leftborderwidth, const Ipp16u value[3]))
IPPAPI (IppStatus, ippiCopyConstBorder_16u_AC4IR,
            (Ipp16u* pSrcDst, int srcDstStep, IppiSize srcRoiSize,
             IppiSize dstRoiSize, int topBorderHeight, int
             leftborderwidth, const Ipp16u value[3]))
IPPAPI (IppStatus, ippiCopyConstBorder_16u_C4IR,
            (Ipp16u* pSrcDst, int srcDstStep, IppiSize srcRoiSize,
             IppiSize dstRoiSize, int topBorderHeight, int
             leftborderwidth, const Ipp16u value[4]))

IPPAPI (IppStatus, ippiCopyConstBorder_16s_C1IR,
            (Ipp16s* pSrcDst, int srcDstStep, IppiSize srcRoiSize,
             IppiSize dstRoiSize, int topBorderHeight, int
             leftborderwidth, const Ipp16s value))
IPPAPI (IppStatus, ippiCopyConstBorder_16s_C3IR,
            (Ipp16s* pSrcDst, int srcDstStep, IppiSize srcRoiSize,
             IppiSize dstRoiSize, int topBorderHeight, int
             leftborderwidth, const Ipp16s value[3]))
IPPAPI (IppStatus, ippiCopyConstBorder_16s_AC4IR,
            (Ipp16s* pSrcDst, int srcDstStep, IppiSize srcRoiSize,
             IppiSize dstRoiSize, int topBorderHeight, int
             leftborderwidth, const Ipp16s value[3]))
IPPAPI (IppStatus, ippiCopyConstBorder_16s_C4IR,
            (Ipp16s* pSrcDst, int srcDstStep, IppiSize srcRoiSize,
             IppiSize dstRoiSize, int topBorderHeight, int
             leftborderwidth, const Ipp16s value[4]))

IPPAPI (IppStatus, ippiCopyConstBorder_32s_C1IR,
            (Ipp32s* pSrcDst, int srcDstStep, IppiSize srcRoiSize,
             IppiSize dstRoiSize, int topBorderHeight, int
             leftborderwidth, const Ipp32s value))
IPPAPI (IppStatus, ippiCopyConstBorder_32s_C3IR,
            (Ipp32s* pSrcDst, int srcDstStep, IppiSize srcRoiSize,
             IppiSize dstRoiSize, int topBorderHeight, int
             leftborderwidth, const Ipp32s value[3]))
IPPAPI (IppStatus, ippiCopyConstBorder_32s_AC4IR,
            (Ipp32s* pSrcDst, int srcDstStep, IppiSize srcRoiSize,
             IppiSize dstRoiSize, int topBorderHeight, int
             leftborderwidth, const Ipp32s value[3]))
IPPAPI (IppStatus, ippiCopyConstBorder_32s_C4IR,
            (Ipp32s* pSrcDst, int srcDstStep, IppiSize srcRoiSize,
             IppiSize dstRoiSize, int topBorderHeight, int
             leftborderwidth, const Ipp32s value[4]))

IPPAPI (IppStatus, ippiCopyConstBorder_32f_C1IR,
            (Ipp32f* pSrcDst, int srcDstStep, IppiSize srcRoiSize,
             IppiSize dstRoiSize, int topBorderHeight, int
             leftborderwidth, const Ipp32f value))
IPPAPI (IppStatus, ippiCopyConstBorder_32f_C3IR,
            (Ipp32f* pSrcDst, int srcDstStep, IppiSize srcRoiSize,
             IppiSize dstRoiSize, int topBorderHeight, int
             leftborderwidth, const Ipp32f value[3]))
IPPAPI (IppStatus, ippiCopyConstBorder_32f_AC4IR,
            (Ipp32f* pSrcDst, int srcDstStep, IppiSize srcRoiSize,
             IppiSize dstRoiSize, int topBorderHeight, int
             leftborderwidth, const Ipp32f value[3]))
IPPAPI (IppStatus, ippiCopyConstBorder_32f_C4IR,
            (Ipp32f* pSrcDst, int srcDstStep, IppiSize srcRoiSize,
             IppiSize dstRoiSize, int topBorderHeight, int
             leftborderwidth, const Ipp32f value[4]))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiCopyMirrorBorder
//
//  Purpose:   Copies pixel values between two buffers and adds
//             the mirror border pixels.
//
//  Returns:
//    ippStsNullPtrErr    One of the pointers is NULL
//    ippStsSizeErr       1). srcRoiSize or dstRoiSize has a field with negative or zero value
//                        2). topBorderHeight or leftBorderWidth is less than zero
//                        3). dstRoiSize.width < srcRoiSize.width + leftBorderWidth
//                        4). dstRoiSize.height < srcRoiSize.height + topBorderHeight
//    ippStsStepErr       srcStep or dstStep is less than or equal to zero
//    ippStsNoErr         OK
//
//  Parameters:
//    pSrc                Pointer  to the source image buffer
//    srcStep             Step in bytes through the source image
//    pDst                Pointer to the  destination image buffer
//    dstStep             Step in bytes through the destination image
//    scrRoiSize          Size of the source ROI in pixels
//    dstRoiSize          Size of the destination ROI in pixels
//    topBorderHeight     Height of the top border in pixels
//    leftBorderWidth     Width of the left border in pixels
*/

IPPAPI (IppStatus, ippiCopyMirrorBorder_8u_C1R,
            ( const Ipp8u* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp8u* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI (IppStatus, ippiCopyMirrorBorder_8u_C3R,
            ( const Ipp8u* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp8u* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI (IppStatus, ippiCopyMirrorBorder_8u_C4R,
            ( const Ipp8u* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp8u* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI (IppStatus, ippiCopyMirrorBorder_16s_C1R,
            ( const Ipp16s* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp16s* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI (IppStatus, ippiCopyMirrorBorder_16s_C3R,
            ( const Ipp16s* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp16s* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI (IppStatus, ippiCopyMirrorBorder_16s_C4R,
            ( const Ipp16s* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp16s* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI (IppStatus, ippiCopyMirrorBorder_32s_C1R,
            ( const Ipp32s* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp32s* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI (IppStatus, ippiCopyMirrorBorder_32s_C3R,
            ( const Ipp32s* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp32s* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI (IppStatus, ippiCopyMirrorBorder_32s_C4R,
            ( const Ipp32s* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp32s* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )

IPPAPI ( IppStatus, ippiCopyMirrorBorder_8u_C1IR,
                    ( const Ipp8u* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )
IPPAPI ( IppStatus, ippiCopyMirrorBorder_8u_C3IR,
                    ( const Ipp8u* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )
IPPAPI ( IppStatus, ippiCopyMirrorBorder_8u_C4IR,
                    ( const Ipp8u* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )

IPPAPI ( IppStatus, ippiCopyMirrorBorder_16s_C1IR,
                    ( const Ipp16s* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )
IPPAPI ( IppStatus, ippiCopyMirrorBorder_16s_C3IR,
                    ( const Ipp16s* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )
IPPAPI ( IppStatus, ippiCopyMirrorBorder_16s_C4IR,
                    ( const Ipp16s* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )

IPPAPI ( IppStatus, ippiCopyMirrorBorder_32s_C1IR,
                    ( const Ipp32s* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )
IPPAPI ( IppStatus, ippiCopyMirrorBorder_32s_C3IR,
                    ( const Ipp32s* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )
IPPAPI ( IppStatus, ippiCopyMirrorBorder_32s_C4IR,
                    ( const Ipp32s* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )

IPPAPI ( IppStatus, ippiCopyMirrorBorder_16u_C1IR,
                    ( const Ipp16u* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )
IPPAPI ( IppStatus, ippiCopyMirrorBorder_16u_C3IR,
                    ( const Ipp16u* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )
IPPAPI ( IppStatus, ippiCopyMirrorBorder_16u_C4IR,
                    ( const Ipp16u* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )

IPPAPI (IppStatus, ippiCopyMirrorBorder_16u_C1R,
            ( const Ipp16u* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp16u* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI (IppStatus, ippiCopyMirrorBorder_16u_C3R,
            ( const Ipp16u* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp16u* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI (IppStatus, ippiCopyMirrorBorder_16u_C4R,
            ( const Ipp16u* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp16u* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )

IPPAPI (IppStatus, ippiCopyMirrorBorder_32f_C1R,
            ( const Ipp32f* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp32f* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI (IppStatus, ippiCopyMirrorBorder_32f_C3R,
            ( const Ipp32f* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp32f* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI (IppStatus, ippiCopyMirrorBorder_32f_C4R,
            ( const Ipp32f* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp32f* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )

IPPAPI ( IppStatus, ippiCopyMirrorBorder_32f_C1IR,
                    ( const Ipp32f* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )
IPPAPI ( IppStatus, ippiCopyMirrorBorder_32f_C3IR,
                    ( const Ipp32f* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )
IPPAPI ( IppStatus, ippiCopyMirrorBorder_32f_C4IR,
                    ( const Ipp32f* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiCopyWrapBorder
//
//  Purpose:    Copies pixel values between two buffers and adds the border pixels.
//
//  Returns:
//    ippStsNullPtrErr    One of the pointers is NULL
//    ippStsSizeErr       1). srcRoiSize or dstRoiSize has a field with negative or zero value
//                        2). topBorderHeight or leftBorderWidth is less than zero
//                        3). dstRoiSize.width < srcRoiSize.width + leftBorderWidth
//                        4). dstRoiSize.height < srcRoiSize.height + topBorderHeight
//    ippStsStepErr       srcStep or dstStep is less than or equal to zero
//    ippStsNoErr         OK
//
//  Parameters:
//    pSrc                Pointer  to the source image buffer
//    srcStep             Step in bytes through the source image
//    pDst                Pointer to the  destination image buffer
//    dstStep             Step in bytes through the destination image
//    scrRoiSize          Size of the source ROI in pixels
//    dstRoiSize          Size of the destination ROI in pixels
//    topBorderHeight     Height of the top border in pixels
//    leftBorderWidth     Width of the left border in pixels
*/

IPPAPI (IppStatus, ippiCopyWrapBorder_32s_C1R,
            ( const Ipp32s* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp32s* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI ( IppStatus, ippiCopyWrapBorder_32s_C1IR,
                    ( const Ipp32s* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )

IPPAPI (IppStatus, ippiCopyWrapBorder_32f_C1R,
            ( const Ipp32f* pSrc,  int srcStep, IppiSize srcRoiSize,
                    Ipp32f* pDst,  int dstStep, IppiSize dstRoiSize,
                    int topBorderHeight, int leftBorderWidth ) )
IPPAPI ( IppStatus, ippiCopyWrapBorder_32f_C1IR,
                    ( const Ipp32f* pSrc,  int srcDstStep,
                            IppiSize srcRoiSize, IppiSize dstRoiSize,
                            int topBorderHeight, int leftborderwidth ) )

/* ////////////////////////////////////////////////////////////////////////////
//  Name:
// ipprCopyConstBorder_8u_C1V
// ipprCopyConstBorder_16u_C1V
// ipprCopyConstBorder_16s_C1V
// ipprCopyConstBorder_32f_C1V
// ipprCopyConstBorder_64f_C1V
// ipprCopyReplicateBorder_8u_C1V
// ipprCopyReplicateBorder_16u_C1V
// ipprCopyReplicateBorder_16s_C1V
// ipprCopyReplicateBorder_32f_C1V
// ipprCopyReplicateBorder_64f_C1V

//
//  Purpose:    Copies pixel values between two images and adds
//              the border pixels
//
//  Returns:
//    ippStsNullPtrErr   One of the pointers is NULL
//    ippStsSizeErr      1). srcRoiVolume or dstRoiVolume has a field with negative or zero value
//                       2). topBorderHeight or leftBorderWidth or forwardBorderDepth is less than zero
//                       3). dstRoiVolume.width  < srcRoiVolume.width  + leftBorderWidth
//                       4). dstRoiVolume.height < srcRoiVolume.height + topBorderHeight
//                       5). dstRoiVolume.depth  < srcRoiVolume.depth  + forwardBorderDepth
//    ippStsStepErr      srcPlaneStep, srcStep, dstPlaneStep or dstStep is less than or equal to zero
//    ippStsNoErr        OK
//
//  Parameters:
//    pSrc               Pointer to 3D source image
//    srcPlaneStep       Step in bytes through the 3D source image planes
//    srcStep            Step in bytes through the one source image plane
//    pDst               Pointer to the 3D destination image
//    dstPlaneStep       Step in bytes through the 3D destination image planes
//    dstStep            Step in bytes through the one destination image plane
//    srcRoiVolume       Size of the source VOI in pixels
//    dstRoiVolume       Size of the destination VOI in pixels
//    topBorderHeight    Height of the top border in pixels
//    leftBorderWidth    Width of the left border in pixels
//    forwardBorderDepth Depth of the forward border in pixels
//    value              Constant value to assign to the border pixels
*/

IPPAPI(IppStatus, ipprCopyConstBorder_8u_C1V , (const Ipp8u*  pSrc, int srcPlaneStep, int srcStep, IpprVolume srcRoiVolume, Ipp8u*  pDst, int dstPlaneStep, int dstStep, IpprVolume dstRoiVolume, int topBorderHeight, int leftBorderWidth, int forwardBorderDepth, const Ipp8u* value))
IPPAPI(IppStatus, ipprCopyConstBorder_16u_C1V, (const Ipp16u* pSrc, int srcPlaneStep, int srcStep, IpprVolume srcRoiVolume, Ipp16u* pDst, int dstPlaneStep, int dstStep, IpprVolume dstRoiVolume, int topBorderHeight, int leftBorderWidth, int forwardBorderDepth, const Ipp16u* value))
IPPAPI(IppStatus, ipprCopyConstBorder_16s_C1V, (const Ipp16s* pSrc, int srcPlaneStep, int srcStep, IpprVolume srcRoiVolume, Ipp16s* pDst, int dstPlaneStep, int dstStep, IpprVolume dstRoiVolume, int topBorderHeight, int leftBorderWidth, int forwardBorderDepth, const Ipp16s* value))
IPPAPI(IppStatus, ipprCopyConstBorder_32f_C1V, (const Ipp32f* pSrc, int srcPlaneStep, int srcStep, IpprVolume srcRoiVolume, Ipp32f* pDst, int dstPlaneStep, int dstStep, IpprVolume dstRoiVolume, int topBorderHeight, int leftBorderWidth, int forwardBorderDepth, const Ipp32f* value))
IPPAPI(IppStatus, ipprCopyConstBorder_64f_C1V, (const Ipp64f* pSrc, int srcPlaneStep, int srcStep, IpprVolume srcRoiVolume, Ipp64f* pDst, int dstPlaneStep, int dstStep, IpprVolume dstRoiVolume, int topBorderHeight, int leftBorderWidth, int forwardBorderDepth, const Ipp64f* value))
IPPAPI(IppStatus, ipprCopyReplicateBorder_8u_C1V , (const Ipp8u*  pSrc, int srcPlaneStep, int srcStep, IpprVolume srcRoiVolume, Ipp8u*  pDst, int dstPlaneStep, int dstStep, IpprVolume dstRoiVolume, int topBorderHeight, int leftBorderWidth, int forwardBorderDepth))
IPPAPI(IppStatus, ipprCopyReplicateBorder_16u_C1V, (const Ipp16u* pSrc, int srcPlaneStep, int srcStep, IpprVolume srcRoiVolume, Ipp16u* pDst, int dstPlaneStep, int dstStep, IpprVolume dstRoiVolume, int topBorderHeight, int leftBorderWidth, int forwardBorderDepth))
IPPAPI(IppStatus, ipprCopyReplicateBorder_16s_C1V, (const Ipp16s* pSrc, int srcPlaneStep, int srcStep, IpprVolume srcRoiVolume, Ipp16s* pDst, int dstPlaneStep, int dstStep, IpprVolume dstRoiVolume, int topBorderHeight, int leftBorderWidth, int forwardBorderDepth))
IPPAPI(IppStatus, ipprCopyReplicateBorder_32f_C1V, (const Ipp32f* pSrc, int srcPlaneStep, int srcStep, IpprVolume srcRoiVolume, Ipp32f* pDst, int dstPlaneStep, int dstStep, IpprVolume dstRoiVolume, int topBorderHeight, int leftBorderWidth, int forwardBorderDepth))
IPPAPI(IppStatus, ipprCopyReplicateBorder_64f_C1V, (const Ipp64f* pSrc, int srcPlaneStep, int srcStep, IpprVolume srcRoiVolume, Ipp64f* pDst, int dstPlaneStep, int dstStep, IpprVolume dstRoiVolume, int topBorderHeight, int leftBorderWidth, int forwardBorderDepth))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiDup
//
//  Purpose:  Duplication pixel values from the source image
//            to the correspondent pixels in all channels
//            of the destination  image.
//
//  Returns:
//    ippStsNullPtrErr  One of the pointers is NULL
//    ippStsSizeErr     roiSize has a field with zero or negative value
//    ippStsNoErr       OK
//
//  Parameters:
//    pSrc              Pointer  to the source image buffer
//    srcStep           Step in bytes through the source image buffer
//    pDst              Pointer to the  destination image buffer
//    dstStep           Step in bytes through the destination image buffer
//    roiSize           Size of the ROI
*/

IPPAPI( IppStatus, ippiDup_8u_C1C3R,
                   ( const Ipp8u* pSrc, int srcStep,
                     Ipp8u* pDst, int dstStep, IppiSize roiSize ))

IPPAPI( IppStatus, ippiDup_8u_C1C4R,
                   ( const Ipp8u* pSrc, int srcStep,
                     Ipp8u* pDst, int dstStep, IppiSize roiSize ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiSet
//
//  Purpose:    Sets pixels in the image buffer to a constant value
//
//  Returns:
//    ippStsNullPtrErr  One of pointers is NULL
//    ippStsSizeErr     roiSize has a field with negative or zero value
//    ippStsNoErr       OK
//
//  Parameters:
//    value      Constant value assigned to each pixel in the image buffer
//    pDst       Pointer to the destination image buffer
//    dstStep    Step in bytes through the destination image buffer
//    roiSize    Size of the ROI
//    pMask      Pointer to the mask image buffer
//    maskStep   Step in bytes through the mask image buffer
*/

IPPAPI ( IppStatus, ippiSet_8u_C1R,
                    ( Ipp8u value, Ipp8u* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_8u_C3CR,
                    ( Ipp8u value, Ipp8u* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_8u_C4CR,
                    ( Ipp8u value, Ipp8u* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_8u_C3R,
                    ( const Ipp8u value[3], Ipp8u* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_8u_C4R,
                    ( const Ipp8u value[4], Ipp8u* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_8u_AC4R,
                    ( const Ipp8u value[3], Ipp8u* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_8u_C1MR,
                    ( Ipp8u value, Ipp8u* pDst, int dstStep,
                      IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiSet_8u_C3MR,
                    ( const Ipp8u value[3], Ipp8u* pDst, int dstStep,
                      IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))

IPPAPI ( IppStatus, ippiSet_8u_C4MR,
                    ( const Ipp8u value[4], Ipp8u* pDst, int dstStep,
                      IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiSet_8u_AC4MR,
                    ( const Ipp8u value[3], Ipp8u* pDst, int dstStep,
                      IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiSet_16s_C1R,
                    ( Ipp16s value, Ipp16s* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_16s_C3CR,
                    ( Ipp16s value, Ipp16s* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_16s_C4CR,
                    ( Ipp16s value, Ipp16s* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_16s_C3R,
                    ( const Ipp16s value[3], Ipp16s* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_16s_C4R,
                    ( const Ipp16s value[4], Ipp16s* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_16s_AC4R,
                    ( const Ipp16s value[3], Ipp16s* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_16s_C1MR,
                    ( Ipp16s value, Ipp16s* pDst, int dstStep,
                      IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiSet_16s_C3MR,
                    ( const Ipp16s value[3], Ipp16s* pDst, int dstStep,
                      IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiSet_16s_C4MR,
                    ( const Ipp16s value[4], Ipp16s* pDst, int dstStep,
                      IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiSet_16s_AC4MR,
                    ( const Ipp16s value[3], Ipp16s* pDst, int dstStep,
                      IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiSet_32f_C1R,
                    ( Ipp32f value, Ipp32f* pDst, int dstStep,
                      IppiSize roiSize ))

IPPAPI ( IppStatus, ippiSet_32f_C3CR,
                    ( Ipp32f value, Ipp32f* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_32f_C4CR,
                    ( Ipp32f value, Ipp32f* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_32f_C3R,
                    ( const Ipp32f value[3], Ipp32f* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_32f_C4R,
                    ( const Ipp32f value[4], Ipp32f* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_32f_AC4R,
                    ( const Ipp32f value[3], Ipp32f* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_32f_C1MR,
                    ( Ipp32f value, Ipp32f* pDst, int dstStep,
                      IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiSet_32f_C3MR,
                    ( const Ipp32f value[3], Ipp32f* pDst, int dstStep,
                      IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiSet_32f_C4MR,
                    ( const Ipp32f value[4], Ipp32f* pDst, int dstStep,
                      IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiSet_32f_AC4MR,
                    ( const Ipp32f value[3], Ipp32f* pDst, int dstStep,
                      IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiSet_32s_C1R,
                    ( Ipp32s value, Ipp32s* pDst, int dstStep,
                      IppiSize roiSize ))

IPPAPI ( IppStatus, ippiSet_32s_C3CR,
                    ( Ipp32s value, Ipp32s* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_32s_C4CR,
                    ( Ipp32s value, Ipp32s* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_32s_C3R,
                    ( const Ipp32s value[3], Ipp32s* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_32s_C4R,
                    ( const Ipp32s value[4], Ipp32s* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_32s_AC4R,
                    ( const Ipp32s value[3], Ipp32s* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_32s_C1MR,
                    ( Ipp32s value, Ipp32s* pDst, int dstStep,
                      IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiSet_32s_C3MR,
                    ( const Ipp32s value[3], Ipp32s* pDst, int dstStep,
                      IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiSet_32s_C4MR,
                    ( const Ipp32s value[4], Ipp32s* pDst, int dstStep,
                      IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiSet_32s_AC4MR,
                    ( const Ipp32s value[3], Ipp32s* pDst, int dstStep,
                      IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))

IPPAPI ( IppStatus, ippiSet_16u_C1R,
                    ( Ipp16u value, Ipp16u* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_16u_C3CR,
                    ( Ipp16u value, Ipp16u* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_16u_C4CR,
                    ( Ipp16u value, Ipp16u* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_16u_C3R,
                    ( const Ipp16u value[3], Ipp16u* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_16u_C4R,
                    ( const Ipp16u value[4], Ipp16u* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_16u_AC4R,
                    ( const Ipp16u value[3], Ipp16u* pDst, int dstStep,
                      IppiSize roiSize ))
IPPAPI ( IppStatus, ippiSet_16u_C1MR,
                    ( Ipp16u value, Ipp16u* pDst, int dstStep,
                      IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiSet_16u_C3MR,
                    ( const Ipp16u value[3], Ipp16u* pDst, int dstStep,
                      IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiSet_16u_C4MR,
                    ( const Ipp16u value[4], Ipp16u* pDst, int dstStep,
                      IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))
IPPAPI ( IppStatus, ippiSet_16u_AC4MR,
                    ( const Ipp16u value[3], Ipp16u* pDst, int dstStep,
                      IppiSize roiSize,
                      const Ipp8u* pMask, int maskStep ))

/* //////////////////////////////////////////////////////////////////////////////////
//  Name:  ippiAddRandUniform_8u_C1IR,  ippiAddRandUniform_8u_C3IR,
//         ippiAddRandUniform_8u_C4IR,  ippiAddRandUniform_8u_AC4IR,
//         ippiAddRandUniform_16s_C1IR, ippiAddRandUniform_16s_C3IR,
//         ippiAddRandUniform_16s_C4IR, ippiAddRandUniform_16s_AC4IR,
//         ippiAddRandUniform_32f_C1IR, ippiAddRandUniform_32f_C3IR,
//         ippiAddRandUniform_32f_C4IR, ippiAddRandUniform_32f_AC4IR
//         ippiAddRandUniform_16u_C1IR, ippiAddRandUniform_16u_C3IR,
//         ippiAddRandUniform_16u_C4IR, ippiAddRandUniform_16u_AC4IR,
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

IPPAPI(IppStatus, ippiAddRandUniform_8u_C1IR,   (Ipp8u* pSrcDst, int srcDstStep,
                                                        IppiSize roiSize, Ipp8u low, Ipp8u high,
                                                        unsigned int* pSeed))
IPPAPI(IppStatus, ippiAddRandUniform_8u_C3IR,   (Ipp8u* pSrcDst, int srcDstStep,
                                                        IppiSize roiSize, Ipp8u low, Ipp8u high,
                                                        unsigned int* pSeed))
IPPAPI(IppStatus, ippiAddRandUniform_8u_C4IR,   (Ipp8u* pSrcDst, int srcDstStep,
                                                        IppiSize roiSize, Ipp8u low, Ipp8u high,
                                                        unsigned int* pSeed))
IPPAPI(IppStatus, ippiAddRandUniform_8u_AC4IR,  (Ipp8u* pSrcDst, int srcDstStep,
                                                        IppiSize roiSize, Ipp8u low, Ipp8u high,
                                                        unsigned int* pSeed))
IPPAPI(IppStatus, ippiAddRandUniform_16s_C1IR,  (Ipp16s* pSrcDst, int srcDstStep,
                                                        IppiSize roiSize, Ipp16s low, Ipp16s high,
                                                        unsigned int* pSeed))
IPPAPI(IppStatus, ippiAddRandUniform_16s_C3IR,  (Ipp16s* pSrcDst, int srcDstStep,
                                                        IppiSize roiSize, Ipp16s low, Ipp16s high,
                                                        unsigned int* pSeed))
IPPAPI(IppStatus, ippiAddRandUniform_16s_C4IR,  (Ipp16s* pSrcDst, int srcDstStep,
                                                        IppiSize roiSize, Ipp16s low, Ipp16s high,
                                                        unsigned int* pSeed))
IPPAPI(IppStatus, ippiAddRandUniform_16s_AC4IR, (Ipp16s* pSrcDst, int srcDstStep,
                                                        IppiSize roiSize, Ipp16s low, Ipp16s high,
                                                        unsigned int* pSeed))
IPPAPI(IppStatus, ippiAddRandUniform_32f_C1IR,  (Ipp32f* pSrcDst, int srcDstStep,
                                                        IppiSize roiSize, Ipp32f low, Ipp32f high,
                                                        unsigned int* pSeed))
IPPAPI(IppStatus, ippiAddRandUniform_32f_C3IR,  (Ipp32f* pSrcDst, int srcDstStep,
                                                        IppiSize roiSize, Ipp32f low, Ipp32f high,
                                                        unsigned int* pSeed))
IPPAPI(IppStatus, ippiAddRandUniform_32f_C4IR,  (Ipp32f* pSrcDst, int srcDstStep,
                                                        IppiSize roiSize, Ipp32f low, Ipp32f high,
                                                        unsigned int* pSeed))
IPPAPI(IppStatus, ippiAddRandUniform_32f_AC4IR, (Ipp32f* pSrcDst, int srcDstStep,
                                                        IppiSize roiSize, Ipp32f low, Ipp32f high,
                                                        unsigned int* pSeed))

IPPAPI(IppStatus,ippiAddRandUniform_16u_C1IR, (Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize,
                                                           Ipp16u low, Ipp16u high, unsigned int* pSeed))
IPPAPI(IppStatus,ippiAddRandUniform_16u_C3IR, (Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize,
                                                           Ipp16u low, Ipp16u high, unsigned int* pSeed))
IPPAPI(IppStatus,ippiAddRandUniform_16u_C4IR, (Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize,
                                                           Ipp16u low, Ipp16u high, unsigned int* pSeed))
IPPAPI(IppStatus,ippiAddRandUniform_16u_AC4IR,(Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize,
                                                           Ipp16u low, Ipp16u high, unsigned int* pSeed))

/* ////////////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiAddRandGauss_8u_C1IR,  ippiAddRandGauss_8u_C3IR,
//              ippiAddRandGauss_8u_C4IR,  ippiAddRandGauss_8u_AC4IR
//              ippiAddRandGauss_16s_C1IR, ippiAddRandGauss_16s_C3IR,
//              ippiAddRandGauss_16s_C4IR, ippiAddRandGauss_16s_AC4IR,
//              ippiAddRandGauss_32f_C1IR, ippiAddRandGauss_32f_C3IR,
//              ippiAddRandGauss_32f_C4IR, ippiAddRandGauss_32f_AC4IR
//              ippiAddRandGauss_16u_C1IR, ippiAddRandGauss_16u_C3IR,
//              ippiAddRandGauss_16u_C4IR, ippiAddRandGauss_16u_AC4IR,
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


IPPAPI(IppStatus, ippiAddRandGauss_8u_C1IR,   (Ipp8u* pSrcDst, int srcDstStep,
                                                      IppiSize roiSize, Ipp8u mean, Ipp8u stdev,
                                                      unsigned int* pSeed))
IPPAPI(IppStatus, ippiAddRandGauss_8u_C3IR,   (Ipp8u* pSrcDst, int srcDstStep,
                                                      IppiSize roiSize, Ipp8u mean, Ipp8u stdev,
                                                      unsigned int* pSeed))
IPPAPI(IppStatus, ippiAddRandGauss_8u_C4IR,   (Ipp8u* pSrcDst, int srcDstStep,
                                                      IppiSize roiSize, Ipp8u mean, Ipp8u stdev,
                                                      unsigned int* pSeed))
IPPAPI(IppStatus, ippiAddRandGauss_8u_AC4IR,  (Ipp8u* pSrcDst, int srcDstStep,
                                                      IppiSize roiSize, Ipp8u mean, Ipp8u stdev,
                                                      unsigned int* pSeed))
IPPAPI(IppStatus, ippiAddRandGauss_16s_C1IR,  (Ipp16s* pSrcDst, int srcDstStep,
                                                      IppiSize roiSize, Ipp16s mean, Ipp16s stdev,
                                                      unsigned int* pSeed))
IPPAPI(IppStatus, ippiAddRandGauss_16s_C3IR,  (Ipp16s* pSrcDst, int srcDstStep,
                                                      IppiSize roiSize, Ipp16s mean, Ipp16s stdev,
                                                      unsigned int* pSeed))
IPPAPI(IppStatus, ippiAddRandGauss_16s_C4IR,  (Ipp16s* pSrcDst, int srcDstStep,
                                                      IppiSize roiSize, Ipp16s mean, Ipp16s stdev,
                                                      unsigned int* pSeed))
IPPAPI(IppStatus, ippiAddRandGauss_16s_AC4IR, (Ipp16s* pSrcDst, int srcDstStep,
                                                      IppiSize roiSize, Ipp16s mean, Ipp16s stdev,
                                                      unsigned int* pSeed))
IPPAPI(IppStatus, ippiAddRandGauss_32f_C1IR,  (Ipp32f* pSrcDst, int srcDstStep,
                                                      IppiSize roiSize, Ipp32f mean, Ipp32f stdev,
                                                      unsigned int* pSeed))
IPPAPI(IppStatus, ippiAddRandGauss_32f_C3IR,  (Ipp32f* pSrcDst, int srcDstStep,
                                                      IppiSize roiSize, Ipp32f mean, Ipp32f stdev,
                                                      unsigned int* pSeed))
IPPAPI(IppStatus, ippiAddRandGauss_32f_C4IR,  (Ipp32f* pSrcDst, int srcDstStep,
                                                      IppiSize roiSize, Ipp32f mean, Ipp32f stdev,
                                                      unsigned int* pSeed))
IPPAPI(IppStatus, ippiAddRandGauss_32f_AC4IR, (Ipp32f* pSrcDst, int srcDstStep,
                                                      IppiSize roiSize, Ipp32f mean, Ipp32f stdev,
                                                      unsigned int* pSeed))

IPPAPI(IppStatus,ippiAddRandGauss_16u_C1IR, (Ipp16u* pSrcDst,int srcDstStep,IppiSize roiSize,
                                                     Ipp16u mean, Ipp16u stdev, unsigned int* pSeed))
IPPAPI(IppStatus,ippiAddRandGauss_16u_C3IR, (Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize,
                                                      Ipp16u mean, Ipp16u stdev, unsigned int* pSeed))
IPPAPI(IppStatus,ippiAddRandGauss_16u_C4IR, (Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize,
                                                      Ipp16u mean, Ipp16u stdev, unsigned int* pSeed))
IPPAPI(IppStatus,ippiAddRandGauss_16u_AC4IR,(Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize,
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
IPPAPI(IppStatus, ippiImageJaehne_8u_C1R, (Ipp8u* pDst, int DstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiImageJaehne_8u_C3R, (Ipp8u* pDst, int DstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiImageJaehne_8u_C4R, (Ipp8u* pDst, int DstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiImageJaehne_8u_AC4R,(Ipp8u* pDst, int DstStep, IppiSize roiSize))

IPPAPI(IppStatus, ippiImageJaehne_16u_C1R, (Ipp16u* pDst, int DstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiImageJaehne_16u_C3R, (Ipp16u* pDst, int DstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiImageJaehne_16u_C4R, (Ipp16u* pDst, int DstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiImageJaehne_16u_AC4R,(Ipp16u* pDst, int DstStep, IppiSize roiSize))

IPPAPI(IppStatus, ippiImageJaehne_16s_C1R, (Ipp16s* pDst, int DstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiImageJaehne_16s_C3R, (Ipp16s* pDst, int DstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiImageJaehne_16s_C4R, (Ipp16s* pDst, int DstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiImageJaehne_16s_AC4R,(Ipp16s* pDst, int DstStep, IppiSize roiSize))

IPPAPI(IppStatus, ippiImageJaehne_32f_C1R, (Ipp32f* pDst, int DstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiImageJaehne_32f_C3R, (Ipp32f* pDst, int DstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiImageJaehne_32f_C4R, (Ipp32f* pDst, int DstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiImageJaehne_32f_AC4R,(Ipp32f* pDst, int DstStep, IppiSize roiSize))



/* /////////////////////////////////////////////////////////////////////////
// Name:          ippiImageRamp
// Purpose:       Creates an ippi test image with an intensity ramp.
// Parameters:
//    pDst        - Pointer to the destination buffer.
//    dstStep     - Distance, in bytes, between the starting points of consecutive lines in the destination image.
//    roiSize     - Size, in pixels, of the destination image ROI.
//    offset      - Offset value.
//    slope       - Slope coefficient.
//    axis        - Specifies the direction of the image intensity ramp, possible values:
//                      ippAxsHorizontal   in X-direction,
//                      ippAxsVertical     in Y-direction,
//                      ippAxsBoth         in both X and Y-directions.
//  Returns:
//    ippStsNoErr      - OK.
//    ippStsNullPtrErr - Error when any of the specified pointers is NULL.
//    ippStsStepErr    - Error when dstStep has a zero or negative value.
//    ippStsSizeErr    - Error when roiSize has a field with value less than 1.
//
// Notes:  Dst(x,y) = offset + slope * x   (if ramp for X-direction)
//         Dst(x,y) = offset + slope * y   (if ramp for Y-direction)
//         Dst(x,y) = offset + slope * x*y (if ramp for X,Y-direction)
*/
IPPAPI(IppStatus, ippiImageRamp_8u_C1R, (Ipp8u* pDst, int dstStep, IppiSize roiSize, float offset, float slope, IppiAxis axis))
IPPAPI(IppStatus, ippiImageRamp_8u_C3R, (Ipp8u* pDst, int dstStep, IppiSize roiSize, float offset, float slope, IppiAxis axis))
IPPAPI(IppStatus, ippiImageRamp_8u_C4R, (Ipp8u* pDst, int dstStep, IppiSize roiSize, float offset, float slope, IppiAxis axis))
IPPAPI(IppStatus, ippiImageRamp_8u_AC4R,(Ipp8u* pDst, int dstStep, IppiSize roiSize, float offset, float slope, IppiAxis axis))

IPPAPI(IppStatus, ippiImageRamp_16u_C1R, (Ipp16u* pDst, int dstStep, IppiSize roiSize, float offset, float slope, IppiAxis axis))
IPPAPI(IppStatus, ippiImageRamp_16u_C3R, (Ipp16u* pDst, int dstStep, IppiSize roiSize, float offset, float slope, IppiAxis axis))
IPPAPI(IppStatus, ippiImageRamp_16u_C4R, (Ipp16u* pDst, int dstStep, IppiSize roiSize, float offset, float slope, IppiAxis axis))
IPPAPI(IppStatus, ippiImageRamp_16u_AC4R,(Ipp16u* pDst, int dstStep, IppiSize roiSize, float offset, float slope, IppiAxis axis))

IPPAPI(IppStatus, ippiImageRamp_16s_C1R, (Ipp16s* pDst, int dstStep, IppiSize roiSize, float offset, float slope, IppiAxis axis))
IPPAPI(IppStatus, ippiImageRamp_16s_C3R, (Ipp16s* pDst, int dstStep, IppiSize roiSize, float offset, float slope, IppiAxis axis))
IPPAPI(IppStatus, ippiImageRamp_16s_C4R, (Ipp16s* pDst, int dstStep, IppiSize roiSize, float offset, float slope, IppiAxis axis))
IPPAPI(IppStatus, ippiImageRamp_16s_AC4R,(Ipp16s* pDst, int dstStep, IppiSize roiSize, float offset, float slope, IppiAxis axis))

IPPAPI(IppStatus, ippiImageRamp_32f_C1R, (Ipp32f* pDst, int dstStep, IppiSize roiSize, float offset, float slope, IppiAxis axis))
IPPAPI(IppStatus, ippiImageRamp_32f_C3R, (Ipp32f* pDst, int dstStep, IppiSize roiSize, float offset, float slope, IppiAxis axis))
IPPAPI(IppStatus, ippiImageRamp_32f_C4R, (Ipp32f* pDst, int dstStep, IppiSize roiSize, float offset, float slope, IppiAxis axis))
IPPAPI(IppStatus, ippiImageRamp_32f_AC4R,(Ipp32f* pDst, int dstStep, IppiSize roiSize, float offset, float slope, IppiAxis axis))



/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiConvert
//
//  Purpose:    Converts pixel values of an image from one bit depth to another
//
//  Returns:
//    ippStsNullPtrErr      One of the pointers is NULL
//    ippStsSizeErr         roiSize has a field with zero or negative value
//    ippStsStepErr         srcStep or dstStep has zero or negative value
//    ippStsNoErr           OK
//
//  Parameters:
//    pSrc                  Pointer  to the source image
//    srcStep               Step through the source image
//    pDst                  Pointer to the  destination image
//    dstStep               Step in bytes through the destination image
//    roiSize               Size of the ROI
//    roundMode             Rounding mode, ippRndZero or ippRndNear
*/
IPPAPI ( IppStatus, ippiConvert_8u8s_C1RSfs, (const Ipp8u*  pSrc, int srcStep, Ipp8s*  pDst, int dstStep, IppiSize roi,IppRoundMode rndMode, int scaleFactor))

IPPAPI ( IppStatus, ippiConvert_8u16u_C1R, (const Ipp8u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_8u16u_C3R, (const Ipp8u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_8u16u_AC4R,(const Ipp8u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_8u16u_C4R, (const Ipp8u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize ))

IPPAPI ( IppStatus, ippiConvert_8u16s_C1R, (const Ipp8u* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_8u16s_C3R, (const Ipp8u* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_8u16s_AC4R,(const Ipp8u* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_8u16s_C4R, (const Ipp8u* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize ))

IPPAPI ( IppStatus, ippiConvert_8u32s_C1R, (const Ipp8u* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_8u32s_C3R, (const Ipp8u* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_8u32s_AC4R,(const Ipp8u* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_8u32s_C4R, (const Ipp8u* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize ))

IPPAPI ( IppStatus, ippiConvert_8u32f_C1R, (const Ipp8u* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_8u32f_C3R, (const Ipp8u* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_8u32f_AC4R,(const Ipp8u* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_8u32f_C4R, (const Ipp8u* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize ))


IPPAPI ( IppStatus, ippiConvert_8s8u_C1Rs, (const Ipp8s*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roi))
IPPAPI ( IppStatus, ippiConvert_8s16s_C1R, (const Ipp8s*  pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roi))
IPPAPI ( IppStatus, ippiConvert_8s16u_C1Rs, (const Ipp8s*  pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roi))
IPPAPI ( IppStatus, ippiConvert_8s32u_C1Rs, (const Ipp8s*  pSrc, int srcStep, Ipp32u* pDst, int dstStep, IppiSize roi))

IPPAPI ( IppStatus, ippiConvert_8s32s_C1R, (const Ipp8s* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_8s32s_C3R, (const Ipp8s* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_8s32s_AC4R,(const Ipp8s* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_8s32s_C4R, (const Ipp8s* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize ))

IPPAPI ( IppStatus, ippiConvert_8s32f_C1R, (const Ipp8s* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_8s32f_C3R, (const Ipp8s* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_8s32f_AC4R,(const Ipp8s* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_8s32f_C4R, (const Ipp8s* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize ))


IPPAPI ( IppStatus, ippiConvert_16u8u_C1R, ( const Ipp16u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_16u8u_C3R, ( const Ipp16u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_16u8u_AC4R,( const Ipp16u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_16u8u_C4R, ( const Ipp16u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize ))

IPPAPI ( IppStatus, ippiConvert_16u8s_C1RSfs, (const Ipp16u* pSrc, int srcStep, Ipp8s*  pDst, int dstStep, IppiSize roi,IppRoundMode rndMode, int scaleFactor))
IPPAPI ( IppStatus, ippiConvert_16u16s_C1RSfs, (const Ipp16u* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roi,IppRoundMode rndMode, int scaleFactor))
IPPAPI ( IppStatus, ippiConvert_16u32u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp32u* pDst, int dstStep, IppiSize roi))

IPPAPI ( IppStatus, ippiConvert_16u32s_C1R, (const Ipp16u* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_16u32s_C3R, (const Ipp16u* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_16u32s_AC4R,(const Ipp16u* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_16u32s_C4R, (const Ipp16u* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize ))

IPPAPI ( IppStatus, ippiConvert_16u32f_C1R, (const Ipp16u* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_16u32f_C3R, (const Ipp16u* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_16u32f_AC4R,(const Ipp16u* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_16u32f_C4R, (const Ipp16u* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize ))


IPPAPI ( IppStatus, ippiConvert_16s8s_C1RSfs, (const Ipp16s* pSrc, int srcStep, Ipp8s*  pDst, int dstStep, IppiSize roi,IppRoundMode rndMode, int scaleFactor))

IPPAPI ( IppStatus, ippiConvert_16s8u_C1R, ( const Ipp16s* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_16s8u_C3R, ( const Ipp16s* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_16s8u_AC4R,( const Ipp16s* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_16s8u_C4R, ( const Ipp16s* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize ))

IPPAPI ( IppStatus, ippiConvert_16s16u_C1Rs, (const Ipp16s* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roi))
IPPAPI ( IppStatus, ippiConvert_16s32u_C1Rs, (const Ipp16s* pSrc, int srcStep, Ipp32u* pDst, int dstStep, IppiSize roi))

IPPAPI ( IppStatus, ippiConvert_16s32s_C1R, (const Ipp16s* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_16s32s_C3R, (const Ipp16s* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_16s32s_AC4R,(const Ipp16s* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_16s32s_C4R, (const Ipp16s* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize ))

IPPAPI ( IppStatus, ippiConvert_16s32f_C1R, (const Ipp16s* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_16s32f_C3R, (const Ipp16s* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_16s32f_AC4R,(const Ipp16s* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_16s32f_C4R, (const Ipp16s* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize ))


IPPAPI ( IppStatus, ippiConvert_32u8u_C1RSfs, (const Ipp32u* pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roi,IppRoundMode rndMode, int scaleFactor))
IPPAPI ( IppStatus, ippiConvert_32u8s_C1RSfs, (const Ipp32u* pSrc, int srcStep, Ipp8s*  pDst, int dstStep, IppiSize roi,IppRoundMode rndMode, int scaleFactor))
IPPAPI ( IppStatus, ippiConvert_32u16u_C1RSfs, (const Ipp32u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roi,IppRoundMode rndMode, int scaleFactor))
IPPAPI ( IppStatus, ippiConvert_32u16s_C1RSfs, (const Ipp32u* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roi,IppRoundMode rndMode, int scaleFactor))
IPPAPI ( IppStatus, ippiConvert_32u32s_C1RSfs, (const Ipp32u* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roi,IppRoundMode rndMode, int scaleFactor))
IPPAPI ( IppStatus, ippiConvert_32u32f_C1R, (const Ipp32u* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roi))


IPPAPI ( IppStatus, ippiConvert_32s8u_C1R, ( const Ipp32s* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_32s8u_C3R, ( const Ipp32s* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_32s8u_AC4R,( const Ipp32s* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_32s8u_C4R, ( const Ipp32s* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize ))

IPPAPI ( IppStatus, ippiConvert_32s8s_C1R, ( const Ipp32s* pSrc, int srcStep, Ipp8s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_32s8s_C3R, ( const Ipp32s* pSrc, int srcStep, Ipp8s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_32s8s_AC4R,( const Ipp32s* pSrc, int srcStep, Ipp8s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiConvert_32s8s_C4R, ( const Ipp32s* pSrc, int srcStep, Ipp8s* pDst, int dstStep, IppiSize roiSize ))

IPPAPI ( IppStatus, ippiConvert_32s16u_C1RSfs, (const Ipp32s* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roi,IppRoundMode rndMode, int scaleFactor))
IPPAPI ( IppStatus, ippiConvert_32s16s_C1RSfs, (const Ipp32s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roi,IppRoundMode rndMode, int scaleFactor))
IPPAPI ( IppStatus, ippiConvert_32s32u_C1Rs, (const Ipp32s* pSrc, int srcStep, Ipp32u* pDst, int dstStep, IppiSize roi))
IPPAPI ( IppStatus, ippiConvert_32s32f_C1R, (const Ipp32s* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roi))


IPPAPI ( IppStatus, ippiConvert_32f8u_C1RSfs, (const Ipp32f* pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roi, IppRoundMode round, int scaleFactor))

IPPAPI ( IppStatus, ippiConvert_32f8u_C1R, ( const Ipp32f* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode ))
IPPAPI ( IppStatus, ippiConvert_32f8u_C3R, ( const Ipp32f* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode ))
IPPAPI ( IppStatus, ippiConvert_32f8u_AC4R,( const Ipp32f* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode ))
IPPAPI ( IppStatus, ippiConvert_32f8u_C4R, ( const Ipp32f* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode ))

IPPAPI ( IppStatus, ippiConvert_32f8s_C1RSfs, (const Ipp32f* pSrc, int srcStep, Ipp8s*  pDst, int dstStep, IppiSize roi, IppRoundMode round, int scaleFactor))

IPPAPI ( IppStatus, ippiConvert_32f8s_C1R, ( const Ipp32f* pSrc, int srcStep, Ipp8s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode ))
IPPAPI ( IppStatus, ippiConvert_32f8s_C3R, ( const Ipp32f* pSrc, int srcStep, Ipp8s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode ))
IPPAPI ( IppStatus, ippiConvert_32f8s_AC4R,( const Ipp32f* pSrc, int srcStep, Ipp8s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode ))
IPPAPI ( IppStatus, ippiConvert_32f8s_C4R, ( const Ipp32f* pSrc, int srcStep, Ipp8s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode ))

IPPAPI ( IppStatus, ippiConvert_32f16u_C1RSfs, (const Ipp32f* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roi, IppRoundMode round, int scaleFactor))

IPPAPI ( IppStatus, ippiConvert_32f16u_C1R, ( const Ipp32f* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode ))
IPPAPI ( IppStatus, ippiConvert_32f16u_C3R, ( const Ipp32f* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode ))
IPPAPI ( IppStatus, ippiConvert_32f16u_AC4R,( const Ipp32f* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode ))
IPPAPI ( IppStatus, ippiConvert_32f16u_C4R, ( const Ipp32f* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode ))

IPPAPI ( IppStatus, ippiConvert_32f16s_C1RSfs, (const Ipp32f* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roi, IppRoundMode round, int scaleFactor))

IPPAPI ( IppStatus, ippiConvert_32f16s_C1R, ( const Ipp32f* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode ))
IPPAPI ( IppStatus, ippiConvert_32f16s_C3R, ( const Ipp32f* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode ))
IPPAPI ( IppStatus, ippiConvert_32f16s_AC4R,( const Ipp32f* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode ))
IPPAPI ( IppStatus, ippiConvert_32f16s_C4R, ( const Ipp32f* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode ))

IPPAPI ( IppStatus, ippiConvert_32f32u_C1RSfs, (const Ipp32f* pSrc, int srcStep, Ipp32u* pDst, int dstStep, IppiSize roi,IppRoundMode rndMode, int scaleFactor))
IPPAPI ( IppStatus, ippiConvert_32f32u_C1IRSfs, (Ipp32u* pSrcDst, int srcDstStep, IppiSize roi,IppRoundMode rndMode, int scaleFactor))

IPPAPI ( IppStatus, ippiConvert_32f32s_C1RSfs, (const Ipp32f* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roi, IppRoundMode round, int scaleFactor))

IPPAPI ( IppStatus, ippiConvert_64f8u_C1RSfs, (const Ipp64f* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode, int scaleFactor))
IPPAPI ( IppStatus, ippiConvert_64f8s_C1RSfs, (const Ipp64f* pSrc, int srcStep, Ipp8s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode, int scaleFactor))
IPPAPI ( IppStatus, ippiConvert_64f16u_C1RSfs, (const Ipp64f* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode, int scaleFactor))
IPPAPI ( IppStatus, ippiConvert_64f16s_C1RSfs, (const Ipp64f* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppRoundMode roundMode, int scaleFactor))
IPPAPI ( IppStatus, ippiConvert_8s64f_C1R, (const Ipp8s* pSrc, int srcStep, Ipp64f* pDst, int dstStep, IppiSize roiSize))


/* ////////////////////////////////////////////////////////////////////////////
// Name:          ippiScaleC
//
// Purpose:       Converts data with scaling by formula: dst = src*Val + aVal
//
// Parameters:
//    pSrc    - Pointer to the source image ROI.
//    srcStep - Distance, in bytes, between the starting points of consecutive lines in the source image.
//    mVal    - Multiply value for scaling.
//    aVal    - Add value for scaling.
//    pDst    - Pointer to the destination image ROI.
//    dstStep - Distance, in bytes, between the starting points of consecutive lines in the destination image.
//    roiSize - Size of the ROI.
//    hint    - Option to specify the computation algorithm: ippAlgHintFast(default) or ippAlgHintAccurate.
//  Returns:
//    ippStsNoErr      - OK.
//    ippStsNullPtrErr - Error when any of the specified pointers is NULL.
//    ippStsStepErr    - Error when srcStep or dstStep has a zero or negative value.
//    ippStsSizeErr    - Error when roiSize has a zero or negative value.
*/
IPPAPI(IppStatus, ippiScaleC_8u_C1R   , ( const Ipp8u* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_8u8s_C1R , ( const Ipp8u* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp8s*  pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_8u16u_C1R, ( const Ipp8u* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_8u16s_C1R, ( const Ipp8u* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_8u32s_C1R, ( const Ipp8u* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp32s* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_8u32f_C1R, ( const Ipp8u* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_8u64f_C1R, ( const Ipp8u* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp64f* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))

IPPAPI(IppStatus, ippiScaleC_8s8u_C1R , ( const Ipp8s* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_8s_C1R   , ( const Ipp8s* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp8s*  pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_8s16u_C1R, ( const Ipp8s* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_8s16s_C1R, ( const Ipp8s* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_8s32s_C1R, ( const Ipp8s* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp32s* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_8s32f_C1R, ( const Ipp8s* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_8s64f_C1R, ( const Ipp8s* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp64f* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))

IPPAPI(IppStatus, ippiScaleC_16u8u_C1R , ( const Ipp16u* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_16u8s_C1R , ( const Ipp16u* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp8s*  pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_16u_C1R   , ( const Ipp16u* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_16u16s_C1R, ( const Ipp16u* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_16u32s_C1R, ( const Ipp16u* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp32s* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_16u32f_C1R, ( const Ipp16u* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_16u64f_C1R, ( const Ipp16u* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp64f* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))

IPPAPI(IppStatus, ippiScaleC_16s8u_C1R , ( const Ipp16s* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_16s8s_C1R , ( const Ipp16s* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp8s*  pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_16s16u_C1R, ( const Ipp16s* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_16s_C1R   , ( const Ipp16s* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_16s32s_C1R, ( const Ipp16s* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp32s* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_16s32f_C1R, ( const Ipp16s* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_16s64f_C1R, ( const Ipp16s* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp64f* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))

IPPAPI(IppStatus, ippiScaleC_32s8u_C1R , ( const Ipp32s* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_32s8s_C1R , ( const Ipp32s* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp8s*  pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_32s16u_C1R, ( const Ipp32s* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_32s16s_C1R, ( const Ipp32s* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_32s_C1R   , ( const Ipp32s* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp32s* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_32s32f_C1R, ( const Ipp32s* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_32s64f_C1R, ( const Ipp32s* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp64f* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))

IPPAPI(IppStatus, ippiScaleC_32f8u_C1R , ( const Ipp32f* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_32f8s_C1R , ( const Ipp32f* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp8s*  pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_32f16u_C1R, ( const Ipp32f* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_32f16s_C1R, ( const Ipp32f* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_32f32s_C1R, ( const Ipp32f* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp32s* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_32f_C1R   , ( const Ipp32f* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_32f64f_C1R, ( const Ipp32f* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp64f* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))

IPPAPI(IppStatus, ippiScaleC_64f8u_C1R , ( const Ipp64f* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_64f8s_C1R , ( const Ipp64f* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp8s*  pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_64f16u_C1R, ( const Ipp64f* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_64f16s_C1R, ( const Ipp64f* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_64f32s_C1R, ( const Ipp64f* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp32s* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_64f32f_C1R, ( const Ipp64f* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_64f_C1R   , ( const Ipp64f* pSrc, int srcStep, Ipp64f mVal, Ipp64f aVal, Ipp64f* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))

IPPAPI(IppStatus, ippiScaleC_8u_C1IR,    ( const Ipp8u*  pSrcDst, int srcDstStep, Ipp64f mVal, Ipp64f aVal, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_8s_C1IR,    ( const Ipp8s*  pSrcDst, int srcDstStep, Ipp64f mVal, Ipp64f aVal, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_16u_C1IR,   ( const Ipp16u* pSrcDst, int srcDstStep, Ipp64f mVal, Ipp64f aVal, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_16s_C1IR,   ( const Ipp16s* pSrcDst, int srcDstStep, Ipp64f mVal, Ipp64f aVal, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_32s_C1IR,   ( const Ipp32s* pSrcDst, int srcDstStep, Ipp64f mVal, Ipp64f aVal, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_32f_C1IR,   ( const Ipp32f* pSrcDst, int srcDstStep, Ipp64f mVal, Ipp64f aVal, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI(IppStatus, ippiScaleC_64f_C1IR,   ( const Ipp64f* pSrcDst, int srcDstStep, Ipp64f mVal, Ipp64f aVal, IppiSize roiSize, IppHintAlgorithm hint ))

/* ////////////////////////////////////////////////////////////////////////////
// Name:       ippiBinToGray_1u{8u|16u|16s|32f}_C1R,
//             ippiGrayToBin_{8u|16u|16s|32f}1u_C1R
// Purpose:    Converts a bitonal image to an 8u,16u,16s, or 32f grayscale image and vice versa.
//
// Parameters:
//    pSrc         - Pointer to the source image ROI.
//    srcStep      - Distance, in bytes, between the starting points of consecutive lines in the source image.
//    srcBitOffset - Offset (in bits) from the first byte of the source image row.
//    pDst         - Pointer to the destination image ROI.
//    dstStep      - Distance, in bytes, between the starting points of consecutive lines in the destination image.
//    dstBitOffset - Offset (in bits) from the first byte of the destination image row.
//    roiSize      - Size of the ROI.
//    loVal        - Destination value that corresponds to the "0" value of the corresponding source element.
//    hiVal        - Destination value that corresponds to the "1" value of the corresponding source element.
//    threahold    - Threshold level.
// Returns:
//    ippStsNoErr      - OK.
//    ippStsNullPtrErr - Error when any of the specified pointers is NULL.
//    ippStsSizeErr    - Error when :
//                         roiSize has a zero or negative value.
//                         srcBitOffset or dstBitOffset is less than zero.
//    ippStsStepErr    - Error when srcStep or dstStep has a zero or negative value.
*/
IPPAPI ( IppStatus, ippiBinToGray_1u8u_C1R, ( const Ipp8u* pSrc, int srcStep, int srcBitOffset, Ipp8u*  pDst, int dstStep, IppiSize roiSize, Ipp8u  loVal, Ipp8u  hiVal ))
IPPAPI ( IppStatus, ippiBinToGray_1u16u_C1R,( const Ipp8u* pSrc, int srcStep, int srcBitOffset, Ipp16u* pDst, int dstStep, IppiSize roiSize, Ipp16u loVal, Ipp16u hiVal ))
IPPAPI ( IppStatus, ippiBinToGray_1u16s_C1R,( const Ipp8u* pSrc, int srcStep, int srcBitOffset, Ipp16s* pDst, int dstStep, IppiSize roiSize, Ipp16s loVal, Ipp16s hiVal ))
IPPAPI ( IppStatus, ippiBinToGray_1u32f_C1R,( const Ipp8u* pSrc, int srcStep, int srcBitOffset, Ipp32f* pDst, int dstStep, IppiSize roiSize, Ipp32f loVal, Ipp32f hiVal ))

IPPAPI ( IppStatus, ippiGrayToBin_8u1u_C1R, (const Ipp8u*  pSrc, int srcStep, Ipp8u* pDst, int dstStep, int dstBitOffset, IppiSize roiSize, Ipp8u  threshold ))
IPPAPI ( IppStatus, ippiGrayToBin_16u1u_C1R,(const Ipp16u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, int dstBitOffset, IppiSize roiSize, Ipp16u threshold ))
IPPAPI ( IppStatus, ippiGrayToBin_16s1u_C1R,(const Ipp16s* pSrc, int srcStep, Ipp8u* pDst, int dstStep, int dstBitOffset, IppiSize roiSize, Ipp16s threshold ))
IPPAPI ( IppStatus, ippiGrayToBin_32f1u_C1R,(const Ipp32f* pSrc, int srcStep, Ipp8u* pDst, int dstStep, int dstBitOffset, IppiSize roiSize, Ipp32f threshold ))


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
IPPAPI(IppStatus, ippiPolarToCart_32fc_C1R,(const Ipp32f* pSrcMagn, const Ipp32f* pSrcPhase, int srcStep, IppiSize roiSize, Ipp32fc *pDst , int dstStep))
IPPAPI(IppStatus, ippiPolarToCart_32fc_C3R,(const Ipp32f* pSrcMagn, const Ipp32f* pSrcPhase, int srcStep, IppiSize roiSize, Ipp32fc *pDst , int dstStep))



/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiSwapChannels
//
//  Purpose:    Changes the order of channels of the image
//              The function performs operation for each pixel:
//                  pDst[0] = pSrc[ dstOrder[0] ]
//                  pDst[1] = pSrc[ dstOrder[1] ]
//                  pDst[2] = pSrc[ dstOrder[2] ]
//                  pDst[3] = pSrc[ dstOrder[3] ]
//
//  Returns:
//    ippStsNullPtrErr      One of the pointers is NULL
//    ippStsSizeErr         roiSize has a field with zero or negative value
//    ippStsStepErr         One of the step values is less than or equal to zero
//    ippStsChannelOrderErr dstOrder is out of the range,
//                           it should be: dstOrder[3] = { 0..2, 0..2, 0..2 } for C3R, AC4R image
//                           and dstOrder[4] = { 0..3, 0..3, 0..3 } for C4R image
//    ippStsNoErr           OK
//
//  Parameters:
//    pSrc           Pointer  to the source image
//    srcStep        Step in bytes through the source image
//    pDst           Pointer to the  destination image
//    dstStep        Step in bytes through the destination image
//    pSrcDst        Pointer to the source/destination image (in-place flavors)
//    srcDstStep     Step through the source/destination image (in-place flavors)
//    roiSize        Size of the ROI
//    dstOrder       The order of channels in the destination image
*/
IPPAPI ( IppStatus, ippiSwapChannels_8u_C3R,
       ( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
         IppiSize roiSize, const int dstOrder[3] ))
IPPAPI ( IppStatus, ippiSwapChannels_8u_AC4R,
       ( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
         IppiSize roiSize, const int dstOrder[3] ))
IPPAPI ( IppStatus, ippiSwapChannels_8u_C4R,
       ( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
         IppiSize roiSize, const int dstOrder[4] ))
IPPAPI ( IppStatus, ippiSwapChannels_16u_C3R,
       ( const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
         IppiSize roiSize, const int dstOrder[3] ))
IPPAPI ( IppStatus, ippiSwapChannels_16u_AC4R,
       ( const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
         IppiSize roiSize, const int dstOrder[3] ))
IPPAPI ( IppStatus, ippiSwapChannels_16u_C4R,
       ( const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep,
         IppiSize roiSize, const int dstOrder[4] ))
IPPAPI ( IppStatus, ippiSwapChannels_16s_C3R,
       ( const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
         IppiSize roiSize, const int dstOrder[3] ))
IPPAPI ( IppStatus, ippiSwapChannels_16s_AC4R,
       ( const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
         IppiSize roiSize, const int dstOrder[3] ))
IPPAPI ( IppStatus, ippiSwapChannels_16s_C4R,
       ( const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep,
         IppiSize roiSize, const int dstOrder[4] ))
IPPAPI ( IppStatus, ippiSwapChannels_32s_C3R,
       ( const Ipp32s* pSrc, int srcStep, Ipp32s* pDst, int dstStep,
         IppiSize roiSize, const int dstOrder[3] ))
IPPAPI ( IppStatus, ippiSwapChannels_32s_AC4R,
       ( const Ipp32s* pSrc, int srcStep, Ipp32s* pDst, int dstStep,
         IppiSize roiSize, const int dstOrder[3] ))
IPPAPI ( IppStatus, ippiSwapChannels_32s_C4R,
       ( const Ipp32s* pSrc, int srcStep, Ipp32s* pDst, int dstStep,
         IppiSize roiSize, const int dstOrder[4] ))
IPPAPI ( IppStatus, ippiSwapChannels_32f_C3R,
       ( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
         IppiSize roiSize, const int dstOrder[3] ))
IPPAPI ( IppStatus, ippiSwapChannels_32f_AC4R,
       ( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
         IppiSize roiSize, const int dstOrder[3] ))
IPPAPI ( IppStatus, ippiSwapChannels_32f_C4R,
       ( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
         IppiSize roiSize, const int dstOrder[4] ))

IPPAPI ( IppStatus, ippiSwapChannels_8u_C3IR,
       ( Ipp8u* pSrcDst, int srcDstStep,
             IppiSize roiSize, const int dstOrder[3] ))

IPPAPI ( IppStatus, ippiSwapChannels_8u_C4IR,
       ( Ipp8u* pSrcDst, int srcDstStep,
             IppiSize roiSize, const int dstOrder[4] ))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiSwapChannels C3C4R,C4C3R
//
//  Purpose:    Changes the order of channels of the image
//              The function performs operation for each pixel:
//  a) C3C4R.
//    if(dstOrder[i] < 3) dst[i] = src[dstOrder[i]];
//    if(dstOrder[i] == 3) dst[i] = val;
//    if(dstOrder[i] > 3) dst[i] does not change;
//    i = 0,1,2,3
//  b) C4C3R.
//    dst[0] = src [dstOrder[0]];
//    dst[1] = src [dstOrder[1]];
//    dst[2] = src [dstOrder[2]];
//
//  Returns:
//    ippStsNullPtrErr      One of the pointers is NULL
//    ippStsSizeErr         roiSize has a field with zero or negative value
//    ippStsChannelOrderErr dstOrder is out of the range, it should be:
//                            a) C3C4R.
//                              dstOrder[i] => 0, i = 0,1,2,3.
//                            b) C4C3R.
//                              0 <= dstOrder[i] <= 3, i = 0,1,2.
//    ippStsNoErr     OK
//
//  Parameters:
//    pSrc           Pointer  to the source image
//    srcStep        Step in bytes through the source image
//    pDst           Pointer to the  destination image
//    dstStep        Step in bytes through the destination image
//    roiSize        Size of the ROI
//    dstOrder       The order of channels in the destination image
//    val            Constant value for C3C4R
*/
IPPAPI ( IppStatus, ippiSwapChannels_8u_C3C4R,
                    ( const Ipp8u* pSrc, int srcStep,
                            Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                   const int dstOrder[4], Ipp8u val ))
IPPAPI ( IppStatus, ippiSwapChannels_8u_C4C3R,
                    ( const Ipp8u* pSrc, int srcStep,
                            Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                   const int dstOrder[3] ))
IPPAPI ( IppStatus, ippiSwapChannels_16s_C3C4R,
                    ( const Ipp16s* pSrc, int srcStep,
                            Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                    const int dstOrder[4], Ipp16s val ))
IPPAPI ( IppStatus, ippiSwapChannels_16s_C4C3R,
                    ( const Ipp16s* pSrc, int srcStep,
                            Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                    const int dstOrder[3] ))
IPPAPI ( IppStatus, ippiSwapChannels_16u_C3C4R,
                    ( const Ipp16u* pSrc, int srcStep,
                            Ipp16u* pDst, int dstStep, IppiSize roiSize,
                                    const int dstOrder[4], Ipp16u val ))
IPPAPI ( IppStatus, ippiSwapChannels_16u_C4C3R,
                    ( const Ipp16u* pSrc, int srcStep,
                            Ipp16u* pDst, int dstStep, IppiSize roiSize,
                                    const int dstOrder[3] ))
IPPAPI ( IppStatus, ippiSwapChannels_32s_C3C4R,
                    ( const Ipp32s* pSrc, int srcStep,
                            Ipp32s* pDst, int dstStep, IppiSize roiSize,
                                    const int dstOrder[4], Ipp32s val ))
IPPAPI ( IppStatus, ippiSwapChannels_32s_C4C3R,
                    ( const Ipp32s* pSrc, int srcStep,
                            Ipp32s* pDst, int dstStep, IppiSize roiSize,
                                    const int dstOrder[3] ))
IPPAPI ( IppStatus, ippiSwapChannels_32f_C3C4R,
                    ( const Ipp32f* pSrc, int srcStep,
                            Ipp32f* pDst, int dstStep, IppiSize roiSize,
                                    const int dstOrder[4], Ipp32f val ))
IPPAPI ( IppStatus, ippiSwapChannels_32f_C4C3R,
                    ( const Ipp32f* pSrc, int srcStep,
                            Ipp32f* pDst, int dstStep, IppiSize roiSize,
                                    const int dstOrder[3] ))


/* /////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiScale
//
//  Purpose:   Scales pixel values of an image and converts them to another bit depth
//              dst = a + b * src;
//              a = type_min_dst - b * type_min_src;
//              b = (type_max_dst - type_min_dst) / (type_max_src - type_min_src).
//
//  Returns:
//    ippStsNullPtrErr      One of the pointers is NULL
//    ippStsSizeErr         roiSize has a field with zero or negative value
//    ippStsStepErr         One of the step values is less than or equal to zero
//    ippStsScaleRangeErr   Input data bounds are incorrect (vMax - vMin <= 0)
//    ippStsNoErr           OK
//
//  Parameters:
//    pSrc            Pointer  to the source image
//    srcStep         Step through the source image
//    pDst            Pointer to the  destination image
//    dstStep         Step through the destination image
//    roiSize         Size of the ROI
//    vMin, vMax      Minimum and maximum values of the input data (32f).
//    hint            Option to select the algorithmic implementation:
//                        1). hint == ippAlgHintAccurate
//                                  - accuracy e-8, but slowly;
//                        2). hint == ippAlgHintFast,
//                                 or ippAlgHintNone
//                                  - accuracy e-3, but quickly.
*/
IPPAPI ( IppStatus, ippiScale_8u16u_C1R, (const Ipp8u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiScale_8u16u_C3R, (const Ipp8u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiScale_8u16u_C4R, (const Ipp8u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiScale_8u16u_AC4R,(const Ipp8u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize ))

IPPAPI ( IppStatus, ippiScale_8u16s_C1R, (const Ipp8u* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiScale_8u16s_C3R, (const Ipp8u* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiScale_8u16s_C4R, (const Ipp8u* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiScale_8u16s_AC4R,(const Ipp8u* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize ))

IPPAPI ( IppStatus, ippiScale_8u32s_C1R, (const Ipp8u* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiScale_8u32s_C3R, (const Ipp8u* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiScale_8u32s_C4R, (const Ipp8u* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI ( IppStatus, ippiScale_8u32s_AC4R,(const Ipp8u* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize ))

IPPAPI ( IppStatus, ippiScale_8u32f_C1R, (const Ipp8u* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, Ipp32f vMin, Ipp32f vMax ))
IPPAPI ( IppStatus, ippiScale_8u32f_C3R, (const Ipp8u* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, Ipp32f vMin, Ipp32f vMax ))
IPPAPI ( IppStatus, ippiScale_8u32f_C4R, (const Ipp8u* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, Ipp32f vMin, Ipp32f vMax ))
IPPAPI ( IppStatus, ippiScale_8u32f_AC4R,(const Ipp8u* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, Ipp32f vMin, Ipp32f vMax ))

IPPAPI ( IppStatus, ippiScale_16u8u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI ( IppStatus, ippiScale_16u8u_C3R, (const Ipp16u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI ( IppStatus, ippiScale_16u8u_C4R, (const Ipp16u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI ( IppStatus, ippiScale_16u8u_AC4R,(const Ipp16u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))

IPPAPI ( IppStatus, ippiScale_16s8u_C1R, (const Ipp16s* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI ( IppStatus, ippiScale_16s8u_C3R, (const Ipp16s* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI ( IppStatus, ippiScale_16s8u_C4R, (const Ipp16s* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI ( IppStatus, ippiScale_16s8u_AC4R,(const Ipp16s* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))

IPPAPI ( IppStatus, ippiScale_32s8u_C1R, (const Ipp32s* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI ( IppStatus, ippiScale_32s8u_C3R, (const Ipp32s* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI ( IppStatus, ippiScale_32s8u_C4R, (const Ipp32s* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))
IPPAPI ( IppStatus, ippiScale_32s8u_AC4R,(const Ipp32s* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint ))

IPPAPI ( IppStatus, ippiScale_32f8u_C1R, (const Ipp32f* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, Ipp32f vMin, Ipp32f vMax ))
IPPAPI ( IppStatus, ippiScale_32f8u_C3R, (const Ipp32f* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, Ipp32f vMin, Ipp32f vMax ))
IPPAPI ( IppStatus, ippiScale_32f8u_C4R, (const Ipp32f* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, Ipp32f vMin, Ipp32f vMax ))
IPPAPI ( IppStatus, ippiScale_32f8u_AC4R,(const Ipp32f* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize, Ipp32f vMin, Ipp32f vMax ))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiMin
//  Purpose:        computes the minimum of image pixel values
//  Returns:        IppStatus
//    ippStsNoErr        OK
//    ippStsNullPtrErr   One of the pointers is NULL
//    ippStsSizeErr      roiSize has a field with zero or negative value
//  Parameters:
//    pSrc        Pointer to the source image.
//    srcStep     Step through the source image
//    roiSize     Size of the source image ROI.
//    pMin        Pointer to the result (C1)
//    min         Array containing results (C3, AC4, C4)
*/

IPPAPI(IppStatus, ippiMin_8u_C1R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp8u* pMin))
IPPAPI(IppStatus, ippiMin_8u_C3R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp8u min[3]))
IPPAPI(IppStatus, ippiMin_8u_AC4R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp8u min[3]))
IPPAPI(IppStatus, ippiMin_8u_C4R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp8u min[4]))

IPPAPI(IppStatus, ippiMin_16s_C1R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp16s* pMin))
IPPAPI(IppStatus, ippiMin_16s_C3R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp16s min[3]))
IPPAPI(IppStatus, ippiMin_16s_AC4R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp16s min[3]))
IPPAPI(IppStatus, ippiMin_16s_C4R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp16s min[4]))

IPPAPI(IppStatus, ippiMin_16u_C1R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp16u* pMin))
IPPAPI(IppStatus, ippiMin_16u_C3R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp16u min[3]))
IPPAPI(IppStatus, ippiMin_16u_AC4R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp16u min[3]))
IPPAPI(IppStatus, ippiMin_16u_C4R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp16u min[4]))

IPPAPI(IppStatus, ippiMin_32f_C1R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32f* pMin))
IPPAPI(IppStatus, ippiMin_32f_C3R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32f min[3]))
IPPAPI(IppStatus, ippiMin_32f_AC4R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32f min[3]))
IPPAPI(IppStatus, ippiMin_32f_C4R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32f min[4]))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiMinIndx
//  Purpose:        computes the minimum of image pixel values and retrieves
//                  the x and y coordinates of pixels with this value
//  Returns:        IppStatus
//    ippStsNoErr        OK
//    ippStsNullPtrErr   One of the pointers is NULL
//    ippStsSizeErr      roiSize has a field with zero or negative value
//  Parameters:
//    pSrc        Pointer to the source image.
//    srcStep     Step in bytes through the source image
//    roiSize     Size of the source image ROI.
//    pMin        Pointer to the result (C1)
//    min         Array of the results (C3, AC4, C4)
//    pIndexX     Pointer to the x coordinate of the pixel with min value (C1)
//    pIndexY     Pointer to the y coordinate of the pixel with min value (C1)
//    indexX      Array containing the x coordinates of the pixel with min value (C3, AC4, C4)
//    indexY      Array containing the y coordinates of the pixel with min value (C3, AC4, C4)
*/

IPPAPI(IppStatus, ippiMinIndx_8u_C1R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp8u* pMin, int* pIndexX, int* pIndexY))
IPPAPI(IppStatus, ippiMinIndx_8u_C3R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp8u min[3], int indexX[3], int indexY[3]))
IPPAPI(IppStatus, ippiMinIndx_8u_AC4R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp8u min[3], int indexX[3], int indexY[3]))
IPPAPI(IppStatus, ippiMinIndx_8u_C4R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp8u min[4], int indexX[4], int indexY[4]))

IPPAPI(IppStatus, ippiMinIndx_16s_C1R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp16s* pMin, int* pIndexX, int* pIndexY))
IPPAPI(IppStatus, ippiMinIndx_16s_C3R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp16s min[3], int indexX[3], int indexY[3]))
IPPAPI(IppStatus, ippiMinIndx_16s_AC4R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp16s min[3], int indexX[3], int indexY[3]))
IPPAPI(IppStatus, ippiMinIndx_16s_C4R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp16s min[4], int indexX[4], int indexY[4]))

IPPAPI(IppStatus, ippiMinIndx_16u_C1R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp16u* pMin, int* pIndexX, int* pIndexY))
IPPAPI(IppStatus, ippiMinIndx_16u_C3R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp16u min[3], int indexX[3], int indexY[3]))
IPPAPI(IppStatus, ippiMinIndx_16u_AC4R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp16u min[3], int indexX[3], int indexY[3]))
IPPAPI(IppStatus, ippiMinIndx_16u_C4R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp16u min[4], int indexX[4], int indexY[4]))

IPPAPI(IppStatus, ippiMinIndx_32f_C1R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32f* pMin, int* pIndexX, int* pIndexY))
IPPAPI(IppStatus, ippiMinIndx_32f_C3R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32f min[3], int indexX[3], int indexY[3]))
IPPAPI(IppStatus, ippiMinIndx_32f_AC4R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32f min[3], int indexX[3], int indexY[3]))
IPPAPI(IppStatus, ippiMinIndx_32f_C4R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32f min[4], int indexX[4], int indexY[4]))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiMax
//  Purpose:        computes the maximum of image pixel values
//  Returns:        IppStatus
//    ippStsNoErr        OK
//    ippStsNullPtrErr   One of the pointers is NULL
//    ippStsSizeErr      roiSize has a field with zero or negative value
//  Parameters:
//    pSrc        Pointer to the source image.
//    srcStep     Step in bytes through the source image
//    roiSize     Size of the source image ROI.
//    pMax        Pointer to the result (C1)
//    max         Array containing the results (C3, AC4, C4)
*/

IPPAPI(IppStatus, ippiMax_8u_C1R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp8u* pMax))
IPPAPI(IppStatus, ippiMax_8u_C3R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp8u max[3]))
IPPAPI(IppStatus, ippiMax_8u_AC4R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp8u max[3]))
IPPAPI(IppStatus, ippiMax_8u_C4R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp8u max[4]))

IPPAPI(IppStatus, ippiMax_16s_C1R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp16s* pMax))
IPPAPI(IppStatus, ippiMax_16s_C3R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp16s max[3]))
IPPAPI(IppStatus, ippiMax_16s_AC4R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp16s max[3]))
IPPAPI(IppStatus, ippiMax_16s_C4R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp16s max[4]))

IPPAPI(IppStatus, ippiMax_16u_C1R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp16u* pMax))
IPPAPI(IppStatus, ippiMax_16u_C3R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp16u max[3]))
IPPAPI(IppStatus, ippiMax_16u_AC4R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp16u max[3]))
IPPAPI(IppStatus, ippiMax_16u_C4R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp16u max[4]))

IPPAPI(IppStatus, ippiMax_32f_C1R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32f* pMax))
IPPAPI(IppStatus, ippiMax_32f_C3R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32f max[3]))
IPPAPI(IppStatus, ippiMax_32f_AC4R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32f max[3]))
IPPAPI(IppStatus, ippiMax_32f_C4R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32f max[4]))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiMaxIndx
//  Purpose:        computes the maximum of image pixel values and retrieves
//                  the x and y coordinates of pixels with this value
//  Returns:        IppStatus
//    ippStsNoErr        OK
//    ippStsNullPtrErr   One of the pointers is NULL
//    ippStsSizeErr      roiSize has a field with zero or negative value
//  Parameters:
//    pSrc        Pointer to the source image.
//    srcStep     Step in bytes through the source image
//    roiSize     Size of the source image ROI.
//    pMax        Pointer to the result (C1)
//    max         Array of the results (C3, AC4, C4)
//    pIndexX     Pointer to the x coordinate of the pixel with max value (C1)
//    pIndexY     Pointer to the y coordinate of the pixel with max value (C1)
//    indexX      Array containing the x coordinates of the pixel with max value (C3, AC4, C4)
//    indexY      Array containing the y coordinates of the pixel with max value (C3, AC4, C4)
*/

IPPAPI(IppStatus, ippiMaxIndx_8u_C1R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp8u* pMax, int* pIndexX, int* pIndexY))
IPPAPI(IppStatus, ippiMaxIndx_8u_C3R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp8u max[3], int indexX[3], int indexY[3]))
IPPAPI(IppStatus, ippiMaxIndx_8u_AC4R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp8u max[3], int indexX[3], int indexY[3]))
IPPAPI(IppStatus, ippiMaxIndx_8u_C4R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp8u max[4], int indexX[4], int indexY[4]))

IPPAPI(IppStatus, ippiMaxIndx_16s_C1R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp16s* pMax, int* pIndexX, int* pIndexY))
IPPAPI(IppStatus, ippiMaxIndx_16s_C3R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp16s max[3], int indexX[3], int indexY[3]))
IPPAPI(IppStatus, ippiMaxIndx_16s_AC4R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp16s max[3], int indexX[3], int indexY[3]))
IPPAPI(IppStatus, ippiMaxIndx_16s_C4R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp16s max[4], int indexX[4], int indexY[4]))

IPPAPI(IppStatus, ippiMaxIndx_16u_C1R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp16u* pMax, int* pIndexX, int* pIndexY))
IPPAPI(IppStatus, ippiMaxIndx_16u_C3R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp16u max[3], int indexX[3], int indexY[3]))
IPPAPI(IppStatus, ippiMaxIndx_16u_AC4R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp16u max[3], int indexX[3], int indexY[3]))
IPPAPI(IppStatus, ippiMaxIndx_16u_C4R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp16u max[4], int indexX[4], int indexY[4]))

IPPAPI(IppStatus, ippiMaxIndx_32f_C1R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32f* pMax, int* pIndexX, int* pIndexY))
IPPAPI(IppStatus, ippiMaxIndx_32f_C3R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32f max[3], int indexX[3], int indexY[3]))
IPPAPI(IppStatus, ippiMaxIndx_32f_AC4R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32f max[3], int indexX[3], int indexY[3]))
IPPAPI(IppStatus, ippiMaxIndx_32f_C4R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32f max[4], int indexX[4], int indexY[4]))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiMinMax
//  Purpose:        computes the minimum and maximum of image pixel value
//  Returns:        IppStatus
//    ippStsNoErr        OK
//    ippStsNullPtrErr   One of the pointers is NULL
//    ippStsSizeErr      roiSize has a field with zero or negative value
//  Parameters:
//    pSrc        Pointer to the source image
//    srcStep     Step in bytes through the source image
//    roiSize     Size of the source image ROI.
//    pMin, pMax  Pointers to the results (C1)
//    min, max    Arrays containing the results (C3, AC4, C4)
*/

IPPAPI(IppStatus, ippiMinMax_8u_C1R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp8u* pMin, Ipp8u* pMax))
IPPAPI(IppStatus, ippiMinMax_8u_C3R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp8u min[3], Ipp8u max[3]))
IPPAPI(IppStatus, ippiMinMax_8u_AC4R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp8u min[3], Ipp8u max[3]))
IPPAPI(IppStatus, ippiMinMax_8u_C4R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, Ipp8u min[4], Ipp8u max[4]))

IPPAPI(IppStatus, ippiMinMax_16s_C1R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp16s* pMin, Ipp16s* pMax))
IPPAPI(IppStatus, ippiMinMax_16s_C3R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp16s min[3], Ipp16s max[3]))
IPPAPI(IppStatus, ippiMinMax_16s_AC4R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp16s min[3], Ipp16s max[3]))
IPPAPI(IppStatus, ippiMinMax_16s_C4R, (const Ipp16s* pSrc, int srcStep, IppiSize roiSize, Ipp16s min[4], Ipp16s max[4]))

IPPAPI(IppStatus, ippiMinMax_16u_C1R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp16u* pMin, Ipp16u* pMax))
IPPAPI(IppStatus, ippiMinMax_16u_C3R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp16u min[3], Ipp16u max[3]))
IPPAPI(IppStatus, ippiMinMax_16u_AC4R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp16u min[3], Ipp16u max[3]))
IPPAPI(IppStatus, ippiMinMax_16u_C4R, (const Ipp16u* pSrc, int srcStep, IppiSize roiSize, Ipp16u min[4], Ipp16u max[4]))

IPPAPI(IppStatus, ippiMinMax_32f_C1R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32f* pMin, Ipp32f* pMax))
IPPAPI(IppStatus, ippiMinMax_32f_C3R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32f min[3], Ipp32f max[3]))
IPPAPI(IppStatus, ippiMinMax_32f_AC4R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32f min[3], Ipp32f max[3]))
IPPAPI(IppStatus, ippiMinMax_32f_C4R, (const Ipp32f* pSrc, int srcStep, IppiSize roiSize, Ipp32f min[4], Ipp32f max[4]))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiBlockMinMax_32f_C1R, ippiBlockMinMax_16s_C1R,
//              ippiBlockMinMax_16u_C1R, ippiBlockMinMax_8u_C1R .
//
//  Purpose:    Finds minimum and maximum values for blocks of the source image.
//
//  Parameters:
//    pSrc                Pointer to the source image ROI.
//    srcStep             Distance, in bytes, between the starting points of consecutive lines in the source image.
//    srcSize             Size, in pixels, of the source image.
//    pDstMin             Pointer to the destination image to store minimum values per block.
//    dstMinStep          Distance, in bytes, between the starting points of consecutive lines in the pDstMin image.
//    pDstMax             Pointer to the destination image to store maximum values per block.
//    dstMaxStep          Distance, in bytes, between the starting points of consecutive lines in the pDstMax image.
//    blockSize           Size, in pixels, of the block.
//    pDstGlobalMin       The destination pointer to store minimum value for the entire source image.
//    pDstGlobalMax       The destination pointer to store maximum value for the entire source image.
//  Returns:
//    ippStsNoErr      - OK.
//    ippStsNullPtrErr - Error when any of the specified pointers is NULL.
//    ippStsStepErr    - Error when :
//                         srcStep is less than srcSize.width*sizeof(*pSrc).
//                         dstMinStep, or dstMaxStep is less than dstSize.width*sizeof(*pDst).
//    ippStsSizeErr    - Error when srcSize or blockSize has a zero or negative value.
*/
IPPAPI(IppStatus, ippiBlockMinMax_32f_C1R, (const Ipp32f *pSrc, int srcStep, IppiSize srcSize, Ipp32f *pDstMin, int dstMinStep, Ipp32f *pDstMax, int dstMaxStep,
                                             IppiSize blockSize, Ipp32f *pDstGlobalMin, Ipp32f *pDstGlobalMax))
IPPAPI(IppStatus, ippiBlockMinMax_16s_C1R, (const Ipp16s *pSrc, int srcStep, IppiSize srcSize, Ipp16s *pDstMin, int dstMinStep, Ipp16s *pDstMax, int dstMaxStep,
                                             IppiSize blockSize, Ipp16s *pDstGlobalMin, Ipp16s *pDstGlobalMax))
IPPAPI(IppStatus, ippiBlockMinMax_16u_C1R, (const Ipp16u *pSrc, int srcStep, IppiSize srcSize, Ipp16u *pDstMin, int dstMinStep, Ipp16u *pDstMax, int dstMaxStep,
                                             IppiSize blockSize, Ipp16u *pDstGlobalMin, Ipp16u *pDstGlobalMax))
IPPAPI(IppStatus, ippiBlockMinMax_8u_C1R , (const Ipp8u  *pSrc, int srcStep, IppiSize srcSize, Ipp8u  *pDstMin, int dstMinStep, Ipp8u  *pDstMax, int dstMaxStep,
                                             IppiSize blockSize, Ipp8u  *pDstGlobalMin, Ipp8u  *pDstGlobalMax))



/* ////////////////////////////////////////////////////////////////////////////
//  Names:              ippiMinEvery, ippiMaxEvery
//  Purpose:            calculation min/max value for every element of two images
//  Parameters:
//   pSrc               pointer to input image
//   pSrcDst            pointer to input/output image
//    srcStep           Step in bytes through the source image
//    roiSize           Size of the source image ROI.
//  Return:
//   ippStsNullPtrErr   pointer(s) to the data is NULL
//   ippStsSizeErr      roiSize has a field with zero or negative value
//   ippStsNoErr        otherwise
*/

IPPAPI(IppStatus,ippiMaxEvery_8u_C1IR,(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMinEvery_8u_C1IR,(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMaxEvery_16s_C1IR,(const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMinEvery_16s_C1IR,(const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMaxEvery_16u_C1IR,(const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMinEvery_16u_C1IR,(const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMaxEvery_32f_C1IR,(const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMinEvery_32f_C1IR,(const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))

IPPAPI(IppStatus,ippiMaxEvery_8u_C3IR,(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMinEvery_8u_C3IR,(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMaxEvery_16s_C3IR,(const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMinEvery_16s_C3IR,(const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMaxEvery_16u_C3IR,(const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMinEvery_16u_C3IR,(const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMaxEvery_32f_C3IR,(const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMinEvery_32f_C3IR,(const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))

IPPAPI(IppStatus,ippiMaxEvery_8u_C4IR,(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMinEvery_8u_C4IR,(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMaxEvery_16s_C4IR,(const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMinEvery_16s_C4IR,(const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMaxEvery_16u_C4IR,(const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMinEvery_16u_C4IR,(const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMaxEvery_32f_C4IR,(const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMinEvery_32f_C4IR,(const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))

IPPAPI(IppStatus,ippiMaxEvery_8u_AC4IR,(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMinEvery_8u_AC4IR,(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMaxEvery_16s_AC4IR,(const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMinEvery_16s_AC4IR,(const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMaxEvery_16u_AC4IR,(const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMinEvery_16u_AC4IR,(const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMaxEvery_32f_AC4IR,(const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMinEvery_32f_AC4IR,(const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst,
                                                                   int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMinEvery_8u_C1R,(const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMinEvery_16u_C1R,(const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMinEvery_32f_C1R,(const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2, int src2Step, Ipp32f* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMaxEvery_8u_C1R,(const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMaxEvery_16u_C1R,(const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiMaxEvery_32f_C1R,(const Ipp32f* pSrc1, int src1Step, const Ipp32f* pSrc2, int src2Step, Ipp32f* pDst, int dstStep, IppiSize roiSize))

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

IPPAPI(IppStatus, ippiAnd_8u_C1R, (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAnd_8u_C3R, (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAnd_8u_C4R, (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAnd_8u_AC4R, (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAnd_8u_C1IR, (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAnd_8u_C3IR, (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAnd_8u_C4IR, (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAnd_8u_AC4IR, (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAndC_8u_C1R, (const Ipp8u* pSrc, int srcStep, Ipp8u value, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAndC_8u_C3R, (const Ipp8u* pSrc, int srcStep, const Ipp8u value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAndC_8u_C4R, (const Ipp8u* pSrc, int srcStep, const Ipp8u value[4], Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAndC_8u_AC4R, (const Ipp8u* pSrc, int srcStep, const Ipp8u value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAndC_8u_C1IR, (Ipp8u value, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAndC_8u_C3IR, (const Ipp8u value[3], Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAndC_8u_C4IR, (const Ipp8u value[4], Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAndC_8u_AC4IR, (const Ipp8u value[3], Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAnd_16u_C1R, (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAnd_16u_C3R, (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAnd_16u_C4R, (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAnd_16u_AC4R, (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAnd_16u_C1IR, (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAnd_16u_C3IR, (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAnd_16u_C4IR, (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAnd_16u_AC4IR, (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAndC_16u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp16u value, Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAndC_16u_C3R, (const Ipp16u* pSrc, int srcStep, const Ipp16u value[3], Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAndC_16u_C4R, (const Ipp16u* pSrc, int srcStep, const Ipp16u value[4], Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAndC_16u_AC4R, (const Ipp16u* pSrc, int srcStep, const Ipp16u value[3], Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAndC_16u_C1IR, (Ipp16u value, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAndC_16u_C3IR, (const Ipp16u value[3], Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAndC_16u_C4IR, (const Ipp16u value[4], Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAndC_16u_AC4IR, (const Ipp16u value[3], Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAnd_32s_C1R, (const Ipp32s* pSrc1, int src1Step, const Ipp32s* pSrc2, int src2Step, Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAnd_32s_C3R, (const Ipp32s* pSrc1, int src1Step, const Ipp32s* pSrc2, int src2Step, Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAnd_32s_C4R, (const Ipp32s* pSrc1, int src1Step, const Ipp32s* pSrc2, int src2Step, Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAnd_32s_AC4R, (const Ipp32s* pSrc1, int src1Step, const Ipp32s* pSrc2, int src2Step, Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAnd_32s_C1IR, (const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAnd_32s_C3IR, (const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAnd_32s_C4IR, (const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAnd_32s_AC4IR, (const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAndC_32s_C1R, (const Ipp32s* pSrc, int srcStep, Ipp32s value, Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAndC_32s_C3R, (const Ipp32s* pSrc, int srcStep, const Ipp32s value[3], Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAndC_32s_C4R, (const Ipp32s* pSrc, int srcStep, const Ipp32s value[4], Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAndC_32s_AC4R, (const Ipp32s* pSrc, int srcStep, const Ipp32s value[3], Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAndC_32s_C1IR, (Ipp32s value, Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAndC_32s_C3IR, (const Ipp32s value[3], Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAndC_32s_C4IR, (const Ipp32s value[4], Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiAndC_32s_AC4IR, (const Ipp32s value[3], Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))

IPPAPI(IppStatus, ippiOr_8u_C1R, (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOr_8u_C3R, (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOr_8u_C4R, (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOr_8u_AC4R, (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOr_8u_C1IR, (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOr_8u_C3IR, (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOr_8u_C4IR, (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOr_8u_AC4IR, (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_8u_C1R, (const Ipp8u* pSrc, int srcStep, Ipp8u value, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_8u_C3R, (const Ipp8u* pSrc, int srcStep, const Ipp8u value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_8u_C4R, (const Ipp8u* pSrc, int srcStep, const Ipp8u value[4], Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_8u_AC4R, (const Ipp8u* pSrc, int srcStep, const Ipp8u value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_8u_C1IR, (Ipp8u value, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_8u_C3IR, (const Ipp8u value[3], Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_8u_C4IR, (const Ipp8u value[4], Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_8u_AC4IR, (const Ipp8u value[3], Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOr_16u_C1R, (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOr_16u_C3R, (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOr_16u_C4R, (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOr_16u_AC4R, (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOr_16u_C1IR, (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOr_16u_C3IR, (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOr_16u_C4IR, (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOr_16u_AC4IR, (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_16u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp16u value, Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_16u_C3R, (const Ipp16u* pSrc, int srcStep, const Ipp16u value[3], Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_16u_C4R, (const Ipp16u* pSrc, int srcStep, const Ipp16u value[4], Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_16u_AC4R, (const Ipp16u* pSrc, int srcStep, const Ipp16u value[3], Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_16u_C1IR, (Ipp16u value, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_16u_C3IR, (const Ipp16u value[3], Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_16u_C4IR, (const Ipp16u value[4], Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_16u_AC4IR, (const Ipp16u value[3], Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOr_32s_C1R, (const Ipp32s* pSrc1, int src1Step, const Ipp32s* pSrc2, int src2Step, Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOr_32s_C3R, (const Ipp32s* pSrc1, int src1Step, const Ipp32s* pSrc2, int src2Step, Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOr_32s_C4R, (const Ipp32s* pSrc1, int src1Step, const Ipp32s* pSrc2, int src2Step, Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOr_32s_AC4R, (const Ipp32s* pSrc1, int src1Step, const Ipp32s* pSrc2, int src2Step, Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOr_32s_C1IR, (const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOr_32s_C3IR, (const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOr_32s_C4IR, (const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOr_32s_AC4IR, (const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_32s_C1R, (const Ipp32s* pSrc, int srcStep, Ipp32s value, Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_32s_C3R, (const Ipp32s* pSrc, int srcStep, const Ipp32s value[3], Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_32s_C4R, (const Ipp32s* pSrc, int srcStep, const Ipp32s value[4], Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_32s_AC4R, (const Ipp32s* pSrc, int srcStep, const Ipp32s value[3], Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_32s_C1IR, (Ipp32s value, Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_32s_C3IR, (const Ipp32s value[3], Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_32s_C4IR, (const Ipp32s value[4], Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiOrC_32s_AC4IR, (const Ipp32s value[3], Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))

IPPAPI(IppStatus, ippiXor_8u_C1R, (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXor_8u_C3R, (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXor_8u_C4R, (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXor_8u_AC4R, (const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXor_8u_C1IR, (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXor_8u_C3IR, (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXor_8u_C4IR, (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXor_8u_AC4IR, (const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_8u_C1R, (const Ipp8u* pSrc, int srcStep, Ipp8u value, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_8u_C3R, (const Ipp8u* pSrc, int srcStep, const Ipp8u value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_8u_C4R, (const Ipp8u* pSrc, int srcStep, const Ipp8u value[4], Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_8u_AC4R, (const Ipp8u* pSrc, int srcStep, const Ipp8u value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_8u_C1IR, (Ipp8u value, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_8u_C3IR, (const Ipp8u value[3], Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_8u_C4IR, (const Ipp8u value[4], Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_8u_AC4IR, (const Ipp8u value[3], Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXor_16u_C1R, (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXor_16u_C3R, (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXor_16u_C4R, (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXor_16u_AC4R, (const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXor_16u_C1IR, (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXor_16u_C3IR, (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXor_16u_C4IR, (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXor_16u_AC4IR, (const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_16u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp16u value, Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_16u_C3R, (const Ipp16u* pSrc, int srcStep, const Ipp16u value[3], Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_16u_C4R, (const Ipp16u* pSrc, int srcStep, const Ipp16u value[4], Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_16u_AC4R, (const Ipp16u* pSrc, int srcStep, const Ipp16u value[3], Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_16u_C1IR, (Ipp16u value, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_16u_C3IR, (const Ipp16u value[3], Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_16u_C4IR, (const Ipp16u value[4], Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_16u_AC4IR, (const Ipp16u value[3], Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXor_32s_C1R, (const Ipp32s* pSrc1, int src1Step, const Ipp32s* pSrc2, int src2Step, Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXor_32s_C3R, (const Ipp32s* pSrc1, int src1Step, const Ipp32s* pSrc2, int src2Step, Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXor_32s_C4R, (const Ipp32s* pSrc1, int src1Step, const Ipp32s* pSrc2, int src2Step, Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXor_32s_AC4R, (const Ipp32s* pSrc1, int src1Step, const Ipp32s* pSrc2, int src2Step, Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXor_32s_C1IR, (const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXor_32s_C3IR, (const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXor_32s_C4IR, (const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXor_32s_AC4IR, (const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_32s_C1R, (const Ipp32s* pSrc, int srcStep, Ipp32s value, Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_32s_C3R, (const Ipp32s* pSrc, int srcStep, const Ipp32s value[3], Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_32s_C4R, (const Ipp32s* pSrc, int srcStep, const Ipp32s value[4], Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_32s_AC4R, (const Ipp32s* pSrc, int srcStep, const Ipp32s value[3], Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_32s_C1IR, (Ipp32s value, Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_32s_C3IR, (const Ipp32s value[3], Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_32s_C4IR, (const Ipp32s value[4], Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiXorC_32s_AC4IR, (const Ipp32s value[3], Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))

IPPAPI(IppStatus, ippiNot_8u_C1R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiNot_8u_C3R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiNot_8u_C4R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiNot_8u_AC4R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiNot_8u_C1IR, (Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiNot_8u_C3IR, (Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiNot_8u_C4IR, (Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiNot_8u_AC4IR, (Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))

IPPAPI(IppStatus, ippiLShiftC_8u_C1R, (const Ipp8u* pSrc, int srcStep, Ipp32u value, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLShiftC_8u_C3R, (const Ipp8u* pSrc, int srcStep, const Ipp32u value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLShiftC_8u_C4R, (const Ipp8u* pSrc, int srcStep, const Ipp32u value[4], Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLShiftC_8u_AC4R, (const Ipp8u* pSrc, int srcStep, const Ipp32u value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLShiftC_8u_C1IR, (Ipp32u value, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLShiftC_8u_C3IR, (const Ipp32u value[3], Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLShiftC_8u_C4IR, (const Ipp32u value[4], Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLShiftC_8u_AC4IR, (const Ipp32u value[3], Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLShiftC_16u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp32u value, Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLShiftC_16u_C3R, (const Ipp16u* pSrc, int srcStep, const Ipp32u value[3], Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLShiftC_16u_C4R, (const Ipp16u* pSrc, int srcStep, const Ipp32u value[4], Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLShiftC_16u_AC4R, (const Ipp16u* pSrc, int srcStep, const Ipp32u value[3], Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLShiftC_16u_C1IR, (Ipp32u value, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLShiftC_16u_C3IR, (const Ipp32u value[3], Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLShiftC_16u_C4IR, (const Ipp32u value[4], Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLShiftC_16u_AC4IR, (const Ipp32u value[3], Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLShiftC_32s_C1R, (const Ipp32s* pSrc, int srcStep, Ipp32u value, Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLShiftC_32s_C3R, (const Ipp32s* pSrc, int srcStep, const Ipp32u value[3], Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLShiftC_32s_C4R, (const Ipp32s* pSrc, int srcStep, const Ipp32u value[4], Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLShiftC_32s_AC4R, (const Ipp32s* pSrc, int srcStep, const Ipp32u value[3], Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLShiftC_32s_C1IR, (Ipp32u value, Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLShiftC_32s_C3IR, (const Ipp32u value[3], Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLShiftC_32s_C4IR, (const Ipp32u value[4], Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiLShiftC_32s_AC4IR, (const Ipp32u value[3], Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))

IPPAPI(IppStatus, ippiRShiftC_8u_C1R, (const Ipp8u* pSrc, int srcStep, Ipp32u value, Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_8u_C3R, (const Ipp8u* pSrc, int srcStep, const Ipp32u value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_8u_C4R, (const Ipp8u* pSrc, int srcStep, const Ipp32u value[4], Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_8u_AC4R, (const Ipp8u* pSrc, int srcStep, const Ipp32u value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_8u_C1IR, (Ipp32u value, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_8u_C3IR, (const Ipp32u value[3], Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_8u_C4IR, (const Ipp32u value[4], Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_8u_AC4IR, (const Ipp32u value[3], Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_16u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp32u value, Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_16u_C3R, (const Ipp16u* pSrc, int srcStep, const Ipp32u value[3], Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_16u_C4R, (const Ipp16u* pSrc, int srcStep, const Ipp32u value[4], Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_16u_AC4R, (const Ipp16u* pSrc, int srcStep, const Ipp32u value[3], Ipp16u* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_16u_C1IR, (Ipp32u value, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_16u_C3IR, (const Ipp32u value[3], Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_16u_C4IR, (const Ipp32u value[4], Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_16u_AC4IR, (const Ipp32u value[3], Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_16s_C1R, (const Ipp16s* pSrc, int srcStep, Ipp32u value, Ipp16s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_16s_C3R, (const Ipp16s* pSrc, int srcStep, const Ipp32u value[3], Ipp16s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_16s_C4R, (const Ipp16s* pSrc, int srcStep, const Ipp32u value[4], Ipp16s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_16s_AC4R, (const Ipp16s* pSrc, int srcStep, const Ipp32u value[3], Ipp16s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_16s_C1IR, (Ipp32u value, Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_16s_C3IR, (const Ipp32u value[3], Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_16s_C4IR, (const Ipp32u value[4], Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_16s_AC4IR, (const Ipp32u value[3], Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_32s_C1R, (const Ipp32s* pSrc, int srcStep, Ipp32u value, Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_32s_C3R, (const Ipp32s* pSrc, int srcStep, const Ipp32u value[3], Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_32s_C4R, (const Ipp32s* pSrc, int srcStep, const Ipp32u value[4], Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_32s_AC4R, (const Ipp32s* pSrc, int srcStep, const Ipp32u value[3], Ipp32s* pDst, int dstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_32s_C1IR, (Ipp32u value, Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_32s_C3IR, (const Ipp32u value[3], Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_32s_C4IR, (const Ipp32u value[4], Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus, ippiRShiftC_32s_AC4IR, (const Ipp32u value[3], Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))


/* /////////////////////////////////////////////////////////////////////////////////////////////////
//                              Compare Operations
///////////////////////////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:           ippiCompare
//                  ippiCompareC
//  Purpose:  Compares pixel values of two images, or pixel values of an image to a constant
//            value using the following compare conditions: <, <=, ==, >, >= ;
//  Names:          ippiCompareEqualEps
//                  ippiCompareEqualEpsC
//  Purpose:  Compares 32f images for being equal, or equal to a given value within given tolerance
//  Context:
//
//  Returns:        IppStatus
//    ippStsNoErr        No errors
//    ippStsNullPtrErr   One of the pointers is NULL
//    ippStsStepErr      One of the step values is less than or equal to zero
//    ippStsSizeErr      roiSize has a field with zero or negative value
//    ippStsEpsValErr    eps is negative
//
//  Parameters:
//    pSrc1         Pointer to the first source image;
//    src1Step      Step through the first source image;
//    pSrc2         Pointer to the second source image data;
//    src2Step      Step through the second source image;
//    pDst          Pointer to destination image data;
//    dstStep       Step in destination image;
//    roiSize       Size of the ROI;
//    ippCmpOp      Compare operation to be used
//    value         Value (array of values for multi-channel image) to compare
//                  each pixel to
//    eps           The tolerance value
//
//  Notes:
*/

IPPAPI (IppStatus, ippiCompare_8u_C1R, ( const Ipp8u* pSrc1, int src1Step,
                                         const Ipp8u* pSrc2, int src2Step,
                                               Ipp8u* pDst,  int dstStep,
                                         IppiSize roiSize,   IppCmpOp ippCmpOp))
IPPAPI (IppStatus, ippiCompare_8u_C3R, ( const Ipp8u* pSrc1, int src1Step,
                                         const Ipp8u* pSrc2, int src2Step,
                                               Ipp8u* pDst,  int dstStep,
                                         IppiSize roiSize,   IppCmpOp ippCmpOp))
IPPAPI (IppStatus, ippiCompare_8u_AC4R, (const Ipp8u* pSrc1, int src1Step,
                                         const Ipp8u* pSrc2, int src2Step,
                                               Ipp8u* pDst,  int dstStep,
                                         IppiSize roiSize,   IppCmpOp ippCmpOp))
IPPAPI (IppStatus, ippiCompare_8u_C4R, ( const Ipp8u* pSrc1, int src1Step,
                                         const Ipp8u* pSrc2, int src2Step,
                                               Ipp8u* pDst,  int dstStep,
                                         IppiSize roiSize,   IppCmpOp ippCmpOp))

IPPAPI (IppStatus, ippiCompareC_8u_C1R,(const Ipp8u* pSrc, int srcStep, Ipp8u value,
                                              Ipp8u* pDst, int dstStep,
                                        IppiSize roiSize,  IppCmpOp ippCmpOp))
IPPAPI (IppStatus, ippiCompareC_8u_C3R,(const Ipp8u* pSrc, int srcStep, const Ipp8u value[3],
                                              Ipp8u* pDst, int dstStep,
                                        IppiSize roiSize,  IppCmpOp ippCmpOp))
IPPAPI (IppStatus, ippiCompareC_8u_AC4R,( const Ipp8u* pSrc, int srcStep, const Ipp8u value[3],
                                                Ipp8u* pDst, int dstStep,
                                          IppiSize roiSize,  IppCmpOp ippCmpOp))
IPPAPI (IppStatus, ippiCompareC_8u_C4R,(const Ipp8u* pSrc, int srcStep, const Ipp8u value[4],
                                              Ipp8u* pDst, int dstStep,
                                        IppiSize roiSize,  IppCmpOp ippCmpOp))

IPPAPI (IppStatus, ippiCompare_16s_C1R, ( const Ipp16s* pSrc1, int src1Step,
                                          const Ipp16s* pSrc2, int src2Step,
                                                Ipp8u*  pDst,  int dstStep,
                                          IppiSize roiSize,    IppCmpOp ippCmpOp))
IPPAPI (IppStatus, ippiCompare_16s_C3R, ( const Ipp16s* pSrc1, int src1Step,
                                          const Ipp16s* pSrc2, int src2Step,
                                                Ipp8u*  pDst,  int dstStep,
                                          IppiSize roiSize,    IppCmpOp ippCmpOp))
IPPAPI (IppStatus, ippiCompare_16s_AC4R, (const Ipp16s* pSrc1, int src1Step,
                                          const Ipp16s* pSrc2, int src2Step,
                                                Ipp8u*  pDst,  int dstStep,
                                          IppiSize roiSize,    IppCmpOp ippCmpOp))
IPPAPI (IppStatus, ippiCompare_16s_C4R, ( const Ipp16s* pSrc1, int src1Step,
                                          const Ipp16s* pSrc2, int src2Step,
                                                Ipp8u*  pDst,  int dstStep,
                                          IppiSize roiSize,    IppCmpOp ippCmpOp))

IPPAPI (IppStatus, ippiCompareC_16s_C1R, ( const Ipp16s* pSrc, int srcStep, Ipp16s value,
                                                Ipp8u*  pDst,  int dstStep,
                                           IppiSize roiSize,   IppCmpOp ippCmpOp))
IPPAPI (IppStatus, ippiCompareC_16s_C3R, ( const Ipp16s* pSrc, int srcStep, const Ipp16s value[3],
                                                 Ipp8u*  pDst, int dstStep,
                                           IppiSize roiSize,   IppCmpOp ippCmpOp))
IPPAPI (IppStatus, ippiCompareC_16s_AC4R, ( const Ipp16s* pSrc, int srcStep, const Ipp16s value[3],
                                                  Ipp8u*  pDst, int dstStep,
                                            IppiSize roiSize,   IppCmpOp ippCmpOp))
IPPAPI (IppStatus, ippiCompareC_16s_C4R, ( const Ipp16s* pSrc, int srcStep, const Ipp16s value[4],
                                                 Ipp8u*  pDst, int dstStep,
                                           IppiSize roiSize,   IppCmpOp ippCmpOp))

IPPAPI (IppStatus, ippiCompare_16u_C1R, ( const Ipp16u* pSrc1, int src1Step,
                                          const Ipp16u* pSrc2, int src2Step,
                                                Ipp8u*  pDst,  int dstStep,
                                          IppiSize roiSize,    IppCmpOp ippCmpOp))
IPPAPI (IppStatus, ippiCompare_16u_C3R, ( const Ipp16u* pSrc1, int src1Step,
                                          const Ipp16u* pSrc2, int src2Step,
                                                Ipp8u*  pDst,  int dstStep,
                                          IppiSize roiSize,    IppCmpOp ippCmpOp))
IPPAPI (IppStatus, ippiCompare_16u_AC4R, (const Ipp16u* pSrc1, int src1Step,
                                          const Ipp16u* pSrc2, int src2Step,
                                                Ipp8u*  pDst,  int dstStep,
                                          IppiSize roiSize,    IppCmpOp ippCmpOp))
IPPAPI (IppStatus, ippiCompare_16u_C4R, ( const Ipp16u* pSrc1, int src1Step,
                                          const Ipp16u* pSrc2, int src2Step,
                                                Ipp8u*  pDst,  int dstStep,
                                          IppiSize roiSize,    IppCmpOp ippCmpOp))

IPPAPI (IppStatus, ippiCompareC_16u_C1R, ( const Ipp16u* pSrc, int srcStep, Ipp16u value,
                                                Ipp8u*  pDst,  int dstStep,
                                           IppiSize roiSize,   IppCmpOp ippCmpOp))
IPPAPI (IppStatus, ippiCompareC_16u_C3R, ( const Ipp16u* pSrc, int srcStep, const Ipp16u value[3],
                                                 Ipp8u*  pDst, int dstStep,
                                           IppiSize roiSize,   IppCmpOp ippCmpOp))
IPPAPI (IppStatus, ippiCompareC_16u_AC4R, ( const Ipp16u* pSrc, int srcStep, const Ipp16u value[3],
                                                  Ipp8u*  pDst, int dstStep,
                                            IppiSize roiSize,   IppCmpOp ippCmpOp))
IPPAPI (IppStatus, ippiCompareC_16u_C4R, ( const Ipp16u* pSrc, int srcStep, const Ipp16u value[4],
                                                 Ipp8u*  pDst, int dstStep,
                                           IppiSize roiSize,   IppCmpOp ippCmpOp))

IPPAPI (IppStatus, ippiCompare_32f_C1R, ( const Ipp32f* pSrc1, int src1Step,
                                          const Ipp32f* pSrc2, int src2Step,
                                                 Ipp8u*  pDst, int dstStep,
                                          IppiSize roiSize,    IppCmpOp ippCmpOp))
IPPAPI (IppStatus, ippiCompare_32f_C3R, ( const Ipp32f* pSrc1, int src1Step,
                                          const Ipp32f* pSrc2, int src2Step,
                                                 Ipp8u*  pDst, int dstStep,
                                          IppiSize roiSize,    IppCmpOp ippCmpOp))
IPPAPI (IppStatus, ippiCompare_32f_AC4R,( const Ipp32f* pSrc1, int src1Step,
                                          const Ipp32f* pSrc2, int src2Step,
                                                 Ipp8u*  pDst, int dstStep,
                                          IppiSize roiSize,    IppCmpOp ippCmpOp))
IPPAPI (IppStatus, ippiCompare_32f_C4R, ( const Ipp32f* pSrc1, int src1Step,
                                          const Ipp32f* pSrc2, int src2Step,

                                                 Ipp8u*  pDst, int dstStep,
                                          IppiSize roiSize,    IppCmpOp ippCmpOp))

IPPAPI (IppStatus, ippiCompareC_32f_C1R, ( const Ipp32f* pSrc, int srcStep, Ipp32f value,
                                                 Ipp8u*  pDst, int dstStep,
                                           IppiSize roiSize,   IppCmpOp ippCmpOp))
IPPAPI (IppStatus, ippiCompareC_32f_C3R, ( const Ipp32f* pSrc, int srcStep, const Ipp32f value[3],
                                                 Ipp8u*  pDst, int dstStep,
                                           IppiSize roiSize,   IppCmpOp ippCmpOp))
IPPAPI (IppStatus, ippiCompareC_32f_AC4R, ( const Ipp32f* pSrc, int srcStep, const Ipp32f value[3],
                                                  Ipp8u*  pDst, int dstStep,
                                            IppiSize roiSize,   IppCmpOp ippCmpOp))
IPPAPI (IppStatus, ippiCompareC_32f_C4R, ( const Ipp32f* pSrc, int srcStep, const Ipp32f value[4],
                                                 Ipp8u*  pDst, int dstStep,
                                           IppiSize roiSize,   IppCmpOp ippCmpOp))

IPPAPI(IppStatus,ippiCompareEqualEps_32f_C1R,(const Ipp32f* pSrc1, int src1Step,
                                              const Ipp32f* pSrc2, int src2Step,
                                                    Ipp8u*  pDst,  int dstStep,
                                              IppiSize roiSize,    Ipp32f eps))
IPPAPI(IppStatus,ippiCompareEqualEps_32f_C3R,(const Ipp32f* pSrc1, int src1Step,
                                              const Ipp32f* pSrc2, int src2Step,
                                                    Ipp8u*  pDst,  int dstStep,
                                              IppiSize roiSize,    Ipp32f eps))
IPPAPI(IppStatus,ippiCompareEqualEps_32f_AC4R,(const Ipp32f* pSrc1,int src1Step,
                                               const Ipp32f* pSrc2,int src2Step,
                                                     Ipp8u*  pDst,  int dstStep,
                                               IppiSize roiSize,   Ipp32f eps))
IPPAPI(IppStatus,ippiCompareEqualEps_32f_C4R,(const Ipp32f* pSrc1, int src1Step,
                                              const Ipp32f* pSrc2, int src2Step,
                                                    Ipp8u*  pDst,  int dstStep,
                                              IppiSize roiSize,    Ipp32f eps))

IPPAPI(IppStatus,ippiCompareEqualEpsC_32f_C1R,(const Ipp32f* pSrc, int srcStep, Ipp32f value,
                                                    Ipp8u*   pDst,  int dstStep,
                                               IppiSize roiSize,   Ipp32f eps))
IPPAPI(IppStatus,ippiCompareEqualEpsC_32f_C3R,(const Ipp32f* pSrc, int srcStep,const Ipp32f value[3],
                                                     Ipp8u*  pDst, int dstStep,
                                               IppiSize roiSize,   Ipp32f eps))
IPPAPI(IppStatus,ippiCompareEqualEpsC_32f_AC4R,(const Ipp32f* pSrc, int srcStep,const Ipp32f value[3],
                                                      Ipp8u*  pDst, int dstStep,
                                                IppiSize roiSize,   Ipp32f eps))
IPPAPI(IppStatus,ippiCompareEqualEpsC_32f_C4R,(const Ipp32f* pSrc, int srcStep,const Ipp32f value[4],
                                                     Ipp8u*  pDst, int dstStep,
                                               IppiSize roiSize,   Ipp32f eps))

/* /////////////////////////////////////////////////////////////////////////////////////////////////
//                 Morphological Operations
///////////////////////////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:      ippiErode3x3_64f_C1R
//             ippiDilate3x3_64f_C1R
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
IPPAPI (IppStatus, ippiErode3x3_64f_C1R,  (const Ipp64f* pSrc, int srcStep, Ipp64f* pDst, int dstStep, IppiSize roiSize))
IPPAPI (IppStatus, ippiDilate3x3_64f_C1R, (const Ipp64f* pSrc, int srcStep, Ipp64f* pDst, int dstStep, IppiSize roiSize))



/* ///////////////////////////////////////////////////////////////////////////
//  Name:
//    ippiZigzagInv8x8_16s_C1
//    ippiZigzagFwd8x8_16s_C1
//
//  Purpose:
//    Converts a natural order  to zigzag in an 8x8 block (forward function),
//    converts a zigzag order to natural  in a 8x8 block (inverse function)
//
//  Parameter:
//    pSrc   Pointer to the source block
//    pDst   Pointer to the destination block
//
//  Returns:
//    ippStsNoErr      No errors
//    ippStsNullPtrErr One of the pointers is NULL
//
*/

IPPAPI(IppStatus, ippiZigzagInv8x8_16s_C1,(const Ipp16s* pSrc, Ipp16s* pDst))
IPPAPI(IppStatus, ippiZigzagFwd8x8_16s_C1, (const Ipp16s* pSrc, Ipp16s* pDst))


/* /////////////////////////////////////////////////////////////////////////////
//                         Windowing functions
//
//  Note: to obtain the window coefficients you have apply the corresponding
//        function to the image with all pixel values set to 1 (this image can
//        be created, for example, calling function ippiSet(1,x,n))
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
// Names:         ippiWinBartlett, ippiWinBartlettSep
// Purpose:       Applies Bartlett windowing function to an image.
// Parameters:
//    pSrc        - Pointer to the source image.
//    srcStep     - Distances, in bytes, between the starting points of consecutive lines in the source images.
//    pDst        - Pointer to the destination image.
//    dstStep     - Distance, in bytes, between the starting points of consecutive lines in the destination image.
//    pSrcDst     - Pointer to the source/destination image (in-place flavors).
//    srcDstStep  - Distance, in bytes, between the starting points of consecutive lines in the source/destination image (in-place flavors).
//    roiSize     - Size, in pixels, of the ROI.
//    pBuffer     - Pointer to the buffer for internal calculations. Size of the buffer is calculated by ippiWinBartlett{Sep}GetBufferSize.
//  Returns:
//    ippStsNoErr      - OK.
//    ippStsNullPtrErr - Error when any of the specified pointers is NULL.
//    ippStsSizeErr    - Error when roiSize has a field with value less than 3.
//    ippStsStepErr    - Error when srcStep, dstStep, or srcDstStep has a zero or negative value.
*/
IPPAPI(IppStatus, ippiWinBartlett_8u_C1R, (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWinBartlett_16u_C1R,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWinBartlett_32f_C1R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiWinBartlett_8u_C1IR, (Ipp8u*  pSrcDst, int srcDstStep, IppiSize roiSize, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWinBartlett_16u_C1IR,(Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWinBartlett_32f_C1IR,(Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiWinBartlettSep_8u_C1R, (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWinBartlettSep_16u_C1R,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWinBartlettSep_32f_C1R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiWinBartlettSep_8u_C1IR, (Ipp8u*  pSrcDst, int srcDstStep, IppiSize roiSize, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWinBartlettSep_16u_C1IR,(Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWinBartlettSep_32f_C1IR,(Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize, Ipp8u* pBuffer))


/* /////////////////////////////////////////////////////////////////////////////
// Names:      ippiWinBartlettGetSize, ippiWinBartlettSepGetSize
//
// Purpose:    Get the size (in bytes) of the buffer for ippiWinBartlett{Sep} internal calculations.
//
// Parameters:
//    dataType    - Data type for windowing function. Possible values are ipp32f, ipp16u, or ipp8u.
//    roiSize     - Size, in pixels, of the ROI.
//    pSize       - Pointer to the calculated buffer size (in bytes).
//
// Return:
//    ippStsNoErr       - OK.
//    ippStsNullPtrErr  - Error when pSize pointer is NULL.
//    ippStsSizeErr     - Error when roiSize has a field with value less than 3.
//    ippStsDataTypeErr - Error when the dataType value differs from the ipp32f, ipp16u, or ipp8u.
*/
IPPAPI(IppStatus, ippiWinBartlettGetBufferSize, (IppDataType dataType, IppiSize roiSize, int *pSize))
IPPAPI(IppStatus, ippiWinBartlettSepGetBufferSize, (IppDataType dataType, IppiSize roiSize, int *pSize))



/* /////////////////////////////////////////////////////////////////////////////
// Names:         ippiWinHamming, ippiWinHammingSep
// Purpose:       Applies Hamming window function to the image.
// Parameters:
//    pSrc        - Pointer to the source image.
//    srcStep     - Distances, in bytes, between the starting points of consecutive lines in the source images.
//    pDst        - Pointer to the destination image.
//    dstStep     - Distance, in bytes, between the starting points of consecutive lines in the destination image.
//    pSrcDst     - Pointer to the source/destination image (in-place flavors).
//    srcDstStep  - Distance, in bytes, between the starting points of consecutive lines in the source/destination image (in-place flavors).
//    roiSize     - Size, in pixels, of the ROI.
//    pBuffer     - Pointer to the buffer for internal calculations. Size of the buffer is calculated by ippiWinHamming{Sep}GetBufferSize.
//  Returns:
//    ippStsNoErr      - OK.
//    ippStsNullPtrErr - Error when any of the specified pointers is NULL.
//    ippStsSizeErr    - Error when roiSize has a field with value less than 3.
//    ippStsStepErr    - Error when srcStep, dstStep, or srcDstStep has a zero or negative value.
*/
IPPAPI(IppStatus, ippiWinHamming_8u_C1R, (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWinHamming_16u_C1R,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWinHamming_32f_C1R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiWinHamming_8u_C1IR, (Ipp8u*  pSrcDst, int srcDstStep, IppiSize roiSize, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWinHamming_16u_C1IR,(Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWinHamming_32f_C1IR,(Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiWinHammingSep_8u_C1R, (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWinHammingSep_16u_C1R,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWinHammingSep_32f_C1R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiWinHammingSep_8u_C1IR, (Ipp8u*  pSrcDst, int srcDstStep, IppiSize roiSize, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWinHammingSep_16u_C1IR,(Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiWinHammingSep_32f_C1IR,(Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize, Ipp8u* pBuffer))


/* /////////////////////////////////////////////////////////////////////////////
// Names:      ippiWinHammingGetBufferSize, ippiWinHammingSepGetBufferSize
//
// Purpose:    Get the size (in bytes) of the buffer for ippiWinHamming{Sep} internal calculations.
//
// Parameters:
//    dataType    - Data type for windowing function. Possible values are ipp32f, ipp16u, or ipp8u.
//    roiSize     - Size, in pixels, of the ROI.
//    pSize       - Pointer to the calculated buffer size (in bytes).
//
// Return:
//    ippStsNoErr       - OK.
//    ippStsNullPtrErr  - Error when pSize pointer is NULL.
//    ippStsSizeErr     - Error when roiSize has a field with value less than 3.
//    ippStsDataTypeErr - Error when the dataType value differs from the ipp32f, ipp16u, or ipp8u.
*/
IPPAPI(IppStatus, ippiWinHammingGetBufferSize, (IppDataType dataType, IppiSize roiSize, int *pSize))
IPPAPI(IppStatus, ippiWinHammingSepGetBufferSize, (IppDataType dataType, IppiSize roiSize, int *pSize))



/* /////////////////////////////////////////////////////////////////////////////
//  Name:        ippiTranspose
//
//  Purpose:     Transposing an image
//
//  Parameters:
//    pSrc       Pointer to the source image
//    srcStep    Step through the source image
//    pDst       Pointer to the destination image
//    dstStep    Step through the destination image
//    pSrcDst    Pointer to the source/destination image (in-place flavors)
//    srcDstStep Step through the source/destination image (in-place flavors)
//    roiSize    Size of the ROI
//
//  Returns:
//    ippStsNoErr      - Ok.
//    ippStsNullPtrErr - Error when any of the specified pointers is NULL.
//    ippStsSizeErr    - Error when:
//                         roiSize has a field with zero or negative value;
//                         roiSize.width != roiSize.height (in-place flavors).
//
//  Notes: Parameters roiSize.width and roiSize.height are defined for the source image.
*/
IPPAPI(IppStatus, ippiTranspose_8u_C1R, ( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiTranspose_8u_C3R, ( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiTranspose_8u_C4R, ( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiTranspose_8u_C1IR, ( Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiTranspose_8u_C3IR, ( Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiTranspose_8u_C4IR, ( Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize ))

IPPAPI(IppStatus, ippiTranspose_16u_C1R, ( const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiTranspose_16u_C3R, ( const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiTranspose_16u_C4R, ( const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiTranspose_16u_C1IR, ( Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiTranspose_16u_C3IR, ( Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiTranspose_16u_C4IR, ( Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize ))

IPPAPI(IppStatus, ippiTranspose_16s_C1R, ( const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiTranspose_16s_C3R, ( const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiTranspose_16s_C4R, ( const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiTranspose_16s_C1IR, ( Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiTranspose_16s_C3IR, ( Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiTranspose_16s_C4IR, ( Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize ))

IPPAPI(IppStatus, ippiTranspose_32s_C1R, ( const Ipp32s* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiTranspose_32s_C3R, ( const Ipp32s* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiTranspose_32s_C4R, ( const Ipp32s* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiTranspose_32s_C1IR, ( Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiTranspose_32s_C3IR, ( Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiTranspose_32s_C4IR, ( Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize ))

IPPAPI(IppStatus, ippiTranspose_32f_C1R, ( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiTranspose_32f_C3R, ( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiTranspose_32f_C4R, ( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiTranspose_32f_C1IR, ( Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiTranspose_32f_C3IR, ( Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiTranspose_32f_C4IR, ( Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize ))


/* //////////////////////////////////////////////////////////////////////
// Name:        ippiDeconvFFTGetSize_32f
//
// Purpose:     Get sizes, in bytes, of the IppiDeconvFFTState_32f_C{1|3}R structure.
//
// Parameters:
//    numChannels - Number of image channels. Possible values are 1 and 3.
//    kernelSize  - Size of kernel.
//    FFTorder    - Order of created FFT structure.
//    pSize       - Pointer to the size of IppiDeconvFFTState_32f_C{1|3}R structure (in bytes).
//
// Returns:
//    ippStsNoErr           - Ok.
//    ippStsNullPtrErr      - Error when any of the specified pointers is NULL.
//    ippStsNumChannelsErr  - Error when the numChannels value differs from 1 or 3.
//    ippStsSizeErr         - Error when:
//                               kernelSize less or equal to zero;
//                               kernelSize great than 2^FFTorder.
*/
IPPAPI(IppStatus, ippiDeconvFFTGetSize_32f, (int nChannels, int kernelSize, int FFTorder, int *pSize))

/* //////////////////////////////////////////////////////////////////////
// Name:        ippiDeconvFFTInit_32f_C1R, ippiDeconvFFTInit_32f_C3R
//
// Purpose:     Initialize IppiDeconvFFTState structure.
//
// Parameters:
//    pDeconvFFTState - Pointer to the created deconvolution structure.
//    pKernel         - Pointer to the kernel array.
//    kernelSize      - Size of kernel.
//    FFTorder        - Order of created FFT structure.
//    threshold       - Threshold level value (for except dividing to zero).
//
// Returns:
//    ippStsNoErr      - Ok.
//    ippStsNullPtrErr - Error when any of the specified pointers is NULL.
//    ippStsSizeErr    - Error when:
//                          kernelSize less or equal to zero;
//                          kernelSize great than 2^FFTorder.
//    ippStsBadArgErr  - Error when threshold less or equal to zero.
*/
IPPAPI(IppStatus, ippiDeconvFFTInit_32f_C1R, (IppiDeconvFFTState_32f_C1R* pDeconvFFTState, const Ipp32f* pKernel, int kernelSize, int FFTorder, Ipp32f threshold))
IPPAPI(IppStatus, ippiDeconvFFTInit_32f_C3R, (IppiDeconvFFTState_32f_C3R* pDeconvFFTState, const Ipp32f* pKernel, int kernelSize, int FFTorder, Ipp32f threshold))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:        ippiDeconvFFT_32f_C*R
//
//  Purpose:    Perform deconvolution for source image using FFT
//
//  Parameters:
//    pSrc            - Pointer to the source image.
//    srcStep         - Step in bytes in the source image.
//    pDst            - Pointer to the destination image.
//    dstStep         - Step in bytes in the destination image.
//    roi             - Size of the image ROI in pixels.
//    pDeconvFFTState - Pointer to the Deconvolution context structure.
//
//  Returns:
//    ippStsNoErr          - Ok.
//    ippStsNullPtrErr     - Error when any of the specified pointers is NULL.
//    ippStsSizeErr        - Error when:
//                               roi.width or roi.height less or equal to zero;
//                               roi.width or roi.height great than (2^FFTorder-kernelSize).
//    ippStsStepErr        - Error when srcstep or dststep less than roi.width multiplied by type size.
//    ippStsNotEvenStepErr - Error when one of step values for floating-point images cannot be divided by 4.
*/
IPPAPI(IppStatus, ippiDeconvFFT_32f_C1R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roi, IppiDeconvFFTState_32f_C1R* pDeconvFFTState))
IPPAPI(IppStatus, ippiDeconvFFT_32f_C3R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roi, IppiDeconvFFTState_32f_C3R* pDeconvFFTState))

/* //////////////////////////////////////////////////////////////////////
// Name:        ippiDeconvLRGetSize_32f
//
// Purpose:     Get sizes, in bytes, of the IppiDeconvLR_32f_C{1|3}R structure.
//
// Parameters:
//    numChannels - Number of image channels. Possible values are 1 and 3.
//    kernelSize  - Size of kernel.
//    maxroi      - Maximum size of the image ROI in pixels.
//    pSize       - Pointer to the size of IppiDeconvLR_32f_C{1|3}R structure (in bytes).
//
// Returns:
//    ippStsNoErr           - Ok.
//    ippStsNullPtrErr      - Error when any of the specified pointers is NULL.
//    ippStsNumChannelsErr  - Error when the numChannels value differs from 1 or 3.
//    ippStsSizeErr         - Error when:
//                               kernelSize less or equal to zero;
//                               kernelSize great than maxroi.width or maxroi.height;
//                               maxroi.height or maxroi.width less or equal to zero.
*/
IPPAPI(IppStatus, ippiDeconvLRGetSize_32f, (int numChannels, int kernelSize, IppiSize maxroi, int *pSize))

/* //////////////////////////////////////////////////////////////////////
// Name:        ippiDeconvLRInit_32f_C1R, ippiDeconvLRInit_32f_C3R
//
// Purpose:     Initialize IppiDeconvLR_32f_C{1|3}R structure.
//
// Parameters:
//    pDeconvLR   - Pointer to the created Lucy-Richardson Deconvolution context structure.
//    pKernel     - Pointer to the kernel array.
//    kernelSize  - Size of kernel.
//    maxroi      - Maximum size of the image ROI in pixels.
//    threshold   - Threshold level value (for except dividing to zero).
//
// Returns:
//    ippStsNoErr      - Ok.
//    ippStsNullPtrErr - Error when any of the specified pointers is NULL.
//    ippStsSizeErr    - Error when:
//                         kernelSize less or equal to zero;
//                         kernelSize great than maxroi.width or maxroi.height,
//                         maxroi.height or maxroi.width less or equal to zero.
//    ippStsBadArgErr  - Error when threshold less or equal to zero.
*/
IPPAPI(IppStatus, ippiDeconvLRInit_32f_C1R, (IppiDeconvLR_32f_C1R* pDeconvLR, const Ipp32f* pKernel, int kernelSize, IppiSize maxroi, Ipp32f threshold))
IPPAPI(IppStatus, ippiDeconvLRInit_32f_C3R, (IppiDeconvLR_32f_C3R* pDeconvLR, const Ipp32f* pKernel, int kernelSize, IppiSize maxroi, Ipp32f threshold))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:        ippiDeconvLR_32f_C1R, ippiDeconvLR_32f_C3R
//
//  Purpose:    Perform deconvolution for source image using Lucy-Richardson algorithm
//
//  Parameters:
//    pSrc      - Pointer to the source image.
//    srcStep   - Step in bytes in the source image.
//    pDst      - Pointer to the destination image.
//    dstStep   - Step in bytes in the destination image.
//    roi       - Size of the image ROI in pixels.
//    numiter   - Number of algorithm iteration.
//    pDeconvLR - Pointer to the Lucy-Richardson Deconvolution context structure.
//
//  Returns:
//    ippStsNoErr          - Ok.
//    ippStsNullPtrErr     - Error when any of the specified pointers is NULL.
//    ippStsSizeErr        - Error when:
//                               roi.width or roi.height less or equal to zero;
//                               roi.width  great than (maxroi.width-kernelSize);
//                               roi.height great than (maxroi.height-kernelSize).
//    ippStsStepErr        - Error when srcstep or dststep less than roi.width multiplied by type size.
//    ippStsNotEvenStepErr - Error when one of step values for floating-point images cannot be divided by 4.
//    ippStsBadArgErr      - Error when number of iterations less or equal to zero.
*/
IPPAPI ( IppStatus, ippiDeconvLR_32f_C1R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roi, int numiter, IppiDeconvLR_32f_C1R* pDeconvLR))
IPPAPI ( IppStatus, ippiDeconvLR_32f_C3R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roi, int numiter, IppiDeconvLR_32f_C3R* pDeconvLR))

/* /////////////////////////////////////////////////////////////////////////////
//
//  Names:        ippiCompColorKey_8u_C1R
//                ippiCompColorKey_8u_C3R
//                ippiCompColorKey_8u_C4R
//                ippiCompColorKey_16s_C1R
//                ippiCompColorKey_16s_C3R
//                ippiCompColorKey_16s_C4R
//                ippiCompColorKey_16u_C1R
//                ippiCompColorKey_16u_C3R
//                ippiCompColorKey_16u_C4R
//
//  Purpose:    Perform alpha blending with transparent background.
//
//  Returns:     IppStatus
//     ippStsNoErr            No errors
//     ippStsNullPtrErr       One of the pointers is NULL
//     ippStsSizeErr          The roiSize has a field with negative or zero value
//     ippStsStepErr          One of steps is less than or equal to zero
//     ippStsAlphaTypeErr     Unsupported type of composition (for ippiAlphaCompColorKey)
//
//  Parameters:
//    pSrc1, pSrc2           Pointers to the source images
//    src1Step, src2Step     Steps through the source images
//    pDst                   Pointer to the destination image
//    dstStep                Step through the destination image
//    roiSize                Size of the image ROI
//    colorKey               Color value (array of values for multi-channel data)
//    alphaType              The type of composition to perform (for ippiAlphaCompColorKey)
//
*/
IPPAPI (IppStatus, ippiCompColorKey_8u_C1R, (const Ipp8u* pSrc1, int src1Step,
                                             const Ipp8u* pSrc2, int src2Step,
                                                   Ipp8u* pDst,  int dstStep,
                                             IppiSize roiSize, Ipp8u colorKey))

IPPAPI (IppStatus, ippiCompColorKey_8u_C3R, (const Ipp8u* pSrc1, int src1Step,
                                             const Ipp8u* pSrc2, int src2Step,
                                                   Ipp8u* pDst,  int dstStep,
                                             IppiSize roiSize, Ipp8u colorKey[3]))

IPPAPI (IppStatus, ippiCompColorKey_8u_C4R, (const Ipp8u* pSrc1, int src1Step,
                                             const Ipp8u* pSrc2, int src2Step,
                                                   Ipp8u* pDst,  int dstStep,
                                             IppiSize roiSize, Ipp8u colorKey[4]))

IPPAPI (IppStatus, ippiCompColorKey_16u_C1R, (const Ipp16u* pSrc1, int src1Step,
                                              const Ipp16u* pSrc2, int src2Step,
                                                    Ipp16u* pDst,  int dstStep,
                                              IppiSize roiSize, Ipp16u colorKey))

IPPAPI (IppStatus, ippiCompColorKey_16u_C3R, (const Ipp16u* pSrc1, int src1Step,
                                              const Ipp16u* pSrc2, int src2Step,
                                                     Ipp16u* pDst,  int dstStep,
                                              IppiSize roiSize,   Ipp16u colorKey[3]))

IPPAPI (IppStatus, ippiCompColorKey_16u_C4R, (const Ipp16u* pSrc1, int src1Step,
                                              const Ipp16u* pSrc2, int src2Step,
                                                  Ipp16u* pDst,  int dstStep,
                                              IppiSize roiSize, Ipp16u colorKey[4]))

IPPAPI (IppStatus, ippiCompColorKey_16s_C1R, (const Ipp16s* pSrc1, int src1Step,
                                              const Ipp16s* pSrc2, int src2Step,
                                                    Ipp16s* pDst,  int dstStep,
                                              IppiSize roiSize, Ipp16s colorKey))

IPPAPI (IppStatus, ippiCompColorKey_16s_C3R, (const Ipp16s* pSrc1, int src1Step,
                                              const Ipp16s* pSrc2, int src2Step,
                                                    Ipp16s* pDst,  int dstStep,
                                              IppiSize roiSize, Ipp16s colorKey[3]))

IPPAPI (IppStatus, ippiCompColorKey_16s_C4R, (const Ipp16s* pSrc1, int src1Step,
                                              const Ipp16s* pSrc2, int src2Step,
                                                    Ipp16s* pDst,  int dstStep,
                                              IppiSize roiSize, Ipp16s colorkey[4]))
IPPAPI (IppStatus, ippiAlphaCompColorKey_8u_AC4R, ( const Ipp8u* pSrc1, int src1Step,Ipp8u alpha1,
                                              const Ipp8u* pSrc2, int src2Step, Ipp8u alpha2,
                                              Ipp8u* pDst,  int dstStep,
                                              IppiSize roiSize,   Ipp8u colorKey[4],IppiAlphaType alphaType ))


/* ///////////////////////////////////////////////////////////////////////////
//                     Median filter function
// ///////////////////////////////////////////////////////////////////////////
// Name:
//   ippiMedian_8u_P3C1R
//
// Purpose:
//   Median of three images.
//
//   For each pixel (x, y) in the ROI:
//   pDst[x + y*dstStep] = MEDIAN(pSrc[0][x + y*srcStep],
//                                pSrc[1][x + y*srcStep],
//                                pSrc[2][x + y*srcStep]);
//
// Parameters:
//   pSrc       Pointer to three source images.
//   srcStep    Step in bytes through source images.
//   pDst       Pointer to the destination image.
//   dstStep    Step in bytes through the destination image buffer.
//   size       Size of the ROI in pixels.
//
// Returns:
//   ippStsNoErr        Indicates no error. Any other value indicates an error or a warning.
//   ippStsNullPtrErr   Indicates an error if one of the specified pointers is NULL.
//   ippStsSizeErr      Indicates an error condition if size has a field with zero or negative value.
//
*/
IPPAPI(IppStatus, ippiMedian_8u_P3C1R, (const Ipp8u *pSrc[3],
                                        int srcStep,
                                        Ipp8u *pDst,
                                        int dstStep,
                                        IppiSize size))


/* /////////////////////////////////////////////////////////////////////////////
//                     De-interlacing filter function
// /////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////
//
//  Name:               ippiDeinterlaceFilterCAVT_8u_C1R
//  Purpose:            Performs de-interlacing of two-field image
//                      using content adaptive vertical temporal (CAVT) filtering
//  Parameters:
//    pSrc              pointer to the source image (frame)
//    srcStep           step of the source pointer in bytes
//    pDst              pointer to the destination image (frame)
//    dstStep           step of the destination pointer in bytes
//    threshold         threshold level value
//    roiSize           size of the source and destination ROI
//  Returns:
//    ippStsNoErr       no errors
//    ippStsNullPtrErr  pSrc == NULL or pDst == NULL
//    ippStsSizeErr     width of roi is less or equal zero or
//                      height of roi is less 8 or odd
*/

IPPAPI(IppStatus, ippiDeinterlaceFilterCAVT_8u_C1R,
    (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, Ipp16u threshold, IppiSize roiSize))




/* /////////////////////////////////////////////////////////////////////////////
//                     Bilateral filter function
*/

/* /////////////////////////////////////////////////////////////////////////////
//                     Bilateral filter functions with Border
// /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFilterBilateralBorderGetBufferSize
//  Purpose:    to define buffer size for bilateral filter
//  Parameters:
//   filter        Type of bilateral filter. Possible value is ippiFilterBilateralGauss.
//   dstRoiSize    Roi size (in pixels) of destination image what will be applied
//                 for processing.
//   radius        Radius of circular neighborhood what defines pixels for calculation.
//   dataType      Data type of the source and desination images. Possible values
//                 are ipp8u and ipp32f.
//   numChannels   Number of channels in the images. Possible values are 1 and 3.
//   distMethod    The type of method for definition of distance beetween pixel untensity.
//                 Possible value is ippDistNormL1.
//   pSpecSize     Pointer to the size (in bytes) of the spec.
//   pBufferSize   Pointer to the size (in bytes) of the external work buffer.
//  Return:
//    ippStsNoErr               OK
//    ippStsNullPtrErr          any pointer is NULL
//    ippStsSizeErr             size of dstRoiSize is less or equal 0
//    ippStsMaskSizeErr         radius is less or equal 0
//    ippStsNotSupportedModeErr filter or distMethod is not supported
//    ippStsDataTypeErr         Indicates an error when dataType has an illegal value.
//    ippStsNumChannelsErr      Indicates an error when numChannels has an illegal value.
*/
IPPAPI(IppStatus,ippiFilterBilateralBorderGetBufferSize,
       (IppiFilterBilateralType filter, IppiSize dstRoiSize,
       int radius, IppDataType dataType, int numChannels,
       IppiDistanceMethodType distMethodType, int *pSpecSize, int *pBufferSize))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFilterBilateralBorderInit
//  Purpose:    initialization of Spec for bilateral filter with border
//  Parameters:
//   filter           Type of bilateral filter. Possible value is ippiFilterBilateralGauss.
//   dstRoiSize       Roi size (in pixels) of destination image what will be applied
//                    for processing.
//   radius           Radius of circular neighborhood what defines pixels for calculation.
//   dataType      Data type of the source and desination images. Possible values
//                 are ipp8u and ipp32f.
//   numChannels   Number of channels in the images. Possible values are 1 and 3.
//   distMethodType   The type of method for definition of distance beetween pixel intensity.
//                    Possible value is ippDistNormL1.
//   valSquareSigma   square of Sigma for factor function for pixel intensity
//   posSquareSigma   square of Sigma for factor function for pixel position
//    pSpec           pointer to Spec
//  Return:
//    ippStsNoErr               OK
//    ippStsNullPtrErr          pointer ro Spec is NULL
//    ippStsSizeErr             size of dstRoiSize is less or equal 0
//    ippStsMaskSizeErr         radius is less or equal 0
//    ippStsNotSupportedModeErr filter or distMethod is not supported
//    ippStsDataTypeErr         Indicates an error when dataType has an illegal value.
//    ippStsNumChannelsErr      Indicates an error when numChannels has an illegal value.
//    ippStsBadArgErr           valSquareSigma or posSquareSigma is less or equal 0
*/
IPPAPI(IppStatus,ippiFilterBilateralBorderInit,
       (IppiFilterBilateralType filter, IppiSize dstRoiSize,
       int radius, IppDataType dataType, int numChannels,
       IppiDistanceMethodType distMethod, Ipp32f valSquareSigma,
       Ipp32f posSquareSigma, IppiFilterBilateralSpec *pSpec))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFilterBilateralBorder_8u_C1R
//              ippiFilterBilateralBorder_8u_C3R
//              ippiFilterBilateralBorder_32f_C1R
//              ippiFilterBilateralBorder_32f_C3R
//  Purpose:    bilateral filter
//  Parameters:
//    pSrc         Pointer to the source image
//    srcStep      Step through the source image
//    pDst         Pointer to the destination image
//    dstStep      Step through the destination image
//    dstRoiSize   Size of the destination ROI
//    borderType   Type of border.
//    borderValue  Pointer to constant value to assign to pixels of the constant border. This parameter is applicable
//                 only to the ippBorderConst border type. If this pointer is NULL than the constant value is equal 0.
//    pSpec        Pointer to filter spec
//    pBuffer      Pointer ro work buffer
//  Return:
//    ippStsNoErr           OK
//    ippStsNullPtrErr      pointer to Src, Dst, Spec or Buffer is NULL
//    ippStsSizeErr         size of dstRoiSize is less or equal 0
//    ippStsContextMatchErr filter Spec is not match
//    ippStsNotEvenStepErr  Indicated an error when one of the step values is not divisible by 4
//                          for floating-point images.
//    ippStsBorderErr       Indicates an error when borderType has illegal value.
*/
IPPAPI(IppStatus,ippiFilterBilateralBorder_8u_C1R,(const Ipp8u *pSrc, int srcStep,
       Ipp8u *pDst, int dstStep, IppiSize dstRoiSize,
       IppiBorderType borderType, Ipp8u *pBorderValue, IppiFilterBilateralSpec *pSpec,
       Ipp8u* pBuffer))
IPPAPI(IppStatus,ippiFilterBilateralBorder_8u_C3R,(const Ipp8u *pSrc, int srcStep,
       Ipp8u *pDst, int dstStep, IppiSize dstRoiSize,
       IppiBorderType borderType, Ipp8u *pBorderValue, IppiFilterBilateralSpec *pSpec,
       Ipp8u* pBuffer))
IPPAPI(IppStatus,ippiFilterBilateralBorder_32f_C1R,(const Ipp32f *pSrc, int srcStep,
       Ipp32f *pDst, int dstStep, IppiSize dstRoiSize,
       IppiBorderType borderType, Ipp32f *pBorderValue, IppiFilterBilateralSpec *pSpec,
       Ipp8u* pBuffer))
IPPAPI(IppStatus,ippiFilterBilateralBorder_32f_C3R,(const Ipp32f *pSrc, int srcStep,
       Ipp32f *pDst, int dstStep, IppiSize dstRoiSize,
       IppiBorderType borderType, Ipp32f *pBorderValue, IppiFilterBilateralSpec *pSpec,
       Ipp8u* pBuffer))



/* ////////////////////////////////////////////////////////////////////////////
//  Name:      ippiFilterGetBufSize_64f_C1R
//  Purpose:   Get size of temporal buffer
//  Parameters:
//      kernelSize      Size of the rectangular kernel in pixels.
//      roiWidth        Width of ROI
//      pSize           Pointer to the size of work buffer
//  Returns:
//   ippStsNoErr        Ok
//   ippStsNullPtrErr   pSize is NULL
//   ippStsSizeErr      Some size of kernelSize or roiWidth less or equal zero
//  Remark:             Function may return zero size of buffer.
*/
IPPAPI( IppStatus, ippiFilterGetBufSize_64f_C1R, (IppiSize  kernelSize, int roiWidth, int* pSize))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFilter_64f_C1R
//  Purpose:    Filters an image using a general float rectangular kernel
//  Parameters:
//      pSrc            Pointer to the source buffer
//      srcStep         Step in bytes through the source image buffer
//      pDst            Pointer to the destination buffer
//      dstStep         Step in bytes through the destination image buffer
//      dstRoiSize      Size of the source and destination ROI in pixels
//      pKernel         Pointer to the kernel values ( 64f kernel )
//      kernelSize      Size of the rectangular kernel in pixels.
//      anchor          Anchor cell specifying the rectangular kernel alignment
//                      with respect to the position of the input pixel
//      pBuffer         Pointer to work buffer
//  Returns:
//   ippStsNoErr        Ok
//   ippStsNullPtrErr   Some of pointers to pSrc, pDst or pKernel are NULL or
//                      pBuffer is null but GetBufSize returned non zero size
//   ippStsSizeErr      Some size of dstRoiSize or kernalSize less or equal zero
//   ippStsStepErr      srcStep is less than (roiWidth + kernelWidth - 1) * sizeof(Ipp64f) or
//                      dstStep is less than  roiWidth * sizeof(Ipp64f)
*/

IPPAPI( IppStatus, ippiFilter_64f_C1R, ( const Ipp64f* pSrc, int srcStep,
        Ipp64f* pDst, int dstStep, IppiSize dstRoiSize, const Ipp64f* pKernel,
        IppiSize kernelSize, IppiPoint anchor, Ipp8u* pBuffer ))


/*
//  Purpose:    Divides pixel values of an image by pixel values of
//              another image with three rounding modes (ippRndZero,ippRndNear,ippRndFinancial)
//              and places the scaled results in a destination
//              image.
//  Name:       ippiDiv_Round_16s_C1RSfs, ippiDiv_Round_8u_C1RSfs, ippiDiv_Round_16u_C1RSfs,
//              ippiDiv_Round_16s_C3RSfs, ippiDiv_Round_8u_C3RSfs, ippiDiv_Round_16u_C3RSfs,
//              ippiDiv_Round_16s_C4RSfs, ippiDiv_Round_8u_C4RSfs, ippiDiv_Round_16u_C4RSfs,
//              ippiDiv_Round_16s_AC4RSfs, ippiDiv_Round_8u_AC4RSfs, ippiDiv_Round_16u_AC4RSfs,
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         One of the pointers is NULL
//    ippStsSizeErr            roiSize has a field with zero or negative value
//    ippStsStepErr            At least one step value is less than or equal to zero
//    ippStsDivByZero          A warning that a divisor value is zero, the function
//                             execution is continued.
//                    If a dividend is equal to zero, then the result is zero;
//                    if it is greater than zero, then the result is IPP_MAX_16S, or IPP_MAX_8U, or IPP_MAX_16U
//                    if it is less than zero (for 16s), then the result is IPP_MIN_16S
//   ippStsRoundModeNotSupportedErr Unsupported round mode
//
//
//  Parameters:
//    pSrc1                    Pointer to the divisor source image
//    src1Step                 Step through the divisor source image
//    pSrc2                    Pointer to the dividend source image
//    src2Step                 Step through the dividend source image
//    pDst                     Pointer to the destination image
//    dstStep                  Step through the destination image
//    roiSize                  Size of the ROI
//    rndMode           Rounding mode (ippRndZero, ippRndNear or ippRndFinancial)
//    scaleFactor              Scale factor
*/

IPPAPI(IppStatus, ippiDiv_Round_16s_C1RSfs, (const Ipp16s* pSrc1, int src1Step,
       const Ipp16s* pSrc2, int src2Step,    Ipp16s* pDst, int dstStep, IppiSize roiSize,
       IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_Round_16s_C3RSfs, (const Ipp16s* pSrc1, int src1Step,
       const Ipp16s* pSrc2, int src2Step, Ipp16s* pDst, int dstStep, IppiSize roiSize,
       IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_Round_16s_C4RSfs, (const Ipp16s* pSrc1, int src1Step,
       const Ipp16s* pSrc2, int src2Step, Ipp16s* pDst, int dstStep, IppiSize roiSize,
       IppRoundMode rndMode, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_Round_16s_AC4RSfs, (const Ipp16s* pSrc1, int src1Step,
       const Ipp16s* pSrc2, int src2Step, Ipp16s* pDst, int dstStep, IppiSize roiSize,
       IppRoundMode rndMode, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_Round_8u_C1RSfs,  (const Ipp8u* pSrc1, int src1Step,
       const Ipp8u* pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize,
       IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_Round_8u_C3RSfs,  (const Ipp8u* pSrc1, int src1Step,
       const Ipp8u* pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize,
       IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_Round_8u_C4RSfs, (const Ipp8u* pSrc1, int src1Step,
       const Ipp8u* pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize,
       IppRoundMode rndMode, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_Round_8u_AC4RSfs, (const Ipp8u* pSrc1, int src1Step,
       const Ipp8u* pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize roiSize,
       IppRoundMode rndMode, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_Round_16u_C1RSfs, (const Ipp16u* pSrc1, int src1Step,
       const Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize,
       IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_Round_16u_C3RSfs, (const Ipp16u* pSrc1, int src1Step,
       const Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize,
       IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_Round_16u_C4RSfs, (const Ipp16u* pSrc1, int src1Step,
       const Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize,
        IppRoundMode rndMode, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_Round_16u_AC4RSfs, (const Ipp16u* pSrc1, int src1Step,
       const Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize roiSize,
        IppRoundMode rndMode, int ScaleFactor))
/*
//  Purpose:    Divides pixel values of an image by pixel values of
//              another image with three rounding modes (ippRndZero,ippRndNear,ippRndFinancial)
//              and places the scaled results in a destination
//              image.
//  Name:       ippiDiv_Round_16s_C1IRSfs, ippiDiv_Round_8u_C1IRSfs, ippiDiv_Round_16u_C1IRSfs,
//              ippiDiv_Round_16s_C3IRSfs, ippiDiv_Round_8u_C3IRSfs, ippiDiv_Round_16u_C3IRSfs,
//              ippiDiv_Round_16s_C4IRSfs, ippiDiv_Round_8u_C4IRSfs, ippiDiv_Round_16u_C4IRSfs,
//              ippiDiv_Round_16s_AC4IRSfs, ippiDiv_Round_8u_AC4IRSfs, ippiDiv_Round_16u_AC4IRSfs,
//  Parameters:
//    pSrc                     Pointer to the divisor source image
//    srcStep                  Step through the divisor source image
//    pSrcDst                  Pointer to the dividend source/destination image
//    srcDstStep               Step through the dividend source/destination image
//    roiSize                  Size of the ROI
//    rndMode           Rounding mode (ippRndZero, ippRndNear or ippRndFinancial)
//    scaleFactor              Scale factor
//  Returns:
//    ippStsNoErr              OK
//    ippStsNullPtrErr         One of the pointers is NULL
//    ippStsSizeErr            roiSize has a field with zero or negative value
//    ippStsStepErr            At least one step value is less than or equal to zero
//    ippStsDivByZero          A warning that a divisor value is zero, the function
//                             execution is continued.
//                    If a dividend is equal to zero, then the result is zero;
//                    if it is greater than zero, then the result is IPP_MAX_16S, or IPP_MAX_8U, or IPP_MAX_16U
//                    if it is less than zero (for 16s), then the result is IPP_MIN_16S
//   ippStsRoundModeNotSupportedErr Unsupported round mode
*/
IPPAPI(IppStatus, ippiDiv_Round_16s_C1IRSfs, (const Ipp16s* pSrc, int srcStep,
         Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize,
       IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_Round_16s_C3IRSfs, (const Ipp16s* pSrc, int srcStep,
         Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize,
       IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_Round_16s_C4IRSfs, (const Ipp16s* pSrc, int srcStep,
         Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize,
       IppRoundMode rndMode, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_Round_16s_AC4IRSfs, (const Ipp16s* pSrc, int srcStep,
         Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize,
       IppRoundMode rndMode, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_Round_8u_C1IRSfs,  (const Ipp8u* pSrc, int srcStep,
         Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize,
       IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_Round_8u_C3IRSfs,  (const Ipp8u* pSrc, int srcStep,
         Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize,
       IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_Round_8u_C4IRSfs, (const Ipp8u* pSrc, int srcStep,
         Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize,
       IppRoundMode rndMode, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_Round_8u_AC4IRSfs, (const Ipp8u* pSrc, int srcStep,
         Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize,
       IppRoundMode rndMode, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_Round_16u_C1IRSfs, (const Ipp16u* pSrc, int srcStep,
         Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize,
       IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_Round_16u_C3IRSfs, (const Ipp16u* pSrc, int srcStep,
         Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize,
       IppRoundMode rndMode, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_Round_16u_C4IRSfs, (const Ipp16u* pSrc, int srcStep,
         Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize,
        IppRoundMode rndMode, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_Round_16u_AC4IRSfs, (const Ipp16u* pSrc, int srcStep,
         Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize,
        IppRoundMode rndMode, int ScaleFactor))



/* /////////////////////////////////////////////////////////////////////////////
//                      Resize Transform Functions
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeGetSize
//  Purpose:            Computes the size of Spec structure and temporal buffer for Resize transform
//
//  Parameters:
//    srcSize           Size of the input image (in pixels)
//    dstSize           Size of the output image (in pixels)
//    interpolation     Interpolation method
//    antialiasing      Supported values: 1- resizing with antialiasing, 0 - resizing without antialiasing
//    pSpecSize         Pointer to the size (in bytes) of the Spec structure
//    pInitBufSize      Pointer to the size (in bytes) of the temporal buffer
//
//  Return Values:
//    ippStsNoErr               Indicates no error
//    ippStsNullPtrErr          Indicates an error if one of the specified pointers is NULL
//    ippStsNoOperation         Indicates a warning if width or height of any image is zero
//    ippStsSizeErr             Indicates an error in the following cases:
//                              -  if the source image size is less than a filter size of the chosen
//                                 interpolation method (except ippSuper),
//                              -  if one of the specified dimensions of the source image is less than
//                                 the corresponding dimension of the destination image (for ippSuper method only),
//                              -  if width or height of the source or destination image is negative,
//                              -  if width or height of the source or destination image is negative.
//    ippStsExceededSizeErr     Indicates an error if one of the calculated sizes exceeds maximum 32 bit signed
//                              integer positive value (the size of the one of the processed images is too large).
//    ippStsInterpolationErr    Indicates an error if interpolation has an illegal value
//    ippStsNoAntialiasing      Indicates a warning if specified interpolation does not support antialiasing
//    ippStsNotSupportedModeErr Indicates an error if requested mode is currently not supported
//
//  Notes:
//    1. Supported interpolation methods are ippNearest, ippLinear, ippCubic, ippLanczos and ippSuper.
//    2. If antialiasing value is equal to 1, use the ippResizeAntialiasing<Filter>Init functions, otherwise, use ippResize<Filter>Init
//    3. The implemented interpolation algorithms have the following filter sizes: Nearest Neighbor 1x1,
//       Linear 2x2, Cubic 4x4, 2-lobed Lanczos 4x4.
*/
IPPAPI (IppStatus, ippiResizeGetSize_8u, (
    IppiSize srcSize, IppiSize dstSize,
    IppiInterpolationType interpolation, Ipp32u antialiasing,
    int* pSpecSize, int* pInitBufSize))
IPPAPI (IppStatus, ippiResizeGetSize_16u, (
    IppiSize srcSize, IppiSize dstSize,
    IppiInterpolationType interpolation, Ipp32u antialiasing,
    int* pSpecSize, int* pInitBufSize))
IPPAPI (IppStatus, ippiResizeGetSize_16s, (
    IppiSize srcSize, IppiSize dstSize,
    IppiInterpolationType interpolation, Ipp32u antialiasing,
    int* pSpecSize, Ipp32s* pInitBufSize))
IPPAPI (IppStatus, ippiResizeGetSize_32f, (
    IppiSize srcSize, IppiSize dstSize,
    IppiInterpolationType interpolation, Ipp32u antialiasing,
    int* pSpecSize, int* pInitBufSize))
IPPAPI (IppStatus, ippiResizeGetSize_64f, (
    IppiSize srcSize, IppiSize dstSize,
    IppiInterpolationType interpolation, Ipp32u antialiasing,
    int* pSpecSize, int* pInitBufSize))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeGetBufferSize
//  Purpose:            Computes the size of external buffer for Resize transform
//
//  Parameters:
//    pSpec             Pointer to the Spec structure for resize filter
//    dstSize           Size of the output image (in pixels)
//    numChannels       Number of channels, possible values are 1 or 3 or 4
//    pBufSize          Pointer to the size (in bytes) of the external buffer
//
//  Return Values:
//    ippStsNoErr            Indicates no error
//    ippStsNullPtrErr       Indicates an error if one of the specified pointers is NULL
//    ippStsNoOperation      Indicates a warning if width or height of output image is zero
//    ippStsContextMatchErr  Indicates an error if pointer to an invalid pSpec structure is passed
//    ippStsNumChannelErr    Indicates an error if numChannels has illegal value
//    ippStsSizeErr          Indicates an error condition in the following cases:
//                           - if width or height of the source image is negative,
//    ippStsExceededSizeErr  Indicates an error if one of the calculated sizes exceeds maximum 32 bit signed
//                           integer positive value (the size of the one of the processed images is too large).
//    ippStsSizeWrn          Indicates a warning if the destination image size is more than
//                           the destination image origin size
*/
IPPAPI (IppStatus, ippiResizeGetBufferSize_8u, (
    const IppiResizeSpec_32f* pSpec,
    IppiSize dstSize, Ipp32u numChannels,
    int* pBufSize))
IPPAPI (IppStatus, ippiResizeGetBufferSize_16u, (
    const IppiResizeSpec_32f* pSpec,
    IppiSize dstSize, Ipp32u numChannels,
    int* pBufSize))
IPPAPI (IppStatus, ippiResizeGetBufferSize_16s, (
    const IppiResizeSpec_32f* pSpec,
    IppiSize dstSize, Ipp32u numChannels,
    int* pBufSize))
IPPAPI (IppStatus, ippiResizeGetBufferSize_32f, (
    const IppiResizeSpec_32f* pSpec,
    IppiSize dstSize, Ipp32u numChannels,
    int* pBufSize))
IPPAPI (IppStatus, ippiResizeGetBufferSize_64f, (
    const IppiResizeSpec_64f* pSpec,
    IppiSize dstSize, Ipp32u numChannels,
    int* pBufSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeGetBorderSize
//  Purpose:            Computes the size of possible borders for Resize transform
//
//  Parameters:
//    pSpec             Pointer to the Spec structure for resize filter
//    borderSize        Size of necessary borders (for memory allocation)
//
//  Return Values:
//    ippStsNoErr           Indicates no error
//    ippStsNullPtrErr      Indicates an error if one of the specified pointers is NULL
//    ippStsContextMatchErr Indicates an error if pointer to an invalid pSpec structure is passed
*/
IPPAPI (IppStatus, ippiResizeGetBorderSize_8u, (
    const IppiResizeSpec_32f* pSpec,
    IppiBorderSize* borderSize))
IPPAPI (IppStatus, ippiResizeGetBorderSize_16u, (
    const IppiResizeSpec_32f* pSpec,
    IppiBorderSize* borderSize))
IPPAPI (IppStatus, ippiResizeGetBorderSize_16s, (
    const IppiResizeSpec_32f* pSpec,
    IppiBorderSize* borderSize))
IPPAPI (IppStatus, ippiResizeGetBorderSize_32f, (
    const IppiResizeSpec_32f* pSpec,
    IppiBorderSize* borderSize))
IPPAPI (IppStatus, ippiResizeGetBorderSize_64f, (
    const IppiResizeSpec_64f* pSpec,
    IppiBorderSize* borderSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeGetSrcOffset
//  Purpose:            Computes the offset of input image for Resize transform by tile processing
//
//  Parameters:
//    pSpec             Pointer to the Spec structure for resize filter
//    dstOffset         Offset of the tiled destination image respective
//                      to the destination image origin
//    srcOffset         Pointer to the computed offset of input image
//
//  Return Values:
//    ippStsNoErr           Indicates no error
//    ippStsNullPtrErr      Indicates an error if one of the specified pointers is NULL
//    ippStsContextMatchErr Indicates an error if pointer to an invalid pSpec structure is passed
//    ippStsOutOfRangeErr   Indicates an error if the destination image offset point is outside the
//                          destination image origin
*/
IPPAPI (IppStatus, ippiResizeGetSrcOffset_8u, (
    const IppiResizeSpec_32f* pSpec,
    IppiPoint dstOffset, IppiPoint* srcOffset))
IPPAPI (IppStatus, ippiResizeGetSrcOffset_16u, (
    const IppiResizeSpec_32f* pSpec,
    IppiPoint dstOffset, IppiPoint* srcOffset))
IPPAPI (IppStatus, ippiResizeGetSrcOffset_16s, (
    const IppiResizeSpec_32f* pSpec,
    IppiPoint dstOffset, IppiPoint* srcOffset))
IPPAPI (IppStatus, ippiResizeGetSrcOffset_32f, (
    const IppiResizeSpec_32f* pSpec,
    IppiPoint dstOffset, IppiPoint* srcOffset))
IPPAPI (IppStatus, ippiResizeGetSrcOffset_64f, (
    const IppiResizeSpec_64f* pSpec,
    IppiPoint dstOffset, IppiPoint* srcOffset))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeGetSrcRoi
//  Purpose:            Computes the ROI of input image
//                      for Resize transform by tile processing
//
//  Parameters:
//    pSpec             Pointer to the Spec structure for resize filter
//    dstRoiOffset      Offset of the destination image ROI
//    dstRoiSize        Size of the ROI of destination image
//    srcRoiOffset      Pointer to the computed offset of source image ROI
//    srcRoiSize        Pointer to the computed ROI size of source image
//
//  Return Values:
//    ippStsNoErr           Indicates no error
//    ippStsNullPtrErr      Indicates an error if one of the specified pointers is NULL
//    ippStsContextMatchErr Indicates an error if pointer to an invalid pSpec structure is passed
//    ippStsOutOfRangeErr   Indicates an error if the destination image offset point is outside
//                          the destination image origin
//    ippStsSizeErr         Indicates an error in the following cases:
//                           -  if width or height of the source or destination image is negative or equal to 0,
//    IppStsSizeWrn         Indicates a warning if the destination ROI exceeds with
//                          the destination image origin
*/

IPPAPI (IppStatus, ippiResizeGetSrcRoi_8u, (const IppiResizeSpec_32f* pSpec,
    IppiPoint dstRoiOffset, IppiSize dstRoiSize,
    IppiPoint* srcRoiOffset, IppiSize* srcRoiSize))

IPPAPI (IppStatus, ippiResizeGetSrcRoi_16u, (const IppiResizeSpec_32f* pSpec,
    IppiPoint dstRoiOffset, IppiSize dstRoiSize,
    IppiPoint* srcRoiOffset, IppiSize* srcRoiSize))

IPPAPI (IppStatus, ippiResizeGetSrcRoi_16s, (const IppiResizeSpec_32f* pSpec,
    IppiPoint dstRoiOffset, IppiSize dstRoiSize,
    IppiPoint* srcRoiOffset, IppiSize* srcRoiSize))

IPPAPI (IppStatus, ippiResizeGetSrcRoi_32f, (const IppiResizeSpec_32f* pSpec,
    IppiPoint dstRoiOffset, IppiSize dstRoiSize,
    IppiPoint* srcRoiOffset, IppiSize* srcRoiSize))

IPPAPI (IppStatus, ippiResizeGetSrcRoi_64f, (const IppiResizeSpec_64f* pSpec,
    IppiPoint dstRoiOffset, IppiSize dstRoiSize,
    IppiPoint* srcRoiOffset, IppiSize* srcRoiSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeNearestInit
//                      ippiResizeLinearInit
//                      ippiResizeCubicInit
//                      ippiResizeLanczosInit
//                      ippiResizeSuperInit
//
//  Purpose:            Initializes the Spec structure for the Resize transform
//                      by different interpolation methods
//
//  Parameters:
//    srcSize           Size of the input image (in pixels)
//    dstSize           Size of the output image (in pixels)
//    valueB            The first parameter (B) for specifying Cubic filters
//    valueC            The second parameter (C) for specifying Cubic filters
//    numLobes          The parameter for specifying Lanczos (2 or 3) or Hahn (3 or 4) filters
//    pInitBuf          Pointer to the temporal buffer for several filter initialization
//    pSpec             Pointer to the Spec structure for resize filter
//
//  Return Values:
//    ippStsNoErr               Indicates no error
//    ippStsNullPtrErr          Indicates an error if one of the specified pointers is NULL
//    ippStsNoOperation         Indicates a warning if width or height of any image is zero
//    ippStsSizeErr             Indicates an error in the following cases:
//                              -  if width or height of the source or destination image is negative,
//                              -  if the source image size is less than a filter size of the chosen
//                                 interpolation method (except ippiResizeSuperInit).
//                              -  if one of the specified dimensions of the source image is less than
//                                 the corresponding dimension of the destination image
//                                 (for ippiResizeSuperInit only).
//    ippStsNotSupportedModeErr Indicates an error if the requested mode is not supported.
//
//  Notes/References:
//    1. The equation shows the family of cubic filters:
//           ((12-9B-6C)*|x|^3 + (-18+12B+6C)*|x|^2                  + (6-2B)  ) / 6   for |x| < 1
//    K(x) = ((   -B-6C)*|x|^3 + (    6B+30C)*|x|^2 + (-12B-48C)*|x| + (8B+24C)) / 6   for 1 <= |x| < 2
//           0   elsewhere
//    Some values of (B,C) correspond to known cubic splines: Catmull-Rom (B=0,C=0.5), B-Spline (B=1,C=0) and other.
//      Mitchell, Don P.; Netravali, Arun N. (Aug. 1988). "Reconstruction filters in computer graphics"
//      http://www.mentallandscape.com/Papers_siggraph88.pdf
//
//    2. Hahn filter does not supported now.
//    3. The implemented interpolation algorithms have the following filter sizes: Nearest Neighbor 1x1,
//       Linear 2x2, Cubic 4x4, 2-lobed Lanczos 4x4, 3-lobed Lanczos 6x6.
*/
IPPAPI (IppStatus, ippiResizeNearestInit_8u, (
    IppiSize srcSize, IppiSize dstSize,
    IppiResizeSpec_32f* pSpec))
IPPAPI (IppStatus, ippiResizeNearestInit_16u, (
    IppiSize srcSize, IppiSize dstSize,
    IppiResizeSpec_32f* pSpec))
IPPAPI (IppStatus, ippiResizeNearestInit_16s, (
    IppiSize srcSize, IppiSize dstSize,
    IppiResizeSpec_32f* pSpec))
IPPAPI (IppStatus, ippiResizeNearestInit_32f, (
    IppiSize srcSize, IppiSize dstSize,
    IppiResizeSpec_32f* pSpec))
IPPAPI (IppStatus, ippiResizeLinearInit_8u, (
    IppiSize srcSize, IppiSize dstSize,
    IppiResizeSpec_32f* pSpec))
IPPAPI (IppStatus, ippiResizeLinearInit_16u, (
    IppiSize srcSize, IppiSize dstSize,
    IppiResizeSpec_32f* pSpec))
IPPAPI (IppStatus, ippiResizeLinearInit_16s, (
    IppiSize srcSize, IppiSize dstSize,
    IppiResizeSpec_32f* pSpec))
IPPAPI (IppStatus, ippiResizeLinearInit_32f, (
    IppiSize srcSize, IppiSize dstSize,
    IppiResizeSpec_32f* pSpec))
IPPAPI (IppStatus, ippiResizeLinearInit_64f, (
    IppiSize srcSize, IppiSize dstSize,
    IppiResizeSpec_64f* pSpec))
IPPAPI (IppStatus, ippiResizeCubicInit_8u, (
    IppiSize srcSize, IppiSize dstSize, Ipp32f valueB, Ipp32f valueC,
    IppiResizeSpec_32f* pSpec, Ipp8u* pInitBuf))
IPPAPI (IppStatus, ippiResizeCubicInit_16u, (
    IppiSize srcSize, IppiSize dstSize, Ipp32f valueB, Ipp32f valueC,
    IppiResizeSpec_32f* pSpec, Ipp8u* pInitBuf))
IPPAPI (IppStatus, ippiResizeCubicInit_16s, (
    IppiSize srcSize, IppiSize dstSize, Ipp32f valueB, Ipp32f valueC,
    IppiResizeSpec_32f* pSpec, Ipp8u* pInitBuf))
IPPAPI (IppStatus, ippiResizeCubicInit_32f, (
    IppiSize srcSize, IppiSize dstSize, Ipp32f valueB, Ipp32f valueC,
    IppiResizeSpec_32f* pSpec, Ipp8u* pInitBuf))
IPPAPI (IppStatus, ippiResizeLanczosInit_8u, (
    IppiSize srcSize, IppiSize dstSize, Ipp32u numLobes,
    IppiResizeSpec_32f* pSpec, Ipp8u* pInitBuf))
IPPAPI (IppStatus, ippiResizeLanczosInit_16u, (
    IppiSize srcSize, IppiSize dstSize, Ipp32u numLobes,
    IppiResizeSpec_32f* pSpec, Ipp8u* pInitBuf))
IPPAPI (IppStatus, ippiResizeLanczosInit_16s, (
    IppiSize srcSize, IppiSize dstSize, Ipp32u numLobes,
    IppiResizeSpec_32f* pSpec, Ipp8u* pInitBuf))
IPPAPI (IppStatus, ippiResizeLanczosInit_32f, (
    IppiSize srcSize, IppiSize dstSize, Ipp32u numLobes,
    IppiResizeSpec_32f* pSpec, Ipp8u* pInitBuf))
IPPAPI (IppStatus, ippiResizeSuperInit_8u, (
    IppiSize srcSize, IppiSize dstSize,
    IppiResizeSpec_32f* pSpec))
IPPAPI (IppStatus, ippiResizeSuperInit_16u, (
    IppiSize srcSize, IppiSize dstSize,
    IppiResizeSpec_32f* pSpec))
IPPAPI (IppStatus, ippiResizeSuperInit_16s, (
    IppiSize srcSize, IppiSize dstSize,
    IppiResizeSpec_32f* pSpec))
IPPAPI (IppStatus, ippiResizeSuperInit_32f, (
    IppiSize srcSize, IppiSize dstSize,
    IppiResizeSpec_32f* pSpec))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeNearest
//                      ippiResizeLinear
//                      ippiResizeCubic
//                      ippiResizeLanczos
//                      ippiResizeSuper
//
//  Purpose:            Changes an image size by different interpolation methods
//
//  Parameters:
//    pSrc              Pointer to the source image
//    srcStep           Distance (in bytes) between of consecutive lines in the source image
//    pDst              Pointer to the destination image
//    dstStep           Distance (in bytes) between of consecutive lines in the destination image
//    dstOffset         Offset of tiled image respectively destination image origin
//    dstSize           Size of the destination image (in pixels)
//    border            Type of the border
//    borderValue       Pointer to the constant value(s) if border type equals ippBorderConstant
//    pSpec             Pointer to the Spec structure for resize filter
//    pBuffer           Pointer to the work buffer
//
//  Return Values:
//    ippStsNoErr               Indicates no error
//    ippStsNullPtrErr          Indicates an error if one of the specified pointers is NULL
//    ippStsNoOperation         Indicates a warning if width or height of output image is zero
//    ippStsBorderErr           Indicates an error if border type has an illegal value
//    ippStsContextMatchErr     Indicates an error if pointer to an invalid pSpec structure is passed
//    ippStsNotSupportedModeErr Indicates an error if requested mode is currently not supported
//    ippStsSizeErr             Indicates an error if width or height of the destination image
//                              is negative
//    ippStsStepErr             Indicates an error if the step value is not data type multiple
//    ippStsOutOfRangeErr       Indicates an error if the destination image offset point is outside the
//                              destination image origin
//    ippStsSizeWrn             Indicates a warning if the destination image size is more than
//                              the destination image origin size
//
//  Notes:
//    1. Supported border types are ippBorderInMemory and ippBorderReplicate
//       (except Nearest Neighbor and Super Sampling methods).
//    2. Hahn filter does not supported now.
*/
IPPAPI (IppStatus, ippiResizeNearest_8u_C1R, (
    const Ipp8u* pSrc, Ipp32s srcStep,
    Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeNearest_8u_C3R, (
    const Ipp8u* pSrc, Ipp32s srcStep,
    Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeNearest_8u_C4R, (
    const Ipp8u* pSrc, Ipp32s srcStep,
    Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeNearest_16u_C1R, (
    const Ipp16u* pSrc, Ipp32s srcStep,
    Ipp16u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeNearest_16u_C3R, (
    const Ipp16u* pSrc, Ipp32s srcStep,
    Ipp16u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeNearest_16u_C4R, (
    const Ipp16u* pSrc, Ipp32s srcStep,
    Ipp16u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeNearest_16s_C1R, (
    const Ipp16s* pSrc, Ipp32s srcStep,
    Ipp16s* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeNearest_16s_C3R, (
    const Ipp16s* pSrc, Ipp32s srcStep,
    Ipp16s* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeNearest_16s_C4R, (
    const Ipp16s* pSrc, Ipp32s srcStep,
    Ipp16s* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeNearest_32f_C1R, (
    const Ipp32f* pSrc, Ipp32s srcStep,
    Ipp32f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeNearest_32f_C3R, (
    const Ipp32f* pSrc, Ipp32s srcStep,
    Ipp32f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeNearest_32f_C4R, (
    const Ipp32f* pSrc, Ipp32s srcStep,
    Ipp32f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_8u_C1R, (
    const Ipp8u* pSrc, Ipp32s srcStep,
    Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp8u* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_8u_C3R, (
    const Ipp8u* pSrc, Ipp32s srcStep,
    Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp8u* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_8u_C4R, (
    const Ipp8u* pSrc, Ipp32s srcStep,
    Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp8u* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_16u_C1R, (
    const Ipp16u* pSrc, Ipp32s srcStep,
    Ipp16u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp16u* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_16u_C3R, (
    const Ipp16u* pSrc, Ipp32s srcStep,
    Ipp16u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp16u* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_16u_C4R, (
    const Ipp16u* pSrc, Ipp32s srcStep,
    Ipp16u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp16u* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_16s_C1R, (
    const Ipp16s* pSrc, Ipp32s srcStep,
    Ipp16s* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp16s* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_16s_C3R, (
    const Ipp16s* pSrc, Ipp32s srcStep,
    Ipp16s* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp16s* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_16s_C4R, (
    const Ipp16s* pSrc, Ipp32s srcStep,
    Ipp16s* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp16s* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_32f_C1R, (
    const Ipp32f* pSrc, Ipp32s srcStep,
    Ipp32f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp32f* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_32f_C3R, (
    const Ipp32f* pSrc, const Ipp32s srcStep,
    Ipp32f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp32f* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_32f_C4R, (
    const Ipp32f* pSrc, Ipp32s srcStep,
    Ipp32f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp32f* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_64f_C1R, (
    const Ipp64f* pSrc, Ipp32s srcStep,
    Ipp64f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp64f* pBorderValue,
    const IppiResizeSpec_64f* pSpec,
    Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_64f_C3R, (
    const Ipp64f* pSrc, Ipp32s srcStep,
    Ipp64f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp64f* pBorderValue,
    const IppiResizeSpec_64f* pSpec,
    Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_64f_C4R, (
    const Ipp64f* pSrc, Ipp32s srcStep,
    Ipp64f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp64f* pBorderValue,
    const IppiResizeSpec_64f* pSpec,
    Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeCubic_8u_C1R, (
    const Ipp8u* pSrc, Ipp32s srcStep,
    Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp8u* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeCubic_8u_C3R, (
    const Ipp8u* pSrc, Ipp32s srcStep,
    Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp8u* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeCubic_8u_C4R, (
    const Ipp8u* pSrc, Ipp32s srcStep,
    Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp8u* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeCubic_16u_C1R, (
    const Ipp16u* pSrc, Ipp32s srcStep,
    Ipp16u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp16u* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeCubic_16u_C3R, (
    const Ipp16u* pSrc, Ipp32s srcStep,
    Ipp16u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp16u* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeCubic_16u_C4R, (
    const Ipp16u* pSrc, Ipp32s srcStep,
    Ipp16u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp16u* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeCubic_16s_C1R, (
    const Ipp16s* pSrc, Ipp32s srcStep,
    Ipp16s* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp16s* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeCubic_16s_C3R, (
    const Ipp16s* pSrc, Ipp32s srcStep,
    Ipp16s* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp16s* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeCubic_16s_C4R, (
    const Ipp16s* pSrc, Ipp32s srcStep,
    Ipp16s* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp16s* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeCubic_32f_C1R, (
    const Ipp32f* pSrc, Ipp32s srcStep,
    Ipp32f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp32f* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeCubic_32f_C3R, (
    const Ipp32f* pSrc, Ipp32s srcStep,
    Ipp32f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp32f* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeCubic_32f_C4R, (
    const Ipp32f* pSrc, Ipp32s srcStep,
    Ipp32f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp32f* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLanczos_8u_C1R, (
    const Ipp8u* pSrc, Ipp32s srcStep,
    Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp8u* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLanczos_8u_C3R, (
    const Ipp8u* pSrc, Ipp32s srcStep,
    Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp8u* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLanczos_8u_C4R, (
    const Ipp8u* pSrc, Ipp32s srcStep,
    Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp8u* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLanczos_16u_C1R, (
    const Ipp16u* pSrc, Ipp32s srcStep,
    Ipp16u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp16u* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLanczos_16u_C3R, (
    const Ipp16u* pSrc, Ipp32s srcStep,
    Ipp16u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp16u* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLanczos_16u_C4R, (
    const Ipp16u* pSrc, Ipp32s srcStep,
    Ipp16u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp16u* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLanczos_16s_C1R, (
    const Ipp16s* pSrc, Ipp32s srcStep,
    Ipp16s* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp16s* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLanczos_16s_C3R, (
    const Ipp16s* pSrc, Ipp32s srcStep,
    Ipp16s* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp16s* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLanczos_16s_C4R, (
    const Ipp16s* pSrc, Ipp32s srcStep,
    Ipp16s* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp16s* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLanczos_32f_C1R, (
    const Ipp32f* pSrc, Ipp32s srcStep,
    Ipp32f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp32f* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLanczos_32f_C3R, (
    const Ipp32f* pSrc, Ipp32s srcStep,
    Ipp32f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp32f* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLanczos_32f_C4R, (
    const Ipp32f* pSrc, Ipp32s srcStep,
    Ipp32f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp32f* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeSuper_8u_C1R, (
    const Ipp8u* pSrc, Ipp32s srcStep,
    Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeSuper_8u_C3R, (
    const Ipp8u* pSrc, Ipp32s srcStep,
    Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeSuper_8u_C4R, (
    const Ipp8u* pSrc, Ipp32s srcStep,
    Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeSuper_16u_C1R, (
    const Ipp16u* pSrc, Ipp32s srcStep,
    Ipp16u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeSuper_16u_C3R, (
    const Ipp16u* pSrc, Ipp32s srcStep,
    Ipp16u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeSuper_16u_C4R, (
    const Ipp16u* pSrc, Ipp32s srcStep,
    Ipp16u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeSuper_16s_C1R, (
    const Ipp16s* pSrc, Ipp32s srcStep,
    Ipp16s* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeSuper_16s_C3R, (
    const Ipp16s* pSrc, Ipp32s srcStep,
    Ipp16s* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeSuper_16s_C4R, (
    const Ipp16s* pSrc, Ipp32s srcStep,
    Ipp16s* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeSuper_32f_C1R, (
    const Ipp32f* pSrc, Ipp32s srcStep,
    Ipp32f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeSuper_32f_C3R, (
    const Ipp32f* pSrc, Ipp32s srcStep,
    Ipp32f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeSuper_32f_C4R, (
    const Ipp32f* pSrc, Ipp32s srcStep,
    Ipp32f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeLinearAntialiasingInit
//
//  Purpose:            Initializes the Spec structure for the Resize transform
//                      by different interpolation methods
//
//  Parameters:
//    srcSize           Size of the input image (in pixels)
//    dstSize           Size of the output image (in pixels)
//    valueB            The first parameter (B) for specifying Cubic filters
//    valueC            The second parameter (C) for specifying Cubic filters
//    numLobes          The parameter for specifying Lanczos (2 or 3) or Hahn (3 or 4) filters
//    pInitBuf          Pointer to the temporal buffer for several filter initialization
//    pSpec             Pointer to the Spec structure for resize filter
//
//  Return Values:
//    ippStsNoErr               Indicates no error
//    ippStsNullPtrErr          Indicates an error if one of the specified pointers is NULL
//    ippStsNoOperation         Indicates a warning if width or height of any image is zero
//    ippStsSizeErr             Indicates an error in the following cases:
//                              -  if width or height of the source or destination image is negative,
//                              -  if the source image size is less than a filter size of the chosen
//                                 interpolation method (except ippiResizeSuperInit).
//                              -  if one of the specified dimensions of the source image is less than
//                                 the corresponding dimension of the destination image
//                                 (for ippiResizeSuperInit only).
//    ippStsNotSupportedModeErr Indicates an error if the requested mode is not supported.
//
//  Notes/References:
//    1. The equation shows the family of cubic filters:
//           ((12-9B-6C)*|x|^3 + (-18+12B+6C)*|x|^2                  + (6-2B)  ) / 6   for |x| < 1
//    K(x) = ((   -B-6C)*|x|^3 + (    6B+30C)*|x|^2 + (-12B-48C)*|x| + (8B+24C)) / 6   for 1 <= |x| < 2
//           0   elsewhere
//    Some values of (B,C) correspond to known cubic splines: Catmull-Rom (B=0,C=0.5), B-Spline (B=1,C=0) and other.
//      Mitchell, Don P.; Netravali, Arun N. (Aug. 1988). "Reconstruction filters in computer graphics"
//      http://www.mentallandscape.com/Papers_siggraph88.pdf
//
//    2. Hahn filter does not supported now.
//    3. The implemented interpolation algorithms have the following filter sizes: Nearest Neighbor 1x1,
//       Linear 2x2, Cubic 4x4, 2-lobed Lanczos 4x4, 3-lobed Lanczos 6x6.
*/

IPPAPI (IppStatus, ippiResizeAntialiasingLinearInit, (
    IppiSize srcSize, IppiSize dstSize, IppiResizeSpec_32f* pSpec,
    Ipp8u* pInitBuf))

IPPAPI (IppStatus, ippiResizeAntialiasingCubicInit, (
    IppiSize srcSize, IppiSize dstSize, Ipp32f valueB,
    Ipp32f valueC, IppiResizeSpec_32f* pSpec, Ipp8u* pInitBuf))

IPPAPI (IppStatus, ippiResizeAntialiasingLanczosInit, (
    IppiSize srcSize, IppiSize dstSize, Ipp32u numLobes,
    IppiResizeSpec_32f* pSpec, Ipp8u* pInitBuf))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeAntialiasing
//
//  Purpose:            Changes an image size by different interpolation methods with antialiasing technique
//
//  Parameters:
//    pSrc              Pointer to the source image
//    srcStep           Distance (in bytes) between of consecutive lines in the source image
//    pDst              Pointer to the destination image
//    dstStep           Distance (in bytes) between of consecutive lines in the destination image
//    dstOffset         Offset of tiled image respectively destination image origin
//    dstSize           Size of the destination image (in pixels)
//    border            Type of the border
//    borderValue       Pointer to the constant value(s) if border type equals ippBorderConstant
//    pSpec             Pointer to the Spec structure for resize filter
//    pBuffer           Pointer to the work buffer
//
//  Return Values:
//    ippStsNoErr               Indicates no error
//    ippStsNullPtrErr          Indicates an error if one of the specified pointers is NULL
//    ippStsNoOperation         Indicates a warning if width or height of output image is zero
//    ippStsBorderErr           Indicates an error if border type has an illegal value
//    ippStsContextMatchErr     Indicates an error if pointer to an invalid pSpec structure is passed
//    ippStsNotSupportedModeErr Indicates an error if requested mode is currently not supported
//    ippStsSizeErr             Indicates an error if width or height of the destination image
//                              is negative
//    ippStsStepErr             Indicates an error if the step value is not data type multiple
//    ippStsOutOfRangeErr       Indicates an error if the destination image offset point is outside the
//                              destination image origin
//    ippStsSizeWrn             Indicates a warning if the destination image size is more than
//                              the destination image origin size
//
//  Notes:
//    1. Supported border types are ippBorderInMemory and ippBorderReplicate
//    2. Hahn filter does not supported now.
*/
IPPAPI (IppStatus, ippiResizeAntialiasing_8u_C1R, (
    const Ipp8u* pSrc, Ipp32s srcStep, Ipp8u* pDst,
    Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp8u* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeAntialiasing_8u_C3R, (
    const Ipp8u* pSrc, Ipp32s srcStep, Ipp8u* pDst,
    Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp8u* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeAntialiasing_8u_C4R, (
    const Ipp8u* pSrc, Ipp32s srcStep, Ipp8u* pDst,
    Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp8u* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))

IPPAPI (IppStatus, ippiResizeAntialiasing_16u_C1R, (
    const Ipp16u* pSrc, Ipp32s srcStep, Ipp16u* pDst,
    Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp16u* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeAntialiasing_16u_C3R, (
    const Ipp16u* pSrc, Ipp32s srcStep, Ipp16u* pDst,
    Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp16u* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeAntialiasing_16u_C4R, (
    const Ipp16u* pSrc, Ipp32s srcStep, Ipp16u* pDst,
    Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp16u* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))

IPPAPI (IppStatus, ippiResizeAntialiasing_16s_C1R, (
    const Ipp16s* pSrc, Ipp32s srcStep, Ipp16s* pDst,
    Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp16s* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeAntialiasing_16s_C3R, (
    const Ipp16s* pSrc, Ipp32s srcStep, Ipp16s* pDst,
    Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp16s* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeAntialiasing_16s_C4R, (
    const Ipp16s* pSrc, Ipp32s srcStep, Ipp16s* pDst,
    Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp16s* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))

IPPAPI (IppStatus, ippiResizeAntialiasing_32f_C1R, (
    const Ipp32f* pSrc, Ipp32s srcStep, Ipp32f* pDst,
    Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp32f* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeAntialiasing_32f_C3R, (
    const Ipp32f* pSrc, Ipp32s srcStep, Ipp32f* pDst,
    Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp32f* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeAntialiasing_32f_C4R, (
    const Ipp32f* pSrc, Ipp32s srcStep, Ipp32f* pDst,
    Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp32f* pBorderValue,
    const IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//                      Resize Transform Functions. YUY2 pixel format
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeYUV422GetSize
//  Purpose:            Computes the size of Spec structure and temporal buffer for Resize transform
//
//  Parameters:
//    srcSize           Size of the source image (in pixels)
//    dstSize           Size of the destination image (in pixels)
//    interpolation     Interpolation method
//    antialiasing      Antialiasing method
//    pSpecSize         Pointer to the size (in bytes) of the Spec structure
//    pInitBufSize      Pointer to the size (in bytes) of the temporal buffer
//
//  Return Values:
//    ippStsNoErr               Indicates no error
//    ippStsNullPtrErr          Indicates an error if one of the specified pointers is NULL
//    ippStsNoOperation         Indicates a warning if width or height of any image is zero
//    ippStsSizeErr             Indicates an error in the following cases:
//                              - if the source image size is less than the filter size
//                                for the chosen interpolation method,
//                              - if one of the calculated sizes exceeds maximum 32 bit signed integer
//                                positive value (the size of one of the processed images is too large).
//    ippStsSizeWrn             Indicates a warning if width of the image is odd
//    ippStsInterpolationErr    Indicates an error if interpolation has an illegal value
//    ippStsNoAntialiasing      if the specified interpolation method does not support antialiasing.
//    ippStsNotSupportedModeErr Indicates an error if requested mode is currently not supported
//
//  Notes:
//    1. Supported interpolation methods are ippNearest, ippLinear.
//    2. Antialiasing feature does not supported now. The antialiasing value should be equal zero.
//    3. The implemented interpolation algorithms have the following filter sizes: Nearest Neighbor 2x1,
//       Linear 4x2.
*/
IPPAPI (IppStatus, ippiResizeYUV422GetSize, (
    IppiSize srcSize, IppiSize dstSize,
    IppiInterpolationType interpolation, Ipp32u antialiasing,
    Ipp32s* pSpecSize, Ipp32s* pInitBufSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeYUV422GetBufSize
//  Purpose:            Computes the size of external buffer for Resize transform
//
//  Parameters:
//    pSpec             Pointer to the Spec structure for resize filter
//    dstSize           Size of the output image (in pixels)
//    pBufSize          Pointer to the size (in bytes) of the external buffer
//
//  Return Values:
//    ippStsNoErr           Indicates no error
//    ippStsNullPtrErr      Indicates an error if one of the specified pointers is NULL
//    ippStsNoOperation     Indicates a warning if width or height of the destination image is
//                          equal to zero.
//    ippStsContextMatchErr Indicates an error if pointer to an invalid pSpec structure is passed
//    ippStsSizeWrn         Indicates a warning in the following cases:
//                          - if width of the image is odd,
//                          - if the destination image size is more than the destination image origin size
//    ippStsSizeErr         Indicates an error in the following cases:
//                          - if width of the image is equal to 1,
//                          - if width or height of the source or destination image is negative,
//                          - if the calculated buffer size exceeds maximum 32 bit signed integer positive
//                          value (the processed image size is too large)
*/
IPPAPI (IppStatus, ippiResizeYUV422GetBufSize, (
    const IppiResizeYUV422Spec* pSpec,
    IppiSize dstSize, Ipp32s* pBufSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeYUV422GetBorderSize
//  Purpose:            Computes the size of possible borders for Resize transform
//
//  Parameters:
//    pSpec             Pointer to the Spec structure for resize filter
//    borderSize        Size of necessary borders
//
//  Return Values:
//    ippStsNoErr           Indicates no error
//    ippStsNullPtrErr      Indicates an error if one of the specified pointers is NULL
//    ippStsContextMatchErr Indicates an error if pointer to an invalid pSpec structure is passed
*/
IPPAPI (IppStatus, ippiResizeYUV422GetBorderSize, (
    const IppiResizeYUV422Spec* pSpec,
    IppiBorderSize* borderSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeYUV422GetSrcOffset
//  Purpose:            Computes the offset of input image for Resize transform by tile processing
//
//  Parameters:
//    pSpec             Pointer to the Spec structure for resize filter
//    dstOffset         Offset of the tiled destination image respective to the destination image origin
//    srcOffset         Pointer to the computed offset of source image
//
//  Return Values:
//    ippStsNoErr               Indicates no error
//    ippStsNullPtrErr          Indicates an error if one of the specified pointers is NULL
//    ippStsMisalignedOffsetErr Indicates an error if the x field of the dstOffset parameter is odd.
//    ippStsContextMatchErr     Indicates an error if pointer to the spec structure is invalid.
*/
IPPAPI (IppStatus, ippiResizeYUV422GetSrcOffset, (
    const IppiResizeYUV422Spec* pSpec,
    IppiPoint dstOffset, IppiPoint* srcOffset))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeYUV422GetSrcRoi
//  Purpose:            Computes the ROI of input image
//                      for Resize transform by tile processing
//
//  Parameters:
//    pSpec             Pointer to the Spec structure for resize filter
//    dstRoiOffset      Offset of the destination image ROI
//    dstRoiSize        Size of the ROI of destination image
//    srcRoiOffset      Pointer to the computed offset of source image ROI
//    srcRoiSize        Pointer to the computed ROI size of source image
//
//  Return Values:
//    ippStsNoErr               Indicates no error
//    ippStsNullPtrErr          Indicates an error if one of the specified pointers is NULL
//    ippStsSizeErr             Indicates an error if width of the destination ROI is less or equal to 1,
//                              or if height of the destination ROI is equal to zero or negative
//    ippStsMisalignedOffsetErr Indicates an error if the x field of the dstOffset parameter is odd.
//    ippStsContextMatchErr     Indicates an error if pointer to an invalid pSpec structure is passed
//    ippStsOutOfRangeErr       Indicates an error if the destination image offset point is outside
//                              the destination image origin
//    ippStsSizeWrn             Indicates a warning in the following cases:
//                               - if width of the image is odd,
//                               - if the destination image size is more than the destination image origin size.
*/
IPPAPI (IppStatus, ippiResizeYUV422GetSrcRoi, (const IppiResizeYUV422Spec* pSpec, IppiPoint dstRoiOffset, IppiSize dstRoiSize, IppiPoint* srcRoiOffset, IppiSize* srcRoiSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeYUV422NearestInit
//                      ippiResizeYUV422LinearInit
//
//  Purpose:            Initializes the Spec structure for the Resize transform
//                      by different interpolation methods
//  Parameters:
//    srcSize           Size of the source image (in pixels)
//    dstSize           Size of the destination image (in pixels)
//    pSpec             Pointer to the Spec structure for resize filter
//
//  Return Values:
//    ippStsNoErr           Indicates no error
//    ippStsNullPtrErr      Indicates an error if one of the specified pointers is NULL
//    ippStsNoOperation     Indicates a warning if width or height of any image is zero
//    ippStsSizeWrn         Indicates a warning if width of any image is odd
//    ippStsSizeErr         Indicates an error in the following cases:
//                          - if width of the image is equal to 1,
//                          - if width or height of the source or destination image is negative,
//                          - if the source image size is less than the chosen
//                            interpolation method filter size
//  Notes:
//    1.The implemented interpolation algorithms have the following filter sizes: Nearest Neighbor 2x1,
//      Linear 4x2.
*/
IPPAPI (IppStatus, ippiResizeYUV422NearestInit, (
    IppiSize srcSize, IppiSize dstSize,
    IppiResizeYUV422Spec* pSpec))
IPPAPI (IppStatus, ippiResizeYUV422LinearInit, (
    IppiSize srcSize, IppiSize dstSize,
    IppiResizeYUV422Spec* pSpec))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeYUV422Nearest_8u_C2R
//                      ippiResizeYUV422Linear_8u_C2R
//
//  Purpose:            Changes an image size by different interpolation methods
//
//  Parameters:
//    pSrc              Pointer to the source image
//    srcStep           Distance (in bytes) between of consecutive lines in the source image
//    pDst              Pointer to the destination image
//    dstStep           Distance (in bytes) between of consecutive lines in the destination image
//    dstOffset         Offset of tiled image respectively output origin image
//    dstSize           Size of the destination image (in pixels)
//    border            Type of the border
//    borderValue       Pointer to the constant value(s) if border type equals ippBorderConstant
//    pSpec             Pointer to the Spec structure for resize filter
//    pBuffer           Pointer to the work buffer
//
//  Return Values:
//    ippStsNoErr                Indicates no error
//    ippStsNullPtrErr           Indicates an error if one of the specified pointers is NULL
//    ippStsNoOperation          Indicates a warning if width or height of output image is zero
//    ippStsContextMatchErr      Indicates an error if pointer to an invalid pSpec structure is passed
//    ippStsSizeWrn              Indicates a warning in the following cases:
/                                - if width of the image is odd,
//                               - if the destination image size is more than the destination image origin size.
//    ippStsMisalignedOffsetErr  Indicates an error if the x field of the dstOffset parameter is odd
//    ippStsSizeErr              Indicates an error if width of the destination image is equal to 1,
//                               or if width or height of the source or destination image is negative
//    ippStsOutOfRangeErr        Indicates an error if the destination image offset point is outside
//                               the destination image origin
//    ippStsStepErr              Indicates an error if the step value is not data type multiple
//
//  Notes:
//    1. YUY2 pixel format (Y0U0Y1V0,Y2U1Y3V1,.. or Y0Cb0Y1Cr0,Y2Cb1Y3Cr1,..).
//    2. Supported border types are ippBorderInMemory and ippBorderReplicate for Linear method.
*/
IPPAPI (IppStatus, ippiResizeYUV422Nearest_8u_C2R, (
    const Ipp8u* pSrc, Ipp32s srcStep,
    Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeYUV422Spec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeYUV422Linear_8u_C2R, (
    const Ipp8u* pSrc, Ipp32s srcStep,
    Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp8u* pBorderValue,
    const IppiResizeYUV422Spec* pSpec, Ipp8u* pBuffer))


/* /////////////////////////////////////////////////////////////////////////////
//                      Resize Transform Functions. NV12 planar format
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeYUV420GetSize
//  Purpose:            Computes the size of Spec structure and temporal buffer for Resize transform
//
//  Parameters:
//    srcSize           Size of the input image (in pixels)
//    dstSize           Size of the output image (in pixels)
//    interpolation     Interpolation method
//    antialiasing      Antialiasing method
//    pSpecSize         Pointer to the size (in bytes) of the Spec structure
//    pInitBufSize      Pointer to the size (in bytes) of the temporal buffer
//
//  Return Values:
//    ippStsNoErr               Indicates no error
//    ippStsNullPtrErr          Indicates an error if one of the specified pointers is NULL
//    ippStsNoOperation         Indicates a warning if width or height of any image is zero
//    ippStsSizeErr             Indicates an error in the following cases:
//                              - if width or height of the image is equal to 1,
//                              - if the source image size is less than a filter size of
//                                the chosen interpolation method (except ippSuper),
//                              - if one of the specified dimensions of the source image is less than
//                                the corresponding dimension of the destination image
//                                (for ippSuper method only),
//                              - if width or height of the source or destination image is negative,
//                              - if one of the calculated sizes exceeds maximum 32 bit signed integer
//                                positive value (the size of the one of the processed images is too large).
//    ippStsSizeWrn             Indicates a warning if width or height of any image is odd
//    ippStsInterpolationErr    Indicates an error if interpolation has an illegal value
//    ippStsNoAntialiasing      Indicates a warning if the specified interpolation method does not
//                              support antialiasing
//    ippStsNotSupportedModeErr Indicates an error if requested mode is currently not supported
//
//  Notes:
//    1. Supported interpolation methods are ippLanczos and ippSuper.
//    2. Antialiasing feature does not supported now. The antialiasing value should be equal zero.
//    3. The implemented interpolation algorithms have the following filter sizes: 2-lobed Lanczos 4x4
*/
IPPAPI (IppStatus, ippiResizeYUV420GetSize, (
    IppiSize srcSize, IppiSize dstSize,
    IppiInterpolationType interpolation, Ipp32u antialiasing,
    Ipp32s* pSpecSize, Ipp32s* pInitBufSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeYUV420GetBufferSize
//  Purpose:            Computes the size of external buffer for Resize transform
//
//  Parameters:
//    pSpec             Pointer to the Spec structure for resize filter
//    dstSize           Size of the output image (in pixels)
//    pBufSize          Pointer to the size (in bytes) of the external buffer
//
//  Return Values:
//    ippStsNoErr           Indicates no error
//    ippStsNullPtrErr      Indicates an error if one of the specified pointers is NULL
//    ippStsContextMatchErr Indicates an error if pointer to an invalid pSpec structure is passed
//    ippStsNoOperation     Indicates a warning if width or height of destination image is zero
//    ippStsSizeWrn         Indicates a warning in the following cases:
//                          - if width or height of the image is odd,
//                          - if the destination image size is more than the destination
/                             image origin size
//    ippStsSizeErr         Indicates an error in the following cases
//                          - if width or height of the image is equal to 1,
//                          - if width or height of the destination image is negative,
//                          - if the calculated buffer size exceeds maximum 32 bit signed integer
//                            positive value (the processed image size is too large)
*/
IPPAPI (IppStatus, ippiResizeYUV420GetBufferSize, (
    const IppiResizeYUV420Spec* pSpec,
    IppiSize dstSize, Ipp32s* pBufSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeYUV420GetBorderSize
//  Purpose:            Computes the size of possible borders for Resize transform
//
//  Parameters:
//    pSpec             Pointer to the Spec structure for resize filter
//    borderSize        Size of necessary borders
//
//  Return Values:
//    ippStsNoErr           Indicates no error
//    ippStsNullPtrErr      Indicates an error if one of the specified pointers is NULL
//    ippStsContextMatchErr Indicates an error if pointer to an invalid pSpec structure is passed
*/
IPPAPI (IppStatus, ippiResizeYUV420GetBorderSize, (
    const IppiResizeYUV420Spec* pSpec,
    IppiBorderSize* borderSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeYUV420GetSrcOffset
//  Purpose:            Computes the offset of input image for Resize transform by tile processing
//
//  Parameters:
//    pSpec             Pointer to the Spec structure for resize filter
//    dstOffset         Point of offset of tiled output image
//    srcOffset         Pointer to the computed offset of input image
//
//  Return Values:
//    ippStsNoErr                Indicates no error
//    ippStsNullPtrErr           Indicates an error if one of the specified pointers is NULL
//    ippStsContextMatchErr      Indicates an error if pointer to an invalid pSpec structure is passed
//    ippStsOutOfRangeErr        Indicates an error if the destination image offset
//                               point is outside the destination image origin
//    ippStsMisalignedOffsetErr  Indicates an error if one of the fields of the dstOffset parameter is odd.
*/
IPPAPI (IppStatus, ippiResizeYUV420GetSrcOffset, (
    const IppiResizeYUV420Spec* pSpec,
    IppiPoint dstOffset, IppiPoint* srcOffset))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeYUV420GetSrcRoi
//  Purpose:            Computes the ROI of input image
//                      for Resize transform by tile processing
//
//  Parameters:
//    pSpec             Pointer to the Spec structure for resize filter
//    dstRoiOffset      Offset of the destination image ROI
//    dstRoiSize        Size of the ROI of destination image
//    srcRoiOffset      Pointer to the computed offset of source image ROI
//    srcRoiSize        Pointer to the computed ROI size of source image
//
//  Return Values:
//    ippStsNoErr               Indicates no error
//    ippStsNullPtrErr          Indicates an error if one of the specified pointers is NULL
//    ippStsSizeErr             Indicates an error if width or height of the destination ROI is less or equal to 1,
//    ippStsMisalignedOffsetErr Indicates an error if one of the fields of the dstOffset parameter is odd.
//    ippStsContextMatchErr     Indicates an error if pointer to an invalid pSpec structure is passed
//    ippStsOutOfRangeErr       Indicates an error if the destination image offset point is outside
//                              the destination image origin
//    ippStsSizeWrn             Indicates a warning in the following cases:
//                               - if width of the image is odd,
//                               - if the destination image size is more than the destination image origin size.
*/
IPPAPI (IppStatus, ippiResizeYUV420GetSrcRoi, (const IppiResizeYUV420Spec* pSpec, IppiPoint dstRoiOffset, IppiSize dstRoiSize, IppiPoint* srcRoiOffset, IppiSize* srcRoiSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeYUV420LanczosInit
//                      ippiResizeYUV420SuperInit
//
//  Purpose:            Initializes the Spec structure for the Resize transform
//                      by different interpolation methods
//
//  Parameters:
//    srcSize           Size of the input image (in pixels)
//    dstSize           Size of the output image (in pixels)
//    pSpec             Pointer to the Spec structure for resize filter
//
//  Return Values:
//    ippStsNoErr                Indicates no error
//    ippStsNullPtrErr           Indicates an error if one of the specified pointers is NULL
//    ippStsNoOperation          Indicates a warning if width or height of any image is zero
//    ippStsSizeWrn              Indicates a warning if width or height of any image is odd
//    ippStsSizeErr              Indicates an error in the following cases:
//                                - if width or height of the source or destination image is equal to 1,
//                                - if width or height of the source or destination image is negative,
//                                - if the source image size is less than the chosen interpolation
//                                  filter size (excepting ippSuper)
//                                - if one of the specified dimensions of the source image is less than
//                                  the corresponding dimension of the destination image (only for ippSuper)
//    ippStsNotSupportedModeErr  Indicates an error if the requested mode is not supported
//
//    Note.
//    The implemented interpolation algorithms have the following filter sizes:
//      2-lobed Lanczos 8x8, 3-lobed Lanczos 12x12.
*/
IPPAPI (IppStatus, ippiResizeYUV420LanczosInit, (
    IppiSize srcSize, IppiSize dstSize, Ipp32u numLobes,
    IppiResizeYUV420Spec* pSpec, Ipp8u* pInitBuf))
IPPAPI (IppStatus, ippiResizeYUV420SuperInit, (
    IppiSize srcSize, IppiSize dstSize,
    IppiResizeYUV420Spec* pSpec))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeYUV420Lanczos_8u_P2R
//                      ippiResizeYUV420Super_8u_P2R
//
//  Purpose:            Changes an image size by different interpolation methods
//
//  Parameters:
//    pSrcY             Pointer to the source image Y plane
//    srcYStep          Distance (in bytes) between of consecutive lines in the source image Y plane
//    pSrcUV            Pointer to the source image UV plane
//    srcUVStep         Distance (in bytes) between of consecutive lines in the source image UV plane
//    pDstY             Pointer to the destination image Y plane
//    dstYStep          Distance (in bytes) between of consecutive lines in the destination image Y plane
//    pDstUV            Pointer to the destination image UV plane
//    dstUVStep         Distance (in bytes) between of consecutive lines in the destination image UV plane
//    dstOffset         Offset of tiled image respectively output origin image
//    dstSize           Size of the output image (in pixels)
//    border            Type of the border
//    borderValue       Pointer to the constant value(s) if border type equals ippBorderConstant
//    pSpec             Pointer to the Spec structure for resize filter
//    pBuffer           Pointer to the work buffer
//
//  Return Values:
//    ippStsNoErr                Indicates no error
//    ippStsNullPtrErr           Indicates an error if one of the specified pointers is NULL
//    ippStsNoOperation          Indicates a warning if width or height of destination image is zero
//    ippStsSizeWrn              Indicates a warning in the following cases:
//                               - if width of the image is odd,
//                               - if the destination image exceeds the destination image origin
//    ippStsSizeErr              Indicates an error if width of the destination image is equal to 1,
//                               or if width or height of the source or destination image is negative
//    ippStsBorderErr            Indicates an error if border type has an illegal value
//    ippStsContextMatchErr      Indicates an error if pointer to an invalid pSpec structure is passed
//    ippStsMisalignedOffsetErr  Indicates an error if one of the fields of the dstOffset parameter is odd
//    ippStsNotSupportedModeErr  Indicates an error if the requested mode is not supported
//
//  Notes:
//    1. Source 4:2:0 two-plane image format (NV12):
//      All Y samples (pSrcY) are found first in memory as an array of unsigned char with an even number of lines memory alignment,
//      followed immediately by an array (pSrcUV) of unsigned char containing interleaved U and V samples.
//    2. Supported border types are ippBorderInMemory and ippBorderReplicate for Lanczos methods.
*/
IPPAPI (IppStatus, ippiResizeYUV420Lanczos_8u_P2R, (
    const Ipp8u* pSrcY, Ipp32s srcYStep, const Ipp8u* pSrcUV, Ipp32s srcUVStep,
    Ipp8u* pDstY, Ipp32s dstYStep, Ipp8u* pDstUV, Ipp32s dstUVStep,
    IppiPoint dstOffset, IppiSize dstSize,
    IppiBorderType border, const Ipp8u* borderValue,
    const IppiResizeYUV420Spec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeYUV420Super_8u_P2R, (
    const Ipp8u* pSrcY, Ipp32s srcYStep, const Ipp8u* pSrcUV, Ipp32s srcUVStep,
    Ipp8u* pDstY, Ipp32s dstYStep, Ipp8u* pDstUV, Ipp32s dstUVStep,
    IppiPoint dstOffset, IppiSize dstSize,
    const IppiResizeYUV420Spec* pSpec, Ipp8u* pBuffer))

/*****************************************************************************************************
//  Name:       ippiFilterBorderGetSize, ippiFilterBorderInit, ippiFilterBorder
//  Purpose:    Filters an image using a general integer rectangular kernel
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  One of the pointers is NULL
//   ippStsSizeErr     dstRoiSize or kernelSize has a field with zero or negative value
//   ippStsDivisorErr  Divisor value is zero, function execution is interrupted
//
//  Parameters:
//      pSrc        Distance, in bytes, between the starting points of consecutive lines in the source image
//      srcStep     Step in bytes through the source image buffer
//      pDst        Pointer to the destination buffer
//      dstStep     Distance, in bytes, between the starting points of consecutive lines in the destination image
//      dstRoiSize  Size of the source and destination ROI in pixels
//      pKernel     Pointer to the kernel values
//      kernelSize  Size of the rectangular kernel in pixels.
//      divisor     The integer value by which the computed result is divided.
//      kernelType  Kernel type {ipp16s|ipp32f}
//      dataType    Data type {ipp8u|ipp16u|ipp32f}
//      numChannels Number of channels, possible values are 1, 3 or 4
//      roundMode   Rounding mode (ippRndZero, ippRndNear or ippRndFinancial)
//      pSpecSize   Pointer to the size (in bytes) of the spec structure
//      pBufSize    Pointer to the size (in bytes) of the external buffer
//      pSpec       Pointer to pointer to the allocated and initialized context structure
//      borderType  Type of the border
//      borderValue Pointer to the constant value(s) if border type equals ippBorderConstant
//      pBuffer     Pointer to the work buffer. It can be equal to NULL if optimization algorithm doesn't demand a work buffer
*/

IPPAPI( IppStatus, ippiFilterBorderGetSize,  (IppiSize  kernelSize, IppiSize dstRoiSize, IppDataType dataType, IppDataType kernelType, int numChannels,int* pSpecSize, int* pBufferSize ))
IPPAPI( IppStatus, ippiFilterBorderInit_16s, ( const Ipp16s* pKernel, IppiSize  kernelSize, int divisor, IppDataType dataType, int numChannels , IppRoundMode roundMode, IppiFilterBorderSpec* pSpec ))
IPPAPI( IppStatus, ippiFilterBorderInit_32f, ( const Ipp32f* pKernel, IppiSize  kernelSize,              IppDataType dataType, int numChannels , IppRoundMode roundMode, IppiFilterBorderSpec* pSpec ))
IPPAPI( IppStatus, ippiFilterBorderInit_64f, ( const Ipp64f* pKernel, IppiSize  kernelSize,              IppDataType dataType, int numChannels , IppRoundMode roundMode, IppiFilterBorderSpec* pSpec ))
IPPAPI( IppStatus, ippiFilterBorder_8u_C1R,  ( const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize dstRoiSize, IppiBorderType border, const Ipp8u borderValue[1], const IppiFilterBorderSpec* pSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiFilterBorder_8u_C3R,  ( const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize dstRoiSize, IppiBorderType border, const Ipp8u borderValue[3], const IppiFilterBorderSpec* pSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiFilterBorder_8u_C4R,  ( const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize dstRoiSize, IppiBorderType border, const Ipp8u borderValue[4], const IppiFilterBorderSpec* pSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiFilterBorder_16u_C1R, ( const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiBorderType border, const Ipp16u borderValue[1], const IppiFilterBorderSpec* pSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiFilterBorder_16u_C3R, ( const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiBorderType border, const Ipp16u borderValue[3], const IppiFilterBorderSpec* pSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiFilterBorder_16u_C4R, ( const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiBorderType border, const Ipp16u borderValue[4], const IppiFilterBorderSpec* pSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiFilterBorder_16s_C1R, ( const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiBorderType border, const Ipp16s borderValue[1], const IppiFilterBorderSpec* pSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiFilterBorder_16s_C3R, ( const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiBorderType border, const Ipp16s borderValue[3], const IppiFilterBorderSpec* pSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiFilterBorder_16s_C4R, ( const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, IppiBorderType border, const Ipp16s borderValue[4], const IppiFilterBorderSpec* pSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiFilterBorder_32f_C1R, ( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiBorderType border, const Ipp32f borderValue[1], const IppiFilterBorderSpec* pSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiFilterBorder_32f_C3R, ( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiBorderType border, const Ipp32f borderValue[3], const IppiFilterBorderSpec* pSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiFilterBorder_32f_C4R, ( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiBorderType border, const Ipp32f borderValue[4], const IppiFilterBorderSpec* pSpec, Ipp8u* pBuffer ))
IPPAPI( IppStatus, ippiFilterBorder_64f_C1R, ( const Ipp64f* pSrc, int srcStep, Ipp64f* pDst, int dstStep, IppiSize dstRoiSize, IppiBorderType border, const Ipp64f borderValue[1], const IppiFilterBorderSpec* pSpec, Ipp8u* pBuffer ))
/*
//  Name:       ippiFilterBorderSetMode
//  Purpose:    Set offset value for Ipp8u and Ipp16u and roundMode (Fast or Accurate)
//
//  Parameters:
//    hint        ippAlgHintNone, ippAlgHintFast, ippAlgHintAccurate.  Default, fast or accurate rounding.
//                             ippAlgHintNone and ippAlgHintFast - default modes, mean that the most common rounding is performed with
//                             roundMode passed to Init function, but function performance takes precedence over accuracy and some output
//                             pixels can differ on +-1 from exact result
//                             ippAlgHintAccurate means that all output pixels are exact and accuracy takes precedence over performance
//    offset             offset value. It is just a constant that is added to the final signed result before converting it to unsigned for Ipp8u and Ipp16u data types
//    pSpec            Pointer to the initialized ippiFilter Spec

//  Returns:
//    ippStsNoErr       no errors
//    ippStsNullPtrErr  one of the pointers is NULL
//    ippStsNotSupportedModeErr     the offset value is not supported, for Ipp16s and Ipp32f data types.
//    ippStsAccurateModeNotSupported the accurate mode not supported for some data types. The result of rounding can be inexact.
*/

IPPAPI( IppStatus, ippiFilterBorderSetMode, (IppHintAlgorithm hint, int offset, IppiFilterBorderSpec* pSpec))

/*****************************************************************************************************
//  Name:       ippiLBPImageMode
//  Purpose:    Calculates the LBP of the image.
//  Parameters:
//    pSrc        Pointer to the source image ROI.
//    srcStep     Distance in bytes between starting points of consecutive lines in the source image.
//    pDst        Pointer to the destination image ROI.
//    dstStep     Distance in bytes between starting points of consecutive lines in the destination image.
//    dstRoiSize  Size of the destination ROI in pixels.
//    mode        Specify how LBP is created.
//    borderType  Type of border.
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
IPPAPI(IppStatus,ippiLBPImageMode3x3_8u_C1R,    (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize dstRoiSize,int  mode,IppiBorderType borderType,const Ipp8u*  borderValue))
IPPAPI(IppStatus,ippiLBPImageMode5x5_8u_C1R,    (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize dstRoiSize,int  mode,IppiBorderType borderType,const Ipp8u*  borderValue))
IPPAPI(IppStatus,ippiLBPImageMode5x5_8u16u_C1R, (const Ipp8u*  pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,int  mode,IppiBorderType borderType,const Ipp8u*  borderValue))
IPPAPI(IppStatus,ippiLBPImageMode3x3_32f8u_C1R, (const Ipp32f* pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize dstRoiSize,int  mode,IppiBorderType borderType,const Ipp32f* borderValue))
IPPAPI(IppStatus,ippiLBPImageMode5x5_32f8u_C1R, (const Ipp32f* pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize dstRoiSize,int  mode,IppiBorderType borderType,const Ipp32f* borderValue))
IPPAPI(IppStatus,ippiLBPImageMode5x5_32f16u_C1R,(const Ipp32f* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,int  mode,IppiBorderType borderType,const Ipp32f* borderValue))



/*****************************************************************************************************
//  Name:       ippiLBPImageHorizCorr_...
//  Purpose:    Calculates a correlation between two LBPs.
//  Parameters:
//    pSrc1, pSrc2       Pointers to the source images ROI.
//    srcStep1, srcStep2 Distance in bytes between starting points of consecutive lines in the source image.
//    pDst               Pointer to the destination image ROI.
//    dstStep            Distance in bytes between starting points of consecutive lines in the destination image.
//    dstRoiSize         Size of the destination ROI in pixels.
//    horShift           Horizontal shift of the pSrc2 image.
//    borderType         Type of border. Possible values are:
//                           ippBorderRepl      Border is replicated from the edge pixels.
//                           ippBorderInMem     Border is obtained from the source image pixels in memory.
//                           Mixed borders are also supported.
//                           They can be obtained by the bitwise operation OR between ippBorderRepl and ippBorderInMemTop, ippBorderInMemBottom, ippBorderInMemLeft, ippBorderInMemRight.
//    borderValue         Constant value to assign to pixels of the constant border. This parameter is applicable only to the ippBorderConst border type.
//  Returns:
//    ippStsNoErr      Indicates no error.
//    ippStsNullPtrErr Indicates an error when one of the specified pointers is NULL.
//    ippStsSizeErr    Indicates an error if dstRoiSize has a field with zero or negative value.
//    ippStsBadArgErr  Indicates an error when border has an illegal value.
*/
IPPAPI(IppStatus,ippiLBPImageHorizCorr_8u_C1R, (const Ipp8u  *pSrc1, int src1Step,const Ipp8u  *pSrc2, int src2Step, Ipp8u  *pDst, int dstStep, IppiSize dstRoiSize, int horShift,IppiBorderType borderType,const Ipp8u*  borderValue))
IPPAPI(IppStatus,ippiLBPImageHorizCorr_16u_C1R,(const Ipp16u *pSrc1, int src1Step,const Ipp16u *pSrc2, int src2Step, Ipp16u *pDst, int dstStep, IppiSize dstRoiSize, int horShift,IppiBorderType borderType,const Ipp16u* borderValue))


/* /////////////////////////////////////////////////////////////////////////////
// Name: ippiSADGetBufferSize
//
// Purpose: Compute size of the work buffer for the ippiSAD
//
// Parameters:
//    srcRoiSize  size of the source ROI in pixels
//    tplRoiSize  size of the template ROI in pixels
//    dataType    input data specifier
//    numChannels Number of channels in the images
//    shape       enumeration, defined shape result of the following SAD operation
//    pBufferSize pointer to the computed value of the external buffer size
//
//  Return:
//   ippStsNoErr        no errors
//   ippStsNullPtrErr   pBufferSize==NULL
//   ippStsSizeErr      0>=srcRoiSize.width || 0>=srcRoiSize.height
//                      0>=tplRoiSize.width || 0>=tplRoiSize.height
//   ippStsDataTypeErr  dataType!=8u or dataType!=16u or dataType!=16s or dataType!=32f
//   ippStsNotSupportedModeErr  shape != ippiROIValid
//                              numChannels != 1
//                              dataType has an illegal value
//
*F*/
IPPAPI(IppStatus, ippiSADGetBufferSize,(IppiSize srcRoiSize, IppiSize tplRoiSize, IppDataType dataType, int numChannels,
                                        IppiROIShape shape, int* pBufferSize))

/* /////////////////////////////////////////////////////////////////////////////
// Name: ippiSAD_...
//
// Purpose: Sum of Absolute Differences of given image and template
//
// Parameters:
//    pSrc        pointer to source ROI
//    srcStep     step through the source image
//    srcRoiSize  size of sourse ROI (pixels)
//    pTpl        pointer to template (source) ROI
//    tplStep     step through the template image
//    tplRoiSize  size of template ROI (pixels)
//    pDst        pointer to destination ROI
//    dstStep     step through the destination image
//    shape       defined shape result of the SAD operation
//    scaleFactor scale factor
//    pBuffer     pointer to the buffer for internal computation (is currentry used)
//
// Return status:
//    ippStsNoErr                no errors
//    ippStsNullPtrErr           pSrc==NULL or pTpl==NULL or pDst==NULL
//    ippStsStepErr              srcStep/dstStep has a zero or negative value
//                               srcStep/dstStep value is not multiple to image data size
//    ippStsSizeErr              ROI has any field with zero or negative value
//    ippStsNotSupportedModeErr  intersection of source and destination ROI is detected
//                               shape!=ippiROIValid
//    ippStsBadArgErr            illegal scaleFactor value, i.e. !(0<=scalefactor<log(W*H)
*F*/
IPPAPI(IppStatus, ippiSAD_8u32s_C1RSfs, (const Ipp8u*  pSrc, int srcStep, IppiSize srcRoiSize,
                                         const Ipp8u*  pTpl, int tplStep, IppiSize tplRoiSize,
                                               Ipp32s* pDst, int dstStep, IppiROIShape shape,
                                         int scaleFactor, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiSAD_16u32s_C1RSfs,(const Ipp16u* pSrc, int srcStep, IppiSize srcRoiSize,
                                         const Ipp16u* pTpl, int tplStep, IppiSize tplRoiSize,
                                               Ipp32s* pDst, int dstStep, IppiROIShape shape,
                                         int scaleFactor, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiSAD_16s32s_C1RSfs,(const Ipp16s* pSrc, int srcStep, IppiSize srcRoiSize,
                                         const Ipp16s* pTpl, int tplStep, IppiSize tplRoiSize,
                                               Ipp32s* pDst, int dstStep, IppiROIShape shape,
                                         int scaleFactor, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiSAD_32f_C1R,(const Ipp32f*  pSrc, int srcStep, IppiSize srcRoiSize,
                                   const Ipp32f*  pTpl, int tplStep, IppiSize tplRoiSize,
                                         Ipp32f*  pDst, int dstStep, IppiROIShape shape,
                                   Ipp8u* pBuffer))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiGradientVectorGetBufferSize
//
//  Purpose:            Computes the size of the external buffer for
//                      Gradient() calls
//
//  Parameters:
//    roiSize           Size of destination ROI in pixels
//    mask              Predefined mask of IppiMaskSize type. Possible values are ippMask3x3 or ippMask5x5
//    dataType          Input data type specifier
//    numChannels       Number of channels of the input image
//    pBufferSize       Pointer to the size (in bytes) of the external work buffer.
//
//  Return Values:
//    ippStsNoErr        Indicates no error
//    ippStsNullPtrErr   Indicates an error when pBufferSize is NULL
//    ippStsDataTypeErr  dataType!=8u or dataType!=16u or dataType!=16s or dataType!=32f
//    ippStsSizeErr      Indicates an error when roiSize is negative, or equal to zero.
//    ippStsMaskSizeErr  Indicates an error condition if mask has a wrong value
*/
IPPAPI(IppStatus, ippiGradientVectorGetBufferSize,(IppiSize roiSize, IppiMaskSize mask, IppDataType dataType, int numChannels,
                                                   int* pBufferSize))

/* /////////////////////////////////////////////////////////////////////////////
// Name: ippiGradientVectorSobel_8u16s_C1R
//       ippiGradientVectorSobel_16u32f_C1R
//       ippiGradientVectorSobel_16s32f_C1R
//       ippiGradientVectorSobel_32f_C1R
//
//       ippiGradientVectorScharr_8u16s_C1R
//       ippiGradientVectorScharr_16u32f_C1R
//       ippiGradientVectorScharr_16s32f_C1R
//       ippiGradientVectorScharr_32f_C1R
//
//       ippiGradientVectorPrewitt_8u16s_C1R
//       ippiGradientVectorPrewitt_16u32f_C1R
//       ippiGradientVectorPrewitt_16s32f_C1R
//       ippiGradientVectorPrewitt_32f_C1R
//
//       ippiGradientVectorSobel_8u16s_C3C1R
//       ippiGradientVectorSobel_16u32f_C3C1R
//       ippiGradientVectorSobel_16s32f_C3C1R
//       ippiGradientVectorSobel_32f_C3C1R
//
//       ippiGradientVectorScharr_8u16s_C3C1R
//       ippiGradientVectorScharr_16u32f_C3C1R
//       ippiGradientVectorScharr_16s32f_C3C1R
//       ippiGradientVectorScharr_32f_C3C1R
//
//       ippiGradientVectorPrewitt_8u16s_C3C1R
//       ippiGradientVectorPrewitt_16u32f_C3C1R
//       ippiGradientVectorPrewitt_16s32f_C3C1R
//       ippiGradientVectorPrewitt_32f_C3C1R
//
// Purpose: Computes gradient vectors over an image using Sobel, Scharr or Prewitt operator
//
// Parameters:
//    pSrc        pointer to source ROI
//    srcStep     step through the source image
//    pGx         pointer to the X-component of computed gradient
//    gxStep      step through the X-component image
//    pGy         pointer to the Y-component of computed gradient
//    gyStep      step through the Y-component image
//    pMag        pointer to the magnitude of computed gradient
//    magStep     step through the magnitude image
//    pAngle      pointer to the angle of computed gradient
//    angleStep   step through the magnitude image
//    dstRoiSize  size of destination
//    mask        operator size specfier
//    normType    normalization type (L1 or L2) specfier
//    borderType  kind of border specfier
//    borderValue constant border value
//    pBuffer     pointer to the buffer for internal computation  (is currentry used)
//
// Return status:
//    ippStsNoErr          no error
//    ippStsNullPtrErr     pSrc==NULL
//    ippStsStepErr        srcStep has a zero or negative value
//                         applicable gxStep or gyStep or magStep or angleStep has a zero or negative value
//                         or is not multiple to image data size (4 for floating-point images or by 2 for short-integer images)
//    ippStsSizeErr        ROI has any field with zero or negative value
//    ippStsMaskSizeErr    illegal maskSize specfier value
//    ippStsBadArgErr      illegal normType specfier value
//    ippStsBorderErr      illegal borderType specfier value
*F*/
IPPAPI(IppStatus, ippiGradientVectorSobel_8u16s_C1R,(const Ipp8u* pSrc, int srcStep,
                     Ipp16s* pGx, int gxStep, Ipp16s* pGy, int gyStep,
                     Ipp16s* pMag, int magStep, Ipp32f* pAngle, int angleStep,
                     IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType,
                     IppiBorderType borderType, Ipp8u borderValue,
                     Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiGradientVectorSobel_16u32f_C1R,(const Ipp16u* pSrc, int srcStep,
                     Ipp32f* pGx, int gxStep, Ipp32f* pGy, int gyStep,
                     Ipp32f* pMag, int magStep, Ipp32f* pAngle, int angleStep,
                     IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType,
                     IppiBorderType borderType, Ipp16u borderValue,
                     Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiGradientVectorSobel_16s32f_C1R,(const Ipp16s* pSrc, int srcStep,
                     Ipp32f* pGx, int gxStep, Ipp32f* pGy, int gyStep,
                     Ipp32f* pMag, int magStep, Ipp32f* pAngle, int angleStep,
                     IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType,
                     IppiBorderType borderType, Ipp16s borderValue,
                     Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiGradientVectorSobel_32f_C1R,(const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pGx, int gxStep, Ipp32f* pGy, int gyStep,
                     Ipp32f* pMag, int magStep, Ipp32f* pAngle, int angleStep,
                     IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType,
                     IppiBorderType borderType, Ipp32f borderValue,
                     Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiGradientVectorScharr_8u16s_C1R,(const Ipp8u* pSrc, int srcStep,
                     Ipp16s* pGx, int gxStep, Ipp16s* pGy, int gyStep,
                     Ipp16s* pMag, int magStep, Ipp32f* pAngle, int angleStep,
                     IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType,
                     IppiBorderType borderType, Ipp8u borderValue,
                     Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiGradientVectorScharr_16u32f_C1R,(const Ipp16u* pSrc, int srcStep,
                     Ipp32f* pGx, int gxStep, Ipp32f* pGy, int gyStep,
                     Ipp32f* pMag, int magStep, Ipp32f* pAngle, int angleStep,
                     IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType,
                     IppiBorderType borderType, Ipp16u borderValue,
                     Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiGradientVectorScharr_16s32f_C1R,(const Ipp16s* pSrc, int srcStep,
                     Ipp32f* pGx, int gxStep, Ipp32f* pGy, int gyStep,
                     Ipp32f* pMag, int magStep, Ipp32f* pAngle, int angleStep,
                     IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType,
                     IppiBorderType borderType, Ipp16s borderValue,
                     Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiGradientVectorScharr_32f_C1R,(const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pGx, int gxStep, Ipp32f* pGy, int gyStep,
                     Ipp32f* pMag, int magStep, Ipp32f* pAngle, int angleStep,
                     IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType,
                     IppiBorderType borderType, Ipp32f borderValue,
                     Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiGradientVectorPrewitt_8u16s_C1R,(const Ipp8u* pSrc, int srcStep,
                     Ipp16s* pGx, int gxStep, Ipp16s* pGy, int gyStep,
                     Ipp16s* pMag, int magStep, Ipp32f* pAngle, int angleStep,
                     IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType,
                     IppiBorderType borderType, Ipp8u borderValue,
                     Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiGradientVectorPrewitt_16u32f_C1R,(const Ipp16u* pSrc, int srcStep,
                     Ipp32f* pGx, int gxStep, Ipp32f* pGy, int gyStep,
                     Ipp32f* pMag, int magStep, Ipp32f* pAngle, int angleStep,
                     IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType,
                     IppiBorderType borderType, Ipp16u borderValue,
                     Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiGradientVectorPrewitt_16s32f_C1R,(const Ipp16s* pSrc, int srcStep,
                     Ipp32f* pGx, int gxStep, Ipp32f* pGy, int gyStep,
                     Ipp32f* pMag, int magStep, Ipp32f* pAngle, int angleStep,
                     IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType,
                     IppiBorderType borderType, Ipp16s borderValue,
                     Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiGradientVectorPrewitt_32f_C1R,(const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pGx, int gxStep, Ipp32f* pGy, int gyStep,
                     Ipp32f* pMag, int magStep, Ipp32f* pAngle, int angleStep,
                     IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType,
                     IppiBorderType borderType, Ipp32f borderValue,
                     Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiGradientVectorSobel_8u16s_C3C1R,(const Ipp8u* pSrc, int srcStep,
                     Ipp16s* pGx, int gxStep, Ipp16s* pGy, int gyStep,
                     Ipp16s* pMag, int magStep, Ipp32f* pAngle, int angleStep,
                     IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType,
                     IppiBorderType borderType, const Ipp8u borderValue[3],
                     Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiGradientVectorSobel_16u32f_C3C1R,(const Ipp16u* pSrc, int srcStep,
                     Ipp32f* pGx, int gxStep, Ipp32f* pGy, int gyStep,
                     Ipp32f* pMag, int magStep, Ipp32f* pAngle, int angleStep,
                     IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType,
                     IppiBorderType borderType, const Ipp16u borderValue[3],
                     Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiGradientVectorSobel_16s32f_C3C1R,(const Ipp16s* pSrc, int srcStep,
                     Ipp32f* pGx, int gxStep, Ipp32f* pGy, int gyStep,
                     Ipp32f* pMag, int magStep, Ipp32f* pAngle, int angleStep,
                     IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType,
                     IppiBorderType borderType, const Ipp16s borderValue[3],
                     Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiGradientVectorSobel_32f_C3C1R,(const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pGx, int gxStep, Ipp32f* pGy, int gyStep,
                     Ipp32f* pMag, int magStep, Ipp32f* pAngle, int angleStep,
                     IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType,
                     IppiBorderType borderType, const Ipp32f borderValue[3],
                     Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiGradientVectorScharr_8u16s_C3C1R,(const Ipp8u* pSrc, int srcStep,
                     Ipp16s* pGx, int gxStep, Ipp16s* pGy, int gyStep,
                     Ipp16s* pMag, int magStep, Ipp32f* pAngle, int angleStep,
                     IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType,
                     IppiBorderType borderType, const Ipp8u borderValue[3],
                     Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiGradientVectorScharr_16u32f_C3C1R,(const Ipp16u* pSrc, int srcStep,
                     Ipp32f* pGx, int gxStep, Ipp32f* pGy, int gyStep,
                     Ipp32f* pMag, int magStep, Ipp32f* pAngle, int angleStep,
                     IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType,
                     IppiBorderType borderType, const Ipp16u borderValue[3],
                     Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiGradientVectorScharr_16s32f_C3C1R,(const Ipp16s* pSrc, int srcStep,
                     Ipp32f* pGx, int gxStep, Ipp32f* pGy, int gyStep,
                     Ipp32f* pMag, int magStep, Ipp32f* pAngle, int angleStep,
                     IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType,
                     IppiBorderType borderType, const Ipp16s borderValue[3],
                     Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiGradientVectorScharr_32f_C3C1R,(const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pGx, int gxStep, Ipp32f* pGy, int gyStep,
                     Ipp32f* pMag, int magStep, Ipp32f* pAngle, int angleStep,
                     IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType,
                     IppiBorderType borderType, const Ipp32f borderValue[3],
                     Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiGradientVectorPrewitt_8u16s_C3C1R,(const Ipp8u* pSrc, int srcStep,
                     Ipp16s* pGx, int gxStep, Ipp16s* pGy, int gyStep,
                     Ipp16s* pMag, int magStep, Ipp32f* pAngle, int angleStep,
                     IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType,
                     IppiBorderType borderType, const Ipp8u borderValue[3],
                     Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiGradientVectorPrewitt_16u32f_C3C1R,(const Ipp16u* pSrc, int srcStep,
                     Ipp32f* pGx, int gxStep, Ipp32f* pGy, int gyStep,
                     Ipp32f* pMag, int magStep, Ipp32f* pAngle, int angleStep,
                     IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType,
                     IppiBorderType borderType, const Ipp16u borderValue[3],
                     Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiGradientVectorPrewitt_16s32f_C3C1R,(const Ipp16s* pSrc, int srcStep,
                     Ipp32f* pGx, int gxStep, Ipp32f* pGy, int gyStep,
                     Ipp32f* pMag, int magStep, Ipp32f* pAngle, int angleStep,
                     IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType,
                     IppiBorderType borderType, const Ipp16s borderValue[3],
                     Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiGradientVectorPrewitt_32f_C3C1R,(const Ipp32f* pSrc, int srcStep,
                     Ipp32f* pGx, int gxStep, Ipp32f* pGy, int gyStep,
                     Ipp32f* pMag, int magStep, Ipp32f* pAngle, int angleStep,
                     IppiSize dstRoiSize, IppiMaskSize maskSize, IppNormType normType,
                     IppiBorderType borderType, const Ipp32f borderValue[3],
                     Ipp8u* pBuffer))


/* /////////////////////////////////////////////////////////////////////////////
// Name:                ippiHOGGetSize
//
// Purpose:             Computes size of HOG spec
//
// Parameters:
//    pConfig           pointer to HOG configure
//    pSpecSize         pointer to the size of HOG spec
//
// Return status:
//    ippStsNoErr          Indicates no error
//    ippStsNullPtrErr     Indicates an error when pConfig or pSpecSize is NULL
//    ippStsSizeErr        Indicates an error in HOG configure:
//                         size of detection window has any field with zero or negative value
//    ippStsNotSupportedModeErr Indicates an error in HOG configure:
//                         - 2>cellSize or cellSize>IPP_HOG_MAX_CELL
//                         - cellSize>blockSize or blockSize>IPP_HOG_MAX_BLOCK
//                         - blockSize is not multiple cellSize
//                         - block has not 2x2 cell geomentry
//                         - blockStride is not multiple cellSize
//                         - detection window size is not multiple blockSize
//                         - 2>nbins or nbins>IPP_HOG_MAX_BINS
//                         - sigma or l2thresh is not positive value
*F*/
IPPAPI(IppStatus, ippiHOGGetSize,(const IppiHOGConfig* pConfig, int* pHOGSpecSize))

/* /////////////////////////////////////////////////////////////////////////////
// Name:                ippiHOGInit
//
// Purpose:             Initialize the HOG spec for future use
//
// Parameters:
//    pConfig           pointer to HOG configure
//    pHOGSpec          pointer to the HOG spec
//
// Return status:
//    ippStsNoErr          Indicates no error
//    ippStsNullPtrErr     Indicates an error when pConfig or pHOGSpec is NULL
//
//    ippStsSizeErr        Indicates an error when size of detection window
//                         defined in pConfig is not match to other
//                         (blockSize and blockStride) geometric parameters
//    ippStsNotSupportedModeErr Indicates an error in HOG configure:
//                         - 2>cellSize or cellSize>IPP_HOG_MAX_CELL
//                         - cellSize>blockSize or blockSize>IPP_HOG_MAX_BLOCK
//                         - blockSize is not multiple cellSize
//                         - block has not 2x2 cell geomentry
//                         - blockStride is not multiple cellSize
//                         - 2>nbins or nbins>IPP_HOG_MAX_BINS
//                         - sigma or l2thresh is not positive value
*F*/
IPPAPI(IppStatus, ippiHOGInit,(const IppiHOGConfig* pConfig, IppiHOGSpec* pHOGSpec))

/* /////////////////////////////////////////////////////////////////////////////
// Name:                ippiHOGGetBufferSize
//
// Purpose:             Computes size of work buffer
//
// Parameters:
//    pHOGSpec          pointer to the HOG spec
//    roiSize           max size of input ROI (pixels)
//    pBufferSize       pointer to the size of work buffer (in bytes)
//
// Return status:
//    ippStsNoErr          Indicates no error
//    ippStsNullPtrErr     Indicates an error when pHOGSpec or pBufferSizeis is NULL
//    ippStsContextMatchErr Indicates an error when undefined pHOGSpec
//    ippStsSizeErr        Indicates an error if roiSize has any field is less then pConfig->winSize
*F*/
IPPAPI(IppStatus, ippiHOGGetBufferSize,(const IppiHOGSpec* pHOGSpec, IppiSize roiSize, int* pBufferSize))

/* /////////////////////////////////////////////////////////////////////////////
// Name:                ippiHOGGetDescriptorSize
//
// Purpose:             Computes size of HOG descriptor
//
// Parameters:
//    pHOGSpec             pointer to the HOG spec
//    pWinDescriptorSize   pointer to the size of HOG descriptor (in bytes)
//                         per each detection window
//
// Return status:
//    ippStsNoErr          Indicates no error
//    ippStsNullPtrErr     Indicates an error when pHOGSpec or pDescriptorSize is NULL
//    ippStsContextMatchErr Indicates an error when undefined pHOGSpec
*F*/
IPPAPI(IppStatus, ippiHOGGetDescriptorSize,(const IppiHOGSpec* pHOGSpec, int* pWinDescriptorSize))

/* /////////////////////////////////////////////////////////////////////////////
// Name:                ippiHOG
//
// Purpose:             Computes HOG descriptor
//
// Parameters:
//    pSrc              pointer to the input detection window
//    roiSize           size of detection window
//    srcStep           input image step
//    pLocation         array of locations of interest (LOI) (detection window position)
//    nLocations        number of LOI
//    pDst              pointer to the HOG descriptor
//    pHOGSpec          pointer to the HOG spec
//    borderID          border type specifier
//    borderValue       border constant value
//    pBuffer           pointer to the work buffer
//
// Return status:
//    ippStsNoErr          Indicates no error
//    ippStsNullPtrErr     Indicates an error when pHOGSpec, pSrc, or pDst is NULL
//    ippStsContextMatchErr Indicates an error when undefined pHOGSpec
//    ippStsStepErr        Indicates an error is input image step isn't positive
//    ippStsNotEvenStepErr Indicates an error when srcStep is not multiple input data type
//    ippStsSizeErr        Indicates an error if roiSize isn't matchs to HOG context
//    ippStsBorderErr      Indicates an error when borderID is not
//                         ippBorderInMem, ippBorderRepl or ippBorderConst
//                         (or derivative from)
*F*/
IPPAPI(IppStatus, ippiHOG_8u32f_C1R,(const Ipp8u* pSrc, int srcStep, IppiSize roiSize,
                                     const IppiPoint* pLocation, int nLocations,
                                     Ipp32f* pDst,
                                     const IppiHOGSpec* pHOGSpec,
                                     IppiBorderType borderID, Ipp8u borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiHOG_16u32f_C1R,(const Ipp16u* pSrc, int srcStep, IppiSize roiSize,
                                      const IppiPoint* pLocation, int nLocations,
                                      Ipp32f* pDst,
                                      const IppiHOGSpec* pHOGSpec,
                                      IppiBorderType borderID, Ipp16u borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiHOG_16s32f_C1R,(const Ipp16s* pSrc, int srcStep, IppiSize roiSize,
                                      const IppiPoint* pLocation, int nLocations,
                                      Ipp32f* pDst,
                                      const IppiHOGSpec* pHOGSpec,
                                      IppiBorderType borderID, Ipp16s borderValue, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiHOG_32f_C1R,(const Ipp32f* pSrc, int srcStep, IppiSize roiSize,
                                   const IppiPoint* pLocation, int nLocations,
                                   Ipp32f* pDst,
                                   const IppiHOGSpec* pHOGSpec,
                                   IppiBorderType borderID, Ipp32f borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiHOG_8u32f_C3R,(const Ipp8u* pSrc, int srcStep, IppiSize roiSize,
                                     const IppiPoint* pLocation, int nLocations,
                                     Ipp32f* pDst,
                                     const IppiHOGSpec* pHOGCtx,
                                     IppiBorderType borderID, Ipp8u borderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiHOG_16u32f_C3R,(const Ipp16u* pSrc, int srcStep, IppiSize roiSize,
                                      const IppiPoint* pLocation, int nLocations,
                                      Ipp32f* pDst,
                                      const IppiHOGSpec* pHOGCtx,
                                      IppiBorderType borderID, Ipp16u borderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiHOG_16s32f_C3R,(const Ipp16s* pSrc, int srcStep, IppiSize roiSize,
                                      const IppiPoint* pLocation, int nLocations,
                                      Ipp32f* pDst,
                                      const IppiHOGSpec* pHOGCtx,
                                      IppiBorderType borderID, Ipp16s borderValue[3], Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiHOG_32f_C3R,(const Ipp32f* pSrc, int srcStep, IppiSize roiSize,
                                   const IppiPoint* pLocation, int nLocations,
                                   Ipp32f* pDst,
                                   const IppiHOGSpec* pHOGCtx,
                                   IppiBorderType borderID, Ipp32f borderValue[3], Ipp8u* pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//           3D Geometric Transform Functions
//////////////////////////////////////////////////////////////////////////////// */

/*
//  Name:               ipprResizeGetBufSize
//  Purpose:            Computes the size of an external work buffer (in bytes)
//  Parameters:
//    srcVOI            region of interest of source volume
//    dstVOI            region of interest of destination volume
//    nChannel          number of channels
//    interpolation     type of interpolation to perform for resizing the input volume:
//                        IPPI_INTER_NN      nearest neighbor interpolation
//                        IPPI_INTER_LINEAR  trilinear interpolation
//                        IPPI_INTER_CUBIC   tricubic polynomial interpolation
//                      including two-parameter cubic filters:
//                        IPPI_INTER_CUBIC2P_BSPLINE      B-spline filter (1, 0)
//                        IPPI_INTER_CUBIC2P_CATMULLROM   Catmull-Rom filter (0, 1/2)
//                        IPPI_INTER_CUBIC2P_B05C03       special filter with parameters (1/2, 3/10)
//    pSize             pointer to the external buffer`s size
//  Returns:
//    ippStsNoErr             no errors
//    ippStsNullPtrErr        pSize == NULL
//    ippStsSizeErr           width or height or depth of volumes is less or equal zero
//    ippStsNumChannelsErr    number of channels is not one
//    ippStsInterpolationErr  (interpolation != IPPI_INTER_NN) &&
//                            (interpolation != IPPI_INTER_LINEAR) &&
//                            (interpolation != IPPI_INTER_CUBIC) &&
//                            (interpolation != IPPI_INTER_CUBIC2P_BSPLINE) &&
//                            (interpolation != IPPI_INTER_CUBIC2P_CATMULLROM) &&
//                            (interpolation != IPPI_INTER_CUBIC2P_B05C03)
*/

IPPAPI(IppStatus, ipprResizeGetBufSize, (
    IpprCuboid srcVOI, IpprCuboid dstVOI, int nChannel, int interpolation, int* pSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ipprGetResizeCuboid
//  Purpose:            Computes coordinates of the destination volume
//  Parameters:
//    srcVOI            volume of interest of source volume
//    pDstCuboid        resultant cuboid
//    xFactor           they specify fraction of resizing in X direction
//    yFactor           they specify fraction of resizing in Y direction
//    zFactor           they specify fraction of resizing in Z direction
//    xShift            they specify shifts of resizing in X direction
//    yShift            they specify shifts of resizing in Y direction
//    zShift            they specify shifts of resizing in Z direction
//    interpolation     type of interpolation
//  Returns:
//    ippStsNoErr             no errors
//    ippStsSizeErr           width or height or depth of srcVOI is less or equal zero
//    ippStsResizeFactorErr   xFactor or yFactor or zFactor is less or equal zero
//    ippStsInterpolationErr  interpolation has an illegal value
//    ippStsNullPtrErr        pDstCuboid == NULL
*/

IPPAPI(IppStatus, ipprGetResizeCuboid, (
    IpprCuboid srcVOI, IpprCuboid* pDstCuboid,
    double xFactor, double yFactor, double zFactor,
    double xShift, double yShift, double zShift, int interpolation))

/*
//  Name:               ipprResize_<mode>
//  Purpose:            Performs RESIZE transform of the source volume
//                      by xFactor, yFactor, zFactor and xShift, yShift, zShift
//                            |X'|   |xFactor    0       0   |   |X|   |xShift|
//                            |Y'| = |        yFactor    0   | * |Y| + |yShift|
//                            |Z'|   |   0       0    zFactor|   |Z|   |zShift|
//  Parameters:
//    pSrc              pointer to source volume data (8u_C1V, 16u_C1V, 32f_C1V modes)
//                      or array of pointers to planes in source volume data
//    srcVolume         size of source volume
//    srcStep           step in every plane of source volume
//    srcPlaneStep      step between planes of source volume (8u_C1V, 16u_C1V, 32f_C1V modes)
//    srcVOI            volume of interest of source volume
//    pDst              pointer to destination volume data (8u_C1V and 16u_C1V modes)
//                      or array of pointers to planes in destination volume data
//    dstStep           step in every plane of destination volume
//    dstPlaneStep      step between planes of destination volume (8u_C1V, 16u_C1V, 32f_C1V modes)
//    dstVOI            volume of interest of destination volume
//    xFactor           they specify fraction of resizing in X direction
//    yFactor           they specify fraction of resizing in Y direction
//    zFactor           they specify fraction of resizing in Z direction
//    xShift            they specify shifts of resizing in X direction
//    yShift            they specify shifts of resizing in Y direction
//    zShift            they specify shifts of resizing in Z direction
//    interpolation     type of interpolation to perform for resizing the input volume:
//                        IPPI_INTER_NN      nearest neighbor interpolation
//                        IPPI_INTER_LINEAR  trilinear interpolation
//                        IPPI_INTER_CUBIC   tricubic polynomial interpolation
//                      including two-parameter cubic filters:
//                        IPPI_INTER_CUBIC2P_BSPLINE      B-spline filter (1, 0)
//                        IPPI_INTER_CUBIC2P_CATMULLROM   Catmull-Rom filter (0, 1/2)
//                        IPPI_INTER_CUBIC2P_B05C03       special filter with parameters (1/2, 3/10)
//    pBuffer           pointer to work buffer
//  Returns:
//    ippStsNoErr             no errors
//    ippStsNullPtrErr        pSrc == NULL or pDst == NULL or pBuffer == NULL
//    ippStsSizeErr           width or height or depth of volumes is less or equal zero
//    ippStsWrongIntersectVOI VOI hasn't an intersection with the source or destination volume
//    ippStsResizeFactorErr   xFactor or yFactor or zFactor is less or equal zero
//    ippStsInterpolationErr  (interpolation != IPPI_INTER_NN) &&
//                            (interpolation != IPPI_INTER_LINEAR) &&
//                            (interpolation != IPPI_INTER_CUBIC) &&
//                            (interpolation != IPPI_INTER_CUBIC2P_BSPLINE) &&
//                            (interpolation != IPPI_INTER_CUBIC2P_CATMULLROM) &&
//                            (interpolation != IPPI_INTER_CUBIC2P_B05C03)
//  Notes:
//    <mode> are 8u_C1V or 16u_C1V or 32f_C1V or 8u_C1PV or 16u_C1PV or 32f_C1PV
*/

IPPAPI(IppStatus, ipprResize_8u_C1V, (
    const Ipp8u* pSrc, IpprVolume srcVolume, int srcStep, int srcPlaneStep, IpprCuboid srcVOI,
    Ipp8u* pDst, int dstStep, int dstPlaneStep, IpprCuboid dstVOI,
    double xFactor, double yFactor, double zFactor, double xShift, double yShift, double zShift,
    int interpolation, Ipp8u* pBuffer))

IPPAPI(IppStatus, ipprResize_16u_C1V, (
    const Ipp16u* pSrc, IpprVolume srcVolume, int srcStep, int srcPlaneStep, IpprCuboid srcVOI,
    Ipp16u* pDst, int dstStep, int dstPlaneStep, IpprCuboid dstVOI,
    double xFactor, double yFactor, double zFactor, double xShift, double yShift, double zShift,
    int interpolation, Ipp8u* pBuffer))

IPPAPI(IppStatus, ipprResize_32f_C1V, (
    const Ipp32f* pSrc, IpprVolume srcVolume, int srcStep, int srcPlaneStep, IpprCuboid srcVOI,
    Ipp32f* pDst, int dstStep, int dstPlaneStep, IpprCuboid dstVOI,
    double xFactor, double yFactor, double zFactor, double xShift, double yShift, double zShift,
    int interpolation, Ipp8u* pBuffer))

IPPAPI(IppStatus, ipprResize_8u_C1PV, (
    const Ipp8u* const pSrc[], IpprVolume srcVolume, int srcStep, IpprCuboid srcVOI,
    Ipp8u* const pDst[], int dstStep, IpprCuboid dstVOI,
    double xFactor, double yFactor, double zFactor, double xShift, double yShift, double zShift,
    int interpolation, Ipp8u* pBuffer))

IPPAPI(IppStatus, ipprResize_16u_C1PV, (
    const Ipp16u* const pSrc[], IpprVolume srcVolume, int srcStep, IpprCuboid srcVOI,
    Ipp16u* const pDst[], int dstStep, IpprCuboid dstVOI,
    double xFactor, double yFactor, double zFactor, double xShift, double yShift, double zShift,
    int interpolation, Ipp8u* pBuffer))

IPPAPI(IppStatus, ipprResize_32f_C1PV, (
    const Ipp32f* const pSrc[], IpprVolume srcVolume, int srcStep, IpprCuboid srcVOI,
    Ipp32f* const pDst[], int dstStep, IpprCuboid dstVOI,
    double xFactor, double yFactor, double zFactor, double xShift, double yShift, double zShift,
    int interpolation, Ipp8u* pBuffer))


/*
//  Name:               ipprWarpAffineGetBufSize
//  Purpose:            Computes the size of an external work buffer (in bytes)
//  Parameters:
//    srcVolume         size of source volume
//    srcVOI            region of interest of source volume
//    dstVOI            region of interest of destination volume
//    coeffs            affine transform matrix
//    nChannel          number of channels
//    interpolation     type of interpolation to perform for resizing the input volume:
//                        IPPI_INTER_NN      nearest neighbor interpolation
//                        IPPI_INTER_LINEAR  trilinear interpolation
//                        IPPI_INTER_CUBIC   tricubic polynomial interpolation
//                      including two-parameter cubic filters:
//                        IPPI_INTER_CUBIC2P_BSPLINE      B-spline filter (1, 0)
//                        IPPI_INTER_CUBIC2P_CATMULLROM   Catmull-Rom filter (0, 1/2)
//                        IPPI_INTER_CUBIC2P_B05C03       special filter with parameters (1/2, 3/10)
//    pSize             pointer to the external buffer`s size
//  Returns:
//    ippStsNoErr             no errors
//    ippStsNullPtrErr        pSize == NULL or coeffs == NULL
//    ippStsSizeErr           size of source or destination volumes is less or equal zero
//    ippStsNumChannelsErr    number of channels is not one
//    ippStsInterpolationErr  (interpolation != IPPI_INTER_NN) &&
//                            (interpolation != IPPI_INTER_LINEAR) &&
//                            (interpolation != IPPI_INTER_CUBIC) &&
//                            (interpolation != IPPI_INTER_CUBIC2P_BSPLINE) &&
//                            (interpolation != IPPI_INTER_CUBIC2P_CATMULLROM) &&
//                            (interpolation != IPPI_INTER_CUBIC2P_B05C03)
*/

IPPAPI(IppStatus, ipprWarpAffineGetBufSize, (
    IpprVolume srcVolume, IpprCuboid srcVOI, IpprCuboid dstVOI, const double coeffs[3][4],
    int nChannel, int interpolation, int* pSize))

/*
//  Names:              ipprWarpAffine_<mode>
//  Purpose:            Performs AFFINE transform of the source volume by matrix a[3][4]
//                            |X'|   |a00 a01 a02|   |X|   |a03|
//                            |Y'| = |a10 a11 a12| * |Y| + |a13|
//                            |Z'|   |a20 a21 a22|   |Z|   |a23|
//  Parameters:
//    pSrc              array of pointers to planes in source volume data
//    srcVolume         size of source volume
//    srcStep           step in every plane of source volume
//    srcVOI            volume of interest of source volume
//    pDst              array of pointers to planes in destination volume data
//    dstStep           step in every plane of destination volume
//    dstVOI            volume of interest of destination volume
//    coeffs            affine transform matrix
//    interpolation     type of interpolation to perform for affine transform the input volume:
//                        IPPI_INTER_NN      nearest neighbor interpolation
//                        IPPI_INTER_LINEAR  trilinear interpolation
//                        IPPI_INTER_CUBIC   tricubic polynomial interpolation
//                      including two-parameter cubic filters:
//                        IPPI_INTER_CUBIC2P_BSPLINE      B-spline filter (1, 0)
//                        IPPI_INTER_CUBIC2P_CATMULLROM   Catmull-Rom filter (0, 1/2)
//                        IPPI_INTER_CUBIC2P_B05C03       special filter with parameters (1/2, 3/10)
//    pBuffer           pointer to work buffer
//  Returns:
//    ippStsNoErr             no errors
//    ippStsNullPtrErr        pSrc == NULL or pDst == NULL or pBuffer == NULL or coeffs == NULL
//    ippStsSizeErr           width or height or depth of source volume is less or equal zero
//    ippStsWrongIntersectVOI VOI hasn't an intersection with the source or destination volume
//    ippStsCoeffErr          determinant of the transform matrix Aij is equal to zero
//    ippStsInterpolationErr  interpolation has an illegal value
//  Notes:
//    <mode> are 8u_C1PV or 16u_C1PV or 32f_C1PV
*/

IPPAPI(IppStatus, ipprWarpAffine_8u_C1PV, (
    const Ipp8u* const pSrc[], IpprVolume srcVolume, int srcStep, IpprCuboid srcVOI,
    Ipp8u* const pDst[], int dstStep, IpprCuboid dstVOI,
    const double coeffs[3][4], int interpolation, Ipp8u* pBuffer))

IPPAPI(IppStatus, ipprWarpAffine_16u_C1PV, (
    const Ipp16u* const pSrc[], IpprVolume srcVolume, int srcStep, IpprCuboid srcVOI,
    Ipp16u* const pDst[], int dstStep, IpprCuboid dstVOI,
    const double coeffs[3][4], int interpolation, Ipp8u* pBuffer))

IPPAPI(IppStatus, ipprWarpAffine_32f_C1PV, (
    const Ipp32f* const pSrc[], IpprVolume srcVolume, int srcStep, IpprCuboid srcVOI,
    Ipp32f* const pDst[], int dstStep, IpprCuboid dstVOI,
    const double coeffs[3][4], int interpolation, Ipp8u* pBuffer))
/*
//  Names:              ipprWarpAffine_<mode>
//  Purpose:            Performs AFFINE transform of the source volume by matrix a[3][4]
//                            |X'|   |a00 a01 a02|   |X|   |a03|
//                            |Y'| = |a10 a11 a12| * |Y| + |a13|
//                            |Z'|   |a20 a21 a22|   |Z|   |a23|
//  Parameters:
//    pSrc              array of pointers to planes in source volume data
//    srcVolume         size of source volume
//    srcStep           step in every plane of source volume
//    srcPlaneStep      step between planes of source volume (8u_C1V, 16u_C1V, 32f_C1V modes)
//    srcVOI            volume of interest of source volume
//    pDst              array of pointers to planes in destination volume data
//    dstStep           step in every plane of destination volume
//    dstPlaneStep      step between planes of destination volume (8u_C1V, 16u_C1V, 32f_C1V modes)
//    dstVOI            volume of interest of destination volume
//    coeffs            affine transform matrix
//    interpolation     type of interpolation to perform for affine transform the input volume:
//                        IPPI_INTER_NN      nearest neighbor interpolation
//                        IPPI_INTER_LINEAR  trilinear interpolation
//                        IPPI_INTER_CUBIC   tricubic polynomial interpolation
//                      including two-parameter cubic filters:
//                        IPPI_INTER_CUBIC2P_BSPLINE      B-spline filter (1, 0)
//                        IPPI_INTER_CUBIC2P_CATMULLROM   Catmull-Rom filter (0, 1/2)
//                        IPPI_INTER_CUBIC2P_B05C03       special filter with parameters (1/2, 3/10)
//    pBuffer           pointer to work buffer
//  Returns:
//    ippStsNoErr             no errors
//    ippStsNullPtrErr        pSrc == NULL or pDst == NULL or pBuffer == NULL or coeffs == NULL
//    ippStsSizeErr           width or height or depth of source volume is less or equal zero
//    ippStsWrongIntersectVOI VOI hasn't an intersection with the source or destination volume
//    ippStsCoeffErr          determinant of the transform matrix Aij is equal to zero
//    ippStsInterpolationErr  interpolation has an illegal value
//  Notes:
//    <mode> are 8u_C1V or 16u_C1V or 32f_C1V
*/

IPPAPI(IppStatus, ipprWarpAffine_8u_C1V, (
    const Ipp8u* pSrc, IpprVolume srcVolume, int srcStep, int srcPlaneStep, IpprCuboid srcVOI,
    Ipp8u* pDst, int dstStep, int dstPlaneStep, IpprCuboid dstVOI,
    const double coeffs[3][4], int interpolation, Ipp8u* pBuffer))
IPPAPI(IppStatus, ipprWarpAffine_16u_C1V, (
    const Ipp16u* pSrc, IpprVolume srcVolume, int srcStep, int srcPlaneStep, IpprCuboid srcVOI,
    Ipp16u* pDst, int dstStep, int dstPlaneStep, IpprCuboid dstVOI,
    const double coeffs[3][4], int interpolation, Ipp8u* pBuffer))

IPPAPI(IppStatus, ipprWarpAffine_32f_C1V, (
    const Ipp32f* pSrc, IpprVolume srcVolume, int srcStep, int srcPlaneStep, IpprCuboid srcVOI,
    Ipp32f* pDst, int dstStep, int dstPlaneStep, IpprCuboid dstVOI,
    const double coeffs[3][4], int interpolation, Ipp8u* pBuffer))

/*
//  Names:              ipprRemap_<mode>
//  Purpose:            Performs REMAP TRANSFORM of the source volume by remapping
//                        dst[i,j,k] = src[xMap[i,j,k], yMap[i,j,k], zMap[i,j,k]]
//  Parameters:
//    pSrc              array of pointers to planes in source volume data
//    srcVolume         size of source volume
//    srcStep           step in every plane of source volume
//    srcVOI            volume of interest of source volume
//    pxMap             array of pointers to images with X coordinates of map
//    pyMap             array of pointers to images with Y coordinates of map
//    pzMap             array of pointers to images with Z coordinates of map
//    mapStep           step in every plane of each map volumes
//    pDst              array of pointers to planes in destination volume data
//    dstStep           step in every plane of destination volume
//    dstVolume         size of destination volume
//    interpolation     type of interpolation to perform for resizing the input volume:
//                        IPPI_INTER_NN      nearest neighbor interpolation
//                        IPPI_INTER_LINEAR  trilinear interpolation
//                        IPPI_INTER_CUBIC   tricubic polynomial interpolation
//                      including two-parameter cubic filters:
//                        IPPI_INTER_CUBIC2P_BSPLINE    B-spline filter (1, 0)
//                        IPPI_INTER_CUBIC2P_CATMULLROM Catmull-Rom filter (0, 1/2)
//                        IPPI_INTER_CUBIC2P_B05C03     special filter with parameters (1/2, 3/10)
//  Returns:
//    ippStsNoErr             no errors
//    ippStsNullPtrErr        pSrc == NULL or pDst == NULL or
//                            pxMap == NULL or pyMap == NULL or pzMap == NULL
//    ippStsSizeErr           width or height or depth of volumes is less or equal zero
//    ippStsInterpolationErr  interpolation has an illegal value
//    ippStsWrongIntersectVOI srcVOI hasn't intersection with the source volume, no operation
//  Notes:
//    <mode> are 8u_C1PV or 16u_C1PV or 32f_C1PV
*/

IPPAPI(IppStatus, ipprRemap_8u_C1PV, (
    const Ipp8u* const pSrc[], IpprVolume srcVolume, int srcStep, IpprCuboid srcVOI,
    const Ipp32f* const pxMap[], const Ipp32f* const pyMap[], const Ipp32f* const pzMap[], int mapStep,
    Ipp8u* const pDst[], int dstStep, IpprVolume dstVolume, int interpolation))

IPPAPI(IppStatus, ipprRemap_16u_C1PV, (
    const Ipp16u* const pSrc[], IpprVolume srcVolume, int srcStep, IpprCuboid srcVOI,
    const Ipp32f* const pxMap[], const Ipp32f* const pyMap[], const Ipp32f* const pzMap[], int mapStep,
    Ipp16u* const pDst[], int dstStep, IpprVolume dstVolume, int interpolation))

IPPAPI(IppStatus, ipprRemap_32f_C1PV, (
    const Ipp32f* const pSrc[], IpprVolume srcVolume, int srcStep, IpprCuboid srcVOI,
    const Ipp32f* const pxMap[], const Ipp32f* const pyMap[], const Ipp32f* const pzMap[], int mapStep,
    Ipp32f* const pDst[], int dstStep, IpprVolume dstVolume, int interpolation))
/*
//  Names:              ipprRemap_<mode>
//  Purpose:            Performs REMAP TRANSFORM of the source volume by remapping
//                        dst[i,j,k] = src[xMap[i,j,k], yMap[i,j,k], zMap[i,j,k]]
//  Parameters:
//    pSrc              array of pointers to planes in source volume data
//    srcVolume         size of source volume
//    srcStep           step in every plane of source volume
//    srcPlaneStep      step between planes of source volume (8u_C1V, 16u_C1V, 32f_C1V modes)
//    srcVOI            volume of interest of source volume
//    pxMap             array of pointers to images with X coordinates of map
//    pyMap             array of pointers to images with Y coordinates of map
//    pzMap             array of pointers to images with Z coordinates of map
//    mapStep           step in every plane of each map volumes
//    pDst              array of pointers to planes in destination volume data
//    dstStep           step in every plane of destination volume
//    dstPlaneStep      step between planes of destination volume (8u_C1V, 16u_C1V, 32f_C1V modes)
//    dstVolume         size of destination volume
//    interpolation     type of interpolation to perform for resizing the input volume:
//                        IPPI_INTER_NN      nearest neighbor interpolation
//                        IPPI_INTER_LINEAR  trilinear interpolation
//                        IPPI_INTER_CUBIC   tricubic polynomial interpolation
//                      including two-parameter cubic filters:
//                        IPPI_INTER_CUBIC2P_BSPLINE    B-spline filter (1, 0)
//                        IPPI_INTER_CUBIC2P_CATMULLROM Catmull-Rom filter (0, 1/2)
//                        IPPI_INTER_CUBIC2P_B05C03     special filter with parameters (1/2, 3/10)
//  Returns:
//    ippStsNoErr             no errors
//    ippStsNullPtrErr        pSrc == NULL or pDst == NULL or
//                            pxMap == NULL or pyMap == NULL or pzMap == NULL
//    ippStsSizeErr           width or height or depth of volumes is less or equal zero
//    ippStsInterpolationErr  interpolation has an illegal value
//    ippStsWrongIntersectVOI srcVOI hasn't intersection with the source volume, no operation
//  Notes:
//    <mode> are 8u_C1V or 16u_C1V or 32f_C1V
*/

IPPAPI(IppStatus, ipprRemap_8u_C1V, (
    const Ipp8u* pSrc, IpprVolume srcVolume, int srcStep, int srcPlaneStep, IpprCuboid srcVOI,
    const Ipp32f* pxMap, const Ipp32f* pyMap, const Ipp32f* pzMap, int mapStep,int mapPlaneStep,
    Ipp8u* pDst, int dstStep,  int dstPlaneStep,IpprVolume dstVolume, int interpolation))
IPPAPI(IppStatus, ipprRemap_16u_C1V, (
    const Ipp16u* pSrc, IpprVolume srcVolume, int srcStep, int srcPlaneStep, IpprCuboid srcVOI,
    const Ipp32f* pxMap, const Ipp32f* pyMap, const Ipp32f* pzMap, int mapStep,int mapPlaneStep,
    Ipp16u* pDst, int dstStep, int dstPlaneStep, IpprVolume dstVolume, int interpolation))
IPPAPI(IppStatus, ipprRemap_32f_C1V, (
    const Ipp32f* pSrc, IpprVolume srcVolume, int srcStep, int srcPlaneStep, IpprCuboid srcVOI,
    const Ipp32f* pxMap, const Ipp32f* pyMap, const Ipp32f* pzMap, int mapStep,int mapPlaneStep,
    Ipp32f* pDst, int dstStep, int dstPlaneStep, IpprVolume dstVolume, int interpolation))

/* /////////////////////////////////////////////////////////////////////////////
//           3D General Linear Filters
//////////////////////////////////////////////////////////////////////////////// */

/*
//  Name:               ipprFilterGetBufSize
//  Purpose:            Computes the size of an external work buffer (in bytes)
//  Parameters:
//    dstVolume         size of the volume
//    kernelVolume      size of the kernel volume
//    nChannel          number of channels
//    pSize             pointer to the external buffer`s size
//  Returns:
//    ippStsNoErr           no errors
//    ippStsNullPtrErr      pSize == NULL
//    ippStsSizeErr         width or height or depth of volumes is less or equal zero
//    ippStsNumChannelsErr  number of channels is not one
*/

IPPAPI(IppStatus, ipprFilterGetBufSize, (
    IpprVolume dstVolume, IpprVolume kernelVolume, int nChannel, int* pSize))

/*
//  Name:               ipprFilter_16s_C1PV
//  Purpose:            Filters a volume using a general integer cuboidal kernel
//  Parameters:
//    pSrc              array of pointers to planes in source volume data
//    srcStep           step in every plane of source volume
//    pDst              array of pointers to planes in destination volume data
//    dstStep           step in every plane of destination volume
//    dstVolume         size of the processed volume
//    pKernel           pointer to the kernel values
//    kernelVolume      size of the kernel volume
//    anchor            anchor 3d-cell specifying the cuboidal kernel alignment
//                      with respect to the position of the input voxel
//    divisor           the integer value by which the computed result is divided
//    pBuffer           pointer to the external buffer`s size
//  Returns:
//    ippStsNoErr       no errors
//    ippStsNullPtrErr  one of the pointers is NULL
//    ippStsSizeErr     width or height or depth of volumes is less or equal zero
//    ippStsDivisorErr  divisor value is zero, function execution is interrupted
*/

IPPAPI(IppStatus, ipprFilter_16s_C1PV, (
    const Ipp16s* const pSrc[], int srcStep,
    const Ipp16s* pDst[], int dstStep, IpprVolume dstVolume,
    const Ipp32s* pKernel, IpprVolume kernelVolume, IpprPoint anchor, int divisor,
    Ipp8u* pBuffer))
/*
//  Name:               ipprFilter_16s_C1V
//  Purpose:            Filters a volume using a general integer cuboidal kernel
//  Parameters:
//    pSrc              array of pointers to planes in source volume data
//    srcStep           step in every plane of source volume
//    srcPlaneStep      step between planes of source volume (8u_C1V, 16u_C1V, 32f_C1V modes)
//    pDst              array of pointers to planes in destination volume data
//    dstStep           step in every plane of destination volume
//    dstPlaneStep      step between planes of destination volume (8u_C1V, 16u_C1V, 32f_C1V modes)
//    dstVolume         size of the processed volume
//    pKernel           pointer to the kernel values
//    kernelVolume      size of the kernel volume
//    anchor            anchor 3d-cell specifying the cuboidal kernel alignment
//                      with respect to the position of the input voxel
//    divisor           the integer value by which the computed result is divided
//    pBuffer           pointer to the external buffer`s size
//  Returns:
//    ippStsNoErr       no errors
//    ippStsNullPtrErr  one of the pointers is NULL
//    ippStsSizeErr     width or height or depth of volumes is less or equal zero
//    ippStsDivisorErr  divisor value is zero, function execution is interrupted
*/
IPPAPI(IppStatus, ipprFilter_16s_C1V, (
    const Ipp16s* pSrc, int srcStep, int srcPlaneStep,
    Ipp16s* pDst, int dstStep,int dstPlaneStep, IpprVolume dstVolume,
    const Ipp32s* pKernel, IpprVolume kernelVolume, IpprPoint anchor, int divisor,
    Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiMulC64f_8u_C1R, (const Ipp8u* pSrc, int srcStep, const Ipp64f value[1], Ipp8u* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint, IppRoundMode rndMode))
IPPAPI(IppStatus, ippiMulC64f_8u_C3R, (const Ipp8u* pSrc, int srcStep, const Ipp64f value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint, IppRoundMode rndMode))
IPPAPI(IppStatus, ippiMulC64f_8u_C4R, (const Ipp8u* pSrc, int srcStep, const Ipp64f value[4], Ipp8u* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint, IppRoundMode rndMode))
IPPAPI(IppStatus, ippiMulC64f_16u_C1R, (const Ipp16u* pSrc, int srcStep, const Ipp64f value[1], Ipp16u* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint, IppRoundMode rndMode))
IPPAPI(IppStatus, ippiMulC64f_16u_C3R, (const Ipp16u* pSrc, int srcStep, const Ipp64f value[3], Ipp16u* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint, IppRoundMode rndMode))
IPPAPI(IppStatus, ippiMulC64f_16u_C4R, (const Ipp16u* pSrc, int srcStep, const Ipp64f value[4], Ipp16u* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint, IppRoundMode rndMode))
IPPAPI(IppStatus, ippiMulC64f_16s_C1R, (const Ipp16s* pSrc, int srcStep, const Ipp64f value[1], Ipp16s* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint, IppRoundMode rndMode))
IPPAPI(IppStatus, ippiMulC64f_16s_C3R, (const Ipp16s* pSrc, int srcStep, const Ipp64f value[3], Ipp16s* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint, IppRoundMode rndMode))
IPPAPI(IppStatus, ippiMulC64f_16s_C4R, (const Ipp16s* pSrc, int srcStep, const Ipp64f value[4], Ipp16s* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint, IppRoundMode rndMode))
IPPAPI(IppStatus, ippiMulC64f_32f_C1R, (const Ipp32f* pSrc, int srcStep, const Ipp64f value[1], Ipp32f* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint, IppRoundMode rndMode))
IPPAPI(IppStatus, ippiMulC64f_32f_C3R, (const Ipp32f* pSrc, int srcStep, const Ipp64f value[3], Ipp32f* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint, IppRoundMode rndMode))
IPPAPI(IppStatus, ippiMulC64f_32f_C4R, (const Ipp32f* pSrc, int srcStep, const Ipp64f value[4], Ipp32f* pDst, int dstStep, IppiSize roiSize, IppHintAlgorithm hint, IppRoundMode rndMode))

IPPAPI(IppStatus, ippiMulC64f_8u_C1IR, (Ipp8u* pSrcDst, int srcDstStep, const Ipp64f value[1], IppiSize roiSize, IppHintAlgorithm hint, IppRoundMode rndMode))
IPPAPI(IppStatus, ippiMulC64f_8u_C3IR, (Ipp8u* pSrcDst, int srcDstStep, const Ipp64f value[3], IppiSize roiSize, IppHintAlgorithm hint, IppRoundMode rndMode))
IPPAPI(IppStatus, ippiMulC64f_8u_C4IR, (Ipp8u* pSrcDst, int srcDstStep, const Ipp64f value[4], IppiSize roiSize, IppHintAlgorithm hint, IppRoundMode rndMode))
IPPAPI(IppStatus, ippiMulC64f_16u_C1IR, (Ipp16u* pSrcDst, int srcDstStep, const Ipp64f value[1], IppiSize roiSize, IppHintAlgorithm hint, IppRoundMode rndMode))
IPPAPI(IppStatus, ippiMulC64f_16u_C3IR, (Ipp16u* pSrcDst, int srcDstStep, const Ipp64f value[3], IppiSize roiSize, IppHintAlgorithm hint, IppRoundMode rndMode))
IPPAPI(IppStatus, ippiMulC64f_16u_C4IR, (Ipp16u* pSrcDst, int srcDstStep, const Ipp64f value[4], IppiSize roiSize, IppHintAlgorithm hint, IppRoundMode rndMode))
IPPAPI(IppStatus, ippiMulC64f_16s_C1IR, (Ipp16s* pSrcDst, int srcDstStep, const Ipp64f value[1], IppiSize roiSize, IppHintAlgorithm hint, IppRoundMode rndMode))
IPPAPI(IppStatus, ippiMulC64f_16s_C3IR, (Ipp16s* pSrcDst, int srcDstStep, const Ipp64f value[3], IppiSize roiSize, IppHintAlgorithm hint, IppRoundMode rndMode))
IPPAPI(IppStatus, ippiMulC64f_16s_C4IR, (Ipp16s* pSrcDst, int srcDstStep, const Ipp64f value[4], IppiSize roiSize, IppHintAlgorithm hint, IppRoundMode rndMode))
IPPAPI(IppStatus, ippiMulC64f_32f_C1IR, (Ipp32f* pSrcDst, int srcDstStep, const Ipp64f value[1], IppiSize roiSize, IppHintAlgorithm hint, IppRoundMode rndMode))
IPPAPI(IppStatus, ippiMulC64f_32f_C3IR, (Ipp32f* pSrcDst, int srcDstStep, const Ipp64f value[3], IppiSize roiSize, IppHintAlgorithm hint, IppRoundMode rndMode))
IPPAPI(IppStatus, ippiMulC64f_32f_C4IR, (Ipp32f* pSrcDst, int srcDstStep, const Ipp64f value[4], IppiSize roiSize, IppHintAlgorithm hint, IppRoundMode rndMode))

/*****************************************************************************************************
// 3D General filter with border
//  Name:
//   ipprFilterBorderGetSize
//   ipprFilterBorderInit_16s
//   ipprFilterBorderInit_32f
//   ipprFilterBorderInit_64f
//   ipprFilterBorder_8u_C1V
//   ipprFilterBorder_16s_C1V
//   ipprFilterBorder_16u_C1V
//   ipprFilterBorder_32f_C1V
//   ipprFilterBorder_64f_C1V
//  Purpose:    Filters an 3D image using a general integer rectangular kernel volume
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  One of the pointers is NULL
//   ippStsSizeErr     dstRoiSize or kernelSize has a field with zero or negative value
//   ippStsDivisorErr  Divisor value is zero, function execution is interrupted
//
//  Parameters:
//      pSrc        Pointer to 3D source image
//      srcPlaneStep Step in bytes through the 3D source image planes
//      srcStep      Step in bytes through the one source image plane
//      pDst        Pointer to the 3D destination image
//      dstPlaneStep Step in bytes through the 3D destination image planes
//      dstStep     Step in bytes through the one destination image plane
//      dstRoiVolume  Size of the source and destination VOI in pixels
//      pKernel     Pointer to the kernel values
//      kernelVolume  Size of the rectangular kernel in pixels.
//      divisor     The integer value by which the computed result is divided.
//      kernelType  Kernel type {ipp16s|ipp32f|ipp64f}
//      dataType    Data type {ipp8u|ipp16u|ipp16s|ipp32f|ipp64f}
//      numChannels Number of channels, possible values are 1
//      pSpecSize   Pointer to the size (in bytes) of the spec structure
//      pBufferSize    Pointer to the size (in bytes) of the external buffer
//      pSpec       Pointer to pointer to the allocated and initialized context structure
//      borderType  Type of the border
//      borderValue Pointer to the constant value(s) if border type equals ippBorderConstant
//      pBuffer     Pointer to the work buffer. It can be equal to NULL if optimization algorithm doesn't demand a work buffer
*/

IPPAPI(IppStatus, ipprFilterBorderGetSize,  (IpprVolume kernelVolume, IpprVolume dstRoiVolume, IppDataType dataType, IppDataType kernelType, int numChannels, int* pSpecSize, int* pBufferSize))
IPPAPI(IppStatus, ipprFilterBorderInit_16s, (const Ipp16s* pKernel, IpprVolume  kernelVolume, int divisor, IppDataType dataType, int numChannels, IpprFilterBorderSpec* pSpec ))
IPPAPI(IppStatus, ipprFilterBorderInit_32f, (const Ipp32f* pKernel, IpprVolume  kernelVolume,              IppDataType dataType, int numChannels, IpprFilterBorderSpec* pSpec ))
IPPAPI(IppStatus, ipprFilterBorderInit_64f, (const Ipp64f* pKernel, IpprVolume  kernelVolume,              IppDataType dataType, int numChannels, IpprFilterBorderSpec* pSpec ))
IPPAPI(IppStatus, ipprFilterBorder_8u_C1V,  (const Ipp8u*  pSrc, int srcPlaneStep, int srcStep,  Ipp8u*  pDst, int dstPlaneStep, int dstStep,  IpprVolume dstRoiVolume, IpprBorderType borderType, const Ipp8u  borderValue[1], const IpprFilterBorderSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ipprFilterBorder_16s_C1V, (const Ipp16s* pSrc, int srcPlaneStep, int srcStep,  Ipp16s* pDst, int dstPlaneStep, int dstStep,  IpprVolume dstRoiVolume, IpprBorderType borderType, const Ipp16s borderValue[1], const IpprFilterBorderSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ipprFilterBorder_16u_C1V, (const Ipp16u* pSrc, int srcPlaneStep, int srcStep,  Ipp16u* pDst, int dstPlaneStep, int dstStep,  IpprVolume dstRoiVolume, IpprBorderType borderType, const Ipp16u borderValue[1], const IpprFilterBorderSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ipprFilterBorder_32f_C1V, (const Ipp32f* pSrc, int srcPlaneStep, int srcStep,  Ipp32f* pDst, int dstPlaneStep, int dstStep,  IpprVolume dstRoiVolume, IpprBorderType borderType, const Ipp32f borderValue[1], const IpprFilterBorderSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ipprFilterBorder_64f_C1V, (const Ipp64f* pSrc, int srcPlaneStep, int srcStep,  Ipp64f* pDst, int dstPlaneStep, int dstStep,  IpprVolume dstRoiVolume, IpprBorderType borderType, const Ipp64f borderValue[1], const IpprFilterBorderSpec* pSpec, Ipp8u* pBuffer))


/*****************************************************************************************************
// 3D Median filter with border
//  Name:
//  ipprFilterMedianGetSize
//  ipprFilterMedianInit
//  ipprFilterMedian_8u_C1V
//  ipprFilterMedian_16u_C1V
//  ipprFilterMedian_16s_C1V
//  ipprFilterMedian_32f_C1V
//  ipprFilterMedian_64f_C1V
//  Purpose:    Filters an 3D image using median filter and a general integer rectangular kernel volume
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  One of the pointers is NULL
//   ippStsSizeErr     dstRoiVolume or kernelVolume has a field with zero or negative value

//
//  Parameters:
//      pSrc        Pointer to 3D source image
//      srcPlaneStep Step in bytes through the 3D source image planes
//      srcStep      Step in bytes through the one source image plane
//      pDst        Pointer to the 3D destination image
//      dstPlaneStep Step in bytes through the 3D destination image planes
//      dstStep     Step in bytes through the one destination image plane
//      dstRoiVolume  Size of the source and destination VOI in pixels
//      kernelVolume  Size of the rectangular kernel in pixels.
//      dataType    Data type {ipp8u|ipp16u|ipp16s|ipp32f|ipp64f}
//      numChannels Number of channels, possible values are 1
//      pSpecSize   Pointer to the size (in bytes) of the spec structure
//      pBufferSize    Pointer to the size (in bytes) of the external buffer
//      pSpec       Pointer to pointer to the allocated and initialized context structure
//      borderType  Type of the border
//      borderValue Pointer to the constant value(s) if border type equals ippBorderConstant
//      pBuffer     Pointer to the work buffer. It can be equal to NULL if optimization algorithm doesn't demand a work buffer
*/

IPPAPI(IppStatus, ipprFilterMedianGetSize, (IpprVolume maskVolume, IpprVolume dstRoiVolume, IppDataType dataType, int numChannels, int* pSpecSize, int* pBufferSize))
IPPAPI(IppStatus, ipprFilterMedianInit, (IpprVolume  maskVolume, IppDataType dataType, int numChannels, IpprFilterMedianSpec* pSpec))
IPPAPI(IppStatus, ipprFilterMedian_8u_C1V,  (const Ipp8u*  pSrc, int srcPlaneStep, int srcStep, Ipp8u*  pDst, int dstPlaneStep, int dstStep, IpprVolume dstRoiVolume, IpprBorderType borderType, const Ipp8u*  pBorderValue, const IpprFilterMedianSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ipprFilterMedian_16u_C1V, (const Ipp16u* pSrc, int srcPlaneStep, int srcStep, Ipp16u* pDst, int dstPlaneStep, int dstStep, IpprVolume dstRoiVolume, IpprBorderType borderType, const Ipp16u* pBorderValue, const IpprFilterMedianSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ipprFilterMedian_16s_C1V, (const Ipp16s* pSrc, int srcPlaneStep, int srcStep, Ipp16s* pDst, int dstPlaneStep, int dstStep, IpprVolume dstRoiVolume, IpprBorderType borderType, const Ipp16s* pBorderValue, const IpprFilterMedianSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ipprFilterMedian_32f_C1V, (const Ipp32f* pSrc, int srcPlaneStep, int srcStep, Ipp32f* pDst, int dstPlaneStep, int dstStep, IpprVolume dstRoiVolume, IpprBorderType borderType, const Ipp32f* pBorderValue, const IpprFilterMedianSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ipprFilterMedian_64f_C1V, (const Ipp64f* pSrc, int srcPlaneStep, int srcStep, Ipp64f* pDst, int dstPlaneStep, int dstStep, IpprVolume dstRoiVolume, IpprBorderType borderType, const Ipp64f* pBorderValue, const IpprFilterMedianSpec* pSpec, Ipp8u* pBuffer))
/* /////////////////////////////////////////////////////////////////////////////
//                     Bilateral filter functions with Border and square mask
// /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFilterBilateralGetBufferSize
//  Purpose:    to define buffer size for bilateral filter
//  Name:       ippiFilterBilateralInit
//  Purpose:    initialization of Spec for bilateral filter with border
//  Name:
                ippiFilterBilateral_8u_C1R
                ippiFilterBilateral_8u_C3R
                ippiFilterBilateral_32f_C1R
                ippiFilterBilateral_32f_C3R
                ippiFilterBilateral_64f_C1R
                ippiFilterBilateral_64f_C3R
                ippiFilterBilateral_8u_P3R
                ippiFilterBilateral_32f_P3R
                ippiFilterBilateral_64f_P3R
//  Purpose:    perform bilateral filter with border

//  Parameters:
//   filter            Type of bilateral filter. Possible value is ippiFilterBilateralGauss.
//   dstRoiSize        Roi size (in pixels) of destination image what will be applied
//                     for processing.
//   kernelWidthHeight Kernel width and height neighborhood what defines pixels for calculation.
//   dataType          Data type of the source and desination images. Possible values
//                     are ipp8u and ipp32f.
//   numChannels       Number of channels in the images. Possible values are 1 and 3.
//   distMethod        The type of method for definition of distance beetween pixel untensity.
//                     Possible value is ippDistNormL1 for C1 and ippDistNormL1/ippDistNormL2 for C3
//   pSpecSize         Pointer to the size (in bytes) of the spec.
//   pBufferSize       Pointer to the size (in bytes) of the external work buffer.
//  Return:
//    ippStsNoErr               OK
//    ippStsNullPtrErr          any pointer is NULL
//    ippStsSizeErr             size of dstRoiSize is less or equal 0
//    ippStsMaskSizeErr         kernelWidthHeight is less or equal 0
//    ippStsNotSupportedModeErr filter or distMethod is not supported
//    ippStsDataTypeErr         Indicates an error when dataType has an illegal value.
//    ippStsNumChannelsErr      Indicates an error when numChannels has an illegal value.
*/
IPPAPI(IppStatus, ippiFilterBilateralGetBufferSize, (IppiFilterBilateralType filter, IppiSize dstRoiSize, int kernelWidthHeight, IppDataType dataType, int numChannels, IppiDistanceMethodType distMethodType, int *pSpecSize, int *pBufferSize))
IPPAPI(IppStatus, ippiFilterBilateralInit, (IppiFilterBilateralType filter, IppiSize dstRoiSize, int kernelWidthHeight, IppDataType dataType, int numChannels, IppiDistanceMethodType distMethod, Ipp64f valSquareSigma, Ipp64f posSquareSigma, IppiFilterBilateralSpec *pSpec))
IPPAPI(IppStatus, ippiFilterBilateral_8u_C1R, (const Ipp8u  *pSrc, int srcStep, Ipp8u  *pDst, int dstStep, IppiSize dstRoiSize, IppiBorderType borderType, const Ipp8u  pBorderValue[1], const IppiFilterBilateralSpec *pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterBilateral_8u_C3R, (const Ipp8u  *pSrc, int srcStep, Ipp8u  *pDst, int dstStep, IppiSize dstRoiSize, IppiBorderType borderType, const Ipp8u  pBorderValue[3], const IppiFilterBilateralSpec *pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterBilateral_32f_C1R, (const Ipp32f *pSrc, int srcStep, Ipp32f *pDst, int dstStep, IppiSize dstRoiSize, IppiBorderType borderType, const Ipp32f pBorderValue[1], const IppiFilterBilateralSpec *pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterBilateral_32f_C3R, (const Ipp32f *pSrc, int srcStep, Ipp32f *pDst, int dstStep, IppiSize dstRoiSize, IppiBorderType borderType, const Ipp32f pBorderValue[3], const IppiFilterBilateralSpec *pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterBilateral_64f_C1R, (const Ipp64f *pSrc, int srcStep, Ipp64f *pDst, int dstStep, IppiSize dstRoiSize, IppiBorderType borderType, const Ipp64f pBorderValue[1], const IppiFilterBilateralSpec *pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterBilateral_64f_C3R, (const Ipp64f *pSrc, int srcStep, Ipp64f *pDst, int dstStep, IppiSize dstRoiSize, IppiBorderType borderType, const Ipp64f pBorderValue[3], const IppiFilterBilateralSpec *pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterBilateral_8u_P3R,  (const Ipp8u*  pSrc[3], int srcStep[3], Ipp8u*  pDst[3], int dstStep[3], IppiSize dstRoiSize, IppiBorderType borderType, const Ipp8u  pBorderValue[3], const IppiFilterBilateralSpec *pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterBilateral_32f_P3R,  (const Ipp32f* pSrc[3], int srcStep[3], Ipp32f* pDst[3], int dstStep[3], IppiSize dstRoiSize, IppiBorderType borderType, const Ipp32f pBorderValue[3], const IppiFilterBilateralSpec *pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterBilateral_64f_P3R,  (const Ipp64f* pSrc[3], int srcStep[3], Ipp64f* pDst[3], int dstStep[3], IppiSize dstRoiSize, IppiBorderType borderType, const Ipp64f pBorderValue[3], const IppiFilterBilateralSpec *pSpec, Ipp8u* pBuffer))


/* /////////////////////////////////////////////////////////////////////////////
//                     Complement code converter
// /////////////////////////////////////////////////////////////////////////////
//  Name:
//   ippiComplement_32s_C1R
//   ippiComplement_32s_C3R
//   ippiComplement_32s_C4R
//   ippiComplement_32s_AC4R
//   ippiComplement_32s_C1IR
//   ippiComplement_32s_C3IR
//   ippiComplement_32s_C4IR
//   ippiComplement_32s_AC4IR

//   ippiComplement_16s_C1R
//   ippiComplement_16s_C3R
//   ippiComplement_16s_C4R
//   ippiComplement_16s_AC4R
//   ippiComplement_16s_C1IR
//   ippiComplement_16s_C3IR
//   ippiComplement_16s_C4IR
//   ippiComplement_16s_AC4IR

//   ippiComplement_8s_C1R
//   ippiComplement_8s_C3R
//   ippiComplement_8s_C4R
//   ippiComplement_8s_AC4R
//   ippiComplement_8s_C1IR
//   ippiComplement_8s_C3IR
//   ippiComplement_8s_C4IR
//   ippiComplement_8s_AC4IR

//  Purpose:    Convert value of every pixel from two's complement code to direct code.

//  Parameters:
//   pSrc          Pointer to the source image
//   srcStep       Step through the source image
//   pDst          Pointer to the destination image
//   dstStep       Step in destination image
//   pSrcDst       Pointer to the source/destination image (in-place flavors)
//   srcDstStep    Step through the source/destination image (in-place flavors)
//   roiSize       Size of the ROI

//  Return:
//    ippStsNoErr               OK
//    ippStsNullPtrErr          any pointer is NULL
//    ippStsStepErr             One of the step values is less than or equal to zero
//    ippStsSizeErr             size of dstRoiSize is less or equal 0
*/

IPPAPI(IppStatus,ippiComplement_32s_C1R,  (Ipp32s* pSrc,    int srcStep,    Ipp32s* pDst,   int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiComplement_32s_C3R,  (Ipp32s* pSrc,    int srcStep,    Ipp32s* pDst,   int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiComplement_32s_C4R,  (Ipp32s* pSrc,    int srcStep,    Ipp32s* pDst,   int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiComplement_32s_AC4R, (Ipp32s* pSrc,    int srcStep,    Ipp32s* pDst,   int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiComplement_32s_C1IR, (Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiComplement_32s_C3IR, (Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiComplement_32s_C4IR, (Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiComplement_32s_AC4IR,(Ipp32s* pSrcDst, int srcDstStep, IppiSize roiSize))

IPPAPI(IppStatus,ippiComplement_16s_C1R,  (Ipp16s* pSrc,    int srcStep,    Ipp16s* pDst,   int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiComplement_16s_C3R,  (Ipp16s* pSrc,    int srcStep,    Ipp16s* pDst,   int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiComplement_16s_C4R,  (Ipp16s* pSrc,    int srcStep,    Ipp16s* pDst,   int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiComplement_16s_AC4R, (Ipp16s* pSrc,    int srcStep,    Ipp16s* pDst,   int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiComplement_16s_C1IR, (Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiComplement_16s_C3IR, (Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiComplement_16s_C4IR, (Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiComplement_16s_AC4IR,(Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize))

IPPAPI(IppStatus,ippiComplement_8s_C1R,   (Ipp8s*  pSrc,    int srcStep,    Ipp8s*  pDst,   int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiComplement_8s_C3R,   (Ipp8s*  pSrc,    int srcStep,    Ipp8s*  pDst,   int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiComplement_8s_C4R,   (Ipp8s*  pSrc,    int srcStep,    Ipp8s*  pDst,   int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiComplement_8s_AC4R,  (Ipp8s*  pSrc,    int srcStep,    Ipp8s*  pDst,   int dstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiComplement_8s_C1IR,  (Ipp8s*  pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiComplement_8s_C3IR,  (Ipp8s*  pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiComplement_8s_C4IR,  (Ipp8s*  pSrcDst, int srcDstStep, IppiSize roiSize))
IPPAPI(IppStatus,ippiComplement_8s_AC4IR, (Ipp8s*  pSrcDst, int srcDstStep, IppiSize roiSize)) 

#ifdef __cplusplus
}
#endif


#endif /* IPPI_H__ */
