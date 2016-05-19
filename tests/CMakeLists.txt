
add_executable (read_test read_test.cpp)
target_link_libraries (read_test ${MATIO_LIBRARIES})

add_test (read_test read_test)

