#pragma once
#include <map>
#include <array>
#include <vector>
#include "common.h"
#include "inttypes.h"
#include "gascost.h"

namespace prlrt {
	template<typename T0, typename T1>
	struct ____scattered_map_base_linker {
		using key_type 						= T0;
		using value_type 					= T1;
		using state_type 					= std::pair<value_type, bool>;		// bool marks the value being erased
		using journaled_states_type 		= std::map<key_type, state_type>;
		using contract_version_id_type 		= uint64_t;
		using scope_id_type 				= uint8_t;
		using slot_id_type 					= uint8_t;
		using size_type						= uint32_t;

		static constexpr serialize_size_type key_type_sized_value = key_type::fixed_size_in_bytes::value;

		mutable journaled_states_type 		journaled_states;
		contract_version_id_type 			cvid;
		scope_id_type 						scope_id;
		slot_id_type 						slot_id;
		size_type							current_size = 0;
#ifdef __wasm32__
		mutable std::vector<std::vector<uint8_t>>	wasm_state_memory;
#endif

		void link_external_map(contract_version_id_type _cvid, scope_id_type _scope_id, slot_id_type _slot_id)
		{
			cvid = _cvid;
			scope_id = _scope_id;
			slot_id = _slot_id;
		}

		bool get_value_from_external_map(const key_type& key, value_type& value) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_SCTP_GET_UNTOUCHED]);
			bool ret = false;
			serialize_size_type key_data_size = key_type_sized_value;
			std::array<uint8_t, key_type_sized_value> key_data;
			key.serialize_out(key_data.data(), true);

			serialize_size_type value_data_size;
#ifdef __wasm32__
			value_data_size = PREDA_CALL(GetStateSize, cvid, scope_id, slot_id, key_data.data(), key_data_size);
			if(value_data_size)
			{
				auto& buffer = wasm_state_memory.emplace_back(std::vector<uint8_t>(value_data_size));
				uint8_t* value_data = buffer.data();
				const uint8_t* const_value_data = buffer.data();
				if(PREDA_CALL(GetStateData, cvid, scope_id, slot_id, key_data.data(), key_data_size, value_data) && 
					value.map_from_serialized_data(const_value_data, value_data_size, false))
					ret = true;
			}
#else
			const uint8_t* value_data = nullptr;
			if(PREDA_CALL(GetState, cvid, scope_id, slot_id, key_data.data(), key_data_size, value_data, value_data_size) &&
				value.map_from_serialized_data(value_data, value_data_size, false))
				ret = true;
