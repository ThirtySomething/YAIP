
// Generated from IniFile.g4 by ANTLR 4.10.1


#include "IniFileLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct IniFileLexerStaticData final {
  IniFileLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  IniFileLexerStaticData(const IniFileLexerStaticData&) = delete;
  IniFileLexerStaticData(IniFileLexerStaticData&&) = delete;
  IniFileLexerStaticData& operator=(const IniFileLexerStaticData&) = delete;
  IniFileLexerStaticData& operator=(IniFileLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag inifilelexerLexerOnceFlag;
IniFileLexerStaticData *inifilelexerLexerStaticData = nullptr;

void inifilelexerLexerInitialize() {
  assert(inifilelexerLexerStaticData == nullptr);
  auto staticData = std::make_unique<IniFileLexerStaticData>(
    std::vector<std::string>{
      "T__0", "ID", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'hello'"
    },
    std::vector<std::string>{
      "", "", "ID", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,3,25,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,1,0,1,0,1,0,1,0,1,0,1,0,1,1,4,1,
  	15,8,1,11,1,12,1,16,1,2,4,2,20,8,2,11,2,12,2,21,1,2,1,2,0,0,3,1,1,3,2,
  	5,3,1,0,2,1,0,97,122,3,0,9,10,13,13,32,32,26,0,1,1,0,0,0,0,3,1,0,0,0,
  	0,5,1,0,0,0,1,7,1,0,0,0,3,14,1,0,0,0,5,19,1,0,0,0,7,8,5,104,0,0,8,9,5,
  	101,0,0,9,10,5,108,0,0,10,11,5,108,0,0,11,12,5,111,0,0,12,2,1,0,0,0,13,
  	15,7,0,0,0,14,13,1,0,0,0,15,16,1,0,0,0,16,14,1,0,0,0,16,17,1,0,0,0,17,
  	4,1,0,0,0,18,20,7,1,0,0,19,18,1,0,0,0,20,21,1,0,0,0,21,19,1,0,0,0,21,
  	22,1,0,0,0,22,23,1,0,0,0,23,24,6,2,0,0,24,6,1,0,0,0,3,0,16,21,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  inifilelexerLexerStaticData = staticData.release();
}

}

IniFileLexer::IniFileLexer(CharStream *input) : Lexer(input) {
  IniFileLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *inifilelexerLexerStaticData->atn, inifilelexerLexerStaticData->decisionToDFA, inifilelexerLexerStaticData->sharedContextCache);
}

IniFileLexer::~IniFileLexer() {
  delete _interpreter;
}

std::string IniFileLexer::getGrammarFileName() const {
  return "IniFile.g4";
}

const std::vector<std::string>& IniFileLexer::getRuleNames() const {
  return inifilelexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& IniFileLexer::getChannelNames() const {
  return inifilelexerLexerStaticData->channelNames;
}

const std::vector<std::string>& IniFileLexer::getModeNames() const {
  return inifilelexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& IniFileLexer::getVocabulary() const {
  return inifilelexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView IniFileLexer::getSerializedATN() const {
  return inifilelexerLexerStaticData->serializedATN;
}

const atn::ATN& IniFileLexer::getATN() const {
  return *inifilelexerLexerStaticData->atn;
}




void IniFileLexer::initialize() {
  std::call_once(inifilelexerLexerOnceFlag, inifilelexerLexerInitialize);
}
