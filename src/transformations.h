#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "pointvector.hpp"

namespace RT {

using Transformation = Matrix::Matrix4f;

Point NewPoint(const float x, const float y, const float z);
Vector NewVector(const float x, const float y, const float z);

Transformation Translate(const float x, const float y, const float z);

Transformation Scale(const float x, const float y, const float z);

Transformation RotateX(const float radians);
Transformation RotateY(const float radians);
Transformation RotateZ(const float radians);

Transformation Shear(const float xToY, const float xToZ,
                       const float yToX, const float yToZ,
                       const float zToX, const float zToY);

Vector Reflect(const Vector& vector, const Vector& normal);

}

#endif
