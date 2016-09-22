PROJECT(YAIP++)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(YAIP_SOURCE
		./../src/YAIP++.h
		./../src/YAIP++Data.h
		./../src/YAIP++.cpp
		./../src/main.cpp)

ADD_EXECUTABLE(YAIP++ ${YAIP_SOURCE})

SET(CMAKE_BUILD_TYPE Debug Release)
SET(DEBUG_FLAGS "-std=c++11 -g -O1 -Wall -Wextra -Werror -pedantic")
SET(RELEASE_FLAGS "-std=c++11 -O3 -Wall -Wextra -Werror -pedantic")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)
