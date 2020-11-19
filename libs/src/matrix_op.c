// "Copyright [2020] <Aleksey Egorov>"

#include <math.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "define_file.h"
#include "matrix.h"
#include "matrix_op.h"

pthread_mutex_t sums_lock;

pthread_t_arr *create_pthread_t_arr(size_t size) {
    pthread_t_arr *arr_ptr = calloc(1, sizeof(pthread_t_arr));
    if (!arr_ptr) {
        return ERROR_MEMORY_ALLOC;
    }

    arr_ptr->data = calloc(size, sizeof(pthread_t));
    if (!arr_ptr->data) {
        free(arr_ptr);
        return ERROR_MEMORY_ALLOC;
    }

    arr_ptr->size = size;

    return arr_ptr;
}


void free_pthread_t_array(pthread_t_arr *arr_ptr) {
    if (arr_ptr != ERROR_MEMORY_ALLOC) {
        free(arr_ptr->data);
    }
    free(arr_ptr);
}

worker_attr_arr *create_worker_attr_arr(size_t size) {
    worker_attr_arr *arr_ptr = calloc(1, sizeof(worker_attr_arr));
    if (!arr_ptr) {
        return ERROR_MEMORY_ALLOC;
    }

    arr_ptr->data = calloc(size, sizeof(worker_attr));
    if (!arr_ptr->data) {
        free(arr_ptr);
        return ERROR_MEMORY_ALLOC;
    }

    arr_ptr->size = size;

    return arr_ptr;
}


void free_worker_attr_array(worker_attr_arr *arr_ptr) {
    if (arr_ptr != ERROR_MEMORY_ALLOC) {
        free(arr_ptr->data);
    }
    free(arr_ptr);
}

int set_workers_attr(worker_attr w_attr[],
                     int sum_end_elem[],
                     const lover_tria_matrix *mat_ptr,
                     size_t n_child_threads) {
    if (!w_attr || !sum_end_elem || !mat_ptr) {
        return ERROR_ARG_FROM_FUNC;
    }

    size_t size = mat_ptr->size / n_child_threads;

    for (size_t i = 0; i < n_child_threads; ++i) {
        w_attr[i].sums_arr_ptr = sum_end_elem + i;
        w_attr[i].mat_ptr = mat_ptr;
        w_attr[i].begin = i * size;

        if (i + 1 != n_child_threads) {
            w_attr[i].end = (i + 1) * size;
        } else {
            w_attr[i].end = mat_ptr->size;
        }
    }

    return EXIT_SUCCESS;
}

int join_child_threads(const pthread_t child_threads[],
                       size_t n_child_threads) {
    if (!child_threads) {
        return ERROR_ARG_FROM_FUNC;
    }

    int status = 0;
    for (size_t i = 0; i < n_child_threads; i++) {
        if (child_threads[i] > 0) {
            void *stat = 0;

            if (pthread_join(child_threads[i], &stat) != 0) {
                status = -1;
            }
            int *casted_stat = stat;
            if (*casted_stat != 0) {
                status = -1;
            }

            free(stat);
        }
    }

    return status;
}

void *thread_worker(void *void_attr_ptr) {
    worker_attr *attr_ptr = void_attr_ptr;

    int *return_stat = calloc(1, sizeof(int));

    if (attr_ptr == NULL ||
        attr_ptr->sums_arr_ptr == NULL ||
        attr_ptr->mat_ptr == NULL) {
        *return_stat = ERROR_ARG_FROM_FUNC;
        return return_stat;
    }

    *attr_ptr->sums_arr_ptr = sum_sequential(attr_ptr->mat_ptr,
                                             attr_ptr->begin,
                                             attr_ptr->end);

    *return_stat = EXIT_SUCCESS;
    return return_stat;
}

int sum_parallel(const lover_tria_matrix *mat_ptr) {
    if (!mat_ptr) {
        return ERROR_ARG_FROM_FUNC;
    }

    int64_t proc_number = sysconf(_SC_NPROCESSORS_ONLN);
    if (proc_number < 1) {
        return ERROR_THREAD_COUNT;
    }
    size_t n_child_threads = proc_number;
    int *sum_end_elem = (int *) calloc(n_child_threads, sizeof(int));
    if (!sum_end_elem) {
        return ERROR_CREATE_THREAD;
    }

    pthread_t_arr *child_threads = create_pthread_t_arr(n_child_threads);
    if (!child_threads) {
        free(sum_end_elem);
        return ERROR_CREATE_THREAD;
    }
    worker_attr_arr *w_attr = create_worker_attr_arr(n_child_threads);
    if (!w_attr) {
        free(sum_end_elem);
        free_pthread_t_array(child_threads);
        return ERROR_CREATE_THREAD;
    }

    if (set_workers_attr(w_attr->data,
                         sum_end_elem,
                         mat_ptr,
                         n_child_threads) != 0) {
        free(sum_end_elem);
        free_pthread_t_array(child_threads);
        free_worker_attr_array(w_attr);
        return ERROR_CREATE_THREAD;
    }

    for (size_t i = 0; i < n_child_threads; i++) {
        if (pthread_create(&child_threads->data[i],
                           NULL,
                           thread_worker,
                           &w_attr->data[i]) != 0) {
            free(sum_end_elem);
            join_child_threads(child_threads->data, n_child_threads);
            free_pthread_t_array(child_threads);
            free_worker_attr_array(w_attr);
            return ERROR_CREATE_THREAD;
        }
    }
    join_child_threads(child_threads->data, n_child_threads);
    free_pthread_t_array(child_threads);
    free_worker_attr_array(w_attr);

    int sum = 0;
    for (size_t i = 0; i < n_child_threads; ++i) {
        sum += sum_end_elem[i];
    }

    free(sum_end_elem);

    return sum;
}
