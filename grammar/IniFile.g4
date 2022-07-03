// Define a grammar for parsing INI files
// Based on the definition found in https://en.wikipedia.org/wiki/INI_file

grammar IniFile;
r  : 'hello' ID ;         // match keyword hello followed by an identifier
ID : [a-z]+ ;             // match lower-case identifiers
WS : [ \t\r\n]+ -> skip ; // skip spaces, tabs, newlines
