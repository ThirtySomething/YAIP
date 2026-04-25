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
 * \file    JsonIniExporterVisitor.cpp
 * \author  ThirtySomething
 * \brief   Visitor implementation exporting a YAIP document to JSON
 */
#include "JsonIniExporterVisitor.h"

#include "IniEntry.h"
#include "IniSection.h"
#include "YAIP.h"

namespace net
{
    namespace derpaul
    {
        namespace yaip
        {
            JsonIniExporterVisitor::JsonIniExporterVisitor()
                : m_Stream(), m_FirstSection(true), m_FirstEntry(true)
            {
            }

            std::string JsonIniExporterVisitor::Export(const YAIP &document)
            {
                m_Stream.str(std::string());
                m_Stream.clear();
                m_FirstSection = true;
                m_FirstEntry = true;

                document.Accept(*this);
                return m_Stream.str();
            }

            void JsonIniExporterVisitor::VisitDocumentBegin(const YAIP &document)
            {
                (void)document;
                m_Stream << "{";
            }

            void JsonIniExporterVisitor::VisitSectionBegin(const IniSection &section)
            {
                if (!m_FirstSection)
                {
                    m_Stream << ",";
                }
                m_FirstSection = false;
                m_FirstEntry = true;

                m_Stream << "\"" << EscapeJsonString(section.ElementIdentifierGet()) << "\":{";
            }

            void JsonIniExporterVisitor::VisitEntry(const IniEntry &entry)
            {
                if (!m_FirstEntry)
                {
                    m_Stream << ",";
                }
                m_FirstEntry = false;

                m_Stream << "\"" << EscapeJsonString(entry.ElementIdentifierGet()) << "\":"
                         << "\"" << EscapeJsonString(entry.ElementValueGet()) << "\"";
            }

            void JsonIniExporterVisitor::VisitSectionEnd(const IniSection &section)
            {
                (void)section;
                m_Stream << "}";
            }

            void JsonIniExporterVisitor::VisitDocumentEnd(const YAIP &document)
            {
                (void)document;
                m_Stream << "}";
            }

            std::string JsonIniExporterVisitor::EscapeJsonString(const std::string &value)
            {
                std::ostringstream escaped;
                for (const auto c : value)
                {
                    switch (c)
                    {
                    case '\\':
                        escaped << "\\\\";
                        break;
                    case '"':
                        escaped << "\\\"";
                        break;
                    case '\b':
                        escaped << "\\b";
                        break;
                    case '\f':
                        escaped << "\\f";
                        break;
                    case '\n':
                        escaped << "\\n";
                        break;
                    case '\r':
                        escaped << "\\r";
                        break;
                    case '\t':
                        escaped << "\\t";
                        break;
                    default:
                        escaped << c;
                        break;
                    }
                }
                return escaped.str();
            }
        }
    }
}