
/*
// Copyright 2004-2020 Intel Corporation All Rights Reserved.
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
//              Data Compression Library (ippDC)
//
//
*/


#if !defined( IPPDC_H__ ) || defined( _OWN_BLDPCS )
#define IPPDC_H__

#ifndef IPPDEFS_H__
  #include "ippdefs.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if !defined( IPP_NO_DEFAULT_LIB )
  #if defined( _IPP_SEQUENTIAL_DYNAMIC )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippdc" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippcore" )
  #elif defined( _IPP_SEQUENTIAL_STATIC )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippdcmt" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippsmt" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippvmmt" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippcoremt" )
  #elif defined( _IPP_PARALLEL_DYNAMIC )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippdc" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippcore" )
  #elif defined( _IPP_PARALLEL_STATIC )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippdcmt" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippsmt" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippvmmt" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippcoremt" )
  #endif
#endif


/********************* Data Structures and Macro ****************************/

/* /////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//                   Functions declarations
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////// */


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippdcGetLibVersion
//  Purpose:    getting of the library version
//  Returns:    the structure of information about version
//              of ippDC library
//  Parameters:
//
//  Notes:      not necessary to release the returned structure
*/
IPPAPI( const IppLibraryVersion*, ippdcGetLibVersion, (void) )

/* Move To Front */

/* /////////////////////////////////////////////////////////////////////////////
// Name:                ippsMTFInit_8u
// Purpose:             Initializes parameters for the MTF transform
//
// Parameters:
//    pMTFState         Pointer to the structure containing parameters for
//                      the MTF transform
//
// Return:
//    ippStsNullPtrErr  Pointer to structure is NULL
//    ippStsNoErr       No errors
//
*/
IPPAPI(IppStatus, ippsMTFInit_8u, ( IppMTFState_8u* pMTFState ))

