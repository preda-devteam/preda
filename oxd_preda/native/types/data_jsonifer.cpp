#include "typetraits.h"
#include "wallet.h"
#include "data_jsonifer.h"


namespace rvm
{

bool TypeStrStreamSeekForwardOneType(std::stringstream &typeStrStream, std::string *pOutType = nullptr)
{
	std::string curType;
	if(!(typeStrStream >> curType))
		return false;
	if(curType == "struct")
	{
		uint32_t numMember;
		if(!(typeStrStream >> numMember))
			return false;
		for(uint32_t i = 0; i < numMember; i++)
		{
			if(!TypeStrStreamSeekForwardOneType(typeStrStream))
				return false;
			std::string memberName;
			if(!(typeStrStream >> memberName))
				return false;
		}

		return true;
	}
	else if(curType == "array")
	{
		return TypeStrStreamSeekForwardOneType(typeStrStream);
	}
	else if(curType == "map")
	{
		if(!TypeStrStreamSeekForwardOneType(typeStrStream))
			return false;
		if(!TypeStrStreamSeekForwardOneType(typeStrStream))
			return false;
	}
	else if(curType == "enum")
	{
		std::string enumType;
		if(!(typeStrStream >> enumType))
			return false;

		return true;
	}

	return true;
}

bool FunctionArgumentSignatureParse(std::string signature, std::vector<std::string> &outArgumentTypes, std::vector<std::string> &outArgumentNames)
{
	std::replace_if(signature.begin(), signature.end(), [](const char &c) { return c == ':' || c == '=' || c == '<' || c == '>' || c == '{' || c == '}' || c == ';' || c == '(' || c == ')' || c == ','; }, ' ');
	std::stringstream typeStrStream;
	typeStrStream << signature;

	outArgumentTypes.clear();
	outArgumentNames.clear();
	while(1)
	{
		uint32_t pos = uint32_t(typeStrStream.tellg());
		if(!TypeStrStreamSeekForwardOneType(typeStrStream))
			return true;
		uint32_t pos2 = uint32_t(typeStrStream.tellg());
		while(pos < pos2 && signature[pos] == ' ')
			pos = pos + 1;
		outArgumentTypes.push_back(signature.substr(pos, pos2 - pos));
		std::string argName;
		if(!(typeStrStream >> argName))
			return false;
		outArgumentNames.push_back(argName);
	}
}

bool TypeStrStreamPeekNextTypeIsFixedSize(std::stringstream &typeStrStream, bool &outIsFixedSize)
{
	std::stringstream::pos_type savedPos = typeStrStream.tellg();

	std::string curType;
	if(!(typeStrStream >> curType))
	{
		typeStrStream.seekg(savedPos); 
		return false;
	}

	if(curType == "array" || curType == "map" || curType == "string" || curType == "bigint" || curType == "token" || curType == "data")
	{
		typeStrStream.seekg(savedPos);
		outIsFixedSize = false;
		return true;
	}
		
	if(curType == "struct")
	{
		uint32_t numMember;
		if(!(typeStrStream >> numMember))
		{
			typeStrStream.seekg(savedPos);
			return false;
		}
		for(uint32_t i = 0; i < numMember; i++)
		{
			bool bMemberIsFixedSize;
			if(!TypeStrStreamPeekNextTypeIsFixedSize(typeStrStream, bMemberIsFixedSize))
			{
				typeStrStream.seekg(savedPos);
				return false;
			}

			if(!bMemberIsFixedSize)
			{
				typeStrStream.seekg(savedPos);
				outIsFixedSize = false;
				return true;
			}
			if(!TypeStrStreamSeekForwardOneType(typeStrStream))
				return false;
			std::string memberName;
			if(!(typeStrStream >> memberName))
				return false;
		}

		typeStrStream.seekg(savedPos);
		outIsFixedSize = false;
		return true;
	}

	typeStrStream.seekg(savedPos);
	outIsFixedSize = true;
	return true;
}

bool TypeStrStreamPeekNextType(std::stringstream &typeStrStream, std::string &outType)
{
	std::stringstream::pos_type savedPos = typeStrStream.tellg();

	if(!(typeStrStream >> outType))
	{
		typeStrStream.seekg(savedPos);
		return false;
	}

	typeStrStream.seekg(savedPos);

	return true;
}

bool TypeStrStreamPeekNextTypeIsValidMapKeyType(std::stringstream &typeStrStream, bool &outIsValidKeyType)
{
	std::string curType;
	if(!TypeStrStreamPeekNextType(typeStrStream, curType))
		return false;

	outIsValidKeyType = (curType == "bool"
		|| curType == "int8" || curType == "int16" || curType == "int32" || curType == "int64"
		|| curType == "uint8" || curType == "uint16" || curType == "uint32" || curType == "uint64"
		|| curType == "uint128" || curType == "uint256" || curType == "uint512" || curType == "int128" || curType == "int256" || curType == "int512"
		|| curType == "address" || curType == "blob" || curType == "hash"
		 || curType == "float256" || curType == "float512" || curType == "float1024"
		 );

	return true;
}

RvmDataJsonifier::RvmDataJsonifier(const char *pTypeStr, ISymbolDatabaseForJsonifier *pSymbolDatabase)
{
	m_simplifiedTypeString = pTypeStr;
	std::replace_if(m_simplifiedTypeString.begin(), m_simplifiedTypeString.end(), [](const char &c) { return c == ':' || c == '=' || c == '<' || c == '>' || c == '{' || c == '}' || c == ';' || c == '(' || c == ')' || c == ','; }, ' ');
	m_typeStrStream << m_simplifiedTypeString;
	m_pSymbolDatabase = pSymbolDatabase;
}

int RvmDataJsonifier::Jsonify(std::string& outJson, const uint8_t* pData, uint32_t dataSize, bool bWrapValueWithQuotation)
{
	uint32_t remainingSize = dataSize;
	if (!_Jsonify(outJson, pData, remainingSize, bWrapValueWithQuotation))
		return -1;

	return dataSize - remainingSize;
}

bool RvmDataJsonifier::_Jsonify(std::string &outJson, const uint8_t* &pData, uint32_t &dataSize, bool bWrapValueWithQuotation)
{
	std::string curType;
	if(!(m_typeStrStream >> curType))
		return false;

	if(curType == "struct")
	{
		uint32_t numMember;
		if(!(m_typeStrStream >> numMember))
			return false;

		if (pData)
		{
			// parse struct header
			if (dataSize < 1)
				return false;
			uint8_t bytesPerOffset = (pData[0] & 3) + 1;			// lower 4 bits of first byte is offset byte width
			if (dataSize < bytesPerOffset)
				return false;

			uint32_t numMember2 = (pData[0] >> 4);				// rest of first byteWidth bytes is number of members
			for (uint8_t i = 1; i < bytesPerOffset; i++)
				numMember2 += uint32_t(pData[i]) << ((i - 1) * 8 + 4);
			if (numMember2 != numMember)							// the number of members should match the one in signature
				return false;
			if (dataSize < bytesPerOffset * (numMember2 + 1))		// skip the offset table
				return false;
			pData += bytesPerOffset * (numMember2 + 1);
			dataSize -= bytesPerOffset * (numMember2 + 1);
		}
		outJson = "{";
		for(uint32_t i = 0; i < numMember; i++)
		{
			std::string memberJson;
			if(!_Jsonify(memberJson, pData, dataSize, bWrapValueWithQuotation))
				return false;

			std::string memberName;
			if(!(m_typeStrStream >> memberName))
				return false;

			if(i > 0)
				outJson += ", ";

			if(bWrapValueWithQuotation)
				outJson += "\"" + memberName + "\" : " + memberJson;
			else
				outJson += memberName + " : " + memberJson;
		}
		outJson += "}";

		return true;
	}
	else if (curType == "uint512" || curType == "uint256" || curType == "uint128" || curType == "uint64" || curType == "uint32" || curType == "uint16" || curType == "uint8" || curType == "interface" || curType == "contract")
	{
		if (!pData)
		{
			outJson = "0";
			return true;
		}
		uint32_t width;
		if (curType == "interface" || curType == "contract")
			width = 64;
		else
		{
#ifdef _WIN32
			sscanf_s(curType.c_str() + 4, "%ud", &width);
#else
			sscanf(curType.c_str() + 4, "%ud", &width);
#endif
		}
		if(dataSize < width / 8)
			return false;
		const uint8_t *pRead = pData;
		dataSize -= width / 8;
		pData += width / 8;
		switch (width)
		{
		case 8:
			outJson = std::to_string(*(uint8_t*)(pRead));
			return true;
		case 16:
			outJson = std::to_string(*(uint16_t*)(pRead));
			return true;
		case 32:
			outJson = std::to_string(*(uint32_t*)(pRead));
			return true;
		case 64:
			outJson = std::to_string(*(uint64_t*)(pRead));
			return true;
		case 128:
			outJson = ((ttmath::UInt<TTMATH_BITS(128)>*)pRead)->ToString();
			return true;
		case 256:
			outJson = ((ttmath::UInt<TTMATH_BITS(256)>*)pRead)->ToString();
			return true;
		case 512:
			outJson = ((ttmath::UInt<TTMATH_BITS(512)>*)pRead)->ToString();
			return true;
		}

		return false;
	}
	else if (curType == "int512" || curType == "int256" || curType == "int128" || curType == "int64" || curType == "int32" || curType == "int16" || curType == "int8")
	{
		if (!pData)
		{
			outJson = "0";
			return true;
		}
		uint32_t width;
#ifdef _WIN32
		sscanf_s(curType.c_str() + 3, "%ud", &width);
#else
		sscanf(curType.c_str() + 3, "%ud", &width);
#endif
		if(dataSize < width / 8)
			return false;
		const uint8_t *pRead = pData;
		dataSize -= width / 8;
		pData += width / 8;
		switch (width)
		{
		case 8:
			outJson = std::to_string(*(int8_t*)(pRead));
			return true;
		case 16:
			outJson = std::to_string(*(int16_t*)(pRead));
			return true;
		case 32:
			outJson = std::to_string(*(int32_t*)(pRead));
			return true;
		case 64:
			outJson = std::to_string(*(int64_t*)(pRead));
			return true;
		case 128:
			outJson = ((ttmath::Int<TTMATH_BITS(128)>*)pRead)->ToString();
			return true;
		case 256:
			outJson = ((ttmath::Int<TTMATH_BITS(256)>*)pRead)->ToString();
			return true;
		case 512:
			outJson = ((ttmath::Int<TTMATH_BITS(512)>*)pRead)->ToString();
			return true;
		}
		return false;
	}
	else if(curType == "float256" || curType == "float512" || curType == "float1024") {
		if (!pData)
		{
			outJson = "0";
			return true;
		}
		uint32_t width;
		#ifdef _WIN32
				sscanf_s(curType.c_str() + 5, "%ud", &width);
		#else
				sscanf(curType.c_str() + 5, "%ud", &width);
		#endif
		if(width/8 + 4 > dataSize)
			return false;
		const uint8_t* pRead = pData;
		dataSize -= (width/8 + 4);
		pData += (width/8 + 4);
		switch (width)
		{
		case 256:
			outJson = ((Float256*)pRead)->ToString();
			return true;
		case 512:
			outJson = ((Float512*)pRead)->ToString();
			return true;
		case 1024:
			outJson = ((Float1024*)pRead)->ToString();
			return true;
		}
		return false;
	}
	else if(curType == "bool")
	{
		if (!pData)
		{
			outJson = "false";
			return true;
		}
		if(dataSize < 1)
			return false;
		outJson = (*(bool*)pData) ? "true" : "false";
		dataSize -= 1;
		pData += 1;

		return true;
	}
	else if(curType == "string")
	{
		if (!pData)
		{
			outJson = bWrapValueWithQuotation ? "\"\"" : "";
			return true;
		}
		if(dataSize < 2)
			return false;
		uint16_t len = *(uint16_t*)pData;
		dataSize -= 2;
		pData += 2;

		if(dataSize < len)
			return false;
		if(bWrapValueWithQuotation)
		{
			outJson.resize(len + 2);
			if(len > 0)
				memcpy(&outJson[1], pData, len);
			outJson[0] = '\"';
			outJson[outJson.length() - 1] = '\"';
		}
		else
		{
			outJson.resize(len);
			if(len > 0)
				memcpy(&outJson[0], pData, len);
		}

		dataSize -= len;
		pData += len;

		return true;
	}
	else if(curType == "array")
	{
		if (!pData)
		{
			outJson = "[]";
			std::string tmp;
			m_typeStrStream >> tmp;
			return true;
		}
		if(dataSize < 4)
			return false;

		uint32_t numElement = *(uint32_t*)(pData);

		bool bIsFixedElementSize;
		if(!TypeStrStreamPeekNextTypeIsFixedSize(m_typeStrStream, bIsFixedElementSize))
			return false;

		uint32_t offsetToElementData = bIsFixedElementSize ? 4 : (4 + 4 * numElement);

		if(dataSize < offsetToElementData)
			return false;
		dataSize -= offsetToElementData;
		pData += offsetToElementData;

		std::stringstream::pos_type savedPos = m_typeStrStream.tellg();

		outJson = "[";
		for(uint32_t i = 0; i < numElement; i++)
		{
			if(i > 0)
				outJson += ", ";

			m_typeStrStream.seekg(savedPos);
			std::string elementJson;
			if(!_Jsonify(elementJson, pData, dataSize, bWrapValueWithQuotation))
				return false;

			outJson += elementJson;
		}
		outJson += "]";

		if(numElement == 0)
		{
			if(!TypeStrStreamSeekForwardOneType(m_typeStrStream))
				return false;
		}

		return true;
	}
	else if(curType == "map")
	{
		if (!pData)
		{
			outJson = "{}";
			std::string tmp;
			m_typeStrStream >> tmp;
			m_typeStrStream >> tmp;
			return true;
		}
		if(dataSize < 4)
			return false;

		uint32_t numElement = *(uint32_t*)(pData);
		dataSize -= 4;
		pData += 4;

		bool bIsValueMapKeyType;
		if(!TypeStrStreamPeekNextTypeIsValidMapKeyType(m_typeStrStream, bIsValueMapKeyType))
			return false;
		if(!bIsValueMapKeyType)
			return false;

		std::stringstream::pos_type savedPos = m_typeStrStream.tellg();

		outJson = "{";
		std::vector<std::string> keyJsons(numElement);
		for(uint32_t i = 0; i < numElement; i++)
		{
			m_typeStrStream.seekg(savedPos);
			if(!_Jsonify(keyJsons[i], pData, dataSize, bWrapValueWithQuotation))
				return false;

			if(!(keyJsons[i].size() >= 2 && keyJsons[i][0] == '\"' && keyJsons[i][keyJsons[i].size() - 1] == '\"'))
				keyJsons[i] = '\"' + keyJsons[i] + '\"';
		}

		if(numElement == 0)
		{
			if(!TypeStrStreamSeekForwardOneType(m_typeStrStream))
				return false;
		}
		savedPos = m_typeStrStream.tellg();

		bool bIsFixedElementSize;
		if(!TypeStrStreamPeekNextTypeIsFixedSize(m_typeStrStream, bIsFixedElementSize))
			return false;

		uint32_t extraOffsetToElementData = bIsFixedElementSize ? 0 : (numElement * 4);
		if(dataSize < extraOffsetToElementData)
			return false;
		dataSize -= extraOffsetToElementData;
		pData += extraOffsetToElementData;

		for(uint32_t i = 0; i < numElement; i++)
		{
			if(i > 0)
				outJson += ", ";

			m_typeStrStream.seekg(savedPos);
			std::string valueJson;
			if(!_Jsonify(valueJson, pData, dataSize, bWrapValueWithQuotation))
				return false;

			outJson += keyJsons[i] + ": " + valueJson;
		}
		outJson += "}";

		if(numElement == 0)
		{
			if(!TypeStrStreamSeekForwardOneType(m_typeStrStream))
				return false;
		}

		return true;
	}
	else if(curType == "blob")
	{
		if (!pData)
		{
			outJson = bWrapValueWithQuotation ? "\"null\"" : "null";
			return true;
		}
		uint32_t numBytes = sizeof(::rvm::Blob);
		if(dataSize < numBytes)
			return false;

		rt::Json res;
		::rvm::RvmTypeJsonify(*(::rvm::Blob *)pData, res);
		outJson = res.GetInternalString();
		if(!bWrapValueWithQuotation && outJson.size() >= 2 && outJson[0] == '\"' && outJson[outJson.size() - 1] == '\"')
			outJson = outJson.substr(1, outJson.size() - 2);

		dataSize -= numBytes;
		pData += numBytes;

		return true;
	}
	else if(curType == "hash")
	{
		if (!pData)
		{
			outJson = bWrapValueWithQuotation ? "\"\"" : "";
			return true;
		}
		uint32_t numBytes = sizeof(::rvm::HashValue);
		if(dataSize < numBytes)
			return false;

		rt::Json res;
		::rvm::RvmTypeJsonify(*(::rvm::HashValue *)pData, res);
		outJson += res.GetInternalString();
		if(!bWrapValueWithQuotation && outJson.size() >= 2 && outJson[0] == '\"' && outJson[outJson.size() - 1] == '\"')
			outJson = outJson.substr(1, outJson.size() - 2);

		dataSize -= numBytes;
		pData += numBytes;

		return true;
	}
	else if(curType == "address")
	{
		if (!pData)
		{
			outJson = bWrapValueWithQuotation ? "\"\"" : "";
			return true;
		}
		uint32_t numBytes = sizeof(::rvm::Address);
		if(dataSize < numBytes)
			return false;

		rt::Json res;
		::rvm::RvmTypeJsonify(*(::rvm::Address *)pData, res);
		outJson += res.GetInternalString();
		if(!bWrapValueWithQuotation && outJson.size() >= 2 && outJson[0] == '\"' && outJson[outJson.size() - 1] == '\"')
			outJson = outJson.substr(1, outJson.size() - 2);

		dataSize -= numBytes;
		pData += numBytes;

		return true;
	}
	else if(curType == "data")
	{
		if (!pData)
		{
			outJson = bWrapValueWithQuotation ? "\"null\"" : "null";
			return true;
		}
		::rvm::Data &data = *(::rvm::Data*)pData;
		uint32_t numReadBytes = uint32_t(data.GetEmbeddedSize());
		if(numReadBytes > dataSize)
			return false;

		rt::Json res;
		::rvm::RvmTypeJsonify(data, res);
		outJson = res.GetInternalString();
		if(!bWrapValueWithQuotation && outJson.size() >= 2 && outJson[0] == '\"' && outJson[outJson.size() - 1] == '\"')
			outJson = outJson.substr(1, outJson.size() - 2);

		dataSize -= numReadBytes;
		pData += numReadBytes;

		return true;
	}
	else if(curType == "bigint")
	{
		if (!pData)
		{
			outJson = bWrapValueWithQuotation ? "\"0\"" : "0";
			return true;
		}
		::rvm::BigNum &bignum = *(::rvm::BigNum*)pData;

		uint32_t numReadBytes = uint32_t(bignum.GetEmbeddedSize());
		if(numReadBytes > dataSize)
			return false;

		rt::Json res;
		::rvm::RvmTypeJsonify(bignum, res);
		outJson = res.GetInternalString();
		if(!bWrapValueWithQuotation && outJson.size() >= 2 && outJson[0] == '\"' && outJson[outJson.size() - 1] == '\"')
			outJson = outJson.substr(1, outJson.size() - 2);

		dataSize -= numReadBytes;
		pData += numReadBytes;

		return true;
	}
	else if(curType == "token")
	{
		if (!pData)
		{
			outJson = bWrapValueWithQuotation ? "{\"id\":0,\"amount\":\"0\"}" : "{id:0,amount:0}";
			return true;
		}
		if(bWrapValueWithQuotation)
			outJson = "{\"id\" : ";
		else
			outJson = "{id : ";
		if(dataSize < 4)
			return false;
		outJson += std::to_string(*(uint64_t*)pData);
		pData += 8;
		dataSize -= 8;

		if(bWrapValueWithQuotation)
			outJson += ", \"amount\" : ";
		else
			outJson += ", amount : ";

		::rvm::BigNum &bignum = *(::rvm::BigNum*)pData;

		uint32_t numReadBytes = uint32_t(bignum.GetEmbeddedSize());
		if(numReadBytes > dataSize)
			return false;

		rt::Json res;
		::rvm::RvmTypeJsonify(bignum, res);
		std::string amountJson(res.GetInternalString());
		if(!bWrapValueWithQuotation && amountJson.size() >= 2 && amountJson[0] == '\"' && amountJson[amountJson.size() - 1] == '\"')
			amountJson = amountJson.substr(1, amountJson.size() - 2);

		outJson += amountJson;
		outJson += "}";

		dataSize -= numReadBytes;
		pData += numReadBytes;

		return true;

	}
	else if(curType == "enum")
	{
		std::string enumTypeName;
		if(!(m_typeStrStream >> enumTypeName))
			return false;
		uint16_t value = 0;
		if (pData)
		{
			if (dataSize < 2)
				return false;
			value = *(uint16_t*)pData;
		}
		const char *enumString = m_pSymbolDatabase ? m_pSymbolDatabase->GetEnumStringFromValue(enumTypeName.c_str(), value) : nullptr;
		if(enumString == nullptr)
			return false;
		if(bWrapValueWithQuotation)
			outJson = "\"" + std::string(enumString) + "\"";
		else
			outJson = std::string(enumString);
		if (pData)
		{
			dataSize -= 2;
			pData += 2;
		}
		return true;
	}
	else if(curType == "vault")
	{
		if (!pData)
		{
			outJson = "[]";
			return true;
		}
		::rvm::NonFungibleVault& vault = *(::rvm::NonFungibleVault*)pData;
		uint32_t numReadBytes = uint32_t(vault.GetEmbeddedSize());
		if(numReadBytes > dataSize)
			return false;

		rt::Json json;
		vault.Jsonify(json);
		rt::String res(json.GetInternalString());
		outJson = res.GetString();
		if(!bWrapValueWithQuotation && outJson.size() >= 2 && outJson[0] == '\"' && outJson[outJson.size() - 1] == '\"')
			outJson = outJson.substr(1, outJson.size() - 2);

		dataSize -= numReadBytes;
		pData += numReadBytes;
		return true;
	}
	return false;
}

RvmDataJsonParser::RvmDataJsonParser(const char *pTypeStr, ISymbolDatabaseForJsonifier *pSymbolDatabase)
{
	m_simplifiedTypeString = pTypeStr ? pTypeStr : "";
	std::replace_if(m_simplifiedTypeString.begin(), m_simplifiedTypeString.end(), [](const char &c) { return c == ':' || c == '=' || c == '<' || c == '>' || c == '{' || c == '}' || c == ';' || c == '(' || c == ')' || c == ','; }, ' ');
	m_typeStrStream << m_simplifiedTypeString;
	m_pSymbolDatabase = pSymbolDatabase;
}

bool RvmDataJsonParser::IsLongIntegerLiteralInRange(const rt::String_Ref& literalBody, size_t bitWidth, bool bIsSigned)
{
	bool literalIsNonPositive = literalBody[0] == '-';
	rt::String_Ref str = literalIsNonPositive ? literalBody.SubStr(1) : literalBody;
	if (str[0] == '0' && (str[1] == 'x' || str[0] == 'X'))
	{
		return false;
	}
	static const std::vector<std::string> unsigned_max{ "340282366920938463463374607431768211455", "115792089237316195423570985008687907853269984665640564039457584007913129639935", "0", "13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084095" };
	static const std::vector<std::string> signed_max{ "170141183460469231731687303715884105727", "57896044618658097711785492504343953926634992332820282019728792003956564819967", "0", "6703903964971298549787012499102923063739682910296196688861780721860882015036773488400937149083451713845015929093243025426876941405973284973216824503042047" };
	std::string maxValue = bIsSigned ? signed_max[bitWidth / 128 - 1] : unsigned_max[bitWidth / 128 - 1];
	size_t maxValueLen = maxValue.length();
	if (literalIsNonPositive)
	{
		if (!bIsSigned)
		{
			return false;
		}
		maxValue[maxValue.length() - 1] = '8';
	}
	if (str.GetLength() > maxValueLen)
	{
		return false;
	}
	else if (str.GetLength() < maxValueLen)
	{
		return true;
	}
	else
	{
		for (int i = 0; i < maxValueLen; i++)
		{
			if (str[i] > maxValue[i]) return false;
			if (str[i] < maxValue[i]) return true;
		}
	}
	//when literalBody = maxValue
	return true;
}

bool RvmDataJsonParser::IsIntegerLiteralInRange(const rt::String_Ref& literalBody, size_t bitWidth, bool bIsSigned)
{
	ASSERT(bitWidth == 8 || bitWidth == 16 || bitWidth == 32 || bitWidth == 64 || bitWidth == 128 || bitWidth == 256 || bitWidth == 512);
	int base = 10;
	if(literalBody[0] == '0' && (literalBody[1] == 'x' || literalBody[1] == 'X')) {
		base = 16;
	}
	if (bitWidth > 64)
	{
		return IsLongIntegerLiteralInRange(literalBody, bitWidth, bIsSigned);
	}
	static const uint64_t maxValues[8] = { 255, 65535, 0, 4294967295, 0, 0, 0, 18446744073709551615llu };
	uint64_t maxValue = maxValues[bitWidth / 8 - 1];
	bool literalIsNonPositive = literalBody[0] == '-';
	if(bIsSigned)
	{
		maxValue /= 2;
		if(literalIsNonPositive)
			maxValue = maxValue + 1;
	}
	else
	{
		if(literalIsNonPositive)
			maxValue = 0;
	}

	uint64_t curValue = 0;

	size_t start = 0;
	if(literalIsNonPositive)
		start++;
	if(base == 16)
		start += 2;
	for(size_t i = start; i < literalBody.GetLength(); i++)
	{
		if(maxValue / base < curValue)
			return false;
		curValue *= base;

		uint64_t curDigit;
		if(literalBody[i] >= '0' && literalBody[i] <= '9')
			curDigit = literalBody[i] - '0';
		else if(literalBody[i] >= 'a' && literalBody[i] <= 'f')
			curDigit = literalBody[i] - 'a' + 10;
		else if(literalBody[i] >= 'A' && literalBody[i] <= 'F')
			curDigit = literalBody[i] - 'F' + 10;
		else
			return false;

		if(maxValue == 0 && (curDigit > 0 || curValue > 0))
			return false;
		if(maxValue - curDigit < curValue)
			return false;
		curValue += curDigit;
	}

	return true;
}

bool RvmDataJsonParser::JsonParse(const rt::String_Ref &jsonStr, std::vector<uint8_t> &outBuffer)
{
	std::string curType;
	if(!(m_typeStrStream >> curType))
		return SetError(jsonStr.Begin(), JsonParseErrorCode::TypeStreamFormatError, "Internal error. Type stream has invalid format.");

	outBuffer.clear();

	if(curType == "struct")
	{
		if(rt::JsonKeyValuePair::GetValueType(jsonStr) != rt::JSON_OBJECT)
			return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonDataTypeMismatch, "Data type mismatch. Expecting object.");

		rt::JsonObject jsonObj(jsonStr);
		uint32_t numMember;
		if(!(m_typeStrStream >> numMember))
			return SetError(jsonStr.Begin(), JsonParseErrorCode::TypeStreamFormatError, "Internal error. Type stream has invalid format.");

		outBuffer.resize((numMember + 1) * 4);
		((uint32_t*)&outBuffer[0])[0] = (numMember << 4) | 3;
		for(uint32_t i = 0; i < numMember; i++)
		{
			std::stringstream::pos_type savedPos = m_typeStrStream.tellg();
			if(!TypeStrStreamSeekForwardOneType(m_typeStrStream))
				return SetError(jsonStr.Begin(), JsonParseErrorCode::TypeStreamFormatError, "Internal error. Type stream has invalid format.");

			std::string memberName;
			if(!(m_typeStrStream >> memberName))
				return SetError(jsonStr.Begin(), JsonParseErrorCode::TypeStreamFormatError, "Internal error. Type stream has invalid format.");

			m_typeStrStream.seekg(savedPos);

			bool bExist;
			rt::String_Ref data = jsonObj.GetValue(memberName.c_str(), bExist);
			if(!bExist)
				return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonObjectMemberMissing, "Object missing expected member \"" + memberName + "\".");

			std::vector<uint8_t> memberBuffer;
			if(!JsonParse(data, memberBuffer))
				return false;
			outBuffer.insert(outBuffer.end(), memberBuffer.begin(), memberBuffer.end());
			((uint32_t*)&outBuffer[0])[i + 1] = (uint32_t)outBuffer.size() - (numMember + 1) * 4;

			m_typeStrStream >> memberName;
		}

