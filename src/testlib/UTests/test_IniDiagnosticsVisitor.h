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

int DiagnosticCount(const std::vector<net::derpaul::yaip::IniDiagnostic> &diagnostics, const net::derpaul::yaip::IniDiagnosticCode code)
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

const net::derpaul::yaip::IniDiagnostic *FindDiagnostic(const std::vector<net::derpaul::yaip::IniDiagnostic> &diagnostics, const net::derpaul::yaip::IniDiagnosticCode code)
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

TEST_CASE("IniDiagnosticsVisitor - clean document has no diagnostics", "[IniDiagnosticsVisitor]")
{
    net::derpaul::yaip::YAIP ini;
    net::derpaul::yaip::IniDocumentBuilder{}
        .section("Network")
        .entry("host", "localhost")
        .entry("port", "8080")
        .build(ini);

    net::derpaul::yaip::IniDiagnosticsVisitor diagnostics;
    diagnostics.Analyze(ini);

    REQUIRE(!diagnostics.HasDiagnostics());
    REQUIRE(diagnostics.DiagnosticsGet().empty());
}

TEST_CASE("IniDiagnosticsVisitor - empty section and empty value diagnostics", "[IniDiagnosticsVisitor]")
{
    net::derpaul::yaip::YAIP ini;
    net::derpaul::yaip::IniDocumentBuilder{}
        .section("")
        .entry("key", "")
        .build(ini);

    net::derpaul::yaip::IniDiagnosticsVisitor diagnostics;
    diagnostics.Analyze(ini);

    const auto &issues = diagnostics.DiagnosticsGet();
    REQUIRE(diagnostics.HasDiagnostics());
    REQUIRE(DiagnosticCount(issues, net::derpaul::yaip::IniDiagnosticCode::EmptySectionName) == 1);
    REQUIRE(DiagnosticCount(issues, net::derpaul::yaip::IniDiagnosticCode::EmptyEntryValue) == 1);

    const net::derpaul::yaip::IniDiagnostic *emptySection = FindDiagnostic(issues, net::derpaul::yaip::IniDiagnosticCode::EmptySectionName);
    REQUIRE(emptySection != nullptr);
    REQUIRE(emptySection->Severity == net::derpaul::yaip::IniDiagnosticSeverity::Error);
    REQUIRE(emptySection->SectionIndex == 0);
    REQUIRE(emptySection->EntryIndex == 0);

    const net::derpaul::yaip::IniDiagnostic *emptyValue = FindDiagnostic(issues, net::derpaul::yaip::IniDiagnosticCode::EmptyEntryValue);
    REQUIRE(emptyValue != nullptr);
    REQUIRE(emptyValue->Severity == net::derpaul::yaip::IniDiagnosticSeverity::Warning);
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

    net::derpaul::yaip::YAIP ini;
    REQUIRE(ini.INIFileLoad(iniFile));

    net::derpaul::yaip::IniDiagnosticsVisitor diagnostics;
    diagnostics.Analyze(ini);

    const auto &issues = diagnostics.DiagnosticsGet();
    REQUIRE(diagnostics.HasDiagnostics());
    REQUIRE(DiagnosticCount(issues, net::derpaul::yaip::IniDiagnosticCode::DuplicateKey) == 1);

    const net::derpaul::yaip::IniDiagnostic *duplicate = FindDiagnostic(issues, net::derpaul::yaip::IniDiagnosticCode::DuplicateKey);
    REQUIRE(duplicate != nullptr);
    REQUIRE(duplicate->Severity == net::derpaul::yaip::IniDiagnosticSeverity::Error);
    REQUIRE(duplicate->Section == "Section");
    REQUIRE(duplicate->Key == "dup");
    REQUIRE(duplicate->SectionIndex == 0);
    REQUIRE(duplicate->EntryIndex == 1);
    REQUIRE(duplicate->KeyOccurrenceInSection == 2);

    REQUIRE(ini.INIFileDelete(iniFile));
}

TEST_CASE("IniDiagnosticsVisitor - implicit global section is not treated as an empty section", "[IniDiagnosticsVisitor]")
{
    const std::string iniFile = "yaip_global_diagnostics.ini";
    {
        std::ofstream out(iniFile, std::ios::trunc);
        REQUIRE(out.is_open());
        out << "host = localhost" << std::endl;
        out << "empty =" << std::endl;
    }

    net::derpaul::yaip::YAIP ini;
    REQUIRE(ini.INIFileLoad(iniFile));

    net::derpaul::yaip::IniDiagnosticsVisitor diagnostics;
    diagnostics.Analyze(ini);

    const auto &issues = diagnostics.DiagnosticsGet();
    REQUIRE(DiagnosticCount(issues, net::derpaul::yaip::IniDiagnosticCode::EmptySectionName) == 0);
    REQUIRE(DiagnosticCount(issues, net::derpaul::yaip::IniDiagnosticCode::EmptyEntryValue) == 1);

    const net::derpaul::yaip::IniDiagnostic *emptyValue = FindDiagnostic(issues, net::derpaul::yaip::IniDiagnosticCode::EmptyEntryValue);
    REQUIRE(emptyValue != nullptr);
    REQUIRE(emptyValue->Section == "");
    REQUIRE(emptyValue->Key == "empty");

    REQUIRE(ini.INIFileDelete(iniFile));
}

TEST_CASE("IniDiagnosticsVisitor - formatting is stable", "[IniDiagnosticsVisitor]")
{
    net::derpaul::yaip::IniDiagnostic diagnostic{
        net::derpaul::yaip::IniDiagnosticSeverity::Error,
        net::derpaul::yaip::IniDiagnosticCode::DuplicateKey,
        "Main",
        "port",
        2,
        5,
        3,
        "Duplicate key in section."};

    REQUIRE(std::string(net::derpaul::yaip::IniDiagnosticsVisitor::SeverityToString(net::derpaul::yaip::IniDiagnosticSeverity::Warning)) == "Warning");
    REQUIRE(std::string(net::derpaul::yaip::IniDiagnosticsVisitor::SeverityToString(net::derpaul::yaip::IniDiagnosticSeverity::Error)) == "Error");
    REQUIRE(std::string(net::derpaul::yaip::IniDiagnosticsVisitor::CodeToString(net::derpaul::yaip::IniDiagnosticCode::DuplicateKey)) == "DuplicateKey");

    REQUIRE(net::derpaul::yaip::IniDiagnosticsVisitor::DiagnosticToString(diagnostic) ==
            "[Error] DuplicateKey section[2] entry[5] sectionName='Main' key='port' occurrence=3: Duplicate key in section.");

    REQUIRE(net::derpaul::yaip::IniDiagnosticsVisitor::DiagnosticToJson(diagnostic) ==
            "{\"severity\":\"Error\",\"code\":\"DuplicateKey\",\"section\":\"Main\",\"key\":\"port\",\"sectionIndex\":2,\"entryIndex\":5,\"keyOccurrenceInSection\":3,\"message\":\"Duplicate key in section.\"}");
}

TEST_CASE("IniDiagnosticsVisitor - report output is newline separated", "[IniDiagnosticsVisitor]")
{
    net::derpaul::yaip::YAIP ini;
    net::derpaul::yaip::IniDocumentBuilder{}
        .section("")
        .entry("empty", "")
        .build(ini);

    net::derpaul::yaip::IniDiagnosticsVisitor diagnostics;
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
