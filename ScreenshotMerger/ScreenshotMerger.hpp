//
//  ScreenshotMerger.hpp
//  ScreenshotMerger
//
//  Created by Andrei Muntean on 22/01/2024.
//

#ifndef ScreenshotMerger_hpp
#define ScreenshotMerger_hpp

#include "Image.hpp"

/** Merges images. */
class ScreenshotMerger {
public:
    /**
     * Vertically merges two images that have the same width.
     * The end of the first image must match the beggining of the second image.
     * Intended for mobile screenshots.
     */
    static Image Merge(const Image&, const Image&);

    ScreenshotMerger() = delete;

private:
    /** Finds the end of the first image that matches the beginning of the second image. */
    static Image findSharedChunk(const Image&, const Image&);
};

#endif /* ScreenshotMerger_hpp */
