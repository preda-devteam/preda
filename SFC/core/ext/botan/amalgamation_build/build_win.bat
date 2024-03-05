@echo off
set MODULES=auto_rng,system_rng,rsa,sha1_sse2,sha1,md5,sha2_32,sha2_64,sha3,sm2,sm3,sm4,emsa1,emsa_pkcs1,emsa_pssr,emsa_raw,dh,ecdh,rmd160,ecdsa,emsa_x931,crc32,cbc,des,blowfish,curve25519,ed25519,dsa,win32_stats,aes,aes_ni,tls


python configure.py --amalgamation --disable-shared --cc=msvc --no-autoload --enable-modules=%MODULES% --cpu=x86_32 --os=windows --with-local-config=config_w32.h
move /Y botan_all*.h ..\platforms\win_x86\
move /Y botan_all*.cpp ..\platforms\win_x86\

python configure.py --amalgamation --disable-shared --cc=msvc --no-autoload --enable-modules=%MODULES% --cpu=x86_64 --os=windows --with-local-config=config_w32.h
move /Y botan_all*.h ..\platforms\win_x64\
move /Y botan_all*.cpp ..\platforms\win_x64\
