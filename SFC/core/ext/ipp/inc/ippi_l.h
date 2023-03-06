/*
// Copyright 2015-2020 Intel Corporation All Rights Reserved.
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
//              Image Processing (ippIP_L)
//
//
*/


#if !defined( IPPI_L_H__ ) || defined( _OWN_BLDPCS )
#define IPPI_L_H__

#ifndef IPPDEFS_L_H__
  #include "ippdefs_l.h"
#endif

#if (defined( IPP_ENABLED_THREADING_LAYER ) || defined( IPP_ENABLED_THREADING_LAYER_REDEFINITIONS ))
    #include "ippi_tl.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//                   Functions declarations
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////////
//                   Memory Allocation Functions
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiMalloc
//  Purpose:    allocates memory with 64-byte aligned pointer for ippIP images,
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

IPPAPI( Ipp8u*,   ippiMalloc_8u_C1_L,    ( IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes ) )
IPPAPI( Ipp16u*,  ippiMalloc_16u_C1_L,   ( IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes ) )
IPPAPI( Ipp16s*,  ippiMalloc_16s_C1_L,   ( IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes ) )
IPPAPI( Ipp32s*,  ippiMalloc_32s_C1_L,   ( IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes ) )
IPPAPI( Ipp32f*,  ippiMalloc_32f_C1_L,   ( IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes ) )
IPPAPI( Ipp32sc*, ippiMalloc_32sc_C1_L,  ( IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes ) )
IPPAPI( Ipp32fc*, ippiMalloc_32fc_C1_L,  ( IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes ) )

IPPAPI( Ipp8u*,   ippiMalloc_8u_C2_L,    ( IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes ) )
IPPAPI( Ipp16u*,  ippiMalloc_16u_C2_L,   ( IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes ) )
IPPAPI( Ipp16s*,  ippiMalloc_16s_C2_L,   ( IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes ) )
IPPAPI( Ipp32s*,  ippiMalloc_32s_C2_L,   ( IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes ) )
IPPAPI( Ipp32f*,  ippiMalloc_32f_C2_L,   ( IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes ) )
IPPAPI( Ipp32sc*, ippiMalloc_32sc_C2_L,  ( IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes ) )
IPPAPI( Ipp32fc*, ippiMalloc_32fc_C2_L,  ( IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes ) )

IPPAPI(Ipp8u*, ippiMalloc_8u_C3_L, (IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes))
IPPAPI(Ipp16u*, ippiMalloc_16u_C3_L, (IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes))
IPPAPI(Ipp16s*, ippiMalloc_16s_C3_L, (IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes))
IPPAPI(Ipp32s*, ippiMalloc_32s_C3_L, (IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes))
IPPAPI(Ipp32f*, ippiMalloc_32f_C3_L, (IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes))
IPPAPI(Ipp32sc*, ippiMalloc_32sc_C3_L, (IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes))
IPPAPI(Ipp32fc*, ippiMalloc_32fc_C3_L, (IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes))

IPPAPI(Ipp8u*, ippiMalloc_8u_C4_L, (IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes))
IPPAPI(Ipp16u*, ippiMalloc_16u_C4_L, (IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes))
IPPAPI(Ipp16s*, ippiMalloc_16s_C4_L, (IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes))
IPPAPI(Ipp32s*, ippiMalloc_32s_C4_L, (IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes))
IPPAPI(Ipp32f*, ippiMalloc_32f_C4_L, (IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes))
IPPAPI(Ipp32sc*, ippiMalloc_32sc_C4_L, (IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes))
IPPAPI(Ipp32fc*, ippiMalloc_32fc_C4_L, (IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes))

IPPAPI(Ipp8u*, ippiMalloc_8u_AC4_L, (IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes))
IPPAPI(Ipp16u*, ippiMalloc_16u_AC4_L, (IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes))
IPPAPI(Ipp16s*, ippiMalloc_16s_AC4_L, (IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes))
IPPAPI(Ipp32s*, ippiMalloc_32s_AC4_L, (IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes))
IPPAPI(Ipp32f*, ippiMalloc_32f_AC4_L, (IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes))
IPPAPI(Ipp32sc*, ippiMalloc_32sc_AC4_L, (IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes))
IPPAPI(Ipp32fc*, ippiMalloc_32fc_AC4_L, (IppSizeL widthPixels, IppSizeL heightPixels, IppSizeL* pStepBytes))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippiCopy..L
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

IPPAPI(IppStatus, ippiCopy_8u_C1R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiCopy_8u_C3R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiCopy_8u_C4R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiCopy_8u_AC4R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize))

IPPAPI(IppStatus, ippiCopy_16s_C1R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiCopy_16s_C3R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiCopy_16s_C4R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiCopy_16s_AC4R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize))

IPPAPI(IppStatus, ippiCopy_16u_C1R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiCopy_16u_C3R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiCopy_16u_C4R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiCopy_16u_AC4R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize))

