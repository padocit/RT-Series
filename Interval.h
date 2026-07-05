#pragma once

#include "Precision.h"

class Interval {
  public:
    static const Interval kEmpty, kUniverse;

    Interval() : min_(+kInfinity), max_(-kInfinity) {} // Default = empty
    Interval(real_t min, real_t max) : min_(min), max_(max) {}

    real_t min() const { return min_; }
    real_t max() const { return max_; }

    real_t Size() const { return max_ - min_; }

    bool Contains(real_t x) const { return min_ <= x && x <= max_; }
    bool Surrounds(real_t x) const { return min_ < x && x < max_; }

    real_t Clamp(real_t x) const {
        if (x < min_) return min_;
        if (x > max_) return max_;
        return x;
    }

  private:
    real_t min_, max_;
};

const Interval Interval::kEmpty = Interval(+kInfinity, -kInfinity);
const Interval Interval::kUniverse = Interval(-kInfinity, +kInfinity);