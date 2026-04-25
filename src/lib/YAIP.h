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

#ifndef _YAIP_H_
#define _YAIP_H_

#include "Convert.h"
#include "IIniParserStrategy.h"
#include "IniSection.h"
#include "IniSectionList.h"
#include <functional>
#include <map>
#include <memory>
#include <vector>

namespace net
{
    namespace derpaul
    {
        namespace yaip
        {
            class IIniVisitor;

            class YAIP
            {
            public:
                YAIP(void);
                virtual ~YAIP(void);

                void Clear(void);

                static bool INIFileDelete(const std::string &Filename);
                static bool INIFileExist(const std::string &Filename);
                bool INIFileLoad(const std::string &Filename);
                bool INIFileSave(const std::string &Filename);

                bool SectionKeyKill(const std::string &Section, const std::string &Key);
                tListString SectionKeyListGet(const std::string &Section);
                bool SectionKeyValueClear(const std::string &Section, const std::string &Key);
                std::string SectionKeyValueGet(const std::string &Section, const std::string &Key, const std::string &Default);

                template <typename VariableType>
                VariableType SectionKeyValueGet(const std::string &Section, const std::string &Key, const VariableType &Default)
                {
                    VariableType ValueReturn;
                    std::string ValueDefault;
                    Convert::ConvertTo(Default, ValueDefault);
                    std::string ValueRaw = SectionKeyValueGet(Section, Key, ValueDefault);
                    Convert::ConvertTo(ValueRaw, ValueReturn);
                    return ValueReturn;
                }

                bool SectionKeyValueSet(const std::string &Section, const std::string &Key, const std::string &Value);
                bool SectionKeyValueSet(const std::string &Section, const std::string &Key, const char *Value);

                template <typename VariableType>
                bool SectionKeyValueSet(const std::string &Section, const std::string &Key, const VariableType &Value)
                {
                    std::string ValueString;
                    Convert::ConvertTo(Value, ValueString);
                    return SectionKeyValueSet(Section, Key, ValueString);
                }

                tListString SectionListGet(void);
                std::string to_string(void) const;
                void Accept(IIniVisitor &visitor) const;

            protected:
                IniSectionList m_Sections;
                bool ParseFileContent(tListString FileContent);
                std::unique_ptr<IIniParserStrategy> m_ParserStrategy;
            };
        }
    }
}

#endif
