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
