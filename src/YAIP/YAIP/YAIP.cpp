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
 * \file	YAIP.cpp
 * \author	ThirtySomething
 * \date	2016-09-19
 * \brief	Implementation of Yet Another INI Parser
 */
#include "YAIP.h"
#include <fstream>
#include <sstream>

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
			YAIP::YAIP()
				: m_Sections()
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
			void YAIP::Clear(void)
			{
				m_Sections.clear();
			}

			// ******************************************************************
			// ******************************************************************
			bool YAIP::INIFileDelete(const std::string &Filename)
			{
				bool deleted = (0 == remove(Filename.c_str()));
				return deleted;
			}

			// ******************************************************************
			// ******************************************************************
			bool YAIP::INIFileExist(const std::string &Filename)
			{
				struct stat buffer;
				bool exist = (0 == stat(Filename.c_str(), &buffer));
				return exist;
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
				if (IniFile.is_open())
				{
					std::string CurrentLine;

					// Temporary storage for all lines of the INI file
					tListString FileContent;

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
				if (IniFile.is_open())
				{
					m_Sections.sort();
					IniFile << m_Sections.to_string();
					IniFile.close();
					Success = true;
				}

				return Success;
			}

			// ******************************************************************
			// ******************************************************************
			bool YAIP::SectionKeyKill(const std::string &Section, const std::string &Key)
			{
				bool Success = false;

				IniSectionPtr CurrentSection = m_Sections.ElementFind(Section);
				if (nullptr != CurrentSection)
				{
					IniEntryPtr CurrentEntry = CurrentSection->EntryFind(Key);
					if (nullptr != CurrentEntry)
					{
						CurrentSection->EntryDelete(CurrentEntry);
						Success = true;
					}

					if (CurrentSection->IsEmpty())
					{
						m_Sections.ElementDelete(CurrentSection);
					}
				}

				return Success;
			}

			// ******************************************************************
			// ******************************************************************
			tListString YAIP::SectionKeyListGet(const std::string &Section)
			{
				tListString KeyList;

				IniSectionPtr CurrentSection = m_Sections.ElementFind(Section);
				if (nullptr != CurrentSection)
				{
					KeyList = CurrentSection->EntryKeyList();
				}

				return KeyList;
			}

			// ******************************************************************
			// ******************************************************************
			bool YAIP::SectionKeyValueClear(const std::string &Section, const std::string &Key)
			{
				return SectionKeyValueSet(Section, Key, ' ');
			}

			// ******************************************************************
			// ******************************************************************
			std::string YAIP::SectionKeyValueGet(const std::string &Section, const std::string &Key, const std::string &Default)
			{
				// Ensure default return value
				std::string ReturnValue = Default;

				IniSectionPtr CurrentSection = m_Sections.ElementFind(Section);
				if (nullptr != CurrentSection)
				{
					IniEntryPtr CurrentEntry = CurrentSection->EntryFind(Key);
					if (nullptr != CurrentEntry)
					{
						ReturnValue = CurrentEntry->ElementValueGet();
					}
				}

				if (0 == ReturnValue.length())
				{
					ReturnValue = Default;
				}

				return ReturnValue;
			}

			// ******************************************************************
			// ******************************************************************
			bool YAIP::SectionKeyValueSet(const std::string &Section, const std::string &Key, const std::string &Value)
			{
				IniSectionPtr CurrentSection = m_Sections.ElementFind(Section);
				if (nullptr == CurrentSection)
				{
					CurrentSection.reset(new IniSection);
					CurrentSection->ElementIdentifierSet(Section);
					m_Sections.ElementAdd(CurrentSection);
				}

				IniEntryPtr CurrentEntry = CurrentSection->EntryFind(Key);
				if (nullptr != CurrentEntry)
				{
					CurrentSection->EntryDelete(CurrentEntry);
				}
				else
				{
					CurrentEntry.reset(new IniEntry);
				}

				CurrentEntry->ElementIdentifierSet(Key);
				CurrentEntry->ElementValueSet(Value);
				CurrentSection->EntryAdd(CurrentEntry);

				return true;
			}

			// ******************************************************************
			// ******************************************************************
			tListString YAIP::SectionListGet(void)
			{
				return m_Sections.ElementIdentifierList();
			}

			// ******************************************************************
			// ******************************************************************
			std::string YAIP::to_string(void) const
			{
				return m_Sections.to_string();
			}

			// ******************************************************************
			// ******************************************************************
			void YAIP::ParseFileContent(tListString FileContent)
			{
				IniSection* CurrentSectionPtr = nullptr;

				// Loop over the INI file
				for (auto const& Loop : FileContent)
				{
					std::string Line = Loop;

					// Got a new section?
					IniSectionPtr SectionPtr(new IniSection);
					if (SectionPtr->CreateFromRawData(Line))
					{
						m_Sections.ElementAdd(SectionPtr);
						CurrentSectionPtr = SectionPtr.get();
						continue;
					}

					if (nullptr != CurrentSectionPtr)
					{
						CurrentSectionPtr->AddRawEntry(Line);
					}
				}
			}
		}
	}
}
