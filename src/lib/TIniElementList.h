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

#ifndef _TINIELEMENTLIST_H_
#define _TINIELEMENTLIST_H_

#include "string_extensions.h"
#include <algorithm>
#include <list>
#include <sstream>
#include <string>
#include <vector>

namespace net
{
    namespace derpaul
    {
        namespace yaip
        {
            using tListString = std::list<std::string>;

            template <typename TIniElement>
            class TIniElementList
            {
            public:
                TIniElementList(void)
                    : m_Elements()
                {
                }

                virtual ~TIniElementList(void)
                {
                    clear();
                }

                void clear(void)
                {
                    m_Elements.clear();
                }

                void ElementAdd(const TIniElement &Element)
                {
                    m_Elements.push_back(Element);
                }

                void ElementDelete(const TIniElement &Element)
                {
                    m_Elements.erase(
                        std::remove_if(
                            m_Elements.begin(),
                            m_Elements.end(),
                            [&Element](const TIniElement &obj)
                            { return obj->ElementIdentifierGet() == Element->ElementIdentifierGet(); }),
                        m_Elements.end());
                }

                TIniElement ElementFind(const std::string &ElementName)
                {
                    std::string ElementNameWork = trim(ElementName);
                    TIniElement Element = nullptr;

                    auto it = std::find_if(m_Elements.begin(), m_Elements.end(), [&ElementNameWork](const TIniElement &obj)
                                           { return obj->ElementIdentifierGet() == ElementNameWork; });
                    if (it != m_Elements.end())
                    {
                        Element = *it;
                    }

                    return Element;
                }

                tListString ElementIdentifierList(void) const
                {
                    tListString List;

                    for (auto CurrentElementPtr = m_Elements.begin(); CurrentElementPtr != m_Elements.end(); ++CurrentElementPtr)
                    {
                        List.push_back((*CurrentElementPtr)->ElementIdentifierGet());
                    }

                    return List;
                }

                int size(void) const
                {
                    return static_cast<int>(m_Elements.size());
                }

                std::string to_string(void) const
                {
                    std::ostringstream tmpStream;

                    for (auto CurrentElementPtr = m_Elements.begin(); CurrentElementPtr != m_Elements.end(); ++CurrentElementPtr)
                    {
                        tmpStream << (*CurrentElementPtr)->to_string();
                    }

                    return tmpStream.str();
                }

                virtual void sort(void) = 0;

            protected:
                std::vector<TIniElement> m_Elements;
            };
        }
    }
}

#endif