		return true;
	}
	else if (curType == "uint512" || curType == "uint256" || curType == "uint128" || curType == "uint64" || curType == "uint32" || curType == "uint16" || curType == "uint8" || curType == "interface" || curType == "contract")
	{
		if(rt::JsonKeyValuePair::GetValueType(jsonStr) != rt::JSON_NUMBER)
			return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonDataTypeMismatch, "Data type mismatch. Expecting number.");
		uint32_t width;
		if (curType == "interface" || curType == "contract")
		{
			width = 64;
		}
		else
		{
#ifdef _WIN32
			sscanf_s(curType.c_str() + 4, "%ud", &width);
#else
			sscanf(curType.c_str() + 4, "%ud", &width);
#endif
		}
		outBuffer.resize(width / 8);
		if(!IsIntegerLiteralInRange(jsonStr, width, false))
		{
			return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonConversionFailure, "Invalid literal for " + curType);
		}
		switch (width)
		{
		case 8:
			if(jsonStr.ToNumber<uint8_t>(*(uint8_t*)(&outBuffer[0])) == 0)
				return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonConversionFailure, "Cannot convert number to " + curType + ".");
			return true;
		case 16:
			if(jsonStr.ToNumber<uint16_t>(*(uint16_t*)(&outBuffer[0])) == 0)
				return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonConversionFailure, "Cannot convert number to " + curType + ".");
			return true;
		case 32:
			if(jsonStr.ToNumber<uint32_t>(*(uint32_t*)(&outBuffer[0])) == 0)
				return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonConversionFailure, "Cannot convert number to " + curType + ".");
			return true;
		case 64:
			if(jsonStr.ToNumber<uint64_t>(*(uint64_t*)(&outBuffer[0])) == 0)
				return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonConversionFailure, "Cannot convert number to " + curType + ".");
			return true;
		case 128:
		{
			ttmath::UInt<TTMATH_BITS(128)> ulongint_128(jsonStr.Begin());
			memcpy(&outBuffer[0], ulongint_128.table, sizeof(ulongint_128.table));
			return true;
		}
		case 256:
		{
			ttmath::UInt<TTMATH_BITS(256)> ulongint_256(jsonStr.Begin());
			memcpy(&outBuffer[0], ulongint_256.table, sizeof(ulongint_256.table));
			return true;
		}
		case 512:
		{
			ttmath::UInt<TTMATH_BITS(512)> ulongint_512(jsonStr.Begin());
			memcpy(&outBuffer[0], ulongint_512.table, sizeof(ulongint_512.table));
			return true;
		}
		}

		return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonUnknownIntegerWidth, "Internal error. Unknown integer width.");
	}
	else if (curType == "int512" || curType == "int256" || curType == "int128" || curType == "int64" || curType == "int32" || curType == "int16" || curType == "int8") 
	{
		if(rt::JsonKeyValuePair::GetValueType(jsonStr) != rt::JSON_NUMBER)
			return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonDataTypeMismatch, "Data type mismatch. Expecting number.");
		uint32_t width;
