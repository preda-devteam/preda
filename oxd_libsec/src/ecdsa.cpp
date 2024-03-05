#include "ecdsa.h"

namespace oxd
{

template<>
const Botan::EC_Group	ECDSA<(int)ECDSASchemes::BTC_ETH>::_EcGroup("secp256k1");
template<>
const std::string		ECDSA<(int)ECDSASchemes::BTC_ETH>::_EMSA("EMSA1(SHA-256)");

template<>
const Botan::EC_Group	ECDSA<(int)ECDSASchemes::SM2>::_EcGroup("sm2p256v1");
template<>
const std::string		ECDSA<(int)ECDSASchemes::SM2>::_EMSA("SM2_Sig(SM3)");

} // namespace oxd