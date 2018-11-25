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
#include "IniSection.h"

SCENARIO("Test class [IniSectioin]", "[net::derpaul::yaip::IniSection]")
{
	net::derpaul::yaip::IniSection sut;

	INFO("Test setter");
	std::string Identifier = "IniEntryIdentifier";
	sut.ElementIdentifierSet(Identifier);
	auto IdentifierRead = sut.ElementIdentifierGet();
	REQUIRE(Identifier == IdentifierRead);

	std::string Comment = "IniEntryComment";
	sut.ElementCommentSet(Comment);
	auto CommentRead = sut.ElementCommentGet();
	REQUIRE(Comment == CommentRead);

	INFO("Test cleanup");
	sut.clear();
	IdentifierRead = sut.ElementIdentifierGet();
	CommentRead = sut.ElementCommentGet();

	REQUIRE("" == IdentifierRead);
	REQUIRE("" == CommentRead);

	INFO("Test setting from raw data");
	std::string RawData = "[" + Identifier + "] ; " + Comment;
	auto result = sut.CreateFromRawData(RawData);
	REQUIRE(true == result);

	IdentifierRead = sut.ElementIdentifierGet();
	CommentRead = sut.ElementCommentGet();

	REQUIRE(Identifier == IdentifierRead);
	REQUIRE(Comment == CommentRead);

	INFO("Test to_string");
	REQUIRE(RawData == sut.to_string());

	// todo:
	// void SectionEntriesSet(const IniEntryList &SectionEntries);
	// IniEntryList SectionEntriesGet(void) const;
	// bool AddRawEntry(const std::string &RawEntryData);
	// IniEntryPtr EntryFind(const std::string &EntryName);
	// void EntryDelete(const IniEntryPtr &Entry);
	// tListString EntryKeyList(void);
	// bool IsEmpty(void);
	// void EntryAdd(const IniEntryPtr &Entry);
}
