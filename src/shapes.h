#ifndef SHAPES_H
#define SHAPES_H

#include "matrix.hpp"
#include "light.h"

namespace RT::Shapes {

class Sphere {
    // Assume unit sphere (raidus = 1) at origin (0, 0, 0)
private:
    Matrix::Matrix4f transform_;
    Material material_;

public:
    Sphere() noexcept
        : transform_{Matrix::Matrix4f::Identity()},
          material_{}
    {}

    Matrix::Matrix4f GetTransform() const { return transform_; }
    void SetTransform(const Matrix::Matrix4f transform) { transform_ = transform; }

    Material GetMaterial() const { return material_; }
    void SetMaterial(const Material material) { material_ = material; }  

    bool operator==(const Sphere&) const = default;

    Matrix::Vector4f NormalAt(const Matrix::Vector4f point) const;
};

}

#endif
