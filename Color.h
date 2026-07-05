#pragma once

#include "Interval.h"
#include "Vec3.h"
#include <iostream>

using Color = Vec3;

void WriteColor(std::ostream &out, const Color &pixel) {
    auto r = pixel.x();
    auto g = pixel.y();
    auto b = pixel.z();

    // [0,1] -> [0,255]
    static const Interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.Clamp(r));
    int gbyte = int(256 * intensity.Clamp(g));
    int bbyte = int(256 * intensity.Clamp(b));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
