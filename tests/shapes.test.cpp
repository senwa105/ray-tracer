#include <gtest/gtest.h>
#include "shapes.h"
#include "transformations.h"

TEST(SphereTest, Initialization) {
    auto s = RT::Shapes::Sphere();
    auto id = Matrix::Matrix4f::Identity();
    EXPECT_EQ(s.GetTransform(), id);
}

TEST(SphereTest, SetTransform) {
    auto s = RT::Shapes::Sphere();
    auto t = Matrix::Matrix4f::Identity() * 4;
    s.SetTransform(t);
    EXPECT_EQ(s.GetTransform(), t);
}

TEST(SphereTest, NormalAt) {
    auto s = RT::Shapes::Sphere();
    auto n = RT::Vector(1, 0, 0);
    auto p = RT::Point(1, 0, 0);
    EXPECT_EQ(s.NormalAt(p), n);

    n = RT::Vector(0, 1, 0);
    p = RT::Point(0, 1, 0);
    EXPECT_EQ(s.NormalAt(p), n);

    n = RT::Vector(0, 0, 1);
    p = RT::Point(0, 0, 1);
    EXPECT_EQ(s.NormalAt(p), n);

    n = RT::Vector(0, 1, 0);
    p = RT::Point(0, 1, 0);
    EXPECT_EQ(s.NormalAt(p), n);

    float x = sqrt(3) / 3;
    n = RT::Vector(x, x, x);
    p = RT::Point(x, x, x);
    EXPECT_EQ(s.NormalAt(p), n);
    EXPECT_EQ(Normalize(n), n);
}
