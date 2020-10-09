cmake_minimum_required(VERSION 3.17)
project(tp_homework2020 C)

set(CMAKE_C_STANDARD 11)
set(SRC src/main.c src/matrix.cpp)

add_executable(tp_homework2020 ${SRC})

add_subdirectory(gtest)
