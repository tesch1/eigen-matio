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

set (CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wpedantic")
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package (HDF5 REQUIRED)

#
# Eigen
#
include (ExternalProject)
ExternalProject_Add (eigenX
  PREFIX eigenX
  URL http://bitbucket.org/eigen/eigen/get/3.3.7.tar.bz2
  URL_HASH MD5=05b1f7511c93980c385ebe11bd3c93fa
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
  URL_HASH MD5=b1436ac47cf66d53ed9f892d0ae027ca
  DOWNLOAD_DIR "$ENV{HOME}/Downloads"
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
    COMMAND etags --language=c++ ${CMAKE_SOURCE_DIR}/MATio ${CMAKE_SOURCE_DIR}/MexEig
    COMMAND etags --language=c --append `find ${CMAKE_BINARY_DIR}/matioX/src -name '*.[ch]'`
    )
  add_custom_target (etags DEPENDS tags)
endif (ETAGS)
