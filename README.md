# YAIP++ #

Yet another INI parser

## Motivation ##

Searching for INI parsers for C++ fires up a lot of them. Most of them come with a lot of stuff/classes around, some of them as library. Only a few of them offers plain classes. Also only a few of them are portable. I like to improve my C++ skills so I decided to write my own INI file parser.

## Features ##

The current features are

* Reading and parsing an INI file
* Get a vector of strings containing all sections
* Get a vector of strings containing all keys of a section
* Get a value of a section/key combination - Note: This is a templated method and requires in any case a default value.

The planned features are

* Allow adding/changing of section/key/values
* Saving the INI file
* Improving the regular expressions
* Unit tests
* Doxygen documentation

## Implementation details ##

* Convenience typedefs for datatypes in YAIPData.h
* Data containers are STL elements like vector or map
* Detection of section and key/value pair is done using regular expressions

## Sample usage ##

The usage is just simple:

<pre>
// Read and parse the INI file
IniParser.INIFileLoad("C:\\Windows\\system.ini");

// Get a vector of strings containing all section names
tVectorString SectionList = IniParser.GetSectionList();

// Get a vector of strings containing all keys of a section
tVectorString KeyList = IniParser.GetSectionKeys(Section);

// Get a value of a key from a section
std::string Default = "Default value";
std::string Value = IniParser.GetSectionKeyValue(Section, Key, Default);
</pre>

## Contributing ##

Any kind of contribution is welcome.

## License ##

This project is published unter the GNU GENERAL PUBLIC LICENSE, Version 3.
