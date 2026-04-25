CMAKE_MINIMUM_REQUIRED(VERSION 3.25)
PROJECT(yaip VERSION 1.0.0 LANGUAGES CXX)

SET(ANTLR_GRAMMAR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/antlr)
SET(ANTLR_GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR}/antlr/generated)
SET(ANTLR_FALLBACK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/antlr/generated)

SET(ANTLR_GENERATED_SOURCES
    ${ANTLR_GENERATED_DIR}/IniLexer.cpp
    ${ANTLR_GENERATED_DIR}/IniLexer.h
    ${ANTLR_GENERATED_DIR}/IniParser.cpp
    ${ANTLR_GENERATED_DIR}/IniParser.h
    ${ANTLR_GENERATED_DIR}/IniParserBaseVisitor.cpp
    ${ANTLR_GENERATED_DIR}/IniParserBaseVisitor.h
    ${ANTLR_GENERATED_DIR}/IniParserVisitor.cpp
    ${ANTLR_GENERATED_DIR}/IniParserVisitor.h
)

OPTION(YAIP_GENERATE_ANTLR "Generate ANTLR parser code from grammar files." ON)
SET(ANTLR4_VERSION 4.13.2)
OPTION(YAIP_USE_SYSTEM_ANTLR_TOOL "Use antlr4 executable from PATH instead of version-pinned JAR." OFF)
SET(ANTLR4_JAR "" CACHE FILEPATH "Path to antlr-4.x-complete.jar used for parser generation")

IF(YAIP_GENERATE_ANTLR)
    IF(YAIP_USE_SYSTEM_ANTLR_TOOL)
        FIND_PROGRAM(ANTLR4_COMMAND antlr4)

        IF(ANTLR4_COMMAND)
            SET(_ANTLR_GENERATOR_COMMAND
                ${ANTLR4_COMMAND}
                -Dlanguage=Cpp
                -visitor
                -no-listener
                -o
                ${ANTLR_GENERATED_DIR}
                ${ANTLR_GRAMMAR_DIR}/IniLexer.g4
                ${ANTLR_GRAMMAR_DIR}/IniParser.g4
            )
        ELSE()
            MESSAGE(WARNING "YAIP_USE_SYSTEM_ANTLR_TOOL is ON but no antlr4 executable was found. Falling back to checked-in generated parser sources.")
            SET(YAIP_GENERATE_ANTLR OFF)
        ENDIF()
    ELSE()
        FIND_PACKAGE(Java COMPONENTS Runtime QUIET)

        IF(Java_Runtime_FOUND)
            IF(NOT ANTLR4_JAR)
                SET(ANTLR4_JAR ${CMAKE_BINARY_DIR}/antlr-${ANTLR4_VERSION}-complete.jar)
            ENDIF()

            IF(NOT EXISTS ${ANTLR4_JAR})
                FILE(DOWNLOAD
                    https://www.antlr.org/download/antlr-${ANTLR4_VERSION}-complete.jar
                    ${ANTLR4_JAR}
                    STATUS _ANTLR_DOWNLOAD_STATUS
                    SHOW_PROGRESS
                    TLS_VERIFY ON
                )

                LIST(GET _ANTLR_DOWNLOAD_STATUS 0 _ANTLR_DOWNLOAD_CODE)

                IF(NOT _ANTLR_DOWNLOAD_CODE EQUAL 0)
                    MESSAGE(WARNING "Failed to download ANTLR tool JAR (${_ANTLR_DOWNLOAD_STATUS}). Falling back to checked-in generated parser sources.")
                    SET(YAIP_GENERATE_ANTLR OFF)
                ENDIF()
            ENDIF()
        ELSE()
            MESSAGE(WARNING "ANTLR code generation requires a Java runtime. Falling back to checked-in generated parser sources.")
            SET(YAIP_GENERATE_ANTLR OFF)
        ENDIF()

        IF(YAIP_GENERATE_ANTLR)
            SET(_ANTLR_GENERATOR_COMMAND
                ${Java_JAVA_EXECUTABLE}
                -jar
                ${ANTLR4_JAR}
                -Dlanguage=Cpp
                -visitor
                -no-listener
                -o
                ${ANTLR_GENERATED_DIR}
                ${ANTLR_GRAMMAR_DIR}/IniLexer.g4
                ${ANTLR_GRAMMAR_DIR}/IniParser.g4
            )
        ENDIF()
    ENDIF()
ENDIF()

IF(YAIP_GENERATE_ANTLR)
    ADD_CUSTOM_COMMAND(
        OUTPUT ${ANTLR_GENERATED_SOURCES}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${ANTLR_GENERATED_DIR}
        COMMAND ${_ANTLR_GENERATOR_COMMAND}
        DEPENDS ${ANTLR_GRAMMAR_DIR}/IniLexer.g4 ${ANTLR_GRAMMAR_DIR}/IniParser.g4
        COMMENT "Generating ANTLR C++ sources from INI grammar"
        VERBATIM
    )

    ADD_CUSTOM_TARGET(yaip_generate_antlr
        DEPENDS ${ANTLR_GENERATED_SOURCES}
    )

    SET(YAIP_ANTLR_FILES ${ANTLR_GENERATED_SOURCES})
ELSE()
    SET(YAIP_ANTLR_FILES
        ${ANTLR_FALLBACK_DIR}/IniLexer.cpp
        ${ANTLR_FALLBACK_DIR}/IniLexer.h
        ${ANTLR_FALLBACK_DIR}/IniParser.cpp
        ${ANTLR_FALLBACK_DIR}/IniParser.h
        ${ANTLR_FALLBACK_DIR}/IniParserBaseVisitor.cpp
        ${ANTLR_FALLBACK_DIR}/IniParserBaseVisitor.h
        ${ANTLR_FALLBACK_DIR}/IniParserVisitor.cpp
        ${ANTLR_FALLBACK_DIR}/IniParserVisitor.h
    )
ENDIF()

ADD_LIBRARY(yaip STATIC
    Convert.cpp
    Convert.h
    IElementCommon.h
    IniAntlrParser.cpp
    IniAntlrParser.h
    IniEntry.cpp
    IniEntry.h
    IniEntryList.cpp
    IniEntryList.h
    IniSection.cpp
    IniSection.h
    IniSectionList.cpp
    IniSectionList.h
    string_extensions.cpp
    string_extensions.h
    TIniElementList.h
    YAIP.cpp
    YAIP.h
    ${YAIP_ANTLR_FILES}
)

IF(TARGET yaip_generate_antlr)
    ADD_DEPENDENCIES(yaip yaip_generate_antlr)
ENDIF()

SET(CMAKE_CXX_STANDARD 17)

TARGET_INCLUDE_DIRECTORIES(yaip PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/antlr/generated>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${ANTLR_GENERATED_DIR}>
)

TARGET_LINK_LIBRARIES(yaip PRIVATE antlr4_static)

SET(dir ${CMAKE_CURRENT_SOURCE_DIR}/../../build/)
SET(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
SET(LIBRARY_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir})
SET(CMAKE_BUILD_FILES_DIRECTORY ${dir})
SET(CMAKE_BUILD_DIRECTORY ${dir})
SET(CMAKE_BINARY_DIR ${dir})
SET(EXECUTABLE_OUTPUT_PATH ${dir})
SET(LIBRARY_OUTPUT_PATH ${dir}lib)
SET(CMAKE_CACHEFILE_DIR ${dir})