#pragma once

#include "Color.h"
#include "Hittable.h"

class Camera {
  public:
    Camera() {}

    real_t aspectRatio() const { return aspectRatio_; }
    int imageWidth() const { return imageWidth_; }

    void aspectRatio(real_t ratio) { aspectRatio_ = ratio; }
    void imageWidth(int width) { imageWidth_ = width; }

    void Render(const Hittable &world) {
        // Init
        Initialize();

        // Render
        std::cout << "P3\n" << imageWidth_ << " " << imageHeight_ << "\n255\n";

        for (int j = 0; j < imageHeight_; j++) {
            std::clog << "\rScanlines remaining: " << (imageHeight_ - j) << ' ' << std::flush;
            for (int i = 0; i < imageWidth_; i++) {
                Point3 pixelCenter = pixel00_ + (i * pixelDeltaU_) + (j * pixelDeltaV_);
                Vec3 rayDir = pixelCenter - cameraCenter_;
                Ray ray(cameraCenter_, rayDir);

                // Shading
                Color pixelColor = RayColor(ray, world);
                WriteColor(std::cout, pixelColor);
            }
        }

        std::clog << "\rDone.               \n";
    }

  private:
    real_t aspectRatio_ = 1.0;
    int imageWidth_ = 100;
    int imageHeight_ = 100;

    real_t focalLength_ = 1.0;
    Point3 cameraCenter_ = Point3(0, 0, 0);

    Vec3 pixelDeltaU_;
    Vec3 pixelDeltaV_;
    Point3 pixel00_;

    void Initialize() {
        // Image
        aspectRatio_ = 16.0 / 9.0;
        imageWidth_ = 400;
        imageHeight_ = std::max(1, int(imageWidth_ / aspectRatio_));

        // Camera
        focalLength_ = 1.0;
        cameraCenter_ = Point3(0, 0, 0);

        // Viewport
        real_t viewportHeight = 2.0;
        real_t viewportWidth = viewportHeight * (real_t(imageWidth_) / imageHeight_);

        Vec3 viewportU = Vec3(viewportWidth, 0, 0);
        Vec3 viewportV = Vec3(0, -viewportHeight, 0); // Flipped Y

        pixelDeltaU_ = viewportU / imageWidth_;
        pixelDeltaV_ = viewportV / imageHeight_;

        // -focalLength: Negative-Z-axis (Right-Handed Coordinates)
        Point3 viewportUpperLeft =
            cameraCenter_ - Vec3(0, 0, focalLength_) - viewportU / 2 - viewportV / 2;

        // The first pixel position
        pixel00_ = viewportUpperLeft + 0.5 * (pixelDeltaU_ + pixelDeltaV_);
    }

    Color RayColor(const Ray &ray, const Hittable &world) const {
        HitRecord rec;

        if (world.Hit(ray, Interval(0, kInfinity), rec)) {
            return 0.5 * (rec.normal + Color(1, 1, 1));
        }

        // Sky background (It's not a layer, Just fill-in)
        Vec3 unitRayDir = Normalize(ray.dir());
        real_t w = 0.5 * (unitRayDir.y() + 1.0);                            // [-1, 1] -> [0, 1]
        return (1.0 - w) * Color(1.0, 1.0, 1.0) + w * Color(0.5, 0.7, 1.0); // White ~ Skyblue
    }
};