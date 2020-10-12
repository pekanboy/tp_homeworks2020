//
// Created by egoro on 09.10.2020.
//

#include "gtest/gtest.h"
extern "C" {
    #include "matrix.h"
}

TEST(Matrix, Alloc) {
    Matrix *matrix = matrixAlloc(3, -1);

    EXPECT_EQ(matrix, nullptr) << "bad alloc in 'matrixAlloc' function";
}

TEST(Matrix, Fill) {
    const char *name = "../../gtest/testFile/test.txt";
    FILE *file = fopen(name, "r");
    ASSERT_FALSE(file == NULL) << "no open file";

    size_t row, col;

    int res = fscanf(file, "%zu %zu", &row, &col);
    ASSERT_FALSE(res != 2) << "invalid fscanf";
    Matrix *matrix = matrixAlloc(row, col);
    ASSERT_FALSE(matrix == NULL) << "invalid malloc";

    matrixFillOut(matrix, file);

    EXPECT_EQ(matrix->m_matrix[0], 1);
    EXPECT_EQ(matrix->m_matrix[1], 232);
    EXPECT_EQ(matrix->m_matrix[2], 4);
    EXPECT_EQ(matrix->m_matrix[3], 23);
    EXPECT_EQ(matrix->m_matrix[4], -1);
    EXPECT_EQ(matrix->m_matrix[5], 23);
    EXPECT_EQ(matrix->m_matrix[6], -99);
    EXPECT_EQ(matrix->m_matrix[7], 32);
    EXPECT_EQ(matrix->m_matrix[8], 0);

    matrixFree(matrix);
    fclose(file);

}

TEST(Matrix, Sort) {
    Matrix *matrix = matrixAlloc(2, 2);
    ASSERT_FALSE(matrix == NULL);
    size_t length = matrix->m_col * matrix->m_row;

    for (size_t counter = 0; counter < length; ++counter) {
        matrix->m_matrix[counter] = length - counter;
    }

    matrixSort(matrix);

    EXPECT_EQ(matrix->m_matrix[0], 3);
    EXPECT_EQ(matrix->m_matrix[1], 4);
    EXPECT_EQ(matrix->m_matrix[2], 1);
    EXPECT_EQ(matrix->m_matrix[3], 2);

    matrixFree(matrix);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
