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

#include "IElementCommon.h"
#include "IniEntry.h"
#include "IniEntryList.h"
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
			 * Represents an INI section
			 */
			class IniSection : public IElementCommon
			{
			public:
				/**
				 * Default constructor
				 */
				IniSection(void);

				/**
				 * Default destructor
				 */
				virtual ~IniSection(void);

				/**
				 * The unique element identifier is the key of an INI entry
				 * \param ElementIdentifier The key of the INI entry
				 */
				virtual void ElementIdentifierSet(const std::string &ElementIdentifier) override;

				/**
				 * Get the unique element identifier aka the key of an INI entry
				 * \return The key of the INI entry
				 */
				virtual std::string ElementIdentifierGet(void) const override;

				/**
				 * Set the INI object comment
				 * \param ElementComment Unique comment of INI object
				 */
				virtual void ElementCommentSet(const std::string &ElementComment) override;

				/**
				 * Get the INI object comment
				 * \return Comment of INI object
				 */
				virtual std::string ElementCommentGet(void) const override;

				/**
				 * Set list of entries
				 * \param SectionEntries Vector with entries to set
				 * \attention This is a replace, not a merge, not an add
				 */
				void SectionEntriesSet(const IniEntryList &SectionEntries);

				/**
				 * Get list of entries
				 * \return List of entries
				 */
				IniEntryList SectionEntriesGet(void) const;

				/**
				 * Will transform string into internal properties
				 * \param RawData string from INI file to transform
				 * \return true on success, otherwise false
				 */
				virtual bool CreateFromRawData(const std::string &RawData) override;

				/**
				 * Add a new entry based on raw data
				 * \param RawEntryData New entry with key, value (and comment) as string
				 * \return True on success, otherwise false
				 */
				bool AddRawEntry(const std::string &RawEntryData);

				/**
				 * Find and return entry based on the entry name (the key)
				 * \param EntryName The name (better: the key) of the entry to search
				 * \return Entry on success, otherwise nullptr
				 */
				IniEntryPtr EntryFind(const std::string &EntryName);

				/**
				 * Delete given entry
				 * \param Entry Entry to delete
				 */
				void EntryDelete(const IniEntryPtr &Entry);

				/**
				 * Get a list of all keys of this sections
				 * \return List of keys
				 */
				tListString EntryKeyList(void) const;

				/**
				 * Check if section is empty
				 * \return True if empty otherwise false
				 */
				bool IsEmpty(void) const;

				/**
				 * Add an entry to the section
				 * \param Entry The entry to add.
				 */
				void EntryAdd(const IniEntryPtr &Entry);

				/**
				 * String representation of an INI entry
				 * \return String representation of an INI entry
				 */
				std::string to_string(void) const;

				/**
				 * To clear object and reset to empty fields
				 */
				virtual void clear(void) override;

				/**
				 * Required by interface to sort entries alphabetically by their key
				 */
				virtual void sort(void) override;

			private:
				/**
				 * Section - Regular expression
				 */
				static const std::regex RegExSection;

				/**
				 * The name of the section
				 */
				std::string m_SectionName;

				/**
				 * The comment of the section
				 */
				std::string m_SectionComment;

				/**
				 * All entries to this section
				 */
				IniEntryList m_Entries;

				/**
				 * Stream the object content to an output stream
				 * \param OutputStream The stream to put the content on
				 * \param SectionObject The object to stream
				 * \return Reference to the output stream
				 */
				friend std::ostream& operator<<(std::ostream &OutputStream, const IniSection &SectionObject);
			};

			/**
			 * Convenience typedef for lazy usage of smart_pointers for IniSections
			 */
			typedef std::shared_ptr<IniSection> IniSectionPtr;
		}
	}
}