/* /////////////////////////////////////////////////////////////////////////////
// Name:                ippsMTFGetSize_8u
// Purpose:             Computes the size of necessary memory (in bytes) for
//                      structure of the MTF transform
//
// Parameters:
//    pMTFStateSize     Pointer to the computed size of structure
//
// Return:
//    ippStsNullPtrErr  Pointer is NULL
//    ippStsNoErr       No errors
//
*/
IPPAPI(IppStatus, ippsMTFGetSize_8u, ( int* pMTFStateSize ))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsMTFFwd_8u
//  Purpose:            Performs the forward MTF transform
//
//  Parameters:
//    pSrc              Pointer to the source vector
//    pDst              Pointer to the destination vector
//    len               Length of source/destination vectors
//    pMTFState         Pointer to the structure containing parameters for
//                      the MTF transform
//  Return:
//    ippStsNullPtrErr  One or several pointer(s) is NULL
//    ippStsSizeErr     Length of the source vector is less or equal zero
//    ippStsNoErr       No errors
//
*/
IPPAPI(IppStatus, ippsMTFFwd_8u, ( const Ipp8u* pSrc, Ipp8u* pDst, int len,
                                   IppMTFState_8u* pMTFState ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsMTFInv_8u
//  Purpose:            Performs the inverse MTF transform
//
//  Parameters:
//    pSrc              Pointer to the source vector
//    pDst              Pointer to the destination vector
//    len               Length of source/destination vectors
//    pMTFState         Pointer to the structure containing parameters for
//                      the MTF transform
//  Return:
//    ippStsNullPtrErr  One or several pointer(s) is NULL
//    ippStsSizeErr     Length of the source vector is less or equal zero
//    ippStsNoErr       No errors
//
*/
IPPAPI(IppStatus, ippsMTFInv_8u, ( const Ipp8u* pSrc, Ipp8u* pDst, int len,
                                   IppMTFState_8u* pMTFState ))

/* Burrows - Wheeler Transform */
/* /////////////////////////////////////////////////////////////////////////////
// Name:                ippsBWTFwdGetSize_8u
// Purpose:             Computes the size of necessary memory (in bytes) for
//                      additional buffer for the forward BWT transform
//
// Parameters:
//    wndSize           Window size for the BWT transform
//    pBWTFwdBuffSize   Pointer to the computed size of buffer
//
// Return:
//    ippStsNullPtrErr  Pointer is NULL
//    ippStsNoErr       No errors
//
*/
/* not used */
IPPAPI(IppStatus, ippsBWTFwdGetSize_8u, ( int wndSize, int* pBWTFwdBuffSize ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsBWTFwd_8u
//  Purpose:            Performs the forward BWT transform
//
//  Parameters:
//    pSrc              Pointer to the source vector
//    pDst              Pointer to the destination vector
//    len               Length of source/destination vectors
//    index             Pointer to the index of first position for
//                      the inverse BWT transform
//    pBWTFwdBuff       Pointer to the additional buffer
//
//  Return:
//    ippStsNullPtrErr  One or several pointer(s) is NULL
//    ippStsSizeErr     Length of source/destination vectors is less or equal zero
//    ippStsNoErr       No errors
//
*/
/* not used */
IPPAPI(IppStatus, ippsBWTFwd_8u, ( const Ipp8u* pSrc, Ipp8u* pDst, int len,
                                   int* index, Ipp8u* pBWTFwdBuff ))


/* /////////////////////////////////////////////////////////////////////////////
// Name:                ippsBWTFwdGetBufSize_SelectSort_8u
// Purpose:             Computes the size of necessary memory (in bytes) for
//                      additional buffer for the forward BWT transform
//
// Parameters:
//    wndSize           Window size for the BWT transform
//    pBWTFwdBufSize    Pointer to the computed size of buffer
//    sortAlgorithmHint Strategy hint for Sort algorithm selection
//
// Return:
//    ippStsNullPtrErr  Pointer is NULL
//    ippStsNoErr       No errors
//
*/
IPPAPI(IppStatus, ippsBWTFwdGetBufSize_SelectSort_8u, (Ipp32u wndSize, Ipp32u* pBWTFwdBufSize,
                                                       IppBWTSortAlgorithmHint sortAlgorithmHint ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsBWTFwd_SelectSort_8u
//  Purpose:            Performs the forward BWT transform
//
//  Parameters:
//    pSrc              Pointer to the source vector
//    pDst              Pointer to the destination vector
//    len               Length of source/destination vectors
//    index             Pointer to the index of first position for
//                      the inverse BWT transform
//    pBWTFwdBuf        Pointer to the additional buffer
//    sortAlgorithmHint Strategy hint for Sort algorithm selection
//
//  Return:
//    ippStsNullPtrErr  One or several pointer(s) is NULL
//    ippStsSizeErr     Length of source/destination vectors is less or equal zero
//    ippStsNoErr       No errors
//
*/
IPPAPI(IppStatus, ippsBWTFwd_SelectSort_8u, ( const Ipp8u* pSrc, Ipp8u* pDst, Ipp32u len, Ipp32u* index, Ipp8u* pBWTFwdBuf,
                                              IppBWTSortAlgorithmHint sortAlgorithmHint ))

/* /////////////////////////////////////////////////////////////////////////////
// Name:                ippsBWTInvGetSize_8u
// Purpose:             Computes the size of necessary memory (in bytes) for
//                      additional buffer for the inverse BWT transform
//
// Parameters:
//    wndSize           Window size for the BWT transform
//    pBWTInvBuffSize   Pointer to the computed size of buffer
//
// Return:
//    ippStsNullPtrErr  Pointer is NULL
//    ippStsNoErr       No errors
//
*/
/* not used */
IPPAPI(IppStatus, ippsBWTInvGetSize_8u, ( int wndSize, int* pBWTInvBuffSize ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsBWTInv_8u
//  Purpose:            Performs the inverse BWT transform
//
//  Parameters:
//    pSrc              Pointer to the source vector
//    pDst              Pointer to the destination vector
//    len               Length of source/destination vectors
//    index             Index of first position for the inverse BWT transform
//    pBWTInvBuff       Pointer to the additional buffer
//
//  Return:
//    ippStsNullPtrErr  One or several pointer(s) is NULL
//    ippStsSizeErr     Length of source/destination vectors is less or
//                      equal zero or index greater or equal srcLen
//    ippStsNoErr       No errors
//
*/
/* not used */
IPPAPI(IppStatus, ippsBWTInv_8u, ( const Ipp8u* pSrc, Ipp8u* pDst, int len,
                                   int index, Ipp8u* pBWTInvBuff ))

/* Ziv Lempel Storer Szymanski (LZSS) functions */

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsLZSSGetSize_8u
//  Purpose:            Finds out size of LZSS internal state structure in bytes
//
//  Parameters:
//    pLZSSStateSize    Pointer to the size of LZSS internal encoding state
//  Return:
//    ippStsNullPtrErr  Pointer to LZSSStateSize is NULL
//    ippStsNoErr       No errors
//
*/

IPPAPI(IppStatus, ippsLZSSGetSize_8u, ( int* pLZSSStateSize ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsEncodeLZSSInit_8u
//  Purpose:            Initializes the LZSS internal state for encoding
//
//  Parameters:
//    pLZSSState        Pointer to memory allocated for LZSS internal state
//  Return:
//    ippStsNullPtrErr  Pointer to internal LZSS state structure is NULL
//    ippStsNoErr       No errors
//
*/

IPPAPI(IppStatus, ippsEncodeLZSSInit_8u, ( IppLZSSState_8u* pLZSSState ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsEncodeLZSS_8u
//  Purpose:            Performs LZSS encoding
//
//  Parameters:
//    ppSrc             Double pointer to the source vector
//    pSrcLen           Pointer to the length of source vector
//    ppDst             Double pointer to the destination vector
//    pDstLen           Pointer to the length of destination vector
//    pLZSSState        Pointer to LZSS internal state for encoding
//  Return:
//    ippStsNullPtrErr           One or several pointer(s) is NULL
//    ippStsSizeErr              Bad length arguments
//    ippStsDstSizeLessExpected  Destination buffer is full
//    ippStsNoErr                No errors
//
*/

IPPAPI(IppStatus, ippsEncodeLZSS_8u, ( Ipp8u** ppSrc, int* pSrcLen, Ipp8u** ppDst, int* pDstLen,
                                    IppLZSSState_8u* pLZSSState ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsEncodeLZSSFlush_8u
//  Purpose:            Flushes the last few bits from the bit stream and alignes
//                      output data on the byte boundary
//
//  Parameters:
//    ppDst             Double pointer to the destination vector
//    pDstLen           Pointer to the length of destination vector
//    pLZSSState        Pointer to the LZSS internal state for encoding
//  Return:
//    ippStsNullPtrErr           One or several pointer(s) is NULL
//    ippStsSizeErr              Bad length arguments
//    ippStsDstSizeLessExpected  Destination buffer is full
//    ippStsNoErr                No errors
*/

IPPAPI(IppStatus, ippsEncodeLZSSFlush_8u, (Ipp8u** ppDst, int* pDstLen, IppLZSSState_8u* pLZSSState))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsDecodeLZSSInit_8u
//  Purpose:            Initializes the LZSS internal state for decoding
//
//  Parameters:
//    pLZSSState        Pointer to memory allocated for LZSS internal state
//  Return:
//    ippStsNullPtrErr  Pointer to internal LZSS state structure is NULL
//    ippStsNoErr       No errors
//
*/

IPPAPI(IppStatus, ippsDecodeLZSSInit_8u, ( IppLZSSState_8u* pLZSSState ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsDecodeLZSS_8u
//  Purpose:            Performs LZSS decoding
//
//  Parameters:
//    ppSrc             Double pointer to the source vector
//    pSrcLen           Pointer to the length of source vector
//    ppDst             Double pointer to the destination vector
//    pDstLen           Pointer to the length of destination vector
//    pLZSSState        Pointer to LZSS internal state
//  Return:
//    ippStsNullPtrErr           One or several pointer(s) is NULL
//    ippStsSizeErr              Bad length arguments
//    ippStsDstSizeLessExpected  Destination buffer is full
//    ippStsNoErr                No errors
//
*/
IPPAPI(IppStatus, ippsDecodeLZSS_8u, ( Ipp8u** ppSrc, int* pSrcLen, Ipp8u** ppDst,
                                    int* pDstLen, IppLZSSState_8u* pLZSSState ))


/* rfc1950, 1951, 1952 - compatible functions */



/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsAdler32
//  Purpose:            Computes the adler32(ITUT V.42) checksum for the source vector.
//
//  Parameters:
//   pSrc               Pointer to the source vector.
//   srcLen             Length of the source vector.
//   pAdler32           Pointer to the checksum value.
//  Return:
//   ippStsNoErr        Indicates no error.
//   ippStsNullPtrErr   Indicates an error when the pSrc pointer is NULL.
//   ippStsSizeErr      Indicates an error when the length of the source vector is less
//                      than or equal to zero.
//
*/
IPPAPI( IppStatus, ippsAdler32_8u, (const Ipp8u* pSrc, int srcLen, Ipp32u* pAdler32) )

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsCRC32
//  Purpose:            Computes the CRC32(ITUT V.42) checksum for the source vector.
//
//  Parameters:
//   pSrc               Pointer to the source vector.
//   srcLen             Length of the source vector.
//   pCRC32             Pointer to the checksum value.
//  Return:
//   ippStsNoErr        Indicates no error.
//   ippStsNullPtrErr   Indicates an error when the pSrc pointer is NULL.
//   ippStsSizeErr      Indicates an error when the length of the source vector is less
//                      than or equal to zero.
//
*/
IPPAPI( IppStatus, ippsCRC32_8u, (const Ipp8u* pSrc, int srcLen, Ipp32u* pCRC32) )

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsCRC32C
//  Purpose:            Computes the CRC32C (the polynomial 0x11EDC6F41) value
//                      for the source vector.
//                      Reference: "Optimization of cyclic redundancy-check
//                      codes with 24 and 32 parity bits". Castagnoli, G.;
//                      Brauer, S.; Herrmann, M.; Communications,
//                      IEEE Transactions on Volume 41, Issue 6,
//                      June 1993 Page(s):883 - 892.
//
//  Parameters:
//   pSrc               Pointer to the source vector
//   srcLen             Length of the source vector
//   pCRC32C            Pointer to the CRC32C value
//  Return:
//   ippStsNoErr        No errors
//   ippStsNullPtrErr   One or several pointer(s) is NULL
//   ippStsSizeErr      Length of the source vector is equal zero
//
*/
IPPAPI( IppStatus, ippsCRC32C_8u, (const Ipp8u* pSrc, Ipp32u srcLen, Ipp32u* pCRC32C) )


/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsInflateBuildHuffTable
//  Purpose:            Builds literal/length and distance Huffman code table for
//                      decoding a block that was compressed with usage dynamic Huffman codes
//                      according to the "deflate" format (rfc1951)
//
//  Parameters:
//    pCodeLens         Pointer to the common array with literal/length and distance
//                      Huffman code lengths
//    nLitCodeLens      Number of literal/length Huffman code lengths
//    nDistCodeLens     Number of distance Huffman code lengths
//  Return:
//    ippStsNullPtrErr  One or several pointer(s) is NULL
//    ippStsSizeErr     nLitCodeLens is greater than 286, or nLitCodeLens is greater than 30
//                      (according to rfc1951)
//    ippStsSrcDataErr  Invalid literal/length and distance set has been met
//                      in the common lengths array
//    ippStsNoErr       No errors
//
*/
IPPAPI(IppStatus, ippsInflateBuildHuffTable, ( const Ipp16u* pCodeLens,
                                               unsigned int nLitCodeLens,
                                               unsigned int nDistCodeLens,
                                               IppInflateState *pIppInflateState ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsInflate_8u
//  Purpose:            Decodes of the "deflate" format (rfc1951)
//                      according to the type of Huffman code tables
//
//  Parameters:
//    ppSrc             Double pointer to the source vector
//    pSrcLen           Pointer to the length of the source vector
//    pCode             Pointer to the bit buffer
//    pCodeLenBits      Number of valid bits in the bit buffer
//    winIdx            Index of the sliding window start position
//    ppDst             Double pointer to the destination vector
//    pDstLen           Pointer to the length of the destination vector
//    dstIdx            Index of the current position in the destination vector
//    pMode             Pointer to the current decode mode
//    pIppInflateState  Pointer to the structure that contains decode parameters
//  Return:
//    ippStsNullPtrErr  One or several pointer(s) is NULL
//    ippStsSizeErr     codeLenBits is greater than 32, or
//                      winIdx is greater than pIppInflateState->winSize, or
//                      dstIdx is greater than dstLen
//    ippStsSrcDataErr  Invalid literal/length and distance set has been met
//                      during decoding
//    ippStsNoErr       No errors
//
*/
IPPAPI(IppStatus, ippsInflate_8u, ( Ipp8u** ppSrc, unsigned int* pSrcLen,
                                    Ipp32u* pCode, unsigned int* pCodeLenBits,
                                    unsigned int winIdx,
                                    Ipp8u** ppDst, unsigned int* pDstLen, unsigned int dstIdx,
                                    IppInflateMode* pMode, IppInflateState *pIppInflateState ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsDeflateLZ77_8u
//  Purpose:            Perform LZ77 encoding according to
//                      the compression level
//
//  Parameters:
//    ppSrc             Double pointer to the source vector
//    pSrcLen           Pointer to the length of the source vector
//    pSrcIdx           Pointer to the index of the current position in
//                      the source vector. This parameter is used by
//                      the function for correlation current possition of
//                      the source vector and indexes in the hash tables.
//                      The normalization of this index and the hash tables
//                      must only be done every 2GB of the source data
//                      instead of 64K (the zlib approach)
//    pWindow           Pointer to the sliding window, which is used as
//                      the dictionary for LZ77 encoding
//    winSize           Size of the window and the hash prev table
//    pHashHead         Pointer to heads of the hash chains. This table is
//                      initialized with (-winSize) value for correct processing
//                      of the first bytes of the source vector
//    pHashPrev         Pointer to links to older strings with the same
//                      hash index
//    hashSize          Size of the hash head table
//    pLitFreqTable     Pointer to the literals/lengths frequency table
//    pDistFreqTable    Pointer to the distances frequency table
//    pLitDst           Pointer to the literals/lengths destination vector
//    pDistDst          Pointer to the distances destination vector
//    pDstLen           Pointer to the length of the destination vectors
//    comprLevel        Compression level. It is like the zlib compression level
//    pDst              Pointer to output vector
//    dstLen            The length of output vector
//    pDstIdx           Pointer to index for output vector
//    pLitHuffCodes     Pointer to the literals/lengths Huffman codes
//    pDistHuffCodes    Pointer to the distances Huffman codes
//    pVecMatch         Pointer to vector of parameters for match finding
//    flush             Flush value
//  Return:
//    ippStsNullPtrErr  One or several pointer(s) is NULL
//    ippStsNoErr       No errors
//
*/

IPPAPI( IppStatus, ippsDeflateLZ77_8u, (
                     const Ipp8u** ppSrc, Ipp32u* pSrcLen, Ipp32u* pSrcIdx,
                     const Ipp8u* pWindow, Ipp32u winSize,
                     Ipp32s* pHashHead, Ipp32s* pHashPrev, Ipp32u hashSize,
                     IppDeflateFreqTable pLitFreqTable[286],
                     IppDeflateFreqTable pDistFreqTable[30],
                     Ipp8u* pLitDst, Ipp16u* pDistDst, Ipp32u* pDstLen,
                     int comprLevel, IppLZ77Flush flush ) )

IPPAPI( IppStatus, ippsDeflateLZ77Fast_8u, (
                     const Ipp8u** ppSrc, Ipp32u* pSrcLen, Ipp32u* pSrcIdx,
                     const Ipp8u* pWindow, Ipp32u winSize,
                     Ipp32s* pHashHead, Ipp32s* pHashPrev, Ipp32u hashSize,
                     IppDeflateFreqTable pLitFreqTable[286],
                     IppDeflateFreqTable pDistFreqTable[30],
                     Ipp8u* pLitDst, Ipp16u* pDistDst, Ipp32u* pDstLen,
                     int *pVecMatch, IppLZ77Flush flush ) )

IPPAPI( IppStatus, ippsDeflateLZ77Fastest_8u, ( const Ipp8u** ppSrc, Ipp32u* pSrcLen, Ipp32u* pSrcIdx,
                     const Ipp8u* pWindow, Ipp32u winSize,
                     Ipp32s* pHashHead, Ipp32u hashSize,
                     Ipp16u* pCode, Ipp32u* pCodeLenBits,
                     Ipp8u* pDst, Ipp32u dstLen, Ipp32u* pDstIdx,
                     IppDeflateHuffCode pLitHuffCodes[286],
                     IppDeflateHuffCode pDistHuffCodes[30],
                     IppLZ77Flush flush ) )

IPPAPI( IppStatus, ippsDeflateLZ77FastestPrecompHeader_8u, ( const Ipp8u** ppSrc, Ipp32u* pSrcLen, Ipp32u* pSrcIdx,
                     const Ipp8u* pWindow, Ipp32u winSize,
                     Ipp32s* pHashHead, Ipp32u hashSize,
                     Ipp16u* pCode, Ipp32u* pCodeLenBits,
                     Ipp8u* pDst, Ipp32u dstLen, Ipp32u* pDstIdx,
                     IppDeflateHuffCode pLitHuffCodes[288],
                     IppDeflateHuffCode pDistHuffCodes[30],
                     const Ipp8u* pHeaderCodeLens, int numBitsHeader,
                     IppLZ77Flush flush ) )


IPPAPI( IppStatus, ippsDeflateLZ77Slow_8u, (
                     const Ipp8u** ppSrc, Ipp32u* pSrcLen, Ipp32u* pSrcIdx,
                     const Ipp8u* pWindow, Ipp32u winSize,
                     Ipp32s* pHashHead, Ipp32s* pHashPrev, Ipp32u hashSize,
                     IppDeflateFreqTable pLitFreqTable[286],
                     IppDeflateFreqTable pDistFreqTable[30],
                     Ipp8u* pLitDst, Ipp16u* pDistDst, Ipp32u* pDstLen,
                     int *pVecMatch, IppLZ77Flush flush ) )

IPPAPI( IppStatus, ippsDeflateLZ77FastestGetStat_8u, ( const Ipp8u** ppSrc, Ipp32u* pSrcLen, Ipp32u* pSrcIdx,
                                         const Ipp8u* pWindow, Ipp32u winSize,
                                         Ipp32s* pHashHead, Ipp32u hashSize,
                                         int    pLitStat[286], int pDistStat[30],
                                         IppLZ77Flush flush ))
IPPAPI( IppStatus, ippsDeflateLZ77FastestGenHuffTable_8u, (const int pLitStat[286], const int pDistStat[30],
    IppDeflateHuffCode pLitCodeTable[286], IppDeflateHuffCode pDistCodeTable[30]))
IPPAPI( IppStatus, ippsDeflateLZ77FastestGenHeader_8u, (const IppDeflateHuffCode pLitCodeTable[286],
    const IppDeflateHuffCode pDistCodeTable[30], Ipp8u *pDstHeader, int *pDstLen, int *pDstBits))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:              ippsDeflateHuff_8u
//  Purpose:           Performs Huffman encoding
//
//  Parameters:
//    pLitSrc          Pointer to the literals/lengths source vector
//    pDistSrc         Pointer to the distances source vector
//    pSrcLen          Pointer to the length of the source vectors
//    pCode            Pointer to the bit buffer
//    pCodeLenBits     Pointer to the number of valid bits in the bit buffer
//    pLitHuffCodes    Pointer to the literals/lengths Huffman codes
//    pDistHuffCodes   Pointer to the distances Huffman codes
//    pDst             Pointer to the destination vector
//    pDstIdx          Pointer to the index in the destination vector, the zlib
//                     uses the knowingly sufficient intermediate buffer for
//                     the Huffman encoding, so we need to know indexes of
//                     the first (input parameter) and the last (output parameter)
//                     symbols, which are written by the function
//  Return:
//    ippStsNullPtrErr One or several pointer(s) is NULL
//    ippStsNoErr      No errors
//
*/
IPPAPI( IppStatus, ippsDeflateHuff_8u, (
          const Ipp8u* pLitSrc, const Ipp16u* pDistSrc, Ipp32u srcLen,
          Ipp16u* pCode, Ipp32u* pCodeLenBits,
          IppDeflateHuffCode pLitHuffCodes[286],
          IppDeflateHuffCode pDistHuffCodes[30],
          Ipp8u* pDst, Ipp32u* pDstIdx ) )

/* /////////////////////////////////////////////////////////////////////////////
//  Name:              ippsDeflateDictionarySet_8u
//  Purpose:           Presets the user's dictionary for LZ77 encoding
//
//  Parameters:
//    pDictSrc         Pointer to the user's dictionary
//    dictLen          Length of the user's dictionary
//    pHashHeadDst     Pointer to heads of the hash chains
//    hashSize         Size of the hash head table
//    pHashPrevDst     Pointer to links to older strings with the same
//                     hash index
//    pWindowDst       Pointer to the sliding window, which is used as
//                     the dictionary for LZ77 encoding
//    winSize          Size of the window and the hash prev table in elements
//    comprLevel       Compression level. It is like the zlib compression level
//  Return:
//    ippStsNullPtrErr One or several pointer(s) is NULL
//    ippStsSizeErr    wndSize less or equal 256 or more than 32768,
//                     hashSize less or equal 256 or more than 65536
//    ippStsNoErr      No errors
//
*/
IPPAPI( IppStatus, ippsDeflateDictionarySet_8u, (
          const Ipp8u* pDictSrc, Ipp32u dictLen,
          Ipp32s* pHashHeadDst, Ipp32u hashSize, Ipp32s* pHashPrevDst,
          Ipp8u* pWindowDst, Ipp32u winSize, int comprLevel ) )

/* /////////////////////////////////////////////////////////////////////////////
//  Name:              ippsDeflateUpdateHash_8u
//  Purpose:           Updates hash tables according to the source context
//
//  Parameters:
//    pDictSrc         Pointer to the source vector
//    srcIdx           Index of the current position in the source vector.
//                     This parameter is used by the function
//                     for correlation current possition of the source vector
//                     and indexes in the hash tables.
//                     The normalization of this index and the hash tables
//                     must only be done every 2GB of the source data
//                     instead of 64K (the zlib approach)
//    srcLen           Length of the source vector
//    pHashHeadDst     Pointer to heads of the hash chains
//    hashSize         Size of the hash head table
//    pHashPrevDst     Pointer to links to older strings with the same
//                     hash index
//    winSize          Size of the window and the hash prev table in elements
//    comprLevel       Compression level. It is like the zlib compression level
//  Return:
//    ippStsNullPtrErr One or several pointer(s) is NULL
//    ippStsSizeErr    wndSize less or equal 256 or more than 32768,
//                     hashSize less or equal 256 or more than 65536
//    ippStsNoErr      No errors
//
*/
IPPAPI( IppStatus, ippsDeflateUpdateHash_8u, ( const Ipp8u* pSrc, Ipp32u srcIdx, Ipp32u srcLen,
                                               Ipp32s* pHashHeadDst, Ipp32u hashSize,
                                               Ipp32s* pHashPrevDst, Ipp32u winSize, int comprLevel ) )

/* bzip2 - compatible functions */

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsRLEGetSize_BZ2_8u
//  Purpose:            Calculates the size of internal state for bzip2-specific RLE.
//                      Specific function for bzip2 compatibility.
//
//  Parameters:
//    pRLEStateSize             Pointer to the size of internal state for bzip2-specific RLE
//
//  Return:
//    ippStsNullPtrErr          One or several pointer(s) is NULL
//    ippStsNoErr               No errors
//
*/

IPPAPI(IppStatus, ippsRLEGetSize_BZ2_8u,    ( int* pRLEStateSize ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsEncodeRLEInit_BZ2_8u
//  Purpose:            Initializes the elements of the bzip2-specific internal state for RLE.
//                      Specific function for bzip2 compatibility.
//
//  Parameters:
//    pRLEState         Pointer to internal state structure for bzip2 specific RLE
//
//  Return:
//    ippStsNullPtrErr          One or several pointer(s) is NULL
//    ippStsNoErr               No errors
//
*/

IPPAPI(IppStatus, ippsEncodeRLEInit_BZ2_8u,    ( IppRLEState_BZ2* pRLEState ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsEncodeRLE_BZ2_8u
//  Purpose:            Performs the RLE encoding with thresholding = 4.
//                      Specific function for bzip2 compatibility.
//
//  Parameters:
//    ppSrc             Double pointer to the source vector
//    pSrcLen           Pointer to the length of source vector
//    pDst              Pointer to the destination vector
//    pDstLen           Pointer to the size of destination buffer on input,
//                      pointer to the resulting length of the destination vector
//                      on output
//    pRLEState         Pointer to internal state structure for bzip2 specific RLE
//
//  Return:
//    ippStsNullPtrErr          One or several pointer(s) is NULL
//    ippStsSizeErr             Lengths of the source/destination vector are less
//                              or equal zero
//    ippStsDstSizeLessExpected The size of destination vector less expected
//    ippStsNoErr               No errors
//
*/

IPPAPI(IppStatus, ippsEncodeRLE_BZ2_8u,    ( Ipp8u** ppSrc, int* pSrcLen, Ipp8u* pDst, int* pDstLen, IppRLEState_BZ2* pRLEState ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsEncodeRLEFlush_BZ2_8u
//  Purpose:            Performs flushing the rest of data after RLE encoding with thresholding = 4.
//                      Specific function for bzip2 compatibility.
//
//  Parameters:
//    pDst              Pointer to the destination vector
//    pDstLen           Pointer to the size of destination buffer on input,
//                      pointer to the resulting length of the destination vector
//                      on output
//    pRLEState         Pointer to internal state structure for bzip2 specific RLE
//
//  Return:
//    ippStsNullPtrErr          One or several pointer(s) is NULL
//    ippStsSizeErr             Lengths of the source/destination vector are less
//                              or equal zero
//    ippStsNoErr               No errors
//
*/

IPPAPI(IppStatus, ippsEncodeRLEFlush_BZ2_8u,   ( Ipp8u* pDst, int* pDstLen, IppRLEState_BZ2* pRLEState ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsDecodeRLEStateInit_BZ2_8u
//  Purpose:            Initializes the elements of the bzip2-specific internal state for RLE.
//                      Specific function for bzip2 compatibility.
//
//  Parameters:
//    pRLEState         Pointer to internal state structure for bzip2 specific RLE
//
//  Return:
//    ippStsNullPtrErr          One or several pointer(s) is NULL
//    ippStsNoErr               No errors
//
*/

IPPAPI(IppStatus, ippsDecodeRLEStateInit_BZ2_8u, ( IppRLEState_BZ2* pRLEState ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsDecodeRLEState_BZ2_8u
//  Purpose:            Performs the RLE decoding with thresholding = 4.
//                      Specific function for bzip2 compatibility.
//
//  Parameters:
//    ppSrc             Double pointer to the source vector
//    pSrcLen           Pointer to the length of source vector
//    pDst              Double pointer to the destination vector
//    pDstLen           Pointer to the size of destination buffer on input,
//                      pointer to the resulting length of the destination vector
//                      on output
//    pRLEState         Pointer to internal state structure for bzip2 specific RLE
//
//  Return:
//    ippStsNullPtrErr          One or several pointer(s) is NULL
//    ippStsDstSizeLessExpected The size of destination vector less expected
//    ippStsNoErr               No errors
//
*/

IPPAPI(IppStatus, ippsDecodeRLEState_BZ2_8u, (Ipp8u** ppSrc, Ipp32u* pSrcLen, Ipp8u** ppDst, Ipp32u* pDstLen, IppRLEState_BZ2* pRLEState ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsDecodeRLEStateFlush_BZ2_8u
//  Purpose:            Performs flushing the rest of data after RLE decoding with thresholding = 4.
//                      Specific function for bzip2 compatibility.
//
//  Parameters:
//    pRLEState         Pointer to internal state structure for bzip2 specific RLE
//    ppDst             Double pointer to the destination vector
//    pDstLen           Pointer to the size of destination buffer on input,
//                      pointer to the resulting length of the destination vector
//                      on output
//
//  Return:
//    ippStsNullPtrErr          One or several pointer(s) is NULL
//    ippStsNoErr               No errors
//
*/

IPPAPI(IppStatus, ippsDecodeRLEStateFlush_BZ2_8u, (IppRLEState_BZ2* pRLEState, Ipp8u** ppDst, Ipp32u* pDstLen ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsRLEGetInUseTable_8u
//  Purpose:            Service function: gets the pointer to the inUse vector from internal state
//                      of type IppRLEState_BZ2. Specific function for bzip2 compatibility.
//
//  Parameters:
//    inUse             Pointer to the inUse vector
//    pRLEState         Pointer to internal state structure for bzip2 specific RLE
//
//  Return:
//    ippStsNullPtrErr          One or several pointer(s) is NULL
//    ippStsNoErr               No errors
//
*/

IPPAPI(IppStatus, ippsRLEGetInUseTable_8u,    ( Ipp8u inUse[256], IppRLEState_BZ2* pRLEState ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsEncodeZ1Z2_BZ2_8u16u
//  Purpose:            Performs the Z1Z2 encoding.
//                      Specific function for bzip2 compatibility.
//
//  Parameters:
//    ppSrc             Double pointer to the source vector
//    pSrcLen           Pointer to the length of source vector on input,
//                      pointer to the size of remainder on output
//    pDst              Pointer to the destination vector
//    pDstLen           Pointer to the size of destination buffer on input,
//                      pointer to the resulting length of the destination vector
//                      on output.
//    freqTable[258]    Table of frequencies collected for alphabet symbols.
//
//  Return:
//    ippStsNullPtrErr          One or several pointer(s) is NULL
//    ippStsSizeErr             Lengths of the source/destination vector are less
//                              or equal zero
//    ippStsDstSizeLessExpected The size of destination vector less expected
//    ippStsNoErr               No errors
//
*/

IPPAPI(IppStatus, ippsEncodeZ1Z2_BZ2_8u16u, ( Ipp8u** ppSrc, int* pSrcLen, Ipp16u* pDst, int* pDstLen, int freqTable[258] ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsDecodeZ1Z2_BZ2_16u8u
//  Purpose:            Performs the Z1Z2 decoding.
//                      Specific function for bzip2 compatibility.
//
//  Parameters:
//    ppSrc             Double pointer to the source vector
//    pSrcLen           Pointer to the length of source vector on input,
//                      pointer to the size of remainder on output
//    pDst              Pointer to the destination vector
//    pDstLen           Pointer to the size of destination buffer on input,
//                      pointer to the resulting length of the destination vector
//                      on output.
//
//  Return:
//    ippStsNullPtrErr          One or several pointer(s) is NULL
//    ippStsSizeErr             Lengths of the source/destination vector are less
//                              or equal zero
//    ippStsDstSizeLessExpected The size of destination vector less expected
//    ippStsNoErr               No errors
//
*/

IPPAPI(IppStatus, ippsDecodeZ1Z2_BZ2_16u8u, ( Ipp16u** ppSrc, int* pSrcLen, Ipp8u* pDst, int* pDstLen ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsReduceDictionary_8u_I
//  Purpose:            Performs the dictionary reducing.
//
//  Parameters:
//    inUse[256]        Table of 256 values of Ipp8u type.
//    pSrcDst           Pointer to the source/destination vector
//    srcDstLen         Length of source/destination vector.
//    pSizeDictionary   Pointer to the size of dictionary on input and to the size
//                      of reduced dictionary on output.
//
//  Return:
//    ippStsNullPtrErr          One or several pointer(s) is NULL
//    ippStsSizeErr             Lengths of the source/destination vector are less
//                              or equal zero
//    ippStsNoErr               No errors
//
*/

IPPAPI(IppStatus, ippsReduceDictionary_8u_I,   ( const Ipp8u inUse[256], Ipp8u* pSrcDst, int srcDstLen, int* pSizeDictionary ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsExpandDictionary_8u_I
//  Purpose:            Performs the dictionary expanding.
//
//  Parameters:
//    inUse[256]        Table of 256 values of Ipp8u type.
//    pSrcDst           Pointer to the source/destination vector
//    srcDstLen         Length of source/destination vector.
//    sizeDictionary    The size of reduced dictionary on input.
//
//  Return:
//    ippStsNullPtrErr          One or several pointer(s) is NULL
//    ippStsSizeErr             Lengths of the source/destination vector are less
//                              or equal zero
//    ippStsNoErr               No errors
//
*/

IPPAPI(IppStatus, ippsExpandDictionary_8u_I,   ( const Ipp8u inUse[256], Ipp8u* pSrcDst, int srcDstLen, int sizeDictionary ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsCRC32_BZ2_8u
//  Purpose:            Performs the CRC32 checksum calculation according to the direct algorithm, which is used in bzip2.
//
//  Parameters:
//    pSrc              Pointer to the source data vector
//    srcLen            The length of source vector
//    pCRC32            Pointer to the value of accumulated CRC32
//
//  Return:
//    ippStsNullPtrErr          One or several pointer(s) is NULL
//    ippStsSizeErr             Length of the source vector is less or equal zero
//    ippStsNoErr               No errors
//
*/

IPPAPI(IppStatus, ippsCRC32_BZ2_8u,    ( const Ipp8u* pSrc, int srcLen, Ipp32u* pCRC32 ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsEncodeHuffGetSize_BZ2_16u8u
//  Purpose:            Calculates the size of internal state for bzip2-specific Huffman coding.
//                      Specific function for bzip2 compatibility.
//
//  Parameters:
//    wndSize                          Size of the block to be processed
//    pEncodeHuffStateSize             Pointer to the size of internal state for bzip2-specific Huffman coding
//
//  Return:
//    ippStsNullPtrErr          One or several pointer(s) is NULL
//    ippStsSizeErr             Lengths of the source/destination vector are less
//                              or equal zero
//    ippStsNoErr               No errors
//
*/
IPPAPI(IppStatus, ippsEncodeHuffGetSize_BZ2_16u8u,   ( int wndSize, int* pEncodeHuffStateSize ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsEncodeHuffInit_BZ2_16u8u
//  Purpose:            Initializes the elements of the bzip2-specific internal state for Huffman coding.
//                      Specific function for bzip2 compatibility.
//
//  Parameters:
//    sizeDictionary     The size of the dictionary
//    freqTable          Table of frequencies of symbols
//    pSrc               Pointer to the source vector
//    srcLen             Length of the source vector
//    pEncodeHuffState   Pointer to internal state structure for bzip2 specific Huffman coding
//
//  Return:
//    ippStsNullPtrErr          One or several pointer(s) is NULL
//    ippStsSizeErr             Lengths of the source/destination vector are less
//                              or equal zero
//    ippStsNoErr               No errors
//
*/
IPPAPI(IppStatus, ippsEncodeHuffInit_BZ2_16u8u,      ( int sizeDictionary, const int freqTable[258], const Ipp16u* pSrc, int srcLen,
                                                       IppEncodeHuffState_BZ2* pEncodeHuffState ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsPackHuffContext_BZ2_16u8u
//  Purpose:            Performs the bzip2-specific encoding of Huffman context.
//                      Specific function for bzip2 compatibility.
//
//  Parameters:
//    pCode             Pointer to the bit buffer
//    pCodeLenBits      Number of valid bits in the bit buffer
//    pDst              Pointer to the destination vector
//    pDstLen           Pointer to the size of destination buffer on input,
//                      pointer to the resulting length of the destination vector
//                      on output
//    pEncodeHuffState  Pointer to internal state structure for bzip2 specific Huffman coding
//
//  Return:
//    ippStsNullPtrErr          One or several pointer(s) is NULL
//    ippStsSizeErr             Lengths of the source/destination vector are less
//                              or equal zero
//    ippStsDstSizeLessExpected The size of destination vector less expected
//    ippStsNoErr               No errors
//
*/
IPPAPI(IppStatus, ippsPackHuffContext_BZ2_16u8u,     ( Ipp32u* pCode, int* pCodeLenBits, Ipp8u* pDst, int* pDstLen,
                                                       IppEncodeHuffState_BZ2* pEncodeHuffState ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsEncodeHuff_BZ2_16u8u
//  Purpose:            Performs the bzip2-specific Huffman encoding.
//                      Specific function for bzip2 compatibility.
//
//  Parameters:
//    pCode             Pointer to the bit buffer
//    pCodeLenBits      Number of valid bits in the bit buffer
//    ppSrc             Double pointer to the source vector
//    pSrcLen           Pointer to the length of source vector
//    pDst              Pointer to the destination vector
//    pDstLen           Pointer to the size of destination buffer on input,
//                      pointer to the resulting length of the destination vector
//                      on output
//    pEncodeHuffState  Pointer to internal state structure for bzip2 specific Huffman coding
//
//  Return:
//    ippStsNullPtrErr          One or several pointer(s) is NULL
//    ippStsSizeErr             Lengths of the source/destination vector are less
//                              or equal zero
//    ippStsDstSizeLessExpected The size of destination vector less expected
//    ippStsNoErr               No errors
//
*/
IPPAPI(IppStatus, ippsEncodeHuff_BZ2_16u8u,          ( Ipp32u* pCode, int* pCodeLenBits, Ipp16u** ppSrc, int* pSrcLen,
                                                       Ipp8u* pDst, int* pDstLen, IppEncodeHuffState_BZ2* pEncodeHuffState ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsDecodeHuffGetSize_BZ2_8u16u
//  Purpose:            Calculates the size of internal state for bzip2-specific Huffman decoding.
//                      Specific function for bzip2 compatibility.
//
//  Parameters:
//    wndSize                    Size of the block to be processed
//    pDecodeHuffStateSize       Pointer to the size of internal state for bzip2-specific Huffman decoding
//
//  Return:
//    ippStsNullPtrErr          One or several pointer(s) is NULL
//    ippStsSizeErr             Lengths of the source/destination vector are less
//                              or equal zero
//    ippStsNoErr               No errors
//
*/
IPPAPI(IppStatus, ippsDecodeHuffGetSize_BZ2_8u16u,   ( int wndSize, int* pDecodeHuffStateSize ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsDecodeHuffInit_BZ2_8u16u
//  Purpose:            Initializes the elements of the bzip2-specific internal state for Huffman decoding.
//                      Specific function for bzip2 compatibility.
//
//  Parameters:
//    sizeDictionary           The size of the dictionary
//    pDecodeHuffState         Pointer to internal state structure for bzip2 specific Huffman decoding
//
//  Return:
//    ippStsNullPtrErr          One or several pointer(s) is NULL
//    ippStsSizeErr             Lengths of the source/destination vector are less
//                              or equal zero
//    ippStsNoErr               No errors
//
*/
IPPAPI(IppStatus, ippsDecodeHuffInit_BZ2_8u16u,      ( int sizeDictionary, IppDecodeHuffState_BZ2* pDecodeHuffState ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsUnpackHuffContext_BZ2_8u16u
//  Purpose:            Performs the bzip2-specific decoding of Huffman context.
//                      Specific function for bzip2 compatibility.
//
//  Parameters:
//    pCode                   Pointer to the bit buffer
//    pCodeLenBits            Number of valid bits in the bit buffer
//    pSrc                    Pointer to the destination vector
//    pSrcLen                 Pointer to the size of destination buffer on input,
//                            pointer to the resulting length of the destination vector
//                            on output
//    pDecodeHuffState        Pointer to internal state structure for bzip2 specific Huffman decoding.
//
//  Return:
//    ippStsNullPtrErr          One or several pointer(s) is NULL
//    ippStsSizeErr             Lengths of the source/destination vector are less
//                              or equal zero
//    ippStsDstSizeLessExpected The size of destination vector less expected
//    ippStsNoErr               No errors
//
*/
IPPAPI(IppStatus, ippsUnpackHuffContext_BZ2_8u16u,   ( Ipp32u* pCode, int* pCodeLenBits, Ipp8u** ppSrc, int* pSrcLen,
                                                       IppDecodeHuffState_BZ2* pDecodeHuffState ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:               ippsDecodeHuff_BZ2_8u16u
//  Purpose:            Performs the bzip2-specific Huffman decoding.
//                      Specific function for bzip2 compatibility.
//
//  Parameters:
//    pCode                   Pointer to the bit buffer
//    pCodeLenBits            Number of valid bits in the bit buffer
//    ppSrc                   Double pointer to the source vector
//    pSrcLen                 Pointer to the length of source vector
//    pDst                    Pointer to the destination vector
//    pDstLen                 Pointer to the size of destination buffer on input,
//                            pointer to the resulting length of the destination vector
//                            on output
//    pDecodeHuffState        Pointer to internal state structure for bzip2 specific Huffman decoding.
//
//  Return:
//    ippStsNullPtrErr          One or several pointer(s) is NULL
//    ippStsSizeErr             Lengths of the source/destination vector are less
//                              or equal zero
//    ippStsDstSizeLessExpected The size of destination vector less expected
//    ippStsNoErr               No errors
//
*/
IPPAPI(IppStatus, ippsDecodeHuff_BZ2_8u16u,          ( Ipp32u* pCode, int* pCodeLenBits, Ipp8u** ppSrc, int* pSrcLen,
                                                       Ipp16u* pDst, int* pDstLen, IppDecodeHuffState_BZ2* pDecodeHuffState ))

/* /////////////////////////////////////////////////////////////////////////////
// Name:                ippsDecodeBlockGetSize_BZ2_8u
// Purpose:             Computes the size of necessary memory (in bytes) for
//                      additional buffer for the bzip2-specific decoding.
//                      Specific function for bzip2 compatibility.
//
// Parameters:
//    blockSize         Block size for the bzip2-specific decoding
//    pBuffSize         Pointer to the computed size of buffer
//
// Return:
//    ippStsNullPtrErr  Pointer is NULL
//    ippStsNoErr       No errors
//
*/
IPPAPI(IppStatus, ippsDecodeBlockGetSize_BZ2_8u, ( int blockSize, int* pBuffSize ))

/* /////////////////////////////////////////////////////////////////////////////
// Name:                ippsDecodeBlockGetSize_BZ2_8u
//  Purpose:            Performs the bzip2-specific block decoding.
//                      Specific function for bzip2 compatibility.
//
// Parameters:
//    pSrc              Pointer to the source vector
//    pSrcLen           Pointer to the length of source vector
//    pDst              Pointer to the destination vector
//    pDstLen           Pointer to the size of destination buffer on input,
//                      pointer to the resulting length of the destination buffer
//                      on output
//    index             Index of first position for the inverse BWT transform
//    dictSize          The size of reduced dictionary
//    inUse             Table of 256 values of Ipp8u type
//    pBuff             Pointer to the additional buffer
//
// Return:
//    ippStsNullPtrErr  One or several pointer(s) is NULL
//    ippStsSizeErr     Length of source/destination vectors is less or
//                      equal zero or index greater or equal srcLen
//    ippStsNoErr       No errors
//
*/
IPPAPI(IppStatus, ippsDecodeBlock_BZ2_16u8u, ( const Ipp16u* pSrc, int srcLen, Ipp8u* pDst, int* pDstLen,
                                               int index, int dictSize, const Ipp8u inUse[256], Ipp8u* pBuff ))

/**************************************************
 LZO Definitions
***************************************************/

/*******************************************************************/

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsEncodeLZOGetSize
//  Purpose:    returns structure size necessary for compression
//
//  Arguments:
//     method           LZO method to be used during compression
//     maxInputLen      maximum length of input buffer, which will be processed by Encode
//     pSize            pointer to size variable
//
//  Return:
//      ippStsBadArgErr          illegal method
//      ippStsNullPtrErr         NULL pointer detected
//      ippStsNoErr              no error
//
*/
IPPAPI(IppStatus, ippsEncodeLZOGetSize, (IppLZOMethod method, Ipp32u maxInputLen, Ipp32u *pSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsEncodeLZO_8u
//  Purpose:    compresses specified input buffer
//
//  Arguments:
//      pSrc                   input data address
//      srcLen                 input data length
//      pDst                   output buffer address
//      pDstLen                pointer to resulting length variable, must contain output buffer length upon start
//      pLZOState              pointer to IppLZOState structure variable
//
//  Return:
//      ippStsNullPtrErr            one of the pointers is NULL
//      ippStsDstSizeLessExpected   output buffer is too short for compressed data
//      ippStsNoErr                 no error detected
//
*/
IPPAPI(IppStatus, ippsEncodeLZO_8u, (const Ipp8u *pSrc, Ipp32u srcLen, Ipp8u *pDst, Ipp32u *pDstLen, IppLZOState_8u *pLZOState ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsEncodeLZOInit
//  Purpose:    initializes IppLZOState_8u structure
//
//  Arguments:
//      method                  LZO compression method desired
//      maxInputLen             maximum length of input buffer, which will be processed by Encode
//      pLZOState               pointer to IppLZOState structure variable
//
//  Return:
//      ippStsNullPtrErr            one of the pointers is NULL
//      ippStsBadArgErr             illegal method
//      ippStsNoErr                 no error detected
//
*/
IPPAPI(IppStatus, ippsEncodeLZOInit_8u, (IppLZOMethod method, Ipp32u maxInputLen, IppLZOState_8u *pLZOState))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDecodeLZO_8u
//      Purpose:    decompresses specified input buffer to output buffer, returns decompressed data length
//  Name:       ippsDecodeLZOSafe_8u
//      Purpose:    decompresses specified input buffer to output buffer with checking output buffer boundaries, returns decompressed data length
//
//  Arguments:
//      pSrc                  pointer to input buffer
//      srcLen                input data length
//      pDst                  pointer to output buffer
//      pDstLen               pointer to output data length variable. Initially contains output buffer length
//
//  Return:
//      ippStsNullPtrErr            one of the pointers is NULL
//      ippStsDstSizeLessExpected   output buffer is too short for compressed data
//      ippStsSrcSizeLessExpected   input buffer data is not complete, i.e. no EOF found
//      ippStsLzoBrokenStreamErr    ippsDecodeLZOSafe_8u detected output buffer boundary violation
//      ippStsNoErr                 no error detected
//
*/
IPPAPI(IppStatus, ippsDecodeLZO_8u, (const Ipp8u *pSrc, Ipp32u srcLen, Ipp8u *pDst, Ipp32u *pDstLen))
IPPAPI(IppStatus, ippsDecodeLZOSafe_8u, (const Ipp8u *pSrc, Ipp32u srcLen, Ipp8u *pDst, Ipp32u *pDstLen))

/**************************************************
Intel(R) IPP LZ4 Definitions
***************************************************/

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsEncodeLZ4HashTableGetSize_8u
//  Purpose:    get size of buffer for Hash Table
//
//  Arguments:
//      pHashTableSize        pointer to size of buffer for Hash Table
//
//  Return:
//      ippStsNullPtrErr      pointer is NULL
//      ippStsNoErr           no error detected
//
*/
IPPAPI(IppStatus, ippsEncodeLZ4HashTableGetSize_8u,(int *pHashTableSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsEncodeLZ4HashTableInit_8u
//              ippsEncodeLZ4DictHashTableInit_8u
//  Purpose:    init of Hash Table
//
//  Arguments:
//      pHashTable      pointer to Hash Table
//      srcLen          length of source
//
//  Return:
//      ippStsNullPtrErr  pointer is NULL
//      ippStsSizeErr     length of source is less or equal zero
//      ippStsNoErr       no error detected
//
*/
IPPAPI(IppStatus, ippsEncodeLZ4HashTableInit_8u,(Ipp8u* pHashTable, int srcLen))
IPPAPI(IppStatus, ippsEncodeLZ4DictHashTableInit_8u,(Ipp8u* pHashTable, int srcLen))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsEncodeLZ4_8u
//              ippsEncodeLZ4Safe_8u
//  Purpose:    LZ4 encoder
//
//  Arguments:
//      pSrc            pointer to source
//      srcLen          length of source
//      pSrcLen         pointer to length of source / to length of proccesed input data
//      pDst            pointer to destination
//      pDstLen         pointer to length of destination buffer/ to length of compressed output data
//      pHashTable      pointer to Hash Table
//
//  Return:
//      ippStsNullPtrErr            one of the pointers is NULL
//      ippStsSizeErr               length of source is less or equal zero
//      ippStsNoErr                 no error detected
//      ippStsDstSizeLessExpected   the length of destination buffer is not enough
*/
IPPAPI(IppStatus, ippsEncodeLZ4_8u,(const Ipp8u* pSrc, int srcLen, Ipp8u* pDst, int *pDstLen, Ipp8u *pHashTable))
IPPAPI(IppStatus, ippsEncodeLZ4Safe_8u,(const Ipp8u* pSrc, int *srcLen, Ipp8u* pDst, int *pDstLen, Ipp8u *pHashTable))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsEncodeLZ4Dict_8u
//              ippsEncodeLZ4DictSafe_8u
//  Purpose:    LZ4 encoder
//
//  Arguments:
//      pSrc            pointer to source
//      srcIdx          index of start byte in source vector
//      srcLen          length of source
//      pSrcLen         pointer to length of source / to length of proccesed input data
//      pDst            pointer to destination
//      pDstLen         pointer to length of destination buffer/ to length of compressed output data
//      pHashTable      pointer to Hash Table
//      pDict           pointer to dictinary
//      dictLen         length of dictinary
//
//  Return:
//      ippStsNullPtrErr            one of the pointers is NULL
//      ippStsSizeErr               length of source is less or equal zero
//      ippStsNoErr                 no error detected
//      ippStsBadArgErr             index of start byte is less then zero
//      ippStsDstSizeLessExpected   thre length of destination buffer is not enough
*/
IPPAPI(IppStatus, ippsEncodeLZ4Dict_8u,(const Ipp8u* pSrc, int srcIdx, int srcLen, Ipp8u* pDst, int *pDstLen,
    Ipp8u *pHashTable, const Ipp8u* pDict, int dictLen))
IPPAPI(IppStatus, ippsEncodeLZ4DictSafe_8u,(const Ipp8u* pSrc, int srcIdx, int *pSrcLen, Ipp8u* pDst, int *pDstLen,
    Ipp8u *pHashTable, const Ipp8u* pDict, int dictLen))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsEncodeLZ4HCHashTableGetSize_8u
//  Purpose:    get size of buffer for Hash Table and for Prev Table
//
//  Arguments:
//      pHashTableSize        pointer to size of buffer for Hash Table
//      pPrevTableSize        pointer to size of buffer for Prev Table
//
//  Return:
//      ippStsNullPtrErr      any pointer is NULL
//      ippStsNoErr           no error detected
//
*/
IPPAPI(IppStatus, ippsEncodeLZ4HCHashTableGetSize_8u,(int *pHashTableSize, int *pPrevTableSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsEncodeLZ4HCHashTableInit_8u
//
//  Purpose:    init of Tables (Hash & Prev) for LZ4 encoding
//              in HC (High Compression) mode
//
//  Arguments:
//      ppHashTable     pointer to pointer to Tables (Hash & Prev)
//                      ppHashTables[0] = pHachTable
//                      ppHashTables[1] = pPrevTable
//
//  Return:
//      ippStsNullPtrErr  if any pointer is NULL
//      ippStsNoErr       no error detected
//
*/
IPPAPI(IppStatus, ippsEncodeLZ4HCHashTableInit_8u,(Ipp8u** ppHashTables))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsEncodeLZ4HC_8u
//  Purpose:    LZ4 encoder for HC (High Compression) mode
//
//  Arguments:
//      pSrc            pointer to source
//      srcIdx          index of start byte in source vector
//      pSrcLen         pointer to length of source / to length of proccesed input data
//      pDst            pointer to destination
//      pDstLen         pointer to length of destination buffer/ to length of compressed output data
//      ppHashTablep    pointer to pointer array (pHashTable & pPrevTable)
//                      ppHashTable[0] = pHashTable
//                      ppPrevTable[1] = pPrevTable
//      pDict           pointer to dictinary
//      dictLen         length of dictinary
//      level           compression level
//
//  Return:
//      ippStsNullPtrErr            one of the pointers is NULL
//      ippStsSizeErr               length of source is less or equal zero
//      ippStsBadArgErr             index of start byte is less then zero
//      ippStsNotSupportedModeErr   this case is not supprted
//      ippStsNoErr                 no error detected
*/

IPPAPI(IppStatus, ippsEncodeLZ4HC_8u,(const Ipp8u* pSrc, int srcIdx, int* pSrcLen, Ipp8u* pDst, int *pDstLen,
    Ipp8u **ppHashTables, const Ipp8u* pDict, int dictLen, int level))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDecodeLZ4_8u
//  Purpose:    LZ4 encoder
//
//  Arguments:
//      pSrc            pointer to source
//      srcLen          length of source
//      pDst            pointer to destination
//      pDstLen         pointer to size of buffer for destination / length of compressed data
//      dstIdx          index of start byte in desination vector
//      pDict           pointer to dictinary
//      dictLen         length of dictinary
//
//  Return:
//      ippStsNullPtrErr            one of the pointers is NULL
//      ippStsSizeErr               length of source or buffer destination is less or equal zero
//                                  or destination buffer length is insufficient
//      ippStsDstSizeLessExpected   desination buffer is too short for uncompressed data
//      ippStsSrcSizeLessExpected   source buffer data is incomplete
//      ippStsNoErr                 no error detected
//
*/
IPPAPI(IppStatus, ippsDecodeLZ4_8u,(const Ipp8u* pSrc, int srcLen, Ipp8u* pDst, int *pDstLen))
IPPAPI(IppStatus, ippsDecodeLZ4Dict_8u, (const Ipp8u* pSrc, int *pSrcLen, Ipp8u* pDst, int dstIdx, int *pDstLen, const Ipp8u* pDict, int dictSize))

/**************************************************
ZFP Definitions
***************************************************/

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsEncodeZfpGetStateSize_32f
//  Purpose:    get size of buffer for IppEncodeZfpState_32f state
//
//  Arguments:
//      pStateSize            pointer to size of IppEncodeZfpState_32f structure
//
//  Return:
//      ippStsNullPtrErr      pointer is NULL
//      ippStsNoErr           no error detected
//
*/
IPPAPI(IppStatus, ippsEncodeZfpGetStateSize_32f,(int *pStateSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsEncodeZfpInit_32f,
//              ippsEncodeZfpInitLong_32f
//
//  Purpose:    init of IppEncodeZfpState_32f state with default values
//              described in ippsSetZfpSet_32f function
//
//  Arguments:
//      pDst            pointer to destination data
//      dstLen          size of buffer for destination
//      pState          pointer to IppEncodeZfpState_32f spec
//
//  Return:
//      ippStsNoErr       no error detected
//      ippStsNullPtrErr  if pDst or pState pointer is NULL
//      ippStsSizeErr     length of destination buffer is less or equal zero
//
*/
IPPAPI(IppStatus, ippsEncodeZfpInit_32f,(Ipp8u *pDst, int dstLen, IppEncodeZfpState_32f *pState))
IPPAPI(IppStatus, ippsEncodeZfpInitLong_32f,(Ipp8u *pDst, Ipp64u dstLen, IppEncodeZfpState_32f *pState))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsEncodeZfpSet_32f
//
//  Purpose:    set of fields for IppEncodeZfpState_32f state
//
//  Arguments:
//      minBits         minimum number of bits for compressed block,
//                      default value is IppZFPMINBITS
//      maxBits         maximum number of bits for compressed block,
//                      default value is IppZFPMAXBITS
//      maxPrec         maximum level of precision,
//                      default value is IppZFPMAXPREC
//      minExp          minimum level of exponent,
//                      default value is IppZFPMINEXP
//      pState          pointer to IppEncodeZfpState_32f spec
//
//  Return:
//      ippStsNullPtrErr        if pState pointer is NULL
//      ippStsContextMatchErr   if context is not appropriate
//      ippStsNoErr             no error detected
//
*/
IPPAPI(IppStatus, ippsEncodeZfpSet_32f,(int minBits, int maxBits, int maxPrec,
    int minExp, IppEncodeZfpState_32f *pState))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsEncodeZfpSetAccuracy_32f
//
//  Purpose:    set of fields for IppEncodeZfpState_32f state
//              accordingly value of precision
//
//  Arguments:
//      precision       precision for encoding
//      pState          pointer to IppEncodeZfpState_32f spec
//
//  Return:
//      ippStsNullPtrErr        if pState pointer is NULL
//      ippStsContextMatchErr   if context is not appropriate
//      ippStsNoErr             no error detected
//
*/
IPPAPI(IppStatus, ippsEncodeZfpSetAccuracy_32f,(Ipp64f precision, IppEncodeZfpState_32f *pState))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsEncodeZfp444_32f
//
//  Purpose:    encoding of block 4x4x4 of Ipp32f type
//
//  Arguments:
//      pSrc            pointer to blcok
//      srcStep         row step
//      srcPlaneStep    plane step
//      pState          pointer to IppEncodeZfpState_32f spec
//
//  Return:
//      ippStsNullPtrErr        if pSrc or pState pointer is NULL
//      ippStsContextMatchErr   if context is not appropriate
//      ippStsNoErr             no error detected
//
*/
IPPAPI(IppStatus, ippsEncodeZfp444_32f,(const Ipp32f *pSrc, int srcStep, int srcPlaneStep, IppEncodeZfpState_32f *pState))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsEncodeZfpFlush_32f
//
//  Purpose:    put data from internal buffer to destination buffer
//
//  Arguments:
//      pState          pointer to IppEncodeZfpState_32f spec
//
//  Return:
//      ippStsNullPtrErr        if pState pointer is NULL
//      ippStsNoErr             no error detected
//
*/
IPPAPI(IppStatus, ippsEncodeZfpFlush_32f,(IppEncodeZfpState_32f *pState))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsEncodeZfpGetCompressedSize_32f,
//              ippsEncodeZfpGetCompressedSizeLong_32f
//
//  Purpose:    returns size in bytes of compressed data
//
//  Arguments:
//      pState          pointer to IppEncodeZfpState_32f spec
//      pCompressedSize pointer to compressed data size
//
//  Return:
//      ippStsNoErr             no error detected
//      ippStsContextMatchErr   if context is not appropriate
//      ippStsNullPtrErr        if pState or pCompressedSize pointer is NULL
//
*/
IPPAPI(IppStatus, ippsEncodeZfpGetCompressedSize_32f,(IppEncodeZfpState_32f *pState, int *pCompressedSize))
IPPAPI(IppStatus, ippsEncodeZfpGetCompressedSizeLong_32f,(IppEncodeZfpState_32f *pState, Ipp64u *pCompressedSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsEncodeZfpGetCompressedBitSize_32f
//
//  Purpose:    returns size in bits of compressed data
//
//  Arguments:
//      pState          pointer to IppEncodeZfpState_32f state structure
//      pCompressedBitSize pointer to compressed data size in bits
//
//  Return:
//      ippStsNoErr             no error detected
//      ippStsNullPtrErr        if pState or pCompressedBitSize pointer is NULL
//
*/
IPPAPI(IppStatus, ippsEncodeZfpGetCompressedBitSize_32f,(IppEncodeZfpState_32f *pState, Ipp64u* pCompressedBitSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDecodeZfpGetStateSize_32f
//  Purpose:    get size of buffer for IppDecodeZfpState_32f state
//
//  Arguments:
//      pStateSize            pointer to size of IppDecodeZfpState_32f structure
//
//  Return:
//      ippStsNullPtrErr      pointer is NULL
//      ippStsNoErr           no error detected
//
*/
IPPAPI(IppStatus, ippsDecodeZfpGetStateSize_32f,(int *pStateSize))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDecodeZfpInit_32f,
//              ippsDecodeZfpInitLong_32f
//
//  Purpose:    init of IppDecodeZfpState_32f state with default values
//              described in ippsSetZfpSet_32f function
//
//  Arguments:
//      pSrc            pointer to source data
//      srcLen          size of buffer for source data
//      pState          pointer to IppDecodeZfpState_32f spec
//
//  Return:
//      ippStsNullPtrErr  if pSrc or pState pointer is NULL
//      ippStsSizeErr     length of source buffer is less or equal zero
//      ippStsNoErr       no error detected
//
*/
IPPAPI(IppStatus, ippsDecodeZfpInit_32f,(const Ipp8u *pSrc, int srcLen, IppDecodeZfpState_32f *pState))
IPPAPI(IppStatus, ippsDecodeZfpInitLong_32f,(const Ipp8u *pSrc, Ipp64u srcLen, IppDecodeZfpState_32f *pState))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDecodeZfpSetAccuracy_32f
//
//  Purpose:    set of fields for IppDecodeZfpState_32f state
//              accordingly value of precision
//
//  Arguments:
//      precision       precision for encoding
//      pState          pointer to IppDecodeZfpState_32f spec
//
//  Return:
//      ippStsNullPtrErr        if pState pointer is NULL
//      ippStsContextMatchErr   if context is not appropriate
//      ippStsNoErr             no error detected
//
*/
IPPAPI(IppStatus, ippsDecodeZfpSetAccuracy_32f,(Ipp64f precision, IppDecodeZfpState_32f *pState))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDecodeZfpSet_32f
//
//  Purpose:    set of fields for IppDecodeZfpState_32f state
//
//  Arguments:
//      minBits         minimum number of bits for compressed block,
//                      default value is IppZFPMINBITS
//      maxBits         pointer to maximum number of bits for compressed block,
//                      default value is IppZFPMAXBITS
//      maxPrec         pointer to maximum level of precision,
//                      default value is IppZFPMAXPREC
//      minExp          pointer to minimum level of exponent,
//                      default value is IppZFPMINEXP
//      pState          pointer to IppDecodeZfpState_32f spec
//
//  Return:
//      ippStsNullPtrErr        if pState pointer is NULL
//      ippStsContextMatchErr   if context is not appropriate
//      ippStsNoErr             no error detected
//
*/
IPPAPI(IppStatus, ippsDecodeZfpSet_32f,(int minBits, int maxBits, int maxPrec,
    int minExp, IppDecodeZfpState_32f *pState))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDecodeZfp444_32f
//
//  Purpose:    encoding of block 4x4x4 of Ipp32f type
//
//  Arguments:
//      pState          pointer to IppDecodeZfpState_32f spec
//      pDst            pointer to destination
//      dstStep         row step
//      dstPlaneStep    plane step
//
//  Return:
//      ippStsNullPtrErr        if pSrc or pState pointer is NULL
//      ippStsContextMatchErr   if context is not appropriate
//      ippStsNoErr             no error detected
//
*/
IPPAPI(IppStatus, ippsDecodeZfp444_32f,(IppDecodeZfpState_32f *pState, Ipp32f *pDst, int dstStep, int dstPlaneStep))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsDecodeZfpGetDecompressedSize_32f,
//              ippsDecodeZfpGetDecompressedSizeLong_32f
//
//  Purpose:    returns size of decompressed data in bytes
//
//  Arguments:
//      pState          pointer to IppDecodeZfpState_32f spec
//      pDecompressedSize pointer to decompressed data size
//
//  Return:
//      ippStsNoErr             no error detected
//      ippStsNullPtrErr        if pState or pDecompressedSize pointer is NULL
//      ippStsContextMatchErr   if context is not appropriate
//
*/
IPPAPI(IppStatus, ippsDecodeZfpGetDecompressedSize_32f,(IppDecodeZfpState_32f *pState, int *pDecompressedSize))
IPPAPI(IppStatus, ippsDecodeZfpGetDecompressedSizeLong_32f,(IppDecodeZfpState_32f *pState, Ipp64u *pDecompressedSize))

#ifdef __cplusplus
}
#endif

#endif /* IPPDC_H__ */
