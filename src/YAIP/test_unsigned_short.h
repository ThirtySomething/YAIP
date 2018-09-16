//******************************************************************************
// Copyright 2016 ThirtySomething
//******************************************************************************
// This file is part of YAIP++.
//
// YAIP++ is free software: you can redistribute it and/or modify it under the
// terms of the GNU Lesser General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// YAIP++ is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
// more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with YAIP++. If not, see <http://www.gnu.org/licenses/>.
//******************************************************************************

#pragma once

#include "./../../externals/Catch2/single_include/Catch2/catch.hpp"
#include "YAIP++.h"
#include <limits>

static const std::string S_FILE_INI_UNSIGNED_SHORT = "unsignedshort.ini";
static const std::string S_SECTION_UNSIGNED_SHORT = "SECTION_UNSIGNED_SHORT";
static const std::string S_KEY_UNSIGNED_SHORT = "KEY_UNSIGNED_SHORT";
static const std::string S_KEY_INVALID_UNSIGNED_SHORT = "KEY_INVALID";
static const unsigned short S_VALUE_DEFAULT_UNSIGNED_SHORT = 0;

SCENARIO("Processing of datatype [unsigned short]", "[net::derpaul::yaip::YAIP]")
{
	auto VALUE_UNSIGNED_SHORT = GENERATE(std::numeric_limits<unsigned short>::min(), std::numeric_limits<unsigned short>::max(), std::numeric_limits<unsigned short>::infinity());

	INFO("Current value [" << VALUE_UNSIGNED_SHORT << "]");

	GIVEN("An empty instance of the YAIP parser")
	{
		net::derpaul::yaip::YAIP sut;
		REQUIRE(true == sut.SectionListGet().empty());
		REQUIRE(true == sut.SectionKeyValueSet(S_SECTION_UNSIGNED_SHORT, S_KEY_UNSIGNED_SHORT, VALUE_UNSIGNED_SHORT));

		WHEN("Add a new section/key/value")
		{
			THEN("Count of section should be 1")
			{
				REQUIRE(false == sut.SectionListGet().empty());
				REQUIRE(1 == sut.SectionListGet().size());
				REQUIRE(1 == sut.SectionKeyListGet(S_SECTION_UNSIGNED_SHORT).size());
			}
		}

		WHEN("Save ini file")
		{
			REQUIRE(true == sut.INIFileSave(S_FILE_INI_UNSIGNED_SHORT));

			THEN("File exists")
			{
				REQUIRE(true == sut.INIFileExist(S_FILE_INI_UNSIGNED_SHORT));
			}
		}

		WHEN("Clear internal data")
		{
			sut.Clear();

			THEN("Section list should be empty")
			{
				REQUIRE(true == sut.SectionListGet().empty());
			}
		}

		WHEN("Reload from ini file")
		{
			REQUIRE(true == sut.INIFileExist(S_FILE_INI_UNSIGNED_SHORT));
			REQUIRE(true == sut.INIFileLoad(S_FILE_INI_UNSIGNED_SHORT));

			THEN("What you save is what you get")
			{
				auto SectionList = sut.SectionListGet();
				auto SectionKeyList = sut.SectionKeyListGet(S_SECTION_UNSIGNED_SHORT);

				REQUIRE(1 == SectionList.size());
				REQUIRE(1 == SectionKeyList.size());

				unsigned short ini_value= sut.SectionKeyValueGet(S_SECTION_UNSIGNED_SHORT, S_KEY_UNSIGNED_SHORT, S_VALUE_DEFAULT_UNSIGNED_SHORT);
				REQUIRE(VALUE_UNSIGNED_SHORT == ini_value);
			}
		}

		WHEN("Read from invalid key")
		{
			unsigned short ini_value = sut.SectionKeyValueGet(S_SECTION_UNSIGNED_SHORT, S_KEY_INVALID_UNSIGNED_SHORT, S_VALUE_DEFAULT_UNSIGNED_SHORT);

			THEN("We get the default value")
			{
				REQUIRE(S_VALUE_DEFAULT_UNSIGNED_SHORT == ini_value);
			}
		}

		WHEN("Cleanup and delete ini file")
		{
			REQUIRE(true == sut.INIFileExist(S_FILE_INI_UNSIGNED_SHORT));
			REQUIRE(true == sut.INIFileDelete(S_FILE_INI_UNSIGNED_SHORT));

			THEN("When the ini file is gone")
			{
				REQUIRE(false == sut.INIFileExist(S_FILE_INI_UNSIGNED_SHORT));
			}
		}
	}
}
