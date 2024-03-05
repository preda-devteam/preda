#pragma once

extern "C" 
{
#define SODIUM_STATIC
#include "./libsodium/libsodium/src/libsodium/include/sodium.h"
}

#include "algo_base.h"
#include "../../SFC/core/ext/botan/inc/datablock.h"


namespace oxd
{

template<>
struct SecSuite<SEC_SUITE_ED25519>
{
	friend class SecuritySuite;
	static const int	Id = SEC_SUITE_ED25519;

	// Primitive Types
	typedef sec::DataBlock<32>				PublicKey;
	typedef sec::DataBlock<64, true>		PrivateKey;
	typedef sec::DataBlock<64>				Signature;
	static const rt::String_Ref&			Name(){ static const rt::SS r("ed25519"); return r; }

	struct _Entropy
	{
		BYTE e[32];
		_Entropy(){ Reset(); }
		void Reset(){ randombytes_buf(e, 32); }
		void Inc(){ ((ULONGLONG&)e)++; }
	};

	static _Entropy& _GetEntropy()
	{	thread_local _Entropy e;
		return e;
	}

protected:
	static bool _VerifySignature(LPCVOID pk, LPCVOID signature, LPCVOID pMessage, UINT MessageLen)
	{	return 0 == crypto_sign_ed25519_verify_detached((LPCBYTE)signature, (LPCBYTE)pMessage, MessageLen, (LPCBYTE)pk);
	}
	static bool _Sign(LPCVOID sk, LPCVOID pMessage, UINT MessageLen, LPVOID signature_out)
	{	return 0 == crypto_sign_ed25519_detached((LPBYTE)signature_out, NULL, (LPCBYTE)pMessage, MessageLen, (LPCBYTE)sk);
	}
	static void _GenerateKeypair(LPVOID pk, LPVOID sk, LPCVOID seed_32bytes)
	{	
		if(seed_32bytes)
		{
			crypto_sign_ed25519_seed_keypair((LPBYTE)pk, (LPBYTE)sk, (LPBYTE)seed_32bytes);
		}
		else
		{
			_GetEntropy().Inc();
			crypto_sign_ed25519_seed_keypair((LPBYTE)pk, (LPBYTE)sk, _GetEntropy().e);
		}
	}
	static bool _DerivePublicKey(LPCVOID sk, LPVOID out)
	{	memcpy(out, &((LPCBYTE)sk)[crypto_sign_ed25519_SEEDBYTES], sizeof(PublicKey));
		return true;
	}
	static void _DeriveAddress(LPCVOID pk, LPVOID out)
	{	memcpy(out, pk, sizeof(PublicKey));
		((SecureAddress*)out)->SetupChecksum(SEC_SUITE_ED25519);
	}
	static bool _DeriveEncryptionPublicKey(LPCVOID pk, LPVOID out_epk)
	{	return 0 == crypto_sign_ed25519_pk_to_curve25519((LPBYTE)out_epk, (LPBYTE)pk);
	}
	static bool _DeriveEncryptionPrivateKey(LPCVOID sk, LPVOID out_esk)
	{	return 0 == crypto_sign_ed25519_sk_to_curve25519((LPBYTE)out_esk, (LPBYTE)sk) &&
			   _DeriveEncryptionPublicKey(((LPBYTE)sk) + crypto_sign_ed25519_SEEDBYTES, ((LPBYTE)out_esk) + crypto_sign_ed25519_SEEDBYTES);
	}
	static void _Encrypt(LPCVOID epk, LPCVOID data, UINT data_size, LPVOID out)
	{	crypto_box_seal((LPBYTE)out, (LPCBYTE)data, data_size, (LPCBYTE)epk);
	}
	static bool _Decrypt(LPCVOID esk, LPCVOID data, UINT data_size, LPVOID out)
	{	return 0 == crypto_box_seal_open((LPBYTE)out, (LPCBYTE)data, data_size, ((LPCBYTE)esk) + crypto_sign_ed25519_SEEDBYTES, (LPCBYTE)esk);
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
			sizeof(PublicKey),
			_DeriveEncryptionPublicKey,
			_DeriveEncryptionPrivateKey,
			_Encrypt,
			_Decrypt,
			32,
			64,
			48,
			true,
			true,
			Name(),
			SEC_SUITE_ED25519
		};

		_GetEntropy().Reset();
		return &ret;
	}
};

} // namespace oxd
