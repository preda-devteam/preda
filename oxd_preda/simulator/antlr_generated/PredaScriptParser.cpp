
// Generated from PredaScript.g4 by ANTLR 4.12.0


#include "PredaScriptListener.h"

#include "PredaScriptParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct PredaScriptParserStaticData final {
  PredaScriptParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  PredaScriptParserStaticData(const PredaScriptParserStaticData&) = delete;
  PredaScriptParserStaticData(PredaScriptParserStaticData&&) = delete;
  PredaScriptParserStaticData& operator=(const PredaScriptParserStaticData&) = delete;
  PredaScriptParserStaticData& operator=(PredaScriptParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag predascriptParserOnceFlag;
PredaScriptParserStaticData *predascriptParserStaticData = nullptr;

void predascriptParserInitialize() {
  assert(predascriptParserStaticData == nullptr);
  auto staticData = std::make_unique<PredaScriptParserStaticData>(
    std::vector<std::string>{
      "scripts", "script", "chainOperation", "awaitChain", "stepChain", 
      "runChain", "stopChain", "getChainInfo", "deployContractOnChain", 
      "contractProperties", "contractProperty", "predaFile", "xtlFile", 
      "batchInsertTxnOnChain", "setGasLimit", "variableDeclaration", "variableAssign", 
      "varName", "varValue", "dataReadFromFile", "csvfilePath", "config", 
      "configState", "setContractState", "stateScope", "updateState", "tokenState", 
      "mintToken", "tokenSymbol", "loadState", "jsonFilePath", "saveState", 
      "configAddress", "configRandomizer", "issueTxn", "txnReturnInfo", 
      "contractId", "contractName", "cvid", "functionName", "count", "scope", 
      "shardScope", "addressScope", "jsonParameters", "jsonParameter", "jsonKey", 
      "jsonValue", "primaryValue", "arrayValue", "concreteValue", "toBeAssignedValue", 
      "bigintRandom", "intExpression", "intRandom", "randomRange", "suppliedTokens", 
      "token", "debugInfo", "logInfo", "normalLog", "logHighlight", "logWarning", 
      "logError", "timeInfo", "stopWatchRestart", "stopWatchReport", "viz", 
      "vizBlock", "vizAddr", "vizShard", "vizTxn", "vizTrace", "vizSection", 
      "vizProfiling", "vizUintScope", "uintScope", "scopeTarget", "numberLiteral", 
      "hexLiteral", "stringLiteral", "boolLiteral", "ed25519Address", "identifier", 
      "fileName", "directivePath"
    },
    std::vector<std::string>{
      "", "'chain.await'", "'chain.step'", "'chain.run'", "'chain.stop'", 
      "'chain.info'", "'chain.deploy'", "'='", "'.prd'", "':'", "'.xtl'", 
      "'chain.batch_insert_txn'", "'chain.gaslimit'", "'.'", "'csv.from'", 
      "'('", "')'", "'.csv'", "'state.set'", "'state.update'", "'state'", 
      "'token'", "'by'", "'-'", "'state.load'", "'<'", "'>'", "'.json'", 
      "'state.save'", "'allocate.address'", "'reseed'", "'<='", "'['", "']'", 
      "'*'", "'#g'", "'#'", "'@'", "'{'", "','", "'}'", "'$'", "'/'", "'+'", 
      "'log'", "'log.highlight'", "'log.warning'", "'log.error'", "'stopwatch.restart'", 
      "'stopwatch.report'", "'viz.block'", "'viz.addr'", "'viz.shard'", 
      "'viz.txn'", "'viz.trace'", "'viz.section'", "'viz.profiling'", "'viz.uint_scope'", 
      "", "", "'random'", "'bigint'", "'all'", "'global'", "'shard'", "'address'", 
      "'true'", "'false'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "WASM", "NATIVE", "RANDOM", "BIGINT", 
      "ALL", "GLOBAL", "SHARD", "ADDRESS", "TrueKeyword", "FalseKeyword", 
      "DecimalNumber", "HexNumber", "StringLiteral", "Ed25519Address", "Identifier", 
      "WINPATH", "WIN_ABSOLUTE_PATH", "WIN_REALATIVE_PATH", "UNIXPATH", 
      "UNIX_ABSOLUTE_PATH", "UNIX_REALATIVE_PATH", "NotDefinedValue", "NewLineBackSlash", 
      "WS", "CommentSingleLine", "CommentMultiLine"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,83,676,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,2,63,7,
  	63,2,64,7,64,2,65,7,65,2,66,7,66,2,67,7,67,2,68,7,68,2,69,7,69,2,70,7,
  	70,2,71,7,71,2,72,7,72,2,73,7,73,2,74,7,74,2,75,7,75,2,76,7,76,2,77,7,
  	77,2,78,7,78,2,79,7,79,2,80,7,80,2,81,7,81,2,82,7,82,2,83,7,83,2,84,7,
  	84,2,85,7,85,1,0,5,0,174,8,0,10,0,12,0,177,9,0,1,0,1,0,1,1,1,1,1,1,1,
  	1,1,1,1,1,3,1,187,8,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,197,8,2,1,3,
  	1,3,1,4,1,4,1,5,1,5,1,6,1,6,1,7,1,7,1,8,1,8,1,8,3,8,212,8,8,1,8,1,8,1,
  	9,5,9,217,8,9,10,9,12,9,220,9,9,1,10,1,10,3,10,224,8,10,1,10,1,10,3,10,
  	228,8,10,1,11,3,11,231,8,11,1,11,1,11,1,11,1,11,3,11,237,8,11,1,12,3,
  	12,240,8,12,1,12,1,12,1,12,1,13,1,13,1,13,1,14,1,14,1,14,3,14,251,8,14,
  	1,14,1,14,1,15,1,15,3,15,257,8,15,1,16,1,16,1,16,1,16,1,17,1,17,1,18,
  	1,18,1,18,3,18,268,8,18,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,20,3,20,
  	278,8,20,1,20,1,20,1,20,1,21,1,21,1,21,3,21,286,8,21,1,22,1,22,1,22,1,
  	22,1,22,3,22,293,8,22,1,23,1,23,1,23,1,23,1,23,3,23,300,8,23,1,23,1,23,
  	1,24,1,24,1,25,1,25,1,25,1,25,1,25,3,25,311,8,25,1,25,1,25,1,26,1,26,
  	1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,28,1,28,5,28,327,8,28,10,28,
  	12,28,330,9,28,1,29,1,29,1,29,1,29,1,29,1,29,1,30,3,30,339,8,30,1,30,
  	1,30,3,30,343,8,30,1,31,1,31,1,31,1,31,1,31,3,31,350,8,31,1,31,1,31,1,
  	32,1,32,3,32,356,8,32,1,33,1,33,1,33,1,33,3,33,362,8,33,1,34,1,34,1,34,
  	3,34,367,8,34,1,34,1,34,1,34,1,34,3,34,373,8,34,1,34,3,34,376,8,34,1,
  	34,3,34,379,8,34,1,34,1,34,3,34,383,8,34,1,35,1,35,1,35,3,35,388,8,35,
  	1,36,1,36,3,36,392,8,36,1,37,1,37,1,37,3,37,397,8,37,1,37,1,37,1,38,1,
  	38,1,39,1,39,1,40,1,40,1,40,1,41,1,41,3,41,410,8,41,1,42,1,42,1,42,1,
  	42,1,42,1,42,3,42,418,8,42,3,42,420,8,42,1,43,1,43,1,43,1,43,1,43,1,43,
  	3,43,428,8,43,1,44,1,44,3,44,432,8,44,1,44,1,44,5,44,436,8,44,10,44,12,
  	44,439,9,44,1,44,1,44,1,45,1,45,1,45,1,45,1,46,1,46,3,46,449,8,46,1,47,
  	1,47,1,47,3,47,454,8,47,1,48,1,48,1,48,3,48,459,8,48,1,49,1,49,3,49,463,
  	8,49,1,49,1,49,5,49,467,8,49,10,49,12,49,470,9,49,1,49,1,49,1,50,1,50,
  	1,50,1,50,3,50,478,8,50,1,51,1,51,1,51,1,51,3,51,484,8,51,1,51,1,51,1,
  	52,1,52,1,52,1,52,1,52,1,52,1,52,1,53,1,53,1,53,1,53,1,53,1,53,1,53,3,
  	53,502,8,53,1,53,1,53,1,53,1,53,1,53,1,53,1,53,1,53,1,53,1,53,1,53,1,
  	53,1,53,1,53,1,53,1,53,1,53,1,53,1,53,1,53,5,53,524,8,53,10,53,12,53,
  	527,9,53,1,54,1,54,3,54,531,8,54,1,55,1,55,1,55,1,55,1,55,1,55,1,56,1,
  	56,3,56,541,8,56,1,56,1,56,5,56,545,8,56,10,56,12,56,548,9,56,1,56,1,
  	56,1,57,1,57,1,57,1,57,1,57,3,57,557,8,57,1,57,1,57,1,58,1,58,3,58,563,
  	8,58,1,59,1,59,1,59,1,59,3,59,569,8,59,1,60,1,60,1,60,1,61,1,61,1,61,
  	1,62,1,62,1,62,1,63,1,63,1,63,1,64,1,64,3,64,585,8,64,1,65,1,65,1,66,
  	1,66,1,67,1,67,1,67,1,67,1,67,1,67,1,67,1,67,3,67,599,8,67,1,68,1,68,
  	1,68,1,68,3,68,605,8,68,1,69,1,69,1,69,3,69,610,8,69,1,70,1,70,1,70,3,
  	70,615,8,70,1,71,1,71,1,71,1,71,1,71,1,71,3,71,623,8,71,1,72,1,72,1,72,
  	1,72,1,72,1,72,3,72,631,8,72,1,73,1,73,1,73,1,74,1,74,1,75,1,75,1,75,
  	1,75,1,75,1,75,1,76,1,76,1,76,3,76,647,8,76,1,77,1,77,3,77,651,8,77,1,
  	78,3,78,654,8,78,1,78,1,78,1,79,1,79,1,80,1,80,1,81,1,81,1,82,1,82,1,
  	83,1,83,1,84,5,84,669,8,84,10,84,12,84,672,9,84,1,85,1,85,1,85,0,1,106,
  	86,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,
  	48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,
  	94,96,98,100,102,104,106,108,110,112,114,116,118,120,122,124,126,128,
  	130,132,134,136,138,140,142,144,146,148,150,152,154,156,158,160,162,164,
  	166,168,170,0,5,1,0,58,59,1,0,63,65,1,0,66,67,2,0,23,23,72,72,2,0,73,
  	73,76,76,690,0,175,1,0,0,0,2,186,1,0,0,0,4,196,1,0,0,0,6,198,1,0,0,0,
  	8,200,1,0,0,0,10,202,1,0,0,0,12,204,1,0,0,0,14,206,1,0,0,0,16,208,1,0,
  	0,0,18,218,1,0,0,0,20,223,1,0,0,0,22,230,1,0,0,0,24,239,1,0,0,0,26,244,
  	1,0,0,0,28,247,1,0,0,0,30,256,1,0,0,0,32,258,1,0,0,0,34,262,1,0,0,0,36,
  	267,1,0,0,0,38,269,1,0,0,0,40,277,1,0,0,0,42,285,1,0,0,0,44,292,1,0,0,
  	0,46,294,1,0,0,0,48,303,1,0,0,0,50,305,1,0,0,0,52,314,1,0,0,0,54,316,
  	1,0,0,0,56,328,1,0,0,0,58,331,1,0,0,0,60,338,1,0,0,0,62,344,1,0,0,0,64,
  	353,1,0,0,0,66,357,1,0,0,0,68,366,1,0,0,0,70,384,1,0,0,0,72,391,1,0,0,
  	0,74,396,1,0,0,0,76,400,1,0,0,0,78,402,1,0,0,0,80,404,1,0,0,0,82,409,
  	1,0,0,0,84,419,1,0,0,0,86,421,1,0,0,0,88,429,1,0,0,0,90,442,1,0,0,0,92,
  	448,1,0,0,0,94,453,1,0,0,0,96,458,1,0,0,0,98,460,1,0,0,0,100,477,1,0,
  	0,0,102,479,1,0,0,0,104,487,1,0,0,0,106,501,1,0,0,0,108,528,1,0,0,0,110,
  	532,1,0,0,0,112,538,1,0,0,0,114,556,1,0,0,0,116,562,1,0,0,0,118,568,1,
  	0,0,0,120,570,1,0,0,0,122,573,1,0,0,0,124,576,1,0,0,0,126,579,1,0,0,0,
  	128,584,1,0,0,0,130,586,1,0,0,0,132,588,1,0,0,0,134,598,1,0,0,0,136,600,
  	1,0,0,0,138,606,1,0,0,0,140,611,1,0,0,0,142,616,1,0,0,0,144,624,1,0,0,
  	0,146,632,1,0,0,0,148,635,1,0,0,0,150,637,1,0,0,0,152,643,1,0,0,0,154,
  	650,1,0,0,0,156,653,1,0,0,0,158,657,1,0,0,0,160,659,1,0,0,0,162,661,1,
  	0,0,0,164,663,1,0,0,0,166,665,1,0,0,0,168,670,1,0,0,0,170,673,1,0,0,0,
  	172,174,3,2,1,0,173,172,1,0,0,0,174,177,1,0,0,0,175,173,1,0,0,0,175,176,
  	1,0,0,0,176,178,1,0,0,0,177,175,1,0,0,0,178,179,5,0,0,1,179,1,1,0,0,0,
  	180,187,3,4,2,0,181,187,3,30,15,0,182,187,3,42,21,0,183,187,3,68,34,0,
  	184,187,3,116,58,0,185,187,3,134,67,0,186,180,1,0,0,0,186,181,1,0,0,0,
  	186,182,1,0,0,0,186,183,1,0,0,0,186,184,1,0,0,0,186,185,1,0,0,0,187,3,
  	1,0,0,0,188,197,3,6,3,0,189,197,3,8,4,0,190,197,3,10,5,0,191,197,3,12,
  	6,0,192,197,3,14,7,0,193,197,3,16,8,0,194,197,3,26,13,0,195,197,3,28,
  	14,0,196,188,1,0,0,0,196,189,1,0,0,0,196,190,1,0,0,0,196,191,1,0,0,0,
  	196,192,1,0,0,0,196,193,1,0,0,0,196,194,1,0,0,0,196,195,1,0,0,0,197,5,
  	1,0,0,0,198,199,5,1,0,0,199,7,1,0,0,0,200,201,5,2,0,0,201,9,1,0,0,0,202,
  	203,5,3,0,0,203,11,1,0,0,0,204,205,5,4,0,0,205,13,1,0,0,0,206,207,5,5,
  	0,0,207,15,1,0,0,0,208,211,5,6,0,0,209,212,3,86,43,0,210,212,3,84,42,
  	0,211,209,1,0,0,0,211,210,1,0,0,0,212,213,1,0,0,0,213,214,3,18,9,0,214,
  	17,1,0,0,0,215,217,3,20,10,0,216,215,1,0,0,0,217,220,1,0,0,0,218,216,
  	1,0,0,0,218,219,1,0,0,0,219,19,1,0,0,0,220,218,1,0,0,0,221,224,3,22,11,
  	0,222,224,3,24,12,0,223,221,1,0,0,0,223,222,1,0,0,0,224,227,1,0,0,0,225,
  	226,5,7,0,0,226,228,3,88,44,0,227,225,1,0,0,0,227,228,1,0,0,0,228,21,
  	1,0,0,0,229,231,3,170,85,0,230,229,1,0,0,0,230,231,1,0,0,0,231,232,1,
  	0,0,0,232,233,3,166,83,0,233,236,5,8,0,0,234,235,5,9,0,0,235,237,7,0,
  	0,0,236,234,1,0,0,0,236,237,1,0,0,0,237,23,1,0,0,0,238,240,3,170,85,0,
  	239,238,1,0,0,0,239,240,1,0,0,0,240,241,1,0,0,0,241,242,3,166,83,0,242,
  	243,5,10,0,0,243,25,1,0,0,0,244,245,5,11,0,0,245,246,3,34,17,0,246,27,
  	1,0,0,0,247,250,5,12,0,0,248,249,5,13,0,0,249,251,5,63,0,0,250,248,1,
  	0,0,0,250,251,1,0,0,0,251,252,1,0,0,0,252,253,3,156,78,0,253,29,1,0,0,
  	0,254,257,3,32,16,0,255,257,3,38,19,0,256,254,1,0,0,0,256,255,1,0,0,0,
  	257,31,1,0,0,0,258,259,3,34,17,0,259,260,5,7,0,0,260,261,3,36,18,0,261,
  	33,1,0,0,0,262,263,3,166,83,0,263,35,1,0,0,0,264,268,3,166,83,0,265,268,
  	3,160,80,0,266,268,3,156,78,0,267,264,1,0,0,0,267,265,1,0,0,0,267,266,
  	1,0,0,0,268,37,1,0,0,0,269,270,3,34,17,0,270,271,5,7,0,0,271,272,5,14,
  	0,0,272,273,5,15,0,0,273,274,3,40,20,0,274,275,5,16,0,0,275,39,1,0,0,
  	0,276,278,3,170,85,0,277,276,1,0,0,0,277,278,1,0,0,0,278,279,1,0,0,0,
  	279,280,3,168,84,0,280,281,5,17,0,0,281,41,1,0,0,0,282,286,3,44,22,0,
  	283,286,3,64,32,0,284,286,3,66,33,0,285,282,1,0,0,0,285,283,1,0,0,0,285,
  	284,1,0,0,0,286,43,1,0,0,0,287,293,3,46,23,0,288,293,3,50,25,0,289,293,
  	3,52,26,0,290,293,3,58,29,0,291,293,3,62,31,0,292,287,1,0,0,0,292,288,
  	1,0,0,0,292,289,1,0,0,0,292,290,1,0,0,0,292,291,1,0,0,0,293,45,1,0,0,
  	0,294,295,5,18,0,0,295,296,3,72,36,0,296,297,5,13,0,0,297,299,3,48,24,
  	0,298,300,3,82,41,0,299,298,1,0,0,0,299,300,1,0,0,0,300,301,1,0,0,0,301,
  	302,3,88,44,0,302,47,1,0,0,0,303,304,7,1,0,0,304,49,1,0,0,0,305,306,5,
  	19,0,0,306,307,3,72,36,0,307,308,5,13,0,0,308,310,3,48,24,0,309,311,3,
  	82,41,0,310,309,1,0,0,0,310,311,1,0,0,0,311,312,1,0,0,0,312,313,3,88,
  	44,0,313,51,1,0,0,0,314,315,3,54,27,0,315,53,1,0,0,0,316,317,5,20,0,0,
  	317,318,5,13,0,0,318,319,5,21,0,0,319,320,3,166,83,0,320,321,3,56,28,
  	0,321,322,5,22,0,0,322,323,3,72,36,0,323,55,1,0,0,0,324,327,3,166,83,
  	0,325,327,5,23,0,0,326,324,1,0,0,0,326,325,1,0,0,0,327,330,1,0,0,0,328,
  	326,1,0,0,0,328,329,1,0,0,0,329,57,1,0,0,0,330,328,1,0,0,0,331,332,5,
  	24,0,0,332,333,5,25,0,0,333,334,3,48,24,0,334,335,5,26,0,0,335,336,3,
  	60,30,0,336,59,1,0,0,0,337,339,3,170,85,0,338,337,1,0,0,0,338,339,1,0,
  	0,0,339,340,1,0,0,0,340,342,3,168,84,0,341,343,5,27,0,0,342,341,1,0,0,
  	0,342,343,1,0,0,0,343,61,1,0,0,0,344,345,5,28,0,0,345,346,3,48,24,0,346,
  	349,5,13,0,0,347,350,3,72,36,0,348,350,5,62,0,0,349,347,1,0,0,0,349,348,
  	1,0,0,0,350,351,1,0,0,0,351,352,3,168,84,0,352,63,1,0,0,0,353,355,5,29,
  	0,0,354,356,3,156,78,0,355,354,1,0,0,0,355,356,1,0,0,0,356,65,1,0,0,0,
  	357,358,5,60,0,0,358,359,5,13,0,0,359,361,5,30,0,0,360,362,3,156,78,0,
  	361,360,1,0,0,0,361,362,1,0,0,0,362,67,1,0,0,0,363,364,3,70,35,0,364,
  	365,5,7,0,0,365,367,1,0,0,0,366,363,1,0,0,0,366,367,1,0,0,0,367,368,1,
  	0,0,0,368,369,3,72,36,0,369,370,5,13,0,0,370,372,3,78,39,0,371,373,3,
  	80,40,0,372,371,1,0,0,0,372,373,1,0,0,0,373,375,1,0,0,0,374,376,3,82,
  	41,0,375,374,1,0,0,0,375,376,1,0,0,0,376,378,1,0,0,0,377,379,3,88,44,
  	0,378,377,1,0,0,0,378,379,1,0,0,0,379,382,1,0,0,0,380,381,5,31,0,0,381,
  	383,3,112,56,0,382,380,1,0,0,0,382,383,1,0,0,0,383,69,1,0,0,0,384,387,
  	3,166,83,0,385,386,5,32,0,0,386,388,5,33,0,0,387,385,1,0,0,0,387,388,
  	1,0,0,0,388,71,1,0,0,0,389,392,3,74,37,0,390,392,3,76,38,0,391,389,1,
  	0,0,0,391,390,1,0,0,0,392,73,1,0,0,0,393,394,3,166,83,0,394,395,5,13,
  	0,0,395,397,1,0,0,0,396,393,1,0,0,0,396,397,1,0,0,0,397,398,1,0,0,0,398,
  	399,3,166,83,0,399,75,1,0,0,0,400,401,3,156,78,0,401,77,1,0,0,0,402,403,
  	3,166,83,0,403,79,1,0,0,0,404,405,5,34,0,0,405,406,3,156,78,0,406,81,
  	1,0,0,0,407,410,3,84,42,0,408,410,3,86,43,0,409,407,1,0,0,0,409,408,1,
  	0,0,0,410,83,1,0,0,0,411,420,5,35,0,0,412,417,5,36,0,0,413,418,3,156,
  	78,0,414,418,3,166,83,0,415,418,5,60,0,0,416,418,5,62,0,0,417,413,1,0,
  	0,0,417,414,1,0,0,0,417,415,1,0,0,0,417,416,1,0,0,0,418,420,1,0,0,0,419,
  	411,1,0,0,0,419,412,1,0,0,0,420,85,1,0,0,0,421,427,5,37,0,0,422,428,3,
  	156,78,0,423,428,3,166,83,0,424,428,5,60,0,0,425,428,5,62,0,0,426,428,
  	3,164,82,0,427,422,1,0,0,0,427,423,1,0,0,0,427,424,1,0,0,0,427,425,1,
  	0,0,0,427,426,1,0,0,0,428,87,1,0,0,0,429,431,5,38,0,0,430,432,3,90,45,
  	0,431,430,1,0,0,0,431,432,1,0,0,0,432,437,1,0,0,0,433,434,5,39,0,0,434,
  	436,3,90,45,0,435,433,1,0,0,0,436,439,1,0,0,0,437,435,1,0,0,0,437,438,
  	1,0,0,0,438,440,1,0,0,0,439,437,1,0,0,0,440,441,5,40,0,0,441,89,1,0,0,
  	0,442,443,3,92,46,0,443,444,5,9,0,0,444,445,3,94,47,0,445,91,1,0,0,0,
  	446,449,3,166,83,0,447,449,3,100,50,0,448,446,1,0,0,0,448,447,1,0,0,0,
  	449,93,1,0,0,0,450,454,3,88,44,0,451,454,3,96,48,0,452,454,3,166,83,0,
  	453,450,1,0,0,0,453,451,1,0,0,0,453,452,1,0,0,0,454,95,1,0,0,0,455,459,
  	3,98,49,0,456,459,3,100,50,0,457,459,3,102,51,0,458,455,1,0,0,0,458,456,
  	1,0,0,0,458,457,1,0,0,0,459,97,1,0,0,0,460,462,5,32,0,0,461,463,3,94,
  	47,0,462,461,1,0,0,0,462,463,1,0,0,0,463,468,1,0,0,0,464,465,5,39,0,0,
  	465,467,3,94,47,0,466,464,1,0,0,0,467,470,1,0,0,0,468,466,1,0,0,0,468,
  	469,1,0,0,0,469,471,1,0,0,0,470,468,1,0,0,0,471,472,5,33,0,0,472,99,1,
  	0,0,0,473,478,3,156,78,0,474,478,3,160,80,0,475,478,3,162,81,0,476,478,
  	3,158,79,0,477,473,1,0,0,0,477,474,1,0,0,0,477,475,1,0,0,0,477,476,1,
  	0,0,0,478,101,1,0,0,0,479,483,5,41,0,0,480,484,3,86,43,0,481,484,3,104,
  	52,0,482,484,3,106,53,0,483,480,1,0,0,0,483,481,1,0,0,0,483,482,1,0,0,
  	0,484,485,1,0,0,0,485,486,5,41,0,0,486,103,1,0,0,0,487,488,5,61,0,0,488,
  	489,5,13,0,0,489,490,5,60,0,0,490,491,5,15,0,0,491,492,3,156,78,0,492,
  	493,5,16,0,0,493,105,1,0,0,0,494,495,6,53,-1,0,495,496,3,108,54,0,496,
  	497,6,53,-1,0,497,502,1,0,0,0,498,499,3,156,78,0,499,500,6,53,-1,0,500,
  	502,1,0,0,0,501,494,1,0,0,0,501,498,1,0,0,0,502,525,1,0,0,0,503,504,10,
  	6,0,0,504,505,5,34,0,0,505,506,3,106,53,7,506,507,6,53,-1,0,507,524,1,
  	0,0,0,508,509,10,5,0,0,509,510,5,42,0,0,510,511,3,106,53,6,511,512,6,
  	53,-1,0,512,524,1,0,0,0,513,514,10,4,0,0,514,515,5,43,0,0,515,516,3,106,
  	53,5,516,517,6,53,-1,0,517,524,1,0,0,0,518,519,10,3,0,0,519,520,5,23,
  	0,0,520,521,3,106,53,4,521,522,6,53,-1,0,522,524,1,0,0,0,523,503,1,0,
  	0,0,523,508,1,0,0,0,523,513,1,0,0,0,523,518,1,0,0,0,524,527,1,0,0,0,525,
  	523,1,0,0,0,525,526,1,0,0,0,526,107,1,0,0,0,527,525,1,0,0,0,528,530,5,
  	60,0,0,529,531,3,110,55,0,530,529,1,0,0,0,530,531,1,0,0,0,531,109,1,0,
  	0,0,532,533,5,15,0,0,533,534,3,106,53,0,534,535,5,39,0,0,535,536,3,106,
  	53,0,536,537,5,16,0,0,537,111,1,0,0,0,538,540,5,15,0,0,539,541,3,114,
  	57,0,540,539,1,0,0,0,540,541,1,0,0,0,541,546,1,0,0,0,542,543,5,39,0,0,
  	543,545,3,114,57,0,544,542,1,0,0,0,545,548,1,0,0,0,546,544,1,0,0,0,546,
  	547,1,0,0,0,547,549,1,0,0,0,548,546,1,0,0,0,549,550,5,16,0,0,550,113,
  	1,0,0,0,551,557,3,156,78,0,552,553,5,41,0,0,553,554,3,106,53,0,554,555,
  	5,41,0,0,555,557,1,0,0,0,556,551,1,0,0,0,556,552,1,0,0,0,557,558,1,0,
  	0,0,558,559,3,166,83,0,559,115,1,0,0,0,560,563,3,118,59,0,561,563,3,128,
  	64,0,562,560,1,0,0,0,562,561,1,0,0,0,563,117,1,0,0,0,564,569,3,120,60,
  	0,565,569,3,122,61,0,566,569,3,124,62,0,567,569,3,126,63,0,568,564,1,
  	0,0,0,568,565,1,0,0,0,568,566,1,0,0,0,568,567,1,0,0,0,569,119,1,0,0,0,
  	570,571,5,44,0,0,571,572,3,160,80,0,572,121,1,0,0,0,573,574,5,45,0,0,
  	574,575,3,160,80,0,575,123,1,0,0,0,576,577,5,46,0,0,577,578,3,160,80,
  	0,578,125,1,0,0,0,579,580,5,47,0,0,580,581,3,160,80,0,581,127,1,0,0,0,
  	582,585,3,130,65,0,583,585,3,132,66,0,584,582,1,0,0,0,584,583,1,0,0,0,
  	585,129,1,0,0,0,586,587,5,48,0,0,587,131,1,0,0,0,588,589,5,49,0,0,589,
  	133,1,0,0,0,590,599,3,136,68,0,591,599,3,138,69,0,592,599,3,140,70,0,
  	593,599,3,142,71,0,594,599,3,144,72,0,595,599,3,146,73,0,596,599,3,148,
  	74,0,597,599,3,150,75,0,598,590,1,0,0,0,598,591,1,0,0,0,598,592,1,0,0,
  	0,598,593,1,0,0,0,598,594,1,0,0,0,598,595,1,0,0,0,598,596,1,0,0,0,598,
  	597,1,0,0,0,599,135,1,0,0,0,600,601,5,50,0,0,601,604,3,84,42,0,602,603,
  	5,9,0,0,603,605,3,156,78,0,604,602,1,0,0,0,604,605,1,0,0,0,605,137,1,
  	0,0,0,606,607,5,51,0,0,607,609,3,86,43,0,608,610,3,74,37,0,609,608,1,
  	0,0,0,609,610,1,0,0,0,610,139,1,0,0,0,611,612,5,52,0,0,612,614,3,84,42,
  	0,613,615,3,74,37,0,614,613,1,0,0,0,614,615,1,0,0,0,615,141,1,0,0,0,616,
  	617,5,53,0,0,617,622,3,70,35,0,618,619,5,32,0,0,619,620,3,156,78,0,620,
  	621,5,33,0,0,621,623,1,0,0,0,622,618,1,0,0,0,622,623,1,0,0,0,623,143,
  	1,0,0,0,624,625,5,54,0,0,625,630,3,70,35,0,626,627,5,32,0,0,627,628,3,
  	156,78,0,628,629,5,33,0,0,629,631,1,0,0,0,630,626,1,0,0,0,630,631,1,0,
  	0,0,631,145,1,0,0,0,632,633,5,55,0,0,633,634,3,160,80,0,634,147,1,0,0,
  	0,635,636,5,56,0,0,636,149,1,0,0,0,637,638,5,57,0,0,638,639,3,152,76,
  	0,639,640,3,74,37,0,640,641,5,9,0,0,641,642,3,154,77,0,642,151,1,0,0,
  	0,643,646,5,36,0,0,644,647,5,62,0,0,645,647,3,156,78,0,646,644,1,0,0,
  	0,646,645,1,0,0,0,647,153,1,0,0,0,648,651,5,62,0,0,649,651,3,156,78,0,
  	650,648,1,0,0,0,650,649,1,0,0,0,651,155,1,0,0,0,652,654,5,23,0,0,653,
  	652,1,0,0,0,653,654,1,0,0,0,654,655,1,0,0,0,655,656,5,68,0,0,656,157,
  	1,0,0,0,657,658,5,69,0,0,658,159,1,0,0,0,659,660,5,70,0,0,660,161,1,0,
  	0,0,661,662,7,2,0,0,662,163,1,0,0,0,663,664,5,71,0,0,664,165,1,0,0,0,
  	665,666,5,72,0,0,666,167,1,0,0,0,667,669,7,3,0,0,668,667,1,0,0,0,669,
  	672,1,0,0,0,670,668,1,0,0,0,670,671,1,0,0,0,671,169,1,0,0,0,672,670,1,
  	0,0,0,673,674,7,4,0,0,674,171,1,0,0,0,66,175,186,196,211,218,223,227,
  	230,236,239,250,256,267,277,285,292,299,310,326,328,338,342,349,355,361,
  	366,372,375,378,382,387,391,396,409,417,419,427,431,437,448,453,458,462,
  	468,477,483,501,523,525,530,540,546,556,562,568,584,598,604,609,614,622,
  	630,646,650,653,670
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  predascriptParserStaticData = staticData.release();
}

}

PredaScriptParser::PredaScriptParser(TokenStream *input) : PredaScriptParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

PredaScriptParser::PredaScriptParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  PredaScriptParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *predascriptParserStaticData->atn, predascriptParserStaticData->decisionToDFA, predascriptParserStaticData->sharedContextCache, options);
}

