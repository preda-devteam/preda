#pragma once
#include "ecdsa.h"


namespace oxd
{

template<>
struct SecSuite<SEC_SUITE_SM2>: public ECDSA<(int)ECDSASchemes::BTC_ETH>
{
	friend class SecuritySuite;
	static const int				Id = SEC_SUITE_SM2;
	static const rt::String_Ref&	Name(){ static const rt::SS r("sm2"); return r; }

protected:
	static void _DeriveAddress(LPCVOID pk, LPVOID out)
	{
		sec::Hash<sec::HASH_SHA256>().Calculate(pk, sizeof(PublicKey), out);
		((SecureAddress*)out)->SetupChecksum(SEC_SUITE_SM2);
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
			32,
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
			SEC_SUITE_SM2
		};

		return &ret;
	}
};

} // namespace oxd
