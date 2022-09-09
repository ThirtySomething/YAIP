// Lexer logic picked from here
// https://stackoverflow.com/questions/56498227/how-to-highlight-qscintilla-using-antlr4

parser grammar INIParser;

options {
	tokenVocab = INILexer;
}

sections: section* EOF;

section: COMMENT | SECTION section_atom*;

section_atom: COMMENT | KEY ASSIGN VALUE COMMENT?;
