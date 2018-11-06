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
 * \file	IniSection.h
 * \author	ThirtySomething
 * \date	2016-09-19
 * \brief	Definition of IniSection as class to deal with sections
 */
#pragma once

#include "IniEntry.h"
#include <iostream>
#include <memory>
#include <regex>
#include <string>

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
			typedef std::vector<IniEntryPtr> tEntryList;

			class IniSection
			{
			public:
				IniSection(void);
				virtual ~IniSection(void);

				void SectionNameSet(const std::string &SectionName);
				std::string SectionNameGet(void);

				void SectionCommentSet(const std::string &SectionComment);
				std::string SectionCommentGet(void);

				void SectionEntriesSet(const tEntryList &SectionEntries);
				tEntryList SectionEntriesGet(void);

				bool SectionDataParse(const std::string &SectionData);

				bool AddRawEntry(const std::string &RawEntryData);

				std::string to_string(void);

			private:
				/**
				 * Section - Regular expression
				 */
				static const std::regex RegExSection;

				std::string m_SectionName;

				std::string m_SectionComment;

				/**
				 * All entries to this section
				 */
				tEntryList m_SectionEntries;

				friend std::ostream& operator<<(std::ostream &OutputStream, const IniSection &SectionObject);
			};

			typedef std::shared_ptr<IniSection> IniSectionPtr;
		}
	}
}
