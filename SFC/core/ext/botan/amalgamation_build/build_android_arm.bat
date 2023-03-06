@echo off
set MODULES=auto_rng,rsa,sha1_sse2,sha1,md5,sha2_32,sha2_64,sha3,emsa1,emsa_pkcs1,emsa_pssr,emsa_raw,dh,ecdh,emsa_x931,cryptoapi_rng,crc32,cbc,des,blowfish,curve25519,dsa,win32_stats,aes,aes_ni,aes_ssse3,tls
mkdir ..\platforms\android_arm\
python configure.py --amalgamation --disable-shared --no-autoload --enable-modules=%MODULES% --cpu=arm --os=android --with-local-config=config_ndk.h --link-method=copy
python post_build_ndk_arm.py
move /Y botan_all*.h ..\platforms\android_arm\
move /Y botan_all*.cpp ..\platforms\android_arm\

pause
exit

