cmake_minimum_required(VERSION 3.12)

project(wildcard VERSION 0.1 LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	message(STATUS "Debug build")
	add_compile_definitions(DEBUG)
endif()

set(SOURCES
	src/wildcard.h
	src/wildcard.cpp
	src/setlocale.h
	src/setlocale.cpp
	src/main.cpp
)

add_executable(wildcard ${SOURCES})
add_test(NAME wildcard COMMAND wildcard)
