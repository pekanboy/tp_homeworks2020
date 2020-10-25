#include "gtest/gtest.h"
extern "C" {
#include "matrix_op.h"
#include "matrix.h"
}

TEST(Stress_test, SmallData) {
    lover_tria_matrix *mat_ptr = create_matrix_from_file("gen_matrix/SmallData.txt");
    ASSERT_FALSE(!mat_ptr);

    EXPECT_EQ(sum_parallel(mat_ptr), sum_sequential(mat_ptr));
    free(mat_ptr);
}

TEST(Stress_test, BigData) {
    lover_tria_matrix *mat_ptr = create_matrix_from_file("gen_matrix/BigData.txt");
    ASSERT_FALSE(!mat_ptr);

    EXPECT_EQ(sum_parallel(mat_ptr), sum_sequential(mat_ptr));
    free(mat_ptr);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}