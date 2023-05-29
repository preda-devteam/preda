#pragma once
#include <cstdint>

namespace transpiler {

enum class ScopeType : uint32_t {
	Mask = 0xf,
	None = 0,			// e.g. function local variables, built-in variables
	Global,
	Shard,
	Address,
	Uint16,
	Uint32,
	Uint64,
	Uint256,
	Uint512,
	Num,
};

enum class FunctionFlags : uint32_t {
	// lowest bytes reserved for scope
	ScopeTypeMask				= uint32_t(ScopeType::Mask),

	CallableFromTransaction		= (uint32_t(ScopeTypeMask) + 1) << 0,		// can be called from a transaction, i.e. defined with "export"
	CallableFromRelay			= (uint32_t(ScopeTypeMask) + 1) << 1,		// can be called from a relay, i.e. a relay statement relays to it
	CallableFromOtherContract	= (uint32_t(ScopeTypeMask) + 1) << 2,		// can be called from other contracts, i.e. defined with "public"
	CallableFromSystem			= (uint32_t(ScopeTypeMask) + 1) << 3,		// can be called from system yield, i.e. it's a reserved function (e.g on_deploy)
	IsConst						= (uint32_t(ScopeTypeMask) + 1) << 4,		// can not change any state variable (can still relay), i.e. defined with "const"
	HasRelayScopeStatement		= (uint32_t(ScopeTypeMask) + 1) << 5,		// has relay@address statement
	HasRelayShardsStatement		= (uint32_t(ScopeTypeMask) + 1) << 6,		// has relay@shards statement
	HasRelayGlobalStatement		= (uint32_t(ScopeTypeMask) + 1) << 7,		// has relay@global statement
	GlobalStateDependency		= (uint32_t(ScopeTypeMask) + 1) << 8,		// accesses global state in function
	HasAnyRelayStatement		= HasRelayScopeStatement | HasRelayShardsStatement | HasRelayGlobalStatement,		// has any relay statement
	PropagatableFlagsMask		= HasAnyRelayStatement | GlobalStateDependency,				// propagatable flags, i.e. if f() calls g(), f() gets any of these flags that g() has
};

}
