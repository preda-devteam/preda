#include <cstdint>

#include "include/inttypes.h"
#include "include/floattypes.h"
#include "include/arraytype.h"
#include "include/maptype.h"
#include "include/tokentype.h"
#include "include/stringtype.h"
#include "include/structtype.h"
#include "include/address_blob_hash_types.h"
#include "include/biginttype.h"
#include "include/enumtype.h"
#include "include/relay.h"
#include "include/interface.h"
#include "include/contexts.h"
#include "include/gascost.h"

#if defined(__linux__) || defined(__linux) || defined(__APPLE__)
	#define API_EXPORT __attribute__((visibility("default")))
#elif defined(_WIN32)
	#define API_EXPORT __declspec(dllexport)
#elif defined(__wasm32__)
#include <emscripten.h>
	#define API_EXPORT EMSCRIPTEN_KEEPALIVE
extern "C" {
}
#else
	#error "Unknown platform"
#endif

thread_local prlrt::IRuntimeInterface* prlrt::g_executionEngineInterface = nullptr;
thread_local bool prlrt::g_inRelaySerialization = false;
