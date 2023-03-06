#pragma once
#include "./src/sec_datablock.h"


namespace oxd
{

enum SecSuiteId: uint8_t
{
	SEC_SUITE_UNKNOWN = 0,

	SEC_SUITE_CRYPTOGRAPHY = 1,	// address is a public key, signing by private key
	SEC_SUITE_ETHEREUM = SEC_SUITE_CRYPTOGRAPHY,	// ethereum
	SEC_SUITE_SM2,		//
	SEC_SUITE_ED25519,			// default
	SEC_SUITE_CRYPTOGRAPHY_MAX,

	SEC_SUITE_DELEGATED	= 8,	// address is not based on a public key, signing is delegated
	SEC_SUITE_REGISTERED_DAPP = SEC_SUITE_DELEGATED,
	SEC_SUITE_REGISTERED_TOKEN,
	SEC_SUITE_REGISTERED_NONFUNGIBLE,
	SEC_SUITE_REGISTERED_DOMAIN,
	SEC_SUITE_REGISTERED_NAME,
	SEC_SUITE_REGISTERED_MAX,

	SEC_SUITE_NONE = 0xff
};

namespace _details
{

typedef bool (*FUNC_VerifySignature)(LPCVOID pk, LPCVOID signature, LPCVOID pMessage, UINT MessageLen);
typedef bool (*FUNC_Sign)(LPCVOID sk, LPCVOID pMessage, UINT MessageLen, LPVOID signature_out);
typedef void (*FUNC_GenerateKeypair)(LPVOID pk, LPVOID sk);
typedef bool (*FUNC_DerivePublicKey)(LPCVOID sk, LPVOID out);
typedef void (*FUNC_DeriveAddress)(LPCVOID pk, LPVOID out);

typedef bool (*FUNC_DeriveEncryptionPublicKey)(LPCVOID pk, LPVOID out_epk);
typedef bool (*FUNC_DeriveEncryptionPrivateKey)(LPCVOID sk, LPVOID out_esk);
typedef void (*FUNC_Encrypt)(LPCVOID epk, LPCVOID data, UINT data_size, LPVOID out);  // sizeof(out) = data_size + EncryptionMacSize
typedef bool (*FUNC_Decrypt)(LPCVOID esk, LPCVOID data, UINT data_size, LPVOID out);  // sizeof(out) = data_size - EncryptionMacSize


struct SecSuiteEntry
{
	FUNC_VerifySignature	VerifySignature;
	FUNC_Sign				Sign;
	FUNC_GenerateKeypair	GenerateKeypair;
	FUNC_DerivePublicKey	DerivePublicKey;
	FUNC_DeriveAddress		DeriveAddress;

	int				PublicKeySize;
	int				PrivateKeySize;
	int				SignatureSize;
	int				AddressSize;

	FUNC_DeriveEncryptionPublicKey	DeriveEncryptionPublicKey;
	FUNC_DeriveEncryptionPrivateKey	DeriveEncryptionPrivateKey;
	FUNC_Encrypt					Encrypt;
	FUNC_Decrypt					Decrypt;

	int				EncryptionPublicKeySize;
	int				EncryptionPrivateKeySize;
	int				EncryptionBoxSize;			// sizeof(encrypted_data) = EncryptiionSizeAdded + sizeof(data)

	bool			bIsCanonicalPublicKey;
	bool			bSupportEncryption;

	rt::String_Ref	Name;
	SecSuiteId		Id;
};

} // namespace _details

class SecuritySuite;

struct SecureAddress: public SecDataBlock<36>
{	
	// <Address:32B> <Sec:4bit><CRC:28bit>
	SecSuiteId		GetSecuritySuiteId() const { return (SecSuiteId)(Bytes[32]&0xf); }
	bool			IsDelegated() const { return GetSecuritySuiteId() >= SEC_SUITE_DELEGATED; }	// address is not a public key
	bool			IsDelegatedAsDApp() const { return GetSecuritySuiteId() == SEC_SUITE_REGISTERED_DAPP; }
	bool			IsDelegatedAsToken() const { return GetSecuritySuiteId() == SEC_SUITE_REGISTERED_TOKEN; }
	bool			IsDelegatedAsName() const { return GetSecuritySuiteId() == SEC_SUITE_REGISTERED_NAME; }
	bool			IsDelegatedAsNonFungible() const { return GetSecuritySuiteId() == SEC_SUITE_REGISTERED_NONFUNGIBLE; }
	bool			IsDelegatedAsDomain() const { return GetSecuritySuiteId() == SEC_SUITE_REGISTERED_DOMAIN; }
	bool			IsValid(const SecuritySuite& ss) const;
	bool			IsValid() const;
	void			SetupChecksum(const SecuritySuite& ss);
	void			UnseededRandom(const SecuritySuite& ss);
	void			UnseededRandom(SecSuiteId ssid);
	void			Random(const SecuritySuite& ss, UINT seed);
	void			Random(SecSuiteId ssid, UINT seed);
	bool			FromString(const rt::String_Ref& str);
	void			ToString(rt::String& append) const;
	void			Jsonify(rt::Json& append) const;

