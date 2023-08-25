#include <gtest/gtest.h>
#include "color.hpp"

using namespace RT;

TEST(ColorTest, Getters) {
    Color a({0.11, 0.22, 0.33});
    EXPECT_FLOAT_EQ(a.red(), 0.11);
    EXPECT_FLOAT_EQ(a.green(), 0.22);
    EXPECT_FLOAT_EQ(a.blue(), 0.33);
}
