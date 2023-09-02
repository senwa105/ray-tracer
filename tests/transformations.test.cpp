#include <cmath>
#include <numbers>
#include <gtest/gtest.h>
#include "transformations.h"
#include "pointvector.h"

TEST(TransformationsTest, Translate) {
    auto p = RT::NewPoint(-3, 4, 5);
    auto v = RT::NewVector(-3, 4, 5);
    auto t = RT::Translate(5, -3, 2);

    auto a = RT::NewPoint(2, 1, 7);
    auto b = RT::NewPoint(-8, 7, 3);
    
    EXPECT_EQ(t * p, a);
    EXPECT_EQ(t.Inverse() * p, b);
    EXPECT_EQ(t * v, v);
}

TEST(TransformationsTest, Scale) {
    auto p = RT::NewPoint(-4, 6, 8);
    auto v = RT::NewVector(-4, 6, 8);
    auto t = RT::Scale(2, 3, 4);

    auto a = RT::NewPoint(-8, 18, 32);
    auto b = RT::NewVector(-8, 18, 32);
    auto c = RT::NewVector(-2, 2, 2);

    EXPECT_EQ(t * p, a);
    EXPECT_EQ(t * v, b);
    EXPECT_EQ(t.Inverse() * v, c);
}

TEST(TransformationsTest, Reflect) {
    auto p = RT::NewPoint(2, 3, 4);
    auto t = RT::Scale(-1, 1, 1);
    auto a = RT::NewPoint(-2, 3, 4);

    EXPECT_EQ(t * p, a);
}

TEST(TransformationsTest, RotateX) {
    auto p = RT::NewPoint(0, 1, 0);
    auto deg45 = RT::RotateX(std::numbers::pi / 4);
    auto deg90 = RT::RotateX(std::numbers::pi / 2);

    auto a = RT::NewPoint(0, std::sqrt(2) / 2, std::sqrt(2) / 2);
    auto b = RT::NewPoint(0, 0, 1);
    auto c = RT::NewPoint(0, std::sqrt(2) / 2, -std::sqrt(2) / 2);

    EXPECT_EQ(deg45 * p, a);
    EXPECT_EQ(deg90 * p, b);
    EXPECT_EQ(deg45.Inverse() * p, c);
}

TEST(TransformationsTest, RotateY) {
    auto p = RT::NewPoint(0, 0, 1);
    auto deg45 = RT::RotateY(std::numbers::pi / 4);
    auto deg90 = RT::RotateY(std::numbers::pi / 2);

    auto a = RT::NewPoint(std::sqrt(2) / 2, 0, std::sqrt(2) / 2);
    auto b = RT::NewPoint(1, 0, 0);
    auto c = RT::NewPoint(-std::sqrt(2) / 2, 0, std::sqrt(2) / 2);

    EXPECT_EQ(deg45 * p, a);
    EXPECT_EQ(deg90 * p, b);
    EXPECT_EQ(deg45.Inverse() * p, c);
}

TEST(TransformationsTest, RotateZ) {
    auto p = RT::NewPoint(0, 1, 0);
    auto deg45 = RT::RotateZ(std::numbers::pi / 4);
    auto deg90 = RT::RotateZ(std::numbers::pi / 2);

    auto a = RT::NewPoint(-std::sqrt(2) / 2, std::sqrt(2) / 2, 0);
    auto b = RT::NewPoint(-1, 0, 0);
    auto c = RT::NewPoint(std::sqrt(2) / 2, std::sqrt(2) / 2, 0);

    EXPECT_EQ(deg45 * p, a);
    EXPECT_EQ(deg90 * p, b);
    EXPECT_EQ(deg45.Inverse() * p, c);
}

TEST(TransformationsTest, Shear) {
    auto p = RT::NewPoint(2, 3, 4);

    auto t1 = RT::Shear(1, 0, 0, 0, 0, 0);
    auto t2 = RT::Shear(0, 1, 0, 0, 0, 0);
    auto t3 = RT::Shear(0, 0, 1, 0, 0, 0);
    auto t4 = RT::Shear(0, 0, 0, 1, 0, 0);
    auto t5 = RT::Shear(0, 0, 0, 0, 1, 0);
    auto t6 = RT::Shear(0, 0, 0, 0, 0, 1);

    auto a1 = RT::NewPoint(5, 3, 4);
    auto a2 = RT::NewPoint(6, 3, 4);
    auto a3 = RT::NewPoint(2, 5, 4);
    auto a4 = RT::NewPoint(2, 7, 4);
    auto a5 = RT::NewPoint(2, 3, 6);
    auto a6 = RT::NewPoint(2, 3, 7);

    EXPECT_EQ(t1 * p, a1);
    EXPECT_EQ(t2 * p, a2);
    EXPECT_EQ(t3 * p, a3);
    EXPECT_EQ(t4 * p, a4);
    EXPECT_EQ(t5 * p, a5);
    EXPECT_EQ(t6 * p, a6);
}

TEST(TransformationsTest, ChainedTransformations) {
    auto p = RT::NewPoint(1, 0, 1);
    auto r = RT::RotateX(std::numbers::pi / 2);
    auto s = RT::Scale(5, 5, 5);
    auto t = RT::Translate(10, 5, 7);

    auto a = r * p;
    a = s * a;
    a = t * a;

    EXPECT_EQ(t * s * r * p, a);
}

TEST(TransformationsTest, ReflectAcrossNormal) {
    auto v = RT::NewVector(1, -1, 0);
    auto n = RT::NewVector(0, 1, 0);
    EXPECT_EQ(RT::Reflect(v, n), RT::NewVector(1, 1, 0));

    v = RT::NewVector(0, -1, 0);
    n = RT::NewVector(std::sqrt(2) / 2, std::sqrt(2) / 2, 0);
    EXPECT_EQ(RT::Reflect(v, n), RT::NewVector(1, 0, 0));
}
