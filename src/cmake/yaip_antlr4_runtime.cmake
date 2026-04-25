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

include_guard(GLOBAL)

function(yaip_antlr4_runtime ANTLR4_VERSION)
    if("${ANTLR4_VERSION}" STREQUAL "")
        message(FATAL_ERROR "yaip_antlr4_runtime: ANTLR4_VERSION must be provided.")
    endif()

    if(TARGET antlr4_static OR TARGET antlr4_shared)
        return()
    endif()

    include(FetchContent)

    set(ANTLR4_INSTALL OFF CACHE BOOL "" FORCE)
    set(WITH_DEMO OFF CACHE BOOL "" FORCE)
    set(ANTLR_BUILD_CPP_TESTS OFF CACHE BOOL "" FORCE)
    set(WITH_LIBCXX OFF CACHE BOOL "" FORCE)
    set(WITH_STATIC_CRT OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(
        antlr4_runtime
        GIT_REPOSITORY https://github.com/antlr/antlr4.git
        GIT_TAG ${ANTLR4_VERSION}
        SOURCE_SUBDIR runtime/Cpp
    )
    FetchContent_MakeAvailable(antlr4_runtime)
endfunction()
