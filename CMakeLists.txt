cmake_minimum_required(VERSION 3.16.3)
project(project)

set(CMAKE_CXX_STANDARD 17)
SET(GCC_COVERAGE_COMPILE_FLAGS "--coverage ")
set(CMAKE_C_FLAGS "-pthread  -fopenmp")
set(CMAKE_CXX_FLAGS "-pthread")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror -Wpedantic")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--no-as-needed -ldl")

add_compile_options("--coverage")
add_link_options("--coverage")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(libs/include)

add_executable(project main.c)

target_link_libraries(project PUBLIC static_lib)
target_link_libraries(project PUBLIC dynamic_lib)
target_link_libraries(project PRIVATE m)
target_link_libraries(project PRIVATE -ldl)

add_subdirectory(libs)
add_subdirectory(test)
add_subdirectory(stress_test)
