#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include <array>
#include "color.hpp"

namespace RT {

class Canvas {
private:
    const size_t width_{};
    const size_t height_{};
    std::vector<Color> pixels_{};

public:
    Canvas(const size_t width, const size_t height) noexcept
        : width_(width),
          height_(height),
          pixels_(width * height)
    {}

    const size_t GetWidth() const { return width_; }
    const size_t GetHeight() const { return height_; }

    const Color PixelAt(const size_t x, const size_t y) const {
        if (x < 0 || x > width_)
            throw std::out_of_range("Requested x coord is out of bounds");
        if (y < 0 || y > height_)
            throw std::out_of_range("Requested y coord is out of bounds");

        return pixels_[y*width_ + x];
    }

    void WritePixel(const size_t x, const size_t y, Color& color) {
        if (x < 0 || x > width_)
            throw std::out_of_range("Requested x coord is out of bounds");
        if (y < 0 || y > height_)
            throw std::out_of_range("Requested y coord is out of bounds");

        pixels_[y*width_ + x] = color;
    }
};

}

#endif
