#include <iostream>

#include "matrix.hpp"
#include "ray.hpp"
#include "canvas.hpp"

int main() {
    const float CAMERA_Z = -5;
    const float WALL_Z = 10;
    const float WALL_SIZE = 7;

    const int RESOLUTION = 100; 

    auto camera = RT::Point(0, 0, CAMERA_Z);

    float pixelSize = WALL_SIZE / RESOLUTION;
    float half = WALL_SIZE / 2;

    RT::Canvas canvas{RESOLUTION, RESOLUTION};
    RT::Color color{{1, 0, 0}}; // Red
    RT::Shapes::Sphere shape{};
    shape.SetTransform(RT::Shear(1, 0, 0, 0, 0, 0)
                       * RT::Scale(0.5, 1, 1));

    for (size_t y = 0; y < RESOLUTION; ++y) {
        float yWorld = half - pixelSize * y;
        for (size_t x = 0; x < RESOLUTION; ++x) {
            float xWorld = -half + pixelSize * x;
            auto position = RT::Point(xWorld, yWorld, WALL_Z);
            RT::Ray r{camera, Normalize(position - camera)};
            auto xs = RT::Intersect(shape, r);

            auto hit = RT::Hit(xs);
            if (hit)
                canvas.WritePixel(x, y, color);
        }
    }

    RT::Canvas::Save(canvas, "output/image.ppm");
}
