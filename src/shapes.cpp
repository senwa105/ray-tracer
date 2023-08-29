#include "shapes.h"
#include "matrix.hpp"
#include "transformations.h"

namespace RT::Shapes {

Matrix::Vector4f Sphere::NormalAt(const Matrix::Vector4f point) const {
    return Normalize(point - Point(0, 0, 0));
}

}
