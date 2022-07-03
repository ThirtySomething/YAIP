
// Generated from IniFile.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "IniFileListener.h"


/**
 * This class provides an empty implementation of IniFileListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  IniFileBaseListener : public IniFileListener {
public:

  virtual void enterR(IniFileParser::RContext * /*ctx*/) override { }
  virtual void exitR(IniFileParser::RContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

