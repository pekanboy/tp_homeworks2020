#include "matrix.h"
#include "matrix_op.h"

int main(int argc, char **argv) {
    const char *file_name = "../../text.txt";

    lover_tria_matrix *mat_ptr = create_matrix_from_file(file_name);
    print_matrix(mat_ptr);

    printf("\n%llu\n", sum_end_elem(mat_ptr));
    printf("\n%llu\n", sum_end_elem_rows(mat_ptr));

    free_matrix(mat_ptr);
}