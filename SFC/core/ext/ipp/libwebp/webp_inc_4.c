#ifdef PLATFORM_INTEL_IPP_WEBP_CODEC
#include "./webp_config.h"

//enc
#include "src/enc/alpha_enc.c"
#include "src/enc/analysis_enc.c"
#include "src/enc/backward_references_cost_enc.c"
#include "src/enc/backward_references_enc.c"
#include "src/enc/config_enc.c"
#include "src/enc/cost_enc.c"
#include "src/enc/filter_enc.c"
#include "src/enc/frame_enc.c"
#include "src/enc/iterator_enc.c"
#include "src/enc/near_lossless_enc.c"
#include "src/enc/picture_csp_enc.c"
#include "src/enc/picture_enc.c"
#include "src/enc/picture_rescale_enc.c"
#include "src/enc/picture_tools_enc.c"
#include "src/enc/syntax_enc.c"
#include "src/enc/token_enc.c"
#include "src/enc/tree_enc.c"
#include "src/enc/vp8l_enc.c"
//utils
#include "src/utils/bit_reader_utils.c"
#include "src/utils/bit_writer_utils.c"
#include "src/utils/color_cache_utils.c"
#include "src/utils/filters_utils.c"
#include "src/utils/huffman_encode_utils.c"
#include "src/utils/huffman_utils.c"
#include "src/utils/quant_levels_utils.c"
#include "src/utils/random_utils.c"
#include "src/utils/rescaler_utils.c"
#include "src/utils/thread_utils.c"
#include "src/utils/utils.c"
//dsp
#include "src/dsp/lossless_enc.c"
//utils
#include "src/dec/vp8_dec.c"
#endif // PLATFORM_INTEL_IPP_WEBP_CODEC