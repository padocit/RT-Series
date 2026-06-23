#pragma once

#include "Hittable.h"
#include "Vec3.h"

class Sphere : public Hittable {
  public:
    Sphere(const Point3 &center, real_t radius) : center_(center), radius_(std::fmax(0, radius)) {}

    bool Hit(const Ray &ray, real_t tmin, real_t tmax, HitRecord &rec) const override {
        Vec3 oc = center_ - ray.orig();
        real_t a = ray.dir().LengthSquared();
        real_t h = Dot(ray.dir(), oc); // b = -2h
        real_t c = oc.LengthSquared() - radius_ * radius_;

        real_t discriminant = h * h - a * c;
        if (discriminant < 0)
            return false;

        real_t sqrtD = std::sqrt(discriminant);

        // Nearest root in [t_min, t_max]
        real_t root = (h - sqrtD) / a;
        if (root <= tmin || root >= tmax) {
            root = (h + sqrtD) / a;
            if (root <= tmin || root >= tmax)
                return false;
        }

        // Hit Record
        rec.t = root;
        rec.p = ray.At(rec.t);
        rec.normal = (rec.p - center_) / radius_;

        return true;
    }

  private:
    Point3 center_;
    real_t radius_;
};