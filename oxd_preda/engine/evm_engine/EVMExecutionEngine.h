#pragma once
#define ENABLE_EVM
#ifdef ENABLE_EVM
#include "../../native/abi/vm_interfaces.h"
#include "EVMContractData.h"
#ifdef _WIN32
	#pragma warning(push)
	#pragma warning(disable:4068 4819)
#endif
#include <evmc/evmc.hpp>
#ifdef _WIN32
	#pragma warning(pop)
#endif

namespace xtl {
	class ContractDatabase;
	class CrystalityHost;

	enum class ExecutionResult : uint8_t {
		NoError = 0,
		ContractNotFound = 1,
		InvalidFunctionId = 2,
		FunctionSignatureMismatch = 3,
		ExecutionError = 4,
		//ContractStateExceedsSizeLimit			= 5,
		//SerializeOutContractStateError		= 6,
		SystemErrorBegin = 128,
		CannotLoadLibrary = 128,
		CannotCreateContractInstance = 129,
		MapContractStateError = 130,
	};

	class EVMExecutionEngine : public rvm::ExecutionUnit
	{
	private:
		evmc::VM m_vm;
		ContractDatabase* m_pDB;
		static constexpr unsigned int CREATE_STORE_GAS = 1;
		static constexpr unsigned int GAS_PRICE = 1;
	public:
		EVMExecutionEngine(ContractDatabase* pDB);
		virtual ~EVMExecutionEngine() {}

		evmc::Result evm_create(CrystalityHost& host, const evmc_message& msg);
		evmc::Result evm_execute(CrystalityHost &host, const evmc_message &msg);
		std::string  emit_log(rvm::ContractId cid, evmc::bytes32 event_sig, evmc::bytes_view event_data);

	// from rvm::ExecutionUnit
	public: 
		virtual rvm::InvokeResult 		Invoke(rvm::ExecutionContext* exec, uint32_t gas_limit, rvm::ContractInvokeId contract, rvm::OpCode opcode, const rvm::ConstData* args_serialized) override;
		virtual bool 					DeployContracts(rvm::ExecutionContext* exec, rvm::CompiledModules* linked, const rvm::ContractVersionId* target_cvids, rvm::DataBuffer** deploy_stub, rvm::LogMessageOutput* log_msg_output) override;
		virtual rvm::InvokeResult		InitializeContracts(rvm::ExecutionContext* exec, uint32_t gas_limit, rvm::CompiledModules* linked, const rvm::ConstData* ctor_args) override;
		virtual void 					Release() override;
		virtual void 					GetExceptionMessage(uint16_t except, rvm::StringStream* str) const override;
	};

	class CrystalityHost : public evmc::Host
	{
		friend EVMExecutionEngine;
    private:
        EVMExecutionEngine& m_engine;
        rvm::ExecutionContext& m_ctx;
        ::evmc_tx_context m_tx_ctx;
		evmc::bytes32 m_shard_order;
		struct Account{
			// evmc::uint256be balance;
			// evmc::uint256be nonce;
			evmc::bytes_view code;
			evmc::bytes32 code_hash;
			std::unordered_map<evmc::bytes32, evmc::bytes32> storage;
		};
		mutable std::map<evmc::address, Account> m_accounts;
		struct AccessedHistory
		{
			std::unordered_set<evmc::address> accessed_account;
			std::unordered_set<evmc::bytes32> accessed_storage_slots;
		};
        mutable std::vector<AccessedHistory> m_access_stack;

	public:
        static constexpr rvm::Scope GlobalStorageScope = rvm::SCOPE_MAKE(rvm::ScopeType::ScatteredMapOnGlobal, rvm::ScopeKeySized::UInt256, 0);
        static constexpr rvm::Scope ShardStorageScope = rvm::SCOPE_MAKE(rvm::ScopeType::ScatteredMapOnShard, rvm::ScopeKeySized::UInt256, 0);
        static constexpr rvm::Scope BalanceScope = rvm::SCOPE_MAKE(rvm::ScopeType::ScatteredMapOnGlobal, rvm::ScopeKeySized::UInt160, 0);
        static constexpr rvm::Scope CodeScope = rvm::SCOPE_MAKE(rvm::ScopeType::ScatteredMapOnGlobal, rvm::ScopeKeySized::UInt160, 1);
        static constexpr rvm::Scope CodeHashScope = rvm::SCOPE_MAKE(rvm::ScopeType::ScatteredMapOnGlobal, rvm::ScopeKeySized::UInt160, 2);
        static constexpr rvm::Scope NonceScope = rvm::SCOPE_MAKE(rvm::ScopeType::ScatteredMapOnGlobal, rvm::ScopeKeySized::UInt160, 3);
        static constexpr rvm::Scope ContractIdScope = rvm::SCOPE_MAKE(rvm::ScopeType::ScatteredMapOnGlobal, rvm::ScopeKeySized::UInt160, 4);