#ifdef _WIN32
		sscanf_s(curType.c_str() + 3, "%ud", &width);
#else
		sscanf(curType.c_str() + 3, "%ud", &width);
#endif
		outBuffer.resize(width / 8);
		if(!IsIntegerLiteralInRange(jsonStr, width, true)) {
			return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonConversionFailure, "Invalid literal for int");
		}
		switch (width)
		{
		case 8:
			if(jsonStr.ToNumber<int8_t>(*(int8_t*)(&outBuffer[0])) == 0)
				return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonConversionFailure, "Cannot convert number to int8.");
			return true;
		case 16:
			if(jsonStr.ToNumber<int16_t>(*(int16_t*)(&outBuffer[0])) == 0)
				return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonConversionFailure, "Cannot convert number to int16.");
			return true;
		case 32:
			if(jsonStr.ToNumber<int32_t>(*(int32_t*)(&outBuffer[0])) == 0)
				return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonConversionFailure, "Cannot convert number to int32.");
			return true;
		case 64:
			if(jsonStr.ToNumber<int64_t>(*(int64_t*)(&outBuffer[0])) == 0)
				return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonConversionFailure, "Cannot convert number to int64.");
			return true;
		case 128:
		{
			ttmath::Int<TTMATH_BITS(128)> longint_128(jsonStr.Begin());
			memcpy(&outBuffer[0], longint_128.table, sizeof(longint_128.table) / sizeof(uint8_t));
			return true;
		}
		case 256:
		{
			ttmath::Int<TTMATH_BITS(256)> longint_256(jsonStr.Begin());
			memcpy(&outBuffer[0], longint_256.table, sizeof(longint_256.table) / sizeof(uint8_t));
			return true;
		}
		case 512:
		{
			ttmath::Int<TTMATH_BITS(512)> longint_512(jsonStr.Begin());
			memcpy(&outBuffer[0], longint_512.table, sizeof(longint_512.table) / sizeof(uint8_t));
			return true;
		}
		}

		return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonUnknownIntegerWidth, "Internal error. Unknown integer width.");
	}
	else if(curType == "float256" || curType == "float512" || curType == "float1024"){
		if(rt::JsonKeyValuePair::GetValueType(jsonStr) != rt::JSON_NUMBER)
			return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonDataTypeMismatch, "Data type mismatch. Expecting number.");
		uint32_t width;
		#ifdef _WIN32
				sscanf_s(curType.c_str() + 5, "%ud", &width);
		#else
				sscanf(curType.c_str() + 5, "%ud", &width);
		#endif
		outBuffer.resize(width/8 + 4);
		switch (width)
		{
		case 256:
		{
			::rvm::Float256 temp256(jsonStr._p);
			memcpy(&outBuffer[0], temp256._Data, sizeof(temp256._Data) / sizeof(uint8_t));
			return true;
		}

		case 512:
		{
			::rvm::Float512 temp512(jsonStr._p);
			memcpy(&outBuffer[0], temp512._Data, sizeof(temp512._Data) / sizeof(uint8_t));
			return true;
		}

		case 1024:
		{
			::rvm::Float1024 temp1024(jsonStr._p);
			memcpy(&outBuffer[0], temp1024._Data, sizeof(temp1024._Data) / sizeof(uint8_t));
			return true;
		}

		}
		return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonUnknownFloatWidth, "Internal error. Unknown float width.");
	}
	else if(curType == "bool")
	{
		if(rt::JsonKeyValuePair::GetValueType(jsonStr) != rt::JSON_BOOL)
			return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonDataTypeMismatch, "Data type mismatch. Expecting boolean.");
		outBuffer.resize(1);
		rt::String boolStr = jsonStr;
		boolStr = boolStr.MakeLower();
		if (boolStr != "true" && boolStr != "false" && boolStr != "t" && boolStr != "f")
		{
			return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonDataTypeMismatch, "Incorrect boolean value.");
		}
		bool v;
		if(jsonStr.ToNumber(v) == 0)
			return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonConversionFailure, "Cannot convert to bool.");

		outBuffer[0] = v ? 1 : 0;

		return true;
	}
	else if(curType == "string")
	{
		if(rt::JsonKeyValuePair::GetValueType(jsonStr) != rt::JSON_STRING)
			return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonDataTypeMismatch, "Data type mismatch. Expecting string.");
		if(jsonStr.GetLength() >= 65535)
			return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonStringTooLong, "String exceeding maximum length of 65535.");
		outBuffer.resize(jsonStr.GetLength() + 2);
		*(uint16_t*)(&outBuffer[0]) = (uint16_t)jsonStr.GetLength();
		if(jsonStr.GetLength() > 0)
			memcpy(&outBuffer[2], jsonStr.Begin(), jsonStr.GetLength());

		return true;
	}
	else if(curType == "array")
	{
		if(rt::JsonKeyValuePair::GetValueType(jsonStr) != rt::JSON_ARRAY)
			return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonDataTypeMismatch, "Data type mismatch. Expecting array.");
		rt::JsonArray jsonArray(jsonStr);

		uint32_t numElement = (uint32_t)jsonArray.GetSize();

		bool bIsFixedElementSize;
		if(!TypeStrStreamPeekNextTypeIsFixedSize(m_typeStrStream, bIsFixedElementSize))
			return SetError(jsonStr.Begin(), JsonParseErrorCode::TypeStreamFormatError, "Internal error. Type stream has invalid format.");

		outBuffer.resize(4 + (bIsFixedElementSize ? 0 : (4 * numElement)));
		*(uint32_t *)(&outBuffer[0]) = numElement;

		std::stringstream::pos_type savedPos = m_typeStrStream.tellg();

		{
			rt::String_Ref element;
			for(uint32_t i = 0; i < numElement; i++)
			{
				m_typeStrStream.seekg(savedPos);

				if(!jsonArray.GetNextObject(element))
					return SetError(jsonStr.Begin(), JsonParseErrorCode::ArraySizeMismatch, "Internal error. array size mismatch.");

				std::vector<uint8_t> elementBuffer;
				if(!JsonParse(element, elementBuffer))
					return false;

				outBuffer.insert(outBuffer.end(), elementBuffer.begin(), elementBuffer.end());

				if(!bIsFixedElementSize)
					*(uint32_t *)(&outBuffer[i * 4 + 4]) = (uint32_t)outBuffer.size();
			}
		}

		if(numElement == 0)
		{
			if(!TypeStrStreamSeekForwardOneType(m_typeStrStream))
				return SetError(jsonStr.Begin(), JsonParseErrorCode::TypeStreamFormatError, "Internal error. Type stream has invalid format.");
		}

		return true;
	}
	else if(curType == "map")
	{
		if(rt::JsonKeyValuePair::GetValueType(jsonStr) != rt::JSON_OBJECT)
			return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonDataTypeMismatch, "Data type mismatch. Expecting object.");

		rt::JsonObject jsonObj(jsonStr);

		uint32_t numElement = 0;
		{
			rt::JsonKeyValuePair kvPair;
			while(jsonObj.GetNextKeyValuePair(kvPair))
				numElement++;
		}

		bool bIsValueMapKeyType;
		if(!TypeStrStreamPeekNextTypeIsValidMapKeyType(m_typeStrStream, bIsValueMapKeyType))
			return SetError(jsonStr.Begin(), JsonParseErrorCode::TypeStreamFormatError, "Internal error. Type stream has invalid format.");
		if(!bIsValueMapKeyType)
			return SetError(jsonStr.Begin(), JsonParseErrorCode::InvalidMapKeyType, "Internal error. Invalid map key type.");

		outBuffer.resize(4);
		*(uint32_t*)(&outBuffer[0]) = numElement;

		std::stringstream::pos_type savedPos = m_typeStrStream.tellg();

		{
			std::string keyType;
			if(!TypeStrStreamPeekNextType(m_typeStrStream, keyType))
				return SetError(jsonStr.Begin(), JsonParseErrorCode::TypeStreamFormatError, "Internal error. Type stream has invalid format.");

			// !IMPORTANT: JsonKeyValuePair::GetValueType() tests if a value is of type string by checking Value[-1] == '\"' or '\''
			//             Therefore, in order to fool it to think that it's not a string, we need to copy it out first.
			bool bAcceptsQuotes = (keyType == "hash" || keyType == "address" || keyType == "blob");

			rt::JsonKeyValuePair kvPair;
			while(jsonObj.GetNextKeyValuePair(kvPair))
			{
				m_typeStrStream.seekg(savedPos);

				rt::String key;
				rt::String_Ref key1;
				if(bAcceptsQuotes)
					key1 = kvPair.GetKey();
				else
				{
					key = kvPair.GetKey();
					key1 = key;
				}

				std::vector<uint8_t> keyBuffer;
				if(!JsonParse(key1, keyBuffer))
					return false;

				outBuffer.insert(outBuffer.end(), keyBuffer.begin(), keyBuffer.end());
			}
		}

		if(numElement == 0)
		{
			if(!TypeStrStreamSeekForwardOneType(m_typeStrStream))
				return SetError(jsonStr.Begin(), JsonParseErrorCode::TypeStreamFormatError, "Internal error. Type stream has invalid format.");
		}
		savedPos = m_typeStrStream.tellg();

		bool bIsFixedElementSize;
		if(!TypeStrStreamPeekNextTypeIsFixedSize(m_typeStrStream, bIsFixedElementSize))
			return SetError(jsonStr.Begin(), JsonParseErrorCode::TypeStreamFormatError, "Internal error. Type stream has invalid format.");

		uint32_t offsetElementBlock = uint32_t(outBuffer.size());
		if(!bIsFixedElementSize)
			outBuffer.resize(offsetElementBlock + 4 * numElement);

		{
			rt::JsonKeyValuePair kvPair;
			uint32_t curEleIdx = 0;
			for(uint32_t i = 0; jsonObj.GetNextKeyValuePair(kvPair); i++)
			{
				m_typeStrStream.seekg(savedPos);

				const rt::String_Ref &element = kvPair.GetValue();

				std::vector<uint8_t> elementBuffer;
				if(!JsonParse(element, elementBuffer))
					return false;

				outBuffer.insert(outBuffer.end(), elementBuffer.begin(), elementBuffer.end());
				if(!bIsFixedElementSize)
					*(uint32_t*)(&outBuffer[offsetElementBlock + i * 4]) = (uint32_t)outBuffer.size() - offsetElementBlock;
			}
		}

		if(numElement == 0)
		{
			if(!TypeStrStreamSeekForwardOneType(m_typeStrStream))
				return SetError(jsonStr.Begin(), JsonParseErrorCode::TypeStreamFormatError, "Internal error. Type stream has invalid format.");
		}

		return true;
	}
	else if(curType == "blob")
	{
		if(rt::JsonKeyValuePair::GetValueType(jsonStr) != rt::JSON_STRING)
			return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonDataTypeMismatch, "Data type mismatch. Expecting string.");

		outBuffer.resize(sizeof(::rvm::Blob));
		if(!::rvm::RvmTypeJsonParse(*(::rvm::Blob*)&outBuffer[0], jsonStr))
			return SetError(jsonStr.Begin(), JsonParseErrorCode::InvalidBlobValue, "Invalid blob value.");

		return true;
	}
	else if(curType == "hash")
	{
		if(rt::JsonKeyValuePair::GetValueType(jsonStr) != rt::JSON_STRING)
			return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonDataTypeMismatch, "Data type mismatch. Expecting string.");

		outBuffer.resize(sizeof(::rvm::HashValue));
		if(!::rvm::RvmTypeJsonParse(*(::rvm::HashValue*)&outBuffer[0], jsonStr))
			return SetError(jsonStr.Begin(), JsonParseErrorCode::InvalidHashValue, "Invalid hash value.");

		return true;
	}
	else if(curType == "address")
	{
		if(rt::JsonKeyValuePair::GetValueType(jsonStr) != rt::JSON_STRING)
			return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonDataTypeMismatch, "Data type mismatch. Expecting string.");

		outBuffer.resize(sizeof(::rvm::Address));
		if(!::rvm::RvmTypeJsonParse(*(::rvm::Address *)&outBuffer[0], jsonStr))
			return SetError(jsonStr.Begin(), JsonParseErrorCode::InvalidAddressValue, "Invalid address value.");

		return true;
	}
	else if(curType == "data")
	{
		if(rt::JsonKeyValuePair::GetValueType(jsonStr) != rt::JSON_STRING)
			return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonDataTypeMismatch, "Data type mismatch. Expecting string.");

		::rvm::DataMutable data;
		if(!::rvm::RvmTypeJsonParse(data, jsonStr))
			return SetError(jsonStr.Begin(), JsonParseErrorCode::InvalidDataValue, "Data parse error.");

		uint32_t embedSize = (uint32_t)::rvm::_details::_Embed<::rvm::Data, ::rvm::DataMutable>::GetEmbeddedSize(data);

		outBuffer.resize(embedSize);
		::rvm::_details::_Embed<::rvm::Data, ::rvm::DataMutable>::Set(&outBuffer[0], data);

		return true;
	}
	else if(curType == "bigint")
	{
		if(rt::JsonKeyValuePair::GetValueType(jsonStr) != rt::JSON_STRING)
			return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonDataTypeMismatch, "Data type mismatch. Expecting string.");

		::rvm::BigNumMutable bigint;
		if(!::rvm::RvmTypeJsonParse(bigint, jsonStr))
			return SetError(jsonStr.Begin(), JsonParseErrorCode::BigintParseError, "Bigint parse error.");
		if(bigint.GetLength() > 127)
			return SetError(jsonStr.Begin(), JsonParseErrorCode::BigintTooLarge, "Bigint too large.");

		uint32_t embedSize = (uint32_t)::rvm::_details::_Embed<::rvm::BigNum, ::rvm::BigNumMutable>::GetEmbeddedSize(bigint);

		outBuffer.resize(embedSize);
		::rvm::_details::_Embed<::rvm::BigNum, ::rvm::BigNumMutable>::Set(&outBuffer[0], bigint);

		return true;
	}
	else if(curType == "token")
	{
		if(rt::JsonKeyValuePair::GetValueType(jsonStr) != rt::JSON_OBJECT)
			return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonDataTypeMismatch, "Data type mismatch. Expecting object.");

		rt::JsonObject jsonObj(jsonStr);

		bool bExist;
		rt::String_Ref data = jsonObj.GetValue("id", bExist);
		if(!bExist)
			return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonObjectMemberMissing, "Object missing expected member \"id\".");
		outBuffer.resize(8);
		if(data.ToNumber(*(uint64_t*)(&outBuffer[0])) == 0)
			return SetError(data.Begin(), JsonParseErrorCode::JsonConversionFailure, "Cannot convert number to uint64.");

		data = jsonObj.GetValue("amount", bExist);
		if(!bExist)
			return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonObjectMemberMissing, "Object missing expected member \"amount\".");

		::rvm::BigNumMutable bigint;
		if(!::rvm::RvmTypeJsonParse(bigint, data))
			return SetError(data.Begin(), JsonParseErrorCode::BigintParseError, "Bigint parse error.");
		if(bigint.GetLength() > 127)
			return SetError(data.Begin(), JsonParseErrorCode::BigintTooLarge, "Bigint too large.");

		uint32_t embedSize = (uint32_t)::rvm::_details::_Embed<::rvm::BigNum, ::rvm::BigNumMutable>::GetEmbeddedSize(bigint);

		outBuffer.resize(uint32_t(outBuffer.size()) + embedSize);
		::rvm::_details::_Embed<::rvm::BigNum, ::rvm::BigNumMutable>::Set(&outBuffer[uint32_t(outBuffer.size()) - embedSize], bigint);

		return true;
	}
	else if(curType == "enum")
	{
		if(rt::JsonKeyValuePair::GetValueType(jsonStr) != rt::JSON_STRING)
			return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonDataTypeMismatch, "Data type mismatch. Expecting string.");
		std::string enumTypeName;
		if(!(m_typeStrStream >> enumTypeName))
			return SetError(jsonStr.Begin(), JsonParseErrorCode::TypeStreamFormatError, "Internal error. Type stream has invalid format.");

		uint16_t value;
		if(!m_pSymbolDatabase || !m_pSymbolDatabase->GetEnumValueFromString(enumTypeName, std::string(rt::String(jsonStr).GetString()), value))
			return SetError(jsonStr.Begin(), JsonParseErrorCode::InvalidEnumerator, "Invalid enumerator.");

		outBuffer.resize(2);
		*(uint16_t*)(&outBuffer[0]) = value;

		return true;
	}
	else if(curType == "vault") {
		if(rt::JsonKeyValuePair::GetValueType(jsonStr) != rt::JSON_ARRAY)
			return SetError(jsonStr.Begin(), JsonParseErrorCode::JsonDataTypeMismatch, "Data type mismatch. Expecting array of Ranges.");
		::rvm::NonFungibleVaultMutable idSet;
		if(!::rvm::RvmTypeJsonParse(idSet, jsonStr))
			return SetError(jsonStr.Begin(), JsonParseErrorCode::BigintParseError, "Bigint parse error.");
		uint32_t embedSize = (uint32_t)::rvm::_details::_Embed<::rvm::NonFungibleVault, ::rvm::NonFungibleVaultMutable>::GetEmbeddedSize(idSet);
		outBuffer.resize(embedSize);
		::rvm::_details::_Embed<::rvm::NonFungibleVault, ::rvm::NonFungibleVaultMutable>::Set(&outBuffer[0], idSet);
		return true;
	}
	return SetError(jsonStr.Begin(), JsonParseErrorCode::TypeStreamFormatError, "Internal error. Type stream has invalid format.");
}

