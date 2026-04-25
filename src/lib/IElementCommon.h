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

#ifndef _IELEMENTCOMMON_H_
#define _IELEMENTCOMMON_H_

#include "string_extensions.h"
#include <string>

namespace net
{
    namespace derpaul
    {
        namespace yaip
        {
            class IElementCommon
            {
            public:
                virtual void clear(void) = 0;

                virtual std::string ElementCommentGet(void) const = 0;

                virtual void ElementCommentSet(const std::string &ElementComment) = 0;

                virtual std::string ElementIdentifierGet(void) const = 0;

                virtual void ElementIdentifierSet(const std::string &ElementIdentifier) = 0;

                virtual std::string to_string(void) const = 0;
            };
        }
    }
}

#endif
