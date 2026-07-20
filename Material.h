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
        Vec3 scatterDir = rec.normal + RandomUnitVector();

        // Catch degenerate(zero) scatter direction (Prevent inf and NaNs)
        if (scatterDir.NearZero()) scatterDir = rec.normal;

        scatteredRay = Ray(rec.p, scatterDir);
        attenuation = albedo_; // albedo/P (if using the fixed scatter probability P)
        return true;
    }

  private:
    Color albedo_;
};

class Metal : public Material {
  public:
    Metal(const Color &albedo, real_t fuzz) : albedo_(albedo), fuzz_(fuzz) {}

    bool Scatter(const Ray &inRay, const HitRecord &rec, Color &attenuation,
                 Ray &scatteredRay) const override {
        Vec3 reflectedDir = Reflect(inRay.dir(), rec.normal);
        reflectedDir = Normalize(reflectedDir) + (fuzz_ * RandomUnitVector()); // fuzz
        scatteredRay = Ray(rec.p, reflectedDir);
        attenuation = albedo_;
        return true;
    }

  private:
    Color albedo_;
    real_t fuzz_;
};

class Dielectric : public Material {
  public:
    Dielectric(real_t refractionIndex) : refractionIndex_(refractionIndex) {}

    bool Scatter(const Ray &inRay, const HitRecord &rec, Color &attenuation,
                 Ray &scatteredRay) const override {
        attenuation = Color(1.0, 1.0, 1.0);
        real_t ri = rec.frontFace ? (1.0 / refractionIndex_) : refractionIndex_; // In? or Out?

        Vec3 unitDir = Normalize(inRay.dir());
        real_t cosTheta = std::fmin(Dot(-unitDir, rec.normal), real_t(1.0));
        real_t sinTheta = std::sqrt(real_t(1.0) - cosTheta * cosTheta);

        bool cannotRefract = ri * sinTheta > 1.0;
        Vec3 direction;
        if (cannotRefract || Reflectance(cosTheta, ri) > RandomReal()) // Total internal reflection
            direction = Reflect(unitDir, rec.normal);
        else
            direction = Refract(unitDir, rec.normal, ri);

        scatteredRay = Ray(rec.p, direction);
        return true;
    }

  private:
    real_t refractionIndex_; // The ratio of this mat's refractive index
                             // over the refracitve index of the enclosing media

    static real_t Reflectance(real_t cosine, real_t refractionIndex) {
        // Schlick's approximation for reflectance (Fresnel)
        auto r0 = (1 - refractionIndex) / (1 + refractionIndex);
        r0 = r0 * r0;
        return r0 + (1 - r0) * std::pow((1 - cosine), 5);
    }
};