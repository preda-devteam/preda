
// Generated from Preda.g4 by ANTLR 4.12.0


#include "PredaListener.h"
#include "PredaVisitor.h"

#include "PredaParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct PredaParserStaticData final {
  PredaParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  PredaParserStaticData(const PredaParserStaticData&) = delete;
  PredaParserStaticData(PredaParserStaticData&&) = delete;
  PredaParserStaticData& operator=(const PredaParserStaticData&) = delete;
  PredaParserStaticData& operator=(PredaParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag predaParserOnceFlag;
PredaParserStaticData *predaParserStaticData = nullptr;

void predaParserInitialize() {
  assert(predaParserStaticData == nullptr);
  auto staticData = std::make_unique<PredaParserStaticData>(
    std::vector<std::string>{
      "predaSource", "directive", "importDirective", "annotation", "annotationItem", 
      "doxygen", "contractDefinition", "interfaceRef", "contractPart", "stateVariableDeclaration", 
      "constVariableDeclaration", "scope", "structDefinition", "interfaceDefinition", 
      "enumDefinition", "functionDefinition", "functionDeclaration", "functionReturnTypeName", 
      "functionParameterList", "functionParameter", "accessSpecifier", "variableDeclaration", 
      "typeNameOrAuto", "typeName", "fundamentalTypeName", "builtInContainerTypeName", 
      "mapKeyTypeName", "mapTypeName", "scatteredMapTypeName", "arrayTypeName", 
      "scatteredArrayTypeName", "userDefinedTypeName", "userBlockStatement", 
      "statement", "expressionStatement", "ifStatement", "ifWithBlock", 
      "elseWithBlock", "elseIfWithBlock", "whileStatement", "relayStatement", 
      "relayType", "relayLambdaDefinition", "relayLambdaParameter", "forStatement", 
      "doWhileStatement", "continueStatement", "breakStatement", "returnStatement", 
      "variableDeclarationStatement", "localVariableDeclaration", "expression", 
      "primaryExpression", "functionCallArguments", "identifier"
    },
    std::vector<std::string>{
      "", "'.'", "';'", "'['", "','", "']'", "'='", "'{'", "'}'", "'@'", 
      "'('", "')'", "'bool'", "'string'", "'blob'", "'hash'", "'bigint'", 
      "'map'", "'<'", "'>'", "'scattered_map'", "'array'", "'scattered_array'", 
      "'while'", "'^'", "'for'", "'do'", "'return'", "'++'", "'--'", "'+'", 
      "'-'", "'!'", "'~'", "'*'", "'/'", "'%'", "'<<'", "'<='", "'>='", 
      "'=='", "'!='", "'&'", "'|'", "'&&'", "'||'", "'\\u003F'", "':'", 
      "'+='", "'-='", "'*='", "'/='", "'%='", "'<<='", "'>>='", "'&='", 
      "'^='", "'|='", "", "", "'break'", "'const'", "'continue'", "'relay'", 
      "'supply'", "'if'", "'else'", "'shard'", "'shards'", "'global'", "'address'", 
      "'auto'", "'miner'", "'struct'", "'enum'", "'contract'", "'import'", 
      "'function'", "'public'", "'export'", "'as'", "'using'", "'interface'", 
      "'implements'", "'deploy'", "'constructor'", "'next'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "DoxygenSingle", "DoxygenMulti", "BreakKeyword", 
      "ConstantKeyword", "ContinueKeyword", "RelayKeyword", "SupplyKeyword", 
      "IfKeyword", "ElseKeyword", "ShardKeyword", "ShardsKeyword", "GlobalKeyword", 
      "AddressKeyword", "AutoKeyword", "MinerKeyword", "StructKeyword", 
      "EnumKeyword", "ContractKeyword", "ImportKeyword", "FunctionKeyword", 
      "PublicKeyword", "ExportKeyword", "AsKeyword", "UsingKeyword", "InterfaceKeyword", 
      "ImplementsKeyword", "DeployKeyword", "ConstructorKeyword", "NextKeyword", 
      "FloatType", "IntType", "UintType", "BooleanLiteral", "DecimalFloatLiteral", 
      "DecimalIntegerLiteral", "DecimalIntegerLiteralBody", "AddressLiteral", 
      "HashLiteral", "HexIntegerLiteral", "HexIntegerLiteralBody", "DecimalBigIntegerLiteral", 
      "HexBigIntegerLiteral", "Identifier", "StringLiteral", "WS", "COMMENT", 
      "LINE_COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,104,842,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,1,0,5,0,112,8,0,
  	10,0,12,0,115,9,0,1,0,1,0,1,0,1,1,1,1,1,2,1,2,1,2,1,2,3,2,126,8,2,1,2,
  	1,2,1,2,3,2,131,8,2,1,2,1,2,1,3,1,3,3,3,137,8,3,1,3,1,3,5,3,141,8,3,10,
  	3,12,3,144,9,3,1,3,1,3,1,4,1,4,1,4,1,4,1,5,4,5,153,8,5,11,5,12,5,154,
  	1,5,3,5,158,8,5,1,6,3,6,161,8,6,1,6,3,6,164,8,6,1,6,1,6,1,6,1,6,1,6,1,
  	6,5,6,172,8,6,10,6,12,6,175,9,6,3,6,177,8,6,1,6,1,6,5,6,181,8,6,10,6,
  	12,6,184,9,6,1,6,1,6,1,7,1,7,1,7,3,7,191,8,7,1,7,1,7,1,8,1,8,1,8,1,8,
  	1,8,1,8,3,8,201,8,8,1,9,3,9,204,8,9,1,9,3,9,207,8,9,1,9,3,9,210,8,9,1,
  	9,1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,12,
  	3,12,227,8,12,1,12,3,12,230,8,12,1,12,1,12,1,12,1,12,1,12,1,12,5,12,238,
  	8,12,10,12,12,12,241,9,12,1,12,1,12,1,13,1,13,1,13,1,13,1,13,1,13,5,13,
  	251,8,13,10,13,12,13,254,9,13,1,13,1,13,1,14,3,14,259,8,14,1,14,3,14,
  	262,8,14,1,14,1,14,1,14,1,14,3,14,268,8,14,1,14,1,14,5,14,272,8,14,10,
  	14,12,14,275,9,14,1,14,1,14,1,15,1,15,1,15,5,15,282,8,15,10,15,12,15,
  	285,9,15,1,15,1,15,1,16,3,16,290,8,16,1,16,3,16,293,8,16,1,16,3,16,296,
  	8,16,1,16,1,16,3,16,300,8,16,1,16,1,16,1,16,1,16,1,16,5,16,307,8,16,10,
  	16,12,16,310,9,16,1,16,3,16,313,8,16,1,17,3,17,316,8,17,1,17,1,17,1,18,
  	1,18,1,18,5,18,323,8,18,10,18,12,18,326,9,18,3,18,328,8,18,1,19,3,19,
  	331,8,19,1,19,1,19,1,19,1,20,1,20,1,21,1,21,1,21,1,22,3,22,342,8,22,1,
  	22,1,22,3,22,346,8,22,1,23,1,23,1,23,3,23,351,8,23,1,24,1,24,1,25,1,25,
  	1,25,1,25,3,25,359,8,25,1,26,1,26,1,27,1,27,1,27,1,27,1,27,1,27,1,27,
  	1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,29,1,29,1,29,1,29,1,29,1,30,1,30,
  	1,30,1,30,1,30,1,31,1,31,1,31,5,31,390,8,31,10,31,12,31,393,9,31,1,31,
  	1,31,1,32,1,32,5,32,399,8,32,10,32,12,32,402,9,32,1,32,1,32,1,33,1,33,
  	1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,3,33,417,8,33,1,34,1,34,
  	1,34,1,35,1,35,5,35,424,8,35,10,35,12,35,427,9,35,1,35,3,35,430,8,35,
  	1,36,1,36,1,36,1,36,1,36,1,36,5,36,438,8,36,10,36,12,36,441,9,36,1,36,
  	1,36,1,37,1,37,1,37,5,37,448,8,37,10,37,12,37,451,9,37,1,37,1,37,1,38,
  	1,38,1,38,1,38,1,38,1,38,1,38,5,38,462,8,38,10,38,12,38,465,9,38,1,38,
  	1,38,1,39,1,39,1,39,1,39,1,39,1,39,5,39,475,8,39,10,39,12,39,478,9,39,
  	1,39,1,39,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,1,40,3,40,492,
  	8,40,1,41,1,41,1,41,1,41,3,41,498,8,41,1,42,1,42,1,42,1,42,5,42,504,8,
  	42,10,42,12,42,507,9,42,3,42,509,8,42,1,42,1,42,3,42,513,8,42,1,42,1,
  	42,5,42,517,8,42,10,42,12,42,520,9,42,1,42,1,42,1,43,1,43,1,43,1,43,1,
  	43,1,43,1,43,3,43,531,8,43,1,44,1,44,1,44,1,44,3,44,537,8,44,1,44,1,44,
  	3,44,541,8,44,1,44,1,44,3,44,545,8,44,1,44,1,44,1,44,5,44,550,8,44,10,
  	44,12,44,553,9,44,1,44,1,44,1,45,1,45,1,45,5,45,560,8,45,10,45,12,45,
  	563,9,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,46,1,46,1,46,1,47,1,47,
  	1,47,1,48,1,48,3,48,580,8,48,1,48,1,48,1,49,1,49,1,49,1,50,1,50,1,50,
  	1,50,3,50,591,8,50,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,
  	1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,
  	1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,
  	1,51,1,51,3,51,633,8,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,
  	1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,
  	1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,
  	1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,
  	1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,
  	1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,
  	1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,
  	1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,
  	1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,
  	1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,
  	1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,
  	1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,
  	1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,5,51,
  	811,8,51,10,51,12,51,814,9,51,1,52,1,52,1,52,1,52,1,52,1,52,1,52,1,52,
  	1,52,1,52,1,52,1,52,3,52,828,8,52,1,53,1,53,1,53,5,53,833,8,53,10,53,
  	12,53,836,9,53,3,53,838,8,53,1,54,1,54,1,54,0,1,102,55,0,2,4,6,8,10,12,
  	14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,
  	60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,
  	106,108,0,5,3,0,90,92,96,96,101,101,3,0,67,67,69,70,89,89,1,0,78,79,3,
  	0,12,16,70,70,87,89,3,0,14,15,70,70,88,89,924,0,113,1,0,0,0,2,119,1,0,
  	0,0,4,121,1,0,0,0,6,134,1,0,0,0,8,147,1,0,0,0,10,157,1,0,0,0,12,160,1,
  	0,0,0,14,190,1,0,0,0,16,200,1,0,0,0,18,203,1,0,0,0,20,215,1,0,0,0,22,
  	222,1,0,0,0,24,226,1,0,0,0,26,244,1,0,0,0,28,258,1,0,0,0,30,278,1,0,0,
  	0,32,289,1,0,0,0,34,315,1,0,0,0,36,327,1,0,0,0,38,330,1,0,0,0,40,335,
  	1,0,0,0,42,337,1,0,0,0,44,341,1,0,0,0,46,350,1,0,0,0,48,352,1,0,0,0,50,
  	358,1,0,0,0,52,360,1,0,0,0,54,362,1,0,0,0,56,369,1,0,0,0,58,376,1,0,0,
  	0,60,381,1,0,0,0,62,391,1,0,0,0,64,396,1,0,0,0,66,416,1,0,0,0,68,418,
  	1,0,0,0,70,421,1,0,0,0,72,431,1,0,0,0,74,444,1,0,0,0,76,454,1,0,0,0,78,
  	468,1,0,0,0,80,481,1,0,0,0,82,497,1,0,0,0,84,499,1,0,0,0,86,530,1,0,0,
  	0,88,532,1,0,0,0,90,556,1,0,0,0,92,571,1,0,0,0,94,574,1,0,0,0,96,577,
  	1,0,0,0,98,583,1,0,0,0,100,586,1,0,0,0,102,632,1,0,0,0,104,827,1,0,0,
  	0,106,837,1,0,0,0,108,839,1,0,0,0,110,112,3,2,1,0,111,110,1,0,0,0,112,
  	115,1,0,0,0,113,111,1,0,0,0,113,114,1,0,0,0,114,116,1,0,0,0,115,113,1,
  	0,0,0,116,117,3,12,6,0,117,118,5,0,0,1,118,1,1,0,0,0,119,120,3,4,2,0,
  	120,3,1,0,0,0,121,125,5,76,0,0,122,123,3,108,54,0,123,124,5,1,0,0,124,
  	126,1,0,0,0,125,122,1,0,0,0,125,126,1,0,0,0,126,127,1,0,0,0,127,130,3,
  	108,54,0,128,129,5,80,0,0,129,131,3,108,54,0,130,128,1,0,0,0,130,131,
  	1,0,0,0,131,132,1,0,0,0,132,133,5,2,0,0,133,5,1,0,0,0,134,136,5,3,0,0,
  	135,137,3,8,4,0,136,135,1,0,0,0,136,137,1,0,0,0,137,142,1,0,0,0,138,139,
  	5,4,0,0,139,141,3,8,4,0,140,138,1,0,0,0,141,144,1,0,0,0,142,140,1,0,0,
  	0,142,143,1,0,0,0,143,145,1,0,0,0,144,142,1,0,0,0,145,146,5,5,0,0,146,
  	7,1,0,0,0,147,148,3,108,54,0,148,149,5,6,0,0,149,150,7,0,0,0,150,9,1,
  	0,0,0,151,153,5,58,0,0,152,151,1,0,0,0,153,154,1,0,0,0,154,152,1,0,0,
  	0,154,155,1,0,0,0,155,158,1,0,0,0,156,158,5,59,0,0,157,152,1,0,0,0,157,
  	156,1,0,0,0,158,11,1,0,0,0,159,161,3,10,5,0,160,159,1,0,0,0,160,161,1,
  	0,0,0,161,163,1,0,0,0,162,164,3,6,3,0,163,162,1,0,0,0,163,164,1,0,0,0,
  	164,165,1,0,0,0,165,166,5,75,0,0,166,176,3,108,54,0,167,168,5,83,0,0,
  	168,173,3,14,7,0,169,170,5,4,0,0,170,172,3,14,7,0,171,169,1,0,0,0,172,
  	175,1,0,0,0,173,171,1,0,0,0,173,174,1,0,0,0,174,177,1,0,0,0,175,173,1,
  	0,0,0,176,167,1,0,0,0,176,177,1,0,0,0,177,178,1,0,0,0,178,182,5,7,0,0,
  	179,181,3,16,8,0,180,179,1,0,0,0,181,184,1,0,0,0,182,180,1,0,0,0,182,
  	183,1,0,0,0,183,185,1,0,0,0,184,182,1,0,0,0,185,186,5,8,0,0,186,13,1,
  	0,0,0,187,188,3,108,54,0,188,189,5,1,0,0,189,191,1,0,0,0,190,187,1,0,
  	0,0,190,191,1,0,0,0,191,192,1,0,0,0,192,193,3,108,54,0,193,15,1,0,0,0,
  	194,201,3,18,9,0,195,201,3,20,10,0,196,201,3,24,12,0,197,201,3,28,14,
  	0,198,201,3,26,13,0,199,201,3,30,15,0,200,194,1,0,0,0,200,195,1,0,0,0,
  	200,196,1,0,0,0,200,197,1,0,0,0,200,198,1,0,0,0,200,199,1,0,0,0,201,17,
  	1,0,0,0,202,204,3,10,5,0,203,202,1,0,0,0,203,204,1,0,0,0,204,206,1,0,
  	0,0,205,207,3,6,3,0,206,205,1,0,0,0,206,207,1,0,0,0,207,209,1,0,0,0,208,
  	210,3,22,11,0,209,208,1,0,0,0,209,210,1,0,0,0,210,211,1,0,0,0,211,212,
  	3,46,23,0,212,213,3,108,54,0,213,214,5,2,0,0,214,19,1,0,0,0,215,216,5,
  	61,0,0,216,217,3,46,23,0,217,218,3,108,54,0,218,219,5,6,0,0,219,220,3,
  	102,51,0,220,221,5,2,0,0,221,21,1,0,0,0,222,223,5,9,0,0,223,224,7,1,0,
  	0,224,23,1,0,0,0,225,227,3,10,5,0,226,225,1,0,0,0,226,227,1,0,0,0,227,
  	229,1,0,0,0,228,230,3,6,3,0,229,228,1,0,0,0,229,230,1,0,0,0,230,231,1,
  	0,0,0,231,232,5,73,0,0,232,233,3,108,54,0,233,239,5,7,0,0,234,235,3,42,
  	21,0,235,236,5,2,0,0,236,238,1,0,0,0,237,234,1,0,0,0,238,241,1,0,0,0,
  	239,237,1,0,0,0,239,240,1,0,0,0,240,242,1,0,0,0,241,239,1,0,0,0,242,243,
  	5,8,0,0,243,25,1,0,0,0,244,245,5,82,0,0,245,246,3,108,54,0,246,252,5,
  	7,0,0,247,248,3,32,16,0,248,249,5,2,0,0,249,251,1,0,0,0,250,247,1,0,0,
  	0,251,254,1,0,0,0,252,250,1,0,0,0,252,253,1,0,0,0,253,255,1,0,0,0,254,
  	252,1,0,0,0,255,256,5,8,0,0,256,27,1,0,0,0,257,259,3,10,5,0,258,257,1,
  	0,0,0,258,259,1,0,0,0,259,261,1,0,0,0,260,262,3,6,3,0,261,260,1,0,0,0,
  	261,262,1,0,0,0,262,263,1,0,0,0,263,264,5,74,0,0,264,265,3,108,54,0,265,
  	267,5,7,0,0,266,268,3,108,54,0,267,266,1,0,0,0,267,268,1,0,0,0,268,273,
  	1,0,0,0,269,270,5,4,0,0,270,272,3,108,54,0,271,269,1,0,0,0,272,275,1,
  	0,0,0,273,271,1,0,0,0,273,274,1,0,0,0,274,276,1,0,0,0,275,273,1,0,0,0,
  	276,277,5,8,0,0,277,29,1,0,0,0,278,279,3,32,16,0,279,283,5,7,0,0,280,
  	282,3,66,33,0,281,280,1,0,0,0,282,285,1,0,0,0,283,281,1,0,0,0,283,284,
  	1,0,0,0,284,286,1,0,0,0,285,283,1,0,0,0,286,287,5,8,0,0,287,31,1,0,0,
  	0,288,290,3,10,5,0,289,288,1,0,0,0,289,290,1,0,0,0,290,292,1,0,0,0,291,
  	293,3,6,3,0,292,291,1,0,0,0,292,293,1,0,0,0,293,295,1,0,0,0,294,296,3,
  	22,11,0,295,294,1,0,0,0,295,296,1,0,0,0,296,297,1,0,0,0,297,299,5,77,
  	0,0,298,300,3,34,17,0,299,298,1,0,0,0,299,300,1,0,0,0,300,301,1,0,0,0,
  	301,302,3,108,54,0,302,303,5,10,0,0,303,304,3,36,18,0,304,308,5,11,0,
  	0,305,307,3,40,20,0,306,305,1,0,0,0,307,310,1,0,0,0,308,306,1,0,0,0,308,
  	309,1,0,0,0,309,312,1,0,0,0,310,308,1,0,0,0,311,313,5,61,0,0,312,311,
  	1,0,0,0,312,313,1,0,0,0,313,33,1,0,0,0,314,316,5,61,0,0,315,314,1,0,0,
  	0,315,316,1,0,0,0,316,317,1,0,0,0,317,318,3,46,23,0,318,35,1,0,0,0,319,
  	324,3,38,19,0,320,321,5,4,0,0,321,323,3,38,19,0,322,320,1,0,0,0,323,326,
  	1,0,0,0,324,322,1,0,0,0,324,325,1,0,0,0,325,328,1,0,0,0,326,324,1,0,0,
  	0,327,319,1,0,0,0,327,328,1,0,0,0,328,37,1,0,0,0,329,331,5,61,0,0,330,
  	329,1,0,0,0,330,331,1,0,0,0,331,332,1,0,0,0,332,333,3,46,23,0,333,334,
  	3,108,54,0,334,39,1,0,0,0,335,336,7,2,0,0,336,41,1,0,0,0,337,338,3,46,
  	23,0,338,339,3,108,54,0,339,43,1,0,0,0,340,342,5,61,0,0,341,340,1,0,0,
  	0,341,342,1,0,0,0,342,345,1,0,0,0,343,346,3,46,23,0,344,346,5,71,0,0,
  	345,343,1,0,0,0,345,344,1,0,0,0,346,45,1,0,0,0,347,351,3,48,24,0,348,
  	351,3,50,25,0,349,351,3,62,31,0,350,347,1,0,0,0,350,348,1,0,0,0,350,349,
  	1,0,0,0,351,47,1,0,0,0,352,353,7,3,0,0,353,49,1,0,0,0,354,359,3,54,27,
  	0,355,359,3,58,29,0,356,359,3,56,28,0,357,359,3,60,30,0,358,354,1,0,0,
  	0,358,355,1,0,0,0,358,356,1,0,0,0,358,357,1,0,0,0,359,51,1,0,0,0,360,
  	361,7,4,0,0,361,53,1,0,0,0,362,363,5,17,0,0,363,364,5,18,0,0,364,365,
  	3,52,26,0,365,366,5,4,0,0,366,367,3,46,23,0,367,368,5,19,0,0,368,55,1,
  	0,0,0,369,370,5,20,0,0,370,371,5,18,0,0,371,372,3,52,26,0,372,373,5,4,
  	0,0,373,374,3,46,23,0,374,375,5,19,0,0,375,57,1,0,0,0,376,377,5,21,0,
  	0,377,378,5,18,0,0,378,379,3,46,23,0,379,380,5,19,0,0,380,59,1,0,0,0,
  	381,382,5,22,0,0,382,383,5,18,0,0,383,384,3,46,23,0,384,385,5,19,0,0,
  	385,61,1,0,0,0,386,387,3,108,54,0,387,388,5,1,0,0,388,390,1,0,0,0,389,
  	386,1,0,0,0,390,393,1,0,0,0,391,389,1,0,0,0,391,392,1,0,0,0,392,394,1,
  	0,0,0,393,391,1,0,0,0,394,395,3,108,54,0,395,63,1,0,0,0,396,400,5,7,0,
  	0,397,399,3,66,33,0,398,397,1,0,0,0,399,402,1,0,0,0,400,398,1,0,0,0,400,
  	401,1,0,0,0,401,403,1,0,0,0,402,400,1,0,0,0,403,404,5,8,0,0,404,65,1,
  	0,0,0,405,417,3,70,35,0,406,417,3,78,39,0,407,417,3,88,44,0,408,417,3,
  	64,32,0,409,417,3,90,45,0,410,417,3,92,46,0,411,417,3,94,47,0,412,417,
  	3,96,48,0,413,417,3,80,40,0,414,417,3,98,49,0,415,417,3,68,34,0,416,405,
  	1,0,0,0,416,406,1,0,0,0,416,407,1,0,0,0,416,408,1,0,0,0,416,409,1,0,0,
  	0,416,410,1,0,0,0,416,411,1,0,0,0,416,412,1,0,0,0,416,413,1,0,0,0,416,
  	414,1,0,0,0,416,415,1,0,0,0,417,67,1,0,0,0,418,419,3,102,51,0,419,420,
  	5,2,0,0,420,69,1,0,0,0,421,425,3,72,36,0,422,424,3,76,38,0,423,422,1,
  	0,0,0,424,427,1,0,0,0,425,423,1,0,0,0,425,426,1,0,0,0,426,429,1,0,0,0,
  	427,425,1,0,0,0,428,430,3,74,37,0,429,428,1,0,0,0,429,430,1,0,0,0,430,
  	71,1,0,0,0,431,432,5,65,0,0,432,433,5,10,0,0,433,434,3,102,51,0,434,435,
  	5,11,0,0,435,439,5,7,0,0,436,438,3,66,33,0,437,436,1,0,0,0,438,441,1,
  	0,0,0,439,437,1,0,0,0,439,440,1,0,0,0,440,442,1,0,0,0,441,439,1,0,0,0,
  	442,443,5,8,0,0,443,73,1,0,0,0,444,445,5,66,0,0,445,449,5,7,0,0,446,448,
  	3,66,33,0,447,446,1,0,0,0,448,451,1,0,0,0,449,447,1,0,0,0,449,450,1,0,
  	0,0,450,452,1,0,0,0,451,449,1,0,0,0,452,453,5,8,0,0,453,75,1,0,0,0,454,
  	455,5,66,0,0,455,456,5,65,0,0,456,457,5,10,0,0,457,458,3,102,51,0,458,
  	459,5,11,0,0,459,463,5,7,0,0,460,462,3,66,33,0,461,460,1,0,0,0,462,465,
  	1,0,0,0,463,461,1,0,0,0,463,464,1,0,0,0,464,466,1,0,0,0,465,463,1,0,0,
  	0,466,467,5,8,0,0,467,77,1,0,0,0,468,469,5,23,0,0,469,470,5,10,0,0,470,
  	471,3,102,51,0,471,472,5,11,0,0,472,476,5,7,0,0,473,475,3,66,33,0,474,
  	473,1,0,0,0,475,478,1,0,0,0,476,474,1,0,0,0,476,477,1,0,0,0,477,479,1,
  	0,0,0,478,476,1,0,0,0,479,480,5,8,0,0,480,79,1,0,0,0,481,482,5,63,0,0,
  	482,483,5,9,0,0,483,491,3,82,41,0,484,485,3,108,54,0,485,486,5,10,0,0,
  	486,487,3,106,53,0,487,488,5,11,0,0,488,489,5,2,0,0,489,492,1,0,0,0,490,
  	492,3,84,42,0,491,484,1,0,0,0,491,490,1,0,0,0,492,81,1,0,0,0,493,498,
  	3,102,51,0,494,498,5,68,0,0,495,498,5,69,0,0,496,498,5,86,0,0,497,493,
  	1,0,0,0,497,494,1,0,0,0,497,495,1,0,0,0,497,496,1,0,0,0,498,83,1,0,0,
  	0,499,508,5,10,0,0,500,505,3,86,43,0,501,502,5,4,0,0,502,504,3,86,43,
  	0,503,501,1,0,0,0,504,507,1,0,0,0,505,503,1,0,0,0,505,506,1,0,0,0,506,
  	509,1,0,0,0,507,505,1,0,0,0,508,500,1,0,0,0,508,509,1,0,0,0,509,510,1,
  	0,0,0,510,512,5,11,0,0,511,513,5,61,0,0,512,511,1,0,0,0,512,513,1,0,0,
  	0,513,514,1,0,0,0,514,518,5,7,0,0,515,517,3,66,33,0,516,515,1,0,0,0,517,
  	520,1,0,0,0,518,516,1,0,0,0,518,519,1,0,0,0,519,521,1,0,0,0,520,518,1,
  	0,0,0,521,522,5,8,0,0,522,85,1,0,0,0,523,524,3,44,22,0,524,525,3,108,
  	54,0,525,526,5,6,0,0,526,527,3,102,51,0,527,531,1,0,0,0,528,529,5,24,
  	0,0,529,531,3,108,54,0,530,523,1,0,0,0,530,528,1,0,0,0,531,87,1,0,0,0,
  	532,533,5,25,0,0,533,536,5,10,0,0,534,537,3,100,50,0,535,537,3,102,51,
  	0,536,534,1,0,0,0,536,535,1,0,0,0,536,537,1,0,0,0,537,538,1,0,0,0,538,
  	540,5,2,0,0,539,541,3,102,51,0,540,539,1,0,0,0,540,541,1,0,0,0,541,542,
  	1,0,0,0,542,544,5,2,0,0,543,545,3,102,51,0,544,543,1,0,0,0,544,545,1,
  	0,0,0,545,546,1,0,0,0,546,547,5,11,0,0,547,551,5,7,0,0,548,550,3,66,33,
  	0,549,548,1,0,0,0,550,553,1,0,0,0,551,549,1,0,0,0,551,552,1,0,0,0,552,
  	554,1,0,0,0,553,551,1,0,0,0,554,555,5,8,0,0,555,89,1,0,0,0,556,557,5,
  	26,0,0,557,561,5,7,0,0,558,560,3,66,33,0,559,558,1,0,0,0,560,563,1,0,
  	0,0,561,559,1,0,0,0,561,562,1,0,0,0,562,564,1,0,0,0,563,561,1,0,0,0,564,
  	565,5,8,0,0,565,566,5,23,0,0,566,567,5,10,0,0,567,568,3,102,51,0,568,
  	569,5,11,0,0,569,570,5,2,0,0,570,91,1,0,0,0,571,572,5,62,0,0,572,573,
  	5,2,0,0,573,93,1,0,0,0,574,575,5,60,0,0,575,576,5,2,0,0,576,95,1,0,0,
  	0,577,579,5,27,0,0,578,580,3,102,51,0,579,578,1,0,0,0,579,580,1,0,0,0,
  	580,581,1,0,0,0,581,582,5,2,0,0,582,97,1,0,0,0,583,584,3,100,50,0,584,
  	585,5,2,0,0,585,99,1,0,0,0,586,587,3,44,22,0,587,590,3,108,54,0,588,589,
  	5,6,0,0,589,591,3,102,51,0,590,588,1,0,0,0,590,591,1,0,0,0,591,101,1,
  	0,0,0,592,593,6,51,-1,0,593,594,5,10,0,0,594,595,3,102,51,0,595,596,5,
  	11,0,0,596,597,6,51,-1,0,597,633,1,0,0,0,598,599,5,28,0,0,599,600,3,102,
  	51,38,600,601,6,51,-1,0,601,633,1,0,0,0,602,603,5,29,0,0,603,604,3,102,
  	51,37,604,605,6,51,-1,0,605,633,1,0,0,0,606,607,5,30,0,0,607,608,3,102,
  	51,36,608,609,6,51,-1,0,609,633,1,0,0,0,610,611,5,31,0,0,611,612,3,102,
  	51,35,612,613,6,51,-1,0,613,633,1,0,0,0,614,615,5,32,0,0,615,616,3,102,
  	51,34,616,617,6,51,-1,0,617,633,1,0,0,0,618,619,5,33,0,0,619,620,3,102,
  	51,33,620,621,6,51,-1,0,621,633,1,0,0,0,622,623,5,84,0,0,623,624,3,102,
  	51,0,624,625,5,10,0,0,625,626,3,106,53,0,626,627,5,11,0,0,627,628,6,51,
  	-1,0,628,633,1,0,0,0,629,630,3,104,52,0,630,631,6,51,-1,0,631,633,1,0,
  	0,0,632,592,1,0,0,0,632,598,1,0,0,0,632,602,1,0,0,0,632,606,1,0,0,0,632,
  	610,1,0,0,0,632,614,1,0,0,0,632,618,1,0,0,0,632,622,1,0,0,0,632,629,1,
  	0,0,0,633,812,1,0,0,0,634,635,10,31,0,0,635,636,5,34,0,0,636,637,3,102,
  	51,32,637,638,6,51,-1,0,638,811,1,0,0,0,639,640,10,30,0,0,640,641,5,35,
  	0,0,641,642,3,102,51,31,642,643,6,51,-1,0,643,811,1,0,0,0,644,645,10,
  	29,0,0,645,646,5,36,0,0,646,647,3,102,51,30,647,648,6,51,-1,0,648,811,
  	1,0,0,0,649,650,10,28,0,0,650,651,5,30,0,0,651,652,3,102,51,29,652,653,
  	6,51,-1,0,653,811,1,0,0,0,654,655,10,27,0,0,655,656,5,31,0,0,656,657,
  	3,102,51,28,657,658,6,51,-1,0,658,811,1,0,0,0,659,660,10,26,0,0,660,661,
  	5,37,0,0,661,662,3,102,51,27,662,663,6,51,-1,0,663,811,1,0,0,0,664,665,
  	10,25,0,0,665,666,5,19,0,0,666,667,5,19,0,0,667,668,3,102,51,26,668,669,
  	6,51,-1,0,669,811,1,0,0,0,670,671,10,24,0,0,671,672,5,18,0,0,672,673,
  	3,102,51,25,673,674,6,51,-1,0,674,811,1,0,0,0,675,676,10,23,0,0,676,677,
  	5,19,0,0,677,678,3,102,51,24,678,679,6,51,-1,0,679,811,1,0,0,0,680,681,
  	10,22,0,0,681,682,5,38,0,0,682,683,3,102,51,23,683,684,6,51,-1,0,684,
  	811,1,0,0,0,685,686,10,21,0,0,686,687,5,39,0,0,687,688,3,102,51,22,688,
  	689,6,51,-1,0,689,811,1,0,0,0,690,691,10,20,0,0,691,692,5,40,0,0,692,
  	693,3,102,51,21,693,694,6,51,-1,0,694,811,1,0,0,0,695,696,10,19,0,0,696,
  	697,5,41,0,0,697,698,3,102,51,20,698,699,6,51,-1,0,699,811,1,0,0,0,700,
  	701,10,18,0,0,701,702,5,42,0,0,702,703,3,102,51,19,703,704,6,51,-1,0,
  	704,811,1,0,0,0,705,706,10,17,0,0,706,707,5,24,0,0,707,708,3,102,51,18,
  	708,709,6,51,-1,0,709,811,1,0,0,0,710,711,10,16,0,0,711,712,5,43,0,0,
  	712,713,3,102,51,17,713,714,6,51,-1,0,714,811,1,0,0,0,715,716,10,15,0,
  	0,716,717,5,44,0,0,717,718,3,102,51,16,718,719,6,51,-1,0,719,811,1,0,
  	0,0,720,721,10,14,0,0,721,722,5,45,0,0,722,723,3,102,51,15,723,724,6,
  	51,-1,0,724,811,1,0,0,0,725,726,10,13,0,0,726,727,5,46,0,0,727,728,3,
  	102,51,0,728,729,5,47,0,0,729,730,3,102,51,14,730,731,6,51,-1,0,731,811,
  	1,0,0,0,732,733,10,12,0,0,733,734,5,6,0,0,734,735,3,102,51,13,735,736,
  	6,51,-1,0,736,811,1,0,0,0,737,738,10,11,0,0,738,739,5,48,0,0,739,740,
  	3,102,51,12,740,741,6,51,-1,0,741,811,1,0,0,0,742,743,10,10,0,0,743,744,
  	5,49,0,0,744,745,3,102,51,11,745,746,6,51,-1,0,746,811,1,0,0,0,747,748,
  	10,9,0,0,748,749,5,50,0,0,749,750,3,102,51,10,750,751,6,51,-1,0,751,811,
  	1,0,0,0,752,753,10,8,0,0,753,754,5,51,0,0,754,755,3,102,51,9,755,756,
  	6,51,-1,0,756,811,1,0,0,0,757,758,10,7,0,0,758,759,5,52,0,0,759,760,3,
  	102,51,8,760,761,6,51,-1,0,761,811,1,0,0,0,762,763,10,6,0,0,763,764,5,
  	53,0,0,764,765,3,102,51,7,765,766,6,51,-1,0,766,811,1,0,0,0,767,768,10,
  	5,0,0,768,769,5,54,0,0,769,770,3,102,51,6,770,771,6,51,-1,0,771,811,1,
  	0,0,0,772,773,10,4,0,0,773,774,5,55,0,0,774,775,3,102,51,5,775,776,6,
  	51,-1,0,776,811,1,0,0,0,777,778,10,3,0,0,778,779,5,56,0,0,779,780,3,102,
  	51,4,780,781,6,51,-1,0,781,811,1,0,0,0,782,783,10,2,0,0,783,784,5,57,
  	0,0,784,785,3,102,51,3,785,786,6,51,-1,0,786,811,1,0,0,0,787,788,10,44,
  	0,0,788,789,5,28,0,0,789,811,6,51,-1,0,790,791,10,43,0,0,791,792,5,29,
  	0,0,792,811,6,51,-1,0,793,794,10,42,0,0,794,795,5,3,0,0,795,796,3,102,
  	51,0,796,797,5,5,0,0,797,798,6,51,-1,0,798,811,1,0,0,0,799,800,10,41,
  	0,0,800,801,5,10,0,0,801,802,3,106,53,0,802,803,5,11,0,0,803,804,6,51,
  	-1,0,804,811,1,0,0,0,805,806,10,40,0,0,806,807,5,1,0,0,807,808,3,108,
  	54,0,808,809,6,51,-1,0,809,811,1,0,0,0,810,634,1,0,0,0,810,639,1,0,0,
  	0,810,644,1,0,0,0,810,649,1,0,0,0,810,654,1,0,0,0,810,659,1,0,0,0,810,
  	664,1,0,0,0,810,670,1,0,0,0,810,675,1,0,0,0,810,680,1,0,0,0,810,685,1,
  	0,0,0,810,690,1,0,0,0,810,695,1,0,0,0,810,700,1,0,0,0,810,705,1,0,0,0,
  	810,710,1,0,0,0,810,715,1,0,0,0,810,720,1,0,0,0,810,725,1,0,0,0,810,732,
  	1,0,0,0,810,737,1,0,0,0,810,742,1,0,0,0,810,747,1,0,0,0,810,752,1,0,0,
  	0,810,757,1,0,0,0,810,762,1,0,0,0,810,767,1,0,0,0,810,772,1,0,0,0,810,
  	777,1,0,0,0,810,782,1,0,0,0,810,787,1,0,0,0,810,790,1,0,0,0,810,793,1,
  	0,0,0,810,799,1,0,0,0,810,805,1,0,0,0,811,814,1,0,0,0,812,810,1,0,0,0,
  	812,813,1,0,0,0,813,103,1,0,0,0,814,812,1,0,0,0,815,828,5,90,0,0,816,
  	828,5,92,0,0,817,828,5,91,0,0,818,828,5,96,0,0,819,828,5,98,0,0,820,828,
  	5,99,0,0,821,828,5,101,0,0,822,828,5,94,0,0,823,828,5,95,0,0,824,828,
  	3,108,54,0,825,828,3,48,24,0,826,828,3,50,25,0,827,815,1,0,0,0,827,816,
  	1,0,0,0,827,817,1,0,0,0,827,818,1,0,0,0,827,819,1,0,0,0,827,820,1,0,0,
  	0,827,821,1,0,0,0,827,822,1,0,0,0,827,823,1,0,0,0,827,824,1,0,0,0,827,
  	825,1,0,0,0,827,826,1,0,0,0,828,105,1,0,0,0,829,834,3,102,51,0,830,831,
  	5,4,0,0,831,833,3,102,51,0,832,830,1,0,0,0,833,836,1,0,0,0,834,832,1,
  	0,0,0,834,835,1,0,0,0,835,838,1,0,0,0,836,834,1,0,0,0,837,829,1,0,0,0,
  	837,838,1,0,0,0,838,107,1,0,0,0,839,840,5,100,0,0,840,109,1,0,0,0,69,
  	113,125,130,136,142,154,157,160,163,173,176,182,190,200,203,206,209,226,
  	229,239,252,258,261,267,273,283,289,292,295,299,308,312,315,324,327,330,
  	341,345,350,358,391,400,416,425,429,439,449,463,476,491,497,505,508,512,
  	518,530,536,540,544,551,561,579,590,632,810,812,827,834,837
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  predaParserStaticData = staticData.release();
}

}

PredaParser::PredaParser(TokenStream *input) : PredaParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

PredaParser::PredaParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  PredaParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *predaParserStaticData->atn, predaParserStaticData->decisionToDFA, predaParserStaticData->sharedContextCache, options);
}

