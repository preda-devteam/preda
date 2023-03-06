#define NO_DUMMY_DECL

#include "zutil.c"
#undef ZLIB_INTERNAL

#include "uncompr.c"
#include "trees.c"
#include "inftrees.c"
#include "inflate.c"
#include "deflate.c"
#include "compress.c"
#include "crc32.c"
#include "inffast.c"

#undef DO1
#undef DO8

#include "adler32.c"
