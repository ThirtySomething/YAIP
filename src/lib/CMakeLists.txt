# ******************************************************************************
# Copyright 2016 ThirtySomething
# ******************************************************************************
# This file is part of YAIP.
#
# YAIP is free software: you can redistribute it and/or modify it under the
# terms of the GNU Lesser General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option)
# any later version.
#
# YAIP is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
# more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with YAIP. If not, see <http://www.gnu.org/licenses/>.
# ******************************************************************************

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

set(YAIP_BASE_FILES
    Convert.cpp
    Convert.h
    IIniParserStrategy.h
    IIniVisitor.h
    IElementCommon.h
    string_extensions.cpp
    string_extensions.h
    TIniElementList.h
)

set(YAIP_DOCUMENT_FILES
    IniEntry.cpp
    IniEntry.h
    IniEntryList.cpp
    IniEntryList.h
    IniSection.cpp
    IniSection.h
    IniSectionList.cpp
    IniSectionList.h
)

set(YAIP_PARSER_FILES
    IniAntlrParser.cpp
    IniAntlrParser.h
    ParseErrorListener.cpp
    ParseErrorListener.h
    IniParserBackend.h
    IniParserFactory.cpp
    IniParserFactory.h
)

set(YAIP_DIAGNOSTICS_FILES
    IniDiagnostic.h
    IniDiagnosticCode.h
    IniDiagnosticsVisitor.cpp
    IniDiagnosticsVisitor.h
    IniDiagnosticSeverity.h
)

set(YAIP_VISITOR_FILES
    IniDocumentBuilder.cpp
    IniDocumentBuilder.h
    JsonIniExporterVisitor.cpp
    JsonIniExporterVisitor.h
)

set(YAIP_PUBLIC_API_FILES
    YAIP.cpp
    YAIP.h
)

add_library(yaip STATIC
    ${YAIP_BASE_FILES}
    ${YAIP_DOCUMENT_FILES}
    ${YAIP_PARSER_FILES}
    ${YAIP_DIAGNOSTICS_FILES}
    ${YAIP_VISITOR_FILES}
    ${YAIP_PUBLIC_API_FILES}
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