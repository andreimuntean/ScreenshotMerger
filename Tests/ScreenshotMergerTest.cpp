//
//  ScreenshotMergerTest.cpp
//  ScreenshotMerger
//
//  Created by Andrei Muntean on 06/02/2024.
//

#include <gtest/gtest.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>

#include "Generators.hpp"
#include "Image.hpp"
#include "ScreenshotMerger.hpp"


static const Pixel red(255, 0, 0);
static const Pixel green(0, 255, 0);
static const Pixel cyan(0, 255, 255);
static const Pixel blue(0, 0, 255);


TEST(ScreenshotMerger, MergesImages) {
    Image firstImage = Generators::CreateImage(100, 300, red, cyan, blue);
    Image secondImage = Generators::CreateImage(100, 300, blue, red, green);

    Image result = ScreenshotMerger::Merge(firstImage, secondImage);

    EXPECT_EQ(result.Width(), 100);
    EXPECT_EQ(result.Height(), 500);
    EXPECT_EQ(result.PixelCount(), 100 * 500);
}


TEST(Pixel, SupportsEquality) {
    Pixel pixel = Pixel(100, 120, 250);
    Pixel samePixel = Pixel(100, 120, 250);
    Pixel differentPixel = Pixel(255, 100, 250);

    EXPECT_EQ(pixel, samePixel);
    EXPECT_NE(pixel, differentPixel);
}


TEST(Pixel, SupportsFuzzyEquality) {
    Pixel pixel = Pixel(100, 120, 250);
    Pixel similarPixel = Pixel(110, 115, 255);
    Pixel differentPixel = Pixel(40, 120, 250);

    EXPECT_EQ(pixel, similarPixel);
    EXPECT_NE(pixel, differentPixel);
}


int main(int argc, const char * argv[]) {
    testing::InitGoogleTest(&argc, (char**)argv);
    return RUN_ALL_TESTS();
}
