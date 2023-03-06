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
//         Intel(R) Integrated Performance Primitives
//             Data Integrity Primitives (ippDI)
//                     Legacy Library
//
*/

#if !defined(__IPPDI_90_LEGACY_H__)
#define __IPPDI_90_LEGACY_H__

#include "ippdefs90legacy.h"
#include "ippdi90legacy_redef.h"

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
LEGACY90IPPAPI( IppStatus, legacy90ippdiInit, ( void ))


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
LEGACY90IPPAPI( IppStatus, legacy90ippdiSetNumThreads, ( int numThr ) )

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
LEGACY90IPPAPI( IppStatus, legacy90ippdiGetNumThreads, (int* pNumThr) )

/*////////////////////////////////////////////////////////////////////////////*/


/* ///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//                   Functions declarations
//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippdiGetLibVersion
//  Purpose:    getting of the library version
//  Returns:    the structure of information about version of ippDI library
//  Parameters:
//
//  Notes:      not necessary to release the returned structure
*/

LEGACY90IPPAPI( const IppLibraryVersion*, legacy90ippdiGetLibVersion, (void) )


/* /////////////////////////////////////////////////////////////////////////////
//
// GF(2^m) extension of elementary GF(2)
//
*/
#if !defined( _OWN_BLDPCS )
   typedef struct _GF8  IppsGFSpec_8u;
#endif /* _OWN_BLDPCS */


LEGACY90IPPAPI(IppStatus, legacy90ippsGFGetSize_8u,(int gfDegree, int* pSize))

LEGACY90IPPAPI(IppStatus, legacy90ippsGFInit_8u,(int gfDegree, const Ipp8u* pPolynomial, IppsGFSpec_8u* pGF))


LEGACY90IPPAPI(IppStatus, legacy90ippsGFAdd_8u,(Ipp8u srcA, Ipp8u srcB, Ipp8u* pDstR, const IppsGFSpec_8u* pGF))

LEGACY90IPPAPI(IppStatus, legacy90ippsGFSub_8u,(Ipp8u srcA, Ipp8u srcB, Ipp8u* pDstR, const IppsGFSpec_8u* pGF))

LEGACY90IPPAPI(IppStatus, legacy90ippsGFMul_8u,(Ipp8u srcA, Ipp8u srcB, Ipp8u* pDstR, const IppsGFSpec_8u* pGF))

LEGACY90IPPAPI(IppStatus, legacy90ippsGFDiv_8u,(Ipp8u srcA, Ipp8u srcB, Ipp8u* pDstR, const IppsGFSpec_8u* pGF))

LEGACY90IPPAPI(IppStatus, legacy90ippsGFPow_8u,(Ipp8u srcA, int srcPwr, Ipp8u* pDstR, const IppsGFSpec_8u* pGF))

LEGACY90IPPAPI(IppStatus, legacy90ippsGFInv_8u,(Ipp8u srcA,        Ipp8u* pDstR,  const IppsGFSpec_8u* pGF))

LEGACY90IPPAPI(IppStatus, legacy90ippsGFNeg_8u,(Ipp8u srcA,        Ipp8u* pDstR,  const IppsGFSpec_8u* pGF))

LEGACY90IPPAPI(IppStatus, legacy90ippsGFLogAlpha_8u,(Ipp8u srcA,   Ipp8u* pDstPwr,const IppsGFSpec_8u* pGF))

LEGACY90IPPAPI(IppStatus, legacy90ippsGFExpAlpha_8u,(Ipp8u srcPwr, Ipp8u* pDdstR, const IppsGFSpec_8u* pGF))


/* /////////////////////////////////////////////////////////////////////////////
//
// polynomials over GF(2^m)
//
*/
#if !defined( _OWN_BLDPCS )
   typedef struct _PolyGF8 IppsPoly_GF8u;
#endif /* _OWN_BLDPCS */


LEGACY90IPPAPI(IppStatus, legacy90ippsPolyGFGetSize_8u,(int maxDegree, int* pSize))

LEGACY90IPPAPI(IppStatus, legacy90ippsPolyGFInit_8u,(const IppsGFSpec_8u* pGF, int maxDegree,
                                    IppsPoly_GF8u* pPoly))


LEGACY90IPPAPI(IppStatus, legacy90ippsPolyGFSetCoeffs_8u,(const Ipp8u* pCoeff,int degree,
                                    IppsPoly_GF8u* pPoly))

LEGACY90IPPAPI(IppStatus, legacy90ippsPolyGFSetDegree_8u,(int degree,
                                    IppsPoly_GF8u* pPoly))

LEGACY90IPPAPI(IppStatus, legacy90ippsPolyGFCopy_8u,(const IppsPoly_GF8u* pPolyA, IppsPoly_GF8u* pPolyB))


LEGACY90IPPAPI(IppStatus, legacy90ippsPolyGFGetRef_8u,(Ipp8u** const pDstCoeff, int* pDstDegree,
                                    IppsGFSpec_8u** const pDstGF,
                                    const IppsPoly_GF8u* pPoly))


LEGACY90IPPAPI(IppStatus, legacy90ippsPolyGFAdd_8u,(const IppsPoly_GF8u* pSrcA, const IppsPoly_GF8u* pSrcB,
                                          IppsPoly_GF8u* pDstR))

LEGACY90IPPAPI(IppStatus, legacy90ippsPolyGFSub_8u,(const IppsPoly_GF8u* pSrcA, const IppsPoly_GF8u* pSrcB,
                                          IppsPoly_GF8u* pSrcR))

