CMAKE_MINIMUM_REQUIRED(VERSION 3.6)

ADD_LIBRARY( YAIP STATIC
             lib/Convert.cpp
			 lib/IniEntry.cpp
			 lib/IniSection.cpp
			 lib/IniSectionList.cpp
			 lib/string_extensions.cpp
			 lib/YAIP.cpp )


# CMake instructions to test using the static lib

SET( APP_EXE testlib )

ADD_EXECUTABLE( ${APP_EXE}
                testlib/testlib.cpp 
				) 		

TARGET_LINK_LIBRARIES( ${APP_EXE}
                       YAIP )
					   
TARGET_INCLUDE_DIRECTORIES(${APP_EXE} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../externals/Catch2/single_include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/testlib/ITests>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/testlib/UTests>
)
