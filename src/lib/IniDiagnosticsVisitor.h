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
 * \file    IniDiagnosticsVisitor.h
 * \author  ThirtySomething
 * \brief   Visitor implementation collecting document diagnostics
 */
#ifndef _INIDIAGNOSTICSVISITOR_H_
#define _INIDIAGNOSTICSVISITOR_H_

#include "IIniVisitor.h"
#include "IniDiagnostic.h"
#include "IniDiagnosticCode.h"
#include "IniDiagnosticSeverity.h"
#include <string>
#include <unordered_map>
#include <vector>

namespace net
{
    namespace derpaul
    {
        namespace yaip
        {
            class IniDiagnosticsVisitor : public IIniVisitor
            {
            public:
                IniDiagnosticsVisitor();

                void Analyze(const YAIP &document);
                const std::vector<IniDiagnostic> &DiagnosticsGet(void) const;
                bool HasDiagnostics(void) const;
                std::string ReportGet(void) const;
                std::string ReportJsonGet(void) const;

                static const char *SeverityToString(const IniDiagnosticSeverity severity);
                static const char *CodeToString(const IniDiagnosticCode code);
                static std::string DiagnosticToString(const IniDiagnostic &diagnostic);
                static std::string DiagnosticToJson(const IniDiagnostic &diagnostic);

                virtual void VisitDocumentBegin(const YAIP &document) override;
                virtual void VisitSectionBegin(const IniSection &section) override;
                virtual void VisitEntry(const IniEntry &entry) override;
                virtual void VisitSectionEnd(const IniSection &section) override;
                virtual void VisitDocumentEnd(const YAIP &document) override;

            private:
                std::string m_CurrentSection;
                std::unordered_map<std::string, int> m_KeyOccurrenceCount;
                std::size_t m_CurrentSectionIndex;
                std::size_t m_CurrentEntryIndex;
                std::vector<IniDiagnostic> m_Diagnostics;
            };
        }
    }
}

#endif