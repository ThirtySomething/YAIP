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

function(yaip_catch2 CATCH2_VERSION)
    if("${CATCH2_VERSION}" STREQUAL "")
        message(FATAL_ERROR "yaip_catch2: CATCH2_VERSION must be provided.")
    endif()

    if(TARGET Catch2::Catch2WithMain)
        return()
    endif()

    include(FetchContent)

    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG ${CATCH2_VERSION}
    )
    FetchContent_MakeAvailable(Catch2)
endfunction()
