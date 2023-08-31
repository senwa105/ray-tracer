#ifndef LIGHT_H
#define LIGHT_H

#include "color.h"
#include "transformations.h"

namespace RT {

struct PointLight {
    Matrix::Vector4f position{Point(0, 0, 0)};
    Color intensity{};
};

struct Material {
    Color color{Color({1, 1, 1})};
    float ambient{0.1};
    float diffuse{0.9};
    float specular{0.9};
    float shininess{200.0};

    bool operator==(const Material&) const = default;
};

Color Lighting(const Material& material,
               const PointLight& light,
               const Matrix::Vector4f& point,
               const Matrix::Vector4f& eyeVector,
               const Matrix::Vector4f& normal);

}

#endif
