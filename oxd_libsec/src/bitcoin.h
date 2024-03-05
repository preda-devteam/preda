#pragma once
#include "ecdsa.h"


namespace oxd
{   
template<>
struct SecSuite<SEC_SUITE_BITCOIN_P2PKH>: public ECDSA<(int)ECDSASchemes::BTC_ETH>
{
	friend class SecuritySuite;
	static const int				Id = SEC_SUITE_BITCOIN_P2PKH;
	static const rt::String_Ref&	Name(){ static const rt::SS r("bitcoin"); return r; }

protected:
	static void _DeriveAddress(LPCVOID pk, LPVOID out)
	{
		uint8_t* addr = (uint8_t*)out; // size = 25

		// https://en.bitcoin.it/wiki/Technical_background_of_version_1_Bitcoin_addresses
		sec::DataBlock<32> stage2, stage6;

		uint8_t prefix = 0x2 + (1&((uint8_t*)pk)[63]);
		sec::Hash<sec::HASH_SHA256> sha256;
		sha256.Update(prefix); // 1 byte 0x02 (y-coord is even), and 0x03 (y-coord is odd)
		static_assert(sizeof(PublicKey) == 64);
		sha256.Update(pk, sizeof(PublicKey)/2);
		sha256.Finalize((LPBYTE)stage2);  // stage2

		Botan::RIPEMD_160 rmd;
		rmd.update((LPCBYTE)stage2, sizeof(stage2));
		rmd.final(&addr[1]);	 // stage4 = 0x00 + stage3
		addr[0] = 0;

		sha256.Reset();
		sha256.Update(addr, 21);
		sha256.Finalize((LPBYTE)stage2);

		sha256.Reset();
		sha256.Update((LPCBYTE)stage2, sizeof(stage2));
		sha256.Finalize((LPBYTE)stage6);

		*(uint32_t*)(addr + 21) = stage6.DWords[0]; // final 25-byte bitcoin address

		rt::Zero<32 - 25>(addr + 25); // reset unused bits
		((SecureAddress*)out)->SetupChecksum(SEC_SUITE_BITCOIN_P2PKH);
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
			25,
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
			SEC_SUITE_BITCOIN_P2PKH
		};

		return &ret;
	}
};

} // namespace oxd
