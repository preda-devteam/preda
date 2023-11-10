#pragma once
#include "common.h"
#include "inttypes.h"
#include <map>
#include <memory>
#include <algorithm>

namespace prlrt {

	template<typename T0, typename T1>
	struct ____map_impl {
		using key_type = T0;
		using element_type = T1;
		using map_type = std::map<key_type, element_type>;
		using index_type = uint32_t;			// depends on vectorType (for ::size_type)

		map_type m;
		uint8_t *mapped_data = nullptr;
		uint8_t *mapped_key_data = nullptr;
		uint8_t *mapped_element_data = nullptr;
		serialize_size_type mapped_element_data_size = 0;
		index_type num_entry_in_mapped_data = 0;
		//index_type num_valid_entry_in_mapped_data = 0;
		mutable std::unordered_map<index_type, element_type> mapped_data_element_cache;
		//std::vector<key_type> mapped_data_key_vector;
		std::map<key_type, index_type> mapped_data_key_to_element_index;

		____map_impl()
		{
			//transpiler should have already prevented this, here just in case.
			if (!key_type::is_fixed_size::value)
				preda_exception::throw_exception("map key type is not of fixed size in " + std::string(__FUNCTION__), prlrt::ExceptionType::InvalidMapKeyType);
			if (!key_type::is_value_type::value)
				preda_exception::throw_exception("map key type is not value type in " + std::string(__FUNCTION__), prlrt::ExceptionType::InvalidMapKeyType);
		}

		index_type length() const
		{
			return index_type(m.size() + mapped_data_key_to_element_index.size());
		}

		const element_type* get_element_internal(const key_type &key) const
		{
			{
				auto itor = mapped_data_key_to_element_index.find(key);
				if (itor != mapped_data_key_to_element_index.end())
				{
					index_type index = itor->second;
					return &get_mapped_element(index);
				}
			}

			{
				// depends on map_type (for .size())
				auto itor = m.find(key);
				if (itor != m.end())
					return &itor->second;
			}

			return nullptr;
		}

		bool has(const key_type &key)
		{
			return get_element_internal(key) != nullptr;
		}

		void erase(const key_type &key)
		{
			if (mapped_data_key_to_element_index.erase(key) == 0)
				m.erase(key);
		}

		element_type& operator[](const key_type &key)
		{
			element_type *ret = const_cast<element_type*>(get_element_internal(key));
			if (ret != nullptr)
				return *ret;

			// TODO: deep copy key if we want to support reference type as key type
			auto res = m.insert(std::make_pair(key, element_type()));
			if (!res.second)
			{
				preda_exception::throw_exception("map insertion failure in " + std::string(__FUNCTION__), prlrt::ExceptionType::MapInsertFailure);
			}

			return res.first->second;
		}

		const element_type& operator[](const key_type &key) const
		{
			const element_type *ret = get_element_internal(key);
			if (ret == nullptr)
				preda_exception::throw_exception("accessing a non-existing key in const map in" + std::string(__FUNCTION__), prlrt::ExceptionType::ConstMapAccessNonExistingKey);

			return *ret;
		}

		element_type& get_mapped_element(const index_type &index) const
		{
			if (element_type::is_fixed_size::value)
				return get_mapped_element_fixed_element_type_size(index);
			else
				return get_mapped_element_non_fixed_element_type_size(index);
		}

		element_type& get_mapped_element_fixed_element_type_size(const index_type &index) const
		{
			uint8_t *element_buffer = mapped_element_data + serialize_size_type(element_type::fixed_size_in_bytes::value * index);
			return *(element_type*)element_buffer;
		}

		element_type& get_mapped_element_non_fixed_element_type_size(const index_type &index) const
		{
			auto itor = mapped_data_element_cache.find(index);
			if (itor != mapped_data_element_cache.end())
				return itor->second;

			serialize_size_type element_buffer_end_offset = ((serialize_size_type*)(mapped_element_data))[index];
			serialize_size_type element_buffer_start_offset = index == 0 ?
				serialize_size_type(num_entry_in_mapped_data * sizeof(serialize_size_type))
				: ((serialize_size_type*)(mapped_element_data))[index - 1];

			if (element_buffer_start_offset > element_buffer_end_offset || element_buffer_end_offset > mapped_element_data_size)
				preda_exception::throw_exception("deserialization error in " + std::string(__FUNCTION__), prlrt::ExceptionType::DeserializationFailure);

			uint8_t *element_buffer_start = mapped_element_data + element_buffer_start_offset;
			serialize_size_type element_size = element_buffer_end_offset - element_buffer_start_offset;

			element_type element;
			if (!element.map_from_serialized_data(element_buffer_start, element_size, false))
				preda_exception::throw_exception("deserialization error in " + std::string(__FUNCTION__), prlrt::ExceptionType::DeserializationFailure);
			if (element_size != 0)
				preda_exception::throw_exception("deserialization error (element buffer not fully consumed) in " + std::string(__FUNCTION__), prlrt::ExceptionType::DeserializationFailure);

			mapped_data_element_cache.insert(std::make_pair(index, element));

			itor = mapped_data_element_cache.find(index);
			return itor->second;
		}


