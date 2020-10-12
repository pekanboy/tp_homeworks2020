project(gtest)

add_executable(Google_Tests_run test.cpp ../project/src/matrix.c)
target_link_libraries(Google_Tests_run ${GTEST_LIBRARIES} pthread)