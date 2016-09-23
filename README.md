# YAIP++ #

Yet another INI parser

[![Build Status](https://travis-ci.org/ThirtySomething/YAIP.svg?branch=master)](https://travis-ci.org/ThirtySomething/YAIP)

## Motivation ##

Searching for INI parsers for C++ fires up a lot of them. Most of them come with a lot of stuff/classes around, some of them as library. Only a few of them offers plain classes. Also only a few of them are portable. I like to improve my C++ skills so I decided to write my own INI file parser.

## Features ##

The current features are:

* Reading and parsing an INI file
* Get a vector of strings containing all sections
* Get a vector of strings containing all keys of a section
* Get a value of a section/key combination - Note: This is a templated method and requires in any case a default value.
* Set a value of a section/key combination - Note: This is a templated method and may require a cast.
* Delete a key
* Delete a complete section

## Implementation details ##

* Convenience typedefs for datatypes in <code>YAIP++Data.h</code>
* Data containers are STL elements like vector or map
* Detection of section and key/value pair is done using regular expressions

## Sample usage ##

The usage is just simple:

<pre>
// Read and parse the INI file
IniParser.INIFileLoad("C:\\Windows\\system.ini");

// Get a vector of strings containing all section names
tVectorString SectionList = IniParser.SectionListGet();

// Get a vector of strings containing all keys of a section
tVectorString KeyList = IniParser.SectionKeyListGet(Section);

// Get a value of a key from a section
std::string Default = "Default value";
std::string Value = IniParser.SectionKeyValueGet(Section, Key, Default);

// Write a value to the INI file
IniParser.SectionKeyValueSet("Section", "Key", "Value");

// Delete a key
IniParser.SectionKeyKill("Section", "Key");

// Delete a complete section
IniParser.SectionKill("Section");

// Save modified INI file
IniParser.INIFileSave("C:\\Windows\\Temp\\YAIP.ini");
</pre>

## Doxygen documentation ##

The doxygen documentation can be generated when you need it. The config file is located here:

<pre>
doxygen\YAIP++.doxy
</pre>

## Contributing ##

Any kind of contribution is welcome.

## License ##

This project is published unter the GNU GENERAL PUBLIC LICENSE, Version 3.
