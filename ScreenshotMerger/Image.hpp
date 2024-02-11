//
//  Image.hpp
//  ScreenshotMerger
//
//  Created by Andrei Muntean on 06/02/2024.
//

#ifndef Image_hpp
#define Image_hpp

#include <opencv2/core/hal/interface.h>
#include <opencv2/core/mat.hpp>
#include <stdint.h>
#include <vector>

/** A 24-bit RGB pixel. */
struct Pixel {
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;

    Pixel(uint8_t red, uint8_t green, uint8_t blue) : Red(red), Green(green), Blue(blue) {}

    // HACK: Fuzzy equality!
    // Should otherwise be `bool operator==(const Pixel& other) const = default;`.
    bool operator==(const Pixel& other) const {
        return abs(Red - other.Red) <= 55  // This value was chosen empirically.
            && abs(Green - other.Green) <= 55
            && abs(Blue - other.Blue) <= 55;
    };
};

/** A two-dimensional 24-bit image. */
class Image {
public:
    uint16_t Width() const { return pixels[0].size(); }
    uint16_t Height() const { return pixels.size(); }
    uint64_t PixelCount() const { return Width() * Height(); }

    Image(uint16_t width, uint16_t height);
    Image(std::vector<std::vector<Pixel>>);
    Image(const cv::Mat&);

    cv::Mat ToMat();
    Image Crop(uint16_t startRow, uint16_t height) const;

    Image operator+(const Image&) const;
    std::vector<Pixel> operator[](uint16_t rowIndex) const { return pixels[rowIndex]; }
    std::vector<Pixel>& operator[](uint16_t rowIndex) { return pixels[rowIndex]; }

private:
    std::vector<std::vector<Pixel>> pixels;
};

#endif /* Image_hpp */
