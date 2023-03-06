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
//              Color Conversion Library (ippCC_L)
//
//
*/


#if !defined( IPPCC_L_H__ ) || defined( _OWN_BLDPCS )
#define IPPCC_L_H__

#ifndef IPPDEFS_L_H__
  #include "ippdefs_l.h"
#endif

#if (defined( IPP_ENABLED_THREADING_LAYER ) || defined( IPP_ENABLED_THREADING_LAYER_REDEFINITIONS ))
    #include "ippcc_tl.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define khdtv0f  0.2126f
#define khdtv1f  0.7152f
#define khdtv2f  0.0722f
#define khdtv3f  0.1146f
#define khdtv4f  0.3854f
#define khdtv5f  0.5000f
#define khdtv6f  0.4542f
#define khdtv7f  0.0458f
#if !defined( _OWN_BLDPCS )
typedef enum {
  ippiBayerBGGR,
  ippiBayerRGGB,
  ippiBayerGBRG,
  ippiBayerGRBG
} IppiBayerGrid;
#endif /* _OWN_BLDPCS */

/* /////////////////////////////////////////////////////////////////////////////
//  Names:        ippiCFAToBGRA_VNG_8u_C1C4R_L
//                ippiCFAToBGRA_VNG_16u_C1C4R_L
//
//  Purpose:      Bayer transform. Converts color filter array image to RGB image using Variable Numbers of Gradients algorithm
//  Returns:
//    ippStsNoErr         No errors
//    ippStsNullPtrErr    One of the pointers is NULL
//    ippStsBadArgErr     Wrong value of grid
//    ippStsSizeErr       The srcSize.width<2 or the srcSize.height<2 or
//                        the roiSize has a field with negative or zero value
//  Parameters:
//    pSrc                Pointers to the source image
//    srcRoiL              ROI in source image(top left corner and size)
//    srcSizeL             Size of source image
//    srcStepL             Steps through the source image
//    scale               Color scale coefficients by channels
//    pDst                Pointer to the destination image
//    dstStepL             Step through the destination image
//    grid                Type of baeyers grid
//
*/

IPPAPI(IppStatus, ippiCFAToBGRA_VNG_8u_C1C4R_L, (const Ipp8u*  pSrc, IppiRectL srcRoiL, IppiSizeL srcSizeL, IppSizeL srcStepL, Ipp32f scale[4], Ipp8u* pDst, IppSizeL dstStepL, IppiBayerGrid grid))
IPPAPI(IppStatus, ippiCFAToBGRA_VNG_16u_C1C4R_L, (const Ipp16u*  pSrc, IppiRectL srcRoiL, IppiSizeL srcSizeL, IppSizeL srcStepL, Ipp32f scale[4], Ipp16u* pDst, IppSizeL dstStepL, IppiBayerGrid grid))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippiRGbToLab_32f_P3R_L
//              ippiRGbToLab_64f_P3R_L
//  Purpose:    Converts an RGB image to CIE Lab color model and vice-versa
//  Parameters:
//    pSrc          Pointer to the source image ROI
//    srcStep       Step through the source  image (bytes)
//    pDst          Pointer to the destination image ROI
//    dstStep       Step through the destination image (bytes)
//    roiSize       Size of the ROI
//  Returns:
//     ippStsNullPtrErr  if src == NULL or dst == NULL
//     ippStsSizeErr     if imgSize.width <= 0 || imgSize.height <= 0
//     ippStsNoErr       otherwise
//  Reference:
//     Computer graphics: principles and practices. James D. Foley... [et al.]. 2nd ed.
//     Addison-Wesley, c1990.p.(584)
//
//    At first an RGB image is converted to the XYZ color model (see the function
//    ippRGBToXYZ_8u_C3R), then to the CIELab with the white point D65 and CIE chromaticity
//    coordinates of white point (xn,yn) = (0.312713, 0.329016)
//    L = 116. *((Y/Yn)^(1/3)) - 16    for Y/Yn >  0.008856
//    L = 903.3*(Y/Yn)                 for Y/Yn <= 0.008856
//    a = 500. * (f(X/Xn) - f(Y/Yn))
//    b = 200. * (f(Y/Yn) - f(Z/Zn))
//    where f(t)=t^(1/3)               for t >  0.008856
//    f(t)=7.787*t+16/116              for t <= 0.008856
//    These values are quantized and scaled to the 8-bit range of 0 to 255 for ippiBGRToLab_8u_C3R.
//    L =   L * 255. / 100.
//    a = (a + 128.)
//    b = (a + 128.)
//    and they are quantized and scaled to the 16-bit range of 0 to 65535 for ippiBGRToLab_8u16u_C3R
//    L =  L * 65535. / 100.
//    a = (a + 128.)* 255
//    b = (a + 128.)* 255
//    where:
//      normalizing multipliers
//    Yn = 1.0      * 255
//    Xn = 0.950455 * 255
//    Zn = 1.088753 * 255
//
//    L component values are in the range [0..100], a and b component values are
//    in the range [-128..127].
//
//    The CIELab to RGB conversion is performed as follows. At first
//    a Lab image is converted to the XYZ image
//      for ippiLabToBGR_8u_C3R
//    L =  L * 100./ 255.
//    a = (a - 128.)
//    b = (a - 128.)
//      or for ippiLabToBGR_16u8u_C3R
//    L =  L * 100./ 65535.
//    a = (a / 255 - 128.)
//    b = (b / 255 - 128.)
//    X = Xn * ( P + a / 500 )^3
//    Y = Yn * P^3
//    Z = Zn * ( P - b / 200 )^3
//    where P = (L + 16) / 116
//    Then the XYZ image is converted to the RGB color model (see the function
//     ippXYZToRGB_8u_C3R).
//
*/
IPPAPI(IppStatus, ippiRGBToLab_32f_P3R_L, (const Ipp32f* pSrc[3], IppSizeL srcStep[3], Ipp32f* pDst[3], IppSizeL dstStep[3], IppiSizeL roiSize))
IPPAPI(IppStatus, ippiRGBToLab_64f_P3R_L, (const Ipp64f* pSrc[3], IppSizeL srcStep[3], Ipp64f* pDst[3], IppSizeL dstStep[3], IppiSizeL roiSize))
IPPAPI(IppStatus, ippiLabToRGB_32f_P3R_L, (const Ipp32f* pSrc[3], IppSizeL srcStep[3], Ipp32f* pDst[3], IppSizeL dstStep[3], IppiSizeL roiSize))
IPPAPI(IppStatus, ippiLabToRGB_64f_P3R_L, (const Ipp64f* pSrc[3], IppSizeL srcStep[3], Ipp64f* pDst[3], IppSizeL dstStep[3], IppiSizeL roiSize))

#ifdef __cplusplus
}
#endif

#endif /* IPPCC_L_H__ */
