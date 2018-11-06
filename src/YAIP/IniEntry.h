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
 * \file	IniEntry.h
 * \author	ThirtySomething
 * \date	2016-11-06
 * \brief	Definition of IniEntry as class to deal with entries
 */
#pragma once

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
			class IniEntry
			{
			public:
				IniEntry(void);
				virtual ~IniEntry(void);

				void EntryKeySet(const std::string &EntryKey);
				std::string EntryKeyGet(void);

				void EntryValueSet(const std::string &EntryValue);
				std::string EntryValueGet(void);

				void EntryCommentSet(const std::string &EntryComment);
				std::string EntryCommentGet(void);

				bool EntryDataParse(const std::string &EntryData);

				std::string to_string(void);

			private:
				/**
				 * Section - Regular expression
				 */
				static const std::regex RegExKeyValue;

				std::string m_EntryKey;
				std::string m_EntryValue;
				std::string m_EntryComment;

				friend std::ostream& operator<<(std::ostream &OutputStream, const IniEntry &EntryObject);
			};

			typedef std::shared_ptr<IniEntry> IniEntryPtr;
		}
	}
}
