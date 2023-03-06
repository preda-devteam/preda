#pragma once
#include "ippi90legacy_redef.h"
#include "ippi90legacy.h"
namespace ipp
{
	namespace ipp_cpp
	{

#define IPPI_WRAP inline IppStatus

IPPI_WRAP ippiCopy_C1R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int 
                             dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiCopy_8u_C1R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiCopy_C3R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int 
                             dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiCopy_8u_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiCopy_C4R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int 
                             dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiCopy_8u_C4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiCopy_C1R(const Ipp16s* pSrc, int srcStep, Ipp16s* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiCopy_16s_C1R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiCopy_C3R(const Ipp16s* pSrc, int srcStep, Ipp16s* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiCopy_16s_C3R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiCopy_C4R(const Ipp16s* pSrc, int srcStep, Ipp16s* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiCopy_16s_C4R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiCopy_C1R(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiCopy_32f_C1R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiCopy_C3R(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiCopy_32f_C3R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiCopy_C4R(const Ipp32f* pSrc, int srcStep, Ipp32f* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiCopy_32f_C4R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiScale_C1R(const Ipp8u* pSrc, int srcStep, Ipp16u* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiScale_8u16u_C1R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiScale_C1R(const Ipp8u* pSrc, int srcStep, Ipp16s* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiScale_8u16s_C1R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiScale_C1R(const Ipp8u* pSrc, int srcStep, Ipp32s* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiScale_8u32s_C1R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiScale_C1R(const Ipp8u* pSrc, int srcStep, Ipp32f* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiScale_8u32f_C1R)(pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->FloatMin, GetEnv()->FloatMax);
}
IPPI_WRAP ippiScale_C1R(const Ipp16u* pSrc, int srcStep, Ipp8u* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiScale_16u8u_C1R)(pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->HintAlgorithm);
}
IPPI_WRAP ippiScale_C1R(const Ipp16s* pSrc, int srcStep, Ipp8u* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiScale_16s8u_C1R)(pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->HintAlgorithm);
}
IPPI_WRAP ippiScale_C1R(const Ipp32s* pSrc, int srcStep, Ipp8u* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiScale_32s8u_C1R)(pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->HintAlgorithm);
}
IPPI_WRAP ippiScale_C1R(const Ipp32f* pSrc, int srcStep, Ipp8u* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiScale_32f8u_C1R)(pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->FloatMin, GetEnv()->FloatMax);
}
IPPI_WRAP ippiScale_C3R(const Ipp8u* pSrc, int srcStep, Ipp16u* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiScale_8u16u_C3R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiScale_C3R(const Ipp8u* pSrc, int srcStep, Ipp16s* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiScale_8u16s_C3R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiScale_C3R(const Ipp8u* pSrc, int srcStep, Ipp32s* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiScale_8u32s_C3R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiScale_C3R(const Ipp8u* pSrc, int srcStep, Ipp32f* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiScale_8u32f_C3R)(pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->FloatMin, GetEnv()->FloatMax);
}
IPPI_WRAP ippiScale_C3R(const Ipp16u* pSrc, int srcStep, Ipp8u* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiScale_16u8u_C3R)(pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->HintAlgorithm);
}
IPPI_WRAP ippiScale_C3R(const Ipp16s* pSrc, int srcStep, Ipp8u* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiScale_16s8u_C3R)(pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->HintAlgorithm);
}
IPPI_WRAP ippiScale_C3R(const Ipp32s* pSrc, int srcStep, Ipp8u* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiScale_32s8u_C3R)(pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->HintAlgorithm);
}
IPPI_WRAP ippiScale_C3R(const Ipp32f* pSrc, int srcStep, Ipp8u* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiScale_32f8u_C3R)(pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->FloatMin, GetEnv()->FloatMax);
}
IPPI_WRAP ippiScale_C4R(const Ipp8u* pSrc, int srcStep, Ipp16u* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiScale_8u16u_C4R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiScale_C4R(const Ipp8u* pSrc, int srcStep, Ipp16s* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiScale_8u16s_C4R)(pSrc, srcStep, pDst, dstStep, roiSize);
}

IPPI_WRAP ippiScale_C4R(const Ipp8u* pSrc, int srcStep, Ipp32s* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiScale_8u32s_C4R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiScale_C4R(const Ipp8u* pSrc, int srcStep, Ipp32f* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiScale_8u32f_C4R)(pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->FloatMin, GetEnv()->FloatMax);
}
IPPI_WRAP ippiScale_C4R(const Ipp16u* pSrc, int srcStep, Ipp8u* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiScale_16u8u_C4R)(pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->HintAlgorithm);
}
IPPI_WRAP ippiScale_C4R(const Ipp16s* pSrc, int srcStep, Ipp8u* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiScale_16s8u_C4R)(pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->HintAlgorithm);
}
IPPI_WRAP ippiScale_C4R(const Ipp32s* pSrc, int srcStep, Ipp8u* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiScale_32s8u_C4R)(pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->HintAlgorithm);
}
IPPI_WRAP ippiScale_C4R(const Ipp32f* pSrc, int srcStep, Ipp8u* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiScale_32f8u_C4R)(pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->FloatMin, GetEnv()->FloatMax);
}
IPPI_WRAP ippiCopy_P3C3R(const Ipp8u* const pSrc[3], int srcStep,
	Ipp8u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiCopy_8u_P3C3R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiCopy_P3C3R(const Ipp16s* const pSrc[3], int srcStep,
	Ipp16s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiCopy_16s_P3C3R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiCopy_P3C3R(const Ipp32f* const pSrc[3], int srcStep,
	Ipp32f* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiCopy_32f_P3C3R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiCopy_P4C4R(const Ipp8u* const pSrc[4], int srcStep,
	Ipp8u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiCopy_8u_P4C4R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiCopy_P4C4R(const Ipp16s* const pSrc[4], int srcStep,
	Ipp16s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiCopy_16s_P4C4R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiCopy_P4C4R(const Ipp32f* const pSrc[4], int srcStep,
	Ipp32f* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiCopy_32f_P4C4R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRGBToGray_C3C1R(const Ipp8u* pSrc, int srcStep, Ipp8u*
	pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRGBToGray_8u_C3C1R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRGBToGray_C3C1R(const Ipp16u* pSrc, int srcStep, Ipp16u*
	pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRGBToGray_16u_C3C1R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRGBToGray_C3C1R(const Ipp16s* pSrc, int srcStep, Ipp16s*
	pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRGBToGray_16s_C3C1R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRGBToGray_C3C1R(const Ipp32f* pSrc, int srcStep, Ipp32f*
	pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRGBToGray_32f_C3C1R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiSet_C1R(Ipp8u value, Ipp8u* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiSet_8u_C1R)(value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiSet_C1R(Ipp16s value, Ipp16s* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiSet_16s_C1R)(value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiSet_C1R(Ipp32f value, Ipp32f* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiSet_32f_C1R)(value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiCopy_C3AC4R(const Ipp8u* pSrc, int srcStep, Ipp8u* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiCopy_8u_C3AC4R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiCopy_C3AC4R(const Ipp16s* pSrc, int srcStep, Ipp16s*
	pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiCopy_16s_C3AC4R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiCopy_C3AC4R(const Ipp32f* pSrc, int srcStep, Ipp32f*
	pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiCopy_32f_C3AC4R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRGBToGray_AC4C1R(const Ipp8u* pSrc, int srcStep, Ipp8u*
	pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRGBToGray_8u_AC4C1R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRGBToGray_AC4C1R(const Ipp16u* pSrc, int srcStep, Ipp16u*
	pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRGBToGray_16u_AC4C1R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRGBToGray_AC4C1R(const Ipp16s* pSrc, int srcStep, Ipp16s*
	pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRGBToGray_16s_AC4C1R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRGBToGray_AC4C1R(const Ipp32f* pSrc, int srcStep, Ipp32f*
	pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRGBToGray_32f_AC4C1R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiCopy_AC4C3R(const Ipp8u* pSrc, int srcStep, Ipp8u* pDst,
	int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiCopy_8u_AC4C3R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiCopy_AC4C3R(const Ipp16s* pSrc, int srcStep, Ipp16s*
	pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiCopy_16s_AC4C3R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiCopy_AC4C3R(const Ipp32f* pSrc, int srcStep, Ipp32f*
	pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiCopy_32f_AC4C3R)(pSrc, srcStep, pDst, dstStep, roiSize);
}

/* ///////////////////////////////////////////////////////////////////////////
//             Linear Filters
/////////////////////////////////////////////////////////////////////////// */
/* /////////////////////////////////////////////////////////////////////////////
// Name:   ippiFilterBox_8u_C1R
//         ippiFilterBox_8u_C3R
//         ippiFilterBox_8u_AC4R
//         ippiFilterBox_16s_C1R
//         ippiFilterBox_16s_C3R
//         ippiFilterBox_16s_AC4R
//         ippiFilterBox_32f_C1R
//         ippiFilterBox_32f_C3R
//         ippiFilterBox_32f_AC4R
//
// Purpose:    Applies simple neighborhood averaging filter to blur an image.
// Returns:             IppStatus
//      ippStsNoErr       No errors.
//      ippStsNullPtrErr  pSrc == NULL, or pDst == NULL.
//      ippStsSizeErr     dstRoiSize or roiSize has a field with zero or negative value
//      ippStsMemAllocErr Memory allocation error
//      ippStsStepErr     One of the step values is zero or negative
//      ippStsAnchorErr   Anchor is outside the mask
//      ippStsMaskSizeErr One of the maskSize fields is less than or equal to 1
// Parameters:
//   pSrc        Pointer to the source image
//   srcStep     Step through the source image
//   pDst        Pointer to the destination image
//   dstStep     Step through the destination image
//   pSrcDst     Pointer to the source/destination image (in-place flavors)
//   srcDstStep  Step through the source/destination image (in-place flavors)
//   dstRoiSize  Size of the destination ROI
//   roiSize     Size of the source/destination ROI (in-place flavors)
//   maskSize    Size of the mask in pixels
//   anchor      The [x,y] coordinates of the anchor cell in the kernel
//
*/
//IPPI_WRAP ippiFilterBox_C1R(const Ipp8u* pSrc, int srcStep, Ipp8u*
//	pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
//	IppiPoint anchor) {
//	return IPPCALL(ippiFilterBox_8u_C1R)(pSrc, srcStep, pDst, dstStep, dstRoiSize, maskSize,
//		anchor);
//}
//IPPI_WRAP ippiFilterBox_C3R(const Ipp8u* pSrc, int srcStep, Ipp8u*
//	pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
//	IppiPoint anchor) {
//	return IPPCALL(ippiFilterBox_8u_C3R)(pSrc, srcStep, pDst, dstStep, dstRoiSize, maskSize,
//		anchor);
//}
//IPPI_WRAP ippiFilterBox_AC4R(const Ipp8u* pSrc, int srcStep, Ipp8u*
//	pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
//	IppiPoint anchor) {
//	return IPPCALL(ippiFilterBox_8u_AC4R)(pSrc, srcStep, pDst, dstStep, dstRoiSize, maskSize,
//		anchor);
//}
//IPPI_WRAP ippiFilterBox_C4R(const Ipp8u* pSrc, int srcStep, Ipp8u*
//	pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
//	IppiPoint anchor) {
//	return IPPCALL(ippiFilterBox_8u_C4R)(pSrc, srcStep, pDst, dstStep, dstRoiSize, maskSize,
//		anchor);
//}
//
//
//IPPI_WRAP ippiFilterBox_C1R(const Ipp16s* pSrc, int srcStep, Ipp16s*
//	pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
//	IppiPoint anchor) {
//	return IPPCALL(ippiFilterBox_16s_C1R)(pSrc, srcStep, pDst, dstStep, dstRoiSize, maskSize,
//		anchor);
//}
//IPPI_WRAP ippiFilterBox_C3R(const Ipp16s* pSrc, int srcStep, Ipp16s*
//	pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
//	IppiPoint anchor) {
//	return IPPCALL(ippiFilterBox_16s_C3R)(pSrc, srcStep, pDst, dstStep, dstRoiSize, maskSize,
//		anchor);
//}
//IPPI_WRAP ippiFilterBox_AC4R(const Ipp16s* pSrc, int srcStep, Ipp16s*
//	pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
//	IppiPoint anchor) {
//	return IPPCALL(ippiFilterBox_16s_AC4R)(pSrc, srcStep, pDst, dstStep, dstRoiSize, maskSize,
//		anchor);
//}
//IPPI_WRAP ippiFilterBox_C4R(const Ipp16s* pSrc, int srcStep, Ipp16s*
//	pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
//	IppiPoint anchor) {
//	return IPPCALL(ippiFilterBox_16s_C4R)(pSrc, srcStep, pDst, dstStep, dstRoiSize, maskSize,
//		anchor);
//}
//IPPI_WRAP ippiFilterBox_C1R(const Ipp32f* pSrc, int srcStep, Ipp32f*
//	pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
//	IppiPoint anchor) {
//	return IPPCALL(ippiFilterBox_32f_C1R)(pSrc, srcStep, pDst, dstStep, dstRoiSize, maskSize,
//		anchor);
//}
//IPPI_WRAP ippiFilterBox_C3R(const Ipp32f* pSrc, int srcStep, Ipp32f*
//	pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
//	IppiPoint anchor) {
//	return IPPCALL(ippiFilterBox_32f_C3R)(pSrc, srcStep, pDst, dstStep, dstRoiSize, maskSize,
//		anchor);
//}
//IPPI_WRAP ippiFilterBox_AC4R(const Ipp32f* pSrc, int srcStep, Ipp32f*
//	pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
//	IppiPoint anchor) {
//	return IPPCALL(ippiFilterBox_32f_AC4R)(pSrc, srcStep, pDst, dstStep, dstRoiSize, maskSize,
//		anchor);
//}
//IPPI_WRAP ippiFilterBox_C4R(const Ipp32f* pSrc, int srcStep, Ipp32f*
//	pDst, int dstStep, IppiSize dstRoiSize, IppiSize maskSize,
//	IppiPoint anchor) {
//	return IPPCALL(ippiFilterBox_32f_C4R)(pSrc, srcStep, pDst, dstStep, dstRoiSize, maskSize,
//		anchor);
//}
//
//IPPI_WRAP ippiFilterBox_C1R(Ipp8u* pSrcDst, int srcDstStep, IppiSize
//	roiSize, IppiSize maskSize, IppiPoint anchor) {
//	return IPPCALL(ippiFilterBox_8u_C1IR)(pSrcDst, srcDstStep, roiSize, maskSize, anchor);
//}
//IPPI_WRAP ippiFilterBox_C3R(Ipp8u* pSrcDst, int srcDstStep, IppiSize
//	roiSize, IppiSize maskSize, IppiPoint anchor) {
//	return IPPCALL(ippiFilterBox_8u_C3IR)(pSrcDst, srcDstStep, roiSize, maskSize, anchor);
//}
//IPPI_WRAP ippiFilterBox_AC4R(Ipp8u* pSrcDst, int srcDstStep, IppiSize
//	roiSize, IppiSize maskSize, IppiPoint anchor) {
//	return IPPCALL(ippiFilterBox_8u_AC4IR)(pSrcDst, srcDstStep, roiSize, maskSize, anchor);
//}
//IPPI_WRAP ippiFilterBox_C4R(Ipp8u* pSrcDst, int srcDstStep, IppiSize
//	roiSize, IppiSize maskSize, IppiPoint anchor) {
//	return IPPCALL(ippiFilterBox_8u_C4IR)(pSrcDst, srcDstStep, roiSize, maskSize, anchor);
//}
//
//IPPI_WRAP ippiFilterBox_C1R(Ipp16s* pSrcDst, int srcDstStep, IppiSize
//	roiSize, IppiSize maskSize, IppiPoint anchor) {
//	return IPPCALL(ippiFilterBox_16s_C1IR)(pSrcDst, srcDstStep, roiSize, maskSize, anchor);
//}
//IPPI_WRAP ippiFilterBox_C3R(Ipp16s* pSrcDst, int srcDstStep, IppiSize
//	roiSize, IppiSize maskSize, IppiPoint anchor) {
//	return IPPCALL(ippiFilterBox_16s_C3IR)(pSrcDst, srcDstStep, roiSize, maskSize, anchor);
//}
//IPPI_WRAP ippiFilterBox_AC4R(Ipp16s* pSrc, int srcDstStep, IppiSize
//	roiSize, IppiSize maskSize, IppiPoint anchor) {
//	return IPPCALL(ippiFilterBox_16s_AC4IR)(pSrc, srcDstStep, roiSize, maskSize, anchor);
//}
//IPPI_WRAP ippiFilterBox_C4R(Ipp16s* pSrcDst, int srcDstStep, IppiSize
//	roiSize, IppiSize maskSize, IppiPoint anchor) {
//	return IPPCALL(ippiFilterBox_16s_C4IR)(pSrcDst, srcDstStep, roiSize, maskSize, anchor);
//}
//
//IPPI_WRAP ippiFilterBox_C1R(Ipp32f* pSrcDst, int srcDstStep, IppiSize
//	roiSize, IppiSize maskSize, IppiPoint anchor) {
//	return IPPCALL(ippiFilterBox_32f_C1IR)(pSrcDst, srcDstStep, roiSize, maskSize, anchor);
//}
//IPPI_WRAP ippiFilterBox_C3R(Ipp32f* pSrcDst, int srcDstStep, IppiSize
//	roiSize, IppiSize maskSize, IppiPoint anchor) {
//	return IPPCALL(ippiFilterBox_32f_C3IR)(pSrcDst, srcDstStep, roiSize, maskSize, anchor);
//}
//IPPI_WRAP ippiFilterBox_AC4R(Ipp32f* pSrcDst, int srcDstStep, IppiSize
//	roiSize, IppiSize maskSize, IppiPoint anchor) {
//	return IPPCALL(ippiFilterBox_32f_AC4IR)(pSrcDst, srcDstStep, roiSize, maskSize, anchor);
//}
//IPPI_WRAP ippiFilterBox_C4R(Ipp32f* pSrcDst, int srcDstStep, IppiSize
//	roiSize, IppiSize maskSize, IppiPoint anchor) {
//	return IPPCALL(ippiFilterBox_32f_C4IR)(pSrcDst, srcDstStep, roiSize, maskSize, anchor);
//}
/* /////////////////////////////////////////////////////////////////////////////////////////////////
//                      Logical Operations and Shift Functions
///////////////////////////////////////////////////////////////////////////////////////////////// */
/*
//  Names:          ippiAnd, ippiAndC, ippiOr, ippiOrC, ippiXor, ippiXorC, ippiNot,
//  Purpose:        Performs corresponding bitwise logical operation between pixels of two image
//                  (AndC/OrC/XorC  - between pixel of the source image and a constant)
//
//  Names:          ippiLShiftC, ippiRShiftC
//  Purpose:        Shifts bits in each pixel value to the left and right
//  Parameters:
//   value         1) The constant value to be ANDed/ORed/XORed with each pixel of the source,
//                     constant vector for multi-channel images;
//                 2) The number of bits to shift, constant vector for multi-channel images.
//   pSrc          Pointer to the source image
//   srcStep       Step through the source image
//   pSrcDst       Pointer to the source/destination image (in-place flavors)
//   srcDstStep    Step through the source/destination image (in-place flavors)
//   pSrc1         Pointer to first source image
//   src1Step      Step through first source image
//   pSrc2         Pointer to second source image
//   src2Step      Step through second source image
//   pDst          Pointer to the destination image
//   dstStep       Step in destination image
//   roiSize       Size of the ROI
//
//  Returns:
//   ippStsNullPtrErr   One of the pointers is NULL
//   ippStsStepErr      One of the step values is less than or equal to zero
//   ippStsSizeErr      roiSize has a field with zero or negative value
//   ippStsShiftErr     Shift value is less than zero
//   ippStsNoErr        No errors
*/

IPPI_WRAP ippiAnd_C1R(const Ipp8u* pSrc1, int src1Step, const Ipp8u*
	pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiAnd_8u_C1R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiAnd_C3R(const Ipp8u* pSrc1, int src1Step, const Ipp8u*
	pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiAnd_8u_C3R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiAnd_C4R(const Ipp8u* pSrc1, int src1Step, const Ipp8u*
	pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiAnd_8u_C4R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiAnd_AC4R(const Ipp8u* pSrc1, int src1Step, const Ipp8u*
	pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiAnd_8u_AC4R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize
		);
}
IPPI_WRAP ippiAnd_C1R(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiAnd_8u_C1IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiAnd_C3R(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiAnd_8u_C3IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiAnd_C4R(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiAnd_8u_C4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiAnd_AC4R(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiAnd_8u_AC4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiAnd_C1R(const Ipp8u* pSrc, int srcStep, Ipp8u value,
	Ipp8u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiAndC_8u_C1R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiAnd_C3R(const Ipp8u* pSrc, int srcStep, const Ipp8u
	value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiAndC_8u_C3R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiAnd_C4R(const Ipp8u* pSrc, int srcStep, const Ipp8u
	value[4], Ipp8u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiAndC_8u_C4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiAnd_AC4R(const Ipp8u* pSrc, int srcStep, const Ipp8u
	value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiAndC_8u_AC4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiAnd_C1R(Ipp8u value, Ipp8u* pSrcDst, int srcDstStep,
	IppiSize roiSize) {
	return IPPCALL(ippiAndC_8u_C1IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiAnd_C3R(const Ipp8u value[3], Ipp8u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiAndC_8u_C3IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiAnd_C4R(const Ipp8u value[4], Ipp8u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiAndC_8u_C4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiAnd_AC4R(const Ipp8u value[3], Ipp8u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiAndC_8u_AC4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiAnd_C1R(const Ipp16u* pSrc1, int src1Step, const Ipp16u*
	pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiAnd_16u_C1R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize
		);
}
IPPI_WRAP ippiAnd_C3R(const Ipp16u* pSrc1, int src1Step, const Ipp16u*
	pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiAnd_16u_C3R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize
		);
}
IPPI_WRAP ippiAnd_C4R(const Ipp16u* pSrc1, int src1Step, const Ipp16u*
	pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiAnd_16u_C4R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize
		);
}
IPPI_WRAP ippiAnd_AC4R(const Ipp16u* pSrc1, int src1Step, const Ipp16u*
	pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiAnd_16u_AC4R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize
		);
}
IPPI_WRAP ippiAnd_C1R(const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiAnd_16u_C1IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiAnd_C3R(const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiAnd_16u_C3IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiAnd_C4R(const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiAnd_16u_C4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiAnd_AC4R(const Ipp16u* pSrc, int srcStep, Ipp16u*
	pSrcDst, int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiAnd_16u_AC4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiAnd_C1R(const Ipp16u* pSrc, int srcStep, Ipp16u value,
	Ipp16u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiAndC_16u_C1R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiAnd_C3R(const Ipp16u* pSrc, int srcStep, const Ipp16u
	value[3], Ipp16u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiAndC_16u_C3R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiAnd_C4R(const Ipp16u* pSrc, int srcStep, const Ipp16u
	value[4], Ipp16u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiAndC_16u_C4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiAnd_AC4R(const Ipp16u* pSrc, int srcStep, const Ipp16u
	value[3], Ipp16u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiAndC_16u_AC4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiAnd_C1R(Ipp16u value, Ipp16u* pSrcDst, int srcDstStep,
	IppiSize roiSize) {
	return IPPCALL(ippiAndC_16u_C1IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiAnd_C3R(const Ipp16u value[3], Ipp16u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiAndC_16u_C3IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiAnd_C4R(const Ipp16u value[4], Ipp16u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiAndC_16u_C4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiAnd_AC4R(const Ipp16u value[3], Ipp16u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiAndC_16u_AC4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiAnd_C1R(const Ipp32s* pSrc1, int src1Step, const Ipp32s*
	pSrc2, int src2Step, Ipp32s* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiAnd_32s_C1R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize
		);
}
IPPI_WRAP ippiAnd_C3R(const Ipp32s* pSrc1, int src1Step, const Ipp32s*
	pSrc2, int src2Step, Ipp32s* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiAnd_32s_C3R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize
		);
}
IPPI_WRAP ippiAnd_C4R(const Ipp32s* pSrc1, int src1Step, const Ipp32s*
	pSrc2, int src2Step, Ipp32s* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiAnd_32s_C4R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize
		);
}
IPPI_WRAP ippiAnd_AC4R(const Ipp32s* pSrc1, int src1Step, const Ipp32s*
	pSrc2, int src2Step, Ipp32s* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiAnd_32s_AC4R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize
		);
}
IPPI_WRAP ippiAnd_C1R(const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiAnd_32s_C1IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiAnd_C3R(const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiAnd_32s_C3IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiAnd_C4R(const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiAnd_32s_C4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiAnd_AC4R(const Ipp32s* pSrc, int srcStep, Ipp32s*
	pSrcDst, int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiAnd_32s_AC4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiAnd_C1R(const Ipp32s* pSrc, int srcStep, Ipp32s value,
	Ipp32s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiAndC_32s_C1R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiAnd_C3R(const Ipp32s* pSrc, int srcStep, const Ipp32s
	value[3], Ipp32s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiAndC_32s_C3R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiAnd_C4R(const Ipp32s* pSrc, int srcStep, const Ipp32s
	value[4], Ipp32s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiAndC_32s_C4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiAnd_AC4R(const Ipp32s* pSrc, int srcStep, const Ipp32s
	value[3], Ipp32s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiAndC_32s_AC4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiAnd_C1R(Ipp32s value, Ipp32s* pSrcDst, int srcDstStep,
	IppiSize roiSize) {
	return IPPCALL(ippiAndC_32s_C1IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiAnd_C3R(const Ipp32s value[3], Ipp32s* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiAndC_32s_C3IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiAnd_C4R(const Ipp32s value[4], Ipp32s* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiAndC_32s_C4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiAnd_AC4R(const Ipp32s value[3], Ipp32s* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiAndC_32s_AC4IR)(value, pSrcDst, srcDstStep, roiSize);
}

IPPI_WRAP ippiOr_C1R(const Ipp8u* pSrc1, int src1Step, const Ipp8u*
	pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiOr_8u_C1R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiOr_C3R(const Ipp8u* pSrc1, int src1Step, const Ipp8u*
	pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiOr_8u_C3R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiOr_C4R(const Ipp8u* pSrc1, int src1Step, const Ipp8u*
	pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiOr_8u_C4R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiOr_AC4R(const Ipp8u* pSrc1, int src1Step, const Ipp8u*
	pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiOr_8u_AC4R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiOr_C1R(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiOr_8u_C1IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiOr_C3R(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiOr_8u_C3IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiOr_C4R(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiOr_8u_C4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiOr_AC4R(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiOr_8u_AC4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiOr_C1R(const Ipp8u* pSrc, int srcStep, Ipp8u value,
	Ipp8u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiOrC_8u_C1R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiOr_C3R(const Ipp8u* pSrc, int srcStep, const Ipp8u
	value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiOrC_8u_C3R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiOr_C4R(const Ipp8u* pSrc, int srcStep, const Ipp8u
	value[4], Ipp8u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiOrC_8u_C4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiOr_AC4R(const Ipp8u* pSrc, int srcStep, const Ipp8u
	value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiOrC_8u_AC4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiOr_C1R(Ipp8u value, Ipp8u* pSrcDst, int srcDstStep,
	IppiSize roiSize) {
	return IPPCALL(ippiOrC_8u_C1IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiOr_C3R(const Ipp8u value[3], Ipp8u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiOrC_8u_C3IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiOr_C4R(const Ipp8u value[4], Ipp8u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiOrC_8u_C4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiOr_AC4R(const Ipp8u value[3], Ipp8u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiOrC_8u_AC4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiOr_C1R(const Ipp16u* pSrc1, int src1Step, const Ipp16u*
	pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiOr_16u_C1R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiOr_C3R(const Ipp16u* pSrc1, int src1Step, const Ipp16u*
	pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiOr_16u_C3R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiOr_C4R(const Ipp16u* pSrc1, int src1Step, const Ipp16u*
	pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiOr_16u_C4R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiOr_AC4R(const Ipp16u* pSrc1, int src1Step, const Ipp16u*
	pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiOr_16u_AC4R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize
		);
}
IPPI_WRAP ippiOr_C1R(const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiOr_16u_C1IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiOr_C3R(const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiOr_16u_C3IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiOr_C4R(const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiOr_16u_C4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiOr_AC4R(const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiOr_16u_AC4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiOr_C1R(const Ipp16u* pSrc, int srcStep, Ipp16u value,
	Ipp16u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiOrC_16u_C1R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiOr_C3R(const Ipp16u* pSrc, int srcStep, const Ipp16u
	value[3], Ipp16u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiOrC_16u_C3R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiOr_C4R(const Ipp16u* pSrc, int srcStep, const Ipp16u
	value[4], Ipp16u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiOrC_16u_C4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiOr_AC4R(const Ipp16u* pSrc, int srcStep, const Ipp16u
	value[3], Ipp16u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiOrC_16u_AC4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiOr_C1R(Ipp16u value, Ipp16u* pSrcDst, int srcDstStep,
	IppiSize roiSize) {
	return IPPCALL(ippiOrC_16u_C1IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiOr_C3R(const Ipp16u value[3], Ipp16u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiOrC_16u_C3IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiOr_C4R(const Ipp16u value[4], Ipp16u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiOrC_16u_C4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiOr_AC4R(const Ipp16u value[3], Ipp16u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiOrC_16u_AC4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiOr_C1R(const Ipp32s* pSrc1, int src1Step, const Ipp32s*
	pSrc2, int src2Step, Ipp32s* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiOr_32s_C1R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiOr_C3R(const Ipp32s* pSrc1, int src1Step, const Ipp32s*
	pSrc2, int src2Step, Ipp32s* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiOr_32s_C3R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiOr_C4R(const Ipp32s* pSrc1, int src1Step, const Ipp32s*
	pSrc2, int src2Step, Ipp32s* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiOr_32s_C4R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiOr_AC4R(const Ipp32s* pSrc1, int src1Step, const Ipp32s*
	pSrc2, int src2Step, Ipp32s* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiOr_32s_AC4R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize
		);
}
IPPI_WRAP ippiOr_C1R(const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiOr_32s_C1IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiOr_C3R(const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiOr_32s_C3IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiOr_C4R(const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiOr_32s_C4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiOr_AC4R(const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiOr_32s_AC4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiOr_C1R(const Ipp32s* pSrc, int srcStep, Ipp32s value,
	Ipp32s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiOrC_32s_C1R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiOr_C3R(const Ipp32s* pSrc, int srcStep, const Ipp32s
	value[3], Ipp32s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiOrC_32s_C3R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiOr_C4R(const Ipp32s* pSrc, int srcStep, const Ipp32s
	value[4], Ipp32s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiOrC_32s_C4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiOr_AC4R(const Ipp32s* pSrc, int srcStep, const Ipp32s
	value[3], Ipp32s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiOrC_32s_AC4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiOr_C1R(Ipp32s value, Ipp32s* pSrcDst, int srcDstStep,
	IppiSize roiSize) {
	return IPPCALL(ippiOrC_32s_C1IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiOr_C3R(const Ipp32s value[3], Ipp32s* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiOrC_32s_C3IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiOr_C4R(const Ipp32s value[4], Ipp32s* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiOrC_32s_C4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiOr_AC4R(const Ipp32s value[3], Ipp32s* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiOrC_32s_AC4IR)(value, pSrcDst, srcDstStep, roiSize);
}

IPPI_WRAP ippiXor_C1R(const Ipp8u* pSrc1, int src1Step, const Ipp8u*
	pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiXor_8u_C1R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiXor_C3R(const Ipp8u* pSrc1, int src1Step, const Ipp8u*
	pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiXor_8u_C3R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiXor_C4R(const Ipp8u* pSrc1, int src1Step, const Ipp8u*
	pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiXor_8u_C4R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiXor_AC4R(const Ipp8u* pSrc1, int src1Step, const Ipp8u*
	pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiXor_8u_AC4R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize
		);
}
IPPI_WRAP ippiXor_C1R(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiXor_8u_C1IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiXor_C3R(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiXor_8u_C3IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiXor_C4R(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiXor_8u_C4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiXor_AC4R(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiXor_8u_AC4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiXor_C1R(const Ipp8u* pSrc, int srcStep, Ipp8u value,
	Ipp8u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiXorC_8u_C1R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiXor_C3R(const Ipp8u* pSrc, int srcStep, const Ipp8u
	value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiXorC_8u_C3R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiXor_C4R(const Ipp8u* pSrc, int srcStep, const Ipp8u
	value[4], Ipp8u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiXorC_8u_C4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiXor_AC4R(const Ipp8u* pSrc, int srcStep, const Ipp8u
	value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiXorC_8u_AC4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiXor_C1R(Ipp8u value, Ipp8u* pSrcDst, int srcDstStep,
	IppiSize roiSize) {
	return IPPCALL(ippiXorC_8u_C1IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiXor_C3R(const Ipp8u value[3], Ipp8u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiXorC_8u_C3IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiXor_C4R(const Ipp8u value[4], Ipp8u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiXorC_8u_C4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiXor_AC4R(const Ipp8u value[3], Ipp8u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiXorC_8u_AC4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiXor_C1R(const Ipp16u* pSrc1, int src1Step, const Ipp16u*
	pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiXor_16u_C1R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize
		);
}
IPPI_WRAP ippiXor_C3R(const Ipp16u* pSrc1, int src1Step, const Ipp16u*
	pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiXor_16u_C3R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize
		);
}
IPPI_WRAP ippiXor_C4R(const Ipp16u* pSrc1, int src1Step, const Ipp16u*
	pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiXor_16u_C4R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize
		);
}
IPPI_WRAP ippiXor_AC4R(const Ipp16u* pSrc1, int src1Step, const Ipp16u*
	pSrc2, int src2Step, Ipp16u* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiXor_16u_AC4R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize
		);
}
IPPI_WRAP ippiXor_C1R(const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiXor_16u_C1IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiXor_C3R(const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiXor_16u_C3IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiXor_C4R(const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiXor_16u_C4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiXor_AC4R(const Ipp16u* pSrc, int srcStep, Ipp16u*
	pSrcDst, int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiXor_16u_AC4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiXor_C1R(const Ipp16u* pSrc, int srcStep, Ipp16u value,
	Ipp16u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiXorC_16u_C1R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiXor_C3R(const Ipp16u* pSrc, int srcStep, const Ipp16u
	value[3], Ipp16u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiXorC_16u_C3R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiXor_C4R(const Ipp16u* pSrc, int srcStep, const Ipp16u
	value[4], Ipp16u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiXorC_16u_C4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiXor_AC4R(const Ipp16u* pSrc, int srcStep, const Ipp16u
	value[3], Ipp16u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiXorC_16u_AC4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiXor_C1R(Ipp16u value, Ipp16u* pSrcDst, int srcDstStep,
	IppiSize roiSize) {
	return IPPCALL(ippiXorC_16u_C1IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiXor_C3R(const Ipp16u value[3], Ipp16u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiXorC_16u_C3IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiXor_C4R(const Ipp16u value[4], Ipp16u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiXorC_16u_C4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiXor_AC4R(const Ipp16u value[3], Ipp16u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiXorC_16u_AC4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiXor_C1R(const Ipp32s* pSrc1, int src1Step, const Ipp32s*
	pSrc2, int src2Step, Ipp32s* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiXor_32s_C1R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize
		);
}
IPPI_WRAP ippiXor_C3R(const Ipp32s* pSrc1, int src1Step, const Ipp32s*
	pSrc2, int src2Step, Ipp32s* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiXor_32s_C3R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize
		);
}
IPPI_WRAP ippiXor_C4R(const Ipp32s* pSrc1, int src1Step, const Ipp32s*
	pSrc2, int src2Step, Ipp32s* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiXor_32s_C4R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize
		);
}
IPPI_WRAP ippiXor_AC4R(const Ipp32s* pSrc1, int src1Step, const Ipp32s*
	pSrc2, int src2Step, Ipp32s* pDst, int dstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiXor_32s_AC4R)(pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize
		);
}
IPPI_WRAP ippiXor_C1R(const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiXor_32s_C1IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiXor_C3R(const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiXor_32s_C3IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiXor_C4R(const Ipp32s* pSrc, int srcStep, Ipp32s* pSrcDst,
	int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiXor_32s_C4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiXor_AC4R(const Ipp32s* pSrc, int srcStep, Ipp32s*
	pSrcDst, int srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiXor_32s_AC4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiXor_C1R(const Ipp32s* pSrc, int srcStep, Ipp32s value,
	Ipp32s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiXorC_32s_C1R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiXor_C3R(const Ipp32s* pSrc, int srcStep, const Ipp32s
	value[3], Ipp32s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiXorC_32s_C3R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiXor_C4R(const Ipp32s* pSrc, int srcStep, const Ipp32s
	value[4], Ipp32s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiXorC_32s_C4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiXor_AC4R(const Ipp32s* pSrc, int srcStep, const Ipp32s
	value[3], Ipp32s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiXorC_32s_AC4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiXor_C1R(Ipp32s value, Ipp32s* pSrcDst, int srcDstStep,
	IppiSize roiSize) {
	return IPPCALL(ippiXorC_32s_C1IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiXor_C3R(const Ipp32s value[3], Ipp32s* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiXorC_32s_C3IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiXor_C4R(const Ipp32s value[4], Ipp32s* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiXorC_32s_C4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiXor_AC4R(const Ipp32s value[3], Ipp32s* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiXorC_32s_AC4IR)(value, pSrcDst, srcDstStep, roiSize);
}

IPPI_WRAP ippiNot_C1R(const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int
	dstStep, IppiSize roiSize) {
	return IPPCALL(ippiNot_8u_C1R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiNot_C3R(const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int
	dstStep, IppiSize roiSize) {
	return IPPCALL(ippiNot_8u_C3R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiNot_C4R(const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int
	dstStep, IppiSize roiSize) {
	return IPPCALL(ippiNot_8u_C4R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiNot_AC4R(const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int
	dstStep, IppiSize roiSize) {
	return IPPCALL(ippiNot_8u_AC4R)(pSrc, srcStep, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiNot_C1R(Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize)
{
	return IPPCALL(ippiNot_8u_C1IR)(pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiNot_C3R(Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize)
{
	return IPPCALL(ippiNot_8u_C3IR)(pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiNot_C4R(Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize)
{
	return IPPCALL(ippiNot_8u_C4IR)(pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiNot_AC4R(Ipp8u* pSrcDst, int srcDstStep, IppiSize
	roiSize) {
	return IPPCALL(ippiNot_8u_AC4IR)(pSrcDst, srcDstStep, roiSize);
}

IPPI_WRAP ippiLShift_C1R(const Ipp8u* pSrc, int srcStep, Ipp32u value,
	Ipp8u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiLShiftC_8u_C1R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiLShift_C3R(const Ipp8u* pSrc, int srcStep, const Ipp32u
	value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiLShiftC_8u_C3R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiLShift_C4R(const Ipp8u* pSrc, int srcStep, const Ipp32u
	value[4], Ipp8u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiLShiftC_8u_C4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiLShift_AC4R(const Ipp8u* pSrc, int srcStep, const Ipp32u
	value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiLShiftC_8u_AC4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiLShift_C1R(Ipp32u value, Ipp8u* pSrcDst, int srcDstStep,
	IppiSize roiSize) {
	return IPPCALL(ippiLShiftC_8u_C1IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiLShift_C3R(const Ipp32u value[3], Ipp8u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiLShiftC_8u_C3IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiLShift_C4R(const Ipp32u value[4], Ipp8u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiLShiftC_8u_C4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiLShift_AC4R(const Ipp32u value[3], Ipp8u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiLShiftC_8u_AC4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiLShift_C1R(const Ipp16u* pSrc, int srcStep, Ipp32u value,
	Ipp16u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiLShiftC_16u_C1R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiLShift_C3R(const Ipp16u* pSrc, int srcStep, const Ipp32u
	value[3], Ipp16u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiLShiftC_16u_C3R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiLShift_C4R(const Ipp16u* pSrc, int srcStep, const Ipp32u
	value[4], Ipp16u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiLShiftC_16u_C4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiLShift_AC4R(const Ipp16u* pSrc, int srcStep, const Ipp32u
	value[3], Ipp16u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiLShiftC_16u_AC4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiLShift_C1R(Ipp32u value, Ipp16u* pSrcDst, int srcDstStep,
	IppiSize roiSize) {
	return IPPCALL(ippiLShiftC_16u_C1IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiLShift_C3R(const Ipp32u value[3], Ipp16u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiLShiftC_16u_C3IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiLShift_C4R(const Ipp32u value[4], Ipp16u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiLShiftC_16u_C4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiLShift_AC4R(const Ipp32u value[3], Ipp16u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiLShiftC_16u_AC4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiLShift_C1R(const Ipp32s* pSrc, int srcStep, Ipp32u value,
	Ipp32s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiLShiftC_32s_C1R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiLShift_C3R(const Ipp32s* pSrc, int srcStep, const Ipp32u
	value[3], Ipp32s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiLShiftC_32s_C3R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiLShift_C4R(const Ipp32s* pSrc, int srcStep, const Ipp32u
	value[4], Ipp32s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiLShiftC_32s_C4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiLShift_AC4R(const Ipp32s* pSrc, int srcStep, const Ipp32u
	value[3], Ipp32s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiLShiftC_32s_AC4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiLShift_C1R(Ipp32u value, Ipp32s* pSrcDst, int srcDstStep,
	IppiSize roiSize) {
	return IPPCALL(ippiLShiftC_32s_C1IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiLShift_C3R(const Ipp32u value[3], Ipp32s* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiLShiftC_32s_C3IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiLShift_C4R(const Ipp32u value[4], Ipp32s* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiLShiftC_32s_C4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiLShift_AC4R(const Ipp32u value[3], Ipp32s* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiLShiftC_32s_AC4IR)(value, pSrcDst, srcDstStep, roiSize);
}

IPPI_WRAP ippiRShift_C1R(const Ipp8u* pSrc, int srcStep, Ipp32u value,
	Ipp8u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_8u_C1R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRShift_C3R(const Ipp8u* pSrc, int srcStep, const Ipp32u
	value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_8u_C3R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRShift_C4R(const Ipp8u* pSrc, int srcStep, const Ipp32u
	value[4], Ipp8u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_8u_C4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRShift_AC4R(const Ipp8u* pSrc, int srcStep, const Ipp32u
	value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_8u_AC4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRShift_C1R(Ipp32u value, Ipp8u* pSrcDst, int srcDstStep,
	IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_8u_C1IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiRShift_C3R(const Ipp32u value[3], Ipp8u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_8u_C3IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiRShift_C4R(const Ipp32u value[4], Ipp8u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_8u_C4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiRShift_AC4R(const Ipp32u value[3], Ipp8u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_8u_AC4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiRShift_C1R(const Ipp8s* pSrc, int srcStep, Ipp32u value,
	Ipp8s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_8s_C1R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRShift_C3R(const Ipp8s* pSrc, int srcStep, const Ipp32u
	value[3], Ipp8s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_8s_C3R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRShift_C4R(const Ipp8s* pSrc, int srcStep, const Ipp32u
	value[4], Ipp8s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_8s_C4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRShift_AC4R(const Ipp8s* pSrc, int srcStep, const Ipp32u
	value[3], Ipp8s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_8s_AC4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRShift_C1R(Ipp32u value, Ipp8s* pSrcDst, int srcDstStep,
	IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_8s_C1IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiRShift_C3R(const Ipp32u value[3], Ipp8s* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_8s_C3IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiRShift_C4R(const Ipp32u value[4], Ipp8s* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_8s_C4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiRShift_AC4R(const Ipp32u value[3], Ipp8s* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_8s_AC4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiRShift_C1R(const Ipp16u* pSrc, int srcStep, Ipp32u value,
	Ipp16u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_16u_C1R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRShift_C3R(const Ipp16u* pSrc, int srcStep, const Ipp32u
	value[3], Ipp16u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_16u_C3R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRShift_C4R(const Ipp16u* pSrc, int srcStep, const Ipp32u
	value[4], Ipp16u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_16u_C4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRShift_AC4R(const Ipp16u* pSrc, int srcStep, const Ipp32u
	value[3], Ipp16u* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_16u_AC4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRShift_C1R(Ipp32u value, Ipp16u* pSrcDst, int srcDstStep,
	IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_16u_C1IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiRShift_C3R(const Ipp32u value[3], Ipp16u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_16u_C3IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiRShift_C4R(const Ipp32u value[4], Ipp16u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_16u_C4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiRShift_AC4R(const Ipp32u value[3], Ipp16u* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_16u_AC4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiRShift_C1R(const Ipp16s* pSrc, int srcStep, Ipp32u value,
	Ipp16s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_16s_C1R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRShift_C3R(const Ipp16s* pSrc, int srcStep, const Ipp32u
	value[3], Ipp16s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_16s_C3R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRShift_C4R(const Ipp16s* pSrc, int srcStep, const Ipp32u
	value[4], Ipp16s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_16s_C4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRShift_AC4R(const Ipp16s* pSrc, int srcStep, const Ipp32u
	value[3], Ipp16s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_16s_AC4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRShift_C1R(Ipp32u value, Ipp16s* pSrcDst, int srcDstStep,
	IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_16s_C1IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiRShift_C3R(const Ipp32u value[3], Ipp16s* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_16s_C3IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiRShift_C4R(const Ipp32u value[4], Ipp16s* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_16s_C4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiRShift_AC4R(const Ipp32u value[3], Ipp16s* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_16s_AC4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiRShift_C1R(const Ipp32s* pSrc, int srcStep, Ipp32u value,
	Ipp32s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_32s_C1R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRShift_C3R(const Ipp32s* pSrc, int srcStep, const Ipp32u
	value[3], Ipp32s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_32s_C3R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRShift_C4R(const Ipp32s* pSrc, int srcStep, const Ipp32u
	value[4], Ipp32s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_32s_C4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRShift_AC4R(const Ipp32s* pSrc, int srcStep, const Ipp32u
	value[3], Ipp32s* pDst, int dstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_32s_AC4R)(pSrc, srcStep, value, pDst, dstStep, roiSize);
}
IPPI_WRAP ippiRShift_C1R(Ipp32u value, Ipp32s* pSrcDst, int srcDstStep,
	IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_32s_C1IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiRShift_C3R(const Ipp32u value[3], Ipp32s* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_32s_C3IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiRShift_C4R(const Ipp32u value[4], Ipp32s* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_32s_C4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiRShift_AC4R(const Ipp32u value[3], Ipp32s* pSrcDst, int
	srcDstStep, IppiSize roiSize) {
	return IPPCALL(ippiRShiftC_32s_AC4IR)(value, pSrcDst, srcDstStep, roiSize);
}
IPPI_WRAP ippiGammaFwd_C3R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiGammaFwd_8u_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiGammaFwd_C3R( Ipp8u* pSrcDst, int srcDstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiGammaFwd_8u_C3IR)( pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiGammaFwd_C3R( const Ipp16u* pSrc, int srcStep, Ipp16u* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiGammaFwd_16u_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiGammaFwd_C3R( Ipp16u* pSrcDst, int srcDstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiGammaFwd_16u_C3IR)( pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiGammaFwd_C3R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiGammaFwd_32f_C3R)( pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->FloatMin, GetEnv()->FloatMax ); 
     } 
IPPI_WRAP ippiGammaFwd_C3R( Ipp32f* pSrcDst, int srcDstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiGammaFwd_32f_C3IR)( pSrcDst, srcDstStep, roiSize, GetEnv()->FloatMin, GetEnv()->FloatMax ); 
     } 
IPPI_WRAP ippiGammaFwd_AC4R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiGammaFwd_8u_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiGammaFwd_AC4R( Ipp8u* pSrcDst, int srcDstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiGammaFwd_8u_AC4IR)( pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiGammaFwd_AC4R( const Ipp16u* pSrc, int srcStep, Ipp16u* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiGammaFwd_16u_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiGammaFwd_AC4R( Ipp16u* pSrcDst, int srcDstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiGammaFwd_16u_AC4IR)( pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiGammaFwd_AC4R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiGammaFwd_32f_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->FloatMin, GetEnv()->FloatMax ); 
     } 
IPPI_WRAP ippiGammaFwd_AC4R( Ipp32f* pSrcDst, int srcDstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiGammaFwd_32f_AC4IR)( pSrcDst, srcDstStep, roiSize, GetEnv()->FloatMin, GetEnv()->FloatMax ); 
     } 
IPPI_WRAP ippiGammaInv_C3R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst,
								 int dstStep, IppiSize roiSize) {
		 return IPPCALL(ippiGammaInv_8u_C3R)( pSrc, srcStep, pDst, dstStep, roiSize );
		 }
IPPI_WRAP ippiGammaInv_C3R( Ipp8u* pSrcDst, int srcDstStep, IppiSize
								 roiSize) {
		 return IPPCALL(ippiGammaInv_8u_C3IR)( pSrcDst, srcDstStep, roiSize );
		 }
IPPI_WRAP ippiGammaInv_C3R( const Ipp16u* pSrc, int srcStep, Ipp16u*
								 pDst, int dstStep, IppiSize roiSize) {
		 return IPPCALL(ippiGammaInv_16u_C3R)( pSrc, srcStep, pDst, dstStep, roiSize );
		 }
IPPI_WRAP ippiGammaInv_C3R( Ipp16u* pSrcDst, int srcDstStep, IppiSize
								 roiSize) {
		 return IPPCALL(ippiGammaInv_16u_C3IR)( pSrcDst, srcDstStep, roiSize );
		 }
IPPI_WRAP ippiGammaInv_AC4R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiGammaInv_8u_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiGammaInv_AC4R( Ipp8u* pSrcDst, int srcDstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiGammaInv_8u_AC4IR)( pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiGammaInv_AC4R( const Ipp16u* pSrc, int srcStep, Ipp16u* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiGammaInv_16u_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiGammaInv_AC4R( Ipp16u* pSrcDst, int srcDstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiGammaInv_16u_AC4IR)( pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiGammaInv_AC4R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiGammaInv_32f_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->FloatMin, GetEnv()->FloatMax ); 
     } 
IPPI_WRAP ippiGammaInv_AC4R( Ipp32f* pSrcDst, int srcDstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiGammaInv_32f_AC4IR)( pSrcDst, srcDstStep, roiSize, GetEnv()->FloatMin, GetEnv()->FloatMax ); 
     }
template<typename Valtype>
	IPPI_WRAP ippiResizeGetSize(IppiSize srcSize, IppiSize dstSize, IppiInterpolationType interpolation, Ipp32u antialiasing, Ipp32s* pSpecSize, Ipp32s* pInitBufSize);
template<>
	IPPI_WRAP ippiResizeGetSize<Ipp8u>(IppiSize srcSize, IppiSize dstSize, IppiInterpolationType interpolation, Ipp32u antialiasing, Ipp32s* pSpecSize, Ipp32s* pInitBufSize)
	{	return IPPCALL(ippiResizeGetSize_8u)(srcSize, dstSize, interpolation, antialiasing, pSpecSize, pInitBufSize);	}
template<>
	IPPI_WRAP ippiResizeGetSize<Ipp16u>(IppiSize srcSize, IppiSize dstSize, IppiInterpolationType interpolation, Ipp32u antialiasing, Ipp32s* pSpecSize, Ipp32s* pInitBufSize)
	{	return IPPCALL(ippiResizeGetSize_16u)(srcSize, dstSize, interpolation, antialiasing, pSpecSize, pInitBufSize);	}
template<>
	IPPI_WRAP ippiResizeGetSize<Ipp32f>(IppiSize srcSize, IppiSize dstSize, IppiInterpolationType interpolation, Ipp32u antialiasing, Ipp32s* pSpecSize, Ipp32s* pInitBufSize)
	{	return IPPCALL(ippiResizeGetSize_32f)(srcSize, dstSize, interpolation, antialiasing, pSpecSize, pInitBufSize);	}
template<typename Valtype>
	IPPI_WRAP ippiResizeNearestInit(IppiSize srcSize, IppiSize dstSize, IppiResizeSpec_32f* pSpec);
template<>
	IPPI_WRAP ippiResizeNearestInit<Ipp8u>(IppiSize srcSize, IppiSize dstSize, IppiResizeSpec_32f* pSpec)
	{	return IPPCALL(ippiResizeNearestInit_8u)(srcSize, dstSize, pSpec);	}
template<>
	IPPI_WRAP ippiResizeNearestInit<Ipp16u>(IppiSize srcSize, IppiSize dstSize, IppiResizeSpec_32f* pSpec)
	{	return IPPCALL(ippiResizeNearestInit_16u)(srcSize, dstSize, pSpec);	}
template<>
	IPPI_WRAP ippiResizeNearestInit<Ipp32f>(IppiSize srcSize, IppiSize dstSize, IppiResizeSpec_32f* pSpec)
	{	return IPPCALL(ippiResizeNearestInit_32f)(srcSize, dstSize, pSpec);	}
template<typename Valtype>
	IPPI_WRAP ippiResizeGetBufferSize(IppiResizeSpec_32f* pSpec, IppiSize dstSize, Ipp32u numChannels, Ipp32s* pBufSize);
template<>
	IPPI_WRAP ippiResizeGetBufferSize<Ipp8u>(IppiResizeSpec_32f* pSpec, IppiSize dstSize, Ipp32u numChannels, Ipp32s* pBufSize)
	{	return IPPCALL(ippiResizeGetBufferSize_8u)(pSpec, dstSize, numChannels, pBufSize); }
template<>
	IPPI_WRAP ippiResizeGetBufferSize<Ipp16u>(IppiResizeSpec_32f* pSpec, IppiSize dstSize, Ipp32u numChannels, Ipp32s* pBufSize)
	{	return IPPCALL(ippiResizeGetBufferSize_16u)(pSpec, dstSize, numChannels, pBufSize); }
template<>
	IPPI_WRAP ippiResizeGetBufferSize<Ipp32f>(IppiResizeSpec_32f* pSpec, IppiSize dstSize, Ipp32u numChannels, Ipp32s* pBufSize)
	{	return IPPCALL(ippiResizeGetBufferSize_32f)(pSpec, dstSize, numChannels, pBufSize); }
IPPI_WRAP ippiResizeNearest_C1R(const Ipp8u* pSrc, Ipp32s srcStep, Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeNearest_8u_C1R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, pSpec, pBuffer);	}
IPPI_WRAP ippiResizeNearest_C1R(const Ipp16u* pSrc, Ipp32s srcStep, Ipp16u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeNearest_16u_C1R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, pSpec, pBuffer);	}
IPPI_WRAP ippiResizeNearest_C1R(const Ipp32f* pSrc, Ipp32s srcStep, Ipp32f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeNearest_32f_C1R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, pSpec, pBuffer);	}
IPPI_WRAP ippiResizeNearest_C3R(const Ipp8u* pSrc, Ipp32s srcStep, Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeNearest_8u_C3R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, pSpec, pBuffer);	}
IPPI_WRAP ippiResizeNearest_C3R(const Ipp16u* pSrc, Ipp32s srcStep, Ipp16u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeNearest_16u_C3R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, pSpec, pBuffer);	}
IPPI_WRAP ippiResizeNearest_C3R(const Ipp32f* pSrc, Ipp32s srcStep, Ipp32f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeNearest_32f_C3R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, pSpec, pBuffer);	}

IPPI_WRAP ippiResizeNearest_C4R(const Ipp8u* pSrc, Ipp32s srcStep, Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeNearest_8u_C4R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, pSpec, pBuffer);	}
IPPI_WRAP ippiResizeNearest_C4R(const Ipp16u* pSrc, Ipp32s srcStep, Ipp16u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeNearest_16u_C4R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, pSpec, pBuffer);	}
IPPI_WRAP ippiResizeNearest_C4R(const Ipp32f* pSrc, Ipp32s srcStep, Ipp32f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeNearest_32f_C4R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, pSpec, pBuffer);	}

// Linear Sample
template<typename Valtype>
IPPI_WRAP ippiResizeLinearInit(IppiSize srcSize, IppiSize dstSize, IppiResizeSpec_32f* pSpec);
template<>
IPPI_WRAP ippiResizeLinearInit<Ipp8u>(IppiSize srcSize, IppiSize dstSize, IppiResizeSpec_32f* pSpec)
{	return IPPCALL(ippiResizeLinearInit_8u)(srcSize, dstSize, pSpec);	}
template<>
IPPI_WRAP ippiResizeLinearInit<Ipp16u>(IppiSize srcSize, IppiSize dstSize, IppiResizeSpec_32f* pSpec)
{	return IPPCALL(ippiResizeLinearInit_16u)(srcSize, dstSize, pSpec);	}
template<>
IPPI_WRAP ippiResizeLinearInit<Ipp32f>(IppiSize srcSize, IppiSize dstSize, IppiResizeSpec_32f* pSpec)
{	return IPPCALL(ippiResizeLinearInit_32f)(srcSize, dstSize, pSpec);	}
IPPI_WRAP ippiResizeLinear_C1R(const Ipp8u* pSrc, Ipp32s srcStep, Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeLinear_8u_C1R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, GetEnv()->BorderType, 0, pSpec, pBuffer);	}
IPPI_WRAP ippiResizeLinear_C1R(const Ipp16u* pSrc, Ipp32s srcStep, Ipp16u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeLinear_16u_C1R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, GetEnv()->BorderType, 0, pSpec, pBuffer);	}
IPPI_WRAP ippiResizeLinear_C1R(const Ipp32f* pSrc, Ipp32s srcStep, Ipp32f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeLinear_32f_C1R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, GetEnv()->BorderType, 0, pSpec, pBuffer);	}
IPPI_WRAP ippiResizeLinear_C3R(const Ipp8u* pSrc, Ipp32s srcStep, Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeLinear_8u_C3R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, GetEnv()->BorderType, 0, pSpec, pBuffer);	}
IPPI_WRAP ippiResizeLinear_C3R(const Ipp16u* pSrc, Ipp32s srcStep, Ipp16u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeLinear_16u_C3R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, GetEnv()->BorderType, 0, pSpec, pBuffer);	}
IPPI_WRAP ippiResizeLinear_C3R(const Ipp32f* pSrc, Ipp32s srcStep, Ipp32f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeLinear_32f_C3R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, GetEnv()->BorderType, 0, pSpec, pBuffer);	}
IPPI_WRAP ippiResizeLinear_C4R(const Ipp8u* pSrc, Ipp32s srcStep, Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeLinear_8u_C4R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, GetEnv()->BorderType, 0, pSpec, pBuffer);	}
IPPI_WRAP ippiResizeLinear_C4R(const Ipp16u* pSrc, Ipp32s srcStep, Ipp16u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeLinear_16u_C4R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, GetEnv()->BorderType, 0, pSpec, pBuffer);	}
IPPI_WRAP ippiResizeLinear_C4R(const Ipp32f* pSrc, Ipp32s srcStep, Ipp32f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeLinear_32f_C4R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, GetEnv()->BorderType, 0, pSpec, pBuffer);	}
// Super Simpling
template<typename Valtype>
IPPI_WRAP ippiResizeSuperInit(IppiSize srcSize, IppiSize dstSize, IppiResizeSpec_32f* pSpec);
template<>
IPPI_WRAP ippiResizeSuperInit<Ipp8u>(IppiSize srcSize, IppiSize dstSize, IppiResizeSpec_32f* pSpec)
{	return IPPCALL(ippiResizeSuperInit_8u)(srcSize, dstSize, pSpec);	}
template<>
IPPI_WRAP ippiResizeSuperInit<Ipp16u>(IppiSize srcSize, IppiSize dstSize, IppiResizeSpec_32f* pSpec)
{	return IPPCALL(ippiResizeSuperInit_16u)(srcSize, dstSize, pSpec);	}
template<>
IPPI_WRAP ippiResizeSuperInit<Ipp32f>(IppiSize srcSize, IppiSize dstSize, IppiResizeSpec_32f* pSpec)
{	return IPPCALL(ippiResizeSuperInit_32f)(srcSize, dstSize, pSpec);	}

IPPI_WRAP ippiResizeSuper_C1R(const Ipp8u* pSrc, Ipp32s srcStep, Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeSuper_8u_C1R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, pSpec, pBuffer);	}
IPPI_WRAP ippiResizeSuper_C1R(const Ipp16u* pSrc, Ipp32s srcStep, Ipp16u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeSuper_16u_C1R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, pSpec, pBuffer);	}
IPPI_WRAP ippiResizeSuper_C1R(const Ipp32f* pSrc, Ipp32s srcStep, Ipp32f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeSuper_32f_C1R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, pSpec, pBuffer);	}
IPPI_WRAP ippiResizeSuper_C3R(const Ipp8u* pSrc, Ipp32s srcStep, Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeSuper_8u_C3R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, pSpec, pBuffer);	}
IPPI_WRAP ippiResizeSuper_C3R(const Ipp16u* pSrc, Ipp32s srcStep, Ipp16u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeSuper_16u_C3R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, pSpec, pBuffer);	}
IPPI_WRAP ippiResizeSuper_C3R(const Ipp32f* pSrc, Ipp32s srcStep, Ipp32f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeSuper_32f_C3R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, pSpec, pBuffer);	}

IPPI_WRAP ippiResizeSuper_C4R(const Ipp8u* pSrc, Ipp32s srcStep, Ipp8u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeSuper_8u_C4R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, pSpec, pBuffer);	}
IPPI_WRAP ippiResizeSuper_C4R(const Ipp16u* pSrc, Ipp32s srcStep, Ipp16u* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeSuper_16u_C4R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, pSpec, pBuffer);	}
IPPI_WRAP ippiResizeSuper_C4R(const Ipp32f* pSrc, Ipp32s srcStep, Ipp32f* pDst, Ipp32s dstStep, IppiPoint dstOffset, IppiSize dstSize, IppiResizeSpec_32f* pSpec, Ipp8u* pBuffer)
{	return IPPCALL(ippiResizeSuper_32f_C4R)(pSrc, srcStep, pDst, dstStep, dstOffset, dstSize, pSpec, pBuffer);	}
IPPI_WRAP ippiCopy_C3P3R( const Ipp8u* pSrc, int srcStep, Ipp8u* const 
                             pDst[3], int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiCopy_8u_C3P3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiCopy_C3P3R( const Ipp16s* pSrc, int srcStep, Ipp16s* const 
                             pDst[3], int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiCopy_16s_C3P3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
    } 
IPPI_WRAP ippiCopy_C3P3R( const Ipp32f* pSrc, int srcStep, Ipp32f* const 
                             pDst[3], int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiCopy_32f_C3P3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiCopy_C4P4R( const Ipp8u* pSrc, int srcStep, Ipp8u* const 
                             pDst[4], int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiCopy_8u_C4P4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiCopy_C4P4R( const Ipp16s* pSrc, int srcStep, Ipp16s* const 
                             pDst[4], int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiCopy_16s_C4P4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiCopy_C4P4R( const Ipp32f* pSrc, int srcStep, Ipp32f* const 
                             pDst[4], int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiCopy_32f_C4P4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiNorm_L2_C1R( const Ipp8u* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp64f* pValue) { 
     return IPPCALL(ippiNorm_L2_8u_C1R)( pSrc, srcStep, roiSize, pValue ); 
     } 

IPPI_WRAP ippiNorm_L2_C3R( const Ipp8u* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp64f value[3]) { 
     return IPPCALL(ippiNorm_L2_8u_C3R)( pSrc, srcStep, roiSize, value ); 
     } 
IPPI_WRAP ippiNorm_L2_C4R( const Ipp8u* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp64f value[4]) { 
     return IPPCALL(ippiNorm_L2_8u_C4R)( pSrc, srcStep, roiSize, value ); 
     } 
IPPI_WRAP ippiNorm_L2_C1R( const Ipp16s* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp64f* pValue) { 
     return IPPCALL(ippiNorm_L2_16s_C1R)( pSrc, srcStep, roiSize, pValue ); 
     } 

IPPI_WRAP ippiNorm_L2_C3R( const Ipp16s* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp64f value[3]) { 
     return IPPCALL(ippiNorm_L2_16s_C3R)( pSrc, srcStep, roiSize, value ); 
     } 

IPPI_WRAP ippiNorm_L2_C4R( const Ipp16s* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp64f value[4]) { 
     return IPPCALL(ippiNorm_L2_16s_C4R)( pSrc, srcStep, roiSize, value ); 
     } 

IPPI_WRAP ippiNorm_L2_C1R( const Ipp32f* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp64f* pValue) { 
     return IPPCALL(ippiNorm_L2_32f_C1R)( pSrc, srcStep, roiSize, pValue, GetEnv()->HintAlgorithm ); 
     } 

IPPI_WRAP ippiNorm_L2_C3R( const Ipp32f* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp64f value[3]) { 
     return IPPCALL(ippiNorm_L2_32f_C3R)( pSrc, srcStep, roiSize, value, GetEnv()->HintAlgorithm ); 
     } 

IPPI_WRAP ippiNorm_L2_C4R( const Ipp32f* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp64f value[4]) { 
     return IPPCALL(ippiNorm_L2_32f_C4R)( pSrc, srcStep, roiSize, value, GetEnv()->HintAlgorithm ); 
     } 
IPPI_WRAP ippiNormDiff_L2_C1R( const Ipp8u* pSrc1, int src1Step, const 
                             Ipp8u* pSrc2, int src2Step, IppiSize roiSize, Ipp64f* 
                             pValue) { 
     return IPPCALL(ippiNormDiff_L2_8u_C1R)( pSrc1, src1Step, pSrc2, src2Step, roiSize, pValue 
                             ); 
     } 

IPPI_WRAP ippiNormDiff_L2_C3R( const Ipp8u* pSrc1, int src1Step, const 
                             Ipp8u* pSrc2, int src2Step, IppiSize roiSize, Ipp64f 
                             value[3]) { 
     return IPPCALL(ippiNormDiff_L2_8u_C3R)( pSrc1, src1Step, pSrc2, src2Step, roiSize, value ); 
     } 

IPPI_WRAP ippiNormDiff_L2_C4R( const Ipp8u* pSrc1, int src1Step, const 
                             Ipp8u* pSrc2, int src2Step, IppiSize roiSize, Ipp64f 
                             value[4]) { 
     return IPPCALL(ippiNormDiff_L2_8u_C4R)( pSrc1, src1Step, pSrc2, src2Step, roiSize, value ); 
     } 

IPPI_WRAP ippiNormDiff_L2_C1R( const Ipp16s* pSrc1, int src1Step, const 
                             Ipp16s* pSrc2, int src2Step, IppiSize roiSize, Ipp64f* 
                             pValue) { 
     return IPPCALL(ippiNormDiff_L2_16s_C1R)( pSrc1, src1Step, pSrc2, src2Step, roiSize, pValue 
                             ); 
     } 

IPPI_WRAP ippiNormDiff_L2_C3R( const Ipp16s* pSrc1, int src1Step, const 
                             Ipp16s* pSrc2, int src2Step, IppiSize roiSize, Ipp64f 
                             value[3]) { 
     return IPPCALL(ippiNormDiff_L2_16s_C3R)( pSrc1, src1Step, pSrc2, src2Step, roiSize, value 
                             ); 
     } 

IPPI_WRAP ippiNormDiff_L2_C4R( const Ipp16s* pSrc1, int src1Step, const 
                             Ipp16s* pSrc2, int src2Step, IppiSize roiSize, Ipp64f 
                             value[4]) { 
     return IPPCALL(ippiNormDiff_L2_16s_C4R)( pSrc1, src1Step, pSrc2, src2Step, roiSize, value 
                             ); 
     } 

IPPI_WRAP ippiNormDiff_L2_C1R( const Ipp32f* pSrc1, int src1Step, const 
                             Ipp32f* pSrc2, int src2Step, IppiSize roiSize, Ipp64f* 
                             pValue) { 
     return IPPCALL(ippiNormDiff_L2_32f_C1R)( pSrc1, src1Step, pSrc2, src2Step, roiSize, pValue, 
                             GetEnv()->HintAlgorithm ); 
     } 

IPPI_WRAP ippiNormDiff_L2_C3R( const Ipp32f* pSrc1, int src1Step, const 
                             Ipp32f* pSrc2, int src2Step, IppiSize roiSize, Ipp64f 
                             value[3]) { 
     return IPPCALL(ippiNormDiff_L2_32f_C3R)( pSrc1, src1Step, pSrc2, src2Step, roiSize, value, 
                             GetEnv()->HintAlgorithm ); 
     } 


IPPI_WRAP ippiNormDiff_L2_C4R( const Ipp32f* pSrc1, int src1Step, const 
                             Ipp32f* pSrc2, int src2Step, IppiSize roiSize, Ipp64f 
                             value[4]) { 
     return IPPCALL(ippiNormDiff_L2_32f_C4R)( pSrc1, src1Step, pSrc2, src2Step, roiSize, value, 
                             GetEnv()->HintAlgorithm ); 
     } 
IPPI_WRAP ippiSum_C1R( const Ipp8u* pSrc, int srcStep, IppiSize roiSize, 
                             Ipp64f* pSum) { 
     return IPPCALL(ippiSum_8u_C1R)( pSrc, srcStep, roiSize, pSum ); 
     } 

IPPI_WRAP ippiSum_C3R( const Ipp8u* pSrc, int srcStep, IppiSize roiSize, 
                             Ipp64f sum[3]) { 
     return IPPCALL(ippiSum_8u_C3R)( pSrc, srcStep, roiSize, sum ); 
     } 

IPPI_WRAP ippiSum_C4R( const Ipp8u* pSrc, int srcStep, IppiSize roiSize, 
                             Ipp64f sum[4]) { 
     return IPPCALL(ippiSum_8u_C4R)( pSrc, srcStep, roiSize, sum ); 
     } 

IPPI_WRAP ippiSum_C1R( const Ipp16s* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp64f* pSum) { 
     return IPPCALL(ippiSum_16s_C1R)( pSrc, srcStep, roiSize, pSum ); 
     } 

IPPI_WRAP ippiSum_C3R( const Ipp16s* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp64f sum[3]) { 
     return IPPCALL(ippiSum_16s_C3R)( pSrc, srcStep, roiSize, sum ); 
     } 

IPPI_WRAP ippiSum_C4R( const Ipp16s* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp64f sum[4]) { 
     return IPPCALL(ippiSum_16s_C4R)( pSrc, srcStep, roiSize, sum ); 
     } 

IPPI_WRAP ippiSum_C1R( const Ipp32f* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp64f* pSum) { 
     return IPPCALL(ippiSum_32f_C1R)( pSrc, srcStep, roiSize, pSum, GetEnv()->HintAlgorithm ); 
     } 

IPPI_WRAP ippiSum_C3R( const Ipp32f* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp64f sum[3]) { 
     return IPPCALL(ippiSum_32f_C3R)( pSrc, srcStep, roiSize, sum, GetEnv()->HintAlgorithm ); 
     } 

IPPI_WRAP ippiSum_C4R( const Ipp32f* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp64f sum[4]) { 
     return IPPCALL(ippiSum_32f_C4R)( pSrc, srcStep, roiSize, sum, GetEnv()->HintAlgorithm ); 
     } 
IPPI_WRAP ippiMean_C1R( const Ipp8u* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp64f* pMean) { 
     return IPPCALL(ippiMean_8u_C1R)( pSrc, srcStep, roiSize, pMean ); 
     } 

IPPI_WRAP ippiMean_C3R( const Ipp8u* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp64f mean[3]) { 
     return IPPCALL(ippiMean_8u_C3R)( pSrc, srcStep, roiSize, mean ); 
     } 

IPPI_WRAP ippiMean_C4R( const Ipp8u* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp64f mean[4]) { 
     return IPPCALL(ippiMean_8u_C4R)( pSrc, srcStep, roiSize, mean ); 
     } 

IPPI_WRAP ippiMean_C1R( const Ipp16s* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp64f* pMean) { 
     return IPPCALL(ippiMean_16s_C1R)( pSrc, srcStep, roiSize, pMean ); 
     } 

IPPI_WRAP ippiMean_C3R( const Ipp16s* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp64f mean[3]) { 
     return IPPCALL(ippiMean_16s_C3R)( pSrc, srcStep, roiSize, mean ); 
     } 
IPPI_WRAP ippiMean_C4R( const Ipp16s* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp64f mean[4]) { 
     return IPPCALL(ippiMean_16s_C4R)( pSrc, srcStep, roiSize, mean ); 
     } 

IPPI_WRAP ippiMean_C1R( const Ipp32f* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp64f* pMean) { 
     return IPPCALL(ippiMean_32f_C1R)( pSrc, srcStep, roiSize, pMean, GetEnv()->HintAlgorithm ); 
     } 

IPPI_WRAP ippiMean_C3R( const Ipp32f* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp64f mean[3]) { 
     return IPPCALL(ippiMean_32f_C3R)( pSrc, srcStep, roiSize, mean, GetEnv()->HintAlgorithm ); 
     } 

IPPI_WRAP ippiMean_C4R( const Ipp32f* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp64f mean[4]) { 
     return IPPCALL(ippiMean_32f_C4R)( pSrc, srcStep, roiSize, mean, GetEnv()->HintAlgorithm ); 
     } 
IPPI_WRAP ippiMean_StdDev_C1R( const Ipp8u* pSrc, int srcStep,
                                 IppiSize roiSize,
                                 Ipp64f* mean, Ipp64f* stddev)
{
	return IPPCALL(ippiMean_StdDev_8u_C1R)(pSrc,srcStep,roiSize,mean,stddev);
}

IPPI_WRAP ippiMean_StdDev_C1R( const Ipp16u* pSrc, int srcStep,
                                 IppiSize roiSize,
                                 Ipp64f* mean, Ipp64f* stddev)
{
	return IPPCALL(ippiMean_StdDev_16u_C1R)(pSrc,srcStep,roiSize,mean,stddev);
}

IPPI_WRAP ippiMean_StdDev_C1R( const Ipp32f* pSrc, int srcStep,
                                 IppiSize roiSize,
                                 Ipp64f* mean, Ipp64f* stddev)
{
	return IPPCALL(ippiMean_StdDev_32f_C1R)(pSrc,srcStep,roiSize,mean,stddev);
}
IPPI_WRAP ippiDotProd_C1R(const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, IppiSize roiSize, double* pD)
{
	return IPPCALL(ippiDotProd_8u64f_C1R)(pSrc1, src1Step, pSrc2, src2Step, roiSize, pD);
}
IPPI_WRAP ippiDotProd_C1R(const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, IppiSize roiSize, double* pD)
{
	return IPPCALL(ippiDotProd_16u64f_C1R)(pSrc1, src1Step, pSrc2, src2Step, roiSize, pD);
}
IPPI_WRAP ippiDotProd_C1R(const Ipp16s* pSrc1, int src1Step, const Ipp16s* pSrc2, int src2Step, IppiSize roiSize, double* pD)
{
	return IPPCALL(ippiDotProd_16s64f_C1R)(pSrc1, src1Step, pSrc2, src2Step, roiSize, pD);
}
IPPI_WRAP ippiDotProd_C1R(const Ipp32u* pSrc1, int src1Step, const Ipp32u* pSrc2, int src2Step, IppiSize roiSize, double* pD)
{
	return IPPCALL(ippiDotProd_32u64f_C1R)(pSrc1, src1Step, pSrc2, src2Step, roiSize, pD);
}
IPPI_WRAP ippiDotProd_C1R(const Ipp32s* pSrc1, int src1Step, const Ipp32s* pSrc2, int src2Step, IppiSize roiSize, double* pD)
{
	return IPPCALL(ippiDotProd_32s64f_C1R)(pSrc1, src1Step, pSrc2, src2Step, roiSize, pD);
}
IPPI_WRAP ippiDotProd_C3R(const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, IppiSize roiSize, double* pD)
{
	return IPPCALL(ippiDotProd_8u64f_C3R)(pSrc1, src1Step, pSrc2, src2Step, roiSize, pD);
}
IPPI_WRAP ippiDotProd_C3R(const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, IppiSize roiSize, double* pD)
{
	return IPPCALL(ippiDotProd_16u64f_C3R)(pSrc1, src1Step, pSrc2, src2Step, roiSize, pD);
}
IPPI_WRAP ippiDotProd_C3R(const Ipp16s* pSrc1, int src1Step, const Ipp16s* pSrc2, int src2Step, IppiSize roiSize, double* pD)
{
	return IPPCALL(ippiDotProd_16s64f_C3R)(pSrc1, src1Step, pSrc2, src2Step, roiSize, pD);
}
IPPI_WRAP ippiDotProd_C3R(const Ipp32u* pSrc1, int src1Step, const Ipp32u* pSrc2, int src2Step, IppiSize roiSize, double* pD)
{
	return IPPCALL(ippiDotProd_32u64f_C3R)(pSrc1, src1Step, pSrc2, src2Step, roiSize, pD);
}
IPPI_WRAP ippiDotProd_C3R(const Ipp32s* pSrc1, int src1Step, const Ipp32s* pSrc2, int src2Step, IppiSize roiSize, double* pD)
{
	return IPPCALL(ippiDotProd_32s64f_C3R)(pSrc1, src1Step, pSrc2, src2Step, roiSize, pD);
}

IPPI_WRAP ippiDotProd_C4R(const Ipp8u* pSrc1, int src1Step, const Ipp8u* pSrc2, int src2Step, IppiSize roiSize, double* pD)
{
	return IPPCALL(ippiDotProd_8u64f_C4R)(pSrc1, src1Step, pSrc2, src2Step, roiSize, pD);
}
IPPI_WRAP ippiDotProd_C4R(const Ipp16u* pSrc1, int src1Step, const Ipp16u* pSrc2, int src2Step, IppiSize roiSize, double* pD)
{
	return IPPCALL(ippiDotProd_16u64f_C4R)(pSrc1, src1Step, pSrc2, src2Step, roiSize, pD);
}
IPPI_WRAP ippiDotProd_C4R(const Ipp16s* pSrc1, int src1Step, const Ipp16s* pSrc2, int src2Step, IppiSize roiSize, double* pD)
{
	return IPPCALL(ippiDotProd_16s64f_C4R)(pSrc1, src1Step, pSrc2, src2Step, roiSize, pD);
}
IPPI_WRAP ippiDotProd_C4R(const Ipp32u* pSrc1, int src1Step, const Ipp32u* pSrc2, int src2Step, IppiSize roiSize, double* pD)
{
	return IPPCALL(ippiDotProd_32u64f_C4R)(pSrc1, src1Step, pSrc2, src2Step, roiSize, pD);
}
IPPI_WRAP ippiDotProd_C4R(const Ipp32s* pSrc1, int src1Step, const Ipp32s* pSrc2, int src2Step, IppiSize roiSize, double* pD)
{
	return IPPCALL(ippiDotProd_32s64f_C4R)(pSrc1, src1Step, pSrc2, src2Step, roiSize, pD);
}
IPPI_WRAP ippiMinEvery_C1IR(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize)
{	return IPPCALL(ippiMinEvery_8u_C1IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);	
}
IPPI_WRAP ippiMinEvery_C1IR(const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize)
{	return IPPCALL(ippiMinEvery_16u_C1IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);	
}
IPPI_WRAP ippiMinEvery_C1IR(const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize)
{	return IPPCALL(ippiMinEvery_16s_C1IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);	
}
IPPI_WRAP ippiMinEvery_C1IR(const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize)
{	return IPPCALL(ippiMinEvery_32f_C1IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);	
}
IPPI_WRAP ippiMinEvery_C3IR(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize)
{	return IPPCALL(ippiMinEvery_8u_C3IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);	
}
IPPI_WRAP ippiMinEvery_C3IR(const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize)
{	return IPPCALL(ippiMinEvery_16u_C3IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);	
}
IPPI_WRAP ippiMinEvery_C3IR(const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize)
{	return IPPCALL(ippiMinEvery_16s_C3IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);	
}
IPPI_WRAP ippiMinEvery_C3IR(const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize)
{	return IPPCALL(ippiMinEvery_32f_C3IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);	
}
IPPI_WRAP ippiMinEvery_C4IR(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize)
{	return IPPCALL(ippiMinEvery_8u_C4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);	
}
IPPI_WRAP ippiMinEvery_C4IR(const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize)
{	return IPPCALL(ippiMinEvery_16u_C4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);	
}
IPPI_WRAP ippiMinEvery_C4IR(const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize)
{	return IPPCALL(ippiMinEvery_16s_C4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);	
}
IPPI_WRAP ippiMinEvery_C4IR(const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize)
{	return IPPCALL(ippiMinEvery_32f_C4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);	
}
IPPI_WRAP ippiMin_C1R( const Ipp8u* pSrc, int srcStep, IppiSize roiSize, 
                             Ipp8u* pMin) { 
     return IPPCALL(ippiMin_8u_C1R)( pSrc, srcStep, roiSize, pMin ); 
     } 

IPPI_WRAP ippiMin_C3R( const Ipp8u* pSrc, int srcStep, IppiSize roiSize, 
                             Ipp8u min[3]) { 
     return IPPCALL(ippiMin_8u_C3R)( pSrc, srcStep, roiSize, min ); 
     } 

IPPI_WRAP ippiMin_C4R( const Ipp8u* pSrc, int srcStep, IppiSize roiSize, 
                             Ipp8u min[4]) { 
     return IPPCALL(ippiMin_8u_C4R)( pSrc, srcStep, roiSize, min ); 
     } 

IPPI_WRAP ippiMin_C1R( const Ipp16s* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp16s* pMin) { 
     return IPPCALL(ippiMin_16s_C1R)( pSrc, srcStep, roiSize, pMin ); 
     } 

IPPI_WRAP ippiMin_C3R( const Ipp16s* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp16s min[3]) { 
     return IPPCALL(ippiMin_16s_C3R)( pSrc, srcStep, roiSize, min ); 
     } 

IPPI_WRAP ippiMin_C4R( const Ipp16s* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp16s min[4]) { 
     return IPPCALL(ippiMin_16s_C4R)( pSrc, srcStep, roiSize, min ); 
     } 

IPPI_WRAP ippiMin_C1R( const Ipp32f* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp32f* pMin) { 
     return IPPCALL(ippiMin_32f_C1R)( pSrc, srcStep, roiSize, pMin ); 
     } 

IPPI_WRAP ippiMin_C3R( const Ipp32f* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp32f min[3]) { 
     return IPPCALL(ippiMin_32f_C3R)( pSrc, srcStep, roiSize, min ); 
     } 


IPPI_WRAP ippiMin_C4R( const Ipp32f* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp32f min[4]) { 
     return IPPCALL(ippiMin_32f_C4R)( pSrc, srcStep, roiSize, min ); 
     } 
IPPI_WRAP ippiMinIndx_C1R( const Ipp8u* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp8u* pMin, int* pIndexX, int* pIndexY) { 
     return IPPCALL(ippiMinIndx_8u_C1R)( pSrc, srcStep, roiSize, pMin, pIndexX, pIndexY ); 
     } 

IPPI_WRAP ippiMinIndx_C3R( const Ipp8u* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp8u min[3], int indexX[3], int indexY[3]) { 
     return IPPCALL(ippiMinIndx_8u_C3R)( pSrc, srcStep, roiSize, min, indexX, indexY ); 
     } 

IPPI_WRAP ippiMinIndx_C4R( const Ipp8u* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp8u min[4], int indexX[4], int indexY[4]) { 
     return IPPCALL(ippiMinIndx_8u_C4R)( pSrc, srcStep, roiSize, min, indexX, indexY ); 
     } 

IPPI_WRAP ippiMinIndx_C1R( const Ipp16s* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp16s* pMin, int* pIndexX, int* pIndexY) { 
     return IPPCALL(ippiMinIndx_16s_C1R)( pSrc, srcStep, roiSize, pMin, pIndexX, pIndexY ); 
     } 

IPPI_WRAP ippiMinIndx_C3R( const Ipp16s* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp16s min[3], int indexX[3], int indexY[3]) { 
     return IPPCALL(ippiMinIndx_16s_C3R)( pSrc, srcStep, roiSize, min, indexX, indexY ); 
     } 

IPPI_WRAP ippiMinIndx_C4R( const Ipp16s* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp16s min[4], int indexX[4], int indexY[4]) { 
     return IPPCALL(ippiMinIndx_16s_C4R)( pSrc, srcStep, roiSize, min, indexX, indexY ); 
     } 

IPPI_WRAP ippiMinIndx_C1R( const Ipp32f* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp32f* pMin, int* pIndexX, int* pIndexY) { 
     return IPPCALL(ippiMinIndx_32f_C1R)( pSrc, srcStep, roiSize, pMin, pIndexX, pIndexY ); 
     } 

IPPI_WRAP ippiMinIndx_C3R( const Ipp32f* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp32f min[3], int indexX[3], int indexY[3]) { 
     return IPPCALL(ippiMinIndx_32f_C3R)( pSrc, srcStep, roiSize, min, indexX, indexY ); 
     } 

IPPI_WRAP ippiMinIndx_C4R( const Ipp32f* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp32f min[4], int indexX[4], int indexY[4]) { 
     return IPPCALL(ippiMinIndx_32f_C4R)( pSrc, srcStep, roiSize, min, indexX, indexY ); 
     } 
IPPI_WRAP ippiMaxEvery_C1IR(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize)
{	return IPPCALL(ippiMaxEvery_8u_C1IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);	
}
IPPI_WRAP ippiMaxEvery_C1IR(const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize)
{	return IPPCALL(ippiMaxEvery_16u_C1IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);	
}
IPPI_WRAP ippiMaxEvery_C1IR(const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize)
{	return IPPCALL(ippiMaxEvery_16s_C1IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);	
}
IPPI_WRAP ippiMaxEvery_C1IR(const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize)
{	return IPPCALL(ippiMaxEvery_32f_C1IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);	
}
IPPI_WRAP ippiMaxEvery_C3IR(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize)
{	return IPPCALL(ippiMaxEvery_8u_C3IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);	
}
IPPI_WRAP ippiMaxEvery_C3IR(const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize)
{	return IPPCALL(ippiMaxEvery_16u_C3IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);	
}
IPPI_WRAP ippiMaxEvery_C3IR(const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize)
{	return IPPCALL(ippiMaxEvery_16s_C3IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);	
}
IPPI_WRAP ippiMaxEvery_C3IR(const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize)
{	return IPPCALL(ippiMaxEvery_32f_C3IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);	
}
IPPI_WRAP ippiMaxEvery_C4IR(const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize)
{	return IPPCALL(ippiMaxEvery_8u_C4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);	
}
IPPI_WRAP ippiMaxEvery_C4IR(const Ipp16u* pSrc, int srcStep, Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize)
{	return IPPCALL(ippiMaxEvery_16u_C4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);	
}
IPPI_WRAP ippiMaxEvery_C4IR(const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize)
{	return IPPCALL(ippiMaxEvery_16s_C4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);	
}
IPPI_WRAP ippiMaxEvery_C4IR(const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize)
{	return IPPCALL(ippiMaxEvery_32f_C4IR)(pSrc, srcStep, pSrcDst, srcDstStep, roiSize);	
}
IPPI_WRAP ippiMax_C1R( const Ipp8u* pSrc, int srcStep, IppiSize roiSize, 
                             Ipp8u* pMax) { 
     return IPPCALL(ippiMax_8u_C1R)( pSrc, srcStep, roiSize, pMax ); 
     } 

IPPI_WRAP ippiMax_C3R( const Ipp8u* pSrc, int srcStep, IppiSize roiSize, 
                             Ipp8u max[3]) { 
     return IPPCALL(ippiMax_8u_C3R)( pSrc, srcStep, roiSize, max ); 
     } 

IPPI_WRAP ippiMax_C4R( const Ipp8u* pSrc, int srcStep, IppiSize roiSize, 
                             Ipp8u max[4]) { 
     return IPPCALL(ippiMax_8u_C4R)( pSrc, srcStep, roiSize, max ); 
     } 

IPPI_WRAP ippiMax_C1R( const Ipp16s* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp16s* pMax) { 
     return IPPCALL(ippiMax_16s_C1R)( pSrc, srcStep, roiSize, pMax ); 
     } 

IPPI_WRAP ippiMax_C3R( const Ipp16s* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp16s max[3]) { 
     return IPPCALL(ippiMax_16s_C3R)( pSrc, srcStep, roiSize, max ); 
     } 

IPPI_WRAP ippiMax_C4R( const Ipp16s* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp16s max[4]) { 
     return IPPCALL(ippiMax_16s_C4R)( pSrc, srcStep, roiSize, max ); 
     } 

IPPI_WRAP ippiMax_C1R( const Ipp32f* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp32f* pMax) { 
     return IPPCALL(ippiMax_32f_C1R)( pSrc, srcStep, roiSize, pMax ); 
     } 

IPPI_WRAP ippiMax_C3R( const Ipp32f* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp32f max[3]) { 
     return IPPCALL(ippiMax_32f_C3R)( pSrc, srcStep, roiSize, max ); 
     } 

IPPI_WRAP ippiMax_C4R( const Ipp32f* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp32f max[4]) { 
     return IPPCALL(ippiMax_32f_C4R)( pSrc, srcStep, roiSize, max ); 
     } 
IPPI_WRAP ippiMaxIndx_C1R( const Ipp8u* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp8u* pMax, int* pIndexX, int* pIndexY) { 
     return IPPCALL(ippiMaxIndx_8u_C1R)( pSrc, srcStep, roiSize, pMax, pIndexX, pIndexY ); 
     } 

IPPI_WRAP ippiMaxIndx_C3R( const Ipp8u* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp8u max[3], int indexX[3], int indexY[3]) { 
     return IPPCALL(ippiMaxIndx_8u_C3R)( pSrc, srcStep, roiSize, max, indexX, indexY ); 
     } 

IPPI_WRAP ippiMaxIndx_C4R( const Ipp8u* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp8u max[4], int indexX[4], int indexY[4]) { 
     return IPPCALL(ippiMaxIndx_8u_C4R)( pSrc, srcStep, roiSize, max, indexX, indexY ); 
     } 

IPPI_WRAP ippiMaxIndx_C1R( const Ipp16s* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp16s* pMax, int* pIndexX, int* pIndexY) { 
     return IPPCALL(ippiMaxIndx_16s_C1R)( pSrc, srcStep, roiSize, pMax, pIndexX, pIndexY ); 
     } 

IPPI_WRAP ippiMaxIndx_C3R( const Ipp16s* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp16s max[3], int indexX[3], int indexY[3]) { 
     return IPPCALL(ippiMaxIndx_16s_C3R)( pSrc, srcStep, roiSize, max, indexX, indexY ); 
     } 


IPPI_WRAP ippiMaxIndx_C4R( const Ipp16s* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp16s max[4], int indexX[4], int indexY[4]) { 
     return IPPCALL(ippiMaxIndx_16s_C4R)( pSrc, srcStep, roiSize, max, indexX, indexY ); 
     } 

IPPI_WRAP ippiMaxIndx_C1R( const Ipp32f* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp32f* pMax, int* pIndexX, int* pIndexY) { 
     return IPPCALL(ippiMaxIndx_32f_C1R)( pSrc, srcStep, roiSize, pMax, pIndexX, pIndexY ); 
     } 

IPPI_WRAP ippiMaxIndx_C3R( const Ipp32f* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp32f max[3], int indexX[3], int indexY[3]) { 
     return IPPCALL(ippiMaxIndx_32f_C3R)( pSrc, srcStep, roiSize, max, indexX, indexY ); 
     } 

IPPI_WRAP ippiMaxIndx_C4R( const Ipp32f* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp32f max[4], int indexX[4], int indexY[4]) { 
     return IPPCALL(ippiMaxIndx_32f_C4R)( pSrc, srcStep, roiSize, max, indexX, indexY ); 
     } 
IPPI_WRAP ippiMinMax_C1R( const Ipp8u* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp8u* pMin, Ipp8u* pMax) { 
     return IPPCALL(ippiMinMax_8u_C1R)( pSrc, srcStep, roiSize, pMin, pMax ); 
     } 

IPPI_WRAP ippiMinMax_C3R( const Ipp8u* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp8u min[3], Ipp8u max[3]) { 
     return IPPCALL(ippiMinMax_8u_C3R)( pSrc, srcStep, roiSize, min, max ); 
     } 

IPPI_WRAP ippiMinMax_C4R( const Ipp8u* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp8u min[4], Ipp8u max[4]) { 
     return IPPCALL(ippiMinMax_8u_C4R)( pSrc, srcStep, roiSize, min, max ); 
     } 

IPPI_WRAP ippiMinMax_C1R( const Ipp16s* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp16s* pMin, Ipp16s* pMax) { 
     return IPPCALL(ippiMinMax_16s_C1R)( pSrc, srcStep, roiSize, pMin, pMax ); 
     } 

IPPI_WRAP ippiMinMax_C3R( const Ipp16s* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp16s min[3], Ipp16s max[3]) { 
     return IPPCALL(ippiMinMax_16s_C3R)( pSrc, srcStep, roiSize, min, max ); 
     } 


IPPI_WRAP ippiMinMax_C4R( const Ipp16s* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp16s min[4], Ipp16s max[4]) { 
     return IPPCALL(ippiMinMax_16s_C4R)( pSrc, srcStep, roiSize, min, max ); 
     } 

IPPI_WRAP ippiMinMax_C1R( const Ipp32f* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp32f* pMin, Ipp32f* pMax) { 
     return IPPCALL(ippiMinMax_32f_C1R)( pSrc, srcStep, roiSize, pMin, pMax ); 
     } 

IPPI_WRAP ippiMinMax_C3R( const Ipp32f* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp32f min[3], Ipp32f max[3]) { 
     return IPPCALL(ippiMinMax_32f_C3R)( pSrc, srcStep, roiSize, min, max ); 
     } 

IPPI_WRAP ippiMinMax_C4R( const Ipp32f* pSrc, int srcStep, IppiSize 
                             roiSize, Ipp32f min[4], Ipp32f max[4]) { 
     return IPPCALL(ippiMinMax_32f_C4R)( pSrc, srcStep, roiSize, min, max ); 
     } 
IPPI_WRAP ippiThreshold_LT_C1R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize, Ipp8u threshold) { 
     return IPPCALL(ippiThreshold_LT_8u_C1R)( pSrc, srcStep, pDst, dstStep, roiSize, threshold 
                             ); 
     } 
IPPI_WRAP ippiThreshold_LT_C1R( const Ipp16s* pSrc, int srcStep, Ipp16s* 
                             pDst, int dstStep, IppiSize roiSize, Ipp16s threshold) { 
     return IPPCALL(ippiThreshold_LT_16s_C1R)( pSrc, srcStep, pDst, dstStep, roiSize, threshold 
                             ); 
     } 
IPPI_WRAP ippiThreshold_LT_C1R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize roiSize, Ipp32f threshold) { 
     return IPPCALL(ippiThreshold_LT_32f_C1R)( pSrc, srcStep, pDst, dstStep, roiSize, threshold 
                             ); 
     } 
IPPI_WRAP ippiThreshold_LT_C3R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize, const Ipp8u 
                             threshold[3]) { 
     return IPPCALL(ippiThreshold_LT_8u_C3R)( pSrc, srcStep, pDst, dstStep, roiSize, threshold 
                             ); 
     } 
IPPI_WRAP ippiThreshold_LT_C3R( const Ipp16s* pSrc, int srcStep, Ipp16s* 
                             pDst, int dstStep, IppiSize roiSize, const Ipp16s 
                             threshold[3]) { 
     return IPPCALL(ippiThreshold_LT_16s_C3R)( pSrc, srcStep, pDst, dstStep, roiSize, threshold 
                             ); 
     } 
IPPI_WRAP ippiThreshold_LT_C3R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize roiSize, const Ipp32f 
                             threshold[3]) { 
     return IPPCALL(ippiThreshold_LT_32f_C3R)( pSrc, srcStep, pDst, dstStep, roiSize, threshold 
                             ); 
     } 
IPPI_WRAP ippiThreshold_LT_C1R( Ipp8u* pSrcDst, int srcDstStep, IppiSize 
                             roiSize, Ipp8u threshold) { 
     return IPPCALL(ippiThreshold_LT_8u_C1IR)( pSrcDst, srcDstStep, roiSize, threshold ); 
     } 
IPPI_WRAP ippiThreshold_LT_C1R( Ipp16s* pSrcDst, int srcDstStep, 
                             IppiSize roiSize, Ipp16s threshold) { 
     return IPPCALL(ippiThreshold_LT_16s_C1IR)( pSrcDst, srcDstStep, roiSize, threshold ); 
     } 
IPPI_WRAP ippiThreshold_LT_C1R( Ipp32f* pSrcDst, int srcDstStep, 
                             IppiSize roiSize, Ipp32f threshold) { 
     return IPPCALL(ippiThreshold_LT_32f_C1IR)( pSrcDst, srcDstStep, roiSize, threshold ); 
     } 
IPPI_WRAP ippiThreshold_LT_C3R( Ipp8u* pSrcDst, int srcDstStep, IppiSize 
                             roiSize, const Ipp8u threshold[3]) { 
     return IPPCALL(ippiThreshold_LT_8u_C3IR)( pSrcDst, srcDstStep, roiSize, threshold ); 
     } 
IPPI_WRAP ippiThreshold_LT_C3R( Ipp16s* pSrcDst, int srcDstStep, 
                             IppiSize roiSize, const Ipp16s threshold[3]) { 
     return IPPCALL(ippiThreshold_LT_16s_C3IR)( pSrcDst, srcDstStep, roiSize, threshold ); 
     } 
IPPI_WRAP ippiThreshold_LT_C3R( Ipp32f* pSrcDst, int srcDstStep, 
                             IppiSize roiSize, const Ipp32f threshold[3]) { 
     return IPPCALL(ippiThreshold_LT_32f_C3IR)( pSrcDst, srcDstStep, roiSize, threshold ); 
     } 
IPPI_WRAP ippiThreshold_LT_AC4R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize, const Ipp8u 
                             threshold[3]) { 
     return IPPCALL(ippiThreshold_LT_8u_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize, threshold 
                             ); 
     } 
IPPI_WRAP ippiThreshold_LT_AC4R( const Ipp16s* pSrc, int srcStep, 
                             Ipp16s* pDst, int dstStep, IppiSize roiSize, const Ipp16s 
                             threshold[3]) { 
     return IPPCALL(ippiThreshold_LT_16s_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize, threshold 
                             ); 
     } 
IPPI_WRAP ippiThreshold_LT_AC4R( const Ipp32f* pSrc, int srcStep, 
                             Ipp32f* pDst, int dstStep, IppiSize roiSize, const Ipp32f 
                             threshold[3]) { 
     return IPPCALL(ippiThreshold_LT_32f_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize, threshold 
                             ); 
     } 
IPPI_WRAP ippiThreshold_LT_AC4R( Ipp8u* pSrcDst, int srcDstStep, 
                             IppiSize roiSize, const Ipp8u threshold[3]) { 
     return IPPCALL(ippiThreshold_LT_8u_AC4IR)( pSrcDst, srcDstStep, roiSize, threshold ); 
     } 
IPPI_WRAP ippiThreshold_LT_AC4R( Ipp16s* pSrcDst, int srcDstStep, 
                             IppiSize roiSize, const Ipp16s threshold[3]) { 
     return IPPCALL(ippiThreshold_LT_16s_AC4IR)( pSrcDst, srcDstStep, roiSize, threshold ); 
     } 
IPPI_WRAP ippiThreshold_LT_AC4R( Ipp32f* pSrcDst, int srcDstStep, 
                             IppiSize roiSize, const Ipp32f threshold[3]) { 
     return IPPCALL(ippiThreshold_LT_32f_AC4IR)( pSrcDst, srcDstStep, roiSize, threshold ); 
     } 
IPPI_WRAP ippiThreshold_GT_C1R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize, Ipp8u threshold) { 
     return IPPCALL(ippiThreshold_GT_8u_C1R)( pSrc, srcStep, pDst, dstStep, roiSize, threshold 
                             ); 
     } 
IPPI_WRAP ippiThreshold_GT_C1R( const Ipp16s* pSrc, int srcStep, Ipp16s* 
                             pDst, int dstStep, IppiSize roiSize, Ipp16s threshold) { 
     return IPPCALL(ippiThreshold_GT_16s_C1R)( pSrc, srcStep, pDst, dstStep, roiSize, threshold 
                             ); 
     } 
IPPI_WRAP ippiThreshold_GT_C1R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize roiSize, Ipp32f threshold) { 
     return IPPCALL(ippiThreshold_GT_32f_C1R)( pSrc, srcStep, pDst, dstStep, roiSize, threshold 
                             ); 
     } 
IPPI_WRAP ippiThreshold_GT_C3R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize, const Ipp8u 
                             threshold[3]) { 
     return IPPCALL(ippiThreshold_GT_8u_C3R)( pSrc, srcStep, pDst, dstStep, roiSize, threshold 
                             ); 
     } 
IPPI_WRAP ippiThreshold_GT_C3R( const Ipp16s* pSrc, int srcStep, Ipp16s* 
                             pDst, int dstStep, IppiSize roiSize, const Ipp16s 
                             threshold[3]) { 
     return IPPCALL(ippiThreshold_GT_16s_C3R)( pSrc, srcStep, pDst, dstStep, roiSize, threshold 
                             ); 
     } 
IPPI_WRAP ippiThreshold_GT_C3R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize roiSize, const Ipp32f 
                             threshold[3]) { 
     return IPPCALL(ippiThreshold_GT_32f_C3R)( pSrc, srcStep, pDst, dstStep, roiSize, threshold 
                             ); 
     } 
IPPI_WRAP ippiThreshold_GT_AC4R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize, const Ipp8u 
                             threshold[3]) { 
     return IPPCALL(ippiThreshold_GT_8u_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize, threshold 
                             ); 
     } 
IPPI_WRAP ippiThreshold_GT_AC4R( const Ipp16s* pSrc, int srcStep, 
                             Ipp16s* pDst, int dstStep, IppiSize roiSize, const Ipp16s 
                             threshold[3]) { 
     return IPPCALL(ippiThreshold_GT_16s_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize, threshold 
                             ); 
     } 
IPPI_WRAP ippiThreshold_GT_AC4R( const Ipp32f* pSrc, int srcStep, 
                             Ipp32f* pDst, int dstStep, IppiSize roiSize, const Ipp32f 
                             threshold[3]) { 
     return IPPCALL(ippiThreshold_GT_32f_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize, threshold 
                             ); 
     } 
IPPI_WRAP ippiThreshold_GT_C1R( Ipp8u* pSrcDst, int srcDstStep, IppiSize 
                             roiSize, Ipp8u threshold) { 
     return IPPCALL(ippiThreshold_GT_8u_C1IR)( pSrcDst, srcDstStep, roiSize, threshold ); 
     } 
IPPI_WRAP ippiThreshold_GT_C1R( Ipp16s* pSrcDst, int srcDstStep, 
                             IppiSize roiSize, Ipp16s threshold) { 
     return IPPCALL(ippiThreshold_GT_16s_C1IR)( pSrcDst, srcDstStep, roiSize, threshold ); 
     } 
IPPI_WRAP ippiThreshold_GT_C1R( Ipp32f* pSrcDst, int srcDstStep, 
                             IppiSize roiSize, Ipp32f threshold) { 
     return IPPCALL(ippiThreshold_GT_32f_C1IR)( pSrcDst, srcDstStep, roiSize, threshold ); 
     } 
IPPI_WRAP ippiThreshold_GT_C3R( Ipp8u* pSrcDst, int srcDstStep, IppiSize 
                             roiSize, const Ipp8u threshold[3]) { 
     return IPPCALL(ippiThreshold_GT_8u_C3IR)( pSrcDst, srcDstStep, roiSize, threshold ); 
     } 
IPPI_WRAP ippiThreshold_GT_C3R( Ipp16s* pSrcDst, int srcDstStep, 
                             IppiSize roiSize, const Ipp16s threshold[3]) { 
     return IPPCALL(ippiThreshold_GT_16s_C3IR)( pSrcDst, srcDstStep, roiSize, threshold ); 
     } 
IPPI_WRAP ippiThreshold_GT_C3R( Ipp32f* pSrcDst, int srcDstStep, 
                             IppiSize roiSize, const Ipp32f threshold[3]) { 
     return IPPCALL(ippiThreshold_GT_32f_C3IR)( pSrcDst, srcDstStep, roiSize, threshold ); 
     } 
IPPI_WRAP ippiThreshold_GT_AC4R( Ipp8u* pSrcDst, int srcDstStep, 
                             IppiSize roiSize, const Ipp8u threshold[3]) { 
     return IPPCALL(ippiThreshold_GT_8u_AC4IR)( pSrcDst, srcDstStep, roiSize, threshold ); 
     } 
IPPI_WRAP ippiThreshold_GT_AC4R( Ipp16s* pSrcDst, int srcDstStep, 
                             IppiSize roiSize, const Ipp16s threshold[3]) { 
     return IPPCALL(ippiThreshold_GT_16s_AC4IR)( pSrcDst, srcDstStep, roiSize, threshold ); 
     } 
IPPI_WRAP ippiThreshold_GT_AC4R( Ipp32f* pSrcDst, int srcDstStep, 
                             IppiSize roiSize, const Ipp32f threshold[3]) { 
     return IPPCALL(ippiThreshold_GT_32f_AC4IR)( pSrcDst, srcDstStep, roiSize, threshold ); 
     } 
IPPI_WRAP ippiMirror_C1R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, 
                             int dstStep, IppiSize roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_8u_C1R)( pSrc, srcStep, pDst, dstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_C3R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, 
                             int dstStep, IppiSize roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_8u_C3R)( pSrc, srcStep, pDst, dstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_AC4R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, 
                             int dstStep, IppiSize roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_8u_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_C4R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, 
                             int dstStep, IppiSize roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_8u_C4R)( pSrc, srcStep, pDst, dstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_C1R( Ipp8u* pSrcDst, int srcDstStep, IppiSize 
                             roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_8u_C1IR)( pSrcDst, srcDstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_C3R( Ipp8u* pSrcDst, int srcDstStep, IppiSize 
                             roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_8u_C3IR)( pSrcDst, srcDstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_AC4R( Ipp8u* pSrcDst, int srcDstStep, IppiSize 
                             roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_8u_AC4IR)( pSrcDst, srcDstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_C4R( Ipp8u* pSrcDst, int srcDstStep, IppiSize 
                             roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_8u_C4IR)( pSrcDst, srcDstStep, roiSize, flip ); 
     } 

IPPI_WRAP ippiMirror_C1R( const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, 
                             int dstStep, IppiSize roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_16u_C1R)( pSrc, srcStep, pDst, dstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_C3R( const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, 
                             int dstStep, IppiSize roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_16u_C3R)( pSrc, srcStep, pDst, dstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_AC4R( const Ipp16u* pSrc, int srcStep, Ipp16u* 
                             pDst, int dstStep, IppiSize roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_16u_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_C4R( const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, 
                             int dstStep, IppiSize roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_16u_C4R)( pSrc, srcStep, pDst, dstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_C1R( Ipp16u* pSrcDst, int srcDstStep, IppiSize 
                             roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_16u_C1IR)( pSrcDst, srcDstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_C3R( Ipp16u* pSrcDst, int srcDstStep, IppiSize 
                             roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_16u_C3IR)( pSrcDst, srcDstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_AC4R( Ipp16u* pSrcDst, int srcDstStep, IppiSize 
                             roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_16u_AC4IR)( pSrcDst, srcDstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_C4R( Ipp16u* pSrcDst, int srcDstStep, IppiSize 
                             roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_16u_C4IR)( pSrcDst, srcDstStep, roiSize, flip ); 
     } 

IPPI_WRAP ippiMirror_C1R( const Ipp32s* pSrc, int srcStep, Ipp32s* pDst, 
                             int dstStep, IppiSize roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_32s_C1R)( pSrc, srcStep, pDst, dstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_C3R( const Ipp32s* pSrc, int srcStep, Ipp32s* pDst, 
                             int dstStep, IppiSize roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_32s_C3R)( pSrc, srcStep, pDst, dstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_AC4R( const Ipp32s* pSrc, int srcStep, Ipp32s* 
                             pDst, int dstStep, IppiSize roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_32s_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_C4R( const Ipp32s* pSrc, int srcStep, Ipp32s* pDst, 
                             int dstStep, IppiSize roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_32s_C4R)( pSrc, srcStep, pDst, dstStep, roiSize, flip ); 
     } 

IPPI_WRAP ippiMirror_C1R( Ipp32s* pSrcDst, int srcDstStep, IppiSize 
                             roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_32s_C1IR)( pSrcDst, srcDstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_C3R( Ipp32s* pSrcDst, int srcDstStep, IppiSize 
                             roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_32s_C3IR)( pSrcDst, srcDstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_AC4R( Ipp32s* pSrcDst, int srcDstStep, IppiSize 
                             roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_32s_AC4IR)( pSrcDst, srcDstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_C4R( Ipp32s* pSrcDst, int srcDstStep, IppiSize 
                             roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_32s_C4IR)( pSrcDst, srcDstStep, roiSize, flip ); 
     } 


IPPI_WRAP ippiMirror_C1R( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, 
                             int dstStep, IppiSize roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_32s_C1R)( (const Ipp32s*)pSrc, srcStep, (Ipp32s*)pDst, dstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_C3R( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, 
                             int dstStep, IppiSize roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_32s_C3R)( (const Ipp32s*)pSrc, srcStep, (Ipp32s*)pDst, dstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_AC4R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_32s_AC4R)( (const Ipp32s*)pSrc, srcStep, (Ipp32s*)pDst, dstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_C4R( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, 
                             int dstStep, IppiSize roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_32s_C4R)( (const Ipp32s*)pSrc, srcStep, (Ipp32s*)pDst, dstStep, roiSize, flip ); 
     } 

IPPI_WRAP ippiMirror_C1R( Ipp32f* pSrcDst, int srcDstStep, IppiSize 
                             roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_32s_C1IR)( (Ipp32s*)pSrcDst, srcDstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_C3R( Ipp32f* pSrcDst, int srcDstStep, IppiSize 
                             roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_32s_C3IR)( (Ipp32s*)pSrcDst, srcDstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_AC4R( Ipp32f* pSrcDst, int srcDstStep, IppiSize 
                             roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_32s_AC4IR)( (Ipp32s*)pSrcDst, srcDstStep, roiSize, flip ); 
     } 
IPPI_WRAP ippiMirror_C4R( Ipp32f* pSrcDst, int srcDstStep, IppiSize 
                             roiSize, IppiAxis flip) { 
     return IPPCALL(ippiMirror_32s_C4IR)( (Ipp32s*)pSrcDst, srcDstStep, roiSize, flip ); 
     } 

IPPI_WRAP ippiRotate_C1R( const Ipp8u* pSrc, IppiSize srcSize, int 
                             srcStep, IppiRect srcRoi, Ipp8u* pDst, int dstStep, 
                             IppiRect dstRoi, double angle, double xShift, double 
                             yShift, int interpolation) { 
     return IPPCALL(ippiRotate_8u_C1R)( pSrc, srcSize, srcStep, srcRoi, pDst, dstStep, dstRoi, 
                             angle, xShift, yShift, interpolation ); 
     } 
IPPI_WRAP ippiRotate_C3R( const Ipp8u* pSrc, IppiSize srcSize, int 
                             srcStep, IppiRect srcRoi, Ipp8u* pDst, int dstStep, 
                             IppiRect dstRoi, double angle, double xShift, double 
                             yShift, int interpolation) { 
     return IPPCALL(ippiRotate_8u_C3R)( pSrc, srcSize, srcStep, srcRoi, pDst, dstStep, dstRoi, 
                             angle, xShift, yShift, interpolation ); 
     } 

IPPI_WRAP ippiRotate_C4R( const Ipp8u* pSrc, IppiSize srcSize, int 
                             srcStep, IppiRect srcRoi, Ipp8u* pDst, int dstStep, 
                             IppiRect dstRoi, double angle, double xShift, double 
                             yShift, int interpolation) { 
     return IPPCALL(ippiRotate_8u_C4R)( pSrc, srcSize, srcStep, srcRoi, pDst, dstStep, dstRoi, 
                             angle, xShift, yShift, interpolation ); 
     } 

IPPI_WRAP ippiRotate_C1R( const Ipp32f* pSrc, IppiSize srcSize, int 
                             srcStep, IppiRect srcRoi, Ipp32f* pDst, int dstStep, 
                             IppiRect dstRoi, double angle, double xShift, double 
                             yShift, int interpolation) { 
     return IPPCALL(ippiRotate_32f_C1R)( pSrc, srcSize, srcStep, srcRoi, pDst, dstStep, dstRoi, 
                             angle, xShift, yShift, interpolation ); 
     } 
IPPI_WRAP ippiRotate_C3R( const Ipp32f* pSrc, IppiSize srcSize, int 
                             srcStep, IppiRect srcRoi, Ipp32f* pDst, int dstStep, 
                             IppiRect dstRoi, double angle, double xShift, double 
                             yShift, int interpolation) { 
     return IPPCALL(ippiRotate_32f_C3R)( pSrc, srcSize, srcStep, srcRoi, pDst, dstStep, dstRoi, 
                             angle, xShift, yShift, interpolation ); 
     } 

IPPI_WRAP ippiRotate_C4R( const Ipp32f* pSrc, IppiSize srcSize, int 
                             srcStep, IppiRect srcRoi, Ipp32f* pDst, int dstStep, 
                             IppiRect dstRoi, double angle, double xShift, double 
                             yShift, int interpolation) { 
     return IPPCALL(ippiRotate_32f_C4R)( pSrc, srcSize, srcStep, srcRoi, pDst, dstStep, dstRoi, 
                             angle, xShift, yShift, interpolation ); 
     } 

IPPI_WRAP ippiRotate_C1R( const Ipp16u* pSrc, IppiSize srcSize, int 
                             srcStep, IppiRect srcRoi, Ipp16u* pDst, int dstStep, 
                             IppiRect dstRoi, double angle, double xShift, double 
                             yShift, int interpolation) { 
     return IPPCALL(ippiRotate_16u_C1R)( pSrc, srcSize, srcStep, srcRoi, pDst, dstStep, dstRoi, 
                             angle, xShift, yShift, interpolation ); 
     } 
IPPI_WRAP ippiRotate_C3R( const Ipp16u* pSrc, IppiSize srcSize, int 
                             srcStep, IppiRect srcRoi, Ipp16u* pDst, int dstStep, 
                             IppiRect dstRoi, double angle, double xShift, double 
                             yShift, int interpolation) { 
     return IPPCALL(ippiRotate_16u_C3R)( pSrc, srcSize, srcStep, srcRoi, pDst, dstStep, dstRoi, 
                             angle, xShift, yShift, interpolation ); 
     } 

IPPI_WRAP ippiRotate_C4R( const Ipp16u* pSrc, IppiSize srcSize, int 
                             srcStep, IppiRect srcRoi, Ipp16u* pDst, int dstStep, 
                             IppiRect dstRoi, double angle, double xShift, double 
                             yShift, int interpolation) { 
     return IPPCALL(ippiRotate_16u_C4R)( pSrc, srcSize, srcStep, srcRoi, pDst, dstStep, dstRoi, 
                             angle, xShift, yShift, interpolation ); 
     } 
IPPI_WRAP ippiMulCScale_C1R( const Ipp32f* pSrc, int srcStep, Ipp32f 
                             value, Ipp32f* pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiMulC_32f_C1R)( pSrc, srcStep, value/GetEnv()->FloatMax, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiMulCScale_C3R( const Ipp32f* pSrc, int srcStep, const Ipp32f 
                             value[3], Ipp32f* pDst, int dstStep, IppiSize roiSize) 
	 { Ipp32f scale[3]; 
		scale[0] = value[0]/GetEnv()->FloatMax; 
		scale[1] = value[1]/GetEnv()->FloatMax; 
		scale[2] = value[2]/GetEnv()->FloatMax; 
		return IPPCALL(ippiMulC_32f_C3R)( pSrc, srcStep, scale, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiMulCScale_C4R( const Ipp32f* pSrc, int srcStep, const Ipp32f 
                             value[4], Ipp32f* pDst, int dstStep, IppiSize roiSize) 
	 {Ipp32f scale[4]; 
		scale[0] = value[0]/GetEnv()->FloatMax; 
		scale[1] = value[1]/GetEnv()->FloatMax; 
		scale[2] = value[2]/GetEnv()->FloatMax; 
		scale[3] = value[3]/GetEnv()->FloatMax; 
     return IPPCALL(ippiMulC_32f_C4R)( pSrc, srcStep, scale, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiMulCScale_C1R( Ipp32f value, Ipp32f* pSrcDst, int 
                             srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiMulC_32f_C1IR)( value/GetEnv()->FloatMax, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiMulCScale_C3R( const Ipp32f value[3], Ipp32f* pSrcDst, int 
                             srcDstStep, IppiSize roiSize) 
	 {Ipp32f scale[3]; 
		scale[0] = value[0]/GetEnv()->FloatMax; 
		scale[1] = value[1]/GetEnv()->FloatMax; 
		scale[2] = value[2]/GetEnv()->FloatMax; 
     return IPPCALL(ippiMulC_32f_C3IR)( scale, pSrcDst, srcDstStep, roiSize ); 
     } 


IPPI_WRAP ippiMulCScale_C1R( const Ipp8u* pSrc, int srcStep, Ipp8u 
                             value, Ipp8u* pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiMulCScale_8u_C1R)( pSrc, srcStep, value, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiMulCScale_C3R( const Ipp8u* pSrc, int srcStep, const Ipp8u 
                             value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiMulCScale_8u_C3R)( pSrc, srcStep, value, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiMulCScale_C4R( const Ipp8u* pSrc, int srcStep, const Ipp8u 
                             value[4], Ipp8u* pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiMulCScale_8u_C4R)( pSrc, srcStep, value, pDst, dstStep, roiSize ); 
     } 

IPPI_WRAP ippiMulCScale_C1R( Ipp8u value, Ipp8u* pSrcDst, int 
                             srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiMulCScale_8u_C1IR)( value, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiMulCScale_C3R( const Ipp8u value[3], Ipp8u* pSrcDst, int 
                             srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiMulCScale_8u_C3IR)( value, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiMulCScale_C4R( const Ipp8u value[4], Ipp8u* pSrcDst, int 
                             srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiMulCScale_8u_C4IR)( value, pSrcDst, srcDstStep, roiSize ); 
     } 

IPPI_WRAP ippiMulScale_C1R( const Ipp16u* pSrc1, int src1Step, const 
                             Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, 
                             IppiSize roiSize) { 
     return IPPCALL(ippiMulScale_16u_C1R)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize ); 
     } 
IPPI_WRAP ippiMulScale_C3R( const Ipp16u* pSrc1, int src1Step, const 
                             Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, 
                             IppiSize roiSize) { 
     return IPPCALL(ippiMulScale_16u_C3R)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize ); 
     } 
IPPI_WRAP ippiMulScale_C4R( const Ipp16u* pSrc1, int src1Step, const 
                             Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, 
                             IppiSize roiSize) { 
     return IPPCALL(ippiMulScale_16u_C4R)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize ); 
     } 

IPPI_WRAP ippiMulScale_C1R( const Ipp16u* pSrc, int srcStep, Ipp16u* 
                             pSrcDst, int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiMulScale_16u_C1IR)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiMulScale_C3R( const Ipp16u* pSrc, int srcStep, Ipp16u* 
                             pSrcDst, int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiMulScale_16u_C3IR)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiMulScale_C4R( const Ipp16u* pSrc, int srcStep, Ipp16u* 
                             pSrcDst, int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiMulScale_16u_C4IR)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize ); 
     } 

IPPI_WRAP ippiMulCScale_C1R( const Ipp16u* pSrc, int srcStep, Ipp16u 
                             value, Ipp16u* pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiMulCScale_16u_C1R)( pSrc, srcStep, value, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiMulCScale_C3R( const Ipp16u* pSrc, int srcStep, const 
                             Ipp16u value[3], Ipp16u* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiMulCScale_16u_C3R)( pSrc, srcStep, value, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiMulCScale_C4R( const Ipp16u* pSrc, int srcStep, const 
                             Ipp16u value[4], Ipp16u* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiMulCScale_16u_C4R)( pSrc, srcStep, value, pDst, dstStep, roiSize ); 
     } 

IPPI_WRAP ippiMulCScale_C1R( Ipp16u value, Ipp16u* pSrcDst, int 
                             srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiMulCScale_16u_C1IR)( value, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiMulCScale_C3R( const Ipp16u value[3], Ipp16u* pSrcDst, int 
                             srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiMulCScale_16u_C3IR)( value, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiMulCScale_C4R( const Ipp16u value[4], Ipp16u* pSrcDst, int 
                             srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiMulCScale_16u_C4IR)( value, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiMul_C1R( const Ipp8u* pSrc1, int src1Step, const Ipp8u* 
                             pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiMul_8u_C1RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiMul_C3R( const Ipp8u* pSrc1, int src1Step, const Ipp8u* 
                             pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiMul_8u_C3RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiMul_C4R( const Ipp8u* pSrc1, int src1Step, const Ipp8u* 
                             pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiMul_8u_C4RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, GetEnv()->ResultBitShift ); 
     } 

IPPI_WRAP ippiMul_C1R( const Ipp16s* pSrc1, int src1Step, const Ipp16s* 
                             pSrc2, int src2Step, Ipp16s* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiMul_16s_C1RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiMul_C3R( const Ipp16s* pSrc1, int src1Step, const Ipp16s* 
                             pSrc2, int src2Step, Ipp16s* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiMul_16s_C3RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiMul_C4R( const Ipp16s* pSrc1, int src1Step, const Ipp16s* 
                             pSrc2, int src2Step, Ipp16s* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiMul_16s_C4RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiDiv_C1R( const Ipp32f* pSrc1, int src1Step, const Ipp32f* 
                             pSrc2, int src2Step, Ipp32f* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiDiv_32f_C1R)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize 
                             ); 
     } 
IPPI_WRAP ippiDiv_C3R( const Ipp32f* pSrc1, int src1Step, const Ipp32f* 
                             pSrc2, int src2Step, Ipp32f* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiDiv_32f_C3R)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize 
                             ); 
     } 
IPPI_WRAP ippiDiv_C4R( const Ipp32f* pSrc1, int src1Step, const Ipp32f* 
                             pSrc2, int src2Step, Ipp32f* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiDiv_32f_C4R)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize 
                             ); 
     }
IPPI_WRAP ippiDiv_C1R( const Ipp16s* pSrc1, int src1Step, const Ipp16s* 
                             pSrc2, int src2Step, Ipp16s* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiDiv_16s_C1RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiDiv_C3R( const Ipp16s* pSrc1, int src1Step, const Ipp16s* 
                             pSrc2, int src2Step, Ipp16s* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiDiv_16s_C3RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiDiv_C1R( const Ipp8u* pSrc1, int src1Step, const Ipp8u* 
                             pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiDiv_8u_C1RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiDiv_C3R( const Ipp8u* pSrc1, int src1Step, const Ipp8u* 
                             pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiDiv_8u_C3RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiDiv_C1R( const Ipp32f* pSrc, int srcStep, Ipp32f value, 
                             Ipp32f* pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiDivC_32f_C1R)( pSrc, srcStep, value, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiDiv_C3R( const Ipp32f* pSrc, int srcStep, const Ipp32f 
                             value[3], Ipp32f* pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiDivC_32f_C3R)( pSrc, srcStep, value, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiDiv_C1R( const Ipp16s* pSrc, int srcStep, Ipp16s value, 
                             Ipp16s* pDst, int dstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiDivC_16s_C1RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiDiv_C3R( const Ipp16s* pSrc, int srcStep, const Ipp16s 
                             value[3], Ipp16s* pDst, int dstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiDivC_16s_C3RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiDiv_C1R( const Ipp8u* pSrc, int srcStep, Ipp8u value, 
                             Ipp8u* pDst, int dstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiDivC_8u_C1RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiDiv_C3R( const Ipp8u* pSrc, int srcStep, const Ipp8u 
                             value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiDivC_8u_C3RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiDiv_C1R( const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst, 
                             int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiDiv_32f_C1IR)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiDiv_C3R( const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst, 
                             int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiDiv_32f_C3IR)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiDiv_C4R( const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst, 
                             int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiDiv_32f_C4IR)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiDiv_C1R( const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst, 
                             int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiDiv_16s_C1IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
								 GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiDiv_C3R( const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst, 
                             int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiDiv_16s_C3IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiDiv_C1R( const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, 
                             int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiDiv_8u_C1IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiDiv_C3R( const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, 
                             int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiDiv_8u_C3IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiDiv_C1R( Ipp32f value, Ipp32f* pSrcDst, int srcDstStep, 
                             IppiSize roiSize) { 
     return IPPCALL(ippiDivC_32f_C1IR)( value, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiDiv_C3R( const Ipp32f value[3], Ipp32f* pSrcDst, int 
                             srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiDivC_32f_C3IR)( value, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiDiv_C1R( Ipp16s value, Ipp16s* pSrcDst, int srcDstStep, 
                             IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiDivC_16s_C1IRSfs)( value, pSrcDst, srcDstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiDiv_C3R( const Ipp16s value[3], Ipp16s* pSrcDst, int 
                             srcDstStep, IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiDivC_16s_C3IRSfs)( value, pSrcDst, srcDstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiDiv_C1R( Ipp8u value, Ipp8u* pSrcDst, int srcDstStep, 
                             IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiDivC_8u_C1IRSfs)( value, pSrcDst, srcDstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiDiv_C3R( const Ipp8u value[3], Ipp8u* pSrcDst, int 
                             srcDstStep, IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiDivC_8u_C3IRSfs)( value, pSrcDst, srcDstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiDiv_C1R( const Ipp32fc* pSrc, int srcStep, Ipp32fc value, 
                             Ipp32fc* pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiDivC_32fc_C1R)( pSrc, srcStep, value, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiDiv_C3R( const Ipp32fc* pSrc, int srcStep, const Ipp32fc 
                             value[3], Ipp32fc* pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiDivC_32fc_C3R)( pSrc, srcStep, value, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiDiv_C1R( Ipp32fc value, Ipp32fc* pSrcDst, int srcDstStep, 
                             IppiSize roiSize) { 
     return IPPCALL(ippiDivC_32fc_C1IR)( value, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiDiv_C3R( const Ipp32fc value[3], Ipp32fc* pSrcDst, int 
                             srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiDivC_32fc_C3IR)( value, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiDiv_C1R( const Ipp32fc* pSrc, int srcStep, Ipp32fc* 
                             pSrcDst, int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiDiv_32fc_C1IR)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiDiv_C3R( const Ipp32fc* pSrc, int srcStep, Ipp32fc* 
                             pSrcDst, int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiDiv_32fc_C3IR)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiDiv_C1R( const Ipp32fc* pSrc1, int src1Step, const 
                             Ipp32fc* pSrc2, int src2Step, Ipp32fc* pDst, int dstStep, 
                             IppiSize roiSize) { 
     return IPPCALL(ippiDiv_32fc_C1R)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize 
                             ); 
     } 
IPPI_WRAP ippiDiv_C3R( const Ipp32fc* pSrc1, int src1Step, const 
                             Ipp32fc* pSrc2, int src2Step, Ipp32fc* pDst, int dstStep, 
                             IppiSize roiSize) { 
     return IPPCALL(ippiDiv_32fc_C3R)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize 
                             ); 
     } 
IPPI_WRAP ippiDiv_C1R( const Ipp16sc* pSrc, int srcStep, Ipp16sc* 
                             pSrcDst, int srcDstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiDiv_16sc_C1IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiDiv_C3R( const Ipp16sc* pSrc, int srcStep, Ipp16sc* 
                             pSrcDst, int srcDstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiDiv_16sc_C3IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiDiv_C1R( const Ipp16sc* pSrc1, int src1Step, const 
                             Ipp16sc* pSrc2, int src2Step, Ipp16sc* pDst, int dstStep, 
                             IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiDiv_16sc_C1RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiDiv_C3R( const Ipp16sc* pSrc1, int src1Step, const 
                             Ipp16sc* pSrc2, int src2Step, Ipp16sc* pDst, int dstStep, 
                             IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiDiv_16sc_C3RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiDiv_C1R( const Ipp32sc* pSrc, int srcStep, Ipp32sc* 
                             pSrcDst, int srcDstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiDiv_32sc_C1IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiDiv_C3R( const Ipp32sc* pSrc, int srcStep, Ipp32sc* 
                             pSrcDst, int srcDstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiDiv_32sc_C3IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiDiv_C1R( const Ipp32sc* pSrc1, int src1Step, const 
                             Ipp32sc* pSrc2, int src2Step, Ipp32sc* pDst, int dstStep, 
                             IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiDiv_32sc_C1RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiDiv_C3R( const Ipp32sc* pSrc1, int src1Step, const 
                             Ipp32sc* pSrc2, int src2Step, Ipp32sc* pDst, int dstStep, 
                             IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiDiv_32sc_C3RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiDiv_C1R( Ipp16sc value, Ipp16sc* pSrcDst, int srcDstStep, 
                             IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiDivC_16sc_C1IRSfs)( value, pSrcDst, srcDstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiDiv_C3R( const Ipp16sc value[3], Ipp16sc* pSrcDst, int 
                             srcDstStep, IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiDivC_16sc_C3IRSfs)( value, pSrcDst, srcDstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiDiv_C1R( const Ipp16sc* pSrc, int srcStep, Ipp16sc value, 
                             Ipp16sc* pDst, int dstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiDivC_16sc_C1RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiDiv_C3R( const Ipp16sc* pSrc, int srcStep, const Ipp16sc 
                             value[3], Ipp16sc* pDst, int dstStep, IppiSize roiSize, 
                             int scaleFactor) { 
     return IPPCALL(ippiDivC_16sc_C3RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiDiv_C1R( Ipp32sc value, Ipp32sc* pSrcDst, int srcDstStep, 
                             IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiDivC_32sc_C1IRSfs)( value, pSrcDst, srcDstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiDiv_C3R( const Ipp32sc value[3], Ipp32sc* pSrcDst, int 
                             srcDstStep, IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiDivC_32sc_C3IRSfs)( value, pSrcDst, srcDstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiDiv_C1R( const Ipp32sc* pSrc, int srcStep, Ipp32sc value, 
                             Ipp32sc* pDst, int dstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiDivC_32sc_C1RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiDiv_C3R( const Ipp32sc* pSrc, int srcStep, const Ipp32sc 
                             value[3], Ipp32sc* pDst, int dstStep, IppiSize roiSize, 
                             int scaleFactor) { 
     return IPPCALL(ippiDivC_32sc_C3RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiSqr_C1R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int 
                             dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqr_8u_C1RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqr_C3R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int 
                             dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqr_8u_C3RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqr_C4R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int 
                             dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqr_8u_C4RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqr_C1R( const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqr_16u_C1RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqr_C3R( const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqr_16u_C3RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 

IPPI_WRAP ippiSqr_C4R( const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqr_16u_C4RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqr_C1R( const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqr_16s_C1RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqr_C3R( const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqr_16s_C3RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqr_C4R( const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqr_16s_C4RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqr_C1R( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqr_32f_C1R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiSqr_C3R( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqr_32f_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiSqr_C4R( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqr_32f_C4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiSqr_C1R( Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqr_8u_C1IRSfs)( pSrcDst, srcDstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqr_C3R( Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqr_8u_C3IRSfs)( pSrcDst, srcDstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqr_C4R( Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqr_8u_C4IRSfs)( pSrcDst, srcDstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqr_C1R( Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqr_16u_C1IRSfs)( pSrcDst, srcDstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqr_C3R( Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqr_16u_C3IRSfs)( pSrcDst, srcDstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqr_C4R( Ipp16u* pSrcDst, int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqr_16u_C4IRSfs)( pSrcDst, srcDstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqr_C1R( Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqr_16s_C1IRSfs)( pSrcDst, srcDstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqr_C3R( Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqr_16s_C3IRSfs)( pSrcDst, srcDstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqr_C4R( Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqr_16s_C4IRSfs)( pSrcDst, srcDstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqr_C1R( Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqr_32f_C1IR)( pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiSqr_C3R( Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqr_32f_C3IR)( pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiSqr_C4R( Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqr_32f_C4IR)( pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiSqrt_C1R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int 
                             dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqrt_8u_C1RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqrt_C3R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int 
                             dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqrt_8u_C3RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqrt_AC4R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqrt_8u_AC4RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqrt_C1R( const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqrt_16u_C1RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqrt_C3R( const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqrt_16u_C3RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqrt_AC4R( const Ipp16u* pSrc, int srcStep, Ipp16u* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqrt_16u_AC4RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqrt_C1R( const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqrt_16s_C1RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqrt_C3R( const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqrt_16s_C3RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqrt_AC4R( const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqrt_16s_AC4RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqrt_C1R( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqrt_32f_C1R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiSqrt_C3R( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqrt_32f_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiSqrt_AC4R( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSqrt_32f_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiSqrt_C1R( Ipp8u* pSrcDst, int srcDstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiSqrt_8u_C1IRSfs)( pSrcDst, srcDstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqrt_C3R( Ipp8u* pSrcDst, int srcDstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiSqrt_8u_C3IRSfs)( pSrcDst, srcDstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqrt_AC4R( Ipp8u* pSrcDst, int srcDstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiSqrt_8u_AC4IRSfs)( pSrcDst, srcDstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqrt_C1R( Ipp16u* pSrcDst, int srcDstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiSqrt_16u_C1IRSfs)( pSrcDst, srcDstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqrt_C3R( Ipp16u* pSrcDst, int srcDstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiSqrt_16u_C3IRSfs)( pSrcDst, srcDstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqrt_AC4R( Ipp16u* pSrcDst, int srcDstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiSqrt_16u_AC4IRSfs)( pSrcDst, srcDstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqrt_C1R( Ipp16s* pSrcDst, int srcDstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiSqrt_16s_C1IRSfs)( pSrcDst, srcDstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqrt_C3R( Ipp16s* pSrcDst, int srcDstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiSqrt_16s_C3IRSfs)( pSrcDst, srcDstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqrt_AC4R( Ipp16s* pSrcDst, int srcDstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiSqrt_16s_AC4IRSfs)( pSrcDst, srcDstStep, roiSize, GetEnv()->IntegerScaleFactor ); 
     } 
IPPI_WRAP ippiSqrt_C1R( Ipp32f* pSrcDst, int srcDstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiSqrt_32f_C1IR)( pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiSqrt_C3R( Ipp32f* pSrcDst, int srcDstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiSqrt_32f_C3IR)( pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiSqrt_AC4R( Ipp32f* pSrcDst, int srcDstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiSqrt_32f_AC4IR)( pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiSqrt_C4R( Ipp32f* pSrcDst, int srcDstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiSqrt_32f_C4IR)( pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiCopy_C3C1R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiCopy_8u_C3C1R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiCopy_C1C3R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiCopy_8u_C1C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiCopy_C4C1R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiCopy_8u_C4C1R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiCopy_C1C4R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiCopy_8u_C1C4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 

IPPI_WRAP ippiCopy_C3C1R( const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiCopy_16s_C3C1R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiCopy_C1C3R( const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiCopy_16s_C1C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiCopy_C4C1R( const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiCopy_16s_C4C1R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiCopy_C1C4R( const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiCopy_16s_C1C4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 

IPPI_WRAP ippiCopy_C3C1R( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiCopy_32f_C3C1R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiCopy_C1C3R( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiCopy_32f_C1C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiCopy_C4C1R( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiCopy_32f_C4C1R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiCopy_C1C4R( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiCopy_32f_C1C4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiAddWeighted_C1R( const Ipp8u* pSrc, int srcStep, 
												Ipp32f* pSrcDst, int SrcDstStep, 
												IppiSize roiSize, Ipp32f alpha) 
 { 
     return IPPCALL(ippiAddWeighted_8u32f_C1IR)( pSrc,srcStep,pSrcDst,SrcDstStep,roiSize,alpha); 
 } 
IPPI_WRAP ippiAddWeighted_C1R( const Ipp16u* pSrc, int srcStep, 
												Ipp32f* pSrcDst, int SrcDstStep, 
												IppiSize roiSize, Ipp32f alpha) 
 { 
     return IPPCALL(ippiAddWeighted_16u32f_C1IR)( pSrc,srcStep,pSrcDst,SrcDstStep,roiSize,alpha); 
 } 
IPPI_WRAP ippiAddWeighted_C1R( const Ipp32f* pSrc, int srcStep, 
												Ipp32f* pSrcDst, int SrcDstStep, 
												IppiSize roiSize, Ipp32f alpha) 
 { 
     return IPPCALL(ippiAddWeighted_32f_C1IR)( pSrc,srcStep,pSrcDst,SrcDstStep,roiSize,alpha); 
 } 
IPPI_WRAP ippiAdd_C1R( const Ipp8u* pSrc1, int src1Step, const Ipp8u* 
                             pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiAdd_8u_C1RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
								roiSize, GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiAdd_C3R( const Ipp8u* pSrc1, int src1Step, const Ipp8u* 
                             pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiAdd_8u_C3RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiAdd_C4R( const Ipp8u* pSrc1, int src1Step, const Ipp8u* 
                             pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiAdd_8u_C4RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, GetEnv()->ResultBitShift ); 
     } 

IPPI_WRAP ippiAdd_C1R( const Ipp16s* pSrc1, int src1Step, const Ipp16s* 
                             pSrc2, int src2Step, Ipp16s* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiAdd_16s_C1RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiAdd_C3R( const Ipp16s* pSrc1, int src1Step, const Ipp16s* 
                             pSrc2, int src2Step, Ipp16s* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiAdd_16s_C3RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiAdd_C4R( const Ipp16s* pSrc1, int src1Step, const Ipp16s* 
                             pSrc2, int src2Step, Ipp16s* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiAdd_16s_C4RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, GetEnv()->ResultBitShift ); 
     } 

IPPI_WRAP ippiSub_C1R( const Ipp8u* pSrc1, int src1Step, const Ipp8u* 
                             pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize 
                             roiSize, int scaleFactor) { 
     return IPPCALL(ippiSub_8u_C1RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiSub_C3R( const Ipp8u* pSrc1, int src1Step, const Ipp8u* 
                             pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize 
                             roiSize, int scaleFactor) { 
     return IPPCALL(ippiSub_8u_C3RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiSub_C4R( const Ipp8u* pSrc1, int src1Step, const Ipp8u* 
                             pSrc2, int src2Step, Ipp8u* pDst, int dstStep, IppiSize 
                             roiSize, int scaleFactor) { 
     return IPPCALL(ippiSub_8u_C4RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, scaleFactor ); 
     } 

IPPI_WRAP ippiSub_C1R( const Ipp16s* pSrc1, int src1Step, const Ipp16s* 
                             pSrc2, int src2Step, Ipp16s* pDst, int dstStep, IppiSize 
                             roiSize, int scaleFactor) { 
     return IPPCALL(ippiSub_16s_C1RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiSub_C3R( const Ipp16s* pSrc1, int src1Step, const Ipp16s* 
                             pSrc2, int src2Step, Ipp16s* pDst, int dstStep, IppiSize 
                             roiSize, int scaleFactor) { 
     return IPPCALL(ippiSub_16s_C3RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiSub_C4R( const Ipp16s* pSrc1, int src1Step, const Ipp16s* 
                             pSrc2, int src2Step, Ipp16s* pDst, int dstStep, IppiSize 
                             roiSize, int scaleFactor) { 
     return IPPCALL(ippiSub_16s_C4RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiAdd_C1R( Ipp8u value, Ipp8u* pSrcDst, int srcDstStep, 
	 IppiSize roiSize) { 
     return IPPCALL(ippiAddC_8u_C1IRSfs)( value, pSrcDst, srcDstStep, roiSize, GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiAdd_C3R( const Ipp8u value[3], Ipp8u* pSrcDst, int 
                             srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiAddC_8u_C3IRSfs)( value, pSrcDst, srcDstStep, roiSize, GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiAdd_C4R( const Ipp8u value[4], Ipp8u* pSrcDst, int 
                             srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiAddC_8u_C4IRSfs)( value, pSrcDst, srcDstStep, roiSize, GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiAdd_C1R( Ipp16s value, Ipp16s* pSrcDst, int srcDstStep, 
                             IppiSize roiSize) { 
     return IPPCALL(ippiAddC_16s_C1IRSfs)( value, pSrcDst, srcDstStep, roiSize, GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiAdd_C3R( const Ipp16s value[3], Ipp16s* pSrcDst, int 
                             srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiAddC_16s_C3IRSfs)( value, pSrcDst, srcDstStep, roiSize, GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiAdd_C4R( const Ipp16s value[4], Ipp16s* pSrcDst, int 
                             srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiAddC_16s_C4IRSfs)( value, pSrcDst, srcDstStep, roiSize, GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiSub_C1R( Ipp8u value, Ipp8u* pSrcDst, int srcDstStep, 
                             IppiSize roiSize) { 
     return IPPCALL(ippiSubC_8u_C1IRSfs)( value, pSrcDst, srcDstStep, roiSize, GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiSub_C3R( const Ipp8u value[3], Ipp8u* pSrcDst, int 
                             srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSubC_8u_C3IRSfs)( value, pSrcDst, srcDstStep, roiSize, GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiSub_C4R( const Ipp8u value[4], Ipp8u* pSrcDst, int 
                             srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSubC_8u_C4IRSfs)( value, pSrcDst, srcDstStep, roiSize, GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiSub_C1R( Ipp16s value, Ipp16s* pSrcDst, int srcDstStep, 
                             IppiSize roiSize) { 
     return IPPCALL(ippiSubC_16s_C1IRSfs)( value, pSrcDst, srcDstStep, roiSize, GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiSub_C3R( const Ipp16s value[3], Ipp16s* pSrcDst, int 
                             srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSubC_16s_C3IRSfs)( value, pSrcDst, srcDstStep, roiSize, GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiSub_C4R( const Ipp16s value[4], Ipp16s* pSrcDst, int 
                             srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSubC_16s_C4IRSfs)( value, pSrcDst, srcDstStep, roiSize, GetEnv()->ResultBitShift ); 
     } 
IPPI_WRAP ippiAdd_C1R( const Ipp8u* pSrc, int srcStep, Ipp8u value, 
                             Ipp8u* pDst, int dstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiAddC_8u_C1RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiAdd_C3R( const Ipp8u* pSrc, int srcStep, const Ipp8u 
                             value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiAddC_8u_C3RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiAdd_C4R( const Ipp8u* pSrc, int srcStep, const Ipp8u 
                             value[4], Ipp8u* pDst, int dstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiAddC_8u_C4RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiAdd_C1R( const Ipp16s* pSrc, int srcStep, Ipp16s value, 
                             Ipp16s* pDst, int dstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiAddC_16s_C1RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiAdd_C3R( const Ipp16s* pSrc, int srcStep, const Ipp16s 
                             value[3], Ipp16s* pDst, int dstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiAddC_16s_C3RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiAdd_C4R( const Ipp16s* pSrc, int srcStep, const Ipp16s 
                             value[4], Ipp16s* pDst, int dstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiAddC_16s_C4RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiSub_C1R( const Ipp8u* pSrc, int srcStep, Ipp8u value, 
                             Ipp8u* pDst, int dstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiSubC_8u_C1RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiSub_C3R( const Ipp8u* pSrc, int srcStep, const Ipp8u 
                             value[3], Ipp8u* pDst, int dstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiSubC_8u_C3RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiSub_C4R( const Ipp8u* pSrc, int srcStep, const Ipp8u 
                             value[4], Ipp8u* pDst, int dstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiSubC_8u_C4RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiSub_C1R( const Ipp16s* pSrc, int srcStep, Ipp16s value, 
                             Ipp16s* pDst, int dstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiSubC_16s_C1RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiSub_C3R( const Ipp16s* pSrc, int srcStep, const Ipp16s 
                             value[3], Ipp16s* pDst, int dstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiSubC_16s_C3RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiSub_C4R( const Ipp16s* pSrc, int srcStep, const Ipp16s 
                             value[4], Ipp16s* pDst, int dstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiSubC_16s_C4RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiAdd_C1R( const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, 
                             int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiAdd_8u_C1IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             GetEnv()->ResultBitShift); 
     } 

IPPI_WRAP ippiAdd_C3R( const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, 
                             int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiAdd_8u_C3IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             GetEnv()->ResultBitShift); 
     } 
IPPI_WRAP ippiAdd_C4R( const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, 
                             int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiAdd_8u_C4IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             GetEnv()->ResultBitShift); 
     } 
IPPI_WRAP ippiAdd_C1R( const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst, 
                             int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiAdd_16s_C1IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             GetEnv()->ResultBitShift); 
     } 
IPPI_WRAP ippiAdd_C3R( const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst, 
                             int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiAdd_16s_C3IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             GetEnv()->ResultBitShift); 
     } 
IPPI_WRAP ippiAdd_C4R( const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst, 
                             int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiAdd_16s_C4IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             GetEnv()->ResultBitShift); 
     } 
IPPI_WRAP ippiSub_C1R( const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, 
                             int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSub_8u_C1IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             1); 
     } 
IPPI_WRAP ippiSub_C3R( const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, 
                             int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSub_8u_C3IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             1); 
     } 
IPPI_WRAP ippiSub_C4R( const Ipp8u* pSrc, int srcStep, Ipp8u* pSrcDst, 
                             int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSub_8u_C4IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             1); 
     } 
IPPI_WRAP ippiSub_C1R( const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst, 
                             int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSub_16s_C1IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             1); 
     } 
IPPI_WRAP ippiSub_C3R( const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst, 
                             int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSub_16s_C3IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             1); 
     } 
IPPI_WRAP ippiSub_C4R( const Ipp16s* pSrc, int srcStep, Ipp16s* pSrcDst, 
                             int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSub_16s_C4IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             1); 
     }
IPPI_WRAP ippiAdd_C1R( const Ipp32f* pSrc, int srcStep, Ipp32f value, 
                             Ipp32f* pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiAddC_32f_C1R)( pSrc, srcStep, value, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiAdd_C3R( const Ipp32f* pSrc, int srcStep, const Ipp32f 
                             value[3], Ipp32f* pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiAddC_32f_C3R)( pSrc, srcStep, value, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiAdd_C4R( const Ipp32f* pSrc, int srcStep, const Ipp32f 
                             value[4], Ipp32f* pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiAddC_32f_C4R)( pSrc, srcStep, value, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiSub_C1R( const Ipp32f* pSrc, int srcStep, Ipp32f value, 
                             Ipp32f* pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSubC_32f_C1R)( pSrc, srcStep, value, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiSub_C3R( const Ipp32f* pSrc, int srcStep, const Ipp32f 
                             value[3], Ipp32f* pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSubC_32f_C3R)( pSrc, srcStep, value, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiSub_C4R( const Ipp32f* pSrc, int srcStep, const Ipp32f 
                             value[4], Ipp32f* pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSubC_32f_C4R)( pSrc, srcStep, value, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiAdd_C1R( Ipp32f value, Ipp32f* pSrcDst, int srcDstStep, 
                             IppiSize roiSize) { 
     return IPPCALL(ippiAddC_32f_C1IR)( value, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiAdd_C3R( const Ipp32f value[3], Ipp32f* pSrcDst, int 
                             srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiAddC_32f_C3IR)( value, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiAdd_C4R( const Ipp32f value[4], Ipp32f* pSrcDst, int 
                             srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiAddC_32f_C4IR)( value, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiSub_C1R( Ipp32f value, Ipp32f* pSrcDst, int srcDstStep, 
                             IppiSize roiSize) { 
     return IPPCALL(ippiSubC_32f_C1IR)( value, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiSub_C3R( const Ipp32f value[3], Ipp32f* pSrcDst, int 
                             srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSubC_32f_C3IR)( value, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiSub_C4R( const Ipp32f value[4], Ipp32f* pSrcDst, int 
                             srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSubC_32f_C4IR)( value, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiAdd_C1R( const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst, 
                             int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiAdd_32f_C1IR)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiAdd_C3R( const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst, 
                             int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiAdd_32f_C3IR)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiAdd_C4R( const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst, 
                             int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiAdd_32f_C4IR)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiSub_C1R( const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst, 
                             int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSub_32f_C1IR)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiSub_C3R( const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst, 
                             int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSub_32f_C3IR)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiSub_C4R( const Ipp32f* pSrc, int srcStep, Ipp32f* pSrcDst, 
                             int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSub_32f_C4IR)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiAdd_C1R( const Ipp32f* pSrc1, int src1Step, const Ipp32f* 
                             pSrc2, int src2Step, Ipp32f* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiAdd_32f_C1R)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize 
                             ); 
     } 
IPPI_WRAP ippiAdd_C3R( const Ipp32f* pSrc1, int src1Step, const Ipp32f* 
                             pSrc2, int src2Step, Ipp32f* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiAdd_32f_C3R)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize 
                             ); 
     } 
IPPI_WRAP ippiAdd_C4R( const Ipp32f* pSrc1, int src1Step, const Ipp32f* 
                             pSrc2, int src2Step, Ipp32f* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiAdd_32f_C4R)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize 
                             ); 
     } 
IPPI_WRAP ippiSub_C1R( const Ipp32f* pSrc1, int src1Step, const Ipp32f* 
                             pSrc2, int src2Step, Ipp32f* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiSub_32f_C1R)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize 
                             ); 
     } 
IPPI_WRAP ippiSub_C3R( const Ipp32f* pSrc1, int src1Step, const Ipp32f* 
                             pSrc2, int src2Step, Ipp32f* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiSub_32f_C3R)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize 
                             ); 
     } 
IPPI_WRAP ippiSub_C4R( const Ipp32f* pSrc1, int src1Step, const Ipp32f* 
                             pSrc2, int src2Step, Ipp32f* pDst, int dstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiSub_32f_C4R)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize 
                             ); 
     } 
IPPI_WRAP ippiAdd_C1R( const Ipp32fc* pSrc, int srcStep, Ipp32fc value, 
                             Ipp32fc* pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiAddC_32fc_C1R)( pSrc, srcStep, value, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiAdd_C3R( const Ipp32fc* pSrc, int srcStep, const Ipp32fc 
                             value[3], Ipp32fc* pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiAddC_32fc_C3R)( pSrc, srcStep, value, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiSub_C1R( const Ipp32fc* pSrc, int srcStep, Ipp32fc value, 
                             Ipp32fc* pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSubC_32fc_C1R)( pSrc, srcStep, value, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiSub_C3R( const Ipp32fc* pSrc, int srcStep, const Ipp32fc 
                             value[3], Ipp32fc* pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSubC_32fc_C3R)( pSrc, srcStep, value, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiAdd_C1R( Ipp32fc value, Ipp32fc* pSrcDst, int srcDstStep, 
                             IppiSize roiSize) { 
     return IPPCALL(ippiAddC_32fc_C1IR)( value, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiAdd_C3R( const Ipp32fc value[3], Ipp32fc* pSrcDst, int 
                             srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiAddC_32fc_C3IR)( value, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiSub_C1R( Ipp32fc value, Ipp32fc* pSrcDst, int srcDstStep, 
                             IppiSize roiSize) { 
     return IPPCALL(ippiSubC_32fc_C1IR)( value, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiSub_C3R( const Ipp32fc value[3], Ipp32fc* pSrcDst, int 
                             srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSubC_32fc_C3IR)( value, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiAdd_C1R( const Ipp32fc* pSrc, int srcStep, Ipp32fc* 
                             pSrcDst, int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiAdd_32fc_C1IR)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiAdd_C3R( const Ipp32fc* pSrc, int srcStep, Ipp32fc* 
                             pSrcDst, int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiAdd_32fc_C3IR)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiSub_C1R( const Ipp32fc* pSrc, int srcStep, Ipp32fc* 
                             pSrcDst, int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSub_32fc_C1IR)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiSub_C3R( const Ipp32fc* pSrc, int srcStep, Ipp32fc* 
                             pSrcDst, int srcDstStep, IppiSize roiSize) { 
     return IPPCALL(ippiSub_32fc_C3IR)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiAdd_C1R( const Ipp32fc* pSrc1, int src1Step, const 
                             Ipp32fc* pSrc2, int src2Step, Ipp32fc* pDst, int dstStep, 
                             IppiSize roiSize) { 
     return IPPCALL(ippiAdd_32fc_C1R)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize 
                             ); 
     } 
IPPI_WRAP ippiAdd_C3R( const Ipp32fc* pSrc1, int src1Step, const 
                             Ipp32fc* pSrc2, int src2Step, Ipp32fc* pDst, int dstStep, 
                             IppiSize roiSize) { 
     return IPPCALL(ippiAdd_32fc_C3R)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize 
                             ); 
     } 
IPPI_WRAP ippiSub_C1R( const Ipp32fc* pSrc1, int src1Step, const 
                             Ipp32fc* pSrc2, int src2Step, Ipp32fc* pDst, int dstStep, 
                             IppiSize roiSize) { 
     return IPPCALL(ippiSub_32fc_C1R)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize 
                             ); 
     } 
IPPI_WRAP ippiSub_C3R( const Ipp32fc* pSrc1, int src1Step, const 
                             Ipp32fc* pSrc2, int src2Step, Ipp32fc* pDst, int dstStep, 
                             IppiSize roiSize) { 
     return IPPCALL(ippiSub_32fc_C3R)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, roiSize 
                             ); 
     } 
IPPI_WRAP ippiAdd_C1R( const Ipp16sc* pSrc, int srcStep, Ipp16sc* 
                             pSrcDst, int srcDstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiAdd_16sc_C1IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiAdd_C3R( const Ipp16sc* pSrc, int srcStep, Ipp16sc* 
                             pSrcDst, int srcDstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiAdd_16sc_C3IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiSub_C1R( const Ipp16sc* pSrc, int srcStep, Ipp16sc* 
                             pSrcDst, int srcDstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiSub_16sc_C1IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiSub_C3R( const Ipp16sc* pSrc, int srcStep, Ipp16sc* 
                             pSrcDst, int srcDstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiSub_16sc_C3IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             scaleFactor ); 
     }
IPPI_WRAP ippiAdd_C1R( const Ipp16sc* pSrc1, int src1Step, const 
                             Ipp16sc* pSrc2, int src2Step, Ipp16sc* pDst, int dstStep, 
                             IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiAdd_16sc_C1RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiAdd_C3R( const Ipp16sc* pSrc1, int src1Step, const 
                             Ipp16sc* pSrc2, int src2Step, Ipp16sc* pDst, int dstStep, 
                             IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiAdd_16sc_C3RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiSub_C1R( const Ipp16sc* pSrc1, int src1Step, const 
                             Ipp16sc* pSrc2, int src2Step, Ipp16sc* pDst, int dstStep, 
                             IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiSub_16sc_C1RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiSub_C3R( const Ipp16sc* pSrc1, int src1Step, const 
                             Ipp16sc* pSrc2, int src2Step, Ipp16sc* pDst, int dstStep, 
                             IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiSub_16sc_C3RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiAdd_C1R( const Ipp32sc* pSrc, int srcStep, Ipp32sc* 
                             pSrcDst, int srcDstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiAdd_32sc_C1IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiAdd_C3R( const Ipp32sc* pSrc, int srcStep, Ipp32sc* 
                             pSrcDst, int srcDstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiAdd_32sc_C3IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiSub_C1R( const Ipp32sc* pSrc, int srcStep, Ipp32sc* 
                             pSrcDst, int srcDstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiSub_32sc_C1IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiSub_C3R( const Ipp32sc* pSrc, int srcStep, Ipp32sc* 
                             pSrcDst, int srcDstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiSub_32sc_C3IRSfs)( pSrc, srcStep, pSrcDst, srcDstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiAdd_C1R( const Ipp32sc* pSrc1, int src1Step, const 
                             Ipp32sc* pSrc2, int src2Step, Ipp32sc* pDst, int dstStep, 
                             IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiAdd_32sc_C1RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiAdd_C3R( const Ipp32sc* pSrc1, int src1Step, const 
                             Ipp32sc* pSrc2, int src2Step, Ipp32sc* pDst, int dstStep, 
                             IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiAdd_32sc_C3RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiSub_C1R( const Ipp32sc* pSrc1, int src1Step, const 
                             Ipp32sc* pSrc2, int src2Step, Ipp32sc* pDst, int dstStep, 
                             IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiSub_32sc_C1RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiSub_C3R( const Ipp32sc* pSrc1, int src1Step, const 
                             Ipp32sc* pSrc2, int src2Step, Ipp32sc* pDst, int dstStep, 
                             IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiSub_32sc_C3RSfs)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiAdd_C1R( Ipp16sc value, Ipp16sc* pSrcDst, int srcDstStep, 
                             IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiAddC_16sc_C1IRSfs)( value, pSrcDst, srcDstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiAdd_C3R( const Ipp16sc value[3], Ipp16sc* pSrcDst, int 
                             srcDstStep, IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiAddC_16sc_C3IRSfs)( value, pSrcDst, srcDstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiSub_C1R( Ipp16sc value, Ipp16sc* pSrcDst, int srcDstStep, 
                             IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiSubC_16sc_C1IRSfs)( value, pSrcDst, srcDstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiSub_C3R( const Ipp16sc value[3], Ipp16sc* pSrcDst, int 
                             srcDstStep, IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiSubC_16sc_C3IRSfs)( value, pSrcDst, srcDstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiAdd_C1R( const Ipp16sc* pSrc, int srcStep, Ipp16sc value, 
                             Ipp16sc* pDst, int dstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiAddC_16sc_C1RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiAdd_C3R( const Ipp16sc* pSrc, int srcStep, const Ipp16sc 
                             value[3], Ipp16sc* pDst, int dstStep, IppiSize roiSize, 
                             int scaleFactor) { 
     return IPPCALL(ippiAddC_16sc_C3RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiSub_C1R( const Ipp16sc* pSrc, int srcStep, Ipp16sc value, 
                             Ipp16sc* pDst, int dstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiSubC_16sc_C1RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiSub_C3R( const Ipp16sc* pSrc, int srcStep, const Ipp16sc 
                             value[3], Ipp16sc* pDst, int dstStep, IppiSize roiSize, 
                             int scaleFactor) { 
     return IPPCALL(ippiSubC_16sc_C3RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiAdd_C1R( Ipp32sc value, Ipp32sc* pSrcDst, int srcDstStep, 
                             IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiAddC_32sc_C1IRSfs)( value, pSrcDst, srcDstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiAdd_C3R( const Ipp32sc value[3], Ipp32sc* pSrcDst, int 
                             srcDstStep, IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiAddC_32sc_C3IRSfs)( value, pSrcDst, srcDstStep, roiSize, scaleFactor ); 
     } 

IPPI_WRAP ippiSub_C1R( Ipp32sc value, Ipp32sc* pSrcDst, int srcDstStep, 
                             IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiSubC_32sc_C1IRSfs)( value, pSrcDst, srcDstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiSub_C3R( const Ipp32sc value[3], Ipp32sc* pSrcDst, int 
                             srcDstStep, IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiSubC_32sc_C3IRSfs)( value, pSrcDst, srcDstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiAdd_C1R( const Ipp32sc* pSrc, int srcStep, Ipp32sc value, 
                             Ipp32sc* pDst, int dstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiAddC_32sc_C1RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiAdd_C3R( const Ipp32sc* pSrc, int srcStep, const Ipp32sc 
                             value[3], Ipp32sc* pDst, int dstStep, IppiSize roiSize, 
                             int scaleFactor) { 
     return IPPCALL(ippiAddC_32sc_C3RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiSub_C1R( const Ipp32sc* pSrc, int srcStep, Ipp32sc value, 
                             Ipp32sc* pDst, int dstStep, IppiSize roiSize, int 
                             scaleFactor) { 
     return IPPCALL(ippiSubC_32sc_C1RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 
IPPI_WRAP ippiSub_C3R( const Ipp32sc* pSrc, int srcStep, const Ipp32sc 
                             value[3], Ipp32sc* pDst, int dstStep, IppiSize roiSize, 
                             int scaleFactor) { 
     return IPPCALL(ippiSubC_32sc_C3RSfs)( pSrc, srcStep, value, pDst, dstStep, roiSize, 
                             scaleFactor ); 
     } 

IPPI_WRAP ippiAbsDiff_C1R(	const Ipp8u* pSrc1, int src1Step,
                            const Ipp8u* pSrc2, int src2Step,
                            Ipp8u* pDst, int dstStep, IppiSize roiSize )
{
	return IPPCALL(ippiAbsDiff_8u_C1R)(pSrc1,src1Step,pSrc2,src2Step,pDst,dstStep,roiSize);
}

IPPI_WRAP ippiAbsDiff_C1R(	const Ipp16u* pSrc1, int src1Step,
                            const Ipp16u* pSrc2, int src2Step,
                            Ipp16u* pDst, int dstStep, IppiSize roiSize )
{
	return IPPCALL(ippiAbsDiff_16u_C1R)(pSrc1,src1Step,pSrc2,src2Step,pDst,dstStep,roiSize);
}

IPPI_WRAP ippiAbsDiff_C1R(	const Ipp32f* pSrc1, int src1Step,
                            const Ipp32f* pSrc2, int src2Step,
                            Ipp32f* pDst, int dstStep, IppiSize roiSize )
{
	return IPPCALL(ippiAbsDiff_32f_C1R)(pSrc1,src1Step,pSrc2,src2Step,pDst,dstStep,roiSize);
}
IPPI_WRAP ippiSet_C3R( const Ipp8u value[3], Ipp8u* pDst, int dstStep, 
                             IppiSize roiSize) { 
     return IPPCALL(ippiSet_8u_C3R)( value, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiSet_C4R( const Ipp8u value[4], Ipp8u* pDst, int dstStep, 
                             IppiSize roiSize) { 
     return IPPCALL(ippiSet_8u_C4R)( value, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiSet_C3R( const Ipp16s value[3], Ipp16s* pDst, int dstStep, 
                             IppiSize roiSize) { 
     return IPPCALL(ippiSet_16s_C3R)( value, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiSet_C4R( const Ipp16s value[4], Ipp16s* pDst, int dstStep, 
                             IppiSize roiSize) { 
     return IPPCALL(ippiSet_16s_C4R)( value, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiSet_C3R( const Ipp32f value[3], Ipp32f* pDst, int dstStep, 
                             IppiSize roiSize) { 
     return IPPCALL(ippiSet_32f_C3R)( value, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiSet_C4R( const Ipp32f value[4], Ipp32f* pDst, int dstStep, 
                             IppiSize roiSize) { 
     return IPPCALL(ippiSet_32f_C4R)( value, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiLn_C1R( Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize) 
                             { 
     return IPPCALL(ippiLn_32f_C1IR)( pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiLn_C3R( Ipp32f* pSrcDst, int srcDstStep, IppiSize roiSize) 
                             { 
     return IPPCALL(ippiLn_32f_C3IR)( pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiLn_C1R( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int 
                             dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiLn_32f_C1R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiLn_C3R( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, int 
                             dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiLn_32f_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 

IPPI_WRAP ippiLn_C1R( Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize, 
                             int scaleFactor) { 
     return IPPCALL(ippiLn_16s_C1IRSfs)( pSrcDst, srcDstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiLn_C3R( Ipp16s* pSrcDst, int srcDstStep, IppiSize roiSize, 
                             int scaleFactor) { 
     return IPPCALL(ippiLn_16s_C3IRSfs)( pSrcDst, srcDstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiLn_C1R( const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int 
                             dstStep, IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiLn_16s_C1RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiLn_C3R( const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, int 
                             dstStep, IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiLn_16s_C3RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, scaleFactor ); 
     } 


IPPI_WRAP ippiLn_C1R( Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize, 
                             int scaleFactor) { 
     return IPPCALL(ippiLn_8u_C1IRSfs)( pSrcDst, srcDstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiLn_C3R( Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize, 
                             int scaleFactor) { 
     return IPPCALL(ippiLn_8u_C3IRSfs)( pSrcDst, srcDstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiLn_C1R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int 
                             dstStep, IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiLn_8u_C1RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiLn_C3R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int 
                             dstStep, IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiLn_8u_C3RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiExp_C1R( Ipp32f* pSrcDst, int srcDstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiExp_32f_C1IR)( pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiExp_C3R( Ipp32f* pSrcDst, int srcDstStep, IppiSize 
                             roiSize) { 
     return IPPCALL(ippiExp_32f_C3IR)( pSrcDst, srcDstStep, roiSize ); 
     } 
IPPI_WRAP ippiExp_C1R( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiExp_32f_C1R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiExp_C3R( const Ipp32f* pSrc, int srcStep, Ipp32f* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiExp_32f_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 

IPPI_WRAP ippiExp_C1R( Ipp16s* pSrcDst, int srcDstStep, IppiSize 
                             roiSize, int scaleFactor) { 
     return IPPCALL(ippiExp_16s_C1IRSfs)( pSrcDst, srcDstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiExp_C3R( Ipp16s* pSrcDst, int srcDstStep, IppiSize 
                             roiSize, int scaleFactor) { 
     return IPPCALL(ippiExp_16s_C3IRSfs)( pSrcDst, srcDstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiExp_C1R( const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, 
                             int dstStep, IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiExp_16s_C1RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiExp_C3R( const Ipp16s* pSrc, int srcStep, Ipp16s* pDst, 
                             int dstStep, IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiExp_16s_C3RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, scaleFactor ); 
     } 


IPPI_WRAP ippiExp_C1R( Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize, 
                             int scaleFactor) { 
     return IPPCALL(ippiExp_8u_C1IRSfs)( pSrcDst, srcDstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiExp_C3R( Ipp8u* pSrcDst, int srcDstStep, IppiSize roiSize, 
                             int scaleFactor) { 
     return IPPCALL(ippiExp_8u_C3IRSfs)( pSrcDst, srcDstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiExp_C1R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int 
                             dstStep, IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiExp_8u_C1RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiExp_C3R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, int 
                             dstStep, IppiSize roiSize, int scaleFactor) { 
     return IPPCALL(ippiExp_8u_C3RSfs)( pSrc, srcStep, pDst, dstStep, roiSize, scaleFactor ); 
     } 
IPPI_WRAP ippiFilterColumn32f_C1R( const Ipp8u* pSrc, int srcStep, 
                             Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const 
                             Ipp32f* pKernel, int kernelSize, int yAnchor) { 
     return IPPCALL(ippiFilterColumn32f_8u_C1R)( pSrc, srcStep, pDst, dstStep, dstRoiSize, 
                             pKernel, kernelSize, yAnchor ); 
     } 
IPPI_WRAP ippiFilterColumn32f_C1R( const Ipp16s* pSrc, int srcStep, 
                             Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const 
                             Ipp32f* pKernel, int kernelSize, int yAnchor) { 
     return IPPCALL(ippiFilterColumn32f_16s_C1R)( pSrc, srcStep, pDst, dstStep, dstRoiSize, 
                             pKernel, kernelSize, yAnchor ); 
     } 

IPPI_WRAP ippiFilterColumn32f_C1R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* 
                             pKernel, int kernelSize, int yAnchor) { 
     return IPPCALL(ippiFilterColumn_32f_C1R)( pSrc, srcStep, pDst, dstStep, dstRoiSize, 
                             pKernel, kernelSize, yAnchor ); 
     } 
IPPI_WRAP ippiFilterRow32f_C1R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* 
                             pKernel, int kernelSize, int xAnchor) { 
     return IPPCALL(ippiFilterRow32f_8u_C1R)( pSrc, srcStep, pDst, dstStep, dstRoiSize, pKernel, 
                             kernelSize, xAnchor ); 
     } 
IPPI_WRAP ippiFilterRow32f_C1R( const Ipp16s* pSrc, int srcStep, Ipp16s* 
                             pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* 
                             pKernel, int kernelSize, int xAnchor) { 
     return IPPCALL(ippiFilterRow32f_16s_C1R)( pSrc, srcStep, pDst, dstStep, dstRoiSize, 
                             pKernel, kernelSize, xAnchor ); 
     } 
IPPI_WRAP ippiFilterRow32f_C1R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* 
                             pKernel, int kernelSize, int xAnchor) { 
     return IPPCALL(ippiFilterRow_32f_C1R)( pSrc, srcStep, pDst, dstStep, dstRoiSize, pKernel, 
                             kernelSize, xAnchor ); 
     } 
IPPI_WRAP ippiFilterColumn32f_C3R( const Ipp8u* pSrc, int srcStep, 
                             Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const 
                             Ipp32f* pKernel, int kernelSize, int yAnchor) { 
     return IPPCALL(ippiFilterColumn32f_8u_C3R)( pSrc, srcStep, pDst, dstStep, dstRoiSize, 
                             pKernel, kernelSize, yAnchor ); 
     } 
IPPI_WRAP ippiFilterColumn32f_C3R( const Ipp16s* pSrc, int srcStep, 
                             Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const 
                             Ipp32f* pKernel, int kernelSize, int yAnchor) { 
     return IPPCALL(ippiFilterColumn32f_16s_C3R)( pSrc, srcStep, pDst, dstStep, dstRoiSize, 
                             pKernel, kernelSize, yAnchor ); 
     } 
IPPI_WRAP ippiFilterColumn32f_C3R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* 
                             pKernel, int kernelSize, int yAnchor) { 
     return IPPCALL(ippiFilterColumn_32f_C3R)( pSrc, srcStep, pDst, dstStep, dstRoiSize, 
                             pKernel, kernelSize, yAnchor ); 
     } 
IPPI_WRAP ippiFilterRow32f_C3R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* 
                             pKernel, int kernelSize, int xAnchor) { 
     return IPPCALL(ippiFilterRow32f_8u_C3R)( pSrc, srcStep, pDst, dstStep, dstRoiSize, pKernel, 
                             kernelSize, xAnchor ); 
     } 
IPPI_WRAP ippiFilterRow32f_C3R( const Ipp16s* pSrc, int srcStep, Ipp16s* 
                             pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* 
                             pKernel, int kernelSize, int xAnchor) { 
     return IPPCALL(ippiFilterRow32f_16s_C3R)( pSrc, srcStep, pDst, dstStep, dstRoiSize, 
                             pKernel, kernelSize, xAnchor ); 
     } 
IPPI_WRAP ippiFilterRow32f_C3R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* 
                             pKernel, int kernelSize, int xAnchor) { 
     return IPPCALL(ippiFilterRow_32f_C3R)( pSrc, srcStep, pDst, dstStep, dstRoiSize, pKernel, 
                             kernelSize, xAnchor ); 
     } 
IPPI_WRAP ippiFilterColumn32f_C4R( const Ipp8u* pSrc, int srcStep, 
                             Ipp8u* pDst, int dstStep, IppiSize dstRoiSize, const 
                             Ipp32f* pKernel, int kernelSize, int yAnchor) { 
     return IPPCALL(ippiFilterColumn32f_8u_C4R)( pSrc, srcStep, pDst, dstStep, dstRoiSize, 
                             pKernel, kernelSize, yAnchor ); 
     } 
IPPI_WRAP ippiFilterColumn32f_C4R( const Ipp16s* pSrc, int srcStep, 
                             Ipp16s* pDst, int dstStep, IppiSize dstRoiSize, const 
                             Ipp32f* pKernel, int kernelSize, int yAnchor) { 
     return IPPCALL(ippiFilterColumn32f_16s_C4R)( pSrc, srcStep, pDst, dstStep, dstRoiSize, 
                             pKernel, kernelSize, yAnchor ); 
     } 
IPPI_WRAP ippiFilterColumn32f_C4R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* 
                             pKernel, int kernelSize, int yAnchor) { 
     return IPPCALL(ippiFilterColumn_32f_C4R)( pSrc, srcStep, pDst, dstStep, dstRoiSize, 
                             pKernel, kernelSize, yAnchor ); 
     } 
IPPI_WRAP ippiFilterRow32f_C4R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* 
                             pKernel, int kernelSize, int xAnchor) { 
     return IPPCALL(ippiFilterRow32f_8u_C4R)( pSrc, srcStep, pDst, dstStep, dstRoiSize, pKernel, 
                             kernelSize, xAnchor ); 
     } 
IPPI_WRAP ippiFilterRow32f_C4R( const Ipp16s* pSrc, int srcStep, Ipp16s* 
                             pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* 
                             pKernel, int kernelSize, int xAnchor) { 
     return IPPCALL(ippiFilterRow32f_16s_C4R)( pSrc, srcStep, pDst, dstStep, dstRoiSize, 
                             pKernel, kernelSize, xAnchor ); 
     } 
IPPI_WRAP ippiFilterRow32f_C4R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize dstRoiSize, const Ipp32f* 
                             pKernel, int kernelSize, int xAnchor) { 
     return IPPCALL(ippiFilterRow_32f_C4R)( pSrc, srcStep, pDst, dstStep, dstRoiSize, pKernel, 
                             kernelSize, xAnchor ); 
     } 
IPPI_WRAP ippiAlphaComp_C1R( const Ipp8u* pSrc1, int src1Step, Ipp8u 
                             alpha1, const Ipp8u* pSrc2, int src2Step, Ipp8u alpha2, 
                             Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiAlphaType 
                             alphaType) { 
     return IPPCALL(ippiAlphaCompC_8u_C1R)( pSrc1, src1Step, alpha1, pSrc2, src2Step, alpha2, 
                             pDst, dstStep, roiSize, alphaType ); 
     } 
IPPI_WRAP ippiAlphaComp_C1R( const Ipp16u* pSrc1, int src1Step, Ipp16u 
                             alpha1, const Ipp16u* pSrc2, int src2Step, Ipp16u alpha2, 
                             Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiAlphaType 
                             alphaType) { 
     return IPPCALL(ippiAlphaCompC_16u_C1R)( pSrc1, src1Step, alpha1, pSrc2, src2Step, alpha2, 
                             pDst, dstStep, roiSize, alphaType ); 
     } 
IPPI_WRAP ippiAlphaComp_C3R( const Ipp8u* pSrc1, int src1Step, Ipp8u 
                             alpha1, const Ipp8u* pSrc2, int src2Step, Ipp8u alpha2, 
                             Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiAlphaType 
                             alphaType) { 
     return IPPCALL(ippiAlphaCompC_8u_C3R)( pSrc1, src1Step, alpha1, pSrc2, src2Step, alpha2, 
                             pDst, dstStep, roiSize, alphaType ); 
     } 
IPPI_WRAP ippiAlphaComp_C3R( const Ipp16u* pSrc1, int src1Step, Ipp16u 
                             alpha1, const Ipp16u* pSrc2, int src2Step, Ipp16u alpha2, 
                             Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiAlphaType 
                             alphaType) { 
     return IPPCALL(ippiAlphaCompC_16u_C3R)( pSrc1, src1Step, alpha1, pSrc2, src2Step, alpha2, 
                             pDst, dstStep, roiSize, alphaType ); 
     } 
IPPI_WRAP ippiAlphaComp_C4R( const Ipp8u* pSrc1, int src1Step, Ipp8u 
                             alpha1, const Ipp8u* pSrc2, int src2Step, Ipp8u alpha2, 
                             Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiAlphaType 
                             alphaType) { 
     return IPPCALL(ippiAlphaCompC_8u_C4R)( pSrc1, src1Step, alpha1, pSrc2, src2Step, alpha2, 
                             pDst, dstStep, roiSize, alphaType ); 
     } 
IPPI_WRAP ippiAlphaComp_C4R( const Ipp16u* pSrc1, int src1Step, Ipp16u 
                             alpha1, const Ipp16u* pSrc2, int src2Step, Ipp16u alpha2, 
                             Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiAlphaType 
                             alphaType) { 
     return IPPCALL(ippiAlphaCompC_16u_C4R)( pSrc1, src1Step, alpha1, pSrc2, src2Step, alpha2, 
                             pDst, dstStep, roiSize, alphaType ); 
     } 
IPPI_WRAP ippiAlphaComp_AC4R( const Ipp8u* pSrc1, int src1Step, const 
                             Ipp8u* pSrc2, int src2Step, Ipp8u* pDst, int dstStep, 
                             IppiSize roiSize, IppiAlphaType alphaType) { 
     return IPPCALL(ippiAlphaComp_8u_AC4R)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, alphaType ); 
     } 
IPPI_WRAP ippiAlphaComp_AC4R( const Ipp16u* pSrc1, int src1Step, const 
                             Ipp16u* pSrc2, int src2Step, Ipp16u* pDst, int dstStep, 
                             IppiSize roiSize, IppiAlphaType alphaType) { 
     return IPPCALL(ippiAlphaComp_16u_AC4R)( pSrc1, src1Step, pSrc2, src2Step, pDst, dstStep, 
                             roiSize, alphaType ); 
     } 
IPPI_WRAP ippiAlphaComp_AC4R( const Ipp8u* pSrc1, int src1Step, Ipp8u 
                             alpha1, const Ipp8u* pSrc2, int src2Step, Ipp8u alpha2, 
                             Ipp8u* pDst, int dstStep, IppiSize roiSize, IppiAlphaType 
                             alphaType) { 
     return IPPCALL(ippiAlphaCompC_8u_AC4R)( pSrc1, src1Step, alpha1, pSrc2, src2Step, alpha2, 
                             pDst, dstStep, roiSize, alphaType ); 
     } 
IPPI_WRAP ippiAlphaComp_AC4R( const Ipp16u* pSrc1, int src1Step, Ipp16u 
                             alpha1, const Ipp16u* pSrc2, int src2Step, Ipp16u alpha2, 
                             Ipp16u* pDst, int dstStep, IppiSize roiSize, IppiAlphaType 
                             alphaType) { 
     return IPPCALL(ippiAlphaCompC_16u_AC4R)( pSrc1, src1Step, alpha1, pSrc2, src2Step, alpha2, 
                             pDst, dstStep, roiSize, alphaType ); 
     } 
IPPI_WRAP ippiRemap_C1R( const Ipp8u* pSrc, IppiSize srcSize, int 
                             srcStep, IppiRect srcRoi, const Ipp32f* pxMap, int 
                             xMapStep, const Ipp32f* pyMap, int yMapStep, Ipp8u* pDst, 
                             int dstStep, IppiSize dstRoiSize, int interpolation) { 
     return IPPCALL(ippiRemap_8u_C1R)( pSrc, srcSize, srcStep, srcRoi, pxMap, xMapStep, pyMap, 
                             yMapStep, pDst, dstStep, dstRoiSize, interpolation ); 
     } 
IPPI_WRAP ippiRemap_C1R( const Ipp32f* pSrc, IppiSize srcSize, int 
                             srcStep, IppiRect srcRoi, const Ipp32f* pxMap, int 
                             xMapStep, const Ipp32f* pyMap, int yMapStep, Ipp32f* pDst, 
                             int dstStep, IppiSize dstRoiSize, int interpolation) { 
     return IPPCALL(ippiRemap_32f_C1R)( pSrc, srcSize, srcStep, srcRoi, pxMap, xMapStep, pyMap, 
                             yMapStep, pDst, dstStep, dstRoiSize, interpolation ); 
     } 
IPPI_WRAP ippiRemap_C3R( const Ipp8u* pSrc, IppiSize srcSize, int 
                             srcStep, IppiRect srcRoi, const Ipp32f* pxMap, int 
                             xMapStep, const Ipp32f* pyMap, int yMapStep, Ipp8u* pDst, 
                             int dstStep, IppiSize dstRoiSize, int interpolation) { 
     return IPPCALL(ippiRemap_8u_C3R)( pSrc, srcSize, srcStep, srcRoi, pxMap, xMapStep, pyMap, 
                             yMapStep, pDst, dstStep, dstRoiSize, interpolation ); 
     } 
IPPI_WRAP ippiRemap_C3R( const Ipp32f* pSrc, IppiSize srcSize, int 
                             srcStep, IppiRect srcRoi, const Ipp32f* pxMap, int 
                             xMapStep, const Ipp32f* pyMap, int yMapStep, Ipp32f* pDst, 
                             int dstStep, IppiSize dstRoiSize, int interpolation) { 
     return IPPCALL(ippiRemap_32f_C3R)( pSrc, srcSize, srcStep, srcRoi, pxMap, xMapStep, pyMap, 
                             yMapStep, pDst, dstStep, dstRoiSize, interpolation ); 
     } 
IPPI_WRAP ippiRemap_C4R( const Ipp8u* pSrc, IppiSize srcSize, int 
                             srcStep, IppiRect srcRoi, const Ipp32f* pxMap, int 
                             xMapStep, const Ipp32f* pyMap, int yMapStep, Ipp8u* pDst, 
                             int dstStep, IppiSize dstRoiSize, int interpolation) { 
     return IPPCALL(ippiRemap_8u_C4R)( pSrc, srcSize, srcStep, srcRoi, pxMap, xMapStep, pyMap, 
                             yMapStep, pDst, dstStep, dstRoiSize, interpolation ); 
     } 
IPPI_WRAP ippiRemap_C4R( const Ipp32f* pSrc, IppiSize srcSize, int 
                             srcStep, IppiRect srcRoi, const Ipp32f* pxMap, int 
                             xMapStep, const Ipp32f* pyMap, int yMapStep, Ipp32f* pDst, 
                             int dstStep, IppiSize dstRoiSize, int interpolation) { 
     return IPPCALL(ippiRemap_32f_C4R)( pSrc, srcSize, srcStep, srcRoi, pxMap, xMapStep, pyMap, 
                             yMapStep, pDst, dstStep, dstRoiSize, interpolation ); 
     } 
IPPI_WRAP ippiHistogramRange_C1R( const Ipp8u* pSrc, int srcStep, 
                             IppiSize roiSize, Ipp32s* pHist, const Ipp32s* pLevels, 
                             int nLevels) { 
     return IPPCALL(ippiHistogramRange_8u_C1R)( pSrc, srcStep, roiSize, pHist, pLevels, nLevels 
                             ); 
     } 
IPPI_WRAP ippiHistogramRange_C3R( const Ipp8u* pSrc, int srcStep, 
                             IppiSize roiSize, Ipp32s* pHist[3], const Ipp32s* 
                             pLevels[3], int nLevels[3]) { 
     return IPPCALL(ippiHistogramRange_8u_C3R)( pSrc, srcStep, roiSize, pHist, pLevels, nLevels 
                             ); 
     } 

IPPI_WRAP ippiHistogramRange_C4R( const Ipp8u* pSrc, int srcStep, 
                             IppiSize roiSize, Ipp32s* pHist[4], const Ipp32s* 
                             pLevels[4], int nLevels[4]) { 
     return IPPCALL(ippiHistogramRange_8u_C4R)( pSrc, srcStep, roiSize, pHist, pLevels, nLevels 
                             ); 
     } 
IPPI_WRAP ippiHistogramRange_C1R( const Ipp16s* pSrc, int srcStep, 
                             IppiSize roiSize, Ipp32s* pHist, const Ipp32s* pLevels, 
                             int nLevels) { 
     return IPPCALL(ippiHistogramRange_16s_C1R)( pSrc, srcStep, roiSize, pHist, pLevels, nLevels 
                             ); 
     } 
IPPI_WRAP ippiHistogramRange_C3R( const Ipp16s* pSrc, int srcStep, 
                             IppiSize roiSize, Ipp32s* pHist[3], const Ipp32s* 
                             pLevels[3], int nLevels[3]) { 
     return IPPCALL(ippiHistogramRange_16s_C3R)( pSrc, srcStep, roiSize, pHist, pLevels, nLevels 
                             ); 
     } 

IPPI_WRAP ippiHistogramRange_C4R( const Ipp16s* pSrc, int srcStep, 
                             IppiSize roiSize, Ipp32s* pHist[4], const Ipp32s* 
                             pLevels[4], int nLevels[4]) { 
     return IPPCALL(ippiHistogramRange_16s_C4R)( pSrc, srcStep, roiSize, pHist, pLevels, nLevels 
                             ); 
     } 
IPPI_WRAP ippiHistogramRange_C1R( const Ipp32f* pSrc, int srcStep, 
                             IppiSize roiSize, Ipp32s* pHist, const Ipp32f* pLevels, 
                             int nLevels) { 
     return IPPCALL(ippiHistogramRange_32f_C1R)( pSrc, srcStep, roiSize, pHist, pLevels, nLevels 
                             ); 
     } 
IPPI_WRAP ippiHistogramRange_C3R( const Ipp32f* pSrc, int srcStep, 
                             IppiSize roiSize, Ipp32s* pHist[3], const Ipp32f* 
                             pLevels[3], int nLevels[3]) { 
     return IPPCALL(ippiHistogramRange_32f_C3R)( pSrc, srcStep, roiSize, pHist, pLevels, nLevels 
                             ); 
     } 

IPPI_WRAP ippiHistogramRange_C4R( const Ipp32f* pSrc, int srcStep, 
                             IppiSize roiSize, Ipp32s* pHist[4], const Ipp32f* 
                             pLevels[4], int nLevels[4]) { 
     return IPPCALL(ippiHistogramRange_32f_C4R)( pSrc, srcStep, roiSize, pHist, pLevels, nLevels 
                             ); 
     } 

IPPI_WRAP ippiRGBToLUV_C3R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiRGBToLUV_8u_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiLUVToRGB_C3R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiLUVToRGB_8u_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiRGBToLUV_AC4R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiRGBToLUV_8u_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiLUVToRGB_AC4R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiLUVToRGB_8u_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiRGBToLUV_C3R( const Ipp16u* pSrc, int srcStep, Ipp16u* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiRGBToLUV_16u_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiLUVToRGB_C3R( const Ipp16u* pSrc, int srcStep, Ipp16u* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiLUVToRGB_16u_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiRGBToLUV_AC4R( const Ipp16u* pSrc, int srcStep, Ipp16u* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiRGBToLUV_16u_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiLUVToRGB_AC4R( const Ipp16u* pSrc, int srcStep, Ipp16u* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiLUVToRGB_16u_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiRGBToLUV_C3R( const Ipp16s* pSrc, int srcStep, Ipp16s* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiRGBToLUV_16s_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiLUVToRGB_C3R( const Ipp16s* pSrc, int srcStep, Ipp16s* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiLUVToRGB_16s_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiRGBToLUV_AC4R( const Ipp16s* pSrc, int srcStep, Ipp16s* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiRGBToLUV_16s_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiLUVToRGB_AC4R( const Ipp16s* pSrc, int srcStep, Ipp16s* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiLUVToRGB_16s_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiRGBToLUV_C3R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiRGBToLUV_32f_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiLUVToRGB_C3R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiLUVToRGB_32f_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiRGBToLUV_AC4R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiRGBToLUV_32f_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiLUVToRGB_AC4R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiLUVToRGB_32f_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiBGRToHLS_AC4R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiBGRToHLS_8u_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiRGBToHLS_C3R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiRGBToHLS_8u_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiHLSToRGB_C3R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiHLSToRGB_8u_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 

IPPI_WRAP ippiRGBToHLS_AC4R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiRGBToHLS_8u_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiHLSToRGB_AC4R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiHLSToRGB_8u_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 

IPPI_WRAP ippiRGBToHLS_C3R( const Ipp16s* pSrc, int srcStep, Ipp16s* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiRGBToHLS_16s_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiHLSToRGB_C3R( const Ipp16s* pSrc, int srcStep, Ipp16s* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiHLSToRGB_16s_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiRGBToHLS_AC4R( const Ipp16s* pSrc, int srcStep, Ipp16s* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiRGBToHLS_16s_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiHLSToRGB_AC4R( const Ipp16s* pSrc, int srcStep, Ipp16s* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiHLSToRGB_16s_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 

IPPI_WRAP ippiRGBToHLS_C3R( const Ipp16u* pSrc, int srcStep, Ipp16u* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiRGBToHLS_16u_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiHLSToRGB_C3R( const Ipp16u* pSrc, int srcStep, Ipp16u* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiHLSToRGB_16u_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiRGBToHLS_AC4R( const Ipp16u* pSrc, int srcStep, Ipp16u* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiRGBToHLS_16u_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiHLSToRGB_AC4R( const Ipp16u* pSrc, int srcStep, Ipp16u* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiHLSToRGB_16u_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 

IPPI_WRAP ippiRGBToHLS_C3R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiRGBToHLS_32f_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiHLSToRGB_C3R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiHLSToRGB_32f_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiRGBToHLS_AC4R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiRGBToHLS_32f_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiHLSToRGB_AC4R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiHLSToRGB_32f_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiBGRToLab_C3R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiBGRToLab_8u_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiLabToBGR_C3R( const Ipp8u* pSrc, int srcStep, Ipp8u* pDst, 
                             int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiLabToBGR_8u_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 

IPPI_WRAP ippiBGRToLab_C3R( const Ipp8u* pSrc, int srcStep, Ipp16u* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiBGRToLab_8u16u_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiLabToBGR_C3R( const Ipp16u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiLabToBGR_16u8u_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiFilterGauss_C1R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask) { 
     return IPPCALL(ippiFilterGauss_8u_C1R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterGauss_C3R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask) { 
     return IPPCALL(ippiFilterGauss_8u_C3R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterGauss_AC4R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask) { 
     return IPPCALL(ippiFilterGauss_8u_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterGauss_C1R( const Ipp16s* pSrc, int srcStep, Ipp16s* 
                             pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask) { 
     return IPPCALL(ippiFilterGauss_16s_C1R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterGauss_C3R( const Ipp16s* pSrc, int srcStep, Ipp16s* 
                             pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask) { 
     return IPPCALL(ippiFilterGauss_16s_C3R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterGauss_AC4R( const Ipp16s* pSrc, int srcStep, Ipp16s* 
                             pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask) { 
     return IPPCALL(ippiFilterGauss_16s_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterGauss_C1R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask) { 
     return IPPCALL(ippiFilterGauss_32f_C1R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterGauss_C3R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask) { 
     return IPPCALL(ippiFilterGauss_32f_C3R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterGauss_AC4R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask) { 
     return IPPCALL(ippiFilterGauss_32f_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterLaplace_C1R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask) { 
     return IPPCALL(ippiFilterLaplace_8u_C1R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterLaplace_C3R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask) { 
     return IPPCALL(ippiFilterLaplace_8u_C3R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterLaplace_AC4R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask) { 
     return IPPCALL(ippiFilterLaplace_8u_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterLaplace_C1R( const Ipp16s* pSrc, int srcStep, 
                             Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize 
                             mask) { 
     return IPPCALL(ippiFilterLaplace_16s_C1R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterLaplace_C3R( const Ipp16s* pSrc, int srcStep, 
                             Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize 
                             mask) { 
     return IPPCALL(ippiFilterLaplace_16s_C3R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterLaplace_AC4R( const Ipp16s* pSrc, int srcStep, 
                             Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize 
                             mask) { 
     return IPPCALL(ippiFilterLaplace_16s_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterLaplace_C1R( const Ipp32f* pSrc, int srcStep, 
                             Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize 
                             mask) { 
     return IPPCALL(ippiFilterLaplace_32f_C1R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterLaplace_C3R( const Ipp32f* pSrc, int srcStep, 
                             Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize 
                             mask) { 
     return IPPCALL(ippiFilterLaplace_32f_C3R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterLaplace_AC4R( const Ipp32f* pSrc, int srcStep, 
                             Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize 
                             mask) { 
     return IPPCALL(ippiFilterLaplace_32f_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterLaplace_C1R( const Ipp8u* pSrc, int srcStep, Ipp16s* 
                             pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask) { 
     return IPPCALL(ippiFilterLaplace_8u16s_C1R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterLaplace_C1R( const Ipp8s* pSrc, int srcStep, Ipp16s* 
                             pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask) { 
     return IPPCALL(ippiFilterLaplace_8s16s_C1R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterHipass_C1R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask) { 
     return IPPCALL(ippiFilterHipass_8u_C1R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterHipass_C3R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask) { 
     return IPPCALL(ippiFilterHipass_8u_C3R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterHipass_AC4R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask) { 
     return IPPCALL(ippiFilterHipass_8u_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterHipass_C1R( const Ipp16s* pSrc, int srcStep, Ipp16s* 
                             pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask) { 
     return IPPCALL(ippiFilterHipass_16s_C1R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterHipass_C3R( const Ipp16s* pSrc, int srcStep, Ipp16s* 
                             pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask) { 
     return IPPCALL(ippiFilterHipass_16s_C3R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterHipass_AC4R( const Ipp16s* pSrc, int srcStep, 
                             Ipp16s* pDst, int dstStep, IppiSize roiSize, IppiMaskSize 
                             mask) { 
     return IPPCALL(ippiFilterHipass_16s_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterHipass_C1R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask) { 
     return IPPCALL(ippiFilterHipass_32f_C1R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterHipass_C3R( const Ipp32f* pSrc, int srcStep, Ipp32f* 
                             pDst, int dstStep, IppiSize roiSize, IppiMaskSize mask) { 
     return IPPCALL(ippiFilterHipass_32f_C3R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterHipass_AC4R( const Ipp32f* pSrc, int srcStep, 
                             Ipp32f* pDst, int dstStep, IppiSize roiSize, IppiMaskSize 
                             mask) { 
     return IPPCALL(ippiFilterHipass_32f_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize, mask ); 
     } 
IPPI_WRAP ippiFilterSharpen_C1R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiFilterSharpen_8u_C1R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiFilterSharpen_C3R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiFilterSharpen_8u_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiFilterSharpen_AC4R( const Ipp8u* pSrc, int srcStep, Ipp8u* 
                             pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiFilterSharpen_8u_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiFilterSharpen_C1R( const Ipp16s* pSrc, int srcStep, 
                             Ipp16s* pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiFilterSharpen_16s_C1R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiFilterSharpen_C3R( const Ipp16s* pSrc, int srcStep, 
                             Ipp16s* pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiFilterSharpen_16s_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiFilterSharpen_AC4R( const Ipp16s* pSrc, int srcStep, 
                             Ipp16s* pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiFilterSharpen_16s_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiFilterSharpen_C1R( const Ipp32f* pSrc, int srcStep, 
                             Ipp32f* pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiFilterSharpen_32f_C1R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiFilterSharpen_C3R( const Ipp32f* pSrc, int srcStep, 
                             Ipp32f* pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiFilterSharpen_32f_C3R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
IPPI_WRAP ippiFilterSharpen_AC4R( const Ipp32f* pSrc, int srcStep, 
                             Ipp32f* pDst, int dstStep, IppiSize roiSize) { 
     return IPPCALL(ippiFilterSharpen_32f_AC4R)( pSrc, srcStep, pDst, dstStep, roiSize ); 
     } 
	} // namespace ipp_cpp 
} // namespace ipp 
