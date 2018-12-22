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

static const std::string S_FILE_INI_UNSIGNED_INT = "unsignedint.ini";
static const std::string S_SECTION_UNSIGNED_INT = "SECTION_UNSIGNED_INT";
static const std::string S_KEY_UNSIGNED_INT = "KEY_UNSIGNED_INT";
static const std::string S_KEY_INVALID_UNSIGNED_INT = "KEY_INVALID";
static const unsigned int S_VALUE_DEFAULT_UNSIGNED_INT = 0;

SCENARIO("Test YAIP with datatype unsigned int", "[unsigned int]")
{
	auto VALUE_UNSIGNED_INT = GENERATE(std::numeric_limits<unsigned int>::min(), std::numeric_limits<unsigned int>::max(), std::numeric_limits<unsigned int>::infinity());

	INFO("Current value [" << VALUE_UNSIGNED_INT << "]");

	GIVEN("An empty instance of the YAIP parser")
	{
		net::derpaul::yaip::YAIP sut;
		REQUIRE(sut.SectionListGet().empty());
		REQUIRE(sut.SectionKeyValueSet(S_SECTION_UNSIGNED_INT, S_KEY_UNSIGNED_INT, VALUE_UNSIGNED_INT));

		WHEN("Add a new section/key/value")
		{
			THEN("Count of section should be 1")
			{
				REQUIRE(false == sut.SectionListGet().empty());
				REQUIRE(1 == sut.SectionListGet().size());
				REQUIRE(1 == sut.SectionKeyListGet(S_SECTION_UNSIGNED_INT).size());
			}
		}

		WHEN("Save ini file")
		{
			REQUIRE(sut.INIFileSave(S_FILE_INI_UNSIGNED_INT));

			THEN("File exists")
			{
				REQUIRE(sut.INIFileExist(S_FILE_INI_UNSIGNED_INT));
			}
		}

		WHEN("Set value of key to empty")
		{
			REQUIRE(sut.SectionKeyValueClear(S_SECTION_UNSIGNED_INT, S_KEY_UNSIGNED_INT));

			THEN("Read value should return default")
			{
				unsigned int ini_value = sut.SectionKeyValueGet(S_SECTION_UNSIGNED_INT, S_KEY_UNSIGNED_INT, S_VALUE_DEFAULT_UNSIGNED_INT);
				REQUIRE(S_VALUE_DEFAULT_UNSIGNED_INT == ini_value);
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
			REQUIRE(sut.INIFileExist(S_FILE_INI_UNSIGNED_INT));
			REQUIRE(sut.INIFileLoad(S_FILE_INI_UNSIGNED_INT));

			THEN("What you save is what you get")
			{
				auto SectionList = sut.SectionListGet();
				auto SectionKeyList = sut.SectionKeyListGet(S_SECTION_UNSIGNED_INT);

				REQUIRE(1 == SectionList.size());
				REQUIRE(1 == SectionKeyList.size());

				unsigned int ini_value = sut.SectionKeyValueGet(S_SECTION_UNSIGNED_INT, S_KEY_UNSIGNED_INT, S_VALUE_DEFAULT_UNSIGNED_INT);
				REQUIRE(VALUE_UNSIGNED_INT == ini_value);
			}
		}

		WHEN("Read from invalid key")
		{
			unsigned int ini_value = sut.SectionKeyValueGet(S_SECTION_UNSIGNED_INT, S_KEY_INVALID_UNSIGNED_INT, S_VALUE_DEFAULT_UNSIGNED_INT);

			THEN("We get the default value")
			{
				REQUIRE(S_VALUE_DEFAULT_UNSIGNED_INT == ini_value);
			}
		}

		WHEN("Cleanup and delete ini file")
		{
			REQUIRE(sut.INIFileExist(S_FILE_INI_UNSIGNED_INT));
			REQUIRE(sut.INIFileDelete(S_FILE_INI_UNSIGNED_INT));

			THEN("When the ini file is gone")
			{
				REQUIRE(false == sut.INIFileExist(S_FILE_INI_UNSIGNED_INT));
			}
		}
	}
}