#pragma once

#include "YAIP++Data.h"
#include <sstream>

class YAIP
{
public:
    YAIP(void);
    virtual ~YAIP(void);

    void INIFileLoad(std::string Filename);
    tVectorString GetSectionList(void);
    tVectorString GetSectionKeys(std::string Section);

    template<typename VariableType>
    VariableType GetSectionKeyValue(std::string Section, std::string Key, VariableType Default)
    {
        VariableType ReturnValue = Default;

        auto SectionDataRaw = m_IniData.find(Section);
        if (m_IniData.end() != SectionDataRaw)
        {
            tMapStringString SectionData = SectionDataRaw->second;
            auto KeyDataRaw = SectionData.find(Key);
            if (SectionData.end() != KeyDataRaw)
            {
                std::stringstream StringStream(KeyDataRaw->second);
                StringStream >> ReturnValue;
            }
        }

        return ReturnValue;
    }

protected:
    tMapMapStringString m_IniData;

    static const std::regex RegExSection;
    static const std::regex RegExKeyValue;

    void ParseFileContent(tVectorString &FileContent);
    bool NewSection(const std::string &Line, std::string &Section);
    bool NewKeyValue(const std::string &Line, std::string &Key, std::string &Value);
};
