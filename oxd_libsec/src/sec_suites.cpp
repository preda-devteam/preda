#include "sec_suites.h"
#include "../../SFC/core/ext/ipp/ipp_core.h"
#include "../../SFC/core/rt/json.h"


namespace oxd
{

static const rt::SS sz_NullAddress("<address:null>");
static const rt::SS sz_InvalidAddress("<address:invalid>");
static const rt::SS sz_NullAddressShort("<:null>");
static const rt::SS sz_InvalidAddressShort("<:invalid>");
static const rt::CharacterSet_AlphabetDigits	DelegatedNameCharset("_-!#$@&^*()[]{}\\/<>|,;?~");
static const rt::CharacterSet_AlphabetDigits	DAppNameCharset("_-#@");
static const rt::CharacterSet_UpperCase			TokenNameCharset("-#");

void SecureAddress::UnseededRandom(SecSuiteId ssid)
{
	UnseededRandom(SecuritySuite(ssid));
}

void SecureAddress::Random(SecSuiteId ssid, UINT s)
{
	Random(SecuritySuite(ssid), s);
}

bool SecureAddress::VerifyDelegatedString(const rt::CharacterSet& charset, uint32_t leng_min, uint32_t leng_max) const
{
	auto e = rt::String_Ref((char*)Bytes, 32).FindCharacterExcluded(charset);
	if(e)
	{
		if(e > leng_max)return false;
		if(e >= 0 && e < leng_min)return false;
		for(; e < 32; e++)
			if(Bytes[e])return false;
	}

	return true;
}

bool SecureAddress::IsValid(const SecuritySuite& ss) const
{
	auto ssid = ss.Id();
	ASSERT(ssid == GetSecuritySuiteId());

	ASSERT((ss.AddressEffectiveSize()%4) == 0);
	for(UINT i = ss.AddressEffectiveSize()/4; i<32/4; i++)
		if(DWords[i])return false;

	switch(ssid)
	{
	case SEC_SUITE_DELEGATED_DAPP:
		if(!VerifyDelegatedString(DAppNameCharset, SEC_SUITE_DELEGATED_DAPP_SIZEMIN, SEC_SUITE_DELEGATED_DAPP_SIZEMAX))
			return false;
		break;
	case SEC_SUITE_DELEGATED_TOKEN:
		if(!VerifyDelegatedString(TokenNameCharset, SEC_SUITE_DELEGATED_TOKEN_SIZEMIN, SEC_SUITE_DELEGATED_TOKEN_SIZEMAX))
			return false;
		break;
	case SEC_SUITE_DELEGATED_NAME:
		if(!VerifyDelegatedString(DelegatedNameCharset, SEC_SUITE_DELEGATED_NAME_SIZEMIN, SEC_SUITE_DELEGATED_NAME_SIZEMAX))
			return false;
		break;
	}

	return !(0xfffffff0 & (DWords[8] ^ ipp::crc32c(Bytes, 32, ss.Id())));
}

void SecureAddress::SetupChecksum(const SecuritySuite& ss)
{
	ASSERT(ss.IsValid());
	ASSERT((ss.AddressEffectiveSize()%4) == 0);

	for(UINT i = ss.AddressEffectiveSize()/4; i<32/4; i++)
		DWords[i] = 0;

	DWords[8] = ((BYTE)ss.Id()) | (0xfffffff0 & ipp::crc32c(Bytes, 32, ss.Id()));
}

bool SecureAddress::IsValid() const
{
	SecuritySuite ss;
	if(!ss.SetId(GetSecuritySuiteId()))return false;

	return IsValid(ss);
}

void SecureAddress::Random(const SecuritySuite& ss, UINT seed)
{
	ASSERT(ss.IsValid());

	rt::Randomizer(seed).Randomize(*this);
	SetupChecksum(ss);
}

void SecureAddress::UnseededRandom(const SecuritySuite& ss)
{
	ASSERT(ss.IsValid());

	SecuritySuite::Randomize(*this);
	SetupChecksum(ss);
}

bool SecureAddress::FromString(const rt::String_Ref& str)
{
	if(str != sz_NullAddress && str != sz_InvalidAddress)
	{
		rt::String_Ref seg[2];
		str.Split(seg, 2, ':');

		SecSuiteId ssid = SEC_SUITE_UNKNOWN;
		if(!seg[1].IsEmpty())
		{
			ssid = SecuritySuite::IdFromString(seg[1]);
			if(ssid == SEC_SUITE_UNKNOWN)
				return false;
		}

		switch(ssid)
		{
		case SEC_SUITE_DELEGATED_NAME:
			return SetDelegatedAsName(seg[0]);
		case SEC_SUITE_DELEGATED_DAPP:
			return SetDelegatedAsDApp(seg[0]);
		case SEC_SUITE_DELEGATED_TOKEN:
			return SetDelegatedAsToken(seg[0]);
		}

		if(SecDataBlock<36>::FromString(seg[0]) && IsValid())
		{
			if(!seg[1].IsEmpty() && ssid != GetSecuritySuiteId())
				return false;

			return true;
		}

		return false;
	}
	else
	{
		rt::Zero(*this);
		return true;
	}
}

void SecureAddress::ToString(rt::String& append) const
{
	auto ss = GetSecuritySuiteId();
	if(ss == SEC_SUITE_UNKNOWN && IsZero())
		append += sz_NullAddress;
	else if(!IsValid())
		append += sz_InvalidAddress;
	else
	{
		uint32_t addr_len = SecureAddress::String::GetStringifyLength(*this);
		SecureAddress::String::Stringify(*this, append.Extend(addr_len), addr_len);
	}
}

void SecureAddress::Jsonify(rt::Json& json) const
{
	auto& append = (rt::String&)json;
	append += '"';
	ToString(append);
	append += '"';
}

void SecureAddress::SetDelegatedAsHash(const uint8_t hash[32])
{
	rt::Copy<32>(this, hash);
	SetupChecksum(SEC_SUITE_DELEGATED_HASH);
}

bool SecureAddress::SetDelegatedAsDApp(const rt::String_Ref& name_in)
{
	return SetDelegatedAsString(name_in, SEC_SUITE_DELEGATED_DAPP, DAppNameCharset, SEC_SUITE_DELEGATED_DAPP_SIZEMIN, SEC_SUITE_DELEGATED_DAPP_SIZEMAX);
}

rt::String_Ref SecureAddress::GetDelegatedString() const
{
	return rt::String_Ref((char*)this, 32).GetLengthRecalculated();
};

bool SecureAddress::SetDelegatedAsName(const rt::String_Ref& name_in)
{
	return SetDelegatedAsString(name_in, SEC_SUITE_DELEGATED_NAME, DelegatedNameCharset, SEC_SUITE_DELEGATED_NAME_SIZEMIN, SEC_SUITE_DELEGATED_NAME_SIZEMAX);
}

bool SecureAddress::SetDelegatedAsToken(const rt::String_Ref& name_in)
{
	return SetDelegatedAsString(name_in, SEC_SUITE_DELEGATED_TOKEN, TokenNameCharset, SEC_SUITE_DELEGATED_TOKEN_SIZEMIN, SEC_SUITE_DELEGATED_TOKEN_SIZEMAX);
}

bool SecureAddress::SetDelegatedAs(SecSuiteId ssid, const rt::String_Ref& name)
{
	switch(ssid)
	{
	case SEC_SUITE_DELEGATED_HASH:
		if(name.GetLength() != 32)return false;
		SetDelegatedAsHash((uint8_t*)name.Begin());
		return true;
	case SEC_SUITE_DELEGATED_NAME:
		return SetDelegatedAsName(name);
	case SEC_SUITE_DELEGATED_DAPP:
		return SetDelegatedAsDApp(name);
	case SEC_SUITE_DELEGATED_TOKEN:
		return SetDelegatedAsToken(name);
	default:
		return false;
	}
}

bool SecureAddress::ValidateDelegatedName(const SecSuiteId ssid, const rt::String_Ref& name)
{
	uint32_t sizemin, sizemax;
	const rt::CharacterSet* charset;

	switch(ssid)
	{
	case SEC_SUITE_DELEGATED_HASH:
		return name.GetLength() == SEC_SUITE_DELEGATED_HASH_SIZE;
	case SEC_SUITE_DELEGATED_NAME:
		sizemin = SEC_SUITE_DELEGATED_NAME_SIZEMIN;
		sizemax = SEC_SUITE_DELEGATED_NAME_SIZEMAX;
		charset = &DelegatedNameCharset;
		break;
	case SEC_SUITE_DELEGATED_DAPP:
		sizemin = SEC_SUITE_DELEGATED_DAPP_SIZEMIN;
		sizemax = SEC_SUITE_DELEGATED_DAPP_SIZEMAX;
		charset = &DAppNameCharset;
		break;
	case SEC_SUITE_DELEGATED_TOKEN:
		sizemin = SEC_SUITE_DELEGATED_TOKEN_SIZEMIN;
		sizemax = SEC_SUITE_DELEGATED_TOKEN_SIZEMAX;
		charset = &TokenNameCharset;
		break;
	default:
		return false;
	}

	return name.GetLength() >= sizemin && name.GetLength() <= sizemax && name.FindCharacterExcluded(*charset) < 0;
}

bool SecureAddress::SetDelegatedAsString(const rt::String_Ref& name_in, SecSuiteId ssid, const rt::CharacterSet& name_charset, uint32_t name_lengmin, uint32_t name_lengmax)
{
	rt::String_Ref name = name_in.GetLengthRecalculated();
	auto name_len = name.GetLength();
	if(name_len > name_lengmax || name_len < name_lengmin || name.FindCharacterExcluded(name_charset) >= 0)
		return false;

	memcpy(this, name.Begin(), name.GetLength());
	rt::Zero(Bytes + name.GetLength(), 32 - name.GetLength());

	SetupChecksum(ssid);
	return true;
}

void SecureAddress::SetAsContract(uint64_t contractId)
{
	*(uint64_t*)Bytes = contractId;
	rt::Zero(Bytes + sizeof(uint64_t), 32 - sizeof(uint64_t));
	SetupChecksum(SEC_SUITE_CONTRACT);
}

uint32_t SecureAddress::String::GetStringifyLength(const SecureAddress& addr, bool shorten)
{
	auto ss = addr.GetSecuritySuiteId();

	if(ss == SEC_SUITE_UNKNOWN && addr.IsZero())
		return (shorten?sz_NullAddressShort:sz_NullAddress).GetLength();
	else if(!addr.IsValid())
		return (shorten?sz_InvalidAddressShort:sz_InvalidAddress).GetLength();
	else
	{
		if(shorten)
		{
			auto ssid = addr.GetSecuritySuiteId();
			if(ssid > SEC_SUITE_DELEGATED_HASH && ssid < SEC_SUITE_DELEGATED_MAX)
				return addr.GetDelegatedString().GetLength() + 2;
			else
				return 10; //"<xxx..xxx>"
		}
		else
			return	SecuritySuite::IdToString(ss).GetLength() + 1 + 
					(
						(ss > SEC_SUITE_DELEGATED_HASH && ss < SEC_SUITE_DELEGATED_MAX)?
							addr.GetDelegatedString().GetLength():
							os::Base32EncodeLength(sizeof(SecureAddress))
					);
	}
}

uint32_t SecureAddress::String::Stringify(const SecureAddress& addr, char* buf, uint32_t buf_size, bool shorten)
{
	auto ss = addr.GetSecuritySuiteId();

	if(ss == SEC_SUITE_UNKNOWN && addr.IsZero())
	{
		auto& str = shorten?sz_NullAddressShort:sz_NullAddress;
		ASSERT(buf_size >= str.GetLength());
		return str.CopyTo(buf);
	}
	else if(!addr.IsValid())
	{
		auto& str = shorten?sz_InvalidAddressShort:sz_InvalidAddress;
		ASSERT(buf_size >= str.GetLength());
		return str.CopyTo(buf);
	}
	else
	{
		if(shorten)
		{
			if(ss > SEC_SUITE_DELEGATED_HASH && ss < SEC_SUITE_DELEGATED_MAX)
			{
				auto str = addr.GetDelegatedString();
				ASSERT(str.GetLength() + 2 <= buf_size);

				return (rt::SS() + '<' + str + '>').CopyTo(buf);
			}
			else
			{
				ASSERT(9 <= buf_size);
				uint32_t b32_len = os::Base32EncodeLength(sizeof(SecureAddress));
				char* b32_buf = (char*)alloca(b32_len);

				os::Base32CrockfordEncodeLowercase(b32_buf, &addr, sizeof(SecureAddress));
				(rt::SS() + '<' + rt::String_Ref(b32_buf, 3) + '.' + '.' + rt::String_Ref(b32_buf + b32_len - 3, 3) + '>').CopyTo(buf);

				return 10;
			}
		}
		else
		{
			auto& name = SecuritySuite::IdToString(ss);

			if(ss > SEC_SUITE_DELEGATED_HASH && ss < SEC_SUITE_DELEGATED_MAX)
			{
				auto str = addr.GetDelegatedString();
				ASSERT(name.GetLength() + 1 + str.GetLength() <= buf_size);
				return (str + ':' + name).CopyTo(buf);
			}
			else
			{
				uint32_t b32_len = os::Base32EncodeLength(sizeof(SecureAddress));
				ASSERT(name.GetLength() + 1 + b32_len <= buf_size);

				os::Base32CrockfordEncodeLowercase(buf, &addr, sizeof(SecureAddress));
				buf[b32_len] = ':';
				return name.CopyTo(buf + b32_len + 1) + 1 + b32_len;
			}
		}
	}
}

SecureAddress::String::String(const SecureAddress& addr, bool shorten)
{
	_len = Stringify(addr, _StrBuf, sizeof(_StrBuf)-1, shorten);
	_p = _StrBuf;
	_StrBuf[_len] = 0;
}

SecuritySuite::SecuritySuite(SecSuiteId ss)
{
	SetId(ss);
}

SecuritySuite::SecuritySuite()
{
	_pEntry = nullptr;
}

#define SEC_SUITE_ITERATE	ITERATE(SEC_SUITE_ETHEREUM)				\
                            ITERATE(SEC_SUITE_SM2)					\
							ITERATE(SEC_SUITE_ED25519)				\
							ITERATE(SEC_SUITE_DELEGATED_HASH)		\
							ITERATE(SEC_SUITE_DELEGATED_NAME)		\
							ITERATE(SEC_SUITE_DELEGATED_DAPP)		\
							ITERATE(SEC_SUITE_DELEGATED_TOKEN)		\
							ITERATE(SEC_SUITE_CONTRACT)	\

bool SecuritySuite::SetId(SecSuiteId ss)
{
#define ITERATE(id)	case id: _pEntry = SecSuite<id>::_GetEntry(); break;

	switch (ss)
	{
	SEC_SUITE_ITERATE
	default: _pEntry = nullptr; return false;
	}

	if(_pEntry->bIsCanonicalPublicKey)
		ASSERT(_pEntry->PublicKeySize == 32 && _pEntry->AddressSize == 32);

	return true;
#undef ITERATE
}

SecSuiteId SecuritySuite::IdFromString(const rt::String_Ref& t)
{
#define ITERATE(id)	if(SecSuite<id>::Name() == t)return id;

	SEC_SUITE_ITERATE
	return SEC_SUITE_UNKNOWN;

#undef ITERATE
}

const rt::String_Ref& SecuritySuite::IdToString(int ss)
{
#define ITERATE(id)	case id: return SecSuite<id>::Name(); break;

	switch (ss)
	{
	SEC_SUITE_ITERATE
	}

	static const rt::SS ret("unknown");
	return ret;

#undef ITERATE
}

void SecuritySuite::Randomize(LPVOID p, uint32_t size)
{
	static Botan::System_RNG rng;
	rng.randomize((LPBYTE)p, size);
}

bool SecuritySuite::DeriveAddressFromPrivateKey(LPCVOID sk, SecureAddress* out) const
{
	auto* pk = _alloca(PublicKeySize());
	if(!DerivePublicKey(sk, pk))return false;

	DeriveAddress(pk, out);
	return true;
}

typedef sec::Hash<sec::HASH_SHA256> SecuritySuiteHash;

void SecuritySuite::Hash(const void* data, uint32_t size, void* hash_value)
{
	 SecuritySuiteHash().Calculate(data, size, hash_value);
}

void SecuritySuite::PowHash(const void* data, uint32_t size, void* hash_value)
{
	sec::Hash<sec::HASH_SHA512>().Calculate(data, size, hash_value);
}

SecuritySuite::Hasher::Hasher()
{
	static_assert(sizeof(_Placehold) >= sizeof(SecuritySuiteHash));
	new (this) SecuritySuiteHash();
}

SecuritySuite::Hasher::~Hasher()
{
	((SecuritySuiteHash*)_Placehold)->~SecuritySuiteHash();
}

SecuritySuite::Hasher& SecuritySuite::Hasher::Reset()
{
	((SecuritySuiteHash*)_Placehold)->Reset();
	return *this;
}

SecuritySuite::Hasher& SecuritySuite::Hasher::Update(LPCVOID data, uint32_t size)
{
	((SecuritySuiteHash*)_Placehold)->Update(data, size);
	return *this;
}

SecuritySuite::Hasher& SecuritySuite::Hasher::Finalize(LPVOID hash_value)
{
	((SecuritySuiteHash*)_Placehold)->Finalize(hash_value);
	return *this;
}

uint64_t SecuritySuite::CRC64(LPCVOID p, uint32_t sz, uint64_t init)
{
	return ipp::crc64(p, sz, init);
}

uint32_t SecuritySuite::CRC32C(LPCVOID p, uint32_t sz, uint32_t init)
{
	return ipp::crc32c(p, sz, init);
}

#undef SEC_SUITE_ITERATE

} // namespace oxd
