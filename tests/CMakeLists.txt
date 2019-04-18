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

add_executable (matdump matdump.cpp)
target_link_libraries (matdump ${MATIO_LIBRARIES} ${HDF5_LIBRARIES} ${GTEST_LIBRARY} ) #coverage_config

# 3.10 adds support for "GoogleTest" which enumerates the tests inside
# of the code and adds them to ctest.
if (CMAKE_VERSION VERSION_LESS 3.10)
  message ("no gtest-based tests because cmake is too old")
else (CMAKE_VERSION VERSION_LESS 3.10)
  # Configure google-test as a downloadable library.
  include ("${CMAKE_SOURCE_DIR}/cmake/External_GTest.cmake")
  include (GoogleTest)

  set (ALL_TESTS test_read)

  foreach (TEST ${ALL_TESTS})
    # google test binaries
    add_executable (${TEST} ${TEST}.cpp)
    target_link_libraries (${TEST} ${MATIO_LIBRARIES} ${HDF5_LIBRARIES} ${GTEST_LIBRARY} ) #coverage_config
    # discover individual tests
    gtest_discover_tests (${TEST} TEST_LIST ${TEST}_targets
      PROPERTIES TIMEOUT 10
      ENVIRONMENT "CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}"
      )
  endforeach (TEST)

endif (CMAKE_VERSION VERSION_LESS 3.10)

#
# MexEig test with octave
#
find_program (OCTAVE_BIN octave)
if (OCTAVE_BIN)
  add_test (
    NAME MexEig-octave
    COMMAND ${OCTAVE_BIN} --no-gui --path ${CMAKE_CURRENT_SOURCE_DIR} --eval mexeig_test
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
  set_tests_properties (MexEig-octave PROPERTIES DEPENDS eigenX)
endif (OCTAVE_BIN)
