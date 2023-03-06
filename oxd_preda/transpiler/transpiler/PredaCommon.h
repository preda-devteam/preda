#pragma once
#include <cstdint>

namespace transpiler {

enum class PredaFunctionFlags : uint32_t {
	ContextClassMask			= 3 << 0,		// mask for context class
	ContextClassNone			= 0 << 0,		// the functions does not need any context
	ContextClassGlobal			= 1 << 0,		// it's a global function
	ContextClassShard			= 2 << 0,		// it's a shard function
	ContextClassAddress			= 3 << 0,		// it's an address function
	CallableFromTransaction		= 1 << 2,		// can be called from a transaction, i.e. defined with "export"
	CallableFromRelay			= 1 << 3,		// can be called from a relay, i.e. a relay statement relays to it
	CallableFromOtherContract	= 1 << 4,		// can be called from other contracts, i.e. defined with "public"
	CallableFromSystem			= 1 << 5,		// can be called from system yield, i.e. it's a reserved function (e.g on_deploy)
	IsConst						= 1 << 6,		// can not change any state variable (can still relay), i.e. defined with "const"
	BlockDependencyPosition		= 1 << 7,		// depends on the position of the block where it's executed, e.g. block height
	BlockDependencyPayload		= 1 << 8,		// depends on the payload of the block where it's executed, e.g. block miner, block time
	BlockDependencyEntropy		= 1 << 9,		// depends on the entropy of the block, e.g. it uses the secure RNG
	TransactionDependency		= 1 << 10,		// depends on the transaction, e.g. signer, initiator address
	HasRelayAddressStatement	= 1 << 11,		// has relay@address statement
	HasRelayShardsStatement		= 1 << 12,		// has relay@shards statement
	HasRelayGlobalStatement		= 1 << 13,		// has relay@global statement
	GlobalStateDependency		= 1 << 14,		// accesses global state in
	HasAnyRelayStatement = HasRelayAddressStatement | HasRelayShardsStatement | HasRelayGlobalStatement,		// has any relay statement
	PropagatableFlagsMask = BlockDependencyPosition | BlockDependencyPayload | BlockDependencyEntropy | TransactionDependency | HasAnyRelayStatement | GlobalStateDependency,		// propagatable flags, i.e. if f() calls g(), f() gets any of these flags that g() has
};

}
