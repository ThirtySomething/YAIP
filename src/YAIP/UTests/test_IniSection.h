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

void testEmpty(const net::derpaul::yaip::IniSection &sut)
{
	INFO("No entries");
	auto EntryList = sut.SectionEntriesGet();
	REQUIRE(0 == EntryList.size());
	REQUIRE(true == sut.IsEmpty());
}

void testEntry(const net::derpaul::yaip::IniSection &sut, const std::string &IdentifierEntry)
{
	INFO("Check for entries");
	REQUIRE(false == sut.IsEmpty());
	auto EntryList = sut.SectionEntriesGet();
	REQUIRE(1 == EntryList.size());

	INFO("Check size of list of entries");
	auto IniEntryList = sut.EntryKeyList();
	REQUIRE(1 == IniEntryList.size());
	REQUIRE(IdentifierEntry == IniEntryList.front());
}

SCENARIO("Test class [IniSection]", "[net::derpaul::yaip::IniSection]")
{
	net::derpaul::yaip::IniSection sut;
	net::derpaul::yaip::IniEntryList EntryList;

	INFO("Set section information");
	std::string IdentifierSection = "IniSectionIdentifier";
	sut.ElementIdentifierSet(IdentifierSection);
	auto IdentifierSectionRead = sut.ElementIdentifierGet();
	REQUIRE(IdentifierSection == IdentifierSectionRead);

	std::string CommentSection = "IniSectionComment";
	sut.ElementCommentSet(CommentSection);
	auto CommentSectionRead = sut.ElementCommentGet();
	REQUIRE(CommentSection == CommentSectionRead);

	INFO("Cleanup information");
	sut.clear();
	IdentifierSectionRead = sut.ElementIdentifierGet();
	CommentSectionRead = sut.ElementCommentGet();

	REQUIRE("" == IdentifierSectionRead);
	REQUIRE("" == CommentSectionRead);

	INFO("Set information from raw data");
	std::ostringstream tmpStream;
	tmpStream <<  "[" << IdentifierSection << "] ; " << CommentSection << std::endl;
	std::string RawData = tmpStream.str();
	auto result = sut.CreateFromRawData(RawData);
	REQUIRE(true == result);

	IdentifierSectionRead = sut.ElementIdentifierGet();
	CommentSectionRead = sut.ElementCommentGet();

	REQUIRE(IdentifierSection == IdentifierSectionRead);
	REQUIRE(CommentSection == CommentSectionRead);

	INFO("Check string representation");
	REQUIRE(RawData == sut.to_string());

	testEmpty(sut);

	INFO("Add an entry from raw data");
	std::string IdentifierEntry = "IniEntryIdentifier";
	std::string ValueEntry = "IniEntryValue";
	std::string CommentEntry = "IniEntryComment";

	tmpStream.str("");
	tmpStream.clear();
	tmpStream << IdentifierEntry << " = " + ValueEntry << " ; " << CommentEntry << std::endl;
	std::string RawDataEntry = tmpStream.str();

	result = sut.AddRawEntry(RawDataEntry);
	REQUIRE(true == result);

	testEntry(sut, IdentifierEntry);

	INFO("Check string representation");
	tmpStream.str("");
	tmpStream.clear();
	tmpStream << RawData << RawDataEntry;
	std::string SectionFull = tmpStream.str();
	REQUIRE(SectionFull == sut.to_string());

	INFO("Check for correct entry");
	auto IniEntryList = sut.EntryKeyList();
	net::derpaul::yaip::IniEntryPtr Entry = sut.EntryFind(IniEntryList.front());
	REQUIRE(Entry != nullptr);

	std::string IdentifierEntryRead = Entry->ElementIdentifierGet();
	std::string ValueEntryRead = Entry->ElementValueGet();
	std::string CommentEntryRead = Entry->ElementCommentGet();

	REQUIRE(IdentifierEntry == IdentifierEntryRead);
	REQUIRE(ValueEntry == ValueEntryRead);
	REQUIRE(CommentEntry == CommentEntryRead);

	INFO("Delete found entry");
	sut.EntryDelete(Entry);

	testEmpty(sut);

	INFO("Add entry");
	sut.EntryAdd(Entry);

	testEntry(sut, IdentifierEntry);

	INFO("Set empty list");
	EntryList.clear();
	sut.SectionEntriesSet(EntryList);

	testEmpty(sut);
}
