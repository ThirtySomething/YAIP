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
 * \file	TIniElementList.h
 * \author	ThirtySomething
 * \date	2016-09-19
 * \brief	Template for list of elements
 */
#pragma once

#include "string_extensions.h"
#include <algorithm>
#include <list>
#include <string>
#include <vector>

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
			/**
			 * Convenience typedef for lazy usage of vector of strings
			 */
			typedef std::list<std::string> tListString;

			/**
			 * Templated  class as base for list of sections and list of entries
			 */
			template <typename TIniElement> class TIniElementList
			{
			public:
				/**
				 * Default constructor
				 */
				TIniElementList(void)
					: m_Elements()
				{
				}

				/**
				 * Default destructor
				 */
				virtual ~TIniElementList(void)
				{
					clear();
				}

				/**
				 * Clear the list
				 */
				void clear(void)
				{
					m_Elements.clear();
				}

				/**
				 * Add an element to the list
				 * \param Element Element to add
				 */
				void ElementAdd(const TIniElement &Element)
				{
					m_Elements.push_back(Element);
				}

				/**
				 * Remove given element from list
				 * \param Element Element to delete
				 */
				void ElementDelete(const TIniElement &Element)
				{
					m_Elements.erase(
						std::remove_if(
							m_Elements.begin(),
							m_Elements.end(),
							[&Element](const TIniElement &obj) { return obj->ElementIdentifierGet() == Element->ElementIdentifierGet(); }
						),
						m_Elements.end()
					);
				}

				/**
				 * Find element by identifier
				 * \param ElementName Name to identify element
				 * \return Pointer to element if exists otherwise nullptr
				 */
				TIniElement ElementFind(const std::string &ElementName)
				{
					std::string ElementNameWork = std::trim(ElementName);
					TIniElement Element = nullptr;

					auto it = std::find_if(m_Elements.begin(), m_Elements.end(), [&ElementNameWork](const TIniElement &obj) {return obj->ElementIdentifierGet() == ElementNameWork; });
					if (it != m_Elements.end())
					{
						Element = *it;
					}

					return Element;
				}

				/**
				 * Determine size of list
				 * \return Size of list
				 */
				int size(void) const
				{
					return static_cast<int>(m_Elements.size());
				}

				/**
				 * Get a list of all element identifiers
				 * \return Vector of all identifiers
				 */
				tListString ElementIdentifierList(void) const
				{
					tListString List;

					for (auto CurrentElementPtr = m_Elements.begin(); CurrentElementPtr != m_Elements.end(); ++CurrentElementPtr)
					{
						List.push_back((*CurrentElementPtr)->ElementIdentifierGet());
					}

					return List;
				}

				/**
				 * String representation of the list
				 * \return String representation of the list
				 */
				std::string to_string(void) const
				{
					std::ostringstream tmpStream;

					for (auto CurrentElementPtr = m_Elements.begin(); CurrentElementPtr != m_Elements.end(); ++CurrentElementPtr)
					{
						tmpStream << (*CurrentElementPtr)->to_string();
					}

					return tmpStream.str();
				}

				virtual void sort(void) = 0;

			protected:
				/**
				 * Vector of elements
				 */
				std::vector<TIniElement> m_Elements;
			};
		}
	}
}

