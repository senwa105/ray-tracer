#include <cmath>
#include <numbers>
#include <gtest/gtest.h>
#include "transformations.hpp"

TEST(TransformationTest, Translate) {
    auto p = RT::Point(-3, 4, 5);
    auto v = RT::Vector(-3, 4, 5);
    auto t = RT::Translate(5, -3, 2);

    auto a = RT::Point(2, 1, 7);
    auto b = RT::Point(-8, 7, 3);
    
    EXPECT_EQ(t * p, a);
    EXPECT_EQ(t.Inverse() * p, b);
    EXPECT_EQ(t * v, v);
}

TEST(TransformationTest, Scale) {
    auto p = RT::Point(-4, 6, 8);
    auto v = RT::Vector(-4, 6, 8);
    auto t = RT::Scale(2, 3, 4);

    auto a = RT::Point(-8, 18, 32);
    auto b = RT::Vector(-8, 18, 32);
    auto c = RT::Vector(-2, 2, 2);

    EXPECT_EQ(t * p, a);
    EXPECT_EQ(t * v, b);
    EXPECT_EQ(t.Inverse() * v, c);
}

TEST(TransformationTest, Reflect) {
    auto p = RT::Point(2, 3, 4);
    auto t = RT::Scale(-1, 1, 1);
    auto a = RT::Point(-2, 3, 4);

    EXPECT_EQ(t * p, a);
}

TEST(TransformationTest, RotateX) {
    auto p = RT::Point(0, 1, 0);
    auto deg45 = RT::RotateX(std::numbers::pi / 4);
    auto deg90 = RT::RotateX(std::numbers::pi / 2);

    auto a = RT::Point(0, std::sqrt(2) / 2, std::sqrt(2) / 2);
    auto b = RT::Point(0, 0, 1);
    auto c = RT::Point(0, std::sqrt(2) / 2, -std::sqrt(2) / 2);

    EXPECT_EQ(deg45 * p, a);
    EXPECT_EQ(deg90 * p, b);
    EXPECT_EQ(deg45.Inverse() * p, c);
}

TEST(TransformationTest, RotateY) {
    auto p = RT::Point(0, 0, 1);
    auto deg45 = RT::RotateY(std::numbers::pi / 4);
    auto deg90 = RT::RotateY(std::numbers::pi / 2);

    auto a = RT::Point(std::sqrt(2) / 2, 0, std::sqrt(2) / 2);
    auto b = RT::Point(1, 0, 0);
    auto c = RT::Point(-std::sqrt(2) / 2, 0, std::sqrt(2) / 2);

    EXPECT_EQ(deg45 * p, a);
    EXPECT_EQ(deg90 * p, b);
    EXPECT_EQ(deg45.Inverse() * p, c);
}

TEST(TransformationTest, RotateZ) {
    auto p = RT::Point(0, 1, 0);
    auto deg45 = RT::RotateZ(std::numbers::pi / 4);
    auto deg90 = RT::RotateZ(std::numbers::pi / 2);

    auto a = RT::Point(-std::sqrt(2) / 2, std::sqrt(2) / 2, 0);
    auto b = RT::Point(-1, 0, 0);
    auto c = RT::Point(std::sqrt(2) / 2, std::sqrt(2) / 2, 0);

    EXPECT_EQ(deg45 * p, a);
    EXPECT_EQ(deg90 * p, b);
    EXPECT_EQ(deg45.Inverse() * p, c);
}

TEST(TransformationTest, Shear) {
    auto p = RT::Point(2, 3, 4);

    auto t1 = RT::Shear(1, 0, 0, 0, 0, 0);
    auto t2 = RT::Shear(0, 1, 0, 0, 0, 0);
    auto t3 = RT::Shear(0, 0, 1, 0, 0, 0);
    auto t4 = RT::Shear(0, 0, 0, 1, 0, 0);
    auto t5 = RT::Shear(0, 0, 0, 0, 1, 0);
    auto t6 = RT::Shear(0, 0, 0, 0, 0, 1);

    auto a1 = RT::Point(5, 3, 4);
    auto a2 = RT::Point(6, 3, 4);
    auto a3 = RT::Point(2, 5, 4);
    auto a4 = RT::Point(2, 7, 4);
    auto a5 = RT::Point(2, 3, 6);
    auto a6 = RT::Point(2, 3, 7);

    EXPECT_EQ(t1 * p, a1);
    EXPECT_EQ(t2 * p, a2);
    EXPECT_EQ(t3 * p, a3);
    EXPECT_EQ(t4 * p, a4);
    EXPECT_EQ(t5 * p, a5);
    EXPECT_EQ(t6 * p, a6);
}
