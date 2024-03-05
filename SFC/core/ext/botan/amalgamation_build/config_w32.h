#undef BOTAN_DISTRIBUTION_INFO
#define BOTAN_DISTRIBUTION_INFO ""

#undef BOTAN_VERSION_VC_REVISION
#define BOTAN_VERSION_VC_REVISION ""

#ifdef min
#undef min
#endif


#ifdef max
#undef max
#endif

#pragma warning(disable:4250) // warning C4250: 'Botan::ECDSA_PrivateKey': inherits 'Botan::ECDSA_PublicKey::Botan::ECDSA_PublicKey::create_verification_op' via dominance