PredaParser::~PredaParser() {
  delete _interpreter;
}

const atn::ATN& PredaParser::getATN() const {
  return *predaParserStaticData->atn;
}

std::string PredaParser::getGrammarFileName() const {
  return "Preda.g4";
}

const std::vector<std::string>& PredaParser::getRuleNames() const {
  return predaParserStaticData->ruleNames;
}

const dfa::Vocabulary& PredaParser::getVocabulary() const {
  return predaParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView PredaParser::getSerializedATN() const {
  return predaParserStaticData->serializedATN;
}


//----------------- PredaSourceContext ------------------------------------------------------------------

PredaParser::PredaSourceContext::PredaSourceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::ContractDefinitionContext* PredaParser::PredaSourceContext::contractDefinition() {
  return getRuleContext<PredaParser::ContractDefinitionContext>(0);
}

tree::TerminalNode* PredaParser::PredaSourceContext::EOF() {
  return getToken(PredaParser::EOF, 0);
}

std::vector<PredaParser::DirectiveContext *> PredaParser::PredaSourceContext::directive() {
  return getRuleContexts<PredaParser::DirectiveContext>();
}

PredaParser::DirectiveContext* PredaParser::PredaSourceContext::directive(size_t i) {
  return getRuleContext<PredaParser::DirectiveContext>(i);
}


size_t PredaParser::PredaSourceContext::getRuleIndex() const {
  return PredaParser::RulePredaSource;
}

void PredaParser::PredaSourceContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPredaSource(this);
}

