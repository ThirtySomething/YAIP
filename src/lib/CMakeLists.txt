set(ANTLR_GRAMMAR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/antlr)
set(ANTLR_GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR}/antlr/generated)
set(ANTLR_FALLBACK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/antlr/generated)

set(ANTLR_GENERATED_SOURCES
    ${ANTLR_GENERATED_DIR}/IniLexer.cpp
    ${ANTLR_GENERATED_DIR}/IniLexer.h
    ${ANTLR_GENERATED_DIR}/IniParser.cpp
    ${ANTLR_GENERATED_DIR}/IniParser.h
    ${ANTLR_GENERATED_DIR}/IniParserBaseVisitor.cpp
    ${ANTLR_GENERATED_DIR}/IniParserBaseVisitor.h
    ${ANTLR_GENERATED_DIR}/IniParserVisitor.cpp
    ${ANTLR_GENERATED_DIR}/IniParserVisitor.h
)

option(YAIP_GENERATE_ANTLR "Generate ANTLR parser code from grammar files." ON)
set(ANTLR4_VERSION 4.13.2)
set(ANTLR4_JAR "" CACHE FILEPATH "Path to antlr-4.x-complete.jar used for parser generation")

if(YAIP_GENERATE_ANTLR)
    find_package(Java COMPONENTS Runtime QUIET)

    if(Java_Runtime_FOUND)
        if(NOT ANTLR4_JAR)
            set(ANTLR4_JAR ${CMAKE_BINARY_DIR}/antlr-${ANTLR4_VERSION}-complete.jar)
        endif()

        if(NOT EXISTS ${ANTLR4_JAR})
            file(DOWNLOAD
                https://www.antlr.org/download/antlr-${ANTLR4_VERSION}-complete.jar
                ${ANTLR4_JAR}
                STATUS _ANTLR_DOWNLOAD_STATUS
                SHOW_PROGRESS
                TLS_VERIFY ON
            )

            list(GET _ANTLR_DOWNLOAD_STATUS 0 _ANTLR_DOWNLOAD_CODE)

            if(NOT _ANTLR_DOWNLOAD_CODE EQUAL 0)
                message(WARNING "Failed to download ANTLR tool JAR (${_ANTLR_DOWNLOAD_STATUS}). Falling back to checked-in generated parser sources.")
                set(YAIP_GENERATE_ANTLR OFF)
            endif()
        endif()
    else()
        message(WARNING "ANTLR code generation requires a Java runtime. Falling back to checked-in generated parser sources.")
        set(YAIP_GENERATE_ANTLR OFF)
    endif()

    if(YAIP_GENERATE_ANTLR)
        set(_ANTLR_GENERATOR_COMMAND
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
    endif()
endif()

if(YAIP_GENERATE_ANTLR)
    add_custom_command(
        OUTPUT ${ANTLR_GENERATED_SOURCES}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${ANTLR_GENERATED_DIR}
        COMMAND ${_ANTLR_GENERATOR_COMMAND}
        DEPENDS ${ANTLR_GRAMMAR_DIR}/IniLexer.g4 ${ANTLR_GRAMMAR_DIR}/IniParser.g4
        COMMENT "Generating ANTLR C++ sources from INI grammar"
        VERBATIM
    )

    add_custom_target(yaip_generate_antlr
        DEPENDS ${ANTLR_GENERATED_SOURCES}
    )

    set(YAIP_ANTLR_FILES ${ANTLR_GENERATED_SOURCES})
else()
    set(YAIP_ANTLR_FILES
        ${ANTLR_FALLBACK_DIR}/IniLexer.cpp
        ${ANTLR_FALLBACK_DIR}/IniLexer.h
        ${ANTLR_FALLBACK_DIR}/IniParser.cpp
        ${ANTLR_FALLBACK_DIR}/IniParser.h
        ${ANTLR_FALLBACK_DIR}/IniParserBaseVisitor.cpp
        ${ANTLR_FALLBACK_DIR}/IniParserBaseVisitor.h
        ${ANTLR_FALLBACK_DIR}/IniParserVisitor.cpp
        ${ANTLR_FALLBACK_DIR}/IniParserVisitor.h
    )
endif()

add_library(yaip STATIC
    Convert.cpp
    Convert.h
    IIniParserStrategy.h
    IIniVisitor.h
    IElementCommon.h
    IniAntlrParser.cpp
    IniAntlrParser.h
    IniDiagnosticsVisitor.cpp
    IniDiagnosticsVisitor.h
    IniDocumentBuilder.cpp
    IniDocumentBuilder.h
    IniEntry.cpp
    IniEntry.h
    IniEntryList.cpp
    IniEntryList.h
    IniSection.cpp
    IniSection.h
    IniSectionList.cpp
    IniSectionList.h
    IniParserFactory.cpp
    IniParserFactory.h
    JsonIniExporterVisitor.cpp
    JsonIniExporterVisitor.h
    ParseErrorListener.cpp
    ParseErrorListener.h
    string_extensions.cpp
    string_extensions.h
    TIniElementList.h
    YAIP.cpp
    YAIP.h
    ${YAIP_ANTLR_FILES}
)

if(TARGET yaip_generate_antlr)
    add_dependencies(yaip yaip_generate_antlr)
endif()

target_compile_features(yaip PUBLIC cxx_std_17)

target_include_directories(yaip PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/antlr/generated>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${ANTLR_GENERATED_DIR}>
)

target_link_libraries(yaip PRIVATE antlr4_static)