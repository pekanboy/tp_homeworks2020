// "Copyright [2020] <Aleksey Egorov>"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/matrix.h"
#include "include/main.h"

int main(int argc, char **argv) {
    FILE *file_In = NULL;
    FILE *file_Out = NULL;

    if (argc > 2) {
        file_In = fopen(argv[1], "r");
        file_Out = fopen(argv[2], "w");
    } else {
        file_In = stdin;
        file_Out = stdout;
    }

    if (!file_In || !file_Out) {
        printf("Error: could not open files: %s %s", argv[1], argv[2]);
        return NOT_OPEN_FILE;
    }
    size_t row = 0;
    size_t col = 0;

    if (fscanf(file_In, "%zd %zd", &row, &col) != 2) {
        printf("Error: Invalid input size.\n");
        return BAD_INPUT;
    }

    Matrix *matrix = matrix_Alloc(row, col);
    if (matrix == NULL) {
        printf("Error: Bad memory allocation.\n");
        return BAD_ALLOC;
    }

    if (!matrix_Fill_Out(matrix, file_In)) {
        printf("Error: Incorrect filling.\n");
        return BAD_INPUT;
    }

    matrix_Sort(matrix);
    matrix_Printf(matrix, file_Out);

    matrix_Free(matrix);

    if (argc > 2) {
        fclose(file_Out);
        fclose(file_In);
    }

    return 0;
}
