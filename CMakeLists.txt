cmake_minimum_required(VERSION 3.10)

project(image_processor)
include_directories(src)
add_subdirectory(tests)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

add_executable(image_processor main.cpp
        main.cpp
        src/args/args.h
        src/args/args.cpp
        src/bmp/loader.h
        src/bmp/loader.cpp
        src/bmp/dumper.h
        src/bmp/dumper.cpp
        src/image/format.h
        src/image/color.h
        src/image/image.h
        src/image/image.cpp
        src/image/color.cpp
        src/filters/filter.h
        src/filters/registry.h
        src/filters/registry.cpp
        src/filters/crop.h
        src/filters/crop.cpp
        src/filters/grayscale.h
        src/filters/grayscale.cpp
        src/filters/neg.h
        src/filters/neg.cpp
        src/filters/matrix_filter.h
        src/filters/matrix_filter.cpp
        src/filters/sharpen.h
        src/filters/sharpen.cpp
        src/filters/edge.h
        src/filters/edge.cpp
        src/filters/blur.h
        src/filters/blur.cpp
        src/filters/blur.cpp
        src/filters/blur.cpp
        src/filters/affine_tile.cpp
        src/filters/affine_tile.h)

target_link_libraries(image_processor PRIVATE imageproc_lib)
add_subdirectory(src/filters)
add_subdirectory(src/bmp)
add_subdirectory(src/image)
