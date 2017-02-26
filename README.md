# YAIP++ - Yet another INI parser

## General information

[![License: LGPL v3](https://img.shields.io/badge/License-LGPL%20v3-blue.svg)](http://www.gnu.org/licenses/lgpl-3.0)
[![Version](https://img.shields.io/github/release/ThirtySomething/YAIP.svg?maxAge=360)](#)
[![GitHub issues](https://img.shields.io/github/issues/ThirtySomething/YAIP.svg?maxAge=360)](#)
<!-- 
[![Build Status](https://travis-ci.org/ThirtySomething/YAIP.svg?branch=master)](https://travis-ci.org/ThirtySomething/YAIP)

[![AUR](https://img.shields.io/aur/votes/YAIP.svg?maxAge=3600)](https://aur.archlinux.org/packages/YAIP/)

[![codecov](https://codecov.io/gh/ThirtySomething/YAIP/branch/master/graph/badge.svg)](https://codecov.io/gh/ThirtySomething/YAIP)

[![Total downloads](https://img.shields.io/github/downloads/ThirtySomething/YAIP/total.svg?maxAge=360)](#)
-->

-  **YAIP++** is distributed under the terms of the **GNU LESSER GENERAL PUBLIC LICENSE**, version 3.0. The text of the license is included in the file [<code>LICENSE.TXT</code>](https://github.com/ThirtySomething/YAIP/blob/master/LICENSE.TXT) in the project root.
- As testing framework [*Catch*](https://github.com/philsquared/Catch) is used.

<!--
- The build is done at [*Travis*](https://travis-ci.org) using the following compilers:
   - GCC C++ 4.9
   - GCC C++ 5
   - CLANG C++ 3.6
   - CLANG C++ 3.7.
- For code coverage [*Codecov*](https://codecov.io) is planned to use.
-->

## Supported Platforms
Current supported/tested platforms are

- [*Windows 7*](https://en.wikipedia.org/wiki/Windows_7), [*MinGW32*](http://www.mingw.org/) (Ships with [*Code::Blocks*](http://www.codeblocks.org/)), 32-bit
- [*Windows 7*](https://en.wikipedia.org/wiki/Windows_7), [*Visual Studio 2013*](https://www.visualstudio.com/), 32-/64-bit
- [*Windows 7*](https://en.wikipedia.org/wiki/Windows_7), [*Visual Studio 2015*](https://www.visualstudio.com/), 32-/64-bit
- [*Debian 8*](https://www.debian.org/), [*gcc 4.9.2*](https://gcc.gnu.org/), 64-bit

## Motivation

Searching for INI parsers for C++ fires up a lot of them. Most of them come with a lot of stuff/classes around, some of them as library. Only a few of them offers plain classes. Also only a few of them are portable. And I'm missing the usage of modern C++ like own [*templates*](https://en.wikipedia.org/wiki/Template_(C%2B%2B)) and the usage of the [*STL*](https://de.wikipedia.org/wiki/Standard_Template_Library). I like to improve my C++ skills so I decided to write my own INI file parser.

## Implementation details

* Convenience typedefs for datatypes in <code>YAIP++.h</code>
* Data containers are STL elements like [*vector*](http://en.cppreference.com/w/cpp/container/vector) or [*map*](http://en.cppreference.com/w/cpp/container/map)
* Detection of section and key/value pair is done using [*regular expressions*](http://en.cppreference.com/w/cpp/regex)
* The major methods are based on [*std::string*](http://en.cppreference.com/w/cpp/string/basic_string)
* The templated methods using converters from and to [*std::string*](http://en.cppreference.com/w/cpp/string/basic_string)

## Extension

If any datatype is currently not supported, the extension is very simple. Just extend the class <code>YAIP::Convert</code> with conversion methods from/to your data type.

## Doxygen documentation

A doxygen documentation can be generated, the config file is located in the doxygen subfolder.

## API overview

### File related actions:

* Load INI file

		/**
		 * Load and parse INI file into internal structures
		 * \param Filename Full qualified filename of the INI file
		 * \return true on success otherwise false
		 */
		bool INIFileLoad(std::string Filename);

* Save INI file

		/**
		 * Save internal structures to INI file
		 * \param Filename Full qualified filename of the INI file
		 * \return true on success otherwise false
		 */
		bool INIFileSave(std::string Filename);

### Section related actions:

* Get a list of all sections

		/**
		 * Get all sections of the INI file
		 * \return Vector with a std::strings for each section
		 */
		tVectorString SectionListGet(void);

* Delete a section

		/**
		 * Remove section completely from internal data structure
		 * \param Section Specified section
		 */
		void SectionKill(const std::string &Section);

### Key related actions:

* Get a list of keys of a section

		/**
		 * Get all keys of a section of the INI file
		 * \param Section Specified section
		 * \return Vector with a std::strings for each key
		 */
		tVectorString SectionKeyListGet(const std::string &Section);

* Get a value of a section/key combination - *Note: This is a templated method and requires in any case a default value.*

		/**
		 * Templated method to retrieve a value of the specified section/key combination
		 * \param Section Specified section
		 * \param Key Specified key
		 * \param Default Specified default value in case key does not exist
		 * \return Returns either the default value or the value of the existing section/key combination
		 */
		template<typename VariableType>
		VariableType SectionKeyValueGet(const std::string &Section, const std::string &Key, const VariableType &Default);


* Set a value of a section/key combination - *Note: This is a templated method and may require a cast.*

		/**
		 * Templated method to set a value of the specified section/key combination
		 * \param Section Specified section
		 * \param Key Specified key
		 * \param Value Specified value to set
		 * \return true on success otherwise false
		 */
		template<typename VariableType>
		bool SectionKeyValueSet(const std::string &Section, const std::string &Key, const VariableType &Value);

* Delete a key

		/**
		 * Remove key completely from section of internal data structure
		 * \param Section Specified section
		 * \param Key Specified key
		 */
		void SectionKeyKill(const std::string &Section, const std::string &Key);
