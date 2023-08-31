#include <gtest/gtest.h>
#include "light.h"

TEST(LightTest, Initialization) {
    auto intensity = RT::Color({1, 1, 1});
    auto position = RT::Point(0, 0, 0);
    auto l = RT::PointLight(intensity, position);

    EXPECT_EQ(l.intensity, intensity);
    EXPECT_EQ(l.position, position);
}

TEST(LightTest, Material) {
    auto m = RT::Material(RT::Color({1, 1, 1}), 0.1, 0.9, 0.9, 200);
    EXPECT_EQ(m.color, RT::Color({1, 1, 1}));
    EXPECT_FLOAT_EQ(m.ambient, 0.1);
    EXPECT_FLOAT_EQ(m.diffuse, 0.9);
    EXPECT_FLOAT_EQ(m.specular, 0.9);
    EXPECT_FLOAT_EQ(m.shininess, 200);
}
