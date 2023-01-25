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
    Matrix2i a({1, 2, 3, 4});
    EXPECT_EQ(1, a(0,0));
    EXPECT_EQ(2, a(0,1));
    EXPECT_EQ(3, a(1,0));
    EXPECT_EQ(4, a(1,1));
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