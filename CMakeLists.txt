cmake_minimum_required(VERSION 3.8)
project(ex3)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES my_set.hpp my_set.h my_set_tester.cpp)
add_executable(ex3 ${SOURCE_FILES})