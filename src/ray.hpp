#ifndef RAY_H
#define RAY_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <memory>
#include <optional>
#include "matrix.hpp"
#include "transformations.hpp"
#include "shapes.hpp"

namespace RT {

template <typename Shape>
struct Intersection {
    float t{};
    std::shared_ptr<Shape> object{};

    Intersection() = default;
    Intersection(const float tt, const Shape& o)
        : t{tt},
          object{std::make_shared<Shape>(o)}
    {}

    friend bool operator==(const Intersection& a, const Intersection& b) {
        return (a.t == b.t) && (a.object == b.object);
    }
};

struct Ray {
    Matrix::Vector4f origin{};
    Matrix::Vector4f direction{};
};

Matrix::Vector4f Position(const Ray& ray, const float t) {
    return ray.origin + ray.direction * t;
}

Ray Transform(const Ray& ray, const Matrix::Matrix4f& transformation) {
    return Ray{transformation * ray.origin, transformation * ray.direction};
}

std::vector<Intersection<Shapes::Sphere>> Intersect(const Shapes::Sphere& sphere, const Ray& ray) {
    Ray ray2 = Transform(ray, sphere.GetTransform().Inverse());
    Matrix::Vector4f sphereToRay = ray2.origin - Point(0, 0, 0);

    float a = Dot(ray2.direction, ray2.direction);
    float b = 2 * Dot(ray2.direction, sphereToRay);
    float c = Dot(sphereToRay, sphereToRay) - 1;
    float discriminant = b*b - 4*a*c;

    std::vector<Intersection<Shapes::Sphere>> xs{};
    if (discriminant < 0)
        // No intersections
        return xs;

    // One or two intersections
    float t1 = (-b - std::sqrt(discriminant)) / (2 * a);
    float t2 = (-b + std::sqrt(discriminant)) / (2 * a);

    if (t1 > t2)
        std::swap(t1, t2);

    xs.push_back(Intersection<Shapes::Sphere>{t1, sphere});
    xs.push_back(Intersection<Shapes::Sphere>{t2, sphere});

    return xs;    
}

template<typename Shape>
std::vector<Intersection<Shape>> Intersections(std::same_as<Intersection<Shape>> auto& ...inter) {
    std::vector<Intersection<Shape>> intersections{};
    (intersections.push_back(inter), ...);
    std::sort(intersections.begin(), intersections.end(), [](Intersection<Shape>& a, Intersection<Shape>& b) {
        return a.t < b.t;
    });
    return intersections;
}

template<typename Shape>
std::optional<Intersection<Shape>> Hit(const std::vector<Intersection<Shape>>& intersections) {
    // Assume intersections is already sorted
    for (const Intersection<Shape>& i : intersections) {
        if (i.t < 0)
            continue;
        return std::make_optional(i);   // Return smalleste nonnegative value
    }
    return std::nullopt;
}

}

#endif
