#include "EVMExecutionEngine.h"

#include <list>
#include <array>

#include <evmone/evmone.h>
#include "EVMContractDataBase.h"

#include "../../../oxd_libsec/oxd_libsec.h"

#ifdef ENABLE_EVM

namespace preda_evm {
    struct CodeAndHash {
        evmc::bytes code;
        evmc::bytes32 hash;
    };

    TTMathUint256 EVMCUintToTTMathUint(const evmc::uint256be& num)
    {
        TTMathUint256 ret;
        uint8_t* b = (uint8_t*)ret.table;
        for (size_t i = 0; i < sizeof(num); i++)
        {
            b[i] = num.bytes[sizeof(num) - 1 - i];
        }
        return ret;
    }

    evmc::uint256be TTMathUintToEVMCUint(const TTMathUint256& num)
    {
        evmc::uint256be ret;
        uint8_t* b = (uint8_t*)num.table;
        for (size_t i = 0; i < sizeof(ret); i++)
        {
            ret.bytes[i] = b[sizeof(ret) - 1 - i];
        }
        return ret;
    }

    struct EVMCallStack
    {
        std::unordered_map<evmc::address, evmc::uint256be> balances;
        std::unordered_map<evmc::address, evmc::uint256be> nonces;
        std::unordered_map<evmc::address, std::unordered_map<evmc::bytes32, evmc::bytes32>> storages;
        std::unordered_map<evmc::address, CodeAndHash> code_hashes;
        std::unordered_set<evmc::address> accessed_account;
        std::unordered_map<evmc::address, std::unordered_set<evmc::bytes32>> accessed_storage_slots;

        void merge(EVMCallStack& other)
        {
            for (auto& it : other.balances)
            {
                balances[it.first] = it.second;
            }

            for (auto& it : other.nonces)
            {
                nonces[it.first] = it.second;
            }

            for (auto& it : other.storages)
            {
                auto& s = storages[it.first];
                for (auto& ist : it.second)
                {
                    s[ist.first] = ist.second;
                }
            }

            for (auto& it : other.code_hashes)
            {
                code_hashes[it.first] = it.second;
            }

            accessed_account.merge(other.accessed_account);

            for (auto& it : other.accessed_storage_slots)
            {
                accessed_storage_slots[it.first].merge(it.second);
            }
        }
    };

    static evmc::bytes32 RVMHashToEVMHash(const rvm::HashValue& hash)
    {
        evmc::bytes32 ret;
        static_assert(sizeof(hash) == sizeof(ret), "hash size match");
        std::copy(&hash._[0], &hash._[0] + sizeof(ret), ret.bytes);
        return ret;
    }

	class EVMHost : public evmc::Host
	{
    private:
        EVMExecutionEngine& m_engine;
        rvm::ExecutionContext& m_ctx;
        mutable std::list<EVMCallStack> m_stack;
        evmc_tx_context m_tx_ctx;

        void record_account_access(const evmc::address& addr) const noexcept
        {
            m_stack.back().accessed_account.insert(addr);
        }

        bool account_accessed(const evmc::address& addr) const noexcept
        {
            for (auto s = m_stack.rbegin(); s != m_stack.rend(); s++)
            {
                if (s->accessed_account.count(addr) != 0)
                {
                    return true;
                }
            }

            return false;
        }

        using StorageStateKey = std::array<uint8_t, 1 + sizeof(evmc::address) + sizeof(evmc::bytes32)>;
        static constexpr uint8_t StorageKeyPrefix = 's';
        using StateKey = std::array<uint8_t, 1 + sizeof(evmc::address)>;
        static constexpr uint8_t BalanceKeyPrefix = 'b';
        static constexpr uint8_t CodeKeyPrefix = 'c';
        static constexpr uint8_t HashKeyPrefix = 'h';
        static constexpr uint8_t NonceKeyPrefix = 'n';
        static constexpr uint8_t ContractIdPrefix = 'i';


        static constexpr rvm::Scope StorageScope = rvm::_details::SCOPE_MAKE(rvm::ScopeType::ScatteredMapOnGlobal, rvm::ScopeKeySized::VaryingSize, 0);
        static constexpr rvm::Scope BalanceScope = rvm::_details::SCOPE_MAKE(rvm::ScopeType::ScatteredMapOnGlobal, rvm::ScopeKeySized::VaryingSize, 1);
        static constexpr rvm::Scope CodeScope = rvm::_details::SCOPE_MAKE(rvm::ScopeType::ScatteredMapOnGlobal, rvm::ScopeKeySized::VaryingSize, 1);
        static constexpr rvm::Scope CodeHashScope = rvm::_details::SCOPE_MAKE(rvm::ScopeType::ScatteredMapOnGlobal, rvm::ScopeKeySized::VaryingSize, 1);
        static constexpr rvm::Scope NonceScope = rvm::_details::SCOPE_MAKE(rvm::ScopeType::ScatteredMapOnGlobal, rvm::ScopeKeySized::VaryingSize, 1);
        static constexpr rvm::Scope ContractIdScope = rvm::_details::SCOPE_MAKE(rvm::ScopeType::ScatteredMapOnGlobal, rvm::ScopeKeySized::VaryingSize, 1);

