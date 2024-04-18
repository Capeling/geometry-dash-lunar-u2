cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "x86_64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(geometry-dash-lunar VERSION 1.0.0)

# Check for debug build
option(ENABLE_DEBUG "Debug mode" ON)

if (CMAKE_BUILD_TYPE STREQUAL "Debug" OR "${CMAKE_BUILD_TYPE}asdf" STREQUAL "asdf" OR ENABLE_DEBUG)
    set(LUNAR_IS_DEBUG ON)
endif()

# Debug/Release options
if (LUNAR_IS_DEBUG)
    add_compile_definitions(LUNAR_DEBUG=1)
    add_compile_definitions(GEODE_DEBUG=1)
else()
    # Enable LTO in release (2.5x less binary size, costs only a few extra seconds of build time)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) #THANKS DANK_MEME I LOVE YOU
endif()

# source files
file(GLOB_RECURSE SOURCES
	src/main.cpp
    src/hooks/src/*.cpp
    src/defs/*.cpp
    src/utils/*.cpp
    src/layers/src/*.cpp
    src/nodes/src/*.cpp
    ${OS_SOURCES}
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

set(GEODE_BINDINGS_REPO_PATH "S:/GitHub/Geode/bindings")
if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

setup_geode_mod(${PROJECT_NAME})