bool FunctionArgumentUtil::JsonifyArguments(const char *pArgSignatureStr, ISymbolDatabaseForJsonifier *pSymbolDatabase, const uint8_t *pData, uint32_t dataSize, bool bWrapValueWithQuotation, std::string &outJson)
{
	std::vector<std::string> argumentTypes;
	std::vector<std::string> argumentNames;

	if(!FunctionArgumentSignatureParse(pArgSignatureStr, argumentTypes, argumentNames) || argumentTypes.size() != argumentNames.size())
		return false;

	outJson = "{";

	for(int i = 0; i < (int)argumentTypes.size(); i++)
	{
		RvmDataJsonifier jsonifier(argumentTypes[i].c_str(), pSymbolDatabase);
		std::string paramJson;
		int32_t numConsumedBytes = jsonifier.Jsonify(paramJson, pData, dataSize, true);
		if (numConsumedBytes == -1)
			return false;

		pData += numConsumedBytes;
		dataSize -= numConsumedBytes;

		if(i > 0)
			outJson += ", ";
		outJson += "\"" + argumentNames[i] + "\": ";
		outJson += paramJson;
	}
	outJson += "}";

	if(dataSize != 0)
		return false;

	return true;
}

bool FunctionArgumentUtil::JsonParseArguments(const char *pArgSignatureStr, ISymbolDatabaseForJsonifier *pSymbolDatabase, const rt::String_Ref &jsonStr, std::vector<uint8_t> &outBuffer)
{
	std::vector<std::string> argumentTypes;
	std::vector<std::string> argumentNames;

	if(!FunctionArgumentSignatureParse(pArgSignatureStr, argumentTypes, argumentNames) || argumentTypes.size() != argumentNames.size())
		return false;

	if(rt::JsonKeyValuePair::GetValueType(jsonStr) != rt::JSON_OBJECT)
		return false;

	rt::JsonObject jsonObj(jsonStr);

	for(int i = 0; i < (int)argumentTypes.size(); i++)
	{
		rt::String_Ref data;
		bool bExist;

		data = jsonObj.GetValue(argumentNames[i].c_str(), bExist);
		if(!bExist)
			return false;

		std::vector<uint8_t> buffer;
		RvmDataJsonParser dejsonifier(argumentTypes[i].c_str(), pSymbolDatabase);
		if(!dejsonifier.JsonParse(data, buffer))
			return false;

		outBuffer.insert(outBuffer.end(), buffer.begin(), buffer.end());
	}

	return true;
}

} // namespace rvm