#include "Color.h"
#include "Ray.h"
#include <iostream>

using namespace color;

// TODO: Distinguish sphere behind the camera
real_t HitSphere(const Point3 &center, double radius, const Ray &ray) {
    Vec3 oc = center - ray.orig();
    real_t a = ray.dir().LengthSquared();
    real_t h = Dot(ray.dir(), oc); // b = -2h
    real_t c = oc.LengthSquared() - radius * radius;
    real_t discriminant = h * h - a * c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (h - std::sqrt(discriminant)) / a;
    }
}

Color RayColor(const Ray &ray) {
    // sphere
    Point3 sphereCenter(0, 0, -1);
    real_t t = HitSphere(sphereCenter, 0.5, ray);
    if (t > 0.0) {
        Vec3 Normal = Normalize(ray.At(t) - sphereCenter);
        return 0.5 * Color(Normal.x() + 1, Normal.y() + 1, Normal.z() + 1); // [-1, 1] -> [0, 1]
    }

    // background
    Vec3 unitDir = Normalize(ray.dir());                                // y -> [-1, 1]
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