#pragma once
#include "type_def.h"
#include "uint_ext.h"

namespace rvm
{

#pragma pack(push, 1)
enum BlobMime: uint8_t
{
	BMIME_NULL = 0,
	BMIME_BINARY,
	BMIME_HTML,
	BMIME_XHTML,
	BMIME_JSON,
	BMIME_JS,
	BMIME_CSS,
	BMIME_PNG,
	BMIME_GIF,
	BMIME_TIFF,
	BMIME_ICON,
	BMIME_JPEG,
	BMIME_PDF,
	BMIME_SVG,
	BMIME_TEXT,
	BMIME_WAVE,
	BMIME_ZIP,
	BMIME_XML,
	BMIME_WOFF,
	BMIME_WOFF2,
	BMIME_MP4,
	BMIME_MP3,
	BMIME_MPG,
	BMIME_AAC,
	BMIME_AVI,
	BMIME_OGA,
	BMIME_OGG,
	BMIME_WEBA,
	BMIME_WEBM,
	BMIME_WEBP,
	BMIME_BITTORRENT,			// the torrent file itself
	BMIME_LINK,

	BMIME_BITMASK = 0x7f
};

extern const rt::String_Ref&	BlobMimeToName(BlobMime m);
extern BlobMime					BlobMimeFromName(const rt::String_Ref& name);
extern BlobMime					BlobMimeFromFileExtName(const rt::String_Ref& ext);	// ".xxx"

class BlobMutable
{
	friend struct Blob;

	static const uint32_t	DATA_PADDING_SIZE = 5;
	rt::Buffer<uint32_t>	_DataPadded;
	os::File				_File;

public:
	uint8_t	Mime;

	// blob:(video/mp4)@d:\some_dir\somefile.mp4
	// blob:@d:\some_dir\somefile.mp4
	// blob:(text/plain)="plain string"
	// blob:(mime)={base64_encoded}	
	// plain text (not starts with "blob:")
	bool	FromString(const rt::String_Ref& s);
	bool	IsEmpty() const { return _DataPadded.GetSize() == 0 && !_File.IsOpen(); }
	void	Empty(){ _DataPadded.ShrinkSize(0); _File.Close(); }
	bool	IsFile() const { return _File.IsOpen(); }

	UINT			GetDataSize() const;
	uint8_t*		GetDataPtr(){ return (uint8_t*)&_DataPadded[DATA_PADDING_SIZE]; }
	const uint8_t*	GetDataPtr() const { return (uint8_t*)&_DataPadded[DATA_PADDING_SIZE]; }

	BlobMutable(){ Mime = BMIME_BINARY; }
	BlobMutable(const rt::String_Ref& str){ FromString(str); }

private:
	BlobMutable(const BlobMutable& x);
};

// its content will be off-load to DKVS as immutable value, if its size > TINY_SIZEMAX
struct Blob
{
	TYPETRAITS_DECLARE_NON_POD;
	static const uint32_t	HASHED_BLOB = 0x80;
	static const uint32_t	TINY_SIZEMAX = RVM_HASH_SIZE + 2;

	uint8_t		Mime;

	union {
	struct {
	uint8_t		TinySize;
	uint8_t		TinyData[TINY_SIZEMAX];	// DataSize <= sizeof(HashValue)
	};
	struct {
	uint24_t	DataSize;
	BlobAddress	DataHash;			// DataSize > sizeof(HashValue)
	};
	};

	Blob() = default;
	Blob(decltype(0) x){ ASSERT(x==0); SetToNull(); }
	BlobMime		GetMime() const { return (BlobMime)(Mime&BMIME_BITMASK); }
	bool			IsTiny() const { return 0 == (HASHED_BLOB&Mime); }
	bool			IsHashed() const { return HASHED_BLOB&Mime; }
	bool			IsNull() const { return Mime == BMIME_NULL; }
	void			SetToNull() const { rt::Zero(*this); }
	bool			CopyFromTinyBlob(BlobMutable& b);

	static UINT		GetEmbeddedSize(){ return sizeof(Blob); }
	UINT			GetDataSize() const { if(IsNull())return 0;	return IsTiny()?TinySize:DataSize; }
	bool			operator == (const Blob& x) const { return memcmp(this, &x, GetEmbeddedSize()) == 0; }

	UINT			Embed(const BlobMutable& bn){ ASSERT(0); return 0; }  // Blob should be created by RvmImmutableTypeCompose, use ShardingHub::GetBlobStoreHub().IssueBlob instead
	UINT			Embed(const Blob& bn)
					{	rt::Copy(*this, bn);
						if(IsTiny())rt::Zero(&TinyData[TinySize], TINY_SIZEMAX - TinySize);
						return sizeof(Blob);
					}
	template<typename T>
	static UINT		GetEmbeddedSize(const T& bn){ return sizeof(Blob); }
	template<typename T>
	static bool		IsEmbeddable(const T& bn){ return true; }

	// null									// IsTinyBlob
	// "blob:(text/plain)=plain string"		// IsTinyBlob
	// "blob:(mime)={base64_encoded}"		// IsTinyBlob
	// "blob:(mime)=[hash_string]:xxx"		//!IsTinyBlob
	void			Jsonify(rt::Json& append) const;
	bool			JsonParse(const rt::String_Ref& s);

	static auto&	Zero(){ static const Blob _zero(0); return _zero; }
	static void		GetTypeSignature(rt::String& n){ n += rt::SS("blob"); }
};
#pragma pack(pop)

} // namespace rvm
