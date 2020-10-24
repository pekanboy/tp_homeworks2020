cmake_minimum_required(VERSION 3.17)
project(tp_homework2020 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_C_FLAGS "-pthread  -fopenmp")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wpedantic")
set(CMAKE_CXX_FLAGS "-pthread")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(project)

add_subdirectory(project)
add_subdirectory(test)