cmake_minimum_required(VERSION 3.10)
project(heston)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(pybind11)

set(SOURCES
        python/python_binding.cpp
        src/black76.cpp
        src/calculator.cpp
        src/underlying_process.cpp)

pybind11_add_module(heston ${SOURCES})

target_include_directories(heston
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include)