		serialize_size_type get_serialize_size() const
		{
			serialize_size_type ret = 0;
			ret += serialize_size_type(sizeof(index_type));								// number of elements in map
			ret += serialize_size_type(key_type::fixed_size_in_bytes::value * length());				// the keys
			ret += get_serialize_element_block_size();

			return ret;
		}

		serialize_size_type get_serialize_element_block_size() const
		{
			serialize_size_type ret = 0;
			if (element_type::is_fixed_size::value)
			{
				ret += serialize_size_type(element_type::fixed_size_in_bytes::value * length());		// the elements
			}
			else
			{
				ret += serialize_size_type(sizeof(serialize_size_type) * length());				// offset of each element

				// values from the mapped data
				for (auto itor = mapped_data_key_to_element_index.begin(); itor != mapped_data_key_to_element_index.end(); itor++)
					ret += get_mapped_element(itor->second).get_serialize_size();

				// keys from m
				for (auto itor = m.begin(); itor != m.end(); itor++)
					ret += itor->second.get_serialize_size();
			}

			return ret;
		}

		// Theoretically this function could be templated regarding key_type::is_fixed_size::value and element_type::is_fixed_size::value
		// But since it's only called once for each map, let's just use run-time if
		void serialize_out(uint8_t *buffer, bool for_debug) const
		{
			uint8_t *ptr = buffer;
			((index_type*)ptr)[0] = index_type(length());											// length

			uint8_t *key_block_write = buffer + serialize_size_type(sizeof(index_type));
			uint8_t *element_block_start = buffer + serialize_size_type(sizeof(index_type) + length() * key_type::fixed_size_in_bytes::value);
			uint8_t *element_block_write = element_block_start + (element_type::is_fixed_size::value ? 0 : serialize_size_type(sizeof(serialize_size_type) * length()));
			index_type key_element_pair_index = 0;

			auto mapped_data_itor = mapped_data_key_to_element_index.begin();
			auto itor = m.begin();
			while (mapped_data_itor != mapped_data_key_to_element_index.end() || itor != m.end())
			{
				const key_type *pkey0 = nullptr, *pkey1 = nullptr;
				if (mapped_data_itor != mapped_data_key_to_element_index.end())
				{
					pkey0 = &mapped_data_itor->first;
				}

				if (itor != m.end())
				{
					pkey1 = &itor->first;
				}

				const key_type *pkey = nullptr;
				if (!pkey1 || (pkey0 && (*pkey0 < *pkey1)))
				{
					pkey = pkey0;
					mapped_data_itor++;
				}
				else
				{
					pkey = pkey1;
					itor++;
				}
				pkey->serialize_out(key_block_write, for_debug);
				key_block_write += pkey->get_serialize_size();

				serialize_size_type cur_element_size = (*this)[*pkey].get_serialize_size();		// This must be done before serialize_out(), some types (e.g. note) will change data when serializing out
				(*this)[*pkey].serialize_out(element_block_write, for_debug);
				element_block_write += cur_element_size;
				if (!element_type::is_fixed_size::value)
					((serialize_size_type*)element_block_start)[key_element_pair_index] = serialize_size_type(element_block_write - element_block_start);

				key_element_pair_index++;
			}
		}

