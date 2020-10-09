//
// Created by egoro on 07.10.2020.
//

#ifndef TP_HOMEWORK2020_MATRIX_H
#define TP_HOMEWORK2020_MATRIX_H

#include <stddef.h>

typedef struct {
    size_t m_row;
    size_t m_col;

    int *m_matrix;
} Matrix;

Matrix *matrixAlloc(size_t row, size_t col);
void matrixFree(Matrix *matrix);

int matrixFillOut(Matrix *matrix);
void matrixPrintf(Matrix *matrix);

void matrixSort(Matrix *matrix);
void matrixSwapCol(Matrix *matrix, size_t one, size_t two);

#endif //TP_HOMEWORK2020_MATRIX_H
