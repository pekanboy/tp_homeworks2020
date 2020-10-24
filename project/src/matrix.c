#include <math.h>
#include "matrix.h"

lover_tria_matrix *create_matrix(size_t rows, size_t cols) {
    if (rows == 0 || cols == 0 || rows != cols) {
        return NULL;  // Error
    }

    lover_tria_matrix *mat_ptr = calloc(1, sizeof(lover_tria_matrix));
    if (mat_ptr == NULL) {
        return NULL;  // Error
    }

    mat_ptr->dir = rows;
    mat_ptr->size = (1 + rows) * rows / 2;

    mat_ptr->data = calloc((size_t)round((double)((double)(1 + mat_ptr->size) * mat_ptr->size / (2 * 4))),
                           sizeof(byte));  // Костыль
    if (mat_ptr->data == NULL) {
        free(mat_ptr);
        return NULL;  // Error
    }

    return mat_ptr;
}

lover_tria_matrix *create_matrix_from_file(const char *file_name) {
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        return NULL;  // Error
    }

    size_t rows = 0;
    size_t cols = 0;
    if (fscanf(fp, "%zu %zu", &rows, &cols) != 2) {
        fclose(fp);
        return NULL;  // Error
    }

    lover_tria_matrix *mat_ptr = create_matrix(rows, cols);
    if (mat_ptr == NULL) {
        fclose(fp);
        return NULL;  // Error
    }

    for (size_t i = 0; i < mat_ptr->size; ++i) {
        unsigned t = 0;
        if (fscanf(fp, "%u", &t) != 1 ||
                t < 0 ||
                t > 3) {
            free_matrix(mat_ptr);
            fclose(fp);
            return NULL;  // Error
        }
        if(!set_elem(mat_ptr, i, t)) {
            free_matrix(mat_ptr);
            fclose(fp);
            return NULL;  // Error
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
    if (mat_ptr == NULL) {
        return 0;  // Error
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
    if (mat_ptr == NULL) {
        return -1;  // Error
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

    return 0;
}


unsigned long long sum_end_elem(const lover_tria_matrix *mat_ptr) {
    if (mat_ptr == NULL) {
        return -1;
    }

    size_t counter = 0;
    size_t t = 1;
    unsigned long long sum = 0;

    for (size_t i = 0; i < mat_ptr->dir; ++i) {
        int res = get_elem(mat_ptr, counter);
        if (res == -1) {
            return -1;
        }

        counter += ++t;
        sum += res;
    }

    return sum;
}

int print_matrix(const lover_tria_matrix *mat_ptr) {
    if (mat_ptr == NULL) {
        return -1;
    }

    size_t counter = 0;
    size_t t = 1;

    for (size_t i = 0; i < mat_ptr->size; ++i) {
        int res = get_elem(mat_ptr, i);
        if (res == -1) {
            return -1;
        }

        if (counter == i) {
            counter += t;
            ++t;
            printf("\n");
        }

        printf("%d ", res);
    }

    return 0;
}
