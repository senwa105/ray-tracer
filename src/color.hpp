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

    Color(const Matrix::Vector3f mat) noexcept
        : rgb_(mat)
    {}

    const float red() const { return rgb_.X(); }
    const float green() const { return rgb_.Y(); }
    const float blue() const { return rgb_.Z(); }

    friend bool operator==(const Color& a, const Color& b) {
        return a.rgb_ == b.rgb_;
    }

    friend bool operator!=(const Color& a, const Color& b) {
        return a.rgb_ != b.rgb_;
    }

    friend Color operator+(const Color& a, const Color& b) {
        return Color(a.rgb_ + b.rgb_);
    }

    friend Color operator-(const Color& a, const Color& b) {
        return Color(a.rgb_ - b.rgb_);
    }

    friend Color operator*(const Color& a, const Color& b) {
        return Color(Hadamard(a.rgb_, b.rgb_));
    }
};

}

#endif
