#include "ray.h"

#include <vector>
#include <cmath>
#include "matrix.hpp"
#include "transformations.h"
#include "shapes.h"

namespace RT {

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

}
