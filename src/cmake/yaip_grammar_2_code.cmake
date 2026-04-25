# Helper function to configure ANTLR4 C++ code generation with fallback to checked-in sources.
#
# Parameters:
# TARGET_NAME          - CMake target name for the library
# GRAMMAR_DIR          - Directory containing the .g4 grammar files
# GENERATED_DIR        - Directory where ANTLR will write generated sources
# FALLBACK_DIR         - Directory with checked-in generated sources (used when Java/JAR unavailable)
# LEXER_GRAMMAR_NAME   - Base name of the lexer grammar (without .g4), e.g. IniLexer
# PARSER_GRAMMAR_NAME  - Base name of the parser grammar (without .g4), e.g. IniParser
# OUT_FILES_VAR        - Output variable receiving the list of generated/fallback source files
# OUT_TARGET_VAR       - Output variable receiving the name of the code-generation custom target
include_guard(GLOBAL)

include(${CMAKE_CURRENT_LIST_DIR}/yaip_antlr4_generator.cmake)

function(yaip_grammar_2_code TARGET_NAME GRAMMAR_DIR GENERATED_DIR FALLBACK_DIR LEXER_GRAMMAR_NAME PARSER_GRAMMAR_NAME OUT_FILES_VAR OUT_TARGET_VAR)
    if("${TARGET_NAME}" STREQUAL "" OR "${GRAMMAR_DIR}" STREQUAL "" OR "${GENERATED_DIR}" STREQUAL "" OR "${FALLBACK_DIR}" STREQUAL "")
        message(FATAL_ERROR "yaip_grammar_2_code: TARGET_NAME, GRAMMAR_DIR, GENERATED_DIR and FALLBACK_DIR are required.")
    endif()

    if("${LEXER_GRAMMAR_NAME}" STREQUAL "" OR "${PARSER_GRAMMAR_NAME}" STREQUAL "")
        message(FATAL_ERROR "yaip_grammar_2_code: LEXER_GRAMMAR_NAME and PARSER_GRAMMAR_NAME are required.")
    endif()

    if("${OUT_FILES_VAR}" STREQUAL "" OR "${OUT_TARGET_VAR}" STREQUAL "")
        message(FATAL_ERROR "yaip_grammar_2_code: OUT_FILES_VAR and OUT_TARGET_VAR are required.")
    endif()

    if("${YAIP_ANTLR4_VERSION}" STREQUAL "")
        message(FATAL_ERROR "yaip_grammar_2_code: YAIP_ANTLR4_VERSION must be defined before calling this macro.")
    endif()

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

    set(_ANTLR_GENERATION_ENABLED ${YAIP_GENERATE_ANTLR})
    set(_ANTLR_TARGET_NAME "")

    if(_ANTLR_GENERATION_ENABLED)
        yaip_antlr4_generator(
            ${YAIP_ANTLR4_VERSION}
            _ANTLR_GENERATION_ENABLED
            _ANTLR_JAVA_EXECUTABLE
            _ANTLR_JAR_PATH
        )

        if(_ANTLR_GENERATION_ENABLED)
            set(_ANTLR_GENERATOR_COMMAND
                ${_ANTLR_JAVA_EXECUTABLE}
                -jar
                ${_ANTLR_JAR_PATH}
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

            set(${OUT_FILES_VAR} ${_ANTLR_GENERATED_SOURCES} PARENT_SCOPE)
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
            PARENT_SCOPE
        )
    endif()

    set(${OUT_TARGET_VAR} ${_ANTLR_TARGET_NAME} PARENT_SCOPE)
endfunction()