PredaScriptParser::~PredaScriptParser() {
  delete _interpreter;
}

const atn::ATN& PredaScriptParser::getATN() const {
  return *predascriptParserStaticData->atn;
}

std::string PredaScriptParser::getGrammarFileName() const {
  return "PredaScript.g4";
}

const std::vector<std::string>& PredaScriptParser::getRuleNames() const {
  return predascriptParserStaticData->ruleNames;
}

const dfa::Vocabulary& PredaScriptParser::getVocabulary() const {
  return predascriptParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView PredaScriptParser::getSerializedATN() const {
  return predascriptParserStaticData->serializedATN;
}


//----------------- ScriptsContext ------------------------------------------------------------------

PredaScriptParser::ScriptsContext::ScriptsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaScriptParser::ScriptsContext::EOF() {
  return getToken(PredaScriptParser::EOF, 0);
}

std::vector<PredaScriptParser::ScriptContext *> PredaScriptParser::ScriptsContext::script() {
  return getRuleContexts<PredaScriptParser::ScriptContext>();
}

PredaScriptParser::ScriptContext* PredaScriptParser::ScriptsContext::script(size_t i) {
  return getRuleContext<PredaScriptParser::ScriptContext>(i);
}


size_t PredaScriptParser::ScriptsContext::getRuleIndex() const {
  return PredaScriptParser::RuleScripts;
}

void PredaScriptParser::ScriptsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterScripts(this);
}

void PredaScriptParser::ScriptsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitScripts(this);
}

PredaScriptParser::ScriptsContext* PredaScriptParser::scripts() {
  ScriptsContext *_localctx = _tracker.createInstance<ScriptsContext>(_ctx, getState());
  enterRule(_localctx, 0, PredaScriptParser::RuleScripts);
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
    setState(175);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1441134289404827774) != 0) || _la == PredaScriptParser::DecimalNumber

    || _la == PredaScriptParser::Identifier) {
      setState(172);
      script();
      setState(177);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(178);
    match(PredaScriptParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ScriptContext ------------------------------------------------------------------

PredaScriptParser::ScriptContext::ScriptContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::ChainOperationContext* PredaScriptParser::ScriptContext::chainOperation() {
  return getRuleContext<PredaScriptParser::ChainOperationContext>(0);
}

PredaScriptParser::VariableDeclarationContext* PredaScriptParser::ScriptContext::variableDeclaration() {
  return getRuleContext<PredaScriptParser::VariableDeclarationContext>(0);
}

PredaScriptParser::ConfigContext* PredaScriptParser::ScriptContext::config() {
  return getRuleContext<PredaScriptParser::ConfigContext>(0);
}

PredaScriptParser::IssueTxnContext* PredaScriptParser::ScriptContext::issueTxn() {
  return getRuleContext<PredaScriptParser::IssueTxnContext>(0);
}

PredaScriptParser::DebugInfoContext* PredaScriptParser::ScriptContext::debugInfo() {
  return getRuleContext<PredaScriptParser::DebugInfoContext>(0);
}

PredaScriptParser::VizContext* PredaScriptParser::ScriptContext::viz() {
  return getRuleContext<PredaScriptParser::VizContext>(0);
}


size_t PredaScriptParser::ScriptContext::getRuleIndex() const {
  return PredaScriptParser::RuleScript;
}

void PredaScriptParser::ScriptContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterScript(this);
}

void PredaScriptParser::ScriptContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitScript(this);
}

PredaScriptParser::ScriptContext* PredaScriptParser::script() {
  ScriptContext *_localctx = _tracker.createInstance<ScriptContext>(_ctx, getState());
  enterRule(_localctx, 2, PredaScriptParser::RuleScript);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(186);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(180);
      chainOperation();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(181);
      variableDeclaration();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(182);
      config();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(183);
      issueTxn();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(184);
      debugInfo();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(185);
      viz();
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

//----------------- ChainOperationContext ------------------------------------------------------------------

PredaScriptParser::ChainOperationContext::ChainOperationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::AwaitChainContext* PredaScriptParser::ChainOperationContext::awaitChain() {
  return getRuleContext<PredaScriptParser::AwaitChainContext>(0);
}

PredaScriptParser::StepChainContext* PredaScriptParser::ChainOperationContext::stepChain() {
  return getRuleContext<PredaScriptParser::StepChainContext>(0);
}

PredaScriptParser::RunChainContext* PredaScriptParser::ChainOperationContext::runChain() {
  return getRuleContext<PredaScriptParser::RunChainContext>(0);
}

PredaScriptParser::StopChainContext* PredaScriptParser::ChainOperationContext::stopChain() {
  return getRuleContext<PredaScriptParser::StopChainContext>(0);
}

PredaScriptParser::GetChainInfoContext* PredaScriptParser::ChainOperationContext::getChainInfo() {
  return getRuleContext<PredaScriptParser::GetChainInfoContext>(0);
}

PredaScriptParser::DeployContractOnChainContext* PredaScriptParser::ChainOperationContext::deployContractOnChain() {
  return getRuleContext<PredaScriptParser::DeployContractOnChainContext>(0);
}

PredaScriptParser::BatchInsertTxnOnChainContext* PredaScriptParser::ChainOperationContext::batchInsertTxnOnChain() {
  return getRuleContext<PredaScriptParser::BatchInsertTxnOnChainContext>(0);
}

PredaScriptParser::SetGasLimitContext* PredaScriptParser::ChainOperationContext::setGasLimit() {
  return getRuleContext<PredaScriptParser::SetGasLimitContext>(0);
}


size_t PredaScriptParser::ChainOperationContext::getRuleIndex() const {
  return PredaScriptParser::RuleChainOperation;
}

void PredaScriptParser::ChainOperationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChainOperation(this);
}