		bool map_from_serialized_data(uint8_t *&buffer, serialize_size_type &bufferSize, bool bDeep)
		{
			m.clear();
			mapped_data = nullptr;
			mapped_key_data = nullptr;
			mapped_element_data = nullptr;
			num_entry_in_mapped_data = 0;
			index_type num_valid_entry_in_mapped_data = 0;
			mapped_data_element_cache.clear();
			mapped_data_key_to_element_index.clear();

			mapped_data = buffer;
			if (bufferSize < serialize_size_type(sizeof(index_type)))
				return false;
			num_entry_in_mapped_data = ((index_type*)buffer)[0];
			num_valid_entry_in_mapped_data = num_entry_in_mapped_data;
			if (bufferSize < serialize_size_type(sizeof(index_type) + num_valid_entry_in_mapped_data * key_type::fixed_size_in_bytes::value))
				return false;

			mapped_key_data = buffer + serialize_size_type(sizeof(index_type));
			mapped_element_data = buffer + serialize_size_type(sizeof(index_type) + num_valid_entry_in_mapped_data * key_type::fixed_size_in_bytes::value);

			buffer += serialize_size_type(sizeof(index_type) + num_valid_entry_in_mapped_data * key_type::fixed_size_in_bytes::value);
			bufferSize -= serialize_size_type(sizeof(index_type) + num_valid_entry_in_mapped_data * key_type::fixed_size_in_bytes::value);

			serialize_size_type expectedElementDataSize = 0;
			if (element_type::is_fixed_size::value)
			{
				expectedElementDataSize = serialize_size_type(num_valid_entry_in_mapped_data * element_type::fixed_size_in_bytes::value);
			}
			else
			{
				if (bufferSize < serialize_size_type(num_valid_entry_in_mapped_data * sizeof(serialize_size_type)))
					return false;
				expectedElementDataSize = num_valid_entry_in_mapped_data > 0 ? ((serialize_size_type*)buffer)[num_valid_entry_in_mapped_data - 1] : 0;
			}

			if (bufferSize < expectedElementDataSize)
				return false;
			mapped_element_data_size = expectedElementDataSize;
			buffer += expectedElementDataSize;
			bufferSize -= expectedElementDataSize;

			// TODO: Do not de-serialize all the keys when mapping, but on-demand when used.
			uint8_t *read_ptr = mapped_key_data;
			serialize_size_type read_buffer_size = serialize_size_type(num_valid_entry_in_mapped_data * key_type::fixed_size_in_bytes::value);
			for (index_type index = 0; index < num_valid_entry_in_mapped_data; index++)
			{
				key_type key;
				if (!key.map_from_serialized_data(read_ptr, read_buffer_size, bDeep))
					preda_exception::throw_exception("deserialization error in " + std::string(__FUNCTION__), prlrt::ExceptionType::DeserializationFailure);
				mapped_data_key_to_element_index.emplace(key, index);
			}
			if (read_buffer_size != 0)
				preda_exception::throw_exception("deserialization error (key buffer not fully consumed) in " + std::string(__FUNCTION__), prlrt::ExceptionType::DeserializationFailure);

			if (bDeep)
			{
				for (index_type index = 0; index < length(); index++)
					get_mapped_element(index);
			}
			return true;
		}
	};

	template<typename T0, typename T1>
	struct __prlt_map {
		using key_type = T0;
		using value_type = T1;
		using implementation_type = ____map_impl<key_type, value_type>;
		using smartptr_type = std::shared_ptr<implementation_type>;
		using is_value_type = std::false_type;
		using is_fixed_size = std::false_type;
		using fixed_size_in_bytes = std::integral_constant<serialize_size_type, 0>;	// doesn't matter
		using type_identifier_type = ____map_type_identifier<typename key_type::type_identifier_type, typename value_type::type_identifier_type>;
		static constexpr uint32_t get_type_identifier_size()
		{
			return type_identifier_type::value.length();
		}

		static constexpr const uint8_t* get_type_identifier_buffer()
		{
			return type_identifier_type::value.data;
		}

		smartptr_type ptr;
		__prlt_map()
			:ptr(new implementation_type) {}											// always new an empty map here in constructor is a waste, but this could be improved if transpiler ignores unused variables when parsing
		__prlt_map(const smartptr_type &p)
			: ptr(p) {}
		void operator=(const smartptr_type &p)
		{
			ptr = p;
		}
		__prlt_map(const __prlt_map<key_type, value_type> &rhs)
		{
			ptr = rhs.ptr;
		}
		void operator=(const __prlt_map<key_type, value_type> &rhs)
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

		void __prli_erase(const key_type &key) const
		{
			return ptr->erase(key);
		}

		// serialization-related interface
		serialize_size_type get_serialize_size() const
		{
			return ptr->get_serialize_size();
		}

		void serialize_out(uint8_t *buffer, bool for_debug) const
		{
			ptr->serialize_out(buffer, for_debug);
		}

		bool map_from_serialized_data(uint8_t *&buffer, serialize_size_type &bufferSize, bool bDeep)
		{
			return ptr->map_from_serialized_data(buffer, bufferSize, bDeep);
		}
	};

}

template<typename T0, typename T1>
using __prlt_map = prlrt::__prlt_map<T0, T1>;
