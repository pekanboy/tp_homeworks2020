set(SRC src/main.c src/matrix.c src/matrix_op.c)

include_directories(include/)

add_executable(tp_homework2020 ${SRC})

target_link_libraries(tp_homework2020 PRIVATE m)