#include <gtest/gtest.h>
#include <cmath>
#include "light.h"

TEST(LightTest, Initialization) {
    auto position = RT::NewPoint(0, 0, 0);
    auto intensity = RT::Color({1, 1, 1});
    auto l = RT::PointLight(position, intensity);

    EXPECT_EQ(l.position, position);
    EXPECT_EQ(l.intensity, intensity);
}

TEST(LightTest, Material) {
    auto m = RT::Material();
    EXPECT_EQ(m.color, RT::Color({1, 1, 1}));
    EXPECT_FLOAT_EQ(m.ambient, 0.1);
    EXPECT_FLOAT_EQ(m.diffuse, 0.9);
    EXPECT_FLOAT_EQ(m.specular, 0.9);
    EXPECT_FLOAT_EQ(m.shininess, 200);
}

TEST(LightTest, EyeBetweenLightAndSurface) {
    auto m = RT::Material();
    auto position = RT::NewPoint(0, 0, 0);

    auto eyeVector = RT::NewVector(0, 0, -1);
    auto normal = RT::NewVector(0, 0, -1);
    auto light = RT::PointLight(RT::NewPoint(0, 0, -10), RT::Color({1, 1, 1}));

    EXPECT_EQ(RT::Lighting(m, light, position, eyeVector, normal), RT::Color({1.9, 1.9, 1.9}));
}

TEST(LightTest, EyeBetweenLightAndSurface45DegreeOffset) {
    auto m = RT::Material();
    auto position = RT::NewPoint(0, 0, 0);

    auto eyeVector = RT::NewVector(0, std::sqrt(2) / 2, -std::sqrt(2) / 2);
    auto normal = RT::NewVector(0, 0, -1);
    auto light = RT::PointLight(RT::NewPoint(0, 0, -10), RT::Color({1, 1, 1}));

    EXPECT_EQ(RT::Lighting(m, light, position, eyeVector, normal), RT::Color({1.0, 1.0, 1.0}));
}

TEST(LightTest, EyeOppositeSurface45DegreeOffset) {
    auto m = RT::Material();
    auto position = RT::NewPoint(0, 0, 0);

    auto eyeVector = RT::NewVector(0, 0, -1);
    auto normal = RT::NewVector(0, 0, -1);
    auto light = RT::PointLight(RT::NewPoint(0, 10, -10), RT::Color({1, 1, 1}));

    EXPECT_EQ(RT::Lighting(m, light, position, eyeVector, normal), RT::Color({0.7364, 0.7364, 0.7364}));
}

TEST(LightTest, EyeInReflectionPath) {
    auto m = RT::Material();
    auto position = RT::NewPoint(0, 0, 0);

    auto eyeVector = RT::NewVector(0, -std::sqrt(2) / 2, -std::sqrt(2) / 2);
    auto normal = RT::NewVector(0, 0, -1);
    auto light = RT::PointLight(RT::NewPoint(0, 10, -10), RT::Color({1, 1, 1}));

    EXPECT_EQ(RT::Lighting(m, light, position, eyeVector, normal), RT::Color({1.63639, 1.63639, 1.63639}));
}

TEST(LightTest, LightBehindSurface) {
    auto m = RT::Material();
    auto position = RT::NewPoint(0, 0, 0);

    auto eyeVector = RT::NewVector(0, 0, -1);
    auto normal = RT::NewVector(0, 0, -1);
    auto light = RT::PointLight(RT::NewPoint(0, 0, 10), RT::Color({1, 1, 1}));

    EXPECT_EQ(RT::Lighting(m, light, position, eyeVector, normal), RT::Color({0.1, 0.1, 0.1}));
}
