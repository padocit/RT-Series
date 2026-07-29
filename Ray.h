#pragma once

#include "Vec3.h"

class Ray {
  public:
    Ray() {}
    Ray(const Point3 &orig, const Vec3 &dir, real_t time) : orig_(orig), dir_(dir), time_(time) {}
    Ray(const Point3 &orig, const Vec3 &dir) : Ray(orig, dir, 0) {}

    const Point3 &orig() const { return orig_; }
    const Vec3 &dir() const { return dir_; }
    real_t time() const { return time_; }

    Point3 At(real_t t) const { return orig_ + t * dir_; }

  private:
    Point3 orig_;
    Vec3 dir_;
    real_t time_;
};