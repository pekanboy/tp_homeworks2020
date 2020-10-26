project(tests_run)

add_executable(tests_run test.cpp stress_test/stress_test.cpp)

target_link_libraries(tests_run ${GTEST_LIBRARIES} pthread)
target_link_libraries(tests_run dynamic_lib static_lib)

add_subdirectory(gen_matrix)
add_subdirectory(stress_test)