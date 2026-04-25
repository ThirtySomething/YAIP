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
 * \file    JsonIniExporterVisitor.h
 * \author  ThirtySomething
 * \brief   Visitor implementation exporting a YAIP document to JSON
 */
#ifndef _JSONINIEXPORTERVISITOR_H_
#define _JSONINIEXPORTERVISITOR_H_

#include "IIniVisitor.h"
#include <sstream>
#include <string>

namespace net
{
    namespace derpaul
    {
        namespace yaip
        {
            class JsonIniExporterVisitor : public IIniVisitor
            {
            public:
                JsonIniExporterVisitor();

                std::string Export(const YAIP &document);

                virtual void VisitDocumentBegin(const YAIP &document) override;
                virtual void VisitSectionBegin(const IniSection &section) override;
                virtual void VisitEntry(const IniEntry &entry) override;
                virtual void VisitSectionEnd(const IniSection &section) override;
                virtual void VisitDocumentEnd(const YAIP &document) override;

            private:
                static std::string EscapeJsonString(const std::string &value);

                std::ostringstream m_Stream;
                bool m_FirstSection;
                bool m_FirstEntry;
            };
        }
    }
}

#endif