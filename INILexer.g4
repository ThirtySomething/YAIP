// Lexer logic picked from here
// https://stackoverflow.com/questions/56498227/how-to-highlight-qscintilla-using-antlr4

lexer grammar INILexer;

SECTION: '[' ~[\]]+ ']';

COMMENT: (SEMICOLON | HASH) ~[\r\n]*;

ASSIGN: '=' -> pushMode(VALUE_MODE);

KEY: ~[ \t\r\n]+;

SPACES: [ \t\r\n]+ -> skip;

UNRECOGNIZED: .;

mode VALUE_MODE;

VALUE_MODE_SPACES: [ \t]+ -> skip;

VALUE: ~[ \t\r\n]+;

VALUE_MODE_COMMENT: (SEMICOLON | HASH) ~[\r\n]* -> type(COMMENT);

VALUE_MODE_NL: [\r\n]+ -> skip, popMode;

SEMICOLON: ';';

HASH: '#';