void PredaParser::PredaSourceContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPredaSource(this);
}


std::any PredaParser::PredaSourceContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitPredaSource(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::PredaSourceContext* PredaParser::predaSource() {
  PredaSourceContext *_localctx = _tracker.createInstance<PredaSourceContext>(_ctx, getState());
  enterRule(_localctx, 0, PredaParser::RulePredaSource);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(113);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PredaParser::ImportKeyword) {
      setState(110);
      directive();
      setState(115);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(116);
    contractDefinition();
    setState(117);
    match(PredaParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DirectiveContext ------------------------------------------------------------------

PredaParser::DirectiveContext::DirectiveContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::ImportDirectiveContext* PredaParser::DirectiveContext::importDirective() {
  return getRuleContext<PredaParser::ImportDirectiveContext>(0);
}


size_t PredaParser::DirectiveContext::getRuleIndex() const {
  return PredaParser::RuleDirective;
}

void PredaParser::DirectiveContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDirective(this);
}

void PredaParser::DirectiveContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDirective(this);
}


std::any PredaParser::DirectiveContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitDirective(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::DirectiveContext* PredaParser::directive() {
  DirectiveContext *_localctx = _tracker.createInstance<DirectiveContext>(_ctx, getState());
  enterRule(_localctx, 2, PredaParser::RuleDirective);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(119);
    importDirective();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportDirectiveContext ------------------------------------------------------------------

PredaParser::ImportDirectiveContext::ImportDirectiveContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaParser::ImportDirectiveContext::ImportKeyword() {
  return getToken(PredaParser::ImportKeyword, 0);
}

std::vector<PredaParser::IdentifierContext *> PredaParser::ImportDirectiveContext::identifier() {
  return getRuleContexts<PredaParser::IdentifierContext>();
}

PredaParser::IdentifierContext* PredaParser::ImportDirectiveContext::identifier(size_t i) {
  return getRuleContext<PredaParser::IdentifierContext>(i);
}

tree::TerminalNode* PredaParser::ImportDirectiveContext::AsKeyword() {
  return getToken(PredaParser::AsKeyword, 0);
}


size_t PredaParser::ImportDirectiveContext::getRuleIndex() const {
  return PredaParser::RuleImportDirective;
}

void PredaParser::ImportDirectiveContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportDirective(this);
}

void PredaParser::ImportDirectiveContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportDirective(this);
}


std::any PredaParser::ImportDirectiveContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitImportDirective(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::ImportDirectiveContext* PredaParser::importDirective() {
  ImportDirectiveContext *_localctx = _tracker.createInstance<ImportDirectiveContext>(_ctx, getState());
  enterRule(_localctx, 4, PredaParser::RuleImportDirective);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(121);
    match(PredaParser::ImportKeyword);
    setState(125);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      setState(122);
      antlrcpp::downCast<ImportDirectiveContext *>(_localctx)->dAppName = identifier();
      setState(123);
      match(PredaParser::T__0);
      break;
    }

    default:
      break;
    }
    setState(127);
    antlrcpp::downCast<ImportDirectiveContext *>(_localctx)->contractName = identifier();
    setState(130);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaParser::AsKeyword) {
      setState(128);
      match(PredaParser::AsKeyword);
      setState(129);
      antlrcpp::downCast<ImportDirectiveContext *>(_localctx)->alias = identifier();
    }
    setState(132);
    match(PredaParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AnnotationContext ------------------------------------------------------------------

PredaParser::AnnotationContext::AnnotationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PredaParser::AnnotationItemContext *> PredaParser::AnnotationContext::annotationItem() {
  return getRuleContexts<PredaParser::AnnotationItemContext>();
}

PredaParser::AnnotationItemContext* PredaParser::AnnotationContext::annotationItem(size_t i) {
  return getRuleContext<PredaParser::AnnotationItemContext>(i);
}


size_t PredaParser::AnnotationContext::getRuleIndex() const {
  return PredaParser::RuleAnnotation;
}

void PredaParser::AnnotationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAnnotation(this);
}

void PredaParser::AnnotationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAnnotation(this);
}


std::any PredaParser::AnnotationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitAnnotation(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::AnnotationContext* PredaParser::annotation() {
  AnnotationContext *_localctx = _tracker.createInstance<AnnotationContext>(_ctx, getState());
  enterRule(_localctx, 6, PredaParser::RuleAnnotation);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(134);
    match(PredaParser::T__2);
    setState(136);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaParser::Identifier) {
      setState(135);
      annotationItem();
    }
    setState(142);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PredaParser::T__3) {
      setState(138);
      match(PredaParser::T__3);
      setState(139);
      annotationItem();
      setState(144);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(145);
    match(PredaParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AnnotationItemContext ------------------------------------------------------------------

PredaParser::AnnotationItemContext::AnnotationItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::IdentifierContext* PredaParser::AnnotationItemContext::identifier() {
  return getRuleContext<PredaParser::IdentifierContext>(0);
}

tree::TerminalNode* PredaParser::AnnotationItemContext::BooleanLiteral() {
  return getToken(PredaParser::BooleanLiteral, 0);
}

tree::TerminalNode* PredaParser::AnnotationItemContext::DecimalIntegerLiteral() {
  return getToken(PredaParser::DecimalIntegerLiteral, 0);
}

tree::TerminalNode* PredaParser::AnnotationItemContext::DecimalFloatLiteral() {
  return getToken(PredaParser::DecimalFloatLiteral, 0);
}

tree::TerminalNode* PredaParser::AnnotationItemContext::HexIntegerLiteral() {
  return getToken(PredaParser::HexIntegerLiteral, 0);
}

tree::TerminalNode* PredaParser::AnnotationItemContext::StringLiteral() {
  return getToken(PredaParser::StringLiteral, 0);
}


size_t PredaParser::AnnotationItemContext::getRuleIndex() const {
  return PredaParser::RuleAnnotationItem;
}

void PredaParser::AnnotationItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAnnotationItem(this);
}

void PredaParser::AnnotationItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAnnotationItem(this);
}


std::any PredaParser::AnnotationItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitAnnotationItem(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::AnnotationItemContext* PredaParser::annotationItem() {
  AnnotationItemContext *_localctx = _tracker.createInstance<AnnotationItemContext>(_ctx, getState());
  enterRule(_localctx, 8, PredaParser::RuleAnnotationItem);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(147);
    identifier();
    setState(148);
    match(PredaParser::T__5);
    setState(149);
    _la = _input->LA(1);
    if (!(((((_la - 90) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 90)) & 2119) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DoxygenContext ------------------------------------------------------------------

PredaParser::DoxygenContext::DoxygenContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> PredaParser::DoxygenContext::DoxygenSingle() {
  return getTokens(PredaParser::DoxygenSingle);
}

tree::TerminalNode* PredaParser::DoxygenContext::DoxygenSingle(size_t i) {
  return getToken(PredaParser::DoxygenSingle, i);
}

tree::TerminalNode* PredaParser::DoxygenContext::DoxygenMulti() {
  return getToken(PredaParser::DoxygenMulti, 0);
}


size_t PredaParser::DoxygenContext::getRuleIndex() const {
  return PredaParser::RuleDoxygen;
}

void PredaParser::DoxygenContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDoxygen(this);
}

void PredaParser::DoxygenContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDoxygen(this);
}


std::any PredaParser::DoxygenContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitDoxygen(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::DoxygenContext* PredaParser::doxygen() {
  DoxygenContext *_localctx = _tracker.createInstance<DoxygenContext>(_ctx, getState());
  enterRule(_localctx, 10, PredaParser::RuleDoxygen);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(157);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaParser::DoxygenSingle: {
        enterOuterAlt(_localctx, 1);
        setState(152); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(151);
          match(PredaParser::DoxygenSingle);
          setState(154); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == PredaParser::DoxygenSingle);
        break;
      }

      case PredaParser::DoxygenMulti: {
        enterOuterAlt(_localctx, 2);
        setState(156);
        match(PredaParser::DoxygenMulti);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ContractDefinitionContext ------------------------------------------------------------------

PredaParser::ContractDefinitionContext::ContractDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaParser::ContractDefinitionContext::ContractKeyword() {
  return getToken(PredaParser::ContractKeyword, 0);
}

PredaParser::IdentifierContext* PredaParser::ContractDefinitionContext::identifier() {
  return getRuleContext<PredaParser::IdentifierContext>(0);
}

PredaParser::DoxygenContext* PredaParser::ContractDefinitionContext::doxygen() {
  return getRuleContext<PredaParser::DoxygenContext>(0);
}

PredaParser::AnnotationContext* PredaParser::ContractDefinitionContext::annotation() {
  return getRuleContext<PredaParser::AnnotationContext>(0);
}

tree::TerminalNode* PredaParser::ContractDefinitionContext::ImplementsKeyword() {
  return getToken(PredaParser::ImplementsKeyword, 0);
}

std::vector<PredaParser::InterfaceRefContext *> PredaParser::ContractDefinitionContext::interfaceRef() {
  return getRuleContexts<PredaParser::InterfaceRefContext>();
}

PredaParser::InterfaceRefContext* PredaParser::ContractDefinitionContext::interfaceRef(size_t i) {
  return getRuleContext<PredaParser::InterfaceRefContext>(i);
}

std::vector<PredaParser::ContractPartContext *> PredaParser::ContractDefinitionContext::contractPart() {
  return getRuleContexts<PredaParser::ContractPartContext>();
}

PredaParser::ContractPartContext* PredaParser::ContractDefinitionContext::contractPart(size_t i) {
  return getRuleContext<PredaParser::ContractPartContext>(i);
}


size_t PredaParser::ContractDefinitionContext::getRuleIndex() const {
  return PredaParser::RuleContractDefinition;
}

void PredaParser::ContractDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContractDefinition(this);
}

void PredaParser::ContractDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContractDefinition(this);
}


std::any PredaParser::ContractDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitContractDefinition(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::ContractDefinitionContext* PredaParser::contractDefinition() {
  ContractDefinitionContext *_localctx = _tracker.createInstance<ContractDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 12, PredaParser::RuleContractDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(160);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaParser::DoxygenSingle

    || _la == PredaParser::DoxygenMulti) {
      setState(159);
      doxygen();
    }
    setState(163);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaParser::T__2) {
      setState(162);
      annotation();
    }
    setState(165);
    match(PredaParser::ContractKeyword);
    setState(166);
    identifier();
    setState(176);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaParser::ImplementsKeyword) {
      setState(167);
      match(PredaParser::ImplementsKeyword);
      setState(168);
      interfaceRef();
      setState(173);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == PredaParser::T__3) {
        setState(169);
        match(PredaParser::T__3);
        setState(170);
        interfaceRef();
        setState(175);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(178);
    match(PredaParser::T__6);
    setState(182);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3170534137676427784) != 0) || ((((_la - 70) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 70)) & 1074663577) != 0)) {
      setState(179);
      contractPart();
      setState(184);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(185);
    match(PredaParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InterfaceRefContext ------------------------------------------------------------------

PredaParser::InterfaceRefContext::InterfaceRefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PredaParser::IdentifierContext *> PredaParser::InterfaceRefContext::identifier() {
  return getRuleContexts<PredaParser::IdentifierContext>();
}

PredaParser::IdentifierContext* PredaParser::InterfaceRefContext::identifier(size_t i) {
  return getRuleContext<PredaParser::IdentifierContext>(i);
}


size_t PredaParser::InterfaceRefContext::getRuleIndex() const {
  return PredaParser::RuleInterfaceRef;
}

void PredaParser::InterfaceRefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInterfaceRef(this);
}

void PredaParser::InterfaceRefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInterfaceRef(this);
}


std::any PredaParser::InterfaceRefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitInterfaceRef(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::InterfaceRefContext* PredaParser::interfaceRef() {
  InterfaceRefContext *_localctx = _tracker.createInstance<InterfaceRefContext>(_ctx, getState());
  enterRule(_localctx, 14, PredaParser::RuleInterfaceRef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(190);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      setState(187);
      antlrcpp::downCast<InterfaceRefContext *>(_localctx)->contractName = identifier();
      setState(188);
      match(PredaParser::T__0);
      break;
    }

    default:
      break;
    }
    setState(192);
    antlrcpp::downCast<InterfaceRefContext *>(_localctx)->interfaceName = identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ContractPartContext ------------------------------------------------------------------

PredaParser::ContractPartContext::ContractPartContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::StateVariableDeclarationContext* PredaParser::ContractPartContext::stateVariableDeclaration() {
  return getRuleContext<PredaParser::StateVariableDeclarationContext>(0);
}

PredaParser::ConstVariableDeclarationContext* PredaParser::ContractPartContext::constVariableDeclaration() {
  return getRuleContext<PredaParser::ConstVariableDeclarationContext>(0);
}

PredaParser::StructDefinitionContext* PredaParser::ContractPartContext::structDefinition() {
  return getRuleContext<PredaParser::StructDefinitionContext>(0);
}

PredaParser::EnumDefinitionContext* PredaParser::ContractPartContext::enumDefinition() {
  return getRuleContext<PredaParser::EnumDefinitionContext>(0);
}

PredaParser::InterfaceDefinitionContext* PredaParser::ContractPartContext::interfaceDefinition() {
  return getRuleContext<PredaParser::InterfaceDefinitionContext>(0);
}

PredaParser::FunctionDefinitionContext* PredaParser::ContractPartContext::functionDefinition() {
  return getRuleContext<PredaParser::FunctionDefinitionContext>(0);
}


size_t PredaParser::ContractPartContext::getRuleIndex() const {
  return PredaParser::RuleContractPart;
}

void PredaParser::ContractPartContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContractPart(this);
}

