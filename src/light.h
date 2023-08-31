#ifndef LIGHT_H
#define LIGHT_H

#include "color.h"
#include "transformations.h"

namespace RT {

struct PointLight {
    Color intensity{};
    Matrix::Vector4f position{Point(0, 0, 0)};
};

}

#endif
