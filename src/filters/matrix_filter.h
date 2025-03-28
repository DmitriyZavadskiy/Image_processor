#pragma once
#include "filter.h"
#include <vector>

class MatrixFilter : public Filter {
public:
    MatrixFilter(const std::vector<double> &kernel, int kernel_size, bool clamp = true);

    void Apply(Image &image) override;

protected:
    virtual void PreProcess(Image &image) {
    }
    virtual void PostProcess(Image &image) {
    }

    std::vector<double> kernel_;
    int kernel_size_;
    bool clamp_values_;
};
