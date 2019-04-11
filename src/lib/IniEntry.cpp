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
 * \file	IniEntry.cpp
 * \author	ThirtySomething
 * \date	2016-11-06
 * \brief	Definition of IniEntry as class to deal with entries
 */

#include "IniEntry.h"
#include "string_extensions.h"
#include <sstream>
#include <iostream>

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
			// Regular expression mask for matching a section
			const std::regex IniEntry::RegExKeyValue("\\s*([^=]+)\\s*=\\s*([^;]+);?(.+)?");

			// Index of entry comment in regular expression
			const int IniEntry::IndexEntryComment = 3;

			// Index of entry key in regular expression
			const int IniEntry::IndexEntryKey = 1;

			// Index of entry value in regular expression
			const int IniEntry::IndexEntryValue = 2;

			// ******************************************************************
			// ******************************************************************
			IniEntry::IniEntry(void)
				: m_EntryKey()
				, m_EntryValue()
				, m_EntryComment()
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
			bool IniEntry::CreateFromRawData(const std::string &RawData)
			{
				bool Success = false;
				std::smatch RegExpMatch;

				// Check for match
				if (std::regex_search(RawData, RegExpMatch, RegExKeyValue))
				{
					// Change new key/value pair only in case of a match.
					// Unfortunately in C++ there are no named groups possible
					// so we have to use the index of the group.
					ElementIdentifierSet(RegExpMatch[IndexEntryKey]);
					ElementValueSet(RegExpMatch[IndexEntryValue]);
					ElementCommentSet(RegExpMatch[IndexEntryComment]);
					Success = true;
				}

				return Success;
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
			bool IniEntryCompare(const IniEntryPtr Left, const IniEntryPtr Right)
			{
				return strcmpcaseless(Left->ElementIdentifierGet(), Right->ElementIdentifierGet());
			}
		}
	}
}
