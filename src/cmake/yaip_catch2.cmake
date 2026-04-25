# Macro to fetch Catch2 via FetchContent.
# Call yaip_catch2(VERSION) once from the top-level CMakeLists.txt.
macro(yaip_catch2 CATCH2_VERSION)
    include(FetchContent)

    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG ${CATCH2_VERSION}
    )
    FetchContent_MakeAvailable(Catch2)
endmacro()
