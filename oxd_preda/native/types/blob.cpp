#include "blob.h"


namespace rvm
{

static const rt::String_Ref _MimeNames[][2] =
{
	{	"application/null",				"" },					//	BMIME_NULL,
	{	"application/octet-stream",		".bin.dat.data" },		//	BMIME_BINARY,
	{	"text/html",					".html.htm" },			//	BMIME_HTML,
	{	"application/xhtml+xml",		".xhtml" },				//	BMIME_XHTML,
	{	"application/json",				".json" },				//	BMIME_JSON,
	{	"application/x-javascript",		".js" },				//	BMIME_JS,
	{	"text/css",						".css" },				//	BMIME_CSS,
	{	"image/png",					".png" },				//	BMIME_PNG,
	{	"image/gif",					".gif" },				//	BMIME_GIF,
	{	"image/tiff",					".tif.tiff" },			//	BMIME_TIFF,
	{	"image/x-icon",					".ico.icon" },			//	BMIME_ICON,
	{	"image/jpeg",					".jpg.jpeg" },			//	BMIME_JPEG,
	{	"application/pdf",				".pdf" },				//	BMIME_PDF,
	{	"image/svg+xml",				".svg" },				//	BMIME_SVG,
	{	"text/plain",					".txt.text.log" },		//	BMIME_TEXT,
	{	"audio/x-wav",					".wav.wave" },			//	BMIME_WAVE,
	{	"application/zip",				".zip" },				//	BMIME_ZIP,
	{	"text/xml",						".xml" },				//	BMIME_XML,
	{	"font/woff",					".woff" },				//	BMIME_WOFF,
	{	"font/woff2",					".woff2" },				//	BMIME_WOFF2,
	{	"video/mp4",					".mp4" },				//	BMIME_MP4,
	{	"audio/mpeg",					".mp3" },				//	BMIME_MP3,
	{	"video/mpeg",					".mpeg.mpg" },			//	BMIME_MPG,
	{	"audio/aac",					".aac" },				//	BMIME_AAC,
	{	"video/x-msvideo",				".avi" },				//	BMIME_AVI,
	{	"audio/ogg",					".oga" },				//	BMIME_OGA,
	{	"video/ogg",					".ogv.ogg" },			//	BMIME_OGG,
	{	"audio/webm",					".weba" },				//	BMIME_WEBA,
	{	"video/webm",					".webm" },				//	BMIME_WEBM,
	{	"image/webp",					".webp" },				//	BMIME_WEBP,
	{	"application/x-bittorrent",		".torrent" },			//	BMIME_BITTORRENT,
	{	"text/uri-list",				".url.uri" },			//	BMIME_LINK,
};

const rt::String_Ref& BlobMimeToName(BlobMime m)
{
	if(m < sizeofArray(_MimeNames))
		return _MimeNames[m][0];
	else
		return _MimeNames[1][0];
}

BlobMime BlobMimeFromName(const rt::String_Ref& name)
{
	for(UINT i=0; i<sizeofArray(_MimeNames); i++)
		if(name == _MimeNames[i][0])return (BlobMime)i;

	return BMIME_BINARY;
}

BlobMime BlobMimeFromFileExtName(const rt::String_Ref& name)
{
	ASSERT(name[0] == '.');
	if(name.GetLength() > 1024)return BMIME_BINARY;

	LPCSTR fn = ALLOCA_C_STRING(name);
	rt::String_Ref(fn, name.GetLength()).MakeLower();

	for(UINT i=0; i<sizeofArray(_MimeNames); i++)
	{
		if(strstr(_MimeNames[i][1].Begin(), fn))
			return (BlobMime)i;
	}

	return BMIME_BINARY;
}

void Blob::Jsonify(rt::Json& json) const
{
	auto& append = (rt::String&)json;
	if(IsTiny())
	{
		if(!IsNull() && TinySize)
		{
			auto bm = (BlobMime)(Mime&BMIME_BITMASK);
			if(bm == BMIME_JSON || bm == BMIME_TEXT || bm == BMIME_LINK)
			{
				thread_local rt::String escape;
				static const rt::CharacterSet_Escape  cse;

				escape = rt::String_Ref((LPCSTR)TinyData, TinySize);
				escape.EscapeCharacters(cse);
				append += rt::SS("\"blob:(") + BlobMimeToName(bm) + rt::SS(")=") + escape + '"';
			}
			else
			{
				append += rt::SS("\"blob:(") + BlobMimeToName(bm) + rt::SS(")={") + rt::tos::Base64OnStack<>(TinyData, TinySize) + rt::SS("}\"");
			}
		}
		else
		{
			append += rt::SS("null");
		}
	}
	else
	{	// blob:[hash_string]:xxx
		append += rt::SS("\"blob:(") + BlobMimeToName((BlobMime)(Mime&BMIME_BITMASK)) + rt::SS(")=[") + b32s(DataHash) + ']' + ':' + DataSize + '"';
	}
}

bool Blob::JsonParse(const rt::String_Ref& s_in)
{
	if(s_in == rt::SS("null"))
	{
		rt::Zero(*this);
		return true;
	}

	auto s = s_in.TrimQuotes().TrimSpace();
	if(!s.StartsWith("blob:("))return false;

	if(s.SubStr(6, 12) == rt::SS("text/plain)="))
	{
		thread_local rt::String unescape;
		static const rt::CharacterSet_Escape  cse;

		unescape.UnescapeCharacters(s.SubStr(18), cse);
		if(unescape.GetLength() > TINY_SIZEMAX)return false;

		Mime = BMIME_TEXT;
		memcpy(TinyData, unescape, unescape.GetLength());
		rt::Zero(TinyData + unescape.GetLength(), TINY_SIZEMAX - unescape.GetLength());

		static_assert(TINY_SIZEMAX <= ((1 << (sizeof(TinySize) * 8)) - 1), "Potential overflow in TinySize");
		TinySize = decltype(TinySize)(unescape.GetLength());
		return true;
	}
	else
	{
		auto pos = s.FindCharacter('=');
		if(pos <= 6 || s[pos-1] != ')')return false;

		if(s[pos+1] == '{' && s.Last() == '}')
		{
			rt::String_Ref b64(&s[pos+2], s.GetLength() - pos - 3);

			auto len = os::Base64DecodeLength(b64.Begin(), b64.GetLength());
			if(len > TINY_SIZEMAX)return false;

			SIZE_T outlen = 0;
			os::Base64Decode(TinyData, &outlen, b64.Begin(), b64.GetLength());
			ASSERT(outlen == len);
			rt::Zero(TinyData + outlen, TINY_SIZEMAX - outlen);

			static_assert(TINY_SIZEMAX <= ((1 << (sizeof(TinySize) * 8)) - 1), "Potential overflow in TinySize");
			TinySize = decltype(TinySize)(len);
			Mime = 0;
		}
		else if(s[pos+1] == '[')
		{
			auto sizepos = s.FindCharacterReverse(':', 6);
			if(sizepos<=0 || s[sizepos-1] != ']')return false;
			UINT size = 0;
			s.SubStr(sizepos+1).ToNumber(size);
			if(!size || size>uint24_t::Max)return false;

			if(!((oxd::SecDataBlock<RVM_HASH_SIZE>&)DataHash).FromString(rt::String_Ref(&s[pos+2], &s[sizepos-1])))return false;
			DataSize = size;
			Mime = HASHED_BLOB;
		}
		else return false;

		Mime |= BlobMimeFromName(rt::String_Ref(&s[6], &s[pos-1]));
	}

	return true;
}

UINT BlobMutable::GetDataSize() const
{
	ASSERT(_DataPadded.GetSize() == 0 || _DataPadded.GetSize() >= DATA_PADDING_SIZE);
	return UINT(_File.IsOpen()?_File.GetLength():_DataPadded.GetSize() - DATA_PADDING_SIZE);
}

bool BlobMutable::FromString(const rt::String_Ref& s)
{
	Empty();

	if(s.StartsWith("blob:"))
	{
		auto mime_end = s.FindString(")=", 5);
		auto mime_start = s.FindCharacter('(', 5);
		if(mime_end > mime_start && mime_start > 0)
			Mime = (BYTE)BlobMimeFromName(s.SubStr(mime_start, mime_end - mime_start));
		else
			Mime = 0xff;

		auto filename = s.FindCharacter('@', 5);
		if(filename > 0)
		{
			if(!_File.Open(ALLOCA_C_STRING(s.SubStr(filename+1))) || _File.GetLength() > RVM_BLOBDATA_SIZEMAX)
				return false;

			if(Mime == 0xff)
				Mime = (BYTE)BlobMimeFromFileExtName(s.GetExtName());

			return true;
		}
		else
		{
			if(Mime == 0xff)return false;

			auto content = s.SubStr(mime_end + 2);
			switch(content[0])
			{
			case '{':
				{
					if(s.Last() != '}')return false;
					UINT size = UINT(os::Base64DecodeLength(&content[1], content.GetLength()-2));
					VERIFY(_DataPadded.SetSize(size + DATA_PADDING_SIZE));

					SIZE_T t;
					VERIFY(os::Base64Decode(GetDataPtr(), &t, &content[1], content.GetLength()-2));
				}
				return true;
			case '"':
				{
					if(s.Last() != '"')return false;
					VERIFY(_DataPadded.SetSize(DATA_PADDING_SIZE + content.GetLength()-2));
					memcpy(GetDataPtr(), &content[1], content.GetLength()-2);
				}
				return true;
			}

			return false;
		}
	}
	else
	{
		Mime = BMIME_TEXT;

		if(s.GetLength() > RVM_BLOBDATA_SIZEMAX)
			return false;

		_DataPadded.SetSize(s.GetLength() + DATA_PADDING_SIZE);
		memcpy(GetDataPtr(), s.Begin(), s.GetLength());
	}

	return true;
}

bool Blob::CopyFromTinyBlob(BlobMutable& b)
{
	rt::Zero(TinyData);

	if(b.GetDataSize() > TINY_SIZEMAX)return false;

	Mime = b.Mime;
	TinySize = b.GetDataSize();
	if(b.IsFile())
	{
		return b._File.Read(TinyData, TinySize) == TinySize;
	}
	else
	{
		memcpy(TinyData, b.GetDataPtr(), TinySize);
		return true;
	}
}

} // namespace rvm
