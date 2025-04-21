#include "EVMExecutionEngine.h"
#include <iostream>
#include <vector>
#include <array>

#include <evmone/evmone.h>
#include "EVMContractDataBase.h"

#include "../../../oxd_libsec/oxd_libsec.h"

#ifdef ENABLE_EVM

namespace xtl {

    static evmc::bytes32 RVMHashToEVMHash(const rvm::HashValue& hash)
    {
        evmc::bytes32 ret;
        static_assert(sizeof(hash) == sizeof(ret), "hash size match");
        std::copy(&hash._[0], &hash._[0] + sizeof(ret), ret.bytes);
        return ret;
    }

	evmc::bytes32 CrystalityHost::get_original_storage_value(const evmc::address& addr, const evmc::bytes32& key) const noexcept
	{
		evmc::bytes32 ret;
		rvm::ContractId cid = get_original_contract_id(addr);
		if(cid == rvm::ContractIdInvalid)
			return ret;

		rvm::ScopeKey skey{ &key.bytes[0], sizeof(key) };
		rvm::ContractScopeId csid = rvm::CONTRACT_SET_SCOPE(cid, ShardStorageScope);
		rvm::ConstStateData state = m_ctx.GetState(csid, &skey);
		if (state.DataSize == sizeof(ret))
		{
			std::copy(state.DataPtr, state.DataPtr + state.DataSize, ret.bytes);
			return ret;
		}
		
		csid = rvm::CONTRACT_SET_SCOPE(cid, GlobalStorageScope);
		state = m_ctx.GetState(csid, &skey);
		if (state.DataSize == sizeof(ret))
		{
			std::copy(state.DataPtr, state.DataPtr + state.DataSize, ret.bytes);
			return ret;
		}

		return ret;
	}

	evmc::uint256be CrystalityHost::get_original_balance(const evmc::address& addr) const noexcept
	{
		evmc::uint256be ret;

		// rvm::ScopeKey skey{ &addr.bytes[0], sizeof(addr) };
		// auto value = m_ctx.GetState(BalanceCSID, &skey);
		// if (value.DataSize == sizeof(ret))
		//     std::copy(value.DataPtr, value.DataPtr + value.DataSize, ret.bytes);

		return ret;
	}

	evmc::uint256be CrystalityHost::get_original_nonce(const evmc::address& addr) const noexcept
	{
		evmc::uint256be ret;

		// rvm::ScopeKey skey{ &addr.bytes[0], sizeof(addr) };
		// auto value = m_ctx.GetState(NonceCSID, &skey);
		// if (value.DataSize == sizeof(ret))
		//     std::copy(value.DataPtr, value.DataPtr + value.DataSize, ret.bytes);

		return ret;
	}

	const evmc::bytes_view CrystalityHost::get_original_code(const evmc::address& addr) const noexcept
	{
		rvm::ScopeKey skey{ &addr.bytes[0], sizeof(addr) };
		auto value = m_ctx.GetState(CodeCSID, &skey);

		if(value.DataSize)
			m_accounts[addr].code = evmc::bytes_view(value.DataPtr, value.DataSize);

		return evmc::bytes_view(value.DataPtr, value.DataSize);
	}

	evmc::bytes32 CrystalityHost::get_original_hash(const evmc::address& addr) const noexcept
	{
		evmc::bytes32 ret;

		rvm::ScopeKey skey{ &addr.bytes[0], sizeof(addr) };
		auto value = m_ctx.GetState(CodeHashCSID, &skey);
		if (value.DataSize == sizeof(ret))
		{
			std::copy(value.DataPtr, value.DataPtr + value.DataSize, ret.bytes);
			m_accounts[addr].code_hash = ret;
		}

		return ret;
	}

