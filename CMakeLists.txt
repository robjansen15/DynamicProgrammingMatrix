cmake_minimum_required(VERSION 3.6)
project(DynamicProgrammingMatrixTable)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(DynamicProgrammingMatrixTable ${SOURCE_FILES})