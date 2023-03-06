#ifdef _MSC_VER
#pragma warning(disable:4996) // warning C4996: 'xxxx': was declared deprecated
#else
#define _7ZIP_ST
#endif

#include "7zAlloc.c"
#include "7zBuf.c"
#include "7zBuf2.c"
#include "7zCrc.c"
#include "7zCrcOpt.c"
#include "7zDec.c"
#include "7zFile.c"
#include "7zIn.c"
#include "7zStream.c"
#include "Alloc.c"
#include "Bcj2.c"
#include "Bra.c"
#include "Bra86.c"
#include "BraIA64.c"
#include "CpuArch.c"
#include "Delta.c"
#include "LzFind.c"
#include "Lzma2Dec.c"
#include "Lzma2Enc.c"
#include "Lzma86Dec.c"
#include "Lzma86Enc.c"
#include "LzmaDec.c"
#include "LzmaEnc.c"
#include "LzmaLib.c"
#include "Ppmd7.c"
#include "Ppmd7Dec.c"
#include "Ppmd7Enc.c"
#include "Sha256.c"
#include "Xz.c"
#include "XzCrc64.c"
#include "XzDec.c"
#include "XzEnc.c"
#include "XzIn.c"

#ifndef _7ZIP_ST
#include "LzFindMt.c"
#include "MtCoder.c"
#include "Threads.c"
#endif
