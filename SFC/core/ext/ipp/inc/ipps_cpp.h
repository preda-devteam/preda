#pragma once
//////////////////////////////////////////////////////////////////////
// Visual Computing Foundation Classes (VCFC)
//					Jiaping Wang  2006.2
//					e_boris2002@hotmail.com
//
// (C) Copyright Jiaping Wang 2004.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all copies.
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//
// Absolutly no garanty!!
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//  Brief Description
//
//  ippi_cpp.h
//
//  wrap ippi function with C++ override for type adaptation
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Revise History
//
// Inital version			2005.?.?		Jiaping
// default flag value		2006.2.?		Jiaping
//							integrate with ipp::GetEnv() 
//
//////////////////////////////////////////////////////////////////////

namespace ipp
{
namespace ipp_cpp 
{

#define IPPS_WRAP static inline IppStatus

//////////////////////////////////////////////////////////////////
//IppStatus ippsSortAscend_8u_I(Ipp8u* pSrcDst, int len);
//IppStatus ippsSortAscend_16s_I(Ipp16s* pSrcDst, int len);
//IppStatus ippsSortAscend_32s_I(Ipp32s* pSrcDst, int len);
//IppStatus ippsSortAscend_32f_I(Ipp32f* pSrcDst, int len);
//IppStatus ippsSortAscend_64f_I(Ipp64f* pSrcDst, int len);
//IppStatus ippsSortDescend_8u_I(Ipp8u* pSrcDst, int len);
//IppStatus ippsSortDescend_16s_I(Ipp16s* pSrcDst, int len);
//IppStatus ippsSortDescend_32s_I(Ipp32s* pSrcDst, int len);
//IppStatus ippsSortDescend_32f_I(Ipp32f* pSrcDst, int len);
//IppStatus ippsSortDescend_64f_I(Ipp64f* pSrcDst, int len);
IPPS_WRAP ippsSortAscend_I(Ipp8u* pSrcDst, int len)
{
	return IPPCALL(ippsSortAscend_8u_I)(pSrcDst,len);
}
IPPS_WRAP ippsSortAscend_I(Ipp16s* pSrcDst, int len)
{
	return IPPCALL(ippsSortAscend_16s_I)(pSrcDst,len);
}
IPPS_WRAP ippsSortAscend_I(Ipp32s* pSrcDst, int len)
{
	return IPPCALL(ippsSortAscend_32s_I)(pSrcDst,len);
}
IPPS_WRAP ippsSortAscend_I(Ipp32f* pSrcDst, int len)
{
	return IPPCALL(ippsSortAscend_32f_I)(pSrcDst,len);
}
IPPS_WRAP ippsSortAscend_I(Ipp64f* pSrcDst, int len)
{
	return IPPCALL(ippsSortAscend_64f_I)(pSrcDst,len);
}
IPPS_WRAP ippsSortDescend_I(Ipp8u* pSrcDst, int len)
{
	return IPPCALL(ippsSortDescend_8u_I)(pSrcDst,len);
}
IPPS_WRAP ippsSortDescend_I(Ipp16s* pSrcDst, int len)
{
	return IPPCALL(ippsSortDescend_16s_I)(pSrcDst,len);
}
IPPS_WRAP ippsSortDescend_I(Ipp32s* pSrcDst, int len)
{
	return IPPCALL(ippsSortDescend_32s_I)(pSrcDst,len);
}
IPPS_WRAP ippsSortDescend_I(Ipp32f* pSrcDst, int len)
{
	return IPPCALL(ippsSortDescend_32f_I)(pSrcDst,len);
}
IPPS_WRAP ippsSortDescend_I(Ipp64f* pSrcDst, int len)
{
	return IPPCALL(ippsSortDescend_64f_I)(pSrcDst,len);
}

//IppStatus ippsPowx_32f_A11 (const Ipp32f* pSrc1, const Ipp32f ConstValue,
//Ipp32f* pDst, int len);
//IppStatus ippsPowx_32f_A21 (const Ipp32f* pSrc1, const Ipp32f ConstValue,
//Ipp32f* pDst, int len);
//IppStatus ippsPowx_32f_A24 (const Ipp32f* pSrc1, const Ipp32f ConstValue,
//Ipp32f* pDst, int len);
//IppStatus ippsPowx_64f_A50 (const Ipp64f* pSrc1, const Ipp64f ConstValue,
//Ipp64f* pDst, int len);
//IppStatus ippsPowx_64f_A53 (const Ipp64f* pSrc1, const Ipp64f ConstValue,
//Ipp64f* pDst, int len);
IPPS_WRAP ippsPow(const Ipp32f* pSrc1, const Ipp32f ConstValue,Ipp32f* pDst, int len)
{
#if defined(IPPS_FAAF_ACCURACY_HIGH)
	return IPPCALL(ippsPowx_32f_A24)(pSrc1,ConstValue,pDst,len);
#elif defined(IPPS_FAAF_ACCURACY_LOW)
	return IPPCALL(ippsPowx_32f_A11)(pSrc1,ConstValue,pDst,len);
#else
	return IPPCALL(ippsPowx_32f_A21)(pSrc1,ConstValue,pDst,len);
#endif
}
IPPS_WRAP ippsPow(const Ipp64f* pSrc1, const Ipp64f ConstValue,Ipp64f* pDst, int len)
{
#if defined(IPPS_FAAF_ACCURACY_HIGH)
	return IPPCALL(ippsPowx_64f_A50)(pSrc1,ConstValue,pDst,len);
#else
	return IPPCALL(ippsPowx_64f_A53)(pSrc1,ConstValue,pDst,len);
#endif
}

IPPS_WRAP ippsZero(Ipp8u* pDst, int len){ return IPPCALL(ippsZero_8u)(pDst, len); }
IPPS_WRAP ippsZero(Ipp16s* pDst, int len){ return IPPCALL(ippsZero_16s)(pDst, len); }
IPPS_WRAP ippsZero(rt::Vec2s* pDst, int len){ return IPPCALL(ippsZero_16sc)((Ipp16sc*)pDst, len); }
IPPS_WRAP ippsZero(Ipp32f* pDst, int len){ return IPPCALL(ippsZero_32f)(pDst, len); }
IPPS_WRAP ippsZero(rt::Vec2f* pDst, int len){ return IPPCALL(ippsZero_32fc)((Ipp32fc*)pDst, len); }
IPPS_WRAP ippsZero(Ipp64f* pDst, int len){ return IPPCALL(ippsZero_64f)(pDst, len); }
IPPS_WRAP ippsZero(rt::Vec2d* pDst, int len){ return IPPCALL(ippsZero_64fc)((Ipp64fc*)pDst, len); }
IPPS_WRAP ippsZero(Ipp32s* pDst, int len){ return IPPCALL(ippsZero_32s)(pDst, len); }
IPPS_WRAP ippsZero(rt::Vec2i* pDst, int len){ return IPPCALL(ippsZero_32sc)((Ipp32sc*)pDst, len); }
IPPS_WRAP ippsZero(Ipp64s* pDst, int len){ return IPPCALL(ippsZero_64s)(pDst, len); }
IPPS_WRAP ippsZero(rt::Vec<LONGLONG,2>* pDst, int len){ return IPPCALL(ippsZero_64sc)((Ipp64sc*)pDst, len); }


} // namespace ipp_cpp 
} // namespace ipp