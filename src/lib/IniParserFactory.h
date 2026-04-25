//******************************************************************************
// Copyright 2016 ThirtySomething
//******************************************************************************

#ifndef _INIPARSERFACTORY_H_
#define _INIPARSERFACTORY_H_

#include "IIniParserStrategy.h"
#include "IniParserBackend.h"
#include <memory>

namespace net
{
    namespace derpaul
    {
        namespace yaip
        {
            class IniParserFactory
            {
            public:
                static std::unique_ptr<IIniParserStrategy> Create(IniParserBackend backend = IniParserBackend::Antlr);
            };
        }
    }
}

#endif