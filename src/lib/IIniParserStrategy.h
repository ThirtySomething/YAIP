//******************************************************************************
// Copyright 2016 ThirtySomething
//******************************************************************************

#ifndef _IINIPARSERSTRATEGY_H_
#define _IINIPARSERSTRATEGY_H_

#include "IniSectionList.h"
#include <string>

namespace net
{
    namespace derpaul
    {
        namespace yaip
        {
            class IIniParserStrategy
            {
            public:
                virtual ~IIniParserStrategy() = default;

                virtual bool Parse(const std::string &content, IniSectionList &sections) const = 0;
            };
        }
    }
}

#endif