void PredaScriptParser::ChainOperationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChainOperation(this);
}

PredaScriptParser::ChainOperationContext* PredaScriptParser::chainOperation() {
  ChainOperationContext *_localctx = _tracker.createInstance<ChainOperationContext>(_ctx, getState());
  enterRule(_localctx, 4, PredaScriptParser::RuleChainOperation);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(196);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaScriptParser::T__0: {
        enterOuterAlt(_localctx, 1);
        setState(188);
        awaitChain();
        break;
      }

      case PredaScriptParser::T__1: {
        enterOuterAlt(_localctx, 2);
        setState(189);
        stepChain();
        break;
      }

      case PredaScriptParser::T__2: {
        enterOuterAlt(_localctx, 3);
        setState(190);
        runChain();
        break;
      }

      case PredaScriptParser::T__3: {
        enterOuterAlt(_localctx, 4);
        setState(191);
        stopChain();
        break;
      }

      case PredaScriptParser::T__4: {
        enterOuterAlt(_localctx, 5);
        setState(192);
        getChainInfo();
        break;
      }

      case PredaScriptParser::T__5: {
        enterOuterAlt(_localctx, 6);
        setState(193);
        deployContractOnChain();
        break;
      }

      case PredaScriptParser::T__10: {
        enterOuterAlt(_localctx, 7);
        setState(194);
        batchInsertTxnOnChain();
        break;
      }

      case PredaScriptParser::T__11: {
        enterOuterAlt(_localctx, 8);
        setState(195);
        setGasLimit();
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

//----------------- AwaitChainContext ------------------------------------------------------------------

PredaScriptParser::AwaitChainContext::AwaitChainContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t PredaScriptParser::AwaitChainContext::getRuleIndex() const {
  return PredaScriptParser::RuleAwaitChain;
}

void PredaScriptParser::AwaitChainContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAwaitChain(this);
}

void PredaScriptParser::AwaitChainContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAwaitChain(this);
}

PredaScriptParser::AwaitChainContext* PredaScriptParser::awaitChain() {
  AwaitChainContext *_localctx = _tracker.createInstance<AwaitChainContext>(_ctx, getState());
  enterRule(_localctx, 6, PredaScriptParser::RuleAwaitChain);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(198);
    match(PredaScriptParser::T__0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StepChainContext ------------------------------------------------------------------

PredaScriptParser::StepChainContext::StepChainContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t PredaScriptParser::StepChainContext::getRuleIndex() const {
  return PredaScriptParser::RuleStepChain;
}

void PredaScriptParser::StepChainContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStepChain(this);
}

void PredaScriptParser::StepChainContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStepChain(this);
}

PredaScriptParser::StepChainContext* PredaScriptParser::stepChain() {
  StepChainContext *_localctx = _tracker.createInstance<StepChainContext>(_ctx, getState());
  enterRule(_localctx, 8, PredaScriptParser::RuleStepChain);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(200);
    match(PredaScriptParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RunChainContext ------------------------------------------------------------------

PredaScriptParser::RunChainContext::RunChainContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t PredaScriptParser::RunChainContext::getRuleIndex() const {
  return PredaScriptParser::RuleRunChain;
}

void PredaScriptParser::RunChainContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRunChain(this);
}

void PredaScriptParser::RunChainContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRunChain(this);
}

PredaScriptParser::RunChainContext* PredaScriptParser::runChain() {
  RunChainContext *_localctx = _tracker.createInstance<RunChainContext>(_ctx, getState());
  enterRule(_localctx, 10, PredaScriptParser::RuleRunChain);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(202);
    match(PredaScriptParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StopChainContext ------------------------------------------------------------------

PredaScriptParser::StopChainContext::StopChainContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t PredaScriptParser::StopChainContext::getRuleIndex() const {
  return PredaScriptParser::RuleStopChain;
}

void PredaScriptParser::StopChainContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStopChain(this);
}

void PredaScriptParser::StopChainContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStopChain(this);
}

PredaScriptParser::StopChainContext* PredaScriptParser::stopChain() {
  StopChainContext *_localctx = _tracker.createInstance<StopChainContext>(_ctx, getState());
  enterRule(_localctx, 12, PredaScriptParser::RuleStopChain);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(204);
    match(PredaScriptParser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GetChainInfoContext ------------------------------------------------------------------

PredaScriptParser::GetChainInfoContext::GetChainInfoContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t PredaScriptParser::GetChainInfoContext::getRuleIndex() const {
  return PredaScriptParser::RuleGetChainInfo;
}

void PredaScriptParser::GetChainInfoContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGetChainInfo(this);
}

void PredaScriptParser::GetChainInfoContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGetChainInfo(this);
}

PredaScriptParser::GetChainInfoContext* PredaScriptParser::getChainInfo() {
  GetChainInfoContext *_localctx = _tracker.createInstance<GetChainInfoContext>(_ctx, getState());
  enterRule(_localctx, 14, PredaScriptParser::RuleGetChainInfo);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(206);
    match(PredaScriptParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeployContractOnChainContext ------------------------------------------------------------------

PredaScriptParser::DeployContractOnChainContext::DeployContractOnChainContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::ContractPropertiesContext* PredaScriptParser::DeployContractOnChainContext::contractProperties() {
  return getRuleContext<PredaScriptParser::ContractPropertiesContext>(0);
}

PredaScriptParser::AddressScopeContext* PredaScriptParser::DeployContractOnChainContext::addressScope() {
  return getRuleContext<PredaScriptParser::AddressScopeContext>(0);
}

PredaScriptParser::ShardScopeContext* PredaScriptParser::DeployContractOnChainContext::shardScope() {
  return getRuleContext<PredaScriptParser::ShardScopeContext>(0);
}


size_t PredaScriptParser::DeployContractOnChainContext::getRuleIndex() const {
  return PredaScriptParser::RuleDeployContractOnChain;
}

void PredaScriptParser::DeployContractOnChainContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeployContractOnChain(this);
}

void PredaScriptParser::DeployContractOnChainContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeployContractOnChain(this);
}

PredaScriptParser::DeployContractOnChainContext* PredaScriptParser::deployContractOnChain() {
  DeployContractOnChainContext *_localctx = _tracker.createInstance<DeployContractOnChainContext>(_ctx, getState());
  enterRule(_localctx, 16, PredaScriptParser::RuleDeployContractOnChain);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(208);
    match(PredaScriptParser::T__5);
    setState(211);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaScriptParser::T__36: {
        setState(209);
        addressScope();
        break;
      }

      case PredaScriptParser::T__34:
      case PredaScriptParser::T__35: {
        setState(210);
        shardScope();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(213);
    contractProperties();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ContractPropertiesContext ------------------------------------------------------------------

PredaScriptParser::ContractPropertiesContext::ContractPropertiesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PredaScriptParser::ContractPropertyContext *> PredaScriptParser::ContractPropertiesContext::contractProperty() {
  return getRuleContexts<PredaScriptParser::ContractPropertyContext>();
}

PredaScriptParser::ContractPropertyContext* PredaScriptParser::ContractPropertiesContext::contractProperty(size_t i) {
  return getRuleContext<PredaScriptParser::ContractPropertyContext>(i);
}


size_t PredaScriptParser::ContractPropertiesContext::getRuleIndex() const {
  return PredaScriptParser::RuleContractProperties;
}

void PredaScriptParser::ContractPropertiesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContractProperties(this);
}

void PredaScriptParser::ContractPropertiesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContractProperties(this);
}

PredaScriptParser::ContractPropertiesContext* PredaScriptParser::contractProperties() {
  ContractPropertiesContext *_localctx = _tracker.createInstance<ContractPropertiesContext>(_ctx, getState());
  enterRule(_localctx, 18, PredaScriptParser::RuleContractProperties);

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
    setState(218);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(215);
        contractProperty(); 
      }
      setState(220);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ContractPropertyContext ------------------------------------------------------------------

PredaScriptParser::ContractPropertyContext::ContractPropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::PredaFileContext* PredaScriptParser::ContractPropertyContext::predaFile() {
  return getRuleContext<PredaScriptParser::PredaFileContext>(0);
}

PredaScriptParser::XtlFileContext* PredaScriptParser::ContractPropertyContext::xtlFile() {
  return getRuleContext<PredaScriptParser::XtlFileContext>(0);
}

PredaScriptParser::JsonParametersContext* PredaScriptParser::ContractPropertyContext::jsonParameters() {
  return getRuleContext<PredaScriptParser::JsonParametersContext>(0);
}


size_t PredaScriptParser::ContractPropertyContext::getRuleIndex() const {
  return PredaScriptParser::RuleContractProperty;
}

void PredaScriptParser::ContractPropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContractProperty(this);
}

void PredaScriptParser::ContractPropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContractProperty(this);
}

PredaScriptParser::ContractPropertyContext* PredaScriptParser::contractProperty() {
  ContractPropertyContext *_localctx = _tracker.createInstance<ContractPropertyContext>(_ctx, getState());
  enterRule(_localctx, 20, PredaScriptParser::RuleContractProperty);
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
    setState(223);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      setState(221);
      predaFile();
      break;
    }

    case 2: {
      setState(222);
      xtlFile();
      break;
    }

    default:
      break;
    }
    setState(227);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaScriptParser::T__6) {
      setState(225);
      match(PredaScriptParser::T__6);
      setState(226);
      jsonParameters();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PredaFileContext ------------------------------------------------------------------

PredaScriptParser::PredaFileContext::PredaFileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::IdentifierContext* PredaScriptParser::PredaFileContext::identifier() {
  return getRuleContext<PredaScriptParser::IdentifierContext>(0);
}

PredaScriptParser::DirectivePathContext* PredaScriptParser::PredaFileContext::directivePath() {
  return getRuleContext<PredaScriptParser::DirectivePathContext>(0);
}

tree::TerminalNode* PredaScriptParser::PredaFileContext::NATIVE() {
  return getToken(PredaScriptParser::NATIVE, 0);
}

tree::TerminalNode* PredaScriptParser::PredaFileContext::WASM() {
  return getToken(PredaScriptParser::WASM, 0);
}


size_t PredaScriptParser::PredaFileContext::getRuleIndex() const {
  return PredaScriptParser::RulePredaFile;
}

void PredaScriptParser::PredaFileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPredaFile(this);
}

void PredaScriptParser::PredaFileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPredaFile(this);
}

PredaScriptParser::PredaFileContext* PredaScriptParser::predaFile() {
  PredaFileContext *_localctx = _tracker.createInstance<PredaFileContext>(_ctx, getState());
  enterRule(_localctx, 22, PredaScriptParser::RulePredaFile);
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
    setState(230);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaScriptParser::WINPATH

    || _la == PredaScriptParser::UNIXPATH) {
      setState(229);
      directivePath();
    }
    setState(232);
    identifier();
    setState(233);
    match(PredaScriptParser::T__7);
    setState(236);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaScriptParser::T__8) {
      setState(234);
      match(PredaScriptParser::T__8);
      setState(235);
      _la = _input->LA(1);
      if (!(_la == PredaScriptParser::WASM

      || _la == PredaScriptParser::NATIVE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
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

//----------------- XtlFileContext ------------------------------------------------------------------

PredaScriptParser::XtlFileContext::XtlFileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::IdentifierContext* PredaScriptParser::XtlFileContext::identifier() {
  return getRuleContext<PredaScriptParser::IdentifierContext>(0);
}

PredaScriptParser::DirectivePathContext* PredaScriptParser::XtlFileContext::directivePath() {
  return getRuleContext<PredaScriptParser::DirectivePathContext>(0);
}


size_t PredaScriptParser::XtlFileContext::getRuleIndex() const {
  return PredaScriptParser::RuleXtlFile;
}

void PredaScriptParser::XtlFileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterXtlFile(this);
}

void PredaScriptParser::XtlFileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitXtlFile(this);
}

PredaScriptParser::XtlFileContext* PredaScriptParser::xtlFile() {
  XtlFileContext *_localctx = _tracker.createInstance<XtlFileContext>(_ctx, getState());
  enterRule(_localctx, 24, PredaScriptParser::RuleXtlFile);
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
    setState(239);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaScriptParser::WINPATH

    || _la == PredaScriptParser::UNIXPATH) {
      setState(238);
      directivePath();
    }
    setState(241);
    identifier();
    setState(242);
    match(PredaScriptParser::T__9);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BatchInsertTxnOnChainContext ------------------------------------------------------------------

PredaScriptParser::BatchInsertTxnOnChainContext::BatchInsertTxnOnChainContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::VarNameContext* PredaScriptParser::BatchInsertTxnOnChainContext::varName() {
  return getRuleContext<PredaScriptParser::VarNameContext>(0);
}


size_t PredaScriptParser::BatchInsertTxnOnChainContext::getRuleIndex() const {
  return PredaScriptParser::RuleBatchInsertTxnOnChain;
}

void PredaScriptParser::BatchInsertTxnOnChainContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBatchInsertTxnOnChain(this);
}

void PredaScriptParser::BatchInsertTxnOnChainContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBatchInsertTxnOnChain(this);
}

PredaScriptParser::BatchInsertTxnOnChainContext* PredaScriptParser::batchInsertTxnOnChain() {
  BatchInsertTxnOnChainContext *_localctx = _tracker.createInstance<BatchInsertTxnOnChainContext>(_ctx, getState());
  enterRule(_localctx, 26, PredaScriptParser::RuleBatchInsertTxnOnChain);

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
    match(PredaScriptParser::T__10);
    setState(245);
    varName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SetGasLimitContext ------------------------------------------------------------------

PredaScriptParser::SetGasLimitContext::SetGasLimitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::NumberLiteralContext* PredaScriptParser::SetGasLimitContext::numberLiteral() {
  return getRuleContext<PredaScriptParser::NumberLiteralContext>(0);
}

tree::TerminalNode* PredaScriptParser::SetGasLimitContext::GLOBAL() {
  return getToken(PredaScriptParser::GLOBAL, 0);
}


size_t PredaScriptParser::SetGasLimitContext::getRuleIndex() const {
  return PredaScriptParser::RuleSetGasLimit;
}

void PredaScriptParser::SetGasLimitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSetGasLimit(this);
}

void PredaScriptParser::SetGasLimitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSetGasLimit(this);
}

PredaScriptParser::SetGasLimitContext* PredaScriptParser::setGasLimit() {
  SetGasLimitContext *_localctx = _tracker.createInstance<SetGasLimitContext>(_ctx, getState());
  enterRule(_localctx, 28, PredaScriptParser::RuleSetGasLimit);
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
    setState(247);
    match(PredaScriptParser::T__11);
    setState(250);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaScriptParser::T__12) {
      setState(248);
      match(PredaScriptParser::T__12);
      setState(249);
      match(PredaScriptParser::GLOBAL);
    }
    setState(252);
    numberLiteral();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationContext ------------------------------------------------------------------

PredaScriptParser::VariableDeclarationContext::VariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::VariableAssignContext* PredaScriptParser::VariableDeclarationContext::variableAssign() {
  return getRuleContext<PredaScriptParser::VariableAssignContext>(0);
}

PredaScriptParser::DataReadFromFileContext* PredaScriptParser::VariableDeclarationContext::dataReadFromFile() {
  return getRuleContext<PredaScriptParser::DataReadFromFileContext>(0);
}


size_t PredaScriptParser::VariableDeclarationContext::getRuleIndex() const {
  return PredaScriptParser::RuleVariableDeclaration;
}

void PredaScriptParser::VariableDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableDeclaration(this);
}

void PredaScriptParser::VariableDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableDeclaration(this);
}

PredaScriptParser::VariableDeclarationContext* PredaScriptParser::variableDeclaration() {
  VariableDeclarationContext *_localctx = _tracker.createInstance<VariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 30, PredaScriptParser::RuleVariableDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(256);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(254);
      variableAssign();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(255);
      dataReadFromFile();
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

//----------------- VariableAssignContext ------------------------------------------------------------------

PredaScriptParser::VariableAssignContext::VariableAssignContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::VarNameContext* PredaScriptParser::VariableAssignContext::varName() {
  return getRuleContext<PredaScriptParser::VarNameContext>(0);
}

PredaScriptParser::VarValueContext* PredaScriptParser::VariableAssignContext::varValue() {
  return getRuleContext<PredaScriptParser::VarValueContext>(0);
}


size_t PredaScriptParser::VariableAssignContext::getRuleIndex() const {
  return PredaScriptParser::RuleVariableAssign;
}

void PredaScriptParser::VariableAssignContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableAssign(this);
}

void PredaScriptParser::VariableAssignContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableAssign(this);
}

PredaScriptParser::VariableAssignContext* PredaScriptParser::variableAssign() {
  VariableAssignContext *_localctx = _tracker.createInstance<VariableAssignContext>(_ctx, getState());
  enterRule(_localctx, 32, PredaScriptParser::RuleVariableAssign);

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
    varName();
    setState(259);
    match(PredaScriptParser::T__6);
    setState(260);
    varValue();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarNameContext ------------------------------------------------------------------

PredaScriptParser::VarNameContext::VarNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::IdentifierContext* PredaScriptParser::VarNameContext::identifier() {
  return getRuleContext<PredaScriptParser::IdentifierContext>(0);
}


size_t PredaScriptParser::VarNameContext::getRuleIndex() const {
  return PredaScriptParser::RuleVarName;
}

void PredaScriptParser::VarNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarName(this);
}

void PredaScriptParser::VarNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarName(this);
}

