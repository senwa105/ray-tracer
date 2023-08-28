#include <gtest/gtest.h>
#include "color.hpp"

#include "ray.hpp"

using namespace RT;

TEST(RayTest, Initialization) {
    auto o = Point(1, 2, 3);
    auto d = Vector(4, 5, 6);
    auto r = Ray(o, d);

    EXPECT_EQ(r.origin, o);
    EXPECT_EQ(r.direction, d);
}

TEST(RayTest, Position) {
    auto r = Ray(Point(2, 3, 4), Vector(1, 0, 0));

    EXPECT_EQ(Position(r, 0), Point(2, 3, 4));
    EXPECT_EQ(Position(r, 1), Point(3, 3, 4));
    EXPECT_EQ(Position(r, -1), Point(1, 3, 4));
    EXPECT_EQ(Position(r, 2.5), Point(4.5, 3, 4));
}
