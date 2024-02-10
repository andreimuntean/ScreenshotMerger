//
//  Generators.hpp
//  ScreenshotMerger
//
//  Created by Andrei Muntean on 06/02/2024.
//

#ifndef Generators_hpp
#define Generators_hpp

#include <stdio.h>
#include <vector>

#include "Image.hpp"

/** Class used for testing. */
class Generators {
public:
    static Image CreateImage(uint16_t width, uint16_t height, Pixel pixel);

    static Image CreateImage(uint16_t width, uint16_t height, Pixel firstThird, Pixel secondThird, Pixel lastThird);

    Generators() = delete;
};

#endif /* Generators_hpp */
