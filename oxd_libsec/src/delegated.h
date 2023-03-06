#pragma once
#include "algo_base.h"
#include "../../SFC/core/ext/botan/inc/datablock.h"


namespace oxd
{

namespace _details
{
	static bool Delegated_VerifySignature(LPCVOID pk, LPCVOID signature, LPCVOID pMessage, UINT MessageLen){ return false; }
	static bool Delegated_Sign(LPCVOID sk, LPCVOID pMessage, UINT MessageLen, LPVOID signature_out){ return false; }
	static void Delegated_GenerateKeypair(LPVOID pk, LPVOID sk){ ASSERT(0); }
	static bool Delegated_DerivePublicKey(LPCVOID sk, LPVOID out){ return false; }
	static void Delegated_DeriveAddress(LPCVOID pk, LPVOID out){ ASSERT(0); }
	static bool Delegated_DeriveEncryptionPublicKey(LPCVOID pk, LPVOID out_epk){ return false; }
	static bool Delegated_DeriveEncryptionPrivateKey(LPCVOID sk, LPVOID out_esk){ return false; }
	static void Delegated_Encrypt(LPCVOID epk, LPCVOID data, UINT data_size, LPVOID out){ ASSERT(0); }
	static bool Delegated_Decrypt(LPCVOID esk, LPCVOID data, UINT data_size, LPVOID out){ return false; }
} // namespace _details


#define DEF_DELEGATED_SUITE(id, name)							\
	template<> struct SecSuite<id>								\
	{	friend class SecuritySuite;								\
	protected:													\
		static const rt::String_Ref& Name(){ static const rt::SS r(name); return r; }	\
		static const _details::SecSuiteEntry* _GetEntry()		\
		{														\
			static const _details::SecSuiteEntry ret = {		\
				_details::Delegated_VerifySignature,			\
				_details::Delegated_Sign,						\
				_details::Delegated_GenerateKeypair,			\
				_details::Delegated_DerivePublicKey,			\
				_details::Delegated_DeriveAddress,				\
				0, 0, 0, 32,									\
				_details::Delegated_DeriveEncryptionPublicKey,	\
				_details::Delegated_DeriveEncryptionPrivateKey,	\
				_details::Delegated_Encrypt,					\
				_details::Delegated_Decrypt,					\
				0, 0, 0,										\
				false, false,									\
				Name(),											\
				id												\
			};													\
			return &ret;										\
		}														\
	};

DEF_DELEGATED_SUITE(SEC_SUITE_REGISTERED_DAPP, "dapp")			// [dapp_name].dapp registered by native contract
DEF_DELEGATED_SUITE(SEC_SUITE_REGISTERED_TOKEN, "token")		// [token_name].token registered by native contract
DEF_DELEGATED_SUITE(SEC_SUITE_REGISTERED_NONFUNGIBLE, "nft")	// [nonfungible_namespec] registered by native contract
DEF_DELEGATED_SUITE(SEC_SUITE_REGISTERED_NAME, "name")			// [subname].[dapp_name].dapp registered by rvm contract
DEF_DELEGATED_SUITE(SEC_SUITE_REGISTERED_DOMAIN, "domain")		// [subname].<root_name> registered by native contract
																// root_name can be ISO3166-1 area code, or common-root (com dev org info net org app edu gov bit coin token team swarm group wire top usr bot), or [common-root].[ISO3166-1 area code]
#undef DEF_DELEGATED_SUITE

} // namespace oxd

