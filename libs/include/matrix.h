// "Copyright [2020] <Aleksey Egorov>"

#ifndef LIBS_INCLUDE_MATRIX_H_
#define LIBS_INCLUDE_MATRIX_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    u_int8_t value1 : 2;
    u_int8_t value2 : 2;
    u_int8_t value3 : 2;
    u_int8_t value4 : 2;
} byte;

typedef struct {
    size_t dir;
    size_t size;  // Размер квадратной матрицы
    byte *data;
} lover_tria_matrix;

// Создаём нижнюю треугольную матрицу
lover_tria_matrix *create_matrix(size_t rows, size_t cols);
// Создаём матрицу из файла
lover_tria_matrix *create_matrix_from_file(const char *file_name);
// Освобождаем память под матрицу
void free_matrix(lover_tria_matrix *mat_ptr);
// Устанавливаем значение элемента на заданую позицию
int set_elem(lover_tria_matrix *mat_ptr, size_t pos, unsigned elem);
// Получаем элемент массива по индексу
int get_elem(lover_tria_matrix const *mat_ptr, size_t pos);
// Получаем сумму диагональных элементов
int sum_sequential(const lover_tria_matrix *mat_ptr);

#endif  // LIBS_INCLUDE_MATRIX_H_
