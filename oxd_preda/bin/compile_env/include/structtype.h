#pragma once

namespace prlrt {

	template<typename T_Struct>
	struct struct_wrapper {
		using implementation_type = T_Struct;
		using smartptr_type = std::shared_ptr<implementation_type>;
		using is_value_type = std::false_type;
		using is_fixed_size = std::false_type;
		using fixed_size_in_bytes = std::integral_constant<serialize_size_type, 0>;		// doesn't matter
		using type_identifier_type = typename T_Struct::type_identifier_type;
		static constexpr uint32_t get_type_identifier_size()
		{
			return type_identifier_type::value.length();
		}

		static constexpr const uint8_t* get_type_identifier_buffer()
		{
			return type_identifier_type::value.data;
		}

		smartptr_type ptr;
		struct_wrapper(const smartptr_type &p)
			: ptr(p) {}
		template<typename ...Args>
		struct_wrapper(Args... args)
			: ptr(new implementation_type(args...))
		{

		}

		struct_wrapper(const struct_wrapper &rhs)
		{
			ptr = rhs.ptr;
		}

		void operator=(const struct_wrapper &rhs)
		{
			ptr = rhs.ptr;
		}

		std::shared_ptr<implementation_type> operator ->()
		{
			return ptr;
		}

		const std::shared_ptr<implementation_type> operator ->() const
		{
			return ptr;
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
