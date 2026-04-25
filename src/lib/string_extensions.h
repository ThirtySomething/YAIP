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

#ifndef _STRING_EXTENSIONS_H_
#define _STRING_EXTENSIONS_H_

#include <string>

namespace net
{
    namespace derpaul
    {
        namespace yaip
        {
            const std::string WHITESPACE = " \n\r\t\f\v";

            std::string ltrim(const std::string &in);

            std::string rtrim(const std::string &in);

            bool strcmpcaseless(const std::string &left, const std::string &right);

            std::string trim(const std::string &in);
        }
    }
}

#endif
