#include <gtest/gtest.h>
#include <numbers>
#include <cmath>
#include "shapes.h"
#include "pointvector.h"
#include "transformations.h"

TEST(SphereTest, Initialization) {
    auto s = RT::Shapes::Sphere();
    auto id = RT::Transformation::Identity();
    EXPECT_EQ(s.GetTransform(), id);
}

TEST(SphereTest, SetTransform) {
    auto s = RT::Shapes::Sphere();
    auto t = RT::Transformation::Identity() * 4;
    s.SetTransform(t);
    EXPECT_EQ(s.GetTransform(), t);
}

TEST(SphereTest, NormalAt) {
    auto s = RT::Shapes::Sphere();
    auto n = RT::NewVector(1, 0, 0);
    auto p = RT::NewPoint(1, 0, 0);
    EXPECT_EQ(s.NormalAt(p), n);

    n = RT::NewVector(0, 1, 0);
    p = RT::NewPoint(0, 1, 0);
    EXPECT_EQ(s.NormalAt(p), n);

    n = RT::NewVector(0, 0, 1);
    p = RT::NewPoint(0, 0, 1);
    EXPECT_EQ(s.NormalAt(p), n);

    n = RT::NewVector(0, 1, 0);
    p = RT::NewPoint(0, 1, 0);
    EXPECT_EQ(s.NormalAt(p), n);

    float x = sqrt(3) / 3;
    n = RT::NewVector(x, x, x);
    p = RT::NewPoint(x, x, x);
    EXPECT_EQ(s.NormalAt(p), n);
    EXPECT_EQ(Normalize(n), n);
}

TEST(SphereTest, TransformedNormalAt) {
    auto s = RT::Shapes::Sphere();
    s.SetTransform(RT::Translate(0, 1, 0));
    EXPECT_EQ(s.NormalAt(RT::NewPoint(0, 1.70711, -0.70711)),
              RT::NewVector(0, 0.70711, -0.70711));

    s.SetTransform(RT::Scale(1, 0.5, 1) * RT::RotateZ(std::numbers::pi / 5));
    EXPECT_EQ(s.NormalAt(RT::NewPoint(0, std::sqrt(2) / 2, -std::sqrt(2) / 2)),
              RT::NewVector(0, 0.97014, -0.24254));
}

TEST(SphereTest, Material) {
    auto s = RT::Shapes::Sphere();
    EXPECT_EQ(s.GetMaterial(), RT::Material());

    auto m = RT::Material();
    m.ambient = 1;
    s.SetMaterial(m);
    EXPECT_EQ(s.GetMaterial(), m);
}
