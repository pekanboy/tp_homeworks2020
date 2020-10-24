#define _GNU_SOURCE

#include <unistd.h>
#include <sched.h>
#include <pthread.h>

#include "matrix.h"
#include "matrix_op.h"

pthread_mutex_t sums_lock;

pthread_t_arr *create_pthread_t_arr(size_t size) {
    pthread_t_arr *arr_ptr = calloc(1, sizeof(pthread_t_arr));
    if (arr_ptr == NULL) {
        return NULL;
    }

    arr_ptr->data = calloc(size, sizeof(pthread_t));
    if (arr_ptr->data == NULL) {
        free(arr_ptr);
        return NULL;
    }

    arr_ptr->size = size;

    return arr_ptr;
}


void free_pthread_t_array(pthread_t_arr *arr_ptr) {
    if (arr_ptr != NULL) {
        free(arr_ptr->data);
    }
    free(arr_ptr);
}



worker_attr_arr *create_worker_attr_arr(size_t size) {
    worker_attr_arr *arr_ptr = calloc(1, sizeof(worker_attr_arr));
    if (arr_ptr == NULL) {
        return NULL;
    }

    arr_ptr->data = calloc(size, sizeof(worker_attr));
    if (arr_ptr->data == NULL) {
        free(arr_ptr);
        return NULL;
    }

    arr_ptr->size = size;

    return arr_ptr;
}


void free_worker_attr_array(worker_attr_arr *arr_ptr) {
    if (arr_ptr != NULL) {
        free(arr_ptr->data);
    }
    free(arr_ptr);
}

int set_workers_attr(worker_attr w_attr[],
                     int *sum_end_elem,
                     const lover_tria_matrix *mat_ptr,
                     size_t n_child_threads) {
    if (w_attr == NULL || sum_end_elem == NULL || mat_ptr == NULL) {
        return -1;
    }

    size_t size = mat_ptr->size / n_child_threads;

    for (size_t i = 0; i <  n_child_threads; ++i) {
        w_attr[i].sums_arr_ptr = sum_end_elem;
        w_attr[i].mat_ptr = mat_ptr;
        w_attr[i].begin = i * size;

        if (i + 1 != n_child_threads) {
            w_attr[i].end = (i + 1) * size;
        } else {
            w_attr[i].end = mat_ptr->size;
        }
    }

    return 0;
}

int join_child_threads(const pthread_t child_threads[], size_t n_child_threads) {
    if (child_threads == NULL) {
        return -1;
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

    if (attr_ptr == NULL || attr_ptr->sums_arr_ptr == NULL || attr_ptr->mat_ptr == NULL) {
        *return_stat = -1;
        return return_stat;
    }

    register size_t begin = attr_ptr->begin;
    register size_t end = attr_ptr->end;
    const register lover_tria_matrix *mat_ptr = attr_ptr->mat_ptr;

    size_t counter = 0;
    size_t t = 1;
    while (counter < mat_ptr->size) {
        if (counter >= begin && counter < end) {
            int res = get_elem(mat_ptr, counter);
            if (res == -1) {
                return NULL;
            }
            *attr_ptr->sums_arr_ptr += res;
        }
        counter += ++t;
    }

//    register double *target_sums_array_ptr = attr_ptr->sums_arr_ptr->data;
//    pthread_mutex_lock(&sums_lock);
//    for (size_t j = 0; j < cols; j++) {
//        target_sums_array_ptr[j] += tmp_arr_ptr_data[j];
//    }
//    pthread_mutex_unlock(&sums_lock);
//
//    free_double_array(tmp_arr_ptr);

    *return_stat = 0;
    return return_stat;
}

unsigned long long sum_end_elem_rows(const lover_tria_matrix *mat_ptr) {
    if (mat_ptr == NULL) {
        return -1;
    }

    long proc_number = sysconf(_SC_NPROCESSORS_ONLN);
    if (proc_number < 1) {
        return -2;
    }
    size_t n_child_threads =  proc_number;

    int sum_end_elem = 0;

    pthread_t_arr *child_threads = create_pthread_t_arr(n_child_threads);
    if (child_threads == NULL) {
        return -3;
    }
    worker_attr_arr *w_attr = create_worker_attr_arr(n_child_threads);
    if (w_attr == NULL) {
        free_pthread_t_array(child_threads);
        return -3;
    }

    if (set_workers_attr(w_attr->data, &sum_end_elem, mat_ptr, n_child_threads) != 0) {
        free_pthread_t_array(child_threads);
        free_worker_attr_array(w_attr);
        return -4;
    }

    for (size_t i = 0; i <  n_child_threads ; i++) {
        if (pthread_create(&child_threads->data[i], NULL, thread_worker, &w_attr->data[i]) != 0) {
            join_child_threads(child_threads->data, n_child_threads);
            free_pthread_t_array(child_threads);
            free_worker_attr_array(w_attr);
            return -4;
        }

        // set affinity
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(i, &cpuset);

        if (pthread_setaffinity_np(child_threads->data[i], sizeof(cpu_set_t), &cpuset) != 0) {
            join_child_threads(child_threads->data, n_child_threads);
            free_pthread_t_array(child_threads);
            free_worker_attr_array(w_attr);
            return -4;
        }
    }

    join_child_threads(child_threads->data, n_child_threads);
    free_pthread_t_array(child_threads);
    free_worker_attr_array(w_attr);
    return sum_end_elem;
}
