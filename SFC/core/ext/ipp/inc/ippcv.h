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
//              Computer Vision (ippCV)
//
//
*/


#if !defined( IPPCV_H__ ) || defined( _OWN_BLDPCS )
#define IPPCV_H__

#ifndef IPPDEFS_H__
  #include "ippdefs.h"
#endif

#include "ippcv_l.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined( IPP_NO_DEFAULT_LIB )
  #if defined( _IPP_SEQUENTIAL_DYNAMIC )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippcv" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippcore" )
  #elif defined( _IPP_SEQUENTIAL_STATIC )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippcvmt" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippimt" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippsmt" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippvmmt" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippcoremt" )
  #elif defined( _IPP_PARALLEL_DYNAMIC )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippcv" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippcore" )
  #elif defined( _IPP_PARALLEL_STATIC )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippcvmt" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippimt" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippsmt" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippvmmt" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippcoremt" )
  #endif
#endif



/* ///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//                   Functions declarations
//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////// */

/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippcvGetLibVersion
//
//  Purpose:    getting of the library version
//
//  Returns:    the structure of information about  version of ippcv library
//
//  Parameters:
//
//  Notes:      not necessary to release the returned structure
*/
IPPAPI( const IppLibraryVersion*, ippcvGetLibVersion, (void) )


/****************************************************************************************\
*                               Copy with Subpixel Precision                             *
\****************************************************************************************/


/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name: ippiCopySubpix_8u_C1R,              ippiCopySubpix_16u_C1R,
//        ippiCopySubpix_8u16u_C1R_Sfs,       ippiCopySubpix_16u32f_C1R,
//        ippiCopySubpix_8u32f_C1R,           ippiCopySubpix_32f_C1R
//
//  Purpose:   copies source image to destination image with interpolation
//
//  Returns:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//
//  Parameters:
//    pSrc                     Pointer to source image
//    srcStep                  Step in source image
//    pDst                     Pointer to destination image
//    dstStep                  Step in destination image
//    roiSize                  Source and destination image ROI size.
//    dx                       x coeff of linear interpolation
//    dy                       y coeff of linear interpolation
//    scaleFactor              Output scale factor, >= 0
//
//  Notes:
//F*/

IPPAPI(IppStatus, ippiCopySubpix_8u_C1R,        (const Ipp8u* pSrc, int srcStep,
                  Ipp8u* pDst, int dstStep, IppiSize roiSize, Ipp32f dx, Ipp32f dy))

IPPAPI(IppStatus, ippiCopySubpix_8u16u_C1R_Sfs, (const Ipp8u* pSrc, int srcStep,
                  Ipp16u* pDst, int dstStep, IppiSize roiSize, Ipp32f dx, Ipp32f dy, int scaleFactor))

IPPAPI(IppStatus, ippiCopySubpix_8u32f_C1R,     (const Ipp8u* pSrc, int srcStep,
                  Ipp32f* pDst, int dstStep, IppiSize roiSize, Ipp32f dx, Ipp32f dy))

IPPAPI(IppStatus, ippiCopySubpix_16u_C1R,       (const Ipp16u* pSrc, int srcStep,
                  Ipp16u* pDst, int dstStep, IppiSize roiSize, Ipp32f dx, Ipp32f dy))

IPPAPI(IppStatus, ippiCopySubpix_16u32f_C1R,    (const Ipp16u* pSrc, int srcStep,
                  Ipp32f* pDst, int dstStep, IppiSize roiSize, Ipp32f dx, Ipp32f dy))

IPPAPI(IppStatus, ippiCopySubpix_32f_C1R,       (const Ipp32f* pSrc, int srcStep,
                  Ipp32f* pDst, int dstStep, IppiSize roiSize, Ipp32f dx, Ipp32f dy))


/*F////////////////////////////////////////////////////////////////////////////////////////////////
//  Name: ippiCopySubpixIntersect_8u_C1R,              ippiCopySubpixIntersect_16u_C1R,
//        ippiCopySubpixIntersect_8u16u_C1R_Sfs,       ippiCopySubpixIntersect_16u32f_C1R,
//        ippiCopySubpixIntersect_8u32f_C1R,           ippiCopySubpixIntersect_32f_C1R
//
//  Purpose:   finds intersection of centered window in the source image and copies
//             in to destination image with the border
//             border pixel are taken from the source image or replicated if they are outside it
//
//  Returns:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//
//  Parameters:
//    pSrc                     Pointer to source image
//    srcStep                  Step in source image
//    srcRoiSize               Source image ROI size.
//    pDst                     Pointer to destination image
//    dstStep                  Step in destination image
//    dstRoiSize               Destination image ROI size.
//    point                    Center of dst window in src image (subpixel)
//    pMin                     Top left corner of dst filled part
//    pMax                     Bottom right corner of dst filled part
//    scaleFactor              Output scale factor, >= 0
//
//  Notes:                     For integer point.x or point.y pixels from the last row
//                             or column are not copied. Branches are possible.
//F*/

IPPAPI(IppStatus, ippiCopySubpixIntersect_8u_C1R,        (const Ipp8u* pSrc, int srcStep,
                  IppiSize srcRoiSize, Ipp8u* pDst, int dstStep, IppiSize dstRoiSize,
                  IppiPoint_32f point, IppiPoint *pMin, IppiPoint *pMax))

IPPAPI(IppStatus, ippiCopySubpixIntersect_8u16u_C1R_Sfs, (const Ipp8u* pSrc, int srcStep,
                  IppiSize srcRoiSize, Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,
                  IppiPoint_32f point, IppiPoint *pMin, IppiPoint *pMax, int scaleFactor))

IPPAPI(IppStatus, ippiCopySubpixIntersect_8u32f_C1R,     (const Ipp8u* pSrc, int srcStep,
                  IppiSize srcRoiSize, Ipp32f* pDst, int dstStep, IppiSize dstRoiSize,
                  IppiPoint_32f point, IppiPoint *pMin, IppiPoint *pMax))

IPPAPI(IppStatus, ippiCopySubpixIntersect_16u_C1R,       (const Ipp16u* pSrc, int srcStep,
                  IppiSize srcRoiSize, Ipp16u* pDst, int dstStep, IppiSize dstRoiSize,
                  IppiPoint_32f point, IppiPoint *pMin, IppiPoint *pMax))

IPPAPI(IppStatus, ippiCopySubpixIntersect_16u32f_C1R,    (const Ipp16u* pSrc, int srcStep,
                  IppiSize srcRoiSize, Ipp32f* pDst, int dstStep, IppiSize dstRoiSize,
                  IppiPoint_32f point, IppiPoint *pMin, IppiPoint *pMax))

IPPAPI(IppStatus, ippiCopySubpixIntersect_32f_C1R,       (const Ipp32f* pSrc, int srcStep,
                  IppiSize srcRoiSize, Ipp32f* pDst, int dstStep, IppiSize dstRoiSize,
                  IppiPoint_32f point, IppiPoint *pMin, IppiPoint *pMax))


/****************************************************************************************\
*                                     Line sampling                                      *
\****************************************************************************************/

/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name:    ippiSampleLine_8u_C1R, ippiSampleLine_8u_C3R,
//           ippiSampleLine_16u_C1R, ippiSampleLine_16u_C3R,
//           ippiSampleLine_32f_C1R, ippiSampleLine_32f_C3R,
//
//  Purpose: Reads values of pixels on the raster
//           line between two given points and write them to buffer.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//    ippStsOutOfRangeErr      At least one of the points is outside the image ROI.
//
//  Parameters:
//    pSrc                     Source image
//    srcStep                  Its step
//    roiSize                  ROI size
//    pBuffer                  Pointer to buffer where the pixels are stored.
//                             It must have size >= max(abs(pt2.y - pt1.y)+1,
//                                                      abs(pt2.x - pt1.x)+1)*
//                                                  <size_of_pixel>.
//    pt1                      Starting point of the line segment.
//                             The pixel value will be stored to buffer first.
//    pt2                      Ending point of the line segment.
//                             The pixel value will be stored to buffer last.
//F*/

IPPAPI(IppStatus, ippiSampleLine_8u_C1R, ( const Ipp8u* pSrc, int srcStep,
                                           IppiSize roiSize, Ipp8u* pDst,
                                           IppiPoint pt1, IppiPoint pt2 ))

IPPAPI(IppStatus, ippiSampleLine_8u_C3R, ( const Ipp8u* pSrc, int srcStep,
                                           IppiSize roiSize, Ipp8u* pDst,
                                           IppiPoint pt1, IppiPoint pt2 ))

IPPAPI(IppStatus, ippiSampleLine_16u_C1R, ( const Ipp16u* pSrc, int srcStep,
                                           IppiSize roiSize, Ipp16u* pDst,
                                           IppiPoint pt1, IppiPoint pt2 ))

IPPAPI(IppStatus, ippiSampleLine_16u_C3R, ( const Ipp16u* pSrc, int srcStep,
                                           IppiSize roiSize, Ipp16u* pDst,
                                           IppiPoint pt1, IppiPoint pt2 ))

IPPAPI(IppStatus, ippiSampleLine_32f_C1R, ( const Ipp32f* pSrc, int srcStep,
                                            IppiSize roiSize, Ipp32f* pDst,
                                            IppiPoint pt1, IppiPoint pt2 ))

IPPAPI(IppStatus, ippiSampleLine_32f_C3R, ( const Ipp32f* pSrc, int srcStep,
                                            IppiSize roiSize, Ipp32f* pDst,
                                            IppiPoint pt1, IppiPoint pt2 ))


/****************************************************************************************\
*                                    Accumulation                                        *
\****************************************************************************************/

/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiAdd_8u32f_C1IR,   ippiAdd_8s32f_C1IR,
//              ippiAdd_16u32f_C1IR,
//              ippiAdd_8u32f_C1IMR,  ippiAdd_8s32f_C1IMR,
//              ippiAdd_16u32f_C1IMR, ippiAdd_32f_C1IMR
//
//  Purpose:    Add image to accumulator.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            Step is too small to fit image.
//    ippStsNotEvenStepErr     Step is not multiple of element.
//
//  Arguments:
//    pSrc                     Pointer to source image
//    srcStep                  Step in the source image
//    pMask                    Pointer to mask
//    maskStep                 Step in the mask image
//    pSrcDst                  Pointer to accumulator image
//    srcDstStep               Step in the accumulator image
//    roiSize                  Image size
*/

IPPAPI(IppStatus, ippiAdd_8u32f_C1IR, (const Ipp8u*  pSrc, int srcStep,
                                       Ipp32f* pSrcDst, int srcDstStep,
                                       IppiSize roiSize ))

IPPAPI(IppStatus, ippiAdd_16u32f_C1IR, (const Ipp16u*  pSrc, int srcStep,
                                        Ipp32f* pSrcDst, int srcDstStep,
                                        IppiSize roiSize ))


IPPAPI(IppStatus, ippiAdd_8u32f_C1IMR,(const Ipp8u*  pSrc, int srcStep,
                                       const Ipp8u* pMask, int maskStep,
                                       Ipp32f* pSrcDst, int srcDstStep,
                                       IppiSize roiSize ))

IPPAPI(IppStatus, ippiAdd_16u32f_C1IMR,(const Ipp16u*  pSrc, int srcStep,
                                        const Ipp8u* pMask, int maskStep,
                                        Ipp32f* pSrcDst, int srcDstStep,
                                        IppiSize roiSize ))

IPPAPI(IppStatus, ippiAdd_32f_C1IMR,  (const Ipp32f* pSrc, int srcStep,
                                       const Ipp8u* pMask, int maskStep,
                                       Ipp32f* pSrcDst, int srcDstStep,
                                       IppiSize roiSize ))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:   ippiAddSquare_8u32f_C1IR,   ippiAddSquare_8u32f_C1IMR,
//          ippiAddSquare_16u32f_C1IR,  ippiAddSquare_16u32f_C1IMR,
//          ippiAddSquare_32f_C1IR,     ippiAddSquare_32f_C1IMR
//
//  Purpose:    Add squared image (i.e. multiplied by itself) to accumulator.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            Step is too small to fit image.
//    ippStsNotEvenStepErr     Step is not multiple of element.
//
//  Arguments:
//    pSrc                     Pointer to source image
//    srcStep                  Step in the source image
//    pMask                    Pointer to mask
//    maskStep                 Step in the mask image
//    pSrcDst                  Pointer to accumulator image
//    srcDstStep               Step in the accumulator image
//    roiSize                  Image size
*/

IPPAPI(IppStatus, ippiAddSquare_8u32f_C1IR, (const Ipp8u*  pSrc, int srcStep,
                                             Ipp32f* pSrcDst, int srcDstStep,
                                             IppiSize roiSize ))

IPPAPI(IppStatus, ippiAddSquare_16u32f_C1IR, (const Ipp16u*  pSrc, int srcStep,
                                              Ipp32f* pSrcDst, int srcDstStep,
                                              IppiSize roiSize ))

IPPAPI(IppStatus, ippiAddSquare_32f_C1IR,   (const Ipp32f* pSrc, int srcStep,
                                             Ipp32f* pSrcDst, int srcDstStep,
                                             IppiSize roiSize ))

IPPAPI(IppStatus, ippiAddSquare_8u32f_C1IMR,(const Ipp8u* pSrc, int srcStep,
                                             const Ipp8u* pMask, int maskStep,
                                             Ipp32f* pSrcDst, int srcDstStep,
                                             IppiSize roiSize ))

IPPAPI(IppStatus, ippiAddSquare_16u32f_C1IMR,(const Ipp16u* pSrc, int srcStep,
                                              const Ipp8u* pMask, int maskStep,
                                              Ipp32f* pSrcDst, int srcDstStep,
                                              IppiSize roiSize ))

IPPAPI(IppStatus, ippiAddSquare_32f_C1IMR,  (const Ipp32f* pSrc, int srcStep,
                                             const Ipp8u* pMask, int maskStep,
                                             Ipp32f* pSrcDst, int srcDstStep,
                                             IppiSize roiSize ))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name: ippiAddProduct_8u32f_C1IR,   ippiAddProduct_8s32f_C1IR,
//        ippiAddProduct_16u32f_C1IR,  ippiAddProduct_32f_C1IR,
//        ippiAddProduct_8u32f_C1IMR,  ippiAddProduct_8s32f_C1IMR,
//        ippiAddProduct_16u32f_C1IMR, ippiAddProduct_32f_C1IMR
//
//  Purpose:  Add product of two images to accumulator.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            Step is too small to fit image.
//    ippStsNotEvenStepErr     Step is not multiple of element.
//
//  Arguments:
//    pSrc1                    Pointer to first source image
//    src1Step                 Step in the first source image
//    pSrc2                    Pointer to second source image
//    src2Step                 Step in the second source image
//    pMask                    Pointer to mask
//    maskStep                 Step in the mask image
//    pSrcDst                  Pointer to accumulator image
//    srcDstStep               Step in the accumulator image
//    roiSize                  Image size
*/

IPPAPI(IppStatus, ippiAddProduct_8u32f_C1IR, (const Ipp8u*  pSrc1, int src1Step,
                                              const Ipp8u*  pSrc2, int src2Step,
                                              Ipp32f* pSrcDst, int srcDstStep,
                                              IppiSize roiSize ))

IPPAPI(IppStatus, ippiAddProduct_16u32f_C1IR, (const Ipp16u*  pSrc1, int src1Step,
                                               const Ipp16u*  pSrc2, int src2Step,
                                               Ipp32f* pSrcDst, int srcDstStep,
                                               IppiSize roiSize ))

IPPAPI(IppStatus, ippiAddProduct_32f_C1IR,   (const Ipp32f* pSrc1, int src1Step,
                                              const Ipp32f* pSrc2, int src2Step,
                                              Ipp32f* pSrcDst, int srcDstStep,
                                              IppiSize roiSize ))

IPPAPI(IppStatus, ippiAddProduct_8u32f_C1IMR,(const Ipp8u*  pSrc1, int src1Step,
                                              const Ipp8u*  pSrc2, int src2Step,
                                              const Ipp8u* pMask, int maskStep,
                                              Ipp32f* pSrcDst, int srcDstStep,
                                              IppiSize roiSize ))

IPPAPI(IppStatus, ippiAddProduct_16u32f_C1IMR,(const Ipp16u*  pSrc1, int src1Step,
                                               const Ipp16u*  pSrc2, int src2Step,
                                               const Ipp8u* pMask, int maskStep,
                                               Ipp32f* pSrcDst, int srcDstStep,
                                               IppiSize roiSize ))

IPPAPI(IppStatus, ippiAddProduct_32f_C1IMR,  (const Ipp32f* pSrc1, int src1Step,
                                              const Ipp32f* pSrc2, int src2Step,
                                              const Ipp8u* pMask, int maskStep,
                                              Ipp32f* pSrcDst, int srcDstStep,
                                              IppiSize roiSize ))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name: ippiAddWeighted_8u32f_C1IR,  ippiAddWeighted_8s32f_C1IR,
//        ippiAddWeighted_16u32f_C1IR, ippiAddWeighted_32f_C1IR,
//        ippiAddWeighted_8u32f_C1IMR, ippiAddWeighted_8s32f_C1IMR,
//        ippiAddWeighted_16u32f_C1IMR,ippiAddWeighted_32f_C1IMR
//        ippiAddWeighted_32f_C1R
//
//  Purpose:  Add image, multiplied by alpha, to accumulator, multiplied by (1 - alpha).
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            Step is too small to fit image.
//    ippStsNotEvenStepErr     Step is not multiple of element.
//
//  Arguments:
//    pSrc1                    Pointer to first source image
//    src1Step                 Step in the first source image
//    pSrc2                    Pointer to second source image
//    src2Step                 Step in the second source image
//    pMask                    Pointer to mask
//    maskStep                 Step in the mask image
//    pSrcDst                  Pointer to accumulator image
//    srcDstStep               Step in the accumulator image
//    pDst                     Pointer to destination image
//    dstStep                  Step in the destination image
//    roiSize                  Image size
//    alpha                    Weight of source image
*/

IPPAPI(IppStatus, ippiAddWeighted_8u32f_C1IR, (const Ipp8u*  pSrc, int srcStep,
                                               Ipp32f* pSrcDst, int srcDstStep,
                                               IppiSize roiSize, Ipp32f alpha ))

IPPAPI(IppStatus, ippiAddWeighted_16u32f_C1IR, (const Ipp16u*  pSrc, int srcStep,
                                                Ipp32f* pSrcDst, int srcDstStep,
                                                IppiSize roiSize, Ipp32f alpha ))

IPPAPI(IppStatus, ippiAddWeighted_32f_C1IR,   (const Ipp32f* pSrc, int srcStep,
                                               Ipp32f* pSrcDst, int srcDstStep,
                                               IppiSize roiSize, Ipp32f alpha ))

IPPAPI(IppStatus, ippiAddWeighted_8u32f_C1IMR,(const Ipp8u* pSrc, int srcStep,
                                               const Ipp8u* pMask, int maskStep,
                                               Ipp32f* pSrcDst, int srcDstStep,
                                               IppiSize roiSize, Ipp32f alpha ))

IPPAPI(IppStatus, ippiAddWeighted_16u32f_C1IMR,(const Ipp16u* pSrc, int srcStep,
                                                const Ipp8u* pMask, int maskStep,
                                                Ipp32f* pSrcDst, int srcDstStep,
                                                IppiSize roiSize, Ipp32f alpha ))

IPPAPI(IppStatus, ippiAddWeighted_32f_C1IMR,  (const Ipp32f* pSrc, int srcStep,
                                               const Ipp8u* pMask, int maskStep,
                                               Ipp32f* pSrcDst, int srcDstStep,
                                               IppiSize roiSize, Ipp32f alpha ))

IPPAPI(IppStatus, ippiAddWeighted_32f_C1R, ( const Ipp32f*  pSrc1, int src1Step,
                                             const Ipp32f*  pSrc2, int src2Step,
                                              Ipp32f* pDst, int dstStep,
                                              IppiSize roiSize, Ipp32f alpha ))


/****************************************************************************************\
*                                 Absolute difference                                    *
\****************************************************************************************/

/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name:    ippiAbsDiff_8u_C1R, ippiAbsDiff_8u_C3R, ippiAbsDiff_16u_C1R, ippiAbsDiff_32f_C1R,
//
//  Purpose: Calculate absolute difference between corresponding pixels of the two images
//           or between image pixels and scalar.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//
//  Parameters:
//    pSrc1                    Source image
//    src1Step                 Its step
//    pSrc2                    Second source image
//    src2Step                 Its step
//    pDst                     Destination image
//    dstStep                  Its step
//    roiSize                  ROI size
//F*/

IPPAPI(IppStatus, ippiAbsDiff_8u_C1R, ( const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        Ipp8u* pDst, int dstStep, IppiSize roiSize ))
IPPAPI(IppStatus, ippiAbsDiff_8u_C3R, ( const Ipp8u* pSrc1, int src1Step,
                                        const Ipp8u* pSrc2, int src2Step,
                                        Ipp8u* pDst, int dstStep, IppiSize roiSize ))

IPPAPI(IppStatus, ippiAbsDiff_16u_C1R, ( const Ipp16u* pSrc1, int src1Step,
                                         const Ipp16u* pSrc2, int src2Step,
                                         Ipp16u* pDst, int dstStep, IppiSize roiSize ))

IPPAPI(IppStatus, ippiAbsDiff_32f_C1R, ( const Ipp32f* pSrc1, int src1Step,
                                         const Ipp32f* pSrc2, int src2Step,
                                         Ipp32f* pDst, int dstStep, IppiSize roiSize ))


/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name:    ippiAbsDiffC_8u_C1R, ippiAbsDiffC_16u_C1R, ippiAbsDiffC_32f_C1R,
//
//  Purpose: Calculate absolute difference between image pixels and scalar.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//
//  Parameters:
//    pSrc                     Source image
//    srcStep                  Its step
//    pDst                     Destination image: dst(x,y) = abs(src(x,y) - value)
//    dstStep                  Its step
//    roiSize                      ROI size
//    value                    Scalar value to compare with. For 8u function
//                             If scalar is not within [0,255], it is clipped
//                             ( value = value < 0 ? 0 : value > 255 ? 255 : value )
//F*/

IPPAPI(IppStatus, ippiAbsDiffC_8u_C1R, ( const Ipp8u* pSrc, int srcStep,
                                         Ipp8u* pDst, int dstStep,
                                         IppiSize roiSize, int value ))

IPPAPI(IppStatus, ippiAbsDiffC_16u_C1R, ( const Ipp16u* pSrc, int srcStep,
                                          Ipp16u* pDst, int dstStep,
                                          IppiSize roiSize, int value ))

IPPAPI(IppStatus, ippiAbsDiffC_32f_C1R, ( const Ipp32f* pSrc, int srcStep,
                                          Ipp32f* pDst, int dstStep,
                                          IppiSize roiSize, Ipp32f value ))


/****************************************************************************************\
*                                Morphological Operations                                *
\****************************************************************************************/

/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:   ippiMorphologyBorderGetSize_16u_C1R,     ippiMorphologyBorderGetSize_16s_C1R,
//          ippiMorphologyBorderGetSize_1u_C1R,      ippiMorphologyBorderGetSize_8u_C1R,
//          ippiMorphologyBorderGetSize_8u_C3R,      ippiMorphologyBorderGetSize_8u_C4R,
//          ippiMorphologyBorderGetSize_32f_C1R,     ippiMorphologyBorderGetSize_32f_C3R
//          ippiMorphologyBorderGetSize_32f_C4R
//
//
//  Purpose:  Gets the size of the internal state or specification structure for morphological operations.
//
//  Return:
//    ippStsNoErr              Ok.
//    ippStsNullPtrErr         One of the pointers is NULL.
//    ippStsSizeErr            Width or height of the image, or width or height of the structuring
//                             element is less than,or equal to zero.
//
//  Parameters:
//    roiSize                  Destination image ROI size in pixels.
//    maskSize                 Size of the structuring element.
//    pSpecSize                Pointer to the specification structure size.
//    pBufferSize              Pointer to the buffer size value for the morphological initialization function.
*/

IPPAPI(IppStatus, ippiMorphologyBorderGetSize_8u_C1R, (IppiSize roiSize, IppiSize maskSize, int* pSpecSize, int* pBufferSize))
IPPAPI(IppStatus, ippiMorphologyBorderGetSize_8u_C3R, (IppiSize roiSize, IppiSize maskSize, int* pSpecSize, int* pBufferSize))
IPPAPI(IppStatus, ippiMorphologyBorderGetSize_8u_C4R, (IppiSize roiSize, IppiSize maskSize, int* pSpecSize, int* pBufferSize))
IPPAPI(IppStatus, ippiMorphologyBorderGetSize_32f_C1R,(IppiSize roiSize, IppiSize maskSize, int* pSpecSize, int* pBufferSize))
IPPAPI(IppStatus, ippiMorphologyBorderGetSize_32f_C3R,(IppiSize roiSize, IppiSize maskSize, int* pSpecSize, int* pBufferSize))
IPPAPI(IppStatus, ippiMorphologyBorderGetSize_32f_C4R,(IppiSize roiSize, IppiSize maskSize, int* pSpecSize, int* pBufferSize))
IPPAPI(IppStatus, ippiMorphologyBorderGetSize_16u_C1R,(IppiSize roiSize, IppiSize maskSize, int* pSpecSize, int* pBufferSize))
IPPAPI(IppStatus, ippiMorphologyBorderGetSize_16s_C1R,(IppiSize roiSize, IppiSize maskSize, int* pSpecSize, int* pBufferSize))
IPPAPI(IppStatus, ippiMorphologyBorderGetSize_1u_C1R, (IppiSize roiSize, IppiSize maskSize, int* pSpecSize, int* pBufferSize))

/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:   ippiMorphologyBorderInit_16u_C1R,        ippiMorphologyBorderInit_16s_C1R
//          ippiMorphologyBorderInit_1u_C1R,         ippiMorphologyBorderInit_8u_C1R
//          ippiMorphologyBorderInit_8u_C3R,         ippiMorphologyBorderInit_8u_C4R
//          ippiMorphologyBorderInit_32f_C1R,        ippiMorphologyBorderInit_32f_C3R,
//          ippiMorphologyBorderInit_32f_C4R,
//
//  Purpose:  Initialize the internal state or specification structure for morphological operation.
//
//  Return:
//    ippStsNoErr              Ok.
//    ippStsNullPtrErr         One of the pointers is NULL.
//    ippStsSizeErr            Width of the image or width or height of the structuring
//                             element is less than, or equal to zero.
//    ippStsAnchorErr          Anchor point is outside the structuring element.
//
//  Parameters:
//    roiSize                  Destination image ROI size in pixels.
//    pMask                    Pointer to the structuring element (mask).
//    maskSize                 Size of the structuring element.
//    pSpec                    Pointer to the morphology state structure.
//    pBuffer                  Pointer to the external work buffer.
*/

