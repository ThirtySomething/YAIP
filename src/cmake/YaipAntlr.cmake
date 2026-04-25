# Helper macro to configure ANTLR4 C++ code generation with fallback to checked-in sources.
macro(yaip_configure_antlr_cpp_generation TARGET_NAME GRAMMAR_DIR GENERATED_DIR FALLBACK_DIR OUT_FILES_VAR OUT_TARGET_VAR)
    set(_ANTLR_GENERATED_SOURCES
        ${GENERATED_DIR}/IniLexer.cpp
        ${GENERATED_DIR}/IniLexer.h
        ${GENERATED_DIR}/IniParser.cpp
        ${GENERATED_DIR}/IniParser.h
        ${GENERATED_DIR}/IniParserBaseVisitor.cpp
        ${GENERATED_DIR}/IniParserBaseVisitor.h
        ${GENERATED_DIR}/IniParserVisitor.cpp
        ${GENERATED_DIR}/IniParserVisitor.h
    )

    option(YAIP_GENERATE_ANTLR "Generate ANTLR parser code from grammar files." ON)
    set(ANTLR4_VERSION 4.13.2)
    set(ANTLR4_JAR "" CACHE FILEPATH "Path to antlr-4.x-complete.jar used for parser generation")

    set(_ANTLR_GENERATION_ENABLED ${YAIP_GENERATE_ANTLR})
    set(_ANTLR_TARGET_NAME "")

    if(_ANTLR_GENERATION_ENABLED)
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
                    set(_ANTLR_GENERATION_ENABLED OFF)
                endif()
            endif()
        else()
            message(WARNING "ANTLR code generation requires a Java runtime. Falling back to checked-in generated parser sources.")
            set(_ANTLR_GENERATION_ENABLED OFF)
        endif()

        if(_ANTLR_GENERATION_ENABLED)
            set(_ANTLR_GENERATOR_COMMAND
                ${Java_JAVA_EXECUTABLE}
                -jar
                ${ANTLR4_JAR}
                -Dlanguage=Cpp
                -visitor
                -no-listener
                -o
                ${GENERATED_DIR}
                ${GRAMMAR_DIR}/IniLexer.g4
                ${GRAMMAR_DIR}/IniParser.g4
            )

            add_custom_command(
                OUTPUT ${_ANTLR_GENERATED_SOURCES}
                COMMAND ${CMAKE_COMMAND} -E make_directory ${GENERATED_DIR}
                COMMAND ${_ANTLR_GENERATOR_COMMAND}
                DEPENDS ${GRAMMAR_DIR}/IniLexer.g4 ${GRAMMAR_DIR}/IniParser.g4
                COMMENT "Generating ANTLR C++ sources from INI grammar"
                VERBATIM
            )

            set(_ANTLR_TARGET_NAME ${TARGET_NAME}_generate_antlr)
            add_custom_target(${_ANTLR_TARGET_NAME}
                DEPENDS ${_ANTLR_GENERATED_SOURCES}
            )

            set(${OUT_FILES_VAR} ${_ANTLR_GENERATED_SOURCES})
        endif()
    endif()

    if(NOT _ANTLR_GENERATION_ENABLED)
        set(${OUT_FILES_VAR}
            ${FALLBACK_DIR}/IniLexer.cpp
            ${FALLBACK_DIR}/IniLexer.h
            ${FALLBACK_DIR}/IniParser.cpp
            ${FALLBACK_DIR}/IniParser.h
            ${FALLBACK_DIR}/IniParserBaseVisitor.cpp
            ${FALLBACK_DIR}/IniParserBaseVisitor.h
            ${FALLBACK_DIR}/IniParserVisitor.cpp
            ${FALLBACK_DIR}/IniParserVisitor.h
        )
    endif()

    set(${OUT_TARGET_VAR} ${_ANTLR_TARGET_NAME})
endmacro()
