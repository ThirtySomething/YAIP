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
#include "IniEntry.h"

SCENARIO("Test class [IniEntry]", "[net::derpaul::yaip::IniEntry]")
{
	net::derpaul::yaip::IniEntry sut;

	INFO("Test setter");
	std::string Identifier = "IniEntryIdentifier";
	sut.ElementIdentifierSet(Identifier);
	auto IdentifierRead = sut.ElementIdentifierGet();
	REQUIRE(Identifier == IdentifierRead);

	std::string Value = "IniEntryValue";
	sut.ElementValueSet(Value);
	auto ValueRead = sut.ElementValueGet();
	REQUIRE(Value == ValueRead);

	std::string Comment = "IniEntryComment";
	sut.ElementCommentSet(Comment);
	auto CommentRead = sut.ElementCommentGet();
	REQUIRE(Comment == CommentRead);

	INFO("Test cleanup");
	sut.clear();
	IdentifierRead = sut.ElementIdentifierGet();
	ValueRead = sut.ElementValueGet();
	CommentRead = sut.ElementCommentGet();

	REQUIRE("" == IdentifierRead);
	REQUIRE("" == ValueRead);
	REQUIRE("" == CommentRead);

	INFO("Test setting from raw data");
	std::string RawData = Identifier + " = " + Value + " ; " + Comment;
	auto result = sut.CreateFromRawData(RawData);
	REQUIRE(true == result);

	IdentifierRead = sut.ElementIdentifierGet();
	ValueRead = sut.ElementValueGet();
	CommentRead = sut.ElementCommentGet();

	REQUIRE(Identifier == IdentifierRead);
	REQUIRE(Value == ValueRead);
	REQUIRE(Comment == CommentRead);

	INFO("Test to_string");
	REQUIRE(RawData == sut.to_string());
}
