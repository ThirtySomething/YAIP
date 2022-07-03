
// Generated from IniFile.g4 by ANTLR 4.10.1


#include "IniFileListener.h"

#include "IniFileParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct IniFileParserStaticData final {
  IniFileParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  IniFileParserStaticData(const IniFileParserStaticData&) = delete;
  IniFileParserStaticData(IniFileParserStaticData&&) = delete;
  IniFileParserStaticData& operator=(const IniFileParserStaticData&) = delete;
  IniFileParserStaticData& operator=(IniFileParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag inifileParserOnceFlag;
IniFileParserStaticData *inifileParserStaticData = nullptr;

void inifileParserInitialize() {
  assert(inifileParserStaticData == nullptr);
  auto staticData = std::make_unique<IniFileParserStaticData>(
    std::vector<std::string>{
      "r"
    },
    std::vector<std::string>{
      "", "'hello'"
    },
    std::vector<std::string>{
      "", "", "ID", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,3,6,2,0,7,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,4,0,2,1,0,0,0,2,3,5,1,0,0,
  	3,4,5,2,0,0,4,1,1,0,0,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  inifileParserStaticData = staticData.release();
}

}

IniFileParser::IniFileParser(TokenStream *input) : IniFileParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

IniFileParser::IniFileParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  IniFileParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *inifileParserStaticData->atn, inifileParserStaticData->decisionToDFA, inifileParserStaticData->sharedContextCache, options);
}

IniFileParser::~IniFileParser() {
  delete _interpreter;
}

const atn::ATN& IniFileParser::getATN() const {
  return *inifileParserStaticData->atn;
}

std::string IniFileParser::getGrammarFileName() const {
  return "IniFile.g4";
}

const std::vector<std::string>& IniFileParser::getRuleNames() const {
  return inifileParserStaticData->ruleNames;
}

const dfa::Vocabulary& IniFileParser::getVocabulary() const {
  return inifileParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView IniFileParser::getSerializedATN() const {
  return inifileParserStaticData->serializedATN;
}


//----------------- RContext ------------------------------------------------------------------

IniFileParser::RContext::RContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IniFileParser::RContext::ID() {
  return getToken(IniFileParser::ID, 0);
}


size_t IniFileParser::RContext::getRuleIndex() const {
  return IniFileParser::RuleR;
}

void IniFileParser::RContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IniFileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterR(this);
}

void IniFileParser::RContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<IniFileListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitR(this);
}

IniFileParser::RContext* IniFileParser::r() {
  RContext *_localctx = _tracker.createInstance<RContext>(_ctx, getState());
  enterRule(_localctx, 0, IniFileParser::RuleR);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(2);
    match(IniFileParser::T__0);
    setState(3);
    match(IniFileParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void IniFileParser::initialize() {
  std::call_once(inifileParserOnceFlag, inifileParserInitialize);
}
