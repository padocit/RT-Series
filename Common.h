#pragma once

// But still should follow IWYU in other headers!
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

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