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

#ifndef _INIDOCUMENTBUILDER_H_
#define _INIDOCUMENTBUILDER_H_

#include "Convert.h"
#include "IniSection.h"
#include <memory>
#include <string>
#include <vector>

namespace net
{
    namespace derpaul
    {
        namespace yaip
        {
            class YAIP;

            class IniDocumentBuilder
            {
            public:
                IniDocumentBuilder &section(const std::string &name);
                IniDocumentBuilder &entry(const std::string &key, const std::string &value);
                IniDocumentBuilder &entry(const std::string &key, const char *value);

                template <typename T>
                IniDocumentBuilder &entry(const std::string &key, const T &value)
                {
                    std::string converted;
                    Convert::ConvertTo(value, converted);
                    return entry(key, converted);
                }

                void build(YAIP &target) const;

            private:
                std::vector<IniSectionPtr> m_Sections;
            };
        }
    }
}

#endif
