#ifndef COLOR_H
#define COLOR_H

#include "matrix.hpp"

namespace RT {

class Color {
private:
    Matrix::Vector3f rgb_{};

public:
    Color() noexcept = default;

    Color(const std::array<float, 3> list) noexcept 
        : rgb_(list)
    {}

    const float red() const { return rgb_.X(); }
    const float green() const { return rgb_.Y(); }
    const float blue() const { return rgb_.Z(); }
};

}

#endif
