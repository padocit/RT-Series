#pragma once

#include "Precision.h"

class Interval {
  public:
    static const Interval empty, universe;

    Interval() : min_(+kInfinity), max_(-kInfinity) {} // Default = empty
    Interval(real_t min, real_t max) : min_(min), max_(max) {}
    Interval(const Interval &a, const Interval &b) {
        // Union
        min_ = a.min_ <= b.min_ ? a.min_ : b.min_;
        max_ = a.max_ >= b.max_ ? a.max_ : b.max_;
    }

    real_t min() const { return min_; }
    real_t max() const { return max_; }
    void min(real_t min) { min_ = min; }
    void max(real_t max) { max_ = max; }

    real_t Size() const { return max_ - min_; }

    bool Contains(real_t x) const { return min_ <= x && x <= max_; }
    bool Surrounds(real_t x) const { return min_ < x && x < max_; }

    real_t Clamp(real_t x) const {
        if (x < min_) return min_;
        if (x > max_) return max_;
        return x;
    }

    Interval Expand(real_t delta) const {
        real_t padding = delta / 2;
        return Interval(min_ - padding, max_ + padding);
    }

  private:
    real_t min_, max_;
};

const Interval Interval::empty = Interval(+kInfinity, -kInfinity);
const Interval Interval::universe = Interval(-kInfinity, +kInfinity);