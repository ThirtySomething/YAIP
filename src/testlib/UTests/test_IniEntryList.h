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

#ifndef _TEST_INIENTRYLIST_H_
#define _TEST_INIENTRYLIST_H_

#include "IniEntryList.h"
#include "catch2/catch_all.hpp"
#include <memory>

SCENARIO("Test class IniEntryList", "[IniEntryList]")
{
    net::derpaul::yaip::IniEntryList sut;
    std::string key = "key";
    std::string value = "value";
    std::string comment = "comment";

    auto size = sut.size();
    REQUIRE(sut.size() == 0);

    auto entry = std::make_shared<net::derpaul::yaip::IniEntry>();
    entry->ElementIdentifierSet(key);
    entry->ElementValueSet(value);
    entry->ElementCommentSet(comment);

    sut.ElementAdd(entry);
    size = sut.size();
    REQUIRE(size == 1);

    sut.clear();
    size = sut.size();
    REQUIRE(size == 0);

    sut.ElementAdd(entry);
    size = sut.size();
    REQUIRE(size == 1);

    auto result = sut.ElementFind(key);
    REQUIRE(nullptr != result);
    REQUIRE(key == result->ElementIdentifierGet());
    REQUIRE(value == result->ElementValueGet());
    REQUIRE(comment == result->ElementCommentGet());

    auto elementList = sut.ElementIdentifierList();
    REQUIRE(elementList.size() == 1);
    REQUIRE(key == elementList.front());

    sut.ElementDelete(entry);
    size = sut.size();
    REQUIRE(size == 0);
}

#endif
