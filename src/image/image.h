#pragma once
#include <vector>
#include "color.h"

class Image {
public:
    Image() = default;
    Image(int width, int height);

    void Resize(int width, int height);

    int Width() const;
    int Height() const;

    Color &GetPixel(int x, int y);
    const Color &GetPixel(int x, int y) const;

private:
    int width_ = 0;
    int height_ = 0;
    std::vector<Color> data_;
};
