#pragma once

#include "Interval.h"
#include "Vec3.h"
#include <iostream>

using Color = Vec3;

inline real_t LinearToGamma(real_t linearComponent) {
    if (linearComponent > 0) return std::sqrt(linearComponent);

    return 0;
}

void WriteColor(std::ostream &out, const Color &pixel) {
    real_t r = pixel.x();
    real_t g = pixel.y();
    real_t b = pixel.z();

    // Linear to gamma (gamma 2)
    r = LinearToGamma(r);
    g = LinearToGamma(g);
    b = LinearToGamma(b);

    // [0,1] -> [0,255]
    static const Interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.Clamp(r));
    int gbyte = int(256 * intensity.Clamp(g));
    int bbyte = int(256 * intensity.Clamp(b));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
