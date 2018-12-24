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
 * \file	YAIP.h
 * \author	ThirtySomething
 * \date	2016-09-19
 * \brief	Header of Yet Another INI Parser
 */
#pragma once

#include "Convert.h"
#include "IniSection.h"
#include "IniSectionList.h"
#include <ctype.h>
#include <functional>
#include <map>
#include <memory>
#include <regex>
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
			 * Class to manipulate INI files
			 */
			class YAIP
			{
			public:
				/**
				 * Default constructor
				 */
				YAIP(void);

				/**
				 * Default destructor
				 */
				virtual ~YAIP(void);

				/**
				 * Delete given INI file
				 * \param Filename Full qualified filename of the INI file
				 * \return true if file is deleted otherwise false
				 */
				static bool INIFileDelete(const std::string &Filename);

				/**
				 * Check if given INI file exists
				 * \param Filename Full qualified filename of the INI file
				 * \return true if file exists otherwise false
				 */
				static bool INIFileExist(const std::string &Filename);

				/**
				 * Load and parse INI file into internal structures
				 * \param Filename Full qualified filename of the INI file
				 * \return true on success otherwise false
				 */
				bool INIFileLoad(const std::string &Filename);

				/**
				 * Save internal structures to INI file
				 * \param Filename Full qualified filename of the INI file
				 * \return true on success otherwise false
				 */
				bool INIFileSave(const std::string &Filename);

				/**
				 * Remove key completely from section of internal data structure
				 * \param Section Specified section
				 * \param Key Specified key
				 * \return true on success otherwise false
				 */
				bool SectionKeyKill(const std::string &Section, const std::string &Key);

				/**
				 * Get all keys of a section of the INI file
				 * \param Section Specified section
				 * \return Vector with a std::strings for each key
				 */
				tListString SectionKeyListGet(const std::string &Section);

				/**
				 * Method to retrieve a value of the specified section/key combination for std::string
				 * \param Section Specified section
				 * \param Key Specified key
				 * \param Default Specified default value in case key does not exist
				 * \return Returns either the default value or the value of the existing section/key combination
				 */
				std::string SectionKeyValueGet(const std::string &Section, const std::string &Key, const std::string &Default);

				/**
				 * Templated method to retrieve a value of the specified section/key combination
				 * \param Section Specified section
				 * \param Key Specified key
				 * \param Default Specified default value in case key does not exist
				 * \return Returns either the default value or the value of the existing section/key combination
				 */
				template<typename VariableType>
				VariableType SectionKeyValueGet(const std::string &Section, const std::string &Key, const VariableType &Default)
				{
					VariableType ValueReturn;
					std::string ValueDefault;
					Convert::ConvertTo(Default, ValueDefault);
					std::string ValueRaw = SectionKeyValueGet(Section, Key, ValueDefault);
					Convert::ConvertTo(ValueRaw, ValueReturn);
					return ValueReturn;
				}

				/**
				 * Method to set a value of the specified section/key combination for std:string
				 * \param Section Specified section
				 * \param Key Specified key
				 * \param Value Specified value to set
				 * \return true on success otherwise false
				 */
				bool SectionKeyValueSet(const std::string &Section, const std::string &Key, const std::string &Value);

				/**
				 * Templated method to set a value of the specified section/key combination
				 * \param Section Specified section
				 * \param Key Specified key
				 * \param Value Specified value to set
				 * \return true on success otherwise false
				 */
				template<typename VariableType>
				bool SectionKeyValueSet(const std::string &Section, const std::string &Key, const VariableType &Value)
				{
					std::string ValueString;
					Convert::ConvertTo(Value, ValueString);
					return SectionKeyValueSet(Section, Key, ValueString);
				}

				/**
				 * Clear a key value
				 * \param Section Specified section
				 * \param Key Specified key
				 * \return true on success otherwise false
				 */
				bool SectionKeyValueClear(const std::string &Section, const std::string &Key);

				/**
				 * Get all sections of the INI file
				 * \return Vector with a std::strings for each section
				 */
				tListString SectionListGet(void);

				/**
				 * Drop all data to get a clean INI
				 */
				void Clear(void);

			protected:
				/**
				 * List of all sections
				 */
				IniSectionList m_Sections;

				/**
				 * Loop over file content to determine sections and key/values to populate internal storage
				 * \param FileContent The INI file as a vector of std::strings, each line a string
				 */
				void ParseFileContent(tListString FileContent);
			};
		}
	}
}
