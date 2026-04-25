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

#ifndef _TEST_YAIP_H_
#define _TEST_YAIP_H_

#include "YAIP.h"
#include "catch2/catch_all.hpp"
#include <fstream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

static const std::string S_FILE_INI = "yaip.ini";
static const std::string S_SECTION = "SECTION";
static const std::string S_KEY = "KEY";
static const std::string S_KEY_INVALID = "KEY_INVALID";

template <typename T>
T GetDefaultValue(void);

template <>
bool GetDefaultValue<bool>(void)
{
    return true;
}

template <>
char GetDefaultValue<char>(void)
{
    return 'Y';
}

template <>
double GetDefaultValue<double>(void)
{
    return 0.0;
}

template <>
float GetDefaultValue<float>(void)
{
    return 0.0f;
}

template <>
int GetDefaultValue<int>(void)
{
    return 0;
}

template <>
long GetDefaultValue<long>(void)
{
    return 0L;
}

template <>
short GetDefaultValue<short>(void)
{
    return 0;
}

template <>
std::string GetDefaultValue<std::string>(void)
{
    return "-=>DEFAULT<=-";
}

template <>
unsigned char GetDefaultValue<unsigned char>(void)
{
    return 'Y';
}

template <>
unsigned int GetDefaultValue<unsigned int>(void)
{
    return 0;
}

template <>
unsigned long GetDefaultValue<unsigned long>(void)
{
    return 0L;
}

template <>
unsigned short GetDefaultValue<unsigned short>(void)
{
    return 0;
}

template <typename T>
void CompareForEqual(const T &ValueLeft, const T &ValueRight)
{
    REQUIRE(ValueLeft == ValueRight);
}

template <>
void CompareForEqual<double>(const double &ValueLeft, const double &ValueRight)
{
    REQUIRE(ValueLeft == Catch::Approx(ValueRight));
}

template <>
void CompareForEqual<float>(const float &ValueLeft, const float &ValueRight)
{
    REQUIRE(ValueLeft == Catch::Approx(ValueRight));
}

template <typename T>
void test_yaip(T Value)
{
    T ValueDefault = GetDefaultValue<T>();
    GIVEN("An empty instance of the YAIP parser")
    {
        net::derpaul::yaip::YAIP sut;
        REQUIRE(sut.SectionListGet().empty());
        REQUIRE(sut.SectionKeyValueSet(S_SECTION, S_KEY, Value));

        WHEN("Add a new section/key/value")
        {
            THEN("Count of section should be 1")
            {
                REQUIRE(!sut.SectionListGet().empty());
                REQUIRE(1 == sut.SectionListGet().size());
                REQUIRE(1 == sut.SectionKeyListGet(S_SECTION).size());
            }
        }

        WHEN("Save ini file")
        {
            REQUIRE(sut.INIFileSave(S_FILE_INI));

            THEN("File exists")
            {
                REQUIRE(sut.INIFileExist(S_FILE_INI));
            }
        }

        WHEN("Set value of key to empty")
        {
            REQUIRE(sut.SectionKeyValueClear(S_SECTION, S_KEY));

            THEN("Read value should return default")
            {
                T ini_value = sut.SectionKeyValueGet(S_SECTION, S_KEY, ValueDefault);
                CompareForEqual(ValueDefault, ini_value);
            }
        }

        WHEN("Clear internal data")
        {
            sut.Clear();

            THEN("Section list should be empty")
            {
                REQUIRE(sut.SectionListGet().empty());
            }
        }

        WHEN("Reload from ini file")
        {
            REQUIRE(sut.INIFileExist(S_FILE_INI));
            REQUIRE(sut.INIFileLoad(S_FILE_INI));

            THEN("What you save is what you get")
            {
                auto SectionList = sut.SectionListGet();
                auto SectionKeyList = sut.SectionKeyListGet(S_SECTION);

                REQUIRE(1 == SectionList.size());
                REQUIRE(1 == SectionKeyList.size());

                T ini_value = sut.SectionKeyValueGet(S_SECTION, S_KEY, ValueDefault);
                CompareForEqual(Value, ini_value);
            }
        }

        WHEN("Read from invalid key")
        {
            T ini_value = sut.SectionKeyValueGet(S_SECTION, S_KEY_INVALID, ValueDefault);

            THEN("We get the default value")
            {
                CompareForEqual(ValueDefault, ini_value);
            }
        }

        WHEN("Delete key")
        {
            REQUIRE(sut.SectionKeyKill(S_SECTION, S_KEY));

            THEN("No entries, no section")
            {
                auto SectionList = sut.SectionListGet();
                auto SectionKeyList = sut.SectionKeyListGet(S_SECTION);

                REQUIRE(0 == SectionList.size());
                REQUIRE(0 == SectionKeyList.size());

                T ini_value = sut.SectionKeyValueGet(S_SECTION, S_KEY, ValueDefault);
                CompareForEqual(ValueDefault, ini_value);
            }
        }

        WHEN("Cleanup and delete ini file")
        {
            REQUIRE(sut.INIFileExist(S_FILE_INI));
            REQUIRE(sut.INIFileDelete(S_FILE_INI));

            THEN("When the ini file is gone")
            {
                REQUIRE(!sut.INIFileExist(S_FILE_INI));
            }
        }
    }
}

