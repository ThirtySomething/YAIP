# YAIP - Yet another INI parser

## General information

**YAIP** is distributed under the terms of the **MIT LICENSE**. The text of the license is included in the file [```LICENSE.TXT```][license] in the project root.

## Requirements

To use **YAIP** you need to have a [C++11][cpp_eleven] compiler. Developed and tested with [Visual Studio 2019][msvs] on [Windows 10][w10].

## Supported Platforms

At the moment only Windows is supported.

## Motivation

Based on the experience with the previous versions of the INI parser I descovered the limitation of [regular expression][wiki_regexp] based parsers. So I decided to give [ATLR4][antlr4] a try.

## Used tools

- As testing framework [Catch2][catch2] is used.
- For general C++ style [CppCheck][cppcheck] is used.
- For code metrics [SourceMonitor][sourcemonitor] is used.
- For logging [plog][plog] is used.


## ToDo's

- Define a grammar based on the inofficial specification at [Wikipedia][wiki_ini].
- Generate code using [ATLR4][antlr4].
- Compile the [ATLR4][antlr4] C++ runtime.
- Create a [Visual Studio][msvs] C++ project using the generated code and the runtime.
- Create tests using [Catch2][catch2]

[antlr4]: https://www.antlr.org/
[catch2]: https://github.com/philsquared/Catch
[cpp_eleven]: https://en.wikipedia.org/wiki/C%2B%2B11
[cppcheck]: http://cppcheck.sourceforge.net/
[license]: LICENSE.TXT
[msvs]: https://www.visualstudio.com/
[plog]: https://github.com/SergiusTheBest/plog
[sourcemonitor]: https://www.derpaul.net/SourceMonitor/
[w10]: https://www.microsoft.com/en-us/software-download/windows10
[wiki_ini]: https://en.wikipedia.org/wiki/INI_file#Comments
[wiki_regexp]: https://en.wikipedia.org/wiki/Regular_expression
