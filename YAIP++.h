/**
 * \file	YAIP++.h
 * \author	ThirtySomething
 * \date	2016-09-19
 * \brief	Header of Yet Another INI Parser
 */
#pragma once

#include "YAIP++Data.h"
#include <sstream>

 /**
  * Namespace of YAIP
  */
namespace YAIP
{
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
		 */
		void INIFileLoad(std::string Filename);

		/**
		 * Save internal structures to INI file
		 * \param Filename Full qualified filename of the INI file
		 */
		void INIFileSave(std::string Filename);

		/**
		 * Get all section of the INI file
		 * \return Vector with a std::strings for each section
		 */
		tVectorString SectionListGet(void);

		/**
		 * Get all keys of a section of the INI file
		 * \param Section Specified section
		 * \return Vector with a std::strings for each key
		 */
		tVectorString SectionKeyListGet(std::string Section);

		/**
		 * Templated method to retrieve a value of the specified section/key combination - will work
		 * for almost everything except std::string
		 * \param Section Specified section
		 * \param Key Specified key
		 * \param Default Specified default value in case key does not exist
		 * \return Returns either the default value or the value of the existing section/key combination
		 */
		template<typename VariableType>
		VariableType SectionKeyValueGet(std::string Section, std::string Key, VariableType Default)
		{
			// First of all ensure the default return value
			VariableType ReturnValue = Default;

			// Check for section
			tMapMapStringString::iterator SectionDataRaw = m_IniData.find(Section);
			if (m_IniData.end() != SectionDataRaw)
			{
				tMapStringString SectionData = SectionDataRaw->second;
				tMapStringString::iterator KeyDataRaw = SectionData.find(Key);
				if (SectionData.end() != KeyDataRaw)
				{
					// Check for std::string
					if (nullptr != dynamic_cast<std::string*>(&Default))
					{
						// Assignment of complete std::string
						ReturnValue = KeyDataRaw->second;
					}
					else
					{
						// Convert std::string into VariableType
						std::stringstream StringStream(KeyDataRaw->second);
						StringStream >> ReturnValue;
					}
				}
			}

			return ReturnValue;
		}

		/**
		 * Templated method to set a value of the specified section/key combination
		 * \param Section Specified section
		 * \param Key Specified key
		 * \param Value Specified value to set
		 */
		template<typename VariableType>
		void SectionKeyValueSet(std::string Section, std::string Key, VariableType Value)
		{
			// Write data into string stream and convert to a std::string
			std::ostringstream DataRaw(Value);
			std::string Data = DataRaw.str();

			// Create new key/value pair
			tMapStringString KeyValueNew;
			KeyValueNew.insert(std::make_pair(Key, Data));

			// Old key/value data
			tMapStringString KeyValueOld;

			// Check for section
			tMapMapStringString::iterator SectionDataRaw = m_IniData.find(Section);
			if (m_IniData.end() != SectionDataRaw)
			{
				// Section already exists, pick data and erase section
				KeyValueOld = SectionDataRaw->second;
				m_IniData.erase(Section);
			}

			tMapStringString::iterator KeyValueOldPosition = KeyValueOld.find(Key);
			if (KeyValueOld.end() != KeyValueOldPosition)
			{
				// Section already exists, pick data and erase section
				KeyValueOld.erase(Key);
			}

			KeyValueOld.insert(KeyValueNew.begin(), KeyValueNew.end());
			m_IniData.insert(std::make_pair(Section, KeyValueOld));
		}

	protected:
		/**
		 * Internal map for all sections, each section represented by a map serving the key/value data
		 */
		tMapMapStringString m_IniData;

		/**
		 * Regular expression to detect the sections
		 */
		static const std::regex RegExSection;

		/**
		 * Regular expression to detect the key/value pairs
		 */
		static const std::regex RegExKeyValue;

		/**
		 * Loop over file content to determine sections and key/values to populate internal storage
		 * \param FileContent The INI file as a vector of std::strings, each line a string
		 */
		void ParseFileContent(tVectorString &FileContent);

		/**
		 * In case a new section is matched by the regex, the return value signals new section and the variable is populated.
		 * \param Line of INI file
		 * \param Section Where to write new section value to
		 * \return true for section match, otherwise false
		 */
		static bool NewSection(const std::string &Line, std::string &Section);

		/**
		 * In case a new key/value-pair is matched by the regex, the return value signals new data and the variables are populated.
		 * \param Line of INI file
		 * \param Key Where to write new key to
		 * \param Value Where to write new value to
		 * \return true for section match, otherwise false
		 */
		static bool NewKeyValue(const std::string &Line, std::string &Key, std::string &Value);

		/**
		 * Save given section into INI file
		 * \param Section Section to write
		 * \param IniFile INI file to read section to
		 */
		void INIFileSaveSection(std::string Section, std::ofstream &IniFile);
	};
}