void PredaParser::ContractPartContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContractPart(this);
}


std::any PredaParser::ContractPartContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitContractPart(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::ContractPartContext* PredaParser::contractPart() {
  ContractPartContext *_localctx = _tracker.createInstance<ContractPartContext>(_ctx, getState());
  enterRule(_localctx, 16, PredaParser::RuleContractPart);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(200);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(194);
      stateVariableDeclaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(195);
      constVariableDeclaration();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(196);
      structDefinition();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(197);
      enumDefinition();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(198);
      interfaceDefinition();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(199);
      functionDefinition();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StateVariableDeclarationContext ------------------------------------------------------------------

PredaParser::StateVariableDeclarationContext::StateVariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::TypeNameContext* PredaParser::StateVariableDeclarationContext::typeName() {
  return getRuleContext<PredaParser::TypeNameContext>(0);
}

PredaParser::IdentifierContext* PredaParser::StateVariableDeclarationContext::identifier() {
  return getRuleContext<PredaParser::IdentifierContext>(0);
}

PredaParser::DoxygenContext* PredaParser::StateVariableDeclarationContext::doxygen() {
  return getRuleContext<PredaParser::DoxygenContext>(0);
}

PredaParser::AnnotationContext* PredaParser::StateVariableDeclarationContext::annotation() {
  return getRuleContext<PredaParser::AnnotationContext>(0);
}

PredaParser::ScopeContext* PredaParser::StateVariableDeclarationContext::scope() {
  return getRuleContext<PredaParser::ScopeContext>(0);
}


size_t PredaParser::StateVariableDeclarationContext::getRuleIndex() const {
  return PredaParser::RuleStateVariableDeclaration;
}

void PredaParser::StateVariableDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStateVariableDeclaration(this);
}

void PredaParser::StateVariableDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStateVariableDeclaration(this);
}


std::any PredaParser::StateVariableDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitStateVariableDeclaration(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::StateVariableDeclarationContext* PredaParser::stateVariableDeclaration() {
  StateVariableDeclarationContext *_localctx = _tracker.createInstance<StateVariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 18, PredaParser::RuleStateVariableDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(203);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaParser::DoxygenSingle

    || _la == PredaParser::DoxygenMulti) {
      setState(202);
      doxygen();
    }
    setState(206);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaParser::T__2) {
      setState(205);
      annotation();
    }
    setState(209);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaParser::T__8) {
      setState(208);
      scope();
    }
    setState(211);
    typeName();
    setState(212);
    identifier();
    setState(213);
    match(PredaParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstVariableDeclarationContext ------------------------------------------------------------------

PredaParser::ConstVariableDeclarationContext::ConstVariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaParser::ConstVariableDeclarationContext::ConstantKeyword() {
  return getToken(PredaParser::ConstantKeyword, 0);
}

PredaParser::TypeNameContext* PredaParser::ConstVariableDeclarationContext::typeName() {
  return getRuleContext<PredaParser::TypeNameContext>(0);
}

PredaParser::IdentifierContext* PredaParser::ConstVariableDeclarationContext::identifier() {
  return getRuleContext<PredaParser::IdentifierContext>(0);
}

PredaParser::ExpressionContext* PredaParser::ConstVariableDeclarationContext::expression() {
  return getRuleContext<PredaParser::ExpressionContext>(0);
}


size_t PredaParser::ConstVariableDeclarationContext::getRuleIndex() const {
  return PredaParser::RuleConstVariableDeclaration;
}

void PredaParser::ConstVariableDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstVariableDeclaration(this);
}

void PredaParser::ConstVariableDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstVariableDeclaration(this);
}


std::any PredaParser::ConstVariableDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitConstVariableDeclaration(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::ConstVariableDeclarationContext* PredaParser::constVariableDeclaration() {
  ConstVariableDeclarationContext *_localctx = _tracker.createInstance<ConstVariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 20, PredaParser::RuleConstVariableDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(215);
    match(PredaParser::ConstantKeyword);
    setState(216);
    typeName();
    setState(217);
    identifier();
    setState(218);
    match(PredaParser::T__5);
    setState(219);
    expression(0);
    setState(220);
    match(PredaParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ScopeContext ------------------------------------------------------------------

PredaParser::ScopeContext::ScopeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaParser::ScopeContext::ShardKeyword() {
  return getToken(PredaParser::ShardKeyword, 0);
}

tree::TerminalNode* PredaParser::ScopeContext::GlobalKeyword() {
  return getToken(PredaParser::GlobalKeyword, 0);
}

tree::TerminalNode* PredaParser::ScopeContext::AddressKeyword() {
  return getToken(PredaParser::AddressKeyword, 0);
}

tree::TerminalNode* PredaParser::ScopeContext::UintType() {
  return getToken(PredaParser::UintType, 0);
}


size_t PredaParser::ScopeContext::getRuleIndex() const {
  return PredaParser::RuleScope;
}

void PredaParser::ScopeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterScope(this);
}

void PredaParser::ScopeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitScope(this);
}


std::any PredaParser::ScopeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitScope(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::ScopeContext* PredaParser::scope() {
  ScopeContext *_localctx = _tracker.createInstance<ScopeContext>(_ctx, getState());
  enterRule(_localctx, 22, PredaParser::RuleScope);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(222);
    match(PredaParser::T__8);
    setState(223);
    _la = _input->LA(1);
    if (!(((((_la - 67) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 67)) & 4194317) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructDefinitionContext ------------------------------------------------------------------

PredaParser::StructDefinitionContext::StructDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaParser::StructDefinitionContext::StructKeyword() {
  return getToken(PredaParser::StructKeyword, 0);
}

PredaParser::IdentifierContext* PredaParser::StructDefinitionContext::identifier() {
  return getRuleContext<PredaParser::IdentifierContext>(0);
}

PredaParser::DoxygenContext* PredaParser::StructDefinitionContext::doxygen() {
  return getRuleContext<PredaParser::DoxygenContext>(0);
}

PredaParser::AnnotationContext* PredaParser::StructDefinitionContext::annotation() {
  return getRuleContext<PredaParser::AnnotationContext>(0);
}

std::vector<PredaParser::VariableDeclarationContext *> PredaParser::StructDefinitionContext::variableDeclaration() {
  return getRuleContexts<PredaParser::VariableDeclarationContext>();
}

PredaParser::VariableDeclarationContext* PredaParser::StructDefinitionContext::variableDeclaration(size_t i) {
  return getRuleContext<PredaParser::VariableDeclarationContext>(i);
}


size_t PredaParser::StructDefinitionContext::getRuleIndex() const {
  return PredaParser::RuleStructDefinition;
}

void PredaParser::StructDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructDefinition(this);
}

void PredaParser::StructDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructDefinition(this);
}


std::any PredaParser::StructDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitStructDefinition(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::StructDefinitionContext* PredaParser::structDefinition() {
  StructDefinitionContext *_localctx = _tracker.createInstance<StructDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 24, PredaParser::RuleStructDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(226);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaParser::DoxygenSingle

    || _la == PredaParser::DoxygenMulti) {
      setState(225);
      doxygen();
    }
    setState(229);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaParser::T__2) {
      setState(228);
      annotation();
    }
    setState(231);
    match(PredaParser::StructKeyword);
    setState(232);
    identifier();
    setState(233);
    match(PredaParser::T__6);
    setState(239);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7598080) != 0) || ((((_la - 70) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 70)) & 1074659329) != 0)) {
      setState(234);
      variableDeclaration();
      setState(235);
      match(PredaParser::T__1);
      setState(241);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(242);
    match(PredaParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InterfaceDefinitionContext ------------------------------------------------------------------

PredaParser::InterfaceDefinitionContext::InterfaceDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaParser::InterfaceDefinitionContext::InterfaceKeyword() {
  return getToken(PredaParser::InterfaceKeyword, 0);
}

PredaParser::IdentifierContext* PredaParser::InterfaceDefinitionContext::identifier() {
  return getRuleContext<PredaParser::IdentifierContext>(0);
}

std::vector<PredaParser::FunctionDeclarationContext *> PredaParser::InterfaceDefinitionContext::functionDeclaration() {
  return getRuleContexts<PredaParser::FunctionDeclarationContext>();
}

PredaParser::FunctionDeclarationContext* PredaParser::InterfaceDefinitionContext::functionDeclaration(size_t i) {
  return getRuleContext<PredaParser::FunctionDeclarationContext>(i);
}


size_t PredaParser::InterfaceDefinitionContext::getRuleIndex() const {
  return PredaParser::RuleInterfaceDefinition;
}

void PredaParser::InterfaceDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInterfaceDefinition(this);
}

void PredaParser::InterfaceDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInterfaceDefinition(this);
}


std::any PredaParser::InterfaceDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitInterfaceDefinition(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::InterfaceDefinitionContext* PredaParser::interfaceDefinition() {
  InterfaceDefinitionContext *_localctx = _tracker.createInstance<InterfaceDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 26, PredaParser::RuleInterfaceDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(244);
    match(PredaParser::InterfaceKeyword);
    setState(245);
    identifier();
    setState(246);
    match(PredaParser::T__6);
    setState(252);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 864691128455135752) != 0) || _la == PredaParser::FunctionKeyword) {
      setState(247);
      functionDeclaration();
      setState(248);
      match(PredaParser::T__1);
      setState(254);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(255);
    match(PredaParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EnumDefinitionContext ------------------------------------------------------------------

PredaParser::EnumDefinitionContext::EnumDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaParser::EnumDefinitionContext::EnumKeyword() {
  return getToken(PredaParser::EnumKeyword, 0);
}

std::vector<PredaParser::IdentifierContext *> PredaParser::EnumDefinitionContext::identifier() {
  return getRuleContexts<PredaParser::IdentifierContext>();
}

PredaParser::IdentifierContext* PredaParser::EnumDefinitionContext::identifier(size_t i) {
  return getRuleContext<PredaParser::IdentifierContext>(i);
}

PredaParser::DoxygenContext* PredaParser::EnumDefinitionContext::doxygen() {
  return getRuleContext<PredaParser::DoxygenContext>(0);
}

PredaParser::AnnotationContext* PredaParser::EnumDefinitionContext::annotation() {
  return getRuleContext<PredaParser::AnnotationContext>(0);
}


size_t PredaParser::EnumDefinitionContext::getRuleIndex() const {
  return PredaParser::RuleEnumDefinition;
}

void PredaParser::EnumDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEnumDefinition(this);
}

void PredaParser::EnumDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEnumDefinition(this);
}


std::any PredaParser::EnumDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitEnumDefinition(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::EnumDefinitionContext* PredaParser::enumDefinition() {
  EnumDefinitionContext *_localctx = _tracker.createInstance<EnumDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 28, PredaParser::RuleEnumDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(258);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaParser::DoxygenSingle

    || _la == PredaParser::DoxygenMulti) {
      setState(257);
      doxygen();
    }
    setState(261);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaParser::T__2) {
      setState(260);
      annotation();
    }
    setState(263);
    match(PredaParser::EnumKeyword);
    setState(264);
    identifier();
    setState(265);
    match(PredaParser::T__6);
    setState(267);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaParser::Identifier) {
      setState(266);
      identifier();
    }
    setState(273);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PredaParser::T__3) {
      setState(269);
      match(PredaParser::T__3);
      setState(270);
      identifier();
      setState(275);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(276);
    match(PredaParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDefinitionContext ------------------------------------------------------------------

PredaParser::FunctionDefinitionContext::FunctionDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::FunctionDeclarationContext* PredaParser::FunctionDefinitionContext::functionDeclaration() {
  return getRuleContext<PredaParser::FunctionDeclarationContext>(0);
}

std::vector<PredaParser::StatementContext *> PredaParser::FunctionDefinitionContext::statement() {
  return getRuleContexts<PredaParser::StatementContext>();
}

PredaParser::StatementContext* PredaParser::FunctionDefinitionContext::statement(size_t i) {
  return getRuleContext<PredaParser::StatementContext>(i);
}


size_t PredaParser::FunctionDefinitionContext::getRuleIndex() const {
  return PredaParser::RuleFunctionDefinition;
}

void PredaParser::FunctionDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionDefinition(this);
}

void PredaParser::FunctionDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionDefinition(this);
}


std::any PredaParser::FunctionDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitFunctionDefinition(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::FunctionDefinitionContext* PredaParser::functionDefinition() {
  FunctionDefinitionContext *_localctx = _tracker.createInstance<FunctionDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 30, PredaParser::RuleFunctionDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(278);
    functionDeclaration();
    setState(279);
    match(PredaParser::T__6);
    setState(283);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -1152921487444544384) != 0) || ((((_la - 65) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 65)) & 132871880801) != 0)) {
      setState(280);
      statement();
      setState(285);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(286);
    match(PredaParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDeclarationContext ------------------------------------------------------------------

PredaParser::FunctionDeclarationContext::FunctionDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaParser::FunctionDeclarationContext::FunctionKeyword() {
  return getToken(PredaParser::FunctionKeyword, 0);
}

PredaParser::IdentifierContext* PredaParser::FunctionDeclarationContext::identifier() {
  return getRuleContext<PredaParser::IdentifierContext>(0);
}

PredaParser::FunctionParameterListContext* PredaParser::FunctionDeclarationContext::functionParameterList() {
  return getRuleContext<PredaParser::FunctionParameterListContext>(0);
}

PredaParser::DoxygenContext* PredaParser::FunctionDeclarationContext::doxygen() {
  return getRuleContext<PredaParser::DoxygenContext>(0);
}

PredaParser::AnnotationContext* PredaParser::FunctionDeclarationContext::annotation() {
  return getRuleContext<PredaParser::AnnotationContext>(0);
}

PredaParser::ScopeContext* PredaParser::FunctionDeclarationContext::scope() {
  return getRuleContext<PredaParser::ScopeContext>(0);
}

PredaParser::FunctionReturnTypeNameContext* PredaParser::FunctionDeclarationContext::functionReturnTypeName() {
  return getRuleContext<PredaParser::FunctionReturnTypeNameContext>(0);
}

std::vector<PredaParser::AccessSpecifierContext *> PredaParser::FunctionDeclarationContext::accessSpecifier() {
  return getRuleContexts<PredaParser::AccessSpecifierContext>();
}

PredaParser::AccessSpecifierContext* PredaParser::FunctionDeclarationContext::accessSpecifier(size_t i) {
  return getRuleContext<PredaParser::AccessSpecifierContext>(i);
}

tree::TerminalNode* PredaParser::FunctionDeclarationContext::ConstantKeyword() {
  return getToken(PredaParser::ConstantKeyword, 0);
}


size_t PredaParser::FunctionDeclarationContext::getRuleIndex() const {
  return PredaParser::RuleFunctionDeclaration;
}

void PredaParser::FunctionDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionDeclaration(this);
}

void PredaParser::FunctionDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionDeclaration(this);
}


std::any PredaParser::FunctionDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitFunctionDeclaration(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::FunctionDeclarationContext* PredaParser::functionDeclaration() {
  FunctionDeclarationContext *_localctx = _tracker.createInstance<FunctionDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 32, PredaParser::RuleFunctionDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(289);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaParser::DoxygenSingle

    || _la == PredaParser::DoxygenMulti) {
      setState(288);
      doxygen();
    }
    setState(292);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaParser::T__2) {
      setState(291);
      annotation();
    }
    setState(295);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaParser::T__8) {
      setState(294);
      scope();
    }
    setState(297);
    match(PredaParser::FunctionKeyword);
    setState(299);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
    case 1: {
      setState(298);
      functionReturnTypeName();
      break;
    }

    default:
      break;
    }
    setState(301);
    identifier();
    setState(302);
    match(PredaParser::T__9);
    setState(303);
    functionParameterList();
    setState(304);
    match(PredaParser::T__10);
    setState(308);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PredaParser::PublicKeyword

    || _la == PredaParser::ExportKeyword) {
      setState(305);
      accessSpecifier();
      setState(310);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(312);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaParser::ConstantKeyword) {
      setState(311);
      match(PredaParser::ConstantKeyword);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionReturnTypeNameContext ------------------------------------------------------------------

PredaParser::FunctionReturnTypeNameContext::FunctionReturnTypeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::TypeNameContext* PredaParser::FunctionReturnTypeNameContext::typeName() {
  return getRuleContext<PredaParser::TypeNameContext>(0);
}

tree::TerminalNode* PredaParser::FunctionReturnTypeNameContext::ConstantKeyword() {
  return getToken(PredaParser::ConstantKeyword, 0);
}


size_t PredaParser::FunctionReturnTypeNameContext::getRuleIndex() const {
  return PredaParser::RuleFunctionReturnTypeName;
}

void PredaParser::FunctionReturnTypeNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionReturnTypeName(this);
}

void PredaParser::FunctionReturnTypeNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionReturnTypeName(this);
}


