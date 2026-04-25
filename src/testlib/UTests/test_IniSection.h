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

#ifndef _TEST_INISECTION_H_
#define _TEST_INISECTION_H_

#include "IniSection.h"
#include "catch2/catch_all.hpp"
#include <memory>

void testEmpty(const net::derpaul::yaip::IniSection &sut)
{
    INFO("No entries");
    auto EntryList = sut.SectionEntriesGet();
    REQUIRE(EntryList.size() == 0);
    REQUIRE(sut.IsEmpty());
}

void testEntry(const net::derpaul::yaip::IniSection &sut, const std::string &IdentifierEntry)
{
    INFO("Check for entries");
    REQUIRE(!sut.IsEmpty());
    auto EntryList = sut.SectionEntriesGet();
    REQUIRE(EntryList.size() == 1);

    INFO("Check size of list of entries");
    auto IniEntryList = sut.EntryKeyList();
    REQUIRE(IniEntryList.size() == 1);
    REQUIRE(IdentifierEntry == IniEntryList.front());
}

SCENARIO("Test class IniSection", "[IniSection]")
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

    INFO("Set information with object API");
    sut.ElementIdentifierSet(IdentifierSection);
    sut.ElementCommentSet(CommentSection);

    IdentifierSectionRead = sut.ElementIdentifierGet();
    CommentSectionRead = sut.ElementCommentGet();

    REQUIRE(IdentifierSection == IdentifierSectionRead);
    REQUIRE(CommentSection == CommentSectionRead);

    INFO("Check string representation");
    std::ostringstream tmpStream;
    tmpStream << "[" << IdentifierSection << "] ; " << CommentSection << std::endl
              << std::endl;
    REQUIRE(tmpStream.str() == sut.to_string());

    testEmpty(sut);

    INFO("Add an entry from object API");
    std::string IdentifierEntry = "IniEntryIdentifier";
    std::string ValueEntry = "IniEntryValue";
    std::string CommentEntry = "IniEntryComment";

    auto Entry = std::make_shared<net::derpaul::yaip::IniEntry>();
    Entry->ElementIdentifierSet(IdentifierEntry);
    Entry->ElementValueSet(ValueEntry);
    Entry->ElementCommentSet(CommentEntry);

    tmpStream.str("");
    tmpStream.clear();
    tmpStream << IdentifierEntry << " = " << ValueEntry << " ; " << CommentEntry << std::endl
              << std::endl;
    std::string RawDataEntry = tmpStream.str();

    sut.EntryAdd(Entry);

    testEntry(sut, IdentifierEntry);

    INFO("Check string representation");
    tmpStream.str("");
    tmpStream.clear();
    tmpStream << "[" << IdentifierSection << "] ; " << CommentSection << std::endl
              << RawDataEntry;
    std::string SectionFull = tmpStream.str();
    REQUIRE(SectionFull == sut.to_string());

    INFO("Check for correct entry");
    auto IniEntryList = sut.EntryKeyList();
    Entry = sut.EntryFind(IniEntryList.front());
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

#endif
