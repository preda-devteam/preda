#include "ipp_core.h"

#define IppEnvStackSize	32

namespace ipp
{
	IppiEnvParam	IppiEnvParam::g_IppEnv;
	BYTE			g_IppEnvParamStack[IppEnvStackSize*sizeof(IppiEnvParamItems)];
} // namespace ipp


ipp::IppiEnvParam::IppiEnvParam()
{
	RoundMode = ippRndNear;
	InterpolationMode = IPPI_INTER_LINEAR;

#ifdef PLATFORM_INTEL_IPP_SUPPORT
	DitherMode = ippDitherNone;
#endif

	HintAlgorithm = ippAlgHintAccurate;

	FloatMin = 0.0f;
	FloatMax = 1.0f;

	ResultBitShift = 0;
	IntegerScaleFactor = 1;

	m_StackPointer = 0;
	JpegEncodeQuality = 95;
	WebpEncodeQuality = 95;
	GifEncodeColorCount = 256;

	BorderType = ippBorderRepl;
}

void ipp::IppiEnvParam::Push()
{
	ASSERT( m_StackPointer < IppEnvStackSize );
	memcpy(&g_IppEnvParamStack[m_StackPointer*EnvParamSize],this,EnvParamSize);
	m_StackPointer++;
}

void ipp::IppiEnvParam::Pop()
{
	ASSERT( m_StackPointer > 0 );
	m_StackPointer--;
	memcpy(this,&g_IppEnvParamStack[m_StackPointer*EnvParamSize],EnvParamSize);	
}
#undef EnvParamSize