PredaScriptParser::VarNameContext* PredaScriptParser::varName() {
  VarNameContext *_localctx = _tracker.createInstance<VarNameContext>(_ctx, getState());
  enterRule(_localctx, 34, PredaScriptParser::RuleVarName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(262);
    identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarValueContext ------------------------------------------------------------------

PredaScriptParser::VarValueContext::VarValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::IdentifierContext* PredaScriptParser::VarValueContext::identifier() {
  return getRuleContext<PredaScriptParser::IdentifierContext>(0);
}

PredaScriptParser::StringLiteralContext* PredaScriptParser::VarValueContext::stringLiteral() {
  return getRuleContext<PredaScriptParser::StringLiteralContext>(0);
}

PredaScriptParser::NumberLiteralContext* PredaScriptParser::VarValueContext::numberLiteral() {
  return getRuleContext<PredaScriptParser::NumberLiteralContext>(0);
}


size_t PredaScriptParser::VarValueContext::getRuleIndex() const {
  return PredaScriptParser::RuleVarValue;
}

void PredaScriptParser::VarValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarValue(this);
}

void PredaScriptParser::VarValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarValue(this);
}

PredaScriptParser::VarValueContext* PredaScriptParser::varValue() {
  VarValueContext *_localctx = _tracker.createInstance<VarValueContext>(_ctx, getState());
  enterRule(_localctx, 36, PredaScriptParser::RuleVarValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(267);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaScriptParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(264);
        identifier();
        break;
      }

      case PredaScriptParser::StringLiteral: {
        enterOuterAlt(_localctx, 2);
        setState(265);
        stringLiteral();
        break;
      }

      case PredaScriptParser::T__22:
      case PredaScriptParser::DecimalNumber: {
        enterOuterAlt(_localctx, 3);
        setState(266);
        numberLiteral();
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

//----------------- DataReadFromFileContext ------------------------------------------------------------------

PredaScriptParser::DataReadFromFileContext::DataReadFromFileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::VarNameContext* PredaScriptParser::DataReadFromFileContext::varName() {
  return getRuleContext<PredaScriptParser::VarNameContext>(0);
}

PredaScriptParser::CsvfilePathContext* PredaScriptParser::DataReadFromFileContext::csvfilePath() {
  return getRuleContext<PredaScriptParser::CsvfilePathContext>(0);
}


size_t PredaScriptParser::DataReadFromFileContext::getRuleIndex() const {
  return PredaScriptParser::RuleDataReadFromFile;
}

void PredaScriptParser::DataReadFromFileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDataReadFromFile(this);
}

void PredaScriptParser::DataReadFromFileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDataReadFromFile(this);
}

PredaScriptParser::DataReadFromFileContext* PredaScriptParser::dataReadFromFile() {
  DataReadFromFileContext *_localctx = _tracker.createInstance<DataReadFromFileContext>(_ctx, getState());
  enterRule(_localctx, 38, PredaScriptParser::RuleDataReadFromFile);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(269);
    varName();
    setState(270);
    match(PredaScriptParser::T__6);
    setState(271);
    match(PredaScriptParser::T__13);
    setState(272);
    match(PredaScriptParser::T__14);
    setState(273);
    csvfilePath();
    setState(274);
    match(PredaScriptParser::T__15);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CsvfilePathContext ------------------------------------------------------------------

PredaScriptParser::CsvfilePathContext::CsvfilePathContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::FileNameContext* PredaScriptParser::CsvfilePathContext::fileName() {
  return getRuleContext<PredaScriptParser::FileNameContext>(0);
}

PredaScriptParser::DirectivePathContext* PredaScriptParser::CsvfilePathContext::directivePath() {
  return getRuleContext<PredaScriptParser::DirectivePathContext>(0);
}


size_t PredaScriptParser::CsvfilePathContext::getRuleIndex() const {
  return PredaScriptParser::RuleCsvfilePath;
}

void PredaScriptParser::CsvfilePathContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCsvfilePath(this);
}

void PredaScriptParser::CsvfilePathContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCsvfilePath(this);
}

PredaScriptParser::CsvfilePathContext* PredaScriptParser::csvfilePath() {
  CsvfilePathContext *_localctx = _tracker.createInstance<CsvfilePathContext>(_ctx, getState());
  enterRule(_localctx, 40, PredaScriptParser::RuleCsvfilePath);
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
    setState(277);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaScriptParser::WINPATH

    || _la == PredaScriptParser::UNIXPATH) {
      setState(276);
      directivePath();
    }
    setState(279);
    fileName();
    setState(280);
    match(PredaScriptParser::T__16);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConfigContext ------------------------------------------------------------------

PredaScriptParser::ConfigContext::ConfigContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::ConfigStateContext* PredaScriptParser::ConfigContext::configState() {
  return getRuleContext<PredaScriptParser::ConfigStateContext>(0);
}

PredaScriptParser::ConfigAddressContext* PredaScriptParser::ConfigContext::configAddress() {
  return getRuleContext<PredaScriptParser::ConfigAddressContext>(0);
}

PredaScriptParser::ConfigRandomizerContext* PredaScriptParser::ConfigContext::configRandomizer() {
  return getRuleContext<PredaScriptParser::ConfigRandomizerContext>(0);
}


size_t PredaScriptParser::ConfigContext::getRuleIndex() const {
  return PredaScriptParser::RuleConfig;
}

void PredaScriptParser::ConfigContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConfig(this);
}

void PredaScriptParser::ConfigContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConfig(this);
}

PredaScriptParser::ConfigContext* PredaScriptParser::config() {
  ConfigContext *_localctx = _tracker.createInstance<ConfigContext>(_ctx, getState());
  enterRule(_localctx, 42, PredaScriptParser::RuleConfig);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(285);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaScriptParser::T__17:
      case PredaScriptParser::T__18:
      case PredaScriptParser::T__19:
      case PredaScriptParser::T__23:
      case PredaScriptParser::T__27: {
        enterOuterAlt(_localctx, 1);
        setState(282);
        configState();
        break;
      }

      case PredaScriptParser::T__28: {
        enterOuterAlt(_localctx, 2);
        setState(283);
        configAddress();
        break;
      }

      case PredaScriptParser::RANDOM: {
        enterOuterAlt(_localctx, 3);
        setState(284);
        configRandomizer();
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

//----------------- ConfigStateContext ------------------------------------------------------------------

PredaScriptParser::ConfigStateContext::ConfigStateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::SetContractStateContext* PredaScriptParser::ConfigStateContext::setContractState() {
  return getRuleContext<PredaScriptParser::SetContractStateContext>(0);
}

PredaScriptParser::UpdateStateContext* PredaScriptParser::ConfigStateContext::updateState() {
  return getRuleContext<PredaScriptParser::UpdateStateContext>(0);
}

PredaScriptParser::TokenStateContext* PredaScriptParser::ConfigStateContext::tokenState() {
  return getRuleContext<PredaScriptParser::TokenStateContext>(0);
}

PredaScriptParser::LoadStateContext* PredaScriptParser::ConfigStateContext::loadState() {
  return getRuleContext<PredaScriptParser::LoadStateContext>(0);
}

PredaScriptParser::SaveStateContext* PredaScriptParser::ConfigStateContext::saveState() {
  return getRuleContext<PredaScriptParser::SaveStateContext>(0);
}


size_t PredaScriptParser::ConfigStateContext::getRuleIndex() const {
  return PredaScriptParser::RuleConfigState;
}

void PredaScriptParser::ConfigStateContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConfigState(this);
}

void PredaScriptParser::ConfigStateContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConfigState(this);
}

PredaScriptParser::ConfigStateContext* PredaScriptParser::configState() {
  ConfigStateContext *_localctx = _tracker.createInstance<ConfigStateContext>(_ctx, getState());
  enterRule(_localctx, 44, PredaScriptParser::RuleConfigState);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(292);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaScriptParser::T__17: {
        enterOuterAlt(_localctx, 1);
        setState(287);
        setContractState();
        break;
      }

      case PredaScriptParser::T__18: {
        enterOuterAlt(_localctx, 2);
        setState(288);
        updateState();
        break;
      }

      case PredaScriptParser::T__19: {
        enterOuterAlt(_localctx, 3);
        setState(289);
        tokenState();
        break;
      }

      case PredaScriptParser::T__23: {
        enterOuterAlt(_localctx, 4);
        setState(290);
        loadState();
        break;
      }

      case PredaScriptParser::T__27: {
        enterOuterAlt(_localctx, 5);
        setState(291);
        saveState();
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

//----------------- SetContractStateContext ------------------------------------------------------------------

PredaScriptParser::SetContractStateContext::SetContractStateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::ContractIdContext* PredaScriptParser::SetContractStateContext::contractId() {
  return getRuleContext<PredaScriptParser::ContractIdContext>(0);
}

PredaScriptParser::StateScopeContext* PredaScriptParser::SetContractStateContext::stateScope() {
  return getRuleContext<PredaScriptParser::StateScopeContext>(0);
}

PredaScriptParser::JsonParametersContext* PredaScriptParser::SetContractStateContext::jsonParameters() {
  return getRuleContext<PredaScriptParser::JsonParametersContext>(0);
}

PredaScriptParser::ScopeContext* PredaScriptParser::SetContractStateContext::scope() {
  return getRuleContext<PredaScriptParser::ScopeContext>(0);
}


size_t PredaScriptParser::SetContractStateContext::getRuleIndex() const {
  return PredaScriptParser::RuleSetContractState;
}

void PredaScriptParser::SetContractStateContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSetContractState(this);
}

void PredaScriptParser::SetContractStateContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSetContractState(this);
}

PredaScriptParser::SetContractStateContext* PredaScriptParser::setContractState() {
  SetContractStateContext *_localctx = _tracker.createInstance<SetContractStateContext>(_ctx, getState());
  enterRule(_localctx, 46, PredaScriptParser::RuleSetContractState);
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
    setState(294);
    match(PredaScriptParser::T__17);
    setState(295);
    contractId();
    setState(296);
    match(PredaScriptParser::T__12);
    setState(297);
    stateScope();
    setState(299);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 240518168576) != 0)) {
      setState(298);
      scope();
    }
    setState(301);
    jsonParameters();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StateScopeContext ------------------------------------------------------------------

PredaScriptParser::StateScopeContext::StateScopeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaScriptParser::StateScopeContext::GLOBAL() {
  return getToken(PredaScriptParser::GLOBAL, 0);
}

tree::TerminalNode* PredaScriptParser::StateScopeContext::SHARD() {
  return getToken(PredaScriptParser::SHARD, 0);
}

tree::TerminalNode* PredaScriptParser::StateScopeContext::ADDRESS() {
  return getToken(PredaScriptParser::ADDRESS, 0);
}


size_t PredaScriptParser::StateScopeContext::getRuleIndex() const {
  return PredaScriptParser::RuleStateScope;
}

void PredaScriptParser::StateScopeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStateScope(this);
}

void PredaScriptParser::StateScopeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStateScope(this);
}

PredaScriptParser::StateScopeContext* PredaScriptParser::stateScope() {
  StateScopeContext *_localctx = _tracker.createInstance<StateScopeContext>(_ctx, getState());
  enterRule(_localctx, 48, PredaScriptParser::RuleStateScope);
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
    setState(303);
    _la = _input->LA(1);
    if (!(((((_la - 63) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 63)) & 7) != 0))) {
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

//----------------- UpdateStateContext ------------------------------------------------------------------

PredaScriptParser::UpdateStateContext::UpdateStateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::ContractIdContext* PredaScriptParser::UpdateStateContext::contractId() {
  return getRuleContext<PredaScriptParser::ContractIdContext>(0);
}

PredaScriptParser::StateScopeContext* PredaScriptParser::UpdateStateContext::stateScope() {
  return getRuleContext<PredaScriptParser::StateScopeContext>(0);
}

PredaScriptParser::JsonParametersContext* PredaScriptParser::UpdateStateContext::jsonParameters() {
  return getRuleContext<PredaScriptParser::JsonParametersContext>(0);
}

PredaScriptParser::ScopeContext* PredaScriptParser::UpdateStateContext::scope() {
  return getRuleContext<PredaScriptParser::ScopeContext>(0);
}


size_t PredaScriptParser::UpdateStateContext::getRuleIndex() const {
  return PredaScriptParser::RuleUpdateState;
}

void PredaScriptParser::UpdateStateContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUpdateState(this);
}

void PredaScriptParser::UpdateStateContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUpdateState(this);
}

PredaScriptParser::UpdateStateContext* PredaScriptParser::updateState() {
  UpdateStateContext *_localctx = _tracker.createInstance<UpdateStateContext>(_ctx, getState());
  enterRule(_localctx, 50, PredaScriptParser::RuleUpdateState);
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
    setState(305);
    match(PredaScriptParser::T__18);
    setState(306);
    contractId();
    setState(307);
    match(PredaScriptParser::T__12);
    setState(308);
    stateScope();
    setState(310);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 240518168576) != 0)) {
      setState(309);
      scope();
    }
    setState(312);
    jsonParameters();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TokenStateContext ------------------------------------------------------------------

PredaScriptParser::TokenStateContext::TokenStateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::MintTokenContext* PredaScriptParser::TokenStateContext::mintToken() {
  return getRuleContext<PredaScriptParser::MintTokenContext>(0);
}


size_t PredaScriptParser::TokenStateContext::getRuleIndex() const {
  return PredaScriptParser::RuleTokenState;
}

void PredaScriptParser::TokenStateContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTokenState(this);
}

void PredaScriptParser::TokenStateContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTokenState(this);
}

PredaScriptParser::TokenStateContext* PredaScriptParser::tokenState() {
  TokenStateContext *_localctx = _tracker.createInstance<TokenStateContext>(_ctx, getState());
  enterRule(_localctx, 52, PredaScriptParser::RuleTokenState);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(314);
    mintToken();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MintTokenContext ------------------------------------------------------------------

PredaScriptParser::MintTokenContext::MintTokenContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::IdentifierContext* PredaScriptParser::MintTokenContext::identifier() {
  return getRuleContext<PredaScriptParser::IdentifierContext>(0);
}

PredaScriptParser::TokenSymbolContext* PredaScriptParser::MintTokenContext::tokenSymbol() {
  return getRuleContext<PredaScriptParser::TokenSymbolContext>(0);
}

PredaScriptParser::ContractIdContext* PredaScriptParser::MintTokenContext::contractId() {
  return getRuleContext<PredaScriptParser::ContractIdContext>(0);
}


size_t PredaScriptParser::MintTokenContext::getRuleIndex() const {
  return PredaScriptParser::RuleMintToken;
}

void PredaScriptParser::MintTokenContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMintToken(this);
}

void PredaScriptParser::MintTokenContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMintToken(this);
}

PredaScriptParser::MintTokenContext* PredaScriptParser::mintToken() {
  MintTokenContext *_localctx = _tracker.createInstance<MintTokenContext>(_ctx, getState());
  enterRule(_localctx, 54, PredaScriptParser::RuleMintToken);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(316);
    match(PredaScriptParser::T__19);
    setState(317);
    match(PredaScriptParser::T__12);
    setState(318);
    match(PredaScriptParser::T__20);
    setState(319);
    identifier();
    setState(320);
    tokenSymbol();
    setState(321);
    match(PredaScriptParser::T__21);
    setState(322);
    contractId();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TokenSymbolContext ------------------------------------------------------------------

PredaScriptParser::TokenSymbolContext::TokenSymbolContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PredaScriptParser::IdentifierContext *> PredaScriptParser::TokenSymbolContext::identifier() {
  return getRuleContexts<PredaScriptParser::IdentifierContext>();
}

PredaScriptParser::IdentifierContext* PredaScriptParser::TokenSymbolContext::identifier(size_t i) {
  return getRuleContext<PredaScriptParser::IdentifierContext>(i);
}


size_t PredaScriptParser::TokenSymbolContext::getRuleIndex() const {
  return PredaScriptParser::RuleTokenSymbol;
}

void PredaScriptParser::TokenSymbolContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTokenSymbol(this);
}

void PredaScriptParser::TokenSymbolContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTokenSymbol(this);
}

PredaScriptParser::TokenSymbolContext* PredaScriptParser::tokenSymbol() {
  TokenSymbolContext *_localctx = _tracker.createInstance<TokenSymbolContext>(_ctx, getState());
  enterRule(_localctx, 56, PredaScriptParser::RuleTokenSymbol);
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
    setState(328);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PredaScriptParser::T__22

    || _la == PredaScriptParser::Identifier) {
      setState(326);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case PredaScriptParser::Identifier: {
          setState(324);
          identifier();
          break;
        }

        case PredaScriptParser::T__22: {
          setState(325);
          match(PredaScriptParser::T__22);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(330);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LoadStateContext ------------------------------------------------------------------

PredaScriptParser::LoadStateContext::LoadStateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::StateScopeContext* PredaScriptParser::LoadStateContext::stateScope() {
  return getRuleContext<PredaScriptParser::StateScopeContext>(0);
}

PredaScriptParser::JsonFilePathContext* PredaScriptParser::LoadStateContext::jsonFilePath() {
  return getRuleContext<PredaScriptParser::JsonFilePathContext>(0);
}


size_t PredaScriptParser::LoadStateContext::getRuleIndex() const {
  return PredaScriptParser::RuleLoadState;
}

void PredaScriptParser::LoadStateContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLoadState(this);
}

void PredaScriptParser::LoadStateContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLoadState(this);
}

PredaScriptParser::LoadStateContext* PredaScriptParser::loadState() {
  LoadStateContext *_localctx = _tracker.createInstance<LoadStateContext>(_ctx, getState());
  enterRule(_localctx, 58, PredaScriptParser::RuleLoadState);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(331);
    match(PredaScriptParser::T__23);
    setState(332);
    match(PredaScriptParser::T__24);
    setState(333);
    stateScope();
    setState(334);
    match(PredaScriptParser::T__25);
    setState(335);
    jsonFilePath();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- JsonFilePathContext ------------------------------------------------------------------

PredaScriptParser::JsonFilePathContext::JsonFilePathContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::FileNameContext* PredaScriptParser::JsonFilePathContext::fileName() {
  return getRuleContext<PredaScriptParser::FileNameContext>(0);
}

PredaScriptParser::DirectivePathContext* PredaScriptParser::JsonFilePathContext::directivePath() {
  return getRuleContext<PredaScriptParser::DirectivePathContext>(0);
}


size_t PredaScriptParser::JsonFilePathContext::getRuleIndex() const {
  return PredaScriptParser::RuleJsonFilePath;
}

void PredaScriptParser::JsonFilePathContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterJsonFilePath(this);
}

void PredaScriptParser::JsonFilePathContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitJsonFilePath(this);
}

