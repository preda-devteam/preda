#pragma once
#include <cstdint>
#include <cstring>
#include "typeidentifier.h"
#include "runtime_interface.h"

namespace prlrt {

	using serialize_size_type = uint32_t;		// type of size data in serialization

	extern thread_local IRuntimeInterface* g_executionEngineInterface;
	extern thread_local bool g_inRelaySerialization;

	bool util_rip_struct_serialized_header(prlrt::serialize_size_type num_member, uint8_t *&buffer, prlrt::serialize_size_type &bufferSize)
	{
		if (bufferSize < 1)
			return false;
		uint8_t bytesPerOffset = (buffer[0] & 3) + 1;
		if (bufferSize < bytesPerOffset * (num_member + 1))
			return false;

		prlrt::serialize_size_type num_member_2 = (buffer[0] >> 4);				// rest of first byteWidth bytes is number of members
		for (uint8_t i = 1; i < bytesPerOffset; i++)
			num_member_2 += prlrt::serialize_size_type(buffer[i]) << ((i - 1) * 8 + 4);
		if (num_member_2 != num_member)							// the number of members should match the one in signature
			return false;

		buffer += bytesPerOffset * (num_member + 1);
		bufferSize -= bytesPerOffset * (num_member + 1);

		return true;
	}
}

#if defined(__wasm32__)
#define PREDA_CALL(FN, ...) preda##FN(__VA_ARGS__)
#else
#define PREDA_CALL(FN, ...) g_executionEngineInterface->FN(__VA_ARGS__)
#endif