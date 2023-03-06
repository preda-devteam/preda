@echo off
set MODULES=auto_rng,system_rng,rsa,sha1_sse2,sha1,md5,sha2_32,sha2_64,sha3,sm2,sm3,sm4,emsa1,emsa_pkcs1,emsa_pssr,emsa_raw,dh,ecdh,emsa_x931,crc32,cbc,des,blowfish,curve25519,dsa,win32_stats,aes,aes_ni,tls


configure.py --amalgamation --disable-shared --cc=gcc --no-autoload --enable-modules=%MODULES% --cpu=x86_32 --os=linux --with-local-config=config_linux.h
move /Y botan_all*.h ..\platforms\linux_x86\
move /Y botan_all*.cpp ..\platforms\linux_x86\

configure.py --amalgamation --disable-shared --cc=gcc --no-autoload --enable-modules=%MODULES% --cpu=x86_64 --os=linux --with-local-config=config_linux.h
move /Y botan_all*.h ..\platforms\linux_x64\
move /Y botan_all*.cpp ..\platforms\linux_x64\