	rvm::ContractId CrystalityHost::get_original_contract_id(const evmc::address& addr) const noexcept
	{
		rvm::ContractId ret = rvm::ContractIdInvalid;

		rvm::ScopeKey skey{ &addr.bytes[0], sizeof(addr) };
		auto value = m_ctx.GetState(ContractIdCSID, &skey);
		if (value.DataSize == sizeof(ret))
			ret = *(rvm::ContractId*)value.DataPtr;

		return ret;
	}

	void CrystalityHost::record_account_access(const evmc::address &addr) const noexcept
	{
		m_access_stack.back().accessed_account.insert(addr);
	}

	bool CrystalityHost::account_accessed(const evmc::address &addr) const noexcept
	{
		return m_access_stack.back().accessed_account.count(addr) != 0;
	}

	void CrystalityHost::push_call_stack() noexcept
	{
		m_access_stack.push_back(AccessedHistory{});
	}

	void CrystalityHost::pop_call_stack() noexcept
	{
		m_access_stack.pop_back();
	}

	CrystalityHost::CrystalityHost(EVMExecutionEngine& engine, rvm::ExecutionContext& ctx):
		m_engine(engine),
		m_ctx(ctx)        
	{
		m_tx_ctx.tx_gas_price = evmc::uint256be(1); // TODO gas
		m_tx_ctx.block_gas_limit = 0xafffffffffffffff;
		m_tx_ctx.block_base_fee = evmc::uint256be(1);

		if(ctx.GetSigner(0))
			m_tx_ctx.tx_origin = _details::RVMAddressToEVMAddress(*ctx.GetSigner(0)) ; // TODO how to translate from evm address to rvm address?
		m_tx_ctx.block_coinbase = _details::RVMAddressToEVMAddress(*ctx.GetBlockCreator());

		m_tx_ctx.block_number = ctx.GetBlockHeight();
		ctx.Randomize(m_tx_ctx.block_prev_randao.bytes, sizeof(evmc::uint256be));
		m_tx_ctx.chain_id = evmc::uint256be({ 'p', 'r', 'e', 'd', 'a' });

		m_shard_order = evmc::bytes32(m_ctx.GetShardOrder());
	}

	int CrystalityHost::commit_state()
	{
		for(auto& it : m_accounts)
		{
			const evmc::address& addr = it.first;
			const Account& account = it.second;
			rvm::ContractId cid = get_original_contract_id(addr);
			
			rvm::ContractInvokeId ciid = rvm::CONTRACT_SET_SCOPE_BUILD(cid, m_ctx.GetShardIndex() == rvm::GlobalShard? GlobalStorageScope : ShardStorageScope, rvm::BuildNumInit);
			if(cid == rvm::ContractIdInvalid)
				return -1;
			
			for(const auto& kv : account.storage)
			{
				rvm::ScopeKey skey{kv.first.bytes, sizeof(evmc::bytes32)};
				uint8_t* state = m_ctx.AllocateStateMemory(sizeof(evmc::bytes32));
				std::copy(std::begin(kv.second.bytes), std::end(kv.second.bytes), state);
				m_ctx.CommitNewState(ciid, &skey, state);
			}
		}
		return 0;
	}

	bool CrystalityHost::transfer(const evmc::address& from, const evmc::address& to, const evmc::uint256be& value_evm)
	{
		// TTMathUint256 from_balance = EVMCUintToTTMathUint(get_balance(from));
		// TTMathUint256 value = EVMCUintToTTMathUint(value_evm);
		// if (from_balance < value)
		//     return false;

		// from_balance -= value;
		// TTMathUint256 to_balance = EVMCUintToTTMathUint(get_balance(to));
		// to_balance += value;
		// m_accounts[from].balance = TTMathUintToEVMCUint(from_balance);
		// m_accounts[to].balance = TTMathUintToEVMCUint(to_balance);
		 return true;
	}

	evmc::uint256be CrystalityHost::get_nonce(const evmc::address& addr) const noexcept
	{
		// record_account_access(addr);

		// auto it = m_accounts.find(addr);
		// if (it != m_accounts.end())
		// 	return it->second.nonce;

		// return get_original_nonce(addr);
		return evmc::uint256be{};
	}

