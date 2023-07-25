#include "data.h"
#include "../../../SFC/core/ext/7zip/7zip.h"


namespace rvm
{
namespace _details
{
	thread_local rt::BufferEx<BYTE> g_data_uncompr_buf;
}

UINT Data::Embed(const DataMutable& d)
{
	ASSERT(d.GetSize() <= 0xfffff);
	SizeLow = (WORD)d.GetSize();
	SizeHighFlag = (BYTE)(d._Flag | (d.GetSize()>>16));

	d.CopyTo(DataPacked);
	return GetEmbeddedSize();
}

UINT Data::GetEmbeddedSize(const DataMutable& d)
{
	return sizeof(SizeLow) + sizeof(SizeHighFlag) + d.GetDataSize(); 
}

bool Data::IsEmbeddable(const DataMutable& d)
{ 
	return d.GetSize() <= 0xfffff;
}

ConstData Data::GetRuntimeData() const
{
	if(GetDataType() == TYPE_RUNTIME)
	{
		return { DataPacked, GetPackedSize() };
	}
	else
		return { nullptr, 0 };
}

void DataMutable::Reset()
{
	_Flag = 0;
	rt::BufferEx<BYTE>::ChangeSize(0);
}

void DataMutable::Set(const rt::String_Ref& x, UINT data_type)
{
	_Flag = data_type&Data::TYPE_BITMASK;
	ASSERT(x.GetLength() <= 16*1024*1024);

	if(x.GetLength() < 128)
	{
		SetSize(x.GetLength());
		CopyFrom(x.Begin());
		return;
	}
	
	auto& buf = _details::g_data_uncompr_buf;
	VERIFY(buf.SetSize(rt::min(x.GetLength(), (SIZE_T)1024*1024) + 3));

	size_t outsize = buf.GetSize();
	if(	Data::TYPE_RUNTIME!=data_type && 
		ext::lzma_encode(x.Begin(), x.GetLength(), buf.Begin() + 3, outsize, 9)
	)
	{
		_Flag |= Data::PACKED_7Z;
		*(UINT*)buf.Begin()  = ((*(UINT*)buf.Begin())&0xff000000) | ((UINT)buf.GetSize() - 3);
		buf.ShrinkSize(3 + outsize);
		rt::Swap(*(rt::BufferEx<BYTE>*)this, buf);
	}
	else
	{
		SetSize(x.GetLength());
		CopyFrom(x.Begin());
	}
}

uint32_t DataMutable::Append(const rt::String_Ref& x)
{
	if(GetSize()){ ASSERT((_Flag&Data::TYPE_BITMASK) == Data::TYPE_RUNTIME); }
	{
		_Flag = Data::TYPE_RUNTIME;
	}
	
	rt::BufferEx<BYTE>::push_back((BYTE*)x.Begin(), x.GetLength());
	return (uint32_t)x.GetLength();
}

BYTE* DataMutable::GetDataBuffer(uint32_t offset)
{
	ASSERT((_Flag&Data::TYPE_BITMASK) == Data::TYPE_RUNTIME);
	ASSERT(GetSize() > offset);
	return Begin() + offset;
}

void Data::_RawJsonify(const rt::String_Ref& x, rt::String& append) const
{
	switch(GetDataType())
	{
	case TYPE_TEXT:
		append += '"';
		rt::JsonEscapeString::Concat(x, append);
		append += '"';
		break;
	case TYPE_JSON:
		append += x;
		break;
	default: // TYPE_BINARY
		append += "\"base64,";
		UINT bsize = (UINT)os::Base64EncodeLength(x.GetLength());
		UINT str_len = (UINT)append.GetLength();
		append.SetLength(bsize + str_len);
		os::Base64Encode(&append[str_len], x.Begin(), x.GetLength());
		append += '"';
		break;
	}
}

void Data::Jsonify(rt::Json& append) const
{
	if(!GetPackedSize())
	{
		append.GetInternalString() += "null";
		return;
	}

	if(IsCompressed())
	{
		auto& buf = _details::g_data_uncompr_buf;
		UINT org_size = (*(UINT*)DataPacked)&0xffffff;
		VERIFY(buf.SetSize(org_size));

		size_t outsize = org_size;
		if(ext::lzma_decode(DataPacked + 3, GetPackedSize() - 3, buf.Begin(), outsize) && org_size == outsize)
		{
			_RawJsonify(rt::String_Ref((LPCSTR)buf.Begin(), org_size), append.GetInternalString());
		}
		else
		{
			append.GetInternalString() += "\"(data corrupted)\"";
		}
	}
	else
	{
		_RawJsonify(rt::String_Ref((LPCSTR)DataPacked, GetPackedSize()), append.GetInternalString());
	}
}

bool DataMutable::JsonParse(const rt::String_Ref& str, UINT data_type)
{
	if(data_type == Data::TYPE_TEXT)
	{
		if(str.StartsWith("base64,"))
		{	
			rt::String data;
			os::Base64Decode(str.SubStr(7, str.GetLength()-7), data);
			Set(data, Data::TYPE_BINARY);
		}
		else
			Set(rt::JsonUnescapeString(str), Data::TYPE_TEXT);
	}
	else
	{
		Set(str, data_type);
	}

	return true;
}

void Data::ToString(rt::String& append) const
{
	if(GetPackedSize())
	{
		if(IsCompressed())
		{
			UINT str_size = (UINT)append.GetLength();
			UINT org_size = (*(UINT*)DataPacked)&0xffffff;
			append.SetLength(str_size + org_size);

			size_t outsize = org_size;
			if(!ext::lzma_decode(DataPacked + 3, GetPackedSize() - 3, append.Begin() + str_size, outsize) && org_size == outsize)
				append.SetLength(str_size);
		}
		else
		{
			append += rt::String_Ref((LPCSTR)DataPacked, GetPackedSize());
		}
	}
}

} // namespace rvm