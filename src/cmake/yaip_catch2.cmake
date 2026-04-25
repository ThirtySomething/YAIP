# Function to fetch Catch2 via FetchContent.
# Call yaip_catch2(VERSION) once from the top-level CMakeLists.txt.
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
