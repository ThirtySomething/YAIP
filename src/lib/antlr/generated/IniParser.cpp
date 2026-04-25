
// Generated from /home/jochen/workdir/YAIP/src/lib/antlr/IniParser.g4 by ANTLR 4.13.2


#include "IniParserVisitor.h"

#include "IniParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct IniParserStaticData final {
  IniParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  IniParserStaticData(const IniParserStaticData&) = delete;
  IniParserStaticData(IniParserStaticData&&) = delete;
  IniParserStaticData& operator=(const IniParserStaticData&) = delete;
  IniParserStaticData& operator=(IniParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag iniparserParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<IniParserStaticData> iniparserParserStaticData = nullptr;

void iniparserParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (iniparserParserStaticData != nullptr) {
    return;
  }
#else
  assert(iniparserParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<IniParserStaticData>(
    std::vector<std::string>{
      "iniFile", "statement", "sectionStatement", "pairStatement", "commentStatement", 
      "comment", "text"
    },
    std::vector<std::string>{
      "", "'['", "']'", "'='"
    },
    std::vector<std::string>{
      "", "LBRACK", "RBRACK", "EQUAL", "SEMI", "NL", "TEXT"
    }
  );
  static const int32_t serializedATNSegment[] = {
    4,1,6,70,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,1,0,
    5,0,16,8,0,10,0,12,0,19,9,0,1,0,1,0,1,1,1,1,1,1,1,1,3,1,27,8,1,1,2,1,
    2,3,2,31,8,2,1,2,1,2,3,2,35,8,2,1,2,3,2,38,8,2,1,3,1,3,1,3,3,3,43,8,3,
    1,3,3,3,46,8,3,1,3,3,3,49,8,3,1,4,3,4,52,8,4,1,4,1,4,3,4,56,8,4,1,4,3,
    4,59,8,4,1,5,1,5,3,5,63,8,5,1,6,4,6,66,8,6,11,6,12,6,67,1,6,0,0,7,0,2,
    4,6,8,10,12,0,0,77,0,17,1,0,0,0,2,26,1,0,0,0,4,28,1,0,0,0,6,39,1,0,0,
    0,8,51,1,0,0,0,10,60,1,0,0,0,12,65,1,0,0,0,14,16,3,2,1,0,15,14,1,0,0,
    0,16,19,1,0,0,0,17,15,1,0,0,0,17,18,1,0,0,0,18,20,1,0,0,0,19,17,1,0,0,
    0,20,21,5,0,0,1,21,1,1,0,0,0,22,27,3,4,2,0,23,27,3,6,3,0,24,27,3,8,4,
    0,25,27,5,5,0,0,26,22,1,0,0,0,26,23,1,0,0,0,26,24,1,0,0,0,26,25,1,0,0,
    0,27,3,1,0,0,0,28,30,5,1,0,0,29,31,3,12,6,0,30,29,1,0,0,0,30,31,1,0,0,
    0,31,32,1,0,0,0,32,34,5,2,0,0,33,35,3,10,5,0,34,33,1,0,0,0,34,35,1,0,
    0,0,35,37,1,0,0,0,36,38,5,5,0,0,37,36,1,0,0,0,37,38,1,0,0,0,38,5,1,0,
    0,0,39,40,3,12,6,0,40,42,5,3,0,0,41,43,3,12,6,0,42,41,1,0,0,0,42,43,1,
    0,0,0,43,45,1,0,0,0,44,46,3,10,5,0,45,44,1,0,0,0,45,46,1,0,0,0,46,48,
    1,0,0,0,47,49,5,5,0,0,48,47,1,0,0,0,48,49,1,0,0,0,49,7,1,0,0,0,50,52,
    3,12,6,0,51,50,1,0,0,0,51,52,1,0,0,0,52,53,1,0,0,0,53,55,5,4,0,0,54,56,
    3,12,6,0,55,54,1,0,0,0,55,56,1,0,0,0,56,58,1,0,0,0,57,59,5,5,0,0,58,57,
    1,0,0,0,58,59,1,0,0,0,59,9,1,0,0,0,60,62,5,4,0,0,61,63,3,12,6,0,62,61,
    1,0,0,0,62,63,1,0,0,0,63,11,1,0,0,0,64,66,5,6,0,0,65,64,1,0,0,0,66,67,
    1,0,0,0,67,65,1,0,0,0,67,68,1,0,0,0,68,13,1,0,0,0,13,17,26,30,34,37,42,
    45,48,51,55,58,62,67
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  iniparserParserStaticData = std::move(staticData);
}

}

IniParser::IniParser(TokenStream *input) : IniParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

IniParser::IniParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  IniParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *iniparserParserStaticData->atn, iniparserParserStaticData->decisionToDFA, iniparserParserStaticData->sharedContextCache, options);
}