TEMPLATE_TEST_CASE("Test YAIP with datatypes except string", "[YAIP]", bool, char, double, float, int, long, short, unsigned char, unsigned int, unsigned long, unsigned short)
{
    auto VALUE = GENERATE(std::numeric_limits<TestType>::min(), std::numeric_limits<TestType>::max(), std::numeric_limits<TestType>::infinity());

    test_yaip<TestType>(VALUE);
}

TEST_CASE("Test YAIP with datatype string", "[YAIP]")
{
    std::string testString("ABCDEFGHIJKLMNOPQRSTUVXYZ abcdefghijklmnopqrstuvxyz () 0123456789 ., _ +- |");
    test_yaip<std::string>(testString);
}

TEST_CASE("Test sorting of INI file", "[YAIP]")
{
    net::derpaul::yaip::YAIP sut;

    sut.Clear();

    sut.SectionKeyValueSet("Section005", "key02", "kadabra");
    sut.SectionKeyValueSet("Section005", "key03", "trois");
    sut.SectionKeyValueSet("Section005", "key01", "abra");

    sut.SectionKeyValueSet("Section001", "entry02", "kadabra");
    sut.SectionKeyValueSet("Section001", "entry01", "trois");
    sut.SectionKeyValueSet("Section001", "entry03", "abra");

    sut.SectionKeyValueSet("Section003", "name01", "blubb");
    sut.SectionKeyValueSet("Section003", "name05", "value");
    sut.SectionKeyValueSet("Section003", "name02", "test");
    sut.SectionKeyValueSet("Section003", "name04", "text");
    sut.SectionKeyValueSet("Section003", "name03", "secret");

    sut.SectionKeyValueSet("Section002", "foo", "foo");
    sut.SectionKeyValueSet("Section002", "baz", "baz");
    sut.SectionKeyValueSet("Section002", "wtf", "ftw");
    sut.SectionKeyValueSet("Section002", "bar", "bar");

    sut.SectionKeyValueSet("Section004", "yellow", "color");
    sut.SectionKeyValueSet("Section004", "bird", "blackbird");
    sut.SectionKeyValueSet("Section004", "porsche", "kind of sportswagon");

    std::string INIUnsorted = sut.to_string();
    std::string INIExpectedUnSorted = "[Section005]\nkey02 = kadabra\nkey03 = trois\nkey01 = abra\n\n[Section001]\nentry02 = kadabra\nentry01 = trois\nentry03 = abra\n\n[Section003]\nname01 = blubb\nname05 = value\nname02 = test\nname04 = text\nname03 = secret\n\n[Section002]\nfoo = foo\nbaz = baz\nwtf = ftw\nbar = bar\n\n[Section004]\nyellow = color\nbird = blackbird\nporsche = kind of sportswagon\n\n";

    REQUIRE(!sut.INIFileExist(S_FILE_INI));
    REQUIRE(sut.INIFileSave(S_FILE_INI));
    REQUIRE(sut.INIFileExist(S_FILE_INI));
    REQUIRE(0 == INIUnsorted.compare(INIExpectedUnSorted));

    std::string INISorted = sut.to_string();
    std::string INIExpectedSorted = "[Section001]\nentry01 = trois\nentry02 = kadabra\nentry03 = abra\n\n[Section002]\nbar = bar\nbaz = baz\nfoo = foo\nwtf = ftw\n\n[Section003]\nname01 = blubb\nname02 = test\nname03 = secret\nname04 = text\nname05 = value\n\n[Section004]\nbird = blackbird\nporsche = kind of sportswagon\nyellow = color\n\n[Section005]\nkey01 = abra\nkey02 = kadabra\nkey03 = trois\n\n";
    REQUIRE(0 != INIUnsorted.compare(INISorted));
    REQUIRE(0 == INISorted.compare(INIExpectedSorted));

    sut.INIFileDelete(S_FILE_INI);
    REQUIRE(!sut.INIFileExist(S_FILE_INI));
}

