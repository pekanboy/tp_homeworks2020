//
// Created by egoro on 07.10.2020.
//

#include <malloc.h>
#include <stdio.h>
#include "../include/matrix.hpp"

Matrix *matrixAlloc(int row, int col) {
    if (row <= 0 || col <= 0) {
        return NULL;
    }

    Matrix *matrix = (Matrix *) malloc(sizeof(Matrix));
    if (!matrix) {
        return NULL; //  Обработка ошибки
    }

    matrix->m_row = row;
    matrix->m_col = col;
    matrix->m_matrix = (int *) malloc(sizeof(int) * row * col);
    if (!matrix->m_matrix) {
        free(matrix);
        return NULL; //  Обработка ошибки
    }

    return matrix;
}

void matrixFree(Matrix *matrix) {
    free(matrix->m_matrix);
    free(matrix);
}

void matrixPrintf(Matrix *matrix, FILE *file) {
    size_t length = matrix->m_col * matrix->m_row;

    for (size_t counter = 0; counter < length; ++counter) {
        if (counter % matrix->m_col == 0) {
            fputc('\n', file);
        }

        fprintf(file, "%5d", matrix->m_matrix[counter]);
    }

}

int matrixFillOut(Matrix *matrix, FILE *file) {
    size_t length = matrix->m_col * matrix->m_row;

    for (size_t counter = 0; counter < length; ++counter) {
        if (fscanf(file, "%d", &matrix->m_matrix[counter]) != 1) {
            return 1;
        }
    }

    return 0;
}

void matrixSort(Matrix *matrix) {
    for (size_t i = 1; i < matrix->m_col; ++i) {
        for (size_t j = i; j > 0 && matrix->m_matrix[j - 1] > matrix->m_matrix[j]; --j) {
            matrixSwapCol(matrix, j - 1, j);
        }
    }

}

void matrixSwapCol(Matrix *matrix, size_t one, size_t two) {

    for (size_t i = 0; i < matrix->m_row; ++i) {
        int t = matrix->m_matrix[matrix->m_col * i + one];
        matrix->m_matrix[matrix->m_col * i + one] = matrix->m_matrix[matrix->m_col * i + two];
        matrix->m_matrix[matrix->m_col * i + two] = t;

    }
}
