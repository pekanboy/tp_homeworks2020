#include <omp.h>

#include "define_file.h"
#include "dlfcn.h"
#include "matrix.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        return INVALID_COUNT_ARG;
    }

    lover_tria_matrix *mat_ptr = create_matrix_from_file(argv[1]);
    if (!mat_ptr) {
        return ERROR_CREATE;
    }

//    SEQUENTIAL

    double wstart = omp_get_wtime();
    printf("%d\n", sum_sequential(mat_ptr, 0, mat_ptr->size));

    double wfinish = omp_get_wtime();
    printf("sequential time: %lf\n\n", wfinish - wstart);

//   PARALLEL

    void *dlib = NULL;

    dlib = dlopen("./libs/libdynamic_lib.so", RTLD_NOW);
    if (!dlib) {
        return EXIT_FAILURE;
    }

    int (*paral_sum)(const lover_tria_matrix *mat_ptr);
    paral_sum = dlsym(dlib, "sum_parallel");

    wstart = omp_get_wtime();
    printf("%d\n", paral_sum(mat_ptr));

    wfinish = omp_get_wtime();
    printf("parallel time: %lf\n\n", wfinish - wstart);

    dlclose(dlib);
    free_matrix(mat_ptr);

    return EXIT_SUCCESS;
}