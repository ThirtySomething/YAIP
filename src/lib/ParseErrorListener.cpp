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
