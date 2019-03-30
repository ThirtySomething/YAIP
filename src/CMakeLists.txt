CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
PROJECT(YAIP VERSION 1.0.0 LANGUAGES CXX)

ADD_LIBRARY(YAIP STATIC
	lib/Convert.cpp
	lib/IniEntry.cpp
	lib/IniSection.cpp
	lib/IniSectionList.cpp
	lib/string_extensions.cpp
	lib/YAIP.cpp
)


SET( APP_EXE testlib )

ADD_EXECUTABLE(${APP_EXE}
	testlib/testlib.cpp
)

TARGET_INCLUDE_DIRECTORIES(${APP_EXE} PRIVATE 
	./../externals/Catch2/single_include
	./lib
	./testlib
)

TARGET_LINK_LIBRARIES(${APP_EXE}
	YAIP
)