	bool			SetAsDelegated(const rt::String_Ref& full_qualified_name, SecSuiteId ss = SEC_SUITE_UNKNOWN);
	void			SetAsDApp(const rt::String_Ref& name);
	void			SetAsToken(const rt::String_Ref& name);
	void			SetAsNonFungible(const rt::String_Ref& namespec);
	bool			SetAsDomain(const rt::String_Ref& domain);

private:
	void			Random(UINT seed);
	void			UnseededRandom();
	void			SwitchByteOrder();
	bool			FromBase64(const rt::String_Ref& str);
	void			ToBase64(rt::String& str) const;
    operator		LPCBYTE () const;
	operator		LPBYTE ();
};

struct b32address: public rt::tos::Base32CrockfordLowercaseOnStack<>
{
	b32address(const SecureAddress& addr);
	template<typename T>
	b32address(const T& x):b32address((const SecureAddress&)x){ static_assert(rt::TypeTraits<T>::IsPOD && sizeof(T) == sizeof(SecureAddress)); }
};

class SecuritySuite
{
	const _details::SecSuiteEntry*	_pEntry;

public:
	SecuritySuite(const SecureAddress& addr):SecuritySuite(addr.GetSecuritySuiteId()){}
	SecuritySuite(SecSuiteId ss);
	SecuritySuite();
	bool	SetId(SecSuiteId ss);

	bool	VerifySignature(LPCVOID pk, LPCVOID signature, LPCVOID pMessage, UINT MessageLen) const { return _pEntry->VerifySignature(pk, signature, pMessage, MessageLen); }
	bool	Sign(LPCVOID sk, LPCVOID pMessage, UINT MessageLen, LPVOID signature_out) const { return _pEntry->Sign(sk, pMessage, MessageLen, signature_out); }
	void	GenerateKeypair(LPVOID pk, LPVOID sk) const { _pEntry->GenerateKeypair(pk, sk); }
	bool	DerivePublicKey(LPCVOID sk, LPVOID out) const { return _pEntry->DerivePublicKey(sk, out); }
	void	DeriveAddress(LPCVOID pk, SecureAddress* out) const { _pEntry->DeriveAddress(pk, out); }
	bool	DeriveAddressFromPrivateKey(LPCVOID sk, SecureAddress* out) const;
	int		PublicKeySize() const { return _pEntry->PublicKeySize; }
	int		PrivateKeySize() const { return _pEntry->PrivateKeySize; }
	int		SignatureSize() const { return _pEntry->SignatureSize; }
	int		AddressEffectiveSize() const { return _pEntry->AddressSize; }

	bool	DeriveEncryptionPublicKey(LPCVOID pk, LPVOID out_epk) const { return _pEntry->DeriveEncryptionPublicKey(pk, out_epk); }
	bool	DeriveEncryptionPrivateKey(LPCVOID sk, LPVOID out_esk) const { return _pEntry->DeriveEncryptionPrivateKey(sk, out_esk); }
	void	Encrypt(LPCVOID epk, LPCVOID data, UINT data_size, LPVOID out) const { return _pEntry->Encrypt(epk, data, data_size, out); }
	bool	Decrypt(LPCVOID esk, LPCVOID data, UINT data_size, LPVOID out) const { return _pEntry->Decrypt(esk, data, data_size, out); }

	int		EncryptionPublicKeySize() const { return _pEntry->EncryptionPublicKeySize; }
	int		EncryptionPrivateKeySize() const { return _pEntry->EncryptionPrivateKeySize; }
	int		EncryptionBoxSize() const { return _pEntry->EncryptionBoxSize; }	// sizeof(encrypted_data) = EncryptiionSizeAdded + sizeof(data)

	bool	IsValid() const { return _pEntry != nullptr; }
	bool	IsCanonicalPublicKey() const { return _pEntry->bIsCanonicalPublicKey; }
	bool	IsEncryptionSupport() const { return _pEntry->bSupportEncryption; }

	const rt::String_Ref&			Name() const { return _pEntry->Name; }
	SecSuiteId						Id() const { return _pEntry->Id; }

	static SecSuiteId				IdFromString(const rt::String_Ref& t);
	static const rt::String_Ref&	IdToString(int ss);
	static bool						IsValidId(SecSuiteId id){ return (id>=SEC_SUITE_CRYPTOGRAPHY && id<SEC_SUITE_CRYPTOGRAPHY_MAX) || IsDelegatedId(id); }
	static bool						IsDelegatedId(SecSuiteId id){ return id>=SEC_SUITE_DELEGATED && id<SEC_SUITE_REGISTERED_MAX; }

	template<typename T>
	static void						Randomize(T& x){ Randomize(&x, sizeof(T)); }
	static void						Randomize(LPVOID p, uint32_t size);
	static uint64_t					CRC64(LPCVOID p, uint32_t sz, uint64_t init = 0);
	static uint32_t					CRC32C(LPCVOID p, uint32_t sz, uint32_t init = 0);

	static const uint32_t POWHASHSIZE = 64;
	static void						PowHash(const void* data, uint32_t size, void* hash_value);

	static const uint32_t HASHSIZE = 32;
	static void						Hash(const void* data, uint32_t size, void* hash_value);
	class Hasher
	{
		BYTE	_Placehold[128];
	public:
		static const uint32_t HASHSIZE = 32;
		Hasher();
		~Hasher();
		Hasher&			Reset();
		Hasher&			Update(LPCVOID data, UINT size);
		template<typename T>
		Hasher&			Update(const T& x){ STATIC_ASSERT(rt::TypeTraits<T>::IsPOD); return Update(&x, sizeof(x)); }
		Hasher&			Finalize(LPVOID hash_value);
		Hasher&			Calculate(const void* data, uint32_t size, void* hash_value){ Reset(); Update(data, size); return Finalize(hash_value); }
	};
};

} // namespace oxd

namespace std
{

template<>
struct hash<::oxd::SecureAddress>: public ::rt::_details::hash_compare_fix<::oxd::SecureAddress> {};

} // namespace std

#ifndef OXD_LIBSEC_TESTPROJ
#if defined(PLATFORM_WIN)
#if defined(PLATFORM_DEBUG_BUILD)
#pragma comment(lib,"oxd_libsec_d.lib")
#else
#pragma comment(lib,"oxd_libsec.lib")
#endif
#endif
#endif
