lexer grammar IniLexer;

LBRACK: '[';

RBRACK: ']';

EQUAL: '=' -> pushMode(VALUE_MODE);

SEMI: ';';

NL: '\r'? '\n';

TEXT: ~[\r\n=;\u005B\u005D]+;

mode VALUE_MODE;

VALUE_SEMI: ';' -> type(SEMI), popMode;

VALUE_NL: '\r'? '\n' -> type(NL), popMode;

VALUE_TEXT: ~[\r\n;]+ -> type(TEXT);