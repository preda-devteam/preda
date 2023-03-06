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

#ifndef IPPCORE_TL_H__ 
#define IPPCORE_TL_H__ 

#ifndef IPPDEFS_L_H__
    #include "ippdefs_l.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    OMP,
    TBB
} IppThreadingType;

typedef IppStatus(*functype_l)(IppSizeL i, void* arg);
typedef IppStatus(*functype)(int i, void* arg);

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippGetThreadingType (_T - Classic API style, _LT - Platform Aware API style)
//
//  Purpose:
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         Pointer to thrType is Null
//
//  Arguments:
//    thrType                  Pointer to memory location where to store current threading type 
*/

IPPAPI(IppStatus, ippGetThreadingType_LT, (IppThreadingType* thrType))
IPPAPI(IppStatus, ippGetThreadingType_T,  (IppThreadingType* thrType))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippGetNumThreads (_T - Classic API style, _LT - Platform Aware API style)
//
//  Purpose:
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         Pointer to numThr is Null
//
//  Arguments:
//    pNumThr                  Pointer to memory location where to store current numThr 
*/

IPPAPI(IppStatus, ippGetNumThreads_LT, (int* pNumThr))
IPPAPI(IppStatus, ippGetNumThreads_T,  (int* pNumThr))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippGetThreadIdx (_T - Classic API style, _LT - Platform Aware API style)
//
//  Purpose:
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         Pointer to numThr is Null
//
//  Arguments:
//    pNumThr                  Pointer to memory location where to store current numThr 
*/

IPPAPI(IppStatus, ippGetThreadIdx_LT, (int* pThrIdx))
IPPAPI(IppStatus, ippGetThreadIdx_T,  (int* pThrIdx))

/* ////////////////////////////////////////////////////////////////////////////
//  Name:       ippParallelFor (_T - Classic API style, _LT - Platform Aware API style)
//
//  Purpose:
//
//  Return:
//    ippStsNoErr              Ok
//    ippStsNullPtrErr         Pointer to arg or func is Null
//    any other output depending on func output
//
//  Arguments:
//    numTiles                  number of tiles
//    func                      pointer to function to use in cycle
//    arg                       pointer to the structure containing arguments for function above 
*/

IPPAPI(IppStatus, ippParallelFor_LT, (IppSizeL numTiles, void* arg, functype_l func))
IPPAPI(IppStatus, ippParallelFor_T,  (int numTiles, void* arg, functype func))

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IPPCORE_TL_H__  */
