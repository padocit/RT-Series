#pragma once

#include "Vec3.h"
#include <iostream>

namespace color {

using Color = Vec3;

void WriteColor(std::ostream &out, const Color &pixel) {
    auto r = pixel.x();
    auto g = pixel.y();
    auto b = pixel.z();

    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
} // namespace color