        static constexpr rvm::ContractScopeId BalanceCSID = rvm::CONTRACT_SET_SCOPE(EVM_BASE_CID, BalanceScope);
        static constexpr rvm::ContractScopeId CodeCSID = rvm::CONTRACT_SET_SCOPE(EVM_BASE_CID, CodeScope);
        static constexpr rvm::ContractScopeId CodeHashCSID = rvm::CONTRACT_SET_SCOPE(EVM_BASE_CID, CodeHashScope);
        static constexpr rvm::ContractScopeId NonceCSID = rvm::CONTRACT_SET_SCOPE(EVM_BASE_CID, NonceScope);
        static constexpr rvm::ContractScopeId ContractIdCSID = rvm::CONTRACT_SET_SCOPE(EVM_BASE_CID, ContractIdScope);
	private:
        evmc::bytes32 				get_original_storage_value(const evmc::address& addr, const evmc::bytes32& key) const noexcept;
        evmc::uint256be 			get_original_balance(const evmc::address& addr) const noexcept;
        evmc::uint256be 			get_original_nonce(const evmc::address& addr) const noexcept;
        const evmc::bytes_view 		get_original_code(const evmc::address& addr) const noexcept;
        evmc::bytes32 				get_original_hash(const evmc::address& addr) const noexcept;
        rvm::ContractId 			get_original_contract_id(const evmc::address& addr) const noexcept;
        void 						record_account_access(const evmc::address& addr) const noexcept;
        bool 						account_accessed(const evmc::address& addr) const noexcept;
        void 						push_call_stack() noexcept;
        void 						pop_call_stack() noexcept;

    public:
        CrystalityHost(EVMExecutionEngine& engine, rvm::ExecutionContext& ctx);
        bool transfer(const evmc::address& from, const evmc::address& to, const evmc::uint256be& value_evm);
        evmc::uint256be get_nonce(const evmc::address& addr) const noexcept;
        evmc::bytes_view get_code(const evmc::address& addr) const noexcept;
		int commit_state();
	
	/// From evmc::Host
	public:
        /// Returns true if an account exists (EVMC Host method).
        bool account_exists(const evmc::address& addr) const noexcept override;
        /// Get the account's storage value at the given key (EVMC Host method).
        evmc::bytes32 get_storage(const evmc::address& addr, const evmc::bytes32& key) const noexcept override;
        /// Set the account's storage value (EVMC Host method).
        evmc_storage_status set_storage(const evmc::address& addr, const evmc::bytes32& key, const evmc::bytes32& value) noexcept override;
        /// Get the account's balance (EVMC Host method).
        evmc::uint256be get_balance(const evmc::address& addr) const noexcept override;
        /// Get the account's code size (EVMC host method).
        size_t get_code_size(const evmc::address& addr) const noexcept override;
        /// Get the account's code hash (EVMC host method).
        evmc::bytes32 get_code_hash(const evmc::address& addr) const noexcept override;
        /// Copy the account's code to the given buffer (EVMC host method).
        size_t copy_code(const evmc::address& addr, size_t code_offset, uint8_t* buffer_data, size_t buffer_size) const noexcept override;
        /// Selfdestruct the account (EVMC host method).
        bool selfdestruct(const evmc::address& addr, const evmc::address& beneficiary) noexcept override;
        /// Call/create other contract (EVMC host method).
        evmc::Result call(const evmc_message& msg) noexcept override;
        /// Get transaction context (EVMC host method).
        evmc_tx_context get_tx_context() const noexcept override;
        /// Get the block header hash (EVMC host method).
        evmc::bytes32 get_block_hash(int64_t block_number) const noexcept override;
        /// Emit LOG (EVMC host method).
        void emit_log(const evmc::address& addr, const uint8_t* data, size_t data_size, const evmc::bytes32 topics[], size_t topics_count) noexcept override;
        /// Record an account access.
        evmc_access_status access_account(const evmc::address& addr) noexcept override;
        /// Access the account's storage value at the given key.
        evmc_access_status access_storage(const evmc::address& addr, const evmc::bytes32& key) noexcept override;
	};
}
#endif