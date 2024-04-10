# Screenshot Merger

Vertically merges two or more images that have the same width. Intended for mobile screenshots.

## Compilation Guide

### Required Libraries

A `Libraries` directory must be created in `ScreenshotMerger` after pulling the repository.

A `Libraries/include/opencv4` directory must be created and the following libraries must be copied into it:
  - `opencv2/core`
  - `opencv2/core.hpp`
  - `opencv2/imgcodecs`
  - `opencv2/imgcodecs.hpp`
  - `opencv2/imgproc`
  - `opencv2/imgproc.hpp`

_(opencv2 is an external library that comes with those and many other libraries)_

A `Libraries/lib` directory must be created and the following libraries must be copied into it:
  - `libopencv_core.a`
  - `libopencv_core.dylib`
  - `libopencv_imgcodecs.a`
  - `libopencv_imgcodecs.dylib`
  - `libopencv_imgproc.a`
  - `libopencv_imgproc.dylib`

In addition, the following commands must be applied on those dylibs:
  - `install_name_tool -id "@rpath/libopencv_core.409.dylib" lib/libopencv_core.409.dylib`
  - `install_name_tool -id "@rpath/libopencv_imgcodecs.409.dylib" lib/libopencv_imgcodecs.409.dylib`
  - `install_name_tool -id "@rpath/libopencv_imgproc.409.dylib" lib/libopencv_imgproc.409.dylib`

Confirm that `@rpath/libopencv_core.409.dylib` is printed when running `otool -L lib/libopencv_core.409.dylib`.
Likewise with the other dylibs.

_(your libraries might have a newer version than 409)_

### Build Flags

Other linker flags must include `-lopencv_core -lopencv_imgcodecs -lopencv_imgproc`.

Runpath search paths must include `@executable_path/lib`.

Header search paths must include `Libraries/include/opencv4`.

Library search paths must include `Libraries/lib`.

### Running the Program

An `Executable` directory should be created in ScreenshotMerger after pulling the repository.

ScreenshotMerger should be compiled into that directory and an `Executable/lib` directory should exist alongside it.

To run the compiled program, a `lib` directory must exist in the same directory as the program and it must contain:
  - `libopencv_core.dylib`
  - `libopencv_imgcodecs.dylib`
  - `libopencv_imgproc.dylib`

_(these are the same dylibs that were enhanced with `install_name_tool` in the previous section)_
