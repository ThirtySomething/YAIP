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

#include "IElementCommon.h"
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
			/**
			 * Represents an INI entry
			 */
			class IniEntry : public IElementCommon
			{
			public:
				/**
				 * Default constructor
				 */
				IniEntry(void);

				/**
				 * Default destructor
				 */
				virtual ~IniEntry(void);

				/**
				 * The unique element identifier is the key of an INI entry
				 * \param ElementIdentifier The key of the INI entry
				 */
				virtual void ElementIdentifierSet(const std::string &ElementIdentifier) override;

				/**
				 * Get the unique element identifier aka the key of an INI entry
				 * \return The key of the INI entry
				 */
				virtual std::string ElementIdentifierGet(void) override;

				/**
				 * Set the INI object value
				 * \param ElementValue Value of INI object
				 */
				virtual void ElementValueSet(const std::string &ElementValue);

				/**
				 * Get the INI object value
				 * \return Value of INI object
				 */
				virtual std::string ElementValueGet(void);

				/**
				 * Set the INI object comment
				 * \param ElementComment Comment of INI object
				 */
				virtual void ElementCommentSet(const std::string &ElementComment) override;

				/**
				 * Get the INI object comment
				 * \return Comment of INI object
				 */
				virtual std::string ElementCommentGet(void) override;

				/**
				 * Will transform string into internal properties
				 * \param RawData string from INI file to transform
				 * \return true on success, otherwise false
				 */
				virtual bool CreateFromRawData(const std::string &RawData) override;

				/**
				 * String representation of an INI entry
				 * \return String representation of an INI entry
				 */
				std::string to_string(void) const;

			private:
				/**
				 * Section - Regular expression
				 */
				static const std::regex RegExKeyValue;

				/**
				 * The key aka unique identifier of the INI entry
				 */
				std::string m_EntryKey;

				/**
				 * The value of the INI entry
				 */
				std::string m_EntryValue;

				/**
				 * The comment of the INI entry
				 */
				std::string m_EntryComment;

				/**
				 * Stream the object content to an output stream
				 * \param OutputStream The stream to put the content on
				 * \param EntryObject The object to stream
				 * \return Reference to the output stream
				 */
				friend std::ostream& operator<<(std::ostream &OutputStream, const IniEntry &EntryObject);
			};

			/**
			 * Convenience typedef for lazy usage of smart_pointers for IniEntries
			 */
			typedef std::shared_ptr<IniEntry> IniEntryPtr;
		}
	}
}
