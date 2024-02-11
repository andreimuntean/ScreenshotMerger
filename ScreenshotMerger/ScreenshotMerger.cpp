//
//  ScreenshotMerger.cpp
//  ScreenshotMerger
//
//  Created by Andrei Muntean on 22/01/2024.
//

#include <iostream>

#include "ScreenshotMerger.hpp"


Image ScreenshotMerger::Merge(const Image& firstImage,
                              const Image& secondImage) {
    assert(firstImage.Width() == secondImage.Width());

    const Image& sharedChunk = findSharedChunk(firstImage, secondImage);

    return firstImage + secondImage.Crop(sharedChunk.Height(),
                                         secondImage.Height() - sharedChunk.Height());
}


Image ScreenshotMerger::findSharedChunk(const Image& firstImage,
                                        const Image& secondImage) {
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

    std::cerr << "WARNING: Couldn't merge two images.\n";
    return Image(std::vector<std::vector<Pixel>>());
}
