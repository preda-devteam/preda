#pragma once
#include "algo_base.h"
#include "../../SFC/core/ext/botan/inc/datablock.h"


namespace oxd
{

namespace _details
{
	static bool Delegated_VerifySignature(LPCVOID pk, LPCVOID signature, LPCVOID pMessage, UINT MessageLen){ return false; }
	static bool Delegated_Sign(LPCVOID sk, LPCVOID pMessage, UINT MessageLen, LPVOID signature_out){ return false; }
	static void Delegated_GenerateKeypair(LPVOID pk, LPVOID sk, LPCVOID){ ASSERT(0); }
	static bool Delegated_DerivePublicKey(LPCVOID sk, LPVOID out){ return false; }
	static void Delegated_DeriveAddress(LPCVOID pk, LPVOID out){ ASSERT(0); }
	static bool Delegated_DeriveEncryptionPublicKey(LPCVOID pk, LPVOID out_epk){ return false; }
	static bool Delegated_DeriveEncryptionPrivateKey(LPCVOID sk, LPVOID out_esk){ return false; }
	static void Delegated_Encrypt(LPCVOID epk, LPCVOID data, UINT data_size, LPVOID out){ ASSERT(0); }
	static bool Delegated_Decrypt(LPCVOID esk, LPCVOID data, UINT data_size, LPVOID out){ return false; }
} // namespace _details


#define DEF_SUITE(id, name, addr_size)							\
	template<> struct SecSuite<id>								\
	{															\
		static const rt::String_Ref& Name(){ static const rt::SS r(name); return r; }	\
		static const _details::SecSuiteEntry* _GetEntry()		\
		{														\
			static const _details::SecSuiteEntry ret = {		\
				_details::Delegated_VerifySignature,			\
				_details::Delegated_Sign,						\
				_details::Delegated_GenerateKeypair,			\
				_details::Delegated_DerivePublicKey,			\
				_details::Delegated_DeriveAddress,				\
				0, 0, 0, addr_size,								\
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

#define DEF_DELEGATED_SUITE(id, name) DEF_SUITE(id, name, 32)
DEF_DELEGATED_SUITE(SEC_SUITE_DELEGATED_HASH, "hash")
DEF_DELEGATED_SUITE(SEC_SUITE_DELEGATED_NAME, "name")
DEF_DELEGATED_SUITE(SEC_SUITE_DELEGATED_DAPP, "dapp")
DEF_DELEGATED_SUITE(SEC_SUITE_DELEGATED_TOKEN, "token")
#undef DEF_DELEGATED_SUITE

DEF_SUITE(SEC_SUITE_CONTRACT, "contract", 8)					// a deployed contract id
#undef DEF_SUITE

} // namespace oxd

