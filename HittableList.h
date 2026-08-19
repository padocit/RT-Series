#pragma once

#include "Aabb.h"
#include "Hittable.h"
#include "Interval.h"

#include <memory>
#include <vector>

class HittableList : public Hittable {
  public:
    HittableList() {}
    HittableList(std::shared_ptr<Hittable> object) { Add(object); }

    Aabb bbox() const override { return bbox_; }
    std::vector<std::shared_ptr<Hittable>> &objects() { return objects_; }
    const std::vector<std::shared_ptr<Hittable>> &objects() const { return objects_; }

    void Clear() { objects_.clear(); }

    void Add(std::shared_ptr<Hittable> object) {
        objects_.push_back(object);
        bbox_ = Aabb(bbox_, object->bbox());
    }

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
    Aabb bbox_; // Bounding box
};