        static constexpr rvm::ContractScopeId StorageCSID = rvm::_details::CONTRACT_SET_SCOPE(EVM_CID, StorageScope);
        static constexpr rvm::ContractScopeId BalanceCSID = rvm::_details::CONTRACT_SET_SCOPE(EVM_CID, BalanceScope);
        static constexpr rvm::ContractScopeId CodeCSID = rvm::_details::CONTRACT_SET_SCOPE(EVM_CID, CodeScope);
        static constexpr rvm::ContractScopeId CodeHashCSID = rvm::_details::CONTRACT_SET_SCOPE(EVM_CID, CodeHashScope);
        static constexpr rvm::ContractScopeId NonceCSID = rvm::_details::CONTRACT_SET_SCOPE(EVM_CID, NonceScope);
        static constexpr rvm::ContractScopeId ContractIdCSID = rvm::_details::CONTRACT_SET_SCOPE(EVM_CID, ContractIdScope);


        static StorageStateKey get_storage_state_key(const evmc::address& addr, const evmc::bytes32& key)
        {
            StorageStateKey key_bytes{};

            key_bytes[0] = StorageKeyPrefix;
            size_t i = 1;
            for (size_t j = 0; j < sizeof(addr); j++)
            {
                key_bytes[i++] = addr.bytes[j];
            }
            for (size_t j = 0; j < sizeof(key); j++)
            {
                key_bytes[i++] = key.bytes[j];
            }

            return key_bytes;
        }

        evmc::bytes32 get_original_storage_value(const evmc::address& addr, const evmc::bytes32& key) const noexcept
        {
            auto key_bytes = get_storage_state_key(addr, key);

            rvm::ScopeKey skey{ key_bytes.data(), sizeof(key_bytes) };
            
            auto value = m_ctx.GetState(StorageCSID, &skey);
            evmc::bytes32 ret{};
            if (value.DataSize >= sizeof(ret))
            {
                std::copy(value.DataPtr, value.DataPtr + value.DataSize, ret.bytes);
            }
            return ret;
        }

        static StateKey get_state_key(uint8_t prefix, const evmc::address& addr)
        {
            StateKey key_bytes{};

            key_bytes[0] = prefix;
            size_t i = 1;
            for (size_t j = 0; j < sizeof(addr); j++)
            {
                key_bytes[i++] = addr.bytes[j];
            }

            return key_bytes;
        }

        evmc::uint256be get_original_balance(const evmc::address& addr) const noexcept
        {
            auto key_bytes = get_state_key(BalanceKeyPrefix, addr);

            rvm::ScopeKey skey{ key_bytes.data(), sizeof(key_bytes) };

            auto value = m_ctx.GetState(BalanceCSID, &skey);
            evmc::uint256be ret{};
            if (value.DataSize >= sizeof(ret))
            {
                std::copy(value.DataPtr, value.DataPtr + value.DataSize, ret.bytes);
            }
            return ret;
        }

        evmc::uint256be get_original_nonce(const evmc::address& addr) const noexcept
        {
            auto key_bytes = get_state_key(NonceKeyPrefix, addr);

            rvm::ScopeKey skey{ key_bytes.data(), sizeof(key_bytes) };

            auto value = m_ctx.GetState(NonceCSID, &skey);
            evmc::uint256be ret{};
            if (value.DataSize >= sizeof(ret))
            {
                std::copy(value.DataPtr, value.DataPtr + value.DataSize, ret.bytes);
            }
            return ret;
        }

        const evmc::bytes_view get_original_code(const evmc::address& addr) const noexcept
        {
            auto key_bytes = get_state_key(CodeKeyPrefix, addr);

            rvm::ScopeKey skey{ key_bytes.data(), sizeof(key_bytes) };

            auto value = m_ctx.GetState(CodeCSID, &skey);
            return evmc::bytes_view(value.DataPtr, value.DataSize);
        }

        evmc::bytes32 get_original_hash(const evmc::address& addr) const noexcept
        {
            auto key_bytes = get_state_key(HashKeyPrefix, addr);

            rvm::ScopeKey skey{ key_bytes.data(), sizeof(key_bytes) };

            auto value = m_ctx.GetState(CodeHashCSID, &skey);
            evmc::bytes32 ret{};
            if (value.DataSize >= sizeof(ret))
            {
                std::copy(value.DataPtr, value.DataPtr + value.DataSize, ret.bytes);
            }
            return ret;
        }

        rvm::ContractId get_original_contract_id(const evmc::address& addr) const noexcept
        {
            auto key_bytes = get_state_key(ContractIdPrefix, addr);

            rvm::ScopeKey skey{ key_bytes.data(), sizeof(key_bytes) };

            auto value = m_ctx.GetState(ContractIdCSID, &skey);
            rvm::ContractId ret = rvm::ContractIdInvalid;
            if (value.DataSize >= sizeof(ret))
            {
                ret = *(rvm::ContractId*)value.DataPtr;
            }
            return ret;
        }

        void push_call_stack()
        {
            m_stack.push_back(EVMCallStack{});
        }

        void pop_call_stack(bool merge)
        {
            EVMCallStack s(std::move(m_stack.back()));
            m_stack.pop_back();
            if (merge)
            {
                m_stack.back().merge(s);
            }
            m_stack.back().merge(s);
        }

    public:

        EVMCallStack& get_stack_back() const {
            return m_stack.back();
        }

        class StackScope {
            EVMHost& m_host;
            bool m_merge = true;
        public:
            StackScope(EVMHost& host) : m_host(host)
            {
                m_host.push_call_stack();
            }

            void NoMerge()
            {
                m_merge = false;
            }

            ~StackScope()
            {
                m_host.pop_call_stack(m_merge);
            }
        };

