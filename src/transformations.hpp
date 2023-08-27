#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

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

}

#endif
