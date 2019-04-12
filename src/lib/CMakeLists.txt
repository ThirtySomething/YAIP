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

SET(dir ${CMAKE_CURRENT_SOURCE_DIR}/../../Build/)
SET(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
SET(LIBRARY_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir})
SET(CMAKE_BUILD_FILES_DIRECTORY ${dir})
SET(CMAKE_BUILD_DIRECTORY ${dir})
SET(CMAKE_BINARY_DIR  ${dir})
SET(EXECUTABLE_OUTPUT_PATH ${dir})
SET(LIBRARY_OUTPUT_PATH ${dir}lib)
SET(CMAKE_CACHEFILE_DIR ${dir})