# YAIP - Yet another INI parser

## Badges

[![License: LGPL v3][yaip_license_badge]][yaip_license] [![Version][yaip_release_badge]][yaip_release] [![GitHub forks](https://img.shields.io/github/forks/ThirtySomething/YAIP.svg?style=social&label=Fork&maxAge=2592000)](https://GitHub.com/ThirtySomething/YAIP/network/) [![GitHub issues][yaip_issues_badge]][yaip_issues] [![Open Source Love svg1](https://badges.frapsoft.com/os/v1/open-source.svg?v=103)](https://github.com/ellerbrock/open-source-badges/) [![Language][lang_cpp_badge]][lang_cpp_badge]

## General information

**YAIP** is distributed under the terms of the **GNU LESSER GENERAL PUBLIC LICENSE**, version 3.0. The text of the license is included in the file [<code>LICENSE.TXT</code>][license] in the project root.

## Requirements

To use **YAIP** you need to have an modern [C++11][cpp_eleven] compiler. See the used parts at the section **Implementation Details**. Tested with [Visual Studio 2017][msvs].

## Supported Platforms

Supported platforms are all platforms where the code compiles and the tests run without any error.

## Motivation

Searching for INI parsers for C++ fires up a lot of them. Most of them come with a lot of stuff/classes around, some of them as library. Only a few of them offers plain classes. Also only a few of them are portable. And I'm missing the usage of modern C++ like own [templates][cpp_templates] and the usage of the [STL][cpp_stl]. I like to improve my C++ skills so I decided to write my own INI file parser.

## Implementation Details

- Convenience typedefs for datatypes are done in their corresponding classes, e. g. the smartpointer <code>net::derpaul::yaip::IniEntryPtr</code> in the class file of <code>net::derpaul::yaip::IniEntry</code>.
- Detection of section and key/value pair while reading is done using [regular expressions][cpp_regexp], see also [regular expression][wiki_regexp].
- The internal data storage methods are based on [std::string][cpp_string].
- Templated methods are used for other datatypes calling converters from and to [std::string][cpp_string].

## Used tools

- As testing framework [Catch2][catch2] is used.
- For general C++ style [CppCheck][CppCheck] is used.
- For code metrics [SourceMonitor][SourceMonitor] is used.
- For code coverage [OpenCppCoverage][OpenCppCoverage] is used.

## Extension

To extend the capabilities with currently not supported datatypes, the extension is very simple. Just extend the class <code>net::derpaul::yaip::Convert</code> with conversion methods from/to your data type.

## Doxygen Documentation

A doxygen documentation can be generated, the config file is located in the doxygen subfolder.

## API Overview

### File related actions

- Load INI file

```C++
/**
 * Load and parse INI file into internal structures
 * \param Filename Full qualified filename of the INI file
 * \return true on success otherwise false
 */
bool INIFileLoad(std::string Filename);
```

- Save INI file

```C++
/**
 * Save internal structures to INI file
 * \param Filename Full qualified filename of the INI file
 * \return true on success otherwise false
 */
bool INIFileSave(std::string Filename);
```

- Does INI file exists

```C++
/**
 * Check if given INI file exists
 * \param Filename Full qualified filename of the INI file
 * \return true if file exists otherwise false
 */
bool INIFileExist(const std::string &Filename) const;
```

- Delete INI file

```C++
/**
 * Delete given INI file
 * \param Filename Full qualified filename of the INI file
 * \return true if file is deleted otherwise false
 */
bool INIFileDelete(const std::string &Filename) const;
```

### Section related actions

- Get a list of all sections

```C++
/**
 * Get all sections of the INI file
 * \return Vector with a std::strings for each section
 */
tVectorString SectionListGet(void) const;
```

- Delete a section

```C++
/**
 * Remove section completely from internal data structure
 * \param Section Specified section
 */
void SectionKill(const std::string &Section);
```

- Check if section is empty

```C++
/**
 * Check if section contains data
 * \param Section Specified section
 * \return true for empty section otherwise false
 */
bool SectionEmpty(const std::string &Section) const;
```

### Key related actions

- Get a list of keys of a section

```C++
/**
 * Get all keys of a section of the INI file
 * \param Section Specified section
 * \return Vector with a std::strings for each key
 */
tVectorString SectionKeyListGet(const std::string &Section) const;
```

- Get a value of a section/key combination - *Note: This is a templated method and requires in any case a default value.*

```C++
/**
 * Templated method to retrieve a value of the specified section/key combination
 * \param Section Specified section
 * \param Key Specified key
 * \param Default Specified default value in case key does not exist
 * \return Returns either the default value or the value of the existing section/key combination
 */
template<typename VariableType>
VariableType SectionKeyValueGet(const std::string &Section, const std::string &Key, const VariableType &Default);
```

- Set a value of a section/key combination - *Note: This is a templated method and may require a cast.*

```C++
/**
 * Templated method to set a value of the specified section/key combination
 * \param Section Specified section
 * \param Key Specified key
 * \param Value Specified value to set
 * \return true on success otherwise false
 */
template<typename VariableType>
bool SectionKeyValueSet(const std::string &Section, const std::string &Key, const VariableType &Value);
```

- Delete a key

```C++
/**
 * Remove key completely from section of internal data structure
 * \param Section Specified section
 * \param Key Specified key
 */
void SectionKeyKill(const std::string &Section, const std::string &Key);
```

- Set/Clear a key value and keep an empty key

```C++
/**
 * Clear a key value
 * \param Section Specified section
 * \param Key Specified key
 * \return true on success otherwise false
 */
bool SectionKeyValueClear(const std::string &Section, const std::string &Key);
```

## ToDo's

- The implementation has to be checked against the inofficial specification at [Wikipedia][wiki_ini] and the tests have to satisfiy the specification.
- Enhance the usage of comments.
- Add tests for untested classes.
- Add sorting to ```TIniElementList```

[catch2]: https://github.com/philsquared/Catch
[CppCheck]: http://cppcheck.sourceforge.net/
[cpp_eleven]: https://en.wikipedia.org/wiki/C%2B%2B11
[cpp_map]: http://en.cppreference.com/w/cpp/container/map
[cpp_templates]: https://en.wikipedia.org/wiki/Template_(C%2B%2B)
[cpp_regexp]: http://en.cppreference.com/w/cpp/regex
[cpp_stl]: https://de.wikipedia.org/wiki/Standard_Template_Library
[cpp_string]: http://en.cppreference.com/w/cpp/string/basic_string
[cpp_vector]: http://en.cppreference.com/w/cpp/container/vector
[license]: https://github.com/ThirtySomething/YAIP/blob/master/LICENSE.TXT
[msvs]: https://www.visualstudio.com/
[OpenCppCoverage]: https://github.com/OpenCppCoverage
[SourceMonitor]: http://www.campwoodsw.com/sourcemonitor.html
[wiki_ini]: https://en.wikipedia.org/wiki/INI_file#Comments
[wiki_regexp]: https://en.wikipedia.org/wiki/Regular_expression

[lang_cpp]: https://isocpp.org/
[lang_cpp_badge]: https://img.shields.io/badge/language-C++-blue.svg
[yaip_issues]: # "Open Issues"
[yaip_issues_badge]: https://img.shields.io/github/issues/ThirtySomething/YAIP.svg?maxAge=360
[yaip_license]: http://www.gnu.org/licenses/lgpl-3.0
[yaip_license_badge]: https://img.shields.io/badge/License-LGPL%20v3-blue.svg
[yaip_release]: # "Latest Release"
[yaip_release_badge]: https://img.shields.io/github/release/ThirtySomething/YAIP.svg?maxAge=360
