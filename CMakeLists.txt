cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(geometry-dash-lunar VERSION 1.0.0)

option(ENABLE_DEBUG "Enable debug" OFF)

if(ENABLE_DEBUG)
    add_compile_definitions(ENABLE_TESTS=1)
    add_compile_definitions(DEBUG_ENABLED=1)
else()
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

# source files
file(GLOB_RECURSE SOURCES
	src/*.cpp
    ${OS_SOURCES}
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    include
)

target_include_directories(${PROJECT_NAME} PRIVATE
    include/lunar
)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

setup_geode_mod(${PROJECT_NAME})