IPPAPI(IppStatus, ippiCopy_32s_C1R_L, (const Ipp32s* pSrc, IppSizeL srcStep, Ipp32s* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiCopy_32s_C3R_L, (const Ipp32s* pSrc, IppSizeL srcStep, Ipp32s* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiCopy_32s_C4R_L, (const Ipp32s* pSrc, IppSizeL srcStep, Ipp32s* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiCopy_32s_AC4R_L, (const Ipp32s* pSrc, IppSizeL srcStep, Ipp32s* pDst, IppSizeL dstStep, IppiSizeL roiSize))

IPPAPI(IppStatus, ippiCopy_32f_C1R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiCopy_32f_C3R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiCopy_32f_C4R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiCopy_32f_AC4R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))

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
IPPAPI(IppStatus, ippiCopyReplicateBorder_8u_C1R_L,  (const Ipp8u* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_8u_C3R_L,  (const Ipp8u* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_8u_C4R_L,  (const Ipp8u* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_8u_AC4R_L, (const Ipp8u* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_16s_C1R_L, (const Ipp16s* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_16s_C3R_L, (const Ipp16s* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_16s_AC4R_L, (const Ipp16s* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_16s_C4R_L, (const Ipp16s* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_16u_C1R_L, (const Ipp16u* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_16u_C3R_L, (const Ipp16u* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_16u_AC4R_L, (const Ipp16u* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_16u_C4R_L, (const Ipp16u* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_32s_C1R_L, (const Ipp32s* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp32s* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_32s_C3R_L, (const Ipp32s* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp32s* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_32s_AC4R_L, (const Ipp32s* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp32s* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_32s_C4R_L, (const Ipp32s* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp32s* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_32s_C1IR_L,(const Ipp32s* pSrc, IppSizeL srcDstStep,    IppiSizeL srcRoiSize, IppiSizeL dstRoiSize,    IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_32s_C3IR_L, (const Ipp32s* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_32s_AC4IR_L, (const Ipp32s* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_32s_C4IR_L, (const Ipp32s* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_32f_C1R_L, (const Ipp32f* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_32f_C3R_L, (const Ipp32f* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_32f_AC4R_L, (const Ipp32f* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_32f_C4R_L, (const Ipp32f* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_32f_C1IR_L, (const Ipp32f* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_32f_C3IR_L, (const Ipp32f* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_32f_AC4IR_L, (const Ipp32f* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_32f_C4IR_L, (const Ipp32f* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_8u_C1IR_L, (const Ipp8u* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_8u_C3IR_L, (const Ipp8u* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_8u_AC4IR_L, (const Ipp8u* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_8u_C4IR_L, (const Ipp8u* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_16u_C1IR_L, (const Ipp16u* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_16u_C3IR_L, (const Ipp16u* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_16u_AC4IR_L, (const Ipp16u* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_16u_C4IR_L, (const Ipp16u* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_16s_C1IR_L, (const Ipp16s* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_16s_C3IR_L, (const Ipp16s* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_16s_AC4IR_L, (const Ipp16s* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyReplicateBorder_16s_C4IR_L, (const Ipp16s* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))


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
IPPAPI(IppStatus, ippiCopyWrapBorder_32s_C1R_L, (const Ipp32s* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp32s* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyWrapBorder_32s_C1IR_L, (const Ipp32s* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyWrapBorder_32f_C1R_L, (const Ipp32f* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyWrapBorder_32f_C1IR_L, (const Ipp32f* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
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
//    pSrcDst            Pointer to the source/destination image (for in-place function)
//    srcStep            Step in bytes through the source image
//    srcDstStep         Step through the source/destination image for in-place functions
//    pDst               Pointer to the  destination image buffer
//    dstStep            Step in bytes through the destination image
//    srcRoiSize         Size of the source ROI in pixels
//    dstRoiSize         Size of the destination ROI in pixels
//    topBorderHeight    Height of the top border in pixels
//    leftBorderWidth    Width of the left border in pixels
//    value              Constant value to assign to the border pixels
*/
IPPAPI(IppStatus, ippiCopyConstBorder_8u_C1R_L, (const Ipp8u* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, Ipp8u value))
IPPAPI(IppStatus, ippiCopyConstBorder_8u_C3R_L, (const Ipp8u* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, const Ipp8u value[3]))
IPPAPI(IppStatus, ippiCopyConstBorder_8u_AC4R_L, (const Ipp8u* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, const Ipp8u value[3]))
IPPAPI(IppStatus, ippiCopyConstBorder_8u_C4R_L, (const Ipp8u* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, const Ipp8u value[4]))
IPPAPI(IppStatus, ippiCopyConstBorder_16s_C1R_L, (const Ipp16s* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, Ipp16s value))
IPPAPI(IppStatus, ippiCopyConstBorder_16s_C3R_L, (const Ipp16s* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, const Ipp16s value[3]))
IPPAPI(IppStatus, ippiCopyConstBorder_16s_AC4R_L, (const Ipp16s* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, const Ipp16s value[3]))
IPPAPI(IppStatus, ippiCopyConstBorder_16s_C4R_L, (const Ipp16s* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, const Ipp16s value[4]))
IPPAPI(IppStatus, ippiCopyConstBorder_32s_C1R_L, (const Ipp32s* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp32s* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, Ipp32s value))
IPPAPI(IppStatus, ippiCopyConstBorder_32s_C3R_L, (const Ipp32s* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp32s* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, const Ipp32s value[3]))
IPPAPI(IppStatus, ippiCopyConstBorder_32s_AC4R_L, (const Ipp32s* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp32s* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, const Ipp32s value[3]))
IPPAPI(IppStatus, ippiCopyConstBorder_32s_C4R_L, (const Ipp32s* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp32s* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, const Ipp32s value[4]))

IPPAPI(IppStatus, ippiCopyConstBorder_16u_C1R_L, (const Ipp16u* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, Ipp16u value))
IPPAPI(IppStatus, ippiCopyConstBorder_16u_C3R_L, (const Ipp16u* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, const Ipp16u value[3]))
IPPAPI(IppStatus, ippiCopyConstBorder_16u_AC4R_L, (const Ipp16u* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, const Ipp16u value[3]))
IPPAPI(IppStatus, ippiCopyConstBorder_16u_C4R_L, (const Ipp16u* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, const Ipp16u value[4]))

IPPAPI(IppStatus, ippiCopyConstBorder_32f_C1R_L, (const Ipp32f* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, Ipp32f value))
IPPAPI(IppStatus, ippiCopyConstBorder_32f_C3R_L, (const Ipp32f* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, const Ipp32f value[3]))
IPPAPI(IppStatus, ippiCopyConstBorder_32f_AC4R_L, (const Ipp32f* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, const Ipp32f value[3]))
IPPAPI(IppStatus, ippiCopyConstBorder_32f_C4R_L, (const Ipp32f* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, const Ipp32f value[4]))

IPPAPI(IppStatus, ippiCopyConstBorder_8u_C1IR_L, (Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth, const Ipp8u value))
IPPAPI(IppStatus, ippiCopyConstBorder_8u_C3IR_L, (Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth, const Ipp8u value[3]))
IPPAPI(IppStatus, ippiCopyConstBorder_8u_AC4IR_L, (Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth, const Ipp8u value[3]))
IPPAPI(IppStatus, ippiCopyConstBorder_8u_C4IR_L, (Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth, const Ipp8u value[4]))

IPPAPI(IppStatus, ippiCopyConstBorder_16u_C1IR_L, (Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth, const Ipp16u value))
IPPAPI(IppStatus, ippiCopyConstBorder_16u_C3IR_L, (Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth, const Ipp16u value[3]))
IPPAPI(IppStatus, ippiCopyConstBorder_16u_AC4IR_L, (Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth, const Ipp16u value[3]))
IPPAPI(IppStatus, ippiCopyConstBorder_16u_C4IR_L, (Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth, const Ipp16u value[4]))

IPPAPI(IppStatus, ippiCopyConstBorder_16s_C1IR_L, (Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth, const Ipp16s value))
IPPAPI(IppStatus, ippiCopyConstBorder_16s_C3IR_L, (Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth, const Ipp16s value[3]))
IPPAPI(IppStatus, ippiCopyConstBorder_16s_AC4IR_L, (Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth, const Ipp16s value[3]))
IPPAPI(IppStatus, ippiCopyConstBorder_16s_C4IR_L, (Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth, const Ipp16s value[4]))

IPPAPI(IppStatus, ippiCopyConstBorder_32s_C1IR_L, (Ipp32s* pSrcDst, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth, const Ipp32s value))
IPPAPI(IppStatus, ippiCopyConstBorder_32s_C3IR_L, (Ipp32s* pSrcDst, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth, const Ipp32s value[3]))
IPPAPI(IppStatus, ippiCopyConstBorder_32s_AC4IR_L, (Ipp32s* pSrcDst, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth, const Ipp32s value[3]))
IPPAPI(IppStatus, ippiCopyConstBorder_32s_C4IR_L, (Ipp32s* pSrcDst, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth, const Ipp32s value[4]))

IPPAPI(IppStatus, ippiCopyConstBorder_32f_C1IR_L, (Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth, const Ipp32f value))
IPPAPI(IppStatus, ippiCopyConstBorder_32f_C3IR_L, (Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth, const Ipp32f value[3]))
IPPAPI(IppStatus, ippiCopyConstBorder_32f_AC4IR_L, (Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth, const Ipp32f value[3]))
IPPAPI(IppStatus, ippiCopyConstBorder_32f_C4IR_L, (Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth, const Ipp32f value[4]))

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
IPPAPI(IppStatus, ippiCopyMirrorBorder_8u_C1R_L, (const Ipp8u* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_8u_C3R_L, (const Ipp8u* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_8u_C4R_L, (const Ipp8u* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_16s_C1R_L, (const Ipp16s* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_16s_C3R_L, (const Ipp16s* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_16s_C4R_L, (const Ipp16s* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_32s_C1R_L, (const Ipp32s* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp32s* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_32s_C3R_L, (const Ipp32s* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp32s* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_32s_C4R_L, (const Ipp32s* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp32s* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_8u_C1IR_L, (const Ipp8u* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_8u_C3IR_L, (const Ipp8u* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_8u_C4IR_L, (const Ipp8u* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_16s_C1IR_L, (const Ipp16s* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_16s_C3IR_L, (const Ipp16s* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_16s_C4IR_L, (const Ipp16s* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_32s_C1IR_L, (const Ipp32s* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_32s_C3IR_L, (const Ipp32s* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_32s_C4IR_L, (const Ipp32s* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_16u_C1IR_L, (const Ipp16u* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_16u_C3IR_L, (const Ipp16u* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_16u_C4IR_L, (const Ipp16u* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_16u_C1R_L, (const Ipp16u* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_16u_C3R_L, (const Ipp16u* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_16u_C4R_L, (const Ipp16u* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_32f_C1R_L, (const Ipp32f* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_32f_C3R_L, (const Ipp32f* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_32f_C4R_L, (const Ipp32f* pSrc, IppSizeL srcStep, IppiSizeL srcRoiSize, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftBorderWidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_32f_C1IR_L, (const Ipp32f* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_32f_C3IR_L, (const Ipp32f* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))
IPPAPI(IppStatus, ippiCopyMirrorBorder_32f_C4IR_L, (const Ipp32f* pSrc, IppSizeL srcDstStep, IppiSizeL srcRoiSize, IppiSizeL dstRoiSize, IppSizeL topBorderHeight, IppSizeL leftborderwidth))


/* ////////////////////////////////////////////////////////////////////////////
//  Name:  ippiAdd_8u_C1RSfs_L,  ippiAdd_8u_C3RSfs_L,  ippiAdd_8u_C4RSfs_L,  ippiAdd_8u_AC4RSfs_L,
//         ippiAdd_16s_C1RSfs_L, ippiAdd_16s_C3RSfs_L, ippiAdd_16s_C4RSfs_L, ippiAdd_16s_AC4RSfs_L,
//         ippiAdd_16u_C1RSfs_L, ippiAdd_16u_C3RSfs_L, ippiAdd_16u_C4RSfs_L, ippiAdd_16u_AC4RSfs_L,
//         ippiSub_8u_C1RSfs_L,  ippiSub_8u_C3RSfs_L,  ippiSub_8u_C4RSfs_L,  ippiSub_8u_AC4RSfs_L,
//         ippiSub_16s_C1RSfs_L, ippiSub_16s_C3RSfs_L, ippiSub_16s_C4RSfs_L, ippiSub_16s_AC4RSfs_L,
//         ippiSub_16u_C1RSfs_L, ippiSub_16u_C3RSfs_L, ippiSub_16u_C4RSfs_L, ippiSub_16u_AC4RSfs_L,
//         ippiMul_8u_C1RSfs_L,  ippiMul_8u_C3RSfs_L,  ippiMul_8u_C4RSfs_L,  ippiMul_8u_AC4RSfs_L,
//         ippiMul_16s_C1RSfs_L, ippiMul_16s_C3RSfs_L, ippiMul_16s_C4RSfs_L, ippiMul_16s_AC4RSfs_L,
//         ippiMul_16u_C1RSfs_L, ippiMul_16u_C3RSfs_L, ippiMul_16u_C4RSfs_L, ippiMul_16u_AC4RSfs_L,
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
IPPAPI(IppStatus, ippiAdd_8u_C1RSfs_L,   (const Ipp8u* pSrc1, IppSizeL src1Step, const Ipp8u* pSrc2, IppSizeL src2Step, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_8u_C3RSfs_L,   (const Ipp8u* pSrc1, IppSizeL src1Step, const Ipp8u* pSrc2, IppSizeL src2Step, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_8u_C4RSfs_L,   (const Ipp8u* pSrc1, IppSizeL src1Step, const Ipp8u* pSrc2, IppSizeL src2Step, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_8u_AC4RSfs_L,  (const Ipp8u* pSrc1, IppSizeL src1Step, const Ipp8u* pSrc2, IppSizeL src2Step, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))

IPPAPI(IppStatus, ippiAdd_16u_C1RSfs_L,  (const Ipp16u* pSrc1, IppSizeL src1Step, const Ipp16u* pSrc2, IppSizeL src2Step, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16u_C3RSfs_L,  (const Ipp16u* pSrc1, IppSizeL src1Step, const Ipp16u* pSrc2, IppSizeL src2Step, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16u_C4RSfs_L,  (const Ipp16u* pSrc1, IppSizeL src1Step, const Ipp16u* pSrc2, IppSizeL src2Step, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16u_AC4RSfs_L, (const Ipp16u* pSrc1, IppSizeL src1Step, const Ipp16u* pSrc2, IppSizeL src2Step, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))

IPPAPI(IppStatus, ippiAdd_16s_C1RSfs_L,  (const Ipp16s* pSrc1, IppSizeL src1Step, const Ipp16s* pSrc2, IppSizeL src2Step, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16s_C3RSfs_L,  (const Ipp16s* pSrc1, IppSizeL src1Step, const Ipp16s* pSrc2, IppSizeL src2Step, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16s_C4RSfs_L,  (const Ipp16s* pSrc1, IppSizeL src1Step, const Ipp16s* pSrc2, IppSizeL src2Step, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16s_AC4RSfs_L, (const Ipp16s* pSrc1, IppSizeL src1Step, const Ipp16s* pSrc2, IppSizeL src2Step, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))

IPPAPI(IppStatus, ippiSub_8u_C1RSfs_L,   (const Ipp8u* pSrc1, IppSizeL src1Step, const Ipp8u* pSrc2, IppSizeL src2Step, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_8u_C3RSfs_L,   (const Ipp8u* pSrc1, IppSizeL src1Step, const Ipp8u* pSrc2, IppSizeL src2Step, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_8u_C4RSfs_L,   (const Ipp8u* pSrc1, IppSizeL src1Step, const Ipp8u* pSrc2, IppSizeL src2Step, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_8u_AC4RSfs_L,  (const Ipp8u* pSrc1, IppSizeL src1Step, const Ipp8u* pSrc2, IppSizeL src2Step, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))

IPPAPI(IppStatus, ippiSub_16u_C1RSfs_L,  (const Ipp16u* pSrc1, IppSizeL src1Step, const Ipp16u* pSrc2, IppSizeL src2Step, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_16u_C3RSfs_L,  (const Ipp16u* pSrc1, IppSizeL src1Step, const Ipp16u* pSrc2, IppSizeL src2Step, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_16u_C4RSfs_L,  (const Ipp16u* pSrc1, IppSizeL src1Step, const Ipp16u* pSrc2, IppSizeL src2Step, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_16u_AC4RSfs_L, (const Ipp16u* pSrc1, IppSizeL src1Step, const Ipp16u* pSrc2, IppSizeL src2Step, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))

IPPAPI(IppStatus, ippiSub_16s_C1RSfs_L,  (const Ipp16s* pSrc1, IppSizeL src1Step, const Ipp16s* pSrc2, IppSizeL src2Step, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_16s_C3RSfs_L,  (const Ipp16s* pSrc1, IppSizeL src1Step, const Ipp16s* pSrc2, IppSizeL src2Step, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_16s_C4RSfs_L,  (const Ipp16s* pSrc1, IppSizeL src1Step, const Ipp16s* pSrc2, IppSizeL src2Step, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_16s_AC4RSfs_L, (const Ipp16s* pSrc1, IppSizeL src1Step, const Ipp16s* pSrc2, IppSizeL src2Step, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))

IPPAPI(IppStatus, ippiMul_8u_C1RSfs_L,  (const Ipp8u* pSrc1, IppSizeL src1Step, const Ipp8u* pSrc2, IppSizeL src2Step, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_8u_C3RSfs_L,  (const Ipp8u* pSrc1, IppSizeL src1Step, const Ipp8u* pSrc2, IppSizeL src2Step, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_8u_C4RSfs_L,  (const Ipp8u* pSrc1, IppSizeL src1Step, const Ipp8u* pSrc2, IppSizeL src2Step, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_8u_AC4RSfs_L, (const Ipp8u* pSrc1, IppSizeL src1Step, const Ipp8u* pSrc2, IppSizeL src2Step, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))

IPPAPI(IppStatus, ippiMul_16s_C1RSfs_L,  (const Ipp16s* pSrc1, IppSizeL src1Step, const Ipp16s* pSrc2, IppSizeL src2Step, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_16s_C3RSfs_L,  (const Ipp16s* pSrc1, IppSizeL src1Step, const Ipp16s* pSrc2, IppSizeL src2Step, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_16s_C4RSfs_L,  (const Ipp16s* pSrc1, IppSizeL src1Step, const Ipp16s* pSrc2, IppSizeL src2Step, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_16s_AC4RSfs_L, (const Ipp16s* pSrc1, IppSizeL src1Step, const Ipp16s* pSrc2, IppSizeL src2Step, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))

IPPAPI(IppStatus, ippiMul_16u_C1RSfs_L,  (const Ipp16u* pSrc1, IppSizeL src1Step, const Ipp16u* pSrc2, IppSizeL src2Step, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_16u_C3RSfs_L,  (const Ipp16u* pSrc1, IppSizeL src1Step, const Ipp16u* pSrc2, IppSizeL src2Step, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_16u_C4RSfs_L,  (const Ipp16u* pSrc1, IppSizeL src1Step, const Ipp16u* pSrc2, IppSizeL src2Step, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_16u_AC4RSfs_L, (const Ipp16u* pSrc1, IppSizeL src1Step, const Ipp16u* pSrc2, IppSizeL src2Step, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))

IPPAPI(IppStatus, ippiMulC_8u_C1RSfs_L,  (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u value, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_8u_C3RSfs_L,  (const Ipp8u* pSrc, IppSizeL srcStep, const Ipp8u value[3], Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_8u_C4RSfs_L,  (const Ipp8u* pSrc, IppSizeL srcStep, const Ipp8u value[4], Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_8u_AC4RSfs_L, (const Ipp8u* pSrc, IppSizeL srcStep, const Ipp8u value[3], Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))

IPPAPI(IppStatus, ippiMulC_16s_C1RSfs_L,  (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s value, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16s_C3RSfs_L,  (const Ipp16s* pSrc, IppSizeL srcStep, const Ipp16s value[3], Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16s_C4RSfs_L,  (const Ipp16s* pSrc, IppSizeL srcStep, const Ipp16s value[4], Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16s_AC4RSfs_L, (const Ipp16s* pSrc, IppSizeL srcStep, const Ipp16s value[3], Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))

IPPAPI(IppStatus, ippiMulC_16u_C1RSfs_L,  (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u value, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16u_C3RSfs_L,  (const Ipp16u* pSrc, IppSizeL srcStep, const Ipp16u value[3], Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16u_C4RSfs_L,  (const Ipp16u* pSrc, IppSizeL srcStep, const Ipp16u value[4], Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16u_AC4RSfs_L, (const Ipp16u* pSrc, IppSizeL srcStep, const Ipp16u value[3], Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))

IPPAPI(IppStatus, ippiMul_8u_C1IRSfs_L,  (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_8u_C3IRSfs_L,  (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_8u_C4IRSfs_L,  (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_8u_AC4IRSfs_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))

IPPAPI(IppStatus, ippiMul_16s_C1IRSfs_L,  (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_16s_C3IRSfs_L,  (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_16s_C4IRSfs_L,  (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_16s_AC4IRSfs_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))

IPPAPI(IppStatus, ippiMul_16u_C1IRSfs_L,  (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_16u_C3IRSfs_L,  (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_16u_C4IRSfs_L,  (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMul_16u_AC4IRSfs_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))

IPPAPI(IppStatus, ippiSub_32f_C1R_L,  (const Ipp32f* pSrc1, IppSizeL src1Step, const Ipp32f* pSrc2, IppSizeL src2Step, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiSub_32f_C3R_L,  (const Ipp32f* pSrc1, IppSizeL src1Step, const Ipp32f* pSrc2, IppSizeL src2Step, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiSub_32f_C4R_L,  (const Ipp32f* pSrc1, IppSizeL src1Step, const Ipp32f* pSrc2, IppSizeL src2Step, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiSub_32f_AC4R_L, (const Ipp32f* pSrc1, IppSizeL src1Step, const Ipp32f* pSrc2, IppSizeL src2Step, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))

IPPAPI(IppStatus, ippiSub_32f_C1IR_L, (const Ipp32f* pSrc1, IppSizeL src1Step, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiSub_32f_C3IR_L, (const Ipp32f* pSrc1, IppSizeL src1Step, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiSub_32f_C4IR_L, (const Ipp32f* pSrc1, IppSizeL src1Step, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiSub_32f_AC4IR_L, (const Ipp32f* pSrc1, IppSizeL src1Step, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))

IPPAPI(IppStatus, ippiAdd_32f_C1R_L,  (const Ipp32f* pSrc1, IppSizeL src1Step, const Ipp32f* pSrc2, IppSizeL src2Step, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiAdd_32f_C3R_L,  (const Ipp32f* pSrc1, IppSizeL src1Step, const Ipp32f* pSrc2, IppSizeL src2Step, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiAdd_32f_C4R_L,  (const Ipp32f* pSrc1, IppSizeL src1Step, const Ipp32f* pSrc2, IppSizeL src2Step, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiAdd_32f_AC4R_L, (const Ipp32f* pSrc1, IppSizeL src1Step, const Ipp32f* pSrc2, IppSizeL src2Step, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))

IPPAPI(IppStatus, ippiAdd_32f_C1IR_L,  (const Ipp32f* pSrc1, IppSizeL src1Step, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiAdd_32f_C3IR_L,  (const Ipp32f* pSrc1, IppSizeL src1Step, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiAdd_32f_C4IR_L,  (const Ipp32f* pSrc1, IppSizeL src1Step, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiAdd_32f_AC4IR_L, (const Ipp32f* pSrc1, IppSizeL src1Step, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))

IPPAPI(IppStatus, ippiMulC_8u_C1IRSfs_L, (Ipp8u value, Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSizeL, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_8u_C3IRSfs_L, (const Ipp8u value[3], Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_8u_C4IRSfs_L, (const Ipp8u value[4], Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_8u_AC4IRSfs_L, (const Ipp8u value[3], Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))

IPPAPI(IppStatus, ippiMulC_16u_C1IRSfs_L, (Ipp16u value, Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSizeL, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16u_C3IRSfs_L, (const Ipp16u value[3], Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16u_C4IRSfs_L, (const Ipp16u value[4], Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16u_AC4IRSfs_L, (const Ipp16u value[3], Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))

IPPAPI(IppStatus, ippiMulC_16s_C1IRSfs_L, (Ipp16s value, Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSizeL, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16s_C3IRSfs_L, (const Ipp16s value[3], Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16s_C4IRSfs_L, (const Ipp16s value[4], Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiMulC_16s_AC4IRSfs_L, (const Ipp16s value[3], Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))

IPPAPI(IppStatus, ippiMul_32f_C1R_L, (const Ipp32f* pSrc1, IppSizeL src1Step, const Ipp32f* pSrc2, IppSizeL src2Step, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiMul_32f_C3R_L, (const Ipp32f* pSrc1, IppSizeL src1Step, const Ipp32f* pSrc2, IppSizeL src2Step, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiMul_32f_C4R_L, (const Ipp32f* pSrc1, IppSizeL src1Step, const Ipp32f* pSrc2, IppSizeL src2Step, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiMul_32f_AC4R_L, (const Ipp32f* pSrc1, IppSizeL src1Step, const Ipp32f* pSrc2, IppSizeL src2Step, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))

IPPAPI(IppStatus, ippiMul_32f_C1IR_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiMul_32f_C3IR_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiMul_32f_C4IR_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiMul_32f_AC4IR_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize))

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

IPPAPI(IppStatus, ippiDiv_32f_C1R_L, (const Ipp32f* pSrc1, IppSizeL src1Step, const Ipp32f* pSrc2, IppSizeL src2Step,Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiDiv_32f_C3R_L, (const Ipp32f* pSrc1, IppSizeL src1Step, const Ipp32f* pSrc2, IppSizeL src2Step,Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiDiv_32f_C4R_L, (const Ipp32f* pSrc1, IppSizeL src1Step, const Ipp32f* pSrc2, IppSizeL src2Step,Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiDiv_32f_AC4R_L, (const Ipp32f* pSrc1, IppSizeL src1Step, const Ipp32f* pSrc2, IppSizeL src2Step,Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))

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

IPPAPI(IppStatus, ippiDiv_32f_C1IR_L, (const Ipp32f* pSrc, IppSizeL srcStep,Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiDiv_32f_C3IR_L, (const Ipp32f* pSrc, IppSizeL srcStep,Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiDiv_32f_C4IR_L, (const Ipp32f* pSrc, IppSizeL srcStep,Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiDiv_32f_AC4IR_L, (const Ipp32f* pSrc, IppSizeL srcStep,Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize))

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

IPPAPI(IppStatus, ippiDiv_16s_C1RSfs_L, (const Ipp16s* pSrc1, IppSizeL src1Step, const Ipp16s* pSrc2, IppSizeL src2Step, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_16s_C3RSfs_L, (const Ipp16s* pSrc1, IppSizeL src1Step, const Ipp16s* pSrc2, IppSizeL src2Step, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_16s_C4RSfs_L, (const Ipp16s* pSrc1, IppSizeL src1Step, const Ipp16s* pSrc2, IppSizeL src2Step, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_16s_AC4RSfs_L, (const Ipp16s* pSrc1, IppSizeL src1Step, const Ipp16s* pSrc2, IppSizeL src2Step, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_8u_C1RSfs_L, (const Ipp8u* pSrc1, IppSizeL src1Step, const Ipp8u* pSrc2, IppSizeL src2Step, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_8u_C3RSfs_L, (const Ipp8u* pSrc1, IppSizeL src1Step, const Ipp8u* pSrc2, IppSizeL src2Step, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_8u_C4RSfs_L, (const Ipp8u* pSrc1, IppSizeL src1Step, const Ipp8u* pSrc2, IppSizeL src2Step, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_8u_AC4RSfs_L, (const Ipp8u* pSrc1, IppSizeL src1Step, const Ipp8u* pSrc2, IppSizeL src2Step, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_16u_C1RSfs_L, (const Ipp16u* pSrc1, IppSizeL src1Step, const Ipp16u* pSrc2, IppSizeL src2Step, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_16u_C3RSfs_L, (const Ipp16u* pSrc1, IppSizeL src1Step, const Ipp16u* pSrc2, IppSizeL src2Step, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_16u_C4RSfs_L, (const Ipp16u* pSrc1, IppSizeL src1Step, const Ipp16u* pSrc2, IppSizeL src2Step, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_16u_AC4RSfs_L, (const Ipp16u* pSrc1, IppSizeL src1Step,const Ipp16u* pSrc2, IppSizeL src2Step,Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int ScaleFactor))

IPPAPI(IppStatus, ippiDivC_16s_C1RSfs_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s value,Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_16s_C3RSfs_L, (const Ipp16s* pSrc, IppSizeL srcStep, const Ipp16s value[3],Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_16s_C4RSfs_L, (const Ipp16s* pSrc, IppSizeL srcStep, const Ipp16s value[4],Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_16s_AC4RSfs_L, (const Ipp16s* pSrc, IppSizeL srcStep, const Ipp16s value[3],Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_8u_C1RSfs_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u value,Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_8u_C3RSfs_L, (const Ipp8u* pSrc, IppSizeL srcStep, const Ipp8u value[3],Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_8u_C4RSfs_L, (const Ipp8u* pSrc, IppSizeL srcStep, const Ipp8u value[4],Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_8u_AC4RSfs_L, (const Ipp8u* pSrc, IppSizeL srcStep, const Ipp8u value[3],Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_16u_C1RSfs_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u value,Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_16u_C3RSfs_L, (const Ipp16u* pSrc, IppSizeL srcStep, const Ipp16u value[3],Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_16u_C4RSfs_L, (const Ipp16u* pSrc, IppSizeL srcStep, const Ipp16u value[4],Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_16u_AC4RSfs_L, (const Ipp16u* pSrc, IppSizeL srcStep, const Ipp16u value[3],Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))

IPPAPI(IppStatus, ippiDivC_16s_C1IRSfs_L, (Ipp16s value, Ipp16s* pSrcDst,IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_16s_C3IRSfs_L, (const Ipp16s value[3], Ipp16s* pSrcDst,IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_16s_C4IRSfs_L, (const Ipp16s val[4], Ipp16s* pSrcDst,IppSizeL srcDstStep, IppiSizeL roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDivC_16s_AC4IRSfs_L, (const Ipp16s val[3], Ipp16s* pSrcDst,IppSizeL srcDstStep, IppiSizeL roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDivC_8u_C1IRSfs_L, (Ipp8u value, Ipp8u* pSrcDst,IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_8u_C3IRSfs_L, (const Ipp8u value[3], Ipp8u* pSrcDst,IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_8u_C4IRSfs_L, (const Ipp8u val[4], Ipp8u* pSrcDst,IppSizeL srcDstStep, IppiSizeL roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDivC_8u_AC4IRSfs_L, (const Ipp8u val[3], Ipp8u* pSrcDst,IppSizeL srcDstStep, IppiSizeL roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDivC_16u_C1IRSfs_L, (Ipp16u value, Ipp16u* pSrcDst,IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_16u_C3IRSfs_L, (const Ipp16u value[3], Ipp16u* pSrcDst,IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDivC_16u_C4IRSfs_L, (const Ipp16u val[4], Ipp16u* pSrcDst,IppSizeL srcDstStep, IppiSizeL roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDivC_16u_AC4IRSfs_L, (const Ipp16u val[3], Ipp16u* pSrcDst,IppSizeL srcDstStep, IppiSizeL roiSize, int ScaleFactor))
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

IPPAPI(IppStatus, ippiDivC_32f_C1R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f value,Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiDivC_32f_C3R_L, (const Ipp32f* pSrc, IppSizeL srcStep, const Ipp32f value[3],Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiDivC_32f_C4R_L, (const Ipp32f* pSrc, IppSizeL srcStep, const Ipp32f val[4],Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiDivC_32f_AC4R_L, (const Ipp32f* pSrc, IppSizeL srcStep, const Ipp32f val[3],Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))

IPPAPI(IppStatus, ippiDivC_32f_C1IR_L, (Ipp32f value, Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiDivC_32f_C3IR_L, (const Ipp32f value[3], Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiDivC_32f_C4IR_L, (const Ipp32f val[4], Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiDivC_32f_AC4IR_L, (const Ipp32f val[3], Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize))

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

IPPAPI(IppStatus, ippiDiv_16s_C1IRSfs_L, (const Ipp16s* pSrc, IppSizeL srcStep,Ipp16s* pSrcDst, IppSizeL srcDstStep,IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_16s_C3IRSfs_L, (const Ipp16s* pSrc, IppSizeL srcStep,Ipp16s* pSrcDst, IppSizeL srcDstStep,IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_16s_C4IRSfs_L, (const Ipp16s* pSrc, IppSizeL srcStep,Ipp16s* pSrcDst, IppSizeL srcDstStep,IppiSizeL roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_16s_AC4IRSfs_L, (const Ipp16s* pSrc, IppSizeL srcStep,Ipp16s* pSrcDst, IppSizeL srcDstStep,IppiSizeL roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_8u_C1IRSfs_L, (const Ipp8u* pSrc, IppSizeL srcStep,Ipp8u* pSrcDst, IppSizeL srcDstStep,IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_8u_C3IRSfs_L, (const Ipp8u* pSrc, IppSizeL srcStep,Ipp8u* pSrcDst, IppSizeL srcDstStep,IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_8u_C4IRSfs_L, (const Ipp8u* pSrc, IppSizeL srcStep,Ipp8u* pSrcDst, IppSizeL srcDstStep,IppiSizeL roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_8u_AC4IRSfs_L, (const Ipp8u* pSrc, IppSizeL srcStep,Ipp8u* pSrcDst, IppSizeL srcDstStep,IppiSizeL roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_16u_C1IRSfs_L, (const Ipp16u* pSrc, IppSizeL srcStep,Ipp16u* pSrcDst, IppSizeL srcDstStep,IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_16u_C3IRSfs_L, (const Ipp16u* pSrc, IppSizeL srcStep,Ipp16u* pSrcDst, IppSizeL srcDstStep,IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiDiv_16u_C4IRSfs_L, (const Ipp16u* pSrc, IppSizeL srcStep,Ipp16u* pSrcDst, IppSizeL srcDstStep,IppiSizeL roiSize, int ScaleFactor))
IPPAPI(IppStatus, ippiDiv_16u_AC4IRSfs_L, (const Ipp16u* pSrc, IppSizeL srcStep,Ipp16u* pSrcDst, IppSizeL srcDstStep,IppiSizeL roiSize, int ScaleFactor))


/* /////////////////////////////////////////////////////////////////////////////////
//  Name: ippiAddC_32f_C1R_L, ippiAddC_32f_C3R_L, ippiAddC_32f_C4R_L,  ippiAddC_32f_AC4R_L,
//        ippiSubC_32f_C1R_L, ippiSubC_32f_C3R_L, ippiSubC_32f_C4R_L,  ippiSubC_32f_AC4R_L,
//        ippiMulC_32f_C1R_L, ippiMulC_32f_C3R_L, ippiMulC_32f_C4R_L,  ippiMulC_32f_AC4R_L
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

IPPAPI(IppStatus, ippiAddC_32f_C1R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f value, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiAddC_32f_C3R_L, (const Ipp32f* pSrc, IppSizeL srcStep, const Ipp32f value[3], Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiAddC_32f_C4R_L, (const Ipp32f* pSrc, IppSizeL srcStep, const Ipp32f value[4], Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiAddC_32f_AC4R_L, (const Ipp32f* pSrc, IppSizeL srcStep, const Ipp32f value[3], Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiSubC_32f_C1R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f value, Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiSubC_32f_C3R_L, (const Ipp32f* pSrc, IppSizeL srcStep, const Ipp32f value[3], Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiSubC_32f_C4R_L, (const Ipp32f* pSrc, IppSizeL srcStep, const Ipp32f value[4], Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiSubC_32f_AC4R_L, (const Ipp32f* pSrc, IppSizeL srcStep, const Ipp32f value[3], Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiMulC_32f_C1R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f value, Ipp32f* Dst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiMulC_32f_C3R_L, (const Ipp32f* pSrc, IppSizeL srcStep, const Ipp32f value[3], Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiMulC_32f_C4R_L, (const Ipp32f* pSrc, IppSizeL srcStep, const Ipp32f value[4], Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiMulC_32f_AC4R_L, (const Ipp32f* pSrc, IppSizeL srcStep, const Ipp32f value[3], Ipp32f* pDst, IppSizeL dstStep, IppiSizeL roiSize))

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

IPPAPI(IppStatus, ippiAddC_32f_C1IR_L, (Ipp32f value, Ipp32f* pSrcDst, IppSizeL srcDstStep,IppiSizeL roiSize))
IPPAPI(IppStatus, ippiAddC_32f_C3IR_L, (const Ipp32f value[3], Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiAddC_32f_C4IR_L, (const Ipp32f value[4], Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiAddC_32f_AC4IR_L, (const Ipp32f value[3], Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiSubC_32f_C1IR_L, (Ipp32f value, Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiSubC_32f_C3IR_L, (const Ipp32f value[3], Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiSubC_32f_C4IR_L, (const Ipp32f value[4], Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiSubC_32f_AC4IR_L, (const Ipp32f value[3], Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiMulC_32f_C1IR_L, (Ipp32f value, Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiMulC_32f_C3IR_L, (const Ipp32f value[3], Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiMulC_32f_C4IR_L, (const Ipp32f value[4], Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize))
IPPAPI(IppStatus, ippiMulC_32f_AC4IR_L, (const Ipp32f value[3], Ipp32f* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize))

/* ////////////////////////////////////////////////////////////////////////////////////////////
//  Name: ippiAdd_8u_C1IRSfs_L,  ippiAdd_8u_C3IRSfs_L,  ippiAdd_8u_C4IRSfs_L,  ippiAdd_8u_AC4IRSfs_L,
//        ippiAdd_16s_C1IRSfs_L, ippiAdd_16s_C3IRSfs_L, ippiAdd_16s_C4IRSfs_L, ippiAdd_16s_AC4IRSfs_L,
//        ippiAdd_16u_C1IRSfs_L, ippiAdd_16u_C3IRSfs_L, ippiAdd_16u_C4IRSfs_L, ippiAdd_16u_AC4IRSfs_L,
//        ippiSub_8u_C1IRSfs_L,  ippiSub_8u_C3IRSfs_L,  ippiSub_8u_C4IRSfs_L,  ippiSub_8u_AC4IRSfs_L,
//        ippiSub_16s_C1IRSfs_L, ippiSub_16s_C3IRSfs_L, ippiSub_16s_C4IRSfs_L  ippiSub_16s_AC4IRSfs_L,
//        ippiSub_16u_C1IRSfs_L, ippiSub_16u_C3IRSfs_L, ippiSub_16u_C4IRSfs_L  ippiSub_16u_AC4IRSfs_L,
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
//    pSrc                     Pointer to the source image
//    srcStep                  Step through the second source image
//    pSrcDst                  Pointer to the source/destination image
//    srcDstStep               Step through the source/destination image
//    roiSize                  Size of the ROI
//    scaleFactor              Scale factor
*/

IPPAPI(IppStatus, ippiAdd_8u_C1IRSfs_L,   (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_8u_C3IRSfs_L,   (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_8u_C4IRSfs_L,   (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_8u_AC4IRSfs_L,  (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16s_C1IRSfs_L,  (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16s_C3IRSfs_L,  (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16s_C4IRSfs_L,  (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16s_AC4IRSfs_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16u_C1IRSfs_L,  (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16u_C3IRSfs_L,  (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16u_C4IRSfs_L,  (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAdd_16u_AC4IRSfs_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_8u_C1IRSfs_L,   (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_8u_C3IRSfs_L,   (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_8u_C4IRSfs_L,   (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_8u_AC4IRSfs_L,  (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_16s_C1IRSfs_L,  (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_16s_C3IRSfs_L,  (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_16s_C4IRSfs_L,  (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_16s_AC4IRSfs_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_16u_C1IRSfs_L,  (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_16u_C3IRSfs_L,  (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_16u_C4IRSfs_L,  (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSub_16u_AC4IRSfs_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))

/* /////////////////////////////////////////////////////////////////////////////////////////////
//  Name: ippiAddC_8u_C1RSfs_L,  ippiAddC_8u_C3RSfs_L,  ippiAddC_8u_C4RSfs_L   ippiAddC_8u_AC4RSfs_L,
//        ippiAddC_16s_C1RSfs_L, ippiAddC_16s_C3RSfs_L, ippiAddC_16s_C4RSfs_L, ippiAddC_16s_AC4RSfs_L,
//        ippiAddC_16u_C1RSfs_L, ippiAddC_16u_C3RSfs_L, ippiAddC_16u_C4RSfs_L, ippiAddC_16u_AC4RSfs_L,
//        ippiSubC_8u_C1RSfs_L,  ippiSubC_8u_C3RSfs_L,  ippiSubC_8u_C4RSfs_L,  ippiSubC_8u_AC4RSfs_L,
//        ippiSubC_16s_C1RSfs_L, ippiSubC_16s_C3RSfs_L, ippiSubC_16s_C4RSfs_L, ippiSubC_16s_AC4RSfs_L,
//        ippiSubC_16u_C1RSfs_L, ippiSubC_16u_C3RSfs_L, ippiSubC_16u_C4RSfs_L, ippiSubC_16u_AC4RSfs_L,
//        ippiMulC_8u_C1RSfs_L,  ippiMulC_8u_C3RSfs_L,  ippiMulC_8u_C4RSfs_L,  ippiMulC_8u_AC4RSfs_L,
//        ippiMulC_16s_C1RSfs_L, ippiMulC_16s_C3RSfs_L, ippiMulC_16s_C4RSfs_L, ippiMulC_16s_AC4RSfs_L
//        ippiMulC_16u_C1RSfs_L, ippiMulC_16u_C3RSfs_L, ippiMulC_16u_C4RSfs_L, ippiMulC_16u_AC4RSfs_L
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

IPPAPI(IppStatus, ippiAddC_8u_C1RSfs_L,   (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u value, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_8u_C3RSfs_L,   (const Ipp8u* pSrc, IppSizeL srcStep, const Ipp8u value[3], Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_8u_C4RSfs_L,   (const Ipp8u* pSrc, IppSizeL srcStep, const Ipp8u value[4], Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_8u_AC4RSfs_L,  (const Ipp8u* pSrc, IppSizeL srcStep, const Ipp8u value[3], Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16s_C1RSfs_L,  (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s value, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16s_C3RSfs_L,  (const Ipp16s* pSrc, IppSizeL srcStep, const Ipp16s value[3], Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16s_C4RSfs_L,  (const Ipp16s* pSrc, IppSizeL srcStep, const Ipp16s value[4], Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16s_AC4RSfs_L, (const Ipp16s* pSrc, IppSizeL srcStep, const Ipp16s value[3], Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16u_C1RSfs_L,  (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u value, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16u_C3RSfs_L,  (const Ipp16u* pSrc, IppSizeL srcStep, const Ipp16u value[3], Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16u_C4RSfs_L,  (const Ipp16u* pSrc, IppSizeL srcStep, const Ipp16u value[4], Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16u_AC4RSfs_L, (const Ipp16u* pSrc, IppSizeL srcStep, const Ipp16u value[3], Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_8u_C1RSfs_L,   (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u value, Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_8u_C3RSfs_L,   (const Ipp8u* pSrc, IppSizeL srcStep ,const Ipp8u value[3], Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_8u_C4RSfs_L,   (const Ipp8u* pSrc, IppSizeL srcStep, const Ipp8u value[4], Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_8u_AC4RSfs_L,  (const Ipp8u* pSrc, IppSizeL srcStep, const Ipp8u value[3], Ipp8u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16s_C1RSfs_L,  (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s value, Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16s_C3RSfs_L,  (const Ipp16s* pSrc, IppSizeL srcStep, const Ipp16s value[3], Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16s_C4RSfs_L,  (const Ipp16s* pSrc, IppSizeL srcStep, const Ipp16s value[4], Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16s_AC4RSfs_L, (const Ipp16s* pSrc, IppSizeL srcStep, const Ipp16s value[3], Ipp16s* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16u_C1RSfs_L,  (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u value, Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16u_C3RSfs_L,  (const Ipp16u* pSrc, IppSizeL srcStep, const Ipp16u value[3], Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16u_C4RSfs_L,  (const Ipp16u* pSrc, IppSizeL srcStep, const Ipp16u value[4], Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16u_AC4RSfs_L, (const Ipp16u* pSrc, IppSizeL srcStep, const Ipp16u value[3], Ipp16u* pDst, IppSizeL dstStep, IppiSizeL roiSize, int scaleFactor))

/* //////////////////////////////////////////////////////////////////////////////////////////////
//  Name: ippiAddC_8u_C1IRSfs_L,  ippiAddC_8u_C3IRSfs_L,  ippiAddC_8u_C4IRSfs_L,   ippiAddC_8u_AC4IRSfs_L,
//        ippiAddC_16s_C1IRSfs_L, ippiAddC_16s_C3IRSfs_L, ippiAddC_16s_C4IRSfs_L,  ippiAddC_16s_AC4IRSfs_L,
//        ippiAddC_16u_C1IRSfs_L, ippiAddC_16u_C3IRSfs_L, ippiAddC_16u_C4IRSfs_L,  ippiAddC_16u_AC4IRSfs_L,
//        ippiSubC_8u_C1IRSfs_L,  ippiSubC_8u_C3IRSfs_L,  ippiSubC_8u_C4IRSfs_L,   ippiSubC_8u_AC4IRSfs_L,
//        ippiSubC_16s_C1IRSfs_L, ippiSubC_16s_C3IRSfs_L, ippiSubC_16s_C4IRSfs_L,  ippiSubC_16s_AC4IRSfs_L,
//        ippiSubC_16u_C1IRSfs_L, ippiSubC_16u_C3IRSfs_L, ippiSubC_16u_C4IRSfs_L,  ippiSubC_16u_AC4IRSfs_L,
//        ippiMulC_8u_C1IRSfs_L,  ippiMulC_8u_C3IRSfs_L,  ippiMulC_8u_C4IRSfs_L,   ippiMulC_8u_AC4IRSfs_L,
//        ippiMulC_16s_C1IRSfs_L, ippiMulC_16s_C3IRSfs_L, ippiMulC_16s_C4IRSfs_L,  ippiMulC_16s_AC4IRSfs_L
//        ippiMulC_16u_C1IRSfs_L, ippiMulC_16u_C3IRSfs_L, ippiMulC_16u_C4IRSfs_L,  ippiMulC_16u_AC4IRSfs_L
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

IPPAPI(IppStatus, ippiAddC_8u_C1IRSfs_L,   (Ipp8u value, Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_8u_C3IRSfs_L,   (const Ipp8u value[3], Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_8u_C4IRSfs_L,   (const Ipp8u value[4], Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_8u_AC4IRSfs_L,  (const Ipp8u value[3], Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16s_C1IRSfs_L,  (Ipp16s value, Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16s_C3IRSfs_L,  (const Ipp16s value[3], Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16s_C4IRSfs_L,  (const Ipp16s value[4], Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16s_AC4IRSfs_L, (const Ipp16s value[3], Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16u_C1IRSfs_L,  (Ipp16u value, Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16u_C3IRSfs_L,  (const Ipp16u value[3], Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16u_C4IRSfs_L,  (const Ipp16u value[4], Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiAddC_16u_AC4IRSfs_L, (const Ipp16u value[3], Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_8u_C1IRSfs_L,   (Ipp8u value, Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_8u_C3IRSfs_L,   (const Ipp8u value[3], Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_8u_C4IRSfs_L,   (const Ipp8u value[4], Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_8u_AC4IRSfs_L,  (const Ipp8u value[3], Ipp8u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16s_C1IRSfs_L,  (Ipp16s value, Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16s_C3IRSfs_L,  (const Ipp16s value[3], Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16s_C4IRSfs_L,  (const Ipp16s value[4], Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16s_AC4IRSfs_L, (const Ipp16s value[3], Ipp16s* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16u_C1IRSfs_L,  (Ipp16u value, Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16u_C3IRSfs_L,  (const Ipp16u value[3], Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16u_C4IRSfs_L,  (const Ipp16u value[4], Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))
IPPAPI(IppStatus, ippiSubC_16u_AC4IRSfs_L, (const Ipp16u value[3], Ipp16u* pSrcDst, IppSizeL srcDstStep, IppiSizeL roiSize, int scaleFactor))


/* ///////////////////////////////////////////////////////////////////////////
////             Linear Filters
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//                     Bilateral filter functions with Border
/////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFilterBilateralBorderGetBufferSize_L
//  Purpose:    to define buffer size for bilateral filter
//  Parameters:
//   filter        Type of bilateral filter. Possible value is ippiFilterBilateralGauss.
//   dstRoiSize    Roi size (in pixels) of destination image what will be applied
//                 for processing.
//   radius        Radius of circular neighborhood what defines pixels for calculation.
//   dataType      Data type of the source and destination images. Possible values
//                 are Ipp8u and Ipp32f.
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
IPPAPI(IppStatus, ippiFilterBilateralBorderGetBufferSize_L ,  (IppiFilterBilateralType filter, IppiSizeL dstRoiSize, int radius, IppDataType dataType, int numChannels, IppiDistanceMethodType distMethodType, IppSizeL *pSpecSize, IppSizeL *pBufferSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFilterBilateralBorderInit_L
//  Purpose:    initialization of Spec for bilateral filter with border
//  Parameters:
//   filter           Type of bilateral filter. Possible value is ippiFilterBilateralGauss.
//   dstRoiSize       Roi size (in pixels) of destination image what will be applied
//                    for processing.
//   radius           Radius of circular neighborhood what defines pixels for calculation.
//   dataType         Data type of the source and destination images. Possible values
//                    are Ipp8u and Ipp32f.
//   numChannels      Number of channels in the images. Possible values are 1 and 3.
//   distMethodType   The type of method for definition of distance between pixel intensity.
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
IPPAPI(IppStatus, ippiFilterBilateralBorderInit_L ,(IppiFilterBilateralType filter, IppiSizeL dstRoiSize, int radius, IppDataType dataType, int numChannels, IppiDistanceMethodType distMethod, Ipp32f valSquareSigma, Ipp32f posSquareSigma, IppiFilterBilateralSpec *pSpec))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFilterBilateralBorder_8u_C1R
//              ippiFilterBilateralBorder_8u_C3R
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
//    pBuffer      Pointer to work buffer
//  Return:
//    ippStsNoErr           OK
//    ippStsNullPtrErr      pointer to Src, Dst, Spec or Buffer is NULL
//    ippStsSizeErr         size of dstRoiSize is less or equal 0
//    ippStsContextMatchErr filter Spec is not match
//    ippStsNotEvenStepErr  Indicated an error when one of the step values is not divisible by 4
//                          for floating-point images.
//    ippStsBorderErr       Indicates an error when borderType has illegal value.
*/
IPPAPI(IppStatus, ippiFilterBilateralBorder_8u_C1R_L, (const Ipp8u *pSrc, IppSizeL srcStep, Ipp8u *pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppiBorderType borderType, Ipp8u *pBorderValue, const IppiFilterBilateralSpec *pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterBilateralBorder_8u_C3R_L, (const Ipp8u *pSrc, IppSizeL srcStep, Ipp8u *pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppiBorderType borderType, Ipp8u *pBorderValue, const IppiFilterBilateralSpec *pSpec, Ipp8u* pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//                      Resize Transform Functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeGetSize_L
//  Purpose:            Computes the size of Spec structure and temporal buffer for Resize transform
//
//  Parameters:
//    srcSize           Size of the input image (in pixels)
//    dstSize           Size of the output image (in pixels)
//    dataType          Data type {ipp8u|ipp16u|ipp16s|ipp32f} and ipp64f only for Linear interpolation
//    numChannels       Number of channels, possible values are 1 or 3 or 4
//    interpolation     Interpolation method
//    antialiasing      Supported values:
//                        0 - resizing without antialiasing
//                        1 - resizing with antialiasing
//    pSpecSize         Pointer to the size (in bytes) of the Spec structure
//    pInitBufSize      Pointer to the size (in bytes) of the temporal buffer
//
//  Return Values:
//    ippStsNoErr               Indicates no error
//    ippStsNullPtrErr          Indicates an error if one of the specified pointers is NULL
//    ippStsNoOperation         Indicates a warning if width or height of any image is zero
//    ippStsSizeErr             Indicates an error in the following cases:
//                              -  if width or height of the source or destination image is negative,
//                              -  if the source image size is less than a filter size of the chosen
//                                 interpolation method (except ippSuper)
//                              -  if one of the specified dimensions of the source image is less than
//                                 the corresponding dimension of the destination image (for ippSuper method only)
//    ippStsExceededSizeErr     Indicates an error in the following cases:
//                              -  if one of the calculated sizes exceeds maximum of IppSizeL type positive value
//                                 (the size of the one of the processed images is too large)
//                              -  if one of width or height of the destination image or the source image
//                                 exceeds 33554431 (0x1FFFFFF)
//    ippStsInterpolationErr    Indicates an error if interpolation has an illegal value
//    ippStsDataTypeErr         Indicates an error when dataType has an illegal value
//    ippStsNoAntialiasing      Indicates a warning if specified interpolation does not support antialiasing
//    ippStsNotSupportedModeErr Indicates an error if requested mode is currently not supported
//
//  Notes:
//    1. Supported interpolation methods are ippNearest, ippLinear, ippCubic, ippLanczos and ippSuper.
//    2. If antialiasing value is equal to 1, use the ippResizeAntialiasing<Filter>Init functions, otherwise, use ippResize<Filter>Init
//    3. The implemented interpolation algorithms have the following filter sizes: Nearest Neighbor 1x1,
//       Linear 2x2, Cubic 4x4, 2-lobed Lanczos 4x4.
*/
IPPAPI(IppStatus, ippiResizeGetSize_L, (IppiSizeL srcSize, IppiSizeL dstSize, IppDataType dataType, IppiInterpolationType interpolation, Ipp32u antialiasing, IppSizeL* pSpecSize, IppSizeL* pInitBufSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeGetBufferSize_L
//  Purpose:            Computes the size of external buffer for Resize transform
//
//  Parameters:
//    pSpec             Pointer to the Spec structure for resize filter
//    dstSize           Size of the output image (in pixels)
//    numChannels       Number of channels, possible values are 1 or 3 or 4
//    pBufSize          Pointer to the size (in bytes) of the external buffer
//
//  Return Values:
//    ippStsNoErr               Indicates no error
//    ippStsNullPtrErr          Indicates an error if one of the specified pointers is NULL
//    ippStsContextMatchErr     Indicates an error if pointer to an invalid pSpec structure is passed
//    ippStsNumChannelsErr      Indicates an error if numChannels has illegal value
//    ippStsExceededSizeErr     Indicates an error if one of the calculated sizes exceeds maximum of IppSizeL type
//                              positive value (the size of the one of the processed images is too large)
//    ippStsSizeWrn             Indicates a warning if the destination image size is more than
//                              the destination image origin size
*/
IPPAPI(IppStatus, ippiResizeGetBufferSize_L, (const IppiResizeSpec* pSpec, IppiSizeL dstSize, Ipp32u numChannels, IppSizeL*  pBufSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeGetBorderSize_L
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
IPPAPI(IppStatus, ippiResizeGetBorderSize_L, (const IppiResizeSpec* pSpec, IppiBorderSize* pBorderSize))

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
IPPAPI (IppStatus, ippiResizeGetSrcOffset_L, (const IppiResizeSpec* pSpec, IppiPointL dstOffset, IppiPointL* srcOffset))

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
//                           -  if width or height of the destination image ROI size
//                              is negative or equal to 0,
//    IppStsSizeWrn         Indicates a warning if the destination ROI exceeds with
//                          the destination image origin
*/
IPPAPI (IppStatus, ippiResizeGetSrcRoi_L, (const IppiResizeSpec* pSpec, IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, IppiPointL* srcRoiOffset, IppiSizeL* srcRoiSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeNearestInit_L
//                      ippiResizeLinearInit_L
//                      ippiResizeCubicInit_L
//                      ippiResizeLanczosInit_L
//                      ippiResizeSuperInit_L
//
//  Purpose:            Initializes the Spec structure for the Resize transform
//                      by different interpolation methods
//
//  Parameters:
//    srcSize           Size of the input image (in pixels)
//    dstSize           Size of the output image (in pixels)
//    dataType          Data type {ipp8u|ipp16u|ipp16s|ipp32f} and ipp64f only for Linear interpolation
//    numChannels       Number of channels, possible values are 1 or 3 or 4
//    valueB            The first parameter (B) for specifying Cubic filters
//    valueC            The second parameter (C) for specifying Cubic filters
//    numLobes          The parameter for specifying Lanczos (2 or 3) or Hahn (3 or 4) filters
//    hint              Option to specify the computation algorithm for processing Ipp8u data:
//                        ippAlgHintFast is default for Linear interpolation
//                        ippAlgHintAccurate is default for Cubic and Lanczos interpolations
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
//    ippStsExceededSizeErr     Indicates an error if one of width or height of the destination image or
//                              the source image with borders exceeds 33554431 (0x1FFFFFF)
//    ippStsDataTypeErr         Indicates an error when dataType has an illegal value.
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
IPPAPI(IppStatus, ippiResizeNearestInit_L, (IppiSizeL srcSize, IppiSizeL dstSize, IppDataType dataType, IppiResizeSpec* pSpec))
IPPAPI(IppStatus, ippiResizeLinearInit_L,  (IppiSizeL srcSize, IppiSizeL dstSize, IppDataType dataType, IppiResizeSpec* pSpec))
IPPAPI(IppStatus, ippiResizeCubicInit_L,   (IppiSizeL srcSize, IppiSizeL dstSize, IppDataType dataType, Ipp32f valueB, Ipp32f valueC, IppiResizeSpec* pSpec, Ipp8u* pInitBuf))
IPPAPI(IppStatus, ippiResizeLanczosInit_L, (IppiSizeL srcSize, IppiSizeL dstSize, IppDataType dataType, Ipp32u numLobes, IppiResizeSpec* pSpec, Ipp8u* pInitBuf))
IPPAPI(IppStatus, ippiResizeSuperInit_L,   (IppiSizeL srcSize, IppiSizeL dstSize, IppDataType dataType, IppiResizeSpec* pSpec))

IPPAPI(IppStatus, ippiResizeLinearInit_8u_L, (IppiSizeL srcSize, IppiSizeL dstSize, IppHintAlgorithm hint, IppiResizeSpec* pSpec))
IPPAPI(IppStatus, ippiResizeCubicInit_8u_L, (IppiSizeL srcSize, IppiSizeL dstSize, Ipp32f valueB, Ipp32f valueC, IppHintAlgorithm hint, IppiResizeSpec* pSpec, Ipp8u* pInitBuf))
IPPAPI(IppStatus, ippiResizeLanczosInit_8u_L, (IppiSizeL srcSize, IppiSizeL dstSize, Ipp32u numLobes, IppHintAlgorithm hint, IppiResizeSpec* pSpec, Ipp8u* pInitBuf))

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
//    ippStsSizeWrn             Indicates a warning if the destination image size is more than
//                              the destination image origin size
//
//  Notes:
//    1. Supported border types are ippBorderInMem and ippBorderRepl
//       (except Nearest Neighbor and Super Sampling methods).
//    2. Hahn filter does not supported now.
*/
IPPAPI(IppStatus, ippiResizeNearest_8u_C1R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiResizeNearest_8u_C3R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiResizeNearest_8u_C4R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiResizeNearest_16u_C1R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiResizeNearest_16u_C3R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiResizeNearest_16u_C4R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiResizeNearest_16s_C1R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiResizeNearest_16s_C3R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiResizeNearest_16s_C4R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiResizeNearest_32f_C1R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiResizeNearest_32f_C3R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiResizeNearest_32f_C4R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))

IPPAPI (IppStatus, ippiResizeLinear_8u_C1R_L,  (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp8u* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_8u_C3R_L,  (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp8u* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_8u_C4R_L,  (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp8u* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_16u_C1R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp16u* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_16u_C3R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp16u* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_16u_C4R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp16u* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_16s_C1R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp16s* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_16s_C3R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp16s* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_16s_C4R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp16s* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_32f_C1R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp32f* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_32f_C3R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp32f* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_32f_C4R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp32f* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_64f_C1R_L, (const Ipp64f* pSrc, IppSizeL srcStep, Ipp64f* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp64f* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_64f_C3R_L, (const Ipp64f* pSrc, IppSizeL srcStep, Ipp64f* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp64f* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLinear_64f_C4R_L, (const Ipp64f* pSrc, IppSizeL srcStep, Ipp64f* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp64f* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))

IPPAPI (IppStatus, ippiResizeCubic_8u_C1R_L,  (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp8u* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeCubic_8u_C3R_L,  (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp8u* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeCubic_8u_C4R_L,  (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp8u* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeCubic_16u_C1R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp16u* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeCubic_16u_C3R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp16u* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeCubic_16u_C4R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp16u* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeCubic_16s_C1R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp16s* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeCubic_16s_C3R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp16s* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeCubic_16s_C4R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp16s* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeCubic_32f_C1R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp32f* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeCubic_32f_C3R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp32f* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeCubic_32f_C4R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp32f* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))

IPPAPI (IppStatus, ippiResizeLanczos_8u_C1R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp8u* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLanczos_8u_C3R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp8u* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLanczos_8u_C4R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp8u* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLanczos_16u_C1R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp16u* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLanczos_16u_C3R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp16u* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLanczos_16u_C4R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp16u* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLanczos_16s_C1R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp16s* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLanczos_16s_C3R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp16s* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLanczos_16s_C4R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp16s* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLanczos_32f_C1R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp32f* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLanczos_32f_C3R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp32f* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeLanczos_32f_C4R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp32f* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))

IPPAPI (IppStatus, ippiResizeSuper_8u_C1R_L,  (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeSuper_8u_C3R_L,  (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeSuper_8u_C4R_L,  (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeSuper_16u_C1R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeSuper_16u_C3R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeSuper_16u_C4R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeSuper_16s_C1R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeSuper_16s_C3R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeSuper_16s_C4R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeSuper_32f_C1R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeSuper_32f_C3R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeSuper_32f_C4R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiResizeNearestAntialiasingInit_L
//                      ippiResizeLinearAntialiasingInit_L
//                      ippiResizeCubicAntialiasingInit_L
//
//  Purpose:            Initializes the Spec structure for the Resize transform
//                      with antialiasing by different interpolation methods
//
//  Parameters:
//    srcSize           Size of the input image (in pixels)
//    dstSize           Size of the output image (in pixels)
//    dataType          Data type {ipp8u|ipp16u|ipp16s|ipp32f}
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
//    ippStsSizeErr             Indicates an error if width or height of the source image is negative
//    ippStsExceededSizeErr     Indicates an error if one of width or height of the destination image or
//                              the source image with borders exceeds 33554431 (0x1FFFFFF)
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
//    3. The implemented interpolation algorithms have the following filter sizes:
//       Linear 2x2, Cubic 4x4, 2-lobed Lanczos 4x4, 3-lobed Lanczos 6x6.
*/

IPPAPI (IppStatus, ippiResizeAntialiasingLinearInit_L, (IppiSizeL srcSize, IppiSizeL dstSize, IppDataType dataType, IppiResizeSpec* pSpec, Ipp8u* pInitBuf))
IPPAPI (IppStatus, ippiResizeAntialiasingCubicInit_L, (IppiSizeL srcSize, IppiSizeL dstSize, IppDataType dataType, Ipp32f valueB, Ipp32f valueC, IppiResizeSpec* pSpec, Ipp8u* pInitBuf))
IPPAPI (IppStatus, ippiResizeAntialiasingLanczosInit_L, (IppiSizeL srcSize, IppiSizeL dstSize, IppDataType dataType, Ipp32u numLobes, IppiResizeSpec* pSpec, Ipp8u* pInitBuf))


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
//    ippStsBorderErr           Indicates an error if border type has an illegal value
//    ippStsContextMatchErr     Indicates an error if pointer to an invalid pSpec structure is passed
//    ippStsNotSupportedModeErr Indicates an error if requested mode is currently not supported
//    ippStsStepErr             Indicates an error if the step value is not data type multiple
//    ippStsOutOfRangeErr       Indicates an error if the destination image offset point is outside the
//                              destination image origin
//    ippStsSizeWrn             Indicates a warning if the destination image size is more than
//                              the destination image origin size
//
//  Notes:
//    1. Supported border types are ippBorderInMemory and ippBorderReplicate.
//    2. Hahn filter does not supported now.
*/
IPPAPI (IppStatus, ippiResizeAntialiasing_8u_C1R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp8u* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeAntialiasing_8u_C3R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp8u* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeAntialiasing_8u_C4R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp8u* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeAntialiasing_16u_C1R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp16u* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeAntialiasing_16u_C3R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp16u* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeAntialiasing_16u_C4R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp16u* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeAntialiasing_16s_C1R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp16s* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeAntialiasing_16s_C3R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp16s* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeAntialiasing_16s_C4R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp16s* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeAntialiasing_32f_C1R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp32f* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeAntialiasing_32f_C3R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp32f* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiResizeAntialiasing_32f_C4R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep, IppiPointL dstOffset, IppiSizeL dstSize, IppiBorderType border, const Ipp32f* pBorderValue, const IppiResizeSpec* pSpec, Ipp8u* pBuffer))

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
IPPAPI (IppStatus, ippiWarpGetBufferSize_L, (const IppiWarpSpec* pSpec, IppiSizeL dstRoiSize, IppSizeL* pBufSize))


/* /////////////////////////////////////////////////////////////////////////////
//                     Warp Affine Transform functions
// ////////////////////////////////////////////////////////////////////////// */

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
//    ippStsNoErr               Indicates no error
//    ippStsNullPtrErr          Indicates an error if one of the specified pointers is NULL
*/

IPPAPI(IppStatus, ippiGetAffineBound_L, (
    IppiRectL srcROI, double bound[2][2], const double coeffs[2][3]))

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
//    ippStsNoErr               Indicates no error
//    ippStsNullPtrErr          Indicates an error if one of the specified pointers is NULL
*/

IPPAPI(IppStatus, ippiGetAffineQuad_L, (
    IppiRectL srcROI, double quad[4][2], const double coeffs[2][3]))

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
//    ippStsNoErr               Indicates no error
//    ippStsNullPtrErr          Indicates an error if one of the specified pointers is NULL
//    ippStsAffineQuadChanged   Indicates an warning if the computed coordinates of the 4th
//                              vertex of the quadrangle are not equal to the ones specified
//                              in the specified quad
*/

IPPAPI(IppStatus, ippiGetAffineTransform_L, (
    IppiRectL srcROI, const double quad[4][2], double coeffs[2][3]))

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
IPPAPI(IppStatus, ippiGetAffineSrcRoi_L, (IppiSizeL srcSize, const double coeffs[2][3], IppiWarpDirection direction, IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, IppiRectL *srcRoi))

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
IPPAPI(IppStatus, ippiGetRotateShift_L, (double xCenter, double yCenter, double angle, double *xShift, double *yShift))


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

IPPAPI(IppStatus, ippiGetRotateTransform_L, (double angle, double xShift, double yShift, double coeffs[2][3]))


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
//    flags             The following flags are supported:
//                          0 - transform without edge smoothing
//                          1 - transform with edge smoothing
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
//                              -  if width or height of the source or destination image is negative,
//    ippStsDataTypeErr         Indicates an error when dataType has an illegal value.
//    ippStsWarpDirectionErr    Indicates an error when the direction value is illegal.
//    ippStsInterpolationErr    Indicates an error if interpolation has an illegal value
//    ippStsNotSupportedModeErr Indicates an error if the requested mode is not supported.
//    ippStsCoeffErr            Indicates an error condition, if affine transformation is singular.
//    ippStsBorderErr           Indicates an error if border type has an illegal value
//    ippStsExceededSizeErr     Indicates an error in the following cases:
//                              -  if one of the calculated sizes exceeds maximum of IppSizeL type positive value
//                                 (the size of the one of the processed images is too large)
//                              -  if one of width or height of the destination image or the source image
//                                 exceeds 33554431 (0x1FFFFFF)
*/
IPPAPI (IppStatus, ippiWarpAffineGetSize_L, (IppiSizeL srcSize, IppiSizeL dstSize, IppDataType dataType, const double coeffs[2][3],
                                             IppiInterpolationType interpolation, IppiWarpDirection direction,
                                             IppiBorderType borderType, int flags, IppSizeL* pSpecSize, IppSizeL* pInitBufSize))

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
//    flags             The following flags are supported:
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
IPPAPI (IppStatus, ippiWarpAffineNearestInit_L, (IppiSizeL srcSize, IppiSizeL dstSize, IppDataType dataType, const double coeffs[2][3],
                                                 IppiWarpDirection direction, int numChannels, IppiBorderType borderType,
                                                 const Ipp64f *pBorderValue, int flags, IppiWarpSpec* pSpec))
IPPAPI (IppStatus, ippiWarpAffineLinearInit_L, (IppiSizeL srcSize, IppiSizeL dstSize, IppDataType dataType, const double coeffs[2][3],
                                                IppiWarpDirection direction, int numChannels, IppiBorderType borderType,
                                                const Ipp64f *pBorderValue, int flags, IppiWarpSpec* pSpec))
IPPAPI (IppStatus, ippiWarpAffineCubicInit_L, (IppiSizeL srcSize, IppiSizeL dstSize, IppDataType dataType, const double coeffs[2][3],
                                               IppiWarpDirection direction, int numChannels, Ipp64f valueB, Ipp64f valueC,
                                               IppiBorderType borderType, const Ipp64f *pBorderValue, int flags, IppiWarpSpec* pSpec,
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
IPPAPI (IppStatus, ippiWarpAffineNearest_8u_C1R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep,
                                                    IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                    Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_8u_C3R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep,
                                                    IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                    Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_8u_C4R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep,
                                                    IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                    Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_16u_C1R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep,
                                                     IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                     Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_16u_C3R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep,
                                                     IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                     Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_16u_C4R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep,
                                                     IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                     Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_16s_C1R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep,
                                                     IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                     Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_16s_C3R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep,
                                                     IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                     Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_16s_C4R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep,
                                                     IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                     Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_32f_C1R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep,
                                                     IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                     Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_32f_C3R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep,
                                                     IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                     Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_32f_C4R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep,
                                                     IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                     Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_64f_C1R_L, (const Ipp64f* pSrc, IppSizeL srcStep, Ipp64f* pDst, IppSizeL dstStep,
                                                     IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                     Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_64f_C3R_L, (const Ipp64f* pSrc, IppSizeL srcStep, Ipp64f* pDst, IppSizeL dstStep,
                                                     IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                     Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineNearest_64f_C4R_L, (const Ipp64f* pSrc, IppSizeL srcStep, Ipp64f* pDst, IppSizeL dstStep,
                                                     IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                     Ipp8u* pBuffer))

IPPAPI (IppStatus, ippiWarpAffineLinear_8u_C1R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep,
                                                   IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_8u_C3R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep,
                                                   IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_8u_C4R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep,
                                                   IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_16u_C1R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep,
                                                    IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                    Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_16u_C3R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep,
                                                    IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                    Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_16u_C4R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep,
                                                    IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                    Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_16s_C1R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep,
                                                    IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                    Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_16s_C3R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep,
                                                    IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                    Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_16s_C4R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep,
                                                    IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                    Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_32f_C1R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep,
                                                    IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                    Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_32f_C3R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep,
                                                    IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                    Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_32f_C4R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep,
                                                    IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                    Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_64f_C1R_L, (const Ipp64f* pSrc, IppSizeL srcStep, Ipp64f* pDst, IppSizeL dstStep,
                                                    IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                    Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_64f_C3R_L, (const Ipp64f* pSrc, IppSizeL srcStep, Ipp64f* pDst, IppSizeL dstStep,
                                                    IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                    Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineLinear_64f_C4R_L, (const Ipp64f* pSrc, IppSizeL srcStep, Ipp64f* pDst, IppSizeL dstStep,
                                                    IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                    Ipp8u* pBuffer))

IPPAPI (IppStatus, ippiWarpAffineCubic_8u_C1R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep,
                                                  IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_8u_C3R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep,
                                                  IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_8u_C4R_L, (const Ipp8u* pSrc, IppSizeL srcStep, Ipp8u* pDst, IppSizeL dstStep,
                                                  IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                  Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_16u_C1R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep,
                                                   IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_16u_C3R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep,
                                                   IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_16u_C4R_L, (const Ipp16u* pSrc, IppSizeL srcStep, Ipp16u* pDst, IppSizeL dstStep,
                                                   IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_16s_C1R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep,
                                                   IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_16s_C3R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep,
                                                   IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_16s_C4R_L, (const Ipp16s* pSrc, IppSizeL srcStep, Ipp16s* pDst, IppSizeL dstStep,
                                                   IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_32f_C1R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep,
                                                   IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_32f_C3R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep,
                                                   IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_32f_C4R_L, (const Ipp32f* pSrc, IppSizeL srcStep, Ipp32f* pDst, IppSizeL dstStep,
                                                   IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_64f_C1R_L, (const Ipp64f* pSrc, IppSizeL srcStep, Ipp64f* pDst, IppSizeL dstStep,
                                                   IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_64f_C3R_L, (const Ipp64f* pSrc, IppSizeL srcStep, Ipp64f* pDst, IppSizeL dstStep,
                                                   IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                   Ipp8u* pBuffer))
IPPAPI (IppStatus, ippiWarpAffineCubic_64f_C4R_L, (const Ipp64f* pSrc, IppSizeL srcStep, Ipp64f* pDst, IppSizeL dstStep,
                                                    IppiPointL dstRoiOffset, IppiSizeL dstRoiSize, const IppiWarpSpec* pSpec,
                                                    Ipp8u* pBuffer))

/*****************************************************************************************************
// 3D General filter with border
//  Name:
//   ipprFilterBorderGetSize_L
//   ipprFilterBorderInit_16s_L
//   ipprFilterBorderInit_32f_L
//   ipprFilterBorderInit_64f_L
//   ipprFilterBorder_8u_C1V_L
//   ipprFilterBorder_16s_C1V_L
//   ipprFilterBorder_16u_C1V_L
//   ipprFilterBorder_32f_C1V_L
//   ipprFilterBorder_64f_C1V_L
//  Purpose:    Filters an 3D image using a general integer rectangular kernel volume
//  Returns:
//   ippStsNoErr       OK
//   ippStsNullPtrErr  One of the pointers is NULL
//   ippStsSizeErr     dstRoiVolume or kernelVolume has a field with zero or negative value
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
//      dataType    Data type {ipp8u|ipp16u|ipp26s|ipp32f|ipp64f}
//      numChannels Number of channels, possible values are 1
//      pSpecSize   Pointer to the size (in bytes) of the spec structure
//      pBufferSize    Pointer to the size (in bytes) of the external buffer
//      pSpec       Pointer to pointer to the allocated and initialized context structure
//      borderType  Type of the border
//      borderValue Pointer to the constant value(s) if border type equals ippBorderConstant
//      pBuffer     Pointer to the work buffer. It can be equal to NULL if optimization algorithm doesn't demand a work buffer
*/

IPPAPI(IppStatus, ipprFilterBorderGetSize_L,  (IpprVolumeL kernelVolume, IpprVolumeL dstRoiVolume, IppDataType dataType, IppDataType kernelType, int numChannels, IppSizeL* pSpecSize, IppSizeL* pBufferSize))
IPPAPI(IppStatus, ipprFilterBorderInit_16s_L, (const Ipp16s* pKernel, IpprVolumeL  kernelVolume, int divisor, IppDataType dataType, int numChannels, IpprFilterBorderSpec* pSpec ))
IPPAPI(IppStatus, ipprFilterBorderInit_32f_L, (const Ipp32f* pKernel, IpprVolumeL  kernelVolume,              IppDataType dataType, int numChannels, IpprFilterBorderSpec* pSpec ))
IPPAPI(IppStatus, ipprFilterBorderInit_64f_L, (const Ipp64f* pKernel, IpprVolumeL  kernelVolume,              IppDataType dataType, int numChannels, IpprFilterBorderSpec* pSpec ))
IPPAPI(IppStatus, ipprFilterBorder_8u_C1V_L,  (const Ipp8u*  pSrc, IppSizeL srcPlaneStep, IppSizeL srcStep,  Ipp8u*  pDst, IppSizeL dstPlaneStep, IppSizeL dstStep,  IpprVolumeL dstRoiVolume, IpprBorderType borderType, const Ipp8u  borderValue[1], const IpprFilterBorderSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ipprFilterBorder_16s_C1V_L, (const Ipp16s* pSrc, IppSizeL srcPlaneStep, IppSizeL srcStep,  Ipp16s* pDst, IppSizeL dstPlaneStep, IppSizeL dstStep,  IpprVolumeL dstRoiVolume, IpprBorderType borderType, const Ipp16s borderValue[1], const IpprFilterBorderSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ipprFilterBorder_16u_C1V_L, (const Ipp16u* pSrc, IppSizeL srcPlaneStep, IppSizeL srcStep,  Ipp16u* pDst, IppSizeL dstPlaneStep, IppSizeL dstStep,  IpprVolumeL dstRoiVolume, IpprBorderType borderType, const Ipp16u borderValue[1], const IpprFilterBorderSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ipprFilterBorder_32f_C1V_L, (const Ipp32f* pSrc, IppSizeL srcPlaneStep, IppSizeL srcStep,  Ipp32f* pDst, IppSizeL dstPlaneStep, IppSizeL dstStep,  IpprVolumeL dstRoiVolume, IpprBorderType borderType, const Ipp32f borderValue[1], const IpprFilterBorderSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ipprFilterBorder_64f_C1V_L, (const Ipp64f* pSrc, IppSizeL srcPlaneStep, IppSizeL srcStep,  Ipp64f* pDst, IppSizeL dstPlaneStep, IppSizeL dstStep,  IpprVolumeL dstRoiVolume, IpprBorderType borderType, const Ipp64f borderValue[1], const IpprFilterBorderSpec* pSpec, Ipp8u* pBuffer))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:
// ipprCopyConstBorder_8u_C1V_L
// ipprCopyConstBorder_16u_C1V_L
// ipprCopyConstBorder_16s_C1V_L
// ipprCopyConstBorder_32f_C1V_L
// ipprCopyConstBorder_64f_C1V_L
// ipprCopyReplicateBorder_8u_C1V_L
// ipprCopyReplicateBorder_16u_C1V_L
// ipprCopyReplicateBorder_16s_C1V_L
// ipprCopyReplicateBorder_32f_C1V_L
// ipprCopyReplicateBorder_64f_C1V_L

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

IPPAPI(IppStatus, ipprCopyConstBorder_8u_C1V_L , (const Ipp8u*  pSrc, IppSizeL srcPlaneStep, IppSizeL srcStep, IpprVolumeL srcRoiVolume, Ipp8u*  pDst, IppSizeL dstPlaneStep, IppSizeL dstStep, IpprVolumeL dstRoiVolume, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, IppSizeL forwardBorderDepth, const Ipp8u* value))
IPPAPI(IppStatus, ipprCopyConstBorder_16u_C1V_L, (const Ipp16u* pSrc, IppSizeL srcPlaneStep, IppSizeL srcStep, IpprVolumeL srcRoiVolume, Ipp16u* pDst, IppSizeL dstPlaneStep, IppSizeL dstStep, IpprVolumeL dstRoiVolume, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, IppSizeL forwardBorderDepth, const Ipp16u* value))
IPPAPI(IppStatus, ipprCopyConstBorder_16s_C1V_L, (const Ipp16s* pSrc, IppSizeL srcPlaneStep, IppSizeL srcStep, IpprVolumeL srcRoiVolume, Ipp16s* pDst, IppSizeL dstPlaneStep, IppSizeL dstStep, IpprVolumeL dstRoiVolume, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, IppSizeL forwardBorderDepth, const Ipp16s* value))
IPPAPI(IppStatus, ipprCopyConstBorder_32f_C1V_L, (const Ipp32f* pSrc, IppSizeL srcPlaneStep, IppSizeL srcStep, IpprVolumeL srcRoiVolume, Ipp32f* pDst, IppSizeL dstPlaneStep, IppSizeL dstStep, IpprVolumeL dstRoiVolume, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, IppSizeL forwardBorderDepth, const Ipp32f* value))
IPPAPI(IppStatus, ipprCopyConstBorder_64f_C1V_L, (const Ipp64f* pSrc, IppSizeL srcPlaneStep, IppSizeL srcStep, IpprVolumeL srcRoiVolume, Ipp64f* pDst, IppSizeL dstPlaneStep, IppSizeL dstStep, IpprVolumeL dstRoiVolume, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, IppSizeL forwardBorderDepth, const Ipp64f* value))
IPPAPI(IppStatus, ipprCopyReplicateBorder_8u_C1V_L , (const Ipp8u*  pSrc, IppSizeL srcPlaneStep, IppSizeL srcStep, IpprVolumeL srcRoiVolume, Ipp8u*  pDst, IppSizeL dstPlaneStep, IppSizeL dstStep, IpprVolumeL dstRoiVolume, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, IppSizeL forwardBorderDepth))
IPPAPI(IppStatus, ipprCopyReplicateBorder_16u_C1V_L, (const Ipp16u* pSrc, IppSizeL srcPlaneStep, IppSizeL srcStep, IpprVolumeL srcRoiVolume, Ipp16u* pDst, IppSizeL dstPlaneStep, IppSizeL dstStep, IpprVolumeL dstRoiVolume, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, IppSizeL forwardBorderDepth))
IPPAPI(IppStatus, ipprCopyReplicateBorder_16s_C1V_L, (const Ipp16s* pSrc, IppSizeL srcPlaneStep, IppSizeL srcStep, IpprVolumeL srcRoiVolume, Ipp16s* pDst, IppSizeL dstPlaneStep, IppSizeL dstStep, IpprVolumeL dstRoiVolume, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, IppSizeL forwardBorderDepth))
IPPAPI(IppStatus, ipprCopyReplicateBorder_32f_C1V_L, (const Ipp32f* pSrc, IppSizeL srcPlaneStep, IppSizeL srcStep, IpprVolumeL srcRoiVolume, Ipp32f* pDst, IppSizeL dstPlaneStep, IppSizeL dstStep, IpprVolumeL dstRoiVolume, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, IppSizeL forwardBorderDepth))
IPPAPI(IppStatus, ipprCopyReplicateBorder_64f_C1V_L, (const Ipp64f* pSrc, IppSizeL srcPlaneStep, IppSizeL srcStep, IpprVolumeL srcRoiVolume, Ipp64f* pDst, IppSizeL dstPlaneStep, IppSizeL dstStep, IpprVolumeL dstRoiVolume, IppSizeL topBorderHeight, IppSizeL leftBorderWidth, IppSizeL forwardBorderDepth))

/* /////////////////////////////////////////////////////////////////////////////
//                     Bilateral filter functions with Border and square mask
// /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFilterBilateralGetBufferSize_L
//  Purpose:    to define buffer size for bilateral filter
//  Name:       ippiFilterBilateralInit_L
//  Purpose:    initialization of Spec for bilateral filter with border
//  Name:
                ippiFilterBilateral_8u_C1R_L
                ippiFilterBilateral_8u_C3R_L
                ippiFilterBilateral_32f_C1R_L
                ippiFilterBilateral_32f_C3R_L
                ippiFilterBilateral_64f_C1R_L
                ippiFilterBilateral_64f_C3R_L
                ippiFilterBilateral_8u_P3R_L
                ippiFilterBilateral_32f_P3R_L
                ippiFilterBilateral_64f_P3R_L
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
IPPAPI(IppStatus, ippiFilterBilateralGetBufferSize_L, (IppiFilterBilateralType filter, IppiSizeL dstRoiSize, IppSizeL kernelWidthHeight, IppDataType dataType, int numChannels, IppiDistanceMethodType distMethodType, IppSizeL *pSpecSize, IppSizeL *pBufferSize))
IPPAPI(IppStatus, ippiFilterBilateralInit_L, (IppiFilterBilateralType filter, IppiSizeL dstRoiSize, IppSizeL kernelWidthHeight, IppDataType dataType, int numChannels, IppiDistanceMethodType distMethod, Ipp64f valSquareSigma, Ipp64f posSquareSigma, IppiFilterBilateralSpec *pSpec))
IPPAPI(IppStatus, ippiFilterBilateral_8u_C1R_L, (const Ipp8u  *pSrc, IppSizeL srcStep, Ipp8u  *pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppiBorderType borderType, const Ipp8u  pBorderValue[1], const IppiFilterBilateralSpec *pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterBilateral_8u_C3R_L, (const Ipp8u  *pSrc, IppSizeL srcStep, Ipp8u  *pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppiBorderType borderType, const Ipp8u  pBorderValue[3], const IppiFilterBilateralSpec *pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterBilateral_32f_C1R_L, (const Ipp32f *pSrc, IppSizeL srcStep, Ipp32f *pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppiBorderType borderType, const Ipp32f pBorderValue[1], const IppiFilterBilateralSpec *pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterBilateral_32f_C3R_L, (const Ipp32f *pSrc, IppSizeL srcStep, Ipp32f *pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppiBorderType borderType, const Ipp32f pBorderValue[3], const IppiFilterBilateralSpec *pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterBilateral_64f_C1R_L, (const Ipp64f *pSrc, IppSizeL srcStep, Ipp64f *pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppiBorderType borderType, const Ipp64f pBorderValue[1], const IppiFilterBilateralSpec *pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterBilateral_64f_C3R_L, (const Ipp64f *pSrc, IppSizeL srcStep, Ipp64f *pDst, IppSizeL dstStep, IppiSizeL dstRoiSize, IppiBorderType borderType, const Ipp64f pBorderValue[3], const IppiFilterBilateralSpec *pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterBilateral_8u_P3R_L,  (const Ipp8u*  pSrc[3], IppSizeL srcStep[3], Ipp8u*  pDst[3], IppSizeL dstStep[3], IppiSizeL dstRoiSize, IppiBorderType borderType, const Ipp8u  pBorderValue[3], const IppiFilterBilateralSpec *pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterBilateral_32f_P3R_L,  (const Ipp32f* pSrc[3], IppSizeL srcStep[3], Ipp32f* pDst[3], IppSizeL dstStep[3], IppiSizeL dstRoiSize, IppiBorderType borderType, const Ipp32f pBorderValue[3], const IppiFilterBilateralSpec *pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterBilateral_64f_P3R_L,  (const Ipp64f* pSrc[3], IppSizeL srcStep[3], Ipp64f* pDst[3], IppSizeL dstStep[3], IppiSizeL dstRoiSize, IppiBorderType borderType, const Ipp64f pBorderValue[3], const IppiFilterBilateralSpec *pSpec, Ipp8u* pBuffer))
#ifdef __cplusplus
}
#endif

#endif /* IPPI_L_H__ */
