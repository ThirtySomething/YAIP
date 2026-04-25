# ******************************************************************************
# Copyright 2016 ThirtySomething
# ******************************************************************************
# This file is part of YAIP.
#
# YAIP is free software: you can redistribute it and/or modify it under the
# terms of the GNU Lesser General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option)
# any later version.
#
# YAIP is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
# more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with YAIP. If not, see <http://www.gnu.org/licenses/>.
# ******************************************************************************

add_executable(yaiptest
    testlib.cpp
    ITests/test_YAIP.h
    UTests/test_Convert.h
    UTests/test_IniDiagnosticsVisitor.h
    UTests/test_IniEntry.h
    UTests/test_IniEntryList.h
    UTests/test_IniSection.h
)

target_compile_features(yaiptest PRIVATE cxx_std_17)

target_include_directories(yaiptest PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../lib>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ITests>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/UTests>
)

target_link_libraries(yaiptest PRIVATE yaip Catch2::Catch2WithMain)

yaip_post_build(yaiptest)

if(UNIX AND NOT APPLE)
    target_compile_definitions(yaiptest PRIVATE CATCH_CONFIG_NO_POSIX_SIGNALS)
endif()

if(BUILD_TESTING)
    add_test(NAME yaiptest COMMAND yaiptest)
endif()
