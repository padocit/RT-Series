#include "Color.h"
#include <iostream>

int main() {
    int imageWidth = 256;
    int imageHeight = 256;

    std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++) {
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
        for (int i = 0; i < imageWidth; i++) {
            auto pixel =
                color::Color(real_t(i) / (imageWidth - 1), real_t(j) / (imageHeight - 1), 0);
            color::WriteColor(std::cout, pixel);
        }
    }

    std::clog << "\rDone.               \n";
}