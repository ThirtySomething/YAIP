# YAIP - Yet another INI parser

## General information

**YAIP** is distributed under the terms of the **MIT LICENSE**. The text of the license is included in the file [```LICENSE.TXT```][license] in the project root.

## Requirements

To use **YAIP** you need to have a [C++17][cpp_seventeen] compiler. Developed and tested with [Visual Studio 2019][msvs] on [Windows 10][w10].

## Supported Platforms

At the moment only Windows is supported.

## Motivation

Based on the experience with the previous versions of the INI parser I descovered the limitation of [regular expression][wiki_regexp] based parsers. So I decided to give [ANTLR4][antlr4] a try.

## Steps

- [ANTLR4][antlr4] runtime
  - The runtime will be part of the YAIP project and compiled there
- Prepare environment based on the description [here][setup_env_w]
  - Installed [Java 1.8][java_p_18] from Oracle and [OpenJDK 11][java_o_11] as alternative
  - Installed [CMake][cmake]
  - Create script `git_init.bat/.sh` to init the submodules
  - Create script `git_update.bat/.sh` to update the submodules
  - Created script `base.bat/.sh` to extend `CLASSPATH` with `antlr-4.10.1-complete.jar` found at vendor path, base of all batches using [ANTLR4][antlr4]
  - Create script `antlr4.bat/.sh` to call [ANTLR4][antlr4]
  - Create script `grun.bat/.sh` to call [ANTLR4][antlr4] TestRig
  - Create script `compile.bat/.sh` to call Java compiler with [ANTLR4][antlr4] in classpath
  - Created test grammar file `INILexer.g4`
  - Created test grammar file `INIParser.g4`
  - Create script `generate.bat/.sh` to create CPP files from previous grammar
- Prerequisites
  - Adjust paths in `base.bat/.sh` to satisfy your environment
- YAIP project
  - Open solution file
  - Select YAIP as start project
  - Compile

## Used tools

- As testing framework [Catch2][catch2] is used.
- For general C++ style [CppCheck][cppcheck] is used.
- For code metrics [SourceMonitor][sourcemonitor] is used.
- For logging [plog][plog] is used.
- For [ANTLR4][antlr4] the tutorials [here][antlr4-tut] and [here][antlr4-tut-cpp] were used.

## ToDo's

- Define a grammar based on the inofficial specification at [Wikipedia][wiki_ini].
- Create tests using [Catch2][catch2]
- ~~Compile the [ANTLR4][antlr4] C++ runtime.~~
- ~~Setup [Windows][w10] environment~~
- ~~Create a [Visual Studio][msvs] C++ project~~ using the generated code and the runtime.
- ~~Generate code using [ANTLR4][antlr4].~~

[antlr4-tut-cpp]: https://tomassetti.me/getting-started-antlr-cpp/
[antlr4-tut]: https://tomassetti.me/antlr-mega-tutorial/
[antlr4]: https://www.antlr.org/
[catch2]: https://github.com/philsquared/Catch
[cmake]: https://cmake.org/
[cpp_seventeen]: https://en.wikipedia.org/wiki/C%2B%2B17
[cppcheck]: http://cppcheck.sourceforge.net/
[java_o_11]: https://openjdk.org/projects/jdk/11/
[java_p_18]: https://www.oracle.com/de/java/technologies/javase/javase8u211-later-archive-downloads.html
[license]: LICENSE.TXT
[msvs]: https://www.visualstudio.com/
[plog]: https://github.com/SergiusTheBest/plog
[setup_env_w]: https://github.com/antlr/antlr4/blob/master/doc/getting-started.md#windows
[sourcemonitor]: https://www.derpaul.net/SourceMonitor/
[w10]: https://www.microsoft.com/en-us/software-download/windows10
[wiki_ini]: https://en.wikipedia.org/wiki/INI_file#Comments
[wiki_regexp]: https://en.wikipedia.org/wiki/Regular_expression
