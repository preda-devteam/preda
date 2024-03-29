﻿#pragma once
#include "type_def.h"


namespace rvm
{
#pragma pack(push, 1)

struct StringMutable;

struct String
{
	TYPETRAITS_DECLARE_NON_POD;
	RVM_IMMUTABLE_TYPE(String);

	WORD	_len;
	char	_p[1];

	String(decltype(0) x){ ASSERT(x == 0); _len = 0; }
	auto			Str() const { return rt::String_Ref(_p, _len); }
	UINT			GetEmbeddedSize() const { return sizeof(WORD) + _len; }
	UINT			Embed(const rvm::String& str){ return Embed(str.Str()); }
	UINT			Embed(const rt::String_Ref& str)
					{	if(!str.IsEmpty() && str.GetLength() <= RVM_STRING_SIZEMAX)
						{	_len = (WORD)str.GetLength();
							memcpy(_p, str.Begin(), _len);
							return (UINT)(sizeof(WORD) + str.GetLength());
						}
						else
						{	_len = 0;
							return sizeof(WORD);
						}
					}
	static UINT		GetEmbeddedSize(const rt::String_Ref& str){ return (UINT)(sizeof(WORD) + str.GetLength()); }
	static bool		IsEmbeddable(const rvm::String& str){ return IsEmbeddable(str.Str()); }
	static bool		IsEmbeddable(const rt::String_Ref& str){ return str.GetLength() <= RVM_STRING_SIZEMAX; }
	bool operator	<(const String& x) const { return Str() < x.Str(); }
	bool operator	<=(const String& x) const { return Str() <= x.Str(); }
	bool operator	==(const String& x) const { return Str() == x.Str(); }
	void			Jsonify(rt::Json& append) const { append.String(Str()); }
	void			ToString(rt::String& append) const { append += Str(); }

	static auto&	Zero(){ static const String _zero(0); return _zero; }
	static void		GetTypeSignature(rt::String& n){ n += rt::SS("string"); }
};

struct StringMutable: public rt::String
{
	typedef rt::String _SC;
	auto&	operator = (const rt::String_Ref& s){ *(_SC*)this = s; return *this; }
	bool	JsonParse(const rt::String_Ref& s){ rt::JsonObject::UnescapeStringValue(s.TrimQuotes(), *this); return true; }
	StringMutable() = default;
	StringMutable(const rt::String_Ref& s):_SC(s){}
	template<typename str_expr>
	StringMutable(const str_expr& x):_SC(x){}
};

#pragma pack(pop)
} // namespace oxd
