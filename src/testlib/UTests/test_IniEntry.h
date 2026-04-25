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

#ifndef _TEST_INIENTRY_H_
#define _TEST_INIENTRY_H_

#include "IniEntry.h"
#include "catch2/catch_all.hpp"

SCENARIO("Test class IniEntry", "[IniEntry]")
{
    net::derpaul::yaip::IniEntry sut;

    INFO("Test setter");
    std::string IdentifierEntry = "IniEntryIdentifier";
    sut.ElementIdentifierSet(IdentifierEntry);
    auto IdentifierEntryRead = sut.ElementIdentifierGet();
    REQUIRE(IdentifierEntry == IdentifierEntryRead);

    std::string ValueEntry = "IniEntryValue";
    sut.ElementValueSet(ValueEntry);
    auto ValueEntryRead = sut.ElementValueGet();
    REQUIRE(ValueEntry == ValueEntryRead);

    std::string CommentEntry = "IniEntryComment";
    sut.ElementCommentSet(CommentEntry);
    auto CommentEntryRead = sut.ElementCommentGet();
    REQUIRE(CommentEntry == CommentEntryRead);

    INFO("Test cleanup");
    sut.clear();
    IdentifierEntryRead = sut.ElementIdentifierGet();
    ValueEntryRead = sut.ElementValueGet();
    CommentEntryRead = sut.ElementCommentGet();

    REQUIRE("" == IdentifierEntryRead);
    REQUIRE("" == ValueEntryRead);
    REQUIRE("" == CommentEntryRead);

    INFO("Test setting with object API");
    sut.ElementIdentifierSet(IdentifierEntry);
    sut.ElementValueSet(ValueEntry);
    sut.ElementCommentSet(CommentEntry);

    IdentifierEntryRead = sut.ElementIdentifierGet();
    ValueEntryRead = sut.ElementValueGet();
    CommentEntryRead = sut.ElementCommentGet();

    REQUIRE(IdentifierEntry == IdentifierEntryRead);
    REQUIRE(ValueEntry == ValueEntryRead);
    REQUIRE(CommentEntry == CommentEntryRead);

    INFO("Test to_string");
    std::ostringstream tmpStream;
    tmpStream << IdentifierEntry << " = " + ValueEntry << " ; " << CommentEntry << std::endl;
    REQUIRE(tmpStream.str() == sut.to_string());
}

#endif
