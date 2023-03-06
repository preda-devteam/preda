/*
* Botan 2.17.3 Amalgamation
* (C) 1999-2020 The Botan Authors
*
* Botan is released under the Simplified BSD License (see license.txt)
*/

#ifndef BOTAN_AMALGAMATION_H_
#define BOTAN_AMALGAMATION_H_

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <deque>
#include <exception>
#include <functional>
#include <iosfwd>
#include <istream>
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

/*
* Build configuration for Botan 2.17.3
*
* Automatically generated from
* 'configure.py --amalgamation --disable-shared --cc=clang --no-autoload --enable-modules=auto_rng,system_rng,rsa,sha1_sse2,sha1,sha2_32,sha2_64,sha3,sm2,sm3,sm4,emsa1,emsa_pkcs1,emsa_pssr,emsa_raw,dh,ecdh,emsa_x931,dev_random,md5,crc32,cbc,des,blowfish,curve25519,dsa,aes,tls,commoncrypto --with-local-config=config_ios.h --os=ios --prefix=iphone-64 --cpu=armv8-a --disable-cc-tests'
*
* Target
*  - Compiler: clang++ -fstack-protector -pthread -stdlib=libc++ -std=c++11 -D_REENTRANT -O3
*  - Arch: arm64
*  - OS: ios
*/

#define BOTAN_VERSION_MAJOR 2
#define BOTAN_VERSION_MINOR 17
#define BOTAN_VERSION_PATCH 3
#define BOTAN_VERSION_DATESTAMP 0


#define BOTAN_VERSION_RELEASE_TYPE "unreleased"

#define BOTAN_VERSION_VC_REVISION "git:dcce309c7f87d976753c34024f313d58626a2197"

#define BOTAN_DISTRIBUTION_INFO "unspecified"

/* How many bits per limb in a BigInt */
#define BOTAN_MP_WORD_BITS 64


#define BOTAN_INSTALL_PREFIX R"(iphone-64)"
#define BOTAN_INSTALL_HEADER_DIR R"(include/botan-2)"
#define BOTAN_INSTALL_LIB_DIR R"(iphone-64/lib)"
#define BOTAN_LIB_LINK ""
#define BOTAN_LINK_FLAGS "-fstack-protector -pthread -stdlib=libc++"

#define BOTAN_SYSTEM_CERT_BUNDLE "/etc/ssl/cert.pem"

#ifndef BOTAN_DLL
  #define BOTAN_DLL 
#endif

/* Target identification and feature test macros */

#define BOTAN_TARGET_OS_IS_IOS

#define BOTAN_TARGET_OS_HAS_ARC4RANDOM
#define BOTAN_TARGET_OS_HAS_ATOMICS
#define BOTAN_TARGET_OS_HAS_COMMONCRYPTO
#define BOTAN_TARGET_OS_HAS_FILESYSTEM
#define BOTAN_TARGET_OS_HAS_POSIX1
#define BOTAN_TARGET_OS_HAS_POSIX_MLOCK
#define BOTAN_TARGET_OS_HAS_SOCKETS
#define BOTAN_TARGET_OS_HAS_THREAD_LOCAL
#define BOTAN_TARGET_OS_HAS_THREADS


#define BOTAN_BUILD_COMPILER_IS_CLANG




#define BOTAN_TARGET_ARCH_IS_ARM64
#define BOTAN_TARGET_CPU_IS_LITTLE_ENDIAN
#define BOTAN_TARGET_CPU_IS_ARM_FAMILY
#define BOTAN_TARGET_CPU_HAS_NATIVE_64BIT

#define BOTAN_TARGET_SUPPORTS_ARMV8CRYPTO
#define BOTAN_TARGET_SUPPORTS_NEON






/*
* Module availability definitions
*/
#define BOTAN_HAS_AEAD_GCM 20131128
#define BOTAN_HAS_AEAD_MODES 20131128
#define BOTAN_HAS_AES 20131128
#define BOTAN_HAS_ASN1 20171109
#define BOTAN_HAS_AUTO_RNG 20161126
#define BOTAN_HAS_AUTO_SEEDING_RNG 20160821
#define BOTAN_HAS_BASE64_CODEC 20131128
#define BOTAN_HAS_BIGINT 20131128
#define BOTAN_HAS_BIGINT_MP 20151225
#define BOTAN_HAS_BLOCK_CIPHER 20131128
#define BOTAN_HAS_BLOWFISH 20180718
#define BOTAN_HAS_CIPHER_MODES 20180124
#define BOTAN_HAS_CIPHER_MODE_PADDING 20131128
#define BOTAN_HAS_COMMONCRYPTO 20180903
#define BOTAN_HAS_CPUID 20170917
#define BOTAN_HAS_CRC32 20131128
#define BOTAN_HAS_CTR_BE 20131128
#define BOTAN_HAS_CURVE_25519 20170621
#define BOTAN_HAS_DES 20131128
#define BOTAN_HAS_DIFFIE_HELLMAN 20131128
#define BOTAN_HAS_DL_GROUP 20131128
#define BOTAN_HAS_DL_PUBLIC_KEY_FAMILY 20131128
#define BOTAN_HAS_DSA 20131128
#define BOTAN_HAS_ECC_GROUP 20170225
#define BOTAN_HAS_ECC_KEY 20190801
#define BOTAN_HAS_ECC_PUBLIC_KEY_CRYPTO 20131128
#define BOTAN_HAS_ECDH 20131128
#define BOTAN_HAS_ECDSA 20131128
#define BOTAN_HAS_EC_CURVE_GFP 20131128
#define BOTAN_HAS_EME_PKCS1 20190426
#define BOTAN_HAS_EME_PKCS1v15 20131128
#define BOTAN_HAS_EMSA1 20131128
#define BOTAN_HAS_EMSA_PKCS1 20140118
#define BOTAN_HAS_EMSA_PSSR 20131128
#define BOTAN_HAS_EMSA_RAW 20131128
#define BOTAN_HAS_EMSA_X931 20140118
#define BOTAN_HAS_ENTROPY_SOURCE 20151120
#define BOTAN_HAS_GHASH 20201002
#define BOTAN_HAS_HASH 20180112
#define BOTAN_HAS_HASH_ID 20131128
#define BOTAN_HAS_HEX_CODEC 20131128
#define BOTAN_HAS_HMAC 20131128
#define BOTAN_HAS_HMAC_DRBG 20140319
#define BOTAN_HAS_KDF2 20131128
#define BOTAN_HAS_KDF_BASE 20131128
#define BOTAN_HAS_KEYPAIR_TESTING 20131128
#define BOTAN_HAS_MAC 20150626
#define BOTAN_HAS_MD5 20131128
#define BOTAN_HAS_MDX_HASH_FUNCTION 20131128
#define BOTAN_HAS_MGF1 20140118
#define BOTAN_HAS_MODES 20150626
#define BOTAN_HAS_MODE_CBC 20131128
#define BOTAN_HAS_NUMBERTHEORY 20131128
#define BOTAN_HAS_OCSP 20161118
#define BOTAN_HAS_PEM_CODEC 20131128
#define BOTAN_HAS_PK_PADDING 20131128
#define BOTAN_HAS_PUBLIC_KEY_CRYPTO 20131128
#define BOTAN_HAS_RSA 20160730
#define BOTAN_HAS_SHA1 20131128
#define BOTAN_HAS_SHA2_32 20131128
#define BOTAN_HAS_SHA2_64 20131128
#define BOTAN_HAS_SHA3 20161018
#define BOTAN_HAS_SM2 20180801
#define BOTAN_HAS_SM3 20170402
#define BOTAN_HAS_SM4 20170716
#define BOTAN_HAS_STATEFUL_RNG 20160819
#define BOTAN_HAS_STREAM_CIPHER 20131128
#define BOTAN_HAS_SYSTEM_RNG 20141202
#define BOTAN_HAS_TLS 20191210
#define BOTAN_HAS_TLS_V10_PRF 20131128
#define BOTAN_HAS_TLS_V12_PRF 20131128
#define BOTAN_HAS_UTIL_FUNCTIONS 20180903
#define BOTAN_HAS_X25519 20180910
#define BOTAN_HAS_X509 20180911
#define BOTAN_HAS_X509_CERTIFICATES 20151023


/*
* Local/misc configuration options (if any) follow
*/
#undef BOTAN_DISTRIBUTION_INFO
#define BOTAN_DISTRIBUTION_INFO ""

#undef BOTAN_VERSION_VC_REVISION
#define BOTAN_VERSION_VC_REVISION ""

//#undef BOTAN_USE_GCC_INLINE_ASM

#undef verify





/*
* Things you can edit (but probably shouldn't)
*/

#if !defined(BOTAN_DEPRECATED_PUBLIC_MEMBER_VARIABLES)

  #if defined(BOTAN_NO_DEPRECATED)
     #define BOTAN_DEPRECATED_PUBLIC_MEMBER_VARIABLES private
  #else
     #define BOTAN_DEPRECATED_PUBLIC_MEMBER_VARIABLES public
  #endif

#endif

/* How much to allocate for a buffer of no particular size */
#define BOTAN_DEFAULT_BUFFER_SIZE 1024

/*
* Total maximum amount of RAM (in KiB) we will lock into memory, even
* if the OS would let us lock more
*/
#define BOTAN_MLOCK_ALLOCATOR_MAX_LOCKED_KB 512

/*
* If BOTAN_MEM_POOL_USE_MMU_PROTECTIONS is defined, the Memory_Pool
* class used for mlock'ed memory will use OS calls to set page
* permissions so as to prohibit access to pages on the free list, then
* enable read/write access when the page is set to be used. This will
* turn (some) use after free bugs into a crash.
*
* The additional syscalls have a substantial performance impact, which
* is why this option is not enabled by default.
*/
#if defined(BOTAN_HAS_VALGRIND) || defined(BOTAN_ENABLE_DEBUG_ASSERTS)
   #define BOTAN_MEM_POOL_USE_MMU_PROTECTIONS
#endif

/*
* If enabled uses memset via volatile function pointer to zero memory,
* otherwise does a byte at a time write via a volatile pointer.
*/
#define BOTAN_USE_VOLATILE_MEMSET_FOR_ZERO 1

/*
* Normally blinding is performed by choosing a random starting point (plus
* its inverse, of a form appropriate to the algorithm being blinded), and
* then choosing new blinding operands by successive squaring of both
* values. This is much faster than computing a new starting point but
* introduces some possible corelation
*
* To avoid possible leakage problems in long-running processes, the blinder
* periodically reinitializes the sequence. This value specifies how often
* a new sequence should be started.
*/
#define BOTAN_BLINDING_REINIT_INTERVAL 64

/*
* Userspace RNGs like HMAC_DRBG will reseed after a specified number
* of outputs are generated. Set to zero to disable automatic reseeding.
*/
#define BOTAN_RNG_DEFAULT_RESEED_INTERVAL 1024
#define BOTAN_RNG_RESEED_POLL_BITS 256

#define BOTAN_RNG_AUTO_RESEED_TIMEOUT std::chrono::milliseconds(10)
#define BOTAN_RNG_RESEED_DEFAULT_TIMEOUT std::chrono::milliseconds(50)

/*
* Specifies (in order) the list of entropy sources that will be used
* to seed an in-memory RNG.
*/
#define BOTAN_ENTROPY_DEFAULT_SOURCES \
   { "rdseed", "hwrng", "p9_darn", "getentropy", "dev_random", \
     "system_rng", "proc_walk", "system_stats" }

/* Multiplier on a block cipher's native parallelism */
#define BOTAN_BLOCK_CIPHER_PAR_MULT 4

/*
* These control the RNG used by the system RNG interface
*/
#define BOTAN_SYSTEM_RNG_DEVICE "/dev/urandom"
#define BOTAN_SYSTEM_RNG_POLL_DEVICES { "/dev/urandom", "/dev/random" }

/*
* This directory will be monitored by ProcWalking_EntropySource and
* the contents provided as entropy inputs to the RNG. May also be
* usefully set to something like "/sys", depending on the system being
* deployed to. Set to an empty string to disable.
*/
#define BOTAN_ENTROPY_PROC_FS_PATH "/proc"

/*
* These paramaters control how many bytes to read from the system
* PRNG, and how long to block if applicable. The timeout only applies
* to reading /dev/urandom and company.
*/
#define BOTAN_SYSTEM_RNG_POLL_REQUEST 64
#define BOTAN_SYSTEM_RNG_POLL_TIMEOUT_MS 20

/*
* When a PBKDF is self-tuning parameters, it will attempt to take about this
* amount of time to self-benchmark.
*/
#define BOTAN_PBKDF_TUNING_TIME std::chrono::milliseconds(10)

/*
* If no way of dynamically determining the cache line size for the
* system exists, this value is used as the default. Used by the side
* channel countermeasures rather than for alignment purposes, so it is
* better to be on the smaller side if the exact value cannot be
* determined. Typically 32 or 64 bytes on modern CPUs.
*/
#if !defined(BOTAN_TARGET_CPU_DEFAULT_CACHE_LINE_SIZE)
  #define BOTAN_TARGET_CPU_DEFAULT_CACHE_LINE_SIZE 32
#endif

/**
* Controls how AutoSeeded_RNG is instantiated
*/
#if !defined(BOTAN_AUTO_RNG_HMAC)

  #if defined(BOTAN_HAS_SHA2_64)
    #define BOTAN_AUTO_RNG_HMAC "HMAC(SHA-384)"
  #elif defined(BOTAN_HAS_SHA2_32)
    #define BOTAN_AUTO_RNG_HMAC "HMAC(SHA-256)"
  #elif defined(BOTAN_HAS_SHA3)
    #define BOTAN_AUTO_RNG_HMAC "HMAC(SHA-3(256))"
  #elif defined(BOTAN_HAS_SHA1)
    #define BOTAN_AUTO_RNG_HMAC "HMAC(SHA-1)"
  #endif
  /* Otherwise, no hash found: leave BOTAN_AUTO_RNG_HMAC undefined */

#endif

/* Check for a common build problem */

#if defined(BOTAN_TARGET_ARCH_IS_X86_64) && ((defined(_MSC_VER) && !defined(_WIN64)) || \
                                             (defined(__clang__) && !defined(__x86_64__)) || \
                                             (defined(__GNUG__) && !defined(__x86_64__)))
    #error "Trying to compile Botan configured as x86_64 with non-x86_64 compiler."
#endif

#if defined(BOTAN_TARGET_ARCH_IS_X86_32) && ((defined(_MSC_VER) && defined(_WIN64)) || \
                                             (defined(__clang__) && !defined(__i386__)) || \
                                             (defined(__GNUG__) && !defined(__i386__)))

    #error "Trying to compile Botan configured as x86_32 with non-x86_32 compiler."
#endif

/* Should we use GCC-style inline assembler? */
#if defined(BOTAN_BUILD_COMPILER_IS_GCC) || \
   defined(BOTAN_BUILD_COMPILER_IS_CLANG) || \
   defined(BOTAN_BUILD_COMPILER_IS_XLC) || \
   defined(BOTAN_BUILD_COMPILER_IS_SUN_STUDIO)

  #define BOTAN_USE_GCC_INLINE_ASM
#endif

/**
* Used to annotate API exports which are public and supported.
* These APIs will not be broken/removed unless strictly required for
* functionality or security, and only in new major versions.
* @param maj The major version this public API was released in
* @param min The minor version this public API was released in
*/
#define BOTAN_PUBLIC_API(maj,min) BOTAN_DLL

/**
* Used to annotate API exports which are public, but are now deprecated
* and which will be removed in a future major release.
*/
#define BOTAN_DEPRECATED_API(msg) BOTAN_DLL BOTAN_DEPRECATED(msg)

/**
* Used to annotate API exports which are public and can be used by
* applications if needed, but which are intentionally not documented,
* and which may change incompatibly in a future major version.
*/
#define BOTAN_UNSTABLE_API BOTAN_DLL

/**
* Used to annotate API exports which are exported but only for the
* purposes of testing. They should not be used by applications and
* may be removed or changed without notice.
*/
#define BOTAN_TEST_API BOTAN_DLL

/*
* Define BOTAN_GCC_VERSION
*/
#if defined(__GNUC__) && !defined(__clang__)
  #define BOTAN_GCC_VERSION (__GNUC__ * 100 + __GNUC_MINOR__ * 10 + __GNUC_PATCHLEVEL__)
#else
  #define BOTAN_GCC_VERSION 0
#endif

/*
* Define BOTAN_CLANG_VERSION
*/
#if defined(__clang__)
  #define BOTAN_CLANG_VERSION (__clang_major__ * 10 + __clang_minor__)
#else
  #define BOTAN_CLANG_VERSION 0
#endif

/*
* Define BOTAN_FUNC_ISA
*/
#if (defined(__GNUC__) && !defined(__clang__)) || (BOTAN_CLANG_VERSION > 38)
  #define BOTAN_FUNC_ISA(isa) __attribute__ ((target(isa)))
#else
  #define BOTAN_FUNC_ISA(isa)
#endif

/*
* Define BOTAN_WARN_UNUSED_RESULT
*/
#if defined(__GNUC__) || defined(__clang__)
  #define BOTAN_WARN_UNUSED_RESULT __attribute__ ((warn_unused_result))
#else
  #define BOTAN_WARN_UNUSED_RESULT
#endif

/*
* Define BOTAN_MALLOC_FN
*/
#if defined(__ibmxl__)
  /* XLC pretends to be both Clang and GCC, but is neither */
  #define BOTAN_MALLOC_FN __attribute__ ((malloc))
#elif defined(__GNUC__)
  #define BOTAN_MALLOC_FN __attribute__ ((malloc, alloc_size(1,2)))
#elif defined(_MSC_VER)
  #define BOTAN_MALLOC_FN __declspec(restrict)
#else
  #define BOTAN_MALLOC_FN
#endif

/*
* Define BOTAN_DEPRECATED
*/
#if !defined(BOTAN_NO_DEPRECATED_WARNINGS) && !defined(BOTAN_IS_BEING_BUILT) && !defined(BOTAN_AMALGAMATION_H_)

  #if defined(__clang__)
    #define BOTAN_DEPRECATED(msg) __attribute__ ((deprecated(msg)))
    #define BOTAN_DEPRECATED_HEADER(hdr) _Pragma("message \"this header is deprecated\"")
    #define BOTAN_FUTURE_INTERNAL_HEADER(hdr) _Pragma("message \"this header will be made internal in the future\"")

  #elif defined(_MSC_VER)
    #define BOTAN_DEPRECATED(msg) __declspec(deprecated(msg))
    #define BOTAN_DEPRECATED_HEADER(hdr) __pragma(message("this header is deprecated"))
    #define BOTAN_FUTURE_INTERNAL_HEADER(hdr) __pragma(message("this header will be made internal in the future"))

  #elif defined(__GNUC__)
    /* msg supported since GCC 4.5, earliest we support is 4.8 */
    #define BOTAN_DEPRECATED(msg) __attribute__ ((deprecated(msg)))
    #define BOTAN_DEPRECATED_HEADER(hdr) _Pragma("GCC warning \"this header is deprecated\"")
    #define BOTAN_FUTURE_INTERNAL_HEADER(hdr) _Pragma("GCC warning \"this header will be made internal in the future\"")
  #endif

#endif

#if !defined(BOTAN_DEPRECATED)
  #define BOTAN_DEPRECATED(msg)
#endif

#if !defined(BOTAN_DEPRECATED_HEADER)
  #define BOTAN_DEPRECATED_HEADER(hdr)
#endif

#if !defined(BOTAN_FUTURE_INTERNAL_HEADER)
  #define BOTAN_FUTURE_INTERNAL_HEADER(hdr)
#endif

/*
* Define BOTAN_NORETURN
*/
#if !defined(BOTAN_NORETURN)

  #if defined (__clang__) || defined (__GNUC__)
    #define BOTAN_NORETURN __attribute__ ((__noreturn__))

  #elif defined (_MSC_VER)
    #define BOTAN_NORETURN __declspec(noreturn)

  #else
    #define BOTAN_NORETURN
  #endif

#endif

/*
* Define BOTAN_THREAD_LOCAL
*/
#if !defined(BOTAN_THREAD_LOCAL)

  #if defined(BOTAN_TARGET_OS_HAS_THREADS) && defined(BOTAN_TARGET_OS_HAS_THREAD_LOCAL)
    #define BOTAN_THREAD_LOCAL thread_local
  #else
    #define BOTAN_THREAD_LOCAL /**/
  #endif

#endif

/*
* Define BOTAN_IF_CONSTEXPR
*/
#if !defined(BOTAN_IF_CONSTEXPR)
   #if __cplusplus >= 201703
      #define BOTAN_IF_CONSTEXPR if constexpr
   #else
      #define BOTAN_IF_CONSTEXPR if
   #endif
#endif

/*
* Define BOTAN_PARALLEL_FOR
*/
#if !defined(BOTAN_PARALLEL_FOR)

#if defined(BOTAN_TARGET_HAS_OPENMP)
  #define BOTAN_PARALLEL_FOR _Pragma("omp parallel for") for
#else
  #define BOTAN_PARALLEL_FOR for
#endif

#endif

/*
* Define BOTAN_FORCE_INLINE
*/
#if !defined(BOTAN_FORCE_INLINE)

  #if defined (__clang__) || defined (__GNUC__)
    #define BOTAN_FORCE_INLINE __attribute__ ((__always_inline__)) inline

  #elif defined (_MSC_VER)
    #define BOTAN_FORCE_INLINE __forceinline

  #else
    #define BOTAN_FORCE_INLINE inline
  #endif

#endif

/*
* Define BOTAN_PARALLEL_SIMD_FOR
*/
#if !defined(BOTAN_PARALLEL_SIMD_FOR)

#if defined(BOTAN_TARGET_HAS_OPENMP)
  #define BOTAN_PARALLEL_SIMD_FOR _Pragma("omp simd") for
#elif defined(BOTAN_BUILD_COMPILER_IS_GCC) && (BOTAN_GCC_VERSION >= 490)
  #define BOTAN_PARALLEL_SIMD_FOR _Pragma("GCC ivdep") for
#else
  #define BOTAN_PARALLEL_SIMD_FOR for
#endif

#endif

namespace Botan {

/**
* Called when an assertion fails
* Throws an Exception object
*/
BOTAN_NORETURN void BOTAN_PUBLIC_API(2,0)
   assertion_failure(const char* expr_str,
                     const char* assertion_made,
                     const char* func,
                     const char* file,
                     int line);

/**
* Called when an invalid argument is used
* Throws Invalid_Argument
*/
BOTAN_NORETURN void BOTAN_UNSTABLE_API throw_invalid_argument(const char* message,
                                                              const char* func,
                                                              const char* file);


#define BOTAN_ARG_CHECK(expr, msg)                                      \
   do { if(!(expr)) Botan::throw_invalid_argument(msg, __func__, __FILE__); } while(0)

/**
* Called when an invalid state is encountered
* Throws Invalid_State
*/
BOTAN_NORETURN void BOTAN_UNSTABLE_API throw_invalid_state(const char* message,
                                                           const char* func,
                                                           const char* file);


#define BOTAN_STATE_CHECK(expr)                                     \
   do { if(!(expr)) Botan::throw_invalid_state(#expr, __func__, __FILE__); } while(0)

/**
* Make an assertion
*/
#define BOTAN_ASSERT(expr, assertion_made)                \
   do {                                                   \
      if(!(expr))                                         \
         Botan::assertion_failure(#expr,                  \
                                  assertion_made,         \
                                  __func__,               \
                                  __FILE__,               \
                                  __LINE__);              \
   } while(0)

/**
* Make an assertion
*/
#define BOTAN_ASSERT_NOMSG(expr)                          \
   do {                                                   \
      if(!(expr))                                         \
         Botan::assertion_failure(#expr,                  \
                                  "",                     \
                                  __func__,               \
                                  __FILE__,               \
                                  __LINE__);              \
   } while(0)

/**
* Assert that value1 == value2
*/
#define BOTAN_ASSERT_EQUAL(expr1, expr2, assertion_made)   \
   do {                                                    \
     if((expr1) != (expr2))                                \
       Botan::assertion_failure(#expr1 " == " #expr2,      \
                                assertion_made,            \
                                __func__,                  \
                                __FILE__,                  \
                                __LINE__);                 \
   } while(0)

/**
* Assert that expr1 (if true) implies expr2 is also true
*/
#define BOTAN_ASSERT_IMPLICATION(expr1, expr2, msg)        \
   do {                                                    \
     if((expr1) && !(expr2))                               \
       Botan::assertion_failure(#expr1 " implies " #expr2, \
                                msg,                       \
                                __func__,                  \
                                __FILE__,                  \
                                __LINE__);                 \
   } while(0)

/**
* Assert that a pointer is not null
*/
#define BOTAN_ASSERT_NONNULL(ptr)                          \
   do {                                                    \
     if((ptr) == nullptr)                                  \
         Botan::assertion_failure(#ptr " is not null",     \
                                  "",                      \
                                  __func__,                \
                                  __FILE__,                \
                                  __LINE__);               \
   } while(0)

#if defined(BOTAN_ENABLE_DEBUG_ASSERTS)

#define BOTAN_DEBUG_ASSERT(expr) BOTAN_ASSERT_NOMSG(expr)

#else

#define BOTAN_DEBUG_ASSERT(expr) do {} while(0)

#endif

/**
* Mark variable as unused. Takes between 1 and 9 arguments and marks all as unused,
* e.g. BOTAN_UNUSED(a); or BOTAN_UNUSED(x, y, z);
*/
#define _BOTAN_UNUSED_IMPL1(a)                         static_cast<void>(a)
#define _BOTAN_UNUSED_IMPL2(a, b)                      static_cast<void>(a); _BOTAN_UNUSED_IMPL1(b)
#define _BOTAN_UNUSED_IMPL3(a, b, c)                   static_cast<void>(a); _BOTAN_UNUSED_IMPL2(b, c)
#define _BOTAN_UNUSED_IMPL4(a, b, c, d)                static_cast<void>(a); _BOTAN_UNUSED_IMPL3(b, c, d)
#define _BOTAN_UNUSED_IMPL5(a, b, c, d, e)             static_cast<void>(a); _BOTAN_UNUSED_IMPL4(b, c, d, e)
#define _BOTAN_UNUSED_IMPL6(a, b, c, d, e, f)          static_cast<void>(a); _BOTAN_UNUSED_IMPL5(b, c, d, e, f)
#define _BOTAN_UNUSED_IMPL7(a, b, c, d, e, f, g)       static_cast<void>(a); _BOTAN_UNUSED_IMPL6(b, c, d, e, f, g)
#define _BOTAN_UNUSED_IMPL8(a, b, c, d, e, f, g, h)    static_cast<void>(a); _BOTAN_UNUSED_IMPL7(b, c, d, e, f, g, h)
#define _BOTAN_UNUSED_IMPL9(a, b, c, d, e, f, g, h, i) static_cast<void>(a); _BOTAN_UNUSED_IMPL8(b, c, d, e, f, g, h, i)
#define _BOTAN_UNUSED_GET_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, IMPL_NAME, ...) IMPL_NAME

#define BOTAN_UNUSED(...) _BOTAN_UNUSED_GET_IMPL(__VA_ARGS__,                      \
                                                 _BOTAN_UNUSED_IMPL9,              \
                                                 _BOTAN_UNUSED_IMPL8,              \
                                                 _BOTAN_UNUSED_IMPL7,              \
                                                 _BOTAN_UNUSED_IMPL6,              \
                                                 _BOTAN_UNUSED_IMPL5,              \
                                                 _BOTAN_UNUSED_IMPL4,              \
                                                 _BOTAN_UNUSED_IMPL3,              \
                                                 _BOTAN_UNUSED_IMPL2,              \
                                                 _BOTAN_UNUSED_IMPL1,              \
                                                 unused dummy rest value           \
                          ) /* we got an one of _BOTAN_UNUSED_IMPL*, now call it */ (__VA_ARGS__)

}

namespace Botan {

/**
* @mainpage Botan Crypto Library API Reference
*
* <dl>
* <dt>Abstract Base Classes<dd>
*        BlockCipher, HashFunction, KDF, MessageAuthenticationCode, RandomNumberGenerator,
*        StreamCipher, SymmetricAlgorithm, AEAD_Mode, Cipher_Mode
* <dt>Public Key Interface Classes<dd>
*        PK_Key_Agreement, PK_Signer, PK_Verifier, PK_Encryptor, PK_Decryptor
* <dt>Authenticated Encryption Modes<dd>
*        @ref CCM_Mode "CCM", @ref ChaCha20Poly1305_Mode "ChaCha20Poly1305", @ref EAX_Mode "EAX",
*        @ref GCM_Mode "GCM", @ref OCB_Mode "OCB", @ref SIV_Mode "SIV"
* <dt>Block Ciphers<dd>
*        @ref aria.h "ARIA", @ref aes.h "AES", @ref Blowfish, @ref camellia.h "Camellia", @ref Cascade_Cipher "Cascade",
*        @ref CAST_128 "CAST-128", @ref CAST_128 "CAST-256", DES, @ref DESX "DES-X", @ref TripleDES "3DES",
*        @ref GOST_28147_89 "GOST 28147-89", IDEA, KASUMI, Lion, MISTY1, Noekeon, SEED, Serpent, SHACAL2, SM4,
*        @ref Threefish_512 "Threefish", Twofish, XTEA
* <dt>Stream Ciphers<dd>
*        ChaCha, @ref CTR_BE "CTR", OFB, RC4, Salsa20
* <dt>Hash Functions<dd>
*        BLAKE2b, @ref GOST_34_11 "GOST 34.11", @ref Keccak_1600 "Keccak", MD4, MD5, @ref RIPEMD_160 "RIPEMD-160",
*        @ref SHA_160 "SHA-1", @ref SHA_224 "SHA-224", @ref SHA_256 "SHA-256", @ref SHA_384 "SHA-384",
*        @ref SHA_512 "SHA-512", @ref Skein_512 "Skein-512", SM3, Streebog, Tiger, Whirlpool
* <dt>Non-Cryptographic Checksums<dd>
*        Adler32, CRC24, CRC32
* <dt>Message Authentication Codes<dd>
*        @ref CBC_MAC "CBC-MAC", CMAC, HMAC, Poly1305, SipHash, ANSI_X919_MAC
* <dt>Random Number Generators<dd>
*        AutoSeeded_RNG, HMAC_DRBG, Processor_RNG, System_RNG
* <dt>Key Derivation<dd>
*        HKDF, @ref KDF1 "KDF1 (IEEE 1363)", @ref KDF1_18033 "KDF1 (ISO 18033-2)", @ref KDF2 "KDF2 (IEEE 1363)",
*        @ref sp800_108.h "SP800-108", @ref SP800_56C "SP800-56C", @ref PKCS5_PBKDF1 "PBKDF1 (PKCS#5),
*        @ref PKCS5_PBKDF2 "PBKDF2 (PKCS#5)"
* <dt>Password Hashing<dd>
*        @ref argon2.h "Argon2", @ref scrypt.h "scrypt", @ref bcrypt.h "bcrypt", @ref passhash9.h "passhash9"
* <dt>Public Key Cryptosystems<dd>
*        @ref dlies.h "DLIES", @ref ecies.h "ECIES", @ref elgamal.h "ElGamal"
*        @ref rsa.h "RSA", @ref newhope.h "NewHope", @ref mceliece.h "McEliece" and @ref mceies.h "MCEIES",
*        @ref sm2.h "SM2"
* <dt>Public Key Signature Schemes<dd>
*        @ref dsa.h "DSA", @ref ecdsa.h "ECDSA", @ref ecgdsa.h "ECGDSA", @ref eckcdsa.h "ECKCDSA",
*        @ref gost_3410.h "GOST 34.10-2001", @ref sm2.h "SM2", @ref xmss.h "XMSS"
* <dt>Key Agreement<dd>
*        @ref dh.h "DH", @ref ecdh.h "ECDH"
* <dt>Compression<dd>
*        @ref bzip2.h "bzip2", @ref lzma.h "lzma", @ref zlib.h "zlib"
* <dt>TLS<dd>
*        TLS::Client, TLS::Server, TLS::Policy, TLS::Protocol_Version, TLS::Callbacks, TLS::Ciphersuite,
*        TLS::Session, TLS::Session_Manager, Credentials_Manager
* <dt>X.509<dd>
*        X509_Certificate, X509_CRL, X509_CA, Certificate_Extension, PKCS10_Request, X509_Cert_Options,
*        Certificate_Store, Certificate_Store_In_SQL, Certificate_Store_In_SQLite
* </dl>
*/

using std::uint8_t;
using std::uint16_t;
using std::uint32_t;
using std::uint64_t;
using std::int32_t;
using std::int64_t;
using std::size_t;

/*
* These typedefs are no longer used within the library headers
* or code. They are kept only for compatability with software
* written against older versions.
*/
using byte   = std::uint8_t;
using u16bit = std::uint16_t;
using u32bit = std::uint32_t;
using u64bit = std::uint64_t;
using s32bit = std::int32_t;

#if (BOTAN_MP_WORD_BITS == 32)
  typedef uint32_t word;
#elif (BOTAN_MP_WORD_BITS == 64)
  typedef uint64_t word;
#else
  #error BOTAN_MP_WORD_BITS must be 32 or 64
#endif

/*
* Should this assert fail on your system please contact the developers
* for assistance in porting.
*/
static_assert(sizeof(std::size_t) == 8 || sizeof(std::size_t) == 4,
              "This platform has an unexpected size for size_t");

}

namespace Botan {

/**
* Allocate a memory buffer by some method. This should only be used for
* primitive types (uint8_t, uint32_t, etc).
*
* @param elems the number of elements
* @param elem_size the size of each element
* @return pointer to allocated and zeroed memory, or throw std::bad_alloc on failure
*/
BOTAN_PUBLIC_API(2,3) BOTAN_MALLOC_FN void* allocate_memory(size_t elems, size_t elem_size);

/**
* Free a pointer returned by allocate_memory
* @param p the pointer returned by allocate_memory
* @param elems the number of elements, as passed to allocate_memory
* @param elem_size the size of each element, as passed to allocate_memory
*/
BOTAN_PUBLIC_API(2,3) void deallocate_memory(void* p, size_t elems, size_t elem_size);

/**
* Ensure the allocator is initialized
*/
void BOTAN_UNSTABLE_API initialize_allocator();

class Allocator_Initializer
   {
   public:
      Allocator_Initializer() { initialize_allocator(); }
   };

/**
* Scrub memory contents in a way that a compiler should not elide,
* using some system specific technique. Note that this function might
* not zero the memory (for example, in some hypothetical
* implementation it might combine the memory contents with the output
* of a system PRNG), but if you can detect any difference in behavior
* at runtime then the clearing is side-effecting and you can just
* use `clear_mem`.
*
* Use this function to scrub memory just before deallocating it, or on
* a stack buffer before returning from the function.
*
* @param ptr a pointer to memory to scrub
* @param n the number of bytes pointed to by ptr
*/
BOTAN_PUBLIC_API(2,0) void secure_scrub_memory(void* ptr, size_t n);

/**
* Memory comparison, input insensitive
* @param x a pointer to an array
* @param y a pointer to another array
* @param len the number of Ts in x and y
* @return 0xFF iff x[i] == y[i] forall i in [0...n) or 0x00 otherwise
*/
BOTAN_PUBLIC_API(2,9) uint8_t ct_compare_u8(const uint8_t x[],
                                            const uint8_t y[],
                                            size_t len);

/**
* Memory comparison, input insensitive
* @param x a pointer to an array
* @param y a pointer to another array
* @param len the number of Ts in x and y
* @return true iff x[i] == y[i] forall i in [0...n)
*/
inline bool constant_time_compare(const uint8_t x[],
                                  const uint8_t y[],
                                  size_t len)
   {
   return ct_compare_u8(x, y, len) == 0xFF;
   }

/**
* Zero out some bytes. Warning: use secure_scrub_memory instead if the
* memory is about to be freed or otherwise the compiler thinks it can
* elide the writes.
*
* @param ptr a pointer to memory to zero
* @param bytes the number of bytes to zero in ptr
*/
inline void clear_bytes(void* ptr, size_t bytes)
   {
   if(bytes > 0)
      {
      std::memset(ptr, 0, bytes);
      }
   }

/**
* Zero memory before use. This simply calls memset and should not be
* used in cases where the compiler cannot see the call as a
* side-effecting operation (for example, if calling clear_mem before
* deallocating memory, the compiler would be allowed to omit the call
* to memset entirely under the as-if rule.)
*
* @param ptr a pointer to an array of Ts to zero
* @param n the number of Ts pointed to by ptr
*/
template<typename T> inline void clear_mem(T* ptr, size_t n)
   {
   clear_bytes(ptr, sizeof(T)*n);
   }

// is_trivially_copyable is missing in g++ < 5.0
#if (BOTAN_GCC_VERSION > 0 && BOTAN_GCC_VERSION < 500)
#define BOTAN_IS_TRIVIALLY_COPYABLE(T) true
#else
#define BOTAN_IS_TRIVIALLY_COPYABLE(T) std::is_trivially_copyable<T>::value
#endif

/**
* Copy memory
* @param out the destination array
* @param in the source array
* @param n the number of elements of in/out
*/
template<typename T> inline void copy_mem(T* out, const T* in, size_t n)
   {
   static_assert(std::is_trivial<typename std::decay<T>::type>::value, "");
   BOTAN_ASSERT_IMPLICATION(n > 0, in != nullptr && out != nullptr,
                            "If n > 0 then args are not null");

   if(in != nullptr && out != nullptr && n > 0)
      {
      std::memmove(out, in, sizeof(T)*n);
      }
   }

template<typename T> inline void typecast_copy(uint8_t out[], T in[], size_t N)
   {
   static_assert(BOTAN_IS_TRIVIALLY_COPYABLE(T), "");
   std::memcpy(out, in, sizeof(T)*N);
   }

template<typename T> inline void typecast_copy(T out[], const uint8_t in[], size_t N)
   {
   static_assert(std::is_trivial<T>::value, "");
   std::memcpy(out, in, sizeof(T)*N);
   }

template<typename T> inline void typecast_copy(uint8_t out[], T in)
   {
   typecast_copy(out, &in, 1);
   }

template<typename T> inline void typecast_copy(T& out, const uint8_t in[])
   {
   static_assert(std::is_trivial<typename std::decay<T>::type>::value, "");
   typecast_copy(&out, in, 1);
   }

template <class To, class From> inline To typecast_copy(const From *src) noexcept
   {
   static_assert(BOTAN_IS_TRIVIALLY_COPYABLE(From) && std::is_trivial<To>::value, "");
   To dst;
   std::memcpy(&dst, src, sizeof(To));
   return dst;
   }

/**
* Set memory to a fixed value
* @param ptr a pointer to an array of bytes
* @param n the number of Ts pointed to by ptr
* @param val the value to set each byte to
*/
inline void set_mem(uint8_t* ptr, size_t n, uint8_t val)
   {
   if(n > 0)
      {
      std::memset(ptr, val, n);
      }
   }

inline const uint8_t* cast_char_ptr_to_uint8(const char* s)
   {
   return reinterpret_cast<const uint8_t*>(s);
   }

inline const char* cast_uint8_ptr_to_char(const uint8_t* b)
   {
   return reinterpret_cast<const char*>(b);
   }

inline uint8_t* cast_char_ptr_to_uint8(char* s)
   {
   return reinterpret_cast<uint8_t*>(s);
   }

inline char* cast_uint8_ptr_to_char(uint8_t* b)
   {
   return reinterpret_cast<char*>(b);
   }

/**
* Memory comparison, input insensitive
* @param p1 a pointer to an array
* @param p2 a pointer to another array
* @param n the number of Ts in p1 and p2
* @return true iff p1[i] == p2[i] forall i in [0...n)
*/
template<typename T> inline bool same_mem(const T* p1, const T* p2, size_t n)
   {
   volatile T difference = 0;

   for(size_t i = 0; i != n; ++i)
      difference |= (p1[i] ^ p2[i]);

   return difference == 0;
   }

template<typename T, typename Alloc>
size_t buffer_insert(std::vector<T, Alloc>& buf,
                     size_t buf_offset,
                     const T input[],
                     size_t input_length)
   {
   BOTAN_ASSERT_NOMSG(buf_offset <= buf.size());
   const size_t to_copy = std::min(input_length, buf.size() - buf_offset);
   if(to_copy > 0)
      {
      copy_mem(&buf[buf_offset], input, to_copy);
      }
   return to_copy;
   }

template<typename T, typename Alloc, typename Alloc2>
size_t buffer_insert(std::vector<T, Alloc>& buf,
                     size_t buf_offset,
                     const std::vector<T, Alloc2>& input)
   {
   BOTAN_ASSERT_NOMSG(buf_offset <= buf.size());
   const size_t to_copy = std::min(input.size(), buf.size() - buf_offset);
   if(to_copy > 0)
      {
      copy_mem(&buf[buf_offset], input.data(), to_copy);
      }
   return to_copy;
   }

/**
* XOR arrays. Postcondition out[i] = in[i] ^ out[i] forall i = 0...length
* @param out the input/output buffer
* @param in the read-only input buffer
* @param length the length of the buffers
*/
inline void xor_buf(uint8_t out[],
                    const uint8_t in[],
                    size_t length)
   {
   const size_t blocks = length - (length % 32);

   for(size_t i = 0; i != blocks; i += 32)
      {
      uint64_t x[4];
      uint64_t y[4];

      typecast_copy(x, out + i, 4);
      typecast_copy(y, in + i, 4);

      x[0] ^= y[0];
      x[1] ^= y[1];
      x[2] ^= y[2];
      x[3] ^= y[3];

      typecast_copy(out + i, x, 4);
      }

   for(size_t i = blocks; i != length; ++i)
      {
      out[i] ^= in[i];
      }
   }

/**
* XOR arrays. Postcondition out[i] = in[i] ^ in2[i] forall i = 0...length
* @param out the output buffer
* @param in the first input buffer
* @param in2 the second output buffer
* @param length the length of the three buffers
*/
inline void xor_buf(uint8_t out[],
                    const uint8_t in[],
                    const uint8_t in2[],
                    size_t length)
   {
   const size_t blocks = length - (length % 32);

   for(size_t i = 0; i != blocks; i += 32)
      {
      uint64_t x[4];
      uint64_t y[4];

      typecast_copy(x, in + i, 4);
      typecast_copy(y, in2 + i, 4);

      x[0] ^= y[0];
      x[1] ^= y[1];
      x[2] ^= y[2];
      x[3] ^= y[3];

      typecast_copy(out + i, x, 4);
      }

   for(size_t i = blocks; i != length; ++i)
      {
      out[i] = in[i] ^ in2[i];
      }
   }

template<typename Alloc, typename Alloc2>
void xor_buf(std::vector<uint8_t, Alloc>& out,
             const std::vector<uint8_t, Alloc2>& in,
             size_t n)
   {
   xor_buf(out.data(), in.data(), n);
   }

template<typename Alloc>
void xor_buf(std::vector<uint8_t, Alloc>& out,
             const uint8_t* in,
             size_t n)
   {
   xor_buf(out.data(), in, n);
   }

template<typename Alloc, typename Alloc2>
void xor_buf(std::vector<uint8_t, Alloc>& out,
             const uint8_t* in,
             const std::vector<uint8_t, Alloc2>& in2,
             size_t n)
   {
   xor_buf(out.data(), in, in2.data(), n);
   }

template<typename Alloc, typename Alloc2>
std::vector<uint8_t, Alloc>&
operator^=(std::vector<uint8_t, Alloc>& out,
           const std::vector<uint8_t, Alloc2>& in)
   {
   if(out.size() < in.size())
      out.resize(in.size());

   xor_buf(out.data(), in.data(), in.size());
   return out;
   }

}

namespace Botan {

template<typename T>
class secure_allocator
   {
   public:
      /*
      * Assert exists to prevent someone from doing something that will
      * probably crash anyway (like secure_vector<non_POD_t> where ~non_POD_t
      * deletes a member pointer which was zeroed before it ran).
      * MSVC in debug mode uses non-integral proxy types in container types
      * like std::vector, thus we disable the check there.
      */
#if !defined(_ITERATOR_DEBUG_LEVEL) || _ITERATOR_DEBUG_LEVEL == 0
      static_assert(std::is_integral<T>::value, "secure_allocator supports only integer types");
#endif

      typedef T          value_type;
      typedef std::size_t size_type;

      secure_allocator() noexcept = default;
      secure_allocator(const secure_allocator&) noexcept = default;
      secure_allocator& operator=(const secure_allocator&) noexcept = default;
      ~secure_allocator() noexcept = default;

      template<typename U>
      secure_allocator(const secure_allocator<U>&) noexcept {}

      T* allocate(std::size_t n)
         {
         return static_cast<T*>(allocate_memory(n, sizeof(T)));
         }

      void deallocate(T* p, std::size_t n)
         {
         deallocate_memory(p, n, sizeof(T));
         }
   };

template<typename T, typename U> inline bool
operator==(const secure_allocator<T>&, const secure_allocator<U>&)
   { return true; }

template<typename T, typename U> inline bool
operator!=(const secure_allocator<T>&, const secure_allocator<U>&)
   { return false; }

template<typename T> using secure_vector = std::vector<T, secure_allocator<T>>;
template<typename T> using secure_deque = std::deque<T, secure_allocator<T>>;

// For better compatibility with 1.10 API
template<typename T> using SecureVector = secure_vector<T>;

template<typename T>
std::vector<T> unlock(const secure_vector<T>& in)
   {
   return std::vector<T>(in.begin(), in.end());
   }

template<typename T, typename Alloc, typename Alloc2>
std::vector<T, Alloc>&
operator+=(std::vector<T, Alloc>& out,
           const std::vector<T, Alloc2>& in)
   {
   out.reserve(out.size() + in.size());
   out.insert(out.end(), in.begin(), in.end());
   return out;
   }

template<typename T, typename Alloc>
std::vector<T, Alloc>& operator+=(std::vector<T, Alloc>& out, T in)
   {
   out.push_back(in);
   return out;
   }

template<typename T, typename Alloc, typename L>
std::vector<T, Alloc>& operator+=(std::vector<T, Alloc>& out,
                                  const std::pair<const T*, L>& in)
   {
   out.reserve(out.size() + in.second);
   out.insert(out.end(), in.first, in.first + in.second);
   return out;
   }

template<typename T, typename Alloc, typename L>
std::vector<T, Alloc>& operator+=(std::vector<T, Alloc>& out,
                                  const std::pair<T*, L>& in)
   {
   out.reserve(out.size() + in.second);
   out.insert(out.end(), in.first, in.first + in.second);
   return out;
   }

/**
* Zeroise the values; length remains unchanged
* @param vec the vector to zeroise
*/
template<typename T, typename Alloc>
void zeroise(std::vector<T, Alloc>& vec)
   {
   clear_mem(vec.data(), vec.size());
   }

/**
* Zeroise the values then free the memory
* @param vec the vector to zeroise and free
*/
template<typename T, typename Alloc>
void zap(std::vector<T, Alloc>& vec)
   {
   zeroise(vec);
   vec.clear();
   vec.shrink_to_fit();
   }

}

namespace Botan {

/**
* Octet String
*/
class BOTAN_PUBLIC_API(2,0) OctetString final
   {
   public:
      /**
      * @return size of this octet string in bytes
      */
      size_t length() const { return m_data.size(); }
      size_t size() const { return m_data.size(); }

      /**
      * @return this object as a secure_vector<uint8_t>
      */
      secure_vector<uint8_t> bits_of() const { return m_data; }

      /**
      * @return start of this string
      */
      const uint8_t* begin() const { return m_data.data(); }

      /**
      * @return end of this string
      */
      const uint8_t* end() const   { return begin() + m_data.size(); }

      /**
      * @return this encoded as hex
      */
      std::string to_string() const;

      std::string BOTAN_DEPRECATED("Use OctetString::to_string") as_string() const
         {
         return this->to_string();
         }

      /**
      * XOR the contents of another octet string into this one
      * @param other octet string
      * @return reference to this
      */
      OctetString& operator^=(const OctetString& other);

      /**
      * Force to have odd parity
      */
      void set_odd_parity();

      /**
      * Create a new OctetString
      * @param str is a hex encoded string
      */
      explicit OctetString(const std::string& str = "");

      /**
      * Create a new random OctetString
      * @param rng is a random number generator
      * @param len is the desired length in bytes
      */
      OctetString(class RandomNumberGenerator& rng, size_t len);

      /**
      * Create a new OctetString
      * @param in is an array
      * @param len is the length of in in bytes
      */
      OctetString(const uint8_t in[], size_t len);

      /**
      * Create a new OctetString
      * @param in a bytestring
      */
      OctetString(const secure_vector<uint8_t>& in) : m_data(in) {}

      /**
      * Create a new OctetString
      * @param in a bytestring
      */
      OctetString(const std::vector<uint8_t>& in) : m_data(in.begin(), in.end()) {}

   private:
      secure_vector<uint8_t> m_data;
   };

/**
* Compare two strings
* @param x an octet string
* @param y an octet string
* @return if x is equal to y
*/
BOTAN_PUBLIC_API(2,0) bool operator==(const OctetString& x,
                          const OctetString& y);

/**
* Compare two strings
* @param x an octet string
* @param y an octet string
* @return if x is not equal to y
*/
BOTAN_PUBLIC_API(2,0) bool operator!=(const OctetString& x,
                          const OctetString& y);

/**
* Concatenate two strings
* @param x an octet string
* @param y an octet string
* @return x concatenated with y
*/
BOTAN_PUBLIC_API(2,0) OctetString operator+(const OctetString& x,
                                const OctetString& y);

/**
* XOR two strings
* @param x an octet string
* @param y an octet string
* @return x XORed with y
*/
BOTAN_PUBLIC_API(2,0) OctetString operator^(const OctetString& x,
                                const OctetString& y);


/**
* Alternate name for octet string showing intent to use as a key
*/
using SymmetricKey = OctetString;

/**
* Alternate name for octet string showing intent to use as an IV
*/
using InitializationVector = OctetString;

}

namespace Botan {

/**
* Represents the length requirements on an algorithm key
*/
class BOTAN_PUBLIC_API(2,0) Key_Length_Specification final
   {
   public:
      /**
      * Constructor for fixed length keys
      * @param keylen the supported key length
      */
      explicit Key_Length_Specification(size_t keylen) :
         m_min_keylen(keylen),
         m_max_keylen(keylen),
         m_keylen_mod(1)
         {
         }

      /**
      * Constructor for variable length keys
      * @param min_k the smallest supported key length
      * @param max_k the largest supported key length
      * @param k_mod the number of bytes the key must be a multiple of
      */
      Key_Length_Specification(size_t min_k,
                               size_t max_k,
                               size_t k_mod = 1) :
         m_min_keylen(min_k),
         m_max_keylen(max_k ? max_k : min_k),
         m_keylen_mod(k_mod)
         {
         }

      /**
      * @param length is a key length in bytes
      * @return true iff this length is a valid length for this algo
      */
      bool valid_keylength(size_t length) const
         {
         return ((length >= m_min_keylen) &&
                 (length <= m_max_keylen) &&
                 (length % m_keylen_mod == 0));
         }

      /**
      * @return minimum key length in bytes
      */
      size_t minimum_keylength() const
         {
         return m_min_keylen;
         }

      /**
      * @return maximum key length in bytes
      */
      size_t maximum_keylength() const
         {
         return m_max_keylen;
         }

      /**
      * @return key length multiple in bytes
      */
      size_t keylength_multiple() const
         {
         return m_keylen_mod;
         }

      /*
      * Multiplies all length requirements with the given factor
      * @param n the multiplication factor
      * @return a key length specification multiplied by the factor
      */
      Key_Length_Specification multiple(size_t n) const
         {
         return Key_Length_Specification(n * m_min_keylen,
                                         n * m_max_keylen,
                                         n * m_keylen_mod);
         }

   private:
      size_t m_min_keylen, m_max_keylen, m_keylen_mod;
   };

/**
* This class represents a symmetric algorithm object.
*/
class BOTAN_PUBLIC_API(2,0) SymmetricAlgorithm
   {
   public:
      virtual ~SymmetricAlgorithm() = default;

      /**
      * Reset the state.
      */
      virtual void clear() = 0;

      /**
      * @return object describing limits on key size
      */
      virtual Key_Length_Specification key_spec() const = 0;

      /**
      * @return maximum allowed key length
      */
      size_t maximum_keylength() const
         {
         return key_spec().maximum_keylength();
         }

      /**
      * @return minimum allowed key length
      */
      size_t minimum_keylength() const
         {
         return key_spec().minimum_keylength();
         }

      /**
      * Check whether a given key length is valid for this algorithm.
      * @param length the key length to be checked.
      * @return true if the key length is valid.
      */
      bool valid_keylength(size_t length) const
         {
         return key_spec().valid_keylength(length);
         }

      /**
      * Set the symmetric key of this object.
      * @param key the SymmetricKey to be set.
      */
      void set_key(const SymmetricKey& key)
         {
         set_key(key.begin(), key.length());
         }

      template<typename Alloc>
      void set_key(const std::vector<uint8_t, Alloc>& key)
         {
         set_key(key.data(), key.size());
         }

      /**
      * Set the symmetric key of this object.
      * @param key the to be set as a byte array.
      * @param length in bytes of key param
      */
      void set_key(const uint8_t key[], size_t length);

      /**
      * @return the algorithm name
      */
      virtual std::string name() const = 0;

   protected:
      void verify_key_set(bool cond) const
         {
         if(cond == false)
            throw_key_not_set_error();
         }

   private:
      void throw_key_not_set_error() const;

      /**
      * Run the key schedule
      * @param key the key
      * @param length of key
      */
      virtual void key_schedule(const uint8_t key[], size_t length) = 0;
   };

}

namespace Botan {

/**
* Different types of errors that might occur
*/
enum class ErrorType {
   /** Some unknown error */
   Unknown = 1,
   /** An error while calling a system interface */
   SystemError,
   /** An operation seems valid, but not supported by the current version */
   NotImplemented,
   /** Memory allocation failure */
   OutOfMemory,
   /** An internal error occurred */
   InternalError,
   /** An I/O error occurred */
   IoError,

   /** Invalid object state */
   InvalidObjectState = 100,
   /** A key was not set on an object when this is required */
   KeyNotSet,
   /** The application provided an argument which is invalid */
   InvalidArgument,
   /** A key with invalid length was provided */
   InvalidKeyLength,
   /** A nonce with invalid length was provided */
   InvalidNonceLength,
   /** An object type was requested but cannot be found */
   LookupError,
   /** Encoding a message or datum failed */
   EncodingFailure,
   /** Decoding a message or datum failed */
   DecodingFailure,
   /** A TLS error (error_code will be the alert type) */
   TLSError,
   /** An error during an HTTP operation */
   HttpError,
   /** A message with an invalid authentication tag was detected */
   InvalidTag,
   /** An error during Roughtime validation */
   RoughtimeError,

   /** An error when calling OpenSSL */
   OpenSSLError = 200,
   /** An error when interacting with CommonCrypto API */
   CommonCryptoError,
   /** An error when interacting with a PKCS11 device */
   Pkcs11Error,
   /** An error when interacting with a TPM device */
   TPMError,
   /** An error when interacting with a database */
   DatabaseError,

   /** An error when interacting with zlib */
   ZlibError = 300,
   /** An error when interacting with bzip2 */
   Bzip2Error,
   /** An error when interacting with lzma */
   LzmaError,

};

//! \brief Convert an ErrorType to string
std::string BOTAN_PUBLIC_API(2,11) to_string(ErrorType type);

/**
* Base class for all exceptions thrown by the library
*/
class BOTAN_PUBLIC_API(2,0) Exception : public std::exception
   {
   public:
      /**
      * Return a descriptive string which is hopefully comprehensible to
      * a developer. It will likely not be useful for an end user.
      *
      * The string has no particular format, and the content of exception
      * messages may change from release to release. Thus the main use of this
      * function is for logging or debugging.
      */
      const char* what() const noexcept override { return m_msg.c_str(); }

      /**
      * Return the "type" of error which occurred.
      */
      virtual ErrorType error_type() const noexcept { return Botan::ErrorType::Unknown; }

      /**
      * Return an error code associated with this exception, or otherwise 0.
      *
      * The domain of this error varies depending on the source, for example on
      * POSIX systems it might be errno, while on a Windows system it might be
      * the result of GetLastError or WSAGetLastError. For error_type() is
      * OpenSSLError, it will (if nonzero) be an OpenSSL error code from
      * ERR_get_error.
      */
      virtual int error_code() const noexcept { return 0; }

      /**
      * Avoid throwing base Exception, use a subclass
      */
      explicit Exception(const std::string& msg);

      /**
      * Avoid throwing base Exception, use a subclass
      */
      Exception(const char* prefix, const std::string& msg);

      /**
      * Avoid throwing base Exception, use a subclass
      */
      Exception(const std::string& msg, const std::exception& e);

   private:
      std::string m_msg;
   };

/**
* An invalid argument was provided to an API call.
*/
class BOTAN_PUBLIC_API(2,0) Invalid_Argument : public Exception
   {
   public:
      explicit Invalid_Argument(const std::string& msg);

      explicit Invalid_Argument(const std::string& msg, const std::string& where);

      Invalid_Argument(const std::string& msg, const std::exception& e);

      ErrorType error_type() const noexcept override { return ErrorType::InvalidArgument; }
   };

/**
* An invalid key length was used
*/
class BOTAN_PUBLIC_API(2,0) Invalid_Key_Length final : public Invalid_Argument
   {
   public:
      Invalid_Key_Length(const std::string& name, size_t length);
      ErrorType error_type() const noexcept override { return ErrorType::InvalidKeyLength; }
   };

/**
* An invalid nonce length was used
*/
class BOTAN_PUBLIC_API(2,0) Invalid_IV_Length final : public Invalid_Argument
   {
   public:
      Invalid_IV_Length(const std::string& mode, size_t bad_len);
      ErrorType error_type() const noexcept override { return ErrorType::InvalidNonceLength; }
   };

/**
* Invalid_Algorithm_Name Exception
*/
class BOTAN_PUBLIC_API(2,0) Invalid_Algorithm_Name final : public Invalid_Argument
   {
   public:
      explicit Invalid_Algorithm_Name(const std::string& name);
   };

/**
* Encoding_Error Exception
*
* This exception derives from Invalid_Argument for historical reasons, and it
* does not make any real sense for it to do so. In a future major release this
* exception type will derive directly from Exception instead.
*/
class BOTAN_PUBLIC_API(2,0) Encoding_Error final : public Invalid_Argument
   {
   public:
      explicit Encoding_Error(const std::string& name);

      ErrorType error_type() const noexcept override { return ErrorType::EncodingFailure; }
   };

/**
* A decoding error occurred.
*
* This exception derives from Invalid_Argument for historical reasons, and it
* does not make any real sense for it to do so. In a future major release this
* exception type will derive directly from Exception instead.
*/
class BOTAN_PUBLIC_API(2,0) Decoding_Error : public Invalid_Argument
   {
   public:
      explicit Decoding_Error(const std::string& name);

      Decoding_Error(const std::string& name, const char* exception_message);

      Decoding_Error(const std::string& msg, const std::exception& e);

      ErrorType error_type() const noexcept override { return ErrorType::DecodingFailure; }
   };

/**
* Invalid state was encountered. A request was made on an object while the
* object was in a state where the operation cannot be performed.
*/
class BOTAN_PUBLIC_API(2,0) Invalid_State : public Exception
   {
   public:
      explicit Invalid_State(const std::string& err) : Exception(err) {}

      ErrorType error_type() const noexcept override { return ErrorType::InvalidObjectState; }
   };

/**
* A PRNG was called on to produce output while still unseeded
*/
class BOTAN_PUBLIC_API(2,0) PRNG_Unseeded final : public Invalid_State
   {
   public:
      explicit PRNG_Unseeded(const std::string& algo);
   };

/**
* The key was not set on an object. This occurs with symmetric objects where
* an operation which requires the key is called prior to set_key being called.
*/
class BOTAN_PUBLIC_API(2,4) Key_Not_Set : public Invalid_State
   {
   public:
      explicit Key_Not_Set(const std::string& algo);

      ErrorType error_type() const noexcept override { return ErrorType::KeyNotSet; }
   };

/**
* A request was made for some kind of object which could not be located
*/
class BOTAN_PUBLIC_API(2,0) Lookup_Error : public Exception
   {
   public:
      explicit Lookup_Error(const std::string& err) : Exception(err) {}

      Lookup_Error(const std::string& type,
                   const std::string& algo,
                   const std::string& provider);

      ErrorType error_type() const noexcept override { return ErrorType::LookupError; }
   };

/**
* Algorithm_Not_Found Exception
*
* @warning This exception type will be removed in the future. Instead
* just catch Lookup_Error.
*/
class BOTAN_PUBLIC_API(2,0) Algorithm_Not_Found final : public Lookup_Error
   {
   public:
      explicit Algorithm_Not_Found(const std::string& name);
   };

/**
* Provider_Not_Found is thrown when a specific provider was requested
* but that provider is not available.
*
* @warning This exception type will be removed in the future. Instead
* just catch Lookup_Error.
*/
class BOTAN_PUBLIC_API(2,0) Provider_Not_Found final : public Lookup_Error
   {
   public:
      Provider_Not_Found(const std::string& algo, const std::string& provider);
   };

/**
* An AEAD or MAC check detected a message modification
*
* In versions before 2.10, Invalid_Authentication_Tag was named
* Integrity_Failure, it was renamed to make its usage more clear.
*/
class BOTAN_PUBLIC_API(2,0) Invalid_Authentication_Tag final : public Exception
   {
   public:
      explicit Invalid_Authentication_Tag(const std::string& msg);

      ErrorType error_type() const noexcept override { return ErrorType::InvalidTag; }
   };

/**
* For compatability with older versions
*/
typedef Invalid_Authentication_Tag Integrity_Failure;

/**
* An error occurred while operating on an IO stream
*/
class BOTAN_PUBLIC_API(2,0) Stream_IO_Error final : public Exception
   {
   public:
      explicit Stream_IO_Error(const std::string& err);

      ErrorType error_type() const noexcept override { return ErrorType::IoError; }
   };

/**
* System_Error
*
* This exception is thrown in the event of an error related to interacting
* with the operating system.
*
* This exception type also (optionally) captures an integer error code eg
* POSIX errno or Windows GetLastError.
*/
class BOTAN_PUBLIC_API(2,9) System_Error : public Exception
   {
   public:
      System_Error(const std::string& msg) : Exception(msg), m_error_code(0) {}

      System_Error(const std::string& msg, int err_code);

      ErrorType error_type() const noexcept override { return ErrorType::SystemError; }

      int error_code() const noexcept override { return m_error_code; }

   private:
      int m_error_code;
   };

/**
* An internal error occurred. If observed, please file a bug.
*/
class BOTAN_PUBLIC_API(2,0) Internal_Error : public Exception
   {
   public:
      explicit Internal_Error(const std::string& err);

      ErrorType error_type() const noexcept override { return ErrorType::InternalError; }
   };

/**
* Not Implemented Exception
*
* This is thrown in the situation where a requested operation is
* logically valid but is not implemented by this version of the library.
*/
class BOTAN_PUBLIC_API(2,0) Not_Implemented final : public Exception
   {
   public:
      explicit Not_Implemented(const std::string& err);

      ErrorType error_type() const noexcept override { return ErrorType::NotImplemented; }
   };

/*
   The following exception types are still in use for compatability reasons,
   but are deprecated and will be removed in a future major release.
   Instead catch the base class.
*/

/**
* An invalid OID string was used.
*
* This exception will be removed in a future major release.
*/
class BOTAN_PUBLIC_API(2,0) Invalid_OID final : public Decoding_Error
   {
   public:
      explicit Invalid_OID(const std::string& oid);
   };

/*
   The following exception types are deprecated, no longer used,
   and will be removed in a future major release
*/

/**
* Self Test Failure Exception
*
* This exception is no longer used. It will be removed in a future major release.
*/
class BOTAN_PUBLIC_API(2,0) Self_Test_Failure final : public Internal_Error
   {
   public:
      BOTAN_DEPRECATED("no longer used") explicit Self_Test_Failure(const std::string& err);
   };

/**
* No_Provider_Found Exception
*
* This exception is no longer used. It will be removed in a future major release.
*/
class BOTAN_PUBLIC_API(2,0) No_Provider_Found final : public Exception
   {
   public:
      BOTAN_DEPRECATED("no longer used") explicit No_Provider_Found(const std::string& name);
   };

/**
* Policy_Violation Exception
*
* This exception is no longer used. It will be removed in a future major release.
*/
class BOTAN_PUBLIC_API(2,0) Policy_Violation final : public Invalid_State
   {
   public:
      BOTAN_DEPRECATED("no longer used") explicit Policy_Violation(const std::string& err);
   };

/**
* Unsupported_Argument Exception
*
* An argument that is invalid because it is not supported by Botan.
* It might or might not be valid in another context like a standard.
*
* This exception is no longer used, instead Not_Implemented is thrown.
* It will be removed in a future major release.
*/
class BOTAN_PUBLIC_API(2,0) Unsupported_Argument final : public Invalid_Argument
   {
   public:
      BOTAN_DEPRECATED("no longer used") explicit Unsupported_Argument(const std::string& msg) : Invalid_Argument(msg) {}
   };

template<typename E, typename... Args>
inline void do_throw_error(const char* file, int line, const char* func, Args... args)
   {
   throw E(file, line, func, args...);
   }

}

namespace Botan {

/**
* The two possible directions for cipher filters, determining whether they
* actually perform encryption or decryption.
*/
enum Cipher_Dir : int { ENCRYPTION, DECRYPTION };

/**
* Interface for cipher modes
*/
class BOTAN_PUBLIC_API(2,0) Cipher_Mode : public SymmetricAlgorithm
   {
   public:
      /**
      * @return list of available providers for this algorithm, empty if not available
      * @param algo_spec algorithm name
      */
      static std::vector<std::string> providers(const std::string& algo_spec);

      /**
      * Create an AEAD mode
      * @param algo the algorithm to create
      * @param direction specify if this should be an encryption or decryption AEAD
      * @param provider optional specification for provider to use
      * @return an AEAD mode or a null pointer if not available
      */
      static std::unique_ptr<Cipher_Mode> create(const std::string& algo,
                                                 Cipher_Dir direction,
                                                 const std::string& provider = "");

      /**
      * Create an AEAD mode, or throw
      * @param algo the algorithm to create
      * @param direction specify if this should be an encryption or decryption AEAD
      * @param provider optional specification for provider to use
      * @return an AEAD mode, or throw an exception
      */
      static std::unique_ptr<Cipher_Mode> create_or_throw(const std::string& algo,
                                                          Cipher_Dir direction,
                                                          const std::string& provider = "");

      /*
      * Prepare for processing a message under the specified nonce
      */
      virtual void start_msg(const uint8_t nonce[], size_t nonce_len) = 0;

      /**
      * Begin processing a message.
      * @param nonce the per message nonce
      */
      template<typename Alloc>
      void start(const std::vector<uint8_t, Alloc>& nonce)
         {
         start_msg(nonce.data(), nonce.size());
         }

      /**
      * Begin processing a message.
      * @param nonce the per message nonce
      * @param nonce_len length of nonce
      */
      void start(const uint8_t nonce[], size_t nonce_len)
         {
         start_msg(nonce, nonce_len);
         }

      /**
      * Begin processing a message.
      */
      void start()
         {
         return start_msg(nullptr, 0);
         }

      /**
      * Process message blocks
      *
      * Input must be a multiple of update_granularity
      *
      * Processes msg in place and returns bytes written. Normally
      * this will be either msg_len (indicating the entire message was
      * processed) or for certain AEAD modes zero (indicating that the
      * mode requires the entire message be processed in one pass).
      *
      * @param msg the message to be processed
      * @param msg_len length of the message in bytes
      */
      virtual size_t process(uint8_t msg[], size_t msg_len) = 0;

      /**
      * Process some data. Input must be in size update_granularity() uint8_t blocks.
      * @param buffer in/out parameter which will possibly be resized
      * @param offset an offset into blocks to begin processing
      */
      void update(secure_vector<uint8_t>& buffer, size_t offset = 0)
         {
         BOTAN_ASSERT(buffer.size() >= offset, "Offset ok");
         uint8_t* buf = buffer.data() + offset;
         const size_t buf_size = buffer.size() - offset;

         const size_t written = process(buf, buf_size);
         buffer.resize(offset + written);
         }

      /**
      * Complete processing of a message.
      *
      * @param final_block in/out parameter which must be at least
      *        minimum_final_size() bytes, and will be set to any final output
      * @param offset an offset into final_block to begin processing
      */
      virtual void finish(secure_vector<uint8_t>& final_block, size_t offset = 0) = 0;

      /**
      * Returns the size of the output if this transform is used to process a
      * message with input_length bytes. In most cases the answer is precise.
      * If it is not possible to precise (namely for CBC decryption) instead a
      * lower bound is returned.
      */
      virtual size_t output_length(size_t input_length) const = 0;

      /**
      * @return size of required blocks to update
      */
      virtual size_t update_granularity() const = 0;

      /**
      * @return required minimium size to finalize() - may be any
      *         length larger than this.
      */
      virtual size_t minimum_final_size() const = 0;

      /**
      * @return the default size for a nonce
      */
      virtual size_t default_nonce_length() const = 0;

      /**
      * @return true iff nonce_len is a valid length for the nonce
      */
      virtual bool valid_nonce_length(size_t nonce_len) const = 0;

      /**
      * Resets just the message specific state and allows encrypting again under the existing key
      */
      virtual void reset() = 0;

      /**
      * @return true iff this mode provides authentication as well as
      * confidentiality.
      */
      virtual bool authenticated() const { return false; }

      /**
      * @return the size of the authentication tag used (in bytes)
      */
      virtual size_t tag_size() const { return 0; }

      /**
      * @return provider information about this implementation. Default is "base",
      * might also return "sse2", "avx2", "openssl", or some other arbitrary string.
      */
      virtual std::string provider() const { return "base"; }
   };

/**
* Get a cipher mode by name (eg "AES-128/CBC" or "Serpent/XTS")
* @param algo_spec cipher name
* @param direction ENCRYPTION or DECRYPTION
* @param provider provider implementation to choose
*/
inline Cipher_Mode* get_cipher_mode(const std::string& algo_spec,
                                    Cipher_Dir direction,
                                    const std::string& provider = "")
   {
   return Cipher_Mode::create(algo_spec, direction, provider).release();
   }

}

namespace Botan {

/**
* Interface for AEAD (Authenticated Encryption with Associated Data)
* modes. These modes provide both encryption and message
* authentication, and can authenticate additional per-message data
* which is not included in the ciphertext (for instance a sequence
* number).
*/
class BOTAN_PUBLIC_API(2,0) AEAD_Mode : public Cipher_Mode
   {
   public:
      /**
      * Create an AEAD mode
      * @param algo the algorithm to create
      * @param direction specify if this should be an encryption or decryption AEAD
      * @param provider optional specification for provider to use
      * @return an AEAD mode or a null pointer if not available
      */
      static std::unique_ptr<AEAD_Mode> create(const std::string& algo,
                                               Cipher_Dir direction,
                                               const std::string& provider = "");

      /**
      * Create an AEAD mode, or throw
      * @param algo the algorithm to create
      * @param direction specify if this should be an encryption or decryption AEAD
      * @param provider optional specification for provider to use
      * @return an AEAD mode, or throw an exception
      */
      static std::unique_ptr<AEAD_Mode> create_or_throw(const std::string& algo,
                                                        Cipher_Dir direction,
                                                        const std::string& provider = "");

      bool authenticated() const override { return true; }

      /**
      * Set associated data that is not included in the ciphertext but
      * that should be authenticated. Must be called after set_key and
      * before start.
      *
      * Unless reset by another call, the associated data is kept
      * between messages. Thus, if the AD does not change, calling
      * once (after set_key) is the optimum.
      *
      * @param ad the associated data
      * @param ad_len length of add in bytes
      */
      virtual void set_associated_data(const uint8_t ad[], size_t ad_len) = 0;

      /**
      * Set associated data that is not included in the ciphertext but
      * that should be authenticated. Must be called after set_key and
      * before start.
      *
      * Unless reset by another call, the associated data is kept
      * between messages. Thus, if the AD does not change, calling
      * once (after set_key) is the optimum.
      *
      * Some AEADs (namely SIV) support multiple AD inputs. For
      * all other modes only nominal AD input 0 is supported; all
      * other values of i will cause an exception.
      *
      * @param ad the associated data
      * @param ad_len length of add in bytes
      */
      virtual void set_associated_data_n(size_t i, const uint8_t ad[], size_t ad_len);

      /**
      * Returns the maximum supported number of associated data inputs which
      * can be provided to set_associated_data_n
      *
      * If returns 0, then no associated data is supported.
      */
      virtual size_t maximum_associated_data_inputs() const { return 1; }

      /**
      * Most AEADs require the key to be set prior to setting the AD
      * A few allow the AD to be set even before the cipher is keyed.
      * Such ciphers would return false from this function.
      */
      virtual bool associated_data_requires_key() const { return true; }

      /**
      * Set associated data that is not included in the ciphertext but
      * that should be authenticated. Must be called after set_key and
      * before start.
      *
      * See @ref set_associated_data().
      *
      * @param ad the associated data
      */
      template<typename Alloc>
      void set_associated_data_vec(const std::vector<uint8_t, Alloc>& ad)
         {
         set_associated_data(ad.data(), ad.size());
         }

      /**
      * Set associated data that is not included in the ciphertext but
      * that should be authenticated. Must be called after set_key and
      * before start.
      *
      * See @ref set_associated_data().
      *
      * @param ad the associated data
      */
      template<typename Alloc>
      void set_ad(const std::vector<uint8_t, Alloc>& ad)
         {
         set_associated_data(ad.data(), ad.size());
         }

      /**
      * @return default AEAD nonce size (a commonly supported value among AEAD
      * modes, and large enough that random collisions are unlikely)
      */
      size_t default_nonce_length() const override { return 12; }

      virtual ~AEAD_Mode() = default;
   };

/**
* Get an AEAD mode by name (eg "AES-128/GCM" or "Serpent/EAX")
* @param name AEAD name
* @param direction ENCRYPTION or DECRYPTION
*/
inline AEAD_Mode* get_aead(const std::string& name, Cipher_Dir direction)
   {
   return AEAD_Mode::create(name, direction, "").release();
   }

}

namespace Botan {

/**
* This class represents a block cipher object.
*/
class BOTAN_PUBLIC_API(2,0) BlockCipher : public SymmetricAlgorithm
   {
   public:

      /**
      * Create an instance based on a name
      * If provider is empty then best available is chosen.
      * @param algo_spec algorithm name
      * @param provider provider implementation to choose
      * @return a null pointer if the algo/provider combination cannot be found
      */
      static std::unique_ptr<BlockCipher>
         create(const std::string& algo_spec,
                const std::string& provider = "");

      /**
      * Create an instance based on a name, or throw if the
      * algo/provider combination cannot be found. If provider is
      * empty then best available is chosen.
      */
      static std::unique_ptr<BlockCipher>
         create_or_throw(const std::string& algo_spec,
                         const std::string& provider = "");

      /**
      * @return list of available providers for this algorithm, empty if not available
      * @param algo_spec algorithm name
      */
      static std::vector<std::string> providers(const std::string& algo_spec);

      /**
      * @return block size of this algorithm
      */
      virtual size_t block_size() const = 0;

      /**
      * @return native parallelism of this cipher in blocks
      */
      virtual size_t parallelism() const { return 1; }

      /**
      * @return prefererred parallelism of this cipher in bytes
      */
      size_t parallel_bytes() const
         {
         return parallelism() * block_size() * BOTAN_BLOCK_CIPHER_PAR_MULT;
         }

      /**
      * @return provider information about this implementation. Default is "base",
      * might also return "sse2", "avx2", "openssl", or some other arbitrary string.
      */
      virtual std::string provider() const { return "base"; }

      /**
      * Encrypt a block.
      * @param in The plaintext block to be encrypted as a byte array.
      * Must be of length block_size().
      * @param out The byte array designated to hold the encrypted block.
      * Must be of length block_size().
      */
      void encrypt(const uint8_t in[], uint8_t out[]) const
         { encrypt_n(in, out, 1); }

      /**
      * Decrypt a block.
      * @param in The ciphertext block to be decypted as a byte array.
      * Must be of length block_size().
      * @param out The byte array designated to hold the decrypted block.
      * Must be of length block_size().
      */
      void decrypt(const uint8_t in[], uint8_t out[]) const
         { decrypt_n(in, out, 1); }

      /**
      * Encrypt a block.
      * @param block the plaintext block to be encrypted
      * Must be of length block_size(). Will hold the result when the function
      * has finished.
      */
      void encrypt(uint8_t block[]) const { encrypt_n(block, block, 1); }

      /**
      * Decrypt a block.
      * @param block the ciphertext block to be decrypted
      * Must be of length block_size(). Will hold the result when the function
      * has finished.
      */
      void decrypt(uint8_t block[]) const { decrypt_n(block, block, 1); }

      /**
      * Encrypt one or more blocks
      * @param block the input/output buffer (multiple of block_size())
      */
      template<typename Alloc>
      void encrypt(std::vector<uint8_t, Alloc>& block) const
         {
         return encrypt_n(block.data(), block.data(), block.size() / block_size());
         }

      /**
      * Decrypt one or more blocks
      * @param block the input/output buffer (multiple of block_size())
      */
      template<typename Alloc>
      void decrypt(std::vector<uint8_t, Alloc>& block) const
         {
         return decrypt_n(block.data(), block.data(), block.size() / block_size());
         }

      /**
      * Encrypt one or more blocks
      * @param in the input buffer (multiple of block_size())
      * @param out the output buffer (same size as in)
      */
      template<typename Alloc, typename Alloc2>
      void encrypt(const std::vector<uint8_t, Alloc>& in,
                   std::vector<uint8_t, Alloc2>& out) const
         {
         return encrypt_n(in.data(), out.data(), in.size() / block_size());
         }

      /**
      * Decrypt one or more blocks
      * @param in the input buffer (multiple of block_size())
      * @param out the output buffer (same size as in)
      */
      template<typename Alloc, typename Alloc2>
      void decrypt(const std::vector<uint8_t, Alloc>& in,
                   std::vector<uint8_t, Alloc2>& out) const
         {
         return decrypt_n(in.data(), out.data(), in.size() / block_size());
         }

      /**
      * Encrypt one or more blocks
      * @param in the input buffer (multiple of block_size())
      * @param out the output buffer (same size as in)
      * @param blocks the number of blocks to process
      */
      virtual void encrypt_n(const uint8_t in[], uint8_t out[],
                             size_t blocks) const = 0;

      /**
      * Decrypt one or more blocks
      * @param in the input buffer (multiple of block_size())
      * @param out the output buffer (same size as in)
      * @param blocks the number of blocks to process
      */
      virtual void decrypt_n(const uint8_t in[], uint8_t out[],
                             size_t blocks) const = 0;

      virtual void encrypt_n_xex(uint8_t data[],
                                 const uint8_t mask[],
                                 size_t blocks) const
         {
         const size_t BS = block_size();
         xor_buf(data, mask, blocks * BS);
         encrypt_n(data, data, blocks);
         xor_buf(data, mask, blocks * BS);
         }

      virtual void decrypt_n_xex(uint8_t data[],
                                 const uint8_t mask[],
                                 size_t blocks) const
         {
         const size_t BS = block_size();
         xor_buf(data, mask, blocks * BS);
         decrypt_n(data, data, blocks);
         xor_buf(data, mask, blocks * BS);
         }

      /**
      * @return new object representing the same algorithm as *this
      */
      virtual BlockCipher* clone() const = 0;

      virtual ~BlockCipher() = default;
   };

/**
* Tweakable block ciphers allow setting a tweak which is a non-keyed
* value which affects the encryption/decryption operation.
*/
class BOTAN_PUBLIC_API(2,8) Tweakable_Block_Cipher : public BlockCipher
   {
   public:
      /**
      * Set the tweak value. This must be called after setting a key. The value
      * persists until either set_tweak, set_key, or clear is called.
      * Different algorithms support different tweak length(s). If called with
      * an unsupported length, Invalid_Argument will be thrown.
      */
      virtual void set_tweak(const uint8_t tweak[], size_t len) = 0;
   };

/**
* Represents a block cipher with a single fixed block size
*/
template<size_t BS, size_t KMIN, size_t KMAX = 0, size_t KMOD = 1, typename BaseClass = BlockCipher>
class Block_Cipher_Fixed_Params : public BaseClass
   {
   public:
      enum { BLOCK_SIZE = BS };
      size_t block_size() const final override { return BS; }

      // override to take advantage of compile time constant block size
      void encrypt_n_xex(uint8_t data[],
                         const uint8_t mask[],
                         size_t blocks) const final override
         {
         xor_buf(data, mask, blocks * BS);
         this->encrypt_n(data, data, blocks);
         xor_buf(data, mask, blocks * BS);
         }

      void decrypt_n_xex(uint8_t data[],
                         const uint8_t mask[],
                         size_t blocks) const final override
         {
         xor_buf(data, mask, blocks * BS);
         this->decrypt_n(data, data, blocks);
         xor_buf(data, mask, blocks * BS);
         }

      Key_Length_Specification key_spec() const final override
         {
         return Key_Length_Specification(KMIN, KMAX, KMOD);
         }
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(aes.h)

namespace Botan {

/**
* AES-128
*/
class BOTAN_PUBLIC_API(2,0) AES_128 final : public Block_Cipher_Fixed_Params<16, 16>
   {
   public:
      void encrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const override;
      void decrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const override;

      void clear() override;

      std::string provider() const override;
      std::string name() const override { return "AES-128"; }
      BlockCipher* clone() const override { return new AES_128; }
      size_t parallelism() const override;

   private:
      void key_schedule(const uint8_t key[], size_t length) override;

#if defined(BOTAN_HAS_AES_VPERM)
      void vperm_encrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const;
      void vperm_decrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const;
      void vperm_key_schedule(const uint8_t key[], size_t length);
#endif

#if defined(BOTAN_HAS_AES_NI)
      void aesni_key_schedule(const uint8_t key[], size_t length);
#endif

#if defined(BOTAN_HAS_AES_POWER8) || defined(BOTAN_HAS_AES_ARMV8) || defined(BOTAN_HAS_AES_NI)
      void hw_aes_encrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const;
      void hw_aes_decrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const;
#endif

      secure_vector<uint32_t> m_EK, m_DK;
   };

/**
* AES-192
*/
class BOTAN_PUBLIC_API(2,0) AES_192 final : public Block_Cipher_Fixed_Params<16, 24>
   {
   public:
      void encrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const override;
      void decrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const override;

      void clear() override;

      std::string provider() const override;
      std::string name() const override { return "AES-192"; }
      BlockCipher* clone() const override { return new AES_192; }
      size_t parallelism() const override;

   private:
#if defined(BOTAN_HAS_AES_VPERM)
      void vperm_encrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const;
      void vperm_decrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const;
      void vperm_key_schedule(const uint8_t key[], size_t length);
#endif

#if defined(BOTAN_HAS_AES_NI)
      void aesni_key_schedule(const uint8_t key[], size_t length);
#endif

#if defined(BOTAN_HAS_AES_POWER8) || defined(BOTAN_HAS_AES_ARMV8) || defined(BOTAN_HAS_AES_NI)
      void hw_aes_encrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const;
      void hw_aes_decrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const;
#endif

      void key_schedule(const uint8_t key[], size_t length) override;

      secure_vector<uint32_t> m_EK, m_DK;
   };

/**
* AES-256
*/
class BOTAN_PUBLIC_API(2,0) AES_256 final : public Block_Cipher_Fixed_Params<16, 32>
   {
   public:
      void encrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const override;
      void decrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const override;

      void clear() override;

      std::string provider() const override;

      std::string name() const override { return "AES-256"; }
      BlockCipher* clone() const override { return new AES_256; }
      size_t parallelism() const override;

   private:
#if defined(BOTAN_HAS_AES_VPERM)
      void vperm_encrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const;
      void vperm_decrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const;
      void vperm_key_schedule(const uint8_t key[], size_t length);
#endif

#if defined(BOTAN_HAS_AES_NI)
      void aesni_key_schedule(const uint8_t key[], size_t length);
#endif

#if defined(BOTAN_HAS_AES_POWER8) || defined(BOTAN_HAS_AES_ARMV8) || defined(BOTAN_HAS_AES_NI)
      void hw_aes_encrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const;
      void hw_aes_decrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const;
#endif

      void key_schedule(const uint8_t key[], size_t length) override;

      secure_vector<uint32_t> m_EK, m_DK;
   };

}

namespace Botan {

class BER_Decoder;
class DER_Encoder;

/**
* ASN.1 Type and Class Tags
* This will become an enum class in a future major release
*/
enum ASN1_Tag : uint32_t {
   UNIVERSAL        = 0x00,
   APPLICATION      = 0x40,
   CONTEXT_SPECIFIC = 0x80,

   CONSTRUCTED      = 0x20,

   PRIVATE          = CONSTRUCTED | CONTEXT_SPECIFIC,

   EOC              = 0x00,
   BOOLEAN          = 0x01,
   INTEGER          = 0x02,
   BIT_STRING       = 0x03,
   OCTET_STRING     = 0x04,
   NULL_TAG         = 0x05,
   OBJECT_ID        = 0x06,
   ENUMERATED       = 0x0A,
   SEQUENCE         = 0x10,
   SET              = 0x11,

   UTF8_STRING      = 0x0C,
   NUMERIC_STRING   = 0x12,
   PRINTABLE_STRING = 0x13,
   T61_STRING       = 0x14,
   IA5_STRING       = 0x16,
   VISIBLE_STRING   = 0x1A,
   UNIVERSAL_STRING = 0x1C,
   BMP_STRING       = 0x1E,

   UTC_TIME                = 0x17,
   GENERALIZED_TIME        = 0x18,
   UTC_OR_GENERALIZED_TIME = 0x19,

   NO_OBJECT        = 0xFF00,
   DIRECTORY_STRING = 0xFF01
};

std::string BOTAN_UNSTABLE_API asn1_tag_to_string(ASN1_Tag type);
std::string BOTAN_UNSTABLE_API asn1_class_to_string(ASN1_Tag type);

/**
* Basic ASN.1 Object Interface
*/
class BOTAN_PUBLIC_API(2,0) ASN1_Object
   {
   public:
      /**
      * Encode whatever this object is into to
      * @param to the DER_Encoder that will be written to
      */
      virtual void encode_into(DER_Encoder& to) const = 0;

      /**
      * Decode whatever this object is from from
      * @param from the BER_Decoder that will be read from
      */
      virtual void decode_from(BER_Decoder& from) = 0;

      /**
      * Return the encoding of this object. This is a convenience
      * method when just one object needs to be serialized. Use
      * DER_Encoder for complicated encodings.
      */
      std::vector<uint8_t> BER_encode() const;

      ASN1_Object() = default;
      ASN1_Object(const ASN1_Object&) = default;
      ASN1_Object & operator=(const ASN1_Object&) = default;
      virtual ~ASN1_Object() = default;
   };

/**
* BER Encoded Object
*/
class BOTAN_PUBLIC_API(2,0) BER_Object final
   {
   public:
      BER_Object() : type_tag(NO_OBJECT), class_tag(UNIVERSAL) {}

      BER_Object(const BER_Object& other) = default;

      BER_Object& operator=(const BER_Object& other) = default;

      BER_Object(BER_Object&& other) = default;

      BER_Object& operator=(BER_Object&& other) = default;

      bool is_set() const { return type_tag != NO_OBJECT; }

      ASN1_Tag tagging() const { return ASN1_Tag(type() | get_class()); }

      ASN1_Tag type() const { return type_tag; }
      ASN1_Tag get_class() const { return class_tag; }

      const uint8_t* bits() const { return value.data(); }

      size_t length() const { return value.size(); }

      void assert_is_a(ASN1_Tag type_tag, ASN1_Tag class_tag,
                       const std::string& descr = "object") const;

      bool is_a(ASN1_Tag type_tag, ASN1_Tag class_tag) const;

      bool is_a(int type_tag, ASN1_Tag class_tag) const;

   BOTAN_DEPRECATED_PUBLIC_MEMBER_VARIABLES:
      /*
      * The following member variables are public for historical reasons, but
      * will be made private in a future major release. Use the accessor
      * functions above.
      */
      ASN1_Tag type_tag, class_tag;
      secure_vector<uint8_t> value;

   private:

      friend class BER_Decoder;

      void set_tagging(ASN1_Tag type_tag, ASN1_Tag class_tag);

      uint8_t* mutable_bits(size_t length)
         {
         value.resize(length);
         return value.data();
         }
   };

/*
* ASN.1 Utility Functions
*/
class DataSource;

namespace ASN1 {

std::vector<uint8_t> put_in_sequence(const std::vector<uint8_t>& val);
std::vector<uint8_t> put_in_sequence(const uint8_t bits[], size_t len);
std::string to_string(const BER_Object& obj);

/**
* Heuristics tests; is this object possibly BER?
* @param src a data source that will be peeked at but not modified
*/
bool maybe_BER(DataSource& src);

}

/**
* General BER Decoding Error Exception
*/
class BOTAN_PUBLIC_API(2,0) BER_Decoding_Error : public Decoding_Error
   {
   public:
      explicit BER_Decoding_Error(const std::string&);
   };

/**
* Exception For Incorrect BER Taggings
*/
class BOTAN_PUBLIC_API(2,0) BER_Bad_Tag final : public BER_Decoding_Error
   {
   public:
      BER_Bad_Tag(const std::string& msg, ASN1_Tag tag);
      BER_Bad_Tag(const std::string& msg, ASN1_Tag tag1, ASN1_Tag tag2);
   };

/**
* This class represents ASN.1 object identifiers.
*/
class BOTAN_PUBLIC_API(2,0) OID final : public ASN1_Object
   {
   public:

      /**
      * Create an uninitialied OID object
      */
      explicit OID() {}

      /**
      * Construct an OID from a string.
      * @param str a string in the form "a.b.c" etc., where a,b,c are numbers
      */
      explicit OID(const std::string& str);

      /**
      * Initialize an OID from a sequence of integer values
      */
      explicit OID(std::initializer_list<uint32_t> init) : m_id(init) {}

      /**
      * Initialize an OID from a vector of integer values
      */
      explicit OID(std::vector<uint32_t>&& init) : m_id(init) {}

      /**
      * Construct an OID from a string.
      * @param str a string in the form "a.b.c" etc., where a,b,c are numbers
      *        or any known OID name (for example "RSA" or "X509v3.SubjectKeyIdentifier")
      */
      static OID from_string(const std::string& str);

      void encode_into(class DER_Encoder&) const override;
      void decode_from(class BER_Decoder&) override;

      /**
      * Find out whether this OID is empty
      * @return true is no OID value is set
      */
      bool empty() const { return m_id.empty(); }

      /**
      * Find out whether this OID has a value
      * @return true is this OID has a value
      */
      bool has_value() const { return (m_id.empty() == false); }

      /**
      * Get this OID as list (vector) of its components.
      * @return vector representing this OID
      */
      const std::vector<uint32_t>& get_components() const { return m_id; }

      const std::vector<uint32_t>& get_id() const { return get_components(); }

      /**
      * Get this OID as a string
      * @return string representing this OID
      */
      std::string BOTAN_DEPRECATED("Use OID::to_string") as_string() const
         {
         return this->to_string();
         }

      /**
      * Get this OID as a dotted-decimal string
      * @return string representing this OID
      */
      std::string to_string() const;

      /**
      * If there is a known name associated with this OID, return that.
      * Otherwise return the result of to_string
      */
      std::string to_formatted_string() const;

      /**
      * Compare two OIDs.
      * @return true if they are equal, false otherwise
      */
      bool operator==(const OID& other) const
         {
         return m_id == other.m_id;
         }

      /**
      * Reset this instance to an empty OID.
      */
      void BOTAN_DEPRECATED("Avoid mutation of OIDs") clear() { m_id.clear(); }

      /**
      * Add a component to this OID.
      * @param new_comp the new component to add to the end of this OID
      * @return reference to *this
      */
      BOTAN_DEPRECATED("Avoid mutation of OIDs") OID& operator+=(uint32_t new_comp)
         {
         m_id.push_back(new_comp);
         return (*this);
         }

   private:
      std::vector<uint32_t> m_id;
   };

/**
* Append another component onto the OID.
* @param oid the OID to add the new component to
* @param new_comp the new component to add
*/
OID BOTAN_PUBLIC_API(2,0) operator+(const OID& oid, uint32_t new_comp);

/**
* Compare two OIDs.
* @param a the first OID
* @param b the second OID
* @return true if a is not equal to b
*/
inline bool operator!=(const OID& a, const OID& b)
   {
   return !(a == b);
   }

/**
* Compare two OIDs.
* @param a the first OID
* @param b the second OID
* @return true if a is lexicographically smaller than b
*/
bool BOTAN_PUBLIC_API(2,0) operator<(const OID& a, const OID& b);

/**
* Time (GeneralizedTime/UniversalTime)
*/
class BOTAN_PUBLIC_API(2,0) ASN1_Time final : public ASN1_Object
   {
   public:
      /// DER encode a ASN1_Time
      void encode_into(DER_Encoder&) const override;

      // Decode a BER encoded ASN1_Time
      void decode_from(BER_Decoder&) override;

      /// Return an internal string representation of the time
      std::string to_string() const;

      /// Returns a human friendly string replesentation of no particular formatting
      std::string readable_string() const;

      /// Return if the time has been set somehow
      bool time_is_set() const;

      ///  Compare this time against another
      int32_t cmp(const ASN1_Time& other) const;

      /// Create an invalid ASN1_Time
      ASN1_Time() = default;

      /// Create a ASN1_Time from a time point
      explicit ASN1_Time(const std::chrono::system_clock::time_point& time);

      /// Create an ASN1_Time from string
      ASN1_Time(const std::string& t_spec, ASN1_Tag tag);

      /// Returns a STL timepoint object
      std::chrono::system_clock::time_point to_std_timepoint() const;

      /// Return time since epoch
      uint64_t time_since_epoch() const;

   private:
      void set_to(const std::string& t_spec, ASN1_Tag);
      bool passes_sanity_check() const;

      uint32_t m_year = 0;
      uint32_t m_month = 0;
      uint32_t m_day = 0;
      uint32_t m_hour = 0;
      uint32_t m_minute = 0;
      uint32_t m_second = 0;
      ASN1_Tag m_tag = NO_OBJECT;
   };

/*
* Comparison Operations
*/
bool BOTAN_PUBLIC_API(2,0) operator==(const ASN1_Time&, const ASN1_Time&);
bool BOTAN_PUBLIC_API(2,0) operator!=(const ASN1_Time&, const ASN1_Time&);
bool BOTAN_PUBLIC_API(2,0) operator<=(const ASN1_Time&, const ASN1_Time&);
bool BOTAN_PUBLIC_API(2,0) operator>=(const ASN1_Time&, const ASN1_Time&);
bool BOTAN_PUBLIC_API(2,0) operator<(const ASN1_Time&, const ASN1_Time&);
bool BOTAN_PUBLIC_API(2,0) operator>(const ASN1_Time&, const ASN1_Time&);

typedef ASN1_Time X509_Time;

/**
* ASN.1 string type
* This class normalizes all inputs to a UTF-8 std::string
*/
class BOTAN_PUBLIC_API(2,0) ASN1_String final : public ASN1_Object
   {
   public:
      void encode_into(class DER_Encoder&) const override;
      void decode_from(class BER_Decoder&) override;

      ASN1_Tag tagging() const { return m_tag; }

      const std::string& value() const { return m_utf8_str; }

      size_t size() const { return value().size(); }

      bool empty() const { return m_utf8_str.empty(); }

      std::string BOTAN_DEPRECATED("Use value() to get UTF-8 string instead")
         iso_8859() const;

      /**
      * Return true iff this is a tag for a known string type we can handle.
      * This ignores string types that are not supported, eg teletexString
      */
      static bool is_string_type(ASN1_Tag tag);

      bool operator==(const ASN1_String& other) const
         { return value() == other.value(); }

      explicit ASN1_String(const std::string& utf8 = "");
      ASN1_String(const std::string& utf8, ASN1_Tag tag);
   private:
      std::vector<uint8_t> m_data;
      std::string m_utf8_str;
      ASN1_Tag m_tag;
   };

/**
* Algorithm Identifier
*/
class BOTAN_PUBLIC_API(2,0) AlgorithmIdentifier final : public ASN1_Object
   {
   public:
      enum Encoding_Option { USE_NULL_PARAM, USE_EMPTY_PARAM };

      void encode_into(class DER_Encoder&) const override;
      void decode_from(class BER_Decoder&) override;

      AlgorithmIdentifier() = default;

      AlgorithmIdentifier(const OID& oid, Encoding_Option enc);
      AlgorithmIdentifier(const std::string& oid_name, Encoding_Option enc);

      AlgorithmIdentifier(const OID& oid, const std::vector<uint8_t>& params);
      AlgorithmIdentifier(const std::string& oid_name, const std::vector<uint8_t>& params);

      const OID& get_oid() const { return oid; }
      const std::vector<uint8_t>& get_parameters() const { return parameters; }

      bool parameters_are_null() const;
      bool parameters_are_empty() const { return parameters.empty(); }

      bool parameters_are_null_or_empty() const
         {
         return parameters_are_empty() || parameters_are_null();
         }

   BOTAN_DEPRECATED_PUBLIC_MEMBER_VARIABLES:
      /*
      * These values are public for historical reasons, but in a future release
      * they will be made private. Do not access them.
      */
      OID oid;
      std::vector<uint8_t> parameters;
   };

/*
* Comparison Operations
*/
bool BOTAN_PUBLIC_API(2,0) operator==(const AlgorithmIdentifier&,
                                      const AlgorithmIdentifier&);
bool BOTAN_PUBLIC_API(2,0) operator!=(const AlgorithmIdentifier&,
                                      const AlgorithmIdentifier&);

}

namespace Botan {

class BER_Decoder;

/**
* Format ASN.1 data and call a virtual to format
*/
class BOTAN_PUBLIC_API(2,4) ASN1_Formatter
   {
   public:
      virtual ~ASN1_Formatter() = default;

      /**
      * @param print_context_specific if true, try to parse nested context specific data.
      * @param max_depth do not recurse more than this many times. If zero, recursion
      *        is unbounded.
      */
      ASN1_Formatter(bool print_context_specific, size_t max_depth) :
         m_print_context_specific(print_context_specific),
         m_max_depth(max_depth)
         {}

      void print_to_stream(std::ostream& out,
                           const uint8_t in[],
                           size_t len) const;

      std::string print(const uint8_t in[], size_t len) const;

      template<typename Alloc>
      std::string print(const std::vector<uint8_t, Alloc>& vec) const
         {
         return print(vec.data(), vec.size());
         }

   protected:
      /**
      * This is called for each element
      */
      virtual std::string format(ASN1_Tag type_tag,
                                 ASN1_Tag class_tag,
                                 size_t level,
                                 size_t length,
                                 const std::string& value) const = 0;

      /**
      * This is called to format binary elements that we don't know how to
      * convert to a string The result will be passed as value to format; the
      * tags are included as a hint to aid decoding.
      */
      virtual std::string format_bin(ASN1_Tag type_tag,
                                     ASN1_Tag class_tag,
                                     const std::vector<uint8_t>& vec) const = 0;

   private:
      void decode(std::ostream& output,
                  BER_Decoder& decoder,
                  size_t level) const;

      const bool m_print_context_specific;
      const size_t m_max_depth;
   };

/**
* Format ASN.1 data into human readable output. The exact form of the output for
* any particular input is not guaranteed and may change from release to release.
*/
class BOTAN_PUBLIC_API(2,4) ASN1_Pretty_Printer final : public ASN1_Formatter
   {
   public:
      /**
      * @param print_limit strings larger than this are not printed
      * @param print_binary_limit binary strings larger than this are not printed
      * @param print_context_specific if true, try to parse nested context specific data.
      * @param initial_level the initial depth (0 or 1 are the only reasonable values)
      * @param value_column ASN.1 values are lined up at this column in output
      * @param max_depth do not recurse more than this many times. If zero, recursion
      *        is unbounded.
      */
      ASN1_Pretty_Printer(size_t print_limit = 4096,
                          size_t print_binary_limit = 2048,
                          bool print_context_specific = true,
                          size_t initial_level = 0,
                          size_t value_column = 60,
                          size_t max_depth = 64) :
         ASN1_Formatter(print_context_specific, max_depth),
         m_print_limit(print_limit),
         m_print_binary_limit(print_binary_limit),
         m_initial_level(initial_level),
         m_value_column(value_column)
         {}

   private:
      std::string format(ASN1_Tag type_tag,
                         ASN1_Tag class_tag,
                         size_t level,
                         size_t length,
                         const std::string& value) const override;

      std::string format_bin(ASN1_Tag type_tag,
                             ASN1_Tag class_tag,
                             const std::vector<uint8_t>& vec) const override;

      const size_t m_print_limit;
      const size_t m_print_binary_limit;
      const size_t m_initial_level;
      const size_t m_value_column;
   };

}

#if defined(BOTAN_TARGET_OS_HAS_THREADS)


namespace Botan {

template<typename T> using lock_guard_type = std::lock_guard<T>;
typedef std::mutex mutex_type;
typedef std::recursive_mutex recursive_mutex_type;

}

#else

// No threads

namespace Botan {

template<typename Mutex>
class lock_guard final
   {
   public:
      explicit lock_guard(Mutex& m) : m_mutex(m)
         { m_mutex.lock(); }

      ~lock_guard() { m_mutex.unlock(); }

      lock_guard(const lock_guard& other) = delete;
      lock_guard& operator=(const lock_guard& other) = delete;
   private:
      Mutex& m_mutex;
   };

class noop_mutex final
   {
   public:
      void lock() {}
      void unlock() {}
   };

typedef noop_mutex mutex_type;
typedef noop_mutex recursive_mutex_type;
template<typename T> using lock_guard_type = lock_guard<T>;

}

#endif

namespace Botan {

class Entropy_Sources;

/**
* An interface to a cryptographic random number generator
*/
class BOTAN_PUBLIC_API(2,0) RandomNumberGenerator
   {
   public:
      virtual ~RandomNumberGenerator() = default;

      RandomNumberGenerator() = default;

      /*
      * Never copy a RNG, create a new one
      */
      RandomNumberGenerator(const RandomNumberGenerator& rng) = delete;
      RandomNumberGenerator& operator=(const RandomNumberGenerator& rng) = delete;

      /**
      * Randomize a byte array.
      * @param output the byte array to hold the random output.
      * @param length the length of the byte array output in bytes.
      */
      virtual void randomize(uint8_t output[], size_t length) = 0;

      /**
      * Returns false if it is known that this RNG object is not able to accept
      * externally provided inputs (via add_entropy, randomize_with_input, etc).
      * In this case, any such provided inputs are ignored.
      *
      * If this function returns true, then inputs may or may not be accepted.
      */
      virtual bool accepts_input() const = 0;

      /**
      * Incorporate some additional data into the RNG state. For
      * example adding nonces or timestamps from a peer's protocol
      * message can help hedge against VM state rollback attacks.
      * A few RNG types do not accept any externally provided input,
      * in which case this function is a no-op.
      *
      * @param input a byte array containg the entropy to be added
      * @param length the length of the byte array in
      */
      virtual void add_entropy(const uint8_t input[], size_t length) = 0;

      /**
      * Incorporate some additional data into the RNG state.
      */
      template<typename T> void add_entropy_T(const T& t)
         {
         static_assert(std::is_standard_layout<T>::value && std::is_trivial<T>::value, "add_entropy_T data must be POD");
         this->add_entropy(reinterpret_cast<const uint8_t*>(&t), sizeof(T));
         }

      /**
      * Incorporate entropy into the RNG state then produce output.
      * Some RNG types implement this using a single operation, default
      * calls add_entropy + randomize in sequence.
      *
      * Use this to further bind the outputs to your current
      * process/protocol state. For instance if generating a new key
      * for use in a session, include a session ID or other such
      * value. See NIST SP 800-90 A, B, C series for more ideas.
      *
      * @param output buffer to hold the random output
      * @param output_len size of the output buffer in bytes
      * @param input entropy buffer to incorporate
      * @param input_len size of the input buffer in bytes
      */
      virtual void randomize_with_input(uint8_t output[], size_t output_len,
                                        const uint8_t input[], size_t input_len);

      /**
      * This calls `randomize_with_input` using some timestamps as extra input.
      *
      * For a stateful RNG using non-random but potentially unique data the
      * extra input can help protect against problems with fork, VM state
      * rollback, or other cases where somehow an RNG state is duplicated. If
      * both of the duplicated RNG states later incorporate a timestamp (and the
      * timestamps don't themselves repeat), their outputs will diverge.
      */
      virtual void randomize_with_ts_input(uint8_t output[], size_t output_len);

      /**
      * @return the name of this RNG type
      */
      virtual std::string name() const = 0;

      /**
      * Clear all internally held values of this RNG
      * @post is_seeded() == false
      */
      virtual void clear() = 0;

      /**
      * Check whether this RNG is seeded.
      * @return true if this RNG was already seeded, false otherwise.
      */
      virtual bool is_seeded() const = 0;

      /**
      * Poll provided sources for up to poll_bits bits of entropy
      * or until the timeout expires. Returns estimate of the number
      * of bits collected.
      */
      virtual size_t reseed(Entropy_Sources& srcs,
                            size_t poll_bits = BOTAN_RNG_RESEED_POLL_BITS,
                            std::chrono::milliseconds poll_timeout = BOTAN_RNG_RESEED_DEFAULT_TIMEOUT);

      /**
      * Reseed by reading specified bits from the RNG
      */
      virtual void reseed_from_rng(RandomNumberGenerator& rng,
                                   size_t poll_bits = BOTAN_RNG_RESEED_POLL_BITS);

      // Some utility functions built on the interface above:

      /**
      * Return a random vector
      * @param bytes number of bytes in the result
      * @return randomized vector of length bytes
      */
      secure_vector<uint8_t> random_vec(size_t bytes)
         {
         secure_vector<uint8_t> output;
         random_vec(output, bytes);
         return output;
         }

      template<typename Alloc>
         void random_vec(std::vector<uint8_t, Alloc>& v, size_t bytes)
         {
         v.resize(bytes);
         this->randomize(v.data(), v.size());
         }

      /**
      * Return a random byte
      * @return random byte
      */
      uint8_t next_byte()
         {
         uint8_t b;
         this->randomize(&b, 1);
         return b;
         }

      /**
      * @return a random byte that is greater than zero
      */
      uint8_t next_nonzero_byte()
         {
         uint8_t b = this->next_byte();
         while(b == 0)
            b = this->next_byte();
         return b;
         }

      /**
      * Create a seeded and active RNG object for general application use
      * Added in 1.8.0
      * Use AutoSeeded_RNG instead
      */
      BOTAN_DEPRECATED("Use AutoSeeded_RNG")
      static RandomNumberGenerator* make_rng();
   };

/**
* Convenience typedef
*/
typedef RandomNumberGenerator RNG;

/**
* Hardware_RNG exists to tag hardware RNG types (PKCS11_RNG, TPM_RNG, Processor_RNG)
*/
class BOTAN_PUBLIC_API(2,0) Hardware_RNG : public RandomNumberGenerator
   {
   public:
      virtual void clear() final override { /* no way to clear state of hardware RNG */ }
   };

/**
* Null/stub RNG - fails if you try to use it for anything
* This is not generally useful except for in certain tests
*/
class BOTAN_PUBLIC_API(2,0) Null_RNG final : public RandomNumberGenerator
   {
   public:
      bool is_seeded() const override { return false; }

      bool accepts_input() const override { return false; }

      void clear() override {}

      void randomize(uint8_t[], size_t) override
         {
         throw PRNG_Unseeded("Null_RNG called");
         }

      void add_entropy(const uint8_t[], size_t) override {}

      std::string name() const override { return "Null_RNG"; }
   };

#if defined(BOTAN_TARGET_OS_HAS_THREADS)
/**
* Wraps access to a RNG in a mutex
* Note that most of the time it's much better to use a RNG per thread
* otherwise the RNG will act as an unnecessary contention point
*
* Since 2.16.0 all Stateful_RNG instances have an internal lock, so
* this class is no longer needed. It will be removed in a future major
* release.
*/
class BOTAN_PUBLIC_API(2,0) Serialized_RNG final : public RandomNumberGenerator
   {
   public:
      void randomize(uint8_t out[], size_t len) override
         {
         lock_guard_type<mutex_type> lock(m_mutex);
         m_rng->randomize(out, len);
         }

      bool accepts_input() const override
         {
         lock_guard_type<mutex_type> lock(m_mutex);
         return m_rng->accepts_input();
         }

      bool is_seeded() const override
         {
         lock_guard_type<mutex_type> lock(m_mutex);
         return m_rng->is_seeded();
         }

      void clear() override
         {
         lock_guard_type<mutex_type> lock(m_mutex);
         m_rng->clear();
         }

      std::string name() const override
         {
         lock_guard_type<mutex_type> lock(m_mutex);
         return m_rng->name();
         }

      size_t reseed(Entropy_Sources& src,
                    size_t poll_bits = BOTAN_RNG_RESEED_POLL_BITS,
                    std::chrono::milliseconds poll_timeout = BOTAN_RNG_RESEED_DEFAULT_TIMEOUT) override
         {
         lock_guard_type<mutex_type> lock(m_mutex);
         return m_rng->reseed(src, poll_bits, poll_timeout);
         }

      void add_entropy(const uint8_t in[], size_t len) override
         {
         lock_guard_type<mutex_type> lock(m_mutex);
         m_rng->add_entropy(in, len);
         }

      BOTAN_DEPRECATED("Use Serialized_RNG(new AutoSeeded_RNG) instead") Serialized_RNG();

      /*
      * Since 2.16.0 this is no longer needed for any RNG type. This
      * class will be removed in a future major release.
      */
      explicit Serialized_RNG(RandomNumberGenerator* rng) : m_rng(rng) {}
   private:
      mutable mutex_type m_mutex;
      std::unique_ptr<RandomNumberGenerator> m_rng;
   };
#endif

}

namespace Botan {

class Stateful_RNG;

/**
* A userspace PRNG
*/
class BOTAN_PUBLIC_API(2,0) AutoSeeded_RNG final : public RandomNumberGenerator
   {
   public:
      void randomize(uint8_t out[], size_t len) override;

      void randomize_with_input(uint8_t output[], size_t output_len,
                                const uint8_t input[], size_t input_len) override;

      bool is_seeded() const override;

      bool accepts_input() const override { return true; }

      /**
      * Mark state as requiring a reseed on next use
      */
      void force_reseed();

      size_t reseed(Entropy_Sources& srcs,
                    size_t poll_bits = BOTAN_RNG_RESEED_POLL_BITS,
                    std::chrono::milliseconds poll_timeout = BOTAN_RNG_RESEED_DEFAULT_TIMEOUT) override;

      void add_entropy(const uint8_t in[], size_t len) override;

      std::string name() const override;

      void clear() override;

      /**
      * Uses the system RNG (if available) or else a default group of
      * entropy sources (all other systems) to gather seed material.
      *
      * @param reseed_interval specifies a limit of how many times
      * the RNG will be called before automatic reseeding is performed
      */
      AutoSeeded_RNG(size_t reseed_interval = BOTAN_RNG_DEFAULT_RESEED_INTERVAL);

      /**
      * Create an AutoSeeded_RNG which will get seed material from some other
      * RNG instance. For example you could provide a reference to the system
      * RNG or a hardware RNG.
      *
      * @param underlying_rng is a reference to some RNG which will be used
      * to perform the periodic reseeding
      * @param reseed_interval specifies a limit of how many times
      * the RNG will be called before automatic reseeding is performed
      */
      AutoSeeded_RNG(RandomNumberGenerator& underlying_rng,
                     size_t reseed_interval = BOTAN_RNG_DEFAULT_RESEED_INTERVAL);

      /**
      * Create an AutoSeeded_RNG which will get seed material from a set of
      * entropy sources.
      *
      * @param entropy_sources will be polled to perform reseeding periodically
      * @param reseed_interval specifies a limit of how many times
      * the RNG will be called before automatic reseeding is performed
      */
      AutoSeeded_RNG(Entropy_Sources& entropy_sources,
                     size_t reseed_interval = BOTAN_RNG_DEFAULT_RESEED_INTERVAL);

      /**
      * Create an AutoSeeded_RNG which will get seed material from both an
      * underlying RNG and a set of entropy sources.
      *
      * @param underlying_rng is a reference to some RNG which will be used
      * to perform the periodic reseeding
      * @param entropy_sources will be polled to perform reseeding periodically
      * @param reseed_interval specifies a limit of how many times
      * the RNG will be called before automatic reseeding is performed
      */
      AutoSeeded_RNG(RandomNumberGenerator& underlying_rng,
                     Entropy_Sources& entropy_sources,
                     size_t reseed_interval = BOTAN_RNG_DEFAULT_RESEED_INTERVAL);

      ~AutoSeeded_RNG();

   private:
      std::unique_ptr<Stateful_RNG> m_rng;
   };

}

namespace Botan {

/**
* Perform base64 encoding
* @param output an array of at least base64_encode_max_output bytes
* @param input is some binary data
* @param input_length length of input in bytes
* @param input_consumed is an output parameter which says how many
*        bytes of input were actually consumed. If less than
*        input_length, then the range input[consumed:length]
*        should be passed in later along with more input.
* @param final_inputs true iff this is the last input, in which case
         padding chars will be applied if needed
* @return number of bytes written to output
*/
size_t BOTAN_PUBLIC_API(2,0) base64_encode(char output[],
                               const uint8_t input[],
                               size_t input_length,
                               size_t& input_consumed,
                               bool final_inputs);

/**
* Perform base64 encoding
* @param input some input
* @param input_length length of input in bytes
* @return base64adecimal representation of input
*/
std::string BOTAN_PUBLIC_API(2,0) base64_encode(const uint8_t input[],
                                    size_t input_length);

/**
* Perform base64 encoding
* @param input some input
* @return base64adecimal representation of input
*/
template<typename Alloc>
std::string base64_encode(const std::vector<uint8_t, Alloc>& input)
   {
   return base64_encode(input.data(), input.size());
   }

/**
* Perform base64 decoding
* @param output an array of at least base64_decode_max_output bytes
* @param input some base64 input
* @param input_length length of input in bytes
* @param input_consumed is an output parameter which says how many
*        bytes of input were actually consumed. If less than
*        input_length, then the range input[consumed:length]
*        should be passed in later along with more input.
* @param final_inputs true iff this is the last input, in which case
         padding is allowed
* @param ignore_ws ignore whitespace on input; if false, throw an
                   exception if whitespace is encountered
* @return number of bytes written to output
*/
size_t BOTAN_PUBLIC_API(2,0) base64_decode(uint8_t output[],
                               const char input[],
                               size_t input_length,
                               size_t& input_consumed,
                               bool final_inputs,
                               bool ignore_ws = true);

/**
* Perform base64 decoding
* @param output an array of at least base64_decode_max_output bytes
* @param input some base64 input
* @param input_length length of input in bytes
* @param ignore_ws ignore whitespace on input; if false, throw an
                   exception if whitespace is encountered
* @return number of bytes written to output
*/
size_t BOTAN_PUBLIC_API(2,0) base64_decode(uint8_t output[],
                               const char input[],
                               size_t input_length,
                               bool ignore_ws = true);

/**
* Perform base64 decoding
* @param output an array of at least base64_decode_max_output bytes
* @param input some base64 input
* @param ignore_ws ignore whitespace on input; if false, throw an
                   exception if whitespace is encountered
* @return number of bytes written to output
*/
size_t BOTAN_PUBLIC_API(2,0) base64_decode(uint8_t output[],
                               const std::string& input,
                               bool ignore_ws = true);

/**
* Perform base64 decoding
* @param input some base64 input
* @param input_length the length of input in bytes
* @param ignore_ws ignore whitespace on input; if false, throw an
                   exception if whitespace is encountered
* @return decoded base64 output
*/
secure_vector<uint8_t> BOTAN_PUBLIC_API(2,0) base64_decode(const char input[],
                                           size_t input_length,
                                           bool ignore_ws = true);

/**
* Perform base64 decoding
* @param input some base64 input
* @param ignore_ws ignore whitespace on input; if false, throw an
                   exception if whitespace is encountered
* @return decoded base64 output
*/
secure_vector<uint8_t> BOTAN_PUBLIC_API(2,0) base64_decode(const std::string& input,
                                           bool ignore_ws = true);

/**
* Calculate the size of output buffer for base64_encode
* @param input_length the length of input in bytes
* @return the size of output buffer in bytes
*/
size_t BOTAN_PUBLIC_API(2,1) base64_encode_max_output(size_t input_length);

/**
* Calculate the size of output buffer for base64_decode
* @param input_length the length of input in bytes
* @return the size of output buffer in bytes
*/
size_t BOTAN_PUBLIC_API(2,1) base64_decode_max_output(size_t input_length);

}

namespace Botan {

/**
* This class represents an abstract data source object.
*/
class BOTAN_PUBLIC_API(2,0) DataSource
   {
   public:
      /**
      * Read from the source. Moves the internal offset so that every
      * call to read will return a new portion of the source.
      *
      * @param out the byte array to write the result to
      * @param length the length of the byte array out
      * @return length in bytes that was actually read and put
      * into out
      */
      virtual size_t read(uint8_t out[], size_t length) BOTAN_WARN_UNUSED_RESULT = 0;

      virtual bool check_available(size_t n) = 0;

      /**
      * Read from the source but do not modify the internal
      * offset. Consecutive calls to peek() will return portions of
      * the source starting at the same position.
      *
      * @param out the byte array to write the output to
      * @param length the length of the byte array out
      * @param peek_offset the offset into the stream to read at
      * @return length in bytes that was actually read and put
      * into out
      */
      virtual size_t peek(uint8_t out[], size_t length, size_t peek_offset) const BOTAN_WARN_UNUSED_RESULT = 0;

      /**
      * Test whether the source still has data that can be read.
      * @return true if there is no more data to read, false otherwise
      */
      virtual bool end_of_data() const = 0;
      /**
      * return the id of this data source
      * @return std::string representing the id of this data source
      */
      virtual std::string id() const { return ""; }

      /**
      * Read one byte.
      * @param out the byte to read to
      * @return length in bytes that was actually read and put
      * into out
      */
      size_t read_byte(uint8_t& out);

      /**
      * Peek at one byte.
      * @param out an output byte
      * @return length in bytes that was actually read and put
      * into out
      */
      size_t peek_byte(uint8_t& out) const;

      /**
      * Discard the next N bytes of the data
      * @param N the number of bytes to discard
      * @return number of bytes actually discarded
      */
      size_t discard_next(size_t N);

      /**
      * @return number of bytes read so far.
      */
      virtual size_t get_bytes_read() const = 0;

      DataSource() = default;
      virtual ~DataSource() = default;
      DataSource& operator=(const DataSource&) = delete;
      DataSource(const DataSource&) = delete;
   };

/**
* This class represents a Memory-Based DataSource
*/
class BOTAN_PUBLIC_API(2,0) DataSource_Memory final : public DataSource
   {
   public:
      size_t read(uint8_t[], size_t) override;
      size_t peek(uint8_t[], size_t, size_t) const override;
      bool check_available(size_t n) override;
      bool end_of_data() const override;

      /**
      * Construct a memory source that reads from a string
      * @param in the string to read from
      */
      explicit DataSource_Memory(const std::string& in);

      /**
      * Construct a memory source that reads from a byte array
      * @param in the byte array to read from
      * @param length the length of the byte array
      */
      DataSource_Memory(const uint8_t in[], size_t length) :
         m_source(in, in + length), m_offset(0) {}

      /**
      * Construct a memory source that reads from a secure_vector
      * @param in the MemoryRegion to read from
      */
      explicit DataSource_Memory(const secure_vector<uint8_t>& in) :
         m_source(in), m_offset(0) {}

      /**
      * Construct a memory source that reads from a std::vector
      * @param in the MemoryRegion to read from
      */
      explicit DataSource_Memory(const std::vector<uint8_t>& in) :
         m_source(in.begin(), in.end()), m_offset(0) {}

      size_t get_bytes_read() const override { return m_offset; }
   private:
      secure_vector<uint8_t> m_source;
      size_t m_offset;
   };

/**
* This class represents a Stream-Based DataSource.
*/
class BOTAN_PUBLIC_API(2,0) DataSource_Stream final : public DataSource
   {
   public:
      size_t read(uint8_t[], size_t) override;
      size_t peek(uint8_t[], size_t, size_t) const override;
      bool check_available(size_t n) override;
      bool end_of_data() const override;
      std::string id() const override;

      DataSource_Stream(std::istream&,
                        const std::string& id = "<std::istream>");

#if defined(BOTAN_TARGET_OS_HAS_FILESYSTEM)
      /**
      * Construct a Stream-Based DataSource from filesystem path
      * @param file the path to the file
      * @param use_binary whether to treat the file as binary or not
      */
      DataSource_Stream(const std::string& file, bool use_binary = false);
#endif

      DataSource_Stream(const DataSource_Stream&) = delete;

      DataSource_Stream& operator=(const DataSource_Stream&) = delete;

      ~DataSource_Stream();

      size_t get_bytes_read() const override { return m_total_read; }
   private:
      const std::string m_identifier;

      std::unique_ptr<std::istream> m_source_memory;
      std::istream& m_source;
      size_t m_total_read;
   };

}

namespace Botan {

class BigInt;

/**
* BER Decoding Object
*/
class BOTAN_PUBLIC_API(2,0) BER_Decoder final
   {
   public:
      /**
      * Set up to BER decode the data in buf of length len
      */
      BER_Decoder(const uint8_t buf[], size_t len);

      /**
      * Set up to BER decode the data in vec
      */
      explicit BER_Decoder(const secure_vector<uint8_t>& vec);

      /**
      * Set up to BER decode the data in vec
      */
      explicit BER_Decoder(const std::vector<uint8_t>& vec);

      /**
      * Set up to BER decode the data in src
      */
      explicit BER_Decoder(DataSource& src);

      /**
      * Set up to BER decode the data in obj
      */
      BER_Decoder(const BER_Object& obj) :
         BER_Decoder(obj.bits(), obj.length()) {}

      /**
      * Set up to BER decode the data in obj
      */
      BER_Decoder(BER_Object&& obj) :
         BER_Decoder(std::move(obj), nullptr) {}

      BER_Decoder(const BER_Decoder& other);

      BER_Decoder& operator=(const BER_Decoder&) = delete;

      /**
      * Get the next object in the data stream.
      * If EOF, returns an object with type NO_OBJECT.
      */
      BER_Object get_next_object();

      BER_Decoder& get_next(BER_Object& ber)
         {
         ber = get_next_object();
         return (*this);
         }

      /**
      * Push an object back onto the stream. Throws if another
      * object was previously pushed and has not been subsequently
      * read out.
      */
      void push_back(const BER_Object& obj);

      /**
      * Push an object back onto the stream. Throws if another
      * object was previously pushed and has not been subsequently
      * read out.
      */
      void push_back(BER_Object&& obj);

      /**
      * Return true if there is at least one more item remaining
      */
      bool more_items() const;

      /**
      * Verify the stream is concluded, throws otherwise.
      * Returns (*this)
      */
      BER_Decoder& verify_end();

      /**
      * Verify the stream is concluded, throws otherwise.
      * Returns (*this)
      */
      BER_Decoder& verify_end(const std::string& err_msg);

      /**
      * Discard any data that remains unread
      * Returns (*this)
      */
      BER_Decoder& discard_remaining();

      /**
      * Start decoding a constructed data (sequence or set)
      */
      BER_Decoder start_cons(ASN1_Tag type_tag, ASN1_Tag class_tag = UNIVERSAL);

      /**
      * Finish decoding a constructed data, throws if any data remains.
      * Returns the parent of *this (ie the object on which start_cons was called).
      */
      BER_Decoder& end_cons();

      /**
      * Get next object and copy value to POD type
      * Asserts value length is equal to POD type sizeof.
      * Asserts Type tag and optional Class tag according to parameters.
      * Copy value to POD type (struct, union, C-style array, std::array, etc.).
      * @param out POD type reference where to copy object value
      * @param type_tag ASN1_Tag enum to assert type on object read
      * @param class_tag ASN1_Tag enum to assert class on object read (default: CONTEXT_SPECIFIC)
      * @return this reference
      */
      template <typename T>
         BER_Decoder& get_next_value(T &out,
                                     ASN1_Tag type_tag,
                                     ASN1_Tag class_tag = CONTEXT_SPECIFIC)
         {
         static_assert(std::is_standard_layout<T>::value && std::is_trivial<T>::value, "Type must be POD");

         BER_Object obj = get_next_object();
         obj.assert_is_a(type_tag, class_tag);

         if (obj.length() != sizeof(T))
            throw BER_Decoding_Error(
                    "Size mismatch. Object value size is " +
                    std::to_string(obj.length()) +
                    "; Output type size is " +
                    std::to_string(sizeof(T)));

         copy_mem(reinterpret_cast<uint8_t*>(&out), obj.bits(), obj.length());

         return (*this);
         }

      /*
      * Save all the bytes remaining in the source
      */
      template<typename Alloc>
      BER_Decoder& raw_bytes(std::vector<uint8_t, Alloc>& out)
         {
         out.clear();
         uint8_t buf;
         while(m_source->read_byte(buf))
            out.push_back(buf);
         return (*this);
         }

      BER_Decoder& decode_null();

      /**
      * Decode a BER encoded BOOLEAN
      */
      BER_Decoder& decode(bool& out)
         {
         return decode(out, BOOLEAN, UNIVERSAL);
         }

      /*
      * Decode a small BER encoded INTEGER
      */
      BER_Decoder& decode(size_t& out)
         {
         return decode(out, INTEGER, UNIVERSAL);
         }

      /*
      * Decode a BER encoded INTEGER
      */
      BER_Decoder& decode(BigInt& out)
         {
         return decode(out, INTEGER, UNIVERSAL);
         }

      std::vector<uint8_t> get_next_octet_string()
         {
         std::vector<uint8_t> out_vec;
         decode(out_vec, OCTET_STRING);
         return out_vec;
         }

      /*
      * BER decode a BIT STRING or OCTET STRING
      */
      template<typename Alloc>
      BER_Decoder& decode(std::vector<uint8_t, Alloc>& out, ASN1_Tag real_type)
         {
         return decode(out, real_type, real_type, UNIVERSAL);
         }

      BER_Decoder& decode(bool& v,
                          ASN1_Tag type_tag,
                          ASN1_Tag class_tag = CONTEXT_SPECIFIC);

      BER_Decoder& decode(size_t& v,
                          ASN1_Tag type_tag,
                          ASN1_Tag class_tag = CONTEXT_SPECIFIC);

      BER_Decoder& decode(BigInt& v,
                          ASN1_Tag type_tag,
                          ASN1_Tag class_tag = CONTEXT_SPECIFIC);

      BER_Decoder& decode(std::vector<uint8_t>& v,
                          ASN1_Tag real_type,
                          ASN1_Tag type_tag,
                          ASN1_Tag class_tag = CONTEXT_SPECIFIC);

      BER_Decoder& decode(secure_vector<uint8_t>& v,
                          ASN1_Tag real_type,
                          ASN1_Tag type_tag,
                          ASN1_Tag class_tag = CONTEXT_SPECIFIC);

      BER_Decoder& decode(class ASN1_Object& obj,
                          ASN1_Tag type_tag = NO_OBJECT,
                          ASN1_Tag class_tag = NO_OBJECT);

      /**
      * Decode an integer value which is typed as an octet string
      */
      BER_Decoder& decode_octet_string_bigint(BigInt& b);

      uint64_t decode_constrained_integer(ASN1_Tag type_tag,
                                          ASN1_Tag class_tag,
                                          size_t T_bytes);

      template<typename T> BER_Decoder& decode_integer_type(T& out)
         {
         return decode_integer_type<T>(out, INTEGER, UNIVERSAL);
         }

      template<typename T>
         BER_Decoder& decode_integer_type(T& out,
                                          ASN1_Tag type_tag,
                                          ASN1_Tag class_tag = CONTEXT_SPECIFIC)
         {
         out = static_cast<T>(decode_constrained_integer(type_tag, class_tag, sizeof(out)));
         return (*this);
         }

      template<typename T>
         BER_Decoder& decode_optional(T& out,
                                      ASN1_Tag type_tag,
                                      ASN1_Tag class_tag,
                                      const T& default_value = T());

      template<typename T>
         BER_Decoder& decode_optional_implicit(
            T& out,
            ASN1_Tag type_tag,
            ASN1_Tag class_tag,
            ASN1_Tag real_type,
            ASN1_Tag real_class,
            const T& default_value = T());

      template<typename T>
         BER_Decoder& decode_list(std::vector<T>& out,
                                  ASN1_Tag type_tag = SEQUENCE,
                                  ASN1_Tag class_tag = UNIVERSAL);

      template<typename T>
         BER_Decoder& decode_and_check(const T& expected,
                                       const std::string& error_msg)
         {
         T actual;
         decode(actual);

         if(actual != expected)
            throw Decoding_Error(error_msg);

         return (*this);
         }

      /*
      * Decode an OPTIONAL string type
      */
      template<typename Alloc>
      BER_Decoder& decode_optional_string(std::vector<uint8_t, Alloc>& out,
                                          ASN1_Tag real_type,
                                          uint16_t type_no,
                                          ASN1_Tag class_tag = CONTEXT_SPECIFIC)
         {
         BER_Object obj = get_next_object();

         ASN1_Tag type_tag = static_cast<ASN1_Tag>(type_no);

         if(obj.is_a(type_tag, class_tag))
            {
            if((class_tag & CONSTRUCTED) && (class_tag & CONTEXT_SPECIFIC))
               {
               BER_Decoder(std::move(obj)).decode(out, real_type).verify_end();
               }
            else
               {
               push_back(std::move(obj));
               decode(out, real_type, type_tag, class_tag);
               }
            }
         else
            {
            out.clear();
            push_back(std::move(obj));
            }

         return (*this);
         }

   private:
      BER_Decoder(BER_Object&& obj, BER_Decoder* parent);

      BER_Decoder* m_parent = nullptr;
      BER_Object m_pushed;
      // either m_data_src.get() or an unowned pointer
      DataSource* m_source;
      mutable std::unique_ptr<DataSource> m_data_src;
   };

/*
* Decode an OPTIONAL or DEFAULT element
*/
template<typename T>
BER_Decoder& BER_Decoder::decode_optional(T& out,
                                          ASN1_Tag type_tag,
                                          ASN1_Tag class_tag,
                                          const T& default_value)
   {
   BER_Object obj = get_next_object();

   if(obj.is_a(type_tag, class_tag))
      {
      if((class_tag & CONSTRUCTED) && (class_tag & CONTEXT_SPECIFIC))
         {
         BER_Decoder(std::move(obj)).decode(out).verify_end();
         }
      else
         {
         push_back(std::move(obj));
         decode(out, type_tag, class_tag);
         }
      }
   else
      {
      out = default_value;
      push_back(std::move(obj));
      }

   return (*this);
   }

/*
* Decode an OPTIONAL or DEFAULT element
*/
template<typename T>
BER_Decoder& BER_Decoder::decode_optional_implicit(
   T& out,
   ASN1_Tag type_tag,
   ASN1_Tag class_tag,
   ASN1_Tag real_type,
   ASN1_Tag real_class,
   const T& default_value)
   {
   BER_Object obj = get_next_object();

   if(obj.is_a(type_tag, class_tag))
      {
      obj.set_tagging(real_type, real_class);
      push_back(std::move(obj));
      decode(out, real_type, real_class);
      }
   else
      {
      // Not what we wanted, push it back on the stream
      out = default_value;
      push_back(std::move(obj));
      }

   return (*this);
   }
/*
* Decode a list of homogenously typed values
*/
template<typename T>
BER_Decoder& BER_Decoder::decode_list(std::vector<T>& vec,
                                      ASN1_Tag type_tag,
                                      ASN1_Tag class_tag)
   {
   BER_Decoder list = start_cons(type_tag, class_tag);

   while(list.more_items())
      {
      T value;
      list.decode(value);
      vec.push_back(std::move(value));
      }

   list.end_cons();

   return (*this);
   }

}

namespace Botan {

class RandomNumberGenerator;

/**
* Arbitrary precision integer
*/
class BOTAN_PUBLIC_API(2,0) BigInt final
   {
   public:
     /**
     * Base enumerator for encoding and decoding
     */
     enum Base { Decimal = 10, Hexadecimal = 16, Binary = 256 };

     /**
     * Sign symbol definitions for positive and negative numbers
     */
     enum Sign { Negative = 0, Positive = 1 };

     /**
     * DivideByZero Exception
     *
     * In a future release this exception will be removed and its usage
     * replaced by Invalid_Argument
     */
     class BOTAN_PUBLIC_API(2,0) DivideByZero final : public Invalid_Argument
        {
        public:
           DivideByZero() : Invalid_Argument("BigInt divide by zero") {}
        };

     /**
     * Create empty BigInt
     */
     BigInt() = default;

     /**
     * Create BigInt from 64 bit integer
     * @param n initial value of this BigInt
     */
     BigInt(uint64_t n);

     /**
     * Copy Constructor
     * @param other the BigInt to copy
     */
     BigInt(const BigInt& other) = default;

     /**
     * Create BigInt from a string. If the string starts with 0x the
     * rest of the string will be interpreted as hexadecimal digits.
     * Otherwise, it will be interpreted as a decimal number.
     *
     * @param str the string to parse for an integer value
     */
     explicit BigInt(const std::string& str);

     /**
     * Create a BigInt from an integer in a byte array
     * @param buf the byte array holding the value
     * @param length size of buf
     */
     BigInt(const uint8_t buf[], size_t length);

     /**
     * Create a BigInt from an integer in a byte array
     * @param vec the byte vector holding the value
     */
     template<typename Alloc>
     explicit BigInt(const std::vector<uint8_t, Alloc>& vec) : BigInt(vec.data(), vec.size()) {}

     /**
     * Create a BigInt from an integer in a byte array
     * @param buf the byte array holding the value
     * @param length size of buf
     * @param base is the number base of the integer in buf
     */
     BigInt(const uint8_t buf[], size_t length, Base base);

     /**
     * Create a BigInt from an integer in a byte array
     * @param buf the byte array holding the value
     * @param length size of buf
     * @param max_bits if the resulting integer is more than max_bits,
     *        it will be shifted so it is at most max_bits in length.
     */
     BigInt(const uint8_t buf[], size_t length, size_t max_bits);

     /**
     * Create a BigInt from an array of words
     * @param words the words
     * @param length number of words
     */
     BigInt(const word words[], size_t length);

     /**
     * \brief Create a random BigInt of the specified size
     *
     * @param rng random number generator
     * @param bits size in bits
     * @param set_high_bit if true, the highest bit is always set
     *
     * @see randomize
     */
     BigInt(RandomNumberGenerator& rng, size_t bits, bool set_high_bit = true);

     /**
     * Create BigInt of specified size, all zeros
     * @param sign the sign
     * @param n size of the internal register in words
     */
     BigInt(Sign sign, size_t n);

     /**
     * Move constructor
     */
     BigInt(BigInt&& other)
        {
        this->swap(other);
        }

     ~BigInt() { const_time_unpoison(); }

     /**
     * Move assignment
     */
     BigInt& operator=(BigInt&& other)
        {
        if(this != &other)
           this->swap(other);

        return (*this);
        }

     /**
     * Copy assignment
     */
     BigInt& operator=(const BigInt&) = default;

     /**
     * Swap this value with another
     * @param other BigInt to swap values with
     */
     void swap(BigInt& other)
        {
        m_data.swap(other.m_data);
        std::swap(m_signedness, other.m_signedness);
        }

     void swap_reg(secure_vector<word>& reg)
        {
        m_data.swap(reg);
        // sign left unchanged
        }

     /**
     * += operator
     * @param y the BigInt to add to this
     */
     BigInt& operator+=(const BigInt& y)
        {
        return add(y.data(), y.sig_words(), y.sign());
        }

     /**
     * += operator
     * @param y the word to add to this
     */
     BigInt& operator+=(word y)
        {
        return add(&y, 1, Positive);
        }

     /**
     * -= operator
     * @param y the BigInt to subtract from this
     */
     BigInt& operator-=(const BigInt& y)
        {
        return sub(y.data(), y.sig_words(), y.sign());
        }

     /**
     * -= operator
     * @param y the word to subtract from this
     */
     BigInt& operator-=(word y)
        {
        return sub(&y, 1, Positive);
        }

     /**
     * *= operator
     * @param y the BigInt to multiply with this
     */
     BigInt& operator*=(const BigInt& y);

     /**
     * *= operator
     * @param y the word to multiply with this
     */
     BigInt& operator*=(word y);

     /**
     * /= operator
     * @param y the BigInt to divide this by
     */
     BigInt& operator/=(const BigInt& y);

     /**
     * Modulo operator
     * @param y the modulus to reduce this by
     */
     BigInt& operator%=(const BigInt& y);

     /**
     * Modulo operator
     * @param y the modulus (word) to reduce this by
     */
     word    operator%=(word y);

     /**
     * Left shift operator
     * @param shift the number of bits to shift this left by
     */
     BigInt& operator<<=(size_t shift);

     /**
     * Right shift operator
     * @param shift the number of bits to shift this right by
     */
     BigInt& operator>>=(size_t shift);

     /**
     * Increment operator
     */
     BigInt& operator++() { return (*this += 1); }

     /**
     * Decrement operator
     */
     BigInt& operator--() { return (*this -= 1); }

     /**
     * Postfix increment operator
     */
     BigInt  operator++(int) { BigInt x = (*this); ++(*this); return x; }

     /**
     * Postfix decrement operator
     */
     BigInt  operator--(int) { BigInt x = (*this); --(*this); return x; }

     /**
     * Unary negation operator
     * @return negative this
     */
     BigInt operator-() const;

     /**
     * ! operator
     * @return true iff this is zero, otherwise false
     */
     bool operator !() const { return (!is_nonzero()); }

     static BigInt add2(const BigInt& x, const word y[], size_t y_words, Sign y_sign);

     BigInt& add(const word y[], size_t y_words, Sign sign);

     BigInt& sub(const word y[], size_t y_words, Sign sign)
        {
        return add(y, y_words, sign == Positive ? Negative : Positive);
        }

     /**
     * Multiply this with y
     * @param y the BigInt to multiply with this
     * @param ws a temp workspace
     */
     BigInt& mul(const BigInt& y, secure_vector<word>& ws);

     /**
     * Square value of *this
     * @param ws a temp workspace
     */
     BigInt& square(secure_vector<word>& ws);

     /**
     * Set *this to y - *this
     * @param y the BigInt to subtract from as a sequence of words
     * @param y_words length of y in words
     * @param ws a temp workspace
     */
     BigInt& rev_sub(const word y[], size_t y_words, secure_vector<word>& ws);

     /**
     * Set *this to (*this + y) % mod
     * This function assumes *this is >= 0 && < mod
     * @param y the BigInt to add - assumed y >= 0 and y < mod
     * @param mod the positive modulus
     * @param ws a temp workspace
     */
     BigInt& mod_add(const BigInt& y, const BigInt& mod, secure_vector<word>& ws);

     /**
     * Set *this to (*this - y) % mod
     * This function assumes *this is >= 0 && < mod
     * @param y the BigInt to subtract - assumed y >= 0 and y < mod
     * @param mod the positive modulus
     * @param ws a temp workspace
     */
     BigInt& mod_sub(const BigInt& y, const BigInt& mod, secure_vector<word>& ws);

     /**
     * Set *this to (*this * y) % mod
     * This function assumes *this is >= 0 && < mod
     * y should be small, less than 16
     * @param y the small integer to multiply by
     * @param mod the positive modulus
     * @param ws a temp workspace
     */
     BigInt& mod_mul(uint8_t y, const BigInt& mod, secure_vector<word>& ws);

     /**
     * Return *this % mod
     *
     * Assumes that *this is (if anything) only slightly larger than
     * mod and performs repeated subtractions. It should not be used if
     * *this is much larger than mod, instead use modulo operator.
     */
     size_t reduce_below(const BigInt& mod, secure_vector<word> &ws);

     /**
     * Return *this % mod
     *
     * Assumes that *this is (if anything) only slightly larger than mod and
     * performs repeated subtractions. It should not be used if *this is much
     * larger than mod, instead use modulo operator.
     *
     * Performs exactly bound subtractions, so if *this is >= bound*mod then the
     * result will not be fully reduced. If bound is zero, nothing happens.
     */
     void ct_reduce_below(const BigInt& mod, secure_vector<word> &ws, size_t bound);

     /**
     * Zeroize the BigInt. The size of the underlying register is not
     * modified.
     */
     void clear() { m_data.set_to_zero(); m_signedness = Positive; }

     /**
     * Compare this to another BigInt
     * @param n the BigInt value to compare with
     * @param check_signs include sign in comparison?
     * @result if (this<n) return -1, if (this>n) return 1, if both
     * values are identical return 0 [like Perl's <=> operator]
     */
     int32_t cmp(const BigInt& n, bool check_signs = true) const;

     /**
     * Compare this to another BigInt
     * @param n the BigInt value to compare with
     * @result true if this == n or false otherwise
     */
     bool is_equal(const BigInt& n) const;

     /**
     * Compare this to another BigInt
     * @param n the BigInt value to compare with
     * @result true if this < n or false otherwise
     */
     bool is_less_than(const BigInt& n) const;

     /**
     * Compare this to an integer
     * @param n the value to compare with
     * @result if (this<n) return -1, if (this>n) return 1, if both
     * values are identical return 0 [like Perl's <=> operator]
     */
     int32_t cmp_word(word n) const;

     /**
     * Test if the integer has an even value
     * @result true if the integer is even, false otherwise
     */
     bool is_even() const { return (get_bit(0) == 0); }

     /**
     * Test if the integer has an odd value
     * @result true if the integer is odd, false otherwise
     */
     bool is_odd()  const { return (get_bit(0) == 1); }

     /**
     * Test if the integer is not zero
     * @result true if the integer is non-zero, false otherwise
     */
     bool is_nonzero() const { return (!is_zero()); }

     /**
     * Test if the integer is zero
     * @result true if the integer is zero, false otherwise
     */
     bool is_zero() const
        {
        return (sig_words() == 0);
        }

     /**
     * Set bit at specified position
     * @param n bit position to set
     */
     void set_bit(size_t n)
        {
        conditionally_set_bit(n, true);
        }

     /**
     * Conditionally set bit at specified position. Note if set_it is
     * false, nothing happens, and if the bit is already set, it
     * remains set.
     *
     * @param n bit position to set
     * @param set_it if the bit should be set
     */
     void conditionally_set_bit(size_t n, bool set_it);

     /**
     * Clear bit at specified position
     * @param n bit position to clear
     */
     void clear_bit(size_t n);

     /**
     * Clear all but the lowest n bits
     * @param n amount of bits to keep
     */
     void mask_bits(size_t n)
        {
        m_data.mask_bits(n);
        }

     /**
     * Return bit value at specified position
     * @param n the bit offset to test
     * @result true, if the bit at position n is set, false otherwise
     */
     bool get_bit(size_t n) const
        {
        return ((word_at(n / BOTAN_MP_WORD_BITS) >> (n % BOTAN_MP_WORD_BITS)) & 1);
        }

     /**
     * Return (a maximum of) 32 bits of the complete value
     * @param offset the offset to start extracting
     * @param length amount of bits to extract (starting at offset)
     * @result the integer extracted from the register starting at
     * offset with specified length
     */
     uint32_t get_substring(size_t offset, size_t length) const;

     /**
     * Convert this value into a uint32_t, if it is in the range
     * [0 ... 2**32-1], or otherwise throw an exception.
     * @result the value as a uint32_t if conversion is possible
     */
     uint32_t to_u32bit() const;

     /**
     * Convert this value to a decimal string.
     * Warning: decimal conversions are relatively slow
     */
     std::string to_dec_string() const;

     /**
     * Convert this value to a hexadecimal string.
     */
     std::string to_hex_string() const;

     /**
     * @param n the offset to get a byte from
     * @result byte at offset n
     */
     uint8_t byte_at(size_t n) const;

     /**
     * Return the word at a specified position of the internal register
     * @param n position in the register
     * @return value at position n
     */
     word word_at(size_t n) const
        {
        return m_data.get_word_at(n);
        }

     void set_word_at(size_t i, word w)
        {
        m_data.set_word_at(i, w);
        }

     void set_words(const word w[], size_t len)
        {
        m_data.set_words(w, len);
        }

     /**
     * Tests if the sign of the integer is negative
     * @result true, iff the integer has a negative sign
     */
     bool is_negative() const { return (sign() == Negative); }

     /**
     * Tests if the sign of the integer is positive
     * @result true, iff the integer has a positive sign
     */
     bool is_positive() const { return (sign() == Positive); }

     /**
     * Return the sign of the integer
     * @result the sign of the integer
     */
     Sign sign() const { return (m_signedness); }

     /**
     * @result the opposite sign of the represented integer value
     */
     Sign reverse_sign() const
        {
        if(sign() == Positive)
           return Negative;
        return Positive;
        }

     /**
     * Flip the sign of this BigInt
     */
     void flip_sign()
        {
        set_sign(reverse_sign());
        }

     /**
     * Set sign of the integer
     * @param sign new Sign to set
     */
     void set_sign(Sign sign)
        {
        if(sign == Negative && is_zero())
           sign = Positive;

        m_signedness = sign;
        }

     /**
     * @result absolute (positive) value of this
     */
     BigInt abs() const;

     /**
     * Give size of internal register
     * @result size of internal register in words
     */
     size_t size() const { return m_data.size(); }

     /**
     * Return how many words we need to hold this value
     * @result significant words of the represented integer value
     */
     size_t sig_words() const
        {
        return m_data.sig_words();
        }

     /**
     * Give byte length of the integer
     * @result byte length of the represented integer value
     */
     size_t bytes() const;

     /**
     * Get the bit length of the integer
     * @result bit length of the represented integer value
     */
     size_t bits() const;

     /**
     * Get the number of high bits unset in the top (allocated) word
     * of this integer. Returns BOTAN_MP_WORD_BITS only iff *this is
     * zero. Ignores sign.
     */
     size_t top_bits_free() const;

     /**
     * Return a mutable pointer to the register
     * @result a pointer to the start of the internal register
     */
     word* mutable_data() { return m_data.mutable_data(); }

     /**
     * Return a const pointer to the register
     * @result a pointer to the start of the internal register
     */
     const word* data() const { return m_data.const_data(); }

     /**
     * Don't use this function in application code
     */
     secure_vector<word>& get_word_vector() { return m_data.mutable_vector(); }

     /**
     * Don't use this function in application code
     */
     const secure_vector<word>& get_word_vector() const { return m_data.const_vector(); }

     /**
     * Increase internal register buffer to at least n words
     * @param n new size of register
     */
     void grow_to(size_t n) const { m_data.grow_to(n); }

     /**
     * Resize the vector to the minimum word size to hold the integer, or
     * min_size words, whichever is larger
     */
     void BOTAN_DEPRECATED("Use resize if required") shrink_to_fit(size_t min_size = 0)
        {
        m_data.shrink_to_fit(min_size);
        }

     void resize(size_t s) { m_data.resize(s); }

     /**
     * Fill BigInt with a random number with size of bitsize
     *
     * If \p set_high_bit is true, the highest bit will be set, which causes
     * the entropy to be \a bits-1. Otherwise the highest bit is randomly chosen
     * by the rng, causing the entropy to be \a bits.
     *
     * @param rng the random number generator to use
     * @param bitsize number of bits the created random value should have
     * @param set_high_bit if true, the highest bit is always set
     */
     void randomize(RandomNumberGenerator& rng, size_t bitsize, bool set_high_bit = true);

     /**
     * Store BigInt-value in a given byte array
     * @param buf destination byte array for the integer value
     */
     void binary_encode(uint8_t buf[]) const;

     /**
     * Store BigInt-value in a given byte array. If len is less than
     * the size of the value, then it will be truncated. If len is
     * greater than the size of the value, it will be zero-padded.
     * If len exactly equals this->bytes(), this function behaves identically
     * to binary_encode.
     *
     * @param buf destination byte array for the integer value
     * @param len how many bytes to write
     */
     void binary_encode(uint8_t buf[], size_t len) const;

     /**
     * Read integer value from a byte array with given size
     * @param buf byte array buffer containing the integer
     * @param length size of buf
     */
     void binary_decode(const uint8_t buf[], size_t length);

     /**
     * Read integer value from a byte vector
     * @param buf the vector to load from
     */
     template<typename Alloc>
     void binary_decode(const std::vector<uint8_t, Alloc>& buf)
        {
        binary_decode(buf.data(), buf.size());
        }

     /**
     * @param base the base to measure the size for
     * @return size of this integer in base base
     *
     * Deprecated. This is only needed when using the `encode` and
     * `encode_locked` functions, which are also deprecated.
     */
     BOTAN_DEPRECATED("See comments on declaration")
     size_t encoded_size(Base base = Binary) const;

     /**
     * Place the value into out, zero-padding up to size words
     * Throw if *this cannot be represented in size words
     */
     void encode_words(word out[], size_t size) const;

     /**
     * If predicate is true assign other to *this
     * Uses a masked operation to avoid side channels
     */
     void ct_cond_assign(bool predicate, const BigInt& other);

     /**
     * If predicate is true swap *this and other
     * Uses a masked operation to avoid side channels
     */
     void ct_cond_swap(bool predicate, BigInt& other);

     /**
     * If predicate is true add value to *this
     */
     void ct_cond_add(bool predicate, const BigInt& value);

     /**
     * If predicate is true flip the sign of *this
     */
     void cond_flip_sign(bool predicate);

#if defined(BOTAN_HAS_VALGRIND)
     void const_time_poison() const;
     void const_time_unpoison() const;
#else
     void const_time_poison() const {}
     void const_time_unpoison() const {}
#endif

     /**
     * @param rng a random number generator
     * @param min the minimum value (must be non-negative)
     * @param max the maximum value (must be non-negative and > min)
     * @return random integer in [min,max)
     */
     static BigInt random_integer(RandomNumberGenerator& rng,
                                  const BigInt& min,
                                  const BigInt& max);

     /**
     * Create a power of two
     * @param n the power of two to create
     * @return bigint representing 2^n
     */
     static BigInt power_of_2(size_t n)
        {
        BigInt b;
        b.set_bit(n);
        return b;
        }

     /**
     * Encode the integer value from a BigInt to a std::vector of bytes
     * @param n the BigInt to use as integer source
     * @result secure_vector of bytes containing the bytes of the integer
     */
     static std::vector<uint8_t> encode(const BigInt& n)
        {
        std::vector<uint8_t> output(n.bytes());
        n.binary_encode(output.data());
        return output;
        }

     /**
     * Encode the integer value from a BigInt to a secure_vector of bytes
     * @param n the BigInt to use as integer source
     * @result secure_vector of bytes containing the bytes of the integer
     */
     static secure_vector<uint8_t> encode_locked(const BigInt& n)
        {
        secure_vector<uint8_t> output(n.bytes());
        n.binary_encode(output.data());
        return output;
        }

     /**
     * Encode the integer value from a BigInt to a byte array
     * @param buf destination byte array for the encoded integer
     * @param n the BigInt to use as integer source
     */
     static BOTAN_DEPRECATED("Use n.binary_encode") void encode(uint8_t buf[], const BigInt& n)
        {
        n.binary_encode(buf);
        }

     /**
     * Create a BigInt from an integer in a byte array
     * @param buf the binary value to load
     * @param length size of buf
     * @result BigInt representing the integer in the byte array
     */
     static BigInt decode(const uint8_t buf[], size_t length)
        {
        return BigInt(buf, length);
        }

     /**
     * Create a BigInt from an integer in a byte array
     * @param buf the binary value to load
     * @result BigInt representing the integer in the byte array
     */
     template<typename Alloc>
     static BigInt decode(const std::vector<uint8_t, Alloc>& buf)
        {
        return BigInt(buf);
        }

     /**
     * Encode the integer value from a BigInt to a std::vector of bytes
     * @param n the BigInt to use as integer source
     * @param base number-base of resulting byte array representation
     * @result secure_vector of bytes containing the integer with given base
     *
     * Deprecated. If you need Binary, call the version of encode that doesn't
     * take a Base. If you need Hex or Decimal output, use to_hex_string or
     * to_dec_string resp.
     */
     BOTAN_DEPRECATED("See comments on declaration")
     static std::vector<uint8_t> encode(const BigInt& n, Base base);

     /**
     * Encode the integer value from a BigInt to a secure_vector of bytes
     * @param n the BigInt to use as integer source
     * @param base number-base of resulting byte array representation
     * @result secure_vector of bytes containing the integer with given base
     *
     * Deprecated. If you need Binary, call the version of encode_locked that
     * doesn't take a Base. If you need Hex or Decimal output, use to_hex_string
     * or to_dec_string resp.
     */
     BOTAN_DEPRECATED("See comments on declaration")
     static secure_vector<uint8_t> encode_locked(const BigInt& n,
                                                 Base base);

     /**
     * Encode the integer value from a BigInt to a byte array
     * @param buf destination byte array for the encoded integer
     * value with given base
     * @param n the BigInt to use as integer source
     * @param base number-base of resulting byte array representation
     *
     * Deprecated. If you need Binary, call binary_encode. If you need
     * Hex or Decimal output, use to_hex_string or to_dec_string resp.
     */
     BOTAN_DEPRECATED("See comments on declaration")
     static void encode(uint8_t buf[], const BigInt& n, Base base);

     /**
     * Create a BigInt from an integer in a byte array
     * @param buf the binary value to load
     * @param length size of buf
     * @param base number-base of the integer in buf
     * @result BigInt representing the integer in the byte array
     */
     static BigInt decode(const uint8_t buf[], size_t length,
                          Base base);

     /**
     * Create a BigInt from an integer in a byte array
     * @param buf the binary value to load
     * @param base number-base of the integer in buf
     * @result BigInt representing the integer in the byte array
     */
     template<typename Alloc>
     static BigInt decode(const std::vector<uint8_t, Alloc>& buf, Base base)
        {
        if(base == Binary)
           return BigInt(buf);
        return BigInt::decode(buf.data(), buf.size(), base);
        }

     /**
     * Encode a BigInt to a byte array according to IEEE 1363
     * @param n the BigInt to encode
     * @param bytes the length of the resulting secure_vector<uint8_t>
     * @result a secure_vector<uint8_t> containing the encoded BigInt
     */
     static secure_vector<uint8_t> encode_1363(const BigInt& n, size_t bytes);

     static void encode_1363(uint8_t out[], size_t bytes, const BigInt& n);

     /**
     * Encode two BigInt to a byte array according to IEEE 1363
     * @param n1 the first BigInt to encode
     * @param n2 the second BigInt to encode
     * @param bytes the length of the encoding of each single BigInt
     * @result a secure_vector<uint8_t> containing the concatenation of the two encoded BigInt
     */
     static secure_vector<uint8_t> encode_fixed_length_int_pair(const BigInt& n1, const BigInt& n2, size_t bytes);

     /**
     * Set output = vec[idx].m_reg in constant time
     *
     * All elements of vec must have the same size, and output must be
     * pre-allocated with the same size.
     */
     static void BOTAN_DEPRECATED("No longer in use") const_time_lookup(
        secure_vector<word>& output,
        const std::vector<BigInt>& vec,
        size_t idx);

   private:

     class Data
        {
        public:
           word* mutable_data()
              {
              invalidate_sig_words();
              return m_reg.data();
              }

           const word* const_data() const
              {
              return m_reg.data();
              }

           secure_vector<word>& mutable_vector()
              {
              invalidate_sig_words();
              return m_reg;
              }

           const secure_vector<word>& const_vector() const
              {
              return m_reg;
              }

           word get_word_at(size_t n) const
              {
              if(n < m_reg.size())
                 return m_reg[n];
              return 0;
              }

           void set_word_at(size_t i, word w)
              {
              invalidate_sig_words();
              if(i >= m_reg.size())
                 {
                 if(w == 0)
                    return;
                 grow_to(i + 1);
                 }
              m_reg[i] = w;
              }

           void set_words(const word w[], size_t len)
              {
              invalidate_sig_words();
              m_reg.assign(w, w + len);
              }

           void set_to_zero()
              {
              m_reg.resize(m_reg.capacity());
              clear_mem(m_reg.data(), m_reg.size());
              m_sig_words = 0;
              }

           void set_size(size_t s)
              {
              invalidate_sig_words();
              clear_mem(m_reg.data(), m_reg.size());
              m_reg.resize(s + (8 - (s % 8)));
              }

           void mask_bits(size_t n)
              {
              if(n == 0) { return set_to_zero(); }

              const size_t top_word = n / BOTAN_MP_WORD_BITS;

              // if(top_word < sig_words()) ?
              if(top_word < size())
                 {
                 const word mask = (static_cast<word>(1) << (n % BOTAN_MP_WORD_BITS)) - 1;
                 const size_t len = size() - (top_word + 1);
                 if(len > 0)
                    {
                    clear_mem(&m_reg[top_word+1], len);
                    }
                 m_reg[top_word] &= mask;
                 invalidate_sig_words();
                 }
              }

           void grow_to(size_t n) const
              {
              if(n > size())
                 {
                 if(n <= m_reg.capacity())
                    m_reg.resize(n);
                 else
                    m_reg.resize(n + (8 - (n % 8)));
                 }
              }

           size_t size() const { return m_reg.size(); }

           void shrink_to_fit(size_t min_size = 0)
              {
              const size_t words = std::max(min_size, sig_words());
              m_reg.resize(words);
              }

           void resize(size_t s)
              {
              m_reg.resize(s);
              }

           void swap(Data& other)
              {
              m_reg.swap(other.m_reg);
              std::swap(m_sig_words, other.m_sig_words);
              }

           void swap(secure_vector<word>& reg)
              {
              m_reg.swap(reg);
              invalidate_sig_words();
              }

           void invalidate_sig_words() const
              {
              m_sig_words = sig_words_npos;
              }

           size_t sig_words() const
              {
              if(m_sig_words == sig_words_npos)
                 {
                 m_sig_words = calc_sig_words();
                 }
              else
                 {
                 BOTAN_DEBUG_ASSERT(m_sig_words == calc_sig_words());
                 }
              return m_sig_words;
              }
        private:
           static const size_t sig_words_npos = static_cast<size_t>(-1);

           size_t calc_sig_words() const;

           mutable secure_vector<word> m_reg;
           mutable size_t m_sig_words = sig_words_npos;
        };

      Data m_data;
      Sign m_signedness = Positive;
   };

/*
* Arithmetic Operators
*/
inline BigInt operator+(const BigInt& x, const BigInt& y)
   {
   return BigInt::add2(x, y.data(), y.sig_words(), y.sign());
   }

inline BigInt operator+(const BigInt& x, word y)
   {
   return BigInt::add2(x, &y, 1, BigInt::Positive);
   }

inline BigInt operator+(word x, const BigInt& y)
   {
   return y + x;
   }

inline BigInt operator-(const BigInt& x, const BigInt& y)
   {
   return BigInt::add2(x, y.data(), y.sig_words(), y.reverse_sign());
   }

inline BigInt operator-(const BigInt& x, word y)
   {
   return BigInt::add2(x, &y, 1, BigInt::Negative);
   }

BigInt BOTAN_PUBLIC_API(2,0) operator*(const BigInt& x, const BigInt& y);
BigInt BOTAN_PUBLIC_API(2,8) operator*(const BigInt& x, word y);
inline BigInt operator*(word x, const BigInt& y) { return y*x; }

BigInt BOTAN_PUBLIC_API(2,0) operator/(const BigInt& x, const BigInt& d);
BigInt BOTAN_PUBLIC_API(2,0) operator/(const BigInt& x, word m);
BigInt BOTAN_PUBLIC_API(2,0) operator%(const BigInt& x, const BigInt& m);
word   BOTAN_PUBLIC_API(2,0) operator%(const BigInt& x, word m);
BigInt BOTAN_PUBLIC_API(2,0) operator<<(const BigInt& x, size_t n);
BigInt BOTAN_PUBLIC_API(2,0) operator>>(const BigInt& x, size_t n);

/*
* Comparison Operators
*/
inline bool operator==(const BigInt& a, const BigInt& b)
   { return a.is_equal(b); }
inline bool operator!=(const BigInt& a, const BigInt& b)
   { return !a.is_equal(b); }
inline bool operator<=(const BigInt& a, const BigInt& b)
   { return (a.cmp(b) <= 0); }
inline bool operator>=(const BigInt& a, const BigInt& b)
   { return (a.cmp(b) >= 0); }
inline bool operator<(const BigInt& a, const BigInt& b)
   { return a.is_less_than(b); }
inline bool operator>(const BigInt& a, const BigInt& b)
   { return b.is_less_than(a); }

inline bool operator==(const BigInt& a, word b)
   { return (a.cmp_word(b) == 0); }
inline bool operator!=(const BigInt& a, word b)
   { return (a.cmp_word(b) != 0); }
inline bool operator<=(const BigInt& a, word b)
   { return (a.cmp_word(b) <= 0); }
inline bool operator>=(const BigInt& a, word b)
   { return (a.cmp_word(b) >= 0); }
inline bool operator<(const BigInt& a, word b)
   { return (a.cmp_word(b) < 0); }
inline bool operator>(const BigInt& a, word b)
   { return (a.cmp_word(b) > 0); }

/*
* I/O Operators
*/
BOTAN_PUBLIC_API(2,0) std::ostream& operator<<(std::ostream&, const BigInt&);
BOTAN_PUBLIC_API(2,0) std::istream& operator>>(std::istream&, BigInt&);

}

namespace std {

template<>
inline void swap<Botan::BigInt>(Botan::BigInt& x, Botan::BigInt& y)
   {
   x.swap(y);
   }

}

namespace Botan {

class RandomNumberGenerator;

/**
* Fused multiply-add
* @param a an integer
* @param b an integer
* @param c an integer
* @return (a*b)+c
*/
BigInt BOTAN_PUBLIC_API(2,0) BOTAN_DEPRECATED("Just use (a*b)+c")
   mul_add(const BigInt& a,
           const BigInt& b,
           const BigInt& c);

/**
* Fused subtract-multiply
* @param a an integer
* @param b an integer
* @param c an integer
* @return (a-b)*c
*/
BigInt BOTAN_PUBLIC_API(2,0) BOTAN_DEPRECATED("Just use (a-b)*c")
   sub_mul(const BigInt& a,
           const BigInt& b,
           const BigInt& c);

/**
* Fused multiply-subtract
* @param a an integer
* @param b an integer
* @param c an integer
* @return (a*b)-c
*/
BigInt BOTAN_PUBLIC_API(2,0) BOTAN_DEPRECATED("Just use (a*b)-c")
   mul_sub(const BigInt& a,
           const BigInt& b,
           const BigInt& c);

/**
* Return the absolute value
* @param n an integer
* @return absolute value of n
*/
inline BigInt abs(const BigInt& n) { return n.abs(); }

/**
* Compute the greatest common divisor
* @param x a positive integer
* @param y a positive integer
* @return gcd(x,y)
*/
BigInt BOTAN_PUBLIC_API(2,0) gcd(const BigInt& x, const BigInt& y);

/**
* Least common multiple
* @param x a positive integer
* @param y a positive integer
* @return z, smallest integer such that z % x == 0 and z % y == 0
*/
BigInt BOTAN_PUBLIC_API(2,0) lcm(const BigInt& x, const BigInt& y);

/**
* @param x an integer
* @return (x*x)
*/
BigInt BOTAN_PUBLIC_API(2,0) square(const BigInt& x);

/**
* Modular inversion. This algorithm is const time with respect to x,
* as long as x is less than modulus. It also avoids leaking
* information about the modulus, except that it does leak which of 3
* categories the modulus is in: an odd integer, a power of 2, or some
* other even number, and if the modulus is even, leaks the power of 2
* which divides the modulus.
*
* @param x a positive integer
* @param modulus a positive integer
* @return y st (x*y) % modulus == 1 or 0 if no such value
*/
BigInt BOTAN_PUBLIC_API(2,0) inverse_mod(const BigInt& x,
                                         const BigInt& modulus);

/**
* Deprecated modular inversion function. Use inverse_mod instead.
* @param x a positive integer
* @param modulus a positive integer
* @return y st (x*y) % modulus == 1 or 0 if no such value
*/
BigInt BOTAN_DEPRECATED_API("Use inverse_mod") inverse_euclid(const BigInt& x, const BigInt& modulus);

/**
* Deprecated modular inversion function. Use inverse_mod instead.
*/
BigInt BOTAN_DEPRECATED_API("Use inverse_mod") ct_inverse_mod_odd_modulus(const BigInt& x, const BigInt& modulus);

/**
* Return a^-1 * 2^k mod b
* Returns k, between n and 2n
* Not const time
*/
size_t BOTAN_PUBLIC_API(2,0) BOTAN_DEPRECATED("Use inverse_mod")
   almost_montgomery_inverse(BigInt& result,
                             const BigInt& a,
                             const BigInt& b);

/**
* Call almost_montgomery_inverse and correct the result to a^-1 mod b
*/
BigInt BOTAN_PUBLIC_API(2,0) BOTAN_DEPRECATED("Use inverse_mod")
   normalized_montgomery_inverse(const BigInt& a, const BigInt& b);


/**
* Compute the Jacobi symbol. If n is prime, this is equivalent
* to the Legendre symbol.
* @see http://mathworld.wolfram.com/JacobiSymbol.html
*
* @param a is a non-negative integer
* @param n is an odd integer > 1
* @return (n / m)
*/
int32_t BOTAN_PUBLIC_API(2,0) jacobi(const BigInt& a, const BigInt& n);

/**
* Modular exponentation
* @param b an integer base
* @param x a positive exponent
* @param m a positive modulus
* @return (b^x) % m
*/
BigInt BOTAN_PUBLIC_API(2,0) power_mod(const BigInt& b,
                                       const BigInt& x,
                                       const BigInt& m);

/**
* Compute the square root of x modulo a prime using the
* Tonelli-Shanks algorithm
*
* @param x the input
* @param p the prime
* @return y such that (y*y)%p == x, or -1 if no such integer
*/
BigInt BOTAN_PUBLIC_API(2,0) ressol(const BigInt& x, const BigInt& p);

/*
* Compute -input^-1 mod 2^MP_WORD_BITS. Throws an exception if input
* is even. If input is odd, then input and 2^n are relatively prime
* and an inverse exists.
*/
word BOTAN_PUBLIC_API(2,0) BOTAN_DEPRECATED("Use inverse_mod")
   monty_inverse(word input);

/**
* @param x an integer
* @return count of the low zero bits in x, or, equivalently, the
*         largest value of n such that 2^n divides x evenly. Returns
*         zero if x is equal to zero.
*/
size_t BOTAN_PUBLIC_API(2,0) low_zero_bits(const BigInt& x);

/**
* Check for primality
* @param n a positive integer to test for primality
* @param rng a random number generator
* @param prob chance of false positive is bounded by 1/2**prob
* @param is_random true if n was randomly chosen by us
* @return true if all primality tests passed, otherwise false
*/
bool BOTAN_PUBLIC_API(2,0) is_prime(const BigInt& n,
                                    RandomNumberGenerator& rng,
                                    size_t prob = 64,
                                    bool is_random = false);

/**
* Test if the positive integer x is a perfect square ie if there
* exists some positive integer y st y*y == x
* See FIPS 186-4 sec C.4
* @return 0 if the integer is not a perfect square, otherwise
*         returns the positive y st y*y == x
*/
BigInt BOTAN_PUBLIC_API(2,8) is_perfect_square(const BigInt& x);

inline bool BOTAN_DEPRECATED("Use is_prime")
   quick_check_prime(const BigInt& n, RandomNumberGenerator& rng)
   { return is_prime(n, rng, 32); }

inline bool BOTAN_DEPRECATED("Use is_prime")
   check_prime(const BigInt& n, RandomNumberGenerator& rng)
   { return is_prime(n, rng, 56); }

inline bool BOTAN_DEPRECATED("Use is_prime")
   verify_prime(const BigInt& n, RandomNumberGenerator& rng)
   { return is_prime(n, rng, 80); }

/**
* Randomly generate a prime suitable for discrete logarithm parameters
* @param rng a random number generator
* @param bits how large the resulting prime should be in bits
* @param coprime a positive integer that (prime - 1) should be coprime to
* @param equiv a non-negative number that the result should be
               equivalent to modulo equiv_mod
* @param equiv_mod the modulus equiv should be checked against
* @param prob use test so false positive is bounded by 1/2**prob
* @return random prime with the specified criteria
*/
BigInt BOTAN_PUBLIC_API(2,0) random_prime(RandomNumberGenerator& rng,
                                          size_t bits,
                                          const BigInt& coprime = 0,
                                          size_t equiv = 1,
                                          size_t equiv_mod = 2,
                                          size_t prob = 128);

/**
* Generate a prime suitable for RSA p/q
* @param keygen_rng a random number generator
* @param prime_test_rng a random number generator
* @param bits how large the resulting prime should be in bits (must be >= 512)
* @param coprime a positive integer that (prime - 1) should be coprime to
* @param prob use test so false positive is bounded by 1/2**prob
* @return random prime with the specified criteria
*/
BigInt BOTAN_PUBLIC_API(2,7) generate_rsa_prime(RandomNumberGenerator& keygen_rng,
                                                RandomNumberGenerator& prime_test_rng,
                                                size_t bits,
                                                const BigInt& coprime,
                                                size_t prob = 128);

/**
* Return a 'safe' prime, of the form p=2*q+1 with q prime
* @param rng a random number generator
* @param bits is how long the resulting prime should be
* @return prime randomly chosen from safe primes of length bits
*/
BigInt BOTAN_PUBLIC_API(2,0) random_safe_prime(RandomNumberGenerator& rng,
                                               size_t bits);

/**
* Generate DSA parameters using the FIPS 186 kosherizer
* @param rng a random number generator
* @param p_out where the prime p will be stored
* @param q_out where the prime q will be stored
* @param pbits how long p will be in bits
* @param qbits how long q will be in bits
* @return random seed used to generate this parameter set
*/
std::vector<uint8_t> BOTAN_PUBLIC_API(2,0) BOTAN_DEPRECATED("Use DL_Group")
generate_dsa_primes(RandomNumberGenerator& rng,
                    BigInt& p_out, BigInt& q_out,
                    size_t pbits, size_t qbits);

/**
* Generate DSA parameters using the FIPS 186 kosherizer
* @param rng a random number generator
* @param p_out where the prime p will be stored
* @param q_out where the prime q will be stored
* @param pbits how long p will be in bits
* @param qbits how long q will be in bits
* @param seed the seed used to generate the parameters
* @param offset optional offset from seed to start searching at
* @return true if seed generated a valid DSA parameter set, otherwise
          false. p_out and q_out are only valid if true was returned.
*/
bool BOTAN_PUBLIC_API(2,0) BOTAN_DEPRECATED("Use DL_Group")
generate_dsa_primes(RandomNumberGenerator& rng,
                    BigInt& p_out, BigInt& q_out,
                    size_t pbits, size_t qbits,
                    const std::vector<uint8_t>& seed,
                    size_t offset = 0);

/**
* The size of the PRIMES[] array
*/
const size_t PRIME_TABLE_SIZE = 6541;

/**
* A const array of all odd primes less than 65535
*/
extern const uint16_t BOTAN_PUBLIC_API(2,0) PRIMES[];

}

namespace Botan {

/**
* Modular Reducer (using Barrett's technique)
*/
class BOTAN_PUBLIC_API(2,0) Modular_Reducer
   {
   public:
      const BigInt& get_modulus() const { return m_modulus; }

      BigInt reduce(const BigInt& x) const;

      /**
      * Multiply mod p
      * @param x the first operand
      * @param y the second operand
      * @return (x * y) % p
      */
      BigInt multiply(const BigInt& x, const BigInt& y) const
         { return reduce(x * y); }

      /**
      * Square mod p
      * @param x the value to square
      * @return (x * x) % p
      */
      BigInt square(const BigInt& x) const
         { return reduce(Botan::square(x)); }

      /**
      * Cube mod p
      * @param x the value to cube
      * @return (x * x * x) % p
      */
      BigInt cube(const BigInt& x) const
         { return multiply(x, this->square(x)); }

      /**
      * Low level reduction function. Mostly for internal use.
      * Sometimes useful for performance by reducing temporaries
      * Reduce x mod p and place the output in out. ** X and out must not reference each other **
      * ws is a temporary workspace.
      */
      void reduce(BigInt& out, const BigInt& x, secure_vector<word>& ws) const;

      bool initialized() const { return (m_mod_words != 0); }

      Modular_Reducer() { m_mod_words = 0; }
      explicit Modular_Reducer(const BigInt& mod);
   private:
      BigInt m_modulus, m_mu;
      size_t m_mod_words;
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(blinding.h)

namespace Botan {

class RandomNumberGenerator;

/**
* Blinding Function Object.
*/
class BOTAN_PUBLIC_API(2,0) Blinder final
   {
   public:
      /**
      * Blind a value.
      * The blinding nonce k is freshly generated after
      * BOTAN_BLINDING_REINIT_INTERVAL calls to blind().
      * BOTAN_BLINDING_REINIT_INTERVAL = 0 means a fresh
      * nonce is only generated once. On every other call,
      * an updated nonce is used for blinding: k' = k*k mod n.
      * @param x value to blind
      * @return blinded value
      */
      BigInt blind(const BigInt& x) const;

      /**
      * Unblind a value.
      * @param x value to unblind
      * @return unblinded value
      */
      BigInt unblind(const BigInt& x) const;

      /**
      * @param modulus the modulus
      * @param rng the RNG to use for generating the nonce
      * @param fwd_func a function that calculates the modular
      * exponentiation of the public exponent and the given value (the nonce)
      * @param inv_func a function that calculates the modular inverse
      * of the given value (the nonce)
      */
      Blinder(const BigInt& modulus,
              RandomNumberGenerator& rng,
              std::function<BigInt (const BigInt&)> fwd_func,
              std::function<BigInt (const BigInt&)> inv_func);

      Blinder(const Blinder&) = delete;

      Blinder& operator=(const Blinder&) = delete;

      RandomNumberGenerator& rng() const { return m_rng; }

   private:
      BigInt blinding_nonce() const;

      Modular_Reducer m_reducer;
      RandomNumberGenerator& m_rng;
      std::function<BigInt (const BigInt&)> m_fwd_fn;
      std::function<BigInt (const BigInt&)> m_inv_fn;
      size_t m_modulus_bits = 0;

      mutable BigInt m_e, m_d;
      mutable size_t m_counter = 0;
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(blowfish.h)

namespace Botan {

/**
* Blowfish
*/
class BOTAN_PUBLIC_API(2,0) Blowfish final : public Block_Cipher_Fixed_Params<8, 1, 56>
   {
   public:
      void encrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const override;
      void decrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const override;

      /**
      * Modified EKSBlowfish key schedule, used for bcrypt password hashing
      */
      void salted_set_key(const uint8_t key[], size_t key_length,
                          const uint8_t salt[], size_t salt_length,
                          const size_t workfactor, bool salt_first = false);

      BOTAN_DEPRECATED("Use Blowfish::salted_set_key taking salt length")
      void eks_key_schedule(const uint8_t key[], size_t key_length,
                            const uint8_t salt[16], size_t workfactor)
         {
         salted_set_key(key, key_length, salt, 16, workfactor);
         }

      void clear() override;
      std::string name() const override { return "Blowfish"; }
      BlockCipher* clone() const override { return new Blowfish; }
   private:
      void key_schedule(const uint8_t key[], size_t length) override;

      void key_expansion(const uint8_t key[],
                         size_t key_length,
                         const uint8_t salt[],
                         size_t salt_length);

      void generate_sbox(secure_vector<uint32_t>& box,
                         uint32_t& L, uint32_t& R,
                         const uint8_t salt[],
                         size_t salt_length,
                         size_t salt_off) const;

      secure_vector<uint32_t> m_S, m_P;
   };

}

#if defined(BOTAN_BUILD_COMPILER_IS_MSVC)
  #include <stdlib.h>
#endif

BOTAN_FUTURE_INTERNAL_HEADER(bswap.h)

namespace Botan {

/**
* Swap a 16 bit integer
*/
inline uint16_t reverse_bytes(uint16_t val)
   {
#if defined(BOTAN_BUILD_COMPILER_IS_GCC) || defined(BOTAN_BUILD_COMPILER_IS_CLANG) || defined(BOTAN_BUILD_COMPILER_IS_XLC)
   return __builtin_bswap16(val);
#else
   return static_cast<uint16_t>((val << 8) | (val >> 8));
#endif
   }

/**
* Swap a 32 bit integer
*/
inline uint32_t reverse_bytes(uint32_t val)
   {
#if defined(BOTAN_BUILD_COMPILER_IS_GCC) || defined(BOTAN_BUILD_COMPILER_IS_CLANG) || defined(BOTAN_BUILD_COMPILER_IS_XLC)
   return __builtin_bswap32(val);

#elif defined(BOTAN_BUILD_COMPILER_IS_MSVC)
   return _byteswap_ulong(val);

#elif defined(BOTAN_USE_GCC_INLINE_ASM) && defined(BOTAN_TARGET_CPU_IS_X86_FAMILY)

   // GCC-style inline assembly for x86 or x86-64
   asm("bswapl %0" : "=r" (val) : "0" (val));
   return val;

#else
   // Generic implementation
   uint16_t hi = static_cast<uint16_t>(val >> 16);
   uint16_t lo = static_cast<uint16_t>(val);

   hi = reverse_bytes(hi);
   lo = reverse_bytes(lo);

   return (static_cast<uint32_t>(lo) << 16) | hi;
#endif
   }

/**
* Swap a 64 bit integer
*/
inline uint64_t reverse_bytes(uint64_t val)
   {
#if defined(BOTAN_BUILD_COMPILER_IS_GCC) || defined(BOTAN_BUILD_COMPILER_IS_CLANG) || defined(BOTAN_BUILD_COMPILER_IS_XLC)
   return __builtin_bswap64(val);

#elif defined(BOTAN_BUILD_COMPILER_IS_MSVC)
   return _byteswap_uint64(val);

#elif defined(BOTAN_USE_GCC_INLINE_ASM) && defined(BOTAN_TARGET_ARCH_IS_X86_64)
   // GCC-style inline assembly for x86-64
   asm("bswapq %0" : "=r" (val) : "0" (val));
   return val;

#else
   /* Generic implementation. Defined in terms of 32-bit bswap so any
    * optimizations in that version can help.
    */

   uint32_t hi = static_cast<uint32_t>(val >> 32);
   uint32_t lo = static_cast<uint32_t>(val);

   hi = reverse_bytes(hi);
   lo = reverse_bytes(lo);

   return (static_cast<uint64_t>(lo) << 32) | hi;
#endif
   }

/**
* Swap 4 Ts in an array
*/
template<typename T>
inline void bswap_4(T x[4])
   {
   x[0] = reverse_bytes(x[0]);
   x[1] = reverse_bytes(x[1]);
   x[2] = reverse_bytes(x[2]);
   x[3] = reverse_bytes(x[3]);
   }

}

namespace Botan {

/**
* This class represents any kind of computation which uses an internal
* state, such as hash functions or MACs
*/
class BOTAN_PUBLIC_API(2,0) Buffered_Computation
   {
   public:
      /**
      * @return length of the output of this function in bytes
      */
      virtual size_t output_length() const = 0;

      /**
      * Add new input to process.
      * @param in the input to process as a byte array
      * @param length of param in in bytes
      */
      void update(const uint8_t in[], size_t length) { add_data(in, length); }

      /**
      * Add new input to process.
      * @param in the input to process as a secure_vector
      */
      void update(const secure_vector<uint8_t>& in)
         {
         add_data(in.data(), in.size());
         }

      /**
      * Add new input to process.
      * @param in the input to process as a std::vector
      */
      void update(const std::vector<uint8_t>& in)
         {
         add_data(in.data(), in.size());
         }

      void update_be(uint16_t val);
      void update_be(uint32_t val);
      void update_be(uint64_t val);

      void update_le(uint16_t val);
      void update_le(uint32_t val);
      void update_le(uint64_t val);

      /**
      * Add new input to process.
      * @param str the input to process as a std::string. Will be interpreted
      * as a byte array based on the strings encoding.
      */
      void update(const std::string& str)
         {
         add_data(cast_char_ptr_to_uint8(str.data()), str.size());
         }

      /**
      * Process a single byte.
      * @param in the byte to process
      */
      void update(uint8_t in) { add_data(&in, 1); }

      /**
      * Complete the computation and retrieve the
      * final result.
      * @param out The byte array to be filled with the result.
      * Must be of length output_length()
      */
      void final(uint8_t out[]) { final_result(out); }

      /**
      * Complete the computation and retrieve the
      * final result.
      * @return secure_vector holding the result
      */
      secure_vector<uint8_t> final()
         {
         secure_vector<uint8_t> output(output_length());
         final_result(output.data());
         return output;
         }

      std::vector<uint8_t> final_stdvec()
         {
         std::vector<uint8_t> output(output_length());
         final_result(output.data());
         return output;
         }

      template<typename Alloc>
         void final(std::vector<uint8_t, Alloc>& out)
         {
         out.resize(output_length());
         final_result(out.data());
         }

      /**
      * Update and finalize computation. Does the same as calling update()
      * and final() consecutively.
      * @param in the input to process as a byte array
      * @param length the length of the byte array
      * @result the result of the call to final()
      */
      secure_vector<uint8_t> process(const uint8_t in[], size_t length)
         {
         add_data(in, length);
         return final();
         }

      /**
      * Update and finalize computation. Does the same as calling update()
      * and final() consecutively.
      * @param in the input to process
      * @result the result of the call to final()
      */
      secure_vector<uint8_t> process(const secure_vector<uint8_t>& in)
         {
         add_data(in.data(), in.size());
         return final();
         }

      /**
      * Update and finalize computation. Does the same as calling update()
      * and final() consecutively.
      * @param in the input to process
      * @result the result of the call to final()
      */
      secure_vector<uint8_t> process(const std::vector<uint8_t>& in)
         {
         add_data(in.data(), in.size());
         return final();
         }

      /**
      * Update and finalize computation. Does the same as calling update()
      * and final() consecutively.
      * @param in the input to process as a string
      * @result the result of the call to final()
      */
      secure_vector<uint8_t> process(const std::string& in)
         {
         update(in);
         return final();
         }

      virtual ~Buffered_Computation() = default;
   private:
      /**
      * Add more data to the computation
      * @param input is an input buffer
      * @param length is the length of input in bytes
      */
      virtual void add_data(const uint8_t input[], size_t length) = 0;

      /**
      * Write the final output to out
      * @param out is an output buffer of output_length()
      */
      virtual void final_result(uint8_t out[]) = 0;
   };

}

namespace Botan {

/**
* Struct representing a particular date and time
*/
class BOTAN_PUBLIC_API(2,0) calendar_point
   {
   public:

      /** The year */
      uint32_t get_year() const { return year; }

      /** The month, 1 through 12 for Jan to Dec */
      uint32_t get_month() const { return month; }

      /** The day of the month, 1 through 31 (or 28 or 30 based on month */
      uint32_t get_day() const { return day; }

      /** Hour in 24-hour form, 0 to 23 */
      uint32_t get_hour() const { return hour; }

      /** Minutes in the hour, 0 to 60 */
      uint32_t get_minutes() const { return minutes; }

      /** Seconds in the minute, 0 to 60, but might be slightly
      larger to deal with leap seconds on some systems
      */
      uint32_t get_seconds() const { return seconds; }

      /**
      * Initialize a calendar_point
      * @param y the year
      * @param mon the month
      * @param d the day
      * @param h the hour
      * @param min the minute
      * @param sec the second
      */
      calendar_point(uint32_t y, uint32_t mon, uint32_t d, uint32_t h, uint32_t min, uint32_t sec) :
         year(y), month(mon), day(d), hour(h), minutes(min), seconds(sec) {}

      /**
      * Returns an STL timepoint object
      */
      std::chrono::system_clock::time_point to_std_timepoint() const;

      /**
      * Returns a human readable string of the struct's components.
      * Formatting might change over time. Currently it is RFC339 'iso-date-time'.
      */
      std::string to_string() const;

   BOTAN_DEPRECATED_PUBLIC_MEMBER_VARIABLES:
      /*
      The member variables are public for historical reasons. Use the get_xxx() functions
      defined above. These members will be made private in a future major release.
      */
      uint32_t year;
      uint32_t month;
      uint32_t day;
      uint32_t hour;
      uint32_t minutes;
      uint32_t seconds;
   };

/**
* Convert a time_point to a calendar_point
* @param time_point a time point from the system clock
* @return calendar_point object representing this time point
*/
BOTAN_PUBLIC_API(2,0) calendar_point calendar_value(
   const std::chrono::system_clock::time_point& time_point);

}

BOTAN_FUTURE_INTERNAL_HEADER(mode_pad.h)

namespace Botan {

/**
* Block Cipher Mode Padding Method
* This class is pretty limited, it cannot deal well with
* randomized padding methods, or any padding method that
* wants to add more than one block. For instance, it should
* be possible to define cipher text stealing mode as simply
* a padding mode for CBC, which happens to consume the last
* two block (and requires use of the block cipher).
*/
class BOTAN_PUBLIC_API(2,0) BlockCipherModePaddingMethod
   {
   public:
      /**
      * Add padding bytes to buffer.
      * @param buffer data to pad
      * @param final_block_bytes size of the final block in bytes
      * @param block_size size of each block in bytes
      */
      virtual void add_padding(secure_vector<uint8_t>& buffer,
                               size_t final_block_bytes,
                               size_t block_size) const = 0;

      /**
      * Remove padding bytes from block
      * @param block the last block
      * @param len the size of the block in bytes
      * @return number of data bytes, or if the padding is invalid returns len
      */
      virtual size_t unpad(const uint8_t block[], size_t len) const = 0;

      /**
      * @param block_size of the cipher
      * @return valid block size for this padding mode
      */
      virtual bool valid_blocksize(size_t block_size) const = 0;

      /**
      * @return name of the mode
      */
      virtual std::string name() const = 0;

      /**
      * virtual destructor
      */
      virtual ~BlockCipherModePaddingMethod() = default;
   };

/**
* PKCS#7 Padding
*/
class BOTAN_PUBLIC_API(2,0) PKCS7_Padding final : public BlockCipherModePaddingMethod
   {
   public:
      void add_padding(secure_vector<uint8_t>& buffer,
                       size_t final_block_bytes,
                       size_t block_size) const override;

      size_t unpad(const uint8_t[], size_t) const override;

      bool valid_blocksize(size_t bs) const override { return (bs > 2 && bs < 256); }

      std::string name() const override { return "PKCS7"; }
   };

/**
* ANSI X9.23 Padding
*/
class BOTAN_PUBLIC_API(2,0) ANSI_X923_Padding final : public BlockCipherModePaddingMethod
   {
   public:
      void add_padding(secure_vector<uint8_t>& buffer,
                       size_t final_block_bytes,
                       size_t block_size) const override;

      size_t unpad(const uint8_t[], size_t) const override;

      bool valid_blocksize(size_t bs) const override { return (bs > 2 && bs < 256); }

      std::string name() const override { return "X9.23"; }
   };

/**
* One And Zeros Padding (ISO/IEC 9797-1, padding method 2)
*/
class BOTAN_PUBLIC_API(2,0) OneAndZeros_Padding final : public BlockCipherModePaddingMethod
   {
   public:
      void add_padding(secure_vector<uint8_t>& buffer,
                       size_t final_block_bytes,
                       size_t block_size) const override;

      size_t unpad(const uint8_t[], size_t) const override;

      bool valid_blocksize(size_t bs) const override { return (bs > 2); }

      std::string name() const override { return "OneAndZeros"; }
   };

/**
* ESP Padding (RFC 4304)
*/
class BOTAN_PUBLIC_API(2,0) ESP_Padding final : public BlockCipherModePaddingMethod
   {
   public:
      void add_padding(secure_vector<uint8_t>& buffer,
                       size_t final_block_bytes,
                       size_t block_size) const override;

      size_t unpad(const uint8_t[], size_t) const override;

      bool valid_blocksize(size_t bs) const override { return (bs > 2 && bs < 256); }

      std::string name() const override { return "ESP"; }
   };

/**
* Null Padding
*/
class BOTAN_PUBLIC_API(2,0) Null_Padding final : public BlockCipherModePaddingMethod
   {
   public:
      void add_padding(secure_vector<uint8_t>&, size_t, size_t) const override
         {
         /* no padding */
         }

      size_t unpad(const uint8_t[], size_t size) const override { return size; }

      bool valid_blocksize(size_t) const override { return true; }

      std::string name() const override { return "NoPadding"; }
   };

/**
* Get a block cipher padding mode by name (eg "NoPadding" or "PKCS7")
* @param algo_spec block cipher padding mode name
*/
BOTAN_PUBLIC_API(2,0) BlockCipherModePaddingMethod* get_bc_pad(const std::string& algo_spec);

}

BOTAN_FUTURE_INTERNAL_HEADER(cbc.h)

namespace Botan {

/**
* CBC Mode
*/
class BOTAN_PUBLIC_API(2,0) CBC_Mode : public Cipher_Mode
   {
   public:
      std::string name() const override;

      size_t update_granularity() const override;

      Key_Length_Specification key_spec() const override;

      size_t default_nonce_length() const override;

      bool valid_nonce_length(size_t n) const override;

      void clear() override;

      void reset() override;

   protected:
      CBC_Mode(BlockCipher* cipher, BlockCipherModePaddingMethod* padding);

      const BlockCipher& cipher() const { return *m_cipher; }

      const BlockCipherModePaddingMethod& padding() const
         {
         BOTAN_ASSERT_NONNULL(m_padding);
         return *m_padding;
         }

      size_t block_size() const { return m_block_size; }

      secure_vector<uint8_t>& state() { return m_state; }

      uint8_t* state_ptr() { return m_state.data(); }

   private:
      void start_msg(const uint8_t nonce[], size_t nonce_len) override;

      void key_schedule(const uint8_t key[], size_t length) override;

      std::unique_ptr<BlockCipher> m_cipher;
      std::unique_ptr<BlockCipherModePaddingMethod> m_padding;
      secure_vector<uint8_t> m_state;
      size_t m_block_size;
   };

/**
* CBC Encryption
*/
class BOTAN_PUBLIC_API(2,0) CBC_Encryption : public CBC_Mode
   {
   public:
      /**
      * @param cipher block cipher to use
      * @param padding padding method to use
      */
      CBC_Encryption(BlockCipher* cipher, BlockCipherModePaddingMethod* padding) :
         CBC_Mode(cipher, padding) {}

      size_t process(uint8_t buf[], size_t size) override;

      void finish(secure_vector<uint8_t>& final_block, size_t offset = 0) override;

      size_t output_length(size_t input_length) const override;

      size_t minimum_final_size() const override;
   };

/**
* CBC Encryption with ciphertext stealing (CBC-CS3 variant)
*/
class BOTAN_PUBLIC_API(2,0) CTS_Encryption final : public CBC_Encryption
   {
   public:
      /**
      * @param cipher block cipher to use
      */
      explicit CTS_Encryption(BlockCipher* cipher) : CBC_Encryption(cipher, nullptr) {}

      size_t output_length(size_t input_length) const override;

      void finish(secure_vector<uint8_t>& final_block, size_t offset = 0) override;

      size_t minimum_final_size() const override;

      bool valid_nonce_length(size_t n) const override;
   };

/**
* CBC Decryption
*/
class BOTAN_PUBLIC_API(2,0) CBC_Decryption : public CBC_Mode
   {
   public:
      /**
      * @param cipher block cipher to use
      * @param padding padding method to use
      */
      CBC_Decryption(BlockCipher* cipher, BlockCipherModePaddingMethod* padding) :
         CBC_Mode(cipher, padding), m_tempbuf(update_granularity()) {}

      size_t process(uint8_t buf[], size_t size) override;

      void finish(secure_vector<uint8_t>& final_block, size_t offset = 0) override;

      size_t output_length(size_t input_length) const override;

      size_t minimum_final_size() const override;

      void reset() override;

   private:
      secure_vector<uint8_t> m_tempbuf;
   };

/**
* CBC Decryption with ciphertext stealing (CBC-CS3 variant)
*/
class BOTAN_PUBLIC_API(2,0) CTS_Decryption final : public CBC_Decryption
   {
   public:
      /**
      * @param cipher block cipher to use
      */
      explicit CTS_Decryption(BlockCipher* cipher) : CBC_Decryption(cipher, nullptr) {}

      void finish(secure_vector<uint8_t>& final_block, size_t offset = 0) override;

      size_t minimum_final_size() const override;

      bool valid_nonce_length(size_t n) const override;
   };

}

namespace Botan {

/**
* Certificate validation status code
*/
enum class Certificate_Status_Code {
   OK = 0,
   VERIFIED = 0,

   // Revocation status
   OCSP_RESPONSE_GOOD = 1,
   OCSP_SIGNATURE_OK = 2,
   VALID_CRL_CHECKED = 3,
   OCSP_NO_HTTP = 4,

   // Warnings
   FIRST_WARNING_STATUS = 500,
   CERT_SERIAL_NEGATIVE = 500,
   DN_TOO_LONG = 501,
   OCSP_NO_REVOCATION_URL = 502,
   OCSP_SERVER_NOT_AVAILABLE = 503,

   // Typo versions of above - will be removed in future major release
   OSCP_NO_REVOCATION_URL = 502,
   OSCP_SERVER_NOT_AVAILABLE = 503,

   // Errors
   FIRST_ERROR_STATUS = 1000,

   SIGNATURE_METHOD_TOO_WEAK = 1000,
   UNTRUSTED_HASH = 1001,
   NO_REVOCATION_DATA = 1002,
   NO_MATCHING_CRLDP = 1003,

   // Time problems
   CERT_NOT_YET_VALID = 2000,
   CERT_HAS_EXPIRED = 2001,
   OCSP_NOT_YET_VALID = 2002,
   OCSP_HAS_EXPIRED = 2003,
   CRL_NOT_YET_VALID = 2004,
   CRL_HAS_EXPIRED = 2005,
   OCSP_IS_TOO_OLD = 2006,

   // Chain generation problems
   CERT_ISSUER_NOT_FOUND = 3000,
   CANNOT_ESTABLISH_TRUST = 3001,
   CERT_CHAIN_LOOP = 3002,
   CHAIN_LACKS_TRUST_ROOT = 3003,
   CHAIN_NAME_MISMATCH = 3004,

   // Validation errors
   POLICY_ERROR = 4000,
   INVALID_USAGE = 4001,
   CERT_CHAIN_TOO_LONG = 4002,
   CA_CERT_NOT_FOR_CERT_ISSUER = 4003,
   NAME_CONSTRAINT_ERROR = 4004,

   // Revocation errors
   CA_CERT_NOT_FOR_CRL_ISSUER = 4005,
   OCSP_CERT_NOT_LISTED = 4006,
   OCSP_BAD_STATUS = 4007,

   // Other problems
   CERT_NAME_NOMATCH = 4008,
   UNKNOWN_CRITICAL_EXTENSION = 4009,
   DUPLICATE_CERT_EXTENSION = 4010,
   OCSP_SIGNATURE_ERROR = 4501,
   OCSP_ISSUER_NOT_FOUND = 4502,
   OCSP_RESPONSE_MISSING_KEYUSAGE = 4503,
   OCSP_RESPONSE_INVALID = 4504,
   EXT_IN_V1_V2_CERT = 4505,
   DUPLICATE_CERT_POLICY = 4506,
   V2_IDENTIFIERS_IN_V1_CERT = 4507,

   // Hard failures
   CERT_IS_REVOKED = 5000,
   CRL_BAD_SIGNATURE = 5001,
   SIGNATURE_ERROR = 5002,
   CERT_PUBKEY_INVALID = 5003,
   SIGNATURE_ALGO_UNKNOWN = 5004,
   SIGNATURE_ALGO_BAD_PARAMS = 5005
};

/**
* Convert a status code to a human readable diagnostic message
* @param code the certifcate status
* @return string literal constant, or nullptr if code unknown
*/
BOTAN_PUBLIC_API(2,0) const char* to_string(Certificate_Status_Code code);

/**
* X.509v3 Key Constraints.
* If updating update copy in ffi.h
*/
enum Key_Constraints {
   NO_CONSTRAINTS     = 0,
   DIGITAL_SIGNATURE  = 1 << 15,
   NON_REPUDIATION    = 1 << 14,
   KEY_ENCIPHERMENT   = 1 << 13,
   DATA_ENCIPHERMENT  = 1 << 12,
   KEY_AGREEMENT      = 1 << 11,
   KEY_CERT_SIGN      = 1 << 10,
   CRL_SIGN           = 1 << 9,
   ENCIPHER_ONLY      = 1 << 8,
   DECIPHER_ONLY      = 1 << 7
};

/**
* X.509v2 CRL Reason Code.
* This will become an enum class in a future major release
*/
enum CRL_Code : uint32_t {
   UNSPECIFIED            = 0,
   KEY_COMPROMISE         = 1,
   CA_COMPROMISE          = 2,
   AFFILIATION_CHANGED    = 3,
   SUPERSEDED             = 4,
   CESSATION_OF_OPERATION = 5,
   CERTIFICATE_HOLD       = 6,
   REMOVE_FROM_CRL        = 8,
   PRIVLEDGE_WITHDRAWN    = 9,
   PRIVILEGE_WITHDRAWN    = 9,
   AA_COMPROMISE          = 10,

   DELETE_CRL_ENTRY       = 0xFF00,
   OCSP_GOOD              = 0xFF01,
   OCSP_UNKNOWN           = 0xFF02
};

}

namespace Botan {

class Public_Key;
class Private_Key;
class RandomNumberGenerator;

/**
* This class represents abstract X.509 signed objects as in the X.500
* SIGNED macro
*/
class BOTAN_PUBLIC_API(2,0) X509_Object : public ASN1_Object
   {
   public:
      /**
      * The underlying data that is to be or was signed
      * @return data that is or was signed
      */
      std::vector<uint8_t> tbs_data() const;

      /**
      * @return signature on tbs_data()
      */
      const std::vector<uint8_t>& signature() const { return m_sig; }

      /**
      * @return signed body
      */
      const std::vector<uint8_t>& signed_body() const { return m_tbs_bits; }

      /**
      * @return signature algorithm that was used to generate signature
      */
      const AlgorithmIdentifier& signature_algorithm() const { return m_sig_algo; }

      /**
      * @return hash algorithm that was used to generate signature
      */
      std::string hash_used_for_signature() const;

      /**
      * Create a signed X509 object.
      * @param signer the signer used to sign the object
      * @param rng the random number generator to use
      * @param alg_id the algorithm identifier of the signature scheme
      * @param tbs the tbs bits to be signed
      * @return signed X509 object
      */
      static std::vector<uint8_t> make_signed(class PK_Signer* signer,
                                              RandomNumberGenerator& rng,
                                              const AlgorithmIdentifier& alg_id,
                                              const secure_vector<uint8_t>& tbs);

      /**
      * Check the signature on this data
      * @param key the public key purportedly used to sign this data
      * @return status of the signature - OK if verified or otherwise an indicator of
      *         the problem preventing verification.
      */
      Certificate_Status_Code verify_signature(const Public_Key& key) const;

      /**
      * Check the signature on this data
      * @param key the public key purportedly used to sign this data
      * @return true if the signature is valid, otherwise false
      */
      bool check_signature(const Public_Key& key) const;

      /**
      * Check the signature on this data
      * @param key the public key purportedly used to sign this data
      *        the object will be deleted after use (this should have
      *        been a std::unique_ptr<Public_Key>)
      * @return true if the signature is valid, otherwise false
      */
      bool check_signature(const Public_Key* key) const;

      /**
      * DER encode an X509_Object
      * See @ref ASN1_Object::encode_into()
      */
      void encode_into(class DER_Encoder& to) const override;

      /**
      * Decode a BER encoded X509_Object
      * See @ref ASN1_Object::decode_from()
      */
      void decode_from(class BER_Decoder& from) override;

      /**
      * @return PEM encoding of this
      */
      std::string PEM_encode() const;

      X509_Object(const X509_Object&) = default;
      X509_Object& operator=(const X509_Object&) = default;

      virtual std::string PEM_label() const = 0;

      virtual std::vector<std::string> alternate_PEM_labels() const
         { return std::vector<std::string>(); }

      virtual ~X509_Object() = default;

      static std::unique_ptr<PK_Signer>
         choose_sig_format(AlgorithmIdentifier& sig_algo,
                           const Private_Key& key,
                           RandomNumberGenerator& rng,
                           const std::string& hash_fn,
                           const std::string& padding_algo);

   protected:

      X509_Object() = default;

      /**
      * Decodes from src as either DER or PEM data, then calls force_decode()
      */
      void load_data(DataSource& src);

   private:
      virtual void force_decode() = 0;

      AlgorithmIdentifier m_sig_algo;
      std::vector<uint8_t> m_tbs_bits;
      std::vector<uint8_t> m_sig;
   };

}

namespace Botan {

class Public_Key;
class X509_DN;
class Extensions;
class AlternativeName;
class NameConstraints;

enum class Usage_Type
   {
   UNSPECIFIED, // no restrictions
   TLS_SERVER_AUTH,
   TLS_CLIENT_AUTH,
   CERTIFICATE_AUTHORITY,
   OCSP_RESPONDER,
   ENCRYPTION
   };

struct X509_Certificate_Data;

/**
* This class represents an X.509 Certificate
*/
class BOTAN_PUBLIC_API(2,0) X509_Certificate : public X509_Object
   {
   public:
      /**
      * Return a newly allocated copy of the public key associated
      * with the subject of this certificate. This object is owned
      * by the caller.
      *
      * Prefer load_subject_public_key in new code
      *
      * @return public key
      */
      Public_Key* subject_public_key() const;

      /**
      * Create a public key object associated with the public key bits in this
      * certificate. If the public key bits was valid for X.509 encoding
      * purposes but invalid algorithmically (for example, RSA with an even
      * modulus) that will be detected at this point, and an exception will be
      * thrown.
      *
      * @return subject public key of this certificate
      */
      std::unique_ptr<Public_Key> load_subject_public_key() const;

      /**
      * Get the public key associated with this certificate. This includes the
      * outer AlgorithmIdentifier
      * @return subject public key of this certificate
      */
      const std::vector<uint8_t>& subject_public_key_bits() const;

      /**
      * Get the SubjectPublicKeyInfo associated with this certificate.
      * @return subject public key info of this certificate
      */
      const std::vector<uint8_t>& subject_public_key_info() const;

      /**
      * Return the algorithm identifier of the public key
      */
      const AlgorithmIdentifier& subject_public_key_algo() const;

      /**
      * Get the bit string of the public key associated with this certificate
      * @return public key bits
      */
      const std::vector<uint8_t>& subject_public_key_bitstring() const;

      /**
      * Get the SHA-1 bit string of the public key associated with this certificate.
      * This is used for OCSP among other protocols.
      * This function will throw if SHA-1 is not available.
      * @return hash of subject public key of this certificate
      */
      const std::vector<uint8_t>& subject_public_key_bitstring_sha1() const;

      /**
      * Get the certificate's issuer distinguished name (DN).
      * @return issuer DN of this certificate
      */
      const X509_DN& issuer_dn() const;

      /**
      * Get the certificate's subject distinguished name (DN).
      * @return subject DN of this certificate
      */
      const X509_DN& subject_dn() const;

      /**
      * Get a value for a specific subject_info parameter name.
      * @param name the name of the parameter to look up. Possible names include
      * "X509.Certificate.version", "X509.Certificate.serial",
      * "X509.Certificate.start", "X509.Certificate.end",
      * "X509.Certificate.v2.key_id", "X509.Certificate.public_key",
      * "X509v3.BasicConstraints.path_constraint",
      * "X509v3.BasicConstraints.is_ca", "X509v3.NameConstraints",
      * "X509v3.ExtendedKeyUsage", "X509v3.CertificatePolicies",
      * "X509v3.SubjectKeyIdentifier", "X509.Certificate.serial",
      * "X520.CommonName", "X520.Organization", "X520.Country",
      * "RFC822" (Email in SAN) or "PKCS9.EmailAddress" (Email in DN).
      * @return value(s) of the specified parameter
      */
      std::vector<std::string> subject_info(const std::string& name) const;

      /**
      * Get a value for a specific subject_info parameter name.
      * @param name the name of the parameter to look up. Possible names are
      * "X509.Certificate.v2.key_id" or "X509v3.AuthorityKeyIdentifier".
      * @return value(s) of the specified parameter
      */
      std::vector<std::string> issuer_info(const std::string& name) const;

      /**
      * Raw issuer DN bits
      */
      const std::vector<uint8_t>& raw_issuer_dn() const;

      /**
      * SHA-256 of Raw issuer DN
      */
      std::vector<uint8_t> raw_issuer_dn_sha256() const;

      /**
      * Raw subject DN
      */
      const std::vector<uint8_t>& raw_subject_dn() const;

      /**
      * SHA-256 of Raw subject DN
      */
      std::vector<uint8_t> raw_subject_dn_sha256() const;

      /**
      * Get the notBefore of the certificate as a string
      * @return notBefore of the certificate
      */
      std::string BOTAN_DEPRECATED("Use not_before().to_string()") start_time() const
         {
         return not_before().to_string();
         }

      /**
      * Get the notAfter of the certificate as a string
      * @return notAfter of the certificate
      */
      std::string BOTAN_DEPRECATED("Use not_after().to_string()") end_time() const
         {
         return not_after().to_string();
         }

      /**
      * Get the notBefore of the certificate as X509_Time
      * @return notBefore of the certificate
      */
      const X509_Time& not_before() const;

      /**
      * Get the notAfter of the certificate as X509_Time
      * @return notAfter of the certificate
      */
      const X509_Time& not_after() const;

      /**
      * Get the X509 version of this certificate object.
      * @return X509 version
      */
      uint32_t x509_version() const;

      /**
      * Get the serial number of this certificate.
      * @return certificates serial number
      */
      const std::vector<uint8_t>& serial_number() const;

      /**
      * Get the serial number's sign
      * @return 1 iff the serial is negative.
      */
      bool is_serial_negative() const;

      /**
      * Get the DER encoded AuthorityKeyIdentifier of this certificate.
      * @return DER encoded AuthorityKeyIdentifier
      */
      const std::vector<uint8_t>& authority_key_id() const;

      /**
      * Get the DER encoded SubjectKeyIdentifier of this certificate.
      * @return DER encoded SubjectKeyIdentifier
      */
      const std::vector<uint8_t>& subject_key_id() const;

      /**
      * Check whether this certificate is self signed.
      * If the DN issuer and subject agree,
      * @return true if this certificate is self signed
      */
      bool is_self_signed() const;

      /**
      * Check whether this certificate is a CA certificate.
      * @return true if this certificate is a CA certificate
      */
      bool is_CA_cert() const;

      /**
      * Returns true if the specified @param usage is set in the key usage extension
      * or if no key usage constraints are set at all.
      * To check if a certain key constraint is set in the certificate
      * use @see X509_Certificate#has_constraints.
      */
      bool allowed_usage(Key_Constraints usage) const;

      /**
      * Returns true if the specified @param usage is set in the extended key usage extension
      * or if no extended key usage constraints are set at all.
      * To check if a certain extended key constraint is set in the certificate
      * use @see X509_Certificate#has_ex_constraint.
      */
      bool allowed_extended_usage(const std::string& usage) const;

      /**
      * Returns true if the specified usage is set in the extended key usage extension,
      * or if no extended key usage constraints are set at all.
      * To check if a certain extended key constraint is set in the certificate
      * use @see X509_Certificate#has_ex_constraint.
      */
      bool allowed_extended_usage(const OID& usage) const;

      /**
      * Returns true if the required key and extended key constraints are set in the certificate
      * for the specified @param usage or if no key constraints are set in both the key usage
      * and extended key usage extension.
      */
      bool allowed_usage(Usage_Type usage) const;

      /**
      * Returns true if the specified @param constraints are included in the key
      * usage extension.
      */
      bool has_constraints(Key_Constraints constraints) const;

      /**
      * Returns true if and only if @param ex_constraint (referring to an
      * extended key constraint, eg "PKIX.ServerAuth") is included in the
      * extended key extension.
      */
      bool BOTAN_DEPRECATED("Use version taking an OID")
         has_ex_constraint(const std::string& ex_constraint) const;

      /**
      * Returns true if and only if OID @param ex_constraint is
      * included in the extended key extension.
      */
      bool has_ex_constraint(const OID& ex_constraint) const;

      /**
      * Get the path limit as defined in the BasicConstraints extension of
      * this certificate.
      * @return path limit
      */
      uint32_t path_limit() const;

      /**
      * Check whenever a given X509 Extension is marked critical in this
      * certificate.
      */
      bool is_critical(const std::string& ex_name) const;

      /**
      * Get the key constraints as defined in the KeyUsage extension of this
      * certificate.
      * @return key constraints
      */
      Key_Constraints constraints() const;

      /**
      * Get the key constraints as defined in the ExtendedKeyUsage
      * extension of this certificate.
      * @return key constraints
      */
      std::vector<std::string>
         BOTAN_DEPRECATED("Use extended_key_usage") ex_constraints() const;

      /**
      * Get the key usage as defined in the ExtendedKeyUsage extension
      * of this certificate, or else an empty vector.
      * @return key usage
      */
      const std::vector<OID>& extended_key_usage() const;

      /**
      * Get the name constraints as defined in the NameConstraints
      * extension of this certificate.
      * @return name constraints
      */
      const NameConstraints& name_constraints() const;

      /**
      * Get the policies as defined in the CertificatePolicies extension
      * of this certificate.
      * @return certificate policies
      */
      std::vector<std::string> BOTAN_DEPRECATED("Use certificate_policy_oids") policies() const;

      const std::vector<OID>& certificate_policy_oids() const;

      /**
      * Get all extensions of this certificate.
      * @return certificate extensions
      */
      const Extensions& v3_extensions() const;

      /**
      * Return the v2 issuer key ID. v2 key IDs are almost never used,
      * instead see v3_subject_key_id.
      */
      const std::vector<uint8_t>& v2_issuer_key_id() const;

      /**
      * Return the v2 subject key ID. v2 key IDs are almost never used,
      * instead see v3_subject_key_id.
      */
      const std::vector<uint8_t>& v2_subject_key_id() const;

      /**
      * Return the subject alternative names (DNS, IP, ...)
      */
      const AlternativeName& subject_alt_name() const;

      /**
      * Return the issuer alternative names (DNS, IP, ...)
      */
      const AlternativeName& issuer_alt_name() const;

      /**
      * Return the listed address of an OCSP responder, or empty if not set
      */
      std::string ocsp_responder() const;

      /**
      * Return the listed addresses of ca issuers, or empty if not set
      */
      std::vector<std::string> ca_issuers() const;

      /**
      * Return the CRL distribution point, or empty if not set
      */
      std::string crl_distribution_point() const;

      /**
      * @return a free-form string describing the certificate
      */
      std::string to_string() const;

      /**
      * @return a fingerprint of the certificate
      * @param hash_name hash function used to calculate the fingerprint
      */
      std::string fingerprint(const std::string& hash_name = "SHA-1") const;

      /**
      * Check if a certain DNS name matches up with the information in
      * the cert
      * @param name DNS name to match
      */
      bool matches_dns_name(const std::string& name) const;

      /**
      * Check to certificates for equality.
      * @return true both certificates are (binary) equal
      */
      bool operator==(const X509_Certificate& other) const;

      /**
      * Impose an arbitrary (but consistent) ordering, eg to allow sorting
      * a container of certificate objects.
      * @return true if this is less than other by some unspecified criteria
      */
      bool operator<(const X509_Certificate& other) const;

      /**
      * Create a certificate from a data source providing the DER or
      * PEM encoded certificate.
      * @param source the data source
      */
      explicit X509_Certificate(DataSource& source);

#if defined(BOTAN_TARGET_OS_HAS_FILESYSTEM)
      /**
      * Create a certificate from a file containing the DER or PEM
      * encoded certificate.
      * @param filename the name of the certificate file
      */
      explicit X509_Certificate(const std::string& filename);
#endif

      /**
      * Create a certificate from a buffer
      * @param in the buffer containing the DER-encoded certificate
      */
      explicit X509_Certificate(const std::vector<uint8_t>& in);

      /**
      * Create a certificate from a buffer
      * @param data the buffer containing the DER-encoded certificate
      * @param length length of data in bytes
      */
      X509_Certificate(const uint8_t data[], size_t length);

      /**
      * Create an uninitialized certificate object. Any attempts to
      * access this object will throw an exception.
      */
      X509_Certificate() = default;

      X509_Certificate(const X509_Certificate& other) = default;

      X509_Certificate& operator=(const X509_Certificate& other) = default;

   private:
      std::string PEM_label() const override;

      std::vector<std::string> alternate_PEM_labels() const override;

      void force_decode() override;

      const X509_Certificate_Data& data() const;

      std::shared_ptr<X509_Certificate_Data> m_data;
   };

/**
* Check two certificates for inequality
* @param cert1 The first certificate
* @param cert2 The second certificate
* @return true if the arguments represent different certificates,
* false if they are binary identical
*/
BOTAN_PUBLIC_API(2,0) bool operator!=(const X509_Certificate& cert1, const X509_Certificate& cert2);

}

namespace Botan {

class Extensions;
class X509_Certificate;
class X509_DN;

struct CRL_Entry_Data;
struct CRL_Data;

/**
* This class represents CRL entries
*/
class BOTAN_PUBLIC_API(2,0) CRL_Entry final : public ASN1_Object
   {
   public:
      void encode_into(class DER_Encoder&) const override;
      void decode_from(class BER_Decoder&) override;

      /**
      * Get the serial number of the certificate associated with this entry.
      * @return certificate's serial number
      */
      const std::vector<uint8_t>& serial_number() const;

      /**
      * Get the revocation date of the certificate associated with this entry
      * @return certificate's revocation date
      */
      const X509_Time& expire_time() const;

      /**
      * Get the entries reason code
      * @return reason code
      */
      CRL_Code reason_code() const;

      /**
      * Get the extensions on this CRL entry
      */
      const Extensions& extensions() const;

      /**
      * Create uninitialized CRL_Entry object
      */
      CRL_Entry() = default;

      /**
      * Construct an CRL entry.
      * @param cert the certificate to revoke
      * @param reason the reason code to set in the entry
      */
      CRL_Entry(const X509_Certificate& cert,
                CRL_Code reason = UNSPECIFIED);

   private:
      friend class X509_CRL;

      const CRL_Entry_Data& data() const;

      std::shared_ptr<CRL_Entry_Data> m_data;
   };

/**
* Test two CRL entries for equality in all fields.
*/
BOTAN_PUBLIC_API(2,0) bool operator==(const CRL_Entry&, const CRL_Entry&);

/**
* Test two CRL entries for inequality in at least one field.
*/
BOTAN_PUBLIC_API(2,0) bool operator!=(const CRL_Entry&, const CRL_Entry&);

/**
* This class represents X.509 Certificate Revocation Lists (CRLs).
*/
class BOTAN_PUBLIC_API(2,0) X509_CRL final : public X509_Object
   {
   public:
      /**
      * This class represents CRL related errors.
      *
      * In a future major release this exception type will be removed and
      * replaced with Decoding_Error
      */
      class BOTAN_PUBLIC_API(2,0) X509_CRL_Error final : public Decoding_Error
         {
         public:
            explicit X509_CRL_Error(const std::string& error) :
               Decoding_Error("X509_CRL: " + error) {}
         };

      /**
      * Check if this particular certificate is listed in the CRL
      */
      bool is_revoked(const X509_Certificate& cert) const;

      /**
      * Get the entries of this CRL in the form of a vector.
      * @return vector containing the entries of this CRL.
      */
      const std::vector<CRL_Entry>& get_revoked() const;

      /**
      * Get the issuer DN of this CRL.
      * @return CRLs issuer DN
      */
      const X509_DN& issuer_dn() const;

      /**
      * @return extension data for this CRL
      */
      const Extensions& extensions() const;

      /**
      * Get the AuthorityKeyIdentifier of this CRL.
      * @return this CRLs AuthorityKeyIdentifier
      */
      const std::vector<uint8_t>& authority_key_id() const;

      /**
      * Get the serial number of this CRL.
      * @return CRLs serial number
      */
      uint32_t crl_number() const;

      /**
      * Get the CRL's thisUpdate value.
      * @return CRLs thisUpdate
      */
      const X509_Time& this_update() const;

      /**
      * Get the CRL's nextUpdate value.
      * @return CRLs nextdUpdate
      */
      const X509_Time& next_update() const;

      /**
      * Get the CRL's distribution point
      * @return CRL.IssuingDistributionPoint from the CRL's Data_Store
      */
      std::string crl_issuing_distribution_point() const;

      /**
      * Create an uninitialized CRL object. Any attempts to access
      * this object will throw an exception.
      */
      X509_CRL() = default;

      /**
      * Construct a CRL from a data source.
      * @param source the data source providing the DER or PEM encoded CRL.
      */
      X509_CRL(DataSource& source);

#if defined(BOTAN_TARGET_OS_HAS_FILESYSTEM)
      /**
      * Construct a CRL from a file containing the DER or PEM encoded CRL.
      * @param filename the name of the CRL file
      */
      X509_CRL(const std::string& filename);
#endif

      /**
      * Construct a CRL from a binary vector
      * @param vec the binary (DER) representation of the CRL
      */
      X509_CRL(const std::vector<uint8_t>& vec);

      /**
      * Construct a CRL
      * @param issuer issuer of this CRL
      * @param thisUpdate valid from
      * @param nextUpdate valid until
      * @param revoked entries to be included in the CRL
      */
      X509_CRL(const X509_DN& issuer, const X509_Time& thisUpdate,
               const X509_Time& nextUpdate, const std::vector<CRL_Entry>& revoked);

   private:
      std::string PEM_label() const override;

      std::vector<std::string> alternate_PEM_labels() const override;

      void force_decode() override;

      const CRL_Data& data() const;

      std::shared_ptr<CRL_Data> m_data;
   };

}

namespace Botan {

/**
* Certificate Store Interface
*/
class BOTAN_PUBLIC_API(2,0) Certificate_Store
   {
   public:
      virtual ~Certificate_Store();

      /**
      * Find a certificate by Subject DN and (optionally) key identifier
      * @param subject_dn the subject's distinguished name
      * @param key_id an optional key id
      * @return a matching certificate or nullptr otherwise
      * If more than one certificate in the certificate store matches, then
      * a single value is selected arbitrarily.
      */
      virtual std::shared_ptr<const X509_Certificate>
         find_cert(const X509_DN& subject_dn, const std::vector<uint8_t>& key_id) const;

      /**
      * Find all certificates with a given Subject DN.
      * Subject DN and even the key identifier might not be unique.
      */
      virtual std::vector<std::shared_ptr<const X509_Certificate>> find_all_certs(
         const X509_DN& subject_dn, const std::vector<uint8_t>& key_id) const = 0;


      /**
      * Find a certificate by searching for one with a matching SHA-1 hash of
      * public key. Used for OCSP.
      * @param key_hash SHA-1 hash of the subject's public key
      * @return a matching certificate or nullptr otherwise
      */
      virtual std::shared_ptr<const X509_Certificate>
         find_cert_by_pubkey_sha1(const std::vector<uint8_t>& key_hash) const = 0;

      /**
      * Find a certificate by searching for one with a matching SHA-256 hash of
      * raw subject name. Used for OCSP.
      * @param subject_hash SHA-256 hash of the subject's raw name
      * @return a matching certificate or nullptr otherwise
      */
      virtual std::shared_ptr<const X509_Certificate>
         find_cert_by_raw_subject_dn_sha256(const std::vector<uint8_t>& subject_hash) const = 0;

      /**
      * Finds a CRL for the given certificate
      * @param subject the subject certificate
      * @return the CRL for subject or nullptr otherwise
      */
      virtual std::shared_ptr<const X509_CRL> find_crl_for(const X509_Certificate& subject) const;

      /**
      * @return whether the certificate is known
      * @param cert certififcate to be searched
      */
      bool certificate_known(const X509_Certificate& cert) const
         {
         return find_cert(cert.subject_dn(), cert.subject_key_id()) != nullptr;
         }

      // remove this (used by TLS::Server)
      virtual std::vector<X509_DN> all_subjects() const = 0;
   };

/**
* In Memory Certificate Store
*/
class BOTAN_PUBLIC_API(2,0) Certificate_Store_In_Memory final : public Certificate_Store
   {
   public:
      /**
      * Attempt to parse all files in dir (including subdirectories)
      * as certificates. Ignores errors.
      */
      explicit Certificate_Store_In_Memory(const std::string& dir);

      /**
      * Adds given certificate to the store.
      */
      explicit Certificate_Store_In_Memory(const X509_Certificate& cert);

      /**
      * Create an empty store.
      */
      Certificate_Store_In_Memory() = default;

      /**
      * Add a certificate to the store.
      * @param cert certificate to be added
      */
      void add_certificate(const X509_Certificate& cert);

      /**
      * Add a certificate already in a shared_ptr to the store.
      * @param cert certificate to be added
      */
      void add_certificate(std::shared_ptr<const X509_Certificate> cert);

      /**
      * Add a certificate revocation list (CRL) to the store.
      * @param crl CRL to be added
      */
      void add_crl(const X509_CRL& crl);

      /**
      * Add a certificate revocation list (CRL) to the store as a shared_ptr
      * @param crl CRL to be added
      */
      void add_crl(std::shared_ptr<const X509_CRL> crl);

      /**
      * @return DNs for all certificates managed by the store
      */
      std::vector<X509_DN> all_subjects() const override;

      /*
      * Find a certificate by Subject DN and (optionally) key identifier
      * @return the first certificate that matches
      */
      std::shared_ptr<const X509_Certificate> find_cert(
         const X509_DN& subject_dn,
         const std::vector<uint8_t>& key_id) const override;

      /*
      * Find all certificates with a given Subject DN.
      * Subject DN and even the key identifier might not be unique.
      */
      std::vector<std::shared_ptr<const X509_Certificate>> find_all_certs(
         const X509_DN& subject_dn, const std::vector<uint8_t>& key_id) const override;

      std::shared_ptr<const X509_Certificate>
         find_cert_by_pubkey_sha1(const std::vector<uint8_t>& key_hash) const override;

      std::shared_ptr<const X509_Certificate>
         find_cert_by_raw_subject_dn_sha256(const std::vector<uint8_t>& subject_hash) const override;

      /**
      * Finds a CRL for the given certificate
      */
      std::shared_ptr<const X509_CRL> find_crl_for(const X509_Certificate& subject) const override;
   private:
      // TODO: Add indexing on the DN and key id to avoid linear search
      std::vector<std::shared_ptr<const X509_Certificate>> m_certs;
      std::vector<std::shared_ptr<const X509_CRL>> m_crls;
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(charset.h)

namespace Botan {

/**
* Convert a sequence of UCS-2 (big endian) characters to a UTF-8 string
* This is used for ASN.1 BMPString type
* @param ucs2 the sequence of UCS-2 characters
* @param len length of ucs2 in bytes, must be a multiple of 2
*/
std::string BOTAN_UNSTABLE_API ucs2_to_utf8(const uint8_t ucs2[], size_t len);

/**
* Convert a sequence of UCS-4 (big endian) characters to a UTF-8 string
* This is used for ASN.1 UniversalString type
* @param ucs4 the sequence of UCS-4 characters
* @param len length of ucs4 in bytes, must be a multiple of 4
*/
std::string BOTAN_UNSTABLE_API ucs4_to_utf8(const uint8_t ucs4[], size_t len);

/**
* Convert a UTF-8 string to Latin-1
* If a character outside the Latin-1 range is encountered, an exception is thrown.
*/
std::string BOTAN_UNSTABLE_API utf8_to_latin1(const std::string& utf8);

/**
* The different charsets (nominally) supported by Botan.
*/
enum Character_Set {
   LOCAL_CHARSET,
   UCS2_CHARSET,
   UTF8_CHARSET,
   LATIN1_CHARSET
};

namespace Charset {

/*
* Character set conversion - avoid this.
* For specific conversions, use the functions above like
* ucs2_to_utf8 and utf8_to_latin1
*
* If you need something more complex than that, use a real library
* such as iconv, Boost.Locale, or ICU
*/
std::string BOTAN_PUBLIC_API(2,0)
   BOTAN_DEPRECATED("Avoid. See comment in header.")
   transcode(const std::string& str,
             Character_Set to,
             Character_Set from);

/*
* Simple character classifier functions
*/
bool BOTAN_PUBLIC_API(2,0) is_digit(char c);
bool BOTAN_PUBLIC_API(2,0) is_space(char c);
bool BOTAN_PUBLIC_API(2,0) caseless_cmp(char x, char y);

uint8_t BOTAN_PUBLIC_API(2,0) char2digit(char c);
char BOTAN_PUBLIC_API(2,0) digit2char(uint8_t b);

}

}

BOTAN_FUTURE_INTERNAL_HEADER(cpuid.h)

namespace Botan {

/**
* A class handling runtime CPU feature detection. It is limited to
* just the features necessary to implement CPU specific code in Botan,
* rather than being a general purpose utility.
*
* This class supports:
*
*  - x86 features using CPUID. x86 is also the only processor with
*    accurate cache line detection currently.
*
*  - PowerPC AltiVec detection on Linux, NetBSD, OpenBSD, and macOS
*
*  - ARM NEON and crypto extensions detection. On Linux and Android
*    systems which support getauxval, that is used to access CPU
*    feature information. Otherwise a relatively portable but
*    thread-unsafe mechanism involving executing probe functions which
*    catching SIGILL signal is used.
*/
class BOTAN_PUBLIC_API(2,1) CPUID final
   {
   public:
      /**
      * Probe the CPU and see what extensions are supported
      */
      static void initialize();

      static bool has_simd_32();

      /**
      * Deprecated equivalent to
      * o << "CPUID flags: " << CPUID::to_string() << "\n";
      */
      BOTAN_DEPRECATED("Use CPUID::to_string")
      static void print(std::ostream& o);

      /**
      * Return a possibly empty string containing list of known CPU
      * extensions. Each name will be seperated by a space, and the ordering
      * will be arbitrary. This list only contains values that are useful to
      * Botan (for example FMA instructions are not checked).
      *
      * Example outputs "sse2 ssse3 rdtsc", "neon arm_aes", "altivec"
      */
      static std::string to_string();

      /**
      * Return a best guess of the cache line size
      */
      static size_t cache_line_size()
         {
         return state().cache_line_size();
         }

      static bool is_little_endian()
         {
#if defined(BOTAN_TARGET_CPU_IS_LITTLE_ENDIAN)
         return true;
#elif defined(BOTAN_TARGET_CPU_IS_BIG_ENDIAN)
         return false;
#else
         return state().endian_status() == Endian_Status::Little;
#endif
         }

      static bool is_big_endian()
         {
#if defined(BOTAN_TARGET_CPU_IS_BIG_ENDIAN)
         return true;
#elif defined(BOTAN_TARGET_CPU_IS_LITTLE_ENDIAN)
         return false;
#else
         return state().endian_status() == Endian_Status::Big;
#endif
         }

      enum CPUID_bits : uint64_t {
#if defined(BOTAN_TARGET_CPU_IS_X86_FAMILY)
         // These values have no relation to cpuid bitfields

         // SIMD instruction sets
         CPUID_SSE2_BIT       = (1ULL << 0),
         CPUID_SSSE3_BIT      = (1ULL << 1),
         CPUID_SSE41_BIT      = (1ULL << 2),
         CPUID_SSE42_BIT      = (1ULL << 3),
         CPUID_AVX2_BIT       = (1ULL << 4),
         CPUID_AVX512F_BIT    = (1ULL << 5),

         CPUID_AVX512DQ_BIT   = (1ULL << 6),
         CPUID_AVX512BW_BIT   = (1ULL << 7),

         // Ice Lake profile: AVX-512 F, DQ, BW, IFMA, VBMI, VBMI2, BITALG
         CPUID_AVX512_ICL_BIT = (1ULL << 11),

         // Crypto-specific ISAs
         CPUID_AESNI_BIT        = (1ULL << 16),
         CPUID_CLMUL_BIT        = (1ULL << 17),
         CPUID_RDRAND_BIT       = (1ULL << 18),
         CPUID_RDSEED_BIT       = (1ULL << 19),
         CPUID_SHA_BIT          = (1ULL << 20),
         CPUID_AVX512_AES_BIT   = (1ULL << 21),
         CPUID_AVX512_CLMUL_BIT = (1ULL << 22),

         // Misc useful instructions
         CPUID_RDTSC_BIT      = (1ULL << 48),
         CPUID_ADX_BIT        = (1ULL << 49),
         CPUID_BMI1_BIT       = (1ULL << 50),
         CPUID_BMI2_BIT       = (1ULL << 51),
#endif

#if defined(BOTAN_TARGET_CPU_IS_PPC_FAMILY)
         CPUID_ALTIVEC_BIT    = (1ULL << 0),
         CPUID_POWER_CRYPTO_BIT = (1ULL << 1),
         CPUID_DARN_BIT       = (1ULL << 2),
#endif

#if defined(BOTAN_TARGET_CPU_IS_ARM_FAMILY)
         CPUID_ARM_NEON_BIT      = (1ULL << 0),
         CPUID_ARM_SVE_BIT       = (1ULL << 1),
         CPUID_ARM_AES_BIT       = (1ULL << 16),
         CPUID_ARM_PMULL_BIT     = (1ULL << 17),
         CPUID_ARM_SHA1_BIT      = (1ULL << 18),
         CPUID_ARM_SHA2_BIT      = (1ULL << 19),
         CPUID_ARM_SHA3_BIT      = (1ULL << 20),
         CPUID_ARM_SHA2_512_BIT  = (1ULL << 21),
         CPUID_ARM_SM3_BIT       = (1ULL << 22),
         CPUID_ARM_SM4_BIT       = (1ULL << 23),
#endif

         CPUID_INITIALIZED_BIT = (1ULL << 63)
      };

#if defined(BOTAN_TARGET_CPU_IS_PPC_FAMILY)
      /**
      * Check if the processor supports AltiVec/VMX
      */
      static bool has_altivec()
         { return has_cpuid_bit(CPUID_ALTIVEC_BIT); }

      /**
      * Check if the processor supports POWER8 crypto extensions
      */
      static bool has_power_crypto()
         { return has_cpuid_bit(CPUID_POWER_CRYPTO_BIT); }

      /**
      * Check if the processor supports POWER9 DARN RNG
      */
      static bool has_darn_rng()
         { return has_cpuid_bit(CPUID_DARN_BIT); }

#endif

#if defined(BOTAN_TARGET_CPU_IS_ARM_FAMILY)
      /**
      * Check if the processor supports NEON SIMD
      */
      static bool has_neon()
         { return has_cpuid_bit(CPUID_ARM_NEON_BIT); }

      /**
      * Check if the processor supports ARMv8 SVE
      */
      static bool has_arm_sve()
         { return has_cpuid_bit(CPUID_ARM_SVE_BIT); }

      /**
      * Check if the processor supports ARMv8 SHA1
      */
      static bool has_arm_sha1()
         { return has_cpuid_bit(CPUID_ARM_SHA1_BIT); }

      /**
      * Check if the processor supports ARMv8 SHA2
      */
      static bool has_arm_sha2()
         { return has_cpuid_bit(CPUID_ARM_SHA2_BIT); }

      /**
      * Check if the processor supports ARMv8 AES
      */
      static bool has_arm_aes()
         { return has_cpuid_bit(CPUID_ARM_AES_BIT); }

      /**
      * Check if the processor supports ARMv8 PMULL
      */
      static bool has_arm_pmull()
         { return has_cpuid_bit(CPUID_ARM_PMULL_BIT); }

      /**
      * Check if the processor supports ARMv8 SHA-512
      */
      static bool has_arm_sha2_512()
         { return has_cpuid_bit(CPUID_ARM_SHA2_512_BIT); }

      /**
      * Check if the processor supports ARMv8 SHA-3
      */
      static bool has_arm_sha3()
         { return has_cpuid_bit(CPUID_ARM_SHA3_BIT); }

      /**
      * Check if the processor supports ARMv8 SM3
      */
      static bool has_arm_sm3()
         { return has_cpuid_bit(CPUID_ARM_SM3_BIT); }

      /**
      * Check if the processor supports ARMv8 SM4
      */
      static bool has_arm_sm4()
         { return has_cpuid_bit(CPUID_ARM_SM4_BIT); }

#endif

#if defined(BOTAN_TARGET_CPU_IS_X86_FAMILY)

      /**
      * Check if the processor supports RDTSC
      */
      static bool has_rdtsc()
         { return has_cpuid_bit(CPUID_RDTSC_BIT); }

      /**
      * Check if the processor supports SSE2
      */
      static bool has_sse2()
         { return has_cpuid_bit(CPUID_SSE2_BIT); }

      /**
      * Check if the processor supports SSSE3
      */
      static bool has_ssse3()
         { return has_cpuid_bit(CPUID_SSSE3_BIT); }

      /**
      * Check if the processor supports SSE4.1
      */
      static bool has_sse41()
         { return has_cpuid_bit(CPUID_SSE41_BIT); }

      /**
      * Check if the processor supports SSE4.2
      */
      static bool has_sse42()
         { return has_cpuid_bit(CPUID_SSE42_BIT); }

      /**
      * Check if the processor supports AVX2
      */
      static bool has_avx2()
         { return has_cpuid_bit(CPUID_AVX2_BIT); }

      /**
      * Check if the processor supports AVX-512F
      */
      static bool has_avx512f()
         { return has_cpuid_bit(CPUID_AVX512F_BIT); }

      /**
      * Check if the processor supports AVX-512DQ
      */
      static bool has_avx512dq()
         { return has_cpuid_bit(CPUID_AVX512DQ_BIT); }

      /**
      * Check if the processor supports AVX-512BW
      */
      static bool has_avx512bw()
         { return has_cpuid_bit(CPUID_AVX512BW_BIT); }

      /**
      * Check if the processor supports AVX-512 Ice Lake profile
      */
      static bool has_avx512_icelake()
         { return has_cpuid_bit(CPUID_AVX512_ICL_BIT); }

      /**
      * Check if the processor supports AVX-512 AES (VAES)
      */
      static bool has_avx512_aes()
         { return has_cpuid_bit(CPUID_AVX512_AES_BIT); }

      /**
      * Check if the processor supports AVX-512 VPCLMULQDQ
      */
      static bool has_avx512_clmul()
         { return has_cpuid_bit(CPUID_AVX512_CLMUL_BIT); }

      /**
      * Check if the processor supports BMI1
      */
      static bool has_bmi1()
         { return has_cpuid_bit(CPUID_BMI1_BIT); }

      /**
      * Check if the processor supports BMI2
      */
      static bool has_bmi2()
         { return has_cpuid_bit(CPUID_BMI2_BIT); }

      /**
      * Check if the processor supports AES-NI
      */
      static bool has_aes_ni()
         { return has_cpuid_bit(CPUID_AESNI_BIT); }

      /**
      * Check if the processor supports CLMUL
      */
      static bool has_clmul()
         { return has_cpuid_bit(CPUID_CLMUL_BIT); }

      /**
      * Check if the processor supports Intel SHA extension
      */
      static bool has_intel_sha()
         { return has_cpuid_bit(CPUID_SHA_BIT); }

      /**
      * Check if the processor supports ADX extension
      */
      static bool has_adx()
         { return has_cpuid_bit(CPUID_ADX_BIT); }

      /**
      * Check if the processor supports RDRAND
      */
      static bool has_rdrand()
         { return has_cpuid_bit(CPUID_RDRAND_BIT); }

      /**
      * Check if the processor supports RDSEED
      */
      static bool has_rdseed()
         { return has_cpuid_bit(CPUID_RDSEED_BIT); }
#endif

      /**
      * Check if the processor supports byte-level vector permutes
      * (SSSE3, NEON, Altivec)
      */
      static bool has_vperm()
         {
#if defined(BOTAN_TARGET_CPU_IS_X86_FAMILY)
         return has_ssse3();
#elif defined(BOTAN_TARGET_CPU_IS_ARM_FAMILY)
         return has_neon();
#elif defined(BOTAN_TARGET_CPU_IS_PPC_FAMILY)
         return has_altivec();
#else
         return false;
#endif
         }

      /**
      * Check if the processor supports hardware AES instructions
      */
      static bool has_hw_aes()
         {
#if defined(BOTAN_TARGET_CPU_IS_X86_FAMILY)
         return has_aes_ni();
#elif defined(BOTAN_TARGET_CPU_IS_ARM_FAMILY)
         return has_arm_aes();
#elif defined(BOTAN_TARGET_CPU_IS_PPC_FAMILY)
         return has_power_crypto();
#else
         return false;
#endif
         }

      /**
      * Check if the processor supports carryless multiply
      * (CLMUL, PMULL)
      */
      static bool has_carryless_multiply()
         {
#if defined(BOTAN_TARGET_CPU_IS_X86_FAMILY)
         return has_clmul();
#elif defined(BOTAN_TARGET_CPU_IS_ARM_FAMILY)
         return has_arm_pmull();
#elif defined(BOTAN_TARGET_ARCH_IS_PPC64)
         return has_power_crypto();
#else
         return false;
#endif
         }

      /*
      * Clear a CPUID bit
      * Call CPUID::initialize to reset
      *
      * This is only exposed for testing, don't use unless you know
      * what you are doing.
      */
      static void clear_cpuid_bit(CPUID_bits bit)
         {
         state().clear_cpuid_bit(static_cast<uint64_t>(bit));
         }

      /*
      * Don't call this function, use CPUID::has_xxx above
      * It is only exposed for the tests.
      */
      static bool has_cpuid_bit(CPUID_bits elem)
         {
         const uint64_t elem64 = static_cast<uint64_t>(elem);
         return state().has_bit(elem64);
         }

      static std::vector<CPUID::CPUID_bits> bit_from_string(const std::string& tok);
   private:
      enum class Endian_Status : uint32_t {
         Unknown = 0x00000000,
         Big     = 0x01234567,
         Little  = 0x67452301,
      };

      struct CPUID_Data
         {
         public:
            CPUID_Data();

            CPUID_Data(const CPUID_Data& other) = default;
            CPUID_Data& operator=(const CPUID_Data& other) = default;

            void clear_cpuid_bit(uint64_t bit)
               {
               m_processor_features &= ~bit;
               }

            bool has_bit(uint64_t bit) const
               {
               return (m_processor_features & bit) == bit;
               }

            uint64_t processor_features() const { return m_processor_features; }
            Endian_Status endian_status() const { return m_endian_status; }
            size_t cache_line_size() const { return m_cache_line_size; }

         private:
            static Endian_Status runtime_check_endian();

#if defined(BOTAN_TARGET_CPU_IS_PPC_FAMILY) || \
    defined(BOTAN_TARGET_CPU_IS_ARM_FAMILY) || \
    defined(BOTAN_TARGET_CPU_IS_X86_FAMILY)

            static uint64_t detect_cpu_features(size_t* cache_line_size);

#endif
            uint64_t m_processor_features;
            size_t m_cache_line_size;
            Endian_Status m_endian_status;
         };

      static CPUID_Data& state()
         {
         static CPUID::CPUID_Data g_cpuid;
         return g_cpuid;
         }
   };

}

namespace Botan {

/**
* This class represents hash function (message digest) objects
*/
class BOTAN_PUBLIC_API(2,0) HashFunction : public Buffered_Computation
   {
   public:
      /**
      * Create an instance based on a name, or return null if the
      * algo/provider combination cannot be found. If provider is
      * empty then best available is chosen.
      */
      static std::unique_ptr<HashFunction>
         create(const std::string& algo_spec,
                const std::string& provider = "");

      /**
      * Create an instance based on a name
      * If provider is empty then best available is chosen.
      * @param algo_spec algorithm name
      * @param provider provider implementation to use
      * Throws Lookup_Error if not found.
      */
      static std::unique_ptr<HashFunction>
         create_or_throw(const std::string& algo_spec,
                         const std::string& provider = "");

      /**
      * @return list of available providers for this algorithm, empty if not available
      * @param algo_spec algorithm name
      */
      static std::vector<std::string> providers(const std::string& algo_spec);

      /**
      * @return new object representing the same algorithm as *this
      */
      virtual HashFunction* clone() const = 0;

      /**
      * @return provider information about this implementation. Default is "base",
      * might also return "sse2", "avx2", "openssl", or some other arbitrary string.
      */
      virtual std::string provider() const { return "base"; }

      virtual ~HashFunction() = default;

      /**
      * Reset the state.
      */
      virtual void clear() = 0;

      /**
      * @return the hash function name
      */
      virtual std::string name() const = 0;

      /**
      * @return hash block size as defined for this algorithm
      */
      virtual size_t hash_block_size() const { return 0; }

      /**
      * Return a new hash object with the same state as *this. This
      * allows computing the hash of several messages with a common
      * prefix more efficiently than would otherwise be possible.
      *
      * This function should be called `clone` but that was already
      * used for the case of returning an uninitialized object.
      * @return new hash object
      */
      virtual std::unique_ptr<HashFunction> copy_state() const = 0;
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(crc32.h)

namespace Botan {

/**
* 32-bit cyclic redundancy check
*/
class BOTAN_PUBLIC_API(2,0) CRC32 final : public HashFunction
   {
   public:
      std::string name() const override { return "CRC32"; }
      size_t output_length() const override { return 4; }
      HashFunction* clone() const override { return new CRC32; }
      std::unique_ptr<HashFunction> copy_state() const override;

      void clear() override { m_crc = 0xFFFFFFFF; }

      CRC32() { clear(); }
      ~CRC32() { clear(); }
   private:
      void add_data(const uint8_t[], size_t) override;
      void final_result(uint8_t[]) override;
      uint32_t m_crc;
   };

}
namespace Botan {

namespace PK_Ops {

class Encryption;
class Decryption;
class Verification;
class Signature;
class Key_Agreement;
class KEM_Encryption;
class KEM_Decryption;

}

}

namespace Botan {

class RandomNumberGenerator;

/**
* The two types of signature format supported by Botan.
*/
enum Signature_Format { IEEE_1363, DER_SEQUENCE };

/**
* Public Key Base Class.
*/
class BOTAN_PUBLIC_API(2,0) Public_Key
   {
   public:
      Public_Key() =default;
      Public_Key(const Public_Key& other) = default;
      Public_Key& operator=(const Public_Key& other) = default;
      virtual ~Public_Key() = default;

      /**
      * Get the name of the underlying public key scheme.
      * @return name of the public key scheme
      */
      virtual std::string algo_name() const = 0;

      /**
      * Return the estimated strength of the underlying key against
      * the best currently known attack. Note that this ignores anything
      * but pure attacks against the key itself and do not take into
      * account padding schemes, usage mistakes, etc which might reduce
      * the strength. However it does suffice to provide an upper bound.
      *
      * @return estimated strength in bits
      */
      virtual size_t estimated_strength() const = 0;

      /**
      * Return an integer value best approximating the length of the
      * primary security parameter. For example for RSA this will be
      * the size of the modulus, for ECDSA the size of the ECC group,
      * and for McEliece the size of the code will be returned.
      */
      virtual size_t key_length() const = 0;

      /**
      * Get the OID of the underlying public key scheme.
      * @return OID of the public key scheme
      */
      virtual OID get_oid() const;

      /**
      * Test the key values for consistency.
      * @param rng rng to use
      * @param strong whether to perform strong and lengthy version
      * of the test
      * @return true if the test is passed
      */
      virtual bool check_key(RandomNumberGenerator& rng,
                             bool strong) const = 0;


      /**
      * @return X.509 AlgorithmIdentifier for this key
      */
      virtual AlgorithmIdentifier algorithm_identifier() const = 0;

      /**
      * @return BER encoded public key bits
      */
      virtual std::vector<uint8_t> public_key_bits() const = 0;

      /**
      * @return X.509 subject key encoding for this key object
      */
      std::vector<uint8_t> subject_public_key() const;

      /**
       * @return Hash of the subject public key
       */
      std::string fingerprint_public(const std::string& alg = "SHA-256") const;

      // Internal or non-public declarations follow

      /**
      * Returns more than 1 if the output of this algorithm
      * (ciphertext, signature) should be treated as more than one
      * value. This is used for algorithms like DSA and ECDSA, where
      * the (r,s) output pair can be encoded as either a plain binary
      * list or a TLV tagged DER encoding depending on the protocol.
      *
      * This function is public but applications should have few
      * reasons to ever call this.
      *
      * @return number of message parts
      */
      virtual size_t message_parts() const { return 1; }

      /**
      * Returns how large each of the message parts refered to
      * by message_parts() is
      *
      * This function is public but applications should have few
      * reasons to ever call this.
      *
      * @return size of the message parts in bits
      */
      virtual size_t message_part_size() const { return 0; }

      virtual Signature_Format default_x509_signature_format() const
         {
         return (this->message_parts() >= 2) ? DER_SEQUENCE : IEEE_1363;
         }

      /**
      * This is an internal library function exposed on key types.
      * In almost all cases applications should use wrappers in pubkey.h
      *
      * Return an encryption operation for this key/params or throw
      *
      * @param rng a random number generator. The PK_Op may maintain a
      * reference to the RNG and use it many times. The rng must outlive
      * any operations which reference it.
      * @param params additional parameters
      * @param provider the provider to use
      */
      virtual std::unique_ptr<PK_Ops::Encryption>
         create_encryption_op(RandomNumberGenerator& rng,
                              const std::string& params,
                              const std::string& provider) const;

      /**
      * This is an internal library function exposed on key types.
      * In almost all cases applications should use wrappers in pubkey.h
      *
      * Return a KEM encryption operation for this key/params or throw
      *
      * @param rng a random number generator. The PK_Op may maintain a
      * reference to the RNG and use it many times. The rng must outlive
      * any operations which reference it.
      * @param params additional parameters
      * @param provider the provider to use
      */
      virtual std::unique_ptr<PK_Ops::KEM_Encryption>
         create_kem_encryption_op(RandomNumberGenerator& rng,
                                  const std::string& params,
                                  const std::string& provider) const;

      /**
      * This is an internal library function exposed on key types.
      * In almost all cases applications should use wrappers in pubkey.h
      *
      * Return a verification operation for this key/params or throw
      * @param params additional parameters
      * @param provider the provider to use
      */
      virtual std::unique_ptr<PK_Ops::Verification>
         create_verification_op(const std::string& params,
                                const std::string& provider) const;
   };

/**
* Private Key Base Class
*/
class BOTAN_PUBLIC_API(2,0) Private_Key : public virtual Public_Key
   {
   public:
      Private_Key() = default;
      Private_Key(const Private_Key& other) = default;
      Private_Key& operator=(const Private_Key& other) = default;
      virtual ~Private_Key() = default;

      virtual bool stateful_operation() const { return false; }

      /**
      * @return BER encoded private key bits
      */
      virtual secure_vector<uint8_t> private_key_bits() const = 0;

      /**
      * @return PKCS #8 private key encoding for this key object
      */
      secure_vector<uint8_t> private_key_info() const;

      /**
      * @return PKCS #8 AlgorithmIdentifier for this key
      * Might be different from the X.509 identifier, but normally is not
      */
      virtual AlgorithmIdentifier pkcs8_algorithm_identifier() const
         { return algorithm_identifier(); }

      // Internal or non-public declarations follow

      /**
       * @return Hash of the PKCS #8 encoding for this key object
       */
      std::string fingerprint_private(const std::string& alg) const;

      BOTAN_DEPRECATED("Use fingerprint_private or fingerprint_public")
         inline std::string fingerprint(const std::string& alg) const
         {
         return fingerprint_private(alg); // match behavior in previous versions
         }

      /**
      * This is an internal library function exposed on key types.
      * In almost all cases applications should use wrappers in pubkey.h
      *
      * Return an decryption operation for this key/params or throw
      *
      * @param rng a random number generator. The PK_Op may maintain a
      * reference to the RNG and use it many times. The rng must outlive
      * any operations which reference it.
      * @param params additional parameters
      * @param provider the provider to use
      *
      */
      virtual std::unique_ptr<PK_Ops::Decryption>
         create_decryption_op(RandomNumberGenerator& rng,
                              const std::string& params,
                              const std::string& provider) const;

      /**
      * This is an internal library function exposed on key types.
      * In almost all cases applications should use wrappers in pubkey.h
      *
      * Return a KEM decryption operation for this key/params or throw
      *
      * @param rng a random number generator. The PK_Op may maintain a
      * reference to the RNG and use it many times. The rng must outlive
      * any operations which reference it.
      * @param params additional parameters
      * @param provider the provider to use
      */
      virtual std::unique_ptr<PK_Ops::KEM_Decryption>
         create_kem_decryption_op(RandomNumberGenerator& rng,
                                  const std::string& params,
                                  const std::string& provider) const;

      /**
      * This is an internal library function exposed on key types.
      * In almost all cases applications should use wrappers in pubkey.h
      *
      * Return a signature operation for this key/params or throw
      *
      * @param rng a random number generator. The PK_Op may maintain a
      * reference to the RNG and use it many times. The rng must outlive
      * any operations which reference it.
      * @param params additional parameters
      * @param provider the provider to use
      */
      virtual std::unique_ptr<PK_Ops::Signature>
         create_signature_op(RandomNumberGenerator& rng,
                             const std::string& params,
                             const std::string& provider) const;

      /**
      * This is an internal library function exposed on key types.
      * In almost all cases applications should use wrappers in pubkey.h
      *
      * Return a key agreement operation for this key/params or throw
      *
      * @param rng a random number generator. The PK_Op may maintain a
      * reference to the RNG and use it many times. The rng must outlive
      * any operations which reference it.
      * @param params additional parameters
      * @param provider the provider to use
      */
      virtual std::unique_ptr<PK_Ops::Key_Agreement>
         create_key_agreement_op(RandomNumberGenerator& rng,
                                 const std::string& params,
                                 const std::string& provider) const;
   };

/**
* PK Secret Value Derivation Key
*/
class BOTAN_PUBLIC_API(2,0) PK_Key_Agreement_Key : public virtual Private_Key
   {
   public:
      /*
      * @return public component of this key
      */
      virtual std::vector<uint8_t> public_value() const = 0;

      PK_Key_Agreement_Key() = default;
      PK_Key_Agreement_Key(const PK_Key_Agreement_Key&) = default;
      PK_Key_Agreement_Key& operator=(const PK_Key_Agreement_Key&) = default;
      virtual ~PK_Key_Agreement_Key() = default;
   };

/*
* Old compat typedefs
* TODO: remove these?
*/
typedef PK_Key_Agreement_Key PK_KA_Key;
typedef Public_Key X509_PublicKey;
typedef Private_Key PKCS8_PrivateKey;

std::string BOTAN_PUBLIC_API(2,4)
   create_hex_fingerprint(const uint8_t bits[], size_t len,
                          const std::string& hash_name);

template<typename Alloc>
std::string create_hex_fingerprint(const std::vector<uint8_t, Alloc>& vec,
                                   const std::string& hash_name)
   {
   return create_hex_fingerprint(vec.data(), vec.size(), hash_name);
   }


}

namespace Botan {

class X509_DN;
class BigInt;

/**
* Interface for a credentials manager.
*
* A type is a fairly static value that represents the general nature
* of the transaction occurring. Currently used values are "tls-client"
* and "tls-server". Context represents a hostname, email address,
* username, or other identifier.
*/
class BOTAN_PUBLIC_API(2,0) Credentials_Manager
   {
   public:
      virtual ~Credentials_Manager() = default;

      /**
      * Return a list of the certificates of CAs that we trust in this
      * type/context.
      *
      * @param type specifies the type of operation occurring
      *
      * @param context specifies a context relative to type. For instance
      *        for type "tls-client", context specifies the servers name.
      */
      virtual std::vector<Certificate_Store*> trusted_certificate_authorities(
         const std::string& type,
         const std::string& context);

      /**
      * Return a cert chain we can use, ordered from leaf to root,
      * or else an empty vector.
      *
      * It is assumed that the caller can get the private key of the
      * leaf with private_key_for
      *
      * @param cert_key_types specifies the key types desired ("RSA",
      *                       "DSA", "ECDSA", etc), or empty if there
      *                       is no preference by the caller.
      *
      * @param acceptable_CAs the CAs the requestor will accept (possibly empty)
      * @param type specifies the type of operation occurring
      * @param context specifies a context relative to type.
      */
      virtual std::vector<X509_Certificate> find_cert_chain(
         const std::vector<std::string>& cert_key_types,
         const std::vector<X509_DN>& acceptable_CAs,
         const std::string& type,
         const std::string& context);

      /**
      * Return a cert chain we can use, ordered from leaf to root,
      * or else an empty vector.
      *
      * This virtual function is deprecated, and will be removed in a
      * future release. Use (and override) find_cert_chain instead.
      *
      * It is assumed that the caller can get the private key of the
      * leaf with private_key_for
      *
      * @param cert_key_types specifies the key types desired ("RSA",
      *                       "DSA", "ECDSA", etc), or empty if there
      *                       is no preference by the caller.
      *
      * @param type specifies the type of operation occurring
      *
      * @param context specifies a context relative to type.
      */
      virtual std::vector<X509_Certificate> cert_chain(
         const std::vector<std::string>& cert_key_types,
         const std::string& type,
         const std::string& context);

      /**
      * Return a cert chain we can use, ordered from leaf to root,
      * or else an empty vector.
      *
      * It is assumed that the caller can get the private key of the
      * leaf with private_key_for
      *
      * @param cert_key_type specifies the type of key requested
      *                      ("RSA", "DSA", "ECDSA", etc)
      *
      * @param type specifies the type of operation occurring
      *
      * @param context specifies a context relative to type.
      */
      std::vector<X509_Certificate> cert_chain_single_type(
         const std::string& cert_key_type,
         const std::string& type,
         const std::string& context);

      /**
      * @return private key associated with this certificate if we should
      *         use it with this context. cert was returned by cert_chain
      * @note this object should retain ownership of the returned key;
      *       it should not be deleted by the caller.
      */
      virtual Private_Key* private_key_for(const X509_Certificate& cert,
                                           const std::string& type,
                                           const std::string& context);

      /**
      * @param type specifies the type of operation occurring
      * @param context specifies a context relative to type.
      * @return true if we should attempt SRP authentication
      */
      virtual bool attempt_srp(const std::string& type,
                               const std::string& context);

      /**
      * @param type specifies the type of operation occurring
      * @param context specifies a context relative to type.
      * @return identifier for client-side SRP auth, if available
                for this type/context. Should return empty string
                if password auth not desired/available.
      */
      virtual std::string srp_identifier(const std::string& type,
                                         const std::string& context);

      /**
      * @param type specifies the type of operation occurring
      * @param context specifies a context relative to type.
      * @param identifier specifies what identifier we want the
      *        password for. This will be a value previously returned
      *        by srp_identifier.
      * @return password for client-side SRP auth, if available
                for this identifier/type/context.
      */
      virtual std::string srp_password(const std::string& type,
                                       const std::string& context,
                                       const std::string& identifier);

      /**
      * Retrieve SRP verifier parameters
      */
      virtual bool srp_verifier(const std::string& type,
                                const std::string& context,
                                const std::string& identifier,
                                std::string& group_name,
                                BigInt& verifier,
                                std::vector<uint8_t>& salt,
                                bool generate_fake_on_unknown);

      /**
      * @param type specifies the type of operation occurring
      * @param context specifies a context relative to type.
      * @return the PSK identity hint for this type/context
      */
      virtual std::string psk_identity_hint(const std::string& type,
                                            const std::string& context);

      /**
      * @param type specifies the type of operation occurring
      * @param context specifies a context relative to type.
      * @param identity_hint was passed by the server (but may be empty)
      * @return the PSK identity we want to use
      */
      virtual std::string psk_identity(const std::string& type,
                                       const std::string& context,
                                       const std::string& identity_hint);

      /**
      * @param type specifies the type of operation occurring
      * @param context specifies a context relative to type.
      * @param identity is a PSK identity previously returned by
               psk_identity for the same type and context.
      * @return the PSK used for identity, or throw an exception if no
      * key exists
      */
      virtual SymmetricKey psk(const std::string& type,
                               const std::string& context,
                               const std::string& identity);
   };

}

namespace Botan {

/**
* Base class for all stream ciphers
*/
class BOTAN_PUBLIC_API(2,0) StreamCipher : public SymmetricAlgorithm
   {
   public:
      virtual ~StreamCipher() = default;

      /**
      * Create an instance based on a name
      * If provider is empty then best available is chosen.
      * @param algo_spec algorithm name
      * @param provider provider implementation to use
      * @return a null pointer if the algo/provider combination cannot be found
      */
      static std::unique_ptr<StreamCipher>
         create(const std::string& algo_spec,
                const std::string& provider = "");

      /**
      * Create an instance based on a name
      * If provider is empty then best available is chosen.
      * @param algo_spec algorithm name
      * @param provider provider implementation to use
      * Throws a Lookup_Error if the algo/provider combination cannot be found
      */
      static std::unique_ptr<StreamCipher>
         create_or_throw(const std::string& algo_spec,
                         const std::string& provider = "");

      /**
      * @return list of available providers for this algorithm, empty if not available
      */
      static std::vector<std::string> providers(const std::string& algo_spec);

      /**
      * Encrypt or decrypt a message
      * @param in the plaintext
      * @param out the byte array to hold the output, i.e. the ciphertext
      * @param len the length of both in and out in bytes
      */
      virtual void cipher(const uint8_t in[], uint8_t out[], size_t len) = 0;

      /**
      * Write keystream bytes to a buffer
      * @param out the byte array to hold the keystream
      * @param len the length of out in bytes
      */
      virtual void write_keystream(uint8_t out[], size_t len)
         {
         clear_mem(out, len);
         cipher1(out, len);
         }

      /**
      * Encrypt or decrypt a message
      * The message is encrypted/decrypted in place.
      * @param buf the plaintext / ciphertext
      * @param len the length of buf in bytes
      */
      void cipher1(uint8_t buf[], size_t len)
         { cipher(buf, buf, len); }

      /**
      * Encrypt a message
      * The message is encrypted/decrypted in place.
      * @param inout the plaintext / ciphertext
      */
      template<typename Alloc>
         void encipher(std::vector<uint8_t, Alloc>& inout)
         { cipher(inout.data(), inout.data(), inout.size()); }

      /**
      * Encrypt a message
      * The message is encrypted in place.
      * @param inout the plaintext / ciphertext
      */
      template<typename Alloc>
         void encrypt(std::vector<uint8_t, Alloc>& inout)
         { cipher(inout.data(), inout.data(), inout.size()); }

      /**
      * Decrypt a message in place
      * The message is decrypted in place.
      * @param inout the plaintext / ciphertext
      */
      template<typename Alloc>
         void decrypt(std::vector<uint8_t, Alloc>& inout)
         { cipher(inout.data(), inout.data(), inout.size()); }

      /**
      * Resync the cipher using the IV
      * @param iv the initialization vector
      * @param iv_len the length of the IV in bytes
      */
      virtual void set_iv(const uint8_t iv[], size_t iv_len) = 0;

      /**
      * Return the default (preferred) nonce length
      * If this function returns 0, then this cipher does not support nonces
      */
      virtual size_t default_iv_length() const { return 0; }

      /**
      * @param iv_len the length of the IV in bytes
      * @return if the length is valid for this algorithm
      */
      virtual bool valid_iv_length(size_t iv_len) const { return (iv_len == 0); }

      /**
      * @return a new object representing the same algorithm as *this
      */
      virtual StreamCipher* clone() const = 0;

      /**
      * Set the offset and the state used later to generate the keystream
      * @param offset the offset where we begin to generate the keystream
      */
      virtual void seek(uint64_t offset) = 0;

      /**
      * @return provider information about this implementation. Default is "base",
      * might also return "sse2", "avx2", "openssl", or some other arbitrary string.
      */
      virtual std::string provider() const { return "base"; }
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(ctr.h)

namespace Botan {

/**
* CTR-BE (Counter mode, big-endian)
*/
class BOTAN_PUBLIC_API(2,0) CTR_BE final : public StreamCipher
   {
   public:
      void cipher(const uint8_t in[], uint8_t out[], size_t length) override;

      void set_iv(const uint8_t iv[], size_t iv_len) override;

      size_t default_iv_length() const override;

      bool valid_iv_length(size_t iv_len) const override;

      Key_Length_Specification key_spec() const override;

      std::string name() const override;

      CTR_BE* clone() const override;

      void clear() override;

      /**
      * @param cipher the block cipher to use
      */
      explicit CTR_BE(BlockCipher* cipher);

      CTR_BE(BlockCipher* cipher, size_t ctr_size);

      void seek(uint64_t offset) override;
   private:
      void key_schedule(const uint8_t key[], size_t key_len) override;
      void add_counter(const uint64_t counter);

      std::unique_ptr<BlockCipher> m_cipher;

      const size_t m_block_size;
      const size_t m_ctr_size;
      const size_t m_ctr_blocks;

      secure_vector<uint8_t> m_counter, m_pad;
      std::vector<uint8_t> m_iv;
      size_t m_pad_pos;
   };

}

namespace Botan {

class BOTAN_PUBLIC_API(2,0) Curve25519_PublicKey : public virtual Public_Key
   {
   public:
      std::string algo_name() const override { return "Curve25519"; }

      size_t estimated_strength() const override { return 128; }

      size_t key_length() const override { return 255; }

      bool check_key(RandomNumberGenerator& rng, bool strong) const override;

      AlgorithmIdentifier algorithm_identifier() const override;

      std::vector<uint8_t> public_key_bits() const override;

      std::vector<uint8_t> public_value() const { return m_public; }

      /**
      * Create a Curve25519 Public Key.
      * @param alg_id the X.509 algorithm identifier
      * @param key_bits DER encoded public key bits
      */
      Curve25519_PublicKey(const AlgorithmIdentifier& alg_id,
                           const std::vector<uint8_t>& key_bits);

      /**
      * Create a Curve25519 Public Key.
      * @param pub 32-byte raw public key
      */
      explicit Curve25519_PublicKey(const std::vector<uint8_t>& pub) : m_public(pub) {}

      /**
      * Create a Curve25519 Public Key.
      * @param pub 32-byte raw public key
      */
      explicit Curve25519_PublicKey(const secure_vector<uint8_t>& pub) :
         m_public(pub.begin(), pub.end()) {}

   protected:
      Curve25519_PublicKey() = default;
      std::vector<uint8_t> m_public;
   };

class BOTAN_PUBLIC_API(2,0) Curve25519_PrivateKey final : public Curve25519_PublicKey,
                                        public virtual Private_Key,
                                        public virtual PK_Key_Agreement_Key
   {
   public:
      /**
      * Construct a private key from the specified parameters.
      * @param alg_id the X.509 algorithm identifier
      * @param key_bits PKCS #8 structure
      */
      Curve25519_PrivateKey(const AlgorithmIdentifier& alg_id,
                            const secure_vector<uint8_t>& key_bits);

      /**
      * Generate a private key.
      * @param rng the RNG to use
      */
      explicit Curve25519_PrivateKey(RandomNumberGenerator& rng);

      /**
      * Construct a private key from the specified parameters.
      * @param secret_key the private key
      */
      explicit Curve25519_PrivateKey(const secure_vector<uint8_t>& secret_key);

      std::vector<uint8_t> public_value() const override { return Curve25519_PublicKey::public_value(); }

      secure_vector<uint8_t> agree(const uint8_t w[], size_t w_len) const;

      const secure_vector<uint8_t>& get_x() const { return m_private; }

      secure_vector<uint8_t> private_key_bits() const override;

      bool check_key(RandomNumberGenerator& rng, bool strong) const override;

      std::unique_ptr<PK_Ops::Key_Agreement>
         create_key_agreement_op(RandomNumberGenerator& rng,
                                 const std::string& params,
                                 const std::string& provider) const override;

   private:
      secure_vector<uint8_t> m_private;
   };

typedef Curve25519_PublicKey X25519_PublicKey;
typedef Curve25519_PrivateKey X25519_PrivateKey;

/*
* The types above are just wrappers for curve25519_donna, plus defining
* encodings for public and private keys.
*/
void BOTAN_PUBLIC_API(2,0) curve25519_donna(uint8_t mypublic[32],
                                const uint8_t secret[32],
                                const uint8_t basepoint[32]);

/**
* Exponentiate by the x25519 base point
* @param mypublic output value
* @param secret random scalar
*/
void BOTAN_PUBLIC_API(2,0) curve25519_basepoint(uint8_t mypublic[32],
                                    const uint8_t secret[32]);

}

// Currently exposed in PointGFp
//BOTAN_FUTURE_INTERNAL_HEADER(curve_gfp.h)

namespace Botan {

class BOTAN_UNSTABLE_API CurveGFp_Repr
   {
   public:
      virtual ~CurveGFp_Repr() = default;

      virtual const BigInt& get_p() const = 0;
      virtual const BigInt& get_a() const = 0;
      virtual const BigInt& get_b() const = 0;

      virtual size_t get_p_words() const = 0;

      virtual size_t get_ws_size() const = 0;

      virtual bool is_one(const BigInt& x) const = 0;

      virtual bool a_is_zero() const = 0;

      virtual bool a_is_minus_3() const = 0;

      /*
      * Returns to_curve_rep(get_a())
      */
      virtual const BigInt& get_a_rep() const = 0;

      /*
      * Returns to_curve_rep(get_b())
      */
      virtual const BigInt& get_b_rep() const = 0;

      /*
      * Returns to_curve_rep(1)
      */
      virtual const BigInt& get_1_rep() const = 0;

      virtual BigInt invert_element(const BigInt& x, secure_vector<word>& ws) const = 0;

      virtual void to_curve_rep(BigInt& x, secure_vector<word>& ws) const = 0;

      virtual void from_curve_rep(BigInt& x, secure_vector<word>& ws) const = 0;

      void curve_mul(BigInt& z, const BigInt& x, const BigInt& y,
                     secure_vector<word>& ws) const
         {
         BOTAN_DEBUG_ASSERT(x.sig_words() <= get_p_words());
         curve_mul_words(z, x.data(), x.size(), y, ws);
         }

      virtual void curve_mul_words(BigInt& z,
                                   const word x_words[],
                                   const size_t x_size,
                                   const BigInt& y,
                                   secure_vector<word>& ws) const = 0;

      void curve_sqr(BigInt& z, const BigInt& x,
                             secure_vector<word>& ws) const
         {
         BOTAN_DEBUG_ASSERT(x.sig_words() <= get_p_words());
         curve_sqr_words(z, x.data(), x.size(), ws);
         }

      virtual void curve_sqr_words(BigInt& z,
                                   const word x_words[],
                                   size_t x_size,
                                   secure_vector<word>& ws) const = 0;
   };

/**
* This class represents an elliptic curve over GF(p)
*
* There should not be any reason for applications to use this type.
* If you need EC primitives use the interfaces EC_Group and PointGFp
*
* It is likely this class will be removed entirely in a future major
* release.
*/
class BOTAN_UNSTABLE_API CurveGFp final
   {
   public:

      /**
      * Create an uninitialized CurveGFp
      */
      CurveGFp() = default;

      /**
      * Construct the elliptic curve E: y^2 = x^3 + ax + b over GF(p)
      * @param p prime number of the field
      * @param a first coefficient
      * @param b second coefficient
      */
      CurveGFp(const BigInt& p, const BigInt& a, const BigInt& b) :
         m_repr(choose_repr(p, a, b))
         {
         }

      CurveGFp(const CurveGFp&) = default;

      CurveGFp& operator=(const CurveGFp&) = default;

      /**
      * @return curve coefficient a
      */
      const BigInt& get_a() const { return m_repr->get_a(); }

      /**
      * @return curve coefficient b
      */
      const BigInt& get_b() const { return m_repr->get_b(); }

      /**
      * Get prime modulus of the field of the curve
      * @return prime modulus of the field of the curve
      */
      const BigInt& get_p() const { return m_repr->get_p(); }

      size_t get_p_words() const { return m_repr->get_p_words(); }

      size_t get_ws_size() const { return m_repr->get_ws_size(); }

      const BigInt& get_a_rep() const { return m_repr->get_a_rep(); }

      const BigInt& get_b_rep() const { return m_repr->get_b_rep(); }

      const BigInt& get_1_rep() const { return m_repr->get_1_rep(); }

      bool a_is_minus_3() const { return m_repr->a_is_minus_3(); }
      bool a_is_zero() const { return m_repr->a_is_zero(); }

      bool is_one(const BigInt& x) const { return m_repr->is_one(x); }

      BigInt invert_element(const BigInt& x, secure_vector<word>& ws) const
         {
         return m_repr->invert_element(x, ws);
         }

      void to_rep(BigInt& x, secure_vector<word>& ws) const
         {
         m_repr->to_curve_rep(x, ws);
         }

      void from_rep(BigInt& x, secure_vector<word>& ws) const
         {
         m_repr->from_curve_rep(x, ws);
         }

      BigInt from_rep_to_tmp(const BigInt& x, secure_vector<word>& ws) const
         {
         BigInt xt(x);
         m_repr->from_curve_rep(xt, ws);
         return xt;
         }

      // TODO: from_rep taking && ref

      void mul(BigInt& z, const BigInt& x, const BigInt& y, secure_vector<word>& ws) const
         {
         m_repr->curve_mul(z, x, y, ws);
         }

      void mul(BigInt& z, const word x_w[], size_t x_size,
               const BigInt& y, secure_vector<word>& ws) const
         {
         m_repr->curve_mul_words(z, x_w, x_size, y, ws);
         }

      void sqr(BigInt& z, const BigInt& x, secure_vector<word>& ws) const
         {
         m_repr->curve_sqr(z, x, ws);
         }

      void sqr(BigInt& z, const word x_w[], size_t x_size, secure_vector<word>& ws) const
         {
         m_repr->curve_sqr_words(z, x_w, x_size, ws);
         }

      BigInt mul(const BigInt& x, const BigInt& y, secure_vector<word>& ws) const
         {
         return mul_to_tmp(x, y, ws);
         }

      BigInt sqr(const BigInt& x, secure_vector<word>& ws) const
         {
         return sqr_to_tmp(x, ws);
         }

      BigInt mul_to_tmp(const BigInt& x, const BigInt& y, secure_vector<word>& ws) const
         {
         BigInt z;
         m_repr->curve_mul(z, x, y, ws);
         return z;
         }

      BigInt sqr_to_tmp(const BigInt& x, secure_vector<word>& ws) const
         {
         BigInt z;
         m_repr->curve_sqr(z, x, ws);
         return z;
         }

      void swap(CurveGFp& other)
         {
         std::swap(m_repr, other.m_repr);
         }

      /**
      * Equality operator
      * @param other a curve
      * @return true iff *this is the same as other
      */
      inline bool operator==(const CurveGFp& other) const
         {
         if(m_repr.get() == other.m_repr.get())
            return true;

         return (get_p() == other.get_p()) &&
                (get_a() == other.get_a()) &&
                (get_b() == other.get_b());
         }

   private:
      static std::shared_ptr<CurveGFp_Repr>
         choose_repr(const BigInt& p, const BigInt& a, const BigInt& b);

      std::shared_ptr<CurveGFp_Repr> m_repr;
   };

inline bool operator!=(const CurveGFp& lhs, const CurveGFp& rhs)
   {
   return !(lhs == rhs);
   }

}

namespace std {

template<> inline
void swap<Botan::CurveGFp>(Botan::CurveGFp& curve1,
                           Botan::CurveGFp& curve2) noexcept
   {
   curve1.swap(curve2);
   }

} // namespace std

BOTAN_FUTURE_INTERNAL_HEADER(curve_nistp.h)

namespace Botan {

/**
* NIST Prime reduction functions.
*
* Reduces the value in place
*
* ws is a workspace function which is used as a temporary,
* and will be resized as needed.
*/
BOTAN_PUBLIC_API(2,0) const BigInt& prime_p521();
BOTAN_PUBLIC_API(2,0) void redc_p521(BigInt& x, secure_vector<word>& ws);

/*
Previously this macro indicated if the P-{192,224,256,384} reducers
were available. Now they are always enabled and this macro has no meaning.
The define will be removed in a future major release.
*/
#define BOTAN_HAS_NIST_PRIME_REDUCERS_W32

BOTAN_PUBLIC_API(2,0) const BigInt& prime_p384();
BOTAN_PUBLIC_API(2,0) void redc_p384(BigInt& x, secure_vector<word>& ws);

BOTAN_PUBLIC_API(2,0) const BigInt& prime_p256();
BOTAN_PUBLIC_API(2,0) void redc_p256(BigInt& x, secure_vector<word>& ws);

BOTAN_PUBLIC_API(2,0) const BigInt& prime_p224();
BOTAN_PUBLIC_API(2,0) void redc_p224(BigInt& x, secure_vector<word>& ws);

BOTAN_PUBLIC_API(2,0) const BigInt& prime_p192();
BOTAN_PUBLIC_API(2,0) void redc_p192(BigInt& x, secure_vector<word>& ws);

}

namespace Botan {

class BOTAN_PUBLIC_API(2,0) SQL_Database
   {
   public:

      class BOTAN_PUBLIC_API(2,0) SQL_DB_Error final : public Exception
         {
         public:
            explicit SQL_DB_Error(const std::string& what) :
               Exception("SQL database", what),
               m_rc(0)
               {}

            SQL_DB_Error(const std::string& what, int rc) :
               Exception("SQL database", what),
               m_rc(rc)
               {}

            ErrorType error_type() const noexcept override { return Botan::ErrorType::DatabaseError; }

            int error_code() const noexcept override { return m_rc; }
         private:
            int m_rc;
         };

      class BOTAN_PUBLIC_API(2,0) Statement
         {
         public:
            /* Bind statement parameters */
            virtual void bind(int column, const std::string& str) = 0;

            virtual void bind(int column, size_t i) = 0;

            virtual void bind(int column, std::chrono::system_clock::time_point time) = 0;

            virtual void bind(int column, const std::vector<uint8_t>& blob) = 0;

            virtual void bind(int column, const uint8_t* data, size_t len) = 0;

            /* Get output */
            virtual std::pair<const uint8_t*, size_t> get_blob(int column) = 0;

            virtual std::string get_str(int column) = 0;

            virtual size_t get_size_t(int column) = 0;

            /* Run to completion */
            virtual size_t spin() = 0;

            /* Maybe update */
            virtual bool step() = 0;

            virtual ~Statement() = default;
         };

      /*
      * Create a new statement for execution.
      * Use ?1, ?2, ?3, etc for parameters to set later with bind
      */
      virtual std::shared_ptr<Statement> new_statement(const std::string& base_sql) const = 0;

      virtual size_t row_count(const std::string& table_name) = 0;

      virtual void create_table(const std::string& table_schema) = 0;

      virtual ~SQL_Database() = default;
};

}

namespace Botan {

class X509_Certificate;
class Data_Store;
class Public_Key;

/**
* Check that key constraints are permitted for a specific public key.
* @param pub_key the public key on which the constraints shall be enforced on
* @param constraints the constraints that shall be enforced on the key
* @throw Invalid_Argument if the given constraints are not permitted for this key
*/
BOTAN_PUBLIC_API(2,0) void verify_cert_constraints_valid_for_key_type(const Public_Key& pub_key,
                                                                      Key_Constraints constraints);

std::string BOTAN_PUBLIC_API(2,0) key_constraints_to_string(Key_Constraints);

/**
* Distinguished Name
*/
class BOTAN_PUBLIC_API(2,0) X509_DN final : public ASN1_Object
   {
   public:
      X509_DN() = default;

      explicit X509_DN(const std::multimap<OID, std::string>& args)
         {
         for(auto i : args)
            add_attribute(i.first, i.second);
         }

      explicit X509_DN(const std::multimap<std::string, std::string>& args)
         {
         for(auto i : args)
            add_attribute(i.first, i.second);
         }

      void encode_into(DER_Encoder&) const override;
      void decode_from(BER_Decoder&) override;

      bool has_field(const OID& oid) const;
      ASN1_String get_first_attribute(const OID& oid) const;

      /*
      * Return the BER encoded data, if any
      */
      const std::vector<uint8_t>& get_bits() const { return m_dn_bits; }

      bool empty() const { return m_rdn.empty(); }

      std::string to_string() const;

      const std::vector<std::pair<OID,ASN1_String>>& dn_info() const { return m_rdn; }

      std::multimap<OID, std::string> get_attributes() const;
      std::multimap<std::string, std::string> contents() const;

      bool has_field(const std::string& attr) const;
      std::vector<std::string> get_attribute(const std::string& attr) const;
      std::string get_first_attribute(const std::string& attr) const;

      void add_attribute(const std::string& key, const std::string& val);

      void add_attribute(const OID& oid, const std::string& val)
         {
         add_attribute(oid, ASN1_String(val));
         }

      void add_attribute(const OID& oid, const ASN1_String& val);

      static std::string deref_info_field(const std::string& key);

      /**
      * Lookup upper bounds in characters for the length of distinguished name fields
      * as given in RFC 5280, Appendix A.
      *
      * @param oid the oid of the DN to lookup
      * @return the upper bound, or zero if no ub is known to Botan
      */
      static size_t lookup_ub(const OID& oid);

   private:
      std::vector<std::pair<OID,ASN1_String>> m_rdn;
      std::vector<uint8_t> m_dn_bits;
   };

bool BOTAN_PUBLIC_API(2,0) operator==(const X509_DN& dn1, const X509_DN& dn2);
bool BOTAN_PUBLIC_API(2,0) operator!=(const X509_DN& dn1, const X509_DN& dn2);

/*
The ordering here is arbitrary and may change from release to release.
It is intended for allowing DNs as keys in std::map and similiar containers
*/
bool BOTAN_PUBLIC_API(2,0) operator<(const X509_DN& dn1, const X509_DN& dn2);

BOTAN_PUBLIC_API(2,0) std::ostream& operator<<(std::ostream& out, const X509_DN& dn);
BOTAN_PUBLIC_API(2,0) std::istream& operator>>(std::istream& in, X509_DN& dn);

/**
* Alternative Name
*/
class BOTAN_PUBLIC_API(2,0) AlternativeName final : public ASN1_Object
   {
   public:
      void encode_into(DER_Encoder&) const override;
      void decode_from(BER_Decoder&) override;

      std::multimap<std::string, std::string> contents() const;

      bool has_field(const std::string& attr) const;
      std::vector<std::string> get_attribute(const std::string& attr) const;

      std::string get_first_attribute(const std::string& attr) const;

      void add_attribute(const std::string& type, const std::string& value);
      void add_othername(const OID& oid, const std::string& value, ASN1_Tag type);

      const std::multimap<std::string, std::string>& get_attributes() const
         {
         return m_alt_info;
         }

      const std::multimap<OID, ASN1_String>& get_othernames() const
         {
         return m_othernames;
         }

      X509_DN dn() const;

      bool has_items() const;

      AlternativeName(const std::string& email_addr = "",
                      const std::string& uri = "",
                      const std::string& dns = "",
                      const std::string& ip_address = "");
   private:
      std::multimap<std::string, std::string> m_alt_info;
      std::multimap<OID, ASN1_String> m_othernames;
   };

/**
* Attribute
*/
class BOTAN_PUBLIC_API(2,0) Attribute final : public ASN1_Object
   {
   public:
      void encode_into(DER_Encoder& to) const override;
      void decode_from(BER_Decoder& from) override;

      Attribute() = default;
      Attribute(const OID&, const std::vector<uint8_t>&);
      Attribute(const std::string&, const std::vector<uint8_t>&);

      const OID& get_oid() const { return oid; }

      const std::vector<uint8_t>& get_parameters() const { return parameters; }

   BOTAN_DEPRECATED_PUBLIC_MEMBER_VARIABLES:
      /*
      * These values are public for historical reasons, but in a future release
      * they will be made private. Do not access them.
      */
      OID oid;
      std::vector<uint8_t> parameters;
   };

/**
* @brief X.509 GeneralName Type
*
* Handles parsing GeneralName types in their BER and canonical string
* encoding. Allows matching GeneralNames against each other using
* the rules laid out in the RFC 5280, sec. 4.2.1.10 (Name Contraints).
*/
class BOTAN_PUBLIC_API(2,0) GeneralName final : public ASN1_Object
   {
   public:
      enum MatchResult : int
            {
            All,
            Some,
            None,
            NotFound,
            UnknownType,
            };

      /**
      * Creates an empty GeneralName.
      */
      GeneralName() = default;

      /**
      * Creates a new GeneralName for its string format.
      * @param str type and name, colon-separated, e.g., "DNS:google.com"
      */
      GeneralName(const std::string& str);

      void encode_into(DER_Encoder&) const override;

      void decode_from(BER_Decoder&) override;

      /**
      * @return Type of the name. Can be DN, DNS, IP, RFC822 or URI.
      */
      const std::string& type() const { return m_type; }

      /**
      * @return The name as string. Format depends on type.
      */
      const std::string& name() const { return m_name; }

      /**
      * Checks whether a given certificate (partially) matches this name.
      * @param cert certificate to be matched
      * @return the match result
      */
      MatchResult matches(const X509_Certificate& cert) const;

   private:
      std::string m_type;
      std::string m_name;

      bool matches_dns(const std::string&) const;
      bool matches_dn(const std::string&) const;
      bool matches_ip(const std::string&) const;
   };

std::ostream& operator<<(std::ostream& os, const GeneralName& gn);

/**
* @brief A single Name Constraint
*
* The Name Constraint extension adds a minimum and maximum path
* length to a GeneralName to form a constraint. The length limits
* are currently unused.
*/
class BOTAN_PUBLIC_API(2,0) GeneralSubtree final : public ASN1_Object
   {
   public:
      /**
      * Creates an empty name constraint.
      */
      GeneralSubtree() : m_base(), m_minimum(0), m_maximum(std::numeric_limits<std::size_t>::max())
      {}

      /***
      * Creates a new name constraint.
      * @param base name
      * @param min minimum path length
      * @param max maximum path length
      */
      GeneralSubtree(const GeneralName& base, size_t min, size_t max)
      : m_base(base), m_minimum(min), m_maximum(max)
      {}

      /**
      * Creates a new name constraint for its string format.
      * @param str name constraint
      */
      GeneralSubtree(const std::string& str);

      void encode_into(DER_Encoder&) const override;

      void decode_from(BER_Decoder&) override;

      /**
      * @return name
      */
      const GeneralName& base() const { return m_base; }

      /**
      * @return minimum path length
      */
      size_t minimum() const { return m_minimum; }

      /**
      * @return maximum path length
      */
      size_t maximum() const { return m_maximum; }

   private:
      GeneralName m_base;
      size_t m_minimum;
      size_t m_maximum;
   };

std::ostream& operator<<(std::ostream& os, const GeneralSubtree& gs);

/**
* @brief Name Constraints
*
* Wraps the Name Constraints associated with a certificate.
*/
class BOTAN_PUBLIC_API(2,0) NameConstraints final
   {
   public:
      /**
      * Creates an empty name NameConstraints.
      */
      NameConstraints() : m_permitted_subtrees(), m_excluded_subtrees() {}

      /**
      * Creates NameConstraints from a list of permitted and excluded subtrees.
      * @param permitted_subtrees names for which the certificate is permitted
      * @param excluded_subtrees names for which the certificate is not permitted
      */
      NameConstraints(std::vector<GeneralSubtree>&& permitted_subtrees,
                    std::vector<GeneralSubtree>&& excluded_subtrees)
      : m_permitted_subtrees(permitted_subtrees), m_excluded_subtrees(excluded_subtrees)
      {}

      /**
      * @return permitted names
      */
      const std::vector<GeneralSubtree>& permitted() const { return m_permitted_subtrees; }

      /**
      * @return excluded names
      */
      const std::vector<GeneralSubtree>& excluded() const { return m_excluded_subtrees; }

   private:
      std::vector<GeneralSubtree> m_permitted_subtrees;
      std::vector<GeneralSubtree> m_excluded_subtrees;
   };

/**
* X.509 Certificate Extension
*/
class BOTAN_PUBLIC_API(2,0) Certificate_Extension
   {
   public:
      /**
      * @return OID representing this extension
      */
      virtual OID oid_of() const = 0;

      /*
      * @return specific OID name
      * If possible OIDS table should match oid_name to OIDS, ie
      * OID::from_string(ext->oid_name()) == ext->oid_of()
      * Should return empty string if OID is not known
      */
      virtual std::string oid_name() const = 0;

      /**
      * Make a copy of this extension
      * @return copy of this
      */
      virtual Certificate_Extension* copy() const = 0;

      /*
      * Add the contents of this extension into the information
      * for the subject and/or issuer, as necessary.
      * @param subject the subject info
      * @param issuer the issuer info
      */
      virtual void contents_to(Data_Store& subject,
                               Data_Store& issuer) const = 0;

      /*
      * Callback visited during path validation.
      *
      * An extension can implement this callback to inspect
      * the path during path validation.
      *
      * If an error occurs during validation of this extension,
      * an appropriate status code shall be added to cert_status.
      *
      * @param subject Subject certificate that contains this extension
      * @param issuer Issuer certificate
      * @param status Certificate validation status codes for subject certificate
      * @param cert_path Certificate path which is currently validated
      * @param pos Position of subject certificate in cert_path
      */
      virtual void validate(const X509_Certificate& subject, const X509_Certificate& issuer,
            const std::vector<std::shared_ptr<const X509_Certificate>>& cert_path,
            std::vector<std::set<Certificate_Status_Code>>& cert_status,
            size_t pos);

      virtual ~Certificate_Extension() = default;
   protected:
      friend class Extensions;
      virtual bool should_encode() const { return true; }
      virtual std::vector<uint8_t> encode_inner() const = 0;
      virtual void decode_inner(const std::vector<uint8_t>&) = 0;
   };

/**
* X.509 Certificate Extension List
*/
class BOTAN_PUBLIC_API(2,0) Extensions final : public ASN1_Object
   {
   public:
      /**
      * Look up an object in the extensions, based on OID Returns
      * nullptr if not set, if the extension was either absent or not
      * handled. The pointer returned is owned by the Extensions
      * object.
      * This would be better with an optional<T> return value
      */
      const Certificate_Extension* get_extension_object(const OID& oid) const;

      template<typename T>
      const T* get_extension_object_as(const OID& oid = T::static_oid()) const
         {
         if(const Certificate_Extension* extn = get_extension_object(oid))
            {
            // Unknown_Extension oid_name is empty
            if(extn->oid_name().empty())
               {
               return nullptr;
               }
            else if(const T* extn_as_T = dynamic_cast<const T*>(extn))
               {
               return extn_as_T;
               }
            else
               {
               throw Decoding_Error("Exception::get_extension_object_as dynamic_cast failed");
               }
            }

         return nullptr;
         }

      /**
      * Return the set of extensions in the order they appeared in the certificate
      * (or as they were added, if constructed)
      */
      const std::vector<OID>& get_extension_oids() const
         {
         return m_extension_oids;
         }

      /**
      * Return true if an extension was set
      */
      bool extension_set(const OID& oid) const;

      /**
      * Return true if an extesion was set and marked critical
      */
      bool critical_extension_set(const OID& oid) const;

      /**
      * Return the raw bytes of the extension
      * Will throw if OID was not set as an extension.
      */
      std::vector<uint8_t> get_extension_bits(const OID& oid) const;

      void encode_into(class DER_Encoder&) const override;
      void decode_from(class BER_Decoder&) override;
      void contents_to(Data_Store&, Data_Store&) const;

      /**
      * Adds a new extension to the list.
      * @param extn pointer to the certificate extension (Extensions takes ownership)
      * @param critical whether this extension should be marked as critical
      * @throw Invalid_Argument if the extension is already present in the list
      */
      void add(Certificate_Extension* extn, bool critical = false);

      /**
      * Adds a new extension to the list unless it already exists. If the extension
      * already exists within the Extensions object, the extn pointer will be deleted.
      *
      * @param extn pointer to the certificate extension (Extensions takes ownership)
      * @param critical whether this extension should be marked as critical
      * @return true if the object was added false if the extension was already used
      */
      bool add_new(Certificate_Extension* extn, bool critical = false);

      /**
      * Adds an extension to the list or replaces it.
      * @param extn the certificate extension
      * @param critical whether this extension should be marked as critical
      */
      void replace(Certificate_Extension* extn, bool critical = false);

      /**
      * Remove an extension from the list. Returns true if the
      * extension had been set, false otherwise.
      */
      bool remove(const OID& oid);

      /**
      * Searches for an extension by OID and returns the result.
      * Only the known extensions types declared in this header
      * are searched for by this function.
      * @return Copy of extension with oid, nullptr if not found.
      * Can avoid creating a copy by using get_extension_object function
      */
      std::unique_ptr<Certificate_Extension> get(const OID& oid) const;

      /**
      * Searches for an extension by OID and returns the result decoding
      * it to some arbitrary extension type chosen by the application.
      *
      * Only the unknown extensions, that is, extensions types that
      * are not declared in this header, are searched for by this
      * function.
      *
      * @return Pointer to new extension with oid, nullptr if not found.
      */
      template<typename T>
      std::unique_ptr<T> get_raw(const OID& oid) const
         {
         auto extn_info = m_extension_info.find(oid);

         if(extn_info != m_extension_info.end())
            {
            // Unknown_Extension oid_name is empty
            if(extn_info->second.obj().oid_name() == "")
               {
               std::unique_ptr<T> ext(new T);
               ext->decode_inner(extn_info->second.bits());
               return ext;
               }
            }
         return nullptr;
         }

      /**
      * Returns a copy of the list of extensions together with the corresponding
      * criticality flag. All extensions are encoded as some object, falling back
      * to Unknown_Extension class which simply allows reading the bytes as well
      * as the criticality flag.
      */
      std::vector<std::pair<std::unique_ptr<Certificate_Extension>, bool>> extensions() const;

      /**
      * Returns the list of extensions as raw, encoded bytes
      * together with the corresponding criticality flag.
      * Contains all extensions, including any extensions encoded as Unknown_Extension
      */
      std::map<OID, std::pair<std::vector<uint8_t>, bool>> extensions_raw() const;

      Extensions() {}

      Extensions(const Extensions&) = default;
      Extensions& operator=(const Extensions&) = default;

      Extensions(Extensions&&) = default;
      Extensions& operator=(Extensions&&) = default;

   private:
      static std::unique_ptr<Certificate_Extension>
         create_extn_obj(const OID& oid,
                         bool critical,
                         const std::vector<uint8_t>& body);

      class Extensions_Info
         {
         public:
            Extensions_Info(bool critical,
                            Certificate_Extension* ext) :
               m_obj(ext),
               m_bits(m_obj->encode_inner()),
               m_critical(critical)
               {
               }

            Extensions_Info(bool critical,
                            const std::vector<uint8_t>& encoding,
                            Certificate_Extension* ext) :
               m_obj(ext),
               m_bits(encoding),
               m_critical(critical)
               {
               }

            bool is_critical() const { return m_critical; }
            const std::vector<uint8_t>& bits() const { return m_bits; }
            const Certificate_Extension& obj() const
               {
               BOTAN_ASSERT_NONNULL(m_obj.get());
               return *m_obj.get();
               }

         private:
            std::shared_ptr<Certificate_Extension> m_obj;
            std::vector<uint8_t> m_bits;
            bool m_critical = false;
         };

      std::vector<OID> m_extension_oids;
      std::map<OID, Extensions_Info> m_extension_info;
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(datastor.h)

namespace Botan {

/**
* Data Store
*
* This class is used internally by the library, and exposed for ABI
* reasons. There is no reason for applications to use this type directly.
* It will be removed in a future major release.
*/
class BOTAN_UNSTABLE_API Data_Store final
   {
   public:
      /**
      * A search function
      */
      bool operator==(const Data_Store&) const;

      std::multimap<std::string, std::string> search_for(
         std::function<bool (std::string, std::string)> predicate) const;

      std::vector<std::string> get(const std::string&) const;

      std::string get1(const std::string& key) const;

      std::string get1(const std::string& key,
                       const std::string& default_value) const;

      std::vector<uint8_t> get1_memvec(const std::string&) const;
      uint32_t get1_uint32(const std::string&, uint32_t = 0) const;

      bool has_value(const std::string&) const;

      void add(const std::multimap<std::string, std::string>&);
      void add(const std::string&, const std::string&);
      void add(const std::string&, uint32_t);
      void add(const std::string&, const secure_vector<uint8_t>&);
      void add(const std::string&, const std::vector<uint8_t>&);
   private:
      std::multimap<std::string, std::string> m_contents;
   };

/*
* Data Store Extraction Operations
*/

/*
* Create and populate a X509_DN
* @param info data store containing DN information
* @return DN containing attributes from data store
*/
BOTAN_PUBLIC_API(2,0) X509_DN
BOTAN_DEPRECATED("Avoid roundtripping names through Data_Store")
create_dn(const Data_Store& info);

/*
* Create and populate an AlternativeName
* @param info data store containing AlternativeName information
* @return AlternativeName containing attributes from data store
*/
BOTAN_PUBLIC_API(2,0) AlternativeName
BOTAN_DEPRECATED("Avoid roundtripping names through Data_Store")
create_alt_name(const Data_Store& info);


}

namespace Botan {

class BigInt;

/**
* General DER Encoding Object
*/
class BOTAN_PUBLIC_API(2,0) DER_Encoder final
   {
   public:
      typedef std::function<void (const uint8_t[], size_t)> append_fn;

      /**
      * DER encode, writing to an internal buffer
      * Use get_contents or get_contents_unlocked to read the results
      * after all encoding is completed.
      */
      DER_Encoder() = default;

      /**
      * DER encode, writing to @param vec
      * If this constructor is used, get_contents* may not be called.
      */
      DER_Encoder(secure_vector<uint8_t>& vec);

      /**
      * DER encode, writing to @param vec
      * If this constructor is used, get_contents* may not be called.
      */
      DER_Encoder(std::vector<uint8_t>& vec);

      /**
      * DER encode, calling append to write output
      * If this constructor is used, get_contents* may not be called.
      */
      DER_Encoder(append_fn append) : m_append_output(append) {}

      secure_vector<uint8_t> get_contents();

      /**
      * Return the encoded contents as a std::vector
      *
      * If using this function, instead pass a std::vector to the
      * contructor of DER_Encoder where the output will be placed. This
      * avoids several unecessary copies.
      */
      std::vector<uint8_t> BOTAN_DEPRECATED("Use DER_Encoder(vector) instead") get_contents_unlocked();

      DER_Encoder& start_cons(ASN1_Tag type_tag,
                              ASN1_Tag class_tag = UNIVERSAL);
      DER_Encoder& end_cons();

      DER_Encoder& start_explicit(uint16_t type_tag);
      DER_Encoder& end_explicit();

      /**
      * Insert raw bytes directly into the output stream
      */
      DER_Encoder& raw_bytes(const uint8_t val[], size_t len);

      template<typename Alloc>
      DER_Encoder& raw_bytes(const std::vector<uint8_t, Alloc>& val)
         {
         return raw_bytes(val.data(), val.size());
         }

      DER_Encoder& encode_null();
      DER_Encoder& encode(bool b);
      DER_Encoder& encode(size_t s);
      DER_Encoder& encode(const BigInt& n);
      DER_Encoder& encode(const uint8_t val[], size_t len, ASN1_Tag real_type);

      template<typename Alloc>
      DER_Encoder& encode(const std::vector<uint8_t, Alloc>& vec, ASN1_Tag real_type)
         {
         return encode(vec.data(), vec.size(), real_type);
         }

      DER_Encoder& encode(bool b,
                          ASN1_Tag type_tag,
                          ASN1_Tag class_tag = CONTEXT_SPECIFIC);

      DER_Encoder& encode(size_t s,
                          ASN1_Tag type_tag,
                          ASN1_Tag class_tag = CONTEXT_SPECIFIC);

      DER_Encoder& encode(const BigInt& n,
                          ASN1_Tag type_tag,
                          ASN1_Tag class_tag = CONTEXT_SPECIFIC);

      DER_Encoder& encode(const uint8_t v[], size_t len,
                          ASN1_Tag real_type,
                          ASN1_Tag type_tag,
                          ASN1_Tag class_tag = CONTEXT_SPECIFIC);

      template<typename Alloc>
      DER_Encoder& encode(const std::vector<uint8_t, Alloc>& bytes,
                          ASN1_Tag real_type,
                          ASN1_Tag type_tag, ASN1_Tag class_tag)
         {
         return encode(bytes.data(), bytes.size(),
                       real_type, type_tag, class_tag);
         }

      template<typename T>
      DER_Encoder& encode_optional(const T& value, const T& default_value)
         {
         if(value != default_value)
            encode(value);
         return (*this);
         }

      template<typename T>
      DER_Encoder& encode_list(const std::vector<T>& values)
         {
         for(size_t i = 0; i != values.size(); ++i)
            encode(values[i]);
         return (*this);
         }

      /*
      * Request for an object to encode itself to this stream
      */
      DER_Encoder& encode(const ASN1_Object& obj);

      /*
      * Conditionally write some values to the stream
      */
      DER_Encoder& encode_if(bool pred, DER_Encoder& enc)
         {
         if(pred)
            return raw_bytes(enc.get_contents());
         return (*this);
         }

      DER_Encoder& encode_if(bool pred, const ASN1_Object& obj)
         {
         if(pred)
            encode(obj);
         return (*this);
         }

      DER_Encoder& add_object(ASN1_Tag type_tag, ASN1_Tag class_tag,
                              const uint8_t rep[], size_t length);

      DER_Encoder& add_object(ASN1_Tag type_tag, ASN1_Tag class_tag,
                              const std::vector<uint8_t>& rep)
         {
         return add_object(type_tag, class_tag, rep.data(), rep.size());
         }

      DER_Encoder& add_object(ASN1_Tag type_tag, ASN1_Tag class_tag,
                              const secure_vector<uint8_t>& rep)
         {
         return add_object(type_tag, class_tag, rep.data(), rep.size());
         }

      DER_Encoder& add_object(ASN1_Tag type_tag, ASN1_Tag class_tag,
                              const std::string& str);

      DER_Encoder& add_object(ASN1_Tag type_tag, ASN1_Tag class_tag,
                              uint8_t val);

   private:
      class DER_Sequence final
         {
         public:
            ASN1_Tag tag_of() const;

            void push_contents(DER_Encoder& der);

            void add_bytes(const uint8_t val[], size_t len);

            void add_bytes(const uint8_t hdr[], size_t hdr_len,
                           const uint8_t val[], size_t val_len);

            DER_Sequence(ASN1_Tag, ASN1_Tag);

            DER_Sequence(DER_Sequence&& seq)
               {
               std::swap(m_type_tag, seq.m_type_tag);
               std::swap(m_class_tag, seq.m_class_tag);
               std::swap(m_contents, seq.m_contents);
               std::swap(m_set_contents, seq.m_set_contents);
               }

            DER_Sequence& operator=(DER_Sequence&& seq)
               {
               std::swap(m_type_tag, seq.m_type_tag);
               std::swap(m_class_tag, seq.m_class_tag);
               std::swap(m_contents, seq.m_contents);
               std::swap(m_set_contents, seq.m_set_contents);
               return (*this);
               }

            DER_Sequence(const DER_Sequence& seq) = default;

            DER_Sequence& operator=(const DER_Sequence& seq) = default;

         private:
            ASN1_Tag m_type_tag, m_class_tag;
            secure_vector<uint8_t> m_contents;
            std::vector< secure_vector<uint8_t> > m_set_contents;
         };

      append_fn m_append_output;
      secure_vector<uint8_t> m_default_outbuf;
      std::vector<DER_Sequence> m_subsequences;
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(des.h)

namespace Botan {

/**
* DES
*/
class BOTAN_PUBLIC_API(2,0) DES final : public Block_Cipher_Fixed_Params<8, 8>
   {
   public:
      void encrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const override;
      void decrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const override;

      void clear() override;
      std::string name() const override { return "DES"; }
      BlockCipher* clone() const override { return new DES; }
   private:
      void key_schedule(const uint8_t[], size_t) override;

      secure_vector<uint32_t> m_round_key;
   };

/**
* Triple DES
*/
class BOTAN_PUBLIC_API(2,0) TripleDES final : public Block_Cipher_Fixed_Params<8, 16, 24, 8>
   {
   public:
      void encrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const override;
      void decrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const override;

      void clear() override;
      std::string name() const override { return "TripleDES"; }
      BlockCipher* clone() const override { return new TripleDES; }
   private:
      void key_schedule(const uint8_t[], size_t) override;

      secure_vector<uint32_t> m_round_key;
   };

/*
* DES Tables
*/
extern const uint32_t DES_SPBOX1[256];
extern const uint32_t DES_SPBOX2[256];
extern const uint32_t DES_SPBOX3[256];
extern const uint32_t DES_SPBOX4[256];
extern const uint32_t DES_SPBOX5[256];
extern const uint32_t DES_SPBOX6[256];
extern const uint32_t DES_SPBOX7[256];
extern const uint32_t DES_SPBOX8[256];

}

BOTAN_FUTURE_INTERNAL_HEADER(desx.h)

namespace Botan {

/**
* DESX
*/
class BOTAN_PUBLIC_API(2,0) DESX final : public Block_Cipher_Fixed_Params<8, 24>
   {
   public:
      void encrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const override;
      void decrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const override;

      void clear() override;
      std::string name() const override { return "DESX"; }
      BlockCipher* clone() const override { return new DESX; }
   private:
      void key_schedule(const uint8_t[], size_t) override;
      secure_vector<uint8_t> m_K1, m_K2;
      DES m_des;
   };

}

namespace Botan {

class Montgomery_Params;
class DL_Group_Data;

enum class DL_Group_Source {
   Builtin,
   RandomlyGenerated,
   ExternalSource,
};

/**
* This class represents discrete logarithm groups. It holds a prime
* modulus p, a generator g, and (optionally) a prime q which is a
* factor of (p-1). In most cases g generates the order-q subgroup.
*/
class BOTAN_PUBLIC_API(2,0) DL_Group final
   {
   public:
      /**
      * Determine the prime creation for DL groups.
      */
      enum PrimeType { Strong, Prime_Subgroup, DSA_Kosherizer };

      /**
      * The DL group encoding format variants.
      */
      enum Format {
         ANSI_X9_42,
         ANSI_X9_57,
         PKCS_3,

         DSA_PARAMETERS = ANSI_X9_57,
         DH_PARAMETERS = ANSI_X9_42,
         ANSI_X9_42_DH_PARAMETERS = ANSI_X9_42,
         PKCS3_DH_PARAMETERS = PKCS_3
      };

      /**
      * Construct a DL group with uninitialized internal value.
      * Use this constructor is you wish to set the groups values
      * from a DER or PEM encoded group.
      */
      DL_Group() = default;

      /**
      * Construct a DL group that is registered in the configuration.
      * @param name the name of the group, for example "modp/ietf/3072"
      *
      * @warning This constructor also accepts PEM inputs. This behavior is
      * deprecated and will be removed in a future major release. Instead
      * use DL_Group_from_PEM function
      */
      explicit DL_Group(const std::string& name);

      /*
      * Read a PEM representation
      */
      static DL_Group DL_Group_from_PEM(const std::string& pem);

      /**
      * Create a new group randomly.
      * @param rng the random number generator to use
      * @param type specifies how the creation of primes p and q shall
      * be performed. If type=Strong, then p will be determined as a
      * safe prime, and q will be chosen as (p-1)/2. If
      * type=Prime_Subgroup and qbits = 0, then the size of q will be
      * determined according to the estimated difficulty of the DL
      * problem. If type=DSA_Kosherizer, DSA primes will be created.
      * @param pbits the number of bits of p
      * @param qbits the number of bits of q. Leave it as 0 to have
      * the value determined according to pbits.
      */
      DL_Group(RandomNumberGenerator& rng, PrimeType type,
               size_t pbits, size_t qbits = 0);

      /**
      * Create a DSA group with a given seed.
      * @param rng the random number generator to use
      * @param seed the seed to use to create the random primes
      * @param pbits the desired bit size of the prime p
      * @param qbits the desired bit size of the prime q.
      */
      DL_Group(RandomNumberGenerator& rng,
               const std::vector<uint8_t>& seed,
               size_t pbits = 1024, size_t qbits = 0);

      /**
      * Create a DL group.
      * @param p the prime p
      * @param g the base g
      */
      DL_Group(const BigInt& p, const BigInt& g);

      /**
      * Create a DL group.
      * @param p the prime p
      * @param q the prime q
      * @param g the base g
      */
      DL_Group(const BigInt& p, const BigInt& q, const BigInt& g);

      /**
      * Decode a BER-encoded DL group param
      */
      DL_Group(const uint8_t ber[], size_t ber_len, Format format);

      /**
      * Decode a BER-encoded DL group param
      */
      template<typename Alloc>
         DL_Group(const std::vector<uint8_t, Alloc>& ber, Format format) :
         DL_Group(ber.data(), ber.size(), format) {}

      /**
      * Get the prime p.
      * @return prime p
      */
      const BigInt& get_p() const;

      /**
      * Get the prime q, returns zero if q is not used
      * @return prime q
      */
      const BigInt& get_q() const;

      /**
      * Get the base g.
      * @return base g
      */
      const BigInt& get_g() const;

      /**
      * Perform validity checks on the group.
      * @param rng the rng to use
      * @param strong whether to perform stronger by lengthier tests
      * @return true if the object is consistent, false otherwise
      */
      bool verify_group(RandomNumberGenerator& rng, bool strong = true) const;

      /**
      * Verify a public element, ie check if y = g^x for some x.
      *
      * This is not a perfect test. It verifies that 1 < y < p and (if q is set)
      * that y is in the subgroup of size q.
      */
      bool verify_public_element(const BigInt& y) const;

      /**
      * Verify a pair of elements y = g^x
      *
      * This verifies that 1 < x,y < p and that y=g^x mod p
      */
      bool verify_element_pair(const BigInt& y, const BigInt& x) const;

      /**
      * Encode this group into a string using PEM encoding.
      * @param format the encoding format
      * @return string holding the PEM encoded group
      */
      std::string PEM_encode(Format format) const;

      /**
      * Encode this group into a string using DER encoding.
      * @param format the encoding format
      * @return string holding the DER encoded group
      */
      std::vector<uint8_t> DER_encode(Format format) const;

      /**
      * Reduce an integer modulo p
      * @return x % p
      */
      BigInt mod_p(const BigInt& x) const;

      /**
      * Multiply and reduce an integer modulo p
      * @return (x*y) % p
      */
      BigInt multiply_mod_p(const BigInt& x, const BigInt& y) const;

      /**
      * Return the inverse of x mod p
      */
      BigInt inverse_mod_p(const BigInt& x) const;

      /**
      * Reduce an integer modulo q
      * Throws if q is unset on this DL_Group
      * @return x % q
      */
      BigInt mod_q(const BigInt& x) const;

      /**
      * Multiply and reduce an integer modulo q
      * Throws if q is unset on this DL_Group
      * @return (x*y) % q
      */
      BigInt multiply_mod_q(const BigInt& x, const BigInt& y) const;

      /**
      * Multiply and reduce an integer modulo q
      * Throws if q is unset on this DL_Group
      * @return (x*y*z) % q
      */
      BigInt multiply_mod_q(const BigInt& x, const BigInt& y, const BigInt& z) const;

      /**
      * Square and reduce an integer modulo q
      * Throws if q is unset on this DL_Group
      * @return (x*x) % q
      */
      BigInt square_mod_q(const BigInt& x) const;

      /**
      * Return the inverse of x mod q
      * Throws if q is unset on this DL_Group
      */
      BigInt inverse_mod_q(const BigInt& x) const;

      /**
      * Modular exponentiation
      *
      * @warning this function leaks the size of x via the number of
      * loop iterations. Use the version taking the maximum size to
      * avoid this.
      *
      * @return (g^x) % p
      */
      BigInt power_g_p(const BigInt& x) const;

      /**
      * Modular exponentiation
      * @param x the exponent
      * @param max_x_bits x is assumed to be at most this many bits long.
      *
      * @return (g^x) % p
      */
      BigInt power_g_p(const BigInt& x, size_t max_x_bits) const;

      /**
      * Multi-exponentiate
      * Return (g^x * y^z) % p
      */
      BigInt multi_exponentiate(const BigInt& x, const BigInt& y, const BigInt& z) const;

      /**
      * Return parameters for Montgomery reduction/exponentiation mod p
      */
      std::shared_ptr<const Montgomery_Params> monty_params_p() const;

      /**
      * Return the size of p in bits
      * Same as get_p().bits()
      */
      size_t p_bits() const;

      /**
      * Return the size of p in bytes
      * Same as get_p().bytes()
      */
      size_t p_bytes() const;

      /**
      * Return the size of q in bits
      * Same as get_q().bits()
      * Throws if q is unset
      */
      size_t q_bits() const;

      /**
      * Return the size of q in bytes
      * Same as get_q().bytes()
      * Throws if q is unset
      */
      size_t q_bytes() const;

      /**
      * Return size in bits of a secret exponent
      *
      * This attempts to balance between the attack costs of NFS
      * (which depends on the size of the modulus) and Pollard's rho
      * (which depends on the size of the exponent).
      *
      * It may vary over time for a particular group, if the attack
      * costs change.
      */
      size_t exponent_bits() const;

      /**
      * Return an estimate of the strength of this group against
      * discrete logarithm attacks (eg NFS). Warning: since this only
      * takes into account known attacks it is by necessity an
      * overestimate of the actual strength.
      */
      size_t estimated_strength() const;

      /**
      * Decode a DER/BER encoded group into this instance.
      * @param ber a vector containing the DER/BER encoded group
      * @param format the format of the encoded group
      *
      * @warning avoid this. Instead use the DL_Group constructor
      */
      void BER_decode(const std::vector<uint8_t>& ber, Format format);

      /**
      * Decode a PEM encoded group into this instance.
      * @param pem the PEM encoding of the group
      */
      void BOTAN_DEPRECATED("Use DL_Group_from_PEM") PEM_decode(const std::string& pem);

      DL_Group_Source source() const;

      /**
      * Return PEM representation of named DL group
      */
      static std::string BOTAN_DEPRECATED("Use DL_Group(name).PEM_encode()")
         PEM_for_named_group(const std::string& name);

      /*
      * For internal use only
      */
      static std::shared_ptr<DL_Group_Data> DL_group_info(const std::string& name);

   private:
      static std::shared_ptr<DL_Group_Data> load_DL_group_info(const char* p_str,
                                                               const char* q_str,
                                                               const char* g_str);

      static std::shared_ptr<DL_Group_Data> load_DL_group_info(const char* p_str,
                                                               const char* g_str);

      static std::shared_ptr<DL_Group_Data>
         BER_decode_DL_group(const uint8_t data[], size_t data_len,
                             DL_Group::Format format,
                             DL_Group_Source source);

      const DL_Group_Data& data() const;
      std::shared_ptr<DL_Group_Data> m_data;
   };

}

namespace Botan {

/**
* This class represents discrete logarithm (DL) public keys.
*/
class BOTAN_PUBLIC_API(2,0) DL_Scheme_PublicKey : public virtual Public_Key
   {
   public:
      bool check_key(RandomNumberGenerator& rng, bool) const override;

      AlgorithmIdentifier algorithm_identifier() const override;

      std::vector<uint8_t> public_key_bits() const override;

      /**
      * Get the DL domain parameters of this key.
      * @return DL domain parameters of this key
      */
      const DL_Group& get_domain() const { return m_group; }

      /**
      * Get the DL domain parameters of this key.
      * @return DL domain parameters of this key
      */
      const DL_Group& get_group() const { return m_group; }

      /**
      * Get the public value y with y = g^x mod p where x is the secret key.
      */
      const BigInt& get_y() const { return m_y; }

      /**
      * Get the prime p of the underlying DL group.
      * @return prime p
      */
      const BigInt& group_p() const { return m_group.get_p(); }

      /**
      * Get the prime q of the underlying DL group.
      * @return prime q
      */
      const BigInt& group_q() const { return m_group.get_q(); }

      /**
      * Get the generator g of the underlying DL group.
      * @return generator g
      */
      const BigInt& group_g() const { return m_group.get_g(); }

      /**
      * Get the underlying groups encoding format.
      * @return encoding format
      */
      virtual DL_Group::Format group_format() const = 0;

      size_t key_length() const override;
      size_t estimated_strength() const override;

      DL_Scheme_PublicKey& operator=(const DL_Scheme_PublicKey& other) = default;

   protected:
      DL_Scheme_PublicKey() = default;

      /**
      * Create a public key.
      * @param alg_id the X.509 algorithm identifier
      * @param key_bits DER encoded public key bits
      * @param group_format the underlying groups encoding format
      */
      DL_Scheme_PublicKey(const AlgorithmIdentifier& alg_id,
                          const std::vector<uint8_t>& key_bits,
                          DL_Group::Format group_format);

      DL_Scheme_PublicKey(const DL_Group& group, const BigInt& y);

      /**
      * The DL public key
      */
      BigInt m_y;

      /**
      * The DL group
      */
      DL_Group m_group;
   };

/**
* This class represents discrete logarithm (DL) private keys.
*/
class BOTAN_PUBLIC_API(2,0) DL_Scheme_PrivateKey : public virtual DL_Scheme_PublicKey,
                                       public virtual Private_Key
   {
   public:
      bool check_key(RandomNumberGenerator& rng, bool) const override;

      /**
      * Get the secret key x.
      * @return secret key
      */
      const BigInt& get_x() const { return m_x; }

      secure_vector<uint8_t> private_key_bits() const override;

      DL_Scheme_PrivateKey& operator=(const DL_Scheme_PrivateKey& other) = default;

   protected:
      /**
      * Create a private key.
      * @param alg_id the X.509 algorithm identifier
      * @param key_bits DER encoded private key bits
      * @param group_format the underlying groups encoding format
      */
      DL_Scheme_PrivateKey(const AlgorithmIdentifier& alg_id,
                           const secure_vector<uint8_t>& key_bits,
                           DL_Group::Format group_format);

      DL_Scheme_PrivateKey() = default;

      /**
      * The DL private key
      */
      BigInt m_x;
   };

}

namespace Botan {

/**
* This class represents Diffie-Hellman public keys.
*/
class BOTAN_PUBLIC_API(2,0) DH_PublicKey : public virtual DL_Scheme_PublicKey
   {
   public:
      std::string algo_name() const override { return "DH"; }

      std::vector<uint8_t> public_value() const;

      DL_Group::Format group_format() const override { return DL_Group::ANSI_X9_42; }

      /**
      * Create a public key.
      * @param alg_id the X.509 algorithm identifier
      * @param key_bits DER encoded public key bits
      */
      DH_PublicKey(const AlgorithmIdentifier& alg_id,
                   const std::vector<uint8_t>& key_bits) :
         DL_Scheme_PublicKey(alg_id, key_bits, DL_Group::ANSI_X9_42) {}

      /**
      * Construct a public key with the specified parameters.
      * @param grp the DL group to use in the key
      * @param y the public value y
      */
      DH_PublicKey(const DL_Group& grp, const BigInt& y);
   protected:
      DH_PublicKey() = default;
   };

/**
* This class represents Diffie-Hellman private keys.
*/
class BOTAN_PUBLIC_API(2,0) DH_PrivateKey final : public DH_PublicKey,
                                public PK_Key_Agreement_Key,
                                public virtual DL_Scheme_PrivateKey
   {
   public:
      std::vector<uint8_t> public_value() const override;

      /**
      * Load a private key.
      * @param alg_id the X.509 algorithm identifier
      * @param key_bits PKCS #8 structure
      */
      DH_PrivateKey(const AlgorithmIdentifier& alg_id,
                    const secure_vector<uint8_t>& key_bits);

      /**
      * Create a private key.
      * @param rng random number generator to use
      * @param grp the group to be used in the key
      * @param x the key's secret value (or if zero, generate a new key)
      */
      DH_PrivateKey(RandomNumberGenerator& rng, const DL_Group& grp,
                    const BigInt& x = 0);

      std::unique_ptr<PK_Ops::Key_Agreement>
         create_key_agreement_op(RandomNumberGenerator& rng,
                                 const std::string& params,
                                 const std::string& provider) const override;
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(divide.h)

namespace Botan {

/**
* BigInt Division
* @param x an integer
* @param y a non-zero integer
* @param q will be set to x / y
* @param r will be set to x % y
*/
void BOTAN_UNSTABLE_API vartime_divide(const BigInt& x,
                                       const BigInt& y,
                                       BigInt& q,
                                       BigInt& r);

/**
* BigInt division, const time variant
*
* This runs with control flow independent of the values of x/y.
* Warning: the loop bounds still leak the sizes of x and y.
*
* @param x an integer
* @param y a non-zero integer
* @param q will be set to x / y
* @param r will be set to x % y
*/
void BOTAN_PUBLIC_API(2,9) ct_divide(const BigInt& x,
                                     const BigInt& y,
                                     BigInt& q,
                                     BigInt& r);

inline void divide(const BigInt& x,
                   const BigInt& y,
                   BigInt& q,
                   BigInt& r)
   {
   ct_divide(x, y, q, r);
   }

/**
* BigInt division, const time variant
*
* This runs with control flow independent of the values of x/y.
* Warning: the loop bounds still leak the sizes of x and y.
*
* @param x an integer
* @param y a non-zero integer
* @return x/y with remainder discarded
*/
inline BigInt ct_divide(const BigInt& x, const BigInt& y)
   {
   BigInt q, r;
   ct_divide(x, y, q, r);
   return q;
   }

/**
* BigInt division, const time variant
*
* This runs with control flow independent of the values of x/y.
* Warning: the loop bounds still leak the sizes of x and y.
*
* @param x an integer
* @param y a non-zero integer
* @param q will be set to x / y
* @param r will be set to x % y
*/
void BOTAN_PUBLIC_API(2,9) ct_divide_u8(const BigInt& x,
                                        uint8_t y,
                                        BigInt& q,
                                        uint8_t& r);

/**
* BigInt modulo, const time variant
*
* Using this function is (slightly) cheaper than calling ct_divide and
* using only the remainder.
*
* @param x a non-negative integer
* @param modulo a positive integer
* @return result x % modulo
*/
BigInt BOTAN_PUBLIC_API(2,9) ct_modulo(const BigInt& x,
                                       const BigInt& modulo);

}

namespace Botan {

/**
* DSA Public Key
*/
class BOTAN_PUBLIC_API(2,0) DSA_PublicKey : public virtual DL_Scheme_PublicKey
   {
   public:
      std::string algo_name() const override { return "DSA"; }

      DL_Group::Format group_format() const override { return DL_Group::ANSI_X9_57; }
      size_t message_parts() const override { return 2; }
      size_t message_part_size() const override { return group_q().bytes(); }

      /**
      * Load a public key.
      * @param alg_id the X.509 algorithm identifier
      * @param key_bits DER encoded public key bits
      */
      DSA_PublicKey(const AlgorithmIdentifier& alg_id,
                    const std::vector<uint8_t>& key_bits) :
         DL_Scheme_PublicKey(alg_id, key_bits, DL_Group::ANSI_X9_57)
         {
         }

      /**
      * Create a public key.
      * @param group the underlying DL group
      * @param y the public value y = g^x mod p
      */
      DSA_PublicKey(const DL_Group& group, const BigInt& y);

      std::unique_ptr<PK_Ops::Verification>
         create_verification_op(const std::string& params,
                                const std::string& provider) const override;
   protected:
      DSA_PublicKey() = default;
   };

/**
* DSA Private Key
*/
class BOTAN_PUBLIC_API(2,0) DSA_PrivateKey final : public DSA_PublicKey,
                                 public virtual DL_Scheme_PrivateKey
   {
   public:
      /**
      * Load a private key.
      * @param alg_id the X.509 algorithm identifier
      * @param key_bits DER encoded key bits in ANSI X9.57 format
      */
      DSA_PrivateKey(const AlgorithmIdentifier& alg_id,
                     const secure_vector<uint8_t>& key_bits);

      /**
      * Create a private key.
      * @param rng the RNG to use
      * @param group the underlying DL group
      * @param private_key the private key (if zero, a new random key is generated)
      */
      DSA_PrivateKey(RandomNumberGenerator& rng,
                     const DL_Group& group,
                     const BigInt& private_key = 0);

      bool check_key(RandomNumberGenerator& rng, bool strong) const override;

      std::unique_ptr<PK_Ops::Signature>
         create_signature_op(RandomNumberGenerator& rng,
                             const std::string& params,
                             const std::string& provider) const override;
   };

}

namespace Botan {

/**
* Exception thrown if you try to convert a zero point to an affine
* coordinate
*
* In a future major release this exception type will be removed and its
* usage replaced by Invalid_State
*/
class BOTAN_PUBLIC_API(2,0) Illegal_Transformation final : public Invalid_State
   {
   public:
      explicit Illegal_Transformation(const std::string& err) : Invalid_State(err) {}
   };

/**
* Exception thrown if some form of illegal point is decoded
*
* In a future major release this exception type will be removed and its
* usage replaced by Decoding_Error
*/
class BOTAN_PUBLIC_API(2,0) Illegal_Point final : public Decoding_Error
   {
   public:
      explicit Illegal_Point(const std::string& err) : Decoding_Error(err) {}
   };

/**
* This class represents one point on a curve of GF(p)
*/
class BOTAN_PUBLIC_API(2,0) PointGFp final
   {
   public:
      enum Compression_Type {
         UNCOMPRESSED = 0,
         COMPRESSED   = 1,
         HYBRID       = 2
      };

      enum { WORKSPACE_SIZE = 8 };

      /**
      * Construct an uninitialized PointGFp
      */
      PointGFp() = default;

      /**
      * Construct the zero point
      * @param curve The base curve
      */
      explicit PointGFp(const CurveGFp& curve);

      /**
      * Copy constructor
      */
      PointGFp(const PointGFp&) = default;

      /**
      * Move Constructor
      */
      PointGFp(PointGFp&& other)
         {
         this->swap(other);
         }

      /**
      * Standard Assignment
      */
      PointGFp& operator=(const PointGFp&) = default;

      /**
      * Move Assignment
      */
      PointGFp& operator=(PointGFp&& other)
         {
         if(this != &other)
            this->swap(other);
         return (*this);
         }

      /**
      * Construct a point from its affine coordinates
      * Prefer EC_Group::point(x,y) for this operation.
      * @param curve the base curve
      * @param x affine x coordinate
      * @param y affine y coordinate
      */
      PointGFp(const CurveGFp& curve, const BigInt& x, const BigInt& y);

      /**
      * EC2OSP - elliptic curve to octet string primitive
      * @param format which format to encode using
      */
      std::vector<uint8_t> encode(PointGFp::Compression_Type format) const;

      /**
      * += Operator
      * @param rhs the PointGFp to add to the local value
      * @result resulting PointGFp
      */
      PointGFp& operator+=(const PointGFp& rhs);

      /**
      * -= Operator
      * @param rhs the PointGFp to subtract from the local value
      * @result resulting PointGFp
      */
      PointGFp& operator-=(const PointGFp& rhs);

      /**
      * *= Operator
      * @param scalar the PointGFp to multiply with *this
      * @result resulting PointGFp
      */
      PointGFp& operator*=(const BigInt& scalar);

      /**
      * Negate this point
      * @return *this
      */
      PointGFp& negate()
         {
         if(!is_zero())
            m_coord_y = m_curve.get_p() - m_coord_y;
         return *this;
         }

      /**
      * get affine x coordinate
      * @result affine x coordinate
      */
      BigInt get_affine_x() const;

      /**
      * get affine y coordinate
      * @result affine y coordinate
      */
      BigInt get_affine_y() const;

      const BigInt& get_x() const { return m_coord_x; }
      const BigInt& get_y() const { return m_coord_y; }
      const BigInt& get_z() const { return m_coord_z; }

      void swap_coords(BigInt& new_x, BigInt& new_y, BigInt& new_z)
         {
         m_coord_x.swap(new_x);
         m_coord_y.swap(new_y);
         m_coord_z.swap(new_z);
         }

      /**
      * Force this point to affine coordinates
      */
      void force_affine();

      /**
      * Force all points on the list to affine coordinates
      */
      static void force_all_affine(std::vector<PointGFp>& points,
                                   secure_vector<word>& ws);

      bool is_affine() const;

      /**
      * Is this the point at infinity?
      * @result true, if this point is at infinity, false otherwise.
      */
      bool is_zero() const { return m_coord_z.is_zero(); }

      /**
      * Checks whether the point is to be found on the underlying
      * curve; used to prevent fault attacks.
      * @return if the point is on the curve
      */
      bool on_the_curve() const;

      /**
      * swaps the states of *this and other, does not throw!
      * @param other the object to swap values with
      */
      void swap(PointGFp& other);

      /**
      * Randomize the point representation
      * The actual value (get_affine_x, get_affine_y) does not change
      */
      void randomize_repr(RandomNumberGenerator& rng);

      /**
      * Randomize the point representation
      * The actual value (get_affine_x, get_affine_y) does not change
      */
      void randomize_repr(RandomNumberGenerator& rng, secure_vector<word>& ws);

      /**
      * Equality operator
      */
      bool operator==(const PointGFp& other) const;

      /**
      * Point addition
      * @param other the point to add to *this
      * @param workspace temp space, at least WORKSPACE_SIZE elements
      */
      void add(const PointGFp& other, std::vector<BigInt>& workspace)
         {
         BOTAN_ASSERT_NOMSG(m_curve == other.m_curve);

         const size_t p_words = m_curve.get_p_words();

         add(other.m_coord_x.data(), std::min(p_words, other.m_coord_x.size()),
             other.m_coord_y.data(), std::min(p_words, other.m_coord_y.size()),
             other.m_coord_z.data(), std::min(p_words, other.m_coord_z.size()),
             workspace);
         }

      /**
      * Point addition. Array version.
      *
      * @param x_words the words of the x coordinate of the other point
      * @param x_size size of x_words
      * @param y_words the words of the y coordinate of the other point
      * @param y_size size of y_words
      * @param z_words the words of the z coordinate of the other point
      * @param z_size size of z_words
      * @param workspace temp space, at least WORKSPACE_SIZE elements
      */
      void add(const word x_words[], size_t x_size,
               const word y_words[], size_t y_size,
               const word z_words[], size_t z_size,
               std::vector<BigInt>& workspace);

      /**
      * Point addition - mixed J+A
      * @param other affine point to add - assumed to be affine!
      * @param workspace temp space, at least WORKSPACE_SIZE elements
      */
      void add_affine(const PointGFp& other, std::vector<BigInt>& workspace)
         {
         BOTAN_ASSERT_NOMSG(m_curve == other.m_curve);
         BOTAN_DEBUG_ASSERT(other.is_affine());

         const size_t p_words = m_curve.get_p_words();
         add_affine(other.m_coord_x.data(), std::min(p_words, other.m_coord_x.size()),
                    other.m_coord_y.data(), std::min(p_words, other.m_coord_y.size()),
                    workspace);
         }

      /**
      * Point addition - mixed J+A. Array version.
      *
      * @param x_words the words of the x coordinate of the other point
      * @param x_size size of x_words
      * @param y_words the words of the y coordinate of the other point
      * @param y_size size of y_words
      * @param workspace temp space, at least WORKSPACE_SIZE elements
      */
      void add_affine(const word x_words[], size_t x_size,
                      const word y_words[], size_t y_size,
                      std::vector<BigInt>& workspace);

      /**
      * Point doubling
      * @param workspace temp space, at least WORKSPACE_SIZE elements
      */
      void mult2(std::vector<BigInt>& workspace);

      /**
      * Repeated point doubling
      * @param i number of doublings to perform
      * @param workspace temp space, at least WORKSPACE_SIZE elements
      */
      void mult2i(size_t i, std::vector<BigInt>& workspace);

      /**
      * Point addition
      * @param other the point to add to *this
      * @param workspace temp space, at least WORKSPACE_SIZE elements
      * @return other plus *this
      */
      PointGFp plus(const PointGFp& other, std::vector<BigInt>& workspace) const
         {
         PointGFp x = (*this);
         x.add(other, workspace);
         return x;
         }

      /**
      * Point doubling
      * @param workspace temp space, at least WORKSPACE_SIZE elements
      * @return *this doubled
      */
      PointGFp double_of(std::vector<BigInt>& workspace) const
         {
         PointGFp x = (*this);
         x.mult2(workspace);
         return x;
         }

      /**
      * Return the zero (aka infinite) point associated with this curve
      */
      PointGFp zero() const { return PointGFp(m_curve); }

      /**
      * Return base curve of this point
      * @result the curve over GF(p) of this point
      *
      * You should not need to use this
      */
      const CurveGFp& get_curve() const { return m_curve; }

   private:
      CurveGFp m_curve;
      BigInt m_coord_x, m_coord_y, m_coord_z;
   };

/**
* Point multiplication operator
* @param scalar the scalar value
* @param point the point value
* @return scalar*point on the curve
*/
BOTAN_PUBLIC_API(2,0) PointGFp operator*(const BigInt& scalar, const PointGFp& point);

/**
* ECC point multiexponentiation - not constant time!
* @param p1 a point
* @param z1 a scalar
* @param p2 a point
* @param z2 a scalar
* @result (p1 * z1 + p2 * z2)
*/
BOTAN_PUBLIC_API(2,0) PointGFp multi_exponentiate(
   const PointGFp& p1, const BigInt& z1,
   const PointGFp& p2, const BigInt& z2);

// relational operators
inline bool operator!=(const PointGFp& lhs, const PointGFp& rhs)
   {
   return !(rhs == lhs);
   }

// arithmetic operators
inline PointGFp operator-(const PointGFp& lhs)
   {
   return PointGFp(lhs).negate();
   }

inline PointGFp operator+(const PointGFp& lhs, const PointGFp& rhs)
   {
   PointGFp tmp(lhs);
   return tmp += rhs;
   }

inline PointGFp operator-(const PointGFp& lhs, const PointGFp& rhs)
   {
   PointGFp tmp(lhs);
   return tmp -= rhs;
   }

inline PointGFp operator*(const PointGFp& point, const BigInt& scalar)
   {
   return scalar * point;
   }

// encoding and decoding
inline secure_vector<uint8_t> BOTAN_DEPRECATED("Use PointGFp::encode")
   EC2OSP(const PointGFp& point, uint8_t format)
   {
   std::vector<uint8_t> enc = point.encode(static_cast<PointGFp::Compression_Type>(format));
   return secure_vector<uint8_t>(enc.begin(), enc.end());
   }

/**
* Perform point decoding
* Use EC_Group::OS2ECP instead
*/
PointGFp BOTAN_PUBLIC_API(2,0) OS2ECP(const uint8_t data[], size_t data_len,
                                      const CurveGFp& curve);

/**
* Perform point decoding
* Use EC_Group::OS2ECP instead
*
* @param data the encoded point
* @param data_len length of data in bytes
* @param curve_p the curve equation prime
* @param curve_a the curve equation a parameter
* @param curve_b the curve equation b parameter
*/
std::pair<BigInt, BigInt> BOTAN_UNSTABLE_API OS2ECP(const uint8_t data[], size_t data_len,
                                                    const BigInt& curve_p,
                                                    const BigInt& curve_a,
                                                    const BigInt& curve_b);

template<typename Alloc>
PointGFp OS2ECP(const std::vector<uint8_t, Alloc>& data, const CurveGFp& curve)
   { return OS2ECP(data.data(), data.size(), curve); }

class PointGFp_Var_Point_Precompute;

/**
* Deprecated API for point multiplication
* Use EC_Group::blinded_base_point_multiply or EC_Group::blinded_var_point_multiply
*/
class BOTAN_PUBLIC_API(2,0) Blinded_Point_Multiply final
   {
   public:
      Blinded_Point_Multiply(const PointGFp& base, const BigInt& order, size_t h = 0);

      ~Blinded_Point_Multiply();

      PointGFp BOTAN_DEPRECATED("Use alternative APIs") blinded_multiply(const BigInt& scalar, RandomNumberGenerator& rng);
   private:
      std::vector<BigInt> m_ws;
      const BigInt& m_order;
      std::unique_ptr<PointGFp_Var_Point_Precompute> m_point_mul;
   };

}

namespace std {

template<>
inline void swap<Botan::PointGFp>(Botan::PointGFp& x, Botan::PointGFp& y)
   { x.swap(y); }

}

namespace Botan {

/**
* This class represents elliptic curce domain parameters
*/
enum EC_Group_Encoding {
   EC_DOMPAR_ENC_EXPLICIT = 0,
   EC_DOMPAR_ENC_IMPLICITCA = 1,
   EC_DOMPAR_ENC_OID = 2
};

enum class EC_Group_Source {
   Builtin,
   ExternalSource,
};

class CurveGFp;

class EC_Group_Data;
class EC_Group_Data_Map;

/**
* Class representing an elliptic curve
*
* The internal representation is stored in a shared_ptr, so copying an
* EC_Group is inexpensive.
*/
class BOTAN_PUBLIC_API(2,0) EC_Group final
   {
   public:

      /**
      * Construct Domain paramers from specified parameters
      * @param curve elliptic curve
      * @param base_point a base point
      * @param order the order of the base point
      * @param cofactor the cofactor
      */
      BOTAN_DEPRECATED("Use version taking all BigInts")
      EC_Group(const CurveGFp& curve,
               const PointGFp& base_point,
               const BigInt& order,
               const BigInt& cofactor) :
         EC_Group(curve.get_p(),
                  curve.get_a(),
                  curve.get_b(),
                  base_point.get_affine_x(),
                  base_point.get_affine_y(),
                  order,
                  cofactor) {}

      /**
      * Construct Domain paramers from specified parameters
      * @param p the elliptic curve p
      * @param a the elliptic curve a param
      * @param b the elliptic curve b param
      * @param base_x the x coordinate of the base point
      * @param base_y the y coordinate of the base point
      * @param order the order of the base point
      * @param cofactor the cofactor
      * @param oid an optional OID used to identify this curve
      */
      EC_Group(const BigInt& p,
               const BigInt& a,
               const BigInt& b,
               const BigInt& base_x,
               const BigInt& base_y,
               const BigInt& order,
               const BigInt& cofactor,
               const OID& oid = OID());

      /**
      * Decode a BER encoded ECC domain parameter set
      * @param ber the bytes of the BER encoding
      * @param ber_len the length of ber
      */
      explicit EC_Group(const uint8_t ber[], size_t ber_len);

      template<typename Alloc>
         EC_Group(const std::vector<uint8_t, Alloc>& ber) :
         EC_Group(ber.data(), ber.size()) {}

      /**
      * Create an EC domain by OID (or throw if unknown)
      * @param oid the OID of the EC domain to create
      */
      explicit EC_Group(const OID& oid);

      /**
      * Create an EC domain from PEM encoding (as from PEM_encode), or
      * from an OID name (eg "secp256r1", or "1.2.840.10045.3.1.7")
      * @param pem_or_oid PEM-encoded data, or an OID

      * @warning Support for PEM in this function is deprecated. Use
      * EC_Group_from_PEM
      */
      explicit EC_Group(const std::string& pem_or_oid);

      static EC_Group EC_Group_from_PEM(const std::string& pem);

      /**
      * Create an uninitialized EC_Group
      */
      EC_Group();

      ~EC_Group();

      EC_Group(const EC_Group&) = default;
      EC_Group(EC_Group&&) = default;

      EC_Group& operator=(const EC_Group&) = default;
      EC_Group& operator=(EC_Group&&) = default;

      /**
      * Create the DER encoding of this domain
      * @param form of encoding to use
      * @returns bytes encododed as DER
      */
      std::vector<uint8_t> DER_encode(EC_Group_Encoding form) const;

      /**
      * Return the PEM encoding (always in explicit form)
      * @return string containing PEM data
      */
      std::string PEM_encode() const;

      /**
      * Return domain parameter curve
      * @result domain parameter curve
      */
      BOTAN_DEPRECATED("Avoid CurveGFp") const CurveGFp& get_curve() const;

      /**
      * Return if a == -3 mod p
      */
      bool a_is_minus_3() const;

      /**
      * Return if a == 0 mod p
      */
      bool a_is_zero() const;

      /**
      * Return the size of p in bits (same as get_p().bits())
      */
      size_t get_p_bits() const;

      /**
      * Return the size of p in bits (same as get_p().bytes())
      */
      size_t get_p_bytes() const;

      /**
      * Return the size of group order in bits (same as get_order().bits())
      */
      size_t get_order_bits() const;

      /**
      * Return the size of p in bytes (same as get_order().bytes())
      */
      size_t get_order_bytes() const;

      /**
      * Return the prime modulus of the field
      */
      const BigInt& get_p() const;

      /**
      * Return the a parameter of the elliptic curve equation
      */
      const BigInt& get_a() const;

      /**
      * Return the b parameter of the elliptic curve equation
      */
      const BigInt& get_b() const;

      /**
      * Return group base point
      * @result base point
      */
      const PointGFp& get_base_point() const;

      /**
      * Return the x coordinate of the base point
      */
      const BigInt& get_g_x() const;

      /**
      * Return the y coordinate of the base point
      */
      const BigInt& get_g_y() const;

      /**
      * Return the order of the base point
      * @result order of the base point
      */
      const BigInt& get_order() const;

      /*
      * Reduce x modulo the order
      */
      BigInt mod_order(const BigInt& x) const;

      /*
      * Return inverse of x modulo the order
      */
      BigInt inverse_mod_order(const BigInt& x) const;

      /*
      * Reduce (x*x) modulo the order
      */
      BigInt square_mod_order(const BigInt& x) const;

      /*
      * Reduce (x*y) modulo the order
      */
      BigInt multiply_mod_order(const BigInt& x, const BigInt& y) const;

      /*
      * Reduce (x*y*z) modulo the order
      */
      BigInt multiply_mod_order(const BigInt& x, const BigInt& y, const BigInt& z) const;

      /**
      * Return the cofactor
      * @result the cofactor
      */
      const BigInt& get_cofactor() const;

      /**
      * Check if y is a plausible point on the curve
      *
      * In particular, checks that it is a point on the curve, not infinity,
      * and that it has order matching the group.
      */
      bool verify_public_element(const PointGFp& y) const;

      /**
      * Return the OID of these domain parameters
      * @result the OID as a string
      */
      std::string BOTAN_DEPRECATED("Use get_curve_oid") get_oid() const { return get_curve_oid().to_string(); }

      /**
      * Return the OID of these domain parameters
      * @result the OID
      */
      const OID& get_curve_oid() const;

      /**
      * Return a point on this curve with the affine values x, y
      */
      PointGFp point(const BigInt& x, const BigInt& y) const;

      /**
      * Multi exponentiate. Not constant time.
      * @return base_point*x + pt*y
      */
      PointGFp point_multiply(const BigInt& x, const PointGFp& pt, const BigInt& y) const;

      /**
      * Blinded point multiplication, attempts resistance to side channels
      * @param k the scalar
      * @param rng a random number generator
      * @param ws a temp workspace
      * @return base_point*k
      */
      PointGFp blinded_base_point_multiply(const BigInt& k,
                                           RandomNumberGenerator& rng,
                                           std::vector<BigInt>& ws) const;

      /**
      * Blinded point multiplication, attempts resistance to side channels
      * Returns just the x coordinate of the point
      *
      * @param k the scalar
      * @param rng a random number generator
      * @param ws a temp workspace
      * @return x coordinate of base_point*k
      */
      BigInt blinded_base_point_multiply_x(const BigInt& k,
                                           RandomNumberGenerator& rng,
                                           std::vector<BigInt>& ws) const;

      /**
      * Blinded point multiplication, attempts resistance to side channels
      * @param point input point
      * @param k the scalar
      * @param rng a random number generator
      * @param ws a temp workspace
      * @return point*k
      */
      PointGFp blinded_var_point_multiply(const PointGFp& point,
                                          const BigInt& k,
                                          RandomNumberGenerator& rng,
                                          std::vector<BigInt>& ws) const;

      /**
      * Return a random scalar ie an integer in [1,order)
      */
      BigInt random_scalar(RandomNumberGenerator& rng) const;

      /**
      * Return the zero (or infinite) point on this curve
      */
      PointGFp zero_point() const;

      size_t point_size(PointGFp::Compression_Type format) const;

      PointGFp OS2ECP(const uint8_t bits[], size_t len) const;

      template<typename Alloc>
      PointGFp OS2ECP(const std::vector<uint8_t, Alloc>& vec) const
         {
         return this->OS2ECP(vec.data(), vec.size());
         }

      bool initialized() const { return (m_data != nullptr); }

      /**
       * Verify EC_Group domain
       * @returns true if group is valid. false otherwise
       */
      bool verify_group(RandomNumberGenerator& rng,
                        bool strong = false) const;

      bool operator==(const EC_Group& other) const;

      EC_Group_Source source() const;

      /**
      * Return PEM representation of named EC group
      * Deprecated: Use EC_Group(name).PEM_encode() if this is needed
      */
      static std::string BOTAN_DEPRECATED("See header comment") PEM_for_named_group(const std::string& name);

      /**
      * Return a set of known named EC groups
      */
      static const std::set<std::string>& known_named_groups();

      /*
      * For internal use only
      */
      static std::shared_ptr<EC_Group_Data> EC_group_info(const OID& oid);

      static size_t clear_registered_curve_data();

   private:
      static EC_Group_Data_Map& ec_group_data();

      static std::shared_ptr<EC_Group_Data> BER_decode_EC_group(const uint8_t bits[], size_t len,
                                                                EC_Group_Source source);

      static std::shared_ptr<EC_Group_Data>
         load_EC_group_info(const char* p,
                            const char* a,
                            const char* b,
                            const char* g_x,
                            const char* g_y,
                            const char* order,
                            const OID& oid);

      // Member data
      const EC_Group_Data& data() const;
      std::shared_ptr<EC_Group_Data> m_data;
   };

inline bool operator!=(const EC_Group& lhs,
                       const EC_Group& rhs)
   {
   return !(lhs == rhs);
   }

// For compatibility with 1.8
typedef EC_Group EC_Domain_Params;

}

namespace Botan {

/**
* This class represents abstract ECC public keys. When encoding a key
* via an encoder that can be accessed via the corresponding member
* functions, the key will decide upon its internally stored encoding
* information whether to encode itself with or without domain
* parameters, or using the domain parameter oid. Furthermore, a public
* key without domain parameters can be decoded. In that case, it
* cannot be used for verification until its domain parameters are set
* by calling the corresponding member function.
*/
class BOTAN_PUBLIC_API(2,0) EC_PublicKey : public virtual Public_Key
   {
   public:
      /**
      * Create a public key.
      * @param dom_par EC domain parameters
      * @param pub_point public point on the curve
      */
      EC_PublicKey(const EC_Group& dom_par,
                   const PointGFp& pub_point);

      /**
      * Load a public key.
      * @param alg_id the X.509 algorithm identifier
      * @param key_bits DER encoded public key bits
      */
      EC_PublicKey(const AlgorithmIdentifier& alg_id,
                   const std::vector<uint8_t>& key_bits);

      EC_PublicKey(const EC_PublicKey& other) = default;
      EC_PublicKey& operator=(const EC_PublicKey& other) = default;
      virtual ~EC_PublicKey() = default;

      /**
      * Get the public point of this key.
      * @throw Invalid_State is thrown if the
      * domain parameters of this point are not set
      * @result the public point of this key
      */
      const PointGFp& public_point() const { return m_public_key; }

      AlgorithmIdentifier algorithm_identifier() const override;

      std::vector<uint8_t> public_key_bits() const override;

      bool check_key(RandomNumberGenerator& rng,
                     bool strong) const override;

      /**
      * Get the domain parameters of this key.
      * @throw Invalid_State is thrown if the
      * domain parameters of this point are not set
      * @result the domain parameters of this key
      */
      const EC_Group& domain() const { return m_domain_params; }

      /**
      * Set the domain parameter encoding to be used when encoding this key.
      * @param enc the encoding to use
      */
      void set_parameter_encoding(EC_Group_Encoding enc);

      /**
      * Set the point encoding method to be used when encoding this key.
      * @param enc the encoding to use
      */
      void set_point_encoding(PointGFp::Compression_Type enc);

      /**
      * Return the DER encoding of this keys domain in whatever format
      * is preset for this particular key
      */
      std::vector<uint8_t> DER_domain() const
         { return domain().DER_encode(domain_format()); }

      /**
      * Get the domain parameter encoding to be used when encoding this key.
      * @result the encoding to use
      */
      EC_Group_Encoding domain_format() const
         { return m_domain_encoding; }

      /**
      * Get the point encoding method to be used when encoding this key.
      * @result the encoding to use
      */
      PointGFp::Compression_Type point_encoding() const
         { return m_point_encoding; }

      size_t key_length() const override;
      size_t estimated_strength() const override;

   protected:
      EC_PublicKey() : m_domain_params{}, m_public_key{}, m_domain_encoding(EC_DOMPAR_ENC_EXPLICIT)
      {}

      EC_Group m_domain_params;
      PointGFp m_public_key;
      EC_Group_Encoding m_domain_encoding;
      PointGFp::Compression_Type m_point_encoding = PointGFp::UNCOMPRESSED;
   };

/**
* This abstract class represents ECC private keys
*/
class BOTAN_PUBLIC_API(2,0) EC_PrivateKey : public virtual EC_PublicKey,
                                public virtual Private_Key
   {
   public:
      /*
      * If x=0, creates a new private key in the domain
      * using the given rng. If with_modular_inverse is set,
      * the public key will be calculated by multiplying
      * the base point with the modular inverse of
      * x (as in ECGDSA and ECKCDSA), otherwise by
      * multiplying directly with x (as in ECDSA).
      */
      EC_PrivateKey(RandomNumberGenerator& rng,
                    const EC_Group& domain,
                    const BigInt& x,
                    bool with_modular_inverse=false);

      /*
      * Creates a new private key object from the
      * ECPrivateKey structure given in key_bits.
      * If with_modular_inverse is set,
      * the public key will be calculated by multiplying
      * the base point with the modular inverse of
      * x (as in ECGDSA and ECKCDSA), otherwise by
      * multiplying directly with x (as in ECDSA).
      */
      EC_PrivateKey(const AlgorithmIdentifier& alg_id,
                    const secure_vector<uint8_t>& key_bits,
                    bool with_modular_inverse=false);

      secure_vector<uint8_t> private_key_bits() const override;

      /**
      * Get the private key value of this key object.
      * @result the private key value of this key object
      */
      const BigInt& private_value() const;

      EC_PrivateKey(const EC_PrivateKey& other) = default;
      EC_PrivateKey& operator=(const EC_PrivateKey& other) = default;
      ~EC_PrivateKey() = default;
   protected:
      EC_PrivateKey() = default;

      BigInt m_private_key;
   };

}

namespace Botan {

/**
* This class represents ECDH Public Keys.
*/
class BOTAN_PUBLIC_API(2,0) ECDH_PublicKey : public virtual EC_PublicKey
   {
   public:
      /**
      * Create an ECDH public key.
      * @param alg_id algorithm identifier
      * @param key_bits DER encoded public key bits
      */
      ECDH_PublicKey(const AlgorithmIdentifier& alg_id,
                     const std::vector<uint8_t>& key_bits) :
         EC_PublicKey(alg_id, key_bits) {}

      /**
      * Construct a public key from a given public point.
      * @param dom_par the domain parameters associated with this key
      * @param public_point the public point defining this key
      */
      ECDH_PublicKey(const EC_Group& dom_par,
                     const PointGFp& public_point) :
         EC_PublicKey(dom_par, public_point) {}

      /**
      * Get this keys algorithm name.
      * @return this keys algorithm name
      */
      std::string algo_name() const override { return "ECDH"; }

      /**
      * @return public point value
      */
      std::vector<uint8_t> public_value() const
         { return public_point().encode(PointGFp::UNCOMPRESSED); }

      /**
      * @return public point value
      */
      std::vector<uint8_t> public_value(PointGFp::Compression_Type format) const
         { return public_point().encode(format); }

   protected:
      ECDH_PublicKey() = default;
   };

/**
* This class represents ECDH Private Keys.
*/
class BOTAN_PUBLIC_API(2,0) ECDH_PrivateKey final : public ECDH_PublicKey,
                                  public EC_PrivateKey,
                                  public PK_Key_Agreement_Key
   {
   public:

      /**
      * Load a private key.
      * @param alg_id the X.509 algorithm identifier
      * @param key_bits ECPrivateKey bits
      */
      ECDH_PrivateKey(const AlgorithmIdentifier& alg_id,
                      const secure_vector<uint8_t>& key_bits) :
         EC_PrivateKey(alg_id, key_bits) {}

      /**
      * Generate a new private key
      * @param rng a random number generator
      * @param domain parameters to used for this key
      * @param x the private key; if zero, a new random key is generated
      */
      ECDH_PrivateKey(RandomNumberGenerator& rng,
                      const EC_Group& domain,
                      const BigInt& x = 0) :
         EC_PrivateKey(rng, domain, x) {}

      std::vector<uint8_t> public_value() const override
         { return ECDH_PublicKey::public_value(PointGFp::UNCOMPRESSED); }

      std::vector<uint8_t> public_value(PointGFp::Compression_Type type) const
         { return ECDH_PublicKey::public_value(type); }

      std::unique_ptr<PK_Ops::Key_Agreement>
         create_key_agreement_op(RandomNumberGenerator& rng,
                                 const std::string& params,
                                 const std::string& provider) const override;
   };

}

namespace Botan {

/**
* This class represents ECDSA Public Keys.
*/
class BOTAN_PUBLIC_API(2,0) ECDSA_PublicKey : public virtual EC_PublicKey
   {
   public:

      /**
      * Create a public key from a given public point.
      * @param dom_par the domain parameters associated with this key
      * @param public_point the public point defining this key
      */
      ECDSA_PublicKey(const EC_Group& dom_par,
                      const PointGFp& public_point) :
         EC_PublicKey(dom_par, public_point) {}

      /**
      * Load a public key.
      * @param alg_id the X.509 algorithm identifier
      * @param key_bits DER encoded public key bits
      */
      ECDSA_PublicKey(const AlgorithmIdentifier& alg_id,
                      const std::vector<uint8_t>& key_bits) :
         EC_PublicKey(alg_id, key_bits) {}

      /**
      * Recover a public key from a signature/msg pair
      * See SEC section 4.6.1
      * @param group the elliptic curve group
      * @param msg the message
      * @param r the r paramter of the signature
      * @param s the s paramter of the signature
      * @param v the recovery ID
      */
      ECDSA_PublicKey(const EC_Group& group,
                      const std::vector<uint8_t>& msg,
                      const BigInt& r,
                      const BigInt& s,
                      uint8_t v);

      /**
      * Get this keys algorithm name.
      * @result this keys algorithm name ("ECDSA")
      */
      std::string algo_name() const override { return "ECDSA"; }

      size_t message_parts() const override { return 2; }

      size_t message_part_size() const override
         { return domain().get_order().bytes(); }

      uint8_t recovery_param(const std::vector<uint8_t>& msg,
                             const BigInt& r,
                             const BigInt& s) const;

      std::unique_ptr<PK_Ops::Verification>
         create_verification_op(const std::string& params,
                                const std::string& provider) const override;
   protected:
      ECDSA_PublicKey() = default;
   };

/**
* This class represents ECDSA Private Keys
*/
class BOTAN_PUBLIC_API(2,0) ECDSA_PrivateKey final : public ECDSA_PublicKey,
                                   public EC_PrivateKey
   {
   public:

      /**
      * Load a private key
      * @param alg_id the X.509 algorithm identifier
      * @param key_bits ECPrivateKey bits
      */
      ECDSA_PrivateKey(const AlgorithmIdentifier& alg_id,
                       const secure_vector<uint8_t>& key_bits) :
         EC_PrivateKey(alg_id, key_bits) {}

      /**
      * Create a private key.
      * @param rng a random number generator
      * @param domain parameters to used for this key
      * @param x the private key (if zero, generate a new random key)
      */
      ECDSA_PrivateKey(RandomNumberGenerator& rng,
                       const EC_Group& domain,
                       const BigInt& x = 0) :
         EC_PrivateKey(rng, domain, x) {}

      bool check_key(RandomNumberGenerator& rng, bool) const override;

      std::unique_ptr<PK_Ops::Signature>
         create_signature_op(RandomNumberGenerator& rng,
                             const std::string& params,
                             const std::string& provider) const override;
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(eme.h)

namespace Botan {

class RandomNumberGenerator;

/**
* Encoding Method for Encryption
*/
class BOTAN_PUBLIC_API(2,0) EME
   {
   public:
      virtual ~EME() = default;

      /**
      * Return the maximum input size in bytes we can support
      * @param keybits the size of the key in bits
      * @return upper bound of input in bytes
      */
      virtual size_t maximum_input_size(size_t keybits) const = 0;

      /**
      * Encode an input
      * @param in the plaintext
      * @param in_length length of plaintext in bytes
      * @param key_length length of the key in bits
      * @param rng a random number generator
      * @return encoded plaintext
      */
      secure_vector<uint8_t> encode(const uint8_t in[],
                                 size_t in_length,
                                 size_t key_length,
                                 RandomNumberGenerator& rng) const;

      /**
      * Encode an input
      * @param in the plaintext
      * @param key_length length of the key in bits
      * @param rng a random number generator
      * @return encoded plaintext
      */
      secure_vector<uint8_t> encode(const secure_vector<uint8_t>& in,
                                 size_t key_length,
                                 RandomNumberGenerator& rng) const;

      /**
      * Decode an input
      * @param valid_mask written to specifies if output is valid
      * @param in the encoded plaintext
      * @param in_len length of encoded plaintext in bytes
      * @return bytes of out[] written to along with
      *         validity mask (0xFF if valid, else 0x00)
      */
      virtual secure_vector<uint8_t> unpad(uint8_t& valid_mask,
                                        const uint8_t in[],
                                        size_t in_len) const = 0;

      /**
      * Encode an input
      * @param in the plaintext
      * @param in_length length of plaintext in bytes
      * @param key_length length of the key in bits
      * @param rng a random number generator
      * @return encoded plaintext
      */
      virtual secure_vector<uint8_t> pad(const uint8_t in[],
                                      size_t in_length,
                                      size_t key_length,
                                      RandomNumberGenerator& rng) const = 0;
   };

/**
* Factory method for EME (message-encoding methods for encryption) objects
* @param algo_spec the name of the EME to create
* @return pointer to newly allocated object of that type
*/
BOTAN_PUBLIC_API(2,0) EME*  get_eme(const std::string& algo_spec);

}

BOTAN_FUTURE_INTERNAL_HEADER(eme_pkcs.h)

namespace Botan {

/**
* EME from PKCS #1 v1.5
*/
class BOTAN_PUBLIC_API(2,0) EME_PKCS1v15 final : public EME
   {
   public:
      size_t maximum_input_size(size_t) const override;

      secure_vector<uint8_t> pad(const uint8_t[], size_t, size_t,
                             RandomNumberGenerator&) const override;

      secure_vector<uint8_t> unpad(uint8_t& valid_mask,
                                const uint8_t in[],
                                size_t in_len) const override;
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(emsa.h)

namespace Botan {

class Private_Key;
class RandomNumberGenerator;

/**
* EMSA, from IEEE 1363s Encoding Method for Signatures, Appendix
*
* Any way of encoding/padding signatures
*/
class BOTAN_PUBLIC_API(2,0) EMSA
   {
   public:
      virtual ~EMSA() = default;

      /**
      * Add more data to the signature computation
      * @param input some data
      * @param length length of input in bytes
      */
      virtual void update(const uint8_t input[], size_t length) = 0;

      /**
      * @return raw hash
      */
      virtual secure_vector<uint8_t> raw_data() = 0;

      /**
      * Return the encoding of a message
      * @param msg the result of raw_data()
      * @param output_bits the desired output bit size
      * @param rng a random number generator
      * @return encoded signature
      */
      virtual secure_vector<uint8_t> encoding_of(const secure_vector<uint8_t>& msg,
                                             size_t output_bits,
                                             RandomNumberGenerator& rng) = 0;

      /**
      * Verify the encoding
      * @param coded the received (coded) message representative
      * @param raw the computed (local, uncoded) message representative
      * @param key_bits the size of the key in bits
      * @return true if coded is a valid encoding of raw, otherwise false
      */
      virtual bool verify(const secure_vector<uint8_t>& coded,
                          const secure_vector<uint8_t>& raw,
                          size_t key_bits) = 0;

      /**
      * Prepare sig_algo for use in choose_sig_format for x509 certs
      *
      * @param key used for checking compatibility with the encoding scheme
      * @param cert_hash_name is checked to equal the hash for the encoding
      * @return algorithm identifier to signatures created using this key,
      *         padding method and hash.
      */
      virtual AlgorithmIdentifier config_for_x509(const Private_Key& key,
                                                  const std::string& cert_hash_name) const;

      /**
      * @return a new object representing the same encoding method as *this
      */
      virtual EMSA* clone() = 0;

      /**
      * @return the SCAN name of the encoding/padding scheme
      */
      virtual std::string name() const = 0;
   };

/**
* Factory method for EMSA (message-encoding methods for signatures
* with appendix) objects
* @param algo_spec the name of the EMSA to create
* @return pointer to newly allocated object of that type
*/
BOTAN_PUBLIC_API(2,0) EMSA* get_emsa(const std::string& algo_spec);

/**
* Returns the hash function used in the given EMSA scheme
* If the hash function is not specified or not understood,
* returns "SHA-512"
* @param algo_spec the name of the EMSA
* @return hash function used in the given EMSA scheme
*/
BOTAN_PUBLIC_API(2,0) std::string hash_for_emsa(const std::string& algo_spec);

}

BOTAN_FUTURE_INTERNAL_HEADER(emsa1.h)

namespace Botan {

/**
* EMSA1 from IEEE 1363
* Essentially, sign the hash directly
*/
class BOTAN_PUBLIC_API(2,0) EMSA1 final : public EMSA
   {
   public:
      /**
      * @param hash the hash function to use
      */
      explicit EMSA1(HashFunction* hash) : m_hash(hash) {}

      EMSA* clone() override;

      std::string name() const override;

      AlgorithmIdentifier config_for_x509(const Private_Key& key,
                                          const std::string& cert_hash_name) const override;
   private:
      size_t hash_output_length() const { return m_hash->output_length(); }

      void update(const uint8_t[], size_t) override;
      secure_vector<uint8_t> raw_data() override;

      secure_vector<uint8_t> encoding_of(const secure_vector<uint8_t>& msg,
                                         size_t output_bits,
                                         RandomNumberGenerator& rng) override;

      bool verify(const secure_vector<uint8_t>& coded,
                  const secure_vector<uint8_t>& raw,
                  size_t key_bits) override;

      std::unique_ptr<HashFunction> m_hash;
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(emsa_pkcs1.h)

namespace Botan {

/**
* PKCS #1 v1.5 signature padding
* aka PKCS #1 block type 1
* aka EMSA3 from IEEE 1363
*/
class BOTAN_PUBLIC_API(2,0) EMSA_PKCS1v15 final : public EMSA
   {
   public:
      /**
      * @param hash the hash function to use
      */
      explicit EMSA_PKCS1v15(HashFunction* hash);

      EMSA* clone() override { return new EMSA_PKCS1v15(m_hash->clone()); }

      void update(const uint8_t[], size_t) override;

      secure_vector<uint8_t> raw_data() override;

      secure_vector<uint8_t> encoding_of(const secure_vector<uint8_t>&, size_t,
                                     RandomNumberGenerator& rng) override;

      bool verify(const secure_vector<uint8_t>&, const secure_vector<uint8_t>&,
                  size_t) override;

      std::string name() const override
         { return "EMSA3(" + m_hash->name() + ")"; }

      AlgorithmIdentifier config_for_x509(const Private_Key& key,
                                          const std::string& cert_hash_name) const override;
   private:
      std::unique_ptr<HashFunction> m_hash;
      std::vector<uint8_t> m_hash_id;
   };

/**
* EMSA_PKCS1v15_Raw which is EMSA_PKCS1v15 without a hash or digest id
* (which according to QCA docs is "identical to PKCS#11's CKM_RSA_PKCS
* mechanism", something I have not confirmed)
*/
class BOTAN_PUBLIC_API(2,0) EMSA_PKCS1v15_Raw final : public EMSA
   {
   public:
      EMSA* clone() override { return new EMSA_PKCS1v15_Raw(); }

      void update(const uint8_t[], size_t) override;

      secure_vector<uint8_t> raw_data() override;

      secure_vector<uint8_t> encoding_of(const secure_vector<uint8_t>&, size_t,
                                     RandomNumberGenerator& rng) override;

      bool verify(const secure_vector<uint8_t>&, const secure_vector<uint8_t>&,
                  size_t) override;

      /**
      * @param hash_algo if non-empty, the digest id for that hash is
      * included in the signature.
      */
      EMSA_PKCS1v15_Raw(const std::string& hash_algo = "");

      std::string name() const override
         {
         if(m_hash_name.empty()) return "EMSA3(Raw)";
         else return "EMSA3(Raw," + m_hash_name + ")";
         }

   private:
      size_t m_hash_output_len = 0;
      std::string m_hash_name;
      std::vector<uint8_t> m_hash_id;
      secure_vector<uint8_t> m_message;
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(emsa_raw.h)

namespace Botan {

/**
* EMSA-Raw - sign inputs directly
* Don't use this unless you know what you are doing.
*/
class BOTAN_PUBLIC_API(2,0) EMSA_Raw final : public EMSA
   {
   public:
      EMSA* clone() override { return new EMSA_Raw(); }

      explicit EMSA_Raw(size_t expected_hash_size = 0) :
         m_expected_size(expected_hash_size) {}

      std::string name() const override;
   private:
      void update(const uint8_t[], size_t) override;
      secure_vector<uint8_t> raw_data() override;

      secure_vector<uint8_t> encoding_of(const secure_vector<uint8_t>&, size_t,
                                         RandomNumberGenerator&) override;

      bool verify(const secure_vector<uint8_t>&,
                  const secure_vector<uint8_t>&,
                  size_t) override;

      const size_t m_expected_size;
      secure_vector<uint8_t> m_message;
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(emsa_x931.h)

namespace Botan {

/**
* EMSA from X9.31 (EMSA2 in IEEE 1363)
* Useful for Rabin-Williams, also sometimes used with RSA in
* odd protocols.
*/
class BOTAN_PUBLIC_API(2,0) EMSA_X931 final : public EMSA
   {
   public:
      /**
      * @param hash the hash function to use
      */
      explicit EMSA_X931(HashFunction* hash);

      EMSA* clone() override { return new EMSA_X931(m_hash->clone()); }

      std::string name() const override;

   private:
      void update(const uint8_t[], size_t) override;
      secure_vector<uint8_t> raw_data() override;

      secure_vector<uint8_t> encoding_of(const secure_vector<uint8_t>&, size_t,
                                     RandomNumberGenerator& rng) override;

      bool verify(const secure_vector<uint8_t>&, const secure_vector<uint8_t>&,
                  size_t) override;

      secure_vector<uint8_t> m_empty_hash;
      std::unique_ptr<HashFunction> m_hash;
      uint8_t m_hash_id;
   };

}

namespace Botan {

class RandomNumberGenerator;

/**
* Abstract interface to a source of entropy
*/
class BOTAN_PUBLIC_API(2,0) Entropy_Source
   {
   public:
      /**
      * Return a new entropy source of a particular type, or null
      * Each entropy source may require substantial resources (eg, a file handle
      * or socket instance), so try to share them among multiple RNGs, or just
      * use the preconfigured global list accessed by Entropy_Sources::global_sources()
      */
      static std::unique_ptr<Entropy_Source> create(const std::string& type);

      /**
      * @return name identifying this entropy source
      */
      virtual std::string name() const = 0;

      /**
      * Perform an entropy gathering poll
      * @param rng will be provided with entropy via calls to add_entropy
      * @return conservative estimate of actual entropy added to rng during poll
      */
      virtual size_t poll(RandomNumberGenerator& rng) = 0;

      Entropy_Source() = default;
      Entropy_Source(const Entropy_Source& other) = delete;
      Entropy_Source(Entropy_Source&& other) = delete;
      Entropy_Source& operator=(const Entropy_Source& other) = delete;

      virtual ~Entropy_Source() = default;
   };

class BOTAN_PUBLIC_API(2,0) Entropy_Sources final
   {
   public:
      static Entropy_Sources& global_sources();

      void add_source(std::unique_ptr<Entropy_Source> src);

      std::vector<std::string> enabled_sources() const;

      size_t poll(RandomNumberGenerator& rng,
                  size_t bits,
                  std::chrono::milliseconds timeout);

      /**
      * Poll just a single named source. Ordinally only used for testing
      */
      size_t poll_just(RandomNumberGenerator& rng, const std::string& src);

      Entropy_Sources() = default;
      explicit Entropy_Sources(const std::vector<std::string>& sources);

      Entropy_Sources(const Entropy_Sources& other) = delete;
      Entropy_Sources(Entropy_Sources&& other) = delete;
      Entropy_Sources& operator=(const Entropy_Sources& other) = delete;

   private:
      std::vector<std::unique_ptr<Entropy_Source>> m_srcs;
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(gcm.h)

namespace Botan {

class BlockCipher;
class StreamCipher;
class GHASH;

/**
* GCM Mode
*/
class BOTAN_PUBLIC_API(2,0) GCM_Mode : public AEAD_Mode
   {
   public:
      void set_associated_data(const uint8_t ad[], size_t ad_len) override;

      std::string name() const override;

      size_t update_granularity() const override;

      Key_Length_Specification key_spec() const override;

      bool valid_nonce_length(size_t len) const override;

      size_t tag_size() const override { return m_tag_size; }

      void clear() override;

      void reset() override;

      std::string provider() const override;
   protected:
      GCM_Mode(BlockCipher* cipher, size_t tag_size);

      ~GCM_Mode();

      static const size_t GCM_BS = 16;

      const size_t m_tag_size;
      const std::string m_cipher_name;

      std::unique_ptr<StreamCipher> m_ctr;
      std::unique_ptr<GHASH> m_ghash;
   private:
      void start_msg(const uint8_t nonce[], size_t nonce_len) override;

      void key_schedule(const uint8_t key[], size_t length) override;

      secure_vector<uint8_t> m_y0;
   };

/**
* GCM Encryption
*/
class BOTAN_PUBLIC_API(2,0) GCM_Encryption final : public GCM_Mode
   {
   public:
      /**
      * @param cipher the 128 bit block cipher to use
      * @param tag_size is how big the auth tag will be
      */
      GCM_Encryption(BlockCipher* cipher, size_t tag_size = 16) :
         GCM_Mode(cipher, tag_size) {}

      size_t output_length(size_t input_length) const override
         { return input_length + tag_size(); }

      size_t minimum_final_size() const override { return 0; }

      size_t process(uint8_t buf[], size_t size) override;

      void finish(secure_vector<uint8_t>& final_block, size_t offset = 0) override;
   };

/**
* GCM Decryption
*/
class BOTAN_PUBLIC_API(2,0) GCM_Decryption final : public GCM_Mode
   {
   public:
      /**
      * @param cipher the 128 bit block cipher to use
      * @param tag_size is how big the auth tag will be
      */
      GCM_Decryption(BlockCipher* cipher, size_t tag_size = 16) :
         GCM_Mode(cipher, tag_size) {}

      size_t output_length(size_t input_length) const override
         {
         BOTAN_ASSERT(input_length >= tag_size(), "Sufficient input");
         return input_length - tag_size();
         }

      size_t minimum_final_size() const override { return tag_size(); }

      size_t process(uint8_t buf[], size_t size) override;

      void finish(secure_vector<uint8_t>& final_block, size_t offset = 0) override;
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(ghash.h)

namespace Botan {

/**
* GCM's GHASH
* This is not intended for general use, but is exposed to allow
* shared code between GCM and GMAC
*/
class BOTAN_PUBLIC_API(2,0) GHASH final : public SymmetricAlgorithm
   {
   public:
      void set_associated_data(const uint8_t ad[], size_t ad_len);

      secure_vector<uint8_t> BOTAN_DEPRECATED("Use other impl")
         nonce_hash(const uint8_t nonce[], size_t nonce_len)
         {
         secure_vector<uint8_t> y0(GCM_BS);
         nonce_hash(y0, nonce, nonce_len);
         return y0;
         }

      void nonce_hash(secure_vector<uint8_t>& y0, const uint8_t nonce[], size_t len);

      void start(const uint8_t nonce[], size_t len);

      /*
      * Assumes input len is multiple of 16
      */
      void update(const uint8_t in[], size_t len);

      /*
      * Incremental update of associated data
      */
      void update_associated_data(const uint8_t ad[], size_t len);

      secure_vector<uint8_t> BOTAN_DEPRECATED("Use version taking output params") final()
         {
         secure_vector<uint8_t> mac(GCM_BS);
         final(mac.data(), mac.size());
         return mac;
         }

      void final(uint8_t out[], size_t out_len);

      Key_Length_Specification key_spec() const override
         { return Key_Length_Specification(16); }

      void clear() override;

      void reset();

      std::string name() const override { return "GHASH"; }

      std::string provider() const;

      void ghash_update(secure_vector<uint8_t>& x,
                        const uint8_t input[], size_t input_len);

      void add_final_block(secure_vector<uint8_t>& x,
                           size_t ad_len, size_t pt_len);
   private:

#if defined(BOTAN_HAS_GHASH_CLMUL_CPU)
      static void ghash_precompute_cpu(const uint8_t H[16], uint64_t H_pow[4*2]);

      static void ghash_multiply_cpu(uint8_t x[16],
                                     const uint64_t H_pow[4*2],
                                     const uint8_t input[], size_t blocks);
#endif

#if defined(BOTAN_HAS_GHASH_CLMUL_VPERM)
      static void ghash_multiply_vperm(uint8_t x[16],
                                       const uint64_t HM[256],
                                       const uint8_t input[], size_t blocks);
#endif

      void key_schedule(const uint8_t key[], size_t key_len) override;

      void ghash_multiply(secure_vector<uint8_t>& x,
                          const uint8_t input[],
                          size_t blocks);

      static const size_t GCM_BS = 16;

      secure_vector<uint8_t> m_H;
      secure_vector<uint8_t> m_H_ad;
      secure_vector<uint8_t> m_ghash;
      secure_vector<uint8_t> m_nonce;
      secure_vector<uint64_t> m_HM;
      secure_vector<uint64_t> m_H_pow;
      size_t m_ad_len = 0;
      size_t m_text_len = 0;
   };

}

namespace Botan {

/**
* Return the PKCS #1 hash identifier
* @see RFC 3447 section 9.2
* @param hash_name the name of the hash function
* @return uint8_t sequence identifying the hash
* @throw Invalid_Argument if the hash has no known PKCS #1 hash id
*/
BOTAN_PUBLIC_API(2,0) std::vector<uint8_t> pkcs_hash_id(const std::string& hash_name);

/**
* Return the IEEE 1363 hash identifier
* @param hash_name the name of the hash function
* @return uint8_t code identifying the hash, or 0 if not known
*/
BOTAN_PUBLIC_API(2,0) uint8_t ieee1363_hash_id(const std::string& hash_name);

}

namespace Botan {

/**
* Perform hex encoding
* @param output an array of at least input_length*2 bytes
* @param input is some binary data
* @param input_length length of input in bytes
* @param uppercase should output be upper or lower case?
*/
void BOTAN_PUBLIC_API(2,0) hex_encode(char output[],
                          const uint8_t input[],
                          size_t input_length,
                          bool uppercase = true);

/**
* Perform hex encoding
* @param input some input
* @param input_length length of input in bytes
* @param uppercase should output be upper or lower case?
* @return hexadecimal representation of input
*/
std::string BOTAN_PUBLIC_API(2,0) hex_encode(const uint8_t input[],
                                 size_t input_length,
                                 bool uppercase = true);

/**
* Perform hex encoding
* @param input some input
* @param uppercase should output be upper or lower case?
* @return hexadecimal representation of input
*/
template<typename Alloc>
std::string hex_encode(const std::vector<uint8_t, Alloc>& input,
                       bool uppercase = true)
   {
   return hex_encode(input.data(), input.size(), uppercase);
   }

/**
* Perform hex decoding
* @param output an array of at least input_length/2 bytes
* @param input some hex input
* @param input_length length of input in bytes
* @param input_consumed is an output parameter which says how many
*        bytes of input were actually consumed. If less than
*        input_length, then the range input[consumed:length]
*        should be passed in later along with more input.
* @param ignore_ws ignore whitespace on input; if false, throw an
                   exception if whitespace is encountered
* @return number of bytes written to output
*/
size_t BOTAN_PUBLIC_API(2,0) hex_decode(uint8_t output[],
                            const char input[],
                            size_t input_length,
                            size_t& input_consumed,
                            bool ignore_ws = true);

/**
* Perform hex decoding
* @param output an array of at least input_length/2 bytes
* @param input some hex input
* @param input_length length of input in bytes
* @param ignore_ws ignore whitespace on input; if false, throw an
                   exception if whitespace is encountered
* @return number of bytes written to output
*/
size_t BOTAN_PUBLIC_API(2,0) hex_decode(uint8_t output[],
                            const char input[],
                            size_t input_length,
                            bool ignore_ws = true);

/**
* Perform hex decoding
* @param output an array of at least input_length/2 bytes
* @param input some hex input
* @param ignore_ws ignore whitespace on input; if false, throw an
                   exception if whitespace is encountered
* @return number of bytes written to output
*/
size_t BOTAN_PUBLIC_API(2,0) hex_decode(uint8_t output[],
                            const std::string& input,
                            bool ignore_ws = true);

/**
* Perform hex decoding
* @param input some hex input
* @param input_length the length of input in bytes
* @param ignore_ws ignore whitespace on input; if false, throw an
                   exception if whitespace is encountered
* @return decoded hex output
*/
std::vector<uint8_t> BOTAN_PUBLIC_API(2,0)
hex_decode(const char input[],
           size_t input_length,
           bool ignore_ws = true);

/**
* Perform hex decoding
* @param input some hex input
* @param ignore_ws ignore whitespace on input; if false, throw an
                   exception if whitespace is encountered
* @return decoded hex output
*/
std::vector<uint8_t> BOTAN_PUBLIC_API(2,0)
hex_decode(const std::string& input,
           bool ignore_ws = true);


/**
* Perform hex decoding
* @param input some hex input
* @param input_length the length of input in bytes
* @param ignore_ws ignore whitespace on input; if false, throw an
                   exception if whitespace is encountered
* @return decoded hex output
*/
secure_vector<uint8_t> BOTAN_PUBLIC_API(2,0)
hex_decode_locked(const char input[],
                  size_t input_length,
                  bool ignore_ws = true);

/**
* Perform hex decoding
* @param input some hex input
* @param ignore_ws ignore whitespace on input; if false, throw an
                   exception if whitespace is encountered
* @return decoded hex output
*/
secure_vector<uint8_t> BOTAN_PUBLIC_API(2,0)
hex_decode_locked(const std::string& input,
                  bool ignore_ws = true);

}

namespace Botan {

/**
* This class represents Message Authentication Code (MAC) objects.
*/
class BOTAN_PUBLIC_API(2,0) MessageAuthenticationCode : public Buffered_Computation,
                                            public SymmetricAlgorithm
   {
   public:
      /**
      * Create an instance based on a name
      * If provider is empty then best available is chosen.
      * @param algo_spec algorithm name
      * @param provider provider implementation to use
      * @return a null pointer if the algo/provider combination cannot be found
      */
      static std::unique_ptr<MessageAuthenticationCode>
         create(const std::string& algo_spec,
                const std::string& provider = "");

      /*
      * Create an instance based on a name
      * If provider is empty then best available is chosen.
      * @param algo_spec algorithm name
      * @param provider provider implementation to use
      * Throws a Lookup_Error if algo/provider combination cannot be found
      */
      static std::unique_ptr<MessageAuthenticationCode>
         create_or_throw(const std::string& algo_spec,
                         const std::string& provider = "");

      /**
      * @return list of available providers for this algorithm, empty if not available
      */
      static std::vector<std::string> providers(const std::string& algo_spec);

      virtual ~MessageAuthenticationCode() = default;

      /**
      * Prepare for processing a message under the specified nonce
      *
      * Most MACs neither require nor support a nonce; for these algorithms
      * calling `start_msg` is optional and calling it with anything other than
      * an empty string is an error. One MAC which *requires* a per-message
      * nonce be specified is GMAC.
      *
      * @param nonce the message nonce bytes
      * @param nonce_len the size of len in bytes
      * Default implementation simply rejects all non-empty nonces
      * since most hash/MAC algorithms do not support randomization
      */
      virtual void start_msg(const uint8_t nonce[], size_t nonce_len);

      /**
      * Begin processing a message with a nonce
      *
      * @param nonce the per message nonce
      */
      template<typename Alloc>
      void start(const std::vector<uint8_t, Alloc>& nonce)
         {
         start_msg(nonce.data(), nonce.size());
         }

      /**
      * Begin processing a message.
      * @param nonce the per message nonce
      * @param nonce_len length of nonce
      */
      void start(const uint8_t nonce[], size_t nonce_len)
         {
         start_msg(nonce, nonce_len);
         }

      /**
      * Begin processing a message.
      */
      void start()
         {
         return start_msg(nullptr, 0);
         }

      /**
      * Verify a MAC.
      * @param in the MAC to verify as a byte array
      * @param length the length of param in
      * @return true if the MAC is valid, false otherwise
      */
      virtual bool verify_mac(const uint8_t in[], size_t length);

      /**
      * Verify a MAC.
      * @param in the MAC to verify as a byte array
      * @return true if the MAC is valid, false otherwise
      */
      virtual bool verify_mac(const std::vector<uint8_t>& in)
         {
         return verify_mac(in.data(), in.size());
         }

      /**
      * Verify a MAC.
      * @param in the MAC to verify as a byte array
      * @return true if the MAC is valid, false otherwise
      */
      virtual bool verify_mac(const secure_vector<uint8_t>& in)
         {
         return verify_mac(in.data(), in.size());
         }

      /**
      * Get a new object representing the same algorithm as *this
      */
      virtual MessageAuthenticationCode* clone() const = 0;

      /**
      * @return provider information about this implementation. Default is "base",
      * might also return "sse2", "avx2", "openssl", or some other arbitrary string.
      */
      virtual std::string provider() const { return "base"; }

   };

typedef MessageAuthenticationCode MAC;

}

BOTAN_FUTURE_INTERNAL_HEADER(hmac.h)

namespace Botan {

/**
* HMAC
*/
class BOTAN_PUBLIC_API(2,0) HMAC final : public MessageAuthenticationCode
   {
   public:
      void clear() override;
      std::string name() const override;
      MessageAuthenticationCode* clone() const override;

      size_t output_length() const override;

      Key_Length_Specification key_spec() const override;

      /**
      * @param hash the hash to use for HMACing
      */
      explicit HMAC(HashFunction* hash);

      HMAC(const HMAC&) = delete;
      HMAC& operator=(const HMAC&) = delete;
   private:
      void add_data(const uint8_t[], size_t) override;
      void final_result(uint8_t[]) override;
      void key_schedule(const uint8_t[], size_t) override;

      std::unique_ptr<HashFunction> m_hash;
      secure_vector<uint8_t> m_ikey, m_okey;
      size_t m_hash_output_length;
      size_t m_hash_block_size;
   };

}

namespace Botan {

/**
* Inherited by RNGs which maintain in-process state, like HMAC_DRBG.
* On Unix these RNGs are vulnerable to problems with fork, where the
* RNG state is duplicated, and the parent and child process RNGs will
* produce identical output until one of them reseeds. Stateful_RNG
* reseeds itself whenever a fork is detected, or after a set number of
* bytes have been output.
*
* Not implemented by RNGs which access an external RNG, such as the
* system PRNG or a hardware RNG.
*/
class BOTAN_PUBLIC_API(2,0) Stateful_RNG : public RandomNumberGenerator
   {
   public:
      /**
      * @param rng is a reference to some RNG which will be used
      * to perform the periodic reseeding
      * @param entropy_sources will be polled to perform reseeding periodically
      * @param reseed_interval specifies a limit of how many times
      * the RNG will be called before automatic reseeding is performed
      */
      Stateful_RNG(RandomNumberGenerator& rng,
                   Entropy_Sources& entropy_sources,
                   size_t reseed_interval) :
         m_underlying_rng(&rng),
         m_entropy_sources(&entropy_sources),
         m_reseed_interval(reseed_interval)
         {}

      /**
      * @param rng is a reference to some RNG which will be used
      * to perform the periodic reseeding
      * @param reseed_interval specifies a limit of how many times
      * the RNG will be called before automatic reseeding is performed
      */
      Stateful_RNG(RandomNumberGenerator& rng, size_t reseed_interval) :
         m_underlying_rng(&rng),
         m_reseed_interval(reseed_interval)
         {}

      /**
      * @param entropy_sources will be polled to perform reseeding periodically
      * @param reseed_interval specifies a limit of how many times
      * the RNG will be called before automatic reseeding is performed
      */
      Stateful_RNG(Entropy_Sources& entropy_sources, size_t reseed_interval) :
         m_entropy_sources(&entropy_sources),
         m_reseed_interval(reseed_interval)
         {}

      /**
      * In this case, automatic reseeding is impossible
      */
      Stateful_RNG() : m_reseed_interval(0) {}

      /**
      * Consume this input and mark the RNG as initialized regardless
      * of the length of the input or the current seeded state of
      * the RNG.
      */
      void initialize_with(const uint8_t input[], size_t length);

      bool is_seeded() const override final;

      bool accepts_input() const override final { return true; }

      /**
      * Mark state as requiring a reseed on next use
      */
      void force_reseed();

      void reseed_from_rng(RandomNumberGenerator& rng,
                           size_t poll_bits = BOTAN_RNG_RESEED_POLL_BITS) override final;

      void add_entropy(const uint8_t input[], size_t input_len) override final;

      void randomize(uint8_t output[], size_t output_len) override final;

      void randomize_with_input(uint8_t output[], size_t output_len,
                                const uint8_t input[], size_t input_len) override final;

      /**
      * Overrides default implementation and also includes the current
      * process ID and the reseed counter.
      */
      void randomize_with_ts_input(uint8_t output[], size_t output_len) override final;

      /**
      * Poll provided sources for up to poll_bits bits of entropy
      * or until the timeout expires. Returns estimate of the number
      * of bits collected.
      */
      size_t reseed(Entropy_Sources& srcs,
                    size_t poll_bits = BOTAN_RNG_RESEED_POLL_BITS,
                    std::chrono::milliseconds poll_timeout = BOTAN_RNG_RESEED_DEFAULT_TIMEOUT) override;

      /**
      * @return intended security level of this DRBG
      */
      virtual size_t security_level() const = 0;

      /**
      * Some DRBGs have a notion of the maximum number of bytes per
      * request.  Longer requests (to randomize) will be treated as
      * multiple requests, and may initiate reseeding multiple times,
      * depending on the values of max_number_of_bytes_per_request and
      * reseed_interval(). This function returns zero if the RNG in
      * question does not have such a notion.
      *
      * @return max number of bytes per request (or zero)
      */
      virtual size_t max_number_of_bytes_per_request() const = 0;

      size_t reseed_interval() const { return m_reseed_interval; }

      void clear() override final;

   protected:
      void reseed_check();

      virtual void generate_output(uint8_t output[], size_t output_len,
                                   const uint8_t input[], size_t input_len) = 0;

      virtual void update(const uint8_t input[], size_t input_len) = 0;

      virtual void clear_state() = 0;

   private:
      void reset_reseed_counter();

      mutable recursive_mutex_type m_mutex;

      // A non-owned and possibly null pointer to shared RNG
      RandomNumberGenerator* m_underlying_rng = nullptr;

      // A non-owned and possibly null pointer to a shared Entropy_Source
      Entropy_Sources* m_entropy_sources = nullptr;

      const size_t m_reseed_interval;
      uint32_t m_last_pid = 0;

      /*
      * Set to 1 after a successful seeding, then incremented.  Reset
      * to 0 by clear() or a fork. This logic is used even if
      * automatic reseeding is disabled (via m_reseed_interval = 0)
      */
      size_t m_reseed_counter = 0;
   };

}

namespace Botan {

class Entropy_Sources;

/**
* HMAC_DRBG from NIST SP800-90A
*/
class BOTAN_PUBLIC_API(2,0) HMAC_DRBG final : public Stateful_RNG
   {
   public:
      /**
      * Initialize an HMAC_DRBG instance with the given MAC as PRF (normally HMAC)
      *
      * Automatic reseeding is disabled completely, as it has no access to
      * any source for seed material.
      *
      * If a fork is detected, the RNG will be unable to reseed itself
      * in response. In this case, an exception will be thrown rather
      * than generating duplicated output.
      */
      explicit HMAC_DRBG(std::unique_ptr<MessageAuthenticationCode> prf);

      /**
      * Constructor taking a string for the hash
      */
      explicit HMAC_DRBG(const std::string& hmac_hash);

      /**
      * Initialize an HMAC_DRBG instance with the given MAC as PRF (normally HMAC)
      *
      * Automatic reseeding from @p underlying_rng will take place after
      * @p reseed_interval many requests or after a fork was detected.
      *
      * @param prf MAC to use as a PRF
      * @param underlying_rng is a reference to some RNG which will be used
      * to perform the periodic reseeding
      * @param reseed_interval specifies a limit of how many times
      * the RNG will be called before automatic reseeding is performed (max. 2^24)
      * @param max_number_of_bytes_per_request requests that are in size higher
      * than max_number_of_bytes_per_request are treated as if multiple single
      * requests of max_number_of_bytes_per_request size had been made.
      * In theory SP 800-90A requires that we reject any request for a DRBG
      * output longer than max_number_of_bytes_per_request. To avoid inconveniencing
      * the caller who wants an output larger than max_number_of_bytes_per_request,
      * instead treat these requests as if multiple requests of
      * max_number_of_bytes_per_request size had been made. NIST requires for
      * HMAC_DRBG that every implementation set a value no more than 2**19 bits
      * (or 64 KiB). Together with @p reseed_interval = 1 you can enforce that for
      * example every 512 bit automatic reseeding occurs.
      */
      HMAC_DRBG(std::unique_ptr<MessageAuthenticationCode> prf,
                RandomNumberGenerator& underlying_rng,
                size_t reseed_interval = BOTAN_RNG_DEFAULT_RESEED_INTERVAL,
                size_t max_number_of_bytes_per_request = 64 * 1024);

      /**
      * Initialize an HMAC_DRBG instance with the given MAC as PRF (normally HMAC)
      *
      * Automatic reseeding from @p entropy_sources will take place after
      * @p reseed_interval many requests or after a fork was detected.
      *
      * @param prf MAC to use as a PRF
      * @param entropy_sources will be polled to perform reseeding periodically
      * @param reseed_interval specifies a limit of how many times
      * the RNG will be called before automatic reseeding is performed (max. 2^24)
      * @param max_number_of_bytes_per_request requests that are in size higher
      * than max_number_of_bytes_per_request are treated as if multiple single
      * requests of max_number_of_bytes_per_request size had been made.
      * In theory SP 800-90A requires that we reject any request for a DRBG
      * output longer than max_number_of_bytes_per_request. To avoid inconveniencing
      * the caller who wants an output larger than max_number_of_bytes_per_request,
      * instead treat these requests as if multiple requests of
      * max_number_of_bytes_per_request size had been made. NIST requires for
      * HMAC_DRBG that every implementation set a value no more than 2**19 bits
      * (or 64 KiB). Together with @p reseed_interval = 1 you can enforce that for
      * example every 512 bit automatic reseeding occurs.
      */
      HMAC_DRBG(std::unique_ptr<MessageAuthenticationCode> prf,
                Entropy_Sources& entropy_sources,
                size_t reseed_interval = BOTAN_RNG_DEFAULT_RESEED_INTERVAL,
                size_t max_number_of_bytes_per_request = 64 * 1024);

      /**
      * Initialize an HMAC_DRBG instance with the given MAC as PRF (normally HMAC)
      *
      * Automatic reseeding from @p underlying_rng and @p entropy_sources
      * will take place after @p reseed_interval many requests or after
      * a fork was detected.
      *
      * @param prf MAC to use as a PRF
      * @param underlying_rng is a reference to some RNG which will be used
      * to perform the periodic reseeding
      * @param entropy_sources will be polled to perform reseeding periodically
      * @param reseed_interval specifies a limit of how many times
      * the RNG will be called before automatic reseeding is performed (max. 2^24)
      * @param max_number_of_bytes_per_request requests that are in size higher
      * than max_number_of_bytes_per_request are treated as if multiple single
      * requests of max_number_of_bytes_per_request size had been made.
      * In theory SP 800-90A requires that we reject any request for a DRBG
      * output longer than max_number_of_bytes_per_request. To avoid inconveniencing
      * the caller who wants an output larger than max_number_of_bytes_per_request,
      * instead treat these requests as if multiple requests of
      * max_number_of_bytes_per_request size had been made. NIST requires for
      * HMAC_DRBG that every implementation set a value no more than 2**19 bits
      * (or 64 KiB). Together with @p reseed_interval = 1 you can enforce that for
      * example every 512 bit automatic reseeding occurs.
      */
      HMAC_DRBG(std::unique_ptr<MessageAuthenticationCode> prf,
                RandomNumberGenerator& underlying_rng,
                Entropy_Sources& entropy_sources,
                size_t reseed_interval = BOTAN_RNG_DEFAULT_RESEED_INTERVAL,
                size_t max_number_of_bytes_per_request = 64 * 1024);

      std::string name() const override;

      size_t security_level() const override;

      size_t max_number_of_bytes_per_request() const override
         { return m_max_number_of_bytes_per_request; }

   private:
      void update(const uint8_t input[], size_t input_len) override;

      void generate_output(uint8_t output[], size_t output_len,
                           const uint8_t input[], size_t input_len) override;

      void clear_state() override;

      std::unique_ptr<MessageAuthenticationCode> m_mac;
      secure_vector<uint8_t> m_V;
      const size_t m_max_number_of_bytes_per_request;
      const size_t m_security_level;
   };

}

namespace Botan {

/**
* Key Derivation Function
*/
class BOTAN_PUBLIC_API(2,0) KDF
   {
   public:
      virtual ~KDF() = default;

      /**
      * Create an instance based on a name
      * If provider is empty then best available is chosen.
      * @param algo_spec algorithm name
      * @param provider provider implementation to choose
      * @return a null pointer if the algo/provider combination cannot be found
      */
      static std::unique_ptr<KDF>
         create(const std::string& algo_spec,
                const std::string& provider = "");

      /**
      * Create an instance based on a name, or throw if the
      * algo/provider combination cannot be found. If provider is
      * empty then best available is chosen.
      */
      static std::unique_ptr<KDF>
         create_or_throw(const std::string& algo_spec,
                         const std::string& provider = "");

      /**
      * @return list of available providers for this algorithm, empty if not available
      */
      static std::vector<std::string> providers(const std::string& algo_spec);

      /**
      * @return KDF name
      */
      virtual std::string name() const = 0;

      /**
      * Derive a key
      * @param key buffer holding the derived key, must be of length key_len
      * @param key_len the desired output length in bytes
      * @param secret the secret input
      * @param secret_len size of secret in bytes
      * @param salt a diversifier
      * @param salt_len size of salt in bytes
      * @param label purpose for the derived keying material
      * @param label_len size of label in bytes
      * @return the derived key
      */
      virtual size_t kdf(uint8_t key[], size_t key_len,
                         const uint8_t secret[], size_t secret_len,
                         const uint8_t salt[], size_t salt_len,
                         const uint8_t label[], size_t label_len) const = 0;

      /**
      * Derive a key
      * @param key_len the desired output length in bytes
      * @param secret the secret input
      * @param secret_len size of secret in bytes
      * @param salt a diversifier
      * @param salt_len size of salt in bytes
      * @param label purpose for the derived keying material
      * @param label_len size of label in bytes
      * @return the derived key
      */
      secure_vector<uint8_t> derive_key(size_t key_len,
                                    const uint8_t secret[],
                                    size_t secret_len,
                                    const uint8_t salt[],
                                    size_t salt_len,
                                    const uint8_t label[] = nullptr,
                                    size_t label_len = 0) const
         {
         secure_vector<uint8_t> key(key_len);
         key.resize(kdf(key.data(), key.size(), secret, secret_len, salt, salt_len, label, label_len));
         return key;
         }

      /**
      * Derive a key
      * @param key_len the desired output length in bytes
      * @param secret the secret input
      * @param salt a diversifier
      * @param label purpose for the derived keying material
      * @return the derived key
      */
      secure_vector<uint8_t> derive_key(size_t key_len,
                                    const secure_vector<uint8_t>& secret,
                                    const std::string& salt = "",
                                    const std::string& label = "") const
         {
         return derive_key(key_len, secret.data(), secret.size(),
                           cast_char_ptr_to_uint8(salt.data()),
                           salt.length(),
                           cast_char_ptr_to_uint8(label.data()),
                           label.length());

         }

      /**
      * Derive a key
      * @param key_len the desired output length in bytes
      * @param secret the secret input
      * @param salt a diversifier
      * @param label purpose for the derived keying material
      * @return the derived key
      */
      template<typename Alloc, typename Alloc2, typename Alloc3>
      secure_vector<uint8_t> derive_key(size_t key_len,
                                     const std::vector<uint8_t, Alloc>& secret,
                                     const std::vector<uint8_t, Alloc2>& salt,
                                     const std::vector<uint8_t, Alloc3>& label) const
         {
         return derive_key(key_len,
                           secret.data(), secret.size(),
                           salt.data(), salt.size(),
                           label.data(), label.size());
         }

      /**
      * Derive a key
      * @param key_len the desired output length in bytes
      * @param secret the secret input
      * @param salt a diversifier
      * @param salt_len size of salt in bytes
      * @param label purpose for the derived keying material
      * @return the derived key
      */
      secure_vector<uint8_t> derive_key(size_t key_len,
                                    const secure_vector<uint8_t>& secret,
                                    const uint8_t salt[],
                                    size_t salt_len,
                                    const std::string& label = "") const
         {
         return derive_key(key_len,
                           secret.data(), secret.size(),
                           salt, salt_len,
                           cast_char_ptr_to_uint8(label.data()),
                           label.size());
         }

      /**
      * Derive a key
      * @param key_len the desired output length in bytes
      * @param secret the secret input
      * @param secret_len size of secret in bytes
      * @param salt a diversifier
      * @param label purpose for the derived keying material
      * @return the derived key
      */
      secure_vector<uint8_t> derive_key(size_t key_len,
                                    const uint8_t secret[],
                                    size_t secret_len,
                                    const std::string& salt = "",
                                    const std::string& label = "") const
         {
         return derive_key(key_len, secret, secret_len,
                           cast_char_ptr_to_uint8(salt.data()),
                           salt.length(),
                           cast_char_ptr_to_uint8(label.data()),
                           label.length());
         }

      /**
      * @return new object representing the same algorithm as *this
      */
      virtual KDF* clone() const = 0;
   };

/**
* Factory method for KDF (key derivation function)
* @param algo_spec the name of the KDF to create
* @return pointer to newly allocated object of that type
*/
BOTAN_PUBLIC_API(2,0) KDF* get_kdf(const std::string& algo_spec);

}

BOTAN_FUTURE_INTERNAL_HEADER(kdf2.h)

namespace Botan {

/**
* KDF2, from IEEE 1363
*/
class BOTAN_PUBLIC_API(2,0) KDF2 final : public KDF
   {
   public:
      std::string name() const override { return "KDF2(" + m_hash->name() + ")"; }

      KDF* clone() const override { return new KDF2(m_hash->clone()); }

      size_t kdf(uint8_t key[], size_t key_len,
                 const uint8_t secret[], size_t secret_len,
                 const uint8_t salt[], size_t salt_len,
                 const uint8_t label[], size_t label_len) const override;

      /**
      * @param h hash function to use
      */
      explicit KDF2(HashFunction* h) : m_hash(h) {}
   private:
      std::unique_ptr<HashFunction> m_hash;
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(keypair.h)

namespace Botan {

namespace KeyPair {

/**
* Tests whether the key is consistent for encryption; whether
* encrypting and then decrypting gives to the original plaintext.
* @param rng the rng to use
* @param private_key the key to test
* @param public_key the key to test
* @param padding the encryption padding method to use
* @return true if consistent otherwise false
*/
BOTAN_PUBLIC_API(2,0) bool
encryption_consistency_check(RandomNumberGenerator& rng,
                             const Private_Key& private_key,
                             const Public_Key& public_key,
                             const std::string& padding);

/**
* Tests whether the key is consistent for signatures; whether a
* signature can be created and then verified
* @param rng the rng to use
* @param private_key the key to test
* @param public_key the key to test
* @param padding the signature padding method to use
* @return true if consistent otherwise false
*/
BOTAN_PUBLIC_API(2,0) bool
signature_consistency_check(RandomNumberGenerator& rng,
                            const Private_Key& private_key,
                            const Public_Key& public_key,
                            const std::string& padding);

/**
* Tests whether the key is consistent for encryption; whether
* encrypting and then decrypting gives to the original plaintext.
* @param rng the rng to use
* @param key the key to test
* @param padding the encryption padding method to use
* @return true if consistent otherwise false
*/
inline bool
encryption_consistency_check(RandomNumberGenerator& rng,
                             const Private_Key& key,
                             const std::string& padding)
   {
   return encryption_consistency_check(rng, key, key, padding);
   }

/**
* Tests whether the key is consistent for signatures; whether a
* signature can be created and then verified
* @param rng the rng to use
* @param key the key to test
* @param padding the signature padding method to use
* @return true if consistent otherwise false
*/
inline bool
signature_consistency_check(RandomNumberGenerator& rng,
                            const Private_Key& key,
                            const std::string& padding)
   {
   return signature_consistency_check(rng, key, key, padding);
   }

}

}

BOTAN_FUTURE_INTERNAL_HEADER(loadstor.h)

#if defined(BOTAN_TARGET_CPU_IS_BIG_ENDIAN)
   #define BOTAN_ENDIAN_N2L(x) reverse_bytes(x)
   #define BOTAN_ENDIAN_L2N(x) reverse_bytes(x)
   #define BOTAN_ENDIAN_N2B(x) (x)
   #define BOTAN_ENDIAN_B2N(x) (x)

#elif defined(BOTAN_TARGET_CPU_IS_LITTLE_ENDIAN)
   #define BOTAN_ENDIAN_N2L(x) (x)
   #define BOTAN_ENDIAN_L2N(x) (x)
   #define BOTAN_ENDIAN_N2B(x) reverse_bytes(x)
   #define BOTAN_ENDIAN_B2N(x) reverse_bytes(x)

#endif

namespace Botan {

/**
* Byte extraction
* @param byte_num which byte to extract, 0 == highest byte
* @param input the value to extract from
* @return byte byte_num of input
*/
template<typename T> inline constexpr uint8_t get_byte(size_t byte_num, T input)
   {
   return static_cast<uint8_t>(
      input >> (((~byte_num)&(sizeof(T)-1)) << 3)
      );
   }

/**
* Make a uint16_t from two bytes
* @param i0 the first byte
* @param i1 the second byte
* @return i0 || i1
*/
inline constexpr uint16_t make_uint16(uint8_t i0, uint8_t i1)
   {
   return static_cast<uint16_t>((static_cast<uint16_t>(i0) << 8) | i1);
   }

/**
* Make a uint32_t from four bytes
* @param i0 the first byte
* @param i1 the second byte
* @param i2 the third byte
* @param i3 the fourth byte
* @return i0 || i1 || i2 || i3
*/
inline constexpr uint32_t make_uint32(uint8_t i0, uint8_t i1, uint8_t i2, uint8_t i3)
   {
   return ((static_cast<uint32_t>(i0) << 24) |
           (static_cast<uint32_t>(i1) << 16) |
           (static_cast<uint32_t>(i2) <<  8) |
           (static_cast<uint32_t>(i3)));
   }

/**
* Make a uint64_t from eight bytes
* @param i0 the first byte
* @param i1 the second byte
* @param i2 the third byte
* @param i3 the fourth byte
* @param i4 the fifth byte
* @param i5 the sixth byte
* @param i6 the seventh byte
* @param i7 the eighth byte
* @return i0 || i1 || i2 || i3 || i4 || i5 || i6 || i7
*/
inline constexpr uint64_t make_uint64(uint8_t i0, uint8_t i1, uint8_t i2, uint8_t i3,
                                      uint8_t i4, uint8_t i5, uint8_t i6, uint8_t i7)
    {
   return ((static_cast<uint64_t>(i0) << 56) |
           (static_cast<uint64_t>(i1) << 48) |
           (static_cast<uint64_t>(i2) << 40) |
           (static_cast<uint64_t>(i3) << 32) |
           (static_cast<uint64_t>(i4) << 24) |
           (static_cast<uint64_t>(i5) << 16) |
           (static_cast<uint64_t>(i6) <<  8) |
           (static_cast<uint64_t>(i7)));
    }

/**
* Load a big-endian word
* @param in a pointer to some bytes
* @param off an offset into the array
* @return off'th T of in, as a big-endian value
*/
template<typename T>
inline T load_be(const uint8_t in[], size_t off)
   {
   in += off * sizeof(T);
   T out = 0;
   for(size_t i = 0; i != sizeof(T); ++i)
      out = static_cast<T>((out << 8) | in[i]);
   return out;
   }

/**
* Load a little-endian word
* @param in a pointer to some bytes
* @param off an offset into the array
* @return off'th T of in, as a litte-endian value
*/
template<typename T>
inline T load_le(const uint8_t in[], size_t off)
   {
   in += off * sizeof(T);
   T out = 0;
   for(size_t i = 0; i != sizeof(T); ++i)
      out = (out << 8) | in[sizeof(T)-1-i];
   return out;
   }

/**
* Load a big-endian uint16_t
* @param in a pointer to some bytes
* @param off an offset into the array
* @return off'th uint16_t of in, as a big-endian value
*/
template<>
inline uint16_t load_be<uint16_t>(const uint8_t in[], size_t off)
   {
   in += off * sizeof(uint16_t);

#if defined(BOTAN_ENDIAN_N2B)
   uint16_t x;
   typecast_copy(x, in);
   return BOTAN_ENDIAN_N2B(x);
#else
   return make_uint16(in[0], in[1]);
#endif
   }

/**
* Load a little-endian uint16_t
* @param in a pointer to some bytes
* @param off an offset into the array
* @return off'th uint16_t of in, as a little-endian value
*/
template<>
inline uint16_t load_le<uint16_t>(const uint8_t in[], size_t off)
   {
   in += off * sizeof(uint16_t);

#if defined(BOTAN_ENDIAN_N2L)
   uint16_t x;
   typecast_copy(x, in);
   return BOTAN_ENDIAN_N2L(x);
#else
   return make_uint16(in[1], in[0]);
#endif
   }

/**
* Load a big-endian uint32_t
* @param in a pointer to some bytes
* @param off an offset into the array
* @return off'th uint32_t of in, as a big-endian value
*/
template<>
inline uint32_t load_be<uint32_t>(const uint8_t in[], size_t off)
   {
   in += off * sizeof(uint32_t);
#if defined(BOTAN_ENDIAN_N2B)
   uint32_t x;
   typecast_copy(x, in);
   return BOTAN_ENDIAN_N2B(x);
#else
   return make_uint32(in[0], in[1], in[2], in[3]);
#endif
   }

/**
* Load a little-endian uint32_t
* @param in a pointer to some bytes
* @param off an offset into the array
* @return off'th uint32_t of in, as a little-endian value
*/
template<>
inline uint32_t load_le<uint32_t>(const uint8_t in[], size_t off)
   {
   in += off * sizeof(uint32_t);
#if defined(BOTAN_ENDIAN_N2L)
   uint32_t x;
   typecast_copy(x, in);
   return BOTAN_ENDIAN_N2L(x);
#else
   return make_uint32(in[3], in[2], in[1], in[0]);
#endif
   }

/**
* Load a big-endian uint64_t
* @param in a pointer to some bytes
* @param off an offset into the array
* @return off'th uint64_t of in, as a big-endian value
*/
template<>
inline uint64_t load_be<uint64_t>(const uint8_t in[], size_t off)
   {
   in += off * sizeof(uint64_t);
#if defined(BOTAN_ENDIAN_N2B)
   uint64_t x;
   typecast_copy(x, in);
   return BOTAN_ENDIAN_N2B(x);
#else
   return make_uint64(in[0], in[1], in[2], in[3],
                      in[4], in[5], in[6], in[7]);
#endif
   }

/**
* Load a little-endian uint64_t
* @param in a pointer to some bytes
* @param off an offset into the array
* @return off'th uint64_t of in, as a little-endian value
*/
template<>
inline uint64_t load_le<uint64_t>(const uint8_t in[], size_t off)
   {
   in += off * sizeof(uint64_t);
#if defined(BOTAN_ENDIAN_N2L)
   uint64_t x;
   typecast_copy(x, in);
   return BOTAN_ENDIAN_N2L(x);
#else
   return make_uint64(in[7], in[6], in[5], in[4],
                      in[3], in[2], in[1], in[0]);
#endif
   }

/**
* Load two little-endian words
* @param in a pointer to some bytes
* @param x0 where the first word will be written
* @param x1 where the second word will be written
*/
template<typename T>
inline void load_le(const uint8_t in[], T& x0, T& x1)
   {
   x0 = load_le<T>(in, 0);
   x1 = load_le<T>(in, 1);
   }

/**
* Load four little-endian words
* @param in a pointer to some bytes
* @param x0 where the first word will be written
* @param x1 where the second word will be written
* @param x2 where the third word will be written
* @param x3 where the fourth word will be written
*/
template<typename T>
inline void load_le(const uint8_t in[],
                    T& x0, T& x1, T& x2, T& x3)
   {
   x0 = load_le<T>(in, 0);
   x1 = load_le<T>(in, 1);
   x2 = load_le<T>(in, 2);
   x3 = load_le<T>(in, 3);
   }

/**
* Load eight little-endian words
* @param in a pointer to some bytes
* @param x0 where the first word will be written
* @param x1 where the second word will be written
* @param x2 where the third word will be written
* @param x3 where the fourth word will be written
* @param x4 where the fifth word will be written
* @param x5 where the sixth word will be written
* @param x6 where the seventh word will be written
* @param x7 where the eighth word will be written
*/
template<typename T>
inline void load_le(const uint8_t in[],
                    T& x0, T& x1, T& x2, T& x3,
                    T& x4, T& x5, T& x6, T& x7)
   {
   x0 = load_le<T>(in, 0);
   x1 = load_le<T>(in, 1);
   x2 = load_le<T>(in, 2);
   x3 = load_le<T>(in, 3);
   x4 = load_le<T>(in, 4);
   x5 = load_le<T>(in, 5);
   x6 = load_le<T>(in, 6);
   x7 = load_le<T>(in, 7);
   }

/**
* Load a variable number of little-endian words
* @param out the output array of words
* @param in the input array of bytes
* @param count how many words are in in
*/
template<typename T>
inline void load_le(T out[],
                    const uint8_t in[],
                    size_t count)
   {
   if(count > 0)
      {
#if defined(BOTAN_TARGET_CPU_IS_LITTLE_ENDIAN)
      typecast_copy(out, in, count);

#elif defined(BOTAN_TARGET_CPU_IS_BIG_ENDIAN)
      typecast_copy(out, in, count);

      const size_t blocks = count - (count % 4);
      const size_t left = count - blocks;

      for(size_t i = 0; i != blocks; i += 4)
         bswap_4(out + i);

      for(size_t i = 0; i != left; ++i)
         out[blocks+i] = reverse_bytes(out[blocks+i]);
#else
      for(size_t i = 0; i != count; ++i)
         out[i] = load_le<T>(in, i);
#endif
      }
   }

/**
* Load two big-endian words
* @param in a pointer to some bytes
* @param x0 where the first word will be written
* @param x1 where the second word will be written
*/
template<typename T>
inline void load_be(const uint8_t in[], T& x0, T& x1)
   {
   x0 = load_be<T>(in, 0);
   x1 = load_be<T>(in, 1);
   }

/**
* Load four big-endian words
* @param in a pointer to some bytes
* @param x0 where the first word will be written
* @param x1 where the second word will be written
* @param x2 where the third word will be written
* @param x3 where the fourth word will be written
*/
template<typename T>
inline void load_be(const uint8_t in[],
                    T& x0, T& x1, T& x2, T& x3)
   {
   x0 = load_be<T>(in, 0);
   x1 = load_be<T>(in, 1);
   x2 = load_be<T>(in, 2);
   x3 = load_be<T>(in, 3);
   }

/**
* Load eight big-endian words
* @param in a pointer to some bytes
* @param x0 where the first word will be written
* @param x1 where the second word will be written
* @param x2 where the third word will be written
* @param x3 where the fourth word will be written
* @param x4 where the fifth word will be written
* @param x5 where the sixth word will be written
* @param x6 where the seventh word will be written
* @param x7 where the eighth word will be written
*/
template<typename T>
inline void load_be(const uint8_t in[],
                    T& x0, T& x1, T& x2, T& x3,
                    T& x4, T& x5, T& x6, T& x7)
   {
   x0 = load_be<T>(in, 0);
   x1 = load_be<T>(in, 1);
   x2 = load_be<T>(in, 2);
   x3 = load_be<T>(in, 3);
   x4 = load_be<T>(in, 4);
   x5 = load_be<T>(in, 5);
   x6 = load_be<T>(in, 6);
   x7 = load_be<T>(in, 7);
   }

/**
* Load a variable number of big-endian words
* @param out the output array of words
* @param in the input array of bytes
* @param count how many words are in in
*/
template<typename T>
inline void load_be(T out[],
                    const uint8_t in[],
                    size_t count)
   {
   if(count > 0)
      {
#if defined(BOTAN_TARGET_CPU_IS_BIG_ENDIAN)
      typecast_copy(out, in, count);

#elif defined(BOTAN_TARGET_CPU_IS_LITTLE_ENDIAN)
      typecast_copy(out, in, count);
      const size_t blocks = count - (count % 4);
      const size_t left = count - blocks;

      for(size_t i = 0; i != blocks; i += 4)
         bswap_4(out + i);

      for(size_t i = 0; i != left; ++i)
         out[blocks+i] = reverse_bytes(out[blocks+i]);
#else
      for(size_t i = 0; i != count; ++i)
         out[i] = load_be<T>(in, i);
#endif
      }
   }

/**
* Store a big-endian uint16_t
* @param in the input uint16_t
* @param out the byte array to write to
*/
inline void store_be(uint16_t in, uint8_t out[2])
   {
#if defined(BOTAN_ENDIAN_N2B)
   uint16_t o = BOTAN_ENDIAN_N2B(in);
   typecast_copy(out, o);
#else
   out[0] = get_byte(0, in);
   out[1] = get_byte(1, in);
#endif
   }

/**
* Store a little-endian uint16_t
* @param in the input uint16_t
* @param out the byte array to write to
*/
inline void store_le(uint16_t in, uint8_t out[2])
   {
#if defined(BOTAN_ENDIAN_N2L)
   uint16_t o = BOTAN_ENDIAN_N2L(in);
   typecast_copy(out, o);
#else
   out[0] = get_byte(1, in);
   out[1] = get_byte(0, in);
#endif
   }

/**
* Store a big-endian uint32_t
* @param in the input uint32_t
* @param out the byte array to write to
*/
inline void store_be(uint32_t in, uint8_t out[4])
   {
#if defined(BOTAN_ENDIAN_B2N)
   uint32_t o = BOTAN_ENDIAN_B2N(in);
   typecast_copy(out, o);
#else
   out[0] = get_byte(0, in);
   out[1] = get_byte(1, in);
   out[2] = get_byte(2, in);
   out[3] = get_byte(3, in);
#endif
   }

/**
* Store a little-endian uint32_t
* @param in the input uint32_t
* @param out the byte array to write to
*/
inline void store_le(uint32_t in, uint8_t out[4])
   {
#if defined(BOTAN_ENDIAN_L2N)
   uint32_t o = BOTAN_ENDIAN_L2N(in);
   typecast_copy(out, o);
#else
   out[0] = get_byte(3, in);
   out[1] = get_byte(2, in);
   out[2] = get_byte(1, in);
   out[3] = get_byte(0, in);
#endif
   }

/**
* Store a big-endian uint64_t
* @param in the input uint64_t
* @param out the byte array to write to
*/
inline void store_be(uint64_t in, uint8_t out[8])
   {
#if defined(BOTAN_ENDIAN_B2N)
   uint64_t o = BOTAN_ENDIAN_B2N(in);
   typecast_copy(out, o);
#else
   out[0] = get_byte(0, in);
   out[1] = get_byte(1, in);
   out[2] = get_byte(2, in);
   out[3] = get_byte(3, in);
   out[4] = get_byte(4, in);
   out[5] = get_byte(5, in);
   out[6] = get_byte(6, in);
   out[7] = get_byte(7, in);
#endif
   }

/**
* Store a little-endian uint64_t
* @param in the input uint64_t
* @param out the byte array to write to
*/
inline void store_le(uint64_t in, uint8_t out[8])
   {
#if defined(BOTAN_ENDIAN_L2N)
   uint64_t o = BOTAN_ENDIAN_L2N(in);
   typecast_copy(out, o);
#else
   out[0] = get_byte(7, in);
   out[1] = get_byte(6, in);
   out[2] = get_byte(5, in);
   out[3] = get_byte(4, in);
   out[4] = get_byte(3, in);
   out[5] = get_byte(2, in);
   out[6] = get_byte(1, in);
   out[7] = get_byte(0, in);
#endif
   }

/**
* Store two little-endian words
* @param out the output byte array
* @param x0 the first word
* @param x1 the second word
*/
template<typename T>
inline void store_le(uint8_t out[], T x0, T x1)
   {
   store_le(x0, out + (0 * sizeof(T)));
   store_le(x1, out + (1 * sizeof(T)));
   }

/**
* Store two big-endian words
* @param out the output byte array
* @param x0 the first word
* @param x1 the second word
*/
template<typename T>
inline void store_be(uint8_t out[], T x0, T x1)
   {
   store_be(x0, out + (0 * sizeof(T)));
   store_be(x1, out + (1 * sizeof(T)));
   }

/**
* Store four little-endian words
* @param out the output byte array
* @param x0 the first word
* @param x1 the second word
* @param x2 the third word
* @param x3 the fourth word
*/
template<typename T>
inline void store_le(uint8_t out[], T x0, T x1, T x2, T x3)
   {
   store_le(x0, out + (0 * sizeof(T)));
   store_le(x1, out + (1 * sizeof(T)));
   store_le(x2, out + (2 * sizeof(T)));
   store_le(x3, out + (3 * sizeof(T)));
   }

/**
* Store four big-endian words
* @param out the output byte array
* @param x0 the first word
* @param x1 the second word
* @param x2 the third word
* @param x3 the fourth word
*/
template<typename T>
inline void store_be(uint8_t out[], T x0, T x1, T x2, T x3)
   {
   store_be(x0, out + (0 * sizeof(T)));
   store_be(x1, out + (1 * sizeof(T)));
   store_be(x2, out + (2 * sizeof(T)));
   store_be(x3, out + (3 * sizeof(T)));
   }

/**
* Store eight little-endian words
* @param out the output byte array
* @param x0 the first word
* @param x1 the second word
* @param x2 the third word
* @param x3 the fourth word
* @param x4 the fifth word
* @param x5 the sixth word
* @param x6 the seventh word
* @param x7 the eighth word
*/
template<typename T>
inline void store_le(uint8_t out[], T x0, T x1, T x2, T x3,
                                 T x4, T x5, T x6, T x7)
   {
   store_le(x0, out + (0 * sizeof(T)));
   store_le(x1, out + (1 * sizeof(T)));
   store_le(x2, out + (2 * sizeof(T)));
   store_le(x3, out + (3 * sizeof(T)));
   store_le(x4, out + (4 * sizeof(T)));
   store_le(x5, out + (5 * sizeof(T)));
   store_le(x6, out + (6 * sizeof(T)));
   store_le(x7, out + (7 * sizeof(T)));
   }

/**
* Store eight big-endian words
* @param out the output byte array
* @param x0 the first word
* @param x1 the second word
* @param x2 the third word
* @param x3 the fourth word
* @param x4 the fifth word
* @param x5 the sixth word
* @param x6 the seventh word
* @param x7 the eighth word
*/
template<typename T>
inline void store_be(uint8_t out[], T x0, T x1, T x2, T x3,
                                 T x4, T x5, T x6, T x7)
   {
   store_be(x0, out + (0 * sizeof(T)));
   store_be(x1, out + (1 * sizeof(T)));
   store_be(x2, out + (2 * sizeof(T)));
   store_be(x3, out + (3 * sizeof(T)));
   store_be(x4, out + (4 * sizeof(T)));
   store_be(x5, out + (5 * sizeof(T)));
   store_be(x6, out + (6 * sizeof(T)));
   store_be(x7, out + (7 * sizeof(T)));
   }

template<typename T>
void copy_out_be(uint8_t out[], size_t out_bytes, const T in[])
   {
   while(out_bytes >= sizeof(T))
      {
      store_be(in[0], out);
      out += sizeof(T);
      out_bytes -= sizeof(T);
      in += 1;
   }

   for(size_t i = 0; i != out_bytes; ++i)
      out[i] = get_byte(i%8, in[0]);
   }

template<typename T, typename Alloc>
void copy_out_vec_be(uint8_t out[], size_t out_bytes, const std::vector<T, Alloc>& in)
   {
   copy_out_be(out, out_bytes, in.data());
   }

template<typename T>
void copy_out_le(uint8_t out[], size_t out_bytes, const T in[])
   {
   while(out_bytes >= sizeof(T))
      {
      store_le(in[0], out);
      out += sizeof(T);
      out_bytes -= sizeof(T);
      in += 1;
   }

   for(size_t i = 0; i != out_bytes; ++i)
      out[i] = get_byte(sizeof(T) - 1 - (i % 8), in[0]);
   }

template<typename T, typename Alloc>
void copy_out_vec_le(uint8_t out[], size_t out_bytes, const std::vector<T, Alloc>& in)
   {
   copy_out_le(out, out_bytes, in.data());
   }

}

BOTAN_FUTURE_INTERNAL_HEADER(mdx_hash.h)

namespace Botan {

/**
* MDx Hash Function Base Class
*/
class BOTAN_PUBLIC_API(2,0) MDx_HashFunction : public HashFunction
   {
   public:
      /**
      * @param block_length is the number of bytes per block, which must
      *        be a power of 2 and at least 8.
      * @param big_byte_endian specifies if the hash uses big-endian bytes
      * @param big_bit_endian specifies if the hash uses big-endian bits
      * @param counter_size specifies the size of the counter var in bytes
      */
      MDx_HashFunction(size_t block_length,
                       bool big_byte_endian,
                       bool big_bit_endian,
                       uint8_t counter_size = 8);

      size_t hash_block_size() const override final { return m_buffer.size(); }
   protected:
      void add_data(const uint8_t input[], size_t length) override final;
      void final_result(uint8_t output[]) override final;

      /**
      * Run the hash's compression function over a set of blocks
      * @param blocks the input
      * @param block_n the number of blocks
      */
      virtual void compress_n(const uint8_t blocks[], size_t block_n) = 0;

      void clear() override;

      /**
      * Copy the output to the buffer
      * @param buffer to put the output into
      */
      virtual void copy_out(uint8_t buffer[]) = 0;

      /**
      * Write the count, if used, to this spot
      * @param out where to write the counter to
      */
      virtual void write_count(uint8_t out[]);
   private:
      const uint8_t m_pad_char;
      const uint8_t m_counter_size;
      const uint8_t m_block_bits;
      const bool m_count_big_endian;

      uint64_t m_count;
      secure_vector<uint8_t> m_buffer;
      size_t m_position;
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(md5.h)

namespace Botan {

/**
* MD5
*/
class BOTAN_PUBLIC_API(2,0) MD5 final : public MDx_HashFunction
   {
   public:
      std::string name() const override { return "MD5"; }
      size_t output_length() const override { return 16; }
      HashFunction* clone() const override { return new MD5; }
      std::unique_ptr<HashFunction> copy_state() const override;

      void clear() override;

      MD5() : MDx_HashFunction(64, false, true), m_M(16), m_digest(4)
         { clear(); }

   private:
      void compress_n(const uint8_t[], size_t blocks) override;
      void copy_out(uint8_t[]) override;

      /**
      * The message buffer
      */
      secure_vector<uint32_t> m_M;

      /**
      * The digest value
      */
      secure_vector<uint32_t> m_digest;
   };

}

namespace Botan {

class HashFunction;

/**
* MGF1 from PKCS #1 v2.0
* @param hash hash function to use
* @param in input buffer
* @param in_len size of the input buffer in bytes
* @param out output buffer
* @param out_len size of the output buffer in bytes
*/
void BOTAN_PUBLIC_API(2,0) mgf1_mask(HashFunction& hash,
                         const uint8_t in[], size_t in_len,
                         uint8_t out[], size_t out_len);

}
BOTAN_FUTURE_INTERNAL_HEADER(monty.h)

namespace Botan {

class Modular_Reducer;

class Montgomery_Params;

/**
* The Montgomery representation of an integer
*/
class BOTAN_UNSTABLE_API Montgomery_Int final
   {
   public:
      /**
      * Create a zero-initialized Montgomery_Int
      */
      Montgomery_Int(std::shared_ptr<const Montgomery_Params> params) : m_params(params) {}

      /**
      * Create a Montgomery_Int
      */
      Montgomery_Int(std::shared_ptr<const Montgomery_Params> params,
                     const BigInt& v,
                     bool redc_needed = true);

      /**
      * Create a Montgomery_Int
      */
      Montgomery_Int(std::shared_ptr<const Montgomery_Params> params,
                     const uint8_t bits[], size_t len,
                     bool redc_needed = true);

      /**
      * Create a Montgomery_Int
      */
      Montgomery_Int(std::shared_ptr<const Montgomery_Params> params,
                     const word words[], size_t len,
                     bool redc_needed = true);

      bool operator==(const Montgomery_Int& other) const;
      bool operator!=(const Montgomery_Int& other) const { return (m_v != other.m_v); }

      std::vector<uint8_t> serialize() const;

      size_t size() const;
      bool is_one() const;
      bool is_zero() const;

      void fix_size();

      /**
      * Return the value to normal mod-p space
      */
      BigInt value() const;

      /**
      * Return the Montgomery representation
      */
      const BigInt& repr() const { return m_v; }

      Montgomery_Int operator+(const Montgomery_Int& other) const;

      Montgomery_Int operator-(const Montgomery_Int& other) const;

      Montgomery_Int& operator+=(const Montgomery_Int& other);

      Montgomery_Int& operator-=(const Montgomery_Int& other);

      Montgomery_Int operator*(const Montgomery_Int& other) const;

      Montgomery_Int& operator*=(const Montgomery_Int& other);

      Montgomery_Int& operator*=(const secure_vector<word>& other);

      Montgomery_Int& add(const Montgomery_Int& other,
                          secure_vector<word>& ws);

      Montgomery_Int& sub(const Montgomery_Int& other,
                          secure_vector<word>& ws);

      Montgomery_Int mul(const Montgomery_Int& other,
                         secure_vector<word>& ws) const;

      Montgomery_Int& mul_by(const Montgomery_Int& other,
                             secure_vector<word>& ws);

      Montgomery_Int& mul_by(const secure_vector<word>& other,
                             secure_vector<word>& ws);

      Montgomery_Int square(secure_vector<word>& ws) const;

      Montgomery_Int& square_this(secure_vector<word>& ws);

      Montgomery_Int& square_this_n_times(secure_vector<word>& ws, size_t n);

      Montgomery_Int multiplicative_inverse() const;

      Montgomery_Int additive_inverse() const;

      Montgomery_Int& mul_by_2(secure_vector<word>& ws);

      Montgomery_Int& mul_by_3(secure_vector<word>& ws);

      Montgomery_Int& mul_by_4(secure_vector<word>& ws);

      Montgomery_Int& mul_by_8(secure_vector<word>& ws);

      void const_time_poison() const { m_v.const_time_poison(); }
      void const_time_unpoison() const { return m_v.const_time_unpoison(); }

   private:
      std::shared_ptr<const Montgomery_Params> m_params;
      BigInt m_v;
   };

/**
* Parameters for Montgomery Reduction
*/
class BOTAN_UNSTABLE_API Montgomery_Params final
   {
   public:
      /**
      * Initialize a set of Montgomery reduction parameters. These values
      * can be shared by all values in a specific Montgomery domain.
      */
      Montgomery_Params(const BigInt& p, const Modular_Reducer& mod_p);

      /**
      * Initialize a set of Montgomery reduction parameters. These values
      * can be shared by all values in a specific Montgomery domain.
      */
      Montgomery_Params(const BigInt& p);

      const BigInt& p() const { return m_p; }
      const BigInt& R1() const { return m_r1; }
      const BigInt& R2() const { return m_r2; }
      const BigInt& R3() const { return m_r3; }

      word p_dash() const { return m_p_dash; }

      size_t p_words() const { return m_p_words; }

      BigInt redc(const BigInt& x,
                  secure_vector<word>& ws) const;

      BigInt mul(const BigInt& x,
                 const BigInt& y,
                 secure_vector<word>& ws) const;

      BigInt mul(const BigInt& x,
                 const secure_vector<word>& y,
                 secure_vector<word>& ws) const;

      void mul_by(BigInt& x,
                  const secure_vector<word>& y,
                  secure_vector<word>& ws) const;

      void mul_by(BigInt& x, const BigInt& y,
                  secure_vector<word>& ws) const;

      BigInt sqr(const BigInt& x,
                 secure_vector<word>& ws) const;

      void square_this(BigInt& x,
                       secure_vector<word>& ws) const;

      BigInt inv_mod_p(const BigInt& x) const;

   private:
      BigInt m_p;
      BigInt m_r1;
      BigInt m_r2;
      BigInt m_r3;
      word m_p_dash;
      size_t m_p_words;
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(mul128.h)

namespace Botan {

#if defined(__SIZEOF_INT128__) && defined(BOTAN_TARGET_CPU_HAS_NATIVE_64BIT)
   #define BOTAN_TARGET_HAS_NATIVE_UINT128

   // Prefer TI mode over __int128 as GCC rejects the latter in pendantic mode
   #if defined(__GNUG__)
     typedef unsigned int uint128_t __attribute__((mode(TI)));
   #else
     typedef unsigned __int128 uint128_t;
   #endif
#endif

}

#if defined(BOTAN_TARGET_HAS_NATIVE_UINT128)

#define BOTAN_FAST_64X64_MUL(a,b,lo,hi)      \
   do {                                      \
      const uint128_t r = static_cast<uint128_t>(a) * b;   \
      *hi = (r >> 64) & 0xFFFFFFFFFFFFFFFF;  \
      *lo = (r      ) & 0xFFFFFFFFFFFFFFFF;  \
   } while(0)

#elif defined(BOTAN_BUILD_COMPILER_IS_MSVC) && defined(BOTAN_TARGET_CPU_HAS_NATIVE_64BIT)

#include <intrin.h>
#pragma intrinsic(_umul128)

#define BOTAN_FAST_64X64_MUL(a,b,lo,hi) \
   do { *lo = _umul128(a, b, hi); } while(0)

#elif defined(BOTAN_USE_GCC_INLINE_ASM)

#if defined(BOTAN_TARGET_ARCH_IS_X86_64)

#define BOTAN_FAST_64X64_MUL(a,b,lo,hi) do {                           \
   asm("mulq %3" : "=d" (*hi), "=a" (*lo) : "a" (a), "rm" (b) : "cc"); \
   } while(0)

#elif defined(BOTAN_TARGET_ARCH_IS_ALPHA)

#define BOTAN_FAST_64X64_MUL(a,b,lo,hi) do {              \
   asm("umulh %1,%2,%0" : "=r" (*hi) : "r" (a), "r" (b)); \
   *lo = a * b;                                           \
} while(0)

#elif defined(BOTAN_TARGET_ARCH_IS_IA64)

#define BOTAN_FAST_64X64_MUL(a,b,lo,hi) do {                \
   asm("xmpy.hu %0=%1,%2" : "=f" (*hi) : "f" (a), "f" (b)); \
   *lo = a * b;                                             \
} while(0)

#elif defined(BOTAN_TARGET_ARCH_IS_PPC64)

#define BOTAN_FAST_64X64_MUL(a,b,lo,hi) do {                      \
   asm("mulhdu %0,%1,%2" : "=r" (*hi) : "r" (a), "r" (b) : "cc"); \
   *lo = a * b;                                                   \
} while(0)

#endif

#endif

namespace Botan {

/**
* Perform a 64x64->128 bit multiplication
*/
inline void mul64x64_128(uint64_t a, uint64_t b, uint64_t* lo, uint64_t* hi)
   {
#if defined(BOTAN_FAST_64X64_MUL)
   BOTAN_FAST_64X64_MUL(a, b, lo, hi);
#else

   /*
   * Do a 64x64->128 multiply using four 32x32->64 multiplies plus
   * some adds and shifts. Last resort for CPUs like UltraSPARC (with
   * 64-bit registers/ALU, but no 64x64->128 multiply) or 32-bit CPUs.
   */
   const size_t HWORD_BITS = 32;
   const uint32_t HWORD_MASK = 0xFFFFFFFF;

   const uint32_t a_hi = (a >> HWORD_BITS);
   const uint32_t a_lo = (a  & HWORD_MASK);
   const uint32_t b_hi = (b >> HWORD_BITS);
   const uint32_t b_lo = (b  & HWORD_MASK);

   uint64_t x0 = static_cast<uint64_t>(a_hi) * b_hi;
   uint64_t x1 = static_cast<uint64_t>(a_lo) * b_hi;
   uint64_t x2 = static_cast<uint64_t>(a_hi) * b_lo;
   uint64_t x3 = static_cast<uint64_t>(a_lo) * b_lo;

   // this cannot overflow as (2^32-1)^2 + 2^32-1 < 2^64-1
   x2 += x3 >> HWORD_BITS;

   // this one can overflow
   x2 += x1;

   // propagate the carry if any
   x0 += static_cast<uint64_t>(static_cast<bool>(x2 < x1)) << HWORD_BITS;

   *hi = x0 + (x2 >> HWORD_BITS);
   *lo  = ((x2 & HWORD_MASK) << HWORD_BITS) + (x3 & HWORD_MASK);
#endif
   }

}

namespace Botan {

class Certificate_Store;

namespace OCSP {

class BOTAN_PUBLIC_API(2,0) CertID final : public ASN1_Object
   {
   public:
      CertID() = default;

      CertID(const X509_Certificate& issuer,
             const BigInt& subject_serial);

      bool is_id_for(const X509_Certificate& issuer,
                     const X509_Certificate& subject) const;

      void encode_into(class DER_Encoder& to) const override;

      void decode_from(class BER_Decoder& from) override;

      const std::vector<uint8_t>& issuer_key_hash() const { return m_issuer_key_hash; }

   private:
      AlgorithmIdentifier m_hash_id;
      std::vector<uint8_t> m_issuer_dn_hash;
      std::vector<uint8_t> m_issuer_key_hash;
      BigInt m_subject_serial;
   };

class BOTAN_PUBLIC_API(2,0) SingleResponse final : public ASN1_Object
   {
   public:
      const CertID& certid() const { return m_certid; }

      size_t cert_status() const { return m_cert_status; }

      X509_Time this_update() const { return m_thisupdate; }

      X509_Time next_update() const { return m_nextupdate; }

      void encode_into(class DER_Encoder& to) const override;

      void decode_from(class BER_Decoder& from) override;
   private:
      CertID m_certid;
      size_t m_cert_status = 2; // unknown
      X509_Time m_thisupdate;
      X509_Time m_nextupdate;
   };

/**
* An OCSP request.
*/
class BOTAN_PUBLIC_API(2,0) Request final
   {
   public:
      /**
      * Create an OCSP request.
      * @param issuer_cert issuer certificate
      * @param subject_cert subject certificate
      */
      Request(const X509_Certificate& issuer_cert,
              const X509_Certificate& subject_cert);

      Request(const X509_Certificate& issuer_cert,
              const BigInt& subject_serial);

      /**
      * @return BER-encoded OCSP request
      */
      std::vector<uint8_t> BER_encode() const;

      /**
      * @return Base64-encoded OCSP request
      */
      std::string base64_encode() const;

      /**
      * @return issuer certificate
      */
      const X509_Certificate& issuer() const { return m_issuer; }

      /**
      * @return subject certificate
      */
      const X509_Certificate& subject() const { throw Not_Implemented("Method have been deprecated"); }

      const std::vector<uint8_t>& issuer_key_hash() const
         { return m_certid.issuer_key_hash(); }
   private:
      X509_Certificate m_issuer;
      CertID m_certid;
   };

/**
* OCSP response status.
*
* see https://tools.ietf.org/html/rfc6960#section-4.2.1
*/
enum class Response_Status_Code {
   Successful = 0,
   Malformed_Request = 1,
   Internal_Error = 2,
   Try_Later = 3,
   Sig_Required = 5,
   Unauthorized = 6
};

/**
* OCSP response.
*
* Note this class is only usable as an OCSP client
*/
class BOTAN_PUBLIC_API(2,0) Response final
   {
   public:
      /**
      * Creates an empty OCSP response.
      */
      Response() = default;

      /**
      * Create a fake OCSP response from a given status code.
      * @param status the status code the check functions will return
      */
      Response(Certificate_Status_Code status);

      /**
      * Parses an OCSP response.
      * @param response_bits response bits received
      */
      Response(const std::vector<uint8_t>& response_bits) :
         Response(response_bits.data(), response_bits.size())
         {}

      /**
      * Parses an OCSP response.
      * @param response_bits response bits received
      * @param response_bits_len length of response in bytes
      */
      Response(const uint8_t response_bits[],
               size_t response_bits_len);

      /**
      * Check signature and return status
      * The optional cert_path is the (already validated!) certificate path of
      * the end entity which is being inquired about
      * @param trust_roots list of certstores containing trusted roots
      * @param cert_path optionally, the (already verified!) certificate path for the certificate
      * this is an OCSP response for. This is necessary to find the correct intermediate CA in
      * some cases.
      */
      Certificate_Status_Code check_signature(const std::vector<Certificate_Store*>& trust_roots,
                                              const std::vector<std::shared_ptr<const X509_Certificate>>& cert_path = {}) const;

      /**
      * Verify that issuer's key signed this response
      * @param issuer certificate of issuer
      * @return if signature valid OCSP_SIGNATURE_OK else an error code
      */
      Certificate_Status_Code verify_signature(const X509_Certificate& issuer) const;

      /**
      * @return the status of the response
      */
      Response_Status_Code status() const { return m_status; }

      /**
      * @return the time this OCSP response was supposedly produced at
      */
      const X509_Time& produced_at() const { return m_produced_at; }

      /**
      * @return DN of signer, if provided in response (may be empty)
      */
      const X509_DN& signer_name() const { return m_signer_name; }

      /**
      * @return key hash, if provided in response (may be empty)
      */
      const std::vector<uint8_t>& signer_key_hash() const { return m_key_hash; }

      const std::vector<uint8_t>& raw_bits() const { return m_response_bits; }

      /**
       * Searches the OCSP response for issuer and subject certificate.
       * @param issuer issuer certificate
       * @param subject subject certificate
       * @param ref_time the reference time
       * @param max_age the maximum age the response should be considered valid
       *                if next_update is not set
       * @return OCSP status code, possible values:
       *         CERT_IS_REVOKED,
       *         OCSP_NOT_YET_VALID,
       *         OCSP_HAS_EXPIRED,
       *         OCSP_IS_TOO_OLD,
       *         OCSP_RESPONSE_GOOD,
       *         OCSP_BAD_STATUS,
       *         OCSP_CERT_NOT_LISTED
       */
      Certificate_Status_Code status_for(const X509_Certificate& issuer,
                                         const X509_Certificate& subject,
                                         std::chrono::system_clock::time_point ref_time = std::chrono::system_clock::now(),
                                         std::chrono::seconds max_age = std::chrono::seconds::zero()) const;

      /**
       * @return the certificate chain, if provided in response
       */
      const std::vector<X509_Certificate> &certificates() const { return  m_certs; }

   private:
      Response_Status_Code m_status;
      std::vector<uint8_t> m_response_bits;
      X509_Time m_produced_at;
      X509_DN m_signer_name;
      std::vector<uint8_t> m_key_hash;
      std::vector<uint8_t> m_tbs_bits;
      AlgorithmIdentifier m_sig_algo;
      std::vector<uint8_t> m_signature;
      std::vector<X509_Certificate> m_certs;

      std::vector<SingleResponse> m_responses;

      Certificate_Status_Code m_dummy_response_status;
   };

#if defined(BOTAN_HAS_HTTP_UTIL)

/**
* Makes an online OCSP request via HTTP and returns the OCSP response.
* @param issuer issuer certificate
* @param subject_serial the subject's serial number
* @param ocsp_responder the OCSP responder to query
* @param trusted_roots trusted roots for the OCSP response
* @param timeout a timeout on the HTTP request
* @return OCSP response
*/
BOTAN_PUBLIC_API(2,1)
Response online_check(const X509_Certificate& issuer,
                      const BigInt& subject_serial,
                      const std::string& ocsp_responder,
                      Certificate_Store* trusted_roots,
                      std::chrono::milliseconds timeout = std::chrono::milliseconds(3000));

/**
* Makes an online OCSP request via HTTP and returns the OCSP response.
* @param issuer issuer certificate
* @param subject subject certificate
* @param trusted_roots trusted roots for the OCSP response
* @param timeout a timeout on the HTTP request
* @return OCSP response
*/
BOTAN_PUBLIC_API(2,0)
Response online_check(const X509_Certificate& issuer,
                      const X509_Certificate& subject,
                      Certificate_Store* trusted_roots,
                      std::chrono::milliseconds timeout = std::chrono::milliseconds(3000));

#endif

}

}

namespace Botan {

namespace OIDS {

/**
* Register an OID to string mapping.
* @param oid the oid to register
* @param name the name to be associated with the oid
*/
BOTAN_UNSTABLE_API void add_oid(const OID& oid, const std::string& name);

BOTAN_UNSTABLE_API void add_oid2str(const OID& oid, const std::string& name);
BOTAN_UNSTABLE_API void add_str2oid(const OID& oid, const std::string& name);

BOTAN_UNSTABLE_API void add_oidstr(const char* oidstr, const char* name);

std::unordered_map<std::string, std::string> load_oid2str_map();
std::unordered_map<std::string, OID> load_str2oid_map();

/**
* Resolve an OID
* @param oid the OID to look up
* @return name associated with this OID, or an empty string
*/
BOTAN_UNSTABLE_API std::string oid2str_or_empty(const OID& oid);

/**
* Find the OID to a name. The lookup will be performed in the
* general OID section of the configuration.
* @param name the name to resolve
* @return OID associated with the specified name
*/
BOTAN_UNSTABLE_API OID str2oid_or_empty(const std::string& name);

BOTAN_UNSTABLE_API std::string oid2str_or_throw(const OID& oid);

/**
* See if an OID exists in the internal table.
* @param oid the oid to check for
* @return true if the oid is registered
*/
BOTAN_UNSTABLE_API bool BOTAN_DEPRECATED("Just lookup the value instead") have_oid(const std::string& oid);

/**
* Tests whether the specified OID stands for the specified name.
* @param oid the OID to check
* @param name the name to check
* @return true if the specified OID stands for the specified name
*/
inline bool BOTAN_DEPRECATED("Use oid == OID::from_string(name)") name_of(const OID& oid, const std::string& name)
   {
   return (oid == str2oid_or_empty(name));
   }

/**
* Prefer oid2str_or_empty
*/
inline std::string lookup(const OID& oid)
   {
   return oid2str_or_empty(oid);
   }

/**
* Prefer str2oid_or_empty
*/
inline OID lookup(const std::string& name)
   {
   return str2oid_or_empty(name);
   }

inline std::string BOTAN_DEPRECATED("Use oid2str_or_empty") oid2str(const OID& oid)
   {
   return oid2str_or_empty(oid);
   }

inline OID BOTAN_DEPRECATED("Use str2oid_or_empty") str2oid(const std::string& name)
   {
   return str2oid_or_empty(name);
   }

}

}


BOTAN_FUTURE_INTERNAL_HEADER(parsing.h)

namespace Botan {

/**
* Parse a SCAN-style algorithm name
* @param scan_name the name
* @return the name components
*/
BOTAN_PUBLIC_API(2,0) std::vector<std::string>
parse_algorithm_name(const std::string& scan_name);

/**
* Split a string
* @param str the input string
* @param delim the delimitor
* @return string split by delim
*/
BOTAN_PUBLIC_API(2,0) std::vector<std::string> split_on(
   const std::string& str, char delim);

/**
* Split a string on a character predicate
* @param str the input string
* @param pred the predicate
*
* This function will likely be removed in a future release
*/
BOTAN_PUBLIC_API(2,0) std::vector<std::string>
split_on_pred(const std::string& str,
              std::function<bool (char)> pred);

/**
* Erase characters from a string
*/
BOTAN_PUBLIC_API(2,0)
BOTAN_DEPRECATED("Unused")
std::string erase_chars(const std::string& str, const std::set<char>& chars);

/**
* Replace a character in a string
* @param str the input string
* @param from_char the character to replace
* @param to_char the character to replace it with
* @return str with all instances of from_char replaced by to_char
*/
BOTAN_PUBLIC_API(2,0)
BOTAN_DEPRECATED("Unused")
std::string replace_char(const std::string& str,
                         char from_char,
                         char to_char);

/**
* Replace a character in a string
* @param str the input string
* @param from_chars the characters to replace
* @param to_char the character to replace it with
* @return str with all instances of from_chars replaced by to_char
*/
BOTAN_PUBLIC_API(2,0)
BOTAN_DEPRECATED("Unused")
std::string replace_chars(const std::string& str,
                          const std::set<char>& from_chars,
                          char to_char);

/**
* Join a string
* @param strs strings to join
* @param delim the delimitor
* @return string joined by delim
*/
BOTAN_PUBLIC_API(2,0)
std::string string_join(const std::vector<std::string>& strs,
                        char delim);

/**
* Parse an ASN.1 OID
* @param oid the OID in string form
* @return OID components
*/
BOTAN_PUBLIC_API(2,0) std::vector<uint32_t>
BOTAN_DEPRECATED("Use OID::from_string(oid).get_components()") parse_asn1_oid(const std::string& oid);

/**
* Compare two names using the X.509 comparison algorithm
* @param name1 the first name
* @param name2 the second name
* @return true if name1 is the same as name2 by the X.509 comparison rules
*/
BOTAN_PUBLIC_API(2,0)
bool x500_name_cmp(const std::string& name1,
                   const std::string& name2);

/**
* Convert a string to a number
* @param str the string to convert
* @return number value of the string
*/
BOTAN_PUBLIC_API(2,0) uint32_t to_u32bit(const std::string& str);

/**
* Convert a string to a number
* @param str the string to convert
* @return number value of the string
*/
BOTAN_PUBLIC_API(2,3) uint16_t to_uint16(const std::string& str);

/**
* Convert a time specification to a number
* @param timespec the time specification
* @return number of seconds represented by timespec
*/
BOTAN_PUBLIC_API(2,0) uint32_t BOTAN_DEPRECATED("Not used anymore")
timespec_to_u32bit(const std::string& timespec);

/**
* Convert a string representation of an IPv4 address to a number
* @param ip_str the string representation
* @return integer IPv4 address
*/
BOTAN_PUBLIC_API(2,0) uint32_t string_to_ipv4(const std::string& ip_str);

/**
* Convert an IPv4 address to a string
* @param ip_addr the IPv4 address to convert
* @return string representation of the IPv4 address
*/
BOTAN_PUBLIC_API(2,0) std::string ipv4_to_string(uint32_t ip_addr);

std::map<std::string, std::string> BOTAN_PUBLIC_API(2,0) read_cfg(std::istream& is);

/**
* Accepts key value pairs deliminated by commas:
*
* "" (returns empty map)
* "K=V" (returns map {'K': 'V'})
* "K1=V1,K2=V2"
* "K1=V1,K2=V2,K3=V3"
* "K1=V1,K2=V2,K3=a_value\,with\,commas_and_\=equals"
*
* Values may be empty, keys must be non-empty and unique. Duplicate
* keys cause an exception.
*
* Within both key and value, comma and equals can be escaped with
* backslash. Backslash can also be escaped.
*/
std::map<std::string, std::string> BOTAN_PUBLIC_API(2,8) read_kv(const std::string& kv);

std::string BOTAN_PUBLIC_API(2,0) clean_ws(const std::string& s);

/**
* Check if the given hostname is a match for the specified wildcard
*/
bool BOTAN_PUBLIC_API(2,0) host_wildcard_match(const std::string& wildcard,
                                               const std::string& host);


}

namespace Botan {

class DataSource;

namespace PEM_Code {

/**
* Encode some binary data in PEM format
* @param data binary data to encode
* @param data_len length of binary data in bytes
* @param label PEM label put after BEGIN and END
* @param line_width after this many characters, a new line is inserted
*/
BOTAN_PUBLIC_API(2,0) std::string encode(const uint8_t data[],
                                         size_t data_len,
                                         const std::string& label,
                                         size_t line_width = 64);

/**
* Encode some binary data in PEM format
* @param data binary data to encode
* @param label PEM label
* @param line_width after this many characters, a new line is inserted
*/
template<typename Alloc>
std::string encode(const std::vector<uint8_t, Alloc>& data,
                   const std::string& label,
                   size_t line_width = 64)
   {
   return encode(data.data(), data.size(), label, line_width);
   }

/**
* Decode PEM data
* @param pem a datasource containing PEM encoded data
* @param label is set to the PEM label found for later inspection
*/
BOTAN_PUBLIC_API(2,0) secure_vector<uint8_t> decode(DataSource& pem,
                                                    std::string& label);

/**
* Decode PEM data
* @param pem a string containing PEM encoded data
* @param label is set to the PEM label found for later inspection
*/
BOTAN_PUBLIC_API(2,0) secure_vector<uint8_t> decode(const std::string& pem,
                                                    std::string& label);

/**
* Decode PEM data
* @param pem a datasource containing PEM encoded data
* @param label is what we expect the label to be
*/
BOTAN_PUBLIC_API(2,0)
secure_vector<uint8_t> decode_check_label(DataSource& pem,
                                          const std::string& label);

/**
* Decode PEM data
* @param pem a string containing PEM encoded data
* @param label is what we expect the label to be
*/
BOTAN_PUBLIC_API(2,0)
secure_vector<uint8_t> decode_check_label(const std::string& pem,
                                          const std::string& label);

/**
* Heuristic test for PEM data.
*/
BOTAN_PUBLIC_API(2,0) bool matches(DataSource& source,
                                   const std::string& extra = "",
                                   size_t search_range = 4096);

}

}

namespace Botan {

BOTAN_PUBLIC_API(2,0) std::unique_ptr<Public_Key>
load_public_key(const AlgorithmIdentifier& alg_id,
                const std::vector<uint8_t>& key_bits);

BOTAN_PUBLIC_API(2,0) std::unique_ptr<Private_Key>
load_private_key(const AlgorithmIdentifier& alg_id,
                 const secure_vector<uint8_t>& key_bits);

/**
* Create a new key
* For ECC keys, algo_params specifies EC group (eg, "secp256r1")
* For DH/DSA/ElGamal keys, algo_params is DL group (eg, "modp/ietf/2048")
* For RSA, algo_params is integer keylength
* For McEliece, algo_params is n,t
* If algo_params is left empty, suitable default parameters are chosen.
*/
BOTAN_PUBLIC_API(2,0) std::unique_ptr<Private_Key>
create_private_key(const std::string& algo_name,
                   RandomNumberGenerator& rng,
                   const std::string& algo_params = "",
                   const std::string& provider = "");

BOTAN_PUBLIC_API(2,2)
std::vector<std::string>
probe_provider_private_key(const std::string& algo_name,
                           const std::vector<std::string> possible);

}
/**
* Ordinary applications should never need to include or use this
* header. It is exposed only for specialized applications which want
* to implement new versions of public key crypto without merging them
* as changes to the library. One actual example of such usage is an
* application which creates RSA signatures using a custom TPM library.
* Unless you're doing something like that, you don't need anything
* here. Instead use pubkey.h which wraps these types safely and
* provides a stable application-oriented API.
*/


namespace Botan {

class RandomNumberGenerator;
class EME;
class KDF;
class EMSA;

namespace PK_Ops {

/**
* Public key encryption interface
*/
class BOTAN_PUBLIC_API(2,0) Encryption
   {
   public:
      virtual secure_vector<uint8_t> encrypt(const uint8_t msg[],
                                          size_t msg_len,
                                          RandomNumberGenerator& rng) = 0;

      virtual size_t max_input_bits() const = 0;

      virtual size_t ciphertext_length(size_t ptext_len) const = 0;

      virtual ~Encryption() = default;
   };

/**
* Public key decryption interface
*/
class BOTAN_PUBLIC_API(2,0) Decryption
   {
   public:
      virtual secure_vector<uint8_t> decrypt(uint8_t& valid_mask,
                                          const uint8_t ciphertext[],
                                          size_t ciphertext_len) = 0;

      virtual size_t plaintext_length(size_t ctext_len) const = 0;

      virtual ~Decryption() = default;
   };

/**
* Public key signature verification interface
*/
class BOTAN_PUBLIC_API(2,0) Verification
   {
   public:
      /*
      * Add more data to the message currently being signed
      * @param msg the message
      * @param msg_len the length of msg in bytes
      */
      virtual void update(const uint8_t msg[], size_t msg_len) = 0;

      /*
      * Perform a verification operation
      * @param rng a random number generator
      */
      virtual bool is_valid_signature(const uint8_t sig[], size_t sig_len) = 0;

      virtual ~Verification() = default;
   };

/**
* Public key signature creation interface
*/
class BOTAN_PUBLIC_API(2,0) Signature
   {
   public:
      /*
      * Add more data to the message currently being signed
      * @param msg the message
      * @param msg_len the length of msg in bytes
      */
      virtual void update(const uint8_t msg[], size_t msg_len) = 0;

      /*
      * Perform a signature operation
      * @param rng a random number generator
      */
      virtual secure_vector<uint8_t> sign(RandomNumberGenerator& rng) = 0;

      /*
      * Return an upper bound on the length of the output signature
      */
      virtual size_t signature_length() const = 0;

      virtual ~Signature() = default;
   };

/**
* A generic key agreement operation (eg DH or ECDH)
*/
class BOTAN_PUBLIC_API(2,0) Key_Agreement
   {
   public:
      virtual secure_vector<uint8_t> agree(size_t key_len,
                                           const uint8_t other_key[], size_t other_key_len,
                                           const uint8_t salt[], size_t salt_len) = 0;

      virtual size_t agreed_value_size() const = 0;

      virtual ~Key_Agreement() = default;
   };

/**
* KEM (key encapsulation)
*/
class BOTAN_PUBLIC_API(2,0) KEM_Encryption
   {
   public:
      virtual void kem_encrypt(secure_vector<uint8_t>& out_encapsulated_key,
                               secure_vector<uint8_t>& out_shared_key,
                               size_t desired_shared_key_len,
                               Botan::RandomNumberGenerator& rng,
                               const uint8_t salt[],
                               size_t salt_len) = 0;

      virtual ~KEM_Encryption() = default;
   };

class BOTAN_PUBLIC_API(2,0) KEM_Decryption
   {
   public:
      virtual secure_vector<uint8_t> kem_decrypt(const uint8_t encap_key[],
                                              size_t len,
                                              size_t desired_shared_key_len,
                                              const uint8_t salt[],
                                              size_t salt_len) = 0;

      virtual ~KEM_Decryption() = default;
   };

}

}

namespace Botan {

struct PKCS10_Data;

class Private_Key;
class Extensions;
class X509_DN;
class AlternativeName;

/**
* PKCS #10 Certificate Request.
*/
class BOTAN_PUBLIC_API(2,0) PKCS10_Request final : public X509_Object
   {
   public:
      /**
      * Get the subject public key.
      * @return subject public key
      */
      Public_Key* subject_public_key() const;

      /**
      * Get the raw DER encoded public key.
      * @return raw DER encoded public key
      */
      const std::vector<uint8_t>& raw_public_key() const;

      /**
      * Get the subject DN.
      * @return subject DN
      */
      const X509_DN& subject_dn() const;

      /**
      * Get the subject alternative name.
      * @return subject alternative name.
      */
      const AlternativeName& subject_alt_name() const;

      /**
      * Get the key constraints for the key associated with this
      * PKCS#10 object.
      * @return key constraints
      */
      Key_Constraints constraints() const;

      /**
      * Get the extendend key constraints (if any).
      * @return extended key constraints
      */
      std::vector<OID> ex_constraints() const;

      /**
      * Find out whether this is a CA request.
      * @result true if it is a CA request, false otherwise.
      */
      bool is_CA() const;

      /**
      * Return the constraint on the path length defined
      * in the BasicConstraints extension.
      * @return path limit
      */
      size_t path_limit() const;

      /**
      * Get the challenge password for this request
      * @return challenge password for this request
      */
      std::string challenge_password() const;

      /**
      * Get the X509v3 extensions.
      * @return X509v3 extensions
      */
      const Extensions& extensions() const;

      /**
      * Create a PKCS#10 Request from a data source.
      * @param source the data source providing the DER encoded request
      */
      explicit PKCS10_Request(DataSource& source);

#if defined(BOTAN_TARGET_OS_HAS_FILESYSTEM)
      /**
      * Create a PKCS#10 Request from a file.
      * @param filename the name of the file containing the DER or PEM
      * encoded request file
      */
      explicit PKCS10_Request(const std::string& filename);
#endif

      /**
      * Create a PKCS#10 Request from binary data.
      * @param vec a std::vector containing the DER value
      */
      explicit PKCS10_Request(const std::vector<uint8_t>& vec);

      /**
      * Create a new PKCS10 certificate request
      * @param key the key that will be included in the certificate request
      * @param subject_dn the DN to be placed in the request
      * @param extensions extensions to include in the request
      * @param hash_fn the hash function to use to create the signature
      * @param rng a random number generator
      * @param padding_scheme if set specifies the padding scheme, otherwise an
      *        algorithm-specific default is used.
      * @param challenge a challenge string to be included in the PKCS10 request,
      *        sometimes used for revocation purposes.
      */
      static PKCS10_Request create(const Private_Key& key,
                                   const X509_DN& subject_dn,
                                   const Extensions& extensions,
                                   const std::string& hash_fn,
                                   RandomNumberGenerator& rng,
                                   const std::string& padding_scheme = "",
                                   const std::string& challenge = "");

   private:
      std::string PEM_label() const override;

      std::vector<std::string> alternate_PEM_labels() const override;

      void force_decode() override;

      const PKCS10_Data& data() const;

      std::shared_ptr<PKCS10_Data> m_data;
   };

}

namespace Botan {

class DataSource;
class RandomNumberGenerator;

/**
* PKCS #8 General Exception
*/
class BOTAN_PUBLIC_API(2,0) PKCS8_Exception final : public Decoding_Error
   {
   public:
      explicit PKCS8_Exception(const std::string& error) :
         Decoding_Error("PKCS #8: " + error) {}
   };

/**
* This namespace contains functions for handling PKCS #8 private keys
*/
namespace PKCS8 {

/**
* BER encode a private key
* @param key the private key to encode
* @return BER encoded key
*/
BOTAN_PUBLIC_API(2,0) secure_vector<uint8_t> BER_encode(const Private_Key& key);

/**
* Get a string containing a PEM encoded private key.
* @param key the key to encode
* @return encoded key
*/
BOTAN_PUBLIC_API(2,0) std::string PEM_encode(const Private_Key& key);

/**
* Encrypt a key using PKCS #8 encryption
* @param key the key to encode
* @param rng the rng to use
* @param pass the password to use for encryption
* @param msec number of milliseconds to run the password derivation
* @param pbe_algo the name of the desired password-based encryption
*        algorithm; if empty ("") a reasonable (portable/secure)
*        default will be chosen.
* @return encrypted key in binary BER form
*/
BOTAN_PUBLIC_API(2,0) std::vector<uint8_t>
BER_encode(const Private_Key& key,
           RandomNumberGenerator& rng,
           const std::string& pass,
           std::chrono::milliseconds msec = std::chrono::milliseconds(300),
           const std::string& pbe_algo = "");

/**
* Get a string containing a PEM encoded private key, encrypting it with a
* password.
* @param key the key to encode
* @param rng the rng to use
* @param pass the password to use for encryption
* @param msec number of milliseconds to run the password derivation
* @param pbe_algo the name of the desired password-based encryption
*        algorithm; if empty ("") a reasonable (portable/secure)
*        default will be chosen.
* @return encrypted key in PEM form
*/
BOTAN_PUBLIC_API(2,0) std::string
PEM_encode(const Private_Key& key,
           RandomNumberGenerator& rng,
           const std::string& pass,
           std::chrono::milliseconds msec = std::chrono::milliseconds(300),
           const std::string& pbe_algo = "");

/**
* Encrypt a key using PKCS #8 encryption and a fixed iteration count
* @param key the key to encode
* @param rng the rng to use
* @param pass the password to use for encryption
* @param pbkdf_iter number of interations to run PBKDF2
* @param cipher if non-empty specifies the cipher to use. CBC and GCM modes
*   are supported, for example "AES-128/CBC", "AES-256/GCM", "Serpent/CBC".
*   If empty a suitable default is chosen.
* @param pbkdf_hash if non-empty specifies the PBKDF hash function to use.
*   For example "SHA-256" or "SHA-384". If empty a suitable default is chosen.
* @return encrypted key in binary BER form
*/
BOTAN_PUBLIC_API(2,1) std::vector<uint8_t>
BER_encode_encrypted_pbkdf_iter(const Private_Key& key,
                                RandomNumberGenerator& rng,
                                const std::string& pass,
                                size_t pbkdf_iter,
                                const std::string& cipher = "",
                                const std::string& pbkdf_hash = "");

/**
* Get a string containing a PEM encoded private key, encrypting it with a
* password.
* @param key the key to encode
* @param rng the rng to use
* @param pass the password to use for encryption
* @param pbkdf_iter number of iterations to run PBKDF
* @param cipher if non-empty specifies the cipher to use. CBC and GCM modes
*   are supported, for example "AES-128/CBC", "AES-256/GCM", "Serpent/CBC".
*   If empty a suitable default is chosen.
* @param pbkdf_hash if non-empty specifies the PBKDF hash function to use.
*   For example "SHA-256" or "SHA-384". If empty a suitable default is chosen.
* @return encrypted key in PEM form
*/
BOTAN_PUBLIC_API(2,1) std::string
PEM_encode_encrypted_pbkdf_iter(const Private_Key& key,
                                RandomNumberGenerator& rng,
                                const std::string& pass,
                                size_t pbkdf_iter,
                                const std::string& cipher = "",
                                const std::string& pbkdf_hash = "");

/**
* Encrypt a key using PKCS #8 encryption and a variable iteration count
* @param key the key to encode
* @param rng the rng to use
* @param pass the password to use for encryption
* @param pbkdf_msec how long to run PBKDF2
* @param pbkdf_iterations if non-null, set to the number of iterations used
* @param cipher if non-empty specifies the cipher to use. CBC and GCM modes
*   are supported, for example "AES-128/CBC", "AES-256/GCM", "Serpent/CBC".
*   If empty a suitable default is chosen.
* @param pbkdf_hash if non-empty specifies the PBKDF hash function to use.
*   For example "SHA-256" or "SHA-384". If empty a suitable default is chosen.
* @return encrypted key in binary BER form
*/
BOTAN_PUBLIC_API(2,1) std::vector<uint8_t>
BER_encode_encrypted_pbkdf_msec(const Private_Key& key,
                                RandomNumberGenerator& rng,
                                const std::string& pass,
                                std::chrono::milliseconds pbkdf_msec,
                                size_t* pbkdf_iterations,
                                const std::string& cipher = "",
                                const std::string& pbkdf_hash = "");

/**
* Get a string containing a PEM encoded private key, encrypting it with a
* password.
* @param key the key to encode
* @param rng the rng to use
* @param pass the password to use for encryption
* @param pbkdf_msec how long in milliseconds to run PBKDF2
* @param pbkdf_iterations (output argument) number of iterations of PBKDF
*  that ended up being used
* @param cipher if non-empty specifies the cipher to use. CBC and GCM modes
*   are supported, for example "AES-128/CBC", "AES-256/GCM", "Serpent/CBC".
*   If empty a suitable default is chosen.
* @param pbkdf_hash if non-empty specifies the PBKDF hash function to use.
*   For example "SHA-256" or "SHA-384". If empty a suitable default is chosen.
* @return encrypted key in PEM form
*/
BOTAN_PUBLIC_API(2,1) std::string
PEM_encode_encrypted_pbkdf_msec(const Private_Key& key,
                                RandomNumberGenerator& rng,
                                const std::string& pass,
                                std::chrono::milliseconds pbkdf_msec,
                                size_t* pbkdf_iterations,
                                const std::string& cipher = "",
                                const std::string& pbkdf_hash = "");

/**
* Load an encrypted key from a data source.
* @param source the data source providing the encoded key
* @param rng ignored for compatibility
* @param get_passphrase a function that returns passphrases
* @return loaded private key object
*/
BOTAN_PUBLIC_API(2,0) Private_Key* load_key(DataSource& source,
                                            RandomNumberGenerator& rng,
                                            std::function<std::string ()> get_passphrase);

/** Load an encrypted key from a data source.
* @param source the data source providing the encoded key
* @param rng ignored for compatibility
* @param pass the passphrase to decrypt the key
* @return loaded private key object
*/
BOTAN_PUBLIC_API(2,0) Private_Key* load_key(DataSource& source,
                                            RandomNumberGenerator& rng,
                                            const std::string& pass);

/** Load an unencrypted key from a data source.
* @param source the data source providing the encoded key
* @param rng ignored for compatibility
* @return loaded private key object
*/
BOTAN_PUBLIC_API(2,0) Private_Key* load_key(DataSource& source,
                                            RandomNumberGenerator& rng);

#if defined(BOTAN_TARGET_OS_HAS_FILESYSTEM)
/**
* Load an encrypted key from a file.
* @param filename the path to the file containing the encoded key
* @param rng ignored for compatibility
* @param get_passphrase a function that returns passphrases
* @return loaded private key object
*/
BOTAN_PUBLIC_API(2,0) Private_Key* load_key(const std::string& filename,
                                            RandomNumberGenerator& rng,
                                            std::function<std::string ()> get_passphrase);

/** Load an encrypted key from a file.
* @param filename the path to the file containing the encoded key
* @param rng ignored for compatibility
* @param pass the passphrase to decrypt the key
* @return loaded private key object
*/
BOTAN_PUBLIC_API(2,0) Private_Key* load_key(const std::string& filename,
                                            RandomNumberGenerator& rng,
                                            const std::string& pass);

/** Load an unencrypted key from a file.
* @param filename the path to the file containing the encoded key
* @param rng ignored for compatibility
* @return loaded private key object
*/
BOTAN_PUBLIC_API(2,0) Private_Key* load_key(const std::string& filename,
                                            RandomNumberGenerator& rng);
#endif

/**
* Copy an existing encoded key object.
* @param key the key to copy
* @param rng ignored for compatibility
* @return new copy of the key
*/
BOTAN_PUBLIC_API(2,0) Private_Key* copy_key(const Private_Key& key,
                                            RandomNumberGenerator& rng);


/**
* Load an encrypted key from a data source.
* @param source the data source providing the encoded key
* @param get_passphrase a function that returns passphrases
* @return loaded private key object
*/
BOTAN_PUBLIC_API(2,3)
std::unique_ptr<Private_Key> load_key(DataSource& source,
                                      std::function<std::string ()> get_passphrase);

/** Load an encrypted key from a data source.
* @param source the data source providing the encoded key
* @param pass the passphrase to decrypt the key
* @return loaded private key object
*/
BOTAN_PUBLIC_API(2,3)
std::unique_ptr<Private_Key> load_key(DataSource& source,
                                      const std::string& pass);

/** Load an unencrypted key from a data source.
* @param source the data source providing the encoded key
* @return loaded private key object
*/
BOTAN_PUBLIC_API(2,3)
std::unique_ptr<Private_Key> load_key(DataSource& source);

/**
* Copy an existing encoded key object.
* @param key the key to copy
* @return new copy of the key
*/
BOTAN_PUBLIC_API(2,3)
std::unique_ptr<Private_Key> copy_key(const Private_Key& key);

}

}

BOTAN_FUTURE_INTERNAL_HEADER(pow_mod.h)

namespace Botan {

class Modular_Exponentiator;

/**
* Modular Exponentiator Proxy
*/
class BOTAN_PUBLIC_API(2,0) Power_Mod
   {
   public:

      enum Usage_Hints {
         NO_HINTS        = 0x0000,

         BASE_IS_FIXED   = 0x0001,
         BASE_IS_SMALL   = 0x0002,
         BASE_IS_LARGE   = 0x0004,
         BASE_IS_2       = 0x0008,

         EXP_IS_FIXED    = 0x0100,
         EXP_IS_SMALL    = 0x0200,
         EXP_IS_LARGE    = 0x0400
      };

      /*
      * Try to choose a good window size
      */
      static size_t window_bits(size_t exp_bits, size_t base_bits,
                                Power_Mod::Usage_Hints hints);

      /**
      * @param modulus the modulus
      * @param hints Passed to set_modulus if modulus > 0
      * @param disable_montgomery_arith Disables use of Montgomery
      * representation. Likely only useful for testing.
      */
      void set_modulus(const BigInt& modulus,
                       Usage_Hints hints = NO_HINTS,
                       bool disable_montgomery_arith = false) const;

      /**
      * Set the base
      */
      void set_base(const BigInt& base) const;

      /**
      * Set the exponent
      */
      void set_exponent(const BigInt& exponent) const;

      /**
      * All three of the above functions must have already been called.
      * @return result of g^x%p
      */
      BigInt execute() const;

      Power_Mod& operator=(const Power_Mod&);

      /**
      * @param modulus Optionally call set_modulus
      * @param hints Passed to set_modulus if modulus > 0
      * @param disable_montgomery_arith Disables use of Montgomery
      * representation. Likely only useful for testing.
      */
      Power_Mod(const BigInt& modulus = 0,
                Usage_Hints hints = NO_HINTS,
                bool disable_montgomery_arith = false);
      Power_Mod(const Power_Mod&);
      virtual ~Power_Mod();
   private:
      mutable std::unique_ptr<Modular_Exponentiator> m_core;
   };

/**
* Fixed Exponent Modular Exponentiator Proxy
*/
class BOTAN_PUBLIC_API(2,0) Fixed_Exponent_Power_Mod final : public Power_Mod
   {
   public:
      BigInt operator()(const BigInt& b) const
         { set_base(b); return execute(); }

      Fixed_Exponent_Power_Mod() = default;

      Fixed_Exponent_Power_Mod(const BigInt& exponent,
                               const BigInt& modulus,
                               Usage_Hints hints = NO_HINTS);
   };

/**
* Fixed Base Modular Exponentiator Proxy
*/
class BOTAN_PUBLIC_API(2,0) Fixed_Base_Power_Mod final : public Power_Mod
   {
   public:
      BigInt operator()(const BigInt& e) const
         { set_exponent(e); return execute(); }

      Fixed_Base_Power_Mod() = default;

      Fixed_Base_Power_Mod(const BigInt& base,
                           const BigInt& modulus,
                           Usage_Hints hints = NO_HINTS);
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(prf_tls.h)

namespace Botan {

/**
* PRF used in TLS 1.0/1.1
*/
class BOTAN_PUBLIC_API(2,0) TLS_PRF final : public KDF
   {
   public:
      std::string name() const override { return "TLS-PRF"; }

      KDF* clone() const override { return new TLS_PRF; }

      size_t kdf(uint8_t key[], size_t key_len,
                 const uint8_t secret[], size_t secret_len,
                 const uint8_t salt[], size_t salt_len,
                 const uint8_t label[], size_t label_len) const override;

      TLS_PRF(std::unique_ptr<MessageAuthenticationCode> hmac_md5,
              std::unique_ptr<MessageAuthenticationCode> hmac_sha1) :
         m_hmac_md5(std::move(hmac_md5)),
         m_hmac_sha1(std::move(hmac_sha1))
         {}

      TLS_PRF();
   private:
      std::unique_ptr<MessageAuthenticationCode> m_hmac_md5;
      std::unique_ptr<MessageAuthenticationCode> m_hmac_sha1;
   };

/**
* PRF used in TLS 1.2
*/
class BOTAN_PUBLIC_API(2,0) TLS_12_PRF final : public KDF
   {
   public:
      std::string name() const override { return "TLS-12-PRF(" + m_mac->name() + ")"; }

      KDF* clone() const override { return new TLS_12_PRF(m_mac->clone()); }

      size_t kdf(uint8_t key[], size_t key_len,
                 const uint8_t secret[], size_t secret_len,
                 const uint8_t salt[], size_t salt_len,
                 const uint8_t label[], size_t label_len) const override;

      /**
      * @param mac MAC algorithm to use
      */
      explicit TLS_12_PRF(MessageAuthenticationCode* mac) : m_mac(mac) {}
   private:
      std::unique_ptr<MessageAuthenticationCode> m_mac;
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(pssr.h)

namespace Botan {

/**
* PSSR (called EMSA4 in IEEE 1363 and in old versions of the library)
*/
class BOTAN_PUBLIC_API(2,0) PSSR final : public EMSA
   {
   public:

      /**
      * @param hash the hash function to use
      */
      explicit PSSR(HashFunction* hash);

      /**
      * @param hash the hash function to use
      * @param salt_size the size of the salt to use in bytes
      */
      PSSR(HashFunction* hash, size_t salt_size);

      EMSA* clone() override;

      std::string name() const override;

      AlgorithmIdentifier config_for_x509(const Private_Key& key,
                                          const std::string& cert_hash_name) const override;
   private:
      void update(const uint8_t input[], size_t length) override;

      secure_vector<uint8_t> raw_data() override;

      secure_vector<uint8_t> encoding_of(const secure_vector<uint8_t>& msg,
                                      size_t output_bits,
                                      RandomNumberGenerator& rng) override;

      bool verify(const secure_vector<uint8_t>& coded,
                  const secure_vector<uint8_t>& raw,
                  size_t key_bits) override;

      std::unique_ptr<HashFunction> m_hash;
      size_t m_salt_size;
      bool m_required_salt_len;
   };

/**
* PSSR_Raw
* This accepts a pre-hashed buffer
*/
class BOTAN_PUBLIC_API(2,3) PSSR_Raw final : public EMSA
   {
   public:

      /**
      * @param hash the hash function to use
      */
      explicit PSSR_Raw(HashFunction* hash);

      /**
      * @param hash the hash function to use
      * @param salt_size the size of the salt to use in bytes
      */
      PSSR_Raw(HashFunction* hash, size_t salt_size);

      EMSA* clone() override;

      std::string name() const override;
   private:
      void update(const uint8_t input[], size_t length) override;

      secure_vector<uint8_t> raw_data() override;

      secure_vector<uint8_t> encoding_of(const secure_vector<uint8_t>& msg,
                                         size_t output_bits,
                                         RandomNumberGenerator& rng) override;

      bool verify(const secure_vector<uint8_t>& coded,
                  const secure_vector<uint8_t>& raw,
                  size_t key_bits) override;

      std::unique_ptr<HashFunction> m_hash;
      secure_vector<uint8_t> m_msg;
      size_t m_salt_size;
      bool m_required_salt_len;
   };

}

#if defined(BOTAN_HAS_SYSTEM_RNG)

namespace Botan {

/**
* Return a shared reference to a global PRNG instance provided by the
* operating system. For instance might be instantiated by /dev/urandom
* or CryptGenRandom.
*/
BOTAN_PUBLIC_API(2,0) RandomNumberGenerator& system_rng();

/*
* Instantiable reference to the system RNG.
*/
class BOTAN_PUBLIC_API(2,0) System_RNG final : public RandomNumberGenerator
   {
   public:
      std::string name() const override { return system_rng().name(); }

      void randomize(uint8_t out[], size_t len) override { system_rng().randomize(out, len); }

      void add_entropy(const uint8_t in[], size_t length) override { system_rng().add_entropy(in, length); }

      bool is_seeded() const override { return system_rng().is_seeded(); }

      bool accepts_input() const override { return system_rng().accepts_input(); }

      void clear() override { system_rng().clear(); }
   };

}
  #define BOTAN_PUBKEY_INCLUDE_DEPRECATED_CONSTRUCTORS
#endif

namespace Botan {

class RandomNumberGenerator;

/**
* Public Key Encryptor
* This is the primary interface for public key encryption
*/
class BOTAN_PUBLIC_API(2,0) PK_Encryptor
   {
   public:

      /**
      * Encrypt a message.
      * @param in the message as a byte array
      * @param length the length of the above byte array
      * @param rng the random number source to use
      * @return encrypted message
      */
      std::vector<uint8_t> encrypt(const uint8_t in[], size_t length,
                                 RandomNumberGenerator& rng) const
         {
         return enc(in, length, rng);
         }

      /**
      * Encrypt a message.
      * @param in the message
      * @param rng the random number source to use
      * @return encrypted message
      */
      template<typename Alloc>
      std::vector<uint8_t> encrypt(const std::vector<uint8_t, Alloc>& in,
                                RandomNumberGenerator& rng) const
         {
         return enc(in.data(), in.size(), rng);
         }

      /**
      * Return the maximum allowed message size in bytes.
      * @return maximum message size in bytes
      */
      virtual size_t maximum_input_size() const = 0;

      /**
      * Return an upper bound on the ciphertext length
      */
      virtual size_t ciphertext_length(size_t ctext_len) const = 0;

      PK_Encryptor() = default;
      virtual ~PK_Encryptor() = default;

      PK_Encryptor(const PK_Encryptor&) = delete;
      PK_Encryptor& operator=(const PK_Encryptor&) = delete;

   private:
      virtual std::vector<uint8_t> enc(const uint8_t[], size_t,
                                    RandomNumberGenerator&) const = 0;
   };

/**
* Public Key Decryptor
*/
class BOTAN_PUBLIC_API(2,0) PK_Decryptor
   {
   public:
      /**
      * Decrypt a ciphertext, throwing an exception if the input
      * seems to be invalid (eg due to an accidental or malicious
      * error in the ciphertext).
      *
      * @param in the ciphertext as a byte array
      * @param length the length of the above byte array
      * @return decrypted message
      */
      secure_vector<uint8_t> decrypt(const uint8_t in[], size_t length) const;

      /**
      * Same as above, but taking a vector
      * @param in the ciphertext
      * @return decrypted message
      */
      template<typename Alloc>
      secure_vector<uint8_t> decrypt(const std::vector<uint8_t, Alloc>& in) const
         {
         return decrypt(in.data(), in.size());
         }

      /**
      * Decrypt a ciphertext. If the ciphertext is invalid (eg due to
      * invalid padding) or is not the expected length, instead
      * returns a random string of the expected length. Use to avoid
      * oracle attacks, especially against PKCS #1 v1.5 decryption.
      */
      secure_vector<uint8_t>
      decrypt_or_random(const uint8_t in[],
                        size_t length,
                        size_t expected_pt_len,
                        RandomNumberGenerator& rng) const;

      /**
      * Decrypt a ciphertext. If the ciphertext is invalid (eg due to
      * invalid padding) or is not the expected length, instead
      * returns a random string of the expected length. Use to avoid
      * oracle attacks, especially against PKCS #1 v1.5 decryption.
      *
      * Additionally checks (also in const time) that:
      *    contents[required_content_offsets[i]] == required_content_bytes[i]
      * for 0 <= i < required_contents
      *
      * Used for example in TLS, which encodes the client version in
      * the content bytes: if there is any timing variation the version
      * check can be used as an oracle to recover the key.
      */
      secure_vector<uint8_t>
      decrypt_or_random(const uint8_t in[],
                        size_t length,
                        size_t expected_pt_len,
                        RandomNumberGenerator& rng,
                        const uint8_t required_content_bytes[],
                        const uint8_t required_content_offsets[],
                        size_t required_contents) const;

      /**
      * Return an upper bound on the plaintext length for a particular
      * ciphertext input length
      */
      virtual size_t plaintext_length(size_t ctext_len) const = 0;

      PK_Decryptor() = default;
      virtual ~PK_Decryptor() = default;

      PK_Decryptor(const PK_Decryptor&) = delete;
      PK_Decryptor& operator=(const PK_Decryptor&) = delete;

   private:
      virtual secure_vector<uint8_t> do_decrypt(uint8_t& valid_mask,
                                             const uint8_t in[], size_t in_len) const = 0;
   };

/**
* Public Key Signer. Use the sign_message() functions for small
* messages. Use multiple calls update() to process large messages and
* generate the signature by finally calling signature().
*/
class BOTAN_PUBLIC_API(2,0) PK_Signer final
   {
   public:

      /**
      * Construct a PK Signer.
      * @param key the key to use inside this signer
      * @param rng the random generator to use
      * @param emsa the EMSA to use
      * An example would be "EMSA1(SHA-224)".
      * @param format the signature format to use
      * @param provider the provider to use
      */
      PK_Signer(const Private_Key& key,
                RandomNumberGenerator& rng,
                const std::string& emsa,
                Signature_Format format = IEEE_1363,
                const std::string& provider = "");

#if defined(BOTAN_PUBKEY_INCLUDE_DEPRECATED_CONSTRUCTORS)
      /**
      * Construct a PK Signer.
      * @param key the key to use inside this signer
      * @param emsa the EMSA to use
      * An example would be "EMSA1(SHA-224)".
      * @param format the signature format to use
      */
      BOTAN_DEPRECATED("Use constructor taking a RNG object")
      PK_Signer(const Private_Key& key,
                const std::string& emsa,
                Signature_Format format = IEEE_1363,
                const std::string& provider = "") :
         PK_Signer(key, system_rng(), emsa, format, provider)
         {}
#endif

      ~PK_Signer();

      PK_Signer(const PK_Signer&) = delete;
      PK_Signer& operator=(const PK_Signer&) = delete;

      /**
      * Sign a message all in one go
      * @param in the message to sign as a byte array
      * @param length the length of the above byte array
      * @param rng the rng to use
      * @return signature
      */
      std::vector<uint8_t> sign_message(const uint8_t in[], size_t length,
                                     RandomNumberGenerator& rng)
         {
         this->update(in, length);
         return this->signature(rng);
         }

      /**
      * Sign a message.
      * @param in the message to sign
      * @param rng the rng to use
      * @return signature
      */
      template<typename Alloc>
         std::vector<uint8_t> sign_message(const std::vector<uint8_t, Alloc>& in,
                                           RandomNumberGenerator& rng)
         {
         return sign_message(in.data(), in.size(), rng);
         }

      /**
      * Add a message part (single byte).
      * @param in the byte to add
      */
      void update(uint8_t in) { update(&in, 1); }

      /**
      * Add a message part.
      * @param in the message part to add as a byte array
      * @param length the length of the above byte array
      */
      void update(const uint8_t in[], size_t length);

      /**
      * Add a message part.
      * @param in the message part to add
      */
      template<typename Alloc>
      void update(const std::vector<uint8_t, Alloc>& in)
         {
         update(in.data(), in.size());
         }

      /**
      * Add a message part.
      * @param in the message part to add
      */
      void update(const std::string& in)
         {
         update(cast_char_ptr_to_uint8(in.data()), in.size());
         }

      /**
      * Get the signature of the so far processed message (provided by the
      * calls to update()).
      * @param rng the rng to use
      * @return signature of the total message
      */
      std::vector<uint8_t> signature(RandomNumberGenerator& rng);


      /**
      * Set the output format of the signature.
      * @param format the signature format to use
      */
      void set_output_format(Signature_Format format) { m_sig_format = format; }

      /**
      * Return an upper bound on the length of the signatures this
      * PK_Signer will produce
      */
      size_t signature_length() const;

   private:
      std::unique_ptr<PK_Ops::Signature> m_op;
      Signature_Format m_sig_format;
      size_t m_parts, m_part_size;
   };

/**
* Public Key Verifier. Use the verify_message() functions for small
* messages. Use multiple calls update() to process large messages and
* verify the signature by finally calling check_signature().
*/
class BOTAN_PUBLIC_API(2,0) PK_Verifier final
   {
   public:
      /**
      * Construct a PK Verifier.
      * @param pub_key the public key to verify against
      * @param emsa the EMSA to use (eg "EMSA3(SHA-1)")
      * @param format the signature format to use
      * @param provider the provider to use
      */
      PK_Verifier(const Public_Key& pub_key,
                  const std::string& emsa,
                  Signature_Format format = IEEE_1363,
                  const std::string& provider = "");

      ~PK_Verifier();

      PK_Verifier& operator=(const PK_Verifier&) = delete;
      PK_Verifier(const PK_Verifier&) = delete;

      /**
      * Verify a signature.
      * @param msg the message that the signature belongs to, as a byte array
      * @param msg_length the length of the above byte array msg
      * @param sig the signature as a byte array
      * @param sig_length the length of the above byte array sig
      * @return true if the signature is valid
      */
      bool verify_message(const uint8_t msg[], size_t msg_length,
                          const uint8_t sig[], size_t sig_length);
      /**
      * Verify a signature.
      * @param msg the message that the signature belongs to
      * @param sig the signature
      * @return true if the signature is valid
      */
      template<typename Alloc, typename Alloc2>
      bool verify_message(const std::vector<uint8_t, Alloc>& msg,
                          const std::vector<uint8_t, Alloc2>& sig)
         {
         return verify_message(msg.data(), msg.size(),
                               sig.data(), sig.size());
         }

      /**
      * Add a message part (single byte) of the message corresponding to the
      * signature to be verified.
      * @param in the byte to add
      */
      void update(uint8_t in) { update(&in, 1); }

      /**
      * Add a message part of the message corresponding to the
      * signature to be verified.
      * @param msg_part the new message part as a byte array
      * @param length the length of the above byte array
      */
      void update(const uint8_t msg_part[], size_t length);

      /**
      * Add a message part of the message corresponding to the
      * signature to be verified.
      * @param in the new message part
      */
      template<typename Alloc>
         void update(const std::vector<uint8_t, Alloc>& in)
         {
         update(in.data(), in.size());
         }

      /**
      * Add a message part of the message corresponding to the
      * signature to be verified.
      */
      void update(const std::string& in)
         {
         update(cast_char_ptr_to_uint8(in.data()), in.size());
         }

      /**
      * Check the signature of the buffered message, i.e. the one build
      * by successive calls to update.
      * @param sig the signature to be verified as a byte array
      * @param length the length of the above byte array
      * @return true if the signature is valid, false otherwise
      */
      bool check_signature(const uint8_t sig[], size_t length);

      /**
      * Check the signature of the buffered message, i.e. the one build
      * by successive calls to update.
      * @param sig the signature to be verified
      * @return true if the signature is valid, false otherwise
      */
      template<typename Alloc>
      bool check_signature(const std::vector<uint8_t, Alloc>& sig)
         {
         return check_signature(sig.data(), sig.size());
         }

      /**
      * Set the format of the signatures fed to this verifier.
      * @param format the signature format to use
      */
      void set_input_format(Signature_Format format);

   private:
      std::unique_ptr<PK_Ops::Verification> m_op;
      Signature_Format m_sig_format;
      size_t m_parts, m_part_size;
   };

/**
* Object used for key agreement
*/
class BOTAN_PUBLIC_API(2,0) PK_Key_Agreement final
   {
   public:

      /**
      * Construct a PK Key Agreement.
      * @param key the key to use
      * @param rng the random generator to use
      * @param kdf name of the KDF to use (or 'Raw' for no KDF)
      * @param provider the algo provider to use (or empty for default)
      */
      PK_Key_Agreement(const Private_Key& key,
                       RandomNumberGenerator& rng,
                       const std::string& kdf,
                       const std::string& provider = "");

#if defined(BOTAN_PUBKEY_INCLUDE_DEPRECATED_CONSTRUCTORS)
      /**
      * Construct a PK Key Agreement.
      * @param key the key to use
      * @param kdf name of the KDF to use (or 'Raw' for no KDF)
      * @param provider the algo provider to use (or empty for default)
      */
      BOTAN_DEPRECATED("Use constructor taking a RNG object")
      PK_Key_Agreement(const Private_Key& key,
                       const std::string& kdf,
                       const std::string& provider = "") :
         PK_Key_Agreement(key, system_rng(), kdf, provider)
         {}
#endif

      ~PK_Key_Agreement();

      // For ECIES
      PK_Key_Agreement& operator=(PK_Key_Agreement&&);
      PK_Key_Agreement(PK_Key_Agreement&&);

      PK_Key_Agreement& operator=(const PK_Key_Agreement&) = delete;
      PK_Key_Agreement(const PK_Key_Agreement&) = delete;

      /**
      * Perform Key Agreement Operation
      * @param key_len the desired key output size
      * @param in the other parties key
      * @param in_len the length of in in bytes
      * @param params extra derivation params
      * @param params_len the length of params in bytes
      */
      SymmetricKey derive_key(size_t key_len,
                              const uint8_t in[],
                              size_t in_len,
                              const uint8_t params[],
                              size_t params_len) const;

      /**
      * Perform Key Agreement Operation
      * @param key_len the desired key output size
      * @param in the other parties key
      * @param params extra derivation params
      * @param params_len the length of params in bytes
      */
      SymmetricKey derive_key(size_t key_len,
                              const std::vector<uint8_t>& in,
                              const uint8_t params[],
                              size_t params_len) const
         {
         return derive_key(key_len, in.data(), in.size(),
                           params, params_len);
         }

      /**
      * Perform Key Agreement Operation
      * @param key_len the desired key output size
      * @param in the other parties key
      * @param in_len the length of in in bytes
      * @param params extra derivation params
      */
      SymmetricKey derive_key(size_t key_len,
                              const uint8_t in[], size_t in_len,
                              const std::string& params = "") const
         {
         return derive_key(key_len, in, in_len,
                           cast_char_ptr_to_uint8(params.data()),
                           params.length());
         }

      /**
      * Perform Key Agreement Operation
      * @param key_len the desired key output size
      * @param in the other parties key
      * @param params extra derivation params
      */
      SymmetricKey derive_key(size_t key_len,
                              const std::vector<uint8_t>& in,
                              const std::string& params = "") const
         {
         return derive_key(key_len, in.data(), in.size(),
                           cast_char_ptr_to_uint8(params.data()),
                           params.length());
         }

      /**
      * Return the underlying size of the value that is agreed.
      * If derive_key is called with a length of 0 with a "Raw"
      * KDF, it will return a value of this size.
      */
      size_t agreed_value_size() const;

   private:
      std::unique_ptr<PK_Ops::Key_Agreement> m_op;
   };

/**
* Encryption using a standard message recovery algorithm like RSA or
* ElGamal, paired with an encoding scheme like OAEP.
*/
class BOTAN_PUBLIC_API(2,0) PK_Encryptor_EME final : public PK_Encryptor
   {
   public:
      size_t maximum_input_size() const override;

      /**
      * Construct an instance.
      * @param key the key to use inside the encryptor
      * @param rng the RNG to use
      * @param padding the message encoding scheme to use (eg "OAEP(SHA-256)")
      * @param provider the provider to use
      */
      PK_Encryptor_EME(const Public_Key& key,
                       RandomNumberGenerator& rng,
                       const std::string& padding,
                       const std::string& provider = "");

#if defined(BOTAN_PUBKEY_INCLUDE_DEPRECATED_CONSTRUCTORS)
      /**
      * Construct an instance.
      * @param key the key to use inside the encryptor
      * @param padding the message encoding scheme to use (eg "OAEP(SHA-256)")
      */
      BOTAN_DEPRECATED("Use constructor taking a RNG object")
      PK_Encryptor_EME(const Public_Key& key,
                       const std::string& padding,
                       const std::string& provider = "") :
         PK_Encryptor_EME(key, system_rng(), padding, provider) {}
#endif

      ~PK_Encryptor_EME();

      PK_Encryptor_EME& operator=(const PK_Encryptor_EME&) = delete;
      PK_Encryptor_EME(const PK_Encryptor_EME&) = delete;

      /**
      * Return an upper bound on the ciphertext length for a particular
      * plaintext input length
      */
      size_t ciphertext_length(size_t ptext_len) const override;
   private:
      std::vector<uint8_t> enc(const uint8_t[], size_t,
                             RandomNumberGenerator& rng) const override;

      std::unique_ptr<PK_Ops::Encryption> m_op;
   };

/**
* Decryption with an MR algorithm and an EME.
*/
class BOTAN_PUBLIC_API(2,0) PK_Decryptor_EME final : public PK_Decryptor
   {
   public:
     /**
      * Construct an instance.
      * @param key the key to use inside the decryptor
      * @param rng the random generator to use
      * @param eme the EME to use
      * @param provider the provider to use
      */
      PK_Decryptor_EME(const Private_Key& key,
                       RandomNumberGenerator& rng,
                       const std::string& eme,
                       const std::string& provider = "");


#if defined(BOTAN_PUBKEY_INCLUDE_DEPRECATED_CONSTRUCTORS)
      /**
      * Construct an instance.
      * @param key the key to use inside the decryptor
      * @param eme the message encoding scheme to use (eg "OAEP(SHA-256)")
      */
      BOTAN_DEPRECATED("Use constructor taking a RNG object")
      PK_Decryptor_EME(const Private_Key& key,
                       const std::string& eme,
                       const std::string& provider = "") :
         PK_Decryptor_EME(key, system_rng(), eme, provider) {}
#endif

      size_t plaintext_length(size_t ptext_len) const override;

      ~PK_Decryptor_EME();
      PK_Decryptor_EME& operator=(const PK_Decryptor_EME&) = delete;
      PK_Decryptor_EME(const PK_Decryptor_EME&) = delete;
   private:
      secure_vector<uint8_t> do_decrypt(uint8_t& valid_mask,
                                     const uint8_t in[],
                                     size_t in_len) const override;

      std::unique_ptr<PK_Ops::Decryption> m_op;
   };

/**
* Public Key Key Encapsulation Mechanism Encryption.
*/
class BOTAN_PUBLIC_API(2,0) PK_KEM_Encryptor final
   {
   public:
      /**
      * Construct an instance.
      * @param key the key to use inside the encryptor
      * @param rng the RNG to use
      * @param kem_param additional KEM parameters
      * @param provider the provider to use
      */
      PK_KEM_Encryptor(const Public_Key& key,
                       RandomNumberGenerator& rng,
                       const std::string& kem_param = "",
                       const std::string& provider = "");

#if defined(BOTAN_PUBKEY_INCLUDE_DEPRECATED_CONSTRUCTORS)
      BOTAN_DEPRECATED("Use constructor taking a RNG object")
      PK_KEM_Encryptor(const Public_Key& key,
                       const std::string& kem_param = "",
                       const std::string& provider = "") :
         PK_KEM_Encryptor(key, system_rng(), kem_param, provider) {}
#endif

      ~PK_KEM_Encryptor();

      PK_KEM_Encryptor& operator=(const PK_KEM_Encryptor&) = delete;
      PK_KEM_Encryptor(const PK_KEM_Encryptor&) = delete;

      /**
      * Generate a shared key for data encryption.
      * @param out_encapsulated_key the generated encapsulated key
      * @param out_shared_key the generated shared key
      * @param desired_shared_key_len desired size of the shared key in bytes
      * @param rng the RNG to use
      * @param salt a salt value used in the KDF
      * @param salt_len size of the salt value in bytes
      */
      void encrypt(secure_vector<uint8_t>& out_encapsulated_key,
                   secure_vector<uint8_t>& out_shared_key,
                   size_t desired_shared_key_len,
                   Botan::RandomNumberGenerator& rng,
                   const uint8_t salt[],
                   size_t salt_len);

      /**
      * Generate a shared key for data encryption.
      * @param out_encapsulated_key the generated encapsulated key
      * @param out_shared_key the generated shared key
      * @param desired_shared_key_len desired size of the shared key in bytes
      * @param rng the RNG to use
      * @param salt a salt value used in the KDF
      */
      template<typename Alloc>
         void encrypt(secure_vector<uint8_t>& out_encapsulated_key,
                      secure_vector<uint8_t>& out_shared_key,
                      size_t desired_shared_key_len,
                      Botan::RandomNumberGenerator& rng,
                      const std::vector<uint8_t, Alloc>& salt)
         {
         this->encrypt(out_encapsulated_key,
                       out_shared_key,
                       desired_shared_key_len,
                       rng,
                       salt.data(), salt.size());
         }


      /**
      * Generate a shared key for data encryption.
      * @param out_encapsulated_key the generated encapsulated key
      * @param out_shared_key the generated shared key
      * @param desired_shared_key_len desired size of the shared key in bytes
      * @param rng the RNG to use
      */
      void encrypt(secure_vector<uint8_t>& out_encapsulated_key,
                   secure_vector<uint8_t>& out_shared_key,
                   size_t desired_shared_key_len,
                   Botan::RandomNumberGenerator& rng)
         {
         this->encrypt(out_encapsulated_key,
                       out_shared_key,
                       desired_shared_key_len,
                       rng,
                       nullptr,
                       0);
         }

   private:
      std::unique_ptr<PK_Ops::KEM_Encryption> m_op;
   };

/**
* Public Key Key Encapsulation Mechanism Decryption.
*/
class BOTAN_PUBLIC_API(2,0) PK_KEM_Decryptor final
   {
   public:
      /**
      * Construct an instance.
      * @param key the key to use inside the decryptor
      * @param rng the RNG to use
      * @param kem_param additional KEM parameters
      * @param provider the provider to use
      */
      PK_KEM_Decryptor(const Private_Key& key,
                       RandomNumberGenerator& rng,
                       const std::string& kem_param = "",
                       const std::string& provider = "");

#if defined(BOTAN_PUBKEY_INCLUDE_DEPRECATED_CONSTRUCTORS)
      BOTAN_DEPRECATED("Use constructor taking a RNG object")
      PK_KEM_Decryptor(const Private_Key& key,
                       const std::string& kem_param = "",
                       const std::string& provider = "") :
         PK_KEM_Decryptor(key, system_rng(), kem_param, provider)
         {}
#endif

      ~PK_KEM_Decryptor();
      PK_KEM_Decryptor& operator=(const PK_KEM_Decryptor&) = delete;
      PK_KEM_Decryptor(const PK_KEM_Decryptor&) = delete;

      /**
      * Decrypts the shared key for data encryption.
      * @param encap_key the encapsulated key
      * @param encap_key_len size of the encapsulated key in bytes
      * @param desired_shared_key_len desired size of the shared key in bytes
      * @param salt a salt value used in the KDF
      * @param salt_len size of the salt value in bytes
      * @return the shared data encryption key
      */
      secure_vector<uint8_t> decrypt(const uint8_t encap_key[],
                                  size_t encap_key_len,
                                  size_t desired_shared_key_len,
                                  const uint8_t salt[],
                                  size_t salt_len);

      /**
      * Decrypts the shared key for data encryption.
      * @param encap_key the encapsulated key
      * @param encap_key_len size of the encapsulated key in bytes
      * @param desired_shared_key_len desired size of the shared key in bytes
      * @return the shared data encryption key
      */
      secure_vector<uint8_t> decrypt(const uint8_t encap_key[],
                                  size_t encap_key_len,
                                  size_t desired_shared_key_len)
         {
         return this->decrypt(encap_key, encap_key_len,
                              desired_shared_key_len,
                              nullptr, 0);
         }

      /**
      * Decrypts the shared key for data encryption.
      * @param encap_key the encapsulated key
      * @param desired_shared_key_len desired size of the shared key in bytes
      * @param salt a salt value used in the KDF
      * @return the shared data encryption key
      */
      template<typename Alloc1, typename Alloc2>
         secure_vector<uint8_t> decrypt(const std::vector<uint8_t, Alloc1>& encap_key,
                                     size_t desired_shared_key_len,
                                     const std::vector<uint8_t, Alloc2>& salt)
         {
         return this->decrypt(encap_key.data(), encap_key.size(),
                              desired_shared_key_len,
                              salt.data(), salt.size());
         }

   private:
      std::unique_ptr<PK_Ops::KEM_Decryption> m_op;
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(rotate.h)

namespace Botan {

/**
* Bit rotation left by a compile-time constant amount
* @param input the input word
* @return input rotated left by ROT bits
*/
template<size_t ROT, typename T>
inline constexpr T rotl(T input)
   {
   static_assert(ROT > 0 && ROT < 8*sizeof(T), "Invalid rotation constant");
   return static_cast<T>((input << ROT) | (input >> (8*sizeof(T) - ROT)));
   }

/**
* Bit rotation right by a compile-time constant amount
* @param input the input word
* @return input rotated right by ROT bits
*/
template<size_t ROT, typename T>
inline constexpr T rotr(T input)
   {
   static_assert(ROT > 0 && ROT < 8*sizeof(T), "Invalid rotation constant");
   return static_cast<T>((input >> ROT) | (input << (8*sizeof(T) - ROT)));
   }

/**
* Bit rotation left, variable rotation amount
* @param input the input word
* @param rot the number of bits to rotate, must be between 0 and sizeof(T)*8-1
* @return input rotated left by rot bits
*/
template<typename T>
inline T rotl_var(T input, size_t rot)
   {
   return rot ? static_cast<T>((input << rot) | (input >> (sizeof(T)*8 - rot))) : input;
   }

/**
* Bit rotation right, variable rotation amount
* @param input the input word
* @param rot the number of bits to rotate, must be between 0 and sizeof(T)*8-1
* @return input rotated right by rot bits
*/
template<typename T>
inline T rotr_var(T input, size_t rot)
   {
   return rot ? static_cast<T>((input >> rot) | (input << (sizeof(T)*8 - rot))) : input;
   }

#if defined(BOTAN_USE_GCC_INLINE_ASM)

#if defined(BOTAN_TARGET_ARCH_IS_X86_64) || defined(BOTAN_TARGET_ARCH_IS_X86_32)

template<>
inline uint32_t rotl_var(uint32_t input, size_t rot)
   {
   asm("roll %1,%0" : "+r" (input) : "c" (static_cast<uint8_t>(rot)));
   return input;
   }

template<>
inline uint32_t rotr_var(uint32_t input, size_t rot)
   {
   asm("rorl %1,%0" : "+r" (input) : "c" (static_cast<uint8_t>(rot)));
   return input;
   }

#endif

#endif


template<typename T>
BOTAN_DEPRECATED("Use rotl<N> or rotl_var")
inline T rotate_left(T input, size_t rot)
   {
   // rotl_var does not reduce
   return rotl_var(input, rot % (8 * sizeof(T)));
   }

template<typename T>
BOTAN_DEPRECATED("Use rotr<N> or rotr_var")
inline T rotate_right(T input, size_t rot)
   {
   // rotr_var does not reduce
   return rotr_var(input, rot % (8 * sizeof(T)));
   }

}

namespace Botan {

class RSA_Public_Data;
class RSA_Private_Data;

/**
* RSA Public Key
*/
class BOTAN_PUBLIC_API(2,0) RSA_PublicKey : public virtual Public_Key
   {
   public:
      /**
      * Load a public key.
      * @param alg_id the X.509 algorithm identifier
      * @param key_bits DER encoded public key bits
      */
      RSA_PublicKey(const AlgorithmIdentifier& alg_id,
                    const std::vector<uint8_t>& key_bits);

      /**
      * Create a public key.
      * @arg n the modulus
      * @arg e the exponent
      */
      RSA_PublicKey(const BigInt& n, const BigInt& e);

      std::string algo_name() const override { return "RSA"; }

      bool check_key(RandomNumberGenerator& rng, bool) const override;

      AlgorithmIdentifier algorithm_identifier() const override;

      std::vector<uint8_t> public_key_bits() const override;

      /**
      * @return public modulus
      */
      const BigInt& get_n() const;

      /**
      * @return public exponent
      */
      const BigInt& get_e() const;

      size_t key_length() const override;
      size_t estimated_strength() const override;

      // internal functions:
      std::shared_ptr<const RSA_Public_Data> public_data() const;

      std::unique_ptr<PK_Ops::Encryption>
         create_encryption_op(RandomNumberGenerator& rng,
                              const std::string& params,
                              const std::string& provider) const override;

      std::unique_ptr<PK_Ops::KEM_Encryption>
         create_kem_encryption_op(RandomNumberGenerator& rng,
                                  const std::string& params,
                                  const std::string& provider) const override;

      std::unique_ptr<PK_Ops::Verification>
         create_verification_op(const std::string& params,
                                const std::string& provider) const override;

   protected:
      RSA_PublicKey() = default;

      void init(BigInt&& n, BigInt&& e);

      std::shared_ptr<const RSA_Public_Data> m_public;
   };

/**
* RSA Private Key
*/
class BOTAN_PUBLIC_API(2,0) RSA_PrivateKey final : public Private_Key, public RSA_PublicKey
   {
   public:
      /**
      * Load a private key.
      * @param alg_id the X.509 algorithm identifier
      * @param key_bits PKCS#1 RSAPrivateKey bits
      */
      RSA_PrivateKey(const AlgorithmIdentifier& alg_id,
                     const secure_vector<uint8_t>& key_bits);

      /**
      * Construct a private key from the specified parameters.
      * @param p the first prime
      * @param q the second prime
      * @param e the exponent
      * @param d if specified, this has to be d with
      * exp * d = 1 mod (p - 1, q - 1). Leave it as 0 if you wish to
      * the constructor to calculate it.
      * @param n if specified, this must be n = p * q. Leave it as 0
      * if you wish to the constructor to calculate it.
      */
      RSA_PrivateKey(const BigInt& p, const BigInt& q,
                     const BigInt& e, const BigInt& d = 0,
                     const BigInt& n = 0);

      /**
      * Create a new private key with the specified bit length
      * @param rng the random number generator to use
      * @param bits the desired bit length of the private key
      * @param exp the public exponent to be used
      */
      RSA_PrivateKey(RandomNumberGenerator& rng,
                     size_t bits, size_t exp = 65537);

      bool check_key(RandomNumberGenerator& rng, bool) const override;

      /**
      * Get the first prime p.
      * @return prime p
      */
      const BigInt& get_p() const;

      /**
      * Get the second prime q.
      * @return prime q
      */
      const BigInt& get_q() const;

      /**
      * Get d with exp * d = 1 mod (p - 1, q - 1).
      * @return d
      */
      const BigInt& get_d() const;

      const BigInt& get_c() const;
      const BigInt& get_d1() const;
      const BigInt& get_d2() const;

      secure_vector<uint8_t> private_key_bits() const override;

      // internal functions:
      std::shared_ptr<const RSA_Private_Data> private_data() const;

      std::unique_ptr<PK_Ops::Decryption>
         create_decryption_op(RandomNumberGenerator& rng,
                              const std::string& params,
                              const std::string& provider) const override;

      std::unique_ptr<PK_Ops::KEM_Decryption>
         create_kem_decryption_op(RandomNumberGenerator& rng,
                                  const std::string& params,
                                  const std::string& provider) const override;

      std::unique_ptr<PK_Ops::Signature>
         create_signature_op(RandomNumberGenerator& rng,
                             const std::string& params,
                             const std::string& provider) const override;

   private:

      void init(BigInt&& d, BigInt&& p, BigInt&& q, BigInt&& d1, BigInt&& d2, BigInt&& c);

      std::shared_ptr<const RSA_Private_Data> m_private;
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(scan_name.h)

namespace Botan {

/**
A class encapsulating a SCAN name (similar to JCE conventions)
http://www.users.zetnet.co.uk/hopwood/crypto/scan/
*/
class BOTAN_PUBLIC_API(2,0) SCAN_Name final
   {
   public:
      /**
      * Create a SCAN_Name
      * @param algo_spec A SCAN-format name
      */
      explicit SCAN_Name(const char* algo_spec);

      /**
      * Create a SCAN_Name
      * @param algo_spec A SCAN-format name
      */
      explicit SCAN_Name(std::string algo_spec);

      /**
      * @return original input string
      */
      const std::string& to_string() const { return m_orig_algo_spec; }

      BOTAN_DEPRECATED("Use SCAN_Name::to_string") const std::string& as_string() const
         {
         return this->to_string();
         }

      /**
      * @return algorithm name
      */
      const std::string& algo_name() const { return m_alg_name; }

      /**
      * @return number of arguments
      */
      size_t arg_count() const { return m_args.size(); }

      /**
      * @param lower is the lower bound
      * @param upper is the upper bound
      * @return if the number of arguments is between lower and upper
      */
      bool arg_count_between(size_t lower, size_t upper) const
         { return ((arg_count() >= lower) && (arg_count() <= upper)); }

      /**
      * @param i which argument
      * @return ith argument
      */
      std::string arg(size_t i) const;

      /**
      * @param i which argument
      * @param def_value the default value
      * @return ith argument or the default value
      */
      std::string arg(size_t i, const std::string& def_value) const;

      /**
      * @param i which argument
      * @param def_value the default value
      * @return ith argument as an integer, or the default value
      */
      size_t arg_as_integer(size_t i, size_t def_value) const;

      /**
      * @return cipher mode (if any)
      */
      std::string cipher_mode() const
         { return (m_mode_info.size() >= 1) ? m_mode_info[0] : ""; }

      /**
      * @return cipher mode padding (if any)
      */
      std::string cipher_mode_pad() const
         { return (m_mode_info.size() >= 2) ? m_mode_info[1] : ""; }

   private:
      std::string m_orig_algo_spec;
      std::string m_alg_name;
      std::vector<std::string> m_args;
      std::vector<std::string> m_mode_info;
   };

// This is unrelated but it is convenient to stash it here
template<typename T>
std::vector<std::string> probe_providers_of(const std::string& algo_spec,
                                            const std::vector<std::string>& possible)
   {
   std::vector<std::string> providers;
   for(auto&& prov : possible)
      {
      std::unique_ptr<T> o(T::create(algo_spec, prov));
      if(o)
         {
         providers.push_back(prov); // available
         }
      }
   return providers;
   }

}

BOTAN_FUTURE_INTERNAL_HEADER(sha160.h)

namespace Botan {

/**
* NIST's SHA-160
*/
class BOTAN_PUBLIC_API(2,0) SHA_160 final : public MDx_HashFunction
   {
   public:
      std::string name() const override { return "SHA-160"; }
      size_t output_length() const override { return 20; }
      HashFunction* clone() const override { return new SHA_160; }
      std::unique_ptr<HashFunction> copy_state() const override;

      void clear() override;

      SHA_160() : MDx_HashFunction(64, true, true), m_digest(5)
         {
         clear();
         }

   private:
      void compress_n(const uint8_t[], size_t blocks) override;

#if defined(BOTAN_HAS_SHA1_ARMV8)
      static void sha1_armv8_compress_n(secure_vector<uint32_t>& digest,
                                        const uint8_t blocks[],
                                        size_t block_count);
#endif

#if defined(BOTAN_HAS_SHA1_SSE2)
      static void sse2_compress_n(secure_vector<uint32_t>& digest,
                                  const uint8_t blocks[],
                                  size_t block_count);
#endif

#if defined(BOTAN_HAS_SHA1_X86_SHA_NI)
      // Using x86 SHA instructions in Intel Goldmont and Cannonlake
      static void sha1_compress_x86(secure_vector<uint32_t>& digest,
                                    const uint8_t blocks[],
                                    size_t block_count);
#endif


      void copy_out(uint8_t[]) override;

      /**
      * The digest value
      */
      secure_vector<uint32_t> m_digest;

      /**
      * The message buffer
      */
      secure_vector<uint32_t> m_W;
   };

typedef SHA_160 SHA_1;

}

BOTAN_FUTURE_INTERNAL_HEADER(sha2_32.h)

namespace Botan {

/**
* SHA-224
*/
class BOTAN_PUBLIC_API(2,0) SHA_224 final : public MDx_HashFunction
   {
   public:
      std::string name() const override { return "SHA-224"; }
      size_t output_length() const override { return 28; }
      HashFunction* clone() const override { return new SHA_224; }
      std::unique_ptr<HashFunction> copy_state() const override;

      void clear() override;

      std::string provider() const override;

      SHA_224() : MDx_HashFunction(64, true, true), m_digest(8)
         { clear(); }
   private:
      void compress_n(const uint8_t[], size_t blocks) override;
      void copy_out(uint8_t[]) override;

      secure_vector<uint32_t> m_digest;
   };

/**
* SHA-256
*/
class BOTAN_PUBLIC_API(2,0) SHA_256 final : public MDx_HashFunction
   {
   public:
      std::string name() const override { return "SHA-256"; }
      size_t output_length() const override { return 32; }
      HashFunction* clone() const override { return new SHA_256; }
      std::unique_ptr<HashFunction> copy_state() const override;

      void clear() override;

      std::string provider() const override;

      SHA_256() : MDx_HashFunction(64, true, true), m_digest(8)
         { clear(); }

      /*
      * Perform a SHA-256 compression. For internal use
      */
      static void compress_digest(secure_vector<uint32_t>& digest,
                                  const uint8_t input[],
                                  size_t blocks);

   private:

#if defined(BOTAN_HAS_SHA2_32_ARMV8)
      static void compress_digest_armv8(secure_vector<uint32_t>& digest,
                                        const uint8_t input[],
                                        size_t blocks);
#endif

#if defined(BOTAN_HAS_SHA2_32_X86_BMI2)
      static void compress_digest_x86_bmi2(secure_vector<uint32_t>& digest,
                                           const uint8_t input[],
                                           size_t blocks);
#endif

#if defined(BOTAN_HAS_SHA2_32_X86)
      static void compress_digest_x86(secure_vector<uint32_t>& digest,
                                      const uint8_t input[],
                                      size_t blocks);
#endif

      void compress_n(const uint8_t[], size_t blocks) override;
      void copy_out(uint8_t[]) override;

      secure_vector<uint32_t> m_digest;
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(sha2_64.h)

namespace Botan {

/**
* SHA-384
*/
class BOTAN_PUBLIC_API(2,0) SHA_384 final : public MDx_HashFunction
   {
   public:
      std::string name() const override { return "SHA-384"; }
      size_t output_length() const override { return 48; }
      HashFunction* clone() const override { return new SHA_384; }
      std::unique_ptr<HashFunction> copy_state() const override;
      std::string provider() const override;

      void clear() override;

      SHA_384() : MDx_HashFunction(128, true, true, 16), m_digest(8)
         { clear(); }
   private:
      void compress_n(const uint8_t[], size_t blocks) override;
      void copy_out(uint8_t[]) override;

      secure_vector<uint64_t> m_digest;
   };

/**
* SHA-512
*/
class BOTAN_PUBLIC_API(2,0) SHA_512 final : public MDx_HashFunction
   {
   public:
      std::string name() const override { return "SHA-512"; }
      size_t output_length() const override { return 64; }
      HashFunction* clone() const override { return new SHA_512; }
      std::unique_ptr<HashFunction> copy_state() const override;
      std::string provider() const override;

      void clear() override;

      /*
      * Perform a SHA-512 compression. For internal use
      */
      static void compress_digest(secure_vector<uint64_t>& digest,
                                  const uint8_t input[],
                                  size_t blocks);

      SHA_512() : MDx_HashFunction(128, true, true, 16), m_digest(8)
         { clear(); }
   private:
      void compress_n(const uint8_t[], size_t blocks) override;
      void copy_out(uint8_t[]) override;

      static const uint64_t K[80];

#if defined(BOTAN_HAS_SHA2_64_BMI2)
      static void compress_digest_bmi2(secure_vector<uint64_t>& digest,
                                       const uint8_t input[],
                                       size_t blocks);
#endif

      secure_vector<uint64_t> m_digest;
   };

/**
* SHA-512/256
*/
class BOTAN_PUBLIC_API(2,0) SHA_512_256 final : public MDx_HashFunction
   {
   public:
      std::string name() const override { return "SHA-512-256"; }
      size_t output_length() const override { return 32; }
      HashFunction* clone() const override { return new SHA_512_256; }
      std::unique_ptr<HashFunction> copy_state() const override;
      std::string provider() const override;

      void clear() override;

      SHA_512_256() : MDx_HashFunction(128, true, true, 16), m_digest(8) { clear(); }
   private:
      void compress_n(const uint8_t[], size_t blocks) override;
      void copy_out(uint8_t[]) override;

      secure_vector<uint64_t> m_digest;
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(sha3.h)

namespace Botan {

/**
* SHA-3
*/
class BOTAN_PUBLIC_API(2,0) SHA_3 : public HashFunction
   {
   public:

      /**
      * @param output_bits the size of the hash output; must be one of
      *                    224, 256, 384, or 512
      */
      explicit SHA_3(size_t output_bits);

      size_t hash_block_size() const override { return m_bitrate / 8; }
      size_t output_length() const override { return m_output_bits / 8; }

      HashFunction* clone() const override;
      std::unique_ptr<HashFunction> copy_state() const override;
      std::string name() const override;
      void clear() override;
      std::string provider() const override;

      // Static functions for internal usage

      /**
      * Absorb data into the provided state
      * @param bitrate the bitrate to absorb into the sponge
      * @param S the sponge state
      * @param S_pos where to begin absorbing into S
      * @param input the input data
      * @param length size of input in bytes
      */
      static size_t absorb(size_t bitrate,
                           secure_vector<uint64_t>& S, size_t S_pos,
                           const uint8_t input[], size_t length);

      /**
      * Add final padding and permute. The padding is assumed to be
      * init_pad || 00... || fini_pad
      *
      * @param bitrate the bitrate to absorb into the sponge
      * @param S the sponge state
      * @param S_pos where to begin absorbing into S
      * @param init_pad the leading pad bits
      * @param fini_pad the final pad bits
      */
      static void finish(size_t bitrate,
                         secure_vector<uint64_t>& S, size_t S_pos,
                         uint8_t init_pad, uint8_t fini_pad);

      /**
      * Expand from provided state
      * @param bitrate sponge parameter
      * @param S the state
      * @param output the output buffer
      * @param output_length the size of output in bytes
      */
      static void expand(size_t bitrate,
                         secure_vector<uint64_t>& S,
                         uint8_t output[], size_t output_length);

      /**
      * The bare Keccak-1600 permutation
      */
      static void permute(uint64_t A[25]);

   private:
      void add_data(const uint8_t input[], size_t length) override;
      void final_result(uint8_t out[]) override;

#if defined(BOTAN_HAS_SHA3_BMI2)
      static void permute_bmi2(uint64_t A[25]);
#endif

      size_t m_output_bits, m_bitrate;
      secure_vector<uint64_t> m_S;
      size_t m_S_pos;
   };

/**
* SHA-3-224
*/
class BOTAN_PUBLIC_API(2,0) SHA_3_224 final : public SHA_3
   {
   public:
      SHA_3_224() : SHA_3(224) {}
   };

/**
* SHA-3-256
*/
class BOTAN_PUBLIC_API(2,0) SHA_3_256 final : public SHA_3
   {
   public:
      SHA_3_256() : SHA_3(256) {}
   };

/**
* SHA-3-384
*/
class BOTAN_PUBLIC_API(2,0) SHA_3_384 final : public SHA_3
   {
   public:
      SHA_3_384() : SHA_3(384) {}
   };

/**
* SHA-3-512
*/
class BOTAN_PUBLIC_API(2,0) SHA_3_512 final : public SHA_3
   {
   public:
      SHA_3_512() : SHA_3(512) {}
   };

}

namespace Botan {

/**
* This class represents SM2 public keys
*/
class BOTAN_PUBLIC_API(2,2) SM2_PublicKey : public virtual EC_PublicKey
   {
   public:

      /**
      * Create a public key from a given public point.
      * @param dom_par the domain parameters associated with this key
      * @param public_point the public point defining this key
      */
      SM2_PublicKey(const EC_Group& dom_par,
                    const PointGFp& public_point) :
         EC_PublicKey(dom_par, public_point) {}

      /**
      * Load a public key.
      * @param alg_id the X.509 algorithm identifier
      * @param key_bits DER encoded public key bits
      */
      SM2_PublicKey(const AlgorithmIdentifier& alg_id,
                    const std::vector<uint8_t>& key_bits) :
         EC_PublicKey(alg_id, key_bits) {}

      /**
      * Get this keys algorithm name.
      * @result this keys algorithm name
      */
      std::string algo_name() const override;

      size_t message_parts() const override { return 2; }

      size_t message_part_size() const override
         { return domain().get_order().bytes(); }

      std::unique_ptr<PK_Ops::Verification>
         create_verification_op(const std::string& params,
                                const std::string& provider) const override;

      std::unique_ptr<PK_Ops::Encryption>
         create_encryption_op(RandomNumberGenerator& rng,
                              const std::string& params,
                              const std::string& provider) const override;

   protected:
      SM2_PublicKey() = default;
   };

/**
* This class represents SM2 private keys
*/
class BOTAN_PUBLIC_API(2,2) SM2_PrivateKey final :
   public SM2_PublicKey, public EC_PrivateKey
   {
   public:

      /**
      * Load a private key
      * @param alg_id the X.509 algorithm identifier
      * @param key_bits ECPrivateKey bits
      */
      SM2_PrivateKey(const AlgorithmIdentifier& alg_id,
                     const secure_vector<uint8_t>& key_bits);

      /**
      * Create a private key.
      * @param rng a random number generator
      * @param domain parameters to used for this key
      * @param x the private key (if zero, generate a new random key)
      */
      SM2_PrivateKey(RandomNumberGenerator& rng,
                     const EC_Group& domain,
                     const BigInt& x = 0);

      bool check_key(RandomNumberGenerator& rng, bool) const override;

      std::unique_ptr<PK_Ops::Signature>
         create_signature_op(RandomNumberGenerator& rng,
                             const std::string& params,
                             const std::string& provider) const override;

      std::unique_ptr<PK_Ops::Decryption>
         create_decryption_op(RandomNumberGenerator& rng,
                              const std::string& params,
                              const std::string& provider) const override;

      const BigInt& get_da_inv() const { return m_da_inv; }
   private:
      BigInt m_da_inv;
   };

class HashFunction;

std::vector<uint8_t>
BOTAN_PUBLIC_API(2,5) sm2_compute_za(HashFunction& hash,
                                     const std::string& user_id,
                                     const EC_Group& domain,
                                     const PointGFp& pubkey);

// For compat with versions 2.2 - 2.7
typedef SM2_PublicKey SM2_Signature_PublicKey;
typedef SM2_PublicKey SM2_Encryption_PublicKey;

typedef SM2_PrivateKey SM2_Signature_PrivateKey;
typedef SM2_PrivateKey SM2_Encryption_PrivateKey;

}

BOTAN_FUTURE_INTERNAL_HEADER(sm3.h)

namespace Botan {

enum {
  SM3_BLOCK_BYTES = 64,
  SM3_DIGEST_BYTES = 32
};

/**
* SM3
*/
class BOTAN_PUBLIC_API(2,2) SM3 final : public MDx_HashFunction
   {
   public:
      std::string name() const override { return "SM3"; }
      size_t output_length() const override { return SM3_DIGEST_BYTES; }
      HashFunction* clone() const override { return new SM3; }
      std::unique_ptr<HashFunction> copy_state() const override;

      void clear() override;

      SM3() : MDx_HashFunction(SM3_BLOCK_BYTES, true, true), m_digest(SM3_DIGEST_BYTES)
         { clear(); }
   private:
      void compress_n(const uint8_t[], size_t blocks) override;
      void copy_out(uint8_t[]) override;

      /**
      * The digest value
      */
      secure_vector<uint32_t> m_digest;
   };

}

BOTAN_FUTURE_INTERNAL_HEADER(sm4.h)

namespace Botan {

/**
* SM4
*/
class BOTAN_PUBLIC_API(2,2) SM4 final : public Block_Cipher_Fixed_Params<16, 16>
   {
   public:
      void encrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const override;
      void decrypt_n(const uint8_t in[], uint8_t out[], size_t blocks) const override;

      void clear() override;
      std::string name() const override { return "SM4"; }
      BlockCipher* clone() const override { return new SM4; }

      std::string provider() const override;
      size_t parallelism() const override;
   private:
      void key_schedule(const uint8_t[], size_t) override;

#if defined(BOTAN_HAS_SM4_ARMV8)
      void sm4_armv8_encrypt(const uint8_t in[], uint8_t out[], size_t blocks) const;
      void sm4_armv8_decrypt(const uint8_t in[], uint8_t out[], size_t blocks) const;
#endif

      secure_vector<uint32_t> m_RK;
   };

}

#if __cplusplus < 201402L
#endif

BOTAN_FUTURE_INTERNAL_HEADER(stl_compatability.h)

namespace Botan
{
/*
* std::make_unique functionality similar as we have in C++14.
* C++11 version based on proposal for C++14 implemenatation by Stephan T. Lavavej
* source: https://isocpp.org/files/papers/N3656.txt
*/
#if __cplusplus >= 201402L
template <typename T, typename ... Args>
constexpr auto make_unique(Args&&... args)
   {
   return std::make_unique<T>(std::forward<Args>(args)...);
   }

template<class T>
constexpr auto make_unique(std::size_t size)
   {
   return std::make_unique<T>(size);
   }

#else
namespace stlCompatibilityDetails
{
template<class T> struct _Unique_if
   {
   typedef std::unique_ptr<T> _Single_object;
   };

template<class T> struct _Unique_if<T[]>
   {
   typedef std::unique_ptr<T[]> _Unknown_bound;
   };

template<class T, size_t N> struct _Unique_if<T[N]>
   {
   typedef void _Known_bound;
   };
}  // namespace stlCompatibilityDetails

template<class T, class... Args>
typename stlCompatibilityDetails::_Unique_if<T>::_Single_object make_unique(Args&&... args)
   {
   return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
   }

template<class T>
typename stlCompatibilityDetails::_Unique_if<T>::_Unknown_bound make_unique(size_t n)
   {
   typedef typename std::remove_extent<T>::type U;
   return std::unique_ptr<T>(new U[n]());
   }

template<class T, class... Args>
typename stlCompatibilityDetails::_Unique_if<T>::_Known_bound make_unique(Args&&...) = delete;

#endif

}  // namespace Botan

#if defined(BOTAN_HAS_STREAM_CIPHER)
#endif

BOTAN_FUTURE_INTERNAL_HEADER(stream_mode.h)

namespace Botan {

#if defined(BOTAN_HAS_STREAM_CIPHER)

class BOTAN_PUBLIC_API(2,0) Stream_Cipher_Mode final : public Cipher_Mode
   {
   public:
      /**
      * @param cipher underyling stream cipher
      */
      explicit Stream_Cipher_Mode(StreamCipher* cipher) : m_cipher(cipher) {}

      size_t process(uint8_t buf[], size_t sz) override
         {
         m_cipher->cipher1(buf, sz);
         return sz;
         }

      void finish(secure_vector<uint8_t>& buf, size_t offset) override
         { return update(buf, offset); }

      size_t output_length(size_t input_length) const override { return input_length; }

      size_t update_granularity() const override { return 1; }

      size_t minimum_final_size() const override { return 0; }

      size_t default_nonce_length() const override { return 0; }

      bool valid_nonce_length(size_t nonce_len) const override
         { return m_cipher->valid_iv_length(nonce_len); }

      Key_Length_Specification key_spec() const override { return m_cipher->key_spec(); }

      std::string name() const override { return m_cipher->name(); }

      void clear() override
         {
         m_cipher->clear();
         reset();
         }

      void reset() override { /* no msg state */ }

   private:
      void start_msg(const uint8_t nonce[], size_t nonce_len) override
         {
         if(nonce_len > 0)
            {
            m_cipher->set_iv(nonce, nonce_len);
            }
         }

      void key_schedule(const uint8_t key[], size_t length) override
         {
         m_cipher->set_key(key, length);
         }

      std::unique_ptr<StreamCipher> m_cipher;
   };

#endif

}

namespace Botan {

namespace TLS {

/**
* SSL/TLS Alert Message
*/
class BOTAN_PUBLIC_API(2,0) Alert final
   {
   public:
      /**
      * Type codes for TLS alerts
      */
      enum Type {
         CLOSE_NOTIFY                    = 0,
         UNEXPECTED_MESSAGE              = 10,
         BAD_RECORD_MAC                  = 20,
         DECRYPTION_FAILED               = 21,
         RECORD_OVERFLOW                 = 22,
         DECOMPRESSION_FAILURE           = 30,
         HANDSHAKE_FAILURE               = 40,
         NO_CERTIFICATE                  = 41, // SSLv3 only
         BAD_CERTIFICATE                 = 42,
         UNSUPPORTED_CERTIFICATE         = 43,
         CERTIFICATE_REVOKED             = 44,
         CERTIFICATE_EXPIRED             = 45,
         CERTIFICATE_UNKNOWN             = 46,
         ILLEGAL_PARAMETER               = 47,
         UNKNOWN_CA                      = 48,
         ACCESS_DENIED                   = 49,
         DECODE_ERROR                    = 50,
         DECRYPT_ERROR                   = 51,
         EXPORT_RESTRICTION              = 60,
         PROTOCOL_VERSION                = 70,
         INSUFFICIENT_SECURITY           = 71,
         INTERNAL_ERROR                  = 80,
         INAPPROPRIATE_FALLBACK          = 86,
         USER_CANCELED                   = 90,
         NO_RENEGOTIATION                = 100,
         UNSUPPORTED_EXTENSION           = 110,
         CERTIFICATE_UNOBTAINABLE        = 111,
         UNRECOGNIZED_NAME               = 112,
         BAD_CERTIFICATE_STATUS_RESPONSE = 113,
         BAD_CERTIFICATE_HASH_VALUE      = 114,
         UNKNOWN_PSK_IDENTITY            = 115,
         CERTIFICATE_REQUIRED            = 116, // RFC 8446

         NO_APPLICATION_PROTOCOL         = 120, // RFC 7301

         // pseudo alert values
         NULL_ALERT                      = 256
      };

      /**
      * @return true iff this alert is non-empty
      */
      bool is_valid() const { return (m_type_code != NULL_ALERT); }

      /**
      * @return if this alert is a fatal one or not
      */
      bool is_fatal() const { return m_fatal; }

      /**
      * @return type of alert
      */
      Type type() const { return m_type_code; }

      /**
      * @return type of alert
      */
      std::string type_string() const;

      /**
      * Serialize an alert
      */
      std::vector<uint8_t> serialize() const;

      /**
      * Deserialize an Alert message
      * @param buf the serialized alert
      */
      explicit Alert(const secure_vector<uint8_t>& buf);

      /**
      * Create a new Alert
      * @param type_code the type of alert
      * @param fatal specifies if this is a fatal alert
      */
      Alert(Type type_code, bool fatal = false) :
         m_fatal(fatal), m_type_code(type_code) {}

      Alert() : m_fatal(false), m_type_code(NULL_ALERT) {}
   private:
      bool m_fatal;
      Type m_type_code;
   };

}

}

//BOTAN_FUTURE_INTERNAL_HEADER(tls_algos.h)

namespace Botan {

namespace TLS {

enum class Cipher_Algo {
   CHACHA20_POLY1305,

   AES_128_CBC_HMAC_SHA1 = 100,
   AES_128_CBC_HMAC_SHA256,
   AES_128_CCM,
   AES_128_CCM_8,
   AES_128_GCM,
   AES_128_OCB,

   AES_256_CBC_HMAC_SHA1 = 200,
   AES_256_CBC_HMAC_SHA256,
   AES_256_CBC_HMAC_SHA384,
   AES_256_CCM,
   AES_256_CCM_8,
   AES_256_GCM,
   AES_256_OCB,

   CAMELLIA_128_CBC_HMAC_SHA1 = 300,
   CAMELLIA_128_CBC_HMAC_SHA256,
   CAMELLIA_128_GCM,

   CAMELLIA_256_CBC_HMAC_SHA1 = 400,
   CAMELLIA_256_CBC_HMAC_SHA256,
   CAMELLIA_256_CBC_HMAC_SHA384,
   CAMELLIA_256_GCM,

   ARIA_128_GCM = 500,
   ARIA_256_GCM,

   DES_EDE_CBC_HMAC_SHA1 = 1000,
   SEED_CBC_HMAC_SHA1,
};

enum class KDF_Algo {
   SHA_1,
   SHA_256,
   SHA_384,
};

std::string BOTAN_DLL kdf_algo_to_string(KDF_Algo algo);

enum class Nonce_Format {
   CBC_MODE,
   AEAD_IMPLICIT_4,
   AEAD_XOR_12,
};

// TODO encoding should match signature_algorithms extension
// TODO this should include hash etc as in TLS v1.3
enum class Auth_Method {
   RSA,
   DSA,
   ECDSA,

   // These are placed outside the encodable range
   IMPLICIT = 0x10000,
   ANONYMOUS
};

std::string BOTAN_TEST_API auth_method_to_string(Auth_Method method);
Auth_Method BOTAN_TEST_API auth_method_from_string(const std::string& str);

/*
* This matches the wire encoding
*/
enum class Signature_Scheme : uint16_t {
   NONE             = 0x0000,

   RSA_PKCS1_SHA1   = 0x0201,
   RSA_PKCS1_SHA256 = 0x0401,
   RSA_PKCS1_SHA384 = 0x0501,
   RSA_PKCS1_SHA512 = 0x0601,

   DSA_SHA1   = 0x0202,
   DSA_SHA256 = 0x0402,
   DSA_SHA384 = 0x0502,
   DSA_SHA512 = 0x0602,

   ECDSA_SHA1   = 0x0203,
   ECDSA_SHA256 = 0x0403,
   ECDSA_SHA384 = 0x0503,
   ECDSA_SHA512 = 0x0603,

   RSA_PSS_SHA256 = 0x0804,
   RSA_PSS_SHA384 = 0x0805,
   RSA_PSS_SHA512 = 0x0806,

   EDDSA_25519 = 0x0807,
   EDDSA_448   = 0x0808,
};

BOTAN_UNSTABLE_API const std::vector<Signature_Scheme>& all_signature_schemes();

bool BOTAN_UNSTABLE_API signature_scheme_is_known(Signature_Scheme scheme);
std::string BOTAN_UNSTABLE_API sig_scheme_to_string(Signature_Scheme scheme);
std::string BOTAN_UNSTABLE_API hash_function_of_scheme(Signature_Scheme scheme);
std::string BOTAN_UNSTABLE_API padding_string_for_scheme(Signature_Scheme scheme);
std::string signature_algorithm_of_scheme(Signature_Scheme scheme);

/*
* Matches with wire encoding
*/
enum class Group_Params : uint16_t {
   NONE = 0,

   SECP256R1 = 23,
   SECP384R1 = 24,
   SECP521R1 = 25,
   BRAINPOOL256R1 = 26,
   BRAINPOOL384R1 = 27,
   BRAINPOOL512R1 = 28,

   X25519 = 29,

   FFDHE_2048 = 256,
   FFDHE_3072 = 257,
   FFDHE_4096 = 258,
   FFDHE_6144 = 259,
   FFDHE_8192 = 260,
};

std::string group_param_to_string(Group_Params group);
Group_Params group_param_from_string(const std::string& group_name);
bool group_param_is_dh(Group_Params group);

enum class Kex_Algo {
   STATIC_RSA,
   DH,
   ECDH,
   CECPQ1,
   SRP_SHA,
   PSK,
   DHE_PSK,
   ECDHE_PSK,
};

std::string BOTAN_TEST_API kex_method_to_string(Kex_Algo method);
Kex_Algo BOTAN_TEST_API kex_method_from_string(const std::string& str);

inline bool key_exchange_is_psk(Kex_Algo m)
   {
   return (m == Kex_Algo::PSK ||
           m == Kex_Algo::DHE_PSK ||
           m == Kex_Algo::ECDHE_PSK);
   }

}

}

namespace Botan {

namespace TLS {

/**
* TLS Protocol Version
*/
class BOTAN_PUBLIC_API(2,0) Protocol_Version final
   {
   public:
      enum Version_Code {
         TLS_V10            = 0x0301,
         TLS_V11            = 0x0302,
         TLS_V12            = 0x0303,

         DTLS_V10           = 0xFEFF,
         DTLS_V12           = 0xFEFD
      };

      /**
      * @return latest known TLS version
      */
      static Protocol_Version latest_tls_version()
         {
         return Protocol_Version(TLS_V12);
         }

      /**
      * @return latest known DTLS version
      */
      static Protocol_Version latest_dtls_version()
         {
         return Protocol_Version(DTLS_V12);
         }

      Protocol_Version() : m_version(0) {}

      explicit Protocol_Version(uint16_t code) : m_version(code) {}

      /**
      * @param named_version a specific named version of the protocol
      */
      Protocol_Version(Version_Code named_version) :
         Protocol_Version(static_cast<uint16_t>(named_version)) {}

      /**
      * @param major the major version
      * @param minor the minor version
      */
      Protocol_Version(uint8_t major, uint8_t minor) :
         Protocol_Version(static_cast<uint16_t>((static_cast<uint16_t>(major) << 8) | minor)) {}

      /**
      * @return true if this is a valid protocol version
      */
      bool valid() const { return (m_version != 0); }

      /**
      * @return true if this is a protocol version we know about
      */
      bool known_version() const;

      /**
      * @return major version of the protocol version
      */
      uint8_t major_version() const { return static_cast<uint8_t>(m_version >> 8); }

      /**
      * @return minor version of the protocol version
      */
      uint8_t minor_version() const { return static_cast<uint8_t>(m_version & 0xFF); }

      /**
      * @return the version code
      */
      uint16_t version_code() const { return m_version; }

      /**
      * @return human-readable description of this version
      */
      std::string to_string() const;

      /**
      * @return true iff this is a DTLS version
      */
      bool is_datagram_protocol() const;

      /**
      * @return true if this version supports negotiable signature algorithms
      */
      bool supports_negotiable_signature_algorithms() const;

      /**
      * @return true if this version uses explicit IVs for block ciphers
      */
      bool supports_explicit_cbc_ivs() const;

      /**
      * @return true if this version uses a ciphersuite specific PRF
      */
      bool supports_ciphersuite_specific_prf() const;

      bool supports_aead_modes() const;

      /**
      * @return if this version is equal to other
      */
      bool operator==(const Protocol_Version& other) const
         {
         return (m_version == other.m_version);
         }

      /**
      * @return if this version is not equal to other
      */
      bool operator!=(const Protocol_Version& other) const
         {
         return (m_version != other.m_version);
         }

      /**
      * @return if this version is later than other
      */
      bool operator>(const Protocol_Version& other) const;

      /**
      * @return if this version is later than or equal to other
      */
      bool operator>=(const Protocol_Version& other) const
         {
         return (*this == other || *this > other);
         }

   private:
      uint16_t m_version;
   };

}

}

namespace Botan {

namespace TLS {

/**
* Ciphersuite Information
*/
class BOTAN_PUBLIC_API(2,0) Ciphersuite final
   {
   public:
      /**
      * Convert an SSL/TLS ciphersuite to algorithm fields
      * @param suite the ciphersuite code number
      * @return ciphersuite object
      */
      static Ciphersuite by_id(uint16_t suite);

      /**
      * Convert an SSL/TLS ciphersuite name to algorithm fields
      * @param name the IANA name for the desired ciphersuite
      * @return ciphersuite object
      */
      static Ciphersuite from_name(const std::string& name);

      /**
      * Returns true iff this suite is a known SCSV
      */
      static bool is_scsv(uint16_t suite);

      /**
      * Generate a static list of all known ciphersuites and return it.
      *
      * @return list of all known ciphersuites
      */
      static const std::vector<Ciphersuite>& all_known_ciphersuites();

      /**
      * Formats the ciphersuite back to an RFC-style ciphersuite string
      * @return RFC ciphersuite string identifier
      */
      std::string to_string() const { return m_iana_id; }

      /**
      * @return ciphersuite number
      */
      uint16_t ciphersuite_code() const { return m_ciphersuite_code; }

      /**
      * @return true if this is a PSK ciphersuite
      */
      bool psk_ciphersuite() const;

      /**
      * @return true if this is an ECC ciphersuite
      */
      bool ecc_ciphersuite() const;

      /**
       * @return true if this suite uses a CBC cipher
       */
      bool cbc_ciphersuite() const;

      bool signature_used() const;

      /**
      * @return key exchange algorithm used by this ciphersuite
      */
      std::string kex_algo() const { return kex_method_to_string(kex_method()); }

      Kex_Algo kex_method() const { return m_kex_algo; }

      /**
      * @return signature algorithm used by this ciphersuite
      */
      std::string sig_algo() const { return auth_method_to_string(auth_method()); }

      Auth_Method auth_method() const { return m_auth_method; }

      /**
      * @return symmetric cipher algorithm used by this ciphersuite
      */
      std::string cipher_algo() const { return m_cipher_algo; }

      /**
      * @return message authentication algorithm used by this ciphersuite
      */
      std::string mac_algo() const { return m_mac_algo; }

      std::string prf_algo() const
         {
         return kdf_algo_to_string(m_prf_algo);
         }

      /**
      * @return cipher key length used by this ciphersuite
      */
      size_t cipher_keylen() const { return m_cipher_keylen; }

      size_t nonce_bytes_from_handshake() const;

      size_t nonce_bytes_from_record(Protocol_Version version) const;

      Nonce_Format nonce_format() const { return m_nonce_format; }

      size_t mac_keylen() const { return m_mac_keylen; }

      /**
      * @return true if this is a valid/known ciphersuite
      */
      bool valid() const { return m_usable; }

      bool usable_in_version(Protocol_Version version) const;

      bool operator<(const Ciphersuite& o) const { return ciphersuite_code() < o.ciphersuite_code(); }
      bool operator<(const uint16_t c) const { return ciphersuite_code() < c; }

      Ciphersuite() = default;

   private:

      bool is_usable() const;

      Ciphersuite(uint16_t ciphersuite_code,
                  const char* iana_id,
                  Auth_Method auth_method,
                  Kex_Algo kex_algo,
                  const char* cipher_algo,
                  size_t cipher_keylen,
                  const char* mac_algo,
                  size_t mac_keylen,
                  KDF_Algo prf_algo,
                  Nonce_Format nonce_format) :
         m_ciphersuite_code(ciphersuite_code),
         m_iana_id(iana_id),
         m_auth_method(auth_method),
         m_kex_algo(kex_algo),
         m_prf_algo(prf_algo),
         m_nonce_format(nonce_format),
         m_cipher_algo(cipher_algo),
         m_mac_algo(mac_algo),
         m_cipher_keylen(cipher_keylen),
         m_mac_keylen(mac_keylen)
         {
         m_usable = is_usable();
         }

      uint16_t m_ciphersuite_code = 0;

      /*
      All of these const char* strings are references to compile time
      constants in tls_suite_info.cpp
      */
      const char* m_iana_id = nullptr;

      Auth_Method m_auth_method = Auth_Method::ANONYMOUS;
      Kex_Algo m_kex_algo = Kex_Algo::STATIC_RSA;
      KDF_Algo m_prf_algo = KDF_Algo::SHA_1;
      Nonce_Format m_nonce_format = Nonce_Format::CBC_MODE;

      const char* m_cipher_algo = nullptr;
      const char* m_mac_algo = nullptr;

      size_t m_cipher_keylen = 0;
      size_t m_mac_keylen = 0;

      bool m_usable = false;
   };

}

}

//BOTAN_FUTURE_INTERNAL_HEADER(tls_magic.h)

namespace Botan {

namespace TLS {

/**
* Protocol Constants for SSL/TLS
*/
enum Size_Limits {
   TLS_HEADER_SIZE    = 5,
   DTLS_HEADER_SIZE   = TLS_HEADER_SIZE + 8,

   MAX_PLAINTEXT_SIZE = 16*1024,
   MAX_COMPRESSED_SIZE = MAX_PLAINTEXT_SIZE + 1024,
   MAX_CIPHERTEXT_SIZE = MAX_COMPRESSED_SIZE + 1024,
};

// This will become an enum class in a future major release
enum Connection_Side { CLIENT = 1, SERVER = 2 };

// This will become an enum class in a future major release
enum Record_Type {
   CHANGE_CIPHER_SPEC = 20,
   ALERT              = 21,
   HANDSHAKE          = 22,
   APPLICATION_DATA   = 23,

   NO_RECORD          = 256
};

// This will become an enum class in a future major release
enum Handshake_Type {
   HELLO_REQUEST        = 0,
   CLIENT_HELLO         = 1,
   SERVER_HELLO         = 2,
   HELLO_VERIFY_REQUEST = 3,
   NEW_SESSION_TICKET   = 4, // RFC 5077
   CERTIFICATE          = 11,
   SERVER_KEX           = 12,
   CERTIFICATE_REQUEST  = 13,
   SERVER_HELLO_DONE    = 14,
   CERTIFICATE_VERIFY   = 15,
   CLIENT_KEX           = 16,
   FINISHED             = 20,

   CERTIFICATE_URL      = 21,
   CERTIFICATE_STATUS   = 22,

   HANDSHAKE_CCS        = 254, // Not a wire value
   HANDSHAKE_NONE       = 255  // Null value
};

const char* handshake_type_to_string(Handshake_Type t);

}

}

namespace Botan {

namespace TLS {

/**
* Represents information known about a TLS server.
*/
class BOTAN_PUBLIC_API(2,0) Server_Information final
   {
   public:
      /**
      * An empty server info - nothing known
      */
      Server_Information() : m_hostname(""), m_service(""), m_port(0) {}

      /**
      * @param hostname the host's DNS name, if known
      * @param port specifies the protocol port of the server (eg for
      *        TCP/UDP). Zero represents unknown.
      */
      Server_Information(const std::string& hostname,
                        uint16_t port = 0) :
         m_hostname(hostname), m_service(""), m_port(port) {}

      /**
      * @param hostname the host's DNS name, if known
      * @param service is a text string of the service type
      *        (eg "https", "tor", or "git")
      * @param port specifies the protocol port of the server (eg for
      *        TCP/UDP). Zero represents unknown.
      */
      Server_Information(const std::string& hostname,
                        const std::string& service,
                        uint16_t port = 0) :
         m_hostname(hostname), m_service(service), m_port(port) {}

      /**
      * @return the host's DNS name, if known
      */
      std::string hostname() const { return m_hostname; }

      /**
      * @return text string of the service type, e.g.,
      * "https", "tor", or "git"
      */
      std::string service() const { return m_service; }

      /**
      * @return the protocol port of the server, or zero if unknown
      */
      uint16_t port() const { return m_port; }

      /**
      * @return whether the hostname is known
      */
      bool empty() const { return m_hostname.empty(); }

   private:
      std::string m_hostname, m_service;
      uint16_t m_port;
   };

inline bool operator==(const Server_Information& a, const Server_Information& b)
   {
   return (a.hostname() == b.hostname()) &&
          (a.service() == b.service()) &&
          (a.port() == b.port());

   }

inline bool operator!=(const Server_Information& a, const Server_Information& b)
   {
   return !(a == b);
   }

inline bool operator<(const Server_Information& a, const Server_Information& b)
   {
   if(a.hostname() != b.hostname())
      return (a.hostname() < b.hostname());
   if(a.service() != b.service())
      return (a.service() < b.service());
   if(a.port() != b.port())
      return (a.port() < b.port());
   return false; // equal
   }

}

}

namespace Botan {

namespace TLS {

/**
* Class representing a TLS session state
*/
class BOTAN_PUBLIC_API(2,0) Session final
   {
   public:

      /**
      * Uninitialized session
      */
      Session() :
         m_start_time(std::chrono::system_clock::time_point::min()),
         m_version(),
         m_ciphersuite(0),
         m_connection_side(static_cast<Connection_Side>(0)),
         m_srtp_profile(0),
         m_extended_master_secret(false),
         m_encrypt_then_mac(false)
            {}

      /**
      * New session (sets session start time)
      */
      Session(const std::vector<uint8_t>& session_id,
              const secure_vector<uint8_t>& master_secret,
              Protocol_Version version,
              uint16_t ciphersuite,
              Connection_Side side,
              bool supports_extended_master_secret,
              bool supports_encrypt_then_mac,
              const std::vector<X509_Certificate>& peer_certs,
              const std::vector<uint8_t>& session_ticket,
              const Server_Information& server_info,
              const std::string& srp_identifier,
              uint16_t srtp_profile);

      /**
      * Load a session from DER representation (created by DER_encode)
      * @param ber DER representation buffer
      * @param ber_len size of buffer in bytes
      */
      Session(const uint8_t ber[], size_t ber_len);

      /**
      * Load a session from PEM representation (created by PEM_encode)
      * @param pem PEM representation
      */
      explicit Session(const std::string& pem);

      /**
      * Encode this session data for storage
      * @warning if the master secret is compromised so is the
      * session traffic
      */
      secure_vector<uint8_t> DER_encode() const;

      /**
      * Encrypt a session (useful for serialization or session tickets)
      */
      std::vector<uint8_t> encrypt(const SymmetricKey& key,
                                RandomNumberGenerator& rng) const;


      /**
      * Decrypt a session created by encrypt
      * @param ctext the ciphertext returned by encrypt
      * @param ctext_size the size of ctext in bytes
      * @param key the same key used by the encrypting side
      */
      static Session decrypt(const uint8_t ctext[],
                             size_t ctext_size,
                             const SymmetricKey& key);

      /**
      * Decrypt a session created by encrypt
      * @param ctext the ciphertext returned by encrypt
      * @param key the same key used by the encrypting side
      */
      static inline Session decrypt(const std::vector<uint8_t>& ctext,
                                    const SymmetricKey& key)
         {
         return Session::decrypt(ctext.data(), ctext.size(), key);
         }

      /**
      * Encode this session data for storage
      * @warning if the master secret is compromised so is the
      * session traffic
      */
      std::string PEM_encode() const;

      /**
      * Get the version of the saved session
      */
      Protocol_Version version() const { return m_version; }

      /**
      * Get the ciphersuite code of the saved session
      */
      uint16_t ciphersuite_code() const { return m_ciphersuite; }

      /**
      * Get the ciphersuite info of the saved session
      */
      Ciphersuite ciphersuite() const { return Ciphersuite::by_id(m_ciphersuite); }

      /**
      * Get which side of the connection the resumed session we are/were
      * acting as.
      */
      Connection_Side side() const { return m_connection_side; }

      /**
      * Get the SRP identity (if sent by the client in the initial handshake)
      */
      const std::string& srp_identifier() const { return m_srp_identifier; }

      /**
      * Get the saved master secret
      */
      const secure_vector<uint8_t>& master_secret() const { return m_master_secret; }

      /**
      * Get the session identifier
      */
      const std::vector<uint8_t>& session_id() const { return m_identifier; }

      /**
      * Get the negotiated DTLS-SRTP algorithm (RFC 5764)
      */
      uint16_t dtls_srtp_profile() const { return m_srtp_profile; }

      bool supports_extended_master_secret() const { return m_extended_master_secret; }

      bool supports_encrypt_then_mac() const { return m_encrypt_then_mac; }

      /**
      * Return the certificate chain of the peer (possibly empty)
      */
      const std::vector<X509_Certificate>& peer_certs() const { return m_peer_certs; }

      /**
      * Get the wall clock time this session began
      */
      std::chrono::system_clock::time_point start_time() const { return m_start_time; }

      /**
      * Return how long this session has existed (in seconds)
      */
      std::chrono::seconds session_age() const;

      /**
      * Return the session ticket the server gave us
      */
      const std::vector<uint8_t>& session_ticket() const { return m_session_ticket; }

      /**
      * @return information about the TLS server
      */
      const Server_Information& server_info() const { return m_server_info; }

   private:
      enum { TLS_SESSION_PARAM_STRUCT_VERSION = 20160812 };

      std::chrono::system_clock::time_point m_start_time;

      std::vector<uint8_t> m_identifier;
      std::vector<uint8_t> m_session_ticket; // only used by client side
      secure_vector<uint8_t> m_master_secret;

      Protocol_Version m_version;
      uint16_t m_ciphersuite;
      Connection_Side m_connection_side;
      uint16_t m_srtp_profile;
      bool m_extended_master_secret;
      bool m_encrypt_then_mac;

      std::vector<X509_Certificate> m_peer_certs;
      Server_Information m_server_info; // optional
      std::string m_srp_identifier; // optional
   };

}

}

namespace Botan {

namespace TLS {

/**
* Session_Manager is an interface to systems which can save
* session parameters for supporting session resumption.
*
* Saving sessions is done on a best-effort basis; an implementation is
* allowed to drop sessions due to space constraints.
*
* Implementations should strive to be thread safe
*/
class BOTAN_PUBLIC_API(2,0) Session_Manager
   {
   public:
      /**
      * Try to load a saved session (using session ID)
      * @param session_id the session identifier we are trying to resume
      * @param session will be set to the saved session data (if found),
               or not modified if not found
      * @return true if session was modified
      */
      virtual bool load_from_session_id(const std::vector<uint8_t>& session_id,
                                        Session& session) = 0;

      /**
      * Try to load a saved session (using info about server)
      * @param info the information about the server
      * @param session will be set to the saved session data (if found),
               or not modified if not found
      * @return true if session was modified
      */
      virtual bool load_from_server_info(const Server_Information& info,
                                         Session& session) = 0;

      /**
      * Remove this session id from the cache, if it exists
      */
      virtual void remove_entry(const std::vector<uint8_t>& session_id) = 0;

      /**
      * Remove all sessions from the cache, return number of sessions deleted
      */
      virtual size_t remove_all() = 0;

      /**
      * Save a session on a best effort basis; the manager may not in
      * fact be able to save the session for whatever reason; this is
      * not an error. Caller cannot assume that calling save followed
      * immediately by load_from_* will result in a successful lookup.
      *
      * @param session to save
      */
      virtual void save(const Session& session) = 0;

      /**
      * Return the allowed lifetime of a session; beyond this time,
      * sessions are not resumed. Returns 0 if unknown/no explicit
      * expiration policy.
      */
      virtual std::chrono::seconds session_lifetime() const = 0;

      virtual ~Session_Manager() = default;
   };

/**
* An implementation of Session_Manager that does not save sessions at
* all, preventing session resumption.
*/
class BOTAN_PUBLIC_API(2,0) Session_Manager_Noop final : public Session_Manager
   {
   public:
      bool load_from_session_id(const std::vector<uint8_t>&, Session&) override
         { return false; }

      bool load_from_server_info(const Server_Information&, Session&) override
         { return false; }

      void remove_entry(const std::vector<uint8_t>&) override {}

      size_t remove_all() override { return 0; }

      void save(const Session&) override {}

      std::chrono::seconds session_lifetime() const override
         { return std::chrono::seconds(0); }
   };

/**
* An implementation of Session_Manager that saves values in memory.
*/
class BOTAN_PUBLIC_API(2,0) Session_Manager_In_Memory final : public Session_Manager
   {
   public:
      /**
      * @param rng a RNG used for generating session key and for
      *        session encryption
      * @param max_sessions a hint on the maximum number of sessions
      *        to keep in memory at any one time. (If zero, don't cap)
      * @param session_lifetime sessions are expired after this many
      *        seconds have elapsed from initial handshake.
      */
      Session_Manager_In_Memory(RandomNumberGenerator& rng,
                                size_t max_sessions = 1000,
                                std::chrono::seconds session_lifetime =
                                   std::chrono::seconds(7200));

      bool load_from_session_id(const std::vector<uint8_t>& session_id,
                                Session& session) override;

      bool load_from_server_info(const Server_Information& info,
                                 Session& session) override;

      void remove_entry(const std::vector<uint8_t>& session_id) override;

      size_t remove_all() override;

      void save(const Session& session_data) override;

      std::chrono::seconds session_lifetime() const override
         { return m_session_lifetime; }

   private:
      bool load_from_session_str(const std::string& session_str,
                                 Session& session);

      mutex_type m_mutex;

      size_t m_max_sessions;

      std::chrono::seconds m_session_lifetime;

      RandomNumberGenerator& m_rng;
      secure_vector<uint8_t> m_session_key;

      std::map<std::string, std::vector<uint8_t>> m_sessions; // hex(session_id) -> session
      std::map<Server_Information, std::string> m_info_sessions;
   };

}

}

namespace Botan {

class Certificate_Store;
class X509_Certificate;

namespace OCSP {

class Response;

}

namespace TLS {

class Handshake_Message;
class Policy;
class Extensions;
class Certificate_Status_Request;

/**
* Encapsulates the callbacks that a TLS channel will make which are due to
* channel specific operations.
*/
class BOTAN_PUBLIC_API(2,0) Callbacks
   {
   public:
       virtual ~Callbacks() = default;

       /**
       * Mandatory callback: output function
       * The channel will call this with data which needs to be sent to the peer
       * (eg, over a socket or some other form of IPC). The array will be overwritten
       * when the function returns so a copy must be made if the data cannot be
       * sent immediately.
       *
       * @param data the vector of data to send
       *
       * @param size the number of bytes to send
       */
       virtual void tls_emit_data(const uint8_t data[], size_t size) = 0;

       /**
       * Mandatory callback: process application data
       * Called when application data record is received from the peer.
       * Again the array is overwritten immediately after the function returns.
       *
       * @param seq_no the underlying TLS/DTLS record sequence number
       *
       * @param data the vector containing the received record
       *
       * @param size the length of the received record, in bytes
       */
       virtual void tls_record_received(uint64_t seq_no, const uint8_t data[], size_t size) = 0;

       /**
       * Mandatory callback: alert received
       * Called when an alert is received from the peer
       * If fatal, the connection is closing. If not fatal, the connection may
       * still be closing (depending on the error and the peer).
       *
       * @param alert the source of the alert
       */
       virtual void tls_alert(Alert alert) = 0;

       /**
       * Mandatory callback: session established
       * Called when a session is established. Throw an exception to abort
       * the connection.
       *
       * @param session the session descriptor
       *
       * @return return false to prevent the session from being cached,
       * return true to cache the session in the configured session manager
       */
       virtual bool tls_session_established(const Session& session) = 0;

       /**
       * Optional callback: session activated
       * Called when a session is active and can be written to
       */
       virtual void tls_session_activated() {}

       /**
       * Optional callback with default impl: verify cert chain
       *
       * Default implementation performs a standard PKIX validation
       * and initiates network OCSP request for end-entity cert.
       * Override to provide different behavior.
       *
       * Check the certificate chain is valid up to a trusted root, and
       * optionally (if hostname != "") that the hostname given is
       * consistent with the leaf certificate.
       *
       * This function should throw an exception derived from
       * std::exception with an informative what() result if the
       * certificate chain cannot be verified.
       *
       * @param cert_chain specifies a certificate chain leading to a
       *        trusted root CA certificate.
       * @param ocsp_responses the server may have provided some
       * @param trusted_roots the list of trusted certificates
       * @param usage what this cert chain is being used for
       *        Usage_Type::TLS_SERVER_AUTH for server chains,
       *        Usage_Type::TLS_CLIENT_AUTH for client chains,
       *        Usage_Type::UNSPECIFIED for other uses
       * @param hostname when authenticating a server, this is the hostname
       *        the client requested (eg via SNI). When authenticating a client,
       *        this is the server name the client is authenticating *to*.
       *        Empty in other cases or if no hostname was used.
       * @param policy the TLS policy associated with the session being authenticated
       *        using the certificate chain
       */
       virtual void tls_verify_cert_chain(
          const std::vector<X509_Certificate>& cert_chain,
          const std::vector<std::shared_ptr<const OCSP::Response>>& ocsp_responses,
          const std::vector<Certificate_Store*>& trusted_roots,
          Usage_Type usage,
          const std::string& hostname,
          const TLS::Policy& policy);

       /**
       * Called by default `tls_verify_cert_chain` to get the timeout to use for OCSP
       * requests. Return 0 to disable online OCSP checks.
       *
       * This function should not be "const" since the implementation might need
       * to perform some side effecting operation to compute the result.
       */
       virtual std::chrono::milliseconds tls_verify_cert_chain_ocsp_timeout() const
          {
          return std::chrono::milliseconds(0);
          }

      /**
       * Called by the TLS server whenever the client included the
       * status_request extension (see RFC 6066, a.k.a OCSP stapling)
       * in the ClientHello.
       *
       * @return the encoded OCSP response to be sent to the client which
       * indicates the revocation status of the server certificate. Return an
       * empty vector to indicate that no response is available, and thus
       * suppress the Certificate_Status message.
       */
       virtual std::vector<uint8_t> tls_provide_cert_status(const std::vector<X509_Certificate>& chain,
                                                            const Certificate_Status_Request& csr)
          {
          BOTAN_UNUSED(chain);
          BOTAN_UNUSED(csr);
          return std::vector<uint8_t>();
          }

       /**
       * Optional callback with default impl: sign a message
       *
       * Default implementation uses PK_Signer::sign_message().
       * Override to provide a different approach, e.g. using an external device.
       *
       * @param key the private key of the signer
       * @param rng a random number generator
       * @param emsa the encoding method to be applied to the message
       * @param format the signature format
       * @param msg the input data for the signature
       *
       * @return the signature
       */
       virtual std::vector<uint8_t> tls_sign_message(
          const Private_Key& key,
          RandomNumberGenerator& rng,
          const std::string& emsa,
          Signature_Format format,
          const std::vector<uint8_t>& msg);

       /**
       * Optional callback with default impl: verify a message signature
       *
       * Default implementation uses PK_Verifier::verify_message().
       * Override to provide a different approach, e.g. using an external device.
       *
       * @param key the public key of the signer
       * @param emsa the encoding method to be applied to the message
       * @param format the signature format
       * @param msg the input data for the signature
       * @param sig the signature to be checked
       *
       * @return true if the signature is valid, false otherwise
       */
       virtual bool tls_verify_message(
          const Public_Key& key,
          const std::string& emsa,
          Signature_Format format,
          const std::vector<uint8_t>& msg,
          const std::vector<uint8_t>& sig);

       /**
       * Optional callback with default impl: client side DH agreement
       *
       * Default implementation uses PK_Key_Agreement::derive_key().
       * Override to provide a different approach, e.g. using an external device.
       *
       * @param modulus the modulus p of the discrete logarithm group
       * @param generator the generator of the DH subgroup
       * @param peer_public_value the public value of the peer
       * @param policy the TLS policy associated with the session being established
       * @param rng a random number generator
       *
       * @return a pair consisting of the agreed raw secret and our public value
       */
       virtual std::pair<secure_vector<uint8_t>, std::vector<uint8_t>> tls_dh_agree(
          const std::vector<uint8_t>& modulus,
          const std::vector<uint8_t>& generator,
          const std::vector<uint8_t>& peer_public_value,
          const Policy& policy,
          RandomNumberGenerator& rng);

       /**
       * Optional callback with default impl: client side ECDH agreement
       *
       * Default implementation uses PK_Key_Agreement::derive_key().
       * Override to provide a different approach, e.g. using an external device.
       *
       * @param curve_name the name of the elliptic curve
       * @param peer_public_value the public value of the peer
       * @param policy the TLS policy associated with the session being established
       * @param rng a random number generator
       * @param compressed the compression preference for our public value
       *
       * @return a pair consisting of the agreed raw secret and our public value
       */
       virtual std::pair<secure_vector<uint8_t>, std::vector<uint8_t>> tls_ecdh_agree(
          const std::string& curve_name,
          const std::vector<uint8_t>& peer_public_value,
          const Policy& policy,
          RandomNumberGenerator& rng,
          bool compressed);

       /**
       * Optional callback: inspect handshake message
       * Throw an exception to abort the handshake.
       * Default simply ignores the message.
       *
       * @param message the handshake message
       */
       virtual void tls_inspect_handshake_msg(const Handshake_Message& message);

       /**
       * Optional callback for server: choose ALPN protocol
       * ALPN (RFC 7301) works by the client sending a list of application
       * protocols it is willing to negotiate. The server then selects which
       * protocol to use, which is not necessarily even on the list that
       * the client sent.
       *
       * @param client_protos the vector of protocols the client is willing to negotiate
       *
       * @return the protocol selected by the server, which need not be on the
       * list that the client sent; if this is the empty string, the server ignores the
       * client ALPN extension. Default return value is empty string.
       */
       virtual std::string tls_server_choose_app_protocol(const std::vector<std::string>& client_protos);

       /**
       * Optional callback: examine/modify Extensions before sending.
       *
       * Both client and server will call this callback on the Extensions object
       * before serializing it in the client/server hellos. This allows an
       * application to modify which extensions are sent during the
       * handshake.
       *
       * Default implementation does nothing.
       *
       * @param extn the extensions
       * @param which_side will be CLIENT or SERVER which is the current
       * applications role in the exchange.
       */
       virtual void tls_modify_extensions(Extensions& extn, Connection_Side which_side);

       /**
       * Optional callback: examine peer extensions.
       *
       * Both client and server will call this callback with the Extensions
       * object after receiving it from the peer. This allows examining the
       * Extensions, for example to implement a custom extension. It also allows
       * an application to require that a particular extension be implemented;
       * throw an exception from this function to abort the handshake.
       *
       * Default implementation does nothing.
       *
       * @param extn the extensions
       * @param which_side will be CLIENT if these are are the clients extensions (ie we are
       *        the server) or SERVER if these are the server extensions (we are the client).
       */
       virtual void tls_examine_extensions(const Extensions& extn, Connection_Side which_side);

       /**
       * Optional callback: decode TLS group ID
       *
       * TLS uses a 16-bit field to identify ECC and DH groups. This callback
       * handles the decoding. You only need to implement this if you are using
       * a custom ECC or DH group (this is extremely uncommon).
       *
       * Default implementation uses the standard (IETF-defined) mappings.
       */
       virtual std::string tls_decode_group_param(Group_Params group_param);

       /**
       * Optional callback: return peer network identity
       *
       * There is no expected or specified format. The only expectation is this
       * function will return a unique value. For example returning the peer
       * host IP and port.
       *
       * This is used to bind the DTLS cookie to a particular network identity.
       * It is only called if the dtls-cookie-secret PSK is also defined.
       */
       virtual std::string tls_peer_network_identity();

       /**
       * Optional callback: error logging. (not currently called)
       * @param err An error message related to this connection.
       */
       virtual void tls_log_error(const char* err)
          {
          BOTAN_UNUSED(err);
          }

       /**
       * Optional callback: debug logging. (not currently called)
       * @param what Some hopefully informative string
       */
       virtual void tls_log_debug(const char* what)
          {
          BOTAN_UNUSED(what);
          }

       /**
       * Optional callback: debug logging taking a buffer. (not currently called)
       * @param descr What this buffer is
       * @param val the bytes
       * @param val_len length of val
       */
       virtual void tls_log_debug_bin(const char* descr, const uint8_t val[], size_t val_len)
          {
          BOTAN_UNUSED(descr, val, val_len);
          }
   };

/**
* TLS::Callbacks using std::function for compatability with the old API signatures.
* This type is only provided for backward compatibility.
* New implementations should derive from TLS::Callbacks instead.
*/
class BOTAN_PUBLIC_API(2,0) Compat_Callbacks final : public Callbacks
   {
   public:
      typedef std::function<void (const uint8_t[], size_t)> output_fn;
      typedef std::function<void (const uint8_t[], size_t)> data_cb;
      typedef std::function<void (Alert, const uint8_t[], size_t)> alert_cb;
      typedef std::function<bool (const Session&)> handshake_cb;
      typedef std::function<void (const Handshake_Message&)> handshake_msg_cb;
      typedef std::function<std::string (std::vector<std::string>)> next_protocol_fn;

      /**
       * @param data_output_fn is called with data for the outbound socket
       *
       * @param app_data_cb is called when new application data is received
       *
       * @param recv_alert_cb is called when a TLS alert is received
       *
       * @param hs_cb is called when a handshake is completed
       *
       * @param hs_msg_cb is called for each handshake message received
       *
       * @param next_proto is called with ALPN protocol data sent by the client
       */
       BOTAN_DEPRECATED("Use TLS::Callbacks (virtual interface).")
       Compat_Callbacks(output_fn data_output_fn, data_cb app_data_cb, alert_cb recv_alert_cb,
                        handshake_cb hs_cb, handshake_msg_cb hs_msg_cb = nullptr,
                        next_protocol_fn next_proto = nullptr)
          : m_output_function(data_output_fn), m_app_data_cb(app_data_cb),
            m_alert_cb(std::bind(recv_alert_cb, std::placeholders::_1, nullptr, 0)),
            m_hs_cb(hs_cb), m_hs_msg_cb(hs_msg_cb), m_next_proto(next_proto) {}

       BOTAN_DEPRECATED("Use TLS::Callbacks (virtual interface).")
       Compat_Callbacks(output_fn data_output_fn, data_cb app_data_cb,
                        std::function<void (Alert)> recv_alert_cb,
                        handshake_cb hs_cb,
                        handshake_msg_cb hs_msg_cb = nullptr,
                        next_protocol_fn next_proto = nullptr)
          : m_output_function(data_output_fn), m_app_data_cb(app_data_cb),
            m_alert_cb(recv_alert_cb),
            m_hs_cb(hs_cb), m_hs_msg_cb(hs_msg_cb), m_next_proto(next_proto) {}

       enum class SILENCE_DEPRECATION_WARNING { PLEASE = 0 };
       Compat_Callbacks(SILENCE_DEPRECATION_WARNING,
                        output_fn data_output_fn, data_cb app_data_cb,
                        std::function<void (Alert)> recv_alert_cb,
                        handshake_cb hs_cb,
                        handshake_msg_cb hs_msg_cb = nullptr,
                        next_protocol_fn next_proto = nullptr)
          : m_output_function(data_output_fn),
            m_app_data_cb(app_data_cb),
            m_alert_cb(recv_alert_cb),
            m_hs_cb(hs_cb),
            m_hs_msg_cb(hs_msg_cb),
            m_next_proto(next_proto) {}

       Compat_Callbacks(SILENCE_DEPRECATION_WARNING,
                        output_fn data_output_fn, data_cb app_data_cb, alert_cb recv_alert_cb,
                        handshake_cb hs_cb, handshake_msg_cb hs_msg_cb = nullptr,
                        next_protocol_fn next_proto = nullptr)
          : m_output_function(data_output_fn), m_app_data_cb(app_data_cb),
            m_alert_cb(std::bind(recv_alert_cb, std::placeholders::_1, nullptr, 0)),
            m_hs_cb(hs_cb), m_hs_msg_cb(hs_msg_cb), m_next_proto(next_proto) {}


       void tls_emit_data(const uint8_t data[], size_t size) override
          {
          BOTAN_ASSERT(m_output_function != nullptr,
                       "Invalid TLS output function callback.");
          m_output_function(data, size);
          }

       void tls_record_received(uint64_t /*seq_no*/, const uint8_t data[], size_t size) override
          {
          BOTAN_ASSERT(m_app_data_cb != nullptr,
                       "Invalid TLS app data callback.");
          m_app_data_cb(data, size);
          }

       void tls_alert(Alert alert) override
          {
          BOTAN_ASSERT(m_alert_cb != nullptr,
                       "Invalid TLS alert callback.");
          m_alert_cb(alert);
          }

       bool tls_session_established(const Session& session) override
          {
          BOTAN_ASSERT(m_hs_cb != nullptr,
                       "Invalid TLS handshake callback.");
          return m_hs_cb(session);
          }

       std::string tls_server_choose_app_protocol(const std::vector<std::string>& client_protos) override
          {
          if(m_next_proto != nullptr) { return m_next_proto(client_protos); }
          return "";
          }

       void tls_inspect_handshake_msg(const Handshake_Message& hmsg) override
          {
          // The handshake message callback is optional so we can
          // not assume it has been set.
          if(m_hs_msg_cb != nullptr) { m_hs_msg_cb(hmsg); }
          }

    private:
         const output_fn m_output_function;
         const data_cb m_app_data_cb;
         const std::function<void (Alert)> m_alert_cb;
         const handshake_cb m_hs_cb;
         const handshake_msg_cb m_hs_msg_cb;
         const next_protocol_fn m_next_proto;
   };

}

}

namespace Botan {

namespace TLS {

class Connection_Cipher_State;
class Connection_Sequence_Numbers;
class Handshake_State;
class Handshake_Message;
class Client_Hello;
class Server_Hello;
class Policy;

/**
* Generic interface for TLS endpoint
*/
class BOTAN_PUBLIC_API(2,0) Channel
   {
   public:
      typedef std::function<void (const uint8_t[], size_t)> output_fn;
      typedef std::function<void (const uint8_t[], size_t)> data_cb;
      typedef std::function<void (Alert, const uint8_t[], size_t)> alert_cb;
      typedef std::function<bool (const Session&)> handshake_cb;
      typedef std::function<void (const Handshake_Message&)> handshake_msg_cb;
      static size_t IO_BUF_DEFAULT_SIZE;

      /**
      * Set up a new TLS session
      *
      * @param callbacks contains a set of callback function references
      *        required by the TLS endpoint.
      * @param session_manager manages session state
      * @param rng a random number generator
      * @param policy specifies other connection policy information
      * @param is_server whether this is a server session or not
      * @param is_datagram whether this is a DTLS session
      * @param io_buf_sz This many bytes of memory will
      *        be preallocated for the read and write buffers. Smaller
      *        values just mean reallocations and copies are more likely.
      */
      Channel(Callbacks& callbacks,
              Session_Manager& session_manager,
              RandomNumberGenerator& rng,
              const Policy& policy,
              bool is_server,
              bool is_datagram,
              size_t io_buf_sz = IO_BUF_DEFAULT_SIZE);

      /**
       * DEPRECATED. This constructor is only provided for backward
       * compatibility and should not be used in new implementations.
       * (Not marked deprecated since it is only called internally, by
       * other deprecated constructors)
       */
      Channel(output_fn out,
              data_cb app_data_cb,
              alert_cb alert_cb,
              handshake_cb hs_cb,
              handshake_msg_cb hs_msg_cb,
              Session_Manager& session_manager,
              RandomNumberGenerator& rng,
              const Policy& policy,
              bool is_server,
              bool is_datagram,
              size_t io_buf_sz = IO_BUF_DEFAULT_SIZE);

      Channel(const Channel&) = delete;

      Channel& operator=(const Channel&) = delete;

      virtual ~Channel();

      /**
      * Inject TLS traffic received from counterparty
      * @return a hint as the how many more bytes we need to process the
      *         current record (this may be 0 if on a record boundary)
      */
      size_t received_data(const uint8_t buf[], size_t buf_size);

      /**
      * Inject TLS traffic received from counterparty
      * @return a hint as the how many more bytes we need to process the
      *         current record (this may be 0 if on a record boundary)
      */
      size_t received_data(const std::vector<uint8_t>& buf);

      /**
      * Inject plaintext intended for counterparty
      * Throws an exception if is_active() is false
      */
      void send(const uint8_t buf[], size_t buf_size);

      /**
      * Inject plaintext intended for counterparty
      * Throws an exception if is_active() is false
      */
      void send(const std::string& val);

      /**
      * Inject plaintext intended for counterparty
      * Throws an exception if is_active() is false
      */
      template<typename Alloc>
         void send(const std::vector<unsigned char, Alloc>& val)
         {
         send(val.data(), val.size());
         }

      /**
      * Send a TLS alert message. If the alert is fatal, the internal
      * state (keys, etc) will be reset.
      * @param alert the Alert to send
      */
      void send_alert(const Alert& alert);

      /**
      * Send a warning alert
      */
      void send_warning_alert(Alert::Type type) { send_alert(Alert(type, false)); }

      /**
      * Send a fatal alert
      */
      void send_fatal_alert(Alert::Type type) { send_alert(Alert(type, true)); }

      /**
      * Send a close notification alert
      */
      void close() { send_warning_alert(Alert::CLOSE_NOTIFY); }

      /**
      * @return true iff the connection is active for sending application data
      */
      bool is_active() const;

      /**
      * @return true iff the connection has been definitely closed
      */
      bool is_closed() const;

      /**
      * @return certificate chain of the peer (may be empty)
      */
      std::vector<X509_Certificate> peer_cert_chain() const;

      /**
      * Key material export (RFC 5705)
      * @param label a disambiguating label string
      * @param context a per-association context value
      * @param length the length of the desired key in bytes
      * @return key of length bytes
      */
      SymmetricKey key_material_export(const std::string& label,
                                       const std::string& context,
                                       size_t length) const;

      /**
      * Attempt to renegotiate the session
      * @param force_full_renegotiation if true, require a full renegotiation,
      * otherwise allow session resumption
      */
      void renegotiate(bool force_full_renegotiation = false);

      /**
      * @return true iff the counterparty supports the secure
      * renegotiation extensions.
      */
      bool secure_renegotiation_supported() const;

      /**
      * Perform a handshake timeout check. This does nothing unless
      * this is a DTLS channel with a pending handshake state, in
      * which case we check for timeout and potentially retransmit
      * handshake packets.
      */
      bool timeout_check();

      virtual std::string application_protocol() const = 0;

   protected:

      virtual void process_handshake_msg(const Handshake_State* active_state,
                                         Handshake_State& pending_state,
                                         Handshake_Type type,
                                         const std::vector<uint8_t>& contents,
                                         bool epoch0_restart) = 0;

      virtual void initiate_handshake(Handshake_State& state,
                                      bool force_full_renegotiation) = 0;

      virtual std::vector<X509_Certificate>
         get_peer_cert_chain(const Handshake_State& state) const = 0;

      virtual Handshake_State* new_handshake_state(class Handshake_IO* io) = 0;

      Handshake_State& create_handshake_state(Protocol_Version version);

      void inspect_handshake_message(const Handshake_Message& msg);

      void activate_session();

      void change_cipher_spec_reader(Connection_Side side);

      void change_cipher_spec_writer(Connection_Side side);

      /* secure renegotiation handling */

      void secure_renegotiation_check(const Client_Hello* client_hello);
      void secure_renegotiation_check(const Server_Hello* server_hello);

      std::vector<uint8_t> secure_renegotiation_data_for_client_hello() const;
      std::vector<uint8_t> secure_renegotiation_data_for_server_hello() const;

      RandomNumberGenerator& rng() { return m_rng; }

      Session_Manager& session_manager() { return m_session_manager; }

      const Policy& policy() const { return m_policy; }

      bool save_session(const Session& session);

      Callbacks& callbacks() const { return m_callbacks; }

      void reset_active_association_state();

   private:
      void init(size_t io_buf_sze);

      void send_record(uint8_t record_type, const std::vector<uint8_t>& record);

      void send_record_under_epoch(uint16_t epoch, uint8_t record_type,
                                   const std::vector<uint8_t>& record);

      void send_record_array(uint16_t epoch, uint8_t record_type,
                             const uint8_t input[], size_t length);

      void write_record(Connection_Cipher_State* cipher_state,
                        uint16_t epoch, uint8_t type, const uint8_t input[], size_t length);

      void reset_state();

      Connection_Sequence_Numbers& sequence_numbers() const;

      std::shared_ptr<Connection_Cipher_State> read_cipher_state_epoch(uint16_t epoch) const;

      std::shared_ptr<Connection_Cipher_State> write_cipher_state_epoch(uint16_t epoch) const;

      const Handshake_State* active_state() const { return m_active_state.get(); }

      const Handshake_State* pending_state() const { return m_pending_state.get(); }

      /* methods to handle incoming traffic through Channel::receive_data. */
      void process_handshake_ccs(const secure_vector<uint8_t>& record,
                                 uint64_t record_sequence,
                                 Record_Type record_type,
                                 Protocol_Version record_version,
                                 bool epoch0_restart);

      void process_application_data(uint64_t req_no, const secure_vector<uint8_t>& record);

      void process_alert(const secure_vector<uint8_t>& record);

      const bool m_is_server;
      const bool m_is_datagram;

      /* callbacks */
      std::unique_ptr<Compat_Callbacks> m_compat_callbacks;
      Callbacks& m_callbacks;

      /* external state */
      Session_Manager& m_session_manager;
      const Policy& m_policy;
      RandomNumberGenerator& m_rng;

      /* sequence number state */
      std::unique_ptr<Connection_Sequence_Numbers> m_sequence_numbers;

      /* pending and active connection states */
      std::unique_ptr<Handshake_State> m_active_state;
      std::unique_ptr<Handshake_State> m_pending_state;

      /* cipher states for each epoch */
      std::map<uint16_t, std::shared_ptr<Connection_Cipher_State>> m_write_cipher_states;
      std::map<uint16_t, std::shared_ptr<Connection_Cipher_State>> m_read_cipher_states;

      /* I/O buffers */
      secure_vector<uint8_t> m_writebuf;
      secure_vector<uint8_t> m_readbuf;
      secure_vector<uint8_t> m_record_buf;

      bool m_has_been_closed;
   };

}

}

namespace Botan {

class Public_Key;

namespace TLS {

/**
* TLS Policy Base Class
* Inherit and overload as desired to suit local policy concerns
*/
class BOTAN_PUBLIC_API(2,0) Policy
   {
   public:

      /**
      * Returns a list of ciphers we are willing to negotiate, in
      * order of preference.
      */
      virtual std::vector<std::string> allowed_ciphers() const;

      /**
      * Returns a list of hash algorithms we are willing to use for
      * signatures, in order of preference.
      */
      virtual std::vector<std::string> allowed_signature_hashes() const;

      /**
      * Returns a list of MAC algorithms we are willing to use.
      */
      virtual std::vector<std::string> allowed_macs() const;

      /**
      * Returns a list of key exchange algorithms we are willing to
      * use, in order of preference. Allowed values: DH, empty string
      * (representing RSA using server certificate key)
      */
      virtual std::vector<std::string> allowed_key_exchange_methods() const;

      /**
      * Returns a list of signature algorithms we are willing to
      * use, in order of preference. Allowed values RSA and DSA.
      */
      virtual std::vector<std::string> allowed_signature_methods() const;

      virtual std::vector<Signature_Scheme> allowed_signature_schemes() const;

      /**
      * The minimum signature strength we will accept
      * Returning 80 allows RSA 1024 and SHA-1. Values larger than 80 disable SHA-1 support.
      * Returning 110 allows RSA 2048.
      * Return 128 to force ECC (P-256) or large (~3000 bit) RSA keys.
      * Default is 110
      */
      virtual size_t minimum_signature_strength() const;

      /**
      * Return if cert revocation info (CRL/OCSP) is required
      * If true, validation will fail unless a valid CRL or OCSP response
      * was examined.
      */
      virtual bool require_cert_revocation_info() const;

      bool allowed_signature_method(const std::string& sig_method) const;
      bool allowed_signature_hash(const std::string& hash) const;

      /**
      * Return list of ECC curves and FFDHE groups we are willing to
      * use in order of preference.
      */
      virtual std::vector<Group_Params> key_exchange_groups() const;

      /**
      * Request that ECC curve points are sent compressed
      */
      virtual bool use_ecc_point_compression() const;

      /**
      * Select a key exchange group to use, from the list of groups sent by the
      * peer. If none are acceptable, return Group_Params::NONE
      */
      virtual Group_Params choose_key_exchange_group(const std::vector<Group_Params>& peer_groups) const;

      /**
      * Allow renegotiation even if the counterparty doesn't
      * support the secure renegotiation extension.
      *
      * @warning Changing this to true exposes you to injected
      * plaintext attacks. Read RFC 5746 for background.
      */
      virtual bool allow_insecure_renegotiation() const;

      /**
      * The protocol dictates that the first 32 bits of the random
      * field are the current time in seconds. However this allows
      * client fingerprinting attacks. Set to false to disable, in
      * which case random bytes will be used instead.
      */
      virtual bool include_time_in_hello_random() const;

      /**
      * Consulted by server side. If true, allows clients to initiate a new handshake
      */
      virtual bool allow_client_initiated_renegotiation() const;

      /**
      * Consulted by client side. If true, allows servers to initiate a new handshake
      */
      virtual bool allow_server_initiated_renegotiation() const;

      /**
      * If true, a request to renegotiate will close the connection with
      * a fatal alert. Otherwise, a warning alert is sent.
      */
      virtual bool abort_connection_on_undesired_renegotiation() const;

      virtual bool only_resume_with_exact_version() const;

      /**
      * Allow TLS v1.0
      */
      virtual bool allow_tls10() const;

      /**
      * Allow TLS v1.1
      */
      virtual bool allow_tls11() const;

      /**
      * Allow TLS v1.2
      */
      virtual bool allow_tls12() const;

      /**
      * Allow DTLS v1.0
      */
      virtual bool allow_dtls10() const;

      /**
      * Allow DTLS v1.2
      */
      virtual bool allow_dtls12() const;

      virtual Group_Params default_dh_group() const;

      /**
      * Return the minimum DH group size we're willing to use
      * Default is currently 1024 (insecure), should be 2048
      */
      virtual size_t minimum_dh_group_size() const;

      /**
      * For ECDSA authenticated ciphersuites, the smallest key size the
      * client will accept.
      * This policy is currently only enforced on the server by the client.
      */
      virtual size_t minimum_ecdsa_group_size() const;

      /**
      * Return the minimum ECDH group size we're willing to use
      * for key exchange
      *
      * Default 255, allowing x25519 and larger
      * x25519 is the smallest curve we will negotiate
      * P-521 is the largest
      */
      virtual size_t minimum_ecdh_group_size() const;

      /**
      * Return the minimum bit size we're willing to accept for RSA
      * key exchange or server signatures.
      *
      * It does not place any requirements on the size of any RSA signature(s)
      * which were used to check the server certificate. This is only
      * concerned with the server's public key.
      *
      * Default is 2048 which is smallest RSA key size still secure
      * for medium term security.
      */
      virtual size_t minimum_rsa_bits() const;

      /**
      * Minimum DSA group size, default 2048 bits
      */
      virtual size_t minimum_dsa_group_size() const;

      /**
      * Throw an exception if you don't like the peer's key.
      * Default impl checks the key size against minimum_rsa_bits, minimum_ecdsa_group_size,
      * or minimum_ecdh_group_size depending on the key's type.
      * Override if you'd like to perform some other kind of test on
      * (or logging of) the peer's keys.
      */
      virtual void check_peer_key_acceptable(const Public_Key& public_key) const;

      /**
      * If this function returns false, unknown SRP/PSK identifiers
      * will be rejected with an unknown_psk_identifier alert as soon
      * as the non-existence is identified. Otherwise, a false
      * identifier value will be used and the protocol allowed to
      * proceed, causing the handshake to eventually fail without
      * revealing that the username does not exist on this system.
      */
      virtual bool hide_unknown_users() const;

      /**
      * Return the allowed lifetime of a session ticket. If 0, session
      * tickets do not expire until the session ticket key rolls over.
      * Expired session tickets cannot be used to resume a session.
      */
      virtual uint32_t session_ticket_lifetime() const;

      /**
      * If this returns a non-empty vector, and DTLS is negotiated,
      * then we will also attempt to negotiate the SRTP extension from
      * RFC 5764 using the returned values as the profile ids.
      */
      virtual std::vector<uint16_t> srtp_profiles() const;

      /**
      * @return true if and only if we are willing to accept this version
      * Default accepts TLS v1.0 and later or DTLS v1.2 or later.
      */
      virtual bool acceptable_protocol_version(Protocol_Version version) const;

      /**
      * Returns the more recent protocol version we are willing to
      * use, for either TLS or DTLS depending on datagram param.
      * Shouldn't ever need to override this unless you want to allow
      * a user to disable use of TLS v1.2 (which is *not recommended*)
      */
      virtual Protocol_Version latest_supported_version(bool datagram) const;

      /**
      * When offering this version, should we send a fallback SCSV?
      * Default returns true iff version is not the latest version the
      * policy allows, exists to allow override in case of interop problems.
      */
      virtual bool send_fallback_scsv(Protocol_Version version) const;

      /**
      * Allows policy to reject any ciphersuites which are undesirable
      * for whatever reason without having to reimplement ciphersuite_list
      */
      virtual bool acceptable_ciphersuite(const Ciphersuite& suite) const;

      /**
      * @return true if servers should choose the ciphersuite matching
      *         their highest preference, rather than the clients.
      *         Has no effect on client side.
      */
      virtual bool server_uses_own_ciphersuite_preferences() const;

      /**
      * Indicates whether the encrypt-then-MAC extension should be negotiated
      * (RFC 7366)
      */
      virtual bool negotiate_encrypt_then_mac() const;

      /**
      * Indicates whether certificate status messages should be supported
      */
      virtual bool support_cert_status_message() const;

      /**
      * Indicate if client certificate authentication is required.
      * If true, then a cert will be requested and if the client does
      * not send a certificate the connection will be closed.
      */
      virtual bool require_client_certificate_authentication() const;

      /**
      * Indicate if client certificate authentication is requested.
      * If true, then a cert will be requested.
      */
      virtual bool request_client_certificate_authentication() const;

      /**
      * If true, then allow a DTLS client to restart a connection to the
      * same server association as described in section 4.2.8 of the DTLS RFC
      */
      virtual bool allow_dtls_epoch0_restart() const;

      /**
      * Return allowed ciphersuites, in order of preference
      */
      virtual std::vector<uint16_t> ciphersuite_list(Protocol_Version version,
                                                     bool have_srp) const;

      /**
      * @return the default MTU for DTLS
      */
      virtual size_t dtls_default_mtu() const;

      /**
      * @return the initial timeout for DTLS
      */
      virtual size_t dtls_initial_timeout() const;

      /**
      * @return the maximum timeout for DTLS
      */
      virtual size_t dtls_maximum_timeout() const;

      /**
      * @return the maximum size of the certificate chain, in bytes.
      * Return 0 to disable this and accept any size.
      */
      virtual size_t maximum_certificate_chain_size() const;

      virtual bool allow_resumption_for_renegotiation() const;

      /**
      * Convert this policy to a printable format.
      * @param o stream to be printed to
      */
      virtual void print(std::ostream& o) const;

      /**
      * Convert this policy to a printable format.
      * Same as calling `print` on a ostringstream and reading o.str()
      */
      std::string to_string() const;

      virtual ~Policy() = default;
   };

typedef Policy Default_Policy;

/**
* NSA Suite B 128-bit security level (RFC 6460)
*
* @warning As of August 2015 NSA indicated only the 192-bit Suite B
* should be used for all classification levels.
*/
class BOTAN_PUBLIC_API(2,0) NSA_Suite_B_128 : public Policy
   {
   public:
      std::vector<std::string> allowed_ciphers() const override
         { return std::vector<std::string>({"AES-128/GCM"}); }

      std::vector<std::string> allowed_signature_hashes() const override
         { return std::vector<std::string>({"SHA-256"}); }

      std::vector<std::string> allowed_macs() const override
         { return std::vector<std::string>({"AEAD"}); }

      std::vector<std::string> allowed_key_exchange_methods() const override
         { return std::vector<std::string>({"ECDH"}); }

      std::vector<std::string> allowed_signature_methods() const override
         { return std::vector<std::string>({"ECDSA"}); }

      std::vector<Group_Params> key_exchange_groups() const override
         { return {Group_Params::SECP256R1}; }

      size_t minimum_signature_strength() const override { return 128; }

      bool allow_tls10()  const override { return false; }
      bool allow_tls11()  const override { return false; }
      bool allow_tls12()  const override { return true;  }
      bool allow_dtls10() const override { return false; }
      bool allow_dtls12() const override { return false; }
   };

/**
* NSA Suite B 192-bit security level (RFC 6460)
*/
class BOTAN_PUBLIC_API(2,7) NSA_Suite_B_192 : public Policy
   {
   public:
      std::vector<std::string> allowed_ciphers() const override
         { return std::vector<std::string>({"AES-256/GCM"}); }

      std::vector<std::string> allowed_signature_hashes() const override
         { return std::vector<std::string>({"SHA-384"}); }

      std::vector<std::string> allowed_macs() const override
         { return std::vector<std::string>({"AEAD"}); }

      std::vector<std::string> allowed_key_exchange_methods() const override
         { return std::vector<std::string>({"ECDH"}); }

      std::vector<std::string> allowed_signature_methods() const override
         { return std::vector<std::string>({"ECDSA"}); }

      std::vector<Group_Params> key_exchange_groups() const override
         { return {Group_Params::SECP384R1}; }

      size_t minimum_signature_strength() const override { return 192; }

      bool allow_tls10()  const override { return false; }
      bool allow_tls11()  const override { return false; }
      bool allow_tls12()  const override { return true;  }
      bool allow_dtls10() const override { return false; }
      bool allow_dtls12() const override { return false; }
   };

/**
* BSI TR-02102-2 Policy
*/
class BOTAN_PUBLIC_API(2,0) BSI_TR_02102_2 : public Policy
   {
   public:
      std::vector<std::string> allowed_ciphers() const override
         {
         return std::vector<std::string>({"AES-256/GCM", "AES-128/GCM", "AES-256/CCM", "AES-128/CCM", "AES-256", "AES-128"});
         }

      std::vector<std::string> allowed_signature_hashes() const override
         {
         return std::vector<std::string>({"SHA-512", "SHA-384", "SHA-256"});
         }

      std::vector<std::string> allowed_macs() const override
         {
         return std::vector<std::string>({"AEAD", "SHA-384", "SHA-256"});
         }

      std::vector<std::string> allowed_key_exchange_methods() const override
         {
         return std::vector<std::string>({"ECDH", "DH", "ECDHE_PSK", "DHE_PSK"});
         }

      std::vector<std::string> allowed_signature_methods() const override
         {
         return std::vector<std::string>({"ECDSA", "RSA", "DSA"});
         }

      std::vector<Group_Params> key_exchange_groups() const override
         {
         return std::vector<Group_Params>({
            Group_Params::BRAINPOOL512R1,
            Group_Params::BRAINPOOL384R1,
            Group_Params::BRAINPOOL256R1,
            Group_Params::SECP384R1,
            Group_Params::SECP256R1,
            Group_Params::FFDHE_4096,
            Group_Params::FFDHE_3072,
            Group_Params::FFDHE_2048
            });
         }

      bool allow_insecure_renegotiation() const override { return false; }
      bool allow_server_initiated_renegotiation() const override { return true; }
      bool server_uses_own_ciphersuite_preferences() const override { return true; }
      bool negotiate_encrypt_then_mac() const override { return true; }

      size_t minimum_rsa_bits() const override { return 2000; }
      size_t minimum_dh_group_size() const override { return 2000; }
      size_t minimum_dsa_group_size() const override { return 2000; }

      size_t minimum_ecdh_group_size() const override { return 250; }
      size_t minimum_ecdsa_group_size() const override { return 250; }

      bool allow_tls10()  const override { return false; }
      bool allow_tls11()  const override { return false; }
      bool allow_tls12()  const override { return true;  }
      bool allow_dtls10() const override { return false; }
      bool allow_dtls12() const override { return false; }
   };

/**
* Policy for DTLS. We require DTLS v1.2 and an AEAD mode.
*/
class BOTAN_PUBLIC_API(2,0) Datagram_Policy : public Policy
   {
   public:
      std::vector<std::string> allowed_macs() const override
         { return std::vector<std::string>({"AEAD"}); }

      bool allow_tls10()  const override { return false; }
      bool allow_tls11()  const override { return false; }
      bool allow_tls12()  const override { return false; }
      bool allow_dtls10() const override { return false; }
      bool allow_dtls12() const override { return true;  }
   };

/*
* This policy requires a secure version of TLS and disables all insecure
* algorithms. It is compatible with other botan TLSes (including those using the
* default policy) and with many other recent implementations. It is a great idea
* to use if you control both sides of the protocol and don't have to worry
* about ancient and/or bizarre TLS implementations.
*/
class BOTAN_PUBLIC_API(2,0) Strict_Policy : public Policy
   {
   public:
      std::vector<std::string> allowed_ciphers() const override;

      std::vector<std::string> allowed_signature_hashes() const override;

      std::vector<std::string> allowed_macs() const override;

      std::vector<std::string> allowed_key_exchange_methods() const override;

      bool allow_tls10()  const override;
      bool allow_tls11()  const override;
      bool allow_tls12()  const override;
      bool allow_dtls10() const override;
      bool allow_dtls12() const override;
   };

class BOTAN_PUBLIC_API(2,0) Text_Policy : public Policy
   {
   public:

      std::vector<std::string> allowed_ciphers() const override;

      std::vector<std::string> allowed_signature_hashes() const override;

      std::vector<std::string> allowed_macs() const override;

      std::vector<std::string> allowed_key_exchange_methods() const override;

      std::vector<std::string> allowed_signature_methods() const override;

      std::vector<Group_Params> key_exchange_groups() const override;

      bool use_ecc_point_compression() const override;

      bool allow_tls10() const override;

      bool allow_tls11() const override;

      bool allow_tls12() const override;

      bool allow_dtls10() const override;

      bool allow_dtls12() const override;

      bool allow_insecure_renegotiation() const override;

      bool include_time_in_hello_random() const override;

      bool allow_client_initiated_renegotiation() const override;
      bool allow_server_initiated_renegotiation() const override;

      bool server_uses_own_ciphersuite_preferences() const override;

      bool negotiate_encrypt_then_mac() const override;

      bool support_cert_status_message() const override;

      bool require_client_certificate_authentication() const override;

      size_t minimum_ecdh_group_size() const override;

      size_t minimum_ecdsa_group_size() const override;

      size_t minimum_dh_group_size() const override;

      size_t minimum_rsa_bits() const override;

      size_t minimum_signature_strength() const override;

      size_t dtls_default_mtu() const override;

      size_t dtls_initial_timeout() const override;

      size_t dtls_maximum_timeout() const override;

      bool require_cert_revocation_info() const override;

      bool hide_unknown_users() const override;

      uint32_t session_ticket_lifetime() const override;

      bool send_fallback_scsv(Protocol_Version version) const override;

      std::vector<uint16_t> srtp_profiles() const override;

      void set(const std::string& k, const std::string& v);

      explicit Text_Policy(const std::string& s);

      explicit Text_Policy(std::istream& in);

   protected:

      std::vector<std::string> get_list(const std::string& key,
                                        const std::vector<std::string>& def) const;

      size_t get_len(const std::string& key, size_t def) const;

      bool get_bool(const std::string& key, bool def) const;

      std::string get_str(const std::string& key, const std::string& def = "") const;

      bool set_value(const std::string& key, const std::string& val, bool overwrite);

   private:
      std::map<std::string, std::string> m_kv;
   };

}

}

namespace Botan {

namespace TLS {

/**
* SSL/TLS Client
*/
class BOTAN_PUBLIC_API(2,0) Client final : public Channel
   {
   public:

      /**
      * Set up a new TLS client session
      *
      * @param callbacks contains a set of callback function references
      *        required by the TLS client.
      *
      * @param session_manager manages session state
      *
      * @param creds manages application/user credentials
      *
      * @param policy specifies other connection policy information
      *
      * @param rng a random number generator
      *
      * @param server_info is identifying information about the TLS server
      *
      * @param offer_version specifies which version we will offer
      *        to the TLS server.
      *
      * @param next_protocols specifies protocols to advertise with ALPN
      *
      * @param reserved_io_buffer_size This many bytes of memory will
      *        be preallocated for the read and write buffers. Smaller
      *        values just mean reallocations and copies are more likely.
      */
     Client(Callbacks& callbacks,
            Session_Manager& session_manager,
            Credentials_Manager& creds,
            const Policy& policy,
            RandomNumberGenerator& rng,
            const Server_Information& server_info = Server_Information(),
            const Protocol_Version& offer_version = Protocol_Version::latest_tls_version(),
            const std::vector<std::string>& next_protocols = {},
            size_t reserved_io_buffer_size = TLS::Client::IO_BUF_DEFAULT_SIZE
         );

      /**
      * DEPRECATED. This constructor is only provided for backward
      * compatibility and should not be used in new code. It will be
      * removed in a future release.
      *
      * Set up a new TLS client session
      *
      * @param data_output_fn is called with data for the outbound socket
      *
      * @param app_data_cb is called when new application data is received
      *
      * @param recv_alert_cb is called when a TLS alert is received
      *
      * @param hs_cb is called when a handshake is completed
      *
      * @param session_manager manages session state
      *
      * @param creds manages application/user credentials
      *
      * @param policy specifies other connection policy information
      *
      * @param rng a random number generator
      *
      * @param server_info is identifying information about the TLS server
      *
      * @param offer_version specifies which version we will offer
      *        to the TLS server.
      *
      * @param next_protocols specifies protocols to advertise with ALPN
      *
      * @param reserved_io_buffer_size This many bytes of memory will
      *        be preallocated for the read and write buffers. Smaller
      *        values just mean reallocations and copies are more likely.
      */
      BOTAN_DEPRECATED("Use TLS::Client(TLS::Callbacks ...)")
      Client(output_fn data_output_fn,
             data_cb app_data_cb,
             alert_cb recv_alert_cb,
             handshake_cb hs_cb,
             Session_Manager& session_manager,
             Credentials_Manager& creds,
             const Policy& policy,
             RandomNumberGenerator& rng,
             const Server_Information& server_info = Server_Information(),
             const Protocol_Version& offer_version = Protocol_Version::latest_tls_version(),
             const std::vector<std::string>& next_protocols = {},
             size_t reserved_io_buffer_size = TLS::Client::IO_BUF_DEFAULT_SIZE
         );

      /**
       * DEPRECATED. This constructor is only provided for backward
       * compatibility and should not be used in new implementations.
       */
      BOTAN_DEPRECATED("Use TLS::Client(TLS::Callbacks ...)")
      Client(output_fn out,
             data_cb app_data_cb,
             alert_cb alert_cb,
             handshake_cb hs_cb,
             handshake_msg_cb hs_msg_cb,
             Session_Manager& session_manager,
             Credentials_Manager& creds,
             const Policy& policy,
             RandomNumberGenerator& rng,
             const Server_Information& server_info = Server_Information(),
             const Protocol_Version& offer_version = Protocol_Version::latest_tls_version(),
             const std::vector<std::string>& next_protocols = {}
         );

      /**
      * @return network protocol as advertised by the TLS server, if server sent the ALPN extension
      */
      std::string application_protocol() const override { return m_application_protocol; }
   private:
      void init(const Protocol_Version& protocol_version,
                const std::vector<std::string>& next_protocols);

      std::vector<X509_Certificate>
         get_peer_cert_chain(const Handshake_State& state) const override;

      void initiate_handshake(Handshake_State& state,
                              bool force_full_renegotiation) override;

      void send_client_hello(Handshake_State& state,
                             bool force_full_renegotiation,
                             Protocol_Version version,
                             const std::string& srp_identifier = "",
                             const std::vector<std::string>& next_protocols = {});

      void process_handshake_msg(const Handshake_State* active_state,
                                 Handshake_State& pending_state,
                                 Handshake_Type type,
                                 const std::vector<uint8_t>& contents,
                                 bool epoch0_restart) override;

      Handshake_State* new_handshake_state(Handshake_IO* io) override;

      Credentials_Manager& m_creds;
      const Server_Information m_info;
      std::string m_application_protocol;
   };

}

}

namespace Botan {

namespace TLS {

/**
* Blocking TLS Client
* Can be used directly, or subclass to get handshake and alert notifications
*/
class BOTAN_PUBLIC_API(2,0) Blocking_Client
   {
   public:
      /*
      * These functions are expected to block until completing entirely, or
      * fail by throwing an exception.
      */
      typedef std::function<size_t (uint8_t[], size_t)> read_fn;
      typedef std::function<void (const uint8_t[], size_t)> write_fn;

      BOTAN_DEPRECATED("Use the regular TLS::Client interface")
      Blocking_Client(read_fn reader,
                      write_fn writer,
                      Session_Manager& session_manager,
                      Credentials_Manager& creds,
                      const Policy& policy,
                      RandomNumberGenerator& rng,
                      const Server_Information& server_info = Server_Information(),
                      const Protocol_Version& offer_version = Protocol_Version::latest_tls_version(),
                      const std::vector<std::string>& next_protos = {});

      /**
      * Completes full handshake then returns
      */
      void do_handshake();

      /**
      * Number of bytes pending read in the plaintext buffer (bytes
      * readable without blocking)
      */
      size_t pending() const { return m_plaintext.size(); }

      /**
      * Blocking read, will return at least 1 byte (eventually) or else 0 if the connection
      * is closed.
      */
      size_t read(uint8_t buf[], size_t buf_len);

      void write(const uint8_t buf[], size_t buf_len) { m_channel.send(buf, buf_len); }

      const TLS::Channel& underlying_channel() const { return m_channel; }
      TLS::Channel& underlying_channel() { return m_channel; }

      void close() { m_channel.close(); }

      bool is_closed() const { return m_channel.is_closed(); }

      std::vector<X509_Certificate> peer_cert_chain() const
         { return m_channel.peer_cert_chain(); }

      virtual ~Blocking_Client() = default;

   protected:
      /**
      * Application can override to get the handshake complete notification
      */
      virtual bool handshake_complete(const Session&) { return true; }

      /**
      * Application can override to get notification of alerts
      */
      virtual void alert_notification(const Alert&) {}

   private:

      bool handshake_cb(const Session&);

      void data_cb(const uint8_t data[], size_t data_len);

      void alert_cb(const Alert& alert);

      read_fn m_read;
      std::unique_ptr<Compat_Callbacks> m_callbacks;
      TLS::Client m_channel;
      secure_vector<uint8_t> m_plaintext;
   };

}

}

namespace Botan {

namespace TLS {

/**
* TLS Exception Base Class
*/
class BOTAN_PUBLIC_API(2,0) TLS_Exception : public Exception
   {
   public:
      Alert::Type type() const { return m_alert_type; }

      TLS_Exception(Alert::Type type,
                    const std::string& err_msg = "Unknown error") :
         Exception(err_msg), m_alert_type(type) {}

      int error_code() const noexcept override { return static_cast<int>(m_alert_type); }

      ErrorType error_type() const noexcept override { return ErrorType::TLSError; }

   private:
      Alert::Type m_alert_type;
   };

/**
* Unexpected_Message Exception
*/
class BOTAN_PUBLIC_API(2,0) Unexpected_Message final : public TLS_Exception
   {
   public:
      explicit Unexpected_Message(const std::string& err) :
         TLS_Exception(Alert::UNEXPECTED_MESSAGE, err) {}
   };

}

}

namespace Botan {

namespace TLS {

class Policy;

class TLS_Data_Reader;

// This will become an enum class in a future major release
enum Handshake_Extension_Type {
   TLSEXT_SERVER_NAME_INDICATION = 0,
   TLSEXT_CERT_STATUS_REQUEST    = 5,

   TLSEXT_CERTIFICATE_TYPES      = 9,
   TLSEXT_SUPPORTED_GROUPS       = 10,
   TLSEXT_EC_POINT_FORMATS       = 11,
   TLSEXT_SRP_IDENTIFIER         = 12,
   TLSEXT_SIGNATURE_ALGORITHMS   = 13,
   TLSEXT_USE_SRTP               = 14,
   TLSEXT_ALPN                   = 16,

   TLSEXT_ENCRYPT_THEN_MAC       = 22,
   TLSEXT_EXTENDED_MASTER_SECRET = 23,

   TLSEXT_SESSION_TICKET         = 35,

   TLSEXT_SUPPORTED_VERSIONS     = 43,

   TLSEXT_SAFE_RENEGOTIATION     = 65281,
};

/**
* Base class representing a TLS extension of some kind
*/
class BOTAN_UNSTABLE_API Extension
   {
   public:
      /**
      * @return code number of the extension
      */
      virtual Handshake_Extension_Type type() const = 0;

      /**
      * @return serialized binary for the extension
      */
      virtual std::vector<uint8_t> serialize(Connection_Side whoami) const = 0;

      /**
      * @return if we should encode this extension or not
      */
      virtual bool empty() const = 0;

      virtual ~Extension() = default;
   };

/**
* Server Name Indicator extension (RFC 3546)
*/
class BOTAN_UNSTABLE_API Server_Name_Indicator final : public Extension
   {
   public:
      static Handshake_Extension_Type static_type()
         { return TLSEXT_SERVER_NAME_INDICATION; }

      Handshake_Extension_Type type() const override { return static_type(); }

      explicit Server_Name_Indicator(const std::string& host_name) :
         m_sni_host_name(host_name) {}

      Server_Name_Indicator(TLS_Data_Reader& reader,
                            uint16_t extension_size);

      std::string host_name() const { return m_sni_host_name; }

      std::vector<uint8_t> serialize(Connection_Side whoami) const override;

      bool empty() const override { return m_sni_host_name.empty(); }
   private:
      std::string m_sni_host_name;
   };

#if defined(BOTAN_HAS_SRP6)
/**
* SRP identifier extension (RFC 5054)
*/
class BOTAN_UNSTABLE_API SRP_Identifier final : public Extension
   {
   public:
      static Handshake_Extension_Type static_type()
         { return TLSEXT_SRP_IDENTIFIER; }

      Handshake_Extension_Type type() const override { return static_type(); }

      explicit SRP_Identifier(const std::string& identifier) :
         m_srp_identifier(identifier) {}

      SRP_Identifier(TLS_Data_Reader& reader,
                     uint16_t extension_size);

      std::string identifier() const { return m_srp_identifier; }

      std::vector<uint8_t> serialize(Connection_Side whoami) const override;

      bool empty() const override { return m_srp_identifier.empty(); }
   private:
      std::string m_srp_identifier;
   };
#endif

/**
* Renegotiation Indication Extension (RFC 5746)
*/
class BOTAN_UNSTABLE_API Renegotiation_Extension final : public Extension
   {
   public:
      static Handshake_Extension_Type static_type()
         { return TLSEXT_SAFE_RENEGOTIATION; }

      Handshake_Extension_Type type() const override { return static_type(); }

      Renegotiation_Extension() = default;

      explicit Renegotiation_Extension(const std::vector<uint8_t>& bits) :
         m_reneg_data(bits) {}

      Renegotiation_Extension(TLS_Data_Reader& reader,
                             uint16_t extension_size);

      const std::vector<uint8_t>& renegotiation_info() const
         { return m_reneg_data; }

      std::vector<uint8_t> serialize(Connection_Side whoami) const override;

      bool empty() const override { return false; } // always send this
   private:
      std::vector<uint8_t> m_reneg_data;
   };

/**
* ALPN (RFC 7301)
*/
class BOTAN_UNSTABLE_API Application_Layer_Protocol_Notification final : public Extension
   {
   public:
      static Handshake_Extension_Type static_type() { return TLSEXT_ALPN; }

      Handshake_Extension_Type type() const override { return static_type(); }

      const std::vector<std::string>& protocols() const { return m_protocols; }

      const std::string& single_protocol() const;

      /**
      * Single protocol, used by server
      */
      explicit Application_Layer_Protocol_Notification(const std::string& protocol) :
         m_protocols(1, protocol) {}

      /**
      * List of protocols, used by client
      */
      explicit Application_Layer_Protocol_Notification(const std::vector<std::string>& protocols) :
         m_protocols(protocols) {}

      Application_Layer_Protocol_Notification(TLS_Data_Reader& reader,
                                              uint16_t extension_size);

      std::vector<uint8_t> serialize(Connection_Side whoami) const override;

      bool empty() const override { return m_protocols.empty(); }
   private:
      std::vector<std::string> m_protocols;
   };

/**
* Session Ticket Extension (RFC 5077)
*/
class BOTAN_UNSTABLE_API Session_Ticket final : public Extension
   {
   public:
      static Handshake_Extension_Type static_type()
         { return TLSEXT_SESSION_TICKET; }

      Handshake_Extension_Type type() const override { return static_type(); }

      /**
      * @return contents of the session ticket
      */
      const std::vector<uint8_t>& contents() const { return m_ticket; }

      /**
      * Create empty extension, used by both client and server
      */
      Session_Ticket() = default;

      /**
      * Extension with ticket, used by client
      */
      explicit Session_Ticket(const std::vector<uint8_t>& session_ticket) :
         m_ticket(session_ticket) {}

      /**
      * Deserialize a session ticket
      */
      Session_Ticket(TLS_Data_Reader& reader, uint16_t extension_size);

      std::vector<uint8_t> serialize(Connection_Side) const override { return m_ticket; }

      bool empty() const override { return false; }
   private:
      std::vector<uint8_t> m_ticket;
   };


/**
* Supported Groups Extension (RFC 7919)
*/
class BOTAN_UNSTABLE_API Supported_Groups final : public Extension
   {
   public:
      static Handshake_Extension_Type static_type()
         { return TLSEXT_SUPPORTED_GROUPS; }

      Handshake_Extension_Type type() const override { return static_type(); }

      std::vector<Group_Params> ec_groups() const;
      std::vector<Group_Params> dh_groups() const;

      std::vector<uint8_t> serialize(Connection_Side whoami) const override;

      explicit Supported_Groups(const std::vector<Group_Params>& groups);

      Supported_Groups(TLS_Data_Reader& reader,
                       uint16_t extension_size);

      bool empty() const override { return m_groups.empty(); }
   private:
      std::vector<Group_Params> m_groups;
   };

// previously Supported Elliptic Curves Extension (RFC 4492)
//using Supported_Elliptic_Curves = Supported_Groups;

/**
* Supported Point Formats Extension (RFC 4492)
*/
class BOTAN_UNSTABLE_API Supported_Point_Formats final : public Extension
   {
   public:
      enum ECPointFormat : uint8_t {
         UNCOMPRESSED = 0,
         ANSIX962_COMPRESSED_PRIME = 1,
         ANSIX962_COMPRESSED_CHAR2 = 2, // don't support these curves
      };

      static Handshake_Extension_Type static_type()
         { return TLSEXT_EC_POINT_FORMATS; }

      Handshake_Extension_Type type() const override { return static_type(); }

      std::vector<uint8_t> serialize(Connection_Side whoami) const override;

      explicit Supported_Point_Formats(bool prefer_compressed) :
         m_prefers_compressed(prefer_compressed) {}

      Supported_Point_Formats(TLS_Data_Reader& reader,
                              uint16_t extension_size);

      bool empty() const override { return false; }

      bool prefers_compressed() { return m_prefers_compressed; }

   private:
      bool m_prefers_compressed = false;
   };

/**
* Signature Algorithms Extension for TLS 1.2 (RFC 5246)
*/
class BOTAN_UNSTABLE_API Signature_Algorithms final : public Extension
   {
   public:
      static Handshake_Extension_Type static_type()
         { return TLSEXT_SIGNATURE_ALGORITHMS; }

      Handshake_Extension_Type type() const override { return static_type(); }

      const std::vector<Signature_Scheme>& supported_schemes() const { return m_schemes; }

      std::vector<uint8_t> serialize(Connection_Side whoami) const override;

      bool empty() const override { return m_schemes.empty(); }

      explicit Signature_Algorithms(const std::vector<Signature_Scheme>& schemes) :
         m_schemes(schemes) {}

      Signature_Algorithms(TLS_Data_Reader& reader,
                           uint16_t extension_size);
   private:
      std::vector<Signature_Scheme> m_schemes;
   };

/**
* Used to indicate SRTP algorithms for DTLS (RFC 5764)
*/
class BOTAN_UNSTABLE_API SRTP_Protection_Profiles final : public Extension
   {
   public:
      static Handshake_Extension_Type static_type()
         { return TLSEXT_USE_SRTP; }

      Handshake_Extension_Type type() const override { return static_type(); }

      const std::vector<uint16_t>& profiles() const { return m_pp; }

      std::vector<uint8_t> serialize(Connection_Side whoami) const override;

      bool empty() const override { return m_pp.empty(); }

      explicit SRTP_Protection_Profiles(const std::vector<uint16_t>& pp) : m_pp(pp) {}

      explicit SRTP_Protection_Profiles(uint16_t pp) : m_pp(1, pp) {}

      SRTP_Protection_Profiles(TLS_Data_Reader& reader, uint16_t extension_size);
   private:
      std::vector<uint16_t> m_pp;
   };

/**
* Extended Master Secret Extension (RFC 7627)
*/
class BOTAN_UNSTABLE_API Extended_Master_Secret final : public Extension
   {
   public:
      static Handshake_Extension_Type static_type()
         { return TLSEXT_EXTENDED_MASTER_SECRET; }

      Handshake_Extension_Type type() const override { return static_type(); }

      std::vector<uint8_t> serialize(Connection_Side whoami) const override;

      bool empty() const override { return false; }

      Extended_Master_Secret() = default;

      Extended_Master_Secret(TLS_Data_Reader& reader, uint16_t extension_size);
   };

/**
* Encrypt-then-MAC Extension (RFC 7366)
*/
class BOTAN_UNSTABLE_API Encrypt_then_MAC final : public Extension
   {
   public:
      static Handshake_Extension_Type static_type()
         { return TLSEXT_ENCRYPT_THEN_MAC; }

      Handshake_Extension_Type type() const override { return static_type(); }

      std::vector<uint8_t> serialize(Connection_Side whoami) const override;

      bool empty() const override { return false; }

      Encrypt_then_MAC() = default;

      Encrypt_then_MAC(TLS_Data_Reader& reader, uint16_t extension_size);
   };

/**
* Certificate Status Request (RFC 6066)
*/
class BOTAN_UNSTABLE_API Certificate_Status_Request final : public Extension
   {
   public:
      static Handshake_Extension_Type static_type()
         { return TLSEXT_CERT_STATUS_REQUEST; }

      Handshake_Extension_Type type() const override { return static_type(); }

      std::vector<uint8_t> serialize(Connection_Side whoami) const override;

      bool empty() const override { return false; }

      const std::vector<uint8_t>& get_responder_id_list() const
         {
         return m_ocsp_names;
         }

      const std::vector<uint8_t>& get_request_extensions() const
         {
         return m_extension_bytes;
         }

      // Server generated version: empty
      Certificate_Status_Request() {}

      // Client version, both lists can be empty
      Certificate_Status_Request(const std::vector<uint8_t>& ocsp_responder_ids,
                                 const std::vector<std::vector<uint8_t>>& ocsp_key_ids);

      Certificate_Status_Request(TLS_Data_Reader& reader,
                                 uint16_t extension_size,
                                 Connection_Side side);
   private:
      std::vector<uint8_t> m_ocsp_names;
      std::vector<std::vector<uint8_t>> m_ocsp_keys; // is this field really needed
      std::vector<uint8_t> m_extension_bytes;
   };

/**
* Supported Versions from RFC 8446
*/
class BOTAN_UNSTABLE_API Supported_Versions final : public Extension
   {
   public:
      static Handshake_Extension_Type static_type()
         { return TLSEXT_SUPPORTED_VERSIONS; }

      Handshake_Extension_Type type() const override { return static_type(); }

      std::vector<uint8_t> serialize(Connection_Side whoami) const override;

      bool empty() const override { return m_versions.empty(); }

      Supported_Versions(Protocol_Version version, const Policy& policy);

      Supported_Versions(Protocol_Version version)
         {
         m_versions.push_back(version);
         }

      Supported_Versions(TLS_Data_Reader& reader,
                         uint16_t extension_size,
                         Connection_Side from);

      bool supports(Protocol_Version version) const;

      const std::vector<Protocol_Version> versions() const { return m_versions; }
   private:
      std::vector<Protocol_Version> m_versions;
   };

/**
* Unknown extensions are deserialized as this type
*/
class BOTAN_UNSTABLE_API Unknown_Extension final : public Extension
   {
   public:
      Unknown_Extension(Handshake_Extension_Type type,
                        TLS_Data_Reader& reader,
                        uint16_t extension_size);

      std::vector<uint8_t> serialize(Connection_Side whoami) const override; // always fails

      const std::vector<uint8_t>& value() { return m_value; }

      bool empty() const override { return false; }

      Handshake_Extension_Type type() const override { return m_type; }

   private:
      Handshake_Extension_Type m_type;
      std::vector<uint8_t> m_value;
   };

/**
* Represents a block of extensions in a hello message
*/
class BOTAN_UNSTABLE_API Extensions final
   {
   public:
      std::set<Handshake_Extension_Type> extension_types() const;

      template<typename T>
      T* get() const
         {
         return dynamic_cast<T*>(get(T::static_type()));
         }

      template<typename T>
      bool has() const
         {
         return get<T>() != nullptr;
         }

      void add(Extension* extn)
         {
         m_extensions[extn->type()].reset(extn);
         }

      Extension* get(Handshake_Extension_Type type) const
         {
         auto i = m_extensions.find(type);

         if(i != m_extensions.end())
            return i->second.get();
         return nullptr;
         }

      std::vector<uint8_t> serialize(Connection_Side whoami) const;

      void deserialize(TLS_Data_Reader& reader, Connection_Side from);

      /**
      * Remvoe an extension from this extensions object, if it exists.
      * Returns true if the extension existed (and thus is now removed),
      * otherwise false (the extension wasn't set in the first place).
      */
      bool remove_extension(Handshake_Extension_Type typ);

      Extensions() = default;

      Extensions(TLS_Data_Reader& reader, Connection_Side side)
         {
         deserialize(reader, side);
         }

   private:
      Extensions(const Extensions&) = delete;
      Extensions& operator=(const Extensions&) = delete;

      std::map<Handshake_Extension_Type, std::unique_ptr<Extension>> m_extensions;
   };

}

}

namespace Botan {

namespace TLS {

class Handshake_IO;
class Handshake_Hash;

/**
* TLS Handshake Message Base Class
*/
class BOTAN_PUBLIC_API(2,0) Handshake_Message
   {
   public:
      /**
      * @return string representation of this message type
      */
      std::string type_string() const;

      /**
      * @return the message type
      */
      virtual Handshake_Type type() const = 0;

      /**
      * @return DER representation of this message
      */
      virtual std::vector<uint8_t> serialize() const = 0;

      virtual ~Handshake_Message() = default;
   };

}

}

#if defined(BOTAN_HAS_CECPQ1)
#endif

#if defined(BOTAN_HAS_SRP6)
#endif

namespace Botan {

class Public_Key;
class Credentials_Manager;

namespace TLS {

class Session;
class Handshake_IO;
class Handshake_State;
class Callbacks;

std::vector<uint8_t> make_hello_random(RandomNumberGenerator& rng,
                                       const Policy& policy);

/**
* DTLS Hello Verify Request
*/
class BOTAN_UNSTABLE_API Hello_Verify_Request final : public Handshake_Message
   {
   public:
      std::vector<uint8_t> serialize() const override;
      Handshake_Type type() const override { return HELLO_VERIFY_REQUEST; }

      const std::vector<uint8_t>& cookie() const { return m_cookie; }

      explicit Hello_Verify_Request(const std::vector<uint8_t>& buf);

      Hello_Verify_Request(const std::vector<uint8_t>& client_hello_bits,
                           const std::string& client_identity,
                           const SymmetricKey& secret_key);
   private:
      std::vector<uint8_t> m_cookie;
   };

/**
* Client Hello Message
*/
class BOTAN_UNSTABLE_API Client_Hello final : public Handshake_Message
   {
   public:
      class Settings final
         {
         public:
            Settings(const Protocol_Version version,
                     const std::string& hostname = "",
                     const std::string& srp_identifier = "") :
               m_new_session_version(version),
               m_hostname(hostname),
               m_srp_identifier(srp_identifier) {}

            const Protocol_Version protocol_version() const { return m_new_session_version; }
            const std::string& hostname() const { return m_hostname; }
            const std::string& srp_identifier() const { return m_srp_identifier; }

         private:
            const Protocol_Version m_new_session_version;
            const std::string m_hostname;
            const std::string m_srp_identifier;
         };

      Handshake_Type type() const override { return CLIENT_HELLO; }

      Protocol_Version version() const { return m_version; }

      std::vector<Protocol_Version> supported_versions() const;

      const std::vector<uint8_t>& random() const { return m_random; }

      const std::vector<uint8_t>& session_id() const { return m_session_id; }

      const std::vector<uint8_t>& compression_methods() const { return m_comp_methods; }

      const std::vector<uint16_t>& ciphersuites() const { return m_suites; }

      bool offered_suite(uint16_t ciphersuite) const;

      bool sent_fallback_scsv() const;

      std::vector<Signature_Scheme> signature_schemes() const;

      std::vector<Group_Params> supported_ecc_curves() const;

      std::vector<Group_Params> supported_dh_groups() const;

      bool prefers_compressed_ec_points() const;

      std::string sni_hostname() const;

#if defined(BOTAN_HAS_SRP6)
      std::string srp_identifier() const;
#endif

      bool secure_renegotiation() const;

      std::vector<uint8_t> renegotiation_info() const;

      bool supports_session_ticket() const;

      std::vector<uint8_t> session_ticket() const;

      bool supports_alpn() const;

      bool supports_extended_master_secret() const;

      bool supports_cert_status_message() const;

      bool supports_encrypt_then_mac() const;

      bool sent_signature_algorithms() const;

      std::vector<std::string> next_protocols() const;

      std::vector<uint16_t> srtp_profiles() const;

      void update_hello_cookie(const Hello_Verify_Request& hello_verify);

      const std::vector<uint8_t>& cookie() const { return m_hello_cookie; }

      std::vector<uint8_t> cookie_input_data() const;

      std::set<Handshake_Extension_Type> extension_types() const
         { return m_extensions.extension_types(); }

      const Extensions& extensions() const { return m_extensions; }

      Client_Hello(Handshake_IO& io,
                   Handshake_Hash& hash,
                   const Policy& policy,
                   Callbacks& cb,
                   RandomNumberGenerator& rng,
                   const std::vector<uint8_t>& reneg_info,
                   const Client_Hello::Settings& client_settings,
                   const std::vector<std::string>& next_protocols);

      Client_Hello(Handshake_IO& io,
                   Handshake_Hash& hash,
                   const Policy& policy,
                   Callbacks& cb,
                   RandomNumberGenerator& rng,
                   const std::vector<uint8_t>& reneg_info,
                   const Session& resumed_session,
                   const std::vector<std::string>& next_protocols);

      explicit Client_Hello(const std::vector<uint8_t>& buf);

   private:
      std::vector<uint8_t> serialize() const override;

      Protocol_Version m_version;
      std::vector<uint8_t> m_session_id;
      std::vector<uint8_t> m_random;
      std::vector<uint16_t> m_suites;
      std::vector<uint8_t> m_comp_methods;
      std::vector<uint8_t> m_hello_cookie; // DTLS only

      Extensions m_extensions;
   };

/**
* Server Hello Message
*/
class BOTAN_UNSTABLE_API Server_Hello final : public Handshake_Message
   {
   public:
      class Settings final
         {
         public:
            Settings(const std::vector<uint8_t> new_session_id,
                     Protocol_Version new_session_version,
                     uint16_t ciphersuite,
                     bool offer_session_ticket) :
               m_new_session_id(new_session_id),
               m_new_session_version(new_session_version),
               m_ciphersuite(ciphersuite),
               m_offer_session_ticket(offer_session_ticket) {}

            const std::vector<uint8_t>& session_id() const { return m_new_session_id; }
            Protocol_Version protocol_version() const { return m_new_session_version; }
            uint16_t ciphersuite() const { return m_ciphersuite; }
            bool offer_session_ticket() const { return m_offer_session_ticket; }

         private:
            const std::vector<uint8_t> m_new_session_id;
            Protocol_Version m_new_session_version;
            uint16_t m_ciphersuite;
            bool m_offer_session_ticket;
         };


      Handshake_Type type() const override { return SERVER_HELLO; }

      Protocol_Version version() const { return m_version; }

      const std::vector<uint8_t>& random() const { return m_random; }

      const std::vector<uint8_t>& session_id() const { return m_session_id; }

      uint16_t ciphersuite() const { return m_ciphersuite; }

      uint8_t compression_method() const { return m_comp_method; }

      bool secure_renegotiation() const
         {
         return m_extensions.has<Renegotiation_Extension>();
         }

      std::vector<uint8_t> renegotiation_info() const
         {
         if(Renegotiation_Extension* reneg = m_extensions.get<Renegotiation_Extension>())
            return reneg->renegotiation_info();
         return std::vector<uint8_t>();
         }

      bool supports_extended_master_secret() const
         {
         return m_extensions.has<Extended_Master_Secret>();
         }

      bool supports_encrypt_then_mac() const
         {
         return m_extensions.has<Encrypt_then_MAC>();
         }

      bool supports_certificate_status_message() const
         {
         return m_extensions.has<Certificate_Status_Request>();
         }

      bool supports_session_ticket() const
         {
         return m_extensions.has<Session_Ticket>();
         }

      uint16_t srtp_profile() const
         {
         if(auto srtp = m_extensions.get<SRTP_Protection_Profiles>())
            {
            auto prof = srtp->profiles();
            if(prof.size() != 1 || prof[0] == 0)
               throw Decoding_Error("Server sent malformed DTLS-SRTP extension");
            return prof[0];
            }

         return 0;
         }

      std::string next_protocol() const
         {
         if(auto alpn = m_extensions.get<Application_Layer_Protocol_Notification>())
            return alpn->single_protocol();
         return "";
         }

      std::set<Handshake_Extension_Type> extension_types() const
         { return m_extensions.extension_types(); }

      const Extensions& extensions() const { return m_extensions; }

      bool prefers_compressed_ec_points() const
         {
         if(auto ecc_formats = m_extensions.get<Supported_Point_Formats>())
            {
            return ecc_formats->prefers_compressed();
            }
         return false;
         }

      bool random_signals_downgrade() const;

      Server_Hello(Handshake_IO& io,
                   Handshake_Hash& hash,
                   const Policy& policy,
                   Callbacks& cb,
                   RandomNumberGenerator& rng,
                   const std::vector<uint8_t>& secure_reneg_info,
                   const Client_Hello& client_hello,
                   const Server_Hello::Settings& settings,
                   const std::string next_protocol);

      Server_Hello(Handshake_IO& io,
                   Handshake_Hash& hash,
                   const Policy& policy,
                   Callbacks& cb,
                   RandomNumberGenerator& rng,
                   const std::vector<uint8_t>& secure_reneg_info,
                   const Client_Hello& client_hello,
                   Session& resumed_session,
                   bool offer_session_ticket,
                   const std::string& next_protocol);

      explicit Server_Hello(const std::vector<uint8_t>& buf);
   private:
      std::vector<uint8_t> serialize() const override;

      Protocol_Version m_version;
      std::vector<uint8_t> m_session_id, m_random;
      uint16_t m_ciphersuite;
      uint8_t m_comp_method;

      Extensions m_extensions;
   };

/**
* Client Key Exchange Message
*/
class BOTAN_UNSTABLE_API Client_Key_Exchange final : public Handshake_Message
   {
   public:
      Handshake_Type type() const override { return CLIENT_KEX; }

      const secure_vector<uint8_t>& pre_master_secret() const
         { return m_pre_master; }

      Client_Key_Exchange(Handshake_IO& io,
                          Handshake_State& state,
                          const Policy& policy,
                          Credentials_Manager& creds,
                          const Public_Key* server_public_key,
                          const std::string& hostname,
                          RandomNumberGenerator& rng);

      Client_Key_Exchange(const std::vector<uint8_t>& buf,
                          const Handshake_State& state,
                          const Private_Key* server_rsa_kex_key,
                          Credentials_Manager& creds,
                          const Policy& policy,
                          RandomNumberGenerator& rng);

   private:
      std::vector<uint8_t> serialize() const override
         { return m_key_material; }

      std::vector<uint8_t> m_key_material;
      secure_vector<uint8_t> m_pre_master;
   };

/**
* Certificate Message
*/
class BOTAN_UNSTABLE_API Certificate final : public Handshake_Message
   {
   public:
      Handshake_Type type() const override { return CERTIFICATE; }
      const std::vector<X509_Certificate>& cert_chain() const { return m_certs; }

      size_t count() const { return m_certs.size(); }
      bool empty() const { return m_certs.empty(); }

      Certificate(Handshake_IO& io,
                  Handshake_Hash& hash,
                  const std::vector<X509_Certificate>& certs);

      explicit Certificate(const std::vector<uint8_t>& buf, const Policy &policy);
   private:
      std::vector<uint8_t> serialize() const override;

      std::vector<X509_Certificate> m_certs;
   };

/**
* Certificate Status (RFC 6066)
*/
class BOTAN_UNSTABLE_API Certificate_Status final : public Handshake_Message
   {
   public:
      Handshake_Type type() const override { return CERTIFICATE_STATUS; }

      //std::shared_ptr<const OCSP::Response> response() const { return m_response; }

      const std::vector<uint8_t>& response() const { return m_response; }

      Certificate_Status(const std::vector<uint8_t>& buf);

      Certificate_Status(Handshake_IO& io,
                         Handshake_Hash& hash,
                         std::shared_ptr<const OCSP::Response> response);

      /*
       * Create a Certificate_Status message using an already DER encoded OCSP response.
       */
      Certificate_Status(Handshake_IO& io,
                         Handshake_Hash& hash,
                         std::vector<uint8_t> const& raw_response_bytes );

   private:
      std::vector<uint8_t> serialize() const override;
      std::vector<uint8_t> m_response;
   };

/**
* Certificate Request Message
*/
class BOTAN_UNSTABLE_API Certificate_Req final : public Handshake_Message
   {
   public:
      Handshake_Type type() const override { return CERTIFICATE_REQUEST; }

      const std::vector<std::string>& acceptable_cert_types() const
         { return m_cert_key_types; }

      const std::vector<X509_DN>& acceptable_CAs() const { return m_names; }

      const std::vector<Signature_Scheme>& signature_schemes() const
         {
         return m_schemes;
         }

      Certificate_Req(Handshake_IO& io,
                      Handshake_Hash& hash,
                      const Policy& policy,
                      const std::vector<X509_DN>& allowed_cas,
                      Protocol_Version version);

      Certificate_Req(const std::vector<uint8_t>& buf,
                      Protocol_Version version);
   private:
      std::vector<uint8_t> serialize() const override;

      std::vector<X509_DN> m_names;
      std::vector<std::string> m_cert_key_types;

      std::vector<Signature_Scheme> m_schemes;
   };

/**
* Certificate Verify Message
*/
class BOTAN_UNSTABLE_API Certificate_Verify final : public Handshake_Message
   {
   public:
      Handshake_Type type() const override { return CERTIFICATE_VERIFY; }

      /**
      * Check the signature on a certificate verify message
      * @param cert the purported certificate
      * @param state the handshake state
      * @param policy the TLS policy
      */
      bool verify(const X509_Certificate& cert,
                  const Handshake_State& state,
                  const Policy& policy) const;

      Certificate_Verify(Handshake_IO& io,
                         Handshake_State& state,
                         const Policy& policy,
                         RandomNumberGenerator& rng,
                         const Private_Key* key);

      Certificate_Verify(const std::vector<uint8_t>& buf,
                         Protocol_Version version);
   private:
      std::vector<uint8_t> serialize() const override;

      std::vector<uint8_t> m_signature;
      Signature_Scheme m_scheme = Signature_Scheme::NONE;
   };

/**
* Finished Message
*/
class BOTAN_UNSTABLE_API Finished final : public Handshake_Message
   {
   public:
      Handshake_Type type() const override { return FINISHED; }

      std::vector<uint8_t> verify_data() const
         { return m_verification_data; }

      bool verify(const Handshake_State& state,
                  Connection_Side side) const;

      Finished(Handshake_IO& io,
               Handshake_State& state,
               Connection_Side side);

      explicit Finished(const std::vector<uint8_t>& buf);
   private:
      std::vector<uint8_t> serialize() const override;

      std::vector<uint8_t> m_verification_data;
   };

/**
* Hello Request Message
*/
class BOTAN_UNSTABLE_API Hello_Request final : public Handshake_Message
   {
   public:
      Handshake_Type type() const override { return HELLO_REQUEST; }

      explicit Hello_Request(Handshake_IO& io);
      explicit Hello_Request(const std::vector<uint8_t>& buf);
   private:
      std::vector<uint8_t> serialize() const override;
   };

/**
* Server Key Exchange Message
*/
class BOTAN_UNSTABLE_API Server_Key_Exchange final : public Handshake_Message
   {
   public:
      Handshake_Type type() const override { return SERVER_KEX; }

      const std::vector<uint8_t>& params() const { return m_params; }

      bool verify(const Public_Key& server_key,
                  const Handshake_State& state,
                  const Policy& policy) const;

      // Only valid for certain kex types
      const Private_Key& server_kex_key() const;

#if defined(BOTAN_HAS_SRP6)
      // Only valid for SRP negotiation
      SRP6_Server_Session& server_srp_params() const
         {
         BOTAN_ASSERT_NONNULL(m_srp_params);
         return *m_srp_params;
         }
#endif

#if defined(BOTAN_HAS_CECPQ1)
      // Only valid for CECPQ1 negotiation
      const CECPQ1_key& cecpq1_key() const
         {
         BOTAN_ASSERT_NONNULL(m_cecpq1_key);
         return *m_cecpq1_key;
         }
#endif

      Server_Key_Exchange(Handshake_IO& io,
                          Handshake_State& state,
                          const Policy& policy,
                          Credentials_Manager& creds,
                          RandomNumberGenerator& rng,
                          const Private_Key* signing_key = nullptr);

      Server_Key_Exchange(const std::vector<uint8_t>& buf,
                          Kex_Algo kex_alg,
                          Auth_Method sig_alg,
                          Protocol_Version version);

      ~Server_Key_Exchange() = default;
   private:
      std::vector<uint8_t> serialize() const override;

#if defined(BOTAN_HAS_SRP6)
      std::unique_ptr<SRP6_Server_Session> m_srp_params;
#endif

#if defined(BOTAN_HAS_CECPQ1)
      std::unique_ptr<CECPQ1_key> m_cecpq1_key;
#endif

      std::unique_ptr<Private_Key> m_kex_key;

      std::vector<uint8_t> m_params;

      std::vector<uint8_t> m_signature;
      Signature_Scheme m_scheme = Signature_Scheme::NONE;
   };

/**
* Server Hello Done Message
*/
class BOTAN_UNSTABLE_API Server_Hello_Done final : public Handshake_Message
   {
   public:
      Handshake_Type type() const override { return SERVER_HELLO_DONE; }

      Server_Hello_Done(Handshake_IO& io, Handshake_Hash& hash);
      explicit Server_Hello_Done(const std::vector<uint8_t>& buf);
   private:
      std::vector<uint8_t> serialize() const override;
   };

/**
* New Session Ticket Message
*/
class BOTAN_UNSTABLE_API New_Session_Ticket final : public Handshake_Message
   {
   public:
      Handshake_Type type() const override { return NEW_SESSION_TICKET; }

      uint32_t ticket_lifetime_hint() const { return m_ticket_lifetime_hint; }
      const std::vector<uint8_t>& ticket() const { return m_ticket; }

      New_Session_Ticket(Handshake_IO& io,
                         Handshake_Hash& hash,
                         const std::vector<uint8_t>& ticket,
                         uint32_t lifetime);

      New_Session_Ticket(Handshake_IO& io,
                         Handshake_Hash& hash);

      explicit New_Session_Ticket(const std::vector<uint8_t>& buf);
   private:
      std::vector<uint8_t> serialize() const override;

      uint32_t m_ticket_lifetime_hint = 0;
      std::vector<uint8_t> m_ticket;
   };

/**
* Change Cipher Spec
*/
class BOTAN_UNSTABLE_API Change_Cipher_Spec final : public Handshake_Message
   {
   public:
      Handshake_Type type() const override { return HANDSHAKE_CCS; }

      std::vector<uint8_t> serialize() const override
         { return std::vector<uint8_t>(1, 1); }
   };

}

}

namespace Botan {

namespace TLS {

class Server_Handshake_State;

/**
* TLS Server
*/
class BOTAN_PUBLIC_API(2,0) Server final : public Channel
   {
   public:
      typedef std::function<std::string (std::vector<std::string>)> next_protocol_fn;

      /**
      * Server initialization
      *
      * @param callbacks contains a set of callback function references
      *        required by the TLS client.
      *
      * @param session_manager manages session state
      *
      * @param creds manages application/user credentials
      *
      * @param policy specifies other connection policy information
      *
      * @param rng a random number generator
      *
      * @param is_datagram set to true if this server should expect DTLS
      *        connections. Otherwise TLS connections are expected.
      *
      * @param reserved_io_buffer_size This many bytes of memory will
      *        be preallocated for the read and write buffers. Smaller
      *        values just mean reallocations and copies are more likely.
      */
      Server(Callbacks& callbacks,
             Session_Manager& session_manager,
             Credentials_Manager& creds,
             const Policy& policy,
             RandomNumberGenerator& rng,
             bool is_datagram = false,
             size_t reserved_io_buffer_size = TLS::Server::IO_BUF_DEFAULT_SIZE
         );

      /**
       * DEPRECATED. This constructor is only provided for backward
       * compatibility and should not be used in new implementations.
       * It will be removed in a future release.
       */
      BOTAN_DEPRECATED("Use TLS::Server(TLS::Callbacks ...)")
      Server(output_fn output,
             data_cb data_cb,
             alert_cb recv_alert_cb,
             handshake_cb hs_cb,
             Session_Manager& session_manager,
             Credentials_Manager& creds,
             const Policy& policy,
             RandomNumberGenerator& rng,
             next_protocol_fn next_proto = next_protocol_fn(),
             bool is_datagram = false,
             size_t reserved_io_buffer_size = TLS::Server::IO_BUF_DEFAULT_SIZE
         );

      /**
       * DEPRECATED. This constructor is only provided for backward
       * compatibility and should not be used in new implementations.
       * It will be removed in a future release.
       */
      BOTAN_DEPRECATED("Use TLS::Server(TLS::Callbacks ...)")
      Server(output_fn output,
             data_cb data_cb,
             alert_cb recv_alert_cb,
             handshake_cb hs_cb,
             handshake_msg_cb hs_msg_cb,
             Session_Manager& session_manager,
             Credentials_Manager& creds,
             const Policy& policy,
             RandomNumberGenerator& rng,
             next_protocol_fn next_proto = next_protocol_fn(),
             bool is_datagram = false
         );

      /**
      * Return the protocol notification set by the client (using the
      * ALPN extension) for this connection, if any. This value is not
      * tied to the session and a later renegotiation of the same
      * session can choose a new protocol.
      */
      std::string next_protocol() const { return m_next_protocol; }

      /**
      * Return the protocol notification set by the client (using the
      * ALPN extension) for this connection, if any. This value is not
      * tied to the session and a later renegotiation of the same
      * session can choose a new protocol.
      */
      std::string application_protocol() const override { return m_next_protocol; }

   private:
      std::vector<X509_Certificate>
         get_peer_cert_chain(const Handshake_State& state) const override;

      void initiate_handshake(Handshake_State& state,
                              bool force_full_renegotiation) override;

      void process_handshake_msg(const Handshake_State* active_state,
                                 Handshake_State& pending_state,
                                 Handshake_Type type,
                                 const std::vector<uint8_t>& contents,
                                 bool epoch0_restart) override;

      void process_client_hello_msg(const Handshake_State* active_state,
                                    Server_Handshake_State& pending_state,
                                    const std::vector<uint8_t>& contents,
                                    bool epoch0_restart);

      void process_certificate_msg(Server_Handshake_State& pending_state,
                                   const std::vector<uint8_t>& contents);

      void process_client_key_exchange_msg(Server_Handshake_State& pending_state,
                                           const std::vector<uint8_t>& contents);

      void process_change_cipher_spec_msg(Server_Handshake_State& pending_state);

      void process_certificate_verify_msg(Server_Handshake_State& pending_state,
                                          Handshake_Type type,
                                          const std::vector<uint8_t>& contents);

      void process_finished_msg(Server_Handshake_State& pending_state,
                                Handshake_Type type,
                                const std::vector<uint8_t>& contents);

      void session_resume(Server_Handshake_State& pending_state,
                          bool have_session_ticket_key,
                          Session& session_info);

      void session_create(Server_Handshake_State& pending_state,
                          bool have_session_ticket_key);

      Handshake_State* new_handshake_state(Handshake_IO* io) override;

      Credentials_Manager& m_creds;
      std::string m_next_protocol;

      // Set by deprecated constructor, Server calls both this fn and Callbacks version
      next_protocol_fn m_choose_next_protocol;
   };

}

}

namespace Botan {

/*
* Get information describing the version
*/

/**
* Get a human-readable string identifying the version of Botan.
* No particular format should be assumed.
* @return version string
*/
BOTAN_PUBLIC_API(2,0) std::string version_string();

/**
* Same as version_string() except returning a pointer to a statically
* allocated string.
* @return version string
*/
BOTAN_PUBLIC_API(2,0) const char* version_cstr();

/**
* Return a version string of the form "MAJOR.MINOR.PATCH" where
* each of the values is an integer.
*/
BOTAN_PUBLIC_API(2,4) std::string short_version_string();

/**
* Same as version_short_string except returning a pointer to the string.
*/
BOTAN_PUBLIC_API(2,4) const char* short_version_cstr();

/**
* Return the date this version of botan was released, in an integer of
* the form YYYYMMDD. For instance a version released on May 21, 2013
* would return the integer 20130521. If the currently running version
* is not an official release, this function will return 0 instead.
*
* @return release date, or zero if unreleased
*/
BOTAN_PUBLIC_API(2,0) uint32_t version_datestamp();

/**
* Get the major version number.
* @return major version number
*/
BOTAN_PUBLIC_API(2,0) uint32_t version_major();

/**
* Get the minor version number.
* @return minor version number
*/
BOTAN_PUBLIC_API(2,0) uint32_t version_minor();

/**
* Get the patch number.
* @return patch number
*/
BOTAN_PUBLIC_API(2,0) uint32_t version_patch();

/**
* Usable for checking that the DLL version loaded at runtime exactly
* matches the compile-time version. Call using BOTAN_VERSION_* macro
* values. Returns the empty string if an exact match, otherwise an
* appropriate message. Added with 1.11.26.
*/
BOTAN_PUBLIC_API(2,0) std::string
runtime_version_check(uint32_t major,
                      uint32_t minor,
                      uint32_t patch);

/*
* Macros for compile-time version checks
*/
#define BOTAN_VERSION_CODE_FOR(a,b,c) ((a << 16) | (b << 8) | (c))

/**
* Compare using BOTAN_VERSION_CODE_FOR, as in
*  # if BOTAN_VERSION_CODE < BOTAN_VERSION_CODE_FOR(1,8,0)
*  #    error "Botan version too old"
*  # endif
*/
#define BOTAN_VERSION_CODE BOTAN_VERSION_CODE_FOR(BOTAN_VERSION_MAJOR, \
                                                  BOTAN_VERSION_MINOR, \
                                                  BOTAN_VERSION_PATCH)

}
BOTAN_FUTURE_INTERNAL_HEADER(workfactor.h)

namespace Botan {

/**
* Estimate work factor for discrete logarithm
* @param prime_group_size size of the group in bits
* @return estimated security level for this group
*/
BOTAN_PUBLIC_API(2,0) size_t dl_work_factor(size_t prime_group_size);

/**
* Return the appropriate exponent size to use for a particular prime
* group. This is twice the size of the estimated cost of breaking the
* key using an index calculus attack; the assumption is that if an
* arbitrary discrete log on a group of size bits would take about 2^n
* effort, and thus using an exponent of size 2^(2*n) implies that all
* available attacks are about as easy (as e.g Pollard's kangaroo
* algorithm can compute the DL in sqrt(x) operations) while minimizing
* the exponent size for performance reasons.
*/
BOTAN_PUBLIC_API(2,0) size_t dl_exponent_size(size_t prime_group_size);

/**
* Estimate work factor for integer factorization
* @param n_bits size of modulus in bits
* @return estimated security level for this modulus
*/
BOTAN_PUBLIC_API(2,0) size_t if_work_factor(size_t n_bits);

/**
* Estimate work factor for EC discrete logarithm
* @param prime_group_size size of the group in bits
* @return estimated security level for this group
*/
BOTAN_PUBLIC_API(2,0) size_t ecp_work_factor(size_t prime_group_size);

}

#if defined(BOTAN_HAS_SYSTEM_RNG)
#endif

namespace Botan {

class BigInt;
class Private_Key;
class PKCS10_Request;
class PK_Signer;

/**
* This class represents X.509 Certificate Authorities (CAs).
*/
class BOTAN_PUBLIC_API(2,0) X509_CA final
   {
   public:
      /**
      * Sign a PKCS#10 Request.
      * @param req the request to sign
      * @param rng the rng to use
      * @param not_before the starting time for the certificate
      * @param not_after the expiration time for the certificate
      * @return resulting certificate
      */
      X509_Certificate sign_request(const PKCS10_Request& req,
                                    RandomNumberGenerator& rng,
                                    const X509_Time& not_before,
                                    const X509_Time& not_after) const;

      /**
      * Sign a PKCS#10 Request.
      * @param req the request to sign
      * @param rng the rng to use
      * @param serial_number the serial number the cert will be assigned.
      * @param not_before the starting time for the certificate
      * @param not_after the expiration time for the certificate
      * @return resulting certificate
      */
      X509_Certificate sign_request(const PKCS10_Request& req,
                                    RandomNumberGenerator& rng,
                                    const BigInt& serial_number,
                                    const X509_Time& not_before,
                                    const X509_Time& not_after) const;

      /**
      * Get the certificate of this CA.
      * @return CA certificate
      */
      X509_Certificate ca_certificate() const;

      /**
      * Create a new and empty CRL for this CA.
      * @param rng the random number generator to use
      * @param issue_time the issue time (typically system_clock::now)
      * @param next_update the time interval after issue_data within which
      *        a new CRL will be produced.
      * @return new CRL
      */
      X509_CRL new_crl(RandomNumberGenerator& rng,
                       std::chrono::system_clock::time_point issue_time,
                       std::chrono::seconds next_update) const;

      /**
      * Create a new CRL by with additional entries.
      * @param last_crl the last CRL of this CA to add the new entries to
      * @param new_entries contains the new CRL entries to be added to the CRL
      * @param rng the random number generator to use
      * @param issue_time the issue time (typically system_clock::now)
      * @param next_update the time interval after issue_data within which
      *        a new CRL will be produced.
      */
      X509_CRL update_crl(const X509_CRL& last_crl,
                          const std::vector<CRL_Entry>& new_entries,
                          RandomNumberGenerator& rng,
                          std::chrono::system_clock::time_point issue_time,
                          std::chrono::seconds next_update) const;

      /**
      * Create a new and empty CRL for this CA.
      * @param rng the random number generator to use
      * @param next_update the time to set in next update in seconds
      * as the offset from the current time
      * @return new CRL
      */
      X509_CRL new_crl(RandomNumberGenerator& rng,
                       uint32_t next_update = 604800) const;

      /**
      * Create a new CRL by with additional entries.
      * @param last_crl the last CRL of this CA to add the new entries to
      * @param new_entries contains the new CRL entries to be added to the CRL
      * @param rng the random number generator to use
      * @param next_update the time to set in next update in seconds
      * as the offset from the current time
      */
      X509_CRL update_crl(const X509_CRL& last_crl,
                          const std::vector<CRL_Entry>& new_entries,
                          RandomNumberGenerator& rng,
                          uint32_t next_update = 604800) const;

      /**
      * Interface for creating new certificates
      * @param signer a signing object
      * @param rng a random number generator
      * @param sig_algo the signature algorithm identifier
      * @param pub_key the serialized public key
      * @param not_before the start time of the certificate
      * @param not_after the end time of the certificate
      * @param issuer_dn the DN of the issuer
      * @param subject_dn the DN of the subject
      * @param extensions an optional list of certificate extensions
      * @returns newly minted certificate
      */
      static X509_Certificate make_cert(PK_Signer* signer,
                                        RandomNumberGenerator& rng,
                                        const AlgorithmIdentifier& sig_algo,
                                        const std::vector<uint8_t>& pub_key,
                                        const X509_Time& not_before,
                                        const X509_Time& not_after,
                                        const X509_DN& issuer_dn,
                                        const X509_DN& subject_dn,
                                        const Extensions& extensions);

      /**
      * Interface for creating new certificates
      * @param signer a signing object
      * @param rng a random number generator
      * @param serial_number the serial number the cert will be assigned
      * @param sig_algo the signature algorithm identifier
      * @param pub_key the serialized public key
      * @param not_before the start time of the certificate
      * @param not_after the end time of the certificate
      * @param issuer_dn the DN of the issuer
      * @param subject_dn the DN of the subject
      * @param extensions an optional list of certificate extensions
      * @returns newly minted certificate
      */
      static X509_Certificate make_cert(PK_Signer* signer,
                                        RandomNumberGenerator& rng,
                                        const BigInt& serial_number,
                                        const AlgorithmIdentifier& sig_algo,
                                        const std::vector<uint8_t>& pub_key,
                                        const X509_Time& not_before,
                                        const X509_Time& not_after,
                                        const X509_DN& issuer_dn,
                                        const X509_DN& subject_dn,
                                        const Extensions& extensions);

      /**
      * Create a new CA object.
      * @param ca_certificate the certificate of the CA
      * @param key the private key of the CA
      * @param hash_fn name of a hash function to use for signing
      * @param rng the random generator to use
      */
      X509_CA(const X509_Certificate& ca_certificate,
              const Private_Key& key,
              const std::string& hash_fn,
              RandomNumberGenerator& rng);

      /**
      * Create a new CA object.
      * @param ca_certificate the certificate of the CA
      * @param key the private key of the CA
      * @param opts additional options, e.g. padding, as key value pairs
      * @param hash_fn name of a hash function to use for signing
      * @param rng the random generator to use
      */
      X509_CA(const X509_Certificate& ca_certificate,
              const Private_Key& key,
              const std::map<std::string,std::string>& opts,
              const std::string& hash_fn,
              RandomNumberGenerator& rng);

#if defined(BOTAN_HAS_SYSTEM_RNG)
      BOTAN_DEPRECATED("Use version taking RNG object")
      X509_CA(const X509_Certificate& ca_certificate,
              const Private_Key& key,
              const std::string& hash_fn) :
         X509_CA(ca_certificate, key, hash_fn, system_rng())
         {}
#endif

      X509_CA(const X509_CA&) = delete;
      X509_CA& operator=(const X509_CA&) = delete;

      X509_CA(X509_CA&&) = default;
      X509_CA& operator=(X509_CA&&) = default;

      ~X509_CA();

   private:
      X509_CRL make_crl(const std::vector<CRL_Entry>& entries,
                        uint32_t crl_number,
                        RandomNumberGenerator& rng,
                        std::chrono::system_clock::time_point issue_time,
                        std::chrono::seconds next_update) const;

      AlgorithmIdentifier m_ca_sig_algo;
      X509_Certificate m_ca_cert;
      std::string m_hash_fn;
      std::unique_ptr<PK_Signer> m_signer;
   };

/**
* Choose the default signature format for a certain public key signature
* scheme.
* @param key will be the key to choose a padding scheme for
* @param rng the random generator to use
* @param hash_fn is the desired hash function
* @param alg_id will be set to the chosen scheme
* @return A PK_Signer object for generating signatures
*/
BOTAN_PUBLIC_API(2,0) PK_Signer* choose_sig_format(const Private_Key& key,
                                       RandomNumberGenerator& rng,
                                       const std::string& hash_fn,
                                       AlgorithmIdentifier& alg_id);

/**
* @verbatim
* Choose the default signature format for a certain public key signature
* scheme.
*
* The only option recognized by opts at this moment is "padding"
* Find an entry from src/build-data/oids.txt under [signature] of the form
* <sig_algo>/<padding>[(<hash_algo>)] and add {"padding",<padding>}
* to opts.
* @endverbatim
*
* @param key will be the key to choose a padding scheme for
* @param opts contains additional options for building the certificate
* @param rng the random generator to use
* @param hash_fn is the desired hash function
* @param alg_id will be set to the chosen scheme
* @return A PK_Signer object for generating signatures
*/
PK_Signer* choose_sig_format(const Private_Key& key,
                             const std::map<std::string,std::string>& opts,
                             RandomNumberGenerator& rng,
                             const std::string& hash_fn,
                             AlgorithmIdentifier& alg_id);

}

namespace Botan {

class Data_Store;
class X509_Certificate;

namespace Cert_Extension {

static const size_t NO_CERT_PATH_LIMIT = 0xFFFFFFF0;

/**
* Basic Constraints Extension
*/
class BOTAN_PUBLIC_API(2,0) Basic_Constraints final : public Certificate_Extension
   {
   public:
      Basic_Constraints* copy() const override
         { return new Basic_Constraints(m_is_ca, m_path_limit); }

      Basic_Constraints(bool ca = false, size_t limit = 0) :
         m_is_ca(ca), m_path_limit(limit) {}

      bool get_is_ca() const { return m_is_ca; }
      size_t get_path_limit() const;

      static OID static_oid() { return OID("2.5.29.19"); }
      OID oid_of() const override { return static_oid(); }

   private:
      std::string oid_name() const override
         { return "X509v3.BasicConstraints"; }

      std::vector<uint8_t> encode_inner() const override;
      void decode_inner(const std::vector<uint8_t>&) override;
      void contents_to(Data_Store&, Data_Store&) const override;

      bool m_is_ca;
      size_t m_path_limit;
   };

/**
* Key Usage Constraints Extension
*/
class BOTAN_PUBLIC_API(2,0) Key_Usage final : public Certificate_Extension
   {
   public:
      Key_Usage* copy() const override { return new Key_Usage(m_constraints); }

      explicit Key_Usage(Key_Constraints c = NO_CONSTRAINTS) : m_constraints(c) {}

      Key_Constraints get_constraints() const { return m_constraints; }

      static OID static_oid() { return OID("2.5.29.15"); }
      OID oid_of() const override { return static_oid(); }

   private:
      std::string oid_name() const override { return "X509v3.KeyUsage"; }

      bool should_encode() const override
         { return (m_constraints != NO_CONSTRAINTS); }
      std::vector<uint8_t> encode_inner() const override;
      void decode_inner(const std::vector<uint8_t>&) override;
      void contents_to(Data_Store&, Data_Store&) const override;

      Key_Constraints m_constraints;
   };

/**
* Subject Key Identifier Extension
*/
class BOTAN_PUBLIC_API(2,0) Subject_Key_ID final : public Certificate_Extension
   {
   public:
      Subject_Key_ID() = default;

      explicit Subject_Key_ID(const std::vector<uint8_t>& k) : m_key_id(k) {}

      Subject_Key_ID(const std::vector<uint8_t>& public_key,
                     const std::string& hash_fn);

      Subject_Key_ID* copy() const override
         { return new Subject_Key_ID(m_key_id); }

      const std::vector<uint8_t>& get_key_id() const { return m_key_id; }

      static OID static_oid() { return OID("2.5.29.14"); }
      OID oid_of() const override { return static_oid(); }

   private:

      std::string oid_name() const override
         { return "X509v3.SubjectKeyIdentifier"; }

      bool should_encode() const override { return (m_key_id.size() > 0); }
      std::vector<uint8_t> encode_inner() const override;
      void decode_inner(const std::vector<uint8_t>&) override;
      void contents_to(Data_Store&, Data_Store&) const override;

      std::vector<uint8_t> m_key_id;
   };

/**
* Authority Key Identifier Extension
*/
class BOTAN_PUBLIC_API(2,0) Authority_Key_ID final : public Certificate_Extension
   {
   public:
      Authority_Key_ID* copy() const override
         { return new Authority_Key_ID(m_key_id); }

      Authority_Key_ID() = default;
      explicit Authority_Key_ID(const std::vector<uint8_t>& k) : m_key_id(k) {}

      const std::vector<uint8_t>& get_key_id() const { return m_key_id; }

      static OID static_oid() { return OID("2.5.29.35"); }
      OID oid_of() const override { return static_oid(); }

   private:
      std::string oid_name() const override
         { return "X509v3.AuthorityKeyIdentifier"; }

      bool should_encode() const override { return (m_key_id.size() > 0); }
      std::vector<uint8_t> encode_inner() const override;
      void decode_inner(const std::vector<uint8_t>&) override;
      void contents_to(Data_Store&, Data_Store&) const override;

      std::vector<uint8_t> m_key_id;
   };

/**
* Subject Alternative Name Extension
*/
class BOTAN_PUBLIC_API(2,4) Subject_Alternative_Name final : public Certificate_Extension
   {
   public:
      const AlternativeName& get_alt_name() const { return m_alt_name; }

      static OID static_oid() { return OID("2.5.29.17"); }
      OID oid_of() const override { return static_oid(); }

      Subject_Alternative_Name* copy() const override
         { return new Subject_Alternative_Name(get_alt_name()); }

      explicit Subject_Alternative_Name(const AlternativeName& name = AlternativeName()) :
         m_alt_name(name) {}

   private:
      std::string oid_name() const override { return "X509v3.SubjectAlternativeName"; }

      bool should_encode() const override { return m_alt_name.has_items(); }
      std::vector<uint8_t> encode_inner() const override;
      void decode_inner(const std::vector<uint8_t>&) override;
      void contents_to(Data_Store&, Data_Store&) const override;

      AlternativeName m_alt_name;
   };

/**
* Issuer Alternative Name Extension
*/
class BOTAN_PUBLIC_API(2,0) Issuer_Alternative_Name final : public Certificate_Extension
   {
   public:
      const AlternativeName& get_alt_name() const { return m_alt_name; }

      static OID static_oid() { return OID("2.5.29.18"); }
      OID oid_of() const override { return static_oid(); }

      Issuer_Alternative_Name* copy() const override
         { return new Issuer_Alternative_Name(get_alt_name()); }

      explicit Issuer_Alternative_Name(const AlternativeName& name = AlternativeName()) :
         m_alt_name(name) {}

   private:
      std::string oid_name() const override { return "X509v3.IssuerAlternativeName"; }

      bool should_encode() const override { return m_alt_name.has_items(); }
      std::vector<uint8_t> encode_inner() const override;
      void decode_inner(const std::vector<uint8_t>&) override;
      void contents_to(Data_Store&, Data_Store&) const override;

      AlternativeName m_alt_name;
   };

/**
* Extended Key Usage Extension
*/
class BOTAN_PUBLIC_API(2,0) Extended_Key_Usage final : public Certificate_Extension
   {
   public:
      Extended_Key_Usage* copy() const override
         { return new Extended_Key_Usage(m_oids); }

      Extended_Key_Usage() = default;
      explicit Extended_Key_Usage(const std::vector<OID>& o) : m_oids(o) {}

      const std::vector<OID>& get_oids() const { return m_oids; }

      static OID static_oid() { return OID("2.5.29.37"); }
      OID oid_of() const override { return static_oid(); }

   private:
      std::string oid_name() const override { return "X509v3.ExtendedKeyUsage"; }

      bool should_encode() const override { return (m_oids.size() > 0); }
      std::vector<uint8_t> encode_inner() const override;
      void decode_inner(const std::vector<uint8_t>&) override;
      void contents_to(Data_Store&, Data_Store&) const override;

      std::vector<OID> m_oids;
   };

/**
* Name Constraints
*/
class BOTAN_PUBLIC_API(2,0) Name_Constraints final : public Certificate_Extension
   {
   public:
      Name_Constraints* copy() const override
         { return new Name_Constraints(m_name_constraints); }

      Name_Constraints() = default;
      Name_Constraints(const NameConstraints &nc) : m_name_constraints(nc) {}

      void validate(const X509_Certificate& subject, const X509_Certificate& issuer,
            const std::vector<std::shared_ptr<const X509_Certificate>>& cert_path,
            std::vector<std::set<Certificate_Status_Code>>& cert_status,
            size_t pos) override;

      const NameConstraints& get_name_constraints() const { return m_name_constraints; }

      static OID static_oid() { return OID("2.5.29.30"); }
      OID oid_of() const override { return static_oid(); }

   private:
      std::string oid_name() const override
         { return "X509v3.NameConstraints"; }

      bool should_encode() const override { return true; }
      std::vector<uint8_t> encode_inner() const override;
      void decode_inner(const std::vector<uint8_t>&) override;
      void contents_to(Data_Store&, Data_Store&) const override;

      NameConstraints m_name_constraints;
   };

/**
* Certificate Policies Extension
*/
class BOTAN_PUBLIC_API(2,0) Certificate_Policies final : public Certificate_Extension
   {
   public:
      Certificate_Policies* copy() const override
         { return new Certificate_Policies(m_oids); }

      Certificate_Policies() = default;
      explicit Certificate_Policies(const std::vector<OID>& o) : m_oids(o) {}

      BOTAN_DEPRECATED("Use get_policy_oids")
      std::vector<OID> get_oids() const { return m_oids; }

      const std::vector<OID>& get_policy_oids() const { return m_oids; }

      static OID static_oid() { return OID("2.5.29.32"); }
      OID oid_of() const override { return static_oid(); }

      void validate(const X509_Certificate& subject, const X509_Certificate& issuer,
            const std::vector<std::shared_ptr<const X509_Certificate>>& cert_path,
            std::vector<std::set<Certificate_Status_Code>>& cert_status,
            size_t pos) override;
   private:
      std::string oid_name() const override
         { return "X509v3.CertificatePolicies"; }

      bool should_encode() const override { return (m_oids.size() > 0); }
      std::vector<uint8_t> encode_inner() const override;
      void decode_inner(const std::vector<uint8_t>&) override;
      void contents_to(Data_Store&, Data_Store&) const override;

      std::vector<OID> m_oids;
   };

/**
* Authority Information Access Extension
*/
class BOTAN_PUBLIC_API(2,0) Authority_Information_Access final : public Certificate_Extension
   {
   public:
      Authority_Information_Access* copy() const override
         { return new Authority_Information_Access(m_ocsp_responder, m_ca_issuers); }

      Authority_Information_Access() = default;

      explicit Authority_Information_Access(const std::string& ocsp, const std::vector<std::string>& ca_issuers = std::vector<std::string>()) :
         m_ocsp_responder(ocsp), m_ca_issuers(ca_issuers) {}

      std::string ocsp_responder() const { return m_ocsp_responder; }

      static OID static_oid() { return OID("1.3.6.1.5.5.7.1.1"); }
      OID oid_of() const override { return static_oid(); }
      const std::vector<std::string> ca_issuers() const { return m_ca_issuers; }

   private:
      std::string oid_name() const override
         { return "PKIX.AuthorityInformationAccess"; }

      bool should_encode() const override { return (!m_ocsp_responder.empty()); }

      std::vector<uint8_t> encode_inner() const override;
      void decode_inner(const std::vector<uint8_t>&) override;

      void contents_to(Data_Store&, Data_Store&) const override;

      std::string m_ocsp_responder;
      std::vector<std::string> m_ca_issuers;
   };

/**
* CRL Number Extension
*/
class BOTAN_PUBLIC_API(2,0) CRL_Number final : public Certificate_Extension
   {
   public:
      CRL_Number* copy() const override;

      CRL_Number() : m_has_value(false), m_crl_number(0) {}
      CRL_Number(size_t n) : m_has_value(true), m_crl_number(n) {}

      size_t get_crl_number() const;

      static OID static_oid() { return OID("2.5.29.20"); }
      OID oid_of() const override { return static_oid(); }

   private:
      std::string oid_name() const override { return "X509v3.CRLNumber"; }

      bool should_encode() const override { return m_has_value; }
      std::vector<uint8_t> encode_inner() const override;
      void decode_inner(const std::vector<uint8_t>&) override;
      void contents_to(Data_Store&, Data_Store&) const override;

      bool m_has_value;
      size_t m_crl_number;
   };

/**
* CRL Entry Reason Code Extension
*/
class BOTAN_PUBLIC_API(2,0) CRL_ReasonCode final : public Certificate_Extension
   {
   public:
      CRL_ReasonCode* copy() const override
         { return new CRL_ReasonCode(m_reason); }

      explicit CRL_ReasonCode(CRL_Code r = UNSPECIFIED) : m_reason(r) {}

      CRL_Code get_reason() const { return m_reason; }

      static OID static_oid() { return OID("2.5.29.21"); }
      OID oid_of() const override { return static_oid(); }

   private:
      std::string oid_name() const override { return "X509v3.ReasonCode"; }

      bool should_encode() const override { return (m_reason != UNSPECIFIED); }
      std::vector<uint8_t> encode_inner() const override;
      void decode_inner(const std::vector<uint8_t>&) override;
      void contents_to(Data_Store&, Data_Store&) const override;

      CRL_Code m_reason;
   };

/**
* CRL Distribution Points Extension
* todo enforce restrictions from RFC 5280 4.2.1.13
*/
class BOTAN_PUBLIC_API(2,0) CRL_Distribution_Points final : public Certificate_Extension
   {
   public:
      class BOTAN_PUBLIC_API(2,0) Distribution_Point final : public ASN1_Object
         {
         public:
            void encode_into(class DER_Encoder&) const override;
            void decode_from(class BER_Decoder&) override;

            const AlternativeName& point() const { return m_point; }
         private:
            AlternativeName m_point;
         };

      CRL_Distribution_Points* copy() const override
         { return new CRL_Distribution_Points(m_distribution_points); }

      CRL_Distribution_Points() = default;

      explicit CRL_Distribution_Points(const std::vector<Distribution_Point>& points) :
         m_distribution_points(points) {}

      const std::vector<Distribution_Point>& distribution_points() const
         { return m_distribution_points; }

      const std::vector<std::string>& crl_distribution_urls() const
         { return m_crl_distribution_urls; }

      static OID static_oid() { return OID("2.5.29.31"); }
      OID oid_of() const override { return static_oid(); }

   private:
      std::string oid_name() const override
         { return "X509v3.CRLDistributionPoints"; }

      bool should_encode() const override
         { return !m_distribution_points.empty(); }

      std::vector<uint8_t> encode_inner() const override;
      void decode_inner(const std::vector<uint8_t>&) override;
      void contents_to(Data_Store&, Data_Store&) const override;

      std::vector<Distribution_Point> m_distribution_points;
      std::vector<std::string> m_crl_distribution_urls;
   };

/**
* CRL Issuing Distribution Point Extension
* todo enforce restrictions from RFC 5280 5.2.5
*/
class CRL_Issuing_Distribution_Point final : public Certificate_Extension
   {
   public:
      CRL_Issuing_Distribution_Point() = default;

      explicit CRL_Issuing_Distribution_Point(const CRL_Distribution_Points::Distribution_Point& distribution_point) :
         m_distribution_point(distribution_point) {}

      CRL_Issuing_Distribution_Point* copy() const override
         { return new CRL_Issuing_Distribution_Point(m_distribution_point); }

      const AlternativeName& get_point() const
         { return m_distribution_point.point(); }

      static OID static_oid() { return OID("2.5.29.28"); }
      OID oid_of() const override { return static_oid(); }

   private:
      std::string oid_name() const override
         { return "X509v3.CRLIssuingDistributionPoint"; }

      bool should_encode() const override { return true; }
      std::vector<uint8_t> encode_inner() const override;
      void decode_inner(const std::vector<uint8_t>&) override;
      void contents_to(Data_Store&, Data_Store&) const override;

      CRL_Distribution_Points::Distribution_Point m_distribution_point;
   };

/**
* An unknown X.509 extension
* Will add a failure to the path validation result, if critical
*/
class BOTAN_PUBLIC_API(2,4) Unknown_Extension final : public Certificate_Extension
   {
   public:
      Unknown_Extension(const OID& oid, bool critical) :
         m_oid(oid), m_critical(critical) {}

      Unknown_Extension* copy() const override
         { return new Unknown_Extension(m_oid, m_critical); }

      /**
      * Return the OID of this unknown extension
      */
      OID oid_of() const override
         { return m_oid; }

      //static_oid not defined for Unknown_Extension

      /**
      * Return the extension contents
      */
      const std::vector<uint8_t>& extension_contents() const { return m_bytes; }

      /**
      * Return if this extension was marked critical
      */
      bool is_critical_extension() const { return m_critical; }

      void validate(const X509_Certificate&, const X509_Certificate&,
            const std::vector<std::shared_ptr<const X509_Certificate>>&,
            std::vector<std::set<Certificate_Status_Code>>& cert_status,
            size_t pos) override
         {
         if(m_critical)
            {
            cert_status.at(pos).insert(Certificate_Status_Code::UNKNOWN_CRITICAL_EXTENSION);
            }
         }

   private:
      std::string oid_name() const override { return ""; }

      bool should_encode() const override { return true; }
      std::vector<uint8_t> encode_inner() const override;
      void decode_inner(const std::vector<uint8_t>&) override;
      void contents_to(Data_Store&, Data_Store&) const override;

      OID m_oid;
      bool m_critical;
      std::vector<uint8_t> m_bytes;
   };

   }

}

namespace Botan {

class RandomNumberGenerator;
class DataSource;

/**
* The two types of X509 encoding supported by Botan.
* This enum is not used anymore, and will be removed in a future major release.
*/
enum X509_Encoding { RAW_BER, PEM };

/**
* This namespace contains functions for handling X.509 public keys
*/
namespace X509 {

/**
* BER encode a key
* @param key the public key to encode
* @return BER encoding of this key
*/
BOTAN_PUBLIC_API(2,0) std::vector<uint8_t> BER_encode(const Public_Key& key);

/**
* PEM encode a public key into a string.
* @param key the key to encode
* @return PEM encoded key
*/
BOTAN_PUBLIC_API(2,0) std::string PEM_encode(const Public_Key& key);

/**
* Create a public key from a data source.
* @param source the source providing the DER or PEM encoded key
* @return new public key object
*/
BOTAN_PUBLIC_API(2,0) Public_Key* load_key(DataSource& source);

#if defined(BOTAN_TARGET_OS_HAS_FILESYSTEM)
/**
* Create a public key from a file
* @param filename pathname to the file to load
* @return new public key object
*/
BOTAN_PUBLIC_API(2,0) Public_Key* load_key(const std::string& filename);
#endif

/**
* Create a public key from a memory region.
* @param enc the memory region containing the DER or PEM encoded key
* @return new public key object
*/
BOTAN_PUBLIC_API(2,0) Public_Key* load_key(const std::vector<uint8_t>& enc);

/**
* Copy a key.
* @param key the public key to copy
* @return new public key object
*/
BOTAN_PUBLIC_API(2,0) Public_Key* copy_key(const Public_Key& key);

}

}

#if defined(BOTAN_TARGET_OS_HAS_THREADS) && defined(BOTAN_HAS_HTTP_UTIL)
  #define BOTAN_HAS_ONLINE_REVOCATION_CHECKS
#endif

namespace Botan {

/**
* This type represents the validation status of an entire certificate path.
* There is one set of status codes for each certificate in the path.
*/
typedef std::vector<std::set<Certificate_Status_Code>> CertificatePathStatusCodes;

/**
* Specifies restrictions on the PKIX path validation
*/
class BOTAN_PUBLIC_API(2,0) Path_Validation_Restrictions final
   {
   public:
      /**
      * @param require_rev if true, revocation information is required

      * @param minimum_key_strength is the minimum strength (in terms of
      *    operations, eg 80 means 2^80) of a signature. Signatures weaker than
      *    this are rejected. If more than 80, SHA-1 signatures are also
      *    rejected. If possible use at least setting 110.
      *
      *        80 bit strength requires 1024 bit RSA
      *        110 bit strength requires 2k bit RSA
      *        128 bit strength requires ~3k bit RSA or P-256
      * @param ocsp_all_intermediates Make OCSP requests for all CAs as
      * well as end entity (if OCSP enabled in path validation request)
      * @param max_ocsp_age maximum age of OCSP responses w/o next_update.
      *        If zero, there is no maximum age
      */
      Path_Validation_Restrictions(bool require_rev = false,
                                   size_t minimum_key_strength = 110,
                                   bool ocsp_all_intermediates = false,
                                   std::chrono::seconds max_ocsp_age = std::chrono::seconds::zero());

      /**
      * @param require_rev if true, revocation information is required
      * @param minimum_key_strength is the minimum strength (in terms of
      *        operations, eg 80 means 2^80) of a signature. Signatures
      *        weaker than this are rejected.
      * @param ocsp_all_intermediates Make OCSP requests for all CAs as
      * well as end entity (if OCSP enabled in path validation request)
      * @param trusted_hashes a set of trusted hashes. Any signatures
      *        created using a hash other than one of these will be
      *        rejected.
      * @param max_ocsp_age maximum age of OCSP responses w/o next_update.
      *        If zero, there is no maximum age
      */
      Path_Validation_Restrictions(bool require_rev,
                                   size_t minimum_key_strength,
                                   bool ocsp_all_intermediates,
                                   const std::set<std::string>& trusted_hashes,
                                   std::chrono::seconds max_ocsp_age = std::chrono::seconds::zero()) :
         m_require_revocation_information(require_rev),
         m_ocsp_all_intermediates(ocsp_all_intermediates),
         m_trusted_hashes(trusted_hashes),
         m_minimum_key_strength(minimum_key_strength),
         m_max_ocsp_age(max_ocsp_age) {}

      /**
      * @return whether revocation information is required
      */
      bool require_revocation_information() const
         { return m_require_revocation_information; }

      /**
      * @return whether all intermediate CAs should also be OCSPed. If false
      * then only end entity OCSP is required/requested.
      */
      bool ocsp_all_intermediates() const
         { return m_ocsp_all_intermediates; }

      /**
      * @return trusted signature hash functions
      */
      const std::set<std::string>& trusted_hashes() const
         { return m_trusted_hashes; }

      /**
      * @return minimum required key strength
      */
      size_t minimum_key_strength() const
         { return m_minimum_key_strength; }

      /**
      * @return maximum age of OCSP responses w/o next_update.
      * If zero, there is no maximum age
      */
      std::chrono::seconds max_ocsp_age() const
         { return m_max_ocsp_age; }

   private:
      bool m_require_revocation_information;
      bool m_ocsp_all_intermediates;
      std::set<std::string> m_trusted_hashes;
      size_t m_minimum_key_strength;
      std::chrono::seconds m_max_ocsp_age;
   };

/**
* Represents the result of a PKIX path validation
*/
class BOTAN_PUBLIC_API(2,0) Path_Validation_Result final
   {
   public:
      typedef Certificate_Status_Code Code;

      /**
      * @return the set of hash functions you are implicitly
      * trusting by trusting this result.
      */
      std::set<std::string> trusted_hashes() const;

      /**
      * @return the trust root of the validation if successful
      * throws an exception if the validation failed
      */
      const X509_Certificate& trust_root() const;

      /**
      * @return the full path from subject to trust root
      * This path may be empty
      */
      const std::vector<std::shared_ptr<const X509_Certificate>>& cert_path() const { return m_cert_path; }

      /**
      * @return true iff the validation was successful
      */
      bool successful_validation() const;

      /**
      * @return true iff no warnings occured during validation
      */
      bool no_warnings() const;

      /**
      * @return overall validation result code
      */
      Certificate_Status_Code result() const { return m_overall; }

      /**
      * @return a set of status codes for each certificate in the chain
      */
      const CertificatePathStatusCodes& all_statuses() const
         { return m_all_status; }

      /**
      * @return the subset of status codes that are warnings
      */
      CertificatePathStatusCodes warnings() const;

      /**
      * @return string representation of the validation result
      */
      std::string result_string() const;

      /**
      * @return string representation of the warnings
      */
      std::string warnings_string() const;

      /**
      * @param code validation status code
      * @return corresponding validation status message
      */
      static const char* status_string(Certificate_Status_Code code);

      /**
      * Create a Path_Validation_Result
      * @param status list of validation status codes
      * @param cert_chain the certificate chain that was validated
      */
      Path_Validation_Result(CertificatePathStatusCodes status,
                             std::vector<std::shared_ptr<const X509_Certificate>>&& cert_chain);

      /**
      * Create a Path_Validation_Result
      * @param status validation status code
      */
      explicit Path_Validation_Result(Certificate_Status_Code status) : m_overall(status) {}

   private:
      CertificatePathStatusCodes m_all_status;
      CertificatePathStatusCodes m_warnings;
      std::vector<std::shared_ptr<const X509_Certificate>> m_cert_path;
      Certificate_Status_Code m_overall;
   };

/**
* PKIX Path Validation
* @param end_certs certificate chain to validate (with end entity certificate in end_certs[0])
* @param restrictions path validation restrictions
* @param trusted_roots list of certificate stores that contain trusted certificates
* @param hostname if not empty, compared against the DNS name in end_certs[0]
* @param usage if not set to UNSPECIFIED, compared against the key usage in end_certs[0]
* @param validation_time what reference time to use for validation
* @param ocsp_timeout timeout for OCSP operations, 0 disables OCSP check
* @param ocsp_resp additional OCSP responses to consider (eg from peer)
* @return result of the path validation
*   note: when enabled, OCSP check is softfail by default: if the OCSP server is not
*   reachable, Path_Validation_Result::successful_validation() will return true.
*   Hardfail OCSP check can be achieve by also calling Path_Validation_Result::no_warnings().
*/
Path_Validation_Result BOTAN_PUBLIC_API(2,0) x509_path_validate(
   const std::vector<X509_Certificate>& end_certs,
   const Path_Validation_Restrictions& restrictions,
   const std::vector<Certificate_Store*>& trusted_roots,
   const std::string& hostname = "",
   Usage_Type usage = Usage_Type::UNSPECIFIED,
   std::chrono::system_clock::time_point validation_time = std::chrono::system_clock::now(),
   std::chrono::milliseconds ocsp_timeout = std::chrono::milliseconds(0),
   const std::vector<std::shared_ptr<const OCSP::Response>>& ocsp_resp = {});

/**
* PKIX Path Validation
* @param end_cert certificate to validate
* @param restrictions path validation restrictions
* @param trusted_roots list of stores that contain trusted certificates
* @param hostname if not empty, compared against the DNS name in end_cert
* @param usage if not set to UNSPECIFIED, compared against the key usage in end_cert
* @param validation_time what reference time to use for validation
* @param ocsp_timeout timeout for OCSP operations, 0 disables OCSP check
* @param ocsp_resp additional OCSP responses to consider (eg from peer)
* @return result of the path validation
*/
Path_Validation_Result BOTAN_PUBLIC_API(2,0) x509_path_validate(
   const X509_Certificate& end_cert,
   const Path_Validation_Restrictions& restrictions,
   const std::vector<Certificate_Store*>& trusted_roots,
   const std::string& hostname = "",
   Usage_Type usage = Usage_Type::UNSPECIFIED,
   std::chrono::system_clock::time_point validation_time = std::chrono::system_clock::now(),
   std::chrono::milliseconds ocsp_timeout = std::chrono::milliseconds(0),
   const std::vector<std::shared_ptr<const OCSP::Response>>& ocsp_resp = {});

/**
* PKIX Path Validation
* @param end_cert certificate to validate
* @param restrictions path validation restrictions
* @param store store that contains trusted certificates
* @param hostname if not empty, compared against the DNS name in end_cert
* @param usage if not set to UNSPECIFIED, compared against the key usage in end_cert
* @param validation_time what reference time to use for validation
* @param ocsp_timeout timeout for OCSP operations, 0 disables OCSP check
* @param ocsp_resp additional OCSP responses to consider (eg from peer)
* @return result of the path validation
*/
Path_Validation_Result BOTAN_PUBLIC_API(2,0) x509_path_validate(
   const X509_Certificate& end_cert,
   const Path_Validation_Restrictions& restrictions,
   const Certificate_Store& store,
   const std::string& hostname = "",
   Usage_Type usage = Usage_Type::UNSPECIFIED,
   std::chrono::system_clock::time_point validation_time = std::chrono::system_clock::now(),
   std::chrono::milliseconds ocsp_timeout = std::chrono::milliseconds(0),
   const std::vector<std::shared_ptr<const OCSP::Response>>& ocsp_resp = {});

/**
* PKIX Path Validation
* @param end_certs certificate chain to validate
* @param restrictions path validation restrictions
* @param store store that contains trusted certificates
* @param hostname if not empty, compared against the DNS name in end_certs[0]
* @param usage if not set to UNSPECIFIED, compared against the key usage in end_certs[0]
* @param validation_time what reference time to use for validation
* @param ocsp_timeout timeout for OCSP operations, 0 disables OCSP check
* @param ocsp_resp additional OCSP responses to consider (eg from peer)
* @return result of the path validation
*/
Path_Validation_Result BOTAN_PUBLIC_API(2,0) x509_path_validate(
   const std::vector<X509_Certificate>& end_certs,
   const Path_Validation_Restrictions& restrictions,
   const Certificate_Store& store,
   const std::string& hostname = "",
   Usage_Type usage = Usage_Type::UNSPECIFIED,
   std::chrono::system_clock::time_point validation_time = std::chrono::system_clock::now(),
   std::chrono::milliseconds ocsp_timeout = std::chrono::milliseconds(0),
   const std::vector<std::shared_ptr<const OCSP::Response>>& ocsp_resp = {});


/**
* namespace PKIX holds the building blocks that are called by x509_path_validate.
* This allows custom validation logic to be written by applications and makes
* for easier testing, but unless you're positive you know what you're doing you
* probably want to just call x509_path_validate instead.
*/
namespace PKIX {

Certificate_Status_Code
build_all_certificate_paths(std::vector<std::vector<std::shared_ptr<const X509_Certificate>>>& cert_paths,
                            const std::vector<Certificate_Store*>& trusted_certstores,
                            const std::shared_ptr<const X509_Certificate>& end_entity,
                            const std::vector<std::shared_ptr<const X509_Certificate>>& end_entity_extra);


/**
* Build certificate path
* @param cert_path_out output parameter, cert_path will be appended to this vector
* @param trusted_certstores list of certificate stores that contain trusted certificates
* @param end_entity the cert to be validated
* @param end_entity_extra optional list of additional untrusted certs for path building
* @return result of the path building operation (OK or error)
*/
Certificate_Status_Code
BOTAN_PUBLIC_API(2,0) build_certificate_path(std::vector<std::shared_ptr<const X509_Certificate>>& cert_path_out,
                                 const std::vector<Certificate_Store*>& trusted_certstores,
                                 const std::shared_ptr<const X509_Certificate>& end_entity,
                                 const std::vector<std::shared_ptr<const X509_Certificate>>& end_entity_extra);

/**
* Check the certificate chain, but not any revocation data
*
* @param cert_path path built by build_certificate_path with OK result
* @param ref_time whatever time you want to perform the validation
* against (normally current system clock)
* @param hostname the hostname
* @param usage end entity usage checks
* @param min_signature_algo_strength 80 or 110 typically
* Note 80 allows 1024 bit RSA and SHA-1. 110 allows 2048 bit RSA and SHA-2.
* Using 128 requires ECC (P-256) or ~3000 bit RSA keys.
* @param trusted_hashes set of trusted hash functions, empty means accept any
* hash we have an OID for
* @return vector of results on per certificate in the path, each containing a set of
* results. If all codes in the set are < Certificate_Status_Code::FIRST_ERROR_STATUS,
* then the result for that certificate is successful. If all results are
*/
CertificatePathStatusCodes
BOTAN_PUBLIC_API(2,0) check_chain(const std::vector<std::shared_ptr<const X509_Certificate>>& cert_path,
                      std::chrono::system_clock::time_point ref_time,
                      const std::string& hostname,
                      Usage_Type usage,
                      size_t min_signature_algo_strength,
                      const std::set<std::string>& trusted_hashes);

/**
* Check OCSP responses for revocation information
* @param cert_path path already validated by check_chain
* @param ocsp_responses the OCSP responses to consider
* @param certstores trusted roots
* @param ref_time whatever time you want to perform the validation against
* (normally current system clock)
* @param max_ocsp_age maximum age of OCSP responses w/o next_update. If zero,
* there is no maximum age
* @return revocation status
*/
CertificatePathStatusCodes
BOTAN_PUBLIC_API(2, 0) check_ocsp(const std::vector<std::shared_ptr<const X509_Certificate>>& cert_path,
                                  const std::vector<std::shared_ptr<const OCSP::Response>>& ocsp_responses,
                                  const std::vector<Certificate_Store*>& certstores,
                                  std::chrono::system_clock::time_point ref_time,
                                  std::chrono::seconds max_ocsp_age = std::chrono::seconds::zero());

/**
* Check CRLs for revocation information
* @param cert_path path already validated by check_chain
* @param crls the list of CRLs to check, it is assumed that crls[i] (if not null)
* is the associated CRL for the subject in cert_path[i].
* @param ref_time whatever time you want to perform the validation against
* (normally current system clock)
* @return revocation status
*/
CertificatePathStatusCodes
BOTAN_PUBLIC_API(2,0) check_crl(const std::vector<std::shared_ptr<const X509_Certificate>>& cert_path,
                    const std::vector<std::shared_ptr<const X509_CRL>>& crls,
                    std::chrono::system_clock::time_point ref_time);

/**
* Check CRLs for revocation information
* @param cert_path path already validated by check_chain
* @param certstores a list of certificate stores to query for the CRL
* @param ref_time whatever time you want to perform the validation against
* (normally current system clock)
* @return revocation status
*/
CertificatePathStatusCodes
BOTAN_PUBLIC_API(2,0) check_crl(const std::vector<std::shared_ptr<const X509_Certificate>>& cert_path,
                    const std::vector<Certificate_Store*>& certstores,
                    std::chrono::system_clock::time_point ref_time);

#if defined(BOTAN_HAS_ONLINE_REVOCATION_CHECKS)

/**
* Check OCSP using online (HTTP) access. Current version creates a thread and
* network connection per OCSP request made.
*
* @param cert_path path already validated by check_chain
* @param trusted_certstores a list of certstores with trusted certs
* @param ref_time whatever time you want to perform the validation against
* (normally current system clock)
* @param timeout for timing out the responses, though actually this function
* may block for up to timeout*cert_path.size()*C for some small C.
* @param ocsp_check_intermediate_CAs if true also performs OCSP on any intermediate
* CA certificates. If false, only does OCSP on the end entity cert.
* @param max_ocsp_age maximum age of OCSP responses w/o next_update. If zero,
* there is no maximum age
* @return revocation status
*/
CertificatePathStatusCodes
BOTAN_PUBLIC_API(2, 0) check_ocsp_online(const std::vector<std::shared_ptr<const X509_Certificate>>& cert_path,
      const std::vector<Certificate_Store*>& trusted_certstores,
      std::chrono::system_clock::time_point ref_time,
      std::chrono::milliseconds timeout,
      bool ocsp_check_intermediate_CAs,
      std::chrono::seconds max_ocsp_age = std::chrono::seconds::zero());

/**
* Check CRL using online (HTTP) access. Current version creates a thread and
* network connection per CRL access.

* @param cert_path path already validated by check_chain
* @param trusted_certstores a list of certstores with trusted certs
* @param certstore_to_recv_crls optional (nullptr to disable), all CRLs
* retreived will be saved to this cert store.
* @param ref_time whatever time you want to perform the validation against
* (normally current system clock)
* @param timeout for timing out the responses, though actually this function
* may block for up to timeout*cert_path.size()*C for some small C.
* @return revocation status
*/
CertificatePathStatusCodes
BOTAN_PUBLIC_API(2,0) check_crl_online(const std::vector<std::shared_ptr<const X509_Certificate>>& cert_path,
                           const std::vector<Certificate_Store*>& trusted_certstores,
                           Certificate_Store_In_Memory* certstore_to_recv_crls,
                           std::chrono::system_clock::time_point ref_time,
                           std::chrono::milliseconds timeout);

#endif

/**
* Find overall status (OK, error) of a validation
* @param cert_status result of merge_revocation_status or check_chain
*/
Certificate_Status_Code BOTAN_PUBLIC_API(2,0) overall_status(const CertificatePathStatusCodes& cert_status);

/**
* Merge the results from CRL and/or OCSP checks into chain_status
* @param chain_status the certificate status
* @param crl_status results from check_crl
* @param ocsp_status results from check_ocsp
* @param require_rev_on_end_entity require valid CRL or OCSP on end-entity cert
* @param require_rev_on_intermediates require valid CRL or OCSP on all intermediate certificates
*/
void BOTAN_PUBLIC_API(2,0) merge_revocation_status(CertificatePathStatusCodes& chain_status,
                                       const CertificatePathStatusCodes& crl_status,
                                       const CertificatePathStatusCodes& ocsp_status,
                                       bool require_rev_on_end_entity,
                                       bool require_rev_on_intermediates);

}

}

namespace Botan {

class RandomNumberGenerator;
class Private_Key;

/**
* Options for X.509 certificates.
*/
class BOTAN_PUBLIC_API(2,0) X509_Cert_Options final
   {
   public:
      /**
      * the subject common name
      */
      std::string common_name;

      /**
      * the subject counry
      */
      std::string country;

      /**
      * the subject organization
      */
      std::string organization;

      /**
      * the subject organizational unit
      */
      std::string org_unit;

      /**
       * additional subject organizational units.
       */
      std::vector<std::string> more_org_units;

      /**
      * the subject locality
      */
      std::string locality;

      /**
      * the subject state
      */
      std::string state;

      /**
      * the subject serial number
      */
      std::string serial_number;

      /**
      * the subject email adress
      */
      std::string email;

      /**
      * the subject URI
      */
      std::string uri;

      /**
      * the subject IPv4 address
      */
      std::string ip;

      /**
      * the subject DNS
      */
      std::string dns;

      /**
       * additional subject DNS entries.
       */
      std::vector<std::string> more_dns;

      /**
      * the subject XMPP
      */
      std::string xmpp;

      /**
      * the subject challenge password
      */
      std::string challenge;

      /**
      * the subject notBefore
      */
      X509_Time start;
      /**
      * the subject notAfter
      */
      X509_Time end;

      /**
      * Indicates whether the certificate request
      */
      bool is_CA;

      /**
      * Indicates the BasicConstraints path limit
      */
      size_t path_limit;

      std::string padding_scheme;

      /**
      * The key constraints for the subject public key
      */
      Key_Constraints constraints;

      /**
      * The key extended constraints for the subject public key
      */
      std::vector<OID> ex_constraints;

      /**
      * Additional X.509 extensions
      */
      Extensions extensions;

      /**
      * Mark the certificate as a CA certificate and set the path limit.
      * @param limit the path limit to be set in the BasicConstraints extension.
      */
      void CA_key(size_t limit = 1);

      /**
      * Choose a padding scheme different from the default for the key used.
      */
      void set_padding_scheme(const std::string& scheme);

      /**
      * Set the notBefore of the certificate.
      * @param time the notBefore value of the certificate
      */
      void not_before(const std::string& time);

      /**
      * Set the notAfter of the certificate.
      * @param time the notAfter value of the certificate
      */
      void not_after(const std::string& time);

      /**
      * Add the key constraints of the KeyUsage extension.
      * @param constr the constraints to set
      */
      void add_constraints(Key_Constraints constr);

      /**
      * Add constraints to the ExtendedKeyUsage extension.
      * @param oid the oid to add
      */
      void add_ex_constraint(const OID& oid);

      /**
      * Add constraints to the ExtendedKeyUsage extension.
      * @param name the name to look up the oid to add
      */
      void add_ex_constraint(const std::string& name);

      /**
      * Construct a new options object
      * @param opts define the common name of this object. An example for this
      * parameter would be "common_name/country/organization/organizational_unit".
      * @param expire_time the expiration time (from the current clock in seconds)
      */
      X509_Cert_Options(const std::string& opts = "",
                        uint32_t expire_time = 365 * 24 * 60 * 60);
   };

namespace X509 {

/**
* Create a self-signed X.509 certificate.
* @param opts the options defining the certificate to create
* @param key the private key used for signing, i.e. the key
* associated with this self-signed certificate
* @param hash_fn the hash function to use
* @param rng the rng to use
* @return newly created self-signed certificate
*/
BOTAN_PUBLIC_API(2,0) X509_Certificate
create_self_signed_cert(const X509_Cert_Options& opts,
                        const Private_Key& key,
                        const std::string& hash_fn,
                        RandomNumberGenerator& rng);

/**
* Create a PKCS#10 certificate request.
* @param opts the options defining the request to create
* @param key the key used to sign this request
* @param rng the rng to use
* @param hash_fn the hash function to use
* @return newly created PKCS#10 request
*/
BOTAN_PUBLIC_API(2,0) PKCS10_Request create_cert_req(const X509_Cert_Options& opts,
                                         const Private_Key& key,
                                         const std::string& hash_fn,
                                         RandomNumberGenerator& rng);

}

}

#endif // BOTAN_AMALGAMATION_H_
