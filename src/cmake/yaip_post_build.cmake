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