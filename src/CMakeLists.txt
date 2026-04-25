CMAKE_MINIMUM_REQUIRED(VERSION 3.6)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
    set(CMAKE_POLICY_DEFAULT_CMP0135 NEW)
endif()

PROJECT(YAIP VERSION 1.0.0 LANGUAGES CXX)

include(CTest)
include(FetchContent)

set(ANTLR4_INSTALL OFF CACHE BOOL "" FORCE)
set(WITH_DEMO OFF CACHE BOOL "" FORCE)
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

ADD_SUBDIRECTORY(lib)
ADD_SUBDIRECTORY(testlib)

SET(dir ${CMAKE_CURRENT_SOURCE_DIR}/../build/)
SET(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
SET(LIBRARY_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir})
SET(CMAKE_BUILD_FILES_DIRECTORY ${dir})
SET(CMAKE_BUILD_DIRECTORY ${dir})
SET(CMAKE_BINARY_DIR ${dir})
SET(EXECUTABLE_OUTPUT_PATH ${dir})
SET(LIBRARY_OUTPUT_PATH ${dir}lib)
SET(CMAKE_CACHEFILE_DIR ${dir})