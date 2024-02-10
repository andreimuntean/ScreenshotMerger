//
//  ScreenshotMerger.cpp
//  ScreenshotMerger
//
//  Created by Andrei Muntean on 22/01/2024.
//

#include "ScreenshotMerger.hpp"
#include <iostream>


Image ScreenshotMerger::Merge(const Image& firstImage,
                              const Image& secondImage) {
    assert(firstImage.Width() == secondImage.Width());
    
    Image sharedChunk = findSharedChunk(firstImage, secondImage);
    Image result(firstImage.Width(),
                 firstImage.Height() + secondImage.Height() - sharedChunk.Height());

    for (uint16_t y = 0; y < result.Height(); ++y) {
        for (uint16_t x = 0; x < result.Width(); ++x) {
            result[y][x] = y < firstImage.Height()
                                  ? firstImage[y][x]
                                  : secondImage[y - firstImage.Height() + sharedChunk.Height()][x];
        }
    }

    return result;
}


Image ScreenshotMerger::findSharedChunk(const Image& firstImage, const Image& secondImage) {
    assert(firstImage.Width() == secondImage.Width());

    for (uint16_t y = MAX(firstImage.Height() - secondImage.Height(), 0); y < firstImage.Height(); ++y) {
        uint16_t sharedChunkHeight = 0;

        while (firstImage[y + sharedChunkHeight] == secondImage[sharedChunkHeight]) {
            ++sharedChunkHeight;

            if (y + sharedChunkHeight == firstImage.Height()) {
                return secondImage.Crop(0, sharedChunkHeight);
            }
        }
    }

    std::cerr << "WARNING: Couldn't merge two images!\n";
    return Image(std::vector<std::vector<Pixel>>());
}
