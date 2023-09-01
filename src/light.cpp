#include "light.h"

#include <cmath>
#include "pointvector.hpp"

namespace RT {

Color Lighting(const Material& material,
               const PointLight& light,
               const Point& point,
               const Vector& eyeVector,
               const Vector& normal) {
    // Combine surface color and light color
    auto effectiveColor = material.color * light.intensity;

    // Find direction to light source
    auto lightVector = Normalize(light.position - point);

    // Find ambient lighting contribution
    auto ambient = effectiveColor * material.ambient;

    // Find cosine of the angle between lightVector and normal
    auto lightDotNormal = Dot(lightVector, normal);

    Color diffuse{}, specular{};    // Initialize to black
    if (lightDotNormal >= 0) {
        // Find diffuse lighting contribution
        diffuse = effectiveColor * material.diffuse * lightDotNormal;

        // Find cosine of the angle between reflection and eyeVector
        auto reflection = Reflect(-lightVector, normal);
        auto reflectDotEye = Dot(reflection, eyeVector);

        if (reflectDotEye > 0) {
            // Compute specular lighting contribution
            auto specularFactor = std::pow(reflectDotEye, material.shininess);
            specular = light.intensity * material.specular * specularFactor;
        }
    }

    return ambient + diffuse + specular;
}

}
