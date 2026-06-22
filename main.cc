#include "Color.h"
#include "Ray.h"
#include <cmath>
#include <iostream>

using namespace color;

Color RayColor(const Ray &r) {
    Vec3 unitDir = Normalize(r.dir());                                  // y -> [-1, 1]
    real_t w = 0.5 * (unitDir.y() + 1.0);                               // w -> [0, 1]
    return (1.0 - w) * Color(1.0, 1.0, 1.0) + w * Color(0.5, 0.7, 1.0); // White ~ Skyblue
}

int main() {
    real_t aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;
    int imageHeight = std::max(1, int(imageWidth / aspectRatio));

    real_t focalLength = 1.0;
    real_t viewportHeight = 2.0;
    real_t viewportWidth = viewportHeight * (real_t(imageWidth) / imageHeight);
    Point3 cameraCenter = Point3(0, 0, 0);

    Vec3 viewportU = Vec3(viewportWidth, 0, 0);
    Vec3 viewportV = Vec3(0, -viewportHeight, 0); // Flipped Y

    Vec3 pixelDeltaU = viewportU / imageWidth;
    Vec3 pixelDeltaV = viewportV / imageHeight;

    // -focalLength: Negative-Z-axis (Right-Handed Coordinates)
    Point3 viewportUpperLeft =
        cameraCenter - Vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;

    // The first pixel position
    Point3 pixel00 = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

    // Render
    std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++) {
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
        for (int i = 0; i < imageWidth; i++) {
            Point3 pixelCenter = pixel00 + (i * pixelDeltaU) + (j * pixelDeltaV);
            Vec3 rayDir = pixelCenter - cameraCenter;
            Ray ray(cameraCenter, rayDir);

            Color pixelColor = RayColor(ray);
            WriteColor(std::cout, pixelColor);
        }
    }

    std::clog << "\rDone.               \n";
}