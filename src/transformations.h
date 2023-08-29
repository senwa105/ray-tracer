#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "matrix.hpp"

namespace RT {

Matrix::Vector4f Point(const float x, const float y, const float z);
Matrix::Vector4f Vector(const float x, const float y, const float z);

Matrix::Matrix4f Translate(const float x, const float y, const float z);

Matrix::Matrix4f Scale(const float x, const float y, const float z);

Matrix::Matrix4f RotateX(const float radians);
Matrix::Matrix4f RotateY(const float radians);
Matrix::Matrix4f RotateZ(const float radians);

Matrix::Matrix4f Shear(const float xToY, const float xToZ,
                       const float yToX, const float yToZ,
                       const float zToX, const float zToY);

}

#endif
