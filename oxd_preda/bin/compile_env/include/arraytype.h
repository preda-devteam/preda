#pragma once
#include "common.h"
#include "inttypes.h"
#include <vector>
#include <memory>
#include <unordered_map>

namespace prlrt {

	template<typename T>
	struct ____array_impl {
		using element_type = T;
		using vector_type = std::vector<element_type>;
		using index_type = uint32_t;			// depends on vectorType (for ::size_type)

		vector_type v;
		uint8_t *mapped_data = nullptr;
		serialize_size_type mapped_data_size = 0;
		index_type num_entry_in_mapped_data = 0;
		index_type num_valid_entry_in_mapped_data = 0;				// This could be less than the number of mapped elements, since the array coule be pop()-ed after mapping
		mutable std::unordered_map<index_type, element_type> mapped_data_element_cache;

		index_type length() const
		{
			return index_type(v.size()) + num_valid_entry_in_mapped_data;			// depends on vectorType (for .size())
		}

		element_type& operator[](const index_type &index)
		{
			if (index < index_type(0) || index >= length())
			{
				preda_exception::throw_exception("out of range in " + std::string(__FUNCTION__), prlrt::ExceptionType::OutOfRange);
			}
			if (index >= num_valid_entry_in_mapped_data)
				return v[index - num_valid_entry_in_mapped_data];	// depends on both vectorType (for .get()) and vectorType (for [])
			else
				return get_mapped_element(index);
		}

		const element_type& operator[](const index_type &index) const
		{
			if (index < index_type(0) || index >= length())
			{
				preda_exception::throw_exception("out of range in " + std::string(__FUNCTION__), prlrt::ExceptionType::OutOfRange);
			}
			if (index >= num_valid_entry_in_mapped_data)
				return v[index - num_valid_entry_in_mapped_data];	// depends on both vectorType (for .get()) and vectorType (for [])
			else
				return get_mapped_element(index);
		}

		element_type& get_mapped_element(const index_type &index) const
		{
			if (element_type::is_fixed_size::value)
				return get_mapped_element_fixed_element_size(index);
			else
				return get_mapped_element_non_fixed_element_size(index);
		}

		element_type& get_mapped_element_fixed_element_size(const index_type &index) const
		{
			uint8_t *element_buffer = mapped_data + serialize_size_type(sizeof(index_type)) + serialize_size_type(element_type::fixed_size_in_bytes::value * index);
			return *(element_type*)element_buffer;
		}

