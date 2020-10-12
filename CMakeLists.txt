cmake_minimum_required(VERSION 3.16.3)
project(tp_homework2020 C)

set(CMAKE_C_STANDARD 11)
set(SRC project/src/main.c project/src/matrix.c)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(project/include)

add_executable(tp_homework2020 ${SRC})

add_subdirectory(gtest)
