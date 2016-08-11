#
# CMake for MATio
#
cmake_minimum_required (VERSION 2.6.8)

#
# Project Name
#
project (MATio CXX)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -Wall -Wpedantic")

find_package (Eigen3 REQUIRED)
find_package (Matio REQUIRED)
find_package (HDF5 REQUIRED)

include_directories(include)
include_directories (${EIGEN3_INCLUDE_DIRS})
include_directories (${MATIO_INCLUDE_DIRS})

enable_testing ()

add_subdirectory (tests)
#add_subdirectory (examples)
