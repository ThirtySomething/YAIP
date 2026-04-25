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
 * \file    IniEntry.cpp
 * \author  ThirtySomething
 * \date    2016-11-06
 * \brief   Definition of IniEntry as class to deal with entries
 */

#include "IniEntry.h"
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
            IniEntry::IniEntry(void)
                : m_EntryKey(), m_EntryValue(), m_EntryComment()
            {
            }

            // ******************************************************************
            // ******************************************************************
            IniEntry::~IniEntry(void)
            {
            }

            // ******************************************************************
            // ******************************************************************
            void IniEntry::clear(void)
            {
                ElementIdentifierSet("");
                ElementCommentSet("");
                ElementValueSet("");
            }

            // ******************************************************************
            // ******************************************************************
            std::string IniEntry::ElementCommentGet(void) const
            {
                return m_EntryComment;
            }

            // ******************************************************************
            // ******************************************************************
            void IniEntry::ElementCommentSet(const std::string &ElementComment)
            {
                m_EntryComment = trim(ElementComment);
            }

            // ******************************************************************
            // ******************************************************************
            std::string IniEntry::ElementIdentifierGet(void) const
            {
                return m_EntryKey;
            }

            // ******************************************************************
            // ******************************************************************
            void IniEntry::ElementIdentifierSet(const std::string &ElementIdentifier)
            {
                m_EntryKey = trim(ElementIdentifier);
            }

            // ******************************************************************
            // ******************************************************************
            std::string IniEntry::ElementValueGet(void) const
            {
                return m_EntryValue;
            }

            // ******************************************************************
            // ******************************************************************
            void IniEntry::ElementValueSet(const std::string &ElementValue)
            {
                m_EntryValue = trim(ElementValue);
            }

            // ******************************************************************
            // ******************************************************************
            std::string IniEntry::to_string(void) const
            {
                std::ostringstream DataStream;
                DataStream << m_EntryKey << " = " << m_EntryValue;

                if (!m_EntryComment.empty())
                {
                    DataStream << " ; " << m_EntryComment;
                }
                DataStream << std::endl;

                return DataStream.str();
            }

            // ******************************************************************
            // ******************************************************************
            void IniEntry::Accept(IIniVisitor &visitor) const
            {
                visitor.VisitEntry(*this);
            }

            // ******************************************************************
            // ******************************************************************
            bool IniEntryCompare(const IniEntryPtr Left, const IniEntryPtr Right)
            {
                return strcmpcaseless(Left->ElementIdentifierGet(), Right->ElementIdentifierGet());
            }
        }
    }
}
