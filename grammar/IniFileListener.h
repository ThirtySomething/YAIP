
// Generated from IniFile.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "IniFileParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by IniFileParser.
 */
class  IniFileListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterR(IniFileParser::RContext *ctx) = 0;
  virtual void exitR(IniFileParser::RContext *ctx) = 0;


};

