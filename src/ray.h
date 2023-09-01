#ifndef RAY_H
#define RAY_H

#include <vector>
#include <memory>
#include <optional>
#include <algorithm>
#include "pointvector.hpp"
#include "shapes.h"

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
    Point origin{};
    Vector direction{};
};

Point Position(const Ray& ray, const float t);

Ray Transform(const Ray& ray, const Matrix::Matrix4f& transformation);

std::vector<Intersection<Shapes::Sphere>> Intersect(const Shapes::Sphere& sphere, const Ray& ray);

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
        return std::make_optional(i);   // Return smallest nonnegative value
    }
    return std::nullopt;
}

}

#endif