#endif
			return ret;
		}

		bool get_journaled_state(const key_type& key, state_type*& value) const
		{
			disable_burn_gas();
			auto ret = journaled_states.find(key);
			enable_burn_gas();
			if(ret != journaled_states.end()) 
			{
				value = &ret->second;
				return true;
			}

			value_type v;
			if(get_value_from_external_map(key, v))
			{
				disable_burn_gas();
				auto itr = journaled_states.insert(std::make_pair(key, std::make_pair(v, false)));
				enable_burn_gas();
				if (!itr.second)
					preda_exception::throw_exception("scattered map insertion failure in " + std::string(__FUNCTION__), prlrt::ExceptionType::MapInsertFailure);

				value = &itr.first->second;
				return true;
			}
			return false;
		}

		size_type length() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_MAP_OP_SIMPLE]);
			return current_size;
		}

		void commit_journaled_states() const 
		{
			// commit each element
			{
				std::array<uint8_t, key_type_sized_value> key_buffer;
				std::vector<uint8_t> value_buffer;

				for(auto& state : journaled_states)
				{
					serialize_size_type key_data_size = key_type_sized_value;
					state.first.serialize_out(key_buffer.data(), true);

					// erase elements
					if(state.second.second){
						burn_gas((uint64_t)gas_costs[PRDOP_SCTP_COMMIT]);
						PREDA_CALL(SetState, cvid, scope_id, slot_id, key_buffer.data(), key_data_size, nullptr, 0);
						continue;
					}

					serialize_size_type value_data_size = state.second.first.get_serialize_size();
					value_buffer.resize(value_data_size);
					state.second.first.serialize_out(value_buffer.data(), true);

					auto origin_value_size = PREDA_CALL(GetStateSize, cvid, scope_id, slot_id, key_buffer.data(), key_data_size);
					uint64_t gas = value_data_size > origin_value_size ? gas_costs[PRDOP_SCTP_COMMIT] * (value_data_size - origin_value_size) : gas_costs[PRDOP_SCTP_COMMIT];
					burn_gas(gas);

					PREDA_CALL(SetState, cvid, scope_id, slot_id, key_buffer.data(), key_data_size, value_buffer.data(), value_data_size);
				}
			}
		}

		serialize_size_type get_serialize_size() const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_SIZE]);
			return serialize_size_type(sizeof(size_type));
		}

		void serialize_out(uint8_t *buffer, bool for_debug) const
		{
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_OUT_STATIC] + (uint64_t)gas_costs[PRDOP_SERIALIZE_DYNAMIC] * sizeof(size_type));
			*reinterpret_cast<size_type*>(buffer) = current_size;	
		}

		bool map_from_serialized_data(const uint8_t *&buffer, serialize_size_type &bufferSize, bool bDeep = false)
		{
			if (bufferSize < serialize_size_type(sizeof(size_type)))
				return false;
			burn_gas((uint64_t)gas_costs[PRDOP_SERIALIZE_MAP_STATIC] + (uint64_t)gas_costs[PRDOP_SERIALIZE_DYNAMIC] * sizeof(size_type));
			current_size = *reinterpret_cast<const size_type*>(buffer);
			buffer += sizeof(size_type);
			bufferSize -= sizeof(size_type);
			return true;
		}
	};
	template<typename T0, typename T1>
	struct ____scattered_map_impl : public ____scattered_map_base_linker<T0, T1> {
		using base_type 			= ____scattered_map_base_linker<T0, T1>;
		using key_type 				= T0;
		using value_type 			= T1;
		using state_type 			= typename base_type::state_type;

		value_type& operator[](const key_type &key)
		{
			burn_gas_traverse_map(base_type::current_size);

			state_type* state = nullptr;
			if(base_type::get_journaled_state(key, state))
			{
				state->second = false;
				return state->first;
			}

			disable_burn_gas();
			auto itr = base_type::journaled_states.insert(std::make_pair(key, std::make_pair(value_type(), false)));
			++base_type::current_size;
			enable_burn_gas();
			if (!itr.second)
				preda_exception::throw_exception("scattered map insertion failure in " + std::string(__FUNCTION__), prlrt::ExceptionType::MapInsertFailure);
			return itr.first->second.first;
		}

		const value_type& operator[](const key_type &key) const
		{
			burn_gas_traverse_map(base_type::current_size);

			state_type* state = nullptr;
			if(base_type::get_journaled_state(key, state) && !state->second)
				return state->first;

			preda_exception::throw_exception("accessing a non-existing key in const scattered map in" + std::string(__FUNCTION__), prlrt::ExceptionType::ConstMapAccessNonExistingKey);
		}

		bool has(const key_type &key) const
		{
			burn_gas_traverse_map(base_type::current_size);

			state_type* state = nullptr;
			if(base_type::get_journaled_state(key, state) && !state->second)
				return true;

			return false;
		}

		void erase(const key_type &key)
		{
			if(has(key))
			{
				burn_gas((uint64_t)gas_costs[PRDOP_SCTMAP_ERASE]);
				disable_burn_gas();
				base_type::journaled_states[key] = std::make_pair(value_type(), true);
				enable_burn_gas();
				--base_type::current_size;
			}
		}

	};

	template<typename T0, typename T1>
	struct __prlt_scattered_map {
		using key_type 						= T0;
		using value_type 					= T1;
		using implementation_type 			= ____scattered_map_impl<key_type, value_type>;
		using smartptr_type 				= std::shared_ptr<implementation_type>;
		using implementation_base_type		= typename implementation_type::base_type;
		using contract_version_id_type 		= typename implementation_base_type::contract_version_id_type;
		using scope_id_type 				= typename implementation_base_type::scope_id_type;
		using slot_id_type 					= typename implementation_base_type::slot_id_type;

		smartptr_type ptr;

		__prlt_scattered_map(): 
			ptr(new implementation_type) {}

		__prlt_scattered_map(const __prlt_scattered_map<key_type, value_type>& rhs): 
			ptr(rhs.ptr) {}

		void link_external_map(contract_version_id_type cvid, scope_id_type scope_id, slot_id_type slot_id) 
		{
			ptr->link_external_map(cvid, scope_id, slot_id);
		}

		void operator=(const __prlt_scattered_map<key_type, value_type>& rhs) 
		{
			ptr = rhs.ptr;
		}

		value_type& operator[](const key_type &key) 
		{
			return (*(ptr.get()))[key];
		}

		const value_type& operator[](const key_type &key) const 
		{
			return (*((const implementation_type*)ptr.get()))[key];
		}

		__prlt_bool __prli_has(const key_type &key) const 
		{
			return __prlt_bool(ptr->has(key));
		}

		void __prli_erase(const key_type &key) 
		{
			ptr->erase(key);
		}

		void commit_journaled_states() const 
		{
			ptr->commit_journaled_states();
		}

		serialize_size_type get_serialize_size() const 
		{
			return ptr->get_serialize_size();
		}

		void serialize_out(uint8_t *buffer, bool for_debug) const 
		{
			return ptr->serialize_out(buffer, for_debug);
		}

		bool map_from_serialized_data(const uint8_t *&buffer, serialize_size_type &bufferSize, bool bDeep = false) 
		{
			return ptr->map_from_serialized_data(buffer, bufferSize, bDeep);
		}

	};
}

template<typename T0, typename T1>
using __prlt_scattered_map = prlrt::__prlt_scattered_map<T0, T1>;