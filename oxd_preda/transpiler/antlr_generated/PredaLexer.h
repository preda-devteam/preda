
// Generated from Preda.g4 by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"




class  PredaLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, T__24 = 25, T__25 = 26, 
    T__26 = 27, T__27 = 28, T__28 = 29, T__29 = 30, T__30 = 31, T__31 = 32, 
    T__32 = 33, T__33 = 34, T__34 = 35, T__35 = 36, T__36 = 37, T__37 = 38, 
    T__38 = 39, T__39 = 40, T__40 = 41, T__41 = 42, T__42 = 43, T__43 = 44, 
    T__44 = 45, T__45 = 46, T__46 = 47, T__47 = 48, T__48 = 49, T__49 = 50, 
    T__50 = 51, T__51 = 52, T__52 = 53, T__53 = 54, T__54 = 55, DoxygenSingle = 56, 
    DoxygenMulti = 57, BreakKeyword = 58, ConstantKeyword = 59, ContinueKeyword = 60, 
    RelayKeyword = 61, SupplyKeyword = 62, IfKeyword = 63, ElseKeyword = 64, 
    ShardKeyword = 65, ShardsKeyword = 66, GlobalKeyword = 67, AddressKeyword = 68, 
    AutoKeyword = 69, MinerKeyword = 70, StructKeyword = 71, EnumKeyword = 72, 
    ContractKeyword = 73, ImportKeyword = 74, FunctionKeyword = 75, PublicKeyword = 76, 
    ExportKeyword = 77, AsKeyword = 78, UsingKeyword = 79, InterfaceKeyword = 80, 
    ImplementsKeyword = 81, DeployKeyword = 82, ConstructorKeyword = 83, 
    NextKeyword = 84, FloatType = 85, IntType = 86, UintType = 87, BooleanLiteral = 88, 
    DecimalFloatLiteral = 89, DecimalIntegerLiteral = 90, DecimalIntegerLiteralBody = 91, 
    AddressLiteral = 92, HashLiteral = 93, HexIntegerLiteral = 94, HexIntegerLiteralBody = 95, 
    DecimalBigIntegerLiteral = 96, HexBigIntegerLiteral = 97, Identifier = 98, 
    StringLiteral = 99, WS = 100, COMMENT = 101, LINE_COMMENT = 102
  };

  explicit PredaLexer(antlr4::CharStream *input);
  ~PredaLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

