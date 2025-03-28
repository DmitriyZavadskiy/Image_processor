#pragma once
#include "matrix_filter.h"

class BlurFilter : public MatrixFilter {
public:
    explicit BlurFilter(double sigma);
};
