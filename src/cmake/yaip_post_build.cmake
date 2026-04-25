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

function(yaip_post_build target_name)
    if("${target_name}" STREQUAL "")
        message(FATAL_ERROR "yaip_post_build: target_name must be provided.")
    endif()

    add_custom_command(TARGET ${target_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${YAIP_DISTRI_DIR}/$<IF:$<CONFIG:Debug>,debug,release>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:${target_name}>
        ${YAIP_DISTRI_DIR}/$<IF:$<CONFIG:Debug>,debug,release>/$<TARGET_FILE_NAME:${target_name}>
        VERBATIM
    )
endfunction()