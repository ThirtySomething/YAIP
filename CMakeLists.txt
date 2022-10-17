# -*- mode:cmake -*-
cmake_minimum_required (VERSION 3.15)

# Set project name and information
# https://cmake.org/cmake/help/latest/command/project.html?highlight=project
project(YAIP
    VERSION 0.0.1.1
    DESCRIPTION "Yet Another INI Parser"
    HOMEPAGE_URL https://github.com/ThirtySomething/YAIP
    LANGUAGES CXX
)

# Set CPP standard to C++17
# https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html
set(CMAKE_CXX_STANDARD 17)

# Set name of executable
add_executable(YAIPTest)

# Add code of YAIP
add_subdirectory("${CMAKE_SOURCE_DIR}/src")

# Add ANTL4 runtime
option(BUILD_ANTLR4_RUNTIME "Enable building ANTLR4 runtime" ON)
if(BUILD_ANTLR4_RUNTIME)
    add_subdirectory("${CMAKE_SOURCE_DIR}/vendor/antlr4/runtime/Cpp")
endif()