std::any PredaParser::FunctionReturnTypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitFunctionReturnTypeName(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::FunctionReturnTypeNameContext* PredaParser::functionReturnTypeName() {
  FunctionReturnTypeNameContext *_localctx = _tracker.createInstance<FunctionReturnTypeNameContext>(_ctx, getState());
  enterRule(_localctx, 34, PredaParser::RuleFunctionReturnTypeName);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(315);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaParser::ConstantKeyword) {
      setState(314);
      match(PredaParser::ConstantKeyword);
    }
    setState(317);
    typeName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionParameterListContext ------------------------------------------------------------------

PredaParser::FunctionParameterListContext::FunctionParameterListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PredaParser::FunctionParameterContext *> PredaParser::FunctionParameterListContext::functionParameter() {
  return getRuleContexts<PredaParser::FunctionParameterContext>();
}

PredaParser::FunctionParameterContext* PredaParser::FunctionParameterListContext::functionParameter(size_t i) {
  return getRuleContext<PredaParser::FunctionParameterContext>(i);
}


size_t PredaParser::FunctionParameterListContext::getRuleIndex() const {
  return PredaParser::RuleFunctionParameterList;
}

void PredaParser::FunctionParameterListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionParameterList(this);
}

void PredaParser::FunctionParameterListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionParameterList(this);
}


std::any PredaParser::FunctionParameterListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitFunctionParameterList(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::FunctionParameterListContext* PredaParser::functionParameterList() {
  FunctionParameterListContext *_localctx = _tracker.createInstance<FunctionParameterListContext>(_ctx, getState());
  enterRule(_localctx, 36, PredaParser::RuleFunctionParameterList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(327);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2305843009221292032) != 0) || ((((_la - 70) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 70)) & 1074659329) != 0)) {
      setState(319);
      functionParameter();
      setState(324);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == PredaParser::T__3) {
        setState(320);
        match(PredaParser::T__3);
        setState(321);
        functionParameter();
        setState(326);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionParameterContext ------------------------------------------------------------------

PredaParser::FunctionParameterContext::FunctionParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::TypeNameContext* PredaParser::FunctionParameterContext::typeName() {
  return getRuleContext<PredaParser::TypeNameContext>(0);
}

PredaParser::IdentifierContext* PredaParser::FunctionParameterContext::identifier() {
  return getRuleContext<PredaParser::IdentifierContext>(0);
}

tree::TerminalNode* PredaParser::FunctionParameterContext::ConstantKeyword() {
  return getToken(PredaParser::ConstantKeyword, 0);
}


size_t PredaParser::FunctionParameterContext::getRuleIndex() const {
  return PredaParser::RuleFunctionParameter;
}

void PredaParser::FunctionParameterContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionParameter(this);
}

void PredaParser::FunctionParameterContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionParameter(this);
}


std::any PredaParser::FunctionParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitFunctionParameter(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::FunctionParameterContext* PredaParser::functionParameter() {
  FunctionParameterContext *_localctx = _tracker.createInstance<FunctionParameterContext>(_ctx, getState());
  enterRule(_localctx, 38, PredaParser::RuleFunctionParameter);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(330);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaParser::ConstantKeyword) {
      setState(329);
      match(PredaParser::ConstantKeyword);
    }
    setState(332);
    typeName();
    setState(333);
    identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AccessSpecifierContext ------------------------------------------------------------------

PredaParser::AccessSpecifierContext::AccessSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaParser::AccessSpecifierContext::PublicKeyword() {
  return getToken(PredaParser::PublicKeyword, 0);
}

tree::TerminalNode* PredaParser::AccessSpecifierContext::ExportKeyword() {
  return getToken(PredaParser::ExportKeyword, 0);
}


size_t PredaParser::AccessSpecifierContext::getRuleIndex() const {
  return PredaParser::RuleAccessSpecifier;
}

void PredaParser::AccessSpecifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAccessSpecifier(this);
}

void PredaParser::AccessSpecifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAccessSpecifier(this);
}


