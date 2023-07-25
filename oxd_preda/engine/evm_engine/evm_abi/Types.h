#pragma once
#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4068 4819)
#endif
#include <evmc/evmc.hpp>
#ifdef _WIN32
#pragma warning(pop)
#endif
#include "../../../../SFC/core/ext/bignum/ttmath/ttmath.h"
#include "../../../../SFC/essentials.h"

using TTMathUint256 = ttmath::UInt<TTMATH_BITS(256)>;

namespace preda_evm {
	TTMathUint256 EVMCUintToTTMathUint(const evmc::uint256be& num);
	evmc::uint256be TTMathUintToEVMCUint(const TTMathUint256& num);
}

namespace EVMUtil {
	enum EVMType : uint16_t
	{
		NumType = 0,
		Bool,
		Address,
		StaticArray,
		StaticArrayDynamicElement,
		StaticArrayStaticStruct,
		DynamicArray,
		Bytes,
		DynamicBytes,
		Utf8String,
		StaticStruct,
		DynamicStruct
	};

	struct Type {
		static const uint32_t MAX_BIT_LENGTH = 256;
		static const uint32_t MAX_BYTE_LENGTH = MAX_BIT_LENGTH / 8;
		bool isDynamic;
		EVMType type;
		int bytes32PaddedLength() {
			return MAX_BYTE_LENGTH;
		}
		virtual std::string encode() = 0;
		//return number of 32bytes needed to be resevered 
		virtual uint64_t getReservedLength() = 0;
	};

	struct NumericType : public Type
	{
		TTMathUint256 m_value;
		bool m_IsSigned;
		NumericType(TTMathUint256 value, bool isSigned) : m_value(value), m_IsSigned(isSigned) {
			isDynamic = false;
			type = EVMType::NumType;
		};
		std::string encode() override {
			evmc::uint256be tmp = preda_evm::TTMathUintToEVMCUint(m_value);
			int32_t len = sizeof(evmc::uint256be);
			if (m_IsSigned)
			{
				bool carried = false;
				for (int32_t i = len - 1; i >= 0; i--)
				{
					tmp.bytes[i] = ~tmp.bytes[i];
					if (i == len - 1 || carried)
					{
						carried = tmp.bytes[i] == 0xff;
						tmp.bytes[i]++;
					}
				}
			}
			return evmc::hex(tmp);
		}
		uint64_t getReservedLength() override { return 1; }
		//TTMathUint256 getValue() override { return m_value; }
	};

	struct AddressType : public Type
	{
		evmc::address m_value;
		AddressType(evmc::address value) : m_value(value) {
			isDynamic = false;
			type = EVMType::Address;
		}
		std::string encode() override {
			evmc::uint256be tmp;
			for (uint32_t i = 0; i < sizeof(evmc::address); i++)
			{
				tmp.bytes[sizeof(evmc::bytes32) - sizeof(evmc::address) + i] = m_value.bytes[i];
			}
			return evmc::hex(tmp);
		}
		uint64_t getReservedLength() override { return 1; }
	};

	struct BoolType : public Type
	{
		uint8_t m_value;
		BoolType(bool value) : m_value(value) {
			isDynamic = false;
			type = EVMType::Bool;
		}
		std::string encode() override { return evmc::hex(preda_evm::TTMathUintToEVMCUint(ttmath::uint(m_value))); }
		uint64_t getReservedLength() override { return 1; }
	};

	struct BytesType : public Type
	{
		evmc::bytes m_value;
		BytesType(evmc::bytes value, bool isFixedSize) : m_value(value) {
			isDynamic = isFixedSize;
			type = EVMType::Bytes;
		}
		std::string encode() override {
			std::string result;
			uint32_t wordRequire = 1;
			if (isDynamic)
			{
				wordRequire = (uint32_t)(m_value.length() + 31) / 32;
				result += evmc::hex(preda_evm::TTMathUintToEVMCUint(ttmath::uint(m_value.length())));
			}
			std::string valueStr = evmc::hex(m_value);
			std::string padding((wordRequire * 32 - m_value.length()) * 2, '0');
			result += valueStr + padding;
			return result;

		}
		uint64_t getReservedLength() override { return 1; }
	};

	struct ArrayType : public Type
	{
		std::vector<std::shared_ptr<EVMUtil::Type>> m_value;
		ArrayType(std::vector<std::shared_ptr<EVMUtil::Type>> value, EVMType evmtype) : m_value(value)
		{
			type = evmtype;
			isDynamic = evmtype != EVMType::StaticArray && evmtype != EVMType::StaticArrayStaticStruct;

		}
		std::string encode() override {
			std::string result;
			if (type == EVMType::DynamicArray)
			{
				result += evmc::hex(preda_evm::TTMathUintToEVMCUint(ttmath::uint(m_value.size())));
			}
			std::vector<std::string> tmpResult;
			uint64_t dataOffset = m_value.size() * MAX_BYTE_LENGTH;
			for (std::shared_ptr<EVMUtil::Type> t : m_value)
			{
				std::string elementEncodeRes = t->encode();
				if (t->isDynamic)
				{
					std::string lenStr = evmc::hex(preda_evm::TTMathUintToEVMCUint(ttmath::uint(dataOffset)));
					result += lenStr;
				}
				tmpResult.push_back(elementEncodeRes);
				dataOffset += elementEncodeRes.length() >> 1;
			}
			for (std::string s : tmpResult)
			{
				result += s;
			}
			return result;
		}
		uint64_t getReservedLength() override {
			if (type == EVMType::StaticArrayStaticStruct || type == EVMType::StaticArray)
			{
				return m_value[0]->getReservedLength() * m_value.size();
			}
			else
			{
				return 1;
			}
		}
	};

	struct StructType : public Type
	{
		std::vector<Type*> m_value;
		StructType(std::vector<Type*> value, EVMType evmtype) : m_value(value)
		{
			type = evmtype;
		}
		std::string encode() override {
			return std::string();
		}
		uint64_t getReservedLength() override {
			if (type == EVMType::StaticStruct)
			{
				return m_value.size();
			}
			else
			{
				return 1;
			}
		}
	};
}
