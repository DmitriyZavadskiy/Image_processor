#pragma once
#include "../filters/filter.h"

class GrayScaleFilter : public Filter {
public:
    void Apply(Image &image) override;
};
