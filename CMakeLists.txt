
project(bitprofile)

if(ENABLE_DEBUG)
    set(CMAKE_BUILD_TYPE Debug)
else()
    set(CMAKE_BUILD_TYPE Release)
endif()

cmake_minimum_required(VERSION 3.2)

set (BitProfile_VERSION_MAJOR 1)
set (BitProfile_VERSION_MINOR 0)
set (BitProfile_VERSION_PATCH 0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/modules")

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/OSFlags.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/lib.cmake)

if(ENABLE_EXAMPLES)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/examples.cmake)
endif()

configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/src/Config.hpp.in"
  "${CMAKE_CURRENT_BINARY_DIR}/include/bitprofile/Config.hpp"
)


