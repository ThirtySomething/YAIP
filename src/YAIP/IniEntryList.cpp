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
 * \file	IniEntryList.cpp
 * \author	ThirtySomething
 * \date	2016-09-19
 * \brief	List of INI entries
 */

#include "IniEntryList.h"
#include <algorithm>

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
			IniEntryList::IniEntryList(void)
				: m_Entries()
			{
			}

			// ******************************************************************
			// ******************************************************************
			IniEntryList::~IniEntryList(void)
			{
				clear();
			}

			// ******************************************************************
			// ******************************************************************
			void IniEntryList::clear(void)
			{
				m_Entries.clear();
			}

			// ******************************************************************
			// ******************************************************************
			void IniEntryList::EntryAdd(const IniEntryPtr &Section)
			{
				m_Entries.push_back(Section);
			}

			// ******************************************************************
			// ******************************************************************
			void IniEntryList::EntryDelete(const IniEntryPtr &Entry)
			{
				
				m_Entries.erase(
					std::remove_if(
						m_Entries.begin(),
						m_Entries.end(),
						[&Entry](const IniEntryPtr &obj) {return obj->EntryKeyGet() == Entry->EntryKeyGet();}
					),
					m_Entries.end()
				);
			}

			// ******************************************************************
			// ******************************************************************
			IniEntryPtr IniEntryList::EntryFind(const std::string &EntryKey)
			{
				auto it = std::find_if(m_Entries.begin(), m_Entries.end(), [&EntryKey](const IniEntryPtr &obj) {return obj->EntryKeyGet() == EntryKey;});
				IniEntryPtr Element = nullptr;

				if (it != m_Entries.end())
				{
					Element = *it;
				}

				return Element;
			}
		}
	}
}
