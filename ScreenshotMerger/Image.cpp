//
//  Image.cpp
//  ScreenshotMerger
//
//  Created by Andrei Muntean on 06/02/2024.
//

#include "Image.hpp"


Image::Image(uint16_t width, uint16_t height) {
    pixels.reserve(height);
    while (height-- > 0) {
        auto row = std::vector<Pixel>();
        row.reserve(width);

        for (uint16_t x = 0; x < width; ++x) {
            row.push_back(Pixel(0, 0, 0));
        }

        pixels.push_back(row);
    }
}


Image::Image(std::vector<std::vector<Pixel>> pixels) : pixels(pixels) {}


Image::Image(const cv::Mat& mat) {
    assert(mat.type() == CV_8UC3); // Only reasonable mats are accepted (8-bit unsigned, 3 channels)!

    pixels.reserve(mat.rows);

    for (uint16_t y = 0; y < mat.rows; ++y) {
        auto row = std::vector<Pixel>();
        row.reserve(mat.cols);

        for (uint16_t x = 0; x < mat.cols; ++x) {
            uint64_t i = 3 * (y * mat.cols + x);
            uint8_t blue = mat.data[i];
            uint8_t green = mat.data[i + 1];
            uint8_t red = mat.data[i + 2];
            row.push_back(Pixel(red, green, blue));
        }

        pixels.push_back(row);
    }
}


cv::Mat Image::ToMat() {
    uint8_t* data = new uint8_t[Height() * Width() * 3];

    for (uint16_t y = 0; y < Height(); ++y) {
        for (uint16_t x = 0; x < Width(); ++x) {
            const Pixel& pixel = pixels[y][x];
            uint64_t i = 3 * (y * Width() + x);

            data[i] = pixel.Blue;
            data[i + 1] = pixel.Green;
            data[i + 2] = pixel.Red;
        }
    }

    return cv::Mat(Height(), Width(), CV_8UC3, data);
}


Image Image::Crop(uint16_t startRow, uint16_t newHeight) const {
    return Image(std::vector<std::vector<Pixel>>(pixels.begin() + startRow,
                                                 pixels.begin() + startRow + newHeight));
}
