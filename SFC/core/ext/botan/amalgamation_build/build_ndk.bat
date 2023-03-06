@echo off
set MODULES=auto_rng,rsa,sha1_sse2,sha1,md5,sha2_32,sha2_64,sha3,emsa1,emsa_pkcs1,emsa_pssr,emsa_raw,dh,ecdh,emsa_x931,cryptoapi_rng,crc32,cbc,des,blowfish,curve25519,dsa,win32_stats,aes,aes_ni,aes_ssse3,tls


configure.py --amalgamation --disable-shared --cc=msvc --no-autoload --enable-modules=%MODULES% --cpu=x86_32 --os=windows --with-local-config=config_w32.h
move /Y botan_all*.h ..\platforms\win_x86\
move /Y botan_all*.cpp ..\platforms\win_x86\

configure.py --amalgamation --disable-shared --cc=msvc --no-autoload --enable-modules=%MODULES% --cpu=x86_64 --os=windows --with-local-config=config_w32.h
move /Y botan_all*.h ..\platforms\win_x64\
move /Y botan_all*.cpp ..\platforms\win_x64\

pause
exit

set MODULES=auto_rng,rsa,emsa4,sha1,eme1,md5,pthreads,dev_random,crc32,cbc,rc5,des,blowfish,ssl

configure.py --amalgamation --disable-shared --cc=gcc --no-autoload --enable-modules=%MODULES% --cpu=arm --os=linux --with-local-config=config_ndk.h
post_build_ndk_arm.py
copy botan_all.h ..\..\shared_library\botan\platforms\botan_ndk_arm.h /Y
copy botan_all.cpp ..\..\shared_library\botan\platforms\botan_ndk_arm.cpp /Y

configure.py --amalgamation --disable-shared --cc=gcc --no-autoload --enable-modules=%MODULES% --cpu=x86_32 --os=linux --with-local-config=config_ndk.h
copy botan_all.h ..\..\shared_library\botan\platforms\botan_ndk_x86.h /Y
copy botan_all.cpp ..\..\shared_library\botan\platforms\botan_ndk_x86.cpp /Y

del  botan_all.h
del  botan_all.cpp
pause

@echo off
rem --no-autoload --enable-modules=rsa,auto_rng,randpool,seed 

rem auto_rng needs cryptoapi_rng to provide entroy source
rem rsa needs rsa,emsa4,sha1 for generating PK
rem rsa needs rsa,eme1,sha1 for "EME1(SHA-1)"
rem ecc needs ec_group, ecc_key 

rem adler32 aes_isa_eng aont arc4 asm_engine auto_rng bcrypt benchmark blowfish bmw_512
rem camellia cascade cast cbc cbc_mac certstore cfb cmac comb4p crc24 crc32 cryptoapi_rng
rem cryptobox ctr cts datastor des dh dl_algo dl_group dlies dsa dyn_engine dyn_load eax
rem ec_gfp ec_group ecb ecc_key ecdh ecdsa elgamal eme1 eme_pkcs emsa1 emsa1_bsi emsa2 emsa3
rem emsa4 emsa_raw fpe_fe1 gost_28147 gost_3410 gost_3411 has160 hash_id hres_timer
rem idea if_algo kasumi kdf1 kdf2 keccak keypair lion lubyrack mars md2 md4 md5 mgf1 
rem misty1 mp_generic noekeon noekeon_simd nr ofb openpgp par_hash passhash9 pbes1
rem pbes2 pbkdf1 pbkdf2 pgps2k pk_filts pkcs10 prf_ssl3 prf_tls prf_x942 randpool rc2
rem rc5 rc6 rfc3394 rmd128 rmd160 rsa rw safer salsa20 seed selftest serpent serp
rem ent_simd sha1 simd simd_engine simd_scalar skein skipjack square srp6 ssl3mac tea
rem tiger tss turing twofish whirlpool wid_wake win32_crit_section win32_stats x50
rem 9ca x509cert x509crl x509self x509store x919_mac x931_rng xtea xtea_simd xts