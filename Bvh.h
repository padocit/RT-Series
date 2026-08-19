#pragma once

#include "Aabb.h"
#include "Hittable.h"
#include "HittableList.h"

#include <memory>
#include <vector>

// One class tree design (Node + Tree)
class Bvh : public Hittable {
  public:
    // TODO: Copy constructor
    Bvh(HittableList list) : Bvh(list.objects(), 0, list.objects().size()) {}

    Bvh(std::vector<std::shared_ptr<Hittable>> &objects, size_t start, size_t end) {
        // TODO
    }

    bool Hit(const Ray &ray, Interval rayT, HitRecord &rec) const override {
        if (!bbox_.Hit(ray, rayT)) return false;

        bool hitLeft = left_->Hit(ray, rayT, rec);
        bool hitRight = right_->Hit(ray, Interval(rayT.min(), hitLeft ? rec.t : rayT.max()), rec);

        return hitLeft || hitRight; // rec = closest hit
    }

  private:
    std::shared_ptr<Hittable> left_;
    std::shared_ptr<Hittable> right_;
    Aabb bbox_;
};