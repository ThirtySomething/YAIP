cmake_minimum_required(VERSION 3.25)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
    set(CMAKE_POLICY_DEFAULT_CMP0135 NEW)
endif()

project(YAIP VERSION 1.0.0 LANGUAGES CXX)

set(YAIP_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../build/)
set(EXECUTABLE_OUTPUT_PATH ${YAIP_BUILD_DIR} CACHE PATH "Build directory" FORCE)
set(LIBRARY_OUTPUT_PATH ${YAIP_BUILD_DIR} CACHE PATH "Build directory" FORCE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${YAIP_BUILD_DIR})
set(CMAKE_BUILD_FILES_DIRECTORY ${YAIP_BUILD_DIR})
set(CMAKE_BUILD_DIRECTORY ${YAIP_BUILD_DIR})
set(CMAKE_BINARY_DIR ${YAIP_BUILD_DIR})
set(EXECUTABLE_OUTPUT_PATH ${YAIP_BUILD_DIR})
set(LIBRARY_OUTPUT_PATH ${YAIP_BUILD_DIR}lib)
set(CMAKE_CACHEFILE_DIR ${YAIP_BUILD_DIR})

include(CTest)
include(FetchContent)

set(ANTLR4_INSTALL OFF CACHE BOOL "" FORCE)
set(WITH_DEMO OFF CACHE BOOL "" FORCE)
set(ANTLR_BUILD_CPP_TESTS OFF CACHE BOOL "" FORCE)
set(WITH_LIBCXX OFF CACHE BOOL "" FORCE)
set(WITH_STATIC_CRT OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    antlr4_runtime
    GIT_REPOSITORY https://github.com/antlr/antlr4.git
    GIT_TAG 4.13.2
    SOURCE_SUBDIR runtime/Cpp
)
FetchContent_MakeAvailable(antlr4_runtime)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.14.0
)
FetchContent_MakeAvailable(Catch2)

add_subdirectory(lib)
add_subdirectory(testlib)