        EVMHost(EVMExecutionEngine& engine, rvm::ExecutionContext& ctx):
            m_engine(engine),
            m_ctx(ctx)        
        {
            push_call_stack();
            m_tx_ctx.tx_gas_price = evmc::uint256be(1); // TODO gas
            m_tx_ctx.block_gas_limit = 0xafffffffffffffff;
            m_tx_ctx.block_base_fee = evmc::uint256be(1);

            m_tx_ctx.tx_origin = _details::RVMAddressToEVMAddress(*ctx.GetSigner(0)) ; // TODO how to translate from evm address to rvm address?
            m_tx_ctx.block_coinbase = _details::RVMAddressToEVMAddress(*ctx.GetBlockCreator());

            m_tx_ctx.block_number = ctx.GetBlockHeight();
            m_tx_ctx.block_prev_randao = evmc::uint256be(ctx.GetRandomNumber());
            m_tx_ctx.chain_id = evmc::uint256be({ 'p', 'r', 'e', 'd', 'a' });
        }

        ~EVMHost()
        {
            EVMCallStack& s = get_stack_back();
            
            for (auto &it : s.nonces)
            {
                auto key_bytes = get_state_key(NonceKeyPrefix, it.first);

                rvm::ScopeKey skey{ key_bytes.data(), sizeof(key_bytes) };

                uint8_t* state = m_ctx.AllocateStateMemory(sizeof(it.second.bytes));
                std::memcpy(state, it.second.bytes, sizeof(it.second.bytes));
                m_ctx.CommitNewState(0, NonceCSID, &skey, state);
            }

            for (auto& it : s.balances)
            {
                auto key_bytes = get_state_key(BalanceKeyPrefix, it.first);

                rvm::ScopeKey skey{ key_bytes.data(), sizeof(key_bytes) };

                uint8_t* state = m_ctx.AllocateStateMemory(sizeof(it.second.bytes));
                std::memcpy(state, it.second.bytes, sizeof(it.second.bytes));
                m_ctx.CommitNewState(0, BalanceCSID, &skey, state);
            }

            for (auto& it : s.storages)
            {
                const evmc::address& addr = it.first;
                for (auto& ist : it.second)
                {
                    auto key_bytes = get_storage_state_key(addr, ist.first);
                    rvm::ScopeKey skey{ key_bytes.data(), sizeof(key_bytes) };
                    uint8_t* state = m_ctx.AllocateStateMemory(sizeof(ist.second.bytes));
                    std::memcpy(state, ist.second.bytes, sizeof(ist.second.bytes));
                    m_ctx.CommitNewState(0, StorageCSID, &skey, state);
                }
            }

            for (auto& it : s.code_hashes)
            {
                {
                    auto key_bytes = get_state_key(CodeKeyPrefix, it.first);

                    rvm::ScopeKey skey{ key_bytes.data(), sizeof(key_bytes) };
                    uint8_t* state = m_ctx.AllocateStateMemory((uint32_t)it.second.code.size());
                    std::memcpy(state, it.second.code.data(), it.second.code.size());
                    m_ctx.CommitNewState(0, CodeCSID, &skey, state);
                }

                {
                    auto key_bytes = get_state_key(HashKeyPrefix, it.first);

                    rvm::ScopeKey skey{ key_bytes.data(), sizeof(key_bytes) };
                    uint8_t* state = m_ctx.AllocateStateMemory(sizeof(it.second.hash.bytes));
                    std::memcpy(state, it.second.hash.bytes, sizeof(it.second.hash.bytes));
                    m_ctx.CommitNewState(0, CodeHashCSID, &skey, state);
                }
            }
        }

        bool transfer(const evmc::address& from, const evmc::address& to, const evmc::uint256be& value_evm)
        {
            TTMathUint256 from_balance = EVMCUintToTTMathUint(get_balance(from));
            TTMathUint256 value = EVMCUintToTTMathUint(value_evm);
            if (from_balance < value)
            {
                return false;
            }
            from_balance -= value;
            TTMathUint256 to_balance = EVMCUintToTTMathUint(get_balance(to));
            to_balance += value;
            m_stack.back().balances[from] = TTMathUintToEVMCUint(from_balance);
            m_stack.back().balances[to] = TTMathUintToEVMCUint(to_balance);
            return true;
        }

        evmc::uint256be get_nonce(const evmc::address& addr) const noexcept
        {
            record_account_access(addr);

            for (auto s = m_stack.rbegin(); s != m_stack.rend(); s++)
            {
                auto it = s->nonces.find(addr);
                if (it != s->nonces.end())
                {
                    return it->second;
                }
            }

            return get_original_nonce(addr);
        }

        /// Returns true if an account exists (EVMC Host method).
        bool account_exists(const evmc::address& addr) const noexcept override
        {
            for (auto s = m_stack.rbegin(); s != m_stack.rend(); s++)
            {
                {
                    auto it = s->balances.find(addr);
                    if (it != s->balances.end())
                    {
                        return true;
                    }
                }

                {
                    auto it = s->code_hashes.find(addr);
                    if (it != s->code_hashes.end())
                    {
                        return true;
                    }
                }

                {
                    auto it = s->storages.find(addr);
                    if (it != s->storages.end())
                    {
                        return true;
                    }
                }

                {
                    auto it = s->nonces.find(addr);
                    if (it != s->nonces.end())
                    {
                        return true;
                    }
                }
            }

            if (get_original_balance(addr) != evmc::uint256be(0))
            {
                return true;
            }


            if (get_original_nonce(addr) != evmc::uint256be(0))
            {
                return true;
            }

            if (get_original_code(addr).size() != 0)
            {
                return true;
            }

            return false;
        }

