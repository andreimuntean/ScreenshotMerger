//
//  main.cpp
//  ScreenshotMerger
//
//  Created by Andrei Muntean on 21/01/2024.
//

#include <chrono>
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>

#include "ScreenshotMerger.hpp"

int main(int argc, const char * argv[]) {
    using namespace std::literals;

    if (argc <= 2) {
        std::cerr << "Please provide at least two images as input and specify an output path, for example:\n";
        std::cerr << "  ScreenshotMerger C:/Images/First.png C:/Images/Second.png C:/Images/Output.png\n";
        return 0;
    }

    Image result(cv::imread(argv[1], cv::IMREAD_COLOR));
    std::cout << "Merging " << result.Width() << 'x' << result.Height() << '\n';
    std::chrono::duration<double> timeElapsedMerging = 0s;

    for (int i = 2; i < argc - 1; ++i) {
        Image image = Image(cv::imread(argv[i], cv::IMREAD_COLOR));
        std::cout << "      + " << image.Width() << 'x' << image.Height() << "...";

        auto startTime = std::chrono::high_resolution_clock::now();
        result = ScreenshotMerger::Merge(result, image);
        auto timeElapsed = std::chrono::high_resolution_clock::now() - startTime;
        timeElapsedMerging += timeElapsed;
        std::cout << " Done (took " << timeElapsed / 1ms << " milliseconds)\n";
    }

    std::cout << "Result is a " << result.Width() << 'x' << result.Height()
              << " image (took " << timeElapsedMerging / 1ms << " milliseconds).\n";
    cv::imwrite(argv[argc - 1], result.ToMat());

    return 0;
}
