#pragma once
#include "ecdsa.h"
#include "keccak256.h"

namespace oxd
{   
template<>
struct SecSuite<SEC_SUITE_ETHEREUM>: public ECDSA<(int)ECDSASchemes::BTC_ETH>
{
	friend class SecuritySuite;
	static const int				Id = SEC_SUITE_ETHEREUM;
	static const rt::String_Ref&	Name(){ static const rt::SS r("ethereum"); return r; }

protected:
	static void _DeriveAddress(LPCVOID pk, LPVOID out)
	{			
		// https://ethereum.stackexchange.com/questions/3542/how-are-ethereum-addresses-generated 
		{	SHA3_CTX a;
			keccak_init(&a);
			keccak_update(&a, (const unsigned char*)pk, sizeof(PublicKey));
			keccak_final(&a, (unsigned char*)out);
		}

		memmove(out, 12 + (unsigned char*)out, 20);	// reset low 12 bytes
		((SecureAddress*)out)->SetupChecksum(SEC_SUITE_ETHEREUM);
	}

	static const _details::SecSuiteEntry* _GetEntry()
	{
		static const _details::SecSuiteEntry ret = {
			_VerifySignature,
			_Sign,
			_GenerateKeypair,
			_DerivePublicKey,
			_DeriveAddress,
			sizeof(PublicKey),
			sizeof(PrivateKey),
			sizeof(Signature),
			20,
			_DeriveEncryptionPublicKey,
			_DeriveEncryptionPrivateKey,
			_Encrypt,
			_Decrypt,
			0,
			0,
			0,
			false,
			false,
			Name(),
			SEC_SUITE_ETHEREUM
		};

		return &ret;
	}
};

} // namespace oxd
