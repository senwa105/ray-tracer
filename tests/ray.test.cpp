#include <gtest/gtest.h>
#include "ray.h"
#include "transformations.h"
#include "shapes.h"
#include "matrix.hpp"

using namespace RT;

TEST(RayTest, Initialization) {
    auto o = NewPoint(1, 2, 3);
    auto d = NewVector(4, 5, 6);
    auto r = Ray(o, d);

    EXPECT_EQ(r.origin, o);
    EXPECT_EQ(r.direction, d);
}

TEST(RayTest, Position) {
    auto r = Ray(NewPoint(2, 3, 4), NewVector(1, 0, 0));

    EXPECT_EQ(Position(r, 0), NewPoint(2, 3, 4));
    EXPECT_EQ(Position(r, 1), NewPoint(3, 3, 4));
    EXPECT_EQ(Position(r, -1), NewPoint(1, 3, 4));
    EXPECT_EQ(Position(r, 2.5), NewPoint(4.5, 3, 4));
}

TEST(RayTest, SphereIntersection) {
    auto r = Ray(NewPoint(0, 0, -5), NewVector(0, 0, 1));
    auto s = Shapes::Sphere();

    auto xs = Intersect(s, r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].t, 4.0);
    EXPECT_EQ(xs[1].t, 6.0);
    EXPECT_EQ(*xs[0].object, s);
    EXPECT_EQ(*xs[1].object, s);
}

TEST(RayTest, SphereTangentIntersection) {
    auto r = Ray(NewPoint(0, 1, -5), NewVector(0, 0, 1));
    auto s = Shapes::Sphere();

    auto xs = Intersect(s, r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_TRUE(Matrix::ApproxEqual(xs[0].t, 5.0));
    EXPECT_TRUE(Matrix::ApproxEqual(xs[1].t, 5.0));
}

TEST(RayTest, SphereNoIntersection) {
    auto r = Ray(NewPoint(0, 2, -5), NewVector(0, 0, 1));
    auto s = Shapes::Sphere();

    auto xs = Intersect(s, r);
    EXPECT_EQ(xs.size(), 0);
}

TEST(RayTest, SphereInsideIntersection) {
    auto r = Ray(NewPoint(0, 0, 0), NewVector(0, 0, 1));
    auto s = Shapes::Sphere();

    auto xs = Intersect(s, r);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_TRUE(Matrix::ApproxEqual(xs[0].t, -1.0));
    EXPECT_TRUE(Matrix::ApproxEqual(xs[1].t, 1.0));
}

TEST(RayTest, SphereRearIntersection) {
    auto r = Ray(NewPoint(0, 0, 5), NewVector(0, 0, 1));
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
    auto s = Shapes::Sphere();
    auto i1 = Intersection(1, s);
    auto i2 = Intersection(2, s);
    auto xs = Intersections<Shapes::Sphere>(i1, i2);
    
    EXPECT_EQ(xs.size(), 2);
    EXPECT_TRUE(Matrix::ApproxEqual(xs[0].t, 1));
    EXPECT_TRUE(Matrix::ApproxEqual(xs[1].t, 2));
}

TEST(RayTest, Hit) {
    auto s = Shapes::Sphere();

    auto i1 = Intersection(1, s);
    auto i2 = Intersection(2, s);
    auto xs = Intersections<Shapes::Sphere>(i2, i1);
    EXPECT_EQ(*Hit(xs), i1);

    i1 = Intersection(-1, s);
    i2 = Intersection(1, s);
    xs = Intersections<Shapes::Sphere>(i2, i1);
    EXPECT_EQ(*Hit(xs), i2);

    i1 = Intersection(-2, s);
    i2 = Intersection(-1, s);
    xs = Intersections<Shapes::Sphere>(i2, i1);
    EXPECT_FALSE(Hit(xs));

    i1 = Intersection(5, s);
    i2 = Intersection(7, s);
    auto i3 = Intersection(-3, s);
    auto i4 = Intersection(2, s);
    xs = Intersections<Shapes::Sphere>(i1, i2, i3, i4);
    EXPECT_EQ(*Hit(xs), i4);
}

TEST(RayTest, Transform) {
    auto r = Ray(NewPoint(1, 2, 3), NewVector(0, 1, 0));

    auto t = Translate(3, 4, 5);
    auto o1 = NewPoint(4, 6, 8);
    auto d1 = NewVector(0, 1, 0);
    auto r2 = Transform(r, t);  
    EXPECT_EQ(r2.origin, o1);
    EXPECT_EQ(r2.direction, d1);

    auto s = Scale(2, 3, 4);
    auto o2 = NewPoint(2, 6, 12);
    auto d2 = NewVector(0, 3, 0);
    auto r3 = Transform(r, s);
    EXPECT_EQ(r3.origin, o2);
    EXPECT_EQ(r3.direction, d2);
}

TEST(RayTest, IntersectScaledSphere) {
    auto r = Ray(NewPoint(0, 0, -5), NewVector(0, 0, 1));
    auto s = Shapes::Sphere();

    s.SetTransform(Scale(2, 2, 2));
    auto xs = Intersect(s, r);

    EXPECT_EQ(xs.size(), 2);
    EXPECT_TRUE(Matrix::ApproxEqual(xs[0].t, 3));
    EXPECT_TRUE(Matrix::ApproxEqual(xs[1].t, 7));

    s.SetTransform(Translate(5, 0, 0));
    xs = Intersect(s, r);

    EXPECT_EQ(xs.size(), 0);
}
