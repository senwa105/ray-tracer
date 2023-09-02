#include "pointvector.h"

#include "matrix.hpp"

namespace RT {

Point NewPoint(const float x, const float y, const float z) {
    return Matrix::Vector4f({x, y, z, 1});
}

Vector NewVector(const float x, const float y, const float z) {
    return Matrix::Vector4f({x, y, z, 0});
}

}
