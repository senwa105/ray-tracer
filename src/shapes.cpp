#include "shapes.h"
#include "pointvector.h"

namespace RT::Shapes {

Vector Sphere::NormalAt(const Point point) const {
    auto objectPoint = transform_.Inverse() * point;
    auto objectNormal = objectPoint - NewPoint(0, 0, 0);
    auto normal = transform_.Inverse().Transpose() * objectNormal;
    normal.W() = 0;
    return Normalize(normal);
}

}
