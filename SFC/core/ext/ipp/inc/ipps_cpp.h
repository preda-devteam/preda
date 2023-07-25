#pragma once
/*********************************************************************
// System Foundation Classes(SFC)
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//     * Neither the name of SFC.  nor the names of its
//       contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

//////////////////////////////////////////////////////////////////////
//  Brief Description
//
//  ippi_cpp.h
//
//  wrap ippi function with C++ override for type adaptation
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