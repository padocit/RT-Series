#pragma once

#include "Color.h"

#include <memory>

class Texture {
  public:
    virtual ~Texture() = default;
    virtual Color Value(real_t u, real_t v, const Point3 &p) const = 0;
};

class SolidColor : public Texture {
  public:
    SolidColor(const Color &albedo) : albedo_(albedo) {}
    SolidColor(real_t r, real_t g, real_t b) : SolidColor(Color(r, g, b)) {}
    Color Value(real_t u, real_t v, const Point3 &p) const override { return albedo_; }

  private:
    Color albedo_;
};

class CheckerTexture : public Texture {
  public:
    CheckerTexture(real_t scale, std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd)
        : invScale(1.0 / scale), even_(even), odd_(odd) {}

    CheckerTexture(real_t scale, const Color &c1, const Color &c2)
        : CheckerTexture(scale, std::make_shared<SolidColor>(c1),
                         std::make_shared<SolidColor>(c2)) {}

    Color Value(real_t u, real_t v, const Point3 &p) const override {
        int xInt = static_cast<int>(std::floor(invScale * p.x()));
        int yInt = static_cast<int>(std::floor(invScale * p.y()));
        int zInt = static_cast<int>(std::floor(invScale * p.z()));

        bool isEven = (xInt + yInt + zInt) % 2 == 0;

        return isEven ? even_->Value(u, v, p) : odd_->Value(u, v, p);
    }

  private:
    real_t invScale;
    std::shared_ptr<Texture> even_;
    std::shared_ptr<Texture> odd_;
};