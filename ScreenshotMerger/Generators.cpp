//
//  Generators.cpp
//  ScreenshotMerger
//
//  Created by Andrei Muntean on 06/02/2024.
//

#include "Generators.hpp"


Image Generators::CreateImage(uint16_t width, uint16_t height, Pixel pixel) {
    std::vector<std::vector<Pixel>> pixels;
    pixels.reserve(height);

    while (height-- > 0) {
        std::vector<Pixel> row;
        row.reserve(width);

        for (uint16_t x = 0; x < width; ++x) {
            row.push_back(pixel);
        }

        pixels.push_back(row);
    }

    return Image(pixels);
}


Image Generators::CreateImage(uint16_t width, uint16_t height,
                              Pixel firstThird, Pixel secondThird, Pixel lastThird) {
    std::vector<std::vector<Pixel>> pixels;
    pixels.reserve(height);

    for (uint16_t y = 0; y < height; ++y) {
        std::vector<Pixel> row;
        row.reserve(width);

        for (uint16_t x = 0; x < width; ++x) {
            row.push_back(y < height / 3 ? firstThird
                            : y < 2 * height / 3 ? secondThird
                                : lastThird );
        }

        pixels.push_back(row);
    }

    return Image(pixels);
}
