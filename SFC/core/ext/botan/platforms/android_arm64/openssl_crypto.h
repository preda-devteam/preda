#pragma once

#include "../../inc/cipher.h"

namespace sec
{


namespace openssl
{
#define AES_MAXNR 14
#define AES_BLOCK_SIZE 16

        struct aes_key_st {
            unsigned int rd_key[4 * (AES_MAXNR + 1)];
            unsigned int rounds;
        };
        typedef struct aes_key_st AES_KEY;


#define SHA_LONG unsigned int
#define SHA_LBLOCK      16
#define SHA256_DIGEST_LENGTH    32
#define SHA224_DIGEST_LENGTH    28

        typedef struct SHA256state_st {
            SHA_LONG h[8];
            SHA_LONG Nl, Nh;
            SHA_LONG data[SHA_LBLOCK];
            unsigned int num, md_len;
        } SHA256_CTX;


# define SHA_LBLOCK      16
# define SHA_CBLOCK      (SHA_LBLOCK*4)/* SHA treats input data as a
                                        * contiguous array of 32 bit wide
                                        * big-endian values. */

#define HASH_LONG               SHA_LONG
#define HASH_FINAL              SHA256_Final
#define HASH_CBLOCK             SHA_CBLOCK
#define HASH_CTX                SHA256_CTX

#define HASH_MAKE_STRING(c,s)   do {    \
        unsigned long ll;               \
        unsigned int  nn;               \
        switch ((c)->md_len)            \
        {   case SHA224_DIGEST_LENGTH:  \
                for (nn=0;nn<SHA224_DIGEST_LENGTH/4;nn++)       \
                {   ll=(c)->h[nn]; (void)HOST_l2c(ll,(s));   }  \
                break;                  \
            case SHA256_DIGEST_LENGTH:  \
                for (nn=0;nn<SHA256_DIGEST_LENGTH/4;nn++)       \
                {   ll=(c)->h[nn]; (void)HOST_l2c(ll,(s));   }  \
                break;                  \
            default:                    \
                if ((c)->md_len > SHA256_DIGEST_LENGTH) \
                    return 0;                           \
                for (nn=0;nn<(c)->md_len/4;nn++)                \
                {   ll=(c)->h[nn]; (void)HOST_l2c(ll,(s));   }  \
                break;                  \
        }                               \
        } while (0)


#define HASH_UPDATE             SHA256_Update
#define HASH_TRANSFORM          SHA256_Transform
#define HASH_FINAL              SHA256_Final
#define HASH_BLOCK_DATA_ORDER   sha256_block_data_order

int SHA256_Init(SHA256_CTX *c);
int HASH_UPDATE(HASH_CTX *c, const void *data_, size_t len);
void HASH_TRANSFORM(HASH_CTX *c, const unsigned char *data);
int HASH_FINAL(unsigned char *md, HASH_CTX *c);


extern "C" {

int aes_v8_set_encrypt_key(const unsigned char *userKey, const int bits,
                           AES_KEY *key);

int aes_v8_set_decrypt_key(const unsigned char *userKey, const int bits,
                           AES_KEY *key);

void aes_v8_encrypt(const unsigned char *in, unsigned char *out,
                    const AES_KEY *key);

void aes_v8_decrypt(const unsigned char *in, unsigned char *out,
                    const AES_KEY *key);

void aes_v8_cbc_encrypt(const unsigned char *in, unsigned char *out,
                        size_t length, const AES_KEY *key,
                        unsigned char *ivec, const int enc);

void aes_v8_ctr32_encrypt_blocks(const unsigned char *in, unsigned char *out,
                                 size_t len, const AES_KEY *key,
                                 const unsigned char ivec[16]);

void sha256_block_data_order(SHA256_CTX *ctx, const void *in, size_t num);

}

#define AES_set_encrypt_key aes_v8_set_encrypt_key
#define AES_set_decrypt_key aes_v8_set_decrypt_key
#define AES_encrypt aes_v8_encrypt
#define AES_decrypt aes_v8_decrypt

} // namespace openssl


