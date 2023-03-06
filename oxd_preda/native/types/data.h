#pragma once
#include "../abi/vm_types.h"


namespace rvm
{

class DataMutable;

#pragma pack(push, 1)
struct Data // at 1MB max
{
	TYPETRAITS_DECLARE_NON_POD;
	enum DataType
	{
		TYPE_NULL		= 0x00,
		TYPE_TEXT		= 0x10,
		TYPE_JSON		= 0x20,
		TYPE_BINARY		= 0x30,
		TYPE_BITMASK	= 0x70,
		PACKED_7Z		= 0x80,
	};

	WORD		SizeLow;
	BYTE		SizeHighFlag;	// high 4bit is flag
	BYTE		DataPacked[1];	// !IsCompressed:[original_data]
								// IsCompressed: [original_size:24bit] + [compressed_data]

	Data(decltype(0) x){ ASSERT(x == 0); SizeLow = 0; SizeHighFlag = 0; }
	UINT		GetPackedSize() const { return *((DWORD*)this)&0xfffff; }
	auto		GetDataType() const { return (DataType)(SizeHighFlag&TYPE_BITMASK); }
	bool		IsCompressed() const { return SizeHighFlag&PACKED_7Z; }
	UINT		GetEmbeddedSize() const { return sizeof(SizeLow) + sizeof(SizeHighFlag) + GetPackedSize(); }
	UINT		Embed(const DataMutable& d);
	void		Jsonify(rt::Json& append) const;
	void		ToString(rt::String& append) const;

	void		ModifyDataType(UINT t = Data::TYPE_JSON){ SizeHighFlag = (SizeHighFlag&~TYPE_BITMASK) | (TYPE_BITMASK&t); }

	static UINT		GetEmbeddedSize(const DataMutable& d);
	static bool		IsEmbeddable(const DataMutable& d);
	static auto&	Zero(){ static const Data _zero(0); return _zero; }
	static void		GetTypeSignature(rt::String& n){ n += rt::SS("data"); }
private:
	void		_RawJsonify(const rt::String_Ref& x, rt::String& append) const;
	Data() = delete;
	Data(const Data&) = delete;
};
#pragma pack(pop)


class DataMutable: protected rt::BufferEx<BYTE>
{
	friend struct Data;
	DWORD	_Flag;
public:
	DataMutable(){ _Flag = 0; }
	DataMutable(const rt::String_Ref& x, UINT data_type = Data::TYPE_TEXT){ Set(x, data_type); }
	UINT GetDataSize() const { return (UINT)GetSize(); }

    auto operator = (const rt::String_Ref& x) -> const rt::String_Ref& { Set(x, Data::TYPE_TEXT); return x; }
	void Set(const rt::String_Ref& x, UINT data_type = Data::TYPE_TEXT);
	bool JsonParse(const rt::String_Ref& str, UINT data_type = Data::TYPE_TEXT);
};

} // namespace rvm
