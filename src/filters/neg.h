#pragma once
#include "../filters/filter.h"

class NegativeFilter : public Filter {
public:
    void Apply(Image &image) override;
};
