#pragma once
#include "Types.h"
namespace EVMUtil {
	struct TypeEncoder {
	private:
		TypeEncoder() {};
	public:
		static void createTypeVector(const std::vector<std::pair<std::string, std::string>>& in, std::vector<std::shared_ptr<EVMUtil::Type>>& parameterList)
		{
			for (uint32_t i = 0; i < in.size(); i++)
			{
				std::string paramType = in[i].first;
				std::string paramValue = in[i].second;
				if (uint64_t bracket_pos = paramType.rfind("["); bracket_pos != std::string::npos)
				{
					uint64_t bracketend_pos = paramType.rfind("]");

					std::string type = paramType.substr(0, bracket_pos);
					rt::JsonArray valArr(paramValue);
					rt::String_Ref val;
					std::vector<std::pair<std::string, std::string>> arrValPair;
					while (valArr.GetNextObject(val))
					{
						arrValPair.push_back({ type, std::string(val.Begin(), val.GetLength()) });
					}
					std::vector<std::shared_ptr<EVMUtil::Type>> EVMTypeArr;
					createTypeVector(arrValPair, EVMTypeArr);
					bool arrIsfixedLen = true;
					bool innerTypeIsDynamic = false;
					if (bracketend_pos == bracket_pos + 1) //"[]" or type is dynamic or 2d dynamic array
					{
						arrIsfixedLen = false;
					}

					for (std::shared_ptr<EVMUtil::Type> t : EVMTypeArr)
					{
						innerTypeIsDynamic = t->isDynamic;
					}

					EVMType t;
					if (arrIsfixedLen)
					{
						//todo: add tuple/struct type
						if (innerTypeIsDynamic)
						{
							t = EVMType::StaticArrayDynamicElement;
						}
						else
						{
							t = EVMType::StaticArray;
						}
					}
					else
					{
						t = EVMType::DynamicArray;
					}
					EVMUtil::ArrayType arrType(EVMTypeArr, t);
					parameterList.push_back(std::make_shared<EVMUtil::ArrayType>(arrType));
				}
				else if (paramType.find("int") != std::string::npos)
				{
					bool isSigned = paramValue[0] == '-';
					std::string numLiteral = isSigned ? paramValue.substr(1) : paramValue;
					EVMUtil::NumericType numType(TTMathUint256(numLiteral), isSigned);
					parameterList.push_back(std::make_shared<EVMUtil::NumericType>(numType));
				}
				else if (paramType == "bool")
				{
					bool val = false;
					if (paramValue == "true")
						val = true;
					EVMUtil::BoolType boolType(val);
					parameterList.push_back(std::make_shared<EVMUtil::BoolType>(boolType));
				}
				else if (paramType == "address")
				{
					evmc::bytes b = evmc::from_hex(paramValue).value();
					evmc::address addr;
					std::copy(b.begin(), b.end(), addr.bytes);
					EVMUtil::AddressType addrType(addr);
					parameterList.push_back(std::make_shared<EVMUtil::AddressType>(addrType));
				}
				else if (paramType == "string")
				{
					std::stringstream ss;
					for (uint32_t i = 0; i < paramValue.length(); i++)
					{
						ss << std::hex << (int)paramValue[i];
					}
					std::string str(ss.str());
					evmc::bytes b = evmc::from_hex(str).value();
					EVMUtil::BytesType bytesType(b, true);
					parameterList.push_back(std::make_shared<EVMUtil::BytesType>(bytesType));
				}
				else if (paramType.find("bytes") != std::string::npos)
				{
					evmc::bytes b = evmc::from_hex(paramValue).value();
					EVMUtil::BytesType bytesType(b, paramType == "bytes" ? true : false); //bytes is dynamic, bytes<M>, 0 < M <= 32, is static
					parameterList.push_back(std::make_shared<EVMUtil::BytesType>(bytesType));
				}
			}
		}
		static void encodeParameters(const std::vector<std::pair<std::string, std::string>>& in, std::string& result)
		{
			std::vector<std::shared_ptr<EVMUtil::Type>> parameters;
			createTypeVector(in, parameters);
			uint64_t dynamicDataOffset = getLength(parameters) * Type::MAX_BYTE_LENGTH;
			std::string dynamicData;
			for (auto parameter : parameters)
			{
				std::string encodedValue = parameter->encode();
				if (parameter->isDynamic)
				{
					result.append(evmc::hex(preda_evm::TTMathUintToEVMCUint(ttmath::uint(dynamicDataOffset))));
					dynamicData.append(encodedValue);
					dynamicDataOffset += encodedValue.length() >> 1;
				}
				else
				{
					result.append(encodedValue);
				}
			}
			result.append(dynamicData);
		}

		static uint64_t getLength(std::vector<std::shared_ptr<EVMUtil::Type>> parameters)
		{
			uint64_t count = 0;
			for (auto parameter : parameters)
			{
				count += parameter->getReservedLength();
			}
			return count;
		}
	};
}