#include "openssl_crypto.h"

namespace sec
{

namespace openssl
{

void OPENSSL_cleanse(void *ptr, size_t len)
{
    memset(ptr, 0, len);
}

int SHA256_Init(SHA256_CTX *c)
{
    memset(c, 0, sizeof(*c));
    c->h[0] = 0x6a09e667UL;
    c->h[1] = 0xbb67ae85UL;
    c->h[2] = 0x3c6ef372UL;
    c->h[3] = 0xa54ff53aUL;
    c->h[4] = 0x510e527fUL;
    c->h[5] = 0x9b05688cUL;
    c->h[6] = 0x1f83d9abUL;
    c->h[7] = 0x5be0cd19UL;
    c->md_len = SHA256_DIGEST_LENGTH;
    return 1;
}

#define DATA_ORDER_IS_BIG_ENDIAN 1  // memory, not cpu !!!
#include "openssl_md32_common.h"

} // namespace openssl

} // namespace sec