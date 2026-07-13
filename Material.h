#pragma once

#include "Color.h"
#include "Hittable.h"

class Material {
  public:
    virtual ~Material() = default;

    virtual bool Scatter(const Ray &rayIn, const HitRecord &rec, Color &attenuation,
                         Ray &scattered) const {
        return false;
    }
};