        /// Get the account's storage value at the given key (EVMC Host method).
        evmc::bytes32 get_storage(const evmc::address& addr, const evmc::bytes32& key) const noexcept override
        {
            record_account_access(addr);

            for (auto s = m_stack.rbegin(); s != m_stack.rend(); s++)
            {
                auto ait = s->storages.find(addr);
                if (ait != s->storages.end())
                {
                    auto sit = ait->second.find(key);
                    if (sit != ait->second.end())
                    {
                        return sit->second;
                    }
                }
            }

            return get_original_storage_value(addr, key);
        }

        /// Set the account's storage value (EVMC Host method).
        evmc_storage_status set_storage(const evmc::address& addr,
            const evmc::bytes32& key,
            const evmc::bytes32& value) noexcept override
        {
            record_account_access(addr);

            // Follow the EIP-2200 specification as closely as possible.
            // https://eips.ethereum.org/EIPS/eip-2200
            // Warning: this is not the most efficient implementation. The storage status can be
            // figured out by combining only 4 checks:
            // - original != current (dirty)
            // - original == value (restored)
            // - current != 0
            // - value != 0
            const auto status = [original = get_original_storage_value(addr, key), current = get_storage(addr, key), &value]() {
                // Clause 1 is irrelevant:
                // 1. "If gasleft is less than or equal to gas stipend,
                //    fail the current call frame with 'out of gas' exception"

                // 2. "If current value equals new value (this is a no-op)"
                if (current == value)
                {
                    // "SLOAD_GAS is deducted"
                    return EVMC_STORAGE_ASSIGNED;
                }
                // 3. "If current value does not equal new value"
                else
                {
                    // 3.1. "If original value equals current value
                    //      (this storage slot has not been changed by the current execution context)"
                    if (original == current)
                    {
                        // 3.1.1 "If original value is 0"
                        if (evmc::is_zero(original))
                        {
                            // "SSTORE_SET_GAS is deducted"
                            return EVMC_STORAGE_ADDED;
                        }
                        // 3.1.2 "Otherwise"
                        else
                        {
                            // "SSTORE_RESET_GAS gas is deducted"
                            auto st = EVMC_STORAGE_MODIFIED;

                            // "If new value is 0"
                            if (evmc::is_zero(value))
                            {
                                // "add SSTORE_CLEARS_SCHEDULE gas to refund counter"
                                st = EVMC_STORAGE_DELETED;
                            }

                            return st;
                        }
                    }
                    // 3.2. "If original value does not equal current value
                    //      (this storage slot is dirty),
                    //      SLOAD_GAS gas is deducted.
                    //      Apply both of the following clauses."
                    else
                    {
                        // Because we need to apply "both following clauses"
                        // we first collect information which clause is triggered
                        // then assign status code to combination of these clauses.
                        enum
                        {
                            None = 0,
                            RemoveClearsSchedule = 1 << 0,
                            AddClearsSchedule = 1 << 1,
                            RestoredBySet = 1 << 2,
                            RestoredByReset = 1 << 3,
                        };
                        int triggered_clauses = None;

                        // 3.2.1. "If original value is not 0"
                        if (!evmc::is_zero(original))
                        {
                            // 3.2.1.1. "If current value is 0"
                            if (evmc::is_zero(current))
                            {
                                // "(also means that new value is not 0)"
                                assert(!evmc::is_zero(value));
                                // "remove SSTORE_CLEARS_SCHEDULE gas from refund counter"
                                triggered_clauses |= RemoveClearsSchedule;
                            }
                            // 3.2.1.2. "If new value is 0"
                            if (evmc::is_zero(value))
                            {
                                // "(also means that current value is not 0)"
                                assert(!evmc::is_zero(current));
                                // "add SSTORE_CLEARS_SCHEDULE gas to refund counter"
                                triggered_clauses |= AddClearsSchedule;
                            }
                        }

                        // 3.2.2. "If original value equals new value (this storage slot is reset)"
                        // Except: we use term 'storage slot restored'.
                        if (original == value)
                        {
                            // 3.2.2.1. "If original value is 0"
                            if (evmc::is_zero(original))
                            {
                                // "add SSTORE_SET_GAS - SLOAD_GAS to refund counter"
                                triggered_clauses |= RestoredBySet;
                            }
                            // 3.2.2.2. "Otherwise"
                            else
                            {
                                // "add SSTORE_RESET_GAS - SLOAD_GAS gas to refund counter"
                                triggered_clauses |= RestoredByReset;
                            }
                        }

                        switch (triggered_clauses)
                        {
                        case RemoveClearsSchedule:
                            return EVMC_STORAGE_DELETED_ADDED;
                        case AddClearsSchedule:
                            return EVMC_STORAGE_MODIFIED_DELETED;
                        case RemoveClearsSchedule | RestoredByReset:
                            return EVMC_STORAGE_DELETED_RESTORED;
                        case RestoredBySet:
                            return EVMC_STORAGE_ADDED_DELETED;
                        case RestoredByReset:
                            return EVMC_STORAGE_MODIFIED_RESTORED;
                        case None:
                            return EVMC_STORAGE_ASSIGNED;
                        default:
                            assert(false);  // Other combinations are impossible.
                            return evmc_storage_status{};
                        }
                    }
                }
            }();

            m_stack.back().storages[addr][key] = value; // Finally update the current storage value.
            return status;
        }

