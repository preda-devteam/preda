#if defined PLATFORM_ANDROID
#define S_IREAD S_IRUSR
#define S_IWRITE S_IWUSR
#define S_IEXEC S_IXUSR
#endif

#include "dgif_lib.c"
#include "egif_lib.c"
#include "gifalloc.c"
#include "gif_err.c"
#include "gif_font.c"
#include "gif_hash.c"
#include "openbsd-reallocarray.c"
#include "quantize.c"

