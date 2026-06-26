#pragma once

#include "Hittable.h"
#include "Interval.h"

#include <memory>
#include <vector>

class HittableList : public Hittable {
  public:
    HittableList() {}
    HittableList(std::shared_ptr<Hittable> object) { Add(object); }

    void Clear() { objects_.clear(); }

    void Add(std::shared_ptr<Hittable> object) { objects_.push_back(object); }

    // Hit() returns &rec
    bool Hit(const Ray &ray, Interval rayT, HitRecord &rec) const override {
        HitRecord tempRec;
        bool hitAnything = false;
        real_t tClosest = rayT.max();

        for (const auto &object : objects_) {
            if (object->Hit(ray, Interval(rayT.min(), tClosest), tempRec)) { // only t < tClosest
                hitAnything = true;
                tClosest = tempRec.t;
                rec = tempRec;
            }
        }

        return hitAnything;
    }

  private:
    std::vector<std::shared_ptr<Hittable>> objects_;
};