PredaScriptParser::JsonFilePathContext* PredaScriptParser::jsonFilePath() {
  JsonFilePathContext *_localctx = _tracker.createInstance<JsonFilePathContext>(_ctx, getState());
  enterRule(_localctx, 60, PredaScriptParser::RuleJsonFilePath);
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
    setState(338);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaScriptParser::WINPATH

    || _la == PredaScriptParser::UNIXPATH) {
      setState(337);
      directivePath();
    }
    setState(340);
    fileName();
    setState(342);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaScriptParser::T__26) {
      setState(341);
      match(PredaScriptParser::T__26);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SaveStateContext ------------------------------------------------------------------

PredaScriptParser::SaveStateContext::SaveStateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::StateScopeContext* PredaScriptParser::SaveStateContext::stateScope() {
  return getRuleContext<PredaScriptParser::StateScopeContext>(0);
}

PredaScriptParser::FileNameContext* PredaScriptParser::SaveStateContext::fileName() {
  return getRuleContext<PredaScriptParser::FileNameContext>(0);
}

PredaScriptParser::ContractIdContext* PredaScriptParser::SaveStateContext::contractId() {
  return getRuleContext<PredaScriptParser::ContractIdContext>(0);
}

tree::TerminalNode* PredaScriptParser::SaveStateContext::ALL() {
  return getToken(PredaScriptParser::ALL, 0);
}


size_t PredaScriptParser::SaveStateContext::getRuleIndex() const {
  return PredaScriptParser::RuleSaveState;
}

void PredaScriptParser::SaveStateContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSaveState(this);
}

void PredaScriptParser::SaveStateContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSaveState(this);
}

PredaScriptParser::SaveStateContext* PredaScriptParser::saveState() {
  SaveStateContext *_localctx = _tracker.createInstance<SaveStateContext>(_ctx, getState());
  enterRule(_localctx, 62, PredaScriptParser::RuleSaveState);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(344);
    match(PredaScriptParser::T__27);
    setState(345);
    stateScope();
    setState(346);
    match(PredaScriptParser::T__12);
    setState(349);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaScriptParser::T__22:
      case PredaScriptParser::DecimalNumber:
      case PredaScriptParser::Identifier: {
        setState(347);
        contractId();
        break;
      }

      case PredaScriptParser::ALL: {
        setState(348);
        match(PredaScriptParser::ALL);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(351);
    fileName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConfigAddressContext ------------------------------------------------------------------

PredaScriptParser::ConfigAddressContext::ConfigAddressContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::NumberLiteralContext* PredaScriptParser::ConfigAddressContext::numberLiteral() {
  return getRuleContext<PredaScriptParser::NumberLiteralContext>(0);
}


size_t PredaScriptParser::ConfigAddressContext::getRuleIndex() const {
  return PredaScriptParser::RuleConfigAddress;
}

void PredaScriptParser::ConfigAddressContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConfigAddress(this);
}

void PredaScriptParser::ConfigAddressContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConfigAddress(this);
}

PredaScriptParser::ConfigAddressContext* PredaScriptParser::configAddress() {
  ConfigAddressContext *_localctx = _tracker.createInstance<ConfigAddressContext>(_ctx, getState());
  enterRule(_localctx, 64, PredaScriptParser::RuleConfigAddress);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(353);
    match(PredaScriptParser::T__28);
    setState(355);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      setState(354);
      numberLiteral();
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

//----------------- ConfigRandomizerContext ------------------------------------------------------------------

PredaScriptParser::ConfigRandomizerContext::ConfigRandomizerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaScriptParser::ConfigRandomizerContext::RANDOM() {
  return getToken(PredaScriptParser::RANDOM, 0);
}

PredaScriptParser::NumberLiteralContext* PredaScriptParser::ConfigRandomizerContext::numberLiteral() {
  return getRuleContext<PredaScriptParser::NumberLiteralContext>(0);
}


size_t PredaScriptParser::ConfigRandomizerContext::getRuleIndex() const {
  return PredaScriptParser::RuleConfigRandomizer;
}

void PredaScriptParser::ConfigRandomizerContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConfigRandomizer(this);
}

void PredaScriptParser::ConfigRandomizerContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConfigRandomizer(this);
}

PredaScriptParser::ConfigRandomizerContext* PredaScriptParser::configRandomizer() {
  ConfigRandomizerContext *_localctx = _tracker.createInstance<ConfigRandomizerContext>(_ctx, getState());
  enterRule(_localctx, 66, PredaScriptParser::RuleConfigRandomizer);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(357);
    match(PredaScriptParser::RANDOM);
    setState(358);
    match(PredaScriptParser::T__12);
    setState(359);
    match(PredaScriptParser::T__29);
    setState(361);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      setState(360);
      numberLiteral();
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

//----------------- IssueTxnContext ------------------------------------------------------------------

PredaScriptParser::IssueTxnContext::IssueTxnContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::ContractIdContext* PredaScriptParser::IssueTxnContext::contractId() {
  return getRuleContext<PredaScriptParser::ContractIdContext>(0);
}

PredaScriptParser::FunctionNameContext* PredaScriptParser::IssueTxnContext::functionName() {
  return getRuleContext<PredaScriptParser::FunctionNameContext>(0);
}

PredaScriptParser::TxnReturnInfoContext* PredaScriptParser::IssueTxnContext::txnReturnInfo() {
  return getRuleContext<PredaScriptParser::TxnReturnInfoContext>(0);
}

PredaScriptParser::CountContext* PredaScriptParser::IssueTxnContext::count() {
  return getRuleContext<PredaScriptParser::CountContext>(0);
}

PredaScriptParser::ScopeContext* PredaScriptParser::IssueTxnContext::scope() {
  return getRuleContext<PredaScriptParser::ScopeContext>(0);
}

PredaScriptParser::JsonParametersContext* PredaScriptParser::IssueTxnContext::jsonParameters() {
  return getRuleContext<PredaScriptParser::JsonParametersContext>(0);
}

PredaScriptParser::SuppliedTokensContext* PredaScriptParser::IssueTxnContext::suppliedTokens() {
  return getRuleContext<PredaScriptParser::SuppliedTokensContext>(0);
}


size_t PredaScriptParser::IssueTxnContext::getRuleIndex() const {
  return PredaScriptParser::RuleIssueTxn;
}

void PredaScriptParser::IssueTxnContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIssueTxn(this);
}

void PredaScriptParser::IssueTxnContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIssueTxn(this);
}

PredaScriptParser::IssueTxnContext* PredaScriptParser::issueTxn() {
  IssueTxnContext *_localctx = _tracker.createInstance<IssueTxnContext>(_ctx, getState());
  enterRule(_localctx, 68, PredaScriptParser::RuleIssueTxn);
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
    setState(366);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      setState(363);
      txnReturnInfo();
      setState(364);
      match(PredaScriptParser::T__6);
      break;
    }

    default:
      break;
    }
    setState(368);
    contractId();
    setState(369);
    match(PredaScriptParser::T__12);
    setState(370);
    functionName();
    setState(372);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaScriptParser::T__33) {
      setState(371);
      count();
    }
    setState(375);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 240518168576) != 0)) {
      setState(374);
      scope();
    }
    setState(378);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaScriptParser::T__37) {
      setState(377);
      jsonParameters();
    }
    setState(382);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaScriptParser::T__30) {
      setState(380);
      match(PredaScriptParser::T__30);
      setState(381);
      suppliedTokens();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TxnReturnInfoContext ------------------------------------------------------------------

PredaScriptParser::TxnReturnInfoContext::TxnReturnInfoContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::IdentifierContext* PredaScriptParser::TxnReturnInfoContext::identifier() {
  return getRuleContext<PredaScriptParser::IdentifierContext>(0);
}


size_t PredaScriptParser::TxnReturnInfoContext::getRuleIndex() const {
  return PredaScriptParser::RuleTxnReturnInfo;
}

void PredaScriptParser::TxnReturnInfoContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTxnReturnInfo(this);
}

void PredaScriptParser::TxnReturnInfoContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTxnReturnInfo(this);
}

PredaScriptParser::TxnReturnInfoContext* PredaScriptParser::txnReturnInfo() {
  TxnReturnInfoContext *_localctx = _tracker.createInstance<TxnReturnInfoContext>(_ctx, getState());
  enterRule(_localctx, 70, PredaScriptParser::RuleTxnReturnInfo);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(384);
    identifier();
    setState(387);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
    case 1: {
      setState(385);
      match(PredaScriptParser::T__31);
      setState(386);
      match(PredaScriptParser::T__32);
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

//----------------- ContractIdContext ------------------------------------------------------------------

PredaScriptParser::ContractIdContext::ContractIdContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::ContractNameContext* PredaScriptParser::ContractIdContext::contractName() {
  return getRuleContext<PredaScriptParser::ContractNameContext>(0);
}

PredaScriptParser::CvidContext* PredaScriptParser::ContractIdContext::cvid() {
  return getRuleContext<PredaScriptParser::CvidContext>(0);
}


size_t PredaScriptParser::ContractIdContext::getRuleIndex() const {
  return PredaScriptParser::RuleContractId;
}

void PredaScriptParser::ContractIdContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContractId(this);
}

void PredaScriptParser::ContractIdContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContractId(this);
}

PredaScriptParser::ContractIdContext* PredaScriptParser::contractId() {
  ContractIdContext *_localctx = _tracker.createInstance<ContractIdContext>(_ctx, getState());
  enterRule(_localctx, 72, PredaScriptParser::RuleContractId);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(391);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaScriptParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(389);
        contractName();
        break;
      }

      case PredaScriptParser::T__22:
      case PredaScriptParser::DecimalNumber: {
        enterOuterAlt(_localctx, 2);
        setState(390);
        cvid();
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

//----------------- ContractNameContext ------------------------------------------------------------------

PredaScriptParser::ContractNameContext::ContractNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PredaScriptParser::IdentifierContext *> PredaScriptParser::ContractNameContext::identifier() {
  return getRuleContexts<PredaScriptParser::IdentifierContext>();
}

PredaScriptParser::IdentifierContext* PredaScriptParser::ContractNameContext::identifier(size_t i) {
  return getRuleContext<PredaScriptParser::IdentifierContext>(i);
}


size_t PredaScriptParser::ContractNameContext::getRuleIndex() const {
  return PredaScriptParser::RuleContractName;
}

void PredaScriptParser::ContractNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContractName(this);
}

void PredaScriptParser::ContractNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContractName(this);
}

PredaScriptParser::ContractNameContext* PredaScriptParser::contractName() {
  ContractNameContext *_localctx = _tracker.createInstance<ContractNameContext>(_ctx, getState());
  enterRule(_localctx, 74, PredaScriptParser::RuleContractName);

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
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
    case 1: {
      setState(393);
      antlrcpp::downCast<ContractNameContext *>(_localctx)->dappName = identifier();
      setState(394);
      match(PredaScriptParser::T__12);
      break;
    }

    default:
      break;
    }
    setState(398);
    identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CvidContext ------------------------------------------------------------------

PredaScriptParser::CvidContext::CvidContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::NumberLiteralContext* PredaScriptParser::CvidContext::numberLiteral() {
  return getRuleContext<PredaScriptParser::NumberLiteralContext>(0);
}


size_t PredaScriptParser::CvidContext::getRuleIndex() const {
  return PredaScriptParser::RuleCvid;
}

void PredaScriptParser::CvidContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCvid(this);
}

void PredaScriptParser::CvidContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCvid(this);
}

PredaScriptParser::CvidContext* PredaScriptParser::cvid() {
  CvidContext *_localctx = _tracker.createInstance<CvidContext>(_ctx, getState());
  enterRule(_localctx, 76, PredaScriptParser::RuleCvid);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(400);
    numberLiteral();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionNameContext ------------------------------------------------------------------

PredaScriptParser::FunctionNameContext::FunctionNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::IdentifierContext* PredaScriptParser::FunctionNameContext::identifier() {
  return getRuleContext<PredaScriptParser::IdentifierContext>(0);
}


size_t PredaScriptParser::FunctionNameContext::getRuleIndex() const {
  return PredaScriptParser::RuleFunctionName;
}

void PredaScriptParser::FunctionNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionName(this);
}

void PredaScriptParser::FunctionNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionName(this);
}

PredaScriptParser::FunctionNameContext* PredaScriptParser::functionName() {
  FunctionNameContext *_localctx = _tracker.createInstance<FunctionNameContext>(_ctx, getState());
  enterRule(_localctx, 78, PredaScriptParser::RuleFunctionName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(402);
    identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CountContext ------------------------------------------------------------------

PredaScriptParser::CountContext::CountContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::NumberLiteralContext* PredaScriptParser::CountContext::numberLiteral() {
  return getRuleContext<PredaScriptParser::NumberLiteralContext>(0);
}


size_t PredaScriptParser::CountContext::getRuleIndex() const {
  return PredaScriptParser::RuleCount;
}

void PredaScriptParser::CountContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCount(this);
}

void PredaScriptParser::CountContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCount(this);
}

PredaScriptParser::CountContext* PredaScriptParser::count() {
  CountContext *_localctx = _tracker.createInstance<CountContext>(_ctx, getState());
  enterRule(_localctx, 80, PredaScriptParser::RuleCount);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(404);
    match(PredaScriptParser::T__33);
    setState(405);
    numberLiteral();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ScopeContext ------------------------------------------------------------------

PredaScriptParser::ScopeContext::ScopeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::ShardScopeContext* PredaScriptParser::ScopeContext::shardScope() {
  return getRuleContext<PredaScriptParser::ShardScopeContext>(0);
}

PredaScriptParser::AddressScopeContext* PredaScriptParser::ScopeContext::addressScope() {
  return getRuleContext<PredaScriptParser::AddressScopeContext>(0);
}


size_t PredaScriptParser::ScopeContext::getRuleIndex() const {
  return PredaScriptParser::RuleScope;
}

void PredaScriptParser::ScopeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterScope(this);
}

void PredaScriptParser::ScopeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitScope(this);
}

PredaScriptParser::ScopeContext* PredaScriptParser::scope() {
  ScopeContext *_localctx = _tracker.createInstance<ScopeContext>(_ctx, getState());
  enterRule(_localctx, 82, PredaScriptParser::RuleScope);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(409);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaScriptParser::T__34:
      case PredaScriptParser::T__35: {
        enterOuterAlt(_localctx, 1);
        setState(407);
        shardScope();
        break;
      }

      case PredaScriptParser::T__36: {
        enterOuterAlt(_localctx, 2);
        setState(408);
        addressScope();
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

//----------------- ShardScopeContext ------------------------------------------------------------------

PredaScriptParser::ShardScopeContext::ShardScopeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::NumberLiteralContext* PredaScriptParser::ShardScopeContext::numberLiteral() {
  return getRuleContext<PredaScriptParser::NumberLiteralContext>(0);
}

PredaScriptParser::IdentifierContext* PredaScriptParser::ShardScopeContext::identifier() {
  return getRuleContext<PredaScriptParser::IdentifierContext>(0);
}

tree::TerminalNode* PredaScriptParser::ShardScopeContext::RANDOM() {
  return getToken(PredaScriptParser::RANDOM, 0);
}

tree::TerminalNode* PredaScriptParser::ShardScopeContext::ALL() {
  return getToken(PredaScriptParser::ALL, 0);
}


size_t PredaScriptParser::ShardScopeContext::getRuleIndex() const {
  return PredaScriptParser::RuleShardScope;
}

void PredaScriptParser::ShardScopeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShardScope(this);
}

void PredaScriptParser::ShardScopeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShardScope(this);
}

PredaScriptParser::ShardScopeContext* PredaScriptParser::shardScope() {
  ShardScopeContext *_localctx = _tracker.createInstance<ShardScopeContext>(_ctx, getState());
  enterRule(_localctx, 84, PredaScriptParser::RuleShardScope);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(419);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaScriptParser::T__34: {
        enterOuterAlt(_localctx, 1);
        setState(411);
        match(PredaScriptParser::T__34);
        break;
      }

      case PredaScriptParser::T__35: {
        enterOuterAlt(_localctx, 2);
        setState(412);
        match(PredaScriptParser::T__35);
        setState(417);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case PredaScriptParser::T__22:
          case PredaScriptParser::DecimalNumber: {
            setState(413);
            numberLiteral();
            break;
          }

          case PredaScriptParser::Identifier: {
            setState(414);
            identifier();
            break;
          }

          case PredaScriptParser::RANDOM: {
            setState(415);
            match(PredaScriptParser::RANDOM);
            break;
          }

          case PredaScriptParser::ALL: {
            setState(416);
            match(PredaScriptParser::ALL);
            break;
          }

        default:
          throw NoViableAltException(this);
        }
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

//----------------- AddressScopeContext ------------------------------------------------------------------

PredaScriptParser::AddressScopeContext::AddressScopeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::NumberLiteralContext* PredaScriptParser::AddressScopeContext::numberLiteral() {
  return getRuleContext<PredaScriptParser::NumberLiteralContext>(0);
}

PredaScriptParser::IdentifierContext* PredaScriptParser::AddressScopeContext::identifier() {
  return getRuleContext<PredaScriptParser::IdentifierContext>(0);
}

tree::TerminalNode* PredaScriptParser::AddressScopeContext::RANDOM() {
  return getToken(PredaScriptParser::RANDOM, 0);
}

tree::TerminalNode* PredaScriptParser::AddressScopeContext::ALL() {
  return getToken(PredaScriptParser::ALL, 0);
}

PredaScriptParser::Ed25519AddressContext* PredaScriptParser::AddressScopeContext::ed25519Address() {
  return getRuleContext<PredaScriptParser::Ed25519AddressContext>(0);
}


size_t PredaScriptParser::AddressScopeContext::getRuleIndex() const {
  return PredaScriptParser::RuleAddressScope;
}

void PredaScriptParser::AddressScopeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAddressScope(this);
}

void PredaScriptParser::AddressScopeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAddressScope(this);
}

PredaScriptParser::AddressScopeContext* PredaScriptParser::addressScope() {
  AddressScopeContext *_localctx = _tracker.createInstance<AddressScopeContext>(_ctx, getState());
  enterRule(_localctx, 86, PredaScriptParser::RuleAddressScope);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(421);
    match(PredaScriptParser::T__36);
    setState(427);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaScriptParser::T__22:
      case PredaScriptParser::DecimalNumber: {
        setState(422);
        numberLiteral();
        break;
      }

      case PredaScriptParser::Identifier: {
        setState(423);
        identifier();
        break;
      }

      case PredaScriptParser::RANDOM: {
        setState(424);
        match(PredaScriptParser::RANDOM);
        break;
      }

      case PredaScriptParser::ALL: {
        setState(425);
        match(PredaScriptParser::ALL);
        break;
      }

      case PredaScriptParser::Ed25519Address: {
        setState(426);
        ed25519Address();
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

//----------------- JsonParametersContext ------------------------------------------------------------------

PredaScriptParser::JsonParametersContext::JsonParametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PredaScriptParser::JsonParameterContext *> PredaScriptParser::JsonParametersContext::jsonParameter() {
  return getRuleContexts<PredaScriptParser::JsonParameterContext>();
}

PredaScriptParser::JsonParameterContext* PredaScriptParser::JsonParametersContext::jsonParameter(size_t i) {
  return getRuleContext<PredaScriptParser::JsonParameterContext>(i);
}


size_t PredaScriptParser::JsonParametersContext::getRuleIndex() const {
  return PredaScriptParser::RuleJsonParameters;
}

void PredaScriptParser::JsonParametersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterJsonParameters(this);
}

void PredaScriptParser::JsonParametersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitJsonParameters(this);
}

