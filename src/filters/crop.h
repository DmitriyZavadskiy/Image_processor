#pragma once
#include "../filters/filter.h"

class CropFilter : public Filter {
public:
    CropFilter(int width, int height) : width_(width), height_(height) {
    }

    void Apply(Image &image) override;

private:
    int width_;
    int height_;
};
