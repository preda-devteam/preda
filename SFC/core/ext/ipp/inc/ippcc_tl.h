/*
// Copyright 2016-2020 Intel Corporation All Rights Reserved.
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
//              Color Conversion (ippCC_TL)
//
//
*/


#if !defined( IPPCC_TL_H__ )
#define IPPCC_TL_H__

#ifndef IPPDEFS_L_H__
  #include "ippdefs_l.h"
#endif

#include "ippcc_l.h"

#if defined( IPP_ENABLED_THREADING_LAYER_REDEFINITIONS )
    #include "ippcc_tl_redefs.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
/* /////////////////////////////////////////////////////////////////////////////
//  Name:   ippiRGBToLab_32f_P3R_LT
//          ippiRGBToLab_64f_P3R_LT
//          ippiLabToRGB_32f_P3R_LT
//          ippiLabToRGB_64f_P3R_LT
//          ippiRGBToLab_32f_P3R_T,
//          ippiRGBToLab_64f_P3R_T,
//          ippiLabToRGB_32f_P3R_T,
//          ippiLabToRGB_64f_P3R_T,
//  Purpose:    Converts an RGB image to CIE Lab color model and vice-versa
//  Parameters:
//    pSrc          Pointer to the source image ROI
//    srcStep       Step through the source  image (bytes)
//    pDst          Pointer to the destination image ROI
//    dstStep       Step through the destination image (bytes)
//    roiSize       Size of the ROI
//  Returns:
//     ippStsNullPtrErr  if src == NULL or dst == NULL or src[0,1,2] == NULL or dst[0,1,2] == NULL
//     ippStsSizeErr     if imgSize.width <= 0 || imgSize.height <= 0
//     ippStsNoErr       otherwise
*/
IPPAPI (IppStatus, ippiRGBToLab_32f_P3R_LT, (const Ipp32f* pSrc[3], IppSizeL srcStep[3], Ipp32f* pDst[3], IppSizeL dstStep[3], IppiSizeL roiSize))
IPPAPI (IppStatus, ippiRGBToLab_64f_P3R_LT, (const Ipp64f* pSrc[3], IppSizeL srcStep[3], Ipp64f* pDst[3], IppSizeL dstStep[3], IppiSizeL roiSize))
IPPAPI (IppStatus, ippiLabToRGB_32f_P3R_LT, (const Ipp32f* pSrc[3], IppSizeL srcStep[3], Ipp32f* pDst[3], IppSizeL dstStep[3], IppiSizeL roiSize))
IPPAPI (IppStatus, ippiLabToRGB_64f_P3R_LT, (const Ipp64f* pSrc[3], IppSizeL srcStep[3], Ipp64f* pDst[3], IppSizeL dstStep[3], IppiSizeL roiSize))
IPPAPI (IppStatus, ippiRGBToLab_32f_P3R_T,  (const Ipp32f* pSrc[3],      int srcStep[3], Ipp32f* pDst[3],      int dstStep[3], IppiSize  roiSize))
IPPAPI (IppStatus, ippiRGBToLab_64f_P3R_T,  (const Ipp64f* pSrc[3],      int srcStep[3], Ipp64f* pDst[3],      int dstStep[3], IppiSize  roiSize))
IPPAPI (IppStatus, ippiLabToRGB_32f_P3R_T,  (const Ipp32f* pSrc[3],      int srcStep[3], Ipp32f* pDst[3],      int dstStep[3], IppiSize  roiSize))
IPPAPI (IppStatus, ippiLabToRGB_64f_P3R_T,  (const Ipp64f* pSrc[3],      int srcStep[3], Ipp64f* pDst[3],      int dstStep[3], IppiSize  roiSize))

#ifdef __cplusplus
}
#endif

#endif /* IPPI_TL_H__ */
