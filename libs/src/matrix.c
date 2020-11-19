// "Copyright [2020] <Aleksey Egorov>"

#include <math.h>
#include <zconf.h>
#include <memory.h>

#include "define_file.h"
#include "matrix.h"


lover_tria_matrix *create_matrix(size_t rows, size_t cols) {
    if (rows == 0 || cols == 0 || rows != cols) {
        return ERROR_MEMORY_ALLOC;  // Error
    }

    int64_t l1dcls = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);

    lover_tria_matrix *mat_ptr = NULL;
    if (posix_memalign((void **) &mat_ptr, l1dcls, sizeof(lover_tria_matrix))) {
        return CASH_ERROR;
    }

    mat_ptr->dir = rows;
    mat_ptr->size = (1 + rows) * rows / 2;

    mat_ptr->data = NULL;
    if (posix_memalign((void **) &mat_ptr->data,
                       l1dcls,
                       round((double) mat_ptr->size / 4) * sizeof(Byte))) {
        free(mat_ptr);
        return CASH_ERROR;
    }

    return mat_ptr;
}

lover_tria_matrix *create_matrix_from_file(const char *file_name) {
    FILE *fp = fopen(file_name, "r");
    if (!fp) {
        return ERROR_CREATE_FROM_FILE;  // Error
    }

    size_t rows = 0;
    size_t cols = 0;
    if (fscanf(fp, "%zu %zu", &rows, &cols) != 2) {
        fclose(fp);
        return ERROR_CREATE_FROM_FILE;  // Error
    }

    lover_tria_matrix *mat_ptr = create_matrix(rows, cols);
    if (!mat_ptr) {
        fclose(fp);
        return ERROR_MEMORY_ALLOC;  // Error
    }

    for (size_t i = 0; i < mat_ptr->size; ++i) {
        unsigned t = 0;
        if (fscanf(fp, "%u", &t) != 1 || t < 0 || t > 3) {
            free_matrix(mat_ptr);
            fclose(fp);
            return ERROR_CREATE_FROM_FILE;  // Error
        }
        if (!set_elem(mat_ptr, i, t)) {
            free_matrix(mat_ptr);
            fclose(fp);
            return ERROR_CREATE_FROM_FILE;  // Error
        }
    }

    fclose(fp);
    return mat_ptr;
}

void free_matrix(lover_tria_matrix *mat_ptr) {
    if (mat_ptr != NULL) {
        free(mat_ptr->data);
    }

    free(mat_ptr);
}

int set_elem(lover_tria_matrix *mat_ptr, size_t pos, unsigned elem) {
    if (!mat_ptr) {
        return ERROR_ARG_FROM_FUNC;
    }

    size_t sw = pos / 4;
    switch (pos % 4) {
        case 0: {
            mat_ptr->data[sw].value1 = elem;
            break;
        }
        case 1: {
            mat_ptr->data[sw].value2 = elem;
            break;
        }
        case 2: {
            mat_ptr->data[sw].value3 = elem;
            break;
        }
        case 3: {
            mat_ptr->data[sw].value4 = elem;
            break;
        }
    }

    return 1;
}

int get_elem(lover_tria_matrix const *mat_ptr, size_t pos) {
    if (!mat_ptr) {
        return ERROR_ARG_FROM_FUNC;  // Error
    }

    size_t sw = pos / 4;
    switch (pos % 4) {
        case 0: {
            return mat_ptr->data[sw].value1;
        }
        case 1: {
            return mat_ptr->data[sw].value2;
        }
        case 2: {
            return mat_ptr->data[sw].value3;
        }
        case 3: {
            return mat_ptr->data[sw].value4;
        }
    }
}

int sum_sequential(const lover_tria_matrix *mat_ptr, size_t begin, size_t end) {
    if (!mat_ptr) {
        return ERROR_ARG_FROM_FUNC;
    }

    size_t t = (int) (-0.5 + sqrt((double) (0.25 + (double) begin * 2))) + 1;
    size_t counter = t * (t + 1) / 2;  // Сумма арифметической прогрессии
    int sum = 0;

    while (counter <= end) {
        int res = get_elem(mat_ptr, counter - 1);
        if (res == ERROR_ARG_FROM_FUNC) {
            return ERROR_ARG_FROM_FUNC;
        }
        counter += ++t;
        sum += res;
    }

    return sum;
}
