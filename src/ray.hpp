#ifndef RAY_H
#define RAY_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <memory>
#include "matrix.hpp"
#include "transformations.hpp"
#include "shapes.hpp"

namespace RT {

template <typename Shape>
struct Intersection {
    float t{};
    std::unique_ptr<Shape> object{};

    Intersection() = default;
    Intersection(const float tt, Shape& o)
        : t{tt},
          object{std::make_unique<Shape>(o)}
    {}
};

struct Ray {
    Matrix::Vector4f origin{};
    Matrix::Vector4f direction{};
};

Matrix::Vector4f Position(const Ray& ray, const float t) {
    return ray.origin + ray.direction * t;
}

std::vector<float> Intersect(const Shapes::Sphere& sphere, const Ray& ray) {
    Matrix::Vector4f sphereToRay = ray.origin - Point(0, 0, 0);

    float a = Dot(ray.direction, ray.direction);
    float b = 2 * Dot(ray.direction, sphereToRay);
    float c = Dot(sphereToRay, sphereToRay) - 1;
    float discriminant = b*b - 4*a*c;

    std::vector<float> xs{};
    if (discriminant < 0)
        // No intersections
        return xs;
    if (Matrix::ApproxEqual(discriminant, 1)) {
        // One intersection
        xs[0] = xs[1] = (-b + std::sqrt(discriminant)) / (2 * a);
        return xs;
    }
    // Two intersections
    xs.push_back((-b - std::sqrt(discriminant)) / (2 * a));
    xs.push_back((-b + std::sqrt(discriminant)) / (2 * a));

    if (xs[0] > xs[1])
        std::swap(xs[0], xs[1]);
    
    return xs;    
}

}

#endif
