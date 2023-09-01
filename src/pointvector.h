#ifndef POINTVECTOR_H
#define POINTVECTOR_H

#include "matrix.hpp"

namespace RT {

using Point = Matrix::Vector4f;
using Vector = Matrix::Vector4f;

Point NewPoint(const float x, const float y, const float z);
Vector NewVector(const float x, const float y, const float z);

}

#endif
