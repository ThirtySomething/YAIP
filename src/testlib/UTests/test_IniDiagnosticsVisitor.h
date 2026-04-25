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

#ifndef _TEST_INIDIAGNOSTICSVISITOR_H_
#define _TEST_INIDIAGNOSTICSVISITOR_H_

#include "IniDiagnosticsVisitor.h"
#include "IniDocumentBuilder.h"
#include "YAIP.h"
#include "catch2/catch_all.hpp"
#include <fstream>
#include <string>

using namespace net::derpaul::yaip;

namespace
{
    int DiagnosticCount(const std::vector<IniDiagnostic> &diagnostics, const IniDiagnosticCode code)
    {
        int count = 0;
        for (const auto &diagnostic : diagnostics)
        {
            if (diagnostic.Code == code)
            {
                ++count;
            }
        }
        return count;
    }

    const IniDiagnostic *FindDiagnostic(const std::vector<IniDiagnostic> &diagnostics, const IniDiagnosticCode code)
    {
        for (const auto &diagnostic : diagnostics)
        {
            if (diagnostic.Code == code)
            {
                return &diagnostic;
            }
        }

        return nullptr;
    }
}

TEST_CASE("IniDiagnosticsVisitor - clean document has no diagnostics", "[IniDiagnosticsVisitor]")
{
    YAIP ini;
    IniDocumentBuilder{}
        .section("Network")
        .entry("host", "localhost")
        .entry("port", "8080")
        .build(ini);

    IniDiagnosticsVisitor diagnostics;
    diagnostics.Analyze(ini);

    REQUIRE(!diagnostics.HasDiagnostics());
    REQUIRE(diagnostics.DiagnosticsGet().empty());
}

TEST_CASE("IniDiagnosticsVisitor - empty section and empty value diagnostics", "[IniDiagnosticsVisitor]")
{
    YAIP ini;
    IniDocumentBuilder{}
        .section("")
        .entry("key", "")
        .build(ini);

    IniDiagnosticsVisitor diagnostics;
    diagnostics.Analyze(ini);

    const auto &issues = diagnostics.DiagnosticsGet();
    REQUIRE(diagnostics.HasDiagnostics());
    REQUIRE(DiagnosticCount(issues, IniDiagnosticCode::EmptySectionName) == 1);
    REQUIRE(DiagnosticCount(issues, IniDiagnosticCode::EmptyEntryValue) == 1);

    const IniDiagnostic *emptySection = FindDiagnostic(issues, IniDiagnosticCode::EmptySectionName);
    REQUIRE(emptySection != nullptr);
    REQUIRE(emptySection->Severity == IniDiagnosticSeverity::Error);
    REQUIRE(emptySection->SectionIndex == 0);
    REQUIRE(emptySection->EntryIndex == 0);

    const IniDiagnostic *emptyValue = FindDiagnostic(issues, IniDiagnosticCode::EmptyEntryValue);
    REQUIRE(emptyValue != nullptr);
    REQUIRE(emptyValue->Severity == IniDiagnosticSeverity::Warning);
    REQUIRE(emptyValue->SectionIndex == 0);
    REQUIRE(emptyValue->EntryIndex == 0);
}

TEST_CASE("IniDiagnosticsVisitor - duplicate keys loaded from file", "[IniDiagnosticsVisitor]")
{
    const std::string iniFile = "yaip_diagnostics.ini";
    {
        std::ofstream out(iniFile, std::ios::trunc);
        REQUIRE(out.is_open());
        out << "[Section]" << std::endl;
        out << "dup = first" << std::endl;
        out << "dup = second" << std::endl;
    }

    YAIP ini;
    REQUIRE(ini.INIFileLoad(iniFile));

    IniDiagnosticsVisitor diagnostics;
    diagnostics.Analyze(ini);

    const auto &issues = diagnostics.DiagnosticsGet();
    REQUIRE(diagnostics.HasDiagnostics());
    REQUIRE(DiagnosticCount(issues, IniDiagnosticCode::DuplicateKey) == 1);

    const IniDiagnostic *duplicate = FindDiagnostic(issues, IniDiagnosticCode::DuplicateKey);
    REQUIRE(duplicate != nullptr);
    REQUIRE(duplicate->Severity == IniDiagnosticSeverity::Error);
    REQUIRE(duplicate->Section == "Section");
    REQUIRE(duplicate->Key == "dup");
    REQUIRE(duplicate->SectionIndex == 0);
    REQUIRE(duplicate->EntryIndex == 1);
    REQUIRE(duplicate->KeyOccurrenceInSection == 2);

    REQUIRE(ini.INIFileDelete(iniFile));
}

TEST_CASE("IniDiagnosticsVisitor - formatting is stable", "[IniDiagnosticsVisitor]")
{
    IniDiagnostic diagnostic{
        IniDiagnosticSeverity::Error,
        IniDiagnosticCode::DuplicateKey,
        "Main",
        "port",
        2,
        5,
        3,
        "Duplicate key in section."};

    REQUIRE(std::string(IniDiagnosticsVisitor::SeverityToString(IniDiagnosticSeverity::Warning)) == "Warning");
    REQUIRE(std::string(IniDiagnosticsVisitor::SeverityToString(IniDiagnosticSeverity::Error)) == "Error");
    REQUIRE(std::string(IniDiagnosticsVisitor::CodeToString(IniDiagnosticCode::DuplicateKey)) == "DuplicateKey");

    REQUIRE(IniDiagnosticsVisitor::DiagnosticToString(diagnostic) ==
            "[Error] DuplicateKey section[2] entry[5] sectionName='Main' key='port' occurrence=3: Duplicate key in section.");

    REQUIRE(IniDiagnosticsVisitor::DiagnosticToJson(diagnostic) ==
            "{\"severity\":\"Error\",\"code\":\"DuplicateKey\",\"section\":\"Main\",\"key\":\"port\",\"sectionIndex\":2,\"entryIndex\":5,\"keyOccurrenceInSection\":3,\"message\":\"Duplicate key in section.\"}");
}

TEST_CASE("IniDiagnosticsVisitor - report output is newline separated", "[IniDiagnosticsVisitor]")
{
    YAIP ini;
    IniDocumentBuilder{}
        .section("")
        .entry("empty", "")
        .build(ini);

    IniDiagnosticsVisitor diagnostics;
    diagnostics.Analyze(ini);

    REQUIRE(diagnostics.DiagnosticsGet().size() == 2);
    REQUIRE(diagnostics.ReportGet() ==
            "[Error] EmptySectionName section[0] entry[0]: Section name is empty.\n"
            "[Warning] EmptyEntryValue section[0] entry[0] key='empty' occurrence=1: Entry value is empty.");

    REQUIRE(diagnostics.ReportJsonGet() ==
            "[{\"severity\":\"Error\",\"code\":\"EmptySectionName\",\"section\":\"\",\"key\":\"\",\"sectionIndex\":0,\"entryIndex\":0,\"keyOccurrenceInSection\":0,\"message\":\"Section name is empty.\"},"
            "{\"severity\":\"Warning\",\"code\":\"EmptyEntryValue\",\"section\":\"\",\"key\":\"empty\",\"sectionIndex\":0,\"entryIndex\":0,\"keyOccurrenceInSection\":1,\"message\":\"Entry value is empty.\"}]");
}

#endif