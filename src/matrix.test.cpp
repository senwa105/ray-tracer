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

TEST(MatrixTest, IdentityMatrix) {
    
}

TEST(MatrixTest, VectorComponentAccess) {
    Vector4f v({1, 2, 3, 4});
    EXPECT_FLOAT_EQ(v.X(), 1);
    EXPECT_FLOAT_EQ(v.Y(), 2);
    EXPECT_FLOAT_EQ(v.Z(), 3);
    EXPECT_FLOAT_EQ(v.W(), 4);
}

TEST(MatrixTest, VectorNorm) {
    Vector3f v({1, 0, 0});
    EXPECT_EQ(v.Norm(), 1);
    v = Vector3f({0, 1, 0});
    EXPECT_EQ(v.Norm(), 1);
    v = Vector3f({0, 0, 1});
    EXPECT_EQ(v.Norm(), 1);
    v = Vector3f({1, 2, 3});
    EXPECT_FLOAT_EQ(v.Norm(), sqrt(14));
    v = Vector3f({-1, -2, -3});
    EXPECT_FLOAT_EQ(v.Norm(), sqrt(14));
}

TEST(MatrixTest, VectorNormalization) {
    Vector3f v({4, 0, 0});
    Vector3f w({1, 0, 0});
    auto norm = Normalize(v);
    EXPECT_EQ(norm, w);
    EXPECT_FLOAT_EQ(norm.Norm(), 1);

    v = Vector3f({1, 2, 3});
    w = Vector3f({1, 2, 3}) * (1 / sqrt(14));
    norm = Normalize(v);
    EXPECT_EQ(norm, w);
    EXPECT_FLOAT_EQ(norm.Norm(), 1);
}

TEST(MatrixTest, VectorDotProduct) {
    Vector3i a({1, 2, 3});
    Vector3i b({2, 3, 4});
    EXPECT_EQ(Dot(a, b),  20);

    Vector3f c({-0.5, 2.5, 4.0});
    Vector3f d({1.5, -3.0, -2.5});
    EXPECT_FLOAT_EQ(Dot(c, d), -18.25);
}

TEST(MatrixTest, VectorCrossProduct) {
    Vector3i a({1, 2, 3});
    Vector3i b({2, 3, 4});
    Vector3i c({-1, 2, -1});
    EXPECT_EQ(Cross(a, b),  c);
    EXPECT_EQ(Cross(b, a), -c);

    Vector3f d({-0.5, 2.5, 4.0});
    Vector3f e({1.5, -3.0, -2.5});
    Vector3f f({5.75, 4.75, -2.25});
    EXPECT_EQ(Cross(d, e),  f);
    EXPECT_EQ(Cross(e, d), -f);
}