IniParser::~IniParser() {
  delete _interpreter;
}

const atn::ATN& IniParser::getATN() const {
  return *iniparserParserStaticData->atn;
}

std::string IniParser::getGrammarFileName() const {
  return "IniParser.g4";
}

const std::vector<std::string>& IniParser::getRuleNames() const {
  return iniparserParserStaticData->ruleNames;
}

const dfa::Vocabulary& IniParser::getVocabulary() const {
  return iniparserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView IniParser::getSerializedATN() const {
  return iniparserParserStaticData->serializedATN;
}


//----------------- IniFileContext ------------------------------------------------------------------

IniParser::IniFileContext::IniFileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IniParser::IniFileContext::EOF() {
  return getToken(IniParser::EOF, 0);
}

std::vector<IniParser::StatementContext *> IniParser::IniFileContext::statement() {
  return getRuleContexts<IniParser::StatementContext>();
}

IniParser::StatementContext* IniParser::IniFileContext::statement(size_t i) {
  return getRuleContext<IniParser::StatementContext>(i);
}


size_t IniParser::IniFileContext::getRuleIndex() const {
  return IniParser::RuleIniFile;
}


std::any IniParser::IniFileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IniParserVisitor*>(visitor))
    return parserVisitor->visitIniFile(this);
  else
    return visitor->visitChildren(this);
}

IniParser::IniFileContext* IniParser::iniFile() {
  IniFileContext *_localctx = _tracker.createInstance<IniFileContext>(_ctx, getState());
  enterRule(_localctx, 0, IniParser::RuleIniFile);
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
    setState(17);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 114) != 0)) {
      setState(14);
      statement();
      setState(19);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(20);
    match(IniParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

IniParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

IniParser::SectionStatementContext* IniParser::StatementContext::sectionStatement() {
  return getRuleContext<IniParser::SectionStatementContext>(0);
}

IniParser::PairStatementContext* IniParser::StatementContext::pairStatement() {
  return getRuleContext<IniParser::PairStatementContext>(0);
}

IniParser::CommentStatementContext* IniParser::StatementContext::commentStatement() {
  return getRuleContext<IniParser::CommentStatementContext>(0);
}

tree::TerminalNode* IniParser::StatementContext::NL() {
  return getToken(IniParser::NL, 0);
}


size_t IniParser::StatementContext::getRuleIndex() const {
  return IniParser::RuleStatement;
}


std::any IniParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IniParserVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

IniParser::StatementContext* IniParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 2, IniParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(26);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(22);
      sectionStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(23);
      pairStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(24);
      commentStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(25);
      match(IniParser::NL);
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

//----------------- SectionStatementContext ------------------------------------------------------------------

IniParser::SectionStatementContext::SectionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IniParser::SectionStatementContext::LBRACK() {
  return getToken(IniParser::LBRACK, 0);
}

tree::TerminalNode* IniParser::SectionStatementContext::RBRACK() {
  return getToken(IniParser::RBRACK, 0);
}

IniParser::CommentContext* IniParser::SectionStatementContext::comment() {
  return getRuleContext<IniParser::CommentContext>(0);
}

tree::TerminalNode* IniParser::SectionStatementContext::NL() {
  return getToken(IniParser::NL, 0);
}

IniParser::TextContext* IniParser::SectionStatementContext::text() {
  return getRuleContext<IniParser::TextContext>(0);
}


size_t IniParser::SectionStatementContext::getRuleIndex() const {
  return IniParser::RuleSectionStatement;
}


std::any IniParser::SectionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IniParserVisitor*>(visitor))
    return parserVisitor->visitSectionStatement(this);
  else
    return visitor->visitChildren(this);
}

IniParser::SectionStatementContext* IniParser::sectionStatement() {
  SectionStatementContext *_localctx = _tracker.createInstance<SectionStatementContext>(_ctx, getState());
  enterRule(_localctx, 4, IniParser::RuleSectionStatement);
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
    setState(28);
    match(IniParser::LBRACK);
    setState(30);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IniParser::TEXT) {
      setState(29);
      antlrcpp::downCast<SectionStatementContext *>(_localctx)->name = text();
    }
    setState(32);
    match(IniParser::RBRACK);
    setState(34);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      setState(33);
      comment();
      break;
    }

    default:
      break;
    }
    setState(37);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      setState(36);
      match(IniParser::NL);
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

//----------------- PairStatementContext ------------------------------------------------------------------

IniParser::PairStatementContext::PairStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IniParser::PairStatementContext::EQUAL() {
  return getToken(IniParser::EQUAL, 0);
}

std::vector<IniParser::TextContext *> IniParser::PairStatementContext::text() {
  return getRuleContexts<IniParser::TextContext>();
}

