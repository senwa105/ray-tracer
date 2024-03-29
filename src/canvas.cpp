#include "canvas.h"

#include <vector>
#include <string>
#include <string_view>
#include <format>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <cerrno>
#include <cstdio>
#include "color.h"

namespace RT {

const Color Canvas::PixelAt(const size_t x, const size_t y) const {
    if (x < 0 || x > width_)
        throw std::out_of_range("Requested x coord is out of bounds");
    if (y < 0 || y > height_)
        throw std::out_of_range("Requested y coord is out of bounds");

    return pixels_[y*width_ + x];
}

void Canvas::WritePixel(const size_t x, const size_t y, Color& color) {
    if (x < 0 || x > width_)
        throw std::out_of_range("Requested x coord is out of bounds");
    if (y < 0 || y > height_)
        throw std::out_of_range("Requested y coord is out of bounds");

    pixels_[y*width_ + x] = color;
}

std::string Canvas::ToPPM(const Canvas& canvas) {
    const size_t MAX_LINE_LENGTH = 70;

    // Header
    std::string ppm = std::format("P3\n{} {}\n255\n", canvas.GetWidth(), canvas.GetHeight());
    
    // Payload
    for (size_t y = 0; y < canvas.GetHeight(); ++y) {
        std::string line{};

        for (size_t x = 0; x < canvas.GetWidth(); ++x) {
            ColorClamped8Bit pixel = canvas.PixelAt(x, y).Clamp8Bit();
            std::string pixelString = std::format("{} {} {} ",
                                                pixel.Red(),
                                                pixel.Green(),
                                                pixel.Blue());

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

void Canvas::Save(const Canvas& canvas, const std::string_view filepath) {
    std::filesystem::path path(filepath);
    if (!std::filesystem::is_directory(path.parent_path()))
        throw std::runtime_error(std::format("RT::Canvas::Save(): directory {} does not exist", path.parent_path().string()));

    std::ofstream file{};
    file.open(path);
    if (!file.is_open()) {
        std::perror("RT::Canvas::Save():");
        throw std::runtime_error("RT::Canvas::Save(): failed to open file");
    }

    file << ToPPM(canvas);
    file.close();
}

}
