#include <gtest/gtest.h>
#include "color.hpp"

#include "ray.hpp"

TEST(RayTest, Initialization) {
    auto o = RT::Point(1, 2, 3);
    auto d = RT::Vector(4, 5, 6);
    auto r = RT::Ray(o, d);

    EXPECT_EQ(r.origin, o);
    EXPECT_EQ(r.direction, d);
}
