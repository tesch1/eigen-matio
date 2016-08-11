
add_executable (read_test read_test.cpp)
target_link_libraries (read_test ${MATIO_LIBRARIES})
target_link_libraries (read_test ${HDF5_LIBRARIES})
target_link_libraries(read_test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test (read_test read_test)

