
// Generated from D:\Workspaces\GitHub\YAIP\Hello.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "HelloVisitor.h"


/**
 * This class provides an empty implementation of HelloVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  HelloBaseVisitor : public HelloVisitor {
public:

  virtual std::any visitR(HelloParser::RContext *ctx) override {
    return visitChildren(ctx);
  }


};

