#pragma once

#include "Ray.h"

struct HitRecord {
    Point3 p;
    Vec3 normal;
    real_t t;
};

class Hittable {
  public:
    virtual ~Hittable() = default;
    virtual bool Hit(const Ray &ray, real_t tmin, real_t tmax, HitRecord &rec) const = 0;
};