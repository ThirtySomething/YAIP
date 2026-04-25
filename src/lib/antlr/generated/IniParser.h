
// Generated from /home/jochen/workdir/YAIP/src/lib/antlr/IniParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  IniParser : public antlr4::Parser {
public:
  enum {
    LBRACK = 1, RBRACK = 2, EQUAL = 3, SEMI = 4, NL = 5, TEXT = 6
  };

  enum {
    RuleIniFile = 0, RuleStatement = 1, RuleSectionStatement = 2, RulePairStatement = 3, 
    RuleCommentStatement = 4, RuleComment = 5, RuleText = 6
  };

  explicit IniParser(antlr4::TokenStream *input);

  IniParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~IniParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class IniFileContext;
  class StatementContext;
  class SectionStatementContext;
  class PairStatementContext;
  class CommentStatementContext;
  class CommentContext;
  class TextContext; 

  class  IniFileContext : public antlr4::ParserRuleContext {
  public:
    IniFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IniFileContext* iniFile();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SectionStatementContext *sectionStatement();
    PairStatementContext *pairStatement();
    CommentStatementContext *commentStatement();
    antlr4::tree::TerminalNode *NL();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  SectionStatementContext : public antlr4::ParserRuleContext {
  public:
    IniParser::TextContext *name = nullptr;
    SectionStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACK();
    antlr4::tree::TerminalNode *RBRACK();
    CommentContext *comment();
    antlr4::tree::TerminalNode *NL();
    TextContext *text();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SectionStatementContext* sectionStatement();

  class  PairStatementContext : public antlr4::ParserRuleContext {
  public:
    IniParser::TextContext *key = nullptr;
    IniParser::TextContext *value = nullptr;
    PairStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EQUAL();
    std::vector<TextContext *> text();
    TextContext* text(size_t i);
    CommentContext *comment();
    antlr4::tree::TerminalNode *NL();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PairStatementContext* pairStatement();

  class  CommentStatementContext : public antlr4::ParserRuleContext {
  public:
    CommentStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMI();
    std::vector<TextContext *> text();
    TextContext* text(size_t i);
    antlr4::tree::TerminalNode *NL();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CommentStatementContext* commentStatement();

  class  CommentContext : public antlr4::ParserRuleContext {
  public:
    CommentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMI();
    TextContext *text();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CommentContext* comment();

  class  TextContext : public antlr4::ParserRuleContext {
  public:
    TextContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> TEXT();
    antlr4::tree::TerminalNode* TEXT(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TextContext* text();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

