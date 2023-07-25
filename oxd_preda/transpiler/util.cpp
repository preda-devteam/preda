#include "util.h"

namespace util
{
	const std::string& ScopeTypeToString(transpiler::ScopeType scope)
	{
		static std::string name_global = "global";
		static std::string name_shard = "shard";
		static std::string name_address = "address";
		static std::string name_uint32 = "uint32";
		static std::string name_uint64 = "uint64";
		static std::string name_uint96 = "uint96";
		static std::string name_uint128 = "uint128";
		static std::string name_uint160 = "uint160";
		static std::string name_uint256 = "uint256";
		static std::string name_uint512 = "uint512";
		static std::string name_empty = "";
		switch (scope)
		{
		case transpiler::ScopeType::Global:
			return name_global;
		case transpiler::ScopeType::Shard:
			return name_shard;
		case transpiler::ScopeType::Address:
			return name_address;
		case transpiler::ScopeType::Uint32:
			return name_uint32;
		case transpiler::ScopeType::Uint64:
			return name_uint64;
		case transpiler::ScopeType::Uint96:
			return name_uint96;
		case transpiler::ScopeType::Uint128:
			return name_uint128;
		case transpiler::ScopeType::Uint160:
			return name_uint160;
		case transpiler::ScopeType::Uint256:
			return name_uint256;
		case transpiler::ScopeType::Uint512:
			return name_uint512;
		default:
			return name_empty;
		}

		return name_empty;
	}
}
