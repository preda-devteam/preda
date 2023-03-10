#pragma once
#include "../../../SFC/essentials.h"

#ifndef RVM_HASH_SIZE
#define RVM_HASH_SIZE		(32U)
#endif

namespace rvm
{

enum class SecSuite: uint8_t
{
	Unknown = 0,

	Cryptography = 1,			// address is a public key, signing by private key
	Ethereum = Cryptography,	// ethereum
	Reserved1,					// 
	Ed25519,					// default
	CryptographyMax,

	Delegated	= 8,			// address is not based on a public key, signing is delegated to a address of Cryptography type
	RegisteredDapp = Delegated,
	RegisteredToken,
	RegisteredNonfungible,
	RegisteredDomain,
	RegisteredName,
	RegisteredMax,

	None = 0xff
};

struct Address
{	
	uint8_t		_[RVM_HASH_SIZE];
	union {
	int			_SSID:4;
	uint32_t	_CheckSum;
	};
};
typedef const Address ConstAddress;
static_assert(sizeof(Address) == 36);

enum class ScopeKeySize
{
	// non-Enumerable
	Default = 0,	// based on actual scope id, 36 (address) or n/a
	Address = 0,	// address
	UInt16,			// uint16_t
	UInt32,			// uint32_t
	UInt64,			// uint64_t
	UInt160,		// SHA160
	UInt256,		// SHA256
	UInt512,		// SHA512
	VaryingSize,	// varying size < 256B
	// Enumerable
	AddressEnumerable,		// address
	UInt16Enumerable,		// uint16_t
	UInt32Enumerable,		// uint32_t
	UInt64Enumerable,		// uint64_t
	UInt160Enumerable,		// SHA160
	UInt256Enumerable,		// SHA256
	UInt512Enumerable,		// SHA512
	VaryingSizeEnumerable,	// varying size < 256B

	Bitmask = 0xfu,
	BaseTypeBitmask = 0x7u,
	IsEnumerable = 0x8u
};

struct ScopeKey
{
	const uint8_t*	Data;
	uint32_t		Size;
};

namespace _details
{

template<int SZ>
inline constexpr uint32_t	SCOPEKEY_SHARD_DWORD(const uint8_t* p)
							{	const uint32_t* d = (const uint32_t*)p;
								if		constexpr (SZ == 1)return *(uint8_t*)d;
								else if constexpr (SZ == 2)return *(uint16_t*)d;
								else if constexpr (SZ == 3)return (*(uint32_t*)d) & 0xffffffU;
								else if constexpr (SZ == 4)return *d;
								else if constexpr (SZ == 36)return d[0] ^ d[4] ^ d[7]; // TBD: remove when code is stable
								else return d[0] ^ d[SZ/8] ^ d[SZ/4 - 1];
							}
inline constexpr uint32_t	SCOPEKEY_SHARD_DWORD(const ScopeKey& k)
							{	const uint32_t* d = (const uint32_t*)k.Data;
								if(k.Size == 36)return d[0] ^ d[4] ^ d[7];  // TBD: remove when code is stable
								return d[0] ^ d[k.Size/8] ^ d[k.Size/4 - 1];
							}
inline uint32_t				SCOPEKEY_SHARD_BITMASK(uint32_t shard_order){ return ~(((uint32_t)(-1))<<shard_order); }
inline uint32_t				SCOPEKEY_SHARD_BRANCH_BIT(uint32_t shard_order){ return shard_order?(1U<<(shard_order-1)):0; } // 0 for base, otherwise for up
inline constexpr int		SCOPEKEY_SIZE(ScopeKeySize t)
							{	switch((ScopeKeySize)((0x7u)&(int)t))
								{	case ScopeKeySize::Default: return 36;
									case ScopeKeySize::VaryingSize: return 0;
									case ScopeKeySize::UInt160: return 20;
									default: return 1<<(((0x7u)&(int)t)-1);
								}
							}
inline constexpr bool		SCOPEKEYSIZE_SHOULD_REFER(ScopeKeySize t){ return t==ScopeKeySize::Default || ((int)t&(int)ScopeKeySize::BaseTypeBitmask) >= (int)ScopeKeySize::UInt160; }

static const uint32_t		ADDRESS_DWORD_SIZE = sizeof(Address)/sizeof(uint32_t);
static const uint32_t		ADDRESS_BASE32_LEN = (sizeof(Address)*8 + 4)/5; // 58
static const uint32_t		ADDRESS_ABBREVIATION_LEN = 7;  //  xxx:yyy

inline 			 uint32_t	ADDRESS_SHARD_DWORD(const Address& a){ return SCOPEKEY_SHARD_DWORD<sizeof(Address)>((uint8_t*)&a); }
inline constexpr uint32_t	ADDRESS_SHARD_BITMASK(uint32_t shard_order){ return ~(((uint32_t)(-1))<<shard_order); }
inline 			 uint32_t	ADDRESS_SHARD_INDEX(const Address& a, uint32_t shard_order){ return ADDRESS_SHARD_DWORD(a)&ADDRESS_SHARD_BITMASK(shard_order); }
inline constexpr SecSuite	ADDRESS_SECSUITE_ID(const Address& a){ return (SecSuite)(a._SSID); }
inline			 bool		ADDRESS_IS_VALID(const Address& a){ return !(0xfffffff0 & (a._CheckSum ^ os::crc32c(a._, RVM_HASH_SIZE, (uint32_t)ADDRESS_SECSUITE_ID(a)))); }
inline			 void		ADDRESS_SET_SECSUITE(Address& a, SecSuite ssid){ a._CheckSum = ((uint8_t)ssid&0xf) | (0xfffffff0 & os::crc32c(a._, RVM_HASH_SIZE, (uint32_t)ssid)); }
inline			 bool		ADDRESS_FROM_STRING(const char str_in[ADDRESS_BASE32_LEN], Address& a){ return os::Base32CrockfordDecode(&a, sizeof(a), str_in, ADDRESS_BASE32_LEN); }
inline			 void		ADDRESS_TO_STRING(const Address& a, char str_out[ADDRESS_BASE32_LEN]){ os::Base32CrockfordEncodeLowercase(str_out, &a, sizeof(a)); }
inline			 void		ADDRESS_TO_ABBREVIATION(const Address& a, char str_out[ADDRESS_ABBREVIATION_LEN]){ char tt[ADDRESS_BASE32_LEN]; ADDRESS_TO_STRING(a,tt); *(uint32_t*)str_out = *(uint32_t*)tt; *(uint32_t*)&str_out[3] = *(uint32_t*)&tt[ADDRESS_BASE32_LEN-4];	str_out[3] = ':'; }
} // namespace _details

} // namespace rvm