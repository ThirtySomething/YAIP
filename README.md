# YAIP++ #

Yet another INI parser

## General information ##

[![License: LGPL v3](https://img.shields.io/badge/License-LGPL%20v3-blue.svg)](http://www.gnu.org/licenses/lgpl-3.0) [![Build Status](https://travis-ci.org/ThirtySomething/YAIP.svg?branch=master)](https://travis-ci.org/ThirtySomething/YAIP) [![codecov](https://codecov.io/gh/ThirtySomething/YAIP/branch/master/graph/badge.svg)](https://codecov.io/gh/ThirtySomething/YAIP)

-  **YAIP++** is distributed under the terms of the **GNU LESSER GENERAL PUBLIC LICENSE**, version 3.0. The text of the license is included in the file **LICENSE.TXT** in the root of the project.
- The build is done at [travis](https://travis-ci.org) using GCC C++ 4.9, GCC C++ 5, CLANG C++ 3.6 and CLANG C++ 3.7.
- For code coverage [codecov](https://codecov.io) is used.
- As testing framework [Catch](https://github.com/philsquared/Catch) is used.

## Motivation ##

Searching for INI parsers for C++ fires up a lot of them. Most of them come with a lot of stuff/classes around, some of them as library. Only a few of them offers plain classes. Also only a few of them are portable. And I'm missing the usage of modern C++ like templates and the usage of the STL. I like to improve my C++ skills so I decided to write my own INI file parser.

## Features ##

The current features are:

* Reading of an INI file
* Parsing of an INI file
* Get a vector of strings containing all sections
* Get a vector of strings containing all keys of a section
* Get a value of a section/key combination - *Note: This is a templated method and requires in any case a default value. This is to figure out the return type of the method.*
* Set a value of a section/key combination - *Note: This is a templated method and may require a cast.*
* Deletion of a key
* Deletion of a section with contents
* Saving of an INI file

## Implementation details ##

* Convenience typedefs for datatypes in <code>YAIP++Data.h</code>
* Data containers are STL elements like [vector](http://en.cppreference.com/w/cpp/container/vector) or [map](http://en.cppreference.com/w/cpp/container/map)
* Detection of section and key/value pair is done using [regular expressions](http://en.cppreference.com/w/cpp/regex)
* The major methods are based on *std::string*
* The templated methods using converters from and to *std::string*

## Simple Extension ##

If any datatype is currently not supported, the extension is very simple. Just extend the class *YAIP::Convert* with conversion methods from/to your data type.

## Sample usage ##

The usage is just simple:

<pre>
// Read and parse the INI file
IniParser.INIFileLoad("C:\\Windows\\system.ini");

// Get a vector of strings containing all section names
tVectorString SectionList = IniParser.SectionListGet();

// Get a vector of strings containing all keys of a section
tVectorString KeyList = IniParser.SectionKeyListGet(Section);

// Read a value
std::string Default = "Default value";
std::string Value = IniParser.SectionKeyValueGet(Section, Key, Default);

// Write a value
IniParser.SectionKeyValueSet("Section", "Key", "Value");

// Delete a key
IniParser.SectionKeyKill("Section", "Key");

// Delete a complete section
IniParser.SectionKill("Section");

// Save modified INI file
IniParser.INIFileSave("C:\\Windows\\Temp\\_YAIP.ini");
</pre>

## Doxygen documentation ##

The latest version of the doxygen documentation can be found [here](https://cdn.rawgit.com/ThirtySomething/YAIP/master/doxygen/html/index.html).

## Contributing ##

Any kind of contribution is welcome.
