cmake_minimum_required(VERSION 3.22)
project(heston VERSION 1.0)

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type selected, default to Release")
  set(CMAKE_BUILD_TYPE
      "Release"
      CACHE STRING "Build type (default Release)" FORCE)
endif()

if(NOT CMAKE_BUILD_TYPE MATCHES "^(Debug|Release|RelWithDebInfo|MinSizeRel)$")
  message(
    FATAL_ERROR
      "Expected CMAKE_BUILD_TYPE is Debug, Release, RelWithDebInfo or MinSizeRel, got ${CMAKE_BUILD_TYPE}"
  )
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

find_package(Python COMPONENTS Interpreter Development)
find_package(pybind11 REQUIRED)

add_subdirectory(src)
add_subdirectory(python)
