#pragma once

#include "Ray.h"

struct HitRecord {
    Point3 p;
    Vec3 normal;
    real_t t;
    bool frontFace;

    void SetFaceNormal(const Ray &ray, const Vec3 &outwardNormal) {
        frontFace = Dot(ray.dir(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable {
  public:
    virtual ~Hittable() = default;
    virtual bool Hit(const Ray &ray, real_t tMin, real_t tMax, HitRecord &rec) const = 0;
};