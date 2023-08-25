#include <gtest/gtest.h>
#include "matrix.hpp"

using Matrix::Matrix2i;
using Matrix::Matrix3i;
using Matrix::Matrix4i;
using Matrix::Vector2i;
using Matrix::Vector3i;
using Matrix::Vector4i;
using Matrix::Matrix2f;
using Matrix::Matrix3f;
using Matrix::Matrix4f;
using Matrix::Vector2f;
using Matrix::Vector3f;
using Matrix::Vector4f;

TEST(MatrixTest, GetRowCount) {
    Matrix4f a;
    EXPECT_EQ(a.GetRowCount(), 4);
    Matrix::Matrix<int, 19, 23> b;
    EXPECT_EQ(b.GetRowCount(), 19);
}

TEST(MatrixTest, GetColCount) {
    Matrix4f a;
    EXPECT_EQ(a.GetColCount(), 4);
    Matrix::Matrix<int, 19, 23> b;
    EXPECT_EQ(b.GetColCount(), 23);
}

TEST(MatrixTest, SubscriptOperator) {
    Matrix::Matrix<int, 2, 3> a({1, 2, 3, 4, 5, 6});
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
    Matrix::Matrix<double, 2, 2> a({1.0f, 2.0f, 3.0f, 4.0f});
    Matrix::Matrix<double, 2, 2> b({1.1f, 2.2f, 3.3f, 4.4f});
    Matrix::Matrix<double, 2, 2> c({1.000001f, 2.000002f, 3.000003f, 4.000004f});

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
    Matrix4i a({0, 1, 2,  4,
                1, 2, 4,  8,
                2, 4, 8,  16,
                4, 8, 16, 32});
    EXPECT_EQ(Matrix4i::Identity() * a, a);

    Vector4f b({1.5f, 2.5f, 3.5f, 4.5f});
    EXPECT_EQ(Matrix4f::Identity() * b, b);
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

TEST(MatrixTest, Transpose) {
    Matrix4f a({0, 9, 3, 0,
                9, 8, 0, 8, 
                1, 8, 5, 3, 
                0, 0, 5, 8});
    Matrix4f b({0, 9, 1, 0, 
                9, 8, 8, 0, 
                3, 0, 5, 5, 
                0, 8, 3, 8});
    EXPECT_EQ(Matrix4f::Transpose(a), b);
    EXPECT_EQ(Matrix4f::Transpose(b), a);

    Matrix4f id = Matrix4f::Identity();
    EXPECT_EQ(Matrix4f::Transpose(id), id);
}

TEST(MatrixTest, Determinant2x2) {
    Matrix2i a({1, 5, -3, 2});
    EXPECT_EQ(a.Determinant(), 17);

    Matrix2f b({1.5f, 2.5f, 3.5f, 4.5f});
    EXPECT_EQ(b.Determinant(), -2.0f);
}

TEST(MatrixTest, Submatrix) {
    Matrix::Matrix<int, 4, 3> a({0, 1,  2,
                                 3, 4,  5,
                                 6, 7,  8,
                                 9, 10, 11});
    Matrix::Matrix<int, 3, 2> b({4,  5,
                                 7,  8,
                                 10, 11});
    Matrix::Matrix<int, 2, 1> c({4,
                                 10});

    EXPECT_EQ(a.Submatrix(0, 0), b);
    EXPECT_EQ(b.Submatrix(1, 1), c);
}

TEST(MatrixTest, Minor) {
    Matrix3i a{{3,  5,  0,
                2, -1, -7,
                6, -1,  5}};

    EXPECT_EQ(a.Minor(0, 0), -12);
    EXPECT_EQ(a.Minor(1, 0), 25);
}

TEST(MatrixTest, Cofactor) {
    Matrix3i a{{3,  5,  0,
                2, -1, -7,
                6, -1,  5}};

    EXPECT_EQ(a.Cofactor(0, 0), -12);
    EXPECT_EQ(a.Cofactor(1, 0), -25);
}

TEST(MatrixTest, DeterminantGeneral) {
    Matrix3i a{{ 1, 2,  6,
                -5, 8, -4,
                 2, 6,  4}};
    Matrix4i b{{-2, -8,  3,  5,
                -3,  1,  7,  3,
                 1,  2, -9,  6,
                -6,  7,  7, -9}};

    EXPECT_EQ(a.Determinant(), -196);
    EXPECT_EQ(b.Determinant(), -4071);
}

TEST(MatrixTest, IsInvertible) {
    Matrix4i a{{6,  4, 4,  4,
                5,  5, 7,  6,
                4, -9, 3, -7,
                9,  1, 7, -6}};
    Matrix4i b{{-4,  2, -2, -3,
                 9,  6,  2,  6,
                 0, -5,  1, -5,
                 0,  0,  0,  0}};

    EXPECT_TRUE(a.IsInvertible());
    EXPECT_FALSE(b.IsInvertible());
}

TEST(MatrixTest, NoninvertibleMatrix) {
    Matrix4i b{{-4,  2, -2, -3,
                 9,  6,  2,  6,
                 0, -5,  1, -5,
                 0,  0,  0,  0}};
    EXPECT_THROW(b.Inverse(), std::runtime_error);
}

TEST(MatrixTest, Inverse) {
    Matrix4f a{{-5,  2,  6, -8,
                 1, -5,  1,  8,
                 7,  7, -6, -7,
                 1, -3,  7,  4}};
    Matrix4f aa{{ 0.21805,  0.45113,  0.24060, -0.04511,
                -0.80827, -1.45677, -0.44361,  0.52068,
                -0.07895, -0.22368, -0.05263,  0.19737,
                -0.52256, -0.81391, -0.30075,  0.30639}};
    Matrix4f b{{ 8, -5,  9,  2,
                 7,  5,  6,  1,
                -6,  0,  9,  6,
                -3,  0, -9, -4}};
    Matrix4f bb{{-0.15385, -0.15385, -0.28205, -0.53846,
                -0.07692,  0.12308,  0.02564,  0.03077,
                 0.35897,  0.35897,  0.43590,  0.92308,
                -0.69231, -0.69231, -0.76923, -1.92308}};
    Matrix4f c{{ 9,  3,  0,  9,
                -5, -2, -6, -3,
                -4,  9,  6,  4,
                -7,  6,  6,  2}};
    Matrix4f cc{{-0.04074, -0.07778,  0.14444, -0.22222,
                 -0.07778,  0.03333,  0.36667, -0.33333,
                 -0.02901, -0.14630, -0.10926,  0.12963,
                  0.17778,  0.06667, -0.26667,  0.33333}};

    EXPECT_EQ(a.Inverse(), aa);
    EXPECT_EQ(a.Inverse() * a, Matrix4f::Identity());
    EXPECT_EQ(b.Inverse(), bb);
    EXPECT_EQ(b.Inverse() * b, Matrix4f::Identity());
    EXPECT_EQ(c.Inverse(), cc);
    EXPECT_EQ(c.Inverse() * c, Matrix4f::Identity());
}

TEST(MatrixTest, MultiplyByInverse) {
    Matrix4f a{{ 3, -9,  7,  3,
                 3, -8,  2, -9,
                -4,  4,  4,  1,
                -6,  5, -1,  1}};
    Matrix4f b{{8,  2, 2, 2,
                3, -1, 7, 0,
                7,  0, 5, 4,
                6, -2, 0, 5}};
    Matrix4f c = a * b;
    EXPECT_EQ(c * b.Inverse(), a);
}
