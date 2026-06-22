#pragma once

#include "Vec3.h"

class Ray {
  public:
    Ray() {}
    Ray(const Point3 &orig, const Vec3 &dir) : orig_(orig), dir_(dir) {}

    const Point3 &orig() const { return orig_; }
    const Vec3 &dir() const { return dir_; }

    Point3 At(real_t t) const { return orig_ + t * dir_; }

  private:
    Point3 orig_;
    Vec3 dir_;
};