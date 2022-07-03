# YAIP - Yet another INI parser

## General information

**YAIP** is distributed under the terms of the **MIT LICENSE**. The text of the license is included in the file [```LICENSE.TXT```][license] in the project root.

## Requirements

To use **YAIP** you need to have a [C++11][cpp_eleven] compiler. Developed and tested with [Visual Studio 2019][msvs] on [Windows 10][w10].

## Supported Platforms

At the moment only Windows is supported.

## Motivation

Based on the experience with the previous versions of the INI parser I descovered the limitation of [regular expression][wiki_regexp] based parsers. So I decided to give [ANTLR4][antlr4] a try.

## Steps

- [ANTLR4][antlr4] runtime
  - First of all download the latest `antlr4.jar` file to `./vendor/antlr4.jar/antlr-4.10.1-complete.jar`
  - Create [Visual Studio project files][msvs] using [CMake][cmake]

    ```bat
    cd ./vendor/antlr4/runtime/Cpp
    cmake -DCMAKE_BUILD_TYPE=Release -DWITH_DEMO=True -DANTLR_JAR_LOCATION=..\..\..\antlr4.jar\antlr-4.10.1-complete.jar .
    ```

  - Open the [Visual Studio][msvs] solution `LIBANTLR4.sln`
  - Build a release version of the `antlr4_static` project
  - Copy the runtime from `./dist/release/antlr4-runtime-static.lib` to `./vendor/antlr4-runtime/antlr4-runtime-static.lib`
  - Git cleanup of the [ANTLR4][antlr4] submodule

## Used tools

- For general C++ style [CppCheck][cppcheck] is used.
- As testing framework [Catch2][catch2] is used.
- For general C++ style [CppCheck][cppcheck] is used.
- For code metrics [SourceMonitor][sourcemonitor] is used.
- For logging [plog][plog] is used.

## ToDo's

- ~~Compile the [ANTLR4][antlr4] C++ runtime.~~
- Define a grammar based on the inofficial specification at [Wikipedia][wiki_ini].
- Generate code using [ANTLR4][antlr4].
- Create a [Visual Studio][msvs] C++ project using the generated code and the runtime.
- Create tests using [Catch2][catch2]

[antlr4]: https://www.antlr.org/
[catch2]: https://github.com/philsquared/Catch
[cmake]: https://cmake.org/
[cpp_eleven]: https://en.wikipedia.org/wiki/C%2B%2B11
[cppcheck]: http://cppcheck.sourceforge.net/
[license]: LICENSE.TXT
[msvs]: https://www.visualstudio.com/
[plog]: https://github.com/SergiusTheBest/plog
[sourcemonitor]: https://www.derpaul.net/SourceMonitor/
[w10]: https://www.microsoft.com/en-us/software-download/windows10
[wiki_ini]: https://en.wikipedia.org/wiki/INI_file#Comments
[wiki_regexp]: https://en.wikipedia.org/wiki/Regular_expression
