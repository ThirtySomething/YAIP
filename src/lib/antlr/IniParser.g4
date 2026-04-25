parser grammar IniParser;

options {
	tokenVocab = IniLexer;
}

iniFile: statement* EOF;

statement:
	sectionStatement
	| pairStatement
	| commentStatement
	| NL;

sectionStatement: LBRACK name = text? RBRACK comment? NL?;

pairStatement: key = text EQUAL value = text? comment? NL?;

commentStatement: text? SEMI text? NL?;

comment: SEMI text?;

text: TEXT+;