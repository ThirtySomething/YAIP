# Function to fetch the ANTLR4 C++ runtime via FetchContent.
# Call yaip_antlr4_runtime(VERSION) once from the top-level CMakeLists.txt
# before any subdirectory that needs to link against antlr4_static.
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
