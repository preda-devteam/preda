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
//              Signal Processing (ippSP_L)
//
//
*/
#if !defined( IPPS_L_H__ ) || defined( _OWN_BLDPCS )
#define IPPS_L_H__

#ifndef IPPDEFS_L_H__
  #include "ippdefs_l.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
/* /////////////////////////////////////////////////////////////////////////////
//                   Memory Allocation Functions
///////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsMalloc*_L
//  Purpose:    64-byte aligned memory allocation
//  Parameter:
//    len       number of elements (according to their type)
//  Returns:    pointer to allocated memory
//
//  Notes:      the memory allocated by ippsMalloc has to be free by ippsFree
//              function only.
*/

IPPAPI(Ipp8u*, ippsMalloc_8u_L, (IppSizeL len))
IPPAPI(Ipp16u*, ippsMalloc_16u_L, (IppSizeL len))
IPPAPI(Ipp32u*, ippsMalloc_32u_L, (IppSizeL len))
IPPAPI(Ipp8s*, ippsMalloc_8s_L, (IppSizeL len))
IPPAPI(Ipp16s*, ippsMalloc_16s_L, (IppSizeL len))
IPPAPI(Ipp32s*, ippsMalloc_32s_L, (IppSizeL len))
IPPAPI(Ipp64s*, ippsMalloc_64s_L, (IppSizeL len))
IPPAPI(Ipp32f*, ippsMalloc_32f_L, (IppSizeL len))
IPPAPI(Ipp64f*, ippsMalloc_64f_L, (IppSizeL len))
IPPAPI(Ipp8sc*, ippsMalloc_8sc_L, (IppSizeL len))
IPPAPI(Ipp16sc*, ippsMalloc_16sc_L, (IppSizeL len))
IPPAPI(Ipp32sc*, ippsMalloc_32sc_L, (IppSizeL len))
IPPAPI(Ipp64sc*, ippsMalloc_64sc_L, (IppSizeL len))
IPPAPI(Ipp32fc*, ippsMalloc_32fc_L, (IppSizeL len))
IPPAPI(Ipp64fc*, ippsMalloc_64fc_L, (IppSizeL len))


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
IPPAPI(IppStatus, ippsSortRadixGetBufferSize_L, (IppSizeL len, IppDataType dataType, IppSizeL *pBufferSize))
IPPAPI(IppStatus, ippsSortRadixIndexGetBufferSize_L, (IppSizeL len, IppDataType dataType, IppSizeL *pBufferSize))

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
IPPAPI(IppStatus, ippsSortRadixAscend_32s_I_L, (Ipp32s *pSrcDst, IppSizeL len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixAscend_32f_I_L, (Ipp32f *pSrcDst, IppSizeL len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixAscend_64u_I_L, (Ipp64u *pSrcDst, IppSizeL len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixAscend_64s_I_L, (Ipp64s *pSrcDst, IppSizeL len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixAscend_64f_I_L, (Ipp64f *pSrcDst, IppSizeL len, Ipp8u *pBuffer))

IPPAPI(IppStatus, ippsSortRadixDescend_32s_I_L, (Ipp32s *pSrcDst, IppSizeL len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixDescend_32f_I_L, (Ipp32f *pSrcDst, IppSizeL len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixDescend_64u_I_L, (Ipp64u *pSrcDst, IppSizeL len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixDescend_64s_I_L, (Ipp64s *pSrcDst, IppSizeL len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixDescend_64f_I_L, (Ipp64f *pSrcDst, IppSizeL len, Ipp8u *pBuffer))


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
IPPAPI(IppStatus, ippsSortRadixIndexAscend_64s_L, (const Ipp64s* pSrc, IppSizeL srcStrideBytes, IppSizeL *pDstIndx, IppSizeL len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixIndexAscend_64u_L, (const Ipp64u* pSrc, IppSizeL srcStrideBytes, IppSizeL *pDstIndx, IppSizeL len, Ipp8u *pBuffer))

IPPAPI(IppStatus, ippsSortRadixIndexDescend_64s_L, (const Ipp64s* pSrc, IppSizeL srcStrideBytes, IppSizeL *pDstIndx, IppSizeL len, Ipp8u *pBuffer))
IPPAPI(IppStatus, ippsSortRadixIndexDescend_64u_L, (const Ipp64u* pSrc, IppSizeL srcStrideBytes, IppSizeL *pDstIndx, IppSizeL len, Ipp8u *pBuffer))



#ifdef __cplusplus
}
#endif

#endif /* IPPS_L_H__ */
