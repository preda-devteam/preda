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
//              Derivative Types and Macro Definitions
//
//              The main purpose of this header file is
//              to support compatibility with the legacy
//              domains until their end of life.
//
*/


#if !defined( IPPTYPES_L_H__ )
#define IPPTYPES_L_H__

#if !defined( _OWN_BLDPCS )

#ifdef __cplusplus
extern "C" {
#endif

#if defined (_M_AMD64) || defined (__x86_64__)
  typedef Ipp64s IppSizeL;
#else
  typedef int IppSizeL;
#endif

/*****************************************************************************/
/*                   Below are ippIP domain specific definitions             */
/*****************************************************************************/

typedef struct {
    IppSizeL x;
    IppSizeL y;
    IppSizeL width;
    IppSizeL height;
} IppiRectL;

typedef struct {
    IppSizeL x;
    IppSizeL y;
} IppiPointL;

typedef struct {
    IppSizeL width;
    IppSizeL height;
} IppiSizeL;

typedef struct {
    IppSizeL width;
    IppSizeL height;
    IppSizeL depth;
} IpprVolumeL;

typedef struct {
    IppSizeL x;
    IppSizeL y;
    IppSizeL z;
} IpprPointL;

typedef enum _IpprBorderType {
    ipprBorderRepl        = ippBorderRepl,
    ipprBorderConst       = ippBorderConst,

    /* Flags to use source image memory pixels from outside of the border in particular directions */
    ipprBorderInMemTop     =  0x0010,
    ipprBorderInMemBottom  =  0x0020,
    ipprBorderInMemLeft    =  0x0040,
    ipprBorderInMemRight   =  0x0080,
    ipprBorderInMemFront   =  0x1000,
    ipprBorderInMemBack    =  0x2000,

    ipprBorderInMem        =  ipprBorderInMemLeft|ipprBorderInMemTop|ipprBorderInMemRight|ipprBorderInMemBottom|ipprBorderInMemFront|ipprBorderInMemBack,
} IpprBorderType;


typedef enum {
    IPP_MORPH_DEFAULT          = 0x0000, /* Default, flip before second opation(erode,dilate), threshold above zero in Black/TopHat */
    IPP_MORPH_MASK_NO_FLIP     = 0x0001, /* Never flip mask */
    IPP_MORPH_NO_THRESHOLD     = 0x0004  /* No threshold in Black/TopHat */
} IppiMorphMode;


typedef struct ResizeSpec IppiResizeSpec;

/* threading wrappers types */
typedef struct FilterBilateralType_T   IppiFilterBilateralSpec_T;
typedef struct FilterBilateralType_LT  IppiFilterBilateralSpec_LT;
typedef struct ResizeSpec_LT           IppiResizeSpec_LT;
typedef struct FilterSobelType_T       IppiFilterSobelSpec_T;
typedef struct FilterBorderSpecV       IpprFilterBorderSpec;
typedef struct FilterMedianSpecV       IpprFilterMedianSpec;
typedef struct IpprFilterBorderType_T  IpprFilterBorderSpec_T;
typedef struct IpprFilterBorderType_LT IpprFilterBorderSpec_LT;
typedef struct IpprFilterMedianType_T  IpprFilterMedianSpec_T;
#ifdef __cplusplus
}
#endif

#endif /* _OWN_BLDPCS */

#endif /* IPPTYPES_L_H__ */
