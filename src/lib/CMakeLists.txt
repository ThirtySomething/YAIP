set(ANTLR_GRAMMAR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/antlr)
set(ANTLR_GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR}/antlr/generated)
set(ANTLR_FALLBACK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/antlr/generated)

yaip_grammar_2_code(
    yaip
    ${ANTLR_GRAMMAR_DIR}
    ${ANTLR_GENERATED_DIR}
    ${ANTLR_FALLBACK_DIR}
    ${YAIP_ANTLR4_LEXER_GRAMMAR}
    ${YAIP_ANTLR4_PARSER_GRAMMAR}
    YAIP_ANTLR_FILES
    YAIP_ANTLR_TARGET
)

add_library(yaip STATIC
    Convert.cpp
    Convert.h
    IIniParserStrategy.h
    IIniVisitor.h
    IElementCommon.h
    IniAntlrParser.cpp
    IniAntlrParser.h
    IniDiagnostic.h
    IniDiagnosticCode.h
    IniDiagnosticsVisitor.cpp
    IniDiagnosticsVisitor.h
    IniDiagnosticSeverity.h
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
    IniParserBackend.h
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

if(YAIP_ANTLR_TARGET)
    add_dependencies(yaip ${YAIP_ANTLR_TARGET})
endif()

target_compile_features(yaip PUBLIC cxx_std_17)

target_include_directories(yaip PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/antlr/generated>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${ANTLR_GENERATED_DIR}>
)

target_link_libraries(yaip PRIVATE antlr4_static)

yaip_post_build(yaip)