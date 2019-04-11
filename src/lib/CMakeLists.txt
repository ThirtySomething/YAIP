CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
PROJECT(yaip VERSION 1.0.0 LANGUAGES CXX)

ADD_LIBRARY(yaip STATIC
	Convert.cpp
	Convert.h
	IElementCommon.h
	IniEntry.cpp
	IniEntry.h
	IniEntryList.cpp
	IniEntryList.h
	IniSection.cpp
	IniSection.h
	IniSectionList.cpp
	IniSectionList.h
	string_extensions.cpp
	string_extensions.h
	TIniElementList.h
	YAIP.cpp
	YAIP.h
)

SET(CMAKE_CXX_STANDARD 11)
