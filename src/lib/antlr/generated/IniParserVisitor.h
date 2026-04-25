
// Generated from /home/jochen/workdir/YAIP/src/lib/antlr/IniParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "IniParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by IniParser.
 */
class  IniParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by IniParser.
   */
    virtual std::any visitIniFile(IniParser::IniFileContext *context) = 0;

    virtual std::any visitStatement(IniParser::StatementContext *context) = 0;

    virtual std::any visitSectionStatement(IniParser::SectionStatementContext *context) = 0;

    virtual std::any visitPairStatement(IniParser::PairStatementContext *context) = 0;

    virtual std::any visitCommentStatement(IniParser::CommentStatementContext *context) = 0;

    virtual std::any visitComment(IniParser::CommentContext *context) = 0;

    virtual std::any visitText(IniParser::TextContext *context) = 0;


};

