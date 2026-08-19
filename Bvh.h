#pragma once

#include "Aabb.h"
#include "Hittable.h"
#include "HittableList.h"

#include <algorithm>
#include <memory>
#include <vector>

// One class tree design (Node + Tree)
class Bvh : public Hittable {
  public:
    // Implicit copy of the hittable list <- Bvh is using smart pointers, fine.
    Bvh(HittableList list) : Bvh(list.objects(), 0, list.objects().size()) {}

    Bvh(std::vector<std::shared_ptr<Hittable>> &objects, size_t start, size_t end) {
        int axis = RandomInt(0, 2);

        auto comparator = (axis == 0) ? BoxCompareX : (axis == 1) ? BoxCompareY : BoxCompareZ;

        size_t objectSpan = end - start;

        if (objectSpan == 1) {
            left_ = right_ = objects[start];
        } else if (objectSpan == 2) {
            left_ = objects[start];
            right_ = objects[start + 1];
        } else {
            std::sort(std::begin(objects) + start, std::begin(objects) + end, comparator);

            size_t mid = start + objectSpan / 2;
            left_ = std::make_shared<Bvh>(objects, start, mid);
            right_ = std::make_shared<Bvh>(objects, mid, end);
        }

        bbox_ = Aabb(left_->bbox(), right_->bbox());
    }

    Aabb bbox() const override { return bbox_; }

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

    // Generic comparators
    static bool BoxCompare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b,
                           int axisIndex) {
        Interval aAxisInterval = a->bbox().AxisInterval(axisIndex);
        Interval bAxisInterval = b->bbox().AxisInterval(axisIndex);
        return aAxisInterval.min() < bAxisInterval.min();
    }

    static bool BoxCompareX(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
        return BoxCompare(a, b, 0);
    }
    static bool BoxCompareY(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
        return BoxCompare(a, b, 1);
    }
    static bool BoxCompareZ(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
        return BoxCompare(a, b, 2);
    }
};