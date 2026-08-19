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
    Bvh(HittableList list) : Bvh(list.Objects(), 0, list.Objects().size()) {}

    Bvh(std::vector<std::shared_ptr<Hittable>> &objects, size_t start, size_t end) {
        // TODO
    }

  private:
    std::shared_ptr<Hittable> left_;
    std::shared_ptr<Hittable> right_;
    Aabb bbox_;
};