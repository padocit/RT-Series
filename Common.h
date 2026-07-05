#pragma once

// But still should follow IWYU in other headers!
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

// Common Headers
#include "Color.h"
#include "Interval.h"
#include "Precision.h"
#include "Ray.h"
#include "Vec3.h"

// C++ Std Usings
using std::make_shared;
using std::shared_ptr;

// Utility Functions
inline real_t DegreesToRadians(real_t degrees) { return degrees * kPi / 180.0; }

inline real_t RandomReal() {
    // [0, 1)
    static std::uniform_real_distribution<real_t> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline real_t RandomReal(real_t min, real_t max) {
    // [min, max)
    return min + (max - min) * RandomReal();
}