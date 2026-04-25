//******************************************************************************
// Copyright 2016 ThirtySomething
//******************************************************************************
// This file is part of YAIP.
//
// YAIP is free software: you can redistribute it and/or modify it under the
// terms of the GNU Lesser General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// YAIP is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
// more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with YAIP. If not, see <http://www.gnu.org/licenses/>.
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

#endif
