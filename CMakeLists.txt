cmake_minimum_required(VERSION 3.15)
project(heston)

set(CMAKE_CXX_STANDARD 14)


set(SOURCES
        src/black76.cpp
        src/calculator.cpp
        src/underlying_process.cpp)

add_executable(heston main.cpp ${SOURCES})

target_include_directories(heston
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include)
