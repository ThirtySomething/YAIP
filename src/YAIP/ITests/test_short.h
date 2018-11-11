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
#include <limits>

static const std::string S_FILE_INI_SHORT = "short.ini";
static const std::string S_SECTION_SHORT = "SECTION_SHORT";
static const std::string S_KEY_SHORT = "KEY_SHORT";
static const std::string S_KEY_INVALID_SHORT = "KEY_INVALID";
static const short S_VALUE_DEFAULT_SHORT = 0;

SCENARIO("Test YAIP with datatype [short]", "[net::derpaul::yaip::YAIP]")
{
	auto VALUE_SHORT = GENERATE(std::numeric_limits<short>::min(), std::numeric_limits<short>::max(), std::numeric_limits<short>::infinity());

	INFO("Current value [" << VALUE_SHORT << "]");

	GIVEN("An empty instance of the YAIP parser")
	{
		net::derpaul::yaip::YAIP sut;
		REQUIRE(sut.SectionListGet().empty());
		REQUIRE(sut.SectionKeyValueSet(S_SECTION_SHORT, S_KEY_SHORT, VALUE_SHORT));

		WHEN("Add a new section/key/value")
		{
			THEN("Count of section should be 1")
			{
				REQUIRE(false == sut.SectionListGet().empty());
				REQUIRE(1 == sut.SectionListGet().size());
				REQUIRE(1 == sut.SectionKeyListGet(S_SECTION_SHORT).size());
			}
		}

		WHEN("Save ini file")
		{
			REQUIRE(sut.INIFileSave(S_FILE_INI_SHORT));

			THEN("File exists")
			{
				REQUIRE(sut.INIFileExist(S_FILE_INI_SHORT));
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
			REQUIRE(sut.INIFileExist(S_FILE_INI_SHORT));
			REQUIRE(sut.INIFileLoad(S_FILE_INI_SHORT));

			THEN("What you save is what you get")
			{
				auto SectionList = sut.SectionListGet();
				auto SectionKeyList = sut.SectionKeyListGet(S_SECTION_SHORT);

				REQUIRE(1 == SectionList.size());
				REQUIRE(1 == SectionKeyList.size());

				short ini_value = sut.SectionKeyValueGet(S_SECTION_SHORT, S_KEY_SHORT, S_VALUE_DEFAULT_SHORT);
				REQUIRE(VALUE_SHORT == ini_value);
			}
		}

		WHEN("Read from invalid key")
		{
			short ini_value = sut.SectionKeyValueGet(S_SECTION_SHORT, S_KEY_INVALID_SHORT, S_VALUE_DEFAULT_SHORT);

			THEN("We get the default value")
			{
				REQUIRE(S_VALUE_DEFAULT_SHORT == ini_value);
			}
		}

		WHEN("Cleanup and delete ini file")
		{
			REQUIRE(sut.INIFileExist(S_FILE_INI_SHORT));
			REQUIRE(sut.INIFileDelete(S_FILE_INI_SHORT));

			THEN("When the ini file is gone")
			{
				REQUIRE(false == sut.INIFileExist(S_FILE_INI_SHORT));
			}
		}
	}
}
