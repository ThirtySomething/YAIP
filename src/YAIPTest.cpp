#include <iostream>

#include "antlr4-runtime.h"
#include "INIFileLexer.h"
#include "INIFileParser.h"
#include "INIFileVisitor.h"

using namespace std;
using namespace antlr4;

int main()
{
    std::ifstream stream;
    stream.open(".\\..\\..\\YAIP.ini");

    ANTLRInputStream input(stream);
    INIFileLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    INIFileParser parser(&tokens);

    return 0;
}
 