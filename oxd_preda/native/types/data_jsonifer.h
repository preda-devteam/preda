#pragma once
#include "type_def.h"
#include <cstdint>
#include <sstream>
#include <vector>


namespace rvm
{

enum class JsonParseErrorCode : uint8_t
{
	NoError = 0,
	InvalidContractId = 1,
	InvalidOpCode = 2,
	ExpandDataTypeError = 3,
	TypeStreamFormatError = 4,
	JsonDataTypeMismatch = 5,
	JsonObjectMemberMissing = 6,
	JsonConversionFailure = 7,
	JsonUnknownIntegerWidth = 8,
	JsonStringTooLong = 9,
	ArraySizeMismatch = 10,
	MapKeysAndValuesSizeMismatch = 11,
	InvalidMapKeyType = 12,
	BlobParseError = 13,
	BlobSizeMismatch = 14,
	BigintParseError = 15,
	BigintTooLarge = 16,
	InvalidEnumerator = 17,
	InvalidHashValue = 18,
	InvalidAddressValue = 19,
	InvalidBlobValue = 20,
	InvalidDataValue = 21,
	JsonUnknownFloatWidth = 22,

};

struct ISymbolDatabaseForJsonifier
{
	virtual bool GetEnumValueFromString(const std::string &enumTypeName, const std::string &enumIdentifier, uint16_t &outValue) = 0;
	virtual const char* GetEnumStringFromValue(const std::string &enumTypeName, uint16_t value) = 0;
};

class CDataJsonifier
{
	std::string m_simplifiedTypeString;
	std::stringstream m_typeStrStream;
	ISymbolDatabaseForJsonifier *m_pSymbolDatabase;
	const uint8_t *m_pData;
	uint32_t m_dataSize;
	bool m_bWrapValueWithQuotation;

public:
	CDataJsonifier(const char *pTypeStr, ISymbolDatabaseForJsonifier *pSymbolDatabase, const uint8_t *pData, uint32_t dataSize, bool bWrapValueWithQuotation);
	bool Jsonify(std::string &outJson);
	uint32_t GetRemainingDataSize()
	{
		return m_dataSize;
	}
};

class CDataJsonParser
{
	std::string m_simplifiedTypeString;
	std::stringstream m_typeStrStream;
	ISymbolDatabaseForJsonifier *m_pSymbolDatabase;
	const char *m_pErrorPos;
	JsonParseErrorCode m_errorCode;
	std::string m_errorMsg;

	bool SetError(const char *pErrorPos, JsonParseErrorCode errorCode, const std::string &errorMsg)
	{
		m_pErrorPos = pErrorPos;
		m_errorCode = errorCode;
		m_errorMsg = errorMsg;

		return false;
	}

public:
	CDataJsonParser(const char *pTypeStr, ISymbolDatabaseForJsonifier *pSymbolDatabase);
	bool JsonParse(const rt::String_Ref &jsonStr, std::vector<uint8_t> &outBuffer);
	bool IsIntegerLiteralInRange(const rt::String_Ref& literalBody, size_t bitWidth, bool bIsSigned);
	bool IsLongIntegerLiteralInRange(const rt::String_Ref& literalBody, size_t bitWidth, bool bIsSigned);
	JsonParseErrorCode GetErrorCode() { return m_errorCode; }
	const std::string& GetErrorMsg() { return m_errorMsg; }
	const char* GetErrorPos() { return m_pErrorPos; }
};

struct FunctionArgumentUtil
{
	bool JsonifyArguments(const char *pArgSignatureStr, ISymbolDatabaseForJsonifier *pSymbolDatabase, const uint8_t *pData, uint32_t dataSize, bool bWrapValueWithQuotation, std::string &outJson);
	bool JsonParseArguments(const char *pArgSignatureStr, ISymbolDatabaseForJsonifier *pSymbolDatabase, const rt::String_Ref &jsonStr, std::vector<uint8_t> &outBuffer);
};

} // namespace rvm
