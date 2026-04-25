//******************************************************************************
// Copyright 2016 ThirtySomething
//******************************************************************************

#include "ParseErrorListener.h"

namespace net
{
    namespace derpaul
    {
        namespace yaip
        {
            namespace detail
            {
                ParseErrorListener::ParseErrorListener() : m_HadError(false)
                {
                }

                void ParseErrorListener::syntaxError(antlr4::Recognizer *, antlr4::Token *, size_t, size_t, const std::string &, std::exception_ptr)
                {
                    m_HadError = true;
                }

                bool ParseErrorListener::HadError() const
                {
                    return m_HadError;
                }
            }
        }
    }
}