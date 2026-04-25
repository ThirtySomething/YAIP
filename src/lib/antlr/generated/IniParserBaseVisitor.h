
// Generated from /home/jochen/workdir/YAIP/src/lib/antlr/IniParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "IniParserVisitor.h"


/**
 * This class provides an empty implementation of IniParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  IniParserBaseVisitor : public IniParserVisitor {
public:

  virtual std::any visitIniFile(IniParser::IniFileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(IniParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSectionStatement(IniParser::SectionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPairStatement(IniParser::PairStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCommentStatement(IniParser::CommentStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComment(IniParser::CommentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitText(IniParser::TextContext *ctx) override {
    return visitChildren(ctx);
  }


};

