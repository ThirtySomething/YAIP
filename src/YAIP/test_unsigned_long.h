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

#include "./../../externals/Catch2/single_include/Catch2/catch.hpp"
#include "YAIP.h"
#include <limits>

static const std::string S_FILE_INI_UNSIGNED_LONG = "unsignedlong.ini";
static const std::string S_SECTION_UNSIGNED_LONG = "SECTION_UNSIGNED_LONG";
static const std::string S_KEY_UNSIGNED_LONG = "KEY_UNSIGNED_LONG";
static const std::string S_KEY_INVALID_UNSIGNED_LONG = "KEY_INVALID";
static const unsigned long S_VALUE_DEFAULT_UNSIGNED_LONG = 0L;

SCENARIO("Processing of datatype [unsigned long]", "[net::derpaul::yaip::YAIP]")
{
	auto VALUE_UNSIGNED_LONG = GENERATE(std::numeric_limits<unsigned long>::min(), std::numeric_limits<unsigned long>::max(), std::numeric_limits<unsigned long>::infinity());

	INFO("Current value [" << VALUE_UNSIGNED_LONG << "]");

	GIVEN("An empty instance of the YAIP parser")
	{
		net::derpaul::yaip::YAIP sut;
		REQUIRE(sut.SectionListGet().empty());
		REQUIRE(sut.SectionKeyValueSet(S_SECTION_UNSIGNED_LONG, S_KEY_UNSIGNED_LONG, VALUE_UNSIGNED_LONG));

		WHEN("Add a new section/key/value")
		{
			THEN("Count of section should be 1")
			{
				REQUIRE(false == sut.SectionListGet().empty());
				REQUIRE(1 == sut.SectionListGet().size());
				REQUIRE(1 == sut.SectionKeyListGet(S_SECTION_UNSIGNED_LONG).size());
			}
		}

		WHEN("Save ini file")
		{
			REQUIRE(sut.INIFileSave(S_FILE_INI_UNSIGNED_LONG));

			THEN("File exists")
			{
				REQUIRE(sut.INIFileExist(S_FILE_INI_UNSIGNED_LONG));
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
			REQUIRE(sut.INIFileExist(S_FILE_INI_UNSIGNED_LONG));
			REQUIRE(sut.INIFileLoad(S_FILE_INI_UNSIGNED_LONG));

			THEN("What you save is what you get")
			{
				auto SectionList = sut.SectionListGet();
				auto SectionKeyList = sut.SectionKeyListGet(S_SECTION_UNSIGNED_LONG);

				REQUIRE(1 == SectionList.size());
				REQUIRE(1 == SectionKeyList.size());

				unsigned long ini_value= sut.SectionKeyValueGet(S_SECTION_UNSIGNED_LONG, S_KEY_UNSIGNED_LONG, S_VALUE_DEFAULT_UNSIGNED_LONG);
				REQUIRE(VALUE_UNSIGNED_LONG == ini_value);
			}
		}

		WHEN("Read from invalid key")
		{
			unsigned long ini_value = sut.SectionKeyValueGet(S_SECTION_UNSIGNED_LONG, S_KEY_INVALID_UNSIGNED_LONG, S_VALUE_DEFAULT_UNSIGNED_LONG);

			THEN("We get the default value")
			{
				REQUIRE(S_VALUE_DEFAULT_UNSIGNED_LONG == ini_value);
			}
		}

		WHEN("Cleanup and delete ini file")
		{
			REQUIRE(sut.INIFileExist(S_FILE_INI_UNSIGNED_LONG));
			REQUIRE(sut.INIFileDelete(S_FILE_INI_UNSIGNED_LONG));

			THEN("When the ini file is gone")
			{
				REQUIRE(false == sut.INIFileExist(S_FILE_INI_UNSIGNED_LONG));
			}
		}
	}
}
