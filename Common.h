#pragma once

// Follow IWYU !
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

// Precision
using real_t = float;

// C++ Std Usings
using std::make_shared;
using std::shared_ptr;

// Constants
const real_t kInfinity = std::numeric_limits<real_t>::infinity();
const real_t kPi = real_t(3.1415926535897932385);

// Utility Functions
inline real_t DegreesToRadians(real_t degrees) { return degrees * kPi / 180.0; }

// Common Headers
#include "Color.h"
#include "Ray.h"
#include "Vec3.h"