std::any PredaParser::AccessSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitAccessSpecifier(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::AccessSpecifierContext* PredaParser::accessSpecifier() {
  AccessSpecifierContext *_localctx = _tracker.createInstance<AccessSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 40, PredaParser::RuleAccessSpecifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(335);
    _la = _input->LA(1);
    if (!(_la == PredaParser::PublicKeyword

    || _la == PredaParser::ExportKeyword)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationContext ------------------------------------------------------------------

PredaParser::VariableDeclarationContext::VariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::TypeNameContext* PredaParser::VariableDeclarationContext::typeName() {
  return getRuleContext<PredaParser::TypeNameContext>(0);
}

PredaParser::IdentifierContext* PredaParser::VariableDeclarationContext::identifier() {
  return getRuleContext<PredaParser::IdentifierContext>(0);
}


size_t PredaParser::VariableDeclarationContext::getRuleIndex() const {
  return PredaParser::RuleVariableDeclaration;
}

void PredaParser::VariableDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableDeclaration(this);
}

void PredaParser::VariableDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableDeclaration(this);
}


std::any PredaParser::VariableDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitVariableDeclaration(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::VariableDeclarationContext* PredaParser::variableDeclaration() {
  VariableDeclarationContext *_localctx = _tracker.createInstance<VariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 42, PredaParser::RuleVariableDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(337);
    typeName();
    setState(338);
    identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeNameOrAutoContext ------------------------------------------------------------------

PredaParser::TypeNameOrAutoContext::TypeNameOrAutoContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::TypeNameContext* PredaParser::TypeNameOrAutoContext::typeName() {
  return getRuleContext<PredaParser::TypeNameContext>(0);
}

tree::TerminalNode* PredaParser::TypeNameOrAutoContext::AutoKeyword() {
  return getToken(PredaParser::AutoKeyword, 0);
}

tree::TerminalNode* PredaParser::TypeNameOrAutoContext::ConstantKeyword() {
  return getToken(PredaParser::ConstantKeyword, 0);
}


size_t PredaParser::TypeNameOrAutoContext::getRuleIndex() const {
  return PredaParser::RuleTypeNameOrAuto;
}

void PredaParser::TypeNameOrAutoContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeNameOrAuto(this);
}

void PredaParser::TypeNameOrAutoContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeNameOrAuto(this);
}


std::any PredaParser::TypeNameOrAutoContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitTypeNameOrAuto(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::TypeNameOrAutoContext* PredaParser::typeNameOrAuto() {
  TypeNameOrAutoContext *_localctx = _tracker.createInstance<TypeNameOrAutoContext>(_ctx, getState());
  enterRule(_localctx, 44, PredaParser::RuleTypeNameOrAuto);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(341);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaParser::ConstantKeyword) {
      setState(340);
      match(PredaParser::ConstantKeyword);
    }
    setState(345);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaParser::T__11:
      case PredaParser::T__12:
      case PredaParser::T__13:
      case PredaParser::T__14:
      case PredaParser::T__15:
      case PredaParser::T__16:
      case PredaParser::T__19:
      case PredaParser::T__20:
      case PredaParser::T__21:
      case PredaParser::AddressKeyword:
      case PredaParser::FloatType:
      case PredaParser::IntType:
      case PredaParser::UintType:
      case PredaParser::Identifier: {
        setState(343);
        typeName();
        break;
      }

      case PredaParser::AutoKeyword: {
        setState(344);
        match(PredaParser::AutoKeyword);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeNameContext ------------------------------------------------------------------

PredaParser::TypeNameContext::TypeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::FundamentalTypeNameContext* PredaParser::TypeNameContext::fundamentalTypeName() {
  return getRuleContext<PredaParser::FundamentalTypeNameContext>(0);
}

PredaParser::BuiltInContainerTypeNameContext* PredaParser::TypeNameContext::builtInContainerTypeName() {
  return getRuleContext<PredaParser::BuiltInContainerTypeNameContext>(0);
}

PredaParser::UserDefinedTypeNameContext* PredaParser::TypeNameContext::userDefinedTypeName() {
  return getRuleContext<PredaParser::UserDefinedTypeNameContext>(0);
}


size_t PredaParser::TypeNameContext::getRuleIndex() const {
  return PredaParser::RuleTypeName;
}

void PredaParser::TypeNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeName(this);
}

void PredaParser::TypeNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeName(this);
}


std::any PredaParser::TypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitTypeName(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::TypeNameContext* PredaParser::typeName() {
  TypeNameContext *_localctx = _tracker.createInstance<TypeNameContext>(_ctx, getState());
  enterRule(_localctx, 46, PredaParser::RuleTypeName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(350);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaParser::T__11:
      case PredaParser::T__12:
      case PredaParser::T__13:
      case PredaParser::T__14:
      case PredaParser::T__15:
      case PredaParser::AddressKeyword:
      case PredaParser::FloatType:
      case PredaParser::IntType:
      case PredaParser::UintType: {
        enterOuterAlt(_localctx, 1);
        setState(347);
        fundamentalTypeName();
        break;
      }

      case PredaParser::T__16:
      case PredaParser::T__19:
      case PredaParser::T__20:
      case PredaParser::T__21: {
        enterOuterAlt(_localctx, 2);
        setState(348);
        builtInContainerTypeName();
        break;
      }

      case PredaParser::Identifier: {
        enterOuterAlt(_localctx, 3);
        setState(349);
        userDefinedTypeName();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FundamentalTypeNameContext ------------------------------------------------------------------

PredaParser::FundamentalTypeNameContext::FundamentalTypeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaParser::FundamentalTypeNameContext::IntType() {
  return getToken(PredaParser::IntType, 0);
}

tree::TerminalNode* PredaParser::FundamentalTypeNameContext::UintType() {
  return getToken(PredaParser::UintType, 0);
}

tree::TerminalNode* PredaParser::FundamentalTypeNameContext::FloatType() {
  return getToken(PredaParser::FloatType, 0);
}

tree::TerminalNode* PredaParser::FundamentalTypeNameContext::AddressKeyword() {
  return getToken(PredaParser::AddressKeyword, 0);
}


size_t PredaParser::FundamentalTypeNameContext::getRuleIndex() const {
  return PredaParser::RuleFundamentalTypeName;
}

void PredaParser::FundamentalTypeNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFundamentalTypeName(this);
}

void PredaParser::FundamentalTypeNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFundamentalTypeName(this);
}


std::any PredaParser::FundamentalTypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitFundamentalTypeName(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::FundamentalTypeNameContext* PredaParser::fundamentalTypeName() {
  FundamentalTypeNameContext *_localctx = _tracker.createInstance<FundamentalTypeNameContext>(_ctx, getState());
  enterRule(_localctx, 48, PredaParser::RuleFundamentalTypeName);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(352);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 126976) != 0) || ((((_la - 70) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 70)) & 917505) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BuiltInContainerTypeNameContext ------------------------------------------------------------------

PredaParser::BuiltInContainerTypeNameContext::BuiltInContainerTypeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::MapTypeNameContext* PredaParser::BuiltInContainerTypeNameContext::mapTypeName() {
  return getRuleContext<PredaParser::MapTypeNameContext>(0);
}

PredaParser::ArrayTypeNameContext* PredaParser::BuiltInContainerTypeNameContext::arrayTypeName() {
  return getRuleContext<PredaParser::ArrayTypeNameContext>(0);
}

PredaParser::ScatteredMapTypeNameContext* PredaParser::BuiltInContainerTypeNameContext::scatteredMapTypeName() {
  return getRuleContext<PredaParser::ScatteredMapTypeNameContext>(0);
}

PredaParser::ScatteredArrayTypeNameContext* PredaParser::BuiltInContainerTypeNameContext::scatteredArrayTypeName() {
  return getRuleContext<PredaParser::ScatteredArrayTypeNameContext>(0);
}


size_t PredaParser::BuiltInContainerTypeNameContext::getRuleIndex() const {
  return PredaParser::RuleBuiltInContainerTypeName;
}

void PredaParser::BuiltInContainerTypeNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBuiltInContainerTypeName(this);
}

void PredaParser::BuiltInContainerTypeNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBuiltInContainerTypeName(this);
}


std::any PredaParser::BuiltInContainerTypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitBuiltInContainerTypeName(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::BuiltInContainerTypeNameContext* PredaParser::builtInContainerTypeName() {
  BuiltInContainerTypeNameContext *_localctx = _tracker.createInstance<BuiltInContainerTypeNameContext>(_ctx, getState());
  enterRule(_localctx, 50, PredaParser::RuleBuiltInContainerTypeName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(358);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaParser::T__16: {
        enterOuterAlt(_localctx, 1);
        setState(354);
        mapTypeName();
        break;
      }

      case PredaParser::T__20: {
        enterOuterAlt(_localctx, 2);
        setState(355);
        arrayTypeName();
        break;
      }

      case PredaParser::T__19: {
        enterOuterAlt(_localctx, 3);
        setState(356);
        scatteredMapTypeName();
        break;
      }

      case PredaParser::T__21: {
        enterOuterAlt(_localctx, 4);
        setState(357);
        scatteredArrayTypeName();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MapKeyTypeNameContext ------------------------------------------------------------------

PredaParser::MapKeyTypeNameContext::MapKeyTypeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaParser::MapKeyTypeNameContext::IntType() {
  return getToken(PredaParser::IntType, 0);
}

tree::TerminalNode* PredaParser::MapKeyTypeNameContext::UintType() {
  return getToken(PredaParser::UintType, 0);
}

tree::TerminalNode* PredaParser::MapKeyTypeNameContext::AddressKeyword() {
  return getToken(PredaParser::AddressKeyword, 0);
}


size_t PredaParser::MapKeyTypeNameContext::getRuleIndex() const {
  return PredaParser::RuleMapKeyTypeName;
}

void PredaParser::MapKeyTypeNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMapKeyTypeName(this);
}

void PredaParser::MapKeyTypeNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMapKeyTypeName(this);
}


std::any PredaParser::MapKeyTypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitMapKeyTypeName(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::MapKeyTypeNameContext* PredaParser::mapKeyTypeName() {
  MapKeyTypeNameContext *_localctx = _tracker.createInstance<MapKeyTypeNameContext>(_ctx, getState());
  enterRule(_localctx, 52, PredaParser::RuleMapKeyTypeName);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(360);
    _la = _input->LA(1);
    if (!(_la == PredaParser::T__13

    || _la == PredaParser::T__14 || ((((_la - 70) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 70)) & 786433) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MapTypeNameContext ------------------------------------------------------------------

PredaParser::MapTypeNameContext::MapTypeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::MapKeyTypeNameContext* PredaParser::MapTypeNameContext::mapKeyTypeName() {
  return getRuleContext<PredaParser::MapKeyTypeNameContext>(0);
}

PredaParser::TypeNameContext* PredaParser::MapTypeNameContext::typeName() {
  return getRuleContext<PredaParser::TypeNameContext>(0);
}


size_t PredaParser::MapTypeNameContext::getRuleIndex() const {
  return PredaParser::RuleMapTypeName;
}

void PredaParser::MapTypeNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMapTypeName(this);
}

void PredaParser::MapTypeNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMapTypeName(this);
}


std::any PredaParser::MapTypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitMapTypeName(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::MapTypeNameContext* PredaParser::mapTypeName() {
  MapTypeNameContext *_localctx = _tracker.createInstance<MapTypeNameContext>(_ctx, getState());
  enterRule(_localctx, 54, PredaParser::RuleMapTypeName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(362);
    match(PredaParser::T__16);
    setState(363);
    match(PredaParser::T__17);
    setState(364);
    mapKeyTypeName();
    setState(365);
    match(PredaParser::T__3);
    setState(366);
    typeName();
    setState(367);
    match(PredaParser::T__18);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ScatteredMapTypeNameContext ------------------------------------------------------------------

PredaParser::ScatteredMapTypeNameContext::ScatteredMapTypeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::MapKeyTypeNameContext* PredaParser::ScatteredMapTypeNameContext::mapKeyTypeName() {
  return getRuleContext<PredaParser::MapKeyTypeNameContext>(0);
}

PredaParser::TypeNameContext* PredaParser::ScatteredMapTypeNameContext::typeName() {
  return getRuleContext<PredaParser::TypeNameContext>(0);
}


size_t PredaParser::ScatteredMapTypeNameContext::getRuleIndex() const {
  return PredaParser::RuleScatteredMapTypeName;
}

void PredaParser::ScatteredMapTypeNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterScatteredMapTypeName(this);
}

void PredaParser::ScatteredMapTypeNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitScatteredMapTypeName(this);
}


std::any PredaParser::ScatteredMapTypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitScatteredMapTypeName(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::ScatteredMapTypeNameContext* PredaParser::scatteredMapTypeName() {
  ScatteredMapTypeNameContext *_localctx = _tracker.createInstance<ScatteredMapTypeNameContext>(_ctx, getState());
  enterRule(_localctx, 56, PredaParser::RuleScatteredMapTypeName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(369);
    match(PredaParser::T__19);
    setState(370);
    match(PredaParser::T__17);
    setState(371);
    mapKeyTypeName();
    setState(372);
    match(PredaParser::T__3);
    setState(373);
    typeName();
    setState(374);
    match(PredaParser::T__18);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayTypeNameContext ------------------------------------------------------------------

PredaParser::ArrayTypeNameContext::ArrayTypeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::TypeNameContext* PredaParser::ArrayTypeNameContext::typeName() {
  return getRuleContext<PredaParser::TypeNameContext>(0);
}


size_t PredaParser::ArrayTypeNameContext::getRuleIndex() const {
  return PredaParser::RuleArrayTypeName;
}

void PredaParser::ArrayTypeNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayTypeName(this);
}

void PredaParser::ArrayTypeNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayTypeName(this);
}


std::any PredaParser::ArrayTypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitArrayTypeName(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::ArrayTypeNameContext* PredaParser::arrayTypeName() {
  ArrayTypeNameContext *_localctx = _tracker.createInstance<ArrayTypeNameContext>(_ctx, getState());
  enterRule(_localctx, 58, PredaParser::RuleArrayTypeName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(376);
    match(PredaParser::T__20);
    setState(377);
    match(PredaParser::T__17);
    setState(378);
    typeName();
    setState(379);
    match(PredaParser::T__18);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ScatteredArrayTypeNameContext ------------------------------------------------------------------

PredaParser::ScatteredArrayTypeNameContext::ScatteredArrayTypeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::TypeNameContext* PredaParser::ScatteredArrayTypeNameContext::typeName() {
  return getRuleContext<PredaParser::TypeNameContext>(0);
}


size_t PredaParser::ScatteredArrayTypeNameContext::getRuleIndex() const {
  return PredaParser::RuleScatteredArrayTypeName;
}

void PredaParser::ScatteredArrayTypeNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterScatteredArrayTypeName(this);
}

void PredaParser::ScatteredArrayTypeNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitScatteredArrayTypeName(this);
}


std::any PredaParser::ScatteredArrayTypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitScatteredArrayTypeName(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::ScatteredArrayTypeNameContext* PredaParser::scatteredArrayTypeName() {
  ScatteredArrayTypeNameContext *_localctx = _tracker.createInstance<ScatteredArrayTypeNameContext>(_ctx, getState());
  enterRule(_localctx, 60, PredaParser::RuleScatteredArrayTypeName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(381);
    match(PredaParser::T__21);
    setState(382);
    match(PredaParser::T__17);
    setState(383);
    typeName();
    setState(384);
    match(PredaParser::T__18);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UserDefinedTypeNameContext ------------------------------------------------------------------

PredaParser::UserDefinedTypeNameContext::UserDefinedTypeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PredaParser::IdentifierContext *> PredaParser::UserDefinedTypeNameContext::identifier() {
  return getRuleContexts<PredaParser::IdentifierContext>();
}

PredaParser::IdentifierContext* PredaParser::UserDefinedTypeNameContext::identifier(size_t i) {
  return getRuleContext<PredaParser::IdentifierContext>(i);
}


size_t PredaParser::UserDefinedTypeNameContext::getRuleIndex() const {
  return PredaParser::RuleUserDefinedTypeName;
}

void PredaParser::UserDefinedTypeNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUserDefinedTypeName(this);
}

void PredaParser::UserDefinedTypeNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUserDefinedTypeName(this);
}


std::any PredaParser::UserDefinedTypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitUserDefinedTypeName(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::UserDefinedTypeNameContext* PredaParser::userDefinedTypeName() {
  UserDefinedTypeNameContext *_localctx = _tracker.createInstance<UserDefinedTypeNameContext>(_ctx, getState());
  enterRule(_localctx, 62, PredaParser::RuleUserDefinedTypeName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(391);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(386);
        identifier();
        setState(387);
        match(PredaParser::T__0); 
      }
      setState(393);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
    }
    setState(394);
    identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UserBlockStatementContext ------------------------------------------------------------------

PredaParser::UserBlockStatementContext::UserBlockStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PredaParser::StatementContext *> PredaParser::UserBlockStatementContext::statement() {
  return getRuleContexts<PredaParser::StatementContext>();
}

PredaParser::StatementContext* PredaParser::UserBlockStatementContext::statement(size_t i) {
  return getRuleContext<PredaParser::StatementContext>(i);
}


size_t PredaParser::UserBlockStatementContext::getRuleIndex() const {
  return PredaParser::RuleUserBlockStatement;
}

void PredaParser::UserBlockStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUserBlockStatement(this);
}

void PredaParser::UserBlockStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUserBlockStatement(this);
}


std::any PredaParser::UserBlockStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitUserBlockStatement(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::UserBlockStatementContext* PredaParser::userBlockStatement() {
  UserBlockStatementContext *_localctx = _tracker.createInstance<UserBlockStatementContext>(_ctx, getState());
  enterRule(_localctx, 64, PredaParser::RuleUserBlockStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(396);
    match(PredaParser::T__6);
    setState(400);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -1152921487444544384) != 0) || ((((_la - 65) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 65)) & 132871880801) != 0)) {
      setState(397);
      statement();
      setState(402);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(403);
    match(PredaParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

PredaParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::IfStatementContext* PredaParser::StatementContext::ifStatement() {
  return getRuleContext<PredaParser::IfStatementContext>(0);
}

PredaParser::WhileStatementContext* PredaParser::StatementContext::whileStatement() {
  return getRuleContext<PredaParser::WhileStatementContext>(0);
}

PredaParser::ForStatementContext* PredaParser::StatementContext::forStatement() {
  return getRuleContext<PredaParser::ForStatementContext>(0);
}

PredaParser::UserBlockStatementContext* PredaParser::StatementContext::userBlockStatement() {
  return getRuleContext<PredaParser::UserBlockStatementContext>(0);
}

PredaParser::DoWhileStatementContext* PredaParser::StatementContext::doWhileStatement() {
  return getRuleContext<PredaParser::DoWhileStatementContext>(0);
}

PredaParser::ContinueStatementContext* PredaParser::StatementContext::continueStatement() {
  return getRuleContext<PredaParser::ContinueStatementContext>(0);
}

PredaParser::BreakStatementContext* PredaParser::StatementContext::breakStatement() {
  return getRuleContext<PredaParser::BreakStatementContext>(0);
}

PredaParser::ReturnStatementContext* PredaParser::StatementContext::returnStatement() {
  return getRuleContext<PredaParser::ReturnStatementContext>(0);
}

PredaParser::RelayStatementContext* PredaParser::StatementContext::relayStatement() {
  return getRuleContext<PredaParser::RelayStatementContext>(0);
}

PredaParser::VariableDeclarationStatementContext* PredaParser::StatementContext::variableDeclarationStatement() {
  return getRuleContext<PredaParser::VariableDeclarationStatementContext>(0);
}

PredaParser::ExpressionStatementContext* PredaParser::StatementContext::expressionStatement() {
  return getRuleContext<PredaParser::ExpressionStatementContext>(0);
}


size_t PredaParser::StatementContext::getRuleIndex() const {
  return PredaParser::RuleStatement;
}

void PredaParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void PredaParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}


std::any PredaParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::StatementContext* PredaParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 66, PredaParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(416);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(405);
      ifStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(406);
      whileStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(407);
      forStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(408);
      userBlockStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(409);
      doWhileStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(410);
      continueStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(411);
      breakStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(412);
      returnStatement();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(413);
      relayStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(414);
      variableDeclarationStatement();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(415);
      expressionStatement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionStatementContext ------------------------------------------------------------------

PredaParser::ExpressionStatementContext::ExpressionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::ExpressionContext* PredaParser::ExpressionStatementContext::expression() {
  return getRuleContext<PredaParser::ExpressionContext>(0);
}


size_t PredaParser::ExpressionStatementContext::getRuleIndex() const {
  return PredaParser::RuleExpressionStatement;
}

void PredaParser::ExpressionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpressionStatement(this);
}

void PredaParser::ExpressionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpressionStatement(this);
}


std::any PredaParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitExpressionStatement(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::ExpressionStatementContext* PredaParser::expressionStatement() {
  ExpressionStatementContext *_localctx = _tracker.createInstance<ExpressionStatementContext>(_ctx, getState());
  enterRule(_localctx, 68, PredaParser::RuleExpressionStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(418);
    expression(0);
    setState(419);
    match(PredaParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStatementContext ------------------------------------------------------------------

PredaParser::IfStatementContext::IfStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::IfWithBlockContext* PredaParser::IfStatementContext::ifWithBlock() {
  return getRuleContext<PredaParser::IfWithBlockContext>(0);
}

std::vector<PredaParser::ElseIfWithBlockContext *> PredaParser::IfStatementContext::elseIfWithBlock() {
  return getRuleContexts<PredaParser::ElseIfWithBlockContext>();
}

PredaParser::ElseIfWithBlockContext* PredaParser::IfStatementContext::elseIfWithBlock(size_t i) {
  return getRuleContext<PredaParser::ElseIfWithBlockContext>(i);
}

PredaParser::ElseWithBlockContext* PredaParser::IfStatementContext::elseWithBlock() {
  return getRuleContext<PredaParser::ElseWithBlockContext>(0);
}


size_t PredaParser::IfStatementContext::getRuleIndex() const {
  return PredaParser::RuleIfStatement;
}

void PredaParser::IfStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfStatement(this);
}

void PredaParser::IfStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfStatement(this);
}


std::any PredaParser::IfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitIfStatement(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::IfStatementContext* PredaParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 70, PredaParser::RuleIfStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(421);
    ifWithBlock();
    setState(425);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(422);
        elseIfWithBlock(); 
      }
      setState(427);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx);
    }
    setState(429);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaParser::ElseKeyword) {
      setState(428);
      elseWithBlock();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfWithBlockContext ------------------------------------------------------------------

PredaParser::IfWithBlockContext::IfWithBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaParser::IfWithBlockContext::IfKeyword() {
  return getToken(PredaParser::IfKeyword, 0);
}

PredaParser::ExpressionContext* PredaParser::IfWithBlockContext::expression() {
  return getRuleContext<PredaParser::ExpressionContext>(0);
}

std::vector<PredaParser::StatementContext *> PredaParser::IfWithBlockContext::statement() {
  return getRuleContexts<PredaParser::StatementContext>();
}

PredaParser::StatementContext* PredaParser::IfWithBlockContext::statement(size_t i) {
  return getRuleContext<PredaParser::StatementContext>(i);
}


size_t PredaParser::IfWithBlockContext::getRuleIndex() const {
  return PredaParser::RuleIfWithBlock;
}

void PredaParser::IfWithBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfWithBlock(this);
}

void PredaParser::IfWithBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfWithBlock(this);
}


std::any PredaParser::IfWithBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitIfWithBlock(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::IfWithBlockContext* PredaParser::ifWithBlock() {
  IfWithBlockContext *_localctx = _tracker.createInstance<IfWithBlockContext>(_ctx, getState());
  enterRule(_localctx, 72, PredaParser::RuleIfWithBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(431);
    match(PredaParser::IfKeyword);
    setState(432);
    match(PredaParser::T__9);
    setState(433);
    expression(0);
    setState(434);
    match(PredaParser::T__10);
    setState(435);
    match(PredaParser::T__6);
    setState(439);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -1152921487444544384) != 0) || ((((_la - 65) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 65)) & 132871880801) != 0)) {
      setState(436);
      statement();
      setState(441);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(442);
    match(PredaParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElseWithBlockContext ------------------------------------------------------------------

PredaParser::ElseWithBlockContext::ElseWithBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaParser::ElseWithBlockContext::ElseKeyword() {
  return getToken(PredaParser::ElseKeyword, 0);
}

std::vector<PredaParser::StatementContext *> PredaParser::ElseWithBlockContext::statement() {
  return getRuleContexts<PredaParser::StatementContext>();
}

PredaParser::StatementContext* PredaParser::ElseWithBlockContext::statement(size_t i) {
  return getRuleContext<PredaParser::StatementContext>(i);
}


size_t PredaParser::ElseWithBlockContext::getRuleIndex() const {
  return PredaParser::RuleElseWithBlock;
}

void PredaParser::ElseWithBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElseWithBlock(this);
}

void PredaParser::ElseWithBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElseWithBlock(this);
}


std::any PredaParser::ElseWithBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitElseWithBlock(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::ElseWithBlockContext* PredaParser::elseWithBlock() {
  ElseWithBlockContext *_localctx = _tracker.createInstance<ElseWithBlockContext>(_ctx, getState());
  enterRule(_localctx, 74, PredaParser::RuleElseWithBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(444);
    match(PredaParser::ElseKeyword);
    setState(445);
    match(PredaParser::T__6);
    setState(449);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -1152921487444544384) != 0) || ((((_la - 65) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 65)) & 132871880801) != 0)) {
      setState(446);
      statement();
      setState(451);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(452);
    match(PredaParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElseIfWithBlockContext ------------------------------------------------------------------

PredaParser::ElseIfWithBlockContext::ElseIfWithBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaParser::ElseIfWithBlockContext::ElseKeyword() {
  return getToken(PredaParser::ElseKeyword, 0);
}

tree::TerminalNode* PredaParser::ElseIfWithBlockContext::IfKeyword() {
  return getToken(PredaParser::IfKeyword, 0);
}

PredaParser::ExpressionContext* PredaParser::ElseIfWithBlockContext::expression() {
  return getRuleContext<PredaParser::ExpressionContext>(0);
}

std::vector<PredaParser::StatementContext *> PredaParser::ElseIfWithBlockContext::statement() {
  return getRuleContexts<PredaParser::StatementContext>();
}

PredaParser::StatementContext* PredaParser::ElseIfWithBlockContext::statement(size_t i) {
  return getRuleContext<PredaParser::StatementContext>(i);
}


size_t PredaParser::ElseIfWithBlockContext::getRuleIndex() const {
  return PredaParser::RuleElseIfWithBlock;
}

void PredaParser::ElseIfWithBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElseIfWithBlock(this);
}

void PredaParser::ElseIfWithBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElseIfWithBlock(this);
}


std::any PredaParser::ElseIfWithBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitElseIfWithBlock(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::ElseIfWithBlockContext* PredaParser::elseIfWithBlock() {
  ElseIfWithBlockContext *_localctx = _tracker.createInstance<ElseIfWithBlockContext>(_ctx, getState());
  enterRule(_localctx, 76, PredaParser::RuleElseIfWithBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(454);
    match(PredaParser::ElseKeyword);
    setState(455);
    match(PredaParser::IfKeyword);
    setState(456);
    match(PredaParser::T__9);
    setState(457);
    expression(0);
    setState(458);
    match(PredaParser::T__10);
    setState(459);
    match(PredaParser::T__6);
    setState(463);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -1152921487444544384) != 0) || ((((_la - 65) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 65)) & 132871880801) != 0)) {
      setState(460);
      statement();
      setState(465);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(466);
    match(PredaParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhileStatementContext ------------------------------------------------------------------

PredaParser::WhileStatementContext::WhileStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::ExpressionContext* PredaParser::WhileStatementContext::expression() {
  return getRuleContext<PredaParser::ExpressionContext>(0);
}

std::vector<PredaParser::StatementContext *> PredaParser::WhileStatementContext::statement() {
  return getRuleContexts<PredaParser::StatementContext>();
}

PredaParser::StatementContext* PredaParser::WhileStatementContext::statement(size_t i) {
  return getRuleContext<PredaParser::StatementContext>(i);
}


size_t PredaParser::WhileStatementContext::getRuleIndex() const {
  return PredaParser::RuleWhileStatement;
}

void PredaParser::WhileStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhileStatement(this);
}

void PredaParser::WhileStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhileStatement(this);
}


std::any PredaParser::WhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitWhileStatement(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::WhileStatementContext* PredaParser::whileStatement() {
  WhileStatementContext *_localctx = _tracker.createInstance<WhileStatementContext>(_ctx, getState());
  enterRule(_localctx, 78, PredaParser::RuleWhileStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(468);
    match(PredaParser::T__22);
    setState(469);
    match(PredaParser::T__9);
    setState(470);
    expression(0);
    setState(471);
    match(PredaParser::T__10);
    setState(472);
    match(PredaParser::T__6);
    setState(476);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -1152921487444544384) != 0) || ((((_la - 65) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 65)) & 132871880801) != 0)) {
      setState(473);
      statement();
      setState(478);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(479);
    match(PredaParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelayStatementContext ------------------------------------------------------------------

PredaParser::RelayStatementContext::RelayStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaParser::RelayStatementContext::RelayKeyword() {
  return getToken(PredaParser::RelayKeyword, 0);
}

PredaParser::RelayTypeContext* PredaParser::RelayStatementContext::relayType() {
  return getRuleContext<PredaParser::RelayTypeContext>(0);
}

PredaParser::RelayLambdaDefinitionContext* PredaParser::RelayStatementContext::relayLambdaDefinition() {
  return getRuleContext<PredaParser::RelayLambdaDefinitionContext>(0);
}

PredaParser::IdentifierContext* PredaParser::RelayStatementContext::identifier() {
  return getRuleContext<PredaParser::IdentifierContext>(0);
}

PredaParser::FunctionCallArgumentsContext* PredaParser::RelayStatementContext::functionCallArguments() {
  return getRuleContext<PredaParser::FunctionCallArgumentsContext>(0);
}


size_t PredaParser::RelayStatementContext::getRuleIndex() const {
  return PredaParser::RuleRelayStatement;
}

void PredaParser::RelayStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelayStatement(this);
}

void PredaParser::RelayStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelayStatement(this);
}