TEST_CASE("Test C-string literal values and empty-value roundtrip", "[YAIP]")
{
    net::derpaul::yaip::YAIP sut;

    REQUIRE(sut.SectionKeyValueSet("Main", "Literal", "literal-value"));
    REQUIRE("literal-value" == sut.SectionKeyValueGet("Main", "Literal", "default"));

    REQUIRE(sut.SectionKeyValueSet("Main", "Empty", "value"));
    REQUIRE(sut.SectionKeyValueClear("Main", "Empty"));
    REQUIRE(sut.INIFileSave(S_FILE_INI));

    net::derpaul::yaip::YAIP reload;
    REQUIRE(reload.INIFileLoad(S_FILE_INI));
    REQUIRE("fallback" == reload.SectionKeyValueGet("Main", "Empty", "fallback"));
    REQUIRE(reload.SectionKeyListGet("Main").size() == 2);

    REQUIRE(reload.INIFileDelete(S_FILE_INI));
}

TEST_CASE("Test sectionless entries are loaded into the global scope", "[YAIP]")
{
    const std::string iniFile = "yaip_global_entries.ini";
    {
        std::ofstream out(iniFile, std::ios::trunc);
        REQUIRE(out.is_open());
        out << "host = localhost\n";
        out << "port = 8080\n";
        out << "[Network]\n";
        out << "mode = tcp\n";
    }

    net::derpaul::yaip::YAIP sut;
    REQUIRE(sut.INIFileLoad(iniFile));

    REQUIRE(sut.SectionKeyValueGet("", "host", std::string()) == "localhost");
    REQUIRE(sut.SectionKeyValueGet("", "port", std::string()) == "8080");
    REQUIRE(sut.SectionKeyValueGet("Network", "mode", std::string()) == "tcp");

    REQUIRE(sut.INIFileSave(iniFile));

    std::ifstream in(iniFile);
    REQUIRE(in.is_open());

    std::ostringstream saved;
    saved << in.rdbuf();

    const std::string savedIni = saved.str();
    REQUIRE(savedIni.find("[]") == std::string::npos);
    REQUIRE(savedIni.find("host = localhost") != std::string::npos);
    REQUIRE(savedIni.find("port = 8080") != std::string::npos);
    REQUIRE(savedIni.find("[Network]") != std::string::npos);
    REQUIRE(savedIni.find("host = localhost") < savedIni.find("[Network]"));

    REQUIRE(sut.INIFileDelete(iniFile));
}

TEST_CASE("At most one nameless section exists regardless of how entries are added", "[YAIP]")
{
    net::derpaul::yaip::YAIP sut;

    REQUIRE(sut.SectionKeyValueSet("", "key1", "value1"));
    REQUIRE(sut.SectionKeyValueSet("", "key2", "value2"));

    auto sections = sut.SectionListGet();
    int namelessCount = 0;
    for (const auto &name : sections)
    {
        if (name.empty())
        {
            ++namelessCount;
        }
    }
    REQUIRE(namelessCount <= 1);
    REQUIRE(sut.SectionKeyValueGet("", "key1", std::string()) == "value1");
    REQUIRE(sut.SectionKeyValueGet("", "key2", std::string()) == "value2");
}

#endif