template<>
class Hash<HASH_SHA256>
{
public:
    static const int HASHSIZE = _details::_HashSize<HASH_SHA256>::size;
protected:
    openssl::SHA256_CTX _Ctx;
public:
    INLFUNC Hash(){Reset();}
    INLFUNC void Reset()
    {
        openssl::SHA256_Init(&_Ctx);
    }
    INLFUNC void Update(LPCVOID data, SIZE_T size)
    {
        openssl::SHA256_Update(&_Ctx, data, size);
    }
    INLFUNC void Finalize(LPVOID HashValue)
    {
        openssl::SHA256_Final((unsigned char *)HashValue, &_Ctx);
    }
    INLFUNC void Calculate(LPCVOID data, SIZE_T size, LPVOID HashValue)
    {
        Reset();
        Update(data, size);
        Finalize(HashValue);
    }
    INLFUNC void Calculate(LPCVOID data, SIZE_T size, rt::String& hash_hex)
    {
        BYTE hash[HASHSIZE];
        Calculate(data,size,hash);

        hash_hex.SetLength(HASHSIZE*2);
        os::Base16Encode(hash_hex.Begin(), hash, HASHSIZE);
    }
    template<typename T> void Update(const T& x){ Update(&x, sizeof(x)); }
};


template<>
class Cipher<CIPHER_AES256>
{
    typedef Cipher<CIPHER_AES256> _SC;
protected:
    openssl::AES_KEY _KeyEncrypt;
    openssl::AES_KEY _KeyDecrypt;
public:
    static const UINT DataBlockSize = _details::_AES_Traits<CIPHER_AES256>::BlockSize;
    static const UINT NativeKeySize = _details::_HashSize<_details::_AES_Traits<CIPHER_AES256>::KEY_HASHER>::size;
    static void     ComputeKey(LPVOID key, LPCVOID data, UINT size){ Hash<_details::_AES_Traits<CIPHER_AES256>::KEY_HASHER>().Calculate(data, size, key); }

    void            SetKey(LPCVOID key, UINT len)
    {   BYTE hash[NativeKeySize];
        if(len != NativeKeySize){ ComputeKey(hash, key, len); key = hash; }
        int r = openssl::AES_set_encrypt_key( (const unsigned char*)key, NativeKeySize*8, &_KeyEncrypt);
        r = openssl::AES_set_decrypt_key( (const unsigned char*)key, NativeKeySize*8, &_KeyDecrypt);
        if(len != NativeKeySize)rt::Zero(hash);
    }

    void            Encrypt(LPCVOID pPlain, LPVOID pCrypt, UINT Len)
    {	ASSERT((Len%DataBlockSize) == 0);
        UINT block_count = Len / DataBlockSize;
        unsigned char* src = (unsigned char*)pPlain;
        unsigned char* dst = (unsigned char*)pCrypt;
        for (UINT i=0;i<block_count; i++)
        {
            openssl::AES_encrypt(src, dst, &_KeyEncrypt);
            src+=DataBlockSize;
            dst+=DataBlockSize;
        }
    }
    void            Decrypt(LPCVOID pCrypt, LPVOID pPlain, UINT Len)
    {	ASSERT((Len%DataBlockSize) == 0);
        UINT block_count = Len / DataBlockSize;
        unsigned char* src = (unsigned char*)pCrypt;
        unsigned char* dst = (unsigned char*)pPlain;
        for (UINT i=0;i<block_count; i++)
        {
            openssl::AES_decrypt(src, dst, &_KeyDecrypt);
            src+=DataBlockSize;
            dst+=DataBlockSize;
        }
    }
    void            EncryptBlockChained(LPCVOID pPlain, LPVOID pCrypt, UINT Len, UINT nonce)
    {   _details::CipherInitVec<DataBlockSize> IV(nonce);
        ASSERT((Len%DataBlockSize) == 0);
        auto* p = (const DataBlock<DataBlockSize>*)pPlain;
        auto* c = (DataBlock<DataBlockSize>*)pCrypt;
        Len /= DataBlockSize;
        for(UINT i=0; i<Len; i++, p++, c++)
        {    IV ^= *p;
            Encrypt(&IV, c, DataBlockSize);
            c->CopyTo(IV);
        }
    }
    void            DecryptBlockChained(LPCVOID pCrypt, LPVOID pPlain, UINT Len, UINT nonce)
    {   _details::CipherInitVec<DataBlockSize> IV(nonce);
        ASSERT((Len%DataBlockSize) == 0);
        const DataBlock<DataBlockSize>* iv = &IV;
        auto* p = (DataBlock<DataBlockSize>*)pPlain;
        auto* c = (const DataBlock<DataBlockSize>*)pCrypt;
        Len /= DataBlockSize;
        for(UINT i=0; i<Len; i++, p++, c++)
        {   Decrypt(c, p, DataBlockSize);
            *p ^= *iv;
            iv = c;
        }
    }

};

