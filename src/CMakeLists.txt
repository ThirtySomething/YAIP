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

cmake_minimum_required(VERSION 3.25)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
    set(CMAKE_POLICY_DEFAULT_CMP0135 NEW)
endif()

project(YAIP VERSION 1.0.0 LANGUAGES CXX)

# Keep artifacts in the selected build tree root (e.g. build/).
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(YAIP_ANTLR4_VERSION "4.13.2")
set(YAIP_ANTLR4_LEXER_GRAMMAR "IniLexer")
set(YAIP_ANTLR4_PARSER_GRAMMAR "IniParser")
set(YAIP_CATCH2_VERSION "v3.14.0")
set(YAIP_DISTRI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../distri)

include(CTest)

foreach(_yaip_module
    yaip_post_build
    yaip_grammar_2_code
    yaip_antlr4_runtime
    yaip_catch2)
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/${_yaip_module}.cmake)
endforeach()

yaip_antlr4_runtime(${YAIP_ANTLR4_VERSION})
yaip_catch2(${YAIP_CATCH2_VERSION})

add_subdirectory(lib)
add_subdirectory(testlib)