IniParser::TextContext* IniParser::PairStatementContext::text(size_t i) {
  return getRuleContext<IniParser::TextContext>(i);
}

IniParser::CommentContext* IniParser::PairStatementContext::comment() {
  return getRuleContext<IniParser::CommentContext>(0);
}

tree::TerminalNode* IniParser::PairStatementContext::NL() {
  return getToken(IniParser::NL, 0);
}


size_t IniParser::PairStatementContext::getRuleIndex() const {
  return IniParser::RulePairStatement;
}


std::any IniParser::PairStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IniParserVisitor*>(visitor))
    return parserVisitor->visitPairStatement(this);
  else
    return visitor->visitChildren(this);
}

IniParser::PairStatementContext* IniParser::pairStatement() {
  PairStatementContext *_localctx = _tracker.createInstance<PairStatementContext>(_ctx, getState());
  enterRule(_localctx, 6, IniParser::RulePairStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(39);
    antlrcpp::downCast<PairStatementContext *>(_localctx)->key = text();
    setState(40);
    match(IniParser::EQUAL);
    setState(42);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      setState(41);
      antlrcpp::downCast<PairStatementContext *>(_localctx)->value = text();
      break;
    }

    default:
      break;
    }
    setState(45);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      setState(44);
      comment();
      break;
    }

    default:
      break;
    }
    setState(48);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      setState(47);
      match(IniParser::NL);
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

//----------------- CommentStatementContext ------------------------------------------------------------------

IniParser::CommentStatementContext::CommentStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IniParser::CommentStatementContext::SEMI() {
  return getToken(IniParser::SEMI, 0);
}

std::vector<IniParser::TextContext *> IniParser::CommentStatementContext::text() {
  return getRuleContexts<IniParser::TextContext>();
}

IniParser::TextContext* IniParser::CommentStatementContext::text(size_t i) {
  return getRuleContext<IniParser::TextContext>(i);
}

tree::TerminalNode* IniParser::CommentStatementContext::NL() {
  return getToken(IniParser::NL, 0);
}


size_t IniParser::CommentStatementContext::getRuleIndex() const {
  return IniParser::RuleCommentStatement;
}


std::any IniParser::CommentStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IniParserVisitor*>(visitor))
    return parserVisitor->visitCommentStatement(this);
  else
    return visitor->visitChildren(this);
}

IniParser::CommentStatementContext* IniParser::commentStatement() {
  CommentStatementContext *_localctx = _tracker.createInstance<CommentStatementContext>(_ctx, getState());
  enterRule(_localctx, 8, IniParser::RuleCommentStatement);
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
    setState(51);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == IniParser::TEXT) {
      setState(50);
      text();
    }
    setState(53);
    match(IniParser::SEMI);
    setState(55);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      setState(54);
      text();
      break;
    }

    default:
      break;
    }
    setState(58);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      setState(57);
      match(IniParser::NL);
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

//----------------- CommentContext ------------------------------------------------------------------

IniParser::CommentContext::CommentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* IniParser::CommentContext::SEMI() {
  return getToken(IniParser::SEMI, 0);
}

IniParser::TextContext* IniParser::CommentContext::text() {
  return getRuleContext<IniParser::TextContext>(0);
}


size_t IniParser::CommentContext::getRuleIndex() const {
  return IniParser::RuleComment;
}


std::any IniParser::CommentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IniParserVisitor*>(visitor))
    return parserVisitor->visitComment(this);
  else
    return visitor->visitChildren(this);
}

IniParser::CommentContext* IniParser::comment() {
  CommentContext *_localctx = _tracker.createInstance<CommentContext>(_ctx, getState());
  enterRule(_localctx, 10, IniParser::RuleComment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(60);
    match(IniParser::SEMI);
    setState(62);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      setState(61);
      text();
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

//----------------- TextContext ------------------------------------------------------------------

IniParser::TextContext::TextContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> IniParser::TextContext::TEXT() {
  return getTokens(IniParser::TEXT);
}

tree::TerminalNode* IniParser::TextContext::TEXT(size_t i) {
  return getToken(IniParser::TEXT, i);
}


size_t IniParser::TextContext::getRuleIndex() const {
  return IniParser::RuleText;
}


std::any IniParser::TextContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<IniParserVisitor*>(visitor))
    return parserVisitor->visitText(this);
  else
    return visitor->visitChildren(this);
}

IniParser::TextContext* IniParser::text() {
  TextContext *_localctx = _tracker.createInstance<TextContext>(_ctx, getState());
  enterRule(_localctx, 12, IniParser::RuleText);

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
    setState(65); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(64);
              match(IniParser::TEXT);
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(67); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void IniParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  iniparserParserInitialize();
#else
  ::antlr4::internal::call_once(iniparserParserOnceFlag, iniparserParserInitialize);
#endif
}
