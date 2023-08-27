#ifndef COLOR_H
#define COLOR_H

#include "matrix.hpp"

namespace RT {

template<typename T>
class ColorBase {
protected:
    Matrix::Matrix<T, 3, 1> rgb_{};

    ColorBase() noexcept = default;

    ColorBase(const std::array<T, 3> list) noexcept 
        : rgb_(list)
    {}

    ColorBase(const Matrix::Matrix<T, 3, 1> mat) noexcept
        : rgb_(mat)
    {}

public:
    const float red() const { return rgb_.X(); }
    const float green() const { return rgb_.Y(); }
    const float blue() const { return rgb_.Z(); }

    friend bool operator==(const ColorBase& a, const ColorBase& b) {
        return a.rgb_ == b.rgb_;
    }

    friend bool operator!=(const ColorBase& a, const ColorBase& b) {
        return a.rgb_ != b.rgb_;
    }


};

namespace {

template<typename T>
T Clamp(const float unclamped, const T max) {
    if (unclamped < 0)
        return 0;
    if (unclamped > 1)
        return max;
    return std::round(unclamped * max);
}

}

class ColorClamped8Bit : public ColorBase<unsigned int> {
public:
    ColorClamped8Bit() noexcept = default;

    ColorClamped8Bit(const std::array<unsigned int, 3> list) noexcept 
        : ColorBase(list)
    {}

    ColorClamped8Bit(const Matrix::Matrix<unsigned int, 3, 1> mat) noexcept
        : ColorBase(mat)
    {} 
};

class Color : public ColorBase<float> {
public:
    Color() noexcept = default;

    Color(const std::array<float, 3> list) noexcept 
        : ColorBase(list)
    {}

    Color(const Matrix::Vector3f mat) noexcept
        : ColorBase(mat)
    {}

    ColorClamped8Bit Clamp8Bit() const {
        const unsigned int MAX_VALUE = 255;

        return ColorClamped8Bit({
            Clamp<unsigned int>(this->red(), MAX_VALUE),
            Clamp<unsigned int>(this->green(), MAX_VALUE),
            Clamp<unsigned int>(this->blue(), MAX_VALUE),
        });
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