template<>
class Cipher<CIPHER_AES128>
{
    typedef Cipher<CIPHER_AES128> _SC;
protected:
    openssl::AES_KEY _KeyEncrypt;
    openssl::AES_KEY _KeyDecrypt;
public:
    static const UINT DataBlockSize = _details::_AES_Traits<CIPHER_AES128>::BlockSize;
    static const UINT NativeKeySize = _details::_HashSize<_details::_AES_Traits<CIPHER_AES128>::KEY_HASHER>::size;
    static void     ComputeKey(LPVOID key, LPCVOID data, UINT size){ Hash<_details::_AES_Traits<CIPHER_AES128>::KEY_HASHER>().Calculate(data, size, key); }

    void            SetKey(LPCVOID key, UINT len)
    {   BYTE hash[NativeKeySize];
        if(len != NativeKeySize){ ComputeKey(hash, key, len); key = hash; }
        int r = openssl::AES_set_encrypt_key( (const unsigned char*)key, NativeKeySize*8, &_KeyEncrypt);
        r = openssl::AES_set_decrypt_key( (const unsigned char*)key, NativeKeySize*8, &_KeyDecrypt);
        if(len != NativeKeySize)rt::Zero(hash);
    }

    void            Encrypt(LPCVOID pPlain, LPVOID pCrypt, UINT Len)
    {	ASSERT((Len%DataBlockSize) == 0);
        UINT block_count = Len / DataBlockSize;
        unsigned char* src = (unsigned char*)pPlain;
        unsigned char* dst = (unsigned char*)pCrypt;
        for (UINT i=0;i<block_count; i++)
        {
            openssl::AES_encrypt(src, dst, &_KeyEncrypt);
            src+=DataBlockSize;
            dst+=DataBlockSize;
        }
    }
    void            Decrypt(LPCVOID pCrypt, LPVOID pPlain, UINT Len)
    {	ASSERT((Len%DataBlockSize) == 0);
        UINT block_count = Len / DataBlockSize;
        unsigned char* src = (unsigned char*)pCrypt;
        unsigned char* dst = (unsigned char*)pPlain;
        for (UINT i=0;i<block_count; i++)
        {
            openssl::AES_decrypt(src, dst, &_KeyDecrypt);
            src+=DataBlockSize;
            dst+=DataBlockSize;
        }
    }
    void            EncryptBlockChained(LPCVOID pPlain, LPVOID pCrypt, UINT Len, UINT nonce)
    {   _details::CipherInitVec<DataBlockSize> IV(nonce);
        ASSERT((Len%DataBlockSize) == 0);
        auto* p = (const DataBlock<DataBlockSize>*)pPlain;
        auto* c = (DataBlock<DataBlockSize>*)pCrypt;
        Len /= DataBlockSize;
        for(UINT i=0; i<Len; i++, p++, c++)
        {    IV ^= *p;
            Encrypt(&IV, c, DataBlockSize);
            c->CopyTo(IV);
        }
    }
    void            DecryptBlockChained(LPCVOID pCrypt, LPVOID pPlain, UINT Len, UINT nonce)
    {   _details::CipherInitVec<DataBlockSize> IV(nonce);
        ASSERT((Len%DataBlockSize) == 0);
        const DataBlock<DataBlockSize>* iv = &IV;
        auto* p = (DataBlock<DataBlockSize>*)pPlain;
        auto* c = (const DataBlock<DataBlockSize>*)pCrypt;
        Len /= DataBlockSize;
        for(UINT i=0; i<Len; i++, p++, c++)
        {   Decrypt(c, p, DataBlockSize);
            *p ^= *iv;
            iv = c;
        }
    }

};

} // namespace sec