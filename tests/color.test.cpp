#include <gtest/gtest.h>
#include "color.h"

using namespace RT;

class ColorTest : public ::testing::Test {
protected:
    void SetUp() override {
        a = Color({0.11, 0.22, 0.33});
        b = Color({0.5, 0.6, 0.7});
    }

    Color a;
    Color b;
};

TEST_F(ColorTest, Getters) {
    EXPECT_FLOAT_EQ(a.Red(), 0.11);
    EXPECT_FLOAT_EQ(a.Green(), 0.22);
    EXPECT_FLOAT_EQ(a.Blue(), 0.33);
}

TEST_F(ColorTest, Comparison) {
    Color aa({0.11, 0.22, 0.33});
    Color bb({0.5, 0.6, 0.7});

    EXPECT_EQ(aa, a);
    EXPECT_EQ(bb, b);

    EXPECT_NE(a, b);
    EXPECT_NE(aa, bb);
}

TEST_F(ColorTest, Addition) {
    Color c({0.61, 0.82, 1.03});
    EXPECT_EQ(a + b, c);
}

TEST_F(ColorTest, Subtraction) {
    Color c({0.39, 0.38, 0.37});
    EXPECT_EQ(b - a, c);
}

TEST_F(ColorTest, Multiplication) {
    Color c({0.055, 0.132, 0.231});
    EXPECT_EQ(a * b, c);
}

TEST_F(ColorTest, Clamp8Bit) {
    ColorClamped8Bit clampedA({28, 56, 84});
    ColorClamped8Bit clampedB({128, 153, 179});

    Color c({-0.5, 1, 1.5});
    ColorClamped8Bit clampedC({0, 255, 255});

    EXPECT_EQ(a.Clamp8Bit(), clampedA);
    EXPECT_EQ(b.Clamp8Bit(), clampedB);
    EXPECT_EQ(c.Clamp8Bit(), clampedC);
}
