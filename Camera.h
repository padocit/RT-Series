#pragma once

#include "Color.h"
#include "Hittable.h"
#include "Material.h"
#include "Precision.h"

class Camera {
  public:
    Camera() {}

    real_t aspectRatio() const { return aspectRatio_; }
    int imageWidth() const { return imageWidth_; }
    int samplesPerPixel() const { return samplesPerPixel_; }
    int maxDepth() const { return maxDepth_; } // Initial depth

    void aspectRatio(real_t ratio) { aspectRatio_ = ratio; }
    void imageWidth(int width) { imageWidth_ = width; }
    void samplesPerPixel(int sample) { samplesPerPixel_ = sample; }
    void maxDepth(int depth) { maxDepth_ = depth; }

    void Render(const Hittable &world) {
        // Init
        Initialize();

        // Render
        std::cout << "P3\n" << imageWidth_ << " " << imageHeight_ << "\n255\n";

        for (int j = 0; j < imageHeight_; j++) {
            std::clog << "\rScanlines remaining: " << (imageHeight_ - j) << ' ' << std::flush;
            for (int i = 0; i < imageWidth_; i++) {
                Color pixelColor(0, 0, 0);
                // Multi-Sampling
                for (int sample = 0; sample < samplesPerPixel_; sample++) {
                    Ray ray = GetRay(i, j);
                    pixelColor += RayColor(ray, maxDepth_, world);
                }
                WriteColor(std::cout, pixelSamplesScale_ * pixelColor);
            }
        }

        std::clog << "\rDone.               \n";
    }

  private:
    real_t aspectRatio_ = 1.0;
    int imageWidth_ = 100;

    int samplesPerPixel_ = 10;
    int maxDepth_ = 10;

    int imageHeight_ = 100;

    real_t focalLength_ = 1.0;
    Point3 cameraCenter_ = Point3(0, 0, 0);

    real_t pixelSamplesScale_; // Color scale factor

    Vec3 pixelDeltaU_;
    Vec3 pixelDeltaV_;
    Point3 pixel00_;

    void Initialize() {
        // Image
        aspectRatio_ = 16.0 / 9.0;
        imageWidth_ = 400;
        imageHeight_ = std::max(1, int(imageWidth_ / aspectRatio_));

        pixelSamplesScale_ = 1.0 / samplesPerPixel_;

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

    Ray GetRay(int i, int j) const {
        Vec3 offset = SampleSquare();
        Point3 pixelSample =
            pixel00_ + ((i + offset.x()) * pixelDeltaU_) + ((j + offset.y()) * pixelDeltaV_);

        Point3 rayOrig = cameraCenter_;
        Vec3 rayDir = pixelSample - rayOrig;

        return Ray(rayOrig, rayDir);
    }

    Vec3 SampleSquare() const {
        // [0,1) -> [-0.5,+0.5)
        return Vec3(RandomReal() - 0.5, RandomReal() - 0.5, 0);
    }

    Color RayColor(const Ray &ray, int depth, const Hittable &world) const {
        if (depth <= 0) return Color(0, 0, 0); // The limit of Raycolor recursion

        HitRecord rec;

        if (world.Hit(ray, Interval(0.001, kInfinity), rec)) { // 0.001 to prevent Shadow-acne
            Ray scattered;
            Color attenuation;
            if (rec.mat->Scatter(ray, rec, attenuation, scattered))
                return attenuation * RayColor(scattered, depth - 1, world); // Recursion

            return Color(0, 0, 0);
        }

        // Sky background (It's not a layer, Just fill-in)
        Vec3 unitRayDir = Normalize(ray.dir());
        real_t w = 0.5 * (unitRayDir.y() + 1.0);                            // [-1, 1] -> [0, 1]
        return (1.0 - w) * Color(1.0, 1.0, 1.0) + w * Color(0.5, 0.7, 1.0); // White ~ Skyblue
    }
};