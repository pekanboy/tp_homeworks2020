// "Copyright [2020] <Aleksey Egorov>"

#ifndef PROJECT_INCLUDE_MATRIX_H_
#define PROJECT_INCLUDE_MATRIX_H_

#include <stddef.h>
#include <stdio.h>

typedef struct {
    size_t m_row;
    size_t m_col;

    int *m_matrix;
} Matrix;

Matrix *matrixAlloc(int row, int col);
void matrixFree(Matrix *matrix);

int matrixFillOut(Matrix *matrix, FILE *file);
void matrixPrintf(Matrix *matrix, FILE *file);

void matrixSort(Matrix *matrix);
void matrixSwapCol(Matrix *matrix, size_t one, size_t two);

#endif  // PROJECT_INCLUDE_MATRIX_H_
