cmake_minimum_required(VERSION 3.18.4)
project(aoc2024)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(aoc ${SOURCES})
target_include_directories(aoc PRIVATE src)
file(COPY input DESTINATION ${CMAKE_BINARY_DIR})