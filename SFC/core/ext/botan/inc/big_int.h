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


#include "botan_inc.h"

namespace Botan
{
/** \defgroup botan botan
 * @ingroup ext
 *  @{
*/
/** \defgroup Functions_botan Functions_botan
* @ingroup botan
*  @{
*/
INLFUNC void BigIntAssign(BigInt& bi, LPCVOID p, SIZE_T len)
{	
	auto& raw = bi.get_word_vector();
	raw.resize((len/sizeof(Botan::word) + 1 + 7)&~7);
	memcpy(raw.data(), p, len);
	memset(len + (LPBYTE)raw.data(), 0, raw.size()*sizeof(Botan::word) - len);
}

template<typename T_POD>
INLFUNC void BigIntAssign(BigInt& bi, const T_POD& x){ BigIntAssign(bi, &x, sizeof(x)); }
INLFUNC void BigIntAssign(BigInt& bi, const rt::String_Ref& x){ BigIntAssign(bi, x.Begin(), x.GetLength()); }

INLFUNC void BigIntToString(const BigInt& x, rt::String& out)
{
	out = "0x";
	if(x.is_nonzero())
	{
		auto& raw = x.get_word_vector();
		LPCBYTE end = (LPCBYTE)raw.data();
		LPCBYTE p = end + raw.size()*sizeof(Botan::word) - 1;
		for(; p>=end; p--)
		{
			BYTE v = *p;
			int c1 = v>>4;
			int c2 = v&0xf;
			out += (char)((c1>9)?('a'+c1-10):('0'+c1));
			out += (char)((c1>9)?('a'+c2-10):('0'+c2));
		}
	}
}
/** @}*/
/** @}*/
} // namespace Botan