        /// Get the account's balance (EVMC Host method).
        evmc::uint256be get_balance(const evmc::address& addr) const noexcept override
        {
            record_account_access(addr);
            
            for (auto s = m_stack.rbegin(); s != m_stack.rend(); s++)
            {
                auto it = s->balances.find(addr);
                if (it != s->balances.end())
                {
                    return it->second;
                }
            }

            return get_original_balance(addr);
        }

        /// Get the account's code size (EVMC host method).
        size_t get_code_size(const evmc::address& addr) const noexcept override
        {
            record_account_access(addr);
            for (auto s = m_stack.rbegin(); s != m_stack.rend(); s++)
            {
                auto it = s->code_hashes.find(addr);
                if (it != s->code_hashes.end())
                {
                    return it->second.code.size();
                }
            }
            return get_original_code(addr).size();
        }

        /// Get the account's code hash (EVMC host method).
        evmc::bytes32 get_code_hash(const evmc::address& addr) const noexcept override
        {
            record_account_access(addr);
            for (auto s = m_stack.rbegin(); s != m_stack.rend(); s++)
            {
                auto it = s->code_hashes.find(addr);
                if (it != s->code_hashes.end())
                {
                    return it->second.hash;
                }
            }
            return get_original_hash(addr);
        }

        evmc::bytes_view get_code(const evmc::address& addr) const noexcept
        {
            record_account_access(addr);

            bool found = false;
            evmc::bytes_view code{};
            for (auto s = m_stack.rbegin(); s != m_stack.rend(); s++)
            {
                auto it = s->code_hashes.find(addr);
                if (it != s->code_hashes.end())
                {
                    code = it->second.code;
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                code = get_original_code(addr);
            }

            return code;
        }

        /// Copy the account's code to the given buffer (EVMC host method).
        size_t copy_code(const evmc::address& addr,
            size_t code_offset,
            uint8_t* buffer_data,
            size_t buffer_size) const noexcept override
        {
            record_account_access(addr);

            evmc::bytes_view code = get_code(addr);

            if (code_offset >= code.size())
                return 0;

            const auto n = std::min(buffer_size, code.size() - code_offset);

            if (n > 0)
                std::copy_n(&code[code_offset], n, buffer_data);
            return n;
        }

        /// Selfdestruct the account (EVMC host method).
        bool selfdestruct(const evmc::address& addr, const evmc::address& beneficiary) noexcept override
        {
            // TODO support selfdestruct
            return true;
        }

        /// Call/create other contract (EVMC host method).
        evmc::Result call(const evmc_message& msg) noexcept override
        {
            if (msg.kind == EVMC_CREATE || msg.kind == EVMC_CREATE2)
            {
                return m_engine.RunCreate(*this, msg);
            }
            else
            {
                return m_engine.Run(*this, msg);
            }
        }

        /// Get transaction context (EVMC host method).
        evmc_tx_context get_tx_context() const noexcept override { return m_tx_ctx; }

        /// Get the block header hash (EVMC host method).
        evmc::bytes32 get_block_hash(int64_t block_number) const noexcept override
        {
			ASSERT(0);  // not supportted in dioxide 
            auto* hash = m_ctx.GetPrevBlockHash();
            return RVMHashToEVMHash(*hash);
        }

        /// Emit LOG (EVMC host method).
        void emit_log(const evmc::address& addr,
            const uint8_t* data,
            size_t data_size,
            const evmc::bytes32 topics[],
            size_t topics_count) noexcept override
        {
			rt::String base16Str;
			os::Base16Encode(rt::String_Ref((const char*)data, data_size), base16Str);
			std::cout << data_size << ": " << base16Str << std::endl;
        }

        /// Record an account access.
        ///
        /// This method is required by EIP-2929 introduced in ::EVMC_BERLIN. It will record the account
        /// access in MockedHost::recorded_account_accesses and return previous access status.
        /// This methods returns ::EVMC_ACCESS_WARM for known addresses of precompiles.
        /// The EIP-2929 specifies that evmc_message::sender and evmc_message::recipient are always
        /// ::EVMC_ACCESS_WARM. Therefore, you should init the MockedHost with:
        ///
        ///     mocked_host.access_account(msg.sender);
        ///     mocked_host.access_account(msg.recipient);
        ///
        /// The same way you can mock transaction access list (EIP-2930) for account addresses.
        ///
        /// @param addr  The address of the accessed account.
        /// @returns     The ::EVMC_ACCESS_WARM if the account has been accessed before,
        ///              the ::EVMC_ACCESS_COLD otherwise.
        evmc_access_status access_account(const evmc::address& addr) noexcept override
        {
            using namespace evmc::literals;

            // Accessing precompiled contracts is always warm.
            if (addr >= 0x0000000000000000000000000000000000000001_address &&
                addr <= 0x0000000000000000000000000000000000000009_address)
                return EVMC_ACCESS_WARM;

            // Check if the address have been already accessed.
            bool already_accessed = false;
            for (auto s = m_stack.rbegin(); s != m_stack.rend(); s++)
            {
                if (s->accessed_account.count(addr) > 0)
                {
                    already_accessed = true;
                    break;
                }
            }

            record_account_access(addr);

            return already_accessed ? EVMC_ACCESS_WARM : EVMC_ACCESS_COLD;
        }

        /// Access the account's storage value at the given key.
        ///
        /// This method is required by EIP-2929 introduced in ::EVMC_BERLIN. In records
        /// that the given account's storage key has been access and returns the
        /// previous access status. To mock storage access list (EIP-2930), you can
        /// pre-init account's storage values with the ::EVMC_ACCESS_WARM flag:
        ///
        ///     mocked_host.accounts[msg.recipient].storage[key] = {value,
        ///     EVMC_ACCESS_WARM};
        ///
        /// @param addr  The account address.
        /// @param key   The account's storage key.
        /// @return      The ::EVMC_ACCESS_WARM if the storage key has been accessed
        /// before,
        ///              the ::EVMC_ACCESS_COLD otherwise.
        evmc_access_status access_storage(const evmc::address& addr, const evmc::bytes32& key) noexcept override
        {
            for (auto s = m_stack.rbegin(); s != m_stack.rend(); s++)
            {
                if (s->accessed_storage_slots[addr].count(key) > 0)
                {
                    return EVMC_ACCESS_WARM;
                }
            }
            m_stack.back().accessed_storage_slots[addr].insert(key);
            return EVMC_ACCESS_COLD;
        }
	}; // end of EVMHost

