#pragma once

#include "Color.h"
#include "Hittable.h"

class Material {
  public:
    virtual ~Material() = default;

    virtual bool Scatter(const Ray &inRay, const HitRecord &rec, Color &attenuation,
                         Ray &scatteredRay) const {
        return false;
    }
};

// Always scatter and attenuate light according to its reflectance R
class Lambertian : public Material {
  public:
    Lambertian(const Color &albedo) : albedo_(albedo) {}

    bool Scatter(const Ray &inRay, const HitRecord &rec, Color &attenuation,
                 Ray &scatteredRay) const override {
        Vec3 scatterDirection = rec.normal + RandomUnitVector();

        // Catch degenerate(zero) scatter direction (Prevent inf and NaNs)
        if (scatterDirection.NearZero()) scatterDirection = rec.normal;

        scatteredRay = Ray(rec.p, scatterDirection);
        attenuation = albedo_; // albedo/P (if using the fixed scatter probability P)
        return true;
    }

  private:
    Color albedo_;
};