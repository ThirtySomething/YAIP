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

#pragma once

#include "catch2\catch.hpp"
#include "YAIP.h"
#include <string>
#include <limits>
#include <vector>

static const std::string S_FILE_INI = "yaip.ini";
static const std::string S_SECTION = "SECTION";
static const std::string S_KEY = "KEY";
static const std::string S_KEY_INVALID = "KEY_INVALID";

template <typename T>
void test_yaip(const std::string &DataType, T Value, T ValueDefault)
{
	INFO("Current value [" << DataType << "]");

	GIVEN("An empty instance of the YAIP parser")
	{
		net::derpaul::yaip::YAIP sut;
		REQUIRE(sut.SectionListGet().empty());
		REQUIRE(sut.SectionKeyValueSet(S_SECTION, S_KEY, Value));

		WHEN("Add a new section/key/value")
		{
			THEN("Count of section should be 1")
			{
				REQUIRE(false == sut.SectionListGet().empty());
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
				REQUIRE(ValueDefault == ini_value);
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
				REQUIRE(Value == ini_value);
			}
		}

		WHEN("Read from invalid key")
		{
			T ini_value = sut.SectionKeyValueGet(S_SECTION, S_KEY_INVALID, ValueDefault);

			THEN("We get the default value")
			{
				REQUIRE(ValueDefault == ini_value);
			}
		}

		WHEN("Cleanup and delete ini file")
		{
			REQUIRE(sut.INIFileExist(S_FILE_INI));
			REQUIRE(sut.INIFileDelete(S_FILE_INI));

			THEN("When the ini file is gone")
			{
				REQUIRE(false == sut.INIFileExist(S_FILE_INI));
			}
		}
	}
}

SCENARIO("Test YAIP with datatype [string]", "[net::derpaul::yaip::YAIP]")
{
	// Test with std::string
	std::string DataTypeString = "std::string";
	std::string DataTypeStringValue = "ABCDEFGHIJKLMNOPQRSTUVXYZ abcdefghijklmnopqrstuvxyz () 0123456789 ., _ +- |";
	std::string DataTypeStringDefault = "-=>DEFAULT<=-";
	test_yaip<std::string>(DataTypeString, DataTypeStringValue, DataTypeStringDefault);

	// Test with bool
	std::string DataTypeBool = "bool";
	test_yaip<bool>(DataTypeBool, std::numeric_limits<bool>::min(), true);
	test_yaip<bool>(DataTypeBool, std::numeric_limits<bool>::max(), true);
	test_yaip<bool>(DataTypeBool, std::numeric_limits<bool>::infinity(), true);

	// Test with char
	std::string DataTypeChar = "char";
	test_yaip<char>(DataTypeChar, std::numeric_limits<char>::min(), 'Y');
	test_yaip<char>(DataTypeChar, std::numeric_limits<char>::max(), 'Y');
	test_yaip<char>(DataTypeChar, std::numeric_limits<char>::infinity(), 'Y');
}