LEGACY90IPPAPI(IppStatus, legacy90ippsPolyGFMul_8u,(const IppsPoly_GF8u* pSrcA, const IppsPoly_GF8u* pSrcB,
                                          IppsPoly_GF8u* pDstR))

LEGACY90IPPAPI(IppStatus, legacy90ippsPolyGFMod_8u,(const IppsPoly_GF8u* pSrcA, const IppsPoly_GF8u* pSrcB,
                                          IppsPoly_GF8u* pDstR))

LEGACY90IPPAPI(IppStatus, legacy90ippsPolyGFDiv_8u,(const IppsPoly_GF8u* pSrcDividend, const IppsPoly_GF8u* pSrcDivisor,
                                          IppsPoly_GF8u* pDstQuotient,
                                          IppsPoly_GF8u* pDstReminder))

LEGACY90IPPAPI(IppStatus, legacy90ippsPolyGFShlC_8u,(const IppsPoly_GF8u* pSrc, int nShift,
                                           IppsPoly_GF8u* pDst))

LEGACY90IPPAPI(IppStatus, legacy90ippsPolyGFShrC_8u,(const IppsPoly_GF8u* pSrc, int nShift,
                                           IppsPoly_GF8u* pDst))


LEGACY90IPPAPI(IppStatus, legacy90ippsPolyGFIrreducible_8u,(const IppsPoly_GF8u* pSrc, IppBool* pIsIrreducible))

LEGACY90IPPAPI(IppStatus, legacy90ippsPolyGFPrimitive_8u,(const IppsPoly_GF8u* pSrc, IppBool isIrreducible, IppBool* pIsPrimitive))


LEGACY90IPPAPI(IppStatus, legacy90ippsPolyGFValue_8u,(const IppsPoly_GF8u* pSrc, Ipp8u srcE, Ipp8u* pDstValue))

LEGACY90IPPAPI(IppStatus, legacy90ippsPolyGFDerive_8u,(const IppsPoly_GF8u* pSrc, IppsPoly_GF8u* pDst))

LEGACY90IPPAPI(IppStatus, legacy90ippsPolyGFRoots_8u,(const IppsPoly_GF8u* pSrc,
                                      Ipp8u* pRoot, int* nRoots))


LEGACY90IPPAPI(IppStatus, legacy90ippsPolyGFGCD_8u,(const IppsPoly_GF8u* pSrcA, const IppsPoly_GF8u* pSrcB,
                                          IppsPoly_GF8u* pDstGCD))



/* /////////////////////////////////////////////////////////////////////////////
//
// RS encoder
//
*/
#if !defined( _OWN_BLDPCS )
   typedef struct _RSencodeGF8   IppsRSEncodeSpec_8u;
#endif /* _OWN_BLDPCS */


LEGACY90IPPAPI(IppStatus, legacy90ippsRSEncodeGetSize_8u,(int codeLen, int dataLen, int* pSize))

LEGACY90IPPAPI(IppStatus, legacy90ippsRSEncodeInit_8u,(int codeLen, int dataLen, const IppsGFSpec_8u* pGF, Ipp8u root,
                                       IppsRSEncodeSpec_8u* pRS))


LEGACY90IPPAPI(IppStatus, legacy90ippsRSEncodeGetBufferSize_8u,(const IppsRSEncodeSpec_8u* pRS, int* pSize))


LEGACY90IPPAPI(IppStatus, legacy90ippsRSEncode_8u,(const Ipp8u* pSrc,
                                         Ipp8u* pDst,
                                   const IppsRSEncodeSpec_8u* pRS,
                                         Ipp8u* pBuffer))


/* /////////////////////////////////////////////////////////////////////////////
//
// RS decoder
//
*/
#if !defined( _OWN_BLDPCS )
   typedef struct _RSdecodeGF8  IppsRSDecodeSpec_8u;
#endif /* _OWN_BLDPCS */


LEGACY90IPPAPI(IppStatus, legacy90ippsRSDecodeGetSize_8u,(int codeLen, int dataLen, int* pSize))

LEGACY90IPPAPI(IppStatus, legacy90ippsRSDecodeInit_8u,(int codeLen, int dataLen, const IppsGFSpec_8u* pGF, Ipp8u root,
                                       IppsRSDecodeSpec_8u* pRS))


LEGACY90IPPAPI(IppStatus, legacy90ippsRSDecodeBMGetBufferSize_8u,(const IppsRSDecodeSpec_8u* pRS, int* pSize))

LEGACY90IPPAPI(IppStatus, legacy90ippsRSDecodeEEGetBufferSize_8u,(const IppsRSDecodeSpec_8u* pRS, int* pSize))


LEGACY90IPPAPI(IppStatus, legacy90ippsRSDecodeBM_8u,(const int *pErasureList, int erasureListLen,
                                     Ipp8u* pSrcDstCodeWord,
                                     const IppsRSDecodeSpec_8u* pRS,
                                     Ipp8u* pBuffer))


LEGACY90IPPAPI(IppStatus, legacy90ippsRSDecodeEE_8u,(const int *pErasureList, int erasureListLen,
                                     Ipp8u* pSrcDstCodeWord,
                                     const IppsRSDecodeSpec_8u* pRS,
                                     Ipp8u* pBuffer))


#ifdef __cplusplus
}
#endif



#endif /* __IPPDI_90_LEGACY_H__ */
