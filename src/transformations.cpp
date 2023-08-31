#include "transformations.h"

#include <cmath>
#include "matrix.hpp"

namespace RT {

Matrix::Vector4f Point(const float x, const float y, const float z) {
    return Matrix::Vector4f({x, y, z, 1});
}

Matrix::Vector4f Vector(const float x, const float y, const float z) {
    return Matrix::Vector4f({x, y, z, 0});
}

Matrix::Matrix4f Translate(const float x, const float y, const float z) {
    Matrix::Matrix4f t = Matrix::Matrix4f::Identity();
    t(0, 3) = x;
    t(1, 3) = y;
    t(2, 3) = z;
    return t;
}

Matrix::Matrix4f Scale(const float x, const float y, const float z) {
    Matrix::Matrix4f t{};
    t(0, 0) = x;
    t(1, 1) = y;
    t(2, 2) = z;
    t(3, 3) = 1;
    return t;
}

Matrix::Matrix4f RotateX(const float radians) {
    Matrix::Matrix4f t{};
    t(0, 0) = t(3, 3) = 1;
    t(1, 1) = t(2, 2) = std::cos(radians);
    t(1, 2) = -std::sin(radians);
    t(2, 1) = std::sin(radians);
    return t;
}

Matrix::Matrix4f RotateY(const float radians) {
    Matrix::Matrix4f t{};
    t(1, 1) = t(3, 3) = 1;
    t(0, 0) = t(2, 2) = std::cos(radians);
    t(0, 2) = std::sin(radians);
    t(2, 0) = -std::sin(radians);
    return t;
}

Matrix::Matrix4f RotateZ(const float radians) {
    Matrix::Matrix4f t{};
    t(2, 2) = t(3, 3) = 1;
    t(0, 0) = t(1, 1) = std::cos(radians);
    t(0, 1) = -std::sin(radians);
    t(1, 0) = std::sin(radians);
    return t;
}

Matrix::Matrix4f Shear(const float xToY, const float xToZ,
                       const float yToX, const float yToZ,
                       const float zToX, const float zToY) {
    Matrix::Matrix4f t = Matrix::Matrix4f::Identity();
    t(0, 1) = xToY;
    t(0, 2) = xToZ;
    t(1, 0) = yToX;
    t(1, 2) = yToZ;
    t(2, 0) = zToX;
    t(2, 1) = zToY;
    return t;
}

Matrix::Vector4f Reflect(const Matrix::Vector4f& vector, const Matrix::Vector4f& normal) {
    return vector - normal * 2 * Dot(vector, normal);
}

}