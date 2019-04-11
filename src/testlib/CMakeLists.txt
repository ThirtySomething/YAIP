CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
PROJECT(yaiptest VERSION 1.0.0 LANGUAGES CXX)

ADD_EXECUTABLE(yaiptest
	../../externals/Catch2/single_include/catch2/catch.hpp
	testlib.cpp
	ITests/test_YAIP.h
	UTests/test_Convert.h
	UTests/test_IniEntry.h
	UTests/test_IniEntryList.h
	UTests/test_IniSection.h
)

# TARGET_COMPILE_OPTIONS(yaiptest PRIVATE -Werror)

SET (CMAKE_CXX_STANDARD 11)

TARGET_INCLUDE_DIRECTORIES(yaiptest PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../externals/Catch2/single_include>  
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../lib>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ITests>  
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/UTests>  
)

LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../lib)
TARGET_LINK_LIBRARIES(yaiptest yaip)