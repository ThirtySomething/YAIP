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
			const std::regex IniSection::RegExSection("\\s*\\[\\s*([^\\]]+)\\]\\s*(;(.+))?");

			// Index of section comment in regular expression
			const int IniSection::IndexSectionComment = 3;

			// Index of section key in regular expression
			const int IniSection::IndexSectionKey = 1;

			// ******************************************************************
			// ******************************************************************
			IniSection::IniSection(void)
				: m_SectionName()
				, m_SectionComment()
				, m_Entries()
			{
			}

			// ******************************************************************
			// ******************************************************************
			IniSection::~IniSection(void)
			{
			}

			// ******************************************************************
			// ******************************************************************
			bool IniSection::AddRawEntry(const std::string &RawEntryData)
			{
				bool Success = false;
				IniEntryPtr EntryPtr(new IniEntry);

				if (EntryPtr->CreateFromRawData(RawEntryData))
				{
					m_Entries.ElementAdd(EntryPtr);
					Success = true;
				}

				return Success;
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
			bool IniSection::CreateFromRawData(const std::string &RawData)
			{
				bool Success = false;
				std::smatch RegExpMatch;

				// Check for match
				if (std::regex_search(RawData, RegExpMatch, RegExSection))
				{
					// Change section only in case of a match.
					// Unfortunately in C++ there are no named groups possible
					// so we have to use the index of the group.
					ElementIdentifierSet(RegExpMatch[IndexSectionKey]);
					ElementCommentSet(RegExpMatch[IndexSectionComment]);
					Success = true;
				}

				return Success;
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
