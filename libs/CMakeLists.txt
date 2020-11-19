project(static_lib)
project(dynamic_lib)

set(SOURCE_FILES src/matrix_op.c src/matrix.c)

include_directories(include/)

add_library(static_lib STATIC  ${SOURCE_FILES})
add_library(dynamic_lib SHARED  ${SOURCE_FILES})

target_include_directories(static_lib PUBLIC include/)
target_include_directories(dynamic_lib PUBLIC include/)