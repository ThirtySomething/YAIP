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

/**
 * \file	IniSection.cpp
 * \author	ThirtySomething
 * \date	2016-09-19
 * \brief	Definition of IniSection as class to deal with sections
 */

#include "IniSection.h"
#include "IIniVisitor.h"
#include "string_extensions.h"
#include <iostream>
#include <sstream>

/**
 * Namespace of YAIP
 */
namespace net
{
    /**
     * Namespace of YAIP
     */
    namespace derpaul
    {
        /**
         * Namespace of YAIP
         */
        namespace yaip
        {
            // ******************************************************************
            // ******************************************************************
            IniSection::IniSection(void)
                : m_SectionName(), m_SectionComment(), m_Entries()
            {
            }

            // ******************************************************************
            // ******************************************************************
            IniSection::~IniSection(void)
            {
            }

            // ******************************************************************
            // ******************************************************************
            void IniSection::clear(void)
            {
                ElementIdentifierSet("");
                ElementCommentSet("");
                m_Entries.clear();
            }

            // ******************************************************************
            // ******************************************************************
            std::string IniSection::ElementCommentGet(void) const
            {
                return m_SectionComment;
            }

            // ******************************************************************
            // ******************************************************************
            void IniSection::ElementCommentSet(const std::string &ElementComment)
            {
                m_SectionComment = trim(ElementComment);
            }

            // ******************************************************************
            // ******************************************************************
            std::string IniSection::ElementIdentifierGet(void) const
            {
                return m_SectionName;
            }

            // ******************************************************************
            // ******************************************************************
            void IniSection::ElementIdentifierSet(const std::string &ElementIdentifier)
            {
                m_SectionName = trim(ElementIdentifier);
            }

            // ******************************************************************
            // ******************************************************************
            void IniSection::EntryAdd(const IniEntryPtr &Entry)
            {
                m_Entries.ElementAdd(Entry);
            }

            // ******************************************************************
            // ******************************************************************
            void IniSection::EntryDelete(const IniEntryPtr &Entry)
            {
                m_Entries.ElementDelete(Entry);
            }

            // ******************************************************************
            // ******************************************************************
            IniEntryPtr IniSection::EntryFind(const std::string &EntryName)
            {
                return m_Entries.ElementFind(EntryName);
            }

            // ******************************************************************
            // ******************************************************************
            tListString IniSection::EntryKeyList(void) const
            {
                return m_Entries.ElementIdentifierList();
            }

            // ******************************************************************
            // ******************************************************************
            bool IniSection::IsEmpty(void) const
            {
                return (0 == m_Entries.size());
            }

            // ******************************************************************
            // ******************************************************************
            IniEntryList IniSection::SectionEntriesGet(void) const
            {
                return m_Entries;
            }

            // ******************************************************************
            // ******************************************************************
            void IniSection::SectionEntriesSet(const IniEntryList &SectionEntries)
            {
                m_Entries = SectionEntries;
            }

            // ******************************************************************
            // ******************************************************************
            std::string IniSection::to_string(void) const
            {
                std::ostringstream DataStream;

                DataStream << "[" << m_SectionName << "]";
                if (!m_SectionComment.empty())
                {
                    DataStream << " ; " << m_SectionComment;
                }
                DataStream << std::endl;
                DataStream << m_Entries.to_string();
                DataStream << std::endl;

                return DataStream.str();
            }

            // ******************************************************************
            // ******************************************************************
            void IniSection::Accept(IIniVisitor &visitor) const
            {
                visitor.VisitSectionBegin(*this);

                IniEntryList entries = SectionEntriesGet();
                for (const auto &key : entries.ElementIdentifierList())
                {
                    if (auto entry = entries.ElementFind(key); entry != nullptr)
                    {
                        entry->Accept(visitor);
                    }
                }

                visitor.VisitSectionEnd(*this);
            }

            // ******************************************************************
            // ******************************************************************
            void IniSection::sort(void)
            {
                m_Entries.sort();
            }

            // ******************************************************************
            // ******************************************************************
            bool IniSectionCompare(const IniSectionPtr Left, const IniSectionPtr Right)
            {
                return strcmpcaseless(Left->ElementIdentifierGet(), Right->ElementIdentifierGet());
            }
        }
    }
}
