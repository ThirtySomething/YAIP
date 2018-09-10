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

static const std::string S_FILE_INI_BOOL = "bool.ini";
static const std::string S_SECTION_BOOL = "SECTION_BOOL";
static const std::string S_KEY_BOOL = "KEY_BOOL";

SCENARIO("Processing of datatype [bool]", "[net::derpaul::yaip::YAIP]")
{
	auto VALUE_BOOL = GENERATE(true, false);

	INFO("Current value [" << VALUE_BOOL << "]");

	GIVEN("An empty instance of the YAIP parser")
	{
		net::derpaul::yaip::YAIP sut;
		REQUIRE(true == sut.SectionListGet().empty());
		REQUIRE(true == sut.SectionKeyValueSet(S_SECTION_BOOL, S_KEY_BOOL, VALUE_BOOL));

		WHEN("Add a new section/key/value")
		{
			THEN("Count of section should be 1")
			{
				REQUIRE(false == sut.SectionListGet().empty());
				REQUIRE(1 == sut.SectionListGet().size());
				REQUIRE(1 == sut.SectionKeyListGet(S_SECTION_BOOL).size());
			}
		}

		WHEN("Save ini file")
		{
			REQUIRE(true == sut.INIFileSave(S_FILE_INI_BOOL));

			THEN("File exists")
			{
				REQUIRE(true == sut.INIFileExist(S_FILE_INI_BOOL));
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
			REQUIRE(true == sut.INIFileExist(S_FILE_INI_BOOL));
			REQUIRE(true == sut.INIFileLoad(S_FILE_INI_BOOL));

			THEN("What you save is what you get")
			{
				REQUIRE(1 == sut.SectionListGet().size());
				REQUIRE(1 == sut.SectionKeyListGet(S_SECTION_BOOL).size());
				bool ini_value= sut.SectionKeyValueGet(S_SECTION_BOOL, S_KEY_BOOL, false);
				REQUIRE(VALUE_BOOL == ini_value);
			}
		}

		WHEN("Cleanup and delete ini file")
		{
			REQUIRE(true == sut.INIFileExist(S_FILE_INI_BOOL));
			REQUIRE(true == sut.INIFileDelete(S_FILE_INI_BOOL));

			THEN("When the ini file is gone")
			{
				REQUIRE(false == sut.INIFileExist(S_FILE_INI_BOOL));
			}
		}
	}
}