PredaScriptParser::JsonParametersContext* PredaScriptParser::jsonParameters() {
  JsonParametersContext *_localctx = _tracker.createInstance<JsonParametersContext>(_ctx, getState());
  enterRule(_localctx, 88, PredaScriptParser::RuleJsonParameters);
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
    setState(429);
    match(PredaScriptParser::T__37);
    setState(431);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 23) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 23)) & 835628837109761) != 0)) {
      setState(430);
      jsonParameter();
    }
    setState(437);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PredaScriptParser::T__38) {
      setState(433);
      match(PredaScriptParser::T__38);
      setState(434);
      jsonParameter();
      setState(439);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(440);
    match(PredaScriptParser::T__39);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- JsonParameterContext ------------------------------------------------------------------

PredaScriptParser::JsonParameterContext::JsonParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::JsonKeyContext* PredaScriptParser::JsonParameterContext::jsonKey() {
  return getRuleContext<PredaScriptParser::JsonKeyContext>(0);
}

PredaScriptParser::JsonValueContext* PredaScriptParser::JsonParameterContext::jsonValue() {
  return getRuleContext<PredaScriptParser::JsonValueContext>(0);
}


size_t PredaScriptParser::JsonParameterContext::getRuleIndex() const {
  return PredaScriptParser::RuleJsonParameter;
}

void PredaScriptParser::JsonParameterContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterJsonParameter(this);
}

void PredaScriptParser::JsonParameterContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitJsonParameter(this);
}

PredaScriptParser::JsonParameterContext* PredaScriptParser::jsonParameter() {
  JsonParameterContext *_localctx = _tracker.createInstance<JsonParameterContext>(_ctx, getState());
  enterRule(_localctx, 90, PredaScriptParser::RuleJsonParameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(442);
    jsonKey();
    setState(443);
    match(PredaScriptParser::T__8);
    setState(444);
    jsonValue();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- JsonKeyContext ------------------------------------------------------------------

PredaScriptParser::JsonKeyContext::JsonKeyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::IdentifierContext* PredaScriptParser::JsonKeyContext::identifier() {
  return getRuleContext<PredaScriptParser::IdentifierContext>(0);
}

PredaScriptParser::ConcreteValueContext* PredaScriptParser::JsonKeyContext::concreteValue() {
  return getRuleContext<PredaScriptParser::ConcreteValueContext>(0);
}


size_t PredaScriptParser::JsonKeyContext::getRuleIndex() const {
  return PredaScriptParser::RuleJsonKey;
}

void PredaScriptParser::JsonKeyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterJsonKey(this);
}

void PredaScriptParser::JsonKeyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitJsonKey(this);
}

PredaScriptParser::JsonKeyContext* PredaScriptParser::jsonKey() {
  JsonKeyContext *_localctx = _tracker.createInstance<JsonKeyContext>(_ctx, getState());
  enterRule(_localctx, 92, PredaScriptParser::RuleJsonKey);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(448);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaScriptParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(446);
        identifier();
        break;
      }

      case PredaScriptParser::T__22:
      case PredaScriptParser::TrueKeyword:
      case PredaScriptParser::FalseKeyword:
      case PredaScriptParser::DecimalNumber:
      case PredaScriptParser::HexNumber:
      case PredaScriptParser::StringLiteral: {
        enterOuterAlt(_localctx, 2);
        setState(447);
        concreteValue();
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

//----------------- JsonValueContext ------------------------------------------------------------------

PredaScriptParser::JsonValueContext::JsonValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::JsonParametersContext* PredaScriptParser::JsonValueContext::jsonParameters() {
  return getRuleContext<PredaScriptParser::JsonParametersContext>(0);
}

PredaScriptParser::PrimaryValueContext* PredaScriptParser::JsonValueContext::primaryValue() {
  return getRuleContext<PredaScriptParser::PrimaryValueContext>(0);
}

PredaScriptParser::IdentifierContext* PredaScriptParser::JsonValueContext::identifier() {
  return getRuleContext<PredaScriptParser::IdentifierContext>(0);
}


size_t PredaScriptParser::JsonValueContext::getRuleIndex() const {
  return PredaScriptParser::RuleJsonValue;
}

void PredaScriptParser::JsonValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterJsonValue(this);
}

void PredaScriptParser::JsonValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitJsonValue(this);
}

PredaScriptParser::JsonValueContext* PredaScriptParser::jsonValue() {
  JsonValueContext *_localctx = _tracker.createInstance<JsonValueContext>(_ctx, getState());
  enterRule(_localctx, 94, PredaScriptParser::RuleJsonValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(453);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaScriptParser::T__37: {
        enterOuterAlt(_localctx, 1);
        setState(450);
        jsonParameters();
        break;
      }

      case PredaScriptParser::T__22:
      case PredaScriptParser::T__31:
      case PredaScriptParser::T__40:
      case PredaScriptParser::TrueKeyword:
      case PredaScriptParser::FalseKeyword:
      case PredaScriptParser::DecimalNumber:
      case PredaScriptParser::HexNumber:
      case PredaScriptParser::StringLiteral: {
        enterOuterAlt(_localctx, 2);
        setState(451);
        primaryValue();
        break;
      }

      case PredaScriptParser::Identifier: {
        enterOuterAlt(_localctx, 3);
        setState(452);
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

//----------------- PrimaryValueContext ------------------------------------------------------------------

PredaScriptParser::PrimaryValueContext::PrimaryValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::ArrayValueContext* PredaScriptParser::PrimaryValueContext::arrayValue() {
  return getRuleContext<PredaScriptParser::ArrayValueContext>(0);
}

PredaScriptParser::ConcreteValueContext* PredaScriptParser::PrimaryValueContext::concreteValue() {
  return getRuleContext<PredaScriptParser::ConcreteValueContext>(0);
}

PredaScriptParser::ToBeAssignedValueContext* PredaScriptParser::PrimaryValueContext::toBeAssignedValue() {
  return getRuleContext<PredaScriptParser::ToBeAssignedValueContext>(0);
}


size_t PredaScriptParser::PrimaryValueContext::getRuleIndex() const {
  return PredaScriptParser::RulePrimaryValue;
}

void PredaScriptParser::PrimaryValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimaryValue(this);
}

void PredaScriptParser::PrimaryValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimaryValue(this);
}

PredaScriptParser::PrimaryValueContext* PredaScriptParser::primaryValue() {
  PrimaryValueContext *_localctx = _tracker.createInstance<PrimaryValueContext>(_ctx, getState());
  enterRule(_localctx, 96, PredaScriptParser::RulePrimaryValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(458);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaScriptParser::T__31: {
        enterOuterAlt(_localctx, 1);
        setState(455);
        arrayValue();
        break;
      }

      case PredaScriptParser::T__22:
      case PredaScriptParser::TrueKeyword:
      case PredaScriptParser::FalseKeyword:
      case PredaScriptParser::DecimalNumber:
      case PredaScriptParser::HexNumber:
      case PredaScriptParser::StringLiteral: {
        enterOuterAlt(_localctx, 2);
        setState(456);
        concreteValue();
        break;
      }

      case PredaScriptParser::T__40: {
        enterOuterAlt(_localctx, 3);
        setState(457);
        toBeAssignedValue();
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

//----------------- ArrayValueContext ------------------------------------------------------------------

PredaScriptParser::ArrayValueContext::ArrayValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PredaScriptParser::JsonValueContext *> PredaScriptParser::ArrayValueContext::jsonValue() {
  return getRuleContexts<PredaScriptParser::JsonValueContext>();
}

PredaScriptParser::JsonValueContext* PredaScriptParser::ArrayValueContext::jsonValue(size_t i) {
  return getRuleContext<PredaScriptParser::JsonValueContext>(i);
}


size_t PredaScriptParser::ArrayValueContext::getRuleIndex() const {
  return PredaScriptParser::RuleArrayValue;
}

void PredaScriptParser::ArrayValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayValue(this);
}

void PredaScriptParser::ArrayValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayValue(this);
}

PredaScriptParser::ArrayValueContext* PredaScriptParser::arrayValue() {
  ArrayValueContext *_localctx = _tracker.createInstance<ArrayValueContext>(_ctx, getState());
  enterRule(_localctx, 98, PredaScriptParser::RuleArrayValue);
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
    setState(460);
    match(PredaScriptParser::T__31);
    setState(462);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 23) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 23)) & 835628837405185) != 0)) {
      setState(461);
      jsonValue();
    }
    setState(468);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PredaScriptParser::T__38) {
      setState(464);
      match(PredaScriptParser::T__38);
      setState(465);
      jsonValue();
      setState(470);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(471);
    match(PredaScriptParser::T__32);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConcreteValueContext ------------------------------------------------------------------

PredaScriptParser::ConcreteValueContext::ConcreteValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::NumberLiteralContext* PredaScriptParser::ConcreteValueContext::numberLiteral() {
  return getRuleContext<PredaScriptParser::NumberLiteralContext>(0);
}

PredaScriptParser::StringLiteralContext* PredaScriptParser::ConcreteValueContext::stringLiteral() {
  return getRuleContext<PredaScriptParser::StringLiteralContext>(0);
}

PredaScriptParser::BoolLiteralContext* PredaScriptParser::ConcreteValueContext::boolLiteral() {
  return getRuleContext<PredaScriptParser::BoolLiteralContext>(0);
}

PredaScriptParser::HexLiteralContext* PredaScriptParser::ConcreteValueContext::hexLiteral() {
  return getRuleContext<PredaScriptParser::HexLiteralContext>(0);
}


size_t PredaScriptParser::ConcreteValueContext::getRuleIndex() const {
  return PredaScriptParser::RuleConcreteValue;
}

void PredaScriptParser::ConcreteValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConcreteValue(this);
}

void PredaScriptParser::ConcreteValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConcreteValue(this);
}

PredaScriptParser::ConcreteValueContext* PredaScriptParser::concreteValue() {
  ConcreteValueContext *_localctx = _tracker.createInstance<ConcreteValueContext>(_ctx, getState());
  enterRule(_localctx, 100, PredaScriptParser::RuleConcreteValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(477);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaScriptParser::T__22:
      case PredaScriptParser::DecimalNumber: {
        enterOuterAlt(_localctx, 1);
        setState(473);
        numberLiteral();
        break;
      }

      case PredaScriptParser::StringLiteral: {
        enterOuterAlt(_localctx, 2);
        setState(474);
        stringLiteral();
        break;
      }

      case PredaScriptParser::TrueKeyword:
      case PredaScriptParser::FalseKeyword: {
        enterOuterAlt(_localctx, 3);
        setState(475);
        boolLiteral();
        break;
      }

      case PredaScriptParser::HexNumber: {
        enterOuterAlt(_localctx, 4);
        setState(476);
        hexLiteral();
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

//----------------- ToBeAssignedValueContext ------------------------------------------------------------------

PredaScriptParser::ToBeAssignedValueContext::ToBeAssignedValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::AddressScopeContext* PredaScriptParser::ToBeAssignedValueContext::addressScope() {
  return getRuleContext<PredaScriptParser::AddressScopeContext>(0);
}

PredaScriptParser::BigintRandomContext* PredaScriptParser::ToBeAssignedValueContext::bigintRandom() {
  return getRuleContext<PredaScriptParser::BigintRandomContext>(0);
}

PredaScriptParser::IntExpressionContext* PredaScriptParser::ToBeAssignedValueContext::intExpression() {
  return getRuleContext<PredaScriptParser::IntExpressionContext>(0);
}


size_t PredaScriptParser::ToBeAssignedValueContext::getRuleIndex() const {
  return PredaScriptParser::RuleToBeAssignedValue;
}

void PredaScriptParser::ToBeAssignedValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterToBeAssignedValue(this);
}

void PredaScriptParser::ToBeAssignedValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitToBeAssignedValue(this);
}

PredaScriptParser::ToBeAssignedValueContext* PredaScriptParser::toBeAssignedValue() {
  ToBeAssignedValueContext *_localctx = _tracker.createInstance<ToBeAssignedValueContext>(_ctx, getState());
  enterRule(_localctx, 102, PredaScriptParser::RuleToBeAssignedValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(479);
    match(PredaScriptParser::T__40);
    setState(483);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaScriptParser::T__36: {
        setState(480);
        addressScope();
        break;
      }

      case PredaScriptParser::BIGINT: {
        setState(481);
        bigintRandom();
        break;
      }

      case PredaScriptParser::T__22:
      case PredaScriptParser::RANDOM:
      case PredaScriptParser::DecimalNumber: {
        setState(482);
        intExpression(0);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(485);
    match(PredaScriptParser::T__40);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BigintRandomContext ------------------------------------------------------------------

PredaScriptParser::BigintRandomContext::BigintRandomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaScriptParser::BigintRandomContext::BIGINT() {
  return getToken(PredaScriptParser::BIGINT, 0);
}

tree::TerminalNode* PredaScriptParser::BigintRandomContext::RANDOM() {
  return getToken(PredaScriptParser::RANDOM, 0);
}

PredaScriptParser::NumberLiteralContext* PredaScriptParser::BigintRandomContext::numberLiteral() {
  return getRuleContext<PredaScriptParser::NumberLiteralContext>(0);
}


size_t PredaScriptParser::BigintRandomContext::getRuleIndex() const {
  return PredaScriptParser::RuleBigintRandom;
}

void PredaScriptParser::BigintRandomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBigintRandom(this);
}

void PredaScriptParser::BigintRandomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBigintRandom(this);
}

PredaScriptParser::BigintRandomContext* PredaScriptParser::bigintRandom() {
  BigintRandomContext *_localctx = _tracker.createInstance<BigintRandomContext>(_ctx, getState());
  enterRule(_localctx, 104, PredaScriptParser::RuleBigintRandom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(487);
    match(PredaScriptParser::BIGINT);
    setState(488);
    match(PredaScriptParser::T__12);
    setState(489);
    match(PredaScriptParser::RANDOM);
    setState(490);
    match(PredaScriptParser::T__14);
    setState(491);
    numberLiteral();
    setState(492);
    match(PredaScriptParser::T__15);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntExpressionContext ------------------------------------------------------------------

PredaScriptParser::IntExpressionContext::IntExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::IntRandomContext* PredaScriptParser::IntExpressionContext::intRandom() {
  return getRuleContext<PredaScriptParser::IntRandomContext>(0);
}

PredaScriptParser::NumberLiteralContext* PredaScriptParser::IntExpressionContext::numberLiteral() {
  return getRuleContext<PredaScriptParser::NumberLiteralContext>(0);
}

std::vector<PredaScriptParser::IntExpressionContext *> PredaScriptParser::IntExpressionContext::intExpression() {
  return getRuleContexts<PredaScriptParser::IntExpressionContext>();
}

PredaScriptParser::IntExpressionContext* PredaScriptParser::IntExpressionContext::intExpression(size_t i) {
  return getRuleContext<PredaScriptParser::IntExpressionContext>(i);
}


size_t PredaScriptParser::IntExpressionContext::getRuleIndex() const {
  return PredaScriptParser::RuleIntExpression;
}

void PredaScriptParser::IntExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntExpression(this);
}

void PredaScriptParser::IntExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntExpression(this);
}


PredaScriptParser::IntExpressionContext* PredaScriptParser::intExpression() {
   return intExpression(0);
}

PredaScriptParser::IntExpressionContext* PredaScriptParser::intExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  PredaScriptParser::IntExpressionContext *_localctx = _tracker.createInstance<IntExpressionContext>(_ctx, parentState);
  PredaScriptParser::IntExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 106;
  enterRecursionRule(_localctx, 106, PredaScriptParser::RuleIntExpression, precedence);

    

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
    setState(501);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaScriptParser::RANDOM: {
        setState(495);
        intRandom();
        antlrcpp::downCast<IntExpressionContext *>(_localctx)->type =  4;
        break;
      }

      case PredaScriptParser::T__22:
      case PredaScriptParser::DecimalNumber: {
        setState(498);
        numberLiteral();
        antlrcpp::downCast<IntExpressionContext *>(_localctx)->type =  5;
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(525);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(523);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<IntExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleIntExpression);
          setState(503);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(504);
          match(PredaScriptParser::T__33);
          setState(505);
          intExpression(7);
          antlrcpp::downCast<IntExpressionContext *>(_localctx)->type =  0;
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<IntExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleIntExpression);
          setState(508);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(509);
          match(PredaScriptParser::T__41);
          setState(510);
          intExpression(6);
          antlrcpp::downCast<IntExpressionContext *>(_localctx)->type =  1;
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<IntExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleIntExpression);
          setState(513);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(514);
          match(PredaScriptParser::T__42);
          setState(515);
          intExpression(5);
          antlrcpp::downCast<IntExpressionContext *>(_localctx)->type =  2;
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<IntExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleIntExpression);
          setState(518);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(519);
          match(PredaScriptParser::T__22);
          setState(520);
          intExpression(4);
          antlrcpp::downCast<IntExpressionContext *>(_localctx)->type =  3;
          break;
        }

        default:
          break;
        } 
      }
      setState(527);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- IntRandomContext ------------------------------------------------------------------

PredaScriptParser::IntRandomContext::IntRandomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaScriptParser::IntRandomContext::RANDOM() {
  return getToken(PredaScriptParser::RANDOM, 0);
}

PredaScriptParser::RandomRangeContext* PredaScriptParser::IntRandomContext::randomRange() {
  return getRuleContext<PredaScriptParser::RandomRangeContext>(0);
}


size_t PredaScriptParser::IntRandomContext::getRuleIndex() const {
  return PredaScriptParser::RuleIntRandom;
}

void PredaScriptParser::IntRandomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntRandom(this);
}

void PredaScriptParser::IntRandomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntRandom(this);
}

