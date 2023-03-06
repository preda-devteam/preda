#ifdef PLATFORM_INTEL_IPP_WEBP_CODEC
#include "./webp_config.h"

#include "src/dsp/ssim_sse2.c"
#include "src/dsp/filters_sse2.c"
#include "src/dsp/yuv_sse2.c"
#include "src/dsp/lossless_sse2.c"
#include "src/dsp/enc_sse2.c"
#endif // PLATFORM_INTEL_IPP_WEBP_CODEC