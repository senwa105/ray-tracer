#include <gtest/gtest.h>
#include "transformations.hpp"

TEST(TransformationTest, Translation) {
    auto p = RT::Point(-3, 4, 5);
    auto v = RT::Vector(-3, 4, 5);
    auto t = RT::Translation(5, -3, 2);

    auto a = RT::Point(2, 1, 7);
    auto b = RT::Point(-8, 7, 3);
    
    EXPECT_EQ(t * p, a);
    EXPECT_EQ(t.Inverse() * p, b);
    EXPECT_EQ(t * v, v);
}
