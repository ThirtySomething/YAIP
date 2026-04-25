add_executable(yaiptest
    testlib.cpp
    ITests/test_YAIP.h
    UTests/test_Convert.h
    UTests/test_IniDiagnosticsVisitor.h
    UTests/test_IniEntry.h
    UTests/test_IniEntryList.h
    UTests/test_IniSection.h
)

# TARGET_COMPILE_OPTIONS(yaiptest PRIVATE -Werror)
target_compile_features(yaiptest PRIVATE cxx_std_17)

target_include_directories(yaiptest PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../lib>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ITests>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/UTests>
)

target_link_libraries(yaiptest PRIVATE yaip Catch2::Catch2WithMain)

yaip_add_post_build_copy(yaiptest)

if(UNIX AND NOT APPLE)
    target_compile_definitions(yaiptest PRIVATE CATCH_CONFIG_NO_POSIX_SIGNALS)
endif()

if(BUILD_TESTING)
    add_test(NAME yaiptest COMMAND yaiptest)
endif()
