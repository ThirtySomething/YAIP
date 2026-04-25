
// Generated from /home/jochen/workdir/YAIP/src/lib/antlr/IniLexer.g4 by ANTLR 4.13.2


#include "IniLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct IniLexerStaticData final {
  IniLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  IniLexerStaticData(const IniLexerStaticData&) = delete;
  IniLexerStaticData(IniLexerStaticData&&) = delete;
  IniLexerStaticData& operator=(const IniLexerStaticData&) = delete;
  IniLexerStaticData& operator=(IniLexerStaticData&&) = delete;

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

::antlr4::internal::OnceFlag inilexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<IniLexerStaticData> inilexerLexerStaticData = nullptr;

void inilexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (inilexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(inilexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<IniLexerStaticData>(
    std::vector<std::string>{
      "LBRACK", "RBRACK", "EQUAL", "SEMI", "NL", "TEXT", "VALUE_SEMI", "VALUE_NL", 
      "VALUE_TEXT"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE", "VALUE_MODE"
    },
    std::vector<std::string>{
      "", "'['", "']'", "'='"
    },
    std::vector<std::string>{
      "", "LBRACK", "RBRACK", "EQUAL", "SEMI", "NL", "TEXT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,6,60,6,-1,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,
  	6,7,6,2,7,7,7,2,8,7,8,1,0,1,0,1,1,1,1,1,2,1,2,1,2,1,2,1,3,1,3,1,4,3,4,
  	32,8,4,1,4,1,4,1,5,4,5,37,8,5,11,5,12,5,38,1,6,1,6,1,6,1,6,1,6,1,7,3,
  	7,47,8,7,1,7,1,7,1,7,1,7,1,7,1,8,4,8,55,8,8,11,8,12,8,56,1,8,1,8,0,0,
  	9,2,1,4,2,6,3,8,4,10,5,12,6,14,0,16,0,18,0,2,0,1,2,6,0,10,10,13,13,59,
  	59,61,61,91,91,93,93,3,0,10,10,13,13,59,59,62,0,2,1,0,0,0,0,4,1,0,0,0,
  	0,6,1,0,0,0,0,8,1,0,0,0,0,10,1,0,0,0,0,12,1,0,0,0,1,14,1,0,0,0,1,16,1,
  	0,0,0,1,18,1,0,0,0,2,20,1,0,0,0,4,22,1,0,0,0,6,24,1,0,0,0,8,28,1,0,0,
  	0,10,31,1,0,0,0,12,36,1,0,0,0,14,40,1,0,0,0,16,46,1,0,0,0,18,54,1,0,0,
  	0,20,21,5,91,0,0,21,3,1,0,0,0,22,23,5,93,0,0,23,5,1,0,0,0,24,25,5,61,
  	0,0,25,26,1,0,0,0,26,27,6,2,0,0,27,7,1,0,0,0,28,29,5,59,0,0,29,9,1,0,
  	0,0,30,32,5,13,0,0,31,30,1,0,0,0,31,32,1,0,0,0,32,33,1,0,0,0,33,34,5,
  	10,0,0,34,11,1,0,0,0,35,37,8,0,0,0,36,35,1,0,0,0,37,38,1,0,0,0,38,36,
  	1,0,0,0,38,39,1,0,0,0,39,13,1,0,0,0,40,41,5,59,0,0,41,42,1,0,0,0,42,43,
  	6,6,1,0,43,44,6,6,2,0,44,15,1,0,0,0,45,47,5,13,0,0,46,45,1,0,0,0,46,47,
  	1,0,0,0,47,48,1,0,0,0,48,49,5,10,0,0,49,50,1,0,0,0,50,51,6,7,3,0,51,52,
  	6,7,2,0,52,17,1,0,0,0,53,55,8,1,0,0,54,53,1,0,0,0,55,56,1,0,0,0,56,54,
  	1,0,0,0,56,57,1,0,0,0,57,58,1,0,0,0,58,59,6,8,4,0,59,19,1,0,0,0,6,0,1,
  	31,38,46,56,5,5,1,0,7,4,0,4,0,0,7,5,0,7,6,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  inilexerLexerStaticData = std::move(staticData);
}

}

IniLexer::IniLexer(CharStream *input) : Lexer(input) {
  IniLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *inilexerLexerStaticData->atn, inilexerLexerStaticData->decisionToDFA, inilexerLexerStaticData->sharedContextCache);
}

IniLexer::~IniLexer() {
  delete _interpreter;
}

std::string IniLexer::getGrammarFileName() const {
  return "IniLexer.g4";
}

const std::vector<std::string>& IniLexer::getRuleNames() const {
  return inilexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& IniLexer::getChannelNames() const {
  return inilexerLexerStaticData->channelNames;
}

const std::vector<std::string>& IniLexer::getModeNames() const {
  return inilexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& IniLexer::getVocabulary() const {
  return inilexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView IniLexer::getSerializedATN() const {
  return inilexerLexerStaticData->serializedATN;
}

const atn::ATN& IniLexer::getATN() const {
  return *inilexerLexerStaticData->atn;
}




void IniLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  inilexerLexerInitialize();
#else
  ::antlr4::internal::call_once(inilexerLexerOnceFlag, inilexerLexerInitialize);
#endif
}