std::any PredaParser::RelayStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitRelayStatement(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::RelayStatementContext* PredaParser::relayStatement() {
  RelayStatementContext *_localctx = _tracker.createInstance<RelayStatementContext>(_ctx, getState());
  enterRule(_localctx, 80, PredaParser::RuleRelayStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(481);
    match(PredaParser::RelayKeyword);
    setState(482);
    match(PredaParser::T__8);
    setState(483);
    relayType();
    setState(491);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaParser::Identifier: {
        setState(484);
        identifier();
        setState(485);
        match(PredaParser::T__9);
        setState(486);
        functionCallArguments();
        setState(487);
        match(PredaParser::T__10);
        setState(488);
        match(PredaParser::T__1);
        break;
      }

      case PredaParser::T__9: {
        setState(490);
        relayLambdaDefinition();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelayTypeContext ------------------------------------------------------------------

PredaParser::RelayTypeContext::RelayTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::ExpressionContext* PredaParser::RelayTypeContext::expression() {
  return getRuleContext<PredaParser::ExpressionContext>(0);
}

tree::TerminalNode* PredaParser::RelayTypeContext::ShardsKeyword() {
  return getToken(PredaParser::ShardsKeyword, 0);
}

tree::TerminalNode* PredaParser::RelayTypeContext::GlobalKeyword() {
  return getToken(PredaParser::GlobalKeyword, 0);
}

tree::TerminalNode* PredaParser::RelayTypeContext::NextKeyword() {
  return getToken(PredaParser::NextKeyword, 0);
}


size_t PredaParser::RelayTypeContext::getRuleIndex() const {
  return PredaParser::RuleRelayType;
}

void PredaParser::RelayTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelayType(this);
}

void PredaParser::RelayTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelayType(this);
}


std::any PredaParser::RelayTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitRelayType(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::RelayTypeContext* PredaParser::relayType() {
  RelayTypeContext *_localctx = _tracker.createInstance<RelayTypeContext>(_ctx, getState());
  enterRule(_localctx, 82, PredaParser::RuleRelayType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(497);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaParser::T__9:
      case PredaParser::T__11:
      case PredaParser::T__12:
      case PredaParser::T__13:
      case PredaParser::T__14:
      case PredaParser::T__15:
      case PredaParser::T__16:
      case PredaParser::T__19:
      case PredaParser::T__20:
      case PredaParser::T__21:
      case PredaParser::T__27:
      case PredaParser::T__28:
      case PredaParser::T__29:
      case PredaParser::T__30:
      case PredaParser::T__31:
      case PredaParser::T__32:
      case PredaParser::AddressKeyword:
      case PredaParser::DeployKeyword:
      case PredaParser::FloatType:
      case PredaParser::IntType:
      case PredaParser::UintType:
      case PredaParser::BooleanLiteral:
      case PredaParser::DecimalFloatLiteral:
      case PredaParser::DecimalIntegerLiteral:
      case PredaParser::AddressLiteral:
      case PredaParser::HashLiteral:
      case PredaParser::HexIntegerLiteral:
      case PredaParser::DecimalBigIntegerLiteral:
      case PredaParser::HexBigIntegerLiteral:
      case PredaParser::Identifier:
      case PredaParser::StringLiteral: {
        setState(493);
        expression(0);
        break;
      }

      case PredaParser::ShardsKeyword: {
        setState(494);
        match(PredaParser::ShardsKeyword);
        break;
      }

      case PredaParser::GlobalKeyword: {
        setState(495);
        match(PredaParser::GlobalKeyword);
        break;
      }

      case PredaParser::NextKeyword: {
        setState(496);
        match(PredaParser::NextKeyword);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelayLambdaDefinitionContext ------------------------------------------------------------------

PredaParser::RelayLambdaDefinitionContext::RelayLambdaDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PredaParser::RelayLambdaParameterContext *> PredaParser::RelayLambdaDefinitionContext::relayLambdaParameter() {
  return getRuleContexts<PredaParser::RelayLambdaParameterContext>();
}

PredaParser::RelayLambdaParameterContext* PredaParser::RelayLambdaDefinitionContext::relayLambdaParameter(size_t i) {
  return getRuleContext<PredaParser::RelayLambdaParameterContext>(i);
}

tree::TerminalNode* PredaParser::RelayLambdaDefinitionContext::ConstantKeyword() {
  return getToken(PredaParser::ConstantKeyword, 0);
}

std::vector<PredaParser::StatementContext *> PredaParser::RelayLambdaDefinitionContext::statement() {
  return getRuleContexts<PredaParser::StatementContext>();
}

PredaParser::StatementContext* PredaParser::RelayLambdaDefinitionContext::statement(size_t i) {
  return getRuleContext<PredaParser::StatementContext>(i);
}


size_t PredaParser::RelayLambdaDefinitionContext::getRuleIndex() const {
  return PredaParser::RuleRelayLambdaDefinition;
}

void PredaParser::RelayLambdaDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelayLambdaDefinition(this);
}

void PredaParser::RelayLambdaDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelayLambdaDefinition(this);
}


std::any PredaParser::RelayLambdaDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitRelayLambdaDefinition(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::RelayLambdaDefinitionContext* PredaParser::relayLambdaDefinition() {
  RelayLambdaDefinitionContext *_localctx = _tracker.createInstance<RelayLambdaDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 84, PredaParser::RuleRelayLambdaDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(499);
    match(PredaParser::T__9);
    setState(508);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2305843009238069248) != 0) || ((((_la - 70) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 70)) & 1074659331) != 0)) {
      setState(500);
      relayLambdaParameter();
      setState(505);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == PredaParser::T__3) {
        setState(501);
        match(PredaParser::T__3);
        setState(502);
        relayLambdaParameter();
        setState(507);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(510);
    match(PredaParser::T__10);
    setState(512);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaParser::ConstantKeyword) {
      setState(511);
      match(PredaParser::ConstantKeyword);
    }
    setState(514);
    match(PredaParser::T__6);
    setState(518);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -1152921487444544384) != 0) || ((((_la - 65) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 65)) & 132871880801) != 0)) {
      setState(515);
      statement();
      setState(520);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(521);
    match(PredaParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelayLambdaParameterContext ------------------------------------------------------------------

PredaParser::RelayLambdaParameterContext::RelayLambdaParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::TypeNameOrAutoContext* PredaParser::RelayLambdaParameterContext::typeNameOrAuto() {
  return getRuleContext<PredaParser::TypeNameOrAutoContext>(0);
}

PredaParser::IdentifierContext* PredaParser::RelayLambdaParameterContext::identifier() {
  return getRuleContext<PredaParser::IdentifierContext>(0);
}

PredaParser::ExpressionContext* PredaParser::RelayLambdaParameterContext::expression() {
  return getRuleContext<PredaParser::ExpressionContext>(0);
}


size_t PredaParser::RelayLambdaParameterContext::getRuleIndex() const {
  return PredaParser::RuleRelayLambdaParameter;
}

void PredaParser::RelayLambdaParameterContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelayLambdaParameter(this);
}

void PredaParser::RelayLambdaParameterContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelayLambdaParameter(this);
}


std::any PredaParser::RelayLambdaParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitRelayLambdaParameter(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::RelayLambdaParameterContext* PredaParser::relayLambdaParameter() {
  RelayLambdaParameterContext *_localctx = _tracker.createInstance<RelayLambdaParameterContext>(_ctx, getState());
  enterRule(_localctx, 86, PredaParser::RuleRelayLambdaParameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(530);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaParser::T__11:
      case PredaParser::T__12:
      case PredaParser::T__13:
      case PredaParser::T__14:
      case PredaParser::T__15:
      case PredaParser::T__16:
      case PredaParser::T__19:
      case PredaParser::T__20:
      case PredaParser::T__21:
      case PredaParser::ConstantKeyword:
      case PredaParser::AddressKeyword:
      case PredaParser::AutoKeyword:
      case PredaParser::FloatType:
      case PredaParser::IntType:
      case PredaParser::UintType:
      case PredaParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(523);
        typeNameOrAuto();
        setState(524);
        identifier();
        setState(525);
        match(PredaParser::T__5);
        setState(526);
        expression(0);
        break;
      }

      case PredaParser::T__23: {
        enterOuterAlt(_localctx, 2);
        setState(528);
        match(PredaParser::T__23);
        setState(529);
        identifier();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForStatementContext ------------------------------------------------------------------

PredaParser::ForStatementContext::ForStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::LocalVariableDeclarationContext* PredaParser::ForStatementContext::localVariableDeclaration() {
  return getRuleContext<PredaParser::LocalVariableDeclarationContext>(0);
}

std::vector<PredaParser::StatementContext *> PredaParser::ForStatementContext::statement() {
  return getRuleContexts<PredaParser::StatementContext>();
}

PredaParser::StatementContext* PredaParser::ForStatementContext::statement(size_t i) {
  return getRuleContext<PredaParser::StatementContext>(i);
}

std::vector<PredaParser::ExpressionContext *> PredaParser::ForStatementContext::expression() {
  return getRuleContexts<PredaParser::ExpressionContext>();
}

PredaParser::ExpressionContext* PredaParser::ForStatementContext::expression(size_t i) {
  return getRuleContext<PredaParser::ExpressionContext>(i);
}


size_t PredaParser::ForStatementContext::getRuleIndex() const {
  return PredaParser::RuleForStatement;
}

void PredaParser::ForStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForStatement(this);
}

void PredaParser::ForStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForStatement(this);
}


std::any PredaParser::ForStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitForStatement(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::ForStatementContext* PredaParser::forStatement() {
  ForStatementContext *_localctx = _tracker.createInstance<ForStatementContext>(_ctx, getState());
  enterRule(_localctx, 88, PredaParser::RuleForStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(532);
    match(PredaParser::T__24);
    setState(533);
    match(PredaParser::T__9);
    setState(536);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx)) {
    case 1: {
      setState(534);
      localVariableDeclaration();
      break;
    }

    case 2: {
      setState(535);
      antlrcpp::downCast<ForStatementContext *>(_localctx)->firstExpression = expression(0);
      break;
    }

    default:
      break;
    }
    setState(538);
    match(PredaParser::T__1);
    setState(540);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 16919032832) != 0) || ((((_la - 70) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 70)) & 4152246273) != 0)) {
      setState(539);
      antlrcpp::downCast<ForStatementContext *>(_localctx)->secondExpression = expression(0);
    }
    setState(542);
    match(PredaParser::T__1);
    setState(544);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 16919032832) != 0) || ((((_la - 70) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 70)) & 4152246273) != 0)) {
      setState(543);
      antlrcpp::downCast<ForStatementContext *>(_localctx)->thirdExpression = expression(0);
    }
    setState(546);
    match(PredaParser::T__10);
    setState(547);
    match(PredaParser::T__6);
    setState(551);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -1152921487444544384) != 0) || ((((_la - 65) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 65)) & 132871880801) != 0)) {
      setState(548);
      statement();
      setState(553);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(554);
    match(PredaParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DoWhileStatementContext ------------------------------------------------------------------

PredaParser::DoWhileStatementContext::DoWhileStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::ExpressionContext* PredaParser::DoWhileStatementContext::expression() {
  return getRuleContext<PredaParser::ExpressionContext>(0);
}

std::vector<PredaParser::StatementContext *> PredaParser::DoWhileStatementContext::statement() {
  return getRuleContexts<PredaParser::StatementContext>();
}

PredaParser::StatementContext* PredaParser::DoWhileStatementContext::statement(size_t i) {
  return getRuleContext<PredaParser::StatementContext>(i);
}


size_t PredaParser::DoWhileStatementContext::getRuleIndex() const {
  return PredaParser::RuleDoWhileStatement;
}

void PredaParser::DoWhileStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDoWhileStatement(this);
}

void PredaParser::DoWhileStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDoWhileStatement(this);
}


std::any PredaParser::DoWhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitDoWhileStatement(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::DoWhileStatementContext* PredaParser::doWhileStatement() {
  DoWhileStatementContext *_localctx = _tracker.createInstance<DoWhileStatementContext>(_ctx, getState());
  enterRule(_localctx, 90, PredaParser::RuleDoWhileStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(556);
    match(PredaParser::T__25);
    setState(557);
    match(PredaParser::T__6);
    setState(561);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -1152921487444544384) != 0) || ((((_la - 65) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 65)) & 132871880801) != 0)) {
      setState(558);
      statement();
      setState(563);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(564);
    match(PredaParser::T__7);
    setState(565);
    match(PredaParser::T__22);
    setState(566);
    match(PredaParser::T__9);
    setState(567);
    expression(0);
    setState(568);
    match(PredaParser::T__10);
    setState(569);
    match(PredaParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ContinueStatementContext ------------------------------------------------------------------

PredaParser::ContinueStatementContext::ContinueStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaParser::ContinueStatementContext::ContinueKeyword() {
  return getToken(PredaParser::ContinueKeyword, 0);
}


size_t PredaParser::ContinueStatementContext::getRuleIndex() const {
  return PredaParser::RuleContinueStatement;
}

void PredaParser::ContinueStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContinueStatement(this);
}

void PredaParser::ContinueStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContinueStatement(this);
}


