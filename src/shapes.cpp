#include "shapes.h"
#include "matrix.hpp"
#include "transformations.h"

namespace RT::Shapes {

Matrix::Vector4f Sphere::NormalAt(const Matrix::Vector4f point) const {
    auto objectPoint = transform_.Inverse() * point;
    auto objectNormal = objectPoint - Point(0, 0, 0);
    auto normal = transform_.Inverse().Transpose() * objectNormal;
    normal.W() = 0;
    return Normalize(normal);
}

}
