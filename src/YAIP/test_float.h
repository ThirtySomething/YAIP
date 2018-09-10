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

#include "./../../externals/Catch/single_include/Catch2/catch.hpp"
#include "YAIP++.h"
#include <limits>

static const std::string S_FILE_INI_FLOAT = "float.ini";
static const std::string S_SECTION_FLOAT = "SECTION_FLOAT";
static const std::string S_KEY_FLOAT = "KEY_FLOAT";

SCENARIO("Processing of datatype [float]", "[net::derpaul::yaip::YAIP]")
{
	auto VALUE_FLOAT = GENERATE(std::numeric_limits<float>::max(), std::numeric_limits<float>::min(), std::numeric_limits<float>::infinity());

	INFO("Current value [" << VALUE_FLOAT << "]");

	GIVEN("An empty instance of the YAIP parser")
	{
		net::derpaul::yaip::YAIP sut;
		REQUIRE(true == sut.SectionListGet().empty());
		REQUIRE(true == sut.SectionKeyValueSet(S_SECTION_FLOAT, S_KEY_FLOAT, VALUE_FLOAT));

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
			REQUIRE(true == sut.INIFileSave(S_FILE_INI_FLOAT));

			THEN("File exists")
			{
				REQUIRE(true == sut.INIFileExist(S_FILE_INI_FLOAT));
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
			REQUIRE(true == sut.INIFileExist(S_FILE_INI_FLOAT));
			REQUIRE(true == sut.INIFileLoad(S_FILE_INI_FLOAT));

			THEN("What you save is what you get")
			{
				REQUIRE(1 == sut.SectionListGet().size());
				REQUIRE(1 == sut.SectionKeyListGet(S_SECTION_FLOAT).size());
				float ini_value= sut.SectionKeyValueGet(S_SECTION_FLOAT, S_KEY_FLOAT, 0.0f);
				REQUIRE(VALUE_FLOAT == Approx(ini_value));
			}
		}

		WHEN("Cleanup and delete ini file")
		{
			REQUIRE(true == sut.INIFileExist(S_FILE_INI_FLOAT));
			REQUIRE(true == sut.INIFileDelete(S_FILE_INI_FLOAT));

			THEN("When the ini file is gone")
			{
				REQUIRE(false == sut.INIFileExist(S_FILE_INI_FLOAT));
			}
		}
	}
}
