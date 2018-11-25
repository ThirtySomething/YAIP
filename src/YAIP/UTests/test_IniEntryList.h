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
#include "IniEntryList.h"

SCENARIO("Test class [IniEntryList]", "[net::derpaul::yaip::IniEntryList]")
{
	net::derpaul::yaip::IniEntryList sut;
	std::string key = "key";
	std::string value = "value";
	std::string comment = "comment";
	std::string entryraw = key + " = " + value + " ; " + comment;

	auto size = sut.size();
	REQUIRE(0 == size);

	net::derpaul::yaip::IniEntryPtr entry(new net::derpaul::yaip::IniEntry);
	entry->CreateFromRawData("key=value;comment");

	sut.ElementAdd(entry);
	size = sut.size();
	REQUIRE(1 == size);

	sut.clear();
	size = sut.size();
	REQUIRE(0 == size);

	sut.ElementAdd(entry);
	size = sut.size();
	REQUIRE(1 == size);

	auto result = sut.ElementFind(key);
	REQUIRE(nullptr != result);
	REQUIRE(key == result->ElementIdentifierGet());
	REQUIRE(value == result->ElementValueGet());
	REQUIRE(comment == result->ElementCommentGet());

	auto elementList = sut.ElementIdentifierList();
	REQUIRE(1 == elementList.size());
	REQUIRE(key == elementList.front());

	sut.ElementDelete(entry);
	size = sut.size();
	REQUIRE(0 == size);
}
