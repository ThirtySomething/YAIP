/**
 * \file	YAIP++.cpp
 * \author	ThirtySomething
 * \date	2016-09-19
 * \brief	Implementation of Yet Another INI Parser
 */
#include "YAIP++.h"
#include <iostream>
#include <fstream>

/**
 * Namespace of YAIP
 */
namespace YAIP{
	// ******************************************************************
	// ******************************************************************
	// Regular expressioin for matching a section
	const std::regex YAIP::RegExSection("([\\s]+)?(\\[){1}([\\s]+)?(([a-zA-Z0-9])+){1}([\\s]+)?(\\]){1}([\\s]+)?([#;])?(.)*");
	//                                      1       2        3            4              5       6        7       8    9
	// 1 - Possible whitespaces
	// 2 - Opening square bracked
	// 3 - Possible whitespaces
	// 4 - Section => Match everything with upper-/lowercase characters and numbers
	// 5 - Possible whitespaces
	// 6 - Closing square bracked
	// 7 - Possible whitespaces
	// 8 - Marker for "comment start"
	// 9 - Comment

	// ******************************************************************
	// ******************************************************************
	// Regular expressioin for matching a key/value pair
	const std::regex YAIP::RegExKeyValue("([\\s]+)?(([a-zA-Z0-9\\.])+){1}([\\s]+)?(=){1}([\\s]+)?(([a-zA-Z0-9\\.\\+-])+)?([\\s]+)?([#;])?(.)*");
	//                                        1           2                 3       4      5               6                7        8    9
	// 1 - Possible whitespaces
	// 2 - Key => Match everything with upper-/lowercase characters, numbers and a dot
	// 3 - Possible whitespaces
	// 4 - The assignment
	// 5 - Possible whitespaces
	// 6 - Value => Match everything with upper-/lowercase characters, numbers, dot, plus and minus sign
	// 7 - Possible whitespaces
	// 8 - Marker for "comment start"
	// 9 - Comment

	// ******************************************************************
	// ******************************************************************
	YAIP::YAIP(void)
		:m_IniData()
	{
	}

	// ******************************************************************
	// ******************************************************************
	YAIP::~YAIP(void)
	{
	}

	// ******************************************************************
	// ******************************************************************
	void YAIP::INIFileLoad(std::string Filename)
	{
		// Always clear internal storage
		m_IniData.clear();
		std::ifstream  IniFile;

		// Open the INI file for reading
		IniFile.open(Filename, std::ios::in);

		// How to handle file errors like file does not exist?
		if (true == IniFile.is_open())
		{
			std::string CurrentLine;
			// Temporary storage for all lines of the INI file
			tVectorString FileContent;

			// Read as long as lines exist
			while (std::getline(IniFile, CurrentLine))
			{
				FileContent.push_back(CurrentLine);
			}
			IniFile.close();

			// After reading parse the data
			ParseFileContent(FileContent);
		}
	}

	// ******************************************************************
	// ******************************************************************
	void YAIP::ParseFileContent(tVectorString &FileContent)
	{
		// Init variables
		std::string CurrentSection = "";
		std::string CurrentKey = "";
		std::string CurrentValue = "";
		tMapStringString CurrentSectionData;

		m_IniData.insert(std::make_pair(CurrentSection, CurrentSectionData));

		// Loop over the content of the INI file
		for (size_t Loop = 0; Loop < FileContent.size(); Loop++)
		{
			std::string Line = FileContent.at(Loop);

			// Got a new section? Add new structures
			if (true == NewSection(Line, CurrentSection))
			{
				tMapStringString SectionData;
				m_IniData.insert(std::make_pair(CurrentSection, SectionData));
			}

			// Got a new key/value pair? Add new data
			if (true == NewKeyValue(Line, CurrentKey, CurrentValue))
			{
				m_IniData[CurrentSection].insert(std::make_pair(CurrentKey, CurrentValue));
			}
		}
	}

	// ******************************************************************
	// ******************************************************************
	bool YAIP::NewSection(const std::string &Line, std::string &Section)
	{
		bool Success = false;
		std::smatch RegExpMatch;

		// Check for match
		if (true == std::regex_search(Line, RegExpMatch, YAIP::RegExSection))
		{
			// Change section only in case of a match
			// Unfortunately in C++ there are no named groups possible
			// so we have to use the index of the group
			Section = RegExpMatch[4].str();
			Success = true;
		}

		return Success;
	}

	// ******************************************************************
	// ******************************************************************
	bool YAIP::NewKeyValue(const std::string &Line, std::string &Key, std::string &Value)
	{
		bool Success = false;
		std::smatch RegExpMatch;

		// Check for match
		if (true == std::regex_search(Line, RegExpMatch, YAIP::RegExKeyValue))
		{
			// Change section only in case of a match
			// Unfortunately in C++ there are no named groups possible
			// so we have to use the index of the group
			Key = RegExpMatch[2].str();
			Value = RegExpMatch[7].str();
			Success = true;
		}

		return Success;
	}

	// ******************************************************************
	// ******************************************************************
	tVectorString YAIP::SectionListGet(void)
	{
		tVectorString SectionList;

		// Loop over the major map containing all sections
		for (tMapMapStringString::iterator Loop = m_IniData.begin(); Loop != m_IniData.end(); ++Loop)
		{
			SectionList.push_back(Loop->first);
		}

		return SectionList;
	}

	// ******************************************************************
	// ******************************************************************
	tVectorString YAIP::SectionKeyListGet(std::string Section)
	{
		tVectorString KeyList;

		// Figure out if requested section exists
		tMapMapStringString::iterator SectionDataRaw = m_IniData.find(Section);
		if (m_IniData.end() != SectionDataRaw)
		{
			tMapStringString SectionData = SectionDataRaw->second;
			// Loop over the key/value map retrieved in previous step
			for (tMapStringString::iterator Loop = SectionData.begin(); Loop != SectionData.end(); ++Loop)
			{
				KeyList.push_back(Loop->first);
			}
		}

		return KeyList;
	}
}
