#pragma once
#include "relay.h"
#include "inttypes.h"
#include "contexts.h"

namespace prlrt {

	template<typename retType, typename ...Args>
	retType interface_call(uint64_t contractId, int64_t interfaceContractImportSlot, uint32_t interfaceSlot, uint32_t funcIdx, Args&& ...args)
	{
		retType ret;
		const void *p[sizeof...(Args) + 1] = { &args..., &ret };
		uint32_t crossCallRes = PREDA_CALL(InterfaceCall, contractId, interfaceContractImportSlot, interfaceSlot, funcIdx, p, sizeof...(Args) + 1);
		if (crossCallRes != 0)
			preda_exception::throw_exception("interface call error", prlrt::ExceptionType(crossCallRes >> 8));
		return ret;
	}

	template<typename ...Args>
	void interface_call_no_ret(uint64_t contractId, int64_t interfaceContractImportSlot, uint32_t interfaceSlot, uint32_t funcIdx, Args&& ...args)
	{
		const void *p[sizeof...(Args) + 1] = { &args..., nullptr };		// here "+ 1" is necessary, otherwise when args... is empty, we are defining an empty array and get a compile error
		uint32_t crossCallRes = PREDA_CALL(InterfaceCall, contractId, interfaceContractImportSlot, interfaceSlot, funcIdx, p, sizeof...(Args));
		if (crossCallRes != 0)
			preda_exception::throw_exception("interface call error", prlrt::ExceptionType(crossCallRes >> 8));
	}

	bool interface_is_implemented(uint64_t contractId, int64_t interfaceContractImportSlot, uint32_t interfaceSlot)
	{
		if (contractId == 0)
			return false;
		return PREDA_CALL(InterfaceIsImplemented, contractId, interfaceContractImportSlot, interfaceSlot);
	}

	struct interface_struct {
		using internal_type = uint64_t;
		internal_type contract_id = 0;
		interface_struct()
		{
		}
		interface_struct(__prlt_uint64 in_id)
		{
			contract_id = in_id._v;
		}

		__prlt_uint64 __prli___id()
		{
			return contract_id;
		}

		constexpr serialize_size_type get_serialize_size() const
		{
			return sizeof(internal_type);
		}
		void serialize_out(uint8_t* buffer, bool for_debug) const
		{
			*(internal_type*)buffer = contract_id;
		}
		bool map_from_serialized_data(uint8_t*& buffer, serialize_size_type& bufferSize, bool bDeep)
		{
			if (bufferSize < serialize_size_type(sizeof(internal_type)))
				return false;
			contract_id = *(internal_type*)buffer;
			buffer += serialize_size_type(sizeof(internal_type));
			bufferSize -= serialize_size_type(sizeof(internal_type));
			return true;
		}
		void operator=(const interface_struct& rhs)
		{
			contract_id = rhs.contract_id;
		}
	};
}
