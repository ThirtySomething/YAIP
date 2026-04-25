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

#ifndef _TEST_INIDOCUMENTBUILDER_H_
#define _TEST_INIDOCUMENTBUILDER_H_

#include "IniDocumentBuilder.h"
#include "YAIP.h"
#include "catch2/catch_all.hpp"
#include <string>

TEST_CASE("IniDocumentBuilder - empty build clears target", "[IniDocumentBuilder]")
{
    net::derpaul::yaip::YAIP ini;
    ini.SectionKeyValueSet("OldSection", "key", "value");

    net::derpaul::yaip::IniDocumentBuilder{}.build(ini);

    REQUIRE(ini.SectionListGet().empty());
}

TEST_CASE("IniDocumentBuilder - single section single entry", "[IniDocumentBuilder]")
{
    net::derpaul::yaip::YAIP ini;
    net::derpaul::yaip::IniDocumentBuilder{}
        .section("Network")
        .entry("host", "localhost")
        .build(ini);

    REQUIRE(ini.SectionListGet().size() == 1);
    REQUIRE(ini.SectionKeyValueGet("Network", "host", std::string{}) == "localhost");
}

TEST_CASE("IniDocumentBuilder - multiple sections", "[IniDocumentBuilder]")
{
    net::derpaul::yaip::YAIP ini;
    net::derpaul::yaip::IniDocumentBuilder{}
        .section("Database")
        .entry("host", "db.example.com")
        .entry("port", "5432")
        .section("Auth")
        .entry("user", "admin")
        .build(ini);

    auto sections = ini.SectionListGet();
    REQUIRE(sections.size() == 2);
    REQUIRE(ini.SectionKeyValueGet("Database", "host", std::string{}) == "db.example.com");
    REQUIRE(ini.SectionKeyValueGet("Database", "port", std::string{}) == "5432");
    REQUIRE(ini.SectionKeyValueGet("Auth", "user", std::string{}) == "admin");
}

TEST_CASE("IniDocumentBuilder - typed entry", "[IniDocumentBuilder]")
{
    net::derpaul::yaip::YAIP ini;
    net::derpaul::yaip::IniDocumentBuilder{}
        .section("Settings")
        .entry("count", 42)
        .entry("ratio", 3.14)
        .entry("flag", true)
        .build(ini);

    REQUIRE(ini.SectionKeyValueGet("Settings", "count", 0) == 42);
    REQUIRE(ini.SectionKeyValueGet("Settings", "flag", false) == true);
}

TEST_CASE("IniDocumentBuilder - revisit section appends entries", "[IniDocumentBuilder]")
{
    net::derpaul::yaip::YAIP ini;
    net::derpaul::yaip::IniDocumentBuilder{}
        .section("A")
        .entry("key1", "v1")
        .section("B")
        .entry("keyB", "vB")
        .section("A")
        .entry("key2", "v2")
        .build(ini);

    auto keys = ini.SectionKeyListGet("A");
    REQUIRE(keys.size() == 2);
    REQUIRE(ini.SectionKeyValueGet("A", "key1", std::string{}) == "v1");
    REQUIRE(ini.SectionKeyValueGet("A", "key2", std::string{}) == "v2");
}

#endif
