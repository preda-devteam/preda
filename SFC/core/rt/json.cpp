#include "json.h"
#include "../os/kernel.h"

namespace rt
{

JsonArray::JsonArray(const rt::String_Ref& doc)
{
	SSIZE_T s = doc.FindCharacter('[');
	if(s>=0)_Doc = doc.SubStr(s);
}

bool JsonArray::GetNextObjectRaw(rt::String_Ref& obj) const
{
	if(_Doc.IsEmpty())return false;
	LPCSTR _CurObject = obj.End();
	if(_CurObject>=_Doc.Begin() && _CurObject<=_Doc.End())
	{	
		if(*_CurObject == '"' && obj.Begin()[-1] == '"')
			_CurObject++;
		_CurObject = JsonObject::_skip_whitespace(_CurObject, _Doc.End());
		if(*_CurObject == ',')
		{	_CurObject++;
		}else return false;
	}
	else
	{	_CurObject = _Doc.Begin() + 1;
	}

	LPCSTR p = JsonObject::_skip_whitespace(_CurObject, _Doc.End());
	if(*p == ']')return false;

	LPCSTR tail = JsonObject::_seek_json_object_closure(p,_Doc.End());
	if(tail)
	{	
		obj = rt::String_Ref(p, tail);
		return true;
	}
	return false;
}

bool JsonArray::GetNextObject(rt::String_Ref& obj) const
{	
	if(GetNextObjectRaw(obj))
	{	
		LPCSTR p = obj.Begin();
		LPCSTR tail = obj.End();
		JsonObject::_cook_raw_value(p, tail);
		obj = rt::String_Ref(p, tail);

		return true;
	}
	else return false;
}

SIZE_T JsonArray::GetSize() const
{	
	rt::String_Ref	obj;
	SIZE_T c = 0;
	while(GetNextObjectRaw(obj))
		c++;
	return c;
}

void JsonObject::_cook_raw_value(LPCSTR& p, LPCSTR& tail)
{
	if(*p == '"' || *p == '\''){ p++; tail--; } // string
	else
		if(*p == '<')
		{	
			p+=2;
			while(*p != '/'){ p++; ASSERT(p<tail); }
			p++;
			tail--;
		}  // binary
}

LPCSTR JsonObject::_seek_char_escape(LPCSTR p, LPCSTR end, char c)
{
	for(;p < end;p++)
	{	if(*p==c)
		{	LPCSTR s = p-1;
			for(;*s == '\\';s--);
			if(((int)(s-p))&1)return p;
		}
	}
	return end;
}

rt::String_Ref JsonObject::GetFirstObject(const rt::String_Ref& str_in)
{
	rt::String_Ref str = str_in.TrimLeftSpace();
	if(str.GetLength()<2)return nullptr;

	auto end = _seek_json_object_closure(str.Begin(), str.End());
	if(end)
		return rt::String_Ref(str.Begin(), end);

	return nullptr;
}

bool JsonObject::ValidateObject(const rt::String_Ref& str_in)
{
	rt::String_Ref str = str_in.TrimSpace();
	return	str.GetLength()>=2 &&
			_match_closure(str[0]) == str.Last() &&
			_seek_json_object_closure(str.Begin(), str.End()) == str.End();
}

LPCSTR JsonObject::_scan_text(LPCSTR p, LPCSTR end)
{
	static const rt::CharacterSet sep("\x7\x9\xa\xb\xc\xd '\",:{}[]");
	while(p < end && !sep.Has(*p))
		p++;
	
	return p;
}

LPCSTR JsonObject::_seek_json_object_closure(LPCSTR p, LPCSTR end)
{
	if(*p == '"' || *p == '\'') // string
	{
		p = _seek_char_escape(p+1, end, *p);
		if(p != end)return p+1;
		return nullptr;
	}
	else if(*p == '<') // binary
	{
		UINT len;
		p++;
		p += rt::String_Ref(p, end).ToNumber(len);
		p += 1 + len;
		if(*p == '>')return p+1;
		return nullptr;
	}
	else
	{
		char c = _match_closure(*p);
		if(c)
		{	char depth_inc = *p;
			char depth_dec = c;
			int closure_depth = 1;
			p++;
				
			while(p<end)
			{
				if(*p == depth_inc)closure_depth++;
				else if(*p == depth_dec)
				{	closure_depth--;
					if(closure_depth == 0)return p+1;
				}
				else if(*p == '"' || *p == '\'')
				{	p = _seek_char_escape(p+1,end,*p);
					if(p == end)return nullptr;
				}
				else if(*p == '<')
				{
					p = _seek_json_object_closure(p, end);
					if(!p)return nullptr;
				}
				p++;
			}
			return nullptr;
		}
		else return _scan_text(p, end);
	}
}

rt::String_Ref JsonObject::GetValueRaw(const rt::String_Ref& xpath, const rt::String_Ref& default_val, bool bDoNotSplitDot) const	// xxx.yyy.zzz
{
	if(xpath.IsEmpty())return _Doc;
	LPCSTR p, tail;
	if((p = _LocateValue(xpath, bDoNotSplitDot)))
	{	
		if((tail = _seek_json_object_closure(p,_Doc.End())))
			return rt::String_Ref(p, tail);
	}

	return default_val;
}

rt::String_Ref JsonObject::GetValueRaw(const rt::String_Ref& xpath, bool& p_exist, bool bDoNotSplitDot) const	// xxx.yyy.zzz
{	
	if(xpath.IsEmpty()){ p_exist = true; return _Doc; }
	LPCSTR p, tail;
	if((p = _LocateValue(xpath, bDoNotSplitDot)))
	{	
		p_exist = true;
		if((tail = _seek_json_object_closure(p,_Doc.End())))
			return rt::String_Ref(p, tail);
	}
	p_exist = false;
	return nullptr;
}

rt::String_Ref JsonObject::GetValue(const rt::String_Ref& xpath, const rt::String_Ref& default_val, bool bDoNotSplitDot) const	// xxx.yyy.zzz
{
	if(xpath.IsEmpty())return _Doc;
	LPCSTR p, tail;
	if((p = _LocateValue(xpath, bDoNotSplitDot)))
	{	
		if((tail = _seek_json_object_closure(p,_Doc.End())))
		{	
			_cook_raw_value(p, tail);
			return rt::String_Ref(p, tail);
		}
	}

	return default_val;
}

rt::String_Ref JsonObject::GetValue(const rt::String_Ref& xpath, bool& p_exist, bool bDoNotSplitDot) const	// xxx.yyy.zzz
{
	if(xpath.IsEmpty()){ p_exist = true; return _Doc; }
	LPCSTR p, tail;
	if((p = _LocateValue(xpath, bDoNotSplitDot)))
	{	
		p_exist = true;
		if((tail = _seek_json_object_closure(p,_Doc.End())))
		{	
			_cook_raw_value(p, tail);
			return rt::String_Ref(p, tail);
		}
	}
	p_exist = false;
	return nullptr;
}


bool JsonObject::IsEmptyObject() const 
{ 
	if(IsEmpty())
		return true;

	if(_Doc.TrimLeftSpace()[0] != '{')return false;

	JsonKeyValuePair kvp;
	if(GetNextKeyValuePair(kvp))
		return false;
	else
		return true;
}

namespace _details
{
int JsonObject_CountSeps(const rt::String_Ref& doc)
{
	bool in_quote = false;
	int ret = 0;
	for(UINT i=0; i<doc.GetLength(); i++)
	{
		char c = doc[i];
		if(in_quote)
		{	if(c == '"' && doc[i-1] != '\\')
				in_quote = false;
		}
		else
		{	if(c == ',' && c == '{' && c == '[')ret++;
			if(c == '"')in_quote = true;
		}
	}
	return ret;
}
} // namespace _details

void JsonObject::UnescapeStringValue(const rt::String_Ref& in, rt::String& val_out)
{
	if(in.IsEmpty()){ val_out.Empty(); return; }

	VERIFY(val_out.SetLength(in.GetLength()));

	static const rt::CharacterSet esc("bfrntv","\b\f\r\n\t\v");
	static const rt::CharacterSet hex("0123456789abcdefABCDEF","\x1\x2\x3\x4\x5\x6\x7\x8\x9\xa\xb\xc\xd\xe\xf\x10\xb\xc\xd\xe\xf\x10");
		
	LPSTR p = val_out.Begin();	LPCSTR s = in.Begin();	LPCSTR end = in.End();
	while(s<end-1)
	{	
		if(*s == '\\'){
			if(s[1] == 'u' && s+5<end)
			{	
				s+=2;
				int c =  ((hex.Mapped(s[0])-1)<<12) + ((hex.Mapped(s[1])-1)<<8) + ((hex.Mapped(s[2])-1)<<4) + (hex.Mapped(s[3])-1);
				if(c <= 0x7f){ *p = (char)c; p++; }
				else if(c > 0x7ff)	// 1110xxxx 	10xxxxxx 	10xxxxxx
				{	*((DWORD*)p) = 0x8080e0 | ((c>>12)&0xf) | ((c<<2)&0x3f00) | ((0x3f&c)<<16);
					p+=3;
				}
				else	// 110xxxxx 	10xxxxxx
				{	*((WORD*)p) = 0x80c0 | ((c>>6)&0x1f) | ((0x3f&c)<<8);
					p+=2;
				}
				s+=4;
			}
			else if(s[1] == 'x' && s+3<end)
			{	
				s+=2;
				*p++ = ((hex.Mapped(s[0])-1)<<4) + (hex.Mapped(s[1])-1);
				s+=2;
			}
			else
			{	
				*p++ = esc.Mapped(s[1]);
				s+=2;
			}
		}else{ *p++ = *s++; }
	}
	if(s<end){ *p++ = *s++; }
	val_out._len = p - val_out._p;
}

bool JsonObject::GetNextKeyValuePair(JsonKeyValuePair& kvp) const
{	
	if(_Doc.IsEmpty())return false;
	ASSERT(*_Doc.Begin() == '{');
	LPCSTR p = _Doc.Begin() + 1;
	LPCSTR end = _Doc.End();
	if(kvp._Key.Begin()>=p && kvp._Value.End()<=_Doc.End())
	{
		p = kvp._Value.End();
		if(*p=='"' || *p=='\'' || *p=='>')p++;
	}

	p = _skip_whitespace(p, end);
	if(*p == '}')return false;
	if(*p == ',')p = _skip_whitespace(p+1, end);

	LPCSTR name_end;
	if(*p=='"' || *p=='\'')
	{ 
		name_end = _seek_char_escape(p+1, end, *p);
		p++;
	}
	else
	{	name_end = _scan_text(p, end);
	}

	if(end == name_end || p == name_end)return false;

	rt::String_Ref key(p, name_end);

	LPCSTR value = _seek_char(name_end, end, ':');
	if(value == end)return false; // ':' not found
	value = _skip_whitespace(value+1, end);
	LPCSTR tail = _seek_json_object_closure(value, end);
	if(tail == nullptr)return false;

	_cook_raw_value(value, tail);

	kvp._Key =  key;
	kvp._Value = rt::String_Ref(value, tail);

	return !kvp._Value.IsEmpty() || *tail == '"';
}

void JsonObject::Override(const rt::String_Ref& base, const rt::String_Ref& sub, rt::String& derived, bool append)
{	
	ASSERT(base.Begin() != sub.Begin());

	typedef rt::hash_map<rt::String_Ref, rt::String_Ref, rt::String_Ref::hash_compare> t_ValList;
	t_ValList	vals;
	{
		JsonKeyValuePair kv;
		JsonObject base_doc(base);
		while(base_doc.GetNextKeyValuePair(kv))
			vals[kv.GetKey()] = kv.GetValueRaw();
	}

	{
		JsonKeyValuePair kv;
		JsonObject base_doc(sub);
		while(base_doc.GetNextKeyValuePair(kv))
			vals[kv.GetKey()] = kv.GetValueRaw();
	}

	if(!append)derived.Empty();

	t_ValList::const_iterator it = vals.begin();
	for(; it != vals.end(); it++)
	{	
		if(derived.IsEmpty())
			derived = rt::SS("{ \"") + it->first + rt::SS("\" : ") + it->second;
		else
			derived += rt::SS(",\n  \"") + it->first + rt::SS("\" : ") + it->second;
	}

	if(derived.IsEmpty())
		derived = rt::SS("{}");

	else derived += '}';
}

void JsonObject::Override(const rt::String_Ref& base, const rt::String_Ref& key, const rt::String_Ref& val_raw, rt::String& derived, bool append)
{
	typedef rt::hash_map<rt::String_Ref, rt::String_Ref, rt::String_Ref::hash_compare> t_ValList;

	t_ValList	vals;
	{
		JsonKeyValuePair kv;
		JsonObject base_doc(base);
		while(base_doc.GetNextKeyValuePair(kv))
			vals[kv.GetKey()] = kv.GetValueRaw();
	}

	vals[key] = val_raw;
	t_ValList::const_iterator it = vals.begin();
	if(!append)derived.Empty();

	for(; it != vals.end(); it++)
	{	
		if(derived.IsEmpty())
			derived = rt::SS("{ \"") + it->first + rt::SS("\" : ") + it->second;
		else
			derived += rt::SS(",\n  \"") + it->first + rt::SS("\" : ") + it->second;
	}

	if(derived.IsEmpty())
		derived = rt::SS("{}");
	else
		derived += '}';
}

void JsonObject::RemoveKeys(const rt::String_Ref& source, const rt::String_Ref& keys_to_exclude, rt::String& removed)
{	
	rt::String_Ref keys[256];
	UINT co = keys_to_exclude.Split(keys, sizeofArray(keys), ",;|");
	if(co == 0){ removed = source; return; }

	JsonKeyValuePair kv;
	JsonObject doc(source);
	while(doc.GetNextKeyValuePair(kv))
	{
		for(UINT i=0;i<co;i++)
			if(kv.GetKey() == keys[i])goto SKIP_THE_KEY;
		if(removed.IsEmpty()){ removed = rt::SS("{ "); }
		else{ removed += rt::SS(",  "); }
		removed += rt::SS("\n  \"") + kv.GetKey() + rt::SS("\": ") + kv.GetValueRaw();
SKIP_THE_KEY:
		continue;
	}

	if(removed.IsEmpty())
		removed = rt::SS("{ }");
	else
		removed += rt::SS("\n}");
}

void JsonObject::RetainKeys(const rt::String_Ref& source, const rt::String_Ref& keys_to_retain, rt::String& out)
{
	rt::String_Ref keys[256];
	UINT co = keys_to_retain.Split(keys, sizeofArray(keys), ",;|");
	if (co == 0) { out = "{ }"; return; }

	rt::JsonKeyValuePair kv;
	rt::JsonObject doc(source);
	while (doc.GetNextKeyValuePair(kv))
	{
		UINT i;
		for (i = 0; i < co; i++)
			if (kv.GetKey() == keys[i]) break;
		if (i >= co) goto SKIP_THE_KEY;
		if (out.IsEmpty()) { out = rt::SS("{ "); }
		else { out += rt::SS(",  "); }
		out += rt::SS("\n  \"") + kv.GetKey() + rt::SS("\": ") + kv.GetValueRaw();
	SKIP_THE_KEY:
		continue;
	}

	if (out.IsEmpty())
		out = rt::SS("{ }");
	else
		out += rt::SS("\n}");
}

LPCSTR JsonObject::_LocateValue(const rt::String_Ref& xpath, bool bDoNotSplitDot /* = false */) const
{
	if(_Doc.IsEmpty())return nullptr;

	rt::String_Ref	path_seg[256];

	int segco;
	if (bDoNotSplitDot)
		segco = xpath.Split<true>(path_seg, sizeofArray(path_seg), "[]");
	else
		segco = xpath.Split<true>(path_seg, sizeofArray(path_seg), ".[]");
	if(path_seg[segco-1].IsEmpty())segco--;

	LPCSTR p = _Doc.Begin();
	LPCSTR end = _Doc.End();

	if(*p != '{')return nullptr;
	for(int i=0; i<segco; i++)
	{
		rt::String_Ref name = path_seg[i];

		if(name[-1] != '[')
		{
			for(;;)
			{	p = _skip_whitespace(p+1, end);
				if(*p == '}')return nullptr; // name not found
				LPCSTR name_end;
				if(*p=='"' || *p=='\''){ 
					name_end = _seek_char_escape(p+1, end, *p);
					p++;
				}
				else{ name_end = _scan_text(p, end); }
				if(end == name_end || p == name_end)return nullptr;

				LPCSTR value = _seek_char(name_end, end, ':');
				if(value == end)return nullptr; // ':' not found
				value = _skip_whitespace(value+1, end);

				if(rt::String_Ref(p, name_end) == name)
				{	// found
					if(i == segco-1)return value;
					p = value;
					if(*p != '{' && *p != '[')return nullptr; // an object expected
					break;
				}
				else
				{	p = _seek_json_object_closure(value, end); // p[-1] = '}' or ']' or '"' or last char of the value
					if(p==nullptr)return nullptr;
					p = _skip_whitespace(p, end);
					if(*p != ',')return nullptr; // end of object reached, name not found
				}
			}
		}
		else
		{	if(*p != '[')return nullptr; // not an array
			UINT co = 0;
			name.ToNumber(co);
			rt::JsonObject item;
			JsonArray  arr(rt::String_Ref(p, _Doc.End()));
			int s = -1;
			do
			{	if(!arr.GetNextObjectRaw(item))return nullptr;
				s++;
			}while(s<(int)co);
			p = item._Doc.Begin();
			if(i == segco-1)
				return p;
		}
	}

	ASSERT(0);
	return nullptr;
}

JsonType JsonKeyValuePair::GetValueType(const rt::String_Ref& Value) 
{	
	if(Value.IsEmpty() && Value.Begin() == nullptr)return JSON_NULL;
	if(Value[-1] == '"' || Value[-1] == '\'')return JSON_STRING;
	if(Value[-1] == '/')return JSON_BINARY;
	if(Value[0] == '{')return JSON_OBJECT;
	if(Value[0] == '[')return JSON_ARRAY;
	if(Value[0] == 't' || Value[0] == 'T' || Value[0] == 'f' || Value[0] == 'F')return JSON_BOOL;
	if((Value[0] >= '0' && Value[0] <= '9') || Value[0] == '-')return JSON_NUMBER;
	if(Value.GetLength() == 4 && *(DWORD*)Value.Begin() == 0x6c6c756e)return JSON_NULL;
	return JSON_CORRUPTED;
}

rt::String_Ref JsonKeyValuePair::GetValueRaw() const 
{
	if(_Value[-1] == '"' || _Value[-1] == '\'')return rt::String_Ref(_Value.Begin()-1, _Value.End()+1);

	if(_Value[-1] == '/')
	{
		LPCSTR p = _Value.Begin() - 1;
		while(*p != '<'){ p--; ASSERT(p>_Key.End()); };
		return rt::String_Ref(p, _Value.End()+1);
	}

	return _Value;
}

Json::_AppendingKeyedValue::_AppendingKeyedValue(Json& j, const rt::String_Ref& key)
	:_Appending(j)
{
	ASSERT(j.IsEndsWith('}'));
	j._String.Shorten(1);
	if(!j.IsEndsWith('{'))j._String += ',';
	j._String += '"'; JsonEscapeString::Concat(key, j._String); j._String+= '"'; j._String+=':';
}

Json::_MergingObject::_MergingObject(Json& j)
	:_Appending(j)
{
	ASSERT(j.IsEndsWith('}'));
	j._String.Shorten(1);
	if(j.IsEndsWith('{')){ _StartPos = INFINITE; j._String.Shorten(1); }
	else _StartPos = j._String.GetLength();
}

Json::_MergingObject::~_MergingObject()
{
	if(_pJson)
	{	if(_StartPos != INFINITE)
		{	ASSERT(_pJson->_String[_StartPos] == '{');
			if(_pJson->_String.GetLength() > _StartPos + 2)
			{
				_pJson->_String[_StartPos] = ','; 
			}
			else // merged with an empty object
			{	_pJson->_String[_StartPos] = '}';
				_pJson->_String.SetLength(_StartPos + 1);
			}
		}
		ASSERT(_pJson->IsEndsWith('}'));
	}
}

Json::_AppendingElement::_AppendingElement(Json& j)
	:_Appending(j)
{
	ASSERT(j.IsEndsWith(']'));
	j._String.Shorten(1);
	if(j._String.Last() != '[')j._String += ',';
}

Json::_AppendingArray::~_AppendingArray()
{
	if(_pJson)
	{	if(_StartPos != INFINITE){ ASSERT(_pJson->_String[_StartPos] == '['); _pJson->_String[_StartPos] = ','; }
		ASSERT(_pJson->IsEndsWith(']'));
	}
}

Json::_AppendingArray::_AppendingArray(Json& j)
	:_Appending(j)
{
	ASSERT(j.IsEndsWith(']'));
	j._String.Shorten(1);
	if(j.IsEndsWith('[')){ _StartPos = INFINITE; j._String.Shorten(1); }
	else _StartPos = j._String.GetLength();
}

Json::_WritingStringEscaped::_WritingStringEscaped(Json& j)
	:_Appending(j)
{	
	if(j.IsEndsWith('"')){ j._String.Shorten(1); }
	else j._String += '"';
}

Json::_WritingStringAtKey::_WritingStringAtKey(Json& j, const rt::String_Ref& key)
	:_Appending(j)
{
	ASSERT(j.IsEndsWith('}'));
	j._String.Shorten(1);
	if(!j.IsEndsWith('{'))j._String += ',';
	j._String += '"'; JsonEscapeString::Concat(key, j._String); j._String+= '"'; j._String+=':'; j._String+='"';
}

Json& Json::MergeObject(const rt::String_Ref& json_str_in)
{
	rt::String_Ref json_str = json_str_in.TrimSpace();
	if(json_str.GetLength() <= 2 || json_str.First() != '{' || json_str.Last() != '}')return *this;
	if(json_str.SubStr(1, json_str.GetLength() - 2).TrimSpace().IsEmpty())return *this;

	if(json_str.TrimSpace().IsEmpty())return *this;
	ASSERT(json_str.First() == '{' && json_str.Last() == '}');
	_MergingObject(*this)._pJson->_String += json_str;
	return *this;
}

Json& Json::AppendKeyWithString(const rt::String_Ref& key, const rt::String_Ref& string) // value is a string, will be escaped
{
	ASSERT(IsEndsWith('}'));
	_details::_AppendJsonValueToString(rt::JsonEscapeString(string), _AppendingKeyedValue(*this, key)._pJson->_String);
	return *this;
}

Json& Json::AppendKeyWithBinary(const rt::String_Ref& key, const rt::String_Ref& data) // value is a binary data, will be base64 encoded
{
	ASSERT(IsEndsWith('}'));
	_String.Last() = ',';
	_String += rt::SS() + '"' + key + rt::SS("\":\"");

	auto val_sz = os::Base64EncodeLength(data.GetLength());
	os::Base64Encode(_String.Extend(val_sz), data.Begin(), data.GetLength());
	_String += rt::SS("\"}");

	return *this;
}

void Json::AppendString(const rt::String_Ref& s)
{
	JsonEscapeString::Concat(s, _String);
}

Json& Json::String(const rt::String_Ref& s)
{
	_String += '"';
	JsonEscapeString::Concat(s, _String);
	_String += '"';
	return *this;
}

Json& Json::Binary(const void* data, uint32_t size)
{
	_String += '"';
	auto bs = os::Base64EncodeLength(size);
	os::Base64Encode(_String.Extend(bs), data, size);
	_String += '"';
	return *this;
}

JsonEscapeString::JsonEscapeString(const rt::String_Ref& c_string, bool add_quote)
{	
	int open = 0;
	if(add_quote)(*this)[open++] = '"';

	SetLength(c_string.GetLength()*4 + 2);
	for(UINT i=0;i<c_string.GetLength();i++)
	{	static const rt::CharacterSet_Escape esc;
		int c = c_string[i];
		if(c)
		{
			if(!esc.Has(c))
			{	(*this)[open++] = c;
			}
			else
			{	(*this)[open++] = '\\';
				(*this)[open++] = esc.Mapped(c);
			}
		}
		else
		{	*(DWORD*)&(*this)[open] = 0x3030785c;
			open += 4;
		}
	}

	if(add_quote)(*this)[open++] = '"';
	SetLength(open);
}

void JsonEscapeString::Concat(const rt::String_Ref& input, rt::String& out)
{
	for(UINT i=0;i<input.GetLength();i++)
	{	static const rt::CharacterSet_Escape esc;
		int c = input[i];
		if(c)
		{
			if(!esc.Has(c))
			{	out += (char)c;
			}
			else
			{	out += '\\';
				out += (char)esc.Mapped(c);
			}
		}
		else
		{	out += rt::SS("\x00");
		}
	}
}

void JsonBeautified::_AppendAsSingleLine(const rt::String_Ref& doc)
{
	bool in_quote = false;
	for(UINT i=0; i<doc.GetLength(); i++)
	{
		char c = doc[i];
		if(in_quote)
		{	*this += c;
			if(c == '"' && doc[i-1] != '\\')
				in_quote = false;
		}
		else
		{	if(c <= ' ')continue;
			*this += c;
			if(c == ',' || c == ':'){ *this += ' '; continue; }
			if(c == '"')in_quote = true;
		}
	}
}

void JsonBeautified::_Beautify(const rt::String_Ref& json_string, bool newline, int depth, int line_remain)
{
	rt::String_Ref doc = json_string.TrimSpace();
	if(doc.IsEmpty())return;

	if(doc[0] != '{' && doc[0] != '[')
	{	*this += doc;
		return;
	}

	if(((int)doc.GetLength()) < line_remain)
	{
		int seps = _details::JsonObject_CountSeps(doc);
		if(	seps == 0 || 
			(doc[0] == '{' && seps<=3) ||
			(doc[0] == '[' && seps<=9)
		)
			return _AppendAsSingleLine(doc);
	}

	if(!newline)
	{	
		if(_bNewLineAsCRLN)*this += '\r';
		*this += '\n';
		_AppendSpace(_Indent*depth);
	}
	*this += doc[0];
	depth++;

	if(depth)
	{
		if(_bNewLineAsCRLN)*this += '\r';
		*this += '\n';
	}

	bool not_empty = false;
	if(doc[0] == '{')
	{
		rt::JsonKeyValuePair	kv;
		rt::JsonObject obj = doc;
		while(obj.GetNextKeyValuePair(kv))
		{
			_AppendSpace(_Indent*depth);
			auto k = kv.GetKey();
			if(k[-1] == '"')
				k = rt::String_Ref(&k[-1], k.GetLength()+2);

			*this += k;
			*this += ':';
			*this += ' ';
			_Beautify(kv.GetValueRaw(), false, depth, _Line_max - _Indent*depth - (int)k.GetLength() + 3);
			*this += ',';
			if(_bNewLineAsCRLN)*this += '\r';
			*this += '\n';
			not_empty = true;
		}
	}
	else
	{	ASSERT(doc[0] == '[');
		rt::JsonArray arr = doc;
		rt::String_Ref obj;
		while(arr.GetNextObjectRaw(obj))
		{
			_AppendSpace(_Indent*depth);
			_Beautify(obj, true, depth, _Line_max - _Indent*depth - 2);
			*this += ',';
			if(_bNewLineAsCRLN)*this += '\r';
			*this += '\n';
			not_empty = true;
		}
	}

	depth--;

	if(not_empty)
	{
		if(_bNewLineAsCRLN)
		{
			Shorten(3);
			*this += '\r';
		}
		else
			Shorten(2);
		
		*this += '\n';
	}

	_AppendSpace(_Indent*depth);
	*this += doc.Last();
}

void JsonBeautified::Beautify(const rt::String_Ref& json_string, int indent, int line_remain)
{
	_Indent = indent;
	_Line_max = 80;

	_Beautify(json_string, true, 0, line_remain);
}

namespace _details
{

bool _json_verify_escaped(LPCSTR p, SIZE_T len)
{
	if(len == 0)return true;
	if(p[0] == '"' || (p[0] < ' ' && p[0] >= 0))return false;

	for(UINT i=1; i<len; i++)
	{
		if(p[i] == '"' && p[i-1] != '\\')return false;
	}

	return true;
}

} // namespace _details
} // namespace rt