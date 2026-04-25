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

#include "IniDocumentBuilder.h"

#include "IniEntry.h"
#include "YAIP.h"
#include <algorithm>
#include <memory>

namespace net
{
    namespace derpaul
    {
        namespace yaip
        {
            IniDocumentBuilder &IniDocumentBuilder::section(const std::string &name)
            {
                auto it = std::find_if(m_Sections.begin(), m_Sections.end(),
                                       [&](const IniSectionPtr &s)
                                       { return s->ElementIdentifierGet() == name; });
                if (it != m_Sections.end())
                {

                    IniSectionPtr reused = std::move(*it);
                    m_Sections.erase(it);
                    m_Sections.push_back(std::move(reused));
                }
                else
                {
                    auto sec = std::make_shared<IniSection>();
                    sec->ElementIdentifierSet(name);
                    m_Sections.push_back(std::move(sec));
                }
                return *this;
            }

            IniDocumentBuilder &IniDocumentBuilder::entry(const std::string &key, const char *value)
            {
                return entry(key, value ? std::string(value) : std::string{});
            }

            IniDocumentBuilder &IniDocumentBuilder::entry(const std::string &key, const std::string &value)
            {
                if (m_Sections.empty())
                {

                    auto unnamed = std::make_shared<IniSection>();
                    unnamed->ElementIdentifierSet("");
                    m_Sections.push_back(std::move(unnamed));
                }
                auto e = std::make_shared<IniEntry>();
                e->ElementIdentifierSet(key);
                e->ElementValueSet(value);
                m_Sections.back()->EntryAdd(e);
                return *this;
            }

            void IniDocumentBuilder::build(YAIP &target) const
            {
                target.Clear();
                for (const auto &sec : m_Sections)
                {
                    const std::string sectionName = sec->ElementIdentifierGet();
                    for (const auto &key : sec->EntryKeyList())
                    {
                        if (auto e = sec->EntryFind(key); e != nullptr)
                        {
                            target.SectionKeyValueSet(sectionName, key, e->ElementValueGet());
                        }
                    }
                }
            }
        }
    }
}
