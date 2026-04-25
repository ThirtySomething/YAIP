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