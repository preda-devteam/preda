#pragma once
#include "inttypes.h"
#include "scattered_map.h"

namespace prlrt {
	template<typename T>
	struct ____scattered_array_impl : public ____scattered_map_base_linker<__prlt_uint32, T>{
		using base_type 			= ____scattered_map_base_linker<__prlt_uint32, T>;
		using index_type 			= __prlt_uint32;
		using value_type 			= T;
		using size_type 			= typename base_type::size_type;
		using state_type 			= typename base_type::state_type;

		value_type& operator[](index_type index)
		{
			if (index._v < 0 || index._v >= base_type::current_size)
				preda_exception::throw_exception("out of range in " + std::string(__FUNCTION__), prlrt::ExceptionType::OutOfRange);

			burn_gas_traverse_map(base_type::current_size);

			state_type* state = nullptr;
			if(base_type::get_journaled_state(index, state) && !state->second)
				return state->first;

			preda_exception::throw_exception("could not get value from scattered map in" + std::string(__FUNCTION__), prlrt::ExceptionType::ConstMapAccessNonExistingKey);
		}

		const value_type& operator[](index_type index) const
		{
			return const_cast<____scattered_array_impl<T>&>(*this)[index];
		}

		void push(const value_type& value) 
		{
			burn_gas((uint64_t)gas_costs[PRDOP_SCTARR_PUSH]);
			disable_burn_gas();
			base_type::journaled_states[index_type(base_type::current_size++)] = std::make_pair(value, false);
			enable_burn_gas();
		}

		void pop() 
		{
			if (base_type::current_size == 0)
				preda_exception::throw_exception("pop an empty scattered array in " + std::string(__FUNCTION__), prlrt::ExceptionType::PopEmptyArray);

			burn_gas((uint64_t)gas_costs[PRDOP_SCTARR_POP]);
			disable_burn_gas();
			base_type::journaled_states[index_type(--base_type::current_size)] = std::make_pair(value_type(), true);
			enable_burn_gas();
		}

		void set_length(index_type new_size) 
		{ 
			if(new_size._v > base_type::current_size)
			{
				value_type value;
				for(size_type i = base_type::current_size; i < new_size._v; ++i)
					push(value);
			}
			else if(new_size._v < base_type::current_size)
			{
				for(size_type i = new_size._v; i < base_type::current_size; ++i)
					pop();				
			}
			base_type::current_size = new_size._v;
		}
	};

	template<typename T>
	struct __prlt_scattered_array {
		using value_type 					= T;
		using implementation_type 			= ____scattered_array_impl<value_type>;
		using smartptr_type 				= std::shared_ptr<implementation_type>;
		using implementation_base_type		= typename implementation_type::base_type;
		using index_type 					= typename implementation_type::index_type;
		using contract_version_id_type 		= typename implementation_base_type::contract_version_id_type;
		using scope_id_type 				= typename implementation_base_type::scope_id_type;
		using slot_id_type 					= typename implementation_base_type::slot_id_type;

		smartptr_type ptr;

		__prlt_scattered_array(): 
			ptr(new implementation_type) {}

		__prlt_scattered_array(const __prlt_scattered_array<value_type>& rhs): 
			ptr(rhs.ptr) {}

		void link_external_map(contract_version_id_type cvid, scope_id_type scope_id, slot_id_type slot_id) 
		{ 
			ptr->link_external_map(cvid, scope_id, slot_id); 
		}

		void operator=(const __prlt_scattered_array<value_type>& rhs) 
		{
			ptr = rhs.ptr;
		}

		index_type __prli_length() const 
		{ 
			return index_type(ptr->length()); 
		}

		value_type& operator[](index_type index) 
		{ 
			return (*(ptr.get()))[index]; 
		}

		const value_type& operator[](index_type index) const 
		{ 
			return (*((const implementation_type*)ptr.get()))[index]; 
		}

		void __prli_push(const value_type& value) 
		{ 
			ptr->push(value); 
		}

		void __prli_pop() 
		{ 
			ptr->pop(); 
		}

		void __prli_set_length(index_type new_size) 
		{ 
			ptr->set_length(new_size); 
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

template<typename T>
using __prlt_scattered_array = prlrt::__prlt_scattered_array<T>;