    evmc::Result EVMExecutionEngine::RunCreate(EVMHost& host, const evmc_message& msg)
    {
        ASSERT(msg.kind == EVMC_CREATE || msg.kind == EVMC_CREATE2);

        EVMHost::StackScope ss(host);

        evmc::address addr;
        if (msg.kind == EVMC_CREATE)
        {
            evmc::uint256be nonce = host.get_nonce(msg.sender);
#pragma pack(push,1)
            struct Data {
                evmc::address addr;
                evmc::uint256be nonce;
            } data{ msg.sender, nonce };
            static_assert(sizeof(Data) == sizeof(evmc::address) + sizeof(evmc::uint256be));
#pragma pack(pop)
            rvm::HashValue hash;
            oxd::SecuritySuite::Hash(&data, sizeof(data), &hash);
            std::copy(hash._ + 12, hash._ + 32, addr.bytes);
        }
        else
        {
            evmc::bytes32 code_hash;
            oxd::SecuritySuite::Hash(msg.input_data, (uint32_t)msg.input_size, &code_hash);

#pragma pack(push,1)
            struct Data {
                uint8_t head;
                evmc::address addr;
                evmc::bytes32 salt;
                evmc::bytes32 code_hash;
            } data{ 0xff, msg.sender, msg.create2_salt, code_hash };
            static_assert(sizeof(Data) == 1 + sizeof(evmc::address) + sizeof(evmc::bytes32) + sizeof(evmc::bytes32));
#pragma pack(pop)

            rvm::HashValue hash;
            oxd::SecuritySuite::Hash(&data, sizeof(data), &hash);
            std::copy(hash._ + 12, hash._ + 32, addr.bytes);
        }

        if (host.account_exists(addr))
        {
            ss.NoMerge();
            return evmc::Result(EVMC_FAILURE);
        }

        evmc_message new_msg = msg;
        new_msg.recipient = addr;
        host.get_stack_back().nonces[addr] = evmc::uint256be(1);
        if (!host.transfer(new_msg.sender, addr, msg.value))
        {
            ss.NoMerge();
            return evmc::Result(EVMC_INSUFFICIENT_BALANCE);
        }

        evmc::Result ret = m_vm.execute(host, EVMC_LONDON, new_msg, new_msg.input_data, new_msg.input_size);

        if (ret.status_code != EVMC_SUCCESS)
        {
            ss.NoMerge();
            return ret;
        }

        ret.create_address = addr;
        
        if (ret.output_size * CREATE_STORE_GAS > (uint64_t)ret.gas_left)
        {
            ss.NoMerge();
            return evmc::Result(EVMC_OUT_OF_GAS);
        }

        ret.gas_left -= ret.output_size * CREATE_STORE_GAS;

        evmc::bytes32 code_hash;
        oxd::SecuritySuite::Hash(ret.output_data, (uint32_t)ret.output_size, code_hash.bytes);
        host.get_stack_back().code_hashes[addr] = CodeAndHash{
            evmc::bytes(ret.output_data, ret.output_size),
            code_hash
        };

        return ret;
    }

    evmc::Result EVMExecutionEngine::Run(EVMHost& host, const evmc_message& msg)
    {
        ASSERT(msg.kind != EVMC_CREATE && msg.kind != EVMC_CREATE2);

        EVMHost::StackScope ss(host);

        using namespace evmc::literals;

        // TODO support precompiles
        if (msg.recipient >= 0x0000000000000000000000000000000000000001_address &&
            msg.recipient <= 0x0000000000000000000000000000000000000009_address)
        {
            return evmc::Result(EVMC_PRECOMPILE_FAILURE);
        }

        if (msg.kind == EVMC_CALL && msg.value != evmc::uint256be(0))
        {
            if (!host.transfer(msg.sender, msg.recipient, msg.value))
            {
                ss.NoMerge();
                return evmc::Result(EVMC_INSUFFICIENT_BALANCE);
            }
        }

        evmc::bytes_view code = host.get_code(msg.code_address);
        if (code.empty()) {
            return evmc::Result(EVMC_SUCCESS, msg.gas);
        }

        evmc::Result ret = m_vm.execute(host, EVMC_LONDON, msg, code.data(), code.size());

        if (ret.status_code != EVMC_SUCCESS)
        {
            ss.NoMerge();
            return ret;
        }

        return ret;
    }

