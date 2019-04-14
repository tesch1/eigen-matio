#
# CMake for MATio
#
cmake_minimum_required (VERSION 2.6.8)

#
# Project Name
#
project (MATio CXX C)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -Wall -Wpedantic")

find_package (HDF5 REQUIRED)

#
# Eigen
#
include (ExternalProject)
#set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wno-int-in-bool-context") ## REMOVE WITH EIGEN 3.3.5 ##
ExternalProject_Add (eigenX
  PREFIX eigenX
  URL http://bitbucket.org/eigen/eigen/get/3.3.7.tar.bz2
  #URL_HASH MD5=e83549a79d1b721da0f8899ab34edf95
  DOWNLOAD_DIR "$ENV{HOME}/Downloads"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  LOG_DOWNLOAD ON
  )
ExternalProject_Get_Property (eigenX source_dir)
set (EIGEN3_INCLUDE_DIRS "${source_dir}")
include_directories ("${EIGEN3_INCLUDE_DIRS}")

#
# Matio
#
ExternalProject_Add (matioX
  PREFIX matioX
  URL https://sourceforge.net/projects/matio/files/matio/1.5.12/matio-1.5.12.tar.gz/download
  URL_HASH MD5=2968b5a95f05fab8b79ec87f9a6c0cac
  DOWNLOAD_DIR "$ENV{HOME}/Downloads"
  #CONFIGURE_COMMAND "pwd; ./configure" --prefix=<INSTALL_DIR> --enable-shared=no
  CONFIGURE_COMMAND "${CMAKE_BINARY_DIR}/matioX/src/matioX/configure" --prefix=<INSTALL_DIR> --enable-shared=no
  #BUILD_COMMAND ""
  #INSTALL_COMMAND ""
  LOG_DOWNLOAD ON
  )
set (MATIO_INCLUDE_DIRS "${CMAKE_BINARY_DIR}/matioX/include")
set (MATIO_LIBRARIES "${CMAKE_BINARY_DIR}/matioX/lib/libmatio.a")
include_directories ("${MATIO_INCLUDE_DIRS}")

include_directories (${MATIO_INCLUDE_DIRS})

enable_testing ()

add_subdirectory (tests)
#add_subdirectory (examples)
