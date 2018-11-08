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
 * \file	IniSectionList.cpp
 * \author	ThirtySomething
 * \date	2016-09-19
 * \brief	List of INI sections
 */

#include "IniSectionList.h"
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
			IniSectionList::IniSectionList(void)
				: m_Sections()
			{
			}

			// ******************************************************************
			// ******************************************************************
			IniSectionList::~IniSectionList(void)
			{
				clear();
			}

			// ******************************************************************
			// ******************************************************************
			void IniSectionList::clear(void)
			{
				m_Sections.clear();
			}

			// ******************************************************************
			// ******************************************************************
			void IniSectionList::SectionAdd(const IniSectionPtr &Section)
			{
				m_Sections.push_back(Section);
			}

			// ******************************************************************
			// ******************************************************************
			void IniSectionList::SectionDelete(const IniSectionPtr &Section)
			{
				
				m_Sections.erase(
					std::remove_if(
						m_Sections.begin(),
						m_Sections.end(),
						[&Section](const IniSectionPtr &obj) {return obj->SectionNameGet() == Section->SectionNameGet();}
					),
					m_Sections.end()
				);
			}

			// ******************************************************************
			// ******************************************************************
			IniSectionPtr IniSectionList::SectionFind(const std::string &SectionName)
			{
				auto it = std::find_if(m_Sections.begin(), m_Sections.end(), [&SectionName](const IniSectionPtr &obj) {return obj->SectionNameGet() == SectionName;});
				IniSectionPtr Element = nullptr;

				if (it != m_Sections.end())
				{
					Element = *it;
				}

				return Element;
			}
		}
	}
}
