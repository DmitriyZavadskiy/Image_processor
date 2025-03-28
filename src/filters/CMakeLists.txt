add_library(
    filters
    registry.cpp
    matrix_filter.cpp
    crop.cpp
    grayscale.cpp
    neg.cpp
    sharpen.cpp
    edge.cpp
    blur.cpp
    affine_tile.cpp
)


target_link_libraries(
    filters
    image
    bmp
)