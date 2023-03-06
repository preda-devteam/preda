#pragma once
#include "../../../SFC/core/ext/bignum/precision_num.h"
#ifdef _WIN32
	#pragma warning(push)
	#pragma warning(disable:4244)
#endif
#include "../../../SFC/core/ext/bignum/ttmath/ttmath.h"
#ifdef _WIN32
	#pragma warning(pop)
#endif

namespace rvm
{

using Float2048 = ext::Float2048;
using Float1024 = ext::Float1024;
using Float512 = ext::Float512;
using Float256 = ext::Float256;

} // namespace rvm
