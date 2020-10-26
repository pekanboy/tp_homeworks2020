project(stress_tests_run)

add_executable(stress_tests_run stress_test.cpp)

target_link_libraries(stress_tests_run ${GTEST_LIBRARIES} pthread)
target_link_libraries(stress_tests_run dynamic_lib static_lib)
