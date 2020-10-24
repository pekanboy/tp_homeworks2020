#ifndef TP_HOMEWORK2020_MATRIX_OP_H
#define TP_HOMEWORK2020_MATRIX_OP_H

#include "matrix.h"
#include <pthread.h>

typedef struct worker_attr {
    int *sums_arr_ptr;
    const lover_tria_matrix *mat_ptr;
    size_t begin;
    size_t end;
} worker_attr;

typedef struct pthread_t_array {
    size_t size;
    pthread_t *data;
} pthread_t_arr;

typedef struct worker_attr_array {
    size_t size;
    worker_attr *data;
} worker_attr_arr;

pthread_t_arr *create_pthread_t_arr(size_t size);
void free_pthread_t_array(pthread_t_arr *arr_ptr);
worker_attr_arr *create_worker_attr_arr(size_t size);
void free_worker_attr_array(worker_attr_arr *arr_ptr);

unsigned long long sum_end_elem_rows(const lover_tria_matrix *mat_ptr);
void *thread_worker(void *void_attr_ptr);
int join_child_threads(const pthread_t child_threads[], size_t n_child_threads);
int set_workers_attr(worker_attr w_attr[],
                     int *sum_end_elem,
                     const lover_tria_matrix *mat_ptr,
                     size_t n_child_threads);

#endif //TP_HOMEWORK2020_MATRIX_OP_H
