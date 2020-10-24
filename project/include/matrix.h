#ifndef TP_HOMEWORK2020_MATRIX_H
#define TP_HOMEWORK2020_MATRIX_H

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

lover_tria_matrix *create_matrix(size_t rows, size_t cols);  // Создаём нижнюю треугольную матрицу
lover_tria_matrix *create_matrix_from_file(const char *file_name);  // Создаём матрицу из файла
void free_matrix(lover_tria_matrix *mat_ptr);  // Освобождаем память под матрицу
int set_elem(lover_tria_matrix *mat_ptr, size_t pos, unsigned elem);  // Устанавливаем значение элемента на заданую позицию
int print_matrix(const lover_tria_matrix *mat_ptr);  // Это удалить !!!!!!
int get_elem(lover_tria_matrix const *mat_ptr, size_t pos);  // Получаем элемент массива по индексу
unsigned long long sum_end_elem(const lover_tria_matrix *mat_ptr);  // Получаем сумму диагональных элементов

#endif //TP_HOMEWORK2020_MATRIX_H
