#pragma once
/**
 * @file precision_num.h
 * @author SFC dev team
 * @brief 
 * @version 1.0
 * @date 2021-04-30
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
/** \defgroup bigNum bigNum
 * @ingroup ext
 *  @{
 */
 
#include "../../rt/type_traits.h"


namespace ext
{
/** \defgroup bigNum bigNum
 * @ingroup ext
 *  @{
 */
#pragma pack(push, 4)
namespace _details
{
template<int bit_width>
class PrecisionFloat
{
	TYPETRAITS_DECLARE_POD;
	BYTE		_Data[bit_width/8 + 4];
public:
	PrecisionFloat(){ rt::Zero(_Data); }
	PrecisionFloat(ULONGLONG x);
	PrecisionFloat(UINT x):PrecisionFloat((ULONGLONG)x){}
	PrecisionFloat(LONGLONG x);
	PrecisionFloat(INT x):PrecisionFloat((LONGLONG)x){}
	PrecisionFloat(double x);
	PrecisionFloat(LPCSTR val_str);

	bool	Pow(ULONGLONG idx);
	bool	Pow(UINT idx){ return Pow((ULONGLONG)idx); }
	bool	Pow(const PrecisionFloat& idx);
	bool	Log(const PrecisionFloat& f, const PrecisionFloat& base);

	bool	Add(const PrecisionFloat& f);
	bool	Sub(const PrecisionFloat& f);
	bool	Mul(const PrecisionFloat& f);
	bool	Div(const PrecisionFloat& f);

//	void	BN_Mul(const ext::BigNumRef& a, ext::BigNumMutable& b) const;	///< b = a*this

	std::string	ToString() const;
	bool	ToNumber(SIZE_T& x) const;
	bool	ToNumber(double& x) const;

	template<class t_Ostream>
	friend t_Ostream& operator<<(t_Ostream& Ostream, const PrecisionFloat& x){	Ostream << x.ToString(); return Ostream; }
};
} // namespace _details

/** \defgroup Typedefs_BigNum Typedefs_BigNum
 * @ingroup bigNum
 *  @{
 */
typedef _details::PrecisionFloat<8192>	Float8192;
typedef _details::PrecisionFloat<2048>	Float2048;
typedef _details::PrecisionFloat<1024>	Float1024;
typedef _details::PrecisionFloat<512>	Float512;
typedef _details::PrecisionFloat<256>	Float256;
/** @}*/
#pragma pack(pop)
/** @}*/
} // namespace ext
/** @}*/