IPPAPI(IppStatus, ippiMorphologyBorderInit_16u_C1R,(IppiSize roiSize, const Ipp8u* pMask, IppiSize maskSize, IppiMorphState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphologyBorderInit_16s_C1R,(IppiSize roiSize, const Ipp8u* pMask, IppiSize maskSize, IppiMorphState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphologyBorderInit_1u_C1R, (IppiSize roiSize, const Ipp8u* pMask, IppiSize maskSize, IppiMorphState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphologyBorderInit_8u_C1R, (IppiSize roiSize, const Ipp8u* pMask, IppiSize maskSize, IppiMorphState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphologyBorderInit_8u_C3R, (IppiSize roiSize, const Ipp8u* pMask, IppiSize maskSize, IppiMorphState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphologyBorderInit_8u_C4R, (IppiSize roiSize, const Ipp8u* pMask, IppiSize maskSize, IppiMorphState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphologyBorderInit_32f_C1R,(IppiSize roiSize, const Ipp8u* pMask, IppiSize maskSize, IppiMorphState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphologyBorderInit_32f_C3R,(IppiSize roiSize, const Ipp8u* pMask, IppiSize maskSize, IppiMorphState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphologyBorderInit_32f_C4R,(IppiSize roiSize, const Ipp8u* pMask, IppiSize maskSize, IppiMorphState* pSpec, Ipp8u* pBuffer))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:   ippiDilateBorder_8u_C1R,    ippiDilateBorder_8u_C3R,
//          ippiDilateBorder_8u_C4R,    ippiDilateBorder_32f_C1R,
//          ippiDilateBorder_32f_C3R,   ippiDilateBorder_32f_C4R
//          ippiDilateBorder_16u_C1R,            ippiDilateBorder_16s_C1R,
//          ippiDilateBorder_1u_C1R
//
//          ippiErodeBorder_8u_C1R,     ippiErodeBorder_8u_C3R,
//          ippiErodeBorder_8u_C4R,     ippiErodeBorder_32f_C1R,
//          ippiErodeBorder_32f_C3R,    ippiErodeBorder_32f_C4R,
//          ippiErodeBorder_16u_C1R,    ippiErodeBorder_16s_C1R,
//          ippiErodeBorder_1u_C1R
//
//
//  Purpose:    Perform erosion/dilation of the image arbitrary shape structuring element.
//
//  Return:
//    ippStsNoErr              Ok.
//    ippStsNullPtrErr         One of the pointers is NULL.
//    ippStsSizeErr            The ROI width or height is less than 1,
//                             or ROI width is bigger than ROI width in the state structure.
//    ippStsStepErr            Step is too small to fit the image.
//    ippStsNotEvenStepErr     Step is not multiple of the element.
//    ippStsBadArgErr          Incorrect border type.
//

//  Parameters:
//    pSrc                     Pointer to the source image.
//    srcStep                  Step in the source image.
//    pDst                     Pointer to the destination image.
//    dstStep                  Step in the destination image.
//    roiSize                  Destination image ROI size in pixels.
//    borderType               Type of border.
//    borderValue              Pointer to the vector of values for the constant border.
//    pSpec                    Pointer to the morphology specification structure.
//    pBuffer                  Pointer to the external work buffer.
*/
IPPAPI(IppStatus, ippiDilateBorder_8u_C1R, (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp8u borderValue,     const IppiMorphState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiDilateBorder_8u_C3R, (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp8u borderValue[3],  const IppiMorphState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiDilateBorder_8u_C4R, (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp8u borderValue[4],  const IppiMorphState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiDilateBorder_32f_C1R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp32f borderValue,    const IppiMorphState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiDilateBorder_32f_C3R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp32f borderValue[3], const IppiMorphState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiDilateBorder_32f_C4R,(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp32f borderValue[4], const IppiMorphState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiDilateBorder_16u_C1R,(const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp16u borderValue,    const IppiMorphState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiDilateBorder_16s_C1R,(const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp16s borderValue,    const IppiMorphState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiErodeBorder_8u_C1R,  (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp8u borderValue,     const IppiMorphState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiErodeBorder_8u_C3R,  (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp8u borderValue[3],  const IppiMorphState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiErodeBorder_8u_C4R,  (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp8u borderValue[4],  const IppiMorphState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiErodeBorder_32f_C1R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp32f borderValue,    const IppiMorphState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiErodeBorder_32f_C3R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp32f borderValue[3], const IppiMorphState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiErodeBorder_32f_C4R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp32f borderValue[4], const IppiMorphState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiErodeBorder_16u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp16u borderValue,    const IppiMorphState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiErodeBorder_16s_C1R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp16s borderValue,    const IppiMorphState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiDilateBorder_1u_C1R, (const Ipp8u*  pSrc, int srcStep, int srcBitOffset, Ipp8u* pDst, int dstStep, int dstBitOffset, IppiSize roiSize, IppiBorderType borderType, Ipp8u borderValue, const IppiMorphState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiErodeBorder_1u_C1R,  (const Ipp8u*  pSrc, int srcStep, int srcBitOffset, Ipp8u* pDst, int dstStep, int dstBitOffset, IppiSize roiSize, IppiBorderType borderType, Ipp8u borderValue, const IppiMorphState* pSpec, Ipp8u* pBuffer ))


/****************************************************************************************\
*                       Advanced Morphological Operations                                *
\****************************************************************************************/

/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:   ippiMorphSetMode
//
//  Purpose:    Set mode for symmetrical operation in advanced morphology
//              IPP_MORPH_DEFAULT - default behavior
//              IPP_MORPH_MASK_NO_FLIP - don't flip mask(the same mask for (erode(dilate)->dilate(erode)) operations)
//
//
//  Return:
//    ippStsNoErr               Ok.
//    ippStsNullPtrErr          One of the pointers is NULL.
//    ippStsNotSupportedModeErr Incorrect mode
//
//  Parameters:
//    mode                     Mode. One of IPP_MORPH_DEFAULT(flip), IPP_MORPH_MASK_NO_FLIP(no flip)
//    pMorphSpec               Pointer to the morphology specification structure.
*/

IPPAPI(IppStatus, ippiMorphSetMode, (int mode, IppiMorphAdvState* pMorphSpec))

/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:   ippiMorphAdvGetSize_8u_C1R,            ippiMorphAdvGetSize_32f_C1R,
//          ippiMorphAdvGetSize_8u_C3R,            ippiMorphAdvGetSize_32f_C3R,
//          ippiMorphAdvGetSize_8u_C4R,            ippiMorphAdvGetSize_32f_C4R,
//          ippiMorphAdvGetSize_16u_C1R,           ippiMorphAdvGetSize_16s_C1R,
//          ippiMorphAdvGetSize_1u_C1R
//
//  Purpose:  Gets the size of the internal state or specification structure for advanced morphological operations.
//
//  Return:
//    ippStsNoErr              Ok.
//    ippStsNullPtrErr         One of the pointers is NULL.
//    ippStsSizeErr            Width or height of the image, or width or height of the structuring.
//                             element is less than, or equal to zero.
//
//  Parameters:
//    roiSize                  Maximum size of the destination image ROI, in pixels.
//    maskSize                 Size of the structuring element.
//    pSpecSize                Pointer to the specification structure size.
//    pBufferSize              Pointer to the buffer size value for the morphology initialization function.
*/

IPPAPI(IppStatus, ippiMorphAdvGetSize_1u_C1R,  (IppiSize roiSize, IppiSize maskSize, int* pSpecSize, int* pBufferSize))
IPPAPI(IppStatus, ippiMorphAdvGetSize_8u_C1R,  (IppiSize roiSize, IppiSize maskSize, int* pSpecSize, int* pBufferSize))
IPPAPI(IppStatus, ippiMorphAdvGetSize_8u_C3R,  (IppiSize roiSize, IppiSize maskSize, int* pSpecSize, int* pBufferSize))
IPPAPI(IppStatus, ippiMorphAdvGetSize_8u_C4R,  (IppiSize roiSize, IppiSize maskSize, int* pSpecSize, int* pBufferSize))
IPPAPI(IppStatus, ippiMorphAdvGetSize_16u_C1R, (IppiSize roiSize, IppiSize maskSize, int* pSpecSize, int* pBufferSize))
IPPAPI(IppStatus, ippiMorphAdvGetSize_16s_C1R, (IppiSize roiSize, IppiSize maskSize, int* pSpecSize, int* pBufferSize))
IPPAPI(IppStatus, ippiMorphAdvGetSize_32f_C1R, (IppiSize roiSize, IppiSize maskSize, int* pSpecSize, int* pBufferSize))
IPPAPI(IppStatus, ippiMorphAdvGetSize_32f_C3R, (IppiSize roiSize, IppiSize maskSize, int* pSpecSize, int* pBufferSize))
IPPAPI(IppStatus, ippiMorphAdvGetSize_32f_C4R, (IppiSize roiSize, IppiSize maskSize, int* pSpecSize, int* pBufferSize))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:   ippiMorphAdvInit_8u_C1R,               ippiMorphAdvInit_32f_C1R,
//          ippiMorphAdvInit_8u_C3R,               ippiMorphAdvInit_32f_C3R,
//          ippiMorphAdvInit_8u_C4R,               ippiMorphAdvInit_32f_C4R,
//          ippiMorphAdvInit_16u_C1R,              ippiMorphAdvInit_16s_C1R,
//          ippiMorphAdvInit_1u_C1R
//
//  Purpose:  Initialize the internal state or specification structure for advanced morphological operations.
//
//  Return:
//    ippStsNoErr              Ok.
//    ippStsNullPtrErr         One of the pointers is NULL.
//    ippStsSizeErr            Width or height of the image or width or height of the structuring
//                             element is less than, or equal to zero.
//    ippStsAnchorErr          Anchor point is outside the structuring element.
//
//  Parameters:
//    roiSize                  Maximum size of the image ROI, in pixels.
//    pMask                    Pointer to the structuring element (mask).
//    maskSize                 Size of the structuring element.
//    pSpec                    Pointer to the advanced morphology specification structure.
//    pBuffer                  Pointer to the external work buffer.
*/

IPPAPI(IppStatus, ippiMorphAdvInit_8u_C1R,  (IppiSize roiSize, const Ipp8u* pMask, IppiSize maskSize, IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphAdvInit_8u_C3R,  (IppiSize roiSize, const Ipp8u* pMask, IppiSize maskSize, IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphAdvInit_8u_C4R,  (IppiSize roiSize, const Ipp8u* pMask, IppiSize maskSize, IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphAdvInit_16u_C1R, (IppiSize roiSize, const Ipp8u* pMask, IppiSize maskSize, IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphAdvInit_16s_C1R, (IppiSize roiSize, const Ipp8u* pMask, IppiSize maskSize, IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphAdvInit_1u_C1R,  (IppiSize roiSize, const Ipp8u* pMask, IppiSize maskSize, IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphAdvInit_32f_C1R, (IppiSize roiSize, const Ipp8u* pMask, IppiSize maskSize, IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphAdvInit_32f_C3R, (IppiSize roiSize, const Ipp8u* pMask, IppiSize maskSize, IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphAdvInit_32f_C4R, (IppiSize roiSize, const Ipp8u* pMask, IppiSize maskSize, IppiMorphAdvState* pSpec, Ipp8u* pBuffer))

/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:   ippiMorphCloseBorder_8u_C1R,             ippiMorphCloseBorder_8u_C3R,
//          ippiMorphCloseBorder_8u_C4R,             ippiMorphCloseBorder_32f_C1R,
//          ippiMorphCloseBorder_32f_C3R,            ippiMorphCloseBorder_32f_C4R
//
//          ippiMorphOpenBorder_8u_C1R,              ippiMorphOpenBorder_8u_C3R,
//          ippiMorphOpenBorder_8u_C4R,              ippiMorphOpenBorder_32f_C1R,
//          ippiMorphOpenBorder_32f_C3R,             ippiMorphOpenBorder_32f_C4R,
//
//          ippiMorphCloseBorder_16u_C1R,            ippiMorphOpenBorder_16u_C1R,
//          ippiMorphCloseBorder_16s_C1R,            ippiMorphOpenBorder_16s_C1R,
//          ippiMorphCloseBorder_1u_C1R,             ippiMorphOpenBorder_1u_C1R,

//          ippiMorphTophatBorder_8u_C1R,            ippiMorphTophatBorder_8u_C3R,
//          ippiMorphTophatBorder_8u_C4R,            ippiMorphTophatBorder_32f_C1R,
//          ippiMorphTophatBorder_32f_C3R,           ippiMorphTophatBorder_32f_C4R,
//
//          ippiMorphBlackhatBorder_8u_C1R,          ippiMorphBlackhatBorder_8u_C3R,
//          ippiMorphBlackhatBorder_8u_C4R,          ippiMorphBlackhatBorder_32f_C1R,
//          ippiMorphBlackhatBorder_32f_C3R,         ippiMorphBlackhatBorder_32f_C4R,
//
//          ippiMorphGradientBorder_8u_C1R,     ippiMorphGradientBorder_8u_C3R,
//          ippiMorphGradientBorder_8u_C4R,     ippiMorphGradientBorder_32f_C1R,
//          ippiMorphGradientBorder_32f_C3R,    ippiMorphGradientBorder_32f_C4R,
//
//  Purpose:    Perform advanced morphologcal operations on the image arbitrary shape structuring element.
//
//  Return:
//    ippStsNoErr              Ok.
//    ippStsNullPtrErr         One of the pointers is NULL.
//    ippStsSizeErr            The ROI width or height is less than 1,
//                             or ROI width(height) is bigger than ROI width(height) in the state structure.
//    ippStsStepErr            Step is too small to fit the image.
//    ippStsNotEvenStepErr     Step is not multiple of the element.
//    ippStsBadArgErr          Incorrect border type.
//
//  Parameters:
//    pSrc                     Pointer to the source image.
//    srcStep                  Step in the source image.
//    pDst                     Pointer to the destination image.
//    dstStep                  Step in the destination image.
//    roiSize                  ROI size.
//    borderType               Type of border.
//    borderValue              Value for the constant border.
//    pSpec                    Pointer to the morphology specification structure.
//    pBuffer                  Pointer to the external work buffer.
*/
IPPAPI(IppStatus, ippiMorphOpenBorder_8u_C1R,      (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp8u borderValue,     const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphOpenBorder_8u_C3R,      (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp8u borderValue[3],  const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphOpenBorder_8u_C4R,      (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp8u borderValue[4],  const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphOpenBorder_16u_C1R,     (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp16u borderValue,    const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphOpenBorder_16s_C1R,     (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp16s borderValue,    const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphOpenBorder_32f_C1R,     (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp32f borderValue,    const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphOpenBorder_32f_C3R,     (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp32f borderValue[3], const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphOpenBorder_32f_C4R,     (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp32f borderValue[4], const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphCloseBorder_8u_C1R,     (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp8u borderValue,     const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphCloseBorder_8u_C3R,     (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp8u borderValue[3],  const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphCloseBorder_8u_C4R,     (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp8u borderValue[4],  const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphCloseBorder_16u_C1R,    (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp16u borderValue,    const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphCloseBorder_16s_C1R,    (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp16s borderValue,    const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphCloseBorder_32f_C1R,    (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp32f borderValue,    const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphCloseBorder_32f_C3R,    (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp32f borderValue[3], const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphCloseBorder_32f_C4R,    (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp32f borderValue[4], const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphTophatBorder_8u_C1R,    (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp8u borderValue,     const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphTophatBorder_8u_C3R,    (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp8u borderValue[3],  const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphTophatBorder_8u_C4R,    (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp8u borderValue[4],  const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphTophatBorder_16u_C1R,   (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp16u borderValue,    const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphTophatBorder_16s_C1R,   (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp16s borderValue,    const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphTophatBorder_32f_C1R,   (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp32f borderValue,    const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphTophatBorder_32f_C3R,   (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp32f borderValue[3], const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphTophatBorder_32f_C4R,   (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp32f borderValue[4], const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphBlackhatBorder_8u_C1R,  (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp8u borderValue,     const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphBlackhatBorder_8u_C3R,  (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp8u borderValue[3],  const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphBlackhatBorder_8u_C4R,  (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp8u borderValue[4],  const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphBlackhatBorder_16u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp16u borderValue,    const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphBlackhatBorder_16s_C1R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp16s borderValue,    const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphBlackhatBorder_32f_C1R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp32f borderValue,    const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphBlackhatBorder_32f_C3R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp32f borderValue[3], const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphBlackhatBorder_32f_C4R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp32f borderValue[4], const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphGradientBorder_8u_C1R,  (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp8u borderValue,     const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphGradientBorder_8u_C3R,  (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp8u borderValue[3],  const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphGradientBorder_8u_C4R,  (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp8u borderValue[4],  const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphGradientBorder_16u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp16u borderValue,    const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphGradientBorder_16s_C1R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp16s borderValue,    const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphGradientBorder_32f_C1R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,       Ipp32f borderValue,    const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphGradientBorder_32f_C3R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp32f borderValue[3], const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphGradientBorder_32f_C4R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp32f borderValue[4], const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiMorphOpenBorder_1u_C1R,     (const Ipp8u* pSrc, int srcStep, int srcBitOffset, Ipp8u* pDst, int dstStep, int dstBitOffset, IppiSize roiSize, IppiBorderType borderType, Ipp8u borderValue, const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphCloseBorder_1u_C1R,    (const Ipp8u* pSrc, int srcStep, int srcBitOffset, Ipp8u* pDst, int dstStep, int dstBitOffset, IppiSize roiSize, IppiBorderType borderType, Ipp8u borderValue, const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphTophatBorder_1u_C1R,   (const Ipp8u* pSrc, int srcStep, int srcBitOffset, Ipp8u* pDst, int dstStep, int dstBitOffset, IppiSize roiSize, IppiBorderType borderType, Ipp8u borderValue, const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphBlackhatBorder_1u_C1R, (const Ipp8u* pSrc, int srcStep, int srcBitOffset, Ipp8u* pDst, int dstStep, int dstBitOffset, IppiSize roiSize, IppiBorderType borderType, Ipp8u borderValue, const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiMorphGradientBorder_1u_C1R, (const Ipp8u* pSrc, int srcStep, int srcBitOffset, Ipp8u* pDst, int dstStep, int dstBitOffset, IppiSize roiSize, IppiBorderType borderType, Ipp8u borderValue, const IppiMorphAdvState* pSpec, Ipp8u* pBuffer))

/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:   ippiMorphGrayGetSize_8u_C1R,            ippiMorphGrayGetSize_32f_C1R
//
//  Purpose:  Gets size of internal state of gray-kernel morphological operation.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width of image or width or height of structuring
//                             element is less or equal zero.
//
//  Arguments:
//    roiSize                  Maximal image ROI in pixels
//    pMask                    Pointer to structuring element
//    maskSize                 Size of structuring element
//    pSize                    Pointer to state length
*/

IPPAPI(IppStatus, ippiMorphGrayGetSize_8u_C1R,(IppiSize roiSize, const Ipp32s* pMask, IppiSize maskSize, int* pSize))

IPPAPI(IppStatus, ippiMorphGrayGetSize_32f_C1R,(IppiSize roiSize, const Ipp32f* pMask, IppiSize maskSize, int* pSize))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:   ippiMorphGrayInit_8u_C1R,               ippiMorphGrayInit_32f_C1R
//
//  Purpose:  Initialize internal state of gray-scale morphological operation.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width of image or width or height of structuring
//                             element is less or equal zero.
//    ippStsAnchorErr          Anchor point is outside the structuring element
//
//  Arguments:
//    roiSize                  Maximal image roiSize in pixels
//    pMask                    Pointer to structuring element (mask)
//    maskSize                 Size of structuring element
//    anchor                   Anchor of the structuring element
//    pState                   Pointer to morphological state (Init)
*/
IPPAPI(IppStatus, ippiMorphGrayInit_8u_C1R,(IppiMorphGrayState_8u* pState, IppiSize roiSize, const Ipp32s* pMask,
                                              IppiSize maskSize, IppiPoint anchor))

IPPAPI(IppStatus, ippiMorphGrayInit_32f_C1R,(IppiMorphGrayState_32f* pState, IppiSize roiSize, const Ipp32f* pMask,
                                              IppiSize maskSize, IppiPoint anchor))


/*F///////////////////////////////////////////////////////////////////////////////////////////////
//  Name:   ippiGrayDilateBorder_8u_C1R,    ippiGrayDilateBorder_32f_C1R,
//          ippiGrayErodeBorder_8u_C1R,     ippiGrayErodeBorder_32f_C1R
//
//  Purpose:    Perform erosion/dilation of image with gray-scale structuring element.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The ROI width or height is less than 1
//                             or ROI width is bigger than ROI width in state
//    ippStsStepErr            Step is too small to fit image.
//    ippStsNotEvenStepErr     Step is not multiple of element.
//    ippStsBadArgErr          Bad border type
//
//  Arguments:
//    pSrc                     The pointer to source image
//    srcStep                  The step in source image
//    pDst                     The pointer to destination image
//    dstStep                  The step in destination image
//    roiSize                  ROI size
//    border                   Type of border (ippBorderRepl now)
//    pState                   Pointer to morphological operation state
*/
IPPAPI(IppStatus, ippiGrayErodeBorder_8u_C1R,(const Ipp8u* pSrc, int srcStep,
                                   Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                   IppiBorderType border, IppiMorphGrayState_8u* pState))

IPPAPI(IppStatus, ippiGrayErodeBorder_32f_C1R,(const Ipp32f* pSrc, int srcStep,
                                   Ipp32f* pDst, int dstStep, IppiSize roiSize,
                                   IppiBorderType border, IppiMorphGrayState_32f* pState))

IPPAPI(IppStatus, ippiGrayDilateBorder_8u_C1R,(const Ipp8u* pSrc, int srcStep,
                                   Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                   IppiBorderType border, IppiMorphGrayState_8u* pState))

IPPAPI(IppStatus, ippiGrayDilateBorder_32f_C1R,(const Ipp32f* pSrc, int srcStep,
                                   Ipp32f* pDst, int dstStep, IppiSize roiSize,
                                   IppiBorderType border, IppiMorphGrayState_32f* pState))


/*F/////////////////////////////////////////////////////////////////////////////////////
//  Name: ippiMorphReconstructGetBufferSize
//
//  Purpose:   returns buffer size for morphological reconstruction
//
//  Returns:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//
//  Parameters:
//    roiSize                  The maximal ROI size.
//    dataType                 The type of data
//    numChannels              The number of channels
//    p(Buf)Size               The pointer to the buffer size.
//
//  Notes:
//F*/

IPPAPI(IppStatus, ippiMorphReconstructGetBufferSize,(IppiSize roiSize, IppDataType dataType, int numChannels, int *pBufSize))

/*F/////////////////////////////////////////////////////////////////////////////////////
//  Name: ippiMorphReconstructDilate_8u_C1IR,              ippiMorphReconstructErode_8u_C1IR
//        ippiMorphReconstructDilate_16u_C1IR,             ippiMorphReconstructErode_16u_C1IR,
//        ippiMorphReconstructDilate_32f_C1IR,             ippiMorphReconstructErode_32f_C1IR
//        ippiMorphReconstructDilate_64f_C1IR,             ippiMorphReconstructErode_64f_C1IR
//
//  Purpose:   performs morphological reconstruction of pSrcDst under/above pSrc
//
//  Returns:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//
//  Parameters:
//    pSrc                     The pointer to source above/under image
//    srcStep                  The step in source image
//    pSrcDst                  The pointer to image to reconstruct
//    srcDstStep               The step in destination image
//    roiSize                  The source and destination image ROI size.
//    norm                     The norm type for dilation
//                                  ippiNormInf = Linf norm (8-connectivity)
//                                  ippiNormL1  = L1 norm   (4-connectivity)
//    pBuffer                  The pointer to working buffer
//
//  Notes:
//F*/

IPPAPI(IppStatus, ippiMorphReconstructDilate_8u_C1IR, (const Ipp8u* pSrc, int srcStep,
       Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize, Ipp8u *pBuf, IppiNorm norm))

IPPAPI(IppStatus, ippiMorphReconstructErode_8u_C1IR, (const Ipp8u* pSrc, int srcStep,
       Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize, Ipp8u *pBuf, IppiNorm norm))

IPPAPI(IppStatus, ippiMorphReconstructDilate_16u_C1IR, (const Ipp16u* pSrc, int srcStep,
       Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize, Ipp8u *pBuf, IppiNorm norm))

IPPAPI(IppStatus, ippiMorphReconstructErode_16u_C1IR, (const Ipp16u* pSrc, int srcStep,
       Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize, Ipp8u *pBuf, IppiNorm norm))

IPPAPI(IppStatus, ippiMorphReconstructDilate_32f_C1IR, (const Ipp32f* pSrc, int srcStep,
       Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize, Ipp32f *pBuf, IppiNorm norm))

IPPAPI(IppStatus, ippiMorphReconstructErode_32f_C1IR, (const Ipp32f* pSrc, int srcStep,
       Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize, Ipp32f *pBuf, IppiNorm norm))

IPPAPI(IppStatus, ippiMorphReconstructDilate_64f_C1IR, (const Ipp64f* pSrc, int srcStep,
       Ipp64f* pSrcDst, int srcDstStep, IppiSize roiSize, Ipp8u *pBuf, IppiNorm norm))

IPPAPI(IppStatus, ippiMorphReconstructErode_64f_C1IR, (const Ipp64f* pSrc, int srcStep,
       Ipp64f* pSrcDst, int srcDstStep, IppiSize roiSize, Ipp8u *pBuf, IppiNorm norm))


/****************************************************************************************\
*                                   Min/Max Filters                                      *
\****************************************************************************************/



/****************************************************************************************\
*                                   Separable Filters                                    *
\****************************************************************************************/


/* ///////////////////////////////////////////////////////////////////////////////////////////////////
//  Name:  ippiFilterRowBorderPipelineGetBufferSize_8u16s_C1R,   ippiFilterRowBorderPipelineGetBufferSize_8u16s_C3R
//         ippiFilterRowBorderPipelineGetBufferSize_16s_C1R,     ippiFilterRowBorderPipelineGetBufferSize_16s_C3R
//         ippiFilterRowBorderPipelineGetBufferSize_16u_C1R,     ippiFilterRowBorderPipelineGetBufferSize_16u_C3R
//         ippiFilterRowBorderPipelineGetBufferSize_Low_16s_C1R, ippiFilterRowBorderPipelineGetBufferSize_Low_16s_C3R
//         ippiFilterRowBorderPipelineGetBufferSize_32f_C1R,     ippiFilterRowBorderPipelineGetBufferSize_32f_C3R
//
//  Purpose:    Get size of external buffer.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width of the image or kernel size are less or equal zero
//
//  Parameters:
//    roiSize                  The image ROI size
//    kernelSize               The size of the kernel
//    pBufferSize              The pointer to the buffer size
*/

IPPAPI(IppStatus, ippiFilterRowBorderPipelineGetBufferSize_8u16s_C1R, (IppiSize roiSize, int kernelSize, int* pBufferSize))

IPPAPI(IppStatus, ippiFilterRowBorderPipelineGetBufferSize_8u16s_C3R, (IppiSize roiSize, int kernelSize, int* pBufferSize))

IPPAPI(IppStatus, ippiFilterRowBorderPipelineGetBufferSize_16s_C1R, (IppiSize roiSize, int kernelSize, int* pBufferSize))

IPPAPI(IppStatus, ippiFilterRowBorderPipelineGetBufferSize_16s_C3R, (IppiSize roiSize, int kernelSize, int* pBufferSize))

IPPAPI(IppStatus, ippiFilterRowBorderPipelineGetBufferSize_16u_C1R, (IppiSize roiSize, int kernelSize, int* pBufferSize))

IPPAPI(IppStatus, ippiFilterRowBorderPipelineGetBufferSize_16u_C3R, (IppiSize roiSize, int kernelSize, int* pBufferSize))

IPPAPI(IppStatus, ippiFilterRowBorderPipelineGetBufferSize_Low_16s_C1R, (IppiSize roiSize, int kernelSize, int* pBufferSize))

IPPAPI(IppStatus, ippiFilterRowBorderPipelineGetBufferSize_Low_16s_C3R, (IppiSize roiSize, int kernelSize, int* pBufferSize))

IPPAPI(IppStatus, ippiFilterRowBorderPipelineGetBufferSize_32f_C1R, (IppiSize roiSize, int kernelSize, int* pBufferSize))

IPPAPI(IppStatus, ippiFilterRowBorderPipelineGetBufferSize_32f_C3R, (IppiSize roiSize, int kernelSize, int* pBufferSize))


/*F///////////////////////////////////////////////////////////////////////////////////////////
//  Name:      ippiFilterRowBorderPipeline_8u16s_C1R,  ippiFilterRowBorderPipeline_8u16s_C3R
//             ippiFilterRowBorderPipeline_16s_C1R,    ippiFilterRowBorderPipeline_16s_C3R
//             ippiFilterRowBorderPipeline_16u_C1R,    ippiFilterRowBorderPipeline_16u_C3R
//             ippiFilterRowBorderPipeline_Low_16s_C1R, ippiFilterRowBorderPipeline_Low_16s_C3R
//             ippiFilterRowBorderPipeline_32f_C1R,    ippiFilterRowBorderPipeline_32f_C3R
//
//  Purpose:   Convolves source image rows with the row kernel
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//    ippStsAnchorErr          The anchor outside the kernel
//    ippStsBadArgErr          Wrong border type or zero divisor
//
//  Parameters:
//    pSrc                     The pointer to the source image
//    srcStep                  The step in the source image
//    ppDst                    The double pointer to the destination image
//    roiSize                  The image ROI size
//    pKernel                  The pointer to the kernel
//    kernelSize               The size of the kernel
//    xAnchor                  The anchor value , (0<=xAnchor<kernelSize)
//    borderType               The type of the border
//    borderValue              The value for the constant border
//    divisor                  The value to divide output pixels by , (for integer functions)
//    pBuffer                  The pointer to the working buffer
//    Notes:                   The output is the doulble pointer to support the circle buffer
//F*/

IPPAPI(IppStatus, ippiFilterRowBorderPipeline_8u16s_C1R, (const Ipp8u* pSrc, int srcStep, Ipp16s** ppDst,
                                        IppiSize roiSize, const Ipp16s* pKernel, int kernelSize, int xAnchor,
                                        IppiBorderType borderType, Ipp8u borderValue, int divisor, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterRowBorderPipeline_8u16s_C3R, (const Ipp8u* pSrc, int srcStep, Ipp16s** ppDst,
                                        IppiSize roiSize, const Ipp16s* pKernel, int kernelSize, int xAnchor,
                                        IppiBorderType borderType, Ipp8u borderValue[3], int divisor, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterRowBorderPipeline_16s_C1R, (const Ipp16s* pSrc, int srcStep, Ipp16s** ppDst,
                                        IppiSize roiSize, const Ipp16s* pKernel, int kernelSize, int xAnchor,
                                        IppiBorderType borderType, Ipp16s borderValue, int divisor, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterRowBorderPipeline_16s_C3R, (const Ipp16s* pSrc, int srcStep, Ipp16s** ppDst,
                                        IppiSize roiSize, const Ipp16s* pKernel, int kernelSize, int xAnchor,
                                        IppiBorderType borderType, Ipp16s borderValue[3], int divisor, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterRowBorderPipeline_Low_16s_C1R, (const Ipp16s* pSrc, int srcStep, Ipp16s** ppDst,
                                        IppiSize roiSize, const Ipp16s* pKernel, int kernelSize, int xAnchor,
                                        IppiBorderType borderType, Ipp16s borderValue, int divisor, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterRowBorderPipeline_Low_16s_C3R, (const Ipp16s* pSrc, int srcStep, Ipp16s** ppDst,
                                        IppiSize roiSize, const Ipp16s* pKernel, int kernelSize, int xAnchor,
                                        IppiBorderType borderType, Ipp16s borderValue[3], int divisor, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterRowBorderPipeline_16u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp16u** ppDst,
                                        IppiSize roiSize, const Ipp16u* pKernel, int kernelSize, int xAnchor,
                                        IppiBorderType borderType, Ipp16u borderValue, int divisor, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterRowBorderPipeline_16u_C3R, (const Ipp16u* pSrc, int srcStep, Ipp16u** ppDst,
                                        IppiSize roiSize, const Ipp16u* pKernel, int kernelSize, int xAnchor,
                                        IppiBorderType borderType, Ipp16u borderValue[3], int divisor, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterRowBorderPipeline_32f_C1R, (const Ipp32f* pSrc, int srcStep, Ipp32f** ppDst,
                                        IppiSize roiSize, const Ipp32f* pKernel, int kernelSize, int xAnchor,
                                        IppiBorderType borderType, Ipp32f borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterRowBorderPipeline_32f_C3R, (const Ipp32f* pSrc, int srcStep, Ipp32f** ppDst,
                                        IppiSize roiSize, const Ipp32f* pKernel, int kernelSize, int xAnchor,
                                        IppiBorderType borderType, Ipp32f borderValue[3], Ipp8u* pBuffer))


/* ///////////////////////////////////////////////////////////////////////////////////////////////////
//  Name:      ippiFilterColumnPipelineGetBufferSize_16s_C1R,       ippiFilterColumnPipelineGetBufferSize_16s_C3R
//             ippiFilterColumnPipelineGetBufferSize_16u_C1R,       ippiFilterColumnPipelineGetBufferSize_16u_C3R
//             ippiFilterColumnPipelineGetBufferSize_Low_16s_C1R,   ippiFilterColumnPipelineGetBufferSize_Low_16s_C3R
//             ippiFilterColumnPipelineGetBufferSize_16s8u_C1R,     ippiFilterColumnPipelineGetBufferSize_16s8u_C3R
//             ippiFilterColumnPipelineGetBufferSize_16s8s_C1R,     ippiFilterColumnPipelineGetBufferSize_16s8s_C3R
//             ippiFilterColumnPipelineGetBufferSize_32f_C1R,       ippiFilterColumnPipelineGetBufferSize_32f_C3R
//
//  Purpose:    Get size of external buffer.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width of the image or kernel size are less or equal zero
//
//  Parameters:
//    roiSize                  The image ROI size
//    kernelSize               The size of the kernel
//    pBufferSize              The pointer to the buffer size
*/


IPPAPI(IppStatus, ippiFilterColumnPipelineGetBufferSize_16s_C1R, (IppiSize roiSize, int kernelSize, int* pBufferSize))

IPPAPI(IppStatus, ippiFilterColumnPipelineGetBufferSize_16s_C3R, (IppiSize roiSize, int kernelSize, int* pBufferSize))

IPPAPI(IppStatus, ippiFilterColumnPipelineGetBufferSize_Low_16s_C1R, (IppiSize roiSize, int kernelSize, int* pBufferSize))

IPPAPI(IppStatus, ippiFilterColumnPipelineGetBufferSize_Low_16s_C3R, (IppiSize roiSize, int kernelSize, int* pBufferSize))

IPPAPI(IppStatus, ippiFilterColumnPipelineGetBufferSize_16u_C1R, (IppiSize roiSize, int kernelSize, int* pBufferSize))

IPPAPI(IppStatus, ippiFilterColumnPipelineGetBufferSize_16u_C3R, (IppiSize roiSize, int kernelSize, int* pBufferSize))

IPPAPI(IppStatus, ippiFilterColumnPipelineGetBufferSize_16s8u_C1R, (IppiSize roiSize, int kernelSize, int* pBufferSize))

IPPAPI(IppStatus, ippiFilterColumnPipelineGetBufferSize_16s8u_C3R, (IppiSize roiSize, int kernelSize, int* pBufferSize))

IPPAPI(IppStatus, ippiFilterColumnPipelineGetBufferSize_16s8s_C1R, (IppiSize roiSize, int kernelSize, int* pBufferSize))

IPPAPI(IppStatus, ippiFilterColumnPipelineGetBufferSize_16s8s_C3R, (IppiSize roiSize, int kernelSize, int* pBufferSize))

IPPAPI(IppStatus, ippiFilterColumnPipelineGetBufferSize_32f_C1R, (IppiSize roiSize, int kernelSize, int* pBufferSize))

IPPAPI(IppStatus, ippiFilterColumnPipelineGetBufferSize_32f_C3R, (IppiSize roiSize, int kernelSize, int* pBufferSize))


/*F///////////////////////////////////////////////////////////////////////////////////////////
//  Name:      ippiFilterColumnPipeline_16s_C1R,     ippiFilterColumnPipeline_16s_C3R
//             ippiFilterColumnPipeline_16u_C1R,     ippiFilterColumnPipeline_16u_C3R
//             ippiFilterColumnPipeline_Low_16s_C1R, ippiFilterColumnPipeline_Low_16s_C3R
//             ippiFilterColumnPipeline_16s8u_C1R,   ippiFilterColumnPipeline_16s8u_C3R
//             ippiFilterColumnPipeline_16s8s_C1R,   ippiFilterColumnPipeline_16s8s_C3R
//             ippiFilterColumnPipeline_32f_C1R,     ippiFilterColumnPipeline_32f_C3R
//  Purpose:   Convolves source image rows with the row kernel
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//    ippStsBadArgErr          Zero divisor
//
//  Parameters:
//    ppSrc                    The double pointer to the source image
//    pDst                     The pointer to the destination image
//    dstStep                  The step in the destination image
//    roiSize                  The image ROI size
//    pKernel                  The pointer to the kernel
//    kernelSize               The size of the kernel
//    divisor                  The value to divide output pixels by , (for integer functions)
//    pBuffer                  The pointer to the working buffer
//    Notes:                   The input is the doulble pointer to support the circle buffer
//F*/

IPPAPI(IppStatus, ippiFilterColumnPipeline_16s_C1R, (const Ipp16s** ppSrc, Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                           const Ipp16s* pKernel, int kernelSize, int divisor, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterColumnPipeline_16s_C3R, (const Ipp16s** ppSrc, Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                           const Ipp16s* pKernel, int kernelSize, int divisor, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterColumnPipeline_Low_16s_C1R, (const Ipp16s** ppSrc, Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                           const Ipp16s* pKernel, int kernelSize, int divisor, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterColumnPipeline_Low_16s_C3R, (const Ipp16s** ppSrc, Ipp16s* pDst, int dstStep, IppiSize roiSize,
                                           const Ipp16s* pKernel, int kernelSize, int divisor, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterColumnPipeline_16u_C1R, (const Ipp16u** ppSrc, Ipp16u* pDst, int dstStep, IppiSize roiSize,
                                           const Ipp16u* pKernel, int kernelSize, int divisor, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterColumnPipeline_16u_C3R, (const Ipp16u** ppSrc, Ipp16u* pDst, int dstStep, IppiSize roiSize,
                                           const Ipp16u* pKernel, int kernelSize, int divisor, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterColumnPipeline_16s8u_C1R, (const Ipp16s** ppSrc, Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                           const Ipp16s* pKernel, int kernelSize, int divisor, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterColumnPipeline_16s8u_C3R, (const Ipp16s** ppSrc, Ipp8u* pDst, int dstStep, IppiSize roiSize,
                                           const Ipp16s* pKernel, int kernelSize, int divisor, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterColumnPipeline_16s8s_C1R, (const Ipp16s** ppSrc, Ipp8s* pDst, int dstStep, IppiSize roiSize,
                                           const Ipp16s* pKernel, int kernelSize, int divisor, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterColumnPipeline_16s8s_C3R, (const Ipp16s** ppSrc, Ipp8s* pDst, int dstStep, IppiSize roiSize,
                                           const Ipp16s* pKernel, int kernelSize, int divisor, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterColumnPipeline_32f_C1R, (const Ipp32f** ppSrc, Ipp32f* pDst, int dstStep, IppiSize roiSize,
                                           const Ipp32f* pKernel, int kernelSize, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterColumnPipeline_32f_C3R, (const Ipp32f** ppSrc, Ipp32f* pDst, int dstStep, IppiSize roiSize,
                                           const Ipp32f* pKernel, int kernelSize, Ipp8u* pBuffer))


/****************************************************************************************\
*                                   Fixed Filters                                        *
\****************************************************************************************/


/* ///////////////////////////////////////////////////////////////////////////////////////////////////
//  Name:   ippiFilterSobelCrossGetBufferSize_8u16s_C1R,  ippiFilterLaplacianGetBufferSize_8u16s_C1R,
//          ippiFilterLowpassGetBufferSize_8u_C1R,        ippiFilterSobelCrossGetBufferSize_32f_C1R,
//          ippiFilterLaplacianGetBufferSize_32f_C1R,     ippiFilterLowpassGetBufferSize_32f_C1R
//
//
//  Purpose:    Perform convolution operation with fixed kernels 3x3 and 5x5
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width of the image is less or equal zero
//    ippStsMaskSizeErr        Wrong mask size
//
//  Parameters:
//    roiSize                  The image ROI size
//    mask                     The mask size
//    pBufferSize              The pointer to the buffer size
*/
IPPAPI(IppStatus, ippiFilterSobelCrossGetBufferSize_8u16s_C1R,      (IppiSize roiSize, IppiMaskSize mask, int* pBufferSize))

IPPAPI(IppStatus, ippiFilterLaplacianGetBufferSize_8u16s_C1R,       (IppiSize roiSize, IppiMaskSize mask, int* pBufferSize))

IPPAPI(IppStatus, ippiFilterLowpassGetBufferSize_8u_C1R,            (IppiSize roiSize, IppiMaskSize mask, int* pBufferSize))

IPPAPI(IppStatus, ippiFilterSobelCrossGetBufferSize_32f_C1R,      (IppiSize roiSize, IppiMaskSize mask, int* pBufferSize))

IPPAPI(IppStatus, ippiFilterLaplacianGetBufferSize_32f_C1R,       (IppiSize roiSize, IppiMaskSize mask, int* pBufferSize))

IPPAPI(IppStatus, ippiFilterLowpassGetBufferSize_32f_C1R,         (IppiSize roiSize, IppiMaskSize mask, int* pBufferSize))


/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name:   ippiFilterSobelCrossBorder_8u16s_C1R,  ippiFilterLaplacianBorder_8u16s_C1R
//          ippiFilterLowpassBorder_8u_C1R,        ippiFilterSobelCrossBorder_32f_C1R
//          ippiFilterLowpassBorder_32f_C1R,       ippiFilterLaplacianBorder_32f_C1R
//
//  Purpose:    Perform convolution operation with fixed kernels 3x3 and 5x5
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//    ippStsMaskSizeErr        Wrong mask size
//    ippStsBadArgErr          Wrong border type or zero divisor
//
//  Parameters:
//    pSrc                     The pointer to the source image
//    srcStep                  The step in the source image
//    pDst                     The pointer to the destination image
//    dstStep                  The step in the destination image
//    roiSize                  The image ROI size
//    mask                     The mask size
//    borderType               The type of the border
//    borderValue              The value for the constant border
//    pBuffer                  The pointer to the working buffer
//    divisor                  The value to divide output pixels by , (for integer functions)
//F*/

IPPAPI(IppStatus, ippiFilterSobelCrossBorder_8u16s_C1R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp8u borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterLaplacianBorder_8u16s_C1R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp8u borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterLowpassBorder_8u_C1R, (const Ipp8u* pSrc, int srcStep,
                                      Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp8u borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterSobelCrossBorder_32f_C1R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp32f  borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterLowpassBorder_32f_C1R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp32f  borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterLaplacianBorder_32f_C1R, (const Ipp32f* pSrc, int srcStep,
                                      Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask,
                                      IppiBorderType borderType, Ipp32f  borderValue, Ipp8u* pBuffer))


/* ///////////////////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiGenSobelKernel_16s,       ippiGenSobelKernel_32f
//
//  Purpose:    Generate kernel for Sobel differential operator
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The size of kernel is less or equal zero
//    ippStsBadArgErr          derivative order is less than 0
//
//  Parameters:
//    pDst                     The pointer to the destination kernel
//    kernelSize               The kernel size, odd
//    dx                       The order of derivative (0<=dx<kernelSize)
//    sign                     Reverse signs in sign < 0
*/

IPPAPI (IppStatus, ippiGenSobelKernel_16s, (Ipp16s* pDst, int kernelSize, int dx, int sign))

IPPAPI (IppStatus, ippiGenSobelKernel_32f, (Ipp32f *pDst, int kernelSize, int dx, int sign))


/****************************************************************************************\
*                                   Image Integrals                                     *
\****************************************************************************************/


/* /////////////////////////////////////////////////////////////////////////////////////
//  Name: ippiIntegral, ippiTiltedIntegral
//        ippiSqrIntegral, ippiTiltedSqrIntegral
//
//  Purpose:   calculates pixel sum on subimage
//
//  Returns:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//
//  Parameters:
//    pSrc                     The pointer to source image
//    srcStep                  The step in source image
//    pDst                     The pointer to destination integral image
//    dstStep                  The step in destination image
//    pSq                      The pointer to destination square integral image
//    sqStep                   The step in destination image
//    roiSize                  The source and destination image ROI size.
//    val                      The value to add to pDst image pixels.
//    valSqr                   The value to add to pSq image pixels.
*/
IPPAPI(IppStatus, ippiIntegral_8u32s_C1R,(const Ipp8u* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize srcRoiSize, Ipp32s val))
IPPAPI(IppStatus, ippiIntegral_8u32f_C1R,(const Ipp8u* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize srcRoiSize, Ipp32f val))
IPPAPI(IppStatus, ippiIntegral_32f_C1R,  (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize srcRoiSize))

IPPAPI(IppStatus, ippiTiltedIntegral_8u32s_C1R,(const Ipp8u* pSrc, int srcStep, Ipp32s* pDst, int dstStep, IppiSize roiSize, Ipp32s val))
IPPAPI(IppStatus, ippiTiltedIntegral_8u32f_C1R,(const Ipp8u* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, Ipp32f val))

IPPAPI(IppStatus, ippiSqrIntegral_8u32s_C1R,   (const Ipp8u* pSrc, int srcStep, Ipp32s* pDst, int dstStep, Ipp32s* pSqr, int sqrStep, IppiSize roi, Ipp32s val, Ipp32s valSqr))
IPPAPI(IppStatus, ippiSqrIntegral_8u32s64f_C1R,(const Ipp8u* pSrc, int srcStep, Ipp32s* pDst, int dstStep, Ipp64f* pSqr, int sqrStep, IppiSize roiSize, Ipp32s val, Ipp64f valSqr))
IPPAPI(IppStatus, ippiSqrIntegral_8u32f64f_C1R,(const Ipp8u* pSrc, int srcStep, Ipp32f* pDst, int dstStep, Ipp64f* pSqr, int sqrStep, IppiSize roiSize, Ipp32f val, Ipp64f valSqr))

IPPAPI(IppStatus, ippiTiltedSqrIntegral_8u32s_C1R,   (const Ipp8u* pSrc, int srcStep, Ipp32s* pDst, int dstStep, Ipp32s* pSqr, int sqrStep, IppiSize roi, Ipp32s val, Ipp32s valSqr))
IPPAPI(IppStatus, ippiTiltedSqrIntegral_8u32s64f_C1R,(const Ipp8u* pSrc, int srcStep, Ipp32s* pDst, int dstStep, Ipp64f* pSqr, int sqrStep, IppiSize roiSize, Ipp32s val, Ipp64f valSqr))
IPPAPI(IppStatus, ippiTiltedSqrIntegral_8u32f64f_C1R,(const Ipp8u* pSrc, int srcStep, Ipp32f* pDst, int dstStep, Ipp64f* pSqr, int sqrStep, IppiSize roiSize, Ipp32f val, Ipp64f valSqr))



/****************************************************************************************\
*                                 Image Mean and Variance                                *
\****************************************************************************************/


/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name: ippiMean_8u_C1MR,   ippiMean_16u_C1MR,  ippiMean_32f_C1MR,
//        ippiMean_8u_C3CMR,  ippiMean_16u_C3CMR, ippiMean_32f_C3CMR
//
//  Purpose:  Find mean value for selected region
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//    ippStsCOIErr             COI index is illegal (coi<1 || coi>3)
//
//  Parameters:
//    pSrc                     Pointer to image
//    srcStep                  Image step
//    pMask                    Pointer to mask image
//    maskStep                 Step in the mask image
//    roiSize                  Size of image ROI
//    coi                      Index of color channel (1..3) (if color image)
//    pMean                    Returned mean value
//
//  Notes:
//F*/

IPPAPI( IppStatus, ippiMean_8u_C1MR, ( const Ipp8u* pSrc, int srcStep,
                                       const Ipp8u* pMask, int maskStep,
                                       IppiSize roiSize, Ipp64f* pMean ))

IPPAPI( IppStatus, ippiMean_8u_C3CMR, ( const Ipp8u* pSrc, int srcStep,
                                        const Ipp8u* pMask, int maskStep,
                                        IppiSize roiSize, int coi, Ipp64f* pMean ))

IPPAPI( IppStatus, ippiMean_16u_C1MR, ( const Ipp16u* pSrc, int srcStep,
                                        const Ipp8u* pMask, int maskStep,
                                        IppiSize roiSize, Ipp64f* pMean ))

IPPAPI( IppStatus, ippiMean_16u_C3CMR, ( const Ipp16u* pSrc, int srcStep,
                                         const Ipp8u* pMask, int maskStep,
                                         IppiSize roiSize, int coi, Ipp64f* pMean ))

IPPAPI( IppStatus, ippiMean_32f_C1MR, ( const Ipp32f* pSrc, int srcStep,
                                        const Ipp8u* pMask, int maskStep,
                                        IppiSize roiSize, Ipp64f* pMean ))

IPPAPI( IppStatus, ippiMean_32f_C3CMR, ( const Ipp32f* pSrc, int srcStep,
                                         const Ipp8u* pMask, int maskStep,
                                         IppiSize roiSize, int coi, Ipp64f* pMean ))


/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name: ippiMean_StdDev_8u_C1R,   ippiMean_StdDev_32f_C1R,
//        ippiMean_StdDev_16u_C1R,  ippiMean_StdDev_32f_C3CR,
//        ippiMean_StdDev_8u_C3CR,  ippiMean_StdDev_16u_C3CR,
//
//  Purpose:  Find mean and standard deviation values for selected region
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//    ippStsCOIErr             COI index is illegal (coi<1 || coi>3)
//
//  Parameters:
//    pSrc                     Pointer to image
//    srcStep                  Image step
//    roiSize                  Size of image ROI
//    coi                      Index of color channel (1..3) (if color image)
//    pMean                    Returned mean value
//    pStdDev                  Returned standard deviation
//
//  Notes:
//F*/

IPPAPI( IppStatus, ippiMean_StdDev_8u_C1R, ( const Ipp8u* pSrc, int srcStep,
                                             IppiSize roiSize,
                                             Ipp64f* pMean, Ipp64f* pStdDev ))

IPPAPI( IppStatus, ippiMean_StdDev_8u_C3CR, ( const Ipp8u* pSrc, int srcStep,
                                              IppiSize roiSize, int coi,
                                              Ipp64f* pMean, Ipp64f* pStdDev ))

IPPAPI( IppStatus, ippiMean_StdDev_16u_C1R, ( const Ipp16u* pSrc, int srcStep,
                                              IppiSize roiSize,
                                              Ipp64f* pMean, Ipp64f* pStdDev ))

IPPAPI( IppStatus, ippiMean_StdDev_16u_C3CR, ( const Ipp16u* pSrc, int srcStep,
                                               IppiSize roiSize, int coi,
                                               Ipp64f* pMean, Ipp64f* pStdDev ))

IPPAPI( IppStatus, ippiMean_StdDev_32f_C1R, ( const Ipp32f* pSrc, int srcStep,
                                              IppiSize roiSize,
                                              Ipp64f* pMean, Ipp64f* pStdDev ))

IPPAPI( IppStatus, ippiMean_StdDev_32f_C3CR, ( const Ipp32f* pSrc, int srcStep,
                                               IppiSize roiSize, int coi,
                                               Ipp64f* pMean, Ipp64f* pStdDev ))


/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name: ippiMean_StdDev_8u_C1MR,   ippiMean_StdDev_8u_C3CMR,
//        ippiMean_StdDev_16u_C1MR,  ippiMean_StdDev_16u_C3CMR,
//        ippiMean_StdDev_32f_C1MR,  ippiMean_StdDev_32f_C3CMR,
//
//  Purpose:  Find mean and standard deviation values for selected region
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//
//  Parameters:
//    pSrc                     Pointer to image
//    srcStep                  Image step
//    pMask                    Pointer to mask image
//    maskStep                 Step in the mask image
//    roiSize                  Size of image ROI
//    coi                      Index of color channel (1..3) (if color image)
//    pMean                    Returned mean value
//    pStdDev                  Returned standard deviation
//
//  Notes:
//F*/

IPPAPI( IppStatus, ippiMean_StdDev_8u_C1MR, ( const Ipp8u* pSrc, int srcStep,
                                              const Ipp8u* pMask, int maskStep,
                                              IppiSize roiSize,
                                              Ipp64f* pMean, Ipp64f* pStdDev ))

IPPAPI( IppStatus, ippiMean_StdDev_8u_C3CMR, ( const Ipp8u* pSrc, int srcStep,
                                               const Ipp8u* pMask, int maskStep,
                                               IppiSize roiSize, int coi,
                                               Ipp64f* pMean, Ipp64f* pStdDev ))

IPPAPI( IppStatus, ippiMean_StdDev_16u_C1MR, ( const Ipp16u* pSrc, int srcStep,
                                              const Ipp8u* pMask, int maskStep,
                                              IppiSize roiSize,
                                              Ipp64f* pMean, Ipp64f* pStdDev ))

IPPAPI( IppStatus, ippiMean_StdDev_16u_C3CMR, ( const Ipp16u* pSrc, int srcStep,
                                               const Ipp8u* pMask, int maskStep,
                                               IppiSize roiSize, int coi,
                                               Ipp64f* pMean, Ipp64f* pStdDev ))

IPPAPI( IppStatus, ippiMean_StdDev_32f_C1MR, ( const Ipp32f* pSrc, int srcStep,
                                               const Ipp8u* pMask, int maskStep,
                                               IppiSize roiSize,
                                               Ipp64f* pMean, Ipp64f* pStdDev ))

IPPAPI( IppStatus, ippiMean_StdDev_32f_C3CMR, ( const Ipp32f* pSrc, int srcStep,
                                                const Ipp8u* pMask, int maskStep,
                                                IppiSize roiSize, int coi,
                                                Ipp64f* pMean, Ipp64f* pStdDev ))


/****************************************************************************************\
*                                   Variance on Window                                   *
\****************************************************************************************/


/*F/////////////////////////////////////////////////////////////////////////////////////
//  Name: ippiRectStdDev, ippiTiltedRectStdDev
//
//  Purpose:   Calculates standard deviation on rectangular window
//
//  Returns:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//
//  Parameters:
//    pSrc                     The pointer to source image of integrals
//    srcStep                  The step in source image
//    pSqr                     The pointer to destination square integral image
//    sqrStep                  The step in destination image
//    pDst                     The pointer to destination image
//    dstStep                  The step in destination image
//    roiSize                  The destination image ROI size.
//    rect                     The rectangular window for standard deviation calculation.
//    scaleFactor              Output scale factor
//
//  Notes:
//F*/
IPPAPI(IppStatus, ippiRectStdDev_32s_C1RSfs,  (const Ipp32s* pSrc, int srcStep, const Ipp32s* pSqr, int sqrStep, Ipp32s* pDst, int dstStep, IppiSize roi, IppiRect rect, int scaleFactor))
IPPAPI(IppStatus, ippiRectStdDev_32s32f_C1R,  (const Ipp32s* pSrc, int srcStep, const Ipp64f* pSqr, int sqrStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiRect rect))
IPPAPI(IppStatus, ippiRectStdDev_32f_C1R,  (const Ipp32f* pSrc, int srcStep, const Ipp64f* pSqr, int sqrStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiRect rect))

IPPAPI(IppStatus, ippiTiltedRectStdDev_32s32f_C1R,  (const Ipp32s* pSrc, int srcStep, const Ipp64f* pSqr, int sqrStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiRect rect))
IPPAPI(IppStatus, ippiTiltedRectStdDev_32s_C1RSfs,  (const Ipp32s* pSrc, int srcStep, const Ipp32s* pSqr, int sqrStep, Ipp32s* pDst, int dstStep, IppiSize roi, IppiRect rect, int scaleFactor))
IPPAPI(IppStatus, ippiTiltedRectStdDev_32f_C1R,  (const Ipp32f* pSrc, int srcStep, const Ipp64f* pSqr, int sqrStep, Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiRect rect))


/****************************************************************************************\
*                                   Image Minimum and Maximum                            *
\****************************************************************************************/


/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name: ippiMinMaxIndx_8u_C1R,   ippiMinMaxIndx_8u_C3CR,
//        ippiMinMaxIndx_16u_C1R,  ippiMinMaxIndx_16u_C3CR,
//        ippiMinMaxIndx_32f_C1R,  ippiMinMaxIndx_32f_C3CR,
//
//  Purpose:  Finds minimum and maximum values in the image and their coordinates
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//
//  Parameters:
//    pSrc                     Pointer to image
//    srcStep                  Image step
//    roiSize                  Size of image ROI
//    coi                      Index of color channel (1..3) (if color image)
//    pMinVal                  Pointer to minimum value
//    pMaxVal                  Pointer to maximum value
//    pMinIndex                Minimum's coordinates
//    pMaxIndex                Maximum's coordinates
//
//  Notes:
//    Any of output parameters is optional
//F*/

IPPAPI(IppStatus, ippiMinMaxIndx_8u_C1R,( const Ipp8u* pSrc, int srcStep, IppiSize roiSize,
                                          Ipp32f* pMinVal, Ipp32f* pMaxVal,
                                          IppiPoint* pMinIndex, IppiPoint* pMaxIndex ))

IPPAPI(IppStatus, ippiMinMaxIndx_8u_C3CR,( const Ipp8u* pSrc, int srcStep,
                                           IppiSize roiSize, int coi,
                                           Ipp32f* pMinVal, Ipp32f* pMaxVal,
                                           IppiPoint* pMinIndex, IppiPoint* pMaxIndex ))

IPPAPI(IppStatus, ippiMinMaxIndx_16u_C1R,( const Ipp16u* pSrc, int srcStep, IppiSize roiSize,
                                           Ipp32f* pMinVal, Ipp32f* pMaxVal,
                                           IppiPoint* pMinIndex, IppiPoint* pMaxIndex ))

IPPAPI(IppStatus, ippiMinMaxIndx_16u_C3CR,( const Ipp16u* pSrc, int srcStep,
                                            IppiSize roiSize, int coi,
                                            Ipp32f* pMinVal, Ipp32f* pMaxVal,
                                            IppiPoint* pMinIndex, IppiPoint* pMaxIndex ))

IPPAPI(IppStatus, ippiMinMaxIndx_32f_C1R,( const Ipp32f* pSrc, int step, IppiSize roiSize,
                                           Ipp32f* pMinVal, Ipp32f* pMaxVal,
                                           IppiPoint* pMinIndex, IppiPoint* pMaxIndex ))

IPPAPI(IppStatus, ippiMinMaxIndx_32f_C3CR,( const Ipp32f* pSrc, int step, IppiSize roiSize,
                                            int coi, Ipp32f* pMinVal, Ipp32f* pMaxVal,
                                            IppiPoint* pMinIndex, IppiPoint* pMaxIndex))


/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name: ippiMinMaxIndx_8u_C1MR,   ippiMinMaxIndx_8u_C3CMR,
//        ippiMinMaxIndx_16u_C1MR,  ippiMinMaxIndx_16u_C3CMR,
//        ippiMinMaxIndx_32f_C1MR,  ippiMinMaxIndx_32f_C3CMR,
//
//  Purpose:  Finds minimum and maximum values in the image and their coordinates
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//
//  Parameters:
//    pSrc                     Pointer to image
//    srcStep                  Image step
//    pMask                    Pointer to mask image
//    maskStep                 Step in the mask image
//    roiSize                  Size of image ROI
//    coi                      Index of color channel (1..3) (if color image)
//    pMinVal                  Pointer to minimum value
//    pMaxVal                  Pointer to maximum value
//    pMinIndex                Minimum's coordinates
//    pMaxIndex                Maximum's coordinates
//
//  Notes:
//    Any of output parameters is optional
//F*/

IPPAPI(IppStatus, ippiMinMaxIndx_8u_C1MR,( const Ipp8u* pSrc, int srcStep,
                                           const Ipp8u* pMask, int maskStep,
                                           IppiSize roiSize,
                                           Ipp32f* pMinVal, Ipp32f* pMaxVal,
                                           IppiPoint* pMinIndex, IppiPoint* pMaxIndex ))

IPPAPI( IppStatus, ippiMinMaxIndx_8u_C3CMR, ( const Ipp8u* pSrc, int srcStep,
                                              const Ipp8u* pMask, int maskStep,
                                              IppiSize roiSize, int coi,
                                              Ipp32f* pMinVal, Ipp32f* pMaxVal,
                                              IppiPoint* pMinIndex, IppiPoint* pMaxIndex ))

IPPAPI(IppStatus, ippiMinMaxIndx_16u_C1MR,( const Ipp16u* pSrc, int srcStep,
                                            const Ipp8u* pMask, int maskStep,
                                            IppiSize roiSize,
                                            Ipp32f* pMinVal, Ipp32f* pMaxVal,
                                            IppiPoint* pMinIndex, IppiPoint* pMaxIndex ))

IPPAPI( IppStatus, ippiMinMaxIndx_16u_C3CMR, ( const Ipp16u* pSrc, int srcStep,
                                               const Ipp8u* pMask, int maskStep,
                                               IppiSize roiSize, int coi,
                                               Ipp32f* pMinVal, Ipp32f* pMaxVal,
                                               IppiPoint* pMinIndex, IppiPoint* pMaxIndex ))

IPPAPI( IppStatus, ippiMinMaxIndx_32f_C1MR, ( const Ipp32f* pSrc, int srcStep,
                                              const Ipp8u* pMask, int maskStep,
                                              IppiSize roiSize,
                                              Ipp32f* pMinVal, Ipp32f* pMaxVal,
                                              IppiPoint* pMinIndex, IppiPoint* pMaxIndex ))

IPPAPI( IppStatus, ippiMinMaxIndx_32f_C3CMR, ( const Ipp32f* pSrc, int srcStep,
                                               const Ipp8u* pMask, int maskStep,
                                               IppiSize roiSize, int coi,
                                               Ipp32f* pMinVal, Ipp32f* pMaxVal,
                                               IppiPoint* pMinIndex, IppiPoint* pMaxIndex ))


/****************************************************************************************\
*                                     Image Norms                                        *
\****************************************************************************************/


/*F///////////////////////////////////////////////////////////////////////////////////////
//  Names: ippiNorm_Inf_8u_C1MR,       ippiNorm_Inf_32f_C1MR,
//         ippiNorm_Inf_16u_C1MR,      ippiNorm_Inf_8u_C3CMR,
//         ippiNorm_Inf_16u_C3CMR,     ippiNorm_Inf_32f_C3CMR,
//         ippiNormDiff_Inf_8u_C1MR,   ippiNormDiff_Inf_8u_C3CMR,
//         ippiNormDiff_Inf_16u_C1MR,  ippiNormDiff_Inf_32f_C1MR,
//         ippiNormDiff_Inf_16u_C3CMR, ippiNormDiff_Inf_32f_C3CMR,
//         ippiNormRel_Inf_8u_C1MR,    ippiNormRel_Inf_8u_C3CMR,
//         ippiNormRel_Inf_16u_C1MR,   ippiNormRel_Inf_32f_C1MR,
//         ippiNormRel_Inf_16u_C3CMR,  ippiNormRel_Inf_32f_C3CMR,
//
//         ippiNorm_L1_8u_C1MR,        ippiNorm_L1_8u_C3CMR,
//         ippiNorm_L1_16u_C1MR,       ippiNorm_L1_32f_C1MR,
//         ippiNorm_L1_16u_C3CMR,      ippiNorm_L1_32f_C3CMR,
//         ippiNormDiff_L1_8u_C1MR,    ippiNormDiff_L1_8u_C3CMR,
//         ippiNormDiff_L1_16u_C1MR,   ippiNormDiff_L1_32f_C1MR,
//         ippiNormDiff_L1_16u_C3CMR,  ippiNormDiff_L1_32f_C3CMR,
//         ippiNormRel_L1_8u_C1MR,     ippiNormRel_L1_8u_C3CMR,
//         ippiNormRel_L1_16u_C1MR,    ippiNormRel_L1_32f_C1MR,
//         ippiNormRel_L1_16u_C3CMR,   ippiNormRel_L1_32f_C3CMR,
//
//         ippiNorm_L2_8u_C1MR,        ippiNorm_L2_8u_C3CMR,
//         ippiNorm_L2_16u_C1MR,       ippiNorm_L2_32f_C1MR,
//         ippiNorm_L2_16u_C3CMR,      ippiNorm_L2_32f_C3CMR,
//         ippiNormDiff_L2_8u_C1MR,    ippiNormDiff_L2_8u_C3CMR,
//         ippiNormDiff_L2_16u_C1MR,   ippiNormDiff_L2_32f_C1MR,
//         ippiNormDiff_L2_16u_C3CMR,  ippiNormDiff_L2_32f_C3CMR,
//         ippiNormRel_L2_8u_C1MR,     ippiNormRel_L2_8u_C3CMR,
//         ippiNormRel_L2_16u_C1MR,    ippiNormRel_L2_32f_C1MR,
//         ippiNormRel_L2_16u_C3CMR,   ippiNormRel_L2_32f_C3CMR
//
//  Purpose: Calculates ordinary, differential or relative norms of one or two images
//           in an arbitrary image region.
//
//  Returns:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//
//  Parameters:
//    pSrc, pSrc1              Pointers to source and mask images
//    pSrc2, pMask
//    srcStep, src1Step        Their steps
//    src2Step, maskStep
//    roiSize                  Their size or ROI size
//    coi                      COI index (1..3) (if 3-channel images)
//    pNorm                    The pointer to calculated norm
//
//  Notes:
//F*/

/* ///////////////////////////////// 8uC1 flavor ////////////////////////////////////// */

IPPAPI( IppStatus, ippiNorm_Inf_8u_C1MR, ( const Ipp8u* pSrc, int srcStep,
                                           const Ipp8u* pMask,int maskStep,
                                           IppiSize roiSize, Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNorm_Inf_16u_C1MR, ( const Ipp16u* pSrc, int srcStep,
                                            const Ipp8u* pMask,int maskStep,
                                            IppiSize roiSize, Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNorm_Inf_32f_C1MR, ( const Ipp32f* pSrc, int srcStep,
                                            const Ipp8u* pMask, int maskStep,
                                            IppiSize roiSize, Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNorm_Inf_8u_C3CMR, ( const Ipp8u* pSrc, int srcStep,
                                            const Ipp8u* pMask,int maskStep,
                                            IppiSize roiSize, int coi, Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNorm_Inf_16u_C3CMR, ( const Ipp16u* pSrc, int srcStep,
                                             const Ipp8u* pMask,int maskStep,
                                             IppiSize roiSize, int coi, Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNorm_Inf_32f_C3CMR, ( const Ipp32f* pSrc, int srcStep,
                                             const Ipp8u* pMask, int maskStep,
                                             IppiSize roiSize, int coi, Ipp64f* pNorm ) )


IPPAPI( IppStatus, ippiNormDiff_Inf_8u_C1MR, ( const Ipp8u* pSrc1, int src1Step,
                                               const Ipp8u* pSrc2, int src2Step,
                                               const Ipp8u* pMask, int maskStep,
                                               IppiSize roiSize,   Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNormDiff_Inf_16u_C1MR, ( const Ipp16u* pSrc1, int src1Step,
                                                const Ipp16u* pSrc2, int src2Step,
                                                const Ipp8u* pMask, int maskStep,
                                                IppiSize roiSize,   Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNormDiff_Inf_32f_C1MR, ( const Ipp32f* pSrc1, int src1Step,
                                                const Ipp32f* pSrc2, int src2Step,
                                                const Ipp8u* pMask,  int maskStep,
                                                IppiSize roiSize,    Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNormDiff_Inf_8u_C3CMR, (const Ipp8u* pSrc1, int src1Step,
                                               const Ipp8u* pSrc2, int src2Step,
                                               const Ipp8u* pMask, int maskStep,
                                               IppiSize roiSize, int coi, Ipp64f* pNorm ))

IPPAPI( IppStatus, ippiNormDiff_Inf_16u_C3CMR, (const Ipp16u* pSrc1, int src1Step,
                                                const Ipp16u* pSrc2, int src2Step,
                                                const Ipp8u* pMask, int maskStep,
                                                IppiSize roiSize, int coi, Ipp64f* pNorm ))

IPPAPI( IppStatus, ippiNormDiff_Inf_32f_C3CMR, (const Ipp32f* pSrc1, int src1Step,
                                                const Ipp32f* pSrc2, int src2Step,
                                                const Ipp8u* pMask,  int maskStep,
                                                IppiSize roiSize, int coi, Ipp64f* pNorm ))


IPPAPI( IppStatus, ippiNormRel_Inf_8u_C1MR, ( const Ipp8u* pSrc1, int src1Step,
                                              const Ipp8u* pSrc2, int src2Step,
                                              const Ipp8u* pMask, int maskStep,
                                              IppiSize roiSize,   Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNormRel_Inf_16u_C1MR, ( const Ipp16u* pSrc1, int src1Step,
                                               const Ipp16u* pSrc2, int src2Step,
                                               const Ipp8u* pMask, int maskStep,
                                               IppiSize roiSize,   Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNormRel_Inf_32f_C1MR, ( const Ipp32f* pSrc1, int src1Step,
                                               const Ipp32f* pSrc2, int src2Step,
                                               const Ipp8u* pMask,  int maskStep,
                                               IppiSize roiSize,    Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNormRel_Inf_8u_C3CMR, ( const Ipp8u* pSrc1, int src1Step,
                                               const Ipp8u* pSrc2, int src2Step,
                                               const Ipp8u* pMask, int maskStep,
                                               IppiSize roiSize, int coi, Ipp64f* pNorm ))

IPPAPI( IppStatus, ippiNormRel_Inf_16u_C3CMR, ( const Ipp16u* pSrc1, int src1Step,
                                                const Ipp16u* pSrc2, int src2Step,
                                                const Ipp8u* pMask, int maskStep,
                                                IppiSize roiSize, int coi, Ipp64f* pNorm ))

IPPAPI( IppStatus, ippiNormRel_Inf_32f_C3CMR, ( const Ipp32f* pSrc1, int src1Step,
                                                const Ipp32f* pSrc2, int src2Step,
                                                const Ipp8u* pMask,  int maskStep,
                                                IppiSize roiSize, int coi, Ipp64f* pNorm ))


IPPAPI( IppStatus, ippiNorm_L1_8u_C1MR, ( const Ipp8u* pSrc, int srcStep,
                                          const Ipp8u* pMask,int maskStep,
                                          IppiSize roiSize, Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNorm_L1_16u_C1MR, ( const Ipp16u* pSrc, int srcStep,
                                           const Ipp8u* pMask,int maskStep,
                                           IppiSize roiSize, Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNorm_L1_32f_C1MR, ( const Ipp32f* pSrc, int srcStep,
                                           const Ipp8u* pMask, int maskStep,
                                           IppiSize roiSize, Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNorm_L1_8u_C3CMR, ( const Ipp8u* pSrc, int srcStep,
                                           const Ipp8u* pMask,int maskStep,
                                           IppiSize roiSize, int coi, Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNorm_L1_16u_C3CMR, ( const Ipp16u* pSrc, int srcStep,
                                            const Ipp8u* pMask,int maskStep,
                                            IppiSize roiSize, int coi, Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNorm_L1_32f_C3CMR, ( const Ipp32f* pSrc, int srcStep,
                                            const Ipp8u* pMask, int maskStep,
                                            IppiSize roiSize, int coi, Ipp64f* pNorm ) )


IPPAPI( IppStatus, ippiNormDiff_L1_8u_C1MR, ( const Ipp8u* pSrc1, int src1Step,
                                              const Ipp8u* pSrc2, int src2Step,
                                              const Ipp8u* pMask, int maskStep,
                                              IppiSize roiSize,   Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNormDiff_L1_16u_C1MR, ( const Ipp16u* pSrc1, int src1Step,
                                               const Ipp16u* pSrc2, int src2Step,
                                               const Ipp8u* pMask, int maskStep,
                                               IppiSize roiSize,   Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNormDiff_L1_32f_C1MR, ( const Ipp32f* pSrc1, int src1Step,
                                               const Ipp32f* pSrc2, int src2Step,
                                               const Ipp8u* pMask,  int maskStep,
                                               IppiSize roiSize,    Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNormDiff_L1_8u_C3CMR, ( const Ipp8u* pSrc1, int src1Step,
                                               const Ipp8u* pSrc2, int src2Step,
                                               const Ipp8u* pMask, int maskStep,
                                               IppiSize roiSize, int coi, Ipp64f* pNorm ))

IPPAPI( IppStatus, ippiNormDiff_L1_16u_C3CMR, ( const Ipp16u* pSrc1, int src1Step,
                                                const Ipp16u* pSrc2, int src2Step,
                                                const Ipp8u* pMask, int maskStep,
                                                IppiSize roiSize, int coi, Ipp64f* pNorm ))

IPPAPI( IppStatus, ippiNormDiff_L1_32f_C3CMR, ( const Ipp32f* pSrc1, int src1Step,
                                                const Ipp32f* pSrc2, int src2Step,
                                                const Ipp8u* pMask,  int maskStep,
                                                IppiSize roiSize, int coi, Ipp64f* pNorm ))


IPPAPI( IppStatus, ippiNormRel_L1_8u_C1MR, ( const Ipp8u* pSrc1, int src1Step,
                                             const Ipp8u* pSrc2, int src2Step,
                                             const Ipp8u* pMask, int maskStep,
                                             IppiSize roiSize,   Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNormRel_L1_16u_C1MR, ( const Ipp16u* pSrc1, int src1Step,
                                              const Ipp16u* pSrc2, int src2Step,
                                              const Ipp8u* pMask, int maskStep,
                                              IppiSize roiSize,   Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNormRel_L1_32f_C1MR, ( const Ipp32f* pSrc1, int src1Step,
                                              const Ipp32f* pSrc2, int src2Step,
                                              const Ipp8u* pMask,  int maskStep,
                                              IppiSize roiSize,    Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNormRel_L1_8u_C3CMR, ( const Ipp8u* pSrc1, int src1Step,
                                              const Ipp8u* pSrc2, int src2Step,
                                              const Ipp8u* pMask, int maskStep,
                                              IppiSize roiSize, int coi, Ipp64f* pNorm ))

IPPAPI( IppStatus, ippiNormRel_L1_16u_C3CMR, ( const Ipp16u* pSrc1, int src1Step,
                                               const Ipp16u* pSrc2, int src2Step,
                                               const Ipp8u* pMask, int maskStep,
                                               IppiSize roiSize, int coi, Ipp64f* pNorm ))

IPPAPI( IppStatus, ippiNormRel_L1_32f_C3CMR, ( const Ipp32f* pSrc1, int src1Step,
                                               const Ipp32f* pSrc2, int src2Step,
                                               const Ipp8u* pMask,  int maskStep,
                                               IppiSize roiSize, int coi, Ipp64f* pNorm ))


IPPAPI( IppStatus, ippiNorm_L2_8u_C1MR, ( const Ipp8u* pSrc, int srcStep,
                                          const Ipp8u* pMask,int maskStep,
                                          IppiSize roiSize, Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNorm_L2_16u_C1MR, ( const Ipp16u* pSrc, int srcStep,
                                           const Ipp8u* pMask,int maskStep,
                                           IppiSize roiSize, Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNorm_L2_32f_C1MR, ( const Ipp32f* pSrc, int srcStep,
                                           const Ipp8u* pMask, int maskStep,
                                           IppiSize roiSize, Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNorm_L2_8u_C3CMR, ( const Ipp8u* pSrc, int srcStep,
                                           const Ipp8u* pMask,int maskStep,
                                           IppiSize roiSize, int coi, Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNorm_L2_16u_C3CMR, ( const Ipp16u* pSrc, int srcStep,
                                            const Ipp8u* pMask,int maskStep,
                                            IppiSize roiSize, int coi, Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNorm_L2_32f_C3CMR, ( const Ipp32f* pSrc, int srcStep,
                                            const Ipp8u* pMask, int maskStep,
                                            IppiSize roiSize, int coi, Ipp64f* pNorm ) )


IPPAPI( IppStatus, ippiNormDiff_L2_8u_C1MR, ( const Ipp8u* pSrc1, int src1Step,
                                              const Ipp8u* pSrc2, int src2Step,
                                              const Ipp8u* pMask, int maskStep,
                                              IppiSize roiSize,   Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNormDiff_L2_16u_C1MR, ( const Ipp16u* pSrc1, int src1Step,
                                               const Ipp16u* pSrc2, int src2Step,
                                               const Ipp8u* pMask, int maskStep,
                                               IppiSize roiSize,   Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNormDiff_L2_32f_C1MR, ( const Ipp32f* pSrc1, int src1Step,
                                               const Ipp32f* pSrc2, int src2Step,
                                               const Ipp8u* pMask,  int maskStep,
                                               IppiSize roiSize,    Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNormDiff_L2_8u_C3CMR, ( const Ipp8u* pSrc1, int src1Step,
                                               const Ipp8u* pSrc2, int src2Step,
                                               const Ipp8u* pMask, int maskStep,
                                               IppiSize roiSize, int coi, Ipp64f* pNorm ))

IPPAPI( IppStatus, ippiNormDiff_L2_16u_C3CMR, ( const Ipp16u* pSrc1, int src1Step,
                                                const Ipp16u* pSrc2, int src2Step,
                                                const Ipp8u* pMask, int maskStep,
                                                IppiSize roiSize, int coi, Ipp64f* pNorm ))

IPPAPI( IppStatus, ippiNormDiff_L2_32f_C3CMR, ( const Ipp32f* pSrc1, int src1Step,
                                                const Ipp32f* pSrc2, int src2Step,
                                                const Ipp8u* pMask,  int maskStep,
                                                IppiSize roiSize, int coi, Ipp64f* pNorm ))


IPPAPI( IppStatus, ippiNormRel_L2_8u_C1MR, ( const Ipp8u* pSrc1, int src1Step,
                                             const Ipp8u* pSrc2, int src2Step,
                                             const Ipp8u* pMask, int maskStep,
                                             IppiSize roiSize,   Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNormRel_L2_16u_C1MR, ( const Ipp16u* pSrc1, int src1Step,
                                              const Ipp16u* pSrc2, int src2Step,
                                              const Ipp8u* pMask, int maskStep,
                                              IppiSize roiSize,   Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNormRel_L2_32f_C1MR, ( const Ipp32f* pSrc1, int src1Step,
                                              const Ipp32f* pSrc2, int src2Step,
                                              const Ipp8u* pMask,  int maskStep,
                                              IppiSize roiSize,    Ipp64f* pNorm ) )

IPPAPI( IppStatus, ippiNormRel_L2_8u_C3CMR, ( const Ipp8u* pSrc1, int src1Step,
                                              const Ipp8u* pSrc2, int src2Step,
                                              const Ipp8u* pMask, int maskStep,
                                              IppiSize roiSize, int coi, Ipp64f* pNorm ))

IPPAPI( IppStatus, ippiNormRel_L2_16u_C3CMR, ( const Ipp16u* pSrc1, int src1Step,
                                               const Ipp16u* pSrc2, int src2Step,
                                               const Ipp8u* pMask, int maskStep,
                                               IppiSize roiSize, int coi, Ipp64f* pNorm ))

IPPAPI( IppStatus, ippiNormRel_L2_32f_C3CMR, ( const Ipp32f* pSrc1, int src1Step,
                                               const Ipp32f* pSrc2, int src2Step,
                                               const Ipp8u* pMask,  int maskStep,
                                               IppiSize roiSize, int coi, Ipp64f* pNorm ))


/****************************************************************************************\
*                                   Edge/Corner detection                                *
\****************************************************************************************/


/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name:    ippiCannyGetSize
//
//  Purpose: Calculates size of temporary buffer, required to run Canny function.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         Pointer bufferSize is NULL
//    ippStsSizeErr            roiSize has a field with zero or negative value
//
//  Parameters:
//    roiSize                  Size of image ROI in pixel
//    bufferSize               Pointer to the variable that returns the size of the temporary buffer
//F*/

IPPAPI( IppStatus, ippiCannyGetSize, ( IppiSize roiSize, int* bufferSize ))


/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name:    ippiCanny_16s8u_C1IR,     ippiCanny_32f8u_C1IR
//
//  Purpose: Creates binary image of source's image edges,
//                using derivatives of the first order.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//    ippStsBadArgErr          Bad thresholds
//
//  Parameters:
//    pSrcDx                   Pointers to the source image ( first derivatives  with respect to X )
//    srcDxStep                Step in bytes through the source image pSrcDx
//    pSrcDy                   Pointers to the source image ( first derivatives  with respect to Y )
//    srcDyStep                Step in bytes through the source image pSrcDy
//
//    roiSize                  Size of the source images ROI in pixels
//    lowThresh                Low threshold for edges detection
//    highThresh               Upper threshold for edges detection
//    pBuffer                  Pointer to the pre-allocated temporary buffer, which size can be
//                             calculated using ippiCannyGetSize function
//F*/

IPPAPI(IppStatus, ippiCanny_16s8u_C1R, ( Ipp16s* pSrcDx, int srcDxStep,
                                         Ipp16s* pSrcDy, int srcDyStep,
                                         Ipp8u*  pDstEdges, int dstEdgeStep,
                                         IppiSize roiSize,
                                         Ipp32f  lowThresh,
                                         Ipp32f  highThresh,
                                         Ipp8u*  pBuffer ))

IPPAPI(IppStatus, ippiCanny_32f8u_C1R, ( Ipp32f* pSrcDx, int srcDxStep,
                                         Ipp32f* pSrcDy, int srcDyStep,
                                         Ipp8u*  pDstEdges, int dstEdgeStep,
                                         IppiSize roiSize,
                                         Ipp32f  lowThresh,
                                         Ipp32f  highThresh,
                                         Ipp8u*  pBuffer ))


/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name:    ippiEigenValsVecsGetBufferSize_8u32f_C1R, ippiEigenValsVecsGetBufferSize_32f_C1R
//
//  Purpose: Calculates size of temporary buffer, required to run one of EigenValsVecs***
//           functions.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width is less or equal zero or bad window size
//
//  Parameters:
//    roiSize                  roiSize size in pixels
//    apertureSize             Linear size of derivative filter aperture
//    avgWindow                Linear size of averaging window
//    bufferSize               Output parameter. Calculated buffer size.
//F*/

IPPAPI(IppStatus, ippiEigenValsVecsGetBufferSize_8u32f_C1R, ( IppiSize roiSize,int apertureSize,
                                              int avgWindow, int* bufferSize ))
IPPAPI(IppStatus, ippiEigenValsVecsGetBufferSize_32f_C1R, ( IppiSize roiSize,int apertureSize,
                                              int avgWindow, int* bufferSize ))


/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name:    ippiEigenValsVecs_8u32f_C1R, ippiEigenValsVecs_32f_C1R
//
//  Purpose: Calculate both eigen values and eigen vectors of 2x2 autocorrelation
//           gradient matrix for every pixel. Can be used for sophisticated
//           edge and corner detection
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//                             or bad window size
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//
//  Parameters:
//    pSrc                     Source image
//    srcStep                  Its step in bytes
//    pEigenVV                 Image, which is 6 times wider that source image,
//                             filled with 6-tuples:
//                             (eig_val1, eig_val2, eig_vec1_x, eig_vec1_y,
//                             eig_vec2_x, eig_vec2_y)
//    eigStep                  Output image step in bytes
//    roiSize                  ROI size in pixels
//    kernType                 Kernel type (Scharr 3x3 or Sobel 3x3, 5x5)
//    apertureSize             Linear size of derivative filter aperture
//    avgWindow                Linear size of averaging window
//    pBuffer                  Preallocated temporary buffer, which size can be calculated
//                             using ippiEigenValsVecsGetSize function
//F*/

IPPAPI(IppStatus, ippiEigenValsVecs_8u32f_C1R, ( const Ipp8u* pSrc, int srcStep,
                                                 Ipp32f* pEigenVV, int eigStep,
                                                 IppiSize roiSize, IppiKernelType kernType,
                                                 int apertureSize, int avgWindow, Ipp8u* pBuffer ))

IPPAPI(IppStatus, ippiEigenValsVecs_32f_C1R, ( const Ipp32f* pSrc, int srcStep,
                                               Ipp32f* pEigenVV, int eigStep,
                                               IppiSize roiSize, IppiKernelType kernType,
                                               int apertureSize, int avgWindow, Ipp8u* pBuffer ))

/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name:    ippiEigenValsVecsBorder_8u32f_C1R, ippiEigenValsVecsBorder_32f_C1R
//
//  Purpose: Calculate both eigen values and eigen vectors of 2x2 autocorrelation
//           gradient matrix for every pixel. Can be used for sophisticated
//           edge and corner detection
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//                             or bad window size
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//
//  Parameters:
//    pSrc                     Source image
//    srcStep                  Its step in bytes
//    pEigenVV                 Image, which is 6 times wider that source image,
//                             filled with 6-tuples:
//                             (eig_val1, eig_val2, eig_vec1_x, eig_vec1_y,
//                             eig_vec2_x, eig_vec2_y)
//    eigStep                  Output image step in bytes
//    roiSize                  ROI size in pixels
//    kernType                 Kernel type (Scharr 3x3 or Sobel 3x3, 5x5)
//    apertureSize             Linear size of derivative filter aperture
//    avgWindow                Linear size of averaging window
//    border                   Type of the border
//    borderValue              Constant value to assign to pixels of the constant border.
//                             if border type equals ippBorderConstant
//    pBuffer                  Preallocated temporary buffer, which size can be calculated
//                             using ippiEigenValsVecsGetSize function
//F*/

IPPAPI(IppStatus, ippiEigenValsVecsBorder_8u32f_C1R, ( const Ipp8u* pSrc, int srcStep, Ipp32f* pEigenVV, int eigStep,
                                               IppiSize roiSize, IppiKernelType kernType, int apertureSize, int avgWindow,
                                               IppiBorderType borderType, Ipp8u borderValue, Ipp8u* pBuffer ))

IPPAPI(IppStatus, ippiEigenValsVecsBorder_32f_C1R, ( const Ipp32f* pSrc, int srcStep, Ipp32f* pEigenVV, int eigStep,
                                               IppiSize roiSize, IppiKernelType kernType, int apertureSize, int avgWindow,
                                               IppiBorderType borderType, Ipp32f borderValue, Ipp8u* pBuffer ))

/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name:    ippiMinEigenValGetBufferSize_8u32f_C1R, ippiMinEigenValGetBufferSize_32f_C1R
//
//  Purpose: Calculates size of temporary buffer, required to run one of MinEigenVal***
//           functions.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width is less or equal zero or bad window size
//
//  Parameters:
//    roiSize                  roiSize size in pixels
//    apertureSize             Linear size of derivative filter aperture
//    avgWindow                Linear size of averaging window
//    bufferSize               Output parameter. Calculated buffer size.
//F*/

IPPAPI(IppStatus, ippiMinEigenValGetBufferSize_8u32f_C1R, ( IppiSize roiSize, int apertureSize,
                                            int avgWindow, int* bufferSize ))

IPPAPI(IppStatus, ippiMinEigenValGetBufferSize_32f_C1R, ( IppiSize roiSize, int apertureSize,
                                            int avgWindow, int* bufferSize ))


/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name:    ippiMinEigenVal_8u32f_C1R, ippiMinEigenVal_32f_C1R
//
//  Purpose: Calculate minimal eigen value of 2x2 autocorrelation gradient matrix
//           for every pixel. Pixels with relatively large minimal eigen values
//           are strong corners on the picture.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//                             or bad window size
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//
//  Parameters:
//    pSrc                     Source image
//    srcStep                  Its step in bytes
//    pMinEigenVal             Image, filled with minimal eigen values for every pixel
//    minValStep               Its step in bytes
//    roiSize                  ROI size in pixels
//    kernType                 Kernel type (Scharr 3x3 or Sobel 3x3, 5x5)
//    apertureSize             Linear size of derivative filter aperture
//    avgWindow                Linear size of averaging window
//    pBuffer                  Preallocated temporary buffer, which size can be calculated
//                             using ippiMinEigenValGetSize function
//F*/

IPPAPI(IppStatus, ippiMinEigenVal_8u32f_C1R, ( const Ipp8u* pSrc, int srcStep,
                                               Ipp32f* pMinEigenVal, int minValStep,
                                               IppiSize roiSize, IppiKernelType kernType,
                                               int apertureSize, int avgWindow, Ipp8u* pBuffer ))

IPPAPI(IppStatus, ippiMinEigenVal_32f_C1R, ( const Ipp32f* pSrc, int srcStep,
                                             Ipp32f* pMinEigenVal, int minValStep,
                                             IppiSize roiSize, IppiKernelType kernType,
                                             int apertureSize, int avgWindow, Ipp8u* pBuffer ))

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    ippiMinEigenValBorder_8u32f_C1R
//             ippiMinEigenValBorder_32f_C1R
//
//  Purpose: Calculate minimal eigen value of 2x2 autocorrelation gradient matrix
//           for every pixel. Pixels with relatively large minimal eigen values
//           are strong corners on the picture.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//                             or bad window size
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//
//  Parameters:
//    pSrc                     Source image
//    srcStep                  Its step in bytes
//    pMinEigenVal             Image, filled with minimal eigen values for every pixel
//    minValStep               Its step in bytes
//    roiSize                  ROI size in pixels
//    kernType                 Kernel type (Scharr 3x3 or Sobel 3x3, 5x5)
//    apertureSize             Linear size of derivative filter aperture
//    avgWindow                Linear size of averaging window
//    border                   Type of the border
//    borderValue              Constant value to assign to pixels of the constant border. if border type equals ippBorderConstant
//    pBuffer                  Preallocated temporary buffer, which size can be calculated
//                             using ippiMinEigenValGetSize function
//F*/

IPPAPI(IppStatus, ippiMinEigenValBorder_8u32f_C1R, (const Ipp8u* pSrc, int srcStep, Ipp32f* pEigenVV, int eigStep,
                                              IppiSize roiSize, IppiKernelType kernType, int apertureSize, int avgWndSize,
                                              IppiBorderType borderType, Ipp8u borderValue, Ipp8u*  pBuffer))

IPPAPI(IppStatus, ippiMinEigenValBorder_32f_C1R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pEigenVV, int eigStep,
                                            IppiSize roiSize, IppiKernelType kernType, int apertureSize, int avgWndSize,
                                            IppiBorderType borderType, Ipp32f borderValue, Ipp8u*  pBuffer))


/****************************************************************************************\
*                                   Distance Transform                                   *
\****************************************************************************************/

/* ///////////////////////////////////////////////////////////////////////////////////////////////////
//  Name:  ippiTrueDistanceTransformGetBufferSize_8u32f_C1R
//
//  Purpose:    Get size of external buffer.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            Indicates an error condition if roiSize has a field with zero
//                             or negative value.
//
//  Parameters:
//    roiSize                  The image ROI size
//    pBufferSize              The pointer to the buffer size
*/

IPPAPI(IppStatus, ippiTrueDistanceTransformGetBufferSize_8u32f_C1R, (IppiSize roiSize, int* pBufferSize))

/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name:    ippiDistanceTransform_3x3_8u32f_C1R, ippiDistanceTransform_5x5_8u32f_C1R,
//           ippiDistanceTransform_3x3_8u16u_C1R, ippiDistanceTransform_5x5_8u16u_C1R,
//           ippiDistanceTransform_3x3_8u_C1R,    ippiDistanceTransform_5x5_8u_C1R,
//           ippiDistanceTransform_3x3_8u_C1IR,   ippiDistanceTransform_5x5_8u_C1IR,
//           ippiTrueDistanceTransform_8u32f_C1R
//
//  Purpose: For every non-zero pixel in the source image, the functions calculate
//           distance between that pixel and nearest zero pixel.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//    ippStsCoeffErr           Zero mask coefficient
//
//  Parameters:
//    pSrc                     Source image
//    pSrcDst                  Pointer to the input and output image
//    srcStep                  Its step
//    pDst                     Output image with distances
//    dstStep                  Its step
//    roiSize                  ROI size
//    pMetrics                 Array that determines metrics used.
//    scaleFactor              Scale factor
//    pBuffer                  The pointer to the working buffer
//
//F*/

IPPAPI(IppStatus, ippiDistanceTransform_3x3_8u32f_C1R, ( const Ipp8u* pSrc, int srcStep,
                                                         Ipp32f* pDst, int dstStep,
                                                         IppiSize roiSize, Ipp32f* pMetrics ))

IPPAPI(IppStatus, ippiDistanceTransform_5x5_8u32f_C1R, ( const Ipp8u* pSrc, int srcStep,
                                                         Ipp32f* pDst, int dstStep,
                                                         IppiSize roiSize, Ipp32f* pMetrics ))

IPPAPI(IppStatus, ippiDistanceTransform_3x3_8u16u_C1R, ( const Ipp8u* pSrc, int srcStep,
                                                         Ipp16u* pDst, int dstStep,
                                                         IppiSize roiSize, Ipp32s* pMetrics ))

IPPAPI(IppStatus, ippiDistanceTransform_5x5_8u16u_C1R, ( const Ipp8u* pSrc, int srcStep,
                                                         Ipp16u* pDst, int dstStep,
                                                         IppiSize roiSize, Ipp32s* pMetrics ))

IPPAPI(IppStatus, ippiDistanceTransform_3x3_8u_C1R, ( const Ipp8u* pSrc, int srcStep,
                                                      Ipp8u* pDst, int dstStep,
                                                      IppiSize roiSize, Ipp32s* pMetrics ))

IPPAPI(IppStatus, ippiDistanceTransform_5x5_8u_C1R, ( const Ipp8u* pSrc, int srcStep,
                                                      Ipp8u* pDst, int dstStep,
                                                      IppiSize roiSize, Ipp32s* pMetrics ))


IPPAPI(IppStatus, ippiDistanceTransform_3x3_8u_C1IR, ( Ipp8u* pSrcDst, int srcDstStep,
                                                       IppiSize roiSize, Ipp32s* pMetrics ))

IPPAPI(IppStatus, ippiDistanceTransform_5x5_8u_C1IR, ( Ipp8u* pSrcDst, int srcDstStep,
                                                       IppiSize roiSize, Ipp32s* pMetrics ))

IPPAPI(IppStatus, ippiTrueDistanceTransform_8u32f_C1R, ( const Ipp8u* pSrc, int srcStep,
                                                         Ipp32f* pDst, int dstStep,
                                                         IppiSize roiSize, Ipp8u* pBuffer ))

/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name:    ippiGetDistanceTransformMask_32f,    ippiGetDistanceTransformMask_32s
//           ippiGetDistanceTransformMask (deprecated name of ippiGetDistanceTransformMask_32f)
//
//  Purpose: Calculates optimal mask for given type of metrics and given mask size
//
//  Return:
//    ippStsOk                 Succeed
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsBadArgErr          Bad kernel size or norm or maskType
//
//  Parameters:
//    kerSize                  Kernel size (3,5)
//    norm                     Norm type (L1,L2,Inf)
//    maskType                 Type of distance:
//                                30 - 3x3 aperture for infinify norm,
//                                31 - 3x3 aperture for L1 norm,
//                                32 - 3x3 aperture for L2 norm,
//                                50 - 5x5 aperture for infinify norm,
//                                51 - 5x5 aperture for L1 norm,
//                                52 - 5x5 aperture for L2 norm
//    pMetrics                 Pointer to resultant metrics
//F*/

IPPAPI( IppStatus, ippiGetDistanceTransformMask_32f, ( int kerSize, IppiNorm norm, Ipp32f* pMetrics ))

IPPAPI( IppStatus, ippiGetDistanceTransformMask_32s, ( int kerSize, IppiNorm norm, Ipp32s* pMetrics ))

IPPAPI( IppStatus, ippiGetDistanceTransformMask,     ( int maskType, Ipp32f* pMetrics ))


/* ///////////////////////////////////////////////////////////////////////////////////////////////////
//  Name:  ippiFastMarchingGetBufferSize_8u32f_C1R
//
//  Purpose:    Get size of external buffer.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width of the image or kernel size are less or equal zero
//
//  Parameters:
//    roiSize                  The image ROI size
//    pBufferSize              The pointer to the buffer size
*/

IPPAPI(IppStatus, ippiFastMarchingGetBufferSize_8u32f_C1R, (IppiSize roiSize, int* pBufferSize))


/* ///////////////////////////////////////////////////////////////////////////////////////////////////
//  Name:  ippiFastMarching_8u32f_C1R
//
//  Purpose:    Calculate distance transform by fast marching method
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width of the image or kernel size are less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//
//  Parameters:
//    pSrc                     Source image
//    srcStep                  Its step
//    pDst                     Output image with distances
//    dstStep                  Its step
//    roiSize                  The image ROI size
//    radius                   The radius of external neighborhood
//    pBuffer                  Pointer to working buffer
//
//  Note: dst = min((src1+src1+sqrt(2-(src1-src2)**2))/2,min(src1,src2)+1)
//        for four neighbour pairs
*/

IPPAPI(IppStatus, ippiFastMarching_8u32f_C1R, (const Ipp8u* pSrc, int srcStep, Ipp32f* pDst, int dstStep,
                                      IppiSize roiSize, Ipp32f radius, Ipp8u* pBuffer))


/****************************************************************************************\
*                                      Flood Fill                                        *
\****************************************************************************************/

/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name:    ippiFloodFillGetSize_4Con, ippiFloodFillGetSize_8Con
//           ippiFloodFillGetSize_Grad4Con, ippiFloodFillGetSize_Grad8Con
//
//  Purpose: The functions calculate size of temporary buffer, required to run
//           one of the corresponding flood fill functions.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//
//  Parameters:
//    roiSize                  ROI size
//    pBufSize                 Temporary buffer size
//F*/

IPPAPI( IppStatus, ippiFloodFillGetSize, ( IppiSize roiSize, int* pBufSize ))

IPPAPI( IppStatus, ippiFloodFillGetSize_Grad, ( IppiSize roiSize, int* pBufSize ))


/*F///////////////////////////////////////////////////////////////////////////////////////
//  Names:   ippiFloodFill_4Con_8u_C1IR
//           ippiFloodFill_8Con_8u_C1IR
//           ippiFloodFill_4Con_16u_C1IR
//           ippiFloodFill_8Con_16u_C1IR
//           ippiFloodFill_4Con_32f_C1IR
//           ippiFloodFill_8Con_32f_C1IR
//           ippiFloodFill_4Con_32s_C1IR
//           ippiFloodFill_8Con_32s_C1IR
//           ippiFloodFill_4Con_8u_C3IR
//           ippiFloodFill_8Con_8u_C3IR
//           ippiFloodFill_4Con_16u_C3IR
//           ippiFloodFill_8Con_16u_C3IR
//           ippiFloodFill_4Con_32f_C3IR
//           ippiFloodFill_8Con_32f_C3IR
//           ippiFloodFill_Grad4Con_8u_C1IR
//           ippiFloodFill_Grad8Con_8u_C1IR
//           ippiFloodFill_Grad4Con_16u_C1IR
//           ippiFloodFill_Grad8Con_16u_C1IR
//           ippiFloodFill_Grad4Con_32f_C1IR
//           ippiFloodFill_Grad8Con_32f_C1IR
//           ippiFloodFill_Grad4Con_8u_C3IR
//           ippiFloodFill_Grad8Con_8u_C3IR
//           ippiFloodFill_Grad4Con_16u_C3IR
//           ippiFloodFill_Grad8Con_16u_C3IR
//           ippiFloodFill_Grad4Con_32f_C3IR
//           ippiFloodFill_Grad8Con_32f_C3IR
//           ippiFloodFill_Range4Con_8u_C1IR
//           ippiFloodFill_Range8Con_8u_C1IR
//           ippiFloodFill_Range4Con_16u_C1IR
//           ippiFloodFill_Range8Con_16u_C1IR
//           ippiFloodFill_Range4Con_32f_C1IR
//           ippiFloodFill_Range8Con_32f_C1IR
//           ippiFloodFill_Range4Con_8u_C3IR
//           ippiFloodFill_Range8Con_8u_C3IR
//           ippiFloodFill_Range4Con_16u_C3IR
//           ippiFloodFill_Range8Con_16u_C3IR
//           ippiFloodFill_Range4Con_32f_C3IR
//           ippiFloodFill_Range8Con_32f_C3IR
//
//  Purpose: The functions fill the seed pixel enewValirons inside which all pixel
//           values are equal to (first 4 funcs) or not far from each other (the others).
//
//  Return:
//    ippStsNoErr              Ok.
//    ippStsNullPtrErr         One of pointers is NULL.
//    ippStsSizeErr            The width or height of images is less or equal zero.
//    ippStsStepErr            The steps in images are too small.
//    ippStsNotEvenStepErr     Step is not multiple of element.
//    ippStsOutOfRangeErr      Indicates an error condition if the seed point is out of ROI.
//
//  Parameters:
//    pImage                   Pointer to ROI of initial image (in the beginning)
//                             which is "repainted" during the function action,
//    imageStep                Full string length of initial image (in bytes),
//    roi                      Size of image ROI,
//    seed                     Coordinates of the seed point inside image ROI,
//    newVal                   Value to fill with for one-channel data,
//    pNewVal                  Pointer to the vector containing values to fill with
//                             for three-channel data,
//    minDelta                 Minimum difference between neighbor pixels for one-channel data,
//    maxDelta                 Maximum difference between neighbor pixels for one-channel data,
//    pMinDelta                Pointer to the minimum differences between neighbor pixels for
//                             three-channel images,
//    pMaxDelta                Pointer to the maximum differences between neighbor pixels for
//                             three-channel images,
//    pRegion                  Pointer to repainted region properties structure,
//    pBuffer                  Buffer needed for calculations (its size must be
//                             calculated by ippiFloodFillGetSize_Grad function).
//
//  Notes:   This function uses a rapid non-recursive algorithm.
//F*/

IPPAPI( IppStatus, ippiFloodFill_4Con_8u_C1IR, ( Ipp8u*  pImage, int imageStep,
                                                 IppiSize roiSize, IppiPoint seed,
                                                 Ipp8u newVal, IppiConnectedComp* pRegion,
                                                 Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_8Con_8u_C1IR, ( Ipp8u*  pImage, int imageStep,
                                                 IppiSize roiSize, IppiPoint seed,
                                                 Ipp8u newVal, IppiConnectedComp* pRegion,
                                                 Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_4Con_16u_C1IR, ( Ipp16u*  pImage, int imageStep,
                                                 IppiSize roiSize, IppiPoint seed,
                                                 Ipp16u newVal, IppiConnectedComp* pRegion,
                                                 Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_8Con_16u_C1IR, ( Ipp16u*  pImage, int imageStep,
                                                 IppiSize roiSize, IppiPoint seed,
                                                 Ipp16u newVal, IppiConnectedComp* pRegion,
                                                 Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_4Con_32f_C1IR, ( Ipp32f* pImage, int imageStep,
                                                  IppiSize roiSize, IppiPoint seed,
                                                  Ipp32f newVal, IppiConnectedComp* pRegion,
                                                  Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_8Con_32f_C1IR, ( Ipp32f* pImage, int imageStep,
                                                  IppiSize roiSize, IppiPoint seed,
                                                  Ipp32f newVal, IppiConnectedComp* pRegion,
                                                  Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_4Con_32s_C1IR, ( Ipp32s* pImage, int imageStep,
                                                  IppiSize roiSize, IppiPoint seed,
                                                  Ipp32s newVal, IppiConnectedComp* pRegion,
                                                  Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_8Con_32s_C1IR, ( Ipp32s* pImage, int imageStep,
                                                  IppiSize roiSize, IppiPoint seed,
                                                  Ipp32s newVal, IppiConnectedComp* pRegion,
                                                  Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_Grad4Con_8u_C1IR, ( Ipp8u*  pImage, int imageStep,
                                                     IppiSize roiSize, IppiPoint seed,
                                                     Ipp8u newVal, Ipp8u minDelta, Ipp8u maxDelta,
                                                     IppiConnectedComp* pRegion, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_Grad8Con_8u_C1IR, ( Ipp8u*  pImage, int imageStep,
                                                     IppiSize roiSize, IppiPoint seed,
                                                     Ipp8u newVal, Ipp8u minDelta, Ipp8u maxDelta,
                                                     IppiConnectedComp* pRegion, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_Grad4Con_16u_C1IR, ( Ipp16u*  pImage, int imageStep,
                                                     IppiSize roiSize, IppiPoint seed,
                                                     Ipp16u newVal, Ipp16u minDelta, Ipp16u maxDelta,
                                                     IppiConnectedComp* pRegion, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_Grad8Con_16u_C1IR, ( Ipp16u*  pImage, int imageStep,
                                                     IppiSize roiSize, IppiPoint seed,
                                                     Ipp16u newVal, Ipp16u minDelta, Ipp16u maxDelta,
                                                     IppiConnectedComp* pRegion, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_Grad4Con_32f_C1IR, ( Ipp32f* pImage, int imageStep,
                                                      IppiSize roiSize, IppiPoint seed,
                                                      Ipp32f newVal, Ipp32f minDelta, Ipp32f maxDelta,
                                                      IppiConnectedComp* pRegion, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_Grad8Con_32f_C1IR, ( Ipp32f* pImage, int imageStep,
                                                      IppiSize roiSize, IppiPoint seed,
                                                      Ipp32f newVal, Ipp32f minDelta, Ipp32f maxDelta,
                                                      IppiConnectedComp* pRegion, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_Range4Con_8u_C1IR, ( Ipp8u*  pImage, int imageStep,
                                                     IppiSize roiSize, IppiPoint seed,
                                                     Ipp8u newVal, Ipp8u minDelta, Ipp8u maxDelta,
                                                     IppiConnectedComp* pRegion, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_Range8Con_8u_C1IR, ( Ipp8u*  pImage, int imageStep,
                                                     IppiSize roiSize, IppiPoint seed,
                                                     Ipp8u newVal, Ipp8u minDelta, Ipp8u maxDelta,
                                                     IppiConnectedComp* pRegion, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_Range4Con_16u_C1IR, ( Ipp16u*  pImage, int imageStep,
                                                     IppiSize roiSize, IppiPoint seed,
                                                     Ipp16u newVal, Ipp16u minDelta, Ipp16u maxDelta,
                                                     IppiConnectedComp* pRegion, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_Range8Con_16u_C1IR, ( Ipp16u*  pImage, int imageStep,
                                                     IppiSize roiSize, IppiPoint seed,
                                                     Ipp16u newVal, Ipp16u minDelta, Ipp16u maxDelta,
                                                     IppiConnectedComp* pRegion, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_Range4Con_32f_C1IR, ( Ipp32f* pImage, int imageStep,
                                                      IppiSize roiSize, IppiPoint seed,
                                                      Ipp32f newVal, Ipp32f minDelta, Ipp32f maxDelta,
                                                      IppiConnectedComp* pRegion, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_Range8Con_32f_C1IR, ( Ipp32f* pImage, int imageStep,
                                                      IppiSize roiSize, IppiPoint seed,
                                                      Ipp32f newVal, Ipp32f minDelta, Ipp32f maxDelta,
                                                      IppiConnectedComp* pRegion, Ipp8u* pBuffer ))


IPPAPI( IppStatus, ippiFloodFill_4Con_8u_C3IR, ( Ipp8u*  pImage, int imageStep,
                                                 IppiSize roiSize, IppiPoint seed,
                                                 Ipp8u *pNewVal, IppiConnectedComp* pRegion,
                                                 Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_8Con_8u_C3IR, ( Ipp8u*  pImage, int imageStep,
                                                 IppiSize roiSize, IppiPoint seed,
                                                 Ipp8u *pNewVal, IppiConnectedComp* pRegion,
                                                 Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_4Con_16u_C3IR, ( Ipp16u*  pImage, int imageStep,
                                                 IppiSize roiSize, IppiPoint seed,
                                                 Ipp16u *pNewVal, IppiConnectedComp* pRegion,
                                                 Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_8Con_16u_C3IR, ( Ipp16u*  pImage, int imageStep,
                                                 IppiSize roiSize, IppiPoint seed,
                                                 Ipp16u *pNewVal, IppiConnectedComp* pRegion,
                                                 Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_4Con_32f_C3IR, ( Ipp32f* pImage, int imageStep,
                                                  IppiSize roiSize, IppiPoint seed,
                                                  Ipp32f *pNewVal, IppiConnectedComp* pRegion,
                                                  Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_8Con_32f_C3IR, ( Ipp32f* pImage, int imageStep,
                                                  IppiSize roiSize, IppiPoint seed,
                                                  Ipp32f *pNewVal, IppiConnectedComp* pRegion,
                                                  Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_Grad4Con_8u_C3IR, ( Ipp8u*  pImage, int imageStep,
                                                     IppiSize roiSize, IppiPoint seed,
                                                     Ipp8u *pNewVal, Ipp8u *pMinDelta, Ipp8u *pMaxDelta,
                                                     IppiConnectedComp* pRegion, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_Grad8Con_8u_C3IR, ( Ipp8u*  pImage, int imageStep,
                                                     IppiSize roiSize, IppiPoint seed,
                                                     Ipp8u *pNewVal, Ipp8u *pMinDelta, Ipp8u *pMaxDelta,
                                                     IppiConnectedComp* pRegion, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_Grad4Con_16u_C3IR, ( Ipp16u*  pImage, int imageStep,
                                                     IppiSize roiSize, IppiPoint seed,
                                                     Ipp16u *pNewVal, Ipp16u *pMinDelta, Ipp16u *pMaxDelta,
                                                     IppiConnectedComp* pRegion, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_Grad8Con_16u_C3IR, ( Ipp16u*  pImage, int imageStep,
                                                     IppiSize roiSize, IppiPoint seed,
                                                     Ipp16u *pNewVal, Ipp16u *pMinDelta, Ipp16u *pMaxDelta,
                                                     IppiConnectedComp* pRegion, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_Grad4Con_32f_C3IR, ( Ipp32f* pImage, int imageStep,
                                                      IppiSize roiSize, IppiPoint seed,
                                                      Ipp32f *pNewVal, Ipp32f *pMinDelta, Ipp32f *pMaxDelta,
                                                      IppiConnectedComp* pRegion, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_Grad8Con_32f_C3IR, ( Ipp32f* pImage, int imageStep,
                                                      IppiSize roiSize, IppiPoint seed,
                                                      Ipp32f *pNewVal, Ipp32f *pMinDelta, Ipp32f *pMaxDelta,
                                                      IppiConnectedComp* pRegion, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_Range4Con_8u_C3IR, ( Ipp8u*  pImage, int imageStep,
                                                     IppiSize roiSize, IppiPoint seed,
                                                     Ipp8u *pNewVal, Ipp8u *pMinDelta, Ipp8u *pMaxDelta,
                                                     IppiConnectedComp* pRegion, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_Range8Con_8u_C3IR, ( Ipp8u*  pImage, int imageStep,
                                                     IppiSize roiSize, IppiPoint seed,
                                                     Ipp8u *pNewVal, Ipp8u *pMinDelta, Ipp8u *pMaxDelta,
                                                     IppiConnectedComp* pRegion, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_Range4Con_16u_C3IR, ( Ipp16u*  pImage, int imageStep,
                                                     IppiSize roiSize, IppiPoint seed,
                                                     Ipp16u *pNewVal, Ipp16u *pMinDelta, Ipp16u *pMaxDelta,
                                                     IppiConnectedComp* pRegion, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_Range8Con_16u_C3IR, ( Ipp16u*  pImage, int imageStep,
                                                     IppiSize roiSize, IppiPoint seed,
                                                     Ipp16u *pNewVal, Ipp16u *pMinDelta, Ipp16u *pMaxDelta,
                                                     IppiConnectedComp* pRegion, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_Range4Con_32f_C3IR, ( Ipp32f* pImage, int imageStep,
                                                      IppiSize roiSize, IppiPoint seed,
                                                      Ipp32f *pNewVal, Ipp32f *pMinDelta, Ipp32f *pMaxDelta,
                                                      IppiConnectedComp* pRegion, Ipp8u* pBuffer ))

IPPAPI( IppStatus, ippiFloodFill_Range8Con_32f_C3IR, ( Ipp32f* pImage, int imageStep,
                                                      IppiSize roiSize, IppiPoint seed,
                                                      Ipp32f *pNewVal, Ipp32f *pMinDelta, Ipp32f *pMaxDelta,
                                                      IppiConnectedComp* pRegion, Ipp8u* pBuffer ))

/****************************************************************************************\
*                                      Motion Templates                                  *
\****************************************************************************************/

/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:      ippiUpdateMotionHistory_8u32f_C1IR,  ippiUpdateMotionHistory_16u32f_C1IR
//             ippiUpdateMotionHistory_32f_C1IR
//
//  Purpose:   Sets motion history image (MHI) pixels to the current time stamp
//             when the corrensonding pixels in the silhoette image are non zero.
//             Else (silhouette pixels are zero) MHI pixels are
//             cleared if their values are too small (less than timestamp - mhiDuration),
//             i.e. they were updated far ago last time. Else MHI pixels remain unchanged.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//    ippStsOutOfRangeErr      Maximal duration is negative
//
//  Arguments:
//    pSilhouette              The pointer to silhouette image
//    silhStep                 The step in silhouette image
//    pMHI                     The pointer to motion history image
//    mhiStep                  The step in mhi image
//    roiSize                  ROI size
//    timestamp                Current time stamp (milliseconds)
//    mhiDuration              Maximal duration of motion track (milliseconds)
*/

IPPAPI(IppStatus, ippiUpdateMotionHistory_8u32f_C1IR,
                        ( const Ipp8u* pSilhouette, int silhStep,
                          Ipp32f* pMHI, int mhiStep, IppiSize roiSize,
                          Ipp32f timestamp, Ipp32f mhiDuration ))

IPPAPI(IppStatus, ippiUpdateMotionHistory_16u32f_C1IR,
                        ( const Ipp16u* pSilhouette, int silhStep,
                          Ipp32f* pMHI, int mhiStep, IppiSize roiSize,
                          Ipp32f timestamp, Ipp32f mhiDuration ))

IPPAPI(IppStatus, ippiUpdateMotionHistory_32f_C1IR,
                        ( const Ipp32f* pSilhouette, int silhStep,
                          Ipp32f* pMHI, int mhiStep, IppiSize roiSize,
                          Ipp32f timestamp, Ipp32f mhiDuration ))


/****************************************************************************************\
*                                        Optical Flow                                    *
\****************************************************************************************/

/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiOpticalFlowPyrLKGetSize
//
//  Purpose:    Computes the size of the pyramidal optical flow structure
//
//  Return:
//    ippStsNoErr              Indicates no error. Any other value indicates an error or a warning.
//    ippStsNullPtrErr         Indicates an error Indicates an error if pStateSize is NULL.
//    ippStsDataTypeErr        Indicates an error when dataType has an illegal value.
//    ippStsSizeErr            Indicates an error condition if roiSize has a field with zero
//                               or negative value or if winSize is equal to or less than 0.
//
//  Arguments:
//    winSize                  Size of search window (2*winSize+1)
//    roi                      Maximal image ROI
//    dataType                 The type of data
//    hint                     Option to select the algorithmic implementation of the function
//    pStateSize               Pointer to the size value of state structure.
*/
IPPAPI(IppStatus, ippiOpticalFlowPyrLKGetSize, ( int winSize, IppiSize roi, IppDataType dataType,
                                                 IppHintAlgorithm hint, int* pStateSize))

/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiOpticalFlowPyrLKInit_8u_C1R, ippiOpticalFlowPyrLKInit_16u_C1R,
//              ippiOpticalFlowPyrLKInit_32f_C1R
//
//  Purpose:    Initializes a structure for pyramidal L-K algorithm
//
//  Return:
//    ippStsNoErr              Indicates no error. Any other value indicates an error or a warning.
//    ippStsNullPtrErr         Indicates an error if ppState or pStateBuf are NULL.
//    ippStsSizeErr            Indicates an error condition if roiSize has a field with zero
//                               or negative value or if winSize is equal to or less than 0.
//    ippStsMemAllocErr        Memory allocation error
//
//  Arguments:
//    ppState                  Pointer to the pointer to the optical flow structure being initialized
//    roiSize                  Size of the source image (zero level of the pyramid) ROI in pixels.
//    winSize                  Size of search window (2*winSize+1) of each pyramid level.
//    hint                     Option to select the algorithmic implementation of the function
//    pStateBuf                Pointer to the work buffer for State structure.
*/


IPPAPI(IppStatus, ippiOpticalFlowPyrLKInit_8u_C1R, (IppiOptFlowPyrLK_8u_C1R** ppState,
                         IppiSize roi, int winSize, IppHintAlgorithm hint, Ipp8u* pStateBuf))

IPPAPI(IppStatus, ippiOpticalFlowPyrLKInit_16u_C1R, (IppiOptFlowPyrLK_16u_C1R** ppState,
                         IppiSize roi, int winSize, IppHintAlgorithm hint, Ipp8u* pStateBuf))


IPPAPI(IppStatus, ippiOpticalFlowPyrLKInit_32f_C1R, (IppiOptFlowPyrLK_32f_C1R** ppState,
                         IppiSize roi, int winSize, IppHintAlgorithm hint, Ipp8u* pStateBuf))


/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name: ippiOpticalFlowPyrLK_8u_C1R, ippiOpticalFlowPyrLK_16u_C1R,
//        ippiOpticalFlowPyrLK_32f_C1R
//
//  Purpose:
//    Pyramidal version of Lucas - Kanade method of optical flow calculation
//
//  Returns:
//    ippStsNoErr              Indicates no error. Any other value indicates an error or a warning
//    ippStsNullPtrErr         Indicates an error if one of the specified pointer is NULL
//    ippStsSizeErr            Indicates an error condition if numFeat or winSize has zero or
//                               negative value.
//    ippStsBadArgErr          Indicates an error condition if maxLev or threshold has negative
//                               value, or maxIter has zero or negative value.
//
//  Arguments:
//    pPyr1                    Pointer to the first image pyramid (time t)
//    pPyr2                    Pointer to the second image pyramid (time t+dt)
//    pPrev                    Array of points, for which the flow needs to be found
//    pNext                    Array of new positions of pPrev points
//    pError                   Array of differences between pPrev and pNext points
//    pStatus                  Array of result indicator (0 - not calculated)
//    numFeat                  Number of points to calculate optical flow
//    winSize                  Size of search window (2*winSize+1)
//    maxLev                   Pyramid level to start the operation
//    maxIter                  Maximum number of algorithm iterations for each pyramid level
//    threshold                Threshold value to stop new position search
//    pState                   Pointer to the pyramidal optical flow structure
//
//    Notes:  For calculating spatial derivatives 3x3 Scharr operator is used.
//            The values of pixels beyond the image are determined using replication mode.
//F*/

IPPAPI(IppStatus, ippiOpticalFlowPyrLK_8u_C1R, (IppiPyramid *pPyr1, IppiPyramid *pPyr2,
                         const IppiPoint_32f *pPrev, IppiPoint_32f *pNext, Ipp8s *pStatus, Ipp32f *pError,
                         int numFeat, int winSize, int maxLev, int maxIter, Ipp32f threshold,
                         IppiOptFlowPyrLK_8u_C1R *pState))

IPPAPI(IppStatus, ippiOpticalFlowPyrLK_16u_C1R, (IppiPyramid *pPyr1, IppiPyramid *pPyr2,
                         const IppiPoint_32f *pPrev, IppiPoint_32f *pNext, Ipp8s *pStatus, Ipp32f *pError,
                         int numFeat, int winSize, int maxLev, int maxIter, Ipp32f threshold,
                         IppiOptFlowPyrLK_16u_C1R *pState))

IPPAPI(IppStatus, ippiOpticalFlowPyrLK_32f_C1R, (IppiPyramid *pPyr1, IppiPyramid *pPyr2,
                         const IppiPoint_32f *pRrev, IppiPoint_32f *pNext, Ipp8s *pStatus, Ipp32f *pError,
                         int numFeat, int winSize, int maxLev, int maxIter, Ipp32f threshold,
                         IppiOptFlowPyrLK_32f_C1R *pState))



/****************************************************************************************\
*                                    Universal Pyramids                                  *
\****************************************************************************************/

/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiPyramidGetSize
//
//  Purpose:    Computes the size of the structure for pyramids and the size
//              of the required work buffer (in bytes)
//
//  Arguments:
//    pPyrSize              Pointer to the size value of pyramid structure
//    pSizeBuf              Pointer to the size value of the pyramid external work buffer
//    level                 Maximal number pyramid level.
//    roiSize               Zero level image ROI size.
//    rate                  Neighbour levels ratio (1<rate<=10)
//
//  Return:
//    ippStsNoErr           Ok
//    ippStsNullPtrErr      One of pointers is NULL
//    ippStsSizeErr         roiSize has a field with zero or negative value.
//    ippStsBadArgErr       level is equal to or less than 0 or if rate has wrong value.
*/

IPPAPI( IppStatus, ippiPyramidGetSize,(int* pPyrSize, int* pBufSize, int level, IppiSize roiSize, Ipp32f rate))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiPyramidInit
//
//  Purpose:    Initializes structure for pyramids, calculates ROI for layers.
//
//  Arguments:
//    pPyr                  Pointer to the pointer to the pyramid structure.
//    level                 Maximal number pyramid level.
//    roiSize               Zero level image ROI size.
//    rate                  Neighbour levels ratio (1<rate<=10).
//    pPyrBuffer            Pointer to the buffer to initialize structure for pyramids.
//    pBuffer               Pointer to the work buffer.
//
//  Return:
//    ippStsNoErr           Ok
//    ippStsNullPtrErr      One of pointers is NULL
//    ippStsSizeErr         roiSize has a field with zero or negative value.
//    ippStsBadArgErr       level is equal to or less than 0 or if rate has wrong value.
*/

IPPAPI( IppStatus, ippiPyramidInit,( IppiPyramid** pPyr, int level, IppiSize roiSize, Ipp32f rate, Ipp8u* pPyrBuffer, Ipp8u* pBuffer))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiPyramidLayerDownGetSize_8u_C1R,   ippiPyramidLayerDownGetSize_8u_C3R
//              ippiPyramidLayerDownGetSize_16u_C1R,  ippiPyramidLayerDownGetSize_16u_C3R
//              ippiPyramidLayerDownGetSize_32f_C1R,  ippiPyramidLayerDownGetSize_32f_C3R
//              ippiPyramidLayerUpGetSize_8u_C1R,     ippiPyramidLayerUpGetSize_8u_C3R
//              ippiPyramidLayerUpGetSize_16u_C1R,    ippiPyramidLayerUpGetSize_16u_C3R
//              ippiPyramidLayerUpGetSizec_32f_C1R,   ippiPyramidLayerUpGetSize_32f_C3R
//
//  Purpose:    Calculates the size of structure for creating a lower(an upper) pyramid layer and the size
//              of the temporary  buffer (in bytes).
//
//  Arguments:
//    srcRoi                   Source image ROI size.
//    dstRoi                   Destination image ROI size.
//    rate                     Neighbour levels ratio (1<rate<=10)
//    kerSize                  Kernel size
//    pStateSize               Pointer to the size value of pyramid state structure.
//    pBufSize                 Pointer to the size value of the external work buffer.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsBadArgErr          Bad rate or kernel size
//
*/

IPPAPI(IppStatus, ippiPyramidLayerDownGetSize_8u_C1R, (IppiSize srcRoi, Ipp32f rate, int kerSize,
                         int* pStateSize, int* pBufSize))
IPPAPI(IppStatus, ippiPyramidLayerDownGetSize_16u_C1R,(IppiSize srcRoi, Ipp32f rate, int kerSize,
                         int* pStateSize, int* pBufSize))
IPPAPI(IppStatus, ippiPyramidLayerDownGetSize_32f_C1R,(IppiSize srcRoi, Ipp32f rate, int kerSize,
                         int* pStateSize, int* pBufSize))
IPPAPI(IppStatus, ippiPyramidLayerDownGetSize_8u_C3R, (IppiSize srcRoi, Ipp32f rate, int kerSize,
                         int* pStateSize, int* pBufSize))
IPPAPI(IppStatus, ippiPyramidLayerDownGetSize_16u_C3R,(IppiSize srcRoi, Ipp32f rate, int kerSize,
                         int* pStateSize, int* pBufSize))
IPPAPI(IppStatus, ippiPyramidLayerDownGetSize_32f_C3R,(IppiSize srcRoi, Ipp32f rate, int kerSize,
                         int* pStateSize, int* pBufSize))


IPPAPI(IppStatus, ippiPyramidLayerUpGetSize_8u_C1R, (IppiSize dstRoi, Ipp32f rate, int kerSize, int* pStateSize))
IPPAPI(IppStatus, ippiPyramidLayerUpGetSize_16u_C1R,(IppiSize dstRoi, Ipp32f rate, int kerSize, int* pStateSize))
IPPAPI(IppStatus, ippiPyramidLayerUpGetSize_32f_C1R,(IppiSize dstRoi, Ipp32f rate, int kerSize, int* pStateSize))
IPPAPI(IppStatus, ippiPyramidLayerUpGetSize_8u_C3R, (IppiSize dstRoi, Ipp32f rate, int kerSize, int* pStateSize))
IPPAPI(IppStatus, ippiPyramidLayerUpGetSize_16u_C3R,(IppiSize dstRoi, Ipp32f rate, int kerSize, int* pStateSize))
IPPAPI(IppStatus, ippiPyramidLayerUpGetSize_32f_C3R,(IppiSize dstRoi, Ipp32f rate, int kerSize, int* pStateSize))




/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiPyramidLayerDownInit_8u_C1R,   ippiPyramidLayerDownInit_8u_C3R
//              ippiPyramidLayerDownInit_16u_C1R,  ippiPyramidLayerDownInit_16u_C3R
//              ippiPyramidLayerDownInit_32f_C1R,  ippiPyramidLayerDownInit_32f_C3R
//              ippiPyramidLayerUpInit_8u_C1R,     ippiPyramidLayerUpInit_8u_C3R
//              ippiPyramidLayerUpInit_16u_C1R,    ippiPyramidLayerUpInit_16u_C3R
//              ippiPyramidLayerUpInit_32f_C1R,    ippiPyramidLayerUpInit_32f_C3R
//
//  Purpose:    Initializesa structure for creating a lower(an upper) pyramid layer.
//
//  Arguments:
//    ppState                  Pointer to the pointer to initialized pyramid state structure
//    srcRoi                   Source image ROI size.
//    dstRoi                   Destination image ROI size.
//    rate                     Neighbour levels ratio (1<rate<=10)
//    pKernel                  Separable symmetric kernel of odd length
//    kerSize                  Kernel size
//    mode                     IPPI_INTER_LINEAR - bilinear interpolation
//    StateBuf                 Pointer to the buffer to initialize state structure for pyramids.
//    pBuffer                  Pointer to the work buffer.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsBadArgErr          Bad mode, rate or kernel size
*/


IPPAPI(IppStatus, ippiPyramidLayerDownInit_8u_C1R, (IppiPyramidDownState_8u_C1R**  ppState, IppiSize srcRoi,
                         Ipp32f rate, Ipp16s* pKernel, int kerSize, int mode, Ipp8u* StateBuf, Ipp8u* Buffer))
IPPAPI(IppStatus, ippiPyramidLayerDownInit_16u_C1R,(IppiPyramidDownState_16u_C1R** ppState, IppiSize srcRoi,
                         Ipp32f rate, Ipp16s* pKernel, int kerSize, int mode, Ipp8u* StateBuf, Ipp8u* Buffer))
IPPAPI(IppStatus, ippiPyramidLayerDownInit_32f_C1R,(IppiPyramidDownState_32f_C1R** pState, IppiSize srcRoi,
                         Ipp32f rate, Ipp32f* pKernel, int kerSize, int mode, Ipp8u* StateBuf, Ipp8u* Buffer))
IPPAPI(IppStatus, ippiPyramidLayerDownInit_8u_C3R, (IppiPyramidDownState_8u_C3R**  ppState, IppiSize srcRoi,
                         Ipp32f rate, Ipp16s* pKernel, int kerSize, int mode, Ipp8u* StateBuf, Ipp8u* Buffer))
IPPAPI(IppStatus, ippiPyramidLayerDownInit_16u_C3R,(IppiPyramidDownState_16u_C3R** ppState, IppiSize srcRoi,
                         Ipp32f rate, Ipp16s* pKernel, int kerSize, int mode, Ipp8u* StateBuf, Ipp8u* Buffer))
IPPAPI(IppStatus, ippiPyramidLayerDownInit_32f_C3R,(IppiPyramidDownState_32f_C3R** ppState, IppiSize srcRoi,
                         Ipp32f rate, Ipp32f* pKernel, int kerSize, int mode, Ipp8u* StateBuf, Ipp8u* Buffer))


IPPAPI(IppStatus, ippiPyramidLayerUpInit_8u_C1R, (IppiPyramidUpState_8u_C1R**  ppState, IppiSize dstRoi,
                         Ipp32f rate, Ipp16s* pKernel, int kerSize, int mode, Ipp8u* StateBuf))
IPPAPI(IppStatus, ippiPyramidLayerUpInit_16u_C1R,(IppiPyramidUpState_16u_C1R** ppState, IppiSize dstRoi,
                         Ipp32f rate, Ipp16s* pKernel, int kerSize, int mode, Ipp8u* StateBuf))
IPPAPI(IppStatus, ippiPyramidLayerUpInit_32f_C1R,(IppiPyramidUpState_32f_C1R** ppState, IppiSize dstRoi,
                         Ipp32f rate, Ipp32f* pKernel, int kerSize, int mode, Ipp8u* StateBuf))
IPPAPI(IppStatus, ippiPyramidLayerUpInit_8u_C3R, (IppiPyramidUpState_8u_C3R**  ppState, IppiSize dstRoi,
                         Ipp32f rate, Ipp16s* pKernel, int kerSize, int mode, Ipp8u* StateBuf))
IPPAPI(IppStatus, ippiPyramidLayerUpInit_16u_C3R,(IppiPyramidUpState_16u_C3R** ppState, IppiSize dstRoi,
                         Ipp32f rate, Ipp16s* pKernel, int kerSize, int mode, Ipp8u* StateBuf))
IPPAPI(IppStatus, ippiPyramidLayerUpInit_32f_C3R,(IppiPyramidUpState_32f_C3R** ppState, IppiSize dstRoi,
                         Ipp32f rate, Ipp32f* pKernel, int kerSize, int mode, Ipp8u* StateBuf))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiGetPyramidDownROI, ippiGetPyramidUpROI
//
//  Purpose:    Calculate possible size of destination ROI.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            Wrong src roi
//    ippStsBadArgErr          Wrong rate
//
//  Arguments:
//    srcRoi                   Source image ROI size.
//    pDstRoi                  Pointer to destination image ROI size (down).
//    pDstRoiMin               Pointer to minimal destination image ROI size (up).
//    pDstRoiMax               Pointer to maximal destination image ROI size (up).
//    rate                     Neighbour levels ratio (1<rate<=10)
//
//  Notes:                     For up case destination size belongs to interval
//                             max((int)((float)((src-1)*rate)),src+1)<=dst<=
//                             max((int)((float)(src)*rate)),src+1)
*/

IPPAPI(IppStatus, ippiGetPyramidDownROI,(IppiSize srcRoi, IppiSize *pDstRoi, Ipp32f rate))
IPPAPI(IppStatus, ippiGetPyramidUpROI,(IppiSize srcRoi, IppiSize *pDstRoiMin, IppiSize *pDstRoiMax, Ipp32f rate))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiPyramidLayerDown_8u_C1R, ippiPyramidLayerDown_16u_C1R, ippiPyramidLayerDown_32f_C1R
//              ippiPyramidLayerDown_8u_C3R, ippiPyramidLayerDown_16u_C3R, ippiPyramidLayerDown_32f_C3R
//              ippiPyramidLayerUp_8u_C1R,   ippiPyramidLayerUp_16u_C1R,   ippiPyramidLayerUp_32f_C1R
//              ippiPyramidLayerUp_8u_C3R,   ippiPyramidLayerUp_16u_C3R,   ippiPyramidLayerUp_32f_C3R
//
//  Purpose:    Perform downsampling/upsampling of the image with 5x5 gaussian.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of the specified pointers is NULL
//    ippStsSizeErr            The srcRoiSize or dstRoiSize has a fild with zero or negativ value
//    ippStsStepErr            The steps in images are too small
//    ippStsBadArgErr          pState->rate has wrong value
//    ippStsNotEvenStepErr     One of the step values is not divisibly by 4 for floating-point
//                             images, or by 2 for short-integer images.
//  Arguments:
//    pSrc                     Pointer to the source image
//    srcStep                  Step in byte through the source image
//    srcRoiSize               Size of the source image ROI in pixel.
//    dstRoiSize               Size of the destination image ROI in pixel.
//    pDst                     Pointer to destination image
//    dstStep                  Step in byte through the destination image
//    pState                   Pointer to the pyramid layer structure
*/

IPPAPI(IppStatus, ippiPyramidLayerDown_8u_C1R, (const Ipp8u* pSrc, int srcStep, IppiSize srcRoiSize,
                         Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiPyramidDownState_8u_C1R* pState))
IPPAPI(IppStatus, ippiPyramidLayerDown_8u_C3R, (const Ipp8u* pSrc, int srcStep, IppiSize srcRoiSize,
                         Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiPyramidDownState_8u_C3R* pState))
IPPAPI(IppStatus, ippiPyramidLayerDown_16u_C1R,(const Ipp16u* pSrc, int srcStep, IppiSize srcRoiSize,
                         Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiPyramidDownState_16u_C1R* pState))
IPPAPI(IppStatus, ippiPyramidLayerDown_16u_C3R,(const Ipp16u* pSrc, int srcStep, IppiSize srcRoiSize,
                         Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiPyramidDownState_16u_C3R* pState))
IPPAPI(IppStatus, ippiPyramidLayerDown_32f_C1R,(const Ipp32f* pSrc, int srcStep, IppiSize srcRoiSize,
                         Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiPyramidDownState_32f_C1R* pState))
IPPAPI(IppStatus, ippiPyramidLayerDown_32f_C3R,(const Ipp32f* pSrc, int srcStep, IppiSize srcRoiSize,
                         Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiPyramidDownState_32f_C3R* pState))

IPPAPI(IppStatus, ippiPyramidLayerUp_8u_C1R, (const Ipp8u* pSrc, int srcStep, IppiSize srcRoiSize,
                         Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiPyramidUpState_8u_C1R* pState))
IPPAPI(IppStatus, ippiPyramidLayerUp_8u_C3R, (const Ipp8u* pSrc, int srcStep, IppiSize srcRoiSize,
                         Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, IppiPyramidUpState_8u_C3R* pState))
IPPAPI(IppStatus, ippiPyramidLayerUp_16u_C1R,(const Ipp16u* pSrc, int srcStep, IppiSize srcRoiSize,
                         Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiPyramidUpState_16u_C1R* pState))
IPPAPI(IppStatus, ippiPyramidLayerUp_16u_C3R,(const Ipp16u* pSrc, int srcStep, IppiSize srcRoiSize,
                         Ipp16u* pDst, int dstStep, IppiSize dstRoiSize, IppiPyramidUpState_16u_C3R* pState))
IPPAPI(IppStatus, ippiPyramidLayerUp_32f_C1R,(const Ipp32f* pSrc, int srcStep, IppiSize srcRoiSize,
                         Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiPyramidUpState_32f_C1R* pState))
IPPAPI(IppStatus, ippiPyramidLayerUp_32f_C3R,(const Ipp32f* pSrc, int srcStep, IppiSize srcRoiSize,
                         Ipp32f* pDst, int dstStep, IppiSize dstRoiSize, IppiPyramidUpState_32f_C3R* pState))


/****************************************************************************************\
*                                     Haar Classifier                                    *
\****************************************************************************************/


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:      ippiHaarClassifierInit  ippiTiltedHaarClassifierInit
//
//  Purpose:   Initializes memory for the stage of the Haar classifier.
//
//  Arguments:
//    pState                   The pointer to the pointer to the Haar classifier structure.
//    pFeature                 The pointer to the array of features.
//    pWeight                  The pointer to the array of feature weights.
//    pThreshold               The pointer to the array of classifier thresholds [length].
//    pVal1, pVal2             Pointers to arrays of classifier results [length].
//    pNum                     The pointer to the array of classifier lengths [length].
//    length                   The number of classifiers in the stage.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The number of classifiers or features is less or equal zero
//    ippStsbadArgErr          The bad feature rectangular
//    ippStsMemAllocErr        Memory allocation error
//
//  Notes:  For integer version feature weights pWeight are in Q0, classifier thresholds
//          pThreshold are in QT (see ApplyHaarClassifier), pVal1 and pVal2 are scale as
//          stage thresholds threshold of ApplyHaarClassifier function
*/
IPPAPI(IppStatus, ippiHaarClassifierInit_32f, (IppiHaarClassifier_32f *pState, const IppiRect* pFeature, const Ipp32f* pWeight,
                              const Ipp32f* pThreshold, const Ipp32f* pVal1, const Ipp32f* pVal2, const int* pNum, int length))
IPPAPI(IppStatus, ippiHaarClassifierInit_32s, (IppiHaarClassifier_32s *pState, const IppiRect* pFeature, const Ipp32s* pWeight,
                              const Ipp32s* pThreshold, const Ipp32s* pVal1, const Ipp32s* pVal2, const int* pNum, int length))
IPPAPI(IppStatus, ippiTiltedHaarClassifierInit_32f, (IppiHaarClassifier_32f *pState, const IppiRect* pFeature, const Ipp32f* pWeight,
                              const Ipp32f* pThreshold, const Ipp32f* pVal1, const Ipp32f* pVal2, const int* pNum, int length))
IPPAPI(IppStatus, ippiTiltedHaarClassifierInit_32s, (IppiHaarClassifier_32s *pState, const IppiRect* pFeature, const Ipp32s* pWeight,
                              const Ipp32s* pThreshold, const Ipp32s* pVal1, const Ipp32s* pVal2, const int* pNum, int length))


IPPAPI(IppStatus, ippiHaarClassifierGetSize, ( IppDataType dataType, IppiSize roiSize, const int* pNum, int length, int *pSize ))



/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:      ippiTiltHaarFeatures_32f,  ippiTiltHaarFeatures_32s
//  Purpose:   Tilts marked feature on -45 degree
//  Arguments:
//    pMask                    The mask of feature to tilt.
//    flag                     1 - left bottom  -45 degree
//                             0 - left top     +45 degree
//    pState                   The pointer to the Haar classifier structure.
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//  Notes:  The mask length is equal to the number of classifiers in the classifier
//          If pMask[i] != 0 i-th feature is tilted
//          Classifiers with tilted features require two input integral images and
//          can be used by rippiApplyMixedHaarClassifier functions
*/
IPPAPI(IppStatus, ippiTiltHaarFeatures_32f, (const Ipp8u *pMask, int flag, IppiHaarClassifier_32f *pState))
IPPAPI(IppStatus, ippiTiltHaarFeatures_32s, (const Ipp8u *pMask, int flag, IppiHaarClassifier_32s *pState))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiGetHaarClassifierSize_32f,      ippiGetHaarClassifierSize_32s
//  Purpose:    Returns the size of the Haar classifier.
//  Arguments:
//    pState    Pointer to the Haar classifier structure.
//    pSize        Pointer to the returned value of Haar classifier size.
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
*/
IPPAPI(IppStatus, ippiGetHaarClassifierSize_32f, (IppiHaarClassifier_32f* pState, IppiSize* pSize))
IPPAPI(IppStatus, ippiGetHaarClassifierSize_32s, (IppiHaarClassifier_32s* pState, IppiSize* pSize))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:      ippiApplyHaarClassifier,    ippiApplyMixedHaarClassifier
//  Purpose:   Applies the stage of Haar classifiers to the image.
//  Arguments:
//    pSrc                     The pointer  to the source image of integrals.
//    srcStep                  The step in bytes through the source image.
//    pNorm                    The pointer  to the source image of norm factors.
//    normStep                 The step  in bytes through the image of norm factors.
//    pMask                    The pointer  to the source and destination image of classification decisions.
//    maskStep                 The step  in bytes through the image of classification decisions.
//    pPositive                The pointer to the number of positive decisions.
//    roiSize                  The size of source and destination images ROI in pixels.
//    threshold                The stage threshold value.
//    pState                   The pointer to the Haar classifier structure.
//    scaleFactor              Scale factor for classifier threshold*norm, <= 0
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The number of classifiers or features is less or equal zero
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
*/
IPPAPI(IppStatus, ippiApplyHaarClassifier_32f_C1R, (const Ipp32f* pSrc, int srcStep,
   const Ipp32f* pNorm, int normStep, Ipp8u* pMask, int maskStep, IppiSize roiSize, int *pPositive, Ipp32f threshold, IppiHaarClassifier_32f *pState))
IPPAPI(IppStatus, ippiApplyHaarClassifier_32s32f_C1R, (const Ipp32s* pSrc, int srcStep,
   const Ipp32f* pNorm, int normStep, Ipp8u* pMask, int maskStep, IppiSize roiSize, int *pPositive, Ipp32f threshold, IppiHaarClassifier_32f *pState))
IPPAPI(IppStatus, ippiApplyHaarClassifier_32s_C1RSfs, (const Ipp32s* pSrc, int srcStep,
   const Ipp32s* pNorm, int normStep, Ipp8u* pMask, int maskStep, IppiSize roiSize, int *pPositive, Ipp32s threshold, IppiHaarClassifier_32s *pState, int scaleFactor))

IPPAPI(IppStatus, ippiApplyMixedHaarClassifier_32f_C1R, (const Ipp32f* pSrc, int srcStep, const Ipp32f* pTilt, int tiltStep,
   const Ipp32f* pNorm, int normStep, Ipp8u* pMask, int maskStep, IppiSize roiSize, int *pPositive, Ipp32f threshold, IppiHaarClassifier_32f *pState))
IPPAPI(IppStatus, ippiApplyMixedHaarClassifier_32s32f_C1R, (const Ipp32s* pSrc, int srcStep, const Ipp32s* pTilt, int tiltStep,
   const Ipp32f* pNorm, int normStep, Ipp8u* pMask, int maskStep, IppiSize roiSize, int *pPositive, Ipp32f threshold, IppiHaarClassifier_32f *pState))
IPPAPI(IppStatus, ippiApplyMixedHaarClassifier_32s_C1RSfs, (const Ipp32s* pSrc, int srcStep, const Ipp32s* pTilt, int tiltStep,
   const Ipp32s* pNorm, int normStep, Ipp8u* pMask, int maskStep, IppiSize roiSize, int *pPositive, Ipp32s threshold, IppiHaarClassifier_32s *pState, int scaleFactor))



/****************************************************************************************\
*                              Correction of Camera Distortions                          *
\****************************************************************************************/


/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name:    ippiUndistortGetSize
//
//  Purpose: calculate the buffer size for Undistort functions
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//
//  Parameters:
//    roiSize                  Maximal image size
//    pBufsize                 Pointer to work buffer size
//
//  Notes:
//F*/

IPPAPI(IppStatus, ippiUndistortGetSize, (IppiSize roiSize, int *pBufsize))


/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name:    ippiCreateMapCameraUndistort_32f_C1R
//
//  Purpose: initialize x and y maps for undistortion by ippiRemap function
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         pxMap or pyMap is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//    ippStsBadArgErr          Bad fx or fy
//
//  Parameters:
//    pxMap                    Pointer to x map (result, free by ippiFree)
//    xStep                    Pointer to x map row step (result)
//    pyMap                    Pointer to x map (result, free by ippiFree)
//    yStep                    Pointer to x map row step (result)
//    roiSize                  Maximal image size
//    fx, fy                   Focal lengths
//    cx, cy                   Coordinates of principal point
//    k1, k2                   Coeffs of radial distortion
//    p1, p2                   Coeffs of tangential distortion
//    pBuffer                  Pointer to work buffer
//
//  Notes:
//    fx, fy != 0
//F*/

IPPAPI(IppStatus, ippiCreateMapCameraUndistort_32f_C1R, (Ipp32f *pxMap, int xStep,
                  Ipp32f *pyMap, int yStep, IppiSize roiSize, Ipp32f fx, Ipp32f fy, Ipp32f cx, Ipp32f cy,
                  Ipp32f k1, Ipp32f k2, Ipp32f p1, Ipp32f p2, Ipp8u *pBuffer))


/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name:    ippiUndistortRadial_8u_C1R,  ippiUndistortRadial_8u_C3R,
//           ippiUndistortRadial_16u_C1R, ippiUndistortRadial_16u_C3R
//           ippiUndistortRadial_32f_C1R, ippiUndistortRadial_32f_C3R
//
//  Purpose: correct camera distortion
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         pSrc or pDst is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//    ippStsBadArgErr          Bad fx or fy
//
//  Parameters:
//    pSrc                     Source image
//    srcStep                  Step in source image
//    pDst                     Pointer to destination image
//    dstStep                  Step in destination image
//    roiSize                  Source and destination image ROI size.
//    fx, fy                   Focal lengths
//    cx, cy                   Coordinates of principal point
//    k1, k2                   Coeffs of radial distortion
//    pBuffer                  Pointer to work buffer
//
//  Notes:
//F*/

IPPAPI(IppStatus, ippiUndistortRadial_8u_C1R, (const Ipp8u* pSrc, int srcStep,
                         Ipp8u* pDst, int dstStep, IppiSize roiSize, Ipp32f fx, Ipp32f fy,
                         Ipp32f cx, Ipp32f cy, Ipp32f k1, Ipp32f k2, Ipp8u *pBuffer))

IPPAPI(IppStatus, ippiUndistortRadial_16u_C1R, (const Ipp16u* pSrc, int srcStep,
                         Ipp16u* pDst, int dstStep, IppiSize roiSize, Ipp32f fx, Ipp32f fy,
                         Ipp32f cx, Ipp32f cy, Ipp32f k1, Ipp32f k2, Ipp8u *pBuffer))

IPPAPI(IppStatus, ippiUndistortRadial_32f_C1R, (const Ipp32f* pSrc, int srcStep,
                         Ipp32f* pDst, int dstStep, IppiSize roiSize, Ipp32f fx, Ipp32f fy,
                         Ipp32f cx, Ipp32f cy, Ipp32f k1, Ipp32f k2, Ipp8u *pBuffer))

IPPAPI(IppStatus, ippiUndistortRadial_8u_C3R, (const Ipp8u* pSrc, int srcStep,
                         Ipp8u* pDst, int dstStep, IppiSize roiSize, Ipp32f fx, Ipp32f fy,
                         Ipp32f cx, Ipp32f cy, Ipp32f k1, Ipp32f k2, Ipp8u *pBuffer))

IPPAPI(IppStatus, ippiUndistortRadial_16u_C3R, (const Ipp16u* pSrc, int srcStep,
                         Ipp16u* pDst, int dstStep, IppiSize roiSize, Ipp32f fx, Ipp32f fy,
                         Ipp32f cx, Ipp32f cy, Ipp32f k1, Ipp32f k2, Ipp8u *pBuffer))

IPPAPI(IppStatus, ippiUndistortRadial_32f_C3R, (const Ipp32f* pSrc, int srcStep,
                         Ipp32f* pDst, int dstStep, IppiSize roiSize, Ipp32f fx, Ipp32f fy,
                         Ipp32f cx, Ipp32f cy, Ipp32f k1, Ipp32f k2, Ipp8u *pBuffer))


/*F/////////////////////////////////////////////////////////////////////////////////////////////////
//  Name:    ippiGradientColorToGray_8u_C3C1R,
//           ippiGradientColorToGray_16u_C3C1R,
//           ippiGradientColorToGray_32f_C3C1R
//
//  Purpose: Calculate gray gradient from 3-channel gradient image.
//
//  Return:
//    ippStsNoErr         Ok
//    ippStsNullPtrErr    One of pointers is NULL
//    ippStsSizeErr       The width or height of images is less or equal zero
//    ippStsStepErr       The steps in images are too small
//
//  Parameters:
//    pSrc                The source image
//    srcStep             Its step
//    pDst                The destination image
//    dstStep             Its step
//    roiSize             ROI size
//    norm                The norm type
//                                  rippiNormInf = max(|a|,|b|,|c|)
//                                  rippiNormL1  = (|a|+|b|+|c|)/3
//                                  rippiNormL2  = sqrt((a*a+b*b+c*c)/3)
//
//  Note:                 For integer flavors, the result is scaled to the full range of the
//                        destination data type
//F*/

IPPAPI(IppStatus, ippiGradientColorToGray_8u_C3C1R, (const Ipp8u* pSrc, int srcStep,
                 Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiNorm norm))

IPPAPI(IppStatus, ippiGradientColorToGray_16u_C3C1R, (const Ipp16u* pSrc, int srcStep,
                 Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiNorm norm))

IPPAPI(IppStatus, ippiGradientColorToGray_32f_C3C1R, (const Ipp32f* pSrc, int srcStep,
                 Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiNorm norm))

/* ///////////////////////////////////////////////////////////////////////////////////////////////////
//  Name:  ippiInpaintGetSize
//
//  Purpose:    Computes the size of the State structure  and the size
//              of the required work buffer (in bytes).
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of the image are less or equal zero
//    ippStsStepErr            The step in distance image is too small
//    ippStsBadArgErr          Wrong radius or flags
//    ippStsNumChannensErr     Specified number of channels is invalid or unsupported
//
//  Parameters:
//    pMask                    Pointer to the mask image ROI
//    maskStep                 Distance in bytes between starts of consecutive lines in the mask image
//    roiSize                  Size of the image ROI in pixels.
//    radius                   Neighborhood radius (dist<=radius pixels are processed)
//    flags                    Inpainting flags
//                                IPP_INPAINT_TELEA  Telea algorithm is used
//                                IPP_INPAINT_NS     Navier-Stokes equation is used
//    channels                 number of image channels
//    pStateSize               Pointer to the size value state structure.
//    pBufSize                 Pointer to the size value of the external work buffer.
*/

IPPAPI(IppStatus, ippiInpaintGetSize, (const Ipp8u* pMask, int maskStep,IppiSize roiSize, Ipp32f radius, IppiInpaintFlag flags,
                                                 int channels, int* pStateSize, int* pBufSize))


/* ///////////////////////////////////////////////////////////////////////////////////////////////////
//  Name:  ippiInpaintInit_8u_C1R,    ippiInpaintInit_8u_C3R
//
//  Purpose:    Initializes a structure for direct inpainting algorithm
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of the image  are less or equal zero
//    ippStsStepErr            The steps in distance image or mask image ROI are too small
//    ippStsNotEvenStepErr     Step is not multiple of element
//    ippStsBadArgErr          Wrong radius or flags
//
//  Parameters:
//    ppState                  Double pointer to the state structure for the image
//                             inpaiting.
//    pDist                    Pointer to the ROI of the image of distances.
//    distStep                 Distance in bytes between starts of consecutive lines in
//                             the image of distances.
//    pMask                    Pointer to the mask image ROI.
//    maskStep                 Distance in bytes between starts of consecutive lines in
//                             the mask image.
//    roiSize                  Size of the image ROI in pixels
//    radius                   Neighborhood radius (dist<=radius pixels are processed)
//    flags                    Specifies algorithm for image inpainting; following values
//                             are possible:
//                                IPP_INPAINT_TELEA  Telea algorithm is used
//                                IPP_INPAINT_NS     Navier-Stokes equation is used
//    StateBuf                 Pointer to the buffer to initialize state structure.
//    pBuffer                  Pointer to the work buffer.
*/

IPPAPI(IppStatus, ippiInpaintInit_8u_C1R, (IppiInpaintState_8u_C1R** ppState, const Ipp32f* pDist,
                                                 int distStep, const Ipp8u* pMask, int maskStep,
                                                 IppiSize roiSize, Ipp32f radius, IppiInpaintFlag flags,
                                                 Ipp8u* pStateBuf, Ipp8u* pBuf))

IPPAPI(IppStatus, ippiInpaintInit_8u_C3R, (IppiInpaintState_8u_C3R** ppState, const Ipp32f* pDist,
                                                 int distStep, const Ipp8u* pMask, int maskStep,
                                                 IppiSize roiSize, Ipp32f radius, IppiInpaintFlag flags,
                                                 Ipp8u* pStateBuf, Ipp8u* pBuf))


/* ///////////////////////////////////////////////////////////////////////////////////////////////////
//  Name:  ippiInpaint_8u_C1R,    ippiInpaint_8u_C3R
//
//  Purpose:    restores damaged image area by direct inpainting
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width of the image  are less or equal zero or different from init
//    ippStsStepErr            The steps in images are too small
//
//  Parameters:
//    pSrc                     Pointer to the source image ROI.
//    srcStep                  Distance in bytes between starts of consecutive lines in the source image.
//    pDst                     Pointer to the destination image ROI.
//    dstStep                  Distance in bytes between starts of consecutive lines in the
//                             destination image.
//    roiSize                  Size of the image ROI in pixels.
//    pState                   Pointer to inpainting structure
//    pBuffer                  Pointer to work buffer
*/

IPPAPI(IppStatus, ippiInpaint_8u_C1R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
                                       IppiSize roiSize, IppiInpaintState_8u_C1R* pState, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiInpaint_8u_C3R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,
                                       IppiSize roiSize, IppiInpaintState_8u_C1R* pState, Ipp8u* pBuffer))


/* ///////////////////////////////////////////////////////////////////////////////////////////////////
//  Name:  ippiSegmentGradientGetBufferSize_8u_C1R
//         ippiSegmentGradientGetBufferSize_8u_C3R
//
//  Purpose:    Get size of external buffer.
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width of the image or kernel size are less or equal zero
//
//  Parameters:
//    roiSize                  The image ROI size
//    pBufSize                 The pointer to the buffer size
*/

IPPAPI(IppStatus, ippiSegmentGradientGetBufferSize_8u_C1R, (IppiSize roiSize, int* pBufSize))

IPPAPI(IppStatus, ippiSegmentGradientGetBufferSize_8u_C3R, (IppiSize roiSize, int* pBufSize))


/* ///////////////////////////////////////////////////////////////////////////////////////////////////
//  Name:  ippiSegmentGradient_8u_C1R, ippiSegmentGradient_8u_C3R
//
//  Purpose:    Draw bounds between image segments
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width of the image or kernel size are less or equal zero
//    ippStsStepErr            The steps in images are too small
//
//  Parameters:
//    pSrc                     Source image
//    srcStep                  Its step
//    pMarker                  Source and destination marker image
//    markerStep               Its step
//    roiSize                  Image ROI size
//    norm                     Type of norm to form the mask for maximum search:
//                                rippiNormInf   Infinity norm (8-connectivity, 3x3 rectangular mask).
//                                rippiNormL1    L1 norm (4-connectivity, 3x3 cross mask).
//    flag                     Flags
//                                IPP_SEGMENT_BORDER_4 Draw L1 segment borders.
//                                IPP_SEGMENT_BORDER_8 Draw Linf segment borders.
//    pBuffer                  Pointer to working buffer
*/

IPPAPI(IppStatus, ippiSegmentGradient_8u_C3IR, (const Ipp8u* pSrc, int srcStep, Ipp8u* pMarker,
                  int markerStep, IppiSize roiSize, IppiNorm norm, int flags, Ipp8u* pBuffer))


IPPAPI(IppStatus, ippiSegmentGradient_8u_C1IR, (const Ipp8u* pSrc, int srcStep, Ipp8u* pMarker,
                  int markerStep, IppiSize roiSize, IppiNorm norm, int flags, Ipp8u* pBuffer))


/* ///////////////////////////////////////////////////////////////////////////////////////////////////
//  Name:      ippiSegmentWatershedGetBufferSize
//
//  Purpose:   Get size of external buffer.
//
//  Parameters:
//    roiSize        - Size, in pixels, of the ROI.
//    pBufferSize    - Pointer to the calculated buffer size (in bytes).
//
//  Return:
//    ippStsNoErr      - OK.
//    ippStsNullPtrErr - Error when any of the specified pointers is NULL.
//    ippStsSizeErr    - Error when roiSize has a zero or negative value.
*/
IPPAPI(IppStatus, ippiSegmentWatershedGetBufferSize_8u_C1R    , (IppiSize roiSize, int *pBufSize))
IPPAPI(IppStatus, ippiSegmentWatershedGetBufferSize_8u16u_C1R , (IppiSize roiSize, int *pBufSize))
IPPAPI(IppStatus, ippiSegmentWatershedGetBufferSize_32f16u_C1R, (IppiSize roiSize, int *pBufSize))


/* ///////////////////////////////////////////////////////////////////////////////////////////////////
//  Name:  ippiSegmentWatershed
//
//  Purpose:    Draw bounds between image segments
//
//  Parameters:
//    pSrc           - Pointers to the source image ROI.
//    srcStep        - Distances, in bytes, between the starting points of consecutive lines in the source image.
//    pMarker        - Pointers to the marker image ROI.
//    markerStep     - Distances, in bytes, between the starting points of consecutive lines in the marker image.
//    roiSize        - Size, in pixels, of the ROI.
//    norm           - Type of norm to form the mask for maximum search:
//                         ippiNormInf   Infinity norm (8-connectivity, 3x3 rectangular mask);
//                         ippiNormL1    L1 norm (4-connectivity, 3x3 cross mask);
//                         ippiNormL2    approximation of L2 norm  (8-connectivity, 3x3 mask 11,15);
//                         ippiNormFM    Fast marching distance (4-connectivity).
//    flag           - Flags
//                         IPP_SEGMENT_QUEUE    Via priority queue (not supported for Ipp32f data).
//                         IPP_SEGMENT_DISTANCE Via distance transform.
//                         IPP_SEGMENT_BORDER_4 Draw L1 segment borders.
//                         IPP_SEGMENT_BORDER_8 Draw Linf segment borders.
//    pBuffer        - Pointer to the buffer for internal calculations.
//
//  Return:
//    ippStsNoErr      - OK.
//    ippStsNullPtrErr - Error when any of the specified pointers is NULL.
//    ippStsSizeErr    - Error when roiSize has a zero or negative value.
//    ippStsStepErr    - Error when The steps in images are too small.
*/
IPPAPI(IppStatus, ippiSegmentWatershed_8u_C1IR    , (const Ipp8u*  pSrc, int srcStep, Ipp8u*  pMarker, int markerStep, IppiSize roiSize, IppiNorm norm, int flag, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiSegmentWatershed_8u16u_C1IR , (const Ipp8u*  pSrc, int srcStep, Ipp16u* pMarker, int markerStep, IppiSize roiSize, IppiNorm norm, int flag, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiSegmentWatershed_32f16u_C1IR, (const Ipp32f* pSrc, int srcStep, Ipp16u* pMarker, int markerStep, IppiSize roiSize, IppiNorm norm, int flag, Ipp8u* pBuffer))


/* ///////////////////////////////////////////////////////////////////////////////////////////////////
//  Name:  ippiBoundSegments_8u_C1IR,  ippiBoundSegments_16u_C1IR
//
//  Purpose:    Draw bounds between image segments
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width of the image or kernel size are less or equal zero
//    ippStsStepErr            The steps in images are too small
//
//  Parameters:
//    pMarker                  Source and destination marker image
//    markerStep               Its step
//    roiSize                  Image ROI size
//    norm                     Type of norm to form the mask for maximum search:
//                                ippiNormInf   Infinity norm (8-connectivity, 3x3 rectangular mask).
//                                ippiNormL1    L1 norm (4-connectivity, 3x3 cross mask).
*/

IPPAPI(IppStatus, ippiBoundSegments_8u_C1IR, (Ipp8u* pMarker, int markerStep, IppiSize roiSize,
                                              Ipp8u val, IppiNorm norm))

IPPAPI(IppStatus, ippiBoundSegments_16u_C1IR, (Ipp16u* pMarker, int markerStep, IppiSize roiSize,
                                               Ipp16u val, IppiNorm norm))


/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name:    ippiLabelMarkersGetBufferSize_8u_C1R
//           ippiLabelMarkersGetBufferSize_8u32s_C1R
//           ippiLabelMarkersGetBufferSize_16u_C1R
//
//  Purpose: The functions calculate size of temporary buffer, required to run
//           marker labeling function
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//
//  Parameters:
//    roiSize                  ROI size
//    pBufSize                 Temporary buffer size
//F*/

IPPAPI(IppStatus, ippiLabelMarkersGetBufferSize_8u_C1R, (IppiSize roiSize, int* pBufSize))

IPPAPI(IppStatus, ippiLabelMarkersGetBufferSize_8u32s_C1R, (IppiSize roiSize, int* pBufSize))

IPPAPI(IppStatus, ippiLabelMarkersGetBufferSize_16u_C1R, (IppiSize roiSize, int* pBufSize))


/* ///////////////////////////////////////////////////////////////////////////////////////////////////
//  Name:  ippiLabelMarkers_8u_C1IR
//         ippiLabelMarkers_8u32s_C1R
//         ippiLabelMarkers_16u_C1IR
//
//  Purpose:    Labels connected non-zero components with different label values
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width of the image or kernel size are less or equal zero
//    ippStsStepErr            The steps in images are too small
//
//  Parameters:
//    pMarker                  Source and destination marker image
//    markerStep               Its step
//    roiSize                  Image ROI size
//    minLabel                 Minimal label value > 0
//    maxLabel                 Maximal label value < 255
//    norm                     Type of norm to form the mask for maximum search:
//                                ippiNormL1    L1 norm (4-connectivity, 3x3 cross mask).
//                                ippiNormInf   Infinity norm (8-connectivity, 3x3 rectangular mask).
//    pNumber                  Pointer to number of markers
//    pBuffer                  Pointer to working buffer
*/

IPPAPI(IppStatus, ippiLabelMarkers_8u_C1IR, (Ipp8u* pMarker, int markerStep, IppiSize roiSize,
                         int minLabel, int maxLabel, IppiNorm norm, int *pNumber, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiLabelMarkers_8u32s_C1R, (Ipp8u* pSrcMarker, int srcMarkerStep, Ipp32s* pDstMarker, int dstMarkerStep,
                         IppiSize roiSize, int minLabel, int maxLabel, IppiNorm norm, int *pNumber, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiLabelMarkers_16u_C1IR, (Ipp16u* pMarker, int markerStep, IppiSize roiSize,
                         int minLabel, int maxLabel, IppiNorm norm, int *pNumber, Ipp8u* pBuffer))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFilterGaussianGetBufferSize
//
//  Purpose:    Computes the size of the working buffer for the Gaussian filter
//
//  Return:
//     ippStsNoErr          Ok. Any other value indicates an error or a warning.
//     ippStsNullPtrErr     One of the pointers is NULL.
//     ippStsSizeErr        maxRoiSize  has a field with zero or negative value.
//     ippStsDataTypeErr    Indicates an error when dataType has an illegal value.
//     ippStsBadArgErr      Indicates an error if kernelSize is even or is less than 3.
//     ippStsChannelErr     Indicates an error when numChannels has an illegal value.
//
//  Arguments:
//     maxRoiSize           Maximal size of the image ROI in pixels.
//     kernelSize           Size of the Gaussian kernel (odd, greater or equal to 3).
//     dataType             Data type of the source and destination images.
//     numChannels          Number of channels in the images. Possible values are 1 and 3.
//     pSpecSize            Pointer to the computed size (in bytes) of the Gaussian
//                            specification structure.
//     pBufferSize          Pointer to the computed size (in bytes) of the external buffer.
*/
IPPAPI(IppStatus, ippiFilterGaussianGetBufferSize,(IppiSize maxRoiSize, Ipp32u kernelSize,
                  IppDataType dataType, int numChannels, int *pSpecSize, int* pBufferSize))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFilterGaussianInit
//
//  Purpose:    initialization of Spec for Gaussian filter
//
//  Return:
//     ippStsNoErr          Ok. Any other value indicates an error or a warning.
//     ippStsNullPtrErr     One of the pointers is NULL.
//     ippStsSizeErr        roiSize has a field with zero or negative value.
//     ippStsDataTypeErr    Indicates an error when borderType has an illegal value.
//     ippStsBadArgErr      kernelSize is even or is less than 3.
//     ippStsChannelErr     Indicates an error when numChannels has an illegal value.
//     ippStsBorderErr      Indicates an error condition if borderType has a illegal
//                           value.
//
//  Arguments:
//     roiSize              Size of the image ROI in pixels.
//     kernelSize           Size of the Gaussian kernel (odd, greater or equal to 3).
//     sigma                Standard deviation of the Gaussian kernel.
//     borderType           One of border supported types.
//     dataType             Data type of the source and destination images.
//     numChannels          Number of channels in the images. Possible values are 1 and 3.
//     pSpec                Pointer to the Spec.
//     pBuffer              Pointer to the buffer:
*/

IPPAPI(IppStatus, ippiFilterGaussianInit,(IppiSize roiSize, Ipp32u kernelSize, Ipp32f sigma,
                  IppiBorderType borderType, IppDataType dataType, int numChannels,
                  IppFilterGaussianSpec* pSpec, Ipp8u* pBuffer))

/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFilterGaussianGetSpecSize
//
//  Purpose:    Computes the size of the working buffer for the Gaussian filter GaussianSpec
//
//  Return:
//     ippStsNoErr          Ok. Any other value indicates an error or a warning.
//     ippStsNullPtrErr     One of the pointers is NULL.
//     ippStsSizeErr        maxRoiSize  has a field with zero or negative value.
//     ippStsDataTypeErr    Indicates an error when dataType has an illegal value.
//     ippStsBadArgErr      Indicates an error if kernelSize is even or is less than 3.
//     ippStsChannelErr     Indicates an error when numChannels has an illegal value.
//
//  Arguments:
//     kernelSize           Size of the Gaussian kernel (odd, greater or equal to 3).
//     dataType             Data type of the source and destination images.
//     numChannels          Number of channels in the images. Possible values are 1 and 3.
//     pSpecSize            Pointer to the computed size (in bytes) of the Gaussian
//                            specification structure.
//     pInitBufferSize      Pointer to the computed size (in bytes) of the external buffer for the Gaussian filter GaussianSpec.
*/
IPPAPI(IppStatus, ippiFilterGaussianGetSpecSize,(int kernelSize, IppDataType dataType, int numChannels, int *pSpecSize, int *pInitBufferSize))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFilterGaussian
//
//  Purpose:    Applies Gaussian filter with borders
//
//  Return:
//     ippStsNoErr      Ok. Any other value indicates an error or a warning.
//     ippStsNullPtrErr One of the specified pointers is NULL.
//     ippStsSizeErr    roiSize has a field with zero or negative value.
//     ippStsStepErr    Indicates an error condition if srcStep or dstStep is less
//                        than  roiSize.width * <pixelSize>.
//     ippStsNotEvenStepErr One of the step values is not divisible by 4 for floating-point images.
//     ippStsBadArgErr  kernelSize is less than 3 or sigma is less or equal than 0.
//
//  Arguments:
//     pSrc             Pointer to the source image ROI.
//     srcStep          Distance in bytes between starts of consecutive lines in the source image.
//     pDst             Pointer to the destination image ROI.
//     dstStep          Distance in bytes between starts of consecutive lines in the destination image.
//     roiSize          Size of the source and destination image ROI.
//     borderType       One of border supported types.
//     borderValue      Constant value to assign to pixels of the constant border. if border type equals ippBorderConstant
//     pSpec            Pointer to the Gaussian specification structure.
//     pBuffer          Pointer to the working buffer.
*/



IPPAPI(IppStatus, ippiFilterGaussian_32f_C1R,(const Ipp32f* pSrc, int srcStep,
      Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType, const Ipp32f borderValue[1],
      IppFilterGaussianSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterGaussian_16u_C1R,(const Ipp16u * pSrc, int srcStep,
      Ipp16u * pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,  const Ipp16u borderValue[1],
      IppFilterGaussianSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterGaussian_16s_C1R,(const Ipp16s* pSrc, int srcStep,
      Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,  const Ipp16s borderValue[1],
      IppFilterGaussianSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterGaussian_8u_C1R,(const Ipp8u* pSrc, int srcStep,
      Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,  const Ipp8u borderValue[1],
      IppFilterGaussianSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterGaussian_32f_C3R,(const Ipp32f* pSrc, int srcStep,
      Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,  const Ipp32f borderValue[3],
      IppFilterGaussianSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterGaussian_16u_C3R,(const Ipp16u * pSrc, int srcStep,
      Ipp16u * pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,  const Ipp16u borderValue[3],
      IppFilterGaussianSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterGaussian_16s_C3R,(const Ipp16s* pSrc, int srcStep,
      Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,  const Ipp16s borderValue[3],
      IppFilterGaussianSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterGaussian_8u_C3R,(const Ipp8u* pSrc, int srcStep,
      Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiBorderType borderType,  const Ipp8u borderValue[3],
      IppFilterGaussianSpec* pSpec, Ipp8u* pBuffer))


/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFilterGaussian
//
//  Purpose:    Applies Gaussian filter with borders
//
//  Return:
//     ippStsNoErr      Ok. Any other value indicates an error or a warning.
//     ippStsNullPtrErr One of the specified pointers is NULL.
//     ippStsSizeErr    roiSize has a field with zero or negative value.
//     ippStsStepErr    Indicates an error condition if srcStep or dstStep is less
//                        than  roiSize.width * <pixelSize>.
//     ippStsNotEvenStepErr One of the step values is not divisible by 4 for floating-point images.
//     ippStsBadArgErr  kernelSize is less than 3 or sigma is less or equal than 0.
//
//  Arguments:
//     pSrc             Pointer to the source image ROI.
//     srcStep          Distance in bytes between starts of consecutive lines in the source image.
//     pDst             Pointer to the destination image ROI.
//     dstStep          Distance in bytes between starts of consecutive lines in the destination image.
//     roiSize          Size of the source and destination image ROI.
//     borderType       One of border supported types.
//     borderValue      Constant value to assign to pixels of the constant border. if border type equals ippBorderConstant
//     pSpec            Pointer to the Gaussian specification structure.
//     pBuffer          Pointer to the working buffer.
*/

IPPAPI(IppStatus, ippiFilterGaussianBorder_32f_C1R,(const Ipp32f* pSrc, int srcStep,
      Ipp32f* pDst, int dstStep, IppiSize roiSize, Ipp32f borderValue,
      IppFilterGaussianSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterGaussianBorder_16u_C1R,(const Ipp16u * pSrc, int srcStep,
      Ipp16u * pDst, int dstStep, IppiSize roiSize, Ipp16u borderValue,
      IppFilterGaussianSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterGaussianBorder_16s_C1R,(const Ipp16s* pSrc, int srcStep,
      Ipp16s* pDst, int dstStep, IppiSize roiSize, Ipp16s borderValue,
      IppFilterGaussianSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterGaussianBorder_8u_C1R,(const Ipp8u* pSrc, int srcStep,
      Ipp8u* pDst, int dstStep, IppiSize roiSize, Ipp8u borderValue,
      IppFilterGaussianSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterGaussianBorder_32f_C3R,(const Ipp32f* pSrc, int srcStep,
      Ipp32f* pDst, int dstStep, IppiSize roiSize, Ipp32f borderValue[3],
      IppFilterGaussianSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterGaussianBorder_16u_C3R,(const Ipp16u * pSrc, int srcStep,
      Ipp16u * pDst, int dstStep, IppiSize roiSize, Ipp16u borderValue[3],
      IppFilterGaussianSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterGaussianBorder_16s_C3R,(const Ipp16s* pSrc, int srcStep,
      Ipp16s* pDst, int dstStep, IppiSize roiSize, Ipp16s borderValue[3],
      IppFilterGaussianSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterGaussianBorder_8u_C3R,(const Ipp8u* pSrc, int srcStep,
      Ipp8u* pDst, int dstStep, IppiSize roiSize, Ipp8u borderValue[3],
      IppFilterGaussianSpec* pSpec, Ipp8u* pBuffer))

/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFindPeaks3x3GetBufferSize
//
//  Purpose:    Computes the size of the working buffer for the peak search
//
//  Return:
//     ippStsNoErr      Ok. Any other value indicates an error or a warning.
//     ippStsNullPtrErr Indicates an error condition if the pointer pBufferSize is NULL.
//     ippStsSizeErr    Indicates an error condition if maskSize has a field with zero
//                      or negative value, or if roiWidth is less than 1.
//
//  Arguments:
//     roiWidth         Maximal image width (in pixels).
//     pBufferSize      Pointer to the computed size of the buffer.
*/

IPPAPI(IppStatus, ippiFindPeaks3x3GetBufferSize_32f_C1R,(int roiWidth, int* pBufferSize))

IPPAPI(IppStatus, ippiFindPeaks3x3GetBufferSize_32s_C1R,(int roiWidth, int* pBufferSize))

/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:       ippiFindPeaks3x3
//
//  Purpose:    Finds coordinates of peaks (maximums or minimums) with absolute value
//              exceeding threshold value
//
//  Return:
//     ippStsNoErr      Ok. Any other value indicates an error or a warning.
//     ippStsNullPtrErr One of the specified pointers is NULL.
//     ippStsSizeErr    Indicates an error condition if roiSize has a field
//                      with zero or negative value or if maxPeakCount is less
//                      than or equal to zero, or if Border is less than 1 or
//                      greater than 0.5* roiSize.width or. greater than 0.5* roiSize.hight
//     ippStsStepErr    Indicates an error condition if srcStep is less than roiSize.width * <pixelSize>
//     ippStsNotEvenStepErr Indicates an error condition if one of the step values is
//                      not divisible by 4 for floating-point or 32-bit integer images.
//     ippStsBadArgErr  Indicates an error condition if norm value is wrong.
//
//  Arguments:
//     pSrc             Pointer to the source image ROI.
//     srcStep          Distance in bytes between starts of consecutive lines in the source image.
//     roiSize          Size of the image ROI in pixels.
//     threshold        Threshold value.
//     pPeak            Pointer to the maximum coordinates [maxPeakCount].
//     maxPeakCount     Maximal number of peaks.
//     pPeakCount       Number of detected peaks.
//     norm             Type of norm to form the mask for maximum search:
//                      ippiNormInf Infinity norm (8-connectivity, 3x3 rectangular mask).
//                      ippiNormL1 L1 norm (4-connectivity, 3x3 cross mask).
//     Border           Border value, only pixel with distance from the edge of the image
//                      greater than Border are processed.
//     pBuffer          Pointer to the working buffer.
*/

IPPAPI(IppStatus, ippiFindPeaks3x3_32f_C1R,(const Ipp32f* pSrc, int srcStep, IppiSize roiSize,
                                   Ipp32f threshold, IppiPoint* pPeak, int maxPeakCount,
                                   int* pPeakCount, IppiNorm norm, int Border, Ipp8u* pBuffer))


IPPAPI(IppStatus, ippiFindPeaks3x3_32s_C1R,(const Ipp32s* pSrc, int srcStep, IppiSize roiSize,
                                   Ipp32s threshold, IppiPoint* pPeak, int maxPeakCount,
                                   int* pPeakCount, IppiNorm norm, int Border, Ipp8u* pBuffer))

/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:      ippiHoughLineGetSize_8u_C1R()
//
//
//  Purpose:   Calculate the size of temporary buffer for ippiHoughLine_8u32f_C1R function.
//
//  Arguments:
//    roiSize                  The size of source ROI.
//    delta                    Discretization step, delta.rho - distance resolution in pixels, delta.theta - angle resolution in radians
//    maxLineCount             The size of detected line buffer
//    pBufSize                 Pointer to the computed size of the temporary buffer
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         pBufSize is NULL
//    ippStsSizeErr            The roiSize or delta has a field with zero or negative value
//    ippStsOverflow           The size of buffer too big. Overflow.
//
*/

IPPAPI(IppStatus, ippiHoughLineGetSize_8u_C1R, (IppiSize roiSize, IppPointPolar delta, int maxLineCount, int* pBufSize))

/* ///////////////////////////////////////////////////////////////////////////////////////
//  Name:      ippiHoughLine_8u32f_C1R()
//
//
//  Purpose:   Perform Hough transform algorithm
//
//
//  Arguments:
//    pSrc                     Pointer to the source image ROI
//    srcStep                  Distance in bytes between starts of consecutive lines in the source image
//    roiSize                  The size of source ROI.
//    delta                    Discretization step, delta.rho - distance resolution in pixels, delta.theta - angle resolution in radians
//    threshold                Threshold for a line is detected (if accumulator value > threshold)
//    pLine                    Pointer to output array of detected lines
//    maxLineCount             Size of output array pLine in elements
//    pLineCount               Number of detected lines.  If founded more than maxLineCount lines than function returns "ippStsDstSizeLessExpected" status
//    pBuffer                  Pointer to the pre-allocated temporary buffer
//
//  Return:
//    ippStsNoErr               Ok
//    ippStsNullPtrErr          pSrc or pLine or pLineCount or pBuffer is NULL
//    ippStsStepErr             srcStep is not valid
//    ippStsSizeErr             roiSize has a field with zero or negative value or maxLineCount is zero or negative
//    ippStsBadArgErr           threshold or is less than or equal to zero or delta.rho less 0 or more ROI width+height or delta.theta less 0 or more PI
//    ippStsDstSizeLessExpected Ok, but lines detected more than maxLineCount
//
*/

IPPAPI(IppStatus, ippiHoughLine_8u32f_C1R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize, IppPointPolar delta, int threshold,
       IppPointPolar* pLine, int maxLineCount, int* pLineCount, Ipp8u* pBuffer))

/*
//  Name:      ippiHoughLine_Region_8u32f_C1R
//
//
//  Purpose:   Perform Hough transform algorithm in defined region
//
//
//  Arguments:
//    pSrc                     Pointer to the source image ROI
//    srcStep                  Distance in bytes between starts of consecutive lines in the source image
//    roiSize                  The size of source ROI.
//    pLine                    Pointer to output array of detected lines
//    dstRoi                   Bottom left and top right corners of searched lines. All founded lines must be
//                             in this area. (line[n].rho>=dstRoi[0].rho && line[n].theta>=dstRoi[0].theta &&
//                                            line[n].rho<=dstRoi[1].rho && line[n].theta<=dstRoi[1].theta)
//    maxLineCount             Size of output array pLine in elements
//    pLineCount               Number of detected lines.  If founded more than maxLineCount lines than function returns "ippStsDstSizeLessExpected" status
//    delta                    Discretization step, delta.rho - distance resolution in pixels, delta.theta - angle resolution in radians
//    threshold                Threshold for a line is detected (if accumulator value > threshold)
//    pBuffer                  Pointer to the pre-allocated temporary buffer
//
//  Return:
//    ippStsNoErr               Ok
//    ippStsNullPtrErr          pSrc or pLine or pLineCount or pBuffer is NULL
//    ippStsStepErr             srcStep is not valid
//    ippStsSizeErr             roiSize has a field with zero or negative value or maxLineCount is zero or negative
//    ippStsBadArgErr           threshold or is less than or equal to zero or delta.rho less 0 or more ROI width+height or
//                              delta.theta less 0 or more PI or dstRoi[0].rho more dstRoi[1].rho or dstRoi[0].theta more dstRoi[1].theta
//    ippStsDstSizeLessExpected Ok, but lines detected more than maxLineCount
//
*/

IPPAPI(IppStatus, ippiHoughLine_Region_8u32f_C1R, (const Ipp8u* pSrc, int srcStep, IppiSize roiSize,
       IppPointPolar* pLine, IppPointPolar dstRoi[2], int maxLineCount, int* pLineCount, IppPointPolar delta, int threshold, Ipp8u* pBuffer))



IPPAPI(IppStatus, ippiHoughProbLineGetSize_8u_C1R, (
      IppiSize      roiSize,
      IppPointPolar delta,
      int*          pSpecSize,
      int*          pBufSize))

IPPAPI(IppStatus, ippiHoughProbLineInit_8u32f_C1R,(
       IppiSize       roiSize,
       IppPointPolar  delta,
       IppHintAlgorithm hint,
       IppiHoughProbSpec*  pSpec))

IPPAPI(IppStatus, ippiHoughProbLine_8u32f_C1R,(
  const Ipp8u*         pSrc,
        int            srcStep,
        IppiSize       roiSize,
        int            threshold,
        int            lineLength,
        int            lineGap,
        IppiPoint*     pLine,
        int            maxLineCount,
        int*           pLineCount,
        Ipp8u*         pBuffer,
        const IppiHoughProbSpec* pSpec
  ))

/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name:    ippiCannyBorder_8u_C1R
//  Purpose: Perform convolution operation with fixed kernels 3x3 and 5x5 and creates binary image of source's image edges,
//                using derivatives of the first order.
//  Parameters:
//    pSrc                     The pointer to the source image
//    srcStep                  The step in the source image
//    pDst                     The pointer to the destination image
//    dstStep                  The step in the destination image
//    roiSize                  The image ROI size
//    filterType               the filter type(ippFilterSobel,ippFilterScharr)
//    mask                     The mask size(ippMskSize3x3,ippMskSize5x5)
//    borderType               Type of border. Possible values are:
//                     ippBorderConst Values of all border pixels are set to constant.
//                     ippBorderRepl Border is replicated from the edge pixels.
//                     ippBorderInMem Border is obtained from the source image pixels in memory.
//                     Mixed borders are also supported. They can be obtained by the bitwise operation OR between ippBorderRepl and ippBorderInMemTop, ippBorderInMemBottom, ippBorderInMemLeft, ippBorderInMemRight.
//    borderValue              The value for the constant border
//    lowThresh                Low threshold for edges detection
//    highThresh               Upper threshold for edges detection
//    norm                     Norm type (ippNormL1,ippNormL2)
//    pBuffer                  Pointer to the pre-allocated temporary buffer, which size can be
//                             calculated using ippiCannyEdgeDetectionGetSize function
//  Return:
//    ippStsNoErr              Ok
//    ippStsMaskSizeErr        Indicates an error when mask has an illegal value.
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsNotEvenStepErr     Step is not multiple of element.
//    ippStsBadArgErr          Bad thresholds
//
//F*/

IPPAPI(IppStatus, ippiCannyBorder_8u_C1R,( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize,
                            IppiDifferentialKernel filterType, IppiMaskSize mask,IppiBorderType borderType, Ipp8u borderValue,
                            Ipp32f lowThresh, Ipp32f highThresh, IppNormType norm,Ipp8u* pBuffer ))
/*F///////////////////////////////////////////////////////////////////////////////////////
//  Name:    ippiCannyBorderGetSize
//
//  Purpose: Calculates size of temporary buffer, required to run ippiCannyBorder_8u_C1R function.
//  Parameters:
//    roiSize           Size of image ROI in pixel
//    filterType        The filter type(ippFilterSobel,ippFilterScharr)
//    mask              The mask size(ippMskSize3x3,ippMskSize5x5)
//    dataType          Data type of the image. Possible values are Ipp8u, Ipp16u, Ipp16s, or Ipp32f.
//    pBufferSize       Pointer to the variable that returns the size of the temporary buffer
//
//  Return:
//    ippStsNoErr       Ok
//    ippStsNullPtrErr  Pointer bufferSize is NULL
//    ippStsMaskSizeErr Indicates an error when mask has an illegal value.
//    ippStsDataTypeErr Indicates an error when dataType has an illegal value.
//    ippStsSizeErr     roiSize has a field with zero or negative value
//
//F*/
IPPAPI(IppStatus, ippiCannyBorderGetSize,( IppiSize roiSize, IppiDifferentialKernel filterType,IppiMaskSize mask, IppDataType dataType, int* pBufferSize ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiHarrisCornerGetBufferSize
//
//  Purpose:            Computes the size of the external buffer for ippiHarrisCorner function
//
//  Parameters:
//   roiSize            Size of the source and destination ROI in pixels.
//   filterMask         Linear size of derivative filter aperture.
//   avgWndSize         Neighborhood block size for smoothing
//   dataType           Data type of the source image.
//   numChannels        Number of channels in the images. Possible values is 1.
//   pBufferSize        Pointer to the size (in bytes) of the external work buffer.
//
//  Return Values:
//   ippStsNoErr          Indicates no error.
//   ippStsNullPtrErr     Indicates an error when pBufferSize is NULL.
//   ippStsSizeErr        Indicates an error in the two cases:
//                          if roiSize is negative, or equal to zero;
//                          if avgWndSize is equal to zero.
//   ippStsFilterTypeErr  Indicates an error when filterType has illegal value.
//   ippStsMaskSizeErr    Indicates an error condition if mask has a wrong value.
//   ippStsDataTypeErr    Indicates an error when dataType has an illegal value.
//   ippStsNumChannelsErr Indicates an error when numChannels has an illegal value.
*/
IPPAPI(IppStatus, ippiHarrisCornerGetBufferSize, (IppiSize roiSize, IppiMaskSize filterMask,
                Ipp32u avgWndSize, IppDataType dataType, int numChannels, int* pBufferSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:                 ippiHarrisCorner
//  Purpose:              Performs Harris corner detector operations
//
//  Parameters:
//    pSrc                Pointer to the source image
//    srcStep             Step through the source image
//    pDst                Pointer to the destination image
//    dstStep             Step through the destination image in pixels.
//    roiSize             Size of the source and destination image ROI.
//    filterType          Type of derivative operator
//    filterMask          Predefined mask of IppiMaskSize type.
//    avgWndSize          Size of a rectangle Window for computing an average value
//    k                   Harris Corner free coefficient
//    scale               Destination image scale factor
//    border              Type of the border
//    borderValue         Constant value to assign to pixels of the constant border. if border type equals ippBorderConstant
//    pBuffer             Pointer to the work buffer
//
//  Return Values:
//    ippStsNoErr          Indicates no error.
//    ippStsNullPtrErr     Indicates an error condition if pSrc, pDst or pBufferSize is NULL.
//    ippStsSizeErr        Indicates an error in the two cases:
//                            if roiSize is negative, or equal to zero;
//                            if avgWndSize is equal to zero.
//    ippStsNotEvenStepErr Indicated an error when dstStep is not divisible by 4.
//    ippStsFilterTypeErr  Indicates an error when filterType has illegal value.
//    ippStsMaskSizeErr    Indicates an error condition if mask has an illegal value.
//    ippStsBorderErr      Indicates an error when borderType has illegal value.
//    ippStsStepErr        Indicates an error condition,  if srcStep or dstStep has negative value
//    ippStsInplaceModeNotSupportedErr Indicates an error condition, if the pSrc and pDst points to the same image
*/

IPPAPI(IppStatus, ippiHarrisCorner_8u32f_C1R, (
    const Ipp8u *pSrc, int srcStep, Ipp32f *pDst, int dstStep, IppiSize roiSize,
    IppiDifferentialKernel filterType, IppiMaskSize filterMask, Ipp32u avgWndSize, float k,
    float scale, IppiBorderType borderType, Ipp8u borderValue, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiHarrisCorner_32f_C1R, (
    const Ipp32f *pSrc, int srcStep, Ipp32f *pDst, int dstStep, IppiSize roiSize,
    IppiDifferentialKernel filterType, IppiMaskSize filterMask, Ipp32u avgWndSize, float k,
    float scale, IppiBorderType borderType, Ipp32f borderValue, Ipp8u* pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiLineSuppressionGetBufferSize
//
//  Purpose:            Computes the size of the external buffer for ippiLineSuppression function
//
//  Parameters:
//   roiSize            Size of the source and destination ROI in pixels.
//   filterMask         Linear size of derivative filter aperture.
//   avgWndSize         Neighborhood block size for smoothing
//   dataType           Data type of the source image.
//   numChannels        Number of channels in the images. Possible values is 1.
//   pBufferSize        Pointer to the size (in bytes) of the external work buffer.
//
//  Return Values:
//   ippStsNoErr          Indicates no error.
//   ippStsNullPtrErr     Indicates an error when pBufferSize is NULL.
//   ippStsSizeErr        Indicates an error in the two cases:
//                          if roiSize is negative, or equal to zero;
//                          if avgWndSize is equal to zero.
//   ippStsFilterTypeErr  Indicates an error when filterType has illegal value.
//   ippStsMaskSizeErr    Indicates an error condition if mask has a wrong value.
//   ippStsDataTypeErr    Indicates an error when dataType has an illegal value.
//   ippStsNumChannelsErr Indicates an error when numChannels has an illegal value.
*/
IPPAPI(IppStatus, ippiLineSuppressionGetBufferSize, (IppiSize roiSize, IppiMaskSize filterMask,
                Ipp32u avgWndSize, IppDataType dataType, int numChannels, int* pBufferSize))

/* /////////////////////////////////////////////////////////////////////////////
//
//  Name:                 ippiLineSuppression
//  Purpose:              Performs Line Suppression algorithm
//
//  Parameters:
//    pSrc                Pointer to the source image
//    srcStep             Step through the source image
//    pFeature            Pointer to the feature points image
//    featureStep         Step through the feature points image
//    pDst                Pointer to the destination image
//    dstStep             Step through the destination image in pixels.
//    roiSize             Size of the source and destination image ROI.
//    filterType          Type of derivative operator
//    filterMask          Predefined mask of IppiMaskSize type.
//    avgWndSize          Size of a rectangle Window for computing an average value
//    threshold           Line suppression threshold
//    border              Type of the border
//    borderValue         Constant value to assign to pixels of the constant border. if border type equals ippBorderConstant
//    pBuffer             Pointer to the work buffer
//
//  Return Values:
//    ippStsNoErr          Indicates no error.
//    ippStsNullPtrErr     Indicates an error condition if pSrc, pFeature, pDst or pBufferSize is NULL.
//    ippStsSizeErr        Indicates an error in the two cases:
//                            if roiSize is negative, or equal to zero;
//                            if avgWndSize is equal to zero.
//    ippStsFilterTypeErr  Indicates an error when filterType has illegal value.
//    ippStsMaskSizeErr    Indicates an error condition if mask has an illegal value.
//    ippStsBorderErr      Indicates an error when borderType has illegal value.
//    ippStsStepErr        Indicates an error condition, if srcStep or dstStep has negative value
//    ippStsInplaceModeNotSupportedErr Indicates an error condition if the pFeature and pDst points to the same image
*/

IPPAPI(IppStatus, ippiLineSuppression_8u_C1R, (
    const Ipp8u *pSrc, int srcStep, const Ipp8u * pFeature, int featureStep,
    Ipp8u *pDst, int dstStep, IppiSize roiSize, IppiDifferentialKernel filterType,
    IppiMaskSize filterMask, Ipp32u avgWndSize, float threshold,
    IppiBorderType borderType, Ipp8u borderValue, Ipp8u* pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiMarkSpecklesGetBufferSize
//
//  Purpose:            Computes the size of the external buffer for ippiFilterSpeckle function
//
//  Parameters:
//   dstRoiSize         Size of destination ROI in pixels.
//   dataType           Data type of the source and destination images.
//   numChannels        Number of channels in the images. Possible value is 1.
//   pBufferSize        Pointer to the size (in bytes) of the external work buffer.
//
//  Return Values:
//   ippStsNoErr        Indicates no error.
//   ippStsNullPtrErr   Indicates an error when pBufferSize is NULL.
//   ippStsSizeErr      Indicates an error when roiSize is negative, or equal to zero.
//   ippStsDataTypeErr  Indicates an error when dataType has an illegal value.
//   ippStsNumChannelsErr Indicates an error when numChannels has an illegal value.
*/

IPPAPI(IppStatus, ippiMarkSpecklesGetBufferSize, (IppiSize roiSize,
    IppDataType dataType, int numChannels, int* pBufferSize))

/* /////////////////////////////////////////////////////////////////////////////
//
//  Name:                ippiMarkSpeckles
//  Purpose:             Performs filtering of small noise blobs (speckles)
//                       in the image
//
//  Parameters:
//    pSrcDst            Pointer to the source and destination image
//    srcDstStep         Step through the source and destination image
//    roiSize            Size of the source and destination image ROI.
//    speckleVal         The disparity value used to paint-off the speckles
//    maxSpeckleSize     The maximum speckle size to consider it a speckle.
//    maxPixDiff         Maximum difference between neighbor pixels to put them into the same blob.
//    norm               Specifies type of the norm to form the mask for marker propagation:
//                          ippiNormInf Infinity norm (8-connectivity);
//                          ippiNormL1  L1 norm (4-connectivity).
//    pBuffer            Pointer to the work buffer
//
//  Return Values:
//    ippStsNoErr        Indicates no error.
//    ippStsNullPtrErr   Indicates an error condition if pSrc, pDst or pBufferSize is NULL.
//    ippStsSizeErr      Indicates an error when roiSize is negative, or equal to zero.
//    ippStsNotEvenStepErr Indicated an error when one of the step values is not divisible by 4
//                       for floating-point images, or by 2 for short-integer images.
//    ippStsNormErr      Indicates an error when norm is incorrect or not supported
*/

IPPAPI(IppStatus, ippiMarkSpeckles_8u_C1IR, (Ipp8u *pSrcDst, int srcDstStep, IppiSize roiSize,
    Ipp8u speckleVal, int maxSpeckleSize, Ipp8u maxPixDiff, IppiNorm norm, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiMarkSpeckles_16u_C1IR, (Ipp16u *pSrcDst, int srcDstStep, IppiSize roiSize,
    Ipp16u speckleVal, int maxSpeckleSize, Ipp16u maxPixDiff, IppiNorm norm, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiMarkSpeckles_16s_C1IR, (Ipp16s *pSrcDst, int srcDstStep, IppiSize roiSize,
    Ipp16s speckleVal, int maxSpeckleSize, Ipp16s maxPixDiff, IppiNorm norm, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiMarkSpeckles_32f_C1IR, (Ipp32f *pSrcDst, int srcDstStep, IppiSize roiSize,
    Ipp32f speckleVal, int maxSpeckleSize, Ipp32f maxPixDiff, IppiNorm norm, Ipp8u* pBuffer))


/*************************** FastN ***********************************************/

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiFastNGetSize
//  Purpose:            initialization of Spec for FastN
//
//  Parameters:
//    srcSize           Roi size (in pixels) of source image what will be applied
//                      for processing
//    circleRadius      Radius for corner finding. Possible values are 1, 3, 5, 7, 9.
//    N                 Critical number of pixels that have different value.
//    orientationBins   The number bins for defining dirrection
//    option            defines the moded of processing
//    dataType          Data type of the source images. Possible value is Ipp8u.
//    nChannels         Number of channels in the images. Possible value is 1.
//    pSpecSize         Pointer to the size (in bytes) of the spec.
//  Return:
//    ippStsNoErr               OK
//    ippStsNullPtrErr          pointer to pSpecSize is NULL
//    ippStsSizeErr             size of srcSize is less or equal 0
//    ippStsDataTypeErr         Indicates an error when dataType has an illegal value.
//    ippStsNumChannelsErr      Indicates an error when numChannels has an illegal value.
//    ippStsOutOfRangeErr       Indicates an error when orientation Bins or N have an illegal value.
//    ippStsBadArgErr           Indicates an error when option or circleRadius have an illegal value.
*/
IPPAPI(IppStatus,ippiFastNGetSize,(IppiSize srcSize, int circleRadius, int N, int orientationBins,
    int option, IppDataType dataType, int nChannels, int *pSpecSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiFastNInit
//  Purpose:            to define spec size for FastN
//
//  Parameters:
//    srcSize           Roi size (in pixels) of source image what will be applied
//                      for processing
//    circleRadius      Radius for corner finding. Possible values are 1, 3, 5, 7, 9.
//    N                 Critical number of pixels that have different value.
//    orientationBins   The number bins for defining dirrection
//    option            defines the moded of processing
//    threshold         the level for definition of critical pixels
//    dataType          Data type of the source images. Possible value is Ipp8u.
//    nChannels         Number of channels in the images. Possible value is 1.
//    pSpec             pointer to Spec
//  Return:
//    ippStsNoErr               OK
//    ippStsNullPtrErr          pointer to pSpecSize is NULL
//    ippStsSizeErr             size of srcSize is less or equal 0
//    ippStsDataTypeErr         Indicates an error when dataType has an illegal value.
//    ippStsNumChannelsErr      Indicates an error when numChannels has an illegal value.
//    ippStsOutOfRangeErr       Indicates an error when orientation Bins or N have an illegal value.
//    ippStsBadArgErr           Indicates an error when option or circleRadius have an illegal value.
//    ippStsThresholdErr        threshold ia less 0
*/
IPPAPI(IppStatus,ippiFastNInit,(IppiSize srcSize, int circleRadius, int N, int orientationBins, int option,
       Ipp32f threshold, IppDataType dataType, int nChannels, IppiFastNSpec *pSpec))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiFastNGetBufferSize
//  Purpose:            to define size of working buffer for FastN
//
//  Parameters:
//    pSpec             pointer to Spec
//    dstRoiSiz         Roi size (in pixels) of destination image what will be applied
//                      for processing
//    pBufSize          Pointer to the size (in bytes) of the working buffer.
*/
IPPAPI(IppStatus,ippiFastNGetBufferSize,(IppiFastNSpec *pSpec, IppiSize dstRoiSize, int *pBufSize))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiFastN_8u_C1R
//  Purpose:            corner finding FastN
//
//  Parameters:
//    pSrc              Pointer to the source image
//    srcStep           Step through the source image
//    pDstCorner        Pointer to the destinartion corner image
//    dstCornerStep     Step through the destinartion corner image
//    pDstScore         Pointer to the destinartion score image
//    dstScoreStep      Step through the destinartion score image
//    pNumCorner        pointer to number of corners in source image
//    srcRoiOffset      offset in source image
//    dstRoiSize        Roi size (in pixels) of destination image what will be applied
//                      for processing
//    pSpec             pointer to Spec
//    pBuffer           pointer to working buffer
//  Return:
//    ippStsNoErr               OK
//    ippStsNullPtrErr          pointer to Src, DstCorner, Spec or Buffer is NULL
//    ippStsSizeErr             sizes of srcSize or dstRoiSize are less or equal 0
//    ippStsContextMatchErr     spec is not match
//    ippStsDataTypeErr         Indicates an error when dataType has an illegal value.
//    ippStsNumChannelsErr      Indicates an error when numChannels has an illegal value.
//    ippStsOutOfRangeErr       Indicates an error when orientation Bins or N have an illegal value.
//    ippStsBadArgErr           Indicates an error when option or circleRadius have an illegal value.
//    ippStsThresholdErr        threshold ia less 0
*/
IPPAPI(IppStatus,ippiFastN_8u_C1R,(const Ipp8u *pSrc, int srcStep, Ipp8u *pDstCorner, int dstCornerStep,
    Ipp8u *pDstScore, int dstScoreStep, int *pNumCorner, IppiPoint srcRoiOffset, IppiSize dstRoiSize,
    IppiFastNSpec *pSpec, Ipp8u *pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippiFastN_8u_C1R
//  Purpose:            corner finding FastN
//
//  Parameters:
//    pSrcCorner        Pointer to the source corner image
//    srcCornerStep     Step through the source corner image
//    pSrcScore         Pointer to the source score image
//    srcScoreStep      Step through the source score image
//    pDst              pointer to array of structures
//    SrcRoiSize        Roi size (in pixels) of source images what will be applied
//    maxLen            length of array of structures
//    pNumCorners       pointer to number of corners
//    pSpec             pointer to Spec
//  Return:
//    ippStsNoErr               OK
//    ippStsNullPtrErr          pointer to pSrcCorner, pSrcScore, pDst or Spec is NULL
//    ippStsSizeErr             sizes of srcSize or dstRoiSize are less or equal 0
//    ippStsContextMatchErr     spec is not match
//    ippStsDataTypeErr         Indicates an error when dataType has an illegal value.
//    ippStsNumChannelsErr      Indicates an error when numChannels has an illegal value.
//    ippStsOutOfRangeErr       Indicates an error when orientation Bins or N have an illegal value.
//    ippStsBadArgErr           Indicates an error when option or circleRadius have an illegal value.
//    ippStsThresholdErr        threshold ia less 0
*/
IPPAPI(IppStatus,ippiFastN2DToVec_8u,(const Ipp8u *pSrcCorner, int srcCornerStep,  const Ipp8u *pSrcScore,
    int srcScoreStep, IppiCornerFastN *pDst, IppiSize srcRoiSize, int maxLen, int *pNumCorners,
    IppiFastNSpec *pSpec))

IPPAPI (IppStatus, ippiFGMMGetBufferSize_8u_C3R, (IppiSize roi, int maxNGauss, int* pSpecSize))
IPPAPI (IppStatus, ippiFGMMInit_8u_C3R         , (IppiSize roi, int maxNGauss, IppFGMModel* pModel,                        IppFGMMState_8u_C3R* pState))
IPPAPI (IppStatus, ippiFGMMForeground_8u_C3R   , (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep,  IppiSize roi, IppFGMMState_8u_C3R* pState, IppFGMModel* pModel, double learning_rate))
IPPAPI (IppStatus, ippiFGMMBackground_8u_C3R   , (                                Ipp8u* pDst, int dstStep,  IppiSize roi, IppFGMMState_8u_C3R* pState))

/****************************************************************************************\
*                                   Separable Filters                                    *
\****************************************************************************************/


/*///////////////////////////////////////////////////////////////////////////////////////////
//  Name:      ippiFilterSeparableGetBufferSize,
//             ippiFilterSeparableGetSpecSize
//             ippiFilterSeparable_8u_C1R,      ippiFilterSeparable_8u_C3R,      ippiFilterSeparable_8u_C4R
//             ippiFilterSeparable_8u16s_C1R,   ippiFilterSeparable_8u16s_C3R,   ippiFilterSeparable_8u16s_C4R
//             ippiFilterSeparable_16s_C1R,     ippiFilterSeparable_16s_C3R,     ippiFilterSeparable_16s_C4R
//             ippiFilterSeparable_16u_C1R,     ippiFilterSeparable_16u_C3R,     ippiFilterSeparable_16u_C4R
//             ippiFilterSeparable_32f_C1R,     ippiFilterSeparable_32f_C3R,     ippiFilterSeparable_32f_C4R
//  Purpose:   Convolves source image rows and columns with the row and column kernels
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         One of pointers is NULL
//    ippStsSizeErr            The width or height of images is less or equal zero
//    ippStsStepErr            The steps in images are too small
//    ippStsNotEvenStepErr     Step is not multiple of element.
//    ippStsBadArgErr          Zero divisor
//
//  Parameters:
//    pSrc                     The pointer to the source image
//    pDst                     The pointer to the destination image
//    srcStep                  The step in the source image
//    dstStep                  The step in the destination image
//    roiSize                  The image ROI size
//    borderType               Type of the border
//    borderValue              Pointer to the constant value(s) if border type equals ippBorderConstant
//    pSpec                    Pointer to the allocated and initialized context structure
//    pBuffer                  The pointer to the working buffer
//    kernelSize               Sizes of row and column kernels
//    dataType                 Data type of source image {ipp8u|ipp16s|ipp16u|ipp32f}
//    kernelType               Kernel type {ipp16s|ipp32f}
//    numChannels              Number of channels, possible values are 1, 3 or 4
//    pBufferSize              Pointer to the size (in bytes) of the external buffer
//    pSpecSize                Pointer to the size (in bytes) of the spec structure
//    pRowKernel               Pointer to row kernel
//    pColumnKernel            Pointer to column kernel
//    divisor                  The integer value by which the computed result is divided
//    scaleFactor              The integer value by which the computed result is scaled
*/

IPPAPI(IppStatus, ippiFilterSeparableGetBufferSize, (IppiSize roiSize, IppiSize kernelSize, IppDataType dataType, IppDataType kernelType, int numChannels, int* pBufferSize))
IPPAPI(IppStatus, ippiFilterSeparableGetSpecSize, (IppiSize kernelSize, IppDataType dataType, int numChannels, int* pSpecSize))

IPPAPI(IppStatus, ippiFilterSeparableInit_16s, (const Ipp16s* pRowKernel, const Ipp16s* pColumnKernel, IppiSize kernelSize, int divisor, int scaleFactor, IppDataType dataType,
    int numChannels, IppiFilterSeparableSpec* pSpec))
IPPAPI(IppStatus, ippiFilterSeparableInit_32f, (const Ipp32f* pRowKernel, const Ipp32f* pColumnKernel, IppiSize kernelSize, IppDataType dataType,
    int numChannels, IppiFilterSeparableSpec* pSpec))

IPPAPI(IppStatus, ippiFilterSeparable_8u_C1R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize,
    IppiBorderType borderType, Ipp8u borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_8u_C3R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize,
    IppiBorderType borderType, Ipp8u* borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_8u_C4R, (const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int dstStep, IppiSize roiSize,
    IppiBorderType borderType, Ipp8u* borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterSeparable_8u16s_C1R, (const Ipp8u* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize,
    IppiBorderType borderType, Ipp8u borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_8u16s_C3R, (const Ipp8u* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize,
    IppiBorderType borderType, Ipp8u* borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_8u16s_C4R, (const Ipp8u* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize,
    IppiBorderType borderType, Ipp8u* borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterSeparable_16s_C1R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize,
    IppiBorderType borderType, Ipp16s borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_16s_C3R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize,
    IppiBorderType borderType, Ipp16s* borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_16s_C4R, (const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int dstStep, IppiSize roiSize,
    IppiBorderType borderType, Ipp16s* borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterSeparable_16u_C1R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize,
    IppiBorderType borderType, Ipp16u borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_16u_C3R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize,
    IppiBorderType borderType, Ipp16u* borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_16u_C4R, (const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, int dstStep, IppiSize roiSize,
    IppiBorderType borderType, Ipp16u* borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))

IPPAPI(IppStatus, ippiFilterSeparable_32f_C1R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize,
    IppiBorderType borderType, Ipp32f borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_32f_C3R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize,
    IppiBorderType borderType, Ipp32f* borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippiFilterSeparable_32f_C4R, (const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int dstStep, IppiSize roiSize,
    IppiBorderType borderType, Ipp32f* borderValue, const IppiFilterSeparableSpec* pSpec, Ipp8u* pBuffer))

#if defined __cplusplus
}
#endif

#endif /* IPPCV_H__ */
