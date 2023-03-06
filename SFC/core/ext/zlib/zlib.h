#pragma once
/**
 * @file snappy.h
 * @author SFC dev team
 * @brief 
 * @version 1.0
 * @date 2021-05-08
 * 
 * @copyright  
 * System Foundation Classes(SFC)
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *      * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *      * Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials provided
 *        with the distribution.
 *      * Neither the name of SFC.  nor the names of its
 *        contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *  
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   
 */
/** \defgroup zlib zlib
 * @ingroup ext
 *  @{
 */

#include "../../os/predefines.h"
#include "../../rt/runtime_base.h"

#ifdef PLATFORM_INTEL_IPP_SUPPORT
#include "../ipp/ipp_config.h"
#include "../ipp/ipp_zlib/zlib.h"
#else
//#define Z_PREFIX
#include "zlib/zlib.h"
#endif

namespace rt
{
/** \defgroup zlib zlib
 * @ingroup ext
 *  @{
 */
INLFUNC bool zlib_encode(LPCVOID pSrc, UINT SrcLen, LPVOID pDst, UINT& DstLen, int Compression_Level = -1)
{
	z_stream defstrm;

	defstrm.zalloc = Z_NULL;
	defstrm.zfree = Z_NULL;
	defstrm.opaque = Z_NULL;
	defstrm.avail_in = SrcLen;
	defstrm.next_in = (Bytef*)pSrc;
	defstrm.next_out = (Bytef*)pDst;
	defstrm.avail_out = DstLen;

	if(deflateInit2(&defstrm, Compression_Level, Z_DEFLATED, -15, 8, Z_DEFAULT_STRATEGY)!= Z_OK)
		return false;

	int ret = deflate(&defstrm, Z_FINISH);
	deflateEnd(&defstrm);
	if(ret == Z_NEED_DICT || ret == Z_DATA_ERROR || ret == Z_MEM_ERROR)
		return false;

	DstLen = (UINT)defstrm.total_out;
	return true;
}

INLFUNC bool zlib_decode(LPCVOID pSrc, UINT SrcLen, LPVOID pDst, UINT& DstLen)
{
	z_stream infstrm;
					
	infstrm.zalloc = Z_NULL;
	infstrm.zfree = Z_NULL;
	infstrm.opaque = Z_NULL;
	infstrm.avail_in = SrcLen;
	infstrm.next_in = (Bytef*)pSrc;
	infstrm.next_out = (Bytef*)pDst;
	infstrm.avail_out = DstLen;
					
	// Inflate using raw inflation
	if (inflateInit2(&infstrm,-15) != Z_OK)return false;
	int ret = inflate(&infstrm, Z_FINISH);
	inflateEnd(&infstrm);
	if(ret == Z_NEED_DICT || ret == Z_DATA_ERROR || ret == Z_MEM_ERROR)
		return false;

	DstLen = (UINT)infstrm.total_out;
	return true;
}
/** @}*/
} // namespace rt
/** @}*/
