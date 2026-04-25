//******************************************************************************
// Copyright 2016 ThirtySomething
//******************************************************************************

#ifndef _INIANTLRPARSER_H_
#define _INIANTLRPARSER_H_

#include "IniSectionList.h"
#include <string>

namespace net
{
    namespace derpaul
    {
        namespace yaip
        {
            class IniAntlrParser
            {
            public:
                static bool Parse(const std::string &content, IniSectionList &sections);
            };
        }
    }
}

#endif