    EVMExecutionEngine::EVMExecutionEngine(ContractDatabase* pDB): m_pDB(pDB), m_vm(evmc_create_evmone())
	{
	}

    static rvm::InvokeErrorCode EVMCErrorCodeTORVMErrorCode(evmc_status_code code)
    {
        switch (code)
        {
        case EVMC_SUCCESS:
            return rvm::InvokeErrorCode::Success;
        case EVMC_FAILURE:
            return rvm::InvokeErrorCode::Unspecified;
        case EVMC_REVERT:
            return rvm::InvokeErrorCode::ExceptionThrown;
        case EVMC_OUT_OF_GAS:
            return rvm::InvokeErrorCode::RunOutOfGas;
        case EVMC_INVALID_INSTRUCTION:
        case EVMC_UNDEFINED_INSTRUCTION:
        case EVMC_INTERNAL_ERROR:
        case EVMC_STACK_OVERFLOW:
        case EVMC_STACK_UNDERFLOW:
        case EVMC_BAD_JUMP_DESTINATION:
        case EVMC_INVALID_MEMORY_ACCESS:
        case EVMC_CALL_DEPTH_EXCEEDED:
        case EVMC_STATIC_MODE_VIOLATION:
        case EVMC_PRECOMPILE_FAILURE:
        case EVMC_CONTRACT_VALIDATION_FAILURE:
        case EVMC_WASM_UNREACHABLE_INSTRUCTION:
        case EVMC_WASM_TRAP:
        case EVMC_REJECTED:
            return rvm::InvokeErrorCode::InternalError;
        case EVMC_ARGUMENT_OUT_OF_RANGE:
            return rvm::InvokeErrorCode::InvalidFunctionArgments;
        case EVMC_OUT_OF_MEMORY:
            return rvm::InvokeErrorCode::OutOfMemory;
        case EVMC_INSUFFICIENT_BALANCE:
            return rvm::InvokeErrorCode::InsufficientFunds;
        default:
            return rvm::InvokeErrorCode::Unspecified;
        }
    }
    bool EVMExecutionEngine::ParseSolArgument(const rt::JsonObject& args_json, const ContractCompileData& compileData, uint64_t& value, std::string& data, rvm::OpCode opCode) const
    {
        if (opCode == rvm::OpCode(0))
        {
            value = args_json.GetValueAs<uint64_t>("value", 0);
            return true;
        }
        else
        {
            return compileData.ComposeInputData(args_json, value, data);
        }
    }
    rvm::InvokeResult EVMExecutionEngine::Invoke(rvm::ExecutionContext* executionContext, uint32_t gas_limit, const rvm::ContractModuleID *contract_deployment_id, rvm::OpCode opCode, const rvm::ConstData* args_serialized)
	{
        const rt::String_Ref args_json_str((const char*)args_serialized->DataPtr, args_serialized->DataSize);
        const rt::JsonObject args_json = args_json_str;
        rvm::InvokeResult ret;
        ret.SubCodeHigh = 0;
        ret.SubCodeLow = 0;
        ret.GasBurnt = rvm::RVM_GAS_BURNT_DEFAULT;

        ContractModuleID deployId = _details::RvmCDIDToEVMCDID(contract_deployment_id);
        const ContractDatabaseEntry* entry = m_pDB->FindContractEntry(deployId);

        if (!entry)
        {
            ret.Code = rvm::InvokeErrorCode::ContractUnavailable;
            return ret;
        }

        EVMHost host(*this, *executionContext);

        evmc::address origin = host.get_tx_context().tx_origin;
        uint64_t value = 0;
        rt::String_Ref dataTmp = args_json.GetValue("data");
        std::string data(dataTmp.Begin(), dataTmp.GetLength());
        if(data.empty() && !ParseSolArgument(args_json, entry->compileData, value, data, opCode))
		{
            ret.Code = rvm::InvokeErrorCode::InvalidFunctionArgments;
			return ret;
		}

        if(opCode == rvm::OpCode(0))
        {
            // mint ETH
            evmc::uint256be current_balance = host.get_stack_back().balances[origin];
            evmc::uint256be current_contract_balance = host.get_stack_back().balances[entry->address];
            host.get_stack_back().balances[origin] = TTMathUintToEVMCUint(EVMCUintToTTMathUint(current_balance) + ttmath::uint(value));
            host.get_stack_back().balances[entry->address] = TTMathUintToEVMCUint(EVMCUintToTTMathUint(current_contract_balance) + ttmath::uint(value));
            ret.Code = rvm::InvokeErrorCode::Success;
            return ret;
        }
        else if (opCode == rvm::OpCode(1))
        {
            evmc::uint256be current_balance = host.get_balance(origin);
            if (EVMCUintToTTMathUint(current_balance) < TTMathUint256(gas_limit) * TTMathUint256(GAS_PRICE)) {
                ret.Code = rvm::InvokeErrorCode::InsufficientGasRequired;
                return ret;
            }

            host.get_stack_back().nonces[origin] = TTMathUintToEVMCUint(EVMCUintToTTMathUint(host.get_nonce(origin)).AddOne());

            rt::String data_binary;
			if (!os::Base16Decode(data, data_binary))
			{
                ret.Code = rvm::InvokeErrorCode::InvalidFunctionArgments;
				return ret;
			}

            host.get_stack_back().balances[origin] = TTMathUintToEVMCUint(EVMCUintToTTMathUint(current_balance) - TTMathUint256(gas_limit) * TTMathUint256(GAS_PRICE));

            evmc_message msg{};
            msg.kind = EVMC_CALL;
            msg.gas = gas_limit;
            msg.sender = origin;
            msg.input_data = (uint8_t*)data_binary.Begin();
            msg.input_size = data_binary.GetLength();
            msg.value = evmc::uint256be(value);
            msg.recipient = entry->address;
            msg.code_address = entry->address;
            evmc::Result result = Run(host, msg);
            
            host.get_stack_back().balances[origin] = TTMathUintToEVMCUint(
                EVMCUintToTTMathUint(host.get_stack_back().balances[origin])
                + TTMathUint256((int)(result.gas_left + result.gas_refund)) * TTMathUint256(GAS_PRICE));

            ret.Code = EVMCErrorCodeTORVMErrorCode(result.status_code);

            return ret;
        }
        else
        {
            ret.Code = rvm::InvokeErrorCode::InvalidFunctionArgments;
            return ret;
        }
	}
	rvm::InvokeResult EVMExecutionEngine::Deploy(rvm::ExecutionContext* exec, uint32_t gas_limit, rvm::CompiledModules* linked, const rvm::ConstData* deploy_args, rvm::ContractModuleID* contract_deployment_ids, rvm::InterfaceModuleID** interface_deployment_ids, rvm::LogMessageOutput* log_msg_output)
	{
		CompiledModules* pCompiledContracts = (CompiledModules*)linked;
		assert(pCompiledContracts->IsLinked());

		uint32_t numContracts = linked->GetCount();
		std::vector<rvm::ContractId> ids(numContracts);
		for (uint32_t i = 0; i < numContracts; i++)
		{
			const ContractCompileData* pCompiledData = pCompiledContracts->GetCompiledData(i);
			ids[i] = _details::GetOnChainContractIdFromContractFullName(exec, pCompiledData->dapp + "." + pCompiledData->name);
			if (ids[i] == rvm::ContractIdInvalid)
				return { 0, 0, rvm::InvokeErrorCode::ContractUnavailable, 0 };
		}

        EVMHost host(*this, *exec);

        rvm::InvokeResult ret;
        ret.SubCodeHigh = 0;
        ret.SubCodeLow = 0;
        ret.GasBurnt = rvm::RVM_GAS_BURNT_DEFAULT;
        ret.Code = rvm::InvokeErrorCode::Success;


        evmc::address origin = host.get_tx_context().tx_origin;
        evmc::uint256be current_balance = host.get_balance(origin);

        if (EVMCUintToTTMathUint(current_balance) < TTMathUint256(gas_limit) * TTMathUint256(GAS_PRICE)) {
            if (current_balance == evmc::uint256be(0)) {
                // FIXME remove this after support normal mint
                current_balance = host.get_stack_back().balances[origin] = TTMathUintToEVMCUint(
                    TTMathUint256(gas_limit) * TTMathUint256(GAS_PRICE));
            }
            else {
                ret.Code = rvm::InvokeErrorCode::InsufficientGasRequired;
                return ret;
            }
        }
        uint32_t count = pCompiledContracts->GetCount();
        uint64_t gas_left = gas_limit;

        std::vector<evmc::address> addresses(count);
        {
            EVMHost::StackScope ss(host);
            bool success = true;

            for (uint32_t i = 0; i < count; i++)
            {
                evmc_message msg{};

                msg.kind = EVMC_CREATE;
                msg.gas = gas_left;
                msg.sender = origin;
                rt::String_Ref callcode = pCompiledContracts->GetBytecode(i);
                rt::String_Ref initdata = pCompiledContracts->GetInitData(i);
                std::vector<uint8_t> data(callcode.GetLength() + initdata.GetLength());
                std::copy(callcode.Begin(), callcode.Begin() + callcode.GetLength(), &data[0]);
                if (!initdata.IsEmpty())
                {
                    std::copy(initdata.Begin(), initdata.Begin() + initdata.GetLength(), &data[callcode.GetLength()]);
                }
                msg.input_data = data.data();
                msg.input_size = data.size();
                msg.value = evmc::uint256be(0); // TODO support pass value when create
                evmc::Result result = RunCreate(host, msg);

                gas_left = result.gas_left + result.gas_refund;
                if (result.status_code != EVMC_SUCCESS)
                {
                    success = false;
                    ret.Code = rvm::InvokeErrorCode::ContractUnavailable;
                    break;
                }

                addresses[i] = result.create_address;
            }

            if (!success) {
                ss.NoMerge();
            }
        }

        if (!m_pDB->Deploy(exec, &ids[0], addresses.data(), linked, contract_deployment_ids, interface_deployment_ids, log_msg_output))
        {
            ret.Code = rvm::InvokeErrorCode::ContractUnavailable;
        }

        host.get_stack_back().balances[origin] = TTMathUintToEVMCUint(
            EVMCUintToTTMathUint(host.get_stack_back().balances[origin])
            + TTMathUint256((unsigned int)gas_left) * TTMathUint256(GAS_PRICE));

		return ret;
	}
	void EVMExecutionEngine::Release()
	{
		delete this;
	}

	void EVMExecutionEngine::GetExceptionMessage(uint16_t except, rvm::StringStream* str) const
	{
	}
}

#endif