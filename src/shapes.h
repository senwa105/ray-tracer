#ifndef SHAPES_H
#define SHAPES_H

#include "pointvector.h"
#include "transformations.h"
#include "light.h"

namespace RT::Shapes {

class Sphere {
    // Assume unit sphere (raidus = 1) at origin (0, 0, 0)
private:
    Transformation transform_;
    Material material_;

public:
    Sphere() noexcept
        : transform_{Transformation::Identity()},
          material_{}
    {}

    Transformation GetTransform() const { return transform_; }
    void SetTransform(const Transformation transform) { transform_ = transform; }

    Material GetMaterial() const { return material_; }
    void SetMaterial(const Material material) { material_ = material; }  

    bool operator==(const Sphere&) const = default;

    Vector NormalAt(const Point point) const;
};

}

#endif
