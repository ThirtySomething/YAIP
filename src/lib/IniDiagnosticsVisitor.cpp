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
 * \file    IniDiagnosticsVisitor.cpp
 * \author  ThirtySomething
 * \brief   Visitor implementation collecting document diagnostics
 */
#include "IniDiagnosticsVisitor.h"

#include "IniEntry.h"
#include "IniSection.h"
#include "YAIP.h"
#include <sstream>

namespace
{
    std::string EscapeJsonString(const std::string &value)
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

namespace net
{
    namespace derpaul
    {
        namespace yaip
        {
            IniDiagnosticsVisitor::IniDiagnosticsVisitor()
                : m_CurrentSection(),
                  m_KeyOccurrenceCount(),
                  m_CurrentSectionIndex(0),
                  m_CurrentEntryIndex(0),
                  m_Diagnostics()
            {
            }

            void IniDiagnosticsVisitor::Analyze(const YAIP &document)
            {
                m_CurrentSection.clear();
                m_KeyOccurrenceCount.clear();
                m_CurrentSectionIndex = 0;
                m_CurrentEntryIndex = 0;
                m_Diagnostics.clear();

                document.Accept(*this);
            }

            const std::vector<IniDiagnostic> &IniDiagnosticsVisitor::DiagnosticsGet(void) const
            {
                return m_Diagnostics;
            }

            bool IniDiagnosticsVisitor::HasDiagnostics(void) const
            {
                return !m_Diagnostics.empty();
            }

            std::string IniDiagnosticsVisitor::ReportGet(void) const
            {
                std::ostringstream stream;

                for (std::size_t i = 0; i < m_Diagnostics.size(); ++i)
                {
                    if (i > 0)
                    {
                        stream << '\n';
                    }

                    stream << DiagnosticToString(m_Diagnostics[i]);
                }

                return stream.str();
            }

            std::string IniDiagnosticsVisitor::ReportJsonGet(void) const
            {
                std::ostringstream stream;
                stream << '[';

                for (std::size_t i = 0; i < m_Diagnostics.size(); ++i)
                {
                    if (i > 0)
                    {
                        stream << ',';
                    }

                    stream << DiagnosticToJson(m_Diagnostics[i]);
                }

                stream << ']';
                return stream.str();
            }

            const char *IniDiagnosticsVisitor::SeverityToString(const IniDiagnosticSeverity severity)
            {
                switch (severity)
                {
                case IniDiagnosticSeverity::Warning:
                    return "Warning";
                case IniDiagnosticSeverity::Error:
                    return "Error";
                default:
                    return "Unknown";
                }
            }

            const char *IniDiagnosticsVisitor::CodeToString(const IniDiagnosticCode code)
            {
                switch (code)
                {
                case IniDiagnosticCode::EmptySectionName:
                    return "EmptySectionName";
                case IniDiagnosticCode::DuplicateKey:
                    return "DuplicateKey";
                case IniDiagnosticCode::EmptyEntryValue:
                    return "EmptyEntryValue";
                default:
                    return "Unknown";
                }
            }

            std::string IniDiagnosticsVisitor::DiagnosticToString(const IniDiagnostic &diagnostic)
            {
                std::ostringstream stream;

                stream << '[' << SeverityToString(diagnostic.Severity) << ']'
                       << ' ' << CodeToString(diagnostic.Code)
                       << " section[" << diagnostic.SectionIndex << "]"
                       << " entry[" << diagnostic.EntryIndex << ']';

                if (!diagnostic.Section.empty())
                {
                    stream << " sectionName='" << diagnostic.Section << "'";
                }

                if (!diagnostic.Key.empty())
                {
                    stream << " key='" << diagnostic.Key << "'";
                }

                if (diagnostic.KeyOccurrenceInSection > 0)
                {
                    stream << " occurrence=" << diagnostic.KeyOccurrenceInSection;
                }

                stream << ": " << diagnostic.Message;

                return stream.str();
            }

            std::string IniDiagnosticsVisitor::DiagnosticToJson(const IniDiagnostic &diagnostic)
            {
                std::ostringstream stream;

                stream << '{'
                       << "\"severity\":\"" << EscapeJsonString(SeverityToString(diagnostic.Severity)) << "\","
                       << "\"code\":\"" << EscapeJsonString(CodeToString(diagnostic.Code)) << "\","
                       << "\"section\":\"" << EscapeJsonString(diagnostic.Section) << "\","
                       << "\"key\":\"" << EscapeJsonString(diagnostic.Key) << "\","
                       << "\"sectionIndex\":" << diagnostic.SectionIndex << ','
                       << "\"entryIndex\":" << diagnostic.EntryIndex << ','
                       << "\"keyOccurrenceInSection\":" << diagnostic.KeyOccurrenceInSection << ','
                       << "\"message\":\"" << EscapeJsonString(diagnostic.Message) << "\""
                       << '}';

                return stream.str();
            }

            void IniDiagnosticsVisitor::VisitDocumentBegin(const YAIP &document)
            {
                (void)document;
            }

            void IniDiagnosticsVisitor::VisitSectionBegin(const IniSection &section)
            {
                m_CurrentSection = section.ElementIdentifierGet();
                m_KeyOccurrenceCount.clear();
                m_CurrentEntryIndex = 0;

                const std::size_t sectionIndex = m_CurrentSectionIndex;
                ++m_CurrentSectionIndex;

                if (m_CurrentSection.empty() && !section.IsImplicitGlobal())
                {
                    m_Diagnostics.push_back({IniDiagnosticSeverity::Error,
                                             IniDiagnosticCode::EmptySectionName,
                                             m_CurrentSection,
                                             "",
                                             sectionIndex,
                                             0,
                                             0,
                                             "Section name is empty."});
                }
            }

            void IniDiagnosticsVisitor::VisitEntry(const IniEntry &entry)
            {
                const std::string key = entry.ElementIdentifierGet();
                const std::string value = entry.ElementValueGet();
                const std::size_t sectionIndex = m_CurrentSectionIndex - 1;
                const std::size_t entryIndex = m_CurrentEntryIndex;
                ++m_CurrentEntryIndex;

                int &occurrence = m_KeyOccurrenceCount[key];
                ++occurrence;
                if (occurrence > 1)
                {
                    m_Diagnostics.push_back({IniDiagnosticSeverity::Error,
                                             IniDiagnosticCode::DuplicateKey,
                                             m_CurrentSection,
                                             key,
                                             sectionIndex,
                                             entryIndex,
                                             static_cast<std::size_t>(occurrence),
                                             "Duplicate key in section."});
                }

                if (value.empty())
                {
                    m_Diagnostics.push_back({IniDiagnosticSeverity::Warning,
                                             IniDiagnosticCode::EmptyEntryValue,
                                             m_CurrentSection,
                                             key,
                                             sectionIndex,
                                             entryIndex,
                                             static_cast<std::size_t>(occurrence),
                                             "Entry value is empty."});
                }
            }

            void IniDiagnosticsVisitor::VisitSectionEnd(const IniSection &section)
            {
                (void)section;
            }

            void IniDiagnosticsVisitor::VisitDocumentEnd(const YAIP &document)
            {
                (void)document;
            }
        }
    }
}