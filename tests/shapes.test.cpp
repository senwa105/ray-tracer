#include <gtest/gtest.h>
#include "shapes.h"

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
