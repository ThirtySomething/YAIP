#include <iostream>
#include <string>

#include "antlr4-runtime.h"
#include "INIFileLexer.h"
#include "INIFileParser.h"
#include "INIFileVisitor.h"

using namespace std;
using namespace antlr4;

int main(int argc, char* argv[])
{
    if (argc != 2) {
        // Abort if name of INI file is not passed
        return 0;
    }

    std::ifstream stream;
    stream.open(argv[1]);

    ANTLRInputStream input(stream);
    INIFileLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    cout << "Tokens:" << endl;
    tokens.fill();
    for (Token* token : tokens.getTokens())
    {
        std::cout << token->toString() << std::endl;
    }

    return 0;
}
 