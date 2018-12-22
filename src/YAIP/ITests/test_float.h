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

static const std::string S_FILE_INI_FLOAT = "float.ini";
static const std::string S_SECTION_FLOAT = "SECTION_FLOAT";
static const std::string S_KEY_FLOAT = "KEY_FLOAT";
static const std::string S_KEY_INVALID_FLOAT = "KEY_INVALID";
static const float S_VALUE_DEFAULT_FLOAT = 0.0f;

SCENARIO("Test YAIP with datatype float", "[float]")
{
	auto VALUE_FLOAT = GENERATE(std::numeric_limits<float>::min(), std::numeric_limits<float>::max(), std::numeric_limits<float>::infinity());

	INFO("Current value [" << VALUE_FLOAT << "]");

	GIVEN("An empty instance of the YAIP parser")
	{
		net::derpaul::yaip::YAIP sut;
		REQUIRE(sut.SectionListGet().empty());
		REQUIRE(sut.SectionKeyValueSet(S_SECTION_FLOAT, S_KEY_FLOAT, VALUE_FLOAT));

		WHEN("Add a new section/key/value")
		{
			THEN("Count of section should be 1")
			{
				REQUIRE(false == sut.SectionListGet().empty());
				REQUIRE(1 == sut.SectionListGet().size());
				REQUIRE(1 == sut.SectionKeyListGet(S_SECTION_FLOAT).size());
			}
		}

		WHEN("Save ini file")
		{
			REQUIRE(sut.INIFileSave(S_FILE_INI_FLOAT));

			THEN("File exists")
			{
				REQUIRE(sut.INIFileExist(S_FILE_INI_FLOAT));
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
			REQUIRE(sut.INIFileExist(S_FILE_INI_FLOAT));
			REQUIRE(sut.INIFileLoad(S_FILE_INI_FLOAT));

			THEN("What you save is what you get")
			{
				auto SectionList = sut.SectionListGet();
				auto SectionKeyList = sut.SectionKeyListGet(S_SECTION_FLOAT);

				REQUIRE(1 == SectionList.size());
				REQUIRE(1 == SectionKeyList.size());

				float ini_value = sut.SectionKeyValueGet(S_SECTION_FLOAT, S_KEY_FLOAT, S_VALUE_DEFAULT_FLOAT);
				REQUIRE(VALUE_FLOAT == Approx(ini_value));
			}
		}

		WHEN("Read from invalid key")
		{
			float ini_value = sut.SectionKeyValueGet(S_SECTION_FLOAT, S_KEY_INVALID_FLOAT, S_VALUE_DEFAULT_FLOAT);

			THEN("We get the default value")
			{
				REQUIRE(S_VALUE_DEFAULT_FLOAT == Approx(ini_value));
			}
		}

		WHEN("Cleanup and delete ini file")
		{
			REQUIRE(sut.INIFileExist(S_FILE_INI_FLOAT));
			REQUIRE(sut.INIFileDelete(S_FILE_INI_FLOAT));

			THEN("When the ini file is gone")
			{
				REQUIRE(false == sut.INIFileExist(S_FILE_INI_FLOAT));
			}
		}
	}
}
