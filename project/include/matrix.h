// "Copyright [2020] <Aleksey Egorov>"

#ifndef PROJECT_INCLUDE_MATRIX_H_
#define PROJECT_INCLUDE_MATRIX_H_

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef struct {
    size_t m_row;
    size_t m_col;

    int *m_matrix;
} Matrix;

Matrix *matrix_Alloc(size_t row, size_t col);
void matrix_Free(Matrix *matrix);

bool matrix_Fill_Out(const Matrix *matrix, FILE *file);
void matrix_Printf(const Matrix *matrix, FILE *file);

void matrix_Sort(const Matrix *matrix);
void matrix_Swap_Col(const Matrix *matrix, size_t left, size_t right);

int get_Value(const Matrix *matrix, size_t row, size_t col);
void set_Value(const Matrix *matrix, size_t row, size_t col, int value);

#endif  // PROJECT_INCLUDE_MATRIX_H_
