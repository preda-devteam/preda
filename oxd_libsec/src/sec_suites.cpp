#include "sec_suites.h"
#include "../../SFC/core/ext/ipp/ipp_core.h"
#include "../../SFC/core/rt/json.h"


namespace oxd
{

static const rt::SS sz_NullAddress("<address:null>");

void SecureAddress::UnseededRandom(SecSuiteId ssid)
{
	UnseededRandom(SecuritySuite(ssid));
}

void SecureAddress::Random(SecSuiteId ssid, UINT s)
{
	Random(SecuritySuite(ssid), s);
}

bool SecureAddress::IsValid(const SecuritySuite& ss) const
{
	ASSERT(ss.Id() == GetSecuritySuiteId());

	ASSERT((ss.AddressEffectiveSize()%4) == 0);
	for(UINT i = ss.AddressEffectiveSize()/4; i<32/4; i++)
		if(DWords[i])return false;

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
	if(str != sz_NullAddress)
	{
		auto end = str.FindCharacterReverse(':');
		
		return	(	(end > 0 && SecDataBlock<36>::FromString(str.SubStr(0, end)))
					|| SecDataBlock<36>::FromString(str)
				) &&
				IsValid() &&
				(end < 0 || SecuritySuite::IdFromString(str.SubStr(end+1)) == GetSecuritySuiteId());
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
	else
	{
		auto& name = SecuritySuite::IdToString(ss);

		UINT org_len = (UINT)append.GetLength();
		UINT b32_len = os::Base32EncodeLength(sizeof(SecureAddress));
		VERIFY(append.SetLength(org_len + b32_len + 1 + name.GetLength()));

		os::Base32CrockfordEncodeLowercase(&append[org_len], this, sizeof(SecureAddress));
		org_len += b32_len;
		append[org_len++] = ':';
		name.CopyTo(&append[org_len]);
	}
}

void SecureAddress::Jsonify(rt::Json& json) const
{
	auto& append = (rt::String&)json;
	append += '"';
	ToString(append);
	append += '"';
}

bool SecureAddress::SetAsDelegated(const rt::String_Ref& full_qualified_name, SecSuiteId ss)
{
	if(ss == SEC_SUITE_UNKNOWN)
	{
		ss = SecuritySuite::IdFromString(full_qualified_name.GetExtName().TrimLeft(1));
	}

	if(ss == SEC_SUITE_UNKNOWN)return false;

	sec::Hash<sec::HASH_SHA256>().Calculate(full_qualified_name.Begin(), full_qualified_name.GetLength(), this);
	SetupChecksum(ss);
	return true;
}

void SecureAddress::SetAsDApp(const rt::String_Ref& name)
{
	rt::String t = name + '.' + SecuritySuite::IdToString(SEC_SUITE_REGISTERED_DAPP);
	t.MakeLower();

	SetAsDelegated(t, SEC_SUITE_REGISTERED_DAPP);
}

void SecureAddress::SetAsToken(const rt::String_Ref& name)
{
	rt::String t = name + '.' + SecuritySuite::IdToString(SEC_SUITE_REGISTERED_TOKEN);
	t.MakeLower();

	SetAsDelegated(t, SEC_SUITE_REGISTERED_TOKEN);
}

void SecureAddress::SetAsNonFungible(const rt::String_Ref& namespec)
{
	SetAsDelegated(namespec, SEC_SUITE_REGISTERED_NONFUNGIBLE);
}

// [dapp_name].dapp registered by native contract
// [asset_name].asset registered by native contract
// [subname].[dapp_name].dapp registered by rvm contract
// [subname].<LTD> registered by native contract
// root_name can be ISO3166-1 area code, or common-root (com dev org info net org app edu gov bit coin token lead me), or [common-root].[ISO3166-1 area code]
namespace _details
{

static const rt::SS DomainTLDs[] = 
{
	"",
	"com",
	"net",
	"org",
	"edu",
	"gov",
	"app",
	"usr",
	"bot",
	"bit",
	"dev",
	"coin",
	"wire",
	"team",
	"token",
	"swarm",
	"group",
	"feed",
	"news",
	"fans",
};

static const BYTE	DomainGeoCode[26][26] = 
{
	{ 2,7,3,0,0,0,0,7,1,7,7,0,0,5,0,4,0,0,0,0,0,7,0,0,7,0 },
	{ 0,0,7,0,0,0,0,0,0,0,7,0,0,0,0,7,1,0,0,0,5,0,0,4,0,0 },
	{ 0,7,0,0,7,0,0,0,0,7,0,0,0,0,0,3,7,0,5,6,0,0,0,0,0,0 },
	{ 7,7,7,6,0,7,3,7,7,0,0,7,0,7,0,7,7,7,7,7,7,7,7,7,4,0 },
	{ 3,7,0,7,0,4,0,0,7,7,7,7,4,7,7,4,7,0,0,0,3,4,4,7,7,3 },
	{ 7,7,7,7,7,7,7,7,0,0,0,4,0,7,0,7,6,0,7,7,7,7,7,3,7,7 },
	{ 0,0,4,0,1,0,0,0,0,7,7,0,0,0,7,0,0,0,0,0,0,7,0,7,0,7 },
	{ 7,7,7,7,7,7,7,7,7,7,0,7,0,0,7,7,7,0,7,0,0,6,7,7,7,7 },
	{ 7,4,3,0,0,7,7,7,7,7,7,0,0,0,0,7,0,0,0,0,7,7,7,7,7,7 },
	{ 4,7,7,7,0,7,7,7,7,7,7,7,0,7,0,0,7,7,7,6,7,7,7,7,7,7 },
	{ 7,7,7,7,0,7,0,0,0,7,7,7,0,0,7,0,7,0,7,7,7,7,0,7,0,0 },
	{ 0,0,0,7,7,4,7,7,0,7,0,7,7,7,7,7,7,0,0,1,0,0,7,7,0,7 },
	{ 0,7,0,0,1,0,0,0,6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,7,0,7,0,0,0,6,0,7,7,0,7,7,0,0,6,0,7,5,0,7,7,7,7,0 },
	{ 4,7,7,7,7,7,7,7,7,7,7,7,0,7,2,7,7,7,7,7,7,7,7,7,7,7 },
	{ 0,7,6,7,0,0,0,0,4,7,0,0,0,0,7,7,7,0,0,0,6,7,0,7,0,6 },
	{ 0,7,7,7,7,7,7,7,7,7,7,7,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
	{ 4,4,4,7,0,7,7,4,4,7,7,4,4,4,0,4,7,7,0,7,1,7,0,7,7,7 },
	{ 0,0,0,0,0,4,0,0,0,0,1,0,0,0,0,7,7,0,0,0,3,0,7,0,0,0 },
	{ 3,7,0,0,7,0,0,0,7,0,0,0,0,0,0,5,7,0,7,0,7,0,0,7,7,0 },
	{ 0,7,7,7,7,7,0,7,7,7,3,7,0,3,7,7,7,7,0,7,7,7,7,7,0,0 },
	{ 0,7,0,6,0,7,0,7,0,7,7,7,7,0,7,7,7,7,7,7,0,7,7,7,7,7 },
	{ 7,7,7,7,7,0,4,7,7,7,6,4,7,7,4,7,7,7,0,7,7,4,7,7,7,7 },
	{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
	{ 7,7,7,6,0,7,7,7,7,7,7,7,7,7,7,7,7,7,7,0,5,4,7,7,7,7 },
	{ 0,7,7,7,7,7,7,7,7,7,7,7,0,7,7,7,7,5,7,7,7,7,0,7,7,2 }
};

bool IsDomainSuffixValid(UINT ds_code)
{
	int TLD = ds_code&0xffff;
	if(TLD)
	{
		if(TLD >= sizeofArray(DomainTLDs))return false;
	}

	int Geo = ds_code>>16;
	if(Geo)
	{
		int x = Geo%26;
		int y = Geo/26;

		int flag = DomainGeoCode[y][x];
		if(flag <= 1 || flag == 3)
		{
			return true;
		}
	}

	return false;
}

bool AppendDomainSuffix(UINT ds_code, rt::String& append)
{
	int TLD = ds_code&0xffff;
	if(TLD)
	{
		if(TLD >= sizeofArray(DomainTLDs))return false;

		append += '.';
		append += DomainTLDs[TLD];
	}

	int Geo = ds_code>>16;
	if(Geo)
	{
		int x = Geo%26;
		int y = Geo/26;

		int flag = DomainGeoCode[y][x];
		if(flag <= 1 || flag == 3)
		{
			append += '.';
			append += (char)('a' + x);
			append += (char)('a' + y);

			return true;
		}
	}

	return false;
}

UINT DomainSuffixToCode(const rt::String_Ref& suffix)
{
	if(suffix.GetLength() < 3 || suffix.First() != '.')return 0;

	int TLD = 0, Geo = 0;
	rt::String_Ref s;
	if(suffix[suffix.GetLength()-3] == '.')
	{
		int x = suffix[suffix.GetLength()-2] - 'a';
		int y = suffix[suffix.GetLength()-1] - 'a';

		if(x<0 || x>=26 || y<0 || y>=26)return false;

		int flag = DomainGeoCode[y][x];
		if(flag <= 1 || flag == 3)
		{
			Geo = y*26 + x;
		}

		s = suffix.SubStr(0, suffix.GetLength() - 3);
	}
	else
		s = suffix;

	if(s.GetLength() > 3)
	{
		for(TLD = 1; TLD < sizeofArray(DomainTLDs); TLD++)
		{
			if(DomainTLDs[TLD] == s.SubStr(1))
				return TLD | (Geo<<16);
		}
	}

	return 0;
}

} // namespace _details


bool SecureAddress::SetAsDomain(const rt::String_Ref& domain_in)
{
	rt::String domain = domain_in;
	rt::String_Ref seg[4];
	UINT co = domain.Split(seg, 4, '.');
	if(co == 2)
	{
		UINT dscode = _details::DomainSuffixToCode(rt::String_Ref(seg[1].Begin()-1, seg[1].End()));
		if(!dscode)return false;
	}
	else if(co == 3)
	{
		UINT dscode = _details::DomainSuffixToCode(rt::String_Ref(seg[1].Begin()-1, seg[2].End()));
		if(!dscode)return false;
	}
	else return false;

	SetAsDelegated(domain, SEC_SUITE_REGISTERED_DOMAIN);
	return true;
}

b32address::b32address(const SecureAddress& addr)
	: rt::tos::Base32CrockfordLowercaseOnStack<>(addr)
{
	auto ss = addr.GetSecuritySuiteId();
	if(ss == SEC_SUITE_UNKNOWN && addr.IsZero())
		_len = sz_NullAddress.CopyTo(_p);
	else
	{
		auto& name = SecuritySuite::IdToString(addr.GetSecuritySuiteId());
		LPSTR p = &_p[GetLength()];
		p[0] = ':';
		p++;
		_len += name.CopyTo(p) + 1;
	}
}

SecuritySuite::SecuritySuite(SecSuiteId ss)
{
	SetId(ss);
}

SecuritySuite::SecuritySuite()
{
	_pEntry = nullptr;
}

#define SEC_SUITE_ITERATE	ITERATE(SEC_SUITE_ETHEREUM)			\
                            ITERATE(SEC_SUITE_SM2)              \
							ITERATE(SEC_SUITE_ED25519)			\
							ITERATE(SEC_SUITE_REGISTERED_DAPP)	\
							ITERATE(SEC_SUITE_REGISTERED_TOKEN)	\
							ITERATE(SEC_SUITE_REGISTERED_NAME)	\
							ITERATE(SEC_SUITE_REGISTERED_NONFUNGIBLE)	\
							
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
