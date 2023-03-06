/* 
// Copyright 2002-2020 Intel Corporation All Rights Reserved.
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
//              String Manipulations Library (ippCH)
// 
// 
*/


#if !defined( IPPCH_H__ ) || defined( _OWN_BLDPCS )
#define IPPCH_H__

#ifndef IPPDEFS_H__
  #include "ippdefs.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if !defined( IPP_NO_DEFAULT_LIB )
  #if defined( _IPP_SEQUENTIAL_DYNAMIC )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippch" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippcore" )
  #elif defined( _IPP_SEQUENTIAL_STATIC )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippchmt" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippsmt" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippvmmt" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "ippcoremt" )
  #elif defined( _IPP_PARALLEL_DYNAMIC )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippch" )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippcore" )
  #elif defined( _IPP_PARALLEL_STATIC )
    #pragma comment( lib, __FILE__ "/../../lib/" INTEL_PLATFORM "threaded/ippchmt" )
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
//  Name:       ippchGetLibVersion
//  Purpose:    getting of the library version
//  Returns:    the structure of information about version
//              of ippCH library
//  Parameters:
//
//  Notes:      not necessary to release the returned structure
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI( const IppLibraryVersion*, ippchGetLibVersion, (void) )

/* /////////////////////////////////////////////////////////////////////////////
//                String Functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsFind_8u
//              ippsFindC_8u
//              ippsFindRev_8u
//              ippsFindRevC_8u
//
//  Purpose:    Finds the match for string of elements or single element
//              within source string in direct or reverse direction
//
//  Arguments:
//     pSrc    - pointer to the source string
//     len     - source string length
//     pFind   - pointer to the searching string
//     lenFind - searching string length
//     valFind - searching element
//     pIndex  - pointer to the result index:
//               *pIndex = index of first occurrence ;
//               *pIndex = -1 if no match;
//
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  pSrc, pFind or pIndex are NULL
//   ippStsLengthErr   len or lenFind are negative
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsFind_8u,  (const Ipp8u* pSrc, int len,
                                  const Ipp8u* pFind, int lenFind,
                                  int *pIndex))
IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsFindC_8u,  (const Ipp8u* pSrc, int len,
                                   Ipp8u valFind, int *pIndex))
IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsFindRev_8u,  (const Ipp8u* pSrc, int len,
                                     const Ipp8u* pFind, int lenFind,
                                     int *pIndex))
IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsFindRevC_8u,  (const Ipp8u* pSrc, int len,
                                      Ipp8u valFind, int *pIndex))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsFind_Z_8u
//              ippsFindC_Z_8u
//
//  Purpose:    Finds the match for zero-ended string of elements or single element
//              within source zero-ended string in direct or reverse direction
//
//  Arguments:
//     pSrcZ   - pointer to the source zero-ended string
//     pFindZ  - pointer to the searching zero-ended string
//     valFind - searching element
//     pIndex  - pointer to the result index:
//               *pIndex = index of first occurrence;
//               *pIndex = -1 if no match;
//
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  pSrcZ, pFindZ or pIndex are NULL
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsFind_Z_8u,   (const Ipp8u* pSrcZ,
                                     const Ipp8u* pFindZ, int *pIndex))
IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsFindC_Z_8u,  (const Ipp8u* pSrcZ,
                                     Ipp8u valFind, int *pIndex))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsCompare_8u
//
//  Purpose:    Compares two strings element-by-element
//
//  Arguments:
//     pSrc1   - pointer to the first string
//     pSrc2   - pointer to the second string
//     len     - string length to compare
//     pResult - pointer to the result:
//               *pResult =  0 if src1 == src2;
//               *pResult = >0 if src1 >  src2;
//               *pResult = <0 if src1 <  src2;
//
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  pSrc1, pSrc2 or pResult are NULL
//   ippStsLengthErr   len is negative
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsCompare_8u,  (const Ipp8u* pSrc1, const Ipp8u* pSrc2,
                                     int len, int *pResult))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsEqual_8u
//
//  Purpose:    Compares two strings element-by-element
//
//  Arguments:
//     pSrc1   - pointer to the first string
//     pSrc2   - pointer to the second string
//     len     - string length to compare
//     pResult - pointer to the result:
//               *pResult =  1 if src1 == src2;
//               *pResult =  0 if src1 != src2;
//
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  pSrc1, pSrc2 or pResult are NULL
//   ippStsLengthErr   len is negative
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsEqual_8u,  (const Ipp8u* pSrc1, const Ipp8u* pSrc2,
                                   int len, int *pResult))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsTrimC_8u_I
//
//  Purpose:    Deletes an odd symbol at the end and the beginning of a string
//              in-place
//
//  Arguments:
//     pSrcDst - pointer to the string
//     pLen    - pointer to the string length:
//               *pLen = source length on input;
//               *pLen = destination length on output;
//     odd     - odd symbol
//
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  pSrcDst or pLen are NULL
//   ippStsLengthErr   *pLen is negative
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsTrimC_8u_I,  (Ipp8u* pSrcDst, int* pLen, Ipp8u odd ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsTrimC_8u
//
//  Purpose:    Deletes an odd symbol at the end and the beginning of a string
//
//  Arguments:
//     pSrc    - pointer to the source string
//     srcLen  - source string length
//     odd     - odd symbol
//     pDst    - pointer to the destination string
//     pDstLen - pointer to the destination string length:
//               *pDstLen doesn't use as input value;
//               *pDstLen = destination length on output;
//
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  pSrcDst, pDst or pDstLen are NULL
//   ippStsLengthErr   srcLen is negative
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsTrimC_8u,  (const Ipp8u* pSrc, int srcLen, Ipp8u odd,
                                   Ipp8u* pDst, int* pDstLen ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsUppercaseLatin_8u_I
//              ippsLowercaseLatin_8u_I
//              ippsLowercaseLatin_8u
//              ippsUppercaseLatin_8u
//
//  Purpose:    Forms an uppercase or lowercase version of the ASCII string
//
//  Arguments:
//     pSrc    - pointer to the source string
//     pDst    - pointer to the destination string
//     pSrcDst - pointer to the string for in-place operation
//     len     - string length
//
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  pSrc, pDst or pSrcDst are NULL;
//   ippStsLengthErr   len is negative;
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsUppercaseLatin_8u_I, ( Ipp8u* pSrcDst, int len ))
IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsLowercaseLatin_8u_I, ( Ipp8u* pSrcDst, int len ))
IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsLowercaseLatin_8u,  (const Ipp8u* pSrc, Ipp8u* pDst, int len))
IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsUppercaseLatin_8u,  (const Ipp8u* pSrc, Ipp8u* pDst, int len))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsHash_8u32u        ippsHash_16u32u
//
//  Purpose:    Calculates hashed value so that different strings yield different
//              values:
//              for (i=0; i<len; i++) hash = (hash << 1) ^ src[i];
//
//  Arguments:
//     pSrc     - pointer to the source string
//     len      - source string length
//     pHashVal - pointer to the result value
//
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  pSrc or pHashVal are NULL
//   ippStsLengthErr   len is negative
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsHash_8u32u,  (const Ipp8u* pSrc, int len, Ipp32u* pHashVal ))
IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsHash_16u32u, (const Ipp16u* pSrc, int len, Ipp32u* pHashVal ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsHashSJ2_8u32u         ippsHashSJ2_16u32u
//
//  Purpose:    Calculates hashed value so that different strings yield different
//              values:
//              for (i=0; i<len; i++) hash =
//
//  Arguments:
//     pSrc     - pointer to the source string
//     len      - source string length
//     pHashVal - pointer to the result value
//
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  pSrc or pHashVal are NULL
//   ippStsLengthErr   len is negative
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus,ippsHashSJ2_8u32u, (const Ipp8u* pSrc, int len, Ipp32u* pHashVal))
IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus,ippsHashSJ2_16u32u, (const Ipp16u* pSrc, int len, Ipp32u* pHashVal))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsHashMSCS_8u32u        ippsHashMSCS_16u32u
//
//  Purpose:    Calculates hashed value so that different strings yield different
//              values:
//              for (i=0; i<len; i++) hash =
//
//  Arguments:
//     pSrc     - pointer to the source string
//     len      - source string length
//     pHashVal - pointer to the result value
//
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  pSrc or pHashVal are NULL
//   ippStsLengthErr   len is negative
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus,ippsHashMSCS_8u32u, (const Ipp8u* pSrc, int len, Ipp32u* pHashVal))
IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus,ippsHashMSCS_16u32u, (const Ipp16u* pSrc, int len, Ipp32u* pHashVal))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsConcat_8u
//
//  Purpose:    Concatenates two strings together
//
//  Arguments:
//     pSrc1   - pointer to the first source string
//     len1    - first source string length
//     pSrc2   - pointer to the second source string
//     len2    - second source string length
//     pDst    - pointer to the destination string
//
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  pSrc1, pSrc2 or pDst are NULL
//   ippStsLengthErr   len1 or len2 are negative
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsConcat_8u,  (const Ipp8u* pSrc1, int len1,
                                    const Ipp8u* pSrc2, int len2,
                                    Ipp8u* pDst))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsConcat_8u_D2L   ippsConcat_16u_D2L
//
//  Purpose:    Concatenates several strings together
//
//  Arguments:
//     pSrc    - pointer to the array of source strings
//     srcLen  - pointer to the array of source strings' lengths
//     numSrc  - number of source strings
//     pDst    - pointer to the destination string
//
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  pSrc, srcLen or pDst are NULL;
//                     pSrc[i] is NULL for i < numSrc
//   ippStsLengthErr   srcLen[i] is negative for i < numSrc
//   ippStsSizeErr     numSrc is not positive
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsConcat_8u_D2L,  (const Ipp8u* const pSrc[], const int srcLen[], int numSrc,
                                        Ipp8u* pDst ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsConcatC_8u_D2L
//
//  Purpose:    Concatenates several strings together and separates them
//              by the symbol delimiter
//
//  Arguments:
//     pSrc    - pointer to the array of source strings
//     srcLen  - pointer to the array of source strings' lengths
//     numSrc  - number of source strings
//     delim   - delimiter
//     pDst    - pointer to the destination string
//
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  pSrc, srcLen or pDst are NULL;
//                     pSrc[i] is NULL for i < numSrc
//   ippStsLengthErr   srcLen[i] is negative for i < numSrc
//   ippStsSizeErr     numSrc is not positive
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsConcatC_8u_D2L,  (const Ipp8u* const pSrc[], const int srcLen[], int numSrc,
                                         Ipp8u delim, Ipp8u* pDst ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsSplitC_8u_D2L
//
//  Purpose:    Splits source string to several destination strings
//              using the symbol delimiter; all delimiters are significant,
//              in the case of double delimiter empty string is inserted.
//
//  Arguments:
//     pSrc    - pointer to the source string
//     srcLen  - source string length
//     delim   - delimiter
//     pDst    - pointer to the array of destination strings
//     dstLen  - pointer to the array of destination strings' lengths
//     pNumDst - pointer to the number of destination strings:
//               *pNumDst = initial number of destination strings on input;
//               *pNumDst = number of splitted strings on output;
//
//  Return:
//     ippStsNoErr       Ok
//  ERRORS:
//     ippStsNullPtrErr  pSrc, pDst, dstLen or pNumDst are NULL;
//                       pDst[i] is NULL for i < number of splitted strings
//     ippStsLengthErr   srcLen is negative;
//                       dstLen[i] is negative for i < number of splitted strings
//     ippStsSizeErr     *pNumDst is not positive
//  WARNINGS:
//     ippStsOvermuchStrings  the initial number of destination strings is less
//                            than the number of splitted strings;
//                            number of destination strings is truncated to
//                            initial number in this case
//     ippStsOverlongString   the length of one of destination strings is less than
//                            length of corresponding splitted string;
//                            splitted string is truncated to destination length
//                            in this case
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsSplitC_8u_D2L,  (const Ipp8u* pSrc, int srcLen, Ipp8u delim,
                                        Ipp8u* pDst[], int dstLen[], int* pNumDst))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsFindCAny_8u
//              ippsFindRevCAny_8u
//
//  Purpose:    Reports the index of the first/last occurrence in
//              the vector of any value in a specified array.
//
//  Arguments:
//     pSrc    - The pointer of vector to find.
//     len     - The length of the vector.
//     pAnyOf  - A pointer of array containing one or more values to seek.
//     lenFind - The length of array.
//     pIndex  - The positive integer index of the first occurrence in
//               the vector where any value in pAnyOf was found;
//               otherwise, -1 if no value in pAnyOf was found.
//
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  Any of pointers is NULL.
//   ippStsLengthErr   len or lenAnyOf are negative.
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsFindCAny_8u, ( const Ipp8u* pSrc, int len,
        const Ipp8u* pAnyOf, int lenAnyOf, int* pIndex ))
IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsFindRevCAny_8u, ( const Ipp8u* pSrc, int len,
        const Ipp8u* pAnyOf, int lenAnyOf, int* pIndex ))


/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsReplaceC_8u
//
//  Purpose:    Replaces all occurrences of a specified value in
//              the vector with another specified value.
//
//  Arguments:
//     pSrc    - The pointer of vector to replace.
//     pDst    - The ponter of replaced vector.
//     len     - The length of the vector.
//     oldVal  - A value to be replaced.
//     newVal  - A value to replace all occurrences of oldVal.
//
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  Any of pointers is NULL.
//   ippStsLengthErr   len is negative.
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsReplaceC_8u, ( const Ipp8u* pSrc, Ipp8u* pDst, int len,
        Ipp8u oldVal, Ipp8u newVal ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsTrimCAny_8u
//              ippsTrimEndCAny_8u
//              ippsTrimStartCAny_8u
//
//  Purpose:    Removes all occurrences of a set of specified values
//              from:
//                TrimCAny  - the beginning and end of the vector.
//                TrimEndCAny   - the end of the vector.
//                TrimStartCAny - the beginning of the vector.
//
//  Arguments:
//     pSrc    - The pointer of src vector to remove.
//     srcLen  - The length of the src vector.
//     pTrim   - An array of values to be removed.
//     trimLen - The length of the array values.
//     pDst    - The pointer of dst vector to result save.
//     pDstLen - The result length of the dst vector.
//
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  Any of pointers is NULL.
//   ippStsLengthErr   srcLen or trimLen are negative.
//
//  Note:
//   The length of the pDst should be sufficient;
//   if values not found, *pDstLen = srcLen.
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsTrimCAny_8u, ( const Ipp8u* pSrc, int srcLen,
        const Ipp8u* pTrim, int trimLen, Ipp8u* pDst, int* pDstLen ))
IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsTrimEndCAny_8u, ( const Ipp8u* pSrc, int srcLen,
        const Ipp8u* pTrim, int trimLen, Ipp8u* pDst, int* pDstLen ))
IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsTrimStartCAny_8u, ( const Ipp8u* pSrc, int srcLen,
        const Ipp8u* pTrim, int trimLen, Ipp8u* pDst, int* pDstLen ))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsCompareIgnoreCaseLatin_8u
//
//  Purpose:    Compares two ASCII strings element-by-element
//
//  Arguments:
//     pSrc1   - pointer to the first string
//     pSrc2   - pointer to the second string
//     len     - string length to compare
//     pResult - pointer to the result:
//               *pResult = 0 if src1 == src2;
//               *pResult > 0 if src1 >  src2;
//               *pResult < 0 if src1 <  src2;
//
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  pSrc1, pSrc2 or pResult is NULL
//   ippStsLengthErr   len is negative
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsCompareIgnoreCaseLatin_8u,  (const Ipp8u* pSrc1, const Ipp8u* pSrc2, int len,
                                                    int *pResult))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsInsert_8u_I
//              ippsInsert_8u
//
//  Purpose:    Inserts one string at a specified index position in other string
//
//  Arguments:
//     pSrc       - pointer to the source string
//     srcLen     - source string length
//     pInsert    - pointer to the string to be inserted
//     insertLen  - length of the string to be inserted
//     pDst       - pointer to the destination string
//     pSrcDst    - pointer to the string for in-place operation
//     pSrcDstLen - pointer to the string length:
//                 *pSrcDstLen = source length on input;
//                 *pSrcDstLen = destination length on output;
//     startIndex - index of start position
//
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  pSrc, pInsert, pDst, pSrcDst or pSrcDstLen is NULL
//   ippStsLengthErr   srcLen, insertLen, *pSrcDstLen or startIndex is negative Or
//                     startIndex is greater than srcLen or *pSrcDstLen
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsInsert_8u_I,  (const Ipp8u* pInsert, int insertLen, Ipp8u* pSrcDst,
                                      int* pSrcDstLen, int startIndex))
IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsInsert_8u,    (const Ipp8u* pSrc, int srcLen, const Ipp8u* pInsert,
                                      int insertLen, Ipp8u* pDst, int startIndex))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsRemove_8u_I
//              ippsRemove_8u
//
//  Purpose:    Deletes a specified number of characters from the string
//              beginning at a specified position.
//
//  Arguments:
//     pSrc       - pointer to the source string
//     srcLen     - source string length
//     pDst       - pointer to the destination string
//     pSrcDst    - pointer to the string for in-place operation
//     pSrcDstLen - pointer to the string length:
//                 *pSrcDstLen = source length on input;
//                 *pSrcDstLen = destination length on output;
//     startIndex - index of start position
//     len        - number of characters to be deleted
//
//  Return:
//   ippStsNoErr       Ok
//   ippStsNullPtrErr  pSrc, pDst, pSrcDst or pSrcDstLen are NULL
//   ippStsLengthErr   srcLen, *pSrcDstLen, len or startIndex is negative Or
//                     (startIndex + len) is greater than srcLen or *pSrcDstLen
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsRemove_8u_I,  (Ipp8u* pSrcDst, int* pSrcDstLen, int startIndex, int len))
IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI (IppStatus, ippsRemove_8u,    (const Ipp8u* pSrc, int srcLen, Ipp8u* pDst, int startIndex,
                                      int len))

/* /////////////////////////////////////////////////////////////////////////////
// Name:                ippsRegExpGetSize
// Purpose:             Computes the size of necessary memory (in bytes) for
//                      structure containing internal form of regular expression
//
// Parameters:
//    pPattern          Pointer to the pattern of regular expression
//    pRegExpStateSize  Pointer to the computed size of structure containing
//                      internal form of regular expression
//
// Return:
//    ippStsNullPtrErr  One or several pointer(s) is NULL
//    ippStsNoErr       No errors
//
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI(IppStatus, ippsRegExpGetSize, ( const char* pPattern, int* pRegExpStateSize ))

/* /////////////////////////////////////////////////////////////////////////////
// Name:                ippsRegExpInit
// Purpose:             Compiles a pattern into the internal form consideration
//                      corresponding options and writes it into the pRegExpState
//
// Parameters:
//    pPattern          Pointer to the pattern of regular expression
//    pOptions          Pointer to options for compiling and executing
//                      regular expression (possible values 'i','s','m','x','g')
//                      It should be NULL if no options are required.
//    pRegExpState      Pointer to the structure containing internal form of
//                      a regular expression.
//    pErrOffset        Pointer to offset into the pattern if compiling is break
//
// Return:
//    ippStsNoErr               No errors
//    ippStsNullPtrErr          One or several pointer(s) is NULL
//    ippStsRegExpOptionsErr    Options are incorrect
//    ippStsRegExpQuantifierErr Error caused by using wrong quantifier
//    ippStsRegExpGroupingErr   Error caused by using wrong grouping
//    ippStsRegExpBackRefErr    Error caused by using wrong back reference
//    ippStsRegExpChClassErr    Error caused by using wrong character class
//    ippStsRegExpMetaChErr     Error caused by using wrong metacharacter
//
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI(IppStatus, ippsRegExpInit, ( const char* pPattern, const char* pOptions,
                                    IppRegExpState*  pRegExpState, int* pErrOffset ))

/* /////////////////////////////////////////////////////////////////////////////
// Name:                ippsRegExpSetMatchLimit
// Purpose:             Changes initial value of the matches kept in stack
//
// Parameters:
//    matchLimit        New value of the matches kept in stack
//    pRegExpState      Pointer to the structure containing internal form of
//                      a regular expression
//
// Return:
//    ippStsNullPtrErr  Pointer is NULL
//    ippStsNoErr       No errors
//
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI(IppStatus, ippsRegExpSetMatchLimit, ( int matchLimit, IppRegExpState* pRegExpState ))

/* /////////////////////////////////////////////////////////////////////////////
// Name:                ippsRegExpSetFormat
// Purpose:             Changes initial value of the matches kept in stack
//
// Parameters:
//    fmt               New source encoding mode
//    pRegExpState      Pointer to the structure containing internal form of
//                      a regular expression
//
// Return:
//    ippStsNullPtrErr  Pointer is NULL.
//    ippStsRangeErr    When
//    ippStsNoErr       No errors
//
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI(IppStatus, ippsRegExpSetFormat, ( IppRegExpFormat fmt, IppRegExpState* pRegExpState ))

/* /////////////////////////////////////////////////////////////////////////////
// Name:                ippsRegExpFind_8u
// Purpose:             Looks for the occurrences of the substrings matching
//                      the specified regular expression.
//
// Parameters:
//    pSrc              Pointer to the source string
//    srcLen            Number of elements in the source string.
//    pRegExpState      Pointer to the structure containing internal form of
//                      a regular expression
//    pFind             Array of pointers to the matching substrings
//    pNumFind          Size of the array pFind on input,
//                      number of matching substrings on output.
//
// Return:
//    ippStsNullPtrErr          One or several pointer(s) is NULL
//    ippStsSizeErr             Length of the source vector is less zero or or
//                              pNumFind is less than or equal to 0
//    ippStsRegExpErr           The structure pRegExpState contains wrong data
//    ippStsRegExpMatchLimitErr The match limit has been exhausted
//    ippStsNoErr               No errors
//
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI(IppStatus, ippsRegExpFind_8u, ( const Ipp8u* pSrc, int srcLen, IppRegExpState* pRegExpState,
                                       IppRegExpFind* pFind, int* pNumFind ))


/* /////////////////////////////////////////////////////////////////////////////
// Name:                ippsConvertUTF
// Purpose:             Convert UTF16BE or UTF16LE format to UTF8 and vice versa.
//
// Parameters:
//    pSrc     Pointer to the input vector.
//    pSrcLen  Length of the pSrc vector on input and its used length on output.
//    BEFlag   Flag to indicate UTF16BE format. 0 means UTF16LE format.
//    pDst     Pointer to the output vector.
//    pDstLen  Length of the pDst vector on input and its used length on output.
//
// Return:
//    ippStsNullPtrErr          One or several pointer(s) is NULL
//    ippStsNoErr               No errors
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI(IppStatus, ippsConvertUTF_8u16u,( const Ipp8u* pSrc, Ipp32u *pSrcLen, Ipp16u* pDst, Ipp32u *pDstLen, int BEFlag))
IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI(IppStatus, ippsConvertUTF_16u8u,( const Ipp16u* pSrc, Ipp32u *pSrcLen, Ipp8u* pDst, Ipp32u *pDstLen, int BEFlag))


/* /////////////////////////////////////////////////////////////////////////////
// Name:                ippsRegExpReplaceGetSize
// Purpose:             Computes the size the find and replace engine memory.
//
// Parameters:
//    pSrcReplacement   Pointer to the input null-terminated replace pattern.
//    pSize             Pointer to the computed size of the replace engine memory.
//
// Return:
//    ippStsNullPtrErr  pSize pointer is NULL
//    ippStsNoErr       No errors
//
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI(IppStatus, ippsRegExpReplaceGetSize, ( const Ipp8u* pSrcReplacement, Ipp32u *pSize))

/* /////////////////////////////////////////////////////////////////////////////
// Name:                ippsRegExpReplaceInit
// Purpose:             Initialize internal form of find and replace engine.
//
// Parameters:
//    pSrcReplacement   Pointer to the input null-terminated replace pattern.
//    pReplaceState     Pointer to the memory allocated for the find and replace
//                      engine structure of size  after ippsRegExpReplaceGetSize function.
//
// Return:
//    ippStsNoErr       No errors
//    ippStsNullPtrErr  pReplaceState pointer is NULL
//
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI(IppStatus, ippsRegExpReplaceInit, ( const Ipp8u* pSrcReplacement, IppRegExpReplaceState *pReplaceState))

/* /////////////////////////////////////////////////////////////////////////////
// Name:                ippsRegExpReplace_8u
// Purpose:             Performs find and replace.
//
// Parameters:
//    pSrc            Pointer to the source string.
//    pSrcLenOffset   Length of the pSrc vector on input and its used length on output.
//    pRegExpState    Pointer to the compiled pattern structure.
//    pReplaceState   Pointer to the memory allocated for the find and replace engine structure.
//    pDst            Pointer to the destination string.
//    pDstLen         Length of the pDst vector on input and its used length on output.
//    pFind           Array of pointers to the matching substrings.
//    pNumFind        Size of the array pFind on input, number of matching substrings on output.
//
// Return:
//    ippStsNoErr       Indicates no error.
//    ippStsNullPtrErr  One or several pointer(s) is NULL.
//    ippStsSizeErr     Indicates an error when value in pSrcLen or pDstLen is less or equal to zero.
//
*/

IPP_DEPRECATED("is deprecated. All functions in the ippCH domain are obsolete and will be removed in one of the future IPP releases. Use the following link for opening a ticket and providing feedback: https://supporttickets.intel.com/ if you have concerns.")\
IPPAPI(IppStatus, ippsRegExpReplace_8u, ( const Ipp8u* pSrc, int *pSrcLenOffset, Ipp8u *pDst, int *pDstLen, IppRegExpFind* pFind, int* pNumFind, IppRegExpState* pRegExpState,
       IppRegExpReplaceState *pReplaceState ))


#ifdef __cplusplus
}
#endif

#endif /* IPPCH_H__ */

