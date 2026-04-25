//******************************************************************************
// Copyright 2016 ThirtySomething
//******************************************************************************

#include "IniParserFactory.h"

#include "IniAntlrParser.h"
#include <memory>

namespace net
{
    namespace derpaul
    {
        namespace yaip
        {
            std::unique_ptr<IIniParserStrategy> IniParserFactory::Create(IniParserBackend backend)
            {
                switch (backend)
                {
                case IniParserBackend::Antlr:
                default:
                    return std::make_unique<IniAntlrParser>();
                }
            }
        }
    }
}