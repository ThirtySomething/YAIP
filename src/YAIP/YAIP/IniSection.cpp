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
			void IniSection::ElementIdentifierSet(const std::string &ElementIdentifier)
			{
				m_SectionName = std::trim(ElementIdentifier);
			}

			// ******************************************************************
			// ******************************************************************
			std::string IniSection::ElementIdentifierGet(void)
			{
				return m_SectionName;
			}

			// ******************************************************************
			// ******************************************************************
			void IniSection::ElementCommentSet(const std::string &ElementComment)
			{
				m_SectionComment = std::trim(ElementComment);
			}

			// ******************************************************************
			// ******************************************************************
			std::string IniSection::ElementCommentGet(void)
			{
				return m_SectionComment;
			}

			// ******************************************************************
			// ******************************************************************
			void IniSection::SectionEntriesSet(const IniEntryList &SectionEntries)
			{
				m_Entries = SectionEntries;
			}

			// ******************************************************************
			// ******************************************************************
			IniEntryList IniSection::SectionEntriesGet(void) const
			{
				return m_Entries;
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
					ElementIdentifierSet(RegExpMatch[1]);
					ElementCommentSet(RegExpMatch[3]);
					Success = true;
				}

				return Success;
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
			IniEntryPtr IniSection::EntryFind(const std::string &EntryName)
			{
				return m_Entries.ElementFind(EntryName);
			}

			// ******************************************************************
			// ******************************************************************
			void IniSection::EntryDelete(const IniEntryPtr &Entry)
			{
				m_Entries.ElementDelete(Entry);
			}

			// ******************************************************************
			// ******************************************************************
			tListString IniSection::EntryKeyList(void)
			{
				return m_Entries.ElementIdentifierList();
			}

			// ******************************************************************
			// ******************************************************************
			bool IniSection::IsEmpty(void)
			{
				return (0 == m_Entries.size());
			}

			// ******************************************************************
			// ******************************************************************
			void IniSection::EntryAdd(const IniEntryPtr &Entry)
			{
				m_Entries.ElementAdd(Entry);
			}

			// ******************************************************************
			// ******************************************************************
			std::string IniSection::to_string(void) const
			{
				std::ostringstream tmpStream;
				tmpStream << "[" << m_SectionName << "]";

				if (!m_SectionComment.empty())
				{
					tmpStream << " ; " << m_SectionComment;
				}

				return tmpStream.str();
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
			std::ostream& operator<<(std::ostream &OutputStream, const IniSection &SectionObject)
			{
				return OutputStream;
			}
		}
	}
}
