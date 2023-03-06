#pragma once
#include "../../../SFC/core/os/platform.h"

#if defined(PLATFORM_WIN)
#include <intrin.h>
#endif

#define SODIUM_STATIC

extern "C"
{

#include "./libsodium/src/libsodium/include/sodium/export.h"
// Doc:  https://download.libsodium.org/doc/public-key_cryptography/public-key_signatures.html
}

#pragma warning(disable:4146)
#pragma warning(disable:4244) // warning C4244: '=' : conversion from 'crypto_int64' to 'crypto_int32', possible loss of data
#pragma warning(disable:4267)
#pragma warning(disable:4996)
