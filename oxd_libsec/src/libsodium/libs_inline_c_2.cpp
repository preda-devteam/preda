#include "libs_inline_c.h"

extern "C"
{

#include "./libsodium/src/libsodium/crypto_core/salsa20/ref/core_salsa20.c"
#include "./libsodium/src/libsodium/crypto_auth/hmacsha256/cp/verify_hmacsha256.c"
#include "./libsodium/src/libsodium/crypto_pwhash/scryptsalsa208sha256/sse/pwhash_scryptsalsa208sha256_sse.c"

#define sigma stream_salsa20_ref_sigma
#include "./libsodium/src/libsodium/crypto_stream/salsa20/ref/stream_salsa20_ref.c"
#undef sigma
#include "./libsodium/src/libsodium/crypto_stream/salsa20/ref/xor_salsa20_ref.c"

#include "./libsodium/src/libsodium/crypto_sign/ed25519/ref10/sc_reduce.c"
}
