#include "YAIP++.h"
#include <iostream>
#include <fstream>

const std::regex YAIP::RegExSection("(\\s)*(\\[)(([a-zA-Z0-9])+)(\\])(.)*");
const std::regex YAIP::RegExKeyValue("(\\s)*(([a-zA-Z0-9\\.])+)(=)(([a-zA-Z0-9\\.\\+-])+)([#;])?(.)*");

YAIP::YAIP(void)
    :m_IniData()
{
}

YAIP::~YAIP(void)
{
}

void YAIP::INIFileLoad(std::string Filename)
{
    std::ifstream  IniFile;
    IniFile.open(Filename, std::ios::in);
    if (true == IniFile.is_open())
    {
        m_IniData.clear();
        std::string CurrentLine;
        tVectorString FileContent;
        while (std::getline(IniFile, CurrentLine))
        {
            FileContent.push_back(CurrentLine);
        }
        IniFile.close();
        ParseFileContent(FileContent);
    }
}

void YAIP::ParseFileContent(tVectorString &FileContent)
{
    std::string CurrentSection = "";
    std::string CurrentKey = "";
    std::string CurrentValue = "";
    tMapStringString CurrentSectionData;
    m_IniData[CurrentSection] = CurrentSectionData;

    for (size_t Loop = 0; Loop < FileContent.size(); Loop++)
    {
        std::string Line = FileContent.at(Loop);

        if (true == NewSection(Line, CurrentSection))
        {
            tMapStringString SectionData;
            m_IniData[CurrentSection] = SectionData;
        }
        if (true == NewKeyValue(Line, CurrentKey, CurrentValue))
        {
            m_IniData[CurrentSection].insert(std::make_pair(CurrentKey, CurrentValue));
        }
    }
}

bool YAIP::NewSection(const std::string &Line, std::string &Section)
{
    bool Success = false;
    std::smatch RegExpMatch;

    if (true == std::regex_search(Line, RegExpMatch, YAIP::RegExSection))
    {
        Section = RegExpMatch[3].str();
        Success = true;
    }

    return Success;
}

bool YAIP::NewKeyValue(const std::string &Line, std::string &Key, std::string &Value)
{
    bool Success = false;
    std::smatch RegExpMatch;

    if (true == std::regex_search(Line, RegExpMatch, YAIP::RegExKeyValue))
    {
        Key = RegExpMatch[2].str();
        Value = RegExpMatch[5].str();
        Success = true;
    }

    return Success;
}

tVectorString YAIP::GetSectionList(void)
{
    tVectorString SectionList;

    for (tMapMapStringString::iterator Loop = m_IniData.begin(); Loop != m_IniData.end(); ++Loop)
    {
        SectionList.push_back(Loop->first);
    }

    return SectionList;
}

tVectorString YAIP::GetSectionKeys(std::string Section)
{
    tVectorString KeyList;

    auto SectionDataRaw = m_IniData.find(Section);
    if (m_IniData.end() != SectionDataRaw)
    {
        tMapStringString SectionData = SectionDataRaw->second;
        for (tMapStringString::iterator Loop = SectionData.begin(); Loop != SectionData.end(); ++Loop)
        {
            KeyList.push_back(Loop->first);
        }
    }

    return KeyList;
}
