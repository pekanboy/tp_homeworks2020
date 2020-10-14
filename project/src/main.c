// "Copyright [2020] <Aleksey Egorov>"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "./matrix.h"

int main() {
    size_t row;
    size_t col;

    fprintf(stdout, "enter the size of the matrix(row col): ");
    if (fscanf(stdin, "%zd %zd", &row, &col) != 2) {
        exit(2);
    }
    if (row == 0 || col == 0) {
        exit(2);
    }

    Matrix *matrix = matrixAlloc(row, col);
    if (matrix == NULL) {
        exit(13);
    }

    fprintf(stdout, "enter the content of the matrix: ");
    if (matrixFillOut(matrix, stdin) != 0) {
        exit(2);
    }

    matrixSort(matrix);
    matrixPrintf(matrix, stdout);

    matrixFree(matrix);

    return 0;
}
