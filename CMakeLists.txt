cmake_minimum_required(VERSION 3.16.3)
project(tp_homework2020 C)

set(CMAKE_C_STANDARD 11)

SET(GCC_COVERAGE_COMPILE_FLAGS "--coverage")
add_compile_options("--coverage")
add_link_options("--coverage")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(project/include)

add_subdirectory(project)
add_subdirectory(gtest)
