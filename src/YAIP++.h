//******************************************************************************
// Copyright 2016 ThirtySomething
//******************************************************************************
// This file is part of YAIP++.
//
// YAIP++ is free software: you can redistribute it and/or modify it under the
// terms of the GNU Lesser General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// YAIP++ is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
// more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with YAIP++. If not, see <http://www.gnu.org/licenses/>.
//******************************************************************************

/**
 * \file	YAIP++.h
 * \author	ThirtySomething
 * \date	2016-09-19
 * \brief	Header of Yet Another INI Parser
 */
#pragma once

#include <ctype.h>
#include <functional>
#include <locale>
#include <map>
#include <regex>
#include <string>
#include <vector>

/**
 * Namespace of YAIP
 */
namespace org
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
			 * This struct will be passed to each map and will ensure an alphabetical order of all keys
			 */
			struct StringCompareCaseLess : std::binary_function<std::string, std::string, bool>
			{
				/**
				 * Comparison of two strings represented by unsigned chars
				 */
				struct CompareCaseless : public std::binary_function<unsigned char, unsigned char, bool>
				{
					/**
					 * Operator for usage in string compare
					 * \param CharLeft Left character to check
					 * \param CharRight Right character to check
					 * \return true in case the left character is less than the right character
					 */
					bool operator() (const unsigned char& CharLeft, const unsigned char& CharRight) const
					{
						return (tolower(CharLeft) < tolower(CharRight));
					}
				};

				/**
				 * Operator for usage in string compare
				 * \param StringLeft Left string to check
				 * \param StringRight Right string to check
				 * \return true in case the left string is less than the right string
				 */
				bool operator() (const std::string & StringLeft, const std::string & StringRight) const
				{
					return std::lexicographical_compare(StringLeft.begin(), StringLeft.end(), StringRight.begin(), StringRight.end(), CompareCaseless());
				}
			};

			/**
			 * Convenience typedef for a map of strings.
			 * Used to represent keys and their corresponding values.
			 * Map will be sorted caseless.
			 */
			typedef std::map<std::string, std::string, StringCompareCaseLess> tMapStringString;

			/**
			 * Convenience typedef for a map of keys/values.
			 * Used to represent a section with their corrresponding keys/values storage.
			 * Map will be sorted caseless.
			 */
			typedef std::map<std::string, tMapStringString, StringCompareCaseLess> tMapStringMapStringString;

			/**
			 * Convenience typedef for a vector of strings.
			 * Used to represent the content of a INI file, a list of sections or a list of keys.
			 */
			typedef std::vector<std::string> tVectorString;

			/**
			 * Class to convert data from and to std::string
			 * \todo Add converters for all fundamental types:
			 * \see http://en.cppreference.com/w/cpp/language/types
			 * <table>
			 * <caption id="multi_row">Fundamental types</caption>
			 * <tr><th>Type</th><th>Done</th></tr>
			 * <tr><td>bool</td><td>x</td></tr>
			 * <tr><td>int</td><td>x</td></tr>
			 * <tr><td>unsigned int</td><td>-</td>x</tr>
			 * <tr><td>short</td><td>-</td></tr>
			 * <tr><td>unsigned short</td><td>-</td></tr>
			 * <tr><td>long</td><td>-</td></tr>
			 * <tr><td>unsigned long</td><td>-</td></tr>
			 * <tr><td>long long</td><td>-</td></tr>
			 * <tr><td>unsigned long long</td><td>-</td></tr>
			 * <tr><td>char</td><td>-</td></tr>
			 * <tr><td>unsigned char</td><td>-</td></tr>
			 * <tr><td>float</td><td>x</td></tr>
			 * <tr><td>double</td><td>x</td></tr>
			 * <tr><td>long double</td><td>-</td></tr>
			 * </table>
			 */
			class Convert
			{
			public:
				/**
				 * Used as constant for bool
				 */
				static const std::string StringTrue;

				/**
				 * Used as constant for bool
				 */
				static const std::string StringFalse;

				/**
				 * Convert integer to std::string
				 * \param Value Value to convert from
				 * \param ValueString Value to convert to
				 */
				static void ConvertTo(int Value, std::string &ValueString);

				/**
				 * Convert unsigned integer to std::string
				 * \param Value Value to convert from
				 * \param ValueString Value to convert to
				 */
				static void ConvertTo(unsigned int Value, std::string &ValueString);

				/**
				 * Convert long to std::string
				 * \param Value Value to convert from
				 * \param ValueString Value to convert to
				 */
				static void ConvertTo(long Value, std::string &ValueString);

				/**
				 * Convert float to std::string
				 * \param Value Value to convert from
				 * \param ValueString Value to convert to
				 */
				static void ConvertTo(float Value, std::string &ValueString);

				/**
				 * Convert double to std::string
				 * \param Value Value to convert from
				 * \param ValueString Value to convert to
				 */
				static void ConvertTo(double Value, std::string &ValueString);

				/**
				 * Convert bool to std::string
				 * \param Value Value to convert from
				 * \param ValueString Value to convert to
				 */
				static void ConvertTo(bool Value, std::string &ValueString);

				/**
				 * Convert std::string to int
				 * \param ValueString Value to convert from
				 * \param Value Value to convert to
				 */
				static void ConvertTo(std::string ValueString, int &Value);

				/**
				 * Convert std::string to unsigned int
				 * \param ValueString Value to convert from
				 * \param Value Value to convert to
				 */
				static void ConvertTo(std::string ValueString, unsigned int &Value);

				/**
				 * Convert std::string to long
				 * \param ValueString Value to convert from
				 * \param Value Value to convert to
				 */
				static void ConvertTo(std::string ValueString, long &Value);

				/**
				 * Convert std::string to float
				 * \param ValueString Value to convert from
				 * \param Value Value to convert to
				 */
				static void ConvertTo(std::string ValueString, float &Value);

				/**
				 * Convert std::string to double
				 * \param ValueString Value to convert from
				 * \param Value Value to convert to
				 */
				static void ConvertTo(std::string ValueString, double &Value);

				/**
				 * Convert std::string to bool
				 * \param ValueString Value to convert from
				 * \param Value Value to convert to
				 */
				static void ConvertTo(std::string ValueString, bool &Value);
			};

			/**
			 * Class to read INI files and offer access to the data
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
				 */
				void SectionKeyKill(const std::string &Section, const std::string &Key);

				/**
				 * Get all keys of a section of the INI file
				 * \param Section Specified section
				 * \return Vector with a std::strings for each key
				 */
				tVectorString SectionKeyListGet(const std::string &Section);

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
				 * Remove section completely from internal data structure
				 * \param Section Specified section
				 */
				void SectionKill(const std::string &Section);

				/**
				 * Get all sections of the INI file
				 * \return Vector with a std::strings for each section
				 */
				tVectorString SectionListGet(void);

				/**
				 * Drop all data to get a clean INI
				 */
				void Clear(void);

			protected:
				/**
				 * Internal map for all sections, each section represented by a map serving the key/value data
				 */
				tMapStringMapStringString m_IniData;

				/**
				 * Regular expression to detect the key/value pairs
				 */
				static const std::regex RegExKeyValue;

				/**
				 * Regular expression to detect the sections
				 */
				static const std::regex RegExSection;

				/**
				 * Save given section into INI file
				 * \param Section Section to write
				 * \param IniFile INI file to read section to
				 */
				void INIFileSaveSection(std::string Section, std::ofstream &IniFile);

				/**
				 * In case a new key/value-pair is matched by the regex, the return value signals new data and the variables are populated.
				 * \param Line of INI file
				 * \param Key Where to write new key to
				 * \param Value Where to write new value to
				 * \return true for section match, otherwise false
				 */
				static bool NewKeyValue(std::string Line, std::string &Key, std::string &Value);

				/**
				 * In case a new section is matched by the regex, the return value signals new section and the variable is populated.
				 * \param Line of INI file
				 * \param Section Where to write new section value to
				 * \return true for section match, otherwise false
				 */
				static bool NewSection(std::string Line, std::string &Section);

				/**
				 * Loop over file content to determine sections and key/values to populate internal storage
				 * \param FileContent The INI file as a vector of std::strings, each line a string
				 */
				void ParseFileContent(tVectorString FileContent);
			};
		}
	}
}
