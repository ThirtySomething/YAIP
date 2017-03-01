## YAIP++ Source ##

Here the contents of this directory are rough described:

* <code>CMakeLists.txt</code> - the [*CMake*](https://cmake.org/ "CMake") makefile for <code>YAIP++</code> and its tests.
* <code>main.cpp</code> - will run the tests on <code>YAIP++</code>. *By default the tests of [*Catch*](https://github.com/philsquared/Catch "Catch") are compiled. By uncommenting the first line you can run plain API tests.*
* <code>main_catch.h</code> - the tests of [*Catch*](https://github.com/philsquared/Catch "Catch") are defined here.
* <code>main_classic.*</code> - the plain API tests are defined/implemented here.
* <code>main_fixtures.*</code> - the common used fixtures are defined here.
* <code>README.md</code> - this file.
* <code>YAIP++.*</code> - the code of <code>YAIP++</code>, consiting of
   * The parser <code>YAIP</code>
   * The helper class <code>Convert</code>
   * The [*map*](http://en.cppreference.com/w/cpp/container/map) definitions for sorted maps
