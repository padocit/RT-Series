#pragma once

#include <limits>
#include <type_traits>

// Precision
using real_t = double;

// Constants
const real_t kInfinity = std::numeric_limits<real_t>::infinity();
const real_t kPi = real_t(3.1415926535897932385);
const real_t kNormalizationEpsilon = std::is_same_v<real_t, float> ? 1e-20 : 1e-160;

// Random functions
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