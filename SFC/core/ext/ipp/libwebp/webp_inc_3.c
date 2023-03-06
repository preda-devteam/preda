#ifdef PLATFORM_INTEL_IPP_WEBP_CODEC
#include "./webp_config.h"

//enc
#include "src/enc/webp_enc.c"
//dsp
#include "src/dsp/enc.c"
//dec
#include "src/dec/alpha_dec.c"
#include "src/dec/buffer_dec.c"
#include "src/dec/frame_dec.c"
#include "src/dec/idec_dec.c"
#include "src/dec/io_dec.c"
#include "src/dec/quant_dec.c"
#include "src/dec/tree_dec.c"
#include "src/dec/vp8l_dec.c"
#include "src/dec/webp_dec.c"
#endif // PLATFORM_INTEL_IPP_WEBP_CODEC
