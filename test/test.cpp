#include "gtest/gtest.h"
extern "C" {
#include "matrix_op.h"
#include "matrix.h"
#include "define_file.h"
}

TEST(Stress_test, SmallData) {
    lover_tria_matrix *mat_ptr = create_matrix_from_file("gen_matrix/SmallData.txt");
    ASSERT_FALSE(!mat_ptr);

    EXPECT_EQ(sum_parallel(mat_ptr), sum_sequential(mat_ptr));
    free_matrix(mat_ptr);
}

TEST(Stress_test, BigData) {
    lover_tria_matrix *mat_ptr = create_matrix_from_file("gen_matrix/BigData.txt");
    ASSERT_FALSE(!mat_ptr);

    EXPECT_EQ(sum_parallel(mat_ptr), sum_sequential(mat_ptr));
    free_matrix(mat_ptr);
}

TEST(Matrix, Create) {
    lover_tria_matrix *mat_ptr = create_matrix(0, 2);
    EXPECT_EQ(mat_ptr, nullptr);

    mat_ptr = create_matrix(9999999, 9999999);
    EXPECT_EQ(mat_ptr, nullptr);
}

TEST(Matrix, CreateFromFile) {
    lover_tria_matrix *mat_ptr = create_matrix_from_file("QQQQQQQ");
    EXPECT_EQ(mat_ptr, nullptr);

    mat_ptr = create_matrix_from_file("../../test/test_files/ErrorCreate.txt");
    EXPECT_EQ(mat_ptr, nullptr);

    mat_ptr = create_matrix_from_file("../../test/test_files/ErrorData.txt");
    EXPECT_EQ(mat_ptr, nullptr);

    mat_ptr = create_matrix_from_file("../../test/test_files/ErrorSize.txt");
    EXPECT_EQ(mat_ptr, nullptr);
}

TEST(Matrix, SetElem) {
    EXPECT_EQ(set_elem(nullptr, 1, 1), ERROR_ARG_FROM_FUNC);
}

TEST(MatrixOp, ErrorsAttr) {
    EXPECT_EQ(create_pthread_t_arr(99999999999), nullptr);
    EXPECT_EQ(create_worker_attr_arr(99999999999), nullptr);
    EXPECT_EQ(set_workers_attr(nullptr, nullptr, nullptr, 1), ERROR_ARG_FROM_FUNC);
    EXPECT_EQ(join_child_threads(nullptr, 1), ERROR_ARG_FROM_FUNC);

    int *res = (int *)thread_worker(nullptr);
    EXPECT_EQ(*res, ERROR_ARG_FROM_FUNC);
    free(res);

    EXPECT_EQ(sum_parallel(nullptr), ERROR_ARG_FROM_FUNC);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}