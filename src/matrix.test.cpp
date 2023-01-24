#include <gtest/gtest.h>
#include "matrix.hpp"

TEST(MatrixTest, GetRowCount) {
    Matrix4f a;
    EXPECT_EQ(a.GetRowCount(), 4);
    Matrix<int, 19, 23> b;
    EXPECT_EQ(b.GetRowCount(), 19);
}

TEST(MatrixTest, GetColCount) {
    Matrix4f a;
    EXPECT_EQ(a.GetColCount(), 4);
    Matrix<int, 19, 23> b;
    EXPECT_EQ(b.GetColCount(), 23);
}