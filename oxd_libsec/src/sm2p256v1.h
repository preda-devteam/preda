#pragma once
#include "algo_base.h"
#include "../../SFC/core/ext/botan/botan.h"

namespace oxd
{
	template<>
	struct SecSuite<SEC_SUITE_SM2>
	{
		friend class SecuritySuite;
		static const int	Id = SEC_SUITE_SM2;

		// Primitive Types
		typedef sec::DataBlock<64>				PublicKey;
		typedef sec::DataBlock<32, true>		PrivateKey;
		typedef sec::DataBlock<64>				Signature;
		static const rt::String_Ref& Name() { static const rt::SS r("sm2"); return r; }

	protected:
		static bool _VerifySignature(LPCVOID pk, LPCVOID signature, LPCVOID pMessage, UINT MessageLen)
		{
			try {
				rt::String keyString;
				keyString.SetLength(128);
				(*(PublicKey*)pk).ToBase16(keyString);

				Botan::BigInt::Base type = Botan::BigInt::Base::Hexadecimal;
				Botan::BigInt bigx(reinterpret_cast<const uint8_t*>(&(keyString.GetString())[0]), 64, type);
				Botan::BigInt bigy(reinterpret_cast<const uint8_t*>(&(keyString.GetString())[64]), 64, type);

				Botan::EC_Group group("sm2p256v1");
				Botan::PointGFp publicPoint(group.get_curve(), bigx, bigy);
				Botan::SM2_PublicKey reproducedPublicKey(group, publicPoint);

				Botan::PK_Verifier verifier(reproducedPublicKey, "SM2_Sig(SM3)");
				return verifier.verify_message((const Botan::byte*)pMessage, MessageLen, (const Botan::byte*)(*(Signature*)signature).GetBytes(), 64);
			}
			catch (...) { _LOGC_ERROR("Failed in _VerifySignature(LPCVOID pk, LPCVOID signature, LPCVOID pMessage, UINT MessageLen)"); ASSERT(false); }
			return false;
		}
		static bool _Sign(LPCVOID sk, LPCVOID pMessage, UINT MessageLen, LPVOID signature_out)
		{
			try {
				rt::String kp;
				kp.SetLength(64);
				(*(PrivateKey*)sk).ToBase16(kp);

				Botan::AutoSeeded_RNG rng;
				Botan::EC_Group ecGroup("sm2p256v1");
				Botan::BigInt::Base type = Botan::BigInt::Base::Hexadecimal;
				Botan::BigInt bigInt(reinterpret_cast<const uint8_t*>(kp.GetString()), kp.GetLength(), type);
				Botan::SM2_PrivateKey keyPair(rng, ecGroup, bigInt);

				Botan::PK_Signer signer(keyPair, rng, "SM2_Sig(SM3)");
				auto sig = signer.sign_message((const Botan::byte*)pMessage, MessageLen, rng);

				ASSERT(sig.size() == 64);
				memcpy(*(PublicKey*)signature_out, sig.data(), sig.size() * sizeof(Botan::byte));

				return true;
			}
			catch (...) { _LOGC_ERROR("Failed in _Sign(LPCVOID sk, LPCVOID pMessage, UINT MessageLen, LPVOID signature_out)"); ASSERT(false); }
			return false;
		}
		static void _GenerateKeypair(LPVOID pk, LPVOID sk)
		{
			try {
				Botan::AutoSeeded_RNG rng;
				Botan::EC_Group ecGroup("sm2p256v1");

				Botan::SM2_PrivateKey keyPair(rng, ecGroup);
				std::vector<uint8_t> publicKey = keyPair.public_key_bits();
				memcpy(*(PublicKey*)pk, publicKey.data() + 1, (publicKey.size() - 1) * sizeof(uint8_t));

				Botan::BigInt skValue = keyPair.private_value();
				PrivateKey& sk1 = *(PrivateKey*)sk;
				memset(sk1.Bytes, 0, size_t(sk1.GetLength()) - skValue.bytes());
				skValue.binary_encode(sk1.Bytes + size_t(sk1.GetLength()) - skValue.bytes());
			}
			catch (...) { _LOGC_ERROR("Failed in _GenerateKeypair(LPVOID pk, LPVOID sk)"); ASSERT(false); }
		}
		static bool _DerivePublicKey(LPCVOID sk, LPVOID out)
		{
			try {
				rt::String kp;
				kp.SetLength(64);
				(*(PrivateKey*)sk).ToBase16(kp);

				Botan::AutoSeeded_RNG rng;
				Botan::EC_Group ecGroup("sm2p256v1");
				Botan::BigInt::Base type = Botan::BigInt::Base::Hexadecimal;
				Botan::BigInt bigInt(reinterpret_cast<const uint8_t*>(kp.GetString()), kp.GetLength(), type);
				Botan::SM2_PrivateKey keyPair(rng, ecGroup, bigInt);

				std::vector<uint8_t> publicKey = keyPair.public_key_bits();
				memcpy(*(PublicKey*)out, publicKey.data() + 1, (publicKey.size() - 1) * sizeof(uint8_t));

				return true;
			}
			catch (...) { _LOGC_ERROR("Failed in _SetKeypair(LPCVOID key, LPVOID pk, LPVOID sk)"); ASSERT(false); }
			return false;
		}
		static void _DeriveAddress(LPCVOID pk, LPVOID out)
		{
			// https://ethereum.stackexchange.com/questions/3542/how-are-ethereum-addresses-generated 
			{	SHA3_CTX a;
				keccak_init(&a);
				keccak_update(&a, (const unsigned char*)pk, sizeof(PublicKey));
				keccak_final(&a, (unsigned char*)out);
			}

			((SecureAddress*)out)->SetupChecksum(SEC_SUITE_SM2);
		}
		static bool _DeriveEncryptionPublicKey(LPCVOID pk, LPVOID out_epk){ return false; }
		static bool _DeriveEncryptionPrivateKey(LPCVOID sk, LPVOID out_esk){ return false; }
		static void _Encrypt(LPCVOID epk, LPCVOID data, UINT data_size, LPVOID out){ ASSERT(0); }
		static bool _Decrypt(LPCVOID esk, LPCVOID data, UINT data_size, LPVOID out){ return false; }

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
