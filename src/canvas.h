#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include <string>
#include "color.h"

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

    const Color PixelAt(const size_t x, const size_t y) const;
    void WritePixel(const size_t x, const size_t y, Color& color);

    static std::string ToPPM(const Canvas& canvas);

    static void Save(const Canvas& canvas, const std::string_view filepath);
};

}

#endif
