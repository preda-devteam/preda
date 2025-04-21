#pragma once
#include <string>
#include <vector>
#include "abi_types.h"
#include "../../../3rdParty/nlohmann/json.hpp"

namespace xtl
{

int function_arguments_abi_encode(const std::vector<std::pair<std::string, std::string>>& type_value_pairs, evmc::bytes& out)
{
	out.resize(type_value_pairs.size() * sizeof(evmc::bytes32));
	auto static_it = out.begin();

	evmc::bytes dynamic_bytes;
	auto dynamic_offset = type_value_pairs.size() * sizeof(evmc::bytes32);

	for(const auto& type_value_pair : type_value_pairs)
	{
		evmc::bytes bytes = get_type_encoded_data(type_value_pair.first, type_value_pair.second);
		if(bytes.empty())
			return -1;

		xtl::TypeParser internal_type(type_value_pair.first);
		if (internal_type.is_dynamic_array || xtl::String == internal_type.type || xtl::Bytes == internal_type.type)
		{
			evmc::bytes32 offset(dynamic_offset);
			static_it = std::copy(std::begin(offset.bytes), std::end(offset.bytes), static_it);
			dynamic_bytes.insert(dynamic_bytes.end(), bytes.begin(), bytes.end());
			dynamic_offset += bytes.size();
		}
		else
			static_it = std::copy(bytes.begin(), bytes.end(), static_it);
	}

	out.insert(out.end(), dynamic_bytes.begin(), dynamic_bytes.end());

	return 0;
}

int abi_decode(const std::vector<std::pair<std::string, std::string>>& type_name_pairs, evmc::bytes_view bv, std::string& out)
{
	nlohmann::json out_json;

	bool is_dynamic_array = false;
	std::vector<bool> is_dynamic(type_name_pairs.size(), false);
	for(auto& type_name_pair : type_name_pairs)
	{
		xtl::TypeParser internal_type(type_name_pair.first);
		if (internal_type.is_dynamic_array || xtl::String == internal_type.type || xtl::Bytes == internal_type.type)
		{
			is_dynamic_array = true;
			break;
		}
	}

	for(auto i = 0; i < type_name_pairs.size(); ++i)
	{
		evmc::bytes_view type_bv = is_dynamic_array ? bv.substr(evmc::load64be(bv.data() + sizeof(evmc::bytes32) * (i + 1) - sizeof(uint64_t))) : bv.substr(sizeof(evmc::bytes32) * i);
		std::string str = std::move(get_type_decoded_string(type_name_pairs[i].first, type_bv));
		if(str.empty())
			return -1;
		out_json[type_name_pairs[i].second] = str;
	}

	out = out_json.dump(4);
	return 0;
}

} // end of namespace xtl