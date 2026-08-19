#pragma once

#include "Aabb.h"
#include "Hittable.h"
#include "Interval.h"
#include "Vec3.h"

class Material;

class Sphere : public Hittable {
  public:
    // Stationary Sphere
    Sphere(const Point3 &center, real_t radius, shared_ptr<Material> mat)
        : center_(center, Vec3(0, 0, 0)), radius_(std::fmax(0, radius)), mat_(mat) {
        Vec3 rvec = Vec3(radius_, radius_, radius_);
        bbox_ = Aabb(center - rvec, center + rvec);
    }

    // Moving Sphere
    Sphere(const Point3 &center1, const Point3 &center2, real_t radius, shared_ptr<Material> mat)
        : center_(center1, center2 - center1), radius_(std::fmax(0, radius)), mat_(mat) {
        Vec3 rvec = Vec3(radius_, radius_, radius_);
        Aabb box1(center_.At(0) - rvec, center_.At(0) + rvec);
        Aabb box2(center_.At(1) - rvec, center_.At(1) + rvec);
        bbox_ = Aabb(box1, box2);
    }

    Aabb bbox() const override { return bbox_; }

    bool Hit(const Ray &ray, Interval rayT, HitRecord &rec) const override {
        Point3 currCenter = center_.At(ray.time());
        Vec3 oc = currCenter - ray.orig();
        real_t a = ray.dir().LengthSquared();
        real_t h = Dot(ray.dir(), oc); // b = -2h
        real_t c = oc.LengthSquared() - radius_ * radius_;

        real_t discriminant = h * h - a * c;
        if (discriminant < 0) return false;

        real_t sqrtD = std::sqrt(discriminant);

        // Nearest root in [t_min, t_max]
        real_t root = (h - sqrtD) / a;
        if (!rayT.Surrounds(root)) {
            root = (h + sqrtD) / a;
            if (!rayT.Surrounds(root)) return false;
        }

        // Hit Record
        rec.t = root;
        rec.p = ray.At(rec.t);
        Vec3 outwardNormal = (rec.p - currCenter) / radius_;
        rec.SetFaceNormal(ray, outwardNormal);
        rec.mat = mat_;

        return true;
    }

  private:
    Ray center_; // For animating spheres
    real_t radius_;
    shared_ptr<Material> mat_;
    Aabb bbox_;
};