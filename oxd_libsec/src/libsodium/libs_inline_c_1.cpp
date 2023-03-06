#include "libs_inline_c.h"

extern "C"
{

#include "./libsodium/src/libsodium/crypto_box/curve25519xsalsa20poly1305/ref/after_curve25519xsalsa20poly1305.c"
#include "./libsodium/src/libsodium/crypto_box/curve25519xsalsa20poly1305/ref/before_curve25519xsalsa20poly1305.c"
#include "./libsodium/src/libsodium/crypto_box/curve25519xsalsa20poly1305/ref/box_curve25519xsalsa20poly1305.c"
#include "./libsodium/src/libsodium/crypto_box/curve25519xsalsa20poly1305/ref/keypair_curve25519xsalsa20poly1305.c"

#include "./libsodium/src/libsodium/crypto_core/hsalsa20/ref2/core_hsalsa20.c"

#include "./libsodium/src/libsodium/randombytes/sysrandom/randombytes_sysrandom.c"

#include "./libsodium/src/libsodium/crypto_onetimeauth/crypto_onetimeauth.c"
#include "./libsodium/src/libsodium/crypto_onetimeauth/poly1305/onetimeauth_poly1305.c"
#include "./libsodium/src/libsodium/crypto_onetimeauth/poly1305/onetimeauth_poly1305_api.c"
#include "./libsodium/src/libsodium/crypto_onetimeauth/poly1305/onetimeauth_poly1305_try.c"
#include "./libsodium/src/libsodium/crypto_onetimeauth/poly1305/donna/auth_poly1305_donna.c"
#include "./libsodium/src/libsodium/crypto_onetimeauth/poly1305/donna/verify_poly1305_donna.c"

#include "./libsodium/src/libsodium/crypto_auth/hmacsha256/cp/hmac_hmacsha256.c"
#include "./libsodium/src/libsodium/crypto_pwhash/scryptsalsa208sha256/nosse/pwhash_scryptsalsa208sha256_nosse.c"

#include "./libsodium/src/libsodium/crypto_stream/aes128ctr/portable/afternm_aes128ctr.c"
#include "./libsodium/src/libsodium/crypto_stream/aes128ctr/portable/beforenm_aes128ctr.c"
#include "./libsodium/src/libsodium/crypto_stream/aes128ctr/portable/common_aes128ctr.c"
#include "./libsodium/src/libsodium/crypto_stream/aes128ctr/portable/consts_aes128ctr.c"
#include "./libsodium/src/libsodium/crypto_stream/aes128ctr/portable/int128_aes128ctr.c"
#include "./libsodium/src/libsodium/crypto_stream/aes128ctr/portable/stream_aes128ctr.c"
#include "./libsodium/src/libsodium/crypto_stream/aes128ctr/portable/xor_afternm_aes128ctr.c"

#include "./libsodium/src/libsodium/crypto_sign/ed25519/ref10/sc_muladd.c"

}
