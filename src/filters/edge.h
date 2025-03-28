#pragma once
#include "matrix_filter.h"

class EdgeFilter : public MatrixFilter {
public:
    explicit EdgeFilter(double threshold);

protected:
    void PreProcess(Image &image) override;
    void PostProcess(Image &image) override;

private:
    double threshold_;
};
