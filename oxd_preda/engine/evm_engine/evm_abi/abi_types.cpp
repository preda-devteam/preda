#include "abi_types.h"
#include "../../../../oxd_libsec/oxd_libsec.h"
#include "../../../3rdParty/nlohmann/json.hpp"
#include <sstream>
#include <intx/intx.hpp>

namespace xtl
{
TypeParser::TypeParser(std::string_view type_str)
	: is_dynamic_array(false), type(Type::Undefined)
{
	if (type_str.length() >= 2 && type_str.substr(type_str.length() - 2) == "[]")
	{
		is_dynamic_array = true;
		type_str = type_str.substr(0, type_str.size() - 2);
	}
	
	if (type_str[0] == '[')
		type = Type::Struct;
	else if (type_str == "address")
		type = Type::Address;
	else if (type_str == "bool")
		type = Type::Bool;
	else if (type_str.size() >= 5 && type_str.substr(0, 5) == "bytes")
	{
		if (5 == type_str.size() || (is_dynamic_array && 7 == type_str.size()))
			type = Type::Bytes;
		else
			type = Type::FixedBytes;
	}
	else if (type_str == "string")
		type = Type::String;
	else if (type_str.size() >= 4 && type_str.substr(0, 4) == "uint")
		type = Type::Uint;
}

void BytesType::Parse(std::string_view bytes_sv)
{
	if(is_dynamic_array)
	{
		std::vector<nlohmann::json> json_vec = nlohmann::json::parse(bytes_sv);
		for(auto& json : json_vec)
			data.emplace_back(Convert2EvmcBytes(nlohmann::to_string(json)));
	}
	else
			data.emplace_back(Convert2EvmcBytes(bytes_sv));
}

evmc::bytes BytesType::Convert2EvmcBytes(std::string_view bytes_sv)
{
	std::string bytes_str(bytes_sv);
	if (bytes_str.length() >= 2 && bytes_str[0] == '\"' && bytes_str.back() == '\"')
		bytes_str = bytes_str.substr(1, bytes_str.length() - 2);

	auto bytes = evmc::from_hex(bytes_str);
	evmc::bytes ret;
	if(bytes.has_value())
		ret = bytes.value();
	return std::move(ret);
}

BytesType::BytesType(std::string_view bytes_sv, bool _dynamic)
	: is_dynamic_array(_dynamic)
{
	Parse(bytes_sv);
}

BytesType::BytesType(evmc::bytes_view bytes_bv, bool _dynamic)
	: is_dynamic_array(_dynamic)
{
	auto compose_evmc_bytes = [](evmc::bytes_view bv) -> evmc::bytes
	{
		uint64_t bytes_len = evmc::load64be(bv.data() + sizeof(evmc::bytes32) - sizeof(uint64_t));
		if(!bytes_len)
			return evmc::bytes{};
		evmc::bytes ret;
		ret.resize(bytes_len);
		std::copy(bv.begin() + sizeof(evmc::bytes32), bv.begin() + sizeof(evmc::bytes32) + bytes_len, ret.begin());
		return std::move(ret);
	};

	if(is_dynamic_array)
	{
		uint64_t array_len = evmc::load64be(bytes_bv.data() + sizeof(evmc::bytes32) - sizeof(uint64_t));
		if(!array_len)
			return;
		for(auto i = 0; i < array_len; ++i)
		{
			uint64_t offset_len = evmc::load64be(bytes_bv.data() + sizeof(evmc::bytes32) * (i + 2) - sizeof(uint64_t));
			evmc::bytes bytes_data = compose_evmc_bytes(bytes_bv.substr(offset_len));
			data.emplace_back(bytes_data);
		}
	}
	else
	{
		evmc::bytes bytes_data = compose_evmc_bytes(bytes_bv);
		data.emplace_back(bytes_data);
	}
}

evmc::bytes BytesType::GetEncodedData() const
{
	evmc::bytes ret;
	if(data.empty())
		return ret;

	ret.resize(GetEncodedDataLength());
	if (is_dynamic_array)
	{
		evmc::bytes32 array_len(data.size());
		auto offset_it = std::copy(std::begin(array_len.bytes), std::end(array_len.bytes), ret.begin());
		auto data_it = offset_it + sizeof(evmc::bytes32) * data.size();
		size_t offset = data.size() * sizeof(evmc::bytes32);
		for (auto& bytes : data)
		{
			evmc::bytes32 offset_bytes(offset);
			// encode offset
			offset_it = std::copy(std::begin(offset_bytes.bytes), std::end(offset_bytes.bytes), offset_it);
			// encode count
			evmc::bytes32 count_bytes(bytes.size());
			data_it = std::copy(std::begin(count_bytes.bytes), std::end(count_bytes.bytes), data_it);
			offset += sizeof(evmc::bytes32);
			// encode data
			std::copy(std::begin(bytes), std::end(bytes), data_it);
			auto remainder = bytes.size() % sizeof(evmc::bytes32);
			auto bytes32_len = remainder ? bytes.size() + sizeof(evmc::bytes32) - remainder : bytes.size();
			offset += bytes32_len;
			data_it += bytes32_len;
		}
	}
	else
	{
		// encode count
		evmc::bytes32 count_bytes(data[0].size());
		std::copy(std::begin(count_bytes.bytes), std::end(count_bytes.bytes), ret.begin());
		// encode data
		std::copy(std::begin(data[0]), std::end(data[0]), ret.begin() + sizeof(evmc::bytes32));
	}

	return ret;
}

uint64_t BytesType::GetEncodedDataLength() const
{
	uint64_t ret = 0;
	if(data.empty())
		return ret;
	if (is_dynamic_array) 
	{
		ret += sizeof(evmc::bytes32);						// array length
		ret += data.size() * sizeof(evmc::bytes32);			// offsets length
		ret += data.size() * sizeof(evmc::bytes32);			// counts length
		for(const auto& bytes : data)						// data length
		{
			auto remainder = bytes.size() % sizeof(evmc::bytes32);
			ret += remainder ? bytes.size() + sizeof(evmc::bytes32) - remainder : bytes.size(); 
		}
	}
	else
	{
		ret += sizeof(evmc::bytes32);
		auto remainder = data[0].size() % sizeof(evmc::bytes32);
		ret += remainder ? data[0].size() + sizeof(evmc::bytes32) - remainder : data[0].size(); 
	}
	return ret;
}

std::string BytesType::GetDecodedDataString() const
{
	std::string ret;
	for(const auto& bytes : data)
		ret += "0x" + evmc::hex(bytes) + ",";
	if(!ret.empty())
		ret.pop_back();
	if(is_dynamic_array)
		ret = '[' + ret + ']';

	return std::move(ret);
}

evmc::bytes StringType::Convert2EvmcBytes(std::string_view str)
{
	std::string str_str(str);
	if (str_str.length() >= 2 && str_str[0] == '\"' && str_str.back() == '\"')
		str_str = str_str.substr(1, str_str.length() - 2);

	evmc::bytes ret;
	ret.resize(str_str.length());
	std::copy(str_str.begin(), str_str.end(), ret.begin());
	return std::move(ret);
}

StringType::StringType(std::string_view str_sv, bool _dynamic)
	: BytesType(_dynamic)
{
	Parse(str_sv);
}

StringType::StringType(evmc::bytes_view str_bv, bool _dynamic)
	: BytesType(str_bv, _dynamic)
{

}

std::string StringType::GetDecodedDataString() const
{
	std::string ret;
	for(const auto& bytes : data)
		ret += std::string((const char*)bytes.data()) + ",";
	if(!ret.empty())
		ret.pop_back();
	if(is_dynamic_array)
		ret = '[' + ret + ']';

	return std::move(ret);
}

void FixedBytesType::Parse(std::string_view fixed_bytes_sv)
{
	if(is_dynamic_array)
	{
		std::vector<nlohmann::json> json_vec = nlohmann::json::parse(fixed_bytes_sv);
		for(auto& json : json_vec)
			data.emplace_back(Convert2EvmcBytes32(nlohmann::to_string(json)));
	}
	else
			data.emplace_back(Convert2EvmcBytes32(fixed_bytes_sv));
}

evmc::bytes32 FixedBytesType::Convert2EvmcBytes32(std::string_view fixedByte)
{
	auto bytes = evmc::from_hex(fixedByte);
	evmc::bytes32 ret;
	if(bytes.has_value() && bytes.value().size() < sizeof(evmc::bytes32))
		std::copy(bytes.value().begin(), bytes.value().end(), std::begin(ret.bytes));
	return std::move(ret);
}

FixedBytesType::FixedBytesType(std::string_view fixed_bytes_sv, bool _dynamic)
	: is_dynamic_array(_dynamic)
{
	Parse(fixed_bytes_sv);
}

FixedBytesType::FixedBytesType(evmc::bytes_view fixed_bytes_bv, bool _dynamic)
	: is_dynamic_array(_dynamic)
{
	auto compose_evmc_bytes32 = [](evmc::bytes_view bv) -> evmc::bytes32
	{
		evmc::bytes32 ret;
		if(bv.size() < sizeof(evmc::bytes32))
			std::copy(bv.begin(), bv.end(), std::end(ret.bytes) + sizeof(evmc::bytes32) - bv.size());
		else
			std::copy(bv.begin(), bv.begin() + sizeof(evmc::bytes32), std::begin(ret.bytes));
		return std::move(ret);
	};

	if(is_dynamic_array)
	{
		uint64_t array_len = evmc::load64be(fixed_bytes_bv.data() + sizeof(evmc::bytes32) - sizeof(uint64_t));
		if(!array_len)
			return;
		for(auto i = 0; i < array_len; ++i)
		{
			evmc::bytes32 bytes_data = compose_evmc_bytes32(fixed_bytes_bv.substr(sizeof(evmc::bytes32) * (i + 1)));
			data.emplace_back(bytes_data);
		}
	}
	else
	{
		evmc::bytes32 bytes_data = compose_evmc_bytes32(fixed_bytes_bv);
		data.emplace_back(bytes_data);
	}
}

evmc::bytes FixedBytesType::GetEncodedData() const
{
	evmc::bytes ret;
	ret.resize(GetEncodedDataLength());

	auto ret_it = ret.begin();
	if (is_dynamic_array)
	{
		evmc::bytes32 len(data.size());
		ret_it = std::copy(std::begin(len.bytes), std::end(len.bytes), ret_it);
	}

	for (auto& bytes : data)
		ret_it = std::copy(std::begin(bytes.bytes), std::end(bytes.bytes), ret_it);

	return ret;
}

uint64_t FixedBytesType::GetEncodedDataLength() const
{
	return (is_dynamic_array ? data.size() + 1 : data.size()) * sizeof(evmc::bytes32);
}

std::string FixedBytesType::GetDecodedDataString() const
{
	std::string ret;
	for(const auto& bytes : data)
		ret += "0x" + evmc::hex(bytes) + ",";
	if(!ret.empty())
		ret.pop_back();
	if(is_dynamic_array)
		ret = '[' + ret + ']';

	return std::move(ret);
}

evmc::bytes32 AddressType::Convert2EvmcBytes32(std::string_view addr_sv)
{
	evmc::bytes32 ret(0);
	oxd::SecureAddress addr;

	if (!addr.FromString(rt::String_Ref(std::string(addr_sv)).TrimQuotes()))
		return ret;
	std::copy(&addr.Bytes[0], &addr.Bytes[20], &ret.bytes[12]);

	return ret;
}

AddressType::AddressType(std::string_view addr_sv, bool _dynamic)
	:FixedBytesType(_dynamic)
{
	Parse(addr_sv);
}

AddressType::AddressType(evmc::bytes_view addr_bv, bool _dynamic)
	:FixedBytesType(addr_bv, _dynamic)
{
}

std::string AddressType::GetDecodedDataString() const
{
	std::string ret;
	for(const auto& bytes : data)
		ret += "0x" + evmc::hex(evmc::bytes_view(&bytes.bytes[12], sizeof(evmc::address))) + ",";
	if(!ret.empty())
		ret.pop_back();
	if(is_dynamic_array)
		ret = '[' + ret + ']';

	return std::move(ret);
}

evmc::bytes32 BoolType::Convert2EvmcBytes32(std::string_view boolType)
{
	return "true" == boolType ? evmc::bytes32(1) : evmc::bytes32(0);
}

BoolType::BoolType(std::string_view bool_sv, bool _dynamic)
	:FixedBytesType(_dynamic)
{
	Parse(bool_sv);
}

BoolType::BoolType(evmc::bytes_view bool_bv, bool _dynamic)
	:FixedBytesType(bool_bv, _dynamic)
{
}

std::string BoolType::GetDecodedDataString() const
{
	std::string ret;
	for(const auto& bytes : data)
		ret += bytes == evmc::bytes32(0) ? "false," : "true,";
	if(!ret.empty())
		ret.pop_back();
	if(is_dynamic_array)
		ret = '[' + ret + ']';

	return std::move(ret);
}

evmc::bytes32 UintType::Convert2EvmcBytes32(std::string_view uintType)
{
	std::string uint_str(uintType);
	if (uint_str.length() >= 2 && uint_str[0] == '\"' && uint_str.back() == '\"')
		uint_str = uint_str.substr(1, uint_str.length() - 2);

	intx::uint256 u256 = intx::from_string<intx::uint256>(uint_str.data());
	return intx::be::store<evmc::bytes32>(u256);
}

UintType::UintType(std::string_view uint_sv, bool _dynamic)
	:FixedBytesType(_dynamic)
{
	Parse(uint_sv);
}

UintType::UintType(evmc::bytes_view uint_bv, bool _dynamic)
	:FixedBytesType(uint_bv, _dynamic)
{
}

std::string UintType::GetDecodedDataString() const
{
	std::string ret;
	for(const auto& bytes : data)
		ret += intx::to_string(intx::be::load<intx::uint256>(bytes)) + ",";
	if(!ret.empty())
		ret.pop_back();
	if(is_dynamic_array)
		ret = '[' + ret + ']';

	return std::move(ret);
}

StructType::StructType(std::string_view struct_sig_sv, std::string_view struct_data_sv, bool _dynamic)
	:is_dynamic_array(_dynamic)
{
	std::vector<nlohmann::json> sig_json = is_dynamic_array ? nlohmann::json::parse(struct_sig_sv.substr(0, struct_sig_sv.length() - 2)) : nlohmann::json::parse(struct_sig_sv);
	nlohmann::json data_json = nlohmann::json::parse(struct_data_sv);
	nlohmann::json data_json_arr = is_dynamic_array ? data_json : nlohmann::json::array({data_json});
	data.resize(data_json_arr.size());

	for(size_t i = 0; i < data_json_arr.size(); ++i)
	{
		for(const auto& component_json : sig_json)
		{
			auto p_type = create_type(std::string(component_json["type"]), nlohmann::to_string(data_json_arr[i][component_json["name"]]));
			if(!p_type)
			{
				data.clear();
				return;
			}
			data[i].emplace_back(p_type.release());
		}
	}
}

StructType::StructType(std::string_view struct_sig_sv, evmc::bytes_view struct_data_bv, bool _dynamic)
	:is_dynamic_array(_dynamic)
{
}

evmc::bytes StructType::GetEncodedData() const
{
	evmc::bytes ret;
	if (data.empty()) return ret;

	size_t retLength = 0, structLen = 0;
	if (is_dynamic_array) retLength += sizeof(evmc::bytes32);
	for (auto& elem : data[0])
		structLen += elem->GetEncodedDataLength();
	retLength += structLen * data.size();
	ret.resize(retLength);

	auto ret_it = ret.begin();
	if (is_dynamic_array)
	{
		evmc::bytes32 len(data.size());
		ret_it = std::copy(std::begin(len.bytes), std::end(len.bytes), ret_it);
	}

	evmc::bytes encodedData;
	encodedData.resize(structLen);
	for (auto& types : data)
	{
		auto data_it = encodedData.begin();
		for (auto& type : types)
		{
			evmc::bytes data = type->GetEncodedData();
			data_it = std::copy(std::begin(data), std::end(data), data_it);
		}
		ret_it = std::copy(std::begin(encodedData), std::end(encodedData), ret_it);
	}
	return ret;
}

uint64_t StructType::GetEncodedDataLength() const
{
	if (data.empty()) return 0;
	size_t ret = 0, length = 0;
	if (is_dynamic_array) ret += sizeof(evmc::bytes32);

	for (auto& elem : data[0])
		length += elem->GetEncodedDataLength();
	ret += length * data.size();

	return (uint64_t)ret;
}

std::string StructType::GetDecodedDataString() const
{
	return std::string();
}

std::unique_ptr<TypeInterface> create_type(std::string_view type, std::string_view data)
{
	xtl::TypeParser internal_type(type);
	switch (internal_type.type)
	{
	case xtl::Address:
		return std::make_unique<AddressType>(data, internal_type.is_dynamic_array);
	case xtl::Bool:
		return std::make_unique<BoolType>(data, internal_type.is_dynamic_array);
	case xtl::Bytes:
		return std::make_unique<BytesType>(data, internal_type.is_dynamic_array);
	case xtl::FixedBytes:
		return std::make_unique<FixedBytesType>(data, internal_type.is_dynamic_array);
	case xtl::String:
		return std::make_unique<StringType>(data, internal_type.is_dynamic_array);
	case xtl::Struct:
		return std::make_unique<StructType>(type, data, internal_type.is_dynamic_array);
	case xtl::Uint:
		return std::make_unique<UintType>(data, internal_type.is_dynamic_array);
	default:
		return nullptr;
	}
}

std::unique_ptr<TypeInterface> create_type(std::string_view type, evmc::bytes_view data)
{
	xtl::TypeParser internal_type(type);
	switch (internal_type.type)
	{
	case xtl::Address:
		return std::make_unique<AddressType>(data, internal_type.is_dynamic_array);
	case xtl::Bool:
		return std::make_unique<BoolType>(data, internal_type.is_dynamic_array);
	case xtl::Bytes:
		return std::make_unique<BytesType>(data, internal_type.is_dynamic_array);
	case xtl::FixedBytes:
		return std::make_unique<FixedBytesType>(data, internal_type.is_dynamic_array);
	case xtl::String:
		return std::make_unique<StringType>(data, internal_type.is_dynamic_array);
	case xtl::Struct:
		return std::make_unique<StructType>(type, data, internal_type.is_dynamic_array);
	case xtl::Uint:
		return std::make_unique<UintType>(data, internal_type.is_dynamic_array);
	default:
		return nullptr;
	}
}

evmc::bytes get_type_encoded_data(std::string_view type, std::string_view data)
{
	auto p_type = create_type(type, data);
	if(p_type == nullptr)
		return evmc::bytes();
	return p_type->GetEncodedData();
}

std::string get_type_decoded_string(std::string_view type, evmc::bytes_view data)
{
	auto p_type = create_type(type, data);
	if(p_type == nullptr)
		return std::string();
	return p_type->GetDecodedDataString();
}

}