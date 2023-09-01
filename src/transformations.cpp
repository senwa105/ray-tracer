#include "transformations.h"

#include <cmath>
#include "pointvector.hpp"

namespace RT {

Point NewPoint(const float x, const float y, const float z) {
    return Vector({x, y, z, 1});
}

Vector NewVector(const float x, const float y, const float z) {
    return Vector({x, y, z, 0});
}

Transformation Translate(const float x, const float y, const float z) {
    Transformation t = Transformation::Identity();
    t(0, 3) = x;
    t(1, 3) = y;
    t(2, 3) = z;
    return t;
}

Transformation Scale(const float x, const float y, const float z) {
    Transformation t{};
    t(0, 0) = x;
    t(1, 1) = y;
    t(2, 2) = z;
    t(3, 3) = 1;
    return t;
}

Transformation RotateX(const float radians) {
    Transformation t{};
    t(0, 0) = t(3, 3) = 1;
    t(1, 1) = t(2, 2) = std::cos(radians);
    t(1, 2) = -std::sin(radians);
    t(2, 1) = std::sin(radians);
    return t;
}

Transformation RotateY(const float radians) {
    Transformation t{};
    t(1, 1) = t(3, 3) = 1;
    t(0, 0) = t(2, 2) = std::cos(radians);
    t(0, 2) = std::sin(radians);
    t(2, 0) = -std::sin(radians);
    return t;
}

Transformation RotateZ(const float radians) {
    Transformation t{};
    t(2, 2) = t(3, 3) = 1;
    t(0, 0) = t(1, 1) = std::cos(radians);
    t(0, 1) = -std::sin(radians);
    t(1, 0) = std::sin(radians);
    return t;
}

Transformation Shear(const float xToY, const float xToZ,
                       const float yToX, const float yToZ,
                       const float zToX, const float zToY) {
    Transformation t = Transformation::Identity();
    t(0, 1) = xToY;
    t(0, 2) = xToZ;
    t(1, 0) = yToX;
    t(1, 2) = yToZ;
    t(2, 0) = zToX;
    t(2, 1) = zToY;
    return t;
}

Vector Reflect(const Vector& vector, const Vector& normal) {
    return vector - normal * 2 * Dot(vector, normal);
}

}
