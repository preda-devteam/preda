#ifndef EXPAND_STRUCT_MEMBER_LIST
	#error "EXPAND_STRUCT_MEMBER_LIST should be defined before including define_struct.h"
#endif
#ifndef STRUCT_MEMBER_COUNT
	#error "STRUCT_MEMBER_COUNT should be defined before including define_struct.h"
#endif
#ifndef STRUCT_INTERNAL_NAME
	#error "STRUCT_INTERNAL_NAME should be defined before including define_struct.h"
#endif
#ifndef STRUCT_NAME
	#error "STRUCT_NAME should be defined before including define_struct.h"
#endif


#ifdef EXPAND_STRUCT_MEMBER
	#error "EXPAND_STRUCT_MEMBER should not be defined before including define_struct.h"
#endif
#ifdef SPLITTER
	#error "SPLITTER should not be defined before including define_struct.h"
#endif
#ifdef UNPACK
	#error "UNPACK should not be defined before including define_struct.h"
#endif

#define UNPACK( ... ) __VA_ARGS__

#define EXPAND_STRUCT_MEMBER(x, y)
struct STRUCT_INTERNAL_NAME {
	using num_members = std::integral_constant<prlrt::serialize_size_type, STRUCT_MEMBER_COUNT>;

#undef EXPAND_STRUCT_MEMBER
#define EXPAND_STRUCT_MEMBER(x, y) UNPACK x y;
#undef SPLITTER
#define SPLITTER
	EXPAND_STRUCT_MEMBER_LIST

	using all_members_are_fixed_size = std::bool_constant<
		true
#undef EXPAND_STRUCT_MEMBER
#define EXPAND_STRUCT_MEMBER(x, y) && UNPACK x ::is_fixed_size::value
#undef SPLITTER
#define SPLITTER
		EXPAND_STRUCT_MEMBER_LIST
	>;

	using fixed_size_in_bytes = std::integral_constant<prlrt::serialize_size_type,
#undef EXPAND_STRUCT_MEMBER
#define EXPAND_STRUCT_MEMBER(x, y) + UNPACK x ::fixed_size_in_bytes::value
#undef SPLITTER
#define SPLITTER
		EXPAND_STRUCT_MEMBER_LIST
	>;

	struct type_identifier_type {
		static constexpr auto value
			= prlrt::type_identifier<
			2
#undef EXPAND_STRUCT_MEMBER
#define EXPAND_STRUCT_MEMBER(x, y) + UNPACK x ::get_type_identifier_size()
#undef SPLITTER
#define SPLITTER
			EXPAND_STRUCT_MEMBER_LIST
			>::create_for_struct
			(
				num_members::value
#undef EXPAND_STRUCT_MEMBER
#define EXPAND_STRUCT_MEMBER(x, y) , UNPACK x ::type_identifier_type::value
#undef SPLITTER
#define SPLITTER
				EXPAND_STRUCT_MEMBER_LIST
			);
	};

	STRUCT_INTERNAL_NAME()
	{
	}

	STRUCT_INTERNAL_NAME(
#undef EXPAND_STRUCT_MEMBER
#define EXPAND_STRUCT_MEMBER(x, y) const UNPACK x &___in_##y
#undef SPLITTER
#define SPLITTER ,
		EXPAND_STRUCT_MEMBER_LIST
	)
		:
#undef EXPAND_STRUCT_MEMBER
#define EXPAND_STRUCT_MEMBER(x, y) y(___in_##y)
#undef SPLITTER
#define SPLITTER ,
		EXPAND_STRUCT_MEMBER_LIST
	{
	}

	prlrt::serialize_size_type get_serialize_size() const
	{
		if (all_members_are_fixed_size::value)
			return get_serialize_size_all_members_are_fixed_size() + get_serialize_header_size();
		else
			return get_serialize_size_not_all_members_are_fixed_size() + get_serialize_header_size();
	}

	prlrt::serialize_size_type get_serialize_header_size() const
	{
		return (num_members::value + 1) * 4;		// num_member + offset table
	}

	prlrt::serialize_size_type get_serialize_size_all_members_are_fixed_size() const
	{
		return fixed_size_in_bytes::value;
	}

	prlrt::serialize_size_type get_serialize_size_not_all_members_are_fixed_size() const
	{
		prlrt::serialize_size_type ret = 0;
#undef EXPAND_STRUCT_MEMBER
#define EXPAND_STRUCT_MEMBER(x, y) ret += y.get_serialize_size();
#undef SPLITTER
#define SPLITTER
		EXPAND_STRUCT_MEMBER_LIST

		return ret;
	}

	void serialize_out(uint8_t *buffer, bool for_debug) const
	{
		uint32_t *header = (uint32_t *)buffer;
		header[0] = (num_members::value << 4) | 3;
		uint32_t cur_member_idx = 0;
		uint8_t *ptr = buffer + get_serialize_header_size();
		prlrt::serialize_size_type cur_element_size;
#undef EXPAND_STRUCT_MEMBER
#define EXPAND_STRUCT_MEMBER(x, y)\
		cur_element_size = y.get_serialize_size();\
		y.serialize_out(ptr, for_debug);\
		ptr += cur_element_size;\
		header[cur_member_idx + 1] = uint32_t(ptr - buffer) - 4;\
		cur_member_idx++;
		// get_serialize_size() must be called before serialize_out(), some types (e.g. note) will change data when serializing out
#undef SPLITTER
#define SPLITTER
		EXPAND_STRUCT_MEMBER_LIST
	}

	bool map_from_serialized_data(const uint8_t *&buffer, prlrt::serialize_size_type &bufferSize, bool bDeep)
	{
		if (!prlrt::util_rip_struct_serialized_header(num_members::value, buffer, bufferSize))
			return false;

#undef EXPAND_STRUCT_MEMBER
#define EXPAND_STRUCT_MEMBER(x, y)\
		if (!y.map_from_serialized_data(buffer, bufferSize, bDeep)) return false;
#undef SPLITTER
#define SPLITTER
		EXPAND_STRUCT_MEMBER_LIST
		return true;
	}
};

using STRUCT_NAME = prlrt::struct_wrapper<STRUCT_INTERNAL_NAME>;

#undef SPLITTER

#undef UNPACK

#undef EXPAND_STRUCT_MEMBER
#undef EXPAND_STRUCT_MEMBER_LIST
#undef STRUCT_MEMBER_COUNT
#undef STRUCT_INTERNAL_NAME
#undef STRUCT_NAME
