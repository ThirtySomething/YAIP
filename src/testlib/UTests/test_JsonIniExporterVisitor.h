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

#ifndef _TEST_JSONINIEXPORTERVISITOR_H_
#define _TEST_JSONINIEXPORTERVISITOR_H_

#include "IniDocumentBuilder.h"
#include "JsonIniExporterVisitor.h"
#include "YAIP.h"
#include "catch2/catch_all.hpp"
#include <fstream>

TEST_CASE("JsonIniExporterVisitor - exports empty document", "[JsonIniExporterVisitor]")
{
    net::derpaul::yaip::YAIP ini;
    net::derpaul::yaip::JsonIniExporterVisitor exporter;

    REQUIRE(exporter.Export(ini) == "{}");
}

TEST_CASE("JsonIniExporterVisitor - exports sections and entries", "[JsonIniExporterVisitor]")
{
    net::derpaul::yaip::YAIP ini;
    net::derpaul::yaip::IniDocumentBuilder{}
        .section("Network")
        .entry("host", "localhost")
        .entry("port", 8080)
        .section("Auth")
        .entry("user", "admin")
        .build(ini);

    net::derpaul::yaip::JsonIniExporterVisitor exporter;
    REQUIRE(exporter.Export(ini) == "{\"Network\":{\"host\":\"localhost\",\"port\":\"8080\"},\"Auth\":{\"user\":\"admin\"}}");
}

TEST_CASE("JsonIniExporterVisitor - escapes JSON characters", "[JsonIniExporterVisitor]")
{
    net::derpaul::yaip::YAIP ini;
    net::derpaul::yaip::IniDocumentBuilder{}
        .section("A\"B")
        .entry("path", "C:\\\\bin\\\"app\"")
        .entry("tab", "a\tb")
        .build(ini);

    net::derpaul::yaip::JsonIniExporterVisitor exporter;
    REQUIRE(exporter.Export(ini) == "{\"A\\\"B\":{\"path\":\"C:\\\\\\\\bin\\\\\\\"app\\\"\",\"tab\":\"a\\tb\"}}");
}

TEST_CASE("JsonIniExporterVisitor - flattens implicit global section entries", "[JsonIniExporterVisitor]")
{
    const std::string iniFile = "yaip_global_json.ini";
    {
        std::ofstream out(iniFile, std::ios::trunc);
        REQUIRE(out.is_open());
        out << "host = localhost\n";
        out << "[Network]\n";
        out << "port = 8080\n";
    }

    net::derpaul::yaip::YAIP ini;
    REQUIRE(ini.INIFileLoad(iniFile));

    net::derpaul::yaip::JsonIniExporterVisitor exporter;
    REQUIRE(exporter.Export(ini) == "{\"host\":\"localhost\",\"Network\":{\"port\":\"8080\"}}");

    REQUIRE(ini.INIFileDelete(iniFile));
}

#endif
