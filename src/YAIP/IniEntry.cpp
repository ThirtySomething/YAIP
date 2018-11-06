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
			const std::regex IniEntry::RegExKeyValue("\\s*([^=]+)\\s*=\\s*([^;]+);?(.+)?");

			// ******************************************************************
			// ******************************************************************
			IniEntry::IniEntry()
				: m_EntryKey()
				, m_EntryValue()
				, m_EntryComment()
			{
			}

			// ******************************************************************
			// ******************************************************************
			IniEntry::~IniEntry()
			{
			}

			// ******************************************************************
			// ******************************************************************
			void IniEntry::EntryKeySet(const std::string &EntryKey)
			{
				m_EntryKey = EntryKey;
			}

			// ******************************************************************
			// ******************************************************************
			std::string IniEntry::EntryKeyGet(void)
			{
				return m_EntryKey;
			}

			// ******************************************************************
			// ******************************************************************
			void IniEntry::EntryValueSet(const std::string &EntryValue)
			{
				m_EntryValue = EntryValue;
			}

			// ******************************************************************
			// ******************************************************************
			std::string IniEntry::EntryValueGet(void)
			{
				return m_EntryValue;
			}

			// ******************************************************************
			// ******************************************************************
			void IniEntry::EntryCommentSet(const std::string &EntryComment)
			{
				m_EntryComment = EntryComment;
			}

			// ******************************************************************
			// ******************************************************************
			std::string IniEntry::EntryCommentGet(void)
			{
				return m_EntryComment;
			}

			// ******************************************************************
			// ******************************************************************
			bool IniEntry::EntryDataParse(const std::string &EntryData)
			{
				bool Success = false;
				std::smatch RegExpMatch;

				// Check for match
				if (std::regex_search(EntryData, RegExpMatch, RegExKeyValue))
				{
					// Change new key/value pair only in case of a match.
					// Unfortunately in C++ there are no named groups possible
					// so we have to use the index of the group.
					EntryKeySet(RegExpMatch[1]);
					EntryValueSet(RegExpMatch[2]);
					EntryCommentSet(RegExpMatch[3]);
					Success = true;
				}

				return Success;
			}

			// ******************************************************************
			// ******************************************************************
			std::string IniEntry::to_string(void)
			{
				std::ostringstream tmpStream;
				tmpStream << m_EntryKey << "=" << m_EntryValue;

				if (!m_EntryComment.empty())
				{
					tmpStream << " ; " << m_EntryComment;
				}

				return tmpStream.str();
			}

			// ******************************************************************
			// ******************************************************************
			std::ostream& operator<<(std::ostream &OutputStream, const IniEntry &EntryObject)
			{
				return OutputStream;
			}
		}
	}
}
