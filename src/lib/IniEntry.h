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

#ifndef _INIENTRY_H_
#define _INIENTRY_H_

#include "IElementCommon.h"
#include <iostream>
#include <memory>
#include <string>

namespace net
{
    namespace derpaul
    {
        namespace yaip
        {
            class IIniVisitor;

            class IniEntry : public IElementCommon
            {
            public:
                IniEntry(void);

                virtual ~IniEntry(void);

                virtual void clear(void) override;

                virtual std::string ElementCommentGet(void) const override;

                virtual void ElementCommentSet(const std::string &ElementComment) override;

                virtual std::string ElementIdentifierGet(void) const override;

                virtual void ElementIdentifierSet(const std::string &ElementIdentifier) override;

                virtual std::string ElementValueGet(void) const;

                virtual void ElementValueSet(const std::string &ElementValue);

                std::string to_string(void) const override;

                void Accept(IIniVisitor &visitor) const;

            private:
                std::string m_EntryComment;

                std::string m_EntryKey;

                std::string m_EntryValue;
            };

            using IniEntryPtr = std::shared_ptr<IniEntry>;

            bool IniEntryCompare(const IniEntryPtr Left, const IniEntryPtr Right);
        }
    }
}

#endif
