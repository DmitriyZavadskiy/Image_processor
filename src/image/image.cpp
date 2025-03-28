#include "image.h"

Image::Image(int width, int height) : width_(width), height_(height) {
    data_.resize(width_ * height_);
}

void Image::Resize(int width, int height) {
    width_ = width;
    height_ = height;
    data_.resize(width_ * height_);
}

int Image::Width() const {
    return width_;
}
int Image::Height() const {
    return height_;
}

Color &Image::GetPixel(int x, int y) {
    return data_[static_cast<size_t>(y) * width_ + x];
}

const Color &Image::GetPixel(int x, int y) const {
    return data_[static_cast<size_t>(y) * width_ + x];
}
