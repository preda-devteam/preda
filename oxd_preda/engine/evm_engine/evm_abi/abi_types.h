#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <optional>
#include <memory>
#ifdef _WIN32
	#pragma warning(push)
	#pragma warning(disable:4068 4819)
#endif
#include <evmc/evmc.hpp>
#ifdef _WIN32
	#pragma warning(pop)
#endif
#include <evmc/hex.hpp>

namespace xtl
{
	enum Type
	{
		Undefined,
		Address,
		Bool,
		Bytes,
		FixedBytes,
		String,
		Struct,
		Uint,
	};

	struct TypeParser
	{
		bool is_dynamic_array;
		Type type;
		TypeParser(std::string_view typeStr);
	};

	struct TypeInterface
	{
		virtual evmc::bytes GetEncodedData() const = 0;
		virtual uint64_t GetEncodedDataLength() const = 0;
		virtual std::string GetDecodedDataString() const = 0;
	};

	class BytesType : public TypeInterface
	{
	protected:
		bool is_dynamic_array;
		std::vector<evmc::bytes> data;
	protected:
		virtual void Parse(std::string_view bytes_sv);
		virtual evmc::bytes Convert2EvmcBytes(std::string_view byte_sv);
	public:
		BytesType(bool _dynamic = false): is_dynamic_array(_dynamic), data() {}
		BytesType(std::string_view bytes_sv, bool _dynamic = false);
		BytesType(evmc::bytes_view bytes_bv, bool _dynamic = false);
		virtual evmc::bytes GetEncodedData() const;
		virtual uint64_t GetEncodedDataLength() const;
		virtual std::string GetDecodedDataString() const;
	};

	class StringType : public BytesType
	{
	protected:
		virtual evmc::bytes Convert2EvmcBytes(std::string_view str_sv) override;
	public:
		StringType(std::string_view str_sv, bool _dynamic = false);
		StringType(evmc::bytes_view str_bv, bool _dynamic = false);
		virtual std::string GetDecodedDataString() const;
	};

	class FixedBytesType : public TypeInterface
	{
	protected:
		bool is_dynamic_array;
		std::vector<evmc::bytes32> data;
	protected:
		virtual void Parse(std::string_view fixed_bytes_sv);
		virtual evmc::bytes32 Convert2EvmcBytes32(std::string_view fixed_bytes);
	public:
		FixedBytesType(bool _dynamic = false): is_dynamic_array(_dynamic), data() {}
		FixedBytesType(std::string_view fixed_bytes_sv, bool _dynamic = false);
		FixedBytesType(evmc::bytes_view fixed_bytes_bv, bool _dynamic = false);
		virtual evmc::bytes GetEncodedData() const;
		virtual uint64_t GetEncodedDataLength() const;
		virtual std::string GetDecodedDataString() const;
	};

	class AddressType : public FixedBytesType
	{
	protected:
		virtual evmc::bytes32 Convert2EvmcBytes32(std::string_view addr_sv) override;
	public:
		AddressType(std::string_view addr_sv, bool _dynamic = false);
		AddressType(evmc::bytes_view addr_bv, bool _dynamic = false);
		virtual std::string GetDecodedDataString() const;
	};

	class BoolType : public FixedBytesType
	{
	protected:
		virtual evmc::bytes32 Convert2EvmcBytes32(std::string_view bool_sv) override;
	public:
		BoolType(std::string_view bool_sv, bool _dynamic = false);
		BoolType(evmc::bytes_view bool_bv, bool _dynamic = false);
		virtual std::string GetDecodedDataString() const;
	};

	class UintType : public FixedBytesType
	{
	protected:
		virtual evmc::bytes32 Convert2EvmcBytes32(std::string_view uint_sv) override;
	public:
		UintType(std::string_view uint_sv, bool _dynamic = false);
		UintType(evmc::bytes_view uint_bv, bool _dynamic = false);
		virtual std::string GetDecodedDataString() const;
	};

	class StructType : public TypeInterface
	{
	protected:
		bool is_dynamic_array;
		std::vector<std::vector<std::unique_ptr<TypeInterface>>> data;
	public:
		StructType(std::string_view struct_sig_sv, std::string_view struct_data_sv, bool _dynamic = false);
		StructType(std::string_view struct_sig_sv, evmc::bytes_view struct_data_bv, bool _dynamic = false);
		virtual evmc::bytes GetEncodedData() const;
		virtual uint64_t GetEncodedDataLength() const;
		virtual std::string GetDecodedDataString() const;
	};

	std::unique_ptr<TypeInterface> create_type(std::string_view type_sv, std::string_view data_sv);
	std::unique_ptr<TypeInterface> create_type(std::string_view type_sv, evmc::bytes_view data_bv);
	evmc::bytes get_type_encoded_data(std::string_view type_sv, std::string_view data_sv);
	std::string	get_type_decoded_string(std::string_view type_sv, evmc::bytes_view data_bv);
} // end of namesapce xtl