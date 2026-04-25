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

using namespace net::derpaul::yaip;

TEST_CASE("JsonIniExporterVisitor - exports empty document", "[JsonIniExporterVisitor]")
{
    YAIP ini;
    JsonIniExporterVisitor exporter;

    REQUIRE(exporter.Export(ini) == "{}");
}

TEST_CASE("JsonIniExporterVisitor - exports sections and entries", "[JsonIniExporterVisitor]")
{
    YAIP ini;
    IniDocumentBuilder{}
        .section("Network")
        .entry("host", "localhost")
        .entry("port", 8080)
        .section("Auth")
        .entry("user", "admin")
        .build(ini);

    JsonIniExporterVisitor exporter;
    REQUIRE(exporter.Export(ini) == "{\"Network\":{\"host\":\"localhost\",\"port\":\"8080\"},\"Auth\":{\"user\":\"admin\"}}");
}

TEST_CASE("JsonIniExporterVisitor - escapes JSON characters", "[JsonIniExporterVisitor]")
{
    YAIP ini;
    IniDocumentBuilder{}
        .section("A\"B")
        .entry("path", "C:\\\\bin\\\"app\"")
        .entry("tab", "a\tb")
        .build(ini);

    JsonIniExporterVisitor exporter;
    REQUIRE(exporter.Export(ini) == "{\"A\\\"B\":{\"path\":\"C:\\\\\\\\bin\\\\\\\"app\\\"\",\"tab\":\"a\\tb\"}}");
}

#endif