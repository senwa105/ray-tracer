#ifndef LIGHT_H
#define LIGHT_H

#include "pointvector.h"
#include "color.h"

namespace RT {

struct PointLight {
    Point position{NewPoint(0, 0, 0)};
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
               const Point& point,
               const Vector& eyeVector,
               const Vector& normal);

}

#endif
