#include <gtest/gtest.h>
#include <string>
#include "canvas.hpp"

class CanvasTest : public ::testing::Test {
protected:
    RT::Canvas c{10, 20};
};

TEST_F(CanvasTest, Initialization) {
    RT::Color black({0, 0, 0});
    for (size_t i = 0; i < 10; ++i)
        for (size_t j = 0; j < 20; ++j)
            EXPECT_EQ(black, c.PixelAt(i, j));
}

TEST_F(CanvasTest, WritePixel) {
    RT::Color red({1, 0, 0});
    c.WritePixel(2, 3, red);
    EXPECT_EQ(red, c.PixelAt(2, 3));
}

TEST_F(CanvasTest, CanvasToPPM) {
    std::string header = RT::CanvasToPPM(c);
    std::string expected = "P3\n"
                           "10 20\n"
                           "255\n";
    EXPECT_EQ(header, expected);
}
