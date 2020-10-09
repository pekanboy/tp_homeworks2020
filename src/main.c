//
// Created by egoro on 07.10.2020.
//

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/matrix.h"

int main(int argc, char **argv) {
    size_t row;
    size_t col;

    printf("enter the size of the matrix(row col): ");
    if (scanf("%zd %zd", &row, &col) != 2) {
        exit(2);
    }
    if (row == 0 || col == 0) {
        exit(2);
    }

    Matrix *matrix = matrixAlloc(row, col);
    if (matrix == NULL) {
        exit(13);
    }

    if (matrixFillOut(matrix) != 0) {
        exit(2);
    }
    matrixPrintf(matrix);

    matrixSort(matrix);
    matrixPrintf(matrix);

    matrixFree(matrix);

    return 0;
}
