//******************************************************************************
// Copyright 2016 ThirtySomething
//******************************************************************************

#ifndef _PARSEERRORLISTENER_H_
#define _PARSEERRORLISTENER_H_

#include "antlr4-runtime.h"

namespace net
{
    namespace derpaul
    {
        namespace yaip
        {
            namespace detail
            {
                class ParseErrorListener : public antlr4::BaseErrorListener
                {
                public:
                    ParseErrorListener();

                    void syntaxError(antlr4::Recognizer *recognizer,
                                     antlr4::Token *offendingSymbol,
                                     size_t line,
                                     size_t charPositionInLine,
                                     const std::string &msg,
                                     std::exception_ptr e) override;

                    bool HadError() const;

                private:
                    bool m_HadError;
                };
            }
        }
    }
}

#endif