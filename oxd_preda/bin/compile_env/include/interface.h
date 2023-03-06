#pragma once
#include "relay.h"
#include "inttypes.h"

namespace prlrt {

	template<typename retType, typename ...Args>
	retType interface_call(uint64_t contractId, const char *interfaceName, uint32_t funcIdx, Args&& ...args)
	{
		retType ret;
		const void *p[sizeof...(Args) + 1] = { &args..., &ret };
		uint32_t crossCallRes = PREDA_CALL(InterfaceCall, contractId, interfaceName, funcIdx, p, sizeof...(Args) + 1);
		if (crossCallRes != 0)
			throw preda_exception("interface call error", prlrt::ExceptionType(crossCallRes >> 8));
		return ret;
	}

	template<typename ...Args>
	void interface_call_no_ret(uint64_t contractId, const char* interfaceName, uint32_t funcIdx, Args&& ...args)
	{
		const void *p[sizeof...(Args) + 1] = { &args..., nullptr };		// here "+ 1" is necessary, otherwise when args... is empty, we are defining an empty array and get a compile error
		uint32_t crossCallRes = PREDA_CALL(InterfaceCall, contractId, interfaceName, funcIdx, p, sizeof...(Args));
		if (crossCallRes != 0)
			throw preda_exception("interface call error", prlrt::ExceptionType(crossCallRes >> 8));
	}

	struct interface_struct {
		uint64_t contract_id = 0;
		interface_struct()
		{
		}
		interface_struct(__prlt_uint64 in_id)
		{
			contract_id = in_id._v;
		}
	};

#define INTERFACE_INHERIT \
using interface_struct::interface_struct;
}