PredaScriptParser::IntRandomContext* PredaScriptParser::intRandom() {
  IntRandomContext *_localctx = _tracker.createInstance<IntRandomContext>(_ctx, getState());
  enterRule(_localctx, 108, PredaScriptParser::RuleIntRandom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(528);
    match(PredaScriptParser::RANDOM);
    setState(530);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx)) {
    case 1: {
      setState(529);
      randomRange();
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

//----------------- RandomRangeContext ------------------------------------------------------------------

PredaScriptParser::RandomRangeContext::RandomRangeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PredaScriptParser::IntExpressionContext *> PredaScriptParser::RandomRangeContext::intExpression() {
  return getRuleContexts<PredaScriptParser::IntExpressionContext>();
}

PredaScriptParser::IntExpressionContext* PredaScriptParser::RandomRangeContext::intExpression(size_t i) {
  return getRuleContext<PredaScriptParser::IntExpressionContext>(i);
}


size_t PredaScriptParser::RandomRangeContext::getRuleIndex() const {
  return PredaScriptParser::RuleRandomRange;
}

void PredaScriptParser::RandomRangeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRandomRange(this);
}

void PredaScriptParser::RandomRangeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRandomRange(this);
}

PredaScriptParser::RandomRangeContext* PredaScriptParser::randomRange() {
  RandomRangeContext *_localctx = _tracker.createInstance<RandomRangeContext>(_ctx, getState());
  enterRule(_localctx, 110, PredaScriptParser::RuleRandomRange);

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
    match(PredaScriptParser::T__14);
    setState(533);
    antlrcpp::downCast<RandomRangeContext *>(_localctx)->min = intExpression(0);
    setState(534);
    match(PredaScriptParser::T__38);
    setState(535);
    antlrcpp::downCast<RandomRangeContext *>(_localctx)->max = intExpression(0);
    setState(536);
    match(PredaScriptParser::T__15);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SuppliedTokensContext ------------------------------------------------------------------

PredaScriptParser::SuppliedTokensContext::SuppliedTokensContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PredaScriptParser::TokenContext *> PredaScriptParser::SuppliedTokensContext::token() {
  return getRuleContexts<PredaScriptParser::TokenContext>();
}

PredaScriptParser::TokenContext* PredaScriptParser::SuppliedTokensContext::token(size_t i) {
  return getRuleContext<PredaScriptParser::TokenContext>(i);
}


size_t PredaScriptParser::SuppliedTokensContext::getRuleIndex() const {
  return PredaScriptParser::RuleSuppliedTokens;
}

void PredaScriptParser::SuppliedTokensContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSuppliedTokens(this);
}

void PredaScriptParser::SuppliedTokensContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSuppliedTokens(this);
}

PredaScriptParser::SuppliedTokensContext* PredaScriptParser::suppliedTokens() {
  SuppliedTokensContext *_localctx = _tracker.createInstance<SuppliedTokensContext>(_ctx, getState());
  enterRule(_localctx, 112, PredaScriptParser::RuleSuppliedTokens);
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
    setState(538);
    match(PredaScriptParser::T__14);
    setState(540);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 23) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 23)) & 35184372350977) != 0)) {
      setState(539);
      token();
    }
    setState(546);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PredaScriptParser::T__38) {
      setState(542);
      match(PredaScriptParser::T__38);
      setState(543);
      token();
      setState(548);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(549);
    match(PredaScriptParser::T__15);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TokenContext ------------------------------------------------------------------

PredaScriptParser::TokenContext::TokenContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::IdentifierContext* PredaScriptParser::TokenContext::identifier() {
  return getRuleContext<PredaScriptParser::IdentifierContext>(0);
}

PredaScriptParser::NumberLiteralContext* PredaScriptParser::TokenContext::numberLiteral() {
  return getRuleContext<PredaScriptParser::NumberLiteralContext>(0);
}

PredaScriptParser::IntExpressionContext* PredaScriptParser::TokenContext::intExpression() {
  return getRuleContext<PredaScriptParser::IntExpressionContext>(0);
}


size_t PredaScriptParser::TokenContext::getRuleIndex() const {
  return PredaScriptParser::RuleToken;
}

void PredaScriptParser::TokenContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterToken(this);
}

void PredaScriptParser::TokenContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitToken(this);
}

PredaScriptParser::TokenContext* PredaScriptParser::token() {
  TokenContext *_localctx = _tracker.createInstance<TokenContext>(_ctx, getState());
  enterRule(_localctx, 114, PredaScriptParser::RuleToken);

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
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaScriptParser::T__22:
      case PredaScriptParser::DecimalNumber: {
        setState(551);
        numberLiteral();
        break;
      }

      case PredaScriptParser::T__40: {
        setState(552);
        match(PredaScriptParser::T__40);
        setState(553);
        intExpression(0);
        setState(554);
        match(PredaScriptParser::T__40);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(558);
    identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DebugInfoContext ------------------------------------------------------------------

PredaScriptParser::DebugInfoContext::DebugInfoContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::LogInfoContext* PredaScriptParser::DebugInfoContext::logInfo() {
  return getRuleContext<PredaScriptParser::LogInfoContext>(0);
}

PredaScriptParser::TimeInfoContext* PredaScriptParser::DebugInfoContext::timeInfo() {
  return getRuleContext<PredaScriptParser::TimeInfoContext>(0);
}


size_t PredaScriptParser::DebugInfoContext::getRuleIndex() const {
  return PredaScriptParser::RuleDebugInfo;
}

void PredaScriptParser::DebugInfoContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDebugInfo(this);
}

void PredaScriptParser::DebugInfoContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDebugInfo(this);
}

PredaScriptParser::DebugInfoContext* PredaScriptParser::debugInfo() {
  DebugInfoContext *_localctx = _tracker.createInstance<DebugInfoContext>(_ctx, getState());
  enterRule(_localctx, 116, PredaScriptParser::RuleDebugInfo);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(562);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaScriptParser::T__43:
      case PredaScriptParser::T__44:
      case PredaScriptParser::T__45:
      case PredaScriptParser::T__46: {
        enterOuterAlt(_localctx, 1);
        setState(560);
        logInfo();
        break;
      }

      case PredaScriptParser::T__47:
      case PredaScriptParser::T__48: {
        enterOuterAlt(_localctx, 2);
        setState(561);
        timeInfo();
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

//----------------- LogInfoContext ------------------------------------------------------------------

PredaScriptParser::LogInfoContext::LogInfoContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::NormalLogContext* PredaScriptParser::LogInfoContext::normalLog() {
  return getRuleContext<PredaScriptParser::NormalLogContext>(0);
}

PredaScriptParser::LogHighlightContext* PredaScriptParser::LogInfoContext::logHighlight() {
  return getRuleContext<PredaScriptParser::LogHighlightContext>(0);
}

PredaScriptParser::LogWarningContext* PredaScriptParser::LogInfoContext::logWarning() {
  return getRuleContext<PredaScriptParser::LogWarningContext>(0);
}

PredaScriptParser::LogErrorContext* PredaScriptParser::LogInfoContext::logError() {
  return getRuleContext<PredaScriptParser::LogErrorContext>(0);
}


size_t PredaScriptParser::LogInfoContext::getRuleIndex() const {
  return PredaScriptParser::RuleLogInfo;
}

void PredaScriptParser::LogInfoContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogInfo(this);
}

void PredaScriptParser::LogInfoContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogInfo(this);
}

PredaScriptParser::LogInfoContext* PredaScriptParser::logInfo() {
  LogInfoContext *_localctx = _tracker.createInstance<LogInfoContext>(_ctx, getState());
  enterRule(_localctx, 118, PredaScriptParser::RuleLogInfo);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(568);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaScriptParser::T__43: {
        enterOuterAlt(_localctx, 1);
        setState(564);
        normalLog();
        break;
      }

      case PredaScriptParser::T__44: {
        enterOuterAlt(_localctx, 2);
        setState(565);
        logHighlight();
        break;
      }

      case PredaScriptParser::T__45: {
        enterOuterAlt(_localctx, 3);
        setState(566);
        logWarning();
        break;
      }

      case PredaScriptParser::T__46: {
        enterOuterAlt(_localctx, 4);
        setState(567);
        logError();
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

//----------------- NormalLogContext ------------------------------------------------------------------

PredaScriptParser::NormalLogContext::NormalLogContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::StringLiteralContext* PredaScriptParser::NormalLogContext::stringLiteral() {
  return getRuleContext<PredaScriptParser::StringLiteralContext>(0);
}


size_t PredaScriptParser::NormalLogContext::getRuleIndex() const {
  return PredaScriptParser::RuleNormalLog;
}

void PredaScriptParser::NormalLogContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNormalLog(this);
}

void PredaScriptParser::NormalLogContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNormalLog(this);
}

PredaScriptParser::NormalLogContext* PredaScriptParser::normalLog() {
  NormalLogContext *_localctx = _tracker.createInstance<NormalLogContext>(_ctx, getState());
  enterRule(_localctx, 120, PredaScriptParser::RuleNormalLog);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(570);
    match(PredaScriptParser::T__43);
    setState(571);
    stringLiteral();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogHighlightContext ------------------------------------------------------------------

PredaScriptParser::LogHighlightContext::LogHighlightContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::StringLiteralContext* PredaScriptParser::LogHighlightContext::stringLiteral() {
  return getRuleContext<PredaScriptParser::StringLiteralContext>(0);
}


size_t PredaScriptParser::LogHighlightContext::getRuleIndex() const {
  return PredaScriptParser::RuleLogHighlight;
}

void PredaScriptParser::LogHighlightContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogHighlight(this);
}

void PredaScriptParser::LogHighlightContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogHighlight(this);
}

PredaScriptParser::LogHighlightContext* PredaScriptParser::logHighlight() {
  LogHighlightContext *_localctx = _tracker.createInstance<LogHighlightContext>(_ctx, getState());
  enterRule(_localctx, 122, PredaScriptParser::RuleLogHighlight);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(573);
    match(PredaScriptParser::T__44);
    setState(574);
    stringLiteral();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogWarningContext ------------------------------------------------------------------

PredaScriptParser::LogWarningContext::LogWarningContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::StringLiteralContext* PredaScriptParser::LogWarningContext::stringLiteral() {
  return getRuleContext<PredaScriptParser::StringLiteralContext>(0);
}


size_t PredaScriptParser::LogWarningContext::getRuleIndex() const {
  return PredaScriptParser::RuleLogWarning;
}

void PredaScriptParser::LogWarningContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogWarning(this);
}

void PredaScriptParser::LogWarningContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogWarning(this);
}

PredaScriptParser::LogWarningContext* PredaScriptParser::logWarning() {
  LogWarningContext *_localctx = _tracker.createInstance<LogWarningContext>(_ctx, getState());
  enterRule(_localctx, 124, PredaScriptParser::RuleLogWarning);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(576);
    match(PredaScriptParser::T__45);
    setState(577);
    stringLiteral();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogErrorContext ------------------------------------------------------------------

PredaScriptParser::LogErrorContext::LogErrorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::StringLiteralContext* PredaScriptParser::LogErrorContext::stringLiteral() {
  return getRuleContext<PredaScriptParser::StringLiteralContext>(0);
}


size_t PredaScriptParser::LogErrorContext::getRuleIndex() const {
  return PredaScriptParser::RuleLogError;
}

void PredaScriptParser::LogErrorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogError(this);
}

void PredaScriptParser::LogErrorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogError(this);
}

PredaScriptParser::LogErrorContext* PredaScriptParser::logError() {
  LogErrorContext *_localctx = _tracker.createInstance<LogErrorContext>(_ctx, getState());
  enterRule(_localctx, 126, PredaScriptParser::RuleLogError);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(579);
    match(PredaScriptParser::T__46);
    setState(580);
    stringLiteral();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TimeInfoContext ------------------------------------------------------------------

PredaScriptParser::TimeInfoContext::TimeInfoContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::StopWatchRestartContext* PredaScriptParser::TimeInfoContext::stopWatchRestart() {
  return getRuleContext<PredaScriptParser::StopWatchRestartContext>(0);
}

PredaScriptParser::StopWatchReportContext* PredaScriptParser::TimeInfoContext::stopWatchReport() {
  return getRuleContext<PredaScriptParser::StopWatchReportContext>(0);
}


size_t PredaScriptParser::TimeInfoContext::getRuleIndex() const {
  return PredaScriptParser::RuleTimeInfo;
}

void PredaScriptParser::TimeInfoContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTimeInfo(this);
}

void PredaScriptParser::TimeInfoContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTimeInfo(this);
}

PredaScriptParser::TimeInfoContext* PredaScriptParser::timeInfo() {
  TimeInfoContext *_localctx = _tracker.createInstance<TimeInfoContext>(_ctx, getState());
  enterRule(_localctx, 128, PredaScriptParser::RuleTimeInfo);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(584);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaScriptParser::T__47: {
        enterOuterAlt(_localctx, 1);
        setState(582);
        stopWatchRestart();
        break;
      }

      case PredaScriptParser::T__48: {
        enterOuterAlt(_localctx, 2);
        setState(583);
        stopWatchReport();
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

//----------------- StopWatchRestartContext ------------------------------------------------------------------

PredaScriptParser::StopWatchRestartContext::StopWatchRestartContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t PredaScriptParser::StopWatchRestartContext::getRuleIndex() const {
  return PredaScriptParser::RuleStopWatchRestart;
}

void PredaScriptParser::StopWatchRestartContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStopWatchRestart(this);
}

void PredaScriptParser::StopWatchRestartContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStopWatchRestart(this);
}

PredaScriptParser::StopWatchRestartContext* PredaScriptParser::stopWatchRestart() {
  StopWatchRestartContext *_localctx = _tracker.createInstance<StopWatchRestartContext>(_ctx, getState());
  enterRule(_localctx, 130, PredaScriptParser::RuleStopWatchRestart);

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
    match(PredaScriptParser::T__47);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StopWatchReportContext ------------------------------------------------------------------

PredaScriptParser::StopWatchReportContext::StopWatchReportContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t PredaScriptParser::StopWatchReportContext::getRuleIndex() const {
  return PredaScriptParser::RuleStopWatchReport;
}

void PredaScriptParser::StopWatchReportContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStopWatchReport(this);
}

void PredaScriptParser::StopWatchReportContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStopWatchReport(this);
}

PredaScriptParser::StopWatchReportContext* PredaScriptParser::stopWatchReport() {
  StopWatchReportContext *_localctx = _tracker.createInstance<StopWatchReportContext>(_ctx, getState());
  enterRule(_localctx, 132, PredaScriptParser::RuleStopWatchReport);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(588);
    match(PredaScriptParser::T__48);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VizContext ------------------------------------------------------------------

PredaScriptParser::VizContext::VizContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::VizBlockContext* PredaScriptParser::VizContext::vizBlock() {
  return getRuleContext<PredaScriptParser::VizBlockContext>(0);
}

PredaScriptParser::VizAddrContext* PredaScriptParser::VizContext::vizAddr() {
  return getRuleContext<PredaScriptParser::VizAddrContext>(0);
}

PredaScriptParser::VizShardContext* PredaScriptParser::VizContext::vizShard() {
  return getRuleContext<PredaScriptParser::VizShardContext>(0);
}

PredaScriptParser::VizTxnContext* PredaScriptParser::VizContext::vizTxn() {
  return getRuleContext<PredaScriptParser::VizTxnContext>(0);
}

PredaScriptParser::VizTraceContext* PredaScriptParser::VizContext::vizTrace() {
  return getRuleContext<PredaScriptParser::VizTraceContext>(0);
}

PredaScriptParser::VizSectionContext* PredaScriptParser::VizContext::vizSection() {
  return getRuleContext<PredaScriptParser::VizSectionContext>(0);
}

PredaScriptParser::VizProfilingContext* PredaScriptParser::VizContext::vizProfiling() {
  return getRuleContext<PredaScriptParser::VizProfilingContext>(0);
}

PredaScriptParser::VizUintScopeContext* PredaScriptParser::VizContext::vizUintScope() {
  return getRuleContext<PredaScriptParser::VizUintScopeContext>(0);
}


size_t PredaScriptParser::VizContext::getRuleIndex() const {
  return PredaScriptParser::RuleViz;
}

void PredaScriptParser::VizContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterViz(this);
}

void PredaScriptParser::VizContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitViz(this);
}

PredaScriptParser::VizContext* PredaScriptParser::viz() {
  VizContext *_localctx = _tracker.createInstance<VizContext>(_ctx, getState());
  enterRule(_localctx, 134, PredaScriptParser::RuleViz);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(598);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaScriptParser::T__49: {
        enterOuterAlt(_localctx, 1);
        setState(590);
        vizBlock();
        break;
      }

      case PredaScriptParser::T__50: {
        enterOuterAlt(_localctx, 2);
        setState(591);
        vizAddr();
        break;
      }

      case PredaScriptParser::T__51: {
        enterOuterAlt(_localctx, 3);
        setState(592);
        vizShard();
        break;
      }

      case PredaScriptParser::T__52: {
        enterOuterAlt(_localctx, 4);
        setState(593);
        vizTxn();
        break;
      }

      case PredaScriptParser::T__53: {
        enterOuterAlt(_localctx, 5);
        setState(594);
        vizTrace();
        break;
      }

      case PredaScriptParser::T__54: {
        enterOuterAlt(_localctx, 6);
        setState(595);
        vizSection();
        break;
      }

      case PredaScriptParser::T__55: {
        enterOuterAlt(_localctx, 7);
        setState(596);
        vizProfiling();
        break;
      }

      case PredaScriptParser::T__56: {
        enterOuterAlt(_localctx, 8);
        setState(597);
        vizUintScope();
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

//----------------- VizBlockContext ------------------------------------------------------------------

PredaScriptParser::VizBlockContext::VizBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::ShardScopeContext* PredaScriptParser::VizBlockContext::shardScope() {
  return getRuleContext<PredaScriptParser::ShardScopeContext>(0);
}

PredaScriptParser::NumberLiteralContext* PredaScriptParser::VizBlockContext::numberLiteral() {
  return getRuleContext<PredaScriptParser::NumberLiteralContext>(0);
}


size_t PredaScriptParser::VizBlockContext::getRuleIndex() const {
  return PredaScriptParser::RuleVizBlock;
}

void PredaScriptParser::VizBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVizBlock(this);
}

void PredaScriptParser::VizBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVizBlock(this);
}

PredaScriptParser::VizBlockContext* PredaScriptParser::vizBlock() {
  VizBlockContext *_localctx = _tracker.createInstance<VizBlockContext>(_ctx, getState());
  enterRule(_localctx, 136, PredaScriptParser::RuleVizBlock);
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
    setState(600);
    match(PredaScriptParser::T__49);
    setState(601);
    shardScope();
    setState(604);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaScriptParser::T__8) {
      setState(602);
      match(PredaScriptParser::T__8);
      setState(603);
      numberLiteral();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VizAddrContext ------------------------------------------------------------------

PredaScriptParser::VizAddrContext::VizAddrContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::AddressScopeContext* PredaScriptParser::VizAddrContext::addressScope() {
  return getRuleContext<PredaScriptParser::AddressScopeContext>(0);
}

PredaScriptParser::ContractNameContext* PredaScriptParser::VizAddrContext::contractName() {
  return getRuleContext<PredaScriptParser::ContractNameContext>(0);
}


size_t PredaScriptParser::VizAddrContext::getRuleIndex() const {
  return PredaScriptParser::RuleVizAddr;
}

void PredaScriptParser::VizAddrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVizAddr(this);
}

