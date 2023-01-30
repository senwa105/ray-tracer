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

TEST(MatrixTest, SubscriptOperator) {
    Matrix<int, 2, 3> a({1, 2, 3, 4, 5, 6});
    EXPECT_EQ(1, a(0, 0));
    EXPECT_EQ(2, a(0, 1));
    EXPECT_EQ(3, a(0, 2));
    EXPECT_EQ(4, a(1, 0));
    EXPECT_EQ(5, a(1, 1));
    EXPECT_EQ(6, a(1, 2));
}

TEST(MatrixTest, FloatComparison) {
    Matrix2f a({1.0f, 2.0f, 3.0f, 4.0f});
    Matrix2f b({1.1f, 2.2f, 3.3f, 4.4f});
    Matrix2f c({1.000001f, 2.000002f, 3.000003f, 4.000004f});

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a == c);
}

TEST(MatrixTest, DoubleComparison) {
    Matrix2f a({1.0f, 2.0f, 3.0f, 4.0f});
    Matrix2f b({1.1f, 2.2f, 3.3f, 4.4f});
    Matrix2f c({1.000001f, 2.000002f, 3.000003f, 4.000004f});

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a == c);
}

TEST(MatrixTest, ScalarAddition) {
    Matrix2i a({1, 2, 3, 4});
    Matrix2i b({3, 4, 5, 6});
    EXPECT_EQ(a + 2, b);

    Matrix2f c;
    Matrix2f d({1.5f, 1.5f, 1.5f, 1.5f});
    EXPECT_EQ(c + 1.5, d);
}

TEST(MatrixTest, ScalarSubtraction) {
    Matrix2i a({1, 2, 3, 4});
    Matrix2i b({-1, 0, 1, 2});
    EXPECT_EQ(a - 2, b);

    Matrix2f c;
    Matrix2f d({-1.5f, -1.5f, -1.5f, -1.5f});
    EXPECT_EQ(c - 1.5, d);
}

TEST(MatrixTest, ScalarMultiplication) {
    Matrix2i a({1, 2, 3, 4});
    Matrix2i b({2, 4, 6, 8});
    EXPECT_EQ(a * 2, b);

    Matrix2f c({1.0f, 1.0f, 1.0f, 1.0f});
    Matrix2f d({-1.5f, -1.5f, -1.5f, -1.5f});
    EXPECT_EQ(c * -1.5, d);
}

TEST(MatrixTest, Negation) {
    Matrix2i a({1, 2, 3, 4});
    Matrix2i b({-1, -2, -3, -4});
    EXPECT_EQ(-a, b);
}

TEST(MatrixTest, MatrixAddition) {
    Matrix2i a({1, 2, 3, 4});
    Matrix2i b({1, 1, 1, 1});
    Matrix2i c({2, 3, 4, 5});
    EXPECT_EQ(a + b, c);

    Matrix2f d({1, 1, 1, 1});
    Matrix2f e({1.5f, 1.5f, 1.5f, 1.5f});
    Matrix2f f({2.5f, 2.5f, 2.5f, 2.5f});
    EXPECT_EQ(d + e, f);
}

TEST(MatrixTest, MatrixSubtraction) {
    Matrix2i a({1, 2, 3, 4});
    Matrix2i b({1, 1, 1, 1});
    Matrix2i c({0, 1, 2, 3});
    EXPECT_EQ(a - b, c);

    Matrix2f d({1, 1, 1, 1});
    Matrix2f e({1.5f, 1.5f, 1.5f, 1.5f});
    Matrix2f f({-0.5f, -0.5f, -0.5f, -0.5f});
    EXPECT_EQ(d - e, f);
}

TEST(MatrixTest, MatrixMultiplication) {
    Matrix4f a({1, 2, 3, 4, 
                5, 6, 7, 8, 
                9, 8, 7, 6, 
                5, 4, 3, 2,});
    Matrix4f b({-2, 1, 2,  3, 
                 3, 2, 1, -1, 
                 4, 3, 6,  5, 
                 1, 2, 7,  8,});
    Matrix4f c({20, 22,  50,  48, 
                44, 54, 114, 108, 
                40, 58, 110, 102, 
                16, 26,  46,  42,});
    EXPECT_EQ(a * b, c);
}