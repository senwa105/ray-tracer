#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include <string>
#include <format>
#include <cmath>
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

unsigned int Clamp(const float unclamped, const unsigned int max) {
    if (unclamped < 0)
        return 0;
    if (unclamped > 1)
        return max;
    return std::round(unclamped * max);
}

std::string CanvasToPPM(const Canvas& canvas) {
    const size_t MAX_VALUE = 255;
    const size_t MAX_LINE_LENGTH = 70;

    // Header
    std::string ppm = std::format("P3\n{} {}\n255\n", canvas.GetWidth(), canvas.GetHeight());
    
    // Payload
    for (size_t y = 0; y < canvas.GetHeight(); ++y) {
        std::string line{};

        for (size_t x = 0; x < canvas.GetWidth(); ++x) {
            Color pixel = canvas.PixelAt(x, y);
            std::string pixelString = std::format("{} {} {} ",
                                                   Clamp(pixel.red(), MAX_VALUE),
                                                   Clamp(pixel.green(), MAX_VALUE),
                                                   Clamp(pixel.blue(), MAX_VALUE));

            if (line.length() + pixelString.length() > MAX_LINE_LENGTH) {
                line[line.length() - 1] = '\n';
                ppm += line;
                line.clear();
            }


            line += pixelString;
        }

        line[line.length() - 1] = '\n';
        ppm += line;
    }

    return ppm;
}

}

#endif