		element_type& get_mapped_element_non_fixed_element_size(const index_type &index) const
		{
			auto itor = mapped_data_element_cache.find(index);
			if (itor != mapped_data_element_cache.end())
				return itor->second;

			serialize_size_type element_buffer_end_offset = ((serialize_size_type*)(mapped_data + serialize_size_type(sizeof(index_type))))[index];
			serialize_size_type element_buffer_start_offset = index == 0 ?
				serialize_size_type(num_entry_in_mapped_data * sizeof(serialize_size_type))
				: ((serialize_size_type*)(mapped_data + serialize_size_type(sizeof(index_type))))[index - 1];

			if (element_buffer_start_offset > element_buffer_end_offset || element_buffer_end_offset > mapped_data_size)
				preda_exception::throw_exception("deserialization error in " + std::string(__FUNCTION__), prlrt::ExceptionType::DeserializationFailure);

			uint8_t *element_buffer_start = mapped_data + serialize_size_type(sizeof(index_type)) + element_buffer_start_offset;
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

		void set_length(const index_type &new_size)
		{
			if (new_size >= num_entry_in_mapped_data)
				v.resize(new_size - num_entry_in_mapped_data);
			else
				num_entry_in_mapped_data = new_size;
		}

		void push(const T& value)
		{
			v.push_back(value);	// depends on vectorType (for .push_back())
		}

		void pop()
		{
			if (length() == index_type(0))
			{
				preda_exception::throw_exception("pop an empty array in " + std::string(__FUNCTION__), prlrt::ExceptionType::PopEmptyArray);
			}

			if (v.size() > 0)
				v.pop_back();		// depends on vectorType (for .pop_back())
			else
				num_valid_entry_in_mapped_data--;
		}

		serialize_size_type get_serialize_size() const
		{
			if (element_type::is_fixed_size::value)
				return get_serialize_size_fixed_element_size();
			else
				return get_serialize_size_non_fixed_element_size();
		}

		serialize_size_type get_serialize_size_fixed_element_size() const
		{
			serialize_size_type ret = 0;
			ret += serialize_size_type(sizeof(index_type));				// number of elements in array
			ret += serialize_size_type(element_type::fixed_size_in_bytes::value * length());		// the elements
			return ret;
		}

		serialize_size_type get_serialize_size_non_fixed_element_size() const
		{
			serialize_size_type ret = 0;
			ret += serialize_size_type(sizeof(index_type));				// number of elements in array
			ret += serialize_size_type(sizeof(serialize_size_type) * length());		// offset of each element
			for (index_type i = 0; i < length(); i++)
				ret += serialize_size_type((*this)[i].get_serialize_size());		// add the size of each element
			return ret;
		}

		void serialize_out(uint8_t *buffer, bool for_debug) const
		{
			if (element_type::is_fixed_size::value)
				return serialize_out_fixed_element_size(buffer, for_debug);
			else
				return serialize_out_non_fixed_element_size(buffer, for_debug);
		}

		void serialize_out_fixed_element_size(uint8_t *buffer, bool for_debug) const
		{
			uint8_t *ptr = buffer;

			// length
			*((index_type*)ptr) = index_type(length());
			ptr += sizeof(index_type);

			// data
			if (num_valid_entry_in_mapped_data > 0)
			{
				memcpy(ptr, mapped_data + sizeof(index_type), element_type::fixed_size_in_bytes::value * num_valid_entry_in_mapped_data);
				ptr += element_type::fixed_size_in_bytes::value * num_valid_entry_in_mapped_data;
			}
			if (v.size())
			{
				memcpy(ptr, &v[0], element_type::fixed_size_in_bytes::value * v.size());
				ptr += element_type::fixed_size_in_bytes::value * v.size();
			}
		}

		void serialize_out_non_fixed_element_size(uint8_t *buffer, bool for_debug) const
		{
			uint8_t *ptr = buffer;

			// length
			*((index_type*)ptr) = index_type(length());
			ptr += sizeof(index_type);

			serialize_size_type header_size = serialize_size_type(ptr - buffer);

			// offsets
			serialize_size_type elementStorageOffset = serialize_size_type(sizeof(serialize_size_type) * length());		// elements storage begins after header and array of offsets
			for (index_type i = 0; i < length(); i++)
			{
				serialize_size_type cur_element_size = (*this)[i].get_serialize_size();		// This must be done before serialize_out(), some types (e.g. note) will change data when serializing out
				//data
				(*this)[i].serialize_out(buffer + header_size + elementStorageOffset, for_debug);
				//offset
				elementStorageOffset += cur_element_size;
				*((serialize_size_type*)ptr) = elementStorageOffset;
				ptr += sizeof(serialize_size_type);
			}
		}

		bool map_from_serialized_data(uint8_t *&buffer, serialize_size_type &bufferSize, bool bDeep)
		{
			v.clear();
			mapped_data = nullptr;
			num_entry_in_mapped_data = 0;
			num_valid_entry_in_mapped_data = 0;
			mapped_data_element_cache.clear();

			if (bufferSize < serialize_size_type(sizeof(index_type)))
				return false;

			mapped_data = buffer;
			num_entry_in_mapped_data = *((index_type*)buffer);
			num_valid_entry_in_mapped_data = num_entry_in_mapped_data;

			serialize_size_type expectedSize = 0;
			if (element_type::is_fixed_size::value)
			{
				expectedSize = serialize_size_type(sizeof(index_type) + num_valid_entry_in_mapped_data * element_type::fixed_size_in_bytes::value);
			}
			else
			{
				if (bufferSize < serialize_size_type(sizeof(index_type) + num_valid_entry_in_mapped_data * sizeof(serialize_size_type)))
					return false;
				expectedSize = num_valid_entry_in_mapped_data > 0 ? ((serialize_size_type*)(mapped_data + serialize_size_type(sizeof(index_type))))[num_valid_entry_in_mapped_data - 1] + sizeof(index_type) : sizeof(index_type);
			}

			if (bufferSize < expectedSize)
				return false;

			mapped_data_size = expectedSize;

			buffer += expectedSize;
			bufferSize -= expectedSize;

			if (bDeep)
			{
				for (index_type index = 0; index < length(); index++)
					get_mapped_element(index);
			}
			return true;
		}
	};

	template<typename T>
	struct __prlt_array {
		using element_type = T;
		using implementation_type = ____array_impl<element_type>;
		using smartptr_type = std::shared_ptr<implementation_type>;
		using internal_index_type = typename implementation_type::index_type;	// depends on vectorType (for ::size_type)
		using external_index_type = __prlt_uint32;									// according to Preda spec
		using is_value_type = std::false_type;
		using is_fixed_size = std::false_type;
		using fixed_size_in_bytes = std::integral_constant<serialize_size_type, 0>;		// doesn't matter
		using type_identifier_type = ____array_type_identifier<typename element_type::type_identifier_type>;
		static constexpr uint32_t get_type_identifier_size()
		{
			return type_identifier_type::value.length();
		}
		static constexpr const uint8_t* get_type_identifier_buffer()
		{
			return type_identifier_type::value.data;
		}

		smartptr_type ptr;
		__prlt_array()
			:ptr(new implementation_type) {}											// always new an empty vector here in constructor is a waste, but this could be improved if transpiler ignores unused variables when parsing
		__prlt_array(const smartptr_type &p)
			: ptr(p) {}
		void operator=(const smartptr_type &p)
		{
			ptr = p;
		}
		__prlt_array(const __prlt_array<T> &rhs)
		{
			ptr = rhs.ptr;
		}
		void operator=(const __prlt_array<T> &rhs)
		{
			ptr = rhs.ptr;
		}

		// array interface
		external_index_type __prli_length() const
		{
			return external_index_type(external_index_type::internal_type(ptr->length()));
		}

		element_type& operator[](const external_index_type &index)
		{
			internal_index_type indexInternal = internal_index_type(index._v);
			return (*(ptr.get()))[indexInternal];
		}

		const element_type& operator[](const external_index_type &index) const
		{
			internal_index_type indexInternal = internal_index_type(index._v);
			return (*((const implementation_type*)ptr.get()))[indexInternal];
		}

		void __prli_push(const T& value)
		{
			ptr->push(value);
		}

		void __prli_pop()
		{
			ptr->pop();
		}

		void __prli_set_length(const external_index_type& new_size)
		{
			ptr->set_length(internal_index_type(new_size._v));
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

template<typename T>
using __prlt_array = prlrt::__prlt_array<T>;