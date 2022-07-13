// Definition of a grammar to parse INI files Based on the inofficial definition
// https://en.wikipedia.org/wiki/INI_file
grammar INIFile;

////////////////////////////////////////////////////////////////////////////////
// Parser rules
////////////////////////////////////////////////////////////////////////////////

ini_file_content: (ini_comment_data | ini_section_data);

ini_comment_data: (ini_comment_start ini_comment_text);

ini_section_data: (ini_section_head ini_section_entry*);

ini_section_head: (sbo ini_section_name sbc);

ini_section_name: (textstring);

ini_section_entry: (ini_comment_data | ini_entry_key is ini_entry_value);

ini_entry_key: (textstring);

ini_entry_value: (textstring);

////////////////////////////////////////////////////////////////////////////////
// Lexer rules
////////////////////////////////////////////////////////////////////////////////

hash: '#';

ini_comment_start: (hash | semicolon);

ini_comment_text: (LETTER* | DIGIT* | WHITESPACE*);

is: '=';

sbc: ']';

sbo: '[';

semicolon: ';';

textstring: (LETTER* | DIGIT*);

DIGIT: [0-9];

LETTER: [a-zA-Z];

WHITESPACE: [ \r\n];
