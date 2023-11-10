#pragma once
#include <vector>
#include "common.h"
#include "address_blob_hash_types.h"

namespace prlrt {

	void relay_serialize_args(std::vector<uint8_t> &outBuffer)
	{
		return;
	}

	template<typename TFirstArg, typename ...Args>
	void relay_serialize_args(std::vector<uint8_t> &outBuffer, TFirstArg &&first_arg, Args &&...args)
	{
		serialize_size_type s = first_arg.get_serialize_size();
		outBuffer.resize(outBuffer.size() + s);
		first_arg.serialize_out(&outBuffer[outBuffer.size() - s], false);

		relay_serialize_args(outBuffer, args...);
	}

	//template<typename ...Args>
	//void relay(const __prlt_address &addr, uint32_t opCode, Args&& ...args)
	//{
	//	std::vector<uint8_t> args_serialized;
	//	g_inRelaySerialization = true;
	//	relay_serialize_args(args_serialized, args...);
	//	g_inRelaySerialization = false;

	//	if (!PREDA_CALL(EmitRelayToAddress, (const uint8_t*)&addr, opCode, args_serialized.size() > 0 ? &args_serialized[0] : nullptr, uint32_t(args_serialized.size())))
	//		preda_exception::throw_exception("relay@address error", prlrt::ExceptionType::RelayError);
	//}

	template<typename TScope, typename ...Args>
	void relay(const TScope &scope_key, uint32_t scope_type, uint32_t opCode, Args&& ...args)
	{
		std::vector<uint8_t> args_serialized;
		g_inRelaySerialization = true;
		relay_serialize_args(args_serialized, args...);
		g_inRelaySerialization = false;

		if (!PREDA_CALL(EmitRelayToScope, (const uint8_t*)&scope_key, sizeof(TScope), scope_type, opCode, args_serialized.size() > 0 ? &args_serialized[0] : nullptr, uint32_t(args_serialized.size())))
			preda_exception::throw_exception("relay error", prlrt::ExceptionType::RelayError);
	}

	template<typename ...Args>
	void relay_shards(uint32_t opCode, Args&& ...args)
	{
		std::vector<uint8_t> args_serialized;
		g_inRelaySerialization = true;
		relay_serialize_args(args_serialized, args...);
		g_inRelaySerialization = false;

		if (!PREDA_CALL(EmitRelayToShards, opCode, args_serialized.size() > 0 ? &args_serialized[0] : nullptr, uint32_t(args_serialized.size())))
			preda_exception::throw_exception("relay@shards error", prlrt::ExceptionType::RelayError);
	}

	template<typename ...Args>
	void relay_global(uint32_t opCode, Args&& ...args)
	{
		std::vector<uint8_t> args_serialized;
		g_inRelaySerialization = true;
		relay_serialize_args(args_serialized, args...);
		g_inRelaySerialization = false;

		if (!PREDA_CALL(EmitRelayToGlobal, opCode, args_serialized.size() > 0 ? &args_serialized[0] : nullptr, uint32_t(args_serialized.size())))
			preda_exception::throw_exception("relay@global error", prlrt::ExceptionType::RelayError);
	}


	template<typename retType, typename ...Args>
	retType cross_call(uint64_t contractId, uint64_t templateContractImportSlot, uint32_t opCode, Args&& ...args)
	{
		retType ret;
		const void *p[sizeof...(Args) + 1] = { &args..., &ret };
		uint32_t crossCallRes = PREDA_CALL(CrossCall, contractId, templateContractImportSlot, opCode, p, sizeof...(Args) + 1);
		if (crossCallRes != 0)
			preda_exception::throw_exception("cross call error", prlrt::ExceptionType(crossCallRes >> 8));
		return ret;
	}

	template<typename ...Args>
	void cross_call_no_ret(uint64_t contractId, uint64_t templateContractImportSlot, uint32_t opCode, Args&& ...args)
	{
		const void *p[sizeof...(Args) + 1] = { &args..., nullptr };		// here "+1" is necessary, otherwise when args... is empty, we are defining an empty array and get a compile error
		uint32_t crossCallRes = PREDA_CALL(CrossCall, contractId, templateContractImportSlot, opCode, p, sizeof...(Args));
		if (crossCallRes != 0)
			preda_exception::throw_exception("cross call error", prlrt::ExceptionType(crossCallRes >> 8));
	}

	template<typename T>
	void report_return_value(const char *typeExportName, T &&arg)
	{
		std::vector<uint8_t> buffer(arg.get_serialize_size());
		arg.serialize_out(&buffer[0], true);
		PREDA_CALL(ReportReturnValue, typeExportName, &buffer[0], (uint32_t)buffer.size());
	}

	template<typename ...Args>
	uint64_t deploy_call(uint64_t templateContractImportSlot, Args&& ...args)
	{
		const void* p[sizeof...(Args) + 1] = { &args..., nullptr };		// here "+1" is necessary, otherwise when args... is empty, we are defining an empty array and get a compile error
		uint64_t new_contract_id = PREDA_CALL(DeployCall, templateContractImportSlot, p, sizeof...(Args));
		if (new_contract_id == 0)		// 0 is invalid contract id
			preda_exception::throw_exception("deploy call error", prlrt::ExceptionType::DeployFailed);

		return new_contract_id;
	}

	void burn_gas_loop()
	{
		if (!PREDA_CALL(BurnGasLoop, ))
			preda_exception::throw_exception("gas used up by loop", prlrt::ExceptionType::GasUsedUp);
	}

	void burn_gas_function_call()
	{
		if (!PREDA_CALL(BurnGasLoop, ))
			preda_exception::throw_exception("gas used up by function call", prlrt::ExceptionType::GasUsedUp);
	}
}
