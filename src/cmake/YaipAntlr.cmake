# Helper macro to configure ANTLR4 C++ code generation with fallback to checked-in sources.
#
# Parameters:
#   TARGET_NAME          - CMake target name for the library
#   GRAMMAR_DIR          - Directory containing the .g4 grammar files
#   GENERATED_DIR        - Directory where ANTLR will write generated sources
#   FALLBACK_DIR         - Directory with checked-in generated sources (used when Java/JAR unavailable)
#   LEXER_GRAMMAR_NAME   - Base name of the lexer grammar (without .g4), e.g. IniLexer
#   PARSER_GRAMMAR_NAME  - Base name of the parser grammar (without .g4), e.g. IniParser
#   OUT_FILES_VAR        - Output variable receiving the list of generated/fallback source files
#   OUT_TARGET_VAR       - Output variable receiving the name of the code-generation custom target
macro(yaip_configure_antlr_cpp_generation TARGET_NAME GRAMMAR_DIR GENERATED_DIR FALLBACK_DIR LEXER_GRAMMAR_NAME PARSER_GRAMMAR_NAME OUT_FILES_VAR OUT_TARGET_VAR)
    set(_ANTLR_GENERATED_SOURCES
        ${GENERATED_DIR}/${LEXER_GRAMMAR_NAME}.cpp
        ${GENERATED_DIR}/${LEXER_GRAMMAR_NAME}.h
        ${GENERATED_DIR}/${PARSER_GRAMMAR_NAME}.cpp
        ${GENERATED_DIR}/${PARSER_GRAMMAR_NAME}.h
        ${GENERATED_DIR}/${PARSER_GRAMMAR_NAME}BaseVisitor.cpp
        ${GENERATED_DIR}/${PARSER_GRAMMAR_NAME}BaseVisitor.h
        ${GENERATED_DIR}/${PARSER_GRAMMAR_NAME}Visitor.cpp
        ${GENERATED_DIR}/${PARSER_GRAMMAR_NAME}Visitor.h
    )

    option(YAIP_GENERATE_ANTLR "Generate ANTLR parser code from grammar files." ON)
    set(ANTLR4_JAR "" CACHE FILEPATH "Path to antlr-4.x-complete.jar used for parser generation")

    set(_ANTLR_GENERATION_ENABLED ${YAIP_GENERATE_ANTLR})
    set(_ANTLR_TARGET_NAME "")

    if(_ANTLR_GENERATION_ENABLED)
        find_package(Java COMPONENTS Runtime QUIET)

        if(Java_Runtime_FOUND)
            if(NOT ANTLR4_JAR)
                set(ANTLR4_JAR ${CMAKE_BINARY_DIR}/antlr-${YAIP_ANTLR4_VERSION}-complete.jar)
            endif()

            if(NOT EXISTS ${ANTLR4_JAR})
                file(DOWNLOAD
                    https://www.antlr.org/download/antlr-${YAIP_ANTLR4_VERSION}-complete.jar
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
                ${GRAMMAR_DIR}/${LEXER_GRAMMAR_NAME}.g4
                ${GRAMMAR_DIR}/${PARSER_GRAMMAR_NAME}.g4
            )

            add_custom_command(
                OUTPUT ${_ANTLR_GENERATED_SOURCES}
                COMMAND ${CMAKE_COMMAND} -E make_directory ${GENERATED_DIR}
                COMMAND ${_ANTLR_GENERATOR_COMMAND}
                DEPENDS ${GRAMMAR_DIR}/${LEXER_GRAMMAR_NAME}.g4 ${GRAMMAR_DIR}/${PARSER_GRAMMAR_NAME}.g4
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
            ${FALLBACK_DIR}/${LEXER_GRAMMAR_NAME}.cpp
            ${FALLBACK_DIR}/${LEXER_GRAMMAR_NAME}.h
            ${FALLBACK_DIR}/${PARSER_GRAMMAR_NAME}.cpp
            ${FALLBACK_DIR}/${PARSER_GRAMMAR_NAME}.h
            ${FALLBACK_DIR}/${PARSER_GRAMMAR_NAME}BaseVisitor.cpp
            ${FALLBACK_DIR}/${PARSER_GRAMMAR_NAME}BaseVisitor.h
            ${FALLBACK_DIR}/${PARSER_GRAMMAR_NAME}Visitor.cpp
            ${FALLBACK_DIR}/${PARSER_GRAMMAR_NAME}Visitor.h
        )
    endif()

    set(${OUT_TARGET_VAR} ${_ANTLR_TARGET_NAME})
endmacro()
