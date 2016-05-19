#
# CMake for MATio
#
cmake_minimum_required (VERSION 2.6.8)

#
# Project Name
#
project (MATio CXX)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -Wall -Wpedantic")

find_package (Eigen3 REQUIRED)

enable_testing ()

add_subdirectory (tests)
#add_subdirectory (examples)
