#ifndef SHAPES_H
#define SHAPES_H

#include "matrix.hpp"

namespace RT::Shapes {

class Sphere {
    // Assume unit sphere (raidus = 1) at origin (0, 0, 0)
private:
    Matrix::Matrix4f transform_;

public:
    Sphere() noexcept
        : transform_{Matrix::Matrix4f::Identity()}
    {}

    Matrix::Matrix4f GetTransform() const { return transform_; }
    void SetTransform(const Matrix::Matrix4f transform) { transform_ = transform; }

    bool operator==(const Sphere&) const = default;
};

}

#endif
