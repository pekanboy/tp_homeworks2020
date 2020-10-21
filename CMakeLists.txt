cmake_minimum_required(VERSION 3.17)
project(tp_homework2020 C)

set(CMAKE_C_STANDARD 11)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(project)

add_subdirectory(project)
add_subdirectory(test)