	bool CrystalityHost::account_exists(const evmc::address& addr) const noexcept
	{
		auto it = m_accounts.find(addr);
		if (it != m_accounts.end())
			return true;

		return false;
	}

	evmc::bytes32 CrystalityHost::get_storage(const evmc::address& addr, const evmc::bytes32& key) const noexcept
	{
		record_account_access(addr);

		auto it = m_accounts.find(addr);
		if(it != m_accounts.end())
		{
			const auto& storage_it = it->second.storage.find(key);
			if(storage_it != it->second.storage.end())
				return storage_it->second;
		}

		return get_original_storage_value(addr, key);
	}

	evmc_storage_status CrystalityHost::set_storage(const evmc::address& addr, const evmc::bytes32& key, const evmc::bytes32& value) noexcept
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

		m_accounts[addr].storage[key] = value; // Finally update the current storage value.
		return status;
	}

	evmc::uint256be CrystalityHost::get_balance(const evmc::address& addr) const noexcept
	{
		// record_account_access(addr);
		
		// auto it = m_accounts.find(addr);
		// if (it != m_accounts.end())
		// 	return it->second.balance;

		// return get_original_balance(addr);
		return evmc::uint256be(0);
	}

	size_t CrystalityHost::get_code_size(const evmc::address& addr) const noexcept
	{
		record_account_access(addr);

		auto it = m_accounts.find(addr);
		if (it != m_accounts.end())
			return it->second.code.size();

		return get_original_code(addr).size();
	}

	evmc::bytes32 CrystalityHost::get_code_hash(const evmc::address& addr) const noexcept
	{
		record_account_access(addr);

		auto it = m_accounts.find(addr);
		if (it != m_accounts.end())
			return it->second.code_hash;

		return get_original_hash(addr);
	}

	evmc::bytes_view CrystalityHost::get_code(const evmc::address& addr) const noexcept
	{
		record_account_access(addr);

		auto it = m_accounts.find(addr);
		if (it != m_accounts.end())
			return it->second.code;

		return get_original_code(addr);
	}

	size_t CrystalityHost::copy_code(const evmc::address& addr, size_t code_offset, uint8_t* buffer_data, size_t buffer_size) const noexcept
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

	bool CrystalityHost::selfdestruct(const evmc::address& addr, const evmc::address& beneficiary) noexcept
	{
		// TODO support selfdestruct
		return true;
	}

	evmc::Result CrystalityHost::call(const evmc_message& msg) noexcept
	{
		evmc::Result ret{EVMC_SUCCESS, msg.gas, 0, nullptr, 0};

		rvm::ContractId cid = get_original_contract_id(msg.sender);
		if(cid == rvm::ContractIdInvalid)
		{
			ret.status_code = EVMC_FAILURE;
			return ret;
		}
		rvm::ContractVersionId cvid = rvm::CONTRACT_SET_BUILD(cid, rvm::BuildNumInit);
		rvm::OpCode op = rvm::OpCodeInvalid;
		uint32_t gas_redistribution_weight = 1;
		rvm::ConstData args{msg.input_data, (uint32_t)msg.input_size};

		if (evmc::address(555) == evmc::address(msg.code_address)) 
		{
			ret.output_data = m_shard_order.bytes;
			ret.output_size = 32;
		}
		else if(evmc::address(666) == evmc::address(msg.code_address))
		{
			rvm::Address scope_target;
			std::copy(msg.input_data + 16, msg.input_data + 36, scope_target._);
			rvm::ScopeKey skey { (const uint8_t*)&scope_target, sizeof(rvm::Address) };
			m_ctx.EmitRelayToScope(rvm::CONTRACT_SET_SCOPE(cvid, rvm::Scope::Address), &skey, op, &args, gas_redistribution_weight);
		}
		else if(evmc::address(777) == evmc::address(msg.code_address))
		{
			m_ctx.EmitBroadcastToShards(rvm::CONTRACT_SET_SCOPE(cvid, rvm::Scope::Shard), op, &args, gas_redistribution_weight);
		}
		else if(evmc::address(888) == evmc::address(msg.code_address))
		{
			m_ctx.EmitRelayToGlobal(rvm::CONTRACT_SET_SCOPE(cvid, rvm::Scope::Global), op, &args, gas_redistribution_weight);
		}
		else if(evmc::address(32) == evmc::address(msg.code_address))
		{
			uint32_t scope_target = evmc::load32be(msg.input_data + 32);
			rvm::ScopeKey skey { (const uint8_t*)&scope_target, sizeof(uint32_t) };
			m_ctx.EmitRelayToScope(rvm::CONTRACT_SET_SCOPE(cvid, rvm::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySized::UInt32, 0)), &skey, op, &args, gas_redistribution_weight);
		}
		 /// TODO: deploy unnamed contract
		 //else if (msg.kind == EVMC_CREATE || msg.kind == EVMC_CREATE2)
		 //{
		 //    return m_engine.evm_create(*this, msg);
		 //}
		 /// TODO: contract call
		 //else
		 //    return m_engine.evm_execute(*this, msg);
		return ret;
	}

	evmc_tx_context CrystalityHost::get_tx_context() const noexcept
	{ 
		return m_tx_ctx; 
	}

	evmc::bytes32 CrystalityHost::get_block_hash(int64_t block_number) const noexcept
	{
		ASSERT(0);  // not supportted in dioxide 
		auto* hash = m_ctx.GetPrevBlockHash();
		return RVMHashToEVMHash(*hash);
	}

	void CrystalityHost::emit_log(const evmc::address& addr, const uint8_t* data, size_t data_size, const evmc::bytes32 topics[], size_t topics_count) noexcept
	{
		rvm::ContractId cid = get_original_contract_id(addr);
		if(cid == rvm::ContractIdInvalid)
		{
			_LOG("[EMIT LOG]: Can't find contract with addrees: "<< evmc::hex(addr.bytes));
			return;
		}
		_LOG("[EMIT LOG]:\n" << m_engine.emit_log(cid, topics[0], evmc::bytes_view(data, data_size)));
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
	evmc_access_status CrystalityHost::access_account(const evmc::address& addr) noexcept
	{
		using namespace evmc::literals;

		// Accessing precompiled contracts is always warm.
		if (addr >= 0x0000000000000000000000000000000000000001_address &&
			addr <= 0x0000000000000000000000000000000000000009_address)
			return EVMC_ACCESS_WARM;

		// Check if the address have been already accessed.
		if (m_access_stack.back().accessed_account.count(addr) > 0)
		{
			record_account_access(addr);
			return EVMC_ACCESS_WARM;
		}

		return EVMC_ACCESS_COLD;
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
	evmc_access_status CrystalityHost::access_storage(const evmc::address& addr, const evmc::bytes32& key) noexcept
	{
		if (m_access_stack.back().accessed_storage_slots.count(key) > 0)
		{
			record_account_access(addr);
			return EVMC_ACCESS_WARM;
		}

		return EVMC_ACCESS_COLD;
	}

    evmc::Result EVMExecutionEngine::evm_create(CrystalityHost& host, const evmc_message& msg)
    {
        ASSERT(msg.kind == EVMC_CREATE || msg.kind == EVMC_CREATE2);

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
            return evmc::Result(EVMC_FAILURE);

        evmc_message new_msg = msg;
        new_msg.recipient = addr;
        if (!host.transfer(new_msg.sender, addr, msg.value))
            return evmc::Result(EVMC_INSUFFICIENT_BALANCE);

		host.push_call_stack();
        evmc::Result ret = m_vm.execute(host, EVMC_LONDON, new_msg, new_msg.input_data, new_msg.input_size);
		host.pop_call_stack();

        if (ret.status_code != EVMC_SUCCESS)
            return ret;

        if (ret.output_size * CREATE_STORE_GAS > (uint64_t)ret.gas_left)
            return evmc::Result(EVMC_OUT_OF_GAS);

        ret.gas_left -= ret.output_size * CREATE_STORE_GAS;
        ret.create_address = addr;

        return ret;
    }

    evmc::Result EVMExecutionEngine::evm_execute(CrystalityHost& host, const evmc_message& msg)
    {
        ASSERT(msg.kind != EVMC_CREATE && msg.kind != EVMC_CREATE2);

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
                return evmc::Result(EVMC_INSUFFICIENT_BALANCE);
        }

        evmc::bytes_view code = host.get_code(msg.code_address);
        if (code.empty()) {
            return evmc::Result(EVMC_FAILURE, msg.gas);
        }

		host.push_call_stack();
        evmc::Result ret = m_vm.execute(host, EVMC_LONDON, msg, code.data(), code.size());
		host.pop_call_stack();

        if (ret.status_code != EVMC_SUCCESS)
            return ret;

        return ret;
    }

	std::string EVMExecutionEngine::emit_log(rvm::ContractId cid, evmc::bytes32 event_sig, evmc::bytes_view event_data)
	{
		std::string ret;
		auto p_entry = m_pDB->FindContractEntry(cid);
		if(!p_entry || 0 != p_entry->DecodeEventArguments(event_sig, event_data, ret))
			return std::string();
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

    rvm::InvokeResult EVMExecutionEngine::Invoke(rvm::ExecutionContext* executionContext, uint32_t gas_limit, rvm::ContractInvokeId contract, rvm::OpCode opCode, const rvm::ConstData* args_serialized)
	{
        rvm::InvokeResult ret{0, 0, rvm::InvokeErrorCode::Success, 0, nullptr};

		rvm::ContractId cid = rvm::CONTRACT_UNSET_SCOPE_BUILD(contract);
        const ContractDatabaseEntry* entry = m_pDB->FindContractEntry(cid);

        if (!entry)
        {
            ret.Code = rvm::InvokeErrorCode::ContractUnavailable;
            return ret;
        }

        CrystalityHost host(*this, *executionContext);

		evmc_message msg{};
		msg.kind = EVMC_CALL;
		msg.gas = gas_limit;
		msg.sender = host.get_tx_context().tx_origin;
		msg.input_data = args_serialized->DataPtr;
		msg.input_size = args_serialized->DataSize;
		msg.value = evmc::uint256be(0);
		msg.recipient = entry->address;
		msg.code_address = entry->address;
		host.push_call_stack();
		evmc::Result result = evm_execute(host, msg);
		host.pop_call_stack();

		ret.Code = EVMCErrorCodeTORVMErrorCode(result.status_code);
		ret.GasBurnt = (uint32_t)(gas_limit - result.gas_left);

		if(result.status_code == EVMC_SUCCESS)
		{
			if(0 != host.commit_state())
				ret.Code = rvm::InvokeErrorCode::SaveStateFailure;
		}	

		return ret;
	}

	bool EVMExecutionEngine::DeployContracts(rvm::ExecutionContext* exec, rvm::CompiledModules* linked, const rvm::ContractVersionId* target_cvids, rvm::DataBuffer** deploy_stub, rvm::LogMessageOutput* log_msg_output)
	{
		return true;
	}
	
	rvm::InvokeResult EVMExecutionEngine::InitializeContracts(rvm::ExecutionContext* exec, uint32_t gas_limit, rvm::CompiledModules* linked, const rvm::ConstData* ctor_args)
	{
		CompiledModules* pCompiledContracts = (CompiledModules*)linked;
        CrystalityHost host(*this, *exec);
        rvm::InvokeResult ret{0, 0, rvm::InvokeErrorCode::Success, 0, nullptr};
        evmc::address origin = host.get_tx_context().tx_origin;
        uint32_t count = pCompiledContracts->GetCount();
        uint64_t gas_left = gas_limit;

        std::vector<evmc::address> addresses(count);
        std::vector<evmc::bytes32> code_hashes(count);
        std::vector<evmc::bytes> codes(count);
		std::vector<rvm::ContractId> cids(count);
        bool success = true;
		for (uint32_t i = 0; i < count; i++)
		{
			evmc_message msg{};
			msg.kind = EVMC_CREATE;
			msg.gas = gas_left;
			msg.sender = origin;
			msg.value = evmc::uint256be(0); // TODO support pass value when create
			rt::String_Ref callcode = pCompiledContracts->GetBytecode(i);
			std::vector<uint8_t> data(callcode.GetLength() + ctor_args->DataSize);
			std::copy(callcode.Begin(), callcode.Begin() + callcode.GetLength(), &data[0]);
			if (ctor_args->DataSize)
				std::copy(ctor_args->DataPtr, ctor_args->DataPtr + ctor_args->DataSize, &data[callcode.GetLength()]);
			msg.input_data = data.data();
			msg.input_size = data.size();

			evmc::Result result = evm_create(host, msg);
			gas_left = result.gas_left + result.gas_refund;
			if (result.status_code != EVMC_SUCCESS)
			{
				success = false;
				ret.Code = rvm::InvokeErrorCode::ContractUnavailable;
				break;
			}

			{
				const ContractCompileData* pCompiledData = pCompiledContracts->GetCompiledData(i);
				rvm::ContractId contractId = rvm::CONTRACT_UNSET_BUILD(::_details::GetOnChainContractIdFromContractFullName(exec, pCompiledData->dapp + "." + pCompiledData->name));
				if (contractId == rvm::ContractIdInvalid)
				{
					success = false;
					ret.Code = rvm::InvokeErrorCode::ContractUnavailable;
					break;
				}
				cids[i] = contractId;
				evmc::bytes32 code_hash;
				oxd::SecuritySuite::Hash(result.output_data, (uint32_t)result.output_size, code_hash.bytes);
				code_hashes[i] = code_hash;
				codes[i] = evmc::bytes(result.output_data, result.output_size);
				addresses[i] = result.create_address;
			}
		}

		if(!success)
			return ret;

		if (!m_pDB->Deploy(exec, linked, addresses.data(), cids.data()))
		{
            ret.Code = rvm::InvokeErrorCode::ContractUnavailable;
			return ret;
		}

		// commit code, code hash and cid
		for(uint32_t i = 0; i < count; ++i)
		{
			rvm::ScopeKey skey{addresses[i].bytes, sizeof(evmc::address)};

			uint8_t* code_data = exec->AllocateStateMemory((uint32_t)codes[i].size());
			std::copy(codes[i].begin(), codes[i].end(), code_data);
			exec->CommitNewState(rvm::CONTRACT_SET_BUILD(CrystalityHost::CodeCSID, rvm::BuildNumInit), &skey, code_data);

			uint8_t* code_hash_data = exec->AllocateStateMemory(sizeof(evmc::bytes32));
			std::copy(std::begin(code_hashes[i].bytes), std::end(code_hashes[i].bytes), code_hash_data);
			exec->CommitNewState(rvm::CONTRACT_SET_BUILD(CrystalityHost::CodeHashCSID, rvm::BuildNumInit), &skey, code_hash_data);

			uint8_t* cid_data = exec->AllocateStateMemory(sizeof(rvm::ContractId));
			memcpy(cid_data, &cids[i], sizeof(rvm::ContractId));
			exec->CommitNewState(rvm::CONTRACT_SET_BUILD(CrystalityHost::ContractIdCSID, rvm::BuildNumInit), &skey, cid_data);
		}

		if(0 != host.commit_state())
			ret.Code = rvm::InvokeErrorCode::SaveStateFailure;

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