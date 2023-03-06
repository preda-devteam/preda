#include "libs_inline_c.h"

extern "C"
{

#include "./libsodium/src/libsodium/crypto_core/salsa2012/ref/core_salsa2012.c"
#include "./libsodium/src/libsodium/crypto_auth/hmacsha512/cp/hmac_hmacsha512.c"
#include "./libsodium/src/libsodium/crypto_auth/hmacsha512/cp/verify_hmacsha512.c"
#include "./libsodium/src/libsodium/crypto_hash/sha256/cp/hash_sha256.c"

#define sigma stream_xsalsa20_sigma
#include "./libsodium/src/libsodium/crypto_stream/xsalsa20/ref/stream_xsalsa20.c"
#undef sigma
#include "./libsodium/src/libsodium/crypto_stream/xsalsa20/ref/xor_xsalsa20.c"

}
