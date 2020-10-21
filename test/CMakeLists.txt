project(test)

add_executable(Tests_run test1.c)

target_link_libraries(Tests_run ${GTEST_LIBRARIES} pthread)