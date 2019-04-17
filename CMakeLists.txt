#
# This file is part of eigen-matio, a lightweight C++ template
# library for reading data files into Eigen matrices.
#
# Copyright (C) 2019 Michael Tesch, tesch1 (a) gmail com
#
# This Source Code Form is subject to the terms of the Mozilla
# Public License v. 2.0. If a copy of the MPL was not distributed
# with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
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
  URL https://github.com/tbeu/matio/releases/download/v1.5.15/matio-1.5.15.tar.gz
  #URL_HASH MD5=2968b5a95f05fab8b79ec87f9a6c0cac
  DOWNLOAD_DIR "$ENV{HOME}/Downloads"
  #CONFIGURE_COMMAND "pwd; ./configure" --prefix=<INSTALL_DIR> --enable-shared=no
  CONFIGURE_COMMAND "${CMAKE_BINARY_DIR}/matioX/src/matioX/configure" --prefix=<INSTALL_DIR> --enable-shared=no
  #BUILD_COMMAND ""
  #INSTALL_COMMAND ""
  LOG_DOWNLOAD ON
  )
set (MATIO_INCLUDE_DIRS "${CMAKE_BINARY_DIR}/matioX/include")
set (MATIO_LIBRARIES "${CMAKE_BINARY_DIR}/matioX/lib/libmatio.a")

#
# Include dirs
#
include_directories (${MATIO_INCLUDE_DIRS})
include_directories (${CMAKE_SOURCE_DIR})

enable_testing ()

add_subdirectory (tests)
#add_subdirectory (examples)

#
# etags
#
find_program (ETAGS etags)
if (ETAGS)
  add_custom_target (tags
    COMMAND etags --language=c++ ${CMAKE_SOURCE_DIR}/MATio
    COMMAND etags --language=c++ --append ${CMAKE_SOURCE_DIR}/MexEig
    COMMAND etags --language=c --append `find ${CMAKE_BINARY_DIR}/matioX/src -name '*.[ch]'`
    )
  add_custom_target (etags DEPENDS tags)
endif (ETAGS)
