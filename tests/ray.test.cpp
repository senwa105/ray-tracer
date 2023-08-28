#include <gtest/gtest.h>
#include "color.hpp"

#include "ray.hpp"
#include "shapes.hpp"
#include "matrix.hpp"

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

TEST(RayTest, SphereIntersection) {
    auto r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    auto s = Shapes::Sphere();

    auto xs = Intersect(s, r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 4.0);
    EXPECT_EQ(xs[1].t, 6.0);
    EXPECT_EQ(*xs[0].object, s);
    EXPECT_EQ(*xs[1].object, s);
}

TEST(RayTest, SphereTangentIntersection) {
    auto r = Ray(Point(0, 1, -5), Vector(0, 0, 1));
    auto s = Shapes::Sphere();

    auto xs = Intersect(s, r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_TRUE(Matrix::ApproxEqual(xs[0].t, 5.0));
    EXPECT_TRUE(Matrix::ApproxEqual(xs[1].t, 5.0));
}

TEST(RayTest, SphereNoIntersection) {
    auto r = Ray(Point(0, 2, -5), Vector(0, 0, 1));
    auto s = Shapes::Sphere();

    auto xs = Intersect(s, r);
    EXPECT_EQ(xs.size(), 0);
}

TEST(RayTest, SphereInsideIntersection) {
    auto r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
    auto s = Shapes::Sphere();

    auto xs = Intersect(s, r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_TRUE(Matrix::ApproxEqual(xs[0].t, -1.0));
    EXPECT_TRUE(Matrix::ApproxEqual(xs[1].t, 1.0));
}

TEST(RayTest, SphereRearIntersection) {
    auto r = Ray(Point(0, 0, 5), Vector(0, 0, 1));
    auto s = Shapes::Sphere();

    auto xs = Intersect(s, r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_TRUE(Matrix::ApproxEqual(xs[0].t, -6.0));
    EXPECT_TRUE(Matrix::ApproxEqual(xs[1].t, -4.0));
}

TEST(RayTest, Intersection) {
    auto s = Shapes::Sphere();
    auto i = Intersection(3.5, s);
    EXPECT_TRUE(Matrix::ApproxEqual(i.t, 3.5));
    EXPECT_EQ(*i.object, s);
}

TEST(RayTest, Intersections) {
    Shapes::Sphere s = Shapes::Sphere();
    Intersection<Shapes::Sphere> i1 = Intersection(1, s);
    Intersection<Shapes::Sphere> i2 = Intersection(2, s);
    auto xs = Intersections<Shapes::Sphere>(i1, i2);
    
    EXPECT_EQ(xs.size(), 2);
    EXPECT_TRUE(Matrix::ApproxEqual(xs[0].t, 1));
    EXPECT_TRUE(Matrix::ApproxEqual(xs[1].t, 2));
}
