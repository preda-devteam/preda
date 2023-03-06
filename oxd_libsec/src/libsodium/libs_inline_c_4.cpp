#include "libs_inline_c.h"


extern "C"
{

#include "./libsodium/src/libsodium/crypto_core/salsa208/ref/core_salsa208.c"
#include "./libsodium/src/libsodium/crypto_auth/hmacsha512256/cp/hmac_hmacsha512256.c"
#include "./libsodium/src/libsodium/crypto_auth/hmacsha512256/cp/verify_hmacsha512256.c"
#include "./libsodium/src/libsodium/crypto_hash/sha512/cp/hash_sha512.c"


#include "./libsodium/src/libsodium/crypto_scalarmult/crypto_scalarmult.c"
#include "./libsodium/src/libsodium/crypto_scalarmult/curve25519/scalarmult_curve25519_api.c"
#include "./libsodium/src/libsodium/crypto_scalarmult/curve25519/donna_c64/base_curve25519_donna_c64.c"
#include "./libsodium/src/libsodium/crypto_scalarmult/curve25519/donna_c64/smult_curve25519_donna_c64.c"
#include "./libsodium/src/libsodium/crypto_scalarmult/curve25519/ref10/base_curve25519_ref10.c"
#include "./libsodium/src/libsodium/crypto_scalarmult/curve25519/ref10/fe_0_curve25519_ref10.c"
#include "./libsodium/src/libsodium/crypto_scalarmult/curve25519/ref10/fe_1_curve25519_ref10.c"
#include "./libsodium/src/libsodium/crypto_scalarmult/curve25519/ref10/fe_add_curve25519_ref10.c"
#include "./libsodium/src/libsodium/crypto_scalarmult/curve25519/ref10/fe_copy_curve25519_ref10.c"
#include "./libsodium/src/libsodium/crypto_scalarmult/curve25519/ref10/fe_cswap_curve25519_ref10.c"
#include "./libsodium/src/libsodium/crypto_scalarmult/curve25519/ref10/fe_frombytes_curve25519_ref10.c"
#include "./libsodium/src/libsodium/crypto_scalarmult/curve25519/ref10/fe_invert_curve25519_ref10.c"
#include "./libsodium/src/libsodium/crypto_scalarmult/curve25519/ref10/fe_mul121666_curve25519_ref10.c"
#include "./libsodium/src/libsodium/crypto_scalarmult/curve25519/ref10/fe_mul_curve25519_ref10.c"
#include "./libsodium/src/libsodium/crypto_scalarmult/curve25519/ref10/fe_sq_curve25519_ref10.c"
#include "./libsodium/src/libsodium/crypto_scalarmult/curve25519/ref10/fe_sub_curve25519_ref10.c"
#include "./libsodium/src/libsodium/crypto_scalarmult/curve25519/ref10/fe_tobytes_curve25519_ref10.c"
#include "./libsodium/src/libsodium/crypto_scalarmult/curve25519/ref10/scalarmult_curve25519_ref10.c"

#include "./libsodium/src/libsodium/crypto_stream/chacha20/ref/stream_chacha20_ref.c"

}


