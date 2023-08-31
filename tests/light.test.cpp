#include <gtest/gtest.h>
#include "light.h"

TEST(LightTest, Initialization) {
    auto intensity = RT::Color({1, 1, 1});
    auto position = RT::Point(0, 0, 0);
    auto l = RT::PointLight(intensity, position);

    EXPECT_EQ(l.intensity, intensity);
    EXPECT_EQ(l.position, position);
}
