#include <gtest/gtest.h>
#include <string>
#include "canvas.hpp"

class CanvasTest : public ::testing::Test {
protected:
    size_t width = 5;
    size_t height = 3;
    RT::Canvas c{width, height};
};

TEST_F(CanvasTest, Initialization) {
    RT::Color black({0, 0, 0});
    for (size_t i = 0; i < width; ++i)
        for (size_t j = 0; j < height; ++j)
            EXPECT_EQ(black, c.PixelAt(i, j));
}

TEST_F(CanvasTest, WritePixel) {
    RT::Color red({1, 0, 0});
    c.WritePixel(2, 3, red);
    EXPECT_EQ(red, c.PixelAt(2, 3));
}

TEST_F(CanvasTest, CanvasToPPM) {
    auto c1 = RT::Color({1.5, 0, 0});
    auto c2 = RT::Color({0, 0.5, 0});
    auto c3 = RT::Color({-0.5, 0, 1});
    c.WritePixel(0, 0, c1);
    c.WritePixel(2, 1, c2);
    c.WritePixel(4, 2, c3);

    std::string expected = "P3\n"
                           "5 3\n"
                           "255\n"
                           "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
                           "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
                           "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";

    EXPECT_EQ(CanvasToPPM(c), expected);
}

TEST_F(CanvasTest, PPMSplitLines) {
    size_t width = 8, height = 2;
    RT::Canvas canvas{width, height};
    RT::Color color ({1, 0.8, 0.6});
    for (size_t i = 0; i < width; ++i)
        for (size_t j = 0; j < height; ++j)
            canvas.WritePixel(i, j, color);

    std::string expected = "P3\n"
                           "8 2\n"
                           "255\n"
                           "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153\n"
                           "255 204 153 255 204 153 255 204 153\n"
                           "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153\n"
                           "255 204 153 255 204 153 255 204 153\n";

    auto ppm = RT::CanvasToPPM(canvas);
    EXPECT_EQ(ppm, expected);
}