std::any PredaParser::ContinueStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitContinueStatement(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::ContinueStatementContext* PredaParser::continueStatement() {
  ContinueStatementContext *_localctx = _tracker.createInstance<ContinueStatementContext>(_ctx, getState());
  enterRule(_localctx, 92, PredaParser::RuleContinueStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(571);
    match(PredaParser::ContinueKeyword);
    setState(572);
    match(PredaParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BreakStatementContext ------------------------------------------------------------------

PredaParser::BreakStatementContext::BreakStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaParser::BreakStatementContext::BreakKeyword() {
  return getToken(PredaParser::BreakKeyword, 0);
}


size_t PredaParser::BreakStatementContext::getRuleIndex() const {
  return PredaParser::RuleBreakStatement;
}

void PredaParser::BreakStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBreakStatement(this);
}

void PredaParser::BreakStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBreakStatement(this);
}


std::any PredaParser::BreakStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitBreakStatement(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::BreakStatementContext* PredaParser::breakStatement() {
  BreakStatementContext *_localctx = _tracker.createInstance<BreakStatementContext>(_ctx, getState());
  enterRule(_localctx, 94, PredaParser::RuleBreakStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(574);
    match(PredaParser::BreakKeyword);
    setState(575);
    match(PredaParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnStatementContext ------------------------------------------------------------------

PredaParser::ReturnStatementContext::ReturnStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::ExpressionContext* PredaParser::ReturnStatementContext::expression() {
  return getRuleContext<PredaParser::ExpressionContext>(0);
}


size_t PredaParser::ReturnStatementContext::getRuleIndex() const {
  return PredaParser::RuleReturnStatement;
}

void PredaParser::ReturnStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnStatement(this);
}

void PredaParser::ReturnStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnStatement(this);
}


std::any PredaParser::ReturnStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitReturnStatement(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::ReturnStatementContext* PredaParser::returnStatement() {
  ReturnStatementContext *_localctx = _tracker.createInstance<ReturnStatementContext>(_ctx, getState());
  enterRule(_localctx, 96, PredaParser::RuleReturnStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(577);
    match(PredaParser::T__26);
    setState(579);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 16919032832) != 0) || ((((_la - 70) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 70)) & 4152246273) != 0)) {
      setState(578);
      expression(0);
    }
    setState(581);
    match(PredaParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationStatementContext ------------------------------------------------------------------

PredaParser::VariableDeclarationStatementContext::VariableDeclarationStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::LocalVariableDeclarationContext* PredaParser::VariableDeclarationStatementContext::localVariableDeclaration() {
  return getRuleContext<PredaParser::LocalVariableDeclarationContext>(0);
}


size_t PredaParser::VariableDeclarationStatementContext::getRuleIndex() const {
  return PredaParser::RuleVariableDeclarationStatement;
}

void PredaParser::VariableDeclarationStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableDeclarationStatement(this);
}

void PredaParser::VariableDeclarationStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableDeclarationStatement(this);
}


std::any PredaParser::VariableDeclarationStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitVariableDeclarationStatement(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::VariableDeclarationStatementContext* PredaParser::variableDeclarationStatement() {
  VariableDeclarationStatementContext *_localctx = _tracker.createInstance<VariableDeclarationStatementContext>(_ctx, getState());
  enterRule(_localctx, 98, PredaParser::RuleVariableDeclarationStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(583);
    localVariableDeclaration();
    setState(584);
    match(PredaParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LocalVariableDeclarationContext ------------------------------------------------------------------

PredaParser::LocalVariableDeclarationContext::LocalVariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaParser::TypeNameOrAutoContext* PredaParser::LocalVariableDeclarationContext::typeNameOrAuto() {
  return getRuleContext<PredaParser::TypeNameOrAutoContext>(0);
}

PredaParser::IdentifierContext* PredaParser::LocalVariableDeclarationContext::identifier() {
  return getRuleContext<PredaParser::IdentifierContext>(0);
}

PredaParser::ExpressionContext* PredaParser::LocalVariableDeclarationContext::expression() {
  return getRuleContext<PredaParser::ExpressionContext>(0);
}


size_t PredaParser::LocalVariableDeclarationContext::getRuleIndex() const {
  return PredaParser::RuleLocalVariableDeclaration;
}

void PredaParser::LocalVariableDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLocalVariableDeclaration(this);
}

void PredaParser::LocalVariableDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLocalVariableDeclaration(this);
}


std::any PredaParser::LocalVariableDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitLocalVariableDeclaration(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::LocalVariableDeclarationContext* PredaParser::localVariableDeclaration() {
  LocalVariableDeclarationContext *_localctx = _tracker.createInstance<LocalVariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 100, PredaParser::RuleLocalVariableDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(586);
    typeNameOrAuto();
    setState(587);
    identifier();
    setState(590);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaParser::T__5) {
      setState(588);
      match(PredaParser::T__5);
      setState(589);
      expression(0);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

PredaParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PredaParser::ExpressionContext *> PredaParser::ExpressionContext::expression() {
  return getRuleContexts<PredaParser::ExpressionContext>();
}

PredaParser::ExpressionContext* PredaParser::ExpressionContext::expression(size_t i) {
  return getRuleContext<PredaParser::ExpressionContext>(i);
}

tree::TerminalNode* PredaParser::ExpressionContext::DeployKeyword() {
  return getToken(PredaParser::DeployKeyword, 0);
}

PredaParser::FunctionCallArgumentsContext* PredaParser::ExpressionContext::functionCallArguments() {
  return getRuleContext<PredaParser::FunctionCallArgumentsContext>(0);
}

PredaParser::PrimaryExpressionContext* PredaParser::ExpressionContext::primaryExpression() {
  return getRuleContext<PredaParser::PrimaryExpressionContext>(0);
}

PredaParser::IdentifierContext* PredaParser::ExpressionContext::identifier() {
  return getRuleContext<PredaParser::IdentifierContext>(0);
}


size_t PredaParser::ExpressionContext::getRuleIndex() const {
  return PredaParser::RuleExpression;
}

void PredaParser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void PredaParser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}


std::any PredaParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}


PredaParser::ExpressionContext* PredaParser::expression() {
   return expression(0);
}

PredaParser::ExpressionContext* PredaParser::expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  PredaParser::ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, parentState);
  PredaParser::ExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 102;
  enterRecursionRule(_localctx, 102, PredaParser::RuleExpression, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(632);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaParser::T__9: {
        setState(593);
        match(PredaParser::T__9);
        setState(594);
        expression(0);
        setState(595);
        match(PredaParser::T__10);
        antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  5;
        break;
      }

      case PredaParser::T__27: {
        setState(598);
        match(PredaParser::T__27);
        setState(599);
        expression(38);
        antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  6;
        break;
      }

      case PredaParser::T__28: {
        setState(602);
        match(PredaParser::T__28);
        setState(603);
        expression(37);
        antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  7;
        break;
      }

      case PredaParser::T__29: {
        setState(606);
        match(PredaParser::T__29);
        setState(607);
        expression(36);
        antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  8;
        break;
      }

      case PredaParser::T__30: {
        setState(610);
        match(PredaParser::T__30);
        setState(611);
        expression(35);
        antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  9;
        break;
      }

      case PredaParser::T__31: {
        setState(614);
        match(PredaParser::T__31);
        setState(615);
        expression(34);
        antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  10;
        break;
      }

      case PredaParser::T__32: {
        setState(618);
        match(PredaParser::T__32);
        setState(619);
        expression(33);
        antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  11;
        break;
      }

      case PredaParser::DeployKeyword: {
        setState(622);
        match(PredaParser::DeployKeyword);
        setState(623);
        expression(0);
        setState(624);
        match(PredaParser::T__9);
        setState(625);
        functionCallArguments();
        setState(626);
        match(PredaParser::T__10);
        antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  12;
        break;
      }

      case PredaParser::T__11:
      case PredaParser::T__12:
      case PredaParser::T__13:
      case PredaParser::T__14:
      case PredaParser::T__15:
      case PredaParser::T__16:
      case PredaParser::T__19:
      case PredaParser::T__20:
      case PredaParser::T__21:
      case PredaParser::AddressKeyword:
      case PredaParser::FloatType:
      case PredaParser::IntType:
      case PredaParser::UintType:
      case PredaParser::BooleanLiteral:
      case PredaParser::DecimalFloatLiteral:
      case PredaParser::DecimalIntegerLiteral:
      case PredaParser::AddressLiteral:
      case PredaParser::HashLiteral:
      case PredaParser::HexIntegerLiteral:
      case PredaParser::DecimalBigIntegerLiteral:
      case PredaParser::HexBigIntegerLiteral:
      case PredaParser::Identifier:
      case PredaParser::StringLiteral: {
        setState(629);
        primaryExpression();
        antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  43;
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(812);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(810);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 64, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(634);

          if (!(precpred(_ctx, 31))) throw FailedPredicateException(this, "precpred(_ctx, 31)");
          setState(635);
          match(PredaParser::T__33);
          setState(636);
          expression(32);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  13;
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(639);

          if (!(precpred(_ctx, 30))) throw FailedPredicateException(this, "precpred(_ctx, 30)");
          setState(640);
          match(PredaParser::T__34);
          setState(641);
          expression(31);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  14;
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(644);

          if (!(precpred(_ctx, 29))) throw FailedPredicateException(this, "precpred(_ctx, 29)");
          setState(645);
          match(PredaParser::T__35);
          setState(646);
          expression(30);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  15;
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(649);

          if (!(precpred(_ctx, 28))) throw FailedPredicateException(this, "precpred(_ctx, 28)");
          setState(650);
          match(PredaParser::T__29);
          setState(651);
          expression(29);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  16;
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(654);

          if (!(precpred(_ctx, 27))) throw FailedPredicateException(this, "precpred(_ctx, 27)");
          setState(655);
          match(PredaParser::T__30);
          setState(656);
          expression(28);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  17;
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(659);

          if (!(precpred(_ctx, 26))) throw FailedPredicateException(this, "precpred(_ctx, 26)");
          setState(660);
          match(PredaParser::T__36);
          setState(661);
          expression(27);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  18;
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(664);

          if (!(precpred(_ctx, 25))) throw FailedPredicateException(this, "precpred(_ctx, 25)");
          setState(665);
          match(PredaParser::T__18);
          setState(666);
          match(PredaParser::T__18);
          setState(667);
          expression(26);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  19;
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(670);

          if (!(precpred(_ctx, 24))) throw FailedPredicateException(this, "precpred(_ctx, 24)");
          setState(671);
          match(PredaParser::T__17);
          setState(672);
          expression(25);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  20;
          break;
        }

        case 9: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(675);

          if (!(precpred(_ctx, 23))) throw FailedPredicateException(this, "precpred(_ctx, 23)");
          setState(676);
          match(PredaParser::T__18);
          setState(677);
          expression(24);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  21;
          break;
        }

        case 10: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(680);

          if (!(precpred(_ctx, 22))) throw FailedPredicateException(this, "precpred(_ctx, 22)");
          setState(681);
          match(PredaParser::T__37);
          setState(682);
          expression(23);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  22;
          break;
        }

        case 11: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(685);

          if (!(precpred(_ctx, 21))) throw FailedPredicateException(this, "precpred(_ctx, 21)");
          setState(686);
          match(PredaParser::T__38);
          setState(687);
          expression(22);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  23;
          break;
        }

        case 12: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(690);

          if (!(precpred(_ctx, 20))) throw FailedPredicateException(this, "precpred(_ctx, 20)");
          setState(691);
          match(PredaParser::T__39);
          setState(692);
          expression(21);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  24;
          break;
        }

        case 13: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(695);

          if (!(precpred(_ctx, 19))) throw FailedPredicateException(this, "precpred(_ctx, 19)");
          setState(696);
          match(PredaParser::T__40);
          setState(697);
          expression(20);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  25;
          break;
        }

        case 14: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(700);

          if (!(precpred(_ctx, 18))) throw FailedPredicateException(this, "precpred(_ctx, 18)");
          setState(701);
          match(PredaParser::T__41);
          setState(702);
          expression(19);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  26;
          break;
        }

        case 15: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(705);

          if (!(precpred(_ctx, 17))) throw FailedPredicateException(this, "precpred(_ctx, 17)");
          setState(706);
          match(PredaParser::T__23);
          setState(707);
          expression(18);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  27;
          break;
        }

        case 16: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(710);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(711);
          match(PredaParser::T__42);
          setState(712);
          expression(17);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  28;
          break;
        }

        case 17: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(715);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(716);
          match(PredaParser::T__43);
          setState(717);
          expression(16);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  29;
          break;
        }

        case 18: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(720);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(721);
          match(PredaParser::T__44);
          setState(722);
          expression(15);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  30;
          break;
        }

        case 19: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(725);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(726);
          match(PredaParser::T__45);
          setState(727);
          expression(0);
          setState(728);
          match(PredaParser::T__46);
          setState(729);
          expression(14);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  31;
          break;
        }

        case 20: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(732);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(733);
          match(PredaParser::T__5);
          setState(734);
          expression(13);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  32;
          break;
        }

        case 21: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(737);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(738);
          match(PredaParser::T__47);
          setState(739);
          expression(12);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  33;
          break;
        }

        case 22: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(742);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(743);
          match(PredaParser::T__48);
          setState(744);
          expression(11);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  34;
          break;
        }

        case 23: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(747);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(748);
          match(PredaParser::T__49);
          setState(749);
          expression(10);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  35;
          break;
        }

        case 24: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(752);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(753);
          match(PredaParser::T__50);
          setState(754);
          expression(9);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  36;
          break;
        }

        case 25: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(757);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(758);
          match(PredaParser::T__51);
          setState(759);
          expression(8);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  37;
          break;
        }

        case 26: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(762);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(763);
          match(PredaParser::T__52);
          setState(764);
          expression(7);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  38;
          break;
        }

        case 27: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(767);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(768);
          match(PredaParser::T__53);
          setState(769);
          expression(6);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  39;
          break;
        }

        case 28: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(772);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(773);
          match(PredaParser::T__54);
          setState(774);
          expression(5);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  40;
          break;
        }

        case 29: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(777);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(778);
          match(PredaParser::T__55);
          setState(779);
          expression(4);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  41;
          break;
        }

        case 30: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(782);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(783);
          match(PredaParser::T__56);
          setState(784);
          expression(3);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  42;
          break;
        }

        case 31: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(787);

          if (!(precpred(_ctx, 44))) throw FailedPredicateException(this, "precpred(_ctx, 44)");
          setState(788);
          match(PredaParser::T__27);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  0;
          break;
        }

        case 32: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(790);

          if (!(precpred(_ctx, 43))) throw FailedPredicateException(this, "precpred(_ctx, 43)");
          setState(791);
          match(PredaParser::T__28);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  1;
          break;
        }

        case 33: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(793);

          if (!(precpred(_ctx, 42))) throw FailedPredicateException(this, "precpred(_ctx, 42)");
          setState(794);
          match(PredaParser::T__2);
          setState(795);
          expression(0);
          setState(796);
          match(PredaParser::T__4);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  2;
          break;
        }

        case 34: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(799);

          if (!(precpred(_ctx, 41))) throw FailedPredicateException(this, "precpred(_ctx, 41)");
          setState(800);
          match(PredaParser::T__9);
          setState(801);
          functionCallArguments();
          setState(802);
          match(PredaParser::T__10);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  3;
          break;
        }

        case 35: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(805);

          if (!(precpred(_ctx, 40))) throw FailedPredicateException(this, "precpred(_ctx, 40)");
          setState(806);
          match(PredaParser::T__0);
          setState(807);
          identifier();
          antlrcpp::downCast<ExpressionContext *>(_localctx)->expressionType =  4;
          break;
        }

        default:
          break;
        } 
      }
      setState(814);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- PrimaryExpressionContext ------------------------------------------------------------------

PredaParser::PrimaryExpressionContext::PrimaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaParser::PrimaryExpressionContext::BooleanLiteral() {
  return getToken(PredaParser::BooleanLiteral, 0);
}

tree::TerminalNode* PredaParser::PrimaryExpressionContext::DecimalIntegerLiteral() {
  return getToken(PredaParser::DecimalIntegerLiteral, 0);
}

tree::TerminalNode* PredaParser::PrimaryExpressionContext::DecimalFloatLiteral() {
  return getToken(PredaParser::DecimalFloatLiteral, 0);
}

tree::TerminalNode* PredaParser::PrimaryExpressionContext::HexIntegerLiteral() {
  return getToken(PredaParser::HexIntegerLiteral, 0);
}

tree::TerminalNode* PredaParser::PrimaryExpressionContext::DecimalBigIntegerLiteral() {
  return getToken(PredaParser::DecimalBigIntegerLiteral, 0);
}

tree::TerminalNode* PredaParser::PrimaryExpressionContext::HexBigIntegerLiteral() {
  return getToken(PredaParser::HexBigIntegerLiteral, 0);
}

tree::TerminalNode* PredaParser::PrimaryExpressionContext::StringLiteral() {
  return getToken(PredaParser::StringLiteral, 0);
}

tree::TerminalNode* PredaParser::PrimaryExpressionContext::AddressLiteral() {
  return getToken(PredaParser::AddressLiteral, 0);
}

tree::TerminalNode* PredaParser::PrimaryExpressionContext::HashLiteral() {
  return getToken(PredaParser::HashLiteral, 0);
}

PredaParser::IdentifierContext* PredaParser::PrimaryExpressionContext::identifier() {
  return getRuleContext<PredaParser::IdentifierContext>(0);
}

PredaParser::FundamentalTypeNameContext* PredaParser::PrimaryExpressionContext::fundamentalTypeName() {
  return getRuleContext<PredaParser::FundamentalTypeNameContext>(0);
}

PredaParser::BuiltInContainerTypeNameContext* PredaParser::PrimaryExpressionContext::builtInContainerTypeName() {
  return getRuleContext<PredaParser::BuiltInContainerTypeNameContext>(0);
}


size_t PredaParser::PrimaryExpressionContext::getRuleIndex() const {
  return PredaParser::RulePrimaryExpression;
}

void PredaParser::PrimaryExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimaryExpression(this);
}

void PredaParser::PrimaryExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimaryExpression(this);
}


std::any PredaParser::PrimaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitPrimaryExpression(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::PrimaryExpressionContext* PredaParser::primaryExpression() {
  PrimaryExpressionContext *_localctx = _tracker.createInstance<PrimaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 104, PredaParser::RulePrimaryExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(827);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaParser::BooleanLiteral: {
        enterOuterAlt(_localctx, 1);
        setState(815);
        match(PredaParser::BooleanLiteral);
        break;
      }

      case PredaParser::DecimalIntegerLiteral: {
        enterOuterAlt(_localctx, 2);
        setState(816);
        match(PredaParser::DecimalIntegerLiteral);
        break;
      }

      case PredaParser::DecimalFloatLiteral: {
        enterOuterAlt(_localctx, 3);
        setState(817);
        match(PredaParser::DecimalFloatLiteral);
        break;
      }

      case PredaParser::HexIntegerLiteral: {
        enterOuterAlt(_localctx, 4);
        setState(818);
        match(PredaParser::HexIntegerLiteral);
        break;
      }

      case PredaParser::DecimalBigIntegerLiteral: {
        enterOuterAlt(_localctx, 5);
        setState(819);
        match(PredaParser::DecimalBigIntegerLiteral);
        break;
      }

      case PredaParser::HexBigIntegerLiteral: {
        enterOuterAlt(_localctx, 6);
        setState(820);
        match(PredaParser::HexBigIntegerLiteral);
        break;
      }

      case PredaParser::StringLiteral: {
        enterOuterAlt(_localctx, 7);
        setState(821);
        match(PredaParser::StringLiteral);
        break;
      }

      case PredaParser::AddressLiteral: {
        enterOuterAlt(_localctx, 8);
        setState(822);
        match(PredaParser::AddressLiteral);
        break;
      }

      case PredaParser::HashLiteral: {
        enterOuterAlt(_localctx, 9);
        setState(823);
        match(PredaParser::HashLiteral);
        break;
      }

      case PredaParser::Identifier: {
        enterOuterAlt(_localctx, 10);
        setState(824);
        identifier();
        break;
      }

      case PredaParser::T__11:
      case PredaParser::T__12:
      case PredaParser::T__13:
      case PredaParser::T__14:
      case PredaParser::T__15:
      case PredaParser::AddressKeyword:
      case PredaParser::FloatType:
      case PredaParser::IntType:
      case PredaParser::UintType: {
        enterOuterAlt(_localctx, 11);
        setState(825);
        fundamentalTypeName();
        break;
      }

      case PredaParser::T__16:
      case PredaParser::T__19:
      case PredaParser::T__20:
      case PredaParser::T__21: {
        enterOuterAlt(_localctx, 12);
        setState(826);
        builtInContainerTypeName();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionCallArgumentsContext ------------------------------------------------------------------

PredaParser::FunctionCallArgumentsContext::FunctionCallArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PredaParser::ExpressionContext *> PredaParser::FunctionCallArgumentsContext::expression() {
  return getRuleContexts<PredaParser::ExpressionContext>();
}

PredaParser::ExpressionContext* PredaParser::FunctionCallArgumentsContext::expression(size_t i) {
  return getRuleContext<PredaParser::ExpressionContext>(i);
}


size_t PredaParser::FunctionCallArgumentsContext::getRuleIndex() const {
  return PredaParser::RuleFunctionCallArguments;
}

void PredaParser::FunctionCallArgumentsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCallArguments(this);
}

void PredaParser::FunctionCallArgumentsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCallArguments(this);
}


std::any PredaParser::FunctionCallArgumentsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitFunctionCallArguments(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::FunctionCallArgumentsContext* PredaParser::functionCallArguments() {
  FunctionCallArgumentsContext *_localctx = _tracker.createInstance<FunctionCallArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 106, PredaParser::RuleFunctionCallArguments);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(837);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 16919032832) != 0) || ((((_la - 70) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 70)) & 4152246273) != 0)) {
      setState(829);
      expression(0);
      setState(834);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == PredaParser::T__3) {
        setState(830);
        match(PredaParser::T__3);
        setState(831);
        expression(0);
        setState(836);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierContext ------------------------------------------------------------------

PredaParser::IdentifierContext::IdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaParser::IdentifierContext::Identifier() {
  return getToken(PredaParser::Identifier, 0);
}


size_t PredaParser::IdentifierContext::getRuleIndex() const {
  return PredaParser::RuleIdentifier;
}

void PredaParser::IdentifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifier(this);
}

void PredaParser::IdentifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifier(this);
}


std::any PredaParser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PredaVisitor*>(visitor))
    return parserVisitor->visitIdentifier(this);
  else
    return visitor->visitChildren(this);
}

PredaParser::IdentifierContext* PredaParser::identifier() {
  IdentifierContext *_localctx = _tracker.createInstance<IdentifierContext>(_ctx, getState());
  enterRule(_localctx, 108, PredaParser::RuleIdentifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(839);
    match(PredaParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool PredaParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 51: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool PredaParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 31);
    case 1: return precpred(_ctx, 30);
    case 2: return precpred(_ctx, 29);
    case 3: return precpred(_ctx, 28);
    case 4: return precpred(_ctx, 27);
    case 5: return precpred(_ctx, 26);
    case 6: return precpred(_ctx, 25);
    case 7: return precpred(_ctx, 24);
    case 8: return precpred(_ctx, 23);
    case 9: return precpred(_ctx, 22);
    case 10: return precpred(_ctx, 21);
    case 11: return precpred(_ctx, 20);
    case 12: return precpred(_ctx, 19);
    case 13: return precpred(_ctx, 18);
    case 14: return precpred(_ctx, 17);
    case 15: return precpred(_ctx, 16);
    case 16: return precpred(_ctx, 15);
    case 17: return precpred(_ctx, 14);
    case 18: return precpred(_ctx, 13);
    case 19: return precpred(_ctx, 12);
    case 20: return precpred(_ctx, 11);
    case 21: return precpred(_ctx, 10);
    case 22: return precpred(_ctx, 9);
    case 23: return precpred(_ctx, 8);
    case 24: return precpred(_ctx, 7);
    case 25: return precpred(_ctx, 6);
    case 26: return precpred(_ctx, 5);
    case 27: return precpred(_ctx, 4);
    case 28: return precpred(_ctx, 3);
    case 29: return precpred(_ctx, 2);
    case 30: return precpred(_ctx, 44);
    case 31: return precpred(_ctx, 43);
    case 32: return precpred(_ctx, 42);
    case 33: return precpred(_ctx, 41);
    case 34: return precpred(_ctx, 40);

  default:
    break;
  }
  return true;
}

void PredaParser::initialize() {
  ::antlr4::internal::call_once(predaParserOnceFlag, predaParserInitialize);
}
