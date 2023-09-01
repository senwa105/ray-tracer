#include <iostream>

#include "matrix.hpp"
#include "transformations.h"
#include "ray.h"
#include "light.h"
#include "canvas.h"

int main() {
    const float CAMERA_Z = -5;
    const float WALL_Z = 10;
    const float WALL_SIZE = 7;

    const int RESOLUTION = 500; 

    auto camera = RT::NewPoint(0, 0, CAMERA_Z);

    float pixelSize = WALL_SIZE / RESOLUTION;
    float half = WALL_SIZE / 2;

    RT::Canvas canvas{RESOLUTION, RESOLUTION};

    RT::Shapes::Sphere shape{};
    // shape.SetTransform(RT::Shear(1, 0, 0, 0, 0, 0)
    //                    * RT::Scale(0.5, 1, 1));
    auto mat = RT::Material();
    mat.color = RT::Color({1, 0.2, 1});
    shape.SetMaterial(mat);

    auto lightPosition = RT::NewPoint(-10, 10, -10);
    auto lightColor = RT::Color({1, 1, 1});
    auto light = RT::PointLight(lightPosition, lightColor);

    for (size_t y = 0; y < RESOLUTION; ++y) {
        float yWorld = half - pixelSize * y;
        for (size_t x = 0; x < RESOLUTION; ++x) {
            float xWorld = -half + pixelSize * x;
            auto position = RT::NewPoint(xWorld, yWorld, WALL_Z);
            auto ray = RT::Ray(camera, Normalize(position - camera));
            auto xs = RT::Intersect(shape, ray);

            auto hit = RT::Hit(xs);
            if (hit) {
                auto point = RT::Position(ray, hit->t);
                auto normal = hit->object->NormalAt(point);
                auto eye = -ray.direction;

                auto color = RT::Lighting(hit->object->GetMaterial(), light, point, eye, normal);
                canvas.WritePixel(x, y, color);
            }
        }
    }

    RT::Canvas::Save(canvas, "output/image.ppm");
}
