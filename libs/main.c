#include <omp.h>

#include "define_file.h"
#include "matrix.h"
#include "matrix_op.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        return INVALID_COUNT_ARG;
    }

    lover_tria_matrix *mat_ptr = create_matrix_from_file(argv[1]);
    if (!mat_ptr) {
        return ERROR_CREATE;
    }

    double wstart = omp_get_wtime();

    printf("%d\n", sum_sequential(mat_ptr));

    double wfinish = omp_get_wtime();

    printf("sequential time: %lf\n\n", wfinish - wstart);

    wstart = omp_get_wtime();

    printf("%d\n", sum_parallel(mat_ptr));

    wfinish = omp_get_wtime();

    printf("parallel time: %lf\n\n", wfinish - wstart);
    free_matrix(mat_ptr);

    return EXIT_SUCCESS;
}
