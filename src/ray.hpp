#ifndef RAY_H
#define RAY_H

#include "matrix.hpp"
#include "transformations.hpp"

namespace RT {

struct Ray {
    Matrix::Vector4f origin{};
    Matrix::Vector4f direction{};
};

}

#endif
