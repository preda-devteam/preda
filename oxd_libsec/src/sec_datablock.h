#pragma once
#include "../../SFC/core/ext/botan/inc/datablock.h"

namespace oxd
{

#pragma pack(push,1)
template<UINT _LEN, bool is_sensitive = false>
struct SecDataBlock: public sec::DataBlock<_LEN, is_sensitive>
{
	typedef sec::DataBlock<_LEN, is_sensitive> _SC;

	const auto&	ToString(rt::String& str, bool for_display = false) const
				{	if(for_display)
					{
						str.SetLength(os::Base32EncodeLength(_LEN));
						os::Base32CrockfordEncodeLowercase(str.Begin(), this, _LEN);
					}
					else
					{
						str.SetLength(os::Base64EncodeLength(_LEN));
						os::Base64Encode(str.Begin(), this, _LEN);
					}
					return str;
				}
	bool		FromString(const rt::String_Ref& str)
				{	if(os::Base16DecodeLength(str.GetLength()) == _LEN)
						return _SC::FromBase16(str);
					else if(os::Base32DecodeLength(str.GetLength()) == _LEN)
						return os::Base32CrockfordDecode(this, _LEN, str.Begin(), str.GetLength())
							|| os::Base32Decode(this, _LEN, str.Begin(), str.GetLength());
					else if(os::Base64DecodeLength(str.Begin(), str.GetLength()) == _LEN)
						return _SC::FromBase64(str);
					else
						return false;
				}
	static auto& ZeroValue()
				{	struct _z: public SecDataBlock{	_z(){ rt::Zero(*this); }};
					static const _z z;
					return z;
				}
};
#pragma pack(pop)


struct b32str: public rt::tos::Base32CrockfordLowercaseOnStack<>
{	
	void	_ShowTrailingZero(){ for(LPSTR p = &Last(); *p == 'o' && p>=_p; p--)*p = '0'; }
public:
	template<UINT _LEN, bool is_sensitive = false>
	b32str(const sec::DataBlock<_LEN, is_sensitive>& x):rt::tos::Base32CrockfordLowercaseOnStack<>(&x, _LEN){ _ShowTrailingZero(); }
	template<UINT _LEN>
	b32str(const typename sec::DataBlockRef<_LEN>& x):rt::tos::Base32CrockfordLowercaseOnStack<>(x.GetBytes(), _LEN){ _ShowTrailingZero(); }
	template<typename T>
	b32str(const T& x):rt::tos::Base32CrockfordLowercaseOnStack<>(&x, sizeof(T)){ static_assert(rt::TypeTraits<T>::IsPOD); _ShowTrailingZero(); }
	b32str(LPCVOID p, UINT size):rt::tos::Base32CrockfordLowercaseOnStack<>(p, size){ _ShowTrailingZero(); }
	const b32str& Shorten(bool as_addr = false)
	{	if(GetLength()>=6)
		{
			*(DWORD*)&_p[4] = *(DWORD*)&_p[_len-4];		_p[4] = ':'; 		_p[8] = as_addr?']':'>';
			_p[3] = _p[2];		_p[2] = _p[1];			_p[1] = _p[0];		_p[0] = as_addr?'[':'<';
			_len = 9;
		}
		return *this;
	}
public:
	static bool Decode(LPVOID out, SIZE_T out_size, LPCSTR str, SIZE_T str_len)
	{
		return os::Base32CrockfordDecode(out, out_size, str, str_len);
	}
};

#define b32shorten(x)			((rt::String_Ref&)oxd::b32str(x).Shorten())
#define b32shorten_address(x)	((rt::String_Ref&)oxd::b32str(x).Shorten(true))

} // namespace oxd
