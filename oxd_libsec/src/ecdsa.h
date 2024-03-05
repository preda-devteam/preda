#pragma once
#include "algo_base.h"
#include "../oxd_libsec.h"
#include "../../SFC/core/ext/botan/botan.h"

namespace oxd
{

enum class ECDSASchemes
{
	BTC_ETH = 1,
	SM2
};

template<int ECDSA_Scheme>
class ECDSA
{
	static const Botan::EC_Group	_EcGroup;
	static const std::string		_EMSA;

public:
	typedef sec::DataBlock<64>				PublicKey;
	typedef sec::DataBlock<32, true>		PrivateKey;
	typedef sec::DataBlock<64>				Signature;

protected:
	static bool _VerifySignature(LPCVOID pk, LPCVOID signature, LPCVOID pMessage, UINT MessageLen)
	{	
		try
		{
			Botan::BigInt bigx((uint8_t*)pk, 32);
			Botan::BigInt bigy((uint8_t*)pk + 32, 32);

			Botan::PointGFp publicPoint(_EcGroup.get_curve(), bigx, bigy);
			Botan::ECDSA_PublicKey reproducedPublicKey(_EcGroup, publicPoint);

			Botan::PK_Verifier verifier(reproducedPublicKey, _EMSA);
			return verifier.verify_message((const Botan::byte *)pMessage, MessageLen, (const Botan::byte*)((*(Signature*)signature).GetBytes()), sizeof(Signature));
		}catch(...){}
		return false;
	}
	static bool _Sign(LPCVOID sk, LPCVOID pMessage, UINT MessageLen, LPVOID signature_out)
	{	
		try
		{
			Botan::BigInt bigInt((uint8_t*)sk, 32);

			Botan::Null_RNG null_rng;
			Botan::ECDSA_PrivateKey keyPair(null_rng, _EcGroup, bigInt);

			Botan::AutoSeeded_RNG rng;
			Botan::PK_Signer signer(keyPair, rng, _EMSA);
			auto sig = signer.sign_message((const Botan::byte*)pMessage, MessageLen, rng);

			ASSERT(sig.size() == sizeof(Signature));
			rt::Copy<sizeof(Signature)>(signature_out, sig.data());
			
			return true;
		}catch(...){}
		return false;
	}
	static void _GenerateKeypair(LPVOID pk, LPVOID sk, LPCVOID seed_32bytes)
	{	
		if(seed_32bytes)
		{
			rt::Copy<32>(sk, seed_32bytes);
			uint64_t* p = (uint64_t*)sk;
			if(	(p[0] == 0xffffffffffffffffu && (p[1] == 0xfeffffffffffffffu || p[1] == 0xffffffffffffffffu)) ||
				(p[0] == 0 && p[1] == 0) // only 0x1 to 0xFFFF FFFF FFFF FFFF FFFF FFFF FFFF FFFE BAAE DCE6 AF48 A03B BFD2 5E8C D036 4140 is a valid private key
			)	p[0] = 0x1000000000000000u;
			_DerivePublicKey(sk, pk);
		}
		else
		{
			try
			{
				Botan::AutoSeeded_RNG rng;

				Botan::ECDSA_PrivateKey keyPair(rng, _EcGroup);
				std::vector<uint8_t> publicKey = keyPair.public_key_bits();
				ASSERT(publicKey.size() == sizeof(PublicKey) + 1);
				rt::Copy<sizeof(PublicKey)>(pk, publicKey.data() + 1);

				//memcpy(*(PublicKey*)pk, publicKey.data() + 1, (publicKey.size() - 1) * sizeof(uint8_t));

				const Botan::BigInt& skValue = keyPair.private_value();
				PrivateKey& sk1 = *(PrivateKey*)sk;
				sk1.Zero();
				skValue.binary_encode(sk1.Bytes + size_t(sk1.GetLength()) - skValue.bytes());
			}
			catch (...) { ASSERT(0); }
		}
	}
	static bool _DerivePublicKey(LPCVOID sk, LPVOID pk)
	{	
		try
		{
			Botan::Null_RNG rng;
			Botan::BigInt bigInt((uint8_t*)sk, 32);
			Botan::ECDSA_PrivateKey keyPair(rng, _EcGroup, bigInt);

			std::vector<uint8_t> publicKey = keyPair.public_key_bits();
			ASSERT(publicKey.size() == sizeof(PublicKey) + 1);
			rt::Copy<sizeof(PublicKey)>(pk, publicKey.data() + 1);

			return true;
		}
		catch (...) { }
		return false;
	}

	static bool _DeriveEncryptionPublicKey(LPCVOID pk, LPVOID out_epk){ return false; }
	static bool _DeriveEncryptionPrivateKey(LPCVOID sk, LPVOID out_esk){ return false; }
	static void _Encrypt(LPCVOID epk, LPCVOID data, UINT data_size, LPVOID out){ ASSERT(0); }
	static bool _Decrypt(LPCVOID esk, LPCVOID data, UINT data_size, LPVOID out){ return false; }
};

} // namespace oxd