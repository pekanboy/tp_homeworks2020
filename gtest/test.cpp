#include "gtest/gtest.h"
extern "C" {
    #include "include/matrix.h"
}


TEST(MatrixTEST1, Alloc) {
    Matrix *matrix = matrix_Alloc(1111111111, 1111111111);

    EXPECT_EQ(matrix, nullptr) << "bad alloc in 'matrixAlloc' function";
}

TEST(MatrixTEST2, FillOut1) {
    const char *name = "../../gtest/testFile/test.txt";

    FILE *file = fopen(name, "r");
    ASSERT_FALSE(file == NULL) << "no open file";

    size_t row, col;

    int res = fscanf(file, "%zu %zu", &row, &col);
    ASSERT_FALSE(res != 2) << "invalid fscanf";
    Matrix *matrix = matrix_Alloc(row, col);
    ASSERT_FALSE(matrix == NULL) << "invalid malloc";

    matrix_Fill_Out(matrix, file);

    EXPECT_EQ(matrix->m_matrix[0], 1);
    EXPECT_EQ(matrix->m_matrix[1], 232);
    EXPECT_EQ(matrix->m_matrix[2], 4);
    EXPECT_EQ(matrix->m_matrix[3], 23);
    EXPECT_EQ(matrix->m_matrix[4], -1);
    EXPECT_EQ(matrix->m_matrix[5], 23);
    EXPECT_EQ(matrix->m_matrix[6], -99);
    EXPECT_EQ(matrix->m_matrix[7], 32);
    EXPECT_EQ(matrix->m_matrix[8], 0);

    fclose(file);
    matrix_Free(matrix);

}

TEST(MatrixTEST2, FillOut2) {
    const char *name = "../../gtest/testFile/test2.txt";

    FILE *file = fopen(name, "r");
    ASSERT_FALSE(file == NULL) << "no open file";

    size_t row, col;

    int res = fscanf(file, "%zu %zu", &row, &col);
    ASSERT_FALSE(res != 2) << "invalid fscanf";
    Matrix *matrix = matrix_Alloc(row, col);
    ASSERT_FALSE(matrix == NULL) << "invalid malloc";

    EXPECT_EQ(matrix_Fill_Out(matrix, file), false);


    fclose(file);
    matrix_Free(matrix);

}

TEST(MatrixTEST4, Printf) {
    const char *name = "../../gtest/testFile/test.txt";

    FILE *file = fopen(name, "r");
    ASSERT_FALSE(file == NULL) << "no open file";

    size_t row, col;

    int res = fscanf(file, "%zu %zu", &row, &col);
    ASSERT_FALSE(res != 2) << "invalid fscanf";
    Matrix *matrix = matrix_Alloc(row, col);
    ASSERT_FALSE(matrix == NULL) << "invalid malloc";

    matrix_Fill_Out(matrix, file);

    fclose(file);

    FILE *f = fopen("no.txt", "wr");

    matrix_Printf(matrix, f);

    matrix_Fill_Out(matrix, f);

    EXPECT_EQ(matrix->m_matrix[0], 1);
    EXPECT_EQ(matrix->m_matrix[1], 232);
    EXPECT_EQ(matrix->m_matrix[2], 4);
    EXPECT_EQ(matrix->m_matrix[3], 23);
    EXPECT_EQ(matrix->m_matrix[4], -1);
    EXPECT_EQ(matrix->m_matrix[5], 23);
    EXPECT_EQ(matrix->m_matrix[6], -99);
    EXPECT_EQ(matrix->m_matrix[7], 32);
    EXPECT_EQ(matrix->m_matrix[8], 0);

    matrix_Free(matrix);
    fclose(f);
}

TEST(MatrixTEST3, Sort) {
    Matrix *matrix = matrix_Alloc(2, 2);
    ASSERT_FALSE(matrix == NULL);
    size_t length = matrix->m_col * matrix->m_row;

    for (size_t counter = 0; counter < length; ++counter) {
        matrix->m_matrix[counter] = length - counter;
    }

    matrix_Sort(matrix);

    EXPECT_EQ(matrix->m_matrix[0], 3);
    EXPECT_EQ(matrix->m_matrix[1], 4);
    EXPECT_EQ(matrix->m_matrix[2], 1);
    EXPECT_EQ(matrix->m_matrix[3], 2);

    matrix_Free(matrix);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
