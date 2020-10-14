// "Copyright [2020] <Aleksey Egorov>"

#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#include "include/matrix.h"

Matrix *matrix_Alloc(size_t row, size_t col) {
    assert(row != 0 && col != 0);

    Matrix *matrix = malloc(sizeof(Matrix));
    if (!matrix) {
        return NULL;  // Обработка ошибки
    }

    matrix->m_row = row;
    matrix->m_col = col;
    matrix->m_matrix = malloc(sizeof(int) * row * col);
    if (!matrix->m_matrix) {
        free(matrix);
        return NULL;  // Обработка ошибки
    }

    return matrix;
}

void matrix_Free(Matrix *matrix) {
    assert(matrix);

    free(matrix->m_matrix);
    free(matrix);
}

void matrix_Printf(const Matrix *matrix, FILE *file) {
    assert(matrix && file);

    const size_t length = matrix->m_col * matrix->m_row;

    for (size_t counter = 0; counter < length; ++counter) {
        if (counter % matrix->m_col == 0) {
            fputc('\n', file);
        }

        fprintf(file, "%5d", matrix->m_matrix[counter]);
    }
}

bool matrix_Fill_Out(const Matrix *matrix, FILE *file) {
    assert(matrix && file);

    const size_t length = matrix->m_col * matrix->m_row;

    for (size_t counter = 0; counter < length; ++counter) {
        if (fscanf(file, "%d", &matrix->m_matrix[counter]) != 1) {
            return false;
        }
    }

    return true;
}

void matrix_Sort(const Matrix *matrix) {
    assert(matrix);

    for (size_t i = 1; i < matrix->m_col; ++i) {
        for (size_t j = i;
                j > 0 && matrix->m_matrix[j - 1] > matrix->m_matrix[j];
                --j) {
            matrix_Swap_Col(matrix, j - 1, j);
        }
    }
}

void matrix_Swap_Col(const Matrix *matrix, size_t left, size_t right) {
    assert(matrix);
    assert(left >= 0 && left < matrix->m_col);
    assert(right >= 0 && right < matrix->m_col);

    for (size_t i = 0; i < matrix->m_row; ++i) {
        int val_left = get_Value(matrix, i, left);
        int val_right = get_Value(matrix, i, right);
        set_Value(matrix, i, left, val_right);
        set_Value(matrix, i, right, val_left);
    }
}

int get_Value(const Matrix *matrix, size_t row, size_t col) {
    assert(matrix);
    assert(row >= 0 && row < matrix->m_row);
    assert(col >= 0 && col < matrix->m_col);

    return matrix->m_matrix[matrix->m_col * row + col];
}

void set_Value(const Matrix *matrix, size_t row, size_t col, int value) {
    assert(matrix);
    assert(row >= 0 && row < matrix->m_row);
    assert(col >= 0 && col < matrix->m_col);

    matrix->m_matrix[matrix->m_col * row + col] = value;
}