void PredaScriptParser::VizAddrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVizAddr(this);
}

PredaScriptParser::VizAddrContext* PredaScriptParser::vizAddr() {
  VizAddrContext *_localctx = _tracker.createInstance<VizAddrContext>(_ctx, getState());
  enterRule(_localctx, 138, PredaScriptParser::RuleVizAddr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(606);
    match(PredaScriptParser::T__50);
    setState(607);
    addressScope();
    setState(609);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx)) {
    case 1: {
      setState(608);
      contractName();
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

//----------------- VizShardContext ------------------------------------------------------------------

PredaScriptParser::VizShardContext::VizShardContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::ShardScopeContext* PredaScriptParser::VizShardContext::shardScope() {
  return getRuleContext<PredaScriptParser::ShardScopeContext>(0);
}

PredaScriptParser::ContractNameContext* PredaScriptParser::VizShardContext::contractName() {
  return getRuleContext<PredaScriptParser::ContractNameContext>(0);
}


size_t PredaScriptParser::VizShardContext::getRuleIndex() const {
  return PredaScriptParser::RuleVizShard;
}

void PredaScriptParser::VizShardContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVizShard(this);
}

void PredaScriptParser::VizShardContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVizShard(this);
}

PredaScriptParser::VizShardContext* PredaScriptParser::vizShard() {
  VizShardContext *_localctx = _tracker.createInstance<VizShardContext>(_ctx, getState());
  enterRule(_localctx, 140, PredaScriptParser::RuleVizShard);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(611);
    match(PredaScriptParser::T__51);
    setState(612);
    shardScope();
    setState(614);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx)) {
    case 1: {
      setState(613);
      contractName();
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

//----------------- VizTxnContext ------------------------------------------------------------------

PredaScriptParser::VizTxnContext::VizTxnContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::TxnReturnInfoContext* PredaScriptParser::VizTxnContext::txnReturnInfo() {
  return getRuleContext<PredaScriptParser::TxnReturnInfoContext>(0);
}

PredaScriptParser::NumberLiteralContext* PredaScriptParser::VizTxnContext::numberLiteral() {
  return getRuleContext<PredaScriptParser::NumberLiteralContext>(0);
}


size_t PredaScriptParser::VizTxnContext::getRuleIndex() const {
  return PredaScriptParser::RuleVizTxn;
}

void PredaScriptParser::VizTxnContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVizTxn(this);
}

void PredaScriptParser::VizTxnContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVizTxn(this);
}

PredaScriptParser::VizTxnContext* PredaScriptParser::vizTxn() {
  VizTxnContext *_localctx = _tracker.createInstance<VizTxnContext>(_ctx, getState());
  enterRule(_localctx, 142, PredaScriptParser::RuleVizTxn);
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
    setState(616);
    match(PredaScriptParser::T__52);
    setState(617);
    txnReturnInfo();
    setState(622);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaScriptParser::T__31) {
      setState(618);
      match(PredaScriptParser::T__31);
      setState(619);
      numberLiteral();
      setState(620);
      match(PredaScriptParser::T__32);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VizTraceContext ------------------------------------------------------------------

PredaScriptParser::VizTraceContext::VizTraceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::TxnReturnInfoContext* PredaScriptParser::VizTraceContext::txnReturnInfo() {
  return getRuleContext<PredaScriptParser::TxnReturnInfoContext>(0);
}

PredaScriptParser::NumberLiteralContext* PredaScriptParser::VizTraceContext::numberLiteral() {
  return getRuleContext<PredaScriptParser::NumberLiteralContext>(0);
}


size_t PredaScriptParser::VizTraceContext::getRuleIndex() const {
  return PredaScriptParser::RuleVizTrace;
}

void PredaScriptParser::VizTraceContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVizTrace(this);
}

void PredaScriptParser::VizTraceContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVizTrace(this);
}

PredaScriptParser::VizTraceContext* PredaScriptParser::vizTrace() {
  VizTraceContext *_localctx = _tracker.createInstance<VizTraceContext>(_ctx, getState());
  enterRule(_localctx, 144, PredaScriptParser::RuleVizTrace);
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
    setState(624);
    match(PredaScriptParser::T__53);
    setState(625);
    txnReturnInfo();
    setState(630);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaScriptParser::T__31) {
      setState(626);
      match(PredaScriptParser::T__31);
      setState(627);
      numberLiteral();
      setState(628);
      match(PredaScriptParser::T__32);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VizSectionContext ------------------------------------------------------------------

PredaScriptParser::VizSectionContext::VizSectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::StringLiteralContext* PredaScriptParser::VizSectionContext::stringLiteral() {
  return getRuleContext<PredaScriptParser::StringLiteralContext>(0);
}


size_t PredaScriptParser::VizSectionContext::getRuleIndex() const {
  return PredaScriptParser::RuleVizSection;
}

void PredaScriptParser::VizSectionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVizSection(this);
}

void PredaScriptParser::VizSectionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVizSection(this);
}

PredaScriptParser::VizSectionContext* PredaScriptParser::vizSection() {
  VizSectionContext *_localctx = _tracker.createInstance<VizSectionContext>(_ctx, getState());
  enterRule(_localctx, 146, PredaScriptParser::RuleVizSection);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(632);
    match(PredaScriptParser::T__54);
    setState(633);
    stringLiteral();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VizProfilingContext ------------------------------------------------------------------

PredaScriptParser::VizProfilingContext::VizProfilingContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t PredaScriptParser::VizProfilingContext::getRuleIndex() const {
  return PredaScriptParser::RuleVizProfiling;
}

void PredaScriptParser::VizProfilingContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVizProfiling(this);
}

void PredaScriptParser::VizProfilingContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVizProfiling(this);
}

PredaScriptParser::VizProfilingContext* PredaScriptParser::vizProfiling() {
  VizProfilingContext *_localctx = _tracker.createInstance<VizProfilingContext>(_ctx, getState());
  enterRule(_localctx, 148, PredaScriptParser::RuleVizProfiling);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(635);
    match(PredaScriptParser::T__55);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VizUintScopeContext ------------------------------------------------------------------

PredaScriptParser::VizUintScopeContext::VizUintScopeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PredaScriptParser::UintScopeContext* PredaScriptParser::VizUintScopeContext::uintScope() {
  return getRuleContext<PredaScriptParser::UintScopeContext>(0);
}

PredaScriptParser::ContractNameContext* PredaScriptParser::VizUintScopeContext::contractName() {
  return getRuleContext<PredaScriptParser::ContractNameContext>(0);
}

PredaScriptParser::ScopeTargetContext* PredaScriptParser::VizUintScopeContext::scopeTarget() {
  return getRuleContext<PredaScriptParser::ScopeTargetContext>(0);
}


size_t PredaScriptParser::VizUintScopeContext::getRuleIndex() const {
  return PredaScriptParser::RuleVizUintScope;
}

void PredaScriptParser::VizUintScopeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVizUintScope(this);
}

void PredaScriptParser::VizUintScopeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVizUintScope(this);
}

PredaScriptParser::VizUintScopeContext* PredaScriptParser::vizUintScope() {
  VizUintScopeContext *_localctx = _tracker.createInstance<VizUintScopeContext>(_ctx, getState());
  enterRule(_localctx, 150, PredaScriptParser::RuleVizUintScope);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(637);
    match(PredaScriptParser::T__56);
    setState(638);
    uintScope();
    setState(639);
    contractName();
    setState(640);
    match(PredaScriptParser::T__8);
    setState(641);
    scopeTarget();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UintScopeContext ------------------------------------------------------------------

PredaScriptParser::UintScopeContext::UintScopeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaScriptParser::UintScopeContext::ALL() {
  return getToken(PredaScriptParser::ALL, 0);
}

PredaScriptParser::NumberLiteralContext* PredaScriptParser::UintScopeContext::numberLiteral() {
  return getRuleContext<PredaScriptParser::NumberLiteralContext>(0);
}


size_t PredaScriptParser::UintScopeContext::getRuleIndex() const {
  return PredaScriptParser::RuleUintScope;
}

void PredaScriptParser::UintScopeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUintScope(this);
}

void PredaScriptParser::UintScopeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUintScope(this);
}

PredaScriptParser::UintScopeContext* PredaScriptParser::uintScope() {
  UintScopeContext *_localctx = _tracker.createInstance<UintScopeContext>(_ctx, getState());
  enterRule(_localctx, 152, PredaScriptParser::RuleUintScope);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(643);
    match(PredaScriptParser::T__35);
    setState(646);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaScriptParser::ALL: {
        setState(644);
        match(PredaScriptParser::ALL);
        break;
      }

      case PredaScriptParser::T__22:
      case PredaScriptParser::DecimalNumber: {
        setState(645);
        numberLiteral();
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

//----------------- ScopeTargetContext ------------------------------------------------------------------

PredaScriptParser::ScopeTargetContext::ScopeTargetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaScriptParser::ScopeTargetContext::ALL() {
  return getToken(PredaScriptParser::ALL, 0);
}

PredaScriptParser::NumberLiteralContext* PredaScriptParser::ScopeTargetContext::numberLiteral() {
  return getRuleContext<PredaScriptParser::NumberLiteralContext>(0);
}


size_t PredaScriptParser::ScopeTargetContext::getRuleIndex() const {
  return PredaScriptParser::RuleScopeTarget;
}

void PredaScriptParser::ScopeTargetContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterScopeTarget(this);
}

void PredaScriptParser::ScopeTargetContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitScopeTarget(this);
}

PredaScriptParser::ScopeTargetContext* PredaScriptParser::scopeTarget() {
  ScopeTargetContext *_localctx = _tracker.createInstance<ScopeTargetContext>(_ctx, getState());
  enterRule(_localctx, 154, PredaScriptParser::RuleScopeTarget);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(650);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PredaScriptParser::ALL: {
        enterOuterAlt(_localctx, 1);
        setState(648);
        match(PredaScriptParser::ALL);
        break;
      }

      case PredaScriptParser::T__22:
      case PredaScriptParser::DecimalNumber: {
        enterOuterAlt(_localctx, 2);
        setState(649);
        numberLiteral();
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

//----------------- NumberLiteralContext ------------------------------------------------------------------

PredaScriptParser::NumberLiteralContext::NumberLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaScriptParser::NumberLiteralContext::DecimalNumber() {
  return getToken(PredaScriptParser::DecimalNumber, 0);
}


size_t PredaScriptParser::NumberLiteralContext::getRuleIndex() const {
  return PredaScriptParser::RuleNumberLiteral;
}

void PredaScriptParser::NumberLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumberLiteral(this);
}

void PredaScriptParser::NumberLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumberLiteral(this);
}

PredaScriptParser::NumberLiteralContext* PredaScriptParser::numberLiteral() {
  NumberLiteralContext *_localctx = _tracker.createInstance<NumberLiteralContext>(_ctx, getState());
  enterRule(_localctx, 156, PredaScriptParser::RuleNumberLiteral);
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
    setState(653);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PredaScriptParser::T__22) {
      setState(652);
      match(PredaScriptParser::T__22);
    }
    setState(655);
    match(PredaScriptParser::DecimalNumber);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- HexLiteralContext ------------------------------------------------------------------

PredaScriptParser::HexLiteralContext::HexLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaScriptParser::HexLiteralContext::HexNumber() {
  return getToken(PredaScriptParser::HexNumber, 0);
}


size_t PredaScriptParser::HexLiteralContext::getRuleIndex() const {
  return PredaScriptParser::RuleHexLiteral;
}

void PredaScriptParser::HexLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterHexLiteral(this);
}

void PredaScriptParser::HexLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitHexLiteral(this);
}

PredaScriptParser::HexLiteralContext* PredaScriptParser::hexLiteral() {
  HexLiteralContext *_localctx = _tracker.createInstance<HexLiteralContext>(_ctx, getState());
  enterRule(_localctx, 158, PredaScriptParser::RuleHexLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(657);
    match(PredaScriptParser::HexNumber);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StringLiteralContext ------------------------------------------------------------------

PredaScriptParser::StringLiteralContext::StringLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaScriptParser::StringLiteralContext::StringLiteral() {
  return getToken(PredaScriptParser::StringLiteral, 0);
}


size_t PredaScriptParser::StringLiteralContext::getRuleIndex() const {
  return PredaScriptParser::RuleStringLiteral;
}

void PredaScriptParser::StringLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStringLiteral(this);
}

void PredaScriptParser::StringLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStringLiteral(this);
}

PredaScriptParser::StringLiteralContext* PredaScriptParser::stringLiteral() {
  StringLiteralContext *_localctx = _tracker.createInstance<StringLiteralContext>(_ctx, getState());
  enterRule(_localctx, 160, PredaScriptParser::RuleStringLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(659);
    match(PredaScriptParser::StringLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BoolLiteralContext ------------------------------------------------------------------

PredaScriptParser::BoolLiteralContext::BoolLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaScriptParser::BoolLiteralContext::TrueKeyword() {
  return getToken(PredaScriptParser::TrueKeyword, 0);
}

tree::TerminalNode* PredaScriptParser::BoolLiteralContext::FalseKeyword() {
  return getToken(PredaScriptParser::FalseKeyword, 0);
}


size_t PredaScriptParser::BoolLiteralContext::getRuleIndex() const {
  return PredaScriptParser::RuleBoolLiteral;
}

void PredaScriptParser::BoolLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBoolLiteral(this);
}

void PredaScriptParser::BoolLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBoolLiteral(this);
}

PredaScriptParser::BoolLiteralContext* PredaScriptParser::boolLiteral() {
  BoolLiteralContext *_localctx = _tracker.createInstance<BoolLiteralContext>(_ctx, getState());
  enterRule(_localctx, 162, PredaScriptParser::RuleBoolLiteral);
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
    setState(661);
    _la = _input->LA(1);
    if (!(_la == PredaScriptParser::TrueKeyword

    || _la == PredaScriptParser::FalseKeyword)) {
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

//----------------- Ed25519AddressContext ------------------------------------------------------------------

PredaScriptParser::Ed25519AddressContext::Ed25519AddressContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaScriptParser::Ed25519AddressContext::Ed25519Address() {
  return getToken(PredaScriptParser::Ed25519Address, 0);
}


size_t PredaScriptParser::Ed25519AddressContext::getRuleIndex() const {
  return PredaScriptParser::RuleEd25519Address;
}

void PredaScriptParser::Ed25519AddressContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEd25519Address(this);
}

void PredaScriptParser::Ed25519AddressContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEd25519Address(this);
}

PredaScriptParser::Ed25519AddressContext* PredaScriptParser::ed25519Address() {
  Ed25519AddressContext *_localctx = _tracker.createInstance<Ed25519AddressContext>(_ctx, getState());
  enterRule(_localctx, 164, PredaScriptParser::RuleEd25519Address);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(663);
    match(PredaScriptParser::Ed25519Address);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierContext ------------------------------------------------------------------

PredaScriptParser::IdentifierContext::IdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaScriptParser::IdentifierContext::Identifier() {
  return getToken(PredaScriptParser::Identifier, 0);
}


size_t PredaScriptParser::IdentifierContext::getRuleIndex() const {
  return PredaScriptParser::RuleIdentifier;
}

void PredaScriptParser::IdentifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifier(this);
}

void PredaScriptParser::IdentifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifier(this);
}

PredaScriptParser::IdentifierContext* PredaScriptParser::identifier() {
  IdentifierContext *_localctx = _tracker.createInstance<IdentifierContext>(_ctx, getState());
  enterRule(_localctx, 166, PredaScriptParser::RuleIdentifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(665);
    match(PredaScriptParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FileNameContext ------------------------------------------------------------------

PredaScriptParser::FileNameContext::FileNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> PredaScriptParser::FileNameContext::Identifier() {
  return getTokens(PredaScriptParser::Identifier);
}

tree::TerminalNode* PredaScriptParser::FileNameContext::Identifier(size_t i) {
  return getToken(PredaScriptParser::Identifier, i);
}


size_t PredaScriptParser::FileNameContext::getRuleIndex() const {
  return PredaScriptParser::RuleFileName;
}

void PredaScriptParser::FileNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFileName(this);
}

void PredaScriptParser::FileNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFileName(this);
}

PredaScriptParser::FileNameContext* PredaScriptParser::fileName() {
  FileNameContext *_localctx = _tracker.createInstance<FileNameContext>(_ctx, getState());
  enterRule(_localctx, 168, PredaScriptParser::RuleFileName);
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
    setState(670);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(667);
        _la = _input->LA(1);
        if (!(_la == PredaScriptParser::T__22

        || _la == PredaScriptParser::Identifier)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        } 
      }
      setState(672);
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

//----------------- DirectivePathContext ------------------------------------------------------------------

PredaScriptParser::DirectivePathContext::DirectivePathContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PredaScriptParser::DirectivePathContext::WINPATH() {
  return getToken(PredaScriptParser::WINPATH, 0);
}

tree::TerminalNode* PredaScriptParser::DirectivePathContext::UNIXPATH() {
  return getToken(PredaScriptParser::UNIXPATH, 0);
}


size_t PredaScriptParser::DirectivePathContext::getRuleIndex() const {
  return PredaScriptParser::RuleDirectivePath;
}

void PredaScriptParser::DirectivePathContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDirectivePath(this);
}

void PredaScriptParser::DirectivePathContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PredaScriptListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDirectivePath(this);
}

PredaScriptParser::DirectivePathContext* PredaScriptParser::directivePath() {
  DirectivePathContext *_localctx = _tracker.createInstance<DirectivePathContext>(_ctx, getState());
  enterRule(_localctx, 170, PredaScriptParser::RuleDirectivePath);
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
    setState(673);
    _la = _input->LA(1);
    if (!(_la == PredaScriptParser::WINPATH

    || _la == PredaScriptParser::UNIXPATH)) {
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

bool PredaScriptParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 53: return intExpressionSempred(antlrcpp::downCast<IntExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool PredaScriptParser::intExpressionSempred(IntExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 6);
    case 1: return precpred(_ctx, 5);
    case 2: return precpred(_ctx, 4);
    case 3: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

void PredaScriptParser::initialize() {
  ::antlr4::internal::call_once(predascriptParserOnceFlag, predascriptParserInitialize);
}
