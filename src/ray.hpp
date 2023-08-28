#ifndef RAY_H
#define RAY_H

#include "matrix.hpp"
#include "transformations.hpp"

namespace RT {

struct Ray {
    Matrix::Vector4f origin{};
    Matrix::Vector4f direction{};
};

Matrix::Vector4f Position(const Ray& ray, const float time) {
    return ray.origin + ray.direction * time;
}

}

#endif
