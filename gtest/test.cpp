//
// Created by egoro on 09.10.2020.
//

#include "gtest/gtest.h"
#include "../include/matrix.h"

TEST(Matrix, Alloc) {
    Matrix *matrix = matrixAlloc(0,(size_t)10);
    EXPECT_EQ(NULL, matrix);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
