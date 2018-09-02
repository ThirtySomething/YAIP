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
 * \file	YAIP++.cpp
 * \author	ThirtySomething
 * \date	2016-09-19
 * \brief	Implementation of Yet Another INI Parser
 */
#include "YAIP++.h"
#include <fstream>
#include <sstream>
#include <ios>
#include <iostream>
#include <iomanip>
#include <limits>

#ifdef __MINGW32__
// GCC on windows does not support std::to_string
#include <string>
#include <sstream>
#include <stdlib.h>

namespace std
{
	template < typename T > std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}

	int stoi(const std::string &s)
	{
		int i = 0;
		sscanf(s.c_str(), "%d", &i);
		return i;
	}

	int stol(const std::string &s)
	{
		long i = 0;
		sscanf(s.c_str(), "%ld", &i);
		return i;
	}

	double stod(const std::string &s)
	{
		double d = 0.0;
		sscanf(s.c_str(), "%lf", &d);
		return d;
	}

	float stof(const std::string &s)
	{
		float f = 0.0;
		sscanf(s.c_str(), "%f", &f);
		return f;
	}
}
#endif // __MINGW32__

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
			// ******************************************************************
			// ******************************************************************
			const std::string Convert::StringTrue = "true";
			const std::string Convert::StringFalse = "false";

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(int Value, std::string &ValueString)
			{
				std::ostringstream StringStream;
				StringStream << std::scientific << Value;
				ValueString = StringStream.str();
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(unsigned int Value, std::string &ValueString)
			{
				std::ostringstream StringStream;
				StringStream << std::scientific << Value;
				ValueString = StringStream.str();
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(long Value, std::string &ValueString)
			{
				std::ostringstream StringStream;
				StringStream << std::scientific << Value;
				ValueString = StringStream.str();
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(float Value, std::string &ValueString)
			{
				typedef std::numeric_limits<float> Limits;
				std::ostringstream StringStream;
				StringStream << std::setprecision(Limits::max_digits10) << std::scientific << Value;
				ValueString = StringStream.str();
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(double Value, std::string &ValueString)
			{
				typedef std::numeric_limits<double> Limits;
				std::ostringstream StringStream;
				StringStream << std::setprecision(Limits::max_digits10) << std::scientific << Value;
				ValueString = StringStream.str();
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(bool Value, std::string &ValueString)
			{
				ValueString = Convert::StringFalse;
				if (true == Value)
				{
					ValueString = Convert::StringTrue;
				}
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(std::string ValueString, int &Value)
			{
				Value = std::stoi(ValueString);
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(std::string ValueString, unsigned int &Value)
			{
				Value = std::stoi(ValueString);
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(std::string ValueString, long &Value)
			{
				Value = std::stol(ValueString);
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(std::string ValueString, double &Value)
			{
				Value = std::stod(ValueString);
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(std::string ValueString, float &Value)
			{
				Value = std::stof(ValueString);
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(std::string ValueString, bool &Value)
			{
				Value = false;
				if (0 == ValueString.compare(Convert::StringTrue))
				{
					Value = true;
				}
			}

			// ******************************************************************
			// ******************************************************************
			/**
			 * \todo Invert regex logic to what is NOT allowed for key/values
			 */
			// Regular expressioin for matching a key/value pair
			const std::regex YAIP::RegExKeyValue("([\\s]+)?(([a-zA-Z0-9\\._])+){1}([\\s]+)?(=){1}([\\s]+)?(([a-zA-Z0-9( ):\\\\\\.,_|\\+-])+)?([\\s]+)?([#;])?(.*)");
			//                                        1           2                 3       4      5               6                7        8    9
			// 1 - Possible whitespaces
			// 2 - Key => Match everything with upper-/lowercase characters, numbers, underscore and a dot
			// 3 - Possible whitespaces
			// 4 - The assignment
			// 5 - Possible whitespaces
			// 6 - Value => Match everything with upper-/lowercase characters, numbers, dot, comma, underscore, vertical bar, plus and minus sign
			// 7 - Possible whitespaces
			// 8 - Marker for "comment start"
			// 9 - Comment

			// ******************************************************************
			// ******************************************************************
			/**
			 * \todo Invert regex logic to what is NOT allowed for sections
			 */
			// Regular expressioin for matching a section
			const std::regex YAIP::RegExSection("([\\s]+)?(\\[){1}([\\s]+)?(([a-zA-Z0-9_])+){1}([\\s]+)?(\\]){1}([\\s]+)?([#;])?(.*)");
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
			YAIP::YAIP(void)
				:m_IniData()
			{
			}

			// ******************************************************************
			// ******************************************************************
			YAIP::~YAIP(void)
			{
				Clear();
			}

			// ******************************************************************
			// ******************************************************************
			bool YAIP::INIFileLoad(const std::string &Filename)
			{
				bool Success = false;
				std::ifstream IniFile;

				// Always clear internal storage
				Clear();

				// Open the INI file for reading
				IniFile.open(Filename, std::ios::in);

				/**
				 * \todo Handle file errors like file does not exist
				 */
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

					// Parse INI file
					ParseFileContent(FileContent);
					Success = true;
				}

				return Success;
			}

			// ******************************************************************
			// ******************************************************************
			bool YAIP::INIFileSave(const std::string &Filename)
			{
				bool Success = false;
				std::ofstream IniFile;

				// Open the INI file for writing
				IniFile.open(Filename, std::ios::trunc);

				/**
				 * \todo Handle file errors like cannot open file
				 */
				if (true == IniFile.is_open())
				{
					// Get a list of all existing sections
					tVectorString SectionList = SectionListGet();
					for (tVectorString::iterator LoopSection = SectionList.begin(); LoopSection != SectionList.end(); ++LoopSection)
					{
						// Save section
						INIFileSaveSection(*LoopSection, IniFile);
					}

					IniFile.close();
					Success = true;
				}

				return Success;
			}

			// ******************************************************************
			// ******************************************************************
			void YAIP::SectionKeyKill(const std::string &Section, const std::string &Key)
			{
				// First check for section existence
				if (0 < m_IniData.count(Section))
				{
					// Memorize section data
					tMapStringString KeyValueData = m_IniData.at(Section);

					// Remove section
					m_IniData.erase(Section);

					// Figure out if requested key exists
					if (0 < KeyValueData.count(Key))
					{
						// Key exists, kill key
						KeyValueData.erase(Key);
					}

					// Re-insert section with deleted key
					m_IniData.insert(std::make_pair(Section, KeyValueData));
				}
			}

			// ******************************************************************
			// ******************************************************************
			tVectorString YAIP::SectionKeyListGet(const std::string &Section) const
			{
				tVectorString KeyList;

				// First check for section existence
				if (0 < m_IniData.count(Section))
				{
					tMapStringString SectionData = m_IniData.at(Section);
					// Loop over the key/value map retrieved from section
					for (tMapStringString::iterator Loop = SectionData.begin(); Loop != SectionData.end(); ++Loop)
					{
						KeyList.push_back(Loop->first);
					}
				}

				return KeyList;
			}

			// ******************************************************************
			// ******************************************************************
			std::string YAIP::SectionKeyValueGet(const std::string &Section, const std::string &Key, const std::string &Default) const
			{
				// Ensure default return value
				std::string ReturnValue = Default;

				// First check for section existence
				if (0 < m_IniData.count(Section))
				{
					tMapStringString SectionData = m_IniData.at(Section);

					// Figure out if requested key exists
					if (0 < SectionData.count(Key))
					{
						ReturnValue = SectionData.at(Key);
					}
				}

				return ReturnValue;
			}

			// ******************************************************************
			// ******************************************************************
			bool YAIP::SectionKeyValueSet(const std::string &Section, const std::string &Key, const std::string &Value)
			{
				bool Success = false;
				std::string Data = Value;

				// Create new key/value pair
				tMapStringString KeyValueNew;
				KeyValueNew.insert(std::make_pair(Key, Data));

				// Old key/value data
				tMapStringString KeyValueOld;

				// Check for section
				if (0 < m_IniData.count(Section))
				{
					// Section exists, pick data and kill section
					KeyValueOld = m_IniData.at(Section);
					m_IniData.erase(Section);
				}

				if (0 < KeyValueOld.count(Key))
				{
					// Key exists, pick data and kill key
					KeyValueOld.erase(Key);
				}

				// Merge new and existing data and memorize them
				KeyValueOld.insert(KeyValueNew.begin(), KeyValueNew.end());
				auto Result = m_IniData.insert(std::make_pair(Section, KeyValueOld));
				if (false != Result.second)
				{
					Success = true;
				}

				return Success;
			}

			// ******************************************************************
			// ******************************************************************
			void YAIP::SectionKill(const std::string &Section)
			{
				// First check for section existence
				if (0 < m_IniData.count(Section))
				{
					// Section exists, kill section
					m_IniData.erase(Section);
				}
			}

			// ******************************************************************
			// ******************************************************************
			tVectorString YAIP::SectionListGet(void) const
			{
				tVectorString SectionList;

				// Loop over the major map containing all sections
				for (tMapStringMapStringString::const_iterator Loop = m_IniData.begin(); Loop != m_IniData.end(); ++Loop)
				{
					SectionList.push_back(Loop->first);
				}

				return SectionList;
			}

			// ******************************************************************
			// ******************************************************************
			void YAIP::Clear(void)
			{
				for (tMapStringMapStringString::iterator Loop = m_IniData.begin(); Loop != m_IniData.end(); ++Loop)
				{
					tMapStringString Data = Loop->second;

					Data.clear();
				}
			}

			// ******************************************************************
			// ******************************************************************
			void YAIP::INIFileSaveSection(std::string Section, std::ofstream &IniFile)
			{
				// Retrieve list of keys
				tVectorString KeyList = SectionKeyListGet(Section);
				/**
				 * \todo Keep empty sections?
				 */

				// Write section marker
				if (0 != Section.length())
				{
					IniFile << "[" << Section << "]" << std::endl;
				}

				// Loop over all keys, retrieve the values and save them
				for (tVectorString::iterator LoopKey = KeyList.begin(); LoopKey != KeyList.end(); ++LoopKey)
				{
					std::string Default = "";
					std::string Key = *LoopKey;
					std::string Value = SectionKeyValueGet(Section, Key, Default);
					IniFile << Key << "=" << Value << std::endl;
				}
			}

			// ******************************************************************
			// ******************************************************************
			bool YAIP::NewKeyValue(std::string Line, std::string &Key, std::string &Value)
			{
				// Assume no new key/value pair
				bool Success = false;
				std::smatch RegExpMatch;

				// Check for match
				if (true == std::regex_search(Line, RegExpMatch, YAIP::RegExKeyValue))
				{
					// Change new key/value pair only in case of a match.
					// Unfortunately in C++ there are no named groups possible
					// so we have to use the index of the group.
					Key = RegExpMatch[2].str();
					Value = RegExpMatch[7].str();
					Success = true;
				}

				return Success;
			}

			// ******************************************************************
			// ******************************************************************
			bool YAIP::NewSection(std::string Line, std::string &Section)
			{
				// Assume no new section
				bool Success = false;
				std::smatch RegExpMatch;

				// Check for match
				if (true == std::regex_search(Line, RegExpMatch, YAIP::RegExSection))
				{
					// Change section only in case of a match.
					// Unfortunately in C++ there are no named groups possible
					// so we have to use the index of the group.
					Section = RegExpMatch[4].str();
					Success = true;
				}

				return Success;
			}

			// ******************************************************************
			// ******************************************************************
			void YAIP::ParseFileContent(tVectorString FileContent)
			{
				/**
				 * \todo Check specification if empty section is allowed
				 */
				std::string CurrentSection = "";
				std::string CurrentKey = "";
				std::string CurrentValue = "";
				tMapStringString CurrentSectionData;

				// Insert default section - some key/value entries might exist without a section
				m_IniData.insert(std::make_pair(CurrentSection, CurrentSectionData));

				// Loop over the INI file
				for (size_t Loop = 0; Loop < FileContent.size(); Loop++)
				{
					std::string Line = FileContent.at(Loop);

					// Got a new section?
					if (true == NewSection(Line, CurrentSection))
					{
						// Add new internal structures
						tMapStringString SectionData;
						m_IniData.insert(std::make_pair(CurrentSection, SectionData));
					}

					// Got a new key/value pair?
					if (true == NewKeyValue(Line, CurrentKey, CurrentValue))
					{
						// Add new data
						m_IniData[CurrentSection].insert(std::make_pair(CurrentKey, CurrentValue));
					}
				}
			}
		}
	}
}
