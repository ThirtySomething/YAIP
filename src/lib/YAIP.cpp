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

#include "YAIP.h"

#include "IIniVisitor.h"
#include "IniParserFactory.h"
#include <fstream>
#include <memory>
#include <sstream>

#ifndef _WIN32
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

namespace net
{
    namespace derpaul
    {
        namespace yaip
        {
            YAIP::YAIP()
                : m_Sections(),
                  m_ParserStrategy(IniParserFactory::Create())
            {
            }

            YAIP::~YAIP(void)
            {
                Clear();
            }

            void YAIP::Clear(void)
            {
                m_Sections.clear();
            }

            bool YAIP::INIFileDelete(const std::string &Filename)
            {
                bool deleted = (0 == remove(Filename.c_str()));
                return deleted;
            }

            bool YAIP::INIFileExist(const std::string &Filename)
            {
#ifdef _WIN32
                struct _stat tmpbuffer;
                int result = _stat(Filename.c_str(), &tmpbuffer);
#else
                struct stat tmpbuffer;
                int result = stat(Filename.c_str(), &tmpbuffer);
#endif
                return result == 0;
            }

            bool YAIP::INIFileLoad(const std::string &Filename)
            {
                bool Success = false;
                std::ifstream IniFile;

                Clear();

                IniFile.open(Filename, std::ios::in);

                if (IniFile.is_open())
                {
                    std::string CurrentLine;

                    tListString FileContent;

                    while (std::getline(IniFile, CurrentLine))
                    {
                        FileContent.push_back(CurrentLine);
                    }
                    IniFile.close();

                    Success = ParseFileContent(FileContent);
                }

                return Success;
            }

            bool YAIP::INIFileSave(const std::string &Filename)
            {
                bool Success = false;
                std::ofstream IniFile;

                IniFile.open(Filename, std::ios::trunc);

                if (IniFile.is_open())
                {
                    m_Sections.sort();
                    IniFile << m_Sections.to_string();
                    IniFile.close();
                    Success = true;
                }

                return Success;
            }

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

            bool YAIP::SectionKeyValueClear(const std::string &Section, const std::string &Key)
            {
                return SectionKeyValueSet(Section, Key, std::string());
            }

            std::string YAIP::SectionKeyValueGet(const std::string &Section, const std::string &Key, const std::string &Default)
            {

                std::string ReturnValue = Default;

                if (auto CurrentSection = m_Sections.ElementFind(Section); nullptr != CurrentSection)
                {
                    if (auto CurrentEntry = CurrentSection->EntryFind(Key); nullptr != CurrentEntry)
                    {
                        ReturnValue = CurrentEntry->ElementValueGet();
                    }
                }

                if (ReturnValue.empty())
                {
                    ReturnValue = Default;
                }

                return ReturnValue;
            }

            bool YAIP::SectionKeyValueSet(const std::string &Section, const std::string &Key, const std::string &Value)
            {
                auto CurrentSection = m_Sections.ElementFind(Section);
                if (nullptr == CurrentSection)
                {
                    CurrentSection = std::make_shared<IniSection>();
                    CurrentSection->ElementIdentifierSet(Section);
                    m_Sections.ElementAdd(CurrentSection);
                }

                auto CurrentEntry = CurrentSection->EntryFind(Key);
                if (nullptr != CurrentEntry)
                {
                    CurrentSection->EntryDelete(CurrentEntry);
                }
                else
                {
                    CurrentEntry = std::make_shared<IniEntry>();
                }

                CurrentEntry->ElementIdentifierSet(Key);
                CurrentEntry->ElementValueSet(Value);
                CurrentSection->EntryAdd(CurrentEntry);

                return true;
            }

            bool YAIP::SectionKeyValueSet(const std::string &Section, const std::string &Key, const char *Value)
            {
                std::string ValueString;
                if (nullptr != Value)
                {
                    ValueString = Value;
                }

                return SectionKeyValueSet(Section, Key, ValueString);
            }

            tListString YAIP::SectionListGet(void)
            {
                return m_Sections.ElementIdentifierList();
            }

            std::string YAIP::to_string(void) const
            {
                return m_Sections.to_string();
            }

            void YAIP::Accept(IIniVisitor &visitor) const
            {
                visitor.VisitDocumentBegin(*this);

                IniSectionList sections = m_Sections;
                for (const auto &sectionName : sections.ElementIdentifierList())
                {
                    if (auto section = sections.ElementFind(sectionName); section != nullptr)
                    {
                        section->Accept(visitor);
                    }
                }

                visitor.VisitDocumentEnd(*this);
            }

            bool YAIP::ParseFileContent(tListString FileContent)
            {
                std::ostringstream FileStream;
                for (auto const &Loop : FileContent)
                {
                    FileStream << Loop << '\n';
                }

                if (!m_ParserStrategy)
                {
                    return false;
                }

                return m_ParserStrategy->Parse(FileStream.str(), m_Sections);
            }
        }
    }
}
