#pragma once

#include "Hittable.h"
#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class HittableList : public Hittable {
  public:
    HittableList() {}
    HittableList(shared_ptr<Hittable> object) { Add(object); }

    void Clear() { objects_.clear(); }

    void Add(shared_ptr<Hittable> object) { objects_.push_back(object); }

    // Hit() returns &rec
    bool Hit(const Ray &ray, real_t tMin, real_t tMax, HitRecord &rec) const override {
        HitRecord tempRec;
        bool hitAnything = false;
        real_t tClosest = tMax;

        for (const auto &object : objects_) {
            if (object->Hit(ray, tMin, tClosest, tempRec)) { // only t < tClosest
                hitAnything = true;
                tClosest = tempRec.t;
                rec = tempRec;
            }
        }

        return hitAnything;
    }

  private:
    std::vector<shared_ptr<Hittable>> objects_;
};